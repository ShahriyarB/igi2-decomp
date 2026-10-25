/* h/2/lodsettings.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: h/2/lodsettings.c:117  [anchor-mhash]
void __cdecl LODSettings_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ptQTask[1].ptNext = nullptr;
  ptQTask[1].ptPrev = nullptr;
  ptQTask[1].tQTaskChildren.ptHead = nullptr;
  ptQTask[1].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[1].tQTaskChildren.ptTail = nullptr;
  ptQTask[1].tQTaskRefList.ptHead = nullptr;
  ptQTask[1].tQTaskRefList.ptMiddle = (struct QReference_s *)1065353216;
  ptQTask[1].tQTaskRefList.ptTail = (struct QReference_s *)1082130432;
}

// source: h/2/lodsettings.c:140  [anchor-mhash]
void __cdecl LODSettings_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  double v2; // st7

  v2 = *(float *)&ptQTask[1].ptNext * 0.019999999552965164;
  Mesh3D_vRadiusImpact = *(float *)&ptQTask[1].tQTaskRefList.ptMiddle;
  Mesh3D_vSplineObjDistance = v2;
  Mesh3D_vRigidObjDistance = *(float *)&ptQTask[1].ptPrev * 0.019999999552965164;
  Mesh3D_vBoneObjDistance = *(float *)&ptQTask[1].tQTaskChildren.ptHead * 0.019999999552965164;
  Mesh3D_vSplineObjCutoff = *(float *)&ptQTask[1].tQTaskChildren.ptMiddle * 0.019999999552965164;
  Mesh3D_vRigidObjCutoff = *(float *)&ptQTask[1].tQTaskChildren.ptTail * 0.019999999552965164;
  Mesh3D_vBoneObjCutoff = *(float *)&ptQTask[1].tQTaskRefList.ptHead * 0.019999999552965164;
  Mesh3D_vIdealRadius = *(float *)&ptQTask[1].tQTaskRefList.ptTail * 4096.0;
}

// source: h/2/lodsettings.c:163  [size]
void __cdecl LODSettings_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = LODSettings_ptParameterList;
}

// source: h/2/lodsettings.c:179  [anchor-mhash]
enum bool __cdecl ModelLODSettings_IsDuplicate(
        struct QTask_s *ptParent,
        struct ModelLODSettings_t *ptModelLODSettings)
{
  struct ModelLODSettings_t *FirstChildOfType; // esi

  FirstChildOfType = (struct ModelLODSettings_t *)QTask_GetFirstChildOfType(ptParent, ModelLODSettings_eQTaskType);
  if ( !FirstChildOfType )
    return false;
  while ( FirstChildOfType == ptModelLODSettings
       || _stricmp(FirstChildOfType->zModelName, ptModelLODSettings->zModelName)
       && ModelLODSettings_IsDuplicate(&FirstChildOfType->tQTask, ptModelLODSettings) == false )
  {
    FirstChildOfType = (struct ModelLODSettings_t *)QTask_GetNextSiblingOfType(
                                                      &FirstChildOfType->tQTask,
                                                      ModelLODSettings_eQTaskType);
    if ( !FirstChildOfType )
      return false;
  }
  return true;
}

// source: h/2/lodsettings.c:217  [anchor-mhash]
struct ModelLODSettings_t *__cdecl ModelLODSettings_FindSettingsForModel(
        struct QTask_s *ptParent,
        char *zModelName,
        struct ModelLODSettings_t *ptSkipModelLODSettings)
{
  unsigned __int16 v3; // bp
  struct ModelLODSettings_t *FirstChildOfType; // edi

  if ( !ptParent )
    return nullptr;
  v3 = ModelLODSettings_eQTaskType;
  FirstChildOfType = (struct ModelLODSettings_t *)QTask_GetFirstChildOfType(ptParent, ModelLODSettings_eQTaskType);
  if ( !FirstChildOfType )
    return nullptr;
  while ( FirstChildOfType == ptSkipModelLODSettings || strcmp(FirstChildOfType->zModelName, zModelName) )
  {
    FirstChildOfType = (struct ModelLODSettings_t *)QTask_GetNextSiblingOfType(&FirstChildOfType->tQTask, v3);
    if ( !FirstChildOfType )
      return nullptr;
  }
  return FirstChildOfType;
}

// source: h/2/lodsettings.c:248  [anchor-mhash]
void __cdecl ModelLODSettings_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ptQTask[1].tQTaskRefList.ptHead = nullptr;
  ptQTask[1].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[1].tQTaskRefList.ptTail = nullptr;
  ptQTask[1].ptParent = nullptr;
  sprintf((char *const)&ptQTask[1], (char *const)&g_zInitialValue);
}

// source: h/2/lodsettings.c:271  [anchor-mhash]
void __cdecl ModelLODSettings_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  char *v2; // edi
  signed int i; // esi
  int v4; // eax
  struct LODVirModel_s *LODVirModelExistsFn; // eax

  v2 = (char *)&ptQTask[1];
  for ( i = strlen((char *)&ptQTask[1]) - 1; i >= 0; v2[i + 1] = 0 )
  {
    if ( _mb_cur_max_6aece0 <= 1 )
      v4 = pctype_6aecec[v2[i]] & 8;
    else
      v4 = isctype(v2[i], 8);
    if ( !v4 )
      break;
    --i;
  }
  if ( !strlen(v2) || ModelLODSettings_IsDuplicate(ptQTask->ptParent, (struct ModelLODSettings_t *)ptQTask) == false )
  {
    if ( *(float *)&ptQTask[1].tQTaskRefList.ptMiddle < (double)*(float *)&ptQTask[1].tQTaskRefList.ptHead )
      ptQTask[1].tQTaskRefList.ptMiddle = ptQTask[1].tQTaskRefList.ptHead;
    if ( *(float *)&ptQTask[1].tQTaskRefList.ptTail < (double)*(float *)&ptQTask[1].tQTaskRefList.ptMiddle )
      ptQTask[1].tQTaskRefList.ptTail = ptQTask[1].tQTaskRefList.ptMiddle;
    if ( *(float *)&ptQTask[1].ptParent < (double)*(float *)&ptQTask[1].tQTaskRefList.ptTail )
      ptQTask[1].ptParent = (struct QTask_s *)ptQTask[1].tQTaskRefList.ptTail;
    if ( *(float *)&ptQTask[1].eQTaskType < (double)*(float *)&ptQTask[1].ptParent )
      *(_DWORD *)&ptQTask[1].eQTaskType = ptQTask[1].ptParent;
    LODVirModelExistsFn = MTP_GetLODVirModelExistsFn(v2);
    if ( LODVirModelExistsFn )
    {
      LODVirModelExistsFn->isLODDistanceSpecified = 1;
      LODVirModelExistsFn->avLODDistance[0] = *(float *)&ptQTask[1].tQTaskRefList.ptHead * 4096.0;
      LODVirModelExistsFn->avLODDistance[1] = *(float *)&ptQTask[1].tQTaskRefList.ptMiddle * 4096.0;
      LODVirModelExistsFn->avLODDistance[2] = *(float *)&ptQTask[1].tQTaskRefList.ptTail * 4096.0;
      LODVirModelExistsFn->avLODDistance[3] = *(float *)&ptQTask[1].ptParent * 4096.0;
      LODVirModelExistsFn->avLODDistance[4] = *(float *)&ptQTask[1].eQTaskType * 4096.0;
    }
  }
}

// source: h/2/lodsettings.c:337  [anchor-mhash]
void __cdecl ModelLODSettings_DeleteHandler(struct QTask_s *ptQTask)
{
  char *v1; // esi
  struct LODVirModel_s *LODVirModelExistsFn; // ebp
  struct ModelLODSettings_t *SettingsForModel; // edi
  struct ModelLODSettings_t *v4; // eax
  struct ModelLODSettings_t *v5; // esi

  v1 = (char *)&ptQTask[1];
  LODVirModelExistsFn = MTP_GetLODVirModelExistsFn((char *)&ptQTask[1]);
  if ( LODVirModelExistsFn )
  {
    SettingsForModel = ModelLODSettings_FindSettingsForModel(
                         &ModelLODSettingsContainer_ptQTask->tQTask,
                         v1,
                         (struct ModelLODSettings_t *)ptQTask);
    v4 = ModelLODSettings_FindSettingsForModel(
           &LocalModelLODSettingsContainer_ptQTask->tQTask,
           v1,
           (struct ModelLODSettings_t *)ptQTask);
    v5 = v4;
    if ( SettingsForModel )
    {
      ((void (__cdecl *)(struct ModelLODSettings_t *, _DWORD))QTask_aatQTaskFinalEvent[ParameterList_eUpdateInternalDataQTaskEvent][SettingsForModel->tQTask.eQTaskType].pfHandler)(
        SettingsForModel,
        0);
      if ( !v5 )
        return;
    }
    else if ( !v4 )
    {
      LODVirModelExistsFn->isLODDistanceSpecified = 0;
      return;
    }
    ((void (__cdecl *)(struct ModelLODSettings_t *, _DWORD))QTask_aatQTaskFinalEvent[ParameterList_eUpdateInternalDataQTaskEvent][v5->tQTask.eQTaskType].pfHandler)(
      v5,
      0);
  }
}

// source: h/2/lodsettings.c:378  [size]
void __cdecl ModelLODSettings_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = ModelLODSettings_ptParameterList;
}

// source: h/2/lodsettings.c:394  [anchor-strings]
void __cdecl ModelLODSettings_PrintQTaskInfoHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct LODVirModel_s *LODVirModelExistsFn; // eax

  LODVirModelExistsFn = MTP_GetLODVirModelExistsFn((char *)&ptQTask[1]);
  if ( LODVirModelExistsFn )
  {
    sprintf(byte_73B710, "Number of LODs: %d", LODVirModelExistsFn->nLOD);
    *(_DWORD *)pxContext = byte_73B710;
  }
}

// source: h/2/lodsettings.c:462  [anchor-mhash]
void __cdecl ModelLODSettingsContainer_LoadSettings(struct QTask_s *ptQTask)
{
  struct QHashTable_s *v1; // esi
  unsigned int v2; // eax
  int v3; // eax
  struct Script_s *v4; // eax
  struct Script_s *v5; // edi

  v1 = Symbol_ptSymbolHashTable;
  v2 = Symbol_ptSymbolHashTable->tPrivate.pfHashFunction(Symbol_ptSymbolHashTable->tPrivate.nHashTableSize, "Task_New");
  v3 = ((int  (__cdecl *)(struct QHashTable_s *, unsigned int, const void *))Symbol_ptSymbolHashTable->tPrivate.pfFindElement)(v1, v2, (const void *)("Task_New"));
  if ( !v3 || !*(_DWORD *)(v3 + 20) )
  {
    LDebug_Error("Script_SetSymbolContext(): Symbol not found: %s", "Task_New");
    abort();
  }
  *(_DWORD *)(v3 + 24) = ptQTask;
  v4 = Script_New((char *)&ptQTask[1].tQTaskChildren.ptMiddle);
  v5 = v4;
  if ( v4 )
  {
    Level_zScriptfile = (char *)&ptQTask[1].tQTaskChildren.ptMiddle;
    Level_isLegalTask = 1;
    Level_nLinenumber = 0;
    Level_isFirstChild = 0;
    Level_ptRootQTask = nullptr;
    Script_Execute(v4);
    Script_Delete(v5);
    File_GetFileTime((struct FileTime_s *)&ptQTask[1].ptPrev, (char *)&ptQTask[1].tQTaskChildren.ptMiddle);
  }
}

// source: h/2/lodsettings.c:510  [anchor-mhash]
void __cdecl ModelLODSettingsContainer_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  LOBYTE(ptQTask[1].ptNext) = 0;
  strcpy((char *)&ptQTask[1].tQTaskChildren.ptMiddle, "lod.qsc");
  ModelLODSettingsContainer_ptQTask = (struct ModelLODSettingsContainer_t *)ptQTask;
  ModelLODSettingsContainer_LoadSettings(ptQTask);
}

// source: h/2/lodsettings.c:531  [size]
void __cdecl ModelLODSettingsContainer_GetParameterListHandler(
        struct QTask_s *ptQTask,
        void *pxContext)
{
  *(_DWORD *)pxContext = ModelLODSettingsContainer_ptParameterList;
}

// source: h/2/lodsettings.c:547  [size]
void __cdecl ModelLODSettingsContainer_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ;
}

// source: h/2/lodsettings.c:586  [size]
void __cdecl ModelLODSettingsContainer_DeleteHandler(struct QTask_s *ptQTask)
{
  ModelLODSettingsContainer_ptQTask = nullptr;
}

// source: h/2/lodsettings.c:625  [anchor-mhash]
void __cdecl LocalModelLODSettingsContainer_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  LOBYTE(ptQTask[1].ptNext) = 0;
  LocalModelLODSettingsContainer_ptQTask = (struct ModelLODSettingsContainer_t *)ptQTask;
  strcpy((char *)&ptQTask[1].tQTaskChildren.ptMiddle, "MISSION:lod.qsc");
}

// source: h/2/lodsettings.c:645  [size]
void __cdecl LocalModelLODSettingsContainer_DeleteHandler(struct QTask_s *ptQTask)
{
  LocalModelLODSettingsContainer_ptQTask = nullptr;
}

// source: h/2/lodsettings.c:659  [size]
// attributes: thunk
void __cdecl LocalModelLODSettingsContainer_UpdateInternalDataAfterLoadHandler(struct QTask_s *ptQTask)
{
  ModelLODSettingsContainer_LoadSettings(ptQTask);
}

// source: h/2/lodsettings.c:674  [size]
unsigned __int16 __cdecl LODSettings_GetQTaskType()
{
  return LODSettings_eQTaskType;
}

// source: h/2/lodsettings.c:687  [size]
unsigned __int16 __cdecl ModelLODSettings_GetQTaskType()
{
  return ModelLODSettings_eQTaskType;
}

// source: h/2/lodsettings.c:700  [size]
unsigned __int16 __cdecl ModelLODSettingsContainer_GetQTaskType()
{
  return ModelLODSettingsContainer_eQTaskType;
}

// source: h/2/lodsettings.c:713  [size]
unsigned __int16 __cdecl LocalModelLODSettingsContainer_GetQTaskType()
{
  return LocalModelLODSettingsContainer_eQTaskType;
}

// source: h/2/lodsettings.c:726  [anchor-hash]
void __cdecl LODSettings_Update()
{
  if ( ModelLODSettingsContainer_ptQTask )
    QTask_TriggerQTaskEventRecursively(
      &ModelLODSettingsContainer_ptQTask->tQTask,
      ParameterList_eUpdateInternalDataQTaskEvent,
      nullptr);
  if ( LocalModelLODSettingsContainer_ptQTask )
    QTask_TriggerQTaskEventRecursively(
      &LocalModelLODSettingsContainer_ptQTask->tQTask,
      ParameterList_eUpdateInternalDataQTaskEvent,
      nullptr);
}

// source: h/2/lodsettings.c:746  [anchor-strings]
void __cdecl LODSettings_Open()
{
  unsigned __int16 BaseQTaskType; // ax
  unsigned __int16 v1; // ax
  unsigned __int16 v2; // ax
  unsigned __int16 v3; // ax
  __int16 v4; // bx
  unsigned __int16 v5; // si
  unsigned __int16 v6; // di
  unsigned __int16 v7; // bx
  __int16 v8; // bp
  __int16 v9; // bx
  unsigned __int16 v10; // si
  struct ParameterList_s *v11; // eax
  struct ParameterList_s *v12; // eax
  struct ParameterList_s *v13; // eax
  struct ParameterList_s *v14; // ecx

  BaseQTaskType = QTask_GetBaseQTaskType();
  LODSettings_eQTaskType = QTask_NewQTaskType("LODSettings", 72, BaseQTaskType, 0, 0);
  v1 = QTask_GetBaseQTaskType();
  ModelLODSettings_eQTaskType = QTask_NewQTaskType("ModelLODSettings", 80, v1, 0, 0);
  v2 = QTask_GetBaseQTaskType();
  ModelLODSettingsContainer_eQTaskType = QTask_NewQTaskType("ModelLODSettingsContainer", 308, v2, 0, 0);
  v3 = QTask_NewQTaskType("LocalModelLODSettingsContainer", 308, ModelLODSettingsContainer_eQTaskType, 0, 0);
  v4 = Level_eAllowSaveQTaskEvent;
  v5 = ModelLODSettings_eQTaskType;
  v6 = v3;
  LocalModelLODSettingsContainer_eQTaskType = v3;
  QTask_LinkQTaskEventHandlerFn(
    ModelLODSettings_eQTaskType,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveHandler);
  QTask_LinkQTaskEventHandlerFn(
    v6,
    v4,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveNoChildrenHandler);
  v7 = LODSettings_eQTaskType;
  QTask_LinkQTaskEventHandlerFn(
    LODSettings_eQTaskType,
    0,
    (void (__cdecl *)(struct QTask_s *, void *))LODSettings_CreateHandler);
  v8 = ParameterList_eUpdateInternalDataQTaskEvent;
  QTask_LinkQTaskEventHandlerFn(
    v7,
    ParameterList_eUpdateInternalDataQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))LODSettings_UpdateInternalDataHandler);
  QTask_LinkQTaskEventHandlerFn(
    v7,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))LODSettings_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(v5, 0, ModelLODSettings_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v5, 2, ModelLODSettings_DeleteHandler);
  QTask_LinkQTaskEventHandlerFn(v5, v8, ModelLODSettings_UpdateInternalDataHandler);
  v9 = ParameterList_eGetParameterListQTaskEvent;
  QTask_LinkQTaskEventHandlerFn(
    v5,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))ModelLODSettings_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(v5, Level_ePrintQTaskInfoQTaskEvent, ModelLODSettings_PrintQTaskInfoHandler);
  v10 = ModelLODSettingsContainer_eQTaskType;
  QTask_LinkQTaskEventHandlerFn(ModelLODSettingsContainer_eQTaskType, 0, ModelLODSettingsContainer_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(
    v10,
    2,
    (void (__cdecl *)(struct QTask_s *))ModelLODSettingsContainer_DeleteHandler);
  QTask_LinkQTaskEventHandlerFn(
    v10,
    v8,
    (void (__cdecl *)(struct QTask_s *, void *))ModelLODSettingsContainer_UpdateInternalDataHandler);
  QTask_LinkQTaskEventHandlerFn(
    v10,
    v9,
    (void (__cdecl *)(struct QTask_s *, void *))ModelLODSettingsContainer_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(v6, 0, LocalModelLODSettingsContainer_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(
    v6,
    2,
    (void (__cdecl *)(struct QTask_s *))LocalModelLODSettingsContainer_DeleteHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(
    v6,
    Level_eUpdateInternalDataAfterLoadEvent,
    LocalModelLODSettingsContainer_UpdateInternalDataAfterLoadHandler);
  v11 = (struct ParameterList_s *)Mem_AllocFn(172, 4);
  v11->nParameters = 0;
  v11->nMaxParameters = 8;
  v11->ptParameterListItem = (struct ParameterListItem_s *)&v11[1];
  LODSettings_ptParameterList = v11;
  v12 = (struct ParameterList_s *)Mem_AllocFn(132, 4);
  v12->nParameters = 0;
  v12->nMaxParameters = 6;
  v12->ptParameterListItem = (struct ParameterListItem_s *)&v12[1];
  ModelLODSettings_ptParameterList = v12;
  v13 = (struct ParameterList_s *)Mem_AllocFn(52, 4);
  v14 = LODSettings_ptParameterList;
  v13->nParameters = 0;
  v13->nMaxParameters = 2;
  v13->ptParameterListItem = (struct ParameterListItem_s *)&v13[1];
  ModelLODSettingsContainer_ptParameterList = v13;
  ParameterList_AddParameterMinMax(
    v14,
    0x28u,
    Level_eParameterTypeReal32,
    "Distance to first switch, relative to object radius (Spline Objects)",
    7u,
    0.0,
    1500.0);
  ParameterList_AddParameterMinMax(
    LODSettings_ptParameterList,
    0x2Cu,
    Level_eParameterTypeReal32,
    "Distance to first switch, relative to object radius (Rigid Objects)",
    7u,
    0.0,
    1500.0);
  ParameterList_AddParameterMinMax(
    LODSettings_ptParameterList,
    0x30u,
    Level_eParameterTypeReal32,
    "Distance to first switch, relative to object radius (Bone Objects)",
    7u,
    0.0,
    1500.0);
  ParameterList_AddParameterMinMax(
    LODSettings_ptParameterList,
    0x34u,
    Level_eParameterTypeReal32,
    "Cutoff distance, relative to object radius (Spline Objects)",
    7u,
    0.0,
    10000.0);
  ParameterList_AddParameterMinMax(
    LODSettings_ptParameterList,
    0x38u,
    Level_eParameterTypeReal32,
    "Cutoff distance, relative to object radius (Rigid Objects)",
    7u,
    0.0,
    10000.0);
  ParameterList_AddParameterMinMax(
    LODSettings_ptParameterList,
    0x3Cu,
    Level_eParameterTypeReal32,
    "Cutoff distance, relative to object radius (Bone Objects)",
    7u,
    0.0,
    10000.0);
  ParameterList_AddParameterMinMax(
    LODSettings_ptParameterList,
    0x40u,
    Level_eParameterTypeReal32,
    "Degree to which radius affects LOD",
    7u,
    0.0,
    1.0);
  ParameterList_AddParameter(
    LODSettings_ptParameterList,
    0x44u,
    Level_eParameterTypeReal32,
    "Ideal radius",
    7u,
    nullptr);
  ParameterList_AddParameter(
    ModelLODSettings_ptParameterList,
    0x28u,
    Level_eParameterTypeString16,
    "Model",
    7u,
    nullptr);
  ParameterList_AddParameterMinMax(
    ModelLODSettings_ptParameterList,
    0x3Cu,
    Level_eParameterTypeReal32,
    "Distance to LOD 2",
    7u,
    0.0,
    1000.0);
  ParameterList_AddParameterMinMax(
    ModelLODSettings_ptParameterList,
    0x40u,
    Level_eParameterTypeReal32,
    "Distance to LOD 3",
    7u,
    0.0,
    1000.0);
  ParameterList_AddParameterMinMax(
    ModelLODSettings_ptParameterList,
    0x44u,
    Level_eParameterTypeReal32,
    "Distance to LOD 4",
    7u,
    0.0,
    1000.0);
  ParameterList_AddParameterMinMax(
    ModelLODSettings_ptParameterList,
    0x48u,
    Level_eParameterTypeReal32,
    "Distance to LOD 5",
    7u,
    0.0,
    1000.0);
  ParameterList_AddParameterMinMax(
    ModelLODSettings_ptParameterList,
    0x4Cu,
    Level_eParameterTypeReal32,
    (char *)&g_zFontName_0.ptParent,
    7u,
    0.0,
    100000.0);
  ParameterList_AddParameter(
    ModelLODSettingsContainer_ptParameterList,
    0x28u,
    Level_eParameterTypePushButton,
    "Save",
    6u,
    nullptr);
  ParameterList_AddParameter(
    ModelLODSettingsContainer_ptParameterList,
    0x34u,
    Level_eParameterTypeString256,
    (char *)&g_zFontName_0.tQTaskRefList.ptMiddle,
    3u,
    nullptr);
}

// source: h/2/lodsettings.c:810  [size]
void __cdecl LODSettings_Close()
{
  int v0; // esi
  int v1; // esi
  int v2; // esi

  if ( ModelLODSettings_ptParameterList )
  {
    v0 = *(_DWORD *)((unsigned int)&ModelLODSettings_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
  if ( ModelLODSettingsContainer_ptParameterList )
  {
    v1 = *(_DWORD *)((unsigned int)&ModelLODSettingsContainer_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v1);
    memset(*(void **)(v1 + 8), 0xCDu, *(_DWORD *)(v1 + 16));
    free((void *)v1);
  }
  if ( LODSettings_ptParameterList )
  {
    v2 = *(_DWORD *)((unsigned int)&LODSettings_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v2);
    memset(*(void **)(v2 + 8), 0xCDu, *(_DWORD *)(v2 + 16));
    free((void *)v2);
  }
  QTask_DeleteQTaskType(LocalModelLODSettingsContainer_eQTaskType);
  QTask_DeleteQTaskType(ModelLODSettingsContainer_eQTaskType);
  QTask_DeleteQTaskType(ModelLODSettings_eQTaskType);
  QTask_DeleteQTaskType(LODSettings_eQTaskType);
}
