/* h/2/setactivecubetask.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: h/2/setactivecubetask.c:72  [anchor-mhash]
void __cdecl SetActiveCubeQTask_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  int v2; // ebx

  v2 = 0;
  ptQTask[1].ptNext = (struct QTask_s *)World_ptActiveWorld;
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
  ptQTask[3].ptNext = (struct QTask_s *)10;
  sprintf((char *const)&ptQTask[3].ptPrev, (char *const)&g_zInitialValue);
  if ( SetActiveCubeQTask_aptActiveQTask[0] )
  {
    while ( SetActiveCubeQTask_aptActiveQTask[++v2] )
      ;
  }
  SetActiveCubeQTask_aptActiveQTask[v2] = (struct SetActiveCubeQTask_t *)ptQTask;
}

// source: h/2/setactivecubetask.c:129  [anchor-mhash]
void __cdecl SetActiveCubeQTask_DeleteHandler(struct QTask_s *ptQTask)
{
  int v1; // eax
  struct SetActiveCubeQTask_t *v2; // esi

  v1 = 0;
  if ( (struct QTask_s *)SetActiveCubeQTask_aptActiveQTask[0] != ptQTask )
  {
    do
      v2 = SetActiveCubeQTask_aptActiveQTask[++v1];
    while ( v2 != (struct SetActiveCubeQTask_t *)ptQTask );
  }
  SetActiveCubeQTask_aptActiveQTask[v1] = nullptr;
}

// source: h/2/setactivecubetask.c:163  [anchor-mhash]
void __cdecl SetActiveCubeQTask_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { double v8; };
    struct { char igi2_o1[8]; int nCubeSize; };
    struct { char igi2_o2[8]; double nCubeSizea; };
    struct { char igi2_o3[16]; double v11; };
    struct { char igi2_o4[24]; struct real64x3_t tNewPos; };
    struct { char igi2_o5[48]; struct real64x3_t tOrigo; };
    char igi2_extent[72];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v2; // edx
  int *ptNext; // ecx
  double v4; // st7
  double v5; // st6
  double v6; // st5
  double v7; // st4

  v2 = 0x40000000 >> (int)ptQTask[3].ptNext;
  qmemcpy(&igi2_frame.tNewPos, &ptQTask[1].tQTaskChildren, sizeof(igi2_frame.tNewPos));
  ptNext = (int *)ptQTask[1].ptNext;
  igi2_frame.nCubeSize = 2 * v2;
  v4 = (double)ptNext[95];
  v2 *= -2;
  v5 = (double)ptNext[96];
  v6 = (double)ptNext[97];
  igi2_frame.tOrigo.vZ = v6;
  igi2_frame.tNewPos.vY = igi2_frame.tNewPos.vY + v5;
  igi2_frame.tNewPos.vZ = igi2_frame.tNewPos.vZ + v6;
  v7 = (double)(int)(v2 & (__int64)(igi2_frame.tNewPos.vX + v4));
  igi2_frame.v11 = (double)(int)(v2 & (__int64)igi2_frame.tNewPos.vY);
  igi2_frame.v8 = (double)(int)(v2 & (__int64)igi2_frame.tNewPos.vZ);
  igi2_frame.nCubeSizea = (double)igi2_frame.nCubeSize;
  *(double *)&ptQTask[1].ptParent = v7 - v4;
  *(double *)&ptQTask[2].ptNext = igi2_frame.v11 - v5;
  *(double *)&ptQTask[2].tQTaskChildren.ptHead = igi2_frame.v8 - v6;
  *(double *)&ptQTask[2].tQTaskChildren.ptTail = igi2_frame.nCubeSizea + v7 - v4;
  *(double *)&ptQTask[2].tQTaskRefList.ptMiddle = igi2_frame.nCubeSizea + igi2_frame.v11 - v5;
  *(double *)&ptQTask[2].ptParent = igi2_frame.nCubeSizea + igi2_frame.v8 - igi2_frame.tOrigo.vZ;
}

// source: h/2/setactivecubetask.c:220  [size]
void __cdecl SetActiveCubeQTask_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = SetActiveCubeQTask_ptParameterList;
}

// source: h/2/setactivecubetask.c:256  [anchor-mhash]
void __cdecl SetActiveCubeQTask_GetCameraTargetInfoHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *ptNext; // ecx

  qmemcpy(pxContext, &ptQTask[1].tQTaskChildren, 0x18u);
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
  ptNext = ptQTask[3].ptNext;
  *((_DWORD *)pxContext + 20) = 0;
  *((float *)pxContext + 19) = (double)(0x40000000 >> (char)ptNext) * 4.0;
}

// source: h/2/setactivecubetask.c:294  [size]
void __cdecl SetActiveCubeQTask_Write(char *zFileName)
{
  ;
}

// source: h/2/setactivecubetask.c:369  [anchor-hash]
void __cdecl SetActiveCubeQTask_Open()
{
  unsigned __int16 v0; // si
  struct ParameterList_s *v1; // eax
  int v2; // edx

  memset(SetActiveCubeQTask_aptActiveQTask, 0, sizeof(SetActiveCubeQTask_aptActiveQTask));
  v0 = QTask_NewQTaskType("CubeModifier", 384, EditorRigidObj_eQTaskType, 0, 0);
  SetActiveCubeQTask_eQTaskType = v0;
  QTask_LinkQTaskEventHandlerFn(v0, 0, SetActiveCubeQTask_CreateHandler);
  QTask_LinkQTaskEventHandlerFn(v0, 8, SetActiveCubeQTask_GetCameraTargetInfoHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 2, SetActiveCubeQTask_DeleteHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))SetActiveCubeQTask_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    ParameterList_eUpdateInternalDataQTaskEvent,
    SetActiveCubeQTask_UpdateInternalDataHandler);
  v1 = (struct ParameterList_s *)Mem_AllocFn(72, 4);
  v2 = Level_eParameterTypeObjectPos;
  v1->ptParameterListItem = (struct ParameterListItem_s *)&v1[1];
  v1->nParameters = 0;
  v1->nMaxParameters = 3;
  SetActiveCubeQTask_ptParameterList = v1;
  ParameterList_AddParameter(v1, 0x30u, v2, "Position", 7u, nullptr);
  ParameterList_AddParameter(SetActiveCubeQTask_ptParameterList, 0x78u, Level_eParameterTypeInt32, "Level", 7u, nullptr);
  ParameterList_AddParameter(
    SetActiveCubeQTask_ptParameterList,
    0x7Cu,
    Level_eParameterTypeString256,
    "Expression",
    7u,
    nullptr);
}

// source: h/2/setactivecubetask.c:409  [size]
void __cdecl SetActiveCubeQTask_Close()
{
  int v0; // esi

  if ( SetActiveCubeQTask_ptParameterList )
  {
    v0 = *(_DWORD *)((unsigned int)&SetActiveCubeQTask_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
  QTask_DeleteQTaskType(SetActiveCubeQTask_eQTaskType);
}

// source: h/2/setactivecubetask.c:427  [size]
unsigned __int16 __cdecl SetActiveCubeQTask_GetQTaskType()
{
  return SetActiveCubeQTask_eQTaskType;
}
