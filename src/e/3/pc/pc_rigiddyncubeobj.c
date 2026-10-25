/* e/3/pc/pc_rigiddyncubeobj.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: e/3/pc/pc_rigiddyncubeobj.c:43  [size~]
void __cdecl RigidDynCubeObj_EnterHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { enum bool pisTotallyInside; };
    struct { char igi2_o1[4]; void ***p_papxElement; };
    struct { char igi2_o2[8]; struct real32x2_t v31; };
    struct { char igi2_o3[16]; struct real32x2_t v32; };
    struct { char igi2_o4[24]; struct QTask_s *v33; };
    struct { char igi2_o5[28]; int *v34; };
    struct { char igi2_o6[32]; int v35; };
    struct { char igi2_o7[36]; struct HazingDynCubeObj_t **v36; };
    struct { char igi2_o8[40]; int v37; };
    struct { char igi2_o9[48]; int v38; };
    struct { char igi2_o10[52]; int v39; };
    struct { char igi2_o11[56]; _BYTE v40[24]; };
    struct { char igi2_o12[80]; _BYTE v41[40]; };
    struct { char igi2_o13[120]; int v42; };
    char igi2_extent[128];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *ptTail; // eax
  signed int v3; // esi
  enum bool v4; // edi
  bool v5; // zf
  struct QReference_s *ptMiddle; // ebp
  unsigned __int16 eQTaskType; // ax
  struct QReference_s *ptNext; // eax
  struct real32x2_t *v9; // eax
  unsigned int *p_nAllocated; // ebp
  struct real32x2_t *v11; // eax
  float vY; // edx
  int v13; // ebp
  int v14; // edx
  int v15; // eax
  struct QTask_s *v16; // eax
  struct QTask_s *ptHead; // eax
  int v18; // edx
  int v19; // eax
  struct QTask_s *v20; // ecx
  void (__cdecl *pfHandler)(int, _BYTE *); // ecx
  int v22; // eax
  struct QTask_s *v23; // ebx
  struct QTask_s *v24; // ecx
  struct QTask_s *v25; // edx
  int v26; // esi
  void (__cdecl *v27)(struct QTask_s *, _BYTE *); // edx
  int v28; // eax

  igi2_frame.v31.vX = RenderContext_tActiveRenderContext.tDisplayAreaMin.vX;
  igi2_frame.v32.vY = RenderContext_tActiveRenderContext.tDisplayAreaMax.vY;
  ptTail = ptQTask[7].tQTaskChildren.ptTail;
  v3 = 0;
  igi2_frame.v31.vY = RenderContext_tActiveRenderContext.tDisplayAreaMin.vY;
  igi2_frame.v32.vX = RenderContext_tActiveRenderContext.tDisplayAreaMax.vX;
  v4 = true;
  igi2_frame.pisTotallyInside = false;
  if ( ptTail )
  {
    v5 = ModelObj_Exclude((struct ModelObj_s *)ptQTask, &igi2_frame.pisTotallyInside) == false;
    goto LABEL_21;
  }
  ptMiddle = ptQTask[2].tQTaskRefList.ptMiddle;
  if ( !pxContext || !*(_DWORD *)pxContext )
  {
    eQTaskType = ptQTask->eQTaskType;
    if ( eQTaskType != ConveyorBelt_eQTaskType
      && eQTaskType != Mine_eQTaskType
      && QTask_IsQTaskTypeDerived(eQTaskType, SectorInteriorObject_eQTaskType) )
    {
      if ( ptMiddle )
      {
        if ( !ptMiddle[32].pxObject )
          return;
        ptNext = ptMiddle[27].ptNext;
        if ( (int)ptNext[3].ptNext > 0 )
        {
          do
          {
            v9 = *((struct real32x2_t **)&ptNext[4].ptNext->ptNext + v3);
            RenderContext_tActiveRenderContext.tDisplayAreaMin = *v9;
            RenderContext_tActiveRenderContext.tDisplayAreaMax = v9[1];
            ++RenderContext_nActiveRenderContextTimeStamp;
            v4 &= ModelObj_Exclude((struct ModelObj_s *)ptQTask, &igi2_frame.pisTotallyInside);
            ptNext = ptMiddle[27].ptNext;
            ++v3;
          }
          while ( v3 < (int)ptNext[3].ptNext );
        }
        RenderContext_tActiveRenderContext.tDisplayAreaMax = igi2_frame.v32;
        RenderContext_tActiveRenderContext.tDisplayAreaMin = igi2_frame.v31;
        ++RenderContext_nActiveRenderContextTimeStamp;
        goto LABEL_20;
      }
      if ( Clipping_tClipData.tClipWindows.ptClipWindowsList )
      {
        p_nAllocated = &Clipping_tClipData.tClipWindows.ptClipWindowsList->nAllocated;
        if ( (int)Clipping_tClipData.tClipWindows.ptClipWindowsList->nAllocated > 0 )
        {
          igi2_frame.p_papxElement = &Clipping_tClipData.tClipWindows.ptClipWindowsList->papxElement;
          do
          {
            v11 = (struct real32x2_t *)(*igi2_frame.p_papxElement)[v3];
            RenderContext_tActiveRenderContext.tDisplayAreaMin = *v11;
            RenderContext_tActiveRenderContext.tDisplayAreaMax.vX = v11[1].vX;
            vY = v11[1].vY;
            ++RenderContext_nActiveRenderContextTimeStamp;
            RenderContext_tActiveRenderContext.tDisplayAreaMax.vY = vY;
            v4 &= ModelObj_Exclude((struct ModelObj_s *)ptQTask, &igi2_frame.pisTotallyInside);
            ++v3;
          }
          while ( v3 < (int)*p_nAllocated );
        }
        RenderContext_tActiveRenderContext.tDisplayAreaMax = igi2_frame.v32;
        RenderContext_tActiveRenderContext.tDisplayAreaMin = igi2_frame.v31;
        ++RenderContext_nActiveRenderContextTimeStamp;
        goto LABEL_20;
      }
      if ( QCube_ptInsideSectorObject )
        return;
    }
    v4 = ModelObj_Exclude((struct ModelObj_s *)ptQTask, &igi2_frame.pisTotallyInside);
LABEL_20:
    v5 = v4 == false;
LABEL_21:
    if ( !v5 )
      return;
  }
  igi2_frame.v38 = 1;
  igi2_frame.v39 = 1;
  v13 = Lightsource_nLightDataStackPos + Lightsource_nLightDataBufferPos;
  igi2_frame.v35 = Lightsource_nLightDataStackPos;
  v14 = Hazinglayers_iHazingBuffer;
  igi2_frame.v34 = (int *)(4 * Lightsource_nLightDataBufferPos + 140666816);
  v15 = Hazinglayers_iHazingStack;
  qmemcpy(igi2_frame.v34, Lightsource_anLightDataStack, 4 * Lightsource_nLightDataStackPos);
  igi2_frame.v33 = ptQTask;
  igi2_frame.v36 = (struct HazingDynCubeObj_t **)(4 * v14 + 129834072);
  qmemcpy(igi2_frame.v36, Hazinglayers_aptHazingStack, 4 * v15);
  Hazinglayers_iHazingBuffer = v15 + v14;
  Lightsource_nLightDataBufferPos = v13;
  igi2_frame.v37 = v15;
  RenderMode_tActiveRenderMode.apfRenderModeMethod[Mesh3D_eDrawRigidMeshRenderModeMethod](&igi2_frame.v33);
  v16 = ptQTask[3].ptNext;
  qmemcpy(igi2_frame.v40, &ptQTask[1], sizeof(igi2_frame.v40));
  qmemcpy(igi2_frame.v41, &ptQTask[3].ptPrev, sizeof(igi2_frame.v41));
  igi2_frame.v42 = 1;
  if ( v16 && (ptHead = v16->tQTaskChildren.ptHead, ptHead->ptNext) && (v18 = (int)ptHead) != 0 )
  {
    v19 = QTask_nProtectedQTaskStackOffset;
    do
    {
      if ( *(_DWORD *)v18 )
        v20 = **(_DWORD **)v18 != 0 ? *(struct QTask_s **)v18 : nullptr;
      else
        v20 = nullptr;
      QTask_atProtectedQTaskStack[v19].ptQTask = v20;
      pfHandler = (void (__cdecl *)(int, _BYTE *))QTask_aatQTaskFinalEvent[MagicObj_eMagicObjEnterEvent][*(unsigned __int16 *)(v18 + 36)].pfHandler;
      v22 = v19 + 1;
      QTask_nProtectedQTaskStackOffset = v22;
      if ( pfHandler )
      {
        pfHandler(v18, igi2_frame.v40);
        v22 = QTask_nProtectedQTaskStackOffset;
      }
      v18 = dword_849C7DC[v22];
      v19 = v22 - 1;
      QTask_nProtectedQTaskStackOffset = v19;
    }
    while ( v18 );
  }
  else
  {
    v19 = QTask_nProtectedQTaskStackOffset;
  }
  v23 = ptQTask->tQTaskChildren.ptHead;
  if ( v23->ptNext )
  {
    v24 = ptQTask->tQTaskChildren.ptHead;
    if ( v23 )
    {
      do
      {
        if ( v24->ptNext )
          v25 = v24->ptNext->ptNext != nullptr ? v24->ptNext : nullptr;
        else
          v25 = nullptr;
        v26 = MagicObj_eMagicObjEnterEvent;
        QTask_atProtectedQTaskStack[v19].ptQTask = v25;
        v27 = (void (__cdecl *)(struct QTask_s *, _BYTE *))QTask_aatQTaskFinalEvent[v26][v24->eQTaskType].pfHandler;
        v28 = v19 + 1;
        QTask_nProtectedQTaskStackOffset = v28;
        if ( v27 )
        {
          v27(v24, igi2_frame.v40);
          v28 = QTask_nProtectedQTaskStackOffset;
        }
        v24 = (struct QTask_s *)dword_849C7DC[v28];
        v19 = v28 - 1;
        QTask_nProtectedQTaskStackOffset = v19;
      }
      while ( v24 );
    }
  }
}

// source: e/3/pc/pc_rigiddyncubeobj.c:266  [size]
void __cdecl RigidDynCubeObj_DrawEnvmapHandler(struct QTask_s *ptQTask, void *pxContext)
{
  int v2; // ebx
  int v3; // edx
  int v4; // eax
  struct DrawRigidMeshContext_t tContext; // [esp+Ch] [ebp-20h] BYREF

  tContext.ptRigidDynCubeObj = (struct RigidDynCubeObj_t *)ptQTask;
  v2 = Lightsource_nLightDataStackPos + Lightsource_nLightDataBufferPos;
  tContext.tLightContext.nLightNum = Lightsource_nLightDataStackPos;
  v3 = Hazinglayers_iHazingBuffer;
  tContext.tLightContext.pnLightList = (int *)(4 * Lightsource_nLightDataBufferPos + 140666816);
  v4 = Hazinglayers_iHazingStack;
  qmemcpy(tContext.tLightContext.pnLightList, Lightsource_anLightDataStack, 4 * Lightsource_nLightDataStackPos);
  tContext.isSort = false;
  tContext.isExcludeTestPassed = true;
  tContext.eDrawMode = MESH3D_DRAWMODE_ENVMAP;
  tContext.tLightContext.pptHazingList = (struct HazingDynCubeObj_t **)(4 * v3 + 129834072);
  qmemcpy(tContext.tLightContext.pptHazingList, Hazinglayers_aptHazingStack, 4 * v4);
  Hazinglayers_iHazingBuffer = v4 + v3;
  Lightsource_nLightDataBufferPos = v2;
  tContext.tLightContext.nNumHazingBox = v4;
  RenderMode_tActiveRenderMode.apfRenderModeMethod[Mesh3D_eDrawRigidMeshRenderModeMethod](&tContext);
}

// source: e/3/pc/pc_rigiddyncubeobj.c:293  [size~]
void __cdecl RigidDynCubeObj_EnumerateEnvmapHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QObjectVector_s *v2; // esi
  unsigned int nAllocated; // eax
  struct QTask_s **v4; // edi
  int v5; // eax
  struct QTask_s *ptNext; // eax
  int ptHead; // eax
  int v8; // edx
  struct QTask_s *v9; // ecx
  void (__cdecl *pfHandler)(int, void *); // ecx
  int v11; // edx
  struct QTask_s *v12; // eax
  struct QTask_s *v13; // ecx
  void (__cdecl *v14)(struct QTask_s *, void *); // ecx
  int v15; // edx
  struct QTask_s *v16; // eax
  struct QTask_s *v17; // ecx
  void (__cdecl *v18)(struct QTask_s *, void *); // ecx
  int v19; // edx
  _DWORD v20[3]; // [esp+4h] [ebp-Ch] BYREF

  if ( (*((_BYTE *)pxContext + 8) & 4) != 0 )
  {
    v2 = *(struct QObjectVector_s **)pxContext;
    if ( *(_DWORD *)(*(_DWORD *)pxContext + 36) == *(_DWORD *)(*(_DWORD *)pxContext + 40) )
      QObjectVector_Realloc(*(struct QObjectVector_s **)pxContext, v2->nReallocSize);
    nAllocated = v2->nAllocated;
    v4 = (struct QTask_s **)v2->papxElement[nAllocated];
    v2->nAllocated = nAllocated + 1;
    v5 = Mesh3D_eIsTransparentRenderModeMethod;
    *v4 = ptQTask;
    v20[0] = ptQTask;
    v20[1] = 0;
    RenderMode_tActiveRenderMode.apfRenderModeMethod[v5](v20);
    v4[1] = (struct QTask_s *)((v20[2] != 0) + 2);
    ptNext = ptQTask[3].ptNext;
    if ( ptNext && (ptHead = (int)ptNext->tQTaskChildren.ptHead, *(_DWORD *)ptHead) && ptHead )
    {
      v8 = QTask_nProtectedQTaskStackOffset;
      do
      {
        if ( *(_DWORD *)ptHead )
          v9 = **(_DWORD **)ptHead != 0 ? *(struct QTask_s **)ptHead : nullptr;
        else
          v9 = nullptr;
        QTask_atProtectedQTaskStack[v8].ptQTask = v9;
        pfHandler = (void (__cdecl *)(int, void *))QTask_aatQTaskFinalEvent[Envmap_eEnumerateQTaskEvent][*(unsigned __int16 *)(ptHead + 36)].pfHandler;
        v11 = v8 + 1;
        QTask_nProtectedQTaskStackOffset = v11;
        if ( pfHandler )
        {
          pfHandler(ptHead, pxContext);
          v11 = QTask_nProtectedQTaskStackOffset;
        }
        ptHead = dword_849C7DC[v11];
        v8 = v11 - 1;
        QTask_nProtectedQTaskStackOffset = v8;
      }
      while ( ptHead );
    }
    else
    {
      v8 = QTask_nProtectedQTaskStackOffset;
    }
    if ( QTask_IsQTaskTypeDerived(ptQTask->eQTaskType, SectorObject_eQTaskType) )
    {
      v12 = ptQTask[10].ptNext->tQTaskChildren.ptHead;
      if ( v12->ptNext )
      {
        for ( ; v12; QTask_nProtectedQTaskStackOffset = v8 )
        {
          if ( v12->ptNext )
            v13 = v12->ptNext->ptNext != nullptr ? v12->ptNext : nullptr;
          else
            v13 = nullptr;
          QTask_atProtectedQTaskStack[v8].ptQTask = v13;
          v14 = (void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[Envmap_eEnumerateQTaskEvent][v12->eQTaskType].pfHandler;
          v15 = v8 + 1;
          QTask_nProtectedQTaskStackOffset = v15;
          if ( v14 )
          {
            v14(v12, pxContext);
            v15 = QTask_nProtectedQTaskStackOffset;
          }
          v12 = (struct QTask_s *)dword_849C7DC[v15];
          v8 = v15 - 1;
        }
      }
    }
    v16 = ptQTask->tQTaskChildren.ptHead;
    if ( v16->ptNext && v16 )
    {
      do
      {
        if ( v16->ptNext )
          v17 = v16->ptNext->ptNext != nullptr ? v16->ptNext : nullptr;
        else
          v17 = nullptr;
        QTask_atProtectedQTaskStack[v8].ptQTask = v17;
        v18 = (void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[Envmap_eEnumerateQTaskEvent][v16->eQTaskType].pfHandler;
        v19 = v8 + 1;
        QTask_nProtectedQTaskStackOffset = v19;
        if ( v18 )
        {
          v18(v16, pxContext);
          v19 = QTask_nProtectedQTaskStackOffset;
        }
        v16 = (struct QTask_s *)dword_849C7DC[v19];
        v8 = v19 - 1;
        QTask_nProtectedQTaskStackOffset = v8;
      }
      while ( v16 );
    }
  }
}

// source: e/3/pc/pc_rigiddyncubeobj.c:346  [anchor-mhash]
void __cdecl RigidDynCubeObj_GetObjectBoundingSphereHandler(struct QTask_s *ptQTask, void *pxContext)
{
  _WORD *v2; // ecx
  int v3; // ecx
  double v4; // rt0
  float Real32x3_Rotate_tTemp_8; // [esp+8h] [ebp-4h]

  v2 = *(_WORD **)&ptQTask[2].eQTaskType;
  if ( v2 )
  {
    if ( v2[30] )
    {
      v3 = *(_DWORD *)(*(_DWORD *)(*(_DWORD *)v2 + 12) + 12);
      Real32x3_Rotate_tTemp_8 = *(float *)&ptQTask[3].eQTaskType * *(float *)(v3 + 56)
                              + *(float *)&ptQTask[3].ptParent * *(float *)(v3 + 52)
                              + *(float *)&ptQTask[3].tQTaskRefList.ptTail * *(float *)(v3 + 48);
      v4 = *(float *)&ptQTask[3].tQTaskRefList.ptMiddle * *(float *)(v3 + 56)
         + *(float *)&ptQTask[3].tQTaskRefList.ptHead * *(float *)(v3 + 52)
         + *(float *)&ptQTask[3].tQTaskChildren.ptTail * *(float *)(v3 + 48);
      *(double *)pxContext = *(float *)&ptQTask[3].tQTaskChildren.ptMiddle * *(float *)(v3 + 56)
                           + *(float *)&ptQTask[3].tQTaskChildren.ptHead * *(float *)(v3 + 52)
                           + *(float *)&ptQTask[3].ptPrev * *(float *)(v3 + 48)
                           + *(double *)&ptQTask[1].ptNext;
      *((double *)pxContext + 1) = v4 + *(double *)&ptQTask[1].tQTaskChildren.ptHead;
      *((double *)pxContext + 2) = Real32x3_Rotate_tTemp_8 + *(double *)&ptQTask[1].tQTaskChildren.ptTail;
      *((_DWORD *)pxContext + 6) = *(_DWORD *)(v3 + 60);
    }
  }
}

// source: e/3/pc/pc_rigiddyncubeobj.c:392  [anchor-mhash]
void __cdecl RigidDynCubeObj_GetClosestVertex(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct MultiMesh_TransformedVertex_t v70; };
    struct { char igi2_o1[28]; struct MultiMesh_TransformedVertex_t v71; };
    struct { char igi2_o2[56]; struct MultiMesh_TransformedVertex_t v72; };
    struct { char igi2_o3[108]; struct RigidDirect3D_FaceGroup_t *ptFaceGroup; };
    struct { char igi2_o4[112]; float vClosestZ; };
    struct { char igi2_o5[116]; float vRadius; };
    struct { char igi2_o6[120]; struct real32x3_t tPos; };
    struct { char igi2_o7[132]; int iFace; };
    struct { char igi2_o8[136]; struct LightmapDirect3D_Vertex_t *ptVertex; };
    struct { char igi2_o9[140]; struct real32x3_t Real32x3_Rotate_tTemp; };
    struct { char igi2_o10[152]; struct real32x3_t tProjected; };
    struct { char igi2_o11[164]; struct real32x3_t ptRotatedPos; };
    struct { char igi2_o12[176]; float vClipZ; };
    struct { char igi2_o13[180]; float v83; };
    struct { char igi2_o14[184]; float v84; };
    struct { char igi2_o15[188]; float v85; };
    struct { char igi2_o16[192]; struct real32x9_t tMatrix; };
    struct { char igi2_o17[232]; struct RigidDirect3D_FaceGroup_t *ptEnd; };
    struct { char igi2_o18[236]; unsigned int v88; };
    struct { char igi2_o19[240]; struct real32x9_t Real32x9_Multiply_tTemp; };
    char igi2_extent[280];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v2; // eax
  int v3; // esi
  float *v4; // eax
  double v5; // st7
  double v6; // st6
  double v7; // st7
  double v8; // st6
  double v9; // st4
  double v10; // st7
  bool v11; // c0
  bool v12; // c3
  double v13; // st7
  double v14; // st7
  float *v15; // edi
  double v16; // st7
  int v17; // eax
  int v18; // ebp
  double v19; // st6
  double v20; // st5
  double v21; // st4
  double v22; // st6
  double v23; // st5
  int v24; // eax
  struct RigidDirect3D_FaceGroup_t *v25; // edx
  struct RigidDirect3D_FaceGroup_t *v26; // ecx
  int *v27; // edx
  double v28; // st6
  double v29; // st6
  double v30; // st6
  double v31; // st5
  int v32; // eax
  bool v33; // cc
  bool v34; // zf
  float v35; // ecx
  int v36; // eax
  float *v37; // esi
  float *v38; // edx
  unsigned int v39; // edi
  int v40; // ebp
  int v41; // eax
  double v42; // st6
  int v43; // ebp
  double v44; // st5
  double v45; // st5
  double v46; // st4
  int v47; // eax
  struct LightmapDirect3D_Vertex_t *v48; // ecx
  double v49; // st6
  int *v50; // edx
  double v51; // st6
  double v52; // st6
  double v53; // st6
  double v54; // st5
  int v55; // eax
  float v56; // ecx
  int iStartVertex; // eax
  float *v58; // esi
  float *v59; // edx
  struct RigidDirect3D_FaceGroup_t *v60; // edi
  int v61; // ebp
  int v62; // eax
  struct QTask_s *ptNext; // ebx
  int ptHead; // eax
  int v65; // edx
  struct QTask_s *v66; // ecx
  int v67; // esi
  void (__cdecl *pfHandler)(int, float *); // ecx
  int v69; // edx

  igi2_frame.vClipZ = Direct3D_vWorldMinZ;
  if ( ptQTask[7].ptPrev == (struct QTask_s *)1 )
  {
    v2 = *(_DWORD *)&ptQTask[2].eQTaskType;
    if ( v2 )
    {
      if ( *(_DWORD *)v2 )
      {
        v3 = *(_DWORD *)(*(_DWORD *)(*(_DWORD *)v2 + 12) + 12);
        igi2_frame.ptRotatedPos.vX = *(double *)&ptQTask[1].ptNext - TransContext_tActiveTransContext.tPos.vX;
        igi2_frame.ptRotatedPos.vY = *(double *)&ptQTask[1].tQTaskChildren.ptHead - TransContext_tActiveTransContext.tPos.vY;
        igi2_frame.ptRotatedPos.vZ = *(double *)&ptQTask[1].tQTaskChildren.ptTail - TransContext_tActiveTransContext.tPos.vZ;
        v4 = *(float **)(*(_DWORD *)(*(_DWORD *)v2 + 12) + 12);
        v5 = *(float *)&ptQTask[3].tQTaskChildren.ptMiddle * v4[14]
           + *(float *)&ptQTask[3].tQTaskChildren.ptHead * v4[13]
           + v4[12] * *(float *)&ptQTask[3].ptPrev;
        v6 = v4[13] * *(float *)&ptQTask[3].tQTaskRefList.ptHead
           + v4[12] * *(float *)&ptQTask[3].tQTaskChildren.ptTail
           + *(float *)&ptQTask[3].tQTaskRefList.ptMiddle * v4[14];
        igi2_frame.v85 = v4[12] * *(float *)&ptQTask[3].tQTaskRefList.ptTail
            + *(float *)&ptQTask[3].ptParent * v4[13]
            + v4[14] * *(float *)&ptQTask[3].eQTaskType;
        igi2_frame.ptRotatedPos.vX = v5 + igi2_frame.ptRotatedPos.vX;
        v7 = v6 + igi2_frame.ptRotatedPos.vY;
        v8 = igi2_frame.v85 + igi2_frame.ptRotatedPos.vZ;
        igi2_frame.Real32x3_Rotate_tTemp.vX = TransContext_tActiveTransContext.tMatrix.tX.vZ * v8
                                 + TransContext_tActiveTransContext.tMatrix.tX.vY * v7
                                 + TransContext_tActiveTransContext.tMatrix.tX.vX * igi2_frame.ptRotatedPos.vX;
        igi2_frame.Real32x3_Rotate_tTemp.vY = TransContext_tActiveTransContext.tMatrix.tY.vZ * v8
                                 + TransContext_tActiveTransContext.tMatrix.tY.vY * v7
                                 + TransContext_tActiveTransContext.tMatrix.tY.vX * igi2_frame.ptRotatedPos.vX;
        igi2_frame.ptRotatedPos.vY = igi2_frame.Real32x3_Rotate_tTemp.vY;
        v9 = TransContext_tActiveTransContext.tMatrix.tZ.vX * igi2_frame.ptRotatedPos.vX;
        igi2_frame.ptRotatedPos.vX = igi2_frame.Real32x3_Rotate_tTemp.vX;
        igi2_frame.Real32x3_Rotate_tTemp.vZ = TransContext_tActiveTransContext.tMatrix.tZ.vZ * v8
                                 + TransContext_tActiveTransContext.tMatrix.tZ.vY * v7
                                 + v9;
        v10 = *(float *)&ptQTask[6].ptPrev;
        v11 = v10 < *(float *)&ptQTask[6].tQTaskChildren.ptHead;
        v12 = v10 == *(float *)&ptQTask[6].tQTaskChildren.ptHead;
        igi2_frame.ptRotatedPos.vZ = igi2_frame.Real32x3_Rotate_tTemp.vZ;
        v13 = v11 || v12 ? *(float *)&ptQTask[6].tQTaskChildren.ptHead : *(float *)&ptQTask[6].ptPrev;
        if ( v13 <= *(float *)&ptQTask[6].tQTaskChildren.ptMiddle )
          v14 = *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
        else
          v14 = *(float *)&ptQTask[6].ptPrev <= (double)*(float *)&ptQTask[6].tQTaskChildren.ptHead
              ? *(float *)&ptQTask[6].tQTaskChildren.ptHead
              : *(float *)&ptQTask[6].ptPrev;
        igi2_frame.vRadius = v14 * *(float *)(v3 + 60);
        if ( Mesh3D_ExcludeObject(&igi2_frame.ptRotatedPos, igi2_frame.vRadius, nullptr) == false )
        {
          v15 = (float *)pxContext;
          v16 = igi2_frame.ptRotatedPos.vZ - igi2_frame.vRadius;
          if ( v16 <= *((float *)pxContext + 2) )
          {
            v17 = *(_DWORD *)(v3 + 32);
            if ( v17 )
            {
              if ( v17 == 3 )
              {
                v42 = *(double *)&ptQTask[1].ptNext - TransContext_tActiveTransContext.tPos.vX;
                v43 = *(_DWORD *)(v3 + 36);
                v44 = *(double *)&ptQTask[1].tQTaskChildren.ptHead;
                igi2_frame.vClosestZ = *((float *)pxContext + 2);
                v45 = v44 - TransContext_tActiveTransContext.tPos.vY;
                v46 = *(double *)&ptQTask[1].tQTaskChildren.ptTail - TransContext_tActiveTransContext.tPos.vZ;
                igi2_frame.v83 = TransContext_tActiveTransContext.tMatrix.tX.vZ * v46
                    + v45 * TransContext_tActiveTransContext.tMatrix.tX.vY
                    + v42 * TransContext_tActiveTransContext.tMatrix.tX.vX;
                igi2_frame.v84 = TransContext_tActiveTransContext.tMatrix.tY.vZ * v46
                    + v45 * TransContext_tActiveTransContext.tMatrix.tY.vY
                    + v42 * TransContext_tActiveTransContext.tMatrix.tY.vX;
                igi2_frame.v85 = v46 * TransContext_tActiveTransContext.tMatrix.tZ.vZ
                    + v45 * TransContext_tActiveTransContext.tMatrix.tZ.vY
                    + v42 * TransContext_tActiveTransContext.tMatrix.tZ.vX;
                igi2_frame.tMatrix.tX.vX = TransContext_tActiveTransContext.tMatrix.tX.vY
                              * *(float *)&ptQTask[3].tQTaskChildren.ptTail
                              + TransContext_tActiveTransContext.tMatrix.tX.vX * *(float *)&ptQTask[3].ptPrev
                              + TransContext_tActiveTransContext.tMatrix.tX.vZ
                              * *(float *)&ptQTask[3].tQTaskRefList.ptTail;
                igi2_frame.tMatrix.tX.vY = TransContext_tActiveTransContext.tMatrix.tX.vZ * *(float *)&ptQTask[3].ptParent
                              + TransContext_tActiveTransContext.tMatrix.tX.vX
                              * *(float *)&ptQTask[3].tQTaskChildren.ptHead
                              + TransContext_tActiveTransContext.tMatrix.tX.vY
                              * *(float *)&ptQTask[3].tQTaskRefList.ptHead;
                igi2_frame.tMatrix.tX.vZ = TransContext_tActiveTransContext.tMatrix.tX.vX
                              * *(float *)&ptQTask[3].tQTaskChildren.ptMiddle
                              + TransContext_tActiveTransContext.tMatrix.tX.vY
                              * *(float *)&ptQTask[3].tQTaskRefList.ptMiddle
                              + TransContext_tActiveTransContext.tMatrix.tX.vZ * *(float *)&ptQTask[3].eQTaskType;
                igi2_frame.tMatrix.tY.vX = TransContext_tActiveTransContext.tMatrix.tY.vY
                              * *(float *)&ptQTask[3].tQTaskChildren.ptTail
                              + TransContext_tActiveTransContext.tMatrix.tY.vX * *(float *)&ptQTask[3].ptPrev
                              + TransContext_tActiveTransContext.tMatrix.tY.vZ
                              * *(float *)&ptQTask[3].tQTaskRefList.ptTail;
                v47 = *(_DWORD *)(v43 + 16);
                v48 = *(struct LightmapDirect3D_Vertex_t **)(v43 + 20);
                v49 = TransContext_tActiveTransContext.tMatrix.tY.vZ * *(float *)&ptQTask[3].ptParent
                    + TransContext_tActiveTransContext.tMatrix.tY.vX * *(float *)&ptQTask[3].tQTaskChildren.ptHead;
                igi2_frame.ptVertex = v48;
                igi2_frame.iFace = 0;
                igi2_frame.tMatrix.tY.vY = v49
                              + TransContext_tActiveTransContext.tMatrix.tY.vY
                              * *(float *)&ptQTask[3].tQTaskRefList.ptHead;
                igi2_frame.tMatrix.tY.vZ = TransContext_tActiveTransContext.tMatrix.tY.vX
                              * *(float *)&ptQTask[3].tQTaskChildren.ptMiddle
                              + TransContext_tActiveTransContext.tMatrix.tY.vY
                              * *(float *)&ptQTask[3].tQTaskRefList.ptMiddle
                              + TransContext_tActiveTransContext.tMatrix.tY.vZ * *(float *)&ptQTask[3].eQTaskType;
                igi2_frame.tMatrix.tZ.vX = TransContext_tActiveTransContext.tMatrix.tZ.vY
                              * *(float *)&ptQTask[3].tQTaskChildren.ptTail
                              + TransContext_tActiveTransContext.tMatrix.tZ.vX * *(float *)&ptQTask[3].ptPrev
                              + TransContext_tActiveTransContext.tMatrix.tZ.vZ
                              * *(float *)&ptQTask[3].tQTaskRefList.ptTail;
                igi2_frame.tMatrix.tZ.vY = TransContext_tActiveTransContext.tMatrix.tZ.vZ * *(float *)&ptQTask[3].ptParent
                              + TransContext_tActiveTransContext.tMatrix.tZ.vX
                              * *(float *)&ptQTask[3].tQTaskChildren.ptHead
                              + TransContext_tActiveTransContext.tMatrix.tZ.vY
                              * *(float *)&ptQTask[3].tQTaskRefList.ptHead;
                igi2_frame.tMatrix.tZ.vZ = TransContext_tActiveTransContext.tMatrix.tZ.vX
                              * *(float *)&ptQTask[3].tQTaskChildren.ptMiddle
                              + TransContext_tActiveTransContext.tMatrix.tZ.vY
                              * *(float *)&ptQTask[3].tQTaskRefList.ptMiddle
                              + TransContext_tActiveTransContext.tMatrix.tZ.vZ * *(float *)&ptQTask[3].eQTaskType;
                if ( v47 > 0 )
                {
                  v50 = dword_7E65FD8;
                  do
                  {
                    igi2_frame.Real32x3_Rotate_tTemp.vX = igi2_frame.tMatrix.tX.vZ * v48->tPos.vZ
                                             + igi2_frame.tMatrix.tX.vY * v48->tPos.vY
                                             + igi2_frame.tMatrix.tX.vX * v48->tPos.vX;
                    igi2_frame.tPos.vX = igi2_frame.Real32x3_Rotate_tTemp.vX;
                    igi2_frame.Real32x3_Rotate_tTemp.vY = igi2_frame.tMatrix.tY.vZ * v48->tPos.vZ
                                             + igi2_frame.tMatrix.tY.vY * v48->tPos.vY
                                             + igi2_frame.tMatrix.tY.vX * v48->tPos.vX;
                    igi2_frame.tPos.vY = igi2_frame.Real32x3_Rotate_tTemp.vY;
                    igi2_frame.Real32x3_Rotate_tTemp.vZ = igi2_frame.tMatrix.tZ.vZ * v48->tPos.vZ
                                             + igi2_frame.tMatrix.tZ.vY * v48->tPos.vY
                                             + igi2_frame.tMatrix.tZ.vX * v48->tPos.vX;
                    igi2_frame.tPos.vX = igi2_frame.Real32x3_Rotate_tTemp.vX + igi2_frame.v83;
                    igi2_frame.tPos.vY = igi2_frame.Real32x3_Rotate_tTemp.vY + igi2_frame.v84;
                    v51 = igi2_frame.Real32x3_Rotate_tTemp.vZ + igi2_frame.v85;
                    igi2_frame.tPos.vZ = v51;
                    if ( v51 < igi2_frame.vClipZ )
                    {
                      v55 = 16;
                    }
                    else
                    {
                      v52 = 1.0 / igi2_frame.tPos.vZ;
                      igi2_frame.tProjected.vZ = v52;
                      v53 = v52 * igi2_frame.tPos.vX * TransContext_tActiveTransContext.vScreenFOVX
                          + TransContext_tActiveTransContext.vScreenOriginX;
                      igi2_frame.tProjected.vX = v53;
                      v54 = igi2_frame.tProjected.vZ * igi2_frame.tPos.vY * TransContext_tActiveTransContext.vScreenFOVY
                          + TransContext_tActiveTransContext.vScreenOriginY;
                      igi2_frame.tProjected.vY = v54;
                      v48 = igi2_frame.ptVertex;
                      v55 = (v53 < RenderContext_tActiveRenderContext.tDisplayAreaMin.vX)
                          | (2
                           * ((v54 < RenderContext_tActiveRenderContext.tDisplayAreaMin.vY)
                            | (2
                             * ((v53 > RenderContext_tActiveRenderContext.tDisplayAreaMax.vX)
                              | (2 * (igi2_frame.tProjected.vY > (double)RenderContext_tActiveRenderContext.tDisplayAreaMax.vY))))));
                    }
                    *((struct real32x3_t *)v50 - 2) = igi2_frame.tPos;
                    *((struct real32x3_t *)v50 - 1) = igi2_frame.tProjected;
                    *v50 = v55;
                    if ( !v55 && igi2_frame.tPos.vZ < (double)igi2_frame.vClosestZ )
                      igi2_frame.vClosestZ = igi2_frame.tPos.vZ;
                    ++v48;
                    v50 += 7;
                    v33 = ++igi2_frame.iFace < (int)(*(_DWORD *)(v43 + 16));
                    igi2_frame.ptVertex = v48;
                  }
                  while ( v33 );
                  v15 = (float *)pxContext;
                }
                if ( v16 < v15[2] )
                {
                  igi2_frame.ptFaceGroup = *(struct RigidDirect3D_FaceGroup_t **)(v43 + 32);
                  if ( igi2_frame.ptFaceGroup )
                  {
                    igi2_frame.v88 = (unsigned int)igi2_frame.ptFaceGroup + 28 * *(_DWORD *)(v43 + 12);
                    do
                    {
                      v34 = igi2_frame.ptFaceGroup->nNumFaces == 0;
                      LODWORD(v56) = &igi2_frame.ptFaceGroup->iEnvMap;
                      LODWORD(igi2_frame.vRadius) = &igi2_frame.ptFaceGroup->iEnvMap;
                      igi2_frame.ptVertex = nullptr;
                      if ( !v34 )
                      {
                        do
                        {
                          iStartVertex = igi2_frame.ptFaceGroup->iStartVertex;
                          v58 = (float *)(28 * (iStartVertex + *(unsigned __int16 *)(LODWORD(v56) + 4)) + 132538304);
                          v59 = (float *)(28 * (iStartVertex + (unsigned __int16)*(_WORD *)LODWORD(v56)) + 132538304);
                          v60 = (struct RigidDirect3D_FaceGroup_t *)dword_7E65FD8[7 * iStartVertex
                                                                                + 7
                                                                                * (unsigned __int16)*(_WORD *)LODWORD(v56)];
                          v61 = 28 * (iStartVertex + *(unsigned __int16 *)(LODWORD(v56) + 2)) + 132538304;
                          igi2_frame.iFace = dword_7E65FD8[7 * iStartVertex + 7 * *(unsigned __int16 *)(LODWORD(v56) + 4)];
                          v62 = *(_DWORD *)(v61 + 24);
                          igi2_frame.ptEnd = v60;
                          if ( igi2_frame.iFace | v62 | (unsigned int)v60
                            && (*(_DWORD *)(v61 + 24) & (unsigned int)igi2_frame.ptEnd & igi2_frame.iFace) == 0
                            && (v59[2] < (double)igi2_frame.vClosestZ
                             || *(float *)(v61 + 8) < (double)igi2_frame.vClosestZ
                             || v58[2] < (double)igi2_frame.vClosestZ) )
                          {
                            qmemcpy(&igi2_frame.v72, v58, sizeof(igi2_frame.v72));
                            qmemcpy(&igi2_frame.v71, (void *)v61, sizeof(igi2_frame.v71));
                            qmemcpy(&igi2_frame.v70, v59, sizeof(igi2_frame.v70));
                            RigidDynCubeObj_CheckTriangle(igi2_frame.v70, igi2_frame.v71, igi2_frame.v72, &igi2_frame.vClosestZ, igi2_frame.vClipZ);
                            v56 = igi2_frame.vRadius;
                          }
                          LODWORD(v56) += 6;
                          v33 = (int)&igi2_frame.ptVertex->tPos.vX + 1 < igi2_frame.ptFaceGroup->nNumFaces;
                          igi2_frame.ptVertex = (struct LightmapDirect3D_Vertex_t *)((char *)igi2_frame.ptVertex + 1);
                          igi2_frame.vRadius = v56;
                        }
                        while ( v33 );
                      }
                      igi2_frame.ptFaceGroup = (struct RigidDirect3D_FaceGroup_t *)((char *)igi2_frame.ptFaceGroup + 28);
                    }
                    while ( (unsigned int)igi2_frame.ptFaceGroup < igi2_frame.v88 );
                  }
                }
                *((float *)pxContext + 2) = igi2_frame.vClosestZ;
                v15 = (float *)pxContext;
              }
            }
            else
            {
              v18 = *(_DWORD *)(v3 + 36);
              v19 = *(double *)&ptQTask[1].ptNext - TransContext_tActiveTransContext.tPos.vX;
              v20 = *(double *)&ptQTask[1].tQTaskChildren.ptHead - TransContext_tActiveTransContext.tPos.vY;
              igi2_frame.vClosestZ = *((float *)pxContext + 2);
              v21 = *(double *)&ptQTask[1].tQTaskChildren.ptTail - TransContext_tActiveTransContext.tPos.vZ;
              igi2_frame.v83 = TransContext_tActiveTransContext.tMatrix.tX.vZ * v21
                  + v20 * TransContext_tActiveTransContext.tMatrix.tX.vY
                  + v19 * TransContext_tActiveTransContext.tMatrix.tX.vX;
              igi2_frame.v84 = TransContext_tActiveTransContext.tMatrix.tY.vZ * v21
                  + v20 * TransContext_tActiveTransContext.tMatrix.tY.vY
                  + v19 * TransContext_tActiveTransContext.tMatrix.tY.vX;
              igi2_frame.v85 = v21 * TransContext_tActiveTransContext.tMatrix.tZ.vZ
                  + v20 * TransContext_tActiveTransContext.tMatrix.tZ.vY
                  + v19 * TransContext_tActiveTransContext.tMatrix.tZ.vX;
              igi2_frame.Real32x9_Multiply_tTemp.tX.vX = TransContext_tActiveTransContext.tMatrix.tX.vY
                                            * *(float *)&ptQTask[3].tQTaskChildren.ptTail
                                            + TransContext_tActiveTransContext.tMatrix.tX.vX
                                            * *(float *)&ptQTask[3].ptPrev
                                            + TransContext_tActiveTransContext.tMatrix.tX.vZ
                                            * *(float *)&ptQTask[3].tQTaskRefList.ptTail;
              igi2_frame.Real32x9_Multiply_tTemp.tX.vY = TransContext_tActiveTransContext.tMatrix.tX.vZ
                                            * *(float *)&ptQTask[3].ptParent
                                            + TransContext_tActiveTransContext.tMatrix.tX.vX
                                            * *(float *)&ptQTask[3].tQTaskChildren.ptHead
                                            + TransContext_tActiveTransContext.tMatrix.tX.vY
                                            * *(float *)&ptQTask[3].tQTaskRefList.ptHead;
              igi2_frame.Real32x9_Multiply_tTemp.tX.vZ = TransContext_tActiveTransContext.tMatrix.tX.vX
                                            * *(float *)&ptQTask[3].tQTaskChildren.ptMiddle
                                            + TransContext_tActiveTransContext.tMatrix.tX.vY
                                            * *(float *)&ptQTask[3].tQTaskRefList.ptMiddle
                                            + TransContext_tActiveTransContext.tMatrix.tX.vZ
                                            * *(float *)&ptQTask[3].eQTaskType;
              igi2_frame.Real32x9_Multiply_tTemp.tY.vX = TransContext_tActiveTransContext.tMatrix.tY.vY
                                            * *(float *)&ptQTask[3].tQTaskChildren.ptTail
                                            + TransContext_tActiveTransContext.tMatrix.tY.vX
                                            * *(float *)&ptQTask[3].ptPrev
                                            + TransContext_tActiveTransContext.tMatrix.tY.vZ
                                            * *(float *)&ptQTask[3].tQTaskRefList.ptTail;
              v22 = TransContext_tActiveTransContext.tMatrix.tY.vZ * *(float *)&ptQTask[3].ptParent;
              v23 = TransContext_tActiveTransContext.tMatrix.tY.vX * *(float *)&ptQTask[3].tQTaskChildren.ptHead;
              igi2_frame.Real32x9_Multiply_tTemp.nOps = (int)&ptQTask[4].ptNext->ptNext
                                           + TransContext_tActiveTransContext.tMatrix.nOps
                                           + 1;
              igi2_frame.Real32x9_Multiply_tTemp.tY.vY = v22
                                            + v23
                                            + TransContext_tActiveTransContext.tMatrix.tY.vY
                                            * *(float *)&ptQTask[3].tQTaskRefList.ptHead;
              igi2_frame.Real32x9_Multiply_tTemp.tY.vZ = TransContext_tActiveTransContext.tMatrix.tY.vX
                                            * *(float *)&ptQTask[3].tQTaskChildren.ptMiddle
                                            + TransContext_tActiveTransContext.tMatrix.tY.vY
                                            * *(float *)&ptQTask[3].tQTaskRefList.ptMiddle
                                            + TransContext_tActiveTransContext.tMatrix.tY.vZ
                                            * *(float *)&ptQTask[3].eQTaskType;
              igi2_frame.Real32x9_Multiply_tTemp.tZ.vX = TransContext_tActiveTransContext.tMatrix.tZ.vY
                                            * *(float *)&ptQTask[3].tQTaskChildren.ptTail
                                            + TransContext_tActiveTransContext.tMatrix.tZ.vX
                                            * *(float *)&ptQTask[3].ptPrev
                                            + TransContext_tActiveTransContext.tMatrix.tZ.vZ
                                            * *(float *)&ptQTask[3].tQTaskRefList.ptTail;
              igi2_frame.Real32x9_Multiply_tTemp.tZ.vY = TransContext_tActiveTransContext.tMatrix.tZ.vZ
                                            * *(float *)&ptQTask[3].ptParent
                                            + TransContext_tActiveTransContext.tMatrix.tZ.vX
                                            * *(float *)&ptQTask[3].tQTaskChildren.ptHead
                                            + TransContext_tActiveTransContext.tMatrix.tZ.vY
                                            * *(float *)&ptQTask[3].tQTaskRefList.ptHead;
              igi2_frame.Real32x9_Multiply_tTemp.tZ.vZ = TransContext_tActiveTransContext.tMatrix.tZ.vX
                                            * *(float *)&ptQTask[3].tQTaskChildren.ptMiddle
                                            + TransContext_tActiveTransContext.tMatrix.tZ.vY
                                            * *(float *)&ptQTask[3].tQTaskRefList.ptMiddle
                                            + TransContext_tActiveTransContext.tMatrix.tZ.vZ
                                            * *(float *)&ptQTask[3].eQTaskType;
              qmemcpy(&igi2_frame.tMatrix, &igi2_frame.Real32x9_Multiply_tTemp, sizeof(igi2_frame.tMatrix));
              igi2_frame.tMatrix.tX.vX = igi2_frame.Real32x9_Multiply_tTemp.tX.vX * *(float *)&ptQTask[6].ptPrev;
              igi2_frame.tMatrix.tX.vY = igi2_frame.tMatrix.tX.vY * *(float *)&ptQTask[6].tQTaskChildren.ptHead;
              igi2_frame.tMatrix.tX.vZ = igi2_frame.tMatrix.tX.vZ * *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
              igi2_frame.tMatrix.tY.vX = igi2_frame.tMatrix.tY.vX * *(float *)&ptQTask[6].ptPrev;
              igi2_frame.tMatrix.tY.vY = igi2_frame.tMatrix.tY.vY * *(float *)&ptQTask[6].tQTaskChildren.ptHead;
              igi2_frame.tMatrix.tY.vZ = igi2_frame.tMatrix.tY.vZ * *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
              igi2_frame.tMatrix.tZ.vX = igi2_frame.tMatrix.tZ.vX * *(float *)&ptQTask[6].ptPrev;
              igi2_frame.tMatrix.tZ.vY = igi2_frame.tMatrix.tZ.vY * *(float *)&ptQTask[6].tQTaskChildren.ptHead;
              v24 = *(_DWORD *)(v18 + 12);
              v25 = *(struct RigidDirect3D_FaceGroup_t **)(v18 + 16);
              igi2_frame.tMatrix.tZ.vZ = igi2_frame.tMatrix.tZ.vZ * *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
              igi2_frame.ptFaceGroup = v25;
              igi2_frame.vRadius = 0.0;
              if ( v24 > 0 )
              {
                v26 = igi2_frame.ptFaceGroup;
                v27 = dword_7DDD450;
                do
                {
                  igi2_frame.Real32x3_Rotate_tTemp.vX = igi2_frame.tMatrix.tX.vX * *(float *)&v26->bMaterialProperties
                                           + igi2_frame.tMatrix.tX.vZ * v26->tAveragePos.vY
                                           + igi2_frame.tMatrix.tX.vY * v26->tAveragePos.vX;
                  igi2_frame.tPos.vX = igi2_frame.Real32x3_Rotate_tTemp.vX;
                  igi2_frame.Real32x3_Rotate_tTemp.vY = igi2_frame.tMatrix.tY.vX * *(float *)&v26->bMaterialProperties
                                           + igi2_frame.tMatrix.tY.vZ * v26->tAveragePos.vY
                                           + igi2_frame.tMatrix.tY.vY * v26->tAveragePos.vX;
                  igi2_frame.tPos.vY = igi2_frame.Real32x3_Rotate_tTemp.vY;
                  igi2_frame.Real32x3_Rotate_tTemp.vZ = igi2_frame.tMatrix.tZ.vX * *(float *)&v26->bMaterialProperties
                                           + igi2_frame.tMatrix.tZ.vZ * v26->tAveragePos.vY
                                           + igi2_frame.tMatrix.tZ.vY * v26->tAveragePos.vX;
                  igi2_frame.tPos.vX = igi2_frame.Real32x3_Rotate_tTemp.vX + igi2_frame.v83;
                  igi2_frame.tPos.vY = igi2_frame.Real32x3_Rotate_tTemp.vY + igi2_frame.v84;
                  v28 = igi2_frame.Real32x3_Rotate_tTemp.vZ + igi2_frame.v85;
                  igi2_frame.tPos.vZ = v28;
                  if ( v28 < igi2_frame.vClipZ )
                  {
                    v32 = 16;
                  }
                  else
                  {
                    v29 = 1.0 / igi2_frame.tPos.vZ;
                    igi2_frame.tProjected.vZ = v29;
                    v30 = v29 * igi2_frame.tPos.vX * TransContext_tActiveTransContext.vScreenFOVX
                        + TransContext_tActiveTransContext.vScreenOriginX;
                    igi2_frame.tProjected.vX = v30;
                    v31 = TransContext_tActiveTransContext.vScreenFOVY * igi2_frame.tProjected.vZ * igi2_frame.tPos.vY
                        + TransContext_tActiveTransContext.vScreenOriginY;
                    igi2_frame.tProjected.vY = v31;
                    v26 = igi2_frame.ptFaceGroup;
                    v32 = (v30 < RenderContext_tActiveRenderContext.tDisplayAreaMin.vX)
                        | (2
                         * ((v31 < RenderContext_tActiveRenderContext.tDisplayAreaMin.vY)
                          | (2
                           * ((v30 > RenderContext_tActiveRenderContext.tDisplayAreaMax.vX)
                            | (2 * (igi2_frame.tProjected.vY > (double)RenderContext_tActiveRenderContext.tDisplayAreaMax.vY))))));
                  }
                  *((struct real32x3_t *)v27 - 2) = igi2_frame.tPos;
                  *((struct real32x3_t *)v27 - 1) = igi2_frame.tProjected;
                  *v27 = v32;
                  if ( !v32 && igi2_frame.tPos.vZ < (double)igi2_frame.vClosestZ )
                    igi2_frame.vClosestZ = igi2_frame.tPos.vZ;
                  ++v26;
                  v27 += 7;
                  v33 = (int)(++LODWORD(igi2_frame.vRadius)) < (int)(*(_DWORD *)(v18 + 12));
                  igi2_frame.ptFaceGroup = v26;
                }
                while ( v33 );
              }
              if ( v16 < *((float *)pxContext + 2) )
              {
                igi2_frame.ptFaceGroup = *(struct RigidDirect3D_FaceGroup_t **)(v18 + 24);
                if ( igi2_frame.ptFaceGroup )
                {
                  igi2_frame.ptEnd = &igi2_frame.ptFaceGroup[*(_DWORD *)(v18 + 8)];
                  do
                  {
                    v34 = igi2_frame.ptFaceGroup->nNumFaces == 0;
                    LODWORD(igi2_frame.vRadius) = &igi2_frame.ptFaceGroup[1];
                    igi2_frame.iFace = 0;
                    if ( !v34 )
                    {
                      LODWORD(v35) = &igi2_frame.ptFaceGroup[1];
                      do
                      {
                        v36 = igi2_frame.ptFaceGroup->iStartVertex;
                        v37 = (float *)(28 * (v36 + *(unsigned __int16 *)(LODWORD(v35) + 4)) + 131978296);
                        v38 = (float *)(28 * (v36 + (unsigned __int16)*(_WORD *)LODWORD(v35)) + 131978296);
                        v39 = dword_7DDD450[7 * v36 + 7 * (unsigned __int16)*(_WORD *)LODWORD(v35)];
                        v40 = 28 * (v36 + *(unsigned __int16 *)(LODWORD(v35) + 2)) + 131978296;
                        igi2_frame.ptVertex = (struct LightmapDirect3D_Vertex_t *)dword_7DDD450[7 * v36
                                                                                   + 7
                                                                                   * *(unsigned __int16 *)(LODWORD(v35) + 4)];
                        v41 = *(_DWORD *)(v40 + 24);
                        igi2_frame.v88 = v39;
                        if ( (unsigned int)igi2_frame.ptVertex | v41 | v39
                          && (*(_DWORD *)(v40 + 24) & igi2_frame.v88 & (unsigned int)igi2_frame.ptVertex) == 0
                          && (v38[2] < (double)igi2_frame.vClosestZ
                           || *(float *)(v40 + 8) < (double)igi2_frame.vClosestZ
                           || v37[2] < (double)igi2_frame.vClosestZ) )
                        {
                          qmemcpy(&igi2_frame.v72, v37, sizeof(igi2_frame.v72));
                          qmemcpy(&igi2_frame.v71, (void *)v40, sizeof(igi2_frame.v71));
                          qmemcpy(&igi2_frame.v70, v38, sizeof(igi2_frame.v70));
                          RigidDynCubeObj_CheckTriangle(igi2_frame.v70, igi2_frame.v71, igi2_frame.v72, &igi2_frame.vClosestZ, igi2_frame.vClipZ);
                          v35 = igi2_frame.vRadius;
                        }
                        LODWORD(v35) += 6;
                        v33 = ++igi2_frame.iFace < igi2_frame.ptFaceGroup->nNumFaces;
                        igi2_frame.vRadius = v35;
                      }
                      while ( v33 );
                    }
                    ++igi2_frame.ptFaceGroup;
                  }
                  while ( igi2_frame.ptFaceGroup < igi2_frame.ptEnd );
                }
              }
              *((float *)pxContext + 2) = igi2_frame.vClosestZ;
              v15 = (float *)pxContext;
            }
            ptNext = ptQTask[3].ptNext;
            if ( ptNext )
            {
              ptHead = (int)ptNext->tQTaskChildren.ptHead;
              if ( *(_DWORD *)ptHead )
              {
                if ( ptHead )
                {
                  v65 = QTask_nProtectedQTaskStackOffset;
                  do
                  {
                    if ( *(_DWORD *)ptHead )
                      v66 = **(_DWORD **)ptHead != 0 ? *(struct QTask_s **)ptHead : nullptr;
                    else
                      v66 = nullptr;
                    v67 = QCube_eGetClosestVertexQTaskEvent;
                    QTask_atProtectedQTaskStack[v65].ptQTask = v66;
                    pfHandler = (void (__cdecl *)(int, float *))QTask_aatQTaskFinalEvent[v67][*(unsigned __int16 *)(ptHead + 36)].pfHandler;
                    v69 = v65 + 1;
                    QTask_nProtectedQTaskStackOffset = v69;
                    if ( pfHandler )
                    {
                      pfHandler(ptHead, v15);
                      v69 = QTask_nProtectedQTaskStackOffset;
                    }
                    ptHead = dword_849C7DC[v69];
                    v65 = v69 - 1;
                    QTask_nProtectedQTaskStackOffset = v65;
                  }
                  while ( ptHead );
                }
              }
            }
          }
        }
      }
    }
  }
}

// source: e/3/pc/pc_rigiddyncubeobj.c:771  [anchor-mhash]
void __cdecl RigidDynCubeObj_CheckTriangle(
        struct MultiMesh_TransformedVertex_t tVertex0,
        struct MultiMesh_TransformedVertex_t tVertex1,
        struct MultiMesh_TransformedVertex_t tVertex2,
        float *pvClosestZ,
        float vClipZ)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct MultiMesh_TransformedVertex_t v118; };
    struct { char igi2_o1[28]; struct MultiMesh_TransformedVertex_t v119; };
    struct { char igi2_o2[56]; struct MultiMesh_TransformedVertex_t v120; };
    struct { char igi2_o3[84]; float *v121; };
    struct { char igi2_o4[88]; float v122; };
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
  BOOL v18; // ebx
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
  int v42; // ecx
  int v43; // edx
  struct MultiMesh_TransformedVertex_t *v44; // eax
  struct MultiMesh_TransformedVertex_t *v45; // edx
  struct MultiMesh_TransformedVertex_t *v46; // esi
  struct MultiMesh_TransformedVertex_t *v47; // ecx
  double v48; // st7
  double v49; // st7
  struct MultiMesh_TransformedVertex_t *v50; // ebx
  struct MultiMesh_TransformedVertex_t *v51; // eax
  struct MultiMesh_TransformedVertex_t *v52; // edx
  struct MultiMesh_TransformedVertex_t *v53; // ecx
  double v54; // st7
  double v55; // st6
  double v56; // rtt
  double vX; // st7
  double v58; // st6
  double v59; // st7
  int v60; // ecx
  int v61; // edx
  struct MultiMesh_TransformedVertex_t *v62; // eax
  struct MultiMesh_TransformedVertex_t *v63; // edx
  struct MultiMesh_TransformedVertex_t *v64; // esi
  struct MultiMesh_TransformedVertex_t *v65; // ecx
  double v66; // st7
  double v67; // st7
  struct MultiMesh_TransformedVertex_t *v68; // ebx
  struct MultiMesh_TransformedVertex_t *v69; // eax
  struct MultiMesh_TransformedVertex_t *v70; // edx
  bool v71; // zf
  double v72; // st7
  double v73; // st6
  double v74; // st7
  double vY; // st7
  double v76; // st7
  double v77; // st6
  int v78; // ecx
  int v79; // edx
  struct MultiMesh_TransformedVertex_t *v80; // eax
  struct MultiMesh_TransformedVertex_t *v81; // edx
  struct MultiMesh_TransformedVertex_t *v82; // esi
  struct MultiMesh_TransformedVertex_t *v83; // ecx
  double v84; // st7
  double v85; // st7
  struct MultiMesh_TransformedVertex_t *v86; // ebx
  struct MultiMesh_TransformedVertex_t *v87; // eax
  struct MultiMesh_TransformedVertex_t *v88; // edx
  double v89; // st7
  double v90; // st6
  double v91; // rt0
  double v92; // st7
  double v93; // st6
  double v94; // st7
  int v95; // ecx
  int v96; // edx
  struct MultiMesh_TransformedVertex_t *v97; // eax
  struct MultiMesh_TransformedVertex_t *v98; // ecx
  struct MultiMesh_TransformedVertex_t *v99; // edx
  struct MultiMesh_TransformedVertex_t *v100; // esi
  double v101; // st7
  double v102; // st6
  double v103; // st7
  double v104; // st6
  struct MultiMesh_TransformedVertex_t *v105; // edx
  struct MultiMesh_TransformedVertex_t *v106; // ebx
  struct MultiMesh_TransformedVertex_t *v107; // eax
  double v108; // st7
  double v109; // st6
  double v110; // st7
  double v111; // st6
  float *v112; // ecx
  double v113; // st7
  double v114; // st6
  double v115; // st6
  float *v116; // ecx
  double v117; // st7

  bOutcode = tVertex1.bOutcode;
  v6 = tVertex2.bOutcode;
  ++dword_7E65FB8;
  v7 = tVertex0.bOutcode;
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
        v7 = tVertex0.bOutcode;
        bOutcode = tVertex1.bOutcode;
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
        v8 = LOBYTE(tVertex2.bOutcode) | LOBYTE(tVertex1.bOutcode) | LOBYTE(tVertex0.bOutcode);
        v9 = tVertex2.bOutcode & tVertex1.bOutcode & tVertex0.bOutcode;
        qmemcpy(&igi2_frame.v120, v27, sizeof(igi2_frame.v120));
        qmemcpy(&igi2_frame.v119, &igi2_frame.tClipped1, sizeof(igi2_frame.v119));
        qmemcpy(&igi2_frame.v118, igi2_frame.ptOK1, sizeof(igi2_frame.v118));
        RigidDynCubeObj_CheckTriangle(igi2_frame.v118, igi2_frame.v119, igi2_frame.v120, pvClosestZ, vClipZ);
        v7 = tVertex0.bOutcode;
        bOutcode = tVertex1.bOutcode;
        v6 = tVertex2.bOutcode;
      }
    }
    if ( !v9 )
    {
      if ( (v8 & 1) != 0 )
      {
        v42 = v7 & 1;
        v43 = bOutcode & 1;
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
          v7 = tVertex0.bOutcode;
          bOutcode = tVertex1.bOutcode;
          v6 = tVertex2.bOutcode;
          v8 = LOBYTE(tVertex2.bOutcode) | LOBYTE(tVertex1.bOutcode) | LOBYTE(tVertex0.bOutcode);
          v9 = tVertex2.bOutcode & tVertex1.bOutcode & tVertex0.bOutcode;
        }
        else
        {
          if ( v42 )
          {
            v50 = &tVertex0;
            v51 = &tVertex1;
            v52 = &tVertex2;
            igi2_frame.ptOK1 = &tVertex0;
          }
          else
          {
            if ( v43 )
            {
              v51 = &tVertex2;
              v52 = &tVertex0;
              v53 = &tVertex1;
            }
            else
            {
              v51 = &tVertex0;
              v52 = &tVertex1;
              v53 = &tVertex2;
            }
            igi2_frame.ptOK1 = v53;
            v50 = v53;
          }
          v54 = v50->tProjected.vX - v51->tProjected.vX;
          v55 = RenderContext_tActiveRenderContext.tDisplayAreaMin.vX - v51->tProjected.vX;
          qmemcpy(&igi2_frame.tClipped1, v50, sizeof(igi2_frame.tClipped1));
          v56 = v55 / v54;
          v50->tProjected.vX = v54 * v56 + v51->tProjected.vX;
          v50->tProjected.vY = (v50->tProjected.vY - v51->tProjected.vY) * v56 + v51->tProjected.vY;
          v50->tProjected.vZ = (v50->tProjected.vZ - v51->tProjected.vZ) * v56 + v51->tProjected.vZ;
          vX = igi2_frame.tClipped1.tProjected.vX;
          v50->bOutcode = 2
                        * ((v50->tProjected.vY < (double)RenderContext_tActiveRenderContext.tDisplayAreaMin.vY)
                         | (2
                          * ((v50->tProjected.vX > (double)RenderContext_tActiveRenderContext.tDisplayAreaMax.vX)
                           | (2 * (v50->tProjected.vY > (double)RenderContext_tActiveRenderContext.tDisplayAreaMax.vY)))));
          v58 = vX - v52->tProjected.vX;
          v59 = (RenderContext_tActiveRenderContext.tDisplayAreaMin.vX - v52->tProjected.vX) / v58;
          igi2_frame.tClipped1.tProjected.vX = v58 * v59 + v52->tProjected.vX;
          igi2_frame.tClipped1.tProjected.vY = (igi2_frame.tClipped1.tProjected.vY - v52->tProjected.vY) * v59 + v52->tProjected.vY;
          igi2_frame.tClipped1.tProjected.vZ = (igi2_frame.tClipped1.tProjected.vZ - v52->tProjected.vZ) * v59 + v52->tProjected.vZ;
          igi2_frame.tClipped1.bOutcode = 2
                             * ((igi2_frame.tClipped1.tProjected.vY < (double)RenderContext_tActiveRenderContext.tDisplayAreaMin.vY)
                              | (2
                               * ((igi2_frame.tClipped1.tProjected.vX > (double)RenderContext_tActiveRenderContext.tDisplayAreaMax.vX)
                                | (2
                                 * (igi2_frame.tClipped1.tProjected.vY > (double)RenderContext_tActiveRenderContext.tDisplayAreaMax.vY)))));
          v8 = LOBYTE(tVertex2.bOutcode) | LOBYTE(tVertex1.bOutcode) | LOBYTE(tVertex0.bOutcode);
          v9 = tVertex2.bOutcode & tVertex1.bOutcode & tVertex0.bOutcode;
          qmemcpy(&igi2_frame.v120, igi2_frame.ptOK1, sizeof(igi2_frame.v120));
          qmemcpy(&igi2_frame.v119, &igi2_frame.tClipped1, sizeof(igi2_frame.v119));
          qmemcpy(&igi2_frame.v118, v52, sizeof(igi2_frame.v118));
          RigidDynCubeObj_CheckTriangle(igi2_frame.v118, igi2_frame.v119, igi2_frame.v120, pvClosestZ, vClipZ);
          v7 = tVertex0.bOutcode;
          bOutcode = tVertex1.bOutcode;
          v6 = tVertex2.bOutcode;
        }
      }
      if ( !v9 )
      {
        if ( (v8 & 2) != 0 )
        {
          v60 = v7 & 2;
          v61 = bOutcode & 2;
          if ( ((v61 + v60 + (v6 & 2)) & 0xFFFFFFFE) == 4 )
          {
            if ( v60 )
            {
              if ( v61 )
              {
                v62 = &tVertex2;
                v63 = &tVertex2;
                v64 = &tVertex0;
                v65 = &tVertex1;
              }
              else
              {
                v62 = &tVertex1;
                v63 = &tVertex1;
                v64 = &tVertex2;
                v65 = &tVertex0;
              }
            }
            else
            {
              v62 = &tVertex0;
              v63 = &tVertex0;
              v64 = &tVertex1;
              v65 = &tVertex2;
            }
            v66 = (RenderContext_tActiveRenderContext.tDisplayAreaMin.vY - v62->tProjected.vY)
                / (v64->tProjected.vY - v62->tProjected.vY);
            v64->tProjected.vX = (v64->tProjected.vX - v62->tProjected.vX) * v66 + v62->tProjected.vX;
            v64->tProjected.vY = (v64->tProjected.vY - v62->tProjected.vY) * v66 + v62->tProjected.vY;
            v64->tProjected.vZ = (v64->tProjected.vZ - v62->tProjected.vZ) * v66 + v62->tProjected.vZ;
            v64->bOutcode = 4
                          * ((v64->tProjected.vX > (double)RenderContext_tActiveRenderContext.tDisplayAreaMax.vX)
                           | (2 * (v64->tProjected.vY > (double)RenderContext_tActiveRenderContext.tDisplayAreaMax.vY)));
            v67 = (RenderContext_tActiveRenderContext.tDisplayAreaMin.vY - v63->tProjected.vY)
                / (v65->tProjected.vY - v63->tProjected.vY);
            v65->tProjected.vX = (v65->tProjected.vX - v63->tProjected.vX) * v67 + v63->tProjected.vX;
            v65->tProjected.vY = (v65->tProjected.vY - v63->tProjected.vY) * v67 + v63->tProjected.vY;
            v65->tProjected.vZ = (v65->tProjected.vZ - v63->tProjected.vZ) * v67 + v63->tProjected.vZ;
            v65->bOutcode = 4
                          * ((v65->tProjected.vX > (double)RenderContext_tActiveRenderContext.tDisplayAreaMax.vX)
                           | (2 * (v65->tProjected.vY > (double)RenderContext_tActiveRenderContext.tDisplayAreaMax.vY)));
            v7 = tVertex0.bOutcode;
            bOutcode = tVertex1.bOutcode;
            v6 = tVertex2.bOutcode;
            v8 = LOBYTE(tVertex2.bOutcode) | LOBYTE(tVertex1.bOutcode) | LOBYTE(tVertex0.bOutcode);
            v9 = tVertex2.bOutcode & tVertex1.bOutcode & tVertex0.bOutcode;
          }
          else
          {
            if ( v60 )
            {
              v68 = &tVertex2;
              v69 = &tVertex1;
              igi2_frame.ptOK1 = &tVertex2;
              v70 = &tVertex0;
            }
            else
            {
              v71 = v61 == 0;
              v70 = &tVertex1;
              if ( v71 )
              {
                igi2_frame.ptOK1 = &tVertex1;
                v69 = &tVertex0;
                v70 = &tVertex2;
              }
              else
              {
                v69 = &tVertex2;
                igi2_frame.ptOK1 = &tVertex0;
              }
              v68 = igi2_frame.ptOK1;
            }
            v72 = RenderContext_tActiveRenderContext.tDisplayAreaMin.vY - v69->tProjected.vY;
            v73 = v70->tProjected.vY - v69->tProjected.vY;
            qmemcpy(&igi2_frame.tClipped1, v70, sizeof(igi2_frame.tClipped1));
            v74 = v72 / v73;
            v70->tProjected.vX = (v70->tProjected.vX - v69->tProjected.vX) * v74 + v69->tProjected.vX;
            v70->tProjected.vY = (v70->tProjected.vY - v69->tProjected.vY) * v74 + v69->tProjected.vY;
            v70->tProjected.vZ = (v70->tProjected.vZ - v69->tProjected.vZ) * v74 + v69->tProjected.vZ;
            vY = igi2_frame.tClipped1.tProjected.vY;
            v70->bOutcode = 4
                          * ((v70->tProjected.vX > (double)RenderContext_tActiveRenderContext.tDisplayAreaMax.vX)
                           | (2 * (v70->tProjected.vY > (double)RenderContext_tActiveRenderContext.tDisplayAreaMax.vY)));
            v76 = vY - v68->tProjected.vY;
            v77 = (RenderContext_tActiveRenderContext.tDisplayAreaMin.vY - v68->tProjected.vY) / v76;
            igi2_frame.tClipped1.tProjected.vX = (igi2_frame.tClipped1.tProjected.vX - v68->tProjected.vX) * v77 + v68->tProjected.vX;
            igi2_frame.tClipped1.tProjected.vY = v76 * v77 + v68->tProjected.vY;
            igi2_frame.tClipped1.tProjected.vZ = (igi2_frame.tClipped1.tProjected.vZ - v68->tProjected.vZ) * v77 + v68->tProjected.vZ;
            igi2_frame.tClipped1.bOutcode = 4
                               * ((igi2_frame.tClipped1.tProjected.vX > (double)RenderContext_tActiveRenderContext.tDisplayAreaMax.vX)
                                | (2
                                 * (igi2_frame.tClipped1.tProjected.vY > (double)RenderContext_tActiveRenderContext.tDisplayAreaMax.vY)));
            v8 = LOBYTE(tVertex2.bOutcode) | LOBYTE(tVertex1.bOutcode) | LOBYTE(tVertex0.bOutcode);
            v9 = tVertex2.bOutcode & tVertex1.bOutcode & tVertex0.bOutcode;
            qmemcpy(&igi2_frame.v120, v70, sizeof(igi2_frame.v120));
            qmemcpy(&igi2_frame.v119, &igi2_frame.tClipped1, sizeof(igi2_frame.v119));
            qmemcpy(&igi2_frame.v118, igi2_frame.ptOK1, sizeof(igi2_frame.v118));
            RigidDynCubeObj_CheckTriangle(igi2_frame.v118, igi2_frame.v119, igi2_frame.v120, pvClosestZ, vClipZ);
            v7 = tVertex0.bOutcode;
            bOutcode = tVertex1.bOutcode;
            v6 = tVertex2.bOutcode;
          }
        }
        if ( !v9 )
        {
          if ( (v8 & 4) != 0 )
          {
            v78 = v7 & 4;
            v79 = bOutcode & 4;
            if ( ((v79 + v78 + (v6 & 4)) & 0xFFFFFFFC) == 8 )
            {
              if ( v78 )
              {
                if ( v79 )
                {
                  v80 = &tVertex2;
                  v81 = &tVertex2;
                  v82 = &tVertex0;
                  v83 = &tVertex1;
                }
                else
                {
                  v80 = &tVertex1;
                  v81 = &tVertex1;
                  v82 = &tVertex2;
                  v83 = &tVertex0;
                }
              }
              else
              {
                v80 = &tVertex0;
                v81 = &tVertex0;
                v82 = &tVertex1;
                v83 = &tVertex2;
              }
              v84 = (RenderContext_tActiveRenderContext.tDisplayAreaMax.vX - v80->tProjected.vX)
                  / (v82->tProjected.vX - v80->tProjected.vX);
              v82->tProjected.vX = (v82->tProjected.vX - v80->tProjected.vX) * v84 + v80->tProjected.vX;
              v82->tProjected.vY = (v82->tProjected.vY - v80->tProjected.vY) * v84 + v80->tProjected.vY;
              v82->tProjected.vZ = (v82->tProjected.vZ - v80->tProjected.vZ) * v84 + v80->tProjected.vZ;
              v82->bOutcode = 8 * (v82->tProjected.vY > (double)RenderContext_tActiveRenderContext.tDisplayAreaMax.vY);
              v85 = (RenderContext_tActiveRenderContext.tDisplayAreaMax.vX - v81->tProjected.vX)
                  / (v83->tProjected.vX - v81->tProjected.vX);
              v83->tProjected.vX = (v83->tProjected.vX - v81->tProjected.vX) * v85 + v81->tProjected.vX;
              v83->tProjected.vY = (v83->tProjected.vY - v81->tProjected.vY) * v85 + v81->tProjected.vY;
              v83->tProjected.vZ = (v83->tProjected.vZ - v81->tProjected.vZ) * v85 + v81->tProjected.vZ;
              v83->bOutcode = 8 * (v83->tProjected.vY > (double)RenderContext_tActiveRenderContext.tDisplayAreaMax.vY);
              v7 = tVertex0.bOutcode;
              bOutcode = tVertex1.bOutcode;
              v6 = tVertex2.bOutcode;
              v8 = LOBYTE(tVertex2.bOutcode) | LOBYTE(tVertex1.bOutcode) | LOBYTE(tVertex0.bOutcode);
              v9 = tVertex2.bOutcode & tVertex1.bOutcode & tVertex0.bOutcode;
            }
            else
            {
              if ( v78 )
              {
                v86 = &tVertex2;
                v87 = &tVertex1;
                igi2_frame.ptOK1 = &tVertex2;
                v88 = &tVertex0;
              }
              else
              {
                v71 = v79 == 0;
                v88 = &tVertex1;
                if ( v71 )
                {
                  igi2_frame.ptOK1 = &tVertex1;
                  v87 = &tVertex0;
                  v88 = &tVertex2;
                }
                else
                {
                  v87 = &tVertex2;
                  igi2_frame.ptOK1 = &tVertex0;
                }
                v86 = igi2_frame.ptOK1;
              }
              v89 = v88->tProjected.vX - v87->tProjected.vX;
              v90 = RenderContext_tActiveRenderContext.tDisplayAreaMax.vX - v87->tProjected.vX;
              qmemcpy(&igi2_frame.tClipped1, v88, sizeof(igi2_frame.tClipped1));
              v91 = v90 / v89;
              v88->tProjected.vX = v89 * v91 + v87->tProjected.vX;
              v88->tProjected.vY = (v88->tProjected.vY - v87->tProjected.vY) * v91 + v87->tProjected.vY;
              v88->tProjected.vZ = (v88->tProjected.vZ - v87->tProjected.vZ) * v91 + v87->tProjected.vZ;
              v92 = igi2_frame.tClipped1.tProjected.vX;
              v88->bOutcode = 8 * (v88->tProjected.vY > (double)RenderContext_tActiveRenderContext.tDisplayAreaMax.vY);
              v93 = v92 - v86->tProjected.vX;
              v94 = (RenderContext_tActiveRenderContext.tDisplayAreaMax.vX - v86->tProjected.vX) / v93;
              igi2_frame.tClipped1.tProjected.vX = v93 * v94 + v86->tProjected.vX;
              igi2_frame.tClipped1.tProjected.vY = (igi2_frame.tClipped1.tProjected.vY - v86->tProjected.vY) * v94 + v86->tProjected.vY;
              igi2_frame.tClipped1.tProjected.vZ = (igi2_frame.tClipped1.tProjected.vZ - v86->tProjected.vZ) * v94 + v86->tProjected.vZ;
              igi2_frame.tClipped1.bOutcode = 8
                                 * (igi2_frame.tClipped1.tProjected.vY > (double)RenderContext_tActiveRenderContext.tDisplayAreaMax.vY);
              v8 = LOBYTE(tVertex2.bOutcode) | LOBYTE(tVertex1.bOutcode) | LOBYTE(tVertex0.bOutcode);
              v9 = tVertex2.bOutcode & tVertex1.bOutcode & tVertex0.bOutcode;
              qmemcpy(&igi2_frame.v120, v88, sizeof(igi2_frame.v120));
              qmemcpy(&igi2_frame.v119, &igi2_frame.tClipped1, sizeof(igi2_frame.v119));
              qmemcpy(&igi2_frame.v118, igi2_frame.ptOK1, sizeof(igi2_frame.v118));
              RigidDynCubeObj_CheckTriangle(igi2_frame.v118, igi2_frame.v119, igi2_frame.v120, pvClosestZ, vClipZ);
              v7 = tVertex0.bOutcode;
              bOutcode = tVertex1.bOutcode;
              v6 = tVertex2.bOutcode;
            }
          }
          if ( !v9 )
          {
            if ( (v8 & 8) != 0 )
            {
              v95 = v7 & 8;
              v96 = bOutcode & 8;
              if ( ((v96 + v95 + (v6 & 8)) & 0xFFFFFFF8) == 0x10 )
              {
                if ( v95 )
                {
                  if ( v96 )
                  {
                    v97 = &tVertex2;
                    v98 = &tVertex2;
                    v99 = &tVertex0;
                    v100 = &tVertex1;
                  }
                  else
                  {
                    v97 = &tVertex1;
                    v98 = &tVertex1;
                    v99 = &tVertex2;
                    v100 = &tVertex0;
                  }
                }
                else
                {
                  v97 = &tVertex0;
                  v98 = &tVertex0;
                  v99 = &tVertex1;
                  v100 = &tVertex2;
                }
                v101 = (RenderContext_tActiveRenderContext.tDisplayAreaMax.vY - v97->tProjected.vY)
                     / (v99->tProjected.vY - v97->tProjected.vY);
                v99->tProjected.vX = (v99->tProjected.vX - v97->tProjected.vX) * v101 + v97->tProjected.vX;
                v99->tProjected.vY = (v99->tProjected.vY - v97->tProjected.vY) * v101 + v97->tProjected.vY;
                v102 = (v99->tProjected.vZ - v97->tProjected.vZ) * v101 + v97->tProjected.vZ;
                v99->bOutcode = 0;
                v99->tProjected.vZ = v102;
                v103 = (RenderContext_tActiveRenderContext.tDisplayAreaMax.vY - v98->tProjected.vY)
                     / (v100->tProjected.vY - v98->tProjected.vY);
                v100->tProjected.vX = (v100->tProjected.vX - v98->tProjected.vX) * v103 + v98->tProjected.vX;
                v100->tProjected.vY = (v100->tProjected.vY - v98->tProjected.vY) * v103 + v98->tProjected.vY;
                v104 = (v100->tProjected.vZ - v98->tProjected.vZ) * v103 + v98->tProjected.vZ;
                v100->bOutcode = 0;
                v100->tProjected.vZ = v104;
                v9 = tVertex2.bOutcode & tVertex1.bOutcode & tVertex0.bOutcode;
              }
              else
              {
                if ( v95 )
                {
                  v105 = &tVertex1;
                  v106 = &tVertex2;
                  v107 = &tVertex0;
                }
                else if ( v96 )
                {
                  v105 = &tVertex2;
                  v106 = &tVertex0;
                  v107 = &tVertex1;
                }
                else
                {
                  v105 = &tVertex0;
                  v106 = &tVertex1;
                  v107 = &tVertex2;
                }
                v108 = RenderContext_tActiveRenderContext.tDisplayAreaMax.vY - v105->tProjected.vY;
                v109 = v107->tProjected.vY - v105->tProjected.vY;
                qmemcpy(&igi2_frame.tClipped1, v107, sizeof(igi2_frame.tClipped1));
                v110 = v108 / v109;
                igi2_frame.tClipped1.bOutcode = 0;
                v107->tProjected.vX = (v107->tProjected.vX - v105->tProjected.vX) * v110 + v105->tProjected.vX;
                v107->tProjected.vY = (v107->tProjected.vY - v105->tProjected.vY) * v110 + v105->tProjected.vY;
                v111 = (v107->tProjected.vZ - v105->tProjected.vZ) * v110 + v105->tProjected.vZ;
                v107->bOutcode = 0;
                v112 = pvClosestZ;
                v107->tProjected.vZ = v111;
                v113 = igi2_frame.tClipped1.tProjected.vY - v106->tProjected.vY;
                v9 = tVertex2.bOutcode & tVertex1.bOutcode & tVertex0.bOutcode;
                v114 = RenderContext_tActiveRenderContext.tDisplayAreaMax.vY - v106->tProjected.vY;
                igi2_frame.v122 = vClipZ;
                igi2_frame.v121 = v112;
                v115 = v114 / v113;
                qmemcpy(&igi2_frame.v120, v107, sizeof(igi2_frame.v120));
                igi2_frame.tClipped1.tProjected.vX = (igi2_frame.tClipped1.tProjected.vX - v106->tProjected.vX) * v115 + v106->tProjected.vX;
                igi2_frame.tClipped1.tProjected.vY = v113 * v115 + v106->tProjected.vY;
                igi2_frame.tClipped1.tProjected.vZ = (igi2_frame.tClipped1.tProjected.vZ - v106->tProjected.vZ) * v115 + v106->tProjected.vZ;
                qmemcpy(&igi2_frame.v119, &igi2_frame.tClipped1, sizeof(igi2_frame.v119));
                qmemcpy(&igi2_frame.v118, v106, sizeof(igi2_frame.v118));
                RigidDynCubeObj_CheckTriangle(igi2_frame.v118, igi2_frame.v119, igi2_frame.v120, v112, vClipZ);
              }
            }
            if ( !v9 )
            {
              v116 = pvClosestZ;
              v117 = 1.0 / tVertex0.tProjected.vZ;
              tVertex1.tProjected.vZ = 1.0 / tVertex1.tProjected.vZ;
              tVertex2.tProjected.vZ = 1.0 / tVertex2.tProjected.vZ;
              if ( v117 < *pvClosestZ )
                *pvClosestZ = v117;
              if ( tVertex1.tProjected.vZ < (double)*v116 )
                *v116 = tVertex1.tProjected.vZ;
              if ( tVertex2.tProjected.vZ < (double)*v116 )
                *v116 = tVertex2.tProjected.vZ;
            }
          }
        }
      }
    }
  }
  --dword_7E65FB8;
}

// source: e/3/pc/pc_rigiddyncubeobj.c:1639  [anchor-caller]
void __cdecl RigidDynCubeObj_Open()
{
  unsigned __int16 v0; // si

  RigidDynCubeObj_GenericOpen();
  v0 = RigidDynCubeObj_eQTaskType;
  QTask_LinkQTaskEventHandlerFn(
    RigidDynCubeObj_eQTaskType,
    QCube_eGetClosestVertexQTaskEvent,
    RigidDynCubeObj_GetClosestVertex);
  QTask_LinkQTaskEventHandlerFn(v0, SLOWORD(ShadowVolume_vIntensity), RigidDynCubeObj_GetObjectBoundingSphereHandler);
  QTask_LinkQTaskEventHandlerFn(v0, Envmap_eDrawQTaskEvent, RigidDynCubeObj_DrawEnvmapHandler);
  QTask_LinkQTaskEventHandlerFn(v0, Envmap_eEnumerateQTaskEvent, RigidDynCubeObj_EnumerateEnvmapHandler);
}

// source: e/3/pc/pc_rigiddyncubeobj.c:1659  [size]
void __cdecl RigidDynCubeObj_Close()
{
  QTask_FreeGroup((unsigned int)&TerrainRender_atEdge[4623].iSplitVertex);
  QTask_DeleteQTaskType(RigidDynCubeObj_eQTaskType);
  RigidDynCubeObj_eQTaskType = 512;
  QTask_DeleteQTaskEvent(RigidDynCubeObj_eRenderStartEvent);
  RigidDynCubeObj_eRenderStartEvent = 512;
}
