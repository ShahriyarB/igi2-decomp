/* j/0/effects/smoke.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/effects/smoke.c:229  [anchor-callee]
struct Smoke_s *__cdecl Smoke_CalcRelativePosAndOrientation(struct Smoke_s *ptSmoke)
{
  struct real64x3_t *ptParentPos; // edx
  struct real32x9_t *ptParentOrientation; // ecx
  double vX; // st7
  double v4; // st6
  double v5; // st5
  float vZ; // esi
  float v7; // ecx
  double v8; // rt0
  double v9; // st5
  float v10; // [esp+0h] [ebp-38h]
  float Real32x9_Invert_tTemp_12; // [esp+1Ch] [ebp-1Ch]
  float Real32x9_Invert_tTemp_16; // [esp+20h] [ebp-18h]
  float Real32x9_Invert_tTemp_20; // [esp+24h] [ebp-14h]
  float Real32x9_Invert_tTemp_24; // [esp+28h] [ebp-10h]
  struct real32x3_t struct_real32x3_t; // 0:^8.12

  ptParentPos = ptSmoke->tAttachContext.ptParentPos;
  if ( ptParentPos )
  {
    ptParentOrientation = ptSmoke->tAttachContext.ptParentOrientation;
    vX = ptParentOrientation->tX.vX;
    v4 = ptParentOrientation->tY.vX;
    v5 = ptParentOrientation->tZ.vX;
    Real32x9_Invert_tTemp_12 = ptParentOrientation->tX.vY;
    Real32x9_Invert_tTemp_16 = ptParentOrientation->tY.vY;
    Real32x9_Invert_tTemp_20 = ptParentOrientation->tZ.vY;
    Real32x9_Invert_tTemp_24 = ptParentOrientation->tX.vZ;
    vZ = ptParentOrientation->tY.vZ;
    v7 = ptParentOrientation->tZ.vZ;
    ptSmoke->tRelativePos.vX = ptSmoke->tPos.vX - ptParentPos->vX;
    ptSmoke->tRelativePos.vY = ptSmoke->tPos.vY - ptParentPos->vY;
    v10 = ptSmoke->tPos.vZ - ptParentPos->vZ;
    v8 = v5;
    v9 = v4 * ptSmoke->tRelativePos.vY;
    ptSmoke->tRelativePos.vZ = v10;
    struct_real32x3_t.vX = v9 + v10 * v8 + vX * ptSmoke->tRelativePos.vX;
    struct_real32x3_t.vY = Real32x9_Invert_tTemp_16 * ptSmoke->tRelativePos.vY
                         + v10 * Real32x9_Invert_tTemp_20
                         + Real32x9_Invert_tTemp_12 * ptSmoke->tRelativePos.vX;
    struct_real32x3_t.vZ = vZ * ptSmoke->tRelativePos.vY
                         + v10 * v7
                         + Real32x9_Invert_tTemp_24 * ptSmoke->tRelativePos.vX;
    ptSmoke->tRelativePos = struct_real32x3_t;
    return (struct Smoke_s *)LODWORD(struct_real32x3_t.vZ);
  }
  return ptSmoke;
}

// source: j/0/effects/smoke.c:305  [anchor-mhash]
void __cdecl Smoke_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ptQTask[2].ptParent = nullptr;
  *(_DWORD *)&ptQTask[2].eQTaskType = 0;
  ptQTask[3].ptNext = nullptr;
  ptQTask[3].ptPrev = nullptr;
  ptQTask[3].tQTaskChildren.ptHead = nullptr;
  ptQTask[3].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[2].tQTaskChildren.ptHead = nullptr;
  ptQTask[2].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[2].tQTaskChildren.ptTail = nullptr;
  ptQTask[2].tQTaskRefList.ptHead = nullptr;
  ptQTask[2].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[2].tQTaskRefList.ptTail = nullptr;
  LOBYTE(ptQTask[1].tQTaskRefList.ptTail) = 0;
  ptQTask[7].tQTaskRefList.ptHead = nullptr;
  ptQTask[4].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[4].tQTaskChildren.ptTail = nullptr;
  ptQTask[4].tQTaskRefList.ptTail = (struct QReference_s *)1083179008;
  ptQTask[4].ptParent = (struct QTask_s *)1086324736;
  *(_DWORD *)&ptQTask[4].eQTaskType = 1061752795;
  ptQTask[5].tQTaskChildren.ptHead = nullptr;
  ptQTask[5].tQTaskChildren.ptMiddle = (struct QTask_s *)1077805056;
  ptQTask[5].tQTaskChildren.ptTail = nullptr;
  ptQTask[7].tQTaskRefList.ptMiddle = (struct QReference_s *)100;
  ptQTask[7].ptParent = (struct QTask_s *)1065353216;
  ptQTask[7].tQTaskRefList.ptTail = (struct QReference_s *)1056964608;
  ptQTask[8].tQTaskChildren.ptHead = nullptr;
  ptQTask[8].tQTaskChildren.ptMiddle = (struct QTask_s *)1076538027;
  ptQTask[4].tQTaskRefList.ptHead = (struct QReference_s *)1056964608;
  ptQTask[8].tQTaskChildren.ptTail = (struct QTask_s *)3;
  ptQTask[8].tQTaskRefList.ptHead = nullptr;
  ptQTask[8].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[8].tQTaskRefList.ptTail = (struct QReference_s *)1065353216;
  ptQTask[8].ptParent = (struct QTask_s *)1065353216;
  LOBYTE(ptQTask[9].tQTaskChildren.ptMiddle) = 0;
  BYTE1(ptQTask[9].tQTaskChildren.ptMiddle) = 0;
  ptQTask[4].tQTaskRefList.ptMiddle = nullptr;
  BYTE2(ptQTask[9].tQTaskChildren.ptMiddle) = 0;
  *(_DWORD *)&ptQTask[8].eQTaskType = 1120403456;
  ptQTask[1].ptParent = nullptr;
  *(_DWORD *)&ptQTask[1].eQTaskType = 0;
  ptQTask[2].ptNext = nullptr;
  ptQTask[2].ptPrev = nullptr;
  *(_DWORD *)&ptQTask[7].eQTaskType = 0x40000000;
  ptQTask[8].ptNext = (struct QTask_s *)0x40000000;
  ptQTask[8].ptPrev = (struct QTask_s *)0x40000000;
  ptQTask[5].tQTaskRefList.ptHead = nullptr;
  ptQTask[5].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[5].tQTaskRefList.ptTail = nullptr;
  ptQTask[7].tQTaskChildren.ptTail = nullptr;
  Smoke_tRandomState.anRandom[0] = -923067897;
  Smoke_tRandomState.anRandom[1] = 971667286;
  Smoke_tRandomState.anRandom[2] = 2146516173;
}

// source: j/0/effects/smoke.c:408  [size]
void __cdecl Smoke_RegisterScriptSymbolsHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { char zName[64]; };
    struct { char igi2_o1[64]; char zTemp[128]; };
    char igi2_extent[192];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)

  if ( !LOBYTE(ptQTask[1].tQTaskRefList.ptTail) )
  {
    LOBYTE(ptQTask[1].tQTaskRefList.ptTail) = 1;
    Level_GetUniqueQTaskNameFromTask(igi2_frame.zName, ptQTask);
    sprintf(igi2_frame.zTemp, "%s.vGenerateFactor", igi2_frame.zName);
    Symbol_Register(
      igi2_frame.zTemp,
      Script_Float,
      &ptQTask[5].tQTaskChildren,
      8,
      QSCRIPT_SYMBOLCLASS_VARIABLE,
      QSCRIPT_SYMBOLTYPE_FLOAT,
      QSCRIPT_SYMBOLLIFESPAN_FINITE);
  }
}

// source: j/0/effects/smoke.c:438  [size]
void __cdecl Smoke_RemoveScriptSymbolsHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { char zName[64]; };
    struct { char igi2_o1[64]; char zTemp[128]; };
    char igi2_extent[192];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)

  if ( LOBYTE(ptQTask[1].tQTaskRefList.ptTail) )
  {
    Level_GetUniqueQTaskNameFromTask(igi2_frame.zName, ptQTask);
    LOBYTE(ptQTask[1].tQTaskRefList.ptTail) = 0;
    sprintf(igi2_frame.zTemp, "%s.vGenerateFactor", igi2_frame.zName);
    Symbol_Remove(igi2_frame.zTemp);
  }
}

// source: j/0/effects/smoke.c:470  [anchor-mhash]
void __cdecl Smoke_DeleteHandler(struct QTask_s *ptQTask)
{
  int v1; // ecx
  struct QReference_s *v2; // eax
  void (__cdecl *pfHandler)(struct QTask_s *); // eax
  struct QReference_s *ptHead; // eax

  v1 = 0;
  while ( 1 )
  {
    v2 = Level_atLevelQTaskID[v1];
    if ( v2 )
    {
      if ( v2->pxObject == ptQTask )
        break;
    }
    if ( ++v1 >= 4096 )
      goto LABEL_9;
  }
  if ( v1 >= 0 )
  {
    pfHandler = (void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[Level_eRemoveLevelScriptSymbolsEvent][ptQTask->eQTaskType].pfHandler;
    if ( pfHandler )
      pfHandler(ptQTask);
  }
LABEL_9:
  ptHead = ptQTask[7].tQTaskRefList.ptHead;
  if ( ptHead )
  {
    QReference_Delete(ptHead, &QTask_tQTaskRefPool);
    ptQTask[7].tQTaskRefList.ptHead = nullptr;
  }
  Level_DeinitLevelExpression((struct LevelExpression_s *)&ptQTask[5].tQTaskRefList);
}

// source: j/0/effects/smoke.c:505  [size]
void __cdecl Smoke_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = Smoke_ptParameterList;
}

// source: j/0/effects/smoke.c:521  [anchor-caller]
void __cdecl Smoke_RunHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { float vMaxAngle; };
    struct { char igi2_o1[4]; float vMinVel; };
    struct { char igi2_o2[12]; float vIntensity; };
    struct { char igi2_o3[56]; struct real64x3_t tMove; };
    char igi2_extent[80];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QReference_s *ptHead; // eax
  struct QTask_s *v3; // ecx
  int v4; // edx
  struct QTask_s *v5; // eax
  void (__cdecl *pfHandler)(struct QTask_s *); // eax
  int v7; // edx
  double v8; // st7
  unsigned int v9; // ecx
  unsigned int v10; // edx
  unsigned int v11; // eax
  double v12; // st7
  int v13; // ecx
  int v14; // edx
  long double v15; // st7
  double v16; // st6
  double v17; // st6
  struct QTask_s *ptMiddle; // edx
  struct QTask_s *ptQTaska = *(struct QTask_s * *)&ptQTask; // [esp+54h] [ebp+4h] ARGSLOT

  ptHead = ptQTask[7].tQTaskRefList.ptHead;
  if ( ptHead )
  {
    ptQTaska = (struct QTask_s *)ptHead->pxObject;
    if ( ptQTaska )
    {
      if ( BYTE1(ptQTask[9].tQTaskChildren.ptMiddle) && LOBYTE(ptQTask[9].tQTaskChildren.ptMiddle) )
      {
        igi2_frame.tMove.vX = *(double *)&ptQTask[2].ptParent - *(double *)&ptQTask[3].tQTaskChildren.ptTail;
        igi2_frame.tMove.vY = *(double *)&ptQTask[3].ptNext - *(double *)&ptQTask[3].tQTaskRefList.ptMiddle;
        igi2_frame.tMove.vZ = *(double *)&ptQTask[3].tQTaskChildren.ptHead - *(double *)&ptQTask[3].ptParent;
        Particle2DDynCubeObj_MoveParticles(ptQTaska, &igi2_frame.tMove);
      }
      qmemcpy(&ptQTask[3].tQTaskChildren.ptTail, &ptQTask[2].ptParent, 0x18u);
      v3 = ptQTask->tQTaskChildren.ptHead;
      BYTE1(ptQTask[9].tQTaskChildren.ptMiddle) = 1;
      if ( v3->ptNext && v3 )
      {
        v4 = QTask_nProtectedQTaskStackOffset;
        do
        {
          if ( v3->ptNext )
            v5 = v3->ptNext->ptNext != nullptr ? v3->ptNext : nullptr;
          else
            v5 = nullptr;
          QTask_atProtectedQTaskStack[v4].ptQTask = v5;
          pfHandler = (void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[1][v3->eQTaskType].pfHandler;
          v7 = v4 + 1;
          QTask_nProtectedQTaskStackOffset = v7;
          if ( pfHandler )
          {
            pfHandler(v3);
            v7 = QTask_nProtectedQTaskStackOffset;
          }
          v3 = (struct QTask_s *)dword_849C7DC[v7];
          v4 = v7 - 1;
          QTask_nProtectedQTaskStackOffset = v4;
        }
        while ( v3 );
      }
      if ( ptQTask[5].tQTaskRefList.ptHead
        && ptQTask[5].tQTaskRefList.ptMiddle->ptNext
        && ptQTask[5].tQTaskRefList.ptTail )
      {
        *(double *)&ptQTask[5].tQTaskChildren.ptHead = Level_RunLevelExpression(
                                                         (struct LevelExpression_s *)&ptQTask[5].tQTaskRefList,
                                                         ptQTask);
      }
      if ( *(double *)&ptQTask[5].tQTaskChildren.ptHead > 0.0 && ptQTask[1].ptParent )
        Smoke_DoDamage((struct Smoke_s *)ptQTask);
      v8 = *(double *)&ptQTask[5].tQTaskChildren.ptHead + *(float *)&ptQTask[5].tQTaskChildren.ptTail;
      *(float *)&ptQTask[5].tQTaskChildren.ptTail = v8;
      if ( v8 > 30.0 )
      {
        do
        {
          v9 = (Smoke_tRandomState.anRandom[0] >> 7) ^ Smoke_tRandomState.anRandom[2];
          v10 = v9 ^ Smoke_tRandomState.anRandom[1];
          v11 = (v9 ^ Smoke_tRandomState.anRandom[1]) + Smoke_tRandomState.anRandom[0];
          v12 = (double)(unsigned __int16)((v9 ^ LOWORD(Smoke_tRandomState.anRandom[1]))
                                         + LOWORD(Smoke_tRandomState.anRandom[0]));
          v13 = (v11 >> 7) ^ v9;
          v14 = v13 ^ v10;
          v15 = v12 * 0.0000152587890625 * 6.2831854820251465;
          Smoke_tRandomState.anRandom[2] = v13;
          Smoke_tRandomState.anRandom[1] = v14;
          Smoke_tRandomState.anRandom[0] = v14 + v11;
          v16 = (double)(unsigned __int16)(v14 + v11) * 0.0000152587890625 * *(float *)&ptQTask[5].ptNext;
          Smoke_tRandomState.anRandom[2] = ((v14 + v11) >> 7) ^ v13;
          v17 = v16 * 4096.0;
          Smoke_tRandomState.anRandom[1] = Smoke_tRandomState.anRandom[2] ^ v14;
          Smoke_tRandomState.anRandom[0] = (Smoke_tRandomState.anRandom[2] ^ v14) + v14 + v11;
          ptMiddle = ptQTask[3].tQTaskChildren.ptMiddle;
          LODWORD(igi2_frame.tMove.vZ) = ptQTask[3].tQTaskChildren.ptHead;
          HIDWORD(igi2_frame.tMove.vZ) = ptMiddle;
          igi2_frame.tMove.vX = cos(v15) * v17 + *(double *)&ptQTask[2].ptParent;
          igi2_frame.tMove.vY = sin(v15) * v17 + *(double *)&ptQTask[3].ptNext;
          igi2_frame.vIntensity = ((double)LOWORD(Smoke_tRandomState.anRandom[0])
                      * 0.0000152587890625
                      * (*(float *)&ptQTask[8].tQTaskRefList.ptHead - *(float *)&ptQTask[8].tQTaskRefList.ptMiddle)
                      + *(float *)&ptQTask[8].tQTaskRefList.ptMiddle)
                     * 0.03333333507180214;
          igi2_frame.vMinVel = *(float *)&ptQTask[4].tQTaskRefList.ptTail * 136.0;
          igi2_frame.vMaxAngle = *(float *)&ptQTask[4].ptParent * 136.0;
          Particle2DDynCubeObj_AddConeParticle(
            ptQTaska,
            &igi2_frame.tMove,
            (struct real32x3_t *)&ptQTask[4],
            *(float *)&ptQTask[4].eQTaskType,
            igi2_frame.vMaxAngle,
            igi2_frame.vMinVel,
            *(float *)&ptQTask[8].tQTaskRefList.ptTail,
            igi2_frame.vIntensity,
            0.0,
            1.0,
            (__int64)(*(float *)&ptQTask[7].tQTaskRefList.ptTail * 30.0),
            (__int64)(*(float *)&ptQTask[7].ptParent / *(float *)&ptQTask[8].tQTaskRefList.ptTail * 30.0));
          *(float *)&ptQTask[5].tQTaskChildren.ptTail = *(float *)&ptQTask[5].tQTaskChildren.ptTail - 30.0;
        }
        while ( *(float *)&ptQTask[5].tQTaskChildren.ptTail > 30.0 );
      }
    }
  }
}

// source: j/0/effects/smoke.c:649  [size]
void __cdecl Smoke_RegisterHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *ptHead; // eax
  int v3; // edx
  struct QTask_s *v4; // ecx
  void (__cdecl *pfHandler)(struct QTask_s *, void *); // ecx
  int v6; // edx

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
      pfHandler = (void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[DynCubeObj_eDynCubeObjRegisterQTaskEvent][ptHead->eQTaskType].pfHandler;
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
}

// source: j/0/effects/smoke.c:667  [size]
void __cdecl Smoke_RemoveHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *ptHead; // eax
  int v3; // edx
  struct QTask_s *v4; // ecx
  void (__cdecl *pfHandler)(struct QTask_s *, void *); // ecx
  int v6; // edx

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
}

// source: j/0/effects/smoke.c:681  [size]
void __cdecl Smoke_UpdateAttachmentHandler(struct QTask_s *ptQTask)
{
  float *ptMiddle; // ecx
  double v2; // st7
  double v3; // st6
  double v4; // st5
  double v5; // st4
  double *ptHead; // ecx
  struct QTask_s *v7; // eax
  struct QTask_s *v8; // ecx
  int v9; // edx
  struct QTask_s *v10; // eax
  int v11; // esi
  void (__cdecl *pfHandler)(struct QTask_s *); // eax
  int v13; // edx
  float Real32x3_Rotate_tTemp_8; // [esp+8h] [ebp-4h]

  ptMiddle = (float *)ptQTask[1].tQTaskChildren.ptMiddle;
  v2 = ptMiddle[2] * *(float *)&ptQTask[9].tQTaskChildren.ptHead
     + ptMiddle[1] * *(float *)&ptQTask[9].ptPrev
     + *(float *)&ptQTask[9].ptNext * *ptMiddle;
  v3 = ptMiddle[5] * *(float *)&ptQTask[9].tQTaskChildren.ptHead
     + ptMiddle[4] * *(float *)&ptQTask[9].ptPrev
     + ptMiddle[3] * *(float *)&ptQTask[9].ptNext;
  v4 = ptMiddle[8] * *(float *)&ptQTask[9].tQTaskChildren.ptHead + ptMiddle[7] * *(float *)&ptQTask[9].ptPrev;
  v5 = ptMiddle[6];
  ptHead = (double *)ptQTask[1].tQTaskChildren.ptHead;
  Real32x3_Rotate_tTemp_8 = v4 + v5 * *(float *)&ptQTask[9].ptNext;
  *(double *)&ptQTask[2].ptParent = v2 + *ptHead;
  *(double *)&ptQTask[3].ptNext = v3 + ptHead[1];
  *(double *)&ptQTask[3].tQTaskChildren.ptHead = Real32x3_Rotate_tTemp_8 + ptHead[2];
  v7 = ptQTask->tQTaskChildren.ptHead;
  if ( v7->ptNext )
  {
    v8 = ptQTask->tQTaskChildren.ptHead;
    if ( v7 )
    {
      v9 = QTask_nProtectedQTaskStackOffset;
      do
      {
        if ( v8->ptNext )
          v10 = v8->ptNext->ptNext != nullptr ? v8->ptNext : nullptr;
        else
          v10 = nullptr;
        v11 = Attach_eUpdateAttachmentEvent;
        QTask_atProtectedQTaskStack[v9].ptQTask = v10;
        pfHandler = (void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[v11][v8->eQTaskType].pfHandler;
        v13 = v9 + 1;
        QTask_nProtectedQTaskStackOffset = v13;
        if ( pfHandler )
        {
          pfHandler(v8);
          v13 = QTask_nProtectedQTaskStackOffset;
        }
        v8 = (struct QTask_s *)dword_849C7DC[v13];
        v9 = v13 - 1;
        QTask_nProtectedQTaskStackOffset = v9;
      }
      while ( v8 );
    }
  }
}

// source: j/0/effects/smoke.c:728  [anchor-mhash]
void __cdecl Smoke_ParentChangedHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *ptHead; // ebx

  ptHead = ptQTask[1].tQTaskChildren.ptHead;
  memset(&ptQTask[1], 0, 0x1Cu);
  QTask_TriggerQTaskEventParent(ptQTask, Attach_eAttachEvent, &ptQTask[1]);
  if ( ptHead != ptQTask[1].tQTaskChildren.ptHead )
    Smoke_CalcRelativePosAndOrientation((struct Smoke_s *)ptQTask);
}

// source: j/0/effects/smoke.c:758  [size]
void __cdecl Smoke_ParticleCollisionCallback(struct Particle2DCollisionContext_t *ptContext)
{
  ;
}

// source: j/0/effects/smoke.c:771  [anchor-callee]
void __cdecl Smoke_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { float nAnimDelta; };
    struct { char igi2_o1[12]; struct QTask_s *ptTail; };
    struct { char igi2_o2[32]; struct real32x2_t nGraphicsFlag; };
    struct { char igi2_o3[40]; struct real32x3_t tRGB; };
    struct { char igi2_o4[52]; struct real32x3_t tAcceleration; };
    struct { char igi2_o5[64]; struct real32x9_t tOriginalOrientation; };
    struct { char igi2_o6[104]; struct real32x9_t tGammaOrientation; };
    char igi2_extent[144];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  bool v2; // c3
  struct QReference_s *ptHead; // eax
  struct QTask_s *pxObject; // eax
  struct QReference_s *v5; // eax
  struct QReference_s *v6; // eax
  float vZ; // ecx
  float v8; // edx
  struct QTask_s *v9; // eax
  char *v10; // eax
  struct MTP_BoneVertexRef_s *vX_low; // edi
  struct QTask_s *v12; // eax
  char *v13; // eax
  struct QSprite_s *p_tQSprite; // eax
  char v15; // dl
  struct World_s *ptWorld; // esi
  struct QReference_s *ptMiddle; // ecx
  double v18; // st7
  struct QTask_s *v19; // eax
  struct QReference_s *v20; // eax
  struct QReference_s *v21; // eax

  v2 = *(float *)&ptQTask[8].tQTaskRefList.ptTail == *(float *)&ptQTask[8].ptParent;
  qmemcpy(&ptQTask[2].ptParent, &ptQTask[2].tQTaskChildren, 0x18u);
  if ( v2 )
  {
    ptHead = ptQTask[7].tQTaskRefList.ptHead;
    if ( ptHead )
    {
      pxObject = (struct QTask_s *)ptHead->pxObject;
      if ( pxObject )
        QTask_Delete(pxObject);
    }
    v5 = ptQTask[7].tQTaskRefList.ptHead;
    if ( v5 )
    {
      QReference_Delete(v5, &QTask_tQTaskRefPool);
      ptQTask[7].tQTaskRefList.ptHead = nullptr;
    }
  }
  ptQTask[8].ptParent = (struct QTask_s *)ptQTask[8].tQTaskRefList.ptTail;
  v6 = ptQTask[7].tQTaskRefList.ptHead;
  BYTE1(ptQTask[9].tQTaskChildren.ptMiddle) = 0;
  if ( !v6 )
  {
    igi2_frame.ptTail = ptQTask[4].tQTaskChildren.ptTail;
    igi2_frame.tOriginalOrientation.tX.vX = 1.0;
    memset(&igi2_frame.tOriginalOrientation.tX.vY, 0, 12);
    igi2_frame.tOriginalOrientation.tY.vY = 1.0;
    memset(&igi2_frame.tOriginalOrientation.tY.vZ, 0, 12);
    igi2_frame.tOriginalOrientation.tZ.vZ = 1.0;
    igi2_frame.tOriginalOrientation.nOps = 0;
    Real32x9_RotateGamma(&igi2_frame.tGammaOrientation, &igi2_frame.tOriginalOrientation, *(float *)&igi2_frame.ptTail);
    Real32x9_RotateAlpha(&igi2_frame.tOriginalOrientation, &igi2_frame.tGammaOrientation, *(float *)&ptQTask[4].tQTaskChildren.ptMiddle);
    vZ = igi2_frame.tOriginalOrientation.tY.vZ;
    v8 = igi2_frame.tOriginalOrientation.tZ.vZ;
    ptQTask[4].ptNext = (struct QTask_s *)LODWORD(igi2_frame.tOriginalOrientation.tX.vZ);
    v9 = ptQTask[8].tQTaskChildren.ptHead;
    *(float *)&ptQTask[4].ptPrev = vZ;
    *(float *)&ptQTask[4].tQTaskChildren.ptHead = v8;
    if ( v9 )
    {
      v10 = &v9[-1].isInMemPool + 1;
      if ( v10 )
      {
        if ( v10 == (char *)1 )
          vX_low = &MTP_atLODVirModel[45].atBoneVertexRefs[20].atVertexRefs[785];
        else
          vX_low = (struct MTP_BoneVertexRef_s *)LODWORD(igi2_frame.nGraphicsFlag.vX);
      }
      else
      {
        vX_low = &MTP_atLODVirModel[45].atBoneVertexRefs[20].atVertexRefs[783];
      }
    }
    else
    {
      vX_low = &MTP_atLODVirModel[48].atBoneVertexRefs[1].atVertexRefs[668];
    }
    v12 = ptQTask[8].tQTaskChildren.ptTail;
    if ( v12 )
    {
      v13 = &v12[-1].isInMemPool + 1;
      if ( v13 )
      {
        if ( v13 == (char *)1 )
          p_tQSprite = &Smoke_ptSmoke2->tQSprite;
        else
          p_tQSprite = &Smoke_ptSmoke1->tQSprite;
      }
      else
      {
        p_tQSprite = &Smoke_ptBlood->tQSprite;
      }
    }
    else
    {
      p_tQSprite = &Smoke_ptFireball->tQSprite;
      if ( !ptQTask[1].ptParent )
      {
        ptQTask[1].ptParent = (struct QTask_s *)1;
        *(_DWORD *)&ptQTask[1].eQTaskType = 1056964608;
        ptQTask[2].ptNext = (struct QTask_s *)1065353216;
      }
    }
    v15 = BYTE2(ptQTask[9].tQTaskChildren.ptMiddle);
    ptWorld = Game_ptGame->ptWorld;
    ptMiddle = ptQTask[7].tQTaskRefList.ptMiddle;
    igi2_frame.tAcceleration.vZ = *(float *)&ptQTask[4].tQTaskRefList.ptMiddle * -204.8000030517578;
    v18 = *(float *)&ptQTask[4].tQTaskRefList.ptHead;
    igi2_frame.tAcceleration.vX = 0.0;
    igi2_frame.tAcceleration.vY = 0.0;
    igi2_frame.nGraphicsFlag.vX = v18 * 4096.0;
    igi2_frame.nGraphicsFlag.vY = igi2_frame.nGraphicsFlag.vX;
    igi2_frame.tRGB.vX = *(float *)&ptQTask[7].eQTaskType * 63.0;
    igi2_frame.tRGB.vY = *(float *)&ptQTask[8].ptNext * 63.0;
    igi2_frame.tRGB.vZ = *(float *)&ptQTask[8].ptPrev * 63.0;
    igi2_frame.nAnimDelta = *(float *)&ptQTask[8].tQTaskChildren.ptMiddle * 0.03333333507180214;
    v19 = Particle2DDynCubeObj_New(
            ptQTask,
            ptWorld,
            p_tQSprite,
            &igi2_frame.tAcceleration,
            &igi2_frame.tRGB,
            &igi2_frame.nGraphicsFlag,
            409600.0,
            (int)vX_low,
            0,
            igi2_frame.nAnimDelta,
            0.0,
            (int)ptMiddle,
            v15 != 0
          ? (void (__cdecl *)(struct Particle2DCollisionContext_t *))Smoke_ParticleCollisionCallback
          : nullptr);
    v20 = QTask_NewQTaskRef(v19);
    ptQTask[7].tQTaskRefList.ptHead = v20;
    *((_BYTE *)v20->pxObject + 261) = 0;
  }
  v21 = ptQTask[7].tQTaskRefList.ptHead;
  if ( v21 )
    *((float *)v21->pxObject + 58) = *(float *)&ptQTask[8].eQTaskType * 4096.0;
  Level_CompileLevelExpression((struct LevelExpression_s *)&ptQTask[5].tQTaskRefList, ptQTask);
  memset(&ptQTask[1], 0, 0x1Cu);
  QTask_TriggerQTaskEventParent(ptQTask, Attach_eAttachEvent, &ptQTask[1]);
  Smoke_CalcRelativePosAndOrientation((struct Smoke_s *)ptQTask);
}

// source: j/0/effects/smoke.c:928  [size]
unsigned __int16 __cdecl Smoke_GetQTaskType()
{
  return Smoke_eQTaskType;
}

// source: j/0/effects/smoke.c:963  [anchor-callee]
struct QTask_s *__cdecl Smoke_New(
        struct QTask_s *ptParent,
        struct real64x3_t *ptPos,
        float vAlpha,
        float vGamma,
        int nMaxNumParticles,
        float vRandomRadius,
        float vRandomAngle,
        float vRandomMinSpeed,
        float vRandomMaxSpeed,
        struct real32x3_t *ptRGB,
        float vLifeTime,
        float vFadeTime,
        enum SmokeMode_e eMode,
        int iSprite,
        float vSize,
        float vSizeDelta,
        float vMinRotation,
        float vMaxRotation,
        float vIntensity,
        float vGenerateFactor)
{
  struct QTask_s *v20; // ebx

  v20 = QTask_NewFn(ptParent, Smoke_eQTaskType, nullptr);
  qmemcpy(&v20[2].ptParent, ptPos, 0x18u);
  *(float *)&v20[4].tQTaskChildren.ptMiddle = vAlpha;
  *(float *)&v20[4].tQTaskChildren.ptTail = vGamma;
  v20[7].tQTaskRefList.ptMiddle = (struct QReference_s *)nMaxNumParticles;
  *(float *)&v20[5].ptNext = vRandomRadius;
  *(float *)&v20[4].eQTaskType = vRandomAngle;
  *(float *)&v20[4].tQTaskRefList.ptTail = vRandomMinSpeed;
  *(float *)&v20[4].ptParent = vRandomMaxSpeed;
  *(struct real32x3_t *)&v20[7].eQTaskType = *ptRGB;
  *(double *)&v20[5].tQTaskChildren.ptHead = vGenerateFactor;
  *(float *)&v20[7].tQTaskRefList.ptTail = vLifeTime;
  *(float *)&v20[7].ptParent = vFadeTime;
  v20[8].tQTaskChildren.ptHead = (struct QTask_s *)eMode;
  v20[8].tQTaskChildren.ptTail = (struct QTask_s *)iSprite;
  *(float *)&v20[4].tQTaskRefList.ptHead = vSize;
  *(float *)&v20[8].tQTaskChildren.ptMiddle = vSizeDelta;
  *(float *)&v20[8].tQTaskRefList.ptMiddle = vMinRotation;
  *(float *)&v20[8].tQTaskRefList.ptHead = vMaxRotation;
  *(float *)&v20[8].tQTaskRefList.ptTail = vIntensity;
  Smoke_UpdateInternalDataHandler(v20, nullptr);
  return v20;
}

// source: j/0/effects/smoke.c:1011  [size]
struct QTask_s *__cdecl Smoke_SetGenerateFactor(struct QTask_s *ptSmokeQTask, float vFactor)
{
  *(double *)&ptSmokeQTask[5].tQTaskChildren.ptHead = vFactor;
  return ptSmokeQTask;
}

// source: j/0/effects/smoke.c:1029  [size]
struct QTask_s *__cdecl Smoke_SetPos(
        struct QTask_s *ptSmokeQTask,
        struct real64x3_t *ptPos)
{
  qmemcpy(&ptSmokeQTask[2].ptParent, ptPos, 0x18u);
  return ptSmokeQTask;
}

// source: j/0/effects/smoke.c:1047  [size]
void __cdecl Smoke_SetIntensity(struct QTask_s *ptSmokeQTask, float vFactor)
{
  *(float *)&ptSmokeQTask[8].tQTaskRefList.ptTail = vFactor;
}

// source: j/0/effects/smoke.c:1068  [anchor-callee]
void __cdecl Smoke_DoDamage(struct Smoke_s *ptSmoke)
{
  int nDamageTimer; // ecx
  struct QTaskList_s *v2; // edx
  struct QTaskList_s *v3; // ebx
  double v4; // st7
  float vDamagePerSec; // ecx
  int v6; // edi
  __int16 v7; // ax
  struct QTask_s **ptQTask; // esi
  void (__cdecl *pfHandler)(struct QTask_s *, struct SmokeDamageContext_s *); // edx
  struct SmokeDamageContext_s tContext; // [esp+10h] [ebp-24h] BYREF

  nDamageTimer = ptSmoke->tSmokeDamage.nDamageTimer;
  v2 = Human_ptQTaskList;
  v3 = Human_ptQTaskList;
  if ( nDamageTimer )
  {
    ptSmoke->tSmokeDamage.nDamageTimer = nDamageTimer - 1;
  }
  else
  {
    v4 = ptSmoke->tSmokeDamage.vDamageRadius * 4096.0;
    qmemcpy(&tContext, &ptSmoke->tPos, 0x18u);
    tContext.vRadius = v4;
    vDamagePerSec = ptSmoke->tSmokeDamage.vDamagePerSec;
    ptSmoke->tSmokeDamage.nDamageTimer = 30;
    tContext.vDamage = vDamagePerSec;
    v6 = 0;
    if ( v2->nTask > 0 )
    {
      v7 = Smoke_eSmokeDamageEvent;
      ptQTask = v2->ptQTask;
      do
      {
        if ( v7 == 512 )
        {
          v7 = QTask_NewQTaskEventFn(0, "SmokeDamage");
          Smoke_eSmokeDamageEvent = v7;
        }
        pfHandler = (void (__cdecl *)(struct QTask_s *, struct SmokeDamageContext_s *))QTask_aatQTaskFinalEvent[v7][(*ptQTask)->eQTaskType].pfHandler;
        if ( pfHandler )
        {
          pfHandler(*ptQTask, &tContext);
          v7 = Smoke_eSmokeDamageEvent;
        }
        ++v6;
        ++ptQTask;
      }
      while ( v6 < v3->nTask );
    }
  }
}

// source: j/0/effects/smoke.c:1104  [anchor-refs]
__int16 __cdecl Smoke_GetSmokeDamageEvent()
{
  __int16 result; // ax

  result = Smoke_eSmokeDamageEvent;
  if ( Smoke_eSmokeDamageEvent == 512 )
  {
    result = QTask_NewQTaskEventFn(0, "SmokeDamage");
    Smoke_eSmokeDamageEvent = result;
  }
  return result;
}

// source: j/0/effects/smoke.c:1125  [anchor-strings]
void __cdecl Smoke_Open()
{
  unsigned __int16 v0; // si
  struct ParameterList_s *v1; // eax
  int v2; // edx

  dword_79EF59C = 3;
  dword_79EF5A0 = (int)Smoke_azDefaultTypes;
  dword_79EF630 = 0;
  dword_79EF634 = 0;
  dword_79EF638 = 0;
  dword_79EF63C = 1076710400;
  dword_79EF5E0 = 0;
  dword_79EF5E4 = 0;
  dword_79EF5E8 = 0;
  dword_79EF5EC = 1080213504;
  dword_79EF670 = 0;
  dword_79EF674 = 1072693248;
  dword_79EF678 = 0;
  dword_79EF67C = 1089470432;
  dword_79EF5F0 = 0;
  dword_79EF5F4 = 0;
  dword_79EF5F8 = 0;
  dword_79EF5FC = 1074790400;
  dword_79EF620 = 0;
  dword_79EF624 = 0;
  dword_79EF628 = 0;
  dword_79EF62C = 1075052544;
  dword_79EF640 = 0;
  dword_79EF644 = 0;
  dword_79EF648 = 0;
  dword_79EF64C = 1075052544;
  dword_79EF608 = 0;
  dword_79EF60C = -1067270144;
  dword_79EF610 = 0;
  dword_79EF614 = 1080213504;
  dword_79EF650 = 0;
  dword_79EF654 = 0;
  dword_79EF658 = 0;
  dword_79EF65C = 1074266112;
  dword_79EF5A8 = 0;
  dword_79EF5AC = 0;
  dword_79EF5B0 = 0;
  dword_79EF5B4 = 0x40000000;
  dword_79EF660 = 0;
  dword_79EF664 = 0;
  dword_79EF668 = 1610612736;
  dword_79EF66C = 1074340347;
  dword_79EF680 = 1610612736;
  dword_79EF684 = -1073143301;
  dword_79EF688 = 1610612736;
  dword_79EF68C = 1074340347;
  dword_79EF5D0 = 0;
  dword_79EF5D4 = 0;
  dword_79EF5D8 = 0;
  dword_79EF5DC = 1072693248;
  Smoke_ptLODVirModel = MTP_GetLODVirModel("1729_01_1");
  v0 = QTask_NewQTaskType("Smoke", 376, EditorRigidObj_eQTaskType, 0, 0);
  Smoke_eQTaskType = v0;
  QTask_LinkQTaskEventHandlerFn(
    v0,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveHandler);
  QTask_LinkQTaskEventHandlerFn(v0, 0, Smoke_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 1, Smoke_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 2, Smoke_DeleteHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, Attach_eUpdateAttachmentEvent, Smoke_UpdateAttachmentHandler);
  QTask_LinkQTaskEventHandlerFn(v0, Attach_eAttachEvent, nullptr);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Smoke_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(v0, ParameterList_eUpdateInternalDataQTaskEvent, Smoke_UpdateInternalDataHandler);
  QTask_LinkQTaskEventHandlerFn(v0, 4, Smoke_ParentChangedHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, Level_eRegisterLevelScriptSymbolsEvent, Smoke_RegisterScriptSymbolsHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, Level_eRemoveLevelScriptSymbolsEvent, Smoke_RemoveScriptSymbolsHandler);
  QTask_LinkQTaskEventHandlerFn(v0, 5, nullptr);
  QTask_LinkQTaskEventHandlerFn(v0, DynCubeObj_eDynCubeObjRegisterQTaskEvent, Smoke_RegisterHandler);
  QTask_LinkQTaskEventHandlerFn(v0, DynCubeObj_eDynCubeObjRemoveQTaskEvent, Smoke_RemoveHandler);
  v1 = (struct ParameterList_s *)Mem_AllocFn(552, 4);
  v1->ptParameterListItem = (struct ParameterListItem_s *)&v1[1];
  v2 = Level_eParameterTypeObjectPos;
  v1->nParameters = 0;
  v1->nMaxParameters = 27;
  Smoke_ptParameterList = v1;
  ParameterList_AddParameter(v1, 0x58u, v2, "Position", 7u, nullptr);
  ParameterList_AddParameter(Smoke_ptParameterList, 0xACu, Level_eParameterTypeAngle, "Alpha", 7u, &dword_79EF660);
  ParameterList_AddParameter(Smoke_ptParameterList, 0xB0u, Level_eParameterTypeAngle, "Gamma", 7u, &dword_79EF680);
  ParameterList_AddParameter(
    Smoke_ptParameterList,
    0x130u,
    Level_eParameterTypeInt32,
    "Number of Particles",
    7u,
    &dword_79EF670);
  ParameterList_AddParameter(Smoke_ptParameterList, 0xC8u, Level_eParameterTypeReal32, "Radius", 7u, &dword_79EF620);
  ParameterList_AddParameter(
    Smoke_ptParameterList,
    0xC4u,
    Level_eParameterTypeAngle,
    "Maximum Random Angle",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Smoke_ptParameterList,
    0xBCu,
    Level_eParameterTypeReal32,
    "Minimum Velocity",
    7u,
    &dword_79EF630);
  ParameterList_AddParameter(
    Smoke_ptParameterList,
    0xC0u,
    Level_eParameterTypeReal32,
    "Maximum Velocity",
    7u,
    &dword_79EF630);
  ParameterList_AddParameter(Smoke_ptParameterList, 0x13Cu, Level_eParameterTypeRGB, "Colour", 7u, nullptr);
  ParameterList_AddParameter(Smoke_ptParameterList, 0x134u, Level_eParameterTypeReal32, "Life Time", 7u, &dword_79EF5F0);
  ParameterList_AddParameter(Smoke_ptParameterList, 0x138u, Level_eParameterTypeReal32, "Fade Time", 7u, &dword_79EF5F0);
  ParameterList_AddParameter(Smoke_ptParameterList, 0x148u, Level_eParameterTypeInt32, "Fade Mode", 7u, &dword_79EF5A8);
  ParameterList_AddParameter(
    Smoke_ptParameterList,
    0x150u,
    Level_eParameterTypeInt32,
    "Sprite index",
    7u,
    &dword_79EF650);
  ParameterList_AddParameter(
    Smoke_ptParameterList,
    0xB4u,
    Level_eParameterTypeReal32,
    "Particle Size",
    7u,
    &dword_79EF640);
  ParameterList_AddParameter(
    Smoke_ptParameterList,
    0x14Cu,
    Level_eParameterTypeReal32,
    "Particle Size Delta",
    7u,
    &dword_79EF608);
  ParameterList_AddParameter(
    Smoke_ptParameterList,
    0x158u,
    Level_eParameterTypeAngle,
    "Minimum Rotation Speed",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Smoke_ptParameterList,
    0x154u,
    Level_eParameterTypeAngle,
    "Maximum Rotation Speed",
    7u,
    nullptr);
  ParameterList_AddParameter(Smoke_ptParameterList, 0x15Cu, Level_eParameterTypeReal32, "Intensity", 7u, &dword_79EF5D0);
  ParameterList_AddParameterMinMax(
    Smoke_ptParameterList,
    0xB8u,
    Level_eParameterTypeReal32,
    "Gravity factor",
    7u,
    -1.0,
    1.0);
  ParameterList_AddParameter(
    Smoke_ptParameterList,
    0xD0u,
    Level_eParameterTypeReal64,
    "Initial generate factor value",
    7u,
    &dword_79EF5E0);
  ParameterList_AddParameter(
    Smoke_ptParameterList,
    0xDCu,
    Level_eParameterTypeVarString,
    "Generate factor",
    7u,
    nullptr);
  ParameterList_AddParameter(Smoke_ptParameterList, 0x174u, Level_eParameterTypebool8, "Move Particles", 7u, nullptr);
  ParameterList_AddParameter(Smoke_ptParameterList, 0x164u, Level_eParameterTypeReal32, "View cutoff", 7u, nullptr);
  ParameterList_AddParameter(Smoke_ptParameterList, 0x48u, Level_eParameterTypebool8, "Do Damage", 7u, nullptr);
  ParameterList_AddParameter(Smoke_ptParameterList, 0x4Cu, Level_eParameterTypeReal32, "Damage Per Sec", 7u, nullptr);
  ParameterList_AddParameter(Smoke_ptParameterList, 0x50u, Level_eParameterTypeReal32, "Damage Radius (m)", 7u, nullptr);
  Symbol_Register(
    "TASKTYPE_SMOKE",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)Smoke_eQTaskType,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Smoke_ptFireball = GameFunctions_RegisterGameSprite("fireball.spr");
  Smoke_ptBlood = GameFunctions_RegisterGameSprite("blood1.spr");
  Smoke_ptSmoke1 = GameFunctions_RegisterGameSprite("smoke1.spr");
  Smoke_ptSmoke2 = GameFunctions_RegisterGameSprite("smoke2.spr");
  QTask_LinkQTaskEventHandlerFn(
    Smoke_eQTaskType,
    Serialize_eDeSerializeDoneQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))sub_544170);
}

// source: j/0/effects/smoke.c:1298  [size]
void __cdecl Smoke_Close()
{
  int v0; // esi

  QTask_DeleteQTaskEvent(Smoke_eSmokeDamageEvent);
  if ( Smoke_ptParameterList )
  {
    v0 = *(_DWORD *)((unsigned int)&Smoke_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
  QTask_DeleteQTaskType(Smoke_eQTaskType);
}
