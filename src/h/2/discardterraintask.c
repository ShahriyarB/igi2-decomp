/* h/2/discardterraintask.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: h/2/discardterraintask.c:46  [anchor-mhash]
void __cdecl DiscardTerrainTask_GetMaterialHandler(struct QTask_s *ptQTask, void *pxContext)
{
  int v2; // ebp
  int v3; // ebx
  double *v4; // ecx

  v2 = 0;
  if ( *((int *)pxContext + 1) > 0 )
  {
    v3 = 0;
    do
    {
      v4 = (double *)(v3 + *(_DWORD *)pxContext);
      if ( *v4 > *(double *)&ptQTask[8].tQTaskRefList.ptMiddle != *v4 > *(double *)&ptQTask[9].tQTaskChildren.ptHead
        && v4[1] > *(double *)&ptQTask[8].ptParent != v4[1] > *(double *)&ptQTask[9].tQTaskChildren.ptTail
        && v4[2] > *(double *)&ptQTask[9].ptNext != v4[2] > *(double *)&ptQTask[9].tQTaskRefList.ptMiddle )
      {
        *((_BYTE *)pxContext + v2 + 12) = 0;
      }
      ++v2;
      v3 += 24;
    }
    while ( v2 < (int)(*((_DWORD *)pxContext + 1)) );
  }
}

// source: h/2/discardterraintask.c:80  [size]
void __cdecl DiscardTerrainTask_DynCubeObjInGameEvalHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = 0;
}

// source: h/2/discardterraintask.c:96  [size]
void __cdecl DiscardTerrainTask_EnterHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ;
}

// source: h/2/discardterraintask.c:113  [anchor-mhash]
void __cdecl DiscardTerrainTask_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct LODVirModel_s *LODVirModelExistsFn; // eax

  ptQTask[8].ptNext = nullptr;
  ptQTask[8].ptPrev = nullptr;
  ptQTask[8].tQTaskChildren.ptHead = nullptr;
  ptQTask[8].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[8].tQTaskChildren.ptTail = nullptr;
  ptQTask[8].tQTaskRefList.ptHead = nullptr;
  ptQTask[8].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[8].tQTaskRefList.ptTail = nullptr;
  ptQTask[8].ptParent = nullptr;
  *(_DWORD *)&ptQTask[8].eQTaskType = 0;
  ptQTask[9].ptNext = nullptr;
  ptQTask[9].ptPrev = nullptr;
  ptQTask[9].tQTaskChildren.ptHead = nullptr;
  ptQTask[9].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[9].tQTaskChildren.ptTail = nullptr;
  ptQTask[9].tQTaskRefList.ptHead = nullptr;
  ptQTask[9].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[9].tQTaskRefList.ptTail = nullptr;
  ptQTask[10].tQTaskChildren.ptTail = (struct QTask_s *)10;
  LODVirModelExistsFn = MTP_GetLODVirModelExistsFn("johan");
  ModelObj_Init((struct ModelObj_s *)ptQTask, World_ptActiveWorld, LODVirModelExistsFn);
  ptQTask[7].tQTaskChildren.ptHead = nullptr;
  ptQTask[7].tQTaskChildren.ptMiddle = (struct QTask_s *)2;
  ptQTask[7].tQTaskRefList.ptHead = nullptr;
  ptQTask[7].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[7].tQTaskRefList.ptTail = nullptr;
  ptQTask[7].ptParent = nullptr;
  *(_DWORD *)&ptQTask[7].eQTaskType = 0;
  World_RegisterDynCubeObjFirstTimeRadius(
    (struct World_s *)ptQTask[2].ptParent,
    (struct DynCubeObj_s *)ptQTask,
    (struct real64x3_t *)&ptQTask[8],
    4096.0,
    WORLD_DYNCUBETREE_CATEGORY_TERRAINMODIFIERS);
}

// source: h/2/discardterraintask.c:149  [size]
void __cdecl DiscardTerrainTask_DeleteHandler(struct QTask_s *ptQTask)
{
  World_RemoveDynCubeObj((struct World_s *)ptQTask[2].ptParent, (struct DynCubeObj_s *)ptQTask);
}

// source: h/2/discardterraintask.c:170  [anchor-mhash]
void __cdecl DiscardTerrainTask_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct World_s *ptParent; // eax
  int v3; // ebp
  double v4; // st7
  double v5; // st6
  double v6; // st7
  double v7; // st7
  double v8; // st6
  double v9; // st7
  struct QTask_s *ptHead; // eax
  int v11; // edx
  struct QTask_s *v12; // ecx
  void (__cdecl *pfHandler)(struct QTask_s *, void *); // ecx
  int v14; // edx
  double v15; // [esp+10h] [ebp-10h]
  double v16; // [esp+10h] [ebp-10h]
  double v17; // [esp+18h] [ebp-8h]
  double v18; // [esp+18h] [ebp-8h]

  ptParent = (struct World_s *)ptQTask[2].ptParent;
  v3 = 0x40000000 >> (int)ptQTask[10].tQTaskChildren.ptTail;
  qmemcpy(&ptQTask[9].ptParent, &ptQTask[8], 0x18u);
  *(double *)&ptQTask[9].ptParent = (double)ptParent->tOrigo.nX + *(double *)&ptQTask[9].ptParent;
  v3 *= 2;
  *(double *)&ptQTask[10].ptNext = (double)ptParent->tOrigo.nY + *(double *)&ptQTask[10].ptNext;
  *(double *)&ptQTask[10].tQTaskChildren.ptHead = (double)ptParent->tOrigo.nZ
                                                + *(double *)&ptQTask[10].tQTaskChildren.ptHead;
  v4 = (double)(int)(-v3 & (__int64)*(double *)&ptQTask[9].ptParent);
  *(double *)&ptQTask[8].tQTaskRefList.ptMiddle = v4;
  v17 = (double)(int)(-v3 & (__int64)*(double *)&ptQTask[10].ptNext);
  *(double *)&ptQTask[8].ptParent = v17;
  v15 = (double)(int)(-v3 & (__int64)*(double *)&ptQTask[10].tQTaskChildren.ptHead);
  *(double *)&ptQTask[9].ptNext = v15;
  qmemcpy(&ptQTask[9].ptParent, &ptQTask[8].tQTaskRefList.ptMiddle, 0x18u);
  v5 = v4;
  v6 = (double)v3;
  *(double *)&ptQTask[9].tQTaskChildren.ptHead = v5 + v6;
  *(double *)&ptQTask[9].tQTaskChildren.ptTail = v17 + v6;
  *(double *)&ptQTask[9].tQTaskRefList.ptMiddle = v15 + v6;
  v7 = v6 * 0.5;
  v8 = v7 + *(double *)&ptQTask[9].ptParent;
  *(double *)&ptQTask[9].ptParent = v8;
  v18 = v7 + *(double *)&ptQTask[10].ptNext;
  *(double *)&ptQTask[10].ptNext = v18;
  v16 = v7 + *(double *)&ptQTask[10].tQTaskChildren.ptHead;
  *(double *)&ptQTask[10].tQTaskChildren.ptHead = v16;
  *(double *)&ptQTask[9].ptParent = v8 - (double)ptParent->tOrigo.nX;
  *(double *)&ptQTask[10].ptNext = v18 - (double)ptParent->tOrigo.nY;
  *(double *)&ptQTask[10].tQTaskChildren.ptHead = v16 - (double)ptParent->tOrigo.nZ;
  *(double *)&ptQTask[8].tQTaskRefList.ptMiddle = *(double *)&ptQTask[8].tQTaskRefList.ptMiddle
                                                - (double)ptParent->tOrigo.nX;
  *(double *)&ptQTask[8].ptParent = *(double *)&ptQTask[8].ptParent - (double)ptParent->tOrigo.nY;
  *(double *)&ptQTask[9].ptNext = *(double *)&ptQTask[9].ptNext - (double)ptParent->tOrigo.nZ;
  *(double *)&ptQTask[9].tQTaskChildren.ptHead = *(double *)&ptQTask[9].tQTaskChildren.ptHead
                                               - (double)ptParent->tOrigo.nX;
  *(double *)&ptQTask[9].tQTaskChildren.ptTail = *(double *)&ptQTask[9].tQTaskChildren.ptTail
                                               - (double)ptParent->tOrigo.nY;
  *(double *)&ptQTask[9].tQTaskRefList.ptMiddle = *(double *)&ptQTask[9].tQTaskRefList.ptMiddle
                                                - (double)ptParent->tOrigo.nZ;
  v9 = (double)v3 * 0.00011625744809862226;
  *(float *)&ptQTask[6].ptPrev = v9;
  *(float *)&ptQTask[6].tQTaskChildren.ptHead = v9;
  *(float *)&ptQTask[6].tQTaskChildren.ptMiddle = v9;
  World_MoveDynCubeObjMinMaxXYZ(
    ptParent,
    (struct DynCubeObj_s *)ptQTask,
    (struct real64x3_t *)&ptQTask[9].ptParent,
    (struct real64x3_t *)&ptQTask[8].tQTaskRefList.ptMiddle,
    (struct real64x3_t *)&ptQTask[9].tQTaskChildren);
  if ( !pxContext || !*(_DWORD *)pxContext )
  {
    ptHead = ptQTask->tQTaskChildren.ptHead;
    if ( ptHead->ptNext )
    {
      if ( ptHead )
      {
        v11 = QTask_nProtectedQTaskStackOffset;
        do
        {
          if ( ptHead->ptNext )
            v12 = ptHead->ptNext->ptNext != nullptr ? ptHead->ptNext : nullptr;
          else
            v12 = nullptr;
          QTask_atProtectedQTaskStack[v11].ptQTask = v12;
          pfHandler = (void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[ParameterList_eUpdateInternalDataQTaskEvent][ptHead->eQTaskType].pfHandler;
          v14 = v11 + 1;
          QTask_nProtectedQTaskStackOffset = v14;
          if ( pfHandler )
          {
            pfHandler(ptHead, pxContext);
            v14 = QTask_nProtectedQTaskStackOffset;
          }
          ptHead = (struct QTask_s *)dword_849C7DC[v14];
          v11 = v14 - 1;
          QTask_nProtectedQTaskStackOffset = v11;
        }
        while ( ptHead );
      }
    }
  }
}

// source: h/2/discardterraintask.c:235  [size]
void __cdecl DiscardTerrainTask_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = DiscardTerrainTask_ptParameterList;
}

// source: h/2/discardterraintask.c:252  [size]
void __cdecl DiscardTerrainTask_GetCameraTargetInfoHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *ptTail; // ecx

  qmemcpy(pxContext, &ptQTask[8], 0x18u);
  *((_DWORD *)pxContext + 6) = 0;
  *((_DWORD *)pxContext + 7) = 0;
  *((_DWORD *)pxContext + 8) = 0;
  *((_DWORD *)pxContext + 9) = 1065353216;
  *((_DWORD *)pxContext + 10) = 0;
  *((_DWORD *)pxContext + 11) = 0;
  *((_DWORD *)pxContext + 12) = 0;
  *((_DWORD *)pxContext + 13) = 1065353216;
  *((_DWORD *)pxContext + 14) = 0;
  *((_DWORD *)pxContext + 15) = 0;
  *((_DWORD *)pxContext + 16) = 0;
  *((_DWORD *)pxContext + 17) = 1065353216;
  *((_DWORD *)pxContext + 18) = 0;
  ptTail = ptQTask[10].tQTaskChildren.ptTail;
  *((_DWORD *)pxContext + 20) = 0;
  *((float *)pxContext + 19) = (float)(0x40000000 >> (char)ptTail);
}

// source: h/2/discardterraintask.c:287  [size]
void __cdecl DiscardTerrainTask_EnterImmediatelyHandler(struct QTask_s *ptQTask, void *pxContext)
{
  QCube_isDiscard = 1;
}

// source: h/2/discardterraintask.c:300  [size]
void __cdecl DiscardTerrainTask_RemoveHandler(struct QTask_s *ptQTask, void *pxContext)
{
  World_RemoveDynCubeObj(*(struct World_s **)pxContext, (struct DynCubeObj_s *)ptQTask);
}

// source: h/2/discardterraintask.c:326  [anchor-mhash]
void __cdecl DiscardTerrainTask_RegisterHandler(struct QTask_s *ptQTask, void *pxContext)
{
  World_RegisterDynCubeObjFirstTimeRadius(
    (struct World_s *)ptQTask[2].ptParent,
    (struct DynCubeObj_s *)ptQTask,
    (struct real64x3_t *)&ptQTask[8],
    4096.0,
    WORLD_DYNCUBETREE_CATEGORY_TERRAINMODIFIERS);
  World_MoveDynCubeObjMinMaxXYZ(
    *((struct World_s **)pxContext + 1),
    (struct DynCubeObj_s *)ptQTask,
    (struct real64x3_t *)&ptQTask[9].ptParent,
    (struct real64x3_t *)&ptQTask[8].tQTaskRefList.ptMiddle,
    (struct real64x3_t *)&ptQTask[9].tQTaskChildren);
}

// source: h/2/discardterraintask.c:367  [anchor-strings]
void __cdecl DiscardTerrainTask_Open()
{
  unsigned __int16 v0; // si
  struct ParameterList_s *v1; // eax
  int v2; // edx

  v0 = QTask_NewQTaskType("DiscardTerrain", 424, EditorRigidObj_eQTaskType, 0, 0);
  DiscardTerrainTask_eQTaskType = v0;
  QTask_LinkQTaskEventHandlerFn(v0, 0, DiscardTerrainTask_CreateHandler);
  QTask_LinkQTaskEventHandlerFn(v0, 5, (void (__cdecl *)(struct QTask_s *, void *))DiscardTerrainTask_EnterHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    15,
    (void (__cdecl *)(struct QTask_s *, void *))DiscardTerrainTask_EnterImmediatelyHandler);
  QTask_LinkQTaskEventHandlerFn(v0, 8, DiscardTerrainTask_GetCameraTargetInfoHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 2, DiscardTerrainTask_DeleteHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))DiscardTerrainTask_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    ParameterList_eUpdateInternalDataQTaskEvent,
    DiscardTerrainTask_UpdateInternalDataHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    DynCube_eDynCubeObjInGameEvalQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))DiscardTerrainTask_DynCubeObjInGameEvalHandler);
  QTask_LinkQTaskEventHandlerFn(v0, 12, DiscardTerrainTask_GetMaterialHandler);
  QTask_LinkQTaskEventHandlerFn(v0, DynCubeObj_eDynCubeObjRemoveQTaskEvent, DiscardTerrainTask_RemoveHandler);
  QTask_LinkQTaskEventHandlerFn(v0, DynCubeObj_eDynCubeObjRegisterQTaskEvent, DiscardTerrainTask_RegisterHandler);
  QTask_LinkQTaskEventHandlerFn(v0, QCube_eGetClosestVertexQTaskEvent, nullptr);
  QTask_LinkQTaskEventHandlerFn(v0, 10, nullptr);
  QTask_LinkQTaskEventHandlerFn(v0, 9, nullptr);
  QTask_LinkQTaskEventHandlerFn(v0, 11, nullptr);
  v1 = (struct ParameterList_s *)Mem_AllocFn(52, 4);
  v2 = Level_eParameterTypeObjectPos;
  v1->ptParameterListItem = (struct ParameterListItem_s *)&v1[1];
  v1->nParameters = 0;
  v1->nMaxParameters = 2;
  DiscardTerrainTask_ptParameterList = v1;
  ParameterList_AddParameter(v1, 0x140u, v2, "Position", 7u, nullptr);
  ParameterList_AddParameter(
    DiscardTerrainTask_ptParameterList,
    0x1A0u,
    Level_eParameterTypeInt32,
    "Level",
    7u,
    nullptr);
}

// source: h/2/discardterraintask.c:406  [size]
void __cdecl DiscardTerrainTask_Close()
{
  int v0; // esi

  if ( DiscardTerrainTask_ptParameterList )
  {
    v0 = *(_DWORD *)((unsigned int)&DiscardTerrainTask_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
  QTask_DeleteQTaskType(DiscardTerrainTask_eQTaskType);
}

// source: h/2/discardterraintask.c:423  [size]
unsigned __int16 __cdecl DiscardTerrainTask_GetQTaskType()
{
  return DiscardTerrainTask_eQTaskType;
}

// source: h/2/discardterraintask.c:439  [anchor-mhash]
struct QTask_s *__cdecl DiscardTerrainTask_New(
        struct QTask_s *ptParent,
        struct real64x3_t *ptPos,
        int nLevel)
{
  struct QTask_s *v3; // ebx
  int eQTaskType; // edx
  void (__cdecl *pfHandler)(struct QTask_s *, _DWORD); // eax

  v3 = QTask_NewFn(ptParent, DiscardTerrainTask_eQTaskType, nullptr);
  eQTaskType = v3->eQTaskType;
  v3[10].tQTaskChildren.ptTail = (struct QTask_s *)nLevel;
  qmemcpy(&v3[8], ptPos, 0x18u);
  pfHandler = (void (__cdecl *)(struct QTask_s *, _DWORD))QTask_aatQTaskFinalEvent[ParameterList_eUpdateInternalDataQTaskEvent][eQTaskType].pfHandler;
  if ( pfHandler )
    pfHandler(v3, 0);
  return v3;
}
