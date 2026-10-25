/* j/0/objects/minefield.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/objects/minefield.c:95  [anchor-mhash]
void __cdecl MineField_Explode(struct MineField_s *ptMineField)
{
  #pragma pack(push, 1)
  union
  {
    struct { float vFullRange; };
    struct { char igi2_o1[4]; float vFallOffRange; };
    struct { char igi2_o2[72]; struct GetCameraTargetInfoContext_s tGetCameraTargetInfoContext; };
    char igi2_extent[164];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  unsigned int nQTaskID; // eax
  struct QReference_s *v2; // eax
  struct QTask_s *pxObject; // ebx
  unsigned __int16 eQTaskType; // dx
  void (__cdecl *pfHandler)(struct QTask_s *, struct GetCameraTargetInfoContext_s *); // eax

  nQTaskID = ptMineField->nQTaskID;
  if ( nQTaskID < 0x1000 )
  {
    v2 = Level_atLevelQTaskID[nQTaskID];
    if ( v2 )
    {
      pxObject = (struct QTask_s *)v2->pxObject;
      if ( pxObject )
      {
        eQTaskType = pxObject->eQTaskType;
        if ( QTask_IsQTaskTypeDerived(eQTaskType, Human_eQTaskType) == false
          || !LOBYTE(pxObject[29].tQTaskRefList.ptHead) )
        {
          pfHandler = (void (__cdecl *)(struct QTask_s *, struct GetCameraTargetInfoContext_s *))QTask_aatQTaskFinalEvent[8][eQTaskType].pfHandler;
          if ( pfHandler )
          {
            igi2_frame.tGetCameraTargetInfoContext.zName = nullptr;
            pfHandler(pxObject, &igi2_frame.tGetCameraTargetInfoContext);
            if ( ptMineField->isSnapExplosionToGround )
              GameFunctions_SnapToGround(pxObject, &igi2_frame.tGetCameraTargetInfoContext.tPos);
            igi2_frame.vFallOffRange = ptMineField->vFalloffRadius * 4096.0;
            igi2_frame.vFullRange = ptMineField->vRadius * 4096.0;
            Explosion0_New(
              &igi2_frame.tGetCameraTargetInfoContext.tPos,
              1,
              (__int64)(ptMineField->vDelay * 30.0),
              ptMineField->vExplosionDamageScale,
              igi2_frame.vFullRange,
              igi2_frame.vFallOffRange,
              6144.0,
              ptMineField->nFragment,
              ptMineField->nFireball,
              nullptr,
              "1009_01_1",
              ptMineField->azSound,
              -1,
              0,
              307200.0,
              nullptr,
              &ptMineField->tEditorRigidObj.tQTask,
              EXPLOSIONDAMAGE_LINEAR_FALLOFF);
          }
        }
      }
    }
  }
}

// source: j/0/objects/minefield.c:164  [anchor-mhash]
void __cdecl MineField_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ptQTask[3].tQTaskRefList.ptMiddle = (struct QReference_s *)1077936128;
  ptQTask[3].ptParent = (struct QTask_s *)1077936128;
  ptQTask[3].tQTaskRefList.ptTail = (struct QReference_s *)1069547520;
  *(_DWORD *)&ptQTask[3].eQTaskType = 0;
  ptQTask[4].ptNext = (struct QTask_s *)3;
  ptQTask[4].ptPrev = (struct QTask_s *)3;
  LOBYTE(ptQTask[4].tQTaskChildren.ptHead) = 0;
  ptQTask[5].ptPrev = (struct QTask_s *)1084227584;
  ptQTask[5].tQTaskChildren.ptMiddle = nullptr;
  LOBYTE(ptQTask[5].tQTaskChildren.ptHead) = 1;
  ptQTask[5].ptNext = nullptr;
  ptQTask[1].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[1].tQTaskRefList.ptTail = nullptr;
  ptQTask[1].ptParent = nullptr;
  ptQTask[3].tQTaskRefList.ptHead = nullptr;
}

// source: j/0/objects/minefield.c:214  [anchor-mhash]
void __cdecl MineField_RunHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptMiddle; // eax

  ptMiddle = ptQTask[5].tQTaskChildren.ptMiddle;
  if ( ptMiddle != (struct QTask_s *)-1 )
  {
    if ( ptMiddle )
    {
      ptQTask[5].tQTaskChildren.ptMiddle = (struct QTask_s *)((char *)ptMiddle - 1);
    }
    else if ( ptQTask[1].tQTaskRefList.ptMiddle
           && ptQTask[1].tQTaskRefList.ptTail->ptNext
           && ptQTask[1].ptParent
           && Level_RunLevelExpression((struct LevelExpression_s *)&ptQTask[1].tQTaskRefList.ptMiddle, ptQTask) != 0.0 )
    {
      MineField_Explode((struct MineField_s *)ptQTask);
      ptQTask[5].tQTaskChildren.ptMiddle = (struct QTask_s *)(__int64)(*(float *)&ptQTask[5].ptPrev * 30.0);
    }
  }
}

// source: j/0/objects/minefield.c:252  [size]
void __cdecl MineField_DeleteHandler(struct QTask_s *ptQTask)
{
  Level_DeinitLevelExpression((struct LevelExpression_s *)&ptQTask[1].tQTaskRefList.ptMiddle);
}

// source: j/0/objects/minefield.c:279  [size]
void __cdecl MineField_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = MineField_ptParameterList;
}

// source: j/0/objects/minefield.c:295  [size]
void __cdecl MineField_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  Level_CompileLevelExpression((struct LevelExpression_s *)&ptQTask[1].tQTaskRefList.ptMiddle, ptQTask);
}

// source: j/0/objects/minefield.c:326  [size]
void __cdecl MineField_GetSerializeParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = MineField_ptSerializeParameterList;
}

// source: j/0/objects/minefield.c:346  [anchor-hash]
void __cdecl MineField_Open()
{
  unsigned __int16 v0; // si
  struct ParameterList_s *v1; // eax
  struct ParameterList_s *v2; // eax
  int v3; // edx

  v0 = QTask_NewQTaskType("MineField", 216, EditorRigidObj_eQTaskType, 0, 0);
  MineField_eQTaskType = v0;
  QTask_LinkQTaskEventHandlerFn(
    v0,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveHandler);
  QTask_LinkQTaskEventHandlerFn(v0, 0, MineField_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 1, MineField_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 2, MineField_DeleteHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))MineField_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(v0, ParameterList_eUpdateInternalDataQTaskEvent, MineField_UpdateInternalDataHandler);
  v1 = (struct ParameterList_s *)Mem_AllocFn(252, 4);
  v1->nParameters = 0;
  v1->nMaxParameters = 12;
  v1->ptParameterListItem = (struct ParameterListItem_s *)&v1[1];
  MineField_ptParameterList = v1;
  dword_79EE518 = 0;
  dword_79EE51C = 0;
  dword_79EE520 = 0;
  dword_79EE524 = 1079574528;
  dword_79EE528 = 0;
  dword_79EE52C = 0;
  dword_79EE530 = 0;
  dword_79EE534 = 1079574528;
  dword_79EE540 = 0;
  dword_79EE544 = 0;
  dword_79EE548 = 0;
  dword_79EE54C = 1076101120;
  dword_79EE560 = 0;
  dword_79EE564 = 0;
  dword_79EE568 = 0;
  dword_79EE56C = 1078853632;
  dword_79EE4F0 = 0;
  dword_79EE4F4 = -1074790400;
  dword_79EE4F8 = 0;
  dword_79EE4FC = 1086556160;
  dword_79EE550 = 0;
  dword_79EE554 = 0;
  dword_79EE558 = 0;
  dword_79EE55C = 1083129856;
  dword_79EE570 = 0;
  dword_79EE574 = 0;
  dword_79EE578 = 0;
  dword_79EE57C = 1079574528;
  dword_79EE508 = 0;
  dword_79EE50C = -1074790400;
  dword_79EE510 = 0;
  dword_79EE514 = 1085276160;
  ParameterList_AddParameter(v1, 0x28u, Level_eParameterTypeObjectPos, "Position", 7u, nullptr);
  ParameterList_AddParameter(MineField_ptParameterList, 0x40u, Level_eParameterTypeVarString, "Explode", 7u, nullptr);
  ParameterList_AddParameter(
    MineField_ptParameterList,
    0x90u,
    Level_eParameterTypeReal32,
    "Explosion radius (meter)",
    7u,
    &dword_79EE518);
  ParameterList_AddParameter(
    MineField_ptParameterList,
    0x94u,
    Level_eParameterTypeReal32,
    "Explosion falloff radius (meter)",
    7u,
    &dword_79EE528);
  ParameterList_AddParameter(
    MineField_ptParameterList,
    0x98u,
    Level_eParameterTypeReal32,
    "Explosion damage scale",
    7u,
    &dword_79EE540);
  ParameterList_AddParameter(
    MineField_ptParameterList,
    0x9Cu,
    Level_eParameterTypeReal32,
    "Explosion delay (seconds)",
    7u,
    &dword_79EE560);
  ParameterList_AddParameter(
    MineField_ptParameterList,
    0xA0u,
    Level_eParameterTypeInt32,
    "Explosion fragments",
    7u,
    &dword_79EE550);
  ParameterList_AddParameter(
    MineField_ptParameterList,
    0xA4u,
    Level_eParameterTypeInt32,
    "Explosion fireballs",
    7u,
    &dword_79EE570);
  ParameterList_AddParameter(
    MineField_ptParameterList,
    0xA8u,
    Level_eParameterTypeString16,
    "Explosion sound",
    7u,
    nullptr);
  ParameterList_AddParameter(
    MineField_ptParameterList,
    0xC8u,
    Level_eParameterTypeInt32,
    "Explode close to task ID",
    7u,
    &dword_79EE508);
  ParameterList_AddParameter(
    MineField_ptParameterList,
    0xCCu,
    Level_eParameterTypeReal32,
    "Explosion delay between explosions (seconds) -1: explode once",
    7u,
    &dword_79EE4F0);
  ParameterList_AddParameter(
    MineField_ptParameterList,
    0xD0u,
    Level_eParameterTypebool8,
    "Snap explosion to ground",
    7u,
    nullptr);
  QTask_LinkQTaskEventHandlerFn(
    MineField_eQTaskType,
    Serialize_eGetSerializeParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))MineField_GetSerializeParameterListHandler);
  v2 = (struct ParameterList_s *)Mem_AllocFn(32, 4);
  v3 = Level_eParameterTypeInt32;
  v2->ptParameterListItem = (struct ParameterListItem_s *)&v2[1];
  v2->nParameters = 0;
  v2->nMaxParameters = 1;
  MineField_ptSerializeParameterList = v2;
  ParameterList_AddParameter(v2, 0xD4u, v3, "nDelayBetweenExplosions", 7u, nullptr);
}

// source: j/0/objects/minefield.c:422  [size]
void __cdecl MineField_Close()
{
  int v0; // esi
  int v1; // esi

  if ( MineField_ptParameterList )
  {
    v0 = *(_DWORD *)((unsigned int)&MineField_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
  if ( MineField_ptSerializeParameterList )
  {
    v1 = *(_DWORD *)((unsigned int)&MineField_ptSerializeParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v1);
    memset(*(void **)(v1 + 8), 0xCDu, *(_DWORD *)(v1 + 16));
    free((void *)v1);
  }
  QTask_DeleteQTaskType(MineField_eQTaskType);
}

// source: j/0/objects/minefield.c:440  [size]
unsigned __int16 __cdecl MineField_GetQTaskType()
{
  return MineField_eQTaskType;
}
