/* e/2/discard2d.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: e/2/discard2d.c:44  [anchor-callee]
enum bool __cdecl Real32x2_IsLineIntersection(
        struct real32x2_t *ptIntersection,
        struct real32x2_t *ptLine1Start,
        struct real32x2_t *ptLine1End,
        struct real32x2_t *ptLine2Start,
        struct real32x2_t *ptLine2End)
{
  struct real32x2_t *v5; // esi
  enum bool v6; // ebp
  struct real32x2_t *v7; // edx
  double v8; // st7
  double v9; // st7
  float vS; // [esp+8h] [ebp-20h]
  float vSa; // [esp+8h] [ebp-20h]
  float vPdX; // [esp+Ch] [ebp-1Ch]
  float tU; // [esp+10h] [ebp-18h]
  float tU_4; // [esp+14h] [ebp-14h]
  float tV; // [esp+20h] [ebp-8h]
  struct real32x2_t tIntersection; // 0:^18.8

  v5 = ptLine1End;
  v6 = false;
  tIntersection.vX = 0.0;
  tIntersection.vY = 0.0;
  if ( ptLine1End->vX - ptLine1Start->vX == 0.0 )
  {
    v7 = ptLine1Start;
    ptLine1Start = ptLine2Start;
    v5 = ptLine2End;
  }
  else
  {
    v7 = ptLine2Start;
    ptLine1End = ptLine2End;
  }
  tU = v5->vX - ptLine1Start->vX;
  tU_4 = v5->vY - ptLine1Start->vY;
  tV = ptLine1End->vX - v7->vX;
  vPdX = ptLine1Start->vX - v7->vX;
  v8 = tV * tU_4 - (ptLine1End->vY - v7->vY) * tU;
  if ( v8 != 0.0 )
  {
    vS = ((v7->vY - ptLine1Start->vY) * tU + vPdX * tU_4) / v8;
    if ( vS >= 0.0 && vS < 1.0 )
    {
      v9 = (vS * tV - vPdX) / tU;
      vSa = v9;
      if ( v9 >= 0.0 && vSa < 1.0 )
      {
        v6 = true;
        tIntersection.vX = vSa * tU + ptLine1Start->vX;
        tIntersection.vY = vSa * tU_4 + ptLine1Start->vY;
      }
    }
  }
  if ( ptIntersection )
    *ptIntersection = tIntersection;
  return v6;
}

// source: e/2/discard2d.c:256  [anchor-mhash]
int __cdecl Discard2D_Vertex2DQSortCompare(void *pxVertex1, void *pxVertex2)
{
  int result; // eax

  result = (__int64)(*(float *)pxVertex1 - *(float *)pxVertex2);
  if ( !result )
    return (__int64)(*((float *)pxVertex1 + 1) - *((float *)pxVertex2 + 1));
  return result;
}

// source: e/2/discard2d.c:277  [anchor-mhash]
struct DiscardMeshContext_s *__cdecl Discard2D_AddEdge(
        struct DiscardMeshContext_s *ptDiscardMeshContext,
        int iVertex1,
        int iVertex2)
{
  int v3; // esi

  v3 = iVertex1;
  if ( iVertex1 >= iVertex2 )
    v3 = iVertex2;
  ptDiscardMeshContext->atEdge[ptDiscardMeshContext->nEdges].aiVertex[0] = v3;
  if ( iVertex1 > iVertex2 )
    iVertex2 = iVertex1;
  ptDiscardMeshContext->atEdge[ptDiscardMeshContext->nEdges++].aiVertex[1] = iVertex2;
  return ptDiscardMeshContext;
}

// source: e/2/discard2d.c:294  [anchor-mhash]
enum bool __cdecl Discard2D_TriangleExists(
        int *piTriangle,
        struct DiscardMeshContext_s *ptDiscardMeshContext,
        int iVertex1,
        int iVertex2,
        int iVertex3)
{
  int nDrawTriangles; // esi
  int v6; // edx
  int *i; // eax
  int v8; // ecx

  nDrawTriangles = ptDiscardMeshContext->nDrawTriangles;
  v6 = 0;
  if ( nDrawTriangles <= 0 )
    return false;
  for ( i = &ptDiscardMeshContext->atDrawTriangle[0].aiVertex[1]; ; i += 3 )
  {
    v8 = *(i - 1);
    if ( (v8 == iVertex1 || *i == iVertex1 || i[1] == iVertex1)
      && (v8 == iVertex2 || *i == iVertex2 || i[1] == iVertex2)
      && (v8 == iVertex3 || *i == iVertex3 || i[1] == iVertex3) )
    {
      break;
    }
    if ( ++v6 >= nDrawTriangles )
      return false;
  }
  if ( piTriangle )
    *piTriangle = v6;
  return true;
}

// source: e/2/discard2d.c:323  [anchor-mhash]
void __cdecl Discard2D_AddTriangle(
        struct DiscardMeshContext_s *ptDiscardMeshContext,
        int iVertex1,
        int iVertex2,
        int iVertex3)
{
  double vX; // st7
  double vY; // st6
  float *v6; // eax
  float tVector2; // [esp+4h] [ebp-18h]
  float tVector1; // [esp+10h] [ebp-Ch]
  float tVector1_4; // [esp+14h] [ebp-8h]

  vX = ptDiscardMeshContext->atVertex[iVertex1].tPos.vX;
  vY = ptDiscardMeshContext->atVertex[iVertex1].tPos.vY;
  v6 = (float *)((char *)ptDiscardMeshContext + 12 * iVertex3);
  tVector1 = ptDiscardMeshContext->atVertex[iVertex2].tPos.vX - vX;
  tVector1_4 = ptDiscardMeshContext->atVertex[iVertex2].tPos.vY - vY;
  tVector2 = v6[1000] - vX;
  if ( (v6[1001] - vY) * tVector1 - tVector2 * tVector1_4 <= 0.0 )
  {
    ptDiscardMeshContext->atDrawTriangle[ptDiscardMeshContext->nDrawTriangles].aiVertex[0] = iVertex3;
    ptDiscardMeshContext->atDrawTriangle[ptDiscardMeshContext->nDrawTriangles].aiVertex[1] = iVertex2;
    ptDiscardMeshContext->atDrawTriangle[ptDiscardMeshContext->nDrawTriangles].aiVertex[2] = iVertex1;
  }
  else
  {
    ptDiscardMeshContext->atDrawTriangle[ptDiscardMeshContext->nDrawTriangles].aiVertex[0] = iVertex1;
    ptDiscardMeshContext->atDrawTriangle[ptDiscardMeshContext->nDrawTriangles].aiVertex[1] = iVertex2;
    ptDiscardMeshContext->atDrawTriangle[ptDiscardMeshContext->nDrawTriangles].aiVertex[2] = iVertex3;
  }
  ++ptDiscardMeshContext->nDrawTriangles;
}

// source: e/2/discard2d.c:361  [anchor-mhash]
struct DiscardMeshContext_s *__cdecl Discard2D_RemoveTriangle(
        struct DiscardMeshContext_s *ptDiscardMeshContext,
        int iTriangle)
{
  struct DiscardTriangle2D_s *v2; // ecx
  struct DiscardTriangle2D_s *v3; // edx

  v2 = &ptDiscardMeshContext->atDiscardTriangle[ptDiscardMeshContext->nDrawTriangles + 99];
  v3 = &ptDiscardMeshContext->atDrawTriangle[iTriangle];
  v3->aiVertex[0] = v2->aiVertex[0];
  v3->aiVertex[1] = v2->aiVertex[1];
  v3->aiVertex[2] = v2->aiVertex[2];
  --ptDiscardMeshContext->nDrawTriangles;
  return ptDiscardMeshContext;
}

// source: e/2/discard2d.c:377  [anchor-mhash]
int __cdecl Discard2D_GetVertex(struct DiscardMeshContext_s *ptDiscardMeshContext, int iVertexID)
{
  int nVertices; // ecx
  int result; // eax
  int *i; // edx

  nVertices = ptDiscardMeshContext->nVertices;
  result = 0;
  if ( nVertices <= 0 )
    return 0;
  for ( i = &ptDiscardMeshContext->atVertex[0].iID; *i != iVertexID; i += 3 )
  {
    if ( ++result >= nVertices )
      return 0;
  }
  return result;
}

// source: e/2/discard2d.c:401  [anchor-mhash]
enum bool __cdecl Discard2D_VertexExists(
        int *piVertex,
        struct DiscardMeshContext_s *ptDiscardMeshContext,
        float vX,
        float vY)
{
  int nVertices; // edx
  int v5; // ecx
  float *i; // esi

  nVertices = ptDiscardMeshContext->nVertices;
  v5 = 0;
  if ( nVertices <= 0 )
    return false;
  for ( i = &ptDiscardMeshContext->atVertex[0].tPos.vY; *(i - 1) != vX || *i != vY; i += 3 )
  {
    if ( ++v5 >= nVertices )
      return false;
  }
  if ( piVertex )
    *piVertex = v5;
  return true;
}

// source: e/2/discard2d.c:428  [anchor-mhash]
int __cdecl Discard2D_AddVertex(struct DiscardMeshContext_s *ptDiscardMeshContext, float vX, float vY)
{
  int v3; // ecx

  ptDiscardMeshContext->atVertex[ptDiscardMeshContext->nVertices].tPos.vX = vX;
  ptDiscardMeshContext->atVertex[ptDiscardMeshContext->nVertices].tPos.vY = vY;
  ptDiscardMeshContext->atVertex[ptDiscardMeshContext->nVertices].iID = ptDiscardMeshContext->nVertices;
  v3 = ptDiscardMeshContext->nVertices + 1;
  ptDiscardMeshContext->nVertices = v3;
  return ptDiscardMeshContext->atEdge[499].aiVertex[3 * v3 + 1];
}

// source: e/2/discard2d.c:446  [anchor-mhash]
enum bool __cdecl Discard2D_EdgeExists(
        int *piEdge,
        struct DiscardMeshContext_s *ptDiscardMeshContext,
        int iVertex1,
        int iVertex2)
{
  int nEdges; // edi
  int v5; // eax
  int v6; // edx

  nEdges = ptDiscardMeshContext->nEdges;
  v5 = 0;
  if ( nEdges <= 0 )
    return false;
  while ( 1 )
  {
    v6 = ptDiscardMeshContext->atEdge[v5].aiVertex[0];
    if ( (v6 == iVertex1 || ptDiscardMeshContext->atEdge[v5].aiVertex[1] == iVertex1)
      && (v6 == iVertex2 || ptDiscardMeshContext->atEdge[v5].aiVertex[1] == iVertex2) )
    {
      break;
    }
    if ( ++v5 >= nEdges )
      return false;
  }
  if ( piEdge )
    *piEdge = v5;
  return true;
}

// source: e/2/discard2d.c:474  [anchor-callee]
enum bool __cdecl Discard2D_IsEdgeCollide(
        struct DiscardMeshContext_s *ptDiscardMeshContext,
        int iVertex1,
        int iVertex2)
{
  int nEdges; // ebx
  int j; // eax
  int v5; // ecx
  int v6; // edi
  int v7; // ecx
  int v8; // eax
  int i; // [esp+8h] [ebp-4h]

  nEdges = ptDiscardMeshContext->nEdges;
  for ( j = 0; j < nEdges; ++j )
  {
    v5 = ptDiscardMeshContext->atEdge[j].aiVertex[0];
    if ( (v5 == iVertex1 || ptDiscardMeshContext->atEdge[j].aiVertex[1] == iVertex1)
      && (v5 == iVertex2 || ptDiscardMeshContext->atEdge[j].aiVertex[1] == iVertex2) )
    {
      return true;
    }
  }
  v6 = 0;
  i = 0;
  if ( nEdges <= 0 )
    return false;
  while ( 1 )
  {
    v7 = ptDiscardMeshContext->atEdge[v6].aiVertex[0];
    if ( iVertex1 == v7 )
      goto LABEL_14;
    v8 = ptDiscardMeshContext->atEdge[v6].aiVertex[1];
    if ( iVertex1 == v8 || iVertex2 == v7 || iVertex2 == v8 )
      goto LABEL_14;
    if ( Real32x2_IsLineIntersection(
           nullptr,
           &ptDiscardMeshContext->atVertex[iVertex1].tPos,
           &ptDiscardMeshContext->atVertex[iVertex2].tPos,
           &ptDiscardMeshContext->atVertex[v7].tPos,
           &ptDiscardMeshContext->atVertex[v8].tPos) )
    {
      return true;
    }
    v6 = i;
LABEL_14:
    i = ++v6;
    if ( v6 >= ptDiscardMeshContext->nEdges )
      return false;
  }
}

// source: e/2/discard2d.c:510  [anchor-mhash]
struct DiscardMeshContext_s *__cdecl Discard2D_AddEdgeVertexID(
        struct DiscardMeshContext_s *ptDiscardMeshContext,
        int iID1,
        int iID2)
{
  int nVertices; // ebx
  int v4; // ecx
  int *p_iID; // edx
  int v6; // edi
  int v7; // ecx
  int *v8; // edx
  int v9; // esi
  int nEdges; // ebp
  int v11; // ecx
  int v12; // edx
  int v13; // ecx
  int *v14; // edx
  int v15; // esi
  int v16; // ecx
  int *v17; // edx
  int v18; // edx

  nVertices = ptDiscardMeshContext->nVertices;
  v4 = 0;
  if ( nVertices <= 0 )
  {
LABEL_5:
    v6 = 0;
  }
  else
  {
    p_iID = &ptDiscardMeshContext->atVertex[0].iID;
    while ( *p_iID != iID2 )
    {
      ++v4;
      p_iID += 3;
      if ( v4 >= ptDiscardMeshContext->nVertices )
        goto LABEL_5;
    }
    v6 = v4;
  }
  v7 = 0;
  if ( nVertices <= 0 )
  {
LABEL_10:
    v9 = 0;
  }
  else
  {
    v8 = &ptDiscardMeshContext->atVertex[0].iID;
    while ( *v8 != iID1 )
    {
      ++v7;
      v8 += 3;
      if ( v7 >= ptDiscardMeshContext->nVertices )
        goto LABEL_10;
    }
    v9 = v7;
  }
  nEdges = ptDiscardMeshContext->nEdges;
  v11 = 0;
  if ( nEdges <= 0 )
  {
LABEL_17:
    v13 = 0;
    if ( nVertices <= 0 )
    {
LABEL_21:
      v15 = 0;
    }
    else
    {
      v14 = &ptDiscardMeshContext->atVertex[0].iID;
      while ( *v14 != iID2 )
      {
        ++v13;
        v14 += 3;
        if ( v13 >= ptDiscardMeshContext->nVertices )
          goto LABEL_21;
      }
      v15 = v13;
    }
    v16 = 0;
    if ( nVertices <= 0 )
    {
LABEL_26:
      v16 = 0;
    }
    else
    {
      v17 = &ptDiscardMeshContext->atVertex[0].iID;
      while ( *v17 != iID1 )
      {
        ++v16;
        v17 += 3;
        if ( v16 >= ptDiscardMeshContext->nVertices )
          goto LABEL_26;
      }
    }
    v18 = v16;
    if ( v16 >= v15 )
      v18 = v15;
    ptDiscardMeshContext->atEdge[nEdges].aiVertex[0] = v18;
    if ( v16 <= v15 )
      v16 = v15;
    ptDiscardMeshContext->atEdge[ptDiscardMeshContext->nEdges++].aiVertex[1] = v16;
  }
  else
  {
    while ( 1 )
    {
      v12 = ptDiscardMeshContext->atEdge[v11].aiVertex[0];
      if ( (v12 == v9 || ptDiscardMeshContext->atEdge[v11].aiVertex[1] == v9)
        && (v12 == v6 || ptDiscardMeshContext->atEdge[v11].aiVertex[1] == v6) )
      {
        break;
      }
      if ( ++v11 >= ptDiscardMeshContext->nEdges )
        goto LABEL_17;
    }
  }
  return ptDiscardMeshContext;
}

// source: e/2/discard2d.c:526  [anchor-hash]
struct DiscardMeshContext_s *__cdecl Discard2D_TriangulateSet(
        struct DiscardMeshContext_s *ptDiscardMeshContext)
{
  int v2; // ebx
  struct DiscardMeshContext_s *result; // eax
  int v4; // ebp
  int i; // edi
  int v6; // eax
  int v7; // eax

  v2 = 0;
  result = (struct DiscardMeshContext_s *)(ptDiscardMeshContext->nVertices - 1);
  if ( (int)result > 0 )
  {
    do
    {
      v4 = v2 + 1;
      for ( i = v2 + 1; i < ptDiscardMeshContext->nVertices; ++i )
      {
        if ( Discard2D_IsEdgeCollide(ptDiscardMeshContext, v2, i) == false )
        {
          v6 = v2;
          if ( v2 >= i )
            v6 = i;
          ptDiscardMeshContext->atEdge[ptDiscardMeshContext->nEdges].aiVertex[0] = v6;
          v7 = v2;
          if ( v2 <= i )
            v7 = i;
          ptDiscardMeshContext->atEdge[ptDiscardMeshContext->nEdges++].aiVertex[1] = v7;
        }
      }
      ++v2;
      result = (struct DiscardMeshContext_s *)(ptDiscardMeshContext->nVertices - 1);
    }
    while ( v4 < (int)result );
  }
  return result;
}

// source: e/2/discard2d.c:554  [anchor-mhash]
float __cdecl Discard2D_GetEdgeAngle(
        struct DiscardMeshContext_s *ptDiscardMeshContext,
        int iEdge1,
        int iEdge2)
{
  int v3; // ecx
  bool v4; // zf
  int v5; // ecx
  float *v6; // edx
  float *v7; // ecx

  v3 = ptDiscardMeshContext->atEdge[iEdge1].aiVertex[0];
  v4 = v3 == ptDiscardMeshContext->atEdge[iEdge2].aiVertex[0];
  v5 = 3 * v3;
  if ( v4 )
  {
    v6 = (float *)((char *)ptDiscardMeshContext + 12 * ptDiscardMeshContext->atEdge[iEdge1].aiVertex[1]);
  }
  else
  {
    v6 = (float *)((char *)ptDiscardMeshContext + 4 * v5);
    v5 = 3 * ptDiscardMeshContext->atEdge[iEdge1].aiVertex[1];
  }
  v7 = (float *)((char *)ptDiscardMeshContext + 4 * v5);
  return atan2(
           ptDiscardMeshContext->atVertex[ptDiscardMeshContext->atEdge[iEdge2].aiVertex[1]].tPos.vX - v7[1000],
           ptDiscardMeshContext->atVertex[ptDiscardMeshContext->atEdge[iEdge2].aiVertex[1]].tPos.vY - v7[1001])
       - atan2(v6[1000] - v7[1000], v6[1001] - v7[1001]);
}

// source: e/2/discard2d.c:589  [anchor-mhash]
void __cdecl Discard2D_GenerateTriangleSet(struct DiscardMeshContext_s *ptDiscardMeshContext)
{
  int v2; // edx
  int v3; // edi
  int v4; // ebx
  double v5; // st7
  int v6; // eax
  int nEdges; // ebx
  int v8; // esi
  int v9; // eax
  int v10; // ecx
  int v11; // edi
  int v12; // ebx
  int iEdge1; // [esp+4h] [ebp-10h]
  int nSign; // [esp+8h] [ebp-Ch]
  float vSmallestAngle; // [esp+Ch] [ebp-8h]
  int iVertex; // [esp+10h] [ebp-4h]
  struct DiscardMeshContext_s *ptDiscardMeshContexta = *(struct DiscardMeshContext_s * *)&ptDiscardMeshContext; // [esp+18h] [ebp+4h] ARGSLOT

  if ( ptDiscardMeshContext->nEdges >= 3 )
  {
    nSign = -1;
    do
    {
      v2 = 0;
      for ( ptDiscardMeshContexta = nullptr;
            v2 < ptDiscardMeshContext->nEdges;
            ptDiscardMeshContexta = (struct DiscardMeshContext_s *)v2 )
      {
        v3 = 0;
        iEdge1 = -1;
        vSmallestAngle = 100.0;
        if ( ptDiscardMeshContext->nEdges > 0 )
        {
          do
          {
            if ( v3 != v2 )
            {
              v4 = ptDiscardMeshContext->atEdge[v2].aiVertex[0];
              if ( ptDiscardMeshContext->atEdge[v3].aiVertex[0] == v4
                || ptDiscardMeshContext->atEdge[v3].aiVertex[1] == v4 )
              {
                v5 = Discard2D_GetEdgeAngle(ptDiscardMeshContext, v3, v2) * (double)nSign;
                if ( v5 >= 0.0 && v5 < vSmallestAngle )
                {
                  v6 = ptDiscardMeshContext->atEdge[v3].aiVertex[0];
                  if ( v6 == v4 )
                    v6 = ptDiscardMeshContext->atEdge[v3].aiVertex[1];
                  vSmallestAngle = v5;
                  iVertex = v6;
                  iEdge1 = v3;
                }
                v2 = (int)ptDiscardMeshContexta;
              }
            }
            nEdges = ptDiscardMeshContext->nEdges;
            ++v3;
          }
          while ( v3 < nEdges );
          if ( iEdge1 >= 0 )
          {
            v8 = ptDiscardMeshContext->atEdge[v2].aiVertex[1];
            v9 = 0;
            while ( 1 )
            {
              v10 = ptDiscardMeshContext->atEdge[v9].aiVertex[0];
              if ( (v10 == v8 || ptDiscardMeshContext->atEdge[v9].aiVertex[1] == v8)
                && (v10 == iVertex || ptDiscardMeshContext->atEdge[v9].aiVertex[1] == iVertex) )
              {
                break;
              }
              if ( ++v9 >= nEdges )
                goto LABEL_28;
            }
            v11 = ptDiscardMeshContext->atEdge[v2].aiVertex[0];
            v12 = ptDiscardMeshContext->atEdge[iEdge1].aiVertex[0];
            if ( v12 == v11 )
              v12 = ptDiscardMeshContext->atEdge[iEdge1].aiVertex[1];
            if ( Discard2D_TriangleExists(
                   nullptr,
                   ptDiscardMeshContext,
                   v11,
                   ptDiscardMeshContext->atEdge[v2].aiVertex[1],
                   v12) == false )
              Discard2D_AddTriangle(ptDiscardMeshContext, v11, v8, v12);
            v2 = (int)ptDiscardMeshContexta;
          }
        }
LABEL_28:
        ++v2;
      }
      nSign += 2;
    }
    while ( nSign < 2 );
  }
}

// source: e/2/discard2d.c:667  [anchor-mhash]
int __cdecl Discard2D_RemoveTriangleVertexID(
        struct DiscardMeshContext_s *ptDiscardMeshContext,
        int iID0,
        int iID1,
        int iID2)
{
  int nVertices; // edi
  int v6; // eax
  int *p_iID; // ecx
  int v8; // ecx
  int *v9; // edx
  int v10; // ebp
  int v11; // ecx
  int *v12; // edx
  int result; // eax
  struct DiscardTriangle2D_s *v14; // ecx
  int iTriangle; // [esp+Ch] [ebp-4h] BYREF

  nVertices = ptDiscardMeshContext->nVertices;
  v6 = 0;
  if ( nVertices <= 0 )
  {
LABEL_5:
    v6 = 0;
  }
  else
  {
    p_iID = &ptDiscardMeshContext->atVertex[0].iID;
    while ( *p_iID != iID2 )
    {
      ++v6;
      p_iID += 3;
      if ( v6 >= ptDiscardMeshContext->nVertices )
        goto LABEL_5;
    }
  }
  v8 = 0;
  if ( nVertices <= 0 )
  {
LABEL_10:
    v10 = 0;
  }
  else
  {
    v9 = &ptDiscardMeshContext->atVertex[0].iID;
    while ( *v9 != iID1 )
    {
      ++v8;
      v9 += 3;
      if ( v8 >= ptDiscardMeshContext->nVertices )
        goto LABEL_10;
    }
    v10 = v8;
  }
  v11 = 0;
  if ( nVertices <= 0 )
  {
LABEL_15:
    v11 = 0;
  }
  else
  {
    v12 = &ptDiscardMeshContext->atVertex[0].iID;
    while ( *v12 != iID0 )
    {
      ++v11;
      v12 += 3;
      if ( v11 >= ptDiscardMeshContext->nVertices )
        goto LABEL_15;
    }
  }
  result = Discard2D_TriangleExists(&iTriangle, ptDiscardMeshContext, v11, v10, v6);
  if ( result )
  {
    v14 = &ptDiscardMeshContext->atDiscardTriangle[ptDiscardMeshContext->nDrawTriangles + 99];
    result = (int)ptDiscardMeshContext->atDrawTriangle[iTriangle].aiVertex;
    *(_DWORD *)result = v14->aiVertex[0];
    *(_DWORD *)(result + 4) = v14->aiVertex[1];
    *(_DWORD *)(result + 8) = v14->aiVertex[2];
    --ptDiscardMeshContext->nDrawTriangles;
  }
  return result;
}

// source: e/2/discard2d.c:695  [anchor-mhash]
void __cdecl Discard2D_RegisterDiscardTriangle(
        struct DiscardMeshContext_s *ptDiscardMeshContext,
        float vX0,
        float vY0,
        float vX1,
        float vY1,
        float vX2,
        float vY2)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct DiscardTriangle_s *ptDiscardTriangle; };
    struct { char igi2_o1[4]; int anVertexID[3]; };
    char igi2_extent[16];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v7; // eax
  int v8; // edx

  igi2_frame.ptDiscardTriangle = &ptDiscardMeshContext->atRegisteredTriangle[ptDiscardMeshContext->nRegisteredTriangles];
  if ( Discard2D_VertexExists(igi2_frame.anVertexID, ptDiscardMeshContext, vX0, vY0) == false )
    igi2_frame.anVertexID[0] = Discard2D_AddVertex(ptDiscardMeshContext, vX0, vY0);
  if ( Discard2D_VertexExists(&igi2_frame.anVertexID[1], ptDiscardMeshContext, vX1, vY1) == false )
    igi2_frame.anVertexID[1] = Discard2D_AddVertex(ptDiscardMeshContext, vX1, vY1);
  if ( Discard2D_VertexExists(&igi2_frame.anVertexID[2], ptDiscardMeshContext, vX2, vY2) )
    v7 = igi2_frame.anVertexID[2];
  else
    v7 = Discard2D_AddVertex(ptDiscardMeshContext, vX2, vY2);
  igi2_frame.ptDiscardTriangle->anVertexID[0] = igi2_frame.anVertexID[0];
  v8 = igi2_frame.anVertexID[1];
  igi2_frame.ptDiscardTriangle->anVertexID[2] = v7;
  igi2_frame.ptDiscardTriangle->anVertexID[1] = v8;
  ++ptDiscardMeshContext->nRegisteredTriangles;
}

// source: e/2/discard2d.c:734  [anchor-mhash]
struct DiscardMeshContext_s *__cdecl Discard2D_InitDiscardMeshContext(
        struct DiscardMeshContext_s *ptDiscardMeshContext,
        struct real64x3_t *ptPos,
        float vWorldWidth,
        float vWorldHeight)
{
  double v4; // st7
  double v5; // st7
  double v6; // st6
  double v7; // st6
  double v8; // st4
  int v9; // edx
  int v10; // ecx
  int v11; // ecx
  float ptDiscardMeshContexta = *(float *)&vWorldWidth; // [esp+4h] [ebp+4h] ARGSLOT
  float ptDiscardMeshContextb = *(float *)&vWorldWidth; // [esp+4h] [ebp+4h] ARGSLOT
  float ptPosa = *(float *)&vWorldHeight; // [esp+8h] [ebp+8h] ARGSLOT
  float ptPosb = *(float *)&vWorldHeight; // [esp+8h] [ebp+8h] ARGSLOT

  v4 = vWorldWidth * 0.5;
  ptDiscardMeshContexta = v4;
  v5 = ptPos->vX - v4;
  v6 = vWorldHeight * 0.5;
  ptPosa = v6;
  v7 = ptPos->vY - v6;
  ptDiscardMeshContextb = ptDiscardMeshContexta + ptPos->vX;
  v8 = ptPosa + ptPos->vY;
  ptDiscardMeshContext->nMaxVertices = 1500;
  ptDiscardMeshContext->nMaxEdges = 500;
  ptDiscardMeshContext->nMaxDrawTriangles = 1000;
  ptPosb = v8;
  ptDiscardMeshContext->vWorldMinX = v5;
  ptDiscardMeshContext->nMaxRegisteredTriangles = 100;
  ptDiscardMeshContext->nMaxDiscardTriangles = 100;
  ptDiscardMeshContext->vWorldMinY = v7;
  ptDiscardMeshContext->nVertices = 0;
  ptDiscardMeshContext->nEdges = 0;
  ptDiscardMeshContext->vWorldMaxX = ptDiscardMeshContextb;
  ptDiscardMeshContext->nDrawTriangles = 0;
  ptDiscardMeshContext->nRegisteredTriangles = 0;
  ptDiscardMeshContext->vWorldMaxY = v8;
  ptDiscardMeshContext->nDiscardTriangles = 0;
  ptDiscardMeshContext->isProcessed = false;
  ptDiscardMeshContext->atVertex[0].tPos.vX = v5;
  ptDiscardMeshContext->atVertex[ptDiscardMeshContext->nVertices].tPos.vY = v7;
  ptDiscardMeshContext->atVertex[ptDiscardMeshContext->nVertices].iID = ptDiscardMeshContext->nVertices;
  v9 = ptDiscardMeshContext->nVertices + 1;
  ptDiscardMeshContext->nVertices = v9;
  ptDiscardMeshContext->atVertex[v9].tPos.vX = v5;
  ptDiscardMeshContext->atVertex[ptDiscardMeshContext->nVertices].tPos.vY = v8;
  ptDiscardMeshContext->atVertex[ptDiscardMeshContext->nVertices].iID = ptDiscardMeshContext->nVertices;
  v10 = ptDiscardMeshContext->nVertices + 1;
  ptDiscardMeshContext->nVertices = v10;
  ptDiscardMeshContext->atVertex[v10].tPos.vX = ptDiscardMeshContextb;
  ptDiscardMeshContext->atVertex[ptDiscardMeshContext->nVertices].tPos.vY = v7;
  ptDiscardMeshContext->atVertex[ptDiscardMeshContext->nVertices].iID = ptDiscardMeshContext->nVertices;
  v11 = ++ptDiscardMeshContext->nVertices;
  ptDiscardMeshContext->atVertex[v11].tPos.vX = ptDiscardMeshContextb;
  ptDiscardMeshContext->atVertex[ptDiscardMeshContext->nVertices].tPos.vY = ptPosb;
  ptDiscardMeshContext->atVertex[ptDiscardMeshContext->nVertices].iID = ptDiscardMeshContext->nVertices;
  ++ptDiscardMeshContext->nVertices;
  return ptDiscardMeshContext;
}
