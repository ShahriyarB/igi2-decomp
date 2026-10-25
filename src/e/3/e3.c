/* e/3/e3.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: e/3/e3.c:29  [size]
void __cdecl E3_Open()
{
  struct RenderStateBlock_t *v0; // eax
  int v1; // ecx
  int v2; // ecx
  int v3; // ecx
  struct RenderStateBlock_t *v4; // eax
  int v5; // ecx
  int v6; // ecx
  int v7; // ecx
  unsigned __int16 BaseQTaskType; // ax
  struct RenderStateBlock_t *v9; // ecx
  int nNumStates; // eax
  __int16 v11; // [esp-8h] [ebp-8h]

  E1_Open();
  CubeOcclusion_Open();
  QCube_Open();
  Hazinglayers_Open();
  BspTreeDynCubeObj_Open();
  MTP_Open();
  DynCubeLight_Open();
  Sky_ptLODVirModel = MTP_GetLODVirModel(off_68698C);
  Sprite3D_Open();
  MagicObj_Open();
  Attach_eAttachEvent = QTask_NewQTaskEventFn(0, "Attach");
  Attach_eUpdateAttachmentEvent = QTask_NewQTaskEventNoContextFn(0, "UpdateAttachment");
  Hierarchy_Open();
  sub_5C5990();
  ModelObj_Open();
  Envmap_eDrawQTaskEvent = QTask_NewQTaskEventFn(0, "DrawEnvmap");
  Envmap_eEnumerateQTaskEvent = QTask_NewQTaskEventFn(0, "EnumerateEnvmap");
  v11 = Envmap_eEnumerateQTaskEvent;
  BaseQTaskType = QTask_GetBaseQTaskType();
  QTask_LinkQTaskEventHandlerFn(BaseQTaskType, v11, QTask_EnumerateEnvmapHandler);
  RigidDynCubeObj_Open();
  BoneDynCubeObj_GenericOpen();
  QTask_LinkQTaskEventHandlerFn(
    BoneDynCubeObj_eQTaskType,
    QCube_eGetClosestVertexQTaskEvent,
    BoneDynCubeObj_GetClosestVertex);
  RigidMagicObj_Open();
  BoneMagicObj_Open();
  AnimController_Open();
  AnimBlender_Open();
  PolyListDynCubeObj_Open();
  SplineObjSegment_Open();
  Shadow_Open();
  Mesh3D_Open();
  SectorObject_Open();
  MagicObjContainer_Open();
  Rain_Open();
  Direct3D_RegisterCallback(SkyDome_RestoreCallback, &Direct3D_ptRestoreCallback);
  Direct3D_RegisterCallback(SkyDome_DestroyCallback, &Direct3D_ptDestroyCallback);
  v9 = Direct3D_ptTextureStateBlock;
  nNumStates = Direct3D_ptTextureStateBlock->nNumStates;
  Direct3D_ptTextureStateBlock->nNumStates = nNumStates + 1;
  v9->atRenderState[nNumStates].pfCallback = Billboard_SetTextureState;
  Billboard_eTextureState = nNumStates;
  Lightmap_Open();
  Direct3DRender_Open();
  WaterRender_Open();
  TerrainRender_Open();
  v0 = Direct3D_ptTextureStateBlock;
  v1 = Direct3D_ptTextureStateBlock->nNumStates;
  Direct3D_ptTextureStateBlock->nNumStates = v1 + 1;
  v0->atRenderState[v1].pfCallback = ForestRender_SetTextureState_Trunk;
  ForestRender_eTextureState_Trunk = v1;
  v2 = v0->nNumStates;
  v0->nNumStates = v2 + 1;
  v0->atRenderState[v2].pfCallback = ForestRender_SetTextureState_AlphaBlendFoliage;
  ForestRender_eTextureState_AlphaBlendFoliage = v2;
  v3 = v0->nNumStates;
  v0->nNumStates = v3 + 1;
  v0->atRenderState[v3].pfCallback = ForestRender_SetTextureState_AlphaTestFoliage;
  v4 = Direct3D_ptGenericStateBlock;
  ForestRender_eTextureState_AlphaTestFoliage = v3;
  v5 = Direct3D_ptGenericStateBlock->nNumStates;
  Direct3D_ptGenericStateBlock->nNumStates = v5 + 1;
  v4->atRenderState[v5].pfCallback = ForestRender_SetGenericState_Trunk;
  ForestRender_eGenericState_Trunk = v5;
  v6 = v4->nNumStates;
  v4->nNumStates = v6 + 1;
  v4->atRenderState[v6].pfCallback = ForestRender_SetGenericState_AlphaBlendFoliage;
  ForestRender_eGenericState_AlphaBlendFoliage = v6;
  v7 = v4->nNumStates;
  v4->nNumStates = v7 + 1;
  v4->atRenderState[v7].pfCallback = ForestRender_SetGenericState_AlphaTestFoliage;
  ForestRender_eGenericState_AlphaTestFoliage = v7;
  RenderMode_atRenderMode[Direct3D_eRenderMode].apfRenderModeMethod[Mesh3D_eDrawForestRenderModeMethod] = (void (__cdecl *)(void *))ForestRender_Draw;
  if ( !ForestRender_atMorphBuffer )
    ForestRender_atMorphBuffer = (struct real32x3_t *)Mem_AllocFn(12 * Batch_atPredefinedVBFormats[3].nMaxVertices, 4);
}

// source: e/3/e3.c:88  [anchor-caller]
void __cdecl E3_Close()
{
  struct RenderStateBlock_t *v0; // esi
  int v1; // ecx
  struct RenderStateBlock_t *v2; // edx
  int v3; // eax
  int v4; // edx
  int v5; // ecx
  struct DisplayCallbackChain_s *v6; // eax
  struct DisplayCallbackChain_s *v7; // ecx
  int v8; // eax

  ForestRender_Close();
  TerrainRender_Close();
  v0 = Direct3D_ptTextureStateBlock;
  v1 = WaterRender_eBlendState;
  v2 = Direct3D_ptBlendStateBlock;
  Direct3D_ptTextureStateBlock->atRenderState[WaterRender_eTextureState].pfCallback = nullptr;
  v3 = WaterRender_eGenericState;
  v2->atRenderState[v1].pfCallback = nullptr;
  v4 = WaterRender_eDrawWaterMethod;
  Direct3D_ptGenericStateBlock->atRenderState[v3].pfCallback = nullptr;
  RenderMode_atRenderModeMethod[v4].isAllocated = 0;
  Direct3DRender_Close();
  QTask_DeleteQTaskEvent(Lightmap_eEnumerateQTaskEvent);
  QTask_DeleteQTaskEvent(Lightmap_eDrawQTaskEvent);
  v5 = Rain_tConsoleID;
  v0->atRenderState[Billboard_eTextureState].pfCallback = nullptr;
  DebugConsole_DeAlloc(v5);
  QTask_DeleteQTaskType(Rain_eQTaskType);
  QTask_DeleteQTaskType(MagicObjContainer_eQTaskType);
  SectorObject_Close();
  Mesh3D_Close();
  QTask_DeleteQTaskType(Shadow_eQTaskType);
  QTask_FreeGroup(0x10000000u);
  QTask_DeleteQTaskType(SplineObjSegment_eQTaskType);
  PolyListDynCubeObj_Close();
  QTask_DeleteQTaskType(AnimBlender_eQTaskType);
  QTask_DeleteQTaskType(AnimController_eQTaskType);
  QTask_DeleteQTaskType(LOWORD(CubeOcclusion_vScreenSizeX));
  LOWORD(CubeOcclusion_vScreenSizeX) = 512;
  QTask_DeleteQTaskType(RigidMagicObj_eQTaskType);
  RigidMagicObj_eQTaskType = 512;
  QTask_DeleteQTaskEvent(RigidMagicObj_eCreateMagicObjEvent);
  RigidMagicObj_eCreateMagicObjEvent = 512;
  QTask_DeleteQTaskType(BoneDynCubeObj_eQTaskType);
  BoneDynCubeObj_eQTaskType = 512;
  QTask_DeleteQTaskEvent(BoneDynCubeObj_eQTaskCollisionEvalEvent);
  BoneDynCubeObj_eQTaskCollisionEvalEvent = 512;
  QTask_DeleteQTaskEventNoContext(BoneDynCubeObj_eInterpolateQTaskEvent);
  BoneDynCubeObj_eInterpolateQTaskEvent = 512;
  QTask_FreeGroup((unsigned int)&TerrainRender_atEdge[4623].iSplitVertex);
  QTask_DeleteQTaskType(RigidDynCubeObj_eQTaskType);
  RigidDynCubeObj_eQTaskType = 512;
  QTask_DeleteQTaskEvent(RigidDynCubeObj_eRenderStartEvent);
  RigidDynCubeObj_eRenderStartEvent = 512;
  QTask_DeleteQTaskEvent(Envmap_eEnumerateQTaskEvent);
  QTask_DeleteQTaskEvent(Envmap_eDrawQTaskEvent);
  QTask_DeleteQTaskType(ModelObj_eQTaskType);
  QTask_DeleteQTaskEvent(ShadowVolume_eGetShadowInfoEvent);
  QTask_DeleteQTaskType(ShadowVolume_eQTaskType);
  QTask_DeleteQTaskType(ShadowVolume_eShadowLayerQTaskType);
  QObjectVector_Delete(ShadowVolume_ptProtectRequestVector);
  QHashTable_Delete(Hierarchy_ptHashTable);
  MemPool_DeInit(&Hierarchy_tRecordPool);
  QTask_DeleteQTaskEvent(Attach_eAttachEvent);
  QTask_DeleteQTaskEventNoContext(Attach_eUpdateAttachmentEvent);
  MagicObj_Close();
  MemPool_DeInit(&Sprite3D_tUDPool);
  QTask_DeleteQTaskType(Sprite3D_eQTaskType);
  QObjectVector_Delete(DynCubeLight_ptPointlightCollection);
  QObjectVector_Delete(DynCubeLight_ptSpotlightCollection);
  QTask_DeleteQTaskType(DynCubeLight_eQTaskTypePointlight);
  DynCubeLight_eQTaskTypePointlight = 512;
  QTask_DeleteQTaskType(DynCubeLight_eQTaskTypeSpotlight);
  DynCubeLight_eQTaskTypeSpotlight = 512;
  MTP_Close();
  BspTreeDynCubeObj_Close();
  QTask_DeleteQTaskType(Hazinglayers_eQTaskType);
  QCube_Close();
  QTask_DeleteQTaskEvent(CubeOcclusion_eOcclusionDrawQTaskEvent);
  CubeOcclusion_eOcclusionDrawQTaskEvent = 512;
  World_Close();
  v6 = Display_ptStartFrameCallback;
  v7 = nullptr;
  if ( Display_ptStartFrameCallback )
  {
    while ( (void (__cdecl *)())v6->pfCallback != Clipping_StartFrameCallback )
    {
      v7 = v6;
      v6 = v6->ptNext;
      if ( !v6 )
        goto LABEL_8;
    }
    if ( v7 )
      v7->ptNext = v6->ptNext;
    else
      Display_ptStartFrameCallback = v6->ptNext;
  }
LABEL_8:
  v8 = Lightsource_eRemoveLightsourceRenderModeMethod;
  RenderMode_atRenderModeMethod[Lightsource_eAddLightsourceRenderModeMethod].isAllocated = 0;
  RenderMode_atRenderModeMethod[v8].isAllocated = 0;
  QTask_DeleteQTaskEvent(DynCube_eDynCubeObjInGameEvalQTaskEvent);
  QTask_DeleteQTaskEvent(DynCubeObj_eDynCubeObjRegisterQTaskEvent);
  QTask_DeleteQTaskEvent(DynCubeObj_eDynCubeObjRemoveQTaskEvent);
  QTask_DeleteQTaskType(DynCubeObj_eQTaskType);
  QTask_DeleteQTaskEvent(QCamera_eFirstPersonQTaskEvent);
  QTaskList_Delete(QCamera_ptFirstPersonQTaskList);
  QTask_DeleteQTaskType(ShadowVolume_nShadow);
  LOWORD(ShadowVolume_nShadow) = 512;
  QTask_DeleteQTaskEvent(8);
  QTask_DeleteQTaskEvent(5);
  QTask_DeleteQTaskEvent(6);
  QTask_DeleteQTaskEvent(7);
  QTask_DeleteQTaskEvent(SLOWORD(ShadowVolume_vIntensity));
}
