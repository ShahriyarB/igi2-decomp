/* j/0/weapons/guncasing.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/weapons/guncasing.c:47  [anchor-mhash]
void __cdecl GunCasing_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct World_s *ptWorld; // eax
  struct DynCubeObj_s *ptManualRedrawList; // ecx
  struct DynCubeObj_s *ptPrev; // ecx

  ModelObj_Init((struct ModelObj_s *)ptQTask, Game_ptGame->ptWorld, nullptr);
  ptQTask[7].tQTaskChildren.ptHead = nullptr;
  ptQTask[7].tQTaskChildren.ptMiddle = (struct QTask_s *)2;
  ptQTask[7].tQTaskRefList.ptHead = nullptr;
  ptQTask[7].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[7].tQTaskRefList.ptTail = nullptr;
  ptQTask[7].ptParent = nullptr;
  *(_DWORD *)&ptQTask[7].eQTaskType = 0;
  ptWorld = Game_ptGame->ptWorld;
  ptManualRedrawList = ptWorld->ptManualRedrawList;
  if ( ptManualRedrawList )
  {
    ptManualRedrawList->ptPrev = (struct DynCubeObj_s *)ptQTask;
    ptWorld->ptManualRedrawList->ptPrev->ptNext = ptWorld->ptManualRedrawList;
    ptPrev = ptWorld->ptManualRedrawList->ptPrev;
    ptWorld->ptManualRedrawList = ptPrev;
    ptPrev->ptPrev = nullptr;
  }
  else
  {
    ptWorld->ptManualRedrawList = (struct DynCubeObj_s *)ptQTask;
    ptQTask[2].tQTaskChildren.ptTail = nullptr;
    ptWorld->ptManualRedrawList->ptPrev = nullptr;
  }
}

// source: j/0/weapons/guncasing.c:72  [anchor-mhash]
void __cdecl GunCasing_RunHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptNext; // ecx
  double v2; // st7
  struct QTask_s *v3; // ecx
  struct QTask_s *v4; // edx
  double v5; // st7
  double v6; // st6
  struct real32x9_t Real32x9_Multiply_tTemp; // [esp+0h] [ebp-28h] BYREF

  ptNext = ptQTask[8].ptNext;
  if ( ptNext )
  {
    v2 = *(float *)&ptQTask[9].tQTaskChildren.ptMiddle - 44.600887298583984;
    *(float *)&ptQTask[9].tQTaskChildren.ptMiddle = v2;
    ptQTask[8].ptNext = (struct QTask_s *)((char *)ptNext - 1);
    *(double *)&ptQTask[1].ptNext = *(float *)&ptQTask[9].ptPrev + *(double *)&ptQTask[1].ptNext;
    *(double *)&ptQTask[1].tQTaskChildren.ptHead = *(float *)&ptQTask[9].tQTaskChildren.ptHead
                                                 + *(double *)&ptQTask[1].tQTaskChildren.ptHead;
    *(double *)&ptQTask[1].tQTaskChildren.ptTail = v2 + *(double *)&ptQTask[1].tQTaskChildren.ptTail;
    Real32x9_Multiply_tTemp.tX.vX = *(float *)&ptQTask[3].ptPrev * *(float *)&ptQTask[8].ptPrev
                                  + *(float *)&ptQTask[8].tQTaskRefList.ptTail
                                  * *(float *)&ptQTask[3].tQTaskChildren.ptMiddle
                                  + *(float *)&ptQTask[8].tQTaskChildren.ptTail
                                  * *(float *)&ptQTask[3].tQTaskChildren.ptHead;
    Real32x9_Multiply_tTemp.tX.vY = *(float *)&ptQTask[8].tQTaskRefList.ptHead
                                  * *(float *)&ptQTask[3].tQTaskChildren.ptHead
                                  + *(float *)&ptQTask[3].ptPrev * *(float *)&ptQTask[8].tQTaskChildren.ptHead
                                  + *(float *)&ptQTask[8].ptParent * *(float *)&ptQTask[3].tQTaskChildren.ptMiddle;
    Real32x9_Multiply_tTemp.tX.vZ = *(float *)&ptQTask[8].tQTaskRefList.ptMiddle
                                  * *(float *)&ptQTask[3].tQTaskChildren.ptHead
                                  + *(float *)&ptQTask[3].ptPrev * *(float *)&ptQTask[8].tQTaskChildren.ptMiddle
                                  + *(float *)&ptQTask[8].eQTaskType * *(float *)&ptQTask[3].tQTaskChildren.ptMiddle;
    Real32x9_Multiply_tTemp.tY.vX = *(float *)&ptQTask[8].tQTaskRefList.ptTail
                                  * *(float *)&ptQTask[3].tQTaskRefList.ptMiddle
                                  + *(float *)&ptQTask[8].tQTaskChildren.ptTail
                                  * *(float *)&ptQTask[3].tQTaskRefList.ptHead
                                  + *(float *)&ptQTask[3].tQTaskChildren.ptTail * *(float *)&ptQTask[8].ptPrev;
    Real32x9_Multiply_tTemp.tY.vY = *(float *)&ptQTask[8].tQTaskRefList.ptHead
                                  * *(float *)&ptQTask[3].tQTaskRefList.ptHead
                                  + *(float *)&ptQTask[8].ptParent * *(float *)&ptQTask[3].tQTaskRefList.ptMiddle
                                  + *(float *)&ptQTask[8].tQTaskChildren.ptHead
                                  * *(float *)&ptQTask[3].tQTaskChildren.ptTail;
    Real32x9_Multiply_tTemp.tY.vZ = *(float *)&ptQTask[8].tQTaskRefList.ptMiddle
                                  * *(float *)&ptQTask[3].tQTaskRefList.ptHead
                                  + *(float *)&ptQTask[8].eQTaskType * *(float *)&ptQTask[3].tQTaskRefList.ptMiddle
                                  + *(float *)&ptQTask[8].tQTaskChildren.ptMiddle
                                  * *(float *)&ptQTask[3].tQTaskChildren.ptTail;
    v3 = ptQTask[9].ptNext;
    v4 = ptQTask[4].ptNext;
    Real32x9_Multiply_tTemp.tZ.vX = *(float *)&ptQTask[8].tQTaskRefList.ptTail * *(float *)&ptQTask[3].eQTaskType
                                  + *(float *)&ptQTask[8].tQTaskChildren.ptTail * *(float *)&ptQTask[3].ptParent
                                  + *(float *)&ptQTask[8].ptPrev * *(float *)&ptQTask[3].tQTaskRefList.ptTail;
    Real32x9_Multiply_tTemp.tZ.vY = *(float *)&ptQTask[8].ptParent * *(float *)&ptQTask[3].eQTaskType
                                  + *(float *)&ptQTask[8].tQTaskChildren.ptHead
                                  * *(float *)&ptQTask[3].tQTaskRefList.ptTail
                                  + *(float *)&ptQTask[3].ptParent * *(float *)&ptQTask[8].tQTaskRefList.ptHead;
    v5 = *(float *)&ptQTask[8].eQTaskType * *(float *)&ptQTask[3].eQTaskType
       + *(float *)&ptQTask[8].tQTaskChildren.ptMiddle * *(float *)&ptQTask[3].tQTaskRefList.ptTail;
    v6 = *(float *)&ptQTask[3].ptParent * *(float *)&ptQTask[8].tQTaskRefList.ptMiddle;
    Real32x9_Multiply_tTemp.nOps = (int)&v4->ptNext + (_DWORD)v3 + 1;
    Real32x9_Multiply_tTemp.tZ.vZ = v5 + v6;
    qmemcpy(&ptQTask[3].ptPrev, &Real32x9_Multiply_tTemp, sizeof(struct QTask_s));
  }
  else
  {
    QTask_Delete(ptQTask);
  }
}

void __cdecl sub_533580(struct QTask_s *a1)
{
  struct QTask_s *ptMiddle; // ecx
  struct QTask_s *ptTail; // ecx

  ptMiddle = a1[2].tQTaskChildren.ptMiddle;
  if ( ptMiddle )
    ptMiddle[2].tQTaskChildren.ptTail = a1[2].tQTaskChildren.ptTail;
  else
    Game_ptGame->ptWorld->ptManualRedrawList = (struct DynCubeObj_s *)a1[2].tQTaskChildren.ptTail;
  ptTail = a1[2].tQTaskChildren.ptTail;
  if ( ptTail )
    ptTail[2].tQTaskChildren.ptMiddle = a1[2].tQTaskChildren.ptMiddle;
}

void __cdecl sub_5335B0(struct QTask_s *a1, void *a2)
{
  ((void (__cdecl *)(struct QTask_s *, _DWORD))QTask_aatQTaskFinalEvent[5][RigidDynCubeObj_eQTaskType].pfHandler)(a1, 0);
}

// source: j/0/weapons/guncasing.c:162  [anchor-strings]
void __cdecl GunCasing_Open()
{
  unsigned __int16 v0; // si

  v0 = QTask_NewQTaskType("GunCasing", 376, RigidDynCubeObj_eQTaskType, 50, 0);
  GunCasing_eQTaskType = v0;
  QTask_LinkQTaskEventHandlerFn(v0, 0, GunCasing_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 1, GunCasing_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 2, sub_533580);
  QTask_LinkQTaskEventHandlerFn(v0, 5, (void (__cdecl *)(struct QTask_s *, void *))sub_5335B0);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    GameFunctions_eWeaponCollisionEvaluateQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))GameFunctions_WeaponCollisionEvaluateDiscardHandler);
}

// source: j/0/weapons/guncasing.c:185  [size]
void __cdecl GunCasing_Close()
{
  QTask_DeleteQTaskType(GunCasing_eQTaskType);
}

// source: j/0/weapons/guncasing.c:199  [size]
unsigned __int16 __cdecl GunCasign_GetQTaskType()
{
  return GunCasing_eQTaskType;
}

// source: j/0/weapons/guncasing.c:218  [anchor-callee]
struct QTask_s *__cdecl GunCasing_New(
        struct QTask_s *ptParent,
        struct real64x3_t *ptPos,
        struct real32x3_t *ptSpeed,
        struct real32x9_t *ptOrientation,
        char *zModel,
        int ltcg_arg4)
{
  struct QTask_s *v6; // ebx
  struct LODVirModel_s *LODVirModelExistsFn; // eax
  struct Game_s *v8; // eax
  unsigned int v9; // esi
  int v10; // edi
  unsigned int v11; // edx
  int v12; // esi
  unsigned int v13; // edx
  unsigned int v14; // ebp
  char v15; // cl
  int v16; // edi
  int v17; // esi
  unsigned int v18; // ebp
  unsigned int v19; // esi
  int v20; // edx
  int v21; // edi
  unsigned int v22; // ebp
  float ptDest; // [esp+0h] [ebp-1Ch]
  float vAlpha; // [esp+4h] [ebp-18h]
  float vBeta; // [esp+8h] [ebp-14h]

  v6 = QTask_NewFn(ptParent, GunCasing_eQTaskType, nullptr);
  LODVirModelExistsFn = MTP_GetLODVirModelExistsFn(zModel);
  if ( LODVirModelExistsFn != *(struct LODVirModel_s **)&v6[2].eQTaskType )
  {
    ModelObj_SetLODVirModel((struct ModelObj_s *)v6, LODVirModelExistsFn, false);
    v6[7].tQTaskRefList.ptHead = nullptr;
    v6[7].tQTaskRefList.ptMiddle = nullptr;
    v6[7].tQTaskRefList.ptTail = nullptr;
    v6[7].ptParent = nullptr;
    *(_DWORD *)&v6[7].eQTaskType = 0;
  }
  if ( ltcg_arg4 )
    v6[7].ptPrev = nullptr;
  qmemcpy(&v6[1], ptPos, 0x18u);
  *(struct real32x3_t *)&v6[9].ptPrev = *ptSpeed;
  v8 = Game_ptGame;
  qmemcpy(&v6[3].ptPrev, ptOrientation, sizeof(struct QTask_s));
  v6[8].ptNext = (struct QTask_s *)19;
  v9 = v8->tRunRandomState.anRandom[1];
  v10 = (v8->tRunRandomState.anRandom[0] >> 7) ^ v8->tRunRandomState.anRandom[2];
  v11 = v8->tRunRandomState.anRandom[0];
  v8->tRunRandomState.anRandom[2] = v10;
  v12 = v10 ^ v9;
  v8->tRunRandomState.anRandom[1] = v12;
  v13 = v12 + v11;
  v8->tRunRandomState.anRandom[0] = v13;
  v14 = v8->tRunRandomState.anRandom[0];
  v15 = v13;
  v16 = (v13 >> 7) ^ v10;
  v17 = v16 ^ v8->tRunRandomState.anRandom[1];
  v8->tRunRandomState.anRandom[1] = v17;
  v18 = v17 + v14;
  v8->tRunRandomState.anRandom[0] = v18;
  v8->tRunRandomState.anRandom[2] = v16;
  v19 = v18;
  v20 = (v18 >> 7) ^ v16;
  v21 = v20 ^ v8->tRunRandomState.anRandom[1];
  v8->tRunRandomState.anRandom[2] = v20;
  v22 = v21 + v8->tRunRandomState.anRandom[0];
  v8->tRunRandomState.anRandom[1] = v21;
  v8->tRunRandomState.anRandom[0] = v22;
  vBeta = (double)(v22 % 5) * 0.01745329238474369;
  vAlpha = (double)(v19 % 5) * 0.01745329238474369;
  ptDest = (double)(v15 & 1) * 0.01745329238474369;
  Real32x9_Create((struct real32x9_t *)&v6[8].ptPrev, ptDest, vAlpha, vBeta);
  return v6;
}

void __cdecl sub_533810(struct QTask_s *a1, void *a2)
{
  ((void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[0][MenuWindow_eQTaskType].pfHandler)(a1, a2);
  LOBYTE(a1[68].tQTaskRefList.ptMiddle) = 0;
  a1[1].ptNext = (struct QTask_s *)320;
  a1[1].ptPrev = (struct QTask_s *)240;
  a1[1].tQTaskChildren.ptHead = (struct QTask_s *)256;
  a1[1].tQTaskChildren.ptMiddle = (struct QTask_s *)192;
  *(_DWORD *)&a1[59].eQTaskType = 0;
  a1[60].ptNext = nullptr;
  a1[60].tQTaskRefList.ptHead = nullptr;
  a1[1].tQTaskRefList.ptTail = (struct QReference_s *)1;
  a1[1].ptParent = (struct QTask_s *)1;
  a1[60].tQTaskChildren.ptTail = (struct QTask_s *)1065353216;
  a1[60].ptPrev = (struct QTask_s *)1065353216;
  a1[60].tQTaskChildren.ptHead = (struct QTask_s *)1065353216;
  a1[60].tQTaskChildren.ptMiddle = (struct QTask_s *)1065353216;
  a1[60].tQTaskRefList.ptMiddle = nullptr;
  a1[60].tQTaskRefList.ptTail = nullptr;
  a1[60].ptParent = nullptr;
  a1[62].tQTaskRefList.ptHead = nullptr;
  a1[62].tQTaskRefList.ptMiddle = nullptr;
  a1[62].tQTaskRefList.ptTail = nullptr;
  a1[62].ptParent = nullptr;
  a1[64].tQTaskRefList.ptHead = nullptr;
  a1[64].tQTaskRefList.ptMiddle = nullptr;
  a1[64].tQTaskRefList.ptTail = nullptr;
  a1[64].ptParent = nullptr;
  a1[66].tQTaskRefList.ptHead = nullptr;
  a1[66].tQTaskRefList.ptMiddle = nullptr;
  a1[66].tQTaskRefList.ptTail = nullptr;
  a1[66].ptParent = nullptr;
  a1[68].tQTaskRefList.ptHead = nullptr;
}
