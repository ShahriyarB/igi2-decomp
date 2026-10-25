/* h/2/dirlighttask.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: h/2/dirlighttask.c:86  [size]
void __cdecl DirlightQTask_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  char v2; // cl
  struct QObjectVector_s *v3; // eax
  unsigned int *p_nAllocated; // edi
  struct QObjectVector_s *v5; // ebx
  struct QReference_s *v6; // ecx

  ptQTask[2].ptParent = (struct QTask_s *)World_ptActiveWorld;
  memset(&ptQTask[1], 0, 0x48u);
  v2 = 1;
  ptQTask[2].tQTaskRefList.ptTail = (struct QReference_s *)5;
  *(_DWORD *)&ptQTask[2].eQTaskType = 0;
  ptQTask[3].ptNext = nullptr;
  ptQTask[3].ptPrev = (struct QTask_s *)1065353216;
  ptQTask[3].tQTaskChildren.ptHead = nullptr;
  ptQTask[3].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[3].tQTaskChildren.ptTail = nullptr;
  ptQTask[3].tQTaskRefList.ptHead = nullptr;
  ptQTask[3].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[3].tQTaskRefList.ptTail = nullptr;
  ptQTask[3].ptParent = nullptr;
  ptQTask[3].eQTaskType = 256;
  ptQTask[3].isInMemPool = 1;
  if ( (~LOBYTE(Direct3D_tCaps.StencilCaps) & 0x1D) != 0
    || Direct3D_tActiveParameters.AutoDepthStencilFormat != D3DFMT_D24S8
    && Direct3D_tActiveParameters.AutoDepthStencilFormat != D3DFMT_D24X4S4 )
  {
    v2 = 0;
  }
  ptQTask[6].tQTaskRefList.ptHead = nullptr;
  *(&ptQTask[3].isInMemPool + 1) = v2;
  ptQTask[4].ptPrev = (struct QTask_s *)1048576000;
  memset(&ptQTask[4].tQTaskRefList.ptMiddle, 0, 0x20u);
  strcpy((char *)&ptQTask[4].tQTaskRefList.ptMiddle, "sun.tex");
  memset(&ptQTask[5].tQTaskChildren.ptTail, 0, 0x2Cu);
  v3 = DirlightQTask_tDirlightPool;
  ptQTask[6].tQTaskRefList.ptMiddle = (struct QReference_s *)1107296256;
  p_nAllocated = &v3->nAllocated;
  v5 = v3;
  if ( v3->nAllocated == v3->nSize )
    QObjectVector_Realloc(v3, v3->nReallocSize);
  v6 = (struct QReference_s *)v5->papxElement[(*p_nAllocated)++];
  ptQTask[4].tQTaskRefList.ptHead = v6;
  v6->ptNext = (struct QReference_s *)ptQTask;
}

// source: h/2/dirlighttask.c:124  [size]
void __cdecl DirlightQTask_RunHandler(struct QTask_s *ptQTask)
{
  ;
}

// source: h/2/dirlighttask.c:139  [anchor-mhash]
void __cdecl DirlightQTask_DeleteHandler(struct QTask_s *ptQTask)
{
  _DWORD *p_ptTail; // edi
  struct QTask_s *ptParent; // ecx
  struct QTask_s *ptMiddle; // eax
  struct QTask_s *ptTail; // eax
  struct QTask_s *v5; // esi

  if ( ptQTask[6].tQTaskRefList.ptHead )
  {
    p_ptTail = &ptQTask[5].tQTaskChildren.ptTail;
    if ( AppContext_tAppContext.isMainMenu == false )
      RenderMode_atRenderMode[*p_ptTail].apfRenderModeMethod[Texture_eDeAllocTextureMethod](&ptQTask[5].tQTaskChildren.ptTail);
    memset(p_ptTail, 0, 0x2Cu);
    ptParent = ptQTask[2].ptParent;
    ptQTask[6].tQTaskRefList.ptHead = nullptr;
    ptMiddle = ptQTask[2].tQTaskChildren.ptMiddle;
    if ( ptMiddle )
      ptMiddle[2].tQTaskChildren.ptTail = ptQTask[2].tQTaskChildren.ptTail;
    else
      ptParent[2].ptPrev = ptQTask[2].tQTaskChildren.ptTail;
    ptTail = ptQTask[2].tQTaskChildren.ptTail;
    if ( ptTail )
      ptTail[2].tQTaskChildren.ptMiddle = ptQTask[2].tQTaskChildren.ptMiddle;
  }
  v5 = ptQTask[3].ptParent;
  if ( v5 )
    Lightsource_DeleteDirlight((struct Dirlight_s *)v5);
  QObjectVector_RemoveElement(
    DirlightQTask_tDirlightPool,
    *(_DWORD *)((char *)ptQTask[4].tQTaskRefList.ptHead + DirlightQTask_tDirlightPool->nElementSize - 4));
  SkyDome_ptDirlight = nullptr;
}

// source: h/2/dirlighttask.c:172  [size]
void __cdecl DirlightQTask_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = DirlightQTask_ptParameterList;
}

// source: h/2/dirlighttask.c:189  [anchor-strings]
void __cdecl DirlightQTask_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  BOOL v2; // eax
  double v3; // st7
  unsigned __int16 v4; // dx
  struct QTask_s *i; // edi
  _DWORD *p_ptTail; // edi
  struct QTask_s *ptMiddle; // eax
  struct QTask_s *ptParent; // ecx
  struct QTask_s *ptTail; // eax
  struct File_s *v10; // eax
  struct QTask_s *v11; // eax
  struct QTask_s *ptPrev; // ecx
  struct QTask_s *v13; // ecx
  char zFilename[256]; // [esp+Ch] [ebp-100h] BYREF

  v2 = GfxOptions_tActiveOptions.isStencilShadows && *(&ptQTask[3].isInMemPool + 1);
  v3 = *(float *)&ptQTask[4].ptPrev;
  ShadowVolume_isEnabled = v2
                        && (~LOBYTE(Direct3D_tCaps.StencilCaps) & 0x1D) == 0
                        && (Direct3D_tActiveParameters.AutoDepthStencilFormat == D3DFMT_D24S8
                         || Direct3D_tActiveParameters.AutoDepthStencilFormat == D3DFMT_D24X4S4);
  v4 = DirlightKeyframeQTask_eQTaskType;
  *(float *)&ShadowVolume_nUseAsm = v3;
  ptQTask[4].tQTaskChildren.ptTail = (struct QTask_s *)-8388609;
  ptQTask[4].tQTaskChildren.ptMiddle = (struct QTask_s *)-8388609;
  ptQTask[4].tQTaskChildren.ptHead = (struct QTask_s *)2139095039;
  for ( i = QTask_GetFirstChildOfType(ptQTask, v4); i; i = QTask_GetNextSiblingOfType(i, v4) )
  {
    if ( *(float *)&i[2].tQTaskChildren.ptHead > (double)*(float *)&ptQTask[4].tQTaskChildren.ptMiddle )
      ptQTask[4].tQTaskChildren.ptMiddle = i[2].tQTaskChildren.ptHead;
    if ( *(float *)&i[2].tQTaskChildren.ptHead < (double)*(float *)&ptQTask[4].tQTaskChildren.ptHead )
      ptQTask[4].tQTaskChildren.ptHead = i[2].tQTaskChildren.ptHead;
  }
  DirlightQTask_SetTime(0.0);
  sprintf(zFilename, "LOCAL:common/textures/%s", (char *)&ptQTask[4].tQTaskRefList.ptMiddle);
  if ( ptQTask[6].tQTaskRefList.ptHead )
  {
    p_ptTail = &ptQTask[5].tQTaskChildren.ptTail;
    if ( AppContext_tAppContext.isMainMenu == false )
      RenderMode_atRenderMode[*p_ptTail].apfRenderModeMethod[Texture_eDeAllocTextureMethod](&ptQTask[5].tQTaskChildren.ptTail);
    memset(p_ptTail, 0, 0x2Cu);
    ptMiddle = ptQTask[2].tQTaskChildren.ptMiddle;
    ptParent = ptQTask[2].ptParent;
    ptQTask[6].tQTaskRefList.ptHead = nullptr;
    if ( ptMiddle )
      ptMiddle[2].tQTaskChildren.ptTail = ptQTask[2].tQTaskChildren.ptTail;
    else
      ptParent[2].ptPrev = ptQTask[2].tQTaskChildren.ptTail;
    ptTail = ptQTask[2].tQTaskChildren.ptTail;
    if ( ptTail )
      ptTail[2].tQTaskChildren.ptMiddle = ptQTask[2].tQTaskChildren.ptMiddle;
  }
  if ( Resource_IsLoadedInternal(zFilename, nullptr) == false )
  {
    v10 = File_New(zFilename, "r");
    if ( !v10 )
      return;
    if ( v10 == &File_tDummyAsyncFile )
      File_tDummyAsyncFile.isAsync = false;
    else
      File_atDevice[v10->eDeviceID].pfDelete(v10->eDeviceID, v10);
  }
  Texture_Load((struct TexInfo_s *)&ptQTask[5].tQTaskChildren.ptTail, nullptr, zFilename);
  v11 = ptQTask[2].ptParent;
  ptQTask[6].tQTaskRefList.ptHead = (struct QReference_s *)1;
  ptPrev = v11[2].ptPrev;
  if ( ptPrev )
  {
    ptPrev[2].tQTaskChildren.ptMiddle = ptQTask;
    v11[2].ptPrev[2].tQTaskChildren.ptMiddle[2].tQTaskChildren.ptTail = v11[2].ptPrev;
    v13 = v11[2].ptPrev[2].tQTaskChildren.ptMiddle;
    v11[2].ptPrev = v13;
    v13[2].tQTaskChildren.ptMiddle = nullptr;
  }
  else
  {
    v11[2].ptPrev = ptQTask;
    ptQTask[2].tQTaskChildren.ptTail = nullptr;
    v11[2].ptPrev[2].tQTaskChildren.ptMiddle = nullptr;
  }
}

// source: h/2/dirlighttask.c:252  [size]
void __cdecl DirlightKeyframeQTask_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ptQTask[2].ptPrev = nullptr;
  ptQTask[2].tQTaskChildren.ptHead = nullptr;
  ptQTask[1].tQTaskRefList.ptHead = (struct QReference_s *)1065353216;
  ptQTask[1].tQTaskRefList.ptMiddle = (struct QReference_s *)1065353216;
  ptQTask[1].tQTaskRefList.ptTail = (struct QReference_s *)1065353216;
  ptQTask[1].ptParent = nullptr;
  *(_DWORD *)&ptQTask[1].eQTaskType = 0;
  ptQTask[2].ptNext = nullptr;
  ptQTask[1].tQTaskChildren.ptHead = nullptr;
  ptQTask[1].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[1].tQTaskChildren.ptTail = (struct QTask_s *)1065353216;
}

// source: h/2/dirlighttask.c:273  [anchor-mhash]
void __cdecl DirlightKeyframeQTask_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { float vAlpha; };
    struct { char igi2_o1[4]; float vBeta; };
    struct { char igi2_o2[20]; struct real32x3_t Real32x3_Rotate_tTemp; };
    struct { char igi2_o3[32]; struct real32x9_t tTempMatrix; };
    char igi2_extent[76];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  double v2; // st7
  double vZ; // st7
  struct QTask_s *ptParent; // eax
  double v5; // st7
  double v6; // st7
  unsigned __int16 eQTaskType; // cx
  struct QObjectVector_s *v8; // eax
  signed int i; // ebx
  int v10; // esi
  int v11; // eax
  _DWORD *v12; // eax
  _DWORD *v13; // eax
  _DWORD *v14; // ecx
  float v15; // edi
  void (__cdecl *v16)(void *); // eax
  struct Dirlight_s *v17; // eax
  int v18; // esi

  if ( !DirlightQTask_ptActiveKeyframe )
    DirlightQTask_ptActiveKeyframe = (struct DirlightKeyframeQTask_t *)ptQTask;
  v2 = 6.2831854820251465 - *(float *)&ptQTask[1].ptPrev;
  ptQTask[1].tQTaskChildren.ptHead = (struct QTask_s *)1065353216;
  ptQTask[1].tQTaskChildren.ptMiddle = nullptr;
  igi2_frame.vBeta = v2;
  ptQTask[1].tQTaskChildren.ptTail = nullptr;
  igi2_frame.vAlpha = 6.2831854820251465 - *(float *)&ptQTask[1].ptNext;
  Real32x9_Create(&igi2_frame.tTempMatrix, 0.0, igi2_frame.vAlpha, igi2_frame.vBeta);
  igi2_frame.Real32x3_Rotate_tTemp.vX = (igi2_frame.tTempMatrix.tX.vZ + igi2_frame.tTempMatrix.tX.vY) * 0.0 + igi2_frame.tTempMatrix.tX.vX;
  vZ = igi2_frame.tTempMatrix.tY.vZ;
  ptQTask[1].tQTaskChildren.ptHead = (struct QTask_s *)LODWORD(igi2_frame.Real32x3_Rotate_tTemp.vX);
  ptParent = ptQTask->ptParent;
  igi2_frame.Real32x3_Rotate_tTemp.vY = (vZ + igi2_frame.tTempMatrix.tY.vY) * 0.0 + igi2_frame.tTempMatrix.tY.vX;
  v5 = igi2_frame.tTempMatrix.tZ.vZ;
  ptQTask[1].tQTaskChildren.ptMiddle = (struct QTask_s *)LODWORD(igi2_frame.Real32x3_Rotate_tTemp.vY);
  igi2_frame.Real32x3_Rotate_tTemp.vZ = (v5 + igi2_frame.tTempMatrix.tZ.vY) * 0.0 + igi2_frame.tTempMatrix.tZ.vX;
  v6 = *(float *)&ptQTask[2].ptPrev;
  ptQTask[1].tQTaskChildren.ptTail = (struct QTask_s *)LODWORD(igi2_frame.Real32x3_Rotate_tTemp.vZ);
  *(float *)&ptQTask[2].tQTaskChildren.ptHead = v6;
  DirlightQTask_vRequestedTime = v6;
  if ( ptParent )
  {
    eQTaskType = ptParent->eQTaskType;
    if ( eQTaskType == DirlightQTask_eQTaskType )
      ((void (__cdecl *)(struct QTask_s *, struct QTask_s *))QTask_aatQTaskFinalEvent[ParameterList_eUpdateInternalDataQTaskEvent][eQTaskType].pfHandler)(
        ptParent,
        ptQTask);
  }
  QTask_TriggerQTaskEventRecursivelySpecificQTaskType(
    &Level_ptQLevelQTask->tQTask,
    ParameterList_eUpdateInternalDataQTaskEvent,
    LensflareQTask_eQTaskType,
    nullptr);
  if ( DirlightQTask_ptActiveKeyframe == (struct DirlightKeyframeQTask_t *)ptQTask )
    DirlightQTask_ptActiveKeyframe = nullptr;
  DirlightQTask_SetTime(0.0);
  v8 = DirlightQTask_tDirlightPool;
  for ( i = 0; i < (signed int)DirlightQTask_tDirlightPool->nAllocated; ++i )
  {
    v10 = *(_DWORD *)v8->papxElement[i];
    v11 = *(_DWORD *)(v10 + 152);
    if ( v11 )
    {
      v12 = (_DWORD *)(v11 + 12);
      *v12 = *(_DWORD *)(v10 + 128);
      v12[1] = *(_DWORD *)(v10 + 132);
      v12[2] = *(_DWORD *)(v10 + 136);
      v13 = (_DWORD *)(*(_DWORD *)(v10 + 152) + 24);
      *v13 = *(_DWORD *)(v10 + 140);
      v13[1] = *(_DWORD *)(v10 + 144);
      v13[2] = *(_DWORD *)(v10 + 148);
      v14 = *(_DWORD **)(v10 + 152);
      *v14 = *(_DWORD *)(v10 + 116);
      v14[1] = *(_DWORD *)(v10 + 120);
      v14[2] = *(_DWORD *)(v10 + 124);
      *(_BYTE *)(*(_DWORD *)(v10 + 152) + 37) = *(_BYTE *)(v10 + 158);
      *(_BYTE *)(*(_DWORD *)(v10 + 152) + 36) = *(_BYTE *)(v10 + 157);
      v15 = *(float *)(v10 + 152);
      if ( AppContext_tAppContext.isMainMenu == false )
      {
        v16 = RenderMode_tActiveRenderMode.apfRenderModeMethod[Lightsource_eAddLightsourceRenderModeMethod];
        LODWORD(igi2_frame.Real32x3_Rotate_tTemp.vX) = 196608;
        LODWORD(igi2_frame.Real32x3_Rotate_tTemp.vZ) = (LODWORD(v15) - 129833024) / 40;
        igi2_frame.Real32x3_Rotate_tTemp.vY = v15;
        if ( v16 )
          v16(&igi2_frame.Real32x3_Rotate_tTemp);
      }
    }
    else
    {
      *(_DWORD *)(v10 + 152) = Lightsource_NewDirlight(
                                 (struct real32x3_t *)(v10 + 116),
                                 (struct real32x3_t *)(v10 + 128),
                                 (struct real32x3_t *)(v10 + 140),
                                 *(_BYTE *)(v10 + 157),
                                 *(_BYTE *)(v10 + 158));
    }
    v17 = *(struct Dirlight_s **)(v10 + 152);
    v18 = *(_DWORD *)(v10 + 112);
    SkyDome_ptDirlight = v17;
    if ( !*(_DWORD *)(v18 + 356) )
    {
      if ( *(_DWORD *)(v18 + 12) )
        *(_DWORD *)(v18 + 356) = 1;
    }
    v8 = DirlightQTask_tDirlightPool;
  }
}

// source: h/2/dirlighttask.c:355  [size]
void __cdecl DirlightKeyframeQTask_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = DirlightKeyframeQTask_ptParameterList;
}

// source: h/2/dirlighttask.c:371  [size]
void __cdecl DirlightKeyframeQTask_DeleteHandler(struct QTask_s *ptQTask)
{
  ptQTask->ptParent[4].tQTaskChildren.ptTail = (struct QTask_s *)-8388609;
}

// source: h/2/dirlighttask.c:424  [anchor-mhash]
void __cdecl DirlightQTask_EnterHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { float vDist; };
    struct { char igi2_o1[4]; struct real64x3_t tStripContext; };
    struct { char igi2_o2[28]; struct real32x2_t tScreenPos; };
    struct { char igi2_o3[36]; struct real64x3_t tCameraPos; };
    struct { char igi2_o4[60]; struct QVertex_s atQVertex[4]; };
    char igi2_extent[208];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  double v2; // st7
  double v3; // st6
  double v4; // st7
  int v5; // esi
  char eQTaskType; // cl
  struct QTaskNodeList_s *p_vR; // eax

  if ( ptQTask[6].tQTaskRefList.ptHead )
  {
    v2 = *(float *)&ptQTask[2].eQTaskType;
    igi2_frame.tStripContext.vY = *(float *)&ptQTask[3].ptNext;
    v3 = *(float *)&ptQTask[3].ptPrev;
    qmemcpy(&igi2_frame.tCameraPos, &TransContext_tActiveTransContext.tPos, sizeof(igi2_frame.tCameraPos));
    igi2_frame.tStripContext.vZ = v3 * 409600000.0;
    igi2_frame.tStripContext.vX = igi2_frame.tCameraPos.vX + v2 * 409600000.0;
    igi2_frame.tStripContext.vY = igi2_frame.tCameraPos.vY + igi2_frame.tStripContext.vY * 409600000.0;
    igi2_frame.tStripContext.vZ = igi2_frame.tCameraPos.vZ + igi2_frame.tStripContext.vZ;
    if ( TransContext_ProjectWorldPos2(&TransContext_tActiveTransContext, &igi2_frame.tScreenPos, &igi2_frame.vDist, &igi2_frame.tStripContext) )
    {
      v4 = *(float *)&ptQTask[6].tQTaskRefList.ptMiddle * 0.5;
      v5 = 4;
      LODWORD(igi2_frame.tStripContext.vZ) = igi2_frame.atQVertex;
      eQTaskType = ptQTask[3].eQTaskType;
      QVertex_ptActiveTexture = (struct TexInfo_s *)&ptQTask[5].tQTaskChildren.ptTail;
      HIDWORD(igi2_frame.tStripContext.vX) = &MTP_atLODVirModel[49].atBoneVertexRefs[17].atVertexRefs[120];
      LODWORD(igi2_frame.tStripContext.vX) = 0;
      *(_QWORD *)&igi2_frame.tStripContext.vY = 0x4FFFFFFFFLL;
      p_vR = (struct QTaskNodeList_s *)&igi2_frame.atQVertex[0].vR;
      do
      {
        p_vR[-1].ptTail = (struct QTask_s *)1065353216;
        if ( eQTaskType )
        {
          *p_vR = ptQTask[3].tQTaskChildren;
        }
        else
        {
          p_vR->ptHead = (struct QTask_s *)1065353216;
          p_vR->ptMiddle = (struct QTask_s *)1065353216;
          p_vR->ptTail = (struct QTask_s *)1065353216;
        }
        p_vR[-2].ptTail = (struct QTask_s *)1304645504;
        p_vR += 3;
        --v5;
      }
      while ( v5 );
      igi2_frame.atQVertex[0].vU = 0.0;
      igi2_frame.atQVertex[0].vX = igi2_frame.tScreenPos.vX - v4;
      igi2_frame.atQVertex[0].vV = 0.0;
      igi2_frame.atQVertex[1].vU = 1.0;
      igi2_frame.atQVertex[1].vV = 0.0;
      igi2_frame.atQVertex[2].vU = 0.0;
      igi2_frame.atQVertex[2].vV = 1.0;
      igi2_frame.atQVertex[0].vY = igi2_frame.tScreenPos.vY - v4;
      igi2_frame.atQVertex[3].vU = 1.0;
      igi2_frame.atQVertex[3].vV = 1.0;
      igi2_frame.vDist = igi2_frame.tScreenPos.vX + v4;
      igi2_frame.atQVertex[1].vX = igi2_frame.vDist;
      igi2_frame.atQVertex[3].vX = igi2_frame.vDist;
      igi2_frame.atQVertex[1].vY = igi2_frame.atQVertex[0].vY;
      igi2_frame.atQVertex[2].vX = igi2_frame.atQVertex[0].vX;
      igi2_frame.atQVertex[2].vY = v4 + igi2_frame.tScreenPos.vY;
      igi2_frame.atQVertex[3].vY = igi2_frame.atQVertex[2].vY;
      RenderMode_tActiveRenderMode.apfRenderModeMethod[QVertex_eRegisterQVertexStripMethod](&igi2_frame.tStripContext);
    }
  }
}

// source: h/2/dirlighttask.c:523  [anchor-callee]
struct DirlightQTask_s *__cdecl DirlightQTask_Update(struct DirlightQTask_s *ptDirlightQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { float x; };
    struct { float xa; };
    struct { char igi2_o2[20]; float vT; };
    struct { char igi2_o3[24]; float tTemp_; };
    struct { char igi2_o4[24]; float tTemp_a; };
    struct { char igi2_o5[28]; float tTemp__4; };
    struct { char igi2_o6[28]; float tTemp__4a; };
    struct { char igi2_o7[32]; float tTemp__8; };
    struct { char igi2_o8[32]; float tTemp__8a; };
    struct { char igi2_o9[36]; struct real32x3_t tAxis; };
    struct { char igi2_o10[48]; struct real32x9_t tTempMatrix; };
    char igi2_extent[88];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  unsigned __int16 v1; // dx
  struct QTask_s *v3; // esi
  struct DirlightQTask_s *result; // eax
  float *v5; // ebp
  struct QTask_s *NextSiblingOfType; // edi
  float v7; // edx
  float *v8; // ebp
  struct real32x3_t *v9; // ebx
  double v10; // st7
  double v11; // st7
  double v12; // st7
  struct real32x3_t *v13; // ebx
  double v14; // st7
  double v15; // st6
  float v16; // ecx
  float *p_tQTaskChildren; // esi
  struct real32x3_t *p_tDirection; // ebx
  struct QTask_s *FirstChildOfType; // eax
  float v20; // ecx

  v1 = DirlightKeyframeQTask_eQTaskType;
  v3 = nullptr;
  ptDirlightQTask->ptWorld->isLightingTablesValid = 0;
  result = (struct DirlightQTask_s *)QTask_GetFirstChildOfType(&ptDirlightQTask->tDynCubeObj.tQObj.tQTask, v1);
  if ( result )
  {
    if ( ptDirlightQTask->vMaxTime == ptDirlightQTask->vMinTime )
    {
      FirstChildOfType = QTask_GetFirstChildOfType(&ptDirlightQTask->tDynCubeObj.tQObj.tQTask, v1);
      ptDirlightQTask->tFrontColor = (*(struct real32x3_t *)&FirstChildOfType[1].tQTaskRefList);
      LODWORD(ptDirlightQTask->tBackColor.vX) = FirstChildOfType[1].ptParent;
      ptDirlightQTask->tBackColor.vY = *(float *)&FirstChildOfType[1].eQTaskType;
      v20 = *(float *)&FirstChildOfType[2].ptNext;
      result = (struct DirlightQTask_s *)&FirstChildOfType[1].tQTaskChildren;
      ptDirlightQTask->tBackColor.vZ = v20;
      ptDirlightQTask->tDirection = *(struct real32x3_t *)&result->tDynCubeObj.tQObj.tQTask.ptNext;
    }
    else
    {
      v5 = nullptr;
      NextSiblingOfType = QTask_GetFirstChildOfType(&ptDirlightQTask->tDynCubeObj.tQObj.tQTask, v1);
      if ( !NextSiblingOfType )
        goto LABEL_17;
      while ( *(float *)&NextSiblingOfType[2].tQTaskChildren.ptHead != ptDirlightQTask->vCurrentTime )
      {
        if ( *(float *)&NextSiblingOfType[2].tQTaskChildren.ptHead < (double)ptDirlightQTask->vCurrentTime
          && (!v3
           || *(float *)&NextSiblingOfType[2].tQTaskChildren.ptHead > (double)*(float *)&v3[2].tQTaskChildren.ptHead) )
        {
          v3 = NextSiblingOfType;
        }
        if ( *(float *)&NextSiblingOfType[2].tQTaskChildren.ptHead > (double)ptDirlightQTask->vCurrentTime
          && (!v5 || *(float *)&NextSiblingOfType[2].tQTaskChildren.ptHead < (double)v5[22]) )
        {
          v5 = (float *)NextSiblingOfType;
        }
        NextSiblingOfType = QTask_GetNextSiblingOfType(NextSiblingOfType, v1);
        if ( !NextSiblingOfType )
          goto LABEL_16;
      }
      v3 = NextSiblingOfType;
      v5 = (float *)NextSiblingOfType;
LABEL_16:
      if ( v3 )
      {
        if ( !v5 || v3 == (struct QTask_s *)v5 || *(float *)&v3[2].tQTaskChildren.ptHead == v5[22] )
        {
          LODWORD(ptDirlightQTask->tFrontColor.vX) = v3[1].tQTaskRefList.ptHead;
          LODWORD(ptDirlightQTask->tFrontColor.vY) = v3[1].tQTaskRefList.ptMiddle;
          LODWORD(ptDirlightQTask->tFrontColor.vZ) = v3[1].tQTaskRefList.ptTail;
          LODWORD(ptDirlightQTask->tBackColor.vX) = v3[1].ptParent;
          ptDirlightQTask->tBackColor.vY = *(float *)&v3[1].eQTaskType;
          v16 = *(float *)&v3[2].ptNext;
          p_tQTaskChildren = (float *)&v3[1].tQTaskChildren;
          ptDirlightQTask->tBackColor.vZ = v16;
          p_tDirection = &ptDirlightQTask->tDirection;
          p_tDirection->vX = *p_tQTaskChildren;
          result = *((struct DirlightQTask_s **)p_tQTaskChildren + 1);
          LODWORD(p_tDirection->vY) = result;
          p_tDirection->vZ = p_tQTaskChildren[2];
        }
        else
        {
          igi2_frame.vT = (ptDirlightQTask->vCurrentTime - *(float *)&v3[2].tQTaskChildren.ptHead)
             / (v5[22] - *(float *)&v3[2].tQTaskChildren.ptHead);
          ptDirlightQTask->tFrontColor.vX = (v5[15] - *(float *)&v3[1].tQTaskRefList.ptHead) * igi2_frame.vT
                                          + *(float *)&v3[1].tQTaskRefList.ptHead;
          ptDirlightQTask->tFrontColor.vY = (v5[16] - *(float *)&v3[1].tQTaskRefList.ptMiddle) * igi2_frame.vT
                                          + *(float *)&v3[1].tQTaskRefList.ptMiddle;
          ptDirlightQTask->tFrontColor.vZ = (v5[17] - *(float *)&v3[1].tQTaskRefList.ptTail) * igi2_frame.vT
                                          + *(float *)&v3[1].tQTaskRefList.ptTail;
          ptDirlightQTask->tBackColor.vX = (v5[18] - *(float *)&v3[1].ptParent) * igi2_frame.vT + *(float *)&v3[1].ptParent;
          ptDirlightQTask->tBackColor.vY = (v5[19] - *(float *)&v3[1].eQTaskType) * igi2_frame.vT + *(float *)&v3[1].eQTaskType;
          ptDirlightQTask->tBackColor.vZ = (v5[20] - *(float *)&v3[2].ptNext) * igi2_frame.vT + *(float *)&v3[2].ptNext;
          igi2_frame.tTemp_ = *(float *)&v3[1].tQTaskChildren.ptMiddle * v5[14] - *(float *)&v3[1].tQTaskChildren.ptTail * v5[13];
          v10 = v5[14] * *(float *)&v3[1].tQTaskChildren.ptHead;
          igi2_frame.tAxis.vX = igi2_frame.tTemp_;
          igi2_frame.tTemp__4 = -(v10 - v5[12] * *(float *)&v3[1].tQTaskChildren.ptTail);
          v11 = *(float *)&v3[1].tQTaskChildren.ptHead;
          igi2_frame.tAxis.vY = igi2_frame.tTemp__4;
          igi2_frame.tTemp__8 = v11 * v5[13] - *(float *)&v3[1].tQTaskChildren.ptMiddle * v5[12];
          v12 = v5[14] * *(float *)&v3[1].tQTaskChildren.ptTail;
          igi2_frame.tAxis.vZ = igi2_frame.tTemp__8;
          igi2_frame.x = v12 + v5[12] * *(float *)&v3[1].tQTaskChildren.ptHead + *(float *)&v3[1].tQTaskChildren.ptMiddle * v5[13];
          igi2_frame.xa = Real32_Acos(igi2_frame.x) * igi2_frame.vT;
          Real32x9_CreateRotationAroundAxis(&igi2_frame.tTempMatrix, &igi2_frame.tAxis, igi2_frame.xa);
          v13 = &ptDirlightQTask->tDirection;
          igi2_frame.tTemp_a = igi2_frame.tTempMatrix.tX.vY * *(float *)&v3[1].tQTaskChildren.ptMiddle
                  + igi2_frame.tTempMatrix.tX.vZ * *(float *)&v3[1].tQTaskChildren.ptTail
                  + igi2_frame.tTempMatrix.tX.vX * *(float *)&v3[1].tQTaskChildren.ptHead;
          igi2_frame.tTemp__4a = igi2_frame.tTempMatrix.tY.vY * *(float *)&v3[1].tQTaskChildren.ptMiddle
                    + igi2_frame.tTempMatrix.tY.vZ * *(float *)&v3[1].tQTaskChildren.ptTail
                    + igi2_frame.tTempMatrix.tY.vX * *(float *)&v3[1].tQTaskChildren.ptHead;
          v14 = igi2_frame.tTempMatrix.tZ.vY * *(float *)&v3[1].tQTaskChildren.ptMiddle
              + igi2_frame.tTempMatrix.tZ.vZ * *(float *)&v3[1].tQTaskChildren.ptTail;
          v15 = igi2_frame.tTempMatrix.tZ.vX * *(float *)&v3[1].tQTaskChildren.ptHead;
          v13->vX = igi2_frame.tTemp_a;
          v13->vY = igi2_frame.tTemp__4a;
          igi2_frame.tTemp__8a = v14 + v15;
          v13->vZ = igi2_frame.tTemp__8a;
          return (struct DirlightQTask_s *)LODWORD(igi2_frame.tTemp_a);
        }
      }
      else
      {
LABEL_17:
        ptDirlightQTask->tFrontColor.vX = v5[15];
        ptDirlightQTask->tFrontColor.vY = v5[16];
        ptDirlightQTask->tFrontColor.vZ = v5[17];
        ptDirlightQTask->tBackColor.vX = v5[18];
        ptDirlightQTask->tBackColor.vY = v5[19];
        v7 = v5[20];
        v8 = v5 + 12;
        ptDirlightQTask->tBackColor.vZ = v7;
        result = *(struct DirlightQTask_s **)v8;
        v9 = &ptDirlightQTask->tDirection;
        v9->vX = *v8;
        v9->vY = v8[1];
        v9->vZ = v8[2];
      }
    }
  }
  else
  {
    ptDirlightQTask->tFrontColor.vX = 0.0;
    ptDirlightQTask->tFrontColor.vY = 0.0;
    ptDirlightQTask->tFrontColor.vZ = 0.0;
    ptDirlightQTask->tBackColor.vX = 0.0;
    ptDirlightQTask->tBackColor.vY = 0.0;
    ptDirlightQTask->tBackColor.vZ = 0.0;
    ptDirlightQTask->tDirection.vX = 0.0;
    ptDirlightQTask->tDirection.vY = 0.0;
    ptDirlightQTask->tDirection.vZ = 1.0;
  }
  return result;
}

// source: h/2/dirlighttask.c:659  [anchor-mhash]
void __cdecl DirlightQTask_DrawCallback(struct QCamera_s *ptQCamera)
{
  struct QObjectVector_s *v1; // eax
  signed int i; // ebx
  int v3; // esi
  int v4; // eax
  _DWORD *v5; // eax
  _DWORD *v6; // eax
  _DWORD *v7; // ecx
  int v8; // edi
  void (__cdecl *v9)(void *); // eax
  struct Dirlight_s *v10; // eax
  int v11; // esi
  _DWORD v12[3]; // [esp+4h] [ebp-Ch] BYREF

  DirlightQTask_SetTime(*(float *)&ptQCamera->isFirstPerson);
  v1 = DirlightQTask_tDirlightPool;
  for ( i = 0; i < (signed int)DirlightQTask_tDirlightPool->nAllocated; ++i )
  {
    v3 = *(_DWORD *)v1->papxElement[i];
    v4 = *(_DWORD *)(v3 + 152);
    if ( v4 )
    {
      v5 = (_DWORD *)(v4 + 12);
      *v5 = *(_DWORD *)(v3 + 128);
      v5[1] = *(_DWORD *)(v3 + 132);
      v5[2] = *(_DWORD *)(v3 + 136);
      v6 = (_DWORD *)(*(_DWORD *)(v3 + 152) + 24);
      *v6 = *(_DWORD *)(v3 + 140);
      v6[1] = *(_DWORD *)(v3 + 144);
      v6[2] = *(_DWORD *)(v3 + 148);
      v7 = *(_DWORD **)(v3 + 152);
      *v7 = *(_DWORD *)(v3 + 116);
      v7[1] = *(_DWORD *)(v3 + 120);
      v7[2] = *(_DWORD *)(v3 + 124);
      *(_BYTE *)(*(_DWORD *)(v3 + 152) + 37) = *(_BYTE *)(v3 + 158);
      *(_BYTE *)(*(_DWORD *)(v3 + 152) + 36) = *(_BYTE *)(v3 + 157);
      v8 = *(_DWORD *)(v3 + 152);
      if ( AppContext_tAppContext.isMainMenu == false )
      {
        v9 = RenderMode_tActiveRenderMode.apfRenderModeMethod[Lightsource_eAddLightsourceRenderModeMethod];
        v12[0] = 196608;
        v12[2] = (v8 - 129833024) / 40;
        v12[1] = v8;
        if ( v9 )
          v9(v12);
      }
    }
    else
    {
      *(_DWORD *)(v3 + 152) = Lightsource_NewDirlight(
                                (struct real32x3_t *)(v3 + 116),
                                (struct real32x3_t *)(v3 + 128),
                                (struct real32x3_t *)(v3 + 140),
                                *(_BYTE *)(v3 + 157),
                                *(_BYTE *)(v3 + 158));
    }
    v10 = *(struct Dirlight_s **)(v3 + 152);
    v11 = *(_DWORD *)(v3 + 112);
    SkyDome_ptDirlight = v10;
    if ( !*(_DWORD *)(v11 + 356) )
    {
      if ( *(_DWORD *)(v11 + 12) )
        *(_DWORD *)(v11 + 356) = 1;
    }
    v1 = DirlightQTask_tDirlightPool;
  }
}

// source: h/2/dirlighttask.c:699  [anchor-hash]
void __cdecl DirlightQTask_Open()
{
  unsigned __int16 BaseQTaskType; // ax
  unsigned __int16 v1; // ax
  unsigned __int16 v2; // ax
  unsigned __int16 v3; // si
  unsigned __int16 v4; // di
  __int16 v5; // bx
  struct ParameterList_s *v6; // eax
  struct ParameterList_s *v7; // eax
  int v8; // edx
  struct QObjectVector_s *v9; // esi
  int v10; // eax

  BaseQTaskType = QTask_GetBaseQTaskType();
  DirlightQTask_eQTaskType = QTask_NewQTaskType("Dirlight", 272, BaseQTaskType, 0, 0);
  v1 = QTask_GetBaseQTaskType();
  v2 = QTask_NewQTaskType("DirlightKeyframe", 92, v1, 0, 0);
  v3 = DirlightQTask_eQTaskType;
  v4 = v2;
  DirlightKeyframeQTask_eQTaskType = v2;
  QTask_LinkQTaskEventHandlerFn(
    DirlightQTask_eQTaskType,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveHandler);
  QTask_LinkQTaskEventHandlerFn(v3, 0, DirlightQTask_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v3, 1, (void (__cdecl *)(struct QTask_s *))DirlightQTask_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v3, 2, DirlightQTask_DeleteHandler);
  v5 = ParameterList_eGetParameterListQTaskEvent;
  QTask_LinkQTaskEventHandlerFn(
    v3,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))DirlightQTask_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(
    v3,
    ParameterList_eUpdateInternalDataQTaskEvent,
    DirlightQTask_UpdateInternalDataHandler);
  QTask_LinkQTaskEventHandlerFn(v3, 5, DirlightQTask_EnterHandler);
  QTask_LinkQTaskEventHandlerFn(v4, 0, DirlightKeyframeQTask_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v4, 2, (void (__cdecl *)(struct QTask_s *))DirlightKeyframeQTask_DeleteHandler);
  QTask_LinkQTaskEventHandlerFn(
    v4,
    v5,
    (void (__cdecl *)(struct QTask_s *, void *))DirlightKeyframeQTask_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(
    v4,
    ParameterList_eUpdateInternalDataQTaskEvent,
    DirlightKeyframeQTask_UpdateInternalDataHandler);
  v6 = (struct ParameterList_s *)Mem_AllocFn(172, 4);
  v6->nParameters = 0;
  v6->nMaxParameters = 8;
  v6->ptParameterListItem = (struct ParameterListItem_s *)&v6[1];
  DirlightQTask_ptParameterList = v6;
  v7 = (struct ParameterList_s *)Mem_AllocFn(132, 4);
  v7->ptParameterListItem = (struct ParameterListItem_s *)&v7[1];
  v8 = Level_eParameterTypebool8;
  v7->nParameters = 0;
  v7->nMaxParameters = 6;
  DirlightKeyframeQTask_ptParameterList = v7;
  ParameterList_AddParameter(DirlightQTask_ptParameterList, 0x9Du, v8, "Affects terrain", 7u, nullptr);
  ParameterList_AddParameter(
    DirlightQTask_ptParameterList,
    0x9Eu,
    Level_eParameterTypebool8,
    "Affects objects",
    7u,
    nullptr);
  ParameterList_AddParameter(
    DirlightQTask_ptParameterList,
    0x9Fu,
    Level_eParameterTypebool8,
    "Hard shadows",
    7u,
    nullptr);
  ParameterList_AddParameter(
    DirlightQTask_ptParameterList,
    0xA0u,
    Level_eParameterTypeReal32,
    "Radiosity intensity",
    7u,
    &unk_6B09F8);
  ParameterList_AddParameter(
    DirlightQTask_ptParameterList,
    0xA4u,
    Level_eParameterTypeReal32,
    "Shadow intensity",
    7u,
    &unk_6B09D8);
  ParameterList_AddParameter(
    DirlightQTask_ptParameterList,
    0xB8u,
    Level_eParameterTypeString32,
    "Sun/Moon Texture",
    7u,
    nullptr);
  ParameterList_AddParameterMinMax(
    DirlightQTask_ptParameterList,
    0x108u,
    Level_eParameterTypeReal32,
    "Sun/Moon Size",
    7u,
    1.0,
    100.0);
  ParameterList_AddParameter(
    DirlightQTask_ptParameterList,
    0x9Cu,
    Level_eParameterTypebool8,
    "Sun/Moon Colored",
    7u,
    nullptr);
  ParameterList_AddParameter(
    DirlightKeyframeQTask_ptParameterList,
    0x28u,
    Level_eParameterTypeAngle,
    "Beta",
    7u,
    nullptr);
  ParameterList_AddParameter(
    DirlightKeyframeQTask_ptParameterList,
    0x2Cu,
    Level_eParameterTypeAngle,
    "Gamma",
    7u,
    nullptr);
  ParameterList_AddParameter(
    DirlightKeyframeQTask_ptParameterList,
    0x3Cu,
    Level_eParameterTypeRGB,
    "Front Color",
    7u,
    nullptr);
  ParameterList_AddParameter(
    DirlightKeyframeQTask_ptParameterList,
    0x48u,
    Level_eParameterTypeRGB,
    "Back Color",
    7u,
    nullptr);
  ParameterList_AddParameter(
    DirlightKeyframeQTask_ptParameterList,
    0x54u,
    Level_eParameterTypeReal32,
    "Time",
    7u,
    nullptr);
  v9 = (struct QObjectVector_s *)Mem_AllocFn(52, 4);
  v9->isStrictOrder = true;
  v9->nSize = 0;
  v9->nAllocated = 0;
  v9->nReallocSize = 0;
  v9->papxElement = nullptr;
  v9->nElementSize = 8;
  v9->tMemPool.nBlocks = 0;
  v9->tMemPool.nAllocatedBlocks = 0;
  v9->tMemPool.nAlignment = 4;
  v9->tMemPool.nBlockSize = 8;
  v9->tMemPool.nReAllocBlocks = 0;
  v9->tMemPool.tMemPoolFreeList.ptHead = nullptr;
  v9->tMemPool.tMemPoolSegmentList.ptHead = nullptr;
  MemPool_ReAlloc(&v9->tMemPool, 3u);
  QObjectVector_Realloc(v9, 3u);
  DirlightQTask_tDirlightPool = v9;
  DirlightQTask_tRandomState.anRandom[0] = -923067897;
  DirlightQTask_tRandomState.anRandom[1] = 971667286;
  DirlightQTask_tRandomState.anRandom[2] = 2146516173;
  v10 = 0;
  while ( ViewportQTask_apfDrawCallback[v10] )
  {
    if ( ++v10 >= 15 )
      return;
  }
  ViewportQTask_apfDrawCallback[v10] = DirlightQTask_DrawCallback;
}

// source: h/2/dirlighttask.c:761  [anchor-hash]
void __cdecl DirlightQTask_Close()
{
  int v0; // esi
  int v1; // esi

  QObjectVector_Delete(DirlightQTask_tDirlightPool);
  if ( DirlightKeyframeQTask_ptParameterList )
  {
    v0 = *(_DWORD *)((unsigned int)&DirlightKeyframeQTask_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
  if ( DirlightQTask_ptParameterList )
  {
    v1 = *(_DWORD *)((unsigned int)&DirlightQTask_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v1);
    memset(*(void **)(v1 + 8), 0xCDu, *(_DWORD *)(v1 + 16));
    free((void *)v1);
  }
  QTask_DeleteQTaskType(DirlightKeyframeQTask_eQTaskType);
  QTask_DeleteQTaskType(DirlightQTask_eQTaskType);
}

// source: h/2/dirlighttask.c:783  [size]
unsigned __int16 __cdecl DirlightQTask_GetQTaskType()
{
  return DirlightQTask_eQTaskType;
}

// source: h/2/dirlighttask.c:796  [size]
unsigned __int16 __cdecl DirlightKeyframeQTask_GetQTaskType()
{
  return DirlightKeyframeQTask_eQTaskType;
}

// source: h/2/dirlighttask.c:809  [size]
int __cdecl DirlightQTask_GetNumDirlights()
{
  return DirlightQTask_tDirlightPool->nAllocated;
}

// source: h/2/dirlighttask.c:822  [size]
struct DirlightQTask_s *__cdecl DirlightQTask_GetDirlight(int iDirlightQTask)
{
  return *(struct DirlightQTask_s **)DirlightQTask_tDirlightPool->papxElement[iDirlightQTask];
}

// source: h/2/dirlighttask.c:835  [anchor-callee]
void __cdecl DirlightQTask_SetTime(float vTime)
{
  struct QObjectVector_s *v1; // edi
  signed int i; // esi
  struct DirlightQTask_s *v3; // ecx

  v1 = DirlightQTask_tDirlightPool;
  for ( i = 0; i < (signed int)v1->nAllocated; ++i )
  {
    v3 = *(struct DirlightQTask_s **)v1->papxElement[i];
    if ( vTime != v3->vCurrentTime )
    {
      v3->vCurrentTime = vTime;
      DirlightQTask_Update(v3);
    }
  }
}

// source: h/2/dirlighttask.c:862  [size]
float *__cdecl DirlightQTask_GetRequestedTime()
{
  return DirlightQTask_pvRequestedTime;
}
