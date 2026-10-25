/* h/2/edithazinglayer.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: h/2/edithazinglayer.c:73  [size]
void __cdecl EditHazingLayer_DynCubeObjInGameEvalHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = 0;
}

// source: h/2/edithazinglayer.c:90  [anchor-mhash]
void __cdecl EditHazinglayer_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ptQTask[1].tQTaskChildren.ptHead = nullptr;
  ptQTask[1].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[1].tQTaskChildren.ptTail = nullptr;
  ptQTask[1].tQTaskRefList.ptHead = nullptr;
  ptQTask[1].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[1].tQTaskRefList.ptTail = nullptr;
  ptQTask[1].ptParent = nullptr;
  *(_DWORD *)&ptQTask[1].eQTaskType = 0;
  ptQTask[2].ptNext = nullptr;
  ptQTask[2].ptPrev = nullptr;
  ptQTask[2].tQTaskChildren.ptHead = nullptr;
  ptQTask[2].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[2].tQTaskChildren.ptTail = nullptr;
  ptQTask[2].tQTaskRefList.ptHead = nullptr;
  ptQTask[2].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[2].tQTaskRefList.ptTail = nullptr;
  ptQTask[2].ptParent = nullptr;
  *(_DWORD *)&ptQTask[2].eQTaskType = 0;
  ptQTask[3].ptPrev = (struct QTask_s *)1120403456;
  ptQTask[3].tQTaskChildren.ptHead = nullptr;
  ptQTask[3].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[3].tQTaskChildren.ptTail = nullptr;
  ptQTask[3].tQTaskRefList.ptHead = nullptr;
  ptQTask[3].ptNext = nullptr;
  ptQTask[1].ptNext = nullptr;
}

// source: h/2/edithazinglayer.c:134  [anchor-mhash]
void __cdecl EditHazinglayer_DeleteHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptNext; // esi

  ptNext = ptQTask[1].ptNext;
  World_RemoveDynCubeObj((struct World_s *)ptNext[2].ptParent, (struct DynCubeObj_s *)ptNext);
  QTask_Delete(ptNext);
}

// source: h/2/edithazinglayer.c:160  [anchor-mhash]
void __cdecl EditHazinglayer_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct QTask_s *ptPrev; };
    struct { char igi2_o1[4]; double vDensity; };
    struct { char igi2_o2[12]; double vMaxZ; };
    struct { char igi2_o3[36]; int v12; };
    struct { char igi2_o4[36]; double v13; };
    struct { char igi2_o5[44]; int nCubeSize; };
    struct { char igi2_o6[44]; double nCubeSizea; };
    struct { char igi2_o7[52]; struct real64x3_t tNewPos; };
    char igi2_extent[76];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v3; // edx
  struct real64x3_t *p_ptParent; // ebx
  double v5; // st7
  double v6; // st6
  struct real64x3_t *p_ptTail; // edx
  struct HazingDynCubeObj_t *ptNext; // ecx

  v3 = 0x40000000 >> (int)ptQTask[3].ptNext;
  qmemcpy(&igi2_frame.tNewPos, &ptQTask[1].tQTaskChildren, sizeof(igi2_frame.tNewPos));
  igi2_frame.nCubeSize = 2 * v3;
  v3 *= -2;
  p_ptParent = (struct real64x3_t *)&ptQTask[1].ptParent;
  v5 = (double)(int)(v3 & (__int64)igi2_frame.tNewPos.vX);
  *(double *)&ptQTask[1].ptParent = v5;
  v6 = (double)(int)(v3 & (__int64)igi2_frame.tNewPos.vY);
  *(double *)&ptQTask[2].ptNext = v6;
  igi2_frame.v12 = v3 & (__int64)igi2_frame.tNewPos.vZ;
  p_ptTail = (struct real64x3_t *)&ptQTask[2].tQTaskChildren.ptTail;
  ptNext = (struct HazingDynCubeObj_t *)ptQTask[1].ptNext;
  igi2_frame.v13 = (double)igi2_frame.v12;
  *(double *)&ptQTask[2].tQTaskChildren.ptHead = igi2_frame.v13;
  igi2_frame.nCubeSizea = (double)igi2_frame.nCubeSize;
  *(double *)&ptQTask[2].tQTaskChildren.ptTail = igi2_frame.nCubeSizea + v5;
  *(double *)&ptQTask[2].tQTaskRefList.ptMiddle = igi2_frame.nCubeSizea + v6;
  *(double *)&ptQTask[2].ptParent = igi2_frame.nCubeSizea + igi2_frame.v13;
  igi2_frame.vMaxZ = *(double *)&ptQTask[3].tQTaskChildren.ptTail + *(double *)&ptQTask[1].tQTaskRefList.ptMiddle;
  igi2_frame.vDensity = *(double *)&ptQTask[3].tQTaskChildren.ptHead + *(double *)&ptQTask[1].tQTaskRefList.ptMiddle;
  igi2_frame.ptPrev = ptQTask[3].ptPrev;
  if ( ptNext )
    Hazinglayers_Update(ptNext, p_ptParent, p_ptTail, nullptr, *(float *)&igi2_frame.ptPrev, igi2_frame.vDensity, igi2_frame.vMaxZ);
  else
    ptQTask[1].ptNext = (struct QTask_s *)Hazinglayers_New(
                                            p_ptParent,
                                            p_ptTail,
                                            nullptr,
                                            *(float *)&igi2_frame.ptPrev,
                                            igi2_frame.vDensity,
                                            igi2_frame.vMaxZ);
}

// source: h/2/edithazinglayer.c:230  [size]
void __cdecl EditHazinglayer_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = EditHazinglayer_ptParameterList;
}

// source: h/2/edithazinglayer.c:285  [anchor-hash]
void __cdecl EditHazinglayer_Open()
{
  unsigned __int16 v0; // si
  struct ParameterList_s *v1; // eax
  int v2; // edx

  v0 = QTask_NewQTaskType("EditHazinglayer", 144, EditorRigidObj_eQTaskType, 0, 0);
  EditHazinglayer_eQTaskType = v0;
  QTask_LinkQTaskEventHandlerFn(v0, 0, (void (__cdecl *)(struct QTask_s *, void *))EditHazinglayer_CreateHandler);
  QTask_LinkQTaskEventHandlerFn(v0, 8, nullptr);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 2, EditHazinglayer_DeleteHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))EditHazinglayer_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    ParameterList_eUpdateInternalDataQTaskEvent,
    EditHazinglayer_UpdateInternalDataHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    DynCube_eDynCubeObjInGameEvalQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))EditHazingLayer_DynCubeObjInGameEvalHandler);
  v1 = (struct ParameterList_s *)Mem_AllocFn(112, 4);
  v2 = Level_eParameterTypeObjectPos;
  v1->ptParameterListItem = (struct ParameterListItem_s *)&v1[1];
  v1->nParameters = 0;
  v1->nMaxParameters = 5;
  EditHazinglayer_ptParameterList = v1;
  ParameterList_AddParameter(v1, 0x30u, v2, "Position", 7u, nullptr);
  ParameterList_AddParameter(EditHazinglayer_ptParameterList, 0x78u, Level_eParameterTypeInt32, "Level", 7u, nullptr);
  ParameterList_AddParameter(EditHazinglayer_ptParameterList, 0x7Cu, Level_eParameterTypeReal32, "Density", 7u, nullptr);
  ParameterList_AddParameter(EditHazinglayer_ptParameterList, 0x80u, Level_eParameterTypeReal64, "Min Z", 7u, nullptr);
  ParameterList_AddParameter(EditHazinglayer_ptParameterList, 0x88u, Level_eParameterTypeReal64, "Max Z", 7u, nullptr);
}

// source: h/2/edithazinglayer.c:318  [size]
void __cdecl EditHazinglayer_Close()
{
  int v0; // esi

  if ( EditHazinglayer_ptParameterList )
  {
    v0 = *(_DWORD *)((unsigned int)&EditHazinglayer_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
  QTask_DeleteQTaskType(EditHazinglayer_eQTaskType);
}

// source: h/2/edithazinglayer.c:336  [size]
unsigned __int16 __cdecl EditHazinglayer_GetQTaskType()
{
  return EditHazinglayer_eQTaskType;
}
