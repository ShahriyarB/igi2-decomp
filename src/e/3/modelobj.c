/* e/3/modelobj.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: e/3/modelobj.c:66  [size]
void __cdecl ModelObj_AttachHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *((_DWORD *)pxContext + 5) = 0;
  *((_DWORD *)pxContext + 4) = 0;
  *((_DWORD *)pxContext + 3) = (char *)ptQTask + 124;
  *((_DWORD *)pxContext + 2) = ptQTask + 1;
}

// source: e/3/modelobj.c:93  [anchor-mhash]
void __cdecl ModelObj_UpdateAttachmentHandler(struct QTask_s *ptQTask)
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
  }
}

// source: e/3/modelobj.c:138  [anchor-mhash]
void __cdecl ModelObj_ParentChangedHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QReference_s *ptMiddle; // ebp

  ptMiddle = ptQTask[5].tQTaskRefList.ptMiddle;
  memset(&ptQTask[5].tQTaskChildren.ptTail, 0, 0x1Cu);
  QTask_TriggerQTaskEventParent(ptQTask, Attach_eAttachEvent, &ptQTask[5].tQTaskChildren.ptTail);
  if ( ptMiddle != ptQTask[5].tQTaskRefList.ptMiddle )
  {
    ptQTask[5].tQTaskRefList.ptHead = nullptr;
    ptQTask[5].tQTaskChildren.ptTail = (struct QTask_s *)-1;
    ModelObj_CalcRelativePosAndOrientation((struct ModelObj_s *)ptQTask);
  }
}

// source: e/3/modelobj.c:170  [size]
void __cdecl ModelObj_RemoveHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *ptHead; // ecx
  int v3; // eax
  struct QTask_s *v4; // edx
  void (__cdecl *pfHandler)(struct QTask_s *, void *); // edx
  int v6; // eax
  struct QTask_s *ptNext; // ecx
  int v8; // ecx
  struct QTask_s *v9; // edx
  void (__cdecl *v10)(int, void *); // edx
  int v11; // eax

  if ( ptQTask[2].tQTaskChildren.ptHead )
  {
    ptHead = ptQTask->tQTaskChildren.ptHead;
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
        pfHandler = (void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[DynCubeObj_eDynCubeObjRemoveQTaskEvent][ptHead->eQTaskType].pfHandler;
        v6 = v3 + 1;
        QTask_nProtectedQTaskStackOffset = v6;
        if ( pfHandler )
        {
          pfHandler(ptHead, pxContext);
          v6 = QTask_nProtectedQTaskStackOffset;
        }
        ptHead = (struct QTask_s *)dword_849C7DC[v6];
        v3 = v6 - 1;
        QTask_nProtectedQTaskStackOffset = v3;
      }
      while ( ptHead );
    }
    else
    {
      v3 = QTask_nProtectedQTaskStackOffset;
    }
    ptNext = ptQTask[3].ptNext;
    if ( ptNext )
    {
      v8 = (int)ptNext->tQTaskChildren.ptHead;
      if ( *(_DWORD *)v8 )
      {
        for ( ; v8; QTask_nProtectedQTaskStackOffset = v3 )
        {
          if ( *(_DWORD *)v8 )
            v9 = **(_DWORD **)v8 != 0 ? *(struct QTask_s **)v8 : nullptr;
          else
            v9 = nullptr;
          QTask_atProtectedQTaskStack[v3].ptQTask = v9;
          v10 = (void (__cdecl *)(int, void *))QTask_aatQTaskFinalEvent[DynCubeObj_eDynCubeObjRemoveQTaskEvent][*(unsigned __int16 *)(v8 + 36)].pfHandler;
          v11 = v3 + 1;
          QTask_nProtectedQTaskStackOffset = v11;
          if ( v10 )
          {
            v10(v8, pxContext);
            v11 = QTask_nProtectedQTaskStackOffset;
          }
          v8 = dword_849C7DC[v11];
          v3 = v11 - 1;
        }
      }
    }
    World_RemoveDynCubeObj(*(struct World_s **)pxContext, (struct DynCubeObj_s *)ptQTask);
  }
}

// source: e/3/modelobj.c:207  [anchor-mhash]
void __cdecl ModelObj_RegisterHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *ptNext; // eax
  struct QTask_s *ptHead; // eax
  int v4; // ecx
  int v5; // eax
  struct QTask_s *v6; // edx
  void (__cdecl *pfHandler)(int, void *); // edx
  int v8; // eax
  struct QTask_s *v9; // ecx
  struct QTask_s *v10; // edx
  void (__cdecl *v11)(struct QTask_s *, void *); // edx
  int v12; // eax

  if ( !ptQTask[2].tQTaskChildren.ptHead )
  {
    World_RegisterDynCubeObjFirstTimeRadius(
      *((struct World_s **)pxContext + 1),
      (struct DynCubeObj_s *)ptQTask,
      (struct real64x3_t *)&ptQTask[1],
      *(float *)&ptQTask[1].eQTaskType,
      *((enum DynCubeTreeCategory_enum *)pxContext + 2));
    ptNext = ptQTask[3].ptNext;
    if ( ptNext && (ptHead = ptNext->tQTaskChildren.ptHead, ptHead->ptNext) && (v4 = (int)ptHead) != 0 )
    {
      v5 = QTask_nProtectedQTaskStackOffset;
      do
      {
        if ( *(_DWORD *)v4 )
          v6 = **(_DWORD **)v4 != 0 ? *(struct QTask_s **)v4 : nullptr;
        else
          v6 = nullptr;
        QTask_atProtectedQTaskStack[v5].ptQTask = v6;
        pfHandler = (void (__cdecl *)(int, void *))QTask_aatQTaskFinalEvent[DynCubeObj_eDynCubeObjRegisterQTaskEvent][*(unsigned __int16 *)(v4 + 36)].pfHandler;
        v8 = v5 + 1;
        QTask_nProtectedQTaskStackOffset = v8;
        if ( pfHandler )
        {
          pfHandler(v4, pxContext);
          v8 = QTask_nProtectedQTaskStackOffset;
        }
        v4 = dword_849C7DC[v8];
        v5 = v8 - 1;
        QTask_nProtectedQTaskStackOffset = v5;
      }
      while ( v4 );
    }
    else
    {
      v5 = QTask_nProtectedQTaskStackOffset;
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
        QTask_atProtectedQTaskStack[v5].ptQTask = v10;
        v11 = (void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[DynCubeObj_eDynCubeObjRegisterQTaskEvent][v9->eQTaskType].pfHandler;
        v12 = v5 + 1;
        QTask_nProtectedQTaskStackOffset = v12;
        if ( v11 )
        {
          v11(v9, pxContext);
          v12 = QTask_nProtectedQTaskStackOffset;
        }
        v9 = (struct QTask_s *)dword_849C7DC[v12];
        v5 = v12 - 1;
        QTask_nProtectedQTaskStackOffset = v5;
      }
      while ( v9 );
    }
  }
}

// source: e/3/modelobj.c:250  [anchor-mhash]
void __cdecl ModelObj_GetShadowInfoHandler(struct QTask_s *ptQTask, void *pxContext)
{
  long double v2; // st7
  int *v3; // edi
  int v4; // edi
  long double v5; // st6

  if ( *((_DWORD *)pxContext + 2) )
  {
    v2 = sub_5C5840((struct real64x3_t *)&ptQTask[1], (struct World_s *)ptQTask[2].ptParent, 204800.0);
    *((float *)pxContext + 1) = v2;
    v3 = *(int **)&ptQTask[2].eQTaskType;
    if ( v3 )
    {
      v4 = *v3;
      if ( v4 )
      {
        v5 = v2 + *(float *)(*(_DWORD *)(*(_DWORD *)(v4 + 12) + 12) + 120);
        *((_DWORD *)pxContext + 4) = 0;
        *((float *)pxContext + 1) = v5;
        return;
      }
    }
    *((float *)pxContext + 1) = v2 + 1.0;
  }
  *((_DWORD *)pxContext + 4) = 0;
}

// source: e/3/modelobj.c:276  [anchor-callee]
struct ModelObj_s *__cdecl ModelObj_CalcRelativePosAndOrientation(struct ModelObj_s *ptModelObj)
{
  #pragma pack(push, 1)
  union
  {
    struct { float v13; };
    struct { char igi2_o1[28]; float Real32x9_Invert_tTemp_12; };
    struct { char igi2_o2[32]; float Real32x9_Invert_tTemp_16; };
    struct { char igi2_o3[36]; float Real32x9_Invert_tTemp_20; };
    struct { char igi2_o4[40]; float Real32x9_Invert_tTemp_24; };
    struct { char igi2_o5[44]; float Real32x9_Invert_tTemp_28; };
    struct { char igi2_o6[56]; struct real32x9_t Real32x9_Multiply_tTemp; };
    char igi2_extent[100];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct real64x3_t *ptParentPos; // edx
  struct real32x9_t *ptParentOrientation; // ecx
  double vX; // st7
  double v4; // st6
  double v5; // st5
  float vZ; // esi
  int nOps; // ecx
  double v8; // st4
  double v9; // st3
  double v10; // st4
  double v11; // rt0
  double v12; // st5
  struct real32x3_t struct_real32x3_t; // 0:^C.12

  ptParentPos = ptModelObj->tAttachContext.ptParentPos;
  if ( ptParentPos )
  {
    ptParentOrientation = ptModelObj->tAttachContext.ptParentOrientation;
    vX = ptParentOrientation->tX.vX;
    v4 = ptParentOrientation->tY.vX;
    igi2_frame.Real32x9_Invert_tTemp_12 = ptParentOrientation->tX.vY;
    v5 = ptParentOrientation->tZ.vX;
    igi2_frame.Real32x9_Invert_tTemp_16 = ptParentOrientation->tY.vY;
    igi2_frame.Real32x9_Invert_tTemp_20 = ptParentOrientation->tZ.vY;
    igi2_frame.Real32x9_Invert_tTemp_24 = ptParentOrientation->tX.vZ;
    igi2_frame.Real32x9_Invert_tTemp_28 = ptParentOrientation->tY.vZ;
    vZ = ptParentOrientation->tZ.vZ;
    nOps = ptParentOrientation->nOps;
    igi2_frame.Real32x9_Multiply_tTemp.tX.vX = vX * ptModelObj->tOrientation.tX.vX
                                  + v5 * ptModelObj->tOrientation.tZ.vX
                                  + v4 * ptModelObj->tOrientation.tY.vX;
    igi2_frame.Real32x9_Multiply_tTemp.tX.vY = v5 * ptModelObj->tOrientation.tZ.vY
                                  + v4 * ptModelObj->tOrientation.tY.vY
                                  + vX * ptModelObj->tOrientation.tX.vY;
    igi2_frame.Real32x9_Multiply_tTemp.tX.vZ = vX * ptModelObj->tOrientation.tX.vZ
                                  + v5 * ptModelObj->tOrientation.tZ.vZ
                                  + v4 * ptModelObj->tOrientation.tY.vZ;
    igi2_frame.Real32x9_Multiply_tTemp.tY.vX = igi2_frame.Real32x9_Invert_tTemp_12 * ptModelObj->tOrientation.tX.vX
                                  + igi2_frame.Real32x9_Invert_tTemp_20 * ptModelObj->tOrientation.tZ.vX
                                  + igi2_frame.Real32x9_Invert_tTemp_16 * ptModelObj->tOrientation.tY.vX;
    igi2_frame.Real32x9_Multiply_tTemp.tY.vY = igi2_frame.Real32x9_Invert_tTemp_20 * ptModelObj->tOrientation.tZ.vY
                                  + igi2_frame.Real32x9_Invert_tTemp_16 * ptModelObj->tOrientation.tY.vY
                                  + igi2_frame.Real32x9_Invert_tTemp_12 * ptModelObj->tOrientation.tX.vY;
    igi2_frame.Real32x9_Multiply_tTemp.tY.vZ = igi2_frame.Real32x9_Invert_tTemp_12 * ptModelObj->tOrientation.tX.vZ
                                  + igi2_frame.Real32x9_Invert_tTemp_20 * ptModelObj->tOrientation.tZ.vZ
                                  + igi2_frame.Real32x9_Invert_tTemp_16 * ptModelObj->tOrientation.tY.vZ;
    v8 = igi2_frame.Real32x9_Invert_tTemp_24 * ptModelObj->tOrientation.tX.vX + vZ * ptModelObj->tOrientation.tZ.vX;
    v9 = igi2_frame.Real32x9_Invert_tTemp_28 * ptModelObj->tOrientation.tY.vX;
    igi2_frame.Real32x9_Multiply_tTemp.nOps = ptModelObj->tOrientation.nOps + nOps + 1;
    igi2_frame.Real32x9_Multiply_tTemp.tZ.vX = v8 + v9;
    igi2_frame.Real32x9_Multiply_tTemp.tZ.vY = vZ * ptModelObj->tOrientation.tZ.vY
                                  + igi2_frame.Real32x9_Invert_tTemp_28 * ptModelObj->tOrientation.tY.vY
                                  + igi2_frame.Real32x9_Invert_tTemp_24 * ptModelObj->tOrientation.tX.vY;
    igi2_frame.Real32x9_Multiply_tTemp.tZ.vZ = igi2_frame.Real32x9_Invert_tTemp_24 * ptModelObj->tOrientation.tX.vZ
                                  + vZ * ptModelObj->tOrientation.tZ.vZ
                                  + igi2_frame.Real32x9_Invert_tTemp_28 * ptModelObj->tOrientation.tY.vZ;
    v10 = ptModelObj->tDynCubeObj.tQObj.tPos.vX;
    qmemcpy(&ptModelObj->tRelativeOrientation, &igi2_frame.Real32x9_Multiply_tTemp, sizeof(ptModelObj->tRelativeOrientation));
    ptModelObj->tRelativePos.vX = v10 - ptParentPos->vX;
    ptModelObj->tRelativePos.vY = ptModelObj->tDynCubeObj.tQObj.tPos.vY - ptParentPos->vY;
    igi2_frame.v13 = ptModelObj->tDynCubeObj.tQObj.tPos.vZ - ptParentPos->vZ;
    v11 = v5;
    v12 = v4 * ptModelObj->tRelativePos.vY;
    ptModelObj->tRelativePos.vZ = igi2_frame.v13;
    struct_real32x3_t.vX = v12 + igi2_frame.v13 * v11 + vX * ptModelObj->tRelativePos.vX;
    struct_real32x3_t.vY = igi2_frame.Real32x9_Invert_tTemp_16 * ptModelObj->tRelativePos.vY
                         + igi2_frame.v13 * igi2_frame.Real32x9_Invert_tTemp_20
                         + igi2_frame.Real32x9_Invert_tTemp_12 * ptModelObj->tRelativePos.vX;
    struct_real32x3_t.vZ = igi2_frame.Real32x9_Invert_tTemp_28 * ptModelObj->tRelativePos.vY
                         + igi2_frame.v13 * vZ
                         + igi2_frame.Real32x9_Invert_tTemp_24 * ptModelObj->tRelativePos.vX;
    ptModelObj->tRelativePos = struct_real32x3_t;
    return (struct ModelObj_s *)LODWORD(struct_real32x3_t.vZ);
  }
  return ptModelObj;
}

// source: e/3/modelobj.c:304  [anchor-callee]
void __cdecl ModelObj_Init(
        struct ModelObj_s *ptModelObj,
        struct World_s *ptWorld,
        struct LODVirModel_s *ptLODVirModel)
{
  struct LODVirModel_s *v3; // ecx

  memset(&ptModelObj->tDynCubeObj.tQObj.tPos, 0, 0x48u);
  v3 = ptModelObj->ptLODVirModel;
  ptModelObj->ptWorld = ptWorld;
  ptModelObj->tDynCubeObj.iRenderGroup = RenderGroup_Normal;
  ptModelObj->ptMagicObjContainer = nullptr;
  if ( v3 )
    ptModelObj->ptLODVirModel = nullptr;
  ptModelObj->tOrientation.tX.vX = 1.0;
  ptModelObj->tOrientation.tX.vY = 0.0;
  ptModelObj->tOrientation.tX.vZ = 0.0;
  ptModelObj->tOrientation.tY.vX = 0.0;
  ptModelObj->tOrientation.tY.vY = 1.0;
  ptModelObj->tOrientation.tY.vZ = 0.0;
  ptModelObj->tOrientation.tZ.vX = 0.0;
  ptModelObj->tOrientation.tZ.vY = 0.0;
  ptModelObj->tOrientation.tZ.vZ = 1.0;
  ptModelObj->tOrientation.nOps = 0;
  ptModelObj->tScale.vX = 1.0;
  ptModelObj->tScale.vY = 1.0;
  ptModelObj->tScale.vZ = 1.0;
  ptModelObj->nTransparency = 0;
  ptModelObj->aptAnimTexIndex[0] = nullptr;
  ptModelObj->aptAnimTexIndex[1] = nullptr;
  ptModelObj->aptAnimTexIndex[2] = nullptr;
  ptModelObj->aptAnimTexIndex[3] = nullptr;
  ptModelObj->aptAnimTexIndex[4] = nullptr;
  ptModelObj->tRelativeOrientation.tX.vX = 1.0;
  ptModelObj->tRelativeOrientation.tX.vY = 0.0;
  ptModelObj->tRelativeOrientation.tX.vZ = 0.0;
  ptModelObj->tRelativeOrientation.tY.vX = 0.0;
  ptModelObj->tRelativeOrientation.tY.vY = 1.0;
  ptModelObj->tRelativeOrientation.tY.vZ = 0.0;
  ptModelObj->tRelativeOrientation.tZ.vX = 0.0;
  ptModelObj->tRelativeOrientation.tZ.vY = 0.0;
  ptModelObj->tRelativeOrientation.tZ.vZ = 1.0;
  ptModelObj->tRelativeOrientation.nOps = 0;
  ptModelObj->tRelativePos.vX = 0.0;
  ptModelObj->tRelativePos.vY = 0.0;
  ptModelObj->tRelativePos.vZ = 0.0;
  ptModelObj->iLightCategory = 1;
  ptModelObj->eLayer = TRANSCONTEXT_LAYER_MIDDLE;
  memset(&ptModelObj->tAttachContext, 0, sizeof(ptModelObj->tAttachContext));
}

// source: e/3/modelobj.c:355  [anchor-mhash]
void __cdecl ModelObj_UpdateAttachment(struct ModelObj_s *ptModelObj)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct real64x3_t tNewPos; };
    struct { char igi2_o1[24]; float v29; };
    struct { char igi2_o2[28]; float v30; };
    struct { char igi2_o3[32]; float v31; };
    struct { char igi2_o4[44]; struct real32x3_t tRelativePos; };
    struct { char igi2_o5[56]; struct real32x9_t Real32x9_Multiply_tTemp; };
    struct { char igi2_o6[96]; struct real32x9_t tNewOrientation; };
    char igi2_extent[140];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct real32x9_t *ptBoneOrientation; // edx
  double vY; // st7
  struct real32x3_t *ptBonePos; // ecx
  double v4; // st7
  double v5; // st6
  double v6; // st5
  struct real32x9_t *ptParentOrientation; // ecx
  double vX; // st7
  double v9; // st7
  double v10; // st6
  double v11; // st5
  double v12; // st4
  double vZ; // st3
  int nOps; // ecx
  double v15; // st3
  int v16; // edx
  int v17; // ecx
  double v18; // st7
  double v19; // st6
  struct real32x9_t *v20; // ecx
  double v21; // st7
  double v22; // st7
  double v23; // st7
  int v24; // edx
  float vRealRadius; // edx
  struct real64x3_t *ptParentPos; // ecx
  double v27; // st7

  ptBoneOrientation = ptModelObj->tAttachContext.ptBoneOrientation;
  if ( ptBoneOrientation )
  {
    *(float *)&igi2_frame.tNewPos.vX = ptBoneOrientation->tX.vY * ptModelObj->tRelativePos.vY
                          + ptModelObj->tRelativePos.vX * ptBoneOrientation->tX.vX
                          + ptModelObj->tRelativePos.vZ * ptBoneOrientation->tX.vZ;
    vY = ptBoneOrientation->tY.vY;
    igi2_frame.tRelativePos.vX = *(float *)&igi2_frame.tNewPos.vX;
    *((float *)&igi2_frame.tNewPos.vX + 1) = vY * ptModelObj->tRelativePos.vY
                                + ptBoneOrientation->tY.vX * ptModelObj->tRelativePos.vX
                                + ptBoneOrientation->tY.vZ * ptModelObj->tRelativePos.vZ;
    *(float *)&igi2_frame.tNewPos.vY = ptModelObj->tRelativePos.vX * ptBoneOrientation->tZ.vX
                          + ptModelObj->tRelativePos.vZ * ptBoneOrientation->tZ.vZ
                          + ptBoneOrientation->tZ.vY * ptModelObj->tRelativePos.vY;
    igi2_frame.tRelativePos.vZ = *(float *)&igi2_frame.tNewPos.vY;
    ptBonePos = ptModelObj->tAttachContext.ptBonePos;
    v4 = *(float *)&igi2_frame.tNewPos.vX + ptBonePos->vX;
    v5 = *((float *)&igi2_frame.tNewPos.vX + 1) + ptBonePos->vY;
    v6 = *(float *)&igi2_frame.tNewPos.vY + ptBonePos->vZ;
    ptParentOrientation = ptModelObj->tAttachContext.ptParentOrientation;
    *(float *)&igi2_frame.tNewPos.vX = v6 * ptParentOrientation->tX.vZ
                          + v5 * ptParentOrientation->tX.vY
                          + v4 * ptParentOrientation->tX.vX;
    *(double *)&igi2_frame.tRelativePos.vX = igi2_frame.tNewPos.vX;
    *((float *)&igi2_frame.tNewPos.vX + 1) = v4 * ptParentOrientation->tY.vX
                                + v6 * ptParentOrientation->tY.vZ
                                + v5 * ptParentOrientation->tY.vY;
    igi2_frame.tRelativePos.vY = *((float *)&igi2_frame.tNewPos.vX + 1);
    *(float *)&igi2_frame.tNewPos.vY = v4 * ptParentOrientation->tZ.vX
                          + v6 * ptParentOrientation->tZ.vZ
                          + v5 * ptParentOrientation->tZ.vY;
    vX = ptBoneOrientation->tX.vX;
    igi2_frame.tRelativePos.vZ = *(float *)&igi2_frame.tNewPos.vY;
    v9 = vX * ptParentOrientation->tX.vX
       + ptParentOrientation->tX.vZ * ptBoneOrientation->tZ.vX
       + ptBoneOrientation->tY.vX * ptParentOrientation->tX.vY;
    v10 = ptBoneOrientation->tX.vY * ptParentOrientation->tX.vX
        + ptParentOrientation->tX.vZ * ptBoneOrientation->tZ.vY
        + ptParentOrientation->tX.vY * ptBoneOrientation->tY.vY;
    v11 = ptParentOrientation->tX.vZ * ptBoneOrientation->tZ.vZ
        + ptParentOrientation->tX.vY * ptBoneOrientation->tY.vZ
        + ptParentOrientation->tX.vX * ptBoneOrientation->tX.vZ;
    *((float *)&igi2_frame.tNewPos.vY + 1) = ptBoneOrientation->tY.vX * ptParentOrientation->tY.vY
                                + ptBoneOrientation->tZ.vX * ptParentOrientation->tY.vZ
                                + ptBoneOrientation->tX.vX * ptParentOrientation->tY.vX;
    *(float *)&igi2_frame.tNewPos.vZ = ptBoneOrientation->tY.vY * ptParentOrientation->tY.vY
                          + ptBoneOrientation->tX.vY * ptParentOrientation->tY.vX
                          + ptBoneOrientation->tZ.vY * ptParentOrientation->tY.vZ;
    *((float *)&igi2_frame.tNewPos.vZ + 1) = ptBoneOrientation->tY.vZ * ptParentOrientation->tY.vY
                                + ptParentOrientation->tY.vX * ptBoneOrientation->tX.vZ
                                + ptBoneOrientation->tZ.vZ * ptParentOrientation->tY.vZ;
    igi2_frame.v29 = ptParentOrientation->tZ.vX * ptBoneOrientation->tX.vX
        + ptBoneOrientation->tY.vX * ptParentOrientation->tZ.vY
        + ptParentOrientation->tZ.vZ * ptBoneOrientation->tZ.vX;
    igi2_frame.v30 = ptParentOrientation->tZ.vY * ptBoneOrientation->tY.vY
        + ptParentOrientation->tZ.vZ * ptBoneOrientation->tZ.vY
        + ptParentOrientation->tZ.vX * ptBoneOrientation->tX.vY;
    v12 = ptParentOrientation->tZ.vX * ptBoneOrientation->tX.vZ + ptParentOrientation->tZ.vY * ptBoneOrientation->tY.vZ;
    vZ = ptParentOrientation->tZ.vZ;
    nOps = ptParentOrientation->nOps;
    v15 = vZ * ptBoneOrientation->tZ.vZ;
    v16 = ptBoneOrientation->nOps;
    igi2_frame.v31 = v12 + v15;
    igi2_frame.Real32x9_Multiply_tTemp.tX.vX = v9 * ptModelObj->tRelativeOrientation.tX.vX
                                  + v11 * ptModelObj->tRelativeOrientation.tZ.vX
                                  + v10 * ptModelObj->tRelativeOrientation.tY.vX;
    igi2_frame.Real32x9_Multiply_tTemp.tX.vY = v9 * ptModelObj->tRelativeOrientation.tX.vY
                                  + v11 * ptModelObj->tRelativeOrientation.tZ.vY
                                  + v10 * ptModelObj->tRelativeOrientation.tY.vY;
    igi2_frame.Real32x9_Multiply_tTemp.tX.vZ = v9 * ptModelObj->tRelativeOrientation.tX.vZ
                                  + v11 * ptModelObj->tRelativeOrientation.tZ.vZ
                                  + v10 * ptModelObj->tRelativeOrientation.tY.vZ;
    igi2_frame.Real32x9_Multiply_tTemp.tY.vX = *((float *)&igi2_frame.tNewPos.vY + 1) * ptModelObj->tRelativeOrientation.tX.vX
                                  + *((float *)&igi2_frame.tNewPos.vZ + 1) * ptModelObj->tRelativeOrientation.tZ.vX
                                  + *(float *)&igi2_frame.tNewPos.vZ * ptModelObj->tRelativeOrientation.tY.vX;
    igi2_frame.Real32x9_Multiply_tTemp.tY.vY = *((float *)&igi2_frame.tNewPos.vY + 1) * ptModelObj->tRelativeOrientation.tX.vY
                                  + *((float *)&igi2_frame.tNewPos.vZ + 1) * ptModelObj->tRelativeOrientation.tZ.vY
                                  + *(float *)&igi2_frame.tNewPos.vZ * ptModelObj->tRelativeOrientation.tY.vY;
    igi2_frame.Real32x9_Multiply_tTemp.tY.vZ = *((float *)&igi2_frame.tNewPos.vY + 1) * ptModelObj->tRelativeOrientation.tX.vZ
                                  + *((float *)&igi2_frame.tNewPos.vZ + 1) * ptModelObj->tRelativeOrientation.tZ.vZ
                                  + *(float *)&igi2_frame.tNewPos.vZ * ptModelObj->tRelativeOrientation.tY.vZ;
    igi2_frame.Real32x9_Multiply_tTemp.tZ.vX = igi2_frame.v31 * ptModelObj->tRelativeOrientation.tZ.vX
                                  + igi2_frame.v30 * ptModelObj->tRelativeOrientation.tY.vX
                                  + igi2_frame.v29 * ptModelObj->tRelativeOrientation.tX.vX;
    igi2_frame.Real32x9_Multiply_tTemp.tZ.vY = igi2_frame.v29 * ptModelObj->tRelativeOrientation.tX.vY
                                  + igi2_frame.v31 * ptModelObj->tRelativeOrientation.tZ.vY
                                  + igi2_frame.v30 * ptModelObj->tRelativeOrientation.tY.vY;
    v17 = ptModelObj->tRelativeOrientation.nOps + nOps + v16 + 1 + 1;
    v18 = igi2_frame.v29 * ptModelObj->tRelativeOrientation.tX.vZ + igi2_frame.v31 * ptModelObj->tRelativeOrientation.tZ.vZ;
    v19 = igi2_frame.v30 * ptModelObj->tRelativeOrientation.tY.vZ;
  }
  else
  {
    v20 = ptModelObj->tAttachContext.ptParentOrientation;
    *(float *)&igi2_frame.tNewPos.vX = v20->tX.vY * ptModelObj->tRelativePos.vY
                          + ptModelObj->tRelativePos.vX * v20->tX.vX
                          + v20->tX.vZ * ptModelObj->tRelativePos.vZ;
    v21 = ptModelObj->tRelativePos.vX;
    igi2_frame.tRelativePos.vX = *(float *)&igi2_frame.tNewPos.vX;
    *((float *)&igi2_frame.tNewPos.vX + 1) = v21 * v20->tY.vX
                                + ptModelObj->tRelativePos.vZ * v20->tY.vZ
                                + v20->tY.vY * ptModelObj->tRelativePos.vY;
    v22 = v20->tZ.vY;
    igi2_frame.tRelativePos.vY = *((float *)&igi2_frame.tNewPos.vX + 1);
    *(float *)&igi2_frame.tNewPos.vY = v22 * ptModelObj->tRelativePos.vY
                          + v20->tZ.vX * ptModelObj->tRelativePos.vX
                          + v20->tZ.vZ * ptModelObj->tRelativePos.vZ;
    v23 = v20->tX.vZ;
    igi2_frame.tRelativePos.vZ = *(float *)&igi2_frame.tNewPos.vY;
    igi2_frame.Real32x9_Multiply_tTemp.tX.vX = v23 * ptModelObj->tRelativeOrientation.tZ.vX
                                  + v20->tX.vY * ptModelObj->tRelativeOrientation.tY.vX
                                  + ptModelObj->tRelativeOrientation.tX.vX * v20->tX.vX;
    igi2_frame.Real32x9_Multiply_tTemp.tX.vY = v20->tX.vX * ptModelObj->tRelativeOrientation.tX.vY
                                  + v20->tX.vZ * ptModelObj->tRelativeOrientation.tZ.vY
                                  + v20->tX.vY * ptModelObj->tRelativeOrientation.tY.vY;
    igi2_frame.Real32x9_Multiply_tTemp.tX.vZ = v20->tX.vZ * ptModelObj->tRelativeOrientation.tZ.vZ
                                  + v20->tX.vY * ptModelObj->tRelativeOrientation.tY.vZ
                                  + v20->tX.vX * ptModelObj->tRelativeOrientation.tX.vZ;
    igi2_frame.Real32x9_Multiply_tTemp.tY.vX = ptModelObj->tRelativeOrientation.tZ.vX * v20->tY.vZ
                                  + ptModelObj->tRelativeOrientation.tY.vX * v20->tY.vY
                                  + ptModelObj->tRelativeOrientation.tX.vX * v20->tY.vX;
    v24 = ptModelObj->tRelativeOrientation.nOps;
    igi2_frame.Real32x9_Multiply_tTemp.tY.vY = ptModelObj->tRelativeOrientation.tZ.vY * v20->tY.vZ
                                  + ptModelObj->tRelativeOrientation.tY.vY * v20->tY.vY
                                  + ptModelObj->tRelativeOrientation.tX.vY * v20->tY.vX;
    igi2_frame.Real32x9_Multiply_tTemp.tY.vZ = v20->tY.vX * ptModelObj->tRelativeOrientation.tX.vZ
                                  + v20->tY.vZ * ptModelObj->tRelativeOrientation.tZ.vZ
                                  + v20->tY.vY * ptModelObj->tRelativeOrientation.tY.vZ;
    igi2_frame.Real32x9_Multiply_tTemp.tZ.vX = v20->tZ.vZ * ptModelObj->tRelativeOrientation.tZ.vX
                                  + v20->tZ.vY * ptModelObj->tRelativeOrientation.tY.vX
                                  + v20->tZ.vX * ptModelObj->tRelativeOrientation.tX.vX;
    igi2_frame.Real32x9_Multiply_tTemp.tZ.vY = v20->tZ.vX * ptModelObj->tRelativeOrientation.tX.vY
                                  + v20->tZ.vZ * ptModelObj->tRelativeOrientation.tZ.vY
                                  + v20->tZ.vY * ptModelObj->tRelativeOrientation.tY.vY;
    v18 = v20->tZ.vZ * ptModelObj->tRelativeOrientation.tZ.vZ + v20->tZ.vY * ptModelObj->tRelativeOrientation.tY.vZ;
    v19 = v20->tZ.vX * ptModelObj->tRelativeOrientation.tX.vZ;
    v17 = v20->nOps + v24 + 1;
  }
  vRealRadius = ptModelObj->tDynCubeObj.tQObj.vRealRadius;
  igi2_frame.Real32x9_Multiply_tTemp.nOps = v17;
  igi2_frame.Real32x9_Multiply_tTemp.tZ.vZ = v18 + v19;
  qmemcpy(&igi2_frame.tNewOrientation, &igi2_frame.Real32x9_Multiply_tTemp, sizeof(igi2_frame.tNewOrientation));
  ptParentPos = ptModelObj->tAttachContext.ptParentPos;
  igi2_frame.tNewPos.vX = igi2_frame.tRelativePos.vX + ptParentPos->vX;
  igi2_frame.tNewPos.vY = igi2_frame.tRelativePos.vY + ptParentPos->vY;
  v27 = igi2_frame.tRelativePos.vZ + ptParentPos->vZ;
  qmemcpy(&ptModelObj->tOrientation, &igi2_frame.tNewOrientation, sizeof(ptModelObj->tOrientation));
  igi2_frame.tNewPos.vZ = v27;
  World_MoveDynCubeObjRadius(ptModelObj->ptWorld, &ptModelObj->tDynCubeObj, &igi2_frame.tNewPos, vRealRadius);
}

// source: e/3/modelobj.c:428  [anchor-callee]
struct QTask_s *__cdecl ModelObj_CreateAttachObject(
        struct ModelObj_s *ptModelObj,
        struct QTask_s *ptParent,
        struct QTask_s *ptCreator,
        struct Mesh3D_AttachObject_t *ptAttachObject,
        enum bool isDisableCollision,
        enum bool isRegister)
{
  #pragma pack(push, 1)
  union
  {
    struct { float tTemp_; };
    struct { char igi2_o1[4]; float tTemp__4; };
    struct { char igi2_o2[8]; float tTemp__8; };
    struct { char igi2_o3[12]; struct MagicObjType_s tMagicObjType; };
    struct { char igi2_o4[52]; struct MagicObjCreateContext_s tMagicObjCreateContext; };
    struct { char igi2_o5[212]; struct SetMagicObjParametersContext_s tSetMagicObjParametersContext; };
    char igi2_extent[356];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v6; // ecx
  float vY; // edx
  float v8; // ecx
  float vX; // edx
  float v10; // ecx
  float v11; // edx
  double v12; // st7
  double v13; // st6
  float vZ; // edx
  void *nOps; // ecx
  float v16; // edx
  double v17; // st7
  double v18; // st6
  double v19; // st7
  double v20; // st6
  struct MagicObjType_s *MagicObjType; // esi
  struct LODVirModel_s *LODVirModelExistsFn; // eax
  struct LODVirModel_s *v23; // edi
  struct Mesh3D_Mesh_t *ptMesh; // eax
  void *pxData; // edx
  struct World_s *ptWorld; // eax
  int nBone; // edx
  enum DynCubeRenderGroup_e iRenderGroup; // eax
  enum TransContext_Layer_e eLayer; // ecx
  struct QTask_s *v31; // eax
  void *v32; // edx
  struct QTask_s *v33; // edi
  void (__cdecl *pfHandler)(struct QTask_s *, struct SetMagicObjParametersContext_s *); // eax

  v6 = 0;
  if ( ModelObj_nDisabledAttachObjects <= 0 )
  {
LABEL_4:
    igi2_frame.tMagicObjCreateContext.tRelativePos.vX = ptAttachObject->tPos.vX;
    vY = ptAttachObject->tPos.vY;
    igi2_frame.tMagicObjCreateContext.tRelativePos.vZ = ptAttachObject->tPos.vZ;
    *(float *)&igi2_frame.tMagicObjType.zName[4] = ptAttachObject->tMatrix.tY.vX;
    v8 = ptAttachObject->tMatrix.tX.vY;
    igi2_frame.tMagicObjCreateContext.tRelativePos.vY = vY;
    *(float *)igi2_frame.tMagicObjType.zName = ptAttachObject->tMatrix.tX.vX;
    vX = ptAttachObject->tMatrix.tZ.vX;
    *(float *)&igi2_frame.tMagicObjType.zName[12] = v8;
    v10 = ptAttachObject->tMatrix.tZ.vY;
    *(float *)&igi2_frame.tMagicObjType.zName[8] = vX;
    v11 = ptAttachObject->tMatrix.tY.vY;
    *(float *)&igi2_frame.tMagicObjType.zModel[4] = v10;
    v12 = v10 * *(float *)&igi2_frame.tMagicObjType.zName[4];
    *(float *)igi2_frame.tMagicObjType.zModel = v11;
    v13 = v11 * *(float *)&igi2_frame.tMagicObjType.zName[8];
    vZ = ptAttachObject->tMatrix.tX.vZ;
    *(float *)&igi2_frame.tMagicObjType.zModel[12] = ptAttachObject->tMatrix.tY.vZ;
    nOps = (void *)ptAttachObject->tMatrix.nOps;
    *(float *)&igi2_frame.tMagicObjType.zModel[8] = vZ;
    v16 = ptAttachObject->tMatrix.tZ.vZ;
    igi2_frame.tMagicObjType.pxData = nOps;
    igi2_frame.tTemp_ = v12 - v13;
    *(float *)&igi2_frame.tMagicObjType.eQTaskType = v16;
    qmemcpy(
      &igi2_frame.tMagicObjCreateContext.tRelativeOrientation,
      &igi2_frame.tMagicObjType,
      sizeof(igi2_frame.tMagicObjCreateContext.tRelativeOrientation));
    igi2_frame.tMagicObjCreateContext.tRelativeOrientation.tZ.vX = igi2_frame.tTemp_;
    igi2_frame.tTemp__4 = -(*(float *)&igi2_frame.tMagicObjType.zModel[4] * *(float *)igi2_frame.tMagicObjType.zName
               - *(float *)&igi2_frame.tMagicObjType.zName[12] * *(float *)&igi2_frame.tMagicObjType.zName[8]);
    igi2_frame.tMagicObjCreateContext.tRelativeOrientation.tZ.vY = igi2_frame.tTemp__4;
    igi2_frame.tTemp__8 = *(float *)igi2_frame.tMagicObjType.zModel * *(float *)igi2_frame.tMagicObjType.zName
             - *(float *)&igi2_frame.tMagicObjType.zName[12] * *(float *)&igi2_frame.tMagicObjType.zName[4];
    v17 = ptAttachObject->tPos.vX;
    v18 = ptAttachObject->tPos.vY;
    igi2_frame.tMagicObjCreateContext.tRelativeOrientation.tZ.vZ = igi2_frame.tTemp__8;
    igi2_frame.tMagicObjCreateContext.tPos.vY = v18;
    igi2_frame.tMagicObjCreateContext.tPos.vZ = ptAttachObject->tPos.vZ;
    *(double *)igi2_frame.tMagicObjType.zName = ptModelObj->tOrientation.tX.vX * v17
                                   + ptModelObj->tOrientation.tX.vY * v18
                                   + ptModelObj->tOrientation.tX.vZ * igi2_frame.tMagicObjCreateContext.tPos.vZ;
    *(double *)&igi2_frame.tMagicObjType.zName[8] = ptModelObj->tOrientation.tY.vY * v18
                                       + ptModelObj->tOrientation.tY.vZ * igi2_frame.tMagicObjCreateContext.tPos.vZ
                                       + ptModelObj->tOrientation.tY.vX * v17;
    *(double *)igi2_frame.tMagicObjType.zModel = ptModelObj->tOrientation.tZ.vY * v18
                                    + ptModelObj->tOrientation.tZ.vZ * igi2_frame.tMagicObjCreateContext.tPos.vZ
                                    + ptModelObj->tOrientation.tZ.vX * v17;
    qmemcpy(&igi2_frame.tMagicObjCreateContext.tPos, &igi2_frame.tMagicObjType, sizeof(igi2_frame.tMagicObjCreateContext.tPos));
    igi2_frame.tMagicObjCreateContext.tPos.vX = *(double *)igi2_frame.tMagicObjType.zName + ptModelObj->tDynCubeObj.tQObj.tPos.vX;
    igi2_frame.tMagicObjCreateContext.tPos.vY = igi2_frame.tMagicObjCreateContext.tPos.vY + ptModelObj->tDynCubeObj.tQObj.tPos.vY;
    igi2_frame.tMagicObjCreateContext.tPos.vZ = igi2_frame.tMagicObjCreateContext.tPos.vZ + ptModelObj->tDynCubeObj.tQObj.tPos.vZ;
    *(float *)igi2_frame.tMagicObjType.zName = igi2_frame.tMagicObjCreateContext.tRelativeOrientation.tX.vX * ptModelObj->tOrientation.tX.vX
                                  + igi2_frame.tMagicObjCreateContext.tRelativeOrientation.tY.vX * ptModelObj->tOrientation.tX.vY
                                  + igi2_frame.tTemp_ * ptModelObj->tOrientation.tX.vZ;
    *(float *)&igi2_frame.tMagicObjType.zName[4] = igi2_frame.tMagicObjCreateContext.tRelativeOrientation.tX.vY
                                      * ptModelObj->tOrientation.tX.vX
                                      + igi2_frame.tMagicObjCreateContext.tRelativeOrientation.tY.vY
                                      * ptModelObj->tOrientation.tX.vY
                                      + igi2_frame.tTemp__4 * ptModelObj->tOrientation.tX.vZ;
    *(float *)&igi2_frame.tMagicObjType.zName[8] = igi2_frame.tMagicObjCreateContext.tRelativeOrientation.tX.vZ
                                      * ptModelObj->tOrientation.tX.vX
                                      + igi2_frame.tMagicObjCreateContext.tRelativeOrientation.tY.vZ
                                      * ptModelObj->tOrientation.tX.vY
                                      + igi2_frame.tTemp__8 * ptModelObj->tOrientation.tX.vZ;
    *(float *)&igi2_frame.tMagicObjType.zName[12] = igi2_frame.tMagicObjCreateContext.tRelativeOrientation.tY.vX
                                       * ptModelObj->tOrientation.tY.vY
                                       + igi2_frame.tTemp_ * ptModelObj->tOrientation.tY.vZ
                                       + igi2_frame.tMagicObjCreateContext.tRelativeOrientation.tX.vX
                                       * ptModelObj->tOrientation.tY.vX;
    *(float *)igi2_frame.tMagicObjType.zModel = igi2_frame.tMagicObjCreateContext.tRelativeOrientation.tY.vY * ptModelObj->tOrientation.tY.vY
                                   + igi2_frame.tTemp__4 * ptModelObj->tOrientation.tY.vZ
                                   + igi2_frame.tMagicObjCreateContext.tRelativeOrientation.tX.vY * ptModelObj->tOrientation.tY.vX;
    v19 = igi2_frame.tMagicObjCreateContext.tRelativeOrientation.tY.vZ * ptModelObj->tOrientation.tY.vY
        + igi2_frame.tTemp__8 * ptModelObj->tOrientation.tY.vZ;
    v20 = igi2_frame.tMagicObjCreateContext.tRelativeOrientation.tX.vZ * ptModelObj->tOrientation.tY.vX;
    igi2_frame.tMagicObjType.pxData = (void *)(ptModelObj->tOrientation.nOps + igi2_frame.tMagicObjCreateContext.tRelativeOrientation.nOps + 1);
    *(float *)&igi2_frame.tMagicObjType.zModel[4] = v19 + v20;
    *(float *)&igi2_frame.tMagicObjType.zModel[8] = igi2_frame.tMagicObjCreateContext.tRelativeOrientation.tY.vX
                                       * ptModelObj->tOrientation.tZ.vY
                                       + igi2_frame.tTemp_ * ptModelObj->tOrientation.tZ.vZ
                                       + igi2_frame.tMagicObjCreateContext.tRelativeOrientation.tX.vX
                                       * ptModelObj->tOrientation.tZ.vX;
    *(float *)&igi2_frame.tMagicObjType.zModel[12] = igi2_frame.tMagicObjCreateContext.tRelativeOrientation.tY.vY
                                        * ptModelObj->tOrientation.tZ.vY
                                        + igi2_frame.tTemp__4 * ptModelObj->tOrientation.tZ.vZ
                                        + igi2_frame.tMagicObjCreateContext.tRelativeOrientation.tX.vY
                                        * ptModelObj->tOrientation.tZ.vX;
    *(float *)&igi2_frame.tMagicObjType.eQTaskType = igi2_frame.tMagicObjCreateContext.tRelativeOrientation.tY.vZ
                                        * ptModelObj->tOrientation.tZ.vY
                                        + igi2_frame.tTemp__8 * ptModelObj->tOrientation.tZ.vZ
                                        + igi2_frame.tMagicObjCreateContext.tRelativeOrientation.tX.vZ
                                        * ptModelObj->tOrientation.tZ.vX;
    qmemcpy(&igi2_frame.tMagicObjCreateContext.tOrientation, &igi2_frame.tMagicObjType, sizeof(igi2_frame.tMagicObjCreateContext.tOrientation));
    MagicObjType = MagicObj_GetMagicObjType(ptAttachObject->zName);
    if ( !MagicObjType )
    {
      LODVirModelExistsFn = MTP_GetLODVirModelExistsFn(ptAttachObject->zName);
      v23 = LODVirModelExistsFn ? LODVirModelExistsFn : nullptr;
      igi2_frame.tMagicObjType.eQTaskType = RigidMagicObj_eQTaskType;
      igi2_frame.tMagicObjType.pxData = nullptr;
      strcpy(igi2_frame.tMagicObjType.zModel, ptAttachObject->zName);
      strcpy(igi2_frame.tMagicObjType.zName, ptAttachObject->zName);
      MagicObjType = &igi2_frame.tMagicObjType;
      if ( v23 )
      {
        ptMesh = v23->aptVirModel[0]->ptModel->ptMesh;
        if ( ptMesh->ptPortal )
        {
          if ( ptCreator
            && QTask_IsQTaskTypeDerived(ptModelObj->tDynCubeObj.tQObj.tQTask.eQTaskType, SectorObject_eQTaskType) )
          {
            igi2_frame.tMagicObjType.eQTaskType = Sector_eQTaskType;
          }
        }
        else if ( ptMesh->nBones )
        {
          igi2_frame.tMagicObjType.eQTaskType = LOWORD(CubeOcclusion_vScreenSizeX);
        }
      }
    }
    pxData = MagicObjType->pxData;
    igi2_frame.tMagicObjCreateContext.zModel = MagicObjType->zModel;
    ptWorld = ptModelObj->ptWorld;
    igi2_frame.tMagicObjCreateContext.pxData = pxData;
    nBone = ptAttachObject->nBone;
    igi2_frame.tMagicObjCreateContext.ptWorld = ptWorld;
    iRenderGroup = ptModelObj->tDynCubeObj.iRenderGroup;
    igi2_frame.tMagicObjCreateContext.ptCreator = ptCreator;
    eLayer = ptModelObj->eLayer;
    igi2_frame.tMagicObjCreateContext.iBone = nBone;
    igi2_frame.tMagicObjCreateContext.iRenderGroup = iRenderGroup;
    igi2_frame.tMagicObjCreateContext.eLayer = eLayer;
    igi2_frame.tMagicObjCreateContext.iID = -1;
    igi2_frame.tMagicObjCreateContext.isDisableCollision = isDisableCollision;
    igi2_frame.tMagicObjCreateContext.isRegister = isRegister;
    v31 = QTask_NewFn(ptParent, MagicObjType->eQTaskType, &igi2_frame.tMagicObjCreateContext);
    v32 = MagicObjType->pxData;
    v33 = v31;
    igi2_frame.tSetMagicObjParametersContext.zModel = MagicObjType->zModel;
    igi2_frame.tSetMagicObjParametersContext.ptWorld = ptModelObj->ptWorld;
    igi2_frame.tSetMagicObjParametersContext.pxData = v32;
    igi2_frame.tSetMagicObjParametersContext.ptCreator = ptCreator;
    pfHandler = (void (__cdecl *)(struct QTask_s *, struct SetMagicObjParametersContext_s *))QTask_aatQTaskFinalEvent[MagicObj_eSetMagicObjParametersEvent][v31->eQTaskType].pfHandler;
    if ( pfHandler )
      pfHandler(v33, &igi2_frame.tSetMagicObjParametersContext);
    if ( QTask_IsQTaskTypeDerived(MagicObjType->eQTaskType, ModelObj_eQTaskType) )
    {
      v33[5].tQTaskRefList.ptHead = (struct QReference_s *)ptAttachObject->nBone;
      v33[5].tQTaskChildren.ptTail = (struct QTask_s *)-1;
    }
    return v33;
  }
  else
  {
    while ( strcmp(ModelObj_apzDisabledAttachObjects[v6], ptAttachObject->zName) )
    {
      if ( ++v6 >= ModelObj_nDisabledAttachObjects )
        goto LABEL_4;
    }
    return nullptr;
  }
}

// source: e/3/modelobj.c:586  [anchor-callee]
struct ModelObj_s *__cdecl ModelObj_CreateAttachObjects(
        struct ModelObj_s *ptModelObj,
        struct QTask_s *ptParent,
        struct QTask_s *ptCreator,
        enum bool isDisableCollision,
        enum bool isRegister)
{
  struct ModelObj_s *result; // eax
  int ptPrev_high; // edi
  int v8; // esi

  result = (struct ModelObj_s *)ptModelObj->ptLODVirModel;
  if ( result )
  {
    result = (struct ModelObj_s *)result->tDynCubeObj.tQObj.tQTask.ptNext;
    ptPrev_high = SHIWORD(result->tDynCubeObj.tQObj.tQTask.tQTaskChildren.ptMiddle->tQTaskChildren.ptMiddle[3].ptPrev);
    if ( ptPrev_high > 0 )
    {
      v8 = 0;
      do
      {
        result = (struct ModelObj_s *)ModelObj_CreateAttachObject(
                                        ptModelObj,
                                        ptParent,
                                        ptCreator,
                                        &ptModelObj->ptLODVirModel->aptVirModel[0]->ptModel->ptMesh->ptAttachObject[v8++],
                                        isDisableCollision,
                                        isRegister);
        --ptPrev_high;
      }
      while ( ptPrev_high );
    }
  }
  return result;
}

// source: e/3/modelobj.c:623  [anchor-callee]
void __cdecl ModelObj_AttachToParent(
        struct ModelObj_s *ptModelObj,
        struct MagicObjCreateContext_s *ptMagicObjCreateContext)
{
  struct AttachContext_t *p_tAttachContext; // eax

  p_tAttachContext = &ptModelObj->tAttachContext;
  if ( ptMagicObjCreateContext )
  {
    p_tAttachContext->iID = ptMagicObjCreateContext->iID;
    ptModelObj->tAttachContext.iBone = ptMagicObjCreateContext->iBone;
    ptModelObj->tRelativePos = ptMagicObjCreateContext->tRelativePos;
    qmemcpy(
      &ptModelObj->tRelativeOrientation,
      &ptMagicObjCreateContext->tRelativeOrientation,
      sizeof(ptModelObj->tRelativeOrientation));
  }
  else
  {
    p_tAttachContext->iID = -1;
    ptModelObj->tAttachContext.iBone = 0;
  }
  QTask_TriggerQTaskEventParent(&ptModelObj->tDynCubeObj.tQObj.tQTask, Attach_eAttachEvent, &ptModelObj->tAttachContext);
  if ( !ptMagicObjCreateContext )
    ModelObj_CalcRelativePosAndOrientation(ptModelObj);
}

// source: e/3/modelobj.c:654  [anchor-callee]
void __cdecl ModelObj_SetLODVirModel(
        struct ModelObj_s *ptModelObj,
        struct LODVirModel_s *ptLODVirModel,
        enum bool isCreateAttachObjectsAsChildren)
{
  struct QTask_s *ptMagicObjContainer; // eax
  enum bool v5; // ebx
  struct VirModel_s *v6; // edi
  unsigned __int16 eQTaskType; // dx
  enum bool v8; // ecx
  struct ModelObj_s *v9; // eax

  if ( ptModelObj->ptLODVirModel != ptLODVirModel )
  {
    ptMagicObjContainer = ptModelObj->ptMagicObjContainer;
    v5 = ptModelObj->tDynCubeObj.ptDynCubeObjTreeItem != nullptr;
    ptModelObj->ptLODVirModel = ptLODVirModel;
    if ( ptMagicObjContainer )
    {
      QTask_Delete(ptMagicObjContainer);
      ptModelObj->ptMagicObjContainer = nullptr;
    }
    if ( ptLODVirModel )
    {
      v6 = ptLODVirModel->aptVirModel[0];
      if ( v6 )
      {
        if ( v6->ptModel->ptMesh->nAttachObject > 0 )
        {
          if ( isCreateAttachObjectsAsChildren == false )
            ptModelObj->ptMagicObjContainer = MagicObjContainer_New(nullptr, &ptModelObj->tDynCubeObj.tQObj.tQTask);
          eQTaskType = ptModelObj->tDynCubeObj.tQObj.tQTask.eQTaskType;
          v8 = QTask_IsQTaskTypeDerived(eQTaskType, BoneDynCubeObj_eQTaskType)
            || QTask_IsQTaskTypeDerived(eQTaskType, RigidDynCubeObj_eQTaskType)
            && ptModelObj[1].tDynCubeObj.tQObj.tQTask.ptNext == (struct QTask_s *)-1;
          v9 = (struct ModelObj_s *)ptModelObj->ptMagicObjContainer;
          if ( !v9 )
            v9 = ptModelObj;
          ModelObj_CreateAttachObjects(
            ptModelObj,
            &v9->tDynCubeObj.tQObj.tQTask,
            &ptModelObj->tDynCubeObj.tQObj.tQTask,
            v8,
            v5);
        }
      }
    }
  }
}

// source: e/3/modelobj.c:716  [anchor-callee]
void __cdecl ModelObj_UpdateAttachments(struct ModelObj_s *ptModelObj)
{
  struct QTask_s *ptMagicObjContainer; // eax
  int ptHead; // edx
  int v3; // eax
  struct QTask_s *v4; // ecx
  int v5; // esi
  void (__cdecl *pfHandler)(int); // ecx
  int v7; // eax
  struct QTask_s *v8; // ecx
  struct QTask_s *v9; // edx
  int v10; // esi
  void (__cdecl *v11)(struct QTask_s *); // edx
  int v12; // eax

  ptMagicObjContainer = ptModelObj->ptMagicObjContainer;
  if ( ptMagicObjContainer && (ptHead = (int)ptMagicObjContainer->tQTaskChildren.ptHead, *(_DWORD *)ptHead) && ptHead )
  {
    v3 = QTask_nProtectedQTaskStackOffset;
    do
    {
      if ( *(_DWORD *)ptHead )
        v4 = **(_DWORD **)ptHead != 0 ? *(struct QTask_s **)ptHead : nullptr;
      else
        v4 = nullptr;
      v5 = Attach_eUpdateAttachmentEvent;
      QTask_atProtectedQTaskStack[v3].ptQTask = v4;
      pfHandler = (void (__cdecl *)(int))QTask_aatQTaskFinalEvent[v5][*(unsigned __int16 *)(ptHead + 36)].pfHandler;
      v7 = v3 + 1;
      QTask_nProtectedQTaskStackOffset = v7;
      if ( pfHandler )
      {
        pfHandler(ptHead);
        v7 = QTask_nProtectedQTaskStackOffset;
      }
      ptHead = dword_849C7DC[v7];
      v3 = v7 - 1;
      QTask_nProtectedQTaskStackOffset = v3;
    }
    while ( ptHead );
  }
  else
  {
    v3 = QTask_nProtectedQTaskStackOffset;
  }
  v8 = ptModelObj->tDynCubeObj.tQObj.tQTask.tQTaskChildren.ptHead;
  if ( v8->ptNext && v8 )
  {
    do
    {
      if ( v8->ptNext )
        v9 = v8->ptNext->ptNext != nullptr ? v8->ptNext : nullptr;
      else
        v9 = nullptr;
      v10 = Attach_eUpdateAttachmentEvent;
      QTask_atProtectedQTaskStack[v3].ptQTask = v9;
      v11 = (void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[v10][v8->eQTaskType].pfHandler;
      v12 = v3 + 1;
      QTask_nProtectedQTaskStackOffset = v12;
      if ( v11 )
      {
        v11(v8);
        v12 = QTask_nProtectedQTaskStackOffset;
      }
      v8 = (struct QTask_s *)dword_849C7DC[v12];
      v3 = v12 - 1;
      QTask_nProtectedQTaskStackOffset = v3;
    }
    while ( v8 );
  }
}

// source: e/3/modelobj.c:743  [size]
enum bool __cdecl ModelObj_Exclude(struct ModelObj_s *ptModelObj, enum bool *pisTotallyInside)
{
  #pragma pack(push, 1)
  union
  {
    struct { float vRadius; };
    struct { char igi2_o1[4]; struct real32x3_t tPos; };
    struct { char igi2_o2[16]; struct real32x3_t Real32x3_Rotate_tTemp; };
    struct { char igi2_o3[28]; struct real32x3_t tRotated; };
    char igi2_extent[40];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct LODVirModel_s *ptLODVirModel; // edx
  float *p_vVersion; // eax
  double v4; // st7
  double v5; // st6
  double vY; // st7
  double vX; // st7

  ptLODVirModel = ptModelObj->ptLODVirModel;
  igi2_frame.tPos.vX = ptModelObj->tDynCubeObj.tQObj.tPos.vX - TransContext_tActiveTransContext.tPos.vX;
  igi2_frame.tPos.vY = ptModelObj->tDynCubeObj.tQObj.tPos.vY - TransContext_tActiveTransContext.tPos.vY;
  igi2_frame.tPos.vZ = ptModelObj->tDynCubeObj.tQObj.tPos.vZ - TransContext_tActiveTransContext.tPos.vZ;
  if ( ptLODVirModel )
  {
    p_vVersion = &ptLODVirModel->aptVirModel[0]->ptModel->ptMesh->vVersion;
    igi2_frame.Real32x3_Rotate_tTemp.vX = ptModelObj->tOrientation.tX.vY * p_vVersion[13]
                             + ptModelObj->tOrientation.tX.vX * p_vVersion[12]
                             + ptModelObj->tOrientation.tX.vZ * p_vVersion[14];
    igi2_frame.Real32x3_Rotate_tTemp.vY = ptModelObj->tOrientation.tY.vY * p_vVersion[13]
                             + ptModelObj->tOrientation.tY.vX * p_vVersion[12]
                             + ptModelObj->tOrientation.tY.vZ * p_vVersion[14];
    igi2_frame.Real32x3_Rotate_tTemp.vZ = ptModelObj->tOrientation.tZ.vY * p_vVersion[13]
                             + ptModelObj->tOrientation.tZ.vX * p_vVersion[12]
                             + ptModelObj->tOrientation.tZ.vZ * p_vVersion[14];
    igi2_frame.tRotated = igi2_frame.Real32x3_Rotate_tTemp;
    v4 = igi2_frame.Real32x3_Rotate_tTemp.vX * ptModelObj->tScale.vX;
    v5 = igi2_frame.Real32x3_Rotate_tTemp.vY * ptModelObj->tScale.vY;
    igi2_frame.tRotated.vZ = igi2_frame.Real32x3_Rotate_tTemp.vZ * ptModelObj->tScale.vZ;
    igi2_frame.tPos.vX = v4 + igi2_frame.tPos.vX;
    igi2_frame.tPos.vY = v5 + igi2_frame.tPos.vY;
    igi2_frame.tPos.vZ = igi2_frame.tRotated.vZ + igi2_frame.tPos.vZ;
    if ( ptModelObj->tScale.vX <= (double)ptModelObj->tScale.vY )
      vY = ptModelObj->tScale.vY;
    else
      vY = ptModelObj->tScale.vX;
    if ( vY <= ptModelObj->tScale.vZ )
    {
      igi2_frame.vRadius = ptModelObj->tScale.vZ * ptLODVirModel->aptVirModel[0]->ptModel->ptMesh->tRenderMeshSphere.vRadius;
    }
    else
    {
      if ( ptModelObj->tScale.vX <= (double)ptModelObj->tScale.vY )
        vX = ptModelObj->tScale.vY;
      else
        vX = ptModelObj->tScale.vX;
      igi2_frame.vRadius = vX * ptLODVirModel->aptVirModel[0]->ptModel->ptMesh->tRenderMeshSphere.vRadius;
    }
  }
  else
  {
    igi2_frame.vRadius = 1.0;
  }
  igi2_frame.tRotated.vX = TransContext_tActiveTransContext.tMatrix.tX.vZ * igi2_frame.tPos.vZ
              + TransContext_tActiveTransContext.tMatrix.tX.vY * igi2_frame.tPos.vY
              + TransContext_tActiveTransContext.tMatrix.tX.vX * igi2_frame.tPos.vX;
  igi2_frame.tRotated.vY = TransContext_tActiveTransContext.tMatrix.tY.vZ * igi2_frame.tPos.vZ
              + TransContext_tActiveTransContext.tMatrix.tY.vY * igi2_frame.tPos.vY
              + TransContext_tActiveTransContext.tMatrix.tY.vX * igi2_frame.tPos.vX;
  igi2_frame.tRotated.vZ = TransContext_tActiveTransContext.tMatrix.tZ.vZ * igi2_frame.tPos.vZ
              + TransContext_tActiveTransContext.tMatrix.tZ.vY * igi2_frame.tPos.vY
              + TransContext_tActiveTransContext.tMatrix.tZ.vX * igi2_frame.tPos.vX;
  igi2_frame.tPos = igi2_frame.tRotated;
  return Mesh3D_ExcludeObject(&igi2_frame.tPos, igi2_frame.vRadius, pisTotallyInside);
}

// source: e/3/modelobj.c:784  [size]
float __cdecl ModelObj_CalcDistanceSquared(
        struct ModelObj_s *ptModelObj,
        struct LODVirModel_s **pptLODVirModel,
        struct real64x3_t *ptCameraPos)
{
  struct LODVirModel_s *ptLODVirModel; // ecx
  double v5; // st7
  double v6; // st6
  double v7; // st5
  float *p_vVersion; // eax
  double v9; // st6
  double v10; // st5
  double v11; // st3
  float Real32x3_RotateInverse_tTemp; // [esp+0h] [ebp-18h]
  float Real32x3_RotateInverse_tTemp_4; // [esp+4h] [ebp-14h]
  float Real32x3_RotateInverse_tTemp_8; // [esp+8h] [ebp-10h]

  ptLODVirModel = ptModelObj->ptLODVirModel;
  *pptLODVirModel = ptLODVirModel;
  if ( ptLODVirModel )
  {
    v5 = ptModelObj->tDynCubeObj.tQObj.tPos.vX - ptCameraPos->vX;
    v6 = ptModelObj->tDynCubeObj.tQObj.tPos.vY - ptCameraPos->vY;
    v7 = ptModelObj->tDynCubeObj.tQObj.tPos.vZ - ptCameraPos->vZ;
    Real32x3_RotateInverse_tTemp = v7 * ptModelObj->tOrientation.tZ.vX
                                 + v6 * ptModelObj->tOrientation.tY.vX
                                 + v5 * ptModelObj->tOrientation.tX.vX;
    Real32x3_RotateInverse_tTemp_4 = v7 * ptModelObj->tOrientation.tZ.vY
                                   + v6 * ptModelObj->tOrientation.tY.vY
                                   + v5 * ptModelObj->tOrientation.tX.vY;
    Real32x3_RotateInverse_tTemp_8 = v7 * ptModelObj->tOrientation.tZ.vZ
                                   + v6 * ptModelObj->tOrientation.tY.vZ
                                   + v5 * ptModelObj->tOrientation.tX.vZ;
    p_vVersion = &ptLODVirModel->aptVirModel[0]->ptModel->ptMesh->vVersion;
    v9 = Real32x3_RotateInverse_tTemp_4 + p_vVersion[13];
    v10 = Real32x3_RotateInverse_tTemp_8 + p_vVersion[14];
    v11 = Real32x3_RotateInverse_tTemp + p_vVersion[12];
    return v10 * v10 + v9 * v9 + v11 * v11;
  }
  else
  {
    return 0.0;
  }
}

// source: e/3/modelobj.c:821  [size]
float __cdecl ModelObj_CalcDistance(struct ModelObj_s *ptModelObj, struct real64x3_t *ptCameraPos)
{
  struct LODVirModel_s *ptLODVirModel; // [esp+4h] [ebp-4h] BYREF

  return sqrt(ModelObj_CalcDistanceSquared(ptModelObj, &ptLODVirModel, ptCameraPos));
}

// source: e/3/modelobj.c:837  [anchor-callee]
int __cdecl ModelObj_GetLOD(struct ModelObj_s *ptModelObj)
{
  #pragma pack(push, 1)
  union
  {
    struct { float vFOVX; };
    struct { float vFOVXa; };
    struct { float vFOVXb; };
    struct { char igi2_o3[4]; float vScale; };
    struct { char igi2_o4[8]; float vLODBiasSquared; };
    struct { char igi2_o5[12]; struct LODVirModel_s *ptLODVirModel; };
    struct { char igi2_o6[16]; float vRadius; };
    struct { char igi2_o7[20]; int vDistanceWithLODBiasSquared; };
    char igi2_extent[24];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct Mesh3D_Mesh_t *ptMesh; // eax
  double vX; // st7
  bool v4; // c0
  bool v5; // c3
  double vY; // st7
  float vZ; // eax
  float v8; // edi
  double v9; // st7
  int v10; // edi
  int v11; // ecx
  float *avLODDistance; // esi
  double v13; // st7

  igi2_frame.ptLODVirModel = ptModelObj->ptLODVirModel;
  if ( !igi2_frame.ptLODVirModel )
    return 0;
  if ( TransContext_tActiveTransContext.vFOVX >= 1.0 )
    igi2_frame.vFOVX = 1.0;
  else
    igi2_frame.vFOVX = TransContext_tActiveTransContext.vFOVX;
  ptMesh = igi2_frame.ptLODVirModel->aptVirModel[0]->ptModel->ptMesh;
  if ( ptMesh->eRenderMeshType == MESH3D_RENDERMESHTYPE_DIRECT3D_BUILDING )
    igi2_frame.vLODBiasSquared = 1.0;
  else
    igi2_frame.vLODBiasSquared = ModelObj_vActualLODBiasSquared;
  vX = ptModelObj->tScale.vX;
  v4 = vX < ptModelObj->tScale.vY;
  v5 = vX == ptModelObj->tScale.vY;
  igi2_frame.vRadius = ptMesh->tRenderMeshSphere.vRadius;
  if ( v4 || v5 )
    vY = ptModelObj->tScale.vY;
  else
    vY = ptModelObj->tScale.vX;
  if ( vY <= ptModelObj->tScale.vZ )
  {
    vZ = ptModelObj->tScale.vZ;
  }
  else if ( ptModelObj->tScale.vX <= (double)ptModelObj->tScale.vY )
  {
    vZ = ptModelObj->tScale.vY;
  }
  else
  {
    vZ = ptModelObj->tScale.vX;
  }
  LODWORD(v8) = igi2_frame.ptLODVirModel->nLOD;
  igi2_frame.vScale = vZ;
  *(float *)&igi2_frame.vDistanceWithLODBiasSquared = v8;
  igi2_frame.vFOVXa = ModelObj_CalcDistanceSquared(ptModelObj, &igi2_frame.ptLODVirModel, &TransContext_tActiveTransContext.tPos)
         * igi2_frame.vFOVX
         * igi2_frame.vFOVX;
  if ( igi2_frame.ptLODVirModel->isLODDistanceSpecified )
  {
    v11 = 0;
    *(float *)&igi2_frame.vDistanceWithLODBiasSquared = igi2_frame.vFOVXa * igi2_frame.vLODBiasSquared;
    if ( (int)(LODWORD(v8) - 1) <= 0 )
    {
LABEL_28:
      v13 = igi2_frame.vScale * igi2_frame.ptLODVirModel->avLODDistance[4];
      if ( igi2_frame.vFOVXa >= v13 * v13 )
        return -1;
      else
        return LODWORD(v8) - 1;
    }
    else
    {
      avLODDistance = igi2_frame.ptLODVirModel->avLODDistance;
      while ( *(float *)&igi2_frame.vDistanceWithLODBiasSquared >= igi2_frame.vScale * *avLODDistance * (igi2_frame.vScale * *avLODDistance) )
      {
        ++v11;
        ++avLODDistance;
        if ( v11 >= (int)(LODWORD(v8) - 1) )
          goto LABEL_28;
      }
      return v11;
    }
  }
  else
  {
    v9 = igi2_frame.vScale * igi2_frame.vRadius * Mesh3D_vRigidObjCutoff;
    igi2_frame.vRadius = v9;
    if ( v9 * v9 >= igi2_frame.vFOVXa )
    {
      v10 = LODWORD(v8) - 1;
      igi2_frame.vFOVXb = igi2_frame.vFOVXa * igi2_frame.vLODBiasSquared;
      for ( *(float *)&igi2_frame.vDistanceWithLODBiasSquared = igi2_frame.vRadius / (double)igi2_frame.vDistanceWithLODBiasSquared; v10; --v10 )
      {
        v9 = v9 - *(float *)&igi2_frame.vDistanceWithLODBiasSquared;
        if ( v9 * v9 < igi2_frame.vFOVXb )
          break;
      }
      return v10;
    }
    else
    {
      return -1;
    }
  }
}

// source: e/3/modelobj.c:932  [size]
void __cdecl ModelObj_DisableAttachObject(char *pzName)
{
  int v1; // eax

  v1 = ModelObj_nDisabledAttachObjects;
  ModelObj_apzDisabledAttachObjects[ModelObj_nDisabledAttachObjects] = pzName;
  ModelObj_nDisabledAttachObjects = v1 + 1;
}

// source: e/3/modelobj.c:949  [size]
void __cdecl ModelObj_ClearDisabledAttachObjects()
{
  ModelObj_nDisabledAttachObjects = 0;
}

// source: e/3/modelobj.c:962  [size]
unsigned __int16 __cdecl ModelObj_GetQTaskType()
{
  return ModelObj_eQTaskType;
}

// source: e/3/modelobj.c:975  [size]
float __cdecl ModelObj_GetLODBias()
{
  return ModelObj_vLODBias;
}

// source: e/3/modelobj.c:988  [anchor-mhash]
void __cdecl ModelObj_SetLODBias(float vLODBias)
{
  ModelObj_vLODBias = vLODBias;
  ModelObj_vActualLODBiasSquared = (vLODBias * 4.0 + 1.0) * (vLODBias * 4.0 + 1.0);
}

// source: e/3/modelobj.c:1003  [anchor-strings]
void __cdecl ModelObj_Open()
{
  unsigned __int16 v0; // si

  v0 = QTask_NewQTaskType("ModelObj", 288, DynCubeObj_eQTaskType, 0, 0);
  ModelObj_eQTaskType = v0;
  QTask_LinkQTaskEventHandlerFn(v0, 4, ModelObj_ParentChangedHandler);
  QTask_LinkQTaskEventHandlerFn(v0, Attach_eAttachEvent, ModelObj_AttachHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, Attach_eUpdateAttachmentEvent, ModelObj_UpdateAttachmentHandler);
  QTask_LinkQTaskEventHandlerFn(v0, DynCubeObj_eDynCubeObjRegisterQTaskEvent, ModelObj_RegisterHandler);
  QTask_LinkQTaskEventHandlerFn(v0, DynCubeObj_eDynCubeObjRemoveQTaskEvent, ModelObj_RemoveHandler);
  QTask_LinkQTaskEventHandlerFn(v0, ShadowVolume_eGetShadowInfoEvent, ModelObj_GetShadowInfoHandler);
  ModelObj_UpdateAttachmentsProfileRegion = nullptr;
  ModelObj_MagicObjUpdateAttachmentsProfileRegion = nullptr;
}

// source: e/3/modelobj.c:1028  [size]
void __cdecl ModelObj_Close()
{
  QTask_DeleteQTaskType(ModelObj_eQTaskType);
}
