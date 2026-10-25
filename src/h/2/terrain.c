/* h/2/terrain.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: h/2/terrain.c:506  [anchor-hash]
struct QTask_s *__cdecl Terrain_SetActiveHeightmaps(struct QTask_s *ptQTask)
{
  unsigned __int16 v1; // dx
  struct QTask_s *result; // eax
  int i; // esi

  v1 = TerrainMap_eQTaskType;
  result = QTask_GetFirstChildOfType(ptQTask, TerrainMap_eQTaskType);
  for ( i = 0; result; ++i )
  {
    if ( i >= 10 )
      break;
    Terrain_aptActiveHeightmap[i] = (struct TerrainMap_t *)result;
    result = QTask_GetNextSiblingOfType(result, v1);
  }
  Terrain_nActiveHeightmaps = i;
  return result;
}

// source: h/2/terrain.c:534  [anchor-callee]
void __cdecl TerrainMap_DeallocateMinMaxHeightMipMaps(struct TerrainMap_t *ptTerrainMap)
{
  int i; // ebp
  struct real32x2_t *v2; // eax
  int v3; // esi
  struct real32x2_t **pptMinMaxHeightMipMap; // eax
  int v5; // ebp

  if ( ptTerrainMap->tMinMaxHeightData.pptMinMaxHeightMipMap )
  {
    for ( i = 0; i < ptTerrainMap->tMinMaxHeightData.nLevels; ++i )
    {
      v2 = ptTerrainMap->tMinMaxHeightData.pptMinMaxHeightMipMap[i];
      if ( v2 )
      {
        v3 = *(_DWORD *)((unsigned int)&v2[-1].vY & 0xFFFFFFFC);
        --Mem_nCurrentAllocations;
        Node_Remove((_DWORD **)v3);
        memset(*(void **)(v3 + 8), 0xCDu, *(_DWORD *)(v3 + 16));
        free((void *)v3);
        ptTerrainMap->tMinMaxHeightData.pptMinMaxHeightMipMap[i] = nullptr;
      }
    }
    pptMinMaxHeightMipMap = ptTerrainMap->tMinMaxHeightData.pptMinMaxHeightMipMap;
    if ( pptMinMaxHeightMipMap )
    {
      --Mem_nCurrentAllocations;
      v5 = *(_DWORD *)((unsigned int)(pptMinMaxHeightMipMap - 1) & 0xFFFFFFFC);
      Node_Remove((_DWORD **)v5);
      memset(*(void **)(v5 + 8), 0xCDu, *(_DWORD *)(v5 + 16));
      free((void *)v5);
    }
    ptTerrainMap->tMinMaxHeightData.pptMinMaxHeightMipMap = nullptr;
  }
  ptTerrainMap->tMinMaxHeightData.pptMinMaxHeightMipMap = nullptr;
  ptTerrainMap->tMinMaxHeightData.nLevels = 0;
}

// source: h/2/terrain.c:562  [anchor-caller]
struct TerrainMap_t *__cdecl TerrainMap_AllocateMinMaxHeightMipMaps(struct TerrainMap_t *ptTerrainMap)
{
  int nWidth; // esi
  int nHeight; // edi
  unsigned int v4; // eax
  int v5; // ebp
  struct TerrainMap_t *result; // eax
  int v7; // ebp
  unsigned int _nTemp; // [esp+10h] [ebp-4h]

  nWidth = ptTerrainMap->nWidth;
  nHeight = ptTerrainMap->nHeight;
  if ( ptTerrainMap->tMinMaxHeightData.pptMinMaxHeightMipMap )
    TerrainMap_DeallocateMinMaxHeightMipMaps(ptTerrainMap);
  _nTemp = nWidth;
  if ( nWidth <= nHeight )
    _nTemp = nHeight;
  _BitScanReverse(&v4, _nTemp);
  v5 = v4 + 1;
  ptTerrainMap->tMinMaxHeightData.nLevels = v4 + 1;
  result = (struct TerrainMap_t *)Mem_AllocFn(4 * (v4 + 1), 4);
  v7 = v5 - 1;
  for ( ptTerrainMap->tMinMaxHeightData.pptMinMaxHeightMipMap = (struct real32x2_t **)result; v7 >= 0; nHeight /= 2 )
  {
    ptTerrainMap->tMinMaxHeightData.pptMinMaxHeightMipMap[v7] = (struct real32x2_t *)Mem_AllocFn(
                                                                                       8 * nWidth * nHeight,
                                                                                       4);
    nWidth /= 2;
    result = (struct TerrainMap_t *)(nHeight / 2);
    --v7;
  }
  return result;
}

// source: h/2/terrain.c:607  [anchor-callee]
void __cdecl TerrainMap_MakeMinMaxHeightMipMaps(struct TerrainMap_t **aptTerrainMaps, int iTerrainMap)
{
  struct TerrainMap_t *v2; // esi
  int v3; // ebx
  float *pvHeightmap; // ebp
  int v5; // edi
  int v6; // eax
  int v7; // edx
  int v8; // ecx
  int v9; // eax
  int v10; // ebx
  float *v11; // ecx
  float *v12; // ebp
  unsigned __int8 *v13; // edx
  unsigned __int8 v14; // cl
  struct TerrainMap_t *v15; // edi
  int nSubmapShift; // ecx
  int v17; // esi
  int v18; // eax
  int v19; // edx
  int v20; // esi
  struct real32x2_t *v21; // edx
  int v22; // esi
  double vX; // st7
  float *v24; // ecx
  float *v25; // ecx
  double v26; // st7
  int v27; // ebp
  int v28; // ecx
  struct real32x2_t **pptMinMaxHeightMipMap; // eax
  struct TerrainMap_t **v30; // edx
  int v31; // eax
  int v32; // edi
  int v33; // ebx
  int v34; // ebx
  int v35; // esi
  int v36; // ecx
  float *v37; // edi
  int v38; // edx
  double v39; // st7
  float *v40; // edi
  int v41; // edx
  bool v42; // c0
  bool v43; // c3
  float *v44; // edx
  int v45; // eax
  double v46; // st7
  bool v47; // cc
  float vMaxZ; // [esp+4h] [ebp-44h]
  int iY; // [esp+8h] [ebp-40h]
  int iYa; // [esp+8h] [ebp-40h]
  float vMaxDelta; // [esp+Ch] [ebp-3Ch]
  float vMaxDeltaa; // [esp+Ch] [ebp-3Ch]
  struct TerrainMap_t *ptTerrainMap; // [esp+10h] [ebp-38h]
  int iLevel; // [esp+14h] [ebp-34h]
  int iLevela; // [esp+14h] [ebp-34h]
  int iX1; // [esp+18h] [ebp-30h]
  int v57; // [esp+1Ch] [ebp-2Ch]
  int v58; // [esp+20h] [ebp-28h]
  float *v59; // [esp+20h] [ebp-28h]
  float *v60; // [esp+24h] [ebp-24h]
  int v61; // [esp+24h] [ebp-24h]
  int v62; // [esp+28h] [ebp-20h]
  float *v63; // [esp+28h] [ebp-20h]
  float *v64; // [esp+2Ch] [ebp-1Ch]
  float *v65; // [esp+2Ch] [ebp-1Ch]
  int nWidth; // [esp+30h] [ebp-18h]
  int v67; // [esp+34h] [ebp-14h]
  float *v68; // [esp+34h] [ebp-14h]
  int nMipMapWidth; // [esp+38h] [ebp-10h]
  int v70; // [esp+3Ch] [ebp-Ch]
  int nHeight; // [esp+44h] [ebp-4h]
  int nHeighta; // [esp+44h] [ebp-4h]
  struct TerrainMap_t **aptTerrainMapsa = *(struct TerrainMap_t ** *)&aptTerrainMaps; // [esp+4Ch] [ebp+4h] ARGSLOT
  float iTerrainMapa = *(float *)&iTerrainMap; // [esp+50h] [ebp+8h] ARGSLOT

  v2 = aptTerrainMaps[iTerrainMap];
  vMaxDelta = 0.0;
  ptTerrainMap = v2;
  if ( !v2->nWidth || !v2->nHeight )
    return;
  TerrainMap_AllocateMinMaxHeightMipMaps(v2);
  v3 = v2->nHeight;
  pvHeightmap = v2->pvHeightmap;
  v5 = v2->nWidth;
  v6 = v2->tMinMaxHeightData.nLevels - 1;
  iLevel = v6;
  nMipMapWidth = (int)pvHeightmap;
  nHeight = v3;
  nWidth = v5;
  iY = 0;
  if ( v3 <= 0 )
    goto LABEL_42;
  v57 = 0;
  v62 = 0;
  v64 = v2->pvHeightmap;
  do
  {
    v7 = iY + 1;
    v8 = v3 - 1;
    if ( iY + 1 < v3 - 1 )
      v8 = iY + 1;
    v9 = 0;
    if ( v5 > 0 )
    {
      v10 = v5 * v8;
      v11 = &pvHeightmap[v5 * v8];
      v12 = v64;
      v58 = v10;
      v67 = v62;
      v60 = v11;
      while ( 1 )
      {
        v70 = v9 + 1;
        iX1 = v9 + 1;
        if ( v9 + 1 >= v5 - 1 )
          iX1 = v5 - 1;
        if ( !iTerrainMap )
        {
          v13 = v2->apiSubmap[0];
          v14 = v13[v57 + v9];
          if ( v14 )
          {
            if ( v13[v10 + iX1] )
            {
              v15 = aptTerrainMaps[v14];
              nSubmapShift = ptTerrainMap->nSubmapShift;
              v17 = v15->nWidth >> nSubmapShift;
              v18 = ((v9 << nSubmapShift) - v15->tSubmapPos.nX) >> nSubmapShift;
              v19 = ((iY << nSubmapShift) - v15->tSubmapPos.nY) >> nSubmapShift;
              if ( v18 >= v17 - 1 )
                v18 = v17 - 1;
              if ( v19 >= v17 - 1 )
                v19 = v17 - 1;
              v20 = v19 * v17;
              v21 = v15->tMinMaxHeightData.pptMinMaxHeightMipMap[v15->tMinMaxHeightData.nLevels - nSubmapShift - 1];
              v22 = v18 + v20;
              vMaxZ = v21[v22].vY;
              vX = v21[v22].vX;
              if ( vMaxZ <= (double)*v12 )
                vMaxZ = *v12;
              v10 = v58;
              v5 = nWidth;
              v2 = ptTerrainMap;
              if ( vX >= *v12 )
                vX = *v12;
              goto LABEL_24;
            }
            v10 = v58;
          }
        }
        vX = *v12;
        vMaxZ = *v12;
LABEL_24:
        if ( vMaxZ <= (double)*v60 )
          vMaxZ = *v60;
        if ( vX >= *v60 )
          vX = *v60;
        v24 = (float *)(nMipMapWidth + 4 * (iX1 + v57));
        if ( vMaxZ <= (double)*v24 )
          vMaxZ = *v24;
        if ( vX >= *v24 )
          vX = *v24;
        v25 = (float *)(nMipMapWidth + 4 * (v10 + iX1));
        if ( vMaxZ <= (double)*v25 )
          vMaxZ = *v25;
        if ( vX >= *v25 )
          vX = *v25;
        *(float *)((char *)&v2->tMinMaxHeightData.pptMinMaxHeightMipMap[iLevel]->vX + v67) = vX;
        *(float *)((char *)&v2->tMinMaxHeightData.pptMinMaxHeightMipMap[iLevel]->vY + v67) = vMaxZ;
        v26 = vMaxZ - vX;
        if ( v26 > vMaxDelta )
          vMaxDelta = v26;
        v9 = v70;
        ++v12;
        ++v60;
        v67 += 8;
        if ( v70 >= v5 )
        {
          pvHeightmap = (float *)nMipMapWidth;
          v7 = iY + 1;
          v3 = nHeight;
          break;
        }
      }
    }
    v57 += v5;
    v62 += 8 * v5;
    iY = v7;
    v64 += v5;
  }
  while ( v7 < v3 );
  v6 = iLevel;
LABEL_42:
  v2->avDeltaZ[v6] = vMaxDelta;
  v27 = v2->nWidth;
  v28 = v2->tMinMaxHeightData.nLevels - 2;
  iLevela = v28;
  if ( v28 >= 0 )
  {
    v68 = &v2->avDeltaZ[v28];
    do
    {
      pptMinMaxHeightMipMap = v2->tMinMaxHeightData.pptMinMaxHeightMipMap;
      v30 = (struct TerrainMap_t **)pptMinMaxHeightMipMap[v28 + 1];
      nHeighta = (int)pptMinMaxHeightMipMap[v28];
      v31 = 0;
      v32 = v27 >> 1;
      aptTerrainMapsa = v30;
      vMaxDeltaa = 0.0;
      iYa = 0;
      if ( v27 > 0 )
      {
        v61 = 0;
        v59 = (float *)v30;
        while ( 1 )
        {
          v33 = v31 + 1;
          if ( v31 + 1 >= v2->nHeight - 2 )
            v33 = v2->nHeight - 2;
          v34 = v27 * v33;
          v35 = 0;
          v36 = v32 * (v31 / 2);
          v37 = (float *)&aptTerrainMapsa[2 * v34];
          v63 = v37;
          v65 = v59;
          while ( 1 )
          {
            v38 = v35 + 1;
            if ( v35 + 1 >= ptTerrainMap->nWidth - 2 )
              v38 = ptTerrainMap->nWidth - 2;
            v39 = *v65;
            iTerrainMapa = v65[1];
            if ( iTerrainMapa <= (double)v37[1] )
              iTerrainMapa = v37[1];
            if ( v39 >= *v37 )
              v39 = *v37;
            v40 = (float *)(&aptTerrainMapsa[2 * v38] + 2 * v61);
            if ( iTerrainMapa <= (double)v40[1] )
              iTerrainMapa = v40[1];
            if ( v39 >= *v40 )
              v39 = *v40;
            v41 = v34 + v38;
            v42 = iTerrainMapa < (double)*(float *)&aptTerrainMapsa[2 * v41 + 1];
            v43 = iTerrainMapa == *(float *)&aptTerrainMapsa[2 * v41 + 1];
            v44 = (float *)&aptTerrainMapsa[2 * v41];
            if ( v42 || v43 )
              iTerrainMapa = v44[1];
            if ( v39 >= *v44 )
              v39 = *v44;
            v45 = v36 + v35 / 2;
            *(float *)(nHeighta + 8 * v45) = v39;
            *(float *)(nHeighta + 8 * v45 + 4) = iTerrainMapa;
            v46 = iTerrainMapa - v39;
            if ( v46 > vMaxDeltaa )
              vMaxDeltaa = v46;
            v35 += 2;
            v65 += 4;
            v63 += 4;
            if ( v35 >= v27 )
              break;
            v37 = v63;
          }
          v32 = v27 >> 1;
          v47 = iYa + 2 < v27;
          v61 += 2 * v27;
          v2 = ptTerrainMap;
          iYa += 2;
          v59 += 4 * v27;
          if ( !v47 )
            break;
          v31 = iYa;
        }
        v28 = iLevela;
      }
      --v28;
      *v68 = vMaxDeltaa;
      v27 = v32;
      iLevela = v28;
      --v68;
    }
    while ( v28 >= 0 );
  }
  TerrainMap_isMipMapsUpdated = 1;
}

// source: h/2/terrain.c:779  [anchor-callee]
struct QTask_s *__cdecl Terrain_MakeMipMaps(struct QTask_s *ptQTask)
{
  unsigned __int16 v1; // dx
  int v2; // esi
  struct QTask_s *result; // eax
  int i; // esi
  struct TerrainMap_t *aptTerrainMaps[10]; // [esp+4h] [ebp-28h] BYREF

  v1 = TerrainMap_eQTaskType;
  v2 = 0;
  for ( result = QTask_GetFirstChildOfType(ptQTask, TerrainMap_eQTaskType);
        result;
        result = QTask_GetNextSiblingOfType(result, v1) )
  {
    aptTerrainMaps[v2++] = (struct TerrainMap_t *)result;
  }
  for ( i = v2 - 1; i >= 0; --i )
    TerrainMap_MakeMinMaxHeightMipMaps(aptTerrainMaps, i);
  return result;
}

// source: h/2/terrain.c:813  [anchor-mhash]
void __cdecl TerrainMap_ClipLineToTerrainMap(
        struct TerrainMap_t *ptTerrainMap,
        struct real32x3_t *ptLineStart,
        struct real32x3_t *ptLineEnd)
{
  #pragma pack(push, 1)
  union
  {
    struct { float vT; };
    struct { float vTa; };
    struct { char igi2_o2[4]; float vZ; };
    struct { char igi2_o3[4]; BOOL vZa; };
    struct { char igi2_o4[4]; BOOL vZb; };
    struct { char igi2_o5[8]; float v18; };
    struct { char igi2_o6[8]; float v19; };
    struct { char igi2_o7[12]; float v20; };
    struct { char igi2_o8[16]; float avX[2]; };
    struct { char igi2_o9[24]; float avY[2]; };
    struct { char igi2_o10[32]; float avInsideSign[2]; };
    char igi2_extent[40];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  double nHeight; // st7
  int i; // esi
  double v5; // st7
  double v6; // st7
  double v7; // st7
  float v8; // eax
  double v9; // st7
  double v10; // st7
  double v11; // st7
  float v12; // eax

  igi2_frame.avX[1] = (float)ptTerrainMap->nWidth;
  nHeight = (double)ptTerrainMap->nHeight;
  igi2_frame.avInsideSign[0] = 1.0;
  igi2_frame.avInsideSign[1] = -1.0;
  igi2_frame.avX[0] = 0.0;
  igi2_frame.avY[1] = nHeight;
  igi2_frame.avY[0] = 0.0;
  for ( i = 0; i < 2; ++i )
  {
    v5 = ptLineStart->vX - igi2_frame.avX[i];
    igi2_frame.v18 = v5;
    igi2_frame.vZa = ptLineEnd->vX - igi2_frame.avX[i] >= 0.0;
    if ( (double)igi2_frame.vZa + (double)igi2_frame.vZa - 1.0 != (double)(v5 >= 0.0) + (double)(v5 >= 0.0) - 1.0 )
    {
      v6 = (igi2_frame.avX[i] - ptLineStart->vX) / (ptLineEnd->vX - ptLineStart->vX);
      igi2_frame.vT = v6;
      if ( v6 > 0.0 && igi2_frame.vT < 1.0 )
      {
        v7 = (ptLineEnd->vY - ptLineStart->vY) * igi2_frame.vT + ptLineStart->vY;
        igi2_frame.vZ = (ptLineEnd->vZ - ptLineStart->vZ) * igi2_frame.vT + ptLineStart->vZ;
        v8 = igi2_frame.avX[i];
        if ( (double)(igi2_frame.v18 >= 0.0) + (double)(igi2_frame.v18 >= 0.0) - 1.0 == igi2_frame.avInsideSign[i] )
        {
          ptLineEnd->vX = v8;
          ptLineEnd->vY = v7;
          ptLineEnd->vZ = igi2_frame.vZ;
        }
        else
        {
          ptLineStart->vX = v8;
          ptLineStart->vY = v7;
          ptLineStart->vZ = igi2_frame.vZ;
        }
      }
    }
    v9 = ptLineStart->vY - igi2_frame.avY[i];
    igi2_frame.v20 = v9;
    igi2_frame.vZb = ptLineEnd->vY - igi2_frame.avY[i] >= 0.0;
    if ( (double)igi2_frame.vZb + (double)igi2_frame.vZb - 1.0 != (double)(v9 >= 0.0) + (double)(v9 >= 0.0) - 1.0 )
    {
      v10 = (igi2_frame.avY[i] - ptLineStart->vY) / (ptLineEnd->vY - ptLineStart->vY);
      igi2_frame.vTa = v10;
      if ( v10 > 0.0 && igi2_frame.vTa < 1.0 )
      {
        v11 = (ptLineEnd->vX - ptLineStart->vX) * igi2_frame.vTa + ptLineStart->vX;
        igi2_frame.v19 = (ptLineEnd->vZ - ptLineStart->vZ) * igi2_frame.vTa + ptLineStart->vZ;
        v12 = igi2_frame.avY[i];
        if ( (double)(igi2_frame.v20 >= 0.0) + (double)(igi2_frame.v20 >= 0.0) - 1.0 == igi2_frame.avInsideSign[i] )
        {
          ptLineEnd->vY = v12;
          ptLineEnd->vX = v11;
          ptLineEnd->vZ = igi2_frame.v19;
        }
        else
        {
          ptLineStart->vY = v12;
          ptLineStart->vX = v11;
          ptLineStart->vZ = igi2_frame.v19;
        }
      }
    }
  }
}

// source: h/2/terrain.c:921  [anchor-hash]
struct TerrainMaterial_t *__cdecl Terrain_GetMaterial(struct Terrain_t *ptTerrain, int iMaterial)
{
  unsigned __int16 v2; // dx
  struct TerrainMaterial_t *result; // eax

  v2 = TerrainMaterial_eQTaskType;
  result = (struct TerrainMaterial_t *)QTask_GetFirstChildOfType(
                                         &ptTerrain->tDynCubeObj.tQObj.tQTask,
                                         TerrainMaterial_eQTaskType);
  if ( !result )
    return nullptr;
  while ( result->iID != iMaterial )
  {
    result = (struct TerrainMaterial_t *)QTask_GetNextSiblingOfType(&result->tQTask, v2);
    if ( !result )
      return nullptr;
  }
  return result;
}

// source: h/2/terrain.c:949  [anchor-mhash]
float __cdecl Terrain_SampleBicubicPatch(float (*G)[4], float x, float y)
{
  #pragma pack(push, 1)
  union
  {
    struct { float C[4][4]; };
    struct { char igi2_o1[64]; float T[4][4]; };
    struct { char igi2_o2[128]; float M[4][4]; };
    char igi2_extent[192];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  float *v3; // edx
  float *v4; // ecx
  int v5; // edi
  float *v6; // eax
  int v7; // esi
  double v8; // st7
  float *v9; // edx
  float *v10; // ecx
  int v11; // esi
  int i; // eax
  double v13; // st7

  *(_QWORD *)&igi2_frame.M[0][0] = 0x3FC00000BF000000LL;
  *(_QWORD *)&igi2_frame.M[0][2] = 0x3F000000BFC00000LL;
  *(_QWORD *)&igi2_frame.M[1][0] = 0xC02000003F800000uLL;
  *(_QWORD *)&igi2_frame.M[1][2] = 0xBF00000040000000uLL;
  *(_QWORD *)&igi2_frame.M[2][0] = 3204448256LL;
  *(_QWORD *)&igi2_frame.M[2][2] = 1056964608;
  *(_QWORD *)&igi2_frame.M[3][0] = 0x3F80000000000000LL;
  *(_QWORD *)&igi2_frame.M[3][2] = 0;
  memset(igi2_frame.C, 0, sizeof(igi2_frame.C));
  memset(igi2_frame.T, 0, sizeof(igi2_frame.T));
  v3 = igi2_frame.T[0];
  v4 = &(*G)[2];
  v5 = 4;
  do
  {
    v6 = &igi2_frame.M[0][1];
    v7 = 4;
    do
    {
      v8 = v6[2];
      v6 += 4;
      ++v3;
      --v7;
      *(v3 - 1) = v8 * v4[1] + *(v6 - 5) * *(v4 - 2) + *(v6 - 3) * *v4 + *(v6 - 4) * *(v4 - 1) + *(v3 - 1);
    }
    while ( v7 );
    v4 += 4;
    --v5;
  }
  while ( v5 );
  v9 = igi2_frame.C[0];
  v10 = &igi2_frame.M[0][1];
  v11 = 4;
  do
  {
    for ( i = 0;
          i < 4;
          *(v9 - 1) = v13 * v10[2] + igi2_frame.T[1][i + 3] * v10[1] + igi2_frame.T[0][i + 3] * *v10 + igi2_frame.C[3][i + 3] * *(v10 - 1) + *(v9 - 1) )
    {
      v13 = igi2_frame.T[3][i++];
      ++v9;
    }
    v10 += 4;
    --v11;
  }
  while ( v11 );
  return (((((igi2_frame.C[0][0] * y + igi2_frame.C[0][1]) * y + igi2_frame.C[0][2]) * y + igi2_frame.C[0][3]) * x
         + ((igi2_frame.C[1][0] * y + igi2_frame.C[1][1]) * y + igi2_frame.C[1][2]) * y
         + igi2_frame.C[1][3])
        * x
        + ((igi2_frame.C[2][0] * y + igi2_frame.C[2][1]) * y + igi2_frame.C[2][2]) * y
        + igi2_frame.C[2][3])
       * x
       + ((igi2_frame.C[3][0] * y + igi2_frame.C[3][1]) * y + igi2_frame.C[3][2]) * y
       + igi2_frame.C[3][3];
}

// source: h/2/terrain.c:1009  [anchor-mhash]
unsigned __int8 __cdecl Terrain_SampleMaterial(
        struct Terrain_t *ptTerrain,
        struct TerrainMap_t *ptTerrainMap,
        float vInX,
        float vInY)
{
  unsigned __int16 v4; // di
  struct QTask_s *PrevSiblingOfType; // eax
  struct QTask_s *v6; // edx
  double v7; // st7
  double v8; // st6
  double v9; // st7
  double v10; // st7
  float vHMY; // [esp+4h] [ebp-20h]
  float vHMHalfY; // [esp+8h] [ebp-1Ch]
  float vHMX; // [esp+Ch] [ebp-18h]
  float vHMHalfX; // [esp+10h] [ebp-14h]
  float vOOScaleY; // [esp+14h] [ebp-10h]
  int nHeightmapWidth; // [esp+1Ch] [ebp-8h]

  v4 = TerrainMap_eQTaskType;
  if ( ptTerrainMap )
    PrevSiblingOfType = QTask_GetPrevSiblingOfType(&ptTerrainMap->tQTask, TerrainMap_eQTaskType);
  else
    PrevSiblingOfType = QTask_GetLastChildOfType(&ptTerrain->tDynCubeObj.tQObj.tQTask, TerrainMap_eQTaskType);
  v6 = PrevSiblingOfType;
  if ( !PrevSiblingOfType )
    return 0;
  while ( 1 )
  {
    if ( !v6[2].ptNext )
    {
      vHMX = *(double *)&v6[3].tQTaskChildren.ptTail - ptTerrain->tPos.vX;
      vHMY = *(double *)&v6[3].tQTaskRefList.ptMiddle - ptTerrain->tPos.vY;
      v7 = *(float *)&v6[4].tQTaskChildren.ptMiddle * 4096.0;
      v8 = *(float *)&v6[4].tQTaskChildren.ptTail * 4096.0;
      vHMHalfX = v7 * 0.5;
      vHMHalfY = 0.5 * v8;
      *(float *)&nHeightmapWidth = v7 / (double)(int)v6[2].tQTaskChildren.ptTail;
      vOOScaleY = v8 / (double)(int)v6[2].tQTaskRefList.ptMiddle;
      v9 = *(float *)&nHeightmapWidth * 0.5;
      if ( vHMX - vHMHalfX + v9 < vInX && vInX < vHMHalfX + vHMX - v9 )
      {
        v10 = vOOScaleY * 0.5;
        if ( vHMY - vHMHalfY + v10 < vInY && vInY < vHMHalfY + vHMY - v10 )
          break;
      }
    }
    v6 = QTask_GetPrevSiblingOfType(v6, v4);
    if ( !v6 )
      return 0;
  }
  return *((_BYTE *)&v6[9].tQTaskChildren.ptMiddle->ptNext
         + (__int64)((vInX - vHMX + vHMHalfX) * (1.0 / *(float *)&nHeightmapWidth))
         + (__int64)v6[2].tQTaskChildren.ptTail * (__int64)((vInY - vHMY + vHMHalfY) * (1.0 / vOOScaleY)));
}

// source: h/2/terrain.c:1075  [anchor-mhash]
float __cdecl Terrain_SampleHeightBicubic(
        struct Terrain_t *ptTerrain,
        struct TerrainMap_t *ptTerrainMap,
        float vInX,
        float vInY)
{
  #pragma pack(push, 1)
  union
  {
    struct { float vOOScaleX; };
    struct { float vOOScaleXa; };
    struct { char igi2_o2[8]; float vOOScaleY; };
    struct { char igi2_o3[8]; float vOOScaleYa; };
    struct { char igi2_o4[20]; float vHMHalfX; };
    struct { char igi2_o5[24]; float vHMX; };
    struct { char igi2_o6[28]; float vHMHalfY; };
    struct { char igi2_o7[32]; float vHMY; };
    struct { char igi2_o8[48]; int anX_8; };
    struct { char igi2_o9[52]; int anX_12; };
    struct { char igi2_o10[56]; int anY[4]; };
    struct { char igi2_o11[72]; float aavZ[4][4]; };
    char igi2_extent[136];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  unsigned __int16 v4; // di
  struct QTask_s *PrevSiblingOfType; // eax
  struct QTask_s *v7; // edx
  int ptTail; // ebx
  double v9; // st7
  double v10; // st6
  double v11; // st7
  double v12; // st7
  double v13; // st7
  double v14; // st6
  int v15; // edi
  int v16; // esi
  int v17; // eax
  struct QTask_s *ptNext; // edx
  int v19; // esi
  _DWORD *v20; // ecx
  int v21; // eax

  v4 = TerrainMap_eQTaskType;
  if ( ptTerrainMap )
    PrevSiblingOfType = QTask_GetPrevSiblingOfType(&ptTerrainMap->tQTask, TerrainMap_eQTaskType);
  else
    PrevSiblingOfType = QTask_GetLastChildOfType(&ptTerrain->tDynCubeObj.tQObj.tQTask, TerrainMap_eQTaskType);
  v7 = PrevSiblingOfType;
  if ( PrevSiblingOfType )
  {
    while ( 1 )
    {
      if ( !v7[2].ptNext )
      {
        ptTail = (int)v7[2].tQTaskChildren.ptTail;
        igi2_frame.vHMX = *(double *)&v7[3].tQTaskChildren.ptTail - ptTerrain->tPos.vX;
        igi2_frame.vHMY = *(double *)&v7[3].tQTaskRefList.ptMiddle - ptTerrain->tPos.vY;
        v9 = *(float *)&v7[4].tQTaskChildren.ptMiddle * 4096.0;
        v10 = *(float *)&v7[4].tQTaskChildren.ptTail * 4096.0;
        igi2_frame.vHMHalfX = v9 * 0.5;
        igi2_frame.vHMHalfY = 0.5 * v10;
        igi2_frame.vOOScaleX = v9 / (double)ptTail;
        igi2_frame.vOOScaleY = v10 / (double)(int)v7[2].tQTaskRefList.ptMiddle;
        v11 = igi2_frame.vOOScaleX * 0.5;
        if ( igi2_frame.vHMX - igi2_frame.vHMHalfX + v11 < vInX && vInX < igi2_frame.vHMHalfX + igi2_frame.vHMX - v11 )
        {
          v12 = igi2_frame.vOOScaleY * 0.5;
          if ( igi2_frame.vHMY - igi2_frame.vHMHalfY + v12 < vInY && vInY < igi2_frame.vHMHalfY + igi2_frame.vHMY - v12 )
            break;
        }
      }
      v7 = QTask_GetPrevSiblingOfType(v7, v4);
      if ( !v7 )
        return 0.0;
    }
    v13 = (vInX - igi2_frame.vHMX + igi2_frame.vHMHalfX) * (1.0 / igi2_frame.vOOScaleX) - 0.5;
    v14 = (vInY - igi2_frame.vHMY + igi2_frame.vHMHalfY) * (1.0 / igi2_frame.vOOScaleY) - 0.5;
    v15 = (__int64)v13;
    v16 = (__int64)v14;
    v17 = ptTail - 1;
    igi2_frame.anX_8 = v15 + 1;
    if ( v15 + 1 >= ptTail - 1 )
      igi2_frame.anX_8 = ptTail - 1;
    igi2_frame.anX_12 = v15 + 2;
    if ( v15 + 2 >= v17 )
      igi2_frame.anX_12 = ptTail - 1;
    igi2_frame.anY[1] = (__int64)v14;
    igi2_frame.anY[0] = (v16 - 1) & ((v16 - 1 < 0) - 1);
    igi2_frame.anY[2] = v16 + 1;
    if ( v16 + 1 >= v17 )
      igi2_frame.anY[2] = ptTail - 1;
    igi2_frame.anY[3] = v16 + 2;
    if ( v16 + 2 >= v17 )
      igi2_frame.anY[3] = ptTail - 1;
    ptNext = v7[7].ptNext;
    v19 = 0;
    v20 = &igi2_frame.aavZ[0][1];
    do
    {
      v21 = ptTail * igi2_frame.anY[v19];
      *(v20 - 1) = *((_DWORD *)&ptNext->ptNext + v21 + ((v15 - 1) & ((v15 - 1 < 0) - 1)));
      *v20 = *((_DWORD *)&ptNext->ptNext + v21 + v15);
      v20[1] = *((_DWORD *)&ptNext->ptNext + v21 + igi2_frame.anX_8);
      v20[2] = *((_DWORD *)&ptNext->ptNext + igi2_frame.anX_12 + v21);
      ++v19;
      v20 += 4;
    }
    while ( v19 < 4 );
    igi2_frame.vOOScaleYa = v13 - (double)(int)(__int64)v13;
    igi2_frame.vOOScaleXa = v14 - (double)(int)(__int64)v14;
    return Terrain_SampleBicubicPatch(igi2_frame.aavZ, igi2_frame.vOOScaleXa, igi2_frame.vOOScaleYa);
  }
  else
  {
    return 0.0;
  }
}

// source: h/2/terrain.c:1201  [anchor-callee]
float __cdecl Terrain_SampleHeightBilinear(
        struct Terrain_t *ptTerrain,
        struct TerrainMap_t *ptTerrainMap,
        float vInX,
        float vInY)
{
  unsigned __int16 v4; // bx
  struct QTask_s *PrevSiblingOfType; // eax
  struct QTask_s *v7; // edx
  unsigned int ptTail; // edi
  double v9; // st7
  double v10; // st6
  double v11; // st7
  double v12; // st7
  double v13; // st7
  unsigned int v14; // eax
  unsigned int v15; // esi
  struct QTask_s *ptNext; // edx
  double v17; // st7
  double v18; // st6
  float vHMX; // [esp+Ch] [ebp-24h]
  float vHMHalfX; // [esp+10h] [ebp-20h]
  float vHMY; // [esp+14h] [ebp-1Ch]
  float vHMHalfY; // [esp+18h] [ebp-18h]
  float vOOScaleX; // [esp+1Ch] [ebp-14h]
  float vOOScaleY; // [esp+2Ch] [ebp-4h]
  float vOOScaleYa; // [esp+2Ch] [ebp-4h]

  v4 = TerrainMap_eQTaskType;
  if ( ptTerrainMap )
    PrevSiblingOfType = QTask_GetPrevSiblingOfType(&ptTerrainMap->tQTask, TerrainMap_eQTaskType);
  else
    PrevSiblingOfType = QTask_GetLastChildOfType(&ptTerrain->tDynCubeObj.tQObj.tQTask, TerrainMap_eQTaskType);
  v7 = PrevSiblingOfType;
  if ( PrevSiblingOfType )
  {
    while ( 1 )
    {
      if ( !v7[2].ptNext )
      {
        ptTail = (unsigned int)v7[2].tQTaskChildren.ptTail;
        vHMX = *(double *)&v7[3].tQTaskChildren.ptTail - ptTerrain->tPos.vX;
        vHMY = *(double *)&v7[3].tQTaskRefList.ptMiddle - ptTerrain->tPos.vY;
        v9 = *(float *)&v7[4].tQTaskChildren.ptMiddle * 4096.0;
        v10 = *(float *)&v7[4].tQTaskChildren.ptTail * 4096.0;
        vHMHalfX = v9 * 0.5;
        vHMHalfY = 0.5 * v10;
        vOOScaleX = v9 / (double)ptTail;
        vOOScaleY = v10 / (double)(unsigned int)v7[2].tQTaskRefList.ptMiddle;
        v11 = vOOScaleX * 0.5;
        if ( vHMX - vHMHalfX + v11 <= vInX && vInX <= vHMHalfX + vHMX - v11 )
        {
          v12 = vOOScaleY * 0.5;
          if ( vHMY - vHMHalfY + v12 <= vInY && vInY <= vHMHalfY + vHMY - v12 )
            break;
        }
      }
      v7 = QTask_GetPrevSiblingOfType(v7, v4);
      if ( !v7 )
        return 0.0;
    }
    v13 = (vInX - vHMX + vHMHalfX) * (1.0 / vOOScaleX) - 0.5;
    vOOScaleYa = (vInY - vHMY + vHMHalfY) * (1.0 / vOOScaleY) - 0.5;
    v14 = (__int64)v13;
    v15 = (__int64)vOOScaleYa;
    ptNext = v7[7].ptNext;
    v17 = v13 - (double)v14;
    v18 = *((float *)&ptNext->ptNext + ptTail * v15 + v14)
        + (*((float *)&ptNext->ptPrev + ptTail * v15 + v14) - *((float *)&ptNext->ptNext + ptTail * v15 + v14)) * v17;
    return ((*((float *)&ptNext->ptPrev + ptTail * (v15 + 1) + v14)
           - *((float *)&ptNext->ptNext + ptTail * (v15 + 1) + v14))
          * v17
          + *((float *)&ptNext->ptNext + ptTail * (v15 + 1) + v14)
          - v18)
         * (vOOScaleYa - (double)v15)
         + v18;
  }
  else
  {
    return 0.0;
  }
}

// source: h/2/terrain.c:1292  [anchor-callee]
void __cdecl TerrainMap_SoftenHeightmapEdges(
        struct Terrain_t *ptTerrain,
        struct TerrainMap_t *ptTerrainMap,
        float vEdgeSize)
{
  int nWidth; // eax
  int v4; // ebx
  double v5; // st5
  float *v6; // edi
  float v7; // [esp+0h] [ebp-28h]
  float v8; // [esp+4h] [ebp-24h]
  float v9; // [esp+14h] [ebp-14h]
  int v10; // [esp+18h] [ebp-10h]
  float v11; // [esp+18h] [ebp-10h]
  int i; // [esp+1Ch] [ebp-Ch]
  float v13; // [esp+1Ch] [ebp-Ch]
  int v14; // [esp+20h] [ebp-8h]
  float v15; // [esp+24h] [ebp-4h]

  if ( QTask_GetPrevSiblingOfType(&ptTerrainMap->tQTask, TerrainMap_eQTaskType) )
  {
    v14 = 0;
    if ( ptTerrainMap->nHeight > 0 )
    {
      nWidth = ptTerrainMap->nWidth;
      v10 = nWidth;
      do
      {
        v4 = 0;
        for ( i = 0; v4 < nWidth; v10 = nWidth )
        {
          v13 = ((double)i + 0.5) / (double)v10;
          v15 = (double)v14 + 0.5;
          v11 = v15 / (double)ptTerrainMap->nHeight;
          switch ( (v13 - v11 > 0.0) | (2 * (v11 + v13 > 1.0)) )
          {
            case 0:
              v5 = v13;
              goto LABEL_10;
            case 1:
              v5 = v11;
              goto LABEL_10;
            case 2:
              v5 = 1.0 - v11;
              goto LABEL_10;
            case 3:
              v5 = 1.0 - v13;
LABEL_10:
              v9 = v5 / vEdgeSize;
              if ( v9 >= 0.0 )
              {
                if ( v9 > 1.0 )
                  v9 = 1.0;
              }
              else
              {
                v9 = 0.0;
              }
              break;
            default:
              break;
          }
          v8 = ptTerrainMap->tPos.vY
             - ptTerrainMap->vWorldHeight * 2048.0
             + v11 * ptTerrainMap->vWorldHeight * 4096.0
             - ptTerrain->tPos.vY;
          v6 = &ptTerrainMap->pvHeightmap[v4 + v14 * nWidth];
          v7 = ptTerrainMap->tPos.vX
             - ptTerrainMap->vWorldWidth * 2048.0
             + v13 * ptTerrainMap->vWorldWidth * 4096.0
             - ptTerrain->tPos.vX;
          i = ++v4;
          *v6 = Terrain_SampleHeightBilinear(ptTerrain, ptTerrainMap, v7, v8) * (1.0 - v9) + v9 * *v6;
          nWidth = ptTerrainMap->nWidth;
        }
        ++v14;
      }
      while ( v14 < ptTerrainMap->nHeight );
    }
  }
}

// source: h/2/terrain.c:1368  [anchor-mhash]
struct real32x3_t *__cdecl Terrain_SampleColor(
        struct real32x3_t *retstr,
        struct Terrain_t *ptTerrain,
        struct TerrainMap_t *ptTerrainMap,
        float vInX,
        float vInY)
{
  #pragma pack(push, 1)
  union
  {
    struct { float vHMX; };
    struct { float vHMXa; };
    struct { char igi2_o2[4]; float vHMHalfX; };
    struct { char igi2_o3[8]; float vHMY; };
    struct { char igi2_o4[12]; float vHMHalfY; };
    struct { char igi2_o5[16]; float vOOScaleX; };
    struct { char igi2_o6[16]; unsigned int vOOScaleXa; };
    struct { char igi2_o7[20]; float vOOScaleY; };
    struct { char igi2_o8[20]; float vOOScaleYa; };
    struct { char igi2_o9[28]; float v49; };
    struct { char igi2_o10[36]; struct real32x3_t tColor; };
    struct { char igi2_o11[48]; struct real32x3_t tTempColor1; };
    struct { char igi2_o12[60]; struct real32x3_t atColor[4]; };
    char igi2_extent[108];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  unsigned __int16 v5; // bx
  struct QTask_s *PrevSiblingOfType; // eax
  struct QTask_s *v8; // edx
  unsigned int ptTail; // edi
  double v10; // st7
  double v11; // st6
  double v12; // st7
  double v13; // st7
  double v14; // st7
  double v15; // st6
  unsigned int v16; // eax
  unsigned int v17; // ecx
  double v18; // st5
  struct QReference_s *ptHead; // edx
  int v20; // ecx
  double v21; // st7
  char *v22; // esi
  int v23; // ebx
  double v24; // st6
  double v25; // st4
  int v26; // ecx
  int v27; // esi
  char *v28; // ecx
  double v29; // st4
  double v30; // st3
  int v31; // ecx
  unsigned int v32; // esi
  int v33; // edi
  char *v34; // esi
  int v35; // eax
  int v36; // ecx
  char *v37; // eax
  double v38; // st6

  v5 = TerrainMap_eQTaskType;
  memset(&igi2_frame.tColor, 0, sizeof(igi2_frame.tColor));
  if ( ptTerrainMap )
    PrevSiblingOfType = QTask_GetPrevSiblingOfType(&ptTerrainMap->tQTask, TerrainMap_eQTaskType);
  else
    PrevSiblingOfType = QTask_GetLastChildOfType(&ptTerrain->tDynCubeObj.tQObj.tQTask, TerrainMap_eQTaskType);
  v8 = PrevSiblingOfType;
  if ( PrevSiblingOfType )
  {
    while ( 1 )
    {
      ptTail = (unsigned int)v8[2].tQTaskChildren.ptTail;
      igi2_frame.vHMX = *(double *)&v8[3].tQTaskChildren.ptTail - ptTerrain->tPos.vX;
      igi2_frame.vHMY = *(double *)&v8[3].tQTaskRefList.ptMiddle - ptTerrain->tPos.vY;
      v10 = *(float *)&v8[4].tQTaskChildren.ptMiddle * 4096.0;
      v11 = *(float *)&v8[4].tQTaskChildren.ptTail * 4096.0;
      igi2_frame.vHMHalfX = v10 * 0.5;
      igi2_frame.vHMHalfY = 0.5 * v11;
      igi2_frame.vOOScaleX = v10 / (double)ptTail;
      igi2_frame.vOOScaleY = v11 / (double)(unsigned int)v8[2].tQTaskRefList.ptMiddle;
      v12 = igi2_frame.vOOScaleX * 0.5;
      if ( igi2_frame.vHMX - igi2_frame.vHMHalfX + v12 < vInX && vInX < igi2_frame.vHMHalfX + igi2_frame.vHMX - v12 )
      {
        v13 = igi2_frame.vOOScaleY * 0.5;
        if ( igi2_frame.vHMY - igi2_frame.vHMHalfY + v13 < vInY && vInY < igi2_frame.vHMHalfY + igi2_frame.vHMY - v13 )
          break;
      }
      v8 = QTask_GetPrevSiblingOfType(v8, v5);
      if ( !v8 )
        goto LABEL_10;
    }
    v14 = (vInX - igi2_frame.vHMX + igi2_frame.vHMHalfX) * (1.0 / igi2_frame.vOOScaleX) - 0.5;
    v15 = (vInY - igi2_frame.vHMY + igi2_frame.vHMHalfY) * (1.0 / igi2_frame.vOOScaleY) - 0.5;
    v16 = (__int64)v14;
    v17 = (__int64)v15;
    igi2_frame.vOOScaleXa = v17 + 1;
    igi2_frame.vHMXa = v14 - (double)v16;
    v18 = (double)v17;
    ptHead = v8[9].tQTaskRefList.ptHead;
    v20 = ptTail * v17;
    v21 = v15 - v18;
    v22 = (char *)ptHead + 4 * v20 + 4 * v16;
    v23 = (unsigned __int8)v22[1];
    v24 = (double)(unsigned __int8)v22[2] * 0.003921568859368563;
    v25 = (double)(unsigned __int8)*(_DWORD *)v22;
    v26 = v20 + v16 + 1;
    v27 = *((unsigned __int8 *)&ptHead->ptNext + 4 * v26 + 2);
    v28 = (char *)ptHead + 4 * v26;
    igi2_frame.atColor[0].vZ = v25 * 0.003921568859368563;
    v29 = (double)v27 * 0.003921568859368563;
    igi2_frame.atColor[1].vY = (double)(unsigned __int8)v28[1] * 0.003921568859368563;
    v30 = (double)(unsigned __int8)*(_DWORD *)v28;
    v31 = ptTail * igi2_frame.vOOScaleXa;
    igi2_frame.atColor[1].vZ = v30 * 0.003921568859368563;
    v32 = ptTail * igi2_frame.vOOScaleXa + v16;
    v33 = *((unsigned __int8 *)&ptHead->ptNext + 4 * v32 + 2);
    v34 = (char *)ptHead + 4 * v32;
    igi2_frame.atColor[2].vX = (double)v33 * 0.003921568859368563;
    igi2_frame.atColor[2].vY = (double)(unsigned __int8)v34[1] * 0.003921568859368563;
    v35 = v31 + v16 + 1;
    v36 = *((unsigned __int8 *)&ptHead->ptNext + 4 * v35 + 2);
    v37 = (char *)ptHead + 4 * v35;
    igi2_frame.atColor[2].vZ = (double)(unsigned __int8)*(_DWORD *)v34 * 0.003921568859368563;
    igi2_frame.atColor[3].vX = (double)v36 * 0.003921568859368563;
    igi2_frame.atColor[3].vY = (double)(unsigned __int8)v37[1] * 0.003921568859368563;
    igi2_frame.atColor[3].vZ = (double)(unsigned __int8)*(_DWORD *)v37 * 0.003921568859368563;
    igi2_frame.vOOScaleYa = (v29 - v24) * igi2_frame.vHMXa + v24;
    v38 = (igi2_frame.atColor[1].vY - (double)v23 * 0.003921568859368563) * igi2_frame.vHMXa + (double)v23 * 0.003921568859368563;
    igi2_frame.v49 = (igi2_frame.atColor[1].vZ - igi2_frame.atColor[0].vZ) * igi2_frame.vHMXa + igi2_frame.atColor[0].vZ;
    igi2_frame.tTempColor1.vY = (igi2_frame.atColor[3].vY - igi2_frame.atColor[2].vY) * igi2_frame.vHMXa + igi2_frame.atColor[2].vY;
    igi2_frame.tTempColor1.vZ = (igi2_frame.atColor[3].vZ - igi2_frame.atColor[2].vZ) * igi2_frame.vHMXa + igi2_frame.atColor[2].vZ;
    igi2_frame.tColor.vX = ((igi2_frame.atColor[3].vX - igi2_frame.atColor[2].vX) * igi2_frame.vHMXa + igi2_frame.atColor[2].vX - igi2_frame.vOOScaleYa) * v21 + igi2_frame.vOOScaleYa;
    igi2_frame.tColor.vY = (igi2_frame.tTempColor1.vY - v38) * v21 + v38;
    igi2_frame.tColor.vZ = (igi2_frame.tTempColor1.vZ - igi2_frame.v49) * v21 + igi2_frame.v49;
  }
LABEL_10:
  *retstr = igi2_frame.tColor;
  return retstr;
}

// source: h/2/terrain.c:1460  [anchor-callee]
void __cdecl TerrainMap_SoftenLightmapEdges(
        struct Terrain_t *ptTerrain,
        struct TerrainMap_t *ptTerrainMap,
        float vEdgeSize)
{
  #pragma pack(push, 1)
  union
  {
    struct { float vInX; };
    struct { char igi2_o1[4]; float vInY; };
    struct { char igi2_o2[16]; float v10; };
    struct { char igi2_o3[20]; int v11; };
    struct { char igi2_o4[20]; float v12; };
    struct { char igi2_o5[24]; int i; };
    struct { char igi2_o6[24]; float v14; };
    struct { char igi2_o7[36]; int v15; };
    struct { char igi2_o8[40]; float v16; };
    struct { char igi2_o9[56]; float v17; };
    struct { char igi2_o10[64]; float v18; };
    struct { char igi2_o11[64]; float v19; };
    struct { char igi2_o12[68]; struct real32x3_t v20; };
    char igi2_extent[80];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int nWidth; // eax
  int v4; // edi
  int v5; // ebp
  double v6; // st5
  unsigned int *v7; // eax
  struct real32x3_t v21; // 0:^3C.12

  if ( QTask_GetPrevSiblingOfType(&ptTerrainMap->tQTask, TerrainMap_eQTaskType) )
  {
    igi2_frame.v15 = 0;
    if ( ptTerrainMap->nHeight > 0 )
    {
      nWidth = ptTerrainMap->nWidth;
      igi2_frame.v11 = nWidth;
      do
      {
        v4 = 0;
        for ( igi2_frame.i = 0; v4 < nWidth; igi2_frame.v11 = nWidth )
        {
          v5 = v4 + igi2_frame.v15 * nWidth;
          igi2_frame.v14 = ((double)igi2_frame.i + 0.5) / (double)igi2_frame.v11;
          igi2_frame.v16 = (double)igi2_frame.v15 + 0.5;
          igi2_frame.v12 = igi2_frame.v16 / (double)ptTerrainMap->nHeight;
          switch ( (igi2_frame.v14 - igi2_frame.v12 > 0.0) | (2 * (igi2_frame.v12 + igi2_frame.v14 > 1.0)) )
          {
            case 0:
              v6 = igi2_frame.v14;
              goto LABEL_10;
            case 1:
              v6 = igi2_frame.v12;
              goto LABEL_10;
            case 2:
              v6 = 1.0 - igi2_frame.v12;
              goto LABEL_10;
            case 3:
              v6 = 1.0 - igi2_frame.v14;
LABEL_10:
              igi2_frame.v10 = v6 / vEdgeSize;
              if ( igi2_frame.v10 >= 0.0 )
              {
                if ( igi2_frame.v10 > 1.0 )
                  igi2_frame.v10 = 1.0;
              }
              else
              {
                igi2_frame.v10 = 0.0;
              }
              break;
            default:
              break;
          }
          igi2_frame.vInY = ptTerrainMap->tPos.vY
               - ptTerrainMap->vWorldHeight * 2048.0
               + igi2_frame.v12 * ptTerrainMap->vWorldHeight * 4096.0
               - ptTerrain->tPos.vY;
          igi2_frame.vInX = ptTerrainMap->tPos.vX
               - ptTerrainMap->vWorldWidth * 2048.0
               + igi2_frame.v14 * ptTerrainMap->vWorldWidth * 4096.0
               - ptTerrain->tPos.vX;
          v21 = *Terrain_SampleColor(&igi2_frame.v20, ptTerrain, ptTerrainMap, igi2_frame.vInX, igi2_frame.vInY);
          v7 = &ptTerrainMap->pbLightmap[v5];
          igi2_frame.v18 = (double)(unsigned __int8)*v7 * 0.003921568859368563;
          igi2_frame.v17 = ((double)*((unsigned __int8 *)v7 + 2) * 0.003921568859368563 - v21.vX) * igi2_frame.v10 + v21.vX;
          igi2_frame.v19 = (igi2_frame.v18 - v21.vZ) * igi2_frame.v10 + v21.vZ;
          *v7 = (__int64)(igi2_frame.v19 * 255.0)
              | (((unsigned int)(__int64)(255.0
                                        * (((double)*((unsigned __int8 *)v7 + 1) * 0.003921568859368563 - v21.vY) * igi2_frame.v10 + v21.vY))
                | (((unsigned __int8)(__int64)(igi2_frame.v17 * 255.0) | 0xFFFFFF00) << 8)) << 8);
          nWidth = ptTerrainMap->nWidth;
          igi2_frame.i = ++v4;
        }
        ++igi2_frame.v15;
      }
      while ( igi2_frame.v15 < ptTerrainMap->nHeight );
    }
    Texture_Download(
      &ptTerrainMap->tLightmapTexInfo,
      nullptr,
      4 * ptTerrainMap->nWidth,
      ptTerrainMap->nWidth,
      ptTerrainMap->nHeight,
      3,
      ptTerrainMap->pbLightmap);
  }
}

// source: h/2/terrain.c:1544  [anchor-mhash]
int __cdecl Terrain_LineVSTriangle(
        struct real32x3_t *ptOutPos,
        struct real32x3_t *ptStart,
        struct real32x3_t *ptEnd,
        struct real32x3_t *ptVertex0,
        struct real32x3_t *ptVertex1,
        struct real32x3_t *ptVertex2)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct real32x3_t tPos; };
    struct { char igi2_o1[12]; struct real32x3_t tNormal; };
    struct { char igi2_o2[24]; struct real32x3_t tEdge1; };
    struct { char igi2_o3[36]; struct real32x3_t tEdge0; };
    struct { char igi2_o4[48]; struct real32x3_t tDelta; };
    struct { char igi2_o5[60]; struct real32x3_t tRelativePos; };
    char igi2_extent[72];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  double v6; // st7
  long double v7; // st7
  double v8; // st7
  int result; // eax

  igi2_frame.tEdge0.vX = ptVertex1->vX - ptVertex0->vX;
  igi2_frame.tEdge0.vY = ptVertex1->vY - ptVertex0->vY;
  igi2_frame.tEdge0.vZ = ptVertex1->vZ - ptVertex0->vZ;
  igi2_frame.tEdge1.vX = ptVertex2->vX - ptVertex0->vX;
  igi2_frame.tEdge1.vY = ptVertex2->vY - ptVertex0->vY;
  v6 = ptVertex2->vZ - ptVertex0->vZ;
  igi2_frame.tEdge1.vZ = v6;
  igi2_frame.tPos.vX = v6 * igi2_frame.tEdge0.vY - igi2_frame.tEdge1.vY * igi2_frame.tEdge0.vZ;
  igi2_frame.tPos.vY = -(igi2_frame.tEdge1.vZ * igi2_frame.tEdge0.vX - igi2_frame.tEdge1.vX * igi2_frame.tEdge0.vZ);
  igi2_frame.tPos.vZ = igi2_frame.tEdge1.vY * igi2_frame.tEdge0.vX - igi2_frame.tEdge1.vX * igi2_frame.tEdge0.vY;
  igi2_frame.tNormal = igi2_frame.tPos;
  if ( igi2_frame.tPos.vX != 0.0 || igi2_frame.tPos.vY != 0.0 || igi2_frame.tPos.vZ != 0.0 )
  {
    v7 = 1.0 / sqrt(igi2_frame.tPos.vX * igi2_frame.tPos.vX + igi2_frame.tPos.vY * igi2_frame.tPos.vY + igi2_frame.tPos.vZ * igi2_frame.tPos.vZ);
    igi2_frame.tNormal.vX = igi2_frame.tPos.vX * v7;
    igi2_frame.tNormal.vY = igi2_frame.tNormal.vY * v7;
    igi2_frame.tNormal.vZ = igi2_frame.tNormal.vZ * v7;
  }
  igi2_frame.tDelta.vX = ptEnd->vX - ptStart->vX;
  igi2_frame.tDelta.vY = ptEnd->vY - ptStart->vY;
  igi2_frame.tDelta.vZ = ptEnd->vZ - ptStart->vZ;
  igi2_frame.tRelativePos.vX = ptStart->vX - ptVertex0->vX;
  igi2_frame.tRelativePos.vY = ptStart->vY - ptVertex0->vY;
  igi2_frame.tRelativePos.vZ = ptStart->vZ - ptVertex0->vZ;
  result = false;
  if ( Real32x3_ProjectPointToPlane(&igi2_frame.tPos, &igi2_frame.tRelativePos, &igi2_frame.tDelta, &igi2_frame.tNormal) )
  {
    ptOutPos->vX = igi2_frame.tPos.vX + ptVertex0->vX;
    ptOutPos->vY = igi2_frame.tPos.vY + ptVertex0->vY;
    v8 = igi2_frame.tPos.vZ + ptVertex0->vZ;
    ptOutPos->vZ = v8;
    if ( ptOutPos->vX > (double)ptStart->vX != ptOutPos->vX >= (double)ptEnd->vX
      && ptOutPos->vY > (double)ptStart->vY != ptOutPos->vY >= (double)ptEnd->vY
      && v8 > ptStart->vZ != v8 >= ptEnd->vZ
      && Real32x3_PointOnTriangle(nullptr, nullptr, &igi2_frame.tPos, &igi2_frame.tEdge0, &igi2_frame.tEdge1, &igi2_frame.tNormal) )
    {
      return true;
    }
  }
  return result;
}

// source: h/2/terrain.c:1590  [anchor-mhash]
// local variable allocation has failed, the output may be wrong!
void __cdecl Terrain_ApplyBrush(
        struct Terrain_t *ptTerrain,
        enum TerrainHeightEditMode_e eHeightEditMode,
        enum TerrainMaterialEditMode_e eMaterialEditMode,
        struct real64x3_t tPos,
        float vBrushRadius,
        float vBrushScale,
        float vPower)
{
  struct Terrain_t *v7; // ebp
  struct QTask_s *FirstChildOfType; // esi
  double v9; // st7
  enum TerrainHeightEditMode_e v10; // ecx
  double v11; // st6
  double v12; // st6
  double v13; // st5
  double v14; // st5
  double v15; // st6
  double v16; // st6
  double v17; // st6
  double v18; // st5
  double v19; // st5
  int v20; // ebx
  int v21; // edx
  int v22; // edi
  double v23; // st6
  double v24; // st5
  long double v25; // st7
  float *v26; // eax
  float *v27; // eax
  struct QTask_s *v28; // eax
  struct QTask_s *ptNext; // ecx
  int v30; // edx
  double v31; // st6
  float *v32; // eax
  struct QTask_s *v33; // eax
  struct QTask_s *v34; // ecx
  float v35; // ecx
  double vFlattenPos; // st6
  float v37; // [esp+10h] [ebp-A4h]
  float ptMiddle; // [esp+14h] [ebp-A0h]
  int v39; // [esp+14h] [ebp-A0h]
  float v40; // [esp+18h] [ebp-9Ch]
  float v41; // [esp+18h] [ebp-9Ch]
  float v42; // [esp+1Ch] [ebp-98h]
  float v43; // [esp+1Ch] [ebp-98h]
  float v44; // [esp+20h] [ebp-94h]
  float v45; // [esp+20h] [ebp-94h]
  float v46; // [esp+24h] [ebp-90h]
  float v47; // [esp+28h] [ebp-8Ch]
  float ptTail; // [esp+30h] [ebp-84h]
  int v49; // [esp+30h] [ebp-84h]
  int v50; // [esp+34h] [ebp-80h]
  char *v51; // [esp+34h] [ebp-80h]
  double v52; // [esp+38h] [ebp-7Ch]
  double v53; // [esp+38h] [ebp-7Ch]
  float *v54; // [esp+38h] [ebp-7Ch]
  float v55; // [esp+40h] [ebp-74h]
  float v56; // [esp+44h] [ebp-70h]
  double v57; // [esp+48h] [ebp-6Ch]
  float v58; // [esp+54h] [ebp-60h]
  int v59; // [esp+58h] [ebp-5Ch]
  float v60; // [esp+64h] [ebp-50h]
  double v61; // [esp+68h] [ebp-4Ch]
  double v62; // [esp+68h] [ebp-4Ch]
  float v63; // [esp+74h] [ebp-40h]
  int v64; // [esp+78h] [ebp-3Ch]
  float v65; // [esp+84h] [ebp-30h]
  float v66; // [esp+90h] [ebp-24h]

  v7 = ptTerrain;
  FirstChildOfType = QTask_GetFirstChildOfType(&ptTerrain->tDynCubeObj.tQObj.tQTask, TerrainMap_eQTaskType);
  if ( FirstChildOfType )
  {
    v9 = *(double *)((char *)&tPos.vZ + 4);
    while ( 1 )
    {
      v10 = eHeightEditMode;
      v58 = *(float *)&FirstChildOfType[4].tQTaskChildren.ptMiddle * 2048.0;
      v60 = *(float *)&FirstChildOfType[4].tQTaskChildren.ptTail * 2048.0;
      ptTail = (float)(int)FirstChildOfType[2].tQTaskChildren.ptTail;
      v55 = ptTail / (v58 + v58);
      ptMiddle = (float)(int)FirstChildOfType[2].tQTaskRefList.ptMiddle;
      v56 = ptMiddle / (v60 + v60);
      v46 = (*(double *)((char *)&tPos.vY + 4) - *(double *)&FirstChildOfType[3].tQTaskChildren.ptTail + v58) * v55
          - 0.5;
      v47 = (v9 - *(double *)&FirstChildOfType[3].tQTaskRefList.ptMiddle + v60) * v56 - 0.5;
      v11 = (v7->tFlattenPos.vX - *(double *)&FirstChildOfType[3].tQTaskChildren.ptTail + v58) * v55 - 0.5;
      v66 = (v7->tFlattenPos.vY - *(double *)&FirstChildOfType[3].tQTaskRefList.ptMiddle + v60) * v56 - 0.5;
      if ( eHeightEditMode == TERRAIN_HEIGHTEDITMODE_FLATTENLINE )
      {
        v40 = v46 >= v11
            ? v11
            : (*(double *)((char *)&tPos.vY + 4) - *(double *)&FirstChildOfType[3].tQTaskChildren.ptTail + v58) * v55
            - 0.5;
        v42 = v46 <= v11
            ? v11
            : (*(double *)((char *)&tPos.vY + 4) - *(double *)&FirstChildOfType[3].tQTaskChildren.ptTail + v58) * v55
            - 0.5;
        v44 = v47 >= (double)v66
            ? (v7->tFlattenPos.vY - *(double *)&FirstChildOfType[3].tQTaskRefList.ptMiddle + v60) * v56 - 0.5
            : (v9 - *(double *)&FirstChildOfType[3].tQTaskRefList.ptMiddle + v60) * v56 - 0.5;
        v12 = v47 <= (double)v66 ? v66 : v47;
        v13 = v55 * *(float *)&tPos.vX;
        v41 = v40 - v13;
        v43 = v13 + v42;
        v14 = v56 * *(float *)&tPos.vX;
        v45 = v44 - v14;
        v15 = v12 + v14;
      }
      else
      {
        v16 = v55 * *(float *)&tPos.vX;
        v41 = v46 - v16;
        v43 = v16 + v46;
        v17 = v56 * *(float *)&tPos.vX;
        v45 = v47 - v17;
        v15 = v17 + v47;
      }
      if ( v46 >= 0.0 )
      {
        v18 = ptTail - 0.5;
        if ( v18 < v46 )
          v46 = v18;
      }
      else
      {
        v46 = 0.0;
      }
      if ( v47 >= 0.0 )
      {
        v19 = ptMiddle - 0.5;
        if ( v19 < v47 )
          v47 = v19;
      }
      else
      {
        v47 = 0.0;
      }
      if ( v41 < 0.0 )
        v41 = 0.0;
      if ( v45 < 0.0 )
        v45 = 0.0;
      if ( v43 > (double)ptTail )
        v43 = (float)(int)FirstChildOfType[2].tQTaskChildren.ptTail;
      if ( v15 > ptMiddle )
        v15 = ptMiddle;
      if ( v43 > (double)v41 && v15 > v45 )
        break;
LABEL_71:
      FirstChildOfType = QTask_GetNextSiblingOfType(FirstChildOfType, TerrainMap_eQTaskType);
      if ( !FirstChildOfType )
        goto LABEL_72;
    }
    v20 = (__int64)v45;
    v59 = (__int64)v43;
    v21 = (__int64)v15;
    v64 = v21;
    v22 = (__int64)v41;
    v50 = v22;
    if ( v22 >= v59 )
      goto LABEL_69;
LABEL_37:
    v39 = v20;
    if ( v20 >= v21 )
      goto LABEL_68;
    v65 = ((double)v50 + 0.5) / v55;
    while ( 1 )
    {
      v61 = *(double *)&FirstChildOfType[3].tQTaskChildren.ptTail - v58 + v65;
      v63 = 1.0 / v56;
      v52 = ((double)v39 + 0.5) * v63 + *(double *)&FirstChildOfType[3].tQTaskRefList.ptMiddle - v60;
      if ( v10 != TERRAIN_HEIGHTEDITMODE_FLATTENLINE )
      {
        v25 = sqrt(
                (v61 - *(double *)((char *)&tPos.vY + 4)) * (v61 - *(double *)((char *)&tPos.vY + 4))
              + (v52 - v9) * (v52 - v9))
            / *(float *)&tPos.vX;
        if ( v25 >= 1.0 )
          v25 = 1.0;
        v10 = eHeightEditMode;
        v37 = pow((cos(v25 * 3.1415927410125732) + 1.0) * 0.5, *(float *)&tPos.vY);
        v9 = *(double *)((char *)&tPos.vZ + 4);
        goto LABEL_51;
      }
      v23 = v7->tFlattenPos.vX - *(double *)((char *)&tPos.vY + 4);
      v24 = v7->tFlattenPos.vY - v9;
      v53 = v52 - v9;
      v62 = v61 - *(double *)((char *)&tPos.vY + 4);
      v57 = (v62 * v23 + v53 * v24) / (v24 * v24 + v23 * v23);
      if ( v57 <= 1.0 )
      {
        if ( v57 >= 0.0 )
          goto LABEL_45;
        HIDWORD(v57) = 0;
      }
      else
      {
        HIDWORD(v57) = 1072693248;
      }
      LODWORD(v57) = 0;
LABEL_45:
      if ( sqrt((v62 - v57 * v23) * (v62 - v57 * v23) + (v53 - v57 * v24) * (v53 - v57 * v24)) / *(float *)&tPos.vX >= 1.0 )
        v37 = 0.0;
      else
        v37 = 1.0;
LABEL_51:
      if ( eMaterialEditMode && v37 < 1.0 )
        *((_BYTE *)&FirstChildOfType[9].tQTaskChildren.ptMiddle->ptNext
        + v20 * (int)FirstChildOfType[2].tQTaskChildren.ptTail
        + v22) = v7->iActiveMaterial;
      if ( v10 )
      {
        switch ( v10 )
        {
          case TERRAIN_HEIGHTEDITMODE_LIFT:
            v26 = (float *)((char *)FirstChildOfType[7].ptNext
                          + 4 * v22
                          + 4 * v20 * (int)FirstChildOfType[2].tQTaskChildren.ptTail);
            *v26 = v37 * *(float *)&tPos.vX * *((float *)&tPos.vX + 1) + *v26;
            break;
          case TERRAIN_HEIGHTEDITMODE_LOWER:
            v27 = (float *)((char *)FirstChildOfType[7].ptNext
                          + 4 * v22
                          + 4 * v20 * (int)FirstChildOfType[2].tQTaskChildren.ptTail);
            *v27 = *v27 - v37 * *(float *)&tPos.vX * *((float *)&tPos.vX + 1);
            break;
          case TERRAIN_HEIGHTEDITMODE_SOFTEN:
            v28 = FirstChildOfType[2].tQTaskChildren.ptTail;
            v51 = (char *)(v22 + 1);
            if ( v22 + 1 >= (int)(&v28[-1].isInMemPool + 1) )
              v51 = &v28[-1].isInMemPool + 1;
            v49 = v20 - 1 + 2;
            if ( v49 >= (int)&FirstChildOfType[2].tQTaskRefList.ptMiddle[-1].pxObject + 3 )
              v49 = (int)&FirstChildOfType[2].tQTaskRefList.ptMiddle[-1].pxObject + 3;
            ptNext = FirstChildOfType[7].ptNext;
            v30 = v20 * (_DWORD)v28;
            v54 = (float *)((char *)ptNext + 4 * v20 * (_DWORD)v28 + 4 * v22);
            v7 = ptTerrain;
            v31 = *((float *)&ptNext->ptNext + v22 + (v20 - 1 <= 0 ? 0 : v20 - 1) * (_DWORD)v28);
            v20 = v39;
            *v54 = ((v31
                   + *((float *)&ptNext->ptNext + v22 + v49 * (_DWORD)v28)
                   + *((float *)&ptNext->ptNext + v30 + ((v22 - 1) & ((v22 - 1 <= 0) - 1)))
                   + *((float *)&ptNext->ptNext + (_DWORD)&v51[v30]))
                  * v37
                  + *v54)
                 / (v37 * 4.0 + 1.0);
            goto LABEL_65;
          case TERRAIN_HEIGHTEDITMODE_FLATTEN:
            v32 = (float *)((char *)FirstChildOfType[7].ptNext
                          + 4 * v22
                          + 4 * v20 * (int)FirstChildOfType[2].tQTaskChildren.ptTail);
            *v32 = (v7->vFlattenPos - *v32) * v37 * *((float *)&tPos.vX + 1) * 10.0 + *v32;
            break;
          case TERRAIN_HEIGHTEDITMODE_FLATTENLINE:
            v33 = FirstChildOfType[2].tQTaskChildren.ptTail;
            v34 = FirstChildOfType[7].ptNext;
            v7 = ptTerrain;
            *((float *)&v34->ptNext + v22 + v20 * (_DWORD)v33) = (*((float *)&v34->ptNext
                                                                  + (__int64)v46
                                                                  + (_DWORD)v33 * (__int64)v47)
                                                                * (1.0 - v57)
                                                                + v57 * ptTerrain->vFlattenPos
                                                                - *((float *)&v34->ptNext + v22 + v20 * (_DWORD)v33))
                                                               * v37
                                                               + *((float *)&v34->ptNext + v22 + v20 * (_DWORD)v33);
LABEL_65:
            v10 = eHeightEditMode;
            break;
          default:
            break;
        }
      }
      v21 = v64;
      v39 = ++v20;
      if ( v20 >= v64 )
      {
        v20 = (__int64)v45;
LABEL_68:
        v50 = ++v22;
        if ( v22 >= v59 )
        {
LABEL_69:
          if ( v10 == TERRAIN_HEIGHTEDITMODE_DROP )
          {
            v35 = *((float *)&FirstChildOfType[7].ptNext->ptNext
                  + (__int64)v46
                  + (__int64)FirstChildOfType[2].tQTaskChildren.ptTail * (__int64)v47);
            v7->tFlattenPos.vY = v9;
            v7->vFlattenPos = v35;
            LODWORD(v7->tFlattenPos.vX) = HIDWORD(tPos.vY);
            vFlattenPos = v7->vFlattenPos;
            HIDWORD(v7->tFlattenPos.vX) = LODWORD(tPos.vZ);
            v7->tFlattenPos.vZ = vFlattenPos;
          }
          goto LABEL_71;
        }
        goto LABEL_37;
      }
    }
  }
LABEL_72:
  TerrainMap_isUpdated = 1;
}

// source: h/2/terrain.c:1819  [anchor-strings]
void __cdecl Terrain_VertexFunction(
        float *pvOutRelativeZ,
        struct real32x3_t *ptOutNormal,
        unsigned int *pbOutColor,
        unsigned __int8 *piOutMaterial,
        unsigned __int8 *piOutLightmap,
        float vInX,
        float vInY,
        float vDistance)
{
  #pragma pack(push, 1)
  union
  {
    struct { int v51; };
    struct { char igi2_o1[4]; int v52; };
    struct { char igi2_o2[21]; unsigned __int8 v53; };
    struct { char igi2_o3[24]; float v54; };
    struct { char igi2_o4[28]; float v55; };
    struct { char igi2_o5[32]; float v56; };
    struct { char igi2_o6[36]; int v57; };
    struct { char igi2_o7[40]; float v58; };
    struct { char igi2_o8[44]; float v59; };
    struct { char igi2_o9[48]; __int64 v60; };
    struct { char igi2_o10[56]; float v61; };
    struct { char igi2_o11[68]; int v62; };
    struct { char igi2_o12[72]; int v63; };
    struct { char igi2_o13[76]; int v64; };
    struct { char igi2_o14[80]; __int64 v65; };
    struct { char igi2_o15[88]; float v66[2]; };
    struct { char igi2_o16[96]; float v67; };
    struct { char igi2_o17[100]; float v68; };
    char igi2_extent[108];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v8; // eax
  int v9; // esi
  unsigned __int16 v10; // di
  struct TerrainMap_t *v11; // edx
  struct QTask_s *FirstParentOfType; // eax
  unsigned int nWidth; // ebx
  unsigned int nHeight; // ecx
  double v15; // st7
  double v16; // st7
  double v17; // st6
  double v18; // st7
  double v19; // st7
  double v20; // st7
  double v21; // st6
  double v22; // st5
  double v23; // st5
  unsigned int v24; // ebp
  unsigned int v25; // edi
  unsigned int v26; // eax
  float *pvHeightmap; // esi
  int v28; // ecx
  double v29; // st6
  int v30; // esi
  float *v31; // ebx
  double v32; // st5
  double v33; // st6
  double v34; // st7
  double v35; // st6
  double v36; // st6
  long double v37; // st4
  double v38; // st6
  long double v39; // st7
  long double v40; // st6
  unsigned __int8 *piMaterialmap; // eax
  unsigned __int8 *v42; // ebx
  unsigned __int8 v43; // cl
  unsigned __int8 v44; // bl
  unsigned __int8 *v45; // esi
  unsigned __int8 v46; // bl
  unsigned int *pbLightmap; // edx
  float v48; // ecx
  int v49; // eax
  double v50; // st7

  v8 = Terrain_nActiveHeightmaps;
  if ( Terrain_nActiveHeightmaps > 0 )
  {
    v9 = Terrain_nActiveHeightmaps - 1;
    *pbOutColor = -1;
    igi2_frame.v57 = v8 - 1;
    if ( v8 - 1 < 0 )
    {
      v11 = (struct TerrainMap_t *)igi2_frame.v65;
      nWidth = igi2_frame.v65;
      nHeight = igi2_frame.v65;
    }
    else
    {
      v10 = Terrain_eQTaskType;
      do
      {
        v11 = Terrain_aptActiveHeightmap[v9];
        FirstParentOfType = QTask_GetFirstParentOfType(&v11->tQTask, v10);
        nWidth = v11->nWidth;
        igi2_frame.v56 = v11->tPos.vX - *(double *)&FirstParentOfType[3].ptNext;
        nHeight = v11->nHeight;
        v15 = v11->tPos.vY - *(double *)&FirstParentOfType[3].tQTaskChildren.ptHead;
        LODWORD(igi2_frame.v65) = nWidth;
        igi2_frame.v54 = v15;
        v16 = v11->vWorldWidth * 4096.0;
        v17 = v11->vWorldHeight * 4096.0;
        igi2_frame.v55 = v16 * 0.5;
        igi2_frame.v58 = 0.5 * v17;
        LODWORD(igi2_frame.v65) = nHeight;
        igi2_frame.v59 = v16 / (double)nWidth;
        *(float *)&igi2_frame.v60 = v17 / (double)nHeight;
        if ( !v9 )
          break;
        v18 = igi2_frame.v59 * 0.5;
        if ( igi2_frame.v56 - igi2_frame.v55 + v18 < vInX && vInX < igi2_frame.v55 + igi2_frame.v56 - v18 )
        {
          v19 = *(float *)&igi2_frame.v60 * 0.5;
          if ( igi2_frame.v54 - igi2_frame.v58 + v19 < vInY && vInY < igi2_frame.v58 + igi2_frame.v54 - v19 )
            break;
        }
        --v9;
      }
      while ( v9 >= 0 );
      igi2_frame.v57 = v9;
    }
    if ( v11->pvHeightmap )
    {
      v20 = 1.0 / igi2_frame.v59;
      igi2_frame.v59 = 1.0 / *(float *)&igi2_frame.v60;
      igi2_frame.v56 = (vInX - igi2_frame.v56 + igi2_frame.v55) * v20 - 0.5;
      v21 = (vInY - igi2_frame.v54 + igi2_frame.v58) * igi2_frame.v59 - 0.5;
      if ( igi2_frame.v56 >= 0.0 )
      {
        LODWORD(igi2_frame.v65) = nWidth - 1;
        v22 = (double)(nWidth - 1);
        if ( v22 < igi2_frame.v56 )
          igi2_frame.v56 = v22;
      }
      else
      {
        igi2_frame.v56 = 0.0;
      }
      if ( v21 >= 0.0 )
      {
        LODWORD(igi2_frame.v65) = nHeight - 1;
        v23 = (double)(nHeight - 1);
        *(float *)&igi2_frame.v60 = v23;
        if ( v23 < v21 )
          v21 = *(float *)&igi2_frame.v60;
      }
      else
      {
        v21 = 0.0;
      }
      v24 = nWidth - 1;
      v25 = (__int64)igi2_frame.v56;
      igi2_frame.v65 = (__int64)v21;
      v26 = (__int64)v21;
      if ( nWidth - 1 >= v25 + 1 )
        v24 = v25 + 1;
      LODWORD(igi2_frame.v60) = nHeight - 1;
      if ( nHeight - 1 >= v26 + 1 )
        LODWORD(igi2_frame.v60) = v26 + 1;
      LODWORD(igi2_frame.v65) = (__int64)v21;
      igi2_frame.v56 = igi2_frame.v56 - (double)v25;
      pvHeightmap = v11->pvHeightmap;
      v28 = nWidth * v26;
      igi2_frame.v55 = v21 - (double)v26;
      igi2_frame.v62 = 4 * (nWidth * v26 + v25);
      igi2_frame.v66[0] = pvHeightmap[igi2_frame.v62 / 4u];
      igi2_frame.v63 = 4 * (nWidth * v26 + v24);
      v29 = pvHeightmap[igi2_frame.v63 / 4u];
      v30 = nWidth * igi2_frame.v60;
      v31 = v11->pvHeightmap;
      igi2_frame.v64 = 4 * (v30 + v25);
      igi2_frame.v67 = v31[igi2_frame.v64 / 4u];
      LODWORD(igi2_frame.v65) = 4 * (v30 + v24);
      igi2_frame.v68 = *(float *)((char *)v31 + igi2_frame.v65);
      v32 = 1.0 - igi2_frame.v56;
      igi2_frame.v58 = v32;
      if ( v32 < igi2_frame.v55 )
      {
        *(float *)&igi2_frame.v60 = v29 - igi2_frame.v68;
        v36 = igi2_frame.v67 - igi2_frame.v68;
        *pvOutRelativeZ = (1.0 - igi2_frame.v55) * *(float *)&igi2_frame.v60 + v36 * igi2_frame.v58 + igi2_frame.v68;
        v34 = v20 * v36;
        v35 = *(float *)&igi2_frame.v60 * igi2_frame.v59;
      }
      else
      {
        *(float *)&igi2_frame.v60 = igi2_frame.v67 - igi2_frame.v66[0];
        v33 = v29 - igi2_frame.v66[0];
        *pvOutRelativeZ = igi2_frame.v56 * v33 + *(float *)&igi2_frame.v60 * igi2_frame.v55 + igi2_frame.v66[0];
        v34 = -(v20 * v33);
        v35 = -(*(float *)&igi2_frame.v60 * igi2_frame.v59);
      }
      *((float *)&igi2_frame.v60 + 1) = v35;
      v37 = sqrt(v34 * v34 + v35 * v35 + 1.0);
      v38 = v34;
      v39 = 1.0 / v37;
      *(float *)&igi2_frame.v60 = v38 * v39;
      v40 = *((float *)&igi2_frame.v60 + 1) * v39;
      LODWORD(ptOutNormal->vX) = igi2_frame.v60;
      *((float *)&igi2_frame.v60 + 1) = v40;
      igi2_frame.v61 = v39;
      ptOutNormal->vY = *((float *)&igi2_frame.v60 + 1);
      ptOutNormal->vZ = igi2_frame.v61;
      piMaterialmap = v11->piMaterialmap;
      v42 = &piMaterialmap[v28];
      v43 = piMaterialmap[v28 + v25];
      v44 = v42[v24];
      v45 = &piMaterialmap[v30];
      BYTE2(igi2_frame.v54) = v45[v25];
      HIBYTE(igi2_frame.v54) = v45[v24];
      BYTE1(igi2_frame.v54) = v44;
      igi2_frame.v53 = v43 ^ BYTE2(igi2_frame.v54);
      LOBYTE(igi2_frame.v54) = v43;
      if ( !((unsigned __int8)(v43 ^ HIBYTE(igi2_frame.v54)) | (unsigned __int8)(v43 ^ BYTE2(igi2_frame.v54) | v43 ^ v44)) )
      {
        v46 = v43;
        goto LABEL_44;
      }
      if ( !(igi2_frame.v53 | (unsigned __int8)(v43 ^ v44)) )
      {
        if ( igi2_frame.v55 + igi2_frame.v56 > 1.5 )
        {
          v46 = HIBYTE(igi2_frame.v54);
          goto LABEL_44;
        }
        goto LABEL_36;
      }
      if ( (unsigned __int8)(BYTE1(igi2_frame.v54) ^ HIBYTE(igi2_frame.v54)) | (unsigned __int8)(BYTE1(igi2_frame.v54) ^ BYTE2(igi2_frame.v54)) )
      {
        v46 = BYTE2(igi2_frame.v54);
        if ( igi2_frame.v53 | (unsigned __int8)(BYTE2(igi2_frame.v54) ^ HIBYTE(igi2_frame.v54)) )
        {
          if ( (unsigned __int8)(v43 ^ HIBYTE(igi2_frame.v54)) | (unsigned __int8)(BYTE1(igi2_frame.v54) ^ HIBYTE(igi2_frame.v54)) )
          {
            igi2_frame.v60 = (__int64)(igi2_frame.v56 + 0.5);
            v46 = *((_BYTE *)&igi2_frame.v54 + 2 * (__int64)(igi2_frame.v55 + 0.5) + igi2_frame.v60);
          }
          else if ( igi2_frame.v56 + 1.0 - igi2_frame.v55 >= 0.5 )
          {
            v46 = HIBYTE(igi2_frame.v54);
          }
          goto LABEL_44;
        }
        if ( igi2_frame.v56 + 1.0 - igi2_frame.v55 <= 1.5 )
        {
LABEL_44:
          *piOutLightmap = igi2_frame.v57;
          if ( v11->isTerrainLightmapAllocated )
          {
            pbLightmap = v11->pbLightmap;
            LODWORD(igi2_frame.v66[0]) = pbLightmap[igi2_frame.v62 / 4u];
            LODWORD(igi2_frame.v66[1]) = pbLightmap[igi2_frame.v63 / 4u];
            v48 = *(float *)&pbLightmap[igi2_frame.v64 / 4u];
            v49 = igi2_frame.v65;
            igi2_frame.v65 = (__int64)(igi2_frame.v55 + 0.5);
            igi2_frame.v67 = v48;
            igi2_frame.v68 = *(float *)((char *)pbLightmap + v49);
            igi2_frame.v65 = (__int64)(igi2_frame.v56 + 0.5);
            LODWORD(igi2_frame.v65) = ((unsigned __int8)LODWORD(igi2_frame.v66[2 * (__int64)(igi2_frame.v55 + 0.5) + igi2_frame.v65])
                          + (unsigned __int8)BYTE1(LODWORD(igi2_frame.v66[2 * (__int64)(igi2_frame.v55 + 0.5) + igi2_frame.v65]))
                          + (unsigned __int8)BYTE2(LODWORD(igi2_frame.v66[2 * (__int64)(igi2_frame.v55 + 0.5) + igi2_frame.v65])))
                         / 3;
            v50 = (double)(unsigned int)igi2_frame.v65 * 0.007843137718737125;
            *piOutMaterial = v46;
            Terrain_vLightIntensity = v50;
          }
          else
          {
            Terrain_vLightIntensity = 0.0;
            DebugConsole_printf("\nlight at(%d,%d):no lightmap found", igi2_frame.v51, igi2_frame.v52);
            *piOutMaterial = v46;
          }
          return;
        }
      }
      else if ( igi2_frame.v55 + igi2_frame.v56 < 0.5 )
      {
LABEL_36:
        v46 = v43;
        goto LABEL_44;
      }
      v46 = BYTE1(igi2_frame.v54);
      goto LABEL_44;
    }
  }
}

// source: e/2/discard2d.c:781  [layout]
void __cdecl Terrain_UpdateDiscardMeshHandler(struct QTask_s *ptQTask)
{
  struct DiscardMeshContext_s *v1; // edi
  struct QTask_s *ptHead; // eax
  int v3; // edx
  struct QTask_s *v4; // ecx
  void (__cdecl *pfHandler)(struct QTask_s *, struct DiscardMeshContext_s *); // ecx
  int v6; // edx
  struct DiscardMeshContext_s *v7; // esi
  struct DiscardMeshContext_s *v8; // eax
  struct DiscardMeshContext_s *v9; // eax
  struct DiscardMeshContext_s *v10; // eax
  int v11; // ebx
  int *p_ptPrev; // edi
  struct DiscardMeshContext_s *v13; // eax
  int v14; // ebx
  int *v15; // edi
  float ptDiscardMeshContext; // [esp+0h] [ebp-10h]
  float ptPos; // [esp+4h] [ebp-Ch]

  v1 = (struct DiscardMeshContext_s *)&ptQTask[7];
  ptPos = *(float *)&ptQTask[4].eQTaskType * 4096.0;
  ptDiscardMeshContext = *(float *)&ptQTask[4].ptParent * 4096.0;
  Discard2D_InitDiscardMeshContext(
    (struct DiscardMeshContext_s *)&ptQTask[7],
    (struct real64x3_t *)&ptQTask[3],
    ptDiscardMeshContext,
    ptPos);
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
      pfHandler = (void (__cdecl *)(struct QTask_s *, struct DiscardMeshContext_s *))QTask_aatQTaskFinalEvent[DiscardTask_eDiscardMeshQTaskEvent][ptHead->eQTaskType].pfHandler;
      v6 = v3 + 1;
      QTask_nProtectedQTaskStackOffset = v6;
      if ( pfHandler )
      {
        pfHandler(ptHead, v1);
        v6 = QTask_nProtectedQTaskStackOffset;
      }
      ptHead = (struct QTask_s *)dword_849C7DC[v6];
      v3 = v6 - 1;
      QTask_nProtectedQTaskStackOffset = v3;
    }
    while ( ptHead );
  }
  v7 = (struct DiscardMeshContext_s *)&ptQTask[7];
  if ( !ptQTask[918].tQTaskChildren.ptTail )
  {
    qsort(&ptQTask[107], ptQTask[917].tQTaskRefList.ptHead, 12, Discard2D_Vertex2DQSortCompare);
    v8 = Discard2D_AddEdgeVertexID(v1, 0, 1);
    v9 = Discard2D_AddEdgeVertexID(v8, 0, 2);
    v10 = Discard2D_AddEdgeVertexID(v9, 1, 3);
    Discard2D_AddEdgeVertexID(v10, 2, 3);
    v11 = 0;
    if ( (int)ptQTask[917].ptParent > 0 )
    {
      p_ptPrev = (int *)&ptQTask[887].ptPrev;
      do
      {
        v13 = Discard2D_AddEdgeVertexID(v7, *(p_ptPrev - 1), *p_ptPrev);
        Discard2D_AddEdgeVertexID(v13, *(p_ptPrev - 1), p_ptPrev[1]);
        Discard2D_AddEdgeVertexID(v7, *p_ptPrev, p_ptPrev[1]);
        ++v11;
        p_ptPrev += 3;
      }
      while ( v11 < (int)ptQTask[917].ptParent );
    }
    Discard2D_TriangulateSet(v7);
    Discard2D_GenerateTriangleSet(v7);
    v14 = 0;
    if ( (int)ptQTask[917].ptParent > 0 )
    {
      v15 = (int *)&ptQTask[887].ptPrev;
      do
      {
        Discard2D_RemoveTriangleVertexID(v7, *(v15 - 1), *v15, v15[1]);
        ++v14;
        v15 += 3;
      }
      while ( v14 < (int)ptQTask[917].ptParent );
    }
    ptQTask[918].tQTaskChildren.ptTail = (struct QTask_s *)1;
  }
}

// source: h/2/terrain.c:2087  [size]
void __cdecl Terrain_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = Terrain_ptParameterList;
}

// source: h/2/terrain.c:2106  [anchor-mhash]
int __cdecl TerrainMap_GetNormal(
        struct TerrainMap_t *ptTerrainMap,
        float *pvZ,
        struct real32x3_t *ptNormal,
        int nX,
        int nY)
{
  int v5; // ebx
  int v7; // ebp
  int v8; // eax
  int v9; // edi
  float *pvHeightmap; // edx
  int v11; // ecx
  double v12; // st7
  long double v13; // st6
  int v15; // [esp+Ch] [ebp-38h]
  int nX1; // [esp+10h] [ebp-34h]
  int nX2; // [esp+14h] [ebp-30h]
  int nWidth; // [esp+18h] [ebp-2Ch]
  float tTempNormal; // [esp+28h] [ebp-1Ch]
  float tTempNormal_8; // [esp+30h] [ebp-14h]
  struct real32x3_t tNormal; // 0:^1C.12

  v5 = 0;
  if ( nX >= 0 )
  {
    v15 = ptTerrainMap->nWidth - 1;
    if ( v15 >= nX )
      v15 = nX;
  }
  else
  {
    v15 = 0;
  }
  if ( nY >= 0 )
  {
    v7 = ptTerrainMap->nHeight - 1;
    if ( v7 >= nY )
      v7 = nY;
  }
  else
  {
    v7 = 0;
  }
  if ( nX - 1 >= 0 )
  {
    nX1 = ptTerrainMap->nWidth - 1;
    if ( nX1 >= nX - 1 )
      nX1 = nX - 1;
  }
  else
  {
    nX1 = 0;
  }
  if ( nX + 1 >= 0 )
  {
    nX2 = ptTerrainMap->nHeight - 1;
    if ( nX2 >= nX + 1 )
      nX2 = nX + 1;
  }
  else
  {
    nX2 = 0;
  }
  if ( nY - 1 >= 0 )
  {
    v5 = ptTerrainMap->nWidth - 1;
    if ( v5 >= nY - 1 )
      v5 = nY - 1;
  }
  v8 = nY + 1;
  if ( nY + 1 >= 0 )
  {
    v9 = ptTerrainMap->nHeight - 1;
    if ( v9 >= v8 )
      v9 = v8;
  }
  else
  {
    v9 = 0;
  }
  pvHeightmap = ptTerrainMap->pvHeightmap;
  v11 = v7 * ptTerrainMap->nWidth;
  nWidth = ptTerrainMap->nWidth;
  v12 = pvHeightmap[v11 + v15];
  tTempNormal = v12 - pvHeightmap[nX2 + v11] + pvHeightmap[v11 + nX1] - v12;
  tNormal.vX = tTempNormal;
  tTempNormal_8 = ptTerrainMap->vWorldWidth * 4096.0 / (double)nWidth;
  tNormal.vY = v12 - pvHeightmap[v15 + v9 * nWidth] + pvHeightmap[v15 + v5 * nWidth] - v12 + 0.0;
  tNormal.vZ = tTempNormal_8 + ptTerrainMap->vWorldHeight * 4096.0 / (double)ptTerrainMap->nHeight;
  if ( tTempNormal != 0.0 || tNormal.vY != 0.0 || tNormal.vZ != 0.0 )
  {
    v13 = 1.0 / sqrt(tTempNormal * tTempNormal + tNormal.vY * tNormal.vY + tNormal.vZ * tNormal.vZ);
    tNormal.vX = tTempNormal * v13;
    tNormal.vY = tNormal.vY * v13;
    tNormal.vZ = tNormal.vZ * v13;
  }
  *ptNormal = tNormal;
  *pvZ = v12;
  return (int)ptNormal;
}

// source: h/2/terrain.c:2157  [anchor-caller]
struct Terrain_t *__cdecl TerrainMap_CalculateLightmaps(
        struct Terrain_t *ptTerrain,
        struct TerrainMap_t *ptTerrainMap,
        enum bool isPreview)
{
  #pragma pack(push, 1)
  union
  {
    struct { int nX; };
    struct { char igi2_o1[4]; float vY; };
    struct { char igi2_o2[4]; float vYa; };
    struct { char igi2_o3[8]; int nY; };
    struct { char igi2_o4[12]; int nNumCalculatedTexels; };
    struct { char igi2_o5[16]; float vX; };
    struct { char igi2_o6[20]; float tColor; };
    struct { char igi2_o7[24]; float tColor_4; };
    struct { char igi2_o8[24]; float tColor_4a; };
    struct { char igi2_o9[28]; float tColor_8; };
    struct { char igi2_o10[28]; float tColor_8a; };
    struct { char igi2_o11[38]; unsigned __int8 iMaterial; };
    struct { char igi2_o12[39]; unsigned __int8 iLightmap; };
    struct { char igi2_o13[40]; __int64 bColor; };
    struct { char igi2_o14[48]; unsigned int *pbLightmap; };
    struct { char igi2_o15[52]; float vZ; };
    struct { char igi2_o16[56]; float vScaleX; };
    struct { char igi2_o17[60]; float vScaleY; };
    struct { char igi2_o18[64]; struct real32x3_t tNormal; };
    struct { char igi2_o19[76]; struct Dirlight_s *ptDirlight; };
    struct { char igi2_o20[80]; float vOffsetX; };
    struct { char igi2_o21[84]; float vOffsetY; };
    struct { char igi2_o22[88]; struct real32x9_t tOrientation; };
    struct { char igi2_o23[128]; struct real32x9_t Real32x9_Invert_tTemp; };
    struct { char igi2_o24[168]; struct real64x3_t tStart; };
    char igi2_extent[192];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v4; // edi
  DWORD PerformanceCounter; // eax
  struct Hemicube_t *v6; // eax
  struct TerrainMap_t *v7; // esi
  double v8; // st7
  int nCalculatingX; // edx
  int nWidth; // edi
  double v11; // st7
  double v12; // st7
  int v13; // eax
  bool v14; // cc
  int v15; // ecx
  unsigned __int16 v16; // cx
  struct TerrainMap_t *ptCalculatingTerrainMap; // eax
  struct TerrainMap_t *NextSiblingOfType; // eax
  bool v19; // zf
  struct Terrain_t *result; // eax
  DWORD TickCount; // eax

  v4 = isPreview != false ? 16768 : 20;
  igi2_frame.nNumCalculatedTexels = 0;
  Level_isDynamicQTaskActive = 1;
  if ( !Flow_nSuspendRefCount )
  {
    if ( Timer_isPerformanceCounter )
      PerformanceCounter = Timer_GetPerformanceCounter();
    else
      PerformanceCounter = GetTickCount();
    Flow_nSuspendTime = PerformanceCounter - Timer_nStartTime;
  }
  ++Flow_nSuspendRefCount;
  v6 = LightmapInfo_NewHemicube(64);
  Terrain_ptHemicube = v6;
  if ( GlobalLightQTask_ptGlobalLight )
    Lightmap_Initialize(
      &Level_ptQLevelQTask->tQTask,
      64,
      GlobalLightQTask_ptGlobalLight->vRadiosityIntensity,
      GlobalLightQTask_ptGlobalLight->vRadiosityGamma,
      GlobalLightQTask_ptGlobalLight->vRadiosityFadeout,
      GlobalLightQTask_ptGlobalLight->vRadiosityDirlightRadius,
      v6->pvMainDeltaFormFactor,
      v6->pvHalfDeltaFormFactor,
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
      v6->pvMainDeltaFormFactor,
      v6->pvHalfDeltaFormFactor,
      Mesh3D_atAmbientColor,
      true,
      nullptr);
  v7 = ptTerrainMap;
  igi2_frame.pbLightmap = ptTerrainMap->pbLightmap;
  if ( igi2_frame.pbLightmap && SkyDome_ptDirlight )
  {
    v8 = ptTerrainMap->vWorldWidth * 2048.0;
    nCalculatingX = ptTerrain->nCalculatingX;
    igi2_frame.ptDirlight = SkyDome_ptDirlight;
    igi2_frame.nY = ptTerrain->nCalculatingY;
    igi2_frame.nX = nCalculatingX;
    igi2_frame.vOffsetX = ptTerrainMap->tPos.vX - v8 - ptTerrain->tPos.vX;
    igi2_frame.vOffsetY = ptTerrainMap->tPos.vY - ptTerrainMap->vWorldHeight * 2048.0 - ptTerrain->tPos.vY;
    igi2_frame.vScaleX = ptTerrainMap->vWorldWidth * 4096.0 / (double)ptTerrainMap->nWidth;
    igi2_frame.vScaleY = ptTerrainMap->vWorldHeight * 4096.0 / (double)ptTerrainMap->nHeight;
    while ( igi2_frame.nY < v7->nHeight )
    {
      if ( igi2_frame.nNumCalculatedTexels < v4 )
      {
        while ( 1 )
        {
          nWidth = v7->nWidth;
          if ( nCalculatingX >= nWidth )
            break;
          igi2_frame.vX = ((double)igi2_frame.nX + 0.5) * igi2_frame.vScaleX + igi2_frame.vOffsetX;
          igi2_frame.vY = ((double)igi2_frame.nY + 0.5) * igi2_frame.vScaleY + igi2_frame.vOffsetY;
          TerrainMap_GetNormal(v7, &igi2_frame.vZ, &igi2_frame.tNormal, nCalculatingX, igi2_frame.nY);
          if ( isPreview )
          {
            igi2_frame.tColor_4 = 0.0;
            igi2_frame.tColor_8 = 0.0;
            igi2_frame.vYa = igi2_frame.tNormal.vZ * igi2_frame.ptDirlight->tDir.vZ + igi2_frame.tNormal.vY * igi2_frame.ptDirlight->tDir.vY + igi2_frame.tNormal.vX * igi2_frame.ptDirlight->tDir.vX;
            v11 = 0.0;
            if ( igi2_frame.vYa > 0.0 )
            {
              v11 = igi2_frame.vYa * igi2_frame.ptDirlight->tFrontColor.vX;
              igi2_frame.tColor_4 = igi2_frame.vYa * igi2_frame.ptDirlight->tFrontColor.vY;
              igi2_frame.tColor_8 = igi2_frame.vYa * igi2_frame.ptDirlight->tFrontColor.vZ;
            }
            igi2_frame.tColor_8a = Mesh3D_atAmbientColor[0].vZ + igi2_frame.tColor_8;
            igi2_frame.tColor = (v11 + Mesh3D_atAmbientColor[0].vX) * 0.5;
            igi2_frame.tColor_4a = (Mesh3D_atAmbientColor[0].vY + igi2_frame.tColor_4) * 0.5;
            v12 = igi2_frame.tColor_8a * 0.5;
            if ( igi2_frame.tColor >= 1.0 )
              igi2_frame.tColor = 1.0;
            if ( igi2_frame.tColor_4a >= 1.0 )
              igi2_frame.tColor_4a = 1.0;
            if ( v12 >= 1.0 )
              v12 = 1.0;
            igi2_frame.bColor = (__int64)(255.0 * v12);
            igi2_frame.pbLightmap[igi2_frame.nX + igi2_frame.nY * nWidth] = igi2_frame.bColor
                                         | (((unsigned int)(__int64)(igi2_frame.tColor_4a * 255.0)
                                           | (((unsigned __int8)(__int64)(igi2_frame.tColor * 255.0) | 0xFFFFFF00) << 8)) << 8);
          }
          else
          {
            Terrain_VertexFunction(&igi2_frame.vZ, &igi2_frame.tNormal, (unsigned int *)&igi2_frame.bColor, &igi2_frame.iMaterial, &igi2_frame.iLightmap, igi2_frame.vX, igi2_frame.vY, 0.0);
            igi2_frame.tStart.vX = igi2_frame.vX + ptTerrain->tPos.vX;
            igi2_frame.tStart.vY = igi2_frame.vY + ptTerrain->tPos.vY;
            igi2_frame.tStart.vZ = igi2_frame.vZ + ptTerrain->tPos.vZ;
            Real32x9_FromReal32x3(&igi2_frame.tOrientation, &igi2_frame.tNormal);
            igi2_frame.Real32x9_Invert_tTemp.tX.vX = igi2_frame.tOrientation.tX.vX;
            igi2_frame.Real32x9_Invert_tTemp.tX.vZ = igi2_frame.tOrientation.tZ.vX;
            igi2_frame.Real32x9_Invert_tTemp.tY.vX = igi2_frame.tOrientation.tX.vY;
            igi2_frame.Real32x9_Invert_tTemp.tY.vZ = igi2_frame.tOrientation.tZ.vY;
            igi2_frame.Real32x9_Invert_tTemp.tZ.vX = igi2_frame.tOrientation.tX.vZ;
            igi2_frame.Real32x9_Invert_tTemp.tZ.vZ = igi2_frame.tOrientation.tZ.vZ;
            igi2_frame.Real32x9_Invert_tTemp.tX.vY = igi2_frame.tOrientation.tY.vX;
            igi2_frame.Real32x9_Invert_tTemp.nOps = igi2_frame.tOrientation.nOps;
            v13 = igi2_frame.nY * ptTerrainMap->nWidth;
            igi2_frame.Real32x9_Invert_tTemp.tY.vY = igi2_frame.tOrientation.tY.vY;
            igi2_frame.Real32x9_Invert_tTemp.tZ.vY = igi2_frame.tOrientation.tY.vZ;
            qmemcpy(&igi2_frame.tOrientation, &igi2_frame.Real32x9_Invert_tTemp, sizeof(igi2_frame.tOrientation));
            Lightmap_RenderHemicube(&igi2_frame.pbLightmap[igi2_frame.nX + v13], &igi2_frame.tStart, &igi2_frame.tOrientation);
            v7 = ptTerrainMap;
          }
          v14 = igi2_frame.nNumCalculatedTexels + 1 < (isPreview != false ? 16768 : 20);
          ++igi2_frame.nX;
          ++igi2_frame.nNumCalculatedTexels;
          if ( !v14 )
            break;
          nCalculatingX = igi2_frame.nX;
        }
        v4 = isPreview != false ? 16768 : 20;
      }
      igi2_frame.nX = 0;
      ++igi2_frame.nY;
      if ( igi2_frame.nNumCalculatedTexels >= v4 )
        break;
      nCalculatingX = 0;
    }
    v15 = igi2_frame.nNumCalculatedTexels + ptTerrain->nCalculatingX;
    ptTerrain->nCalculatingX = v15;
    ptTerrain->nCalculatingY += v15 / v7->nWidth;
    ptTerrain->nCalculatingX = v15 % v7->nWidth;
    ptTerrain->nCalculatedTexels += igi2_frame.nNumCalculatedTexels;
    if ( igi2_frame.nNumCalculatedTexels < v4 )
    {
      TerrainMap_SoftenLightmapEdges(ptTerrain, v7, 0.10000000149011612);
      v16 = TerrainMap_eQTaskType;
      ptCalculatingTerrainMap = ptTerrain->ptCalculatingTerrainMap;
      ptTerrain->nCalculatingX = 0;
      ptTerrain->nCalculatingY = 0;
      NextSiblingOfType = (struct TerrainMap_t *)QTask_GetNextSiblingOfType(&ptCalculatingTerrainMap->tQTask, v16);
      ptTerrain->ptCalculatingTerrainMap = NextSiblingOfType;
      if ( !NextSiblingOfType )
      {
        ptTerrain->isCalculating = 0;
        TerrainMap_isUpdated = 1;
      }
    }
    Texture_Download(&v7->tLightmapTexInfo, nullptr, 4 * v7->nWidth, v7->nWidth, v7->nHeight, 3, v7->pbLightmap);
  }
  Lightmap_Deinitialize(false);
  LightmapInfo_DeleteHemicube(Terrain_ptHemicube);
  result = (struct Terrain_t *)(Flow_nSuspendRefCount - 1);
  v19 = Flow_nSuspendRefCount == 1;
  Terrain_ptHemicube = nullptr;
  --Flow_nSuspendRefCount;
  if ( v19 )
  {
    if ( Timer_isPerformanceCounter )
      TickCount = Timer_GetPerformanceCounter();
    else
      TickCount = GetTickCount();
    result = (struct Terrain_t *)(TickCount - Timer_nStartTime - Flow_nSuspendTime);
    Flow_ptFlow->nSkipTime += (int)result;
    Flow_nSuspendTime = 0;
  }
  Level_isDynamicQTaskActive = 0;
  return result;
}

// source: h/2/terrain.c:2354  [anchor-mhash]
void __cdecl Terrain_CalculateLightmaps(struct Terrain_t *ptTerrain, enum bool isPreview)
{
  unsigned __int16 v2; // dx
  struct QTask_s *i; // esi

  v2 = TerrainMap_eQTaskType;
  if ( QTask_GetFirstChildOfType(&ptTerrain->tDynCubeObj.tQObj.tQTask, TerrainMap_eQTaskType) )
  {
    ptTerrain->isCalculatingPreview = isPreview;
    ptTerrain->isDynamicLighting = 0;
    ptTerrain->vProgress = 0.0;
    ptTerrain->isCalculating = 1;
    ptTerrain->ptCalculatingTerrainMap = (struct TerrainMap_t *)QTask_GetFirstChildOfType(
                                                                  &ptTerrain->tDynCubeObj.tQObj.tQTask,
                                                                  v2);
    ptTerrain->nCalculatedTexels = 0;
    ptTerrain->nCalculatingX = 0;
    ptTerrain->nCalculatingY = 0;
    ptTerrain->nTotalTexels = 0;
    for ( i = QTask_GetFirstChildOfType(&ptTerrain->tDynCubeObj.tQObj.tQTask, v2); i; i = QTask_GetNextSiblingOfType(
                                                                                            i,
                                                                                            v2) )
    {
      memset(i[9].tQTaskRefList.ptHead, 0, 4 * (int)i[2].tQTaskRefList.ptMiddle * (int)i[2].tQTaskChildren.ptTail);
      ptTerrain->nTotalTexels += (int)i[2].tQTaskRefList.ptMiddle * (int)i[2].tQTaskChildren.ptTail;
    }
    if ( Timer_isPerformanceCounter )
      ptTerrain->nStartTime = Timer_GetPerformanceCounter() - Timer_nStartTime;
    else
      ptTerrain->nStartTime = GetTickCount() - Timer_nStartTime;
  }
}

// source: h/2/terrain.c:2413  [anchor-caller]
void __cdecl TerrainMap_Syncronize(struct Terrain_t *ptTerrain, struct TerrainMap_t *ptTerrainMap)
{
  int nWidth; // ecx
  float *v3; // eax
  int v4; // edi
  int v5; // esi
  double v6; // st7
  int v7; // edi
  int v8; // esi
  float v9; // [esp+0h] [ebp-2Ch]
  float v10; // [esp+4h] [ebp-28h]
  int nY; // [esp+14h] [ebp-18h]
  int nX; // [esp+18h] [ebp-14h]
  int pvTempMapa; // [esp+1Ch] [ebp-10h]
  float *pvTempMap; // [esp+1Ch] [ebp-10h]
  float vTexelHeight; // [esp+20h] [ebp-Ch]
  float v16; // [esp+24h] [ebp-8h]
  float vTexelWidth; // [esp+28h] [ebp-4h]

  nWidth = ptTerrainMap->nWidth;
  pvTempMapa = ptTerrainMap->nHeight;
  vTexelWidth = ptTerrainMap->vWorldWidth * 4096.0 / (double)nWidth;
  vTexelHeight = ptTerrainMap->vWorldHeight * 4096.0 / (double)pvTempMapa;
  v3 = (float *)Mem_AllocFn(4 * nWidth * pvTempMapa, 4);
  pvTempMap = v3;
  nY = 0;
  if ( ptTerrainMap->nHeight > 0 )
  {
    v4 = ptTerrainMap->nWidth;
    do
    {
      v5 = 0;
      for ( nX = 0; v5 < v4; nX = v5 )
      {
        v16 = ((double)nY + 0.5) * vTexelHeight;
        v10 = ptTerrainMap->tPos.vY - ptTerrainMap->vWorldHeight * 2048.0 + v16 - ptTerrain->tPos.vY;
        v9 = ptTerrainMap->tPos.vX
           - ptTerrainMap->vWorldWidth * 2048.0
           + ((double)nX + 0.5) * vTexelWidth
           - ptTerrain->tPos.vX;
        v6 = Terrain_SampleHeightBilinear(ptTerrain, nullptr, v9, v10);
        v3 = pvTempMap;
        v7 = v5 + nY * v4;
        ++v5;
        pvTempMap[v7] = v6;
        v4 = ptTerrainMap->nWidth;
      }
      ++nY;
    }
    while ( nY < ptTerrainMap->nHeight );
  }
  qmemcpy(ptTerrainMap->pvHeightmap, v3, 4 * ptTerrainMap->nWidth * ptTerrainMap->nHeight);
  if ( v3 )
  {
    v8 = *(_DWORD *)((unsigned int)(v3 - 1) & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v8);
    memset(*(void **)(v8 + 8), 0xCDu, *(_DWORD *)(v8 + 16));
    free((void *)v8);
  }
  ((void (__cdecl *)(struct TerrainMap_t *, _DWORD))QTask_aatQTaskFinalEvent[ParameterList_eUpdateInternalDataQTaskEvent][ptTerrainMap->tQTask.eQTaskType].pfHandler)(
    ptTerrainMap,
    0);
}

// source: h/2/terrain.c:2554  [anchor-callee]
void __cdecl TerrainMap_ResampleAndAlign(
        struct TerrainMap_t *ptTerrainMap,
        struct TerrainMap_t *ptBaseTerrainMap,
        struct Terrain_t *ptTerrain)
{
  #pragma pack(push, 1)
  union
  {
    struct { int v27; };
    struct { float v28; };
    struct { char igi2_o2[4]; float v29; };
    struct { char igi2_o3[4]; float *v30; };
    struct { char igi2_o4[8]; int i; };
    struct { char igi2_o5[8]; float v31; };
    struct { char igi2_o6[12]; struct Terrain_t *v33; };
    struct { char igi2_o7[12]; float v34; };
    struct { char igi2_o8[12]; struct Terrain_t *v35; };
    struct { char igi2_o9[12]; float v36; };
    struct { char igi2_o10[16]; float v37; };
    struct { char igi2_o11[20]; float v38; };
    struct { char igi2_o12[24]; int nEditHeight; };
    struct { char igi2_o13[24]; unsigned __int8 *v40; };
    struct { char igi2_o14[28]; float v41; };
    struct { char igi2_o15[36]; double v42; };
    struct { char igi2_o16[44]; double v43; };
    struct { char igi2_o17[52]; double v44[3]; };
    char igi2_extent[76];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v4; // eax
  int v5; // esi
  unsigned int v6; // eax
  double v7; // st7
  int nEditWidth; // ecx
  double v9; // st7
  double v10; // st6
  double v11; // st5
  double v12; // st4
  int v13; // edi
  int v14; // eax
  int v15; // ecx
  enum bool isLightmapResource; // eax
  unsigned int *pbLightmap; // eax
  int v18; // esi
  struct TexInfo_s *p_tLightmapTexInfo; // edi
  int v20; // esi
  unsigned int *v21; // edi
  enum bool isHeightmapResource; // eax
  float *pvHeightmap; // eax
  int v24; // esi
  unsigned __int8 *piMaterialmap; // eax
  int v26; // esi
  float ptTerrainMapa = *(float *)&ptTerrain; // [esp+5Ch] [ebp+4h] ARGSLOT

  igi2_frame.v29 = ptBaseTerrainMap->vWorldWidth * 4096.0 / (double)ptBaseTerrainMap->nWidth;
  igi2_frame.v31 = ptBaseTerrainMap->vWorldHeight * 4096.0 / (double)ptBaseTerrainMap->nHeight;
  v4 = (__int64)(ptTerrainMap->vEditWorldWidth / igi2_frame.v29 * 4096.0);
  igi2_frame.v27 = v4;
  v5 = (__int64)(ptTerrainMap->vEditWorldHeight / igi2_frame.v31 * 4096.0);
  igi2_frame.v33 = (struct Terrain_t *)v5;
  if ( v4 > 1 )
  {
    _BitScanReverse((unsigned int *)&v4, v4 - 1);
    igi2_frame.v27 = 1 << (v4 + 1);
  }
  if ( v5 > 1 )
  {
    _BitScanReverse(&v6, v5 - 1);
    igi2_frame.v33 = (struct Terrain_t *)(1 << (v6 + 1));
  }
  ptTerrainMapa = (double)igi2_frame.v27 * igi2_frame.v29;
  igi2_frame.v28 = (double)(int)igi2_frame.v33 * igi2_frame.v31;
  v7 = ptTerrainMapa / igi2_frame.v28 / (ptBaseTerrainMap->vWorldWidth / ptBaseTerrainMap->vWorldHeight);
  if ( v7 <= 1.0 )
    ptTerrainMapa = ptTerrainMapa / v7;
  else
    igi2_frame.v28 = v7 * igi2_frame.v28;
  nEditWidth = ptTerrainMap->nEditWidth;
  igi2_frame.nEditHeight = ptTerrainMap->nEditHeight;
  HIDWORD(igi2_frame.v44[2]) = HIDWORD(ptTerrain->tPos.vZ);
  igi2_frame.v38 = ptTerrainMapa / (double)nEditWidth;
  igi2_frame.v37 = igi2_frame.v28 / (double)igi2_frame.nEditHeight;
  igi2_frame.v34 = igi2_frame.v38 * 0.5;
  v9 = ptBaseTerrainMap->tPos.vX - (ptBaseTerrainMap->vWorldWidth * 4096.0 + igi2_frame.v29) * 0.5;
  igi2_frame.v44[0] = igi2_frame.v34 + ptTerrainMap->tEditPos.vX - v9;
  v10 = igi2_frame.v37 * 0.5;
  v11 = ptBaseTerrainMap->tPos.vY - (ptBaseTerrainMap->vWorldHeight * 4096.0 + igi2_frame.v31) * 0.5;
  v12 = v10 + ptTerrainMap->tEditPos.vY - v11;
  igi2_frame.v44[0] = (double)(int)(__int64)(igi2_frame.v44[0] / igi2_frame.v29 + 0.5) * igi2_frame.v29 - igi2_frame.v34 + v9;
  LODWORD(igi2_frame.v44[2]) = LODWORD(ptTerrain->tPos.vZ);
  igi2_frame.v44[1] = (double)(int)(__int64)(v12 / igi2_frame.v31 + 0.5) * igi2_frame.v31 - v10 + v11;
  igi2_frame.v30 = (float *)Mem_AllocFn(4 * nEditWidth * igi2_frame.nEditHeight, 4);
  igi2_frame.v40 = (unsigned __int8 *)Mem_AllocFn(ptTerrainMap->nEditHeight * ptTerrainMap->nEditWidth, 4);
  for ( igi2_frame.i = 0; igi2_frame.i < ptTerrainMap->nEditHeight; ++igi2_frame.i )
  {
    v13 = 0;
    igi2_frame.v35 = nullptr;
    if ( ptTerrainMap->nEditWidth > 0 )
    {
      igi2_frame.v42 = igi2_frame.v44[0] - ptTerrainMapa * 0.5;
      igi2_frame.v43 = igi2_frame.v44[1] - igi2_frame.v28 * 0.5 + ((double)igi2_frame.i + 0.5) * igi2_frame.v37;
      do
      {
        igi2_frame.v41 = igi2_frame.v43 - ptTerrain->tPos.vY;
        igi2_frame.v36 = ((double)(int)igi2_frame.v35 + 0.5) * igi2_frame.v38 + igi2_frame.v42 - ptTerrain->tPos.vX;
        igi2_frame.v30[v13 + igi2_frame.i * ptTerrainMap->nEditWidth] = Terrain_SampleHeightBicubic(ptTerrain, nullptr, igi2_frame.v36, igi2_frame.v41);
        igi2_frame.v40[igi2_frame.i * ptTerrainMap->nEditWidth + v13++] = Terrain_SampleMaterial(ptTerrain, nullptr, igi2_frame.v36, igi2_frame.v41);
        igi2_frame.v35 = (struct Terrain_t *)v13;
      }
      while ( v13 < ptTerrainMap->nEditWidth );
    }
  }
  v14 = ptTerrainMap->nEditHeight;
  qmemcpy(&ptTerrainMap->tPos, igi2_frame.v44, sizeof(ptTerrainMap->tPos));
  ptTerrainMap->vWorldWidth = ptTerrainMapa * 0.000244140625;
  ptTerrainMap->vWorldHeight = igi2_frame.v28 * 0.000244140625;
  v15 = ptTerrainMap->nEditWidth;
  ptTerrainMap->nHeight = v14;
  ptTerrainMap->nRawDataSize = 4 * v15 * v14;
  isLightmapResource = ptTerrainMap->isLightmapResource;
  ptTerrainMap->nWidth = v15;
  if ( isLightmapResource == false )
  {
    pbLightmap = ptTerrainMap->pbLightmap;
    if ( pbLightmap )
    {
      v18 = *(_DWORD *)((unsigned int)(pbLightmap - 1) & 0xFFFFFFFC);
      --Mem_nCurrentAllocations;
      Node_Remove((_DWORD **)v18);
      memset(*(void **)(v18 + 8), 0xCDu, *(_DWORD *)(v18 + 16));
      free((void *)v18);
      ptTerrainMap->pbLightmap = nullptr;
    }
  }
  if ( ptTerrainMap->isTerrainLightmapAllocated )
  {
    p_tLightmapTexInfo = &ptTerrainMap->tLightmapTexInfo;
    if ( AppContext_tAppContext.isMainMenu == false )
      RenderMode_atRenderMode[p_tLightmapTexInfo->eRenderMode].apfRenderModeMethod[Texture_eDeAllocTextureMethod](&ptTerrainMap->tLightmapTexInfo);
    memset(p_tLightmapTexInfo, 0, sizeof(struct TexInfo_s));
    ptTerrainMap->isTerrainLightmapAllocated = false;
  }
  v20 = 4 * ptTerrainMap->nWidth * ptTerrainMap->nHeight;
  v21 = (unsigned int *)Mem_AllocFn(v20, 4);
  ptTerrainMap->pbLightmap = v21;
  memset(v21, 0xFFu, v20);
  Texture_AllocAndDownload(
    &ptTerrainMap->tLightmapTexInfo,
    nullptr,
    4 * ptTerrainMap->nWidth,
    ptTerrainMap->nWidth,
    ptTerrainMap->nHeight,
    3,
    0,
    0,
    ptTerrainMap->pbLightmap);
  ptTerrainMap->isTerrainLightmapAllocated = true;
  TerrainMap_isUpdated = 1;
  isHeightmapResource = ptTerrainMap->isHeightmapResource;
  ptTerrainMap->isLightmapResource = false;
  if ( isHeightmapResource == false )
  {
    pvHeightmap = ptTerrainMap->pvHeightmap;
    if ( pvHeightmap )
    {
      v24 = *(_DWORD *)((unsigned int)(pvHeightmap - 1) & 0xFFFFFFFC);
      --Mem_nCurrentAllocations;
      Node_Remove((_DWORD **)v24);
      memset(*(void **)(v24 + 8), 0xCDu, *(_DWORD *)(v24 + 16));
      free((void *)v24);
    }
    ptTerrainMap->pvHeightmap = nullptr;
  }
  if ( ptTerrainMap->isMaterialmapResource == false )
  {
    piMaterialmap = ptTerrainMap->piMaterialmap;
    if ( piMaterialmap )
    {
      v26 = *(_DWORD *)((unsigned int)(piMaterialmap - 4) & 0xFFFFFFFC);
      --Mem_nCurrentAllocations;
      Node_Remove((_DWORD **)v26);
      memset(*(void **)(v26 + 8), 0xCDu, *(_DWORD *)(v26 + 16));
      free((void *)v26);
    }
    ptTerrainMap->piMaterialmap = nullptr;
  }
  ptTerrainMap->isHeightmapResource = false;
  ptTerrainMap->isMaterialmapResource = false;
  ptTerrainMap->pvHeightmap = igi2_frame.v30;
  ptTerrainMap->piMaterialmap = igi2_frame.v40;
  TerrainMap_SoftenHeightmapEdges(ptTerrain, ptTerrainMap, 0.05000000074505806);
}

// source: h/2/terrain.c:2712  [anchor-callee]
void __cdecl Terrain_UpdateSubmaps(struct Terrain_t *ptTerrain)
{
  struct QTask_s *FirstChildOfType; // esi
  int ptTail; // ebx
  int ptMiddle; // edi
  struct QReference_s **p_ptMiddle; // ebp
  _DWORD ***v5; // eax
  int v6; // ebx
  int v7; // edi
  double v8; // st5
  double v9; // st4
  char v10; // bl
  struct QTask_s *NextSiblingOfType; // edx
  char i; // bp
  double v13; // st3
  double v14; // st2
  double v15; // st3
  double v16; // st2
  bool v17; // cc
  unsigned __int16 v18; // cx
  unsigned __int16 v19; // di
  struct QTask_s *v20; // eax
  struct QTask_s *v21; // ebx
  int v22; // ebp
  double v23; // st6
  struct QTask_s *v24; // esi
  double v25; // st7
  struct QTask_s *v26; // eax
  int nWidth; // [esp+14h] [ebp-5Ch]
  int nWidtha; // [esp+14h] [ebp-5Ch]
  int nHeight; // [esp+18h] [ebp-58h]
  _DWORD *vTexelWidth; // [esp+1Ch] [ebp-54h]
  float vTexelWidtha; // [esp+1Ch] [ebp-54h]
  int nY; // [esp+20h] [ebp-50h]
  int v33; // [esp+24h] [ebp-4Ch]
  int iMipMap; // [esp+28h] [ebp-48h]
  int iMipMapa; // [esp+28h] [ebp-48h]
  char iMap; // [esp+2Ch] [ebp-44h]
  int iMapa; // [esp+2Ch] [ebp-44h]
  float v38; // [esp+30h] [ebp-40h]
  int nX; // [esp+34h] [ebp-3Ch]
  int nXa; // [esp+34h] [ebp-3Ch]
  int nXb; // [esp+34h] [ebp-3Ch]
  float vMipMapTexelWidth; // [esp+38h] [ebp-38h]
  float vMipMapTexelWidtha; // [esp+38h] [ebp-38h]
  float vMipMapTexelHeight; // [esp+3Ch] [ebp-34h]
  float vMipMapTexelHeighta; // [esp+3Ch] [ebp-34h]
  float vTexelHeight; // [esp+40h] [ebp-30h]
  float v47; // [esp+44h] [ebp-2Ch]
  float v48; // [esp+48h] [ebp-28h]
  float v49; // [esp+4Ch] [ebp-24h]
  float vSubmapTexelHeight; // [esp+50h] [ebp-20h]

  FirstChildOfType = QTask_GetFirstChildOfType(&ptTerrain->tDynCubeObj.tQObj.tQTask, TerrainMap_eQTaskType);
  iMap = 0;
  if ( FirstChildOfType )
  {
    do
    {
      ptTail = (int)FirstChildOfType[2].tQTaskChildren.ptTail;
      ptMiddle = (int)FirstChildOfType[2].tQTaskRefList.ptMiddle;
      nWidth = ptTail;
      nHeight = ptMiddle;
      p_ptMiddle = &FirstChildOfType[4].tQTaskRefList.ptMiddle;
      iMipMap = 20;
      do
      {
        if ( *p_ptMiddle )
        {
          v5 = (_DWORD ***)((unsigned int)&(*p_ptMiddle)[-1].pxObject & 0xFFFFFFFC);
          --Mem_nCurrentAllocations;
          v6 = (int)*v5;
          Node_Remove(*v5);
          memset(*(void **)(v6 + 8), 0xCDu, *(_DWORD *)(v6 + 16));
          free((void *)v6);
          ptTail = nWidth;
          ptMiddle = nHeight;
          *p_ptMiddle = nullptr;
        }
        ++p_ptMiddle;
        --iMipMap;
      }
      while ( iMipMap );
      iMipMapa = 0;
      if ( ptTail > 0 )
      {
        vTexelWidth = &FirstChildOfType[4].tQTaskRefList.ptMiddle;
        do
        {
          if ( ptMiddle <= 0 )
            break;
          v38 = *(float *)&FirstChildOfType[4].tQTaskChildren.ptMiddle
              * 4096.0
              / (double)(int)FirstChildOfType[2].tQTaskChildren.ptTail;
          vTexelHeight = *(float *)&FirstChildOfType[4].tQTaskChildren.ptTail
                       * 4096.0
                       / (double)(int)FirstChildOfType[2].tQTaskRefList.ptMiddle;
          *vTexelWidth = Mem_AllocFn(ptTail * ptMiddle, 4);
          nY = 0;
          v33 = 0;
          do
          {
            v7 = 0;
            nX = 0;
            if ( ptTail > 0 )
            {
              do
              {
                vMipMapTexelWidth = *(float *)&FirstChildOfType[4].tQTaskChildren.ptMiddle * 4096.0 / (double)nWidth;
                vMipMapTexelHeight = *(float *)&FirstChildOfType[4].tQTaskChildren.ptTail * 4096.0 / (double)nHeight;
                v47 = v38 * 0.5;
                v8 = v47
                   - *(float *)&FirstChildOfType[4].tQTaskChildren.ptMiddle * 2048.0
                   + (double)nX * vMipMapTexelWidth
                   + *(double *)&FirstChildOfType[3].tQTaskChildren.ptTail;
                v48 = vTexelHeight * 0.5;
                v49 = (float)nY;
                v9 = v48
                   - *(float *)&FirstChildOfType[4].tQTaskChildren.ptTail * 2048.0
                   + v49 * vMipMapTexelHeight
                   + *(double *)&FirstChildOfType[3].tQTaskRefList.ptMiddle;
                v10 = 0;
                NextSiblingOfType = QTask_GetNextSiblingOfType(FirstChildOfType, TerrainMap_eQTaskType);
                for ( i = iMap + 1;
                      NextSiblingOfType;
                      NextSiblingOfType = QTask_GetNextSiblingOfType(NextSiblingOfType, TerrainMap_eQTaskType) )
                {
                  *(float *)&nXa = *(float *)&NextSiblingOfType[4].tQTaskChildren.ptMiddle
                                 * 4096.0
                                 / (double)(int)NextSiblingOfType[2].tQTaskChildren.ptTail;
                  if ( !NextSiblingOfType[2].ptNext )
                  {
                    if ( v38 >= (double)*(float *)&nXa )
                    {
                      v13 = *(float *)&nXa * 0.5;
                      v14 = *(float *)&NextSiblingOfType[4].tQTaskChildren.ptMiddle * 2048.0;
                      if ( v8 >= v13 - v14 + *(double *)&NextSiblingOfType[3].tQTaskChildren.ptTail - 4.0960001945495605
                        && v14 + v13 + *(double *)&NextSiblingOfType[3].tQTaskChildren.ptTail + 4.0960001945495605 >= vMipMapTexelWidth + v8 )
                      {
                        vSubmapTexelHeight = *(float *)&NextSiblingOfType[4].tQTaskChildren.ptTail
                                           * 4096.0
                                           / (double)(int)NextSiblingOfType[2].tQTaskRefList.ptMiddle;
                        v15 = vSubmapTexelHeight * 0.5;
                        v16 = *(float *)&NextSiblingOfType[4].tQTaskChildren.ptTail * 2048.0;
                        if ( v9 >= v15
                                 - v16
                                 + *(double *)&NextSiblingOfType[3].tQTaskRefList.ptMiddle
                                 - 4.0960001945495605
                          && v16 + v15 + *(double *)&NextSiblingOfType[3].tQTaskRefList.ptMiddle + 4.0960001945495605 >= vMipMapTexelHeight + v9 )
                        {
                          v10 = i;
                        }
                      }
                    }
                    ++i;
                  }
                }
                *(_BYTE *)(v33 + *vTexelWidth + v7++) = v10;
                nX = v7;
              }
              while ( v7 < nWidth );
              ptTail = nWidth;
            }
            v17 = ++nY < nHeight;
            v33 += ptTail;
          }
          while ( v17 );
          ptTail >>= 1;
          ptMiddle = nHeight >> 1;
          ++iMipMapa;
          ++vTexelWidth;
          nWidth = ptTail;
          nHeight >>= 1;
        }
        while ( ptTail > 0 );
      }
      *(_DWORD *)&FirstChildOfType[6].eQTaskType = iMipMapa;
      ++iMap;
      v18 = TerrainMap_eQTaskType;
      FirstChildOfType = QTask_GetNextSiblingOfType(FirstChildOfType, TerrainMap_eQTaskType);
    }
    while ( FirstChildOfType );
    v19 = v18;
    v20 = QTask_GetFirstChildOfType(&ptTerrain->tDynCubeObj.tQObj.tQTask, v18);
    v21 = v20;
    v22 = 1;
    *(float *)&nWidtha = *(float *)&v20[4].tQTaskChildren.ptMiddle * 4096.0 / (double)(int)v20[2].tQTaskChildren.ptTail;
    *(float *)&iMapa = *(float *)&v20[4].tQTaskChildren.ptTail * 4096.0 / (double)(int)v20[2].tQTaskRefList.ptMiddle;
    do
    {
      v23 = *(float *)&nWidtha
          / (*(float *)&v20[4].tQTaskChildren.ptMiddle
           * 4096.0
           / (double)(int)v20[2].tQTaskChildren.ptTail);
      if ( (int)(__int64)v23 > v22 )
        v22 = (__int64)v23;
      v20 = QTask_GetNextSiblingOfType(v20, v19);
    }
    while ( v20 );
    v24 = v21;
    do
    {
      if ( v24[2].tQTaskChildren.ptTail )
      {
        if ( v24[2].tQTaskRefList.ptMiddle )
        {
          vMipMapTexelHeighta = *(float *)&v24[4].tQTaskChildren.ptMiddle * 4096.0;
          vTexelWidtha = vMipMapTexelHeighta / (double)(int)v24[2].tQTaskChildren.ptTail;
          vMipMapTexelWidtha = *(float *)&v24[4].tQTaskChildren.ptTail * 4096.0;
          *(float *)&nXb = vMipMapTexelWidtha / (double)(int)v24[2].tQTaskRefList.ptMiddle;
          if ( vTexelWidtha != 0.0
            && *(float *)&nXb != 0.0
            && *(float *)&nWidtha != 0.0
            && *(float *)&iMapa != 0.0
            && *(float *)&nWidtha >= (double)vTexelWidtha )
          {
            v25 = (*(double *)&v24[3].tQTaskRefList.ptMiddle
                 - (vMipMapTexelWidtha - *(float *)&nXb) * 0.5
                 - (*(double *)&v21[3].tQTaskRefList.ptMiddle
                  - (*(float *)&v21[4].tQTaskChildren.ptTail * 4096.0 - *(float *)&iMapa) * 0.5))
                / *(float *)&iMapa;
            v24[6].tQTaskRefList.ptMiddle = (struct QReference_s *)(v22
                                                                  * (__int64)((*(double *)&v24[3].tQTaskChildren.ptTail
                                                                             - (vMipMapTexelHeighta - vTexelWidtha)
                                                                             * 0.5
                                                                             - (*(double *)&v21[3].tQTaskChildren.ptTail
                                                                              - (*(float *)&v21[4].tQTaskChildren.ptMiddle
                                                                               * 4096.0
                                                                               - *(float *)&nWidtha)
                                                                              * 0.5))
                                                                            / *(float *)&nWidtha
                                                                            + 0.5));
            v24[6].tQTaskRefList.ptTail = (struct QReference_s *)(v22 * (__int64)(v25 + 0.5));
            _BitScanReverse((unsigned int *)&v26, v22 / (int)(__int64)(*(float *)&nWidtha / vTexelWidtha));
            v24[6].ptParent = v26;
          }
        }
      }
      v24 = QTask_GetNextSiblingOfType(v24, v19);
    }
    while ( v24 );
  }
}

// source: h/2/terrain.c:2881  [anchor-caller]
void __cdecl Terrain_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct real64x3_t v40[2]; };
    struct { char igi2_o1[52]; float vHalfX; };
    struct { char igi2_o2[56]; float vHalfY; };
    struct { char igi2_o3[60]; int iBrush; };
    struct { char igi2_o4[64]; float v44; };
    struct { char igi2_o5[68]; float v45; };
    struct { char igi2_o6[72]; float v46; };
    struct { char igi2_o7[76]; int v47; };
    struct { char igi2_o8[80]; struct RandomState_s tRandomState; };
    struct { char igi2_o9[92]; struct real64x3_t tPos; };
    char igi2_extent[136];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int ptTail; // eax
  double v4; // st7
  unsigned __int16 v5; // di
  struct TerrainMap_t *i; // esi
  struct TerrainMap_t *j; // ebx
  struct TerrainMap_t *k; // ebx
  unsigned __int16 v9; // dx
  struct QTask_s *m; // esi
  DWORD PerformanceCounter; // eax
  DWORD v12; // ebx
  int v13; // esi
  int v14; // edi
  int v15; // eax
  unsigned int v16; // ebx
  unsigned int v17; // esi
  int v18; // edi
  int v19; // esi
  unsigned int v20; // ebx
  int v21; // edi
  int v22; // esi
  unsigned int v23; // ebx
  int v24; // edi
  int v25; // esi
  unsigned int v26; // ebx
  long double v27; // st7
  double v28; // st7
  double v29; // st6
  int v30; // edi
  int v31; // esi
  double v32; // st5
  struct QReference_s *ptHead; // eax
  int v34; // ecx
  unsigned __int16 v35; // dx
  struct TerrainMap_t *n; // ebx
  int v37; // esi
  struct QTask_s *ii; // eax
  int jj; // esi
  struct TerrainMap_t *ptQTaska = *(struct TerrainMap_t * *)&ptQTask; // [esp+84h] [ebp+4h] ARGSLOT
  float ptQTaskb = *(float *)&ptQTask; // [esp+84h] [ebp+4h] ARGSLOT
  unsigned int ptQTaskc = *(unsigned int *)&ptQTask; // [esp+84h] [ebp+4h] ARGSLOT

  ptTail = (int)ptQTask[6].tQTaskRefList.ptTail;
  if ( ptTail >= 1 )
  {
    if ( ptTail > 4 )
      ptTail = 4;
  }
  else
  {
    ptTail = 1;
  }
  ptQTask[6].tQTaskRefList.ptTail = (struct QReference_s *)ptTail;
  if ( *(float *)&ptQTask[4].tQTaskChildren.ptHead >= 1.0 )
  {
    if ( *(float *)&ptQTask[4].tQTaskChildren.ptHead <= 10.0 )
      v4 = *(float *)&ptQTask[4].tQTaskChildren.ptHead;
    else
      v4 = 10.0;
  }
  else
  {
    v4 = 1.0;
  }
  *(float *)&ptQTask[4].tQTaskChildren.ptHead = v4;
  TerrainMap_isMipMapsUpdated = 0;
  Terrain_SetActiveHeightmaps(ptQTask);
  if ( ptQTask[5].tQTaskChildren.ptMiddle )
  {
    v5 = TerrainMap_eQTaskType;
    ptQTaska = nullptr;
    for ( i = (struct TerrainMap_t *)QTask_GetFirstChildOfType(ptQTask, TerrainMap_eQTaskType);
          i;
          i = (struct TerrainMap_t *)QTask_GetNextSiblingOfType(&i->tQTask, v5) )
    {
      TerrainMap_SoftenHeightmapEdges((struct Terrain_t *)ptQTask, i, 0.05000000074505806);
    }
    for ( j = (struct TerrainMap_t *)QTask_GetFirstChildOfType(ptQTask, v5);
          j;
          j = (struct TerrainMap_t *)QTask_GetNextSiblingOfType(&j->tQTask, v5) )
    {
      if ( ptQTaska )
      {
        TerrainMap_ResampleAndAlign(j, ptQTaska, (struct Terrain_t *)ptQTask);
        v5 = TerrainMap_eQTaskType;
      }
      else
      {
        ptQTaska = j;
      }
    }
    for ( k = (struct TerrainMap_t *)QTask_GetFirstChildOfType(ptQTask, v5);
          k;
          k = (struct TerrainMap_t *)QTask_GetNextSiblingOfType(&k->tQTask, TerrainMap_eQTaskType) )
    {
      TerrainMap_Syncronize((struct Terrain_t *)ptQTask, k);
    }
    Terrain_UpdateSubmaps((struct Terrain_t *)ptQTask);
    ptQTask[5].tQTaskRefList.ptTail = (struct QReference_s *)1;
    TerrainMap_isUpdated = 1;
  }
  if ( ptQTask[5].tQTaskRefList.ptTail && !ptQTask[918].tQTaskRefList.ptMiddle )
  {
    LODWORD(igi2_frame.v40[1].vY) = 1;
    HIDWORD(igi2_frame.v40[1].vX) = ptQTask;
    ptQTask[5].tQTaskRefList.ptTail = nullptr;
    Terrain_CalculateLightmaps((struct Terrain_t *)HIDWORD(igi2_frame.v40[1].vX), SLODWORD(igi2_frame.v40[1].vY));
  }
  if ( ptQTask[5].tQTaskRefList.ptMiddle && !ptQTask[918].tQTaskRefList.ptMiddle )
  {
    LODWORD(igi2_frame.v40[1].vY) = 0;
    HIDWORD(igi2_frame.v40[1].vX) = ptQTask;
    ptQTask[5].tQTaskRefList.ptMiddle = nullptr;
    Terrain_CalculateLightmaps((struct Terrain_t *)HIDWORD(igi2_frame.v40[1].vX), SLODWORD(igi2_frame.v40[1].vY));
  }
  if ( ptQTask[5].tQTaskChildren.ptTail || ptQTask[5].tQTaskRefList.ptHead )
  {
    v9 = TerrainMap_eQTaskType;
    for ( m = QTask_GetFirstChildOfType(ptQTask, TerrainMap_eQTaskType); m; m = QTask_GetNextSiblingOfType(m, v9) )
    {
      memset(m[9].tQTaskChildren.ptMiddle, 0, (int)m[2].tQTaskChildren.ptTail * (int)m[2].tQTaskRefList.ptMiddle);
      memset(m[7].ptNext, 0, 4 * (int)m[2].tQTaskChildren.ptTail * (int)m[2].tQTaskRefList.ptMiddle);
    }
    TerrainMap_isUpdated = 1;
  }
  if ( ptQTask[5].tQTaskRefList.ptHead )
  {
    igi2_frame.vHalfX = *(float *)&ptQTask[4].ptParent * 2048.0;
    igi2_frame.vHalfY = igi2_frame.vHalfX;
    if ( Timer_isPerformanceCounter )
      PerformanceCounter = Timer_GetPerformanceCounter();
    else
      PerformanceCounter = GetTickCount();
    v12 = PerformanceCounter - Timer_nStartTime;
    v13 = (PerformanceCounter - Timer_nStartTime) << 15;
    v14 = 2146516173 - ((PerformanceCounter - Timer_nStartTime) << 9);
    v15 = *(_DWORD *)&ptQTask[6].eQTaskType;
    v16 = v12 ^ 0xC8FB1A07;
    v17 = v13 + 971667286;
    igi2_frame.iBrush = 0;
    if ( v15 > 0 )
    {
      igi2_frame.v44 = igi2_frame.vHalfX + igi2_frame.vHalfX;
      igi2_frame.v45 = igi2_frame.vHalfY + igi2_frame.vHalfY;
      while ( 1 )
      {
        v18 = (v16 >> 7) ^ v14;
        v19 = v18 ^ v17;
        v20 = v19 + v16;
        ptQTaskb = (double)(unsigned __int16)v20 * 0.0000152587890625;
        v21 = (v20 >> 7) ^ v18;
        v22 = v21 ^ v19;
        v23 = v22 + v20;
        igi2_frame.v46 = (double)(unsigned __int16)v23 * 0.0000152587890625;
        v24 = (v23 >> 7) ^ v21;
        v25 = v24 ^ v22;
        v26 = v25 + v23;
        v27 = (pow(ptQTaskb, 2.0)
             * (*(float *)&ptQTask[6].tQTaskChildren.ptTail - *(float *)&ptQTask[6].tQTaskChildren.ptMiddle)
             + *(float *)&ptQTask[6].tQTaskChildren.ptMiddle)
            * 2048.0;
        igi2_frame.v47 = (unsigned __int16)v26;
        *(float *)&ptQTaskc = v27;
        v28 = *(float *)&ptQTaskc + *(float *)&ptQTaskc;
        v29 = (double)(unsigned __int16)v26;
        v30 = (v26 >> 7) ^ v24;
        v31 = v30 ^ v25;
        v16 = v31 + v26;
        v32 = *(double *)&ptQTask[3].ptNext - igi2_frame.vHalfX;
        igi2_frame.v47 = (unsigned __int16)v16;
        igi2_frame.tRandomState.anRandom[2] = v30;
        igi2_frame.tRandomState.anRandom[1] = v31;
        igi2_frame.tPos.vX = v29 * 0.0000152587890625 * (igi2_frame.v44 - v28) + v32 + *(float *)&ptQTaskc;
        ptHead = ptQTask[3].tQTaskRefList.ptHead;
        LODWORD(igi2_frame.tPos.vZ) = ptQTask[3].tQTaskChildren.ptTail;
        HIDWORD(igi2_frame.tPos.vZ) = ptHead;
        igi2_frame.tPos.vY = (double)(unsigned __int16)v16 * 0.0000152587890625 * (igi2_frame.v45 - v28)
                + *(double *)&ptQTask[3].tQTaskChildren.ptHead
                - igi2_frame.vHalfY
                + *(float *)&ptQTaskc;
        qmemcpy((char *)&igi2_frame.v40[0].vY + 4, &igi2_frame.tPos, sizeof(struct real64x3_t));
        *(float *)&igi2_frame.v40[0].vY = (*(float *)&ptQTask[6].tQTaskRefList.ptMiddle - *(float *)&ptQTask[6].tQTaskRefList.ptHead)
                             * igi2_frame.v46
                             + *(float *)&ptQTask[6].tQTaskRefList.ptHead;
        *(_QWORD *)&igi2_frame.v40[0].vX = ptQTaskc | 0x3DCCCCCD00000000LL;
        Terrain_ApplyBrush(
          (struct Terrain_t *)ptQTask,
          TERRAIN_HEIGHTEDITMODE_LIFT,
          TERRAIN_MATERIALEDITMODE_NONE,
          igi2_frame.v40[0],
          *(float *)&igi2_frame.v40[1].vX,
          *((float *)&igi2_frame.v40[1].vX + 1),
          *(float *)&igi2_frame.v40[1].vY);
        v34 = *(_DWORD *)&ptQTask[6].eQTaskType;
        if ( ++igi2_frame.iBrush >= v34 )
          break;
        v14 = igi2_frame.tRandomState.anRandom[2];
        v17 = igi2_frame.tRandomState.anRandom[1];
      }
    }
    LOBYTE(ptQTask[5].ptNext) = 1;
  }
  ((void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[DiscardTask_eUpdateDiscardMeshQTaskEvent][ptQTask->eQTaskType].pfHandler)(ptQTask);
  if ( ptQTask[5].tQTaskChildren.ptHead )
    Terrain_UpdateSubmaps((struct Terrain_t *)ptQTask);
  v35 = TerrainMap_eQTaskType;
  if ( ptQTask[5].ptPrev )
  {
    for ( n = (struct TerrainMap_t *)QTask_GetFirstChildOfType(ptQTask, TerrainMap_eQTaskType);
          n;
          n = (struct TerrainMap_t *)QTask_GetNextSiblingOfType(&n->tQTask, TerrainMap_eQTaskType) )
    {
      TerrainMap_Syncronize((struct Terrain_t *)ptQTask, n);
      v35 = TerrainMap_eQTaskType;
    }
  }
  v37 = 0;
  for ( ii = QTask_GetFirstChildOfType(ptQTask, v35); ii; ii = QTask_GetNextSiblingOfType(ii, v35) )
    *((_DWORD *)&igi2_frame.tPos.vX + v37++) = ii;
  for ( jj = v37 - 1; jj >= 0; --jj )
    TerrainMap_MakeMinMaxHeightMipMaps((struct TerrainMap_t **)&igi2_frame.tPos, jj);
}

// source: h/2/terrain.c:3048  [anchor-caller]
void __cdecl Terrain_UpdateInternalDataHandlerAfterLoad(struct QTask_s *ptQTask)
{
  Terrain_ptActiveTerrain = (struct Terrain_t *)ptQTask;
  Terrain_SetActiveHeightmaps(ptQTask);
  Terrain_MakeMipMaps(ptQTask);
}

// source: h/2/terrain.c:3069  [anchor-caller]
void __cdecl Terrain_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *ptParent; // ecx
  struct QTaskList_s *v3; // eax
  float ptDiscardMeshContext; // [esp+0h] [ebp-10h]
  float ptPos; // [esp+4h] [ebp-Ch]

  ptQTask[2].ptParent = (struct QTask_s *)World_ptActiveWorld;
  ptQTask[4].tQTaskChildren.ptHead = (struct QTask_s *)1065353216;
  ptQTask[4].tQTaskRefList.ptHead = (struct QReference_s *)1065353216;
  ptQTask[5].ptParent = nullptr;
  *(_DWORD *)&ptQTask[5].eQTaskType = 0;
  ptQTask[6].ptNext = nullptr;
  ptQTask[6].ptPrev = nullptr;
  ptQTask[6].tQTaskChildren.ptHead = nullptr;
  ptQTask[6].ptParent = nullptr;
  ptQTask[4].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[919].tQTaskChildren.ptTail = nullptr;
  ptQTask[919].tQTaskRefList.ptHead = nullptr;
  ptQTask[919].ptPrev = nullptr;
  ptQTask[918].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[4].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[4].ptParent = (struct QTask_s *)1148846080;
  *(_DWORD *)&ptQTask[4].eQTaskType = 1148846080;
  ptParent = ptQTask[2].ptParent;
  ptQTask[3].ptNext = nullptr;
  ptQTask[3].ptPrev = nullptr;
  ptQTask[3].tQTaskChildren.ptHead = nullptr;
  ptQTask[3].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[3].tQTaskChildren.ptTail = nullptr;
  ptQTask[3].tQTaskRefList.ptHead = nullptr;
  ptQTask[5].tQTaskChildren.ptTail = nullptr;
  ptQTask[5].tQTaskRefList.ptHead = nullptr;
  ptQTask[5].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[5].tQTaskRefList.ptTail = nullptr;
  v3 = Terrain_ptQTaskList;
  ptQTask[6].tQTaskRefList.ptTail = (struct QReference_s *)2;
  LOBYTE(ptQTask[5].ptNext) = 1;
  ptQTask[4].tQTaskChildren.ptTail = (struct QTask_s *)1120403456;
  ptQTask[4].tQTaskRefList.ptTail = (struct QReference_s *)1045220557;
  ptQTask[6].tQTaskChildren.ptMiddle = (struct QTask_s *)1092616192;
  ptQTask[6].tQTaskChildren.ptTail = (struct QTask_s *)1128792064;
  ptQTask[6].tQTaskRefList.ptHead = (struct QReference_s *)1063675494;
  ptQTask[6].tQTaskRefList.ptMiddle = (struct QReference_s *)1066192077;
  *(_DWORD *)&ptQTask[6].eQTaskType = 1000;
  ptParent[16].tQTaskRefList.ptMiddle = (struct QReference_s *)v3;
  QTaskList_Register(v3, (struct QTaskList_s *)ptQTask);
  ptPos = *(float *)&ptQTask[4].eQTaskType * 4096.0;
  ptDiscardMeshContext = *(float *)&ptQTask[4].ptParent * 4096.0;
  Discard2D_InitDiscardMeshContext(
    (struct DiscardMeshContext_s *)&ptQTask[7],
    (struct real64x3_t *)&ptQTask[3],
    ptDiscardMeshContext,
    ptPos);
  Terrain_MakeMipMaps(ptQTask);
  Terrain_SetActiveHeightmaps(ptQTask);
}

// source: h/2/terrain.c:3130  [anchor-caller]
void __cdecl Terrain_DeleteHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptTail; // eax
  struct QReference_s *ptHead; // ebx

  QTaskList_Remove(Terrain_ptQTaskList, ptQTask);
  ptTail = ptQTask[919].tQTaskChildren.ptTail;
  if ( ptTail )
  {
    TextWindow_Delete((struct TextWindow_s *)ptTail);
    ptHead = ptQTask[919].tQTaskRefList.ptHead;
    ptQTask[919].tQTaskChildren.ptTail = nullptr;
    FontManager_DeleteFont((struct QSprite_s *)ptHead);
    ptQTask[919].tQTaskRefList.ptHead = nullptr;
  }
}

// source: h/2/terrain.c:3200  [anchor-caller]
void __cdecl Terrain_EnterHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { unsigned __int8 **apiSubmap; };
    struct { float v27; };
    struct { char igi2_o2[4]; _BYTE *v29; };
    struct { char igi2_o3[8]; double v30[5]; };
    struct { char igi2_o4[48]; _DWORD v31[18]; };
    struct { char igi2_o5[120]; _DWORD v32[9]; };
    struct { char igi2_o6[156]; float v33; };
    struct { char igi2_o7[160]; float v34; };
    struct { char igi2_o8[164]; float v35; };
    struct { char igi2_o9[168]; _DWORD v36[17]; };
    struct { char igi2_o10[236]; _DWORD v37[4]; };
    struct { char igi2_o11[252]; _DWORD v38[76]; };
    struct { char igi2_o12[556]; _BYTE v39[1084]; };
    struct { char igi2_o13[1640]; char v40; };
    struct { char igi2_o14[1756]; int v41; };
    struct { char igi2_o15[1760]; BOOL v42; };
    char igi2_extent[1772];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct DrawLightmapContext_t *v2; // ebx
  float vFOVX; // eax
  struct QReference_s *ptMiddle; // eax
  double v5; // st7
  struct QTask_s *v6; // ecx
  double v7; // st7
  double v8; // st7
  double v9; // st7
  struct TerrainMap_t *FirstChildOfType; // eax
  int v11; // esi
  _DWORD *v12; // edx
  float *v13; // edi
  struct TexInfo_s *p_tLightmapTexInfo; // ecx
  int v15; // ecx
  unsigned __int16 v16; // cx
  unsigned __int16 v17; // si
  struct QTask_s *NextSiblingOfType; // eax
  unsigned __int8 i; // dl
  struct QTask_s *ptHead; // ebp
  int v21; // ecx
  int v22; // edx
  struct QTask_s *v23; // eax
  int v24; // esi
  void (__cdecl *pfHandler)(int, _DWORD *); // eax
  int v26; // edx

  if ( Terrain_nActiveHeightmaps > 0 )
  {
    v2 = Terrain_ptDrawLightmapContext;
    if ( Terrain_ptDrawLightmapContext )
    {
      vFOVX = Terrain_ptDrawLightmapContext->vFOVX;
      qmemcpy(igi2_frame.v31, &Terrain_ptDrawLightmapContext->tOrientation, 0x28u);
      qmemcpy(igi2_frame.v30, &Terrain_ptDrawLightmapContext->tPos, 0x18u);
      igi2_frame.v27 = vFOVX;
    }
    else
    {
      ptMiddle = ptQTask[918].tQTaskRefList.ptMiddle;
      qmemcpy(igi2_frame.v31, &TransContext_tActiveTransContext, 0x28u);
      qmemcpy(igi2_frame.v30, &TransContext_tActiveTransContext.tPos, 0x18u);
      igi2_frame.v27 = TransContext_tActiveTransContext.vFOVX;
      if ( ptMiddle )
      {
        Line_DrawLine3D(
          &Terrain_tTempLineStart,
          &Terrain_tTempLineEnd,
          &Terrain_tTempLineColor,
          1.0,
          &Terrain_tTempLineColor,
          1.0);
        v2 = Terrain_ptDrawLightmapContext;
      }
    }
    v5 = *(float *)&ptQTask[4].ptParent * 4096.0;
    v6 = ptQTask[4].tQTaskChildren.ptMiddle;
    igi2_frame.v38[24] = SLOBYTE(ptQTask[5].ptNext);
    igi2_frame.v34 = v5;
    v7 = *(float *)&ptQTask[4].eQTaskType;
    igi2_frame.v32[5] = igi2_frame.v31[5];
    igi2_frame.v38[25] = ptQTask + 7;
    igi2_frame.v32[7] = v6;
    igi2_frame.v35 = v7 * 4096.0;
    v8 = *(double *)&ptQTask[3].ptNext;
    igi2_frame.v32[0] = Terrain_VertexFunction;
    igi2_frame.v32[8] = 923306121;
    *(float *)&igi2_frame.v32[1] = v8 - igi2_frame.v30[0];
    igi2_frame.v32[4] = igi2_frame.v31[2];
    v9 = *(double *)&ptQTask[3].tQTaskChildren.ptHead;
    igi2_frame.v32[6] = igi2_frame.v31[8];
    *(float *)&igi2_frame.v32[2] = v9 - igi2_frame.v30[1];
    *(float *)&igi2_frame.v32[3] = *(double *)&ptQTask[3].tQTaskChildren.ptTail - igi2_frame.v30[2];
    igi2_frame.v33 = ((1.2999999523162842 - *(float *)&ptQTask[4].tQTaskRefList.ptTail * 4.0) * Terrain_vManualDetail
         + *(float *)&ptQTask[4].tQTaskRefList.ptTail * 4.0
         - 0.15000000596046448
         - 1.5)
        * Terrain_vManualDetail
        + 0.5;
    if ( igi2_frame.v27 != 1.0 )
      igi2_frame.v33 = pow(igi2_frame.v27, 0.4000000059604645) * igi2_frame.v33;
    FirstChildOfType = (struct TerrainMap_t *)QTask_GetFirstChildOfType(ptQTask, TerrainMap_eQTaskType);
    v11 = 0;
    if ( FirstChildOfType && FirstChildOfType->pvHeightmap )
    {
      v12 = igi2_frame.v39;
      v13 = (float *)&igi2_frame.v40;
      igi2_frame.v29 = igi2_frame.v39;
      do
      {
        if ( v11 >= 10 )
          break;
        igi2_frame.v42 = v2 != nullptr;
        if ( FirstChildOfType->pbLightmap )
          p_tLightmapTexInfo = &FirstChildOfType->tLightmapTexInfo;
        else
          p_tLightmapTexInfo = nullptr;
        igi2_frame.v38[v11 + 4] = p_tLightmapTexInfo;
        *(float *)&igi2_frame.v38[2 * v11 + 8] = FirstChildOfType->tPos.vX
                                    - FirstChildOfType->vWorldWidth * 2048.0
                                    - *(double *)&ptQTask[3].ptNext;
        *(float *)&igi2_frame.v38[2 * v11 + 9] = FirstChildOfType->tPos.vY
                                    - FirstChildOfType->vWorldHeight * 2048.0
                                    - *(double *)&ptQTask[3].tQTaskChildren.ptHead;
        *(float *)&igi2_frame.v38[2 * v11 + 16] = 1.0 / (FirstChildOfType->vWorldWidth * 4096.0);
        *(float *)&igi2_frame.v38[2 * v11 + 17] = 1.0 / (FirstChildOfType->vWorldHeight * 4096.0);
        igi2_frame.v38[v11 + 46] = FirstChildOfType->pvHeightmap;
        igi2_frame.v38[v11 + 66] = FirstChildOfType->avDeltaZ;
        igi2_frame.v38[v11 + 56] = &FirstChildOfType->tMinMaxHeightData;
        *(_DWORD *)&igi2_frame.v39[4 * v11 + 960] = FirstChildOfType->piMaterialmap;
        *(float *)&igi2_frame.v38[v11 + 26] = FirstChildOfType->vWorldWidth * 4096.0;
        *(float *)&igi2_frame.v38[v11 + 36] = FirstChildOfType->vWorldHeight * 4096.0;
        *(_DWORD *)&igi2_frame.v39[8 * v11 + 1000] = FirstChildOfType->nWidth;
        *(_DWORD *)&igi2_frame.v39[8 * v11 + 1004] = FirstChildOfType->nHeight;
        *(_DWORD *)&igi2_frame.v39[4 * v11 + 920] = FirstChildOfType->nNumMipMaps;
        v15 = 0;
        if ( FirstChildOfType->nNumMipMaps > 0 )
        {
          igi2_frame.apiSubmap = FirstChildOfType->apiSubmap;
          do
          {
            *v12 = *igi2_frame.apiSubmap++;
            ++v15;
            ++v12;
          }
          while ( v15 < FirstChildOfType->nNumMipMaps );
          v2 = Terrain_ptDrawLightmapContext;
        }
        *(_DWORD *)&igi2_frame.v39[8 * v11 + 800] = FirstChildOfType->tSubmapPos.nX;
        *(_DWORD *)&igi2_frame.v39[8 * v11 + 804] = FirstChildOfType->tSubmapPos.nY;
        v16 = TerrainMap_eQTaskType;
        *(_DWORD *)&igi2_frame.v39[4 * v11 + 880] = FirstChildOfType->nSubmapShift;
        *(v13 - 1) = FirstChildOfType->tPos.vX - *(double *)&ptQTask[3].ptNext;
        *v13 = FirstChildOfType->tPos.vY - *(double *)&ptQTask[3].tQTaskChildren.ptHead;
        v13[1] = FirstChildOfType->tPos.vZ - *(double *)&ptQTask[3].tQTaskChildren.ptTail;
        FirstChildOfType->bColor = -1;
        Terrain_aptActiveHeightmap[v11] = FirstChildOfType;
        FirstChildOfType = (struct TerrainMap_t *)QTask_GetNextSiblingOfType(&FirstChildOfType->tQTask, v16);
        v12 = igi2_frame.v29 + 80;
        ++v11;
        v13 += 3;
        igi2_frame.v29 += 80;
      }
      while ( FirstChildOfType );
      igi2_frame.v41 = v11;
      memset(igi2_frame.v36, 0, 0x40u);
      memset(igi2_frame.v37, 0, sizeof(igi2_frame.v37));
      memset(igi2_frame.v38, 0, 16);
      Terrain_nActiveHeightmaps = v11;
      v17 = TerrainMaterial_eQTaskType;
      NextSiblingOfType = QTask_GetFirstChildOfType(ptQTask, TerrainMaterial_eQTaskType);
      for ( i = 0; NextSiblingOfType; ++i )
      {
        igi2_frame.v36[(int)NextSiblingOfType[1].ptPrev] = NextSiblingOfType;
        *((_BYTE *)igi2_frame.v37 + i) = NextSiblingOfType[1].ptPrev;
        *((_BYTE *)igi2_frame.v38 + (unsigned int)NextSiblingOfType[1].ptPrev) = i;
        NextSiblingOfType = QTask_GetNextSiblingOfType(NextSiblingOfType, v17);
      }
      igi2_frame.v36[16] = i;
      if ( igi2_frame.v41 )
      {
        Terrain_ptActiveTerrain = (struct Terrain_t *)ptQTask;
        if ( !TerrainMap_isMipMapsUpdated )
          Terrain_MakeMipMaps(ptQTask);
        RenderMode_tActiveRenderMode.apfRenderModeMethod[TerrainRender_eDrawTerrainMethod](igi2_frame.v32);
        v2 = Terrain_ptDrawLightmapContext;
      }
      if ( !v2 )
      {
        ptHead = ptQTask->tQTaskChildren.ptHead;
        qmemcpy(igi2_frame.v31, &ptQTask[1], 0x18u);
        *(_QWORD *)&igi2_frame.v30[0] = 1065353216;
        igi2_frame.v30[1] = 0.0;
        *(_QWORD *)&igi2_frame.v30[2] = 1065353216;
        igi2_frame.v30[3] = 0.0;
        *(_QWORD *)&igi2_frame.v30[4] = 1065353216;
        qmemcpy(&igi2_frame.v31[6], igi2_frame.v30, 0x28u);
        if ( ptHead->ptNext )
        {
          v21 = (int)ptHead;
          if ( ptHead )
          {
            v22 = QTask_nProtectedQTaskStackOffset;
            do
            {
              if ( *(_DWORD *)v21 )
                v23 = **(_DWORD **)v21 != 0 ? *(struct QTask_s **)v21 : nullptr;
              else
                v23 = nullptr;
              v24 = MagicObj_eMagicObjEnterEvent;
              QTask_atProtectedQTaskStack[v22].ptQTask = v23;
              pfHandler = (void (__cdecl *)(int, _DWORD *))QTask_aatQTaskFinalEvent[v24][*(unsigned __int16 *)(v21 + 36)].pfHandler;
              v26 = v22 + 1;
              QTask_nProtectedQTaskStackOffset = v26;
              if ( pfHandler )
              {
                pfHandler(v21, igi2_frame.v31);
                v26 = QTask_nProtectedQTaskStackOffset;
              }
              v21 = dword_849C7DC[v26];
              v22 = v26 - 1;
              QTask_nProtectedQTaskStackOffset = v22;
            }
            while ( v21 );
          }
        }
      }
    }
  }
}

// source: h/2/terrain.c:3538  [anchor-caller]
void __cdecl Terrain_GetNextZHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { float vInX; };
    struct { char igi2_o1[4]; float vInY; };
    struct { char igi2_o2[35]; unsigned __int8 iLightMap; };
    struct { char igi2_o3[36]; int iLine; };
    struct { char igi2_o4[40]; struct real64x3_t *ptStart; };
    struct { char igi2_o5[44]; double *v34; };
    struct { char igi2_o6[48]; float vRelativeZ; };
    struct { char igi2_o7[52]; double vDistance; };
    struct { char igi2_o8[60]; double vActualZ; };
    struct { char igi2_o9[68]; struct real32x3_t tWorldPos; };
    struct { char igi2_o10[80]; struct real32x3_t tNormal; };
    struct { char igi2_o11[92]; struct real64x3_t tDelta; };
    char igi2_extent[120];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v2; // ecx
  int v3; // ebx
  struct real64x3_t *v4; // esi
  int v5; // edi
  struct QTask_s *v6; // ebp
  double *v7; // edi
  double v8; // st7
  double v9; // st6
  double vZ; // st5
  double v11; // st4
  int v12; // edx
  double v13; // st7
  int v14; // ecx
  int v15; // eax
  int v16; // edx
  float v17; // ecx
  double v18; // st7
  double v19; // st6
  double v20; // st5
  unsigned __int16 v21; // dx
  struct QTask_s *FirstChildOfType; // eax
  struct QTask_s *v23; // edi
  float vX; // eax
  float v25; // edx
  float vY; // ecx
  unsigned int ptNext; // eax
  bool v28; // cc

  v2 = *((_DWORD *)pxContext + 2);
  v3 = *((_DWORD *)pxContext + 9);
  v4 = *(struct real64x3_t **)pxContext;
  v5 = *((_DWORD *)pxContext + 1);
  igi2_frame.ptStart = *(struct real64x3_t **)pxContext;
  igi2_frame.iLine = 0;
  if ( v2 > 0 )
  {
    v6 = ptQTask;
    v7 = (double *)(v5 + 16);
    igi2_frame.v34 = v7;
    do
    {
      igi2_frame.vInY = v4->vY - *(double *)&v6[3].tQTaskChildren.ptHead;
      igi2_frame.vInX = v4->vX - *(double *)&v6[3].ptNext;
      Terrain_VertexFunction(
        &igi2_frame.vRelativeZ,
        &igi2_frame.tNormal,
        (unsigned int *)&igi2_frame.vDistance,
        (unsigned __int8 *)&ptQTask,
        &igi2_frame.iLightMap,
        igi2_frame.vInX,
        igi2_frame.vInY,
        0.0);
      v8 = igi2_frame.vRelativeZ + *(double *)&v6[3].tQTaskChildren.ptTail;
      igi2_frame.vActualZ = v8;
      if ( v4->vZ <= *v7 )
      {
        v9 = *v7;
        vZ = v4->vZ;
      }
      else
      {
        v9 = v4->vZ;
        vZ = *v7;
      }
      v11 = v4->vZ - v8;
      if ( v11 < 0.0 )
        v11 = -v11;
      igi2_frame.vDistance = v11;
      if ( v8 >= vZ && v8 <= v9 )
      {
        igi2_frame.tWorldPos.vX = v4->vX;
        igi2_frame.tWorldPos.vY = v4->vY;
        igi2_frame.tWorldPos.vZ = v8;
        if ( DiscardTask_IsDiscardVertex(&igi2_frame.tWorldPos) == false
          && (!*(_DWORD *)(v3 + 92) || igi2_frame.vDistance < *(double *)(v3 + 96)) )
        {
          v12 = LODWORD(igi2_frame.vActualZ);
          *(_DWORD *)(v3 + 92) = 1;
          *(_DWORD *)v3 = v6;
          qmemcpy((void *)(v3 + 8), v4, 0x18u);
          v13 = *(double *)(v3 + 8);
          v14 = HIDWORD(igi2_frame.vActualZ);
          v15 = HIDWORD(igi2_frame.vDistance);
          *(_DWORD *)(v3 + 24) = v12;
          v16 = LODWORD(igi2_frame.vDistance);
          *(_DWORD *)(v3 + 28) = v14;
          v17 = Terrain_vLightIntensity;
          v18 = v13 - *(double *)&v6[3].ptNext;
          v19 = *(double *)(v3 + 16) - *(double *)&v6[3].tQTaskChildren.ptHead;
          v20 = igi2_frame.vActualZ - *(double *)&v6[3].tQTaskChildren.ptTail;
          *(_DWORD *)(v3 + 96) = v16;
          v21 = TerrainMaterial_eQTaskType;
          *(_DWORD *)(v3 + 100) = v15;
          igi2_frame.tDelta.vZ = v20;
          *(_DWORD *)(v3 + 88) = 0;
          *(float *)(v3 + 32) = v18;
          *(float *)(v3 + 112) = v17;
          *(float *)(v3 + 36) = v19;
          *(float *)(v3 + 40) = igi2_frame.tDelta.vZ;
          FirstChildOfType = QTask_GetFirstChildOfType(v6, v21);
          if ( !FirstChildOfType )
            goto LABEL_17;
          v23 = (struct QTask_s *)(unsigned __int8)ptQTask;
          while ( FirstChildOfType[1].ptPrev != v23 )
          {
            FirstChildOfType = QTask_GetNextSiblingOfType(FirstChildOfType, v21);
            if ( !FirstChildOfType )
              goto LABEL_17;
          }
          ptNext = (unsigned int)FirstChildOfType[1].ptNext;
          if ( ptNext < 0x40 )
            *(_DWORD *)(v3 + 80) = World_ptActiveWorld->aptQMaterial[ptNext];
          else
LABEL_17:
            *(_DWORD *)(v3 + 80) = 0;
          vX = igi2_frame.tNormal.vX;
          v25 = igi2_frame.tNormal.vZ;
          v7 = igi2_frame.v34;
          *(_DWORD *)(v3 + 84) = 0;
          vY = igi2_frame.tNormal.vY;
          *(float *)(v3 + 56) = vX;
          *(float *)(v3 + 60) = vY;
          *(float *)(v3 + 64) = v25;
          *(float *)(v3 + 44) = vX;
          *(float *)(v3 + 48) = vY;
          *(float *)(v3 + 52) = v25;
          v4 = igi2_frame.ptStart;
        }
      }
      ++v4;
      v7 += 3;
      v3 += 120;
      v28 = ++igi2_frame.iLine < (int)(*((_DWORD *)pxContext + 2));
      igi2_frame.ptStart = v4;
      igi2_frame.v34 = v7;
    }
    while ( v28 );
  }
}

// source: h/2/terrain.c:3666  [anchor-caller]
void __cdecl Terrain_TraceLinesHandler1(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { float vInX; };
    struct { char igi2_o1[4]; float vInY; };
    struct { char igi2_o2[28]; float v153; };
    struct { char igi2_o3[28]; float v154; };
    struct { char igi2_o4[28]; float v155; };
    struct { char igi2_o5[28]; float v156; };
    struct { char igi2_o6[28]; int v157; };
    struct { char igi2_o7[28]; float v158; };
    struct { char igi2_o8[32]; float v159; };
    struct { char igi2_o9[32]; int v160; };
    struct { char igi2_o10[32]; int v161; };
    struct { char igi2_o11[36]; int vX; };
    struct { char igi2_o12[36]; int vY; };
    struct { char igi2_o13[40]; struct real32x3_t ptStart; };
    struct { char igi2_o14[52]; struct real32x3_t ptEnd; };
    struct { char igi2_o15[64]; int v166; };
    struct { char igi2_o16[68]; int v167; };
    struct { char igi2_o17[72]; struct real32x3_t ptOutPos; };
    struct { char igi2_o18[84]; float v169; };
    struct { char igi2_o19[88]; int v170; };
    struct { char igi2_o20[92]; unsigned int pbOutColor[2]; };
    struct { char igi2_o21[104]; float v172; };
    struct { char igi2_o22[108]; __int64 v173; };
    struct { char igi2_o23[116]; __int64 v174; };
    struct { char igi2_o24[128]; float v175; };
    struct { char igi2_o25[132]; float v176; };
    struct { char igi2_o26[139]; unsigned __int8 piOutMaterial; };
    struct { char igi2_o27[140]; double *v178; };
    struct { char igi2_o28[144]; int v179; };
    struct { char igi2_o29[148]; int v180; };
    struct { char igi2_o30[152]; double *v181; };
    struct { char igi2_o31[156]; struct QTask_s *v182; };
    struct { char igi2_o32[160]; struct real32x3_t v183; };
    struct { char igi2_o33[172]; double v184; };
    struct { char igi2_o34[187]; unsigned __int8 piOutLightmap; };
    struct { char igi2_o35[188]; double v186; };
    struct { char igi2_o36[196]; double pvOutRelativeZ; };
    struct { char igi2_o37[208]; int v188; };
    struct { char igi2_o38[212]; int v189; };
    struct { char igi2_o39[216]; int v190; };
    struct { char igi2_o40[220]; int v191; };
    struct { char igi2_o41[224]; int v192; };
    struct { char igi2_o42[228]; int v193; };
    struct { char igi2_o43[232]; int v194; };
    struct { char igi2_o44[236]; int v195; };
    struct { char igi2_o45[240]; int v196; };
    struct { char igi2_o46[244]; int v197; };
    struct { char igi2_o47[248]; int v198; };
    struct { char igi2_o48[252]; int v199; };
    struct { char igi2_o49[256]; int v200; };
    struct { char igi2_o50[260]; int v201; };
    struct { char igi2_o51[264]; int v202; };
    struct { char igi2_o52[268]; int v203; };
    struct { char igi2_o53[272]; int v204; };
    struct { char igi2_o54[276]; int v205; };
    struct { char igi2_o55[280]; int v206; };
    struct { char igi2_o56[284]; int v207; };
    struct { char igi2_o57[288]; int v208; };
    struct { char igi2_o58[292]; int v209; };
    struct { char igi2_o59[296]; int v210; };
    struct { char igi2_o60[300]; int v211; };
    struct { char igi2_o61[304]; int v212; };
    struct { char igi2_o62[308]; struct real32x3_t ptVertex0; };
    struct { char igi2_o63[320]; float v214; };
    struct { char igi2_o64[324]; float v215; };
    struct { char igi2_o65[328]; float v216; };
    struct { char igi2_o66[332]; float v217; };
    struct { char igi2_o67[336]; float v218; };
    struct { char igi2_o68[340]; float v219; };
    struct { char igi2_o69[344]; float v220; };
    struct { char igi2_o70[348]; float v221; };
    struct { char igi2_o71[352]; float v222; };
    struct { char igi2_o72[356]; struct real32x3_t ptVertex1; };
    struct { char igi2_o73[368]; float v224; };
    struct { char igi2_o74[372]; float v225; };
    struct { char igi2_o75[376]; float v226; };
    struct { char igi2_o76[380]; float v227; };
    struct { char igi2_o77[384]; float v228; };
    struct { char igi2_o78[388]; float v229; };
    struct { char igi2_o79[392]; float v230; };
    struct { char igi2_o80[396]; float v231; };
    struct { char igi2_o81[400]; float v232; };
    struct { char igi2_o82[404]; struct real32x3_t v233; };
    struct { char igi2_o83[416]; float v234; };
    struct { char igi2_o84[420]; float v235; };
    struct { char igi2_o85[424]; float v236; };
    struct { char igi2_o86[428]; float v237; };
    struct { char igi2_o87[432]; float v238; };
    struct { char igi2_o88[436]; float v239; };
    struct { char igi2_o89[440]; float v240; };
    struct { char igi2_o90[444]; float v241; };
    struct { char igi2_o91[448]; float v242; };
    struct { char igi2_o92[452]; struct real32x3_t ptVertex2; };
    struct { char igi2_o93[464]; float v244; };
    struct { char igi2_o94[468]; float v245; };
    struct { char igi2_o95[472]; float v246; };
    struct { char igi2_o96[476]; float v247; };
    struct { char igi2_o97[480]; float v248; };
    struct { char igi2_o98[484]; float v249; };
    struct { char igi2_o99[488]; float v250; };
    struct { char igi2_o100[492]; float v251; };
    struct { char igi2_o101[496]; float v252; };
    struct { char igi2_o102[500]; double v253[3]; };
    struct { char igi2_o103[524]; struct real32x3_t v254; };
    struct { char igi2_o104[536]; struct real32x3_t v255; };
    struct { char igi2_o105[548]; struct real32x3_t v256; };
    struct { char igi2_o106[560]; struct real32x3_t ptPos; };
    struct { char igi2_o107[588]; double v258; };
    char igi2_extent[600];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  _DWORD *v2; // esi
  int v3; // edx
  double *v4; // ecx
  struct QTask_s *FirstChildOfType; // ebp
  int v6; // eax
  double v7; // st7
  double v8; // st6
  double v9; // st7
  double v10; // st7
  double v11; // st7
  double v12; // st6
  double v13; // st7
  double v14; // st7
  double v15; // st6
  double v16; // st7
  double v17; // st7
  double v18; // st6
  double v19; // st7
  double v20; // st7
  double v21; // st6
  double v22; // st7
  double v23; // st7
  double v24; // st6
  double v25; // st7
  double v26; // st7
  double v27; // st6
  double v28; // st7
  double v29; // st7
  double v30; // st6
  double v31; // st7
  double v32; // st7
  double v33; // st6
  double v34; // st7
  double v35; // st7
  double v36; // st6
  double v37; // st5
  double v38; // st4
  int v39; // ecx
  double v40; // st7
  double v41; // st6
  float v42; // ebx
  int v43; // edi
  struct QTask_s *v44; // eax
  struct QTask_s *v45; // esi
  int v46; // ecx
  int v47; // edx
  int v48; // ebx
  int v49; // edi
  int v50; // edx
  int v51; // ebx
  int v52; // edi
  int v53; // edx
  int v54; // edx
  double v55; // st7
  double v56; // st6
  int v57; // eax
  int v58; // esi
  int ptMiddle; // edx
  struct QTask_s *v60; // eax
  int v61; // ebx
  struct QTask_s *v62; // edi
  int v63; // ecx
  int v64; // edx
  int v65; // esi
  double v66; // st7
  int v67; // ebx
  int v68; // esi
  int v69; // ebp
  int v70; // ebx
  int v71; // esi
  int v72; // edx
  double v73; // st7
  double v74; // st6
  int v75; // esi
  int v76; // eax
  bool v77; // zf
  struct QTask_s *v78; // edi
  int v79; // ecx
  double v80; // st7
  float v81; // ebx
  struct QTask_s *ptTail; // eax
  struct QTask_s *ptNext; // edi
  int v84; // ecx
  int v85; // edx
  int v86; // esi
  int v87; // ebp
  int v88; // edx
  bool v89; // cc
  int v90; // ebx
  int v91; // esi
  int v92; // ebp
  int v93; // ebx
  int v94; // esi
  int v95; // esi
  double v96; // st7
  double v97; // st6
  int v98; // eax
  int v99; // esi
  double v100; // st7
  int v101; // edx
  int v102; // ecx
  struct QTask_s *v103; // ebx
  int v104; // eax
  int v105; // esi
  int v106; // edi
  int v107; // ebp
  int v108; // esi
  int v109; // edi
  int v110; // edi
  int v111; // edx
  double v112; // st7
  double v113; // st6
  int v114; // esi
  double v115; // st7
  double v116; // st3
  double v117; // st6
  unsigned __int16 v118; // bx
  BOOL v119; // esi
  struct QTask_s *NextSiblingOfType; // edx
  double v121; // st5
  int v122; // eax
  double v123; // st4
  double v124; // st3
  double v125; // st2
  double v126; // st2
  double v127; // st4
  double v128; // st3
  int v129; // ebx
  double *v130; // eax
  double *v131; // edi
  double v132; // st5
  unsigned __int16 v133; // si
  double v134; // st5
  double v135; // st4
  double v136; // st3
  struct TerrainMap_t *v137; // eax
  int i; // edx
  double v139; // st7
  float *v140; // esi
  unsigned __int16 v141; // dx
  struct QTask_s *v142; // eax
  struct QTask_s *v143; // edi
  double v144; // st7
  long double v145; // st3
  int v146; // edx
  int v147; // eax
  _DWORD *v148; // ebx
  unsigned int v149; // eax
  int v150; // eax

  v2 = pxContext;
  v3 = *((_DWORD *)pxContext + 9);
  v4 = *((double **)pxContext + 1);
  igi2_frame.v178 = *(double **)pxContext;
  igi2_frame.v179 = v3;
  igi2_frame.v181 = v4;
  FirstChildOfType = QTask_GetFirstChildOfType(ptQTask, TerrainMap_eQTaskType);
  igi2_frame.v182 = FirstChildOfType;
  if ( !FirstChildOfType )
    return;
  do
  {
    v6 = v2[2];
    v7 = *(float *)&FirstChildOfType[4].tQTaskChildren.ptMiddle * 2048.0;
    v8 = *(float *)&FirstChildOfType[4].tQTaskChildren.ptTail;
    igi2_frame.v188 = 0;
    *(float *)&igi2_frame.v167 = v8 * 2048.0;
    igi2_frame.v176 = (double)(int)FirstChildOfType[2].tQTaskChildren.ptTail / (v7 + v7);
    igi2_frame.v175 = (double)(int)FirstChildOfType[2].tQTaskRefList.ptMiddle / (*(float *)&igi2_frame.v167 + *(float *)&igi2_frame.v167);
    if ( v6 <= 0 )
      goto LABEL_226;
    igi2_frame.v186 = v7;
    igi2_frame.v184 = *(float *)&igi2_frame.v167;
    do
    {
      v9 = *igi2_frame.v178;
      igi2_frame.v172 = 3.4028234663852886e+38;
      v10 = v9 - *(double *)&FirstChildOfType[3].tQTaskChildren.ptTail;
      igi2_frame.v180 = 0;
      igi2_frame.ptStart.vX = (v10 + igi2_frame.v186) * igi2_frame.v176 - 0.5;
      igi2_frame.ptStart.vY = (igi2_frame.v178[1] - *(double *)&FirstChildOfType[3].tQTaskRefList.ptMiddle + igi2_frame.v184) * igi2_frame.v175 - 0.5;
      igi2_frame.ptStart.vZ = igi2_frame.v178[2] - *(double *)&FirstChildOfType[3].ptParent;
      igi2_frame.ptEnd.vX = (*igi2_frame.v181 - *(double *)&FirstChildOfType[3].tQTaskChildren.ptTail + igi2_frame.v186) * igi2_frame.v176 - 0.5;
      igi2_frame.ptEnd.vY = (igi2_frame.v181[1] - *(double *)&FirstChildOfType[3].tQTaskRefList.ptMiddle + igi2_frame.v184) * igi2_frame.v175 - 0.5;
      igi2_frame.ptEnd.vZ = igi2_frame.v181[2] - *(double *)&FirstChildOfType[3].ptParent;
      if ( igi2_frame.ptStart.vX < 0.0 )
      {
        if ( igi2_frame.ptEnd.vX < 0.0 )
          goto LABEL_224;
        v11 = -igi2_frame.ptStart.vX;
        v12 = igi2_frame.ptEnd.vX - igi2_frame.ptStart.vX;
        igi2_frame.ptStart.vX = 0.0;
        v13 = v11 / v12;
        igi2_frame.ptStart.vY = (igi2_frame.ptEnd.vY - igi2_frame.ptStart.vY) * v13 + igi2_frame.ptStart.vY;
        igi2_frame.ptStart.vZ = (igi2_frame.ptEnd.vZ - igi2_frame.ptStart.vZ) * v13 + igi2_frame.ptStart.vZ;
      }
      LODWORD(igi2_frame.v173) = (char *)FirstChildOfType[2].tQTaskChildren.ptTail - 1;
      igi2_frame.v153 = (float)(int)igi2_frame.v173;
      if ( igi2_frame.ptStart.vX > (double)igi2_frame.v153 )
      {
        if ( igi2_frame.ptEnd.vX > (double)igi2_frame.v153 )
          goto LABEL_224;
        v14 = igi2_frame.v153 - igi2_frame.ptStart.vX;
        v15 = igi2_frame.ptEnd.vX - igi2_frame.ptStart.vX;
        igi2_frame.ptStart.vX = (float)(int)igi2_frame.v173;
        v16 = v14 / v15;
        igi2_frame.ptStart.vY = (igi2_frame.ptEnd.vY - igi2_frame.ptStart.vY) * v16 + igi2_frame.ptStart.vY;
        igi2_frame.ptStart.vZ = (igi2_frame.ptEnd.vZ - igi2_frame.ptStart.vZ) * v16 + igi2_frame.ptStart.vZ;
      }
      if ( igi2_frame.ptStart.vY < 0.0 )
      {
        if ( igi2_frame.ptEnd.vY < 0.0 )
          goto LABEL_224;
        v17 = -igi2_frame.ptStart.vY;
        v18 = igi2_frame.ptEnd.vY - igi2_frame.ptStart.vY;
        igi2_frame.ptStart.vY = 0.0;
        v19 = v17 / v18;
        igi2_frame.ptStart.vX = (igi2_frame.ptEnd.vX - igi2_frame.ptStart.vX) * v19 + igi2_frame.ptStart.vX;
        igi2_frame.ptStart.vZ = (igi2_frame.ptEnd.vZ - igi2_frame.ptStart.vZ) * v19 + igi2_frame.ptStart.vZ;
      }
      LODWORD(igi2_frame.v173) = (char *)FirstChildOfType[2].tQTaskRefList.ptMiddle - 1;
      igi2_frame.v159 = (float)(int)igi2_frame.v173;
      if ( igi2_frame.ptStart.vY > (double)igi2_frame.v159 )
      {
        if ( igi2_frame.ptEnd.vY > (double)igi2_frame.v159 )
          goto LABEL_224;
        v20 = igi2_frame.v159 - igi2_frame.ptStart.vY;
        v21 = igi2_frame.ptEnd.vY - igi2_frame.ptStart.vY;
        igi2_frame.ptStart.vY = (float)(int)igi2_frame.v173;
        v22 = v20 / v21;
        igi2_frame.ptStart.vX = (igi2_frame.ptEnd.vX - igi2_frame.ptStart.vX) * v22 + igi2_frame.ptStart.vX;
        igi2_frame.ptStart.vZ = (igi2_frame.ptEnd.vZ - igi2_frame.ptStart.vZ) * v22 + igi2_frame.ptStart.vZ;
      }
      if ( igi2_frame.ptEnd.vX < 0.0 )
      {
        if ( igi2_frame.ptStart.vX < 0.0 )
          goto LABEL_224;
        v23 = -igi2_frame.ptEnd.vX;
        v24 = igi2_frame.ptStart.vX - igi2_frame.ptEnd.vX;
        igi2_frame.ptEnd.vX = 0.0;
        v25 = v23 / v24;
        igi2_frame.ptEnd.vY = (igi2_frame.ptStart.vY - igi2_frame.ptEnd.vY) * v25 + igi2_frame.ptEnd.vY;
        igi2_frame.ptEnd.vZ = (igi2_frame.ptStart.vZ - igi2_frame.ptEnd.vZ) * v25 + igi2_frame.ptEnd.vZ;
      }
      if ( igi2_frame.ptEnd.vX > (double)igi2_frame.v153 )
      {
        if ( igi2_frame.ptStart.vX > (double)igi2_frame.v153 )
          goto LABEL_224;
        v26 = igi2_frame.v153 - igi2_frame.ptEnd.vX;
        v27 = igi2_frame.ptStart.vX - igi2_frame.ptEnd.vX;
        igi2_frame.ptEnd.vX = igi2_frame.v153;
        v28 = v26 / v27;
        igi2_frame.ptEnd.vY = (igi2_frame.ptStart.vY - igi2_frame.ptEnd.vY) * v28 + igi2_frame.ptEnd.vY;
        igi2_frame.ptEnd.vZ = (igi2_frame.ptStart.vZ - igi2_frame.ptEnd.vZ) * v28 + igi2_frame.ptEnd.vZ;
      }
      if ( igi2_frame.ptEnd.vY < 0.0 )
      {
        if ( igi2_frame.ptStart.vY < 0.0 )
          goto LABEL_224;
        v29 = -igi2_frame.ptEnd.vY;
        v30 = igi2_frame.ptStart.vY - igi2_frame.ptEnd.vY;
        igi2_frame.ptEnd.vY = 0.0;
        v31 = v29 / v30;
        igi2_frame.ptEnd.vX = (igi2_frame.ptStart.vX - igi2_frame.ptEnd.vX) * v31 + igi2_frame.ptEnd.vX;
        igi2_frame.ptEnd.vZ = (igi2_frame.ptStart.vZ - igi2_frame.ptEnd.vZ) * v31 + igi2_frame.ptEnd.vZ;
      }
      if ( igi2_frame.ptEnd.vY > (double)igi2_frame.v159 )
      {
        if ( igi2_frame.ptStart.vY > (double)igi2_frame.v159 )
          goto LABEL_224;
        v32 = igi2_frame.v159 - igi2_frame.ptEnd.vY;
        v33 = igi2_frame.ptStart.vY - igi2_frame.ptEnd.vY;
        igi2_frame.ptEnd.vY = (float)(int)igi2_frame.v173;
        v34 = v32 / v33;
        igi2_frame.ptEnd.vX = (igi2_frame.ptStart.vX - igi2_frame.ptEnd.vX) * v34 + igi2_frame.ptEnd.vX;
        igi2_frame.ptEnd.vZ = (igi2_frame.ptStart.vZ - igi2_frame.ptEnd.vZ) * v34 + igi2_frame.ptEnd.vZ;
      }
      v35 = igi2_frame.ptEnd.vX - igi2_frame.ptStart.vX;
      v36 = igi2_frame.ptEnd.vY - igi2_frame.ptStart.vY;
      v37 = v35;
      if ( v35 < 0.0 )
        v37 = -v35;
      v38 = v36;
      if ( v36 < 0.0 )
        v38 = -v36;
      if ( v37 <= v38 )
      {
        if ( v36 >= 0.0 )
          v79 = 1;
        else
          *(unsigned int *)&v79 = 0xffffffffu;
        igi2_frame.v167 = v79;
        if ( v36 == 0.0 )
          v80 = 0.0;
        else
          v80 = v35 / v36;
        igi2_frame.vY = (__int64)igi2_frame.ptStart.vY;
        *(float *)&igi2_frame.v174 = ((double)igi2_frame.vY - igi2_frame.ptStart.vY) * v80 + igi2_frame.ptStart.vX;
        *(float *)&igi2_frame.v173 = (float)igi2_frame.v167;
        igi2_frame.v169 = v80 * *(float *)&igi2_frame.v173;
        *(_QWORD *)igi2_frame.pbOutColor = (__int64)igi2_frame.ptEnd.vY;
        LODWORD(igi2_frame.pvOutRelativeZ) = igi2_frame.pbOutColor[0] + v79;
        if ( igi2_frame.vY == igi2_frame.pbOutColor[0] + v79 )
          goto LABEL_224;
        igi2_frame.v207 = 0;
        igi2_frame.v208 = 1;
        *(float *)igi2_frame.pbOutColor = igi2_frame.v169 * *(float *)&igi2_frame.v173;
        while ( 1 )
        {
          igi2_frame.v173 = (__int64)*(float *)&igi2_frame.v174;
          v81 = *(float *)&igi2_frame.v173;
          igi2_frame.v170 = igi2_frame.v173;
          if ( igi2_frame.vY >= 0 )
          {
            if ( (int)FirstChildOfType[2].tQTaskRefList.ptMiddle < igi2_frame.vY )
              igi2_frame.vY = (int)FirstChildOfType[2].tQTaskRefList.ptMiddle;
          }
          else
          {
            igi2_frame.vY = 0;
          }
          if ( (int)igi2_frame.v173 < 0 )
            break;
          if ( (int)FirstChildOfType[2].tQTaskChildren.ptTail < (int)igi2_frame.v173 )
          {
            v81 = *(float *)&FirstChildOfType[2].tQTaskChildren.ptTail;
            goto LABEL_129;
          }
LABEL_130:
          ptTail = FirstChildOfType[2].tQTaskChildren.ptTail;
          ptNext = FirstChildOfType[7].ptNext;
          v84 = (int)(&ptTail[-1].isInMemPool + 1);
          v85 = (int)&FirstChildOfType[2].tQTaskRefList.ptMiddle[-1].pxObject + 3;
          igi2_frame.v166 = v85;
          v86 = LODWORD(v81);
          if ( SLODWORD(v81) >= (int)(&ptTail[-1].isInMemPool + 1) )
            v86 = (int)(&ptTail[-1].isInMemPool + 1);
          if ( igi2_frame.vY < v85 )
            v85 = igi2_frame.vY;
          igi2_frame.ptVertex2.vX = (float)v86;
          igi2_frame.v160 = v85;
          v87 = v86 + v85 * (_DWORD)ptTail;
          v88 = LODWORD(v81) + 1;
          v89 = (int)(LODWORD(v81) + 1) < v84;
          v90 = LODWORD(v81) + 1;
          igi2_frame.ptVertex2.vY = (float)igi2_frame.v160;
          igi2_frame.ptVertex2.vZ = *((float *)&ptNext->ptNext + v87);
          if ( !v89 )
            v90 = (int)(&ptTail[-1].isInMemPool + 1);
          v91 = igi2_frame.vY;
          if ( igi2_frame.vY >= igi2_frame.v166 )
            v91 = igi2_frame.v166;
          igi2_frame.v244 = (float)v90;
          v92 = v90 + v91 * (_DWORD)ptTail;
          v93 = igi2_frame.v170;
          igi2_frame.v245 = (float)v91;
          igi2_frame.v246 = *((float *)&ptNext->ptNext + v92);
          if ( igi2_frame.v170 >= v84 )
            v93 = (int)(&ptTail[-1].isInMemPool + 1);
          v94 = igi2_frame.vY + 1;
          if ( igi2_frame.vY + 1 >= igi2_frame.v166 )
            v94 = igi2_frame.v166;
          igi2_frame.v247 = (float)v93;
          igi2_frame.v248 = (float)v94;
          igi2_frame.v249 = *((float *)&ptNext->ptNext + v93 + v94 * (_DWORD)ptTail);
          if ( v88 < v84 )
            v84 = v88;
          v95 = igi2_frame.vY + 1;
          if ( igi2_frame.vY + 1 >= igi2_frame.v166 )
            v95 = igi2_frame.v166;
          igi2_frame.v250 = (float)v84;
          igi2_frame.v251 = (float)v95;
          igi2_frame.v252 = *((float *)&ptNext->ptNext + v84 + v95 * (_DWORD)ptTail);
          v96 = igi2_frame.ptVertex2.vZ - igi2_frame.v252;
          if ( v96 < 0.0 )
            v96 = -v96;
          v97 = igi2_frame.v246 - igi2_frame.v249;
          if ( v97 < 0.0 )
            v97 = -v97;
          if ( v96 <= v97 )
          {
            v98 = 3;
            igi2_frame.v210 = 0;
            igi2_frame.v211 = 3;
            igi2_frame.v212 = 2;
          }
          else
          {
            v98 = 2;
            igi2_frame.v210 = 2;
            igi2_frame.v211 = 1;
            igi2_frame.v212 = 3;
          }
          FirstChildOfType = igi2_frame.v182;
          v78 = ptQTask;
          igi2_frame.v209 = v98;
          v99 = 0;
          while ( 1 )
          {
            if ( Terrain_LineVSTriangle(
                   &igi2_frame.ptOutPos,
                   &igi2_frame.ptStart,
                   &igi2_frame.ptEnd,
                   &igi2_frame.ptVertex2 + *(&igi2_frame.v207 + v99),
                   &igi2_frame.ptVertex2 + *(&igi2_frame.v208 + v99),
                   &igi2_frame.ptVertex2 + *(&igi2_frame.v209 + v99)) )
            {
              igi2_frame.v156 = sqrt(
                       (igi2_frame.ptOutPos.vX - igi2_frame.ptStart.vX) * (igi2_frame.ptOutPos.vX - igi2_frame.ptStart.vX)
                     + (igi2_frame.ptOutPos.vY - igi2_frame.ptStart.vY) * (igi2_frame.ptOutPos.vY - igi2_frame.ptStart.vY)
                     + (igi2_frame.ptOutPos.vZ - igi2_frame.ptStart.vZ) * (igi2_frame.ptOutPos.vZ - igi2_frame.ptStart.vZ));
              if ( igi2_frame.v156 < (double)igi2_frame.v172 )
              {
                igi2_frame.v254.vX = (igi2_frame.ptOutPos.vX + 0.5) / igi2_frame.v176 + *(double *)&FirstChildOfType[3].tQTaskChildren.ptTail - igi2_frame.v186;
                igi2_frame.v254.vY = (igi2_frame.ptOutPos.vY + 0.5) / igi2_frame.v175 + *(double *)&FirstChildOfType[3].tQTaskRefList.ptMiddle - igi2_frame.v184;
                igi2_frame.v254.vZ = igi2_frame.ptOutPos.vZ + *(double *)&ptQTask[3].tQTaskChildren.ptTail;
                if ( DiscardTask_IsDiscardVertex(&igi2_frame.v254) == false )
                  break;
              }
            }
            v99 += 3;
            if ( v99 >= 6 )
              goto LABEL_160;
          }
          igi2_frame.v183 = igi2_frame.ptOutPos;
          igi2_frame.v180 = 1;
          igi2_frame.v172 = igi2_frame.v156;
LABEL_160:
          v100 = *(float *)&igi2_frame.v174 + *(float *)igi2_frame.pbOutColor;
          igi2_frame.v173 = (__int64)v100;
          v101 = (__int64)v100;
          if ( v101 != igi2_frame.v170 && v101 >= 0 )
          {
            v102 = (int)FirstChildOfType[2].tQTaskChildren.ptTail;
            if ( v101 < v102 )
            {
              v103 = FirstChildOfType[7].ptNext;
              v104 = v102 - 1;
              v105 = (int)&FirstChildOfType[2].tQTaskRefList.ptMiddle[-1].pxObject + 3;
              igi2_frame.v166 = v105;
              v106 = (__int64)v100;
              if ( v101 >= v102 - 1 )
                v106 = v102 - 1;
              if ( igi2_frame.vY < v105 )
                v105 = igi2_frame.vY;
              igi2_frame.v233.vX = (float)v106;
              igi2_frame.v157 = v105;
              v107 = v106 + v105 * v102;
              v108 = v101 + 1;
              igi2_frame.v161 = v101 + 1;
              igi2_frame.v233.vY = (float)igi2_frame.v157;
              igi2_frame.v233.vZ = *((float *)&v103->ptNext + v107);
              if ( v101 + 1 >= v104 )
                igi2_frame.v161 = v102 - 1;
              v109 = igi2_frame.vY;
              if ( igi2_frame.vY >= igi2_frame.v166 )
                v109 = igi2_frame.v166;
              igi2_frame.v234 = (float)igi2_frame.v161;
              igi2_frame.v235 = (float)v109;
              igi2_frame.v236 = *((float *)&v103->ptNext + igi2_frame.v161 + v109 * v102);
              if ( v101 >= v104 )
                v101 = v102 - 1;
              v110 = igi2_frame.vY + 1;
              if ( igi2_frame.vY + 1 >= igi2_frame.v166 )
                v110 = igi2_frame.v166;
              igi2_frame.v237 = (float)v101;
              igi2_frame.v238 = (float)v110;
              igi2_frame.v239 = *((float *)&v103->ptNext + v101 + v110 * v102);
              if ( v108 < v104 )
                v104 = v108;
              v111 = igi2_frame.vY + 1;
              if ( igi2_frame.vY + 1 >= igi2_frame.v166 )
                v111 = igi2_frame.v166;
              igi2_frame.v240 = (float)v104;
              igi2_frame.v241 = (float)v111;
              igi2_frame.v242 = *((float *)&v103->ptNext + v104 + v111 * v102);
              v112 = igi2_frame.v233.vZ - igi2_frame.v242;
              if ( v112 < 0.0 )
                v112 = -v112;
              v113 = igi2_frame.v236 - igi2_frame.v239;
              if ( v113 < 0.0 )
                v113 = -v113;
              v114 = 0;
              igi2_frame.v195 = 0;
              igi2_frame.v196 = 1;
              if ( v112 <= v113 )
              {
                igi2_frame.v197 = 3;
                igi2_frame.v198 = 0;
                igi2_frame.v199 = 3;
                igi2_frame.v200 = 2;
              }
              else
              {
                igi2_frame.v197 = 2;
                igi2_frame.v198 = 2;
                igi2_frame.v199 = 1;
                igi2_frame.v200 = 3;
              }
              FirstChildOfType = igi2_frame.v182;
              while ( 1 )
              {
                if ( Terrain_LineVSTriangle(
                       &igi2_frame.ptOutPos,
                       &igi2_frame.ptStart,
                       &igi2_frame.ptEnd,
                       &igi2_frame.v233 + *(&igi2_frame.v195 + v114),
                       &igi2_frame.v233 + *(&igi2_frame.v196 + v114),
                       &igi2_frame.v233 + *(&igi2_frame.v197 + v114)) )
                {
                  igi2_frame.v158 = sqrt(
                           (igi2_frame.ptOutPos.vX - igi2_frame.ptStart.vX) * (igi2_frame.ptOutPos.vX - igi2_frame.ptStart.vX)
                         + (igi2_frame.ptOutPos.vY - igi2_frame.ptStart.vY) * (igi2_frame.ptOutPos.vY - igi2_frame.ptStart.vY)
                         + (igi2_frame.ptOutPos.vZ - igi2_frame.ptStart.vZ) * (igi2_frame.ptOutPos.vZ - igi2_frame.ptStart.vZ));
                  if ( igi2_frame.v158 < (double)igi2_frame.v172 )
                  {
                    igi2_frame.v256.vX = (igi2_frame.ptOutPos.vX + 0.5) / igi2_frame.v176 + *(double *)&FirstChildOfType[3].tQTaskChildren.ptTail - igi2_frame.v186;
                    igi2_frame.v256.vY = (igi2_frame.ptOutPos.vY + 0.5) / igi2_frame.v175 + *(double *)&FirstChildOfType[3].tQTaskRefList.ptMiddle - igi2_frame.v184;
                    igi2_frame.v256.vZ = igi2_frame.ptOutPos.vZ + *(double *)&ptQTask[3].tQTaskChildren.ptTail;
                    if ( DiscardTask_IsDiscardVertex(&igi2_frame.v256) == false )
                      break;
                  }
                }
                v114 += 3;
                if ( v114 >= 6 )
                  goto LABEL_193;
              }
              igi2_frame.v183 = igi2_frame.ptOutPos;
              igi2_frame.v180 = 1;
              igi2_frame.v172 = igi2_frame.v158;
LABEL_193:
              v78 = ptQTask;
            }
          }
          v77 = igi2_frame.v167 + igi2_frame.vY == LODWORD(igi2_frame.pvOutRelativeZ);
          *(float *)&igi2_frame.v174 = *(float *)&igi2_frame.v174 + igi2_frame.v169;
          igi2_frame.vY += igi2_frame.v167;
          if ( v77 )
            goto LABEL_195;
        }
        v81 = 0.0;
LABEL_129:
        *(float *)&igi2_frame.v170 = v81;
        goto LABEL_130;
      }
      if ( v35 >= 0.0 )
        v39 = 1;
      else
        *(unsigned int *)&v39 = 0xffffffffu;
      igi2_frame.v167 = v39;
      igi2_frame.vX = (__int64)igi2_frame.ptStart.vX;
      v40 = v36 / v35;
      *(float *)&igi2_frame.v170 = ((double)igi2_frame.vX - igi2_frame.ptStart.vX) * v40 + igi2_frame.ptStart.vY;
      v41 = (double)v39;
      *(float *)&igi2_frame.v174 = v41;
      *(float *)&igi2_frame.v173 = v41 * v40;
      *(_QWORD *)igi2_frame.pbOutColor = (__int64)igi2_frame.ptEnd.vX;
      igi2_frame.pbOutColor[0] += v39;
      if ( igi2_frame.vX == igi2_frame.pbOutColor[0] )
        goto LABEL_224;
      igi2_frame.v201 = 0;
      igi2_frame.v202 = 1;
      *(float *)&igi2_frame.pvOutRelativeZ = *(float *)&igi2_frame.v174 * *(float *)&igi2_frame.v173;
      do
      {
        igi2_frame.v174 = (__int64)*(float *)&igi2_frame.v170;
        v42 = *(float *)&igi2_frame.v174;
        igi2_frame.v169 = *(float *)&igi2_frame.v174;
        if ( (int)igi2_frame.v174 >= 0 )
        {
          if ( (int)FirstChildOfType[2].tQTaskRefList.ptMiddle >= (int)igi2_frame.v174 )
            goto LABEL_43;
          v42 = *(float *)&FirstChildOfType[2].tQTaskRefList.ptMiddle;
        }
        else
        {
          v42 = 0.0;
        }
        igi2_frame.v169 = v42;
LABEL_43:
        v43 = igi2_frame.vX;
        if ( igi2_frame.vX < 0 )
        {
          v43 = 0;
LABEL_47:
          igi2_frame.vX = v43;
          goto LABEL_48;
        }
        if ( (int)FirstChildOfType[2].tQTaskChildren.ptTail < igi2_frame.vX )
        {
          v43 = (int)FirstChildOfType[2].tQTaskChildren.ptTail;
          goto LABEL_47;
        }
LABEL_48:
        v44 = FirstChildOfType[2].tQTaskChildren.ptTail;
        v45 = FirstChildOfType[7].ptNext;
        v46 = (int)(&v44[-1].isInMemPool + 1);
        v47 = (int)&FirstChildOfType[2].tQTaskRefList.ptMiddle[-1].pxObject + 3;
        igi2_frame.v166 = v47;
        if ( v43 >= (int)(&v44[-1].isInMemPool + 1) )
          v43 = (int)(&v44[-1].isInMemPool + 1);
        if ( SLODWORD(v42) < v47 )
          v47 = LODWORD(v42);
        igi2_frame.ptVertex0.vX = (float)v43;
        v48 = v43 + v47 * (_DWORD)v44;
        v49 = igi2_frame.vX + 1;
        igi2_frame.ptVertex0.vY = (float)v47;
        igi2_frame.ptVertex0.vZ = *((float *)&v45->ptNext + v48);
        if ( igi2_frame.vX + 1 >= v46 )
          v49 = (int)(&v44[-1].isInMemPool + 1);
        v50 = igi2_frame.v166;
        if ( SLODWORD(igi2_frame.v169) < igi2_frame.v166 )
          v50 = LODWORD(igi2_frame.v169);
        igi2_frame.v214 = (float)v49;
        v51 = v49 + v50 * (_DWORD)v44;
        v52 = igi2_frame.vX;
        igi2_frame.v215 = (float)v50;
        igi2_frame.v216 = *((float *)&v45->ptNext + v51);
        if ( igi2_frame.vX >= v46 )
          v52 = (int)(&v44[-1].isInMemPool + 1);
        v53 = LODWORD(igi2_frame.v169) + 1;
        if ( (int)(LODWORD(igi2_frame.v169) + 1) >= igi2_frame.v166 )
          v53 = igi2_frame.v166;
        igi2_frame.v217 = (float)v52;
        igi2_frame.v218 = (float)v53;
        igi2_frame.v219 = *((float *)&v45->ptNext + v52 + v53 * (_DWORD)v44);
        if ( igi2_frame.vX + 1 < v46 )
          v46 = igi2_frame.vX + 1;
        v54 = LODWORD(igi2_frame.v169) + 1;
        if ( (int)(LODWORD(igi2_frame.v169) + 1) >= igi2_frame.v166 )
          v54 = igi2_frame.v166;
        igi2_frame.v220 = (float)v46;
        igi2_frame.v221 = (float)v54;
        igi2_frame.v222 = *((float *)&v45->ptNext + v46 + v54 * (_DWORD)v44);
        v55 = igi2_frame.ptVertex0.vZ - igi2_frame.v222;
        if ( v55 < 0.0 )
          v55 = -v55;
        v56 = igi2_frame.v216 - igi2_frame.v219;
        if ( v56 < 0.0 )
          v56 = -v56;
        if ( v55 <= v56 )
        {
          v57 = 3;
          igi2_frame.v204 = 0;
          igi2_frame.v205 = 3;
          igi2_frame.v206 = 2;
        }
        else
        {
          v57 = 2;
          igi2_frame.v204 = 2;
          igi2_frame.v205 = 1;
          igi2_frame.v206 = 3;
        }
        igi2_frame.v203 = v57;
        v58 = 0;
        while ( 1 )
        {
          if ( Terrain_LineVSTriangle(
                 &igi2_frame.ptOutPos,
                 &igi2_frame.ptStart,
                 &igi2_frame.ptEnd,
                 &igi2_frame.ptVertex0 + *(&igi2_frame.v201 + v58),
                 &igi2_frame.ptVertex0 + *(&igi2_frame.v202 + v58),
                 &igi2_frame.ptVertex0 + *(&igi2_frame.v203 + v58)) )
          {
            igi2_frame.v154 = sqrt(
                     (igi2_frame.ptOutPos.vX - igi2_frame.ptStart.vX) * (igi2_frame.ptOutPos.vX - igi2_frame.ptStart.vX)
                   + (igi2_frame.ptOutPos.vY - igi2_frame.ptStart.vY) * (igi2_frame.ptOutPos.vY - igi2_frame.ptStart.vY)
                   + (igi2_frame.ptOutPos.vZ - igi2_frame.ptStart.vZ) * (igi2_frame.ptOutPos.vZ - igi2_frame.ptStart.vZ));
            if ( igi2_frame.v154 < (double)igi2_frame.v172 )
            {
              igi2_frame.ptPos.vX = (igi2_frame.ptOutPos.vX + 0.5) / igi2_frame.v176 + *(double *)&FirstChildOfType[3].tQTaskChildren.ptTail - igi2_frame.v186;
              igi2_frame.ptPos.vY = (igi2_frame.ptOutPos.vY + 0.5) / igi2_frame.v175 + *(double *)&FirstChildOfType[3].tQTaskRefList.ptMiddle - igi2_frame.v184;
              igi2_frame.ptPos.vZ = igi2_frame.ptOutPos.vZ + *(double *)&ptQTask[3].tQTaskChildren.ptTail;
              if ( DiscardTask_IsDiscardVertex(&igi2_frame.ptPos) == false )
                break;
            }
          }
          v58 += 3;
          if ( v58 >= 6 )
            goto LABEL_78;
        }
        igi2_frame.v183 = igi2_frame.ptOutPos;
        igi2_frame.v180 = 1;
        igi2_frame.v172 = igi2_frame.v154;
LABEL_78:
        igi2_frame.v174 = (__int64)(*(float *)&igi2_frame.pvOutRelativeZ + *(float *)&igi2_frame.v170);
        if ( (_DWORD)igi2_frame.v174 != LODWORD(igi2_frame.v169) && (int)igi2_frame.v174 >= 0 )
        {
          ptMiddle = (int)FirstChildOfType[2].tQTaskRefList.ptMiddle;
          if ( (int)igi2_frame.v174 < ptMiddle )
          {
            v60 = FirstChildOfType[2].tQTaskChildren.ptTail;
            v61 = igi2_frame.vX;
            v62 = FirstChildOfType[7].ptNext;
            v63 = (int)(&v60[-1].isInMemPool + 1);
            v64 = ptMiddle - 1;
            igi2_frame.v166 = v64;
            if ( igi2_frame.vX >= (int)(&v60[-1].isInMemPool + 1) )
              v61 = (int)(&v60[-1].isInMemPool + 1);
            v65 = igi2_frame.v174;
            if ( (int)igi2_frame.v174 >= v64 )
              v65 = igi2_frame.v166;
            igi2_frame.ptVertex1.vX = (float)v61;
            igi2_frame.ptVertex1.vY = (float)v65;
            v66 = *((float *)&v62->ptNext + v61 + v65 * (_DWORD)v60);
            v67 = igi2_frame.vX + 1;
            igi2_frame.ptVertex1.vZ = v66;
            if ( igi2_frame.vX + 1 >= v63 )
              v67 = (int)(&v60[-1].isInMemPool + 1);
            v68 = igi2_frame.v166;
            if ( (int)igi2_frame.v174 < igi2_frame.v166 )
              v68 = igi2_frame.v174;
            igi2_frame.v224 = (float)v67;
            v69 = v67 + v68 * (_DWORD)v60;
            v70 = igi2_frame.vX;
            igi2_frame.v225 = (float)v68;
            igi2_frame.v226 = *((float *)&v62->ptNext + v69);
            if ( igi2_frame.vX >= v63 )
              v70 = (int)(&v60[-1].isInMemPool + 1);
            v71 = igi2_frame.v166;
            v72 = igi2_frame.v174 + 1;
            if ( (int)igi2_frame.v174 + 1 < igi2_frame.v166 )
              v71 = igi2_frame.v174 + 1;
            igi2_frame.v227 = (float)v70;
            igi2_frame.v228 = (float)v71;
            igi2_frame.v229 = *((float *)&v62->ptNext + v70 + v71 * (_DWORD)v60);
            if ( igi2_frame.vX + 1 < v63 )
              v63 = igi2_frame.vX + 1;
            if ( v72 >= igi2_frame.v166 )
              v72 = igi2_frame.v166;
            igi2_frame.v230 = (float)v63;
            igi2_frame.v231 = (float)v72;
            igi2_frame.v232 = *((float *)&v62->ptNext + v63 + v72 * (_DWORD)v60);
            v73 = igi2_frame.ptVertex1.vZ - igi2_frame.v232;
            if ( v73 < 0.0 )
              v73 = -v73;
            v74 = igi2_frame.v226 - igi2_frame.v229;
            if ( v74 < 0.0 )
              v74 = -v74;
            v75 = 0;
            igi2_frame.v189 = 0;
            if ( v73 <= v74 )
            {
              v76 = 3;
              igi2_frame.v190 = 1;
              igi2_frame.v192 = 0;
              igi2_frame.v193 = 3;
              igi2_frame.v194 = 2;
            }
            else
            {
              v76 = 2;
              igi2_frame.v190 = 1;
              igi2_frame.v192 = 2;
              igi2_frame.v193 = 1;
              igi2_frame.v194 = 3;
            }
            FirstChildOfType = igi2_frame.v182;
            igi2_frame.v191 = v76;
            while ( 1 )
            {
              if ( Terrain_LineVSTriangle(
                     &igi2_frame.ptOutPos,
                     &igi2_frame.ptStart,
                     &igi2_frame.ptEnd,
                     &igi2_frame.ptVertex1 + *(&igi2_frame.v189 + v75),
                     &igi2_frame.ptVertex1 + *(&igi2_frame.v190 + v75),
                     &igi2_frame.ptVertex1 + *(&igi2_frame.v191 + v75)) )
              {
                igi2_frame.v155 = sqrt(
                         (igi2_frame.ptOutPos.vX - igi2_frame.ptStart.vX) * (igi2_frame.ptOutPos.vX - igi2_frame.ptStart.vX)
                       + (igi2_frame.ptOutPos.vY - igi2_frame.ptStart.vY) * (igi2_frame.ptOutPos.vY - igi2_frame.ptStart.vY)
                       + (igi2_frame.ptOutPos.vZ - igi2_frame.ptStart.vZ) * (igi2_frame.ptOutPos.vZ - igi2_frame.ptStart.vZ));
                if ( igi2_frame.v155 < (double)igi2_frame.v172 )
                {
                  igi2_frame.v255.vX = (igi2_frame.ptOutPos.vX + 0.5) / igi2_frame.v176 + *(double *)&FirstChildOfType[3].tQTaskChildren.ptTail - igi2_frame.v186;
                  igi2_frame.v255.vY = (igi2_frame.ptOutPos.vY + 0.5) / igi2_frame.v175 + *(double *)&FirstChildOfType[3].tQTaskRefList.ptMiddle - igi2_frame.v184;
                  igi2_frame.v255.vZ = igi2_frame.ptOutPos.vZ + *(double *)&ptQTask[3].tQTaskChildren.ptTail;
                  if ( DiscardTask_IsDiscardVertex(&igi2_frame.v255) == false )
                    break;
                }
              }
              v75 += 3;
              if ( v75 >= 6 )
                goto LABEL_111;
            }
            igi2_frame.v183 = igi2_frame.ptOutPos;
            igi2_frame.v180 = 1;
            igi2_frame.v172 = igi2_frame.v155;
          }
        }
LABEL_111:
        v77 = igi2_frame.v167 + igi2_frame.vX == igi2_frame.pbOutColor[0];
        *(float *)&igi2_frame.v170 = *(float *)&igi2_frame.v170 + *(float *)&igi2_frame.v173;
        igi2_frame.vX += igi2_frame.v167;
      }
      while ( !v77 );
      v78 = ptQTask;
LABEL_195:
      if ( igi2_frame.v180 )
      {
        igi2_frame.v253[0] = (igi2_frame.v183.vX + 0.5) / igi2_frame.v176 + *(double *)&FirstChildOfType[3].tQTaskChildren.ptTail - igi2_frame.v186;
        v115 = (igi2_frame.v183.vY + 0.5) / igi2_frame.v175 + *(double *)&FirstChildOfType[3].tQTaskRefList.ptMiddle - igi2_frame.v184;
        igi2_frame.v253[1] = v115;
        igi2_frame.v253[2] = igi2_frame.v183.vZ + *(double *)&v78[3].tQTaskChildren.ptTail;
        v116 = sqrt(
                 (igi2_frame.v253[2] - igi2_frame.v178[2]) * (igi2_frame.v253[2] - igi2_frame.v178[2])
               + (v115 - igi2_frame.v178[1]) * (v115 - igi2_frame.v178[1])
               + (igi2_frame.v253[0] - *igi2_frame.v178) * (igi2_frame.v253[0] - *igi2_frame.v178));
        v117 = v116;
        if ( !*(_DWORD *)(igi2_frame.v179 + 92) || v116 < *(double *)(igi2_frame.v179 + 96) )
        {
          v118 = TerrainMap_eQTaskType;
          v119 = 1;
          NextSiblingOfType = QTask_GetFirstChildOfType(v78, TerrainMap_eQTaskType);
          if ( !NextSiblingOfType )
            goto LABEL_209;
          v121 = igi2_frame.v253[0] - *(double *)&v78[3].ptNext;
          do
          {
            v122 = (int)NextSiblingOfType[2].tQTaskChildren.ptTail;
            v123 = *(double *)&NextSiblingOfType[3].tQTaskChildren.ptTail - *(double *)&v78[3].ptNext;
            *(float *)&igi2_frame.v173 = *(double *)&NextSiblingOfType[3].tQTaskRefList.ptMiddle
                            - *(double *)&v78[3].tQTaskChildren.ptHead;
            v124 = *(float *)&NextSiblingOfType[4].tQTaskChildren.ptMiddle * 2048.0;
            *(float *)&igi2_frame.v167 = *(float *)&NextSiblingOfType[4].tQTaskChildren.ptTail * 2048.0;
            v125 = (double)(int)NextSiblingOfType[2].tQTaskChildren.ptTail;
            if ( v122 < 0 )
              v125 = v125 + 4294967296.0;
            *(float *)igi2_frame.pbOutColor = 1.0
                                 / ((double)(unsigned int)NextSiblingOfType[2].tQTaskRefList.ptMiddle
                                  / *(float *)&igi2_frame.v167
                                  * 0.5);
            v126 = 1.0 / (v125 / v124 * 0.5) * 0.5;
            if ( v121 > v123 - v124 + v126 && v121 < v124 + v123 - v126 )
            {
              v127 = v115 - *(double *)&v78[3].tQTaskChildren.ptHead;
              v128 = *(float *)igi2_frame.pbOutColor * 0.5;
              if ( v127 > *(float *)&igi2_frame.v173 - *(float *)&igi2_frame.v167 + v128 && v127 < *(float *)&igi2_frame.v167 + *(float *)&igi2_frame.v173 - v128 )
                v119 = NextSiblingOfType == FirstChildOfType;
            }
            NextSiblingOfType = QTask_GetNextSiblingOfType(NextSiblingOfType, v118);
          }
          while ( NextSiblingOfType );
          if ( v119 )
          {
LABEL_209:
            v129 = igi2_frame.v179;
            v130 = (double *)(igi2_frame.v179 + 8);
            v131 = (double *)(igi2_frame.v179 + 8);
            *(_DWORD *)igi2_frame.v179 = ptQTask;
            qmemcpy(v131, igi2_frame.v253, 0x18u);
            v132 = *v130;
            v133 = TerrainMap_eQTaskType;
            *(_DWORD *)(v129 + 92) = 1;
            v134 = v132 - *(double *)&ptQTask[3].ptNext;
            v135 = *(double *)(v129 + 16) - *(double *)&ptQTask[3].tQTaskChildren.ptHead;
            v136 = *(double *)(v129 + 24) - *(double *)&ptQTask[3].tQTaskChildren.ptTail;
            *(_DWORD *)(v129 + 88) = 0;
            *(_DWORD *)(v129 + 80) = 0;
            *(_DWORD *)(v129 + 84) = 0;
            igi2_frame.v258 = v136;
            *(float *)(v129 + 32) = v134;
            *(float *)(v129 + 36) = v135;
            *(float *)(v129 + 40) = igi2_frame.v258;
            *(double *)(v129 + 96) = v117;
            v137 = (struct TerrainMap_t *)QTask_GetFirstChildOfType(ptQTask, v133);
            for ( i = 0; v137; ++i )
            {
              if ( i >= 10 )
                break;
              v137->bColor = -1;
              Terrain_aptActiveHeightmap[i] = v137;
              v137 = (struct TerrainMap_t *)QTask_GetNextSiblingOfType(&v137->tQTask, v133);
            }
            igi2_frame.vInY = v115 - *(double *)&ptQTask[3].tQTaskChildren.ptHead;
            v139 = igi2_frame.v253[0] - *(double *)&ptQTask[3].ptNext;
            Terrain_nActiveHeightmaps = i;
            igi2_frame.vInX = v139;
            v140 = (float *)(v129 + 56);
            Terrain_ptActiveTerrain = (struct Terrain_t *)ptQTask;
            Terrain_VertexFunction(
              (float *)&igi2_frame.pvOutRelativeZ,
              (struct real32x3_t *)(v129 + 56),
              igi2_frame.pbOutColor,
              &igi2_frame.piOutMaterial,
              &igi2_frame.piOutLightmap,
              igi2_frame.vInX,
              igi2_frame.vInY,
              0.0);
            v141 = TerrainMaterial_eQTaskType;
            v142 = QTask_GetFirstChildOfType(ptQTask, TerrainMaterial_eQTaskType);
            if ( !v142 )
              goto LABEL_216;
            v143 = (struct QTask_s *)igi2_frame.piOutMaterial;
            while ( v142[1].ptPrev != v143 )
            {
              v142 = QTask_GetNextSiblingOfType(v142, v141);
              if ( !v142 )
                goto LABEL_216;
            }
            v149 = (unsigned int)v142[1].ptNext;
            if ( v149 < 0x40 )
              *(_DWORD *)(v129 + 80) = World_ptActiveWorld->aptQMaterial[v149];
            else
LABEL_216:
              *(_DWORD *)(v129 + 80) = 0;
            if ( *v140 != 0.0 || *(float *)(v129 + 60) != 0.0 || *(float *)(v129 + 64) != 0.0 )
            {
              v144 = *(float *)(v129 + 64);
              igi2_frame.pvOutRelativeZ = *(float *)(v129 + 60);
              *(double *)igi2_frame.pbOutColor = *v140;
              v145 = sqrt(*(double *)igi2_frame.pbOutColor * *(double *)igi2_frame.pbOutColor + igi2_frame.pvOutRelativeZ * igi2_frame.pvOutRelativeZ + v144 * v144);
              *v140 = *(double *)igi2_frame.pbOutColor * (1.0 / v145);
              *(float *)(v129 + 60) = igi2_frame.pvOutRelativeZ * (1.0 / v145);
              *(float *)(v129 + 64) = 1.0 / v145 * v144;
            }
            v146 = *(_DWORD *)(v129 + 60);
            v147 = *(_DWORD *)(v129 + 64);
            v148 = (_DWORD *)(v129 + 44);
            *v148 = *(_DWORD *)v140;
            v148[1] = v146;
            v148[2] = v147;
          }
        }
      }
LABEL_224:
      v89 = ++igi2_frame.v188 < (int)(*((_DWORD *)pxContext + 2));
      igi2_frame.v178 += 3;
      igi2_frame.v181 += 3;
      igi2_frame.v179 += 120;
    }
    while ( v89 );
    v2 = pxContext;
LABEL_226:
    v150 = v2[2];
    igi2_frame.v179 += -120 * v150;
    igi2_frame.v178 -= 3 * v150;
    igi2_frame.v181 -= 3 * v150;
    FirstChildOfType = QTask_GetNextSiblingOfType(FirstChildOfType, TerrainMap_eQTaskType);
    igi2_frame.v182 = FirstChildOfType;
  }
  while ( FirstChildOfType );
}

// source: h/2/terrain.c:4147  [size]
void __cdecl Terrain_GetTaskTextHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ;
}

// source: h/2/terrain.c:4169  [anchor-hash]
void __cdecl Terrain_DeleteMaterialPalette(struct Terrain_t *ptTerrain)
{
  if ( ptTerrain->ptMaterialPalette )
  {
    QTask_Delete(ptTerrain->ptMaterialPalette);
    ptTerrain->ptMaterialPalette = nullptr;
  }
}

// source: h/2/terrain.c:4553  [anchor-hash]
struct QTask_s *__cdecl TerrainMap_QEditorRunHandler(struct QTask_s *ptQTask)
{
  if ( *(_DWORD *)&ptQTask[1].eQTaskType )
  {
    if ( (Mouse_tMouse.bButton & 1) == 0 )
      *(_DWORD *)&ptQTask[1].eQTaskType = 0;
  }
  return ptQTask;
}

// source: h/2/terrain.c:4578  [anchor-callee]
void __cdecl TerrainMap_Free(struct TerrainMap_t *ptTerrainMap)
{
  float *pvHeightmap; // eax
  int v2; // ebx
  unsigned __int8 *piMaterialmap; // eax
  int v4; // ebx
  unsigned int *pbLightmap; // eax
  int v6; // ebx
  struct TexInfo_s *p_tLightmapTexInfo; // edi

  if ( ptTerrainMap->isHeightmapResource == false )
  {
    pvHeightmap = ptTerrainMap->pvHeightmap;
    if ( pvHeightmap )
    {
      --Mem_nCurrentAllocations;
      v2 = *(_DWORD *)((unsigned int)(pvHeightmap - 1) & 0xFFFFFFFC);
      Node_Remove((_DWORD **)v2);
      memset(*(void **)(v2 + 8), 0xCDu, *(_DWORD *)(v2 + 16));
      free((void *)v2);
      ptTerrainMap->pvHeightmap = nullptr;
    }
  }
  if ( ptTerrainMap->isMaterialmapResource == false )
  {
    piMaterialmap = ptTerrainMap->piMaterialmap;
    if ( piMaterialmap )
    {
      --Mem_nCurrentAllocations;
      v4 = *(_DWORD *)((unsigned int)(piMaterialmap - 4) & 0xFFFFFFFC);
      Node_Remove((_DWORD **)v4);
      memset(*(void **)(v4 + 8), 0xCDu, *(_DWORD *)(v4 + 16));
      free((void *)v4);
      ptTerrainMap->piMaterialmap = nullptr;
    }
  }
  if ( ptTerrainMap->isLightmapResource == false )
  {
    pbLightmap = ptTerrainMap->pbLightmap;
    if ( pbLightmap )
    {
      --Mem_nCurrentAllocations;
      v6 = *(_DWORD *)((unsigned int)(pbLightmap - 1) & 0xFFFFFFFC);
      Node_Remove((_DWORD **)v6);
      memset(*(void **)(v6 + 8), 0xCDu, *(_DWORD *)(v6 + 16));
      free((void *)v6);
      ptTerrainMap->pbLightmap = nullptr;
    }
  }
  if ( ptTerrainMap->isTerrainLightmapAllocated )
  {
    p_tLightmapTexInfo = &ptTerrainMap->tLightmapTexInfo;
    if ( AppContext_tAppContext.isMainMenu == false )
      RenderMode_atRenderMode[p_tLightmapTexInfo->eRenderMode].apfRenderModeMethod[Texture_eDeAllocTextureMethod](&ptTerrainMap->tLightmapTexInfo);
    memset(p_tLightmapTexInfo, 0, sizeof(struct TexInfo_s));
    ptTerrainMap->isTerrainLightmapAllocated = false;
  }
}

// source: h/2/terrain.c:4631  [anchor-hash]
char *__cdecl TerrainMap_GetDirectory()
{
  sprintf(TerrainMap_zDirectory, (char *const)&g_zFileName.aptSelectableItems[28], "MISSION:", "heightmaps");
  return TerrainMap_zDirectory;
}

// source: h/2/terrain.c:4646  [size]
struct TerrainMapTHMHeader_t *__cdecl TerrainMap_LoadTerrainMap(
        struct TerrainMap_t *ptTerrainMap,
        char *zFilename)
{
  char *v3; // ecx
  struct Resource_s *v4; // eax
  struct TerrainMapTHMHeader_t *result; // eax
  void *v6; // eax
  struct Resource_s *pptResource; // [esp+4h] [ebp-4h] BYREF

  if ( Resource_IsLoadedInternal(zFilename, nullptr) == false && File_Exists(zFilename) == false )
    return nullptr;
  if ( Resource_IsLoadedInternal(zFilename, &pptResource) )
  {
    v4 = pptResource;
    pptResource->isReferenced = 1;
    result = (struct TerrainMapTHMHeader_t *)v4->pxData;
  }
  else
  {
    Game_MPRunNetwork(v3);
    v6 = File_Load(zFilename, (unsigned int *)&pptResource);
    if ( !v6 )
    {
      LDebug_Error("Failed to load resource: '%s'", zFilename);
      abort();
    }
    result = (struct TerrainMapTHMHeader_t *)Resource_ParseFile(
                                               File_zLastSubstitutedPath,
                                               v6,
                                               (unsigned int)pptResource);
  }
  if ( LODWORD(result->vVersion) != 1008981770
    || ptTerrainMap->nEditWidth != result->nWidth
    || ptTerrainMap->nEditHeight != result->nHeight
    || result->eFormat != TERRAINMAP_FILEFORMAT_REAL32 )
  {
    Resource_Flush(result);
    return nullptr;
  }
  return result;
}

// source: h/2/terrain.c:4687  [anchor-callee]
void __cdecl TerrainMap_LoadDEM(struct TerrainMap_t *ptTerrainMap, char *zFilename)
{
  #pragma pack(push, 1)
  union
  {
    struct { float vXResolution; };
    struct { int vXResolutiona; };
    struct { float vXResolutionb; };
    struct { char igi2_o3[4]; int n; };
    struct { char igi2_o4[4]; int na; };
    struct { char igi2_o5[8]; float vHeightUnit; };
    struct { char igi2_o6[12]; char *pcDEMFile; };
    struct { char igi2_o7[16]; float vZResolution; };
    struct { char igi2_o8[20]; float vScale; };
    struct { char igi2_o9[24]; int nY; };
    struct { char igi2_o10[28]; int m; };
    struct { char igi2_o11[32]; int v27; };
    struct { char igi2_o12[36]; int iRow; };
    struct { char igi2_o13[40]; int iColumn; };
    struct { char igi2_o14[44]; float vBaseHeight; };
    struct { char igi2_o15[48]; char zTemp[256]; };
    char igi2_extent[304];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  void *v2; // eax
  char *v3; // edi
  struct TerrainMap_t *v4; // ebx
  int v5; // ebp
  int v6; // eax
  char *v7; // esi
  int v8; // ebx
  double v9; // st7
  int v10; // ecx
  int v11; // ebp
  int v12; // edi
  int v13; // edx
  int v14; // ebx
  int v15; // edx

  v2 = File_Load(zFilename, (unsigned int *)&igi2_frame.pcDEMFile);
  v3 = (char *)v2;
  igi2_frame.pcDEMFile = (char *)v2;
  if ( v2 )
  {
    strncpy(igi2_frame.zTemp, (char *)v2 + 528, 6u);
    igi2_frame.zTemp[6] = 0;
    igi2_frame.vXResolution = 1248.4608154296875;
    if ( atoi(igi2_frame.zTemp) != 1 )
      igi2_frame.vXResolution = 4096.0;
    strncpy(igi2_frame.zTemp, v3 + 534, 6u);
    igi2_frame.zTemp[6] = 0;
    igi2_frame.vHeightUnit = 1248.4608154296875;
    if ( atoi(igi2_frame.zTemp) != 1 )
      igi2_frame.vHeightUnit = 4096.0;
    strncpy(igi2_frame.zTemp, v3 + 816, 0xCu);
    igi2_frame.zTemp[12] = 0;
    igi2_frame.vXResolutionb = atof(igi2_frame.zTemp) * igi2_frame.vXResolution;
    strncpy(igi2_frame.zTemp, v3 + 828, 0xCu);
    igi2_frame.zTemp[12] = 0;
    atof(igi2_frame.zTemp);
    strncpy(igi2_frame.zTemp, v3 + 840, 0xCu);
    igi2_frame.zTemp[12] = 0;
    v4 = ptTerrainMap;
    igi2_frame.vZResolution = atof(igi2_frame.zTemp) * igi2_frame.vHeightUnit;
    igi2_frame.vScale = ptTerrainMap->vWorldWidth / (double)ptTerrainMap->nWidth / igi2_frame.vXResolutionb * 4096.0;
    strncpy(igi2_frame.zTemp, v3 + 852, 6u);
    igi2_frame.zTemp[6] = 0;
    v5 = atoi(igi2_frame.zTemp);
    strncpy(igi2_frame.zTemp, v3 + 858, 6u);
    igi2_frame.zTemp[6] = 0;
    v6 = v5 * atoi(igi2_frame.zTemp);
    v7 = v3 + 1024;
    if ( v6 > 0 )
    {
      igi2_frame.vXResolutiona = v6;
      do
      {
        strncpy(igi2_frame.zTemp, v7, 6u);
        igi2_frame.zTemp[6] = 0;
        igi2_frame.iRow = atoi(igi2_frame.zTemp);
        strncpy(igi2_frame.zTemp, v7 + 6, 6u);
        igi2_frame.zTemp[6] = 0;
        igi2_frame.iColumn = atoi(igi2_frame.zTemp);
        strncpy(igi2_frame.zTemp, v7 + 12, 6u);
        igi2_frame.zTemp[6] = 0;
        v8 = atoi(igi2_frame.zTemp);
        igi2_frame.m = v8;
        strncpy(igi2_frame.zTemp, v7 + 18, 6u);
        igi2_frame.zTemp[6] = 0;
        igi2_frame.n = atoi(igi2_frame.zTemp);
        strncpy(igi2_frame.zTemp, v7 + 72, 0x18u);
        igi2_frame.zTemp[24] = 0;
        v9 = atof(igi2_frame.zTemp);
        v10 = v8 * igi2_frame.n;
        v11 = 0;
        igi2_frame.vBaseHeight = v9 * igi2_frame.vHeightUnit;
        v12 = 145;
        igi2_frame.v27 = v8 * igi2_frame.n;
        if ( v8 * igi2_frame.n > 0 )
        {
          while ( 1 )
          {
            v13 = v11 % v8;
            v14 = v11 / v8 + igi2_frame.iColumn - 1;
            v15 = v13 + igi2_frame.iRow - 1;
            igi2_frame.nY = v15;
            if ( v12 + 5 > 1024 )
            {
              v7 += 1024;
              v12 = 1;
            }
            if ( v14 < ptTerrainMap->nWidth && v15 < ptTerrainMap->nHeight )
            {
              strncpy(igi2_frame.zTemp, &v7[v12 - 1], 6u);
              igi2_frame.zTemp[6] = 0;
              igi2_frame.na = atoi(igi2_frame.zTemp);
              ptTerrainMap->pvHeightmap[v14 + igi2_frame.nY * ptTerrainMap->nWidth] = ((double)igi2_frame.na * igi2_frame.vZResolution + igi2_frame.vBaseHeight)
                                                                         * igi2_frame.vScale;
              v10 = igi2_frame.v27;
            }
            v12 += 6;
            if ( ++v11 >= v10 )
              break;
            v8 = igi2_frame.m;
          }
        }
        v7 += 1024;
        --igi2_frame.vXResolutiona;
      }
      while ( igi2_frame.vXResolutiona );
      v3 = igi2_frame.pcDEMFile;
      v4 = ptTerrainMap;
    }
    File_Flush(v3);
    v4->isDirty = true;
    TerrainMap_isUpdated = 1;
  }
}

// source: h/2/terrain.c:4812  [size]
struct TerrainMapTMMHeader_t *__cdecl TerrainMap_LoadTerrainMaterial(
        struct TerrainMap_t *ptTerrainMap,
        char *zFilename)
{
  char *v3; // ecx
  struct Resource_s *v4; // eax
  struct TerrainMapTMMHeader_t *result; // eax
  void *v6; // eax
  struct Resource_s *pptResource; // [esp+4h] [ebp-4h] BYREF

  if ( Resource_IsLoadedInternal(zFilename, nullptr) == false && File_Exists(zFilename) == false )
    return nullptr;
  if ( Resource_IsLoadedInternal(zFilename, &pptResource) )
  {
    v4 = pptResource;
    pptResource->isReferenced = 1;
    result = (struct TerrainMapTMMHeader_t *)v4->pxData;
  }
  else
  {
    Game_MPRunNetwork(v3);
    v6 = File_Load(zFilename, (unsigned int *)&pptResource);
    if ( !v6 )
    {
      LDebug_Error("Failed to load resource: '%s'", zFilename);
      abort();
    }
    result = (struct TerrainMapTMMHeader_t *)Resource_ParseFile(
                                               File_zLastSubstitutedPath,
                                               v6,
                                               (unsigned int)pptResource);
  }
  if ( LODWORD(result->vVersion) != 1008981770
    || ptTerrainMap->nEditWidth != result->nWidth
    || ptTerrainMap->nEditHeight != result->nHeight
    || result->eFormat )
  {
    Resource_Flush(result);
    return nullptr;
  }
  return result;
}

// source: h/2/terrain.c:4847  [size]
struct TerrainMapTLMHeader_t *__cdecl TerrainMap_LoadTerrainLightmap(
        struct TerrainMap_t *ptTerrainMap,
        char *zFilename)
{
  char *v3; // ecx
  struct Resource_s *v4; // eax
  struct TerrainMapTLMHeader_t *result; // eax
  void *v6; // eax
  struct Resource_s *pptResource; // [esp+4h] [ebp-4h] BYREF

  if ( Resource_IsLoadedInternal(zFilename, nullptr) == false && File_Exists(zFilename) == false )
    return nullptr;
  if ( Resource_IsLoadedInternal(zFilename, &pptResource) )
  {
    v4 = pptResource;
    pptResource->isReferenced = 1;
    result = (struct TerrainMapTLMHeader_t *)v4->pxData;
  }
  else
  {
    Game_MPRunNetwork(v3);
    v6 = File_Load(zFilename, (unsigned int *)&pptResource);
    if ( !v6 )
    {
      LDebug_Error("Failed to load resource: '%s'", zFilename);
      abort();
    }
    result = (struct TerrainMapTLMHeader_t *)Resource_ParseFile(
                                               File_zLastSubstitutedPath,
                                               v6,
                                               (unsigned int)pptResource);
  }
  if ( LODWORD(result->vVersion) != 1008981770
    || ptTerrainMap->nEditWidth != result->nWidth
    || ptTerrainMap->nEditHeight != result->nHeight
    || result->eFormat != TERRAINMAP_FILEFORMAT_UINT32 )
  {
    Resource_Flush(result);
    return nullptr;
  }
  return result;
}

// source: h/2/terrain.c:4882  [anchor-callee]
struct TerrainMap_t *__cdecl TerrainMap_Alloc(struct TerrainMap_t *ptTerrainMap)
{
  #pragma pack(push, 1)
  union
  {
    struct { int nHeight; };
    struct { char igi2_o1[16]; int v18; };
    struct { char igi2_o2[16]; int v19; };
    struct { char igi2_o3[36]; char zFilename[512]; };
    char igi2_extent[548];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int nEditHeight; // ecx
  int iID; // eax
  struct TerrainMapTHMHeader_t *TerrainMap; // eax
  float *p_vVersion; // eax
  int v6; // eax
  char *Directory; // eax
  struct TerrainMapTMMHeader_t *TerrainMaterial; // eax
  int v9; // ebp
  unsigned __int8 *v10; // edi
  char *v11; // eax
  struct TerrainMapTLMHeader_t *TerrainLightmap; // edx
  int nWidth; // ecx
  struct TerrainMap_t *result; // eax
  int v15; // ebp
  unsigned int *v16; // edi

  nEditHeight = ptTerrainMap->nEditHeight;
  ptTerrainMap->nWidth = ptTerrainMap->nEditWidth;
  iID = ptTerrainMap->iID;
  ptTerrainMap->nHeight = nEditHeight;
  if ( iID >= 1000
    || (sprintf(TerrainMap_zDirectory, (char *const)&g_zFileName.aptSelectableItems[28], "MISSION:", "heightmaps"),
        strlen(TerrainMap_zDirectory) + 17 > 0x200) )
  {
    LDebug_Error("Error occured while loading heightmaps");
LABEL_20:
    abort();
  }
  sprintf(TerrainMap_zDirectory, (char *const)&g_zFileName.aptSelectableItems[28], "MISSION:", "heightmaps");
  sprintf(igi2_frame.zFilename, "%s/%s%03d.thm", TerrainMap_zDirectory, "heightmap", ptTerrainMap->iID);
  TerrainMap = TerrainMap_LoadTerrainMap(ptTerrainMap, igi2_frame.zFilename);
  if ( TerrainMap
    || (sprintf(igi2_frame.zFilename, "%s%03d.thm", "heightmap", ptTerrainMap->iID),
        (TerrainMap = TerrainMap_LoadTerrainMap(ptTerrainMap, igi2_frame.zFilename)) != nullptr) )
  {
    ptTerrainMap->nRawDataSize = 4 * ptTerrainMap->nWidth * ptTerrainMap->nHeight;
    p_vVersion = &TerrainMap[1].vVersion;
    ptTerrainMap->isHeightmapResource = true;
  }
  else
  {
    v6 = 4 * ptTerrainMap->nWidth * ptTerrainMap->nHeight;
    ptTerrainMap->nRawDataSize = v6;
    p_vVersion = (float *)Mem_AllocFn(v6, 4);
    ptTerrainMap->isHeightmapResource = false;
    TerrainMap_isUpdated = 1;
  }
  ptTerrainMap->pvHeightmap = p_vVersion;
  if ( ptTerrainMap->iID >= 1000
    || (sprintf(TerrainMap_zDirectory, (char *const)&g_zFileName.aptSelectableItems[28], "MISSION:", "heightmaps"),
        strlen(TerrainMap_zDirectory) + 17 > 0x200) )
  {
    LDebug_Error("Error occured while loading materialmaps");
    goto LABEL_20;
  }
  igi2_frame.v18 = ptTerrainMap->iID;
  Directory = TerrainMap_GetDirectory();
  sprintf(igi2_frame.zFilename, "%s/%s%03d.tmm", Directory, "heightmap", igi2_frame.v18);
  TerrainMaterial = TerrainMap_LoadTerrainMaterial(ptTerrainMap, igi2_frame.zFilename);
  if ( TerrainMaterial
    || (sprintf(igi2_frame.zFilename, "%s%03d.tmm", "heightmap", ptTerrainMap->iID),
        (TerrainMaterial = TerrainMap_LoadTerrainMaterial(ptTerrainMap, igi2_frame.zFilename)) != nullptr) )
  {
    ptTerrainMap->piMaterialmap = (unsigned __int8 *)&TerrainMaterial[1];
    ptTerrainMap->isMaterialmapResource = true;
  }
  else
  {
    v9 = ptTerrainMap->nWidth * ptTerrainMap->nHeight;
    v10 = (unsigned __int8 *)Mem_AllocFn(v9, 4);
    ptTerrainMap->piMaterialmap = v10;
    memset(v10, 0, v9);
    ptTerrainMap->isMaterialmapResource = false;
    TerrainMap_isUpdated = 1;
  }
  if ( ptTerrainMap->iID >= 1000 || strlen(TerrainMap_GetDirectory()) + 17 > 0x200 )
  {
    LDebug_Error("Error occured while loading terrain lightmaps");
    goto LABEL_20;
  }
  igi2_frame.v19 = ptTerrainMap->iID;
  v11 = TerrainMap_GetDirectory();
  sprintf(igi2_frame.zFilename, "%s/%s%03d.tlm", v11, "heightmap", igi2_frame.v19);
  TerrainLightmap = TerrainMap_LoadTerrainLightmap(ptTerrainMap, igi2_frame.zFilename);
  if ( TerrainLightmap
    || (sprintf(igi2_frame.zFilename, "%s%03d.tlm", "heightmap", ptTerrainMap->iID),
        (TerrainLightmap = TerrainMap_LoadTerrainLightmap(ptTerrainMap, igi2_frame.zFilename)) != nullptr) )
  {
    LOBYTE(QTask_GetFirstParentOfType(&ptTerrainMap->tQTask, Terrain_eQTaskType)[5].ptNext) = 0;
    nWidth = ptTerrainMap->nWidth;
    igi2_frame.nHeight = ptTerrainMap->nHeight;
    ptTerrainMap->pbLightmap = (unsigned int *)&TerrainLightmap[1];
    Texture_AllocAndDownload(
      &ptTerrainMap->tLightmapTexInfo,
      nullptr,
      4 * nWidth,
      nWidth,
      igi2_frame.nHeight,
      3,
      0,
      0,
      &TerrainLightmap[1]);
    ptTerrainMap->isTerrainLightmapAllocated = true;
    ptTerrainMap->isLightmapResource = true;
  }
  else
  {
    v15 = 4 * ptTerrainMap->nWidth * ptTerrainMap->nHeight;
    v16 = (unsigned int *)Mem_AllocFn(v15, 4);
    ptTerrainMap->pbLightmap = v16;
    memset(v16, 0xFFu, v15);
    Texture_AllocAndDownload(
      &ptTerrainMap->tLightmapTexInfo,
      nullptr,
      4 * ptTerrainMap->nWidth,
      ptTerrainMap->nWidth,
      ptTerrainMap->nHeight,
      3,
      0,
      0,
      ptTerrainMap->pbLightmap);
    ptTerrainMap->isTerrainLightmapAllocated = true;
    TerrainMap_isUpdated = 1;
    ptTerrainMap->isLightmapResource = false;
  }
  return result;
}

// source: h/2/terrain.c:5031  [anchor-hash]
char *__cdecl TerrainMap_GetResourceFilename()
{
  sprintf(TerrainMap_zResource, "%s%s/%s", "MISSION:", "heightmaps", "heightmaps.res");
  return TerrainMap_zResource;
}

// source: h/2/terrain.c:5046  [anchor-strings]
void __cdecl TerrainMap_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s **FirstParentOfType; // eax
  int i; // eax

  FirstParentOfType = (struct QTask_s **)QTask_GetFirstParentOfType(ptQTask, Terrain_eQTaskType);
  ++Terrain_nNumHeightmaps;
  *(_DWORD *)&ptQTask[1].eQTaskType = 1;
  ptQTask[1].ptNext = (struct QTask_s *)1;
  ptQTask[2].ptNext = nullptr;
  ptQTask[2].tQTaskChildren.ptHead = nullptr;
  ptQTask[2].tQTaskChildren.ptTail = nullptr;
  ptQTask[2].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[7].ptNext = nullptr;
  ptQTask[1].ptParent = nullptr;
  ptQTask[1].tQTaskRefList.ptHead = nullptr;
  ptQTask[1].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[9].tQTaskChildren.ptTail = (struct QTask_s *)-1;
  ptQTask[9].tQTaskRefList.ptHead = nullptr;
  ptQTask[1].tQTaskRefList.ptTail = nullptr;
  ptQTask[10].tQTaskRefList.ptTail = nullptr;
  ptQTask[9].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[1].tQTaskChildren.ptHead = nullptr;
  LOBYTE(ptQTask[10].ptParent) = 0;
  qmemcpy(&ptQTask[3].tQTaskChildren.ptTail, FirstParentOfType + 30, 0x18u);
  ptQTask[4].tQTaskChildren.ptMiddle = FirstParentOfType[48];
  ptQTask[4].tQTaskChildren.ptTail = FirstParentOfType[49];
  qmemcpy(&ptQTask[2].ptParent, FirstParentOfType + 30, 0x18u);
  ptQTask[4].ptPrev = FirstParentOfType[48];
  ptQTask[4].tQTaskChildren.ptHead = FirstParentOfType[49];
  ptQTask[2].tQTaskChildren.ptMiddle = (struct QTask_s *)128;
  ptQTask[2].tQTaskRefList.ptHead = (struct QReference_s *)128;
  ptQTask[4].ptNext = (struct QTask_s *)1036831949;
  ptQTask[1].ptPrev = nullptr;
  ptQTask[2].ptPrev = nullptr;
  ptQTask[1].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[1].tQTaskChildren.ptTail = nullptr;
  for ( i = 0; i < 10; ++i )
  {
    if ( !Terrain_aisIDTaken[i] )
      break;
  }
  if ( i == 10 )
  {
    LDebug_Error("Too many heightmaps");
    abort();
  }
  ptQTask[4].tQTaskRefList.ptHead = (struct QReference_s *)i;
  memset(&ptQTask[4].tQTaskRefList.ptMiddle, 0, 0x50u);
  TerrainMap_isMipMapsUpdated = 0;
}

// source: h/2/terrain.c:5130  [anchor-strings]
void __cdecl TerrainMap_DeleteHandler(struct QTask_s *ptQTask)
{
  struct Terrain_t *FirstParentOfType; // edi
  struct QReference_s *ptHead; // eax
  struct QReference_s **p_ptMiddle; // ebx
  int v4; // ebp
  int v5; // esi

  FirstParentOfType = (struct Terrain_t *)QTask_GetFirstParentOfType(ptQTask, Terrain_eQTaskType);
  TerrainMap_DeallocateMinMaxHeightMipMaps((struct TerrainMap_t *)ptQTask);
  ptQTask[2].ptNext = (struct QTask_s *)1;
  Terrain_UpdateSubmaps(FirstParentOfType);
  ptHead = ptQTask[4].tQTaskRefList.ptHead;
  if ( !Terrain_aisIDTaken[(_DWORD)ptHead] )
  {
    LDebug_Error("ID error in heightmap system");
    abort();
  }
  Terrain_aisIDTaken[(_DWORD)ptHead] = 0;
  TerrainMap_Free((struct TerrainMap_t *)ptQTask);
  --Terrain_nNumHeightmaps;
  p_ptMiddle = &ptQTask[4].tQTaskRefList.ptMiddle;
  v4 = 20;
  do
  {
    if ( *p_ptMiddle )
    {
      v5 = *(_DWORD *)((unsigned int)&(*p_ptMiddle)[-1].pxObject & 0xFFFFFFFC);
      --Mem_nCurrentAllocations;
      Node_Remove((_DWORD **)v5);
      memset(*(void **)(v5 + 8), 0xCDu, *(_DWORD *)(v5 + 16));
      free((void *)v5);
      *p_ptMiddle = nullptr;
    }
    ++p_ptMiddle;
    --v4;
  }
  while ( v4 );
}

// source: h/2/terrain.c:5179  [size]
void __cdecl TerrainMap_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = TerrainMap_ptParameterList;
}

// source: h/2/terrain.c:5207  [size]
void __cdecl TerrainMap_UpdateInternalDataAfterLoadHandler(struct QTask_s *ptQTask)
{
  ;
}

// source: h/2/terrain.c:5225  [anchor-strings]
void __cdecl TerrainMap_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *FirstParentOfType; // eax
  bool v3; // c0
  bool v4; // c3
  struct Terrain_t *v5; // edi
  double v6; // st7
  struct QTask_s *ptParent; // eax
  struct QReference_s *ptHead; // eax
  int ptMiddle; // eax
  char v10; // cl
  int v11; // eax
  unsigned __int16 v12; // cx
  struct TerrainMap_t *i; // esi
  struct QTask_s *v14; // edx
  struct Terrain_t *ptTerrain; // [esp+10h] [ebp-4h]

  FirstParentOfType = QTask_GetFirstParentOfType(ptQTask, Terrain_eQTaskType);
  v3 = *(float *)&ptQTask[4].ptNext > 0.05000000074505806;
  v4 = 0.05000000074505806 == *(float *)&ptQTask[4].ptNext;
  v5 = (struct Terrain_t *)FirstParentOfType;
  ptTerrain = (struct Terrain_t *)FirstParentOfType;
  TerrainMap_isMipMapsUpdated = 1;
  if ( v3 || v4 )
  {
    if ( *(float *)&ptQTask[4].ptNext <= 0.5 )
      v6 = *(float *)&ptQTask[4].ptNext;
    else
      v6 = 0.5;
  }
  else
  {
    v6 = 0.05000000074505806;
  }
  *(float *)&ptQTask[4].ptNext = v6;
  ptQTask[3].tQTaskChildren.ptHead = FirstParentOfType[3].tQTaskChildren.ptTail;
  ptParent = ptQTask[1].ptParent;
  ptQTask[3].tQTaskChildren.ptMiddle = (struct QTask_s *)HIDWORD(v5->tPos.vZ);
  if ( !ptParent )
  {
    ptHead = ptQTask[4].tQTaskRefList.ptHead;
    if ( Terrain_aisIDTaken[(_DWORD)ptHead] )
    {
      LDebug_Error("Duplicate heightmap IDs");
      abort();
    }
    Terrain_aisIDTaken[(_DWORD)ptHead] = 1;
    ptQTask[1].ptParent = (struct QTask_s *)1;
  }
  ptMiddle = (int)ptQTask[2].tQTaskChildren.ptMiddle;
  if ( ptMiddle >= 1 )
  {
    if ( ptMiddle > 1024 )
      ptMiddle = 1024;
  }
  else
  {
    ptMiddle = 1;
  }
  ptQTask[2].tQTaskChildren.ptMiddle = (struct QTask_s *)ptMiddle;
  _BitScanReverse((unsigned int *)&ptMiddle, ptMiddle - 1);
  v10 = ptMiddle;
  v11 = (int)ptQTask[2].tQTaskRefList.ptHead;
  ptQTask[2].tQTaskChildren.ptMiddle = (struct QTask_s *)(1 << (v10 + 1));
  if ( v11 >= 1 )
  {
    if ( v11 > 1024 )
      v11 = 1024;
  }
  else
  {
    v11 = 1;
  }
  ptQTask[2].tQTaskRefList.ptHead = (struct QReference_s *)v11;
  _BitScanReverse((unsigned int *)&v11, v11 - 1);
  ptQTask[2].tQTaskRefList.ptHead = (struct QReference_s *)(1 << (v11 + 1));
  if ( ptQTask[1].ptPrev || ptQTask[2].ptPrev )
  {
    v12 = TerrainMap_eQTaskType;
    for ( i = (struct TerrainMap_t *)ptQTask;
          QTask_GetPrevSiblingOfType(&i->tQTask, v12);
          i = (struct TerrainMap_t *)QTask_GetPrevSiblingOfType(&i->tQTask, v12) )
    {
      ;
    }
    if ( ptQTask[2].ptPrev )
      ptQTask[2].ptNext = (struct QTask_s *)1;
    TerrainMap_ResampleAndAlign((struct TerrainMap_t *)ptQTask, i, v5);
    ptQTask[2].ptNext = nullptr;
    Terrain_UpdateSubmaps(v5);
    TerrainMap_isMipMapsUpdated = 0;
  }
  if ( ptQTask[1].tQTaskChildren.ptMiddle )
  {
    TerrainMap_SoftenHeightmapEdges(v5, (struct TerrainMap_t *)ptQTask, *(float *)&ptQTask[4].ptNext);
    TerrainMap_isMipMapsUpdated = 0;
  }
  if ( ptQTask[1].tQTaskChildren.ptTail )
    TerrainMap_SoftenLightmapEdges(v5, (struct TerrainMap_t *)ptQTask, *(float *)&ptQTask[4].ptNext);
  if ( ptQTask[1].tQTaskChildren.ptHead )
  {
    TerrainMap_LoadDEM((struct TerrainMap_t *)ptQTask, (char *)&ptQTask[10].ptParent);
    ptQTask[1].tQTaskChildren.ptHead = nullptr;
    TerrainMap_isMipMapsUpdated = 0;
  }
  if ( ptQTask[1].ptNext )
  {
    v14 = ptQTask[4].tQTaskChildren.ptHead;
    qmemcpy(&ptQTask[3].tQTaskChildren.ptTail, &ptQTask[2].ptParent, 0x18u);
    ptQTask[4].tQTaskChildren.ptMiddle = ptQTask[4].ptPrev;
    ptQTask[4].tQTaskChildren.ptTail = v14;
    TerrainMap_Free((struct TerrainMap_t *)ptQTask);
    TerrainMap_Alloc((struct TerrainMap_t *)ptQTask);
    Terrain_UpdateSubmaps(ptTerrain);
    v5 = ptTerrain;
    ptQTask[1].ptNext = nullptr;
  }
  if ( !TerrainMap_isMipMapsUpdated )
  {
    Terrain_MakeMipMaps(&v5->tDynCubeObj.tQObj.tQTask);
    TerrainMap_isMipMapsUpdated = 1;
  }
}

// source: h/2/terrain.c:5589  [anchor-strings]
void __cdecl TerrainMaterial_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  int i; // ecx

  ptQTask[29].tQTaskRefList.ptTail = nullptr;
  ptQTask[29].ptParent = nullptr;
  ptQTask[1].ptNext = nullptr;
  *(_DWORD *)&ptQTask[29].eQTaskType = 0;
  ptQTask[15].tQTaskChildren.ptHead = (struct QTask_s *)1120403456;
  ptQTask[29].tQTaskChildren.ptMiddle = (struct QTask_s *)1065353216;
  ptQTask[1].tQTaskChildren.ptHead = nullptr;
  LOBYTE(ptQTask[8].ptParent) = 0;
  LOBYTE(ptQTask[2].tQTaskChildren.ptTail) = 0;
  ptQTask[15].tQTaskChildren.ptMiddle = nullptr;
  LOBYTE(ptQTask[22].eQTaskType) = 0;
  LOBYTE(ptQTask[16].tQTaskRefList.ptHead) = 0;
  for ( i = 0; i < 10; ++i )
  {
    if ( !TerrainMaterial_aisIDTaken[i] )
      break;
  }
  if ( i == 10 )
  {
    LDebug_Error("Too many materials");
    abort();
  }
  ptQTask[1].ptPrev = (struct QTask_s *)i;
  Terrain_isRefreshToolbar = 1;
  TerrainMap_isMipMapsUpdated = 0;
}

// source: h/2/terrain.c:5647  [anchor-strings]
void __cdecl TerrainMaterial_DeleteHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptPrev; // eax
  _DWORD *p_ptMiddle; // esi
  int v3; // ebx

  ptPrev = ptQTask[1].ptPrev;
  if ( !TerrainMaterial_aisIDTaken[(_DWORD)ptPrev] )
  {
    LDebug_Error("ID error in material system");
    abort();
  }
  TerrainMaterial_aisIDTaken[(_DWORD)ptPrev] = 0;
  p_ptMiddle = &ptQTask[1].tQTaskChildren.ptMiddle;
  v3 = 2;
  do
  {
    if ( *(p_ptMiddle - 1) )
    {
      if ( AppContext_tAppContext.isMainMenu == false )
        RenderMode_atRenderMode[*p_ptMiddle].apfRenderModeMethod[Texture_eDeAllocTextureMethod](p_ptMiddle);
      memset(p_ptMiddle, 0, 0x2Cu);
      *(p_ptMiddle - 1) = 0;
    }
    p_ptMiddle += 141;
    --v3;
  }
  while ( v3 );
  Terrain_isRefreshToolbar = 1;
}

// source: h/2/terrain.c:5686  [size]
void __cdecl TerrainMaterial_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = TerrainMaterial_ptParameterList;
}

// source: h/2/terrain.c:5705  [anchor-callee]
void __cdecl TerrainMaterial_FixFilename(char *zFilename)
{
  unsigned int v1; // ecx
  unsigned int v2; // edx
  char v4; // al
  signed int v5; // edx
  signed int i; // eax
  char zTemp[256]; // [esp+0h] [ebp-100h] BYREF

  if ( strlen(zFilename) >= 0xFF )
    v1 = 255;
  else
    v1 = strlen(zFilename);
  v2 = v1;
  do
  {
    if ( !v1-- )
      break;
    v4 = zFilename[v1 - 1];
    if ( v4 == 47 )
      break;
  }
  while ( v4 != 92 );
  v5 = v2 - v1;
  for ( i = 0; i < v5; ++i )
    zTemp[i] = zFilename[v1 + i];
  zTemp[i] = 0;
  sprintf(zFilename, (char *const)&g_zFileName.aptSelectableItems[28], "MISSION:textures/", zTemp);
}

// source: h/2/terrain.c:5734  [anchor-strings]
void __cdecl TerrainMaterial_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  int v2; // eax
  double v3; // st7
  double v4; // st7
  struct QTask_s *ptPrev; // eax
  char *p_ptParent; // esi
  int v7; // ebp
  struct File_s *v8; // eax
  char zTemp[512]; // [esp+0h] [ebp-200h] BYREF

  v2 = *(_DWORD *)&ptQTask[29].eQTaskType;
  if ( v2 >= 0 )
  {
    if ( v2 > 2 )
      v2 = 2;
  }
  else
  {
    v2 = 0;
  }
  *(_DWORD *)&ptQTask[29].eQTaskType = v2;
  if ( *(float *)&ptQTask[15].tQTaskChildren.ptHead >= 1.0 )
    v3 = *(float *)&ptQTask[15].tQTaskChildren.ptHead;
  else
    v3 = 1.0;
  *(float *)&ptQTask[15].tQTaskChildren.ptHead = v3;
  if ( *(float *)&ptQTask[29].tQTaskChildren.ptMiddle >= 1.0 )
    v4 = *(float *)&ptQTask[29].tQTaskChildren.ptMiddle;
  else
    v4 = 1.0;
  *(float *)&ptQTask[29].tQTaskChildren.ptMiddle = v4;
  if ( !ptQTask[29].tQTaskRefList.ptTail )
  {
    ptPrev = ptQTask[1].ptPrev;
    if ( TerrainMaterial_aisIDTaken[(_DWORD)ptPrev] )
    {
      LDebug_Error("Duplicate heightmap IDs");
      abort();
    }
    TerrainMaterial_aisIDTaken[(_DWORD)ptPrev] = 1;
    ptQTask[29].tQTaskRefList.ptTail = (struct QReference_s *)1;
  }
  p_ptParent = (char *)&ptQTask[8].ptParent;
  v7 = 2;
  do
  {
    TerrainMaterial_FixFilename(p_ptParent);
    strncpy(zTemp, p_ptParent, 0x100u);
    if ( *p_ptParent && (!strstr(p_ptParent - 256, p_ptParent) || strlen(p_ptParent) != strlen(p_ptParent - 256)) )
    {
      if ( strstr(p_ptParent, "File not found") )
        goto LABEL_30;
      if ( Resource_IsLoadedInternal(zTemp, nullptr) == false )
      {
        v8 = File_New(zTemp, "r");
        if ( !v8 )
        {
LABEL_30:
          sprintf(p_ptParent, "File not found");
          goto LABEL_31;
        }
        if ( v8 == &File_tDummyAsyncFile )
          File_tDummyAsyncFile.isAsync = false;
        else
          File_atDevice[v8->eDeviceID].pfDelete(v8->eDeviceID, v8);
      }
      if ( *((_DWORD *)p_ptParent - 76) )
      {
        if ( AppContext_tAppContext.isMainMenu == false )
          RenderMode_atRenderMode[*((_DWORD *)p_ptParent - 75)].apfRenderModeMethod[Texture_eDeAllocTextureMethod](p_ptParent - 300);
        memset(p_ptParent - 300, 0, 0x2Cu);
        *((_DWORD *)p_ptParent - 76) = 0;
      }
      Texture_Load((struct TexInfo_s *)(p_ptParent - 300), nullptr, zTemp);
      *((_DWORD *)p_ptParent - 76) = 1;
    }
LABEL_31:
    sprintf(p_ptParent - 256, p_ptParent);
    p_ptParent += 564;
    --v7;
  }
  while ( v7 );
}

// source: h/2/terrain.c:6068  [size]
// attributes: thunk
void __cdecl Terrain_DrawEnvmapHandler(struct QTask_s *ptQTask, void *pxContext)
{
  Terrain_EnterHandler(ptQTask, pxContext);
}

// source: h/2/terrain.c:6081  [size]
void __cdecl Terrain_EnumerateEnvmapHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QObjectVector_s *v2; // esi
  unsigned int nAllocated; // eax
  struct QTask_s **v4; // ecx

  if ( (*((_BYTE *)pxContext + 8) & 2) != 0 )
  {
    v2 = *(struct QObjectVector_s **)pxContext;
    if ( *(_DWORD *)(*(_DWORD *)pxContext + 36) == *(_DWORD *)(*(_DWORD *)pxContext + 40) )
      QObjectVector_Realloc(v2, v2->nReallocSize);
    nAllocated = v2->nAllocated;
    v4 = (struct QTask_s **)v2->papxElement[nAllocated];
    v2->nAllocated = nAllocated + 1;
    *v4 = ptQTask;
    v4[1] = (struct QTask_s *)1;
  }
}

// source: h/2/terrain.c:6111  [size]
void __cdecl Terrain_EnumerateLightmapHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QObjectVector_s *v2; // esi
  unsigned int nAllocated; // eax
  struct QTask_s **v4; // ecx
  struct QTask_s *ptHead; // eax
  int v6; // edx
  struct QTask_s *v7; // ecx
  void (__cdecl *pfHandler)(struct QTask_s *, void *); // ecx
  int v9; // edx

  v2 = *(struct QObjectVector_s **)pxContext;
  if ( *(_DWORD *)(*(_DWORD *)pxContext + 36) == *(_DWORD *)(*(_DWORD *)pxContext + 40) )
    QObjectVector_Realloc(*(struct QObjectVector_s **)pxContext, v2->nReallocSize);
  nAllocated = v2->nAllocated;
  v4 = (struct QTask_s **)v2->papxElement[nAllocated];
  v2->nAllocated = nAllocated + 1;
  *v4 = ptQTask;
  ptHead = ptQTask->tQTaskChildren.ptHead;
  if ( ptHead->ptNext && ptHead )
  {
    v6 = QTask_nProtectedQTaskStackOffset;
    do
    {
      if ( ptHead->ptNext )
        v7 = ptHead->ptNext->ptNext != nullptr ? ptHead->ptNext : nullptr;
      else
        v7 = nullptr;
      QTask_atProtectedQTaskStack[v6].ptQTask = v7;
      pfHandler = (void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[Lightmap_eEnumerateQTaskEvent][ptHead->eQTaskType].pfHandler;
      v9 = v6 + 1;
      QTask_nProtectedQTaskStackOffset = v9;
      if ( pfHandler )
      {
        pfHandler(ptHead, pxContext);
        v9 = QTask_nProtectedQTaskStackOffset;
      }
      ptHead = (struct QTask_s *)dword_849C7DC[v9];
      v6 = v9 - 1;
      QTask_nProtectedQTaskStackOffset = v6;
    }
    while ( ptHead );
  }
}

// source: h/2/terrain.c:6134  [anchor-mhash]
void *__cdecl Terrain_DrawLightmapHandler(struct QTask_s *ptQTask, void *pxContext)
{
  if ( GlobalLightQTask_ptGlobalLight->isRadiosityTerrainShadows || *((_DWORD *)pxContext + 4) )
  {
    if ( *((_DWORD *)pxContext + 2) )
    {
      Terrain_ptDrawLightmapContext = (struct DrawLightmapContext_t *)pxContext;
      pxContext = (void *)((int (__cdecl *)(struct QTask_s *, _DWORD))QTask_aatQTaskFinalEvent[5][ptQTask->eQTaskType].pfHandler)(
                            ptQTask,
                            0);
      Terrain_ptDrawLightmapContext = nullptr;
    }
  }
  return pxContext;
}

// source: h/2/terrain.c:6160  [size]
void __cdecl Terrain_SetDetailLevel(float vDetail)
{
  Terrain_vManualDetail = vDetail;
}

// source: h/2/terrain.c:6173  [anchor-strings]
void __cdecl Terrain_Open()
{
  unsigned __int16 v0; // si
  unsigned __int16 BaseQTaskType; // ax
  unsigned __int16 v2; // si
  unsigned __int16 v3; // ax
  unsigned __int16 v4; // si
  struct ParameterList_s *v5; // eax
  int v6; // edx
  struct ParameterList_s *v7; // eax
  int v8; // edx
  struct ParameterList_s *v9; // eax
  int v10; // edx
  __int16 v11; // si

  v0 = QTask_NewQTaskType("Terrain", 36784, DynCubeObj_eQTaskType, 0, 0);
  Terrain_eQTaskType = v0;
  QTask_SetQTaskTypeGroup(v0, 0x80000000);
  QTask_LinkQTaskEventHandlerFn(v0, 0, Terrain_CreateHandler);
  QTask_LinkQTaskEventHandlerFn(v0, 5, Terrain_EnterHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Terrain_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(v0, ParameterList_eUpdateInternalDataQTaskEvent, Terrain_UpdateInternalDataHandler);
  QTask_LinkQTaskEventHandlerFn(v0, 10, Terrain_TraceLinesHandler1);
  QTask_LinkQTaskEventHandlerFn(v0, 11, Terrain_GetNextZHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(
    v0,
    Level_eUpdateInternalDataAfterLoadEvent,
    Terrain_UpdateInternalDataHandlerAfterLoad);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 2, Terrain_DeleteHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, DiscardTask_eUpdateDiscardMeshQTaskEvent, Terrain_UpdateDiscardMeshHandler);
  QTask_LinkQTaskEventHandlerFn(v0, Envmap_eDrawQTaskEvent, Terrain_DrawEnvmapHandler);
  QTask_LinkQTaskEventHandlerFn(v0, Envmap_eEnumerateQTaskEvent, Terrain_EnumerateEnvmapHandler);
  BaseQTaskType = QTask_GetBaseQTaskType();
  v2 = QTask_NewQTaskType("TerrainMap", 688, BaseQTaskType, 0, 0);
  TerrainMap_eQTaskType = v2;
  QTask_LinkQTaskEventHandlerFn(v2, 0, TerrainMap_CreateHandler);
  QTask_LinkQTaskEventHandlerFn(
    v2,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))TerrainMap_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(v2, ParameterList_eUpdateInternalDataQTaskEvent, TerrainMap_UpdateInternalDataHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(
    v2,
    Level_eUpdateInternalDataAfterLoadEvent,
    (void (__cdecl *)(struct QTask_s *))TerrainMap_UpdateInternalDataAfterLoadHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v2, 2, TerrainMap_DeleteHandler);
  v3 = QTask_GetBaseQTaskType();
  v4 = QTask_NewQTaskType("TerrainMaterial", 1200, v3, 0, 0);
  TerrainMaterial_eQTaskType = v4;
  QTask_LinkQTaskEventHandlerFn(v4, 0, TerrainMaterial_CreateHandler);
  QTask_LinkQTaskEventHandlerFn(
    v4,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))TerrainMaterial_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(
    v4,
    ParameterList_eUpdateInternalDataQTaskEvent,
    TerrainMaterial_UpdateInternalDataHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v4, 2, TerrainMaterial_DeleteHandler);
  v5 = (struct ParameterList_s *)Mem_AllocFn(432, 4);
  v5->ptParameterListItem = (struct ParameterListItem_s *)&v5[1];
  v6 = Level_eParameterTypeObjectPos;
  v5->nParameters = 0;
  v5->nMaxParameters = 21;
  Terrain_ptParameterList = v5;
  ParameterList_AddParameter(v5, 0x78u, v6, "Position", 7u, nullptr);
  ParameterList_AddParameter(Terrain_ptParameterList, 0xC0u, Level_eParameterTypeReal32, "World width", 7u, nullptr);
  ParameterList_AddParameter(Terrain_ptParameterList, 0xC4u, Level_eParameterTypeReal32, "World height", 7u, nullptr);
  ParameterList_AddParameter(Terrain_ptParameterList, 0xBCu, Level_eParameterTypeReal32, "Detail", 7u, nullptr);
  ParameterList_AddParameterMinMax(
    Terrain_ptParameterList,
    0xACu,
    Level_eParameterTypeReal32,
    "Adaption",
    7u,
    0.0,
    50.0);
  ParameterList_AddParameter(Terrain_ptParameterList, 0xB0u, Level_eParameterTypeReal32, "Brush size", 7u, nullptr);
  ParameterList_AddParameter(Terrain_ptParameterList, 0xB4u, Level_eParameterTypeReal32, "Brush power", 7u, nullptr);
  ParameterList_AddParameter(
    Terrain_ptParameterList,
    0xCCu,
    Level_eParameterTypePushButton,
    "Syncronize maps",
    6u,
    nullptr);
  ParameterList_AddParameter(
    Terrain_ptParameterList,
    0xD0u,
    Level_eParameterTypePushButton,
    "Update submaps",
    6u,
    nullptr);
  ParameterList_AddParameter(
    Terrain_ptParameterList,
    0xE0u,
    Level_eParameterTypePushButton,
    "Calculate lightmaps",
    6u,
    nullptr);
  ParameterList_AddParameter(
    Terrain_ptParameterList,
    0xE4u,
    Level_eParameterTypePushButton,
    "Calculate preview lightmaps",
    6u,
    nullptr);
  ParameterList_AddParameter(Terrain_ptParameterList, 0x10Cu, Level_eParameterTypeInt32, "Shadow samples", 7u, nullptr);
  ParameterList_AddParameter(Terrain_ptParameterList, 0xA8u, Level_eParameterTypeReal32, "Shadow spread", 7u, nullptr);
  ParameterList_AddParameter(Terrain_ptParameterList, 0xD8u, Level_eParameterTypePushButton, "Clear", 6u, nullptr);
  ParameterList_AddParameter(Terrain_ptParameterList, 0xDCu, Level_eParameterTypePushButton, "Generate", 6u, nullptr);
  ParameterList_AddParameter(
    Terrain_ptParameterList,
    0xFCu,
    Level_eParameterTypeReal32,
    "Minimum brush size",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Terrain_ptParameterList,
    0x100u,
    Level_eParameterTypeReal32,
    "Maximum brush size",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Terrain_ptParameterList,
    0x104u,
    Level_eParameterTypeReal32,
    "Minimum brush power",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Terrain_ptParameterList,
    0x108u,
    Level_eParameterTypeReal32,
    "Maximum brush power",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Terrain_ptParameterList,
    0x114u,
    Level_eParameterTypeInt32,
    "Number of brushes",
    7u,
    nullptr);
  v7 = (struct ParameterList_s *)Mem_AllocFn(252, 4);
  v7->ptParameterListItem = (struct ParameterListItem_s *)&v7[1];
  v8 = Level_eParameterTypeInt32;
  v7->nParameters = 0;
  v7->nMaxParameters = 12;
  TerrainMap_ptParameterList = v7;
  ParameterList_AddParameter(v7, 0xB4u, v8, "ID", 1u, nullptr);
  ParameterList_AddParameter(TerrainMap_ptParameterList, 0x5Cu, Level_eParameterTypeInt32, "Map width", 7u, nullptr);
  ParameterList_AddParameter(TerrainMap_ptParameterList, 0x64u, Level_eParameterTypeInt32, "Map height", 7u, nullptr);
  ParameterList_AddParameter(TerrainMap_ptParameterList, 0x70u, Level_eParameterTypeObjectPos, "Position", 7u, nullptr);
  ParameterList_AddParameter(TerrainMap_ptParameterList, 0xA4u, Level_eParameterTypeReal32, "World width", 7u, nullptr);
  ParameterList_AddParameter(TerrainMap_ptParameterList, 0xA8u, Level_eParameterTypeReal32, "World height", 7u, nullptr);
  ParameterList_AddParameter(TerrainMap_ptParameterList, 0x2Cu, Level_eParameterTypePushButton, "Apply", 6u, nullptr);
  ParameterList_AddParameter(TerrainMap_ptParameterList, 0x54u, Level_eParameterTypePushButton, "Sample", 6u, nullptr);
  ParameterList_AddParameter(
    TerrainMap_ptParameterList,
    0x34u,
    Level_eParameterTypePushButton,
    "Soften heightmap edges",
    6u,
    nullptr);
  ParameterList_AddParameter(
    TerrainMap_ptParameterList,
    0xA0u,
    Level_eParameterTypeReal32,
    "Soften edge size",
    7u,
    nullptr);
  ParameterList_AddParameter(
    TerrainMap_ptParameterList,
    0x1B0u,
    Level_eParameterTypeString256,
    "DEM File name",
    7u,
    nullptr);
  ParameterList_AddParameter(
    TerrainMap_ptParameterList,
    0x30u,
    Level_eParameterTypePushButton,
    "Import DEM",
    6u,
    nullptr);
  v9 = (struct ParameterList_s *)Mem_AllocFn(152, 4);
  v10 = Level_eParameterTypeInt32;
  v9->ptParameterListItem = (struct ParameterListItem_s *)&v9[1];
  v9->nParameters = 0;
  v9->nMaxParameters = 7;
  TerrainMaterial_ptParameterList = v9;
  ParameterList_AddParameter(v9, 0x2Cu, v10, "ID", 1u, nullptr);
  ParameterList_AddParameter(
    TerrainMaterial_ptParameterList,
    0x28u,
    Level_eParameterTypeInt32,
    "Game material",
    7u,
    nullptr);
  ParameterList_AddParameter(
    TerrainMaterial_ptParameterList,
    0x160u,
    Level_eParameterTypeString256,
    "Texture",
    7u,
    nullptr);
  ParameterList_AddParameter(
    TerrainMaterial_ptParameterList,
    0x394u,
    Level_eParameterTypeString256,
    "Detail texture",
    7u,
    nullptr);
  ParameterList_AddParameter(
    TerrainMaterial_ptParameterList,
    0x260u,
    Level_eParameterTypeReal32,
    "Texture scale",
    7u,
    nullptr);
  ParameterList_AddParameter(
    TerrainMaterial_ptParameterList,
    0x494u,
    Level_eParameterTypeReal32,
    "Detail texture scale",
    7u,
    nullptr);
  ParameterList_AddParameter(
    TerrainMaterial_ptParameterList,
    0x4ACu,
    Level_eParameterTypeInt32,
    "Mapping style",
    7u,
    nullptr);
  v11 = Level_eAllowSaveQTaskEvent;
  QTask_LinkQTaskEventHandlerFn(
    Terrain_eQTaskType,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveHandler);
  QTask_LinkQTaskEventHandlerFn(
    TerrainMap_eQTaskType,
    v11,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveNoChildrenHandler);
  QTask_LinkQTaskEventHandlerFn(
    TerrainMaterial_eQTaskType,
    v11,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveNoChildrenHandler);
  Terrain_ptQTaskList = QTaskList_New(10);
  Terrain_ptTracelinesHandler1ProfileRegion = nullptr;
  Terrain_ptTracelinesHandler2ProfileRegion = nullptr;
  Terrain_ptTracelinesHandler2FindMaterialProfileRegion = nullptr;
}

// source: h/2/terrain.c:6297  [anchor-hash]
void __cdecl Terrain_Close()
{
  int v0; // esi
  int v1; // esi
  int v2; // esi

  QTaskList_Delete(Terrain_ptQTaskList);
  if ( TerrainMaterial_ptParameterList )
  {
    v0 = *(_DWORD *)((unsigned int)&TerrainMaterial_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
  if ( TerrainMap_ptParameterList )
  {
    v1 = *(_DWORD *)((unsigned int)&TerrainMap_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v1);
    memset(*(void **)(v1 + 8), 0xCDu, *(_DWORD *)(v1 + 16));
    free((void *)v1);
  }
  if ( Terrain_ptParameterList )
  {
    v2 = *(_DWORD *)((unsigned int)&Terrain_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v2);
    memset(*(void **)(v2 + 8), 0xCDu, *(_DWORD *)(v2 + 16));
    free((void *)v2);
  }
  QTask_DeleteQTaskType(TerrainMaterialTool_eQTaskType);
  QTask_DeleteQTaskType(TerrainMaterial_eQTaskType);
  QTask_DeleteQTaskType(TerrainMap_eQTaskType);
  QTask_DeleteQTaskType(Terrain_eQTaskType);
}

// source: h/2/terrain.c:6322  [anchor-mhash]
struct QTask_s *__cdecl TerrainHeightmap_New(
        struct QTask_s *ptParent,
        struct real64x3_t *ptPos,
        float vWorldWidth,
        float vWorldHeight,
        int nWidth,
        int nHeight,
        float *pvData)
{
  float *v7; // ebp
  struct QTask_s *v8; // ebx
  int v9; // edx
  int v10; // esi
  int v11; // ecx
  int v12; // edx
  int v13; // edi
  int v14; // edx
  float *v15; // eax
  double v16; // st7
  char *v17; // edi
  int v18; // eax
  int v19; // edx
  double v20; // st7
  bool v21; // zf
  int v23; // [esp+8h] [ebp-14h]
  int j; // [esp+Ch] [ebp-10h]
  int v25; // [esp+10h] [ebp-Ch]
  int v26; // [esp+14h] [ebp-8h]
  float ptParenta = *(float *)&ptParent; // [esp+20h] [ebp+4h] ARGSLOT

  v7 = pvData;
  if ( QTask_IsQTaskTypeDerived(ptParent->eQTaskType, Terrain_eQTaskType) == false )
    return nullptr;
  v8 = QTask_NewFn(ptParent, TerrainMap_eQTaskType, nullptr);
  *(float *)&v8[4].tQTaskChildren.ptMiddle = vWorldWidth;
  v9 = ParameterList_eUpdateInternalDataQTaskEvent;
  v8[2].tQTaskChildren.ptMiddle = (struct QTask_s *)nWidth;
  *(float *)&v8[4].tQTaskChildren.ptTail = vWorldHeight;
  v8[2].tQTaskRefList.ptHead = (struct QReference_s *)nHeight;
  qmemcpy(&v8[3].tQTaskChildren.ptTail, ptPos, 0x18u);
  ptParenta = ptPos->vZ - *(double *)&ptParent[3].tQTaskChildren.ptTail;
  ((void (__cdecl *)(struct QTask_s *, _DWORD))QTask_aatQTaskFinalEvent[v9][v8->eQTaskType].pfHandler)(v8, 0);
  v10 = nWidth;
  if ( nWidth > 0 )
  {
    v11 = 0;
    v23 = 0;
    v25 = 0;
    v26 = nWidth;
    do
    {
      v12 = nHeight;
      v13 = 0;
      j = 0;
      if ( nHeight >= 4 )
      {
        v14 = 3;
        v15 = (float *)((char *)v7 + v11);
        do
        {
          v14 += 4;
          v11 += 16;
          *(float *)((char *)v8[7].ptNext + v11 - 16) = ptParenta + *v15;
          *(float *)((char *)v8[7].ptNext + v11 - 12) = ptParenta + v15[1];
          *(float *)((char *)v15 + 8 - (_DWORD)v7 + (unsigned int)v8[7].ptNext) = ptParenta + v15[2];
          v16 = ptParenta + v15[3];
          v17 = (char *)v15 + 12 - (_DWORD)v7;
          v15 += 4;
          *(float *)&v17[(unsigned int)v8[7].ptNext] = v16;
          v13 = j + 4;
          j += 4;
        }
        while ( v14 < nHeight );
        v7 = pvData;
        v11 = v25;
        v10 = nWidth;
        v12 = nHeight;
      }
      if ( v13 < v12 )
      {
        v18 = v13 + v23;
        v19 = v12 - v13;
        do
        {
          v20 = ptParenta + v7[v18++];
          --v19;
          *(float *)((char *)v8[7].ptNext + v18 * 4 - 4) = v20;
        }
        while ( v19 );
      }
      v11 += 4 * v10;
      v21 = v26 == 1;
      v23 += v10;
      v25 = v11;
      --v26;
    }
    while ( !v21 );
  }
  TerrainMap_isUpdated = 1;
  return v8;
}

// source: h/2/terrain.c:6381  [size]
unsigned __int16 __cdecl Terrain_GetQTaskType()
{
  return Terrain_eQTaskType;
}

// source: h/2/terrain.c:6398  [anchor-caller]
// local variable allocation has failed, the output may be wrong!
void __cdecl Terrain_GetZFromWorldCoordinates(double vWorldX, double vWorldY, double *pvOutZ)
{
  double v3; // st7
  int v4; // edi
  unsigned __int16 v5; // cx
  struct TerrainMap_t *v6; // edx
  struct QTask_s *FirstParentOfType; // eax
  double v8; // st6
  unsigned int nWidth; // esi
  unsigned int nHeight; // ebx
  double v11; // st5
  double v12; // st4
  double v13; // st5
  double v14; // st5
  double v15; // st7
  double v16; // st6
  double v17; // st6
  unsigned int v18; // ecx
  unsigned int v19; // edi
  unsigned int v20; // eax
  unsigned int v21; // ebx
  double v22; // st6
  float *pvHeightmap; // edx
  int v24; // eax
  double v25; // st7
  double v26; // st6
  double v27; // st5
  double v28; // st4
  double v29; // st3
  float vHMY; // [esp+0h] [ebp-20h]
  float vHMHalfY; // [esp+4h] [ebp-1Ch]
  float vOOScaleX; // [esp+8h] [ebp-18h]
  float vOOScaleY; // [esp+Ch] [ebp-14h]
  float avZ; // [esp+10h] [ebp-10h]
  float vWorldX_4; // [esp+28h] [ebp+8h] ARGSLOT
  float pvOutZa; // [esp+30h] [ebp+10h] ARGSLOT
  float pvOutZb; // [esp+30h] [ebp+10h] ARGSLOT

  v3 = *(double *)((char *)&vWorldX + 4) - Terrain_ptActiveTerrain->tPos.vX;
  pvOutZa = *(double *)((char *)&vWorldY + 4) - Terrain_ptActiveTerrain->tPos.vY;
  v4 = Terrain_nActiveHeightmaps - 1;
  if ( Terrain_nActiveHeightmaps - 1 < 0 )
  {
    v6 = (struct TerrainMap_t *)HIDWORD(vWorldX);
    v8 = *((float *)&vWorldX + 1);
    nWidth = HIDWORD(vWorldX);
    nHeight = HIDWORD(vWorldX);
  }
  else
  {
    v5 = Terrain_eQTaskType;
    do
    {
      v6 = Terrain_aptActiveHeightmap[v4];
      FirstParentOfType = QTask_GetFirstParentOfType(&v6->tQTask, v5);
      v8 = v6->tPos.vX - *(double *)&FirstParentOfType[3].ptNext;
      nWidth = v6->nWidth;
      nHeight = v6->nHeight;
      vHMY = v6->tPos.vY - *(double *)&FirstParentOfType[3].tQTaskChildren.ptHead;
      v11 = v6->vWorldWidth * 4096.0;
      v12 = v6->vWorldHeight * 4096.0;
      *((float *)&vWorldX + 1) = v11 * 0.5;
      vHMHalfY = 0.5 * v12;
      vOOScaleX = v11 / (double)nWidth;
      vOOScaleY = v12 / (double)nHeight;
      if ( !v4 )
        break;
      v13 = vOOScaleX * 0.5;
      if ( v3 > v8 - *((float *)&vWorldX + 1) + v13 && v3 < *((float *)&vWorldX + 1) + v8 - v13 )
      {
        v14 = vOOScaleY * 0.5;
        if ( vHMY - vHMHalfY + v14 < pvOutZa && pvOutZa < vHMHalfY + vHMY - v14 )
          break;
      }
      --v4;
    }
    while ( v4 >= 0 );
  }
  vWorldX_4 = (v3 - v8 + *((float *)&vWorldX + 1)) * (1.0 / vOOScaleX) - 0.5;
  v15 = (pvOutZa - vHMY + vHMHalfY) * (1.0 / vOOScaleY) - 0.5;
  if ( vWorldX_4 >= 0.0 )
  {
    v16 = (double)(nWidth - 1);
    if ( v16 < vWorldX_4 )
      vWorldX_4 = v16;
  }
  else
  {
    vWorldX_4 = 0.0;
  }
  if ( v15 >= 0.0 )
  {
    v17 = (double)(nHeight - 1);
    if ( v17 < v15 )
    {
      pvOutZb = v17;
      v15 = pvOutZb;
    }
  }
  else
  {
    v15 = 0.0;
  }
  v18 = (__int64)vWorldX_4;
  v19 = v18 + 1;
  v20 = (__int64)v15;
  if ( nWidth - 1 < v18 + 1 )
    v19 = nWidth - 1;
  v21 = nHeight - 1;
  if ( v21 >= v20 + 1 )
    v21 = v20 + 1;
  *((float *)&vWorldX + 1) = vWorldX_4 - (double)v18;
  v22 = (double)v20;
  pvHeightmap = v6->pvHeightmap;
  v24 = nWidth * v20;
  v25 = v15 - v22;
  v26 = pvHeightmap[v19 + v24];
  v27 = pvHeightmap[nWidth * v21 + v18];
  v29 = 1.0 - *((float *)&vWorldX + 1);
  if ( v29 < v25 )
  {
    v28 = pvHeightmap[v19 + nWidth * v21];
    *(double *)LODWORD(vWorldX) = v28 + (v26 - v28) * (1.0 - v25) + (v27 - v28) * v29 + Terrain_ptActiveTerrain->tPos.vZ;
  }
  else
  {
    avZ = pvHeightmap[v24 + v18];
    *(double *)LODWORD(vWorldX) = (v27 - avZ) * v25
                                + (v26 - avZ) * *((float *)&vWorldX + 1)
                                + Terrain_ptActiveTerrain->tPos.vZ
                                + avZ;
  }
}
