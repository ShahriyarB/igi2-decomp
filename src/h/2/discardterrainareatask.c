/* h/2/discardterrainareatask.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: h/2/discardterrainareatask.c:70  [anchor-mhash]
int __cdecl DiscardTerrainAreaTask_FindCubeStatus(
        struct DiscardTerrainAreaTask_t *ptDiscardTerrainAreaTask,
        int nCubeSize,
        struct real64x3_t *ptPos)
{
  #pragma pack(push, 1)
  union
  {
    struct { int iXStep; };
    struct { char igi2_o1[4]; struct real64x3_t tCheckPos; };
    struct { char igi2_o2[32]; struct QMaterial_t *ptMaterial; };
    struct { char igi2_o3[36]; double vCheckDist; };
    struct { char igi2_o4[44]; struct CollisionEvaluateContext_s tContext; };
    struct { char igi2_o5[52]; double v13; };
    struct { char igi2_o6[60]; struct real64x3_t tGetMaterialCheckPos; };
    struct { char igi2_o7[84]; struct QIntersection_s tIntersection; };
    char igi2_extent[208];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  double v3; // st7
  int v4; // ebx
  int v5; // ebp
  bool v6; // cc

  v3 = (double)nCubeSize;
  igi2_frame.vCheckDist = -v3;
  qmemcpy(&igi2_frame.tCheckPos, ptPos, sizeof(igi2_frame.tCheckPos));
  igi2_frame.v13 = v3 * 0.5;
  igi2_frame.tCheckPos.vX = igi2_frame.tCheckPos.vX - igi2_frame.v13;
  igi2_frame.tContext.ptQTask = &ptDiscardTerrainAreaTask->tEditorRigidObj.tQTask;
  igi2_frame.tCheckPos.vY = igi2_frame.tCheckPos.vY - igi2_frame.v13;
  v4 = nCubeSize / 4096;
  igi2_frame.tCheckPos.vZ = igi2_frame.v13 + igi2_frame.tCheckPos.vZ;
  igi2_frame.iXStep = 0;
  if ( nCubeSize / 4096 > 0 )
  {
    while ( 2 )
    {
      v5 = 0;
      do
      {
        World_GetNextZ(World_ptActiveWorld, &igi2_frame.tIntersection, &igi2_frame.tCheckPos, 1, &igi2_frame.vCheckDist, 512, nullptr, 0x80000000);
        if ( !igi2_frame.tIntersection.isHit )
          return 2;
        if ( -igi2_frame.vCheckDist < igi2_frame.tIntersection.vDistance )
          return 2;
        qmemcpy(&igi2_frame.tGetMaterialCheckPos, &igi2_frame.tIntersection.tPos, sizeof(igi2_frame.tGetMaterialCheckPos));
        igi2_frame.tGetMaterialCheckPos.vZ = igi2_frame.tIntersection.tPos.vZ + 40.96;
        World_GetMaterial(World_ptActiveWorld, &igi2_frame.ptMaterial, &igi2_frame.tGetMaterialCheckPos, 1, 13, &igi2_frame.tContext, 0xFFFFFFFF);
        if ( igi2_frame.ptMaterial->vDensity == 0.0 )
          return 2;
        ++v5;
        igi2_frame.tCheckPos.vY = igi2_frame.tCheckPos.vY + 4096.0;
      }
      while ( v5 < v4 );
      v6 = ++igi2_frame.iXStep < v4;
      igi2_frame.tCheckPos.vY = ptPos->vY - igi2_frame.v13;
      igi2_frame.tCheckPos.vX = igi2_frame.tCheckPos.vX + 4096.0;
      if ( v6 )
        continue;
      break;
    }
  }
  return 1;
}

// source: h/2/discardterrainareatask.c:166  [anchor-mhash]
void __cdecl DiscardTerrainAreaTask_CreateDiscardTerrainTasksRecursive(
        struct DiscardTerrainAreaTask_t *ptDiscardTerrainAreaTask,
        int nLevel,
        int nCubeSize,
        struct real64x3_t *ptPos)
{
  #pragma pack(push, 1)
  union
  {
    struct { double v8; };
    struct { char igi2_o1[8]; struct real64x3_t tSubCubePos; };
    struct { char igi2_o2[32]; double avAddX[8]; };
    struct { char igi2_o3[96]; double avAddY[8]; };
    struct { char igi2_o4[160]; double avAddZ[8]; };
    struct { char igi2_o5[224]; double v13; };
    char igi2_extent[236];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct real64x3_t *v4; // esi
  double v5; // st7
  int v6; // ebx
  double v7; // st6

  if ( nLevel <= ptDiscardTerrainAreaTask->nMaxLevel )
  {
    v4 = ptPos;
    if ( DiscardTerrainAreaTask_FindCubeStatus(ptDiscardTerrainAreaTask, nCubeSize, ptPos) == 1 )
    {
      DiscardTerrainTask_New(&ptDiscardTerrainAreaTask->tEditorRigidObj.tQTask, ptPos, nLevel);
    }
    else
    {
      v5 = (double)nCubeSize;
      igi2_frame.v13 = v5;
      igi2_frame.avAddX[0] = 0.25;
      igi2_frame.v8 = 0.5 * v5;
      igi2_frame.avAddX[1] = 0.75;
      igi2_frame.avAddX[2] = 0.25;
      igi2_frame.avAddX[3] = 0.75;
      igi2_frame.avAddX[4] = 0.25;
      igi2_frame.avAddX[5] = 0.75;
      igi2_frame.avAddX[6] = 0.25;
      igi2_frame.avAddX[7] = 0.75;
      igi2_frame.avAddY[0] = 0.25;
      igi2_frame.avAddY[1] = 0.25;
      igi2_frame.avAddY[2] = 0.75;
      igi2_frame.avAddY[3] = 0.75;
      igi2_frame.avAddY[4] = 0.25;
      igi2_frame.avAddY[5] = 0.25;
      igi2_frame.avAddY[6] = 0.75;
      igi2_frame.avAddY[7] = 0.75;
      igi2_frame.avAddZ[0] = 0.25;
      igi2_frame.avAddZ[1] = 0.25;
      igi2_frame.avAddZ[2] = 0.25;
      igi2_frame.avAddZ[3] = 0.25;
      igi2_frame.avAddZ[4] = 0.75;
      igi2_frame.avAddZ[5] = 0.75;
      igi2_frame.avAddZ[6] = 0.75;
      igi2_frame.avAddZ[7] = 0.75;
      v6 = 0;
      while ( 1 )
      {
        v7 = v5 * igi2_frame.avAddX[v6];
        qmemcpy(&igi2_frame.tSubCubePos, v4, sizeof(igi2_frame.tSubCubePos));
        igi2_frame.tSubCubePos.vX = v7 - igi2_frame.v8 + igi2_frame.tSubCubePos.vX;
        igi2_frame.tSubCubePos.vY = v5 * igi2_frame.avAddY[v6] - igi2_frame.v8 + igi2_frame.tSubCubePos.vY;
        igi2_frame.tSubCubePos.vZ = v5 * igi2_frame.avAddZ[v6] - igi2_frame.v8 + igi2_frame.tSubCubePos.vZ;
        DiscardTerrainAreaTask_CreateDiscardTerrainTasksRecursive(
          ptDiscardTerrainAreaTask,
          nLevel + 1,
          nCubeSize / 2,
          &igi2_frame.tSubCubePos);
        if ( ++v6 >= 8 )
          break;
        v5 = igi2_frame.v13;
        v4 = ptPos;
      }
    }
  }
}

// source: h/2/discardterrainareatask.c:223  [size]
void __cdecl DiscardTerrainAreaTask_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ptQTask[1].ptNext = nullptr;
  ptQTask[1].ptPrev = nullptr;
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
  ptQTask[2].ptParent = (struct QTask_s *)12;
  *(_DWORD *)&ptQTask[2].eQTaskType = 16;
  LOBYTE(ptQTask[3].ptNext) = 0;
}

// source: h/2/discardterrainareatask.c:261  [size]
void __cdecl DiscardTerrainAreaTask_DeleteHandler(struct QTask_s *ptQTask)
{
  ;
}

// source: h/2/discardterrainareatask.c:280  [anchor-mhash]
void __cdecl DiscardTerrainAreaTask_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { int nCubeSize; };
    struct { char igi2_o1[12]; double nY; };
    struct { char igi2_o2[20]; double nZ; };
    struct { char igi2_o3[28]; struct real64x3_t tNewPos; };
    struct { char igi2_o4[52]; struct real64x3_t tNewMax; };
    struct { char igi2_o5[76]; struct real64x3_t tNewMin; };
    char igi2_extent[100];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v2; // eax
  double nX; // st7
  double v4; // st6
  double v5; // st5
  double v6; // st4
  double v7; // st4
  double v8; // st7

  v2 = 0x40000000 >> (int)ptQTask[2].ptParent;
  qmemcpy(&igi2_frame.tNewPos, &ptQTask[1], sizeof(igi2_frame.tNewPos));
  igi2_frame.nCubeSize = 2 * v2;
  nX = (double)World_ptActiveWorld->tOrigo.nX;
  v2 *= -2;
  igi2_frame.nY = (double)World_ptActiveWorld->tOrigo.nY;
  igi2_frame.tNewPos.vY = igi2_frame.nY + igi2_frame.tNewPos.vY;
  igi2_frame.nZ = (double)World_ptActiveWorld->tOrigo.nZ;
  igi2_frame.tNewPos.vZ = igi2_frame.nZ + igi2_frame.tNewPos.vZ;
  v4 = (double)(int)(v2 & (__int64)(igi2_frame.tNewPos.vX + nX));
  v5 = (double)(int)(v2 & (__int64)igi2_frame.tNewPos.vY);
  igi2_frame.tNewMin.vZ = (double)(int)(v2 & (__int64)igi2_frame.tNewPos.vZ);
  v6 = (double)igi2_frame.nCubeSize;
  igi2_frame.tNewMax.vX = v6 + v4;
  igi2_frame.tNewMax.vY = v6 + v5;
  igi2_frame.tNewMax.vZ = igi2_frame.tNewMin.vZ + v6;
  v7 = v6 * 0.5;
  igi2_frame.tNewPos.vY = v7 + v5;
  igi2_frame.tNewPos.vX = v7 + v4 - nX;
  igi2_frame.tNewPos.vY = igi2_frame.tNewPos.vY - igi2_frame.nY;
  igi2_frame.tNewPos.vZ = v7 + igi2_frame.tNewMin.vZ - igi2_frame.nZ;
  igi2_frame.tNewMin.vX = v4 - nX;
  igi2_frame.tNewMin.vY = v5 - igi2_frame.nY;
  igi2_frame.tNewMin.vZ = igi2_frame.tNewMin.vZ - igi2_frame.nZ;
  LOBYTE(v2) = ptQTask[3].ptNext;
  igi2_frame.tNewMax.vX = igi2_frame.tNewMax.vX - nX;
  v8 = igi2_frame.tNewMax.vY - igi2_frame.nY;
  qmemcpy(&ptQTask[1].tQTaskRefList.ptMiddle, &igi2_frame.tNewMin, 0x18u);
  igi2_frame.tNewMax.vY = v8;
  igi2_frame.tNewMax.vZ = igi2_frame.tNewMax.vZ - igi2_frame.nZ;
  qmemcpy(&ptQTask[2].tQTaskChildren, &igi2_frame.tNewMax, 0x18u);
  if ( (_BYTE)v2 )
  {
    QTask_DeleteChildren(ptQTask);
    DiscardTerrainAreaTask_CreateDiscardTerrainTasksRecursive(
      (struct DiscardTerrainAreaTask_t *)ptQTask,
      (int)ptQTask[2].ptParent,
      igi2_frame.nCubeSize,
      &igi2_frame.tNewPos);
    LOBYTE(ptQTask[3].ptNext) = 0;
  }
}

// source: h/2/discardterrainareatask.c:362  [size]
void __cdecl DiscardTerrainAreaTask_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = DiscardTerrainAreaTask_ptParameterList;
}

// source: h/2/discardterrainareatask.c:378  [size]
void __cdecl DiscardTerrainAreaTask_GetCameraTargetInfoHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *ptParent; // ecx

  qmemcpy(pxContext, &ptQTask[1], 0x18u);
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
  ptParent = ptQTask[2].ptParent;
  *((_DWORD *)pxContext + 20) = 0;
  *((float *)pxContext + 19) = (float)(0x40000000 >> (char)ptParent);
}

// source: h/2/discardterrainareatask.c:443  [anchor-hash]
void __cdecl DiscardTerrainAreaTask_Open()
{
  unsigned __int16 v0; // si
  struct ParameterList_s *v1; // eax
  int v2; // edx

  v0 = QTask_NewQTaskType("DiscardTerrainArea", 128, RigidDynCubeObj_eQTaskType, 0, 0);
  DiscardTerrainAreaTask_eQTaskType = v0;
  QTask_LinkQTaskEventHandlerFn(v0, 0, (void (__cdecl *)(struct QTask_s *, void *))DiscardTerrainAreaTask_CreateHandler);
  QTask_LinkQTaskEventHandlerFn(v0, 8, DiscardTerrainAreaTask_GetCameraTargetInfoHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(
    v0,
    2,
    (void (__cdecl *)(struct QTask_s *))DiscardTerrainAreaTask_DeleteHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))DiscardTerrainAreaTask_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    ParameterList_eUpdateInternalDataQTaskEvent,
    DiscardTerrainAreaTask_UpdateInternalDataHandler);
  v1 = (struct ParameterList_s *)Mem_AllocFn(92, 4);
  v2 = Level_eParameterTypeObjectPos;
  v1->ptParameterListItem = (struct ParameterListItem_s *)&v1[1];
  v1->nParameters = 0;
  v1->nMaxParameters = 4;
  DiscardTerrainAreaTask_ptParameterList = v1;
  ParameterList_AddParameter(v1, 0x28u, v2, "Position", 7u, nullptr);
  ParameterList_AddParameter(
    DiscardTerrainAreaTask_ptParameterList,
    0x70u,
    Level_eParameterTypeInt32,
    "Level",
    7u,
    nullptr);
  ParameterList_AddParameter(
    DiscardTerrainAreaTask_ptParameterList,
    0x74u,
    Level_eParameterTypeInt32,
    "Max Level",
    7u,
    nullptr);
  ParameterList_AddParameter(
    DiscardTerrainAreaTask_ptParameterList,
    0x78u,
    Level_eParameterTypebool8,
    "Create cubes",
    7u,
    nullptr);
}

// source: h/2/discardterrainareatask.c:474  [size]
void __cdecl DiscardTerrainAreaTask_Close()
{
  int v0; // esi

  if ( DiscardTerrainAreaTask_ptParameterList )
  {
    v0 = *(_DWORD *)((unsigned int)&DiscardTerrainAreaTask_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
  QTask_DeleteQTaskType(DiscardTerrainAreaTask_eQTaskType);
}

// source: h/2/discardterrainareatask.c:491  [size]
unsigned __int16 __cdecl DiscardTerrainAreaTask_GetQTaskType()
{
  return DiscardTerrainAreaTask_eQTaskType;
}
