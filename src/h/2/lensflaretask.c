/* h/2/lensflaretask.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: h/2/lensflaretask.c:526  [anchor-mhash]
void __cdecl LensflareItemQTask_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ptQTask[1].ptNext = (struct QTask_s *)World_ptActiveWorld;
  ptQTask[1].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[1].tQTaskRefList.ptTail = nullptr;
  ptQTask[1].tQTaskChildren.ptMiddle = (struct QTask_s *)1065353216;
  ptQTask[1].tQTaskChildren.ptTail = (struct QTask_s *)1065353216;
  ptQTask[1].tQTaskRefList.ptHead = (struct QReference_s *)1065353216;
  ptQTask[1].tQTaskChildren.ptHead = nullptr;
  ptQTask[1].ptPrev = (struct QTask_s *)1115684864;
  LOBYTE(ptQTask[1].ptParent) = 1;
}

// source: h/2/lensflaretask.c:550  [size]
void __cdecl LensflareItemQTask_DeleteHandler(struct QTask_s *ptQTask)
{
  ;
}

// source: h/2/lensflaretask.c:564  [size]
void __cdecl LensflareItemQTask_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = LensflareItemQTask_ptParameterList;
}

// source: h/2/lensflaretask.c:580  [anchor-mhash]
void __cdecl LensflareItemQTask_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QReference_s *ptTail; // eax

  if ( (int)ptQTask[1].tQTaskRefList.ptTail >= 10 )
    ptQTask[1].tQTaskRefList.ptTail = (struct QReference_s *)9;
  if ( (int)ptQTask[1].tQTaskRefList.ptTail < 0 )
    ptQTask[1].tQTaskRefList.ptTail = nullptr;
  ptTail = ptQTask[1].tQTaskRefList.ptTail;
  if ( LensflareItemQTask_aisTexLoaded[(_DWORD)ptTail] )
    ptQTask[1].tQTaskRefList.ptMiddle = (struct QReference_s *)(44 * (_DWORD)ptTail + 139180064);
  else
    ptQTask[1].tQTaskRefList.ptMiddle = nullptr;
}

// source: h/2/lensflaretask.c:612  [anchor-strings]
void __cdecl LensflareItemQTask_InitResources(char *zName)
{
  int v1; // esi
  struct TexInfo_s *v2; // ebp
  char zFileName[256]; // [esp+10h] [ebp-100h] BYREF

  v1 = 0;
  v2 = LensflareItemQTask_atTexInfo;
  do
  {
    sprintf(zFileName, "%s%d.tex", zName, v1);
    if ( Resource_IsLoadedInternal(zFileName, nullptr) )
    {
      Texture_Load(v2, nullptr, zFileName);
      LensflareItemQTask_aisTexLoaded[v1] = 1;
    }
    else
    {
      LensflareItemQTask_aisTexLoaded[v1] = 0;
    }
    ++v2;
    ++v1;
  }
  while ( (int)v2 < 139180504 );
}

// source: h/2/lensflaretask.c:649  [anchor-hash]
void __cdecl LensflareItemQTask_DeinitResources()
{
  struct TexInfo_s *v0; // ebx
  int *v1; // esi

  v0 = LensflareItemQTask_atTexInfo;
  v1 = LensflareItemQTask_aisTexLoaded;
  do
  {
    if ( *v1 )
    {
      if ( AppContext_tAppContext.isMainMenu == false )
        RenderMode_atRenderMode[v0->eRenderMode].apfRenderModeMethod[Texture_eDeAllocTextureMethod](v0);
      memset(v0, 0, sizeof(struct TexInfo_s));
    }
    ++v1;
    ++v0;
  }
  while ( (int)v1 < 139180552 );
}

// source: h/2/lensflaretask.c:672  [size]
unsigned __int16 __cdecl LensflareItemQTask_GetQTaskType()
{
  return LensflareItemQTask_eQTaskType;
}

// source: h/2/lensflaretask.c:685  [anchor-mhash]
void __cdecl LensflareQTask_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *ptParent; // ecx
  struct QTask_s *ptPrev; // esi
  struct QTask_s *ptMiddle; // eax

  ptQTask[2].ptParent = (struct QTask_s *)World_ptActiveWorld;
  ptQTask[3].ptPrev = (struct QTask_s *)1065353216;
  ptQTask[3].tQTaskChildren.ptHead = (struct QTask_s *)1065353216;
  ptQTask[3].tQTaskChildren.ptMiddle = (struct QTask_s *)1065353216;
  ptQTask[3].tQTaskChildren.ptTail = (struct QTask_s *)1065353216;
  ptParent = ptQTask[2].ptParent;
  ptQTask[3].tQTaskRefList.ptHead = (struct QReference_s *)-1;
  *(_DWORD *)&ptQTask[2].eQTaskType = 0;
  ptQTask[3].ptNext = nullptr;
  ptQTask[4].ptNext = nullptr;
  ptQTask[3].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[3].tQTaskRefList.ptTail = nullptr;
  ptQTask[3].ptParent = nullptr;
  *(_DWORD *)&ptQTask[3].eQTaskType = 0;
  ptPrev = ptParent[2].ptPrev;
  if ( ptPrev )
  {
    ptPrev[2].tQTaskChildren.ptMiddle = ptQTask;
    ptParent[2].ptPrev[2].tQTaskChildren.ptMiddle[2].tQTaskChildren.ptTail = ptParent[2].ptPrev;
    ptMiddle = ptParent[2].ptPrev[2].tQTaskChildren.ptMiddle;
    ptParent[2].ptPrev = ptMiddle;
    ptMiddle[2].tQTaskChildren.ptMiddle = nullptr;
  }
  else
  {
    ptParent[2].ptPrev = ptQTask;
    ptQTask[2].tQTaskChildren.ptTail = nullptr;
    ptParent[2].ptPrev[2].tQTaskChildren.ptMiddle = nullptr;
  }
}

// source: h/2/lensflaretask.c:714  [size]
void __cdecl LensflareQTask_DeleteHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptMiddle; // ecx
  struct QTask_s *ptTail; // ecx

  ptMiddle = ptQTask[2].tQTaskChildren.ptMiddle;
  if ( ptMiddle )
    ptMiddle[2].tQTaskChildren.ptTail = ptQTask[2].tQTaskChildren.ptTail;
  else
    ptQTask[2].ptParent[2].ptPrev = ptQTask[2].tQTaskChildren.ptTail;
  ptTail = ptQTask[2].tQTaskChildren.ptTail;
  if ( ptTail )
    ptTail[2].tQTaskChildren.ptMiddle = ptQTask[2].tQTaskChildren.ptMiddle;
}

// source: h/2/lensflaretask.c:731  [size]
void __cdecl LensflareQTask_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = LensflareQTask_ptParameterList;
}

// source: h/2/lensflaretask.c:747  [anchor-hash]
struct LensflareQTask_t *__cdecl LensflareQTask_GetDirlightDirectionAndColor(
        struct LensflareQTask_t *ptLensflareQTask)
{
  struct LensflareQTask_t *result; // eax
  struct QTask_s *ptParent; // edx
  float v4; // eax
  struct QTaskNodeList_s *p_tQTaskChildren; // edx
  struct real32x3_t *p_tColor; // esi

  result = (struct LensflareQTask_t *)ptLensflareQTask->nDirlightQTaskID;
  if ( result == (struct LensflareQTask_t *)-1 )
  {
    ptParent = ptLensflareQTask->tDynCubeObj.tQObj.tQTask.ptParent;
  }
  else
  {
    if ( (unsigned int)result >= 0x1000 )
      return result;
    result = (struct LensflareQTask_t *)Level_atLevelQTaskID[(_DWORD)result];
    if ( !result )
      return result;
    ptParent = result->tDynCubeObj.tQObj.tQTask.tQTaskChildren.ptHead;
  }
  if ( ptParent )
  {
    result = (struct LensflareQTask_t *)QTask_IsQTaskTypeDerived(ptParent->eQTaskType, DirlightQTask_eQTaskType);
    if ( result )
    {
      ptLensflareQTask->tDirection.vX = *(float *)&ptParent[2].eQTaskType;
      LODWORD(ptLensflareQTask->tDirection.vY) = ptParent[3].ptNext;
      v4 = *(float *)&ptParent[3].ptPrev;
      p_tQTaskChildren = &ptParent[3].tQTaskChildren;
      ptLensflareQTask->tDirection.vZ = v4;
      p_tColor = &ptLensflareQTask->tColor;
      LODWORD(p_tColor->vX) = p_tQTaskChildren->ptHead;
      result = (struct LensflareQTask_t *)p_tQTaskChildren->ptMiddle;
      LODWORD(p_tColor->vY) = result;
      LODWORD(p_tColor->vZ) = p_tQTaskChildren->ptTail;
    }
  }
  return result;
}

// source: h/2/lensflaretask.c:781  [size]
void __cdecl LensflareQTask_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  LensflareQTask_GetDirlightDirectionAndColor((struct LensflareQTask_t *)ptQTask);
}

// source: h/2/lensflaretask.c:797  [anchor-callee]
float __cdecl Lensflaretask_CalcIntensity(struct LensflareQTask_t *ptLensflare)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct LineOfSightOutputContext_s tContext; };
    struct { char igi2_o1[8]; struct real64x3_t tStop; };
    struct { char igi2_o2[32]; struct real64x3_t tStart; };
    char igi2_extent[60];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  double vX; // st7
  struct World_s *ptWorld; // edx

  vX = ptLensflare->tDirection.vX;
  igi2_frame.tStop.vY = ptLensflare->tDirection.vY;
  ptWorld = ptLensflare->ptWorld;
  igi2_frame.tStop.vZ = ptLensflare->tDirection.vZ;
  qmemcpy(&igi2_frame.tStart, &TransContext_tActiveTransContext.tPos, sizeof(igi2_frame.tStart));
  igi2_frame.tStop.vZ = igi2_frame.tStop.vZ * 409600000.0;
  igi2_frame.tStop.vX = igi2_frame.tStart.vX + vX * 409600000.0;
  igi2_frame.tStop.vY = igi2_frame.tStart.vY + igi2_frame.tStop.vY * 409600000.0;
  igi2_frame.tStop.vZ = igi2_frame.tStart.vZ + igi2_frame.tStop.vZ;
  World_LineOfSight(ptWorld, &igi2_frame.tStart, &igi2_frame.tStop, 512, nullptr, 0xFFFFFFFF, WORLD_DYNCUBETREE_CATEGORY_ALL, &igi2_frame.tContext);
  return igi2_frame.tContext.vTransparency;
}

// source: h/2/lensflaretask.c:833  [anchor-callee]
void __cdecl Lensflaretask_DrawLensflareItem(
        struct LensflareItemQTask_t *ptLensflareItem,
        float vIntensity,
        struct real32x2_t *ptPos)
{
  #pragma pack(push, 1)
  union
  {
    struct { float vSize; };
    struct { char igi2_o1[4]; struct QVertex_s atQVertex[4]; };
    struct { char igi2_o2[148]; struct QVertexStripContext_s tStripContext; };
    char igi2_extent[168];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct TexInfo_s *ptTexInfo; // eax
  double v4; // st7
  int v5; // ecx
  double v6; // st7
  double v7; // st6
  float *p_vR; // eax
  double v9; // st5
  float vX; // edx
  double v11; // st7
  double v12; // st6
  double v13; // st7
  float v14; // edx
  double v15; // st6
  float v16; // edx
  float vY; // ecx
  double v18; // st6
  float v19; // edx
  float v20; // ecx
  double v21; // st6

  ptTexInfo = ptLensflareItem->ptTexInfo;
  if ( ptTexInfo )
  {
    v4 = ptLensflareItem->vSize * 0.9900000095367432;
    igi2_frame.tStripContext.atQVertex = igi2_frame.atQVertex;
    v5 = 4;
    igi2_frame.vSize = v4;
    QVertex_ptActiveTexture = ptTexInfo;
    igi2_frame.tStripContext.bFlags = (unsigned int)&MTP_atLODVirModel[46].atBoneVertexRefs[36].atVertexRefs[235];
    v6 = vIntensity * ptLensflareItem->tColor.vX;
    igi2_frame.tStripContext.isLine = 0;
    igi2_frame.tStripContext.nDepth = -1;
    v7 = vIntensity * ptLensflareItem->tColor.vY;
    igi2_frame.tStripContext.nStripLength = 4;
    p_vR = &igi2_frame.atQVertex[0].vR;
    v9 = vIntensity * ptLensflareItem->tColor.vZ;
    do
    {
      *(p_vR - 1) = 1.0;
      *p_vR = v6;
      *(p_vR - 4) = 409.5899963378906;
      p_vR += 9;
      --v5;
      *(p_vR - 8) = v7;
      *(p_vR - 7) = v9;
    }
    while ( v5 );
    vX = ptPos->vX;
    igi2_frame.atQVertex[0].vY = ptPos->vY;
    v11 = igi2_frame.vSize + ptPos->vX;
    igi2_frame.atQVertex[1].vY = igi2_frame.atQVertex[0].vY;
    igi2_frame.atQVertex[1].vX = v11;
    igi2_frame.atQVertex[0].vU = 0.009999999776482582;
    v12 = igi2_frame.vSize + ptPos->vY;
    igi2_frame.atQVertex[0].vV = 0.009999999776482582;
    igi2_frame.atQVertex[0].vX = vX;
    igi2_frame.atQVertex[1].vU = 0.9900000095367432;
    igi2_frame.atQVertex[2].vY = v12;
    igi2_frame.atQVertex[1].vV = 0.009999999776482582;
    igi2_frame.atQVertex[2].vU = 0.009999999776482582;
    igi2_frame.atQVertex[3].vX = v11;
    igi2_frame.atQVertex[2].vV = 0.9900000095367432;
    igi2_frame.atQVertex[2].vX = vX;
    igi2_frame.atQVertex[3].vY = v12;
    igi2_frame.atQVertex[3].vU = 0.9900000095367432;
    igi2_frame.atQVertex[3].vV = 0.9900000095367432;
    RenderMode_tActiveRenderMode.apfRenderModeMethod[QVertex_eRegisterQVertexStripMethod](&igi2_frame.tStripContext);
    if ( ptLensflareItem->isMirror )
    {
      v13 = ptPos->vX - igi2_frame.vSize;
      v14 = ptPos->vX;
      igi2_frame.atQVertex[0].vY = ptPos->vY;
      igi2_frame.atQVertex[1].vX = v13;
      igi2_frame.atQVertex[1].vY = igi2_frame.atQVertex[0].vY;
      v15 = igi2_frame.vSize + ptPos->vY;
      igi2_frame.atQVertex[0].vU = 0.009999999776482582;
      igi2_frame.atQVertex[2].vY = v15;
      igi2_frame.atQVertex[0].vV = 0.009999999776482582;
      igi2_frame.atQVertex[0].vX = v14;
      igi2_frame.atQVertex[3].vX = v13;
      igi2_frame.atQVertex[1].vU = 0.9900000095367432;
      igi2_frame.atQVertex[1].vV = 0.009999999776482582;
      igi2_frame.atQVertex[3].vY = v15;
      igi2_frame.atQVertex[2].vU = 0.009999999776482582;
      igi2_frame.atQVertex[2].vV = 0.9900000095367432;
      igi2_frame.atQVertex[2].vX = v14;
      igi2_frame.atQVertex[3].vU = 0.9900000095367432;
      igi2_frame.atQVertex[3].vV = 0.9900000095367432;
      RenderMode_tActiveRenderMode.apfRenderModeMethod[QVertex_eRegisterQVertexStripMethod](&igi2_frame.tStripContext);
      v16 = ptPos->vX;
      vY = ptPos->vY;
      igi2_frame.atQVertex[1].vX = igi2_frame.vSize + ptPos->vX;
      igi2_frame.atQVertex[0].vY = vY;
      v18 = ptPos->vY - igi2_frame.vSize;
      igi2_frame.atQVertex[1].vY = vY;
      igi2_frame.atQVertex[2].vY = v18;
      igi2_frame.atQVertex[0].vU = 0.009999999776482582;
      igi2_frame.atQVertex[0].vV = 0.009999999776482582;
      igi2_frame.atQVertex[3].vX = igi2_frame.atQVertex[1].vX;
      igi2_frame.atQVertex[0].vX = v16;
      igi2_frame.atQVertex[1].vU = 0.9900000095367432;
      igi2_frame.atQVertex[3].vY = v18;
      igi2_frame.atQVertex[1].vV = 0.009999999776482582;
      igi2_frame.atQVertex[2].vU = 0.009999999776482582;
      igi2_frame.atQVertex[2].vV = 0.9900000095367432;
      igi2_frame.atQVertex[2].vX = v16;
      igi2_frame.atQVertex[3].vU = 0.9900000095367432;
      igi2_frame.atQVertex[3].vV = 0.9900000095367432;
      RenderMode_tActiveRenderMode.apfRenderModeMethod[QVertex_eRegisterQVertexStripMethod](&igi2_frame.tStripContext);
      v19 = ptPos->vX;
      v20 = ptPos->vY;
      igi2_frame.atQVertex[1].vX = ptPos->vX - igi2_frame.vSize;
      igi2_frame.atQVertex[0].vY = v20;
      v21 = ptPos->vY;
      igi2_frame.atQVertex[0].vU = 0.009999999776482582;
      igi2_frame.atQVertex[0].vV = 0.009999999776482582;
      igi2_frame.atQVertex[0].vX = v19;
      igi2_frame.atQVertex[1].vU = 0.9900000095367432;
      igi2_frame.atQVertex[2].vY = v21 - igi2_frame.vSize;
      igi2_frame.atQVertex[1].vV = 0.009999999776482582;
      igi2_frame.atQVertex[1].vY = v20;
      igi2_frame.atQVertex[3].vX = igi2_frame.atQVertex[1].vX;
      igi2_frame.atQVertex[2].vU = 0.009999999776482582;
      igi2_frame.atQVertex[2].vV = 0.9900000095367432;
      igi2_frame.atQVertex[3].vY = igi2_frame.atQVertex[2].vY;
      igi2_frame.atQVertex[2].vX = v19;
      igi2_frame.atQVertex[3].vU = 0.9900000095367432;
      igi2_frame.atQVertex[3].vV = 0.9900000095367432;
      RenderMode_tActiveRenderMode.apfRenderModeMethod[QVertex_eRegisterQVertexStripMethod](&igi2_frame.tStripContext);
    }
  }
}

// source: h/2/lensflaretask.c:972  [anchor-caller]
void __cdecl LensflareQTask_EnterHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { __int64 vIntensity; };
    struct { char igi2_o1[8]; struct real32x2_t tScreenPos; };
    struct { char igi2_o2[16]; struct real32x2_t tItemPos; };
    struct { char igi2_o3[24]; struct real32x2_t tMirroredScreenPos; };
    struct { char igi2_o4[32]; struct real64x3_t tPos; };
    struct { char igi2_o5[56]; struct real64x3_t tCameraPos; };
    char igi2_extent[80];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *ptHead; // eax
  double v3; // st7
  double v4; // st6
  double v5; // st7
  struct LensflareItemQTask_t *ptNext; // edi
  double v7; // st7
  float v8; // ebx
  double v9; // st7

  if ( LensflareQTask_isDisabled == false )
  {
    LensflareQTask_GetDirlightDirectionAndColor((struct LensflareQTask_t *)ptQTask);
    ptHead = ptQTask->tQTaskChildren.ptHead;
    if ( ptHead->ptNext )
    {
      if ( ptHead )
      {
        v3 = *(float *)&ptQTask[2].eQTaskType;
        v4 = *(float *)&ptQTask[3].ptNext;
        igi2_frame.tPos.vZ = *(float *)&ptQTask[3].ptPrev;
        qmemcpy(&igi2_frame.tCameraPos, &TransContext_tActiveTransContext.tPos, sizeof(igi2_frame.tCameraPos));
        igi2_frame.tPos.vX = v3 * 409600000.0;
        igi2_frame.tPos.vX = igi2_frame.tCameraPos.vX + igi2_frame.tPos.vX;
        igi2_frame.tPos.vY = igi2_frame.tCameraPos.vY + v4 * 409600000.0;
        igi2_frame.tPos.vZ = igi2_frame.tCameraPos.vZ + igi2_frame.tPos.vZ * 409600000.0;
        TransContext_ProjectWorldPos2(&TransContext_tActiveTransContext, &igi2_frame.tScreenPos, (float *)&igi2_frame.vIntensity, &igi2_frame.tPos);
        if ( *(float *)&igi2_frame.vIntensity < 10000.0
          || igi2_frame.tScreenPos.vX < (double)RenderContext_tActiveRenderContext.tDisplayAreaMin.vX
          || igi2_frame.tScreenPos.vX >= (double)RenderContext_tActiveRenderContext.tDisplayAreaMax.vX
          || igi2_frame.tScreenPos.vY < (double)RenderContext_tActiveRenderContext.tDisplayAreaMin.vY
          || igi2_frame.tScreenPos.vY >= (double)RenderContext_tActiveRenderContext.tDisplayAreaMax.vY )
        {
          v5 = 0.0;
        }
        else
        {
          v5 = Lensflaretask_CalcIntensity((struct LensflareQTask_t *)ptQTask);
        }
        ptNext = ptQTask->tQTaskChildren.ptHead->ptNext != nullptr
               ? (struct LensflareItemQTask_t *)ptQTask->tQTaskChildren.ptHead
               : nullptr;
        igi2_frame.tMirroredScreenPos.vX = (RenderContext_tActiveRenderContext.tDisplayAreaMax.vX
                               + RenderContext_tActiveRenderContext.tDisplayAreaMin.vX)
                              * 0.5
                              - igi2_frame.tScreenPos.vX
                              + (RenderContext_tActiveRenderContext.tDisplayAreaMax.vX
                               + RenderContext_tActiveRenderContext.tDisplayAreaMin.vX)
                              * 0.5;
        igi2_frame.tMirroredScreenPos.vY = (RenderContext_tActiveRenderContext.tDisplayAreaMax.vY
                               + RenderContext_tActiveRenderContext.tDisplayAreaMin.vY)
                              * 0.5
                              - igi2_frame.tScreenPos.vY
                              + (RenderContext_tActiveRenderContext.tDisplayAreaMax.vY
                               + RenderContext_tActiveRenderContext.tDisplayAreaMin.vY)
                              * 0.5;
        v7 = *(float *)&ptQTask[4].ptNext * 0.800000011920929 + v5 * 0.20000000298023224;
        *(float *)&ptQTask[4].ptNext = v7;
        *(float *)&igi2_frame.vIntensity = v7;
        if ( v7 >= 0.009999999776482582 )
        {
          v8 = *(float *)&igi2_frame.vIntensity;
          do
          {
            if ( ptNext->tQTask.eQTaskType == LensflareItemQTask_eQTaskType )
            {
              v9 = (igi2_frame.tMirroredScreenPos.vX - igi2_frame.tScreenPos.vX) * ptNext->vPos + igi2_frame.tScreenPos.vX;
              igi2_frame.tItemPos.vY = (igi2_frame.tMirroredScreenPos.vY - igi2_frame.tScreenPos.vY) * ptNext->vPos + igi2_frame.tScreenPos.vY;
              LODWORD(igi2_frame.vIntensity) = (__int64)v9;
              igi2_frame.tItemPos.vX = (float)(int)igi2_frame.vIntensity;
              igi2_frame.vIntensity = (__int64)igi2_frame.tItemPos.vY;
              igi2_frame.tItemPos.vY = (float)(int)igi2_frame.vIntensity;
              Lensflaretask_DrawLensflareItem(ptNext, v8, &igi2_frame.tItemPos);
            }
            ptNext = (struct LensflareItemQTask_t *)ptNext->tQTask.ptNext;
          }
          while ( ptNext );
        }
      }
    }
  }
}

// source: h/2/lensflaretask.c:1130  [size]
enum bool __cdecl LensflareQTask_IsLensflaresEnabled()
{
  return LensflareQTask_isDisabled == false;
}

// source: h/2/lensflaretask.c:1143  [size]
void __cdecl LensflareQTask_EnableLensflares(enum bool isEnabled)
{
  LensflareQTask_isDisabled = isEnabled == false;
}

// source: h/2/lensflaretask.c:1156  [anchor-hash]
void __cdecl LensflareQTask_Open()
{
  unsigned __int16 BaseQTaskType; // ax
  unsigned __int16 v1; // ax
  unsigned __int16 v2; // ax
  unsigned __int16 v3; // si
  unsigned __int16 v4; // di
  __int16 v5; // bx
  __int16 v6; // bp
  struct ParameterList_s *v7; // eax
  struct ParameterList_s *v8; // eax
  int v9; // edx
  int *p_iViewport; // eax

  BaseQTaskType = QTask_GetBaseQTaskType();
  LensflareQTask_eQTaskType = QTask_NewQTaskType("Lensflare", 168, BaseQTaskType, 0, 0);
  v1 = QTask_GetBaseQTaskType();
  v2 = QTask_NewQTaskType("LensflareItem", 76, v1, 0, 0);
  v3 = LensflareQTask_eQTaskType;
  v4 = v2;
  LensflareItemQTask_eQTaskType = v2;
  QTask_LinkQTaskEventHandlerFn(LensflareQTask_eQTaskType, 0, LensflareQTask_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v3, 2, LensflareQTask_DeleteHandler);
  v5 = ParameterList_eGetParameterListQTaskEvent;
  QTask_LinkQTaskEventHandlerFn(
    v3,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))LensflareQTask_GetParameterListHandler);
  v6 = ParameterList_eUpdateInternalDataQTaskEvent;
  QTask_LinkQTaskEventHandlerFn(
    v3,
    ParameterList_eUpdateInternalDataQTaskEvent,
    LensflareQTask_UpdateInternalDataHandler);
  QTask_LinkQTaskEventHandlerFn(v3, 5, LensflareQTask_EnterHandler);
  QTask_LinkQTaskEventHandlerFn(v3, DynCubeObj_eDynCubeObjRegisterQTaskEvent, nullptr);
  QTask_LinkQTaskEventHandlerFn(v3, DynCubeObj_eDynCubeObjRemoveQTaskEvent, nullptr);
  QTask_LinkQTaskEventHandlerFn(v4, 0, LensflareItemQTask_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v4, 2, (void (__cdecl *)(struct QTask_s *))LensflareItemQTask_DeleteHandler);
  QTask_LinkQTaskEventHandlerFn(
    v4,
    v5,
    (void (__cdecl *)(struct QTask_s *, void *))LensflareItemQTask_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(v4, v6, LensflareItemQTask_UpdateInternalDataHandler);
  v7 = (struct ParameterList_s *)Mem_AllocFn(72, 4);
  v7->nParameters = 0;
  v7->nMaxParameters = 3;
  v7->ptParameterListItem = (struct ParameterListItem_s *)&v7[1];
  LensflareQTask_ptParameterList = v7;
  v8 = (struct ParameterList_s *)Mem_AllocFn(112, 4);
  v8->ptParameterListItem = (struct ParameterListItem_s *)&v8[1];
  v9 = Level_eParameterTypeReal32;
  v8->nParameters = 0;
  v8->nMaxParameters = 5;
  LensflareItemQTask_ptParameterList = v8;
  LensflareQTask_eParameterTypeRangeReal32 = ParameterList_NewParameterType("RangeReal32", v9);
  ParameterList_AddParameter(
    LensflareQTask_ptParameterList,
    0x74u,
    Level_eParameterTypeReal32x3,
    "Direction",
    7u,
    nullptr);
  ParameterList_AddParameter(LensflareQTask_ptParameterList, 0x80u, Level_eParameterTypeRGB, "Color", 7u, nullptr);
  ParameterList_AddParameter(
    LensflareQTask_ptParameterList,
    0x8Cu,
    Level_eParameterTypeInt32,
    "Dirlight QTask ID",
    7u,
    nullptr);
  ParameterList_AddParameter(LensflareItemQTask_ptParameterList, 0x34u, Level_eParameterTypeRGB, "Color", 7u, nullptr);
  ParameterList_AddParameter(
    LensflareItemQTask_ptParameterList,
    0x30u,
    LensflareQTask_eParameterTypeRangeReal32,
    "Position",
    7u,
    nullptr);
  ParameterList_AddParameter(LensflareItemQTask_ptParameterList, 0x2Cu, Level_eParameterTypeReal32, "Size", 7u, nullptr);
  ParameterList_AddParameter(
    LensflareItemQTask_ptParameterList,
    0x44u,
    Level_eParameterTypeInt32,
    "SpriteIndex",
    7u,
    nullptr);
  ParameterList_AddParameter(
    LensflareItemQTask_ptParameterList,
    0x48u,
    Level_eParameterTypebool8,
    "Mirror?",
    7u,
    nullptr);
  memset(LensflareItemQTask_aisTexLoaded, 0, sizeof(LensflareItemQTask_aisTexLoaded));
  LensflareQTask_tRandomState.anRandom[0] = -923067897;
  LensflareQTask_tRandomState.anRandom[1] = 971667286;
  LensflareQTask_tRandomState.anRandom[2] = 2146516173;
  p_iViewport = &Lensflare_atReadIntensityInfo[0].iViewport;
  do
  {
    *(p_iViewport - 2) = -1;
    *p_iViewport = 0;
    p_iViewport += 5;
  }
  while ( (int)p_iViewport < 127905176 );
  memset(Lensflare_avLastIntensity, 0, sizeof(Lensflare_avLastIntensity));
}

// source: h/2/lensflaretask.c:1229  [anchor-mhash]
void __cdecl LensflareQTask_Close()
{
  int v0; // esi
  int v1; // esi

  ParameterList_atParameterType[LensflareQTask_eParameterTypeRangeReal32].isUsed = false;
  if ( LensflareItemQTask_ptParameterList )
  {
    v0 = *(_DWORD *)((unsigned int)&LensflareItemQTask_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
  if ( LensflareQTask_ptParameterList )
  {
    v1 = *(_DWORD *)((unsigned int)&LensflareQTask_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v1);
    memset(*(void **)(v1 + 8), 0xCDu, *(_DWORD *)(v1 + 16));
    free((void *)v1);
  }
  QTask_DeleteQTaskType(LensflareItemQTask_eQTaskType);
  QTask_DeleteQTaskType(LensflareQTask_eQTaskType);
}

// source: h/2/lensflaretask.c:1251  [size]
unsigned __int16 __cdecl LensflareQTask_GetQTaskType()
{
  return LensflareQTask_eQTaskType;
}
