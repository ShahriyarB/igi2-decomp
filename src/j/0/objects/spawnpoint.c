/* j/0/objects/spawnpoint.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/objects/spawnpoint.c:95  [anchor-mhash]
void __cdecl SpawnPoint_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *v2; // ecx
  struct QTask_s *v3; // eax

  v2 = (struct QTask_s *)NetManager_iSpawnPointID++;
  ptQTask[1].tQTaskChildren.ptHead = nullptr;
  ptQTask[1].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[1].tQTaskChildren.ptTail = nullptr;
  ptQTask[1].tQTaskRefList.ptHead = nullptr;
  ptQTask[1].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[1].tQTaskRefList.ptTail = nullptr;
  ptQTask[1].ptParent = nullptr;
  *(_DWORD *)&ptQTask[1].eQTaskType = 0;
  ptQTask[1].ptNext = v2;
  v3 = (struct QTask_s *)Mem_AllocFn(12, 4);
  if ( !v3 )
  {
    LDebug_Error((char *)&g_zMessage.anDR[15]);
    abort();
  }
  ptQTask[2].ptNext = v3;
  v3->ptPrev = nullptr;
  v3->ptNext = nullptr;
  v3->tQTaskChildren.ptHead = ptQTask;
  List_AddTail(v3, (int)&SpawnPoint_tSpawnPointList);
}

// source: j/0/objects/spawnpoint.c:183  [anchor-mhash]
void __cdecl SpawnPoint_DeleteHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptNext; // eax
  int v2; // esi

  Node_Remove(ptQTask[2].ptNext);
  ptNext = ptQTask[2].ptNext;
  if ( ptNext )
  {
    v2 = *(_DWORD *)((unsigned int)&ptNext[-1].eQTaskType & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v2);
    memset(*(void **)(v2 + 8), 0xCDu, *(_DWORD *)(v2 + 16));
    free((void *)v2);
  }
  ptQTask[2].ptNext = nullptr;
}

// source: j/0/objects/spawnpoint.c:218  [size]
void __cdecl SpawnPoint_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = SpawnPoint_ptParameterList;
}

// source: j/0/objects/spawnpoint.c:234  [anchor-caller]
void __cdecl SpawnPoint_PointTowardsObjective(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { float vGamma; };
    struct { char igi2_o1[4]; float vAlpha; };
    struct { char igi2_o2[8]; struct real64x3_t tSecPos; };
    struct { char igi2_o3[32]; struct real64x3_t tPriPos; };
    char igi2_extent[56];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *ptParent; // ecx
  struct Game_s *v2; // eax
  unsigned int v3; // esi
  int v4; // esi
  unsigned int v5; // esi
  int v6; // esi
  int EnumObjectivePos; // eax
  long double v8; // st7

  ptParent = ptQTask->ptParent->ptParent;
  v2 = Game_ptGame;
  v3 = (Game_ptGame->tRunRandomState.anRandom[0] >> 7) ^ Game_ptGame->tRunRandomState.anRandom[2];
  Game_ptGame->tRunRandomState.anRandom[2] = v3;
  v4 = v3 ^ v2->tRunRandomState.anRandom[1];
  v2->tRunRandomState.anRandom[1] = v4;
  v5 = v4 + v2->tRunRandomState.anRandom[0];
  v2->tRunRandomState.anRandom[0] = v5;
  v6 = v5 & 1;
  EnumObjectivePos = ComputerHilight_GetEnumObjectivePos(&igi2_frame.tPriPos, &igi2_frame.tSecPos, (int)ptParent[5].ptNext);
  if ( EnumObjectivePos == 1 || v6 )
  {
    *(float *)&igi2_frame.tSecPos.vX = igi2_frame.tPriPos.vX - *(double *)&ptQTask[1].tQTaskChildren.ptHead;
    *((float *)&igi2_frame.tSecPos.vX + 1) = igi2_frame.tPriPos.vY - *(double *)&ptQTask[1].tQTaskChildren.ptTail;
    *(float *)&igi2_frame.tSecPos.vY = igi2_frame.tPriPos.vZ - *(double *)&ptQTask[1].tQTaskRefList.ptMiddle;
  }
  if ( EnumObjectivePos == 2 && !v6 )
  {
    *(float *)&igi2_frame.tSecPos.vX = igi2_frame.tPriPos.vX - *(double *)&ptQTask[1].tQTaskChildren.ptHead;
    *((float *)&igi2_frame.tSecPos.vX + 1) = igi2_frame.tPriPos.vY - *(double *)&ptQTask[1].tQTaskChildren.ptTail;
    *(float *)&igi2_frame.tSecPos.vY = igi2_frame.tPriPos.vZ - *(double *)&ptQTask[1].tQTaskRefList.ptMiddle;
  }
  if ( *(float *)&igi2_frame.tSecPos.vX != 0.0 || *((float *)&igi2_frame.tSecPos.vX + 1) != 0.0 || *(float *)&igi2_frame.tSecPos.vY != 0.0 )
  {
    v8 = 1.0
       / sqrt(
           *(float *)&igi2_frame.tSecPos.vX * *(float *)&igi2_frame.tSecPos.vX
         + *((float *)&igi2_frame.tSecPos.vX + 1) * *((float *)&igi2_frame.tSecPos.vX + 1)
         + *(float *)&igi2_frame.tSecPos.vY * *(float *)&igi2_frame.tSecPos.vY);
    *(float *)&igi2_frame.tSecPos.vX = *(float *)&igi2_frame.tSecPos.vX * v8;
    *((float *)&igi2_frame.tSecPos.vX + 1) = *((float *)&igi2_frame.tSecPos.vX + 1) * v8;
    *(float *)&igi2_frame.tSecPos.vY = *(float *)&igi2_frame.tSecPos.vY * v8;
  }
  Real32x3_GetAngles((struct real32x3_t *)&igi2_frame.tSecPos, &igi2_frame.vAlpha, &igi2_frame.vGamma);
  *(float *)&ptQTask[1].ptParent = igi2_frame.vGamma - 1.5707963705062866;
}

// source: j/0/objects/spawnpoint.c:285  [size]
void __cdecl SpawnPoint_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  SpawnPoint_PointTowardsObjective(ptQTask);
}

// source: j/0/objects/spawnpoint.c:348  [size]
void __cdecl SpawnPoint_UpdateAttachmentHandler(struct QTask_s *ptQTask)
{
  ;
}

// source: j/0/objects/spawnpoint.c:434  [anchor-strings]
void __cdecl SpawnPoint_Open()
{
  unsigned __int16 BaseQTaskType; // ax
  unsigned __int16 v1; // si
  struct ParameterList_s *v2; // eax
  int v3; // edx

  BaseQTaskType = QTask_GetBaseQTaskType();
  v1 = QTask_NewQTaskType((char *)&g_zMessage.anDR[12], 88, BaseQTaskType, 0, 0);
  SpawnPoint_eQTaskType = v1;
  QTask_LinkQTaskEventHandlerFn(
    v1,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveHandler);
  QTask_LinkQTaskEventHandlerFn(v1, 0, SpawnPoint_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 2, SpawnPoint_DeleteHandler);
  QTask_LinkQTaskEventHandlerFn(
    v1,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))SpawnPoint_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(v1, ParameterList_eUpdateInternalDataQTaskEvent, SpawnPoint_UpdateInternalDataHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(
    v1,
    Attach_eUpdateAttachmentEvent,
    (void (__cdecl *)(struct QTask_s *))SpawnPoint_UpdateAttachmentHandler);
  v2 = (struct ParameterList_s *)Mem_AllocFn(72, 4);
  v3 = Level_eParameterTypeObjectPos;
  v2->ptParameterListItem = (struct ParameterListItem_s *)&v2[1];
  v2->nParameters = 0;
  v2->nMaxParameters = 3;
  SpawnPoint_ptParameterList = v2;
  ParameterList_AddParameter(v2, 0x30u, v3, "Position", 7u, nullptr);
  ParameterList_AddParameter(SpawnPoint_ptParameterList, 0x48u, Level_eParameterTypeAngle, "Gamma", 7u, nullptr);
  Symbol_Register(
    (char *)&g_zMessage.anDR[7],
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)SpawnPoint_eQTaskType,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  SpawnPoint_tSpawnPointList.ptHead = (struct Node_s *)&SpawnPoint_tSpawnPointList.ptMiddle;
  SpawnPoint_tSpawnPointList.ptTail = (struct Node_s *)&SpawnPoint_tSpawnPointList;
  SpawnPoint_tSpawnPointList.ptMiddle = nullptr;
}

// source: j/0/objects/spawnpoint.c:485  [size]
void __cdecl SpawnPoint_Close()
{
  int v0; // esi

  QTask_DeleteQTaskType(SpawnPoint_eQTaskType);
  if ( SpawnPoint_ptParameterList )
  {
    v0 = *(_DWORD *)((unsigned int)&SpawnPoint_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
}

// source: j/0/objects/spawnpoint.c:503  [size]
unsigned __int16 __cdecl SpawnPoint_GetQTaskType()
{
  return SpawnPoint_eQTaskType;
}

// source: j/0/objects/spawnpoint.c:521  [size]
struct QTask_s *__cdecl SpawnPoint_GetSpawnPoint(
        struct QTask_s *ptSpawnAreaQTask,
        int eSearchMethod)
{
  struct QTask_s *v2; // esi
  unsigned __int16 v3; // dx
  struct QTask_s *FirstChildOfType; // eax
  struct QTask_s *i; // eax

  v2 = nullptr;
  if ( ptSpawnAreaQTask )
  {
    v3 = SpawnPoint_eQTaskType;
    FirstChildOfType = QTask_GetFirstChildOfType(ptSpawnAreaQTask, SpawnPoint_eQTaskType);
    for ( i = QTask_GetNextSiblingOfType(FirstChildOfType, v3); i; i = QTask_GetNextSiblingOfType(i, v3) )
    {
      if ( !eSearchMethod && (!v2 || (int)(*(_DWORD *)&i[1].eQTaskType) < (int)(*(_DWORD *)&v2[1].eQTaskType)) )
        v2 = i;
    }
    return v2;
  }
  return ptSpawnAreaQTask;
}

// source: j/0/objects/spawnpoint.c:571  [size]
struct QTask_s *__cdecl SpawnPoint_GetSpawnPointFromID(int iID)
{
  struct Node_s *ptHead; // eax
  struct Node_s *ptNext; // ecx
  struct QTask_s *result; // eax

  ptHead = SpawnPoint_tSpawnPointList.ptHead;
  ptNext = SpawnPoint_tSpawnPointList.ptHead->ptNext;
  if ( !SpawnPoint_tSpawnPointList.ptHead->ptNext )
    return nullptr;
  while ( 1 )
  {
    result = (struct QTask_s *)ptHead[1].ptNext;
    if ( result[1].ptNext == (struct QTask_s *)iID )
      break;
    ptHead = ptNext;
    ptNext = ptNext->ptNext;
    if ( !ptNext )
      return nullptr;
  }
  return result;
}

// source: j/0/objects/spawnpoint.c:606  [anchor-callee]
struct QTask_s *__cdecl SpawnPoint_GetPositionAndOrientation(
        struct real64x3_t *ptPos,
        float *pvGamma,
        struct QTask_s *ptSpawnPointQTask)
{
  if ( ptPos )
    qmemcpy(ptPos, &ptSpawnPointQTask[1].tQTaskChildren, sizeof(struct real64x3_t));
  if ( pvGamma )
  {
    ptSpawnPointQTask = ptSpawnPointQTask[1].ptParent;
    *(_DWORD *)pvGamma = ptSpawnPointQTask;
  }
  return ptSpawnPointQTask;
}

// source: j/0/objects/spawnpoint.c:632  [size]
int __cdecl SpawnPoint_GetID(struct QTask_s *ptSpawnPointQTask)
{
  return (int)ptSpawnPointQTask[1].ptNext;
}

// source: j/0/objects/spawnpoint.c:650  [size]
void __cdecl SpawnPoint_Use(struct QTask_s *ptSpawnPointQTask)
{
  int v1; // eax

  v1 = SpawnPoint_nUse;
  *(_DWORD *)&ptSpawnPointQTask[1].eQTaskType = SpawnPoint_nUse;
  SpawnPoint_nUse = v1 + 1;
}
