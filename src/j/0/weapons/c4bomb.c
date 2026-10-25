/* j/0/weapons/c4bomb.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/weapons/c4bomb.c:147  [anchor-callee]
enum bool __cdecl C4BombArea_IsInsideArea(
        struct QTask_s *ptQTask,
        struct real64x3_t *ptPos)
{
  double v2; // st7
  double v3; // st6
  double v4; // st5
  float Real32x3_RotateInverse_tTemp; // [esp+0h] [ebp-Ch]
  float Real32x3_RotateInverse_tTemp_4; // [esp+4h] [ebp-8h]
  float Real32x3_RotateInverse_tTemp_8; // [esp+8h] [ebp-4h]

  v2 = ptPos->vX - *(double *)&ptQTask[2].tQTaskChildren.ptTail;
  v3 = ptPos->vY - *(double *)&ptQTask[2].tQTaskRefList.ptMiddle;
  v4 = ptPos->vZ - *(double *)&ptQTask[2].ptParent;
  Real32x3_RotateInverse_tTemp = v4 * *(float *)&ptQTask[4].tQTaskChildren.ptHead
                               + v3 * *(float *)&ptQTask[3].eQTaskType
                               + v2 * *(float *)&ptQTask[3].tQTaskRefList.ptMiddle;
  Real32x3_RotateInverse_tTemp_4 = v4 * *(float *)&ptQTask[4].tQTaskChildren.ptMiddle
                                 + v3 * *(float *)&ptQTask[4].ptNext
                                 + v2 * *(float *)&ptQTask[3].tQTaskRefList.ptTail;
  Real32x3_RotateInverse_tTemp_8 = v4 * *(float *)&ptQTask[4].tQTaskChildren.ptTail
                                 + v3 * *(float *)&ptQTask[4].ptPrev
                                 + v2 * *(float *)&ptQTask[3].ptParent;
  return Real32x3_RotateInverse_tTemp <= (double)*(float *)&ptQTask[3].ptNext
      && Real32x3_RotateInverse_tTemp_4 <= (double)*(float *)&ptQTask[3].ptPrev
      && Real32x3_RotateInverse_tTemp_8 <= (double)*(float *)&ptQTask[3].tQTaskChildren.ptHead
      && -*(float *)&ptQTask[3].ptNext <= Real32x3_RotateInverse_tTemp
      && -*(float *)&ptQTask[3].ptPrev <= Real32x3_RotateInverse_tTemp_4
      && -*(float *)&ptQTask[3].tQTaskChildren.ptHead <= Real32x3_RotateInverse_tTemp_8;
}

void __cdecl sub_4F81C0(struct QTask_s *a1)
{
  C4Bomb_ptQTask = a1;
  a1[2].ptParent = (struct QTask_s *)-1;
  *(_DWORD *)&a1[2].eQTaskType = 1;
  a1[3].ptPrev = (struct QTask_s *)1065353216;
  a1[3].tQTaskChildren.ptHead = nullptr;
  a1[3].tQTaskChildren.ptMiddle = (struct QTask_s *)1077936128;
  LOBYTE(a1[3].tQTaskRefList.ptMiddle) = 0;
  LOBYTE(a1[4].tQTaskChildren.ptTail) = 0;
  LOBYTE(a1[5].tQTaskChildren.ptHead) = 0;
  a1[3].ptNext = nullptr;
  a1[1].ptNext = nullptr;
  a1[1].tQTaskChildren.ptHead = nullptr;
  a1[1].tQTaskChildren.ptMiddle = nullptr;
  a1[1].tQTaskChildren.ptTail = nullptr;
  a1[1].tQTaskRefList.ptHead = nullptr;
  a1[1].tQTaskRefList.ptMiddle = nullptr;
  a1[1].tQTaskRefList.ptTail = nullptr;
  a1[1].ptParent = (struct QTask_s *)1065353216;
  *(_DWORD *)&a1[1].eQTaskType = 0;
  a1[2].ptNext = nullptr;
  a1[2].ptPrev = nullptr;
  a1[2].tQTaskChildren.ptHead = (struct QTask_s *)1065353216;
  a1[2].tQTaskChildren.ptMiddle = nullptr;
  a1[2].tQTaskChildren.ptTail = nullptr;
  a1[2].tQTaskRefList.ptHead = nullptr;
  a1[2].tQTaskRefList.ptMiddle = (struct QReference_s *)1065353216;
  a1[2].tQTaskRefList.ptTail = nullptr;
  a1[3].tQTaskChildren.ptTail = nullptr;
  a1[3].tQTaskRefList.ptHead = nullptr;
}

void __cdecl sub_4F8250(struct QTask_s *a1)
{
  C4Bomb_ptQTask = nullptr;
}

// source: j/0/weapons/c4bomb.c:234  [anchor-mhash]
void __cdecl C4BombArea_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *v2; // eax

  ptQTask[10].ptNext = nullptr;
  ptQTask[10].ptPrev = nullptr;
  ptQTask[10].tQTaskChildren.ptHead = nullptr;
  ptQTask[10].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[10].tQTaskRefList.ptHead = nullptr;
  ptQTask[10].tQTaskChildren.ptTail = nullptr;
  ptQTask[10].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[1].ptNext = nullptr;
  ptQTask[8].ptNext = nullptr;
  ptQTask[8].ptPrev = nullptr;
  ptQTask[8].tQTaskChildren.ptHead = nullptr;
  *(_DWORD *)&ptQTask[9].eQTaskType = 0;
  v2 = (struct QTask_s *)Mem_AllocFn(12, 4);
  if ( !v2 )
  {
    LDebug_Error((char *)&g_zMessage.anDR[15]);
    abort();
  }
  ptQTask[10].ptParent = v2;
  v2->ptPrev = nullptr;
  v2->ptNext = nullptr;
  v2->tQTaskChildren.ptHead = ptQTask;
  List_AddTail(v2, (int)&C4BombArea_tC4BombAreaList);
  ptQTask[3].tQTaskChildren.ptMiddle = (struct QTask_s *)1166016512;
  ptQTask[3].tQTaskChildren.ptTail = (struct QTask_s *)1166016512;
  ptQTask[3].tQTaskRefList.ptHead = (struct QReference_s *)1166016512;
}

// source: j/0/weapons/c4bomb.c:296  [anchor-mhash]
void __cdecl C4BombArea_DeleteHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptParent; // eax
  int v2; // esi
  int v3; // eax
  struct QReference_s *v4; // ecx
  void (__cdecl *pfHandler)(struct QTask_s *); // eax

  Node_Remove(ptQTask[10].ptParent);
  ptParent = ptQTask[10].ptParent;
  if ( ptParent )
  {
    v2 = *(_DWORD *)((unsigned int)&ptParent[-1].eQTaskType & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v2);
    memset(*(void **)(v2 + 8), 0xCDu, *(_DWORD *)(v2 + 16));
    free((void *)v2);
  }
  ptQTask[10].ptParent = nullptr;
  v3 = 0;
  while ( 1 )
  {
    v4 = Level_atLevelQTaskID[v3];
    if ( v4 )
    {
      if ( v4->pxObject == ptQTask )
        break;
    }
    if ( ++v3 >= 4096 )
      goto LABEL_11;
  }
  if ( v3 >= 0 )
  {
    pfHandler = (void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[Level_eRemoveLevelScriptSymbolsEvent][ptQTask->eQTaskType].pfHandler;
    if ( pfHandler )
      pfHandler(ptQTask);
  }
LABEL_11:
  Level_DeinitLevelExpression((struct LevelExpression_s *)&ptQTask[8]);
}

// source: j/0/weapons/c4bomb.c:335  [anchor-mhash]
void __cdecl C4BombArea_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { float v15; };
    struct { char igi2_o1[4]; struct real64x3_t tCorner; };
    struct { char igi2_o2[28]; struct real64x3_t tMin; };
    struct { char igi2_o3[56]; float v18; };
    struct { char igi2_o4[60]; struct QTask_s *ptTail; };
    struct { char igi2_o5[64]; float v20; };
    struct { char igi2_o6[68]; float v21; };
    struct { char igi2_o7[72]; struct QTask_s *ptParent; };
    struct { char igi2_o8[76]; struct real64x3_t tMax; };
    struct { char igi2_o9[104]; struct QReference_s *v24; };
    struct { char igi2_o10[108]; float v25; };
    struct { char igi2_o11[112]; struct QTask_s *ptPrev; };
    struct { char igi2_o12[116]; struct QTask_s *ptNext; };
    struct { char igi2_o13[120]; float v28; };
    struct { char igi2_o14[124]; struct QTask_s *v29; };
    struct { char igi2_o15[128]; float v30; };
    struct { char igi2_o16[132]; double v31; };
    struct { char igi2_o17[140]; double v32; };
    struct { char igi2_o18[148]; double v33; };
    struct { char igi2_o19[156]; struct real64x3_t Real64x3_Rotate_tTemp; };
    char igi2_extent[180];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  double vZ; // st7
  struct QTask_s *ptHead; // ecx
  double v4; // st6
  struct QReference_s *ptMiddle; // ecx
  double v6; // st5
  struct QTask_s *v7; // ecx
  double v8; // st4
  unsigned int v9; // ecx
  struct QTask_s *v10; // eax
  int v11; // ebx
  double v12; // st6
  double v13; // st6
  double v14; // st5

  vZ = -1.7976931348623157e+308;
  igi2_frame.tMax.vZ = -1.7976931348623157e+308;
  ptQTask[3].ptNext = ptQTask[3].tQTaskChildren.ptMiddle;
  ptHead = (struct QTask_s *)ptQTask[3].tQTaskRefList.ptHead;
  ptQTask[3].ptPrev = ptQTask[3].tQTaskChildren.ptTail;
  ptQTask[3].tQTaskChildren.ptHead = ptHead;
  v4 = *(float *)&ptQTask[3].ptNext * 0.5;
  igi2_frame.ptParent = ptQTask[3].ptParent;
  ptMiddle = ptQTask[3].tQTaskRefList.ptMiddle;
  *(float *)&ptQTask[3].ptNext = v4;
  igi2_frame.v21 = *(float *)&ptMiddle;
  v6 = *(float *)&ptQTask[3].ptPrev * 0.5;
  igi2_frame.ptNext = ptQTask[4].ptNext;
  igi2_frame.ptTail = ptQTask[4].tQTaskChildren.ptTail;
  v7 = ptQTask[4].tQTaskChildren.ptHead;
  *(float *)&ptQTask[3].ptPrev = v6;
  v8 = *(float *)&ptQTask[3].tQTaskChildren.ptHead;
  igi2_frame.v20 = *(float *)&v7;
  HIDWORD(igi2_frame.v31) = ptQTask[2].tQTaskRefList.ptHead;
  igi2_frame.v15 = v8 * 0.5;
  HIDWORD(igi2_frame.v32) = ptQTask[2].tQTaskRefList.ptTail;
  *(float *)&ptQTask[3].tQTaskChildren.ptHead = igi2_frame.v15;
  v9 = *(_DWORD *)&ptQTask[2].eQTaskType;
  igi2_frame.v30 = igi2_frame.v15;
  igi2_frame.v25 = v4;
  igi2_frame.v24 = ptQTask[3].tQTaskRefList.ptTail;
  igi2_frame.v28 = v6;
  igi2_frame.ptPrev = ptQTask[4].ptPrev;
  igi2_frame.v18 = *(float *)&ptQTask[3].eQTaskType;
  igi2_frame.v29 = ptQTask[4].tQTaskChildren.ptMiddle;
  LODWORD(igi2_frame.v31) = ptQTask[2].tQTaskChildren.ptTail;
  LODWORD(igi2_frame.v32) = ptQTask[2].tQTaskRefList.ptMiddle;
  v10 = ptQTask[2].ptParent;
  igi2_frame.tMin.vX = 1.7976931348623157e+308;
  igi2_frame.tMin.vY = 1.7976931348623157e+308;
  igi2_frame.tMin.vZ = 1.7976931348623157e+308;
  igi2_frame.tMax.vX = -1.7976931348623157e+308;
  igi2_frame.tMax.vY = -1.7976931348623157e+308;
  v11 = 0;
  igi2_frame.v33 = COERCE_DOUBLE(__PAIR64__(v9, (unsigned int)v10));
  do
  {
    v12 = (double)(1 - 2 * (v11 & 1)) * igi2_frame.v25;
    igi2_frame.tCorner.vY = (double)(1 - (v11 & 2)) * igi2_frame.v28;
    igi2_frame.tCorner.vZ = (double)(1 - ((v11 >> 1) & 2)) * igi2_frame.v30;
    igi2_frame.Real64x3_Rotate_tTemp.vX = *(float *)&igi2_frame.ptParent * igi2_frame.tCorner.vZ + igi2_frame.v21 * v12 + *(float *)&igi2_frame.v24 * igi2_frame.tCorner.vY;
    igi2_frame.Real64x3_Rotate_tTemp.vY = *(float *)&igi2_frame.ptPrev * igi2_frame.tCorner.vZ + *(float *)&igi2_frame.ptNext * igi2_frame.tCorner.vY + igi2_frame.v18 * v12;
    igi2_frame.Real64x3_Rotate_tTemp.vZ = *(float *)&igi2_frame.v29 * igi2_frame.tCorner.vY + *(float *)&igi2_frame.ptTail * igi2_frame.tCorner.vZ + igi2_frame.v20 * v12;
    qmemcpy(&igi2_frame.tCorner, &igi2_frame.Real64x3_Rotate_tTemp, sizeof(igi2_frame.tCorner));
    v13 = igi2_frame.v31 + igi2_frame.Real64x3_Rotate_tTemp.vX;
    v14 = igi2_frame.v32 + igi2_frame.tCorner.vY;
    igi2_frame.tCorner.vY = igi2_frame.v32 + igi2_frame.tCorner.vY;
    igi2_frame.tCorner.vZ = igi2_frame.v33 + igi2_frame.tCorner.vZ;
    if ( igi2_frame.tMin.vX >= igi2_frame.v31 + igi2_frame.Real64x3_Rotate_tTemp.vX )
      igi2_frame.tMin.vX = v13;
    if ( igi2_frame.tMin.vY >= v14 )
      igi2_frame.tMin.vY = v14;
    if ( igi2_frame.tMin.vZ >= igi2_frame.tCorner.vZ )
      igi2_frame.tMin.vZ = igi2_frame.tCorner.vZ;
    if ( igi2_frame.tMax.vX <= v13 )
      igi2_frame.tMax.vX = v13;
    if ( igi2_frame.tMax.vY <= igi2_frame.tCorner.vY )
      igi2_frame.tMax.vY = igi2_frame.tCorner.vY;
    if ( vZ <= igi2_frame.tCorner.vZ )
      vZ = igi2_frame.tCorner.vZ;
    ++v11;
  }
  while ( v11 < 8 );
  igi2_frame.tMax.vZ = vZ;
  qmemcpy(&ptQTask[1].tQTaskChildren, &igi2_frame.tMin, 0x18u);
  qmemcpy(&ptQTask[1].ptParent, &igi2_frame.tMax, 0x18u);
  Level_CompileLevelExpression((struct LevelExpression_s *)&ptQTask[8], ptQTask);
}

// source: j/0/weapons/c4bomb.c:423  [anchor-caller]
void __cdecl C4BombArea_RunHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct QTask_s *v22; };
    struct { char igi2_o1[4]; struct QTask_s *v23; };
    struct { char igi2_o2[16]; struct NetManagerGameMessage_s ptGameMessage[3]; };
    struct { char igi2_o3[40]; double a2[3]; };
    struct { char igi2_o4[64]; struct real64x3_t ptSource; };
    char igi2_extent[88];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *v1; // ebx
  struct QTask_s *ptHead; // ecx
  struct QTask_s *v3; // edi
  int v4; // edx
  struct QTask_s *v5; // eax
  void (__cdecl *pfHandler)(struct QTask_s *); // eax
  int v7; // edx
  struct QTask_s *ptNext; // eax
  struct QTask_s *v9; // eax
  struct Weapon_s *v10; // esi
  struct WeaponTypeItem_s *ptActiveWeapon; // eax
  int v12; // eax
  struct QTask_s *v13; // esi
  struct QTask_s *v14; // ebx
  struct QTask_s *ptTail; // eax
  struct QTask_s *v16; // edi
  struct QReference_s *v17; // eax
  void (__cdecl *v18)(struct QReference_s **, struct QTask_s *); // eax
  struct QReference_s *v19; // ecx
  struct QTask_s *ptPrev; // eax
  struct QTask_s *ptMiddle; // ecx

  v1 = ptQTask;
  ptHead = ptQTask->tQTaskChildren.ptHead;
  v3 = HumanPlayer_ptQTask;
  igi2_frame.v23 = HumanPlayer_ptQTask;
  igi2_frame.v22 = HumanPlayer_ptQTask;
  if ( ptHead->ptNext && ptHead )
  {
    v4 = QTask_nProtectedQTaskStackOffset;
    do
    {
      if ( ptHead->ptNext )
        v5 = ptHead->ptNext->ptNext != nullptr ? ptHead->ptNext : nullptr;
      else
        v5 = nullptr;
      QTask_atProtectedQTaskStack[v4].ptQTask = v5;
      pfHandler = (void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[1][ptHead->eQTaskType].pfHandler;
      v7 = v4 + 1;
      QTask_nProtectedQTaskStackOffset = v7;
      if ( pfHandler )
      {
        pfHandler(ptHead);
        v7 = QTask_nProtectedQTaskStackOffset;
      }
      ptHead = (struct QTask_s *)dword_849C7DC[v7];
      v4 = v7 - 1;
      QTask_nProtectedQTaskStackOffset = v4;
    }
    while ( ptHead );
  }
  ptNext = ptQTask[1].ptNext;
  if ( ptNext && !ptQTask[10].tQTaskRefList.ptHead )
    ptQTask[10].tQTaskChildren.ptTail = (struct QTask_s *)SLOBYTE(ptNext[13].tQTaskRefList.ptHead);
  if ( ptQTask[8].ptNext && ptQTask[8].ptPrev->ptNext && ptQTask[8].tQTaskChildren.ptHead )
    ptQTask[10].ptPrev = (struct QTask_s *)((int)ptQTask[10].ptPrev
                                          | (char)(__int64)Level_RunLevelExpression(
                                                             (struct LevelExpression_s *)&ptQTask[8],
                                                             ptQTask));
  if ( v3 && ptQTask[10].ptPrev )
  {
    v9 = (struct QTask_s *)C4BombArea_IsInsideArea(
                             ptQTask[10].ptParent->tQTaskChildren.ptHead,
                             (struct real64x3_t *)&v3[1]);
    ptQTask[10].tQTaskChildren.ptHead = v9;
    if ( v9 )
    {
      if ( (v3[30].eQTaskType & 2) != 0 )
      {
        v10 = (struct Weapon_s *)v3[33].ptNext;
        if ( Weapon_GetWeaponTypeItemFromCategory(v10, WEAPONCATEGORY_C4) )
        {
          ptActiveWeapon = v10->tPrivate.ptActiveWeapon;
          if ( ptActiveWeapon )
            ptActiveWeapon = (struct WeaponTypeItem_s *)ptActiveWeapon->ptWeaponType;
          if ( strcmp((char *)&ptActiveWeapon[2].eWeaponTypeID, "WEAPON_ID_C4BOMB")
            && *(float *)&igi2_frame.v22[20].ptNext != 0.0 )
          {
            v12 = Script_ParseLineInt32("WEAPON_ID_C4BOMB");
            igi2_frame.v23[76].ptParent = (struct QTask_s *)WeaponType_GetWeaponTypeFromID(v12)->eID;
          }
          ActionMenuScreen_RegisterActionItem(ActionMenuScreen_ptQTask, ptQTask, nullptr, nullptr);
          v3 = igi2_frame.v22;
          igi2_frame.v23[87].ptParent = (struct QTask_s *)1;
        }
      }
    }
    if ( ptQTask[1].ptNext && !ptQTask[10].tQTaskRefList.ptHead )
    {
      if ( NetManager_GetClientFromHumanQTask(v3)->eTeam == NetMission_eDefendingTeam )
      {
        qmemcpy(igi2_frame.ptGameMessage, &ptQTask[1].ptNext[8], sizeof(igi2_frame.ptGameMessage));
        sub_580CA0((int)igi2_frame.v22, igi2_frame.a2);
        igi2_frame.ptSource.vX = *(double *)igi2_frame.ptGameMessage - igi2_frame.a2[0];
        igi2_frame.ptSource.vY = *(double *)&igi2_frame.ptGameMessage[1] - igi2_frame.a2[1];
        igi2_frame.ptSource.vZ = *(double *)&igi2_frame.ptGameMessage[2] - igi2_frame.a2[2];
        if ( Real64x3_Len(&igi2_frame.ptSource) <= 8192.0 )
        {
          ActionMenuScreen_RegisterActionItem(ActionMenuScreen_ptQTask, ptQTask, nullptr, nullptr);
          if ( (InputPort_atInputPort[0].tInput.bEdgeButton & 0x20000) != 0 )
          {
            v13 = HumanPlayer_ptQTask;
            v14 = HumanPlayer_ptQTask;
            HumanView_DisableZoomMode(HumanPlayer_ptQTask[33].tQTaskChildren.ptTail);
            Human_SetEvaluateActivateTask(v13, ptQTask);
            ptTail = v14[46].tQTaskChildren.ptTail;
            if ( ptTail )
              v16 = ptTail->tQTaskChildren.ptHead;
            else
              v16 = nullptr;
            v17 = v14[46].tQTaskRefList.ptHead;
            if ( v17 )
            {
              QReference_Delete(v17, &QTask_tQTaskRefPool);
              v14[46].tQTaskRefList.ptHead = nullptr;
            }
            if ( v16 )
              v14[46].tQTaskRefList.ptHead = QTask_NewQTaskRef(v16);
            LOBYTE(v14[46].tQTaskRefList.ptMiddle) = 1;
            v14[46].tQTaskRefList.ptTail = nullptr;
            v18 = *((void (__cdecl **)(struct QReference_s **, struct QTask_s *))&v14[30].ptParent->ptNext
                  + (int)v14[31].ptPrev);
            if ( v18 )
              v18(&v14[30].tQTaskRefList.ptMiddle, v14);
            v19 = v14[30].tQTaskRefList.ptTail;
            v14[31].ptNext = v14[31].ptPrev;
            v14[31].ptPrev = (struct QTask_s *)43;
            ptPrev = (struct QTask_s *)v19[14].ptPrev;
            v14[31].tQTaskChildren.ptHead = ptPrev;
            ((void (__cdecl *)(struct QReference_s **, struct QTask_s *))ptPrev)(&v14[30].tQTaskRefList.ptMiddle, v14);
            v1 = ptQTask;
          }
        }
      }
      if ( v1[10].tQTaskChildren.ptTail )
      {
        v1[1].ptNext = nullptr;
        igi2_frame.ptGameMessage[0].eGameMessage = 1094931529;
        igi2_frame.ptGameMessage[0].nLocalTime = NetManager_GetTimer();
        igi2_frame.ptGameMessage[1].eGameMessage = 0;
        igi2_frame.ptGameMessage[1].nLocalTime = Level_GetLevelQTaskIDFromQTask(v1);
        ptMiddle = Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle;
        igi2_frame.ptGameMessage[2].nLocalTime = 0;
        NetManager_SendGameMessage(0, (int)ptMiddle, NETWORKQUEUE_GUARANTEED, igi2_frame.ptGameMessage, 0x18u);
      }
    }
  }
}

// source: j/0/weapons/c4bomb.c:560  [size]
void __cdecl C4Bomb_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = C4Bomb_ptParameterList;
}

// source: j/0/weapons/c4bomb.c:578  [size]
void __cdecl C4BombArea_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = C4BombArea_ptParameterList;
}

// source: j/0/weapons/c4bomb.c:596  [size]
void __cdecl C4Bomb_CreateWeaponTypeParametersHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *((_DWORD *)pxContext + 2) = QTask_NewFn(*((struct QTask_s **)pxContext + 1), C4Bomb_eQTaskType, nullptr);
}

// source: j/0/weapons/c4bomb.c:615  [size]
void __cdecl C4Bomb_GetAnimHandler(struct QTask_s *ptQTask, void *pxContext)
{
  int v2; // ecx
  int v3; // eax
  int v4; // edi
  struct QHashTable_s *v5; // esi
  unsigned int v6; // eax
  int v7; // eax
  int v8; // esi
  int v9; // eax

  v2 = *((_DWORD *)pxContext + 3);
  v3 = *((_DWORD *)pxContext + 5);
  if ( v2 == 4 )
  {
    v4 = v3 + 144;
    v5 = Hierarchy_ptHashTable;
    v6 = Hierarchy_ptHashTable->tPrivate.pfHashFunction(
           Hierarchy_ptHashTable->tPrivate.nHashTableSize,
           *(void **)pxContext);
    v7 = ((int  (__cdecl *)(struct QHashTable_s *, unsigned int, const void *))Hierarchy_ptHashTable->tPrivate.pfFindElement)(v5, v6, (const void *)(*(void **)pxContext));
    v8 = *(_DWORD *)v7;
    v9 = (*(int (__cdecl **)(_DWORD, int))(*(_DWORD *)v7 + 12))(*(_DWORD *)(*(_DWORD *)v7 + 4), v4);
    *((_DWORD *)pxContext + 6) = (*(int (__cdecl **)(int, int, const void *))(v8 + 28))(v8, v9, (const void *)(v4));
  }
  else if ( v2 == 17 )
  {
    *((_DWORD *)pxContext + 6) = Hierarchy_GetAnim(*(unsigned __int8 **)pxContext, (char *)(v3 + 176));
  }
}

// source: j/0/weapons/c4bomb.c:651  [size]
void __cdecl C4Bomb_GetAmmoInfoHandler(struct QTask_s *ptQTask, void *pxContext)
{
  int v2; // eax

  v2 = *(_DWORD *)pxContext;
  *((_DWORD *)pxContext + 2) = 1;
  *((_DWORD *)pxContext + 3) = 1;
  *((_DWORD *)pxContext + 4) = 1;
  *((_DWORD *)pxContext + 1) = AmmoType_GetAmmoTypeFromID(*(_DWORD *)(v2 + 112));
}

// source: j/0/weapons/c4bomb.c:676  [size]
void __cdecl C4BombArea_DrawActionItemHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ActionMenuScreen_DrawActionItem(
    ActionMenuScreen_ptQTask,
    (struct QSprite_s *)&StatusScreen_ptStatusScreenQTask[20].tQTaskRefList,
    pxContext);
}

// source: j/0/weapons/c4bomb.c:777  [size]
void __cdecl C4Bomb_DrawComputerObjectHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ;
}

// source: j/0/weapons/c4bomb.c:817  [anchor-callee]
enum bool __cdecl C4Bomb_AimAtObject(
        struct WeaponFireContext_s *ptFireContext,
        struct QIntersection_s *ptIntersection,
        float vRange)
{
  #pragma pack(push, 1)
  union
  {
    struct { enum bool isDerivedFormHuman; };
    struct { char igi2_o1[4]; enum bool isParentDerivedFromHuman; };
    struct { char igi2_o2[8]; struct WeaponCollisionEvaluateContext_t tWeaponCollisionEvaluateContext; };
    struct { char igi2_o3[28]; struct real64x3_t tPos0; };
    struct { char igi2_o4[52]; struct real64x3_t tPos1; };
    char igi2_extent[76];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  double vY; // st7
  float v5; // ecx
  struct real64x3_t *p_tPosition; // esi
  struct QTask_s *ptIgnoreQTask; // eax
  struct QObj_s *ptHitObj; // ebx
  unsigned __int16 v9; // cx
  struct QTask_s *ptParent; // eax
  unsigned __int16 eQTaskType; // bx
  BOOL v12; // ebp

  vY = ptFireContext->tIn.tOrientation.tY.vY;
  v5 = ptFireContext->tIn.tOrientation.tZ.vY;
  *(float *)&igi2_frame.tWeaponCollisionEvaluateContext.tCollisionEvaluateContext.isEvaluate = ptFireContext->tIn.tOrientation.tX.vY
                                                                                  * vRange;
  *(float *)&igi2_frame.tWeaponCollisionEvaluateContext.ptIgnore1QTask = v5;
  p_tPosition = &ptFireContext->tIn.tPosition;
  ptIgnoreQTask = ptFireContext->tIn.ptIgnoreQTask;
  qmemcpy(&igi2_frame.tPos0, p_tPosition, sizeof(igi2_frame.tPos0));
  igi2_frame.tPos1.vX = *(float *)&igi2_frame.tWeaponCollisionEvaluateContext.tCollisionEvaluateContext.isEvaluate + igi2_frame.tPos0.vX;
  igi2_frame.tPos1.vY = vY * vRange + igi2_frame.tPos0.vY;
  igi2_frame.tWeaponCollisionEvaluateContext.tCollisionEvaluateContext.ptQTask = ptIgnoreQTask;
  igi2_frame.tWeaponCollisionEvaluateContext.ptIgnore1QTask = ptIgnoreQTask;
  igi2_frame.tPos1.vZ = v5 * vRange + igi2_frame.tPos0.vZ;
  igi2_frame.tWeaponCollisionEvaluateContext.ptIgnore2QTask = nullptr;
  igi2_frame.tWeaponCollisionEvaluateContext.vHitProbability = 1.0;
  World_TraceLines(
    Game_ptGame->ptWorld,
    ptIntersection,
    &igi2_frame.tPos0,
    &igi2_frame.tPos1,
    1,
    GameFunctions_eWeaponCollisionEvaluateQTaskEvent,
    &igi2_frame.tWeaponCollisionEvaluateContext.tCollisionEvaluateContext,
    0xFFFFFFFF);
  if ( !ptIntersection->isHit )
    return false;
  ptHitObj = ptIntersection->ptHitObj;
  v9 = Human_eQTaskType;
  if ( !ptHitObj
    || (igi2_frame.isDerivedFormHuman = true,
        QTask_IsQTaskTypeDerived(ptHitObj->tQTask.eQTaskType, Human_eQTaskType) == false) )
  {
    igi2_frame.isDerivedFormHuman = false;
  }
  if ( !ptHitObj
    || (ptParent = ptHitObj->tQTask.ptParent) == nullptr
    || (igi2_frame.isParentDerivedFromHuman = true, QTask_IsQTaskTypeDerived(ptParent->eQTaskType, v9) == false) )
  {
    igi2_frame.isParentDerivedFromHuman = false;
  }
  v12 = false;
  if ( ptHitObj )
  {
    eQTaskType = ptHitObj->tQTask.eQTaskType;
    if ( eQTaskType == Glass_eQTaskType
      || eQTaskType == Door_eQTaskType
      || QTask_IsQTaskTypeDerived(eQTaskType, Vehicle_eQTaskType) )
    {
      v12 = true;
    }
  }
  return igi2_frame.isDerivedFormHuman == false && igi2_frame.isParentDerivedFromHuman == false && !v12;
}

// source: j/0/weapons/c4bomb.c:890  [anchor-caller]
void __cdecl C4Bomb_WeaponFireHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { float vX; };
    struct { char igi2_o1[20]; struct Human_s *ptHumanShooter; };
    struct { char igi2_o2[20]; struct Human_s *ptHumanShootera; };
    struct { char igi2_o3[24]; struct HumanPlayer_t *ptHumanPlayer; };
    struct { char igi2_o4[24]; struct HumanPlayer_t *ptHumanPlayera; };
    struct { char igi2_o5[24]; struct HumanPlayer_t *ptHumanPlayerb; };
    struct { char igi2_o6[28]; struct C4Bomb_t *ptC4BombParameters; };
    struct { char igi2_o7[44]; struct real32x9_t tOrientation; };
    struct { char igi2_o8[84]; struct C4BombArea_t *ptC4BombArea; };
    struct { char igi2_o9[88]; int eState[3]; };
    struct { char igi2_o10[100]; BOOL v59; };
    struct { char igi2_o11[104]; struct QIntersection_s tIntersection; };
    char igi2_extent[224];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v2; // eax
  struct Human_s *v3; // esi
  struct Node_s *ptHead; // ecx
  struct Node_s *ptNext; // eax
  struct C4BombArea_t *v6; // ebx
  bool v7; // zf
  struct C4Bomb_t *v8; // edi
  long double v9; // st4
  struct QTask_s *ptHumanViewQTask; // eax
  struct HumanPlayer_t *v11; // edi
  struct QReference_s *ptEvaluateActivateQTaskRef; // eax
  struct State_s *p_tState; // esi
  struct QReference_s *ptActivateQTaskRef; // eax
  void (__cdecl *v15)(struct State_s *, struct QTask_s *); // eax
  void (__cdecl **apfState)(struct State_s *, struct QTask_s *); // edx
  void (__cdecl *v17)(struct State_s *, struct QTask_s *); // eax
  struct QTask_s *v18; // edi
  struct RandomState_s *p_tRunRandomState; // eax
  double RandomNumberReal32; // st7
  float v21; // ecx
  float *p_ptPrev; // esi
  int v23; // eax
  float v24; // eax
  float v25; // edi
  int v26; // eax
  int v27; // eax
  int v28; // edi
  void (__cdecl *v29)(int, struct real32x9_t *); // eax
  int v30; // edi
  float v31; // ecx
  float v32; // edx
  float v33; // eax
  int v34; // ecx
  int v35; // ecx
  int v36; // eax
  void (__cdecl *v37)(int, struct real32x9_t *); // ecx
  int v38; // eax
  struct AnimController_t *ptActiveUpperBodyController; // edx
  float v40; // ecx
  float v41; // eax
  int v42; // ecx
  int v43; // ecx
  int v44; // eax
  void (__cdecl *pfHandler)(int, struct real32x9_t *); // ecx
  int v46; // eax
  struct AnimController_t *ptActiveMainController; // eax
  struct QTask_s *v48; // esi

  v2 = *(_DWORD *)(*(_DWORD *)pxContext + 96);
  if ( v2 )
  {
    v3 = *(struct Human_s **)(v2 + 8);
    igi2_frame.ptHumanShooter = v3;
  }
  else
  {
    igi2_frame.ptHumanShooter = nullptr;
    v3 = nullptr;
  }
  igi2_frame.ptHumanPlayer = (struct HumanPlayer_t *)HumanPlayer_ptQTask;
  if ( v3 == (struct Human_s *)HumanPlayer_ptQTask && (v3->tState.bSignal & 2) != 0 && v3->ePose != 2 )
  {
    ptHead = C4BombArea_tC4BombAreaList.ptHead;
    ptNext = C4BombArea_tC4BombAreaList.ptHead->ptNext;
    if ( C4BombArea_tC4BombAreaList.ptHead->ptNext )
    {
      while ( 1 )
      {
        v6 = (struct C4BombArea_t *)ptHead[1].ptNext;
        v7 = v6->isInside == false;
        igi2_frame.ptC4BombArea = v6;
        if ( !v7 )
          break;
        ptHead = ptNext;
        ptNext = ptNext->ptNext;
        if ( !ptNext )
          return;
      }
      if ( v6->isLocked == false )
      {
        v8 = *((struct C4Bomb_t **)pxContext + 25);
        igi2_frame.ptC4BombParameters = v8;
        v6->isBombOnObject = false;
        if ( C4Bomb_AimAtObject((struct WeaponFireContext_s *)pxContext, &igi2_frame.tIntersection, 6144.0) )
        {
          GameFunctions_CreateOrientationFromDirection(&igi2_frame.tOrientation, &igi2_frame.tIntersection.tNormal);
          Real32x9_RotateGamma(&igi2_frame.tOrientation, &igi2_frame.tOrientation, 3.1415927410125732);
          qmemcpy((char *)pxContext + 40, &igi2_frame.tOrientation, 0x28u);
          if ( C4Bomb_AimAtObject((struct WeaponFireContext_s *)pxContext, &igi2_frame.tIntersection, 6144.0) )
          {
            if ( igi2_frame.tIntersection.tNormal.vX != 0.0 || igi2_frame.tIntersection.tNormal.vY != 0.0 || igi2_frame.tIntersection.tNormal.vZ != 0.0 )
            {
              v9 = sqrt(
                     igi2_frame.tIntersection.tNormal.vX * igi2_frame.tIntersection.tNormal.vX
                   + igi2_frame.tIntersection.tNormal.vY * igi2_frame.tIntersection.tNormal.vY
                   + igi2_frame.tIntersection.tNormal.vZ * igi2_frame.tIntersection.tNormal.vZ);
              igi2_frame.tIntersection.tNormal.vX = igi2_frame.tIntersection.tNormal.vX * (1.0 / v9);
              igi2_frame.tIntersection.tNormal.vY = igi2_frame.tIntersection.tNormal.vY * (1.0 / v9);
              igi2_frame.tIntersection.tNormal.vZ = igi2_frame.tIntersection.tNormal.vZ * (1.0 / v9);
            }
            GameFunctions_CreateOrientationFromDirection(&igi2_frame.tOrientation, &igi2_frame.tIntersection.tNormal);
            qmemcpy(&v8->tPos, &igi2_frame.tIntersection.tPos, sizeof(v8->tPos));
            qmemcpy(&v8->tOrientation, &igi2_frame.tOrientation, sizeof(v8->tOrientation));
            qmemcpy(&v6->tBombContext.tPos, &igi2_frame.tIntersection.tPos, sizeof(v6->tBombContext.tPos));
            qmemcpy(&v6->tBombContext.tOrientation, &igi2_frame.tOrientation, sizeof(v6->tBombContext.tOrientation));
            v6->isBombOnObject = true;
          }
          v3 = igi2_frame.ptHumanShooter;
        }
        if ( v6->isBombOnObject == false )
        {
          qmemcpy(&v8->tPos, &HumanPlayer_ptQTask[1], sizeof(v8->tPos));
          qmemcpy(&v8->tOrientation, &HumanPlayer_ptQTask[3].ptPrev, sizeof(v8->tOrientation));
          qmemcpy(&v6->tBombContext.tPos, &v8->tPos, sizeof(v6->tBombContext.tPos));
          v6->tBombContext.tPos.vZ = v6->tBombContext.tPos.vZ + 614.4000244140625;
          qmemcpy(&v6->tBombContext.tOrientation, &v8->tOrientation, sizeof(v6->tBombContext.tOrientation));
          v3 = igi2_frame.ptHumanShooter;
        }
        strcpy(v6->tBombContext.zFixedModel, (char *)(*((_DWORD *)pxContext + 26) + 676));
        v6->tBombContext.vTimeBeforeArm = v8->vTimeBeforeArm;
        v6->tBombContext.vEffectiveRange = v8->vEffectiveRange;
        v6->tBombContext.vTimeBeforeExplode = (float)ServerConfig_tServerConfig.nSpawnMaxCost;
        v6->tBombContext.vExplodeRadius = v8->vExplodeRadius;
        ptHumanViewQTask = v3->ptHumanViewQTask;
        ptHumanViewQTask[16].tQTaskRefList.ptMiddle = nullptr;
        *(float *)&ptHumanViewQTask[16].tQTaskChildren.ptHead = tan(0.7853981852531433);
        *(float *)&ptHumanViewQTask[16].tQTaskRefList.ptHead = tan(0.5235987901687622);
        Human_SetEvaluateActivateTask(
          &v3->tBoneDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask,
          &v6->tEditorRigidObj.tQTask);
        v11 = igi2_frame.ptHumanPlayer;
        ptEvaluateActivateQTaskRef = igi2_frame.ptHumanPlayer->tHuman.ptEvaluateActivateQTaskRef;
        p_tState = &igi2_frame.ptHumanPlayer->tHuman.tState;
        if ( ptEvaluateActivateQTaskRef )
          igi2_frame.ptHumanPlayera = (struct HumanPlayer_t *)ptEvaluateActivateQTaskRef->pxObject;
        else
          igi2_frame.ptHumanPlayera = nullptr;
        ptActivateQTaskRef = v11->tHuman.ptActivateQTaskRef;
        if ( ptActivateQTaskRef )
        {
          QReference_Delete(ptActivateQTaskRef, &QTask_tQTaskRefPool);
          v11->tHuman.ptActivateQTaskRef = nullptr;
        }
        if ( igi2_frame.ptHumanPlayera )
          v11->tHuman.ptActivateQTaskRef = QTask_NewQTaskRef(&igi2_frame.ptHumanPlayera->tHuman.tBoneDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask);
        v11->tHuman.isLockActivate = 1;
        v11->tHuman.nActivateTime = 0;
        v15 = p_tState->apfExitState[p_tState->nState];
        if ( v15 )
          v15(p_tState, &v11->tHuman.tBoneDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask);
        apfState = p_tState->apfState;
        p_tState->nPreviousState = p_tState->nState;
        p_tState->nState = 43;
        v17 = apfState[43];
        p_tState->pfState = v17;
        v17(p_tState, &v11->tHuman.tBoneDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask);
        v18 = HumanPlayer_ptQTask;
        p_tRunRandomState = &Game_ptGame->tRunRandomState;
        igi2_frame.ptHumanShootera = (struct Human_s *)HumanPlayer_ptQTask;
        igi2_frame.ptHumanPlayerb = (struct HumanPlayer_t *)HumanPlayer_ptQTask;
        HumanPlayer_ptQTask[77].tQTaskRefList.ptTail = (struct QReference_s *)6;
        v18[87].tQTaskChildren.ptMiddle = (struct QTask_s *)1;
        RandomNumberReal32 = Random_GetRandomNumberReal32(p_tRunRandomState);
        v21 = *(float *)&v18[77].ptPrev;
        p_ptPrev = (float *)&v18[77].ptPrev;
        v23 = *(_DWORD *)&v18[32].eQTaskType;
        igi2_frame.v59 = LODWORD(v21) != 0;
        igi2_frame.eState[0] = v23 == 2 ? 76 : 83;
        if ( v23 == 2 )
        {
          HumanAnim_ClearUpperBodyAnimation(v18, 0.0);
          if ( igi2_frame.eState[0] == 77 || igi2_frame.eState[0] == 78 || igi2_frame.eState[0] == 79 )
          {
            v40 = *(float *)&igi2_frame.ptHumanPlayerb->tHuman.tBoneDynCubeObj.pcHierarchy;
            igi2_frame.tOrientation.tY.vY = *p_ptPrev;
            v41 = *(float *)&igi2_frame.ptHumanPlayerb->tHuman.ptWeaponQTask;
            igi2_frame.tOrientation.tX.vX = v40;
            LODWORD(igi2_frame.tOrientation.tY.vX) = (__int64)(RandomNumberReal32 * 0.17499999701976776 * 4800.0);
            igi2_frame.tOrientation.tX.vY = v41;
            igi2_frame.tOrientation.tX.vZ = 0.0;
            igi2_frame.tOrientation.tZ.vX = 0.0;
            v42 = *(_DWORD *)(LODWORD(v41) + 44);
            if ( v42 )
              v43 = *(_DWORD *)(v42 + 16);
            else
              v43 = 0;
            v44 = *(_DWORD *)(LODWORD(v41) + 44);
            pfHandler = (void (__cdecl *)(int, struct real32x9_t *))QTask_aatQTaskFinalEvent[WeaponType_eGetAnimQTaskEvent][*(unsigned __int16 *)(v43 + 36)].pfHandler;
            if ( v44 )
              v46 = *(_DWORD *)(v44 + 16);
            else
              v46 = 0;
            pfHandler(v46, &igi2_frame.tOrientation);
            if ( LODWORD(igi2_frame.tOrientation.tZ.vX) )
            {
              HumanAnim_SetAnimation(
                &igi2_frame.ptHumanShootera->tBoneDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask,
                (struct AnimHeader_s *)LODWORD(igi2_frame.tOrientation.tZ.vX),
                0,
                0.0);
              ptActiveMainController = igi2_frame.ptHumanPlayerb->tHuman.tHumanAnim.ptActiveMainController;
              *(_QWORD *)igi2_frame.eState = (__int64)((double)AnimController_nTicksPerFrame * igi2_frame.tOrientation.tZ.vY);
              ptActiveMainController->nTimeStep = igi2_frame.eState[0];
            }
            goto LABEL_66;
          }
          if ( igi2_frame.eState[0] == 90 || igi2_frame.eState[0] == 91 )
          {
            v31 = *p_ptPrev;
            v32 = *(float *)&igi2_frame.ptHumanPlayerb->tHuman.tBoneDynCubeObj.pcHierarchy;
            LODWORD(igi2_frame.tOrientation.tY.vX) = (__int64)(RandomNumberReal32 * 0.17499999701976776 * 4800.0);
            v33 = *(float *)&igi2_frame.ptHumanPlayerb->tHuman.ptWeaponQTask;
            igi2_frame.tOrientation.tX.vX = v32;
            igi2_frame.tOrientation.tY.vY = v31;
            igi2_frame.tOrientation.tX.vY = v33;
            igi2_frame.tOrientation.tX.vZ = 0.0;
            igi2_frame.tOrientation.tZ.vX = 0.0;
            v34 = *(_DWORD *)(LODWORD(v33) + 44);
            if ( v34 )
              v35 = *(_DWORD *)(v34 + 16);
            else
              v35 = 0;
            v36 = *(_DWORD *)(LODWORD(v33) + 44);
            v37 = (void (__cdecl *)(int, struct real32x9_t *))QTask_aatQTaskFinalEvent[WeaponType_eGetAnimQTaskEvent][*(unsigned __int16 *)(v35 + 36)].pfHandler;
            if ( v36 )
              v38 = *(_DWORD *)(v36 + 16);
            else
              v38 = 0;
            v37(v38, &igi2_frame.tOrientation);
            if ( !LODWORD(igi2_frame.tOrientation.tZ.vX) )
            {
LABEL_41:
              HumanAnim_ClearUpperBodyAnimation(
                &igi2_frame.ptHumanShootera->tBoneDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask,
                0.0);
              goto LABEL_66;
            }
            HumanAnim_SetUpperBodyAnimationFromHeader(
              &igi2_frame.ptHumanShootera->tBoneDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask,
              (struct AnimHeader_s *)LODWORD(igi2_frame.tOrientation.tZ.vX),
              0,
              0.0);
            ptActiveUpperBodyController = igi2_frame.ptHumanPlayerb->tHuman.tHumanAnim.ptActiveUpperBodyController;
            *(_QWORD *)igi2_frame.eState = (__int64)((double)AnimController_nTicksPerFrame * igi2_frame.tOrientation.tZ.vY);
            ptActiveUpperBodyController->nTimeStep = igi2_frame.eState[0];
          }
          else
          {
            HumanAnim_SetAnimationAndTimeFromState(
              &igi2_frame.ptHumanShootera->tBoneDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask,
              igi2_frame.eState[0],
              0,
              0.0);
            v6 = igi2_frame.ptC4BombArea;
          }
        }
        else
        {
          if ( igi2_frame.v59 )
          {
            v24 = *(float *)&v18[7].tQTaskRefList.ptTail;
            v25 = *(float *)&v18[33].ptNext;
            igi2_frame.tOrientation.tX.vX = v24;
            LODWORD(igi2_frame.tOrientation.tY.vX) = 17;
            igi2_frame.tOrientation.tY.vY = v21;
            igi2_frame.tOrientation.tX.vY = v25;
            igi2_frame.tOrientation.tX.vZ = 0.0;
            igi2_frame.tOrientation.tZ.vX = 0.0;
            v26 = *(_DWORD *)(LODWORD(v25) + 44);
            if ( v26 )
              v27 = *(_DWORD *)(v26 + 16);
            else
              v27 = 0;
            v28 = *(_DWORD *)(LODWORD(v25) + 44);
            v29 = (void (__cdecl *)(int, struct real32x9_t *))QTask_aatQTaskFinalEvent[WeaponType_eGetAnimQTaskEvent][*(unsigned __int16 *)(v27 + 36)].pfHandler;
            if ( v28 )
              v30 = *(_DWORD *)(v28 + 16);
            else
              v30 = 0;
            v29(v30, &igi2_frame.tOrientation);
            if ( LODWORD(igi2_frame.tOrientation.tZ.vX) )
            {
              igi2_frame.vX = igi2_frame.tOrientation.tZ.vX;
              igi2_frame.ptHumanPlayerb->tHuman.tHumanAnim.iStateLastUsedToSetUpperBodyAnimation = 83;
              HumanAnim_SetUpperBodyAnimationFromHeader(
                &igi2_frame.ptHumanShootera->tBoneDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask,
                (struct AnimHeader_s *)LODWORD(igi2_frame.vX),
                0,
                0.0);
              goto LABEL_66;
            }
            goto LABEL_41;
          }
          HumanAnim_SetUpperBodyAnimationAndTimeFromState(v18, v23 == 2 ? 76 : 83, 0, 0.0);
          v6 = igi2_frame.ptC4BombArea;
        }
LABEL_66:
        HumanPlayer_SetWeaponTypeAnim(
          &igi2_frame.ptHumanShootera->tBoneDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask,
          WEAPONTYPE_GETANIMTYPE_1STFIRE,
          (__int64)(RandomNumberReal32 * 0.17499999701976776 * 4800.0),
          false);
        if ( v6->ptBomb )
        {
          *((_DWORD *)pxContext + 28) = 1;
          v48 = *(struct QTask_s **)pxContext;
          *((_DWORD *)pxContext + 29) = (__int64)(60.0 / (double)igi2_frame.ptC4BombParameters->nRoundsPerMinute * 30.0);
          Weapon_PlaySound(v48, 0, igi2_frame.ptC4BombParameters->zFireSound, false);
        }
      }
    }
  }
}

// source: j/0/weapons/c4bomb.c:1061  [size]
void __cdecl C4BombArea_ActivateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ;
}

// source: j/0/weapons/c4bomb.c:1078  [size]
void __cdecl RemoteBomb_CreateWeaponTypeParametersHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *((_DWORD *)pxContext + 2) = QTask_NewFn(*((struct QTask_s **)pxContext + 1), RemoteBomb_eQTaskType, nullptr);
}

// source: j/0/weapons/c4bomb.c:1097  [anchor-caller]
void __cdecl RemoteBomb_WeaponFireHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { float vTimeBeforeArm; };
    struct { char igi2_o1[32]; int isDerivedFormHuman; };
    struct { char igi2_o2[36]; struct C4Bomb_t *ptC4BombParameters; };
    struct { char igi2_o3[48]; struct WeaponCollisionEvaluateContext_t tWeaponCollisionEvaluateContext; };
    struct { char igi2_o4[68]; struct real64x3_t tPos0; };
    struct { char igi2_o5[92]; struct real64x3_t tPos1; };
    struct { char igi2_o6[116]; struct QIntersection_s tIntersection; };
    struct { char igi2_o7[236]; struct real32x9_t tOrientation; };
    char igi2_extent[276];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct C4Bomb_t *v2; // eax
  double v3; // st7
  double v4; // st6
  struct QTask_s *v5; // eax
  double v6; // st6
  int v7; // esi
  struct QObj_s *ptHitObj; // edx
  unsigned __int16 v9; // cx
  struct QTask_s *ptParent; // eax
  unsigned __int16 eQTaskType; // ax
  BOOL v12; // eax
  long double v13; // st7

  v2 = *((struct C4Bomb_t **)pxContext + 25);
  v3 = *((float *)pxContext + 14);
  v4 = *((float *)pxContext + 11) * 6144.0;
  igi2_frame.tWeaponCollisionEvaluateContext.ptIgnore1QTask = *((struct QTask_s **)pxContext + 17);
  igi2_frame.ptC4BombParameters = v2;
  v5 = *((struct QTask_s **)pxContext + 1);
  *(float *)&igi2_frame.tWeaponCollisionEvaluateContext.tCollisionEvaluateContext.isEvaluate = v4;
  v6 = *(float *)&igi2_frame.tWeaponCollisionEvaluateContext.ptIgnore1QTask * 6144.0;
  qmemcpy(&igi2_frame.tPos0, (char *)pxContext + 16, sizeof(igi2_frame.tPos0));
  igi2_frame.tPos1.vX = *(float *)&igi2_frame.tWeaponCollisionEvaluateContext.tCollisionEvaluateContext.isEvaluate + igi2_frame.tPos0.vX;
  igi2_frame.tPos1.vY = v3 * 6144.0 + igi2_frame.tPos0.vY;
  igi2_frame.tWeaponCollisionEvaluateContext.tCollisionEvaluateContext.ptQTask = v5;
  igi2_frame.tWeaponCollisionEvaluateContext.ptIgnore1QTask = v5;
  igi2_frame.tPos1.vZ = v6 + igi2_frame.tPos0.vZ;
  v7 = 1;
  igi2_frame.tWeaponCollisionEvaluateContext.ptIgnore2QTask = nullptr;
  igi2_frame.tWeaponCollisionEvaluateContext.vHitProbability = 1.0;
  World_TraceLines(
    Game_ptGame->ptWorld,
    &igi2_frame.tIntersection,
    &igi2_frame.tPos0,
    &igi2_frame.tPos1,
    1,
    GameFunctions_eWeaponCollisionEvaluateQTaskEvent,
    &igi2_frame.tWeaponCollisionEvaluateContext.tCollisionEvaluateContext,
    0xFFFFFFFF);
  if ( igi2_frame.tIntersection.isHit )
  {
    ptHitObj = igi2_frame.tIntersection.ptHitObj;
    v9 = Human_eQTaskType;
    if ( !igi2_frame.tIntersection.ptHitObj
      || (igi2_frame.isDerivedFormHuman = 1,
          QTask_IsQTaskTypeDerived(igi2_frame.tIntersection.ptHitObj->tQTask.eQTaskType, Human_eQTaskType) == false) )
    {
      igi2_frame.isDerivedFormHuman = 0;
    }
    if ( !ptHitObj
      || (ptParent = ptHitObj->tQTask.ptParent) == nullptr
      || QTask_IsQTaskTypeDerived(ptParent->eQTaskType, v9) == false )
    {
      v7 = 0;
    }
    v12 = false;
    if ( ptHitObj )
    {
      eQTaskType = ptHitObj->tQTask.eQTaskType;
      if ( eQTaskType == Glass_eQTaskType
        || eQTaskType == Door_eQTaskType
        || QTask_IsQTaskTypeDerived(eQTaskType, Vehicle_eQTaskType) )
      {
        v12 = true;
      }
    }
    if ( !igi2_frame.isDerivedFormHuman && !v7 && !v12 && igi2_frame.ptC4BombParameters->isArmed )
    {
      if ( igi2_frame.tIntersection.tNormal.vX != 0.0 || igi2_frame.tIntersection.tNormal.vY != 0.0 || igi2_frame.tIntersection.tNormal.vZ != 0.0 )
      {
        v13 = 1.0
            / sqrt(
                igi2_frame.tIntersection.tNormal.vX * igi2_frame.tIntersection.tNormal.vX
              + igi2_frame.tIntersection.tNormal.vY * igi2_frame.tIntersection.tNormal.vY
              + igi2_frame.tIntersection.tNormal.vZ * igi2_frame.tIntersection.tNormal.vZ);
        igi2_frame.tIntersection.tNormal.vX = igi2_frame.tIntersection.tNormal.vX * v13;
        igi2_frame.tIntersection.tNormal.vY = igi2_frame.tIntersection.tNormal.vY * v13;
        igi2_frame.tIntersection.tNormal.vZ = igi2_frame.tIntersection.tNormal.vZ * v13;
      }
      GameFunctions_CreateOrientationFromDirection(&igi2_frame.tOrientation, &igi2_frame.tIntersection.tNormal);
      igi2_frame.vTimeBeforeArm = (float)ServerConfig_tServerConfig.nSpawnMaxCost;
      Bomb_New(
        Level_ptDynamicQTask,
        &igi2_frame.tIntersection.tPos,
        &igi2_frame.tOrientation,
        (char *)(*((_DWORD *)pxContext + 26) + 676),
        igi2_frame.ptC4BombParameters->vTimeBeforeArm,
        igi2_frame.vTimeBeforeArm,
        igi2_frame.ptC4BombParameters->vEffectiveRange,
        igi2_frame.ptC4BombParameters->vExplodeRadius,
        -1.0,
        true);
      *((_DWORD *)pxContext + 28) = 1;
      *((_DWORD *)pxContext + 29) = (__int64)(60.0 / (double)igi2_frame.ptC4BombParameters->nRoundsPerMinute * 30.0);
    }
  }
  *((_DWORD *)pxContext + 32) = 0;
  *((_DWORD *)pxContext + 33) = 0;
}

// source: j/0/weapons/c4bomb.c:1211  [anchor-refs]
void __cdecl C4BombArea_RegisterScriptSymbolsHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { char zName[64]; };
    struct { char igi2_o1[64]; char zTemp[128]; };
    char igi2_extent[192];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)

  if ( !ptQTask[10].tQTaskRefList.ptTail )
  {
    ptQTask[10].tQTaskRefList.ptTail = (struct QReference_s *)1;
    Level_GetUniqueQTaskNameFromTask(igi2_frame.zName, ptQTask);
    sprintf(igi2_frame.zTemp, "%s.isInside", igi2_frame.zName);
    Symbol_Register(
      igi2_frame.zTemp,
      (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_Bool,
      &ptQTask[10].tQTaskChildren,
      4,
      QSCRIPT_SYMBOLCLASS_VARIABLE,
      QSCRIPT_SYMBOLTYPE_INT,
      QSCRIPT_SYMBOLLIFESPAN_FINITE);
    sprintf(igi2_frame.zTemp, "%s.isExploded", igi2_frame.zName);
    Symbol_Register(
      igi2_frame.zTemp,
      (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_Bool,
      &ptQTask[10].tQTaskChildren.ptTail,
      4,
      QSCRIPT_SYMBOLCLASS_VARIABLE,
      QSCRIPT_SYMBOLTYPE_INT,
      QSCRIPT_SYMBOLLIFESPAN_FINITE);
    sprintf(igi2_frame.zTemp, "%s.isDisarmed", igi2_frame.zName);
    Symbol_Register(
      igi2_frame.zTemp,
      (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_Bool,
      &ptQTask[10].tQTaskRefList,
      4,
      QSCRIPT_SYMBOLCLASS_VARIABLE,
      QSCRIPT_SYMBOLTYPE_INT,
      QSCRIPT_SYMBOLLIFESPAN_FINITE);
  }
}

// source: j/0/weapons/c4bomb.c:1245  [anchor-mhash]
void __cdecl C4BombArea_RemoveScriptSymbolsHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { char zName[64]; };
    struct { char igi2_o1[64]; char zTemp[128]; };
    char igi2_extent[192];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)

  if ( ptQTask[10].tQTaskRefList.ptTail )
  {
    ptQTask[10].tQTaskRefList.ptTail = nullptr;
    Level_GetUniqueQTaskNameFromTask(igi2_frame.zName, ptQTask);
    sprintf(igi2_frame.zTemp, "%s.isInside", igi2_frame.zName);
    Symbol_Remove(igi2_frame.zTemp);
    sprintf(igi2_frame.zTemp, "%s.isExploded", igi2_frame.zName);
    Symbol_Remove(igi2_frame.zTemp);
    sprintf(igi2_frame.zTemp, "%s.isDisarmed", igi2_frame.zName);
    Symbol_Remove(igi2_frame.zTemp);
  }
}

// source: j/0/weapons/c4bomb.c:1281  [size]
struct QTask_s *__cdecl C4BombArea_GetActivatePosAndOrientation(
        struct QTask_s *ptQTask,
        struct real64x3_t *ptPos,
        struct real32x9_t *ptOrientation)
{
  qmemcpy(ptPos, &ptQTask[6], sizeof(struct real64x3_t));
  qmemcpy(ptOrientation, &ptQTask[6].tQTaskRefList.ptMiddle, sizeof(struct real32x9_t));
  return ptQTask;
}

// source: j/0/weapons/c4bomb.c:1298  [anchor-strings]
struct QTask_s *__cdecl C4BombArea_PlaceBomb(struct QTask_s *ptQTask, void *pxContext)
{
  struct Node_s *ptHead; // eax
  struct Node_s *ptNext; // edx
  struct QTask_s *v5; // ebx
  struct QTask_s *result; // eax
  struct QTask_s *v7; // eax
  struct QTask_s *v8; // eax
  struct QTask_s *v9; // [esp+Ch] [ebp-4h]

  ptHead = C4BombArea_tC4BombAreaList.ptHead;
  ptNext = C4BombArea_tC4BombAreaList.ptHead->ptNext;
  if ( C4BombArea_tC4BombAreaList.ptHead->ptNext )
  {
    do
    {
      v5 = (struct QTask_s *)ptHead[1].ptNext;
      if ( C4BombArea_IsInsideArea(v5, (struct real64x3_t *)&ptQTask[1].tQTaskChildren.ptTail) )
        break;
      ptHead = ptNext;
      ptNext = ptNext->ptNext;
    }
    while ( ptNext );
  }
  else
  {
    v5 = v9;
  }
  result = v5[1].ptNext;
  if ( !result )
  {
    v7 = Bomb_New(
           Level_ptDynamicQTask,
           (struct real64x3_t *)&ptQTask[1].tQTaskChildren.ptTail,
           (struct real32x9_t *)&ptQTask[2],
           (char *)&ptQTask->tQTaskRefList,
           *(float *)&ptQTask[3].ptNext,
           *(float *)&ptQTask[3].ptPrev,
           *(float *)&ptQTask[3].tQTaskChildren.ptHead,
           *(float *)&ptQTask[3].tQTaskChildren.ptMiddle,
           -1.0,
           false);
    v5[1].ptNext = v7;
    qmemcpy(&v5[4].tQTaskRefList.ptMiddle, ptQTask, 0x88u);
    v8 = SoundSys_NewSoundFn(v7, "tba_c4seconds");
    result = (struct QTask_s *)QTask_NewQTaskRef(v8);
    v5[1].ptNext[16].tQTaskChildren.ptTail = result;
  }
  return result;
}

// source: j/0/weapons/c4bomb.c:1351  [size]
struct Bomb_t *__cdecl C4BombArea_GetBomb(struct QTask_s *ptQTask)
{
  return (struct Bomb_t *)ptQTask[1].ptNext;
}

// source: j/0/weapons/c4bomb.c:1367  [anchor-mhash]
struct QTask_s *__cdecl C4BombArea_DisarmBomb(struct QTask_s *ptQTask)
{
  struct QTask_s *ptNext; // ecx
  struct QTask_s *result; // eax

  ptNext = ptQTask[1].ptNext;
  ptQTask[10].tQTaskRefList.ptHead = (struct QReference_s *)1;
  LOBYTE(ptNext[16].tQTaskChildren.ptMiddle) = 0;
  ptQTask[1].ptNext[15].ptParent = (struct QTask_s *)((char *)&MTP_atLODVirModel[11].atBoneVertexRefs[28].atVertexRefs[780].iVertex
                                                    + 3);
  QTask_DeleteQTaskAndQTaskRefSafe((struct QReference_s **)&ptQTask[1].ptNext[16].tQTaskChildren.ptTail);
  return result;
}

// source: j/0/weapons/c4bomb.c:1389  [size]
void *__cdecl C4BombArea_GetBombContext(struct QTask_s *ptQTask)
{
  return &ptQTask[4].tQTaskRefList.ptMiddle;
}

// source: j/0/weapons/c4bomb.c:1405  [anchor-mhash]
enum bool __cdecl C4BombArea_IsArmed(struct QTask_s *ptQTask)
{
  return ptQTask[1].ptNext && !ptQTask[10].tQTaskRefList.ptHead && !ptQTask[10].tQTaskChildren.ptTail;
}

// source: j/0/weapons/c4bomb.c:1428  [size]
struct QTask_s *__cdecl C4BombArea_Lock(struct QTask_s *ptQTask)
{
  ptQTask[10].ptNext = (struct QTask_s *)1;
  return ptQTask;
}

// source: j/0/weapons/c4bomb.c:1446  [size]
struct QTask_s *__cdecl C4BombArea_UnLock(struct QTask_s *ptQTask)
{
  if ( !ptQTask[1].ptNext )
    ptQTask[10].ptNext = nullptr;
  return ptQTask;
}

// source: j/0/weapons/c4bomb.c:1468  [size]
struct QTask_s *__cdecl C4Bomb_GetQTask()
{
  return C4Bomb_ptQTask;
}

// source: j/0/weapons/c4bomb.c:1481  [anchor-mhash]
void __cdecl C4Bomb_SetPos(struct real64x3_t *ptPos)
{
  if ( C4Bomb_ptQTask )
    qmemcpy(&C4Bomb_ptQTask[1].tQTaskChildren, ptPos, 0x18u);
}

// source: j/0/weapons/c4bomb.c:1503  [size]
void __cdecl C4Bomb_EnableDrawInMapComputer(enum bool isEnable)
{
  if ( C4Bomb_ptQTask )
    C4Bomb_ptQTask[3].tQTaskRefList.ptHead = (struct QReference_s *)isEnable;
}

// source: j/0/weapons/c4bomb.c:1522  [size]
enum bool __cdecl C4BombArea_IsBombOnObject(struct QTask_s *ptQTask)
{
  return (enum bool)ptQTask[10].tQTaskRefList.ptMiddle;
}

// source: j/0/weapons/c4bomb.c:1538  [size~]
int C4BombArea_SoundUpdateParameterListHandler()
{
  struct Node_s *ptHead; // eax
  struct Node_s *ptNext; // ecx
  struct Node_s *v2; // eax

  ptHead = C4BombArea_tC4BombAreaList.ptHead;
  ptNext = C4BombArea_tC4BombAreaList.ptHead->ptNext;
  if ( !C4BombArea_tC4BombAreaList.ptHead->ptNext )
    return 0;
  while ( 1 )
  {
    v2 = ptHead[1].ptNext;
    if ( v2[5].ptNext )
    {
      if ( !v2[52].ptPrev && !v2[52].ptNext )
        break;
    }
    if ( v2[52].ptNext || v2[52].ptPrev )
      break;
    ptHead = ptNext;
    ptNext = ptNext->ptNext;
    if ( !ptNext )
      return 0;
  }
  return 1;
}

void __cdecl sub_4F9AA0(struct QTask_s *a1, _DWORD *a2)
{
  struct QTask_s *ptNext; // eax

  ptNext = a1[1].ptNext;
  if ( ptNext )
  {
    *a2 = ptNext + 8;
    a2[1] = (char *)a1[1].ptNext + 344;
  }
  a2[2] = 0;
}

// source: j/0/weapons/c4bomb.c:1562  [anchor-mhash]
void __cdecl C4Bomb_Open()
{
  unsigned __int16 v0; // ax
  __int16 v1; // bp
  unsigned __int16 v2; // di
  unsigned __int16 v3; // bx
  unsigned __int16 v4; // si
  __int16 v5; // ax
  __int16 v6; // ax
  struct ParameterList_s *v7; // eax
  int v8; // edx
  struct ParameterList_s *v9; // eax
  int v10; // edx

  C4Bomb_eQTaskType = QTask_NewQTaskType("C4Bomb", 240, FireType_eQTaskType, 0, 0);
  C4BombArea_eQTaskType = QTask_NewQTaskType("C4BombArea", 440, EditorRigidObj_eQTaskType, 0, 0);
  v0 = QTask_NewQTaskType("RemoteBomb", 240, C4Bomb_eQTaskType, 0, 0);
  v1 = Level_eAllowSaveQTaskEvent;
  v2 = C4Bomb_eQTaskType;
  v3 = v0;
  RemoteBomb_eQTaskType = v0;
  QTask_LinkQTaskEventHandlerFn(
    C4Bomb_eQTaskType,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveHandler);
  v4 = C4BombArea_eQTaskType;
  QTask_LinkQTaskEventHandlerFn(
    C4BombArea_eQTaskType,
    v1,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveHandler);
  QTask_LinkQTaskEventHandlerFn(v3, v1, (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveHandler);
  QTask_LinkQTaskEventHandlerFn(v2, 0, (void (__cdecl *)(struct QTask_s *, void *))sub_4F81C0);
  QTask_LinkQTaskEventHandlerNoContextFn(v2, 2, (void (__cdecl *)(struct QTask_s *))sub_4F8250);
  QTask_LinkQTaskEventHandlerFn(
    v2,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))C4Bomb_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(v2, WeaponType_eCreateParametersQTaskEvent, C4Bomb_CreateWeaponTypeParametersHandler);
  QTask_LinkQTaskEventHandlerFn(v2, WeaponType_eGetAnimQTaskEvent, C4Bomb_GetAnimHandler);
  QTask_LinkQTaskEventHandlerFn(v2, WeaponType_eGetAmmoInfoQTaskEvent, C4Bomb_GetAmmoInfoHandler);
  QTask_LinkQTaskEventHandlerFn(v2, Weapon_eFireQTaskEvent, C4Bomb_WeaponFireHandler);
  v5 = ComputerObject_eDrawComputerObjectQTaskEvent;
  if ( ComputerObject_eDrawComputerObjectQTaskEvent == 512 )
  {
    v5 = QTask_NewQTaskEventFn(0x200u, "DrawComputerObject");
    v4 = C4BombArea_eQTaskType;
    v3 = RemoteBomb_eQTaskType;
    v2 = C4Bomb_eQTaskType;
    ComputerObject_eDrawComputerObjectQTaskEvent = v5;
  }
  QTask_LinkQTaskEventHandlerFn(v2, v5, (void (__cdecl *)(struct QTask_s *, void *))C4Bomb_DrawComputerObjectHandler);
  QTask_LinkQTaskEventHandlerFn(
    v3,
    WeaponType_eCreateParametersQTaskEvent,
    RemoteBomb_CreateWeaponTypeParametersHandler);
  QTask_LinkQTaskEventHandlerFn(v3, Weapon_eFireQTaskEvent, RemoteBomb_WeaponFireHandler);
  QTask_LinkQTaskEventHandlerFn(v4, 0, C4BombArea_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v4, 2, C4BombArea_DeleteHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v4, 1, C4BombArea_RunHandler);
  QTask_LinkQTaskEventHandlerFn(
    v4,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))C4BombArea_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(v4, ParameterList_eUpdateInternalDataQTaskEvent, C4BombArea_UpdateInternalDataHandler);
  QTask_LinkQTaskEventHandlerFn(v4, ActionMenuScreen_eDrawActionItemQTaskEvent, C4BombArea_DrawActionItemHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(
    v4,
    Level_eRegisterLevelScriptSymbolsEvent,
    C4BombArea_RegisterScriptSymbolsHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(
    v4,
    Level_eRemoveLevelScriptSymbolsEvent,
    C4BombArea_RemoveScriptSymbolsHandler);
  QTask_LinkQTaskEventHandlerFn(
    v4,
    GameFunctions_eActivateQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))C4BombArea_ActivateHandler);
  v6 = SoundSys_eUpdateParameterListQTaskEvent;
  if ( SoundSys_eUpdateParameterListQTaskEvent == 512 )
  {
    v6 = QTask_NewQTaskEventFn(0, (char *)&g_zFileName.nRealFadeCount);
    v4 = C4BombArea_eQTaskType;
    SoundSys_eUpdateParameterListQTaskEvent = v6;
  }
  QTask_LinkQTaskEventHandlerFn(v4, v6, (void (__cdecl *)(struct QTask_s *, void *))sub_4F9AA0);
  v7 = (struct ParameterList_s *)Mem_AllocFn(192, 4);
  v7->ptParameterListItem = (struct ParameterListItem_s *)&v7[1];
  v8 = ParameterEnumList_eParameterTypeInt32;
  v7->nParameters = 0;
  v7->nMaxParameters = 9;
  C4Bomb_ptParameterList = v7;
  ParameterList_AddParameter(v7, 0x70u, v8, "AmmoType", 7u, &AmmoType_tEnumList);
  ParameterList_AddParameter(C4Bomb_ptParameterList, 0x74u, Level_eParameterTypeInt32, "Rounds Per Minute", 7u, nullptr);
  ParameterList_AddParameter(
    C4Bomb_ptParameterList,
    0x7Cu,
    Level_eParameterTypeReal32,
    "Effective Range (meters)",
    7u,
    nullptr);
  ParameterList_AddParameter(
    C4Bomb_ptParameterList,
    0x80u,
    Level_eParameterTypeReal32,
    "Time before arming (seconds)",
    7u,
    nullptr);
  ParameterList_AddParameter(
    C4Bomb_ptParameterList,
    0x84u,
    Level_eParameterTypeReal32,
    "Explosion radius (meters)",
    7u,
    nullptr);
  ParameterList_AddParameter(C4Bomb_ptParameterList, 0x90u, Level_eParameterTypeString32, "1st Fire Anim", 7u, nullptr);
  ParameterList_AddParameter(C4Bomb_ptParameterList, 0xB0u, Level_eParameterTypeString32, "3rd Fire Anim", 7u, nullptr);
  ParameterList_AddParameter(C4Bomb_ptParameterList, 0xD0u, Level_eParameterTypeString32, "Fire Sound", 7u, nullptr);
  v9 = (struct ParameterList_s *)Mem_AllocFn(92, 4);
  v10 = Level_eParameterTypeObjectPos;
  v9->ptParameterListItem = (struct ParameterListItem_s *)&v9[1];
  v9->nParameters = 0;
  v9->nMaxParameters = 4;
  C4BombArea_ptParameterList = v9;
  ParameterList_AddParameter(v9, 0x60u, v10, "Position", 7u, nullptr);
  ParameterList_AddParameter(
    C4BombArea_ptParameterList,
    0x90u,
    Level_eParameterTypeReal32x9,
    "Orientation",
    7u,
    nullptr);
  ParameterList_AddParameter(C4BombArea_ptParameterList, 0x84u, Level_eParameterTypeReal32x3, "Dimensions", 7u, nullptr);
  ParameterList_AddParameter(
    C4BombArea_ptParameterList,
    0x140u,
    Level_eParameterTypeVarString,
    "Active Expression",
    7u,
    nullptr);
  Symbol_Register(
    "TASKTYPE_C4BOMB",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)C4Bomb_eQTaskType,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "TASKTYPE_C4BOMBAREA",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)C4BombArea_eQTaskType,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "TASKTYPE_REMOTEBOME",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)RemoteBomb_eQTaskType,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  C4BombArea_tC4BombAreaList.ptHead = (struct Node_s *)&C4BombArea_tC4BombAreaList.ptMiddle;
  C4BombArea_tC4BombAreaList.ptTail = (struct Node_s *)&C4BombArea_tC4BombAreaList;
  C4BombArea_tC4BombAreaList.ptMiddle = nullptr;
}

// source: j/0/weapons/c4bomb.c:1686  [size]
void __cdecl C4Bomb_Close()
{
  int v0; // esi
  int v1; // esi

  if ( C4Bomb_ptParameterList )
  {
    v0 = *(_DWORD *)((unsigned int)&C4Bomb_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
  if ( C4BombArea_ptParameterList )
  {
    v1 = *(_DWORD *)((unsigned int)&C4BombArea_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v1);
    memset(*(void **)(v1 + 8), 0xCDu, *(_DWORD *)(v1 + 16));
    free((void *)v1);
  }
  QTask_DeleteQTaskType(RemoteBomb_eQTaskType);
  QTask_DeleteQTaskType(C4BombArea_eQTaskType);
  QTask_DeleteQTaskType(C4Bomb_eQTaskType);
}

// source: j/0/weapons/c4bomb.c:1706  [size]
unsigned __int16 __cdecl C4BombArea_GetQTaskType()
{
  return C4BombArea_eQTaskType;
}
