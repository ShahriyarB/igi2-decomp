/* e/0/lightsource.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: e/0/lightsource.c:74  [size]
int __cdecl Lightsource_GetAddLightsourceRenderModeMethod()
{
  return Lightsource_eAddLightsourceRenderModeMethod;
}

// source: e/0/lightsource.c:87  [size]
int __cdecl Lightsource_GetRemoveLightsourceRenderModeMethod()
{
  return Lightsource_eRemoveLightsourceRenderModeMethod;
}

// source: e/0/lightsource.c:100  [anchor-hash]
void __cdecl Lightsource_Open()
{
  int v0; // eax
  int v1; // eax

  Lightsource_ptFreeDirlight = Lightsource_atDirlight;
  LODWORD(Lightsource_atDirlight[0].tDir.vX) = &Lightsource_atDirlight[1];
  LODWORD(Lightsource_atDirlight[1].tDir.vX) = &Lightsource_atDirlight[2];
  Lightsource_atDirlight[2].tDir.vX = 0.0;
  v0 = 0;
  while ( RenderMode_atRenderModeMethod[v0].isAllocated )
  {
    if ( ++v0 >= 128 )
    {
      LDebug_Error("RenderMode: Failed to create new method '%s'", "AddLightsource");
      goto LABEL_5;
    }
  }
  RenderMode_atRenderModeMethod[v0].zName = "AddLightsource";
  RenderMode_atRenderModeMethod[v0].isAllocated = 1;
  Lightsource_eAddLightsourceRenderModeMethod = v0;
  v1 = 0;
  while ( RenderMode_atRenderModeMethod[v1].isAllocated )
  {
    if ( ++v1 >= 128 )
    {
      LDebug_Error("RenderMode: Failed to create new method '%s'", "RemoveLightsource");
LABEL_5:
      abort();
    }
  }
  RenderMode_atRenderModeMethod[v1].zName = "RemoveLightsource";
  RenderMode_atRenderModeMethod[v1].isAllocated = 1;
  Lightsource_eRemoveLightsourceRenderModeMethod = v1;
}

// source: e/0/lightsource.c:133  [size]
void __cdecl Lightsource_Close()
{
  int v0; // edx

  v0 = Lightsource_eRemoveLightsourceRenderModeMethod;
  RenderMode_atRenderModeMethod[Lightsource_eAddLightsourceRenderModeMethod].isAllocated = 0;
  RenderMode_atRenderModeMethod[v0].isAllocated = 0;
}

// source: e/0/lightsource.c:150  [size]
void __cdecl Lightsource_ResetList()
{
  Lightsource_nLightDataBufferPos = 0;
  Lightsource_nNumPointlights = 0;
  Lightsource_nNumSpotlights = 0;
}

// source: e/0/lightsource.c:171  [anchor-mhash]
void __cdecl Lightsource_NewPointlight(struct real64x3_t *ptPos, struct real32x3_t *ptColor, float vRadius)
{
  int v3; // eax
  int v4; // edx
  int v5; // ecx
  struct real32x3_t *v6; // edx

  v3 = Lightsource_nNumPointlights;
  v4 = ++Lightsource_nIdealLightDataStackPos;
  if ( Lightsource_nNumPointlights < 10 && v4 <= 23 )
  {
    v5 = Lightsource_nLightDataStackPos;
    Lightsource_anLightDataStack[Lightsource_nLightDataStackPos] = Lightsource_nNumPointlights + 0x10000;
    Lightsource_nLightDataStackPos = v5 + 1;
    v6 = (struct real32x3_t *)(40 * v3 + 140676032);
    Lightsource_nNumPointlights = v3 + 1;
    qmemcpy(v6, ptPos, 0x18u);
    v6[2] = *ptColor;
    v6[3].vX = vRadius;
  }
}

// source: e/0/lightsource.c:213  [anchor-mhash]
void __cdecl Lightsource_NewSpotlight(
        struct real64x3_t *ptPos,
        struct real32x3_t *ptColor,
        float vRadius,
        struct real32x3_t *ptDir,
        float vAngle)
{
  int v5; // ecx
  int v6; // esi
  int v7; // eax

  ++Lightsource_nIdealLightDataStackPos;
  v5 = Lightsource_nNumSpotlights;
  if ( Lightsource_nNumSpotlights < 10 && Lightsource_nIdealLightDataStackPos <= 23 )
  {
    v6 = Lightsource_nLightDataStackPos;
    Lightsource_anLightDataStack[Lightsource_nLightDataStackPos] = Lightsource_nNumSpotlights + 0x20000;
    v7 = 56 * v5 + 140676576;
    Lightsource_nNumSpotlights = v5 + 1;
    Lightsource_nLightDataStackPos = v6 + 1;
    qmemcpy((void *)v7, ptPos, 0x18u);
    *(struct real32x3_t *)(v7 + 24) = *ptColor;
    *(float *)(v7 + 36) = vRadius;
    *(struct real32x3_t *)(v7 + 40) = *ptDir;
    *(float *)(v7 + 52) = cos(vAngle * 0.5);
  }
}

// source: e/0/lightsource.c:257  [size]
void __cdecl Lightsource_DeleteLight()
{
  if ( Lightsource_nIdealLightDataStackPos == Lightsource_nLightDataStackPos )
    --Lightsource_nLightDataStackPos;
  --Lightsource_nIdealLightDataStackPos;
}

// source: e/0/lightsource.c:278  [anchor-mhash]
int *__cdecl Lightsource_CreateIndexList(int *pnNumItems)
{
  int v1; // edx
  int v2; // ebx
  int *result; // eax

  v1 = Lightsource_nLightDataStackPos;
  v2 = Lightsource_nLightDataBufferPos;
  result = (int *)(4 * Lightsource_nLightDataBufferPos + 140666816);
  qmemcpy(result, Lightsource_anLightDataStack, 4 * Lightsource_nLightDataStackPos);
  Lightsource_nLightDataBufferPos = v1 + v2;
  *pnNumItems = v1;
  return result;
}

// source: e/0/lightsource.c:307  [anchor-strings]
struct Dirlight_s *__cdecl Lightsource_CreateDirlightList(
        int *pnNumDirlights,
        struct real64x3_t *ptPos,
        int *pnList,
        int nNumItems)
{
  struct real64x3_t *v4; // ebx
  float *v5; // edi
  float *v6; // esi
  struct Dirlight_s *v7; // edx
  int v8; // ecx
  int v9; // ecx
  double v10; // st7
  double v11; // st7
  double v12; // st6
  double v13; // st5
  double v14; // st4
  int v15; // ecx
  double v16; // st5
  double v17; // st4
  float v18; // ebx
  float v19; // ecx
  double v20; // rt0
  unsigned int v21; // ecx
  double vX; // st7
  int v23; // ecx
  double v24; // st7
  double v25; // st6
  float *v26; // ecx
  float v27; // ebx
  float v28; // ecx
  float vLen; // [esp+Ch] [ebp-44h]
  float vLena; // [esp+Ch] [ebp-44h]
  float vScale; // [esp+10h] [ebp-40h]
  float vScalea; // [esp+10h] [ebp-40h]
  struct real32x3_t *p_tFrontColor; // [esp+14h] [ebp-3Ch]
  float *p_vZ; // [esp+18h] [ebp-38h]
  int nNumDirlights; // [esp+1Ch] [ebp-34h]
  struct real32x3_t *p_tBackColor; // [esp+20h] [ebp-30h]
  float *p_vY; // [esp+24h] [ebp-2Ch]
  int iLight; // [esp+28h] [ebp-28h]
  float tTempNormal_4; // [esp+30h] [ebp-20h]
  double tTempVector_8; // [esp+40h] [ebp-10h]
  double tTempVector_8a; // [esp+40h] [ebp-10h]
  double tTempVector_16; // [esp+48h] [ebp-8h]
  double tTempVector_16a; // [esp+48h] [ebp-8h]

  v4 = ptPos;
  nNumDirlights = 0;
  iLight = 0;
  if ( nNumItems > 0 )
  {
    p_vZ = &Lightsource_atTempDirlight[0].tBackColor.vZ;
    p_vY = &Lightsource_atTempDirlight[0].tBackColor.vY;
    p_tBackColor = &Lightsource_atTempDirlight[0].tBackColor;
    p_tFrontColor = &Lightsource_atTempDirlight[0].tFrontColor;
    v5 = &Lightsource_atTempDirlight[0].tDir.vZ;
    v6 = &Lightsource_atTempDirlight[0].tDir.vY;
    v7 = Lightsource_atTempDirlight;
    do
    {
      v8 = pnList[iLight];
      if ( (v8 & 0xFFFF0000) == 0x10000 )
      {
        v21 = 5 * (unsigned __int16)v8;
        vX = Lightsource_atPointlight[v21 / 5].tPos.vX;
        v23 = 8 * v21 + 140676032;
        v24 = vX - v4->vX;
        tTempVector_8a = *(double *)(v23 + 8) - v4->vY;
        tTempVector_16a = *(double *)(v23 + 16) - v4->vZ;
        vLena = sqrt(tTempVector_8a * tTempVector_8a + tTempVector_16a * tTempVector_16a + v24 * v24);
        if ( vLena < (double)*(float *)(v23 + 36) && vLena != 0.0 )
        {
          v25 = vLena / *(float *)(v23 + 36);
          v26 = (float *)(v23 + 24);
          p_tFrontColor->vX = *v26;
          v27 = v26[1];
          v28 = v26[2];
          p_tFrontColor->vY = v27;
          p_tFrontColor->vZ = v28;
          *p_vZ = 0.0;
          p_tBackColor->vX = 0.0;
          ++nNumDirlights;
          p_tBackColor = (struct real32x3_t *)((char *)p_tBackColor + 40);
          *p_vY = 0.0;
          ++v7;
          v6 += 10;
          v5 += 10;
          p_tFrontColor = (struct real32x3_t *)((char *)p_tFrontColor + 40);
          v4 = ptPos;
          p_vY += 10;
          p_vZ += 10;
          vScalea = (1.0 - v25) / vLena;
          v7[-1].tDir.vX = v24 * vScalea;
          *(v6 - 10) = tTempVector_8a * vScalea;
          *(v5 - 10) = tTempVector_16a * vScalea;
        }
      }
      else
      {
        if ( (v8 & 0xFFFF0000) != 0x20000 )
        {
          LDebug_Error("Invalid lightsource type");
          abort();
        }
        v9 = 56 * (unsigned __int16)v8 + 140676576;
        v10 = *(double *)v9 - v4->vX;
        tTempVector_8 = *(double *)(v9 + 8) - v4->vY;
        tTempVector_16 = *(double *)(v9 + 16) - v4->vZ;
        vLen = sqrt(tTempVector_8 * tTempVector_8 + tTempVector_16 * tTempVector_16 + v10 * v10);
        if ( vLen < (double)*(float *)(v9 + 36) && vLen != 0.0 )
        {
          vScale = 1.0 / vLen;
          v11 = v10 * vScale;
          tTempNormal_4 = tTempVector_8 * vScale;
          v12 = tTempVector_16 * vScale;
          v13 = v12 * *(float *)(v9 + 48) + tTempNormal_4 * *(float *)(v9 + 44) + v11 * *(float *)(v9 + 40);
          if ( v13 > *(float *)(v9 + 52) )
          {
            v14 = v13 - *(float *)(v9 + 52);
            v15 = v9 + 24;
            ++v7;
            v6 += 10;
            v5 += 10;
            v16 = v13 * (v14 / (1.0 - *(float *)(v15 + 28)));
            v17 = vLen / *(float *)(v15 + 12);
            p_tFrontColor->vX = *(float *)v15;
            v18 = *(float *)(v15 + 4);
            v19 = *(float *)(v15 + 8);
            p_tFrontColor->vY = v18;
            p_tFrontColor->vZ = v19;
            *p_vZ = 0.0;
            p_tBackColor->vX = 0.0;
            ++nNumDirlights;
            p_tBackColor = (struct real32x3_t *)((char *)p_tBackColor + 40);
            *p_vY = 0.0;
            p_tFrontColor = (struct real32x3_t *)((char *)p_tFrontColor + 40);
            v4 = ptPos;
            p_vY += 10;
            p_vZ += 10;
            v20 = v16 * (1.0 - v17);
            v7[-1].tDir.vX = v11 * v20;
            *(v6 - 10) = tTempNormal_4 * v20;
            *(v5 - 10) = v12 * v20;
          }
        }
      }
      ++iLight;
    }
    while ( iLight < nNumItems );
  }
  *pnNumDirlights = nNumDirlights;
  return Lightsource_atTempDirlight;
}

// source: e/0/lightsource.c:424  [anchor-mhash]
struct Dirlight_s *__cdecl Lightsource_NewDirlight(
        struct real32x3_t *ptDir,
        struct real32x3_t *ptFrontColor,
        struct real32x3_t *ptBackColor,
        char isAffectTerrain,
        char isAffectObjects)
{
  struct Dirlight_s *v5; // esi
  void (__cdecl *v7)(void *); // eax
  struct LightsourceContext_t tContext; // [esp+4h] [ebp-Ch] BYREF

  if ( AppContext_tAppContext.isMainMenu )
    return nullptr;
  v5 = Lightsource_ptFreeDirlight;
  if ( !Lightsource_ptFreeDirlight )
    return nullptr;
  Lightsource_ptFreeDirlight = (struct Dirlight_s *)LODWORD(Lightsource_ptFreeDirlight->tDir.vX);
  v5->tDir = *ptDir;
  v5->tFrontColor = *ptFrontColor;
  v5->tBackColor = *ptBackColor;
  v5->isAffectTerrain = isAffectTerrain;
  v5->isAffectObjects = isAffectObjects;
  v7 = RenderMode_tActiveRenderMode.apfRenderModeMethod[Lightsource_eAddLightsourceRenderModeMethod];
  tContext.eLightsourceType = LIGHTSOURCE_TYPE_DIRECTIONAL;
  tContext.iLightIndex = (int)&v5[-3245826].tFrontColor.vY / 40;
  tContext.ptLight.ptPointlight = (struct Pointlight_s *)v5;
  if ( v7 )
    v7(&tContext);
  return v5;
}

// source: e/0/lightsource.c:467  [anchor-mhash]
void __cdecl Lightsource_UpdateDirlight(struct Dirlight_s *ptDirlight)
{
  void (__cdecl *v1)(void *); // eax
  struct LightsourceContext_t tContext; // [esp+0h] [ebp-Ch] BYREF

  if ( AppContext_tAppContext.isMainMenu == false )
  {
    v1 = RenderMode_tActiveRenderMode.apfRenderModeMethod[Lightsource_eAddLightsourceRenderModeMethod];
    tContext.eLightsourceType = LIGHTSOURCE_TYPE_DIRECTIONAL;
    tContext.iLightIndex = (int)&ptDirlight[-3245826].tFrontColor.vY / 40;
    tContext.ptLight.ptPointlight = (struct Pointlight_s *)ptDirlight;
    if ( v1 )
      v1(&tContext);
  }
}

// source: e/0/lightsource.c:493  [anchor-mhash]
void __cdecl Lightsource_SetAmbientlight(struct Ambientlight_t *ptAmbientlight)
{
  void (__cdecl *v1)(void *); // eax
  struct LightsourceContext_t tContext; // [esp+0h] [ebp-Ch] BYREF

  if ( AppContext_tAppContext.isMainMenu == false )
  {
    tContext.ptLight.ptPointlight = (struct Pointlight_s *)ptAmbientlight;
    v1 = RenderMode_tActiveRenderMode.apfRenderModeMethod[Lightsource_eAddLightsourceRenderModeMethod];
    tContext.eLightsourceType = LIGHTSOURCE_TYPE_AMBIENT;
    tContext.iLightIndex = 0;
    if ( v1 )
      v1(&tContext);
  }
}

// source: e/0/lightsource.c:517  [anchor-mhash]
void __cdecl Lightsource_DeleteDirlight(struct Dirlight_s *ptDirlight)
{
  void (__cdecl *v1)(void *); // eax
  struct LightsourceContext_t tContext; // [esp+0h] [ebp-Ch] BYREF

  if ( AppContext_tAppContext.isMainMenu == false )
  {
    v1 = RenderMode_tActiveRenderMode.apfRenderModeMethod[Lightsource_eRemoveLightsourceRenderModeMethod];
    tContext.eLightsourceType = LIGHTSOURCE_TYPE_DIRECTIONAL;
    tContext.iLightIndex = (int)&ptDirlight[-3245826].tFrontColor.vY / 40;
    tContext.ptLight.ptPointlight = (struct Pointlight_s *)ptDirlight;
    if ( v1 )
      v1(&tContext);
    LODWORD(ptDirlight->tDir.vX) = Lightsource_ptFreeDirlight;
    Lightsource_ptFreeDirlight = ptDirlight;
  }
}
