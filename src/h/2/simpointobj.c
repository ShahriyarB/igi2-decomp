/* h/2/simpointobj.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: h/2/simpointobj.c:42  [size]
void __cdecl SimpointObjContainer_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ;
}

// source: h/2/simpointobj.c:56  [size]
void __cdecl SimpointObjContainer_DeleteHandler(struct QTask_s *ptQTask)
{
  ;
}

// source: h/2/simpointobj.c:68  [anchor-mhash]
void __cdecl SimpointObjContainer_RunHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { float vAirResistance; };
    struct { char igi2_o1[16]; float ptDest; };
    struct { char igi2_o2[16]; struct QTask_s *ptDesta; };
    struct { char igi2_o3[20]; struct real32x9_t Real32x9_Multiply_tTemp; };
    struct { char igi2_o4[60]; struct real32x9_t Real32x9_Normalize_tTemp; };
    struct { char igi2_o5[100]; struct real32x9_t tDeltaOrientation; };
    struct { char igi2_o6[140]; float vAlpha; };
    struct { char igi2_o7[144]; float vGravity; };
    struct { char igi2_o8[148]; float vBeta; };
    struct { char igi2_o9[152]; struct real64x3_t tNewPos; };
    char igi2_extent[176];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *ptHead; // ebx
  float v2; // edx
  int nOps; // edx
  double v4; // st7
  double v5; // st6
  int v6; // eax
  bool v7; // sf
  double v8; // st7
  long double v9; // st4
  long double v10; // st4
  long double v11; // st7
  struct QTask_s *v12; // ecx
  int v13; // edx
  struct QTask_s *v14; // eax
  void (__cdecl *pfHandler)(struct QTask_s *); // eax
  int v16; // edx
  struct real32x3_t tTemp_; // 0:^18.12
  struct real32x3_t v32; // 0:^28.12

  ptHead = ptQTask->tQTaskChildren.ptHead;
  if ( ptHead->ptNext && ptHead )
  {
    igi2_frame.vAirResistance = *(float *)&ptQTask[1].eQTaskType;
    igi2_frame.vGravity = *(float *)&ptQTask[2].tQTaskChildren.ptHead * *(float *)&ptQTask[2].ptPrev * igi2_frame.vAirResistance;
    igi2_frame.ptDest = *(float *)&ptQTask[2].tQTaskChildren.ptMiddle * 0.9900000095367432;
    *(float *)&ptQTask[2].tQTaskChildren.ptMiddle = igi2_frame.ptDest;
    igi2_frame.vAlpha = *(float *)&ptQTask[2].tQTaskChildren.ptTail * 0.9900000095367432;
    *(float *)&ptQTask[2].tQTaskChildren.ptTail = igi2_frame.vAlpha;
    igi2_frame.vBeta = *(float *)&ptQTask[2].tQTaskRefList.ptHead * 0.9900000095367432;
    v2 = igi2_frame.vBeta;
    *(float *)&ptQTask[2].tQTaskRefList.ptHead = igi2_frame.vBeta;
    Real32x9_Create(&igi2_frame.tDeltaOrientation, igi2_frame.ptDest, igi2_frame.vAlpha, v2);
    nOps = igi2_frame.tDeltaOrientation.nOps;
    do
    {
      v4 = igi2_frame.vAirResistance * *(float *)&ptHead[8].ptNext;
      *(float *)&ptHead[8].ptNext = v4;
      v5 = igi2_frame.vAirResistance * *(float *)&ptHead[8].ptPrev;
      *(float *)&ptHead[8].ptPrev = v5;
      *(float *)&igi2_frame.ptDesta = igi2_frame.vAirResistance * *(float *)&ptHead[8].tQTaskChildren.ptHead - igi2_frame.vGravity;
      ptHead[8].tQTaskChildren.ptHead = igi2_frame.ptDesta;
      igi2_frame.tNewPos.vX = v4 + *(double *)&ptHead[1].ptNext;
      igi2_frame.tNewPos.vY = v5 + *(double *)&ptHead[1].tQTaskChildren.ptHead;
      igi2_frame.tNewPos.vZ = *(float *)&igi2_frame.ptDesta + *(double *)&ptHead[1].tQTaskChildren.ptTail;
      qmemcpy(&ptHead[1], &igi2_frame.tNewPos, 0x18u);
      igi2_frame.Real32x9_Multiply_tTemp.tX.vX = igi2_frame.tDeltaOrientation.tX.vX * *(float *)&ptHead[3].ptPrev
                                    + igi2_frame.tDeltaOrientation.tX.vZ * *(float *)&ptHead[3].tQTaskRefList.ptTail
                                    + igi2_frame.tDeltaOrientation.tX.vY * *(float *)&ptHead[3].tQTaskChildren.ptTail;
      igi2_frame.Real32x9_Multiply_tTemp.tX.vY = igi2_frame.tDeltaOrientation.tX.vZ * *(float *)&ptHead[3].ptParent
                                    + igi2_frame.tDeltaOrientation.tX.vY * *(float *)&ptHead[3].tQTaskRefList.ptHead
                                    + igi2_frame.tDeltaOrientation.tX.vX * *(float *)&ptHead[3].tQTaskChildren.ptHead;
      igi2_frame.Real32x9_Multiply_tTemp.tX.vZ = igi2_frame.tDeltaOrientation.tX.vX * *(float *)&ptHead[3].tQTaskChildren.ptMiddle
                                    + igi2_frame.tDeltaOrientation.tX.vZ * *(float *)&ptHead[3].eQTaskType
                                    + igi2_frame.tDeltaOrientation.tX.vY * *(float *)&ptHead[3].tQTaskRefList.ptMiddle;
      igi2_frame.Real32x9_Multiply_tTemp.tY.vX = igi2_frame.tDeltaOrientation.tY.vX * *(float *)&ptHead[3].ptPrev
                                    + igi2_frame.tDeltaOrientation.tY.vZ * *(float *)&ptHead[3].tQTaskRefList.ptTail
                                    + igi2_frame.tDeltaOrientation.tY.vY * *(float *)&ptHead[3].tQTaskChildren.ptTail;
      igi2_frame.Real32x9_Multiply_tTemp.tY.vY = igi2_frame.tDeltaOrientation.tY.vZ * *(float *)&ptHead[3].ptParent
                                    + igi2_frame.tDeltaOrientation.tY.vY * *(float *)&ptHead[3].tQTaskRefList.ptHead
                                    + igi2_frame.tDeltaOrientation.tY.vX * *(float *)&ptHead[3].tQTaskChildren.ptHead;
      v6 = (int)&ptHead[4].ptNext->ptNext + nOps + 1;
      v7 = (int)&ptHead[4].ptNext[-24] + nOps - 39 < 0;
      igi2_frame.Real32x9_Multiply_tTemp.tY.vZ = igi2_frame.tDeltaOrientation.tY.vX * *(float *)&ptHead[3].tQTaskChildren.ptMiddle
                                    + igi2_frame.tDeltaOrientation.tY.vZ * *(float *)&ptHead[3].eQTaskType
                                    + igi2_frame.tDeltaOrientation.tY.vY * *(float *)&ptHead[3].tQTaskRefList.ptMiddle;
      v8 = igi2_frame.tDeltaOrientation.tZ.vX * *(float *)&ptHead[3].ptPrev;
      igi2_frame.Real32x9_Multiply_tTemp.nOps = v6;
      igi2_frame.Real32x9_Multiply_tTemp.tZ.vX = v8
                                    + igi2_frame.tDeltaOrientation.tZ.vZ * *(float *)&ptHead[3].tQTaskRefList.ptTail
                                    + igi2_frame.tDeltaOrientation.tZ.vY * *(float *)&ptHead[3].tQTaskChildren.ptTail;
      igi2_frame.Real32x9_Multiply_tTemp.tZ.vY = igi2_frame.tDeltaOrientation.tZ.vZ * *(float *)&ptHead[3].ptParent
                                    + igi2_frame.tDeltaOrientation.tZ.vY * *(float *)&ptHead[3].tQTaskRefList.ptHead
                                    + igi2_frame.tDeltaOrientation.tZ.vX * *(float *)&ptHead[3].tQTaskChildren.ptHead;
      igi2_frame.Real32x9_Multiply_tTemp.tZ.vZ = igi2_frame.tDeltaOrientation.tZ.vX * *(float *)&ptHead[3].tQTaskChildren.ptMiddle
                                    + igi2_frame.tDeltaOrientation.tZ.vZ * *(float *)&ptHead[3].eQTaskType
                                    + igi2_frame.tDeltaOrientation.tZ.vY * *(float *)&ptHead[3].tQTaskRefList.ptMiddle;
      qmemcpy(&ptHead[3].ptPrev, &igi2_frame.Real32x9_Multiply_tTemp, sizeof(struct QTask_s));
      if ( !(v7 ^ __OFSUB__(v6, 1000) | (v6 == 1000)) )
      {
        igi2_frame.Real32x9_Normalize_tTemp.tX = igi2_frame.Real32x9_Multiply_tTemp.tX;
        if ( igi2_frame.Real32x9_Multiply_tTemp.tX.vX != 0.0
          || igi2_frame.Real32x9_Multiply_tTemp.tX.vY != 0.0
          || igi2_frame.Real32x9_Multiply_tTemp.tX.vZ != 0.0 )
        {
          v9 = sqrt(
                 igi2_frame.Real32x9_Multiply_tTemp.tX.vX * igi2_frame.Real32x9_Multiply_tTemp.tX.vX
               + igi2_frame.Real32x9_Multiply_tTemp.tX.vY * igi2_frame.Real32x9_Multiply_tTemp.tX.vY
               + igi2_frame.Real32x9_Multiply_tTemp.tX.vZ * igi2_frame.Real32x9_Multiply_tTemp.tX.vZ);
          igi2_frame.Real32x9_Normalize_tTemp.tX.vX = igi2_frame.Real32x9_Multiply_tTemp.tX.vX * (1.0 / v9);
          igi2_frame.Real32x9_Normalize_tTemp.tX.vY = igi2_frame.Real32x9_Normalize_tTemp.tX.vY * (1.0 / v9);
          igi2_frame.Real32x9_Normalize_tTemp.tX.vZ = igi2_frame.Real32x9_Normalize_tTemp.tX.vZ * (1.0 / v9);
        }
        tTemp_.vX = igi2_frame.Real32x9_Multiply_tTemp.tZ.vY * igi2_frame.Real32x9_Multiply_tTemp.tX.vZ
                  - igi2_frame.Real32x9_Multiply_tTemp.tZ.vZ * igi2_frame.Real32x9_Multiply_tTemp.tX.vY;
        tTemp_.vY = -(igi2_frame.Real32x9_Multiply_tTemp.tZ.vX * igi2_frame.Real32x9_Multiply_tTemp.tX.vZ
                    - igi2_frame.Real32x9_Multiply_tTemp.tZ.vZ * igi2_frame.Real32x9_Multiply_tTemp.tX.vX);
        tTemp_.vZ = igi2_frame.Real32x9_Multiply_tTemp.tZ.vX * igi2_frame.Real32x9_Multiply_tTemp.tX.vY
                  - igi2_frame.Real32x9_Multiply_tTemp.tZ.vY * igi2_frame.Real32x9_Multiply_tTemp.tX.vX;
        igi2_frame.Real32x9_Normalize_tTemp.tY = tTemp_;
        v32.vX = tTemp_.vZ * igi2_frame.Real32x9_Normalize_tTemp.tX.vY - tTemp_.vY * igi2_frame.Real32x9_Normalize_tTemp.tX.vZ;
        v32.vY = -(tTemp_.vZ * igi2_frame.Real32x9_Normalize_tTemp.tX.vX - tTemp_.vX * igi2_frame.Real32x9_Normalize_tTemp.tX.vZ);
        v32.vZ = tTemp_.vY * igi2_frame.Real32x9_Normalize_tTemp.tX.vX - tTemp_.vX * igi2_frame.Real32x9_Normalize_tTemp.tX.vY;
        igi2_frame.Real32x9_Normalize_tTemp.tZ = v32;
        if ( tTemp_.vX != 0.0 || tTemp_.vY != 0.0 || tTemp_.vZ != 0.0 )
        {
          v10 = sqrt(tTemp_.vZ * tTemp_.vZ + tTemp_.vY * tTemp_.vY + tTemp_.vX * tTemp_.vX);
          igi2_frame.Real32x9_Normalize_tTemp.tY.vX = tTemp_.vX * (1.0 / v10);
          igi2_frame.Real32x9_Normalize_tTemp.tY.vY = igi2_frame.Real32x9_Normalize_tTemp.tY.vY * (1.0 / v10);
          igi2_frame.Real32x9_Normalize_tTemp.tY.vZ = igi2_frame.Real32x9_Normalize_tTemp.tY.vZ * (1.0 / v10);
        }
        if ( v32.vX != 0.0 || v32.vY != 0.0 || v32.vZ != 0.0 )
        {
          v11 = 1.0 / sqrt(v32.vX * v32.vX + v32.vY * v32.vY + v32.vZ * v32.vZ);
          igi2_frame.Real32x9_Normalize_tTemp.tZ.vX = v32.vX * v11;
          igi2_frame.Real32x9_Normalize_tTemp.tZ.vY = igi2_frame.Real32x9_Normalize_tTemp.tZ.vY * v11;
          igi2_frame.Real32x9_Normalize_tTemp.tZ.vZ = igi2_frame.Real32x9_Normalize_tTemp.tZ.vZ * v11;
        }
        qmemcpy(&igi2_frame.Real32x9_Multiply_tTemp, &igi2_frame.Real32x9_Normalize_tTemp, sizeof(igi2_frame.Real32x9_Multiply_tTemp));
        igi2_frame.Real32x9_Multiply_tTemp.nOps = 0;
      }
      ptHead = ptHead->ptNext;
    }
    while ( ptHead && ptHead->ptNext );
    v12 = ptQTask->tQTaskChildren.ptHead;
    if ( v12->ptNext && v12 )
    {
      v13 = QTask_nProtectedQTaskStackOffset;
      do
      {
        if ( v12->ptNext )
          v14 = v12->ptNext->ptNext != nullptr ? v12->ptNext : nullptr;
        else
          v14 = nullptr;
        QTask_atProtectedQTaskStack[v13].ptQTask = v14;
        pfHandler = (void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[1][v12->eQTaskType].pfHandler;
        v16 = v13 + 1;
        QTask_nProtectedQTaskStackOffset = v16;
        if ( pfHandler )
        {
          pfHandler(v12);
          v16 = QTask_nProtectedQTaskStackOffset;
        }
        v12 = (struct QTask_s *)dword_849C7DC[v16];
        v13 = v16 - 1;
        QTask_nProtectedQTaskStackOffset = v13;
      }
      while ( v12 );
    }
  }
  else if ( LOBYTE(ptQTask[2].tQTaskRefList.ptMiddle) )
  {
    QTask_Delete(ptQTask);
  }
}

// source: h/2/simpointobj.c:160  [anchor-mhash]
void __cdecl SimpointObj_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct World_s *v2; // eax
  struct DynCubeObj_s *ptManualRedrawList; // ecx
  struct DynCubeObj_s *ptPrev; // ecx

  ModelObj_Init((struct ModelObj_s *)ptQTask, World_ptActiveWorld, nullptr);
  ptQTask[7].tQTaskChildren.ptHead = nullptr;
  ptQTask[7].tQTaskChildren.ptMiddle = (struct QTask_s *)2;
  ptQTask[7].tQTaskRefList.ptHead = nullptr;
  ptQTask[7].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[7].tQTaskRefList.ptTail = nullptr;
  ptQTask[7].ptParent = nullptr;
  *(_DWORD *)&ptQTask[7].eQTaskType = 0;
  v2 = World_ptActiveWorld;
  ptManualRedrawList = World_ptActiveWorld->ptManualRedrawList;
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
    World_ptActiveWorld->ptManualRedrawList = (struct DynCubeObj_s *)ptQTask;
    ptQTask[2].tQTaskChildren.ptTail = nullptr;
    v2->ptManualRedrawList->ptPrev = nullptr;
  }
}

// source: h/2/simpointobj.c:183  [anchor-mhash]
void __cdecl SimpointObj_DeleteHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptMiddle; // ecx
  struct QTask_s *ptTail; // ecx

  ptMiddle = ptQTask[2].tQTaskChildren.ptMiddle;
  if ( ptMiddle )
    ptMiddle[2].tQTaskChildren.ptTail = ptQTask[2].tQTaskChildren.ptTail;
  else
    World_ptActiveWorld->ptManualRedrawList = (struct DynCubeObj_s *)ptQTask[2].tQTaskChildren.ptTail;
  ptTail = ptQTask[2].tQTaskChildren.ptTail;
  if ( ptTail )
    ptTail[2].tQTaskChildren.ptMiddle = ptQTask[2].tQTaskChildren.ptMiddle;
}

// source: h/2/simpointobj.c:203  [anchor-mhash]
void __cdecl SimpointObj_RunHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptMiddle; // eax

  ptMiddle = ptQTask[8].tQTaskChildren.ptMiddle;
  if ( (int)ptMiddle > 0 )
    ptQTask[8].tQTaskChildren.ptMiddle = (struct QTask_s *)((char *)ptMiddle - 1);
  else
    QTask_Delete(ptQTask);
}

// source: h/2/simpointobj.c:229  [size]
void __cdecl SimpointObj_CollisionEvalHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_BYTE *)pxContext = 0;
}

// source: h/2/simpointobj.c:282  [anchor-callee]
void __cdecl SimpointObj_Open()
{
  unsigned __int16 BaseQTaskType; // ax
  unsigned __int16 v1; // si
  unsigned __int16 v2; // si

  BaseQTaskType = QTask_GetBaseQTaskType();
  v1 = QTask_NewQTaskType("SimpointObjContainer", 108, BaseQTaskType, 32, 0);
  SimpointObjContainer_eQTaskType = v1;
  QTask_LinkQTaskEventHandlerFn(v1, 0, (void (__cdecl *)(struct QTask_s *, void *))SimpointObjContainer_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 2, (void (__cdecl *)(struct QTask_s *))SimpointObjContainer_DeleteHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 1, SimpointObjContainer_RunHandler);
  v2 = QTask_NewQTaskType("SimpointObj", 336, RigidDynCubeObj_eQTaskType, 0, 0);
  SimpointObj_eQTaskType = v2;
  QTask_LinkQTaskEventHandlerFn(v2, 0, SimpointObj_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v2, 2, SimpointObj_DeleteHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v2, 1, SimpointObj_RunHandler);
  QTask_LinkQTaskEventHandlerFn(v2, 13, (void (__cdecl *)(struct QTask_s *, void *))SimpointObj_CollisionEvalHandler);
  SimpointObj_tRandomState.anRandom[0] = -923067897;
  SimpointObj_tRandomState.anRandom[1] = 971667286;
  SimpointObj_tRandomState.anRandom[2] = 2146516173;
}

// source: h/2/simpointobj.c:314  [size]
void __cdecl SimpointObj_Close()
{
  QTask_DeleteQTaskType(SimpointObjContainer_eQTaskType);
  QTask_DeleteQTaskType(SimpointObj_eQTaskType);
}

// source: h/2/simpointobj.c:329  [size]
unsigned __int16 __cdecl SimpointObj_GetQTaskType()
{
  return SimpointObj_eQTaskType;
}

// source: h/2/simpointobj.c:344  [size]
unsigned __int16 __cdecl SimpointObjContainer_GetQTaskType()
{
  return SimpointObjContainer_eQTaskType;
}

// source: h/2/simpointobj.c:368  [anchor-callee]
struct SimpointObjContainer_s *__cdecl SimpointObjContainer_New(
        int nLifetime,
        char *zModel,
        char *zCollSound,
        float vAirResistance,
        float vBounceFactor,
        float vGravity,
        float vMass,
        struct real32x3_t *ptRotationVelocity,
        char isSelfDestruct)
{
  struct SimpointObjContainer_s *result; // eax

  result = (struct SimpointObjContainer_s *)QTask_NewFn(Level_ptDynamicQTask, SimpointObjContainer_eQTaskType, nullptr);
  result->nLifetime = nLifetime;
  strcpy(result->zModel, zModel);
  if ( zCollSound )
    strcpy(result->zCollSound, zCollSound);
  else
    result->zCollSound[0] = 0;
  result->vAirResistance = vAirResistance;
  result->vBounceFactor = vBounceFactor;
  result->vGravity = vGravity;
  result->vMass = vMass;
  result->tRotationVelocity = *ptRotationVelocity;
  result->isSelfDestruct = isSelfDestruct;
  return result;
}

// source: h/2/simpointobj.c:428  [anchor-callee]
struct SimpointObj_s *__cdecl SimpointObjContainer_Add(
        struct SimpointObjContainer_s *ptSimpointObjContainer,
        unsigned __int16 eQTaskType,
        struct real64x3_t *ptPos,
        struct real32x9_t *ptOrientation,
        struct real32x3_t *ptVelocity)
{
  struct QTask_s *v5; // ebx
  struct LODVirModel_s *LODVirModelExistsFn; // eax

  v5 = QTask_NewFn(&ptSimpointObjContainer->tQTask, eQTaskType, nullptr);
  LODVirModelExistsFn = MTP_GetLODVirModelExistsFn(ptSimpointObjContainer->zModel);
  if ( LODVirModelExistsFn != *(struct LODVirModel_s **)&v5[2].eQTaskType )
  {
    ModelObj_SetLODVirModel((struct ModelObj_s *)v5, LODVirModelExistsFn, false);
    v5[7].tQTaskRefList.ptHead = nullptr;
    v5[7].tQTaskRefList.ptMiddle = nullptr;
    v5[7].tQTaskRefList.ptTail = nullptr;
    v5[7].ptParent = nullptr;
    *(_DWORD *)&v5[7].eQTaskType = 0;
  }
  qmemcpy(&v5[1], ptPos, 0x18u);
  qmemcpy(&v5[3].ptPrev, ptOrientation, sizeof(struct QTask_s));
  *(struct real32x3_t *)&v5[8].ptNext = *ptVelocity;
  v5[8].tQTaskChildren.ptMiddle = (struct QTask_s *)ptSimpointObjContainer->nLifetime;
  return (struct SimpointObj_s *)v5;
}

// source: h/2/simpointobj.c:473  [size]
void __cdecl SimpointObjContainer_SetSelfDestruct(
        struct SimpointObjContainer_s *ptSimpointObjContainer,
        char isSelfDestruct)
{
  ptSimpointObjContainer->isSelfDestruct = isSelfDestruct;
}
