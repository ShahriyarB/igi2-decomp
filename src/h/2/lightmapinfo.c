/* h/2/lightmapinfo.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: h/2/lightmapinfo.c:375  [anchor-hash]
void __cdecl LightmapInfo_EndSave()
{
  int v0; // esi

  if ( LightmapInfo_ptOLMFilenameList )
  {
    v0 = *(_DWORD *)((unsigned int)&LightmapInfo_ptOLMFilenameList[-1].zFilename[96] & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
    LightmapInfo_ptOLMFilenameList = nullptr;
  }
  LightmapInfo_isUpdated = false;
}

// source: h/2/lightmapinfo.c:393  [anchor-hash]
char *__cdecl LightmapInfo_GetDirectory()
{
  sprintf(LightmapInfo_zDirectory, "LOCAL:%s", "lightmaps");
  return LightmapInfo_zDirectory;
}

// source: h/2/lightmapinfo.c:409  [anchor-strings]
char *__cdecl LightmapInfo_GetResourceFilename()
{
  sprintf(LightmapInfo_zResource, "MISSION:%s/%s", "lightmaps", "lightmaps.res");
  return LightmapInfo_zResource;
}

// source: h/2/lightmapinfo.c:424  [anchor-hash]
void __cdecl LightmapInfo_FreeLightmapTexInfo(struct Mesh3D_Lightmap_t *ptLightmap)
{
  Texture_eCategory = TEXTURE_CATEGORY_LIGHTMAP;
  if ( AppContext_tAppContext.isMainMenu == false )
    RenderMode_atRenderMode[ptLightmap->tTexInfo.eRenderMode].apfRenderModeMethod[Texture_eDeAllocTextureMethod](ptLightmap);
  memset(ptLightmap, 0, 0x2Cu);
  memset(ptLightmap, 0, 0x2Cu);
  Texture_eCategory = TEXTURE_CATEGORY_OTHER;
}

// source: h/2/lightmapinfo.c:448  [size]
void __cdecl LightmapInfo_DownloadLightmapTexInfo(
        struct Mesh3D_Lightmap_t *ptLightmap,
        unsigned int *pnMainRAMMap)
{
  int nWidth; // [esp-10h] [ebp-10h]
  int nHeight; // [esp-Ch] [ebp-Ch]

  nHeight = ptLightmap->nHeight;
  nWidth = ptLightmap->nWidth;
  Texture_eCategory = TEXTURE_CATEGORY_LIGHTMAP;
  Texture_Download(&ptLightmap->tTexInfo, nullptr, 4 * nWidth, nWidth, nHeight, 3, pnMainRAMMap);
  Texture_eCategory = TEXTURE_CATEGORY_OTHER;
}

// source: h/2/lightmapinfo.c:471  [size]
void __cdecl LightmapInfo_AllocLightmapTexInfo(struct Mesh3D_Lightmap_t *ptLightmap)
{
  int nWidth; // [esp-Ch] [ebp-14h]
  int nHeight; // [esp-8h] [ebp-10h]

  nHeight = ptLightmap->nHeight;
  nWidth = ptLightmap->nWidth;
  Texture_eCategory = TEXTURE_CATEGORY_LIGHTMAP;
  Texture_Alloc(&ptLightmap->tTexInfo, nullptr, 4 * nWidth, nWidth, nHeight, 3, 0, 0x20000001u);
  Texture_eCategory = TEXTURE_CATEGORY_OTHER;
}

// source: h/2/lightmapinfo.c:492  [anchor-callee]
void __cdecl LightmapInfo_DeleteCalculationLightmaps(struct Mesh3D_LightmapList_s *ptLightmapList)
{
  struct Mesh3D_LightmapList_s *v1; // ecx
  int v2; // ebx
  struct CalculationLightmap_s *v3; // ebp
  int v4; // esi
  struct CalculationLightmap_s *ptCalculationLightmap; // eax
  int v6; // esi

  v1 = ptLightmapList;
  if ( ptLightmapList->ptCalculationLightmap )
  {
    v2 = 0;
    if ( ptLightmapList->nNumLightmaps > 0 )
    {
      do
      {
        v3 = &v1->ptCalculationLightmap[v2];
        if ( v3->patCalculationTexel )
        {
          v4 = *(_DWORD *)((int)&v3->patCalculationTexel[-1].nIllumination & 0xFFFFFFFC);
          --Mem_nCurrentAllocations;
          Node_Remove((_DWORD **)v4);
          memset(*(void **)(v4 + 8), 0xCDu, *(_DWORD *)(v4 + 16));
          free((void *)v4);
          v1 = ptLightmapList;
        }
        v3->patCalculationTexel = nullptr;
        ++v2;
      }
      while ( v2 < v1->nNumLightmaps );
    }
    ptCalculationLightmap = v1->ptCalculationLightmap;
    if ( ptCalculationLightmap )
    {
      v6 = *(_DWORD *)((unsigned int)&ptCalculationLightmap[-1] & 0xFFFFFFFC);
      --Mem_nCurrentAllocations;
      Node_Remove((_DWORD **)v6);
      memset(*(void **)(v6 + 8), 0xCDu, *(_DWORD *)(v6 + 16));
      free((void *)v6);
      v1 = ptLightmapList;
    }
    v1->ptCalculationLightmap = nullptr;
  }
}

// source: h/2/lightmapinfo.c:520  [anchor-callee]
void __cdecl LightmapInfo_DeleteLightmapList(struct Mesh3D_LightmapList_s *ptLightmapList)
{
  int v2; // ebp
  struct Mesh3D_Lightmap_t *atLightmap; // esi
  struct Resource_s *ptHead; // ecx
  struct Resource_s *ptNext; // eax
  unsigned int nType; // eax
  int **p_pnMainRAMMap; // ebp
  int v8; // esi
  int v9; // esi
  int iLightmap; // [esp+10h] [ebp-4h]

  LightmapInfo_DeleteCalculationLightmaps(ptLightmapList);
  v2 = 0;
  if ( ptLightmapList->nNumLightmaps > 0 )
  {
    atLightmap = ptLightmapList->atLightmap;
    do
    {
      Texture_eCategory = TEXTURE_CATEGORY_LIGHTMAP;
      if ( AppContext_tAppContext.isMainMenu == false )
        RenderMode_atRenderMode[atLightmap->tTexInfo.eRenderMode].apfRenderModeMethod[Texture_eDeAllocTextureMethod](atLightmap);
      memset(atLightmap, 0, 0x2Cu);
      memset(atLightmap, 0, 0x2Cu);
      Texture_eCategory = TEXTURE_CATEGORY_OTHER;
      ++v2;
      ++atLightmap;
    }
    while ( v2 < ptLightmapList->nNumLightmaps );
  }
  if ( ptLightmapList->isResource )
  {
    ptHead = Resource_tResourceList.ptHead;
    ptNext = Resource_tResourceList.ptHead->ptNext;
    if ( Resource_tResourceList.ptHead->ptNext )
    {
      while ( ptHead->pxData != ptLightmapList )
      {
        ptHead = ptNext;
        ptNext = ptNext->ptNext;
        if ( !ptNext )
          return;
      }
      nType = ptHead->nType;
      if ( nType != 3 && nType != 1 )
        Resource_Remove(ptHead);
    }
  }
  else
  {
    iLightmap = 0;
    if ( ptLightmapList->nNumLightmaps > 0 )
    {
      p_pnMainRAMMap = &ptLightmapList->atLightmap[0].pnMainRAMMap;
      do
      {
        if ( *p_pnMainRAMMap )
        {
          v8 = *(_DWORD *)((unsigned int)(*p_pnMainRAMMap - 1) & 0xFFFFFFFC);
          --Mem_nCurrentAllocations;
          Node_Remove((_DWORD **)v8);
          memset(*(void **)(v8 + 8), 0xCDu, *(_DWORD *)(v8 + 16));
          free((void *)v8);
          *p_pnMainRAMMap = nullptr;
        }
        p_pnMainRAMMap += 13;
        ++iLightmap;
      }
      while ( iLightmap < ptLightmapList->nNumLightmaps );
    }
    v9 = *(_DWORD *)((unsigned int)&ptLightmapList[-1].atLightmap[0].nWidth & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v9);
    memset(*(void **)(v9 + 8), 0xCDu, *(_DWORD *)(v9 + 16));
    free((void *)v9);
  }
}

// source: h/2/lightmapinfo.c:571  [anchor-strings]
enum bool __cdecl LightmapInfo_CreateLightmapList(
        struct Mesh3D_LightmapVirModel_t *ptLightmapVirModel,
        enum bool isForceCreateNew,
        float vRadiosityPerSquareMeter,
        char *zMainFilename,
        int iVirModel)
{
  #pragma pack(push, 1)
  union
  {
    struct { int v30; };
    struct { int v31; };
    struct { char igi2_o2[4]; int v32; };
    struct { char igi2_o3[4]; int v33; };
    struct { char igi2_o4[12]; void *v34; };
    struct { char igi2_o5[24]; int v35; };
    struct { char igi2_o6[24]; int v36; };
    struct { char igi2_o7[28]; int v37; };
    struct { char igi2_o8[28]; int v38; };
    struct { char igi2_o9[52]; struct VirModel_s *ptVirModel; };
    struct { char igi2_o10[52]; struct VirModel_s *ptVirModela; };
    struct { char igi2_o11[56]; int iLightmap; };
    struct { char igi2_o12[56]; int iLightmapa; };
    struct { char igi2_o13[60]; struct Mesh3D_RenderMesh_LightmapDirect3D_t *ptRenderMesh; };
    struct { char igi2_o14[64]; char zFilename[512]; };
    char igi2_extent[576];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct VirModel_s *v5; // ebp
  enum bool v6; // esi
  struct Mesh3D_Mesh_t *ptMesh; // eax
  struct Mesh3D_RenderMesh_LightmapDirect3D_t *v8; // ebp
  char *v9; // esi
  struct Mesh3D_Mesh_t *v10; // ecx
  _DWORD *v11; // esi
  struct Mesh3D_Mesh_t *v12; // ecx
  char *v13; // ebx
  __int16 *v14; // edi
  struct LightmapDirect3D_Lightmap_t *v15; // eax
  __int16 nWidth; // cx
  __int16 *v17; // ebp
  void *v18; // eax
  int v19; // ecx
  int v20; // edx
  bool v21; // cc
  int i; // eax
  _DWORD *v23; // ebx
  struct Mesh3D_LightmapList_s *v24; // ebp
  __int16 *p_nWidth; // edi
  int nNumLightmaps; // ecx
  struct Resource_s *ptHead; // ecx
  struct Resource_s *ptNext; // eax
  unsigned int nType; // eax

  v5 = ptLightmapVirModel->ptVirModel;
  v6 = isForceCreateNew;
  igi2_frame.ptVirModel = v5;
  if ( isForceCreateNew )
  {
    if ( ptLightmapVirModel->ptLightmapList )
    {
      LightmapInfo_DeleteLightmapList(ptLightmapVirModel->ptLightmapList);
      ptLightmapVirModel->ptLightmapList = nullptr;
    }
  }
  else if ( ptLightmapVirModel->ptLightmapList )
  {
    return isForceCreateNew;
  }
  ptMesh = v5->ptModel->ptMesh;
  if ( ptMesh->eRenderMeshType == MESH3D_RENDERMESHTYPE_DIRECT3D_BUILDING )
  {
    igi2_frame.ptRenderMesh = (struct Mesh3D_RenderMesh_LightmapDirect3D_t *)ptMesh->pxRenderMesh;
    if ( !igi2_frame.ptRenderMesh->nNumFaces )
      igi2_frame.ptRenderMesh = nullptr;
    v8 = igi2_frame.ptRenderMesh;
  }
  else
  {
    v8 = nullptr;
    igi2_frame.ptRenderMesh = nullptr;
  }
  v8->ptVertexData->isInitialized = 0;
  if ( v6 )
    goto LABEL_30;
  sprintf(LightmapInfo_zDirectory, "LOCAL:%s", "lightmaps");
  sprintf(igi2_frame.zFilename, "%s/%s", LightmapInfo_zDirectory, ptLightmapVirModel->zFilename);
  if ( Resource_IsLoadedInternal(igi2_frame.zFilename, nullptr) == false && File_Exists(igi2_frame.zFilename) == false )
  {
    sprintf(
      igi2_frame.zFilename,
      "LOCAL:missions/location%d/level%d/lightmaps/%s",
      Game_iMissionID / 10,
      Game_iMissionID % 10,
      ptLightmapVirModel->zFilename);
    if ( Resource_IsLoadedInternal(igi2_frame.zFilename, nullptr) == false && File_Exists(igi2_frame.zFilename) == false )
      goto LABEL_22;
    LightmapInfo_isUpdated = true;
  }
  v9 = (char *)Resource_Load(igi2_frame.zFilename, nullptr);
  if ( *(_DWORD *)v9 == 1039516303 )
  {
    v10 = igi2_frame.ptVirModel->ptModel->ptMesh;
    if ( v10->vVersion == *((float *)v9 + 1)
      && QCalendar_Compare(&v10->tTime, (struct QCalendar_s *)(v9 + 8)) < 0
      && v8->nNumLightmaps == *((_DWORD *)v9 + 11) )
    {
      goto LABEL_39;
    }
  }
  Resource_Flush(v9);
LABEL_22:
  if ( iVirModel == -1 )
    goto LABEL_30;
  sprintf(LightmapInfo_zDirectory, "LOCAL:%s", "lightmaps");
  sprintf(igi2_frame.zFilename, "%s/%s_%05d.olm", LightmapInfo_zDirectory, zMainFilename, iVirModel);
  if ( Resource_IsLoadedInternal(igi2_frame.zFilename, nullptr) == false && File_Exists(igi2_frame.zFilename) == false )
    goto LABEL_30;
  v11 = Resource_Load(igi2_frame.zFilename, nullptr);
  if ( *v11 != 1039516303
    || (v12 = igi2_frame.ptVirModel->ptModel->ptMesh, v12->vVersion != *((float *)v11 + 1))
    || QCalendar_Compare(&v12->tTime, (struct QCalendar_s *)(v11 + 2)) >= 0
    || v8->nNumLightmaps != v11[11] )
  {
    Resource_Flush(v11);
LABEL_30:
    v13 = (char *)Mem_AllocFn(52 * v8->nNumLightmaps + 60, 4);
    *((_DWORD *)v13 + 11) = v8->nNumLightmaps;
    *((_DWORD *)v13 + 14) = 0;
    *((_DWORD *)v13 + 9) = 0;
    *((_DWORD *)v13 + 10) = 1;
    LightmapInfo_isUpdated = true;
    *((_DWORD *)v13 + 12) = 0;
    *((_DWORD *)v13 + 13) = 0;
    *((_DWORD *)v13 + 1) = 1042536202;
    *(_DWORD *)v13 = 1039516303;
    QCalendar_Init((struct QCalendar_s *)(v13 + 8));
    igi2_frame.iLightmap = 0;
    if ( *((int *)v13 + 11) > 0 )
    {
      v14 = (__int16 *)(v13 + 108);
      do
      {
        v15 = &igi2_frame.ptRenderMesh->ptLightmap[igi2_frame.iLightmap];
        nWidth = v15->nWidth;
        *v14 = v15->nWidth;
        LOWORD(v15) = v15->nHeight;
        v14[1] = (__int16)v15;
        v17 = v14 - 24;
        v18 = Mem_AllocFn(4 * nWidth * (__int16)v15, 4);
        v19 = 0;
        v20 = 0;
        v21 = v14[1] <= 0;
        *((_DWORD *)v14 - 1) = v18;
        if ( !v21 )
        {
          do
          {
            for ( i = 0; i < *v14; ++v19 )
            {
              *(_DWORD *)(*((_DWORD *)v14 - 1) + 4 * v19) = -1;
              ++i;
            }
            ++v20;
          }
          while ( v20 < v14[1] );
        }
        igi2_frame.v37 = v17[25];
        igi2_frame.v35 = *v14;
        Texture_eCategory = TEXTURE_CATEGORY_LIGHTMAP;
        Texture_Alloc((struct TexInfo_s *)(v14 - 24), nullptr, 4 * igi2_frame.v35, igi2_frame.v35, igi2_frame.v37, 3, 0, 0x20000001u);
        igi2_frame.v34 = *((void **)v17 + 11);
        igi2_frame.v32 = v17[25];
        igi2_frame.v30 = *v14;
        Texture_eCategory = TEXTURE_CATEGORY_LIGHTMAP;
        Texture_Download((struct TexInfo_s *)(v14 - 24), nullptr, 4 * igi2_frame.v30, igi2_frame.v30, igi2_frame.v32, 3, igi2_frame.v34);
        ptLightmapVirModel->isLightmapsUploaded = 0;
        isForceCreateNew = igi2_frame.iLightmap + 1;
        v14 += 26;
        v21 = igi2_frame.iLightmap + 1 < (int)(*((_DWORD *)v13 + 11));
        Texture_eCategory = TEXTURE_CATEGORY_OTHER;
        ++igi2_frame.iLightmap;
      }
      while ( v21 );
    }
    ptLightmapVirModel->ptLightmapList = (struct Mesh3D_LightmapList_s *)v13;
    return isForceCreateNew;
  }
LABEL_39:
  v23 = Resource_Load(igi2_frame.zFilename, nullptr);
  v24 = (struct Mesh3D_LightmapList_s *)Mem_AllocFn(52 * v23[11] + 60, 4);
  qmemcpy(v24, v23, 52 * v23[11] + 60);
  v24->ptCalculationLightmap = nullptr;
  v24->isResource = 0;
  v24->isUpdated = 1;
  igi2_frame.ptVirModela = (struct VirModel_s *)&v23[13 * v23[11] + 15];
  igi2_frame.iLightmapa = 0;
  if ( v24->nNumLightmaps > 0 )
  {
    p_nWidth = &v24->atLightmap[0].nWidth;
    do
    {
      igi2_frame.v38 = p_nWidth[1];
      igi2_frame.v36 = *p_nWidth;
      Texture_eCategory = TEXTURE_CATEGORY_LIGHTMAP;
      Texture_Alloc((struct TexInfo_s *)(p_nWidth - 24), nullptr, 4 * igi2_frame.v36, igi2_frame.v36, igi2_frame.v38, 3, 0, 0x20000001u);
      igi2_frame.v33 = p_nWidth[1];
      igi2_frame.v31 = *p_nWidth;
      Texture_eCategory = TEXTURE_CATEGORY_LIGHTMAP;
      Texture_Download((struct TexInfo_s *)(p_nWidth - 24), nullptr, 4 * igi2_frame.v31, igi2_frame.v31, igi2_frame.v33, 3, igi2_frame.ptVirModela);
      igi2_frame.ptVirModela = (struct VirModel_s *)((char *)igi2_frame.ptVirModela + 4 * *p_nWidth * p_nWidth[1]);
      *((_DWORD *)p_nWidth - 1) = 0;
      nNumLightmaps = v24->nNumLightmaps;
      p_nWidth += 26;
      Texture_eCategory = TEXTURE_CATEGORY_OTHER;
      ++igi2_frame.iLightmapa;
    }
    while ( igi2_frame.iLightmapa < nNumLightmaps );
  }
  ptHead = Resource_tResourceList.ptHead;
  ptNext = Resource_tResourceList.ptHead->ptNext;
  if ( Resource_tResourceList.ptHead->ptNext )
  {
    while ( ptHead->pxData != v24 )
    {
      ptHead = ptNext;
      ptNext = ptNext->ptNext;
      if ( !ptNext )
        goto LABEL_49;
    }
    nType = ptHead->nType;
    if ( nType != 3 && nType != 1 )
      Resource_Remove(ptHead);
  }
LABEL_49:
  LightmapInfo_nNumTexels += v24->nNumTexels;
  LightmapInfo_nNumLightTexels += v24->nNumLightTexels;
  ptLightmapVirModel->ptLightmapList = v24;
  ptLightmapVirModel->isLightmapsUploaded = 1;
  return (enum bool)ptLightmapVirModel;
}

// source: h/2/lightmapinfo.c:804  [size]
void __cdecl LightmapInfo_CalculateCollFaceToRenderFaceTable(
        struct Mesh3D_LightmapVirModel_t *ptLightmapVirModel)
{
  ;
}

// source: h/2/lightmapinfo.c:1213  [size]
void __cdecl LightmapInfo_CalculateLightmaps(
        struct LightmapInfo_s *ptLightmapInfo,
        int nNumBounce,
        enum bool isUpdate)
{
  ;
}

// source: h/2/lightmapinfo.c:1585  [anchor-mhash]
void __cdecl LightmapInfo_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct World_s *v2; // ecx
  struct DynCubeObj_s *ptManualRedrawList; // edx
  struct DynCubeObj_s *ptPrev; // edx

  QVector_AddElement(LightmapInfo_ptLightmapInfoVector, ptQTask);
  v2 = World_ptActiveWorld;
  LOBYTE(ptQTask[2].ptParent) = 0;
  LOBYTE(ptQTask[2].eQTaskType) = 0;
  HIBYTE(ptQTask[2].ptParent) = 0;
  BYTE2(ptQTask[2].ptParent) = 0;
  BYTE1(ptQTask[2].ptParent) = 0;
  HIBYTE(ptQTask[2].eQTaskType) = 0;
  ptQTask[3].ptNext = (struct QTask_s *)150;
  ptQTask[3].tQTaskChildren.ptHead = nullptr;
  ptQTask[3].ptPrev = nullptr;
  ptQTask[3].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[3].tQTaskChildren.ptTail = (struct QTask_s *)1;
  ptQTask[3].ptParent = nullptr;
  *(_DWORD *)&ptQTask[3].eQTaskType = 0;
  ptQTask[4].ptNext = nullptr;
  ptQTask[4].ptPrev = nullptr;
  ptQTask[3].tQTaskRefList.ptHead = nullptr;
  ptManualRedrawList = v2->ptManualRedrawList;
  if ( ptManualRedrawList )
  {
    ptManualRedrawList->ptPrev = (struct DynCubeObj_s *)ptQTask;
    v2->ptManualRedrawList->ptPrev->ptNext = v2->ptManualRedrawList;
    ptPrev = v2->ptManualRedrawList->ptPrev;
    v2->ptManualRedrawList = ptPrev;
    ptPrev->ptPrev = nullptr;
  }
  else
  {
    v2->ptManualRedrawList = (struct DynCubeObj_s *)ptQTask;
    ptQTask[2].tQTaskChildren.ptTail = nullptr;
    v2->ptManualRedrawList->ptPrev = nullptr;
  }
}

// source: h/2/lightmapinfo.c:1623  [anchor-mhash]
void __cdecl LightmapInfo_DeleteHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptMiddle; // eax
  struct QTask_s *ptTail; // eax

  ptMiddle = ptQTask[2].tQTaskChildren.ptMiddle;
  if ( ptMiddle )
    ptMiddle[2].tQTaskChildren.ptTail = ptQTask[2].tQTaskChildren.ptTail;
  else
    World_ptActiveWorld->ptManualRedrawList = (struct DynCubeObj_s *)ptQTask[2].tQTaskChildren.ptTail;
  ptTail = ptQTask[2].tQTaskChildren.ptTail;
  if ( ptTail )
    ptTail[2].tQTaskChildren.ptMiddle = ptQTask[2].tQTaskChildren.ptMiddle;
  QVector_RemoveElementByPointer(LightmapInfo_ptLightmapInfoVector, ptQTask);
}

// source: h/2/lightmapinfo.c:1685  [anchor-mhash]
void __cdecl LightmapInfo_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { float isForceCreateNew; };
    struct { char igi2_o1[4]; unsigned int _iVirModel; };
    struct { char igi2_o2[8]; struct EnumerateLightmapVirModelsContext_t _tContext; };
    char igi2_extent[40];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *ptParent; // edx
  struct QTask_s **p_ptPrev; // edx
  void **v5; // edi
  struct QVector_s *v6; // eax
  struct QTask_s *v7; // eax
  struct QVector_s *ptLightmapVirModelVector; // eax
  unsigned int v9; // ebp
  struct Mesh3D_LightmapVirModel_t *v10; // edi
  struct Mesh3D_LightmapList_s *ptLightmapList; // eax
  int v12; // edx
  int v13; // ecx
  struct QReference_s *v14; // edx
  char ptQTaska = *(char *)&ptQTask; // [esp+34h] [ebp+4h] ARGSLOT

  ptParent = ptQTask->ptParent;
  if ( QTask_IsQTaskTypeDerived(ptParent->eQTaskType, SectorObject_eQTaskType) )
  {
    p_ptPrev = &ptParent[10].ptPrev;
    *p_ptPrev = ptQTask[3].ptParent;
    p_ptPrev[1] = *(struct QTask_s **)&ptQTask[3].eQTaskType;
    p_ptPrev[2] = ptQTask[4].ptNext;
  }
  if ( AppContext_tAppContext.isWinMessageInput
    && AppContext_tAppContext.isLightmapsUsed == false
    && (LOBYTE(ptQTask[2].eQTaskType) || BYTE2(ptQTask[2].ptParent) || HIBYTE(ptQTask[2].eQTaskType)) )
  {
    memset(&igi2_frame._tContext.nModelVariation, 255, 12);
    ptQTask[3].tQTaskChildren.ptHead = nullptr;
    ptQTask[3].ptPrev = nullptr;
    LightmapInfo_nNumTexels = 0;
    LightmapInfo_nNumLightTexels = 0;
    igi2_frame._tContext.ptLightmapInfo = (struct LightmapInfo_s *)ptQTask;
    v5 = (void **)Mem_AllocFn(400, 4);
    v6 = (struct QVector_s *)Mem_AllocFn(24, 4);
    v6->tPrivate.nElements = 0;
    v6->tPrivate.isPrivateMem = false;
    v6->tPrivate.papxElement = v5;
    v6->tPrivate.isStrictOrder = false;
    v6->tPrivate.nArraySize = 100;
    v6->tPrivate.nReallocSize = 100;
    igi2_frame._tContext.tAmbientColor.vY = Mesh3D_atAmbientColor[1].vY;
    igi2_frame._tContext.ptLightmapVirModelVector = v6;
    igi2_frame._tContext.tAmbientColor.vZ = Mesh3D_atAmbientColor[1].vZ;
    v7 = ptQTask->ptParent;
    igi2_frame._tContext.tAmbientColor.vX = Mesh3D_atAmbientColor[1].vX;
    ((void (__cdecl *)(struct QTask_s *, struct EnumerateLightmapVirModelsContext_t *))QTask_aatQTaskFinalEvent[LightmapInfo_eEnumerateLightmapVirModelsEvent][v7->eQTaskType].pfHandler)(
      v7,
      &igi2_frame._tContext);
    ptLightmapVirModelVector = igi2_frame._tContext.ptLightmapVirModelVector;
    v9 = 0;
    for ( igi2_frame._iVirModel = 0; v9 < igi2_frame._tContext.ptLightmapVirModelVector->tPrivate.nElements; igi2_frame._iVirModel = v9 )
    {
      v10 = (struct Mesh3D_LightmapVirModel_t *)ptLightmapVirModelVector->tPrivate.papxElement[v9];
      if ( GlobalLightQTask_ptGlobalLight )
        igi2_frame.isForceCreateNew = GlobalLightQTask_ptGlobalLight->vRadiosityIntensity;
      else
        igi2_frame.isForceCreateNew = 0.0;
      LightmapInfo_CreateLightmapList(
        v10,
        (enum bool)SLOBYTE(ptQTask[2].eQTaskType),
        igi2_frame.isForceCreateNew,
        (char *)&ptQTask[4].tQTaskChildren,
        v9);
      ptLightmapList = v10->ptLightmapList;
      v12 = 0;
      if ( v10->ptLightmapList->nNumLightmaps > 0 )
      {
        ptQTaska = ptQTask[2].eQTaskType;
        v13 = 0;
        do
        {
          ptQTask[3].tQTaskChildren.ptHead = (struct QTask_s *)((char *)ptQTask[3].tQTaskChildren.ptHead
                                                              + ptLightmapList->atLightmap[v13].nWidth
                                                              * ptLightmapList->atLightmap[v13].nHeight);
          if ( ptQTaska || !v10->isLightmapsUploaded )
            ptQTask[3].ptPrev = (struct QTask_s *)((char *)ptQTask[3].ptPrev
                                                 + v10->ptLightmapList->atLightmap[v13].nWidth
                                                 * v10->ptLightmapList->atLightmap[v13].nHeight);
          ptLightmapList = v10->ptLightmapList;
          ++v12;
          ++v13;
        }
        while ( v12 < v10->ptLightmapList->nNumLightmaps );
        v9 = igi2_frame._iVirModel;
      }
      ptLightmapVirModelVector = igi2_frame._tContext.ptLightmapVirModelVector;
      ++v9;
    }
    QVector_Delete(ptLightmapVirModelVector);
    v14 = (struct QReference_s *)LightmapInfo_nNumLightTexels;
    ptQTask[3].tQTaskRefList.ptMiddle = (struct QReference_s *)LightmapInfo_nNumTexels;
    ptQTask[3].tQTaskRefList.ptTail = v14;
  }
  if ( LOBYTE(ptQTask[2].eQTaskType) || BYTE2(ptQTask[2].ptParent) )
  {
    LOBYTE(ptQTask[2].eQTaskType) = 0;
    BYTE2(ptQTask[2].ptParent) = 0;
    LightmapInfo_isCancel = false;
  }
}

// source: h/2/lightmapinfo.c:1814  [anchor-mhash]
void __cdecl LightmapInfo_UpdateInternalDataAfterLoadHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { int iVirModel; };
    struct { char igi2_o1[8]; unsigned int _iVirModel; };
    struct { char igi2_o2[12]; struct EnumerateLightmapVirModelsContext_t _tContext; };
    char igi2_extent[44];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  void **v2; // esi
  struct QVector_s *v3; // eax
  struct QTask_s *ptParent; // eax
  struct QVector_s *ptLightmapVirModelVector; // eax
  unsigned int v6; // ebp
  struct Mesh3D_LightmapVirModel_t *v7; // esi
  int v8; // eax
  struct QReference_s *v9; // ecx
  unsigned __int16 eQTaskType; // dx
  struct Mesh3D_LightmapList_s *ptLightmapList; // eax
  int v12; // edx
  int v13; // ecx
  struct QReference_s *v14; // edx
  float ptQTaska = *(float *)&ptQTask; // [esp+38h] [ebp+4h] ARGSLOT

  ptQTask[3].tQTaskChildren.ptHead = nullptr;
  igi2_frame.iVirModel = 0;
  LightmapInfo_nNumTexels = 0;
  LightmapInfo_nNumLightTexels = 0;
  if ( AppContext_tAppContext.isWinMessageInput && AppContext_tAppContext.isLightmapsUsed == false )
  {
    memset(&igi2_frame._tContext.nModelVariation, 255, 12);
    igi2_frame._tContext.ptLightmapInfo = (struct LightmapInfo_s *)ptQTask;
    v2 = (void **)Mem_AllocFn(400, 4);
    v3 = (struct QVector_s *)Mem_AllocFn(24, 4);
    v3->tPrivate.nElements = 0;
    v3->tPrivate.isPrivateMem = false;
    v3->tPrivate.papxElement = v2;
    v3->tPrivate.isStrictOrder = false;
    v3->tPrivate.nArraySize = 100;
    v3->tPrivate.nReallocSize = 100;
    igi2_frame._tContext.tAmbientColor.vZ = Mesh3D_atAmbientColor[1].vZ;
    igi2_frame._tContext.ptLightmapVirModelVector = v3;
    igi2_frame._tContext.tAmbientColor.vX = Mesh3D_atAmbientColor[1].vX;
    ptParent = ptQTask->ptParent;
    igi2_frame._tContext.tAmbientColor.vY = Mesh3D_atAmbientColor[1].vY;
    ((void (__cdecl *)(struct QTask_s *, struct EnumerateLightmapVirModelsContext_t *))QTask_aatQTaskFinalEvent[LightmapInfo_eEnumerateLightmapVirModelsEvent][ptParent->eQTaskType].pfHandler)(
      ptParent,
      &igi2_frame._tContext);
    ptLightmapVirModelVector = igi2_frame._tContext.ptLightmapVirModelVector;
    v6 = 0;
    for ( igi2_frame._iVirModel = 0; v6 < igi2_frame._tContext.ptLightmapVirModelVector->tPrivate.nElements; igi2_frame._iVirModel = v6 )
    {
      v7 = (struct Mesh3D_LightmapVirModel_t *)ptLightmapVirModelVector->tPrivate.papxElement[v6];
      v8 = 0;
      while ( 1 )
      {
        v9 = Level_atLevelQTaskID[v8];
        if ( v9 )
        {
          if ( v9->pxObject == v7->ptQTask )
            break;
        }
        if ( ++v8 >= 4096 )
          goto LABEL_10;
      }
      if ( v8 != -1 )
        goto LABEL_16;
LABEL_10:
      eQTaskType = v7->ptQTask->eQTaskType;
      if ( QTask_IsQTaskTypeDerived(eQTaskType, RigidMagicObj_eQTaskType) == false
        && QTask_IsQTaskTypeDerived(eQTaskType, Sector_eQTaskType) == false )
      {
        if ( GlobalLightQTask_ptGlobalLight )
          ptQTaska = GlobalLightQTask_ptGlobalLight->vRadiosityIntensity;
        else
          ptQTaska = 0.0;
        LightmapInfo_CreateLightmapList(v7, false, ptQTaska, (char *)&ptQTask[4].tQTaskChildren, -1);
        goto LABEL_20;
      }
LABEL_16:
      if ( GlobalLightQTask_ptGlobalLight )
        LightmapInfo_CreateLightmapList(
          v7,
          false,
          GlobalLightQTask_ptGlobalLight->vRadiosityIntensity,
          (char *)&ptQTask[4].tQTaskChildren,
          igi2_frame.iVirModel);
      else
        LightmapInfo_CreateLightmapList(v7, false, 0.0, (char *)&ptQTask[4].tQTaskChildren, igi2_frame.iVirModel);
      ++igi2_frame.iVirModel;
LABEL_20:
      ptLightmapList = v7->ptLightmapList;
      v12 = 0;
      if ( v7->ptLightmapList->nNumLightmaps > 0 )
      {
        v13 = 0;
        do
        {
          ptQTask[3].tQTaskChildren.ptHead = (struct QTask_s *)((char *)ptQTask[3].tQTaskChildren.ptHead
                                                              + ptLightmapList->atLightmap[v13].nWidth
                                                              * ptLightmapList->atLightmap[v13].nHeight);
          if ( !v7->isLightmapsUploaded )
            ptQTask[3].ptPrev = (struct QTask_s *)((char *)ptQTask[3].ptPrev
                                                 + v7->ptLightmapList->atLightmap[v13].nWidth
                                                 * v7->ptLightmapList->atLightmap[v13].nHeight);
          ptLightmapList = v7->ptLightmapList;
          ++v12;
          ++v13;
        }
        while ( v12 < v7->ptLightmapList->nNumLightmaps );
        v6 = igi2_frame._iVirModel;
      }
      ptLightmapVirModelVector = igi2_frame._tContext.ptLightmapVirModelVector;
      ++v6;
    }
    QVector_Delete(ptLightmapVirModelVector);
    v14 = (struct QReference_s *)LightmapInfo_nNumLightTexels;
    ptQTask[3].tQTaskRefList.ptMiddle = (struct QReference_s *)LightmapInfo_nNumTexels;
    ptQTask[3].tQTaskRefList.ptTail = v14;
  }
}

// source: h/2/lightmapinfo.c:1883  [size]
void __cdecl LightmapInfo_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = LightmapInfo_ptParameterList;
}

// source: h/2/lightmapinfo.c:1899  [anchor-hash]
void __cdecl LightmapInfo_QEDCreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *((_DWORD *)pxContext + 1) = QTask_GetFirstChildOfType(*((struct QTask_s **)pxContext + 2), LightmapInfo_eQTaskType) == nullptr;
}

// source: h/2/lightmapinfo.c:2089  [size]
void __cdecl QTask_EnumerateLightmapVirModelsHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *ptHead; // eax
  int v3; // edx
  struct QTask_s *v4; // ecx
  void (__cdecl *pfHandler)(struct QTask_s *, void *); // ecx
  int v6; // edx

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
      pfHandler = (void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[LightmapInfo_eEnumerateLightmapVirModelsEvent][ptHead->eQTaskType].pfHandler;
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
}

// source: h/2/lightmapinfo.c:2102  [anchor-mhash]
void __cdecl RigidDynCubeObj_EnumerateLightmapVirModelsHandler(struct QTask_s *ptQTask, void *pxContext)
{
  unsigned __int16 v2; // dx
  _DWORD *p_tMyContext; // ebx
  int v4; // eax
  struct QReference_s *v5; // ecx
  int v6; // esi
  struct QTask_s *ptNext; // eax
  int ptHead; // eax
  int v9; // edx
  struct QTask_s *v10; // ecx
  void (__cdecl *pfHandler)(int, _DWORD *); // ecx
  int v12; // edx
  struct QTask_s *v13; // eax
  int v14; // eax
  struct QTask_s *v15; // ecx
  void (__cdecl *v16)(int, _DWORD *); // ecx
  int v17; // edx
  struct QTask_s *v18; // eax
  struct QTask_s *v19; // ecx
  void (__cdecl *v20)(struct QTask_s *, _DWORD *); // ecx
  int v21; // edx
  struct EnumerateLightmapVirModelsContext_t tMyContext; // [esp+10h] [ebp-20h] BYREF

  v2 = LightmapInfo_eQTaskType;
  p_tMyContext = pxContext;
  qmemcpy(&tMyContext, pxContext, sizeof(tMyContext));
  if ( !QTask_GetFirstChildOfType(ptQTask, LightmapInfo_eQTaskType)
    || QTask_GetFirstChildOfType(ptQTask, v2) == *(struct QTask_s **)pxContext )
  {
    v4 = 0;
    while ( 1 )
    {
      v5 = Level_atLevelQTaskID[v4];
      if ( v5 )
      {
        if ( v5->pxObject == ptQTask )
          break;
      }
      if ( ++v4 >= 4096 )
      {
        v6 = -1;
        goto LABEL_10;
      }
    }
    v6 = v4;
    if ( v4 != -1 )
    {
      tMyContext.nParentQTaskID = v4;
      tMyContext.nSubQTaskID = 0;
      tMyContext.nModelVariation = 0;
    }
LABEL_10:
    LightmapInfo_AddLightmapVirModelToEnumeration(
      ptQTask,
      *(struct LODVirModel_s **)&ptQTask[2].eQTaskType,
      (struct Mesh3D_LightmapVirModel_t *(*)[5])&ptQTask[7].tQTaskRefList,
      &tMyContext);
    if ( v6 != -1 )
      p_tMyContext = &tMyContext;
    ++p_tMyContext[3];
    ptNext = ptQTask[3].ptNext;
    if ( ptNext && (ptHead = (int)ptNext->tQTaskChildren.ptHead, *(_DWORD *)ptHead) && ptHead )
    {
      v9 = QTask_nProtectedQTaskStackOffset;
      do
      {
        if ( *(_DWORD *)ptHead )
          v10 = **(_DWORD **)ptHead != 0 ? *(struct QTask_s **)ptHead : nullptr;
        else
          v10 = nullptr;
        QTask_atProtectedQTaskStack[v9].ptQTask = v10;
        pfHandler = (void (__cdecl *)(int, _DWORD *))QTask_aatQTaskFinalEvent[LightmapInfo_eEnumerateLightmapVirModelsEvent][*(unsigned __int16 *)(ptHead + 36)].pfHandler;
        v12 = v9 + 1;
        QTask_nProtectedQTaskStackOffset = v12;
        if ( pfHandler )
        {
          pfHandler(ptHead, p_tMyContext);
          v12 = QTask_nProtectedQTaskStackOffset;
        }
        ptHead = dword_849C7DC[v12];
        v9 = v12 - 1;
        QTask_nProtectedQTaskStackOffset = v9;
      }
      while ( ptHead );
    }
    else
    {
      v9 = QTask_nProtectedQTaskStackOffset;
    }
    if ( QTask_IsQTaskTypeDerived(ptQTask->eQTaskType, SectorObject_eQTaskType) )
    {
      p_tMyContext[5] = ptQTask[10].ptPrev;
      p_tMyContext[6] = ptQTask[10].tQTaskChildren.ptHead;
      p_tMyContext[7] = ptQTask[10].tQTaskChildren.ptMiddle;
      v13 = ptQTask[10].ptNext;
      if ( v13 )
      {
        v14 = (int)v13->tQTaskChildren.ptHead;
        if ( *(_DWORD *)v14 )
        {
          for ( ; v14; QTask_nProtectedQTaskStackOffset = v9 )
          {
            if ( *(_DWORD *)v14 )
              v15 = **(_DWORD **)v14 != 0 ? *(struct QTask_s **)v14 : nullptr;
            else
              v15 = nullptr;
            QTask_atProtectedQTaskStack[v9].ptQTask = v15;
            v16 = (void (__cdecl *)(int, _DWORD *))QTask_aatQTaskFinalEvent[LightmapInfo_eEnumerateLightmapVirModelsEvent][*(unsigned __int16 *)(v14 + 36)].pfHandler;
            v17 = v9 + 1;
            QTask_nProtectedQTaskStackOffset = v17;
            if ( v16 )
            {
              v16(v14, p_tMyContext);
              v17 = QTask_nProtectedQTaskStackOffset;
            }
            v14 = dword_849C7DC[v17];
            v9 = v17 - 1;
          }
        }
      }
      *(struct real32x3_t *)(p_tMyContext + 5) = Mesh3D_atAmbientColor[1];
    }
    v18 = ptQTask->tQTaskChildren.ptHead;
    if ( v18->ptNext && v18 )
    {
      do
      {
        if ( v18->ptNext )
          v19 = v18->ptNext->ptNext != nullptr ? v18->ptNext : nullptr;
        else
          v19 = nullptr;
        QTask_atProtectedQTaskStack[v9].ptQTask = v19;
        v20 = (void (__cdecl *)(struct QTask_s *, _DWORD *))QTask_aatQTaskFinalEvent[LightmapInfo_eEnumerateLightmapVirModelsEvent][v18->eQTaskType].pfHandler;
        v21 = v9 + 1;
        QTask_nProtectedQTaskStackOffset = v21;
        if ( v20 )
        {
          v20(v18, p_tMyContext);
          v21 = QTask_nProtectedQTaskStackOffset;
        }
        v18 = (struct QTask_s *)dword_849C7DC[v21];
        v9 = v21 - 1;
        QTask_nProtectedQTaskStackOffset = v9;
      }
      while ( v18 );
    }
  }
}

// source: h/2/lightmapinfo.c:2357  [anchor-strings]
void __cdecl LightmapInfo_AddLightmapVirModelToEnumeration(
        struct QTask_s *ptQTask,
        struct LODVirModel_s *ptLODVirModel,
        struct Mesh3D_LightmapVirModel_t *(*paptLightmapVirModel)[5],
        struct EnumerateLightmapVirModelsContext_t *ptContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { int v21; };
    struct { char igi2_o1[4]; int v22; };
    struct { char igi2_o2[8]; char zFilename[256]; };
    char igi2_extent[264];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct LODVirModel_s *v4; // ebx
  int v5; // ebp
  int nModelVariation; // eax
  struct QHashTable_s *v7; // esi
  unsigned int v8; // eax
  struct VirModel_s *v9; // edi
  struct Mesh3D_Mesh_t *ptMesh; // eax
  _DWORD *pxRenderMesh; // eax
  struct QObjectVector_s *v12; // edi
  unsigned int *p_nAllocated; // esi
  char *v14; // eax
  char v15; // cl
  struct QHashTable_s *v16; // esi
  unsigned int v17; // eax
  struct PalInfo **v18; // ecx
  struct QVector_s *ptLightmapVirModelVector; // esi
  unsigned int nElements; // ebp

  v4 = ptLODVirModel;
  if ( ptLODVirModel )
  {
    v5 = 0;
    if ( ptLODVirModel->nLOD > 0 )
    {
      igi2_frame.v22 = (char *)paptLightmapVirModel - (char *)ptLODVirModel;
      do
      {
        nModelVariation = ptContext->nModelVariation;
        igi2_frame.v21 = v5 + 1;
        if ( nModelVariation )
          sprintf(
            igi2_frame.zFilename,
            "%04d%c_%04d_%1d.olm",
            ptContext->nParentQTaskID,
            byte_6B6604[nModelVariation],
            ptContext->nSubQTaskID,
            v5 + 1);
        else
          sprintf(igi2_frame.zFilename, "%04d_%04d_%1d.olm", ptContext->nParentQTaskID, ptContext->nSubQTaskID, v5 + 1);
        v7 = LightmapInfo_ptLightmapVirModelHashTable;
        v8 = LightmapInfo_ptLightmapVirModelHashTable->tPrivate.pfHashFunction(
               LightmapInfo_ptLightmapVirModelHashTable->tPrivate.nHashTableSize,
               igi2_frame.zFilename);
        v9 = (struct VirModel_s *)((int  (__cdecl *)(struct QHashTable_s *, unsigned int, const void *))LightmapInfo_ptLightmapVirModelHashTable->tPrivate.pfFindElement)(v7, v8, (const void *)(igi2_frame.zFilename));
        if ( !v9 )
        {
          ptMesh = v4->aptVirModel[0]->ptModel->ptMesh;
          if ( ptMesh->eRenderMeshType == MESH3D_RENDERMESHTYPE_DIRECT3D_BUILDING )
          {
            pxRenderMesh = ptMesh->pxRenderMesh;
            if ( pxRenderMesh[2] )
            {
              if ( pxRenderMesh )
              {
                v12 = LightmapInfo_ptLightmapVirModelVector;
                p_nAllocated = &LightmapInfo_ptLightmapVirModelVector->nAllocated;
                if ( LightmapInfo_ptLightmapVirModelVector->nAllocated == LightmapInfo_ptLightmapVirModelVector->nSize )
                  QObjectVector_Realloc(
                    LightmapInfo_ptLightmapVirModelVector,
                    LightmapInfo_ptLightmapVirModelVector->nReallocSize);
                v9 = (struct VirModel_s *)v12->papxElement[(*p_nAllocated)++];
                *(struct VirModel_s **)((char *)v4->aptVirModel + igi2_frame.v22) = v9;
                v9->ptNext = nullptr;
                v9->nNumTexInfo = v5;
                v9[1].ptPrev = nullptr;
                v9[1].ptNext = (struct VirModel_s *)ptLODVirModel->nLOD;
                v9->ptPrev = v4->aptVirModel[0];
                v14 = igi2_frame.zFilename;
                do
                {
                  v15 = *v14;
                  v14[(char *)v9 - igi2_frame.zFilename + 36] = *v14;
                  ++v14;
                }
                while ( v15 );
                v16 = LightmapInfo_ptLightmapVirModelHashTable;
                v17 = LightmapInfo_ptLightmapVirModelHashTable->tPrivate.pfHashFunction(
                        LightmapInfo_ptLightmapVirModelHashTable->tPrivate.nHashTableSize,
                        igi2_frame.zFilename);
                LightmapInfo_ptLightmapVirModelHashTable->tPrivate.pfCreateElement(v16, v17, (const void *)(igi2_frame.zFilename), (const void *)(v9));
              }
            }
          }
        }
        *(struct VirModel_s **)((char *)v4->aptVirModel + igi2_frame.v22) = v9;
        if ( v9 )
        {
          if ( QTask_IsQTaskTypeDerived(ptQTask->eQTaskType, SplineObjSegment_eQTaskType) )
            v9->ptModel = (struct Model_s *)&unk_6B6620;
          else
            v9->ptModel = (struct Model_s *)&ptQTask[3].ptPrev;
          v9->pptTexInfo = (struct TexInfo_s **)&ptQTask[1];
          v18 = *(struct PalInfo ***)&ptQTask[6].eQTaskType;
          v9->pzName = (char *)ptQTask;
          v9->pptPalInfo = v18;
          ptLightmapVirModelVector = ptContext->ptLightmapVirModelVector;
          nElements = ptLightmapVirModelVector->tPrivate.nElements;
          if ( ptLightmapVirModelVector->tPrivate.nElements == ptLightmapVirModelVector->tPrivate.nArraySize )
            QVector_Realloc(ptLightmapVirModelVector, 1u);
          if ( nElements < ptLightmapVirModelVector->tPrivate.nElements - 1 )
            memmove(
              &ptLightmapVirModelVector->tPrivate.papxElement[nElements + 1],
              &ptLightmapVirModelVector->tPrivate.papxElement[nElements],
              4 * (ptLightmapVirModelVector->tPrivate.nElements - nElements));
          ++ptLightmapVirModelVector->tPrivate.nElements;
          ptLightmapVirModelVector->tPrivate.papxElement[nElements] = v9;
        }
        v5 = igi2_frame.v21;
        v4 = (struct LODVirModel_s *)((char *)v4 + 4);
      }
      while ( igi2_frame.v21 < ptLODVirModel->nLOD );
    }
  }
}

// source: h/2/lightmapinfo.c:2480  [size]
__int16 __cdecl LightmapInfo_GetEnumerateLightmapVirModelsEvent()
{
  return LightmapInfo_eEnumerateLightmapVirModelsEvent;
}

// source: h/2/lightmapinfo.c:2493  [anchor-strings]
void __cdecl LightmapInfo_LoadResource()
{
  char *v0; // ecx
  void *v1; // eax
  struct QObjectVector_s *v2; // esi
  struct QHashTable_s *v3; // esi
  void *v4; // edi
  unsigned int v5; // eax
  char zFilename[4]; // [esp+8h] [ebp-4h] BYREF

  sprintf(LightmapInfo_zResource, "MISSION:%s/%s", "lightmaps", "lightmaps.res");
  if ( Resource_IsLoadedInternal(LightmapInfo_zResource, nullptr) || File_Exists(LightmapInfo_zResource) )
  {
    sprintf(LightmapInfo_zResource, "MISSION:%s/%s", "lightmaps", "lightmaps.res");
    if ( Resource_IsLoadedInternal(LightmapInfo_zResource, (struct Resource_s **)zFilename) )
    {
      *(_DWORD *)(*(_DWORD *)zFilename + 44) = 1;
    }
    else
    {
      Game_MPRunNetwork(v0);
      v1 = File_Load(LightmapInfo_zResource, (unsigned int *)zFilename);
      if ( !v1 )
      {
        LDebug_Error("Failed to load resource: '%s'", LightmapInfo_zResource);
        abort();
      }
      Resource_ParseFile(File_zLastSubstitutedPath, v1, *(unsigned int *)zFilename);
    }
  }
  v2 = (struct QObjectVector_s *)Mem_AllocFn(52, 4);
  v2->isStrictOrder = false;
  v2->nSize = 0;
  v2->nAllocated = 0;
  v2->nReallocSize = 10;
  v2->papxElement = nullptr;
  v2->nElementSize = 56;
  v2->tMemPool.nBlocks = 0;
  v2->tMemPool.nAllocatedBlocks = 0;
  v2->tMemPool.nAlignment = 4;
  v2->tMemPool.nBlockSize = 56;
  v2->tMemPool.nReAllocBlocks = 10;
  v2->tMemPool.tMemPoolFreeList.ptHead = nullptr;
  v2->tMemPool.tMemPoolSegmentList.ptHead = nullptr;
  MemPool_ReAlloc(&v2->tMemPool, 0xAu);
  QObjectVector_Realloc(v2, 0xAu);
  LightmapInfo_ptLightmapVirModelVector = v2;
  v3 = (struct QHashTable_s *)Mem_AllocFn(40, 4);
  v3->tPrivate.nHashTableSize = 256;
  v3->tPrivate.pfHashFunction = QHashTable_StringHashFunction;
  v3->tPrivate.pfCompareKey = QHashTable_StringCompareKeyFunction;
  v3->tPrivate.pfDuplicateKey = QHashTable_StringDuplicateKeyFunction;
  v3->tPrivate.pfCreateElement = QHashTable_CreateElementChained;
  v3->tPrivate.pfFindElement = QHashTable_FindElementChained;
  v3->tPrivate.pfDeleteElement = QHashTable_DeleteElementChained;
  v3->tPrivate.pfMap = QHashTable_MapChained;
  v3->tPrivate.nEntries = 0;
  v4 = Mem_AllocFn(3072, 4);
  v5 = 0;
  v3->tPrivate.papxElement = v4;
  memset(v4, 0, 0xC00u);
  do
  {
    *(_DWORD *)((char *)v3->tPrivate.papxElement + v5) = (char *)v3->tPrivate.papxElement + v5 + 4;
    *(_DWORD *)((char *)v3->tPrivate.papxElement + v5 + 8) = (char *)v3->tPrivate.papxElement + v5;
    *(_DWORD *)((char *)v3->tPrivate.papxElement + v5 + 4) = 0;
    *(_DWORD *)((char *)v3->tPrivate.papxElement + v5 + 12) = (char *)v3->tPrivate.papxElement + v5 + 16;
    *(_DWORD *)((char *)v3->tPrivate.papxElement + v5 + 20) = (char *)v3->tPrivate.papxElement + v5 + 12;
    *(_DWORD *)((char *)v3->tPrivate.papxElement + v5 + 16) = 0;
    *(_DWORD *)((char *)v3->tPrivate.papxElement + v5 + 24) = (char *)v3->tPrivate.papxElement + v5 + 28;
    *(_DWORD *)((char *)v3->tPrivate.papxElement + v5 + 32) = (char *)v3->tPrivate.papxElement + v5 + 24;
    *(_DWORD *)((char *)v3->tPrivate.papxElement + v5 + 28) = 0;
    *(_DWORD *)((char *)v3->tPrivate.papxElement + v5 + 36) = (char *)v3->tPrivate.papxElement + v5 + 40;
    *(_DWORD *)((char *)v3->tPrivate.papxElement + v5 + 44) = (char *)v3->tPrivate.papxElement + v5 + 36;
    *(_DWORD *)((char *)v3->tPrivate.papxElement + v5 + 40) = 0;
    *(_DWORD *)((char *)v3->tPrivate.papxElement + v5 + 48) = (char *)v3->tPrivate.papxElement + v5 + 52;
    *(_DWORD *)((char *)v3->tPrivate.papxElement + v5 + 56) = (char *)v3->tPrivate.papxElement + v5 + 48;
    *(_DWORD *)((char *)v3->tPrivate.papxElement + v5 + 52) = 0;
    *(_DWORD *)((char *)v3->tPrivate.papxElement + v5 + 60) = (char *)v3->tPrivate.papxElement + v5 + 64;
    *(_DWORD *)((char *)v3->tPrivate.papxElement + v5 + 68) = (char *)v3->tPrivate.papxElement + v5 + 60;
    *(_DWORD *)((char *)v3->tPrivate.papxElement + v5 + 64) = 0;
    *(_DWORD *)((char *)v3->tPrivate.papxElement + v5 + 72) = (char *)v3->tPrivate.papxElement + v5 + 76;
    *(_DWORD *)((char *)v3->tPrivate.papxElement + v5 + 80) = (char *)v3->tPrivate.papxElement + v5 + 72;
    *(_DWORD *)((char *)v3->tPrivate.papxElement + v5 + 76) = 0;
    *(_DWORD *)((char *)v3->tPrivate.papxElement + v5 + 84) = (char *)v3->tPrivate.papxElement + v5 + 88;
    *(_DWORD *)((char *)v3->tPrivate.papxElement + v5 + 92) = (char *)v3->tPrivate.papxElement + v5 + 84;
    *(_DWORD *)((char *)v3->tPrivate.papxElement + v5 + 88) = 0;
    v5 += 96;
  }
  while ( v5 < 0xC00 );
  LightmapInfo_ptLightmapVirModelHashTable = v3;
}

// source: h/2/lightmapinfo.c:2515  [anchor-strings]
void __cdecl LightmapInfo_FreeResource()
{
  int v0; // eax
  struct QObjectVector_s *v1; // eax
  unsigned int i; // esi
  struct Mesh3D_LightmapList_s **v3; // edi
  struct QHashTable_s *v4; // esi
  int v5; // esi
  char zFilename[4]; // [esp+Ch] [ebp-4h] BYREF

  sprintf(LightmapInfo_zResource, "MISSION:%s/%s", "lightmaps", "lightmaps.res");
  if ( Resource_IsLoadedInternal(LightmapInfo_zResource, nullptr) )
  {
    sprintf(LightmapInfo_zResource, "MISSION:%s/%s", "lightmaps", "lightmaps.res");
    if ( Resource_IsLoadedInternal(LightmapInfo_zResource, (struct Resource_s **)zFilename) )
    {
      v0 = *(_DWORD *)(*(_DWORD *)zFilename + 36);
      if ( v0 != 3 && v0 != 1 )
        Resource_Remove(*(struct Resource_s **)zFilename);
    }
  }
  v1 = LightmapInfo_ptLightmapVirModelVector;
  for ( i = 0; i < v1->nAllocated; ++i )
  {
    v3 = (struct Mesh3D_LightmapList_s **)v1->papxElement[i];
    LightmapInfo_DeleteLightmapList(*v3);
    v1 = LightmapInfo_ptLightmapVirModelVector;
    *v3 = nullptr;
  }
  QObjectVector_Delete(v1);
  v4 = LightmapInfo_ptLightmapVirModelHashTable;
  LightmapInfo_ptLightmapVirModelVector = nullptr;
  QHashTable_DeAlloc(LightmapInfo_ptLightmapVirModelHashTable);
  if ( v4 )
  {
    v5 = *(_DWORD *)((unsigned int)&v4[-1].tPrivate.pfMap & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v5);
    memset(*(void **)(v5 + 8), 0xCDu, *(_DWORD *)(v5 + 16));
    free((void *)v5);
  }
  LightmapInfo_ptLightmapVirModelHashTable = nullptr;
}

// source: h/2/lightmapinfo.c:2549  [anchor-mhash]
struct Hemicube_t *__cdecl LightmapInfo_NewHemicube(int nSize)
{
  struct Hemicube_t *v1; // esi
  int v2; // edi
  void **apvHalfZBuffer; // ebx
  int v4; // ebp
  int v5; // edx
  int v6; // ecx
  double v7; // st7
  double v8; // st6
  double v9; // st4
  double v10; // st4
  double v11; // st6
  int v12; // edi
  int v13; // ecx
  double v14; // st7
  double v15; // st6
  double v16; // st6
  double v17; // st5
  double v18; // st4
  double v19; // st6
  int nY; // [esp+10h] [ebp-4h]
  float nYc; // [esp+10h] [ebp-4h]
  int nYa; // [esp+10h] [ebp-4h]
  int nYb; // [esp+10h] [ebp-4h]
  int nSizea = *(int *)&nSize; // [esp+18h] [ebp+4h] ARGSLOT
  float nSized = *(float *)&nSize; // [esp+18h] [ebp+4h] ARGSLOT
  int nSizeb = *(int *)&nSize; // [esp+18h] [ebp+4h] ARGSLOT
  int nSizec = *(int *)&nSize; // [esp+18h] [ebp+4h] ARGSLOT

  v1 = (struct Hemicube_t *)Mem_AllocFn(276, 4);
  v1->nSize = nSize;
  v1->nHalfSize = nSize >> 1;
  v1->pnMainFrameBuffer = (int *)Mem_AllocFn(4 * nSize * nSize, 4);
  v1->pvMainZBuffer = (float *)Mem_AllocFn(4 * nSize * nSize, 4);
  v1->pvMainDeltaFormFactor = (float *)Mem_AllocFn(4 * nSize * nSize, 4);
  v2 = 4 * nSize * (nSize >> 1);
  v1->pvHalfDeltaFormFactor = (float *)Mem_AllocFn(v2, 4);
  apvHalfZBuffer = (void **)v1->apvHalfZBuffer;
  v4 = 4;
  do
  {
    *(apvHalfZBuffer - 5) = Mem_AllocFn(v2, 4);
    *apvHalfZBuffer++ = Mem_AllocFn(v2, 4);
    --v4;
  }
  while ( v4 );
  v5 = 0;
  for ( nY = 0; v5 < v1->nSize; nY = v5 )
  {
    v6 = 0;
    nSizea = 0;
    if ( v1->nSize > 0 )
    {
      v7 = (double)nY;
      do
      {
        v8 = (double)v1->nSize;
        nSized = ((double)nSizea - 0.5 * v8 + 0.5) / (0.5 * v8);
        nYc = 2.0 / v8;
        v9 = (v7 - 0.5 * v8 + 0.5) / (0.5 * v8);
        v10 = v9 * v9 + nSized * nSized + 1.0;
        v11 = 1.0 / (v10 * v10 * 3.1415927410125732) * (nYc * nYc);
        v1->pvMainDeltaFormFactor[v6 + v5 * v1->nSize] = v11;
        if ( LightmapInfo_vMaxDeltaFormFactor <= v11 )
          LightmapInfo_vMaxDeltaFormFactor = v11;
        nSizea = ++v6;
      }
      while ( v6 < v1->nSize );
    }
    ++v5;
  }
  v12 = 0;
  for ( nYa = 0; v12 < v1->nSize / 2; nYa = v12 )
  {
    v13 = 0;
    nSizeb = 0;
    if ( v1->nSize > 0 )
    {
      v14 = (double)nYa;
      do
      {
        v15 = (double)v1->nSize;
        *(float *)&nYb = ((double)nSizeb - 0.5 * v15 + 0.5) / (0.5 * v15);
        *(float *)&nSizec = (v14 - 0.5 * v15 + 0.5) / (0.5 * v15);
        v16 = 2.0 / v15 * (2.0 / v15);
        v17 = *(float *)&nSizec;
        if ( *(float *)&nSizec < 0.0 )
          v17 = -v17;
        v18 = *(float *)&nSizec * *(float *)&nSizec + *(float *)&nYb * *(float *)&nYb + 1.0;
        v19 = v16 * (v17 / (v18 * v18 * 3.1415927410125732));
        v1->pvHalfDeltaFormFactor[v13 + v12 * v1->nSize] = v19;
        if ( LightmapInfo_vMaxDeltaFormFactorSide <= v19 )
          LightmapInfo_vMaxDeltaFormFactorSide = v19;
        nSizeb = ++v13;
      }
      while ( v13 < v1->nSize );
    }
    ++v12;
  }
  return v1;
}

// source: h/2/lightmapinfo.c:2633  [anchor-mhash]
void __cdecl LightmapInfo_DeleteHemicube(struct Hemicube_t *ptHemicube)
{
  float *pvHalfDeltaFormFactor; // eax
  int v3; // esi
  float *pvMainDeltaFormFactor; // eax
  int v5; // esi
  float *pvMainZBuffer; // eax
  int v7; // esi
  int *pnMainFrameBuffer; // eax
  int v9; // esi
  int **apnHalfFrameBuffer; // ebx
  int *v11; // eax
  int v12; // esi
  int *v13; // eax
  bool v14; // zf
  int v15; // esi
  int v16; // esi
  int ptHemicubea = *(int *)&ptHemicube; // [esp+14h] [ebp+4h] ARGSLOT

  pvHalfDeltaFormFactor = ptHemicube->pvHalfDeltaFormFactor;
  if ( pvHalfDeltaFormFactor )
  {
    v3 = *(_DWORD *)((unsigned int)(pvHalfDeltaFormFactor - 1) & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v3);
    memset(*(void **)(v3 + 8), 0xCDu, *(_DWORD *)(v3 + 16));
    free((void *)v3);
  }
  pvMainDeltaFormFactor = ptHemicube->pvMainDeltaFormFactor;
  ptHemicube->pvHalfDeltaFormFactor = nullptr;
  if ( pvMainDeltaFormFactor )
  {
    v5 = *(_DWORD *)((unsigned int)(pvMainDeltaFormFactor - 1) & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v5);
    memset(*(void **)(v5 + 8), 0xCDu, *(_DWORD *)(v5 + 16));
    free((void *)v5);
  }
  pvMainZBuffer = ptHemicube->pvMainZBuffer;
  ptHemicube->pvMainDeltaFormFactor = nullptr;
  if ( pvMainZBuffer )
  {
    v7 = *(_DWORD *)((unsigned int)(pvMainZBuffer - 1) & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v7);
    memset(*(void **)(v7 + 8), 0xCDu, *(_DWORD *)(v7 + 16));
    free((void *)v7);
  }
  pnMainFrameBuffer = ptHemicube->pnMainFrameBuffer;
  ptHemicube->pvMainZBuffer = nullptr;
  if ( pnMainFrameBuffer )
  {
    v9 = *(_DWORD *)((unsigned int)(pnMainFrameBuffer - 1) & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v9);
    memset(*(void **)(v9 + 8), 0xCDu, *(_DWORD *)(v9 + 16));
    free((void *)v9);
  }
  ptHemicube->pnMainFrameBuffer = nullptr;
  apnHalfFrameBuffer = ptHemicube->apnHalfFrameBuffer;
  ptHemicubea = 4;
  do
  {
    v11 = apnHalfFrameBuffer[5];
    if ( v11 )
    {
      v12 = *(_DWORD *)((unsigned int)(v11 - 1) & 0xFFFFFFFC);
      --Mem_nCurrentAllocations;
      Node_Remove((_DWORD **)v12);
      memset(*(void **)(v12 + 8), 0xCDu, *(_DWORD *)(v12 + 16));
      free((void *)v12);
    }
    v13 = *apnHalfFrameBuffer;
    v14 = *apnHalfFrameBuffer == nullptr;
    apnHalfFrameBuffer[5] = nullptr;
    if ( !v14 )
    {
      v15 = *(_DWORD *)((unsigned int)(v13 - 1) & 0xFFFFFFFC);
      --Mem_nCurrentAllocations;
      Node_Remove((_DWORD **)v15);
      memset(*(void **)(v15 + 8), 0xCDu, *(_DWORD *)(v15 + 16));
      free((void *)v15);
    }
    *apnHalfFrameBuffer++ = nullptr;
    --ptHemicubea;
  }
  while ( ptHemicubea );
  v16 = *(_DWORD *)((unsigned int)&ptHemicube[-1].atHalfTexture[3].eDirect3DFormat & 0xFFFFFFFC);
  --Mem_nCurrentAllocations;
  Node_Remove((_DWORD **)v16);
  memset(*(void **)(v16 + 8), 0xCDu, *(_DWORD *)(v16 + 16));
  free((void *)v16);
}

// source: h/2/lightmapinfo.c:2660  [size]
float __cdecl LightmapInfo_GetMaxRadiosityPerSquareMeter()
{
  return LightmapInfo_vMaxRadiosityPerSquareMeter;
}

// source: h/2/lightmapinfo.c:2673  [size]
void __cdecl LightmapInfo_SetMaxRadiosityPerSquareMeter(float vMaxRadiosityPerSquareMeter)
{
  LightmapInfo_vMaxRadiosityPerSquareMeter = vMaxRadiosityPerSquareMeter;
}

// source: h/2/lightmapinfo.c:2686  [anchor-strings]
void __cdecl LightmapInfo_Open()
{
  unsigned __int16 BaseQTaskType; // ax
  unsigned __int16 v1; // si
  struct ParameterList_s *v2; // eax
  int v3; // edx
  void **v4; // esi
  struct QVector_s *v5; // eax
  float *p_vZ; // esi
  __int16 v7; // ax
  __int16 v8; // si
  unsigned __int16 v9; // ax
  struct real32x9_t *v10; // [esp-8h] [ebp-2Ch]
  float vAlpha; // [esp+0h] [ebp-24h]
  __int16 vAlphaa; // [esp+0h] [ebp-24h]
  int iSide; // [esp+14h] [ebp-10h]
  float v14; // [esp+18h] [ebp-Ch]
  float v15; // [esp+1Ch] [ebp-8h]
  float v16; // [esp+20h] [ebp-4h]

  BaseQTaskType = QTask_GetBaseQTaskType();
  v1 = QTask_NewQTaskType("LightmapInfo", 184, BaseQTaskType, 0, 0);
  LightmapInfo_eQTaskType = v1;
  QTask_LinkQTaskEventHandlerFn(v1, 0, LightmapInfo_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 2, LightmapInfo_DeleteHandler);
  QTask_LinkQTaskEventHandlerFn(v1, ParameterList_eUpdateInternalDataQTaskEvent, LightmapInfo_UpdateInternalDataHandler);
  QTask_LinkQTaskEventHandlerFn(
    v1,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))LightmapInfo_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(
    v1,
    Level_eUpdateInternalDataAfterLoadEvent,
    LightmapInfo_UpdateInternalDataAfterLoadHandler);
  v2 = (struct ParameterList_s *)Mem_AllocFn(212, 4);
  v3 = Level_eParameterTypeInt32;
  v2->ptParameterListItem = (struct ParameterListItem_s *)&v2[1];
  v2->nParameters = 0;
  v2->nMaxParameters = 10;
  LightmapInfo_ptParameterList = v2;
  ParameterList_AddParameter(v2, 0x78u, v3, "Hemicube resolution", 7u, nullptr);
  ParameterList_AddParameter(
    LightmapInfo_ptParameterList,
    0x98u,
    Level_eParameterTypeRGB,
    "Indoors ambient light",
    7u,
    nullptr);
  ParameterList_AddParameter(
    LightmapInfo_ptParameterList,
    0x72u,
    Level_eParameterTypePushButton,
    "Update lightmaps",
    6u,
    nullptr);
  ParameterList_AddParameter(
    LightmapInfo_ptParameterList,
    0x71u,
    Level_eParameterTypePushButton,
    "Update all lightmaps and save",
    6u,
    nullptr);
  ParameterList_AddParameter(
    LightmapInfo_ptParameterList,
    0x74u,
    Level_eParameterTypePushButton,
    "Calculate lightmaps",
    6u,
    nullptr);
  ParameterList_AddParameter(
    LightmapInfo_ptParameterList,
    0x73u,
    Level_eParameterTypePushButton,
    "Calculate all lightmaps and save",
    6u,
    nullptr);
  ParameterList_AddParameter(
    LightmapInfo_ptParameterList,
    0x70u,
    Level_eParameterTypePushButton,
    "Propagate lightmap info",
    6u,
    nullptr);
  ParameterList_AddParameter(
    LightmapInfo_ptParameterList,
    0x75u,
    Level_eParameterTypebool8,
    "Show texel normals",
    6u,
    nullptr);
  ParameterList_AddParameter(
    LightmapInfo_ptParameterList,
    0x80u,
    Level_eParameterTypeInt32,
    "Texels allocated",
    2u,
    nullptr);
  ParameterList_AddParameter(LightmapInfo_ptParameterList, 0xA8u, Level_eParameterTypeString16, "Filename", 1u, nullptr);
  v4 = (void **)Mem_AllocFn(4000, 4);
  v5 = (struct QVector_s *)Mem_AllocFn(24, 4);
  v5->tPrivate.nArraySize = 1000;
  v5->tPrivate.nReallocSize = 0;
  v5->tPrivate.nElements = 0;
  v5->tPrivate.isPrivateMem = false;
  v5->tPrivate.papxElement = v4;
  v5->tPrivate.isStrictOrder = true;
  LightmapInfo_ptLightmapInfoVector = v5;
  LightmapInfo_tRandomState.anRandom[0] = -923067897;
  LightmapInfo_tRandomState.anRandom[1] = 971667286;
  LightmapInfo_tRandomState.anRandom[2] = 2146516173;
  iSide = 0;
  v14 = sin(1.5707963705062866);
  p_vZ = &LightmapInfo_atHemicubeMatrix[0].tX.vZ;
  v15 = cos(1.5707963705062866);
  do
  {
    v16 = -v14;
    p_vZ[3] = v16;
    vAlpha = (double)iSide * 1.5707963705062866;
    p_vZ[2] = v15;
    v10 = (struct real32x9_t *)(p_vZ - 2);
    v10->tX.vX = 1.0;
    *(p_vZ - 1) = 0.0;
    *p_vZ = 0.0;
    p_vZ[1] = 0.0;
    p_vZ[4] = 0.0;
    p_vZ[5] = v14;
    p_vZ[6] = v15;
    p_vZ[7] = 0.0;
    Real32x9_Rotate(v10, v10, 0.0, vAlpha, 0.0);
    p_vZ += 10;
    ++iSide;
  }
  while ( (int)p_vZ < 127858808 );
  LightmapInfo_eEnumerateLightmapVirModelsEvent = QTask_NewQTaskEventFn(
                                                    LightmapInfo_eQTaskType,
                                                    "EnumerateLightmapVirModels");
  LightmapInfo_eGetNumberOfFormFactorsQTaskEvent = QTask_NewQTaskEventFn(0x200u, "GetNumberOfFormFactors");
  LightmapInfo_eCalculateFormFactorsQTaskEvent = QTask_NewQTaskEventFn(0x200u, "CalculateFormFactors");
  v7 = QTask_NewQTaskEventFn(0x200u, "EmitRadiosity");
  v8 = LightmapInfo_eEnumerateLightmapVirModelsEvent;
  LightmapInfo_eEmitRadiosityQTaskEvent = v7;
  vAlphaa = LightmapInfo_eEnumerateLightmapVirModelsEvent;
  v9 = QTask_GetBaseQTaskType();
  QTask_LinkQTaskEventHandlerFn(v9, vAlphaa, QTask_EnumerateLightmapVirModelsHandler);
  QTask_LinkQTaskEventHandlerFn(RigidDynCubeObj_eQTaskType, v8, RigidDynCubeObj_EnumerateLightmapVirModelsHandler);
  QTask_LinkQTaskEventHandlerFn(EditorRigidObj_eQTaskType, v8, QTask_EnumerateLightmapVirModelsHandler);
  LightmapInfo_piBlankIndexMap = (int *)Mem_AllocFn(0x40000, 4);
  memset(LightmapInfo_piBlankIndexMap, 0xFFu, 0x40000u);
}

// source: h/2/lightmapinfo.c:2773  [anchor-hash]
void __cdecl LightmapInfo_Close()
{
  int v0; // esi
  int v1; // esi

  LightmapInfo_EndSave();
  if ( LightmapInfo_piBlankIndexMap )
  {
    v0 = *(_DWORD *)((unsigned int)(LightmapInfo_piBlankIndexMap - 1) & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
  LightmapInfo_piBlankIndexMap = nullptr;
  QTask_DeleteQTaskEvent(LightmapInfo_eEnumerateLightmapVirModelsEvent);
  QTask_DeleteQTaskEvent(LightmapInfo_eEmitRadiosityQTaskEvent);
  QTask_DeleteQTaskEvent(LightmapInfo_eCalculateFormFactorsQTaskEvent);
  QTask_DeleteQTaskEvent(LightmapInfo_eGetNumberOfFormFactorsQTaskEvent);
  QVector_Delete(LightmapInfo_ptLightmapInfoVector);
  if ( LightmapInfo_ptParameterList )
  {
    v1 = *(_DWORD *)((unsigned int)&LightmapInfo_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v1);
    memset(*(void **)(v1 + 8), 0xCDu, *(_DWORD *)(v1 + 16));
    free((void *)v1);
  }
  QTask_DeleteQTaskType(LightmapInfo_eQTaskType);
}

// source: h/2/lightmapinfo.c:2805  [size]
unsigned __int16 __cdecl LightmapInfo_GetQTaskType()
{
  return LightmapInfo_eQTaskType;
}

// source: h/2/lightmapinfo.c:2820  [anchor-refs]
void *__cdecl ProgressBar_New(int nX, int nY)
{
  int *v2; // esi
  struct QSprite_s *Font; // eax
  struct TextWindow_s *v4; // eax
  int v5; // ecx
  int v6; // edx
  bool v7; // zf

  v2 = (int *)Mem_AllocFn(20, 4);
  *v2 = nX;
  v2[1] = nY;
  Font = FontManager_LoadFont("LOCAL:debug.fnt");
  v2[4] = (int)Font;
  v4 = TextWindow_New(Font, 380, 100);
  v5 = v2[1];
  v6 = *v2;
  v2[3] = (int)v4;
  v4->nY = v5 + 10;
  v4->nX = v6 + 10;
  *(_DWORD *)(v2[3] + 32) = -1;
  v7 = Timer_isPerformanceCounter == 0;
  *(_DWORD *)(v2[3] + 4) = 1;
  if ( v7 )
    v2[2] = GetTickCount() - Timer_nStartTime;
  else
    v2[2] = Timer_GetPerformanceCounter() - Timer_nStartTime;
  return v2;
}

// source: h/2/lightmapinfo.c:2849  [anchor-hash]
void __cdecl ProgressBar_Delete(void *pxProgressBar)
{
  int v2; // esi

  RenderMode_tActiveRenderMode.apfRenderModeMethod[Display_eClearMethod](nullptr);
  RenderMode_tActiveRenderMode.apfRenderModeMethod[Display_eSwapBuffersMethod](nullptr);
  RenderMode_tActiveRenderMode.apfRenderModeMethod[Display_eClearMethod](nullptr);
  RenderMode_tActiveRenderMode.apfRenderModeMethod[Display_eSwapBuffersMethod](nullptr);
  RenderMode_tActiveRenderMode.apfRenderModeMethod[Display_eClearMethod](nullptr);
  RenderMode_tActiveRenderMode.apfRenderModeMethod[Display_eSwapBuffersMethod](nullptr);
  TextWindow_Delete(*((struct TextWindow_s **)pxProgressBar + 3));
  FontManager_DeleteFont(*((struct QSprite_s **)pxProgressBar + 4));
  v2 = *(_DWORD *)(((int)pxProgressBar - 4) & 0xFFFFFFFC);
  --Mem_nCurrentAllocations;
  Node_Remove((_DWORD **)v2);
  memset(*(void **)(v2 + 8), 0xCDu, *(_DWORD *)(v2 + 16));
  free((void *)v2);
}

// source: h/2/lightmapinfo.c:2878  [anchor-strings]
void __cdecl ProgressBar_Draw(void *pxProgressBar, float vProgress, char *zTitle)
{
  #pragma pack(push, 1)
  union
  {
    struct { float vX; };
    struct { float vXa; };
    struct { float vXb; };
    struct { float vXc; };
    struct { float vXd; };
    struct { float vXe; };
    struct { float vXf; };
    struct { float vXg; };
    struct { char igi2_o8[4]; float vY; };
    struct { char igi2_o9[4]; float vYa; };
    struct { char igi2_o10[4]; float vYb; };
    struct { char igi2_o11[4]; float vYc; };
    struct { char igi2_o12[4]; float vYd; };
    struct { char igi2_o13[4]; float vYe; };
    struct { char igi2_o14[4]; float vYf; };
    struct { char igi2_o15[4]; float vYg; };
    struct { char igi2_o16[8]; float vWidth; };
    struct { char igi2_o17[76]; struct RenderContext_s tRenderContext; };
    char igi2_extent[152];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  DWORD PerformanceCounter; // eax
  int v5; // esi
  int v6; // ecx
  int v7; // edi
  int v8; // ebp
  int v9; // eax
  struct real32x2_t struct_real32x2_t; // 0:^44.8

  struct_real32x2_t.vX = (float)Display_tActiveMode.nWidth;
  struct_real32x2_t.vY = (float)Display_tActiveMode.nHeight;
  RenderContext_Alloc(&igi2_frame.tRenderContext, 1);
  igi2_frame.tRenderContext.tDisplayAreaMin.vX = 0.0;
  igi2_frame.tRenderContext.tDisplayAreaMax = struct_real32x2_t;
  RenderContext_nActiveRenderContextTimeStamp += 2;
  igi2_frame.tRenderContext.tDisplayAreaMin.vY = 0.0;
  qmemcpy(&RenderContext_tActiveRenderContext, &igi2_frame.tRenderContext, sizeof(RenderContext_tActiveRenderContext));
  if ( vProgress >= 0.0 )
  {
    if ( vProgress > 1.0 )
      vProgress = 1.0;
  }
  else
  {
    vProgress = 0.0;
  }
  igi2_frame.vY = (float)*((int *)pxProgressBar + 1);
  igi2_frame.vX = (float)*(int *)pxProgressBar;
  QSprite_RegisterBlank(igi2_frame.vX, igi2_frame.vY, 399.0, 119.0, 128.0, 128.0, 128.0, 0, -1);
  igi2_frame.vYa = (float)(*((_DWORD *)pxProgressBar + 1) + 1);
  igi2_frame.vXa = (float)(*(_DWORD *)pxProgressBar + 1);
  QSprite_RegisterBlank(igi2_frame.vXa, igi2_frame.vYa, 399.0, 119.0, 40.0, 40.0, 40.0, 0, -1);
  igi2_frame.vYb = (float)(*((_DWORD *)pxProgressBar + 1) + 1);
  igi2_frame.vXb = (float)(*(_DWORD *)pxProgressBar + 1);
  QSprite_RegisterBlank(igi2_frame.vXb, igi2_frame.vYb, 398.0, 118.0, 80.0, 80.0, 80.0, 0, -1);
  igi2_frame.vYc = (float)(*((_DWORD *)pxProgressBar + 1) + 90);
  igi2_frame.vXc = (float)(*(_DWORD *)pxProgressBar + 10);
  QSprite_RegisterBlank(igi2_frame.vXc, igi2_frame.vYc, 379.0, 19.0, 40.0, 40.0, 40.0, 0, -1);
  igi2_frame.vYd = (float)(*((_DWORD *)pxProgressBar + 1) + 91);
  igi2_frame.vXd = (float)(*(_DWORD *)pxProgressBar + 11);
  QSprite_RegisterBlank(igi2_frame.vXd, igi2_frame.vYd, 379.0, 19.0, 128.0, 128.0, 128.0, 0, -1);
  igi2_frame.vYe = (float)(*((_DWORD *)pxProgressBar + 1) + 91);
  igi2_frame.vXe = (float)(*(_DWORD *)pxProgressBar + 11);
  QSprite_RegisterBlank(igi2_frame.vXe, igi2_frame.vYe, 378.0, 18.0, 80.0, 80.0, 80.0, 0, -1);
  igi2_frame.vWidth = vProgress * 378.0;
  igi2_frame.vYf = (float)(*((_DWORD *)pxProgressBar + 1) + 91);
  igi2_frame.vXf = (float)(*(_DWORD *)pxProgressBar + 11);
  QSprite_RegisterBlank(igi2_frame.vXf, igi2_frame.vYf, igi2_frame.vWidth, 18.0, 0.0, 0.0, 80.0, 0, -1);
  if ( Timer_isPerformanceCounter )
    PerformanceCounter = Timer_GetPerformanceCounter();
  else
    PerformanceCounter = GetTickCount();
  v5 = PerformanceCounter - Timer_nStartTime - *((_DWORD *)pxProgressBar + 2);
  if ( vProgress == 0.0 )
    v6 = 0;
  else
    v6 = (__int64)((double)v5 / vProgress) - v5;
  v7 = v6 / 1000 % 60;
  v8 = v6 / 1000 / 60;
  TextWindow_Clear(*((struct TextWindow_s **)pxProgressBar + 3));
  TextWindow_printf(
    *((struct TextWindow_s **)pxProgressBar + 3),
    "%s\n"
    "\n"
    "%d%% complete\n"
    "\n"
    "Elapsed time:         %2d:%02d:%02d\n"
    "Estimated time left:  %2d:%02d:%02d\n"
    "\n"
    "Press and hold Ctrl+Shift+C to cancel\n",
    zTitle,
    (unsigned int)(__int64)(vProgress * 100.0),
    v5 / 1000 / 60 / 60 % 24,
    v5 / 1000 / 60 % 60,
    v5 / 1000 % 60,
    v8 / 60 % 24,
    v8 % 60,
    v7);
  v9 = *((_DWORD *)pxProgressBar + 3);
  if ( *(_DWORD *)(v9 + 4) && *(_DWORD *)v9 )
  {
    igi2_frame.vYg = (float)*(int *)(v9 + 12);
    igi2_frame.vXg = (float)*(int *)(v9 + 8);
    QTilemap_Register(*(struct QTilemap_s **)v9, igi2_frame.vXg, igi2_frame.vYg, 128.0, 128.0, 128.0, 1.0, 1.0, 0, *(_DWORD *)(v9 + 32));
  }
  RenderContext_DeAlloc(&igi2_frame.tRenderContext);
}
