/* h/2/moverigidobj.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: h/2/moverigidobj.c:85  [anchor-callee]
void __cdecl MoveRigidObj_UpdatePositionAndOrientation(
        struct MoveRigidObj_t *ptMoveRigidObj,
        struct RigidDynCubeObj_t *ptRigidDynCubeObj,
        char isForceUpdate)
{
  #pragma pack(push, 1)
  union
  {
    struct { float ptDest; };
    struct { char igi2_o1[4]; float vAlpha; };
    struct { char igi2_o2[8]; float vBeta; };
    struct { char igi2_o3[8]; float vBetaa; };
    struct { char igi2_o4[20]; __int64 iValue0; };
    struct { char igi2_o5[28]; struct real64x3_t tPos; };
    char igi2_extent[52];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v4; // eax
  double *v5; // ebx
  double v6; // st7
  double *v7; // edx
  double vZ; // st7
  double vY; // st7
  struct LODVirModel_s *ptLODVirModel; // eax
  struct VirModel_s *v11; // eax
  double vRadius; // st6
  int vValue_high; // ecx

  if ( ptMoveRigidObj->vValue != ptMoveRigidObj->vLastValue || isForceUpdate )
  {
    igi2_frame.iValue0 = (__int64)ptMoveRigidObj->vValue;
    v4 = ((int)igi2_frame.iValue0 + 1) % 2;
    v5 = (double *)((char *)ptMoveRigidObj + 24 * v4);
    v6 = ptMoveRigidObj->vValue - (double)(int)igi2_frame.iValue0;
    v7 = (double *)((char *)ptMoveRigidObj + 24 * igi2_frame.iValue0);
    igi2_frame.tPos.vX = v6 * v5[40] + (1.0 - v6) * v7[40];
    igi2_frame.tPos.vY = v6 * v5[41] + (1.0 - v6) * v7[41];
    igi2_frame.tPos.vZ = (1.0 - v6) * ptMoveRigidObj->atPos[igi2_frame.iValue0].vZ + v6 * ptMoveRigidObj->atPos[v4].vZ;
    igi2_frame.vBeta = (1.0 - v6) * ptMoveRigidObj->avGamma[igi2_frame.iValue0] + v6 * ptMoveRigidObj->avGamma[v4];
    igi2_frame.vAlpha = (1.0 - v6) * ptMoveRigidObj->avBeta[igi2_frame.iValue0] + v6 * ptMoveRigidObj->avBeta[v4];
    igi2_frame.ptDest = (1.0 - v6) * ptMoveRigidObj->avAlpha[igi2_frame.iValue0] + v6 * ptMoveRigidObj->avAlpha[v4];
    Real32x9_Create(&ptRigidDynCubeObj->tModelObj.tOrientation, igi2_frame.ptDest, igi2_frame.vAlpha, igi2_frame.vBeta);
    if ( ptRigidDynCubeObj->tModelObj.tScale.vY <= (double)ptRigidDynCubeObj->tModelObj.tScale.vZ )
      vZ = ptRigidDynCubeObj->tModelObj.tScale.vZ;
    else
      vZ = ptRigidDynCubeObj->tModelObj.tScale.vY;
    if ( vZ >= ptRigidDynCubeObj->tModelObj.tScale.vX )
    {
      if ( ptRigidDynCubeObj->tModelObj.tScale.vY <= (double)ptRigidDynCubeObj->tModelObj.tScale.vZ )
        vY = ptRigidDynCubeObj->tModelObj.tScale.vZ;
      else
        vY = ptRigidDynCubeObj->tModelObj.tScale.vY;
    }
    else
    {
      vY = ptRigidDynCubeObj->tModelObj.tScale.vX;
    }
    ptLODVirModel = ptRigidDynCubeObj->tModelObj.ptLODVirModel;
    if ( ptLODVirModel && (v11 = ptLODVirModel->aptVirModel[0]) != nullptr )
      vRadius = v11->ptModel->ptMesh->vRadius;
    else
      vRadius = 1.0;
    igi2_frame.vBetaa = vY * vRadius;
    World_MoveDynCubeObjRadius(
      ptRigidDynCubeObj->tModelObj.ptWorld,
      &ptRigidDynCubeObj->tModelObj.tDynCubeObj,
      &igi2_frame.tPos,
      igi2_frame.vBetaa);
    vValue_high = HIDWORD(ptMoveRigidObj->vValue);
    LODWORD(ptMoveRigidObj->vLastValue) = LODWORD(ptMoveRigidObj->vValue);
    HIDWORD(ptMoveRigidObj->vLastValue) = vValue_high;
  }
}

// source: h/2/moverigidobj.c:152  [anchor-mhash]
void __cdecl MoveRigidObj_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { float ptDynCubeObj; };
    struct { char igi2_o1[24]; struct real64x3_t tVNull; };
    char igi2_extent[48];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct World_s *v2; // eax
  double v3; // st7
  double v4; // st7
  int *v5; // eax
  int v6; // eax
  double v7; // st6
  struct QReference_s **p_ptMiddle; // ecx
  struct QTaskNodeList_s *p_tQTaskChildren; // eax
  int v10; // esi

  v2 = World_ptActiveWorld;
  ptQTask[12].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[12].tQTaskRefList.ptTail = (struct QReference_s *)-1074790400;
  LOBYTE(ptQTask[11].tQTaskRefList.ptMiddle) = 0;
  memset(&igi2_frame.tVNull, 0, sizeof(igi2_frame.tVNull));
  *(_DWORD *)&ptQTask[12].eQTaskType = 0;
  ptQTask[13].ptNext = nullptr;
  ptQTask[13].ptPrev = nullptr;
  ptQTask[14].ptParent = nullptr;
  ModelObj_Init((struct ModelObj_s *)ptQTask, v2, nullptr);
  ptQTask[7].tQTaskChildren.ptHead = nullptr;
  ptQTask[7].tQTaskChildren.ptMiddle = (struct QTask_s *)2;
  ptQTask[7].tQTaskRefList.ptHead = nullptr;
  ptQTask[7].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[7].tQTaskRefList.ptTail = nullptr;
  ptQTask[7].ptParent = nullptr;
  *(_DWORD *)&ptQTask[7].eQTaskType = 0;
  if ( *(float *)&ptQTask[6].tQTaskChildren.ptHead <= (double)*(float *)&ptQTask[6].tQTaskChildren.ptMiddle )
    v3 = *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
  else
    v3 = *(float *)&ptQTask[6].tQTaskChildren.ptHead;
  if ( v3 >= *(float *)&ptQTask[6].ptPrev )
  {
    if ( *(float *)&ptQTask[6].tQTaskChildren.ptHead <= (double)*(float *)&ptQTask[6].tQTaskChildren.ptMiddle )
      v4 = *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
    else
      v4 = *(float *)&ptQTask[6].tQTaskChildren.ptHead;
  }
  else
  {
    v4 = *(float *)&ptQTask[6].ptPrev;
  }
  v5 = *(int **)&ptQTask[2].eQTaskType;
  if ( v5 && (v6 = *v5) != 0 )
    v7 = *(float *)(*(_DWORD *)(*(_DWORD *)(v6 + 12) + 12) + 120);
  else
    v7 = 1.0;
  igi2_frame.ptDynCubeObj = v4 * v7;
  World_RegisterDynCubeObjFirstTimeRadius(
    World_ptActiveWorld,
    (struct DynCubeObj_s *)ptQTask,
    &igi2_frame.tVNull,
    igi2_frame.ptDynCubeObj,
    WORLD_DYNCUBETREE_CATEGORY_MOBILE);
  p_ptMiddle = &ptQTask[10].tQTaskRefList.ptMiddle;
  p_tQTaskChildren = &ptQTask[8].tQTaskChildren;
  v10 = 2;
  do
  {
    p_tQTaskChildren[-1].ptMiddle = nullptr;
    p_tQTaskChildren[-1].ptTail = nullptr;
    p_tQTaskChildren->ptHead = nullptr;
    p_tQTaskChildren->ptMiddle = nullptr;
    p_tQTaskChildren->ptTail = nullptr;
    p_tQTaskChildren[1].ptHead = nullptr;
    *(p_ptMiddle - 2) = nullptr;
    *p_ptMiddle = nullptr;
    p_ptMiddle[2] = nullptr;
    p_tQTaskChildren[3].ptMiddle = nullptr;
    p_tQTaskChildren[3].ptTail = nullptr;
    p_tQTaskChildren[4].ptHead = nullptr;
    p_tQTaskChildren[4].ptMiddle = nullptr;
    p_tQTaskChildren[4].ptTail = nullptr;
    p_tQTaskChildren[5].ptHead = nullptr;
    p_ptMiddle[4] = (struct QReference_s *)-1082130432;
    p_ptMiddle[6] = (struct QReference_s *)-1082130432;
    p_ptMiddle[8] = (struct QReference_s *)-1082130432;
    ++p_ptMiddle;
    p_tQTaskChildren += 2;
    --v10;
  }
  while ( v10 );
  LOBYTE(ptQTask[14].eQTaskType) = 0;
}

// source: h/2/moverigidobj.c:212  [size]
void __cdecl MoveRigidObj_RegisterScriptSymbolsHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { char zName[64]; };
    struct { char igi2_o1[64]; char zTemp[128]; };
    char igi2_extent[192];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)

  if ( !LOBYTE(ptQTask[14].eQTaskType) )
  {
    LOBYTE(ptQTask[14].eQTaskType) = 1;
    Level_GetUniqueQTaskNameFromTask(igi2_frame.zName, ptQTask);
    sprintf(igi2_frame.zTemp, "%s.vValue", igi2_frame.zName);
    Symbol_Register(
      igi2_frame.zTemp,
      Script_Float,
      &ptQTask[12].tQTaskChildren.ptTail,
      8,
      QSCRIPT_SYMBOLCLASS_VARIABLE,
      QSCRIPT_SYMBOLTYPE_FLOAT,
      QSCRIPT_SYMBOLLIFESPAN_FINITE);
  }
}

// source: h/2/moverigidobj.c:242  [size]
void __cdecl MoveRigidObj_RemoveScriptSymbolsHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { char zName[64]; };
    struct { char igi2_o1[64]; char zTemp[128]; };
    char igi2_extent[192];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)

  Level_GetUniqueQTaskNameFromTask(igi2_frame.zName, ptQTask);
  LOBYTE(ptQTask[14].eQTaskType) = 0;
  sprintf(igi2_frame.zTemp, "%s.vValue", igi2_frame.zName);
  Symbol_Remove(igi2_frame.zTemp);
  LOBYTE(ptQTask[14].eQTaskType) = 0;
}

// source: h/2/moverigidobj.c:272  [anchor-mhash]
void __cdecl MoveRigidObj_DeleteHandler(struct QTask_s *ptQTask)
{
  int v1; // ecx
  struct QReference_s *v2; // eax
  void (__cdecl *pfHandler)(struct QTask_s *); // eax

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
  Level_DeinitLevelExpression((struct LevelExpression_s *)&ptQTask[12].eQTaskType);
  World_RemoveDynCubeObj((struct World_s *)ptQTask[2].ptParent, (struct DynCubeObj_s *)ptQTask);
  if ( *(_DWORD *)&ptQTask[2].eQTaskType )
  {
    ModelObj_SetLODVirModel((struct ModelObj_s *)ptQTask, nullptr, false);
    ptQTask[7].tQTaskRefList.ptHead = nullptr;
    ptQTask[7].tQTaskRefList.ptMiddle = nullptr;
    ptQTask[7].tQTaskRefList.ptTail = nullptr;
    ptQTask[7].ptParent = nullptr;
    *(_DWORD *)&ptQTask[7].eQTaskType = 0;
  }
}

// source: h/2/moverigidobj.c:304  [size]
void __cdecl MoveRigidObj_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = MoveRigidObj_ptParameterList;
}

// source: h/2/moverigidobj.c:349  [size]
void __cdecl MoveRigidObj_RunHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { float ptDest; };
    struct { char igi2_o1[4]; float vAlpha; };
    struct { char igi2_o2[8]; float vBeta; };
    struct { char igi2_o3[8]; float vBetaa; };
    struct { char igi2_o4[20]; __int64 v22; };
    struct { char igi2_o5[28]; struct real64x3_t ptNewPos; };
    char igi2_extent[52];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *ptHead; // ecx
  int v2; // edx
  struct QTask_s *v3; // eax
  void (__cdecl *pfHandler)(struct QTask_s *); // eax
  int v5; // edx
  double v6; // st7
  double v7; // st7
  int v8; // eax
  double *v9; // edi
  double v10; // st7
  double *v11; // edx
  double v12; // st7
  double v13; // st7
  int *v14; // eax
  int v15; // eax
  double v16; // st6
  struct QReference_s *v17; // ecx

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
  if ( *(_DWORD *)&ptQTask[12].eQTaskType && ptQTask[13].ptNext->ptNext && ptQTask[13].ptPrev )
    *(double *)&ptQTask[12].tQTaskChildren.ptTail = Level_RunLevelExpression(
                                                      (struct LevelExpression_s *)&ptQTask[12].eQTaskType,
                                                      ptQTask);
  if ( *(double *)&ptQTask[12].tQTaskChildren.ptTail < 0.0 )
  {
    v6 = *(double *)&ptQTask[12].tQTaskChildren.ptTail;
    do
      v6 = v6 + 2.0;
    while ( v6 < 0.0 );
    *(double *)&ptQTask[12].tQTaskChildren.ptTail = v6;
  }
  if ( *(double *)&ptQTask[12].tQTaskChildren.ptTail > 1.0 )
  {
    v7 = *(double *)&ptQTask[12].tQTaskChildren.ptTail;
    do
      v7 = v7 - 1.0;
    while ( v7 > 1.0 );
    *(double *)&ptQTask[12].tQTaskChildren.ptTail = v7;
  }
  if ( *(double *)&ptQTask[12].tQTaskChildren.ptTail != *(double *)&ptQTask[12].tQTaskRefList.ptMiddle )
  {
    igi2_frame.v22 = (__int64)*(double *)&ptQTask[12].tQTaskChildren.ptTail;
    v8 = ((int)igi2_frame.v22 + 1) % 2;
    v9 = (double *)((char *)ptQTask + 24 * v8);
    v10 = *(double *)&ptQTask[12].tQTaskChildren.ptTail - (double)(int)igi2_frame.v22;
    v11 = (double *)((char *)ptQTask + 24 * igi2_frame.v22);
    igi2_frame.ptNewPos.vX = v10 * v9[40] + (1.0 - v10) * v11[40];
    igi2_frame.ptNewPos.vY = v10 * v9[41] + (1.0 - v10) * v11[41];
    igi2_frame.ptNewPos.vZ = (1.0 - v10) * *((double *)&ptQTask[8].tQTaskChildren.ptTail + 3 * igi2_frame.v22)
                + v10 * *((double *)&ptQTask[8].tQTaskChildren.ptTail + 3 * v8);
    igi2_frame.vBeta = (1.0 - v10) * *((float *)&ptQTask[10].ptParent + igi2_frame.v22) + v10 * *((float *)&ptQTask[10].ptParent + v8);
    igi2_frame.vAlpha = (1.0 - v10) * *((float *)&ptQTask[10].tQTaskRefList.ptMiddle + igi2_frame.v22)
           + v10 * *((float *)&ptQTask[10].tQTaskRefList.ptMiddle + v8);
    igi2_frame.ptDest = (1.0 - v10) * *((float *)&ptQTask[10].tQTaskChildren.ptTail + igi2_frame.v22)
           + v10 * *((float *)&ptQTask[10].tQTaskChildren.ptTail + v8);
    Real32x9_Create((struct real32x9_t *)&ptQTask[3].ptPrev, igi2_frame.ptDest, igi2_frame.vAlpha, igi2_frame.vBeta);
    if ( *(float *)&ptQTask[6].tQTaskChildren.ptHead <= (double)*(float *)&ptQTask[6].tQTaskChildren.ptMiddle )
      v12 = *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
    else
      v12 = *(float *)&ptQTask[6].tQTaskChildren.ptHead;
    if ( v12 >= *(float *)&ptQTask[6].ptPrev )
    {
      if ( *(float *)&ptQTask[6].tQTaskChildren.ptHead <= (double)*(float *)&ptQTask[6].tQTaskChildren.ptMiddle )
        v13 = *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
      else
        v13 = *(float *)&ptQTask[6].tQTaskChildren.ptHead;
    }
    else
    {
      v13 = *(float *)&ptQTask[6].ptPrev;
    }
    v14 = *(int **)&ptQTask[2].eQTaskType;
    if ( v14 && (v15 = *v14) != 0 )
      v16 = *(float *)(*(_DWORD *)(*(_DWORD *)(v15 + 12) + 12) + 120);
    else
      v16 = 1.0;
    igi2_frame.vBetaa = v13 * v16;
    World_MoveDynCubeObjRadius((struct World_s *)ptQTask[2].ptParent, (struct DynCubeObj_s *)ptQTask, &igi2_frame.ptNewPos, igi2_frame.vBetaa);
    v17 = ptQTask[12].tQTaskRefList.ptHead;
    ptQTask[12].tQTaskRefList.ptMiddle = (struct QReference_s *)ptQTask[12].tQTaskChildren.ptTail;
    ptQTask[12].tQTaskRefList.ptTail = v17;
  }
}

// source: h/2/moverigidobj.c:389  [anchor-mhash]
void __cdecl MoveRigidObj_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  int v2; // ebp
  float *p_ptPrev; // edx
  double *p_ptParent; // ebx
  int v5; // eax
  int v6; // ecx
  int v7; // eax
  struct LODVirModel_s *LODVirModelExistsFn; // eax
  struct QTask_s *ptHead; // eax
  int v10; // edx
  struct QTask_s *v11; // ecx
  void (__cdecl *pfHandler)(struct QTask_s *, _DWORD); // ecx
  int v13; // edx
  int iCount; // [esp+10h] [ebp-4h]

  v2 = 1;
  p_ptPrev = (float *)&ptQTask[11].ptPrev;
  iCount = 1;
  p_ptParent = (double *)&ptQTask[8].ptParent;
  do
  {
    if ( p_ptParent[5] != *(p_ptParent - 1)
      || p_ptParent[6] != *p_ptParent
      || p_ptParent[7] != p_ptParent[1]
      || *(p_ptPrev - 6) != *p_ptPrev
      || *(p_ptPrev - 4) != p_ptPrev[2]
      || *(p_ptPrev - 2) != p_ptPrev[4] )
    {
      v5 = *((_DWORD *)p_ptPrev - 6);
      qmemcpy(p_ptParent + 5, p_ptParent - 1, 0x18u);
      v6 = *((_DWORD *)p_ptPrev - 4);
      *(_DWORD *)p_ptPrev = v5;
      v7 = *((_DWORD *)p_ptPrev - 2);
      *((_DWORD *)p_ptPrev + 2) = v6;
      *((_DWORD *)p_ptPrev + 4) = v7;
      *(double *)&ptQTask[12].tQTaskChildren.ptTail = (double)iCount;
    }
    --v2;
    --p_ptPrev;
    p_ptParent -= 3;
    iCount = v2;
  }
  while ( v2 >= 0 );
  LODVirModelExistsFn = MTP_GetLODVirModelExistsFn((char *)&ptQTask[11].tQTaskRefList.ptMiddle);
  if ( LODVirModelExistsFn != *(struct LODVirModel_s **)&ptQTask[2].eQTaskType )
  {
    ModelObj_SetLODVirModel((struct ModelObj_s *)ptQTask, LODVirModelExistsFn, false);
    ptQTask[7].tQTaskRefList.ptHead = nullptr;
    ptQTask[7].tQTaskRefList.ptMiddle = nullptr;
    ptQTask[7].tQTaskRefList.ptTail = nullptr;
    ptQTask[7].ptParent = nullptr;
    *(_DWORD *)&ptQTask[7].eQTaskType = 0;
  }
  MoveRigidObj_UpdatePositionAndOrientation((struct MoveRigidObj_t *)ptQTask, (struct RigidDynCubeObj_t *)ptQTask, 1);
  if ( !pxContext || !*(_DWORD *)pxContext )
  {
    ptHead = ptQTask->tQTaskChildren.ptHead;
    if ( ptHead->ptNext )
    {
      if ( ptHead )
      {
        v10 = QTask_nProtectedQTaskStackOffset;
        do
        {
          if ( ptHead->ptNext )
            v11 = ptHead->ptNext->ptNext != nullptr ? ptHead->ptNext : nullptr;
          else
            v11 = nullptr;
          QTask_atProtectedQTaskStack[v10].ptQTask = v11;
          pfHandler = (void (__cdecl *)(struct QTask_s *, _DWORD))QTask_aatQTaskFinalEvent[ParameterList_eUpdateInternalDataQTaskEvent][ptHead->eQTaskType].pfHandler;
          v13 = v10 + 1;
          QTask_nProtectedQTaskStackOffset = v13;
          if ( pfHandler )
          {
            pfHandler(ptHead, 0);
            v13 = QTask_nProtectedQTaskStackOffset;
          }
          ptHead = (struct QTask_s *)dword_849C7DC[v13];
          v10 = v13 - 1;
          QTask_nProtectedQTaskStackOffset = v10;
        }
        while ( ptHead );
      }
    }
  }
  Level_CompileLevelExpression((struct LevelExpression_s *)&ptQTask[12].eQTaskType, ptQTask);
}

// source: h/2/moverigidobj.c:479  [anchor-strings]
void __cdecl MoveRigidObj_Open()
{
  unsigned __int16 v0; // si
  struct ParameterList_s *v1; // eax
  int v2; // esi
  signed int v3; // edi
  int v4; // ebx
  unsigned int ptParameterList; // [esp+10h] [ebp-4h]

  v0 = QTask_NewQTaskType("MoveRigidObj", 600, RigidDynCubeObj_eQTaskType, 0, 0);
  MoveRigidObj_eQTaskType = v0;
  QTask_LinkQTaskEventHandlerFn(
    v0,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveHandler);
  QTask_LinkQTaskEventHandlerFn(v0, 0, MoveRigidObj_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 1, MoveRigidObj_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 2, MoveRigidObj_DeleteHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))MoveRigidObj_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(v0, ParameterList_eUpdateInternalDataQTaskEvent, MoveRigidObj_UpdateInternalDataHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(
    v0,
    Level_eRegisterLevelScriptSymbolsEvent,
    MoveRigidObj_RegisterScriptSymbolsHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(
    v0,
    Level_eRemoveLevelScriptSymbolsEvent,
    MoveRigidObj_RemoveScriptSymbolsHandler);
  v1 = (struct ParameterList_s *)Mem_AllocFn(412, 4);
  v1->nParameters = 0;
  v1->nMaxParameters = 20;
  v1->ptParameterListItem = (struct ParameterListItem_s *)&v1[1];
  MoveRigidObj_ptParameterList = v1;
  v2 = 0;
  v3 = 424;
  ptParameterList = 320;
  v4 = 0;
  do
  {
    sprintf(&byte_8343D60[v4], "Position %d", v2);
    sprintf(&byte_8343DC4[v4], "Alpha %d", v2);
    sprintf(&byte_8343DA4[v4], "Beta %d", v2);
    sprintf(&byte_8343D84[v4], "Gamma %d", v2);
    ParameterList_AddParameter(
      MoveRigidObj_ptParameterList,
      ptParameterList,
      Level_eParameterTypeObjectPos,
      &byte_8343D60[v4],
      7u,
      nullptr);
    ParameterList_AddParameter(
      MoveRigidObj_ptParameterList,
      v3 - 8,
      Level_eParameterTypeAngle,
      &byte_8343DC4[v4],
      7u,
      nullptr);
    ParameterList_AddParameter(
      MoveRigidObj_ptParameterList,
      v3,
      Level_eParameterTypeAngle,
      &byte_8343DA4[v4],
      7u,
      nullptr);
    ParameterList_AddParameter(
      MoveRigidObj_ptParameterList,
      v3 + 8,
      Level_eParameterTypeAngle,
      &byte_8343D84[v4],
      7u,
      nullptr);
    v3 += 4;
    ++v2;
    v4 += 16;
    ptParameterList += 24;
  }
  while ( v3 < 432 );
  ParameterList_AddParameter(MoveRigidObj_ptParameterList, 0x1D0u, Level_eParameterTypeString16, "Model", 3u, nullptr);
  ParameterList_AddParameter(
    MoveRigidObj_ptParameterList,
    0x204u,
    Level_eParameterTypeVarString,
    "Morph value",
    7u,
    nullptr);
  ParameterList_AddParameter(MoveRigidObj_ptParameterList, 0x1F0u, Level_eParameterTypeReal64, "Value", 3u, nullptr);
  ParameterList_AddParameter(MoveRigidObj_ptParameterList, 0x200u, Level_eParameterTypebool8, "Animate", 3u, nullptr);
  Symbol_Register(
    "TASKTYPE_MOVERIGIDOBJ",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)MoveRigidObj_eQTaskType,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
}

// source: h/2/moverigidobj.c:541  [size]
void __cdecl MoveRigidObj_Close()
{
  int v0; // esi

  if ( MoveRigidObj_ptParameterList )
  {
    v0 = *(_DWORD *)((unsigned int)&MoveRigidObj_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
  QTask_DeleteQTaskType(MoveRigidObj_eQTaskType);
}

// source: h/2/moverigidobj.c:558  [size]
unsigned __int16 __cdecl MoveRigidObj_GetQTaskType()
{
  return MoveRigidObj_eQTaskType;
}
