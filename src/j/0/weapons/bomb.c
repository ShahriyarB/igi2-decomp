/* j/0/weapons/bomb.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/weapons/bomb.c:58  [anchor-mhash]
void __cdecl Bomb_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  bool v2; // zf

  QTaskList_Register(GameFunctions_ptNotifyQTaskList, (struct QTaskList_s *)ptQTask);
  QTaskList_Register(Bomb_ptBombQTaskList, (struct QTaskList_s *)ptQTask);
  QTaskList_Register(GameFunctions_ptCutsceneDeleteQTaskList, (struct QTaskList_s *)ptQTask);
  ((void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[0][ExplodeObject_eQTaskType].pfHandler)(
    ptQTask,
    pxContext);
  ExplodeObject_SetParameters(ptQTask, 1.0, 2.0, 0.0, 1.0, 0.0, 5, 1, "explo_proxy");
  sprintf((char *const)&ptQTask[9].tQTaskRefList.ptMiddle, "136_01_1");
  v2 = Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER;
  ptQTask[16].ptNext = (struct QTask_s *)1084227584;
  ptQTask[16].ptPrev = (struct QTask_s *)1110704128;
  ptQTask[15].ptParent = (struct QTask_s *)150;
  *(_DWORD *)&ptQTask[15].eQTaskType = 1350;
  LOBYTE(ptQTask[16].tQTaskChildren.ptMiddle) = 0;
  BYTE1(ptQTask[16].tQTaskChildren.ptMiddle) = 0;
  ptQTask[15].tQTaskRefList.ptTail = nullptr;
  ptQTask[16].tQTaskChildren.ptTail = nullptr;
  if ( v2 && !Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle )
  {
    ptQTask[16].tQTaskRefList.ptHead = (struct QReference_s *)NetworkGameItem_RegisterGameItem(
                                                                ptQTask,
                                                                0x30u,
                                                                g_iGameItemID);
    g_iGameItemID = 0;
  }
}

void __cdecl sub_476630(struct QTask_s *ptQTask)
{
  struct QTask_s *ptBombComputerHighlightQTask; // eax
  struct QTask_s *ptParent; // eax
  int v3; // eax
  int v4; // eax

  ((void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[1][ExplodeObject_eQTaskType].pfHandler)(ptQTask);
  if ( Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER )
  {
    if ( NetMission_ptNetMission )
    {
      ptBombComputerHighlightQTask = NetMission_ptNetMission->ptBombComputerHighlightQTask;
      if ( ptBombComputerHighlightQTask )
      {
        qmemcpy(&ptBombComputerHighlightQTask[1], &ptQTask[1], 0x18u);
        *(double *)&ptBombComputerHighlightQTask[1].tQTaskChildren.ptTail = *(double *)&ptBombComputerHighlightQTask[1].tQTaskChildren.ptTail
                                                                          + 8192.0;
      }
    }
  }
  ptParent = ptQTask[15].ptParent;
  if ( ptParent )
    ptQTask[15].ptParent = (struct QTask_s *)((char *)ptParent - 1);
  else
    LOBYTE(ptQTask[16].tQTaskChildren.ptMiddle) = 1;
  if ( LOBYTE(ptQTask[16].tQTaskChildren.ptMiddle) )
  {
    v3 = *(_DWORD *)&ptQTask[15].eQTaskType;
    if ( v3 )
      *(_DWORD *)&ptQTask[15].eQTaskType = v3 - 1;
    else
      LOBYTE(ptQTask[13].tQTaskRefList.ptHead) = 1;
  }
  if ( LOBYTE(ptQTask[11].tQTaskChildren.ptTail) )
    QTask_Delete(ptQTask);
  v4 = *(_DWORD *)&ptQTask[15].eQTaskType;
  if ( v4 == 900
    || v4 == 600
    || v4 == 300
    || v4 == 270
    || v4 == 240
    || v4 == 210
    || v4 == 180
    || v4 == 150
    || v4 == 120
    || v4 == 90
    || v4 == 60
    || v4 == 30 )
  {
    SoundSys_NewSoundFn(ptQTask, "tba_c4seconds2");
  }
}

// source: j/0/weapons/bomb.c:210  [anchor-mhash]
void __cdecl Bomb_DeleteHandler(struct QTask_s *ptQTask)
{
  QTask_DeleteQTaskAndQTaskRefSafe((struct QReference_s **)&ptQTask[16].tQTaskChildren.ptTail);
  QTaskList_Remove(GameFunctions_ptNotifyQTaskList, ptQTask);
  QTaskList_Remove(Bomb_ptBombQTaskList, ptQTask);
  QTaskList_Remove(GameFunctions_ptCutsceneDeleteQTaskList, ptQTask);
  if ( Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER && !Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle )
    NetworkGameItem_RemoveGameItem((int)ptQTask[16].tQTaskRefList.ptHead);
  ((void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[2][ExplodeObject_eQTaskType].pfHandler)(ptQTask);
  if ( ptQTask[15].tQTaskRefList.ptMiddle )
  {
    QTask_Delete((struct QTask_s *)ptQTask[15].tQTaskRefList.ptMiddle);
    ptQTask[15].tQTaskRefList.ptMiddle = nullptr;
  }
}

// source: j/0/weapons/bomb.c:248  [size]
void __cdecl Bomb_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = Bomb_ptParameterList;
}

// source: j/0/weapons/bomb.c:264  [anchor-callee]
void __cdecl Bomb_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ((void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[ParameterList_eUpdateInternalDataQTaskEvent][ExplodeObject_eQTaskType].pfHandler)(
    ptQTask,
    pxContext);
  ptQTask[15].ptParent = (struct QTask_s *)(__int64)(*(float *)&ptQTask[16].ptNext * 30.0);
  *(_DWORD *)&ptQTask[15].eQTaskType = (__int64)(*(float *)&ptQTask[16].ptPrev * 30.0);
}

// source: j/0/weapons/bomb.c:289  [size]
void __cdecl Bomb_NotifyHandler(struct QTask_s *ptQTask, void *pxContext)
{
  double v2; // st7
  double v3; // st6
  double v4; // st5

  if ( !BYTE2(ptQTask[16].tQTaskChildren.ptMiddle) )
  {
    v2 = *((double *)pxContext + 1) - *(double *)&ptQTask[1].ptNext;
    v3 = *((double *)pxContext + 2) - *(double *)&ptQTask[1].tQTaskChildren.ptHead;
    v4 = *((double *)pxContext + 3) - *(double *)&ptQTask[1].tQTaskChildren.ptTail;
    if ( *(float *)&ptQTask[16].tQTaskChildren.ptHead * 4096.0 + *((float *)pxContext + 8) > sqrt(
                                                                                               v3 * v3
                                                                                             + v4 * v4
                                                                                             + v2 * v2)
      && *(float *)&ptQTask[3].ptParent * v4
       + *(float *)&ptQTask[3].tQTaskRefList.ptHead * v3
       + *(float *)&ptQTask[3].tQTaskChildren.ptHead * v2 > 0.0 )
    {
      ptQTask[15].tQTaskRefList.ptTail = (struct QReference_s *)((int)ptQTask[15].tQTaskRefList.ptTail | 1);
      if ( BYTE1(ptQTask[16].tQTaskChildren.ptMiddle) )
      {
        if ( !ptQTask[15].ptParent && !LOBYTE(ptQTask[16].tQTaskChildren.ptMiddle) )
          LOBYTE(ptQTask[16].tQTaskChildren.ptMiddle) = 1;
      }
    }
  }
}

// source: j/0/weapons/bomb.c:355  [size]
void __cdecl Bomb_DrawComputerObjectHandler(struct QTask_s *ptQTask, void *pxContext)
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
    if ( BYTE2(ptQTask[16].tQTaskChildren.ptMiddle) )
    {
      *((_DWORD *)pxContext + 6) = &ComputerMenu_tComputerMenuResource.atQSpriteHilight[5];
      ComputerObject_DrawSprite((struct DrawComputerObjectContext_s *)pxContext);
      *((_DWORD *)pxContext + 6) = 0;
    }
  }
}

// source: j/0/weapons/bomb.c:395  [anchor-strings]
void __cdecl Bomb_Open()
{
  unsigned __int16 v0; // si
  __int16 v1; // ax

  v0 = QTask_NewQTaskType("Bomb", 664, ExplodeObject_eQTaskType, 0, 0);
  Bomb_eQTaskType = v0;
  QTask_LinkQTaskEventHandlerFn(
    v0,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveNoChildrenHandler);
  QTask_LinkQTaskEventHandlerFn(v0, 0, Bomb_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 1, sub_476630);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 2, Bomb_DeleteHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Bomb_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(v0, ParameterList_eUpdateInternalDataQTaskEvent, Bomb_UpdateInternalDataHandler);
  QTask_LinkQTaskEventHandlerFn(v0, GameFunctions_eNotifyQTaskEvent, Bomb_NotifyHandler);
  v1 = ComputerObject_eDrawComputerObjectQTaskEvent;
  if ( ComputerObject_eDrawComputerObjectQTaskEvent == 512 )
  {
    v1 = QTask_NewQTaskEventFn(0x200u, "DrawComputerObject");
    v0 = Bomb_eQTaskType;
    ComputerObject_eDrawComputerObjectQTaskEvent = v1;
  }
  QTask_LinkQTaskEventHandlerFn(v0, v1, Bomb_DrawComputerObjectHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    NetworkGameItem_eGetGameItemDataQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))sub_4764C0);
  Bomb_ptBombQTaskList = QTaskList_New(64);
  Bomb_ptParameterList = ParameterList_Derive(ExplodeObject_ptParameterList, 2);
  ParameterList_AddParameter(
    Bomb_ptParameterList,
    0x280u,
    Level_eParameterTypeReal32,
    "Time before arm (s)",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Bomb_ptParameterList,
    0x284u,
    Level_eParameterTypeReal32,
    "Time Before explode (s)",
    7u,
    nullptr);
  Symbol_Register(
    "TASKTYPE_BOMB",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)Bomb_eQTaskType,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
}

// source: j/0/weapons/bomb.c:433  [size]
void __cdecl Bomb_Close()
{
  int v0; // esi

  if ( Bomb_ptParameterList )
  {
    v0 = *(_DWORD *)((unsigned int)&Bomb_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
  QTaskList_Delete(Bomb_ptBombQTaskList);
  QTask_DeleteQTaskType(Bomb_eQTaskType);
}

// source: j/0/weapons/bomb.c:453  [size]
unsigned __int16 __cdecl Bomb_GetQTaskType()
{
  return Bomb_eQTaskType;
}

// source: j/0/weapons/bomb.c:468  [size]
struct QTaskList_s *__cdecl Bomb_GetBombQTaskList()
{
  return Bomb_ptBombQTaskList;
}

// source: j/0/weapons/bomb.c:494  [anchor-callee]
struct QTask_s *__cdecl Bomb_New(
        struct QTask_s *ptParent,
        struct real64x3_t *ptPos,
        struct real32x9_t *ptOrientation,
        char *zModel,
        float vTimeBeforeArm,
        float vTimeBeforeExplode,
        float vEffectiveRange,
        float vExplodeRadius,
        float vMaxDamageScale,
        enum bool isRemoteBomb)
{
  struct QTask_s *v10; // ebx

  v10 = QTask_NewFn(ptParent, Bomb_eQTaskType, nullptr);
  qmemcpy(&v10[8], ptPos, 0x18u);
  qmemcpy(&v10[8].tQTaskRefList.ptMiddle, ptOrientation, sizeof(struct QTask_s));
  strcpy((char *)&v10[9].tQTaskRefList.ptMiddle, zModel);
  *(float *)&v10[16].ptNext = vTimeBeforeArm;
  *(float *)&v10[16].ptPrev = vTimeBeforeExplode;
  BYTE2(v10[16].tQTaskChildren.ptMiddle) = isRemoteBomb;
  ExplodeObject_SetParameters(v10, vMaxDamageScale, vEffectiveRange, vExplodeRadius, 1.2999999523162842, 0.0, 5, 1, "explo_proxy");
  Bomb_UpdateInternalDataHandler(v10, nullptr);
  return v10;
}

struct QTask_s *__cdecl sub_476CC0(unsigned __int16 a1, int a2, void *a3)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct QTask_s ptQTask; };
    struct { char igi2_o1[56]; _BYTE v16[24]; };
    struct { char igi2_o2[80]; _BYTE v17[40]; };
    struct { char igi2_o3[120]; int v18; };
    struct { char igi2_o4[124]; int v19; };
    struct { char igi2_o5[128]; struct QTask_s *v20; };
    struct { char igi2_o6[132]; struct QTask_s *v21; };
    struct { char igi2_o7[136]; struct real32x9_t ptOrientation; };
    char igi2_extent[180];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  double v3; // st7
  struct real32x3_t *v4; // ecx
  struct QTask_s *v5; // ebp
  long double v6; // st7
  int v7; // eax
  char *zFixedModel; // eax
  int v9; // edx
  char v10; // cl
  struct QTask_s *ptPrev; // eax
  int v12; // edx
  struct QTask_s *ptMiddle; // ecx

  v3 = *(float *)(a2 + 24);
  v4 = (struct real32x3_t *)(a2 + 24);
  v5 = C4Bomb_ptQTask;
  g_iGameItemID = a1;
  if ( v3 != 0.0 || *(float *)(a2 + 28) != 0.0 || *(float *)(a2 + 32) != 0.0 )
  {
    v6 = 1.0
       / sqrt(*(float *)(a2 + 28) * *(float *)(a2 + 28) + *(float *)(a2 + 32) * *(float *)(a2 + 32) + v4->vX * v4->vX);
    v4->vX = v4->vX * v6;
    *(float *)(a2 + 28) = *(float *)(a2 + 28) * v6;
    *(float *)(a2 + 32) = *(float *)(a2 + 32) * v6;
  }
  GameFunctions_CreateOrientationFromDirection(&igi2_frame.ptOrientation, v4);
  qmemcpy(igi2_frame.v16, (void *)a2, sizeof(igi2_frame.v16));
  qmemcpy(igi2_frame.v17, &igi2_frame.ptOrientation, sizeof(igi2_frame.v17));
  v7 = Script_ParseLineInt32("WEAPON_ID_C4BOMB");
  zFixedModel = WeaponType_GetWeaponTypeFromID(v7)->zFixedModel;
  v9 = (char *)&igi2_frame.ptQTask.tQTaskRefList - zFixedModel;
  do
  {
    v10 = *zFixedModel;
    zFixedModel[v9] = *zFixedModel;
    ++zFixedModel;
  }
  while ( v10 );
  ptPrev = v5[3].ptPrev;
  v12 = *(_DWORD *)(a2 + 40);
  igi2_frame.v18 = *(_DWORD *)(a2 + 36);
  ptMiddle = v5[3].tQTaskChildren.ptMiddle;
  igi2_frame.v20 = ptPrev;
  igi2_frame.v19 = v12;
  igi2_frame.v21 = ptMiddle;
  return C4BombArea_PlaceBomb(&igi2_frame.ptQTask, a3);
}

unsigned __int16 __cdecl sub_476DE0(unsigned __int16 a1)
{
  g_iGameItemID = a1;
  return a1;
}

int __cdecl sub_476DF0(int a1)
{
  return *(_DWORD *)(a1 + 660);
}
