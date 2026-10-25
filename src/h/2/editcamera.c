/* h/2/editcamera.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: h/2/editcamera.c:48  [anchor-hash]
struct QCamera_s *__cdecl EditCamera_GetQCamera(struct QTask_s *ptQTask)
{
  struct QTask_s *FirstParentOfType; // eax

  FirstParentOfType = QTask_GetFirstParentOfType(ptQTask, CutScene_eQTaskType);
  if ( FirstParentOfType )
    return (struct QCamera_s *)FirstParentOfType[15].tQTaskChildren.ptHead;
  else
    return nullptr;
}

// source: h/2/editcamera.c:72  [anchor-mhash]
struct QTask_s *__cdecl EditCamera_GetLastQTask(struct QTask_s *ptQTask, char isTopLevel)
{
  unsigned __int16 i; // dx
  bool v5; // zf
  struct QTask_s *result; // eax

  for ( i = EditCamera_eQTaskType; ; ptQTask = QTask_GetFirstChildOfType(ptQTask, i) )
  {
    while ( !isTopLevel && QTask_GetNextSiblingOfType(ptQTask, i) )
      ptQTask = QTask_GetNextSiblingOfType(ptQTask, i);
    v5 = QTask_GetFirstChildOfType(ptQTask, i) == nullptr;
    result = ptQTask;
    if ( v5 )
      break;
    isTopLevel = 0;
  }
  return result;
}

// source: h/2/editcamera.c:171  [anchor-strings]
void __cdecl EditCamera_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ptQTask[3].tQTaskRefList.ptTail = (struct QReference_s *)-1;
  ptQTask[3].ptParent = (struct QTask_s *)-1;
  ptQTask[3].eQTaskType = 257;
  ptQTask[3].isInMemPool = 1;
  ptQTask[1].ptNext = nullptr;
  ptQTask[1].ptPrev = nullptr;
  ptQTask[1].tQTaskChildren.ptHead = nullptr;
  ptQTask[1].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[1].tQTaskChildren.ptTail = nullptr;
  ptQTask[1].tQTaskRefList.ptHead = nullptr;
  LOBYTE(ptQTask[4].tQTaskChildren.ptTail) = 0;
  ptQTask[1].tQTaskRefList.ptTail = nullptr;
  ptQTask[1].ptParent = nullptr;
  *(_DWORD *)&ptQTask[1].eQTaskType = 0;
  ptQTask[1].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[3].tQTaskRefList.ptMiddle = (struct QReference_s *)1065353216;
  ptQTask[4].ptNext = (struct QTask_s *)-1082130432;
  ptQTask[4].ptPrev = nullptr;
  ptQTask[4].tQTaskChildren.ptHead = nullptr;
  ptQTask[4].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[5].tQTaskChildren.ptTail = (struct QTask_s *)1056964608;
  ptQTask[5].tQTaskRefList.ptHead = nullptr;
  ptQTask[5].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[5].tQTaskRefList.ptTail = nullptr;
  ptQTask[5].ptParent = nullptr;
  strcpy((char *)&ptQTask[4].tQTaskChildren.ptTail + 1, "CAMERAFILTER_TYPE_NONE");
  ptQTask[5].tQTaskChildren.ptMiddle = nullptr;
}

// source: h/2/editcamera.c:282  [anchor-mhash]
void __cdecl EditCamera_DeleteHandler(struct QTask_s *ptQTask)
{
  int v1; // ecx
  struct QReference_s *v2; // eax
  void (__cdecl *pfHandler)(struct QTask_s *); // eax
  struct QTask_s *ptPrev; // eax
  struct QTask_s *ptHead; // eax
  struct QTask_s *v6; // eax
  struct QTask_s *v7; // eax
  struct QTask_s *ptMiddle; // eax
  struct QTask_s *v9; // eax

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
  ptPrev = ptQTask[4].ptPrev;
  if ( ptPrev )
  {
    ptHead = ptPrev->tQTaskChildren.ptHead;
    if ( ptHead )
      QTask_Delete(ptHead);
    QReference_Delete((struct QReference_s *)ptQTask[4].ptPrev, &QTask_tQTaskRefPool);
  }
  v6 = ptQTask[4].tQTaskChildren.ptHead;
  if ( v6 )
  {
    v7 = v6->tQTaskChildren.ptHead;
    if ( v7 )
      QTask_Delete(v7);
    QReference_Delete((struct QReference_s *)ptQTask[4].tQTaskChildren.ptHead, &QTask_tQTaskRefPool);
  }
  ptMiddle = ptQTask[4].tQTaskChildren.ptMiddle;
  if ( ptMiddle )
  {
    v9 = ptMiddle->tQTaskChildren.ptHead;
    if ( v9 )
      QTask_Delete(v9);
    QReference_Delete((struct QReference_s *)ptQTask[4].tQTaskChildren.ptMiddle, &QTask_tQTaskRefPool);
  }
}

// source: h/2/editcamera.c:346  [size]
void __cdecl EditCamera_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = EditCamera_ptParameterList;
}

// source: h/2/editcamera.c:445  [size]
void __cdecl EditCamera_RunHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptHead; // ecx
  int v2; // edx
  struct QTask_s *v3; // eax
  void (__cdecl *pfHandler)(struct QTask_s *); // eax
  int v5; // edx

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
}

// source: h/2/editcamera.c:461  [anchor-mhash]
void __cdecl EditCamera_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *v2; // eax
  bool v3; // c0
  bool v4; // c3
  double v5; // st7
  struct QTask_s *ptParent; // eax
  struct QReference_s *v7; // eax
  struct QTask_s *pxObject; // ecx
  struct QReference_s *ptTail; // eax
  struct QReference_s *v10; // eax
  unsigned __int16 *v11; // esi
  int v12; // eax
  void (__cdecl *pfHandler)(unsigned __int16 *, void *); // eax
  int v14; // eax
  struct QTask_s *ptHead; // eax
  int v16; // edx
  struct QTask_s *v17; // ecx
  void (__cdecl *v18)(struct QTask_s *, _DWORD); // ecx
  int v19; // edx
  struct GetCameraTargetInfoContext_s tGetCameraTargetInfoContext; // [esp+Ch] [ebp-58h] BYREF

  v2 = (struct QTask_s *)Script_ParseLineInt32((char *)&ptQTask[4].tQTaskChildren.ptTail + 1);
  v3 = *(float *)&ptQTask[3].tQTaskRefList.ptMiddle > 0.0010000000474974513;
  v4 = 0.0010000000474974513 == *(float *)&ptQTask[3].tQTaskRefList.ptMiddle;
  ptQTask[5].tQTaskChildren.ptMiddle = v2;
  if ( v3 || v4 )
  {
    if ( *(float *)&ptQTask[3].tQTaskRefList.ptMiddle <= 3.0 )
      v5 = *(float *)&ptQTask[3].tQTaskRefList.ptMiddle;
    else
      v5 = 3.0;
  }
  else
  {
    v5 = 0.0010000000474974513;
  }
  ptParent = ptQTask[3].ptParent;
  *(float *)&ptQTask[3].tQTaskRefList.ptMiddle = v5;
  if ( (unsigned int)ptParent < 0x1000 && (v7 = Level_atLevelQTaskID[(_DWORD)ptParent]) != nullptr )
    pxObject = (struct QTask_s *)v7->pxObject;
  else
    pxObject = nullptr;
  ptTail = ptQTask[3].tQTaskRefList.ptTail;
  if ( (unsigned int)ptTail < 0x1000 && (v10 = Level_atLevelQTaskID[(_DWORD)ptTail]) != nullptr )
    v11 = (unsigned __int16 *)v10->pxObject;
  else
    v11 = nullptr;
  if ( pxObject == ptQTask )
    ptQTask[3].ptParent = (struct QTask_s *)-1;
  ptQTask[2].ptNext = nullptr;
  ptQTask[2].ptPrev = nullptr;
  ptQTask[2].tQTaskChildren.ptHead = nullptr;
  ptQTask[2].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[2].tQTaskChildren.ptTail = nullptr;
  ptQTask[2].tQTaskRefList.ptHead = nullptr;
  ptQTask[2].tQTaskRefList.ptMiddle = (struct QReference_s *)1065353216;
  ptQTask[2].tQTaskRefList.ptTail = nullptr;
  ptQTask[2].ptParent = nullptr;
  *(_DWORD *)&ptQTask[2].eQTaskType = 0;
  ptQTask[3].ptNext = (struct QTask_s *)1065353216;
  ptQTask[3].ptPrev = nullptr;
  ptQTask[3].tQTaskChildren.ptHead = nullptr;
  ptQTask[3].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[3].tQTaskChildren.ptTail = (struct QTask_s *)1065353216;
  ptQTask[3].tQTaskRefList.ptHead = nullptr;
  if ( v11 )
  {
    v12 = v11[18];
    if ( QTask_aatQTaskFinalEvent[8][v12].pfHandler )
    {
      pfHandler = (void (__cdecl *)(unsigned __int16 *, void *))QTask_aatQTaskFinalEvent[ParameterList_eUpdateInternalDataQTaskEvent][v12].pfHandler;
      if ( pfHandler )
        pfHandler(v11, pxContext);
      v14 = v11[18];
      tGetCameraTargetInfoContext.zName = nullptr;
      ((void (__cdecl *)(unsigned __int16 *, struct GetCameraTargetInfoContext_s *))QTask_aatQTaskFinalEvent[8][v14].pfHandler)(
        v11,
        &tGetCameraTargetInfoContext);
      qmemcpy(&ptQTask[2], &tGetCameraTargetInfoContext, 0x18u);
      qmemcpy(&ptQTask[2].tQTaskRefList.ptMiddle, &tGetCameraTargetInfoContext.tOrientation, sizeof(struct QTask_s));
    }
    else
    {
      ptQTask[3].tQTaskRefList.ptTail = (struct QReference_s *)-1;
    }
  }
  if ( !pxContext || !*(_DWORD *)pxContext )
  {
    ptHead = ptQTask->tQTaskChildren.ptHead;
    if ( ptHead->ptNext )
    {
      if ( ptHead )
      {
        v16 = QTask_nProtectedQTaskStackOffset;
        do
        {
          if ( ptHead->ptNext )
            v17 = ptHead->ptNext->ptNext != nullptr ? ptHead->ptNext : nullptr;
          else
            v17 = nullptr;
          QTask_atProtectedQTaskStack[v16].ptQTask = v17;
          v18 = (void (__cdecl *)(struct QTask_s *, _DWORD))QTask_aatQTaskFinalEvent[ParameterList_eUpdateInternalDataQTaskEvent][ptHead->eQTaskType].pfHandler;
          v19 = v16 + 1;
          QTask_nProtectedQTaskStackOffset = v19;
          if ( v18 )
          {
            v18(ptHead, 0);
            v19 = QTask_nProtectedQTaskStackOffset;
          }
          ptHead = (struct QTask_s *)dword_849C7DC[v19];
          v16 = v19 - 1;
          QTask_nProtectedQTaskStackOffset = v16;
        }
        while ( ptHead );
      }
    }
  }
}

// source: h/2/editcamera.c:690  [anchor-hash]
void __cdecl EditCamera_Open()
{
  _DWORD *v0; // esi
  struct ParameterList_s *v1; // eax
  int v2; // edx

  EditCamera_tFilterEnumList.pfEnumItemsCallback = ParameterEnumList_EnumerateItemsCallback;
  EditCamera_tFilterEnumList.ptHead = (struct ParameterEnumItem_s *)&EditCamera_tFilterEnumList.ptMiddle;
  EditCamera_tFilterEnumList.ptTail = (struct ParameterEnumItem_s *)&EditCamera_tFilterEnumList;
  EditCamera_tFilterEnumList.ptMiddle = nullptr;
  v0 = Mem_AllocFn(18444, 4);
  v0[1] = 0;
  *v0 = 0;
  v0[4610] = "CAMERAFILTER_TYPE_.*";
  Wildcard_CreateNFA("CAMERAFILTER_TYPE_.*", v0 + 2, (char *)v0 + 10248);
  List_AddTail(v0, (int)&EditCamera_tFilterEnumList);
  EditCamera_ptLODVirModel = MTP_GetLODVirModel("1717_01_1");
  LOWORD(v0) = QTask_NewQTaskType("EditCamera", 240, EditorRigidObj_eQTaskType, 0, 0);
  EditCamera_eQTaskType = (unsigned __int16)v0;
  QTask_LinkQTaskEventHandlerFn(
    (unsigned __int16)v0,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveHandler);
  QTask_LinkQTaskEventHandlerFn((unsigned __int16)v0, 0, EditCamera_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn((unsigned __int16)v0, 2, EditCamera_DeleteHandler);
  QTask_LinkQTaskEventHandlerFn(
    (unsigned __int16)v0,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))EditCamera_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(
    (unsigned __int16)v0,
    ParameterList_eUpdateInternalDataQTaskEvent,
    EditCamera_UpdateInternalDataHandler);
  QTask_LinkQTaskEventHandlerFn((unsigned __int16)v0, 10, nullptr);
  QTask_LinkQTaskEventHandlerFn((unsigned __int16)v0, 9, nullptr);
  QTask_LinkQTaskEventHandlerNoContextFn((unsigned __int16)v0, 1, EditCamera_RunHandler);
  QTask_LinkQTaskEventHandlerFn((unsigned __int16)v0, DynCubeObj_eDynCubeObjRegisterQTaskEvent, nullptr);
  QTask_LinkQTaskEventHandlerFn((unsigned __int16)v0, DynCubeObj_eDynCubeObjRemoveQTaskEvent, nullptr);
  QTask_LinkQTaskEventHandlerFn((unsigned __int16)v0, 5, nullptr);
  v1 = (struct ParameterList_s *)Mem_AllocFn(352, 4);
  v2 = Level_eParameterTypeObjectPos;
  v1->nParameters = 0;
  v1->nMaxParameters = 17;
  v1->ptParameterListItem = (struct ParameterListItem_s *)&v1[1];
  EditCamera_ptParameterList = v1;
  dword_7B77D30 = 0;
  dword_7B77D34 = 0;
  dword_7B77D38 = 0;
  dword_7B77D3C = 1072693248;
  dword_7B77D18 = 0;
  dword_7B77D1C = 0;
  dword_7B77D20 = 0;
  dword_7B77D24 = 1072693248;
  ParameterList_AddParameter(v1, 0x28u, v2, "Position", 7u, nullptr);
  ParameterList_AddParameter(EditCamera_ptParameterList, 0x44u, Level_eParameterTypeAngle, "Alpha", 7u, nullptr);
  ParameterList_AddParameter(EditCamera_ptParameterList, 0x48u, Level_eParameterTypeAngle, "Beta", 7u, nullptr);
  ParameterList_AddParameter(EditCamera_ptParameterList, 0x4Cu, Level_eParameterTypeAngle, "Gamma", 7u, nullptr);
  ParameterList_AddParameter(EditCamera_ptParameterList, 0x90u, Level_eParameterTypeReal32, dword_687204, 7u, nullptr);
  ParameterList_AddParameter(EditCamera_ptParameterList, 0x40u, Level_eParameterTypeReal32, "Duration", 7u, nullptr);
  ParameterList_AddParameter(EditCamera_ptParameterList, 0x94u, Level_eParameterTypeInt32, "Link task ID", 7u, nullptr);
  ParameterList_AddParameter(
    EditCamera_ptParameterList,
    0x9Du,
    Level_eParameterTypebool8,
    "Update link continously",
    7u,
    nullptr);
  ParameterList_AddParameter(
    EditCamera_ptParameterList,
    0x98u,
    Level_eParameterTypeInt32,
    "Target task ID",
    7u,
    nullptr);
  ParameterList_AddParameter(
    EditCamera_ptParameterList,
    0x9Eu,
    Level_eParameterTypebool8,
    "Update target continously",
    7u,
    nullptr);
  ParameterList_AddParameter(
    EditCamera_ptParameterList,
    0x9Cu,
    Level_eParameterTypebool8,
    "Smooth to next",
    7u,
    nullptr);
  ParameterList_AddParameter(
    EditCamera_ptParameterList,
    0xA0u,
    Level_eParameterTypeReal32,
    "Time of day (-1 means use default)",
    7u,
    nullptr);
  ParameterList_AddParameter(
    EditCamera_ptParameterList,
    0xB1u,
    ParameterEnumList_eParameterTypeString32,
    "FILTER",
    7u,
    &EditCamera_tFilterEnumList);
  ParameterList_AddParameter(EditCamera_ptParameterList, 0xD8u, Level_eParameterTypeReal32, "Noise", 7u, &dword_7B77D30);
  ParameterList_AddParameter(EditCamera_ptParameterList, 0xDCu, Level_eParameterTypeRGB, "Filter color", 7u, nullptr);
  ParameterList_AddParameter(
    EditCamera_ptParameterList,
    0xE8u,
    Level_eParameterTypeReal32,
    "Camera shake",
    7u,
    &dword_7B77D18);
  Symbol_Register(
    "TASKTYPE_EDITCAMERA",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)EditCamera_eQTaskType,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  QTask_SetQTaskTypeGroup(
    EditCamera_eQTaskType,
    (unsigned int)&MTP_atLODVirModel[296].atBoneVertexRefs[36].atVertexRefs[609]);
}

// source: h/2/editcamera.c:775  [size]
void __cdecl EditCamera_Close()
{
  int v0; // esi

  if ( EditCamera_ptParameterList )
  {
    v0 = *(_DWORD *)((unsigned int)&EditCamera_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
  QTask_DeleteQTaskType(EditCamera_eQTaskType);
  ParameterEnumList_DeAlloc(&EditCamera_tFilterEnumList);
}

// source: h/2/editcamera.c:794  [size]
unsigned __int16 __cdecl EditCamera_GetQTaskType()
{
  return EditCamera_eQTaskType;
}

// source: h/2/editcamera.c:809  [anchor-callee]
int __cdecl EditCamera_FollowTarget(
        struct real64x3_t *ptPos,
        struct real32x9_t *ptOrientation,
        int iTargetID)
{
  #pragma pack(push, 1)
  union
  {
    struct { float tForward_4; };
    struct { char igi2_o1[4]; float tForward_8; };
    struct { char igi2_o2[8]; float tTemp_; };
    struct { char igi2_o3[12]; float tTemp__4; };
    struct { char igi2_o4[16]; float tTemp__8; };
    struct { char igi2_o5[20]; float tUp; };
    struct { char igi2_o6[20]; float tUpa; };
    struct { char igi2_o7[24]; float tUp_4; };
    struct { char igi2_o8[24]; float tUp_4a; };
    struct { char igi2_o9[28]; float tUp_8; };
    struct { char igi2_o10[32]; float v22; };
    struct { char igi2_o11[36]; float v23; };
    struct { char igi2_o12[40]; float v24; };
    struct { char igi2_o13[44]; float tForward64; };
    struct { char igi2_o14[48]; float tForward64_4; };
    struct { char igi2_o15[52]; float tForward64_8; };
    struct { char igi2_o16[68]; struct GetCameraTargetInfoContext_s tGetCameraTargetInfoContext; };
    char igi2_extent[160];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  long double v3; // st7
  long double v4; // st6
  long double v5; // st7
  long double v6; // rt1
  long double v7; // st6
  double v8; // st6
  long double v9; // st6
  long double v10; // st3
  long double v11; // st6

  if ( (unsigned int)iTargetID >= 0x1000 )
    return iTargetID;
  iTargetID = (int)Level_atLevelQTaskID[iTargetID];
  if ( !iTargetID )
    return iTargetID;
  iTargetID = *(_DWORD *)(iTargetID + 8);
  if ( !iTargetID || !QTask_aatQTaskFinalEvent[8][*(unsigned __int16 *)(iTargetID + 36)].pfHandler )
    return iTargetID;
  igi2_frame.tGetCameraTargetInfoContext.zName = nullptr;
  ((void (__cdecl *)(int, struct GetCameraTargetInfoContext_s *))QTask_aatQTaskFinalEvent[8][*(unsigned __int16 *)(iTargetID + 36)].pfHandler)(
    iTargetID,
    &igi2_frame.tGetCameraTargetInfoContext);
  v3 = igi2_frame.tGetCameraTargetInfoContext.tPos.vX - ptPos->vX;
  igi2_frame.tForward_4 = igi2_frame.tGetCameraTargetInfoContext.tPos.vY - ptPos->vY;
  igi2_frame.tForward_8 = igi2_frame.tGetCameraTargetInfoContext.tPos.vZ - ptPos->vZ;
  if ( v3 == 0.0 )
  {
    if ( igi2_frame.tForward_4 == 0.0 && igi2_frame.tForward_8 == 0.0 )
    {
      v3 = 1.0;
      goto LABEL_13;
    }
    if ( v3 == 0.0 && igi2_frame.tForward_4 == 0.0 && igi2_frame.tForward_8 == 0.0 )
      goto LABEL_13;
  }
  v4 = v3;
  v5 = 1.0 / sqrt(v3 * v3 + igi2_frame.tForward_4 * igi2_frame.tForward_4 + igi2_frame.tForward_8 * igi2_frame.tForward_8);
  v6 = v4 * v5;
  v7 = v5;
  v3 = v6;
  igi2_frame.tForward_4 = igi2_frame.tForward_4 * v7;
  igi2_frame.tForward_8 = igi2_frame.tForward_8 * v7;
LABEL_13:
  v8 = igi2_frame.tForward_8 * 0.0;
  igi2_frame.tTemp_ = igi2_frame.tForward_4 - v8;
  igi2_frame.tForward64 = igi2_frame.tTemp_;
  igi2_frame.tTemp__4 = -(v3 - v8);
  igi2_frame.tForward64_4 = igi2_frame.tTemp__4;
  igi2_frame.tTemp__8 = 0.0 * v3 - igi2_frame.tForward_4 * 0.0;
  igi2_frame.tForward64_8 = igi2_frame.tTemp__8;
  igi2_frame.v22 = igi2_frame.tTemp__4 * igi2_frame.tForward_8 - igi2_frame.tTemp__8 * igi2_frame.tForward_4;
  igi2_frame.tUp = igi2_frame.v22;
  igi2_frame.v23 = -(igi2_frame.tTemp_ * igi2_frame.tForward_8 - igi2_frame.tTemp__8 * v3);
  igi2_frame.tUp_4 = igi2_frame.v23;
  igi2_frame.v24 = igi2_frame.tTemp_ * igi2_frame.tForward_4 - igi2_frame.tTemp__4 * v3;
  if ( igi2_frame.tTemp_ != 0.0 || igi2_frame.tTemp__4 != 0.0 || igi2_frame.tTemp__8 != 0.0 )
  {
    v9 = 1.0 / sqrt(igi2_frame.tTemp_ * igi2_frame.tTemp_ + igi2_frame.tTemp__4 * igi2_frame.tTemp__4 + igi2_frame.tTemp__8 * igi2_frame.tTemp__8);
    igi2_frame.tForward64 = igi2_frame.tTemp_ * v9;
    igi2_frame.tForward64_4 = igi2_frame.tTemp__4 * v9;
    igi2_frame.tForward64_8 = igi2_frame.tTemp__8 * v9;
  }
  if ( igi2_frame.v22 == 0.0 && igi2_frame.v23 == 0.0 && igi2_frame.v24 == 0.0 )
  {
    v11 = igi2_frame.v24;
  }
  else
  {
    v10 = sqrt(igi2_frame.v22 * igi2_frame.v22 + igi2_frame.v23 * igi2_frame.v23 + igi2_frame.v24 * igi2_frame.v24);
    igi2_frame.tUp = igi2_frame.v22 * (1.0 / v10);
    igi2_frame.tUp_4 = igi2_frame.v23 * (1.0 / v10);
    v11 = 1.0 / v10 * igi2_frame.v24;
  }
  ptOrientation->tY.vZ = igi2_frame.tForward_4;
  igi2_frame.tUpa = igi2_frame.tUp * -1.0;
  ptOrientation->tZ.vZ = igi2_frame.tForward_8;
  ptOrientation->tX.vX = igi2_frame.tForward64;
  igi2_frame.tUp_4a = igi2_frame.tUp_4 * -1.0;
  ptOrientation->tY.vX = igi2_frame.tForward64_4;
  ptOrientation->tZ.vX = igi2_frame.tForward64_8;
  ptOrientation->tX.vY = igi2_frame.tUpa;
  ptOrientation->tY.vY = igi2_frame.tUp_4a;
  igi2_frame.tUp_8 = v11 * -1.0;
  ptOrientation->tZ.vY = igi2_frame.tUp_8;
  ptOrientation->tX.vZ = v3;
  return LODWORD(igi2_frame.tUp_8);
}

// source: h/2/editcamera.c:893  [anchor-callee]
int __cdecl EditCamera_TransformRelativeToLinkQTask(
        struct real64x3_t *ptPos,
        struct real32x9_t *ptOrientation,
        struct real64x3_t *ptOriginalPos,
        struct real32x9_t *ptOriginalOrientation,
        int iLinkID)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct real64x3_t Real64x3_RotateInverse_tTemp; };
    struct { char igi2_o1[24]; float v25; };
    struct { char igi2_o2[28]; float v26; };
    struct { char igi2_o3[32]; float v27; };
    struct { char igi2_o4[40]; struct real32x9_t Real32x9_Multiply_tTemp; };
    struct { char igi2_o5[80]; struct GetCameraTargetInfoContext_s tGetCameraTargetInfoContext; };
    char igi2_extent[172];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  double v7; // st7
  double vX; // st7
  float vY; // ecx
  double v10; // st6
  double v11; // st5
  double v12; // st4
  double v13; // st3
  float vZ; // edx
  float v15; // ecx
  double v16; // st4
  int nOps; // eax
  double v18; // st3
  double v19; // st7
  double v20; // st6
  double v21; // st7
  double v22; // st7
  double v23; // st6

  if ( (unsigned int)iLinkID < 0x1000 )
  {
    iLinkID = (int)Level_atLevelQTaskID[iLinkID];
    if ( iLinkID )
    {
      iLinkID = *(_DWORD *)(iLinkID + 8);
      if ( iLinkID )
      {
        if ( QTask_aatQTaskFinalEvent[8][*(unsigned __int16 *)(iLinkID + 36)].pfHandler )
        {
          igi2_frame.tGetCameraTargetInfoContext.zName = nullptr;
          ((void (__cdecl *)(int, struct GetCameraTargetInfoContext_s *))QTask_aatQTaskFinalEvent[8][*(unsigned __int16 *)(iLinkID + 36)].pfHandler)(
            iLinkID,
            &igi2_frame.tGetCameraTargetInfoContext);
          ptPos->vX = ptPos->vX - ptOriginalPos->vX;
          ptPos->vY = ptPos->vY - ptOriginalPos->vY;
          v7 = ptPos->vZ - ptOriginalPos->vZ;
          ptPos->vZ = v7;
          igi2_frame.Real64x3_RotateInverse_tTemp.vX = ptOriginalOrientation->tZ.vX * v7
                                          + ptOriginalOrientation->tY.vX * ptPos->vY
                                          + ptOriginalOrientation->tX.vX * ptPos->vX;
          igi2_frame.Real64x3_RotateInverse_tTemp.vY = ptOriginalOrientation->tZ.vY * v7
                                          + ptOriginalOrientation->tX.vY * ptPos->vX
                                          + ptOriginalOrientation->tY.vY * ptPos->vY;
          igi2_frame.Real64x3_RotateInverse_tTemp.vZ = ptOriginalOrientation->tY.vZ * ptPos->vY
                                          + ptOriginalOrientation->tZ.vZ * v7
                                          + ptOriginalOrientation->tX.vZ * ptPos->vX;
          qmemcpy(ptPos, &igi2_frame.Real64x3_RotateInverse_tTemp, sizeof(struct real64x3_t));
          igi2_frame.Real64x3_RotateInverse_tTemp.vX = igi2_frame.tGetCameraTargetInfoContext.tOrientation.tX.vY * ptPos->vY
                                          + igi2_frame.tGetCameraTargetInfoContext.tOrientation.tX.vX * ptPos->vX
                                          + igi2_frame.tGetCameraTargetInfoContext.tOrientation.tX.vZ * ptPos->vZ;
          igi2_frame.Real64x3_RotateInverse_tTemp.vY = igi2_frame.tGetCameraTargetInfoContext.tOrientation.tY.vY * ptPos->vY
                                          + igi2_frame.tGetCameraTargetInfoContext.tOrientation.tY.vX * ptPos->vX
                                          + igi2_frame.tGetCameraTargetInfoContext.tOrientation.tY.vZ * ptPos->vZ;
          igi2_frame.Real64x3_RotateInverse_tTemp.vZ = igi2_frame.tGetCameraTargetInfoContext.tOrientation.tZ.vY * ptPos->vY
                                          + igi2_frame.tGetCameraTargetInfoContext.tOrientation.tZ.vX * ptPos->vX
                                          + igi2_frame.tGetCameraTargetInfoContext.tOrientation.tZ.vZ * ptPos->vZ;
          qmemcpy(ptPos, &igi2_frame.Real64x3_RotateInverse_tTemp, sizeof(struct real64x3_t));
          ptPos->vX = igi2_frame.tGetCameraTargetInfoContext.tPos.vX + ptPos->vX;
          ptPos->vY = igi2_frame.tGetCameraTargetInfoContext.tPos.vY + ptPos->vY;
          ptPos->vZ = igi2_frame.tGetCameraTargetInfoContext.tPos.vZ + ptPos->vZ;
          vX = ptOriginalOrientation->tX.vX;
          vY = ptOriginalOrientation->tY.vY;
          v10 = ptOriginalOrientation->tY.vX;
          HIDWORD(igi2_frame.Real64x3_RotateInverse_tTemp.vY) = LODWORD(ptOriginalOrientation->tX.vY);
          v11 = ptOriginalOrientation->tZ.vX;
          HIDWORD(igi2_frame.Real64x3_RotateInverse_tTemp.vZ) = LODWORD(ptOriginalOrientation->tZ.vY);
          v12 = vX * ptOrientation->tX.vX;
          *(float *)&igi2_frame.Real64x3_RotateInverse_tTemp.vZ = vY;
          v13 = v11 * ptOrientation->tZ.vX;
          vZ = ptOriginalOrientation->tY.vZ;
          igi2_frame.v25 = ptOriginalOrientation->tX.vZ;
          v15 = ptOriginalOrientation->tZ.vZ;
          v16 = v12 + v13;
          nOps = ptOriginalOrientation->nOps;
          igi2_frame.v26 = vZ;
          v18 = v10 * ptOrientation->tY.vX;
          igi2_frame.v27 = v15;
          igi2_frame.Real32x9_Multiply_tTemp.tX.vX = v16 + v18;
          igi2_frame.Real32x9_Multiply_tTemp.tX.vY = vX * ptOrientation->tX.vY
                                        + v11 * ptOrientation->tZ.vY
                                        + v10 * ptOrientation->tY.vY;
          igi2_frame.Real32x9_Multiply_tTemp.tX.vZ = vX * ptOrientation->tX.vZ
                                        + v11 * ptOrientation->tZ.vZ
                                        + v10 * ptOrientation->tY.vZ;
          igi2_frame.Real32x9_Multiply_tTemp.tY.vX = *((float *)&igi2_frame.Real64x3_RotateInverse_tTemp.vY + 1) * ptOrientation->tX.vX
                                        + *((float *)&igi2_frame.Real64x3_RotateInverse_tTemp.vZ + 1) * ptOrientation->tZ.vX
                                        + *(float *)&igi2_frame.Real64x3_RotateInverse_tTemp.vZ * ptOrientation->tY.vX;
          igi2_frame.Real32x9_Multiply_tTemp.tY.vY = *((float *)&igi2_frame.Real64x3_RotateInverse_tTemp.vY + 1) * ptOrientation->tX.vY
                                        + *((float *)&igi2_frame.Real64x3_RotateInverse_tTemp.vZ + 1) * ptOrientation->tZ.vY
                                        + *(float *)&igi2_frame.Real64x3_RotateInverse_tTemp.vZ * ptOrientation->tY.vY;
          igi2_frame.Real32x9_Multiply_tTemp.tY.vZ = *((float *)&igi2_frame.Real64x3_RotateInverse_tTemp.vY + 1) * ptOrientation->tX.vZ
                                        + *((float *)&igi2_frame.Real64x3_RotateInverse_tTemp.vZ + 1) * ptOrientation->tZ.vZ
                                        + *(float *)&igi2_frame.Real64x3_RotateInverse_tTemp.vZ * ptOrientation->tY.vZ;
          v19 = igi2_frame.v25 * ptOrientation->tX.vX;
          v20 = v15 * ptOrientation->tZ.vX;
          igi2_frame.Real32x9_Multiply_tTemp.nOps = nOps + ptOrientation->nOps + 1;
          igi2_frame.Real32x9_Multiply_tTemp.tZ.vX = v19 + v20 + vZ * ptOrientation->tY.vX;
          igi2_frame.Real32x9_Multiply_tTemp.tZ.vY = igi2_frame.v25 * ptOrientation->tX.vY
                                        + v15 * ptOrientation->tZ.vY
                                        + vZ * ptOrientation->tY.vY;
          igi2_frame.Real32x9_Multiply_tTemp.tZ.vZ = igi2_frame.v25 * ptOrientation->tX.vZ
                                        + v15 * ptOrientation->tZ.vZ
                                        + vZ * ptOrientation->tY.vZ;
          v21 = igi2_frame.tGetCameraTargetInfoContext.tOrientation.tX.vX;
          qmemcpy(ptOrientation, &igi2_frame.Real32x9_Multiply_tTemp, sizeof(struct real32x9_t));
          igi2_frame.Real32x9_Multiply_tTemp.tX.vX = v21 * ptOrientation->tX.vX
                                        + igi2_frame.tGetCameraTargetInfoContext.tOrientation.tX.vZ * ptOrientation->tZ.vX
                                        + igi2_frame.tGetCameraTargetInfoContext.tOrientation.tX.vY * ptOrientation->tY.vX;
          igi2_frame.Real32x9_Multiply_tTemp.tX.vY = igi2_frame.tGetCameraTargetInfoContext.tOrientation.tX.vX * ptOrientation->tX.vY
                                        + igi2_frame.tGetCameraTargetInfoContext.tOrientation.tX.vZ * ptOrientation->tZ.vY
                                        + igi2_frame.tGetCameraTargetInfoContext.tOrientation.tX.vY * ptOrientation->tY.vY;
          igi2_frame.Real32x9_Multiply_tTemp.tX.vZ = igi2_frame.tGetCameraTargetInfoContext.tOrientation.tX.vX * ptOrientation->tX.vZ
                                        + igi2_frame.tGetCameraTargetInfoContext.tOrientation.tX.vZ * ptOrientation->tZ.vZ
                                        + igi2_frame.tGetCameraTargetInfoContext.tOrientation.tX.vY * ptOrientation->tY.vZ;
          igi2_frame.Real32x9_Multiply_tTemp.tY.vX = igi2_frame.tGetCameraTargetInfoContext.tOrientation.tY.vX * ptOrientation->tX.vX
                                        + igi2_frame.tGetCameraTargetInfoContext.tOrientation.tY.vZ * ptOrientation->tZ.vX
                                        + igi2_frame.tGetCameraTargetInfoContext.tOrientation.tY.vY * ptOrientation->tY.vX;
          iLinkID = igi2_frame.tGetCameraTargetInfoContext.tOrientation.nOps + ptOrientation->nOps + 1;
          v22 = igi2_frame.tGetCameraTargetInfoContext.tOrientation.tY.vX * ptOrientation->tX.vY
              + igi2_frame.tGetCameraTargetInfoContext.tOrientation.tY.vZ * ptOrientation->tZ.vY;
          v23 = igi2_frame.tGetCameraTargetInfoContext.tOrientation.tY.vY * ptOrientation->tY.vY;
          igi2_frame.Real32x9_Multiply_tTemp.nOps = iLinkID;
          igi2_frame.Real32x9_Multiply_tTemp.tY.vY = v22 + v23;
          igi2_frame.Real32x9_Multiply_tTemp.tY.vZ = igi2_frame.tGetCameraTargetInfoContext.tOrientation.tY.vX * ptOrientation->tX.vZ
                                        + igi2_frame.tGetCameraTargetInfoContext.tOrientation.tY.vZ * ptOrientation->tZ.vZ
                                        + igi2_frame.tGetCameraTargetInfoContext.tOrientation.tY.vY * ptOrientation->tY.vZ;
          igi2_frame.Real32x9_Multiply_tTemp.tZ.vX = igi2_frame.tGetCameraTargetInfoContext.tOrientation.tZ.vX * ptOrientation->tX.vX
                                        + igi2_frame.tGetCameraTargetInfoContext.tOrientation.tZ.vZ * ptOrientation->tZ.vX
                                        + igi2_frame.tGetCameraTargetInfoContext.tOrientation.tZ.vY * ptOrientation->tY.vX;
          igi2_frame.Real32x9_Multiply_tTemp.tZ.vY = igi2_frame.tGetCameraTargetInfoContext.tOrientation.tZ.vX * ptOrientation->tX.vY
                                        + igi2_frame.tGetCameraTargetInfoContext.tOrientation.tZ.vZ * ptOrientation->tZ.vY
                                        + igi2_frame.tGetCameraTargetInfoContext.tOrientation.tZ.vY * ptOrientation->tY.vY;
          igi2_frame.Real32x9_Multiply_tTemp.tZ.vZ = igi2_frame.tGetCameraTargetInfoContext.tOrientation.tZ.vX * ptOrientation->tX.vZ
                                        + igi2_frame.tGetCameraTargetInfoContext.tOrientation.tZ.vZ * ptOrientation->tZ.vZ
                                        + igi2_frame.tGetCameraTargetInfoContext.tOrientation.tZ.vY * ptOrientation->tY.vZ;
          qmemcpy(ptOrientation, &igi2_frame.Real32x9_Multiply_tTemp, sizeof(struct real32x9_t));
        }
      }
    }
  }
  return iLinkID;
}

// source: h/2/editcamera.c:947  [size]
struct ParameterEnumItemList_s *__cdecl EditCamera_GetFilterEnumList()
{
  return &EditCamera_tFilterEnumList;
}
