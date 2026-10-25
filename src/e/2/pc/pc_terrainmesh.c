/* e/2/pc/pc_terrainmesh.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: e/2/pc/pc_terrainmesh.c:41  [size]
void __cdecl TerrainMesh_InitRender()
{
  ;
}

// source: e/2/pc/pc_terrainmesh.c:46  [size]
void __cdecl TerrainMesh_Render()
{
  ;
}

// source: e/2/pc/pc_terrainmesh.c:51  [size]
void __cdecl DrawTerrainMesh_Init(struct World_s *ptWorld)
{
  ;
}

// source: e/2/pc/pc_terrainmesh.c:56  [size]
void __cdecl TerrainMesh_Open()
{
  ;
}

// source: e/2/pc/pc_terrainmesh.c:61  [size]
void __cdecl TerrainMesh_Close()
{
  ;
}

// source: e/2/pc/pc_terrainmesh.c:73  [size]
void __cdecl DrawTerrainMesh_CalculateLightning(struct World_s *ptWorld, struct RGB8_s *ptColor)
{
  ;
}

// source: e/2/pc/pc_terrainmesh.c:176  [size]
void __cdecl DrawTerrainMesh_Open()
{
  ;
}

// source: e/2/pc/pc_terrainmesh.c:189  [size]
void __cdecl DrawTerrainMesh_Close()
{
  ;
}

// source: e/2/pc/pc_terrainmesh.c:202  [anchor-callee]
void __cdecl DrawTerrainMesh_SetFog(struct real32x3_t *ptColor, float vDensity)
{
  DrawTerrainMesh_tFogColor = *ptColor;
  DrawTerrainMesh_vFogDensity = vDensity;
  if ( DrawTerrainMesh_tFogColor.vX >= 0.0 )
  {
    if ( DrawTerrainMesh_tFogColor.vX > 1.0 )
      DrawTerrainMesh_tFogColor.vX = 1.0;
  }
  else
  {
    DrawTerrainMesh_tFogColor.vX = 0.0;
  }
  if ( DrawTerrainMesh_tFogColor.vY >= 0.0 )
  {
    if ( DrawTerrainMesh_tFogColor.vY > 1.0 )
      DrawTerrainMesh_tFogColor.vY = 1.0;
  }
  else
  {
    DrawTerrainMesh_tFogColor.vY = 0.0;
  }
  if ( DrawTerrainMesh_tFogColor.vZ >= 0.0 )
  {
    if ( DrawTerrainMesh_tFogColor.vZ > 1.0 )
      DrawTerrainMesh_tFogColor.vZ = 1.0;
  }
  else
  {
    DrawTerrainMesh_tFogColor.vZ = 0.0;
  }
  if ( vDensity >= 0.0 )
  {
    if ( vDensity > 16384.0 )
      DrawTerrainMesh_vFogDensity = 16384.0;
  }
  else
  {
    DrawTerrainMesh_vFogDensity = 0.0;
  }
}

// source: e/2/pc/pc_terrainmesh.c:221  [size]
struct real32x3_t *__cdecl DrawTerrainMesh_SetAmbientColor(struct real32x3_t *ptColor)
{
  float vX; // ecx
  float vY; // edx
  struct real32x3_t *result; // eax

  vX = ptColor->vX;
  vY = ptColor->vY;
  result = (struct real32x3_t *)LODWORD(ptColor->vZ);
  DrawTerrainMesh_tAmbientColor.vX = vX;
  DrawTerrainMesh_tAmbientColor.vY = vY;
  LODWORD(DrawTerrainMesh_tAmbientColor.vZ) = result;
  return result;
}
