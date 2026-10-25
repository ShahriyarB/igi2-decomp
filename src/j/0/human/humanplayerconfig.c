/* j/0/human/humanplayerconfig.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/human/humanplayerconfig.c:68  [size]
void __cdecl HumanPlayerConfig_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ptQTask[1].ptNext = nullptr;
}

// source: j/0/human/humanplayerconfig.c:84  [size]
void __cdecl HumanPlayerConfig_DeleteHandler(struct QTask_s *ptQTask)
{
  ;
}

// source: j/0/human/humanplayerconfig.c:96  [size]
void __cdecl HumanPlayerConfig_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = HumanPlayerConfig_ptParameterList;
}

// source: j/0/human/humanplayerconfig.c:112  [size]
void __cdecl HumanPlayerConfig_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ;
}

// source: j/0/human/humanplayerconfig.c:133  [size]
void __cdecl HumanPlayerConfigItem_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ptQTask[5].tQTaskChildren.ptTail = nullptr;
  ptQTask[5].tQTaskRefList.ptHead = nullptr;
  ptQTask[5].tQTaskChildren.ptMiddle = (struct QTask_s *)1097859072;
}

// source: j/0/human/humanplayerconfig.c:152  [size]
void __cdecl HumanPlayerConfigItem_RunHandler(struct QTask_s *ptQTask)
{
  ;
}

// source: j/0/human/humanplayerconfig.c:164  [anchor-mhash]
void __cdecl HumanPlayerConfigItem_DeleteHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptTail; // eax
  int v2; // esi
  struct QReference_s *ptHead; // eax
  int v4; // esi

  ptTail = ptQTask[5].tQTaskChildren.ptTail;
  if ( ptTail )
  {
    v2 = *(_DWORD *)((unsigned int)&ptTail[-1].eQTaskType & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v2);
    memset(*(void **)(v2 + 8), 0xCDu, *(_DWORD *)(v2 + 16));
    free((void *)v2);
    ptQTask[5].tQTaskChildren.ptTail = nullptr;
  }
  ptHead = ptQTask[5].tQTaskRefList.ptHead;
  if ( ptHead )
  {
    v4 = *(_DWORD *)((unsigned int)&ptHead[-1].pxObject & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v4);
    memset(*(void **)(v4 + 8), 0xCDu, *(_DWORD *)(v4 + 16));
    free((void *)v4);
    ptQTask[5].tQTaskRefList.ptHead = nullptr;
  }
}

// source: j/0/human/humanplayerconfig.c:188  [size]
void __cdecl HumanPlayerConfigItem_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = HumanPlayerConfigItem_ptParameterList;
}

// source: j/0/human/humanplayerconfig.c:204  [anchor-mhash]
void __cdecl HumanPlayerConfigItem_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *ptTail; // edx
  struct QReference_s *ptHead; // edx

  ptTail = ptQTask[5].tQTaskChildren.ptTail;
  if ( ptTail )
    Script_ParseLineInt32((char *)ptTail);
  ptHead = ptQTask[5].tQTaskRefList.ptHead;
  if ( ptHead )
    Script_ParseLineInt32((char *)ptHead);
  HumanPlayer_UpdateParameters((struct HumanPlayerConfigItem_t *)ptQTask);
}

// source: j/0/human/humanplayerconfig.c:232  [anchor-hash]
void __cdecl HumanPlayerConfig_Open()
{
  unsigned __int16 BaseQTaskType; // ax
  unsigned __int16 v1; // ax
  unsigned __int16 v2; // ax
  unsigned __int16 v3; // si
  struct ParameterList_s *v4; // eax
  int v5; // edx
  unsigned __int16 v6; // si
  struct ParameterList_s *v7; // eax
  int v8; // edx

  BaseQTaskType = QTask_GetBaseQTaskType();
  HumanPlayerConfig_eQTaskType = QTask_NewQTaskType("HumanPlayerConfig", 44, BaseQTaskType, 0, 0);
  v1 = QTask_GetBaseQTaskType();
  v2 = QTask_NewQTaskType("HumanPlayerConfigItem", 224, v1, 0, 0);
  v3 = HumanPlayerConfig_eQTaskType;
  HumanPlayerConfigItem_eQTaskType = v2;
  QTask_LinkQTaskEventHandlerFn(
    HumanPlayerConfig_eQTaskType,
    0,
    (void (__cdecl *)(struct QTask_s *, void *))HumanPlayerConfig_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v3, 2, (void (__cdecl *)(struct QTask_s *))HumanPlayerConfig_DeleteHandler);
  QTask_LinkQTaskEventHandlerFn(
    v3,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))HumanPlayerConfig_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(
    v3,
    ParameterList_eUpdateInternalDataQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))HumanPlayerConfig_UpdateInternalDataHandler);
  QTask_LinkQTaskEventHandlerFn(
    v3,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveHandler);
  v4 = (struct ParameterList_s *)Mem_AllocFn(32, 4);
  v5 = Level_eParameterTypePushButton;
  v4->ptParameterListItem = (struct ParameterListItem_s *)&v4[1];
  v4->nParameters = 0;
  v4->nMaxParameters = 1;
  HumanPlayerConfig_ptParameterList = v4;
  ParameterList_AddParameter(v4, 0x28u, v5, "Save all settings", 7u, nullptr);
  v6 = HumanPlayerConfigItem_eQTaskType;
  QTask_LinkQTaskEventHandlerFn(
    HumanPlayerConfigItem_eQTaskType,
    0,
    (void (__cdecl *)(struct QTask_s *, void *))HumanPlayerConfigItem_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v6, 1, (void (__cdecl *)(struct QTask_s *))HumanPlayerConfigItem_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v6, 2, HumanPlayerConfigItem_DeleteHandler);
  QTask_LinkQTaskEventHandlerFn(
    v6,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))HumanPlayerConfigItem_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(
    v6,
    ParameterList_eUpdateInternalDataQTaskEvent,
    HumanPlayerConfigItem_UpdateInternalDataHandler);
  QTask_LinkQTaskEventHandlerFn(
    v6,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveNoChildrenHandler);
  v7 = (struct ParameterList_s *)Mem_AllocFn(1012, 4);
  v8 = Level_eParameterTypeReal32;
  v7->ptParameterListItem = (struct ParameterListItem_s *)&v7[1];
  v7->nParameters = 0;
  v7->nMaxParameters = 50;
  HumanPlayerConfigItem_ptParameterList = v7;
  ParameterList_AddParameter(v7, 0x28u, v8, "Movement speed scale", 7u, nullptr);
  ParameterList_AddParameter(
    HumanPlayerConfigItem_ptParameterList,
    0x2Cu,
    Level_eParameterTypeReal32,
    "Forward jump speed (km/h)",
    7u,
    nullptr);
  ParameterList_AddParameter(
    HumanPlayerConfigItem_ptParameterList,
    0x30u,
    Level_eParameterTypeReal32,
    "Upward jump speed (km/h)",
    7u,
    nullptr);
  ParameterList_AddParameter(
    HumanPlayerConfigItem_ptParameterList,
    0x34u,
    Level_eParameterTypeReal32,
    "In air control speed (km/h)",
    7u,
    nullptr);
  ParameterList_AddParameter(
    HumanPlayerConfigItem_ptParameterList,
    0xD4u,
    Level_eParameterTypeReal32,
    "Throwing base velocity (km/h)",
    7u,
    nullptr);
  ParameterList_AddParameter(
    HumanPlayerConfigItem_ptParameterList,
    0x38u,
    Level_eParameterTypeReal32,
    "Peek length right/left (m)",
    7u,
    nullptr);
  ParameterList_AddParameter(
    HumanPlayerConfigItem_ptParameterList,
    0x3Cu,
    Level_eParameterTypeReal32,
    "Peek length up from crouch (m)",
    7u,
    nullptr);
  ParameterList_AddParameter(
    HumanPlayerConfigItem_ptParameterList,
    0x40u,
    Level_eParameterTypeReal32,
    "Time to reach peek length (s)",
    7u,
    nullptr);
  ParameterList_AddParameter(
    HumanPlayerConfigItem_ptParameterList,
    0x44u,
    Level_eParameterTypeReal32,
    "Max damage scale",
    7u,
    nullptr);
  ParameterList_AddParameter(
    HumanPlayerConfigItem_ptParameterList,
    0x48u,
    Level_eParameterTypeReal32,
    "Electric fence damage scale",
    7u,
    nullptr);
  ParameterList_AddParameter(
    HumanPlayerConfigItem_ptParameterList,
    0x4Cu,
    Level_eParameterTypeReal32,
    "Right foot damage multiplier SINGLEPLAYER",
    7u,
    nullptr);
  ParameterList_AddParameter(
    HumanPlayerConfigItem_ptParameterList,
    0x50u,
    Level_eParameterTypeReal32,
    "Right lower leg damage multiplier SINGLEPLAYER",
    7u,
    nullptr);
  ParameterList_AddParameter(
    HumanPlayerConfigItem_ptParameterList,
    0x54u,
    Level_eParameterTypeReal32,
    "Right upper leg damage multiplier SINGLEPLAYER",
    7u,
    nullptr);
  ParameterList_AddParameter(
    HumanPlayerConfigItem_ptParameterList,
    0x58u,
    Level_eParameterTypeReal32,
    "Right hand damage multiplier SINGLEPLAYER",
    7u,
    nullptr);
  ParameterList_AddParameter(
    HumanPlayerConfigItem_ptParameterList,
    0x5Cu,
    Level_eParameterTypeReal32,
    "Right lower arm damage multiplier SINGLEPLAYER",
    7u,
    nullptr);
  ParameterList_AddParameter(
    HumanPlayerConfigItem_ptParameterList,
    0x60u,
    Level_eParameterTypeReal32,
    "Right upper arm damage multiplier SINGLEPLAYER",
    7u,
    nullptr);
  ParameterList_AddParameter(
    HumanPlayerConfigItem_ptParameterList,
    0x64u,
    Level_eParameterTypeReal32,
    "Left foot damage multiplier SINGLEPLAYER",
    7u,
    nullptr);
  ParameterList_AddParameter(
    HumanPlayerConfigItem_ptParameterList,
    0x68u,
    Level_eParameterTypeReal32,
    "Left lower leg damage multiplier SINGLEPLAYER",
    7u,
    nullptr);
  ParameterList_AddParameter(
    HumanPlayerConfigItem_ptParameterList,
    0x6Cu,
    Level_eParameterTypeReal32,
    "Left upper leg damage multiplier SINGLEPLAYER",
    7u,
    nullptr);
  ParameterList_AddParameter(
    HumanPlayerConfigItem_ptParameterList,
    0x70u,
    Level_eParameterTypeReal32,
    "Left hand damage multiplier SINGLEPLAYER",
    7u,
    nullptr);
  ParameterList_AddParameter(
    HumanPlayerConfigItem_ptParameterList,
    0x74u,
    Level_eParameterTypeReal32,
    "Left lower arm damage multiplier SINGLEPLAYER",
    7u,
    nullptr);
  ParameterList_AddParameter(
    HumanPlayerConfigItem_ptParameterList,
    0x78u,
    Level_eParameterTypeReal32,
    "Left upper arm damage multiplier SINGLEPLAYER",
    7u,
    nullptr);
  ParameterList_AddParameter(
    HumanPlayerConfigItem_ptParameterList,
    0x7Cu,
    Level_eParameterTypeReal32,
    "Upperbody damage multiplier SINGLEPLAYER",
    7u,
    nullptr);
  ParameterList_AddParameter(
    HumanPlayerConfigItem_ptParameterList,
    0x80u,
    Level_eParameterTypeReal32,
    "Chest damage multiplier SINGLEPLAYER",
    7u,
    nullptr);
  ParameterList_AddParameter(
    HumanPlayerConfigItem_ptParameterList,
    0x84u,
    Level_eParameterTypeReal32,
    "Back damage multiplier SINGLEPLAYER",
    7u,
    nullptr);
  ParameterList_AddParameter(
    HumanPlayerConfigItem_ptParameterList,
    0x88u,
    Level_eParameterTypeReal32,
    "Groin damage multiplier SINGLEPLAYER",
    7u,
    nullptr);
  ParameterList_AddParameter(
    HumanPlayerConfigItem_ptParameterList,
    0x8Cu,
    Level_eParameterTypeReal32,
    "Head damage multiplier SINGLEPLAYER",
    7u,
    nullptr);
  ParameterList_AddParameter(
    HumanPlayerConfigItem_ptParameterList,
    0x90u,
    Level_eParameterTypeReal32,
    "Right foot damage multiplier MULTIPLAYER",
    7u,
    nullptr);
  ParameterList_AddParameter(
    HumanPlayerConfigItem_ptParameterList,
    0x94u,
    Level_eParameterTypeReal32,
    "Right lower leg damage multiplier MULTIPLAYER",
    7u,
    nullptr);
  ParameterList_AddParameter(
    HumanPlayerConfigItem_ptParameterList,
    0x98u,
    Level_eParameterTypeReal32,
    "Right upper leg damage multiplier MULTIPLAYER",
    7u,
    nullptr);
  ParameterList_AddParameter(
    HumanPlayerConfigItem_ptParameterList,
    0x9Cu,
    Level_eParameterTypeReal32,
    "Right hand damage multiplier MULTIPLAYER",
    7u,
    nullptr);
  ParameterList_AddParameter(
    HumanPlayerConfigItem_ptParameterList,
    0xA0u,
    Level_eParameterTypeReal32,
    "Right lower arm damage multiplier MULTIPLAYER",
    7u,
    nullptr);
  ParameterList_AddParameter(
    HumanPlayerConfigItem_ptParameterList,
    0xA4u,
    Level_eParameterTypeReal32,
    "Right upper arm damage multiplier MULTIPLAYER",
    7u,
    nullptr);
  ParameterList_AddParameter(
    HumanPlayerConfigItem_ptParameterList,
    0xA8u,
    Level_eParameterTypeReal32,
    "Left foot damage multiplier MULTIPLAYER",
    7u,
    nullptr);
  ParameterList_AddParameter(
    HumanPlayerConfigItem_ptParameterList,
    0xACu,
    Level_eParameterTypeReal32,
    "Left lower leg damage multiplier MULTIPLAYER",
    7u,
    nullptr);
  ParameterList_AddParameter(
    HumanPlayerConfigItem_ptParameterList,
    0xB0u,
    Level_eParameterTypeReal32,
    "Left upper leg damage multiplier MULTIPLAYER",
    7u,
    nullptr);
  ParameterList_AddParameter(
    HumanPlayerConfigItem_ptParameterList,
    0xB4u,
    Level_eParameterTypeReal32,
    "Left hand damage multiplier MULTIPLAYER",
    7u,
    nullptr);
  ParameterList_AddParameter(
    HumanPlayerConfigItem_ptParameterList,
    0xB8u,
    Level_eParameterTypeReal32,
    "Left lower arm damage multiplier MULTIPLAYER",
    7u,
    nullptr);
  ParameterList_AddParameter(
    HumanPlayerConfigItem_ptParameterList,
    0xBCu,
    Level_eParameterTypeReal32,
    "Left upper arm damage multiplier MULTIPLAYER",
    7u,
    nullptr);
  ParameterList_AddParameter(
    HumanPlayerConfigItem_ptParameterList,
    0xC0u,
    Level_eParameterTypeReal32,
    "Upperbody damage multiplier MULTIPLAYER",
    7u,
    nullptr);
  ParameterList_AddParameter(
    HumanPlayerConfigItem_ptParameterList,
    0xC4u,
    Level_eParameterTypeReal32,
    "Chest damage multiplier MULTIPLAYER",
    7u,
    nullptr);
  ParameterList_AddParameter(
    HumanPlayerConfigItem_ptParameterList,
    0xC8u,
    Level_eParameterTypeReal32,
    "Back damage multiplier MULTIPLAYER",
    7u,
    nullptr);
  ParameterList_AddParameter(
    HumanPlayerConfigItem_ptParameterList,
    0xCCu,
    Level_eParameterTypeReal32,
    "Groin damage multiplier MULTIPLAYER",
    7u,
    nullptr);
  ParameterList_AddParameter(
    HumanPlayerConfigItem_ptParameterList,
    0xD0u,
    Level_eParameterTypeReal32,
    "Head damage multiplier MULTIPLAYER",
    7u,
    nullptr);
  ParameterList_AddParameter(
    HumanPlayerConfigItem_ptParameterList,
    0xD8u,
    Level_eParameterTypeVarString,
    "Define weapon cycle script",
    7u,
    nullptr);
  ParameterList_AddParameter(
    HumanPlayerConfigItem_ptParameterList,
    0xDCu,
    Level_eParameterTypeVarString,
    "Define ammo limit script",
    7u,
    nullptr);
}

// source: j/0/human/humanplayerconfig.c:319  [size]
void __cdecl HumanPlayerConfig_Close()
{
  int v0; // esi
  int v1; // esi

  if ( HumanPlayerConfig_ptParameterList )
  {
    v0 = *(_DWORD *)((unsigned int)&HumanPlayerConfig_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
  if ( HumanPlayerConfigItem_ptParameterList )
  {
    v1 = *(_DWORD *)((unsigned int)&HumanPlayerConfigItem_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v1);
    memset(*(void **)(v1 + 8), 0xCDu, *(_DWORD *)(v1 + 16));
    free((void *)v1);
  }
  QTask_DeleteQTaskType(HumanPlayerConfig_eQTaskType);
  QTask_DeleteQTaskType(HumanPlayerConfigItem_eQTaskType);
}

// source: j/0/human/humanplayerconfig.c:338  [size]
unsigned __int16 __cdecl HumanPlayerConfig_GetQTaskType()
{
  return HumanPlayerConfig_eQTaskType;
}

// source: j/0/human/humanplayerconfig.c:353  [size]
unsigned __int16 __cdecl HumanPlayerConfigItem_GetQTaskType()
{
  return HumanPlayerConfigItem_eQTaskType;
}

// source: j/0/human/humanplayerconfig.c:368  [anchor-hash]
void __cdecl HumanPlayerConfig_LoadSettings(struct QTask_s *ptParentQTask)
{
  struct QTask_s *v1; // eax

  v1 = QTask_NewFn(ptParentQTask, HumanPlayerConfig_eQTaskType, nullptr);
  if ( v1 )
  {
    HumanPlayerConfig_ptHumanPlayerConfigQTask = v1;
    Level_LoadQTask(v1, "LOCAL:humanplayer/humanplayer.qsc", false);
  }
}
