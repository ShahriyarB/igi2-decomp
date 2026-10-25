/* h/2/origo.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: h/2/origo.c:73  [size]
void __cdecl Origo_DynCubeObjInGameEvalHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = 0;
}

// source: h/2/origo.c:90  [anchor-mhash]
void __cdecl Origo_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct LODVirModel_s *LODVirModelExistsFn; // eax

  ptQTask[8].ptNext = (struct QTask_s *)World_ptActiveWorld;
  ptQTask[8].tQTaskChildren.ptHead = nullptr;
  ptQTask[8].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[8].tQTaskChildren.ptTail = nullptr;
  ptQTask[8].tQTaskRefList.ptHead = nullptr;
  ptQTask[8].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[8].tQTaskRefList.ptTail = nullptr;
  ptQTask[9].tQTaskChildren.ptTail = nullptr;
  LODVirModelExistsFn = MTP_GetLODVirModelExistsFn("johan");
  ModelObj_Init((struct ModelObj_s *)ptQTask, (struct World_s *)ptQTask[8].ptNext, LODVirModelExistsFn);
  ptQTask[7].tQTaskChildren.ptHead = nullptr;
  ptQTask[7].tQTaskChildren.ptMiddle = (struct QTask_s *)2;
  ptQTask[7].tQTaskRefList.ptHead = nullptr;
  ptQTask[7].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[7].tQTaskRefList.ptTail = nullptr;
  ptQTask[7].ptParent = nullptr;
  *(_DWORD *)&ptQTask[7].eQTaskType = 0;
  World_RegisterDynCubeObjFirstTimeRadius(
    (struct World_s *)ptQTask[8].ptNext,
    (struct DynCubeObj_s *)ptQTask,
    (struct real64x3_t *)&ptQTask[8].tQTaskChildren,
    4096.0,
    WORLD_DYNCUBETREE_CATEGORY_STATIONARY);
}

// source: h/2/origo.c:126  [size]
void __cdecl Origo_EnterHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ;
}

// source: h/2/origo.c:154  [size]
void __cdecl Origo_GetCameraTargetInfoHandler(struct QTask_s *ptQTask, void *pxContext)
{
  double v2; // st7
  double v3; // st7
  int *v4; // ebx
  int v5; // ebx
  double v6; // st6

  qmemcpy(pxContext, &ptQTask[1], 0x18u);
  *((_DWORD *)pxContext + 9) = 1065353216;
  *((_DWORD *)pxContext + 13) = 1065353216;
  *((_DWORD *)pxContext + 17) = 1065353216;
  *((_DWORD *)pxContext + 6) = 0;
  *((_DWORD *)pxContext + 7) = 0;
  *((_DWORD *)pxContext + 8) = 0;
  *((_DWORD *)pxContext + 10) = 0;
  *((_DWORD *)pxContext + 11) = 0;
  *((_DWORD *)pxContext + 12) = 0;
  *((_DWORD *)pxContext + 14) = 0;
  *((_DWORD *)pxContext + 15) = 0;
  *((_DWORD *)pxContext + 16) = 0;
  *((_DWORD *)pxContext + 18) = 0;
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
  {
    v6 = v3 * *(float *)(*(_DWORD *)(*(_DWORD *)(v5 + 12) + 12) + 120);
    *((_DWORD *)pxContext + 20) = 0;
    *((float *)pxContext + 19) = v6;
  }
  else
  {
    *((_DWORD *)pxContext + 20) = 0;
    *((float *)pxContext + 19) = v3 * 1.0;
  }
}

// source: h/2/origo.c:190  [size]
void __cdecl Origo_DeleteHandler(struct QTask_s *ptQTask)
{
  World_RemoveDynCubeObj((struct World_s *)ptQTask[8].ptNext, (struct DynCubeObj_s *)ptQTask);
}

// source: h/2/origo.c:208  [size]
void __cdecl Origo_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = Origo_ptParameterList;
}

// source: h/2/origo.c:225  [anchor-mhash]
void __cdecl Origo_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct QTask_s *v5; };
    struct { char igi2_o1[16]; __int64 v6; };
    struct { char igi2_o2[24]; struct real64x3_t tNewPos; };
    char igi2_extent[48];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  double v2; // st7
  struct QTask_s *ptNext; // esi
  double ptPrev; // st7

  if ( !ptQTask[9].tQTaskChildren.ptTail )
  {
    ptQTask[8].ptParent = (struct QTask_s *)((__int64)*(double *)&ptQTask[8].tQTaskChildren.ptHead & 0xFFFFFFFE);
    v2 = *(double *)&ptQTask[8].tQTaskChildren.ptTail;
    ptQTask[9].tQTaskChildren.ptTail = (struct QTask_s *)1;
    *(_DWORD *)&ptQTask[8].eQTaskType = (__int64)v2 & 0xFFFFFFFE;
    ptQTask[9].ptNext = (struct QTask_s *)((__int64)*(double *)&ptQTask[8].tQTaskRefList.ptMiddle & 0xFFFFFFFE);
    ptQTask[9].ptPrev = ptQTask[8].ptParent;
    ptNext = ptQTask[9].ptNext;
    ptQTask[9].tQTaskChildren.ptHead = *(struct QTask_s **)&ptQTask[8].eQTaskType;
    ptQTask[9].tQTaskChildren.ptMiddle = ptNext;
    ptQTask[8].ptNext[9].tQTaskRefList = *(struct QReferenceList_s *)&ptQTask[8].ptParent;
  }
  igi2_frame.v6 = (__int64)*(double *)&ptQTask[8].tQTaskChildren.ptHead;
  nOrigoAddress = (int)&ptQTask[8].tQTaskChildren;
  ptQTask[8].ptParent = (struct QTask_s *)(igi2_frame.v6 & 0xFFFFFFFE);
  *(_DWORD *)&ptQTask[8].eQTaskType = (__int64)*(double *)&ptQTask[8].tQTaskChildren.ptTail & 0xFFFFFFFE;
  ptQTask[9].ptNext = (struct QTask_s *)((__int64)*(double *)&ptQTask[8].tQTaskRefList.ptMiddle & 0xFFFFFFFE);
  Origo_tDelta.nX = (int)ptQTask[9].ptPrev - (igi2_frame.v6 & 0xFFFFFFFE);
  Origo_tDelta.nY = (int)ptQTask[9].tQTaskChildren.ptHead - *(_DWORD *)&ptQTask[8].eQTaskType;
  Origo_tDelta.nZ = (char *)ptQTask[9].tQTaskChildren.ptMiddle - (char *)ptQTask[9].ptNext;
  ptPrev = (double)(int)ptQTask[9].ptPrev;
  qmemcpy(&igi2_frame.tNewPos, &ptQTask[8].tQTaskChildren, sizeof(igi2_frame.tNewPos));
  igi2_frame.tNewPos.vX = igi2_frame.tNewPos.vX - ptPrev;
  igi2_frame.tNewPos.vY = igi2_frame.tNewPos.vY - (double)(int)ptQTask[9].tQTaskChildren.ptHead;
  igi2_frame.v5 = ptQTask[8].ptNext;
  igi2_frame.tNewPos.vZ = igi2_frame.tNewPos.vZ - (double)(int)ptQTask[9].tQTaskChildren.ptMiddle;
  World_MoveDynCubeObjRadius((struct World_s *)igi2_frame.v5, (struct DynCubeObj_s *)ptQTask, &igi2_frame.tNewPos, 4096.0);
}

// source: h/2/origo.c:281  [anchor-strings]
void __cdecl Origo_Open()
{
  unsigned __int16 v0; // si
  struct ParameterList_s *v1; // eax
  int v2; // edx

  v0 = QTask_NewQTaskType("Origo", 384, RigidDynCubeObj_eQTaskType, 0, 0);
  g_eQTaskType = v0;
  QTask_LinkQTaskEventHandlerFn(v0, 0, Origo_CreateHandler);
  QTask_LinkQTaskEventHandlerFn(v0, 5, (void (__cdecl *)(struct QTask_s *, void *))Origo_EnterHandler);
  QTask_LinkQTaskEventHandlerFn(v0, 8, Origo_GetCameraTargetInfoHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 2, Origo_DeleteHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Origo_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(v0, ParameterList_eUpdateInternalDataQTaskEvent, Origo_UpdateInternalDataHandler);
  QTask_LinkQTaskEventHandlerFn(v0, 11, nullptr);
  QTask_LinkQTaskEventHandlerFn(v0, 12, nullptr);
  QTask_LinkQTaskEventHandlerFn(v0, QCube_eGetClosestVertexQTaskEvent, nullptr);
  QTask_LinkQTaskEventHandlerFn(v0, 10, nullptr);
  QTask_LinkQTaskEventHandlerFn(v0, 9, nullptr);
  QTask_LinkQTaskEventHandlerFn(v0, 13, nullptr);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    DynCube_eDynCubeObjInGameEvalQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Origo_DynCubeObjInGameEvalHandler);
  v1 = (struct ParameterList_s *)Mem_AllocFn(32, 4);
  v1->ptParameterListItem = (struct ParameterListItem_s *)&v1[1];
  v2 = Level_eParameterTypeObjectPos;
  v1->nParameters = 0;
  v1->nMaxParameters = 1;
  Origo_ptParameterList = v1;
  ParameterList_AddParameter(v1, 0x148u, v2, "Position", 7u, nullptr);
}

// source: h/2/origo.c:317  [size]
void __cdecl Origo_Close()
{
  int v0; // esi

  if ( Origo_ptParameterList )
  {
    v0 = *(_DWORD *)((unsigned int)&Origo_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
  QTask_DeleteQTaskType(g_eQTaskType);
}

// source: h/2/origo.c:335  [size]
unsigned __int16 __cdecl Origo_GetQTaskType()
{
  return g_eQTaskType;
}
