/* e/3/sectorobject.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: e/3/sectorobject.c:171  [anchor-hash]
struct QTask_s *__cdecl Sector_GetFirstAttachObject(struct Sector_s *ptSector)
{
  struct QTask_s *ptMagicObjContainer; // eax

  ptMagicObjContainer = ptSector->tRigidDynCubeObj.tModelObj.ptMagicObjContainer;
  if ( ptMagicObjContainer )
    return ptMagicObjContainer->tQTaskChildren.ptHead->ptNext != nullptr
         ? ptMagicObjContainer->tQTaskChildren.ptHead
         : nullptr;
  else
    return nullptr;
}

// source: e/3/sectorobject.c:202  [anchor-mhash]
void __cdecl SectorObject_CheckTriangle(
        struct MultiMesh_TransformedVertex_t tVertex0,
        struct MultiMesh_TransformedVertex_t tVertex1,
        struct MultiMesh_TransformedVertex_t tVertex2,
        struct CheckTriangleContext_t *ptContext,
        float vClipZ)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct MultiMesh_TransformedVertex_t v144; };
    struct { char igi2_o1[28]; struct MultiMesh_TransformedVertex_t v145; };
    struct { char igi2_o2[56]; struct MultiMesh_TransformedVertex_t v146; };
    struct { char igi2_o3[84]; struct CheckTriangleContext_t *v147; };
    struct { char igi2_o4[88]; float v148; };
    struct { char igi2_o5[108]; struct MultiMesh_TransformedVertex_t *ptOK1; };
    struct { char igi2_o6[112]; struct MultiMesh_TransformedVertex_t tClipped1; };
    char igi2_extent[140];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  char bOutcode; // dl
  char v6; // al
  char v7; // cl
  char v8; // bl
  unsigned int v9; // ebp
  struct MultiMesh_TransformedVertex_t *p_tVertex2; // eax
  struct MultiMesh_TransformedVertex_t *v11; // edx
  struct MultiMesh_TransformedVertex_t *p_tVertex0; // esi
  struct MultiMesh_TransformedVertex_t *p_tVertex1; // ecx
  double v14; // st7
  double v15; // st7
  double v16; // st7
  double v17; // st7
  BOOL v18; // ebp
  BOOL v19; // eax
  double v20; // st7
  double v21; // st7
  double v22; // st7
  double v23; // st7
  double v24; // st7
  struct MultiMesh_TransformedVertex_t *v25; // ebx
  struct MultiMesh_TransformedVertex_t *v26; // eax
  struct MultiMesh_TransformedVertex_t *v27; // edx
  double v28; // st7
  double v29; // st6
  double v30; // st7
  double v31; // st7
  double v32; // st7
  double v33; // st7
  BOOL v34; // esi
  BOOL v35; // eax
  double vZ; // st7
  double v37; // st7
  double v38; // st6
  double v39; // st7
  double v40; // st7
  double v41; // st6
  int v42; // edx
  int v43; // ecx
  struct MultiMesh_TransformedVertex_t *v44; // eax
  struct MultiMesh_TransformedVertex_t *v45; // edx
  struct MultiMesh_TransformedVertex_t *v46; // esi
  struct MultiMesh_TransformedVertex_t *v47; // ecx
  double v48; // st7
  double v49; // st7
  unsigned int v50; // ebp
  struct MultiMesh_TransformedVertex_t *v51; // ebx
  struct MultiMesh_TransformedVertex_t *v52; // eax
  struct MultiMesh_TransformedVertex_t *v53; // edx
  struct MultiMesh_TransformedVertex_t *v54; // ecx
  double v55; // st7
  double v56; // st6
  double v57; // rtt
  double vX; // st7
  double v59; // st6
  double v60; // st7
  int v61; // edx
  int v62; // ecx
  struct MultiMesh_TransformedVertex_t *v63; // eax
  struct MultiMesh_TransformedVertex_t *v64; // edx
  struct MultiMesh_TransformedVertex_t *v65; // esi
  struct MultiMesh_TransformedVertex_t *v66; // ecx
  double v67; // st7
  double v68; // st7
  unsigned int v69; // ebp
  struct MultiMesh_TransformedVertex_t *v70; // ebx
  struct MultiMesh_TransformedVertex_t *v71; // eax
  struct MultiMesh_TransformedVertex_t *v72; // edx
  double v73; // st7
  double v74; // st6
  double v75; // st7
  double vY; // st7
  double v77; // st7
  double v78; // st6
  int v79; // edx
  int v80; // ecx
  struct MultiMesh_TransformedVertex_t *v81; // eax
  struct MultiMesh_TransformedVertex_t *v82; // edx
  struct MultiMesh_TransformedVertex_t *v83; // esi
  struct MultiMesh_TransformedVertex_t *v84; // ecx
  double v85; // st7
  double v86; // st7
  unsigned int v87; // ebp
  struct MultiMesh_TransformedVertex_t *v88; // eax
  struct MultiMesh_TransformedVertex_t *v89; // ecx
  struct MultiMesh_TransformedVertex_t *v90; // edx
  double v91; // st7
  double v92; // st6
  double v93; // rt0
  double v94; // st7
  double v95; // st6
  double v96; // st7
  int v97; // edx
  int v98; // ecx
  struct MultiMesh_TransformedVertex_t *v99; // eax
  struct MultiMesh_TransformedVertex_t *v100; // ecx
  struct MultiMesh_TransformedVertex_t *v101; // edx
  struct MultiMesh_TransformedVertex_t *v102; // esi
  double v103; // st7
  double v104; // st6
  double v105; // st7
  double v106; // st6
  unsigned int v107; // ebp
  struct MultiMesh_TransformedVertex_t *v108; // edx
  struct MultiMesh_TransformedVertex_t *v109; // ebx
  struct MultiMesh_TransformedVertex_t *v110; // eax
  double v111; // st7
  double v112; // st6
  double v113; // st7
  double v114; // st6
  struct CheckTriangleContext_t *v115; // ecx
  double v116; // st7
  double v117; // st6
  double v118; // st6
  struct CheckTriangleContext_t *v119; // edx
  struct real32x2_t *ptMax; // ecx
  double v121; // st7
  struct real32x2_t *v122; // ecx
  double v123; // st7
  float *p_vX; // ecx
  double v125; // st7
  struct real32x2_t *ptMin; // ecx
  double v127; // st7
  float *v128; // ecx
  double v129; // st7
  struct real32x2_t *v130; // ecx
  double v131; // st7
  float *v132; // ecx
  double v133; // st7
  struct real32x2_t *v134; // ecx
  double v135; // st7
  float *v136; // ecx
  double v137; // st7
  struct real32x2_t *v138; // ecx
  double v139; // st7
  float *v140; // ecx
  double v141; // st7
  struct real32x2_t *v142; // ecx
  double v143; // st7

  bOutcode = tVertex0.bOutcode;
  v6 = tVertex2.bOutcode;
  ++dword_7B7A53C;
  v7 = tVertex1.bOutcode;
  v8 = LOBYTE(tVertex2.bOutcode) | LOBYTE(tVertex1.bOutcode) | LOBYTE(tVertex0.bOutcode);
  v9 = tVertex2.bOutcode & tVertex1.bOutcode & tVertex0.bOutcode;
  if ( !v9 )
  {
    if ( (v8 & 0x10) != 0 )
    {
      if ( (((tVertex1.bOutcode & 0x10) + (tVertex0.bOutcode & 0x10) + (tVertex2.bOutcode & 0x10)) & 0xFFFFFFF0) == 0x20 )
      {
        if ( (tVertex0.bOutcode & 0x10) != 0 )
        {
          if ( (tVertex1.bOutcode & 0x10) != 0 )
          {
            p_tVertex2 = &tVertex2;
            v11 = &tVertex2;
            p_tVertex0 = &tVertex0;
            p_tVertex1 = &tVertex1;
          }
          else
          {
            p_tVertex2 = &tVertex1;
            v11 = &tVertex1;
            p_tVertex0 = &tVertex2;
            p_tVertex1 = &tVertex0;
          }
        }
        else
        {
          p_tVertex2 = &tVertex0;
          v11 = &tVertex0;
          p_tVertex0 = &tVertex1;
          p_tVertex1 = &tVertex2;
        }
        v14 = (vClipZ - p_tVertex2->tRotated.vZ) / (p_tVertex0->tRotated.vZ - p_tVertex2->tRotated.vZ);
        p_tVertex0->tRotated.vX = (p_tVertex0->tRotated.vX - p_tVertex2->tRotated.vX) * v14 + p_tVertex2->tRotated.vX;
        p_tVertex0->tRotated.vY = (p_tVertex0->tRotated.vY - p_tVertex2->tRotated.vY) * v14 + p_tVertex2->tRotated.vY;
        v15 = v14 * (p_tVertex0->tRotated.vZ - p_tVertex2->tRotated.vZ) + p_tVertex2->tRotated.vZ;
        p_tVertex0->tRotated.vZ = v15;
        v16 = 1.0 / v15;
        p_tVertex0->tProjected.vZ = v16;
        p_tVertex0->tProjected.vX = v16 * TransContext_tActiveTransContext.vScreenFOVX * p_tVertex0->tRotated.vX
                                  + TransContext_tActiveTransContext.vScreenOriginX;
        v17 = p_tVertex0->tProjected.vZ * p_tVertex0->tRotated.vY * TransContext_tActiveTransContext.vScreenFOVY
            + TransContext_tActiveTransContext.vScreenOriginY;
        p_tVertex0->tProjected.vY = v17;
        v18 = v17 < RenderContext_tActiveRenderContext.tDisplayAreaMin.vY;
        v19 = v17 > RenderContext_tActiveRenderContext.tDisplayAreaMax.vY;
        v20 = vClipZ;
        p_tVertex0->bOutcode = (p_tVertex0->tProjected.vX < (double)RenderContext_tActiveRenderContext.tDisplayAreaMin.vX)
                             | (2
                              * (v18
                               | (2
                                * ((p_tVertex0->tProjected.vX > (double)RenderContext_tActiveRenderContext.tDisplayAreaMax.vX)
                                 | (2 * v19)))));
        v21 = (v20 - v11->tRotated.vZ) / (p_tVertex1->tRotated.vZ - v11->tRotated.vZ);
        p_tVertex1->tRotated.vX = (p_tVertex1->tRotated.vX - v11->tRotated.vX) * v21 + v11->tRotated.vX;
        p_tVertex1->tRotated.vY = (p_tVertex1->tRotated.vY - v11->tRotated.vY) * v21 + v11->tRotated.vY;
        v22 = v21 * (p_tVertex1->tRotated.vZ - v11->tRotated.vZ) + v11->tRotated.vZ;
        p_tVertex1->tRotated.vZ = v22;
        v23 = 1.0 / v22;
        p_tVertex1->tProjected.vZ = v23;
        p_tVertex1->tProjected.vX = v23 * p_tVertex1->tRotated.vX * TransContext_tActiveTransContext.vScreenFOVX
                                  + TransContext_tActiveTransContext.vScreenOriginX;
        v24 = p_tVertex1->tProjected.vZ * p_tVertex1->tRotated.vY * TransContext_tActiveTransContext.vScreenFOVY
            + TransContext_tActiveTransContext.vScreenOriginY;
        p_tVertex1->tProjected.vY = v24;
        p_tVertex1->bOutcode = (p_tVertex1->tProjected.vX < (double)RenderContext_tActiveRenderContext.tDisplayAreaMin.vX)
                             | (2
                              * ((v24 < RenderContext_tActiveRenderContext.tDisplayAreaMin.vY)
                               | (2
                                * ((p_tVertex1->tProjected.vX > (double)RenderContext_tActiveRenderContext.tDisplayAreaMax.vX)
                                 | (2 * (v24 > RenderContext_tActiveRenderContext.tDisplayAreaMax.vY))))));
        bOutcode = tVertex0.bOutcode;
        v7 = tVertex1.bOutcode;
        v6 = tVertex2.bOutcode;
        v8 = LOBYTE(tVertex2.bOutcode) | LOBYTE(tVertex1.bOutcode) | LOBYTE(tVertex0.bOutcode);
        v9 = tVertex2.bOutcode & tVertex1.bOutcode & tVertex0.bOutcode;
      }
      else
      {
        if ( (tVertex0.bOutcode & 0x10) != 0 )
        {
          v25 = &tVertex2;
          v26 = &tVertex1;
          igi2_frame.ptOK1 = &tVertex2;
          v27 = &tVertex0;
        }
        else
        {
          v27 = &tVertex1;
          if ( (tVertex1.bOutcode & 0x10) != 0 )
          {
            v26 = &tVertex2;
            igi2_frame.ptOK1 = &tVertex0;
          }
          else
          {
            igi2_frame.ptOK1 = &tVertex1;
            v26 = &tVertex0;
            v27 = &tVertex2;
          }
          v25 = igi2_frame.ptOK1;
        }
        v28 = vClipZ - v26->tRotated.vZ;
        v29 = v27->tRotated.vZ - v26->tRotated.vZ;
        qmemcpy(&igi2_frame.tClipped1, v27, sizeof(igi2_frame.tClipped1));
        v30 = v28 / v29;
        v27->tRotated.vX = (v27->tRotated.vX - v26->tRotated.vX) * v30 + v26->tRotated.vX;
        v27->tRotated.vY = (v27->tRotated.vY - v26->tRotated.vY) * v30 + v26->tRotated.vY;
        v31 = v30 * (v27->tRotated.vZ - v26->tRotated.vZ) + v26->tRotated.vZ;
        v27->tRotated.vZ = v31;
        v32 = 1.0 / v31;
        v27->tProjected.vZ = v32;
        v27->tProjected.vX = v32 * v27->tRotated.vX * TransContext_tActiveTransContext.vScreenFOVX
                           + TransContext_tActiveTransContext.vScreenOriginX;
        v33 = TransContext_tActiveTransContext.vScreenFOVY * v27->tProjected.vZ * v27->tRotated.vY
            + TransContext_tActiveTransContext.vScreenOriginY;
        v27->tProjected.vY = v33;
        v34 = v33 < RenderContext_tActiveRenderContext.tDisplayAreaMin.vY;
        v35 = v33 > RenderContext_tActiveRenderContext.tDisplayAreaMax.vY;
        vZ = igi2_frame.tClipped1.tRotated.vZ;
        v27->bOutcode = (v27->tProjected.vX < (double)RenderContext_tActiveRenderContext.tDisplayAreaMin.vX)
                      | (2
                       * (v34
                        | (2
                         * ((v27->tProjected.vX > (double)RenderContext_tActiveRenderContext.tDisplayAreaMax.vX)
                          | (2 * v35)))));
        v37 = vZ - v25->tRotated.vZ;
        v38 = (vClipZ - v25->tRotated.vZ) / v37;
        igi2_frame.tClipped1.tRotated.vX = (igi2_frame.tClipped1.tRotated.vX - v25->tRotated.vX) * v38 + v25->tRotated.vX;
        igi2_frame.tClipped1.tRotated.vY = (igi2_frame.tClipped1.tRotated.vY - v25->tRotated.vY) * v38 + v25->tRotated.vY;
        igi2_frame.tClipped1.tRotated.vZ = v37 * v38 + v25->tRotated.vZ;
        v39 = 1.0 / igi2_frame.tClipped1.tRotated.vZ;
        igi2_frame.tClipped1.tProjected.vZ = v39;
        v40 = v39 * igi2_frame.tClipped1.tRotated.vX * TransContext_tActiveTransContext.vScreenFOVX
            + TransContext_tActiveTransContext.vScreenOriginX;
        igi2_frame.tClipped1.tProjected.vX = v40;
        v41 = igi2_frame.tClipped1.tProjected.vZ * igi2_frame.tClipped1.tRotated.vY * TransContext_tActiveTransContext.vScreenFOVY
            + TransContext_tActiveTransContext.vScreenOriginY;
        igi2_frame.tClipped1.tProjected.vY = v41;
        igi2_frame.tClipped1.bOutcode = (v40 < RenderContext_tActiveRenderContext.tDisplayAreaMin.vX)
                           | (2
                            * ((v41 < RenderContext_tActiveRenderContext.tDisplayAreaMin.vY)
                             | (2
                              * ((v40 > RenderContext_tActiveRenderContext.tDisplayAreaMax.vX)
                               | (2
                                * (igi2_frame.tClipped1.tProjected.vY > (double)RenderContext_tActiveRenderContext.tDisplayAreaMax.vY))))));
        v9 = tVertex2.bOutcode & tVertex1.bOutcode & tVertex0.bOutcode;
        v8 = LOBYTE(tVertex2.bOutcode) | LOBYTE(tVertex1.bOutcode) | LOBYTE(tVertex0.bOutcode);
        qmemcpy(&igi2_frame.v146, v27, sizeof(igi2_frame.v146));
        qmemcpy(&igi2_frame.v145, &igi2_frame.tClipped1, sizeof(igi2_frame.v145));
        qmemcpy(&igi2_frame.v144, igi2_frame.ptOK1, sizeof(igi2_frame.v144));
        SectorObject_CheckTriangle(igi2_frame.v144, igi2_frame.v145, igi2_frame.v146, ptContext, vClipZ);
        v6 = tVertex2.bOutcode;
        v7 = tVertex1.bOutcode;
        bOutcode = tVertex0.bOutcode;
      }
    }
    if ( !v9 )
    {
      if ( (v8 & 1) == 0 )
        goto LABEL_34;
      v42 = bOutcode & 1;
      v43 = v7 & 1;
      if ( v43 + v42 + (v6 & 1) == 2 )
      {
        if ( v42 )
        {
          if ( v43 )
          {
            v44 = &tVertex2;
            v45 = &tVertex2;
            v46 = &tVertex0;
            v47 = &tVertex1;
          }
          else
          {
            v44 = &tVertex1;
            v45 = &tVertex1;
            v46 = &tVertex2;
            v47 = &tVertex0;
          }
        }
        else
        {
          v44 = &tVertex0;
          v45 = &tVertex0;
          v46 = &tVertex1;
          v47 = &tVertex2;
        }
        v48 = (RenderContext_tActiveRenderContext.tDisplayAreaMin.vX - v44->tProjected.vX)
            / (v46->tProjected.vX - v44->tProjected.vX);
        v46->tProjected.vX = (v46->tProjected.vX - v44->tProjected.vX) * v48 + v44->tProjected.vX;
        v46->tProjected.vY = (v46->tProjected.vY - v44->tProjected.vY) * v48 + v44->tProjected.vY;
        v46->tProjected.vZ = (v46->tProjected.vZ - v44->tProjected.vZ) * v48 + v44->tProjected.vZ;
        v46->bOutcode = 2
                      * ((v46->tProjected.vY < (double)RenderContext_tActiveRenderContext.tDisplayAreaMin.vY)
                       | (2
                        * ((v46->tProjected.vX > (double)RenderContext_tActiveRenderContext.tDisplayAreaMax.vX)
                         | (2 * (v46->tProjected.vY > (double)RenderContext_tActiveRenderContext.tDisplayAreaMax.vY)))));
        v49 = (RenderContext_tActiveRenderContext.tDisplayAreaMin.vX - v45->tProjected.vX)
            / (v47->tProjected.vX - v45->tProjected.vX);
        v47->tProjected.vX = (v47->tProjected.vX - v45->tProjected.vX) * v49 + v45->tProjected.vX;
        v47->tProjected.vY = (v47->tProjected.vY - v45->tProjected.vY) * v49 + v45->tProjected.vY;
        v47->tProjected.vZ = (v47->tProjected.vZ - v45->tProjected.vZ) * v49 + v45->tProjected.vZ;
        v47->bOutcode = 2
                      * ((v47->tProjected.vY < (double)RenderContext_tActiveRenderContext.tDisplayAreaMin.vY)
                       | (2
                        * ((v47->tProjected.vX > (double)RenderContext_tActiveRenderContext.tDisplayAreaMax.vX)
                         | (2 * (v47->tProjected.vY > (double)RenderContext_tActiveRenderContext.tDisplayAreaMax.vY)))));
        bOutcode = tVertex0.bOutcode;
        v7 = tVertex1.bOutcode;
        v6 = tVertex2.bOutcode;
        v8 = LOBYTE(tVertex2.bOutcode) | LOBYTE(tVertex1.bOutcode) | LOBYTE(tVertex0.bOutcode);
        v50 = tVertex2.bOutcode & tVertex1.bOutcode & tVertex0.bOutcode;
      }
      else
      {
        if ( v42 )
        {
          v51 = &tVertex0;
          v52 = &tVertex1;
          v53 = &tVertex2;
          igi2_frame.ptOK1 = &tVertex0;
        }
        else
        {
          if ( v43 )
          {
            v52 = &tVertex2;
            v53 = &tVertex0;
            v54 = &tVertex1;
          }
          else
          {
            v52 = &tVertex0;
            v53 = &tVertex1;
            v54 = &tVertex2;
          }
          igi2_frame.ptOK1 = v54;
          v51 = v54;
        }
        v55 = v51->tProjected.vX - v52->tProjected.vX;
        v56 = RenderContext_tActiveRenderContext.tDisplayAreaMin.vX - v52->tProjected.vX;
        qmemcpy(&igi2_frame.tClipped1, v51, sizeof(igi2_frame.tClipped1));
        v57 = v56 / v55;
        v51->tProjected.vX = v55 * v57 + v52->tProjected.vX;
        v51->tProjected.vY = (v51->tProjected.vY - v52->tProjected.vY) * v57 + v52->tProjected.vY;
        v51->tProjected.vZ = (v51->tProjected.vZ - v52->tProjected.vZ) * v57 + v52->tProjected.vZ;
        vX = igi2_frame.tClipped1.tProjected.vX;
        v51->bOutcode = 2
                      * ((v51->tProjected.vY < (double)RenderContext_tActiveRenderContext.tDisplayAreaMin.vY)
                       | (2
                        * ((v51->tProjected.vX > (double)RenderContext_tActiveRenderContext.tDisplayAreaMax.vX)
                         | (2 * (v51->tProjected.vY > (double)RenderContext_tActiveRenderContext.tDisplayAreaMax.vY)))));
        v59 = vX - v53->tProjected.vX;
        v60 = (RenderContext_tActiveRenderContext.tDisplayAreaMin.vX - v53->tProjected.vX) / v59;
        igi2_frame.tClipped1.tProjected.vX = v59 * v60 + v53->tProjected.vX;
        igi2_frame.tClipped1.tProjected.vY = (igi2_frame.tClipped1.tProjected.vY - v53->tProjected.vY) * v60 + v53->tProjected.vY;
        igi2_frame.tClipped1.tProjected.vZ = (igi2_frame.tClipped1.tProjected.vZ - v53->tProjected.vZ) * v60 + v53->tProjected.vZ;
        igi2_frame.tClipped1.bOutcode = 2
                           * ((igi2_frame.tClipped1.tProjected.vY < (double)RenderContext_tActiveRenderContext.tDisplayAreaMin.vY)
                            | (2
                             * ((igi2_frame.tClipped1.tProjected.vX > (double)RenderContext_tActiveRenderContext.tDisplayAreaMax.vX)
                              | (2
                               * (igi2_frame.tClipped1.tProjected.vY > (double)RenderContext_tActiveRenderContext.tDisplayAreaMax.vY)))));
        v50 = tVertex2.bOutcode & tVertex1.bOutcode & tVertex0.bOutcode;
        v8 = LOBYTE(tVertex2.bOutcode) | LOBYTE(tVertex1.bOutcode) | LOBYTE(tVertex0.bOutcode);
        qmemcpy(&igi2_frame.v146, igi2_frame.ptOK1, sizeof(igi2_frame.v146));
        qmemcpy(&igi2_frame.v145, &igi2_frame.tClipped1, sizeof(igi2_frame.v145));
        qmemcpy(&igi2_frame.v144, v53, sizeof(igi2_frame.v144));
        SectorObject_CheckTriangle(igi2_frame.v144, igi2_frame.v145, igi2_frame.v146, ptContext, vClipZ);
        v6 = tVertex2.bOutcode;
        v7 = tVertex1.bOutcode;
        bOutcode = tVertex0.bOutcode;
      }
      if ( !v50 )
      {
LABEL_34:
        if ( (v8 & 2) == 0 )
          goto LABEL_50;
        v61 = bOutcode & 2;
        v62 = v7 & 2;
        if ( ((v62 + v61 + (v6 & 2)) & 0xFFFFFFFE) == 4 )
        {
          if ( v61 )
          {
            if ( v62 )
            {
              v63 = &tVertex2;
              v64 = &tVertex2;
              v65 = &tVertex0;
              v66 = &tVertex1;
            }
            else
            {
              v63 = &tVertex1;
              v64 = &tVertex1;
              v65 = &tVertex2;
              v66 = &tVertex0;
            }
          }
          else
          {
            v63 = &tVertex0;
            v64 = &tVertex0;
            v65 = &tVertex1;
            v66 = &tVertex2;
          }
          v67 = (RenderContext_tActiveRenderContext.tDisplayAreaMin.vY - v63->tProjected.vY)
              / (v65->tProjected.vY - v63->tProjected.vY);
          v65->tProjected.vX = (v65->tProjected.vX - v63->tProjected.vX) * v67 + v63->tProjected.vX;
          v65->tProjected.vY = (v65->tProjected.vY - v63->tProjected.vY) * v67 + v63->tProjected.vY;
          v65->tProjected.vZ = (v65->tProjected.vZ - v63->tProjected.vZ) * v67 + v63->tProjected.vZ;
          v65->bOutcode = 4
                        * ((v65->tProjected.vX > (double)RenderContext_tActiveRenderContext.tDisplayAreaMax.vX)
                         | (2 * (v65->tProjected.vY > (double)RenderContext_tActiveRenderContext.tDisplayAreaMax.vY)));
          v68 = (RenderContext_tActiveRenderContext.tDisplayAreaMin.vY - v64->tProjected.vY)
              / (v66->tProjected.vY - v64->tProjected.vY);
          v66->tProjected.vX = (v66->tProjected.vX - v64->tProjected.vX) * v68 + v64->tProjected.vX;
          v66->tProjected.vY = (v66->tProjected.vY - v64->tProjected.vY) * v68 + v64->tProjected.vY;
          v66->tProjected.vZ = (v66->tProjected.vZ - v64->tProjected.vZ) * v68 + v64->tProjected.vZ;
          v66->bOutcode = 4
                        * ((v66->tProjected.vX > (double)RenderContext_tActiveRenderContext.tDisplayAreaMax.vX)
                         | (2 * (v66->tProjected.vY > (double)RenderContext_tActiveRenderContext.tDisplayAreaMax.vY)));
          bOutcode = tVertex0.bOutcode;
          v7 = tVertex1.bOutcode;
          v6 = tVertex2.bOutcode;
          v8 = LOBYTE(tVertex2.bOutcode) | LOBYTE(tVertex1.bOutcode) | LOBYTE(tVertex0.bOutcode);
          v69 = tVertex2.bOutcode & tVertex1.bOutcode & tVertex0.bOutcode;
        }
        else
        {
          if ( v61 )
          {
            v70 = &tVertex2;
            v71 = &tVertex1;
            igi2_frame.ptOK1 = &tVertex2;
            v72 = &tVertex0;
          }
          else
          {
            v72 = &tVertex1;
            if ( v62 )
            {
              v71 = &tVertex2;
              igi2_frame.ptOK1 = &tVertex0;
            }
            else
            {
              igi2_frame.ptOK1 = &tVertex1;
              v71 = &tVertex0;
              v72 = &tVertex2;
            }
            v70 = igi2_frame.ptOK1;
          }
          v73 = RenderContext_tActiveRenderContext.tDisplayAreaMin.vY - v71->tProjected.vY;
          v74 = v72->tProjected.vY - v71->tProjected.vY;
          qmemcpy(&igi2_frame.tClipped1, v72, sizeof(igi2_frame.tClipped1));
          v75 = v73 / v74;
          v72->tProjected.vX = (v72->tProjected.vX - v71->tProjected.vX) * v75 + v71->tProjected.vX;
          v72->tProjected.vY = (v72->tProjected.vY - v71->tProjected.vY) * v75 + v71->tProjected.vY;
          v72->tProjected.vZ = (v72->tProjected.vZ - v71->tProjected.vZ) * v75 + v71->tProjected.vZ;
          vY = igi2_frame.tClipped1.tProjected.vY;
          v72->bOutcode = 4
                        * ((v72->tProjected.vX > (double)RenderContext_tActiveRenderContext.tDisplayAreaMax.vX)
                         | (2 * (v72->tProjected.vY > (double)RenderContext_tActiveRenderContext.tDisplayAreaMax.vY)));
          v77 = vY - v70->tProjected.vY;
          v78 = (RenderContext_tActiveRenderContext.tDisplayAreaMin.vY - v70->tProjected.vY) / v77;
          igi2_frame.tClipped1.tProjected.vX = (igi2_frame.tClipped1.tProjected.vX - v70->tProjected.vX) * v78 + v70->tProjected.vX;
          igi2_frame.tClipped1.tProjected.vY = v77 * v78 + v70->tProjected.vY;
          igi2_frame.tClipped1.tProjected.vZ = (igi2_frame.tClipped1.tProjected.vZ - v70->tProjected.vZ) * v78 + v70->tProjected.vZ;
          igi2_frame.tClipped1.bOutcode = 4
                             * ((igi2_frame.tClipped1.tProjected.vX > (double)RenderContext_tActiveRenderContext.tDisplayAreaMax.vX)
                              | (2
                               * (igi2_frame.tClipped1.tProjected.vY > (double)RenderContext_tActiveRenderContext.tDisplayAreaMax.vY)));
          v69 = tVertex2.bOutcode & tVertex1.bOutcode & tVertex0.bOutcode;
          v8 = LOBYTE(tVertex2.bOutcode) | LOBYTE(tVertex1.bOutcode) | LOBYTE(tVertex0.bOutcode);
          qmemcpy(&igi2_frame.v146, v72, sizeof(igi2_frame.v146));
          qmemcpy(&igi2_frame.v145, &igi2_frame.tClipped1, sizeof(igi2_frame.v145));
          qmemcpy(&igi2_frame.v144, igi2_frame.ptOK1, sizeof(igi2_frame.v144));
          SectorObject_CheckTriangle(igi2_frame.v144, igi2_frame.v145, igi2_frame.v146, ptContext, vClipZ);
          v6 = tVertex2.bOutcode;
          v7 = tVertex1.bOutcode;
          bOutcode = tVertex0.bOutcode;
        }
        if ( !v69 )
        {
LABEL_50:
          if ( (v8 & 4) == 0 )
          {
LABEL_66:
            if ( (v8 & 8) == 0 )
              goto LABEL_81;
            v97 = bOutcode & 8;
            v98 = v7 & 8;
            if ( ((v98 + v97 + (v6 & 8)) & 0xFFFFFFF8) == 0x10 )
            {
              if ( v97 )
              {
                if ( v98 )
                {
                  v99 = &tVertex2;
                  v100 = &tVertex2;
                  v101 = &tVertex0;
                  v102 = &tVertex1;
                }
                else
                {
                  v99 = &tVertex1;
                  v100 = &tVertex1;
                  v101 = &tVertex2;
                  v102 = &tVertex0;
                }
              }
              else
              {
                v99 = &tVertex0;
                v100 = &tVertex0;
                v101 = &tVertex1;
                v102 = &tVertex2;
              }
              v103 = (RenderContext_tActiveRenderContext.tDisplayAreaMax.vY - v99->tProjected.vY)
                   / (v101->tProjected.vY - v99->tProjected.vY);
              v101->tProjected.vX = (v101->tProjected.vX - v99->tProjected.vX) * v103 + v99->tProjected.vX;
              v101->tProjected.vY = (v101->tProjected.vY - v99->tProjected.vY) * v103 + v99->tProjected.vY;
              v104 = (v101->tProjected.vZ - v99->tProjected.vZ) * v103 + v99->tProjected.vZ;
              v101->bOutcode = 0;
              v101->tProjected.vZ = v104;
              v105 = (RenderContext_tActiveRenderContext.tDisplayAreaMax.vY - v100->tProjected.vY)
                   / (v102->tProjected.vY - v100->tProjected.vY);
              v102->tProjected.vX = (v102->tProjected.vX - v100->tProjected.vX) * v105 + v100->tProjected.vX;
              v102->tProjected.vY = (v102->tProjected.vY - v100->tProjected.vY) * v105 + v100->tProjected.vY;
              v106 = (v102->tProjected.vZ - v100->tProjected.vZ) * v105 + v100->tProjected.vZ;
              v102->bOutcode = 0;
              v102->tProjected.vZ = v106;
              v107 = tVertex2.bOutcode & tVertex1.bOutcode & tVertex0.bOutcode;
            }
            else
            {
              if ( v97 )
              {
                v108 = &tVertex1;
                v109 = &tVertex2;
                v110 = &tVertex0;
              }
              else if ( v98 )
              {
                v108 = &tVertex2;
                v109 = &tVertex0;
                v110 = &tVertex1;
              }
              else
              {
                v108 = &tVertex0;
                v109 = &tVertex1;
                v110 = &tVertex2;
              }
              v111 = RenderContext_tActiveRenderContext.tDisplayAreaMax.vY - v108->tProjected.vY;
              v112 = v110->tProjected.vY - v108->tProjected.vY;
              qmemcpy(&igi2_frame.tClipped1, v110, sizeof(igi2_frame.tClipped1));
              v113 = v111 / v112;
              igi2_frame.tClipped1.bOutcode = 0;
              v110->tProjected.vX = (v110->tProjected.vX - v108->tProjected.vX) * v113 + v108->tProjected.vX;
              v110->tProjected.vY = (v110->tProjected.vY - v108->tProjected.vY) * v113 + v108->tProjected.vY;
              v114 = (v110->tProjected.vZ - v108->tProjected.vZ) * v113 + v108->tProjected.vZ;
              v110->bOutcode = 0;
              v115 = ptContext;
              v110->tProjected.vZ = v114;
              v116 = igi2_frame.tClipped1.tProjected.vY - v109->tProjected.vY;
              v107 = tVertex2.bOutcode & tVertex1.bOutcode & tVertex0.bOutcode;
              v117 = RenderContext_tActiveRenderContext.tDisplayAreaMax.vY - v109->tProjected.vY;
              igi2_frame.v148 = vClipZ;
              igi2_frame.v147 = v115;
              v118 = v117 / v116;
              qmemcpy(&igi2_frame.v146, v110, sizeof(igi2_frame.v146));
              igi2_frame.tClipped1.tProjected.vX = (igi2_frame.tClipped1.tProjected.vX - v109->tProjected.vX) * v118 + v109->tProjected.vX;
              igi2_frame.tClipped1.tProjected.vY = v116 * v118 + v109->tProjected.vY;
              igi2_frame.tClipped1.tProjected.vZ = (igi2_frame.tClipped1.tProjected.vZ - v109->tProjected.vZ) * v118 + v109->tProjected.vZ;
              qmemcpy(&igi2_frame.v145, &igi2_frame.tClipped1, sizeof(igi2_frame.v145));
              qmemcpy(&igi2_frame.v144, v109, sizeof(igi2_frame.v144));
              SectorObject_CheckTriangle(igi2_frame.v144, igi2_frame.v145, igi2_frame.v146, v115, vClipZ);
            }
            if ( !v107 )
            {
LABEL_81:
              v119 = ptContext;
              ptMax = ptContext->ptMax;
              if ( ptMax->vX <= (double)tVertex0.tProjected.vX )
                v121 = tVertex0.tProjected.vX;
              else
                v121 = ptMax->vX;
              ptMax->vX = v121;
              v122 = v119->ptMax;
              if ( v122->vY <= (double)tVertex0.tProjected.vY )
                v123 = tVertex0.tProjected.vY;
              else
                v123 = v122->vY;
              v122->vY = v123;
              p_vX = &v119->ptMin->vX;
              if ( v119->ptMin->vX >= (double)tVertex0.tProjected.vX )
                v125 = tVertex0.tProjected.vX;
              else
                v125 = *p_vX;
              *p_vX = v125;
              ptMin = v119->ptMin;
              if ( v119->ptMin->vY >= (double)tVertex0.tProjected.vY )
                v127 = tVertex0.tProjected.vY;
              else
                v127 = ptMin->vY;
              ptMin->vY = v127;
              v128 = &v119->ptMax->vX;
              if ( *v128 <= (double)tVertex1.tProjected.vX )
                v129 = tVertex1.tProjected.vX;
              else
                v129 = *v128;
              *v128 = v129;
              v130 = v119->ptMax;
              if ( v130->vY <= (double)tVertex1.tProjected.vY )
                v131 = tVertex1.tProjected.vY;
              else
                v131 = v130->vY;
              v130->vY = v131;
              v132 = &v119->ptMin->vX;
              if ( v119->ptMin->vX >= (double)tVertex1.tProjected.vX )
                v133 = tVertex1.tProjected.vX;
              else
                v133 = *v132;
              *v132 = v133;
              v134 = v119->ptMin;
              if ( v119->ptMin->vY >= (double)tVertex1.tProjected.vY )
                v135 = tVertex1.tProjected.vY;
              else
                v135 = v134->vY;
              v134->vY = v135;
              v136 = &v119->ptMax->vX;
              if ( *v136 <= (double)tVertex2.tProjected.vX )
                v137 = tVertex2.tProjected.vX;
              else
                v137 = *v136;
              *v136 = v137;
              v138 = v119->ptMax;
              if ( v138->vY <= (double)tVertex2.tProjected.vY )
                v139 = tVertex2.tProjected.vY;
              else
                v139 = v138->vY;
              v138->vY = v139;
              v140 = &v119->ptMin->vX;
              if ( v119->ptMin->vX >= (double)tVertex2.tProjected.vX )
                v141 = tVertex2.tProjected.vX;
              else
                v141 = *v140;
              *v140 = v141;
              v142 = v119->ptMin;
              if ( v119->ptMin->vY >= (double)tVertex2.tProjected.vY )
                v143 = tVertex2.tProjected.vY;
              else
                v143 = v142->vY;
              v142->vY = v143;
            }
            goto LABEL_118;
          }
          v79 = bOutcode & 4;
          v80 = v7 & 4;
          if ( ((v80 + v79 + (v6 & 4)) & 0xFFFFFFFC) == 8 )
          {
            if ( v79 )
            {
              if ( v80 )
              {
                v81 = &tVertex2;
                v82 = &tVertex2;
                v83 = &tVertex0;
                v84 = &tVertex1;
              }
              else
              {
                v81 = &tVertex1;
                v82 = &tVertex1;
                v83 = &tVertex2;
                v84 = &tVertex0;
              }
            }
            else
            {
              v81 = &tVertex0;
              v82 = &tVertex0;
              v83 = &tVertex1;
              v84 = &tVertex2;
            }
            v85 = (RenderContext_tActiveRenderContext.tDisplayAreaMax.vX - v81->tProjected.vX)
                / (v83->tProjected.vX - v81->tProjected.vX);
            v83->tProjected.vX = (v83->tProjected.vX - v81->tProjected.vX) * v85 + v81->tProjected.vX;
            v83->tProjected.vY = (v83->tProjected.vY - v81->tProjected.vY) * v85 + v81->tProjected.vY;
            v83->tProjected.vZ = (v83->tProjected.vZ - v81->tProjected.vZ) * v85 + v81->tProjected.vZ;
            v83->bOutcode = 8 * (v83->tProjected.vY > (double)RenderContext_tActiveRenderContext.tDisplayAreaMax.vY);
            v86 = (RenderContext_tActiveRenderContext.tDisplayAreaMax.vX - v82->tProjected.vX)
                / (v84->tProjected.vX - v82->tProjected.vX);
            v84->tProjected.vX = (v84->tProjected.vX - v82->tProjected.vX) * v86 + v82->tProjected.vX;
            v84->tProjected.vY = (v84->tProjected.vY - v82->tProjected.vY) * v86 + v82->tProjected.vY;
            v84->tProjected.vZ = (v84->tProjected.vZ - v82->tProjected.vZ) * v86 + v82->tProjected.vZ;
            v84->bOutcode = 8 * (v84->tProjected.vY > (double)RenderContext_tActiveRenderContext.tDisplayAreaMax.vY);
            bOutcode = tVertex0.bOutcode;
            v7 = tVertex1.bOutcode;
            v6 = tVertex2.bOutcode;
            v8 = LOBYTE(tVertex2.bOutcode) | LOBYTE(tVertex1.bOutcode) | LOBYTE(tVertex0.bOutcode);
            v87 = tVertex2.bOutcode & tVertex1.bOutcode & tVertex0.bOutcode;
LABEL_65:
            if ( v87 )
              goto LABEL_118;
            goto LABEL_66;
          }
          if ( v79 )
          {
            v88 = &tVertex1;
            v89 = &tVertex2;
            v90 = &tVertex0;
          }
          else
          {
            if ( v80 )
            {
              igi2_frame.ptOK1 = &tVertex0;
              v88 = &tVertex2;
              v90 = &tVertex1;
LABEL_64:
              v91 = v90->tProjected.vX - v88->tProjected.vX;
              v92 = RenderContext_tActiveRenderContext.tDisplayAreaMax.vX - v88->tProjected.vX;
              qmemcpy(&igi2_frame.tClipped1, v90, sizeof(igi2_frame.tClipped1));
              v93 = v92 / v91;
              v90->tProjected.vX = v91 * v93 + v88->tProjected.vX;
              v90->tProjected.vY = (v90->tProjected.vY - v88->tProjected.vY) * v93 + v88->tProjected.vY;
              v90->tProjected.vZ = (v90->tProjected.vZ - v88->tProjected.vZ) * v93 + v88->tProjected.vZ;
              v94 = igi2_frame.tClipped1.tProjected.vX;
              v90->bOutcode = 8 * (v90->tProjected.vY > (double)RenderContext_tActiveRenderContext.tDisplayAreaMax.vY);
              v95 = v94 - igi2_frame.ptOK1->tProjected.vX;
              v96 = (RenderContext_tActiveRenderContext.tDisplayAreaMax.vX - igi2_frame.ptOK1->tProjected.vX) / v95;
              igi2_frame.tClipped1.tProjected.vX = v95 * v96 + igi2_frame.ptOK1->tProjected.vX;
              igi2_frame.tClipped1.tProjected.vY = (igi2_frame.tClipped1.tProjected.vY - igi2_frame.ptOK1->tProjected.vY) * v96 + igi2_frame.ptOK1->tProjected.vY;
              igi2_frame.tClipped1.tProjected.vZ = (igi2_frame.tClipped1.tProjected.vZ - igi2_frame.ptOK1->tProjected.vZ) * v96 + igi2_frame.ptOK1->tProjected.vZ;
              igi2_frame.tClipped1.bOutcode = 8
                                 * (igi2_frame.tClipped1.tProjected.vY > (double)RenderContext_tActiveRenderContext.tDisplayAreaMax.vY);
              v87 = tVertex2.bOutcode & tVertex1.bOutcode & tVertex0.bOutcode;
              v8 = LOBYTE(tVertex2.bOutcode) | LOBYTE(tVertex1.bOutcode) | LOBYTE(tVertex0.bOutcode);
              qmemcpy(&igi2_frame.v146, v90, sizeof(igi2_frame.v146));
              qmemcpy(&igi2_frame.v145, &igi2_frame.tClipped1, sizeof(igi2_frame.v145));
              qmemcpy(&igi2_frame.v144, igi2_frame.ptOK1, sizeof(igi2_frame.v144));
              SectorObject_CheckTriangle(igi2_frame.v144, igi2_frame.v145, igi2_frame.v146, ptContext, vClipZ);
              v6 = tVertex2.bOutcode;
              v7 = tVertex1.bOutcode;
              bOutcode = tVertex0.bOutcode;
              goto LABEL_65;
            }
            v88 = &tVertex0;
            v89 = &tVertex1;
            v90 = &tVertex2;
          }
          igi2_frame.ptOK1 = v89;
          goto LABEL_64;
        }
      }
    }
  }
LABEL_118:
  --dword_7B7A53C;
}

// source: e/3/sectorobject.c:1052  [anchor-mhash]
void __cdecl Sector_CleanUpReferences(struct Sector_s *ptSector)
{
  struct QObjectVector_s *ptInteriorDynCubeObjPool; // eax
  struct QObjectVector_s *i; // esi
  struct DynCubeObj_s **v3; // edx
  struct DynCubeObj_s *v4; // ebx
  int v5; // eax
  unsigned int v6; // ebp
  struct DynCubeObj_s ***v7; // edi
  unsigned int j; // edi
  struct Sector_s **v9; // eax
  struct DynCubeObj_s **pptDynCubeObj; // [esp+0h] [ebp-4h]

  ptInteriorDynCubeObjPool = ptSector->ptInteriorDynCubeObjPool;
  for ( i = SectorObject_tInteriorDynCubeObjPool;
        ptInteriorDynCubeObjPool->nAllocated;
        ptInteriorDynCubeObjPool = ptSector->ptInteriorDynCubeObjPool )
  {
    v3 = (struct DynCubeObj_s **)*ptInteriorDynCubeObjPool->papxElement;
    v4 = *v3;
    v5 = 0;
    v6 = 0;
    for ( pptDynCubeObj = v3; v6 < i->nAllocated; ++v6 )
    {
      if ( v5 )
        break;
      v7 = (struct DynCubeObj_s ***)i->papxElement[v6];
      if ( *v7 == v3 )
      {
        QObjectVector_RemoveElement(
          (struct QObjectVector_s *)v7[1][80],
          *(_DWORD *)((char *)v7[1][80]->tQObj.tQTask.ptParent + (unsigned int)*v7 - 4));
        QObjectVector_RemoveElement(i, *(unsigned int *)((char *)v7 + i->nElementSize - 4));
        v3 = pptDynCubeObj;
        v4->iSector = 0;
        v4->ptSector = nullptr;
        v5 = 1;
      }
    }
  }
  for ( j = 0; j < i->nAllocated; ++j )
  {
    v9 = (struct Sector_s **)i->papxElement[j];
    if ( v9[1] == ptSector )
    {
      QObjectVector_RemoveElement(i, *(unsigned int *)((char *)v9 + i->nElementSize - 4));
      --j;
    }
  }
}

// source: e/3/sectorobject.c:1107  [anchor-mhash]
void __cdecl SectorObject_AddSphere(struct QObjectVector_s *ptSpherePool, struct QTask_s *ptQTask)
{
  struct QTask_s *ptHead; // edi
  int v3; // eax
  _DWORD *v4; // ebx
  unsigned int nAllocated; // eax
  _DWORD *v6; // ecx

  ptHead = ptQTask->tQTaskChildren.ptHead;
  if ( ptHead->ptNext && ptHead )
  {
    do
    {
      if ( QTask_IsQTaskTypeDerived(ptHead->eQTaskType, ModelObj_eQTaskType) )
      {
        v3 = *(_DWORD *)&ptHead[2].eQTaskType;
        if ( v3 )
        {
          v4 = *(_DWORD **)(*(_DWORD *)(*(_DWORD *)v3 + 12) + 12);
          if ( ptSpherePool->nAllocated == ptSpherePool->nSize )
            QObjectVector_Realloc(ptSpherePool, ptSpherePool->nReallocSize);
          nAllocated = ptSpherePool->nAllocated;
          v6 = ptSpherePool->papxElement[nAllocated];
          ptSpherePool->nAllocated = nAllocated + 1;
          *v6 = v4[20];
          v6[1] = v4[21];
          v6[2] = v4[22];
          v6[3] = v4[23];
          SectorObject_AddSphere(ptSpherePool, ptHead);
        }
      }
      ptHead = ptHead->ptNext;
    }
    while ( ptHead && ptHead->ptNext );
  }
}

// source: e/3/sectorobject.c:1148  [anchor-mhash]
void __cdecl SectorObject_GetOptimalInsideSphere(
        struct SectorObject_s *ptSectorObject,
        struct real32x3_t *ptDestPos,
        float *pvDestRadius)
{
  struct QTask_s *ptSectorContainer; // eax
  struct QTask_s *ptHead; // eax
  struct LODVirModel_s *ptLODVirModel; // edi
  struct Mesh3D_Mesh_t *ptMesh; // eax
  void *v8; // esi
  struct QTask_s *v9; // eax
  struct QTask_s *v10; // eax
  struct QTask_s *v11; // edi
  _DWORD *v12; // ebx
  int v13; // eax
  _DWORD *v14; // ecx
  float *p_vX; // edi
  float *v16; // ebx
  struct Sphere_t *v17; // ecx
  struct Sphere_t *v18; // ebp
  int v19; // eax
  float *v20; // edx
  float *v21; // ecx
  double v22; // st6
  double v23; // st5
  double v24; // st3
  long double v25; // st4
  unsigned int v26; // eax
  double v27; // st7
  long double v28; // st4
  long double v29; // st6
  long double v30; // st7
  double v31; // st7
  struct real32x3_t *v32; // eax
  struct QObjectVector_s *v33; // eax
  float vDistance; // [esp+Ch] [ebp-38h]
  struct Sphere_t *ptSphere0; // [esp+10h] [ebp-34h]
  struct Sphere_t *ptSphere0a; // [esp+10h] [ebp-34h]
  float tTempPos0; // [esp+14h] [ebp-30h]
  float tTempPos0_4; // [esp+18h] [ebp-2Ch]
  float tTempPos0_4a; // [esp+18h] [ebp-2Ch]
  float tTempPos0_8; // [esp+1Ch] [ebp-28h]
  float tTempPos0_8a; // [esp+1Ch] [ebp-28h]
  float tTempPos0_8b; // [esp+1Ch] [ebp-28h]
  float tTempPos1; // [esp+20h] [ebp-24h]
  float tTempPos1_4; // [esp+24h] [ebp-20h]
  float tTempPos1_4a; // [esp+24h] [ebp-20h]
  float tTempPos1_8; // [esp+28h] [ebp-1Ch]
  float tDelta; // [esp+2Ch] [ebp-18h]
  float tDelta_4; // [esp+30h] [ebp-14h]
  float tDelta_8; // [esp+34h] [ebp-10h]
  float tNewPos; // [esp+38h] [ebp-Ch]
  float tNewPos_4; // [esp+3Ch] [ebp-8h]
  float tNewPos_8; // [esp+40h] [ebp-4h]

  ptSectorContainer = ptSectorObject->ptSectorContainer;
  if ( ptSectorContainer )
  {
    ptHead = ptSectorContainer->tQTaskChildren.ptHead;
    if ( ptHead->ptNext )
    {
      if ( ptHead )
      {
        v8 = Mem_AllocFn(52, 4);
        *((_DWORD *)v8 + 7) = 1;
        *((_DWORD *)v8 + 10) = 0;
        *((_DWORD *)v8 + 9) = 0;
        *((_DWORD *)v8 + 11) = 0;
        *((_DWORD *)v8 + 12) = 0;
        *((_DWORD *)v8 + 8) = 20;
        *((_DWORD *)v8 + 2) = 0;
        *((_DWORD *)v8 + 1) = 0;
        *(_DWORD *)v8 = 4;
        *((_DWORD *)v8 + 4) = 20;
        *((_DWORD *)v8 + 3) = 0;
        *((_DWORD *)v8 + 5) = 0;
        *((_DWORD *)v8 + 6) = 0;
        MemPool_ReAlloc((struct MemPool_s *)v8, 0x3E8u);
        QObjectVector_Realloc((struct QObjectVector_s *)v8, 0x3E8u);
        v9 = ptSectorObject->ptSectorContainer;
        if ( v9 )
        {
          v10 = v9->tQTaskChildren.ptHead;
          if ( v10->ptNext )
          {
            v11 = v10;
            if ( v10 )
            {
              do
              {
                v12 = *(_DWORD **)(*(_DWORD *)(**(_DWORD **)&v11[2].eQTaskType + 12) + 12);
                if ( *((_DWORD *)v8 + 9) == *((_DWORD *)v8 + 10) )
                  QObjectVector_Realloc((struct QObjectVector_s *)v8, *((_DWORD *)v8 + 11));
                v13 = *((_DWORD *)v8 + 9);
                v14 = *(_DWORD **)(*((_DWORD *)v8 + 12) + 4 * v13);
                *((_DWORD *)v8 + 9) = v13 + 1;
                *v14 = v12[20];
                v14[1] = v12[21];
                v14[2] = v12[22];
                v14[3] = v12[23];
                if ( v11[3].ptNext )
                  SectorObject_AddSphere((struct QObjectVector_s *)v8, v11[3].ptNext);
                v11 = v11->ptNext;
              }
              while ( v11 && v11->ptNext );
            }
          }
        }
        if ( *((_DWORD *)v8 + 9) <= 1u )
        {
LABEL_36:
          v32 = **((struct real32x3_t ***)v8 + 12);
          *ptDestPos = *v32;
          *pvDestRadius = v32[1].vX;
          v33 = QObjectVector_RemoveElement(
                  (struct QObjectVector_s *)v8,
                  *(_DWORD *)((char *)v32 + *((_DWORD *)v8 + 8) - 4));
          QObjectVector_Delete(v33);
          return;
        }
        p_vX = &ptSphere0->tPos.vX;
        v16 = &ptSphere0->tPos.vX;
        while ( 1 )
        {
          v17 = nullptr;
          vDistance = 3.4028234663852886e+38;
          ptSphere0a = nullptr;
          if ( *((_DWORD *)v8 + 9) )
          {
            do
            {
              v18 = nullptr;
              do
              {
                if ( v17 != v18 )
                {
                  v19 = *((_DWORD *)v8 + 12);
                  v20 = *(float **)(v19 + 4 * (_DWORD)v18);
                  v21 = *(float **)(v19 + 4 * (_DWORD)v17);
                  v22 = v20[1] - v21[1];
                  v23 = *v20 - *v21;
                  v24 = v20[2] - v21[2];
                  v25 = sqrt(v23 * v23 + v22 * v22 + v24 * v24);
                  if ( v25 < vDistance )
                  {
                    vDistance = v25;
                    p_vX = v21;
                    v16 = *(float **)(v19 + 4 * (_DWORD)v18);
                  }
                  v17 = ptSphere0a;
                }
                v26 = *((_DWORD *)v8 + 9);
                v18 = (struct Sphere_t *)((char *)v18 + 1);
              }
              while ( (unsigned int)v18 < v26 );
              v17 = (struct Sphere_t *)((char *)v17 + 1);
              ptSphere0a = v17;
            }
            while ( (unsigned int)v17 < v26 );
            if ( vDistance == 0.0 )
              break;
          }
          if ( vDistance + v16[3] < p_vX[3] )
            goto LABEL_34;
          if ( vDistance + p_vX[3] >= v16[3] )
          {
            tDelta = *v16 - *p_vX;
            tDelta_4 = v16[1] - p_vX[1];
            v27 = v16[2] - p_vX[2];
            tDelta_8 = v27;
            v28 = sqrt(tDelta * tDelta + tDelta_4 * tDelta_4 + v27 * v27);
            v29 = p_vX[3] / v28;
            tTempPos0_4 = tDelta_4 * v29;
            tTempPos0_8 = tDelta_8 * v29;
            tTempPos0_8a = -tTempPos0_8;
            tTempPos0 = *p_vX - tDelta * v29;
            tTempPos0_4a = p_vX[1] - tTempPos0_4;
            tTempPos0_8b = tTempPos0_8a + p_vX[2];
            v30 = v16[3] / v28;
            tTempPos1_4 = tDelta_4 * v30;
            tTempPos1_8 = tDelta_8 * v30;
            tTempPos1 = tDelta * v30 + *v16;
            tTempPos1_4a = tTempPos1_4 + v16[1];
            v31 = tTempPos1_8 + v16[2];
            tNewPos = (tTempPos1 - tTempPos0) * 0.5 + tTempPos0;
            *p_vX = tNewPos;
            tNewPos_4 = (tTempPos1_4a - tTempPos0_4a) * 0.5 + tTempPos0_4a;
            p_vX[1] = tNewPos_4;
            tNewPos_8 = (v31 - tTempPos0_8b) * 0.5 + tTempPos0_8b;
            p_vX[2] = tNewPos_8;
            p_vX[3] = sqrt(
                        (tTempPos1 - tNewPos) * (tTempPos1 - tNewPos)
                      + (tTempPos1_4a - tNewPos_4) * (tTempPos1_4a - tNewPos_4)
                      + (v31 - tNewPos_8) * (v31 - tNewPos_8));
LABEL_34:
            QObjectVector_RemoveElement(
              (struct QObjectVector_s *)v8,
              *(_DWORD *)((char *)v16 + *((_DWORD *)v8 + 8) - 4));
            goto LABEL_35;
          }
          QObjectVector_RemoveElement((struct QObjectVector_s *)v8, *(_DWORD *)((char *)p_vX + *((_DWORD *)v8 + 8) - 4));
LABEL_35:
          if ( *((_DWORD *)v8 + 9) <= 1u )
            goto LABEL_36;
        }
        if ( p_vX[3] <= (double)v16[3] )
          p_vX[3] = v16[3];
        else
          p_vX[3] = p_vX[3];
        goto LABEL_34;
      }
    }
  }
  ptLODVirModel = ptSectorObject->tSector.tRigidDynCubeObj.tModelObj.ptLODVirModel;
  if ( ptLODVirModel )
  {
    ptMesh = ptLODVirModel->aptVirModel[0]->ptModel->ptMesh;
    *ptDestPos = ptMesh->tSphere.tPos;
    *pvDestRadius = ptMesh->tSphere.vRadius;
  }
}

// source: e/3/sectorobject.c:1568  [anchor-mhash]
int __cdecl Sector_IsPortalVisible(
        struct Sector_s *ptSector,
        int iLOD,
        int iPortal,
        struct real32x2_t *ptMin,
        struct real32x2_t *ptMax,
        struct real32x2_t *ptDestMin,
        struct real32x2_t *ptDestMax)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct MultiMesh_TransformedVertex_t v60; };
    struct { char igi2_o1[28]; struct MultiMesh_TransformedVertex_t v61; };
    struct { char igi2_o2[56]; struct MultiMesh_TransformedVertex_t v62; };
    struct { char igi2_o3[84]; struct real32x3_t *p_tContext; };
    struct { char igi2_o4[88]; int v64; };
    struct { char igi2_o5[108]; struct real32x3_t tNormal; };
    struct { char igi2_o6[120]; struct real32x3_t tContext; };
    struct { char igi2_o7[132]; float v67; };
    struct { char igi2_o8[136]; struct real32x3_t tEdge1; };
    struct { char igi2_o9[148]; float v69; };
    struct { char igi2_o10[152]; float v70; };
    struct { char igi2_o11[156]; struct real32x3_t Real32x3_Rotate_tTemp; };
    struct { char igi2_o12[168]; struct Mesh3D_Portal_t *ptPortal; };
    struct { char igi2_o13[172]; struct real32x2_t tScreenMin; };
    struct { char igi2_o14[180]; struct real32x2_t tScreenMax; };
    struct { char igi2_o15[188]; int isVertexBeyondZ0; };
    struct { char igi2_o16[192]; struct Mesh3D_Mesh_t *ptMesh; };
    struct { char igi2_o17[196]; struct real64x3_t tWorldPos0; };
    struct { char igi2_o18[220]; struct MultiMesh_TransformedVertex_t atVertex[100]; };
    char igi2_extent[3020];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct LODVirModel_s *ptLODVirModel; // ecx
  struct Mesh3D_Mesh_t *v9; // ecx
  struct Mesh3D_Portal_t *v10; // esi
  char isOpen; // dl
  struct Mesh3D_PortalVertex_t *ptPortalVertex; // ebp
  struct Mesh3D_PortalFace_t *ptPortalFace; // eax
  int iPortalVertex0; // ecx
  struct Mesh3D_PortalFace_t *v15; // eax
  float *p_vX; // edx
  double v17; // st7
  float *v18; // ecx
  double v19; // st6
  float *v20; // eax
  double v21; // st5
  double v22; // st4
  double v23; // st7
  double vX; // st6
  double v25; // st7
  double vY; // st6
  long double v27; // st7
  double v28; // st7
  double v29; // st7
  double v30; // st7
  double v31; // st6
  double v32; // st5
  double v33; // st4
  double v34; // st7
  double v35; // rtt
  double v36; // st4
  float v37; // edi
  float *p_vY; // edx
  float *v39; // ecx
  double v40; // st7
  double v41; // st7
  double v42; // st7
  float *v43; // eax
  double v44; // st6
  double v45; // st5
  double vZ; // st4
  double v47; // st7
  int v48; // edi
  double v49; // st7
  double v50; // st7
  double v51; // st6
  int v52; // ebx
  struct Mesh3D_PortalFace_t *v53; // eax
  int iStartVertex; // edx
  struct MultiMesh_TransformedVertex_t *v55; // esi
  float v56; // edx
  float v57; // ecx
  float v58; // edx

  ptLODVirModel = ptSector->tRigidDynCubeObj.tModelObj.ptLODVirModel;
  igi2_frame.tScreenMin.vX = 3.4028234663852886e+38;
  igi2_frame.tScreenMin.vY = 3.4028234663852886e+38;
  igi2_frame.tScreenMax.vX = -3.4028234663852886e+38;
  igi2_frame.tScreenMax.vY = -3.4028234663852886e+38;
  v9 = ptLODVirModel->aptVirModel[iLOD]->ptModel->ptMesh;
  v10 = &v9->ptPortal[iPortal];
  isOpen = ptSector->atPortalStatus[v10->iPortal].isOpen;
  igi2_frame.ptMesh = v9;
  igi2_frame.ptPortal = v10;
  igi2_frame.isVertexBeyondZ0 = 0;
  if ( !isOpen )
    return 0;
  ptPortalVertex = v9->ptPortalVertex;
  ptPortalFace = v9->ptPortalFace;
  iPortalVertex0 = ptPortalFace[v10->iStartFace].iPortalVertex0;
  v15 = &ptPortalFace[v10->iStartFace];
  p_vX = &ptPortalVertex[v15->iPortalVertex1].tPos.vX;
  iPortalVertex0 *= 3;
  v17 = *p_vX - *(&ptPortalVertex->tPos.vX + iPortalVertex0);
  v18 = &ptPortalVertex->tPos.vX + iPortalVertex0;
  v19 = p_vX[1] - v18[1];
  v20 = &ptPortalVertex[v15->iPortalVertex2].tPos.vX;
  v21 = p_vX[2] - v18[2];
  igi2_frame.tEdge1.vX = *v20 - *v18;
  igi2_frame.tEdge1.vY = v20[1] - v18[1];
  v22 = v20[2] - v18[2];
  igi2_frame.tNormal.vX = v22 * v19 - igi2_frame.tEdge1.vY * v21;
  igi2_frame.tNormal.vY = -(v22 * v17 - igi2_frame.tEdge1.vX * v21);
  v23 = v17 * igi2_frame.tEdge1.vY - igi2_frame.tEdge1.vX * v19;
  igi2_frame.tContext.vX = igi2_frame.tNormal.vX * ptSector->tRigidDynCubeObj.tModelObj.tOrientation.tX.vX
              + v23 * ptSector->tRigidDynCubeObj.tModelObj.tOrientation.tX.vZ
              + igi2_frame.tNormal.vY * ptSector->tRigidDynCubeObj.tModelObj.tOrientation.tX.vY;
  igi2_frame.tContext.vY = igi2_frame.tNormal.vX * ptSector->tRigidDynCubeObj.tModelObj.tOrientation.tY.vX
              + v23 * ptSector->tRigidDynCubeObj.tModelObj.tOrientation.tY.vZ
              + igi2_frame.tNormal.vY * ptSector->tRigidDynCubeObj.tModelObj.tOrientation.tY.vY;
  vX = igi2_frame.tNormal.vX;
  igi2_frame.tNormal.vX = igi2_frame.tContext.vX;
  v25 = vX * ptSector->tRigidDynCubeObj.tModelObj.tOrientation.tZ.vX
      + v23 * ptSector->tRigidDynCubeObj.tModelObj.tOrientation.tZ.vZ;
  vY = igi2_frame.tNormal.vY;
  igi2_frame.tNormal.vY = igi2_frame.tContext.vY;
  igi2_frame.tContext.vZ = v25 + vY * ptSector->tRigidDynCubeObj.tModelObj.tOrientation.tZ.vY;
  igi2_frame.tNormal.vZ = igi2_frame.tContext.vZ;
  if ( igi2_frame.tContext.vX != 0.0 || igi2_frame.tContext.vY != 0.0 || igi2_frame.tContext.vZ != 0.0 )
  {
    v27 = 1.0 / sqrt(igi2_frame.tContext.vZ * igi2_frame.tContext.vZ + igi2_frame.tContext.vX * igi2_frame.tContext.vX + igi2_frame.tContext.vY * igi2_frame.tContext.vY);
    igi2_frame.tNormal.vX = igi2_frame.tContext.vX * v27;
    igi2_frame.tNormal.vY = igi2_frame.tNormal.vY * v27;
    igi2_frame.tNormal.vZ = igi2_frame.tNormal.vZ * v27;
  }
  v28 = ptSector->tRigidDynCubeObj.tModelObj.tOrientation.tX.vX * *v18
      + ptSector->tRigidDynCubeObj.tModelObj.tOrientation.tX.vZ * v18[2]
      + ptSector->tRigidDynCubeObj.tModelObj.tOrientation.tX.vY * v18[1];
  igi2_frame.Real32x3_Rotate_tTemp.vY = v18[1] * ptSector->tRigidDynCubeObj.tModelObj.tOrientation.tY.vY
                           + *v18 * ptSector->tRigidDynCubeObj.tModelObj.tOrientation.tY.vX
                           + v18[2] * ptSector->tRigidDynCubeObj.tModelObj.tOrientation.tY.vZ;
  igi2_frame.Real32x3_Rotate_tTemp.vZ = ptSector->tRigidDynCubeObj.tModelObj.tOrientation.tZ.vX * *v18
                           + ptSector->tRigidDynCubeObj.tModelObj.tOrientation.tZ.vZ * v18[2]
                           + ptSector->tRigidDynCubeObj.tModelObj.tOrientation.tZ.vY * v18[1];
  v29 = v28 + ptSector->tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos.vX;
  igi2_frame.tWorldPos0.vY = igi2_frame.Real32x3_Rotate_tTemp.vY + ptSector->tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos.vY;
  igi2_frame.tWorldPos0.vZ = igi2_frame.Real32x3_Rotate_tTemp.vZ + ptSector->tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos.vZ;
  v30 = v29 - TransContext_tActiveTransContext.tPos.vX;
  igi2_frame.v67 = v30;
  v31 = igi2_frame.tWorldPos0.vY - TransContext_tActiveTransContext.tPos.vY;
  igi2_frame.v69 = igi2_frame.tWorldPos0.vY - TransContext_tActiveTransContext.tPos.vY;
  v32 = igi2_frame.tWorldPos0.vZ - TransContext_tActiveTransContext.tPos.vZ;
  igi2_frame.v70 = igi2_frame.tWorldPos0.vZ - TransContext_tActiveTransContext.tPos.vZ;
  if ( v30 != 0.0 || v31 != 0.0 || v32 != 0.0 )
  {
    igi2_frame.tContext.vX = sqrt(v30 * v30 + v31 * v31 + v32 * v32);
    v33 = v30;
    v34 = 1.0 / igi2_frame.tContext.vX;
    v35 = v33 * v34;
    v36 = v34;
    v30 = v35;
    v31 = v31 * v36;
    v32 = v32 * v36;
  }
  if ( igi2_frame.tNormal.vZ * v32 + v31 * igi2_frame.tNormal.vY + v30 * igi2_frame.tNormal.vX < 0.0 )
  {
    igi2_frame.tContext.vX = -igi2_frame.tNormal.vX;
    igi2_frame.tContext.vY = -igi2_frame.tNormal.vY;
    igi2_frame.tEdge1.vY = igi2_frame.v69;
    igi2_frame.tEdge1.vZ = igi2_frame.v70;
    igi2_frame.tContext.vZ = -igi2_frame.tNormal.vZ;
    igi2_frame.tEdge1.vX = igi2_frame.v67;
    Real32x3_ProjectPointToPlane(&igi2_frame.Real32x3_Rotate_tTemp, &igi2_frame.tEdge1, &igi2_frame.tContext, &igi2_frame.tNormal);
    if ( (igi2_frame.tEdge1.vX - igi2_frame.Real32x3_Rotate_tTemp.vX) * (igi2_frame.tEdge1.vX - igi2_frame.Real32x3_Rotate_tTemp.vX)
       + (igi2_frame.tEdge1.vY - igi2_frame.Real32x3_Rotate_tTemp.vY) * (igi2_frame.tEdge1.vY - igi2_frame.Real32x3_Rotate_tTemp.vY)
       + (igi2_frame.tEdge1.vZ - igi2_frame.Real32x3_Rotate_tTemp.vZ) * (igi2_frame.tEdge1.vZ - igi2_frame.Real32x3_Rotate_tTemp.vZ) > 167772.171875 )
      return 0;
    v10 = igi2_frame.ptPortal;
  }
  v37 = *(float *)&v10->nNumVertices;
  *(float *)&igi2_frame.tWorldPos0.vX = ptSector->tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos.vX
                           - TransContext_tActiveTransContext.tPos.vX;
  *((float *)&igi2_frame.tWorldPos0.vX + 1) = ptSector->tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos.vY
                                 - TransContext_tActiveTransContext.tPos.vY;
  *(float *)&igi2_frame.tWorldPos0.vY = ptSector->tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos.vZ
                           - TransContext_tActiveTransContext.tPos.vZ;
  if ( SLODWORD(v37) > 0 )
  {
    p_vY = &igi2_frame.atVertex[0].tProjected.vY;
    v39 = &ptPortalVertex[v10->iStartVertex].tPos.vX;
    igi2_frame.v69 = v37;
    do
    {
      igi2_frame.tEdge1.vX = v39[2] * ptSector->tRigidDynCubeObj.tModelObj.tOrientation.tX.vZ
                + ptSector->tRigidDynCubeObj.tModelObj.tOrientation.tX.vX * *v39
                + v39[1] * ptSector->tRigidDynCubeObj.tModelObj.tOrientation.tX.vY;
      v40 = v39[2];
      igi2_frame.Real32x3_Rotate_tTemp.vX = igi2_frame.tEdge1.vX;
      igi2_frame.tEdge1.vY = v40 * ptSector->tRigidDynCubeObj.tModelObj.tOrientation.tY.vZ
                + v39[1] * ptSector->tRigidDynCubeObj.tModelObj.tOrientation.tY.vY
                + ptSector->tRigidDynCubeObj.tModelObj.tOrientation.tY.vX * *v39;
      v41 = v39[2];
      igi2_frame.Real32x3_Rotate_tTemp.vY = igi2_frame.tEdge1.vY;
      igi2_frame.tEdge1.vZ = v41 * ptSector->tRigidDynCubeObj.tModelObj.tOrientation.tZ.vZ
                + ptSector->tRigidDynCubeObj.tModelObj.tOrientation.tZ.vX * *v39
                + v39[1] * ptSector->tRigidDynCubeObj.tModelObj.tOrientation.tZ.vY;
      igi2_frame.Real32x3_Rotate_tTemp.vZ = igi2_frame.tEdge1.vZ;
      v42 = igi2_frame.tEdge1.vX + *(float *)&igi2_frame.tWorldPos0.vX;
      v43 = p_vY - 4;
      v44 = igi2_frame.tEdge1.vY + *((float *)&igi2_frame.tWorldPos0.vX + 1);
      v45 = igi2_frame.tEdge1.vZ + *(float *)&igi2_frame.tWorldPos0.vY;
      igi2_frame.tNormal.vX = TransContext_tActiveTransContext.tMatrix.tX.vZ * v45
                 + v44 * TransContext_tActiveTransContext.tMatrix.tX.vY
                 + v42 * TransContext_tActiveTransContext.tMatrix.tX.vX;
      vZ = TransContext_tActiveTransContext.tMatrix.tY.vZ;
      *v43 = igi2_frame.tNormal.vX;
      igi2_frame.tNormal.vY = vZ * v45
                 + v44 * TransContext_tActiveTransContext.tMatrix.tY.vY
                 + v42 * TransContext_tActiveTransContext.tMatrix.tY.vX;
      v43[1] = igi2_frame.tNormal.vY;
      igi2_frame.tNormal.vZ = v45 * TransContext_tActiveTransContext.tMatrix.tZ.vZ
                 + v44 * TransContext_tActiveTransContext.tMatrix.tZ.vY
                 + v42 * TransContext_tActiveTransContext.tMatrix.tZ.vX;
      v47 = igi2_frame.tNormal.vZ;
      v43[2] = igi2_frame.tNormal.vZ;
      if ( v47 < 0.04095999896526337 )
      {
        *((_DWORD *)p_vY + 2) = 16;
      }
      else
      {
        v48 = 1;
        igi2_frame.isVertexBeyondZ0 = 1;
        LODWORD(igi2_frame.v70) = 1;
        igi2_frame.v67 = 1.0 / igi2_frame.tNormal.vZ;
        v49 = igi2_frame.v67 * igi2_frame.tNormal.vX;
        p_vY[1] = igi2_frame.v67;
        v50 = v49 * TransContext_tActiveTransContext.vScreenFOVX + TransContext_tActiveTransContext.vScreenOriginX;
        *(p_vY - 1) = v50;
        v51 = igi2_frame.v67 * igi2_frame.tNormal.vY * TransContext_tActiveTransContext.vScreenFOVY
            + TransContext_tActiveTransContext.vScreenOriginY;
        igi2_frame.tContext.vX = v51;
        *p_vY = v51;
        if ( v50 >= RenderContext_tActiveRenderContext.tDisplayAreaMin.vX )
          igi2_frame.v70 = 0.0;
        if ( v50 <= RenderContext_tActiveRenderContext.tDisplayAreaMax.vX )
          v48 = 0;
        *((_DWORD *)p_vY + 2) = LODWORD(igi2_frame.v70)
                              | (2
                               * ((v51 < RenderContext_tActiveRenderContext.tDisplayAreaMin.vY)
                                | (2
                                 * (v48
                                  | (2 * (igi2_frame.tContext.vX > (double)RenderContext_tActiveRenderContext.tDisplayAreaMax.vY))))));
      }
      v39 += 3;
      p_vY += 7;
      --LODWORD(igi2_frame.v69);
    }
    while ( igi2_frame.v69 != 0.0 );
    if ( igi2_frame.isVertexBeyondZ0 )
    {
      LODWORD(igi2_frame.tContext.vX) = &igi2_frame.tScreenMin;
      LODWORD(igi2_frame.tContext.vY) = &igi2_frame.tScreenMax;
      v52 = 0;
      if ( v10->nNumFaces > 0 )
      {
        while ( 1 )
        {
          v53 = &igi2_frame.ptMesh->ptPortalFace[v52 + v10->iStartFace];
          iStartVertex = v10->iStartVertex;
          v55 = &igi2_frame.atVertex[v53->iPortalVertex2 - v10->iStartVertex];
          igi2_frame.v64 = 1026016684;
          igi2_frame.p_tContext = &igi2_frame.tContext;
          qmemcpy(&igi2_frame.v62, v55, sizeof(igi2_frame.v62));
          qmemcpy(&igi2_frame.v61, &igi2_frame.atVertex[v53->iPortalVertex1 - iStartVertex], sizeof(igi2_frame.v61));
          qmemcpy(&igi2_frame.v60, &igi2_frame.atVertex[v53->iPortalVertex0 - iStartVertex], sizeof(igi2_frame.v60));
          SectorObject_CheckTriangle(igi2_frame.v60, igi2_frame.v61, igi2_frame.v62, (struct CheckTriangleContext_t *)&igi2_frame.tContext, 0.04095999896526337);
          if ( ++v52 >= igi2_frame.ptPortal->nNumFaces )
            break;
          v10 = igi2_frame.ptPortal;
        }
      }
      if ( igi2_frame.tScreenMin.vX <= (double)ptMax->vX
        && igi2_frame.tScreenMin.vY <= (double)ptMax->vY
        && igi2_frame.tScreenMax.vX >= (double)ptMin->vX
        && igi2_frame.tScreenMax.vY >= (double)ptMin->vY )
      {
        v56 = igi2_frame.tScreenMin.vY;
        ptDestMin->vX = igi2_frame.tScreenMin.vX;
        v57 = igi2_frame.tScreenMax.vX;
        ptDestMin->vY = v56;
        v58 = igi2_frame.tScreenMax.vY;
        ptDestMax->vX = v57;
        ptDestMax->vY = v58;
        return 1;
      }
    }
  }
  return 0;
}

// source: e/3/sectorobject.c:1797  [anchor-mhash]
void __cdecl SectorObject_RequestSector(
        struct Sector_s *ptSector,
        struct real32x2_t *ptMin,
        struct real32x2_t *ptMax,
        int iLOD,
        int isFirstSector)
{
  struct QObjectVector_s *v5; // esi
  unsigned int nAllocated; // edi
  unsigned int v7; // edx
  void **papxElement; // eax
  float *v9; // esi
  struct QObjectVector_s *ptClipWindowsList; // edi
  unsigned int v11; // ecx
  struct real32x2_t *v12; // eax
  double vX; // st7
  double vY; // st7
  double v15; // st7
  double v16; // st7
  unsigned int *p_nAllocated; // edi
  struct real32x2_t *v18; // esi
  struct QObjectVector_s *v19; // edi
  unsigned int v20; // ecx
  struct real32x2_t *v21; // eax
  int v22; // ecx
  unsigned int iRequest; // [esp+10h] [ebp-8h]
  unsigned int nRequests; // [esp+14h] [ebp-4h]

  v5 = SectorObject_tRequestPool;
  nAllocated = SectorObject_tRequestPool->nAllocated;
  v7 = 0;
  nRequests = nAllocated;
  if ( nAllocated )
  {
    papxElement = SectorObject_tRequestPool->papxElement;
    while ( 1 )
    {
      v9 = (float *)*papxElement;
      if ( *((struct Sector_s **)*papxElement + 4) == ptSector )
        break;
      ++v7;
      ++papxElement;
      if ( v7 >= nAllocated )
        goto LABEL_21;
    }
    ptClipWindowsList = ptSector->ptClipWindowsList;
    iRequest = v7;
    if ( ptClipWindowsList->nAllocated == ptClipWindowsList->nSize )
    {
      QObjectVector_Realloc(ptClipWindowsList, ptClipWindowsList->nReallocSize);
      v7 = iRequest;
    }
    v11 = ptClipWindowsList->nAllocated;
    v12 = (struct real32x2_t *)ptClipWindowsList->papxElement[v11];
    ptClipWindowsList->nAllocated = v11 + 1;
    *v12 = *ptMin;
    v12[1] = *ptMax;
    if ( *v9 >= (double)ptMin->vX )
      vX = ptMin->vX;
    else
      vX = *v9;
    *v9 = vX;
    if ( v9[1] >= (double)ptMin->vY )
      vY = ptMin->vY;
    else
      vY = v9[1];
    v9[1] = vY;
    if ( v9[2] <= (double)ptMax->vX )
      v15 = ptMax->vX;
    else
      v15 = v9[2];
    v9[2] = v15;
    if ( v9[3] <= (double)ptMax->vY )
      v16 = ptMax->vY;
    else
      v16 = v9[3];
    nAllocated = nRequests;
    v9[3] = v16;
LABEL_21:
    v5 = SectorObject_tRequestPool;
  }
  if ( v7 == nAllocated )
  {
    p_nAllocated = &v5->nAllocated;
    if ( v5->nAllocated == v5->nSize )
      QObjectVector_Realloc(v5, v5->nReallocSize);
    v18 = (struct real32x2_t *)v5->papxElement[(*p_nAllocated)++];
    LODWORD(v18[2].vX) = ptSector;
    LODWORD(v18[3].vX) = iLOD;
    v19 = ptSector->ptClipWindowsList;
    if ( v19->nAllocated == v19->nSize )
      QObjectVector_Realloc(v19, v19->nReallocSize);
    v20 = v19->nAllocated;
    v21 = (struct real32x2_t *)v19->papxElement[v20];
    v19->nAllocated = v20 + 1;
    *v21 = *ptMin;
    v21[1] = *ptMax;
    *v18 = *ptMin;
    v22 = SectorObject_nRequestTimeStamp;
    v18[1] = *ptMax;
    LODWORD(v18[2].vY) = v22 + 1;
    v18[3].vY = 0.0;
  }
  SectorObject_TraverseSector(ptSector, ptMin, ptMax, iLOD);
}

// source: e/3/sectorobject.c:1875  [size]
void __cdecl Sector_EnterHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct DrawRigidMeshContext_t tContext; };
    struct { char igi2_o1[32]; struct MagicObjEnterContext_s tMagicObjEnterContext; };
    char igi2_extent[104];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *v2; // ebx
  struct QTask_s *ptNext; // eax
  struct QTask_s *v4; // esi
  unsigned __int16 eQTaskType; // dx
  struct QTask_s *ptHead; // esi
  void (__cdecl *pfHandler)(struct QTask_s *, struct MagicObjEnterContext_s *); // eax
  struct QTask_s *v8; // eax
  unsigned int i; // esi
  int v10; // eax
  void (__cdecl *v11)(int, struct QTask_s **); // ecx

  v2 = ptQTask;
  igi2_frame.tContext.tLightContext.nLightNum = SectorObject_nLightNum;
  igi2_frame.tContext.tLightContext.pnLightList = SectorObject_pnLightList;
  igi2_frame.tContext.tLightContext.pptHazingList = SectorObject_pptHazingList;
  igi2_frame.tContext.isExcludeTestPassed = false;
  igi2_frame.tContext.isSort = true;
  igi2_frame.tContext.ptRigidDynCubeObj = (struct RigidDynCubeObj_t *)ptQTask;
  igi2_frame.tContext.tLightContext.nNumHazingBox = SectorObject_nNumHazingBox;
  RenderMode_tActiveRenderMode.apfRenderModeMethod[Mesh3D_eDrawRigidMeshRenderModeMethod](&igi2_frame.tContext);
  ptNext = v2[3].ptNext;
  qmemcpy(&igi2_frame.tMagicObjEnterContext, &v2[1], 0x18u);
  qmemcpy(&igi2_frame.tMagicObjEnterContext.tParentOrientation, &v2[3].ptPrev, sizeof(igi2_frame.tMagicObjEnterContext.tParentOrientation));
  if ( ptNext )
    v4 = ptNext->tQTaskChildren.ptHead->ptNext != nullptr ? ptNext->tQTaskChildren.ptHead : nullptr;
  else
    v4 = nullptr;
  igi2_frame.tMagicObjEnterContext.isExcludeTestPassed = 0;
  if ( v4 )
  {
    do
    {
      eQTaskType = v4->eQTaskType;
      if ( QTask_IsQTaskTypeDerived(eQTaskType, DynCubeObj_eQTaskType) )
        v4[2].tQTaskRefList.ptMiddle = (struct QReference_s *)v2;
      ((void (__cdecl *)(struct QTask_s *, struct MagicObjEnterContext_s *))QTask_aatQTaskFinalEvent[MagicObj_eMagicObjEnterEvent][eQTaskType].pfHandler)(
        v4,
        &igi2_frame.tMagicObjEnterContext);
      v4 = v4->ptNext;
    }
    while ( v4 && v4->ptNext );
  }
  ptHead = v2->tQTaskChildren.ptHead;
  if ( ptHead->ptNext && ptHead )
  {
    do
    {
      pfHandler = (void (__cdecl *)(struct QTask_s *, struct MagicObjEnterContext_s *))QTask_aatQTaskFinalEvent[MagicObj_eMagicObjEnterEvent][ptHead->eQTaskType].pfHandler;
      if ( pfHandler )
        pfHandler(ptHead, &igi2_frame.tMagicObjEnterContext);
      ptHead = ptHead->ptNext;
    }
    while ( ptHead && ptHead->ptNext );
  }
  v8 = v2[8].ptNext;
  for ( i = 0; i < *(_DWORD *)&v8->eQTaskType; ++i )
  {
    v10 = **((_DWORD **)&v8[1].tQTaskChildren.ptHead->ptNext + i);
    *(_DWORD *)(v10 + 104) = v2;
    ptQTask = nullptr;
    v11 = (void (__cdecl *)(int, struct QTask_s **))QTask_aatQTaskFinalEvent[5][*(unsigned __int16 *)(v10 + 36)].pfHandler;
    if ( v11 )
      v11(v10, &ptQTask);
    v8 = v2[8].ptNext;
  }
}

// source: e/3/sectorobject.c:1966  [anchor-callee]
struct SectorRequest_t *__cdecl SectorObject_DrawSector(struct SectorRequest_t *ptRequest)
{
  struct SectorObject_s *v1; // ecx
  struct Sector_s *ptSector; // esi
  float vY; // edx
  struct SectorRequest_t *result; // eax
  enum DynCubeRenderGroup_e iRenderGroup; // ecx
  struct Sector_s *pxQData; // edx
  struct CallQueueItem_s *ptNext; // edi
  int v8; // ecx
  _DWORD *v9; // edx

  v1 = SectorObject_ptActiveSectorObject;
  ptSector = ptRequest->ptSector;
  if ( ptSector == (struct Sector_s *)SectorObject_ptActiveSectorObject
    && SectorObject_ptActiveSectorObject == (struct SectorObject_s *)QCube_ptInsideSectorObject )
  {
    Clipping_tClipData.tClipWindows.ptClipWindowsList = ptSector->ptClipWindowsList;
    Clipping_tClipData.tClipWindows.tEnclosingWindow.tX.vX = ptRequest->tMin.vX;
    Clipping_tClipData.tClipWindows.tEnclosingWindow.tX.vY = ptRequest->tMin.vY;
    Clipping_tClipData.tClipWindows.tEnclosingWindow.tY.vX = ptRequest->tMax.vX;
    vY = ptRequest->tMax.vY;
    QCube_isDrawOutside = 1;
    Clipping_tClipData.tClipWindows.tEnclosingWindow.tY.vY = vY;
    Clipping_SetupClippingPlanes(Clipping_tClipData.tClipWindows.ptClipWindowsList);
    v1 = SectorObject_ptActiveSectorObject;
  }
  ptSector->isVisible = 1;
  ptSector->tRigidDynCubeObj.tModelObj.tDynCubeObj.ptSector = ptSector;
  if ( ptSector == (struct Sector_s *)v1 )
    return ((struct SectorRequest_t *(__cdecl *)(struct Sector_s *, _DWORD))QTask_aatQTaskFinalEvent[5][Sector_eQTaskType].pfHandler)(
             ptSector,
             0);
  iRenderGroup = ptSector->tRigidDynCubeObj.tModelObj.tDynCubeObj.iRenderGroup;
  result = (struct SectorRequest_t *)CallQueue_ptFirstFreeItem;
  pxQData = (struct Sector_s *)ptSector->tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.pxQData;
  ptNext = CallQueue_ptFirstFreeItem->ptNext;
  CallQueue_ptFirstFreeItem->ptQTask = &ptSector->tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask;
  v8 = 8 * iRenderGroup + 128714432;
  LOWORD(result->tMax.vX) = 5;
  result->tMax.vY = 0.0;
  result->ptSector = pxQData;
  result->tMin.vX = 0.0;
  v9 = *(_DWORD **)(v8 + 4);
  CallQueue_ptFirstFreeItem = ptNext;
  *v9 = result;
  *(_DWORD *)(v8 + 4) = result;
  return result;
}

// source: e/3/sectorobject.c:2063  [anchor-mhash]
void __cdecl SectorObject_TraverseSector(
        struct Sector_s *ptSector,
        struct real32x2_t *ptMin,
        struct real32x2_t *ptMax,
        int iLOD)
{
  #pragma pack(push, 1)
  union
  {
    struct { int v17; };
    struct { char igi2_o1[4]; int v18; };
    struct { char igi2_o2[8]; int v19; };
    struct { char igi2_o3[12]; struct Mesh3D_Mesh_t *ptMesh; };
    struct { char igi2_o4[16]; int iChildPortal; };
    struct { char igi2_o5[20]; int iPortalIndex; };
    struct { char igi2_o6[24]; struct Sector_s **pptDiscardSector; };
    struct { char igi2_o7[28]; struct real32x2_t tMax; };
    struct { char igi2_o8[36]; struct real32x2_t tMin; };
    char igi2_extent[44];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QObjectVector_s *v4; // edi
  unsigned int *p_nAllocated; // esi
  struct QObjectVector_s *v6; // ebx
  struct Sector_s **v7; // ecx
  struct SectorObject_s *ptHead; // esi
  int nAllocated; // ecx
  int v10; // eax
  void **papxElement; // edx
  int LOD; // eax
  int v13; // ebx
  struct Mesh3D_Mesh_t *v14; // edi
  struct QTask_s *ptSectorContainer; // esi
  bool v16; // cc

  v4 = SectorObject_ptDiscardSectorList;
  p_nAllocated = &SectorObject_ptDiscardSectorList->nAllocated;
  igi2_frame.ptMesh = ptSector->tRigidDynCubeObj.tModelObj.ptLODVirModel->aptVirModel[iLOD]->ptModel->ptMesh;
  v6 = SectorObject_ptDiscardSectorList;
  if ( SectorObject_ptDiscardSectorList->nAllocated == SectorObject_ptDiscardSectorList->nSize )
  {
    QObjectVector_Realloc(SectorObject_ptDiscardSectorList, SectorObject_ptDiscardSectorList->nReallocSize);
    v4 = SectorObject_ptDiscardSectorList;
  }
  v7 = (struct Sector_s **)v6->papxElement[(*p_nAllocated)++];
  *v7 = ptSector;
  igi2_frame.pptDiscardSector = v7;
  igi2_frame.v18 = 0;
  if ( igi2_frame.ptMesh->nPortal > 0 )
  {
    igi2_frame.v19 = 0;
    do
    {
      igi2_frame.iPortalIndex = igi2_frame.ptMesh->ptPortal[igi2_frame.v19].iPortal;
      if ( Sector_IsPortalVisible(ptSector, iLOD, igi2_frame.v18, ptMin, ptMax, &igi2_frame.tMin, &igi2_frame.tMax) )
      {
        if ( igi2_frame.tMin.vX <= (double)ptMin->vX )
          igi2_frame.tMin.vX = ptMin->vX;
        if ( igi2_frame.tMin.vY <= (double)ptMin->vY )
          igi2_frame.tMin.vY = ptMin->vY;
        if ( igi2_frame.tMax.vX >= (double)ptMax->vX )
          igi2_frame.tMax.vX = ptMax->vX;
        if ( igi2_frame.tMax.vY >= (double)ptMax->vY )
          igi2_frame.tMax.vY = ptMax->vY;
        ptHead = SectorObject_ptActiveSectorObject;
        if ( SectorObject_ptActiveSectorObject )
        {
          do
          {
            nAllocated = v4->nAllocated;
            v10 = 0;
            if ( nAllocated > 0 )
            {
              papxElement = v4->papxElement;
              do
              {
                if ( *(struct SectorObject_s **)*papxElement == ptHead )
                  break;
                ++v10;
                ++papxElement;
              }
              while ( v10 < nAllocated );
            }
            if ( v10 == nAllocated )
            {
              LOD = ModelObj_GetLOD(&ptHead->tSector.tRigidDynCubeObj.tModelObj);
              v13 = LOD;
              if ( LOD != -1 )
              {
                v14 = ptHead->tSector.tRigidDynCubeObj.tModelObj.ptLODVirModel->aptVirModel[LOD]->ptModel->ptMesh;
                igi2_frame.iChildPortal = 0;
                if ( v14->nPortal > 0 )
                {
                  igi2_frame.v17 = 0;
                  do
                  {
                    if ( v14->ptPortal[igi2_frame.v17].iPortal == igi2_frame.iPortalIndex )
                      SectorObject_RequestSector(&ptHead->tSector, &igi2_frame.tMin, &igi2_frame.tMax, v13, 0);
                    ++igi2_frame.v17;
                    ++igi2_frame.iChildPortal;
                  }
                  while ( igi2_frame.iChildPortal < v14->nPortal );
                }
                v4 = SectorObject_ptDiscardSectorList;
              }
            }
            if ( ptHead == SectorObject_ptActiveSectorObject )
            {
              ptSectorContainer = ptHead->ptSectorContainer;
              if ( !ptSectorContainer )
                break;
              ptHead = (struct SectorObject_s *)ptSectorContainer->tQTaskChildren.ptHead;
            }
            else
            {
              ptHead = (struct SectorObject_s *)ptHead->tSector.tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask.ptNext;
              if ( !ptHead )
                break;
            }
          }
          while ( ptHead->tSector.tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask.ptNext && ptHead );
        }
      }
      v16 = ++igi2_frame.v18 < igi2_frame.ptMesh->nPortal;
      ++igi2_frame.v19;
    }
    while ( v16 );
    v7 = igi2_frame.pptDiscardSector;
  }
  QObjectVector_RemoveElement(v4, *(unsigned int *)((char *)v7 + v4->nElementSize - 4));
}

// source: e/3/sectorobject.c:2177  [anchor-mhash]
void __cdecl SectorObject_EnterHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct Sector_s *ptStartSector; };
    struct { char igi2_o1[4]; void ***p_papxElement; };
    struct { char igi2_o2[8]; unsigned int *p_nAllocated; };
    struct { char igi2_o3[12]; struct real32x2_t tStartMax; };
    struct { char igi2_o4[20]; struct real32x2_t tStartMin; };
    char igi2_extent[28];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v2; // eax
  struct QTask_s *ptNext; // eax
  struct QTask_s *v4; // eax
  struct QTask_s *ptPrev; // ecx
  int *v6; // eax
  int v7; // ebx
  int v8; // edx
  int v9; // eax
  signed int v10; // edi
  float *v11; // eax
  float v12; // ecx
  struct LODVirModel_s *v13; // esi
  float v14; // edx
  float v15; // eax
  int v16; // eax
  struct LODVirModel_s *ptLODVirModel; // ebx
  int LOD; // eax
  int v19; // esi
  struct QObjectVector_s *v20; // eax
  unsigned int i; // ebx
  struct SectorRequest_t *v22; // esi
  struct QObjectVector_s *ptClipWindowsList; // eax
  struct Sector_s *ptSector; // edx
  struct QObjectVector_s *v25; // edi
  unsigned int nAllocated; // ecx
  _DWORD *v27; // eax

  v2 = *(_DWORD *)&ptQTask[2].eQTaskType;
  igi2_frame.ptStartSector = (struct Sector_s *)ptQTask;
  SectorObject_ptActiveSectorObject = (struct SectorObject_s *)ptQTask;
  ptQTask[2].tQTaskRefList.ptTail = (struct QReference_s *)3;
  if ( v2 )
  {
    ptNext = ptQTask[10].ptNext;
    if ( ptNext )
      v4 = ptNext->tQTaskChildren.ptHead->ptNext != nullptr ? ptNext->tQTaskChildren.ptHead : nullptr;
    else
      v4 = nullptr;
    *(_DWORD *)&ptQTask[8].ptPrev->eQTaskType = 0;
    if ( v4 )
    {
      do
      {
        ptPrev = v4[8].ptPrev;
        v4[9].ptParent = nullptr;
        *(_DWORD *)&ptPrev->eQTaskType = 0;
        v4 = v4->ptNext;
      }
      while ( v4 && v4->ptNext );
    }
    if ( ptQTask == (struct QTask_s *)QCube_ptInsideSectorObject )
    {
      if ( QCube_isInsideSectorObjectDrawn )
        return;
      QCube_isDrawOutside = 0;
      igi2_frame.ptStartSector = (struct Sector_s *)QCube_ptInsideSector;
    }
    v6 = (int *)(4 * Lightsource_nLightDataBufferPos + 140666816);
    v7 = Lightsource_nLightDataStackPos + Lightsource_nLightDataBufferPos;
    SectorObject_nLightNum = Lightsource_nLightDataStackPos;
    v8 = Hazinglayers_iHazingBuffer;
    qmemcpy(v6, Lightsource_anLightDataStack, 4 * Lightsource_nLightDataStackPos);
    SectorObject_pnLightList = v6;
    v9 = Hazinglayers_iHazingStack;
    SectorObject_pptHazingList = (struct HazingDynCubeObj_t **)(4 * v8 + 129834072);
    qmemcpy((void *)(4 * v8 + 129834072), Hazinglayers_aptHazingStack, 4 * Hazinglayers_iHazingStack);
    SectorObject_nNumHazingBox = v9;
    Lightsource_nLightDataBufferPos = v7;
    Hazinglayers_iHazingBuffer = v9 + v8;
    if ( !QCube_ptInsideSectorObject || ptQTask == (struct QTask_s *)QCube_ptInsideSectorObject )
    {
      igi2_frame.tStartMin.vY = RenderContext_tActiveRenderContext.tDisplayAreaMin.vY;
      ptLODVirModel = igi2_frame.ptStartSector->tRigidDynCubeObj.tModelObj.ptLODVirModel;
      igi2_frame.tStartMin.vX = RenderContext_tActiveRenderContext.tDisplayAreaMin.vX;
      igi2_frame.tStartMax = RenderContext_tActiveRenderContext.tDisplayAreaMax;
      if ( ptLODVirModel )
      {
        LOD = ModelObj_GetLOD((struct ModelObj_s *)ptQTask);
        v19 = LOD;
        if ( LOD >= 0 && LOD < ptLODVirModel->nLOD )
        {
          SectorObject_RequestSector(igi2_frame.ptStartSector, &igi2_frame.tStartMin, &igi2_frame.tStartMax, LOD, 1);
          MagicObjContainer_RunHandler((struct QTask_s *)((char *)ptQTask + 432), (int)ptQTask, v19);
        }
      }
    }
    else
    {
      if ( !Clipping_tClipData.tClipWindows.ptClipWindowsList )
        return;
      v10 = 0;
      igi2_frame.p_nAllocated = &Clipping_tClipData.tClipWindows.ptClipWindowsList->nAllocated;
      if ( (int)Clipping_tClipData.tClipWindows.ptClipWindowsList->nAllocated > 0 )
      {
        igi2_frame.p_papxElement = &Clipping_tClipData.tClipWindows.ptClipWindowsList->papxElement;
        do
        {
          v11 = (float *)(*igi2_frame.p_papxElement)[v10];
          v12 = v11[1];
          v13 = igi2_frame.ptStartSector->tRigidDynCubeObj.tModelObj.ptLODVirModel;
          igi2_frame.tStartMin.vX = *v11;
          v14 = v11[2];
          v15 = v11[3];
          igi2_frame.tStartMin.vY = v12;
          igi2_frame.tStartMax.vX = v14;
          igi2_frame.tStartMax.vY = v15;
          if ( v13 )
          {
            v16 = ModelObj_GetLOD((struct ModelObj_s *)ptQTask);
            if ( v16 >= 0 && v16 < v13->nLOD )
              SectorObject_RequestSector(igi2_frame.ptStartSector, &igi2_frame.tStartMin, &igi2_frame.tStartMax, v16, 1);
          }
          ++v10;
        }
        while ( v10 < (int)*igi2_frame.p_nAllocated );
      }
    }
    v20 = SectorObject_tRequestPool;
    for ( i = 0; i < SectorObject_tRequestPool->nAllocated; ++i )
    {
      v22 = (struct SectorRequest_t *)v20->papxElement[i];
      ptClipWindowsList = v22->ptSector->ptClipWindowsList;
      if ( ptClipWindowsList->nAllocated > 4 )
      {
        ptClipWindowsList->nAllocated = 0;
        ptSector = v22->ptSector;
        v25 = ptSector->ptClipWindowsList;
        if ( v25->nAllocated == v25->nSize )
          QObjectVector_Realloc(ptSector->ptClipWindowsList, v25->nReallocSize);
        nAllocated = v25->nAllocated;
        v27 = v25->papxElement[nAllocated];
        v25->nAllocated = nAllocated + 1;
        *v27 = LODWORD(v22->tMin.vX);
        v27[1] = LODWORD(v22->tMin.vY);
        v27[2] = LODWORD(v22->tMax.vX);
        v27[3] = LODWORD(v22->tMax.vY);
      }
      SectorObject_DrawSector(v22);
      v20 = SectorObject_tRequestPool;
    }
    v20->nAllocated = 0;
  }
}

// source: e/3/sectorobject.c:2349  [anchor-mhash]
void __cdecl SectorObject_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QObjectVector_s *v2; // esi
  struct QObjectVector_s *v3; // esi

  ModelObj_Init((struct ModelObj_s *)ptQTask, World_ptActiveWorld, nullptr);
  ptQTask[7].tQTaskChildren.ptHead = nullptr;
  ptQTask[7].tQTaskChildren.ptMiddle = (struct QTask_s *)2;
  ptQTask[7].tQTaskRefList.ptHead = nullptr;
  ptQTask[7].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[7].tQTaskRefList.ptTail = nullptr;
  ptQTask[7].ptParent = nullptr;
  *(_DWORD *)&ptQTask[7].eQTaskType = 0;
  ptQTask[10].ptNext = nullptr;
  v2 = (struct QObjectVector_s *)Mem_AllocFn(52, 4);
  v2->isStrictOrder = false;
  v2->nSize = 0;
  v2->nAllocated = 0;
  v2->nReallocSize = 10;
  v2->papxElement = nullptr;
  v2->nElementSize = 8;
  v2->tMemPool.nBlocks = 0;
  v2->tMemPool.nAllocatedBlocks = 0;
  v2->tMemPool.nAlignment = 4;
  v2->tMemPool.nBlockSize = 8;
  v2->tMemPool.nReAllocBlocks = 10;
  v2->tMemPool.tMemPoolFreeList.ptHead = nullptr;
  v2->tMemPool.tMemPoolSegmentList.ptHead = nullptr;
  MemPool_ReAlloc(&v2->tMemPool, 0xAu);
  QObjectVector_Realloc(v2, 0xAu);
  ptQTask[8].ptNext = (struct QTask_s *)v2;
  v3 = (struct QObjectVector_s *)Mem_AllocFn(52, 4);
  v3->isStrictOrder = false;
  v3->nSize = 0;
  v3->nAllocated = 0;
  v3->nReallocSize = 10;
  v3->papxElement = nullptr;
  v3->nElementSize = 20;
  v3->tMemPool.nBlocks = 0;
  v3->tMemPool.nAllocatedBlocks = 0;
  v3->tMemPool.nAlignment = 4;
  v3->tMemPool.nBlockSize = 20;
  v3->tMemPool.nReAllocBlocks = 10;
  v3->tMemPool.tMemPoolFreeList.ptHead = nullptr;
  v3->tMemPool.tMemPoolSegmentList.ptHead = nullptr;
  MemPool_ReAlloc(&v3->tMemPool, 0xAu);
  QObjectVector_Realloc(v3, 0xAu);
  ptQTask[8].ptPrev = (struct QTask_s *)v3;
  *(struct real32x3_t *)&ptQTask[10].ptPrev = Mesh3D_atAmbientColor[1];
  ptQTask[2].tQTaskRefList.ptTail = (struct QReference_s *)3;
  memset(&ptQTask[10].ptParent, 0, 0x2Cu);
  memset(&ptQTask[8].tQTaskChildren, 1u, 0x40u);
}

// source: e/3/sectorobject.c:2387  [anchor-mhash]
void __cdecl SectorObject_DeleteHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptParent; // eax

  *(_DWORD *)&ptQTask[8].ptPrev->eQTaskType = 0;
  QObjectVector_Delete((struct QObjectVector_s *)ptQTask[8].ptPrev);
  Sector_CleanUpReferences((struct Sector_s *)ptQTask);
  QObjectVector_Delete((struct QObjectVector_s *)ptQTask[8].ptNext);
  if ( *(_DWORD *)&ptQTask[2].eQTaskType )
  {
    ModelObj_SetLODVirModel((struct ModelObj_s *)ptQTask, nullptr, false);
    ptQTask[7].tQTaskRefList.ptHead = nullptr;
    ptQTask[7].tQTaskRefList.ptMiddle = nullptr;
    ptQTask[7].tQTaskRefList.ptTail = nullptr;
    ptQTask[7].ptParent = nullptr;
    *(_DWORD *)&ptQTask[7].eQTaskType = 0;
  }
  if ( ptQTask[10].ptNext )
    QTask_Delete(ptQTask[10].ptNext);
  ptParent = ptQTask[10].ptParent;
  if ( ptParent )
    ((void (__stdcall *)(struct QTask_s *))ptParent->ptNext->tQTaskChildren.ptHead)(ptQTask[10].ptParent);
  memset(&ptQTask[10].ptParent, 0, 0x2Cu);
}

// source: e/3/sectorobject.c:2421  [size]
void __cdecl SectorObject_GetNextZHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *ptNext; // eax
  int ptHead; // eax
  int v4; // edx
  struct QTask_s *v5; // ecx
  int v6; // ecx

  ((void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[11][Sector_eQTaskType].pfHandler)(
    ptQTask,
    pxContext);
  ptNext = ptQTask[10].ptNext;
  if ( ptNext )
  {
    ptHead = (int)ptNext->tQTaskChildren.ptHead;
    if ( *(_DWORD *)ptHead )
    {
      if ( ptHead )
      {
        v4 = QTask_nProtectedQTaskStackOffset;
        do
        {
          if ( *(_DWORD *)ptHead )
            v5 = **(_DWORD **)ptHead != 0 ? *(struct QTask_s **)ptHead : nullptr;
          else
            v5 = nullptr;
          QTask_atProtectedQTaskStack[v4].ptQTask = v5;
          v6 = *(unsigned __int16 *)(ptHead + 36);
          QTask_nProtectedQTaskStackOffset = v4 + 1;
          ((void (__cdecl *)(int, void *))QTask_aatQTaskFinalEvent[11][v6].pfHandler)(ptHead, pxContext);
          ptHead = dword_849C7DC[QTask_nProtectedQTaskStackOffset];
          v4 = --QTask_nProtectedQTaskStackOffset;
        }
        while ( ptHead );
      }
    }
  }
}

// source: e/3/sectorobject.c:2444  [size]
void __cdecl SectorObject_TraceLinesHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *ptNext; // eax
  int ptHead; // eax
  int v4; // edx
  struct QTask_s *v5; // ecx
  int v6; // ecx

  ((void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[10][Sector_eQTaskType].pfHandler)(
    ptQTask,
    pxContext);
  ptNext = ptQTask[10].ptNext;
  if ( ptNext )
  {
    ptHead = (int)ptNext->tQTaskChildren.ptHead;
    if ( *(_DWORD *)ptHead )
    {
      if ( ptHead )
      {
        v4 = QTask_nProtectedQTaskStackOffset;
        do
        {
          if ( *(_DWORD *)ptHead )
            v5 = **(_DWORD **)ptHead != 0 ? *(struct QTask_s **)ptHead : nullptr;
          else
            v5 = nullptr;
          QTask_atProtectedQTaskStack[v4].ptQTask = v5;
          v6 = *(unsigned __int16 *)(ptHead + 36);
          QTask_nProtectedQTaskStackOffset = v4 + 1;
          ((void (__cdecl *)(int, void *))QTask_aatQTaskFinalEvent[10][v6].pfHandler)(ptHead, pxContext);
          ptHead = dword_849C7DC[QTask_nProtectedQTaskStackOffset];
          v4 = --QTask_nProtectedQTaskStackOffset;
        }
        while ( ptHead );
      }
    }
  }
}

// source: e/3/sectorobject.c:2467  [size]
void __cdecl SectorObject_LineOfSightHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *ptNext; // eax
  int ptHead; // eax
  int v4; // edx
  struct QTask_s *v5; // ecx
  int v6; // ecx

  ((void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[9][Sector_eQTaskType].pfHandler)(
    ptQTask,
    pxContext);
  ptNext = ptQTask[10].ptNext;
  if ( ptNext )
  {
    ptHead = (int)ptNext->tQTaskChildren.ptHead;
    if ( *(_DWORD *)ptHead )
    {
      if ( ptHead )
      {
        v4 = QTask_nProtectedQTaskStackOffset;
        do
        {
          if ( *(_DWORD *)ptHead )
            v5 = **(_DWORD **)ptHead != 0 ? *(struct QTask_s **)ptHead : nullptr;
          else
            v5 = nullptr;
          QTask_atProtectedQTaskStack[v4].ptQTask = v5;
          v6 = *(unsigned __int16 *)(ptHead + 36);
          QTask_nProtectedQTaskStackOffset = v4 + 1;
          ((void (__cdecl *)(int, void *))QTask_aatQTaskFinalEvent[9][v6].pfHandler)(ptHead, pxContext);
          ptHead = dword_849C7DC[QTask_nProtectedQTaskStackOffset];
          v4 = --QTask_nProtectedQTaskStackOffset;
        }
        while ( ptHead );
      }
    }
  }
}

// source: e/3/sectorobject.c:2490  [anchor-mhash]
void __cdecl SectorObject_GetMaterialHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct QTask_s *ptChild; };
    struct { char igi2_o1[4]; struct GetMaterialContext_s tTempContext; };
    struct { char igi2_o2[156]; struct QMaterial_t *aptQMaterial[64]; };
    char igi2_extent[412];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *ptNext; // eax
  struct QTask_s *ptHead; // eax
  struct QTask_s *v4; // edx
  int v5; // ecx
  int i; // eax
  _DWORD *v7; // ecx
  struct QTask_s *v8; // eax

  ((void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[12][Sector_eQTaskType].pfHandler)(
    ptQTask,
    pxContext);
  ptNext = ptQTask[10].ptNext;
  if ( ptNext )
  {
    ptHead = ptNext->tQTaskChildren.ptHead;
    if ( ptHead->ptNext )
    {
      v4 = ptHead;
      igi2_frame.ptChild = ptHead;
      if ( ptHead )
      {
        while ( 1 )
        {
          qmemcpy(&igi2_frame.tTempContext, pxContext, sizeof(igi2_frame.tTempContext));
          igi2_frame.tTempContext.pptQMaterial = igi2_frame.aptQMaterial;
          v5 = *((_DWORD *)pxContext + 1);
          igi2_frame.tTempContext.isAllowFlippedGroups = 1;
          if ( v5 > 0 )
            memset(igi2_frame.aptQMaterial, 0, 4 * v5);
          ((void (__cdecl *)(struct QTask_s *, struct GetMaterialContext_s *))QTask_aatQTaskFinalEvent[12][v4->eQTaskType].pfHandler)(
            v4,
            &igi2_frame.tTempContext);
          for ( i = 0; i < (int)(*((_DWORD *)pxContext + 1)); ++i )
          {
            v7 = (_DWORD *)(*((_DWORD *)pxContext + 2) + 4 * i);
            if ( *v7 && !igi2_frame.tTempContext.pptQMaterial[i] )
              *v7 = 0;
          }
          v8 = igi2_frame.ptChild->ptNext;
          if ( !igi2_frame.ptChild->ptNext )
            break;
          if ( !v8->ptNext )
            break;
          igi2_frame.ptChild = igi2_frame.ptChild->ptNext;
          if ( !v8 )
            break;
          v4 = igi2_frame.ptChild;
        }
      }
    }
  }
}

// source: e/3/sectorobject.c:2577  [anchor-mhash]
void __cdecl SectorObject_GetSectorHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct TraceLinesContext_s tTraceContext; };
    struct { char igi2_o1[40]; struct real64x3_t atEnd[2]; };
    struct { char igi2_o2[92]; struct real32x3_t Real32x3_Rotate_tTemp; };
    struct { char igi2_o3[104]; struct real64x3_t atStart[2]; };
    struct { char igi2_o4[152]; struct QIntersection_s atIntersection[2]; };
    char igi2_extent[392];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  void *v2; // eax
  void *v3; // esi
  int v4; // eax
  double v5; // st7
  double v6; // st7
  double v7; // st7
  double v8; // st7
  int *v9; // ecx
  double v10; // st6
  double v11; // st7
  double v12; // st7
  int v13; // ecx
  double v14; // st6
  struct QTask_s *ptNext; // eax
  struct QObj_s *ptHead; // esi
  double vDistance; // st7
  double v18; // st6
  double v19; // st5
  double v20; // st6

  if ( ptQTask[10].ptNext )
  {
    v2 = *(void **)pxContext;
    qmemcpy(igi2_frame.atStart, *(void **)pxContext, 0x18u);
    qmemcpy(&igi2_frame.atStart[1], v2, sizeof(struct real64x3_t));
    qmemcpy(igi2_frame.atEnd, v2, 0x18u);
    v3 = v2;
    v4 = *((_DWORD *)pxContext + 1);
    qmemcpy(&igi2_frame.atEnd[1], v3, sizeof(struct real64x3_t));
    v5 = v4 ? 409.6000061035156 : 0.0;
    igi2_frame.atStart[0].vZ = v5 + igi2_frame.atStart[0].vZ;
    v6 = v4 ? 409.6000061035156 : 0.0;
    igi2_frame.atStart[1].vZ = v6 + igi2_frame.atStart[1].vZ;
    v7 = *(float *)&ptQTask[6].tQTaskChildren.ptHead <= (double)*(float *)&ptQTask[6].tQTaskChildren.ptMiddle
       ? *(float *)&ptQTask[6].tQTaskChildren.ptMiddle
       : *(float *)&ptQTask[6].tQTaskChildren.ptHead;
    if ( v7 >= *(float *)&ptQTask[6].ptPrev )
      v8 = *(float *)&ptQTask[6].tQTaskChildren.ptHead <= (double)*(float *)&ptQTask[6].tQTaskChildren.ptMiddle
         ? *(float *)&ptQTask[6].tQTaskChildren.ptMiddle
         : *(float *)&ptQTask[6].tQTaskChildren.ptHead;
    else
      v8 = *(float *)&ptQTask[6].ptPrev;
    v9 = *(int **)&ptQTask[2].eQTaskType;
    if ( v9 && *v9 )
      v10 = *(float *)(*(_DWORD *)(*(_DWORD *)(*v9 + 12) + 12) + 120);
    else
      v10 = 1.0;
    igi2_frame.atEnd[0].vZ = igi2_frame.atEnd[0].vZ - (v10 * v8 + v10 * v8);
    v11 = *(float *)&ptQTask[6].tQTaskChildren.ptHead <= (double)*(float *)&ptQTask[6].tQTaskChildren.ptMiddle
        ? *(float *)&ptQTask[6].tQTaskChildren.ptMiddle
        : *(float *)&ptQTask[6].tQTaskChildren.ptHead;
    if ( v11 >= *(float *)&ptQTask[6].ptPrev )
      v12 = *(float *)&ptQTask[6].tQTaskChildren.ptHead <= (double)*(float *)&ptQTask[6].tQTaskChildren.ptMiddle
          ? *(float *)&ptQTask[6].tQTaskChildren.ptMiddle
          : *(float *)&ptQTask[6].tQTaskChildren.ptHead;
    else
      v12 = *(float *)&ptQTask[6].ptPrev;
    if ( v9 && (v13 = *v9) != 0 )
      v14 = *(float *)(*(_DWORD *)(*(_DWORD *)(v13 + 12) + 12) + 120);
    else
      v14 = 1.0;
    igi2_frame.atIntersection[0].ptHitObj = nullptr;
    igi2_frame.atIntersection[0].isHit = 0;
    igi2_frame.tTraceContext.ptEnd = igi2_frame.atEnd;
    ptNext = ptQTask[10].ptNext;
    igi2_frame.tTraceContext.eEvalQTaskEvent = 512;
    igi2_frame.tTraceContext.ptEvalContext = nullptr;
    igi2_frame.atEnd[1].vZ = v12 * v14 + v12 * v14 + igi2_frame.atEnd[1].vZ;
    qmemcpy(&igi2_frame.atIntersection[0].tPos, igi2_frame.atEnd, sizeof(igi2_frame.atIntersection[0].tPos));
    igi2_frame.atIntersection[1].ptHitObj = nullptr;
    igi2_frame.atIntersection[1].isHit = 0;
    qmemcpy(&igi2_frame.atIntersection[1].tPos, &igi2_frame.atEnd[1], sizeof(igi2_frame.atIntersection[1].tPos));
    igi2_frame.tTraceContext.ptStart = igi2_frame.atStart;
    igi2_frame.tTraceContext.ptIntersection = igi2_frame.atIntersection;
    igi2_frame.tTraceContext.nNumLines = 2;
    igi2_frame.tTraceContext.iMesh = 0;
    igi2_frame.tTraceContext.iIgnoreMaterial = 0;
    igi2_frame.tTraceContext.isTracePortals = 1;
    igi2_frame.tTraceContext.nValidationNumber = 1094861636;
    ptHead = (struct QObj_s *)ptNext->tQTaskChildren.ptHead;
    if ( ptHead->tQTask.ptNext )
    {
      if ( ptHead )
      {
        do
        {
          ((void (__cdecl *)(struct QObj_s *, struct TraceLinesContext_s *))QTask_aatQTaskFinalEvent[10][Sector_eQTaskType].pfHandler)(
            ptHead,
            &igi2_frame.tTraceContext);
          if ( igi2_frame.atIntersection[0].isHit
            && igi2_frame.atIntersection[1].isHit
            && igi2_frame.atIntersection[0].ptHitObj == igi2_frame.atIntersection[1].ptHitObj
            && igi2_frame.atIntersection[0].ptHitObj == ptHead )
          {
            if ( igi2_frame.atIntersection[0].vDistance >= igi2_frame.atIntersection[1].vDistance )
              vDistance = igi2_frame.atIntersection[1].vDistance;
            else
              vDistance = igi2_frame.atIntersection[0].vDistance;
            if ( !*((_DWORD *)pxContext + 3) || vDistance < *((double *)pxContext + 6) )
            {
              v18 = *(float *)&ptQTask[3].tQTaskChildren.ptMiddle * *(float *)&ptQTask[10].tQTaskRefList.ptMiddle
                  + *(float *)&ptQTask[3].tQTaskChildren.ptHead * *(float *)&ptQTask[10].tQTaskRefList.ptHead
                  + *(float *)&ptQTask[3].ptPrev * *(float *)&ptQTask[10].tQTaskChildren.ptTail;
              v19 = *(float *)&ptQTask[3].tQTaskRefList.ptMiddle * *(float *)&ptQTask[10].tQTaskRefList.ptMiddle
                  + *(float *)&ptQTask[3].tQTaskRefList.ptHead * *(float *)&ptQTask[10].tQTaskRefList.ptHead
                  + *(float *)&ptQTask[3].tQTaskChildren.ptTail * *(float *)&ptQTask[10].tQTaskChildren.ptTail;
              igi2_frame.Real32x3_Rotate_tTemp.vZ = *(float *)&ptQTask[3].eQTaskType
                                       * *(float *)&ptQTask[10].tQTaskRefList.ptMiddle
                                       + *(float *)&ptQTask[3].ptParent * *(float *)&ptQTask[10].tQTaskRefList.ptHead
                                       + *(float *)&ptQTask[3].tQTaskRefList.ptTail
                                       * *(float *)&ptQTask[10].tQTaskChildren.ptTail;
              *((double *)pxContext + 2) = v18 + ptHead->tPos.vX;
              *((double *)pxContext + 3) = v19 + ptHead->tPos.vY;
              v20 = igi2_frame.Real32x3_Rotate_tTemp.vZ + ptHead->tPos.vZ;
              *((_DWORD *)pxContext + 2) = ptHead;
              *((_DWORD *)pxContext + 3) = ptQTask;
              *((double *)pxContext + 4) = v20;
              *((_DWORD *)pxContext + 10) = ptQTask[10].tQTaskRefList.ptTail;
              *((double *)pxContext + 6) = vDistance;
            }
          }
          ptHead = (struct QObj_s *)ptHead->tQTask.ptNext;
        }
        while ( ptHead && ptHead->tQTask.ptNext );
      }
    }
  }
}

// source: e/3/sectorobject.c:2676  [anchor-mhash]
struct SectorObject_s *__cdecl SectorObject_CreateAttachObjects(
        struct SectorObject_s *ptSectorObject,
        struct QTask_s *ptCreator)
{
  struct SectorObject_s *result; // eax
  int v4; // edi
  struct QTask_s *AttachObject; // edx
  struct SectorObject_s *v6; // [esp+8h] [ebp-4h]

  result = (struct SectorObject_s *)ptSectorObject->tSector.tRigidDynCubeObj.tModelObj.ptLODVirModel;
  if ( result )
  {
    result = (struct SectorObject_s *)SHIWORD(result->tSector.tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask.ptNext->tQTaskChildren.ptMiddle->tQTaskChildren.ptMiddle[3].ptPrev);
    if ( (int)result > 0 )
    {
      v4 = 0;
      v6 = result;
      do
      {
        AttachObject = ModelObj_CreateAttachObject(
                         &ptSectorObject->tSector.tRigidDynCubeObj.tModelObj,
                         ptSectorObject->tSector.tRigidDynCubeObj.tModelObj.ptMagicObjContainer,
                         ptCreator,
                         &ptSectorObject->tSector.tRigidDynCubeObj.tModelObj.ptLODVirModel->aptVirModel[0]->ptModel->ptMesh->ptAttachObject[v4],
                         false,
                         true);
        if ( QTask_IsQTaskTypeDerived(AttachObject->eQTaskType, Sector_eQTaskType) )
          QTask_ChangeParent(AttachObject, ptSectorObject->ptSectorContainer);
        ++v4;
        result = (struct SectorObject_s *)((char *)v6 - 1);
        v6 = (struct SectorObject_s *)((char *)v6 - 1);
      }
      while ( v6 );
    }
  }
  return result;
}

// source: e/3/sectorobject.c:2744  [anchor-hash]
void __cdecl Sector_SetLODVirModel(struct Sector_s *ptSector, struct LODVirModel_s *ptLODVirModel)
{
  struct QTask_s *ptMagicObjContainer; // eax
  struct VirModel_s *v4; // edi
  struct QTask_s *v5; // eax

  if ( ptSector->tRigidDynCubeObj.tModelObj.ptLODVirModel != ptLODVirModel )
  {
    ptMagicObjContainer = ptSector->tRigidDynCubeObj.tModelObj.ptMagicObjContainer;
    ptSector->tRigidDynCubeObj.tModelObj.ptLODVirModel = ptLODVirModel;
    if ( ptMagicObjContainer )
    {
      QTask_Delete(ptMagicObjContainer);
      ptSector->tRigidDynCubeObj.tModelObj.ptMagicObjContainer = nullptr;
    }
    if ( ptLODVirModel )
    {
      v4 = ptLODVirModel->aptVirModel[0];
      if ( v4 )
      {
        if ( v4->ptModel->ptMesh->nAttachObject > 0 )
        {
          v5 = QTask_NewFn(nullptr, MagicObjContainer_eQTaskType, nullptr);
          v5[1].ptNext = &ptSector->tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask;
          ptSector->tRigidDynCubeObj.tModelObj.ptMagicObjContainer = v5;
          ModelObj_CreateAttachObjects(
            &ptSector->tRigidDynCubeObj.tModelObj,
            v5,
            &ptSector->tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask,
            false,
            true);
        }
      }
    }
  }
}

// source: e/3/sectorobject.c:2793  [anchor-mhash]
void __cdecl SectorObject_RunHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptHead; // edx
  int v2; // eax
  struct QTask_s *v3; // ecx
  void (__cdecl *pfHandler)(struct QTask_s *); // ecx
  int v5; // eax
  struct QTask_s *ptNext; // ecx
  int v7; // edx
  struct QTask_s *v8; // ecx
  void (__cdecl *v9)(int); // ecx
  int v10; // eax
  struct QTask_s *v11; // ecx
  struct QTask_s *v12; // ecx
  struct QTask_s *v13; // edi
  int v14; // edx
  struct QTask_s *v15; // ecx
  void (__cdecl *v16)(int); // ecx
  int v17; // eax
  struct QTask_s *v18; // ecx
  int v19; // edx
  struct QTask_s *v20; // ecx
  void (__cdecl *v21)(int); // ecx
  int v22; // eax
  struct QTask_s *v23; // ecx

  ptHead = ptQTask->tQTaskChildren.ptHead;
  if ( ptHead->ptNext && ptHead )
  {
    v2 = QTask_nProtectedQTaskStackOffset;
    do
    {
      if ( ptHead->ptNext )
        v3 = ptHead->ptNext->ptNext != nullptr ? ptHead->ptNext : nullptr;
      else
        v3 = nullptr;
      QTask_atProtectedQTaskStack[v2].ptQTask = v3;
      pfHandler = (void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[1][ptHead->eQTaskType].pfHandler;
      v5 = v2 + 1;
      QTask_nProtectedQTaskStackOffset = v5;
      if ( pfHandler )
      {
        pfHandler(ptHead);
        v5 = QTask_nProtectedQTaskStackOffset;
      }
      ptHead = (struct QTask_s *)dword_849C7DC[v5];
      v2 = v5 - 1;
      QTask_nProtectedQTaskStackOffset = v2;
    }
    while ( ptHead );
  }
  else
  {
    v2 = QTask_nProtectedQTaskStackOffset;
  }
  ptNext = ptQTask[3].ptNext;
  if ( ptNext )
  {
    v7 = (int)ptNext->tQTaskChildren.ptHead;
    if ( *(_DWORD *)v7 )
    {
      for ( ; v7; QTask_nProtectedQTaskStackOffset = v2 )
      {
        if ( *(_DWORD *)v7 )
          v8 = **(_DWORD **)v7 != 0 ? *(struct QTask_s **)v7 : nullptr;
        else
          v8 = nullptr;
        QTask_atProtectedQTaskStack[v2].ptQTask = v8;
        v9 = (void (__cdecl *)(int))QTask_aatQTaskFinalEvent[1][*(unsigned __int16 *)(v7 + 36)].pfHandler;
        v10 = v2 + 1;
        QTask_nProtectedQTaskStackOffset = v10;
        if ( v9 )
        {
          v9(v7);
          v10 = QTask_nProtectedQTaskStackOffset;
        }
        v7 = dword_849C7DC[v10];
        v2 = v10 - 1;
      }
    }
  }
  if ( *(_DWORD *)&ptQTask[2].eQTaskType )
  {
    v11 = ptQTask[10].ptNext;
    if ( v11 )
    {
      v12 = v11->tQTaskChildren.ptHead;
      if ( v12->ptNext )
      {
        v13 = v12;
        if ( v12 )
        {
          do
          {
            v14 = (int)v13->tQTaskChildren.ptHead;
            if ( *(_DWORD *)v14 && v14 )
            {
              do
              {
                if ( *(_DWORD *)v14 )
                  v15 = **(_DWORD **)v14 != 0 ? *(struct QTask_s **)v14 : nullptr;
                else
                  v15 = nullptr;
                QTask_atProtectedQTaskStack[v2].ptQTask = v15;
                v16 = (void (__cdecl *)(int))QTask_aatQTaskFinalEvent[1][*(unsigned __int16 *)(v14 + 36)].pfHandler;
                v17 = v2 + 1;
                QTask_nProtectedQTaskStackOffset = v17;
                if ( v16 )
                {
                  v16(v14);
                  v17 = QTask_nProtectedQTaskStackOffset;
                }
                v14 = dword_849C7DC[v17];
                v2 = v17 - 1;
                QTask_nProtectedQTaskStackOffset = v2;
              }
              while ( v14 );
            }
            v18 = v13[3].ptNext;
            if ( v18 )
            {
              v19 = (int)v18->tQTaskChildren.ptHead;
              if ( *(_DWORD *)v19 )
              {
                for ( ; v19; QTask_nProtectedQTaskStackOffset = v2 )
                {
                  if ( *(_DWORD *)v19 )
                    v20 = **(_DWORD **)v19 != 0 ? *(struct QTask_s **)v19 : nullptr;
                  else
                    v20 = nullptr;
                  QTask_atProtectedQTaskStack[v2].ptQTask = v20;
                  v21 = (void (__cdecl *)(int))QTask_aatQTaskFinalEvent[1][*(unsigned __int16 *)(v19 + 36)].pfHandler;
                  v22 = v2 + 1;
                  QTask_nProtectedQTaskStackOffset = v22;
                  if ( v21 )
                  {
                    v21(v19);
                    v22 = QTask_nProtectedQTaskStackOffset;
                  }
                  v19 = dword_849C7DC[v22];
                  v2 = v22 - 1;
                }
              }
            }
            v23 = v13->ptNext;
            if ( !v13->ptNext )
              break;
            if ( !v23->ptNext )
              break;
            v13 = v13->ptNext;
          }
          while ( v23 );
        }
      }
    }
  }
}

// source: e/3/sectorobject.c:2839  [anchor-caller]
void __cdecl Sector_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct LODVirModel_s *LODVirModelExistsFn; // eax
  struct QObjectVector_s *v3; // esi
  struct QObjectVector_s *v4; // esi

  ModelObj_Init((struct ModelObj_s *)ptQTask, *((struct World_s **)pxContext + 1), nullptr);
  ptQTask[7].tQTaskChildren.ptHead = nullptr;
  ptQTask[7].tQTaskChildren.ptMiddle = (struct QTask_s *)2;
  ptQTask[7].tQTaskRefList.ptHead = nullptr;
  ptQTask[7].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[7].tQTaskRefList.ptTail = nullptr;
  ptQTask[7].ptParent = nullptr;
  *(_DWORD *)&ptQTask[7].eQTaskType = 0;
  ptQTask[2].tQTaskRefList.ptTail = (struct QReference_s *)12;
  qmemcpy(&ptQTask[1], (char *)pxContext + 8, 0x18u);
  qmemcpy(&ptQTask[3].ptPrev, (char *)pxContext + 44, sizeof(struct QTask_s));
  LODVirModelExistsFn = MTP_GetLODVirModelExistsFn(*(char **)pxContext);
  Sector_SetLODVirModel((struct Sector_s *)ptQTask, LODVirModelExistsFn);
  ModelObj_AttachToParent((struct ModelObj_s *)ptQTask, (struct MagicObjCreateContext_s *)pxContext);
  v3 = (struct QObjectVector_s *)Mem_AllocFn(52, 4);
  v3->isStrictOrder = false;
  v3->nSize = 0;
  v3->nAllocated = 0;
  v3->nReallocSize = 10;
  v3->papxElement = nullptr;
  v3->nElementSize = 8;
  v3->tMemPool.nBlocks = 0;
  v3->tMemPool.nAllocatedBlocks = 0;
  v3->tMemPool.nAlignment = 4;
  v3->tMemPool.nBlockSize = 8;
  v3->tMemPool.nReAllocBlocks = 10;
  v3->tMemPool.tMemPoolFreeList.ptHead = nullptr;
  v3->tMemPool.tMemPoolSegmentList.ptHead = nullptr;
  MemPool_ReAlloc(&v3->tMemPool, 0xAu);
  QObjectVector_Realloc(v3, 0xAu);
  ptQTask[8].ptNext = (struct QTask_s *)v3;
  v4 = (struct QObjectVector_s *)Mem_AllocFn(52, 4);
  v4->isStrictOrder = false;
  v4->nSize = 0;
  v4->nAllocated = 0;
  v4->nReallocSize = 10;
  v4->papxElement = nullptr;
  v4->nElementSize = 20;
  v4->tMemPool.nBlocks = 0;
  v4->tMemPool.nAllocatedBlocks = 0;
  v4->tMemPool.nAlignment = 4;
  v4->tMemPool.nBlockSize = 20;
  v4->tMemPool.nReAllocBlocks = 10;
  v4->tMemPool.tMemPoolFreeList.ptHead = nullptr;
  v4->tMemPool.tMemPoolSegmentList.ptHead = nullptr;
  MemPool_ReAlloc(&v4->tMemPool, 0xAu);
  QObjectVector_Realloc(v4, 0xAu);
  ptQTask[8].ptPrev = (struct QTask_s *)v4;
  memset(&ptQTask[8].tQTaskChildren, 1u, 0x40u);
}

// source: e/3/sectorobject.c:2902  [anchor-mhash]
void __cdecl Sector_DeleteHandler(struct QTask_s *ptQTask)
{
  *(_DWORD *)&ptQTask[8].ptPrev->eQTaskType = 0;
  QObjectVector_Delete((struct QObjectVector_s *)ptQTask[8].ptPrev);
  Sector_CleanUpReferences((struct Sector_s *)ptQTask);
  QObjectVector_Delete((struct QObjectVector_s *)ptQTask[8].ptNext);
  if ( *(_DWORD *)&ptQTask[2].eQTaskType )
  {
    ModelObj_SetLODVirModel((struct ModelObj_s *)ptQTask, nullptr, false);
    ptQTask[7].tQTaskRefList.ptHead = nullptr;
    ptQTask[7].tQTaskRefList.ptMiddle = nullptr;
    ptQTask[7].tQTaskRefList.ptTail = nullptr;
    ptQTask[7].ptParent = nullptr;
    *(_DWORD *)&ptQTask[7].eQTaskType = 0;
  }
}

// source: e/3/sectorobject.c:2928  [anchor-mhash]
void __cdecl Sector_RegisterHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *ptNext; // eax
  int ptHead; // eax
  int v4; // edx
  struct QTask_s *v5; // ecx
  void (__cdecl *pfHandler)(int, void *); // ecx
  int v7; // edx

  ptNext = ptQTask[3].ptNext;
  if ( ptNext )
  {
    ptHead = (int)ptNext->tQTaskChildren.ptHead;
    if ( *(_DWORD *)ptHead )
    {
      if ( ptHead )
      {
        v4 = QTask_nProtectedQTaskStackOffset;
        do
        {
          if ( *(_DWORD *)ptHead )
            v5 = **(_DWORD **)ptHead != 0 ? *(struct QTask_s **)ptHead : nullptr;
          else
            v5 = nullptr;
          QTask_atProtectedQTaskStack[v4].ptQTask = v5;
          pfHandler = (void (__cdecl *)(int, void *))QTask_aatQTaskFinalEvent[DynCubeObj_eDynCubeObjRegisterQTaskEvent][*(unsigned __int16 *)(ptHead + 36)].pfHandler;
          v7 = v4 + 1;
          QTask_nProtectedQTaskStackOffset = v7;
          if ( pfHandler )
          {
            pfHandler(ptHead, pxContext);
            v7 = QTask_nProtectedQTaskStackOffset;
          }
          ptHead = dword_849C7DC[v7];
          v4 = v7 - 1;
          QTask_nProtectedQTaskStackOffset = v4;
        }
        while ( ptHead );
      }
    }
  }
}

// source: e/3/sectorobject.c:2955  [anchor-mhash]
void __cdecl Sector_UpdateAttachmentHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { float Real32x3_Rotate_tTemp_8; };
    struct { char igi2_o1[4]; struct real32x9_t Real32x9_Multiply_tTemp; };
    char igi2_extent[44];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QReference_s *ptTail; // ecx
  double v2; // st7
  double v3; // st6
  struct QTask_s *ptNext; // edx
  double v5; // st5
  double v6; // st4
  double *ptMiddle; // ecx

  ptTail = ptQTask[5].tQTaskRefList.ptTail;
  v2 = *(float *)&ptTail->pxObject * *(float *)&ptQTask[5].tQTaskChildren.ptMiddle
     + *(float *)&ptTail->ptPrev * *(float *)&ptQTask[5].tQTaskChildren.ptHead
     + *(float *)&ptTail->ptNext * *(float *)&ptQTask[5].ptPrev;
  v3 = *(float *)&ptTail[1].pxObject * *(float *)&ptQTask[5].tQTaskChildren.ptMiddle
     + *(float *)&ptTail[1].ptNext * *(float *)&ptQTask[5].ptPrev
     + *(float *)&ptTail[1].ptPrev * *(float *)&ptQTask[5].tQTaskChildren.ptHead;
  igi2_frame.Real32x3_Rotate_tTemp_8 = *(float *)&ptTail[2].pxObject * *(float *)&ptQTask[5].tQTaskChildren.ptMiddle
                          + *(float *)&ptTail[2].ptNext * *(float *)&ptQTask[5].ptPrev
                          + *(float *)&ptTail[2].ptPrev * *(float *)&ptQTask[5].tQTaskChildren.ptHead;
  igi2_frame.Real32x9_Multiply_tTemp.tX.vX = *(float *)&ptTail->ptPrev * *(float *)&ptQTask[4].tQTaskChildren.ptTail
                                + *(float *)&ptTail->pxObject * *(float *)&ptQTask[4].tQTaskRefList.ptTail
                                + *(float *)&ptTail->ptNext * *(float *)&ptQTask[4].ptPrev;
  igi2_frame.Real32x9_Multiply_tTemp.tX.vY = *(float *)&ptTail->ptPrev * *(float *)&ptQTask[4].tQTaskRefList.ptHead
                                + *(float *)&ptTail->pxObject * *(float *)&ptQTask[4].ptParent
                                + *(float *)&ptTail->ptNext * *(float *)&ptQTask[4].tQTaskChildren.ptHead;
  igi2_frame.Real32x9_Multiply_tTemp.tX.vZ = *(float *)&ptTail->ptPrev * *(float *)&ptQTask[4].tQTaskRefList.ptMiddle
                                + *(float *)&ptTail->pxObject * *(float *)&ptQTask[4].eQTaskType
                                + *(float *)&ptTail->ptNext * *(float *)&ptQTask[4].tQTaskChildren.ptMiddle;
  igi2_frame.Real32x9_Multiply_tTemp.tY.vX = *(float *)&ptTail[1].pxObject * *(float *)&ptQTask[4].tQTaskRefList.ptTail
                                + *(float *)&ptTail[1].ptNext * *(float *)&ptQTask[4].ptPrev
                                + *(float *)&ptTail[1].ptPrev * *(float *)&ptQTask[4].tQTaskChildren.ptTail;
  igi2_frame.Real32x9_Multiply_tTemp.tY.vY = *(float *)&ptTail[1].pxObject * *(float *)&ptQTask[4].ptParent
                                + *(float *)&ptTail[1].ptNext * *(float *)&ptQTask[4].tQTaskChildren.ptHead
                                + *(float *)&ptTail[1].ptPrev * *(float *)&ptQTask[4].tQTaskRefList.ptHead;
  ptNext = ptQTask[5].ptNext;
  igi2_frame.Real32x9_Multiply_tTemp.tY.vZ = *(float *)&ptTail[1].pxObject * *(float *)&ptQTask[4].eQTaskType
                                + *(float *)&ptTail[1].ptNext * *(float *)&ptQTask[4].tQTaskChildren.ptMiddle
                                + *(float *)&ptTail[1].ptPrev * *(float *)&ptQTask[4].tQTaskRefList.ptMiddle;
  igi2_frame.Real32x9_Multiply_tTemp.tZ.vX = *(float *)&ptTail[2].ptPrev * *(float *)&ptQTask[4].tQTaskChildren.ptTail
                                + *(float *)&ptTail[2].pxObject * *(float *)&ptQTask[4].tQTaskRefList.ptTail
                                + *(float *)&ptTail[2].ptNext * *(float *)&ptQTask[4].ptPrev;
  igi2_frame.Real32x9_Multiply_tTemp.tZ.vY = *(float *)&ptTail[2].ptPrev * *(float *)&ptQTask[4].tQTaskRefList.ptHead
                                + *(float *)&ptTail[2].pxObject * *(float *)&ptQTask[4].ptParent
                                + *(float *)&ptTail[2].ptNext * *(float *)&ptQTask[4].tQTaskChildren.ptHead;
  v5 = *(float *)&ptTail[2].ptPrev * *(float *)&ptQTask[4].tQTaskRefList.ptMiddle
     + *(float *)&ptTail[2].pxObject * *(float *)&ptQTask[4].eQTaskType;
  v6 = *(float *)&ptTail[2].ptNext * *(float *)&ptQTask[4].tQTaskChildren.ptMiddle;
  igi2_frame.Real32x9_Multiply_tTemp.nOps = (int)&ptTail[3].ptNext->ptNext + (unsigned int)ptNext + 1;
  igi2_frame.Real32x9_Multiply_tTemp.tZ.vZ = v5 + v6;
  qmemcpy(&ptQTask[3].ptPrev, &igi2_frame.Real32x9_Multiply_tTemp, sizeof(struct QTask_s));
  ptMiddle = (double *)ptQTask[5].tQTaskRefList.ptMiddle;
  *(double *)&ptQTask[1].ptNext = v2 + *ptMiddle;
  *(double *)&ptQTask[1].tQTaskChildren.ptHead = v3 + ptMiddle[1];
  *(double *)&ptQTask[1].tQTaskChildren.ptTail = igi2_frame.Real32x3_Rotate_tTemp_8 + ptMiddle[2];
  ModelObj_UpdateAttachments((struct ModelObj_s *)ptQTask);
}

// source: e/3/sectorobject.c:2992  [anchor-mhash]
void __cdecl Sector_RemoveHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *ptNext; // eax
  int ptHead; // eax
  int v4; // edx
  struct QTask_s *v5; // ecx
  void (__cdecl *pfHandler)(int, void *); // ecx
  int v7; // edx

  if ( ptQTask[2].tQTaskChildren.ptHead )
  {
    Sector_CleanUpReferences((struct Sector_s *)ptQTask);
    ptNext = ptQTask[3].ptNext;
    if ( ptNext )
    {
      ptHead = (int)ptNext->tQTaskChildren.ptHead;
      if ( *(_DWORD *)ptHead )
      {
        if ( ptHead )
        {
          v4 = QTask_nProtectedQTaskStackOffset;
          do
          {
            if ( *(_DWORD *)ptHead )
              v5 = **(_DWORD **)ptHead != 0 ? *(struct QTask_s **)ptHead : nullptr;
            else
              v5 = nullptr;
            QTask_atProtectedQTaskStack[v4].ptQTask = v5;
            pfHandler = (void (__cdecl *)(int, void *))QTask_aatQTaskFinalEvent[DynCubeObj_eDynCubeObjRemoveQTaskEvent][*(unsigned __int16 *)(ptHead + 36)].pfHandler;
            v7 = v4 + 1;
            QTask_nProtectedQTaskStackOffset = v7;
            if ( pfHandler )
            {
              pfHandler(ptHead, pxContext);
              v7 = QTask_nProtectedQTaskStackOffset;
            }
            ptHead = dword_849C7DC[v7];
            v4 = v7 - 1;
            QTask_nProtectedQTaskStackOffset = v4;
          }
          while ( ptHead );
        }
      }
    }
  }
}

// source: e/3/sectorobject.c:3090  [anchor-mhash]
void __cdecl SectorObject_GetClosestVertex(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *ptHead; // edi
  struct QTask_s *ptNext; // eax
  unsigned int i; // esi
  int v5; // eax
  void (__cdecl *pfHandler)(int, void *); // ecx
  struct QTask_s *v7; // edi

  ptHead = ptQTask;
  if ( ptQTask )
  {
    do
    {
      ((void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[QCube_eGetClosestVertexQTaskEvent][RigidDynCubeObj_eQTaskType].pfHandler)(
        ptHead,
        pxContext);
      ptNext = ptHead[8].ptNext;
      for ( i = 0; i < *(_DWORD *)&ptNext->eQTaskType; ++i )
      {
        v5 = **((_DWORD **)&ptNext[1].tQTaskChildren.ptHead->ptNext + i);
        pfHandler = (void (__cdecl *)(int, void *))QTask_aatQTaskFinalEvent[QCube_eGetClosestVertexQTaskEvent][*(unsigned __int16 *)(v5 + 36)].pfHandler;
        if ( pfHandler )
          pfHandler(v5, pxContext);
        ptNext = ptHead[8].ptNext;
      }
      if ( ptHead == ptQTask )
      {
        v7 = ptHead[10].ptNext;
        if ( !v7 )
          return;
        ptHead = v7->tQTaskChildren.ptHead;
      }
      else
      {
        ptHead = ptHead->ptNext;
        if ( !ptHead )
          return;
      }
    }
    while ( ptHead->ptNext && ptHead );
  }
}

// source: e/3/sectorobject.c:3128  [anchor-mhash]
void __cdecl SectorObject_RegisterHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *v2; // ebx
  struct QTask_s *ptNext; // eax
  void *v4; // edi
  struct QTask_s *ptHead; // eax
  int v6; // ecx
  int v7; // eax
  struct QTask_s *v8; // edx
  void (__cdecl *pfHandler)(int, void *); // edx
  int v10; // eax
  struct QTask_s *v11; // ecx
  int v12; // ecx
  struct QTask_s *v13; // edx
  void (__cdecl *v14)(int, void *); // edx
  int v15; // eax
  double v16; // st7
  double v17; // st7
  double v18; // st7
  int *v19; // eax
  int v20; // eax
  double v21; // st6
  float v22; // [esp+0h] [ebp-18h]

  v2 = ptQTask;
  ptNext = ptQTask[3].ptNext;
  v4 = pxContext;
  if ( ptNext && (ptHead = ptNext->tQTaskChildren.ptHead, ptHead->ptNext) && (v6 = (int)ptHead) != 0 )
  {
    v7 = QTask_nProtectedQTaskStackOffset;
    do
    {
      if ( *(_DWORD *)v6 )
        v8 = **(_DWORD **)v6 != 0 ? *(struct QTask_s **)v6 : nullptr;
      else
        v8 = nullptr;
      QTask_atProtectedQTaskStack[v7].ptQTask = v8;
      pfHandler = (void (__cdecl *)(int, void *))QTask_aatQTaskFinalEvent[DynCubeObj_eDynCubeObjRegisterQTaskEvent][*(unsigned __int16 *)(v6 + 36)].pfHandler;
      v10 = v7 + 1;
      QTask_nProtectedQTaskStackOffset = v10;
      if ( pfHandler )
      {
        pfHandler(v6, v4);
        v10 = QTask_nProtectedQTaskStackOffset;
      }
      v6 = dword_849C7DC[v10];
      v7 = v10 - 1;
      QTask_nProtectedQTaskStackOffset = v7;
    }
    while ( v6 );
  }
  else
  {
    v7 = QTask_nProtectedQTaskStackOffset;
  }
  v11 = v2[10].ptNext;
  if ( v11 )
  {
    v12 = (int)v11->tQTaskChildren.ptHead;
    if ( *(_DWORD *)v12 )
    {
      for ( ; v12; QTask_nProtectedQTaskStackOffset = v7 )
      {
        if ( *(_DWORD *)v12 )
          v13 = **(_DWORD **)v12 != 0 ? *(struct QTask_s **)v12 : nullptr;
        else
          v13 = nullptr;
        QTask_atProtectedQTaskStack[v7].ptQTask = v13;
        v14 = (void (__cdecl *)(int, void *))QTask_aatQTaskFinalEvent[DynCubeObj_eDynCubeObjRegisterQTaskEvent][*(unsigned __int16 *)(v12 + 36)].pfHandler;
        v15 = v7 + 1;
        QTask_nProtectedQTaskStackOffset = v15;
        if ( v14 )
        {
          v14(v12, v4);
          v15 = QTask_nProtectedQTaskStackOffset;
        }
        v12 = dword_849C7DC[v15];
        v7 = v15 - 1;
      }
    }
  }
  v16 = *(float *)&v2[6].tQTaskChildren.ptHead;
  ptQTask = v2;
  if ( v16 <= *(float *)&v2[6].tQTaskChildren.ptMiddle )
    v17 = *(float *)&v2[6].tQTaskChildren.ptMiddle;
  else
    v17 = *(float *)&v2[6].tQTaskChildren.ptHead;
  if ( v17 >= *(float *)&v2[6].ptPrev )
  {
    if ( *(float *)&v2[6].tQTaskChildren.ptHead <= (double)*(float *)&v2[6].tQTaskChildren.ptMiddle )
      v18 = *(float *)&v2[6].tQTaskChildren.ptMiddle;
    else
      v18 = *(float *)&v2[6].tQTaskChildren.ptHead;
  }
  else
  {
    v18 = *(float *)&v2[6].ptPrev;
  }
  v19 = *(int **)&v2[2].eQTaskType;
  if ( v19 && (v20 = *v19) != 0 )
    v21 = *(float *)(*(_DWORD *)(*(_DWORD *)(v20 + 12) + 12) + 120);
  else
    v21 = 1.0;
  v22 = v18 * v21;
  World_TriggerQTaskEventSphereSpecificTree(
    (struct World_s *)v2[2].ptParent,
    SectorObject_eRegisterInteriorEvent,
    &ptQTask,
    (struct real64x3_t *)&v2[1],
    v22,
    (unsigned int)&TerrainRender_atEdge[4623].iSplitVertex,
    WORLD_DYNCUBETREE_STATIONARY);
}

// source: e/3/sectorobject.c:3182  [anchor-mhash]
void __cdecl SectorObject_RemoveHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QReference_s *ptTail; // eax
  struct QTask_s *ptParent; // ecx
  struct QTask_s *ptNext; // eax
  struct QTask_s *ptHead; // eax
  int v6; // ecx
  int v7; // eax
  struct QTask_s *v8; // edx
  void (__cdecl *pfHandler)(int, void *); // edx
  int v10; // eax
  struct QTask_s *v11; // edi
  int v12; // ecx
  struct QTask_s *v13; // edx
  void (__cdecl *v14)(int, void *); // edx
  int v15; // eax
  struct real64x3_t tSpherePos; // [esp+4h] [ebp-18h] BYREF

  if ( ptQTask[2].tQTaskChildren.ptHead )
  {
    ptTail = ptQTask[10].tQTaskRefList.ptTail;
    ptParent = ptQTask[2].ptParent;
    tSpherePos.vX = *(float *)&ptQTask[10].tQTaskChildren.ptTail;
    tSpherePos.vY = *(float *)&ptQTask[10].tQTaskRefList.ptHead;
    tSpherePos.vZ = *(float *)&ptQTask[10].tQTaskRefList.ptMiddle;
    World_TriggerQTaskEventSphereSpecificTree(
      (struct World_s *)ptParent,
      SectorObject_eRemoveInteriorEvent,
      pxContext,
      &tSpherePos,
      *(float *)&ptTail,
      (unsigned int)&TerrainRender_atEdge[4623].iSplitVertex,
      WORLD_DYNCUBETREE_STATIONARY);
    Sector_CleanUpReferences((struct Sector_s *)ptQTask);
    ptNext = ptQTask[10].ptNext;
    if ( ptNext && (ptHead = ptNext->tQTaskChildren.ptHead, ptHead->ptNext) && (v6 = (int)ptHead) != 0 )
    {
      v7 = QTask_nProtectedQTaskStackOffset;
      do
      {
        if ( *(_DWORD *)v6 )
          v8 = **(_DWORD **)v6 != 0 ? *(struct QTask_s **)v6 : nullptr;
        else
          v8 = nullptr;
        QTask_atProtectedQTaskStack[v7].ptQTask = v8;
        pfHandler = (void (__cdecl *)(int, void *))QTask_aatQTaskFinalEvent[DynCubeObj_eDynCubeObjRemoveQTaskEvent][*(unsigned __int16 *)(v6 + 36)].pfHandler;
        v10 = v7 + 1;
        QTask_nProtectedQTaskStackOffset = v10;
        if ( pfHandler )
        {
          pfHandler(v6, pxContext);
          v10 = QTask_nProtectedQTaskStackOffset;
        }
        v6 = dword_849C7DC[v10];
        v7 = v10 - 1;
        QTask_nProtectedQTaskStackOffset = v7;
      }
      while ( v6 );
    }
    else
    {
      v7 = QTask_nProtectedQTaskStackOffset;
    }
    v11 = ptQTask[3].ptNext;
    if ( v11 )
    {
      v12 = (int)v11->tQTaskChildren.ptHead;
      if ( *(_DWORD *)v12 )
      {
        for ( ; v12; QTask_nProtectedQTaskStackOffset = v7 )
        {
          if ( *(_DWORD *)v12 )
            v13 = **(_DWORD **)v12 != 0 ? *(struct QTask_s **)v12 : nullptr;
          else
            v13 = nullptr;
          QTask_atProtectedQTaskStack[v7].ptQTask = v13;
          v14 = (void (__cdecl *)(int, void *))QTask_aatQTaskFinalEvent[DynCubeObj_eDynCubeObjRemoveQTaskEvent][*(unsigned __int16 *)(v12 + 36)].pfHandler;
          v15 = v7 + 1;
          QTask_nProtectedQTaskStackOffset = v15;
          if ( v14 )
          {
            v14(v12, pxContext);
            v15 = QTask_nProtectedQTaskStackOffset;
          }
          v12 = dword_849C7DC[v15];
          v7 = v15 - 1;
        }
      }
    }
  }
}

// source: e/3/sectorobject.c:3235  [anchor-mhash]
void __cdecl SectorObject_UpdateAttachmentHandler(struct QTask_s *ptQTask)
{
  if ( ptQTask[2].ptParent )
  {
    ModelObj_UpdateAttachment((struct ModelObj_s *)ptQTask);
    SectorObject_UpdateAttachObjects((struct SectorObject_s *)ptQTask);
  }
}

// source: e/3/sectorobject.c:3338  [anchor-callee]
int __cdecl SectorObject_RegisterInteriorDynCubeObjSpecificSectorObject(
        struct World_s *ptWorld,
        struct SectorObject_s *ptSectorObject,
        struct DynCubeObj_s *ptDynCubeObj,
        struct real64x3_t *ptPos)
{
  #pragma pack(push, 1)
  union
  {
    struct { float Real32x3_Rotate_tTemp_8; };
    struct { char igi2_o1[4]; struct real64x3_t tCenterPos; };
    struct { char igi2_o2[28]; struct GetSectorContext_t tContext; };
    char igi2_extent[88];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *ptPrev; // eax
  struct QTask_s *ptNext; // eax
  float *ptMiddle; // eax
  double v7; // rt0
  struct QObjectVector_s **ptInsideSector; // ebp
  unsigned int *p_nAllocated; // esi
  struct QObjectVector_s *v10; // edi
  struct DynCubeObj_s ***v11; // edi
  struct QObjectVector_s *v12; // esi
  unsigned int nAllocated; // eax
  struct DynCubeObj_s **v14; // ecx

  ptPrev = ptDynCubeObj[1].tQObj.tQTask.ptPrev;
  if ( ptPrev && (ptNext = ptPrev->ptNext) != nullptr )
  {
    ptMiddle = (float *)ptNext->tQTaskChildren.ptMiddle->tQTaskChildren.ptMiddle;
    igi2_frame.Real32x3_Rotate_tTemp_8 = *((float *)&ptDynCubeObj[1].tQObj.tPos.vX + 1) * ptMiddle[14]
                            + *(float *)&ptDynCubeObj[1].tQObj.tPos.vX * ptMiddle[13]
                            + *(float *)&ptDynCubeObj[1].tQObj.tQTask.eQTaskType * ptMiddle[12];
    v7 = *(float *)&ptDynCubeObj[1].tQObj.tQTask.ptParent * ptMiddle[14]
       + *(float *)&ptDynCubeObj[1].tQObj.tQTask.tQTaskRefList.ptTail * ptMiddle[13]
       + *(float *)&ptDynCubeObj[1].tQObj.tQTask.tQTaskRefList.ptMiddle * ptMiddle[12];
    igi2_frame.tCenterPos.vX = *(float *)&ptDynCubeObj[1].tQObj.tQTask.tQTaskRefList.ptHead * ptMiddle[14]
                  + *(float *)&ptDynCubeObj[1].tQObj.tQTask.tQTaskChildren.ptTail * ptMiddle[13]
                  + *(float *)&ptDynCubeObj[1].tQObj.tQTask.tQTaskChildren.ptMiddle * ptMiddle[12]
                  + ptDynCubeObj->tQObj.tPos.vX;
    igi2_frame.tCenterPos.vY = v7 + ptDynCubeObj->tQObj.tPos.vY;
    igi2_frame.tCenterPos.vZ = igi2_frame.Real32x3_Rotate_tTemp_8 + ptDynCubeObj->tQObj.tPos.vZ;
  }
  else
  {
    qmemcpy(&igi2_frame.tCenterPos, ptPos, sizeof(igi2_frame.tCenterPos));
  }
  igi2_frame.tContext.ptInsideSector = nullptr;
  igi2_frame.tContext.ptInsideSectorObject = nullptr;
  igi2_frame.tContext.ptPos = &igi2_frame.tCenterPos;
  igi2_frame.tContext.isTolerance = 1;
  if ( ptSectorObject )
    ((void (__cdecl *)(struct SectorObject_s *, struct GetSectorContext_t *))QTask_aatQTaskFinalEvent[QCube_eGetSectorQTaskEvent][ptSectorObject->tSector.tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask.eQTaskType].pfHandler)(
      ptSectorObject,
      &igi2_frame.tContext);
  else
    World_TriggerQTaskEventXyzSpecificTree(
      ptWorld,
      QCube_eGetSectorQTaskEvent,
      &igi2_frame.tContext,
      ptPos,
      0xFFFFFFFF,
      WORLD_DYNCUBETREE_STATIONARY);
  ptInsideSector = (struct QObjectVector_s **)igi2_frame.tContext.ptInsideSector;
  if ( !igi2_frame.tContext.ptInsideSector || igi2_frame.tContext.ptInsideSector == igi2_frame.tContext.ptInsideSectorObject )
  {
    ptDynCubeObj->iSector = 0;
    ptDynCubeObj->ptSector = nullptr;
    return 0;
  }
  else
  {
    p_nAllocated = &SectorObject_tInteriorDynCubeObjPool->nAllocated;
    v10 = SectorObject_tInteriorDynCubeObjPool;
    if ( SectorObject_tInteriorDynCubeObjPool->nAllocated == SectorObject_tInteriorDynCubeObjPool->nSize )
      QObjectVector_Realloc(SectorObject_tInteriorDynCubeObjPool, SectorObject_tInteriorDynCubeObjPool->nReallocSize);
    v11 = (struct DynCubeObj_s ***)v10->papxElement[(*p_nAllocated)++];
    v11[1] = (struct DynCubeObj_s **)ptInsideSector;
    v11[2] = (struct DynCubeObj_s **)igi2_frame.tContext.ptInsideSectorObject;
    v12 = ptInsideSector[80];
    if ( v12->nAllocated == v12->nSize )
      QObjectVector_Realloc(ptInsideSector[80], v12->nReallocSize);
    nAllocated = v12->nAllocated;
    v14 = (struct DynCubeObj_s **)v12->papxElement[nAllocated];
    v12->nAllocated = nAllocated + 1;
    *v11 = v14;
    *v14 = ptDynCubeObj;
    ptDynCubeObj->iSector = 1;
    ptDynCubeObj->ptSector = ptInsideSector;
    ptDynCubeObj->iRenderGroup = RenderGroup_NoShadow;
    return 1;
  }
}

// source: e/3/sectorobject.c:3449  [anchor-callee]
void __cdecl SectorObject_RemoveInteriorDynCubeObj(struct DynCubeObj_s *ptDynCubeObj)
{
  struct QObjectVector_s *v1; // ebx
  unsigned int nAllocated; // edx
  int v3; // eax
  void **i; // ecx
  struct DynCubeObj_s ***v5; // esi

  if ( ptDynCubeObj->iSector )
  {
    v1 = SectorObject_tInteriorDynCubeObjPool;
    nAllocated = SectorObject_tInteriorDynCubeObjPool->nAllocated;
    v3 = 0;
    if ( nAllocated )
    {
      for ( i = SectorObject_tInteriorDynCubeObjPool->papxElement; ; ++i )
      {
        v5 = (struct DynCubeObj_s ***)*i;
        if ( **(struct DynCubeObj_s ***)*i == ptDynCubeObj )
          break;
        if ( ++v3 >= nAllocated )
          return;
      }
      QObjectVector_RemoveElement(
        (struct QObjectVector_s *)v5[1][80],
        *(_DWORD *)((char *)v5[1][80]->tQObj.tQTask.ptParent + (unsigned int)*v5 - 4));
      *v5 = nullptr;
      QObjectVector_RemoveElement(v1, *(unsigned int *)((char *)v5 + v1->nElementSize - 4));
      ptDynCubeObj->iSector = 0;
      ptDynCubeObj->ptSector = nullptr;
      ptDynCubeObj->iRenderGroup = RenderGroup_Normal;
    }
  }
}

// source: e/3/sectorobject.c:3519  [anchor-mhash]
void __cdecl SectorInteriorObject_RegisterHandler(struct QTask_s *ptQTask, void *pxContext)
{
  double v2; // st7
  double v3; // st7
  int *v4; // eax
  int v5; // eax
  double v6; // st6
  struct QTask_s *ptHead; // ecx
  int v8; // eax
  struct QTask_s *v9; // edx
  void (__cdecl *pfHandler)(struct QTask_s *, void *); // edx
  int v11; // eax
  struct QTask_s *ptNext; // ebx
  int v13; // ecx
  struct QTask_s *v14; // edx
  void (__cdecl *v15)(int, void *); // edx
  int v16; // eax
  float ptDynCubeObj; // [esp+0h] [ebp-14h]

  if ( !ptQTask[2].tQTaskChildren.ptHead )
  {
    if ( *(float *)&ptQTask[6].tQTaskChildren.ptHead <= (double)*(float *)&ptQTask[6].tQTaskChildren.ptMiddle )
      v2 = *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
    else
      v2 = *(float *)&ptQTask[6].tQTaskChildren.ptHead;
    if ( v2 >= *(float *)&ptQTask[6].ptPrev )
    {
      if ( *(float *)&ptQTask[6].tQTaskChildren.ptHead <= (double)*(float *)&ptQTask[6].tQTaskChildren.ptMiddle )
        v3 = *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
      else
        v3 = *(float *)&ptQTask[6].tQTaskChildren.ptHead;
    }
    else
    {
      v3 = *(float *)&ptQTask[6].ptPrev;
    }
    v4 = *(int **)&ptQTask[2].eQTaskType;
    if ( v4 && (v5 = *v4) != 0 )
      v6 = *(float *)(*(_DWORD *)(*(_DWORD *)(v5 + 12) + 12) + 120);
    else
      v6 = 1.0;
    ptDynCubeObj = v3 * v6;
    World_RegisterDynCubeObjFirstTimeRadius(
      *((struct World_s **)pxContext + 1),
      (struct DynCubeObj_s *)ptQTask,
      (struct real64x3_t *)&ptQTask[1],
      ptDynCubeObj,
      WORLD_DYNCUBETREE_CATEGORY_STATIONARY);
    if ( ptQTask[7].tQTaskChildren.ptTail )
    {
      ptQTask[2].tQTaskRefList.ptHead = nullptr;
      ptQTask[2].tQTaskRefList.ptMiddle = nullptr;
    }
    else
    {
      SectorObject_RegisterInteriorDynCubeObjSpecificSectorObject(
        *((struct World_s **)pxContext + 1),
        nullptr,
        (struct DynCubeObj_s *)ptQTask,
        (struct real64x3_t *)&ptQTask[1]);
    }
    ptHead = ptQTask->tQTaskChildren.ptHead;
    if ( ptHead->ptNext && ptHead )
    {
      v8 = QTask_nProtectedQTaskStackOffset;
      do
      {
        if ( ptHead->ptNext )
          v9 = ptHead->ptNext->ptNext != nullptr ? ptHead->ptNext : nullptr;
        else
          v9 = nullptr;
        QTask_atProtectedQTaskStack[v8].ptQTask = v9;
        pfHandler = (void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[DynCubeObj_eDynCubeObjRegisterQTaskEvent][ptHead->eQTaskType].pfHandler;
        v11 = v8 + 1;
        QTask_nProtectedQTaskStackOffset = v11;
        if ( pfHandler )
        {
          pfHandler(ptHead, pxContext);
          v11 = QTask_nProtectedQTaskStackOffset;
        }
        ptHead = (struct QTask_s *)dword_849C7DC[v11];
        v8 = v11 - 1;
        QTask_nProtectedQTaskStackOffset = v8;
      }
      while ( ptHead );
    }
    else
    {
      v8 = QTask_nProtectedQTaskStackOffset;
    }
    ptNext = ptQTask[3].ptNext;
    if ( ptNext )
    {
      v13 = (int)ptNext->tQTaskChildren.ptHead;
      if ( *(_DWORD *)v13 )
      {
        for ( ; v13; QTask_nProtectedQTaskStackOffset = v8 )
        {
          if ( *(_DWORD *)v13 )
            v14 = **(_DWORD **)v13 != 0 ? *(struct QTask_s **)v13 : nullptr;
          else
            v14 = nullptr;
          QTask_atProtectedQTaskStack[v8].ptQTask = v14;
          v15 = (void (__cdecl *)(int, void *))QTask_aatQTaskFinalEvent[DynCubeObj_eDynCubeObjRegisterQTaskEvent][*(unsigned __int16 *)(v13 + 36)].pfHandler;
          v16 = v8 + 1;
          QTask_nProtectedQTaskStackOffset = v16;
          if ( v15 )
          {
            v15(v13, pxContext);
            v16 = QTask_nProtectedQTaskStackOffset;
          }
          v13 = dword_849C7DC[v16];
          v8 = v16 - 1;
        }
      }
    }
  }
}

void __cdecl sub_5A7180(struct DynCubeObj_s *a1, struct World_s **a2)
{
  struct QTask_s *ptHead; // ecx
  int v3; // eax
  struct QTask_s *v4; // edx
  void (__cdecl *pfHandler)(struct QTask_s *, struct World_s **); // edx
  int v6; // eax
  struct QTask_s *v7; // ecx
  int v8; // ecx
  struct QTask_s *v9; // edx
  void (__cdecl *v10)(int, struct World_s **); // edx
  int v11; // eax

  if ( a1->ptDynCubeObjTreeItem )
  {
    SectorObject_RemoveInteriorDynCubeObj(a1);
    World_RemoveDynCubeObj(*a2, a1);
    ptHead = a1->tQObj.tQTask.tQTaskChildren.ptHead;
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
        pfHandler = (void (__cdecl *)(struct QTask_s *, struct World_s **))QTask_aatQTaskFinalEvent[DynCubeObj_eDynCubeObjRemoveQTaskEvent][ptHead->eQTaskType].pfHandler;
        v6 = v3 + 1;
        QTask_nProtectedQTaskStackOffset = v6;
        if ( pfHandler )
        {
          pfHandler(ptHead, a2);
          v6 = QTask_nProtectedQTaskStackOffset;
        }
        ptHead = (struct QTask_s *)dword_849C7DC[v6];
        v3 = v6 - 1;
        QTask_nProtectedQTaskStackOffset = v3;
      }
      while ( ptHead );
    }
    else
    {
      v3 = QTask_nProtectedQTaskStackOffset;
    }
    v7 = a1[1].tQObj.tQTask.tQTaskChildren.ptHead;
    if ( v7 )
    {
      v8 = (int)v7->tQTaskChildren.ptHead;
      if ( *(_DWORD *)v8 )
      {
        for ( ; v8; QTask_nProtectedQTaskStackOffset = v3 )
        {
          if ( *(_DWORD *)v8 )
            v9 = **(_DWORD **)v8 != 0 ? *(struct QTask_s **)v8 : nullptr;
          else
            v9 = nullptr;
          QTask_atProtectedQTaskStack[v3].ptQTask = v9;
          v10 = (void (__cdecl *)(int, struct World_s **))QTask_aatQTaskFinalEvent[DynCubeObj_eDynCubeObjRemoveQTaskEvent][*(unsigned __int16 *)(v8 + 36)].pfHandler;
          v11 = v3 + 1;
          QTask_nProtectedQTaskStackOffset = v11;
          if ( v10 )
          {
            v10(v8, a2);
            v11 = QTask_nProtectedQTaskStackOffset;
          }
          v8 = dword_849C7DC[v11];
          v3 = v11 - 1;
        }
      }
    }
  }
}

// source: e/3/sectorobject.c:3604  [anchor-mhash]
void __cdecl SectorInteriorObject_RegisterInteriorHandler(struct QTask_s *ptQTask, void *pxContext)
{
  if ( !ptQTask[2].tQTaskRefList.ptMiddle )
  {
    if ( ptQTask[7].tQTaskChildren.ptTail )
    {
      ptQTask[2].tQTaskRefList.ptHead = nullptr;
      ptQTask[2].tQTaskRefList.ptMiddle = nullptr;
    }
    else
    {
      SectorObject_RegisterInteriorDynCubeObjSpecificSectorObject(
        (struct World_s *)ptQTask[2].ptParent,
        nullptr,
        (struct DynCubeObj_s *)ptQTask,
        (struct real64x3_t *)&ptQTask[1]);
    }
  }
}

void __cdecl sub_5A72D0(struct DynCubeObj_s *a1)
{
  if ( a1->ptSector )
    SectorObject_RemoveInteriorDynCubeObj(a1);
}

// source: e/3/sectorobject.c:3661  [anchor-strings]
void __cdecl SectorObject_Open()
{
  unsigned __int16 v0; // si
  __int16 v1; // ax
  unsigned __int16 v2; // si
  struct QObjectVector_s *v3; // esi
  struct QObjectVector_s *v4; // esi
  struct QObjectVector_s *v5; // esi

  v0 = QTask_NewQTaskType("Sector", 400, RigidDynCubeObj_eQTaskType, 0, 0);
  Sector_eQTaskType = v0;
  QTask_LinkQTaskEventHandlerFn(v0, 5, Sector_EnterHandler);
  QTask_LinkQTaskEventHandlerFn(v0, 0, Sector_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 2, Sector_DeleteHandler);
  QTask_LinkQTaskEventHandlerFn(v0, DynCubeObj_eDynCubeObjRegisterQTaskEvent, Sector_RegisterHandler);
  QTask_LinkQTaskEventHandlerFn(v0, DynCubeObj_eDynCubeObjRemoveQTaskEvent, Sector_RemoveHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, Attach_eUpdateAttachmentEvent, Sector_UpdateAttachmentHandler);
  SectorObject_eQTaskType = QTask_NewQTaskType("SectorObject", 480, v0, 0, 0);
  SectorObject_eRegisterInteriorEvent = QTask_NewQTaskEventFn(0, "Register Interior");
  v1 = QTask_NewQTaskEventFn(0, "Remove Interior");
  v2 = SectorObject_eQTaskType;
  SectorObject_eRemoveInteriorEvent = v1;
  QTask_LinkQTaskEventHandlerFn(SectorObject_eQTaskType, 5, SectorObject_EnterHandler);
  QTask_LinkQTaskEventHandlerFn(v2, 0, SectorObject_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v2, 2, SectorObject_DeleteHandler);
  QTask_LinkQTaskEventHandlerFn(v2, 11, SectorObject_GetNextZHandler);
  QTask_LinkQTaskEventHandlerFn(v2, 10, SectorObject_TraceLinesHandler);
  QTask_LinkQTaskEventHandlerFn(v2, 9, SectorObject_LineOfSightHandler);
  QTask_LinkQTaskEventHandlerFn(v2, 12, SectorObject_GetMaterialHandler);
  QTask_LinkQTaskEventHandlerFn(v2, QCube_eGetSectorQTaskEvent, SectorObject_GetSectorHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v2, 1, SectorObject_RunHandler);
  QTask_LinkQTaskEventHandlerFn(v2, QCube_eGetClosestVertexQTaskEvent, SectorObject_GetClosestVertex);
  QTask_LinkQTaskEventHandlerFn(v2, DynCubeObj_eDynCubeObjRegisterQTaskEvent, SectorObject_RegisterHandler);
  QTask_LinkQTaskEventHandlerFn(v2, DynCubeObj_eDynCubeObjRemoveQTaskEvent, SectorObject_RemoveHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v2, Attach_eUpdateAttachmentEvent, SectorObject_UpdateAttachmentHandler);
  v3 = (struct QObjectVector_s *)Mem_AllocFn(52, 4);
  v3->isStrictOrder = true;
  v3->nSize = 0;
  v3->nAllocated = 0;
  v3->nReallocSize = 0;
  v3->papxElement = nullptr;
  v3->nElementSize = 36;
  v3->tMemPool.nBlocks = 0;
  v3->tMemPool.nAllocatedBlocks = 0;
  v3->tMemPool.nAlignment = 4;
  v3->tMemPool.nBlockSize = 36;
  v3->tMemPool.nReAllocBlocks = 0;
  v3->tMemPool.tMemPoolFreeList.ptHead = nullptr;
  v3->tMemPool.tMemPoolSegmentList.ptHead = nullptr;
  MemPool_ReAlloc(&v3->tMemPool, 0x14u);
  QObjectVector_Realloc(v3, 0x14u);
  SectorObject_tRequestPool = v3;
  v4 = (struct QObjectVector_s *)Mem_AllocFn(52, 4);
  v4->isStrictOrder = true;
  v4->nSize = 0;
  v4->nAllocated = 0;
  v4->nReallocSize = 0;
  v4->papxElement = nullptr;
  v4->nElementSize = 16;
  v4->tMemPool.nBlocks = 0;
  v4->tMemPool.nAllocatedBlocks = 0;
  v4->tMemPool.nAlignment = 4;
  v4->tMemPool.nBlockSize = 16;
  v4->tMemPool.nReAllocBlocks = 0;
  v4->tMemPool.tMemPoolFreeList.ptHead = nullptr;
  v4->tMemPool.tMemPoolSegmentList.ptHead = nullptr;
  MemPool_ReAlloc(&v4->tMemPool, 0x3E8u);
  QObjectVector_Realloc(v4, 0x3E8u);
  SectorObject_tInteriorDynCubeObjPool = v4;
  v5 = (struct QObjectVector_s *)Mem_AllocFn(52, 4);
  v5->isStrictOrder = false;
  v5->nSize = 0;
  v5->nAllocated = 0;
  v5->nReallocSize = 20;
  v5->papxElement = nullptr;
  v5->nElementSize = 8;
  v5->tMemPool.nBlocks = 0;
  v5->tMemPool.nAllocatedBlocks = 0;
  v5->tMemPool.nAlignment = 4;
  v5->tMemPool.nBlockSize = 8;
  v5->tMemPool.nReAllocBlocks = 20;
  v5->tMemPool.tMemPoolFreeList.ptHead = nullptr;
  v5->tMemPool.tMemPoolSegmentList.ptHead = nullptr;
  MemPool_ReAlloc(&v5->tMemPool, 0x14u);
  QObjectVector_Realloc(v5, 0x14u);
  SectorObject_ptDiscardSectorList = v5;
  LOWORD(v5) = QTask_NewQTaskType("SectorInteriorObject", 320, RigidDynCubeObj_eQTaskType, 0, 0);
  SectorInteriorObject_eQTaskType = (unsigned __int16)v5;
  QTask_SetQTaskTypeGroup((unsigned __int16)v5, (unsigned int)&TerrainRender_atEdge[4623].iSplitVertex);
  QTask_LinkQTaskEventHandlerFn(
    (unsigned __int16)v5,
    DynCubeObj_eDynCubeObjRegisterQTaskEvent,
    SectorInteriorObject_RegisterHandler);
  QTask_LinkQTaskEventHandlerFn(
    (unsigned __int16)v5,
    DynCubeObj_eDynCubeObjRemoveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))sub_5A7180);
  QTask_LinkQTaskEventHandlerFn(
    (unsigned __int16)v5,
    SectorObject_eRegisterInteriorEvent,
    SectorInteriorObject_RegisterInteriorHandler);
  QTask_LinkQTaskEventHandlerFn(
    (unsigned __int16)v5,
    SectorObject_eRemoveInteriorEvent,
    (void (__cdecl *)(struct QTask_s *, void *))sub_5A72D0);
}

// source: e/3/sectorobject.c:3723  [anchor-hash]
void __cdecl SectorObject_Close()
{
  QObjectVector_Delete(SectorObject_tInteriorDynCubeObjPool);
  QObjectVector_Delete(SectorObject_tRequestPool);
  QObjectVector_Delete(SectorObject_ptDiscardSectorList);
  QTask_DeleteQTaskType(SectorObject_eQTaskType);
  QTask_DeleteQTaskType(Sector_eQTaskType);
  QTask_DeleteQTaskType(SectorInteriorObject_eQTaskType);
  QTask_DeleteQTaskEvent(SectorObject_eRegisterInteriorEvent);
  QTask_DeleteQTaskEvent(SectorObject_eRemoveInteriorEvent);
}

// source: e/3/sectorobject.c:3748  [size]
unsigned __int16 __cdecl SectorObject_GetQTaskType()
{
  return SectorObject_eQTaskType;
}

// source: e/3/sectorobject.c:3763  [anchor-mhash]
struct LODVirModel_s *__cdecl SectorObject_SetModel(
        struct SectorObject_s *ptSectorObject,
        struct LODVirModel_s *ptLODVirModel)
{
  struct LODVirModel_s *v2; // esi
  struct QTask_s *ptMagicObjContainer; // eax
  struct QTask_s *v5; // eax
  struct QTask_s *v6; // eax

  v2 = ptLODVirModel;
  if ( ptSectorObject->tSector.tRigidDynCubeObj.tModelObj.ptLODVirModel != ptLODVirModel )
  {
    ptMagicObjContainer = ptSectorObject->tSector.tRigidDynCubeObj.tModelObj.ptMagicObjContainer;
    ptSectorObject->tSector.tRigidDynCubeObj.tModelObj.ptLODVirModel = v2;
    if ( ptMagicObjContainer )
    {
      QTask_Delete(ptMagicObjContainer);
      ptSectorObject->tSector.tRigidDynCubeObj.tModelObj.ptMagicObjContainer = nullptr;
    }
    if ( ptSectorObject->ptSectorContainer )
    {
      QTask_Delete(ptSectorObject->ptSectorContainer);
      ptSectorObject->ptSectorContainer = nullptr;
    }
    v5 = QTask_NewFn(nullptr, MagicObjContainer_eQTaskType, nullptr);
    v5[1].ptNext = &ptSectorObject->tSector.tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask;
    ptSectorObject->tSector.tRigidDynCubeObj.tModelObj.ptMagicObjContainer = v5;
    v6 = QTask_NewFn(nullptr, MagicObjContainer_eQTaskType, nullptr);
    v6[1].ptNext = &ptSectorObject->tSector.tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask;
    ptSectorObject->ptSectorContainer = v6;
    SectorObject_CreateAttachObjects(
      ptSectorObject,
      &ptSectorObject->tSector.tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask);
    SectorObject_GetOptimalInsideSphere(
      ptSectorObject,
      &ptSectorObject->tInsideSpherePos,
      &ptSectorObject->vInsideSphereRadius);
    ptSectorObject->tSector.tRigidDynCubeObj.aptLightmapVirModel[1] = nullptr;
    ptSectorObject->tSector.tRigidDynCubeObj.aptLightmapVirModel[2] = nullptr;
    ptSectorObject->tSector.tRigidDynCubeObj.aptLightmapVirModel[3] = nullptr;
    ptSectorObject->tSector.tRigidDynCubeObj.aptLightmapVirModel[4] = nullptr;
    ptSectorObject->tSector.tRigidDynCubeObj.aptLightmapVirModel[5] = nullptr;
    return (struct LODVirModel_s *)sub_5C5600(
                                     (int)v2,
                                     (int *)&ptSectorObject->tProtectMesh,
                                     (int)&ptSectorObject->tSector.tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos,
                                     &ptSectorObject->tSector.tRigidDynCubeObj.tModelObj.tOrientation.tX.vX);
  }
  return ptLODVirModel;
}

// source: e/3/sectorobject.c:3817  [anchor-mhash]
void __cdecl SectorObject_UpdateAttachObjects(struct SectorObject_s *ptSectorObject)
{
  struct QTask_s *ptMagicObjContainer; // eax
  int ptHead; // edx
  int v3; // eax
  struct QTask_s *v4; // ecx
  int v5; // esi
  void (__cdecl *pfHandler)(int); // ecx
  int v7; // eax
  struct QTask_s *ptSectorContainer; // ecx
  int v9; // ecx
  struct QTask_s *v10; // edx
  int v11; // esi
  void (__cdecl *v12)(int); // edx
  int v13; // eax
  struct QTask_s *v14; // ecx
  struct QTask_s *v15; // edx
  int v16; // esi
  void (__cdecl *v17)(struct QTask_s *); // edx
  int v18; // eax

  ptMagicObjContainer = ptSectorObject->tSector.tRigidDynCubeObj.tModelObj.ptMagicObjContainer;
  if ( ptMagicObjContainer && (ptHead = (int)ptMagicObjContainer->tQTaskChildren.ptHead, *(_DWORD *)ptHead) && ptHead )
  {
    v3 = QTask_nProtectedQTaskStackOffset;
    do
    {
      if ( *(_DWORD *)ptHead )
        v4 = **(_DWORD **)ptHead != 0 ? *(struct QTask_s **)ptHead : nullptr;
      else
        v4 = nullptr;
      v5 = Attach_eUpdateAttachmentEvent;
      QTask_atProtectedQTaskStack[v3].ptQTask = v4;
      pfHandler = (void (__cdecl *)(int))QTask_aatQTaskFinalEvent[v5][*(unsigned __int16 *)(ptHead + 36)].pfHandler;
      v7 = v3 + 1;
      QTask_nProtectedQTaskStackOffset = v7;
      if ( pfHandler )
      {
        pfHandler(ptHead);
        v7 = QTask_nProtectedQTaskStackOffset;
      }
      ptHead = dword_849C7DC[v7];
      v3 = v7 - 1;
      QTask_nProtectedQTaskStackOffset = v3;
    }
    while ( ptHead );
  }
  else
  {
    v3 = QTask_nProtectedQTaskStackOffset;
  }
  ptSectorContainer = ptSectorObject->ptSectorContainer;
  if ( ptSectorContainer )
  {
    v9 = (int)ptSectorContainer->tQTaskChildren.ptHead;
    if ( *(_DWORD *)v9 )
    {
      for ( ; v9; QTask_nProtectedQTaskStackOffset = v3 )
      {
        if ( *(_DWORD *)v9 )
          v10 = **(_DWORD **)v9 != 0 ? *(struct QTask_s **)v9 : nullptr;
        else
          v10 = nullptr;
        v11 = Attach_eUpdateAttachmentEvent;
        QTask_atProtectedQTaskStack[v3].ptQTask = v10;
        v12 = (void (__cdecl *)(int))QTask_aatQTaskFinalEvent[v11][*(unsigned __int16 *)(v9 + 36)].pfHandler;
        v13 = v3 + 1;
        QTask_nProtectedQTaskStackOffset = v13;
        if ( v12 )
        {
          v12(v9);
          v13 = QTask_nProtectedQTaskStackOffset;
        }
        v9 = dword_849C7DC[v13];
        v3 = v13 - 1;
      }
    }
  }
  v14 = ptSectorObject->tSector.tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask.tQTaskChildren.ptHead;
  if ( v14->ptNext && v14 )
  {
    do
    {
      if ( v14->ptNext )
        v15 = v14->ptNext->ptNext != nullptr ? v14->ptNext : nullptr;
      else
        v15 = nullptr;
      v16 = Attach_eUpdateAttachmentEvent;
      QTask_atProtectedQTaskStack[v3].ptQTask = v15;
      v17 = (void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[v16][v14->eQTaskType].pfHandler;
      v18 = v3 + 1;
      QTask_nProtectedQTaskStackOffset = v18;
      if ( v17 )
      {
        v17(v14);
        v18 = QTask_nProtectedQTaskStackOffset;
      }
      v14 = (struct QTask_s *)dword_849C7DC[v18];
      v3 = v18 - 1;
      QTask_nProtectedQTaskStackOffset = v3;
    }
    while ( v14 );
  }
}

// source: e/3/sectorobject.c:3845  [size]
struct SectorObject_s *__cdecl SectorObject_SetOrientation(
        struct SectorObject_s *ptSectorObject,
        struct real32x9_t *ptOrientation)
{
  qmemcpy(
    &ptSectorObject->tSector.tRigidDynCubeObj.tModelObj.tOrientation,
    ptOrientation,
    sizeof(ptSectorObject->tSector.tRigidDynCubeObj.tModelObj.tOrientation));
  return ptSectorObject;
}

// source: e/3/sectorobject.c:3861  [anchor-mhash]
void __cdecl Sector_SetPortalOpenAdditive(
        struct Sector_s *ptSector,
        int iPortal,
        int isOpen)
{
  int v3; // eax

  if ( isOpen )
  {
    ++ptSector->atPortalStatus[iPortal].isOpen;
  }
  else
  {
    v3 = (unsigned __int8)ptSector->atPortalStatus[iPortal].isOpen;
    if ( (char)v3 <= 0 )
      ptSector->atPortalStatus[iPortal].isOpen = 0;
    else
      ptSector->atPortalStatus[iPortal].isOpen = v3 - 1;
  }
}

// source: e/3/sectorobject.c:3892  [size]
void __cdecl Sector_SetPortalOpen(
        struct Sector_s *ptSector,
        int iPortal,
        int isOpen)
{
  ptSector->atPortalStatus[iPortal].isOpen = isOpen != 0;
}

// source: e/3/sectorobject.c:3908  [anchor-mhash]
void __cdecl SectorObject_GetAveragePortalPos(
        struct SectorObject_s *ptSectorObject,
        int iPortal,
        struct real64x3_t *ptDest)
{
  double v3; // st7
  struct SectorObject_s *v4; // ecx
  double v5; // st6
  double v6; // st5
  int v7; // ebx
  struct SectorObject_s *v8; // ebp
  struct LODVirModel_s *ptLODVirModel; // eax
  struct Mesh3D_Mesh_t *ptMesh; // edi
  int *p_iStartVertex; // esi
  int v12; // ecx
  int v13; // edx
  int v14; // edx
  int v15; // eax
  double v16; // st4
  struct QTask_s *ptSectorContainer; // eax
  struct SectorObject_s *ptHead; // eax
  int v19; // [esp+8h] [ebp-18h]
  struct SectorObject_s *ptChild; // [esp+Ch] [ebp-14h]
  int nPortal; // [esp+10h] [ebp-10h]
  float tAveragePos_8; // [esp+1Ch] [ebp-4h]

  v3 = 0.0;
  v4 = SectorObject_ptActiveSectorObject;
  v5 = 0.0;
  v6 = 0.0;
  v7 = 0;
  tAveragePos_8 = 0.0;
  v8 = SectorObject_ptActiveSectorObject;
  ptChild = SectorObject_ptActiveSectorObject;
  if ( SectorObject_ptActiveSectorObject )
  {
    do
    {
      ptLODVirModel = v8->tSector.tRigidDynCubeObj.tModelObj.ptLODVirModel;
      if ( ptLODVirModel )
      {
        ptMesh = ptLODVirModel->aptVirModel[0]->ptModel->ptMesh;
        if ( ptMesh->nPortal > 0 )
        {
          p_iStartVertex = &ptMesh->ptPortal->iStartVertex;
          nPortal = ptMesh->nPortal;
          do
          {
            if ( p_iStartVertex[4] == iPortal )
            {
              v12 = *p_iStartVertex;
              v13 = *p_iStartVertex + p_iStartVertex[1];
              if ( *p_iStartVertex < v13 )
              {
                v19 = v7 + 1;
                v14 = v13 - v12;
                v15 = (int)&ptMesh->ptPortalVertex[v12];
                v7 += v14;
                do
                {
                  v15 += 12;
                  --v14;
                  v16 = 1.0 / (double)v19++;
                  v3 = v3 + (*(float *)(v15 - 12) - v3) * v16;
                  v5 = v5 + (*(float *)(v15 - 8) - v5) * v16;
                  v6 = v6 + (*(float *)(v15 - 4) - v6) * v16;
                }
                while ( v14 );
                v8 = ptChild;
              }
            }
            p_iStartVertex += 5;
            --nPortal;
          }
          while ( nPortal );
          v4 = SectorObject_ptActiveSectorObject;
        }
      }
      if ( v8 == v4 )
      {
        ptSectorContainer = v8->ptSectorContainer;
        if ( !ptSectorContainer )
          break;
        ptHead = (struct SectorObject_s *)ptSectorContainer->tQTaskChildren.ptHead;
      }
      else
      {
        ptHead = (struct SectorObject_s *)v8->tSector.tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask.ptNext;
        if ( !v8->tSector.tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask.ptNext )
          break;
      }
      if ( !ptHead->tSector.tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask.ptNext )
        break;
      v8 = ptHead;
      ptChild = ptHead;
    }
    while ( ptHead );
    tAveragePos_8 = v6;
  }
  ptDest->vX = v3 + ptSectorObject->tSector.tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos.vX;
  ptDest->vY = v5 + ptSectorObject->tSector.tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos.vY;
  ptDest->vZ = tAveragePos_8 + ptSectorObject->tSector.tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos.vZ;
}

// source: e/3/sectorobject.c:3967  [size]
unsigned __int16 __cdecl SectorInteriorObject_GetQTaskType()
{
  return SectorInteriorObject_eQTaskType;
}
