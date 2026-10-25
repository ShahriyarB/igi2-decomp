/* h/h.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: h/h.c:51  [anchor-strings]
void __cdecl H_Open()
{
  unsigned __int16 BaseQTaskType; // ax
  int v1; // esi
  int v2; // esi
  int v3; // esi
  int v4; // esi
  struct QVector_s *v5; // eax
  unsigned __int16 v6; // ax

  G_Open();
  Particle2DDynCubeObj_Open();
  BaseQTaskType = QTask_GetBaseQTaskType();
  CamQTask_eQTaskType = QTask_NewQTaskType("CamTask", 152, BaseQTaskType, 0, 0);
  Input_eGetInputQTaskEvent = QTask_NewQTaskEventFn(0, "GetInput");
  InputPort_Open();
  Sync_Open();
  MenuItem_Open();
  MenuItemQTask_Open();
  PushButton_Open();
  SimBoneDynCubeObj_eQTaskType = QTask_NewQTaskType("SimBoneDynCubeObj", 504, BoneDynCubeObj_eQTaskType, 0, 0);
  ParameterList_Open();
  Level_Open();
  MemRef_nReAllocMemRefs = 256;
  MemRef_ReAlloc(0x400u);
  Serialize_Open();
  v1 = ParameterList_NewParameterType("SerializeList", -1);
  SerializeList_eParameterType = v1;
  ParameterList_LinkParameterEventHandler(v1, ParameterList_eQParameterPrintEvent, SerializeList_ParameterPrintHandler);
  ParameterList_LinkParameterEventHandler(v1, ParameterList_eQParameterParseEvent, SerializeList_ParameterParseHandler);
  v2 = ParameterList_NewParameterType("SerializeArray", -1);
  SerializeArray_eParameterType = v2;
  ParameterList_LinkParameterEventHandler(v2, ParameterList_eQParameterPrintEvent, SerializeArray_ParameterPrintHandler);
  ParameterList_LinkParameterEventHandler(v2, ParameterList_eQParameterParseEvent, SerializeArray_ParameterParseHandler);
  v3 = ParameterList_NewParameterType("SerializeStruct", -1);
  SerializeStruct_eParameterType = v3;
  ParameterList_LinkParameterEventHandler(
    v3,
    ParameterList_eQParameterPrintEvent,
    SerializeStruct_ParameterPrintHandler);
  ParameterList_LinkParameterEventHandler(
    v3,
    ParameterList_eQParameterParseEvent,
    SerializeStruct_ParameterParseHandler);
  v4 = ParameterList_NewParameterType("SerializeQTaskRef", -1);
  SerializeQTaskRef_eParameterType = v4;
  ParameterList_LinkParameterEventHandler(
    v4,
    ParameterList_eQParameterPrintEvent,
    SerializeQTaskRef_ParameterPrintHandler);
  ParameterList_LinkParameterEventHandler(
    v4,
    ParameterList_eQParameterParseEvent,
    SerializeQTaskRef_ParameterParseHandler);
  ParameterEnumList_Open();
  ModelObjParameters_Open();
  MagicObjConfigContainer_Open();
  MagicObjConfig_Open();
  LevelScript_Open();
  SkyQTask_Open();
  PhysicsObjType_Open();
  PhysicsObj_Open();
  PhysicsMagicObj_Open();
  EditorRigidObj_Open();
  DiscardTerrainTask_Open();
  DiscardTerrainAreaTask_Open();
  SetActiveCubeQTask_Open();
  AnimQTask_OpenTypes();
  BspTreeEdit_Open();
  TagItem_Open();
  SplineObj_Open();
  AnimQTask_Open();
  EditRigidObj_Open();
  EditBoneObj_Open();
  DiscardTask_Open();
  TextureModifier_Open();
  Terrain_Open();
  Water_Open();
  EditHazinglayer_Open();
  LODSettings_Open();
  EditRigidObjAttachedToBone_Open();
  CutScene_Open();
  AnimScaleQTask_Open();
  AnimRigidDynCubeObj_Open();
  Graph_Open();
  GraphNode_Open();
  AnimCam_Open();
  AreaActivateQTask_Open();
  Vehicle_Open();
  GlobalLightQTask_Open();
  DirlightQTask_Open();
  LightmapInfo_Open();
  LensflareQTask_Open();
  Container_Open();
  Origo_Open();
  NoiseQTask_Open();
  MoveRigidObj_Open();
  SmoothQTask_Open();
  MipMapTask_Open();
  ScreenGrab_Open();
  FlatSky_Open();
  FlatSkyKeyframe_Open();
  FlatWater_Open();
  Forest_Open();
  RunDelayed_eQTaskEvent = QTask_NewQTaskEventNoContextFn(0, "RunDelayed");
  v5 = (struct QVector_s *)Mem_AllocFn(24, 4);
  v5->tPrivate.nArraySize = 0;
  v5->tPrivate.nReallocSize = 32;
  v5->tPrivate.nElements = 0;
  v5->tPrivate.isPrivateMem = false;
  v5->tPrivate.papxElement = nullptr;
  v5->tPrivate.isStrictOrder = false;
  RunDelayed_ptRunDelayedQTaskRefVector = v5;
  Wind_Open();
  SoundSysEdit_Open();
  SoundDefGroupEdit_Open();
  SoundDefGraphEdit_Open();
  SoundDefSoundEdit_Open();
  SoundDefTriggerOnceEdit_Open();
  SoundManager_Open();
  EditCamera_Open();
  LevelTimer_Open();
  EditorMagicObj_Open();
  AnimSound_Open();
  TerrainLightMap_Open();
  SimpointObj_Open();
  SplinePathDynCubeObj_Open();
  SplinePathGuideQTask_Open();
  HeightMap_Open();
  v6 = QTask_GetBaseQTaskType();
  LevelInfo_eQTaskType = QTask_NewQTaskType("LevelInfo", 40, v6, 0, 0);
  GFXCapsViewer_Open();
  OLELoader_Open();
  DebugConsoleTask_Open();
  DebugConsoleWindow_Open();
  BreakPoint_Open();
  RotateAttachment_Open();
  ScriptDebugger_Open();
  TelnetDaemon_Open();
}
