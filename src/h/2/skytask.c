/* h/2/skytask.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: h/2/skytask.c:57  [size]
void __cdecl SkyQTask_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ;
}

// source: h/2/skytask.c:70  [size]
void __cdecl SkyQTask_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = SkyQTask_ptParameterList;
}

// source: h/2/skytask.c:87  [size]
void __cdecl SkyQTask_EnterHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ;
}

// source: h/2/skytask.c:105  [size]
void __cdecl SkyQTask_DeleteHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptMiddle; // ecx
  struct QTask_s *ptTail; // ecx

  ptMiddle = ptQTask[2].tQTaskChildren.ptMiddle;
  if ( ptMiddle )
    ptMiddle[2].tQTaskChildren.ptTail = ptQTask[2].tQTaskChildren.ptTail;
  else
    ptQTask[2].ptParent[2].ptPrev = ptQTask[2].tQTaskChildren.ptTail;
  ptTail = ptQTask[2].tQTaskChildren.ptTail;
  if ( ptTail )
    ptTail[2].tQTaskChildren.ptMiddle = ptQTask[2].tQTaskChildren.ptMiddle;
}

// source: h/2/skytask.c:123  [anchor-mhash]
void __cdecl SkyQTask_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct World_s *v2; // eax
  struct DynCubeObj_s *ptManualRedrawList; // edx
  struct DynCubeObj_s *ptPrev; // ecx

  v2 = World_ptActiveWorld;
  ptQTask[2].ptParent = (struct QTask_s *)World_ptActiveWorld;
  *(_DWORD *)&ptQTask[2].eQTaskType = 0;
  ptQTask[3].ptNext = nullptr;
  ptManualRedrawList = v2->ptManualRedrawList;
  if ( ptManualRedrawList )
  {
    ptManualRedrawList->ptPrev = (struct DynCubeObj_s *)ptQTask;
    v2->ptManualRedrawList->ptPrev->ptNext = v2->ptManualRedrawList;
    ptPrev = v2->ptManualRedrawList->ptPrev;
    v2->ptManualRedrawList = ptPrev;
    ptPrev->ptPrev = nullptr;
  }
  else
  {
    v2->ptManualRedrawList = (struct DynCubeObj_s *)ptQTask;
    ptQTask[2].tQTaskChildren.ptTail = nullptr;
    v2->ptManualRedrawList->ptPrev = nullptr;
  }
}

// source: h/2/skytask.c:147  [anchor-hash]
void __cdecl SkyQTask_Open()
{
  unsigned __int16 BaseQTaskType; // ax
  unsigned __int16 v1; // si
  struct ParameterList_s *v2; // eax
  int v3; // edx

  BaseQTaskType = QTask_GetBaseQTaskType();
  v1 = QTask_NewQTaskType("SkyTask", 128, BaseQTaskType, 0, 0);
  SkyQTask_eQTaskType = v1;
  QTask_LinkQTaskEventHandlerFn(v1, 5, (void (__cdecl *)(struct QTask_s *, void *))SkyQTask_EnterHandler);
  QTask_LinkQTaskEventHandlerFn(v1, 0, SkyQTask_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 2, SkyQTask_DeleteHandler);
  QTask_LinkQTaskEventHandlerFn(
    v1,
    ParameterList_eUpdateInternalDataQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))SkyQTask_UpdateInternalDataHandler);
  QTask_LinkQTaskEventHandlerFn(
    v1,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))SkyQTask_GetParameterListHandler);
  v2 = (struct ParameterList_s *)Mem_AllocFn(52, 4);
  v3 = Level_eParameterTypeReal32;
  v2->ptParameterListItem = (struct ParameterListItem_s *)&v2[1];
  v2->nParameters = 0;
  v2->nMaxParameters = 2;
  SkyQTask_ptParameterList = v2;
  ParameterList_AddParameter(v2, 0x78u, v3, "Z Displacement", 7u, nullptr);
  ParameterList_AddParameter(SkyQTask_ptParameterList, 0x74u, Level_eParameterTypeAngle, "Gamma Rotation", 7u, nullptr);
}

// source: h/2/skytask.c:177  [size]
void __cdecl SkyQTask_Close()
{
  int v0; // esi

  if ( SkyQTask_ptParameterList )
  {
    v0 = *(_DWORD *)((unsigned int)&SkyQTask_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
  QTask_DeleteQTaskType(SkyQTask_eQTaskType);
  SkyQTask_eQTaskType = 512;
}

// source: h/2/skytask.c:196  [size]
unsigned __int16 __cdecl SkyQTask_GetQTaskType()
{
  return SkyQTask_eQTaskType;
}
