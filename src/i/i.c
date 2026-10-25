/* i/i.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: i/i.c:32  [anchor-caller]
void __cdecl I_Open()
{
  H_Open();
  AIGraph_Open();
}

// source: i/i.c:53  [anchor-caller]
void __cdecl I_Close()
{
  int v0; // edx
  int v1; // ecx
  int v2; // edx
  int v3; // ecx
  int v4; // edx
  int v5; // ecx
  int v6; // edx
  int v7; // ecx

  AIGraph_Close();
  TelnetDaemon_Close();
  ScriptDebugger_Close();
  RotateAttachment_Close();
  BreakPoint_Close();
  DebugConsoleWindow_Close();
  DebugConsoleTask_Close();
  OLELoader_Close();
  QTask_DeleteQTaskType(GFXCapsViewer_eQTaskType);
  QTask_DeleteQTaskType(LevelInfo_eQTaskType);
  HeightMap_Close();
  SplinePathGuideQTask_Close();
  SplinePathDynCubeObj_Close();
  QTask_DeleteQTaskType(SimpointObjContainer_eQTaskType);
  QTask_DeleteQTaskType(SimpointObj_eQTaskType);
  TerrainLightMap_Close();
  QTask_DeleteQTaskType(AnimSound_eQTaskType);
  QTask_DeleteQTaskType(EditorMagicObj_eQTaskType);
  LevelTimer_Close();
  EditCamera_Close();
  SoundManager_Close();
  SoundDefTriggerOnceEdit_Close();
  SoundDefSoundEdit_Close();
  SoundDefGraphEdit_Close();
  SoundDefGroupEdit_Close();
  SoundSysEdit_Close();
  Wind_Close();
  QTask_DeleteQTaskEventNoContext(RunDelayed_eQTaskEvent);
  QVector_Delete(RunDelayed_ptRunDelayedQTaskRefVector);
  Forest_Close();
  FlatWater_Close();
  FlatSkyKeyframe_Close();
  FlatSky_Close();
  ScreenGrab_Close();
  MipMapTask_Close();
  SmoothQTask_Close();
  MoveRigidObj_Close();
  NoiseQTask_Close();
  Origo_Close();
  Container_Close();
  LensflareQTask_Close();
  LightmapInfo_Close();
  DirlightQTask_Close();
  GlobalLightQTask_Close();
  Vehicle_Close();
  AreaActivateQTask_Close();
  AnimCam_Close();
  GraphNode_Close();
  Graph_Close();
  QTask_DeleteQTaskType(AnimRigidDynCubeObj_eQTaskType);
  AnimScaleQTask_Close();
  CutScene_Close();
  EditRigidObjAttachedToBone_Close();
  TagItem_Close();
  BspTreeEdit_Close();
  LODSettings_Close();
  EditHazinglayer_Close();
  Water_Close();
  Terrain_Close();
  TextureModifier_Close();
  DiscardTask_Close();
  EditBoneObj_Close();
  EditRigidObj_Close();
  AnimQTask_Close();
  SplineObj_Close();
  SetActiveCubeQTask_Close();
  DiscardTerrainAreaTask_Close();
  DiscardTerrainTask_Close();
  QTask_DeleteQTaskType(EditorRigidObj_eQTaskType);
  QTask_DeleteQTaskType(PhysicsMagicObj_eQTaskType);
  PhysicsMagicObj_eQTaskType = 512;
  QTask_DeleteQTaskEvent(PhysicsObj_eMove);
  QTask_DeleteQTaskEvent(PhysicsObj_eUpdateOrientation);
  QTask_DeleteQTaskEvent(PhysicsObj_eHit);
  QTask_DeleteQTaskType(PhysicsObj_eQTaskType);
  QTask_DeleteQTaskEvent(PhysicsObjType_eParsePhysicsObjTypeEvent);
  QTask_DeleteQTaskEvent(PhysicsObjType_eGetPhysicsObjTypeSizeEvent);
  QTask_DeleteQTaskEvent(PhysicsObjType_ePhysicsObjTypeDeleteEvent);
  SkyQTask_Close();
  LevelScript_Close();
  MagicObjConfig_Close();
  MagicObjConfigContainer_Close();
  ModelObjParameters_Close();
  v0 = ParameterEnumList_eParameterTypeReal32;
  ParameterList_atParameterType[ParameterEnumList_eParameterTypeInt32].isUsed = false;
  v1 = ParameterEnumList_eParameterTypeString16;
  ParameterList_atParameterType[v0].isUsed = false;
  v2 = ParameterEnumList_eParameterTypeString32;
  ParameterList_atParameterType[v1].isUsed = false;
  v3 = ParameterEnumList_eParameterTypeString256;
  ParameterList_atParameterType[v2].isUsed = false;
  v4 = SerializeQTaskRef_eParameterType;
  ParameterList_atParameterType[v3].isUsed = false;
  v5 = SerializeStruct_eParameterType;
  ParameterList_atParameterType[v4].isUsed = false;
  v6 = SerializeArray_eParameterType;
  ParameterList_atParameterType[v5].isUsed = false;
  v7 = SerializeList_eParameterType;
  ParameterList_atParameterType[v6].isUsed = false;
  ParameterList_atParameterType[v7].isUsed = false;
  Symbol_Remove("DefineTaskState");
  QTask_DeleteQTaskEvent(Serialize_eGetSerializeInfoQTaskEvent);
  QTask_DeleteQTaskEvent(Serialize_eGetSerializeParameterListQTaskEvent);
  QTask_DeleteQTaskEvent(Serialize_eSerializeQTaskEvent);
  QTask_DeleteQTaskEvent(Serialize_eDeSerializeQTaskEvent);
  QTask_DeleteQTaskEvent(Serialize_eDeSerializeDoneQTaskEvent);
  MemRef_Close();
  Level_Close();
  ParameterList_Close();
  QTask_DeleteQTaskType(SimBoneDynCubeObj_eQTaskType);
  QTask_DeleteQTaskType(PushButton_eQTaskType);
  QTask_DeleteQTaskEvent(MenuItem_eGetMenuItemQTaskEvent);
  QTask_DeleteQTaskEvent(MenuItem_eActivateQTaskEvent);
  QTask_DeleteQTaskEvent(MenuItem_eUpdateActiveQTaskEvent);
  QTask_DeleteQTaskType(MenuItem_eQTaskType);
  MenuItem_eQTaskType = 512;
  QTask_DeleteQTaskEvent(MenuItemQTask_eMenuItemInputQTaskEvent);
  QTask_DeleteQTaskEvent(MenuItemQTask_eRegisterHitboxQTaskEvent);
  QTask_DeleteQTaskType(MenuItemQTask_eQTaskType);
  QTask_DeleteQTaskEvent(Sync_eRegisterDirtyRectangleQTaskEvent);
  QTask_DeleteQTaskEvent(Sync_eRedrawDirtyRectangleQTaskEvent);
  QTask_DeleteQTaskType(Sync_eQTaskType);
  QTask_DeleteQTaskType(InputPort_eQTaskType);
  QTask_DeleteQTaskEvent(Input_eGetInputQTaskEvent);
  QTask_DeleteQTaskType(CamQTask_eQTaskType);
  QTask_DeleteQTaskEvent(Particle2DDynCubeObj_eParticle2DCollisionEvaluateQTaskEvent);
  QTask_DeleteQTaskType(Particle2DDynCubeObj_eQTaskType);
  Particle2DDynCubeObj_eQTaskType = 512;
  AnimTrigger_Close();
  QTask_DeleteQTaskEvent(State_eGetStateQTaskEvent);
  QTask_DeleteQTaskEvent(Idle_eActivateQTaskEvent);
  QTask_DeleteQTaskEvent(Idle_eDeactivateQTaskEvent);
  F_Close();
}
