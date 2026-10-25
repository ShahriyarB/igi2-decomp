/* e/3/pc/pc_bonedyncubeobj.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: e/3/pc/pc_bonedyncubeobj.c:38  [size]
void __cdecl BoneDynCubeObj_EnterHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct DrawBoneMeshContext_t tContext; };
    struct { char igi2_o1[24]; struct MagicObjEnterContext_s tMagicObjEnterContext; };
    char igi2_extent[96];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v2; // ebx
  int v3; // edx
  int v4; // eax
  struct QTask_s *ptNext; // eax
  struct QTask_s *ptHead; // eax
  int v7; // edx
  int v8; // eax
  struct QTask_s *v9; // ecx
  void (__cdecl *pfHandler)(int, struct MagicObjEnterContext_s *); // ecx
  int v11; // eax
  struct QTask_s *v12; // ebp
  struct QTask_s *v13; // ecx
  struct QTask_s *v14; // edx
  void (__cdecl *v15)(struct QTask_s *, struct MagicObjEnterContext_s *); // edx
  int v16; // eax

  if ( ptQTask[7].tQTaskRefList.ptTail )
    BoneDynCubeObj_UpdateHierarchy((struct BoneDynCubeObj_s *)ptQTask);
  igi2_frame.tContext.isExcludeTestPassed = 0;
  igi2_frame.tMagicObjEnterContext.isExcludeTestPassed = 0;
  if ( pxContext && *(_DWORD *)pxContext )
  {
    igi2_frame.tContext.isExcludeTestPassed = 1;
    igi2_frame.tMagicObjEnterContext.isExcludeTestPassed = 1;
  }
  v2 = Lightsource_nLightDataStackPos + Lightsource_nLightDataBufferPos;
  igi2_frame.tContext.tLightContext.nLightNum = Lightsource_nLightDataStackPos;
  v3 = Hazinglayers_iHazingBuffer;
  igi2_frame.tContext.tLightContext.pnLightList = (int *)(4 * Lightsource_nLightDataBufferPos + 140666816);
  v4 = Hazinglayers_iHazingStack;
  qmemcpy(igi2_frame.tContext.tLightContext.pnLightList, Lightsource_anLightDataStack, 4 * Lightsource_nLightDataStackPos);
  igi2_frame.tContext.ptBoneDynCubeObj = (struct BoneDynCubeObj_s *)ptQTask;
  igi2_frame.tContext.tLightContext.pptHazingList = (struct HazingDynCubeObj_t **)(4 * v3 + 129834072);
  qmemcpy(igi2_frame.tContext.tLightContext.pptHazingList, Hazinglayers_aptHazingStack, 4 * v4);
  igi2_frame.tContext.tLightContext.nNumHazingBox = v4;
  Lightsource_nLightDataBufferPos = v2;
  Hazinglayers_iHazingBuffer = v4 + v3;
  RenderMode_tActiveRenderMode.apfRenderModeMethod[Mesh3D_eDrawBoneMeshRenderModeMethod](&igi2_frame.tContext);
  ptNext = ptQTask[3].ptNext;
  igi2_frame.tMagicObjEnterContext.isExcludeTestPassed = 1;
  qmemcpy(&igi2_frame.tMagicObjEnterContext, &ptQTask[1], 0x18u);
  qmemcpy(
    &igi2_frame.tMagicObjEnterContext.tParentOrientation,
    &ptQTask[3].ptPrev,
    sizeof(igi2_frame.tMagicObjEnterContext.tParentOrientation));
  if ( ptNext && (ptHead = ptNext->tQTaskChildren.ptHead, ptHead->ptNext) && (v7 = (int)ptHead) != 0 )
  {
    v8 = QTask_nProtectedQTaskStackOffset;
    do
    {
      if ( *(_DWORD *)v7 )
        v9 = **(_DWORD **)v7 != 0 ? *(struct QTask_s **)v7 : nullptr;
      else
        v9 = nullptr;
      QTask_atProtectedQTaskStack[v8].ptQTask = v9;
      pfHandler = (void (__cdecl *)(int, struct MagicObjEnterContext_s *))QTask_aatQTaskFinalEvent[MagicObj_eMagicObjEnterEvent][*(unsigned __int16 *)(v7 + 36)].pfHandler;
      v11 = v8 + 1;
      QTask_nProtectedQTaskStackOffset = v11;
      if ( pfHandler )
      {
        pfHandler(v7, &igi2_frame.tMagicObjEnterContext);
        v11 = QTask_nProtectedQTaskStackOffset;
      }
      v7 = dword_849C7DC[v11];
      v8 = v11 - 1;
      QTask_nProtectedQTaskStackOffset = v8;
    }
    while ( v7 );
  }
  else
  {
    v8 = QTask_nProtectedQTaskStackOffset;
  }
  v12 = ptQTask->tQTaskChildren.ptHead;
  if ( v12->ptNext )
  {
    v13 = ptQTask->tQTaskChildren.ptHead;
    if ( v12 )
    {
      do
      {
        if ( v13->ptNext )
          v14 = v13->ptNext->ptNext != nullptr ? v13->ptNext : nullptr;
        else
          v14 = nullptr;
        QTask_atProtectedQTaskStack[v8].ptQTask = v14;
        v15 = (void (__cdecl *)(struct QTask_s *, struct MagicObjEnterContext_s *))QTask_aatQTaskFinalEvent[MagicObj_eMagicObjEnterEvent][v13->eQTaskType].pfHandler;
        v16 = v8 + 1;
        QTask_nProtectedQTaskStackOffset = v16;
        if ( v15 )
        {
          v15(v13, &igi2_frame.tMagicObjEnterContext);
          v16 = QTask_nProtectedQTaskStackOffset;
        }
        v13 = (struct QTask_s *)dword_849C7DC[v16];
        v8 = v16 - 1;
        QTask_nProtectedQTaskStackOffset = v8;
      }
      while ( v13 );
    }
  }
}

// source: e/3/pc/pc_bonedyncubeobj.c:100  [anchor-mhash]
void __cdecl BoneDynCubeObj_GetClosestVertex(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { float vClipZ; };
    struct { char igi2_o1[4]; float Real32x3_Rotate_tTemp; };
    struct { char igi2_o2[8]; float Real32x3_Rotate_tTemp_4; };
    struct { char igi2_o3[12]; float Real32x3_Rotate_tTemp_8; };
    struct { char igi2_o4[16]; struct real32x3_t tPos; };
    char igi2_extent[28];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v2; // ecx
  double v3; // st7
  double v4; // st6
  int v5; // esi
  double v6; // st5
  double v7; // st7
  struct QTask_s *ptQTaska = *(struct QTask_s * *)&ptQTask; // [esp+20h] [ebp+4h] ARGSLOT

  igi2_frame.vClipZ = Direct3D_vWorldMinZ;
  if ( ptQTask[7].ptPrev == (struct QTask_s *)1 )
  {
    v2 = *(_DWORD *)&ptQTask[2].eQTaskType;
    if ( v2 )
    {
      v3 = *(double *)&ptQTask[1].ptNext - TransContext_tActiveTransContext.tPos.vX;
      v4 = *(double *)&ptQTask[1].tQTaskChildren.ptHead - TransContext_tActiveTransContext.tPos.vY;
      v5 = *(_DWORD *)(*(_DWORD *)(*(_DWORD *)v2 + 12) + 12);
      v6 = *(double *)&ptQTask[1].tQTaskChildren.ptTail - TransContext_tActiveTransContext.tPos.vZ;
      igi2_frame.Real32x3_Rotate_tTemp = TransContext_tActiveTransContext.tMatrix.tX.vZ * v6
                            + TransContext_tActiveTransContext.tMatrix.tX.vY * v4
                            + TransContext_tActiveTransContext.tMatrix.tX.vX * v3;
      igi2_frame.tPos.vX = igi2_frame.Real32x3_Rotate_tTemp;
      igi2_frame.Real32x3_Rotate_tTemp_4 = TransContext_tActiveTransContext.tMatrix.tY.vZ * v6
                              + TransContext_tActiveTransContext.tMatrix.tY.vY * v4
                              + TransContext_tActiveTransContext.tMatrix.tY.vX * v3;
      igi2_frame.tPos.vY = igi2_frame.Real32x3_Rotate_tTemp_4;
      ptQTaska = ptQTask[8].ptNext;
      igi2_frame.Real32x3_Rotate_tTemp_8 = TransContext_tActiveTransContext.tMatrix.tZ.vZ * v6
                              + TransContext_tActiveTransContext.tMatrix.tZ.vY * v4
                              + TransContext_tActiveTransContext.tMatrix.tZ.vX * v3;
      igi2_frame.tPos.vZ = igi2_frame.Real32x3_Rotate_tTemp_8;
      if ( Mesh3D_ExcludeObject(&igi2_frame.tPos, *(float *)&ptQTaska, nullptr) == false )
      {
        v7 = igi2_frame.tPos.vZ - *(float *)(v5 + 60);
        if ( v7 <= *((float *)pxContext + 2) )
        {
          if ( igi2_frame.vClipZ > v7 )
            v7 = igi2_frame.vClipZ;
          *((float *)pxContext + 2) = v7;
        }
      }
    }
  }
}

// source: e/3/pc/pc_bonedyncubeobj.c:163  [anchor-callee]
void __cdecl BoneDynCubeObj_InitBloodStains(struct BoneDynCubeObj_s *ptBoneDynCubeObj)
{
  struct LODVirModel_s *ptLODVirModel; // eax
  _DWORD *pxRenderMesh; // esi
  int i; // eax

  if ( !ptBoneDynCubeObj->abBloodStains )
  {
    ptLODVirModel = ptBoneDynCubeObj->tModelObj.ptLODVirModel;
    if ( ptLODVirModel )
    {
      pxRenderMesh = ptLODVirModel->aptVirModel[0]->ptModel->ptMesh->pxRenderMesh;
      if ( pxRenderMesh )
      {
        ptBoneDynCubeObj->abBloodStains = (unsigned int *)Mem_AllocFn(4 * pxRenderMesh[4], 4);
        for ( i = 0; i < (int)(pxRenderMesh[4]); ++i )
          ptBoneDynCubeObj->abBloodStains[i] = -1;
      }
    }
  }
}

// source: e/3/pc/pc_bonedyncubeobj.c:201  [anchor-callee]
void __cdecl BoneDynCubeObj_DeInitBloodStains(struct BoneDynCubeObj_s *ptBoneDynCubeObj)
{
  unsigned int *abBloodStains; // eax
  int v2; // esi

  abBloodStains = ptBoneDynCubeObj->abBloodStains;
  if ( abBloodStains )
  {
    v2 = *(_DWORD *)((unsigned int)(abBloodStains - 1) & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v2);
    memset(*(void **)(v2 + 8), 0xCDu, *(_DWORD *)(v2 + 16));
    free((void *)v2);
    ptBoneDynCubeObj->abBloodStains = nullptr;
  }
}

// source: e/3/pc/pc_bonedyncubeobj.c:218  [anchor-hash]
void __cdecl BoneDynCubeObj_Open()
{
  BoneDynCubeObj_GenericOpen();
  QTask_LinkQTaskEventHandlerFn(
    BoneDynCubeObj_eQTaskType,
    QCube_eGetClosestVertexQTaskEvent,
    BoneDynCubeObj_GetClosestVertex);
}

// source: e/3/pc/pc_bonedyncubeobj.c:235  [size]
void __cdecl BoneDynCubeObj_Close()
{
  QTask_DeleteQTaskType(BoneDynCubeObj_eQTaskType);
  BoneDynCubeObj_eQTaskType = 512;
  QTask_DeleteQTaskEvent(BoneDynCubeObj_eQTaskCollisionEvalEvent);
  BoneDynCubeObj_eQTaskCollisionEvalEvent = 512;
  QTask_DeleteQTaskEventNoContext(BoneDynCubeObj_eInterpolateQTaskEvent);
  BoneDynCubeObj_eInterpolateQTaskEvent = 512;
}
