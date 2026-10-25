/* j/0/weapons/mine.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/weapons/mine.c:75  [size]
void __cdecl Mine_GetGameItemDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *((_WORD *)pxContext + 1) = 40;
  *(_WORD *)pxContext = ptQTask[16].tQTaskChildren.ptHead;
  *((_WORD *)pxContext + 2) = Mine_eQTaskType;
  qmemcpy((char *)pxContext + 6, &ptQTask[8], 0x18u);
  *(_DWORD *)((char *)pxContext + 30) = ptQTask[8].tQTaskRefList.ptTail;
  *(_DWORD *)((char *)pxContext + 34) = ptQTask[9].ptNext;
  *(_DWORD *)((char *)pxContext + 38) = ptQTask[9].tQTaskChildren.ptMiddle;
}

// source: j/0/weapons/mine.c:104  [size]
void __cdecl Mine_GetSerializeInfoHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = 1;
  *((_DWORD *)pxContext + 1) = 1;
}

// source: j/0/weapons/mine.c:123  [size]
void __cdecl Mine_GetSerializeParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = Mine_ptSerializeParameterList;
}

// source: j/0/weapons/mine.c:142  [anchor-mhash]
void __cdecl Mine_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  bool v2; // zf

  QTaskList_Register(GameFunctions_ptNotifyQTaskList, (struct QTaskList_s *)ptQTask);
  QTaskList_Register(Mine_ptMineQTaskList, (struct QTaskList_s *)ptQTask);
  QTaskList_Register(GameFunctions_ptCutsceneDeleteQTaskList, (struct QTaskList_s *)ptQTask);
  ((void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[0][ExplodeObject_eQTaskType].pfHandler)(
    ptQTask,
    pxContext);
  ExplodeObject_SetParameters(ptQTask, 1.0, 2.0, 0.0, 1.0, 0.0, 5, 1, "explo_proxy");
  sprintf((char *const)&ptQTask[9].tQTaskRefList.ptMiddle, "136_01_1");
  v2 = Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER;
  ptQTask[15].tQTaskRefList.ptTail = nullptr;
  ptQTask[15].ptParent = nullptr;
  *(_DWORD *)&ptQTask[15].eQTaskType = 1061158912;
  ptQTask[16].ptNext = (struct QTask_s *)1077936128;
  LOBYTE(ptQTask[16].ptPrev) = 0;
  BYTE1(ptQTask[16].ptPrev) = 0;
  ptQTask[15].tQTaskRefList.ptMiddle = nullptr;
  if ( v2 )
  {
    LOWORD(ptQTask[16].tQTaskChildren.ptHead) = NetworkGameItem_RegisterGameItem(ptQTask, 0x28u, Mine_iGameItemID);
    Mine_iGameItemID = 0;
  }
}

// source: j/0/weapons/mine.c:215  [anchor-strings]
void __cdecl Mine_RunHandler(struct QTask_s *ptQTask)
{
  struct QReference_s *ptTail; // eax
  struct QTask_s *v2; // eax
  struct QTask_s *ptParent; // eax

  ((void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[1][ExplodeObject_eQTaskType].pfHandler)(ptQTask);
  ptTail = ptQTask[15].tQTaskRefList.ptTail;
  if ( ptTail )
  {
    ptQTask[15].tQTaskRefList.ptTail = (struct QReference_s *)((char *)ptTail - 1);
  }
  else if ( ((int)ptQTask[15].tQTaskRefList.ptMiddle & 1) == 0 )
  {
    if ( !BYTE1(ptQTask[16].ptPrev) )
    {
      v2 = SoundSys_NewSoundFn(Level_ptDynamicQTask, "proxy_arm");
      if ( v2 )
        SoundSys_SetSoundPosition(v2, (struct real64x3_t *)&ptQTask[1]);
    }
    BYTE1(ptQTask[16].ptPrev) = 1;
  }
  if ( LOBYTE(ptQTask[16].ptPrev) )
  {
    ptParent = ptQTask[15].ptParent;
    if ( ptParent )
      ptQTask[15].ptParent = (struct QTask_s *)((char *)ptParent - 1);
    else
      LOBYTE(ptQTask[13].tQTaskRefList.ptHead) = 1;
  }
  if ( LOBYTE(ptQTask[11].tQTaskChildren.ptTail) )
    QTask_Delete(ptQTask);
  ptQTask[15].tQTaskRefList.ptMiddle = (struct QReference_s *)((int)ptQTask[15].tQTaskRefList.ptMiddle & ~1u);
}

// source: j/0/weapons/mine.c:283  [anchor-mhash]
void __cdecl Mine_DeleteHandler(struct QTask_s *ptQTask)
{
  QTaskList_Remove(GameFunctions_ptNotifyQTaskList, ptQTask);
  QTaskList_Remove(Mine_ptMineQTaskList, ptQTask);
  QTaskList_Remove(GameFunctions_ptCutsceneDeleteQTaskList, ptQTask);
  if ( Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER )
    NetworkGameItem_RemoveGameItem(LOWORD(ptQTask[16].tQTaskChildren.ptHead));
  ((void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[2][ExplodeObject_eQTaskType].pfHandler)(ptQTask);
}

// source: j/0/weapons/mine.c:317  [size]
void __cdecl Mine_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = Mine_ptParameterList;
}

// source: j/0/weapons/mine.c:333  [anchor-callee]
void __cdecl Mine_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ((void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[ParameterList_eUpdateInternalDataQTaskEvent][ExplodeObject_eQTaskType].pfHandler)(
    ptQTask,
    pxContext);
  ptQTask[15].ptParent = (struct QTask_s *)(__int64)(*(float *)&ptQTask[15].eQTaskType * 30.0);
}

// source: j/0/weapons/mine.c:357  [size]
void __cdecl Mine_NotifyHandler(struct QTask_s *ptQTask, void *pxContext)
{
  double v2; // st7
  double v3; // st6
  double v4; // st5

  if ( !BYTE2(ptQTask[16].ptPrev) )
  {
    v2 = *((double *)pxContext + 1) - *(double *)&ptQTask[1].ptNext;
    v3 = *((double *)pxContext + 2) - *(double *)&ptQTask[1].tQTaskChildren.ptHead;
    v4 = *((double *)pxContext + 3) - *(double *)&ptQTask[1].tQTaskChildren.ptTail;
    if ( *(float *)&ptQTask[16].ptNext * 4096.0 + *((float *)pxContext + 8) > sqrt(v3 * v3 + v4 * v4 + v2 * v2)
      && *(float *)&ptQTask[3].ptParent * v4
       + *(float *)&ptQTask[3].tQTaskRefList.ptHead * v3
       + *(float *)&ptQTask[3].tQTaskChildren.ptHead * v2 > 0.0 )
    {
      ptQTask[15].tQTaskRefList.ptMiddle = (struct QReference_s *)((int)ptQTask[15].tQTaskRefList.ptMiddle | 1);
      if ( BYTE1(ptQTask[16].ptPrev) )
      {
        if ( !ptQTask[15].tQTaskRefList.ptTail && !LOBYTE(ptQTask[16].ptPrev) )
          LOBYTE(ptQTask[16].ptPrev) = 1;
      }
    }
  }
}

// source: j/0/weapons/mine.c:423  [size]
void __cdecl Mine_DrawComputerObjectHandler(struct QTask_s *ptQTask, void *pxContext)
{
  double v2; // st7
  double v3; // st7
  int *v4; // eax
  int v5; // eax
  double v6; // st6

  *((_DWORD *)pxContext + 3) = ptQTask + 1;
  *((_DWORD *)pxContext + 4) = (char *)ptQTask + 124;
  if ( *(float *)&ptQTask[6].tQTaskChildren.ptHead <= (double)*(float *)&ptQTask[6].tQTaskChildren.ptMiddle )
    v2 = *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
  else
    v2 = *(float *)&ptQTask[6].tQTaskChildren.ptHead;
  if ( v2 >= *(float *)&ptQTask[6].ptPrev )
  {
    if ( *(float *)&ptQTask[6].tQTaskChildren.ptHead <= (double)*(float *)&ptQTask[6].tQTaskChildren.ptMiddle )
      v3 = *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
    else
      v3 = *(float *)&ptQTask[6].tQTaskChildren.ptHead;
  }
  else
  {
    v3 = *(float *)&ptQTask[6].ptPrev;
  }
  v4 = *(int **)&ptQTask[2].eQTaskType;
  if ( v4 && (v5 = *v4) != 0 )
    v6 = *(float *)(*(_DWORD *)(*(_DWORD *)(v5 + 12) + 12) + 120);
  else
    v6 = 1.0;
  *((_DWORD *)pxContext + 6) = 0;
  *((float *)pxContext + 5) = v3 * v6;
  if ( !LOBYTE(ptQTask[11].tQTaskChildren.ptTail) )
  {
    if ( BYTE2(ptQTask[16].ptPrev) )
    {
      *((_DWORD *)pxContext + 6) = &ComputerMenu_tComputerMenuResource.atQSpriteHilight[5];
      ComputerObject_DrawSprite((struct DrawComputerObjectContext_s *)pxContext);
      *((_DWORD *)pxContext + 6) = 0;
    }
  }
}

// source: j/0/weapons/mine.c:463  [size]
unsigned __int16 __cdecl Mine_GetQTaskType()
{
  return Mine_eQTaskType;
}

// source: j/0/weapons/mine.c:478  [size]
struct QTaskList_s *__cdecl Mine_GetMineQTaskList()
{
  return Mine_ptMineQTaskList;
}

// source: j/0/weapons/mine.c:503  [anchor-callee]
struct QTask_s *__cdecl Mine_New(
        struct QTask_s *ptParent,
        struct real64x3_t *ptPos,
        struct real32x9_t *ptOrientation,
        char *zModel,
        int nTimeBeforeArm,
        float vTimeBeforeExplode,
        float vDetectionRadius,
        float vExplodeRadius,
        enum bool isRemoteMine)
{
  struct QTask_s *v9; // ebx

  v9 = QTask_NewFn(ptParent, Mine_eQTaskType, nullptr);
  qmemcpy(&v9[8], ptPos, 0x18u);
  qmemcpy(&v9[8].tQTaskRefList.ptMiddle, ptOrientation, sizeof(struct QTask_s));
  strcpy((char *)&v9[9].tQTaskRefList.ptMiddle, zModel);
  *(float *)&v9[15].eQTaskType = vTimeBeforeExplode;
  v9[15].tQTaskRefList.ptTail = (struct QReference_s *)nTimeBeforeArm;
  BYTE2(v9[16].ptPrev) = isRemoteMine;
  *(float *)&v9[16].ptNext = vDetectionRadius;
  ExplodeObject_SetParameters(v9, 1.0, vExplodeRadius, 0.0, 1.0, 0.0, 5, 1, "explo_proxy");
  Mine_UpdateInternalDataHandler(v9, nullptr);
  return v9;
}

// source: j/0/weapons/mine.c:554  [anchor-hash]
void __cdecl Mine_DeleteAll()
{
  struct QTaskList_s *v0; // edi
  struct QTask_s **ptQTask; // esi

  v0 = Mine_ptMineQTaskList;
  if ( Mine_ptMineQTaskList->nTask )
  {
    ptQTask = Mine_ptMineQTaskList->ptQTask;
    do
      QTask_Delete(*ptQTask);
    while ( v0->nTask );
  }
}

// source: j/0/weapons/mine.c:578  [anchor-strings]
void __cdecl Mine_Open()
{
  unsigned __int16 v0; // si
  __int16 v1; // ax
  unsigned __int16 v2; // si

  v0 = QTask_NewQTaskType("Mine", 656, ExplodeObject_eQTaskType, 0, 0);
  Mine_eQTaskType = v0;
  QTask_LinkQTaskEventHandlerFn(
    v0,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveNoChildrenHandler);
  QTask_LinkQTaskEventHandlerFn(v0, 0, Mine_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 1, Mine_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 2, Mine_DeleteHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Mine_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(v0, ParameterList_eUpdateInternalDataQTaskEvent, Mine_UpdateInternalDataHandler);
  QTask_LinkQTaskEventHandlerFn(v0, GameFunctions_eNotifyQTaskEvent, Mine_NotifyHandler);
  v1 = ComputerObject_eDrawComputerObjectQTaskEvent;
  if ( ComputerObject_eDrawComputerObjectQTaskEvent == 512 )
  {
    v1 = QTask_NewQTaskEventFn(0x200u, "DrawComputerObject");
    v0 = Mine_eQTaskType;
    ComputerObject_eDrawComputerObjectQTaskEvent = v1;
  }
  QTask_LinkQTaskEventHandlerFn(v0, v1, Mine_DrawComputerObjectHandler);
  QTask_LinkQTaskEventHandlerFn(v0, NetworkGameItem_eGetGameItemDataQTaskEvent, Mine_GetGameItemDataHandler);
  Mine_ptMineQTaskList = QTaskList_New(64);
  Mine_ptParameterList = ParameterList_Derive(ExplodeObject_ptParameterList, 2);
  ParameterList_AddParameter(Mine_ptParameterList, 0x280u, Level_eParameterTypeReal32, "Arm Radius (m)", 7u, nullptr);
  ParameterList_AddParameter(
    Mine_ptParameterList,
    0x27Cu,
    Level_eParameterTypeReal32,
    "Time Before Explode (s)",
    7u,
    nullptr);
  Symbol_Register(
    "TASKTYPE_MINE",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)Mine_eQTaskType,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  v2 = Mine_eQTaskType;
  QTask_LinkQTaskEventHandlerFn(
    Mine_eQTaskType,
    Serialize_eGetSerializeInfoQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Mine_GetSerializeInfoHandler);
  QTask_LinkQTaskEventHandlerFn(
    v2,
    Serialize_eGetSerializeParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Mine_GetSerializeParameterListHandler);
  Mine_ptSerializeParameterList = ParameterList_Derive(ExplodeObject_ptSerializeParameterList, 8);
  ParameterList_AddParameter(Mine_ptSerializeParameterList, 0x270u, Level_eParameterTypeInt32, "bFlags", 7u, nullptr);
  ParameterList_AddParameter(
    Mine_ptSerializeParameterList,
    0x274u,
    Level_eParameterTypeInt32,
    "nTimeBeforeArm",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Mine_ptSerializeParameterList,
    0x278u,
    Level_eParameterTypeInt32,
    "nTimeBeforeExplode",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Mine_ptSerializeParameterList,
    0x27Cu,
    Level_eParameterTypeReal32,
    "vTimeBeforeExplode",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Mine_ptSerializeParameterList,
    0x280u,
    Level_eParameterTypeReal32,
    "vDetectionRadius",
    7u,
    nullptr);
  ParameterList_AddParameter(Mine_ptSerializeParameterList, 0x284u, Level_eParameterTypebool8, "isArmed", 7u, nullptr);
  ParameterList_AddParameter(Mine_ptSerializeParameterList, 0x285u, Level_eParameterTypebool8, "isArmable", 7u, nullptr);
  ParameterList_AddParameter(
    Mine_ptSerializeParameterList,
    0x286u,
    Level_eParameterTypebool8,
    "isRemoteMine",
    7u,
    nullptr);
}

// source: j/0/weapons/mine.c:629  [size]
void __cdecl Mine_Close()
{
  int v0; // esi
  int v1; // esi

  if ( Mine_ptParameterList )
  {
    v0 = *(_DWORD *)((unsigned int)&Mine_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
  if ( Mine_ptSerializeParameterList )
  {
    v1 = *(_DWORD *)((unsigned int)&Mine_ptSerializeParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v1);
    memset(*(void **)(v1 + 8), 0xCDu, *(_DWORD *)(v1 + 16));
    free((void *)v1);
  }
  QTaskList_Delete(Mine_ptMineQTaskList);
  QTask_DeleteQTaskType(Mine_eQTaskType);
}

// source: j/0/weapons/mine.c:653  [anchor-strings]
struct QTask_s *__cdecl Mine_CreateFromItem(void *pxItem, unsigned __int16 iGameItemID)
{
  int v2; // eax
  struct WeaponType_s *WeaponTypeFromID; // eax
  double v4; // st7
  float *pxObject; // esi
  struct real32x3_t *v6; // ecx
  long double v7; // st7
  int v8; // eax
  struct WeaponType_s *v9; // eax
  struct real32x9_t tOrientation; // [esp+10h] [ebp-28h] BYREF

  v2 = Script_ParseLineInt32("WEAPON_ID_PROXIMITYMINE");
  WeaponTypeFromID = WeaponType_GetWeaponTypeFromID(v2);
  v4 = *((float *)pxItem + 6);
  pxObject = (float *)WeaponTypeFromID->atFireTypes[0].ptParametersQTaskRef->pxObject;
  Mine_iGameItemID = iGameItemID;
  v6 = (struct real32x3_t *)((char *)pxItem + 24);
  if ( v4 != 0.0 || *((float *)pxItem + 7) != 0.0 || *((float *)pxItem + 8) != 0.0 )
  {
    v7 = 1.0
       / sqrt(
           v6->vX * v6->vX
         + *((float *)pxItem + 7) * *((float *)pxItem + 7)
         + *((float *)pxItem + 8) * *((float *)pxItem + 8));
    v6->vX = v6->vX * v7;
    *((float *)pxItem + 7) = *((float *)pxItem + 7) * v7;
    *((float *)pxItem + 8) = *((float *)pxItem + 8) * v7;
  }
  GameFunctions_CreateOrientationFromDirection(&tOrientation, v6);
  v8 = Script_ParseLineInt32("WEAPON_ID_PROXIMITYMINE");
  v9 = WeaponType_GetWeaponTypeFromID(v8);
  return Mine_New(
           Level_ptDynamicQTask,
           (struct real64x3_t *)pxItem,
           &tOrientation,
           v9->zFixedModel,
           (__int64)(pxObject[13] * 30.0),
           pxObject[14],
           pxObject[15],
           pxObject[16],
           false);
}

// source: j/0/weapons/mine.c:700  [size]
void __cdecl Mine_SetGameItemID(int iGameItemID)
{
  Mine_iGameItemID = iGameItemID;
}

// source: j/0/weapons/mine.c:713  [size]
int __cdecl Mine_GetGameItemID(struct QTask_s *ptQTask)
{
  return LOWORD(ptQTask[16].tQTaskChildren.ptHead);
}
