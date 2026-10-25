/* e/3/rigiddyncubeobj.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: e/3/rigiddyncubeobj.c:58  [anchor-mhash]
void __cdecl RigidDynCubeObj_BspTreeGenerationSizeHandler(struct QTask_s *ptQTask, void *pxContext)
{
  int v2; // eax
  struct QTask_s *ptHead; // ecx
  int v4; // eax
  _DWORD *v5; // ecx
  int v6; // edx

  v2 = *(_DWORD *)&ptQTask[2].eQTaskType;
  if ( v2 )
  {
    ptHead = ptQTask[7].tQTaskChildren.ptHead;
    if ( ptHead != (struct QTask_s *)-1 )
    {
      v4 = *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(v2 + 4 * (_DWORD)ptHead) + 12) + 12);
      if ( !*(_DWORD *)(v4 + 40) )
      {
        v5 = *(_DWORD **)(v4 + 44);
        if ( v5 )
        {
          v6 = *((_DWORD *)pxContext + 1);
          *(_DWORD *)pxContext += (int)(v5[1]);
          *((_DWORD *)pxContext + 1) = 3 * *v5 + v6;
        }
      }
    }
  }
}

// source: e/3/rigiddyncubeobj.c:114  [anchor-mhash]
void __cdecl RigidDynCubeObj_BspTreeGenerationListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  int v2; // eax
  struct QTask_s *ptHead; // edx
  int v4; // eax
  int *p_nNumFaces; // ebx
  unsigned __int16 *v6; // edi
  int v7; // edx
  float *v8; // eax
  double v9; // st7
  double v10; // st6
  double v11; // st5
  float *v12; // eax
  double v13; // st7
  double v14; // st6
  double v15; // st5
  double v16; // st4
  double v17; // st3
  float *v18; // eax
  double v19; // st7
  long double v20; // st7
  float *v21; // eax
  _BYTE *v22; // ebx
  int v23; // eax
  unsigned int v24; // edx
  int v25; // ebx
  int v26; // eax
  int v27; // ebx
  int v28; // eax
  int v29; // edx
  int v30; // eax
  int v31; // edi
  double v32; // st7
  float *v33; // eax
  double v34; // st6
  int v35; // edi
  int v36; // edi
  int v37; // eax
  int nI; // [esp+Ch] [ebp-A4h]
  int nIa; // [esp+Ch] [ebp-A4h]
  float tTemp_; // [esp+10h] [ebp-A0h]
  float tTemp__4; // [esp+14h] [ebp-9Ch]
  float tTemp__8; // [esp+18h] [ebp-98h]
  float tNormal; // [esp+1Ch] [ebp-94h]
  float tNormal_4; // [esp+20h] [ebp-90h]
  float tNormal_8; // [esp+24h] [ebp-8Ch]
  struct MultiMesh_Mesh_t *ptCollMesh; // [esp+28h] [ebp-88h]
  float atEdge; // [esp+2Ch] [ebp-84h]
  float atEdge_4; // [esp+30h] [ebp-80h]
  float atEdge_8; // [esp+34h] [ebp-7Ch]
  float atEdge_12; // [esp+38h] [ebp-78h]
  float Real32x3_Rotate_tTemp_4; // [esp+48h] [ebp-68h]
  float Real32x3_Rotate_tTemp_8; // [esp+4Ch] [ebp-64h]
  float Real32x3_Rotate_tTemp_8a; // [esp+4Ch] [ebp-64h]
  float v54; // [esp+54h] [ebp-5Ch]
  float v55; // [esp+58h] [ebp-58h]
  float v56; // [esp+60h] [ebp-50h]
  float v57; // [esp+64h] [ebp-4Ch]
  double atVertex_16; // [esp+78h] [ebp-38h]
  double atVertex_40; // [esp+90h] [ebp-20h]

  v2 = *(_DWORD *)&ptQTask[2].eQTaskType;
  if ( v2 )
  {
    ptHead = ptQTask[7].tQTaskChildren.ptHead;
    if ( ptHead != (struct QTask_s *)-1 )
    {
      v4 = *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(v2 + 4 * (_DWORD)ptHead) + 12) + 12);
      if ( !*(_DWORD *)(v4 + 40) )
      {
        p_nNumFaces = *(int **)(v4 + 44);
        ptCollMesh = (struct MultiMesh_Mesh_t *)p_nNumFaces;
        if ( p_nNumFaces )
        {
          v6 = (unsigned __int16 *)p_nNumFaces[4];
          nI = 0;
          if ( *p_nNumFaces > 0 )
          {
            do
            {
              v7 = p_nNumFaces[5];
              v8 = (float *)(v7 + 20 * *v6);
              v9 = v8[1] * *(float *)&ptQTask[3].tQTaskChildren.ptHead
                 + *(float *)&ptQTask[3].tQTaskChildren.ptMiddle * v8[2]
                 + *v8 * *(float *)&ptQTask[3].ptPrev;
              v54 = v8[1] * *(float *)&ptQTask[3].tQTaskRefList.ptHead
                  + *(float *)&ptQTask[3].tQTaskRefList.ptMiddle * v8[2]
                  + *v8 * *(float *)&ptQTask[3].tQTaskChildren.ptTail;
              v10 = v8[1] * *(float *)&ptQTask[3].ptParent + *(float *)&ptQTask[3].eQTaskType * v8[2];
              v11 = *v8;
              v12 = (float *)(v7 + 20 * v6[1]);
              v55 = v10 + v11 * *(float *)&ptQTask[3].tQTaskRefList.ptTail;
              v13 = v9 + *(double *)&ptQTask[1].ptNext;
              v14 = v54 + *(double *)&ptQTask[1].tQTaskChildren.ptHead;
              atVertex_16 = v55 + *(double *)&ptQTask[1].tQTaskChildren.ptTail;
              v15 = *(float *)&ptQTask[3].tQTaskChildren.ptHead * v12[1]
                  + *(float *)&ptQTask[3].tQTaskChildren.ptMiddle * v12[2]
                  + *v12 * *(float *)&ptQTask[3].ptPrev;
              v56 = v12[2] * *(float *)&ptQTask[3].tQTaskRefList.ptMiddle
                  + *v12 * *(float *)&ptQTask[3].tQTaskChildren.ptTail
                  + v12[1] * *(float *)&ptQTask[3].tQTaskRefList.ptHead;
              v16 = *(float *)&ptQTask[3].ptParent * v12[1] + *(float *)&ptQTask[3].eQTaskType * v12[2];
              v17 = *v12;
              v18 = (float *)(v7 + 20 * v6[2]);
              v57 = v16 + v17 * *(float *)&ptQTask[3].tQTaskRefList.ptTail;
              atVertex_40 = v57 + *(double *)&ptQTask[1].tQTaskChildren.ptTail;
              Real32x3_Rotate_tTemp_4 = v18[2] * *(float *)&ptQTask[3].tQTaskRefList.ptMiddle
                                      + *v18 * *(float *)&ptQTask[3].tQTaskChildren.ptTail
                                      + v18[1] * *(float *)&ptQTask[3].tQTaskRefList.ptHead;
              Real32x3_Rotate_tTemp_8 = *(float *)&ptQTask[3].ptParent * v18[1]
                                      + *(float *)&ptQTask[3].eQTaskType * v18[2]
                                      + *v18 * *(float *)&ptQTask[3].tQTaskRefList.ptTail;
              atEdge = *(float *)&ptQTask[3].tQTaskChildren.ptHead * v18[1]
                     + *(float *)&ptQTask[3].tQTaskChildren.ptMiddle * v18[2]
                     + *v18 * *(float *)&ptQTask[3].ptPrev
                     + *(double *)&ptQTask[1].ptNext
                     - v13;
              atEdge_4 = Real32x3_Rotate_tTemp_4 + *(double *)&ptQTask[1].tQTaskChildren.ptHead - v14;
              atEdge_8 = Real32x3_Rotate_tTemp_8 + *(double *)&ptQTask[1].tQTaskChildren.ptTail - atVertex_16;
              atEdge_12 = v15 + *(double *)&ptQTask[1].ptNext - v13;
              v19 = v56 + *(double *)&ptQTask[1].tQTaskChildren.ptHead - v14;
              tTemp_ = atEdge_4 * (atVertex_40 - atVertex_16) - v19 * atEdge_8;
              tNormal = tTemp_;
              tTemp__4 = -((atVertex_40 - atVertex_16) * atEdge - atEdge_12 * atEdge_8);
              tNormal_4 = tTemp__4;
              tTemp__8 = v19 * atEdge - atEdge_12 * atEdge_4;
              tNormal_8 = tTemp__8;
              if ( tTemp_ != 0.0 || tTemp__4 != 0.0 || tTemp__8 != 0.0 )
              {
                v20 = 1.0 / sqrt(tTemp_ * tTemp_ + tTemp__4 * tTemp__4 + tTemp__8 * tTemp__8);
                tNormal = tTemp_ * v20;
                tNormal_4 = tTemp__4 * v20;
                tNormal_8 = tTemp__8 * v20;
              }
              v21 = (float *)(*((_DWORD *)pxContext + 3) + 12 * (*((_DWORD *)pxContext + 7) / 3u));
              *v21 = tNormal;
              v21[1] = tNormal_4;
              v21[2] = tNormal_8;
              v22 = (_BYTE *)(16 * v6[3] + p_nNumFaces[6] + 12);
              v23 = *((_DWORD *)pxContext + 2);
              v24 = *((_DWORD *)pxContext + 7) / 3u;
              if ( *(_WORD *)v22 == 0xFFFF )
                *(_BYTE *)(v24 + v23) = 1;
              else
                *(_BYTE *)(v24 + v23) = *v22;
              *(_DWORD *)(*((_DWORD *)pxContext + 1) + 4 * *((_DWORD *)pxContext + 7)) = *((_DWORD *)pxContext + 6)
                                                                                       + *v6;
              v25 = *((_DWORD *)pxContext + 6);
              v26 = *((_DWORD *)pxContext + 7) + 1;
              *((_DWORD *)pxContext + 7) = v26;
              *(_DWORD *)(*((_DWORD *)pxContext + 1) + 4 * v26) = v25 + v6[1];
              v27 = *((_DWORD *)pxContext + 6);
              v28 = *((_DWORD *)pxContext + 7) + 1;
              *((_DWORD *)pxContext + 7) = v28;
              *(_DWORD *)(*((_DWORD *)pxContext + 1) + 4 * v28) = v27 + v6[2];
              ++*((_DWORD *)pxContext + 7);
              p_nNumFaces = &ptCollMesh->nNumFaces;
              v6 += 6;
              ++nI;
            }
            while ( nI < ptCollMesh->nNumFaces );
          }
          v29 = 0;
          if ( p_nNumFaces[1] > 0 )
          {
            v30 = 0;
            nIa = 0;
            do
            {
              v31 = p_nNumFaces[5];
              v32 = *(float *)(v30 + v31 + 4);
              v33 = (float *)(v31 + v30);
              v34 = v33[1] * *(float *)&ptQTask[3].tQTaskRefList.ptHead
                  + *(float *)&ptQTask[3].tQTaskRefList.ptMiddle * v33[2]
                  + *v33 * *(float *)&ptQTask[3].tQTaskChildren.ptTail;
              Real32x3_Rotate_tTemp_8a = v33[1] * *(float *)&ptQTask[3].ptParent
                                       + *(float *)&ptQTask[3].eQTaskType * v33[2]
                                       + *(float *)&ptQTask[3].tQTaskRefList.ptTail * *v33;
              *(double *)(*(_DWORD *)pxContext + 24 * *((_DWORD *)pxContext + 6)) = v32
                                                                                  * *(float *)&ptQTask[3].tQTaskChildren.ptHead
                                                                                  + *(float *)&ptQTask[3].tQTaskChildren.ptMiddle
                                                                                  * v33[2]
                                                                                  + *(float *)&ptQTask[3].ptPrev * *v33
                                                                                  + *(double *)&ptQTask[1].ptNext;
              v35 = *((_DWORD *)pxContext + 6) + 1;
              *((_DWORD *)pxContext + 6) = v35;
              *(double *)(*(_DWORD *)pxContext + 24 * v35 + 8) = v34 + *(double *)&ptQTask[1].tQTaskChildren.ptHead;
              v36 = *(_DWORD *)pxContext;
              v37 = *((_DWORD *)pxContext + 6) + 1;
              *((_DWORD *)pxContext + 6) = v37;
              *(double *)(v36 + 24 * v37 + 16) = Real32x3_Rotate_tTemp_8a + *(double *)&ptQTask[1].tQTaskChildren.ptTail;
              ++*((_DWORD *)pxContext + 6);
              ++v29;
              v30 = nIa + 20;
              nIa += 20;
            }
            while ( v29 < p_nNumFaces[1] );
          }
        }
      }
    }
  }
}

// source: e/3/rigiddyncubeobj.c:237  [size]
void __cdecl RigidDynCubeObj_CollisionEvalHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_BYTE *)pxContext = ptQTask != *((struct QTask_s **)pxContext + 1);
}

// source: e/3/rigiddyncubeobj.c:451  [anchor-caller]
void __cdecl RigidDynCubeObj_TraceLinesHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { float vRadius; };
    struct { float vRadiusa; };
    struct { float *vRadiusb; };
    struct { float vRadiusc; };
    struct { char igi2_o4[6]; char isDoubleFace; };
    struct { char igi2_o5[7]; char isHitFrontFace; };
    struct { char igi2_o6[8]; float ptVertex2; };
    struct { char igi2_o7[8]; struct real32x3_t *ptVertex2a; };
    struct { char igi2_o8[8]; float ptVertex2b; };
    struct { char igi2_o9[8]; float ptVertex2c; };
    struct { char igi2_o10[12]; float tStartPos; };
    struct { char igi2_o11[16]; float tStartPos_4; };
    struct { char igi2_o12[20]; float tStartPos_8; };
    struct { char igi2_o13[26]; char isHitCurrentFace; };
    struct { char igi2_o14[27]; char isHit; };
    struct { char igi2_o15[28]; float tEdge0; };
    struct { char igi2_o16[32]; float tEdge0_4; };
    struct { char igi2_o17[36]; float tEdge0_8; };
    struct { char igi2_o18[40]; float tHitPos; };
    struct { char igi2_o19[40]; float tHitPosa; };
    struct { char igi2_o20[44]; float tHitPos_4; };
    struct { char igi2_o21[44]; float tHitPos_4a; };
    struct { char igi2_o22[48]; float tHitPos_8; };
    struct { char igi2_o23[48]; float tHitPos_8a; };
    struct { char igi2_o24[52]; float v133; };
    struct { char igi2_o25[52]; float v134; };
    struct { char igi2_o26[52]; float v135; };
    struct { char igi2_o27[52]; float v136; };
    struct { char igi2_o28[56]; int nLevel; };
    struct { char igi2_o29[60]; double v138; };
    struct { char igi2_o30[60]; double v139; };
    struct { char igi2_o31[74]; char isFirstIteration; };
    struct { char igi2_o32[75]; char isHitCurrentObject; };
    struct { char igi2_o33[76]; struct real64x3_t *ptEndPos; };
    struct { char igi2_o34[80]; struct real64x3_t *ptStartPos; };
    struct { char igi2_o35[84]; float vDistance; };
    struct { char igi2_o36[84]; float vDistancea; };
    struct { char igi2_o37[84]; float vDistanceb; };
    struct { char igi2_o38[84]; float vDistancec; };
    struct { char igi2_o39[84]; double vDistanced; };
    struct { char igi2_o40[92]; int iFace; };
    struct { char igi2_o41[92]; struct QTask_s *iFacea; };
    struct { char igi2_o42[92]; float iFaceb; };
    struct { char igi2_o43[96]; float tPos; };
    struct { char igi2_o44[100]; float tPos_4; };
    struct { char igi2_o45[104]; float tPos_8; };
    struct { char igi2_o46[108]; signed int bColor; };
    struct { char igi2_o47[108]; unsigned int bColora; };
    struct { char igi2_o48[108]; double bColorb; };
    struct { char igi2_o49[108]; double bColorc; };
    struct { char igi2_o50[116]; double vDot; };
    struct { char igi2_o51[116]; double vDota; };
    struct { char igi2_o52[124]; struct MultiMesh_Mesh_t *ptCollMesh; };
    struct { char igi2_o53[128]; float tMax; };
    struct { char igi2_o54[132]; float tMax_4; };
    struct { char igi2_o55[136]; float tMax_8; };
    struct { char igi2_o56[140]; float tMin; };
    struct { char igi2_o57[144]; float tMin_4; };
    struct { char igi2_o58[148]; float tMin_8; };
    struct { char igi2_o59[152]; float v168; };
    struct { char igi2_o60[152]; float v169; };
    struct { char igi2_o61[156]; struct real32x3_t *ptVertex1; };
    struct { char igi2_o62[164]; float tTemp__4; };
    struct { char igi2_o63[172]; double vClosest; };
    struct { char igi2_o64[180]; struct MultiMesh_Sphere_t *ptSphere; };
    struct { char igi2_o65[184]; float tEdge1; };
    struct { char igi2_o66[188]; float tEdge1_4; };
    struct { char igi2_o67[192]; float tEdge1_8; };
    struct { char igi2_o68[196]; float tEndPos; };
    struct { char igi2_o69[200]; float tEndPos_4; };
    struct { char igi2_o70[204]; float tEndPos_8; };
    struct { char igi2_o71[208]; struct MultiMesh_Vertex_t *ptVertexPos; };
    struct { char igi2_o72[212]; float tDelta; };
    struct { char igi2_o73[216]; float tDelta_4; };
    struct { char igi2_o74[220]; float tDelta_8; };
    struct { char igi2_o75[224]; float tHitUV; };
    struct { char igi2_o76[228]; float tHitUV_4; };
    struct { char igi2_o77[232]; struct MultiMesh_Sphere_t *ptFirstSphere; };
    struct { char igi2_o78[236]; struct MultiMesh_Face_t *ptHitFace; };
    struct { char igi2_o79[240]; struct QTask_s *v188; };
    struct { char igi2_o80[244]; float tLight; };
    struct { char igi2_o81[248]; float tLight_4; };
    struct { char igi2_o82[256]; float tUVEdge1; };
    struct { char igi2_o83[260]; float tUVEdge1_4; };
    struct { char igi2_o84[260]; float tUVEdge1_4a; };
    struct { char igi2_o85[264]; int iHitLightmap; };
    struct { char igi2_o86[268]; int iCheck; };
    struct { char igi2_o87[272]; float tUV; };
    struct { char igi2_o88[276]; float tUV_4; };
    struct { char igi2_o89[276]; float tUV_4a; };
    struct { char igi2_o90[280]; float Real32x3_RotateInverse_tTemp; };
    struct { char igi2_o91[284]; float Real32x3_RotateInverse_tTemp_4; };
    struct { char igi2_o92[288]; float Real32x3_RotateInverse_tTemp_8; };
    struct { char igi2_o93[292]; float v202; };
    struct { char igi2_o94[296]; float v203; };
    struct { char igi2_o95[300]; float v204; };
    struct { char igi2_o96[304]; float v205; };
    struct { char igi2_o97[308]; float v206; };
    struct { char igi2_o98[312]; float v207; };
    struct { char igi2_o99[316]; float Real32x3_Rotate_tTemp; };
    struct { char igi2_o100[320]; float Real32x3_Rotate_tTemp_4; };
    struct { char igi2_o101[324]; float Real32x3_Rotate_tTemp_8; };
    struct { char igi2_o102[328]; struct MultiMesh_Material_t *ptMaterial; };
    struct { char igi2_o103[332]; float vLineLength; };
    struct { char igi2_o104[336]; float v213; };
    struct { char igi2_o105[340]; float v214; };
    struct { char igi2_o106[348]; struct Mesh3D_Mesh_t *ptMesh; };
    struct { char igi2_o107[352]; float v216; };
    struct { char igi2_o108[356]; float v217; };
    struct { char igi2_o109[360]; float v218; };
    struct { char igi2_o110[364]; double v1DivSquaredDistance; };
    struct { char igi2_o111[372]; float tTempStartPos; };
    struct { char igi2_o112[380]; float tTempStartPos_8; };
    struct { char igi2_o113[384]; float v222; };
    struct { char igi2_o114[388]; float v223; };
    struct { char igi2_o115[396]; float tAbsNormal; };
    struct { char igi2_o116[408]; float tUVEdge0; };
    struct { char igi2_o117[424]; float tTempHitPos_8; };
    struct { char igi2_o118[428]; struct MultiMesh_Sphere_t *aptSphereStack[100]; };
    char igi2_extent[828];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int *v2; // eax
  double *v3; // ebx
  int v4; // ecx
  int v5; // edi
  struct QTask_s *ptHead; // edx
  int v7; // ecx
  int v8; // ecx
  int v9; // edx
  int v10; // ecx
  bool v11; // zf
  struct MultiMesh_Mesh_t *v12; // ecx
  __int16 v13; // cx
  void (__cdecl *pfHandler)(struct QTask_s *, _DWORD); // ecx
  double v15; // st7
  bool v16; // c0
  bool v17; // c3
  struct MultiMesh_Sphere_t *v18; // edx
  double v19; // st7
  struct QTask_s *ptMiddle; // eax
  double v21; // st7
  double *p_vX; // ecx
  double v23; // st7
  double v24; // st7
  double v25; // st7
  double v26; // st7
  double v27; // st7
  double v28; // st7
  double v29; // st7
  double v30; // st6
  double v31; // st5
  double v32; // st7
  double v33; // st7
  double v34; // st7
  double v35; // st7
  double v36; // st6
  double v37; // st5
  double v38; // st7
  double v39; // st6
  double v40; // st4
  long double v41; // st5
  double v42; // st4
  double v43; // st3
  double v44; // st2
  double v45; // st4
  double v46; // st4
  double v47; // st4
  double v48; // st4
  double v49; // st4
  double v50; // st4
  int v51; // ecx
  unsigned __int16 iNext; // dx
  double v53; // st7
  double v54; // st5
  unsigned __int16 iChild; // ax
  double v56; // st7
  double vY; // st6
  double v58; // st5
  signed int v59; // eax
  unsigned __int16 *aiVertex; // ecx
  float *v61; // edx
  unsigned __int16 iPortal; // bx
  double v63; // st7
  double v64; // st7
  double v65; // st7
  double v66; // st7
  double v67; // st6
  double v68; // st7
  double v69; // st7
  double v70; // st6
  double v71; // st7
  double v72; // st7
  double v73; // st7
  double v74; // st6
  double v75; // st7
  double v76; // st6
  double v77; // st7
  double v78; // st7
  double v79; // st7
  double v80; // st7
  double v81; // st7
  double v82; // st7
  double v83; // st6
  double v84; // st5
  float *v85; // ecx
  float *v86; // edx
  int v87; // ebx
  unsigned __int16 v88; // ax
  double v89; // st7
  double v90; // st6
  double v91; // st5
  double v92; // st4
  float *v93; // ecx
  long double v94; // st7
  double v95; // st7
  double v96; // st6
  double v97; // st7
  double v98; // st6
  double v99; // st5
  double v100; // st7
  double v101; // st7
  struct QReference_s *v102; // eax
  float *v103; // eax
  unsigned int Texel; // eax
  double v105; // st7
  double v106; // st7
  double vZ; // st7
  bool v108; // cc

  v2 = (int *)pxContext;
  v3 = *(double **)pxContext;
  igi2_frame.ptEndPos = *((struct real64x3_t **)pxContext + 1);
  v4 = *(_DWORD *)&ptQTask[2].eQTaskType;
  v5 = *((_DWORD *)pxContext + 9);
  igi2_frame.ptStartPos = *(struct real64x3_t **)pxContext;
  if ( v4 )
  {
    ptHead = ptQTask[7].tQTaskChildren.ptHead;
    if ( ptHead != (struct QTask_s *)-1 )
    {
      v7 = *(_DWORD *)(v4 + 4 * (_DWORD)ptHead);
      if ( v7 )
      {
        v8 = *(_DWORD *)(*(_DWORD *)(v7 + 12) + 12);
        igi2_frame.ptMesh = (struct Mesh3D_Mesh_t *)v8;
        if ( !*(_DWORD *)(v8 + 40) )
        {
          v9 = *(_DWORD *)(v8 + 44);
          if ( v9 )
          {
            v10 = 32 * *((_DWORD *)pxContext + 5);
            v11 = v9 + v10 == 0;
            v12 = (struct MultiMesh_Mesh_t *)(v9 + v10);
            igi2_frame.ptCollMesh = v12;
            if ( !v11 )
            {
              if ( v12->nNumFaces )
              {
                igi2_frame.ptVertexPos = v12->ptVertex;
                v13 = *((_WORD *)pxContext + 6);
                if ( v13 != 512 )
                {
                  pfHandler = (void (__cdecl *)(struct QTask_s *, _DWORD))QTask_aatQTaskFinalEvent[v13][ptQTask->eQTaskType].pfHandler;
                  if ( pfHandler )
                  {
                    pfHandler(ptQTask, *((_DWORD *)pxContext + 4));
                    if ( !**((_BYTE **)pxContext + 4) )
                      return;
                    v2 = (int *)pxContext;
                  }
                }
                igi2_frame.iCheck = 0;
                if ( v2[2] > 0 )
                {
                  while ( 1 )
                  {
                    igi2_frame.isDoubleFace = 0;
                    igi2_frame.isFirstIteration = 1;
                    if ( *(_DWORD *)(v5 + 92) )
                      igi2_frame.isHitFrontFace = *(_DWORD *)(v5 + 80) != 0;
                    else
                      igi2_frame.isHitFrontFace = 0;
                    v15 = *(float *)&ptQTask[6].tQTaskChildren.ptHead;
                    v16 = v15 < *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
                    v17 = v15 == *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
                    v18 = igi2_frame.ptCollMesh->ptSphere;
                    igi2_frame.isHit = *(_BYTE *)(v5 + 92);
                    igi2_frame.isHitCurrentObject = 0;
                    igi2_frame.nLevel = 0;
                    igi2_frame.ptFirstSphere = v18;
                    igi2_frame.ptSphere = v18;
                    igi2_frame.aptSphereStack[0] = v18;
                    if ( v16 || v17 )
                      v19 = *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
                    else
                      v19 = *(float *)&ptQTask[6].tQTaskChildren.ptHead;
                    if ( v19 >= *(float *)&ptQTask[6].ptPrev )
                    {
                      if ( *(float *)&ptQTask[6].tQTaskChildren.ptHead > (double)*(float *)&ptQTask[6].tQTaskChildren.ptMiddle )
                      {
                        igi2_frame.v188 = ptQTask[6].tQTaskChildren.ptHead;
                        goto LABEL_27;
                      }
                      ptMiddle = ptQTask[6].tQTaskChildren.ptMiddle;
                    }
                    else
                    {
                      ptMiddle = ptQTask[6].ptPrev;
                    }
                    igi2_frame.v188 = ptMiddle;
LABEL_27:
                    v21 = Mesh3D_GetLODVirModelRadius(*(struct LODVirModel_s **)&ptQTask[2].eQTaskType)
                        * *(float *)&igi2_frame.v188;
                    p_vX = &igi2_frame.ptEndPos->vX;
                    igi2_frame.vRadius = v21;
                    v23 = *(double *)&ptQTask[1].ptNext - v21;
                    if ( v23 > *v3 )
                    {
                      if ( v23 > igi2_frame.ptEndPos->vX )
                        goto LABEL_226;
                      v3 = &igi2_frame.ptStartPos->vX;
                    }
                    v24 = igi2_frame.vRadius + *(double *)&ptQTask[1].ptNext;
                    if ( v24 < *v3 )
                    {
                      if ( v24 < igi2_frame.ptEndPos->vX )
                        goto LABEL_226;
                      p_vX = &igi2_frame.ptEndPos->vX;
                      v3 = &igi2_frame.ptStartPos->vX;
                    }
                    v25 = *(double *)&ptQTask[1].tQTaskChildren.ptHead - igi2_frame.vRadius;
                    if ( v25 > v3[1] )
                    {
                      if ( v25 > p_vX[1] )
                        goto LABEL_226;
                      p_vX = &igi2_frame.ptEndPos->vX;
                      v3 = &igi2_frame.ptStartPos->vX;
                    }
                    v26 = igi2_frame.vRadius + *(double *)&ptQTask[1].tQTaskChildren.ptHead;
                    if ( v26 < v3[1] )
                    {
                      if ( v26 < p_vX[1] )
                        goto LABEL_226;
                      p_vX = &igi2_frame.ptEndPos->vX;
                      v3 = &igi2_frame.ptStartPos->vX;
                    }
                    v27 = *(double *)&ptQTask[1].tQTaskChildren.ptTail - igi2_frame.vRadius;
                    if ( v27 > v3[2] )
                    {
                      if ( v27 > p_vX[2] )
                        goto LABEL_226;
                      p_vX = &igi2_frame.ptEndPos->vX;
                      v3 = &igi2_frame.ptStartPos->vX;
                    }
                    v28 = igi2_frame.vRadius + *(double *)&ptQTask[1].tQTaskChildren.ptTail;
                    if ( v28 < v3[2] )
                    {
                      if ( v28 < p_vX[2] )
                        goto LABEL_226;
                      p_vX = &igi2_frame.ptEndPos->vX;
                      v3 = &igi2_frame.ptStartPos->vX;
                    }
                    v29 = *v3 - *(double *)&ptQTask[1].ptNext;
                    v30 = v3[1] - *(double *)&ptQTask[1].tQTaskChildren.ptHead;
                    v31 = v3[2] - *(double *)&ptQTask[1].tQTaskChildren.ptTail;
                    igi2_frame.v202 = v31 * *(float *)&ptQTask[3].tQTaskRefList.ptTail
                         + v29 * *(float *)&ptQTask[3].ptPrev
                         + v30 * *(float *)&ptQTask[3].tQTaskChildren.ptTail;
                    igi2_frame.v203 = v30 * *(float *)&ptQTask[3].tQTaskRefList.ptHead
                         + v31 * *(float *)&ptQTask[3].ptParent
                         + v29 * *(float *)&ptQTask[3].tQTaskChildren.ptHead;
                    igi2_frame.v204 = v31 * *(float *)&ptQTask[3].eQTaskType
                         + v29 * *(float *)&ptQTask[3].tQTaskChildren.ptMiddle
                         + v30 * *(float *)&ptQTask[3].tQTaskRefList.ptMiddle;
                    v32 = 1.0 / *(float *)&ptQTask[6].ptPrev;
                    igi2_frame.vDistance = v32;
                    igi2_frame.tStartPos = v32 * igi2_frame.v202;
                    v33 = 1.0 / *(float *)&ptQTask[6].tQTaskChildren.ptHead;
                    igi2_frame.v133 = v33;
                    igi2_frame.tStartPos_4 = v33 * igi2_frame.v203;
                    v34 = 1.0 / *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
                    igi2_frame.vRadiusa = v34;
                    igi2_frame.tStartPos_8 = v34 * igi2_frame.v204;
                    v35 = *p_vX - *(double *)&ptQTask[1].ptNext;
                    v36 = p_vX[1] - *(double *)&ptQTask[1].tQTaskChildren.ptHead;
                    v37 = p_vX[2] - *(double *)&ptQTask[1].tQTaskChildren.ptTail;
                    igi2_frame.v205 = v37 * *(float *)&ptQTask[3].tQTaskRefList.ptTail
                         + v35 * *(float *)&ptQTask[3].ptPrev
                         + v36 * *(float *)&ptQTask[3].tQTaskChildren.ptTail;
                    igi2_frame.v206 = v37 * *(float *)&ptQTask[3].ptParent
                         + v35 * *(float *)&ptQTask[3].tQTaskChildren.ptHead
                         + v36 * *(float *)&ptQTask[3].tQTaskRefList.ptHead;
                    igi2_frame.v207 = v37 * *(float *)&ptQTask[3].eQTaskType
                         + v35 * *(float *)&ptQTask[3].tQTaskChildren.ptMiddle
                         + v36 * *(float *)&ptQTask[3].tQTaskRefList.ptMiddle;
                    igi2_frame.tEndPos = igi2_frame.vDistance * igi2_frame.v205;
                    igi2_frame.tHitPos = igi2_frame.tEndPos;
                    igi2_frame.tEndPos_4 = igi2_frame.v133 * igi2_frame.v206;
                    igi2_frame.tHitPos_4 = igi2_frame.tEndPos_4;
                    igi2_frame.tEndPos_8 = igi2_frame.vRadiusa * igi2_frame.v207;
                    igi2_frame.tHitPos_8 = igi2_frame.tEndPos_8;
                    v38 = igi2_frame.tEndPos_4 - igi2_frame.tStartPos_4;
                    v39 = igi2_frame.tEndPos - igi2_frame.tStartPos;
                    v40 = igi2_frame.tEndPos_8 - igi2_frame.tStartPos_8;
                    igi2_frame.ptVertex2 = v40;
                    v41 = v40 * v40 + v39 * v39 + v38 * v38;
                    igi2_frame.vLineLength = sqrt(v41);
                    if ( igi2_frame.isHit )
                    {
                      v42 = *(double *)(v5 + 8) - *(double *)&ptQTask[1].ptNext;
                      v43 = *(double *)(v5 + 16) - *(double *)&ptQTask[1].tQTaskChildren.ptHead;
                      v44 = *(double *)(v5 + 24) - *(double *)&ptQTask[1].tQTaskChildren.ptTail;
                      igi2_frame.Real32x3_RotateInverse_tTemp = v44 * *(float *)&ptQTask[3].tQTaskRefList.ptTail
                                                   + v42 * *(float *)&ptQTask[3].ptPrev
                                                   + v43 * *(float *)&ptQTask[3].tQTaskChildren.ptTail;
                      igi2_frame.Real32x3_RotateInverse_tTemp_4 = v44 * *(float *)&ptQTask[3].ptParent
                                                     + v42 * *(float *)&ptQTask[3].tQTaskChildren.ptHead
                                                     + v43 * *(float *)&ptQTask[3].tQTaskRefList.ptHead;
                      igi2_frame.Real32x3_RotateInverse_tTemp_8 = v44 * *(float *)&ptQTask[3].eQTaskType
                                                     + v42 * *(float *)&ptQTask[3].tQTaskChildren.ptMiddle
                                                     + v43 * *(float *)&ptQTask[3].tQTaskRefList.ptMiddle;
                      igi2_frame.tHitPos = igi2_frame.vDistance * igi2_frame.Real32x3_RotateInverse_tTemp;
                      igi2_frame.tHitPos_4 = igi2_frame.v133 * igi2_frame.Real32x3_RotateInverse_tTemp_4;
                      igi2_frame.tHitPos_8 = igi2_frame.vRadiusa * igi2_frame.Real32x3_RotateInverse_tTemp_8;
                      igi2_frame.iFaceb = sqrt(
                                 (igi2_frame.tHitPos_8 - igi2_frame.tStartPos_8) * (igi2_frame.tHitPos_8 - igi2_frame.tStartPos_8)
                               + (igi2_frame.tHitPos - igi2_frame.tStartPos) * (igi2_frame.tHitPos - igi2_frame.tStartPos)
                               + (igi2_frame.tHitPos_4 - igi2_frame.tStartPos_4) * (igi2_frame.tHitPos_4 - igi2_frame.tStartPos_4));
                      igi2_frame.vClosest = igi2_frame.iFaceb;
                    }
                    if ( igi2_frame.tStartPos >= (double)igi2_frame.tHitPos )
                      v45 = igi2_frame.tHitPos;
                    else
                      v45 = igi2_frame.tStartPos;
                    igi2_frame.tMin = v45 - 40.959999084472656;
                    if ( igi2_frame.tStartPos_4 >= (double)igi2_frame.tHitPos_4 )
                      v46 = igi2_frame.tHitPos_4;
                    else
                      v46 = igi2_frame.tStartPos_4;
                    igi2_frame.tMin_4 = v46 - 40.959999084472656;
                    if ( igi2_frame.tStartPos_8 >= (double)igi2_frame.tHitPos_8 )
                      v47 = igi2_frame.tHitPos_8;
                    else
                      v47 = igi2_frame.tStartPos_8;
                    igi2_frame.tMin_8 = v47 - 40.959999084472656;
                    if ( igi2_frame.tStartPos <= (double)igi2_frame.tHitPos )
                      v48 = igi2_frame.tHitPos;
                    else
                      v48 = igi2_frame.tStartPos;
                    igi2_frame.tMax = v48 + 40.959999084472656;
                    if ( igi2_frame.tStartPos_4 <= (double)igi2_frame.tHitPos_4 )
                      v49 = igi2_frame.tHitPos_4;
                    else
                      v49 = igi2_frame.tStartPos_4;
                    igi2_frame.tMax_4 = v49 + 40.959999084472656;
                    if ( igi2_frame.tStartPos_8 <= (double)igi2_frame.tHitPos_8 )
                      v50 = igi2_frame.tHitPos_8;
                    else
                      v50 = igi2_frame.tStartPos_8;
                    igi2_frame.tHitPosa = igi2_frame.vDistance * igi2_frame.v205;
                    igi2_frame.tMax_8 = v50 + 40.959999084472656;
                    igi2_frame.tHitPos_8a = igi2_frame.vRadiusa * igi2_frame.v207;
                    igi2_frame.tDelta_8 = igi2_frame.ptVertex2;
                    igi2_frame.tHitPos_4a = igi2_frame.v133 * igi2_frame.v206;
                    igi2_frame.v1DivSquaredDistance = 1.0 / v41;
                    igi2_frame.tDelta = v39;
                    igi2_frame.tDelta_4 = v38;
                    if ( igi2_frame.ptCollMesh->nNumSpheres )
                    {
LABEL_72:
                      v51 = igi2_frame.nLevel;
                      while ( 1 )
                      {
                        if ( igi2_frame.isFirstIteration )
                        {
LABEL_82:
                          iChild = v18->iChild;
                          igi2_frame.isFirstIteration = 0;
                          if ( iChild )
                          {
                            do
                            {
                              v18 = &igi2_frame.ptFirstSphere[iChild];
                              igi2_frame.v169 = v18->tSphere.vRadius;
                              ++v51;
                              v56 = v18->tSphere.tPos.vX - igi2_frame.tStartPos;
                              igi2_frame.ptSphere = v18;
                              vY = v18->tSphere.tPos.vY;
                              igi2_frame.aptSphereStack[v51] = v18;
                              igi2_frame.bColorc = vY - igi2_frame.tStartPos_4;
                              igi2_frame.vDota = v18->tSphere.tPos.vZ - igi2_frame.tStartPos_8;
                              v58 = igi2_frame.vDota * igi2_frame.tDelta_8 + igi2_frame.bColorc * igi2_frame.tDelta_4 + v56 * igi2_frame.tDelta;
                              if ( igi2_frame.v169 * igi2_frame.v169 < igi2_frame.vDota * igi2_frame.vDota
                                               + v56 * v56
                                               + igi2_frame.bColorc * igi2_frame.bColorc
                                               - v58 * v58 * igi2_frame.v1DivSquaredDistance )
                                break;
                              if ( v18->tSphere.vRadius + v18->tSphere.tPos.vX < igi2_frame.tMin )
                                break;
                              if ( v18->tSphere.vRadius + v18->tSphere.tPos.vY < igi2_frame.tMin_4 )
                                break;
                              if ( v18->tSphere.vRadius + v18->tSphere.tPos.vZ < igi2_frame.tMin_8 )
                                break;
                              if ( v18->tSphere.tPos.vX - v18->tSphere.vRadius > igi2_frame.tMax )
                                break;
                              if ( v18->tSphere.tPos.vY - v18->tSphere.vRadius > igi2_frame.tMax_4 )
                                break;
                              if ( v18->tSphere.tPos.vZ - v18->tSphere.vRadius > igi2_frame.tMax_8 )
                                break;
                              iChild = v18->iChild;
                            }
                            while ( iChild );
                            igi2_frame.nLevel = v51;
                          }
                          if ( v18->nFace )
                          {
                            v59 = v18->iFace;
                            aiVertex = igi2_frame.ptCollMesh->ptFace[v59].aiVertex;
                            igi2_frame.iFace = v59;
                            igi2_frame.bColor = v59 + v18->nFace;
                            if ( v59 >= igi2_frame.bColor )
                              goto LABEL_72;
                            igi2_frame.ptMaterial = igi2_frame.ptCollMesh->ptMaterial;
                            while ( 1 )
                            {
                              igi2_frame.vRadiusb = &igi2_frame.ptVertexPos[aiVertex[1]].tPos.vX;
                              igi2_frame.ptVertex2a = &igi2_frame.ptVertexPos[aiVertex[2]].tPos;
                              v61 = &igi2_frame.ptVertexPos[*aiVertex].tPos.vX;
                              iPortal = igi2_frame.ptMaterial[aiVertex[3]].iPortal;
                              igi2_frame.isHitCurrentFace = 0;
                              if ( iPortal != 0xFFFF && !*((_DWORD *)pxContext + 6) )
                                goto LABEL_154;
                              if ( igi2_frame.tMin > (double)*v61 && igi2_frame.tMin > (double)*igi2_frame.vRadiusb && igi2_frame.tMin > (double)igi2_frame.ptVertex2a->vX )
                                goto LABEL_154;
                              if ( igi2_frame.tMin_4 > (double)v61[1]
                                && igi2_frame.tMin_4 > (double)igi2_frame.vRadiusb[1]
                                && igi2_frame.tMin_4 > (double)igi2_frame.ptVertex2a->vY )
                              {
                                goto LABEL_154;
                              }
                              if ( igi2_frame.tMin_8 > (double)v61[2]
                                && igi2_frame.tMin_8 > (double)igi2_frame.vRadiusb[2]
                                && igi2_frame.tMin_8 > (double)igi2_frame.ptVertex2a->vZ )
                              {
                                goto LABEL_154;
                              }
                              if ( igi2_frame.tMax < (double)*v61 && igi2_frame.tMax < (double)*igi2_frame.vRadiusb && igi2_frame.tMax < (double)igi2_frame.ptVertex2a->vX )
                                goto LABEL_154;
                              if ( igi2_frame.tMax_4 < (double)v61[1]
                                && igi2_frame.tMax_4 < (double)igi2_frame.vRadiusb[1]
                                && igi2_frame.tMax_4 < (double)igi2_frame.ptVertex2a->vY )
                              {
                                goto LABEL_154;
                              }
                              if ( igi2_frame.tMax_8 < (double)v61[2]
                                && igi2_frame.tMax_8 < (double)igi2_frame.vRadiusb[2]
                                && igi2_frame.tMax_8 < (double)igi2_frame.ptVertex2a->vZ )
                              {
                                goto LABEL_154;
                              }
                              igi2_frame.tEdge0 = igi2_frame.ptVertex2a->vX - *v61;
                              igi2_frame.tEdge0_4 = igi2_frame.ptVertex2a->vY - v61[1];
                              igi2_frame.tEdge0_8 = igi2_frame.ptVertex2a->vZ - v61[2];
                              igi2_frame.tEdge1 = *igi2_frame.vRadiusb - *v61;
                              igi2_frame.tEdge1_4 = igi2_frame.vRadiusb[1] - v61[1];
                              v63 = igi2_frame.vRadiusb[2] - v61[2];
                              igi2_frame.tEdge1_8 = v63;
                              igi2_frame.vDistancea = v63 * igi2_frame.tEdge0_4 - igi2_frame.tEdge1_4 * igi2_frame.tEdge0_8;
                              v64 = igi2_frame.tEdge1_8 * igi2_frame.tEdge0 - igi2_frame.tEdge1 * igi2_frame.tEdge0_8;
                              igi2_frame.v134 = v64;
                              igi2_frame.tTemp__4 = -v64;
                              igi2_frame.ptVertex2b = igi2_frame.tEdge1_4 * igi2_frame.tEdge0 - igi2_frame.tEdge1 * igi2_frame.tEdge0_4;
                              igi2_frame.vDot = igi2_frame.ptVertex2b * igi2_frame.tDelta_8 + igi2_frame.tTemp__4 * igi2_frame.tDelta_4 + igi2_frame.vDistancea * igi2_frame.tDelta;
                              if ( igi2_frame.vDot == 0.0 || iPortal != 0xFFFF && igi2_frame.vDot > 0.0 )
                                goto LABEL_154;
                              v65 = ((v61[1] - igi2_frame.tStartPos_4) * igi2_frame.tTemp__4
                                   + (*v61 - igi2_frame.tStartPos) * igi2_frame.vDistancea
                                   + (v61[2] - igi2_frame.tStartPos_8) * igi2_frame.ptVertex2b)
                                  / igi2_frame.vDot;
                              igi2_frame.vRadiusc = v65;
                              if ( v65 < 0.0 || igi2_frame.vRadiusc > 1.0 )
                                goto LABEL_154;
                              igi2_frame.tPos = igi2_frame.vRadiusc * igi2_frame.tDelta + igi2_frame.tStartPos;
                              igi2_frame.tPos_4 = igi2_frame.vRadiusc * igi2_frame.tDelta_4 + igi2_frame.tStartPos_4;
                              igi2_frame.tPos_8 = igi2_frame.vRadiusc * igi2_frame.tDelta_8 + igi2_frame.tStartPos_8;
                              if ( igi2_frame.vDistancea >= 0.0 )
                                igi2_frame.tAbsNormal = igi2_frame.vDistancea;
                              else
                                igi2_frame.tAbsNormal = -igi2_frame.vDistancea;
                              v66 = igi2_frame.tTemp__4;
                              if ( igi2_frame.tTemp__4 < 0.0 )
                                v66 = -v66;
                              v67 = igi2_frame.ptVertex2b;
                              if ( igi2_frame.ptVertex2b < 0.0 )
                                v67 = -v67;
                              if ( igi2_frame.tAbsNormal > v66 && igi2_frame.tAbsNormal > v67 )
                                break;
                              if ( v66 > v67 )
                              {
                                v72 = igi2_frame.v134;
                                if ( igi2_frame.v134 == 0.0 )
                                  goto LABEL_154;
                                igi2_frame.ptVertex2c = igi2_frame.tPos_8 - v61[2];
                                igi2_frame.v135 = igi2_frame.tPos - *v61;
                                igi2_frame.v139 = (igi2_frame.ptVertex2c * igi2_frame.tEdge0 - igi2_frame.v135 * igi2_frame.tEdge0_8) / v72;
                                if ( igi2_frame.v139 < 0.0 || igi2_frame.v139 > 1.0 )
                                  goto LABEL_154;
                                v73 = igi2_frame.tEdge0;
                                if ( igi2_frame.tEdge0 < 0.0 )
                                  v73 = -v73;
                                v74 = igi2_frame.tEdge0_8;
                                if ( igi2_frame.tEdge0_8 < 0.0 )
                                  v74 = -v74;
                                if ( v73 > v74 )
                                {
                                  v71 = (igi2_frame.v135 - igi2_frame.tEdge1 * igi2_frame.v139) / igi2_frame.tEdge0;
                                  goto LABEL_152;
                                }
LABEL_150:
                                if ( igi2_frame.tEdge0_8 == 0.0 )
                                  goto LABEL_154;
                                v71 = (igi2_frame.ptVertex2c - igi2_frame.tEdge1_8 * igi2_frame.v139) / igi2_frame.tEdge0_8;
                                goto LABEL_152;
                              }
                              if ( igi2_frame.ptVertex2b == 0.0 )
                                goto LABEL_154;
                              igi2_frame.vDistancec = igi2_frame.tPos_4 - v61[1];
                              igi2_frame.v136 = igi2_frame.tPos - *v61;
                              igi2_frame.v139 = (igi2_frame.vDistancec * igi2_frame.tEdge0 - igi2_frame.v136 * igi2_frame.tEdge0_4) / igi2_frame.ptVertex2b;
                              if ( igi2_frame.v139 < 0.0 || igi2_frame.v139 > 1.0 )
                                goto LABEL_154;
                              v75 = igi2_frame.tEdge0;
                              if ( igi2_frame.tEdge0 < 0.0 )
                                v75 = -v75;
                              v76 = igi2_frame.tEdge0_4;
                              if ( igi2_frame.tEdge0_4 < 0.0 )
                                v76 = -v76;
                              if ( v75 <= v76 )
                              {
                                if ( igi2_frame.tEdge0_4 == 0.0 )
                                  goto LABEL_154;
                                v71 = (igi2_frame.vDistancec - igi2_frame.tEdge1_4 * igi2_frame.v139) / igi2_frame.tEdge0_4;
                              }
                              else
                              {
                                v71 = (igi2_frame.v136 - igi2_frame.tEdge1 * igi2_frame.v139) / igi2_frame.tEdge0;
                              }
                              if ( v71 < 0.0 || igi2_frame.v139 + v71 > 1.0 )
                                goto LABEL_154;
LABEL_169:
                              igi2_frame.vDistanced = igi2_frame.vRadiusc * igi2_frame.vLineLength;
                              if ( !igi2_frame.isHit )
                              {
                                igi2_frame.isDoubleFace = 0;
                                goto LABEL_181;
                              }
                              if ( igi2_frame.vDistanced + 40.96 < igi2_frame.vClosest )
                              {
                                igi2_frame.isDoubleFace = 0;
LABEL_181:
                                if ( igi2_frame.ptMaterial[aiVertex[3]].iMaterial != *((_DWORD *)pxContext + 7) )
                                {
                                  igi2_frame.tHitUV = v71;
                                  igi2_frame.tHitUV_4 = igi2_frame.v139;
                                  igi2_frame.isHitFrontFace = igi2_frame.vDot < 0.0;
                                  igi2_frame.tHitPos_4a = igi2_frame.vRadiusc * igi2_frame.tDelta_4 + igi2_frame.tStartPos_4;
                                  igi2_frame.vClosest = igi2_frame.vRadiusc * igi2_frame.vLineLength;
                                  igi2_frame.iHitLightmap = aiVertex[4];
                                  igi2_frame.tHitPosa = igi2_frame.vRadiusc * igi2_frame.tDelta + igi2_frame.tStartPos;
                                  igi2_frame.isHitCurrentObject = 1;
                                  igi2_frame.isHit = 1;
                                  igi2_frame.ptHitFace = (struct MultiMesh_Face_t *)aiVertex;
                                  igi2_frame.tHitPos_8a = igi2_frame.vRadiusc * igi2_frame.tDelta_8 + igi2_frame.tStartPos_8;
                                  if ( igi2_frame.tStartPos >= (double)igi2_frame.tPos )
                                    v77 = igi2_frame.tPos;
                                  else
                                    v77 = igi2_frame.tStartPos;
                                  igi2_frame.tMin = v77 - 40.959999084472656;
                                  if ( igi2_frame.tStartPos_4 >= (double)igi2_frame.tPos_4 )
                                    v78 = igi2_frame.tPos_4;
                                  else
                                    v78 = igi2_frame.tStartPos_4;
                                  igi2_frame.tMin_4 = v78 - 40.959999084472656;
                                  if ( igi2_frame.tStartPos_8 >= (double)igi2_frame.tPos_8 )
                                    v79 = igi2_frame.tPos_8;
                                  else
                                    v79 = igi2_frame.tStartPos_8;
                                  igi2_frame.tMin_8 = v79 - 40.959999084472656;
                                  if ( igi2_frame.tStartPos <= (double)igi2_frame.tPos )
                                    v80 = igi2_frame.tPos;
                                  else
                                    v80 = igi2_frame.tStartPos;
                                  igi2_frame.tMax = v80 + 40.959999084472656;
                                  if ( igi2_frame.tStartPos_4 <= (double)igi2_frame.tPos_4 )
                                    v81 = igi2_frame.tPos_4;
                                  else
                                    v81 = igi2_frame.tStartPos_4;
                                  igi2_frame.tMax_4 = v81 + 40.959999084472656;
                                  if ( igi2_frame.tStartPos_8 <= (double)igi2_frame.tPos_8 )
                                    v82 = igi2_frame.tPos_8 + 40.959999084472656;
                                  else
                                    v82 = igi2_frame.tStartPos_8 + 40.959999084472656;
                                  igi2_frame.tMax_8 = v82;
                                }
                                goto LABEL_154;
                              }
                              if ( igi2_frame.vDistanced >= igi2_frame.vClosest )
                              {
                                if ( igi2_frame.vDistanced - 40.96 >= igi2_frame.vClosest )
                                  goto LABEL_154;
                                if ( igi2_frame.vDot >= 0.0 )
                                  goto LABEL_180;
LABEL_178:
                                if ( igi2_frame.isHitFrontFace )
                                  goto LABEL_180;
                                goto LABEL_179;
                              }
                              if ( igi2_frame.vDot >= 0.0 )
                                goto LABEL_178;
LABEL_179:
                              igi2_frame.isHitCurrentFace = 1;
LABEL_180:
                              igi2_frame.isDoubleFace = 1;
                              if ( igi2_frame.isHitCurrentFace )
                                goto LABEL_181;
LABEL_154:
                              aiVertex += 6;
                              if ( ++igi2_frame.iFace >= igi2_frame.bColor )
                              {
                                v18 = igi2_frame.ptSphere;
                                goto LABEL_72;
                              }
                            }
                            v68 = igi2_frame.vDistancea;
                            if ( igi2_frame.vDistancea == 0.0 )
                              goto LABEL_154;
                            igi2_frame.ptVertex2c = igi2_frame.tPos_8 - v61[2];
                            igi2_frame.vDistanceb = igi2_frame.tPos_4 - v61[1];
                            igi2_frame.v139 = (igi2_frame.ptVertex2c * igi2_frame.tEdge0_4 - igi2_frame.vDistanceb * igi2_frame.tEdge0_8) / v68;
                            if ( igi2_frame.v139 < 0.0 || igi2_frame.v139 > 1.0 )
                              goto LABEL_154;
                            v69 = igi2_frame.tEdge0_4;
                            if ( igi2_frame.tEdge0_4 < 0.0 )
                              v69 = -v69;
                            v70 = igi2_frame.tEdge0_8;
                            if ( igi2_frame.tEdge0_8 < 0.0 )
                              v70 = -v70;
                            if ( v69 > v70 )
                            {
                              v71 = (igi2_frame.vDistanceb - igi2_frame.tEdge1_4 * igi2_frame.v139) / igi2_frame.tEdge0_4;
LABEL_152:
                              if ( v71 < 0.0 || igi2_frame.v139 + v71 > 1.0 )
                                goto LABEL_154;
                              goto LABEL_169;
                            }
                            goto LABEL_150;
                          }
                        }
                        else
                        {
                          iNext = v18->iNext;
                          if ( iNext )
                          {
                            v18 = &igi2_frame.ptFirstSphere[iNext];
                            igi2_frame.v168 = v18->tSphere.vRadius;
                            igi2_frame.ptSphere = v18;
                            v53 = v18->tSphere.tPos.vX - igi2_frame.tStartPos;
                            igi2_frame.aptSphereStack[v51] = v18;
                            igi2_frame.bColorb = v18->tSphere.tPos.vZ - igi2_frame.tStartPos_8;
                            igi2_frame.v138 = v18->tSphere.tPos.vY - igi2_frame.tStartPos_4;
                            v54 = igi2_frame.bColorb * igi2_frame.tDelta_8 + igi2_frame.v138 * igi2_frame.tDelta_4 + v53 * igi2_frame.tDelta;
                            if ( igi2_frame.v168 * igi2_frame.v168 >= v53 * v53
                                              + igi2_frame.v138 * igi2_frame.v138
                                              + igi2_frame.bColorb * igi2_frame.bColorb
                                              - v54 * v54 * igi2_frame.v1DivSquaredDistance
                              && v18->tSphere.vRadius + v18->tSphere.tPos.vX >= igi2_frame.tMin
                              && v18->tSphere.vRadius + v18->tSphere.tPos.vY >= igi2_frame.tMin_4
                              && v18->tSphere.vRadius + v18->tSphere.tPos.vZ >= igi2_frame.tMin_8
                              && v18->tSphere.tPos.vX - v18->tSphere.vRadius <= igi2_frame.tMax
                              && v18->tSphere.tPos.vY - v18->tSphere.vRadius <= igi2_frame.tMax_4
                              && v18->tSphere.tPos.vZ - v18->tSphere.vRadius <= igi2_frame.tMax_8 )
                            {
                              goto LABEL_82;
                            }
                          }
                          else
                          {
                            igi2_frame.nLevel = --v51;
                            if ( v51 < 0 )
                            {
                              if ( igi2_frame.isHitCurrentObject )
                              {
                                if ( ptQTask[6].ptPrev != (struct QTask_s *)1065353216
                                  || ptQTask[6].tQTaskChildren.ptHead != (struct QTask_s *)1065353216
                                  || ptQTask[6].tQTaskChildren.ptMiddle != (struct QTask_s *)1065353216 )
                                {
                                  igi2_frame.tTempHitPos_8 = igi2_frame.tHitPos_8a * *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
                                  igi2_frame.tTempStartPos = igi2_frame.tStartPos * *(float *)&ptQTask[6].ptPrev;
                                  igi2_frame.tTempStartPos_8 = igi2_frame.tStartPos_8 * *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
                                  v83 = igi2_frame.tStartPos_4 * *(float *)&ptQTask[6].tQTaskChildren.ptHead
                                      - igi2_frame.tHitPos_4a * *(float *)&ptQTask[6].tQTaskChildren.ptHead;
                                  v84 = igi2_frame.tTempStartPos - igi2_frame.tHitPosa * *(float *)&ptQTask[6].ptPrev;
                                  igi2_frame.vClosest = sqrt(
                                               (igi2_frame.tTempStartPos_8 - igi2_frame.tTempHitPos_8) * (igi2_frame.tTempStartPos_8 - igi2_frame.tTempHitPos_8)
                                             + v84 * v84
                                             + v83 * v83);
                                }
                                if ( !*(_DWORD *)(v5 + 92) || igi2_frame.vClosest < *(double *)(v5 + 96) )
                                {
                                  igi2_frame.ptVertex1 = &igi2_frame.ptVertexPos[igi2_frame.ptHitFace->aiVertex[1]].tPos;
                                  v85 = &igi2_frame.ptVertexPos[igi2_frame.ptHitFace->aiVertex[0]].tPos.vX;
                                  v86 = &igi2_frame.ptVertexPos[igi2_frame.ptHitFace->aiVertex[2]].tPos.vX;
                                  v87 = (int)&igi2_frame.ptCollMesh->ptMaterial[igi2_frame.ptHitFace->iMaterial];
                                  v88 = *(_WORD *)(v87 + 12);
                                  if ( v88 == 0xFFFF )
                                  {
                                    igi2_frame.iFacea = ptQTask[2].ptParent[2].tQTaskChildren.ptMiddle;
                                  }
                                  else
                                  {
                                    igi2_frame.iFacea = *(&ptQTask[2].ptParent[2].tQTaskChildren.ptHead + v88);
                                    v86 = &igi2_frame.ptVertexPos[igi2_frame.ptHitFace->aiVertex[2]].tPos.vX;
                                  }
                                  v89 = *v86 - *v85;
                                  v90 = v86[1] - v85[1];
                                  v91 = v86[2] - v85[2];
                                  igi2_frame.v213 = igi2_frame.ptVertex1->vX - *v85;
                                  igi2_frame.v214 = igi2_frame.ptVertex1->vY - v85[1];
                                  v92 = igi2_frame.ptVertex1->vZ - v85[2];
                                  v93 = (float *)(v5 + 44);
                                  igi2_frame.v216 = v92 * v90 - igi2_frame.v214 * v91;
                                  *(float *)(v5 + 44) = igi2_frame.v216;
                                  igi2_frame.v217 = -(v92 * v89 - igi2_frame.v213 * v91);
                                  *(float *)(v5 + 48) = igi2_frame.v217;
                                  igi2_frame.v218 = igi2_frame.v214 * v89 - igi2_frame.v213 * v90;
                                  *(float *)(v5 + 52) = igi2_frame.v218;
                                  if ( *(float *)(v5 + 44) != 0.0
                                    || *(float *)(v5 + 48) != 0.0
                                    || *(float *)(v5 + 52) != 0.0 )
                                  {
                                    v94 = 1.0
                                        / sqrt(
                                            *v93 * *v93
                                          + *(float *)(v5 + 48) * *(float *)(v5 + 48)
                                          + *(float *)(v5 + 52) * *(float *)(v5 + 52));
                                    *v93 = *v93 * v94;
                                    *(float *)(v5 + 48) = *(float *)(v5 + 48) * v94;
                                    *(float *)(v5 + 52) = *(float *)(v5 + 52) * v94;
                                  }
                                  igi2_frame.Real32x3_Rotate_tTemp = *(float *)&ptQTask[3].tQTaskChildren.ptMiddle
                                                        * *(float *)(v5 + 52)
                                                        + *(float *)(v5 + 48)
                                                        * *(float *)&ptQTask[3].tQTaskChildren.ptHead
                                                        + *(float *)&ptQTask[3].ptPrev * *v93;
                                  igi2_frame.Real32x3_Rotate_tTemp_4 = *(float *)&ptQTask[3].tQTaskRefList.ptHead
                                                          * *(float *)(v5 + 48)
                                                          + *(float *)&ptQTask[3].tQTaskChildren.ptTail * *v93
                                                          + *(float *)(v5 + 52)
                                                          * *(float *)&ptQTask[3].tQTaskRefList.ptMiddle;
                                  v95 = *(float *)&ptQTask[3].eQTaskType * *(float *)(v5 + 52)
                                      + *(float *)(v5 + 48) * *(float *)&ptQTask[3].ptParent;
                                  v96 = *(float *)&ptQTask[3].tQTaskRefList.ptTail * *v93;
                                  *(float *)(v5 + 56) = igi2_frame.Real32x3_Rotate_tTemp;
                                  *(float *)(v5 + 60) = igi2_frame.Real32x3_Rotate_tTemp_4;
                                  igi2_frame.Real32x3_Rotate_tTemp_8 = v95 + v96;
                                  *(float *)(v5 + 64) = igi2_frame.Real32x3_Rotate_tTemp_8;
                                  *(float *)(v5 + 32) = igi2_frame.tHitPosa;
                                  *(float *)(v5 + 36) = igi2_frame.tHitPos_4a;
                                  *(float *)(v5 + 40) = igi2_frame.tHitPos_8a;
                                  v97 = igi2_frame.tHitPosa * *(float *)&ptQTask[6].ptPrev;
                                  v98 = igi2_frame.tHitPos_4a * *(float *)&ptQTask[6].tQTaskChildren.ptHead;
                                  v99 = igi2_frame.tHitPos_8a * *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
                                  igi2_frame.v222 = v99 * *(float *)&ptQTask[3].tQTaskChildren.ptMiddle
                                       + v97 * *(float *)&ptQTask[3].ptPrev
                                       + v98 * *(float *)&ptQTask[3].tQTaskChildren.ptHead;
                                  igi2_frame.v223 = v99 * *(float *)&ptQTask[3].tQTaskRefList.ptMiddle
                                       + v97 * *(float *)&ptQTask[3].tQTaskChildren.ptTail
                                       + v98 * *(float *)&ptQTask[3].tQTaskRefList.ptHead;
                                  v100 = v99 * *(float *)&ptQTask[3].eQTaskType
                                       + v97 * *(float *)&ptQTask[3].tQTaskRefList.ptTail
                                       + v98 * *(float *)&ptQTask[3].ptParent;
                                  *(double *)(v5 + 8) = igi2_frame.v222 + *(double *)&ptQTask[1].ptNext;
                                  *(double *)(v5 + 16) = igi2_frame.v223 + *(double *)&ptQTask[1].tQTaskChildren.ptHead;
                                  v101 = v100 + *(double *)&ptQTask[1].tQTaskChildren.ptTail;
                                  *(_DWORD *)v5 = ptQTask;
                                  *(double *)(v5 + 24) = v101;
                                  *(_DWORD *)(v5 + 92) = 1;
                                  *(_DWORD *)(v5 + 80) = igi2_frame.isHitFrontFace != 0 ? igi2_frame.iFacea : nullptr;
                                  *(_DWORD *)(v5 + 96) = LODWORD(igi2_frame.vClosest);
                                  *(_DWORD *)(v5 + 84) = igi2_frame.isHitFrontFace != 0 ? nullptr : igi2_frame.iFacea;
                                  *(_DWORD *)(v5 + 88) = igi2_frame.isDoubleFace;
                                  *(_DWORD *)(v5 + 100) = HIDWORD(igi2_frame.vClosest);
                                  *(_DWORD *)(v5 + 72) = igi2_frame.ptHitFace - igi2_frame.ptCollMesh->ptFace;
                                  *(_WORD *)(v5 + 76) = *(_WORD *)(v87 + 4);
                                  *(float *)(v5 + 104) = igi2_frame.tHitUV;
                                  *(float *)(v5 + 108) = igi2_frame.tHitUV_4;
                                  if ( igi2_frame.ptMesh->eRenderMeshType == MESH3D_RENDERMESHTYPE_DIRECT3D_BUILDING
                                    && igi2_frame.iHitLightmap != 0xFFFF
                                    && (v102 = ptQTask[7].tQTaskRefList.ptHead) != nullptr
                                    && (igi2_frame.bColora = (unsigned int)v102->ptNext) != 0 )
                                  {
                                    v103 = &igi2_frame.ptVertexPos[igi2_frame.ptHitFace->aiVertex[0]].u.tLightmapUV.vX;
                                    igi2_frame.tUVEdge1 = igi2_frame.ptVertexPos[igi2_frame.ptHitFace->aiVertex[1]].u.tLightmapUV.vX - *v103;
                                    igi2_frame.tUVEdge1_4 = igi2_frame.ptVertexPos[igi2_frame.ptHitFace->aiVertex[1]].u.tLightmapUV.vY
                                               - igi2_frame.ptVertexPos[igi2_frame.ptHitFace->aiVertex[0]].u.tLightmapUV.vY;
                                    igi2_frame.tUVEdge0 = (igi2_frame.ptVertexPos[igi2_frame.ptHitFace->aiVertex[2]].u.tLightmapUV.vX - *v103) * igi2_frame.tHitUV;
                                    igi2_frame.tUVEdge1_4a = igi2_frame.tUVEdge1_4 * igi2_frame.tHitUV_4;
                                    igi2_frame.tUV_4 = igi2_frame.tUVEdge1_4a
                                          + (igi2_frame.ptVertexPos[igi2_frame.ptHitFace->aiVertex[2]].u.tLightmapUV.vY
                                           - igi2_frame.ptVertexPos[igi2_frame.ptHitFace->aiVertex[0]].u.tLightmapUV.vY)
                                          * igi2_frame.tHitUV;
                                    igi2_frame.tUV = igi2_frame.tUVEdge1 * igi2_frame.tHitUV_4 + igi2_frame.tUVEdge0 + *v103;
                                    igi2_frame.tUV_4a = igi2_frame.tUV_4 + igi2_frame.ptVertexPos[igi2_frame.ptHitFace->aiVertex[0]].u.tLightmapUV.vY;
                                    Texel = Lightmap_ReadTexel(
                                              (struct Mesh3D_Lightmap_t *)(52 * igi2_frame.iHitLightmap + igi2_frame.bColora + 60),
                                              igi2_frame.tUV,
                                              igi2_frame.tUV_4a);
                                    v105 = (double)((unsigned __int8)Texel + BYTE1(Texel) + (unsigned int)BYTE2(Texel))
                                         * 0.0026143791619688272;
                                  }
                                  else
                                  {
                                    igi2_frame.tLight = Mesh3D_atAmbientColor[1].vX;
                                    igi2_frame.tLight_4 = Mesh3D_atAmbientColor[1].vY;
                                    if ( SkyDome_ptDirlight
                                      && (v106 = SkyDome_ptDirlight->tDir.vZ * *(float *)(v5 + 64)
                                               + SkyDome_ptDirlight->tDir.vY * *(float *)(v5 + 60)
                                               + *(float *)(v5 + 56) * SkyDome_ptDirlight->tDir.vX,
                                          v106 > 0.0) )
                                    {
                                      igi2_frame.tLight = v106 * SkyDome_ptDirlight->tFrontColor.vX + Mesh3D_atAmbientColor[1].vX;
                                      igi2_frame.tLight_4 = v106 * SkyDome_ptDirlight->tFrontColor.vY + Mesh3D_atAmbientColor[1].vY;
                                      vZ = v106 * SkyDome_ptDirlight->tFrontColor.vZ + Mesh3D_atAmbientColor[1].vZ;
                                    }
                                    else
                                    {
                                      vZ = Mesh3D_atAmbientColor[1].vZ;
                                    }
                                    v105 = (vZ + igi2_frame.tLight_4 + igi2_frame.tLight) * 0.3333333432674408;
                                  }
                                  *(float *)(v5 + 112) = v105;
                                }
                              }
                              break;
                            }
                            v18 = igi2_frame.aptSphereStack[v51];
                            igi2_frame.ptSphere = v18;
                          }
                        }
                      }
                    }
LABEL_226:
                    ++igi2_frame.ptStartPos;
                    v5 += 120;
                    v108 = ++igi2_frame.iCheck < (int)(*((_DWORD *)pxContext + 2));
                    ++igi2_frame.ptEndPos;
                    if ( !v108 )
                      return;
                    v3 = &igi2_frame.ptStartPos->vX;
                  }
                }
              }
            }
          }
        }
      }
    }
  }
}

// source: e/3/rigiddyncubeobj.c:1243  [anchor-mhash]
void __cdecl RigidDynCubeObj_LineOfSightHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct QTask_s *v70; };
    struct { float v71; };
    struct { float v72; };
    struct { float v73; };
    struct { float v74; };
    struct { float v75; };
    struct { float v76; };
    struct { float v77; };
    struct { char igi2_o8[4]; float vRadius; };
    struct { char igi2_o9[4]; float vRadiusa; };
    struct { char igi2_o10[8]; float tEdge0; };
    struct { char igi2_o11[12]; float tEdge0_4; };
    struct { char igi2_o12[16]; float tEdge0_8; };
    struct { char igi2_o13[20]; struct real64x3_t *ptEndPos; };
    struct { char igi2_o14[20]; float ptEndPosa; };
    struct { char igi2_o15[20]; float ptEndPosb; };
    struct { char igi2_o16[20]; float ptEndPosc; };
    struct { char igi2_o17[27]; char isFirstIteration; };
    struct { char igi2_o18[28]; float tEndPos; };
    struct { char igi2_o19[32]; float tEndPos_4; };
    struct { char igi2_o20[32]; float tEndPos_4a; };
    struct { char igi2_o21[40]; float tStartPos; };
    struct { char igi2_o22[44]; float tStartPos_4; };
    struct { char igi2_o23[48]; float tStartPos_8; };
    struct { char igi2_o24[52]; int nLevel; };
    struct { char igi2_o25[56]; float v95; };
    struct { char igi2_o26[56]; float v96; };
    struct { char igi2_o27[60]; float Real32x3_RotateInverse_tTemp; };
    struct { char igi2_o28[60]; float Real32x3_RotateInverse_tTempa; };
    struct { char igi2_o29[60]; float Real32x3_RotateInverse_tTempb; };
    struct { char igi2_o30[64]; float Real32x3_RotateInverse_tTemp_4; };
    struct { char igi2_o31[64]; float Real32x3_RotateInverse_tTemp_4a; };
    struct { char igi2_o32[64]; float Real32x3_RotateInverse_tTemp_4b; };
    struct { char igi2_o33[68]; float Real32x3_RotateInverse_tTemp_8; };
    struct { char igi2_o34[68]; float Real32x3_RotateInverse_tTemp_8a; };
    struct { char igi2_o35[68]; float Real32x3_RotateInverse_tTemp_8b; };
    struct { char igi2_o36[72]; float tMax; };
    struct { char igi2_o37[76]; float tMax_4; };
    struct { char igi2_o38[80]; float tMax_8; };
    struct { char igi2_o39[84]; float tMin; };
    struct { char igi2_o40[88]; float tMin_4; };
    struct { char igi2_o41[92]; float tMin_8; };
    struct { char igi2_o42[96]; float v112; };
    struct { char igi2_o43[96]; float v113; };
    struct { char igi2_o44[100]; float v114; };
    struct { char igi2_o45[100]; float v115; };
    struct { char igi2_o46[104]; int iFace; };
    struct { char igi2_o47[104]; float iFacea; };
    struct { char igi2_o48[108]; float tDelta; };
    struct { char igi2_o49[112]; float tDelta_4; };
    struct { char igi2_o50[116]; float tDelta_8; };
    struct { char igi2_o51[120]; float tEdge1; };
    struct { char igi2_o52[124]; float tEdge1_4; };
    struct { char igi2_o53[128]; float tEdge1_8; };
    struct { char igi2_o54[132]; struct MultiMesh_Mesh_t *ptCollMesh; };
    struct { char igi2_o55[136]; struct MultiMesh_Sphere_t *ptFirstSphere; };
    struct { char igi2_o56[140]; float tPos; };
    struct { char igi2_o57[144]; float tPos_4; };
    struct { char igi2_o58[148]; float tPos_8; };
    struct { char igi2_o59[152]; float tCurrentDelta; };
    struct { char igi2_o60[156]; float tCurrentDelta_4; };
    struct { char igi2_o61[160]; float tCurrentDelta_8; };
    struct { char igi2_o62[164]; struct MultiMesh_Vertex_t *ptVertexPos; };
    struct { char igi2_o63[168]; float tAbsNormal; };
    struct { char igi2_o64[180]; struct MultiMesh_Sphere_t *aptSphereStack[100]; };
    char igi2_extent[580];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  double *v2; // ebp
  int v3; // eax
  struct QTask_s *ptHead; // ecx
  int v5; // eax
  struct MultiMesh_Mesh_t *v6; // eax
  __int16 v7; // ax
  void (__cdecl *pfHandler)(struct QTask_s *, _DWORD); // eax
  double v9; // st7
  bool v10; // c0
  bool v11; // c3
  struct MultiMesh_Sphere_t *ptSphere; // edx
  int v13; // ebx
  double v14; // st7
  struct QTask_s *ptPrev; // ecx
  double v16; // st7
  double v17; // st7
  double v18; // st7
  double v19; // st7
  double v20; // st7
  double v21; // st7
  double v22; // st7
  double v23; // st7
  double v24; // st6
  double v25; // st5
  double v26; // st7
  double v27; // st6
  double v28; // st5
  double v29; // st5
  double v30; // st4
  double v31; // st3
  double v32; // st7
  double v33; // st7
  double v34; // st6
  double v35; // st5
  double v36; // st7
  unsigned __int16 iNext; // dx
  double vX; // st6
  double v39; // st6
  unsigned __int16 iChild; // ax
  double v41; // st6
  double v42; // st6
  unsigned __int16 nFace; // cx
  int v44; // eax
  unsigned __int16 *aiVertex; // edi
  float *p_vX; // esi
  float *v47; // ebp
  float *v48; // ebx
  int v49; // ecx
  double v50; // st6
  double v51; // st6
  double v52; // st6
  double v53; // st6
  double v54; // st6
  double v55; // st5
  double v56; // st6
  double v57; // st6
  double v58; // st5
  double v59; // st4
  double v60; // st5
  double v61; // st6
  double v62; // st5
  double v63; // st4
  double v64; // st6
  double v65; // st5
  double v66; // st4
  double v67; // st5
  unsigned __int16 v68; // cx
  float *v69; // ecx

  v2 = *(double **)pxContext;
  igi2_frame.ptEndPos = *((struct real64x3_t **)pxContext + 1);
  v3 = *(_DWORD *)&ptQTask[2].eQTaskType;
  if ( !v3 )
    return;
  ptHead = ptQTask[7].tQTaskChildren.ptHead;
  if ( ptHead == (struct QTask_s *)-1 )
    return;
  v5 = *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(v3 + 4 * (_DWORD)ptHead) + 12) + 12);
  if ( *(_DWORD *)(v5 + 40) )
    return;
  v6 = *(struct MultiMesh_Mesh_t **)(v5 + 44);
  igi2_frame.ptCollMesh = v6;
  if ( !v6 )
    return;
  if ( !v6->nNumFaces )
    return;
  igi2_frame.ptVertexPos = v6->ptVertex;
  if ( *((_BYTE *)pxContext + 20) )
  {
    if ( *((float *)pxContext + 8) == 0.0 )
      return;
  }
  v7 = *((_WORD *)pxContext + 4);
  if ( v7 != 512 )
  {
    pfHandler = (void (__cdecl *)(struct QTask_s *, _DWORD))QTask_aatQTaskFinalEvent[v7][ptQTask->eQTaskType].pfHandler;
    if ( pfHandler )
    {
      pfHandler(ptQTask, *((_DWORD *)pxContext + 3));
      if ( !**((_BYTE **)pxContext + 3) )
        return;
    }
  }
  v9 = *(float *)&ptQTask[6].tQTaskChildren.ptHead;
  v10 = v9 < *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
  v11 = v9 == *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
  ptSphere = igi2_frame.ptCollMesh->ptSphere;
  v13 = 0;
  igi2_frame.isFirstIteration = 1;
  igi2_frame.nLevel = 0;
  igi2_frame.ptFirstSphere = ptSphere;
  igi2_frame.aptSphereStack[0] = ptSphere;
  if ( v10 || v11 )
    v14 = *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
  else
    v14 = *(float *)&ptQTask[6].tQTaskChildren.ptHead;
  if ( v14 < *(float *)&ptQTask[6].ptPrev )
  {
    ptPrev = ptQTask[6].ptPrev;
LABEL_19:
    igi2_frame.v70 = ptPrev;
    goto LABEL_20;
  }
  if ( *(float *)&ptQTask[6].tQTaskChildren.ptHead <= (double)*(float *)&ptQTask[6].tQTaskChildren.ptMiddle )
  {
    ptPrev = ptQTask[6].tQTaskChildren.ptMiddle;
    goto LABEL_19;
  }
  igi2_frame.v70 = ptQTask[6].tQTaskChildren.ptHead;
LABEL_20:
  v16 = Mesh3D_GetLODVirModelRadius(*(struct LODVirModel_s **)&ptQTask[2].eQTaskType) * *(float *)&igi2_frame.v70;
  igi2_frame.vRadius = v16;
  v17 = *(double *)&ptQTask[1].ptNext - v16;
  if ( v17 > *v2 && v17 > igi2_frame.ptEndPos->vX )
    return;
  v18 = igi2_frame.vRadius + *(double *)&ptQTask[1].ptNext;
  if ( v18 < *v2 && v18 < igi2_frame.ptEndPos->vX )
    return;
  v19 = *(double *)&ptQTask[1].tQTaskChildren.ptHead - igi2_frame.vRadius;
  if ( v19 > v2[1] && v19 > igi2_frame.ptEndPos->vY )
    return;
  v20 = igi2_frame.vRadius + *(double *)&ptQTask[1].tQTaskChildren.ptHead;
  if ( v20 < v2[1] && v20 < igi2_frame.ptEndPos->vY )
    return;
  v21 = *(double *)&ptQTask[1].tQTaskChildren.ptTail - igi2_frame.vRadius;
  if ( v21 > v2[2] && v21 > igi2_frame.ptEndPos->vZ )
    return;
  v22 = igi2_frame.vRadius + *(double *)&ptQTask[1].tQTaskChildren.ptTail;
  if ( v22 < v2[2] && v22 < igi2_frame.ptEndPos->vZ )
    return;
  v23 = *v2 - *(double *)&ptQTask[1].ptNext;
  v24 = v2[1] - *(double *)&ptQTask[1].tQTaskChildren.ptHead;
  v25 = v2[2] - *(double *)&ptQTask[1].tQTaskChildren.ptTail;
  igi2_frame.Real32x3_RotateInverse_tTemp = v25 * *(float *)&ptQTask[3].tQTaskRefList.ptTail
                               + v23 * *(float *)&ptQTask[3].ptPrev
                               + v24 * *(float *)&ptQTask[3].tQTaskChildren.ptTail;
  igi2_frame.Real32x3_RotateInverse_tTemp_4a = v25 * *(float *)&ptQTask[3].ptParent
                                  + v23 * *(float *)&ptQTask[3].tQTaskChildren.ptHead
                                  + v24 * *(float *)&ptQTask[3].tQTaskRefList.ptHead;
  igi2_frame.Real32x3_RotateInverse_tTemp_8 = v25 * *(float *)&ptQTask[3].eQTaskType
                                 + v23 * *(float *)&ptQTask[3].tQTaskChildren.ptMiddle
                                 + v24 * *(float *)&ptQTask[3].tQTaskRefList.ptMiddle;
  v26 = 1.0 / *(float *)&ptQTask[6].ptPrev;
  igi2_frame.tStartPos = igi2_frame.Real32x3_RotateInverse_tTemp * v26;
  v27 = 1.0 / *(float *)&ptQTask[6].tQTaskChildren.ptHead;
  igi2_frame.tStartPos_4 = igi2_frame.Real32x3_RotateInverse_tTemp_4a * v27;
  v28 = 1.0 / *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
  igi2_frame.v71 = v28;
  igi2_frame.tStartPos_8 = v28 * igi2_frame.Real32x3_RotateInverse_tTemp_8;
  v29 = igi2_frame.ptEndPos->vX - *(double *)&ptQTask[1].ptNext;
  v30 = igi2_frame.ptEndPos->vY - *(double *)&ptQTask[1].tQTaskChildren.ptHead;
  v31 = igi2_frame.ptEndPos->vZ - *(double *)&ptQTask[1].tQTaskChildren.ptTail;
  igi2_frame.Real32x3_RotateInverse_tTempa = v31 * *(float *)&ptQTask[3].tQTaskRefList.ptTail
                                + v29 * *(float *)&ptQTask[3].ptPrev
                                + v30 * *(float *)&ptQTask[3].tQTaskChildren.ptTail;
  igi2_frame.Real32x3_RotateInverse_tTemp_4 = v30 * *(float *)&ptQTask[3].tQTaskRefList.ptHead
                                 + v31 * *(float *)&ptQTask[3].ptParent
                                 + v29 * *(float *)&ptQTask[3].tQTaskChildren.ptHead;
  igi2_frame.Real32x3_RotateInverse_tTemp_8a = v31 * *(float *)&ptQTask[3].eQTaskType
                                  + v29 * *(float *)&ptQTask[3].tQTaskChildren.ptMiddle
                                  + v30 * *(float *)&ptQTask[3].tQTaskRefList.ptMiddle;
  igi2_frame.tEndPos = v26 * igi2_frame.Real32x3_RotateInverse_tTempa;
  igi2_frame.tEndPos_4 = v27 * igi2_frame.Real32x3_RotateInverse_tTemp_4;
  v32 = igi2_frame.v71 * igi2_frame.Real32x3_RotateInverse_tTemp_8a;
  if ( igi2_frame.tStartPos >= (double)igi2_frame.tEndPos )
    igi2_frame.tMin = igi2_frame.tEndPos;
  else
    igi2_frame.tMin = igi2_frame.tStartPos;
  if ( igi2_frame.tStartPos_4 >= (double)igi2_frame.tEndPos_4 )
    igi2_frame.tMin_4 = v27 * igi2_frame.Real32x3_RotateInverse_tTemp_4;
  else
    igi2_frame.tMin_4 = igi2_frame.tStartPos_4;
  if ( igi2_frame.tStartPos_8 >= v32 )
    igi2_frame.tMin_8 = v32;
  else
    igi2_frame.tMin_8 = igi2_frame.tStartPos_8;
  if ( igi2_frame.tStartPos <= (double)igi2_frame.tEndPos )
    igi2_frame.tMax = igi2_frame.tEndPos;
  else
    igi2_frame.tMax = igi2_frame.tStartPos;
  if ( igi2_frame.tStartPos_4 <= (double)igi2_frame.tEndPos_4 )
    igi2_frame.tMax_4 = v27 * igi2_frame.Real32x3_RotateInverse_tTemp_4;
  else
    igi2_frame.tMax_4 = igi2_frame.tStartPos_4;
  if ( igi2_frame.tStartPos_8 <= v32 )
    igi2_frame.tMax_8 = v32;
  else
    igi2_frame.tMax_8 = igi2_frame.tStartPos_8;
  v33 = v32 - igi2_frame.tStartPos_8;
  igi2_frame.v72 = v33;
  v34 = igi2_frame.tEndPos_4 - igi2_frame.tStartPos_4;
  igi2_frame.v114 = v34;
  v35 = igi2_frame.tEndPos - igi2_frame.tStartPos;
  igi2_frame.tDelta_4 = igi2_frame.v114;
  igi2_frame.iFacea = v35;
  igi2_frame.tDelta = igi2_frame.iFacea;
  igi2_frame.tDelta_8 = igi2_frame.v72;
  v36 = 1.0 / (v35 * v35 + v34 * v34 + v33 * v33);
  while ( 1 )
  {
LABEL_51:
    while ( igi2_frame.isFirstIteration )
    {
LABEL_60:
      iChild = ptSphere->iChild;
      igi2_frame.isFirstIteration = 0;
      if ( iChild )
      {
        do
        {
          ptSphere = &igi2_frame.ptFirstSphere[iChild];
          igi2_frame.v113 = ptSphere->tSphere.vRadius;
          ++v13;
          v41 = ptSphere->tSphere.tPos.vX - igi2_frame.tStartPos;
          igi2_frame.aptSphereStack[v13] = ptSphere;
          igi2_frame.Real32x3_RotateInverse_tTempb = v41;
          igi2_frame.Real32x3_RotateInverse_tTemp_4b = ptSphere->tSphere.tPos.vY - igi2_frame.tStartPos_4;
          v42 = ptSphere->tSphere.tPos.vZ - igi2_frame.tStartPos_8;
          igi2_frame.Real32x3_RotateInverse_tTemp_8b = v42;
          igi2_frame.v74 = igi2_frame.Real32x3_RotateInverse_tTemp_8b * igi2_frame.tDelta_8
              + igi2_frame.Real32x3_RotateInverse_tTemp_4b * igi2_frame.tDelta_4
              + igi2_frame.Real32x3_RotateInverse_tTempb * igi2_frame.tDelta;
          if ( igi2_frame.v113 * igi2_frame.v113 < igi2_frame.Real32x3_RotateInverse_tTempb * igi2_frame.Real32x3_RotateInverse_tTempb
                           + igi2_frame.Real32x3_RotateInverse_tTemp_4b * igi2_frame.Real32x3_RotateInverse_tTemp_4b
                           + v42 * v42
                           - igi2_frame.v74 * igi2_frame.v74 * v36 )
            break;
          if ( ptSphere->tSphere.vRadius + ptSphere->tSphere.tPos.vX < igi2_frame.tMin )
            break;
          if ( ptSphere->tSphere.vRadius + ptSphere->tSphere.tPos.vY < igi2_frame.tMin_4 )
            break;
          if ( ptSphere->tSphere.vRadius + ptSphere->tSphere.tPos.vZ < igi2_frame.tMin_8 )
            break;
          if ( ptSphere->tSphere.tPos.vX - ptSphere->tSphere.vRadius > igi2_frame.tMax )
            break;
          if ( ptSphere->tSphere.tPos.vY - ptSphere->tSphere.vRadius > igi2_frame.tMax_4 )
            break;
          if ( ptSphere->tSphere.tPos.vZ - ptSphere->tSphere.vRadius > igi2_frame.tMax_8 )
            break;
          iChild = ptSphere->iChild;
        }
        while ( iChild );
        igi2_frame.nLevel = v13;
      }
      nFace = ptSphere->nFace;
      if ( nFace )
      {
        v44 = ptSphere->iFace;
        igi2_frame.iFace = v44;
        aiVertex = igi2_frame.ptCollMesh->ptFace[v44].aiVertex;
        if ( v44 < v44 + nFace )
        {
          while ( 1 )
          {
            p_vX = &igi2_frame.ptVertexPos[*aiVertex].tPos.vX;
            v47 = &igi2_frame.ptVertexPos[aiVertex[1]].tPos.vX;
            v48 = &igi2_frame.ptVertexPos[aiVertex[2]].tPos.vX;
            v49 = (int)&igi2_frame.ptCollMesh->ptMaterial[aiVertex[3]];
            if ( *(_WORD *)(v49 + 4) != 0xFFFF || igi2_frame.tMin > (double)*p_vX && igi2_frame.tMin > (double)*v47 && igi2_frame.tMin > (double)*v48 )
              goto LABEL_151;
            if ( igi2_frame.tMin_4 > (double)p_vX[1] && igi2_frame.tMin_4 > (double)v47[1] && igi2_frame.tMin_4 > (double)v48[1] )
              goto LABEL_151;
            if ( igi2_frame.tMin_8 > (double)p_vX[2] && igi2_frame.tMin_8 > (double)v47[2] && igi2_frame.tMin_8 > (double)v48[2] )
              goto LABEL_151;
            if ( igi2_frame.tMax < (double)*p_vX && igi2_frame.tMax < (double)*v47 && igi2_frame.tMax < (double)*v48 )
              goto LABEL_151;
            if ( igi2_frame.tMax_4 < (double)p_vX[1] && igi2_frame.tMax_4 < (double)v47[1] && igi2_frame.tMax_4 < (double)v48[1] )
              goto LABEL_151;
            if ( igi2_frame.tMax_8 < (double)p_vX[2] && igi2_frame.tMax_8 < (double)v47[2] && igi2_frame.tMax_8 < (double)v48[2] )
              goto LABEL_151;
            igi2_frame.tEdge0 = *v48 - *p_vX;
            igi2_frame.tEdge0_4 = v48[1] - p_vX[1];
            igi2_frame.tEdge0_8 = v48[2] - p_vX[2];
            igi2_frame.tEdge1 = *v47 - *p_vX;
            igi2_frame.tEdge1_4 = v47[1] - p_vX[1];
            v50 = v47[2] - p_vX[2];
            igi2_frame.tEdge1_8 = v50;
            igi2_frame.v75 = v50 * igi2_frame.tEdge0_4 - igi2_frame.tEdge1_4 * igi2_frame.tEdge0_8;
            v51 = igi2_frame.tEdge1_8 * igi2_frame.tEdge0 - igi2_frame.tEdge1 * igi2_frame.tEdge0_8;
            igi2_frame.ptEndPosa = v51;
            igi2_frame.tEndPos_4a = -v51;
            igi2_frame.v95 = igi2_frame.tEdge1_4 * igi2_frame.tEdge0 - igi2_frame.tEdge1 * igi2_frame.tEdge0_4;
            v52 = igi2_frame.v95 * igi2_frame.tDelta_8 + igi2_frame.tEndPos_4a * igi2_frame.tDelta_4 + igi2_frame.v75 * igi2_frame.tDelta;
            igi2_frame.v115 = v52;
            if ( v52 == 0.0 )
              goto LABEL_151;
            v53 = ((*p_vX - igi2_frame.tStartPos) * igi2_frame.v75 + (p_vX[2] - igi2_frame.tStartPos_8) * igi2_frame.v95 + (p_vX[1] - igi2_frame.tStartPos_4) * igi2_frame.tEndPos_4a)
                / v52;
            igi2_frame.vRadiusa = v53;
            if ( v53 < 0.0 || igi2_frame.vRadiusa > 1.0 )
              goto LABEL_151;
            igi2_frame.tPos = igi2_frame.vRadiusa * igi2_frame.tDelta + igi2_frame.tStartPos;
            igi2_frame.tPos_4 = igi2_frame.vRadiusa * igi2_frame.tDelta_4 + igi2_frame.tStartPos_4;
            igi2_frame.tPos_8 = igi2_frame.vRadiusa * igi2_frame.tDelta_8 + igi2_frame.tStartPos_8;
            if ( igi2_frame.v75 >= 0.0 )
              igi2_frame.tAbsNormal = igi2_frame.v75;
            else
              igi2_frame.tAbsNormal = -igi2_frame.v75;
            v54 = igi2_frame.tEndPos_4a;
            if ( igi2_frame.tEndPos_4a < 0.0 )
              v54 = -v54;
            v55 = igi2_frame.v95;
            if ( igi2_frame.v95 < 0.0 )
              v55 = -v55;
            if ( igi2_frame.tAbsNormal > v54 && igi2_frame.tAbsNormal > v55 )
              break;
            if ( v54 > v55 )
            {
              v61 = igi2_frame.ptEndPosa;
              if ( igi2_frame.ptEndPosa == 0.0 )
                goto LABEL_151;
              igi2_frame.v96 = igi2_frame.tPos_8 - p_vX[2];
              igi2_frame.ptEndPosb = igi2_frame.tPos - *p_vX;
              v57 = (igi2_frame.v96 * igi2_frame.tEdge0 - igi2_frame.ptEndPosb * igi2_frame.tEdge0_8) / v61;
              if ( v57 < 0.0 || v57 > 1.0 )
                goto LABEL_151;
              v62 = igi2_frame.tEdge0;
              if ( igi2_frame.tEdge0 < 0.0 )
                v62 = -v62;
              v63 = igi2_frame.tEdge0_8;
              if ( igi2_frame.tEdge0_8 < 0.0 )
                v63 = -v63;
              if ( v62 > v63 )
              {
                v60 = (igi2_frame.ptEndPosb - igi2_frame.tEdge1 * v57) / igi2_frame.tEdge0;
                goto LABEL_126;
              }
LABEL_124:
              if ( igi2_frame.tEdge0_8 == 0.0 )
                goto LABEL_151;
              v60 = (igi2_frame.v96 - igi2_frame.tEdge1_8 * v57) / igi2_frame.tEdge0_8;
              goto LABEL_126;
            }
            if ( igi2_frame.v95 == 0.0 )
              goto LABEL_151;
            igi2_frame.v77 = igi2_frame.tPos_4 - p_vX[1];
            igi2_frame.ptEndPosc = igi2_frame.tPos - *p_vX;
            v64 = (igi2_frame.v77 * igi2_frame.tEdge0 - igi2_frame.ptEndPosc * igi2_frame.tEdge0_4) / igi2_frame.v95;
            if ( v64 < 0.0 || v64 > 1.0 )
              goto LABEL_151;
            v65 = igi2_frame.tEdge0;
            if ( igi2_frame.tEdge0 < 0.0 )
              v65 = -v65;
            v66 = igi2_frame.tEdge0_4;
            if ( igi2_frame.tEdge0_4 < 0.0 )
              v66 = -v66;
            if ( v65 <= v66 )
            {
              if ( igi2_frame.tEdge0_4 == 0.0 )
                goto LABEL_151;
              v67 = (igi2_frame.v77 - igi2_frame.tEdge1_4 * v64) / igi2_frame.tEdge0_4;
            }
            else
            {
              v67 = (igi2_frame.ptEndPosc - igi2_frame.tEdge1 * v64) / igi2_frame.tEdge0;
            }
            if ( v67 >= 0.0 && v67 + v64 <= 1.0 )
            {
LABEL_142:
              *((_BYTE *)pxContext + 20) = 1;
              v68 = *(_WORD *)(v49 + 12);
              if ( v68 == 0xFFFF )
                goto LABEL_149;
              v69 = *(float **)(*((_DWORD *)pxContext + 4) + 4 * v68 + 88);
              if ( igi2_frame.v115 < 0.0 )
                *((float *)pxContext + 8) = *v69 * *((float *)pxContext + 8);
              if ( !*((_DWORD *)pxContext + 6) || *((float *)pxContext + 7) > (double)igi2_frame.vRadiusa )
              {
                *((_DWORD *)pxContext + 6) = v69;
                *((float *)pxContext + 7) = igi2_frame.vRadiusa;
              }
              if ( *v69 == 0.0 )
              {
LABEL_149:
                *((_DWORD *)pxContext + 8) = 0;
                return;
              }
            }
LABEL_151:
            aiVertex += 6;
            if ( ++igi2_frame.iFace >= ptSphere->iFace + ptSphere->nFace )
            {
              v13 = igi2_frame.nLevel;
              goto LABEL_51;
            }
          }
          v56 = igi2_frame.v75;
          if ( igi2_frame.v75 == 0.0 )
            goto LABEL_151;
          igi2_frame.v96 = igi2_frame.tPos_8 - p_vX[2];
          igi2_frame.v76 = igi2_frame.tPos_4 - p_vX[1];
          v57 = (igi2_frame.v96 * igi2_frame.tEdge0_4 - igi2_frame.v76 * igi2_frame.tEdge0_8) / v56;
          if ( v57 < 0.0 || v57 > 1.0 )
            goto LABEL_151;
          v58 = igi2_frame.tEdge0_4;
          if ( igi2_frame.tEdge0_4 < 0.0 )
            v58 = -v58;
          v59 = igi2_frame.tEdge0_8;
          if ( igi2_frame.tEdge0_8 < 0.0 )
            v59 = -v59;
          if ( v58 > v59 )
          {
            v60 = (igi2_frame.v76 - igi2_frame.tEdge1_4 * v57) / igi2_frame.tEdge0_4;
LABEL_126:
            if ( v60 >= 0.0 && v60 + v57 <= 1.0 )
              goto LABEL_142;
            goto LABEL_151;
          }
          goto LABEL_124;
        }
      }
    }
    iNext = ptSphere->iNext;
    if ( !iNext )
      break;
    ptSphere = &igi2_frame.ptFirstSphere[iNext];
    igi2_frame.v112 = ptSphere->tSphere.vRadius;
    vX = ptSphere->tSphere.tPos.vX;
    igi2_frame.aptSphereStack[v13] = ptSphere;
    igi2_frame.tCurrentDelta = vX - igi2_frame.tStartPos;
    igi2_frame.tCurrentDelta_4 = ptSphere->tSphere.tPos.vY - igi2_frame.tStartPos_4;
    v39 = ptSphere->tSphere.tPos.vZ - igi2_frame.tStartPos_8;
    igi2_frame.tCurrentDelta_8 = v39;
    igi2_frame.v73 = igi2_frame.tCurrentDelta_8 * igi2_frame.tDelta_8 + igi2_frame.tCurrentDelta_4 * igi2_frame.tDelta_4 + igi2_frame.tCurrentDelta * igi2_frame.tDelta;
    if ( igi2_frame.v112 * igi2_frame.v112 >= igi2_frame.tCurrentDelta * igi2_frame.tCurrentDelta + igi2_frame.tCurrentDelta_4 * igi2_frame.tCurrentDelta_4 + v39 * v39 - igi2_frame.v73 * igi2_frame.v73 * v36
      && ptSphere->tSphere.vRadius + ptSphere->tSphere.tPos.vX >= igi2_frame.tMin
      && ptSphere->tSphere.vRadius + ptSphere->tSphere.tPos.vY >= igi2_frame.tMin_4
      && ptSphere->tSphere.vRadius + ptSphere->tSphere.tPos.vZ >= igi2_frame.tMin_8
      && ptSphere->tSphere.tPos.vX - ptSphere->tSphere.vRadius <= igi2_frame.tMax
      && ptSphere->tSphere.tPos.vY - ptSphere->tSphere.vRadius <= igi2_frame.tMax_4
      && ptSphere->tSphere.tPos.vZ - ptSphere->tSphere.vRadius <= igi2_frame.tMax_8 )
    {
      goto LABEL_60;
    }
  }
  igi2_frame.nLevel = --v13;
  if ( v13 >= 0 )
  {
    ptSphere = igi2_frame.aptSphereStack[v13];
    goto LABEL_51;
  }
}

// source: e/3/rigiddyncubeobj.c:1817  [size]
void __cdecl RigidDynCubeObj_GetMaterialHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ;
}

// source: e/3/rigiddyncubeobj.c:2310  [anchor-mhash]
void __cdecl RigidDynCubeObj_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct LODVirModel_s *LODVirModelExistsFn; // eax
  double v4; // st7
  bool v5; // c0
  bool v6; // c3
  double v7; // st7
  double v8; // st7
  int *v9; // eax
  int v10; // eax
  double v11; // st6
  float ptDynCubeObj; // [esp+0h] [ebp-18h]
  struct QTask_s *ptQTaska = *(struct QTask_s * *)&ptQTask; // [esp+1Ch] [ebp+4h] ARGSLOT

  ptQTask[7].tQTaskChildren.ptTail = nullptr;
  if ( pxContext )
  {
    LODVirModelExistsFn = MTP_GetLODVirModelExistsFn(*(char **)pxContext);
    ptQTaska = (struct QTask_s *)LODVirModelExistsFn;
    if ( !LODVirModelExistsFn )
    {
      LDebug_Error("VirModel \"%s\" not available", *(char **)pxContext);
      abort();
    }
    ModelObj_Init((struct ModelObj_s *)ptQTask, *((struct World_s **)pxContext + 1), LODVirModelExistsFn);
    ptQTask[7].tQTaskChildren.ptHead = nullptr;
    ptQTask[7].tQTaskChildren.ptMiddle = (struct QTask_s *)2;
    ptQTask[7].tQTaskRefList.ptHead = nullptr;
    ptQTask[7].tQTaskRefList.ptMiddle = nullptr;
    ptQTask[7].tQTaskRefList.ptTail = nullptr;
    ptQTask[7].ptParent = nullptr;
    *(_DWORD *)&ptQTask[7].eQTaskType = 0;
    v4 = *(float *)&ptQTask[6].tQTaskChildren.ptHead;
    v5 = v4 < *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
    v6 = v4 == *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
    ptQTask[2].ptParent = *((struct QTask_s **)pxContext + 1);
    if ( v5 || v6 )
      v7 = *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
    else
      v7 = *(float *)&ptQTask[6].tQTaskChildren.ptHead;
    if ( v7 >= *(float *)&ptQTask[6].ptPrev )
    {
      if ( *(float *)&ptQTask[6].tQTaskChildren.ptHead <= (double)*(float *)&ptQTask[6].tQTaskChildren.ptMiddle )
        v8 = *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
      else
        v8 = *(float *)&ptQTask[6].tQTaskChildren.ptHead;
    }
    else
    {
      v8 = *(float *)&ptQTask[6].ptPrev;
    }
    v9 = *(int **)&ptQTask[2].eQTaskType;
    if ( v9 && (v10 = *v9) != 0 )
      v11 = *(float *)(*(_DWORD *)(*(_DWORD *)(v10 + 12) + 12) + 120);
    else
      v11 = 1.0;
    ptDynCubeObj = v8 * v11;
    World_RegisterDynCubeObjFirstTimeRadius(
      *((struct World_s **)pxContext + 1),
      (struct DynCubeObj_s *)ptQTask,
      (struct real64x3_t *)((char *)pxContext + 8),
      ptDynCubeObj,
      (enum DynCubeTreeCategory_enum)ptQTask[7].tQTaskChildren.ptMiddle);
    qmemcpy(&ptQTask[3].ptPrev, (char *)pxContext + 44, sizeof(struct QTask_s));
    ModelObj_AttachToParent((struct ModelObj_s *)ptQTask, (struct MagicObjCreateContext_s *)pxContext);
    RigidDynCubeObj_SetLODVirModel((struct RigidDynCubeObj_t *)ptQTask, (struct LODVirModel_s *)ptQTaska);
  }
  else
  {
    ptQTask[2].tQTaskChildren.ptHead = nullptr;
  }
}

void __cdecl RigidDynCubeObj_DeleteHandler(struct ModelObj_s *a1)
{
  if ( a1->ptLODVirModel )
  {
    ModelObj_SetLODVirModel(a1, nullptr, false);
    a1[1].tDynCubeObj.tQObj.tQTask.tQTaskChildren.ptMiddle = nullptr;
    a1[1].tDynCubeObj.tQObj.tQTask.tQTaskChildren.ptTail = nullptr;
    a1[1].tDynCubeObj.tQObj.tQTask.tQTaskRefList.ptHead = nullptr;
    a1[1].tDynCubeObj.tQObj.tQTask.tQTaskRefList.ptMiddle = nullptr;
    a1[1].tDynCubeObj.tQObj.tQTask.tQTaskRefList.ptTail = nullptr;
  }
  if ( a1->tDynCubeObj.ptDynCubeObjTreeItem )
    World_RemoveDynCubeObj(a1->ptWorld, &a1->tDynCubeObj);
}

// source: e/3/rigiddyncubeobj.c:2407  [anchor-mhash]
void __cdecl RigidDynCubeObj_GetCameraTargetInfoHandler(struct QTask_s *ptQTask, void *pxContext)
{
  double v2; // st7
  double v3; // st7
  int *v4; // edx
  int v5; // edx
  double v6; // st6
  char *v7; // ebx

  qmemcpy(pxContext, &ptQTask[1], 0x18u);
  *((_DWORD *)pxContext + 6) = 0;
  *((_DWORD *)pxContext + 7) = 0;
  *((_DWORD *)pxContext + 8) = 0;
  qmemcpy((char *)pxContext + 36, &ptQTask[3].ptPrev, 0x28u);
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
  *((float *)pxContext + 19) = v3 * v6;
  v7 = *((char **)pxContext + 20);
  if ( v7 )
    strcpy(v7, "Rigid Object");
}

// source: e/3/rigiddyncubeobj.c:2445  [anchor-mhash]
void __cdecl RigidDynCubeObj_RegisterHandler(struct QTask_s *ptQTask, void *pxContext)
{
  double v2; // st7
  bool v3; // c0
  bool v4; // c3
  double v5; // st7
  double v6; // st7
  int *v7; // eax
  int v8; // eax
  double v9; // st6
  struct QTask_s *ptNext; // eax
  struct QTask_s *ptHead; // eax
  int v12; // ecx
  int v13; // eax
  struct QTask_s *v14; // edx
  void (__cdecl *pfHandler)(int, void *); // edx
  int v16; // eax
  struct QTask_s *v17; // ecx
  struct QTask_s *v18; // edx
  void (__cdecl *v19)(struct QTask_s *, void *); // edx
  int v20; // eax
  float ptDynCubeObj; // [esp+0h] [ebp-14h]

  if ( !ptQTask[2].tQTaskChildren.ptHead )
  {
    v2 = *(float *)&ptQTask[6].tQTaskChildren.ptHead;
    v3 = v2 < *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
    v4 = v2 == *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
    ptQTask[2].ptParent = *((struct QTask_s **)pxContext + 1);
    if ( v3 || v4 )
      v5 = *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
    else
      v5 = *(float *)&ptQTask[6].tQTaskChildren.ptHead;
    if ( v5 >= *(float *)&ptQTask[6].ptPrev )
    {
      if ( *(float *)&ptQTask[6].tQTaskChildren.ptHead <= (double)*(float *)&ptQTask[6].tQTaskChildren.ptMiddle )
        v6 = *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
      else
        v6 = *(float *)&ptQTask[6].tQTaskChildren.ptHead;
    }
    else
    {
      v6 = *(float *)&ptQTask[6].ptPrev;
    }
    v7 = *(int **)&ptQTask[2].eQTaskType;
    if ( v7 && (v8 = *v7) != 0 )
      v9 = *(float *)(*(_DWORD *)(*(_DWORD *)(v8 + 12) + 12) + 120);
    else
      v9 = 1.0;
    ptDynCubeObj = v6 * v9;
    World_RegisterDynCubeObjFirstTimeRadius(
      *((struct World_s **)pxContext + 1),
      (struct DynCubeObj_s *)ptQTask,
      (struct real64x3_t *)&ptQTask[1],
      ptDynCubeObj,
      *((enum DynCubeTreeCategory_enum *)pxContext + 2));
    ptNext = ptQTask[3].ptNext;
    if ( ptNext && (ptHead = ptNext->tQTaskChildren.ptHead, ptHead->ptNext) && (v12 = (int)ptHead) != 0 )
    {
      v13 = QTask_nProtectedQTaskStackOffset;
      do
      {
        if ( *(_DWORD *)v12 )
          v14 = **(_DWORD **)v12 != 0 ? *(struct QTask_s **)v12 : nullptr;
        else
          v14 = nullptr;
        QTask_atProtectedQTaskStack[v13].ptQTask = v14;
        pfHandler = (void (__cdecl *)(int, void *))QTask_aatQTaskFinalEvent[DynCubeObj_eDynCubeObjRegisterQTaskEvent][*(unsigned __int16 *)(v12 + 36)].pfHandler;
        v16 = v13 + 1;
        QTask_nProtectedQTaskStackOffset = v16;
        if ( pfHandler )
        {
          pfHandler(v12, pxContext);
          v16 = QTask_nProtectedQTaskStackOffset;
        }
        v12 = dword_849C7DC[v16];
        v13 = v16 - 1;
        QTask_nProtectedQTaskStackOffset = v13;
      }
      while ( v12 );
    }
    else
    {
      v13 = QTask_nProtectedQTaskStackOffset;
    }
    v17 = ptQTask->tQTaskChildren.ptHead;
    if ( v17->ptNext && v17 )
    {
      do
      {
        if ( v17->ptNext )
          v18 = v17->ptNext->ptNext != nullptr ? v17->ptNext : nullptr;
        else
          v18 = nullptr;
        QTask_atProtectedQTaskStack[v13].ptQTask = v18;
        v19 = (void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[DynCubeObj_eDynCubeObjRegisterQTaskEvent][v17->eQTaskType].pfHandler;
        v20 = v13 + 1;
        QTask_nProtectedQTaskStackOffset = v20;
        if ( v19 )
        {
          v19(v17, pxContext);
          v20 = QTask_nProtectedQTaskStackOffset;
        }
        v17 = (struct QTask_s *)dword_849C7DC[v20];
        v13 = v20 - 1;
        QTask_nProtectedQTaskStackOffset = v13;
      }
      while ( v17 );
    }
  }
}

// source: e/3/rigiddyncubeobj.c:2486  [size]
void __cdecl RigidDynCubeObj_RemoveHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *ptHead; // ecx
  int v3; // eax
  struct QTask_s *v4; // edx
  void (__cdecl *pfHandler)(struct QTask_s *, void *); // edx
  int v6; // eax
  struct QTask_s *ptNext; // ecx
  int v8; // ecx
  struct QTask_s *v9; // edx
  void (__cdecl *v10)(int, void *); // edx
  int v11; // eax

  if ( ptQTask[2].tQTaskChildren.ptHead )
  {
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
        pfHandler = (void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[DynCubeObj_eDynCubeObjRemoveQTaskEvent][ptHead->eQTaskType].pfHandler;
        v6 = v3 + 1;
        QTask_nProtectedQTaskStackOffset = v6;
        if ( pfHandler )
        {
          pfHandler(ptHead, pxContext);
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
    ptNext = ptQTask[3].ptNext;
    if ( ptNext )
    {
      v8 = (int)ptNext->tQTaskChildren.ptHead;
      if ( *(_DWORD *)v8 )
      {
        for ( ; v8; QTask_nProtectedQTaskStackOffset = v3 )
        {
          if ( *(_DWORD *)v8 )
            v9 = **(_DWORD **)v8 != 0 ? *(struct QTask_s **)v8 : nullptr;
          else
            v9 = nullptr;
          QTask_atProtectedQTaskStack[v3].ptQTask = v9;
          v10 = (void (__cdecl *)(int, void *))QTask_aatQTaskFinalEvent[DynCubeObj_eDynCubeObjRemoveQTaskEvent][*(unsigned __int16 *)(v8 + 36)].pfHandler;
          v11 = v3 + 1;
          QTask_nProtectedQTaskStackOffset = v11;
          if ( v10 )
          {
            v10(v8, pxContext);
            v11 = QTask_nProtectedQTaskStackOffset;
          }
          v8 = dword_849C7DC[v11];
          v3 = v11 - 1;
        }
      }
    }
    World_RemoveDynCubeObj(*(struct World_s **)pxContext, (struct DynCubeObj_s *)ptQTask);
  }
}

// source: e/3/rigiddyncubeobj.c:2520  [anchor-mhash]
void __cdecl RigidDynCubeObj_SetPositionHandler(struct QTask_s *ptQTask, void *pxContext)
{
  double v2; // st7
  double v3; // st7
  int *v4; // eax
  int v5; // eax
  double v6; // st6
  __int16 v7; // cx
  float ptDynCubeObj; // [esp+0h] [ebp-10h]

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
  World_MoveDynCubeObjRadius(
    World_ptActiveWorld,
    (struct DynCubeObj_s *)ptQTask,
    (struct real64x3_t *)pxContext,
    ptDynCubeObj);
  qmemcpy(&ptQTask[3].ptPrev, (char *)pxContext + 24, sizeof(struct QTask_s));
  v7 = Attach_eAttachEvent;
  ptQTask[5].tQTaskChildren.ptTail = (struct QTask_s *)-1;
  ptQTask[5].tQTaskRefList.ptHead = nullptr;
  QTask_TriggerQTaskEventParent(ptQTask, v7, &ptQTask[5].tQTaskChildren.ptTail);
  ModelObj_CalcRelativePosAndOrientation((struct ModelObj_s *)ptQTask);
  RigidDynCubeObj_UpdateAttachments((struct RigidDynCubeObj_t *)ptQTask);
}

// source: e/3/rigiddyncubeobj.c:2555  [size]
struct real64x3_t *__cdecl RigidDynCubeObj_GetCenterPos(
        struct RigidDynCubeObj_t *ptRigidDynCubeObj)
{
  return &ptRigidDynCubeObj->tModelObj.tDynCubeObj.tQObj.tPos;
}

// source: e/3/rigiddyncubeobj.c:2617  [anchor-strings]
void __cdecl RigidDynCubeObj_GenericOpen()
{
  __int16 v0; // ax
  unsigned __int16 v1; // si
  unsigned int SystemGroup; // eax

  RigidDynCubeObj_eQTaskType = QTask_NewQTaskType("RigidDynCubeObj", 320, ModelObj_eQTaskType, 0, 0);
  v0 = QTask_NewQTaskEventFn(0, "RenderStartEvent");
  v1 = RigidDynCubeObj_eQTaskType;
  RigidDynCubeObj_eRenderStartEvent = v0;
  QTask_LinkQTaskEventHandlerFn(RigidDynCubeObj_eQTaskType, 5, RigidDynCubeObj_EnterHandler);
  QTask_LinkQTaskEventHandlerFn(v1, 8, RigidDynCubeObj_GetCameraTargetInfoHandler);
  QTask_LinkQTaskEventHandlerFn(v1, 11, RigidDynCubeObj_TraceLinesHandler);
  QTask_LinkQTaskEventHandlerFn(v1, 12, (void (__cdecl *)(struct QTask_s *, void *))RigidDynCubeObj_GetMaterialHandler);
  QTask_LinkQTaskEventHandlerFn(v1, 10, RigidDynCubeObj_TraceLinesHandler);
  QTask_LinkQTaskEventHandlerFn(v1, 9, RigidDynCubeObj_LineOfSightHandler);
  QTask_LinkQTaskEventHandlerFn(v1, 13, RigidDynCubeObj_CollisionEvalHandler);
  QTask_LinkQTaskEventHandlerFn(v1, 0, RigidDynCubeObj_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 2, (void (__cdecl *)(struct QTask_s *))RigidDynCubeObj_DeleteHandler);
  QTask_LinkQTaskEventHandlerFn(v1, DynCubeObj_eDynCubeObjRegisterQTaskEvent, RigidDynCubeObj_RegisterHandler);
  QTask_LinkQTaskEventHandlerFn(v1, DynCubeObj_eDynCubeObjRemoveQTaskEvent, RigidDynCubeObj_RemoveHandler);
  QTask_LinkQTaskEventHandlerFn(v1, 7, RigidDynCubeObj_SetPositionHandler);
  QTask_LinkQTaskEventHandlerFn(
    v1,
    BspTreeDynCubeObj_eGenerationSizeEvent,
    RigidDynCubeObj_BspTreeGenerationSizeHandler);
  QTask_LinkQTaskEventHandlerFn(
    v1,
    BspTreeDynCubeObj_eGenerationListEvent,
    RigidDynCubeObj_BspTreeGenerationListHandler);
  SystemGroup = QTask_AllocateSystemGroup((unsigned int)&TerrainRender_atEdge[4623].iSplitVertex);
  QTask_SetQTaskTypeGroup(RigidDynCubeObj_eQTaskType, SystemGroup);
}

// source: e/3/rigiddyncubeobj.c:2659  [size]
void __cdecl RigidDynCubeObj_GenericClose()
{
  QTask_FreeGroup((unsigned int)&TerrainRender_atEdge[4623].iSplitVertex);
  QTask_DeleteQTaskType(RigidDynCubeObj_eQTaskType);
  RigidDynCubeObj_eQTaskType = 512;
  QTask_DeleteQTaskEvent(RigidDynCubeObj_eRenderStartEvent);
  RigidDynCubeObj_eRenderStartEvent = 512;
}

// source: e/3/rigiddyncubeobj.c:2682  [size]
__int16 __cdecl RigidDynCubeObj_GetRenderStartEvent()
{
  return RigidDynCubeObj_eRenderStartEvent;
}

// source: e/3/rigiddyncubeobj.c:2697  [size]
unsigned __int16 __cdecl RigidDynCubeObj_GetQTaskType()
{
  return RigidDynCubeObj_eQTaskType;
}

// source: e/3/rigiddyncubeobj.c:2712  [anchor-mhash]
struct LODVirModel_s *__cdecl RigidDynCubeObj_Init(
        struct World_s *ptWorld,
        struct RigidDynCubeObj_t *ptRigidDynCubeObj,
        struct LODVirModel_s *ptLODVirModel)
{
  struct Mesh3D_LightmapVirModel_t **v4; // edx

  ModelObj_Init(&ptRigidDynCubeObj->tModelObj, ptWorld, ptLODVirModel);
  ptRigidDynCubeObj->iCollisionLOD = 0;
  ptRigidDynCubeObj->iDynCubeTree = 2;
  v4 = &ptRigidDynCubeObj->aptLightmapVirModel[1];
  *v4 = nullptr;
  v4[1] = nullptr;
  v4[2] = nullptr;
  v4[3] = nullptr;
  v4[4] = nullptr;
  return nullptr;
}

// source: e/3/rigiddyncubeobj.c:2735  [anchor-callee]
struct LODVirModel_s *__cdecl RigidDynCubeObj_SetLODVirModel(
        struct RigidDynCubeObj_t *ptRigidDynCubeObj,
        struct LODVirModel_s *ptLODVirModel)
{
  struct Mesh3D_LightmapVirModel_t **v3; // esi

  if ( ptLODVirModel != ptRigidDynCubeObj->tModelObj.ptLODVirModel )
  {
    ModelObj_SetLODVirModel(&ptRigidDynCubeObj->tModelObj, ptLODVirModel, false);
    v3 = &ptRigidDynCubeObj->aptLightmapVirModel[1];
    *v3 = nullptr;
    v3[1] = nullptr;
    v3[2] = nullptr;
    v3[3] = nullptr;
    v3[4] = nullptr;
    return nullptr;
  }
  return ptLODVirModel;
}

// source: e/3/rigiddyncubeobj.c:2758  [anchor-callee]
unsigned int __cdecl RigidDynCubeObj_GetMagicVertexLocalPos(
        struct RigidDynCubeObj_t *ptRigidDynCubeObj,
        unsigned int iMagicVertex,
        struct real32x3_t *ptPos)
{
  struct LODVirModel_s *ptLODVirModel; // edx
  struct Mesh3D_Mesh_t *ptMesh; // edx

  ptLODVirModel = ptRigidDynCubeObj->tModelObj.ptLODVirModel;
  if ( ptLODVirModel )
  {
    ptMesh = ptLODVirModel->aptVirModel[0]->ptModel->ptMesh;
    if ( iMagicVertex < ptMesh->nMagicVertex && (iMagicVertex = (unsigned int)&ptMesh->ptMagicVertex[iMagicVertex]) != 0 )
    {
      ptPos->vX = *(float *)iMagicVertex;
      ptPos->vY = *(float *)(iMagicVertex + 4);
      iMagicVertex = *(_DWORD *)(iMagicVertex + 8);
      LODWORD(ptPos->vZ) = iMagicVertex;
    }
    else
    {
      ptPos->vX = 0.0;
      ptPos->vY = 0.0;
      ptPos->vZ = 0.0;
    }
    ptPos->vX = ptRigidDynCubeObj->tModelObj.tScale.vX * ptPos->vX;
    ptPos->vY = ptRigidDynCubeObj->tModelObj.tScale.vY * ptPos->vY;
    ptPos->vZ = ptRigidDynCubeObj->tModelObj.tScale.vZ * ptPos->vZ;
  }
  else
  {
    ptPos->vX = 0.0;
    ptPos->vY = 0.0;
    ptPos->vZ = 0.0;
  }
  return iMagicVertex;
}

// source: e/3/rigiddyncubeobj.c:2782  [anchor-callee]
unsigned int __cdecl RigidDynCubeObj_GetMagicVertexPos(
        struct RigidDynCubeObj_t *ptRigidDynCubeObj,
        unsigned int iMagicVertex,
        struct real64x3_t *ptPos)
{
  unsigned int result; // eax
  double v5; // st7
  double v6; // st6
  struct real32x3_t tLocalPos; // [esp+4h] [ebp-Ch] BYREF

  result = RigidDynCubeObj_GetMagicVertexLocalPos(ptRigidDynCubeObj, iMagicVertex, &tLocalPos);
  v5 = tLocalPos.vZ * ptRigidDynCubeObj->tModelObj.tOrientation.tX.vZ
     + tLocalPos.vY * ptRigidDynCubeObj->tModelObj.tOrientation.tX.vY
     + tLocalPos.vX * ptRigidDynCubeObj->tModelObj.tOrientation.tX.vX;
  v6 = tLocalPos.vZ * ptRigidDynCubeObj->tModelObj.tOrientation.tY.vZ
     + tLocalPos.vY * ptRigidDynCubeObj->tModelObj.tOrientation.tY.vY
     + tLocalPos.vX * ptRigidDynCubeObj->tModelObj.tOrientation.tY.vX;
  tLocalPos.vZ = tLocalPos.vZ * ptRigidDynCubeObj->tModelObj.tOrientation.tZ.vZ
               + tLocalPos.vY * ptRigidDynCubeObj->tModelObj.tOrientation.tZ.vY
               + tLocalPos.vX * ptRigidDynCubeObj->tModelObj.tOrientation.tZ.vX;
  ptPos->vX = v5 + ptRigidDynCubeObj->tModelObj.tDynCubeObj.tQObj.tPos.vX;
  ptPos->vY = v6 + ptRigidDynCubeObj->tModelObj.tDynCubeObj.tQObj.tPos.vY;
  ptPos->vZ = tLocalPos.vZ + ptRigidDynCubeObj->tModelObj.tDynCubeObj.tQObj.tPos.vZ;
  return result;
}

// source: e/3/rigiddyncubeobj.c:2803  [anchor-callee]
void __cdecl RigidDynCubeObj_UpdateAttachments(struct RigidDynCubeObj_t *ptRigidDynCubeObj)
{
  struct QTask_s *ptMagicObjContainer; // eax
  int ptHead; // edx
  int v3; // eax
  struct QTask_s *v4; // ecx
  int v5; // esi
  void (__cdecl *pfHandler)(int); // ecx
  int v7; // eax
  struct QTask_s *v8; // ecx
  struct QTask_s *v9; // edx
  int v10; // esi
  void (__cdecl *v11)(struct QTask_s *); // edx
  int v12; // eax

  ptMagicObjContainer = ptRigidDynCubeObj->tModelObj.ptMagicObjContainer;
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
  v8 = ptRigidDynCubeObj->tModelObj.tDynCubeObj.tQObj.tQTask.tQTaskChildren.ptHead;
  if ( v8->ptNext && v8 )
  {
    do
    {
      if ( v8->ptNext )
        v9 = v8->ptNext->ptNext != nullptr ? v8->ptNext : nullptr;
      else
        v9 = nullptr;
      v10 = Attach_eUpdateAttachmentEvent;
      QTask_atProtectedQTaskStack[v3].ptQTask = v9;
      v11 = (void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[v10][v8->eQTaskType].pfHandler;
      v12 = v3 + 1;
      QTask_nProtectedQTaskStackOffset = v12;
      if ( v11 )
      {
        v11(v8);
        v12 = QTask_nProtectedQTaskStackOffset;
      }
      v8 = (struct QTask_s *)dword_849C7DC[v12];
      v3 = v12 - 1;
      QTask_nProtectedQTaskStackOffset = v3;
    }
    while ( v8 );
  }
}

// source: e/3/rigiddyncubeobj.c:2824  [anchor-callee]
enum bool __cdecl RigidDynCubeObj_IsTransparent(struct RigidDynCubeObj_t *ptRigidDynCubeObj)
{
  struct IsTransparentContext_t tContext; // [esp+0h] [ebp-Ch] BYREF

  tContext.ptRigidDynCubeObj = ptRigidDynCubeObj;
  tContext.iLOD = 0;
  RenderMode_tActiveRenderMode.apfRenderModeMethod[Mesh3D_eIsTransparentRenderModeMethod](&tContext);
  return tContext.isTransparent;
}
