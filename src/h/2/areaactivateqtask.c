/* h/2/areaactivateqtask.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: h/2/areaactivateqtask.c:111  [anchor-mhash]
struct Result_s *__cdecl AreaActivateQTask_IdInAreaCB(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  #pragma pack(push, 1)
  union
  {
    struct { unsigned int pxData; };
    struct { char igi2_o1[4]; struct Result_s Rs; };
    char igi2_extent[28];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  unsigned int v3; // esi
  unsigned int v4; // edx
  struct QReference_s *v5; // esi
  struct QTask_s *pxObject; // esi
  struct QReference_s *v7; // eax
  char *v8; // edx

  if ( ptArgList->nArguments != 2 )
  {
    igi2_frame.Rs.nResult = 0;
LABEL_20:
    HIDWORD(igi2_frame.Rs.vResult) = 0;
    goto LABEL_21;
  }
  if ( ptArgList->isQVM )
  {
    igi2_frame.pxData = 0;
    QVM_EvalArg(&igi2_frame.pxData, 4, ptArgList, 0, 1);
    v3 = igi2_frame.pxData;
  }
  else
  {
    v3 = Expression_EvalInt(*ptArgList->aptExpression);
  }
  if ( ptArgList->isQVM )
  {
    igi2_frame.pxData = 0;
    QVM_EvalArg(&igi2_frame.pxData, 4, ptArgList, 1, 1);
    v4 = igi2_frame.pxData;
  }
  else
  {
    v4 = Expression_EvalInt(ptArgList->aptExpression[1]);
  }
  if ( v3 >= 0x1000
    || (v5 = Level_atLevelQTaskID[v3]) == nullptr
    || (pxObject = (struct QTask_s *)v5->pxObject) == nullptr
    || QTask_IsQTaskTypeDerived(pxObject->eQTaskType, AreaActivateQTask_eQTaskType) == false
    || v4 >= 0x1000
    || (v7 = Level_atLevelQTaskID[v4]) == nullptr
    || (v8 = (char *)v7->pxObject) == nullptr
    || QTask_IsQTaskTypeDerived(*((_WORD *)v8 + 18), ShadowVolume_nShadow) == false
    || !AreaActivateQTask_IsInsideArea(pxObject, (struct real64x3_t *)(v8 + 40)) )
  {
    igi2_frame.Rs.nResult = 0;
    goto LABEL_20;
  }
  igi2_frame.Rs.nResult = 1;
  HIDWORD(igi2_frame.Rs.vResult) = 1072693248;
LABEL_21:
  LODWORD(igi2_frame.Rs.vResult) = 0;
  igi2_frame.Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &igi2_frame.Rs, sizeof(struct Result_s));
  return retstr;
}

// source: h/2/areaactivateqtask.c:173  [size]
void __cdecl AreaActivateQTask_RegisterScriptSymbolsHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { char zName[64]; };
    struct { char igi2_o1[64]; char zTemp[128]; };
    char igi2_extent[192];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)

  if ( !BYTE2(ptQTask[4].tQTaskRefList.ptTail) )
  {
    BYTE2(ptQTask[4].tQTaskRefList.ptTail) = 1;
    Level_GetUniqueQTaskNameFromTask(igi2_frame.zName, ptQTask);
    sprintf(igi2_frame.zTemp, "%s.nActive", igi2_frame.zName);
    Symbol_Register(
      igi2_frame.zTemp,
      (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_Int,
      &ptQTask[4].tQTaskChildren.ptTail,
      4,
      QSCRIPT_SYMBOLCLASS_VARIABLE,
      QSCRIPT_SYMBOLTYPE_INT,
      QSCRIPT_SYMBOLLIFESPAN_FINITE);
    sprintf(igi2_frame.zTemp, "%s.nClientID", igi2_frame.zName);
    Symbol_Register(
      igi2_frame.zTemp,
      (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_Int,
      &ptQTask[4].ptParent,
      4,
      QSCRIPT_SYMBOLCLASS_VARIABLE,
      QSCRIPT_SYMBOLTYPE_INT,
      QSCRIPT_SYMBOLLIFESPAN_FINITE);
  }
}

// source: h/2/areaactivateqtask.c:206  [size]
void __cdecl AreaActivateQTask_RemoveScriptSymbolsHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { char zName[64]; };
    struct { char igi2_o1[64]; char zTemp[128]; };
    char igi2_extent[192];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)

  if ( BYTE2(ptQTask[4].tQTaskRefList.ptTail) )
  {
    Level_GetUniqueQTaskNameFromTask(igi2_frame.zName, ptQTask);
    BYTE2(ptQTask[4].tQTaskRefList.ptTail) = 0;
    sprintf(igi2_frame.zTemp, "%s.nActive", igi2_frame.zName);
    Symbol_Remove(igi2_frame.zTemp);
    sprintf(igi2_frame.zTemp, "%s.nClientID", igi2_frame.zName);
    Symbol_Remove(igi2_frame.zTemp);
  }
}

// source: h/2/areaactivateqtask.c:241  [anchor-mhash]
void __cdecl AreaActivateQTask_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { float v19; };
    struct { char igi2_o1[4]; struct real64x3_t tCorner; };
    struct { char igi2_o2[28]; struct real64x3_t tMax; };
    struct { char igi2_o3[52]; struct real64x3_t tMin; };
    struct { char igi2_o4[76]; struct QTask_s *ptHead; };
    struct { char igi2_o5[80]; struct QReference_s *v24; };
    struct { char igi2_o6[84]; float v25; };
    struct { char igi2_o7[88]; float v26; };
    struct { char igi2_o8[92]; struct QReference_s *v27; };
    struct { char igi2_o9[96]; float v28; };
    struct { char igi2_o10[100]; float v29; };
    struct { char igi2_o11[104]; struct QTask_s *ptNext; };
    struct { char igi2_o12[108]; float v31; };
    struct { char igi2_o13[112]; struct QTask_s *ptPrev; };
    struct { char igi2_o14[116]; float v33; };
    struct { char igi2_o15[120]; float v34; };
    struct { char igi2_o16[124]; struct real64x3_t Real64x3_Rotate_tTemp; };
    char igi2_extent[148];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QReference_s *ptMiddle; // edx
  struct QTask_s *v3; // ecx
  double v4; // st7
  struct QTask_s *ptParent; // ecx
  double v6; // st6
  struct QTask_s *ptTail; // ecx
  int v8; // edx
  double v9; // st5
  float v10; // eax
  struct QTask_s *v11; // eax
  double v12; // st7
  double v13; // st6
  double v14; // st5
  double vZ; // st4
  double v16; // st3
  double v17; // st3
  double v18; // st2

  ptMiddle = ptQTask[4].tQTaskRefList.ptMiddle;
  igi2_frame.tMin.vX = 1.7976931348623157e+308;
  igi2_frame.tMin.vY = 1.7976931348623157e+308;
  igi2_frame.tMin.vZ = 1.7976931348623157e+308;
  igi2_frame.tMax.vX = -1.7976931348623157e+308;
  igi2_frame.tMax.vY = -1.7976931348623157e+308;
  igi2_frame.tMax.vZ = -1.7976931348623157e+308;
  ptQTask[4].tQTaskRefList.ptHead = nullptr;
  if ( ptMiddle )
    ptQTask[4].tQTaskRefList.ptHead = (struct QReference_s *)Script_ParseLineInt32((char *)ptMiddle);
  ptQTask[3].ptParent = ptQTask[4].ptPrev;
  v3 = ptQTask[4].tQTaskChildren.ptMiddle;
  *(_DWORD *)&ptQTask[3].eQTaskType = ptQTask[4].tQTaskChildren.ptHead;
  ptQTask[4].ptNext = v3;
  v4 = *(float *)&ptQTask[3].ptParent * 0.5;
  igi2_frame.ptNext = ptQTask[3].ptNext;
  ptParent = ptQTask[2].ptParent;
  *(float *)&ptQTask[3].ptParent = v4;
  igi2_frame.v26 = *(float *)&ptParent;
  v6 = *(float *)&ptQTask[3].eQTaskType * 0.5;
  igi2_frame.ptHead = ptQTask[3].tQTaskChildren.ptHead;
  igi2_frame.v24 = ptQTask[3].tQTaskRefList.ptMiddle;
  ptTail = ptQTask[3].tQTaskChildren.ptTail;
  *(float *)&ptQTask[3].eQTaskType = v6;
  v8 = 0;
  v9 = *(float *)&ptQTask[4].ptNext * 0.5;
  igi2_frame.v25 = *(float *)&ptTail;
  igi2_frame.v19 = v9;
  *(float *)&ptQTask[4].ptNext = v9;
  igi2_frame.v31 = igi2_frame.v19;
  v10 = *(float *)&ptQTask[2].eQTaskType;
  igi2_frame.v28 = v4;
  igi2_frame.v33 = v10;
  v11 = ptQTask[3].tQTaskChildren.ptMiddle;
  igi2_frame.v29 = v6;
  v12 = *(double *)&ptQTask[2].tQTaskChildren.ptHead;
  igi2_frame.v34 = *(float *)&v11;
  v13 = *(double *)&ptQTask[2].tQTaskChildren.ptTail;
  v14 = *(double *)&ptQTask[2].tQTaskRefList.ptMiddle;
  igi2_frame.ptPrev = ptQTask[3].ptPrev;
  vZ = igi2_frame.tMax.vZ;
  igi2_frame.v27 = ptQTask[3].tQTaskRefList.ptHead;
  do
  {
    v16 = (double)(1 - 2 * (v8 & 1)) * igi2_frame.v28;
    igi2_frame.tCorner.vY = (double)(1 - (v8 & 2)) * igi2_frame.v29;
    igi2_frame.tCorner.vZ = (double)(1 - ((v8 >> 1) & 2)) * igi2_frame.v31;
    igi2_frame.Real64x3_Rotate_tTemp.vX = igi2_frame.v33 * igi2_frame.tCorner.vY + *(float *)&igi2_frame.ptNext * igi2_frame.tCorner.vZ + igi2_frame.v26 * v16;
    igi2_frame.Real64x3_Rotate_tTemp.vY = igi2_frame.v34 * igi2_frame.tCorner.vZ + *(float *)&igi2_frame.ptHead * igi2_frame.tCorner.vY + *(float *)&igi2_frame.ptPrev * v16;
    igi2_frame.Real64x3_Rotate_tTemp.vZ = *(float *)&igi2_frame.v24 * igi2_frame.tCorner.vZ + igi2_frame.v25 * v16 + *(float *)&igi2_frame.v27 * igi2_frame.tCorner.vY;
    qmemcpy(&igi2_frame.tCorner, &igi2_frame.Real64x3_Rotate_tTemp, sizeof(igi2_frame.tCorner));
    v17 = v12 + igi2_frame.Real64x3_Rotate_tTemp.vX;
    v18 = v13 + igi2_frame.tCorner.vY;
    igi2_frame.tCorner.vY = v13 + igi2_frame.tCorner.vY;
    igi2_frame.tCorner.vZ = v14 + igi2_frame.tCorner.vZ;
    if ( igi2_frame.tMin.vX >= v12 + igi2_frame.Real64x3_Rotate_tTemp.vX )
      igi2_frame.tMin.vX = v17;
    if ( igi2_frame.tMin.vY >= v18 )
      igi2_frame.tMin.vY = v18;
    if ( igi2_frame.tMin.vZ >= igi2_frame.tCorner.vZ )
      igi2_frame.tMin.vZ = igi2_frame.tCorner.vZ;
    if ( igi2_frame.tMax.vX <= v17 )
      igi2_frame.tMax.vX = v17;
    if ( igi2_frame.tMax.vY <= igi2_frame.tCorner.vY )
      igi2_frame.tMax.vY = igi2_frame.tCorner.vY;
    if ( vZ <= igi2_frame.tCorner.vZ )
      vZ = igi2_frame.tCorner.vZ;
    ++v8;
  }
  while ( v8 < 8 );
  igi2_frame.tMax.vZ = vZ;
  qmemcpy(&ptQTask[1], &igi2_frame.tMin, 0x18u);
  qmemcpy(&ptQTask[1].tQTaskRefList.ptMiddle, &igi2_frame.tMax, 0x18u);
}

// source: h/2/areaactivateqtask.c:332  [size]
void __cdecl AreaActivateQTask_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = AreaActivateQTask_ptParameterList;
}

// source: h/2/areaactivateqtask.c:348  [anchor-mhash]
void __cdecl AreaActivateQTask_RunHandler(struct QTask_s *ptQTask)
{
  char v1; // di
  struct QTask_s *v2; // ebx
  void (__cdecl **p_pfAreaActivateCB)(struct AreaActivateContext_s *); // esi
  struct QTask_s *ptHead; // ecx
  int v5; // edx
  struct QTask_s *v6; // eax
  void (__cdecl *pfHandler)(struct QTask_s *); // eax
  int v8; // edx
  struct AreaActivateContext_s tContext; // [esp+10h] [ebp-Ch] BYREF

  v1 = 0;
  v2 = nullptr;
  tContext.ptAreaActivateQTask = ptQTask;
  tContext.nHitCount = 0;
  p_pfAreaActivateCB = &AreaActivate_atCriteria[0].pfAreaActivateCB;
  do
  {
    if ( ((1 << v1) & (int)ptQTask[4].tQTaskRefList.ptHead) != 0 )
    {
      (*p_pfAreaActivateCB)(&tContext);
      v2 = (struct QTask_s *)((char *)v2 + tContext.nHitCount);
      if ( tContext.nHitCount > 0 )
        ptQTask[4].ptParent = (struct QTask_s *)tContext.nClientID;
      tContext.nHitCount = 0;
    }
    p_pfAreaActivateCB += 3;
    ++v1;
  }
  while ( (int)p_pfAreaActivateCB < 129476436 );
  if ( !HIBYTE(ptQTask[4].tQTaskRefList.ptTail) )
    ptQTask[4].tQTaskChildren.ptTail = v2;
  ptHead = ptQTask->tQTaskChildren.ptHead;
  if ( ptHead->ptNext && ptHead )
  {
    v5 = QTask_nProtectedQTaskStackOffset;
    do
    {
      if ( ptHead->ptNext )
        v6 = ptHead->ptNext->ptNext != nullptr ? ptHead->ptNext : nullptr;
      else
        v6 = nullptr;
      QTask_atProtectedQTaskStack[v5].ptQTask = v6;
      pfHandler = (void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[1][ptHead->eQTaskType].pfHandler;
      v8 = v5 + 1;
      QTask_nProtectedQTaskStackOffset = v8;
      if ( pfHandler )
      {
        pfHandler(ptHead);
        v8 = QTask_nProtectedQTaskStackOffset;
      }
      ptHead = (struct QTask_s *)dword_849C7DC[v8];
      v5 = v8 - 1;
      QTask_nProtectedQTaskStackOffset = v5;
    }
    while ( ptHead );
  }
}

// source: h/2/areaactivateqtask.c:399  [anchor-mhash]
void __cdecl AreaActivateQTask_DeleteHandler(struct QTask_s *ptQTask)
{
  int v1; // ecx
  struct QReference_s *v2; // eax
  struct QReference_s *ptMiddle; // eax
  int v4; // esi

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
      goto LABEL_8;
  }
  if ( v1 >= 0 )
    ((void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[Level_eRemoveLevelScriptSymbolsEvent][ptQTask->eQTaskType].pfHandler)(ptQTask);
LABEL_8:
  ptMiddle = ptQTask[4].tQTaskRefList.ptMiddle;
  if ( ptMiddle )
  {
    v4 = *(_DWORD *)((unsigned int)&ptMiddle[-1].pxObject & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v4);
    memset(*(void **)(v4 + 8), 0xCDu, *(_DWORD *)(v4 + 16));
    free((void *)v4);
    ptQTask[4].tQTaskRefList.ptMiddle = nullptr;
  }
}

// source: h/2/areaactivateqtask.c:432  [size]
void __cdecl AreaActivateQTask_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  BYTE2(ptQTask[4].tQTaskRefList.ptTail) = 0;
  ptQTask[4].tQTaskChildren.ptTail = nullptr;
  ptQTask[4].ptParent = nullptr;
  ptQTask[4].tQTaskRefList.ptHead = nullptr;
  ptQTask[4].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[4].ptPrev = (struct QTask_s *)1166016512;
  ptQTask[4].tQTaskChildren.ptHead = (struct QTask_s *)1166016512;
  ptQTask[4].tQTaskChildren.ptMiddle = (struct QTask_s *)1166016512;
}

// source: h/2/areaactivateqtask.c:475  [anchor-mhash]
char __cdecl AreaActivateQTask_IsInsideArea(
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
  Real32x3_RotateInverse_tTemp = v4 * *(float *)&ptQTask[3].tQTaskChildren.ptTail
                               + v3 * *(float *)&ptQTask[3].ptPrev
                               + v2 * *(float *)&ptQTask[2].ptParent;
  Real32x3_RotateInverse_tTemp_4 = v4 * *(float *)&ptQTask[3].tQTaskRefList.ptHead
                                 + v3 * *(float *)&ptQTask[3].tQTaskChildren.ptHead
                                 + v2 * *(float *)&ptQTask[2].eQTaskType;
  Real32x3_RotateInverse_tTemp_8 = v4 * *(float *)&ptQTask[3].tQTaskRefList.ptMiddle
                                 + v3 * *(float *)&ptQTask[3].tQTaskChildren.ptMiddle
                                 + v2 * *(float *)&ptQTask[3].ptNext;
  return Real32x3_RotateInverse_tTemp <= (double)*(float *)&ptQTask[3].ptParent
      && Real32x3_RotateInverse_tTemp_4 <= (double)*(float *)&ptQTask[3].eQTaskType
      && Real32x3_RotateInverse_tTemp_8 <= (double)*(float *)&ptQTask[4].ptNext
      && -*(float *)&ptQTask[3].ptParent <= Real32x3_RotateInverse_tTemp
      && -*(float *)&ptQTask[3].eQTaskType <= Real32x3_RotateInverse_tTemp_4
      && -*(float *)&ptQTask[4].ptNext <= Real32x3_RotateInverse_tTemp_8;
}

// source: h/2/areaactivateqtask.c:527  [anchor-mhash]
void __cdecl AreaActivateQTask_GetCameraTargetInfoHandler(struct QTask_s *ptQTask, void *pxContext)
{
  char *v2; // eax

  qmemcpy(pxContext, &ptQTask[2].tQTaskChildren, 0x18u);
  *((_DWORD *)pxContext + 6) = 0;
  *((_DWORD *)pxContext + 7) = 0;
  *((_DWORD *)pxContext + 8) = 0;
  qmemcpy((char *)pxContext + 36, &ptQTask[2].ptParent, 0x28u);
  *((_DWORD *)pxContext + 19) = ptQTask[4].ptPrev;
  v2 = *((char **)pxContext + 20);
  if ( v2 )
    strcpy(v2, "AreaActivate Task");
}

// source: h/2/areaactivateqtask.c:565  [anchor-hash]
void __cdecl AreaActivateQTask_Open()
{
  __int16 v0; // ax
  unsigned __int16 v1; // si
  struct ParameterList_s *v2; // eax
  struct ParameterList_s *v3; // eax
  int v4; // edx

  AreaActivateQTask_eQTaskType = QTask_NewQTaskType("AreaActivate", 200, EditorRigidObj_eQTaskType, 0, 0);
  v0 = QTask_NewQTaskEventFn(0, "AreaActivate");
  v1 = AreaActivateQTask_eQTaskType;
  AreaActivateQTask_eQTaskEvent = v0;
  QTask_LinkQTaskEventHandlerFn(
    AreaActivateQTask_eQTaskType,
    0,
    (void (__cdecl *)(struct QTask_s *, void *))AreaActivateQTask_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 2, AreaActivateQTask_DeleteHandler);
  QTask_LinkQTaskEventHandlerFn(
    v1,
    ParameterList_eUpdateInternalDataQTaskEvent,
    AreaActivateQTask_UpdateInternalDataHandler);
  QTask_LinkQTaskEventHandlerFn(
    v1,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))AreaActivateQTask_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 1, AreaActivateQTask_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(
    v1,
    Level_eRegisterLevelScriptSymbolsEvent,
    AreaActivateQTask_RegisterScriptSymbolsHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(
    v1,
    Level_eRemoveLevelScriptSymbolsEvent,
    AreaActivateQTask_RemoveScriptSymbolsHandler);
  QTask_LinkQTaskEventHandlerFn(v1, 8, AreaActivateQTask_GetCameraTargetInfoHandler);
  v2 = (struct ParameterList_s *)Mem_AllocFn(92, 4);
  v2->ptParameterListItem = (struct ParameterListItem_s *)&v2[1];
  v2->nParameters = 0;
  v2->nMaxParameters = 4;
  AreaActivateQTask_ptParameterList = v2;
  ParameterList_AddParameter(v2, 0x58u, Level_eParameterTypeObjectPos, "Position", 7u, nullptr);
  ParameterList_AddParameter(
    AreaActivateQTask_ptParameterList,
    0x70u,
    Level_eParameterTypeReal32x9,
    "Orientation",
    7u,
    nullptr);
  ParameterList_AddParameter(
    AreaActivateQTask_ptParameterList,
    0xA4u,
    Level_eParameterTypeReal32x3,
    "Dimensions",
    7u,
    nullptr);
  ParameterList_AddParameter(
    AreaActivateQTask_ptParameterList,
    0xB8u,
    Level_eParameterTypeVarString,
    "Criteria",
    7u,
    nullptr);
  Symbol_Register(
    "AreaActivate_IdInArea",
    AreaActivateQTask_IdInAreaCB,
    nullptr,
    2,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  QTask_LinkQTaskEventHandlerFn(
    AreaActivateQTask_eQTaskType,
    Serialize_eGetSerializeParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))sub_5AC3D0);
  v3 = (struct ParameterList_s *)Mem_AllocFn(32, 4);
  v4 = Level_eParameterTypeInt32;
  v3->ptParameterListItem = (struct ParameterListItem_s *)&v3[1];
  v3->nParameters = 0;
  v3->nMaxParameters = 1;
  dword_7B7A74C = (int)v3;
  ParameterList_AddParameter(v3, 0xB0u, v4, "nActive", 7u, nullptr);
}

// source: h/2/areaactivateqtask.c:606  [anchor-hash]
void __cdecl AreaActivateQTask_Close()
{
  int v0; // esi
  int v1; // esi

  Symbol_Remove("AreaActivate_IdInArea");
  if ( AreaActivateQTask_ptParameterList )
  {
    v0 = *(_DWORD *)((unsigned int)&AreaActivateQTask_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
  if ( dword_7B7A74C )
  {
    v1 = *(_DWORD *)((dword_7B7A74C - 4) & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v1);
    memset(*(void **)(v1 + 8), 0xCDu, *(_DWORD *)(v1 + 16));
    free((void *)v1);
  }
  QTask_DeleteQTaskEvent(AreaActivateQTask_eQTaskEvent);
  AreaActivateQTask_eQTaskEvent = 512;
  QTask_DeleteQTaskType(AreaActivateQTask_eQTaskType);
  AreaActivateQTask_eQTaskType = 512;
}

// source: h/2/areaactivateqtask.c:642  [size]
unsigned __int16 __cdecl AreaActivateQTask_GetQTaskType()
{
  return AreaActivateQTask_eQTaskType;
}

// source: h/2/areaactivateqtask.c:655  [size]
__int16 __cdecl AreaActivateQTask_GetQTaskEvent()
{
  return AreaActivateQTask_eQTaskEvent;
}

// source: h/2/areaactivateqtask.c:670  [anchor-strings]
int __cdecl AreaActivateQTask_RegisterCriteria(
        char *zName,
        void (__cdecl *pfAreaActivateCB)(struct AreaActivateContext_s *))
{
  int v3; // ecx
  struct AreaActivateCriteria_s *v4; // eax
  int v5; // esi
  int v6; // eax

  v3 = 0;
  v4 = AreaActivate_atCriteria;
  while ( v4->isUsed )
  {
    ++v4;
    ++v3;
    if ( (int)v4 >= 129476428 )
    {
      LDebug_Error("Unable to register AreaActivate criteria");
      abort();
    }
  }
  v5 = 1 << v3;
  v6 = v3;
  AreaActivate_atCriteria[v6].isUsed = 1;
  AreaActivate_atCriteria[v6].zName = zName;
  AreaActivate_atCriteria[v6].pfAreaActivateCB = pfAreaActivateCB;
  Symbol_Register(
    zName,
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)(1 << v3),
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  return v5;
}

// source: h/2/areaactivateqtask.c:704  [anchor-mhash]
void __cdecl AreaActivateQTask_RemoveCriteria(int iCriteriaMask)
{
  int i; // eax
  int v2; // eax

  for ( i = 0; (iCriteriaMask & 1) == 0; ++i )
    iCriteriaMask >>= 1;
  v2 = i;
  AreaActivate_atCriteria[v2].isUsed = 0;
  Symbol_Remove(AreaActivate_atCriteria[v2].zName);
}

// source: h/2/areaactivateqtask.c:740  [size]
int __cdecl AreaActivate_GetCriteria(struct QTask_s *ptQTask)
{
  return (int)ptQTask[4].tQTaskRefList.ptHead;
}

// source: h/2/areaactivateqtask.c:758  [size]
int __cdecl AreaActivateQTask_GetNumberOfActive(struct QTask_s *ptQTask)
{
  return (int)ptQTask[4].tQTaskChildren.ptTail;
}

// source: h/2/areaactivateqtask.c:778  [size]
struct QTask_s *__cdecl AreaActivateQTask_SetNumberOfActive(
        struct QTask_s *ptQTask,
        int nActive,
        int nClientID)
{
  ptQTask[4].tQTaskChildren.ptTail = (struct QTask_s *)nActive;
  ptQTask[4].ptParent = (struct QTask_s *)nClientID;
  return ptQTask;
}

// source: h/2/areaactivateqtask.c:798  [size]
void __cdecl AreaActivateQTask_DisableDetection(
        struct QTask_s *ptQTask,
        enum bool isDisable)
{
  HIBYTE(ptQTask[4].tQTaskRefList.ptTail) = isDisable;
}
