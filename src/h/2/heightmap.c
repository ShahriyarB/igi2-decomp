/* h/2/heightmap.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: h/2/heightmap.c:276  [anchor-hash]
struct World_s *__cdecl HeightMap_SaveBitmap(struct World_s *ptWorld)
{
  #pragma pack(push, 1)
  union
  {
    struct { int v11; };
    struct { char igi2_o1[4]; char zFileName[256]; };
    char igi2_extent[260];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct Terrain_HeightBitmap_t *ptHeightBitmap; // ebx
  int v2; // eax
  char v3; // cl
  char *v4; // edi
  struct File_s *v6; // esi
  struct Terrain_HeightBitmap_t *v7; // eax
  int v8; // ecx
  struct Terrain_HeightBitmap_t *v9; // edi
  struct World_s *result; // eax

  ptHeightBitmap = ptWorld->ptHeightBitmap;
  v2 = 0;
  do
  {
    v3 = World_zTerrainFileName[v2];
    igi2_frame.zFileName[v2++] = v3;
  }
  while ( v3 );
  v4 = (char *)&igi2_frame.v11 + 3;
  while ( *++v4 )
    ;
  strcpy(v4, ".hmp");
  v6 = File_New(igi2_frame.zFileName, "w");
  v7 = ptHeightBitmap;
  v8 = 256;
  do
  {
    if ( !v7->ptBitmap )
      v7->nSize = 0;
    ++v7;
    --v8;
  }
  while ( v8 );
  File_atDevice[v6->eDeviceID].pfWrite(v6->eDeviceID, v6, ptHeightBitmap, 3072u);
  File_atDevice[v6->eDeviceID].pfSync(v6->eDeviceID, v6, FILE_SYNC_WAIT);
  v9 = ptHeightBitmap;
  igi2_frame.v11 = 256;
  do
  {
    if ( v9->ptBitmap )
    {
      File_atDevice[v6->eDeviceID].pfWrite(v6->eDeviceID, v6, v9->ptBitmap, (v9->nSize + 1) * (v9->nSize + 1));
      File_atDevice[v6->eDeviceID].pfSync(v6->eDeviceID, v6, FILE_SYNC_WAIT);
    }
    ++v9;
    result = (struct World_s *)--igi2_frame.v11;
  }
  while ( igi2_frame.v11 );
  if ( v6 != &File_tDummyAsyncFile )
    return ((struct World_s *(__cdecl *)(int, struct File_s *))File_atDevice[v6->eDeviceID].pfDelete)(v6->eDeviceID, v6);
  File_tDummyAsyncFile.isAsync = false;
  return result;
}

// source: h/2/heightmap.c:334  [anchor-mhash]
void __cdecl HeightMap_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *v2; // ecx

  v2 = (struct QTask_s *)World_ptActiveWorld;
  ptQTask[5].ptNext = (struct QTask_s *)-1;
  ptQTask[6].tQTaskChildren.ptTail = (struct QTask_s *)-1;
  ptQTask[2].ptParent = v2;
  HIBYTE(ptQTask[5].tQTaskRefList.ptTail) = 1;
  BYTE1(ptQTask[5].ptParent) = 1;
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
  ptQTask[4].ptParent = (struct QTask_s *)12;
  *(_DWORD *)&ptQTask[4].eQTaskType = 255;
  ptQTask[5].ptPrev = nullptr;
  LOBYTE(ptQTask[5].tQTaskRefList.ptTail) = 0;
  *(_DWORD *)&ptQTask[5].eQTaskType = 128;
  BYTE1(ptQTask[5].tQTaskRefList.ptTail) = 0;
  LOBYTE(ptQTask[5].ptParent) = 0;
  ptQTask[6].ptPrev = nullptr;
  BYTE2(ptQTask[5].tQTaskRefList.ptTail) = 0;
  ptQTask[6].tQTaskRefList.ptHead = nullptr;
  ptQTask[6].tQTaskChildren.ptHead = nullptr;
  ptQTask[6].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[5].tQTaskChildren.ptTail = (struct QTask_s *)8;
  ptQTask[5].tQTaskRefList.ptHead = (struct QReference_s *)7;
  ptQTask[5].tQTaskRefList.ptMiddle = (struct QReference_s *)7;
  BYTE2(ptQTask[5].ptParent) = 0;
  HeightMap_tRandomState.anRandom[0] = -773192938;
  HeightMap_tRandomState.anRandom[1] = -965544106;
  HeightMap_tRandomState.anRandom[2] = 1572805325;
}

// source: h/2/heightmap.c:1566  [anchor-mhash]
void __cdecl HeightMap_EnterHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *ptParent; // edx
  int v3; // ecx
  int v4; // ecx
  char *v5; // edx

  ptParent = ptQTask[2].ptParent;
  if ( ptParent->tQTaskChildren.ptMiddle )
  {
    v3 = *(_DWORD *)&ptQTask[4].eQTaskType;
    if ( v3 >= 0 && *((_DWORD *)&ptParent[9].ptPrev->ptNext + 3 * v3) )
    {
      v4 = HeightMap_nStackItem;
      v5 = (char *)&ptQTask[6].tQTaskChildren.ptTail->ptNext + 1;
      ptQTask[6].ptNext = (struct QTask_s *)1;
      HeightMap_aiStackItem[v4] = (unsigned int)v5;
      HeightMap_biHeightMap = (unsigned int)&ptQTask[6].tQTaskChildren.ptTail->ptNext + 1;
      HeightMap_nStackItem = v4 + 1;
    }
    else
    {
      ptQTask[6].ptNext = nullptr;
    }
  }
}

// source: h/2/heightmap.c:1605  [anchor-mhash]
void __cdecl HeightMap_LeaveHandler(struct QTask_s *ptQTask, void *pxContext)
{
  if ( ptQTask[2].ptParent->tQTaskChildren.ptMiddle && ptQTask[6].ptNext )
  {
    --HeightMap_nStackItem;
    HeightMap_biHeightMap = 0;
    if ( HeightMap_nStackItem - 1 >= 0 )
      HeightMap_biHeightMap = HeightMap_aiStackItem[HeightMap_nStackItem - 1];
  }
}

// source: h/2/heightmap.c:1679  [anchor-mhash]
void __cdecl HeightMap_DeleteHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptNext; // eax
  struct QTask_s *ptTail; // eax
  int v3; // edx
  struct HeightMap_t *v4; // ecx

  if ( World_ptActiveWorld->ptCubeTree )
  {
    if ( !LOBYTE(ptQTask[5].ptParent) )
    {
      ptNext = ptQTask[5].ptNext;
      if ( ptNext != (struct QTask_s *)-1 && !World_aisHeightBitmapResource[(_DWORD)ptNext] )
      {
        Mem_DeAllocFn(*((void **)&ptQTask[2].ptParent[9].ptPrev->ptNext + 3 * (_DWORD)ptNext));
        *((_DWORD *)&ptQTask[2].ptParent[9].ptPrev->ptNext + 3 * (int)ptQTask[5].ptNext) = 0;
        *((_DWORD *)&ptQTask[2].ptParent[9].ptPrev->ptNext + 3 * (int)ptQTask[5].ptNext) = 0;
      }
      ptTail = ptQTask[6].tQTaskChildren.ptTail;
      if ( ptTail != (struct QTask_s *)-1 )
      {
        v3 = HeightMap_nHeightMap - 1;
        if ( ptTail != (struct QTask_s *)(HeightMap_nHeightMap - 1) )
        {
          v4 = (struct HeightMap_t *)dword_7AE80D4[HeightMap_nHeightMap];
          HeightMap_aptHeightMap[(_DWORD)ptTail] = v4;
          v4->iGlobalList = (int)ptTail;
        }
        HeightMap_nHeightMap = v3;
      }
    }
    World_RemoveDynCubeObj((struct World_s *)ptQTask[2].ptParent, (struct DynCubeObj_s *)ptQTask);
  }
}

// source: h/2/heightmap.c:1734  [size]
void __cdecl HeightMap_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = *(_DWORD *)&Origo_eQTaskType;
}

// source: h/2/heightmap.c:2079  [anchor-callee]
int __cdecl HeightMap_SnapSize(int nSize)
{
  if ( nSize >= 256 )
    return 256;
  if ( nSize >= 128 )
    return 128;
  if ( nSize >= 64 )
    return 64;
  if ( nSize < 32 )
    return 8 * (nSize >= 16) + 8;
  return 32;
}

// source: h/2/heightmap.c:2125  [anchor-mhash]
void __cdecl HeightMap_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct QTask_s *v43; };
    struct { char igi2_o1[52]; struct Terrain_HeightBitmap_t *ptHeightBitmap; };
    struct { char igi2_o2[52]; int ptHeightBitmapa; };
    struct { char igi2_o3[56]; double vHighestZ; };
    struct { char igi2_o4[56]; double vHighestZa; };
    struct { char igi2_o5[56]; double vHighestZb; };
    struct { char igi2_o6[68]; int nCubeSize; };
    struct { char igi2_o7[68]; int nCubeSizea; };
    struct { char igi2_o8[68]; int nCubeSizeb; };
    struct { char igi2_o9[72]; struct real64x3_t tNewPos; };
    struct { char igi2_o10[96]; double vLowestZ; };
    struct { char igi2_o11[104]; double vRadius; };
    struct { char igi2_o12[112]; double vNegDist; };
    struct { char igi2_o13[120]; struct real64x3_t tCenterPos; };
    struct { char igi2_o14[144]; struct real64x3_t tGetNextZPos; };
    struct { char igi2_o15[168]; struct QIntersection_s tIntersection; };
    char igi2_extent[288];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  bool v2; // zf
  char ptParent; // al
  struct QTask_s *v4; // eax
  int isHit; // eax
  int v6; // esi
  double vZ; // st7
  struct World_s *v8; // eax
  double v9; // st7
  double v10; // st6
  double v11; // st7
  int ptTail_high; // ecx
  struct QTask_s *v13; // esi
  int v14; // eax
  int v15; // esi
  struct Terrain_HeightBitmap_t *v16; // eax
  unsigned __int8 *v17; // eax
  struct Terrain_HeightBitmap_t *v18; // edi
  unsigned __int8 *v19; // eax
  struct Terrain_HeightBitmap_t *v20; // eax
  int v21; // eax
  struct QTask_s *ptNext; // eax
  struct Terrain_HeightBitmap_t *v23; // esi
  char ptTail; // cl
  struct QTask_s *v25; // eax
  unsigned __int8 *p_isEdit; // eax
  int v27; // ecx
  int v28; // eax
  char v29; // al
  unsigned int v30; // ecx
  unsigned int v31; // edx
  unsigned int v32; // eax
  int v33; // ecx
  int v34; // edx
  unsigned __int16 BaseQTaskType; // ax
  struct QTask_s *ptHead; // ecx
  unsigned __int16 v37; // ax
  struct QTask_s *v38; // ecx
  struct QTask_s *ptPrev; // edx
  int v40; // eax
  int v41; // esi
  double v42; // st7

  igi2_frame.nCubeSize = 2 * (0x40000000 >> (int)ptQTask[4].ptParent);
  v2 = World_ptActiveWorld->ptCubeTree == nullptr;
  igi2_frame.vNegDist = -536870912.0;
  if ( !v2 )
  {
    ptParent = (char)ptQTask[5].ptParent;
    World_isImmediateRunOnCollision = 0;
    if ( !ptParent )
    {
      if ( ptQTask[6].tQTaskRefList.ptHead )
      {
        QTask_Delete((struct QTask_s *)ptQTask[6].tQTaskRefList.ptHead);
        ptQTask[6].tQTaskRefList.ptHead = nullptr;
      }
      igi2_frame.ptHeightBitmap = (struct Terrain_HeightBitmap_t *)ptQTask[2].ptParent[9].ptPrev;
      if ( ptQTask[6].tQTaskChildren.ptTail == (struct QTask_s *)-1 )
      {
        v4 = (struct QTask_s *)HeightMap_nHeightMap;
        HeightMap_aptHeightMap[HeightMap_nHeightMap] = (struct HeightMap_t *)ptQTask;
        ptQTask[6].tQTaskChildren.ptTail = v4;
        HeightMap_nHeightMap = (int)&v4->ptNext + 1;
        if ( (int)&v4->ptNext + 1 >= 256 )
        {
          LDebug_Error("Too many texturemodfiers");
          goto LABEL_8;
        }
      }
    }
    HeightMap_atRenderItem[(int)ptQTask[6].tQTaskChildren.ptTail].ptBitmap = nullptr;
    qmemcpy(&igi2_frame.tNewPos, &ptQTask[3], sizeof(igi2_frame.tNewPos));
    if ( LOBYTE(ptQTask[5].ptParent) )
      goto LABEL_16;
    isHit = 0;
    qmemcpy(&igi2_frame.tGetNextZPos, &ptQTask[3], sizeof(igi2_frame.tGetNextZPos));
    igi2_frame.tIntersection.isHit = 0;
    v6 = 0;
    while ( v6 < 5 )
    {
      World_GetNextZ(
        (struct World_s *)ptQTask[2].ptParent,
        &igi2_frame.tIntersection,
        &igi2_frame.tGetNextZPos,
        1,
        &igi2_frame.vNegDist,
        512,
        nullptr,
        0x80000000);
      isHit = igi2_frame.tIntersection.isHit;
      ++v6;
      if ( igi2_frame.tIntersection.isHit )
      {
        vZ = igi2_frame.tIntersection.tPos.vZ;
        goto LABEL_17;
      }
    }
    if ( !isHit )
LABEL_16:
      vZ = igi2_frame.tNewPos.vZ;
    else
      vZ = igi2_frame.tIntersection.tPos.vZ;
LABEL_17:
    v8 = (struct World_s *)ptQTask[2].ptParent;
    igi2_frame.tNewPos.vX = (double)v8->tOrigo.nX + igi2_frame.tNewPos.vX;
    igi2_frame.tNewPos.vY = (double)v8->tOrigo.nY + igi2_frame.tNewPos.vY;
    igi2_frame.tNewPos.vZ = (double)v8->tOrigo.nZ + vZ;
    v9 = (double)(int)(-igi2_frame.nCubeSize & (__int64)igi2_frame.tNewPos.vX);
    *(double *)&ptQTask[3].tQTaskRefList.ptMiddle = v9;
    v10 = (double)(int)(-igi2_frame.nCubeSize & (__int64)igi2_frame.tNewPos.vY);
    *(double *)&ptQTask[3].ptParent = v10;
    igi2_frame.vLowestZ = (double)(int)(-igi2_frame.nCubeSize & (__int64)igi2_frame.tNewPos.vZ);
    *(double *)&ptQTask[4].ptNext = igi2_frame.vLowestZ;
    qmemcpy(&igi2_frame.tNewPos, &ptQTask[3].tQTaskRefList.ptMiddle, sizeof(igi2_frame.tNewPos));
    igi2_frame.vHighestZa = (double)igi2_frame.nCubeSize;
    *(double *)&ptQTask[4].tQTaskChildren.ptHead = igi2_frame.vHighestZa + v9;
    *(double *)&ptQTask[4].tQTaskChildren.ptTail = igi2_frame.vHighestZa + v10;
    *(double *)&ptQTask[4].tQTaskRefList.ptMiddle = igi2_frame.vHighestZa + igi2_frame.vLowestZ;
    igi2_frame.tNewPos.vY = igi2_frame.vHighestZa * 0.5 + igi2_frame.tNewPos.vY;
    v11 = igi2_frame.tNewPos.vX + igi2_frame.vHighestZa * 0.5;
    igi2_frame.tNewPos.vZ = igi2_frame.vHighestZa * 0.5 + igi2_frame.tNewPos.vZ;
    igi2_frame.vHighestZb = (double)v8->tOrigo.nX;
    igi2_frame.tNewPos.vX = v11 - igi2_frame.vHighestZb;
    igi2_frame.tNewPos.vY = igi2_frame.tNewPos.vY - (double)v8->tOrigo.nY;
    igi2_frame.tNewPos.vZ = igi2_frame.tNewPos.vZ - (double)v8->tOrigo.nZ;
    *(double *)&ptQTask[3].tQTaskRefList.ptMiddle = *(double *)&ptQTask[3].tQTaskRefList.ptMiddle - igi2_frame.vHighestZb;
    *(double *)&ptQTask[3].ptParent = *(double *)&ptQTask[3].ptParent - (double)v8->tOrigo.nY;
    *(double *)&ptQTask[4].ptNext = *(double *)&ptQTask[4].ptNext - (double)v8->tOrigo.nZ;
    ptTail_high = HIBYTE(ptQTask[5].tQTaskRefList.ptTail);
    *(double *)&ptQTask[4].tQTaskChildren.ptHead = *(double *)&ptQTask[4].tQTaskChildren.ptHead - (double)v8->tOrigo.nX;
    *(double *)&ptQTask[4].tQTaskChildren.ptTail = *(double *)&ptQTask[4].tQTaskChildren.ptTail - (double)v8->tOrigo.nY;
    *(double *)&ptQTask[4].tQTaskRefList.ptMiddle = *(double *)&ptQTask[4].tQTaskRefList.ptMiddle
                                                  - (double)v8->tOrigo.nZ;
    if ( (_BYTE)ptTail_high )
      World_RegisterDynCubeObjFirstTimeMinMaxXYZ(
        v8,
        (struct DynCubeObj_s *)ptQTask,
        &igi2_frame.tNewPos,
        (struct real64x3_t *)&ptQTask[3].tQTaskRefList.ptMiddle,
        (struct real64x3_t *)&ptQTask[4].tQTaskChildren,
        WORLD_DYNCUBETREE_CATEGORY_TERRAINMODIFIERS);
    World_MoveDynCubeObjMinMaxXYZ(
      (struct World_s *)ptQTask[2].ptParent,
      (struct DynCubeObj_s *)ptQTask,
      &igi2_frame.tNewPos,
      (struct real64x3_t *)&ptQTask[3].tQTaskRefList.ptMiddle,
      (struct real64x3_t *)&ptQTask[4].tQTaskChildren);
    if ( !LOBYTE(ptQTask[5].ptParent) )
    {
      v13 = *(struct QTask_s **)&ptQTask[4].eQTaskType;
      if ( v13 != (struct QTask_s *)-1 )
      {
        v14 = HeightMap_SnapSize(*(_DWORD *)&ptQTask[5].eQTaskType);
        *(_DWORD *)&ptQTask[5].eQTaskType = v14;
        igi2_frame.nCubeSizea = v14;
        if ( igi2_frame.ptHeightBitmap[(_DWORD)v13].ptBitmap )
        {
          if ( HIBYTE(ptQTask[5].tQTaskRefList.ptTail) )
            BYTE2(ptQTask[5].tQTaskRefList.ptTail) = 1;
          if ( v13 == ptQTask[5].ptNext )
          {
            v18 = &igi2_frame.ptHeightBitmap[(_DWORD)v13];
            if ( v18->nSize != v14 )
            {
              if ( World_aisHeightBitmapResource[(_DWORD)v13] )
              {
                BYTE2(ptQTask[5].tQTaskRefList.ptTail) = 0;
              }
              else
              {
                Mem_DeAllocFn(v18->ptBitmap);
                v18->ptBitmap = nullptr;
              }
              v18->nSize = igi2_frame.nCubeSizea;
              v19 = (unsigned __int8 *)Mem_AllocFn((igi2_frame.nCubeSizea + 1) * (igi2_frame.nCubeSizea + 1), 4);
              igi2_frame.ptHeightBitmap[(_DWORD)v13].ptBitmap = v19;
              memset(v19, 0x40u, (igi2_frame.nCubeSizea + 1) * (igi2_frame.nCubeSizea + 1));
              World_aisHeightBitmapResource[(_DWORD)v13] = 0;
            }
          }
          else
          {
            v20 = &igi2_frame.ptHeightBitmap[(_DWORD)v13];
            *(_DWORD *)&ptQTask[5].eQTaskType = v20->nSize;
            LOBYTE(ptQTask[5].tQTaskRefList.ptTail) = v20->isEdit;
          }
        }
        else
        {
          v15 = 0;
          v16 = igi2_frame.ptHeightBitmap + 2;
          while ( v16[-2].ptBitmap )
          {
            if ( !v16[-1].ptBitmap )
            {
              ++v15;
              break;
            }
            if ( !v16->ptBitmap )
            {
              v15 += 2;
              break;
            }
            if ( !v16[1].ptBitmap )
            {
              v15 += 3;
              break;
            }
            if ( !v16[2].ptBitmap )
            {
              v15 += 4;
              break;
            }
            if ( !v16[3].ptBitmap )
            {
              v15 += 5;
              break;
            }
            if ( !v16[4].ptBitmap )
            {
              v15 += 6;
              break;
            }
            if ( !v16[5].ptBitmap )
            {
              v15 += 7;
              break;
            }
            v15 += 8;
            v16 += 8;
            if ( v15 >= 256 )
              break;
          }
          if ( v15 == 256 )
            v15 = 255;
          igi2_frame.ptHeightBitmap[v15].nSize = igi2_frame.nCubeSizea;
          v17 = (unsigned __int8 *)Mem_AllocFn((igi2_frame.nCubeSizea + 1) * (igi2_frame.nCubeSizea + 1), 4);
          igi2_frame.ptHeightBitmap[v15].ptBitmap = v17;
          memset(v17, 0x40u, (igi2_frame.nCubeSizea + 1) * (igi2_frame.nCubeSizea + 1));
          World_aisHeightBitmapResource[v15] = 0;
          *(_DWORD *)&ptQTask[4].eQTaskType = v15;
        }
        switch ( igi2_frame.nCubeSizea )
        {
          case 256:
            v21 = 7;
            break;
          case 128:
            v21 = 6;
            break;
          case 64:
            v21 = 5;
            break;
          case 32:
            v21 = 4;
            break;
          case 16:
            v21 = 3;
            break;
          case 8:
            v21 = 2;
            break;
          default:
            LDebug_Error("Illegal shift size");
LABEL_8:
            abort();
        }
        ptQTask[5].tQTaskChildren.ptHead = (struct QTask_s *)(30 - (unsigned int)ptQTask[4].ptParent - v21);
        ptQTask[5].tQTaskChildren.ptMiddle = (struct QTask_s *)(v21 - 2);
      }
      if ( *(_DWORD *)&ptQTask[4].eQTaskType != -1 || (ptNext = ptQTask[5].ptNext, ptNext == (struct QTask_s *)-1) )
      {
        v23 = igi2_frame.ptHeightBitmap;
      }
      else
      {
        v23 = igi2_frame.ptHeightBitmap;
        if ( !World_aisHeightBitmapResource[(_DWORD)ptNext] )
        {
          Mem_DeAllocFn(igi2_frame.ptHeightBitmap[(_DWORD)ptNext].ptBitmap);
          igi2_frame.ptHeightBitmap[(int)ptQTask[5].ptNext].ptBitmap = nullptr;
        }
        igi2_frame.ptHeightBitmap[(int)ptQTask[5].ptNext].ptBitmap = nullptr;
      }
      ptTail = (char)ptQTask[5].tQTaskRefList.ptTail;
      v25 = *(struct QTask_s **)&ptQTask[4].eQTaskType;
      ptQTask[5].ptNext = v25;
      if ( ptTail )
      {
        p_isEdit = &v23->isEdit;
        v27 = 256;
        do
        {
          *p_isEdit = 0;
          p_isEdit += 12;
          --v27;
        }
        while ( v27 );
        v28 = *(_DWORD *)&ptQTask[4].eQTaskType;
        if ( v28 >= 0 )
          v23[v28].isEdit = 1;
      }
      else if ( (int)v25 >= 0 )
      {
        v23[(_DWORD)v25].isEdit = 0;
      }
      v29 = BYTE1(ptQTask[5].ptParent);
      HIBYTE(ptQTask[5].tQTaskRefList.ptTail) = 0;
      if ( v29 )
      {
        qmemcpy(&igi2_frame.tCenterPos, &ptQTask[1], sizeof(igi2_frame.tCenterPos));
        igi2_frame.vLowestZ = igi2_frame.tCenterPos.vZ;
        igi2_frame.vHighestZ = igi2_frame.tCenterPos.vZ;
        igi2_frame.nCubeSizeb = 200;
        igi2_frame.vRadius = (double)(0x40000000 >> (int)ptQTask[4].ptParent);
        do
        {
          qmemcpy(&igi2_frame.tGetNextZPos, &igi2_frame.tCenterPos, sizeof(igi2_frame.tGetNextZPos));
          v30 = (HeightMap_tRandomState.anRandom[0] >> 7) ^ HeightMap_tRandomState.anRandom[2];
          v31 = v30 ^ HeightMap_tRandomState.anRandom[1];
          v32 = (v30 ^ HeightMap_tRandomState.anRandom[1]) + HeightMap_tRandomState.anRandom[0];
          v33 = (v32 >> 7) ^ v30;
          v34 = v33 ^ v31;
          HeightMap_tRandomState.anRandom[0] = v34 + v32;
          HeightMap_tRandomState.anRandom[2] = v33;
          HeightMap_tRandomState.anRandom[1] = v34;
          igi2_frame.tGetNextZPos.vX = ((double)(unsigned __int16)v32 * 0.0000152587890625
                           + (double)(unsigned __int16)v32 * 0.0000152587890625
                           - 1.0)
                          * igi2_frame.vRadius
                          + igi2_frame.tCenterPos.vX;
          igi2_frame.v43 = ptQTask[2].ptParent;
          igi2_frame.tGetNextZPos.vY = ((double)(unsigned __int16)(v34 + v32) * 0.0000152587890625
                           + (double)(unsigned __int16)(v34 + v32) * 0.0000152587890625
                           - 1.0)
                          * igi2_frame.vRadius
                          + igi2_frame.tGetNextZPos.vY;
          igi2_frame.tGetNextZPos.vZ = igi2_frame.tGetNextZPos.vZ + 268435456.0;
          World_GetNextZ((struct World_s *)igi2_frame.v43, &igi2_frame.tIntersection, &igi2_frame.tGetNextZPos, 1, &igi2_frame.vNegDist, 512, nullptr, 0x80000000);
          if ( igi2_frame.tIntersection.isHit )
          {
            if ( igi2_frame.tIntersection.tPos.vZ < igi2_frame.vLowestZ )
              igi2_frame.vLowestZ = igi2_frame.tIntersection.tPos.vZ;
            if ( igi2_frame.tIntersection.tPos.vZ > igi2_frame.vHighestZ )
              igi2_frame.vHighestZ = igi2_frame.tIntersection.tPos.vZ;
          }
          --igi2_frame.nCubeSizeb;
        }
        while ( igi2_frame.nCubeSizeb );
        qmemcpy(&igi2_frame.tNewPos, &igi2_frame.tCenterPos, sizeof(igi2_frame.tNewPos));
        igi2_frame.tNewPos.vZ = igi2_frame.tCenterPos.vZ - igi2_frame.vRadius;
        for ( igi2_frame.ptHeightBitmapa = 0; igi2_frame.vLowestZ < igi2_frame.tNewPos.vZ; igi2_frame.tNewPos.vZ = igi2_frame.tNewPos.vZ - igi2_frame.vRadius )
        {
          if ( !igi2_frame.ptHeightBitmapa )
          {
            BaseQTaskType = QTask_GetBaseQTaskType();
            ptQTask[6].tQTaskRefList.ptHead = (struct QReference_s *)QTask_NewFn(ptQTask, BaseQTaskType, nullptr);
            igi2_frame.ptHeightBitmapa = 1;
          }
          ptHead = (struct QTask_s *)ptQTask[6].tQTaskRefList.ptHead;
          igi2_frame.tNewPos.vZ = igi2_frame.tNewPos.vZ - igi2_frame.vRadius;
          HeightMap_NewCopy(ptHead, (struct HeightMap_t *)ptQTask, &igi2_frame.tNewPos);
        }
        qmemcpy(&igi2_frame.tNewPos, &igi2_frame.tCenterPos, sizeof(igi2_frame.tNewPos));
        for ( igi2_frame.tNewPos.vZ = igi2_frame.vRadius + igi2_frame.tCenterPos.vZ; igi2_frame.vHighestZ > igi2_frame.tNewPos.vZ; igi2_frame.tNewPos.vZ = igi2_frame.tNewPos.vZ + igi2_frame.vRadius )
        {
          if ( !igi2_frame.ptHeightBitmapa )
          {
            v37 = QTask_GetBaseQTaskType();
            ptQTask[6].tQTaskRefList.ptHead = (struct QReference_s *)QTask_NewFn(ptQTask, v37, nullptr);
            igi2_frame.ptHeightBitmapa = 1;
          }
          v38 = (struct QTask_s *)ptQTask[6].tQTaskRefList.ptHead;
          igi2_frame.tNewPos.vZ = igi2_frame.tNewPos.vZ + igi2_frame.vRadius;
          HeightMap_NewCopy(v38, (struct HeightMap_t *)ptQTask, &igi2_frame.tNewPos);
        }
      }
    }
    ptPrev = ptQTask[2].ptParent[9].ptPrev;
    v40 = (int)ptQTask[6].tQTaskChildren.ptTail;
    HeightMap_atRenderItem[v40].nPitchShift = (int)ptQTask[5].tQTaskChildren.ptMiddle;
    HeightMap_atRenderItem[v40].vScale = 1.0;
    HeightMap_atRenderItem[v40].iMaterial = (int)ptQTask[5].ptPrev;
    HeightMap_atRenderItem[v40].nShift = (int)ptQTask[5].tQTaskChildren.ptHead;
    HeightMap_atRenderItem[v40].ptBitmap = *((unsigned __int8 **)&ptPrev->ptNext + 3 * *(_DWORD *)&ptQTask[4].eQTaskType);
    v41 = 1 << HeightMap_atRenderItem[v40].nShift;
    World_isImmediateRunOnCollision = 1;
    *(float *)(v40 * 48 + 139693584) = 1.0 / (double)v41;
    v42 = (double)(0x40000000 >> (int)ptQTask[4].ptParent);
    *(double *)(v40 * 48 + 139693592) = *(double *)&ptQTask[1].ptNext - v42;
    *(double *)(v40 * 48 + 139693600) = *(double *)&ptQTask[1].tQTaskChildren.ptHead - v42;
    LOBYTE(ptQTask[5].tQTaskRefList.ptTail) = *((_BYTE *)&ptPrev->ptPrev + 12 * *(_DWORD *)&ptQTask[4].eQTaskType);
    HIBYTE(ptQTask[5].tQTaskRefList.ptTail) = 0;
  }
}

// source: h/2/heightmap.c:2582  [size]
void __cdecl HeightMap_ModifyGroundMaterialHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *ptTail; // eax
  int v3; // ecx

  if ( *(int *)&ptQTask[4].eQTaskType >= 0 )
  {
    ptTail = ptQTask[6].tQTaskChildren.ptTail;
    if ( HeightMap_atRenderItem[(_DWORD)ptTail].ptBitmap )
    {
      v3 = HeightMap_nStackItem;
      HeightMap_aiStackItem[HeightMap_nStackItem] = (unsigned int)ptTail;
      HeightMap_nStackItem = v3 + 1;
    }
  }
}

// source: h/2/heightmap.c:2606  [size]
void __cdecl HeightMap_DynCubeObjInGameEvalHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = 0;
}

// source: h/2/heightmap.c:2652  [anchor-hash]
void __cdecl HeightMap_Open()
{
  unsigned __int16 v0; // si
  struct ParameterList_s *v1; // eax
  int v2; // edx

  HeightMap_tRandomState.anRandom[0] = -773192938;
  HeightMap_tRandomState.anRandom[1] = -965544106;
  HeightMap_tRandomState.anRandom[2] = 1572805325;
  v0 = QTask_NewQTaskType("HeightMap", 264, DynCubeObj_eQTaskType, 0, 0);
  HeightMap_eQTaskType = v0;
  QTask_LinkQTaskEventHandlerFn(v0, 0, HeightMap_CreateHandler);
  QTask_LinkQTaskEventHandlerFn(v0, 14, HeightMap_ModifyGroundMaterialHandler);
  QTask_LinkQTaskEventHandlerFn(v0, 16, HeightMap_LeaveHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 2, HeightMap_DeleteHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))HeightMap_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(v0, ParameterList_eUpdateInternalDataQTaskEvent, HeightMap_UpdateInternalDataHandler);
  QTask_LinkQTaskEventHandlerFn(v0, 11, nullptr);
  QTask_LinkQTaskEventHandlerFn(v0, 12, nullptr);
  QTask_LinkQTaskEventHandlerFn(v0, QCube_eGetClosestVertexQTaskEvent, nullptr);
  QTask_LinkQTaskEventHandlerFn(v0, 10, nullptr);
  QTask_LinkQTaskEventHandlerFn(v0, 13, nullptr);
  QTask_LinkQTaskEventHandlerFn(v0, 15, HeightMap_EnterHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    DynCube_eDynCubeObjInGameEvalQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))HeightMap_DynCubeObjInGameEvalHandler);
  QTask_LinkQTaskEventHandlerFn(v0, 9, nullptr);
  QTask_LinkQTaskEventHandlerFn(v0, 5, nullptr);
  QTask_LinkQTaskEventHandlerFn(v0, 6, nullptr);
  v1 = (struct ParameterList_s *)Mem_AllocFn(292, 4);
  v1->ptParameterListItem = (struct ParameterListItem_s *)&v1[1];
  v2 = Level_eParameterTypeObjectPos;
  v1->nParameters = 0;
  v1->nMaxParameters = 14;
  *(_DWORD *)&Origo_eQTaskType = v1;
  ParameterList_AddParameter(v1, 0x78u, v2, "Position", 7u, nullptr);
  ParameterList_AddParameter(
    *(struct ParameterList_s **)&Origo_eQTaskType,
    0xC0u,
    Level_eParameterTypeInt32,
    "Level",
    7u,
    nullptr);
  ParameterList_AddParameter(
    *(struct ParameterList_s **)&Origo_eQTaskType,
    0xECu,
    Level_eParameterTypeInt32,
    "Size",
    7u,
    nullptr);
  ParameterList_AddParameter(
    *(struct ParameterList_s **)&Origo_eQTaskType,
    0xE4u,
    Level_eParameterTypebool8,
    "isEdit",
    7u,
    nullptr);
  ParameterList_AddParameter(
    *(struct ParameterList_s **)&Origo_eQTaskType,
    0xE5u,
    Level_eParameterTypebool8,
    "isSave",
    6u,
    nullptr);
  ParameterList_AddParameter(
    *(struct ParameterList_s **)&Origo_eQTaskType,
    0xF4u,
    Level_eParameterTypePushButton,
    "FIXUPALL",
    6u,
    nullptr);
  ParameterList_AddParameter(
    *(struct ParameterList_s **)&Origo_eQTaskType,
    0xF8u,
    Level_eParameterTypePushButton,
    "AUTOSMOOTH",
    6u,
    nullptr);
  ParameterList_AddParameter(
    *(struct ParameterList_s **)&Origo_eQTaskType,
    0xE9u,
    Level_eParameterTypebool8,
    "MULTIPLE HEIGHT",
    6u,
    nullptr);
  ParameterList_AddParameter(
    *(struct ParameterList_s **)&Origo_eQTaskType,
    0xC4u,
    Level_eParameterTypeInt32,
    "Bitmap ID",
    3u,
    nullptr);
  ParameterList_AddParameter(
    *(struct ParameterList_s **)&Origo_eQTaskType,
    0xD8u,
    Level_eParameterTypeInt32,
    "NORMALSMOOTH",
    7u,
    nullptr);
  ParameterList_AddParameter(
    *(struct ParameterList_s **)&Origo_eQTaskType,
    0xDCu,
    Level_eParameterTypeInt32,
    "BLURSMOOTH",
    7u,
    nullptr);
  ParameterList_AddParameter(
    *(struct ParameterList_s **)&Origo_eQTaskType,
    0xE0u,
    Level_eParameterTypeInt32,
    "HEIGHTSMOOTH",
    6u,
    nullptr);
  ParameterList_AddParameter(
    *(struct ParameterList_s **)&Origo_eQTaskType,
    0xFCu,
    Level_eParameterTypePushButton,
    "AUTOSMOOTH ALL",
    6u,
    nullptr);
  ParameterList_AddParameter(
    *(struct ParameterList_s **)&Origo_eQTaskType,
    0xEAu,
    Level_eParameterTypebool8,
    "isTraceTop",
    6u,
    nullptr);
  HeightMap_nStackItem = 0;
}

// source: h/2/heightmap.c:2716  [size]
void __cdecl HeightMap_Close()
{
  int v0; // esi

  if ( *(_DWORD *)&Origo_eQTaskType )
  {
    v0 = *(_DWORD *)((*(_DWORD *)&Origo_eQTaskType - 4) & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
  QTask_DeleteQTaskType(HeightMap_eQTaskType);
}

// source: h/2/heightmap.c:2733  [size]
unsigned __int16 __cdecl HeightMap_GetQTaskType()
{
  return HeightMap_eQTaskType;
}

// source: h/2/heightmap.c:2764  [anchor-callee]
struct QTask_s *__cdecl HeightMap_NewCopy(
        struct QTask_s *ptParent,
        struct HeightMap_t *ptCopyOf,
        struct real64x3_t *ptPos)
{
  struct QTask_s *v3; // ebx
  int eQTaskType; // edx
  void (__cdecl *pfHandler)(struct QTask_s *, _DWORD); // eax

  v3 = QTask_NewFn(ptParent, HeightMap_eQTaskType, nullptr);
  LOBYTE(v3[5].ptParent) = 1;
  v3[4].ptParent = (struct QTask_s *)ptCopyOf->nLevel;
  *(_DWORD *)&v3[5].eQTaskType = ptCopyOf->nEditSize;
  v3[5].tQTaskChildren.ptHead = (struct QTask_s *)ptCopyOf->nShift;
  v3[5].tQTaskChildren.ptMiddle = (struct QTask_s *)ptCopyOf->nPitchShift;
  v3[5].ptPrev = (struct QTask_s *)ptCopyOf->iMaterial;
  v3[6].tQTaskChildren.ptTail = (struct QTask_s *)ptCopyOf->iGlobalList;
  eQTaskType = v3->eQTaskType;
  *(_DWORD *)&v3[4].eQTaskType = ptCopyOf->nBitmapID;
  qmemcpy(&v3[4].tQTaskChildren, &ptCopyOf->tMax, 0x18u);
  qmemcpy(&v3[3].tQTaskRefList.ptMiddle, &ptCopyOf->tMin, 0x18u);
  qmemcpy(&v3[3], ptPos, 0x18u);
  pfHandler = (void (__cdecl *)(struct QTask_s *, _DWORD))QTask_aatQTaskFinalEvent[ParameterList_eUpdateInternalDataQTaskEvent][eQTaskType].pfHandler;
  if ( pfHandler )
    pfHandler(v3, 0);
  return v3;
}
