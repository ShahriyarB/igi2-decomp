/* j/0/objects/spawnarea.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/objects/spawnarea.c:115  [anchor-mhash]
void __cdecl SpawnArea_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *v2; // ecx
  struct QReference_s *v3; // eax

  ptQTask[4].tQTaskChildren.ptTail = (struct QTask_s *)1065353216;
  ptQTask[4].ptParent = (struct QTask_s *)1065353216;
  ptQTask[5].tQTaskChildren.ptHead = (struct QTask_s *)1065353216;
  v2 = (struct QTask_s *)NetManager_iSpawnAreaID++;
  ptQTask[2].ptParent = nullptr;
  *(_DWORD *)&ptQTask[2].eQTaskType = 0;
  ptQTask[3].ptNext = nullptr;
  ptQTask[3].ptPrev = nullptr;
  ptQTask[3].tQTaskChildren.ptHead = nullptr;
  ptQTask[3].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[4].tQTaskRefList.ptHead = nullptr;
  ptQTask[4].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[4].tQTaskRefList.ptTail = nullptr;
  *(_DWORD *)&ptQTask[4].eQTaskType = 0;
  ptQTask[5].ptNext = nullptr;
  ptQTask[5].ptPrev = nullptr;
  ptQTask[5].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[6].tQTaskChildren.ptHead = (struct QTask_s *)-1;
  ptQTask[6].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[6].tQTaskChildren.ptTail = (struct QTask_s *)1;
  ptQTask[6].ptNext = v2;
  v3 = (struct QReference_s *)Mem_AllocFn(12, 4);
  if ( !v3 )
  {
    LDebug_Error((char *)&g_zMessage.anDR[15]);
    abort();
  }
  ptQTask[6].tQTaskRefList.ptHead = v3;
  v3->ptPrev = nullptr;
  v3->ptNext = nullptr;
  v3->pxObject = ptQTask;
  List_AddTail(v3, (int)&SpawnArea_tSpawnAreaList);
  if ( !SpawnArea_ptActive )
    SpawnArea_ptActive = ptQTask;
  ptQTask[5].tQTaskRefList.ptTail = (struct QReference_s *)1166016512;
  ptQTask[5].ptParent = (struct QTask_s *)1166016512;
  *(_DWORD *)&ptQTask[5].eQTaskType = 1166016512;
}

// source: j/0/objects/spawnarea.c:248  [anchor-mhash]
void __cdecl SpawnArea_DeleteHandler(struct QTask_s *ptQTask)
{
  struct QReference_s *ptHead; // eax
  int v2; // esi
  struct QTask_s *v3; // eax

  Node_Remove(ptQTask[6].tQTaskRefList.ptHead);
  ptHead = ptQTask[6].tQTaskRefList.ptHead;
  if ( ptHead )
  {
    v2 = *(_DWORD *)((unsigned int)&ptHead[-1].pxObject & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v2);
    memset(*(void **)(v2 + 8), 0xCDu, *(_DWORD *)(v2 + 16));
    free((void *)v2);
  }
  v3 = SpawnArea_ptActive;
  ptQTask[6].tQTaskRefList.ptHead = nullptr;
  if ( v3 == ptQTask )
    SpawnArea_ptActive = nullptr;
}

// source: j/0/objects/spawnarea.c:282  [size]
void __cdecl SpawnArea_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = SpawnArea_ptParameterList;
}

// source: j/0/objects/spawnarea.c:298  [anchor-mhash]
void __cdecl SpawnArea_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { float v17; };
    struct { char igi2_o1[4]; struct real64x3_t tCorner; };
    struct { char igi2_o2[28]; struct real64x3_t tMin; };
    struct { char igi2_o3[56]; struct QReference_s *v20; };
    struct { char igi2_o4[60]; float v21; };
    struct { char igi2_o5[64]; struct QTask_s *ptPrev; };
    struct { char igi2_o6[68]; struct QReference_s *ptMiddle; };
    struct { char igi2_o7[72]; struct QReference_s *v24; };
    struct { char igi2_o8[76]; struct real64x3_t tMax; };
    struct { char igi2_o9[104]; float v26; };
    struct { char igi2_o10[108]; float v27; };
    struct { char igi2_o11[112]; float v28; };
    struct { char igi2_o12[116]; struct QTask_s *ptParent; };
    struct { char igi2_o13[120]; float v30; };
    struct { char igi2_o14[124]; struct QTask_s *v31; };
    struct { char igi2_o15[128]; float v32; };
    struct { char igi2_o16[132]; double v33; };
    struct { char igi2_o17[140]; double v34; };
    struct { char igi2_o18[148]; double v35; };
    struct { char igi2_o19[156]; struct real64x3_t Real64x3_Rotate_tTemp; };
    char igi2_extent[180];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  double vZ; // st7
  struct QTask_s *ptHead; // eax
  int v4; // eax
  int v5; // eax
  struct QReference_s *v6; // ecx
  double v7; // st6
  struct QTask_s *ptTail; // ecx
  double v9; // st5
  struct QTask_s *ptNext; // ecx
  double v11; // st4
  struct QReference_s *v12; // ecx
  int v13; // ebx
  double v14; // st6
  double v15; // st6
  double v16; // st5

  vZ = -1.7976931348623157e+308;
  ptHead = ptQTask[6].tQTaskChildren.ptHead;
  igi2_frame.tMax.vZ = -1.7976931348623157e+308;
  igi2_frame.tMin.vX = 1.7976931348623157e+308;
  igi2_frame.tMin.vY = 1.7976931348623157e+308;
  igi2_frame.tMin.vZ = 1.7976931348623157e+308;
  igi2_frame.tMax.vX = -1.7976931348623157e+308;
  igi2_frame.tMax.vY = -1.7976931348623157e+308;
  if ( ptHead )
  {
    v5 = SpawnArea_nBadIndex;
    ptQTask[6].ptPrev = (struct QTask_s *)SpawnArea_nBadIndex;
    SpawnArea_nBadIndex = v5 + 1;
  }
  else
  {
    v4 = SpawnArea_nGoodIndex;
    ptQTask[6].ptPrev = (struct QTask_s *)SpawnArea_nGoodIndex;
    SpawnArea_nGoodIndex = v4 + 1;
  }
  ptQTask[5].tQTaskChildren.ptTail = (struct QTask_s *)ptQTask[5].tQTaskRefList.ptTail;
  v6 = *(struct QReference_s **)&ptQTask[5].eQTaskType;
  ptQTask[5].tQTaskRefList.ptHead = (struct QReference_s *)ptQTask[5].ptParent;
  ptQTask[5].tQTaskRefList.ptMiddle = v6;
  v7 = *(float *)&ptQTask[5].tQTaskChildren.ptTail * 0.5;
  igi2_frame.ptMiddle = ptQTask[3].tQTaskRefList.ptMiddle;
  ptTail = ptQTask[3].tQTaskChildren.ptTail;
  *(float *)&ptQTask[5].tQTaskChildren.ptTail = v7;
  igi2_frame.v26 = *(float *)&ptTail;
  v9 = *(float *)&ptQTask[5].tQTaskRefList.ptHead * 0.5;
  igi2_frame.ptParent = ptQTask[3].ptParent;
  igi2_frame.v31 = ptQTask[4].tQTaskChildren.ptHead;
  ptNext = ptQTask[4].ptNext;
  *(float *)&ptQTask[5].tQTaskRefList.ptHead = v9;
  v11 = *(float *)&ptQTask[5].tQTaskRefList.ptMiddle;
  igi2_frame.v21 = *(float *)&ptNext;
  HIDWORD(igi2_frame.v33) = ptQTask[2].tQTaskChildren.ptMiddle;
  igi2_frame.v17 = v11 * 0.5;
  HIDWORD(igi2_frame.v34) = ptQTask[2].tQTaskRefList.ptHead;
  *(float *)&ptQTask[5].tQTaskRefList.ptMiddle = igi2_frame.v17;
  v12 = ptQTask[2].tQTaskRefList.ptTail;
  igi2_frame.v32 = igi2_frame.v17;
  igi2_frame.v27 = v7;
  igi2_frame.v24 = ptQTask[3].tQTaskRefList.ptHead;
  igi2_frame.v30 = v9;
  igi2_frame.v28 = *(float *)&ptQTask[3].eQTaskType;
  igi2_frame.v20 = ptQTask[3].tQTaskRefList.ptTail;
  igi2_frame.ptPrev = ptQTask[4].ptPrev;
  LODWORD(igi2_frame.v33) = ptQTask[2].tQTaskChildren.ptHead;
  LODWORD(igi2_frame.v34) = ptQTask[2].tQTaskChildren.ptTail;
  v13 = 0;
  LODWORD(igi2_frame.v35) = ptQTask[2].tQTaskRefList.ptMiddle;
  HIDWORD(igi2_frame.v35) = v12;
  do
  {
    v14 = (double)(1 - 2 * (v13 & 1)) * igi2_frame.v27;
    igi2_frame.tCorner.vY = (double)(1 - (v13 & 2)) * igi2_frame.v30;
    igi2_frame.tCorner.vZ = (double)(1 - ((v13 >> 1) & 2)) * igi2_frame.v32;
    igi2_frame.Real64x3_Rotate_tTemp.vX = *(float *)&igi2_frame.v24 * igi2_frame.tCorner.vY + *(float *)&igi2_frame.ptMiddle * igi2_frame.tCorner.vZ + igi2_frame.v26 * v14;
    igi2_frame.Real64x3_Rotate_tTemp.vY = igi2_frame.v28 * igi2_frame.tCorner.vZ + *(float *)&igi2_frame.ptParent * igi2_frame.tCorner.vY + *(float *)&igi2_frame.v20 * v14;
    igi2_frame.Real64x3_Rotate_tTemp.vZ = *(float *)&igi2_frame.v31 * igi2_frame.tCorner.vZ + igi2_frame.v21 * v14 + *(float *)&igi2_frame.ptPrev * igi2_frame.tCorner.vY;
    qmemcpy(&igi2_frame.tCorner, &igi2_frame.Real64x3_Rotate_tTemp, sizeof(igi2_frame.tCorner));
    v15 = igi2_frame.v33 + igi2_frame.Real64x3_Rotate_tTemp.vX;
    v16 = igi2_frame.v34 + igi2_frame.tCorner.vY;
    igi2_frame.tCorner.vY = igi2_frame.v34 + igi2_frame.tCorner.vY;
    igi2_frame.tCorner.vZ = igi2_frame.v35 + igi2_frame.tCorner.vZ;
    if ( igi2_frame.tMin.vX >= igi2_frame.v33 + igi2_frame.Real64x3_Rotate_tTemp.vX )
      igi2_frame.tMin.vX = v15;
    if ( igi2_frame.tMin.vY >= v16 )
      igi2_frame.tMin.vY = v16;
    if ( igi2_frame.tMin.vZ >= igi2_frame.tCorner.vZ )
      igi2_frame.tMin.vZ = igi2_frame.tCorner.vZ;
    if ( igi2_frame.tMax.vX <= v15 )
      igi2_frame.tMax.vX = v15;
    if ( igi2_frame.tMax.vY <= igi2_frame.tCorner.vY )
      igi2_frame.tMax.vY = igi2_frame.tCorner.vY;
    if ( vZ <= igi2_frame.tCorner.vZ )
      vZ = igi2_frame.tCorner.vZ;
    ++v13;
  }
  while ( v13 < 8 );
  igi2_frame.tMax.vZ = vZ;
  qmemcpy(&ptQTask[1], &igi2_frame.tMin, 0x18u);
  qmemcpy(&ptQTask[1].tQTaskRefList.ptMiddle, &igi2_frame.tMax, 0x18u);
}

// source: j/0/objects/spawnarea.c:393  [anchor-hash]
void __cdecl SpawnArea_Open()
{
  unsigned __int16 v0; // si
  struct ParameterList_s *v1; // eax
  int v2; // edx

  v0 = QTask_NewQTaskType("SpawnArea", 264, EditorRigidObj_eQTaskType, 0, 0);
  SpawnArea_eQTaskType = v0;
  QTask_LinkQTaskEventHandlerFn(
    v0,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveHandler);
  QTask_LinkQTaskEventHandlerFn(v0, 0, SpawnArea_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 2, SpawnArea_DeleteHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))SpawnArea_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(v0, ParameterList_eUpdateInternalDataQTaskEvent, SpawnArea_UpdateInternalDataHandler);
  v1 = (struct ParameterList_s *)Mem_AllocFn(132, 4);
  v1->ptParameterListItem = (struct ParameterListItem_s *)&v1[1];
  v2 = Level_eParameterTypeObjectPos;
  v1->nParameters = 0;
  v1->nMaxParameters = 6;
  SpawnArea_ptParameterList = v1;
  ParameterList_AddParameter(v1, 0x58u, v2, "Position", 7u, nullptr);
  ParameterList_AddParameter(SpawnArea_ptParameterList, 0x88u, Level_eParameterTypeReal32x9, "Orientation", 7u, nullptr);
  ParameterList_AddParameter(SpawnArea_ptParameterList, 0xE4u, Level_eParameterTypeReal32x3, "Dimentions", 7u, nullptr);
  ParameterList_AddParameter(
    SpawnArea_ptParameterList,
    0x70u,
    Level_eParameterTypeObjectPos,
    "Camera Position",
    7u,
    nullptr);
  ParameterList_AddParameter(
    SpawnArea_ptParameterList,
    0xB0u,
    Level_eParameterTypeReal32x9,
    "Camera Orientation",
    7u,
    nullptr);
  ParameterList_AddParameter(SpawnArea_ptParameterList, 0xF8u, Level_eParameterTypeInt32, "Team", 7u, nullptr);
  Symbol_Register(
    "TASKTYPE_SPAWNAREA",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)SpawnArea_eQTaskType,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  SpawnArea_tSpawnAreaList.ptHead = (struct Node_s *)&SpawnArea_tSpawnAreaList.ptMiddle;
  SpawnArea_tSpawnAreaList.ptTail = (struct Node_s *)&SpawnArea_tSpawnAreaList;
  SpawnArea_tSpawnAreaList.ptMiddle = nullptr;
}

// source: j/0/objects/spawnarea.c:437  [size]
void __cdecl SpawnArea_Close()
{
  int v0; // esi

  QTask_DeleteQTaskType(SpawnArea_eQTaskType);
  if ( SpawnArea_ptParameterList )
  {
    v0 = *(_DWORD *)((unsigned int)&SpawnArea_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
}

// source: j/0/objects/spawnarea.c:455  [size]
unsigned __int16 __cdecl SpawnArea_GetQTaskType()
{
  return SpawnArea_eQTaskType;
}

// source: j/0/objects/spawnarea.c:528  [anchor-callee]
struct DrawComputerObjectContext_s *__cdecl SpawnArea_DrawComputerObject(
        struct DrawComputerObjectContext_s *ptDrawComputerObjectContext,
        struct SpawnArea_s *ptSpawnArea)
{
  double v2; // st7
  struct real32x9_t tOrientation; // [esp+4h] [ebp-28h] BYREF

  ptDrawComputerObjectContext->ptPos = &ptSpawnArea->tPos;
  ptDrawComputerObjectContext->ptOrientation = &tOrientation;
  v2 = ptSpawnArea->tHalvedDimensions.vY + ptSpawnArea->tHalvedDimensions.vX;
  tOrientation.tX.vX = 1.0;
  memset(&tOrientation.tX.vY, 0, 12);
  ptDrawComputerObjectContext->vRadius = v2 * 0.5;
  tOrientation.tY.vY = 1.0;
  memset(&tOrientation.tY.vZ, 0, 12);
  tOrientation.tZ.vZ = 1.0;
  tOrientation.nOps = 0;
  ptDrawComputerObjectContext->eComputerObjectMarker = COMPUTEROBJECTMARKER_BOX;
  ptDrawComputerObjectContext->eComputerObjectMarkerColor = COMPUTEROBJECTMARKER_COLOR_YELLOW;
  return ComputerObject_DrawMarker(ptDrawComputerObjectContext);
}

// source: j/0/objects/spawnarea.c:563  [anchor-caller]
void __cdecl SpawnArea_DrawAllComputerObjects(
        struct DrawComputerObjectContext_s *ptDrawComputerObjectContext,
        int eTeam)
{
  struct Node_s *ptHead; // eax
  struct Node_s *i; // esi
  struct SpawnArea_s *ptNext; // eax

  ptHead = SpawnArea_tSpawnAreaList.ptHead;
  for ( i = SpawnArea_tSpawnAreaList.ptHead->ptNext; i; i = i->ptNext )
  {
    ptNext = (struct SpawnArea_s *)ptHead[1].ptNext;
    if ( ptNext->eTeam == eTeam || eTeam == -1 )
      SpawnArea_DrawComputerObject(ptDrawComputerObjectContext, ptNext);
    ptHead = i;
  }
}

// source: j/0/objects/spawnarea.c:598  [anchor-callee]
void __cdecl SpawnArea_DrawAllActiveComputerObjects(
        struct DrawComputerObjectContext_s *ptDrawComputerObjectContext,
        int eTeam)
{
  unsigned __int16 v2; // bx
  int v3; // esi
  unsigned __int16 v4; // di
  struct QTask_s *FirstChildOfType; // eax
  int v6; // edx
  struct SpawnArea_s *NextSiblingOfType; // esi
  int nObjective; // [esp+4h] [ebp-4h]

  if ( SpawnArea_ptActive )
  {
    v2 = NetObjective_eQTaskType;
    v3 = 1;
    v4 = SpawnArea_eQTaskType;
    nObjective = 1;
    do
    {
      FirstChildOfType = QTask_GetFirstChildOfType(&NetMission_ptNetMission->tQTask, v2);
      if ( FirstChildOfType )
      {
        while ( FirstChildOfType[5].ptNext != (struct QTask_s *)v3 )
        {
          FirstChildOfType = QTask_GetNextSiblingOfType(FirstChildOfType, v2);
          if ( !FirstChildOfType )
            goto LABEL_15;
        }
        v6 = eTeam;
        NextSiblingOfType = (struct SpawnArea_s *)QTask_GetFirstChildOfType(FirstChildOfType, v4);
        if ( (NetMission_eDefendingTeam == eTeam || NetMission_eCurrentObjective >= nObjective) && NextSiblingOfType )
        {
          do
          {
            if ( NextSiblingOfType->eTeam == v6 || v6 == -1 )
            {
              SpawnArea_DrawComputerObject(ptDrawComputerObjectContext, NextSiblingOfType);
              v2 = NetObjective_eQTaskType;
              v4 = SpawnArea_eQTaskType;
              v6 = eTeam;
            }
            NextSiblingOfType = (struct SpawnArea_s *)QTask_GetNextSiblingOfType(
                                                        &NextSiblingOfType->tEditorRigidObj.tQTask,
                                                        v4);
          }
          while ( NextSiblingOfType );
        }
        v3 = nObjective;
      }
LABEL_15:
      nObjective = ++v3;
    }
    while ( v3 <= 3 );
  }
}

// source: j/0/objects/spawnarea.c:657  [anchor-callee]
enum bool __cdecl SpawnArea_isInsideAnyActiveSpawnAreaForTeam(int eTeam, struct real64x3_t *ptPos)
{
  unsigned __int16 v3; // bx
  unsigned __int16 v4; // di
  int v5; // ebp
  struct QTask_s *FirstChildOfType; // eax
  struct QTask_s *v7; // eax
  struct QTask_s *NextSiblingOfType; // edx

  if ( !SpawnArea_ptActive )
    return false;
  v3 = NetObjective_eQTaskType;
  v4 = SpawnArea_eQTaskType;
  v5 = 1;
  while ( 1 )
  {
    FirstChildOfType = QTask_GetFirstChildOfType(&NetMission_ptNetMission->tQTask, v3);
    if ( FirstChildOfType )
    {
      while ( FirstChildOfType[5].ptNext != (struct QTask_s *)v5 )
      {
        FirstChildOfType = QTask_GetNextSiblingOfType(FirstChildOfType, v3);
        if ( !FirstChildOfType )
          goto LABEL_15;
      }
      v7 = QTask_GetFirstChildOfType(FirstChildOfType, v4);
      NextSiblingOfType = v7;
      if ( NetMission_eDefendingTeam == eTeam || NetMission_eCurrentObjective >= v5 )
      {
        if ( v7 )
          break;
      }
    }
LABEL_15:
    if ( ++v5 > 3 )
      return false;
  }
  while ( NextSiblingOfType[6].tQTaskChildren.ptHead != (struct QTask_s *)eTeam && eTeam != -1
       || SpawnArea_IsInsideArea(NextSiblingOfType, ptPos) == false )
  {
    NextSiblingOfType = QTask_GetNextSiblingOfType(NextSiblingOfType, v4);
    if ( !NextSiblingOfType )
      goto LABEL_15;
  }
  return true;
}

// source: j/0/objects/spawnarea.c:731  [anchor-caller]
enum bool __cdecl SpawnArea_isInsideAnySpawnAreaForTeam(int eTeam, struct real64x3_t *ptPos)
{
  struct Node_s *ptHead; // eax
  struct Node_s *ptNext; // edx
  struct QTask_s *v4; // ecx

  ptHead = SpawnArea_tSpawnAreaList.ptHead;
  ptNext = SpawnArea_tSpawnAreaList.ptHead->ptNext;
  if ( !SpawnArea_tSpawnAreaList.ptHead->ptNext )
    return false;
  while ( 1 )
  {
    v4 = (struct QTask_s *)ptHead[1].ptNext;
    if ( v4[6].tQTaskChildren.ptHead == (struct QTask_s *)eTeam || eTeam == -1 )
    {
      if ( SpawnArea_IsInsideArea(v4, ptPos) )
        break;
    }
    ptHead = ptNext;
    ptNext = ptNext->ptNext;
    if ( !ptNext )
      return false;
  }
  return true;
}

// source: j/0/objects/spawnarea.c:769  [size]
struct QTask_s *__cdecl SpawnArea_GetSpawnAreaFromID(int iID)
{
  struct Node_s *ptHead; // eax
  struct Node_s *ptNext; // ecx
  struct QTask_s *result; // eax

  ptHead = SpawnArea_tSpawnAreaList.ptHead;
  ptNext = SpawnArea_tSpawnAreaList.ptHead->ptNext;
  if ( !SpawnArea_tSpawnAreaList.ptHead->ptNext )
    return nullptr;
  while ( 1 )
  {
    result = (struct QTask_s *)ptHead[1].ptNext;
    if ( result[6].ptNext == (struct QTask_s *)iID )
      break;
    ptHead = ptNext;
    ptNext = ptNext->ptNext;
    if ( !ptNext )
      return nullptr;
  }
  return result;
}

// source: j/0/objects/spawnarea.c:804  [size]
int __cdecl SpawnArea_GetID(struct QTask_s *ptSpawnAreaQTask)
{
  return (int)ptSpawnAreaQTask[6].ptNext;
}

// source: j/0/objects/spawnarea.c:822  [size]
struct QTask_s *__cdecl SpawnArea_SetActiveAreaTask(struct QTask_s *ptSpawnAreaQTask)
{
  SpawnArea_ptActive = ptSpawnAreaQTask;
  return ptSpawnAreaQTask;
}

// source: j/0/objects/spawnarea.c:835  [size]
struct QTask_s *__cdecl SpawnArea_GetActiveAreaTask()
{
  return SpawnArea_ptActive;
}

// source: j/0/objects/spawnarea.c:848  [size]
int __cdecl SpawnArea_GetTeam(struct QTask_s *ptSpawnAreaQTask)
{
  return (int)ptSpawnAreaQTask[6].tQTaskChildren.ptHead;
}

// source: j/0/objects/spawnarea.c:864  [size]
struct real64x3_t *__cdecl SpawnArea_GetPos(struct QTask_s *ptSpawnAreaQTask)
{
  return (struct real64x3_t *)&ptSpawnAreaQTask[2].tQTaskChildren;
}

// source: j/0/objects/spawnarea.c:880  [size]
struct real64x3_t *__cdecl SpawnArea_GetCameraPosition(struct QTask_s *ptSpawnAreaQTask)
{
  return (struct real64x3_t *)&ptSpawnAreaQTask[2].ptParent;
}

// source: j/0/objects/spawnarea.c:896  [size]
struct real32x9_t *__cdecl SpawnArea_GetCameraOrientation(
        struct QTask_s *ptSpawnAreaQTask)
{
  return (struct real32x9_t *)&ptSpawnAreaQTask[4].tQTaskChildren.ptTail;
}

// source: j/0/objects/spawnarea.c:913  [anchor-callee]
enum bool __cdecl SpawnArea_IsInsideArea(
        struct QTask_s *ptQTask,
        struct real64x3_t *ptPos)
{
  double v2; // st7
  double v3; // st6
  double v4; // st5
  float Real32x3_RotateInverse_tTemp; // [esp+0h] [ebp-Ch]
  float Real32x3_RotateInverse_tTemp_4; // [esp+4h] [ebp-8h]
  float Real32x3_RotateInverse_tTemp_8; // [esp+8h] [ebp-4h]

  v2 = ptPos->vX - *(double *)&ptQTask[2].tQTaskChildren.ptHead;
  v3 = ptPos->vY - *(double *)&ptQTask[2].tQTaskChildren.ptTail;
  v4 = ptPos->vZ - *(double *)&ptQTask[2].tQTaskRefList.ptMiddle;
  Real32x3_RotateInverse_tTemp = v4 * *(float *)&ptQTask[4].ptNext
                               + v3 * *(float *)&ptQTask[3].tQTaskRefList.ptTail
                               + v2 * *(float *)&ptQTask[3].tQTaskChildren.ptTail;
  Real32x3_RotateInverse_tTemp_4 = v4 * *(float *)&ptQTask[4].ptPrev
                                 + v3 * *(float *)&ptQTask[3].ptParent
                                 + v2 * *(float *)&ptQTask[3].tQTaskRefList.ptHead;
  Real32x3_RotateInverse_tTemp_8 = v4 * *(float *)&ptQTask[4].tQTaskChildren.ptHead
                                 + v3 * *(float *)&ptQTask[3].eQTaskType
                                 + v2 * *(float *)&ptQTask[3].tQTaskRefList.ptMiddle;
  return Real32x3_RotateInverse_tTemp <= (double)*(float *)&ptQTask[5].tQTaskChildren.ptTail
      && Real32x3_RotateInverse_tTemp_4 <= (double)*(float *)&ptQTask[5].tQTaskRefList.ptHead
      && Real32x3_RotateInverse_tTemp_8 <= (double)*(float *)&ptQTask[5].tQTaskRefList.ptMiddle
      && -*(float *)&ptQTask[5].tQTaskChildren.ptTail <= Real32x3_RotateInverse_tTemp
      && -*(float *)&ptQTask[5].tQTaskRefList.ptHead <= Real32x3_RotateInverse_tTemp_4
      && -*(float *)&ptQTask[5].tQTaskRefList.ptMiddle <= Real32x3_RotateInverse_tTemp_8;
}

// source: j/0/objects/spawnarea.c:965  [anchor-hash]
void __cdecl SpawnArea_ResetIndexes()
{
  SpawnArea_nGoodIndex = 1;
  SpawnArea_nBadIndex = 1;
}

// source: j/0/objects/spawnarea.c:979  [anchor-hash]
int __cdecl SpawnArea_GetActiveAreaIndex()
{
  return (int)SpawnArea_ptActive[6].ptPrev;
}
