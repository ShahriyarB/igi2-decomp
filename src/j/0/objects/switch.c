/* j/0/objects/switch.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/objects/switch.c:133  [anchor-callee]
enum bool __cdecl Switch_SetModel(
        struct Switch_t *ptSwitch,
        enum bool isOn,
        enum bool isLastOn,
        enum bool isPressed,
        enum bool isLastPressed,
        enum bool isDestroyed,
        enum bool isLastDestroyed)
{
  int v7; // edi
  struct LODVirModel_s *LODVirModelExistsFn; // eax

  if ( isOn != isLastOn || isPressed != isLastPressed || isDestroyed != isLastDestroyed )
  {
    if ( isDestroyed )
    {
      v7 = 4;
    }
    else if ( isOn )
    {
      v7 = isPressed != false;
    }
    else
    {
      v7 = (isPressed != false) + 2;
    }
    LODVirModelExistsFn = MTP_GetLODVirModelExistsFn(ptSwitch->azModel[v7]);
    if ( LODVirModelExistsFn != ptSwitch->tSectorInteriorObject.tRigidDynCubeObj.tModelObj.ptLODVirModel )
    {
      ModelObj_SetLODVirModel(
        &ptSwitch->tSectorInteriorObject.tRigidDynCubeObj.tModelObj,
        LODVirModelExistsFn,
        false);
      ptSwitch->tSectorInteriorObject.tRigidDynCubeObj.aptLightmapVirModel[1] = nullptr;
      ptSwitch->tSectorInteriorObject.tRigidDynCubeObj.aptLightmapVirModel[2] = nullptr;
      ptSwitch->tSectorInteriorObject.tRigidDynCubeObj.aptLightmapVirModel[3] = nullptr;
      ptSwitch->tSectorInteriorObject.tRigidDynCubeObj.aptLightmapVirModel[4] = nullptr;
      ptSwitch->tSectorInteriorObject.tRigidDynCubeObj.aptLightmapVirModel[5] = nullptr;
    }
    ptSwitch->tSectorInteriorObject.tRigidDynCubeObj.aptLightmapVirModel[1] = ptSwitch->aaptLightmapVirModel[v7][0];
    ptSwitch->tSectorInteriorObject.tRigidDynCubeObj.aptLightmapVirModel[2] = ptSwitch->aaptLightmapVirModel[v7][1];
    ptSwitch->tSectorInteriorObject.tRigidDynCubeObj.aptLightmapVirModel[3] = ptSwitch->aaptLightmapVirModel[v7][2];
    ptSwitch->tSectorInteriorObject.tRigidDynCubeObj.aptLightmapVirModel[4] = ptSwitch->aaptLightmapVirModel[v7][3];
    ptSwitch->tSectorInteriorObject.tRigidDynCubeObj.aptLightmapVirModel[5] = ptSwitch->aaptLightmapVirModel[v7][4];
    return 5 * v7;
  }
  return isOn;
}

// source: j/0/objects/switch.c:195  [size]
void __cdecl Switch_GetSerializeParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = Switch_ptSerializeParameterList;
}

// source: j/0/objects/switch.c:211  [anchor-mhash]
void __cdecl Switch_DeSerializeHandler(struct QTask_s *ptQTask, void *pxContext)
{
  Serialize_DeSerializeHandler(ptQTask, pxContext);
  Switch_SetModel(
    (struct Switch_t *)ptQTask,
    (enum bool)SLOBYTE(ptQTask[14].tQTaskRefList.ptHead),
    (enum bool)(LOBYTE(ptQTask[14].tQTaskRefList.ptHead) == 0),
    (enum bool)SLOBYTE(ptQTask[14].tQTaskRefList.ptMiddle),
    false,
    (enum bool)SBYTE2(ptQTask[14].tQTaskRefList.ptHead),
    false);
}

// source: j/0/objects/switch.c:228  [anchor-mhash]
void __cdecl Switch_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { float ptDynCubeObj; };
    struct { char igi2_o1[24]; struct real64x3_t ptPos; };
    char igi2_extent[52];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  double v2; // st7
  double v3; // st7
  int *v4; // eax
  int v5; // eax
  double v6; // st6
  struct QReference_s **p_ptMiddle; // eax
  int v8; // ecx
  __int16 v9; // cx
  struct QTask_s *v10; // eax

  memset(&igi2_frame.ptPos, 0, sizeof(igi2_frame.ptPos));
  QTaskList_Register(GameFunctions_ptActivateQTaskList, (struct QTaskList_s *)ptQTask);
  ModelObj_Init((struct ModelObj_s *)ptQTask, World_ptActiveWorld, nullptr);
  ptQTask[7].tQTaskChildren.ptHead = nullptr;
  ptQTask[7].tQTaskChildren.ptMiddle = (struct QTask_s *)2;
  ptQTask[7].tQTaskRefList.ptHead = nullptr;
  ptQTask[7].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[7].tQTaskRefList.ptTail = nullptr;
  ptQTask[7].ptParent = nullptr;
  *(_DWORD *)&ptQTask[7].eQTaskType = 0;
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
  igi2_frame.ptDynCubeObj = v3 * v6;
  World_RegisterDynCubeObjFirstTimeRadius(
    World_ptActiveWorld,
    (struct DynCubeObj_s *)ptQTask,
    &igi2_frame.ptPos,
    igi2_frame.ptDynCubeObj,
    WORLD_DYNCUBETREE_CATEGORY_STATIONARY);
  if ( ptQTask[7].tQTaskChildren.ptTail )
  {
    ptQTask[2].tQTaskRefList.ptHead = nullptr;
    ptQTask[2].tQTaskRefList.ptMiddle = nullptr;
  }
  else
  {
    SectorObject_RegisterInteriorDynCubeObjSpecificSectorObject(
      (struct World_s *)ptQTask[2].ptParent,
      nullptr,
      (struct DynCubeObj_s *)ptQTask,
      (struct real64x3_t *)&ptQTask[1]);
  }
  ptQTask[3].ptPrev = (struct QTask_s *)1065353216;
  ptQTask[3].tQTaskRefList.ptHead = (struct QReference_s *)1065353216;
  *(_DWORD *)&ptQTask[3].eQTaskType = 1065353216;
  ptQTask[8].tQTaskRefList.ptMiddle = (struct QReference_s *)1065353216;
  ptQTask[9].ptNext = (struct QTask_s *)1065353216;
  ptQTask[9].tQTaskChildren.ptTail = (struct QTask_s *)1065353216;
  ptQTask[3].tQTaskChildren.ptHead = nullptr;
  ptQTask[3].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[3].tQTaskChildren.ptTail = nullptr;
  ptQTask[3].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[3].tQTaskRefList.ptTail = nullptr;
  ptQTask[3].ptParent = nullptr;
  ptQTask[4].ptNext = nullptr;
  ptQTask[8].tQTaskRefList.ptTail = nullptr;
  ptQTask[8].ptParent = nullptr;
  *(_DWORD *)&ptQTask[8].eQTaskType = 0;
  ptQTask[9].ptPrev = nullptr;
  ptQTask[9].tQTaskChildren.ptHead = nullptr;
  ptQTask[9].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[9].tQTaskRefList.ptHead = nullptr;
  p_ptMiddle = &ptQTask[9].tQTaskRefList.ptMiddle;
  v8 = 5;
  do
  {
    *(_BYTE *)p_ptMiddle = 0;
    p_ptMiddle += 4;
    --v8;
  }
  while ( v8 );
  strcpy((char *)&ptQTask[11].tQTaskRefList.ptMiddle, "$!undefined!$");
  LOBYTE(ptQTask[14].tQTaskRefList.ptHead) = 0;
  HIBYTE(ptQTask[16].eQTaskType) = 1;
  BYTE2(ptQTask[14].tQTaskRefList.ptHead) = 0;
  LOBYTE(ptQTask[14].tQTaskRefList.ptMiddle) = 0;
  BYTE1(ptQTask[14].tQTaskRefList.ptHead) = 0;
  HIBYTE(ptQTask[14].tQTaskRefList.ptHead) = 0;
  BYTE1(ptQTask[14].tQTaskRefList.ptMiddle) = 0;
  ptQTask[14].tQTaskRefList.ptTail = nullptr;
  LOBYTE(ptQTask[14].ptParent) = 0;
  LOBYTE(ptQTask[16].eQTaskType) = 1;
  ptQTask[17].tQTaskChildren.ptHead = nullptr;
  memset(&ptQTask[12], 0, 0x64u);
  v9 = Attach_eAttachEvent;
  *(_DWORD *)&ptQTask[14].eQTaskType = 0;
  ptQTask[15].ptNext = nullptr;
  ptQTask[15].ptPrev = nullptr;
  ptQTask[16].ptParent = nullptr;
  ptQTask[5].tQTaskChildren.ptTail = (struct QTask_s *)-1;
  ptQTask[5].tQTaskRefList.ptHead = nullptr;
  QTask_TriggerQTaskEventParent(ptQTask, v9, &ptQTask[5].tQTaskChildren.ptTail);
  ModelObj_CalcRelativePosAndOrientation((struct ModelObj_s *)ptQTask);
  v10 = (struct QTask_s *)Mem_AllocFn(strlen(StatusScreen_azQSpriteActivateIconPointer[4]) + 1, 4);
  ptQTask[17].ptNext = v10;
  strcpy((char *)v10, StatusScreen_azQSpriteActivateIconPointer[4]);
  ptQTask[17].ptPrev = nullptr;
}

// source: j/0/objects/switch.c:314  [anchor-mhash]
void __cdecl Switch_RunHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptHead; // ecx
  int v2; // edx
  struct QTask_s *v3; // eax
  void (__cdecl *pfHandler)(struct QTask_s *); // eax
  int v5; // edx
  struct QReference_s *ptTail; // ecx
  struct LevelFlow_s *v7; // edx
  char v8; // al
  struct QTask_s *v9; // eax

  ptHead = ptQTask->tQTaskChildren.ptHead;
  if ( ptHead->ptNext && ptHead )
  {
    v2 = QTask_nProtectedQTaskStackOffset;
    do
    {
      if ( ptHead->ptNext )
        v3 = ptHead->ptNext->ptNext != nullptr ? ptHead->ptNext : nullptr;
      else
        v3 = nullptr;
      QTask_atProtectedQTaskStack[v2].ptQTask = v3;
      pfHandler = (void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[1][ptHead->eQTaskType].pfHandler;
      v5 = v2 + 1;
      QTask_nProtectedQTaskStackOffset = v5;
      if ( pfHandler )
      {
        pfHandler(ptHead);
        v5 = QTask_nProtectedQTaskStackOffset;
      }
      ptHead = (struct QTask_s *)dword_849C7DC[v5];
      v2 = v5 - 1;
      QTask_nProtectedQTaskStackOffset = v2;
    }
    while ( ptHead );
  }
  if ( *(_DWORD *)&ptQTask[14].eQTaskType && ptQTask[15].ptNext->ptNext && ptQTask[15].ptPrev )
    HIBYTE(ptQTask[16].eQTaskType) = (__int64)Level_RunLevelExpression(
                                                (struct LevelExpression_s *)&ptQTask[14].eQTaskType,
                                                ptQTask);
  ptTail = ptQTask[14].tQTaskRefList.ptTail;
  v7 = LevelFlow_ptLevelFlow;
  HIBYTE(ptQTask[14].tQTaskRefList.ptHead) = BYTE2(ptQTask[14].tQTaskRefList.ptHead);
  v8 = (char)ptQTask[14].tQTaskRefList.ptHead;
  BYTE1(ptQTask[14].tQTaskRefList.ptHead) = v8;
  if ( v7->nTick > (int)&ptTail->ptNext + 3 )
    LOBYTE(ptQTask[14].tQTaskRefList.ptMiddle) = 0;
  if ( LOBYTE(ptQTask[14].tQTaskRefList.ptMiddle) )
  {
    if ( !BYTE1(ptQTask[14].tQTaskRefList.ptMiddle) )
    {
      LOBYTE(ptQTask[14].tQTaskRefList.ptHead) = v8 == 0;
      v9 = SoundSys_NewSoundFn(ptQTask, (char *)&ptQTask[11].tQTaskRefList.ptMiddle);
      if ( v9 )
        ((void (__cdecl *)(struct QTask_s *, struct QTask_s *))QTask_aatQTaskFinalEvent[SoundSys_eSetPositionQTaskEvent][v9->eQTaskType].pfHandler)(
          v9,
          &ptQTask[1]);
    }
  }
  Switch_SetModel(
    (struct Switch_t *)ptQTask,
    (enum bool)SLOBYTE(ptQTask[14].tQTaskRefList.ptHead),
    (enum bool)SBYTE1(ptQTask[14].tQTaskRefList.ptHead),
    (enum bool)SLOBYTE(ptQTask[14].tQTaskRefList.ptMiddle),
    (enum bool)SBYTE1(ptQTask[14].tQTaskRefList.ptMiddle),
    (enum bool)SBYTE2(ptQTask[14].tQTaskRefList.ptHead),
    (enum bool)SHIBYTE(ptQTask[14].tQTaskRefList.ptHead));
  BYTE1(ptQTask[14].tQTaskRefList.ptMiddle) = ptQTask[14].tQTaskRefList.ptMiddle;
}

// source: j/0/objects/switch.c:367  [anchor-mhash]
void __cdecl Switch_DeleteHandler(struct QTask_s *ptQTask)
{
  int v1; // eax
  struct QReference_s *v2; // ecx
  void (__cdecl *pfHandler)(struct QTask_s *); // eax
  struct QTask_s *ptNext; // eax
  int v5; // esi

  QTaskList_Remove(GameFunctions_ptActivateQTaskList, ptQTask);
  v1 = 0;
  while ( 1 )
  {
    v2 = Level_atLevelQTaskID[v1];
    if ( v2 )
    {
      if ( v2->pxObject == ptQTask )
        break;
    }
    if ( ++v1 >= 4096 )
      goto LABEL_9;
  }
  if ( v1 >= 0 )
  {
    pfHandler = (void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[Level_eRemoveLevelScriptSymbolsEvent][ptQTask->eQTaskType].pfHandler;
    if ( pfHandler )
      pfHandler(ptQTask);
  }
LABEL_9:
  Level_DeinitLevelExpression((struct LevelExpression_s *)&ptQTask[14].eQTaskType);
  SectorObject_RemoveInteriorDynCubeObj((struct DynCubeObj_s *)ptQTask);
  World_RemoveDynCubeObj((struct World_s *)ptQTask[2].ptParent, (struct DynCubeObj_s *)ptQTask);
  ptNext = ptQTask[17].ptNext;
  if ( ptNext )
  {
    v5 = *(_DWORD *)((unsigned int)&ptNext[-1].eQTaskType & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v5);
    memset(*(void **)(v5 + 8), 0xCDu, *(_DWORD *)(v5 + 16));
    free((void *)v5);
    ptQTask[17].ptNext = nullptr;
  }
}

// source: j/0/objects/switch.c:407  [size]
void __cdecl Switch_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = Switch_ptParameterList;
}

// source: j/0/objects/switch.c:423  [anchor-strings]
void __cdecl Switch_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *ptNext; // edx
  int v3; // edi
  char ptHead; // cl
  int v5; // edi
  struct LODVirModel_s *LODVirModelExistsFn; // eax
  double v7; // st7
  double v8; // st7
  int *v9; // eax
  int v10; // eax
  double v11; // st6
  struct QTask_s *ptParent; // esi
  __int16 v13; // cx
  float ptDynCubeObj; // [esp+0h] [ebp-18h]

  BYTE1(ptQTask[14].tQTaskRefList.ptHead) = ptQTask[14].tQTaskRefList.ptHead;
  if ( !strcmp((char *)&ptQTask[11].tQTaskRefList.ptMiddle, (char *)&dword_6907A4) )
  {
    if ( !strcmp((char *)&ptQTask[9].tQTaskRefList.ptMiddle, "360_14_1")
      || !strcmp((char *)&ptQTask[9].tQTaskRefList.ptMiddle, "360_15_1") )
    {
      strcpy((char *)&ptQTask[11].tQTaskRefList.ptMiddle, "switch_1");
    }
    else
    {
      strcpy((char *)&ptQTask[11].tQTaskRefList.ptMiddle, "button_1");
    }
  }
  ptNext = ptQTask[17].ptNext;
  ptQTask[17].ptPrev = nullptr;
  if ( ptNext )
  {
    v3 = 0;
    while ( strcmp((char *)ptNext, StatusScreen_azQSpriteActivateIconPointer[v3]) )
    {
      if ( ++v3 >= 21 )
        goto LABEL_12;
    }
    ptQTask[17].ptPrev = (struct QTask_s *)((char *)StatusScreen_ptStatusScreenQTask + 24 * v3 + 604);
  }
LABEL_12:
  ptHead = (char)ptQTask[14].tQTaskRefList.ptHead;
  if ( ptHead != (ptHead == 0) )
  {
    v5 = ptHead != 0 ? 0 : 2;
    LODVirModelExistsFn = MTP_GetLODVirModelExistsFn((char *)&ptQTask[9].tQTaskRefList.ptMiddle + 16 * v5);
    if ( LODVirModelExistsFn != *(struct LODVirModel_s **)&ptQTask[2].eQTaskType )
    {
      ModelObj_SetLODVirModel((struct ModelObj_s *)ptQTask, LODVirModelExistsFn, false);
      ptQTask[7].tQTaskRefList.ptHead = nullptr;
      ptQTask[7].tQTaskRefList.ptMiddle = nullptr;
      ptQTask[7].tQTaskRefList.ptTail = nullptr;
      ptQTask[7].ptParent = nullptr;
      *(_DWORD *)&ptQTask[7].eQTaskType = 0;
    }
    ptQTask[7].tQTaskRefList.ptHead = *((struct QReference_s **)&ptQTask[12].ptNext + 5 * v5);
    ptQTask[7].tQTaskRefList.ptMiddle = *((struct QReference_s **)&ptQTask[12].ptPrev + 5 * v5);
    ptQTask[7].tQTaskRefList.ptTail = *((struct QReference_s **)&ptQTask[12].tQTaskChildren.ptHead + 5 * v5);
    ptQTask[7].ptParent = *(&ptQTask[12].tQTaskChildren.ptMiddle + 5 * v5);
    *(_DWORD *)&ptQTask[7].eQTaskType = *((_DWORD *)&ptQTask[12].tQTaskChildren.ptTail + 5 * v5);
  }
  if ( *(float *)&ptQTask[6].tQTaskChildren.ptHead <= (double)*(float *)&ptQTask[6].tQTaskChildren.ptMiddle )
    v7 = *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
  else
    v7 = *(float *)&ptQTask[6].tQTaskChildren.ptHead;
  if ( v7 >= *(float *)&ptQTask[6].ptPrev )
  {
    if ( *(float *)&ptQTask[6].tQTaskChildren.ptHead <= (double)*(float *)&ptQTask[6].tQTaskChildren.ptMiddle )
      v8 = *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
    else
      v8 = *(float *)&ptQTask[6].tQTaskChildren.ptHead;
  }
  else
  {
    v8 = *(float *)&ptQTask[6].ptPrev;
  }
  v9 = *(int **)&ptQTask[2].eQTaskType;
  if ( v9 && (v10 = *v9) != 0 )
    v11 = *(float *)(*(_DWORD *)(*(_DWORD *)(v10 + 12) + 12) + 120);
  else
    v11 = 1.0;
  ptDynCubeObj = v8 * v11;
  World_MoveDynCubeObjRadius(
    (struct World_s *)ptQTask[2].ptParent,
    (struct DynCubeObj_s *)ptQTask,
    (struct real64x3_t *)&ptQTask[8],
    ptDynCubeObj);
  ptParent = ptQTask[2].ptParent;
  SectorObject_RemoveInteriorDynCubeObj((struct DynCubeObj_s *)ptQTask);
  if ( ptQTask[7].tQTaskChildren.ptTail )
  {
    ptQTask[2].tQTaskRefList.ptHead = nullptr;
    ptQTask[2].tQTaskRefList.ptMiddle = nullptr;
  }
  else
  {
    SectorObject_RegisterInteriorDynCubeObjSpecificSectorObject(
      (struct World_s *)ptParent,
      nullptr,
      (struct DynCubeObj_s *)ptQTask,
      (struct real64x3_t *)&ptQTask[1]);
  }
  qmemcpy(&ptQTask[3].ptPrev, &ptQTask[8].tQTaskRefList.ptMiddle, sizeof(struct QTask_s));
  Level_CompileLevelExpression((struct LevelExpression_s *)&ptQTask[14].eQTaskType, ptQTask);
  RigidDynCubeObj_UpdateAttachments((struct RigidDynCubeObj_t *)ptQTask);
  v13 = Attach_eAttachEvent;
  ptQTask[5].tQTaskChildren.ptTail = (struct QTask_s *)-1;
  ptQTask[5].tQTaskRefList.ptHead = nullptr;
  QTask_TriggerQTaskEventParent(ptQTask, v13, &ptQTask[5].tQTaskChildren.ptTail);
  ModelObj_CalcRelativePosAndOrientation((struct ModelObj_s *)ptQTask);
}

// source: j/0/objects/switch.c:525  [size]
void __cdecl Switch_UpdateAttachmentHandler(struct QTask_s *ptQTask)
{
  ((void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[Attach_eUpdateAttachmentEvent][SectorInteriorObject_eQTaskType].pfHandler)(ptQTask);
  qmemcpy(&ptQTask[8].tQTaskRefList.ptMiddle, &ptQTask[3].ptPrev, sizeof(struct QTask_s));
  qmemcpy(&ptQTask[8], &ptQTask[1], 0x18u);
}

// source: j/0/objects/switch.c:547  [anchor-mhash]
void __cdecl Switch_EvaluateActivateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { double tDelta; };
    struct { char igi2_o1[8]; double tDelta_8; };
    struct { char igi2_o2[16]; double tDelta_16; };
    struct { char igi2_o3[24]; struct real64x3_t tPos; };
    char igi2_extent[52];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  double v2; // st7

  if ( !BYTE2(ptQTask[14].tQTaskRefList.ptHead) )
  {
    if ( HIBYTE(ptQTask[16].eQTaskType) )
    {
      GameFunctions_GetMagicVertex(&igi2_frame.tPos, ptQTask, 0);
      igi2_frame.tDelta = *((double *)pxContext + 1) - igi2_frame.tPos.vX;
      igi2_frame.tDelta_8 = *((double *)pxContext + 2) - igi2_frame.tPos.vY;
      igi2_frame.tDelta_16 = *((double *)pxContext + 3) - igi2_frame.tPos.vZ;
      v2 = *(float *)&ptQTask[3].tQTaskRefList.ptTail * igi2_frame.tDelta_16
         + *(float *)&ptQTask[3].tQTaskChildren.ptTail * igi2_frame.tDelta_8
         + *(float *)&ptQTask[3].ptPrev * igi2_frame.tDelta;
      if ( *(float *)&ptQTask[3].ptParent * igi2_frame.tDelta_16
         + *(float *)&ptQTask[3].tQTaskRefList.ptHead * igi2_frame.tDelta_8
         + *(float *)&ptQTask[3].tQTaskChildren.ptHead * igi2_frame.tDelta > 0.0 )
      {
        if ( v2 < 0.0 )
          v2 = -v2;
        if ( v2 < 3072.0 )
          GameFunctions_ResolveEvaluateActivate((struct EvaluateActivateContext_t *)pxContext, ptQTask, &igi2_frame.tPos);
      }
    }
  }
}

// source: j/0/objects/switch.c:593  [size]
void __cdecl Switch_GetActivateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = 1;
}

// source: j/0/objects/switch.c:610  [size]
void __cdecl Switch_ActivateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ;
}

// source: j/0/objects/switch.c:630  [size]
void __cdecl Switch_WeaponHitHandler(struct QTask_s *ptQTask, void *pxContext)
{
  if ( LOBYTE(ptQTask[16].eQTaskType) )
    BYTE2(ptQTask[14].tQTaskRefList.ptHead) = 1;
}

// source: j/0/objects/switch.c:652  [anchor-strings]
void __cdecl Switch_RegisterScriptSymbolsHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { char zName[64]; };
    struct { char igi2_o1[64]; char zTemp[128]; };
    char igi2_extent[192];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)

  if ( !LOBYTE(ptQTask[14].ptParent) )
  {
    LOBYTE(ptQTask[14].ptParent) = 1;
    Level_GetUniqueQTaskNameFromTask(igi2_frame.zName, ptQTask);
    sprintf(igi2_frame.zTemp, "%s.isActive", igi2_frame.zName);
    Symbol_Register(
      igi2_frame.zTemp,
      (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_Int8,
      (char *)&ptQTask[16].eQTaskType + 1,
      1,
      QSCRIPT_SYMBOLCLASS_VARIABLE,
      QSCRIPT_SYMBOLTYPE_INT,
      QSCRIPT_SYMBOLLIFESPAN_FINITE);
    sprintf(igi2_frame.zTemp, "%s.isOn", igi2_frame.zName);
    Symbol_Register(
      igi2_frame.zTemp,
      (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_Int8,
      &ptQTask[14].tQTaskRefList,
      1,
      QSCRIPT_SYMBOLCLASS_VARIABLE,
      QSCRIPT_SYMBOLTYPE_INT,
      QSCRIPT_SYMBOLLIFESPAN_FINITE);
    sprintf(igi2_frame.zTemp, "%s.isLastOn", igi2_frame.zName);
    Symbol_Register(
      igi2_frame.zTemp,
      (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_Int8,
      (char *)&ptQTask[14].tQTaskRefList.ptHead + 1,
      1,
      QSCRIPT_SYMBOLCLASS_VARIABLE,
      QSCRIPT_SYMBOLTYPE_INT,
      QSCRIPT_SYMBOLLIFESPAN_FINITE);
    sprintf(igi2_frame.zTemp, "%s.isPressed", igi2_frame.zName);
    Symbol_Register(
      igi2_frame.zTemp,
      (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_Int8,
      &ptQTask[14].tQTaskRefList.ptMiddle,
      1,
      QSCRIPT_SYMBOLCLASS_VARIABLE,
      QSCRIPT_SYMBOLTYPE_INT,
      QSCRIPT_SYMBOLLIFESPAN_FINITE);
    sprintf(igi2_frame.zTemp, "%s.isLastPressed", igi2_frame.zName);
    Symbol_Register(
      igi2_frame.zTemp,
      (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_Int8,
      (char *)&ptQTask[14].tQTaskRefList.ptMiddle + 1,
      1,
      QSCRIPT_SYMBOLCLASS_VARIABLE,
      QSCRIPT_SYMBOLTYPE_INT,
      QSCRIPT_SYMBOLLIFESPAN_FINITE);
    sprintf(igi2_frame.zTemp, "%s.isDestroyed", igi2_frame.zName);
    Symbol_Register(
      igi2_frame.zTemp,
      (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_Int8,
      (char *)&ptQTask[14].tQTaskRefList.ptHead + 2,
      1,
      QSCRIPT_SYMBOLCLASS_VARIABLE,
      QSCRIPT_SYMBOLTYPE_INT,
      QSCRIPT_SYMBOLLIFESPAN_FINITE);
    sprintf(igi2_frame.zTemp, "%s.isLastDestroyed", igi2_frame.zName);
    Symbol_Register(
      igi2_frame.zTemp,
      (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_Int8,
      (char *)&ptQTask[14].tQTaskRefList.ptHead + 3,
      1,
      QSCRIPT_SYMBOLCLASS_VARIABLE,
      QSCRIPT_SYMBOLTYPE_INT,
      QSCRIPT_SYMBOLLIFESPAN_FINITE);
    sprintf(igi2_frame.zTemp, "%s.nClientID", igi2_frame.zName);
    Symbol_Register(
      igi2_frame.zTemp,
      (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_Int,
      &ptQTask[17].tQTaskChildren,
      4,
      QSCRIPT_SYMBOLCLASS_VARIABLE,
      QSCRIPT_SYMBOLTYPE_INT,
      QSCRIPT_SYMBOLLIFESPAN_FINITE);
  }
}

// source: j/0/objects/switch.c:703  [anchor-strings]
void __cdecl Switch_RemoveScriptSymbolsHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { char zName[64]; };
    struct { char igi2_o1[64]; char zTemp[128]; };
    char igi2_extent[192];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)

  if ( LOBYTE(ptQTask[14].ptParent) )
  {
    Level_GetUniqueQTaskNameFromTask(igi2_frame.zName, ptQTask);
    LOBYTE(ptQTask[14].ptParent) = 0;
    sprintf(igi2_frame.zTemp, "%s.isActive", igi2_frame.zName);
    Symbol_Remove(igi2_frame.zTemp);
    sprintf(igi2_frame.zTemp, "%s.isOn", igi2_frame.zName);
    Symbol_Remove(igi2_frame.zTemp);
    sprintf(igi2_frame.zTemp, "%s.isDestroyed", igi2_frame.zName);
    Symbol_Remove(igi2_frame.zTemp);
    sprintf(igi2_frame.zTemp, "%s.isPressed", igi2_frame.zName);
    Symbol_Remove(igi2_frame.zTemp);
    sprintf(igi2_frame.zTemp, "%s.isLastOn", igi2_frame.zName);
    Symbol_Remove(igi2_frame.zTemp);
    sprintf(igi2_frame.zTemp, "%s.isLastDestroyed", igi2_frame.zName);
    Symbol_Remove(igi2_frame.zTemp);
    sprintf(igi2_frame.zTemp, "%s.isLastPressed", igi2_frame.zName);
    Symbol_Remove(igi2_frame.zTemp);
    sprintf(igi2_frame.zTemp, "%s.nClientID", igi2_frame.zName);
    Symbol_Remove(igi2_frame.zTemp);
    LOBYTE(ptQTask[14].ptParent) = 0;
  }
}

// source: j/0/objects/switch.c:758  [anchor-caller]
void __cdecl Switch_EnumerateLightmapVirModelsHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct Mesh3D_LightmapVirModel_t **paptLightmapVirModel; };
    struct { char igi2_o1[4]; struct QTask_s **v16; };
    struct { char igi2_o2[8]; int nQTaskID; };
    struct { char igi2_o3[12]; struct EnumerateLightmapVirModelsContext_t *ptContext; };
    struct { char igi2_o4[16]; struct EnumerateLightmapVirModelsContext_t tMyContext; };
    char igi2_extent[48];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  unsigned __int16 v2; // dx
  int v4; // ecx
  struct QReference_s *v5; // eax
  int v6; // edi
  struct QTask_s **p_ptPrev; // ebx
  int v8; // ebp
  char *p_ptMiddle; // edx
  int v10; // eax
  struct LODVirModel_s *LODVirModelExistsFn; // eax
  char ptHead; // cl
  int v13; // edi
  struct LODVirModel_s *v14; // eax
  struct QTask_s *ptQTaska = *(struct QTask_s * *)&ptQTask; // [esp+40h] [ebp+4h] ARGSLOT
  char *pxContexta = *(char * *)&pxContext; // [esp+44h] [ebp+8h] ARGSLOT

  v2 = LightmapInfo_eQTaskType;
  qmemcpy(&igi2_frame.tMyContext, pxContext, sizeof(igi2_frame.tMyContext));
  igi2_frame.ptContext = (struct EnumerateLightmapVirModelsContext_t *)pxContext;
  if ( !QTask_GetFirstChildOfType(ptQTask, LightmapInfo_eQTaskType)
    || QTask_GetFirstChildOfType(ptQTask, v2) == *(struct QTask_s **)pxContext )
  {
    v4 = 0;
    while ( 1 )
    {
      v5 = Level_atLevelQTaskID[v4];
      if ( v5 )
      {
        if ( v5->pxObject == ptQTask )
          break;
      }
      if ( ++v4 >= 4096 )
      {
        igi2_frame.nQTaskID = -1;
        goto LABEL_8;
      }
    }
    igi2_frame.nQTaskID = v4;
LABEL_8:
    igi2_frame.paptLightmapVirModel = (struct Mesh3D_LightmapVirModel_t **)&ptQTask[12];
    v6 = 0;
    p_ptPrev = &ptQTask[12].ptPrev;
    ptQTaska = nullptr;
    pxContexta = (char *)&ptQTask[9].tQTaskRefList.ptMiddle;
    igi2_frame.v16 = &ptQTask[12].ptPrev;
    do
    {
      v8 = 0;
      if ( v6 > 0 )
      {
        p_ptMiddle = (char *)&ptQTask[9].tQTaskRefList.ptMiddle;
        do
        {
          v10 = strcmp(pxContexta, p_ptMiddle);
          v6 = (int)ptQTaska;
          if ( !v10 )
            break;
          ++v8;
          p_ptMiddle += 16;
        }
        while ( v8 < (int)ptQTaska );
        p_ptPrev = igi2_frame.v16;
      }
      if ( v8 == v6 )
      {
        LODVirModelExistsFn = MTP_GetLODVirModelExistsFn(pxContexta);
        if ( LODVirModelExistsFn != *(struct LODVirModel_s **)&ptQTask[2].eQTaskType )
        {
          ModelObj_SetLODVirModel((struct ModelObj_s *)ptQTask, LODVirModelExistsFn, false);
          ptQTask[7].tQTaskRefList.ptHead = nullptr;
          ptQTask[7].tQTaskRefList.ptMiddle = nullptr;
          ptQTask[7].tQTaskRefList.ptTail = nullptr;
          ptQTask[7].ptParent = nullptr;
          *(_DWORD *)&ptQTask[7].eQTaskType = 0;
        }
        if ( igi2_frame.nQTaskID != -1 )
        {
          igi2_frame.tMyContext.nParentQTaskID = igi2_frame.nQTaskID;
          igi2_frame.tMyContext.nSubQTaskID = 0;
          igi2_frame.tMyContext.nModelVariation = v6 + 1;
        }
        LightmapInfo_AddLightmapVirModelToEnumeration(
          ptQTask,
          *(struct LODVirModel_s **)&ptQTask[2].eQTaskType,
          (struct Mesh3D_LightmapVirModel_t *(*)[5])igi2_frame.paptLightmapVirModel,
          &igi2_frame.tMyContext);
        if ( igi2_frame.nQTaskID == -1 )
        {
          ++igi2_frame.ptContext->nSubQTaskID;
        }
        else
        {
          igi2_frame.ptContext = &igi2_frame.tMyContext;
          ++igi2_frame.tMyContext.nSubQTaskID;
        }
      }
      else
      {
        *(p_ptPrev - 1) = *(&ptQTask[12].ptNext + 5 * v8);
        *p_ptPrev = *(&ptQTask[12].ptPrev + 5 * v8);
        p_ptPrev[1] = *(&ptQTask[12].tQTaskChildren.ptHead + 5 * v8);
        p_ptPrev[2] = *(&ptQTask[12].tQTaskChildren.ptMiddle + 5 * v8);
        p_ptPrev[3] = *(&ptQTask[12].tQTaskChildren.ptTail + 5 * v8);
      }
      ++v6;
      p_ptPrev += 5;
      ptQTaska = (struct QTask_s *)v6;
      pxContexta += 16;
      igi2_frame.paptLightmapVirModel += 5;
      igi2_frame.v16 = p_ptPrev;
    }
    while ( v6 < 5 );
    ptHead = (char)ptQTask[14].tQTaskRefList.ptHead;
    if ( ptHead != (ptHead == 0) )
    {
      v13 = ptHead != 0 ? 0 : 2;
      v14 = MTP_GetLODVirModelExistsFn((char *)&ptQTask[9].tQTaskRefList.ptMiddle + 16 * v13);
      if ( v14 != *(struct LODVirModel_s **)&ptQTask[2].eQTaskType )
      {
        ModelObj_SetLODVirModel((struct ModelObj_s *)ptQTask, v14, false);
        ptQTask[7].tQTaskRefList.ptHead = nullptr;
        ptQTask[7].tQTaskRefList.ptMiddle = nullptr;
        ptQTask[7].tQTaskRefList.ptTail = nullptr;
        ptQTask[7].ptParent = nullptr;
        *(_DWORD *)&ptQTask[7].eQTaskType = 0;
      }
      ptQTask[7].tQTaskRefList.ptHead = *((struct QReference_s **)&ptQTask[12].ptNext + 5 * v13);
      ptQTask[7].tQTaskRefList.ptMiddle = *((struct QReference_s **)&ptQTask[12].ptPrev + 5 * v13);
      ptQTask[7].tQTaskRefList.ptTail = *((struct QReference_s **)&ptQTask[12].tQTaskChildren.ptHead + 5 * v13);
      ptQTask[7].ptParent = *(&ptQTask[12].tQTaskChildren.ptMiddle + 5 * v13);
      *(_DWORD *)&ptQTask[7].eQTaskType = *((_DWORD *)&ptQTask[12].tQTaskChildren.ptTail + 5 * v13);
    }
  }
}

// source: j/0/objects/switch.c:839  [size]
void __cdecl Switch_DrawActionItemHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ActionMenuScreen_DrawActionItem(ActionMenuScreen_ptQTask, (struct QSprite_s *)ptQTask[17].ptPrev, pxContext);
}

// source: j/0/objects/switch.c:857  [anchor-callee]
struct QTask_s *__cdecl Switch_Pressed(struct QTask_s *ptQTask, int nClientID)
{
  struct LevelFlow_s *v2; // ecx

  v2 = LevelFlow_ptLevelFlow;
  LOBYTE(ptQTask[14].tQTaskRefList.ptMiddle) = 1;
  ptQTask[14].tQTaskRefList.ptTail = (struct QReference_s *)v2->nTick;
  ptQTask[17].tQTaskChildren.ptHead = (struct QTask_s *)nClientID;
  return ptQTask;
}

// source: j/0/objects/switch.c:912  [size]
unsigned __int16 __cdecl Switch_GetQTaskType()
{
  return Switch_eQTaskType;
}

// source: j/0/objects/switch.c:925  [anchor-mhash]
void __cdecl Switch_Open()
{
  unsigned __int16 v0; // si
  struct ParameterList_s *v1; // eax
  int v2; // edx
  unsigned __int16 v3; // si
  struct ParameterList_s *v4; // eax
  int v5; // edx

  dword_752ED4 = 21;
  unk_752ED8 = StatusScreen_azQSpriteActivateIconPointer;
  v0 = QTask_NewQTaskType("Switch", 696, SectorInteriorObject_eQTaskType, 0, 0);
  Switch_eQTaskType = v0;
  QTask_LinkQTaskEventHandlerFn(
    v0,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveHandler);
  QTask_LinkQTaskEventHandlerFn(v0, 0, Switch_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 1, Switch_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 2, Switch_DeleteHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Switch_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(v0, ParameterList_eUpdateInternalDataQTaskEvent, Switch_UpdateInternalDataHandler);
  QTask_LinkQTaskEventHandlerFn(v0, GameFunctions_eEvaluateActivateQTaskEvent, Switch_EvaluateActivateHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    GameFunctions_eGetActivateQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Switch_GetActivateHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    GameFunctions_eActivateQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Switch_ActivateHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    GameFunctions_eWeaponHitQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Switch_WeaponHitHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(
    v0,
    Level_eRegisterLevelScriptSymbolsEvent,
    Switch_RegisterScriptSymbolsHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, Level_eRemoveLevelScriptSymbolsEvent, Switch_RemoveScriptSymbolsHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, Attach_eUpdateAttachmentEvent, Switch_UpdateAttachmentHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    LightmapInfo_eEnumerateLightmapVirModelsEvent,
    Switch_EnumerateLightmapVirModelsHandler);
  QTask_LinkQTaskEventHandlerFn(v0, ActionMenuScreen_eDrawActionItemQTaskEvent, Switch_DrawActionItemHandler);
  QTask_LinkQTaskEventHandlerFn(v0, BulletHole_eCreateBulletHoleTaskEvent, nullptr);
  v1 = (struct ParameterList_s *)Mem_AllocFn(252, 4);
  v1->ptParameterListItem = (struct ParameterListItem_s *)&v1[1];
  v2 = Level_eParameterTypeObjectPos;
  v1->nParameters = 0;
  v1->nMaxParameters = 12;
  Switch_ptParameterList = v1;
  ParameterList_AddParameter(v1, 0x140u, v2, "Position", 7u, nullptr);
  ParameterList_AddParameter(Switch_ptParameterList, 0x158u, Level_eParameterTypeReal32x9, "Orientation", 7u, nullptr);
  ParameterList_AddParameter(Switch_ptParameterList, 0x254u, Level_eParameterTypeVarString, "Active", 7u, nullptr);
  ParameterList_AddParameter(Switch_ptParameterList, 0x244u, Level_eParameterTypebool8, "Initial on", 7u, nullptr);
  ParameterList_AddParameter(Switch_ptParameterList, 0x1D0u, Level_eParameterTypeString16, "Sound", 7u, nullptr);
  ParameterList_AddParameter(Switch_ptParameterList, 0x180u, Level_eParameterTypeString16, "On model", 7u, nullptr);
  ParameterList_AddParameter(
    Switch_ptParameterList,
    0x190u,
    Level_eParameterTypeString16,
    "On pressed model",
    7u,
    nullptr);
  ParameterList_AddParameter(Switch_ptParameterList, 0x1A0u, Level_eParameterTypeString16, "Off model", 7u, nullptr);
  ParameterList_AddParameter(
    Switch_ptParameterList,
    0x1B0u,
    Level_eParameterTypeString16,
    "Off pressed model",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Switch_ptParameterList,
    0x1C0u,
    Level_eParameterTypeString16,
    "Destroyed model",
    7u,
    nullptr);
  ParameterList_AddParameter(Switch_ptParameterList, 0x2A4u, Level_eParameterTypebool8, "Destructable", 7u, nullptr);
  ParameterList_AddParameter(
    Switch_ptParameterList,
    0x2A8u,
    Level_eParameterTypeDropDownCombo,
    "Click to select sprite",
    7u,
    &dword_752ED4);
  v3 = Switch_eQTaskType;
  QTask_LinkQTaskEventHandlerFn(
    Switch_eQTaskType,
    Serialize_eGetSerializeParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Switch_GetSerializeParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(v3, Serialize_eDeSerializeQTaskEvent, Switch_DeSerializeHandler);
  v4 = (struct ParameterList_s *)Mem_AllocFn(172, 4);
  v5 = Level_eParameterTypebool8;
  v4->ptParameterListItem = (struct ParameterListItem_s *)&v4[1];
  v4->nParameters = 0;
  v4->nMaxParameters = 8;
  Switch_ptSerializeParameterList = v4;
  ParameterList_AddParameter(v4, 0x244u, v5, "isOn", 7u, nullptr);
  ParameterList_AddParameter(
    Switch_ptSerializeParameterList,
    0x245u,
    Level_eParameterTypebool8,
    "isLastOn",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Switch_ptSerializeParameterList,
    0x246u,
    Level_eParameterTypebool8,
    "isDestroyed",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Switch_ptSerializeParameterList,
    0x247u,
    Level_eParameterTypebool8,
    "isLastDestroyed",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Switch_ptSerializeParameterList,
    0x248u,
    Level_eParameterTypebool8,
    "isPressed",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Switch_ptSerializeParameterList,
    0x249u,
    Level_eParameterTypebool8,
    "isLastPressed",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Switch_ptSerializeParameterList,
    0x24Cu,
    Level_eParameterTypeInt32,
    "nLastPressedTick",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Switch_ptSerializeParameterList,
    0x2A5u,
    Level_eParameterTypebool8,
    "isActive",
    7u,
    nullptr);
}

// source: j/0/objects/switch.c:1007  [size]
void __cdecl Switch_Close()
{
  int v0; // esi
  int v1; // esi

  if ( Switch_ptParameterList )
  {
    v0 = *(_DWORD *)((unsigned int)&Switch_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
  if ( Switch_ptSerializeParameterList )
  {
    v1 = *(_DWORD *)((unsigned int)&Switch_ptSerializeParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v1);
    memset(*(void **)(v1 + 8), 0xCDu, *(_DWORD *)(v1 + 16));
    free((void *)v1);
  }
  QTask_DeleteQTaskType(Switch_eQTaskType);
}

// source: j/0/objects/switch.c:1027  [size]
enum bool __cdecl Switch_IsOn(struct QTask_s *ptQTask)
{
  return SLOBYTE(ptQTask[14].tQTaskRefList.ptHead);
}

// source: j/0/objects/switch.c:1044  [size]
int __cdecl Switch_GetLastPressedTick(struct QTask_s *ptQTask)
{
  return (int)ptQTask[14].tQTaskRefList.ptTail;
}
