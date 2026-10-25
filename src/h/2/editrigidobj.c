/* h/2/editrigidobj.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: h/2/editrigidobj.c:41  [size]
void __cdecl EditRigidObj_GetSerializeParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = EditRigidObj_ptSerializeParameterList;
}

// source: h/2/editrigidobj.c:57  [anchor-mhash]
void __cdecl EditRigidObj_SerializeHandler(struct QTask_s *ptQTask, void *pxContext)
{
  if ( QTask_GetFirstParentDerivedOfType(ptQTask, Level_eDynamicQTaskType) )
    ((void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[Serialize_eSerializeQTaskEvent][SectorInteriorObject_eQTaskType].pfHandler)(
      ptQTask,
      pxContext);
}

// source: h/2/editrigidobj.c:129  [anchor-mhash]
void __cdecl EditRigidObj_UpdateAttachmentHandler(struct QTask_s *ptQTask)
{
  __int16 v1; // cx
  struct QTask_s *ptNext; // eax
  int ptHead; // edx
  int v4; // eax
  struct QTask_s *v5; // ecx
  int v6; // esi
  void (__cdecl *pfHandler)(int); // ecx
  int v8; // eax
  struct QTask_s *v9; // ecx
  struct QTask_s *v10; // edx
  int v11; // esi
  void (__cdecl *v12)(struct QTask_s *); // edx
  int v13; // eax

  if ( ptQTask[2].ptParent )
  {
    if ( !ptQTask[5].tQTaskRefList.ptMiddle )
    {
      v1 = Attach_eAttachEvent;
      ptQTask[5].tQTaskChildren.ptTail = (struct QTask_s *)-1;
      ptQTask[5].tQTaskRefList.ptHead = nullptr;
      QTask_TriggerQTaskEventParent(ptQTask, v1, &ptQTask[5].tQTaskChildren.ptTail);
      ModelObj_CalcRelativePosAndOrientation((struct ModelObj_s *)ptQTask);
    }
    ModelObj_UpdateAttachment((struct ModelObj_s *)ptQTask);
    ptNext = ptQTask[3].ptNext;
    if ( ptNext && (ptHead = (int)ptNext->tQTaskChildren.ptHead, *(_DWORD *)ptHead) && ptHead )
    {
      v4 = QTask_nProtectedQTaskStackOffset;
      do
      {
        if ( *(_DWORD *)ptHead )
          v5 = **(_DWORD **)ptHead != 0 ? *(struct QTask_s **)ptHead : nullptr;
        else
          v5 = nullptr;
        v6 = Attach_eUpdateAttachmentEvent;
        QTask_atProtectedQTaskStack[v4].ptQTask = v5;
        pfHandler = (void (__cdecl *)(int))QTask_aatQTaskFinalEvent[v6][*(unsigned __int16 *)(ptHead + 36)].pfHandler;
        v8 = v4 + 1;
        QTask_nProtectedQTaskStackOffset = v8;
        if ( pfHandler )
        {
          pfHandler(ptHead);
          v8 = QTask_nProtectedQTaskStackOffset;
        }
        ptHead = dword_849C7DC[v8];
        v4 = v8 - 1;
        QTask_nProtectedQTaskStackOffset = v4;
      }
      while ( ptHead );
    }
    else
    {
      v4 = QTask_nProtectedQTaskStackOffset;
    }
    v9 = ptQTask->tQTaskChildren.ptHead;
    if ( v9->ptNext && v9 )
    {
      do
      {
        if ( v9->ptNext )
          v10 = v9->ptNext->ptNext != nullptr ? v9->ptNext : nullptr;
        else
          v10 = nullptr;
        v11 = Attach_eUpdateAttachmentEvent;
        QTask_atProtectedQTaskStack[v4].ptQTask = v10;
        v12 = (void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[v11][v9->eQTaskType].pfHandler;
        v13 = v4 + 1;
        QTask_nProtectedQTaskStackOffset = v13;
        if ( v12 )
        {
          v12(v9);
          v13 = QTask_nProtectedQTaskStackOffset;
        }
        v9 = (struct QTask_s *)dword_849C7DC[v13];
        v4 = v13 - 1;
        QTask_nProtectedQTaskStackOffset = v4;
      }
      while ( v9 );
    }
    qmemcpy(&ptQTask[8].tQTaskRefList.ptMiddle, &ptQTask[3].ptPrev, sizeof(struct QTask_s));
    qmemcpy(&ptQTask[8], &ptQTask[1], 0x18u);
  }
}

// source: h/2/editrigidobj.c:174  [anchor-mhash]
void __cdecl EditRigidObj_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { float ptDynCubeObj; };
    struct { char igi2_o1[24]; struct real64x3_t ptPos; };
    char igi2_extent[48];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  double v2; // st7
  double v3; // st7
  int *v4; // eax
  int v5; // eax
  double v6; // st6
  __int16 v7; // cx

  memset(&igi2_frame.ptPos, 0, sizeof(igi2_frame.ptPos));
  ModelObj_Init((struct ModelObj_s *)ptQTask, World_ptActiveWorld, nullptr);
  ptQTask[7].tQTaskChildren.ptHead = nullptr;
  ptQTask[7].tQTaskChildren.ptMiddle = (struct QTask_s *)2;
  ptQTask[7].tQTaskRefList.ptHead = nullptr;
  ptQTask[7].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[7].tQTaskRefList.ptTail = nullptr;
  ptQTask[7].ptParent = nullptr;
  *(_DWORD *)&ptQTask[7].eQTaskType = 0;
  LOBYTE(ptQTask[11].tQTaskRefList.ptMiddle) = 0;
  memset(&ptQTask[11].tQTaskRefList.ptTail, 0, 0x2Cu);
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
    WORLD_DYNCUBETREE_CATEGORY_MOBILE);
  if ( ptQTask[7].tQTaskChildren.ptTail )
  {
    ptQTask[2].tQTaskRefList.ptHead = nullptr;
    ptQTask[2].tQTaskRefList.ptMiddle = nullptr;
  }
  else
  {
    SectorObject_RegisterInteriorDynCubeObjSpecificSectorObject(
      World_ptActiveWorld,
      nullptr,
      (struct DynCubeObj_s *)ptQTask,
      (struct real64x3_t *)&ptQTask[1]);
  }
  ptQTask[8].tQTaskRefList.ptMiddle = (struct QReference_s *)1065353216;
  ptQTask[9].ptNext = (struct QTask_s *)1065353216;
  ptQTask[9].tQTaskChildren.ptTail = (struct QTask_s *)1065353216;
  ptQTask[8].ptNext = nullptr;
  ptQTask[8].ptPrev = nullptr;
  ptQTask[8].tQTaskChildren.ptHead = nullptr;
  ptQTask[8].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[8].tQTaskChildren.ptTail = nullptr;
  ptQTask[8].tQTaskRefList.ptHead = nullptr;
  ptQTask[8].tQTaskRefList.ptTail = nullptr;
  ptQTask[8].ptParent = nullptr;
  *(_DWORD *)&ptQTask[8].eQTaskType = 0;
  ptQTask[9].ptPrev = nullptr;
  ptQTask[9].tQTaskChildren.ptHead = nullptr;
  ptQTask[9].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[9].tQTaskRefList.ptHead = nullptr;
  ptQTask[5].tQTaskChildren.ptTail = (struct QTask_s *)-1;
  ptQTask[5].tQTaskRefList.ptHead = nullptr;
  v7 = Attach_eAttachEvent;
  LOBYTE(ptQTask[9].tQTaskRefList.ptMiddle) = 0;
  QTask_TriggerQTaskEventParent(ptQTask, v7, &ptQTask[5].tQTaskChildren.ptTail);
  ModelObj_CalcRelativePosAndOrientation((struct ModelObj_s *)ptQTask);
}

void __cdecl sub_5CC9B0(struct QTask_s *a1)
{
  struct QTask_s *ptNext; // eax
  struct QTask_s *ptHead; // ecx
  int v3; // edx
  struct QTask_s *v4; // eax
  void (__cdecl *pfHandler)(struct QTask_s *); // eax
  int v6; // edx

  ptNext = a1[3].ptNext;
  if ( ptNext )
    ((void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[1][ptNext->eQTaskType].pfHandler)(a1[3].ptNext);
  ptHead = a1->tQTaskChildren.ptHead;
  if ( ptHead->ptNext && ptHead )
  {
    v3 = QTask_nProtectedQTaskStackOffset;
    do
    {
      if ( ptHead->ptNext )
        v4 = ptHead->ptNext->ptNext != nullptr ? ptHead->ptNext : nullptr;
      else
        v4 = nullptr;
      QTask_atProtectedQTaskStack[v3].ptQTask = v4;
      pfHandler = (void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[1][ptHead->eQTaskType].pfHandler;
      v6 = v3 + 1;
      QTask_nProtectedQTaskStackOffset = v6;
      if ( pfHandler )
      {
        pfHandler(ptHead);
        v6 = QTask_nProtectedQTaskStackOffset;
      }
      ptHead = (struct QTask_s *)dword_849C7DC[v6];
      v3 = v6 - 1;
      QTask_nProtectedQTaskStackOffset = v3;
    }
    while ( ptHead );
  }
}

// source: h/2/editrigidobj.c:244  [anchor-mhash]
void __cdecl EditRigidObj_DeleteHandler(struct QTask_s *ptQTask)
{
  struct QReference_s *ptTail; // eax

  if ( *(_DWORD *)&ptQTask[2].eQTaskType )
  {
    ModelObj_SetLODVirModel((struct ModelObj_s *)ptQTask, nullptr, false);
    ptQTask[7].tQTaskRefList.ptHead = nullptr;
    ptQTask[7].tQTaskRefList.ptMiddle = nullptr;
    ptQTask[7].tQTaskRefList.ptTail = nullptr;
    ptQTask[7].ptParent = nullptr;
    *(_DWORD *)&ptQTask[7].eQTaskType = 0;
  }
  ptTail = ptQTask[11].tQTaskRefList.ptTail;
  if ( ptTail )
    ((void (__stdcall *)(struct QReference_s *))ptTail->ptNext->pxObject)(ptQTask[11].tQTaskRefList.ptTail);
  memset(&ptQTask[11].tQTaskRefList.ptTail, 0, 0x2Cu);
  SectorObject_RemoveInteriorDynCubeObj((struct DynCubeObj_s *)ptQTask);
  World_RemoveDynCubeObj((struct World_s *)ptQTask[2].ptParent, (struct DynCubeObj_s *)ptQTask);
}

// source: h/2/editrigidobj.c:272  [size]
void __cdecl EditRigidObj_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = EditRigidObj_ptParameterList;
}

// source: h/2/editrigidobj.c:288  [anchor-callee]
void __cdecl EditRigidObj_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTaskNote_s *QTaskNoteNode; // eax
  char *zString; // eax
  struct QTaskNote_s *v4; // eax
  char *v5; // eax
  struct LODVirModel_s *LODVirModelExistsFn; // eax
  struct LODVirModel_s *v7; // edi
  struct QReference_s *ptTail; // eax
  double v9; // st7
  double v10; // st7
  int *v11; // eax
  int v12; // eax
  double v13; // st6
  struct QTask_s *ptParent; // esi
  __int16 v15; // cx
  float ptDynCubeObj; // [esp+4h] [ebp-14h]

  if ( (int)ptQTask[2].tQTaskRefList.ptTail < 5 )
    ptQTask[2].tQTaskRefList.ptTail = (struct QReference_s *)5;
  QTaskNoteNode = Level_GetQTaskNoteNode(ptQTask);
  if ( QTaskNoteNode )
    zString = QTaskNoteNode->zString;
  else
    zString = (char *)&g_zInitialValue;
  if ( strstr(zString, "Wall")
    || ((v4 = Level_GetQTaskNoteNode(ptQTask)) == nullptr ? (v5 = (char *)&g_zInitialValue) : (v5 = v4->zString),
        strstr(v5, "wall")) )
  {
    LOBYTE(ptQTask[11].tQTaskRefList.ptMiddle) = 1;
  }
  qmemcpy(&ptQTask[3].ptPrev, &ptQTask[8].tQTaskRefList.ptMiddle, sizeof(struct QTask_s));
  LODVirModelExistsFn = MTP_GetLODVirModelExistsFn((char *)&ptQTask[9].tQTaskRefList.ptMiddle);
  if ( LODVirModelExistsFn )
    v7 = LODVirModelExistsFn;
  else
    v7 = nullptr;
  if ( v7 != *(struct LODVirModel_s **)&ptQTask[2].eQTaskType )
  {
    ModelObj_SetLODVirModel((struct ModelObj_s *)ptQTask, v7, false);
    ptQTask[7].tQTaskRefList.ptHead = nullptr;
    ptQTask[7].tQTaskRefList.ptMiddle = nullptr;
    ptQTask[7].tQTaskRefList.ptTail = nullptr;
    ptQTask[7].ptParent = nullptr;
    *(_DWORD *)&ptQTask[7].eQTaskType = 0;
  }
  if ( LOBYTE(ptQTask[11].tQTaskRefList.ptMiddle) )
  {
    sub_5C5600((int)v7, (int *)&ptQTask[11].tQTaskRefList.ptTail, (int)&ptQTask[1], (float *)&ptQTask[3].ptPrev);
  }
  else
  {
    ptTail = ptQTask[11].tQTaskRefList.ptTail;
    if ( ptTail )
      ((void (__stdcall *)(struct QReference_s *))ptTail->ptNext->pxObject)(ptQTask[11].tQTaskRefList.ptTail);
    memset(&ptQTask[11].tQTaskRefList.ptTail, 0, 0x2Cu);
  }
  if ( *(float *)&ptQTask[6].tQTaskChildren.ptHead <= (double)*(float *)&ptQTask[6].tQTaskChildren.ptMiddle )
    v9 = *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
  else
    v9 = *(float *)&ptQTask[6].tQTaskChildren.ptHead;
  if ( v9 >= *(float *)&ptQTask[6].ptPrev )
  {
    if ( *(float *)&ptQTask[6].tQTaskChildren.ptHead <= (double)*(float *)&ptQTask[6].tQTaskChildren.ptMiddle )
      v10 = *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
    else
      v10 = *(float *)&ptQTask[6].tQTaskChildren.ptHead;
  }
  else
  {
    v10 = *(float *)&ptQTask[6].ptPrev;
  }
  v11 = *(int **)&ptQTask[2].eQTaskType;
  if ( v11 && (v12 = *v11) != 0 )
    v13 = *(float *)(*(_DWORD *)(*(_DWORD *)(v12 + 12) + 12) + 120);
  else
    v13 = 1.0;
  ptDynCubeObj = v10 * v13;
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
      (struct real64x3_t *)&ptQTask[8]);
  }
  RigidDynCubeObj_UpdateAttachments((struct RigidDynCubeObj_t *)ptQTask);
  v15 = Attach_eAttachEvent;
  ptQTask[5].tQTaskChildren.ptTail = (struct QTask_s *)-1;
  ptQTask[5].tQTaskRefList.ptHead = nullptr;
  QTask_TriggerQTaskEventParent(ptQTask, v15, &ptQTask[5].tQTaskChildren.ptTail);
  ModelObj_CalcRelativePosAndOrientation((struct ModelObj_s *)ptQTask);
}

// source: h/2/editrigidobj.c:358  [anchor-mhash]
void __cdecl EditRigidObj_UpdateInternalDataAfterLoadHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptParent; // esi

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
      (struct real64x3_t *)&ptQTask[8]);
  }
}

// source: h/2/editrigidobj.c:380  [size]
void __cdecl EditRigidObj_SetPositionHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ;
}

// source: h/2/editrigidobj.c:429  [anchor-mhash]
void __cdecl EditRigidObj_RenderStartHandler(struct QTask_s *ptQTask, void *pxContext)
{
  if ( LOBYTE(ptQTask[11].tQTaskRefList.ptMiddle) )
    MagicObjContainer_RunHandler((struct QTask_s *)((char *)ptQTask + 468), (int)ptQTask, *(_DWORD *)pxContext);
}

// source: h/2/editrigidobj.c:484  [anchor-mhash]
void __cdecl EditRigidObj_GetShadowInfoHandler(struct QTask_s *ptQTask, void *pxContext)
{
  long double v2; // st7
  double v3; // st6
  double v4; // st6
  int *v5; // edi
  int v6; // edi
  double v7; // st5

  if ( *((_DWORD *)pxContext + 2) )
  {
    v2 = sub_5C5840((struct real64x3_t *)&ptQTask[1], (struct World_s *)ptQTask[2].ptParent, 204800.0);
    *((float *)pxContext + 1) = v2;
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
    *((float *)pxContext + 1) = v4 * v7 + v2;
  }
  *((_DWORD *)pxContext + 4) = 0;
}

// source: h/2/editrigidobj.c:510  [size]
unsigned __int16 __cdecl EditRigidObj_GetQTaskType()
{
  return EditRigidObj_eQTaskType;
}

// source: h/2/editrigidobj.c:529  [anchor-callee]
struct QTask_s *__cdecl EditRigidObj_New(
        struct QTask_s *ptParent,
        char *zModel,
        struct real64x3_t *ptPos,
        struct real32x9_t *ptOrientation)
{
  struct QTask_s *v4; // ebx

  v4 = QTask_NewFn(ptParent, EditRigidObj_eQTaskType, nullptr);
  qmemcpy(&v4[8], ptPos, 0x18u);
  qmemcpy(&v4[8].tQTaskRefList.ptMiddle, ptOrientation, sizeof(struct QTask_s));
  strcpy((char *)&v4[9].tQTaskRefList.ptMiddle, zModel);
  EditRigidObj_UpdateInternalDataHandler(v4, nullptr);
  return v4;
}

// source: h/2/editrigidobj.c:560  [size]
struct ParameterList_s *__cdecl EditRigidObj_GetSerializeParameterList()
{
  return EditRigidObj_ptSerializeParameterList;
}

// source: h/2/editrigidobj.c:573  [anchor-strings]
void __cdecl EditRigidObj_Open()
{
  unsigned __int16 v0; // si
  struct ParameterList_s *v1; // eax
  int v2; // edx
  unsigned __int16 v3; // si

  v0 = QTask_NewQTaskType("EditRigidObj", 512, SectorInteriorObject_eQTaskType, 0, 0);
  EditRigidObj_eQTaskType = v0;
  QTask_LinkQTaskEventHandlerFn(
    v0,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveHandler);
  QTask_LinkQTaskEventHandlerFn(v0, 0, EditRigidObj_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 1, sub_5CC9B0);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 2, EditRigidObj_DeleteHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, Attach_eUpdateAttachmentEvent, EditRigidObj_UpdateAttachmentHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))EditRigidObj_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(v0, ParameterList_eUpdateInternalDataQTaskEvent, EditRigidObj_UpdateInternalDataHandler);
  QTask_LinkQTaskEventHandlerFn(v0, 7, (void (__cdecl *)(struct QTask_s *, void *))EditRigidObj_SetPositionHandler);
  QTask_LinkQTaskEventHandlerFn(v0, ShadowVolume_eGetShadowInfoEvent, EditRigidObj_GetShadowInfoHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(
    v0,
    Level_eUpdateInternalDataAfterLoadEvent,
    EditRigidObj_UpdateInternalDataAfterLoadHandler);
  QTask_LinkQTaskEventHandlerFn(v0, RigidDynCubeObj_eRenderStartEvent, EditRigidObj_RenderStartHandler);
  v1 = (struct ParameterList_s *)Mem_AllocFn(132, 4);
  v2 = Level_eParameterTypeObjectPos;
  v1->ptParameterListItem = (struct ParameterListItem_s *)&v1[1];
  v1->nParameters = 0;
  v1->nMaxParameters = 6;
  EditRigidObj_ptParameterList = v1;
  ParameterList_AddParameter(v1, 0x140u, v2, "Position", 7u, nullptr);
  ParameterList_AddParameter(
    EditRigidObj_ptParameterList,
    0x158u,
    Level_eParameterTypeReal32x9,
    "Orientation",
    7u,
    nullptr);
  ParameterList_AddParameter(EditRigidObj_ptParameterList, 0x180u, Level_eParameterTypeString16, "Model", 7u, nullptr);
  ParameterList_AddParameter(EditRigidObj_ptParameterList, 0x6Cu, Level_eParameterTypeInt32, "RenderGroup", 7u, nullptr);
  ParameterList_AddParameter(
    EditRigidObj_ptParameterList,
    0x1D0u,
    Level_eParameterTypebool8,
    "Protect from shadows",
    7u,
    nullptr);
  ParameterList_AddParameter(
    EditRigidObj_ptParameterList,
    0x128u,
    Level_eParameterTypebool8,
    "Excluded from clipping against portals",
    7u,
    nullptr);
  Symbol_Register(
    "TASKTYPE_EDITRIGIDOBJ",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)EditRigidObj_eQTaskType,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  v3 = EditRigidObj_eQTaskType;
  QTask_LinkQTaskEventHandlerFn(
    EditRigidObj_eQTaskType,
    Serialize_eGetSerializeParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))EditRigidObj_GetSerializeParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(v3, Serialize_eSerializeQTaskEvent, EditRigidObj_SerializeHandler);
  EditRigidObj_ptSerializeParameterList = ParameterList_Derive(ModelObjParameters_ptSerializeParameterList, 0);
}

// source: h/2/editrigidobj.c:620  [size]
void __cdecl EditRigidObj_Close()
{
  int v0; // esi
  int v1; // esi

  if ( EditRigidObj_ptParameterList )
  {
    v0 = *(_DWORD *)((unsigned int)&EditRigidObj_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
  if ( EditRigidObj_ptSerializeParameterList )
  {
    v1 = *(_DWORD *)((unsigned int)&EditRigidObj_ptSerializeParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v1);
    memset(*(void **)(v1 + 8), 0xCDu, *(_DWORD *)(v1 + 16));
    free((void *)v1);
  }
  QTask_DeleteQTaskType(EditRigidObj_eQTaskType);
}
