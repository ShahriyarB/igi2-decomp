/* e/3/rigidmagicobj.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: e/3/rigidmagicobj.c:36  [size]
void __cdecl RigidMagicObj_SetMagicObjParametersHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ;
}

// source: e/3/rigidmagicobj.c:53  [anchor-mhash]
void __cdecl RigidMagicObj_InterpolateHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { float vZZ; };
    struct { char igi2_o1[4]; float vXZ; };
    struct { char igi2_o2[4]; float vXZa; };
    struct { char igi2_o3[8]; float vYW; };
    struct { char igi2_o4[8]; float vYWa; };
    struct { char igi2_o5[12]; float vYZ; };
    struct { char igi2_o6[12]; float vYZa; };
    struct { char igi2_o7[16]; float vXW; };
    struct { char igi2_o8[16]; float vXWa; };
    struct { char igi2_o9[20]; float vYY; };
    struct { char igi2_o10[20]; float vYYa; };
    struct { char igi2_o11[24]; struct Quat32_t tQ; };
    char igi2_extent[44];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *ptNext; // ebp
  struct QTask_s *v3; // ebx
  double v4; // st7
  float *p_ptMiddle; // ebx
  float *p_ptPrev; // edi
  double v7; // st6
  double v8; // st6
  double v9; // st5
  double v10; // st5
  double v11; // st4
  double v12; // st5
  double v13; // st5
  double v14; // st4
  double v15; // st5
  double v16; // st5
  double v17; // st7
  double v18; // st7
  double v19; // st6
  double v20; // st5
  double v21; // st7
  float ptQTaska = *(float *)&ptQTask; // [esp+3Ch] [ebp+4h] ARGSLOT
  float ptQTaskb = *(float *)&ptQTask; // [esp+3Ch] [ebp+4h] ARGSLOT

  ptNext = ptQTask[6].ptNext;
  v3 = nullptr;
  if ( ptNext )
  {
    while ( (int)ptNext->ptPrev <= AnimController_nTime )
    {
      v3 = ptNext;
      ptNext = ptNext->tQTaskChildren.ptHead;
      if ( !ptNext )
      {
        v4 = *(float *)&v3->tQTaskRefList.ptMiddle;
        p_ptMiddle = (float *)&v3->tQTaskChildren.ptMiddle;
        p_ptPrev = (float *)&ptQTask[5].ptPrev;
        v7 = p_ptMiddle[4] * p_ptMiddle[3];
        v8 = v7 + v7;
        v9 = p_ptMiddle[5] * p_ptMiddle[3];
        igi2_frame.vYY = v9 + v9;
        v10 = p_ptMiddle[6] * p_ptMiddle[3];
        igi2_frame.vYW = v10 + v10;
        v11 = p_ptMiddle[4] * p_ptMiddle[4];
        igi2_frame.vXZ = v11 + v11;
        v12 = p_ptMiddle[5] * p_ptMiddle[4];
        igi2_frame.vYZ = v12 + v12;
        v13 = p_ptMiddle[6] * p_ptMiddle[4];
        igi2_frame.vXW = v13 + v13;
        v14 = p_ptMiddle[5] * p_ptMiddle[5];
        ptQTaska = v14 + v14;
        v15 = p_ptMiddle[5] * p_ptMiddle[6];
        v16 = v15 + v15;
        *(p_ptPrev - 10) = 1.0 - igi2_frame.vXZ - ptQTaska;
        *(p_ptPrev - 9) = v8 - v16;
        *(p_ptPrev - 8) = igi2_frame.vXW + igi2_frame.vYY;
        *(p_ptPrev - 7) = v16 + v8;
        v17 = 1.0 - (v4 * v4 + v4 * v4);
        *(p_ptPrev - 6) = v17 - ptQTaska;
        *(p_ptPrev - 5) = igi2_frame.vYZ - igi2_frame.vYW;
        *(p_ptPrev - 4) = igi2_frame.vYY - igi2_frame.vXW;
        *(p_ptPrev - 3) = igi2_frame.vYZ + igi2_frame.vYW;
        *(p_ptPrev - 2) = v17 - igi2_frame.vXZ;
        *(p_ptPrev - 1) = p_ptMiddle[7];
        *p_ptPrev = *p_ptMiddle;
        p_ptPrev[1] = p_ptMiddle[1];
        p_ptPrev[2] = p_ptMiddle[2];
        return;
      }
    }
    ptQTaskb = (double)(AnimController_nTime - (unsigned int)v3->ptPrev)
             / (double)((char *)ptNext->ptPrev - (char *)v3->ptPrev);
    Quat32_SLERP(
      &igi2_frame.tQ,
      (struct Quat32_t *)&v3->tQTaskRefList.ptMiddle,
      (struct Quat32_t *)&ptNext->tQTaskRefList.ptMiddle,
      ptQTaskb);
    v18 = igi2_frame.tQ.vX * igi2_frame.tQ.vX + igi2_frame.tQ.vX * igi2_frame.tQ.vX;
    v19 = igi2_frame.tQ.vY * igi2_frame.tQ.vX + igi2_frame.tQ.vY * igi2_frame.tQ.vX;
    igi2_frame.vXZa = igi2_frame.tQ.vZ * igi2_frame.tQ.vX + igi2_frame.tQ.vZ * igi2_frame.tQ.vX;
    igi2_frame.vXWa = igi2_frame.tQ.vW * igi2_frame.tQ.vX + igi2_frame.tQ.vW * igi2_frame.tQ.vX;
    igi2_frame.vYYa = igi2_frame.tQ.vY * igi2_frame.tQ.vY + igi2_frame.tQ.vY * igi2_frame.tQ.vY;
    igi2_frame.vYZa = igi2_frame.tQ.vZ * igi2_frame.tQ.vY + igi2_frame.tQ.vZ * igi2_frame.tQ.vY;
    igi2_frame.vYWa = igi2_frame.tQ.vW * igi2_frame.tQ.vY + igi2_frame.tQ.vW * igi2_frame.tQ.vY;
    igi2_frame.vZZ = igi2_frame.tQ.vZ * igi2_frame.tQ.vZ + igi2_frame.tQ.vZ * igi2_frame.tQ.vZ;
    v20 = igi2_frame.tQ.vW * igi2_frame.tQ.vZ + igi2_frame.tQ.vW * igi2_frame.tQ.vZ;
    *(float *)&ptQTask[4].ptPrev = 1.0 - igi2_frame.vYYa - igi2_frame.vZZ;
    *(float *)&ptQTask[4].tQTaskChildren.ptHead = v19 - v20;
    *(float *)&ptQTask[4].tQTaskChildren.ptMiddle = igi2_frame.vYWa + igi2_frame.vXZa;
    *(float *)&ptQTask[4].tQTaskChildren.ptTail = v20 + v19;
    v21 = 1.0 - v18;
    *(float *)&ptQTask[4].tQTaskRefList.ptHead = v21 - igi2_frame.vZZ;
    *(float *)&ptQTask[4].tQTaskRefList.ptMiddle = igi2_frame.vYZa - igi2_frame.vXWa;
    *(float *)&ptQTask[4].tQTaskRefList.ptTail = igi2_frame.vXZa - igi2_frame.vYWa;
    ptQTask[5].ptNext = (struct QTask_s *)igi2_frame.tQ.nOps;
    *(float *)&ptQTask[4].ptParent = igi2_frame.vYZa + igi2_frame.vXWa;
    *(float *)&ptQTask[4].eQTaskType = v21 - igi2_frame.vYYa;
    *(float *)&ptQTask[5].ptPrev = (*(float *)&ptNext->tQTaskChildren.ptMiddle - *(float *)&v3->tQTaskChildren.ptMiddle)
                                 * ptQTaskb
                                 + *(float *)&v3->tQTaskChildren.ptMiddle;
    *(float *)&ptQTask[5].tQTaskChildren.ptHead = (*(float *)&ptNext->tQTaskChildren.ptTail
                                                 - *(float *)&v3->tQTaskChildren.ptTail)
                                                * ptQTaskb
                                                + *(float *)&v3->tQTaskChildren.ptTail;
    *(float *)&ptQTask[5].tQTaskChildren.ptMiddle = (*(float *)&ptNext->tQTaskRefList.ptHead
                                                   - *(float *)&v3->tQTaskRefList.ptHead)
                                                  * ptQTaskb
                                                  + *(float *)&v3->tQTaskRefList.ptHead;
  }
}

// source: e/3/rigidmagicobj.c:121  [anchor-caller]
void __cdecl RigidMagicObj_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct LODVirModel_s *v3; // edi
  double vRadius; // st7
  struct LODVirModel_s *pxContexta = *(struct LODVirModel_s * *)&pxContext; // [esp+18h] [ebp+8h] ARGSLOT
  float pxContextb = *(float *)&pxContext; // [esp+18h] [ebp+8h] ARGSLOT

  pxContexta = MTP_GetLODVirModelExistsFn(*(char **)pxContext);
  if ( !pxContexta )
    pxContexta = nullptr;
  ModelObj_Init((struct ModelObj_s *)ptQTask, *((struct World_s **)pxContext + 1), pxContexta);
  ptQTask[7].tQTaskChildren.ptHead = nullptr;
  ptQTask[7].tQTaskChildren.ptMiddle = (struct QTask_s *)2;
  ptQTask[7].tQTaskRefList.ptHead = nullptr;
  ptQTask[7].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[7].tQTaskRefList.ptTail = nullptr;
  ptQTask[7].ptParent = nullptr;
  *(_DWORD *)&ptQTask[7].eQTaskType = 0;
  qmemcpy(&ptQTask[3].ptPrev, (char *)pxContext + 44, sizeof(struct QTask_s));
  ptQTask[8].ptNext = *((struct QTask_s **)pxContext + 31);
  ptQTask[7].ptPrev = *((struct QTask_s **)pxContext + 35);
  ptQTask[2].tQTaskRefList.ptTail = *((struct QReference_s **)pxContext + 34);
  if ( *((_DWORD *)pxContext + 37) )
    ptQTask[7].tQTaskChildren.ptHead = (struct QTask_s *)-1;
  if ( *((_DWORD *)pxContext + 36) )
  {
    v3 = pxContexta;
    if ( pxContexta && pxContexta->aptVirModel[0] )
      pxContextb = pxContexta->aptVirModel[0]->ptModel->ptMesh->vRadius;
    else
      pxContextb = 1.0;
    World_RegisterDynCubeObjFirstTimeRadius(
      *((struct World_s **)pxContext + 1),
      (struct DynCubeObj_s *)ptQTask,
      (struct real64x3_t *)((char *)pxContext + 8),
      pxContextb,
      (enum DynCubeTreeCategory_enum)ptQTask[7].tQTaskChildren.ptMiddle);
  }
  else
  {
    if ( pxContexta && pxContexta->aptVirModel[0] )
      vRadius = pxContexta->aptVirModel[0]->ptModel->ptMesh->vRadius;
    else
      vRadius = 1.0;
    v3 = pxContexta;
    *(float *)&ptQTask[1].eQTaskType = vRadius;
  }
  if ( v3 )
    ModelObj_SetLODVirModel((struct ModelObj_s *)ptQTask, v3, true);
  ModelObj_AttachToParent((struct ModelObj_s *)ptQTask, (struct MagicObjCreateContext_s *)pxContext);
}

// source: e/3/rigidmagicobj.c:199  [size]
void __cdecl RigidMagicObj_RunHandler(struct QTask_s *ptQTask)
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

// source: e/3/rigidmagicobj.c:212  [anchor-mhash]
void __cdecl RigidMagicObj_MagicObjEnterHandler(struct QTask_s *ptQTask, void *pxContext)
{
  if ( pxContext )
    pxContext = *((void **)pxContext + 16);
  else
    pxContext = nullptr;
  ((void (__cdecl *)(struct QTask_s *, void **))QTask_aatQTaskFinalEvent[5][RigidDynCubeObj_eQTaskType].pfHandler)(
    ptQTask,
    &pxContext);
}

// source: e/3/rigidmagicobj.c:255  [size]
void __cdecl RigidMagicObj_UpdateMagicObjHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *ptHead; // edx
  int v3; // eax
  struct QTask_s *v4; // ecx
  void (__cdecl *pfHandler)(struct QTask_s *, struct UpdateMagicObjContext_t *); // ecx
  int v6; // eax
  struct QTask_s *ptNext; // edi
  int v8; // ecx
  struct QTask_s *v9; // edx
  void (__cdecl *v10)(int, struct UpdateMagicObjContext_t *); // edx
  int v11; // eax
  struct UpdateMagicObjContext_t tUpdateMagicObjContext; // [esp+8h] [ebp-Ch] BYREF

  ptQTask[5].tQTaskRefList.ptTail = *((struct QReference_s **)pxContext + 1);
  ptQTask[5].tQTaskRefList.ptMiddle = *(struct QReference_s **)pxContext;
  *(_DWORD *)&ptQTask[5].eQTaskType = 0;
  ptQTask[5].ptParent = nullptr;
  ModelObj_UpdateAttachment((struct ModelObj_s *)ptQTask);
  ptHead = ptQTask->tQTaskChildren.ptHead;
  tUpdateMagicObjContext.ptParentOrientation = (struct real32x9_t *)&ptQTask[3].ptPrev;
  tUpdateMagicObjContext.ptParentPos = (struct real64x3_t *)&ptQTask[1];
  tUpdateMagicObjContext.ptTriggeredBy = ptQTask;
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
      pfHandler = (void (__cdecl *)(struct QTask_s *, struct UpdateMagicObjContext_t *))QTask_aatQTaskFinalEvent[MagicObj_eUpdateMagicObjEvent][ptHead->eQTaskType].pfHandler;
      v6 = v3 + 1;
      QTask_nProtectedQTaskStackOffset = v6;
      if ( pfHandler )
      {
        pfHandler(ptHead, &tUpdateMagicObjContext);
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
        v10 = (void (__cdecl *)(int, struct UpdateMagicObjContext_t *))QTask_aatQTaskFinalEvent[MagicObj_eUpdateMagicObjEvent][*(unsigned __int16 *)(v8 + 36)].pfHandler;
        v11 = v3 + 1;
        QTask_nProtectedQTaskStackOffset = v11;
        if ( v10 )
        {
          v10(v8, &tUpdateMagicObjContext);
          v11 = QTask_nProtectedQTaskStackOffset;
        }
        v8 = dword_849C7DC[v11];
        v3 = v11 - 1;
      }
    }
  }
}

// source: e/3/rigidmagicobj.c:300  [size]
void __cdecl RigidMagicObj_CollisionEvaluateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *v2; // eax

  v2 = *((struct QTask_s **)pxContext + 1);
  *(_BYTE *)pxContext = ptQTask != v2 && ptQTask[8].ptNext != v2;
}

// source: e/3/rigidmagicobj.c:320  [anchor-mhash]
void __cdecl RigidMagicObj_DeleteHandler(struct QTask_s *ptQTask)
{
  World_RemoveDynCubeObj((struct World_s *)ptQTask[2].ptParent, (struct DynCubeObj_s *)ptQTask);
  if ( *(_DWORD *)&ptQTask[2].eQTaskType )
  {
    ModelObj_SetLODVirModel((struct ModelObj_s *)ptQTask, nullptr, false);
    ptQTask[7].tQTaskRefList.ptHead = nullptr;
    ptQTask[7].tQTaskRefList.ptMiddle = nullptr;
    ptQTask[7].tQTaskRefList.ptTail = nullptr;
    ptQTask[7].ptParent = nullptr;
    *(_DWORD *)&ptQTask[7].eQTaskType = 0;
  }
}

// source: e/3/rigidmagicobj.c:373  [anchor-strings]
void __cdecl RigidMagicObj_Open()
{
  __int16 v0; // ax
  unsigned __int16 v1; // si

  RigidMagicObj_eQTaskType = QTask_NewQTaskType("MagicObj", 328, RigidDynCubeObj_eQTaskType, 0, 0);
  v0 = QTask_NewQTaskEventFn(0, "CreateMagicObj");
  v1 = RigidMagicObj_eQTaskType;
  RigidMagicObj_eCreateMagicObjEvent = v0;
  QTask_LinkQTaskEventHandlerFn(RigidMagicObj_eQTaskType, 5, nullptr);
  QTask_LinkQTaskEventHandlerFn(v1, MagicObj_eMagicObjEnterEvent, RigidMagicObj_MagicObjEnterHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 1, RigidMagicObj_RunHandler);
  QTask_LinkQTaskEventHandlerFn(v1, 0, RigidMagicObj_CreateHandler);
  QTask_LinkQTaskEventHandlerFn(v1, MagicObj_eUpdateMagicObjEvent, RigidMagicObj_UpdateMagicObjHandler);
  QTask_LinkQTaskEventHandlerFn(v1, 13, RigidMagicObj_CollisionEvaluateHandler);
  QTask_LinkQTaskEventHandlerFn(
    v1,
    MagicObj_eSetMagicObjParametersEvent,
    (void (__cdecl *)(struct QTask_s *, void *))RigidMagicObj_SetMagicObjParametersHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 2, RigidMagicObj_DeleteHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, BoneDynCubeObj_eInterpolateQTaskEvent, RigidMagicObj_InterpolateHandler);
  QTask_LinkQTaskEventHandlerFn(v1, ShadowVolume_eGetShadowInfoEvent, nullptr);
  Symbol_Register(
    "TASKTYPE_MAGICOBJ",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)v1,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
}

// source: e/3/rigidmagicobj.c:407  [anchor-hash]
void __cdecl RigidMagicObj_Close()
{
  QTask_DeleteQTaskType(RigidMagicObj_eQTaskType);
  RigidMagicObj_eQTaskType = 512;
  QTask_DeleteQTaskEvent(RigidMagicObj_eCreateMagicObjEvent);
  RigidMagicObj_eCreateMagicObjEvent = 512;
}

// source: e/3/rigidmagicobj.c:430  [size]
unsigned __int16 __cdecl RigidMagicObj_GetQTaskType()
{
  return RigidMagicObj_eQTaskType;
}

// source: e/3/rigidmagicobj.c:445  [size]
__int16 __cdecl RigidMagicObj_GetCreateMagicObjEvent()
{
  return RigidMagicObj_eCreateMagicObjEvent;
}
