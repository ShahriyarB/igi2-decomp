/* j/0/weapons/stationarygun.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/weapons/stationarygun.c:66  [anchor-mhash]
int __cdecl StationaryGun_Fire(struct QTask_s *ptQTask, int isFire)
{
  double v2; // st7
  double v3; // st6
  float vGamma; // [esp+0h] [ebp-4h]

  if ( isFire )
  {
    Weapon_Fire(*(struct QTask_s **)&ptQTask[14].eQTaskType, 0);
    isFire = *(_DWORD *)&ptQTask[14].eQTaskType;
    if ( *(_DWORD *)(isFire + 56) == 1 )
    {
      v2 = *(float *)(isFire + 84);
      v3 = *(float *)(isFire + 76);
      vGamma = *(float *)(isFire + 88);
      *(float *)&ptQTask[13].tQTaskRefList.ptHead = (v2 + vGamma) * 0.4000000059604645
                                                  + *(float *)&ptQTask[13].tQTaskRefList.ptHead;
      *(float *)&ptQTask[13].tQTaskRefList.ptTail = v2 * 0.01745329238474369 + *(float *)&ptQTask[13].tQTaskRefList.ptTail;
      *(float *)&ptQTask[13].ptParent = vGamma * 0.01745329238474369 + *(float *)&ptQTask[13].ptParent;
      *(float *)&ptQTask[13].tQTaskRefList.ptMiddle = v3;
    }
  }
  return isFire;
}

// source: j/0/weapons/stationarygun.c:99  [size]
void __cdecl StationaryGun_GetWeaponObjectHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *((_DWORD *)pxContext + 2) = 0;
  *(_DWORD *)pxContext = ptQTask[8].ptNext;
}

// source: j/0/weapons/stationarygun.c:119  [size]
void __cdecl StationaryGun_GetWeaponPrecisionHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = ptQTask[13].tQTaskRefList.ptHead;
}

// source: j/0/weapons/stationarygun.c:142  [size]
void __cdecl StationaryGun_StatusDisplayHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ((void (__cdecl *)(_DWORD))QTask_aatQTaskFinalEvent[StatusScreen_eStatusDisplayQTaskEvent][*(unsigned __int16 *)(*(_DWORD *)&ptQTask[14].eQTaskType + 36)].pfHandler)(*(_DWORD *)&ptQTask[14].eQTaskType);
}

// source: j/0/weapons/stationarygun.c:161  [anchor-mhash]
void __cdecl StationaryGun_PositionWeapon(struct QTask_s *ptQTask, struct real32x9_t *ptParentOrientation)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct real32x9_t Real32x9_Multiply_tTemp; };
    struct { char igi2_o1[40]; struct real64x3_t tAttachPos; };
    struct { char igi2_o2[68]; struct real32x3_t Real32x3_Rotate_tTemp; };
    struct { char igi2_o3[80]; struct SetPositionContext_s tSetPositionContext; };
    char igi2_extent[148];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  BOOL v3; // ebx
  struct real32x9_t *v4; // eax
  struct real32x9_t *v5; // edi
  int v6; // eax
  double v7; // st7
  double v8; // st6
  struct QTask_s *ptMiddle; // edx
  struct real32x9_t *v10; // eax
  struct real32x9_t *v11; // edi
  double v12; // st7
  struct QTask_s *ptNext; // eax
  void (__cdecl *pfHandler)(struct QTask_s *, struct SetPositionContext_s *); // ecx
  struct QReference_s *ptHead; // eax
  struct QTask_s *v16; // ebp
  double v17; // st7
  struct QReference_s *ptPrev; // eax
  double v19; // st6
  double v20; // st5

  v3 = 1;
  v4 = Real32x9_Create((struct real32x9_t *)&ptQTask[3].ptPrev, 0.0, 0.0, *(float *)&ptQTask[14].tQTaskChildren.ptTail);
  igi2_frame.Real32x9_Multiply_tTemp.tX.vX = *(float *)&ptQTask[8].ptParent * v4->tX.vX
                                + *(float *)&ptQTask[3].tQTaskRefList.ptTail * *(float *)&ptQTask[9].ptNext
                                + *(float *)&ptQTask[3].tQTaskChildren.ptTail * *(float *)&ptQTask[8].eQTaskType;
  igi2_frame.Real32x9_Multiply_tTemp.tX.vY = *(float *)&ptQTask[8].eQTaskType * *(float *)&ptQTask[3].tQTaskRefList.ptHead
                                + *(float *)&ptQTask[8].ptParent * *(float *)&ptQTask[3].tQTaskChildren.ptHead
                                + *(float *)&ptQTask[3].ptParent * *(float *)&ptQTask[9].ptNext;
  igi2_frame.Real32x9_Multiply_tTemp.tX.vZ = *(float *)&ptQTask[8].eQTaskType * *(float *)&ptQTask[3].tQTaskRefList.ptMiddle
                                + *(float *)&ptQTask[8].ptParent * *(float *)&ptQTask[3].tQTaskChildren.ptMiddle
                                + *(float *)&ptQTask[3].eQTaskType * *(float *)&ptQTask[9].ptNext;
  igi2_frame.Real32x9_Multiply_tTemp.tY.vX = *(float *)&ptQTask[9].tQTaskChildren.ptMiddle
                                * *(float *)&ptQTask[3].tQTaskRefList.ptTail
                                + *(float *)&ptQTask[9].ptPrev * v4->tX.vX
                                + *(float *)&ptQTask[3].tQTaskChildren.ptTail
                                * *(float *)&ptQTask[9].tQTaskChildren.ptHead;
  igi2_frame.Real32x9_Multiply_tTemp.tY.vY = *(float *)&ptQTask[9].tQTaskChildren.ptHead
                                * *(float *)&ptQTask[3].tQTaskRefList.ptHead
                                + *(float *)&ptQTask[9].tQTaskChildren.ptMiddle * *(float *)&ptQTask[3].ptParent
                                + *(float *)&ptQTask[9].ptPrev * *(float *)&ptQTask[3].tQTaskChildren.ptHead;
  igi2_frame.Real32x9_Multiply_tTemp.tY.vZ = *(float *)&ptQTask[9].tQTaskChildren.ptHead
                                * *(float *)&ptQTask[3].tQTaskRefList.ptMiddle
                                + *(float *)&ptQTask[9].tQTaskChildren.ptMiddle * *(float *)&ptQTask[3].eQTaskType
                                + *(float *)&ptQTask[9].ptPrev * *(float *)&ptQTask[3].tQTaskChildren.ptMiddle;
  igi2_frame.Real32x9_Multiply_tTemp.tZ.vX = *(float *)&ptQTask[3].tQTaskRefList.ptTail
                                * *(float *)&ptQTask[9].tQTaskRefList.ptMiddle
                                + v4->tX.vX * *(float *)&ptQTask[9].tQTaskChildren.ptTail
                                + *(float *)&ptQTask[9].tQTaskRefList.ptHead
                                * *(float *)&ptQTask[3].tQTaskChildren.ptTail;
  v5 = v4;
  v6 = *(_DWORD *)&ptQTask[2].eQTaskType;
  v7 = *(float *)&ptQTask[3].ptParent * *(float *)&ptQTask[9].tQTaskRefList.ptMiddle
     + *(float *)&ptQTask[3].tQTaskChildren.ptHead * *(float *)&ptQTask[9].tQTaskChildren.ptTail;
  v8 = *(float *)&ptQTask[9].tQTaskRefList.ptHead * *(float *)&ptQTask[3].tQTaskRefList.ptHead;
  igi2_frame.Real32x9_Multiply_tTemp.nOps = (int)&ptQTask[4].ptNext->ptNext + (unsigned int)ptQTask[9].tQTaskRefList.ptTail + 1;
  igi2_frame.Real32x9_Multiply_tTemp.tZ.vY = v7 + v8;
  igi2_frame.Real32x9_Multiply_tTemp.tZ.vZ = *(float *)&ptQTask[3].eQTaskType * *(float *)&ptQTask[9].tQTaskRefList.ptMiddle
                                + *(float *)&ptQTask[3].tQTaskChildren.ptMiddle
                                * *(float *)&ptQTask[9].tQTaskChildren.ptTail
                                + *(float *)&ptQTask[9].tQTaskRefList.ptHead
                                * *(float *)&ptQTask[3].tQTaskRefList.ptMiddle;
  qmemcpy(v5, &igi2_frame.Real32x9_Multiply_tTemp, sizeof(struct real32x9_t));
  if ( v6 )
    v3 = (__int16)(*(_WORD *)(*(_DWORD *)(*(_DWORD *)(*(_DWORD *)v6 + 12) + 12) + 124)) >= 1;
  GameFunctions_GetMagicVertex(&igi2_frame.tAttachPos, ptQTask, v3);
  ptMiddle = ptQTask[14].tQTaskChildren.ptMiddle;
  qmemcpy(&ptQTask[9].ptParent, &igi2_frame.tAttachPos, 0x18u);
  v10 = Real32x9_Create(
          (struct real32x9_t *)&ptQTask[10].tQTaskChildren.ptTail,
          *(float *)&ptMiddle,
          0.0,
          *(float *)&ptQTask[14].tQTaskChildren.ptTail);
  igi2_frame.Real32x9_Multiply_tTemp.tX.vX = *(float *)&ptQTask[11].ptNext * *(float *)&ptQTask[9].ptNext
                                + *(float *)&ptQTask[8].ptParent * v10->tX.vX
                                + *(float *)&ptQTask[10].tQTaskRefList.ptTail * *(float *)&ptQTask[8].eQTaskType;
  igi2_frame.Real32x9_Multiply_tTemp.tX.vY = *(float *)&ptQTask[8].ptParent * *(float *)&ptQTask[10].tQTaskRefList.ptHead
                                + *(float *)&ptQTask[8].eQTaskType * *(float *)&ptQTask[10].ptParent
                                + *(float *)&ptQTask[11].ptPrev * *(float *)&ptQTask[9].ptNext;
  igi2_frame.Real32x9_Multiply_tTemp.tX.vZ = *(float *)&ptQTask[8].ptParent * *(float *)&ptQTask[10].tQTaskRefList.ptMiddle
                                + *(float *)&ptQTask[8].eQTaskType * *(float *)&ptQTask[10].eQTaskType
                                + *(float *)&ptQTask[11].tQTaskChildren.ptHead * *(float *)&ptQTask[9].ptNext;
  igi2_frame.Real32x9_Multiply_tTemp.tY.vX = *(float *)&ptQTask[11].ptNext * *(float *)&ptQTask[9].tQTaskChildren.ptMiddle
                                + *(float *)&ptQTask[9].ptPrev * v10->tX.vX
                                + *(float *)&ptQTask[10].tQTaskRefList.ptTail
                                * *(float *)&ptQTask[9].tQTaskChildren.ptHead;
  igi2_frame.Real32x9_Multiply_tTemp.tY.vY = *(float *)&ptQTask[9].tQTaskChildren.ptHead * *(float *)&ptQTask[10].ptParent
                                + *(float *)&ptQTask[9].tQTaskChildren.ptMiddle * *(float *)&ptQTask[11].ptPrev
                                + *(float *)&ptQTask[9].ptPrev * *(float *)&ptQTask[10].tQTaskRefList.ptHead;
  igi2_frame.Real32x9_Multiply_tTemp.tY.vZ = *(float *)&ptQTask[9].tQTaskChildren.ptHead * *(float *)&ptQTask[10].eQTaskType
                                + *(float *)&ptQTask[9].tQTaskChildren.ptMiddle
                                * *(float *)&ptQTask[11].tQTaskChildren.ptHead
                                + *(float *)&ptQTask[9].ptPrev * *(float *)&ptQTask[10].tQTaskRefList.ptMiddle;
  v11 = v10;
  v12 = *(float *)&ptQTask[11].ptNext * *(float *)&ptQTask[9].tQTaskRefList.ptMiddle
      + *(float *)&ptQTask[9].tQTaskRefList.ptHead * *(float *)&ptQTask[10].tQTaskRefList.ptTail
      + v10->tX.vX * *(float *)&ptQTask[9].tQTaskChildren.ptTail;
  ptNext = ptQTask[8].ptNext;
  igi2_frame.Real32x9_Multiply_tTemp.nOps = (int)&ptQTask[11].tQTaskChildren.ptMiddle->ptNext
                               + (unsigned int)ptQTask[9].tQTaskRefList.ptTail
                               + 1;
  igi2_frame.Real32x9_Multiply_tTemp.tZ.vX = v12;
  igi2_frame.Real32x9_Multiply_tTemp.tZ.vY = *(float *)&ptQTask[9].tQTaskRefList.ptHead * *(float *)&ptQTask[10].ptParent
                                + *(float *)&ptQTask[11].ptPrev * *(float *)&ptQTask[9].tQTaskRefList.ptMiddle
                                + *(float *)&ptQTask[10].tQTaskRefList.ptHead
                                * *(float *)&ptQTask[9].tQTaskChildren.ptTail;
  igi2_frame.Real32x9_Multiply_tTemp.tZ.vZ = *(float *)&ptQTask[9].tQTaskRefList.ptHead * *(float *)&ptQTask[10].eQTaskType
                                + *(float *)&ptQTask[11].tQTaskChildren.ptHead
                                * *(float *)&ptQTask[9].tQTaskRefList.ptMiddle
                                + *(float *)&ptQTask[10].tQTaskRefList.ptMiddle
                                * *(float *)&ptQTask[9].tQTaskChildren.ptTail;
  qmemcpy(v11, &igi2_frame.Real32x9_Multiply_tTemp, sizeof(struct real32x9_t));
  if ( ptNext )
  {
    qmemcpy(&igi2_frame.tSetPositionContext, &ptQTask[9].ptParent, 0x18u);
    qmemcpy(&igi2_frame.tSetPositionContext.tOrientation, &igi2_frame.Real32x9_Multiply_tTemp, sizeof(igi2_frame.tSetPositionContext.tOrientation));
    pfHandler = (void (__cdecl *)(struct QTask_s *, struct SetPositionContext_s *))QTask_aatQTaskFinalEvent[7][ptNext->eQTaskType].pfHandler;
    if ( pfHandler )
      pfHandler(ptNext, &igi2_frame.tSetPositionContext);
  }
  ptHead = ptQTask[14].tQTaskRefList.ptHead;
  if ( ptHead )
  {
    v16 = ptQTask[8].ptNext;
    if ( v16 )
    {
      qmemcpy(&igi2_frame.Real32x9_Multiply_tTemp, &v16[3].ptPrev, sizeof(igi2_frame.Real32x9_Multiply_tTemp));
      v17 = igi2_frame.Real32x9_Multiply_tTemp.tX.vZ * 819.2000122070312
          - igi2_frame.Real32x9_Multiply_tTemp.tX.vY * 2048.0
          + igi2_frame.Real32x9_Multiply_tTemp.tX.vX * 0.0;
      ptPrev = ptHead[111].ptPrev;
      v19 = igi2_frame.Real32x9_Multiply_tTemp.tY.vZ * 819.2000122070312;
      v20 = igi2_frame.Real32x9_Multiply_tTemp.tY.vY * 2048.0;
      BYTE2(ptPrev[42].ptPrev) = 1;
      igi2_frame.Real32x3_Rotate_tTemp.vZ = igi2_frame.Real32x9_Multiply_tTemp.tZ.vZ * 819.2000122070312
                               - igi2_frame.Real32x9_Multiply_tTemp.tZ.vY * 2048.0
                               + igi2_frame.Real32x9_Multiply_tTemp.tZ.vX * 0.0;
      igi2_frame.tAttachPos.vX = v17 + igi2_frame.tAttachPos.vX;
      igi2_frame.tAttachPos.vY = v19 - v20 + igi2_frame.Real32x9_Multiply_tTemp.tY.vX * 0.0 + igi2_frame.tAttachPos.vY;
      igi2_frame.tAttachPos.vZ = igi2_frame.Real32x3_Rotate_tTemp.vZ + igi2_frame.tAttachPos.vZ;
      qmemcpy(&ptPrev[42].pxObject, &igi2_frame.tAttachPos, 0x18u);
      qmemcpy(&ptPrev[44].pxObject, &igi2_frame.Real32x9_Multiply_tTemp, 0x28u);
    }
  }
}

// source: j/0/weapons/stationarygun.c:252  [anchor-mhash]
void __cdecl StationaryGun_LimitRotation(struct QTask_s *ptQTask)
{
  double v1; // st7
  unsigned int v2; // eax
  double v3; // st7
  double v4; // st7
  double v5; // st7
  double v6; // st7
  struct QReference_s *ptTail; // eax
  float v8; // [esp+0h] [ebp-4h]

  v1 = *(float *)&ptQTask[13].ptPrev * 0.01745329238474369;
  v2 = (int)ptQTask[14].tQTaskRefList.ptTail & 0xFFFFFFFC;
  ptQTask[14].tQTaskRefList.ptTail = (struct QReference_s *)v2;
  if ( v1 <= *(float *)&ptQTask[14].ptPrev )
  {
    v3 = *(float *)&ptQTask[13].ptNext * 0.01745329238474369;
    if ( v3 < *(float *)&ptQTask[14].ptPrev )
    {
      *(float *)&ptQTask[14].ptPrev = v3;
      ptQTask[14].tQTaskRefList.ptTail = (struct QReference_s *)(v2 | 1);
    }
  }
  else
  {
    *(float *)&ptQTask[14].ptPrev = v1;
    ptQTask[14].tQTaskRefList.ptTail = (struct QReference_s *)(v2 | 1);
  }
  if ( *(float *)&ptQTask[14].tQTaskChildren.ptHead >= -6.283185307179589 )
  {
    if ( *(float *)&ptQTask[14].tQTaskChildren.ptHead <= 6.283185307179589 )
      goto LABEL_10;
    v4 = *(float *)&ptQTask[14].tQTaskChildren.ptHead - 6.2831854820251465;
  }
  else
  {
    v4 = *(float *)&ptQTask[14].tQTaskChildren.ptHead + 6.2831854820251465;
  }
  *(float *)&ptQTask[14].tQTaskChildren.ptHead = v4;
LABEL_10:
  v5 = *(float *)&ptQTask[13].tQTaskChildren.ptHead * 0.01745329238474369;
  v8 = v5;
  v6 = -v5;
  if ( v6 <= *(float *)&ptQTask[14].tQTaskChildren.ptHead )
  {
    if ( *(float *)&ptQTask[14].tQTaskChildren.ptHead > (double)v8 )
    {
      *(float *)&ptQTask[14].tQTaskChildren.ptHead = v8;
      ptQTask[14].tQTaskRefList.ptTail = (struct QReference_s *)((int)ptQTask[14].tQTaskRefList.ptTail | 2);
    }
  }
  else
  {
    ptTail = ptQTask[14].tQTaskRefList.ptTail;
    *(float *)&ptQTask[14].tQTaskChildren.ptHead = v6;
    ptQTask[14].tQTaskRefList.ptTail = (struct QReference_s *)((unsigned int)ptTail | 2);
  }
}

// source: j/0/weapons/stationarygun.c:306  [anchor-mhash]
void __cdecl StationaryGun_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  double v2; // st7
  bool v3; // c0
  bool v4; // c3
  double v5; // st7
  double v6; // st7
  int *v7; // eax
  int v8; // eax
  double v9; // st6
  int v10; // esi
  int v11; // eax
  struct QReference_s *v12; // ecx
  struct QTask_s *v13; // eax
  int v14; // edi
  struct QReference_s *v15; // eax
  __int16 v16; // cx
  float ptDynCubeObj; // [esp+0h] [ebp-1Ch]

  QTaskList_Register(GameFunctions_ptActivateQTaskList, (struct QTaskList_s *)ptQTask);
  ModelObj_Init((struct ModelObj_s *)ptQTask, Game_ptGame->ptWorld, nullptr);
  ptQTask[7].tQTaskChildren.ptHead = nullptr;
  ptQTask[7].tQTaskChildren.ptMiddle = (struct QTask_s *)2;
  ptQTask[7].tQTaskRefList.ptHead = nullptr;
  ptQTask[7].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[7].tQTaskRefList.ptTail = nullptr;
  ptQTask[7].ptParent = nullptr;
  *(_DWORD *)&ptQTask[7].eQTaskType = 0;
  v2 = *(float *)&ptQTask[6].tQTaskChildren.ptHead;
  v3 = v2 < *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
  v4 = v2 == *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
  ptQTask[8].tQTaskChildren.ptHead = nullptr;
  ptQTask[8].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[8].tQTaskChildren.ptTail = nullptr;
  ptQTask[8].tQTaskRefList.ptHead = nullptr;
  ptQTask[8].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[8].tQTaskRefList.ptTail = nullptr;
  if ( v3 || v4 )
    v5 = *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
  else
    v5 = *(float *)&ptQTask[6].tQTaskChildren.ptHead;
  if ( v5 >= *(float *)&ptQTask[6].ptPrev )
  {
    if ( *(float *)&ptQTask[6].tQTaskChildren.ptHead <= (double)*(float *)&ptQTask[6].tQTaskChildren.ptMiddle )
      v6 = *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
    else
      v6 = *(float *)&ptQTask[6].tQTaskChildren.ptHead;
  }
  else
  {
    v6 = *(float *)&ptQTask[6].ptPrev;
  }
  v7 = *(int **)&ptQTask[2].eQTaskType;
  if ( v7 && (v8 = *v7) != 0 )
    v9 = *(float *)(*(_DWORD *)(*(_DWORD *)(v8 + 12) + 12) + 120);
  else
    v9 = 1.0;
  ptDynCubeObj = v6 * v9;
  World_RegisterDynCubeObjFirstTimeRadius(
    Game_ptGame->ptWorld,
    (struct DynCubeObj_s *)ptQTask,
    (struct real64x3_t *)&ptQTask[8].tQTaskChildren,
    ptDynCubeObj,
    WORLD_DYNCUBETREE_CATEGORY_STATIONARY);
  if ( ptQTask[7].tQTaskChildren.ptTail )
  {
    ptQTask[2].tQTaskRefList.ptHead = nullptr;
    ptQTask[2].tQTaskRefList.ptMiddle = nullptr;
  }
  else
  {
    SectorObject_RegisterInteriorDynCubeObjSpecificSectorObject(
      (struct World_s *)ptQTask[2].ptParent,
      nullptr,
      (struct DynCubeObj_s *)ptQTask,
      (struct real64x3_t *)&ptQTask[1]);
  }
  ptQTask[8].ptParent = (struct QTask_s *)1065353216;
  *(_DWORD *)&ptQTask[8].eQTaskType = 0;
  ptQTask[9].ptNext = nullptr;
  ptQTask[9].ptPrev = nullptr;
  ptQTask[9].tQTaskChildren.ptHead = (struct QTask_s *)1065353216;
  ptQTask[9].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[9].tQTaskChildren.ptTail = nullptr;
  ptQTask[9].tQTaskRefList.ptHead = nullptr;
  ptQTask[9].tQTaskRefList.ptMiddle = (struct QReference_s *)1065353216;
  ptQTask[9].tQTaskRefList.ptTail = nullptr;
  qmemcpy(&ptQTask[3].ptPrev, &ptQTask[8].ptParent, sizeof(struct QTask_s));
  v10 = -1;
  ptQTask[8].ptNext = nullptr;
  ptQTask[14].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[14].tQTaskChildren.ptTail = nullptr;
  ptQTask[14].ptPrev = nullptr;
  ptQTask[14].tQTaskChildren.ptHead = nullptr;
  *(_DWORD *)&ptQTask[13].eQTaskType = 0;
  ptQTask[14].ptNext = nullptr;
  ptQTask[14].tQTaskRefList.ptHead = nullptr;
  ptQTask[14].tQTaskRefList.ptMiddle = (struct QReference_s *)-1;
  ptQTask[14].tQTaskRefList.ptTail = nullptr;
  LOBYTE(ptQTask[14].ptParent) = 0;
  ptQTask[13].tQTaskChildren.ptTail = nullptr;
  ptQTask[13].tQTaskRefList.ptHead = nullptr;
  ptQTask[13].tQTaskRefList.ptMiddle = (struct QReference_s *)1065353216;
  ptQTask[13].tQTaskRefList.ptTail = nullptr;
  ptQTask[13].ptParent = nullptr;
  LOBYTE(ptQTask[11].tQTaskChildren.ptTail) = 0;
  sprintf((char *const)&ptQTask[12].tQTaskChildren, "WEAPON_ID_M2HB");
  ptQTask[13].ptNext = (struct QTask_s *)1103626240;
  ptQTask[13].ptPrev = (struct QTask_s *)-1043857408;
  ptQTask[13].tQTaskChildren.ptHead = (struct QTask_s *)1119092736;
  ptQTask[13].tQTaskChildren.ptMiddle = (struct QTask_s *)-1;
  v11 = 0;
  while ( 1 )
  {
    v12 = Level_atLevelQTaskID[v11];
    if ( v12 )
    {
      if ( v12->pxObject == ptQTask->ptParent )
        break;
    }
    if ( ++v11 >= 4096 )
      goto LABEL_22;
  }
  v10 = v11;
LABEL_22:
  v13 = QTask_NewFn(ptQTask, Weapon_eQTaskType, nullptr);
  v13[16].tQTaskRefList.ptTail = (struct QReference_s *)v10;
  *(_DWORD *)&ptQTask[14].eQTaskType = v13;
  v13[2].tQTaskRefList.ptHead = (struct QReference_s *)1050253722;
  v14 = *(_DWORD *)&ptQTask[14].eQTaskType;
  v15 = *(struct QReference_s **)(v14 + 96);
  if ( v15 )
    QReference_Delete(v15, &QTask_tQTaskRefPool);
  v16 = Attach_eAttachEvent;
  *(_DWORD *)(v14 + 96) = 0;
  *(_DWORD *)(*(_DWORD *)&ptQTask[14].eQTaskType + 92) = -1;
  ptQTask[5].tQTaskChildren.ptTail = (struct QTask_s *)-1;
  ptQTask[5].tQTaskRefList.ptHead = nullptr;
  QTask_TriggerQTaskEventParent(ptQTask, v16, &ptQTask[5].tQTaskChildren.ptTail);
  ModelObj_CalcRelativePosAndOrientation((struct ModelObj_s *)ptQTask);
}

// source: j/0/weapons/stationarygun.c:388  [anchor-mhash]
void __cdecl StationaryGun_UpdateAttachmentHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptNext; // eax
  struct QTask_s *ptHead; // eax
  int v3; // edx
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
    ModelObj_UpdateAttachment((struct ModelObj_s *)ptQTask);
    qmemcpy(&ptQTask[8].ptParent, &ptQTask[3].ptPrev, sizeof(struct QTask_s));
    qmemcpy(&ptQTask[8].tQTaskChildren, &ptQTask[1], 0x18u);
    StationaryGun_PositionWeapon(ptQTask, (struct real32x9_t *)&ptQTask[3].ptPrev);
    ptNext = ptQTask[3].ptNext;
    if ( ptNext && (ptHead = ptNext->tQTaskChildren.ptHead, ptHead->ptNext) && (v3 = (int)ptHead) != 0 )
    {
      v4 = QTask_nProtectedQTaskStackOffset;
      do
      {
        if ( *(_DWORD *)v3 )
          v5 = **(_DWORD **)v3 != 0 ? *(struct QTask_s **)v3 : nullptr;
        else
          v5 = nullptr;
        v6 = Attach_eUpdateAttachmentEvent;
        QTask_atProtectedQTaskStack[v4].ptQTask = v5;
        pfHandler = (void (__cdecl *)(int))QTask_aatQTaskFinalEvent[v6][*(unsigned __int16 *)(v3 + 36)].pfHandler;
        v8 = v4 + 1;
        QTask_nProtectedQTaskStackOffset = v8;
        if ( pfHandler )
        {
          pfHandler(v3);
          v8 = QTask_nProtectedQTaskStackOffset;
        }
        v3 = dword_849C7DC[v8];
        v4 = v8 - 1;
        QTask_nProtectedQTaskStackOffset = v4;
      }
      while ( v3 );
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

// source: j/0/weapons/stationarygun.c:428  [anchor-mhash]
void __cdecl StationaryGun_RunHandler(struct QTask_s *ptQTask)
{
  int v2; // eax
  struct QReference_s *nTicks; // ecx
  double v4; // st7
  struct QReference_s *ptHead; // edi
  double v6; // st7
  double v7; // st6
  char v8; // bl
  int v9; // eax
  double v10; // st7
  double v11; // st7
  double v12; // st6
  double v13; // st6
  struct QTask_s *v14; // ecx
  int v15; // edx
  struct QTask_s *v16; // eax
  void (__cdecl *pfHandler)(struct QTask_s *); // eax
  int v18; // edx
  struct QTask_s *ptQTaska = *(struct QTask_s * *)&ptQTask; // [esp+14h] [ebp+4h] ARGSLOT

  v2 = *(_DWORD *)(*(_DWORD *)&ptQTask[14].eQTaskType + 44);
  if ( v2 )
    v2 = *(_DWORD *)(v2 + 16);
  nTicks = (struct QReference_s *)Flow_ptFlow->nTicks;
  if ( ptQTask[14].tQTaskRefList.ptMiddle != nTicks )
  {
    ptQTask[14].tQTaskRefList.ptMiddle = nTicks;
    v4 = *(float *)(v2 + 840);
    ptQTask[13].tQTaskChildren.ptTail = *(struct QTask_s **)(v2 + 840);
    ptHead = ptQTask[14].tQTaskRefList.ptHead;
    *(float *)&ptQTask[13].tQTaskRefList.ptHead = (v4 - *(float *)&ptQTask[13].tQTaskRefList.ptHead) * 0.4000000059604645
                                                + *(float *)&ptQTask[13].tQTaskRefList.ptHead;
    v6 = -*(float *)&ptQTask[13].tQTaskRefList.ptTail * *(float *)&ptQTask[13].tQTaskRefList.ptMiddle
       + *(float *)&ptQTask[13].tQTaskRefList.ptTail;
    *(float *)&ptQTask[13].tQTaskRefList.ptTail = v6;
    v7 = -*(float *)&ptQTask[13].ptParent * *(float *)&ptQTask[13].tQTaskRefList.ptMiddle
       + *(float *)&ptQTask[13].ptParent;
    *(float *)&ptQTask[13].ptParent = v7;
    *(float *)&ptQTask[13].eQTaskType = v6;
    *(float *)&ptQTask[14].ptNext = v7;
    if ( ptHead )
    {
      v8 = 0;
      *(float *)&ptQTask[14].ptPrev = *(float *)&ptHead[64].ptNext * 3.1415927410125732 + *(float *)&ptQTask[14].ptPrev;
      *(float *)&ptQTask[14].tQTaskChildren.ptHead = *(float *)&ptHead[63].pxObject * -3.1415927410125732
                                                   + *(float *)&ptQTask[14].tQTaskChildren.ptHead;
      StationaryGun_LimitRotation(ptQTask);
      if ( *(float *)&ptHead[65].pxObject == 0.0 )
      {
        if ( *(float *)&ptHead[44].pxObject != 0.0 )
        {
          v9 = *(_DWORD *)&ptQTask[14].eQTaskType;
          *(_DWORD *)(v9 + 112) = 1;
          *(_DWORD *)(v9 + 56) = 0;
        }
      }
      else
      {
        v8 = 1;
        ++*(int *)&ptHead[40].ptPrev;
      }
      v10 = *(float *)&ptQTask[14].ptPrev;
      ptQTask[14].tQTaskChildren.ptMiddle = ptQTask[14].ptPrev;
      ptQTaska = ptQTask[14].tQTaskChildren.ptHead;
      ptQTask[14].tQTaskChildren.ptTail = ptQTask[14].tQTaskChildren.ptHead;
      if ( !ptHead[162].pxObject )
      {
        *(float *)&ptQTask[14].tQTaskChildren.ptMiddle = v10 + *(float *)&ptQTask[14].ptNext;
        *(float *)&ptQTask[14].tQTaskChildren.ptTail = *(float *)&ptQTaska + *(float *)&ptQTask[13].eQTaskType;
      }
      *(float *)&ptQTask[13].eQTaskType = *(float *)&ptQTask[13].eQTaskType * 0.8999999761581421;
      *(float *)&ptQTask[14].ptNext = *(float *)&ptQTask[14].ptNext * 0.8999999761581421;
      StationaryGun_Fire(ptQTask, v8);
    }
    else
    {
      v11 = *(float *)&ptQTask[13].ptPrev * 0.8999999761581421 * 0.01745329238474369;
      if ( v11 <= *(float *)&ptQTask[14].tQTaskChildren.ptMiddle )
      {
        if ( v11 < *(float *)&ptQTask[14].tQTaskChildren.ptMiddle )
        {
          v13 = *(float *)&ptQTask[14].tQTaskChildren.ptMiddle - 0.0872664675116539;
          *(float *)&ptQTask[14].tQTaskChildren.ptMiddle = v13;
          if ( v13 < v11 )
            *(float *)&ptQTask[14].tQTaskChildren.ptMiddle = v11;
        }
      }
      else
      {
        v12 = *(float *)&ptQTask[14].tQTaskChildren.ptMiddle + 0.0872664675116539;
        *(float *)&ptQTask[14].tQTaskChildren.ptMiddle = v12;
        if ( v12 > v11 )
          *(float *)&ptQTask[14].tQTaskChildren.ptMiddle = v11;
      }
      ptQTask[14].ptPrev = nullptr;
      ptQTask[14].tQTaskChildren.ptHead = nullptr;
    }
    StationaryGun_PositionWeapon(ptQTask, (struct real32x9_t *)&ptQTask[3].ptPrev);
    Weapon_UpdateStatus(*(struct QTask_s **)&ptQTask[14].eQTaskType);
    v14 = ptQTask->tQTaskChildren.ptHead;
    if ( v14->ptNext && v14 )
    {
      v15 = QTask_nProtectedQTaskStackOffset;
      do
      {
        if ( v14->ptNext )
          v16 = v14->ptNext->ptNext != nullptr ? v14->ptNext : nullptr;
        else
          v16 = nullptr;
        QTask_atProtectedQTaskStack[v15].ptQTask = v16;
        pfHandler = (void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[1][v14->eQTaskType].pfHandler;
        v18 = v15 + 1;
        QTask_nProtectedQTaskStackOffset = v18;
        if ( pfHandler )
        {
          pfHandler(v14);
          v18 = QTask_nProtectedQTaskStackOffset;
        }
        v14 = (struct QTask_s *)dword_849C7DC[v18];
        v15 = v18 - 1;
        QTask_nProtectedQTaskStackOffset = v15;
      }
      while ( v14 );
    }
  }
}

// source: j/0/weapons/stationarygun.c:543  [anchor-mhash]
void __cdecl StationaryGun_DeleteHandler(struct QTask_s *ptQTask)
{
  QTaskList_Remove(GameFunctions_ptActivateQTaskList, ptQTask);
  SectorObject_RemoveInteriorDynCubeObj((struct DynCubeObj_s *)ptQTask);
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

// source: j/0/weapons/stationarygun.c:567  [anchor-mhash]
void __cdecl StationaryGun_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { float ptDynCubeObj; };
    struct { char igi2_o1[28]; struct QTask_s ptParent; };
    struct { char igi2_o2[68]; int v20; };
    struct { char igi2_o3[72]; _BYTE v21[40]; };
    struct { char igi2_o4[112]; int v22; };
    struct { char igi2_o5[116]; int v23; };
    struct { char igi2_o6[120]; int v24; };
    struct { char igi2_o7[124]; int v25; };
    struct { char igi2_o8[128]; int v26; };
    struct { char igi2_o9[132]; int v27; };
    struct { char igi2_o10[136]; int v28; };
    struct { char igi2_o11[140]; int v29; };
    struct { char igi2_o12[144]; int v30; };
    struct { char igi2_o13[148]; int v31; };
    struct { char igi2_o14[152]; struct QTask_s *v32; };
    struct { char igi2_o15[164]; struct QReference_s *v33; };
    struct { char igi2_o16[168]; struct QTask_s *v34; };
    struct { char igi2_o17[172]; int v35; };
    struct { char igi2_o18[176]; int v36; };
    struct { char igi2_o19[180]; int v37; };
    struct { char igi2_o20[192]; _DWORD v38[10]; };
    struct { char igi2_o21[232]; _BYTE ptNetManagerGameMessage[24]; };
    char igi2_extent[256];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct LODVirModel_s *LODVirModelExistsFn; // eax
  double v3; // st7
  double v4; // st7
  int *v5; // eax
  int v6; // eax
  double v7; // st6
  struct QTask_s *v8; // esi
  int v9; // eax
  struct WeaponType_s *WeaponTypeFromID; // esi
  struct AmmoTypeItem_s *AmmoTypeItemFromAmmoType; // eax
  struct QTask_s *ptMiddle; // ecx
  int nAmmoCount; // edx
  struct QTask_s *zFixedModel; // esi
  struct QReference_s *ptTail; // edx
  struct QTask_s *ptPrev; // eax
  __int16 v17; // cx

  LODVirModelExistsFn = MTP_GetLODVirModelExistsFn((char *)&ptQTask[11].tQTaskChildren.ptTail);
  if ( !LODVirModelExistsFn )
    LODVirModelExistsFn = nullptr;
  if ( LODVirModelExistsFn != *(struct LODVirModel_s **)&ptQTask[2].eQTaskType )
  {
    ModelObj_SetLODVirModel((struct ModelObj_s *)ptQTask, LODVirModelExistsFn, false);
    ptQTask[7].tQTaskRefList.ptHead = nullptr;
    ptQTask[7].tQTaskRefList.ptMiddle = nullptr;
    ptQTask[7].tQTaskRefList.ptTail = nullptr;
    ptQTask[7].ptParent = nullptr;
    *(_DWORD *)&ptQTask[7].eQTaskType = 0;
  }
  if ( *(float *)&ptQTask[6].tQTaskChildren.ptHead <= (double)*(float *)&ptQTask[6].tQTaskChildren.ptMiddle )
    v3 = *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
  else
    v3 = *(float *)&ptQTask[6].tQTaskChildren.ptHead;
  if ( v3 >= *(float *)&ptQTask[6].ptPrev )
  {
    if ( *(float *)&ptQTask[6].tQTaskChildren.ptHead <= (double)*(float *)&ptQTask[6].tQTaskChildren.ptMiddle )
      v4 = *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
    else
      v4 = *(float *)&ptQTask[6].tQTaskChildren.ptHead;
  }
  else
  {
    v4 = *(float *)&ptQTask[6].ptPrev;
  }
  v5 = *(int **)&ptQTask[2].eQTaskType;
  if ( v5 && (v6 = *v5) != 0 )
    v7 = *(float *)(*(_DWORD *)(*(_DWORD *)(v6 + 12) + 12) + 120);
  else
    v7 = 1.0;
  igi2_frame.ptDynCubeObj = v4 * v7;
  World_MoveDynCubeObjRadius(
    Game_ptGame->ptWorld,
    (struct DynCubeObj_s *)ptQTask,
    (struct real64x3_t *)&ptQTask[8].tQTaskChildren,
    igi2_frame.ptDynCubeObj);
  v8 = ptQTask[2].ptParent;
  SectorObject_RemoveInteriorDynCubeObj((struct DynCubeObj_s *)ptQTask);
  if ( ptQTask[7].tQTaskChildren.ptTail )
  {
    ptQTask[2].tQTaskRefList.ptHead = nullptr;
    ptQTask[2].tQTaskRefList.ptMiddle = nullptr;
  }
  else
  {
    SectorObject_RegisterInteriorDynCubeObjSpecificSectorObject(
      (struct World_s *)v8,
      nullptr,
      (struct DynCubeObj_s *)ptQTask,
      (struct real64x3_t *)&ptQTask[1]);
  }
  RigidDynCubeObj_UpdateAttachments((struct RigidDynCubeObj_t *)ptQTask);
  qmemcpy(&ptQTask[3].ptPrev, &ptQTask[8].ptParent, sizeof(struct QTask_s));
  ptQTask[14].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[14].tQTaskChildren.ptTail = nullptr;
  ptQTask[14].ptPrev = nullptr;
  ptQTask[14].tQTaskChildren.ptHead = nullptr;
  *(_DWORD *)&ptQTask[13].eQTaskType = 0;
  ptQTask[14].ptNext = nullptr;
  ptQTask[14].tQTaskRefList.ptHead = nullptr;
  ptQTask[14].tQTaskRefList.ptMiddle = (struct QReference_s *)-1;
  LOBYTE(ptQTask[14].ptParent) = 0;
  v9 = Script_ParseLineInt32((char *)&ptQTask[12].tQTaskChildren);
  WeaponTypeFromID = WeaponType_GetWeaponTypeFromID(v9);
  if ( WeaponTypeFromID )
  {
    Weapon_EnableWeaponType(*(struct QTask_s **)&ptQTask[14].eQTaskType, WeaponTypeFromID->zWeaponScriptID, true);
    if ( ptQTask[13].tQTaskChildren.ptMiddle == (struct QTask_s *)-1 )
    {
      *(_DWORD *)(*(_DWORD *)&ptQTask[14].eQTaskType + 60) = 1;
    }
    else
    {
      *(_DWORD *)(*(_DWORD *)&ptQTask[14].eQTaskType + 60) = 0;
      memset(igi2_frame.v38, 0, sizeof(igi2_frame.v38));
      ((void (__cdecl *)(struct WeaponType_s *, _DWORD *))QTask_aatQTaskFinalEvent[WeaponType_eGetAmmoInfoQTaskEvent][WeaponTypeFromID->tQTask.eQTaskType].pfHandler)(
        WeaponTypeFromID,
        igi2_frame.v38);
      if ( igi2_frame.v38[1] )
      {
        Weapon_ClearAllWeapons(*(struct QTask_s **)&ptQTask[14].eQTaskType);
        Weapon_EnableWeaponType(
          *(struct QTask_s **)&ptQTask[14].eQTaskType,
          (char *)&ptQTask[12].tQTaskChildren,
          false);
        AmmoTypeItemFromAmmoType = Weapon_GetAmmoTypeItemFromAmmoType(
                                     *(struct QTask_s **)&ptQTask[14].eQTaskType,
                                     (char *)(igi2_frame.v38[1] + 40));
        if ( AmmoTypeItemFromAmmoType )
        {
          ptMiddle = ptQTask[13].tQTaskChildren.ptMiddle;
          AmmoTypeItemFromAmmoType->nAmmoLimit = (int)ptMiddle;
          if ( ptMiddle != (struct QTask_s *)-1 )
          {
            nAmmoCount = AmmoTypeItemFromAmmoType->nAmmoCount;
            if ( nAmmoCount >= 0 )
            {
              if ( nAmmoCount > (int)ptMiddle )
                AmmoTypeItemFromAmmoType->nAmmoCount = (int)ptMiddle;
            }
            else
            {
              AmmoTypeItemFromAmmoType->nAmmoCount = 0;
            }
          }
        }
        Weapon_AddAmmoToAmmoType(
          *(struct QTask_s **)&ptQTask[14].eQTaskType,
          (char *)(igi2_frame.v38[1] + 40),
          (int)ptQTask[13].tQTaskChildren.ptMiddle);
        Weapon_SendWeaponEvent(*(struct QTask_s **)&ptQTask[14].eQTaskType, 0x5753524Cu, igi2_frame.ptNetManagerGameMessage, 20);
      }
    }
    if ( ptQTask[8].ptNext )
    {
      QTask_Delete(ptQTask[8].ptNext);
      ptQTask[8].ptNext = nullptr;
    }
    zFixedModel = (struct QTask_s *)WeaponTypeFromID->zFixedModel;
    if ( MTP_GetLODVirModelExistsFn((char *)zFixedModel) )
    {
      ptTail = ptQTask[2].tQTaskRefList.ptTail;
      igi2_frame.v32 = ptQTask;
      ptPrev = ptQTask[7].ptPrev;
      igi2_frame.ptParent.ptPrev = (struct QTask_s *)Game_ptGame->ptWorld;
      igi2_frame.ptParent.ptNext = zFixedModel;
      igi2_frame.v36 = 0;
      igi2_frame.v35 = 1;
      qmemcpy(&igi2_frame.ptParent.tQTaskChildren, &ptQTask[9].ptParent, 0x18u);
      igi2_frame.ptParent.ptParent = nullptr;
      *(_DWORD *)&igi2_frame.ptParent.eQTaskType = 0;
      igi2_frame.v20 = 0;
      qmemcpy(igi2_frame.v21, &ptQTask[10].tQTaskChildren.ptTail, sizeof(igi2_frame.v21));
      igi2_frame.v34 = ptPrev;
      igi2_frame.v22 = 1065353216;
      igi2_frame.v23 = 0;
      igi2_frame.v24 = 0;
      igi2_frame.v25 = 0;
      igi2_frame.v26 = 1065353216;
      igi2_frame.v27 = 0;
      igi2_frame.v28 = 0;
      igi2_frame.v29 = 0;
      igi2_frame.v30 = 1065353216;
      igi2_frame.v31 = 0;
      igi2_frame.v33 = ptTail;
      igi2_frame.v37 = 0;
      ptQTask[8].ptNext = QTask_NewFn(ptQTask, RigidDynCubeObj_eQTaskType, &igi2_frame.ptParent);
      qmemcpy(&ptQTask[10].tQTaskChildren.ptTail, &ptQTask[8].ptParent, sizeof(struct QTask_s));
    }
    StationaryGun_PositionWeapon(ptQTask, (struct real32x9_t *)&ptQTask[3].ptPrev);
  }
  v17 = Attach_eAttachEvent;
  ptQTask[5].tQTaskChildren.ptTail = (struct QTask_s *)-1;
  ptQTask[5].tQTaskRefList.ptHead = nullptr;
  QTask_TriggerQTaskEventParent(ptQTask, v17, &ptQTask[5].tQTaskChildren.ptTail);
  ModelObj_CalcRelativePosAndOrientation((struct ModelObj_s *)ptQTask);
}

// source: j/0/weapons/stationarygun.c:709  [size~]
void __cdecl StationaryGun_UpdateInternalDataAfterLoadHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptParent; // esi

  ptParent = ptQTask[2].ptParent;
  SectorObject_RemoveInteriorDynCubeObj((struct DynCubeObj_s *)ptQTask);
  if ( ptQTask[7].tQTaskChildren.ptTail )
  {
    ptQTask[2].tQTaskRefList.ptHead = nullptr;
    ptQTask[2].tQTaskRefList.ptMiddle = nullptr;
  }
  else
  {
    SectorObject_RegisterInteriorDynCubeObjSpecificSectorObject(
      (struct World_s *)ptParent,
      nullptr,
      (struct DynCubeObj_s *)ptQTask,
      (struct real64x3_t *)&ptQTask[1]);
  }
}

// source: j/0/weapons/stationarygun.c:752  [anchor-mhash]
void __cdecl StationaryGun_EvaluateActivateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct real64x3_t tPos; // [esp+8h] [ebp-1Ch] BYREF

  if ( !LOBYTE(ptQTask[14].ptParent) )
  {
    GameFunctions_GetMagicVertex(&tPos, ptQTask, 0);
    if ( *(float *)&ptQTask[3].ptParent * (*((double *)pxContext + 3) - tPos.vZ)
       + *(float *)&ptQTask[3].tQTaskRefList.ptHead * (*((double *)pxContext + 2) - tPos.vY)
       + *(float *)&ptQTask[3].tQTaskChildren.ptHead * (*((double *)pxContext + 1) - tPos.vX) <= 0.0 )
      GameFunctions_ResolveEvaluateActivate((struct EvaluateActivateContext_t *)pxContext, ptQTask, &tPos);
  }
}

// source: j/0/weapons/stationarygun.c:799  [size]
void __cdecl StationaryGun_GetActivateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = 5;
}

// source: j/0/weapons/stationarygun.c:816  [anchor-mhash]
void __cdecl StationaryGun_ActivateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QReference_s *v2; // edi
  struct QTask_s *v3; // eax

  v2 = *(struct QReference_s **)pxContext;
  if ( !*((_DWORD *)pxContext + 10) )
  {
    v3 = *(struct QTask_s **)&ptQTask[14].eQTaskType;
    ptQTask[14].tQTaskRefList.ptHead = v2;
    Weapon_SetHumanOperator(v3, (struct QTask_s *)v2);
    *(_DWORD *)(*(_DWORD *)&ptQTask[14].eQTaskType + 92) = v2[35].pxObject;
  }
  LOBYTE(ptQTask[14].ptParent) = 1;
}

// source: j/0/weapons/stationarygun.c:851  [size]
void __cdecl StationaryGun_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = StationaryGun_ptParameterList;
}

// source: j/0/weapons/stationarygun.c:867  [size]
void __cdecl StationaryGun_SetPositionHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ;
}

// source: j/0/weapons/stationarygun.c:902  [size]
void __cdecl StationaryGun_AILineOfSightHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *v2; // eax
  struct QReference_s *ptHead; // edx
  struct QTask_s *v4; // eax

  v2 = *((struct QTask_s **)pxContext + 2);
  *(_BYTE *)pxContext = v2 != ptQTask
                     && (ptHead = ptQTask[14].tQTaskRefList.ptHead, v2 != (struct QTask_s *)ptHead)
                     && (v4 = *((struct QTask_s **)pxContext + 3), v4 != ptQTask)
                     && v4 != (struct QTask_s *)ptHead;
}

// source: j/0/weapons/stationarygun.c:932  [anchor-mhash]
void __cdecl StationaryGun_GetParentPositionHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { float ptDest; };
    struct { char igi2_o1[4]; float vAlpha; };
    struct { char igi2_o2[28]; struct real32x9_t tNewOrientation; };
    struct { char igi2_o3[68]; struct real32x9_t Real32x9_Multiply_tTemp; };
    char igi2_extent[112];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QReference_s *ptHead; // edx
  double v4; // st7
  struct QReference_s *ptPrev; // eax
  struct RandomState_s *p_tRunRandomState; // esi
  double v7; // st6
  double v8; // rt0
  double v9; // st6
  struct RandomState_s *v10; // eax
  double RandomNumberReal32; // st7
  double v12; // st7
  double v13; // st6
  char *pxObject; // edx
  double v15; // st7
  double v16; // st6

  ptHead = ptQTask[14].tQTaskRefList.ptHead;
  if ( ptHead )
  {
    if ( QTask_IsQTaskTypeDerived((unsigned __int16)ptHead[3].ptNext, HumanPlayer_eQTaskType) )
    {
      qmemcpy((char *)pxContext + 24, &ptHead[111].ptPrev[44].pxObject, 0x28u);
      v4 = (*((float *)pxContext + 6) + *((float *)pxContext + 8)) * 0.0 + *((float *)pxContext + 7) * 8192.0;
      ptPrev = ptHead[111].ptPrev;
      p_tRunRandomState = &Game_ptGame->tRunRandomState;
      v7 = (*((float *)pxContext + 11) + *((float *)pxContext + 9)) * 0.0 + *((float *)pxContext + 10) * 8192.0;
      *(double *)&igi2_frame.tNewOrientation.tY.vY = (*((float *)pxContext + 14) + *((float *)pxContext + 12)) * 0.0
                                        + *((float *)pxContext + 13) * 8192.0;
      v8 = v7;
      v9 = v4 + *(double *)&ptPrev[42].pxObject;
      v10 = &Game_ptGame->tRunRandomState;
      *(double *)pxContext = v9;
      *((double *)pxContext + 1) = v8 + *(double *)&ptHead[111].ptPrev[43].ptPrev;
      *((double *)pxContext + 2) = *(double *)&igi2_frame.tNewOrientation.tY.vY + *(double *)&ptHead[111].ptPrev[44].ptNext;
      RandomNumberReal32 = Random_GetRandomNumberReal32(v10);
      igi2_frame.vAlpha = Random_GetRandomNumberReal32(p_tRunRandomState) * 6.2831854820251465;
      igi2_frame.ptDest = *(float *)&ptQTask[13].tQTaskRefList.ptHead * 0.01745329238474369 * RandomNumberReal32;
      Real32x9_Create(&igi2_frame.tNewOrientation, igi2_frame.ptDest, igi2_frame.vAlpha, 0.0);
      igi2_frame.Real32x9_Multiply_tTemp.tX.vX = igi2_frame.tNewOrientation.tX.vX * *((float *)pxContext + 6)
                                    + igi2_frame.tNewOrientation.tY.vX * *((float *)pxContext + 7)
                                    + igi2_frame.tNewOrientation.tZ.vX * *((float *)pxContext + 8);
      igi2_frame.Real32x9_Multiply_tTemp.tX.vY = igi2_frame.tNewOrientation.tX.vY * *((float *)pxContext + 6)
                                    + igi2_frame.tNewOrientation.tY.vY * *((float *)pxContext + 7)
                                    + igi2_frame.tNewOrientation.tZ.vY * *((float *)pxContext + 8);
      v12 = igi2_frame.tNewOrientation.tX.vZ * *((float *)pxContext + 6) + igi2_frame.tNewOrientation.tY.vZ * *((float *)pxContext + 7);
      v13 = igi2_frame.tNewOrientation.tZ.vZ * *((float *)pxContext + 8);
      igi2_frame.Real32x9_Multiply_tTemp.nOps = *((_DWORD *)pxContext + 15) + igi2_frame.tNewOrientation.nOps + 1;
      igi2_frame.Real32x9_Multiply_tTemp.tX.vZ = v12 + v13;
      igi2_frame.Real32x9_Multiply_tTemp.tY.vX = igi2_frame.tNewOrientation.tY.vX * *((float *)pxContext + 10)
                                    + igi2_frame.tNewOrientation.tZ.vX * *((float *)pxContext + 11)
                                    + igi2_frame.tNewOrientation.tX.vX * *((float *)pxContext + 9);
      igi2_frame.Real32x9_Multiply_tTemp.tY.vY = igi2_frame.tNewOrientation.tY.vY * *((float *)pxContext + 10)
                                    + igi2_frame.tNewOrientation.tZ.vY * *((float *)pxContext + 11)
                                    + igi2_frame.tNewOrientation.tX.vY * *((float *)pxContext + 9);
      igi2_frame.Real32x9_Multiply_tTemp.tY.vZ = igi2_frame.tNewOrientation.tY.vZ * *((float *)pxContext + 10)
                                    + igi2_frame.tNewOrientation.tZ.vZ * *((float *)pxContext + 11)
                                    + igi2_frame.tNewOrientation.tX.vZ * *((float *)pxContext + 9);
      igi2_frame.Real32x9_Multiply_tTemp.tZ.vX = igi2_frame.tNewOrientation.tY.vX * *((float *)pxContext + 13)
                                    + igi2_frame.tNewOrientation.tZ.vX * *((float *)pxContext + 14)
                                    + igi2_frame.tNewOrientation.tX.vX * *((float *)pxContext + 12);
      igi2_frame.Real32x9_Multiply_tTemp.tZ.vY = igi2_frame.tNewOrientation.tY.vY * *((float *)pxContext + 13)
                                    + igi2_frame.tNewOrientation.tZ.vY * *((float *)pxContext + 14)
                                    + igi2_frame.tNewOrientation.tX.vY * *((float *)pxContext + 12);
      igi2_frame.Real32x9_Multiply_tTemp.tZ.vZ = igi2_frame.tNewOrientation.tY.vZ * *((float *)pxContext + 13)
                                    + igi2_frame.tNewOrientation.tZ.vZ * *((float *)pxContext + 14)
                                    + igi2_frame.tNewOrientation.tX.vZ * *((float *)pxContext + 12);
      qmemcpy((char *)pxContext + 24, &igi2_frame.Real32x9_Multiply_tTemp, 0x28u);
    }
    else
    {
      pxObject = (char *)ptHead[162].pxObject;
      if ( pxObject )
      {
        v15 = (*(float *)&ptQTask[10].tQTaskRefList.ptMiddle + *(float *)&ptQTask[10].tQTaskChildren.ptTail) * 0.0
            + *(float *)&ptQTask[10].tQTaskRefList.ptHead * 4096.0;
        v16 = (*(float *)&ptQTask[10].eQTaskType + *(float *)&ptQTask[10].tQTaskRefList.ptTail) * 0.0
            + *(float *)&ptQTask[10].ptParent * 4096.0;
        *(double *)&igi2_frame.tNewOrientation.tY.vY = (*(float *)&ptQTask[11].tQTaskChildren.ptHead + *(float *)&ptQTask[11].ptNext)
                                          * 0.0
                                          + *(float *)&ptQTask[11].ptPrev * 4096.0;
        *(double *)pxContext = v15 + *(double *)&ptQTask[9].ptParent;
        *((double *)pxContext + 1) = v16 + *(double *)&ptQTask[10].ptNext;
        *((double *)pxContext + 2) = *(double *)&igi2_frame.tNewOrientation.tY.vY + *(double *)&ptQTask[10].tQTaskChildren.ptHead;
        qmemcpy((char *)pxContext + 24, pxObject + 160, 0x28u);
      }
    }
  }
}

// source: j/0/weapons/stationarygun.c:987  [size]
void __cdecl StationaryGun_SoundUpdateParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = ptQTask + 1;
  *((_DWORD *)pxContext + 1) = (char *)ptQTask + 124;
  *((_DWORD *)pxContext + 2) = 0;
}

// source: j/0/weapons/stationarygun.c:1013  [size]
unsigned __int16 __cdecl StationaryGun_GetQTaskType()
{
  return StationaryGun_eQTaskType;
}

// source: j/0/weapons/stationarygun.c:1027  [size]
struct real64x3_t *__cdecl StationaryGun_GetActivatePosAndOrientation(
        struct QTask_s *ptQTask,
        struct real64x3_t *ptPos,
        struct real32x9_t *ptOrientation)
{
  qmemcpy(ptOrientation, &ptQTask[3].ptPrev, sizeof(struct real32x9_t));
  return GameFunctions_GetMagicVertex(ptPos, ptQTask, 0);
}

// source: j/0/weapons/stationarygun.c:1050  [size]
struct QTask_s *__cdecl StationaryGun_GetGunPosAndOrientation(
        struct QTask_s *ptQTask,
        struct real64x3_t *ptPos,
        struct real32x9_t *ptOrientation)
{
  qmemcpy(ptOrientation, &ptQTask[10].tQTaskChildren.ptTail, sizeof(struct real32x9_t));
  qmemcpy(ptPos, &ptQTask[9].ptParent, sizeof(struct real64x3_t));
  return ptQTask;
}

// source: j/0/weapons/stationarygun.c:1070  [anchor-callee]
void __cdecl StationaryGun_Deactivate(struct QTask_s *ptQTask)
{
  struct QReference_s *ptHead; // edi
  int v3; // ebp
  struct QReference_s *v4; // eax
  _DWORD *v5; // esi

  ptHead = ptQTask[14].tQTaskRefList.ptHead;
  BYTE2(ptHead[111].ptPrev[42].ptPrev) = 0;
  v3 = *(_DWORD *)&ptQTask[14].eQTaskType;
  ptQTask[14].tQTaskRefList.ptHead = nullptr;
  LOBYTE(ptQTask[14].ptParent) = 0;
  v4 = *(struct QReference_s **)(v3 + 96);
  if ( v4 )
    QReference_Delete(v4, &QTask_tQTaskRefPool);
  *(_DWORD *)(v3 + 96) = 0;
  *(_DWORD *)(*(_DWORD *)&ptQTask[14].eQTaskType + 92) = -1;
  if ( *(float *)&ptHead[44].pxObject != 0.0 )
  {
    v5 = *(_DWORD **)&ptQTask[14].eQTaskType;
    v5[28] = 1;
    v5[14] = 0;
    v5[16] = 0;
  }
}

// source: j/0/weapons/stationarygun.c:1106  [anchor-mhash]
void __cdecl StationaryGun_Pause(struct QTask_s *ptQTask)
{
  struct QReference_s *ptHead; // eax
  _DWORD *v2; // eax

  ptHead = ptQTask[14].tQTaskRefList.ptHead;
  ptQTask[14].tQTaskRefList.ptHead = nullptr;
  if ( *(float *)&ptHead[44].pxObject != 0.0 )
  {
    v2 = *(_DWORD **)&ptQTask[14].eQTaskType;
    v2[28] = 1;
    v2[14] = 0;
    v2[16] = 0;
  }
}

// source: j/0/weapons/stationarygun.c:1137  [size]
struct QTask_s *__cdecl StationaryGun_Unpause(
        struct QTask_s *ptQTask,
        struct QTask_s *ptHumanOperator)
{
  ptQTask[14].tQTaskRefList.ptHead = (struct QReference_s *)ptHumanOperator;
  return ptHumanOperator;
}

// source: j/0/weapons/stationarygun.c:1155  [size]
char __cdecl StationaryGun_IsActivated(struct QTask_s *ptQTask)
{
  return (char)ptQTask[14].ptParent;
}

// source: j/0/weapons/stationarygun.c:1173  [anchor-strings]
void __cdecl StationaryGun_Open()
{
  unsigned __int16 v0; // si
  __int16 v1; // ax
  struct ParameterList_s *v2; // eax
  int v3; // edx

  v0 = QTask_NewQTaskType("StationaryGun", 600, SectorInteriorObject_eQTaskType, 0, 0);
  StationaryGun_eQTaskType = v0;
  QTask_LinkQTaskEventHandlerFn(
    v0,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveNoChildrenHandler);
  QTask_LinkQTaskEventHandlerFn(v0, 0, StationaryGun_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 1, StationaryGun_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 2, StationaryGun_DeleteHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, Attach_eUpdateAttachmentEvent, StationaryGun_UpdateAttachmentHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    ParameterList_eUpdateInternalDataQTaskEvent,
    StationaryGun_UpdateInternalDataHandler);
  QTask_LinkQTaskEventHandlerFn(v0, GameFunctions_eEvaluateActivateQTaskEvent, StationaryGun_EvaluateActivateHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    GameFunctions_eGetActivateQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))StationaryGun_GetActivateHandler);
  QTask_LinkQTaskEventHandlerFn(v0, GameFunctions_eActivateQTaskEvent, StationaryGun_ActivateHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))StationaryGun_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(v0, 7, (void (__cdecl *)(struct QTask_s *, void *))StationaryGun_SetPositionHandler);
  QTask_LinkQTaskEventHandlerFn(v0, AIDetection_eLineOfSightQTaskEvent, StationaryGun_AILineOfSightHandler);
  QTask_LinkQTaskEventHandlerFn(v0, Weapon_eGetParentParametersQTaskEvent, StationaryGun_GetParentPositionHandler);
  v1 = SoundSys_eUpdateParameterListQTaskEvent;
  if ( SoundSys_eUpdateParameterListQTaskEvent == 512 )
  {
    v1 = QTask_NewQTaskEventFn(0, (char *)&g_zFileName.nRealFadeCount);
    v0 = StationaryGun_eQTaskType;
    SoundSys_eUpdateParameterListQTaskEvent = v1;
  }
  QTask_LinkQTaskEventHandlerFn(v0, v1, StationaryGun_SoundUpdateParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(v0, StatusScreen_eStatusDisplayQTaskEvent, StationaryGun_StatusDisplayHandler);
  QTask_LinkQTaskEventHandlerFn(v0, Weapon_eGetWeaponPrecisionQTaskEvent, StationaryGun_GetWeaponPrecisionHandler);
  QTask_LinkQTaskEventHandlerFn(v0, Weapon_eGetWeaponObjectEvent, StationaryGun_GetWeaponObjectHandler);
  QTask_LinkQTaskEventHandlerFn(v0, Serialize_eSerializeQTaskEvent, sub_45B360);
  QTask_LinkQTaskEventHandlerNoContextFn(
    v0,
    Level_eUpdateInternalDataAfterLoadEvent,
    StationaryGun_UpdateInternalDataAfterLoadHandler);
  v2 = (struct ParameterList_s *)Mem_AllocFn(172, 4);
  v3 = Level_eParameterTypeObjectPos;
  v2->ptParameterListItem = (struct ParameterListItem_s *)&v2[1];
  v2->nParameters = 0;
  v2->nMaxParameters = 8;
  StationaryGun_ptParameterList = v2;
  ParameterList_AddParameter(v2, 0x148u, v3, "Position", 7u, nullptr);
  ParameterList_AddParameter(
    StationaryGun_ptParameterList,
    0x160u,
    Level_eParameterTypeReal32x9,
    "Orientation",
    7u,
    nullptr);
  ParameterList_AddParameter(
    StationaryGun_ptParameterList,
    0x1C8u,
    Level_eParameterTypeString32,
    "Holder model",
    7u,
    nullptr);
  ParameterList_AddParameter(
    StationaryGun_ptParameterList,
    0x1E8u,
    Level_eParameterTypeString32,
    "Weapon ID",
    7u,
    nullptr);
  ParameterList_AddParameter(
    StationaryGun_ptParameterList,
    0x208u,
    Level_eParameterTypeDegrees,
    g_zMessage.zChallenge,
    7u,
    nullptr);
  ParameterList_AddParameter(
    StationaryGun_ptParameterList,
    0x20Cu,
    Level_eParameterTypeDegrees,
    (char *)&g_zMessage.anDR[31],
    7u,
    nullptr);
  ParameterList_AddParameter(
    StationaryGun_ptParameterList,
    0x210u,
    Level_eParameterTypeDegrees,
    (char *)&g_zMessage.anDR[26],
    7u,
    nullptr);
  ParameterList_AddParameterMinMax(
    StationaryGun_ptParameterList,
    0x214u,
    Level_eParameterTypeInt32,
    (char *)&g_zMessage.anDR[24],
    7u,
    -1.0,
    100000.0);
}

// source: j/0/weapons/stationarygun.c:1236  [size]
void __cdecl StationaryGun_Close()
{
  int v0; // esi

  if ( StationaryGun_ptParameterList )
  {
    v0 = *(_DWORD *)((unsigned int)&StationaryGun_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
  QTask_DeleteQTaskType(StationaryGun_eQTaskType);
}
