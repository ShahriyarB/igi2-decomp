/* b/4/pc/pc_direct3dqvertex.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: b/4/pc/pc_direct3dqvertex.c:181  [size]
struct QVertex_s *__cdecl Direct3DQVertex_Interpolate(
        struct QVertex_s *ptDestination,
        struct QVertex_s *ptSource1,
        struct QVertex_s *ptSource2,
        float vFactor)
{
  ptDestination->vX = (ptSource2->vX - ptSource1->vX) * vFactor + ptSource1->vX;
  ptDestination->vY = (ptSource2->vY - ptSource1->vY) * vFactor + ptSource1->vY;
  ptDestination->vZ = (ptSource2->vZ - ptSource1->vZ) * vFactor + ptSource1->vZ;
  ptDestination->vR = (ptSource2->vR - ptSource1->vR) * vFactor + ptSource1->vR;
  ptDestination->vG = (ptSource2->vG - ptSource1->vG) * vFactor + ptSource1->vG;
  ptDestination->vB = (ptSource2->vB - ptSource1->vB) * vFactor + ptSource1->vB;
  ptDestination->vU = (ptSource2->vU - ptSource1->vU) * vFactor + ptSource1->vU;
  ptDestination->vV = (ptSource2->vV - ptSource1->vV) * vFactor + ptSource1->vV;
  ptDestination->vA = (ptSource2->vA - ptSource1->vA) * vFactor + ptSource1->vA;
  return ptSource1;
}

// source: b/4/pc/pc_direct3dqvertex.c:208  [size~]
void __cdecl Direct3DQVertex_CheckTriangle(
        struct QVertexTransformedVertex_t tVertex0,
        struct QVertexTransformedVertex_t tVertex1,
        struct QVertexTransformedVertex_t tVertex2,
        float vClipZ,
        void (__cdecl *pfCallback)(struct QVertexTransformedVertex_t **, void *),
        void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct QVertexTransformedVertex_t v60; };
    struct { char igi2_o1[40]; struct QVertexTransformedVertex_t v61; };
    struct { char igi2_o2[80]; struct QVertexTransformedVertex_t v62; };
    struct { char igi2_o3[128]; struct QVertex_s *ptDestination; };
    struct { char igi2_o4[148]; struct QVertex_s *ptSource1; };
    struct { char igi2_o5[152]; struct QVertex_s *ptSource2; };
    struct { char igi2_o6[156]; struct QVertexTransformedVertex_t *v66[3]; };
    struct { char igi2_o7[168]; _BYTE v67[40]; };
    char igi2_extent[208];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  char bOutcode; // dl
  char v7; // al
  char v8; // cl
  char v9; // bl
  unsigned int v10; // ebp
  struct QVertexTransformedVertex_t *p_tVertex2; // eax
  struct QVertexTransformedVertex_t *v12; // edi
  struct QVertexTransformedVertex_t *p_tVertex0; // ecx
  struct QVertexTransformedVertex_t *p_tVertex1; // esi
  double v15; // st7
  struct QVertexTransformedVertex_t *v16; // eax
  struct QVertexTransformedVertex_t *v17; // ecx
  struct QVertexTransformedVertex_t *v18; // edx
  double v19; // st7
  double v20; // st6
  BOOL v21; // ecx
  double v22; // st7
  int v23; // edx
  int v24; // ecx
  struct QVertexTransformedVertex_t *v25; // eax
  struct QVertexTransformedVertex_t *v26; // edi
  struct QVertexTransformedVertex_t *v27; // ecx
  struct QVertexTransformedVertex_t *v28; // esi
  double v29; // st7
  unsigned int v30; // ebp
  struct QVertexTransformedVertex_t *v31; // eax
  struct QVertexTransformedVertex_t *v32; // ecx
  struct QVertexTransformedVertex_t *v33; // edx
  double v34; // st7
  double v35; // st6
  BOOL v36; // ecx
  double v37; // st7
  int v38; // edx
  int v39; // ecx
  struct QVertexTransformedVertex_t *v40; // eax
  struct QVertexTransformedVertex_t *v41; // edi
  struct QVertexTransformedVertex_t *v42; // ecx
  struct QVertexTransformedVertex_t *v43; // esi
  unsigned int v44; // ebp
  struct QVertexTransformedVertex_t *v45; // eax
  struct QVertexTransformedVertex_t *v46; // edx
  struct QVertexTransformedVertex_t *v47; // ecx
  double v48; // st7
  double v49; // st6
  int v50; // edx
  int v51; // ecx
  struct QVertexTransformedVertex_t *v52; // eax
  struct QVertexTransformedVertex_t *v53; // edi
  struct QVertexTransformedVertex_t *v54; // ecx
  struct QVertexTransformedVertex_t *v55; // esi
  unsigned int v56; // ebx
  struct QVertexTransformedVertex_t *v57; // ebx
  struct QVertexTransformedVertex_t *v58; // eax
  struct QVertexTransformedVertex_t *v59; // ebp

  bOutcode = tVertex0.bOutcode;
  v7 = tVertex2.bOutcode;
  ++dword_8344018;
  v8 = tVertex1.bOutcode;
  v9 = LOBYTE(tVertex2.bOutcode) | LOBYTE(tVertex1.bOutcode) | LOBYTE(tVertex0.bOutcode);
  v10 = tVertex2.bOutcode & tVertex1.bOutcode & tVertex0.bOutcode;
  if ( !v10 && (v9 & 0x10) == 0 )
  {
    if ( (v9 & 1) != 0 )
    {
      if ( (tVertex1.bOutcode & 1) + (tVertex0.bOutcode & 1) + (tVertex2.bOutcode & 1) == 2 )
      {
        if ( (tVertex0.bOutcode & 1) != 0 )
        {
          if ( (tVertex1.bOutcode & 1) != 0 )
          {
            p_tVertex2 = &tVertex2;
            v12 = &tVertex2;
            p_tVertex0 = &tVertex0;
            p_tVertex1 = &tVertex1;
          }
          else
          {
            p_tVertex2 = &tVertex1;
            v12 = &tVertex1;
            p_tVertex0 = &tVertex2;
            p_tVertex1 = &tVertex0;
          }
        }
        else
        {
          p_tVertex2 = &tVertex0;
          v12 = &tVertex0;
          p_tVertex0 = &tVertex1;
          p_tVertex1 = &tVertex2;
        }
        igi2_frame.ptDestination = (struct QVertex_s *)p_tVertex0;
        *(float *)&igi2_frame.ptDestination = (RenderContext_tActiveRenderContext.tDisplayAreaMin.vX - p_tVertex2->tViewVertex.vX)
                                 / (p_tVertex0->tViewVertex.vX - p_tVertex2->tViewVertex.vX);
        Direct3DQVertex_Interpolate(
          &p_tVertex0->tViewVertex,
          &p_tVertex2->tViewVertex,
          &p_tVertex0->tViewVertex,
          *(float *)&igi2_frame.ptDestination);
        p_tVertex0->bOutcode = 2
                             * ((p_tVertex0->tViewVertex.vY < (double)RenderContext_tActiveRenderContext.tDisplayAreaMin.vY)
                              | (2
                               * ((RenderContext_tActiveRenderContext.tDisplayAreaMax.vX + 1.0 < p_tVertex0->tViewVertex.vX)
                                | (2
                                 * (RenderContext_tActiveRenderContext.tDisplayAreaMax.vY + 1.0 < p_tVertex0->tViewVertex.vY)))));
        v15 = RenderContext_tActiveRenderContext.tDisplayAreaMin.vX - v12->tViewVertex.vX;
        igi2_frame.ptDestination = (struct QVertex_s *)p_tVertex0;
        *(float *)&igi2_frame.ptDestination = v15 / (p_tVertex1->tViewVertex.vX - v12->tViewVertex.vX);
        Direct3DQVertex_Interpolate(
          &p_tVertex1->tViewVertex,
          &v12->tViewVertex,
          &p_tVertex1->tViewVertex,
          *(float *)&igi2_frame.ptDestination);
        p_tVertex1->bOutcode = 2
                             * ((p_tVertex1->tViewVertex.vY < (double)RenderContext_tActiveRenderContext.tDisplayAreaMin.vY)
                              | (2
                               * ((RenderContext_tActiveRenderContext.tDisplayAreaMax.vX + 1.0 < p_tVertex1->tViewVertex.vX)
                                | (2
                                 * (RenderContext_tActiveRenderContext.tDisplayAreaMax.vY + 1.0 < p_tVertex1->tViewVertex.vY)))));
        bOutcode = tVertex0.bOutcode;
        v8 = tVertex1.bOutcode;
        v7 = tVertex2.bOutcode;
        v9 = LOBYTE(tVertex2.bOutcode) | LOBYTE(tVertex1.bOutcode) | LOBYTE(tVertex0.bOutcode);
        v10 = tVertex2.bOutcode & tVertex1.bOutcode & tVertex0.bOutcode;
      }
      else
      {
        if ( (tVertex0.bOutcode & 1) != 0 )
        {
          v16 = &tVertex1;
          v17 = &tVertex2;
          v18 = &tVertex0;
        }
        else if ( (tVertex1.bOutcode & 1) != 0 )
        {
          v16 = &tVertex2;
          v17 = &tVertex0;
          v18 = &tVertex1;
        }
        else
        {
          v16 = &tVertex0;
          v17 = &tVertex1;
          v18 = &tVertex2;
        }
        igi2_frame.ptSource2 = &v17->tViewVertex;
        v19 = RenderContext_tActiveRenderContext.tDisplayAreaMin.vX - v16->tViewVertex.vX;
        v20 = v18->tViewVertex.vX - v16->tViewVertex.vX;
        qmemcpy(igi2_frame.v67, v18, sizeof(igi2_frame.v67));
        igi2_frame.ptSource1 = &v18->tViewVertex;
        *(float *)&igi2_frame.ptDestination = v19 / v20;
        Direct3DQVertex_Interpolate(&v18->tViewVertex, &v16->tViewVertex, &v18->tViewVertex, *(float *)&igi2_frame.ptDestination);
        v21 = RenderContext_tActiveRenderContext.tDisplayAreaMax.vX + 1.0 < v18->tViewVertex.vX;
        v18->bOutcode = 2
                      * ((v18->tViewVertex.vY < (double)RenderContext_tActiveRenderContext.tDisplayAreaMin.vY)
                       | (2
                        * (v21
                         | (2 * (RenderContext_tActiveRenderContext.tDisplayAreaMax.vY + 1.0 < v18->tViewVertex.vY)))));
        v22 = RenderContext_tActiveRenderContext.tDisplayAreaMin.vX - igi2_frame.ptSource2->vX;
        igi2_frame.ptDestination = (struct QVertex_s *)v21;
        *(float *)&igi2_frame.ptDestination = v22 / (*(float *)igi2_frame.v67 - igi2_frame.ptSource2->vX);
        Direct3DQVertex_Interpolate(
          (struct QVertex_s *)igi2_frame.v67,
          igi2_frame.ptSource2,
          (struct QVertex_s *)igi2_frame.v67,
          *(float *)&igi2_frame.ptDestination);
        *(_DWORD *)&igi2_frame.v67[36] = 2
                            * ((*(float *)&igi2_frame.v67[4] < (double)RenderContext_tActiveRenderContext.tDisplayAreaMin.vY)
                             | (2
                              * ((RenderContext_tActiveRenderContext.tDisplayAreaMax.vX + 1.0 < *(float *)igi2_frame.v67)
                               | (2 * (RenderContext_tActiveRenderContext.tDisplayAreaMax.vY + 1.0 < *(float *)&igi2_frame.v67[4])))));
        v9 = LOBYTE(tVertex2.bOutcode) | LOBYTE(tVertex1.bOutcode) | LOBYTE(tVertex0.bOutcode);
        v10 = tVertex2.bOutcode & tVertex1.bOutcode & tVertex0.bOutcode;
        qmemcpy(&igi2_frame.v62, igi2_frame.ptSource1, sizeof(igi2_frame.v62));
        qmemcpy(&igi2_frame.v61, igi2_frame.v67, sizeof(igi2_frame.v61));
        qmemcpy(&igi2_frame.v60, igi2_frame.ptSource2, sizeof(igi2_frame.v60));
        Direct3DQVertex_CheckTriangle(igi2_frame.v60, igi2_frame.v61, igi2_frame.v62, vClipZ, pfCallback, pxContext);
        v7 = tVertex2.bOutcode;
        v8 = tVertex1.bOutcode;
        bOutcode = tVertex0.bOutcode;
      }
    }
    if ( !v10 )
    {
      if ( (v9 & 2) == 0 )
        goto LABEL_33;
      v23 = bOutcode & 2;
      v24 = v8 & 2;
      if ( ((v24 + v23 + (v7 & 2)) & 0xFFFFFFFE) == 4 )
      {
        if ( v23 )
        {
          if ( v24 )
          {
            v25 = &tVertex2;
            v26 = &tVertex2;
            v27 = &tVertex0;
            v28 = &tVertex1;
          }
          else
          {
            v25 = &tVertex1;
            v26 = &tVertex1;
            v27 = &tVertex2;
            v28 = &tVertex0;
          }
        }
        else
        {
          v25 = &tVertex0;
          v26 = &tVertex0;
          v27 = &tVertex1;
          v28 = &tVertex2;
        }
        igi2_frame.ptDestination = (struct QVertex_s *)v27;
        *(float *)&igi2_frame.ptDestination = (RenderContext_tActiveRenderContext.tDisplayAreaMin.vY - v25->tViewVertex.vY)
                                 / (v27->tViewVertex.vY - v25->tViewVertex.vY);
        Direct3DQVertex_Interpolate(&v27->tViewVertex, &v25->tViewVertex, &v27->tViewVertex, *(float *)&igi2_frame.ptDestination);
        v27->bOutcode = 4
                      * ((RenderContext_tActiveRenderContext.tDisplayAreaMax.vX + 1.0 < v27->tViewVertex.vX)
                       | (2 * (RenderContext_tActiveRenderContext.tDisplayAreaMax.vY + 1.0 < v27->tViewVertex.vY)));
        v29 = RenderContext_tActiveRenderContext.tDisplayAreaMin.vY - v26->tViewVertex.vY;
        igi2_frame.ptDestination = (struct QVertex_s *)v27;
        *(float *)&igi2_frame.ptDestination = v29 / (v28->tViewVertex.vY - v26->tViewVertex.vY);
        Direct3DQVertex_Interpolate(&v28->tViewVertex, &v26->tViewVertex, &v28->tViewVertex, *(float *)&igi2_frame.ptDestination);
        v28->bOutcode = 4
                      * ((RenderContext_tActiveRenderContext.tDisplayAreaMax.vX + 1.0 < v28->tViewVertex.vX)
                       | (2 * (RenderContext_tActiveRenderContext.tDisplayAreaMax.vY + 1.0 < v28->tViewVertex.vY)));
        bOutcode = tVertex0.bOutcode;
        v8 = tVertex1.bOutcode;
        v7 = tVertex2.bOutcode;
        v9 = LOBYTE(tVertex2.bOutcode) | LOBYTE(tVertex1.bOutcode) | LOBYTE(tVertex0.bOutcode);
        v30 = tVertex2.bOutcode & tVertex1.bOutcode & tVertex0.bOutcode;
      }
      else
      {
        if ( v23 )
        {
          v31 = &tVertex1;
          v32 = &tVertex2;
          v33 = &tVertex0;
        }
        else if ( v24 )
        {
          v31 = &tVertex2;
          v32 = &tVertex0;
          v33 = &tVertex1;
        }
        else
        {
          v31 = &tVertex0;
          v32 = &tVertex1;
          v33 = &tVertex2;
        }
        igi2_frame.ptSource1 = &v32->tViewVertex;
        v34 = RenderContext_tActiveRenderContext.tDisplayAreaMin.vY - v31->tViewVertex.vY;
        v35 = v33->tViewVertex.vY - v31->tViewVertex.vY;
        qmemcpy(igi2_frame.v67, v33, sizeof(igi2_frame.v67));
        igi2_frame.ptSource2 = &v33->tViewVertex;
        *(float *)&igi2_frame.ptDestination = v34 / v35;
        Direct3DQVertex_Interpolate(&v33->tViewVertex, &v31->tViewVertex, &v33->tViewVertex, *(float *)&igi2_frame.ptDestination);
        v36 = RenderContext_tActiveRenderContext.tDisplayAreaMax.vX + 1.0 < v33->tViewVertex.vX;
        v33->bOutcode = 4
                      * (v36 | (2 * (RenderContext_tActiveRenderContext.tDisplayAreaMax.vY + 1.0 < v33->tViewVertex.vY)));
        v37 = RenderContext_tActiveRenderContext.tDisplayAreaMin.vY - igi2_frame.ptSource1->vY;
        igi2_frame.ptDestination = (struct QVertex_s *)v36;
        *(float *)&igi2_frame.ptDestination = v37 / (*(float *)&igi2_frame.v67[4] - igi2_frame.ptSource1->vY);
        Direct3DQVertex_Interpolate(
          (struct QVertex_s *)igi2_frame.v67,
          igi2_frame.ptSource1,
          (struct QVertex_s *)igi2_frame.v67,
          *(float *)&igi2_frame.ptDestination);
        *(_DWORD *)&igi2_frame.v67[36] = 4
                            * ((RenderContext_tActiveRenderContext.tDisplayAreaMax.vX + 1.0 < *(float *)igi2_frame.v67)
                             | (2 * (RenderContext_tActiveRenderContext.tDisplayAreaMax.vY + 1.0 < *(float *)&igi2_frame.v67[4])));
        v30 = tVertex2.bOutcode & tVertex1.bOutcode & tVertex0.bOutcode;
        v9 = LOBYTE(tVertex2.bOutcode) | LOBYTE(tVertex1.bOutcode) | LOBYTE(tVertex0.bOutcode);
        qmemcpy(&igi2_frame.v62, igi2_frame.ptSource2, sizeof(igi2_frame.v62));
        qmemcpy(&igi2_frame.v61, igi2_frame.v67, sizeof(igi2_frame.v61));
        qmemcpy(&igi2_frame.v60, igi2_frame.ptSource1, sizeof(igi2_frame.v60));
        Direct3DQVertex_CheckTriangle(igi2_frame.v60, igi2_frame.v61, igi2_frame.v62, vClipZ, pfCallback, pxContext);
        v7 = tVertex2.bOutcode;
        v8 = tVertex1.bOutcode;
        bOutcode = tVertex0.bOutcode;
      }
      if ( !v30 )
      {
LABEL_33:
        if ( (v9 & 4) == 0 )
          goto LABEL_63;
        v38 = bOutcode & 4;
        v39 = v8 & 4;
        if ( ((v39 + v38 + (v7 & 4)) & 0xFFFFFFFC) == 8 )
        {
          if ( v38 )
          {
            if ( v39 )
            {
              v40 = &tVertex2;
              v41 = &tVertex2;
              v42 = &tVertex0;
              v43 = &tVertex1;
            }
            else
            {
              v40 = &tVertex1;
              v41 = &tVertex1;
              v42 = &tVertex2;
              v43 = &tVertex0;
            }
          }
          else
          {
            v40 = &tVertex0;
            v41 = &tVertex0;
            v42 = &tVertex1;
            v43 = &tVertex2;
          }
          igi2_frame.ptDestination = (struct QVertex_s *)v42;
          *(float *)&igi2_frame.ptDestination = (RenderContext_tActiveRenderContext.tDisplayAreaMax.vX + 1.0 - v40->tViewVertex.vX)
                                   / (v42->tViewVertex.vX - v40->tViewVertex.vX);
          Direct3DQVertex_Interpolate(&v42->tViewVertex, &v40->tViewVertex, &v42->tViewVertex, *(float *)&igi2_frame.ptDestination);
          v42->bOutcode = 8 * (RenderContext_tActiveRenderContext.tDisplayAreaMax.vY + 1.0 < v42->tViewVertex.vY);
          igi2_frame.ptDestination = (struct QVertex_s *)v42;
          *(float *)&igi2_frame.ptDestination = (RenderContext_tActiveRenderContext.tDisplayAreaMax.vX + 1.0 - v41->tViewVertex.vX)
                                   / (v43->tViewVertex.vX - v41->tViewVertex.vX);
          Direct3DQVertex_Interpolate(&v43->tViewVertex, &v41->tViewVertex, &v43->tViewVertex, *(float *)&igi2_frame.ptDestination);
          v43->bOutcode = 8 * (RenderContext_tActiveRenderContext.tDisplayAreaMax.vY + 1.0 < v43->tViewVertex.vY);
          bOutcode = tVertex0.bOutcode;
          v8 = tVertex1.bOutcode;
          v7 = tVertex2.bOutcode;
          v9 = LOBYTE(tVertex2.bOutcode) | LOBYTE(tVertex1.bOutcode) | LOBYTE(tVertex0.bOutcode);
          v44 = tVertex2.bOutcode & tVertex1.bOutcode & tVertex0.bOutcode;
        }
        else
        {
          if ( v38 )
          {
            v45 = &tVertex1;
            v46 = &tVertex2;
            v47 = &tVertex0;
          }
          else if ( v39 )
          {
            v45 = &tVertex2;
            v46 = &tVertex0;
            v47 = &tVertex1;
          }
          else
          {
            v45 = &tVertex0;
            v46 = &tVertex1;
            v47 = &tVertex2;
          }
          igi2_frame.ptSource2 = &v47->tViewVertex;
          igi2_frame.ptSource1 = &v46->tViewVertex;
          v48 = RenderContext_tActiveRenderContext.tDisplayAreaMax.vX + 1.0 - v45->tViewVertex.vX;
          v49 = v47->tViewVertex.vX - v45->tViewVertex.vX;
          qmemcpy(igi2_frame.v67, v47, sizeof(igi2_frame.v67));
          *(float *)&igi2_frame.ptDestination = v48 / v49;
          Direct3DQVertex_Interpolate(&v47->tViewVertex, &v45->tViewVertex, &v47->tViewVertex, *(float *)&igi2_frame.ptDestination);
          v47->bOutcode = 8 * (RenderContext_tActiveRenderContext.tDisplayAreaMax.vY + 1.0 < v47->tViewVertex.vY);
          igi2_frame.ptDestination = (struct QVertex_s *)v47;
          *(float *)&igi2_frame.ptDestination = (RenderContext_tActiveRenderContext.tDisplayAreaMax.vX + 1.0 - igi2_frame.ptSource1->vX)
                                   / (*(float *)igi2_frame.v67 - igi2_frame.ptSource1->vX);
          Direct3DQVertex_Interpolate(
            (struct QVertex_s *)igi2_frame.v67,
            igi2_frame.ptSource1,
            (struct QVertex_s *)igi2_frame.v67,
            *(float *)&igi2_frame.ptDestination);
          *(_DWORD *)&igi2_frame.v67[36] = 8 * (RenderContext_tActiveRenderContext.tDisplayAreaMax.vY + 1.0 < *(float *)&igi2_frame.v67[4]);
          v9 = LOBYTE(tVertex2.bOutcode) | LOBYTE(tVertex1.bOutcode) | LOBYTE(tVertex0.bOutcode);
          v44 = tVertex2.bOutcode & tVertex1.bOutcode & tVertex0.bOutcode;
          qmemcpy(&igi2_frame.v62, igi2_frame.ptSource2, sizeof(igi2_frame.v62));
          qmemcpy(&igi2_frame.v61, igi2_frame.v67, sizeof(igi2_frame.v61));
          qmemcpy(&igi2_frame.v60, igi2_frame.ptSource1, sizeof(igi2_frame.v60));
          Direct3DQVertex_CheckTriangle(igi2_frame.v60, igi2_frame.v61, igi2_frame.v62, vClipZ, pfCallback, pxContext);
          v7 = tVertex2.bOutcode;
          v8 = tVertex1.bOutcode;
          bOutcode = tVertex0.bOutcode;
        }
        if ( !v44 )
        {
LABEL_63:
          if ( (v9 & 8) == 0 )
            goto LABEL_64;
          v50 = bOutcode & 8;
          v51 = v8 & 8;
          if ( ((v51 + v50 + (v7 & 8)) & 0xFFFFFFF8) == 0x10 )
          {
            if ( v50 )
            {
              if ( v51 )
              {
                v52 = &tVertex2;
                v53 = &tVertex2;
                v54 = &tVertex0;
                v55 = &tVertex1;
              }
              else
              {
                v52 = &tVertex1;
                v53 = &tVertex1;
                v54 = &tVertex2;
                v55 = &tVertex0;
              }
            }
            else
            {
              v52 = &tVertex0;
              v53 = &tVertex0;
              v54 = &tVertex1;
              v55 = &tVertex2;
            }
            igi2_frame.ptDestination = (struct QVertex_s *)v54;
            *(float *)&igi2_frame.ptDestination = (RenderContext_tActiveRenderContext.tDisplayAreaMax.vY + 1.0 - v52->tViewVertex.vY)
                                     / (v54->tViewVertex.vY - v52->tViewVertex.vY);
            Direct3DQVertex_Interpolate(
              &v54->tViewVertex,
              &v52->tViewVertex,
              &v54->tViewVertex,
              *(float *)&igi2_frame.ptDestination);
            v54->bOutcode = 0;
            *(float *)&igi2_frame.ptDestination = (RenderContext_tActiveRenderContext.tDisplayAreaMax.vY + 1.0 - v53->tViewVertex.vY)
                                     / (v55->tViewVertex.vY - v53->tViewVertex.vY);
            Direct3DQVertex_Interpolate(
              &v55->tViewVertex,
              &v53->tViewVertex,
              &v55->tViewVertex,
              *(float *)&igi2_frame.ptDestination);
            v55->bOutcode = 0;
            v56 = tVertex2.bOutcode & tVertex1.bOutcode & tVertex0.bOutcode;
          }
          else
          {
            if ( v50 )
            {
              v57 = &tVertex2;
              v58 = &tVertex1;
              igi2_frame.ptSource1 = (struct QVertex_s *)&tVertex2;
              v59 = &tVertex0;
            }
            else
            {
              if ( v51 )
              {
                v58 = &tVertex2;
                igi2_frame.ptSource1 = (struct QVertex_s *)&tVertex0;
                v59 = &tVertex1;
              }
              else
              {
                v58 = &tVertex0;
                igi2_frame.ptSource1 = (struct QVertex_s *)&tVertex1;
                v59 = &tVertex2;
              }
              v57 = (struct QVertexTransformedVertex_t *)igi2_frame.ptSource1;
            }
            qmemcpy(igi2_frame.v67, v59, sizeof(igi2_frame.v67));
            *(float *)&igi2_frame.ptDestination = (RenderContext_tActiveRenderContext.tDisplayAreaMax.vY + 1.0 - v58->tViewVertex.vY)
                                     / (v59->tViewVertex.vY - v58->tViewVertex.vY);
            Direct3DQVertex_Interpolate(
              &v59->tViewVertex,
              &v58->tViewVertex,
              &v59->tViewVertex,
              *(float *)&igi2_frame.ptDestination);
            v59->bOutcode = 0;
            *(float *)&igi2_frame.ptDestination = (RenderContext_tActiveRenderContext.tDisplayAreaMax.vY + 1.0 - v57->tViewVertex.vY)
                                     / (*(float *)&igi2_frame.v67[4] - v57->tViewVertex.vY);
            Direct3DQVertex_Interpolate(
              (struct QVertex_s *)igi2_frame.v67,
              &v57->tViewVertex,
              (struct QVertex_s *)igi2_frame.v67,
              *(float *)&igi2_frame.ptDestination);
            *(_DWORD *)&igi2_frame.v67[36] = 0;
            v56 = tVertex2.bOutcode & tVertex1.bOutcode & tVertex0.bOutcode;
            qmemcpy(&igi2_frame.v62, v59, sizeof(igi2_frame.v62));
            qmemcpy(&igi2_frame.v61, igi2_frame.v67, sizeof(igi2_frame.v61));
            qmemcpy(&igi2_frame.v60, igi2_frame.ptSource1, sizeof(igi2_frame.v60));
            Direct3DQVertex_CheckTriangle(igi2_frame.v60, igi2_frame.v61, igi2_frame.v62, vClipZ, pfCallback, pxContext);
          }
          if ( !v56 )
          {
LABEL_64:
            igi2_frame.v66[0] = &tVertex0;
            igi2_frame.v66[1] = &tVertex1;
            igi2_frame.v66[2] = &tVertex2;
            pfCallback(igi2_frame.v66, pxContext);
          }
        }
      }
    }
  }
  --dword_8344018;
}

// source: b/4/pc/pc_direct3dqvertex.c:880  [size]
void __cdecl Direct3DQVertex_SetGenericState(struct Direct3DQVertexStateContext_t *ptContext)
{
  struct IDirect3DDevice8Vtbl *lpVtbl; // edx

  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ZBIAS, 0);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_FOGENABLE, 0);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_SPECULARENABLE, 0);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_CULLMODE, 1u);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_LIGHTING, 0);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_DITHERENABLE, 1u);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_COLORVERTEX, 1u);
  if ( (ptContext->bFlags & 0x8000003C) != 0 )
  {
    Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ALPHATESTENABLE, 1u);
    Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ALPHAREF, 10u);
    Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ALPHAFUNC, 5u);
  }
  else
  {
    Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ALPHATESTENABLE, 0);
  }
  lpVtbl = Direct3D_ptDevice->lpVtbl;
  if ( (ptContext->bFlags & 0x20000) != 0 )
  {
    lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ZFUNC, 4u);
    Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ZENABLE, Direct3D_bZBufferMode);
    Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ZWRITEENABLE, 1u);
  }
  else if ( (ptContext->bFlags & 0x40000) != 0 )
  {
    lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ZFUNC, 4u);
    Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ZENABLE, Direct3D_bZBufferMode);
    Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ZWRITEENABLE, 0);
  }
  else
  {
    lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ZENABLE, 0);
  }
}

// source: b/4/pc/pc_direct3dqvertex.c:928  [size]
void __cdecl Direct3DQVertex_SetTextureState(struct Direct3DQVertexStateContext_t *ptContext)
{
  struct IDirect3DDevice8Vtbl *lpVtbl; // ecx
  struct IDirect3DDevice8Vtbl *v2; // ecx
  struct TexInfo_s *ptTexInfo; // edx

  if ( ptContext->ptTexInfo )
  {
    lpVtbl = Direct3D_ptDevice->lpVtbl;
    if ( (ptContext->bFlags & 0x1000000) != 0 )
    {
      lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_MINFILTER, 2u);
      Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_MAGFILTER, 2u);
    }
    else
    {
      lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_MINFILTER, 1u);
      Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_MAGFILTER, 1u);
    }
    v2 = Direct3D_ptDevice->lpVtbl;
    if ( (ptContext->bFlags & 0x400000) != 0 )
    {
      v2->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_ADDRESSU, 1u);
      Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_ADDRESSV, 1u);
    }
    else
    {
      v2->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_ADDRESSU, 3u);
      Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_ADDRESSV, 3u);
    }
    Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_MIPFILTER, 1u);
    Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_TEXCOORDINDEX, 0);
    Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_ALPHAOP, 4u);
    Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_ALPHAARG1, 2u);
    Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_ALPHAARG2, 0);
    Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_COLOROP, 4u);
    Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_COLORARG1, 2u);
    Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_COLORARG2, 0);
    Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 1u, D3DTSS_COLOROP, 1u);
    ptTexInfo = ptContext->ptTexInfo;
    if ( ptTexInfo->ptDirect3DBaseTexture != Direct3D_tState.aptTexture[0] )
    {
      Direct3D_tState.aptTexture[0] = ptTexInfo->ptDirect3DBaseTexture;
      Direct3D_ptDevice->lpVtbl->SetTexture(Direct3D_ptDevice, 0, Direct3D_tState.aptTexture[0]);
    }
  }
  else
  {
    Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_ALPHAOP, 3u);
    Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_ALPHAARG1, 2u);
    Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_ALPHAARG2, 0);
    Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_COLOROP, 3u);
    Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_COLORARG1, 2u);
    Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_COLORARG2, 0);
    Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 1u, D3DTSS_COLOROP, 1u);
    if ( Direct3D_tState.aptTexture[0] )
    {
      Direct3D_tState.aptTexture[0] = nullptr;
      Direct3D_ptDevice->lpVtbl->SetTexture(Direct3D_ptDevice, 0, nullptr);
    }
  }
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_TEXTURETRANSFORMFLAGS, 0);
}

// source: b/4/pc/pc_direct3dqvertex.c:991  [size]
void __cdecl Direct3DQVertex_SetAlphaState(struct Direct3DQVertexStateContext_t *ptContext)
{
  signed int bFlags; // eax

  bFlags = ptContext->bFlags;
  if ( (ptContext->bFlags & 8) != 0 )
  {
    Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ALPHABLENDENABLE, 1u);
    Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_SRCBLEND, 5u);
    Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_DESTBLEND, 2u);
  }
  else if ( (bFlags & 0x10) != 0 )
  {
    Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ALPHABLENDENABLE, 1u);
    Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_SRCBLEND, 1u);
    Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_DESTBLEND, 4u);
  }
  else if ( bFlags >= 0 )
  {
    Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ALPHABLENDENABLE, 1u);
    Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_SRCBLEND, 5u);
    Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_DESTBLEND, 6u);
  }
  else
  {
    Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ALPHABLENDENABLE, 1u);
    Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_SRCBLEND, 1u);
    Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_DESTBLEND, 3u);
  }
}

// source: b/4/pc/pc_direct3dqvertex.c:1027  [size]
void __cdecl Direct3DQVertex_SetStates(struct Batch_SetStatesContext_s *ptContext)
{
  int v1; // edx
  bool v2; // zf
  struct RenderStateBlock_t *v3; // ecx
  _DWORD *pxUserContext; // esi
  struct RenderStateBlock_t *v5; // eax
  struct RenderStateBlock_t *v6; // edi
  int v7; // ecx
  int v8; // eax
  struct RenderStateBlock_t *v9; // eax
  int v10; // ecx

  v1 = Direct3DQVertex_eTextureState;
  v2 = Direct3DQVertex_eTextureState == -1;
  v3 = Direct3D_ptTextureStateBlock;
  pxUserContext = ptContext->pxUserContext;
  v5 = Direct3D_ptBlendStateBlock;
  v6 = Direct3D_ptGenericStateBlock;
  Direct3D_ptGenericStateBlock->eCurrentState = -1;
  v5->eCurrentState = -1;
  v3->eCurrentState = -1;
  if ( !v2 )
  {
    v3->eCurrentState = v1;
    v3->atRenderState[v1].pfCallback(pxUserContext);
    v6 = Direct3D_ptGenericStateBlock;
    v5 = Direct3D_ptBlendStateBlock;
  }
  v7 = Direct3DQVertex_eBlendState;
  if ( v5->eCurrentState != Direct3DQVertex_eBlendState )
  {
    v5->eCurrentState = Direct3DQVertex_eBlendState;
    v5->atRenderState[v7].pfCallback(pxUserContext);
    v6 = Direct3D_ptGenericStateBlock;
  }
  v8 = Direct3DQVertex_eGenericState;
  if ( v6->eCurrentState != Direct3DQVertex_eGenericState )
  {
    v6->eCurrentState = Direct3DQVertex_eGenericState;
    v6->atRenderState[v8].pfCallback(pxUserContext);
  }
  v9 = Direct3D_ptClippingStateBlock;
  v10 = Direct3D_eClippingStateOn;
  if ( Direct3D_ptClippingStateBlock->eCurrentState != Direct3D_eClippingStateOn )
  {
    Direct3D_ptClippingStateBlock->eCurrentState = Direct3D_eClippingStateOn;
    v9->atRenderState[v10].pfCallback(pxUserContext);
  }
  if ( (*pxUserContext & 0x100000) != 0 )
  {
    Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_STENCILFUNC, 2u);
    Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_STENCILREF, 0);
    Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_STENCILENABLE, 1u);
  }
}

// source: b/4/pc/pc_direct3dqvertex.c:1063  [size]
void __cdecl Direct3DQVertex_UnsetStates(struct Batch_SetStatesContext_s *ptContext)
{
  if ( (*(_DWORD *)ptContext->pxUserContext & 0x100000) != 0 )
    Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_STENCILFUNC, 8u);
}

// source: b/4/pc/pc_direct3dqvertex.c:1086  [size]
void __cdecl Direct3DQVertex_DrawStrip(struct Direct3DQVertexStrip_s *ptStrip)
{
  #pragma pack(push, 1)
  union
  {
    struct { unsigned int v24; };
    struct { char igi2_o1[24]; struct Direct3DQVertex_s *ptVertices; };
    struct { char igi2_o2[28]; struct Batch_SetStatesContext_s tBatchSetStatesContext; };
    char igi2_extent[44];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct Direct3DQVertexStrip_s *v1; // ebx
  _DWORD *v2; // eax
  int v3; // ebp
  _DWORD *v4; // ecx
  struct TexInfo_s *ptTexInfo; // edx
  int nStripLength; // eax
  _DWORD *v7; // esi
  struct Direct3DQVertex_s *ptDirect3DQVertex; // eax
  int v9; // ecx
  __int16 v10; // bp
  int v11; // ecx
  int v12; // eax
  int v13; // ecx
  _WORD *v14; // edx
  int v15; // eax
  _WORD *v16; // ecx
  __int16 v17; // dx
  _WORD *v18; // ecx
  struct Direct3DQVertex_s *v19; // eax
  int v20; // ecx
  int v21; // edx
  __int16 v22; // cx
  _WORD *v23; // edx

  v1 = ptStrip;
  v2 = (_DWORD *)(8 * dword_834D9A4 + 137644872);
  v3 = 0;
  v4 = (_DWORD *)(8 * (dword_834D9A4 ^ 1) + 137644872);
  dword_8344B38 = (int)v2;
  dword_8344014 = (int)v4;
  if ( ptStrip )
  {
    dword_8344B48[2 * dword_834D9A4] = ptStrip->bFlags;
    ptTexInfo = v1->ptTexInfo;
    v2[1] = ptTexInfo;
    if ( v1->isLine )
    {
      Batch_Flush((unsigned int *)&dword_834D9A8, v4);
      nStripLength = v1->nStripLength;
      v7 = (_DWORD *)dword_8344B38;
      igi2_frame.tBatchSetStatesContext.nNumFaces = nStripLength - 1;
      igi2_frame.tBatchSetStatesContext.nNumVertices = nStripLength;
      igi2_frame.tBatchSetStatesContext.pxUserContext = (void *)dword_8344B38;
      Direct3DQVertex_SetStates(&igi2_frame.tBatchSetStatesContext);
      Direct3D_tState.nHandle = Direct3D_atDynamicVertexBuffer[2].nFVF;
      Direct3D_ptDevice->lpVtbl->SetVertexShader(Direct3D_ptDevice, Direct3D_atDynamicVertexBuffer[2].nFVF);
      ptDirect3DQVertex = v1->ptDirect3DQVertex;
      igi2_frame.v24 = v1->nStripLength - 1;
      Direct3D_tState.aptStreamData[0] = nullptr;
      Direct3D_tState.anStride[0] = 0;
      Direct3D_ptDevice->lpVtbl->DrawPrimitiveUP(Direct3D_ptDevice, D3DPT_LINESTRIP, igi2_frame.v24, ptDirect3DQVertex, 28u);
      if ( (*v7 & 0x100000) != 0 )
        Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_STENCILFUNC, 8u);
    }
    else
    {
      if ( ptTexInfo != (struct TexInfo_s *)v4[1] || *v2 != *v4 )
      {
        Batch_Flush((unsigned int *)&dword_834D9A8, v4);
        v2 = (_DWORD *)dword_8344B38;
      }
      v9 = v1->nStripLength;
      if ( v9 <= 2 )
      {
        Batch_GetLockedVertex(
          BATCH_XYZRHWDIFFUSETEX1,
          BATCH_INDEX16,
          4,
          2,
          0,
          nullptr,
          0,
          Direct3DQVertex_SetStates,
          Direct3DQVertex_UnsetStates,
          v2,
          (unsigned __int8 **)&igi2_frame.ptVertices,
          (int *)&ptStrip,
          (unsigned int *)&dword_834D9A8);
        v19 = &igi2_frame.ptVertices[(_DWORD)ptStrip];
        if ( dword_834D9A8 )
        {
          v20 = *((_DWORD *)dword_834D9A8 + 2);
          v21 = *(_DWORD *)(v20 + 8);
          v3 = *(_DWORD *)(v20 + 16);
        }
        else
        {
          v21 = 0;
        }
        qmemcpy(v19, v1->ptDirect3DQVertex, sizeof(struct Direct3DQVertex_s));
        qmemcpy(&v19[1], v1->ptDirect3DQVertex, sizeof(struct Direct3DQVertex_s));
        v19[1].vX = v1->ptDirect3DQVertex[1].vX;
        v19[1].vU = v1->ptDirect3DQVertex[1].vU;
        qmemcpy(&v19[2], v1->ptDirect3DQVertex, sizeof(struct Direct3DQVertex_s));
        v19[2].vY = v1->ptDirect3DQVertex[1].vY;
        v19[2].vV = v1->ptDirect3DQVertex[1].vV;
        qmemcpy(&v19[3], &v1->ptDirect3DQVertex[1], sizeof(struct Direct3DQVertex_s));
        v22 = (__int16)ptStrip;
        *(_WORD *)(v21 + 2 * v3) = (_WORD)ptStrip;
        *(_WORD *)(v21 + 2 * v3 + 2) = v22 + 1;
        *(_WORD *)(v21 + 2 * v3 + 4) = v22 + 2;
        *(_WORD *)(v21 + 2 * v3 + 6) = v22 + 1;
        v23 = (_WORD *)(v21 + 2 * v3 + 8);
        *v23 = v22 + 3;
        v23[1] = v22 + 2;
      }
      else
      {
        Batch_GetLockedVertex(
          BATCH_XYZRHWDIFFUSETEX1,
          BATCH_INDEX16,
          v9,
          v9 - 2,
          0,
          nullptr,
          0,
          Direct3DQVertex_SetStates,
          Direct3DQVertex_UnsetStates,
          v2,
          (unsigned __int8 **)&igi2_frame.ptVertices,
          (int *)&ptStrip,
          (unsigned int *)&dword_834D9A8);
        v10 = (__int16)ptStrip;
        if ( dword_834D9A8 )
        {
          v11 = *((_DWORD *)dword_834D9A8 + 2);
          v12 = *(_DWORD *)(v11 + 8);
          v13 = *(_DWORD *)(v11 + 16);
        }
        else
        {
          v12 = 0;
          v13 = 0;
        }
        v14 = (_WORD *)(v12 + 2 * v13);
        qmemcpy(&igi2_frame.ptVertices[(_DWORD)ptStrip], v1->ptDirect3DQVertex, 28 * v1->nStripLength);
        v15 = 0;
        if ( v1->nStripLength - 2 > 0 )
        {
          v16 = v14;
          do
          {
            *v16 = v15 + v10;
            v17 = v15 & 1;
            v18 = v16 + 1;
            *v18++ = v17 + v15 + v10 + 1;
            *v18 = v15 - v17 + v10 + 2;
            v16 = v18 + 1;
            ++v15;
          }
          while ( v15 < v1->nStripLength - 2 );
        }
      }
      dword_834D9A4 ^= 1u;
    }
  }
  else
  {
    Batch_Flush((unsigned int *)&dword_834D9A8, (void *)(8 * (dword_834D9A4 ^ 1) + 137644872));
  }
}

// source: b/4/pc/pc_direct3dqvertex.c:1356  [size]
void __cdecl Direct3DQVertex_ClipLineCallback(struct QVertexTransformedVertex_t **atVertex, void *pxContext)
{
  if ( !*(_DWORD *)pxContext )
  {
    *(_DWORD *)pxContext = 1;
    **((_DWORD **)pxContext + 4) = LODWORD((*atVertex)->tViewVertex.vX);
    *(float *)(*((_DWORD *)pxContext + 4) + 4) = (*atVertex)->tViewVertex.vY;
    *(float *)(*((_DWORD *)pxContext + 4) + 8) = 1.0 / (*atVertex)->tViewVertex.vZ;
    *(float *)(*((_DWORD *)pxContext + 4) + 12) = *(float *)(*((_DWORD *)pxContext + 4) + 8)
                                                * (*atVertex)->tViewVertex.vU;
    *(float *)(*((_DWORD *)pxContext + 4) + 16) = *(float *)(*((_DWORD *)pxContext + 4) + 8)
                                                * (*atVertex)->tViewVertex.vV;
    *(float *)(*((_DWORD *)pxContext + 4) + 20) = *(float *)(*((_DWORD *)pxContext + 4) + 8)
                                                * (*atVertex)->tViewVertex.vA;
    *(float *)(*((_DWORD *)pxContext + 4) + 24) = *(float *)(*((_DWORD *)pxContext + 4) + 8)
                                                * (*atVertex)->tViewVertex.vR;
    *(float *)(*((_DWORD *)pxContext + 4) + 28) = *(float *)(*((_DWORD *)pxContext + 4) + 8)
                                                * (*atVertex)->tViewVertex.vG;
    *(float *)(*((_DWORD *)pxContext + 4) + 32) = *(float *)(*((_DWORD *)pxContext + 4) + 8)
                                                * (*atVertex)->tViewVertex.vB;
    *(float *)(*((_DWORD *)pxContext + 4) + 36) = atVertex[1]->tViewVertex.vX;
    *(float *)(*((_DWORD *)pxContext + 4) + 40) = atVertex[1]->tViewVertex.vY;
    *(float *)(*((_DWORD *)pxContext + 4) + 44) = 1.0 / atVertex[1]->tViewVertex.vZ;
    *(float *)(*((_DWORD *)pxContext + 4) + 48) = *(float *)(*((_DWORD *)pxContext + 4) + 44)
                                                * atVertex[1]->tViewVertex.vU;
    *(float *)(*((_DWORD *)pxContext + 4) + 52) = *(float *)(*((_DWORD *)pxContext + 4) + 44)
                                                * atVertex[1]->tViewVertex.vV;
    *(float *)(*((_DWORD *)pxContext + 4) + 56) = *(float *)(*((_DWORD *)pxContext + 4) + 44)
                                                * atVertex[1]->tViewVertex.vA;
    *(float *)(*((_DWORD *)pxContext + 4) + 60) = *(float *)(*((_DWORD *)pxContext + 4) + 44)
                                                * atVertex[1]->tViewVertex.vR;
    *(float *)(*((_DWORD *)pxContext + 4) + 64) = *(float *)(*((_DWORD *)pxContext + 4) + 44)
                                                * atVertex[1]->tViewVertex.vG;
    *(float *)(*((_DWORD *)pxContext + 4) + 68) = *(float *)(*((_DWORD *)pxContext + 4) + 44)
                                                * atVertex[1]->tViewVertex.vB;
    Direct3DQVertex_RegisterClippedStrip((struct QVertexStripContext_s *)pxContext);
  }
}

// source: b/4/pc/pc_direct3dqvertex.c:1405  [size]
void __cdecl Direct3DQVertex_ClipLine(struct QVertexStripContext_s *ptStripContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct QVertexTransformedVertex_t v12; };
    struct { char igi2_o1[40]; struct QVertexTransformedVertex_t v13; };
    struct { char igi2_o2[80]; struct QVertexTransformedVertex_t v14; };
    struct { char igi2_o3[148]; int v15; };
    struct { char igi2_o4[152]; int i; };
    struct { char igi2_o5[156]; struct QVertexTransformedVertex_t atTransformedVertex[2]; };
    struct { char igi2_o6[236]; struct QVertexStripContext_s tStripContext; };
    struct { char igi2_o7[256]; struct QVertex_s atQVertex[2]; };
    char igi2_extent[328];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QVertexStripContext_s *v1; // eax
  unsigned int v2; // ebx
  bool v3; // cc
  struct QVertex_s *v4; // edx
  double vX; // st7
  float *p_vX; // edx
  unsigned int v7; // ebp
  float v8; // eax
  double v9; // st7
  float v10; // ecx
  double v11; // st7

  v1 = ptStripContext;
  qmemcpy(&igi2_frame.tStripContext, ptStripContext, sizeof(igi2_frame.tStripContext));
  v2 = 0;
  igi2_frame.tStripContext.atQVertex = igi2_frame.atQVertex;
  v3 = ptStripContext->nStripLength <= 0;
  igi2_frame.tStripContext.nStripLength = 2;
  igi2_frame.tStripContext.isLine = 0;
  igi2_frame.i = 0;
  if ( !v3 )
  {
    igi2_frame.v15 = 0;
    while ( 1 )
    {
      v4 = v1->atQVertex;
      vX = v4[igi2_frame.v15 / 0x24u].vX;
      p_vX = &v4[igi2_frame.v15 / 0x24u].vX;
      v7 = v2;
      v2 = (vX < RenderContext_tActiveRenderContext.tDisplayAreaMin.vX)
         | (2
          * ((p_vX[1] < (double)RenderContext_tActiveRenderContext.tDisplayAreaMin.vY)
           | (2
            * ((RenderContext_tActiveRenderContext.tDisplayAreaMax.vX + 1.0 < *p_vX)
             | (2 * (RenderContext_tActiveRenderContext.tDisplayAreaMax.vY + 1.0 < p_vX[1]))))));
      if ( igi2_frame.v15 > 0 )
      {
        if ( v7 | v2 )
        {
          if ( (v2 & v7) == 0 )
          {
            v8 = *(p_vX - 9);
            v9 = 1.0 / *(p_vX - 7);
            igi2_frame.atTransformedVertex[0].tViewVertex.vY = *(p_vX - 8);
            v10 = p_vX[1];
            igi2_frame.atTransformedVertex[0].tViewVertex.vX = v8;
            igi2_frame.atTransformedVertex[1].tViewVertex.vX = *p_vX;
            igi2_frame.atTransformedVertex[1].tViewVertex.vY = v10;
            igi2_frame.atTransformedVertex[0].bOutcode = v7;
            igi2_frame.atTransformedVertex[1].bOutcode = v2;
            igi2_frame.atTransformedVertex[0].tViewVertex.vZ = v9;
            igi2_frame.atTransformedVertex[0].tViewVertex.vU = v9 * *(p_vX - 6);
            igi2_frame.atTransformedVertex[0].tViewVertex.vV = igi2_frame.atTransformedVertex[0].tViewVertex.vZ * *(p_vX - 5);
            igi2_frame.atTransformedVertex[0].tViewVertex.vA = igi2_frame.atTransformedVertex[0].tViewVertex.vZ * *(p_vX - 4);
            igi2_frame.atTransformedVertex[0].tViewVertex.vR = igi2_frame.atTransformedVertex[0].tViewVertex.vZ * *(p_vX - 3);
            igi2_frame.atTransformedVertex[0].tViewVertex.vG = igi2_frame.atTransformedVertex[0].tViewVertex.vZ * *(p_vX - 2);
            igi2_frame.atTransformedVertex[0].tViewVertex.vB = igi2_frame.atTransformedVertex[0].tViewVertex.vZ * *(p_vX - 1);
            v11 = 1.0 / p_vX[2];
            igi2_frame.atTransformedVertex[1].tViewVertex.vZ = v11;
            igi2_frame.atTransformedVertex[1].tViewVertex.vU = v11 * p_vX[3];
            igi2_frame.atTransformedVertex[1].tViewVertex.vV = igi2_frame.atTransformedVertex[1].tViewVertex.vZ * p_vX[4];
            igi2_frame.atTransformedVertex[1].tViewVertex.vA = igi2_frame.atTransformedVertex[1].tViewVertex.vZ * p_vX[5];
            igi2_frame.atTransformedVertex[1].tViewVertex.vR = igi2_frame.atTransformedVertex[1].tViewVertex.vZ * p_vX[6];
            igi2_frame.atTransformedVertex[1].tViewVertex.vG = igi2_frame.atTransformedVertex[1].tViewVertex.vZ * p_vX[7];
            igi2_frame.atTransformedVertex[1].tViewVertex.vB = igi2_frame.atTransformedVertex[1].tViewVertex.vZ * p_vX[8];
            qmemcpy(&igi2_frame.v14, igi2_frame.atTransformedVertex, sizeof(igi2_frame.v14));
            qmemcpy(&igi2_frame.v13, &igi2_frame.atTransformedVertex[1], sizeof(igi2_frame.v13));
            igi2_frame.tStripContext.isLine = 0;
            qmemcpy(&igi2_frame.v12, igi2_frame.atTransformedVertex, sizeof(igi2_frame.v12));
            Direct3DQVertex_CheckTriangle(
              igi2_frame.v12,
              igi2_frame.v13,
              igi2_frame.v14,
              Direct3D_vWorldMinZ,
              Direct3DQVertex_ClipLineCallback,
              &igi2_frame.tStripContext);
          }
        }
        else
        {
          qmemcpy(igi2_frame.atQVertex, p_vX - 9, 0x24u);
          qmemcpy(&igi2_frame.atQVertex[1], p_vX, sizeof(struct QVertex_s));
          igi2_frame.tStripContext.isLine = 1;
          Direct3DQVertex_RegisterClippedStrip(&igi2_frame.tStripContext);
        }
      }
      v3 = ++igi2_frame.i < ptStripContext->nStripLength;
      igi2_frame.v15 += 36;
      if ( !v3 )
        break;
      v1 = ptStripContext;
    }
  }
}

// source: b/4/pc/pc_direct3dqvertex.c:1509  [size]
void __cdecl Direct3DQVertex_ClipStripCallback(struct QVertexTransformedVertex_t **atVertex, void *pxContext)
{
  **((_DWORD **)pxContext + 4) = LODWORD((*atVertex)->tViewVertex.vX);
  *(float *)(*((_DWORD *)pxContext + 4) + 4) = (*atVertex)->tViewVertex.vY;
  *(float *)(*((_DWORD *)pxContext + 4) + 8) = 1.0 / (*atVertex)->tViewVertex.vZ;
  *(float *)(*((_DWORD *)pxContext + 4) + 12) = *(float *)(*((_DWORD *)pxContext + 4) + 8) * (*atVertex)->tViewVertex.vU;
  *(float *)(*((_DWORD *)pxContext + 4) + 16) = *(float *)(*((_DWORD *)pxContext + 4) + 8) * (*atVertex)->tViewVertex.vV;
  *(float *)(*((_DWORD *)pxContext + 4) + 20) = *(float *)(*((_DWORD *)pxContext + 4) + 8) * (*atVertex)->tViewVertex.vA;
  *(float *)(*((_DWORD *)pxContext + 4) + 24) = *(float *)(*((_DWORD *)pxContext + 4) + 8) * (*atVertex)->tViewVertex.vR;
  *(float *)(*((_DWORD *)pxContext + 4) + 28) = *(float *)(*((_DWORD *)pxContext + 4) + 8) * (*atVertex)->tViewVertex.vG;
  *(float *)(*((_DWORD *)pxContext + 4) + 32) = *(float *)(*((_DWORD *)pxContext + 4) + 8) * (*atVertex)->tViewVertex.vB;
  *(float *)(*((_DWORD *)pxContext + 4) + 36) = atVertex[1]->tViewVertex.vX;
  *(float *)(*((_DWORD *)pxContext + 4) + 40) = atVertex[1]->tViewVertex.vY;
  *(float *)(*((_DWORD *)pxContext + 4) + 44) = 1.0 / atVertex[1]->tViewVertex.vZ;
  *(float *)(*((_DWORD *)pxContext + 4) + 48) = *(float *)(*((_DWORD *)pxContext + 4) + 44)
                                              * atVertex[1]->tViewVertex.vU;
  *(float *)(*((_DWORD *)pxContext + 4) + 52) = *(float *)(*((_DWORD *)pxContext + 4) + 44)
                                              * atVertex[1]->tViewVertex.vV;
  *(float *)(*((_DWORD *)pxContext + 4) + 56) = *(float *)(*((_DWORD *)pxContext + 4) + 44)
                                              * atVertex[1]->tViewVertex.vA;
  *(float *)(*((_DWORD *)pxContext + 4) + 60) = *(float *)(*((_DWORD *)pxContext + 4) + 44)
                                              * atVertex[1]->tViewVertex.vR;
  *(float *)(*((_DWORD *)pxContext + 4) + 64) = *(float *)(*((_DWORD *)pxContext + 4) + 44)
                                              * atVertex[1]->tViewVertex.vG;
  *(float *)(*((_DWORD *)pxContext + 4) + 68) = *(float *)(*((_DWORD *)pxContext + 4) + 44)
                                              * atVertex[1]->tViewVertex.vB;
  *(float *)(*((_DWORD *)pxContext + 4) + 72) = atVertex[2]->tViewVertex.vX;
  *(float *)(*((_DWORD *)pxContext + 4) + 76) = atVertex[2]->tViewVertex.vY;
  *(float *)(*((_DWORD *)pxContext + 4) + 80) = 1.0 / atVertex[2]->tViewVertex.vZ;
  *(float *)(*((_DWORD *)pxContext + 4) + 84) = *(float *)(*((_DWORD *)pxContext + 4) + 80)
                                              * atVertex[2]->tViewVertex.vU;
  *(float *)(*((_DWORD *)pxContext + 4) + 88) = *(float *)(*((_DWORD *)pxContext + 4) + 80)
                                              * atVertex[2]->tViewVertex.vV;
  *(float *)(*((_DWORD *)pxContext + 4) + 92) = *(float *)(*((_DWORD *)pxContext + 4) + 80)
                                              * atVertex[2]->tViewVertex.vA;
  *(float *)(*((_DWORD *)pxContext + 4) + 96) = *(float *)(*((_DWORD *)pxContext + 4) + 80)
                                              * atVertex[2]->tViewVertex.vR;
  *(float *)(*((_DWORD *)pxContext + 4) + 100) = *(float *)(*((_DWORD *)pxContext + 4) + 80)
                                               * atVertex[2]->tViewVertex.vG;
  *(float *)(*((_DWORD *)pxContext + 4) + 104) = *(float *)(*((_DWORD *)pxContext + 4) + 80)
                                               * atVertex[2]->tViewVertex.vB;
  Direct3DQVertex_RegisterClippedStrip((struct QVertexStripContext_s *)pxContext);
}

// source: b/4/pc/pc_direct3dqvertex.c:1559  [size]
void __cdecl Direct3DQVertex_ClipStrip(struct QVertexStripContext_s *ptStripContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct QVertexTransformedVertex_t v12; };
    struct { char igi2_o1[40]; struct QVertexTransformedVertex_t v13; };
    struct { char igi2_o2[80]; struct QVertexTransformedVertex_t v14; };
    struct { char igi2_o3[120]; float v15; };
    struct { char igi2_o4[124]; void (__cdecl *v16)(struct QVertexTransformedVertex_t **, void *); };
    struct { char igi2_o5[128]; struct QVertexStripContext_s *p_tStripContext; };
    struct { char igi2_o6[148]; int v18; };
    struct { char igi2_o7[152]; int i; };
    struct { char igi2_o8[156]; int an1[5]; };
    struct { char igi2_o9[176]; struct QVertexStripContext_s tStripContext; };
    struct { char igi2_o10[196]; struct QVertexTransformedVertex_t atTransformedVertex[3]; };
    struct { char igi2_o11[316]; struct QVertex_s atQVertex[3]; };
    char igi2_extent[424];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QVertexStripContext_s *v1; // eax
  int nStripLength; // ecx
  int v3; // ebx
  float *p_vX; // ecx
  int v5; // ebx
  double v6; // st7
  int v7; // eax
  int v8; // eax
  int v9; // esi
  int v10; // eax
  bool v11; // cc

  v1 = ptStripContext;
  qmemcpy(&igi2_frame.tStripContext, ptStripContext, sizeof(igi2_frame.tStripContext));
  igi2_frame.tStripContext.atQVertex = igi2_frame.atQVertex;
  nStripLength = ptStripContext->nStripLength;
  v3 = 0;
  igi2_frame.tStripContext.nStripLength = 3;
  igi2_frame.i = 0;
  if ( nStripLength > 0 )
  {
    igi2_frame.v18 = 0;
    while ( 1 )
    {
      p_vX = &v1->atQVertex[igi2_frame.v18 / 0x24u].vX;
      v5 = v3 > 2 ? 0 : v3;
      v6 = 1.0 / p_vX[2];
      v7 = v5;
      igi2_frame.atTransformedVertex[v7].bOutcode = (*p_vX < (double)RenderContext_tActiveRenderContext.tDisplayAreaMin.vX)
                                       | (2
                                        * ((p_vX[1] < (double)RenderContext_tActiveRenderContext.tDisplayAreaMin.vY)
                                         | (2
                                          * ((RenderContext_tActiveRenderContext.tDisplayAreaMax.vX + 1.0 < *p_vX)
                                           | (2 * (RenderContext_tActiveRenderContext.tDisplayAreaMax.vY + 1.0 < p_vX[1]))))));
      igi2_frame.atTransformedVertex[v7].tViewVertex.vX = *p_vX;
      igi2_frame.atTransformedVertex[v7].tViewVertex.vY = p_vX[1];
      igi2_frame.atTransformedVertex[v7].tViewVertex.vZ = v6;
      igi2_frame.atTransformedVertex[v7].tViewVertex.vU = v6 * p_vX[3];
      igi2_frame.atTransformedVertex[v7].tViewVertex.vV = v6 * p_vX[4];
      igi2_frame.atTransformedVertex[v7].tViewVertex.vA = v6 * p_vX[5];
      igi2_frame.atTransformedVertex[v7].tViewVertex.vR = v6 * p_vX[6];
      igi2_frame.atTransformedVertex[v7].tViewVertex.vG = v6 * p_vX[7];
      igi2_frame.atTransformedVertex[v7].tViewVertex.vB = v6 * p_vX[8];
      if ( igi2_frame.v18 > 36 )
      {
        igi2_frame.an1[1] = 2;
        igi2_frame.an1[4] = 2;
        igi2_frame.an1[0] = 1;
        igi2_frame.an1[3] = 1;
        igi2_frame.p_tStripContext = &igi2_frame.tStripContext;
        igi2_frame.v16 = Direct3DQVertex_ClipStripCallback;
        igi2_frame.v15 = Direct3D_vWorldMinZ;
        igi2_frame.an1[2] = 0;
        v8 = igi2_frame.an1[v5 + 1];
        qmemcpy(&igi2_frame.v14, &igi2_frame.atTransformedVertex[igi2_frame.an1[v5 + 2]], sizeof(igi2_frame.v14));
        v9 = v8;
        v10 = igi2_frame.an1[v5];
        qmemcpy(&igi2_frame.v13, &igi2_frame.atTransformedVertex[v9], sizeof(igi2_frame.v13));
        qmemcpy(&igi2_frame.v12, &igi2_frame.atTransformedVertex[v10], sizeof(igi2_frame.v12));
        Direct3DQVertex_CheckTriangle(
          igi2_frame.v12,
          igi2_frame.v13,
          igi2_frame.v14,
          Direct3D_vWorldMinZ,
          Direct3DQVertex_ClipStripCallback,
          &igi2_frame.tStripContext);
      }
      v3 = v5 + 1;
      v11 = ++igi2_frame.i < ptStripContext->nStripLength;
      igi2_frame.v18 += 36;
      if ( !v11 )
        break;
      v1 = ptStripContext;
    }
  }
}

// source: b/4/pc/pc_direct3dqvertex.c:1614  [size]
struct QVertexStripContext_s *__cdecl Direct3DQVertex_ClipSprite(
        struct QVertexStripContext_s *ptStripContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct QVertexTransformedVertex_t v21; };
    struct { char igi2_o1[40]; struct QVertexTransformedVertex_t v22; };
    struct { char igi2_o2[80]; struct QVertexTransformedVertex_t v23; };
    struct { char igi2_o3[140]; float v24; };
    struct { char igi2_o4[144]; float v25; };
    struct { char igi2_o5[148]; float v26; };
    struct { char igi2_o6[152]; float v27; };
    struct { char igi2_o7[156]; float v28; };
    struct { char igi2_o8[160]; struct QVertexTransformedVertex_t atTransformedVertex[4]; };
    struct { char igi2_o9[320]; struct QVertexStripContext_s tStripContext; };
    struct { char igi2_o10[340]; struct QVertex_s atQVertex[3]; };
    char igi2_extent[448];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QVertex_s *v1; // ecx
  BOOL v2; // edi
  BOOL v3; // esi
  double v4; // st7
  double vX; // st6
  BOOL v6; // edi
  double v7; // st6
  BOOL v8; // edi
  double v9; // st6
  BOOL v10; // eax
  double v11; // st7
  float v12; // edx
  float vY; // eax
  float v14; // edx
  double v15; // st4
  double v16; // st4
  float v17; // edx
  float v18; // eax
  double v19; // st6
  struct QVertexStripContext_s *result; // eax

  qmemcpy(&igi2_frame.tStripContext, ptStripContext, sizeof(igi2_frame.tStripContext));
  igi2_frame.tStripContext.atQVertex = igi2_frame.atQVertex;
  v1 = ptStripContext->atQVertex;
  igi2_frame.tStripContext.nStripLength = 3;
  v2 = v1->vX < (double)RenderContext_tActiveRenderContext.tDisplayAreaMin.vX;
  v3 = v1->vY < (double)RenderContext_tActiveRenderContext.tDisplayAreaMin.vY;
  igi2_frame.v24 = RenderContext_tActiveRenderContext.tDisplayAreaMax.vX + 1.0;
  v4 = RenderContext_tActiveRenderContext.tDisplayAreaMax.vY + 1.0;
  vX = v1[1].vX;
  igi2_frame.atTransformedVertex[0].bOutcode = v2 | (2 * (v3 | (2 * ((v1->vX > (double)igi2_frame.v24) | (2 * (v4 < v1->vY))))));
  v6 = vX < RenderContext_tActiveRenderContext.tDisplayAreaMin.vX;
  v7 = v1->vX;
  igi2_frame.atTransformedVertex[1].bOutcode = v6
                                  | (2
                                   * ((v1->vY < (double)RenderContext_tActiveRenderContext.tDisplayAreaMin.vY)
                                    | (2 * ((v1[1].vX > (double)igi2_frame.v24) | (2 * (v4 < v1->vY))))));
  v8 = v7 < RenderContext_tActiveRenderContext.tDisplayAreaMin.vX;
  v9 = v1[1].vX;
  igi2_frame.atTransformedVertex[2].bOutcode = v8
                                  | (2
                                   * ((v1[1].vY < (double)RenderContext_tActiveRenderContext.tDisplayAreaMin.vY)
                                    | (2 * ((v1->vX > (double)igi2_frame.v24) | (2 * (v4 < v1[1].vY))))));
  v10 = v4 < v1[1].vY;
  v11 = 1.0 / v1->vZ;
  v12 = v1->vX;
  igi2_frame.atTransformedVertex[3].bOutcode = (v9 < RenderContext_tActiveRenderContext.tDisplayAreaMin.vX)
                                  | (2
                                   * ((v1[1].vY < (double)RenderContext_tActiveRenderContext.tDisplayAreaMin.vY)
                                    | (2 * ((v1[1].vX > (double)igi2_frame.v24) | (2 * v10)))));
  vY = v1->vY;
  igi2_frame.atTransformedVertex[0].tViewVertex.vX = v12;
  v14 = v1[1].vX;
  igi2_frame.atTransformedVertex[0].tViewVertex.vY = vY;
  igi2_frame.atTransformedVertex[1].tViewVertex.vX = v14;
  igi2_frame.atTransformedVertex[1].tViewVertex.vY = vY;
  igi2_frame.atTransformedVertex[0].tViewVertex.vZ = v11;
  igi2_frame.atTransformedVertex[0].tViewVertex.vU = v11 * v1->vU;
  igi2_frame.atTransformedVertex[0].tViewVertex.vV = v11 * v1->vV;
  igi2_frame.v24 = v11 * v1->vA;
  igi2_frame.atTransformedVertex[0].tViewVertex.vA = igi2_frame.v24;
  igi2_frame.atTransformedVertex[1].tViewVertex.vA = igi2_frame.v24;
  igi2_frame.v27 = v11 * v1->vR;
  igi2_frame.atTransformedVertex[0].tViewVertex.vR = igi2_frame.v27;
  igi2_frame.atTransformedVertex[1].tViewVertex.vR = igi2_frame.v27;
  igi2_frame.v26 = v11 * v1->vG;
  igi2_frame.atTransformedVertex[0].tViewVertex.vG = igi2_frame.v26;
  igi2_frame.atTransformedVertex[1].tViewVertex.vG = igi2_frame.v26;
  v15 = v11 * v1->vB;
  igi2_frame.atTransformedVertex[2].tViewVertex.vX = v1->vX;
  igi2_frame.v25 = v15;
  igi2_frame.atTransformedVertex[2].tViewVertex.vA = igi2_frame.v24;
  igi2_frame.atTransformedVertex[0].tViewVertex.vB = v15;
  igi2_frame.atTransformedVertex[1].tViewVertex.vZ = v11;
  igi2_frame.atTransformedVertex[1].tViewVertex.vB = igi2_frame.v25;
  v16 = v11 * v1[1].vU;
  igi2_frame.atTransformedVertex[2].tViewVertex.vY = v1[1].vY;
  igi2_frame.atTransformedVertex[2].tViewVertex.vR = igi2_frame.v27;
  igi2_frame.v28 = v16;
  igi2_frame.atTransformedVertex[1].tViewVertex.vU = v16;
  igi2_frame.atTransformedVertex[2].tViewVertex.vG = igi2_frame.v26;
  v17 = v1[1].vX;
  igi2_frame.atTransformedVertex[1].tViewVertex.vV = igi2_frame.atTransformedVertex[0].tViewVertex.vV;
  igi2_frame.atTransformedVertex[2].tViewVertex.vB = igi2_frame.v25;
  v18 = v1[1].vY;
  igi2_frame.atTransformedVertex[2].tViewVertex.vZ = v11;
  igi2_frame.atTransformedVertex[3].tViewVertex.vX = v17;
  igi2_frame.atTransformedVertex[3].tViewVertex.vY = v18;
  igi2_frame.atTransformedVertex[2].tViewVertex.vU = igi2_frame.atTransformedVertex[0].tViewVertex.vU;
  v19 = v11 * v1[1].vV;
  igi2_frame.atTransformedVertex[3].tViewVertex.vU = igi2_frame.v28;
  igi2_frame.atTransformedVertex[2].tViewVertex.vV = v19;
  igi2_frame.atTransformedVertex[3].tViewVertex.vZ = v11;
  igi2_frame.atTransformedVertex[3].tViewVertex.vV = v19;
  igi2_frame.atTransformedVertex[3].tViewVertex.vR = igi2_frame.v27;
  igi2_frame.atTransformedVertex[3].tViewVertex.vG = igi2_frame.v26;
  igi2_frame.atTransformedVertex[3].tViewVertex.vA = igi2_frame.v24;
  igi2_frame.atTransformedVertex[3].tViewVertex.vB = igi2_frame.v25;
  qmemcpy(&igi2_frame.v23, &igi2_frame.atTransformedVertex[2], sizeof(igi2_frame.v23));
  qmemcpy(&igi2_frame.v22, &igi2_frame.atTransformedVertex[1], sizeof(igi2_frame.v22));
  qmemcpy(&igi2_frame.v21, igi2_frame.atTransformedVertex, sizeof(igi2_frame.v21));
  Direct3DQVertex_CheckTriangle(igi2_frame.v21, igi2_frame.v22, igi2_frame.v23, Direct3D_vWorldMinZ, Direct3DQVertex_ClipStripCallback, &igi2_frame.tStripContext);
  qmemcpy(&igi2_frame.v23, &igi2_frame.atTransformedVertex[3], sizeof(igi2_frame.v23));
  qmemcpy(&igi2_frame.v22, &igi2_frame.atTransformedVertex[2], sizeof(igi2_frame.v22));
  qmemcpy(&igi2_frame.v21, &igi2_frame.atTransformedVertex[1], sizeof(igi2_frame.v21));
  Direct3DQVertex_CheckTriangle(igi2_frame.v21, igi2_frame.v22, igi2_frame.v23, Direct3D_vWorldMinZ, Direct3DQVertex_ClipStripCallback, &igi2_frame.tStripContext);
  return result;
}

// source: b/4/pc/pc_direct3dqvertex.c:1729  [size~]
void __cdecl Direct3DQVertex_RegisterClippedStrip(struct QVertexStripContext_s *ptStripContext)
{
  unsigned int bFlags; // eax
  double vZ; // st7
  struct SortRenderList_t *v3; // esi
  int nNumItems; // ecx
  int v5; // eax
  int v6; // ecx
  unsigned __int8 *v7; // esi
  int v8; // edx
  struct TexInfo_s *v9; // ecx
  struct PalInfo *v10; // edx
  int v11; // eax
  double v12; // st7
  struct QVertex_s *atQVertex; // ecx
  double v14; // st7
  float *p_vX; // ecx
  int v16; // edx
  double v17; // st7
  double v18; // st7
  double v19; // st7
  int v20; // eax
  double v21; // st7
  unsigned int v22; // eax
  unsigned int v23; // ebx
  int v24; // eax
  bool v25; // cc
  int nDepth; // eax
  struct RenderPrimitive_s *v27; // eax
  float v28; // [esp+8h] [ebp-20h]
  int v29; // [esp+10h] [ebp-18h]
  int v30; // [esp+14h] [ebp-14h]
  int v31; // [esp+18h] [ebp-10h]
  int v32; // [esp+24h] [ebp-4h]

  bFlags = ptStripContext->bFlags;
  if ( (bFlags & 0x60000) != 0 && SortRender_isActive && (bFlags & 0x40000000) == 0 )
  {
    vZ = ptStripContext->atQVertex->vZ;
    v3 = SortRender_ptActiveList;
    nNumItems = SortRender_ptActiveList->nNumItems;
    v5 = 28 * ptStripContext->nStripLength + 40;
    ++SortRender_ptActiveList->nNumItems;
    v6 = (int)&v3->atItem[nNumItems];
    v7 = &SortRender_anSortBuffer[SortRender_nBufferPos];
    v8 = v5 + SortRender_nBufferPos;
    *(float *)(v6 + 8) = vZ;
    v32 = 1;
    *(_DWORD *)(v6 + 4) = v7;
    SortRender_nBufferPos = v8;
    *(_DWORD *)v6 = Direct3DQVertex_DrawStrip;
    goto LABEL_5;
  }
  v32 = 0;
  if ( ptStripContext->nDepth >= 0 )
  {
    v7 = (unsigned __int8 *)Primitive_ptNextFreePrimitive;
    Primitive_ptNextFreePrimitive = (char *)Primitive_ptNextFreePrimitive + 28 * ptStripContext->nStripLength + 40;
    if ( (char *)Primitive_ptNextFreePrimitive - Primitive_asPrimitive[0] > (char *)Primitive_nMaxPrimitiveUsage )
    {
      Primitive_nMaxPrimitiveUsage = (unsigned int)Primitive_ptNextFreePrimitive - Primitive_asPrimitive[0];
      if ( (char *)Primitive_ptNextFreePrimitive - Primitive_asPrimitive[0] > (char *)dword_6B9E3C )
      {
        v7 = nullptr;
        goto LABEL_32;
      }
    }
LABEL_5:
    if ( !v7 )
      goto LABEL_31;
    goto LABEL_6;
  }
  v7 = Direct3DQVertex_anTempPrimitive;
LABEL_6:
  v9 = QVertex_ptActiveTexture;
  v10 = QVertex_ptActivePalette;
  *((_DWORD *)v7 + 1) = QVertex_eStripPrimType;
  *((_DWORD *)v7 + 3) = v9;
  *((_DWORD *)v7 + 4) = v10;
  *((_DWORD *)v7 + 5) = ptStripContext->bFlags;
  *((_DWORD *)v7 + 7) = ptStripContext->nStripLength;
  *((_DWORD *)v7 + 8) = ptStripContext->isLine;
  v11 = *((_DWORD *)v7 + 7);
  v12 = ptStripContext->atQVertex->vA * 255.0;
  *((_DWORD *)v7 + 9) = v7 + 40;
  v7[24] = (__int64)v12;
  v31 = 0;
  if ( v11 > 0 )
  {
    v30 = 0;
    v29 = 0;
    do
    {
      atQVertex = ptStripContext->atQVertex;
      v14 = atQVertex[v29].vX - 0.5;
      p_vX = &atQVertex[v29].vX;
      v16 = v30 + *((_DWORD *)v7 + 9);
      *(float *)v16 = v14;
      *(float *)(v16 + 4) = p_vX[1] - 0.5;
      if ( p_vX[2] > 0.0 && TransContext_isValid )
      {
        v17 = Direct3D_vD3DMinZ * 1.0099999904632568;
        v28 = Direct3D_vScale * p_vX[2];
        if ( v17 <= v28 )
        {
          if ( Direct3D_vD3DMaxZ >= (double)v28 )
            v17 = v28;
          else
            v17 = Direct3D_vD3DMaxZ;
        }
        v18 = 1.0 / v17;
        *(float *)(v16 + 12) = v18;
        *(float *)(v16 + 8) = (1.0 - v18 * Direct3D_vD3DMinZ)
                            * (Direct3D_vMaxZ - Direct3D_vMinZ)
                            * TransContext_tActiveTransContext.tProjection._33
                            + Direct3D_vMinZ;
      }
      else
      {
        v19 = Direct3D_vD3DMaxZ;
        *(_DWORD *)(v16 + 8) = 1056964608;
        *(float *)(v16 + 12) = 1.0 / ((v19 - Direct3D_vD3DMinZ) * 0.5);
      }
      v20 = *((_DWORD *)v7 + 5);
      v21 = p_vX[5];
      if ( (v20 & 4) != 0 )
      {
        v21 = 0.5;
      }
      else if ( (v20 & 0x20) != 0 )
      {
        v21 = 0.25;
      }
      if ( (v20 & 0x10880024) != 0 )
      {
        v22 = ((unsigned int)(__int64)(p_vX[7] * -255.0)
             + (((unsigned int)(__int64)(p_vX[6] * -255.0) + ((unsigned int)(__int64)(-255.0 * v21) << 8)) << 8)) << 8;
        v23 = (__int64)(p_vX[8] * 255.0);
      }
      else
      {
        v23 = (((65280 - (unsigned int)(__int64)(p_vX[6] * -255.0)) << 8) - (unsigned int)(__int64)(p_vX[7] * -255.0)) << 8;
        v22 = (__int64)(p_vX[8] * -255.0);
      }
      *(_DWORD *)(v16 + 16) = v23 - v22;
      v24 = *((_DWORD *)v7 + 3);
      if ( v24 )
      {
        *(float *)(v16 + 20) = *(float *)(v24 + 16) * p_vX[3];
        *(float *)(v16 + 24) = *(float *)(*((_DWORD *)v7 + 3) + 20) * p_vX[4];
      }
      ++v29;
      v25 = ++v31 < (int)(*((_DWORD *)v7 + 7));
      v30 += 28;
    }
    while ( v25 );
  }
LABEL_31:
  if ( v32 )
    return;
LABEL_32:
  nDepth = ptStripContext->nDepth;
  if ( nDepth >= 0 )
  {
    v27 = &RenderContext_tActiveRenderContext.ptRenderPrimitive_[nDepth];
    *(_DWORD *)v7 = v27->ptNext;
    v27->ptNext = (struct RenderPrimitive_s *)v7;
  }
  else
  {
    if ( v7 )
    {
      RenderMode_tActiveRenderMode.apfRenderModeMethod[*((_DWORD *)v7 + 1)](v7);
      dword_834E068 = (int)v7;
    }
    else
    {
      if ( !dword_834E068 )
        return;
      RenderMode_tActiveRenderMode.apfRenderModeMethod[*(_DWORD *)(dword_834E068 + 4)](nullptr);
      v7 = (unsigned __int8 *)dword_834E068;
    }
    if ( v7 )
      RenderMode_tActiveRenderMode.apfRenderModeMethod[*((_DWORD *)v7 + 1)](nullptr);
  }
}

void __cdecl sub_616080(struct QVertexStripContext_s *ptStripContext)
{
  struct QVertexStripContext_s *v1; // ecx
  int nStripLength; // edi
  int v3; // ebp
  struct QVertex_s *atQVertex; // esi

  v1 = ptStripContext;
  nStripLength = ptStripContext->nStripLength;
  v3 = 0;
  if ( nStripLength > 0 )
  {
    atQVertex = ptStripContext->atQVertex;
    do
    {
      v3 |= (atQVertex->vX < (double)RenderContext_tActiveRenderContext.tDisplayAreaMin.vX)
          | (2
           * ((atQVertex->vY < (double)RenderContext_tActiveRenderContext.tDisplayAreaMin.vY)
            | (2
             * ((atQVertex->vX > RenderContext_tActiveRenderContext.tDisplayAreaMax.vX + 1.0)
              | (2 * (RenderContext_tActiveRenderContext.tDisplayAreaMax.vY + 1.0 < atQVertex->vY))))));
      ++atQVertex;
      --nStripLength;
    }
    while ( nStripLength );
    v1 = ptStripContext;
  }
  if ( v1->isLine )
  {
    if ( v3 )
    {
      Direct3DQVertex_ClipLine(v1);
      return;
    }
    goto LABEL_15;
  }
  if ( v1->nStripLength > 2 )
  {
    if ( v3 )
    {
      Direct3DQVertex_ClipStrip(v1);
      return;
    }
    goto LABEL_15;
  }
  if ( !v3 )
  {
LABEL_15:
    Direct3DQVertex_RegisterClippedStrip(v1);
    return;
  }
  if ( (v1->bFlags & 0x60000) == 0 )
  {
    v1->atQVertex->vZ = 1.0;
    v1->atQVertex[1].vZ = 1.0;
  }
  Direct3DQVertex_ClipSprite(v1);
}

// source: b/4/pc/pc_direct3dqvertex.c:1959  [size]
void __cdecl Direct3DQVertex_Close()
{
  ;
}
