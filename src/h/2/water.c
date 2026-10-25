/* h/2/water.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: h/2/water.c:288  [anchor-strings]
char *__cdecl Water_GetResourceFilename(struct QTask_s *ptQTask, char *zFilename)
{
  int v2; // eax
  struct QReference_s *v3; // ecx

  v2 = 0;
  while ( 1 )
  {
    v3 = Level_atLevelQTaskID[v2];
    if ( v3 )
    {
      if ( v3->pxObject == ptQTask )
        break;
    }
    if ( ++v2 >= 4096 )
    {
      v2 = -1;
      break;
    }
  }
  sprintf(zFilename, "water_%d.res", v2);
  return zFilename;
}

// source: h/2/water.c:302  [anchor-callee]
void __cdecl Water_UpdateWaveBounds(struct Water_t *ptWater)
{
  struct QObjectVector_s *tWavePool; // edi
  signed int v2; // esi
  float *v3; // edx
  double vX; // st7
  double v5; // st7
  double vY; // st7
  double v7; // st7

  tWavePool = ptWater->tWavePool;
  ptWater->tWaveMax.vX = -3.4028234663852886e+38;
  ptWater->tWaveMin.vX = 3.4028234663852886e+38;
  ptWater->tWaveMax.vY = -3.4028234663852886e+38;
  ptWater->tWaveMin.vY = 3.4028234663852886e+38;
  v2 = 0;
  if ( (int)tWavePool->nAllocated > 0 )
  {
    do
    {
      v3 = (float *)tWavePool->papxElement[v2];
      vX = v3[6] + v3[11];
      if ( vX < ptWater->tWaveMax.vX )
        vX = ptWater->tWaveMax.vX;
      ptWater->tWaveMax.vX = vX;
      v5 = v3[6] - v3[11];
      if ( v5 > ptWater->tWaveMin.vX )
        v5 = ptWater->tWaveMin.vX;
      ptWater->tWaveMin.vX = v5;
      vY = v3[11] + v3[7];
      if ( vY < ptWater->tWaveMax.vY )
        vY = ptWater->tWaveMax.vY;
      ptWater->tWaveMax.vY = vY;
      v7 = v3[7] - v3[11];
      if ( v7 > ptWater->tWaveMin.vY )
        v7 = ptWater->tWaveMin.vY;
      ptWater->tWaveMin.vY = v7;
      ++v2;
    }
    while ( v2 < (signed int)ptWater->tWavePool->nAllocated );
  }
}

// source: h/2/water.c:332  [anchor-callee]
void __cdecl Water_UpdateWave(struct Water_t *ptWater, struct Wave_t *ptWave)
{
  double v2; // st7
  double v3; // st7

  if ( ptWater->nTick >= *(&ptWave->nDuration + 1) + ptWave->nDuration )
  {
    QObjectVector_RemoveElement(ptWater->tWavePool, *(_DWORD *)((char *)ptWave + ptWater->tWavePool->nElementSize - 4));
    Water_UpdateWaveBounds(ptWater);
  }
  v2 = (double)(ptWater->nTick - ptWave->nDuration) / (double)*(&ptWave->nDuration + 1);
  ptWave->vCurrentRadius = (1.0 - v2) * ptWave->vMaxRadius;
  v3 = v2 * (ptWave->vCurrentFrequency - *(float *)&ptWave->nStartTick) + *(float *)&ptWave->nStartTick;
  ptWave->vStart = v3;
  ptWave->vBumpRadius = v3 - (*(float *)&ptWave->nStartTick + *(float *)&ptWave->nStartTick);
}

// source: h/2/water.c:360  [anchor-callee]
void __cdecl Water_VertexFunction(
        float *pvOutRelativeZ,
        float *pvOutDeltaZ,
        struct real32x3_t *ptOutNormal,
        float vInX,
        float vInY,
        float vInZ,
        float vDistance)
{
  #pragma pack(push, 1)
  union
  {
    struct { _BYTE v32[20]; };
    struct { char igi2_o1[28]; float v33; };
    struct { char igi2_o2[28]; float v34; };
    struct { char igi2_o3[32]; float v35; };
    struct { char igi2_o4[32]; float v36; };
    struct { char igi2_o5[32]; float v37; };
    struct { char igi2_o6[32]; float v38; };
    struct { char igi2_o7[32]; float v39; };
    struct { char igi2_o8[36]; float v40; };
    struct { char igi2_o9[40]; float v41; };
    struct { char igi2_o10[40]; float v42; };
    struct { char igi2_o11[44]; float v43; };
    struct { char igi2_o12[52]; float v44; };
    struct { char igi2_o13[60]; double vWorldX; };
    struct { char igi2_o14[68]; float v46; };
    char igi2_extent[76];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct Water_t *v7; // esi
  double v8; // st7
  int v9; // ecx
  long double v10; // st7
  long double v11; // st6
  long double v12; // st5
  struct WaterLayer_t *v13; // eax
  double v14; // st3
  double v15; // st2
  struct QObjectVector_s *tWavePool; // edx
  int nAllocated; // ecx
  double v18; // st4
  double v19; // st4
  void **papxElement; // edx
  int v21; // edi
  float *v22; // ecx
  double v23; // st4
  double v24; // st3
  double v25; // st1
  bool v26; // cc
  long double v27; // st7
  long double v28; // st6
  long double v29; // st7
  float v30; // edx
  float v31; // ecx
  float vDistancea = *(float *)&vDistance; // [esp+64h] [ebp+1Ch] ARGSLOT
  float vDistanceb = *(float *)&vDistance; // [esp+64h] [ebp+1Ch] ARGSLOT
  float vDistancec = *(float *)&vDistance; // [esp+64h] [ebp+1Ch] ARGSLOT

  v7 = Water_ptActiveWater;
  v8 = vDistance * Water_ptActiveWater->vScaledFadeOut;
  if ( v8 <= 1.0 )
    v8 = 1.0;
  v9 = 0;
  vDistancea = 1.0 / v8;
  v10 = 0.0;
  igi2_frame.v35 = 0.0;
  v11 = 0.0;
  v12 = 0.0;
  if ( Water_nActiveLayers > 0 )
  {
    do
    {
      v13 = Water_aptActiveWaterLayer[v9];
      v14 = vInX * v13->tRotation.vX;
      ++v9;
      v15 = vInY * v13->tRotation.vY;
      igi2_frame.v36 = Water_vTime * v13->vSpeed;
      v10 = v10
          + sin((v15 + v14 + Water_ptActiveWater->vOffset) * v13->vScaledFreq + igi2_frame.v36) * v13->vScaledAmp * vDistancea;
      v11 = v11
          + sin(
              (v15 + (Water_vActiveSampleScale + vInX) * v13->tRotation.vX + Water_ptActiveWater->vOffset)
            * v13->vScaledFreq
            + igi2_frame.v36)
          * v13->vScaledAmp
          * vDistancea;
      igi2_frame.v33 = Water_vActiveSampleScale + vInY;
      v12 = v12
          + sin((v14 + igi2_frame.v33 * v13->tRotation.vY + Water_ptActiveWater->vOffset) * v13->vScaledFreq + igi2_frame.v36)
          * v13->vScaledAmp
          * vDistancea;
    }
    while ( v9 < Water_nActiveLayers );
    igi2_frame.v35 = v10;
  }
  tWavePool = Water_ptActiveWater->tWavePool;
  nAllocated = tWavePool->nAllocated;
  if ( nAllocated )
  {
    if ( vInX >= (double)Water_ptActiveWater->tWaveMin.vX )
    {
      v18 = Water_vActiveSampleScale + vInX;
      igi2_frame.v40 = v18;
      if ( v18 <= Water_ptActiveWater->tWaveMax.vX && vInY >= (double)Water_ptActiveWater->tWaveMin.vY )
      {
        v19 = Water_vActiveSampleScale + vInY;
        igi2_frame.v34 = v19;
        if ( v19 <= Water_ptActiveWater->tWaveMax.vY && nAllocated > 0 )
        {
          papxElement = tWavePool->papxElement;
          v21 = nAllocated;
          do
          {
            v22 = (float *)*papxElement;
            vDistanceb = *((float *)*papxElement + 13);
            if ( *((float *)*papxElement + 6) - vDistanceb <= vInX
              && vDistanceb + v22[6] >= igi2_frame.v40
              && v22[7] - vDistanceb <= vInY
              && vDistanceb + v22[7] >= igi2_frame.v34 )
            {
              v23 = vInX - v22[6];
              igi2_frame.v43 = v23;
              v24 = vInY - v22[7];
              igi2_frame.v37 = sqrt(igi2_frame.v43 * igi2_frame.v43 + v24 * v24);
              if ( igi2_frame.v37 < (double)v22[13] && igi2_frame.v37 > (double)v22[14] && igi2_frame.v37 > (double)v22[9] )
                v10 = v10 + (1.0 - cos((igi2_frame.v37 - v22[14]) * 6.2831854820251465 / (v22[15] + v22[15]))) * v22[12];
              igi2_frame.v44 = igi2_frame.v40 - v22[6];
              igi2_frame.v41 = v24;
              igi2_frame.v38 = sqrt(igi2_frame.v44 * igi2_frame.v44 + igi2_frame.v41 * igi2_frame.v41);
              if ( igi2_frame.v38 < (double)v22[13] && igi2_frame.v38 > (double)v22[14] && igi2_frame.v38 > (double)v22[9] )
                v11 = v11 + (1.0 - cos((igi2_frame.v38 - v22[14]) * 6.2831854820251465 / (v22[15] + v22[15]))) * v22[12];
              *(float *)&igi2_frame.vWorldX = v23;
              v25 = igi2_frame.v34 - v22[7];
              igi2_frame.v39 = sqrt(*(float *)&igi2_frame.vWorldX * *(float *)&igi2_frame.vWorldX + v25 * v25);
              if ( igi2_frame.v39 < (double)v22[13] && igi2_frame.v39 > (double)v22[14] && igi2_frame.v39 > (double)v22[9] )
                v12 = v12 + (1.0 - cos((igi2_frame.v39 - v22[14]) * 6.2831854820251465 / (v22[15] + v22[15]))) * v22[12];
            }
            ++papxElement;
            --v21;
          }
          while ( v21 );
          igi2_frame.v35 = v10;
        }
      }
    }
  }
  v26 = WaterRender_iQualityLevel <= 0;
  vDistancec = v11 - v10;
  igi2_frame.v42 = v12 - v10;
  *pvOutRelativeZ = v10 - vInZ;
  if ( v26 )
  {
    *pvOutDeltaZ = 0.0;
  }
  else
  {
    *(double *)&igi2_frame.v32[12] = vInY + v7->tPos.vY;
    *(double *)&igi2_frame.v32[4] = vInX + v7->tPos.vX;
    *(_DWORD *)igi2_frame.v32 = &igi2_frame.vWorldX;
    Terrain_GetZFromWorldCoordinates(*(double *)igi2_frame.v32, *(double *)&igi2_frame.v32[8], *(double **)&igi2_frame.v32[16]);
    v27 = fabs(igi2_frame.v35 + v7->tPos.vZ - igi2_frame.vWorldX);
    v28 = v7->vAbsorptionLength * 4096.0;
    if ( v27 <= v28 )
      *pvOutDeltaZ = 1.0 - v27 / v28;
    else
      *pvOutDeltaZ = 0.0;
  }
  *(float *)&igi2_frame.vWorldX = -(Water_vActiveSampleScale * vDistancec);
  *((float *)&igi2_frame.vWorldX + 1) = -(Water_vActiveSampleScale * igi2_frame.v42);
  igi2_frame.v46 = Water_vActiveSampleScale * Water_vActiveSampleScale;
  if ( *(float *)&igi2_frame.vWorldX != 0.0 || *((float *)&igi2_frame.vWorldX + 1) != 0.0 || igi2_frame.v46 != 0.0 )
  {
    v29 = 1.0
        / sqrt(*(float *)&igi2_frame.vWorldX * *(float *)&igi2_frame.vWorldX + *((float *)&igi2_frame.vWorldX + 1) * *((float *)&igi2_frame.vWorldX + 1) + igi2_frame.v46 * igi2_frame.v46);
    *(float *)&igi2_frame.vWorldX = *(float *)&igi2_frame.vWorldX * v29;
    *((float *)&igi2_frame.vWorldX + 1) = *((float *)&igi2_frame.vWorldX + 1) * v29;
    igi2_frame.v46 = igi2_frame.v46 * v29;
  }
  v30 = *((float *)&igi2_frame.vWorldX + 1);
  ptOutNormal->vX = *(float *)&igi2_frame.vWorldX;
  v31 = igi2_frame.v46;
  ptOutNormal->vY = v30;
  ptOutNormal->vZ = v31;
}

// source: h/2/water.c:514  [size]
void __cdecl Water_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = Water_ptParameterList;
}

// source: h/2/water.c:533  [anchor-strings]
void __cdecl Water_CreateResourceFile(char *zResourceFileName, int nFiles, char *pzFileList, int nNameLength)
{
  #pragma pack(push, 1)
  union
  {
    struct { char Buffer[256]; };
    struct { char igi2_o1[256]; char v14[256]; };
    struct { char igi2_o2[512]; char zFilename[1024]; };
    char igi2_extent[1536];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct File_s *v4; // ebp
  int v5; // edi
  char *v6; // esi
  char v7; // al
  int v8; // ecx
  char *v9; // eax
  char *v10; // edx
  char v11; // cl
  char *v12; // esi

  v4 = File_New("LOCAL:WaterMergeScript.tmp", "w");
  if ( v4 )
  {
    strcpy(igi2_frame.zFilename, "// This file is generated by Water and can safely be deleted\n\n");
    File_atDevice[v4->eDeviceID].pfWrite(v4->eDeviceID, v4, igi2_frame.zFilename, strlen(igi2_frame.zFilename));
    sprintf(igi2_frame.Buffer, "%s/%s", "MISSION:envmaps", zResourceFileName);
    File_SubstituteAlias(igi2_frame.zFilename, igi2_frame.Buffer, 0, false);
    strcpy(igi2_frame.Buffer, File_GetRealFilename(igi2_frame.zFilename));
    sprintf(igi2_frame.zFilename, "BeginResource(\"%s\");\n\n", igi2_frame.Buffer);
    File_atDevice[v4->eDeviceID].pfWrite(v4->eDeviceID, v4, igi2_frame.zFilename, strlen(igi2_frame.zFilename));
    v5 = nFiles;
    if ( nFiles > 0 )
    {
      v6 = pzFileList;
      do
      {
        File_SubstituteAlias(igi2_frame.v14, v6, 0, false);
        if ( File_IsValidDevicename(nullptr, igi2_frame.v14) && (v7 = igi2_frame.v14[0], v8 = 0, igi2_frame.v14[0]) )
        {
          while ( v7 != 58 )
          {
            v7 = igi2_frame.v14[++v8];
            if ( !v7 )
              goto LABEL_8;
          }
          v9 = &igi2_frame.v14[v8 + 1];
        }
        else
        {
LABEL_8:
          v9 = igi2_frame.v14;
        }
        v10 = (char *)(igi2_frame.Buffer - v9);
        do
        {
          v11 = *v9;
          v9[(_DWORD)v10] = *v9;
          ++v9;
        }
        while ( v11 );
        sprintf(igi2_frame.zFilename, "AddResource(\"%s\", \"%s\");\n", igi2_frame.Buffer, v6 + 16);
        File_atDevice[v4->eDeviceID].pfWrite(v4->eDeviceID, v4, igi2_frame.zFilename, strlen(igi2_frame.zFilename));
        v6 += nNameLength;
        --v5;
      }
      while ( v5 );
      v5 = nFiles;
    }
    strcpy(igi2_frame.zFilename, "\nEndResource();\n");
    File_atDevice[v4->eDeviceID].pfWrite(v4->eDeviceID, v4, igi2_frame.zFilename, strlen(igi2_frame.zFilename));
    if ( v4 == &File_tDummyAsyncFile )
      File_tDummyAsyncFile.isAsync = false;
    else
      File_atDevice[v4->eDeviceID].pfDelete(v4->eDeviceID, v4);
    File_Remove("LOCAL:WaterMergeScript.tmp");
    if ( v5 > 0 )
    {
      v12 = pzFileList;
      do
      {
        File_Remove(v12);
        v12 += nNameLength;
        --v5;
      }
      while ( v5 );
    }
  }
}

// source: h/2/water.c:616  [size~]
void __cdecl Water_LoadEnvmapData(struct Water_t *ptWater)
{
  #pragma pack(push, 1)
  union
  {
    struct { int *p_isValid; };
    struct { char igi2_o1[4]; int v17; };
    struct { char igi2_o2[8]; unsigned int pnSize; };
    struct { char igi2_o3[12]; _BYTE v19[4]; };
    struct { char igi2_o4[16]; _BYTE v20[4]; };
    struct { char igi2_o5[20]; _BYTE v21[4]; };
    struct { char igi2_o6[24]; _BYTE v22[4]; };
    struct { char igi2_o7[28]; _BYTE v23[4]; };
    struct { char igi2_o8[32]; char v24[16]; };
    struct { char igi2_o9[48]; struct Envmap_t ptEnvmap; };
    char igi2_extent[328];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct Water_t *v1; // ebx
  int v2; // eax
  _DWORD *v3; // ebp
  int v4; // edi
  int v5; // eax
  struct QReference_s *v6; // ecx
  struct File_s *v7; // eax
  int v8; // eax
  struct QReference_s *v9; // ecx
  struct File_s *v10; // eax
  int v11; // eax
  struct QReference_s *v12; // ecx
  int v13; // ecx
  struct File_s *v14; // eax
  bool v15; // zf

  memset(&igi2_frame.ptEnvmap, 0, 0x18u);
  *(_DWORD *)igi2_frame.v24 = &unk_706D62;
  if ( WaterRender_iQualityLevel <= 0 )
    return;
  v1 = ptWater;
  v2 = scprintf(ptWater->zResourceList, "%d %d %d %d %d", igi2_frame.v19, igi2_frame.v20, igi2_frame.v21, igi2_frame.v22, igi2_frame.v23);
  if ( v2 <= 0 )
    return;
  v3 = igi2_frame.v19;
  igi2_frame.p_isValid = &ptWater->atEnvmapPool[0].isValid;
  igi2_frame.v17 = v2;
  ptWater->atEnvmapPool[0].eEnvmapType = ENVMAP_TYPE_CUBIC;
  v4 = 0;
  while ( 2 )
  {
    while ( 2 )
    {
      *igi2_frame.p_isValid = 0;
      v5 = 0;
      while ( 1 )
      {
        v6 = Level_atLevelQTaskID[v5];
        if ( v6 )
        {
          if ( v6->pxObject == v1 )
            break;
        }
        if ( ++v5 >= 4096 )
        {
          v5 = -1;
          break;
        }
      }
      sprintf((char *const)&igi2_frame.ptEnvmap.tCameraPos.vZ, "%s/cubemap_%d_%03d_%d.%s", "MISSION:envmaps", v5, *v3, v4, igi2_frame.v24);
      if ( Resource_IsLoadedInternal((char *)&igi2_frame.ptEnvmap.tCameraPos.vZ, nullptr) == false )
      {
        v7 = File_New((char *)&igi2_frame.ptEnvmap.tCameraPos.vZ, "r");
        if ( v7 )
        {
          if ( v7 == &File_tDummyAsyncFile )
            File_tDummyAsyncFile.isAsync = false;
          else
            File_atDevice[v7->eDeviceID].pfDelete(v7->eDeviceID, v7);
        }
        else
        {
          v8 = 0;
          while ( 1 )
          {
            v9 = Level_atLevelQTaskID[v8];
            if ( v9 )
            {
              if ( v9->pxObject == ptWater )
                break;
            }
            if ( ++v8 >= 4096 )
            {
              v8 = -1;
              break;
            }
          }
          sprintf((char *const)&igi2_frame.ptEnvmap.tCameraPos.vZ, "cubemap_%d_%03d_%d.%s", v8, *v3, v4, igi2_frame.v24);
        }
      }
      if ( Resource_IsLoadedInternal((char *)&igi2_frame.ptEnvmap.tCameraPos.vZ, nullptr) == false )
      {
        v10 = File_New((char *)&igi2_frame.ptEnvmap.tCameraPos.vZ, "r");
        if ( v10 )
        {
          if ( v10 == &File_tDummyAsyncFile )
            File_tDummyAsyncFile.isAsync = false;
          else
            File_atDevice[v10->eDeviceID].pfDelete(v10->eDeviceID, v10);
        }
        else
        {
          v11 = 0;
          while ( 1 )
          {
            v12 = Level_atLevelQTaskID[v11];
            if ( v12 )
            {
              if ( v12->pxObject == ptWater )
                break;
            }
            if ( ++v11 >= 4096 )
            {
              v13 = -1;
              goto LABEL_32;
            }
          }
          v13 = v11;
LABEL_32:
          sprintf(
            (char *const)&igi2_frame.ptEnvmap.tCameraPos.vZ,
            "LOCAL:missions/location%d/level%d/envmaps/cubemap_%d_%03d_%d.%s",
            Game_iMissionID / 10,
            Game_iMissionID % 10,
            v13,
            *v3,
            v4,
            igi2_frame.v24);
        }
      }
      if ( Resource_IsLoadedInternal((char *)&igi2_frame.ptEnvmap.tCameraPos.vZ, nullptr) )
        goto LABEL_39;
      v14 = File_New((char *)&igi2_frame.ptEnvmap.tCameraPos.vZ, "r");
      if ( v14 )
      {
        if ( v14 == &File_tDummyAsyncFile )
          File_tDummyAsyncFile.isAsync = false;
        else
          File_atDevice[v14->eDeviceID].pfDelete(v14->eDeviceID, v14);
LABEL_39:
        (&igi2_frame.ptEnvmap.ptCubemap)[v4] = (struct IDirect3DCubeTexture8 *)Resource_Load(
                                                                      (char *)&igi2_frame.ptEnvmap.tCameraPos.vZ,
                                                                      &igi2_frame.pnSize);
        *igi2_frame.p_isValid = 1;
      }
      if ( ++v4 < 6 )
      {
        v1 = ptWater;
        continue;
      }
      break;
    }
    if ( *igi2_frame.p_isValid )
      Envmap_LoadFromMemory((struct Envmap_t *)(igi2_frame.p_isValid - 23), (unsigned __int8 **)&igi2_frame.ptEnvmap, igi2_frame.pnSize);
    ++v3;
    v15 = igi2_frame.v17 == 1;
    igi2_frame.p_isValid += 24;
    --igi2_frame.v17;
    if ( !v15 )
    {
      v1 = ptWater;
      *(igi2_frame.p_isValid - 4) = 1;
      v4 = 0;
      continue;
    }
    break;
  }
}

int __cdecl sub_5A9FC0(char *a1)
{
  unsigned int v1; // ecx
  unsigned int v2; // edx
  char v4; // al
  signed int v5; // edx
  signed int i; // eax
  _BYTE v8[256]; // [esp+0h] [ebp-100h] BYREF

  if ( strlen(a1) >= 0xFF )
    v1 = 255;
  else
    v1 = strlen(a1);
  v2 = v1;
  do
  {
    if ( !v1-- )
      break;
    v4 = a1[v1 - 1];
    if ( v4 == 47 )
      break;
  }
  while ( v4 != 92 );
  v5 = v2 - v1;
  for ( i = 0; i < v5; ++i )
    v8[i] = a1[v1 + i];
  v8[i] = 0;
  return sprintf(a1, (char *const)&g_zFileName.aptSelectableItems[28], "MISSION:textures/", v8);
}

void __cdecl Water_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { float ptDynCubeObj; };
    struct { char igi2_o1[20]; int v48; };
    struct { char igi2_o2[24]; char zFilename[4]; };
    struct { char igi2_o3[28]; int v50; };
    struct { char igi2_o4[32]; _BYTE v51[4]; };
    struct { char igi2_o5[36]; _BYTE v52[4]; };
    struct { char igi2_o6[40]; _BYTE v53[4]; };
    struct { char igi2_o7[44]; _BYTE v54[4]; };
    struct { char igi2_o8[48]; _BYTE v55[4]; };
    struct { char igi2_o9[52]; char v56[16]; };
    struct { char igi2_o10[68]; char v57[256]; };
    struct { char igi2_o11[324]; char pptResource[256]; };
    struct { char igi2_o12[580]; char isConvertToUpperCase[256]; };
    struct { char igi2_o13[836]; char Buffer[256]; };
    struct { char igi2_o14[1092]; char Destination[512]; };
    struct { char igi2_o15[1604]; char pzFileList[7908]; };
    char igi2_extent[9512];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *v2; // ebx
  struct QTask_s **p_ptMiddle; // ebp
  int v4; // esi
  _DWORD *v5; // ebx
  int v6; // eax
  struct QReference_s *v7; // ecx
  struct File_s *v8; // eax
  char *v9; // ecx
  void *v10; // eax
  BOOL v11; // ecx
  struct QTask_s *ptHead; // eax
  unsigned int v13; // eax
  struct QTask_s *v14; // eax
  unsigned int v15; // eax
  struct QTask_s *v16; // eax
  unsigned int v17; // eax
  struct QTask_s *v18; // eax
  unsigned int v19; // eax
  struct QTask_s *v20; // eax
  unsigned int v21; // eax
  unsigned int ptPrev; // edx
  unsigned int v23; // eax
  int v24; // eax
  struct QReference_s *v25; // ecx
  char v26; // al
  int v27; // ecx
  char *v28; // eax
  int v29; // edx
  char v30; // cl
  struct Envmap_t *v31; // ebx
  struct QTask_s *ptNext; // eax
  char v33; // al
  int v34; // ecx
  char *v35; // eax
  int v36; // edx
  char v37; // cl
  int v38; // edi
  _DWORD *v39; // ebp
  char *v40; // ebx
  int i; // edi
  int v42; // eax
  struct QReference_s *v43; // ecx
  int v44; // eax
  struct QReference_s *v45; // ecx
  struct QTask_s *ptParent; // eax

  v2 = ptQTask;
  if ( !WaterRender_iQualityLevel )
  {
    p_ptMiddle = &ptQTask[12].tQTaskChildren.ptMiddle;
    v4 = 2;
    do
    {
      sub_5A9FC0((char *)p_ptMiddle);
      strncpy(igi2_frame.Destination, (char *)p_ptMiddle, 0x100u);
      if ( *(_BYTE *)p_ptMiddle
        && (!strstr((char *)p_ptMiddle - 256, (char *)p_ptMiddle)
         || strlen((char *)p_ptMiddle) != strlen((char *)p_ptMiddle - 256)) )
      {
        if ( !strstr((char *)p_ptMiddle, "File not found")
          && (Resource_IsLoadedInternal(igi2_frame.Destination, nullptr) || File_Exists(igi2_frame.Destination)) )
        {
          v5 = p_ptMiddle + 65;
          if ( p_ptMiddle[64] )
          {
            if ( AppContext_tAppContext.isMainMenu == false )
              RenderMode_atRenderMode[*v5].apfRenderModeMethod[Texture_eDeAllocTextureMethod](p_ptMiddle + 65);
            memset(v5, 0, 0x2Cu);
            p_ptMiddle[64] = nullptr;
          }
          Texture_Load((struct TexInfo_s *)(p_ptMiddle + 65), nullptr, igi2_frame.Destination);
          p_ptMiddle[64] = (struct QTask_s *)1;
        }
        else
        {
          sprintf((char *const)p_ptMiddle, "File not found");
        }
        v2 = ptQTask;
      }
      sprintf((char *const)p_ptMiddle - 256, (char *const)p_ptMiddle);
      p_ptMiddle += 140;
      --v4;
    }
    while ( v4 );
  }
  if ( v2[50].tQTaskChildren.ptHead )
  {
    v6 = 0;
    while ( 1 )
    {
      v7 = Level_atLevelQTaskID[v6];
      if ( v7 )
      {
        if ( v7->pxObject == v2 )
          break;
      }
      if ( ++v6 >= 4096 )
      {
        v6 = -1;
        break;
      }
    }
    sprintf(igi2_frame.Buffer, "water_%d.res", v6);
    sprintf(igi2_frame.pptResource, "%s/%s", "MISSION:envmaps", igi2_frame.Buffer);
    if ( Resource_IsLoadedInternal(igi2_frame.pptResource, nullptr) == false )
    {
      v8 = File_New(igi2_frame.pptResource, "r");
      if ( !v8 )
      {
LABEL_33:
        Water_LoadEnvmapData((struct Water_t *)ptQTask);
        ptQTask[50].tQTaskChildren.ptHead = nullptr;
        v2 = ptQTask;
        goto LABEL_34;
      }
      if ( v8 == &File_tDummyAsyncFile )
        File_tDummyAsyncFile.isAsync = false;
      else
        File_atDevice[v8->eDeviceID].pfDelete(v8->eDeviceID, v8);
    }
    if ( Resource_IsLoadedInternal(igi2_frame.pptResource, (struct Resource_s **)igi2_frame.zFilename) )
    {
      *(_DWORD *)(*(_DWORD *)igi2_frame.zFilename + 44) = 1;
    }
    else
    {
      Game_MPRunNetwork(v9);
      v10 = File_Load(igi2_frame.pptResource, (unsigned int *)igi2_frame.zFilename);
      if ( !v10 )
      {
        LDebug_Error("Failed to load resource: '%s'", igi2_frame.pptResource);
        abort();
      }
      Resource_ParseFile(File_zLastSubstitutedPath, v10, *(unsigned int *)igi2_frame.zFilename);
    }
    goto LABEL_33;
  }
LABEL_34:
  if ( v2[50].tQTaskRefList.ptMiddle )
  {
    v11 = LOBYTE(v2[52].tQTaskRefList.ptTail) != 0;
    v2[36].ptNext = nullptr;
    *(_DWORD *)&v2[35].eQTaskType = v11;
    ptHead = v2[36].tQTaskChildren.ptHead;
    if ( BYTE1(v2[52].tQTaskRefList.ptTail) )
      v13 = (unsigned int)ptHead | 1;
    else
      v13 = (unsigned int)ptHead & 0xFFFFFFFE;
    v2[36].tQTaskChildren.ptHead = (struct QTask_s *)v13;
    v14 = v2[36].tQTaskChildren.ptHead;
    if ( BYTE2(v2[52].tQTaskRefList.ptTail) )
      v15 = (unsigned int)v14 | 2;
    else
      v15 = (unsigned int)v14 & 0xFFFFFFFD;
    v2[36].tQTaskChildren.ptHead = (struct QTask_s *)v15;
    v16 = v2[36].tQTaskChildren.ptHead;
    if ( HIBYTE(v2[52].tQTaskRefList.ptTail) )
      v17 = (unsigned int)v16 | 4;
    else
      v17 = (unsigned int)v16 & 0xFFFFFFFB;
    v2[36].tQTaskChildren.ptHead = (struct QTask_s *)v17;
    v18 = v2[36].tQTaskChildren.ptHead;
    if ( LOBYTE(v2[52].ptParent) )
      v19 = (unsigned int)v18 | 8;
    else
      v19 = (unsigned int)v18 & 0xFFFFFFF7;
    v2[36].tQTaskChildren.ptHead = (struct QTask_s *)v19;
    v20 = v2[36].tQTaskChildren.ptHead;
    if ( BYTE1(v2[52].ptParent) )
      v21 = (unsigned int)v20 | 0x10;
    else
      v21 = (unsigned int)v20 & 0xFFFFFFEF;
    ptPrev = (unsigned int)v2[36].ptPrev;
    v2[36].tQTaskChildren.ptHead = (struct QTask_s *)v21;
    _BitScanReverse(&v23, ptPrev);
    v2[36].ptPrev = (struct QTask_s *)(1 << v23);
  }
  if ( v2[50].tQTaskChildren.ptTail )
  {
    if ( !LOBYTE(ptQTask[52].tQTaskRefList.ptTail) )
    {
      if ( ptQTask == (struct QTask_s *)-1719 )
        goto LABEL_80;
      sprintf(igi2_frame.isConvertToUpperCase, "%s/%s", "MISSION:envmaps", (char *)&ptQTask[42].isInMemPool + 1);
      File_SubstituteAlias(igi2_frame.v57, igi2_frame.isConvertToUpperCase, 0, false);
      if ( File_IsValidDevicename(nullptr, igi2_frame.v57) && (v33 = igi2_frame.v57[0], v34 = 0, igi2_frame.v57[0]) )
      {
        while ( v33 != 58 )
        {
          v33 = igi2_frame.v57[++v34];
          if ( !v33 )
            goto LABEL_75;
        }
        v35 = &igi2_frame.v57[v34 + 1];
      }
      else
      {
LABEL_75:
        v35 = igi2_frame.v57;
      }
      v36 = igi2_frame.isConvertToUpperCase - v35;
      do
      {
        v37 = *v35;
        v35[v36] = *v35;
        ++v35;
      }
      while ( v37 );
      v31 = (struct Envmap_t *)&ptQTask[34];
      goto LABEL_79;
    }
    v24 = 0;
    while ( 1 )
    {
      v25 = Level_atLevelQTaskID[v24];
      if ( v25 )
      {
        if ( v25->pxObject == ptQTask )
          break;
      }
      if ( ++v24 >= 4096 )
      {
        v24 = -1;
        break;
      }
    }
    sprintf(igi2_frame.isConvertToUpperCase, "%s/cubemap_%d_%03d", "MISSION:envmaps", v24, ptQTask[50].ptNext);
    File_SubstituteAlias(igi2_frame.v57, igi2_frame.isConvertToUpperCase, 0, false);
    if ( File_IsValidDevicename(nullptr, igi2_frame.v57) && (v26 = igi2_frame.v57[0], v27 = 0, igi2_frame.v57[0]) )
    {
      while ( v26 != 58 )
      {
        v26 = igi2_frame.v57[++v27];
        if ( !v26 )
          goto LABEL_62;
      }
      v28 = &igi2_frame.v57[v27 + 1];
    }
    else
    {
LABEL_62:
      v28 = igi2_frame.v57;
    }
    v29 = igi2_frame.isConvertToUpperCase - v28;
    do
    {
      v30 = *v28;
      v28[v29] = *v28;
      ++v28;
    }
    while ( v30 );
    v31 = (struct Envmap_t *)&ptQTask[34];
    if ( ptQTask[34].ptNext
      || (ptNext = ptQTask[50].ptNext, (unsigned int)ptNext <= 5)
      && (v31 = (struct Envmap_t *)((char *)&ptQTask[53] + 96 * (_DWORD)ptNext), v31->ptCubemap) )
    {
LABEL_79:
      Envmap_Save(v31, igi2_frame.isConvertToUpperCase);
    }
  }
LABEL_80:
  if ( ptQTask[50].tQTaskRefList.ptHead )
  {
    igi2_frame.v50 = 0;
    *(_DWORD *)igi2_frame.v56 = &unk_706D62;
    v38 = scprintf((char *const)&ptQTask[36].tQTaskRefList.ptMiddle, "%d %d %d %d %d", igi2_frame.v51, igi2_frame.v52, igi2_frame.v53, igi2_frame.v54, igi2_frame.v55);
    igi2_frame.v48 = v38;
    if ( *(&ptQTask[42].isInMemPool + 1) )
    {
      sprintf(igi2_frame.pzFileList, "%s/%s.%s", "MISSION:envmaps", (char *)&ptQTask[42].isInMemPool + 1, igi2_frame.v56);
      igi2_frame.v50 = 1;
    }
    if ( v38 > 0 )
    {
      v39 = igi2_frame.v51;
      v40 = &igi2_frame.pzFileList[255 * igi2_frame.v50];
      *(_DWORD *)igi2_frame.zFilename = v38;
      do
      {
        for ( i = 0; i < 6; ++i )
        {
          v42 = 0;
          while ( 1 )
          {
            v43 = Level_atLevelQTaskID[v42];
            if ( v43 )
            {
              if ( v43->pxObject == ptQTask )
                break;
            }
            if ( ++v42 >= 4096 )
            {
              v42 = -1;
              break;
            }
          }
          sprintf(v40, "%s/cubemap_%d_%03d_%d.%s", "MISSION:envmaps", v42, *v39, i, igi2_frame.v56);
          v40 += 255;
        }
        ++v39;
        --*(_DWORD *)igi2_frame.zFilename;
      }
      while ( *(_DWORD *)igi2_frame.zFilename );
    }
    v44 = 0;
    while ( 1 )
    {
      v45 = Level_atLevelQTaskID[v44];
      if ( v45 )
      {
        if ( v45->pxObject == ptQTask )
          break;
      }
      if ( ++v44 >= 4096 )
      {
        v44 = -1;
        break;
      }
    }
    sprintf(igi2_frame.pptResource, "water_%d.res", v44);
    Water_CreateResourceFile(igi2_frame.pptResource, igi2_frame.v50 + 6 * igi2_frame.v48, igi2_frame.pzFileList, 255);
  }
  ptParent = ptQTask[2].ptParent;
  *(float *)&ptQTask[5].ptPrev = *(float *)&ptQTask[5].ptParent * 0.000244140625;
  *(float *)&ptQTask[5].ptNext = *(float *)&ptQTask[5].tQTaskRefList.ptHead * 8192.0;
  *(float *)&ptQTask[4].eQTaskType = 1.0 / (*(float *)&ptQTask[5].tQTaskRefList.ptMiddle * 4096.0);
  igi2_frame.ptDynCubeObj = *(float *)&ptQTask[5].tQTaskRefList.ptHead * 4096.0;
  World_MoveDynCubeObjRadius(
    (struct World_s *)ptParent,
    (struct DynCubeObj_s *)ptQTask,
    (struct real64x3_t *)&ptQTask[3],
    igi2_frame.ptDynCubeObj);
  Level_CompileLevelExpression((struct LevelExpression_s *)&ptQTask[50].tQTaskRefList.ptTail, ptQTask);
}

// source: h/2/water.c:945  [anchor-mhash]
void __cdecl Water_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QObjectVector_s *v2; // esi
  struct MemPoolSegment_s *v3; // eax
  int v4; // ecx
  struct MemPoolFreeItem_s *ptHead; // edx
  struct MemPoolFreeItem_s *pxData; // eax
  unsigned int nBlockSize; // edx
  struct MemPoolFreeItem_s *v8; // eax
  struct MemPoolFreeItem_s *v9; // eax
  struct MemPoolFreeItem_s *v10; // eax
  struct MemPoolFreeItem_s *v11; // eax
  struct QObjectVector_s *v12; // esi
  struct MemPoolSegment_s *v13; // edi
  int v14; // eax
  int v15; // eax
  struct MemPoolFreeItem_s *v16; // ecx
  struct MemPoolFreeItem_s *v17; // ecx
  struct MemPoolFreeItem_s *v18; // ecx
  struct MemPoolFreeItem_s *v19; // ecx
  struct MemPoolFreeItem_s *v20; // ecx
  struct MemPoolFreeItem_s *v21; // ecx
  struct MemPoolFreeItem_s *v22; // ecx
  struct MemPoolFreeItem_s *v23; // ecx
  struct MemPoolFreeItem_s *v24; // ecx
  struct MemPoolFreeItem_s *v25; // ecx
  struct QTaskList_s *v26; // eax
  float ptDynCubeObj; // [esp+0h] [ebp-18h]
  struct MemPoolSegment_s *v28; // [esp+14h] [ebp-4h]
  int v29; // [esp+14h] [ebp-4h]

  memset(&ptQTask[1], 0, 0x48u);
  ptQTask[2].ptParent = (struct QTask_s *)World_ptActiveWorld;
  ptQTask[2].tQTaskRefList.ptTail = (struct QReference_s *)14;
  ptQTask[5].ptPrev = nullptr;
  *(_DWORD *)&ptQTask[4].eQTaskType = 0;
  ptQTask[5].ptNext = nullptr;
  ptQTask[36].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[50].ptPrev = nullptr;
  ptQTask[67].tQTaskChildren.ptTail = nullptr;
  ptQTask[67].tQTaskRefList.ptHead = nullptr;
  ptQTask[5].tQTaskChildren.ptHead = (struct QTask_s *)1045220557;
  ptQTask[5].tQTaskRefList.ptHead = (struct QReference_s *)1092616192;
  ptQTask[5].tQTaskChildren.ptTail = nullptr;
  ptQTask[5].tQTaskRefList.ptTail = (struct QReference_s *)1056964608;
  ptQTask[5].ptParent = (struct QTask_s *)1000593162;
  ptQTask[4].tQTaskRefList.ptHead = (struct QReference_s *)1036831949;
  ptQTask[4].tQTaskRefList.ptMiddle = (struct QReference_s *)1036831949;
  ptQTask[4].tQTaskChildren.ptHead = (struct QTask_s *)1036831949;
  ptQTask[4].tQTaskChildren.ptMiddle = (struct QTask_s *)1036831949;
  ptQTask[4].tQTaskRefList.ptTail = nullptr;
  ptQTask[4].tQTaskChildren.ptTail = nullptr;
  ptQTask[4].ptParent = (struct QTask_s *)1080033280;
  ptQTask[36].ptPrev = (struct QTask_s *)128;
  ptQTask[50].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[3].ptNext = nullptr;
  ptQTask[3].ptPrev = nullptr;
  ptQTask[3].tQTaskChildren.ptHead = nullptr;
  ptQTask[3].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[3].tQTaskChildren.ptTail = nullptr;
  ptQTask[3].tQTaskRefList.ptHead = nullptr;
  ptQTask[34].tQTaskChildren.ptHead = nullptr;
  ptQTask[34].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[34].tQTaskChildren.ptTail = nullptr;
  ptQTask[34].tQTaskRefList.ptHead = nullptr;
  ptQTask[34].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[34].tQTaskRefList.ptTail = nullptr;
  *(_DWORD *)&ptQTask[34].eQTaskType = 0;
  ptQTask[35].ptNext = nullptr;
  ptQTask[35].ptPrev = nullptr;
  ptQTask[35].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[35].tQTaskChildren.ptTail = nullptr;
  ptQTask[35].tQTaskRefList.ptHead = nullptr;
  ptQTask[35].tQTaskRefList.ptTail = nullptr;
  BYTE2(ptQTask[52].tQTaskRefList.ptTail) = 0;
  HIBYTE(ptQTask[52].tQTaskRefList.ptTail) = 0;
  LOBYTE(ptQTask[52].ptParent) = 0;
  BYTE1(ptQTask[52].ptParent) = 0;
  ptQTask[5].tQTaskChildren.ptMiddle = (struct QTask_s *)1065353216;
  ptQTask[5].tQTaskRefList.ptMiddle = (struct QReference_s *)1065353216;
  ptQTask[35].ptParent = (struct QTask_s *)1065353216;
  ptQTask[34].ptParent = (struct QTask_s *)1065353216;
  ptQTask[35].tQTaskChildren.ptHead = (struct QTask_s *)1065353216;
  ptQTask[35].tQTaskRefList.ptMiddle = (struct QReference_s *)1065353216;
  *(_DWORD *)&ptQTask[35].eQTaskType = 1;
  LOBYTE(ptQTask[52].tQTaskRefList.ptTail) = 1;
  ptQTask[50].tQTaskChildren.ptHead = (struct QTask_s *)1;
  BYTE1(ptQTask[52].tQTaskRefList.ptTail) = 1;
  ptQTask[50].tQTaskRefList.ptTail = nullptr;
  ptQTask[50].ptParent = nullptr;
  *(_DWORD *)&ptQTask[50].eQTaskType = 0;
  ptQTask[52].tQTaskRefList.ptMiddle = nullptr;
  *(_DWORD *)&ptQTask[49].eQTaskType = 0;
  ptQTask[18].tQTaskRefList.ptTail = nullptr;
  LOBYTE(ptQTask[12].tQTaskChildren.ptMiddle) = 0;
  LOBYTE(ptQTask[5].eQTaskType) = 0;
  ptQTask[32].tQTaskRefList.ptTail = nullptr;
  LOBYTE(ptQTask[26].tQTaskChildren.ptMiddle) = 0;
  LOBYTE(ptQTask[19].eQTaskType) = 0;
  ptDynCubeObj = *(float *)&ptQTask[5].tQTaskRefList.ptHead * 4096.0;
  World_RegisterDynCubeObjFirstTimeRadius(
    (struct World_s *)ptQTask[2].ptParent,
    (struct DynCubeObj_s *)ptQTask,
    (struct real64x3_t *)&ptQTask[3],
    ptDynCubeObj,
    WORLD_DYNCUBETREE_CATEGORY_STATIONARY);
  v2 = (struct QObjectVector_s *)Mem_AllocFn(52, 4);
  v2->nElementSize = 76;
  v2->tMemPool.nBlockSize = 76;
  v2->isStrictOrder = true;
  v2->nSize = 0;
  v2->nAllocated = 0;
  v2->nReallocSize = 0;
  v2->papxElement = nullptr;
  v2->tMemPool.nBlocks = 0;
  v2->tMemPool.nAllocatedBlocks = 0;
  v2->tMemPool.nAlignment = 4;
  v2->tMemPool.nReAllocBlocks = 0;
  v2->tMemPool.tMemPoolFreeList.ptHead = nullptr;
  v2->tMemPool.tMemPoolSegmentList.ptHead = nullptr;
  v3 = (struct MemPoolSegment_s *)Mem_AllocFn(12, 4);
  v4 = 5 * v2->tMemPool.nBlockSize;
  v28 = v3;
  v3->nByteSize = v4;
  v3->pxData = Mem_AllocFn(v4, v2->tMemPool.nAlignment);
  v28->ptNext = v2->tMemPool.tMemPoolSegmentList.ptHead;
  ptHead = v2->tMemPool.tMemPoolFreeList.ptHead;
  v2->tMemPool.nBlocks += 5;
  v2->tMemPool.tMemPoolSegmentList.ptHead = v28;
  pxData = (struct MemPoolFreeItem_s *)v28->pxData;
  pxData->ptNext = ptHead;
  nBlockSize = v2->tMemPool.nBlockSize;
  v2->tMemPool.tMemPoolFreeList.ptHead = pxData;
  v8 = (struct MemPoolFreeItem_s *)((char *)v28->pxData + nBlockSize);
  v8->ptNext = v2->tMemPool.tMemPoolFreeList.ptHead;
  v2->tMemPool.tMemPoolFreeList.ptHead = v8;
  v9 = (struct MemPoolFreeItem_s *)((char *)v28->pxData + 2 * v2->tMemPool.nBlockSize);
  v9->ptNext = v2->tMemPool.tMemPoolFreeList.ptHead;
  v2->tMemPool.tMemPoolFreeList.ptHead = v9;
  v10 = (struct MemPoolFreeItem_s *)((char *)v28->pxData + 3 * v2->tMemPool.nBlockSize);
  v10->ptNext = v2->tMemPool.tMemPoolFreeList.ptHead;
  v2->tMemPool.tMemPoolFreeList.ptHead = v10;
  v11 = (struct MemPoolFreeItem_s *)((char *)v28->pxData + 4 * v2->tMemPool.nBlockSize);
  v11->ptNext = v2->tMemPool.tMemPoolFreeList.ptHead;
  v2->tMemPool.tMemPoolFreeList.ptHead = v11;
  QObjectVector_Realloc(v2, 5u);
  ptQTask[36].tQTaskChildren.ptTail = (struct QTask_s *)v2;
  v12 = (struct QObjectVector_s *)Mem_AllocFn(52, 4);
  v12->nElementSize = 68;
  v12->tMemPool.nBlockSize = 68;
  v12->isStrictOrder = false;
  v12->nSize = 0;
  v12->nAllocated = 0;
  v12->nReallocSize = 20;
  v12->papxElement = nullptr;
  v12->tMemPool.nBlocks = 0;
  v12->tMemPool.nAllocatedBlocks = 0;
  v12->tMemPool.nAlignment = 4;
  v12->tMemPool.nReAllocBlocks = 20;
  v12->tMemPool.tMemPoolFreeList.ptHead = nullptr;
  v12->tMemPool.tMemPoolSegmentList.ptHead = nullptr;
  v13 = (struct MemPoolSegment_s *)Mem_AllocFn(12, 4);
  v14 = 30 * v12->tMemPool.nBlockSize;
  v13->nByteSize = v14;
  v13->pxData = Mem_AllocFn(v14, v12->tMemPool.nAlignment);
  v13->ptNext = v12->tMemPool.tMemPoolSegmentList.ptHead;
  v12->tMemPool.nBlocks += 30;
  v12->tMemPool.tMemPoolSegmentList.ptHead = v13;
  v15 = 2;
  v29 = 3;
  do
  {
    v16 = (struct MemPoolFreeItem_s *)((char *)v13->pxData + v12->tMemPool.nBlockSize * (v15 - 2));
    v16->ptNext = v12->tMemPool.tMemPoolFreeList.ptHead;
    v12->tMemPool.tMemPoolFreeList.ptHead = v16;
    v17 = (struct MemPoolFreeItem_s *)((char *)v13->pxData + v12->tMemPool.nBlockSize * (v15 - 1));
    v17->ptNext = v12->tMemPool.tMemPoolFreeList.ptHead;
    v12->tMemPool.tMemPoolFreeList.ptHead = v17;
    v18 = (struct MemPoolFreeItem_s *)((char *)v13->pxData + v15 * v12->tMemPool.nBlockSize);
    v18->ptNext = v12->tMemPool.tMemPoolFreeList.ptHead;
    v12->tMemPool.tMemPoolFreeList.ptHead = v18;
    v19 = (struct MemPoolFreeItem_s *)((char *)v13->pxData + v12->tMemPool.nBlockSize * (v15 + 1));
    v19->ptNext = v12->tMemPool.tMemPoolFreeList.ptHead;
    v12->tMemPool.tMemPoolFreeList.ptHead = v19;
    v20 = (struct MemPoolFreeItem_s *)((char *)v13->pxData + v12->tMemPool.nBlockSize * (v15 + 2));
    v20->ptNext = v12->tMemPool.tMemPoolFreeList.ptHead;
    v12->tMemPool.tMemPoolFreeList.ptHead = v20;
    v21 = (struct MemPoolFreeItem_s *)((char *)v13->pxData + v12->tMemPool.nBlockSize * (v15 + 3));
    v21->ptNext = v12->tMemPool.tMemPoolFreeList.ptHead;
    v12->tMemPool.tMemPoolFreeList.ptHead = v21;
    v22 = (struct MemPoolFreeItem_s *)((char *)v13->pxData + v12->tMemPool.nBlockSize * (v15 + 4));
    v22->ptNext = v12->tMemPool.tMemPoolFreeList.ptHead;
    v12->tMemPool.tMemPoolFreeList.ptHead = v22;
    v23 = (struct MemPoolFreeItem_s *)((char *)v13->pxData + v12->tMemPool.nBlockSize * (v15 + 5));
    v23->ptNext = v12->tMemPool.tMemPoolFreeList.ptHead;
    v12->tMemPool.tMemPoolFreeList.ptHead = v23;
    v24 = (struct MemPoolFreeItem_s *)((char *)v13->pxData + v12->tMemPool.nBlockSize * (v15 + 6));
    v24->ptNext = v12->tMemPool.tMemPoolFreeList.ptHead;
    v12->tMemPool.tMemPoolFreeList.ptHead = v24;
    v25 = (struct MemPoolFreeItem_s *)((char *)v13->pxData + v12->tMemPool.nBlockSize * (v15 + 7));
    v25->ptNext = v12->tMemPool.tMemPoolFreeList.ptHead;
    v12->tMemPool.tMemPoolFreeList.ptHead = v25;
    v15 += 10;
    --v29;
  }
  while ( v29 );
  QObjectVector_Realloc(v12, 0x1Eu);
  v26 = Water_ptQTaskList;
  ptQTask[36].tQTaskRefList.ptHead = (struct QReference_s *)v12;
  QTaskList_Register(v26, (struct QTaskList_s *)ptQTask);
}

// source: h/2/water.c:1033  [size]
void __cdecl Water_DeleteHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { char zFilename[4]; };
    struct { char igi2_o1[4]; char zResourceFilename[256]; };
    struct { char igi2_o2[260]; char zResourceShortFilename[256]; };
    char igi2_extent[516];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  _DWORD *p_ptParent; // esi
  int v2; // ebp
  int v3; // eax
  int v4; // edi
  struct QTask_s *ptNext; // eax
  struct QTask_s *v6; // esi
  int v7; // eax
  struct QTask_s *v8; // eax
  int v9; // ecx
  struct QReference_s *v10; // eax
  int v11; // eax

  Level_DeinitLevelExpression((struct LevelExpression_s *)&ptQTask[50].tQTaskRefList.ptTail);
  QTaskList_Remove(Water_ptQTaskList, ptQTask);
  QObjectVector_Delete((struct QObjectVector_s *)ptQTask[36].tQTaskChildren.ptTail);
  QObjectVector_Delete((struct QObjectVector_s *)ptQTask[36].tQTaskRefList.ptHead);
  World_RemoveDynCubeObj((struct World_s *)ptQTask[2].ptParent, (struct DynCubeObj_s *)ptQTask);
  p_ptParent = &ptQTask[18].ptParent;
  v2 = 2;
  do
  {
    if ( *(p_ptParent - 1) )
    {
      if ( AppContext_tAppContext.isMainMenu == false )
        RenderMode_atRenderMode[*p_ptParent].apfRenderModeMethod[Texture_eDeAllocTextureMethod](p_ptParent);
      memset(p_ptParent, 0, 0x2Cu);
      *(p_ptParent - 1) = 0;
    }
    p_ptParent += 140;
    --v2;
  }
  while ( v2 );
  v3 = *(_DWORD *)&ptQTask[35].eQTaskType;
  v4 = 0;
  if ( v3 )
  {
    if ( v3 != 1 )
    {
LABEL_9:
      LDebug_Error("Environmental map render: unknown type of environmental map");
      abort();
    }
    ptNext = ptQTask[34].ptNext;
    if ( !ptNext )
      goto LABEL_14;
    goto LABEL_13;
  }
  ptNext = ptQTask[34].ptNext;
  if ( ptNext )
  {
LABEL_13:
    ((void (__stdcall *)(struct QTask_s *))ptNext->ptNext->tQTaskChildren.ptHead)(ptQTask[34].ptNext);
    ptQTask[34].ptNext = nullptr;
    ptQTask[36].tQTaskChildren.ptMiddle = nullptr;
  }
LABEL_14:
  v6 = ptQTask + 53;
  do
  {
    if ( !v6->ptNext )
      goto LABEL_22;
    v7 = *(_DWORD *)&v6[1].eQTaskType;
    if ( !v7 )
    {
      v8 = v6->ptNext;
      if ( !v6->ptNext )
        goto LABEL_22;
LABEL_21:
      ((void (__stdcall *)(struct QTask_s *))v8->ptNext->tQTaskChildren.ptHead)(v6->ptNext);
      v6->ptNext = nullptr;
      v6[2].tQTaskChildren.ptMiddle = nullptr;
      goto LABEL_22;
    }
    if ( v7 != 1 )
      goto LABEL_9;
    v8 = v6->ptNext;
    if ( v6->ptNext )
      goto LABEL_21;
LABEL_22:
    ++v4;
    v6 = (struct QTask_s *)((char *)v6 + 96);
  }
  while ( v4 < 5 );
  v9 = 0;
  while ( 1 )
  {
    v10 = Level_atLevelQTaskID[v9];
    if ( v10 )
    {
      if ( v10->pxObject == ptQTask )
        break;
    }
    if ( ++v9 >= 4096 )
    {
      v9 = -1;
      break;
    }
  }
  sprintf(igi2_frame.zResourceShortFilename, "water_%d.res", v9);
  sprintf(igi2_frame.zResourceFilename, "%s/%s", "MISSION:envmaps", igi2_frame.zResourceShortFilename);
  if ( Resource_IsLoadedInternal(igi2_frame.zResourceFilename, nullptr) )
  {
    if ( Resource_IsLoadedInternal(igi2_frame.zResourceFilename, (struct Resource_s **)igi2_frame.zFilename) )
    {
      v11 = *(_DWORD *)(*(_DWORD *)igi2_frame.zFilename + 36);
      if ( v11 != 3 && v11 != 1 )
        Resource_Remove(*(struct Resource_s **)igi2_frame.zFilename);
    }
  }
}

// source: h/2/water.c:1098  [anchor-caller]
void __cdecl Water_RunHandler(struct QTask_s *ptQTask)
{
  int i; // ebx
  int j; // esi
  int v3; // ecx
  double v4; // st7
  int v5; // eax
  double v6; // st7
  double v7; // st6
  double v8; // st5
  double v9; // st4
  double v10; // st6
  struct QExpression_s *v11; // ebx
  float vTime; // [esp+Ch] [ebp-Ch]
  float vTMax; // [esp+10h] [ebp-8h]
  float vTMaxb; // [esp+10h] [ebp-8h]
  double vTMaxa; // [esp+10h] [ebp-8h]

  for ( i = 0; i < (int)(*(_DWORD *)&ptQTask[36].tQTaskChildren.ptTail->eQTaskType); ++i )
    Water_UpdateWave(
      (struct Water_t *)ptQTask,
      *((struct Wave_t **)&ptQTask[36].tQTaskChildren.ptTail[1].tQTaskChildren.ptHead->ptNext + i));
  for ( j = 0; j < (int)ptQTask[36].tQTaskRefList.ptHead[3].ptNext; ++j )
  {
    v3 = *((_DWORD *)&ptQTask[36].tQTaskRefList.ptHead[4].ptNext->ptNext + j);
    v4 = (double)((unsigned int)ptQTask[49].ptParent - *(_DWORD *)(v3 + 60)) * 0.06666666666666667;
    vTime = v4;
    if ( v4 > 0.0 )
    {
      v5 = *(_DWORD *)(v3 + 40);
      *(float *)(v3 + 20) = vTime * *(float *)(v3 + 12) + *(float *)(v3 + 28);
      v6 = vTime * *(float *)(v3 + 16) - vTime * vTime * 4.90500020980835 + *(float *)(v3 + 32);
      *(float *)(v3 + 24) = v6;
      if ( v5 )
      {
        vTMax = *(float *)(v3 + 16) * 0.10193679481744766;
        v7 = vTime - vTMax;
        if ( v7 <= 0.0 )
          v8 = 0.0;
        else
          v8 = v7;
        v9 = 1.0 / vTMax;
        if ( 1.0 - v9 * v8 * 1.5 <= 0.0 )
        {
          v10 = 0.0;
        }
        else
        {
          if ( v7 <= 0.0 )
            v7 = 0.0;
          vTMaxb = v9;
          v10 = 1.0 - v7 * vTMaxb * 1.5;
        }
        *(float *)(v3 + 56) = v10;
      }
      if ( v6 < 0.0 )
      {
        QObjectVector_RemoveElement(
          (struct QObjectVector_s *)ptQTask[36].tQTaskRefList.ptHead,
          *(_DWORD *)((char *)ptQTask[36].tQTaskRefList.ptHead[2].pxObject + v3 - 4));
        --j;
      }
    }
  }
  if ( ptQTask[50].tQTaskRefList.ptTail && ptQTask[50].ptParent->ptNext && *(_DWORD *)&ptQTask[50].eQTaskType )
  {
    vTMaxa = 0.0;
    if ( !ptQTask[50].ptParent
      || (Level_ValidateLevelExpression((struct LevelExpression_s *)&ptQTask[50].tQTaskRefList.ptTail),
          !ptQTask[50].ptParent) )
    {
      Level_CompileLevelExpression((struct LevelExpression_s *)&ptQTask[50].tQTaskRefList.ptTail, ptQTask);
    }
    v11 = *(struct QExpression_s **)&ptQTask[50].eQTaskType;
    if ( v11 )
      vTMaxa = Expression_EvalFloat(v11);
    *(_DWORD *)&ptQTask[49].eQTaskType = (__int64)vTMaxa;
  }
  ++*(int *)&ptQTask[49].ptParent;
}

// source: h/2/water.c:1243  [anchor-hash]
struct QTask_s *__cdecl Water_SetVertexFunctionParameters(struct QTask_s *ptQTask)
{
  unsigned __int16 v1; // dx
  int v2; // esi
  double v3; // st7
  struct QTask_s *result; // eax

  v1 = WaterLayer_eQTaskType;
  v2 = 0;
  Water_nActiveLayers = 0;
  Water_vTime = (double)Timer_nTicks * 0.016666666666666666;
  v3 = 0.0;
  result = QTask_GetFirstChildOfType(ptQTask, WaterLayer_eQTaskType);
  if ( result )
  {
    do
    {
      if ( v2 >= 4 )
        break;
      Water_aptActiveWaterLayer[v2] = (struct WaterLayer_t *)result;
      v3 = v3 + *(float *)&result[1].tQTaskChildren.ptHead;
      result = QTask_GetNextSiblingOfType(result, v1);
      ++v2;
    }
    while ( result );
    Water_nActiveLayers = v2;
  }
  Water_vActiveSampleScale = v3 / (double)Water_nActiveLayers * 40.959999084472656;
  return result;
}

// source: h/2/water.c:1276  [anchor-caller]
void __cdecl Water_EnterHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { float tPos_8; };
    struct { char igi2_o1[12]; float Real32x3_Rotate_tTemp_8; };
    struct { char igi2_o2[16]; struct WaterContext_t tContext; };
    char igi2_extent[96];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *ptMiddle; // ecx
  double v3; // st7
  float v4; // edx
  struct QReference_s *ptTail; // eax
  struct QTask_s *v6; // eax
  int v7; // eax
  char *v8; // eax
  int v9; // edi
  struct Envmap_t *v10; // eax
  int v11; // ecx
  struct QTask_s **p_ptParent; // edx
  double v13; // st7
  struct QReference_s *ptHead; // eax
  int ptNext; // ecx
  double v16; // st6
  double v17; // st5
  struct SortRenderList_t *v18; // ebx
  int v19; // ebp
  int v20; // ecx
  double v21; // st7
  double v22; // st6
  int v23; // eax
  double v24; // st5
  double v25; // st4
  unsigned __int8 *v26; // edx
  double v27; // st7

  ptMiddle = ptQTask[5].tQTaskChildren.ptMiddle;
  v3 = *(float *)&ptQTask[5].tQTaskRefList.ptHead * 4096.0;
  v4 = *(float *)&ptQTask[4].eQTaskType;
  LODWORD(igi2_frame.tContext.vDetail) = ptQTask[5].tQTaskChildren.ptHead;
  ptTail = ptQTask[5].tQTaskRefList.ptTail;
  igi2_frame.tContext.vRadius = v3;
  LODWORD(igi2_frame.tContext.vEnvScale) = ptTail;
  LODWORD(igi2_frame.tContext.vAlpha) = ptMiddle;
  igi2_frame.tContext.tView.vZ = TransContext_tActiveTransContext.tMatrix.tZ.vZ;
  v6 = ptQTask[5].tQTaskChildren.ptTail;
  igi2_frame.tContext.tView.vX = TransContext_tActiveTransContext.tMatrix.tX.vZ;
  LODWORD(igi2_frame.tContext.vMaxReflectionAngle) = v6;
  v7 = *(_DWORD *)&ptQTask[49].eQTaskType;
  igi2_frame.tContext.vScaledUVScale = v4;
  igi2_frame.tContext.ptDiffuseColor = (struct real32x3_t *)&ptQTask[4].tQTaskChildren;
  igi2_frame.tContext.tView.vY = TransContext_tActiveTransContext.tMatrix.tY.vZ;
  v8 = (char *)ptQTask + 96 * v7;
  igi2_frame.tContext.pfWaterFunction = Water_VertexFunction;
  igi2_frame.tContext.ptSpecularColor = (struct real32x3_t *)&ptQTask[4].tQTaskRefList;
  v9 = 0;
  if ( *((_DWORD *)v8 + 553) )
  {
    v10 = (struct Envmap_t *)(v8 + 2120);
LABEL_6:
    igi2_frame.tContext.ptEnvmap = v10;
    goto LABEL_7;
  }
  if ( !ptQTask[36].tQTaskChildren.ptMiddle )
  {
    v10 = (struct Envmap_t *)&ptQTask[53];
    goto LABEL_6;
  }
  igi2_frame.tContext.ptEnvmap = (struct Envmap_t *)&ptQTask[34];
LABEL_7:
  v11 = 0;
  p_ptParent = &ptQTask[18].ptParent;
  igi2_frame.tContext.vAbsorptionLength = *(float *)&ptQTask[4].ptParent * 4096.0;
  igi2_frame.tContext.tDisplacement.vX = *(double *)&ptQTask[3].ptNext - TransContext_tActiveTransContext.tPos.vX;
  igi2_frame.tContext.tDisplacement.vY = *(double *)&ptQTask[3].tQTaskChildren.ptHead - TransContext_tActiveTransContext.tPos.vY;
  igi2_frame.tContext.tDisplacement.vZ = *(double *)&ptQTask[3].tQTaskChildren.ptTail - TransContext_tActiveTransContext.tPos.vZ;
  do
  {
    igi2_frame.tContext.aptTexInfo[v11++] = *(p_ptParent - 1) != nullptr ? (struct TexInfo_s *)p_ptParent : nullptr;
    p_ptParent += 140;
  }
  while ( v11 < 2 );
  Water_SetVertexFunctionParameters(ptQTask);
  Water_ptActiveWater = (struct Water_t *)ptQTask;
  RenderMode_tActiveRenderMode.apfRenderModeMethod[WaterRender_eDrawWaterMethod](&igi2_frame.tContext);
  v13 = *(double *)&ptQTask[3].ptNext - TransContext_tActiveTransContext.tPos.vX;
  ptHead = ptQTask[36].tQTaskRefList.ptHead;
  ptNext = (int)ptHead[3].ptNext;
  v16 = *(double *)&ptQTask[3].tQTaskChildren.ptHead - TransContext_tActiveTransContext.tPos.vY;
  v17 = *(double *)&ptQTask[3].tQTaskChildren.ptTail - TransContext_tActiveTransContext.tPos.vZ;
  Water_ptActiveWater = nullptr;
  igi2_frame.Real32x3_Rotate_tTemp_8 = v16 * TransContext_tActiveTransContext.tMatrix.tZ.vY
                          + v13 * TransContext_tActiveTransContext.tMatrix.tZ.vX
                          + v17 * TransContext_tActiveTransContext.tMatrix.tZ.vZ;
  if ( ptNext > 0 )
  {
    v18 = SortRender_ptActiveList;
    v19 = SortRender_nBufferPos;
    do
    {
      v20 = *((_DWORD *)&ptHead[4].ptNext->ptNext + v9);
      v21 = *(float *)v20 - TransContext_tActiveTransContext.tMatrix.tZ.vX * *(float *)(v20 + 44);
      igi2_frame.tPos_8 = *(float *)(v20 + 8);
      v22 = *(float *)(v20 + 4) - TransContext_tActiveTransContext.tMatrix.tZ.vY * *(float *)(v20 + 44);
      v23 = (int)&v18->atItem[v18->nNumItems];
      v24 = igi2_frame.tPos_8 * TransContext_tActiveTransContext.tMatrix.tZ.vZ
          + v22 * TransContext_tActiveTransContext.tMatrix.tZ.vY;
      v25 = v21 * TransContext_tActiveTransContext.tMatrix.tZ.vX;
      ++v18->nNumItems;
      *(_DWORD *)v23 = Billboard_DrawSorted;
      v26 = &SortRender_anSortBuffer[v19];
      *(_DWORD *)(v23 + 4) = &SortRender_anSortBuffer[v19];
      v19 += 44;
      ++v9;
      *(float *)(v23 + 8) = v24 + v25 + igi2_frame.Real32x3_Rotate_tTemp_8;
      *(float *)v26 = v21 - TransContext_tActiveTransContext.tPos.vX;
      *((float *)v26 + 1) = v22 - TransContext_tActiveTransContext.tPos.vY;
      *((float *)v26 + 2) = igi2_frame.tPos_8 - TransContext_tActiveTransContext.tPos.vZ;
      *(float *)v26 = Direct3D_vScale * *(float *)v26;
      *((float *)v26 + 1) = Direct3D_vScale * *((float *)v26 + 1);
      *((float *)v26 + 2) = Direct3D_vScale * *((float *)v26 + 2);
      *((float *)v26 + 3) = *(float *)(v20 + 20) * 4096.0;
      v27 = *(float *)(v20 + 24);
      *((_DWORD *)v26 + 6) = 1065353216;
      *((_DWORD *)v26 + 7) = 1065353216;
      *((_DWORD *)v26 + 8) = 1065353216;
      *((float *)v26 + 4) = v27 * 4096.0;
      *((float *)v26 + 9) = *(float *)(v20 + 52) * *(float *)(v20 + 48);
      *((float *)v26 + 10) = *(float *)(v20 + 56) * *(float *)(v20 + 48);
      *((_DWORD *)v26 + 5) = *(_DWORD *)(v20 + 36);
      ptHead = ptQTask[36].tQTaskRefList.ptHead;
    }
    while ( v9 < (int)ptHead[3].ptNext );
    SortRender_nBufferPos = v19;
  }
}

// source: h/2/water.c:1416  [anchor-mhash]
void __cdecl Water_TraceLinesHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { float vRadius; };
    struct { char igi2_o1[4]; int iLine; };
    struct { char igi2_o2[8]; struct real64x3_t *ptEnd; };
    struct { char igi2_o3[24]; struct real64x3_t tHitPos; };
    char igi2_extent[48];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  double *v2; // ecx
  _DWORD *v3; // edi
  double *p_vX; // esi
  double *v5; // ebx
  int v6; // edx
  double v7; // st7
  double v8; // st6
  long double v9; // st4
  struct World_s *v10; // ecx
  bool v11; // cc

  v2 = (double *)ptQTask;
  v3 = pxContext;
  igi2_frame.vRadius = *(float *)&ptQTask[5].tQTaskRefList.ptHead * 4096.0;
  p_vX = *((double **)pxContext + 1);
  v5 = *(double **)pxContext;
  v6 = *((_DWORD *)pxContext + 9);
  ptQTask[67].tQTaskRefList.ptHead = (struct QReference_s *)ptQTask[67].tQTaskChildren.ptTail;
  ptQTask[67].tQTaskChildren.ptTail = (struct QTask_s *)(Mouse_tMouse.bButton & 1);
  igi2_frame.ptEnd = (struct real64x3_t *)p_vX;
  igi2_frame.iLine = 0;
  if ( *((int *)pxContext + 2) > 0 )
  {
    do
    {
      if ( (v5[2] >= v2[17] || p_vX[2] >= v2[17]) && (v5[2] <= v2[17] || p_vX[2] <= v2[17]) && v5[2] != p_vX[2] )
      {
        v7 = p_vX[2] - v5[2];
        v8 = (v2[17] - v5[2]) / v7;
        igi2_frame.tHitPos.vX = (*p_vX - *v5) * v8 + *v5;
        igi2_frame.tHitPos.vY = (p_vX[1] - v5[1]) * v8 + v5[1];
        igi2_frame.tHitPos.vZ = v8 * v7 + v5[2];
        if ( igi2_frame.vRadius + v2[15] >= igi2_frame.tHitPos.vX
          && v2[15] - igi2_frame.vRadius <= igi2_frame.tHitPos.vX
          && igi2_frame.vRadius + v2[16] >= igi2_frame.tHitPos.vY
          && v2[16] - igi2_frame.vRadius <= igi2_frame.tHitPos.vY )
        {
          v9 = sqrt(
                 (igi2_frame.tHitPos.vZ - v5[2]) * (igi2_frame.tHitPos.vZ - v5[2])
               + (igi2_frame.tHitPos.vY - v5[1]) * (igi2_frame.tHitPos.vY - v5[1])
               + (igi2_frame.tHitPos.vX - *v5) * (igi2_frame.tHitPos.vX - *v5));
          if ( !*(_DWORD *)(v6 + 92) || v9 < *(double *)(v6 + 96) )
          {
            *(_DWORD *)v6 = v2;
            *(long double *)(v6 + 96) = v9;
            qmemcpy((void *)(v6 + 8), &igi2_frame.tHitPos, 0x18u);
            v10 = World_ptActiveWorld;
            p_vX = &igi2_frame.ptEnd->vX;
            v3 = pxContext;
            *(_DWORD *)(v6 + 88) = 0;
            *(_DWORD *)(v6 + 92) = 1;
            *(_DWORD *)(v6 + 80) = v10->aptQMaterial[2];
            *(_DWORD *)(v6 + 84) = 0;
            *(_DWORD *)(v6 + 56) = 0;
            *(_DWORD *)(v6 + 60) = 0;
            *(_DWORD *)(v6 + 64) = 1065353216;
            v2 = (double *)ptQTask;
          }
        }
      }
      p_vX += 3;
      v5 += 3;
      v6 += 120;
      v11 = ++igi2_frame.iLine < (int)(v3[2]);
      igi2_frame.ptEnd = (struct real64x3_t *)p_vX;
    }
    while ( v11 );
  }
}

// source: h/2/water.c:1509  [size]
void __cdecl Water_PhysicsObjHitHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *((_DWORD *)pxContext + 2) = 1;
}

// source: h/2/water.c:1527  [size]
void __cdecl WaterLayer_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = WaterLayer_ptParameterList;
}

// source: h/2/water.c:1546  [anchor-mhash]
void __cdecl WaterLayer_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  long double v2; // st7

  v2 = *(float *)&ptQTask[1].tQTaskRefList.ptHead * 0.01745329238474369;
  *(float *)&ptQTask[1].tQTaskRefList.ptMiddle = sin(v2);
  *(float *)&ptQTask[1].tQTaskRefList.ptTail = cos(v2);
  *(float *)&ptQTask[1].ptNext = 6.2831854820251465 / (*(float *)&ptQTask[1].tQTaskChildren.ptHead * 4096.0);
  *(float *)&ptQTask[1].ptPrev = *(float *)&ptQTask[1].tQTaskChildren.ptMiddle * 4096.0;
}

// source: h/2/water.c:1568  [size]
void __cdecl WaterLayer_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ptQTask[1].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[1].tQTaskRefList.ptTail = nullptr;
  ptQTask[1].tQTaskChildren.ptHead = (struct QTask_s *)1120403456;
  ptQTask[1].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[1].tQTaskChildren.ptTail = (struct QTask_s *)1065353216;
  ptQTask[1].tQTaskRefList.ptHead = nullptr;
}

// source: h/2/water.c:1591  [size]
void __cdecl WaterLayer_DeleteHandler(struct QTask_s *ptQTask)
{
  ;
}

// source: h/2/water.c:1610  [anchor-callee]
enum bool __cdecl Water_IsUnderWater(float *pvDepth, struct real64x3_t *ptPos, int *iWaterIndex)
{
  #pragma pack(push, 1)
  union
  {
    struct { float vInX; };
    struct { char igi2_o1[4]; float vInY; };
    struct { char igi2_o2[8]; float vInZ; };
    struct { char igi2_o3[28]; float vRadius; };
    struct { char igi2_o4[32]; struct QTask_s **v12; };
    struct { char igi2_o5[36]; float vDepth; };
    struct { char igi2_o6[40]; int n; };
    struct { char igi2_o7[44]; struct real32x3_t tNormal; };
    char igi2_extent[56];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int nTask; // ecx
  int v4; // ebx
  struct QTask_s **ptQTask; // eax
  struct Water_t *v6; // esi

  nTask = Water_ptQTaskList->nTask;
  v4 = 0;
  igi2_frame.n = Water_ptQTaskList->nTask;
  if ( igi2_frame.n <= 0 )
  {
LABEL_11:
    *iWaterIndex = -1;
    return false;
  }
  ptQTask = Water_ptQTaskList->ptQTask;
  igi2_frame.v12 = Water_ptQTaskList->ptQTask;
  while ( 1 )
  {
    v6 = (struct Water_t *)*ptQTask;
    igi2_frame.vRadius = *(float *)&(*ptQTask)[5].tQTaskRefList.ptHead * 4096.0;
    if ( v6->tPos.vZ + 40960.0 <= ptPos->vZ
      || v6->tPos.vX - igi2_frame.vRadius >= ptPos->vX
      || igi2_frame.vRadius + v6->tPos.vX <= ptPos->vX
      || v6->tPos.vY - igi2_frame.vRadius >= ptPos->vY
      || igi2_frame.vRadius + v6->tPos.vY <= ptPos->vY )
    {
      goto LABEL_10;
    }
    Water_SetVertexFunctionParameters(&v6->tDynCubeObj.tQObj.tQTask);
    igi2_frame.vInZ = ptPos->vZ - v6->tPos.vZ;
    igi2_frame.vInY = ptPos->vY - v6->tPos.vY;
    Water_ptActiveWater = v6;
    igi2_frame.vInX = ptPos->vX - v6->tPos.vX;
    Water_VertexFunction(&igi2_frame.vDepth, &igi2_frame.vRadius, &igi2_frame.tNormal, igi2_frame.vInX, igi2_frame.vInY, igi2_frame.vInZ, 0.0);
    Water_ptActiveWater = nullptr;
    if ( igi2_frame.vDepth > 0.0 )
      break;
    nTask = igi2_frame.n;
LABEL_10:
    ++v4;
    ptQTask = ++igi2_frame.v12;
    if ( v4 >= nTask )
      goto LABEL_11;
  }
  if ( pvDepth )
    *pvDepth = igi2_frame.vDepth;
  *iWaterIndex = v4;
  return true;
}

// source: h/2/water.c:1675  [anchor-callee]
int __cdecl Water_AddWave(
        struct Water_t *ptWater,
        struct real64x3_t *ptPos,
        float vMaxFrequency,
        float vMaxRadius,
        int ltcg_arg4)
{
  struct QObjectVector_s *tWavePool; // eax
  void **papxElement; // ecx
  _DWORD *v7; // edi
  _DWORD *v8; // esi
  int v9; // ecx
  struct QObjectVector_s *v10; // esi
  unsigned int nAllocated; // eax
  double *v12; // ebx
  double v13; // st7
  double vX; // st7
  double v15; // st7
  double vY; // st7
  double v17; // st7

  tWavePool = ptWater->tWavePool;
  if ( tWavePool->nAllocated == 5 )
  {
    papxElement = tWavePool->papxElement;
    v7 = *papxElement;
    v8 = papxElement + 1;
    v9 = tWavePool->nAllocated - 1;
    do
    {
      if ( (int)(*(_DWORD *)(*v8 + 64)) < (int)(v7[16]) )
        v7 = (_DWORD *)*v8;
      ++v8;
      --v9;
    }
    while ( v9 );
    QObjectVector_RemoveElement(tWavePool, *(_DWORD *)((char *)v7 + tWavePool->nElementSize - 4));
    Water_UpdateWaveBounds(ptWater);
  }
  v10 = ptWater->tWavePool;
  if ( v10->nAllocated == v10->nSize )
    QObjectVector_Realloc(ptWater->tWavePool, v10->nReallocSize);
  nAllocated = v10->nAllocated;
  v12 = (double *)v10->papxElement[nAllocated];
  v10->nAllocated = nAllocated + 1;
  *((_DWORD *)v12 + 16) = ptWater->nTick;
  *((_DWORD *)v12 + 17) = 150;
  qmemcpy(v12, ptPos, 0x18u);
  *((float *)v12 + 15) = vMaxRadius * 0.20000000298023224;
  v13 = *v12;
  *((float *)v12 + 10) = vMaxFrequency;
  *((float *)v12 + 11) = vMaxRadius;
  *((_DWORD *)v12 + 9) = ltcg_arg4;
  *((float *)v12 + 6) = v13 - ptWater->tPos.vX;
  *((float *)v12 + 7) = v12[1] - ptWater->tPos.vY;
  *((float *)v12 + 8) = v12[2] - ptWater->tPos.vZ;
  Water_UpdateWave(ptWater, (struct Wave_t *)v12);
  vX = *((float *)v12 + 11) + *((float *)v12 + 6);
  if ( vX < ptWater->tWaveMax.vX )
    vX = ptWater->tWaveMax.vX;
  ptWater->tWaveMax.vX = vX;
  v15 = *((float *)v12 + 6) - *((float *)v12 + 11);
  if ( v15 > ptWater->tWaveMin.vX )
    v15 = ptWater->tWaveMin.vX;
  ptWater->tWaveMin.vX = v15;
  vY = *((float *)v12 + 11) + *((float *)v12 + 7);
  if ( vY < ptWater->tWaveMax.vY )
    vY = ptWater->tWaveMax.vY;
  ptWater->tWaveMax.vY = vY;
  v17 = *((float *)v12 + 7) - *((float *)v12 + 11);
  if ( v17 > ptWater->tWaveMin.vY )
    v17 = ptWater->tWaveMin.vY;
  ptWater->tWaveMin.vY = v17;
  return *((_DWORD *)v12 + 17);
}

// source: h/2/water.c:1735  [anchor-caller]
struct real64x3_t *__cdecl Water_PlayerMovementEffect(
        struct real64x3_t *ptPos,
        int iWaterIndex,
        enum bool isRunning)
{
  struct Water_t *v4; // edi
  struct real64x3_t *result; // eax
  double v6; // st7
  int v7; // eax
  float vMaxFrequency; // [esp+0h] [ebp-14h]
  float vMaxRadius; // [esp+4h] [ebp-10h]

  v4 = (struct Water_t *)Water_ptQTaskList->ptQTask[iWaterIndex];
  if ( (ptPos->vZ - dbl_7B7A5C0) * (ptPos->vZ - dbl_7B7A5C0)
     + (ptPos->vY - dbl_7B7A5B8) * (ptPos->vY - dbl_7B7A5B8)
     + (ptPos->vX - dbl_7B7A5B0) * (ptPos->vX - dbl_7B7A5B0) > 150994944.0
    || (result = (struct real64x3_t *)(dword_834DBCC + dword_834DBC8), v4->nTick > dword_834DBCC + dword_834DBC8) )
  {
    v6 = (double)(int)isRunning;
    vMaxRadius = (v6 + 1.0) * 16384.0;
    vMaxFrequency = (v6 + 1.0) * 204.8;
    v7 = Water_AddWave(v4, ptPos, vMaxFrequency, vMaxRadius, 1170210816);
    dword_834DBCC = v4->nTick;
    result = (struct real64x3_t *)(v7 >> 1);
    dword_834DBC8 = (int)result;
    qmemcpy(&dbl_7B7A5B0, ptPos, 0x18u);
  }
  return result;
}

// source: h/2/water.c:1771  [anchor-callee]
enum bool __cdecl Water_GunShotEffect(
        struct real64x3_t *ptPos,
        struct QIntersection_s *ptIntersection,
        float vPenetrationPower,
        struct TexInfo_s *ptSplashTexture,
        int iWaterIndex,
        enum bool isExplosion)
{
  #pragma pack(push, 1)
  union
  {
    struct { float vInX; };
    struct { char igi2_o1[4]; float vInY; };
    struct { char igi2_o2[36]; int pvOutDeltaZ; };
    struct { char igi2_o3[40]; float pvOutRelativeZ; };
    struct { char igi2_o4[44]; struct real32x3_t ptOutNormal; };
    char igi2_extent[60];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QObj_s *ptHitObj; // ebp
  _DWORD *vY_high; // edi
  int v9; // eax
  int v10; // ebx
  unsigned __int16 v11; // cx
  struct Water_t *v12; // edx
  int v13; // eax
  enum bool result; // eax
  long double v15; // st7
  struct Water_t *v16; // ebx
  int v17; // ebp
  struct QObjectVector_s *ptBulletSplashVector; // edi
  bool v19; // zf
  unsigned int nAllocated; // eax
  float *v21; // edi
  double vY; // st7
  unsigned int v23; // ecx
  unsigned int v24; // ecx
  double v25; // st7

  if ( isExplosion )
  {
    result = (enum bool)Water_ptQTaskList;
    v16 = (struct Water_t *)Water_ptQTaskList->ptQTask[iWaterIndex];
    if ( v16 )
    {
      v17 = 0;
      dword_7B7A5A4 = 0;
      do
      {
        ptBulletSplashVector = v16->ptBulletSplashVector;
        v19 = ptBulletSplashVector->nAllocated == ptBulletSplashVector->nSize;
        igi2_frame.pvOutDeltaZ = (int)ptBulletSplashVector;
        if ( v19 )
        {
          QObjectVector_Realloc(ptBulletSplashVector, ptBulletSplashVector->nReallocSize);
          v17 = dword_7B7A5A4;
        }
        nAllocated = ptBulletSplashVector->nAllocated;
        v21 = (float *)ptBulletSplashVector->papxElement[nAllocated];
        *(_DWORD *)(igi2_frame.pvOutDeltaZ + 36) = nAllocated + 1;
        Water_ptActiveWater = v16;
        Water_SetVertexFunctionParameters(&v16->tDynCubeObj.tQObj.tQTask);
        igi2_frame.vInY = ptPos->vY;
        igi2_frame.vInX = ptPos->vX;
        Water_VertexFunction(&igi2_frame.pvOutRelativeZ, (float *)&igi2_frame.pvOutDeltaZ, &igi2_frame.ptOutNormal, igi2_frame.vInX, igi2_frame.vInY, 0.0, 0.0);
        *((_DWORD *)v21 + 10) = 1;
        *v21 = ptPos->vX;
        vY = ptPos->vY;
        Water_ptActiveWater = nullptr;
        v21[1] = vY;
        v21[2] = igi2_frame.pvOutRelativeZ + v16->tPos.vZ - 2048.0;
        v21[11] = (double)dword_7B7A5A4 * 819.2000122070312;
        *((_DWORD *)v21 + 15) = v16->nTick + 8 * v17;
        v23 = (Water_tRandomState.anRandom[0] >> 7) ^ Water_tRandomState.anRandom[2];
        Water_tRandomState.anRandom[0] += v23 ^ Water_tRandomState.anRandom[1];
        Water_tRandomState.anRandom[2] = v23;
        Water_tRandomState.anRandom[1] ^= v23;
        v21[3] = ((0.5 - (double)LOWORD(Water_tRandomState.anRandom[0]) * 0.0000152587890625) * 0.5 + 1.0) * 0.05000000074505806;
        v24 = (Water_tRandomState.anRandom[0] >> 7) ^ Water_tRandomState.anRandom[2];
        Water_tRandomState.anRandom[0] += v24 ^ Water_tRandomState.anRandom[1];
        v25 = (double)LOWORD(Water_tRandomState.anRandom[0]);
        Water_tRandomState.anRandom[2] = v24;
        Water_tRandomState.anRandom[1] ^= v24;
        v21[13] = 1.0;
        v21[14] = 1.0;
        igi2_frame.pvOutDeltaZ = v17 / 6;
        ++v17;
        v21[7] = 3.0;
        v21[8] = 0.0;
        *((_DWORD *)v21 + 9) = &tWaterExplosionTexture.tTexInfo;
        v21[4] = ((0.5 - v25 * 0.0000152587890625) * 0.30000001192092896 + 1.0) * 16.0;
        dword_7B7A5A4 = v17;
        v21[12] = 1.0 - (double)igi2_frame.pvOutDeltaZ;
      }
      while ( v17 < 7 );
      if ( v16->vRadius <= 10.0 )
        return Water_AddWave(v16, ptPos, 1228.800048828125, 40960.0, 0);
      else
        return Water_AddWave(v16, ptPos, 6144.0, 81920.0, 0);
    }
  }
  else
  {
    ptHitObj = ptIntersection->ptHitObj;
    vY_high = (_DWORD *)HIDWORD(ptIntersection->ptHitObj[16].tPos.vY);
    if ( vY_high[9] == vY_high[10] )
      QObjectVector_Realloc((struct QObjectVector_s *)HIDWORD(ptIntersection->ptHitObj[16].tPos.vY), vY_high[11]);
    v9 = vY_high[9];
    v10 = *(_DWORD *)(vY_high[12] + 4 * v9);
    v11 = Water_eQTaskType;
    vY_high[9] = v9 + 1;
    *(float *)v10 = ptPos->vX;
    *(float *)(v10 + 4) = ptPos->vY;
    *(float *)(v10 + 8) = ptPos->vZ;
    *(_DWORD *)(v10 + 60) = LODWORD(ptHitObj[22].tPos.vZ);
    v12 = (struct Water_t *)ptIntersection->ptHitObj;
    if ( QTask_IsQTaskTypeDerived(ptIntersection->ptHitObj->tQTask.eQTaskType, v11)
      && vPenetrationPower > 2.0
      && ((ptPos->vZ - dbl_7B7A570) * (ptPos->vZ - dbl_7B7A570)
        + (ptPos->vY - dbl_7B7A568) * (ptPos->vY - dbl_7B7A568)
        + (ptPos->vX - dbl_7B7A560) * (ptPos->vX - dbl_7B7A560) > 37748736.0
       || SLODWORD(ptHitObj[22].tPos.vZ) > dword_834DBD4 + dword_834DBD0) )
    {
      v13 = Water_AddWave(v12, &ptIntersection->tPos, 409.6000061035156, 20480.0, 0);
      dword_834DBD4 = LODWORD(ptHitObj[22].tPos.vZ);
      dword_834DBD0 = v13 >> 1;
      qmemcpy(&dbl_7B7A560, ptPos, 0x18u);
    }
    *(_DWORD *)(v10 + 40) = 0;
    *(_DWORD *)(v10 + 28) = 1000593162;
    *(_DWORD *)(v10 + 32) = 1028443341;
    *(_DWORD *)(v10 + 52) = 1065353216;
    *(_DWORD *)(v10 + 56) = 1065353216;
    *(_DWORD *)(v10 + 44) = 0;
    *(_DWORD *)(v10 + 48) = 1065353216;
    *(_DWORD *)(v10 + 36) = ptSplashTexture;
    v15 = sqrt(vPenetrationPower) * 1.2000000476837158;
    *(float *)(v10 + 16) = v15;
    *(float *)(v10 + 12) = v15 * 0.019999999552965164;
    return 1065353216;
  }
  return result;
}

// source: h/2/water.c:1882  [anchor-hash]
void __cdecl Water_Open()
{
  struct QTaskList_s *v0; // eax
  unsigned __int16 v1; // si
  unsigned __int16 BaseQTaskType; // ax
  unsigned __int16 v3; // si
  struct ParameterList_s *v4; // eax
  int v5; // edx
  struct ParameterList_s *v6; // eax
  int v7; // edx
  __int16 v8; // si

  Water_eQTaskType = QTask_NewQTaskType("Water", 2704, DynCubeObj_eQTaskType, 0, 0);
  v0 = QTaskList_New(32);
  v1 = Water_eQTaskType;
  Water_ptQTaskList = v0;
  QTask_LinkQTaskEventHandlerFn(Water_eQTaskType, 0, Water_CreateHandler);
  QTask_LinkQTaskEventHandlerFn(v1, 5, Water_EnterHandler);
  QTask_LinkQTaskEventHandlerFn(
    v1,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Water_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(v1, ParameterList_eUpdateInternalDataQTaskEvent, Water_UpdateInternalDataHandler);
  QTask_LinkQTaskEventHandlerFn(v1, 10, Water_TraceLinesHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 1, Water_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 2, Water_DeleteHandler);
  QTask_LinkQTaskEventHandlerFn(
    v1,
    PhysicsObj_eHit,
    (void (__cdecl *)(struct QTask_s *, void *))Water_PhysicsObjHitHandler);
  BaseQTaskType = QTask_GetBaseQTaskType();
  v3 = QTask_NewQTaskType("WaterLayer", 72, BaseQTaskType, 0, 0);
  WaterLayer_eQTaskType = v3;
  QTask_LinkQTaskEventHandlerFn(v3, 0, (void (__cdecl *)(struct QTask_s *, void *))WaterLayer_CreateHandler);
  QTask_LinkQTaskEventHandlerFn(
    v3,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))WaterLayer_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(
    v3,
    ParameterList_eUpdateInternalDataQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))WaterLayer_UpdateInternalDataHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v3, 2, (void (__cdecl *)(struct QTask_s *))WaterLayer_DeleteHandler);
  v4 = (struct ParameterList_s *)Mem_AllocFn(612, 4);
  v5 = Level_eParameterTypeObjectPos;
  v4->ptParameterListItem = (struct ParameterListItem_s *)&v4[1];
  v4->nParameters = 0;
  v4->nMaxParameters = 30;
  Water_ptParameterList = v4;
  ParameterList_AddParameter(v4, 0x78u, v5, "Position", 7u, nullptr);
  ParameterList_AddParameter(Water_ptParameterList, 0xDCu, Level_eParameterTypeReal32, "Size", 7u, nullptr);
  ParameterList_AddParameter(Water_ptParameterList, 0xD0u, Level_eParameterTypeReal32, "Detail", 7u, nullptr);
  ParameterList_AddParameter(Water_ptParameterList, 0xD4u, Level_eParameterTypeReal32, "Alpha", 7u, nullptr);
  ParameterList_AddParameter(Water_ptParameterList, 0xE0u, Level_eParameterTypeReal32, "UV Scale", 7u, nullptr);
  ParameterList_AddParameter(Water_ptParameterList, 0xE4u, Level_eParameterTypeReal32, "Env Scale", 7u, nullptr);
  ParameterList_AddParameter(Water_ptParameterList, 0xE8u, Level_eParameterTypeReal32, "Fadeout", 7u, nullptr);
  ParameterList_AddParameter(Water_ptParameterList, 0x1ECu, Level_eParameterTypeString256, "Texture", 7u, nullptr);
  ParameterList_AddParameter(Water_ptParameterList, 0x41Cu, Level_eParameterTypeString256, "Envmap", 7u, nullptr);
  ParameterList_AddParameter(Water_ptParameterList, 0xA8u, Level_eParameterTypeRGB, "Diffuse Color", 7u, nullptr);
  ParameterList_AddParameter(Water_ptParameterList, 0xB4u, Level_eParameterTypeRGB, "Specular Color", 7u, nullptr);
  ParameterList_AddParameter(
    Water_ptParameterList,
    0xC0u,
    Level_eParameterTypeReal32,
    "Absorption length (depth) (m)",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Water_ptParameterList,
    0xD8u,
    Level_eParameterTypeReal32,
    "Max Reflection Angle (cos)",
    7u,
    nullptr);
  ParameterList_AddParameter(Water_ptParameterList, 0x83Cu, Level_eParameterTypebool8, "Cubemap", 7u, nullptr);
  ParameterList_AddParameter(
    Water_ptParameterList,
    0x6B7u,
    Level_eParameterTypeString16,
    "Plain env. map file",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Water_ptParameterList,
    0x5A4u,
    Level_eParameterTypeInt32,
    "Resolution of the environmental map",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Water_ptParameterList,
    0x558u,
    Level_eParameterTypeObjectPos,
    "Camera position",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Water_ptParameterList,
    0x570u,
    Level_eParameterTypeReal32x9,
    "Camera orientation",
    7u,
    nullptr);
  ParameterList_AddParameter(Water_ptParameterList, 0x598u, Level_eParameterTypeReal32, dword_687204, 7u, nullptr);
  ParameterList_AddParameter(Water_ptParameterList, 0x83Du, Level_eParameterTypebool8, off_68698C, 7u, nullptr);
  ParameterList_AddParameter(Water_ptParameterList, 0x83Eu, Level_eParameterTypebool8, "Terrain", 7u, nullptr);
  ParameterList_AddParameter(Water_ptParameterList, 0x83Fu, Level_eParameterTypebool8, "Rigid objects", 7u, nullptr);
  ParameterList_AddParameter(Water_ptParameterList, 0x840u, Level_eParameterTypebool8, "Forests", 7u, nullptr);
  ParameterList_AddParameter(Water_ptParameterList, 0x841u, Level_eParameterTypebool8, "Spline objects", 7u, nullptr);
  ParameterList_AddParameter(
    Water_ptParameterList,
    0x7E8u,
    Level_eParameterTypePushButton,
    "Rebuild env. map",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Water_ptParameterList,
    0x7D0u,
    Level_eParameterTypeInt32,
    "Environmental map number",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Water_ptParameterList,
    0x7E0u,
    Level_eParameterTypePushButton,
    "Save env. map",
    7u,
    nullptr);
  ParameterList_AddParameter(Water_ptParameterList, 0x5B8u, Level_eParameterTypeString16, "Resource list", 7u, nullptr);
  ParameterList_AddParameter(
    Water_ptParameterList,
    0x7E4u,
    Level_eParameterTypePushButton,
    "Make resource file",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Water_ptParameterList,
    0x7ECu,
    Level_eParameterTypeVarString,
    "Environmental map index",
    7u,
    nullptr);
  v6 = (struct ParameterList_s *)Mem_AllocFn(92, 4);
  v6->ptParameterListItem = (struct ParameterListItem_s *)&v6[1];
  v7 = Level_eParameterTypeReal32;
  v6->nParameters = 0;
  v6->nMaxParameters = 4;
  WaterLayer_ptParameterList = v6;
  ParameterList_AddParameter(v6, 0x30u, v7, "Frequency", 7u, nullptr);
  ParameterList_AddParameter(WaterLayer_ptParameterList, 0x34u, Level_eParameterTypeReal32, "Amplitude", 7u, nullptr);
  ParameterList_AddParameter(WaterLayer_ptParameterList, 0x38u, Level_eParameterTypeReal32, "Speed", 7u, nullptr);
  ParameterList_AddParameter(WaterLayer_ptParameterList, 0x3Cu, Level_eParameterTypeReal32, "Angle", 7u, nullptr);
  v8 = Level_eAllowSaveQTaskEvent;
  Water_tRandomState.anRandom[0] = -925902492;
  Water_tRandomState.anRandom[1] = -1684277418;
  Water_tRandomState.anRandom[2] = 376075981;
  QTask_LinkQTaskEventHandlerFn(
    Water_eQTaskType,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveHandler);
  QTask_LinkQTaskEventHandlerFn(
    WaterLayer_eQTaskType,
    v8,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveNoChildrenHandler);
  QTask_SetQTaskTypeGroup(Water_eQTaskType, 0x40000000u);
}

// source: h/2/water.c:2001  [size]
void __cdecl Water_Close()
{
  int v0; // esi
  int v1; // esi

  if ( WaterLayer_ptParameterList )
  {
    v0 = *(_DWORD *)((unsigned int)&WaterLayer_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
  if ( Water_ptParameterList )
  {
    v1 = *(_DWORD *)((unsigned int)&Water_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v1);
    memset(*(void **)(v1 + 8), 0xCDu, *(_DWORD *)(v1 + 16));
    free((void *)v1);
  }
  QTask_DeleteQTaskType(WaterLayer_eQTaskType);
  QTask_DeleteQTaskType(Water_eQTaskType);
  QTaskList_Delete(Water_ptQTaskList);
}

// source: h/2/water.c:2022  [size]
unsigned __int16 __cdecl Water_GetQTaskType()
{
  return Water_eQTaskType;
}

void __cdecl sub_5AC3D0(struct QTask_s *a1, void *a2)
{
  *(_DWORD *)a2 = dword_7B7A74C;
}
