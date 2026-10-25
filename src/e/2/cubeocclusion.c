/* e/2/cubeocclusion.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: e/2/cubeocclusion.c:204  [anchor-hash]
void __cdecl CubeOcclusion_ResetList()
{
  unsigned int *v0; // eax
  int v1; // ecx
  _DWORD *v2; // eax
  double vY; // st7

  v0 = CubeOcclusion_abFrameBuffer;
  v1 = 48;
  do
  {
    *v0 = 0;
    v2 = v0 + 1;
    *v2 = 0;
    v0 = v2 + 1;
    --v1;
  }
  while ( v1 );
  CubeOcclusion_vVertexMaxX = QCube_atGlobalCubePos[0].vX;
  CubeOcclusion_vScreenFOVX = 1.0 / (TransContext_tActiveTransContext.vFOVX * 1.2) * 32.0;
  CubeOcclusion_vScreenFOVY = 1.0 / (TransContext_tActiveTransContext.vFOVY * 1.2) * 24.0;
  vY = QCube_atGlobalCubePos[0].vY;
  if ( QCube_atGlobalCubePos[1].vX > QCube_atGlobalCubePos[0].vX )
    CubeOcclusion_vVertexMaxX = QCube_atGlobalCubePos[1].vX;
  if ( QCube_atGlobalCubePos[1].vY > QCube_atGlobalCubePos[0].vY )
    vY = QCube_atGlobalCubePos[1].vY;
  if ( QCube_atGlobalCubePos[2].vX > CubeOcclusion_vVertexMaxX )
    CubeOcclusion_vVertexMaxX = QCube_atGlobalCubePos[2].vX;
  if ( QCube_atGlobalCubePos[2].vY > vY )
    vY = QCube_atGlobalCubePos[2].vY;
  if ( QCube_atGlobalCubePos[3].vX > CubeOcclusion_vVertexMaxX )
    CubeOcclusion_vVertexMaxX = QCube_atGlobalCubePos[3].vX;
  if ( QCube_atGlobalCubePos[3].vY > vY )
    vY = QCube_atGlobalCubePos[3].vY;
  if ( QCube_atGlobalCubePos[4].vX > CubeOcclusion_vVertexMaxX )
    CubeOcclusion_vVertexMaxX = QCube_atGlobalCubePos[4].vX;
  if ( QCube_atGlobalCubePos[4].vY > vY )
    vY = QCube_atGlobalCubePos[4].vY;
  if ( QCube_atGlobalCubePos[5].vX > CubeOcclusion_vVertexMaxX )
    CubeOcclusion_vVertexMaxX = QCube_atGlobalCubePos[5].vX;
  if ( QCube_atGlobalCubePos[5].vY > vY )
    vY = QCube_atGlobalCubePos[5].vY;
  if ( QCube_atGlobalCubePos[6].vX > CubeOcclusion_vVertexMaxX )
    CubeOcclusion_vVertexMaxX = QCube_atGlobalCubePos[6].vX;
  if ( QCube_atGlobalCubePos[6].vY > vY )
    vY = QCube_atGlobalCubePos[6].vY;
  if ( QCube_atGlobalCubePos[7].vX > CubeOcclusion_vVertexMaxX )
    CubeOcclusion_vVertexMaxX = QCube_atGlobalCubePos[7].vX;
  if ( QCube_atGlobalCubePos[7].vY > vY )
    vY = QCube_atGlobalCubePos[7].vY;
  CubeOcclusion_vVertexMaxX = CubeOcclusion_vVertexMaxX * CubeOcclusion_vScreenFOVX * 1.2;
  CubeOcclusion_vVertexMaxY = vY * CubeOcclusion_vScreenFOVY * 1.2;
}

// source: e/2/cubeocclusion.c:330  [anchor-strings]
void __cdecl CubeOcclusion_Open()
{
  unsigned int *v0; // eax
  int v1; // ecx
  _DWORD *v2; // eax
  int v3; // esi
  int i; // edi
  int j; // eax
  int k; // eax

  CubeOcclusion_eOcclusionDrawQTaskEvent = QTask_NewQTaskEventFn(0, "OcclusionDraw");
  v0 = CubeOcclusion_abFrameBuffer;
  v1 = 48;
  do
  {
    *v0 = 0;
    v2 = v0 + 1;
    *v2 = 0;
    v0 = v2 + 1;
    --v1;
  }
  while ( v1 );
  v3 = 0;
  for ( i = 0; i < 8; ++i )
  {
    for ( j = 0; j < 64; ++j )
    {
      CubeOcclusion_aabEdgeMaskMap[v3][j] = 0;
      if ( (j & 1) != 0 )
        CubeOcclusion_aabEdgeMaskMap[v3][j] = 1 << CubeOcclusion_aabEdgeMap[i][0];
      if ( (j & 2) != 0 )
        CubeOcclusion_aabEdgeMaskMap[v3][j] |= 1 << CubeOcclusion_aabEdgeMap[i][1];
      if ( (j & 4) != 0 )
        CubeOcclusion_aabEdgeMaskMap[v3][j] |= 1 << CubeOcclusion_aabEdgeMap[i][2];
      if ( (j & 8) != 0 )
        CubeOcclusion_aabEdgeMaskMap[v3][j] |= 1 << CubeOcclusion_aabEdgeMap[i][3];
      if ( (j & 0x10) != 0 )
        CubeOcclusion_aabEdgeMaskMap[v3][j] |= 1 << CubeOcclusion_aabEdgeMap[i][4];
      if ( (j & 0x20) != 0 )
        CubeOcclusion_aabEdgeMaskMap[v3][j] |= 1 << CubeOcclusion_aabEdgeMap[i][5];
      CubeOcclusion_aabEdgeMaskMapInverse[v3][j] = 0;
      if ( (j & 1) != 0 )
        CubeOcclusion_aabEdgeMaskMapInverse[v3][j] = 1 << CubeOcclusion_aabEdgeMapInverse[i][0];
      if ( (j & 2) != 0 )
        CubeOcclusion_aabEdgeMaskMapInverse[v3][j] |= 1 << CubeOcclusion_aabEdgeMapInverse[i][1];
      if ( (j & 4) != 0 )
        CubeOcclusion_aabEdgeMaskMapInverse[v3][j] |= 1 << CubeOcclusion_aabEdgeMapInverse[i][2];
      if ( (j & 8) != 0 )
        CubeOcclusion_aabEdgeMaskMapInverse[v3][j] |= 1 << CubeOcclusion_aabEdgeMapInverse[i][3];
      if ( (j & 0x10) != 0 )
        CubeOcclusion_aabEdgeMaskMapInverse[v3][j] |= 1 << CubeOcclusion_aabEdgeMapInverse[i][4];
      if ( (j & 0x20) != 0 )
        CubeOcclusion_aabEdgeMaskMapInverse[v3][j] |= 1 << CubeOcclusion_aabEdgeMapInverse[i][5];
    }
    ++v3;
  }
  for ( k = 0; k < 64; ++k )
  {
    CubeOcclusion_abEnableVertex[k] = 0;
    if ( (k & 1) != 0 )
      CubeOcclusion_abEnableVertex[k] = (1 << CubeOcclusion_aaiFaceTable[0][0])
                                      | (1 << CubeOcclusion_aaiFaceTable[0][1])
                                      | (1 << CubeOcclusion_aaiFaceTable[0][2])
                                      | (1 << CubeOcclusion_aaiFaceTable[0][3]);
    if ( (k & 2) != 0 )
      CubeOcclusion_abEnableVertex[k] |= (unsigned __int8)(1 << CubeOcclusion_aaiFaceTable[1][0])
                                       | (1 << CubeOcclusion_aaiFaceTable[1][1])
                                       | (1 << CubeOcclusion_aaiFaceTable[1][2])
                                       | (1 << CubeOcclusion_aaiFaceTable[1][3]);
    if ( (k & 4) != 0 )
      CubeOcclusion_abEnableVertex[k] |= (unsigned __int8)(1 << CubeOcclusion_aaiFaceTable[2][0])
                                       | (1 << CubeOcclusion_aaiFaceTable[2][1])
                                       | (1 << CubeOcclusion_aaiFaceTable[2][2])
                                       | (1 << CubeOcclusion_aaiFaceTable[2][3]);
    if ( (k & 8) != 0 )
      CubeOcclusion_abEnableVertex[k] |= (unsigned __int8)(1 << CubeOcclusion_aaiFaceTable[3][0])
                                       | (1 << CubeOcclusion_aaiFaceTable[3][1])
                                       | (1 << CubeOcclusion_aaiFaceTable[3][2])
                                       | (1 << CubeOcclusion_aaiFaceTable[3][3]);
    if ( (k & 0x10) != 0 )
      CubeOcclusion_abEnableVertex[k] |= (unsigned __int8)(1 << CubeOcclusion_aaiFaceTable[4][0])
                                       | (1 << CubeOcclusion_aaiFaceTable[4][1])
                                       | (1 << CubeOcclusion_aaiFaceTable[4][2])
                                       | (1 << CubeOcclusion_aaiFaceTable[4][3]);
    if ( (k & 0x20) != 0 )
      CubeOcclusion_abEnableVertex[k] |= (unsigned __int8)(1 << CubeOcclusion_aaiFaceTable[5][0])
                                       | (1 << CubeOcclusion_aaiFaceTable[5][1])
                                       | (1 << CubeOcclusion_aaiFaceTable[5][2])
                                       | (1 << CubeOcclusion_aaiFaceTable[5][3]);
  }
}

// source: e/2/cubeocclusion.c:425  [anchor-hash]
void __cdecl CubeOcclusion_Close()
{
  QTask_DeleteQTaskEvent(CubeOcclusion_eOcclusionDrawQTaskEvent);
  CubeOcclusion_eOcclusionDrawQTaskEvent = 512;
}

// source: e/2/cubeocclusion.c:442  [anchor-mhash]
int __cdecl CubeOcclusion_DrawRectangle(int iVertex0, int iVertex1, int iVertex2, int iVertex3)
{
  int nX; // eax
  int v6; // ecx
  int v7; // edx
  int v8; // esi
  int v9; // edx
  int v10; // edi
  int v11; // edx
  int v12; // edx
  int v13; // edx
  int v14; // edx
  int nY; // ecx
  int v16; // edx
  int v17; // edi
  int result; // eax
  int v19; // edi
  int v20; // ebx
  int v21; // edi
  int v22; // edi
  int v23; // edi
  int v24; // edi
  int v25; // edx
  int v26; // ecx
  unsigned int v27; // eax
  unsigned int v28; // ecx
  char v29; // dl
  char v30; // si
  int v31; // edx
  int v32; // ebx
  int nMinX; // [esp+14h] [ebp-4h]
  int iVertex0a = *(int *)&iVertex0; // [esp+20h] [ebp+8h] ARGSLOT
  int iVertex0b = *(int *)&iVertex0; // [esp+20h] [ebp+8h] ARGSLOT
  int iVertex1a = *(int *)&iVertex2; // [esp+24h] [ebp+Ch] ARGSLOT
  int iVertex2a = *(int *)&iVertex3; // [esp+28h] [ebp+10h] ARGSLOT

  nX = CubeOcclusion_atScreenPos[iVertex0].nX;
  v6 = CubeOcclusion_atScreenPos[iVertex1].nX;
  v7 = nX;
  if ( nX >= v6 )
    v7 = CubeOcclusion_atScreenPos[iVertex1].nX;
  v8 = CubeOcclusion_atScreenPos[iVertex2].nX;
  if ( v7 >= v8 )
  {
    v9 = CubeOcclusion_atScreenPos[iVertex2].nX;
  }
  else if ( nX >= v6 )
  {
    v9 = CubeOcclusion_atScreenPos[iVertex1].nX;
  }
  else
  {
    v9 = CubeOcclusion_atScreenPos[iVertex0].nX;
  }
  v10 = CubeOcclusion_atScreenPos[iVertex3].nX;
  if ( v9 >= v10 )
  {
    nMinX = CubeOcclusion_atScreenPos[iVertex3].nX;
  }
  else
  {
    v11 = CubeOcclusion_atScreenPos[iVertex0].nX;
    if ( nX >= v6 )
      v11 = CubeOcclusion_atScreenPos[iVertex1].nX;
    if ( v11 >= v8 )
    {
      nMinX = CubeOcclusion_atScreenPos[iVertex2].nX;
    }
    else if ( nX >= v6 )
    {
      nMinX = CubeOcclusion_atScreenPos[iVertex1].nX;
    }
    else
    {
      nMinX = CubeOcclusion_atScreenPos[iVertex0].nX;
    }
  }
  v12 = CubeOcclusion_atScreenPos[iVertex0].nX;
  if ( nX <= v6 )
    v12 = CubeOcclusion_atScreenPos[iVertex1].nX;
  if ( v12 <= v8 )
  {
    v13 = CubeOcclusion_atScreenPos[iVertex2].nX;
  }
  else if ( nX <= v6 )
  {
    v13 = CubeOcclusion_atScreenPos[iVertex1].nX;
  }
  else
  {
    v13 = CubeOcclusion_atScreenPos[iVertex0].nX;
  }
  if ( v13 <= v10 )
  {
    v8 = CubeOcclusion_atScreenPos[iVertex3].nX;
  }
  else
  {
    v14 = CubeOcclusion_atScreenPos[iVertex0].nX;
    if ( nX <= v6 )
      v14 = CubeOcclusion_atScreenPos[iVertex1].nX;
    if ( v14 > v8 )
    {
      if ( nX <= v6 )
        v8 = CubeOcclusion_atScreenPos[iVertex1].nX;
      else
        v8 = CubeOcclusion_atScreenPos[iVertex0].nX;
    }
  }
  nY = CubeOcclusion_atScreenPos[iVertex0].nY;
  v16 = CubeOcclusion_atScreenPos[iVertex1].nY;
  v17 = nY;
  if ( nY >= v16 )
    v17 = CubeOcclusion_atScreenPos[iVertex1].nY;
  result = CubeOcclusion_atScreenPos[iVertex2].nY;
  if ( v17 >= result )
  {
    v19 = CubeOcclusion_atScreenPos[iVertex2].nY;
  }
  else if ( nY >= v16 )
  {
    v19 = CubeOcclusion_atScreenPos[iVertex1].nY;
  }
  else
  {
    v19 = CubeOcclusion_atScreenPos[iVertex0].nY;
  }
  v20 = CubeOcclusion_atScreenPos[iVertex3].nY;
  if ( v19 >= v20 )
  {
    iVertex0a = CubeOcclusion_atScreenPos[iVertex3].nY;
  }
  else
  {
    v21 = CubeOcclusion_atScreenPos[iVertex0].nY;
    if ( nY >= v16 )
      v21 = v16;
    if ( v21 >= result )
    {
      iVertex0a = CubeOcclusion_atScreenPos[iVertex2].nY;
    }
    else if ( nY >= v16 )
    {
      iVertex0a = v16;
    }
    else
    {
      iVertex0a = CubeOcclusion_atScreenPos[iVertex0].nY;
    }
  }
  v22 = nY;
  if ( nY <= v16 )
    v22 = v16;
  if ( v22 <= result )
  {
    v23 = CubeOcclusion_atScreenPos[iVertex2].nY;
  }
  else if ( nY <= v16 )
  {
    v23 = v16;
  }
  else
  {
    v23 = nY;
  }
  if ( v23 <= v20 )
  {
    result = CubeOcclusion_atScreenPos[iVertex3].nY;
  }
  else
  {
    v24 = nY;
    if ( nY <= v16 )
      v24 = v16;
    if ( v24 > result )
    {
      if ( nY <= v16 )
        result = v16;
      else
        result = nY;
    }
  }
  v25 = nMinX <= 0 ? 0 : nMinX;
  if ( v8 >= 64 )
    v8 = 64;
  v26 = iVertex0a <= 0 ? 0 : iVertex0a;
  if ( result >= 48 )
    result = 48;
  if ( v25 < v8 && v26 < result )
  {
    iVertex0b = 8 * result;
    iVertex2a = 8 * v26;
    v27 = (v25 >> 3) & 0xFFFFFFFC;
    v28 = (v8 >> 3) & 0xFFFFFFFC;
    v29 = v25 - 32 * v27;
    v30 = v8 - 32 * v28;
    iVertex1a = v27;
    if ( v27 == v28 )
    {
      result = v27 + iVertex2a;
      v31 = (-1 << v29) & ((1 << v30) - 1);
      do
      {
        *(unsigned int *)((char *)CubeOcclusion_abFrameBuffer + result) |= v31;
        result += 8;
      }
      while ( result < iVertex0b );
    }
    else if ( v27 == v28 - 4 )
    {
      result = v27 + iVertex2a;
      do
      {
        *(unsigned int *)((char *)CubeOcclusion_abFrameBuffer + result) |= -1 << v29;
        *(unsigned int *)((char *)&CubeOcclusion_abFrameBuffer[1] + result) |= (1 << v30) - 1;
        result += 8;
      }
      while ( result < iVertex0b );
    }
    else
    {
      result = iVertex2a;
      do
      {
        *(unsigned int *)((char *)CubeOcclusion_abFrameBuffer + result + iVertex1a) |= -1 << v29;
        *(unsigned int *)((char *)CubeOcclusion_abFrameBuffer + result + v28) |= (1 << v30) - 1;
        if ( (int)(v28 - iVertex1a) >= 8 )
        {
          v32 = result + iVertex1a + 4;
          do
          {
            *(unsigned int *)((char *)CubeOcclusion_abFrameBuffer + v32) = -1;
            v32 += 4;
          }
          while ( v32 < (int)(result + v28) );
        }
        result += 8;
      }
      while ( result < iVertex0b );
    }
  }
  return result;
}

// source: e/2/cubeocclusion.c:591  [anchor-mhash]
char __cdecl CubeOcclusion_CheckRectangle(int nMinX, int nMaxX, int nMinY, int nMaxY)
{
  int v5; // eax
  int v6; // edx
  int v7; // eax
  int v8; // eax
  int v9; // ebx
  int v10; // ecx
  int v11; // ebx
  int v12; // [esp+4h] [ebp-38h]
  int v13; // [esp+8h] [ebp-34h]
  int nFracStartX; // [esp+20h] [ebp-1Ch]
  int nFracStopX; // [esp+24h] [ebp-18h]
  char isVisible; // [esp+2Bh] [ebp-11h]
  int nBufferStartX; // [esp+2Ch] [ebp-10h]
  int nScanOffs; // [esp+30h] [ebp-Ch]
  int nMaxScanOffs; // [esp+34h] [ebp-8h]
  int nBufferStopX; // [esp+38h] [ebp-4h]
  int nMinXa = *(int *)&nMinX; // [esp+44h] [ebp+8h] ARGSLOT
  int nMinYa = *(int *)&nMinY; // [esp+4Ch] [ebp+10h] ARGSLOT

  isVisible = 0;
  nMinXa = nMinX <= 0 ? 0 : nMinX;
  if ( nMaxX >= 64 )
    v13 = 64;
  else
    v13 = nMaxX;
  nMinYa = nMinY <= 0 ? 0 : nMinY;
  if ( nMaxY >= 48 )
    v12 = 48;
  else
    v12 = nMaxY;
  if ( nMinXa >= v13 || nMinYa >= v12 )
    return 0;
  nScanOffs = 8 * nMinYa;
  nMaxScanOffs = 8 * v12;
  nBufferStartX = 4 * (nMinXa >> 5);
  nBufferStopX = 4 * (v13 >> 5);
  nFracStartX = nMinXa - (nMinXa >> 5 << 7);
  nFracStopX = v13 - (v13 >> 5 << 7);
  if ( nBufferStartX == nBufferStopX )
  {
    v5 = nBufferStartX + nScanOffs;
    while ( 1 )
    {
      v6 = ((1 << nFracStopX) - 1) & -(1 << nFracStartX);
      if ( (*(unsigned int *)((char *)CubeOcclusion_abFrameBuffer + v5) & v6) != v6 )
        break;
      v5 += 8;
      if ( v5 >= nMaxScanOffs )
        return isVisible;
    }
    return 1;
  }
  else
  {
    if ( nBufferStartX == nBufferStopX - 4 )
    {
      v7 = nBufferStartX + nScanOffs;
      while ( (*(unsigned int *)((char *)CubeOcclusion_abFrameBuffer + v7) & -(1 << nFracStartX)) == -(1 << nFracStartX)
           && (*(unsigned int *)((char *)&CubeOcclusion_abFrameBuffer[1] + v7) & ((1 << nFracStopX) - 1)) == (1 << nFracStopX) - 1 )
      {
        v7 += 8;
        if ( v7 >= nMaxScanOffs )
          return isVisible;
      }
    }
    else
    {
      v8 = 8 * nMinYa;
      while ( 1 )
      {
        v9 = v8 + nBufferStartX;
        v10 = v8 + nBufferStopX;
        if ( (CubeOcclusion_abFrameBuffer[v8 / 4u] & -(1 << nFracStartX)) != -(1 << nFracStartX)
          || (*(unsigned int *)((char *)CubeOcclusion_abFrameBuffer + v10) & ((1 << nFracStopX) - 1)) != (1 << nFracStopX) - 1 )
        {
          break;
        }
        if ( v10 - v9 >= 8 )
        {
          v11 = v9 + 4;
          while ( *(unsigned int *)((char *)CubeOcclusion_abFrameBuffer + v11) == -1 )
          {
            v11 += 4;
            if ( v11 >= v10 )
              goto LABEL_30;
          }
          return 1;
        }
LABEL_30:
        v8 += 8;
        if ( v8 >= nMaxScanOffs )
          return isVisible;
      }
    }
    return 1;
  }
}

// source: e/2/cubeocclusion.c:786  [anchor-mhash]
char __cdecl CubeOcclusion_CheckCube(
        unsigned __int8 bSolidEdge,
        unsigned __int8 bDrawnEdg,
        struct real64x3_t *ptRotatedPos,
        int nLevel,
        unsigned __int8 bOrientation,
        char isDrawBackfac)
{
  unsigned __int8 v6; // bl
  double v7; // st7
  int v8; // eax
  unsigned int v9; // edx
  char result; // al
  char v11; // cl
  double v12; // st7
  int v13; // ecx
  int v14; // esi
  double *v15; // edx
  int i; // esi
  double vScale; // [esp+8h] [ebp-20h]
  double v18; // [esp+10h] [ebp-18h]
  double tScreenPos_8; // [esp+20h] [ebp-8h]

  v6 = CubeOcclusion_aabEdgeMaskMapInverse[bOrientation][bSolidEdge];
  vScale = (double)(0x40000000 >> nLevel) * 9.313225746154785e-10;
  if ( nLevel < 10 )
    v6 &= 0x2Fu;
  if ( ptRotatedPos->vZ <= 4.0 )
    return 1;
  v7 = 1.0 / ptRotatedPos->vZ;
  v8 = (__int64)(CubeOcclusion_vScreenFOVX * ptRotatedPos->vX * v7 + CubeOcclusion_vScreenOriginX);
  v9 = (__int64)(CubeOcclusion_vScreenFOVY * ptRotatedPos->vY * v7 + CubeOcclusion_vScreenOriginY);
  if ( (unsigned int)v8 >= 0x40
    || v9 >= 0x30
    || ((1 << (v8 & 0x1F)) & CubeOcclusion_abFrameBuffer[2 * v9 + (v8 >> 5)]) != 0 )
  {
    v11 = 0;
  }
  else
  {
    if ( !v6 )
      return 1;
    v11 = 1;
  }
  v12 = v7 * vScale;
  if ( v11
    || (result = CubeOcclusion_CheckRectangle(
                   v8 - (__int64)(CubeOcclusion_vVertexMaxX * v12),
                   (__int64)(CubeOcclusion_vVertexMaxX * v12) + v8,
                   v9 - (__int64)(CubeOcclusion_vVertexMaxY * v12),
                   (__int64)(CubeOcclusion_vVertexMaxY * v12) + v9)) != 0 )
  {
    result = 1;
    if ( v6 )
    {
      v13 = 0;
      v14 = CubeOcclusion_abEnableVertex[v6];
      v15 = nullptr;
      do
      {
        if ( ((1 << v13) & v14) != 0 )
        {
          v15[17620656] = vScale * v15[17454468] + ptRotatedPos->vX;
          v15[17620657] = vScale * v15[17454469] + ptRotatedPos->vY;
          v18 = vScale * v15[17454470] + ptRotatedPos->vZ;
          v15[17620658] = v18;
          if ( v18 <= 0.0 )
            return 1;
          tScreenPos_8 = CubeOcclusion_vScreenFOVY * v15[17620657] * (1.0 / v18) + CubeOcclusion_vScreenOriginY;
          CubeOcclusion_atScreenPos[v13].nX = (__int64)(CubeOcclusion_vScreenFOVX * v15[17620656] * (1.0 / v18)
                                                      + CubeOcclusion_vScreenOriginX);
          CubeOcclusion_atScreenPos[v13].nY = (__int64)tScreenPos_8;
        }
        ++v13;
        v15 += 3;
      }
      while ( v13 < 8 );
      for ( i = 0; i < 6; ++i )
      {
        if ( ((1 << i) & v6) != 0 )
          CubeOcclusion_DrawRectangle(
            CubeOcclusion_aaiFaceTable[i][0],
            CubeOcclusion_aaiFaceTable[i][1],
            CubeOcclusion_aaiFaceTable[i][2],
            CubeOcclusion_aaiFaceTable[i][3]);
      }
      return 1;
    }
  }
  return result;
}

// source: e/2/cubeocclusion.c:925  [anchor-mhash]
void __cdecl CubeOcclusion_DrawTriangle(
        struct real64x2_t *ptVertex0,
        struct real64x2_t *ptVertex1,
        struct real64x2_t *ptVertex2)
{
  double vY; // st7
  struct real64x2_t *v5; // ecx
  struct real64x2_t *v6; // esi
  struct real64x2_t *v7; // ebp
  int v8; // edx
  int v9; // esi
  int v10; // edi
  int v11; // edx
  int v12; // edi
  double v13; // st7
  double v14; // st6
  double v15; // st6
  double v16; // st5
  int v17; // ebx
  double v18; // st6
  double v19; // st5
  int v20; // ebp
  int v21; // edi
  int v22; // eax
  int v23; // edx
  int v24; // edi
  int v25; // ebp
  bool v26; // zf
  double v27; // st6
  int v28; // edx
  int v29; // ecx
  double v30; // st4
  int v31; // ebx
  double v32; // st5
  int v33; // ebp
  int v34; // edi
  int v35; // eax
  int v36; // edx
  int v37; // edi
  int v38; // ebp
  int v39; // esi
  double v40; // st6
  double v41; // st5
  int v42; // ebx
  double v43; // st6
  double v44; // st5
  int v45; // ebp
  int v46; // edi
  int v47; // eax
  int v48; // edx
  int v49; // edi
  int v50; // ebp
  int v51; // edx
  int v52; // ecx
  double v53; // st4
  int v54; // ebx
  double v55; // st5
  int v56; // ebp
  int v57; // edi
  int v58; // eax
  int v59; // edx
  int v60; // edi
  int v61; // ebp
  struct real64x2_t *ptBtmVertex; // [esp+10h] [ebp-24h]
  struct real64x2_t *ptMidVertex; // [esp+14h] [ebp-20h]
  int nMidY; // [esp+18h] [ebp-1Ch]
  int v65; // [esp+1Ch] [ebp-18h]
  int v66; // [esp+1Ch] [ebp-18h]
  int v67; // [esp+1Ch] [ebp-18h]
  int nBtmY; // [esp+20h] [ebp-14h]
  int nBtmYa; // [esp+20h] [ebp-14h]
  int nBtmYb; // [esp+20h] [ebp-14h]
  double vIPStep0; // [esp+2Ch] [ebp-8h]
  double vIPStep0a; // [esp+2Ch] [ebp-8h]
  double vIPStep0b; // [esp+2Ch] [ebp-8h]
  double vIPStep0c; // [esp+2Ch] [ebp-8h]

  vY = ptVertex1->vY;
  v5 = ptVertex0;
  if ( vY < ptVertex0->vY )
    v5 = ptVertex1;
  if ( ptVertex2->vY < v5->vY )
    v5 = ptVertex2;
  v6 = ptVertex0;
  ptBtmVertex = ptVertex0;
  if ( ptVertex1->vY > ptVertex0->vY )
  {
    ptBtmVertex = ptVertex1;
    v6 = ptVertex1;
  }
  if ( ptVertex2->vY > v6->vY )
  {
    ptBtmVertex = ptVertex2;
    v6 = ptVertex2;
  }
  v7 = ptVertex0;
  ptMidVertex = ptVertex0;
  if ( ptVertex0 == v5 || ptVertex0 == v6 )
  {
    v7 = ptVertex1;
    ptMidVertex = ptVertex1;
  }
  if ( v7 == v5 || v7 == v6 )
  {
    v7 = ptVertex2;
    ptMidVertex = ptVertex2;
  }
  v8 = (__int64)v5->vY;
  v9 = (__int64)v7->vY;
  nMidY = v9;
  v10 = (__int64)ptBtmVertex->vY;
  nBtmY = v10;
  if ( !v8 && v5->vY < 0.0 )
    v8 = -1;
  if ( !v9 && v7->vY < 0.0 )
  {
    v9 = -1;
    nMidY = -1;
  }
  if ( !v10 && ptBtmVertex->vY < 0.0 )
  {
    v10 = -1;
    nBtmY = -1;
  }
  if ( v10 > v8 )
  {
    v11 = v8 + 1;
    v12 = v9;
    v65 = v11;
    v13 = 1.0 / (ptBtmVertex->vY - v5->vY) * (ptBtmVertex->vX - v5->vX);
    v14 = v7->vY - v5->vY;
    if ( v14 * v13 + v5->vX <= v7->vX )
    {
      if ( v11 < 0 )
        v11 = 0;
      if ( v9 >= 48 )
        v12 = 47;
      if ( v12 - v11 < 0 )
      {
        if ( v5->vY >= 0.0 )
          v43 = ((double)(v9 + 1) - v5->vY) * v13 + v5->vX;
        else
          v43 = -v5->vY * v13 + v5->vX;
      }
      else
      {
        v40 = 1.0 / v14;
        if ( v5->vY >= 0.0 )
          v41 = (double)v65 - v5->vY;
        else
          v41 = -v5->vY;
        v42 = 2 * v11;
        vIPStep0b = (ptMidVertex->vX - v5->vX) * v40;
        v43 = v41 * v13 + v5->vX;
        v44 = vIPStep0b * v41 + v5->vX;
        if ( v11 <= v12 )
        {
          v67 = v12 - v11 + 1;
          do
          {
            v45 = (__int64)v44;
            v46 = (int)(__int64)v43 <= 0 ? 0 : (__int64)v43;
            if ( v45 >= 64 )
              v45 = 64;
            if ( v46 <= v45 )
            {
              v47 = v46 >> 5;
              v48 = v45 >> 5;
              v49 = v46 - 32 * (v46 >> 5);
              v50 = v45 - 32 * (v45 >> 5);
              if ( v47 == v48 )
              {
                CubeOcclusion_abFrameBuffer[v42 + v47] |= (-1 << v49) & ((1 << v50) - 1);
              }
              else if ( v47 + 1 == v48 )
              {
                CubeOcclusion_abFrameBuffer[v42 + v47] |= -1 << v49;
                CubeOcclusion_abFrameBuffer[v42 + v48] |= (1 << v50) - 1;
              }
              else
              {
                CubeOcclusion_abFrameBuffer[v47 + v42] |= -1 << v49;
                CubeOcclusion_abFrameBuffer[v48 + v42] |= (1 << v50) - 1;
                if ( v47 + v42 + 1 < v48 + v42 )
                  memset((void *)(4 * (v47 + v42 + 1) + 133164704), 0xFFu, 4 * (v48 - (v47 + 1)));
              }
            }
            v42 += 2;
            v43 = v43 + v13;
            v26 = v67 == 1;
            v44 = v44 + vIPStep0b;
            --v67;
          }
          while ( !v26 );
          v9 = nMidY;
        }
      }
      v51 = nBtmY;
      v52 = v9 + 1;
      if ( v9 + 1 < 0 )
        v52 = 0;
      if ( nBtmY >= 48 )
        v51 = 47;
      if ( v51 - v52 >= 0 )
      {
        v53 = ptMidVertex->vY >= 0.0 ? (double)(v9 + 1) - ptMidVertex->vY : -ptMidVertex->vY;
        v54 = 2 * v52;
        vIPStep0c = (ptBtmVertex->vX - ptMidVertex->vX) * (1.0 / (ptBtmVertex->vY - ptMidVertex->vY));
        v55 = vIPStep0c * v53 + ptMidVertex->vX;
        if ( v52 <= v51 )
        {
          nBtmYb = v51 - v52 + 1;
          do
          {
            v56 = (__int64)v55;
            v57 = (int)(__int64)v43 <= 0 ? 0 : (__int64)v43;
            if ( v56 >= 64 )
              v56 = 64;
            if ( v57 <= v56 )
            {
              v58 = v57 >> 5;
              v59 = v56 >> 5;
              v60 = v57 - 32 * (v57 >> 5);
              v61 = v56 - 32 * (v56 >> 5);
              if ( v58 == v59 )
              {
                CubeOcclusion_abFrameBuffer[v54 + v58] |= (-1 << v60) & ((1 << v61) - 1);
              }
              else if ( v58 + 1 == v59 )
              {
                CubeOcclusion_abFrameBuffer[v54 + v58] |= -1 << v60;
                CubeOcclusion_abFrameBuffer[v54 + v59] |= (1 << v61) - 1;
              }
              else
              {
                CubeOcclusion_abFrameBuffer[v58 + v54] |= -1 << v60;
                CubeOcclusion_abFrameBuffer[v59 + v54] |= (1 << v61) - 1;
                if ( v58 + v54 + 1 < v59 + v54 )
                  memset((void *)(4 * (v58 + v54 + 1) + 133164704), 0xFFu, 4 * (v59 - (v58 + 1)));
              }
            }
            v54 += 2;
            v43 = v43 + v13;
            v26 = nBtmYb == 1;
            v55 = v55 + vIPStep0c;
            --nBtmYb;
          }
          while ( !v26 );
        }
      }
    }
    else
    {
      if ( v11 < 0 )
        v11 = 0;
      if ( v9 >= 48 )
        v12 = 47;
      if ( v12 - v11 < 0 )
      {
        if ( v5->vY >= 0.0 )
          v27 = (double)(v9 + 1) - v5->vY;
        else
          v27 = -v5->vY;
        v18 = v27 * v13 + v5->vX;
      }
      else
      {
        v15 = 1.0 / v14;
        if ( v5->vY >= 0.0 )
          v16 = (double)v65 - v5->vY;
        else
          v16 = -v5->vY;
        v17 = 2 * v11;
        vIPStep0 = (ptMidVertex->vX - v5->vX) * v15;
        v18 = v16 * v13 + v5->vX;
        if ( v11 <= v12 )
        {
          v19 = vIPStep0 * v16 + v5->vX;
          v66 = v12 - v11 + 1;
          do
          {
            v20 = (__int64)v18;
            v21 = (int)(__int64)v19 <= 0 ? 0 : (__int64)v19;
            if ( v20 >= 64 )
              v20 = 64;
            if ( v21 <= v20 )
            {
              v22 = v21 >> 5;
              v23 = v20 >> 5;
              v24 = v21 - 32 * (v21 >> 5);
              v25 = v20 - 32 * (v20 >> 5);
              if ( v22 == v23 )
              {
                CubeOcclusion_abFrameBuffer[v17 + v22] |= (-1 << v24) & ((1 << v25) - 1);
              }
              else if ( v22 + 1 == v23 )
              {
                CubeOcclusion_abFrameBuffer[v17 + v22] |= -1 << v24;
                CubeOcclusion_abFrameBuffer[v17 + v23] |= (1 << v25) - 1;
              }
              else
              {
                CubeOcclusion_abFrameBuffer[v22 + v17] |= -1 << v24;
                CubeOcclusion_abFrameBuffer[v23 + v17] |= (1 << v25) - 1;
                if ( v22 + v17 + 1 < v23 + v17 )
                  memset((void *)(4 * (v22 + v17 + 1) + 133164704), 0xFFu, 4 * (v23 - (v22 + 1)));
                v9 = nMidY;
              }
            }
            v17 += 2;
            v26 = v66 == 1;
            v19 = v19 + vIPStep0;
            v18 = v18 + v13;
            --v66;
          }
          while ( !v26 );
        }
      }
      v28 = nBtmY;
      v29 = v9 + 1;
      if ( v9 + 1 < 0 )
        v29 = 0;
      if ( nBtmY >= 48 )
        v28 = 47;
      if ( v28 - v29 >= 0 )
      {
        v30 = ptMidVertex->vY >= 0.0 ? (double)(v9 + 1) - ptMidVertex->vY : -ptMidVertex->vY;
        v31 = 2 * v29;
        vIPStep0a = (ptBtmVertex->vX - ptMidVertex->vX) * (1.0 / (ptBtmVertex->vY - ptMidVertex->vY));
        v32 = vIPStep0a * v30 + ptMidVertex->vX;
        if ( v29 <= v28 )
        {
          nBtmYa = v28 - v29 + 1;
          do
          {
            v33 = (__int64)v18;
            v34 = (int)(__int64)v32 <= 0 ? 0 : (__int64)v32;
            if ( v33 >= 64 )
              v33 = 64;
            if ( v34 <= v33 )
            {
              v35 = v34 >> 5;
              v36 = v33 >> 5;
              v37 = v34 - 32 * (v34 >> 5);
              v38 = v33 - 32 * (v33 >> 5);
              if ( v35 == v36 )
              {
                CubeOcclusion_abFrameBuffer[v31 + v35] |= (-1 << v37) & ((1 << v38) - 1);
              }
              else if ( v35 + 1 == v36 )
              {
                CubeOcclusion_abFrameBuffer[v31 + v35] |= -1 << v37;
                CubeOcclusion_abFrameBuffer[v31 + v36] |= (1 << v38) - 1;
              }
              else
              {
                CubeOcclusion_abFrameBuffer[v35 + v31] |= -1 << v37;
                v39 = v35 + v31 + 1;
                CubeOcclusion_abFrameBuffer[v36 + v31] |= (1 << v38) - 1;
                if ( v39 < v36 + v31 )
                  memset((void *)(4 * v39 + 133164704), 0xFFu, 4 * (v36 - (v35 + 1)));
              }
            }
            v31 += 2;
            v26 = nBtmYa == 1;
            v32 = v32 + vIPStep0a;
            v18 = v18 + v13;
            --nBtmYa;
          }
          while ( !v26 );
        }
      }
    }
  }
}
