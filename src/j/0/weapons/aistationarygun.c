/* j/0/weapons/aistationarygun.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/weapons/aistationarygun.c:64  [anchor-mhash]
void __cdecl AIStationaryGun_DeSerializeDoneHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QReference_s *ptHead; // edi

  QTask_DeleteQTaskAndQTaskRefSafe(&ptQTask[11].tQTaskRefList.ptTail);
  ptHead = ptQTask[12].tQTaskRefList.ptHead;
  if ( ptHead )
  {
    SectorObject_RemoveInteriorDynCubeObj((struct DynCubeObj_s *)ptHead);
    if ( ptHead[24].pxObject )
    {
      ptHead[8].ptPrev = nullptr;
      ptHead[8].pxObject = nullptr;
    }
    else
    {
      SectorObject_RegisterInteriorDynCubeObjSpecificSectorObject(
        (struct World_s *)ptHead[9].ptPrev,
        nullptr,
        (struct DynCubeObj_s *)ptHead,
        (struct real64x3_t *)&ptHead[3].ptPrev);
    }
  }
}

// source: j/0/weapons/aistationarygun.c:92  [anchor-mhash]
void __cdecl AIStationaryGun_SetGunPosAndOrientation(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct real32x9_t tReal32x9; };
    struct { char igi2_o1[40]; struct SetPositionContext_s tSetPositionContext; };
    char igi2_extent[104];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  double v1; // st7
  double v2; // st6
  double v3; // st7
  struct QReference_s *ptHead; // ebp
  void (__cdecl *pfHandler)(struct QReference_s *, struct SetPositionContext_s *); // eax

  if ( ptQTask[12].tQTaskRefList.ptHead )
  {
    Real32x9_Create(&igi2_frame.tReal32x9, 0.0, 0.0, *(float *)&ptQTask[11].tQTaskRefList.ptMiddle);
    *(float *)&igi2_frame.tSetPositionContext.tPos.vX = igi2_frame.tReal32x9.tZ.vX * *(float *)&ptQTask[9].ptNext
                                           + igi2_frame.tReal32x9.tX.vX * *(float *)&ptQTask[8].ptParent
                                           + igi2_frame.tReal32x9.tY.vX * *(float *)&ptQTask[8].eQTaskType;
    *((float *)&igi2_frame.tSetPositionContext.tPos.vX + 1) = igi2_frame.tReal32x9.tZ.vY * *(float *)&ptQTask[9].ptNext
                                                 + igi2_frame.tReal32x9.tX.vY * *(float *)&ptQTask[8].ptParent
                                                 + igi2_frame.tReal32x9.tY.vY * *(float *)&ptQTask[8].eQTaskType;
    *(float *)&igi2_frame.tSetPositionContext.tPos.vY = igi2_frame.tReal32x9.tZ.vZ * *(float *)&ptQTask[9].ptNext
                                           + igi2_frame.tReal32x9.tX.vZ * *(float *)&ptQTask[8].ptParent
                                           + igi2_frame.tReal32x9.tY.vZ * *(float *)&ptQTask[8].eQTaskType;
    *((float *)&igi2_frame.tSetPositionContext.tPos.vY + 1) = igi2_frame.tReal32x9.tZ.vX * *(float *)&ptQTask[9].tQTaskChildren.ptMiddle
                                                 + igi2_frame.tReal32x9.tX.vX * *(float *)&ptQTask[9].ptPrev
                                                 + igi2_frame.tReal32x9.tY.vX * *(float *)&ptQTask[9].tQTaskChildren.ptHead;
    *(float *)&igi2_frame.tSetPositionContext.tPos.vZ = igi2_frame.tReal32x9.tZ.vY * *(float *)&ptQTask[9].tQTaskChildren.ptMiddle
                                           + igi2_frame.tReal32x9.tX.vY * *(float *)&ptQTask[9].ptPrev
                                           + igi2_frame.tReal32x9.tY.vY * *(float *)&ptQTask[9].tQTaskChildren.ptHead;
    *((float *)&igi2_frame.tSetPositionContext.tPos.vZ + 1) = igi2_frame.tReal32x9.tZ.vZ * *(float *)&ptQTask[9].tQTaskChildren.ptMiddle
                                                 + igi2_frame.tReal32x9.tX.vZ * *(float *)&ptQTask[9].ptPrev
                                                 + igi2_frame.tReal32x9.tY.vZ * *(float *)&ptQTask[9].tQTaskChildren.ptHead;
    igi2_frame.tSetPositionContext.tOrientation.tX.vX = igi2_frame.tReal32x9.tZ.vX * *(float *)&ptQTask[9].tQTaskRefList.ptMiddle
                                           + igi2_frame.tReal32x9.tX.vX * *(float *)&ptQTask[9].tQTaskChildren.ptTail
                                           + igi2_frame.tReal32x9.tY.vX * *(float *)&ptQTask[9].tQTaskRefList.ptHead;
    v1 = igi2_frame.tReal32x9.tZ.vY * *(float *)&ptQTask[9].tQTaskRefList.ptMiddle
       + igi2_frame.tReal32x9.tX.vY * *(float *)&ptQTask[9].tQTaskChildren.ptTail;
    v2 = igi2_frame.tReal32x9.tY.vY * *(float *)&ptQTask[9].tQTaskRefList.ptHead;
    LODWORD(igi2_frame.tSetPositionContext.tOrientation.tY.vX) = (char *)&ptQTask[9].tQTaskRefList.ptTail->ptNext
                                                    + igi2_frame.tReal32x9.nOps
                                                    + 1;
    igi2_frame.tSetPositionContext.tOrientation.tX.vY = v1 + v2;
    igi2_frame.tSetPositionContext.tOrientation.tX.vZ = igi2_frame.tReal32x9.tZ.vZ * *(float *)&ptQTask[9].tQTaskRefList.ptMiddle
                                           + igi2_frame.tReal32x9.tX.vZ * *(float *)&ptQTask[9].tQTaskChildren.ptTail
                                           + igi2_frame.tReal32x9.tY.vZ * *(float *)&ptQTask[9].tQTaskRefList.ptHead;
    qmemcpy(&ptQTask[3].ptPrev, &igi2_frame.tSetPositionContext, sizeof(struct QTask_s));
    Real32x9_Create(
      &igi2_frame.tReal32x9,
      *(float *)&ptQTask[11].tQTaskRefList.ptHead,
      0.0,
      *(float *)&ptQTask[11].tQTaskRefList.ptMiddle);
    *(float *)&igi2_frame.tSetPositionContext.tPos.vX = igi2_frame.tReal32x9.tZ.vX * *(float *)&ptQTask[9].ptNext
                                           + igi2_frame.tReal32x9.tX.vX * *(float *)&ptQTask[8].ptParent
                                           + igi2_frame.tReal32x9.tY.vX * *(float *)&ptQTask[8].eQTaskType;
    *((float *)&igi2_frame.tSetPositionContext.tPos.vX + 1) = igi2_frame.tReal32x9.tZ.vY * *(float *)&ptQTask[9].ptNext
                                                 + igi2_frame.tReal32x9.tX.vY * *(float *)&ptQTask[8].ptParent
                                                 + igi2_frame.tReal32x9.tY.vY * *(float *)&ptQTask[8].eQTaskType;
    *(float *)&igi2_frame.tSetPositionContext.tPos.vY = igi2_frame.tReal32x9.tZ.vZ * *(float *)&ptQTask[9].ptNext
                                           + igi2_frame.tReal32x9.tX.vZ * *(float *)&ptQTask[8].ptParent
                                           + igi2_frame.tReal32x9.tY.vZ * *(float *)&ptQTask[8].eQTaskType;
    *((float *)&igi2_frame.tSetPositionContext.tPos.vY + 1) = igi2_frame.tReal32x9.tZ.vX * *(float *)&ptQTask[9].tQTaskChildren.ptMiddle
                                                 + igi2_frame.tReal32x9.tX.vX * *(float *)&ptQTask[9].ptPrev
                                                 + igi2_frame.tReal32x9.tY.vX * *(float *)&ptQTask[9].tQTaskChildren.ptHead;
    *(float *)&igi2_frame.tSetPositionContext.tPos.vZ = igi2_frame.tReal32x9.tZ.vY * *(float *)&ptQTask[9].tQTaskChildren.ptMiddle
                                           + igi2_frame.tReal32x9.tX.vY * *(float *)&ptQTask[9].ptPrev
                                           + igi2_frame.tReal32x9.tY.vY * *(float *)&ptQTask[9].tQTaskChildren.ptHead;
    v3 = igi2_frame.tReal32x9.tZ.vZ * *(float *)&ptQTask[9].tQTaskChildren.ptMiddle;
    LODWORD(igi2_frame.tSetPositionContext.tOrientation.tY.vX) = (char *)&ptQTask[9].tQTaskRefList.ptTail->ptNext
                                                    + igi2_frame.tReal32x9.nOps
                                                    + 1;
    *((float *)&igi2_frame.tSetPositionContext.tPos.vZ + 1) = v3
                                                 + igi2_frame.tReal32x9.tX.vZ * *(float *)&ptQTask[9].ptPrev
                                                 + igi2_frame.tReal32x9.tY.vZ * *(float *)&ptQTask[9].tQTaskChildren.ptHead;
    igi2_frame.tSetPositionContext.tOrientation.tX.vX = igi2_frame.tReal32x9.tZ.vX * *(float *)&ptQTask[9].tQTaskRefList.ptMiddle
                                           + igi2_frame.tReal32x9.tX.vX * *(float *)&ptQTask[9].tQTaskChildren.ptTail
                                           + igi2_frame.tReal32x9.tY.vX * *(float *)&ptQTask[9].tQTaskRefList.ptHead;
    igi2_frame.tSetPositionContext.tOrientation.tX.vY = igi2_frame.tReal32x9.tZ.vY * *(float *)&ptQTask[9].tQTaskRefList.ptMiddle
                                           + igi2_frame.tReal32x9.tX.vY * *(float *)&ptQTask[9].tQTaskChildren.ptTail
                                           + igi2_frame.tReal32x9.tY.vY * *(float *)&ptQTask[9].tQTaskRefList.ptHead;
    igi2_frame.tSetPositionContext.tOrientation.tX.vZ = igi2_frame.tReal32x9.tZ.vZ * *(float *)&ptQTask[9].tQTaskRefList.ptMiddle
                                           + igi2_frame.tReal32x9.tX.vZ * *(float *)&ptQTask[9].tQTaskChildren.ptTail
                                           + igi2_frame.tReal32x9.tY.vZ * *(float *)&ptQTask[9].tQTaskRefList.ptHead;
    qmemcpy(&ptQTask[10].tQTaskChildren.ptTail, &igi2_frame.tSetPositionContext, sizeof(struct QTask_s));
    GameFunctions_GetMagicVertex((struct real64x3_t *)&ptQTask[9].ptParent, ptQTask, 0);
    qmemcpy(&igi2_frame.tSetPositionContext, &ptQTask[9].ptParent, 0x18u);
    ptHead = ptQTask[12].tQTaskRefList.ptHead;
    qmemcpy(
      &igi2_frame.tSetPositionContext.tOrientation,
      &ptQTask[10].tQTaskChildren.ptTail,
      sizeof(igi2_frame.tSetPositionContext.tOrientation));
    pfHandler = (void (__cdecl *)(struct QReference_s *, struct SetPositionContext_s *))QTask_aatQTaskFinalEvent[7][LOWORD(ptHead[3].ptNext)].pfHandler;
    if ( pfHandler )
      pfHandler(ptHead, &igi2_frame.tSetPositionContext);
  }
}

// source: j/0/weapons/aistationarygun.c:141  [anchor-mhash]
void __cdecl AIStationaryGun_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct World_s *ptWorld; };
    struct { struct World_s *ptWorlda; };
    struct { char igi2_o2[4]; struct QTask_s ptParent; };
    struct { char igi2_o3[44]; int v13; };
    struct { char igi2_o4[48]; int v14; };
    struct { char igi2_o5[52]; int v15; };
    struct { char igi2_o6[56]; int v16; };
    struct { char igi2_o7[60]; int v17; };
    struct { char igi2_o8[64]; int v18; };
    struct { char igi2_o9[68]; int v19; };
    struct { char igi2_o10[72]; int v20; };
    struct { char igi2_o11[76]; int v21; };
    struct { char igi2_o12[80]; int v22; };
    struct { char igi2_o13[84]; int v23; };
    struct { char igi2_o14[88]; int v24; };
    struct { char igi2_o15[92]; int v25; };
    struct { char igi2_o16[96]; int v26; };
    struct { char igi2_o17[100]; int v27; };
    struct { char igi2_o18[104]; int v28; };
    struct { char igi2_o19[108]; int v29; };
    struct { char igi2_o20[112]; int v30; };
    struct { char igi2_o21[116]; int v31; };
    struct { char igi2_o22[120]; int v32; };
    struct { char igi2_o23[124]; int v33; };
    struct { char igi2_o24[128]; struct QTask_s *v34; };
    struct { char igi2_o25[140]; struct QReference_s *v35; };
    struct { char igi2_o26[144]; struct QTask_s *v36; };
    struct { char igi2_o27[148]; int v37; };
    struct { char igi2_o28[152]; int v38; };
    struct { char igi2_o29[156]; int v39; };
    char igi2_extent[164];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct DynCubeObj_s *ptHead; // edi
  struct QTask_s *ptTail; // eax
  struct QTask_s *v4; // edx
  struct QReference_s *v5; // ecx
  struct QTask_s *ptPrev; // edx
  struct QTask_s *v7; // edi
  struct QTask_s *v8; // ecx
  double v9; // st7

  igi2_frame.ptWorld = (struct World_s *)MTP_GetLODVirModelExistsFn((char *)ptQTask[11].tQTaskChildren.ptTail);
  if ( !igi2_frame.ptWorld )
    igi2_frame.ptWorld = nullptr;
  ptHead = (struct DynCubeObj_s *)ptQTask[12].tQTaskRefList.ptHead;
  if ( ptHead )
  {
    SectorObject_RemoveInteriorDynCubeObj(ptHead);
    QTask_Delete((struct QTask_s *)ptQTask[12].tQTaskRefList.ptHead);
    ptQTask[12].tQTaskRefList.ptHead = nullptr;
  }
  if ( igi2_frame.ptWorld )
  {
    ptTail = ptQTask[11].tQTaskChildren.ptTail;
    igi2_frame.v34 = ptQTask;
    v4 = (struct QTask_s *)Game_ptGame->ptWorld;
    v5 = ptQTask[2].tQTaskRefList.ptTail;
    igi2_frame.ptParent.ptNext = ptTail;
    igi2_frame.ptParent.ptPrev = v4;
    ptPrev = ptQTask[7].ptPrev;
    memset(&igi2_frame.ptParent.tQTaskChildren, 0, 32);
    igi2_frame.v13 = 0;
    igi2_frame.v14 = 1065353216;
    igi2_frame.v15 = 0;
    igi2_frame.v16 = 0;
    igi2_frame.v17 = 0;
    igi2_frame.v18 = 1065353216;
    igi2_frame.v19 = 0;
    igi2_frame.v20 = 0;
    igi2_frame.v21 = 0;
    igi2_frame.v22 = 1065353216;
    igi2_frame.v23 = 0;
    igi2_frame.v24 = 1065353216;
    igi2_frame.v25 = 0;
    igi2_frame.v26 = 0;
    igi2_frame.v27 = 0;
    igi2_frame.v28 = 1065353216;
    igi2_frame.v29 = 0;
    igi2_frame.v30 = 0;
    igi2_frame.v31 = 0;
    igi2_frame.v32 = 1065353216;
    igi2_frame.v33 = 0;
    igi2_frame.v35 = v5;
    igi2_frame.v36 = ptPrev;
    igi2_frame.v38 = 0;
    igi2_frame.v37 = 1;
    igi2_frame.v39 = 0;
    v7 = QTask_NewFn(ptQTask, SectorInteriorObject_eQTaskType, &igi2_frame.ptParent);
    ptQTask[12].tQTaskRefList.ptHead = (struct QReference_s *)v7;
    AIStationaryGun_SetGunPosAndOrientation(ptQTask);
    if ( v7[7].tQTaskChildren.ptTail )
    {
      v7[2].tQTaskRefList.ptHead = nullptr;
      v7[2].tQTaskRefList.ptMiddle = nullptr;
    }
    else
    {
      SectorObject_RegisterInteriorDynCubeObjSpecificSectorObject(
        (struct World_s *)v7[2].ptParent,
        nullptr,
        (struct DynCubeObj_s *)v7,
        (struct real64x3_t *)&v7[1]);
    }
    igi2_frame.ptWorlda = (struct World_s *)v7[2].ptParent;
    SectorObject_RemoveInteriorDynCubeObj((struct DynCubeObj_s *)v7);
    if ( v7[7].tQTaskChildren.ptTail )
    {
      v7[2].tQTaskRefList.ptHead = nullptr;
      v7[2].tQTaskRefList.ptMiddle = nullptr;
    }
    else
    {
      SectorObject_RegisterInteriorDynCubeObjSpecificSectorObject(
        igi2_frame.ptWorlda,
        nullptr,
        (struct DynCubeObj_s *)v7,
        (struct real64x3_t *)&v7[1]);
    }
  }
  AIStationaryGun_SetGunPosAndOrientation(ptQTask);
  v8 = ptQTask[11].tQTaskChildren.ptTail;
  if ( *(float *)&v8[3].ptPrev >= 0.0 )
  {
    if ( *(float *)&v8[3].ptPrev <= 1.0 )
      v9 = *(float *)&v8[3].ptPrev;
    else
      v9 = 1.0;
  }
  else
  {
    v9 = 0.0;
  }
  *(float *)&v8[3].ptPrev = v9;
  ptQTask[12].tQTaskChildren.ptTail[2].tQTaskRefList.ptHead = (struct QReference_s *)ptQTask[11].tQTaskChildren.ptTail[3].ptPrev;
  *(float *)&ptQTask[11].tQTaskChildren.ptTail->ptParent = *(float *)&ptQTask[11].tQTaskChildren.ptTail->ptParent
                                                         * 0.01745329238474369;
  *(float *)&ptQTask[11].tQTaskChildren.ptTail->eQTaskType = *(float *)&ptQTask[11].tQTaskChildren.ptTail->eQTaskType
                                                           * 0.01745329238474369;
  *(float *)&ptQTask[11].tQTaskChildren.ptTail[1].ptNext = *(float *)&ptQTask[11].tQTaskChildren.ptTail[1].ptNext
                                                         * 0.01745329238474369;
  *(float *)&ptQTask[11].tQTaskChildren.ptTail[1].tQTaskChildren.ptHead = *(float *)&ptQTask[11].tQTaskChildren.ptTail[1].tQTaskChildren.ptHead
                                                                        * 0.01745329238474369
                                                                        * 0.03333333507180214;
  *(float *)&ptQTask[11].tQTaskChildren.ptTail[1].tQTaskChildren.ptMiddle = *(float *)&ptQTask[11].tQTaskChildren.ptTail[1].tQTaskChildren.ptMiddle
                                                                          * 0.01745329238474369
                                                                          * 0.03333333507180214;
  *(float *)&ptQTask[11].tQTaskChildren.ptTail[3].ptNext = *(float *)&ptQTask[11].tQTaskChildren.ptTail[3].ptNext
                                                         * 0.01745329238474369
                                                         * 0.03333333507180214;
}

void __cdecl sub_505750(struct QTask_s *a1)
{
  struct QReference_s *ptHead; // edi
  struct World_s *ptPrev; // esi

  ptHead = a1[12].tQTaskRefList.ptHead;
  if ( ptHead )
  {
    ptPrev = (struct World_s *)ptHead[9].ptPrev;
    SectorObject_RemoveInteriorDynCubeObj((struct DynCubeObj_s *)ptHead);
    if ( ptHead[24].pxObject )
    {
      ptHead[8].ptPrev = nullptr;
      ptHead[8].pxObject = nullptr;
    }
    else
    {
      SectorObject_RegisterInteriorDynCubeObjSpecificSectorObject(
        ptPrev,
        nullptr,
        (struct DynCubeObj_s *)ptHead,
        (struct real64x3_t *)&ptHead[3].ptPrev);
    }
  }
}

// source: j/0/weapons/aistationarygun.c:253  [anchor-mhash]
void __cdecl AIStationaryGun_UpdateAttachmentHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptNext; // eax
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

  if ( ptQTask[2].ptParent )
  {
    ModelObj_UpdateAttachment((struct ModelObj_s *)ptQTask);
    ptNext = ptQTask[3].ptNext;
    if ( ptNext && (ptHead = (int)ptNext->tQTaskChildren.ptHead, *(_DWORD *)ptHead) && ptHead )
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
    v8 = ptQTask->tQTaskChildren.ptHead;
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
    qmemcpy(&ptQTask[8].ptParent, &ptQTask[3].ptPrev, sizeof(struct QTask_s));
    qmemcpy(&ptQTask[8].tQTaskChildren, &ptQTask[1], 0x18u);
    AIStationaryGun_SetGunPosAndOrientation(ptQTask);
  }
}

// source: j/0/weapons/aistationarygun.c:302  [anchor-mhash]
void __cdecl AIStationaryGun_LimitRotation(struct QTask_s *ptQTask)
{
  struct QTask_s *ptTail; // ecx
  double v2; // st7
  double v3; // st7

  ptTail = ptQTask[11].tQTaskChildren.ptTail;
  if ( *(float *)&ptTail->eQTaskType <= (double)*(float *)&ptQTask[11].tQTaskRefList.ptHead )
  {
    if ( *(float *)&ptTail->ptParent >= (double)*(float *)&ptQTask[11].tQTaskRefList.ptHead )
      v2 = *(float *)&ptQTask[11].tQTaskRefList.ptHead;
    else
      v2 = *(float *)&ptTail->ptParent;
  }
  else
  {
    v2 = *(float *)&ptTail->eQTaskType;
  }
  *(float *)&ptQTask[11].tQTaskRefList.ptHead = v2;
  if ( *(float *)&ptTail[1].ptNext < 6.251769410604253 )
  {
    v3 = -*(float *)&ptTail[1].ptNext;
    if ( v3 <= *(float *)&ptQTask[11].tQTaskRefList.ptMiddle )
    {
      if ( *(float *)&ptTail[1].ptNext < (double)*(float *)&ptQTask[11].tQTaskRefList.ptMiddle )
      {
        ptQTask[11].tQTaskRefList.ptMiddle = (struct QReference_s *)ptTail[1].ptNext;
        return;
      }
      v3 = *(float *)&ptQTask[11].tQTaskRefList.ptMiddle;
    }
    *(float *)&ptQTask[11].tQTaskRefList.ptMiddle = v3;
  }
}

// source: j/0/weapons/aistationarygun.c:473  [size]
void __cdecl AIStationaryGun_SoundUpdateParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = (char *)ptQTask + 392;
  *((_DWORD *)pxContext + 1) = (char *)ptQTask + 416;
  *((_DWORD *)pxContext + 2) = 0;
}

// source: j/0/weapons/aistationarygun.c:496  [anchor-caller]
void __cdecl AIStationaryGun_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *v2; // ebx
  char *v3; // esi
  __int16 v4; // ax
  struct QTask_s *ptNext; // ecx
  void (__cdecl *pfHandler)(struct QTask_s *, struct QTask_s **); // eax
  bool v7; // zf
  struct QReference_s **v8; // eax
  int v9; // eax
  struct QReference_s *v10; // ecx
  int v11; // esi
  struct QTask_s *v12; // eax
  struct QTask_s *v13; // eax
  struct QTask_s *ptHead; // esi
  struct QReference_s *v15; // eax
  struct QTask_s *v16; // edi
  char *p_tQTaskChildren; // edx
  int v18; // eax
  struct WeaponType_s *WeaponTypeFromID; // eax
  struct QTask_s *v20; // eax

  v2 = ptQTask;
  v3 = (char *)pxContext;
  ((void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[0][RigidMagicObj_eQTaskType].pfHandler)(
    ptQTask,
    pxContext);
  v4 = AIStationaryGun_eGetGunParametersEvent;
  ptQTask = nullptr;
  if ( AIStationaryGun_eGetGunParametersEvent == 512 )
  {
    v4 = QTask_NewQTaskEventFn(0, "AIStationaryGunGetGunParams");
    AIStationaryGun_eGetGunParametersEvent = v4;
  }
  ptNext = v2[8].ptNext;
  pfHandler = (void (__cdecl *)(struct QTask_s *, struct QTask_s **))QTask_aatQTaskFinalEvent[v4][ptNext->eQTaskType].pfHandler;
  if ( pfHandler )
    pfHandler(ptNext, &ptQTask);
  v7 = ptQTask == nullptr;
  v2[11].tQTaskChildren.ptTail = ptQTask;
  if ( v7 )
  {
    v8 = Level_atLevelQTaskID;
    do
    {
      if ( *v8 && (*v8)->pxObject == v2 )
        break;
      ++v8;
    }
    while ( (int)v8 < 127904760 );
  }
  qmemcpy(&v2[8].tQTaskChildren, v3 + 8, 0x18u);
  qmemcpy(&v2[8].ptParent, (char *)pxContext + 44, sizeof(struct QTask_s));
  v2[11].tQTaskRefList.ptHead = nullptr;
  v2[11].tQTaskRefList.ptMiddle = nullptr;
  v9 = 0;
  while ( 1 )
  {
    v10 = Level_atLevelQTaskID[v9];
    if ( v10 )
    {
      if ( v10->pxObject == v2[8].ptNext )
        break;
    }
    if ( ++v9 >= 4096 )
    {
      v11 = -1;
      goto LABEL_15;
    }
  }
  v11 = v9;
LABEL_15:
  v12 = QTask_NewFn(v2, Weapon_eQTaskType, nullptr);
  v12[16].tQTaskRefList.ptTail = (struct QReference_s *)v11;
  v2[12].tQTaskChildren.ptTail = v12;
  v13 = v12[5].ptNext;
  if ( v13 )
  {
    ptHead = v13->tQTaskChildren.ptHead;
    if ( ptHead )
    {
      v15 = (struct QReference_s *)ptHead[3].ptNext;
      ptHead[4].tQTaskChildren.ptMiddle = (struct QTask_s *)((int)ptHead[4].tQTaskChildren.ptMiddle | 2);
      v16 = v2[8].ptNext;
      if ( v15 )
        QReference_Delete(v15, &QTask_tQTaskRefPool);
      ptHead[3].ptNext = (struct QTask_s *)QTask_NewQTaskRef(v16);
    }
  }
  p_tQTaskChildren = (char *)&ptQTask[2].tQTaskChildren;
  if ( !ptQTask )
    p_tQTaskChildren = unk_699A28;
  v18 = Script_ParseLineInt32(p_tQTaskChildren);
  WeaponTypeFromID = WeaponType_GetWeaponTypeFromID(v18);
  Weapon_EnableWeaponType(v2[12].tQTaskChildren.ptTail, WeaponTypeFromID->zWeaponScriptID, true);
  v2[12].tQTaskChildren.ptTail[1].tQTaskRefList.ptHead = (struct QReference_s *)1;
  v20 = v2[8].ptNext;
  v2[11].tQTaskRefList.ptTail = nullptr;
  qmemcpy(&v2[9].ptParent, &v20[1], 0x18u);
  qmemcpy(&v2[10].tQTaskChildren.ptTail, &v20[3].ptPrev, sizeof(struct QTask_s));
  v2[11].ptParent = nullptr;
  *(_DWORD *)&v2[11].eQTaskType = 0;
  v2[12].tQTaskChildren.ptMiddle = nullptr;
  v2[12].tQTaskRefList.ptHead = nullptr;
}

// source: j/0/weapons/aistationarygun.c:595  [anchor-mhash]
void __cdecl AIStationaryGun_RunHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct real64x3_t vValue; };
    struct { char igi2_o1[40]; float v44; };
    struct { char igi2_o2[44]; float v45; };
    struct { char igi2_o3[48]; int v46; };
    struct { char igi2_o4[52]; float v47; };
    struct { char igi2_o5[56]; int v48; };
    struct { char igi2_o6[60]; float v49; };
    struct { char igi2_o7[64]; _DWORD v50[2]; };
    struct { char igi2_o8[72]; double ptNetManagerGameMessage[3]; };
    struct { char igi2_o9[96]; double v52[3]; };
    struct { char igi2_o10[120]; float v53[10]; };
    char igi2_extent[160];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *v1; // ebx
  struct QTask_s *ptNext; // ecx
  int v3; // eax
  void (__cdecl *pfHandler)(struct QTask_s *, _DWORD *); // edx
  _DWORD *v5; // eax
  _DWORD *v6; // edx
  bool v7; // zf
  int v8; // ecx
  int v9; // esi
  double v10; // st7
  double v11; // st6
  long double v12; // st5
  struct QTask_s *ptParent; // eax
  struct QTask_s *ptHead; // edx
  float v15; // ecx
  float *ptTail; // ecx
  double v17; // st7
  double v18; // st7
  double v19; // st6
  double v20; // st7
  double v21; // st6
  double v22; // st7
  double v23; // st7
  double v24; // st7
  struct QTask_s *v25; // eax
  struct QTask_s *v26; // eax
  struct QTask_s *v27; // ecx
  double v28; // st7
  double v29; // st6
  double v30; // st7
  double v31; // st7
  struct QReference_s *v32; // eax
  unsigned __int16 *pxObject; // eax
  struct QTask_s *v34; // eax
  struct QTask_s *v35; // esi
  struct QTask_s *v36; // edx
  struct QTask_s *v37; // ebx
  int v38; // ecx
  int v39; // edx
  struct QTask_s *v40; // eax
  void (__cdecl *v41)(int); // eax
  int v42; // edx

  v1 = ptQTask;
  ptNext = ptQTask[8].ptNext;
  v3 = 0;
  igi2_frame.v50[0] = 0;
  igi2_frame.v50[1] = 0;
  pfHandler = (void (__cdecl *)(struct QTask_s *, _DWORD *))QTask_aatQTaskFinalEvent[AIDetection_eGetAIDetectionEvent][ptNext->eQTaskType].pfHandler;
  igi2_frame.v45 = 0.0;
  igi2_frame.v44 = 0.0;
  igi2_frame.v46 = 0;
  igi2_frame.v48 = 0;
  if ( pfHandler )
  {
    pfHandler(ptNext, igi2_frame.v50);
    v3 = igi2_frame.v50[0];
  }
  if ( v3 && ptQTask[11].tQTaskChildren.ptTail )
  {
    qmemcpy(igi2_frame.v52, &ptQTask[8].tQTaskChildren, sizeof(igi2_frame.v52));
    ptQTask[12].tQTaskChildren.ptTail[2].tQTaskChildren.ptMiddle = *(struct QTask_s **)(v3 + 4);
    v5 = *(_DWORD **)(v3 + 28);
    v6 = (_DWORD *)*v5;
    v7 = *v5 == 0;
    qmemcpy(igi2_frame.v53, &ptQTask[8].ptParent, sizeof(igi2_frame.v53));
    if ( !v7 )
    {
      while ( 2 )
      {
        v8 = 0;
        while ( !*((_BYTE *)v5 + v8 + 51) )
        {
          if ( ++v8 >= 3 )
            goto LABEL_11;
        }
        if ( *(_DWORD *)(v5[2] + 8) )
        {
          v9 = *(_DWORD *)(v5[2] + 8);
          if ( QTask_IsQTaskTypeDerived(*(_WORD *)(v9 + 36), Human_eQTaskType) )
          {
            BoneDynCubeObj_GetBonePosition(
              (struct BoneDynCubeObj_s *)igi2_frame.ptNetManagerGameMessage,
              (struct real32x3_t *)v9,
              *(_DWORD *)(v9 + 1432));
            v1 = ptQTask;
          }
          else
          {
            qmemcpy(igi2_frame.ptNetManagerGameMessage, (void *)(v9 + 40), sizeof(igi2_frame.ptNetManagerGameMessage));
          }
          v10 = igi2_frame.ptNetManagerGameMessage[0] - igi2_frame.v52[0];
          v11 = igi2_frame.ptNetManagerGameMessage[1] - igi2_frame.v52[1];
          igi2_frame.ptNetManagerGameMessage[0] = igi2_frame.v53[6] * (igi2_frame.ptNetManagerGameMessage[2] - igi2_frame.v52[2])
                                     + igi2_frame.v53[3] * (igi2_frame.ptNetManagerGameMessage[1] - igi2_frame.v52[1])
                                     + igi2_frame.v53[0] * (igi2_frame.ptNetManagerGameMessage[0] - igi2_frame.v52[0]);
          igi2_frame.ptNetManagerGameMessage[1] = igi2_frame.v53[7] * (igi2_frame.ptNetManagerGameMessage[2] - igi2_frame.v52[2])
                                     + igi2_frame.v53[4] * (igi2_frame.ptNetManagerGameMessage[1] - igi2_frame.v52[1])
                                     + igi2_frame.v53[1] * v10;
          igi2_frame.ptNetManagerGameMessage[2] = igi2_frame.v53[8] * (igi2_frame.ptNetManagerGameMessage[2] - igi2_frame.v52[2]) + igi2_frame.v53[5] * v11 + igi2_frame.v53[2] * v10;
          qmemcpy(&igi2_frame.vValue, igi2_frame.ptNetManagerGameMessage, sizeof(igi2_frame.vValue));
          igi2_frame.v44 = GameFunctions_CalcGamma(igi2_frame.vValue);
          v12 = sqrt(
                  igi2_frame.ptNetManagerGameMessage[1] * igi2_frame.ptNetManagerGameMessage[1]
                + igi2_frame.ptNetManagerGameMessage[2] * igi2_frame.ptNetManagerGameMessage[2]
                + igi2_frame.ptNetManagerGameMessage[0] * igi2_frame.ptNetManagerGameMessage[0]);
          if ( v12 <= 0.10000000149011612 )
          {
            igi2_frame.v45 = 0.0;
          }
          else
          {
            *((float *)&igi2_frame.vValue.vZ + 1) = igi2_frame.ptNetManagerGameMessage[2] / v12;
            igi2_frame.v45 = Real32_Asin(*((float *)&igi2_frame.vValue.vZ + 1));
          }
          igi2_frame.v48 = 1;
          break;
        }
LABEL_11:
        v5 = v6;
        v6 = (_DWORD *)*v6;
        if ( v6 )
          continue;
        break;
      }
    }
    if ( *(_DWORD *)&v1[11].eQTaskType )
    {
      if ( !igi2_frame.v48 )
      {
        v1[11].ptParent = (struct QTask_s *)90;
        goto LABEL_25;
      }
    }
    else if ( !igi2_frame.v48 )
    {
      goto LABEL_25;
    }
    v1[11].ptParent = nullptr;
LABEL_25:
    ptParent = v1[11].ptParent;
    if ( ptParent )
    {
      ptHead = v1[12].tQTaskChildren.ptHead;
      igi2_frame.v45 = *(float *)&v1[12].ptPrev;
      igi2_frame.v44 = *(float *)&ptHead;
      v1[11].ptParent = (struct QTask_s *)((char *)ptParent - 1);
    }
    else
    {
      v15 = igi2_frame.v44;
      *(float *)&v1[12].ptPrev = igi2_frame.v45;
      *(float *)&v1[12].tQTaskChildren.ptHead = v15;
    }
    ptTail = (float *)v1[11].tQTaskChildren.ptTail;
    if ( ptTail[10] > 6.2831854820251465 )
    {
      v17 = igi2_frame.v44 - *(float *)&v1[11].tQTaskRefList.ptMiddle;
      if ( v17 < 0.0 )
        v17 = -v17;
      if ( v17 > 3.1415927410125732 )
        igi2_frame.v44 = igi2_frame.v44 + 6.2831854820251465;
    }
    v18 = igi2_frame.v45 - *(float *)&v1[11].tQTaskRefList.ptHead;
    v19 = -ptTail[12];
    igi2_frame.v49 = v19;
    if ( v19 <= v18 )
    {
      if ( v18 > ptTail[12] )
        v18 = ptTail[12];
    }
    else
    {
      v18 = igi2_frame.v49;
    }
    *(float *)&v1[11].tQTaskRefList.ptHead = v18 + *(float *)&v1[11].tQTaskRefList.ptHead;
    v20 = igi2_frame.v44 - *(float *)&v1[11].tQTaskRefList.ptMiddle;
    v21 = -ptTail[13];
    igi2_frame.v49 = v21;
    if ( v21 <= v20 )
    {
      if ( v20 > ptTail[13] )
        v20 = ptTail[13];
    }
    else
    {
      v20 = igi2_frame.v49;
    }
    v22 = v20 + *(float *)&v1[11].tQTaskRefList.ptMiddle;
    *(float *)&v1[11].tQTaskRefList.ptMiddle = v22;
    if ( v22 <= 3.1415927410125732 )
    {
      if ( v22 < -3.1415927410125732 )
        *(float *)&v1[11].tQTaskRefList.ptMiddle = v22 + 3.1415927410125732 + 3.1415927410125732;
    }
    else
    {
      *(float *)&v1[11].tQTaskRefList.ptMiddle = v22 - 3.1415927410125732 - 3.1415927410125732;
    }
    AIStationaryGun_LimitRotation(v1);
    v23 = *(float *)&v1[11].tQTaskRefList.ptHead - igi2_frame.v45;
    if ( v23 < 0.0 )
      v23 = -v23;
    igi2_frame.v47 = v23;
    v24 = *(float *)&v1[11].tQTaskRefList.ptMiddle - igi2_frame.v44;
    if ( v24 < 0.0 )
      v24 = -v24;
    igi2_frame.v49 = v24;
    AIStationaryGun_SetGunPosAndOrientation(v1);
    if ( !igi2_frame.v48 )
      goto LABEL_62;
    if ( igi2_frame.v47 >= 0.0872664675116539 || (igi2_frame.v46 = 1, igi2_frame.v49 >= 0.0872664675116539) )
      igi2_frame.v46 = 0;
    if ( Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER && Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle )
      igi2_frame.v46 = 0;
    v25 = v1[12].tQTaskChildren.ptTail;
    if ( v25[1].tQTaskChildren.ptTail == (struct QTask_s *)4 )
    {
      Weapon_SendWeaponEvent(v25, 0x5753524Cu, igi2_frame.ptNetManagerGameMessage, 20);
    }
    else
    {
      if ( !igi2_frame.v46 )
      {
LABEL_62:
        if ( v1[12].ptNext && !igi2_frame.v46 || v1[12].tQTaskChildren.ptTail[1].tQTaskChildren.ptTail == (struct QTask_s *)2 )
        {
          v26 = v1[12].tQTaskChildren.ptTail;
          v26[2].ptParent = (struct QTask_s *)1;
          v26[1].tQTaskChildren.ptTail = nullptr;
        }
        v27 = v1[11].tQTaskChildren.ptTail;
        v28 = igi2_frame.v45;
        if ( igi2_frame.v45 >= (double)*(float *)&v27->eQTaskType )
        {
          if ( v28 > *(float *)&v27->ptParent )
            v28 = *(float *)&v27->ptParent;
        }
        else
        {
          v28 = *(float *)&v27->eQTaskType;
        }
        v29 = -*(float *)&v27[1].ptNext;
        if ( igi2_frame.v44 >= v29 )
        {
          if ( igi2_frame.v44 > (double)*(float *)&v27[1].ptNext )
            igi2_frame.v44 = *(float *)&v27[1].ptNext;
        }
        else
        {
          igi2_frame.v44 = v29;
        }
        v30 = *(float *)&v1[11].tQTaskRefList.ptHead - v28;
        if ( v30 < 0.0 )
          v30 = -v30;
        igi2_frame.v47 = v30;
        v31 = *(float *)&v1[11].tQTaskRefList.ptMiddle - igi2_frame.v44;
        if ( v31 < 0.0 )
          v31 = -v31;
        if ( igi2_frame.v47 > 0.03490658476948738 || v31 > 0.03490658476948738 )
        {
          v32 = v1[11].tQTaskRefList.ptTail;
          if ( v32 && (pxObject = (unsigned __int16 *)v32->pxObject) != nullptr )
          {
            ((void (__cdecl *)(unsigned __int16 *, double *))QTask_aatQTaskFinalEvent[SoundSys_eSetPositionQTaskEvent][pxObject[18]].pfHandler)(
              pxObject,
              igi2_frame.v52);
          }
          else
          {
            v34 = SoundSys_NewSoundFn(v1, (char *)&v27[1].tQTaskChildren.ptTail);
            v35 = v34;
            if ( v34 )
            {
              ((void (__cdecl *)(struct QTask_s *, double *))QTask_aatQTaskFinalEvent[SoundSys_eSetPositionQTaskEvent][v34->eQTaskType].pfHandler)(
                v34,
                igi2_frame.v52);
              v1[11].tQTaskRefList.ptTail = QTask_NewQTaskRef(v35);
            }
          }
        }
        else
        {
          QTask_DeleteQTaskAndQTaskRefSafe(&v1[11].tQTaskRefList.ptTail);
        }
        Weapon_UpdateStatus(v1[12].tQTaskChildren.ptTail);
        v36 = (struct QTask_s *)igi2_frame.v46;
        *(_DWORD *)&v1[11].eQTaskType = igi2_frame.v48;
        v1[12].ptNext = v36;
        v37 = v1->tQTaskChildren.ptHead;
        if ( v37->ptNext )
        {
          v38 = (int)v37;
          if ( v37 )
          {
            v39 = QTask_nProtectedQTaskStackOffset;
            do
            {
              if ( *(_DWORD *)v38 )
                v40 = **(_DWORD **)v38 != 0 ? *(struct QTask_s **)v38 : nullptr;
              else
                v40 = nullptr;
              QTask_atProtectedQTaskStack[v39].ptQTask = v40;
              v41 = (void (__cdecl *)(int))QTask_aatQTaskFinalEvent[1][*(unsigned __int16 *)(v38 + 36)].pfHandler;
              v42 = v39 + 1;
              QTask_nProtectedQTaskStackOffset = v42;
              if ( v41 )
              {
                v41(v38);
                v42 = QTask_nProtectedQTaskStackOffset;
              }
              v38 = dword_849C7DC[v42];
              v39 = v42 - 1;
              QTask_nProtectedQTaskStackOffset = v39;
            }
            while ( v38 );
          }
        }
        return;
      }
      Weapon_Fire(v1[12].tQTaskChildren.ptTail, 0);
    }
    if ( igi2_frame.v46 )
      *(float *)&v1[12].tQTaskChildren.ptMiddle = *(float *)&v1[11].tQTaskChildren.ptTail[3].ptNext
                                                + *(float *)&v1[12].tQTaskChildren.ptMiddle;
    goto LABEL_62;
  }
}

// source: j/0/weapons/aistationarygun.c:853  [anchor-mhash]
void __cdecl AIStationaryGun_PrepareDeleteHandler(struct QTask_s *ptQTask)
{
  struct DynCubeObj_s *ptHead; // edi

  ptHead = (struct DynCubeObj_s *)ptQTask[12].tQTaskRefList.ptHead;
  if ( ptHead )
    SectorObject_RemoveInteriorDynCubeObj(ptHead);
}

// source: j/0/weapons/aistationarygun.c:872  [anchor-mhash]
void __cdecl AIStationaryGun_DeleteHandler(struct QTask_s *ptQTask)
{
  QTask_DeleteQTaskAndQTaskRefSafe(&ptQTask[11].tQTaskRefList.ptTail);
  World_RemoveDynCubeObj((struct World_s *)ptQTask[2].ptParent, (struct DynCubeObj_s *)ptQTask);
}

// source: j/0/weapons/aistationarygun.c:895  [size]
void __cdecl AIStationaryGun_GetMagicObjParameterSizeHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = 128;
}

// source: j/0/weapons/aistationarygun.c:911  [size]
void __cdecl AIStationaryGun_AILineOfSightHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_BYTE *)pxContext = 0;
}

// source: j/0/weapons/aistationarygun.c:963  [anchor-mhash]
void __cdecl AIStationaryGun_GetParentParametersHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct real64x3_t tReal64x3; // [esp+10h] [ebp-18h] BYREF

  GameFunctions_GetMagicVertex(&tReal64x3, (struct QTask_s *)ptQTask[12].tQTaskRefList.ptHead, 2);
  qmemcpy(pxContext, &tReal64x3, 0x18u);
  qmemcpy((char *)pxContext + 24, &ptQTask[10].tQTaskChildren.ptTail, 0x28u);
}

// source: j/0/weapons/aistationarygun.c:987  [size]
void __cdecl AIStationaryGun_GetWeaponObjectHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *((_DWORD *)pxContext + 2) = 0;
  *(_DWORD *)pxContext = ptQTask[12].tQTaskRefList.ptHead;
}

// source: j/0/weapons/aistationarygun.c:1009  [size]
unsigned __int16 __cdecl AIStationaryGun_GetQTaskType()
{
  return AIStationaryGun_eQTaskType;
}

// source: j/0/weapons/aistationarygun.c:1025  [anchor-mhash]
void __cdecl AIStationaryGun_Open()
{
  unsigned __int16 v0; // si
  __int16 v1; // ax
  _DWORD *v2; // esi

  v0 = QTask_NewQTaskType("AIStationaryGun", 504, RigidMagicObj_eQTaskType, 0, 0);
  AIStationaryGun_eQTaskType = v0;
  QTask_LinkQTaskEventHandlerFn(v0, 0, AIStationaryGun_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 1, AIStationaryGun_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 2, AIStationaryGun_DeleteHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, Attach_eUpdateAttachmentEvent, AIStationaryGun_UpdateAttachmentHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    MagicObj_eGetMagicObjParameterSizeEvent,
    (void (__cdecl *)(struct QTask_s *, void *))AIStationaryGun_GetMagicObjParameterSizeHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    AIDetection_eLineOfSightQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))AIStationaryGun_AILineOfSightHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    ParameterList_eUpdateInternalDataQTaskEvent,
    AIStationaryGun_UpdateInternalDataHandler);
  QTask_LinkQTaskEventHandlerFn(v0, Weapon_eGetParentParametersQTaskEvent, AIStationaryGun_GetParentParametersHandler);
  v1 = SoundSys_eUpdateParameterListQTaskEvent;
  if ( SoundSys_eUpdateParameterListQTaskEvent == 512 )
  {
    v1 = QTask_NewQTaskEventFn(0, (char *)&g_zFileName.nRealFadeCount);
    v0 = AIStationaryGun_eQTaskType;
    SoundSys_eUpdateParameterListQTaskEvent = v1;
  }
  QTask_LinkQTaskEventHandlerFn(v0, v1, AIStationaryGun_SoundUpdateParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(v0, Weapon_eGetWeaponObjectEvent, AIStationaryGun_GetWeaponObjectHandler);
  QTask_LinkQTaskEventHandlerFn(v0, Serialize_eDeSerializeDoneQTaskEvent, AIStationaryGun_DeSerializeDoneHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, Level_eUpdateInternalDataAfterLoadEvent, sub_505750);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 3, AIStationaryGun_PrepareDeleteHandler);
  Symbol_Register(
    "TASKTYPE_AISTATIONARYGUN",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)v0,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  v2 = Mem_AllocFn(18444, 4);
  v2[1] = 0;
  *v2 = 0;
  v2[4610] = "TASKTYPE_AISTATIONARYGUN";
  Wildcard_CreateNFA("TASKTYPE_AISTATIONARYGUN", v2 + 2, (char *)v2 + 10248);
  List_AddTail(v2, (int)&MagicObjConfig_tTaskTypeEnumList);
}

// source: j/0/weapons/aistationarygun.c:1063  [size]
void __cdecl AIStationaryGun_Close()
{
  QTask_DeleteQTaskEvent(AIStationaryGun_eGetGunParametersEvent);
  QTask_DeleteQTaskType(AIStationaryGun_eQTaskType);
}

// source: j/0/weapons/aistationarygun.c:1081  [size]
__int16 __cdecl AIStationaryGun_GetGunParametersEvent()
{
  __int16 result; // ax

  result = AIStationaryGun_eGetGunParametersEvent;
  if ( AIStationaryGun_eGetGunParametersEvent == 512 )
  {
    result = QTask_NewQTaskEventFn(0, "AIStationaryGunGetGunParams");
    AIStationaryGun_eGetGunParametersEvent = result;
  }
  return result;
}

// source: j/0/weapons/aistationarygun.c:1099  [anchor-mhash]
struct real64x3_t *__cdecl AIStationaryGun_GetMuzzlePosition(
        struct QTask_s *ptQTask,
        struct real64x3_t *ptPos)
{
  struct QTask_s *ptHead; // edx

  ptHead = (struct QTask_s *)ptQTask[12].tQTaskRefList.ptHead;
  if ( ptHead )
    return GameFunctions_GetMagicVertex(ptPos, ptHead, 2);
  qmemcpy(ptPos, &ptQTask[9].ptParent, sizeof(struct real64x3_t));
  return ptPos;
}

// source: j/0/weapons/aistationarygun.c:1123  [size]
struct QTask_s *__cdecl AIStationaryGun_GetGunOrientation(
        struct QTask_s *ptQTask,
        struct real32x9_t *ptOrientation)
{
  qmemcpy(ptOrientation, &ptQTask[10].tQTaskChildren.ptTail, sizeof(struct real32x9_t));
  return ptQTask;
}
