/* j/0/weapons/muzzleflash.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/weapons/muzzleflash.c:81  [size]
void __cdecl MuzzleFlash_Update(struct MuzzleFlash_s *ptMuzzleFlash, enum bool isRegister)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct GetWeaponObjectContext_t tGetWeaponObjectContext; };
    struct { char igi2_o1[12]; struct real64x3_t tPos; };
    char igi2_extent[36];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct RigidDynCubeObj_t *ptWeaponObject; // ebp
  struct World_s *ptWorld; // eax
  struct DynCubeObj_s *ptManualRedrawList; // ecx
  struct DynCubeObj_s *ptPrev; // ecx

  igi2_frame.tGetWeaponObjectContext.nWeapon = ptMuzzleFlash->nWeapon;
  igi2_frame.tGetWeaponObjectContext.ptWeaponObject = nullptr;
  igi2_frame.tGetWeaponObjectContext.isFirstPerson = false;
  QTask_TriggerQTaskEventParent(
    &ptMuzzleFlash->tPolyListDynCubeObj.tDynCubeObj.tQObj.tQTask,
    Weapon_eGetWeaponObjectEvent,
    &igi2_frame.tGetWeaponObjectContext);
  ptWeaponObject = igi2_frame.tGetWeaponObjectContext.ptWeaponObject;
  if ( igi2_frame.tGetWeaponObjectContext.ptWeaponObject )
  {
    qmemcpy(
      &ptMuzzleFlash->tPolyListDynCubeObj.tOrientation,
      &igi2_frame.tGetWeaponObjectContext.ptWeaponObject->tModelObj.tOrientation,
      sizeof(ptMuzzleFlash->tPolyListDynCubeObj.tOrientation));
    RigidDynCubeObj_GetMagicVertexPos(ptWeaponObject, 2u, &igi2_frame.tPos);
    ptMuzzleFlash->tPolyListDynCubeObj.tDynCubeObj.iRenderGroup = ptWeaponObject->tModelObj.tDynCubeObj.iRenderGroup;
    ptMuzzleFlash->tPolyListDynCubeObj.eLayer = ptWeaponObject->tModelObj.eLayer;
    if ( isRegister )
    {
      ptWorld = ptMuzzleFlash->tPolyListDynCubeObj.ptWorld;
      ptManualRedrawList = ptWorld->ptManualRedrawList;
      if ( ptManualRedrawList )
      {
        ptManualRedrawList->ptPrev = &ptMuzzleFlash->tPolyListDynCubeObj.tDynCubeObj;
        ptWorld->ptManualRedrawList->ptPrev->ptNext = ptWorld->ptManualRedrawList;
        ptPrev = ptWorld->ptManualRedrawList->ptPrev;
        ptWorld->ptManualRedrawList = ptPrev;
        ptPrev->ptPrev = nullptr;
      }
      else
      {
        ptWorld->ptManualRedrawList = &ptMuzzleFlash->tPolyListDynCubeObj.tDynCubeObj;
        ptMuzzleFlash->tPolyListDynCubeObj.tDynCubeObj.ptNext = nullptr;
        ptWorld->ptManualRedrawList->ptPrev = nullptr;
      }
    }
    qmemcpy(
      &ptMuzzleFlash->tPolyListDynCubeObj.tDynCubeObj.tQObj.tPos,
      &igi2_frame.tPos,
      sizeof(ptMuzzleFlash->tPolyListDynCubeObj.tDynCubeObj.tQObj.tPos));
  }
}

// source: j/0/weapons/muzzleflash.c:124  [anchor-mhash]
void __cdecl MuzzleFlash_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  double v2; // st7

  ptQTask[2].ptParent = (struct QTask_s *)Game_ptGame->ptWorld;
  *(_DWORD *)&ptQTask[2].eQTaskType = (char *)ptQTask + 312;
  ptQTask[4].tQTaskChildren.ptHead = (struct QTask_s *)8;
  ptQTask[4].tQTaskChildren.ptTail = nullptr;
  ptQTask[4].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[4].tQTaskRefList.ptHead = nullptr;
  ptQTask[4].tQTaskRefList.ptTail = nullptr;
  ptQTask[4].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[4].ptNext = nullptr;
  *(_DWORD *)&ptQTask[4].eQTaskType = 0;
  ptQTask[16].tQTaskChildren.ptMiddle = *(struct QTask_s **)pxContext;
  ptQTask[16].tQTaskChildren.ptTail = *((struct QTask_s **)pxContext + 1);
  ptQTask[5].ptNext = (struct QTask_s *)1065353216;
  ptQTask[5].ptPrev = (struct QTask_s *)1065353216;
  ptQTask[5].tQTaskChildren.ptHead = (struct QTask_s *)1065353216;
  ptQTask[5].tQTaskChildren.ptMiddle = (struct QTask_s *)1065353216;
  v2 = *((float *)pxContext + 2);
  *(float *)&ptQTask[15].eQTaskType = *((float *)pxContext + 2);
  *(float *)&ptQTask[15].ptParent = v2;
  ptQTask[16].tQTaskRefList.ptHead = *((struct QReference_s **)pxContext + 3);
  ptQTask[7].ptParent = (struct QTask_s *)((char *)ptQTask + 216);
  ptQTask[8].ptPrev = ptQTask + 5;
  ptQTask[8].tQTaskChildren.ptHead = ptQTask + 5;
  ptQTask[8].tQTaskChildren.ptMiddle = ptQTask + 5;
  ptQTask[10].ptPrev = ptQTask + 5;
  ptQTask[10].tQTaskChildren.ptHead = ptQTask + 5;
  ptQTask[10].tQTaskChildren.ptMiddle = ptQTask + 5;
  ptQTask[12].ptPrev = ptQTask + 5;
  ptQTask[12].tQTaskChildren.ptHead = ptQTask + 5;
  ptQTask[12].tQTaskChildren.ptMiddle = ptQTask + 5;
  ptQTask[14].ptPrev = ptQTask + 5;
  ptQTask[14].tQTaskChildren.ptHead = ptQTask + 5;
  ptQTask[14].tQTaskChildren.ptMiddle = ptQTask + 5;
  *(_DWORD *)&ptQTask[7].eQTaskType = (char *)ptQTask + 228;
  ptQTask[9].ptParent = (struct QTask_s *)((char *)ptQTask + 228);
  ptQTask[11].ptParent = (struct QTask_s *)((char *)ptQTask + 264);
  *(_DWORD *)&ptQTask[9].eQTaskType = (char *)ptQTask + 252;
  *(_DWORD *)&ptQTask[11].eQTaskType = (char *)ptQTask + 276;
  ptQTask[13].ptParent = (struct QTask_s *)((char *)ptQTask + 276);
  ptQTask[16].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[8].ptNext = ptQTask + 6;
  ptQTask[10].ptNext = ptQTask + 6;
  ptQTask[8].tQTaskChildren.ptTail = nullptr;
  ptQTask[8].tQTaskRefList.ptHead = nullptr;
  ptQTask[8].tQTaskRefList.ptMiddle = (struct QReference_s *)1065353216;
  ptQTask[8].tQTaskRefList.ptTail = nullptr;
  ptQTask[8].ptParent = nullptr;
  *(_DWORD *)&ptQTask[8].eQTaskType = 1065353216;
  ptQTask[10].tQTaskChildren.ptTail = (struct QTask_s *)1065353216;
  ptQTask[10].tQTaskRefList.ptHead = nullptr;
  ptQTask[10].tQTaskRefList.ptMiddle = (struct QReference_s *)1065353216;
  ptQTask[10].tQTaskRefList.ptTail = (struct QReference_s *)1065353216;
  ptQTask[10].ptParent = nullptr;
  *(_DWORD *)&ptQTask[10].eQTaskType = 1065353216;
  ptQTask[9].tQTaskRefList.ptTail = nullptr;
  ptQTask[11].tQTaskRefList.ptTail = nullptr;
  ptQTask[12].ptNext = (struct QTask_s *)((char *)ptQTask + 288);
  *(_DWORD *)&ptQTask[13].eQTaskType = (char *)ptQTask + 300;
  ptQTask[14].ptNext = (struct QTask_s *)((char *)ptQTask + 288);
  ptQTask[12].tQTaskChildren.ptTail = nullptr;
  ptQTask[12].tQTaskRefList.ptHead = nullptr;
  ptQTask[12].tQTaskRefList.ptMiddle = (struct QReference_s *)1065353216;
  ptQTask[12].tQTaskRefList.ptTail = nullptr;
  ptQTask[12].ptParent = nullptr;
  *(_DWORD *)&ptQTask[12].eQTaskType = 1065353216;
  ptQTask[14].tQTaskChildren.ptTail = (struct QTask_s *)1065353216;
  ptQTask[14].tQTaskRefList.ptHead = nullptr;
  ptQTask[14].tQTaskRefList.ptMiddle = (struct QReference_s *)1065353216;
  ptQTask[14].tQTaskRefList.ptTail = (struct QReference_s *)1065353216;
  ptQTask[14].ptParent = nullptr;
  *(_DWORD *)&ptQTask[14].eQTaskType = 1065353216;
  ptQTask[13].tQTaskRefList.ptTail = nullptr;
  ptQTask[15].tQTaskRefList.ptTail = nullptr;
  MuzzleFlash_Update((struct MuzzleFlash_s *)ptQTask, true);
}

// source: j/0/weapons/muzzleflash.c:233  [size]
void __cdecl MuzzleFlash_EnterHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct real64x3_t tViewDirection; };
    struct { char igi2_o1[24]; struct real32x3_t tForward; };
    char igi2_extent[36];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  __int16 v3; // cx
  float vX; // edx
  float v5; // eax
  struct QTask_s *v6; // eax
  struct QTask_s *ptTail; // edx
  struct QTask_s *ptMiddle; // eax
  double v9; // st7
  double v10; // st6
  double v11; // st7
  float *p_ptTail; // ecx
  struct QTask_s **p_ptParent; // edx
  double v14; // st6
  double v15; // st6
  double v16; // st7
  double v17; // st6
  double v18; // st5
  long double v19; // st7
  double v20; // st7
  double v21; // st6
  float ptQTaskb = *(float *)&ptQTask; // [esp+34h] [ebp+4h] ARGSLOT
  float ptQTaska = *(float *)&ptQTask; // [esp+34h] [ebp+4h] ARGSLOT

  LODWORD(igi2_frame.tForward.vY) = ptQTask[16].tQTaskRefList.ptHead;
  v3 = Weapon_eGetWeaponObjectEvent;
  ptQTask[16].tQTaskRefList.ptMiddle = (struct QReference_s *)1;
  igi2_frame.tForward.vX = 0.0;
  igi2_frame.tForward.vZ = 0.0;
  QTask_TriggerQTaskEventParent(ptQTask, v3, &igi2_frame.tForward);
  vX = igi2_frame.tForward.vX;
  if ( LODWORD(igi2_frame.tForward.vX) )
  {
    qmemcpy(&ptQTask[3], (void *)(LODWORD(igi2_frame.tForward.vX) + 124), sizeof(struct QTask_s));
    RigidDynCubeObj_GetMagicVertexPos((struct RigidDynCubeObj_t *)LODWORD(vX), 2u, &igi2_frame.tViewDirection);
    v5 = igi2_frame.tForward.vX;
    ptQTask[2].tQTaskRefList.ptTail = *(struct QReference_s **)(LODWORD(igi2_frame.tForward.vX) + 108);
    v6 = *(struct QTask_s **)(LODWORD(v5) + 284);
    qmemcpy(&ptQTask[1], &igi2_frame.tViewDirection, 0x18u);
    ptQTask[4].ptParent = v6;
  }
  *(float *)&igi2_frame.tViewDirection.vY = TransContext_tActiveTransContext.tMatrix.tZ.vZ;
  ptTail = ptQTask[3].tQTaskChildren.ptTail;
  LODWORD(igi2_frame.tForward.vZ) = ptQTask[3].tQTaskRefList.ptTail;
  ptMiddle = ptQTask[16].tQTaskChildren.ptMiddle;
  LODWORD(igi2_frame.tForward.vY) = ptTail;
  igi2_frame.tViewDirection.vX = *(double *)&TransContext_tActiveTransContext.tMatrix.tZ.vX;
  v9 = TransContext_tActiveTransContext.tMatrix.tZ.vZ * igi2_frame.tForward.vZ
     + TransContext_tActiveTransContext.tMatrix.tZ.vY * *(float *)&ptTail;
  LODWORD(igi2_frame.tForward.vX) = ptQTask[3].ptPrev;
  v10 = TransContext_tActiveTransContext.tMatrix.tZ.vX;
  ptQTask[4].ptPrev = nullptr;
  if ( ptMiddle )
  {
    if ( ptQTask[16].tQTaskChildren.ptTail )
    {
      ptQTaskb = v9 + v10 * igi2_frame.tForward.vX;
      v11 = ptQTaskb * ptQTaskb * 1.5 - 0.25;
      if ( v11 >= 0.0 )
      {
        if ( v11 > 1.0 )
          v11 = 1.0;
        ptQTaska = 1.0 - v11;
      }
      else
      {
        v11 = 0.0;
        ptQTaska = 1.0 - 0.0;
      }
    }
    else
    {
      v11 = 1.0;
      ptQTaska = 0.0;
    }
    p_ptTail = (float *)&ptQTask[5].tQTaskChildren.ptTail;
    p_ptParent = &ptQTask[7].ptParent;
    if ( v11 > 0.0 )
    {
      v14 = *(float *)&ptQTask[15].ptParent;
      if ( ptQTask[4].ptParent )
        v15 = v14 * 5120.0;
      else
        v15 = v14 * 4096.0;
      ptQTask[5].tQTaskRefList.ptHead = nullptr;
      ptQTask[5].ptParent = nullptr;
      *p_ptTail = -v15;
      ptQTask[6].ptPrev = nullptr;
      *(float *)&ptQTask[5].tQTaskRefList.ptMiddle = -v15;
      ptQTask[6].tQTaskChildren.ptTail = nullptr;
      *(float *)&ptQTask[5].tQTaskRefList.ptTail = v15;
      p_ptTail = (float *)&ptQTask[6].tQTaskRefList.ptMiddle;
      *(float *)&ptQTask[5].eQTaskType = -v15;
      *(float *)&ptQTask[6].ptNext = -v15;
      *(float *)&ptQTask[6].tQTaskChildren.ptHead = v15;
      *(float *)&ptQTask[6].tQTaskChildren.ptMiddle = v15;
      *(float *)&ptQTask[6].tQTaskRefList.ptHead = v15;
      ptQTask[9].tQTaskChildren.ptMiddle = nullptr;
      ptQTask[9].tQTaskChildren.ptTail = (struct QTask_s *)-1082130432;
      ptQTask[9].tQTaskRefList.ptHead = nullptr;
      ptQTask[11].tQTaskChildren.ptMiddle = nullptr;
      ptQTask[11].tQTaskChildren.ptTail = (struct QTask_s *)-1082130432;
      ptQTask[11].tQTaskRefList.ptHead = nullptr;
      ptQTask[9].tQTaskRefList.ptMiddle = (struct QReference_s *)ptQTask[16].tQTaskChildren.ptMiddle;
      ptQTask[11].tQTaskRefList.ptMiddle = (struct QReference_s *)ptQTask[16].tQTaskChildren.ptMiddle;
      *(float *)&ptQTask[9].ptNext = v11 * *(float *)&ptQTask[5].tQTaskChildren.ptMiddle;
      *(float *)&ptQTask[9].ptPrev = v11 * *(float *)&ptQTask[5].tQTaskChildren.ptMiddle;
      *(float *)&ptQTask[9].tQTaskChildren.ptHead = v11 * *(float *)&ptQTask[5].tQTaskChildren.ptMiddle;
      *(float *)&ptQTask[11].ptNext = v11 * *(float *)&ptQTask[5].tQTaskChildren.ptMiddle;
      *(float *)&ptQTask[11].ptPrev = v11 * *(float *)&ptQTask[5].tQTaskChildren.ptMiddle;
      *(float *)&ptQTask[11].tQTaskChildren.ptHead = v11 * *(float *)&ptQTask[5].tQTaskChildren.ptMiddle;
      ptQTask[4].ptPrev = (struct QTask_s *)((char *)ptQTask[4].ptPrev + 2);
      p_ptParent = &ptQTask[11].ptParent;
    }
    if ( ptQTaska > 0.0 )
    {
      v16 = *(float *)&igi2_frame.tViewDirection.vY * igi2_frame.tForward.vY - *((float *)&igi2_frame.tViewDirection.vX + 1) * igi2_frame.tForward.vZ;
      v17 = -(*(float *)&igi2_frame.tViewDirection.vY * igi2_frame.tForward.vX - *(float *)&igi2_frame.tViewDirection.vX * igi2_frame.tForward.vZ);
      v18 = *((float *)&igi2_frame.tViewDirection.vX + 1) * igi2_frame.tForward.vX - *(float *)&igi2_frame.tViewDirection.vX * igi2_frame.tForward.vY;
      igi2_frame.tForward.vX = v18 * *(float *)&ptQTask[3].tQTaskRefList.ptMiddle
                  + v17 * *(float *)&ptQTask[3].tQTaskChildren.ptMiddle
                  + v16 * *(float *)&ptQTask[3].ptNext;
      *(float *)&igi2_frame.tViewDirection.vX = igi2_frame.tForward.vX;
      igi2_frame.tForward.vY = v16 * *(float *)&ptQTask[3].ptPrev
                  + v17 * *(float *)&ptQTask[3].tQTaskChildren.ptTail
                  + v18 * *(float *)&ptQTask[3].tQTaskRefList.ptTail;
      HIDWORD(igi2_frame.tViewDirection.vX) = LODWORD(igi2_frame.tForward.vY);
      igi2_frame.tForward.vZ = v18 * *(float *)&ptQTask[3].ptParent
                  + v17 * *(float *)&ptQTask[3].tQTaskRefList.ptHead
                  + v16 * *(float *)&ptQTask[3].tQTaskChildren.ptHead;
      *(float *)&igi2_frame.tViewDirection.vY = igi2_frame.tForward.vZ;
      if ( igi2_frame.tForward.vX != 0.0 || igi2_frame.tForward.vZ != 0.0 )
      {
        v19 = 1.0 / sqrt(igi2_frame.tForward.vX * igi2_frame.tForward.vX + igi2_frame.tForward.vZ * igi2_frame.tForward.vZ);
        *(float *)&igi2_frame.tViewDirection.vX = igi2_frame.tForward.vX * v19;
        *(float *)&igi2_frame.tViewDirection.vY = *(float *)&igi2_frame.tViewDirection.vY * v19;
      }
      v20 = *(float *)&igi2_frame.tViewDirection.vX * *(float *)&ptQTask[15].ptParent * 4096.0;
      v21 = *(float *)&igi2_frame.tViewDirection.vY * *(float *)&ptQTask[15].ptParent * 4096.0;
      *p_ptTail = -v20;
      p_ptTail[1] = *(float *)&ptQTask[15].ptParent * -2048.0;
      p_ptTail[2] = -v21;
      p_ptTail[3] = -v20;
      p_ptTail[4] = *(float *)&ptQTask[15].ptParent * 14336.0;
      p_ptTail[5] = -v21;
      p_ptTail[6] = v20;
      p_ptTail[7] = *(float *)&ptQTask[15].ptParent * -2048.0;
      p_ptTail[8] = v21;
      p_ptTail[9] = v20;
      p_ptTail[10] = *(float *)&ptQTask[15].ptParent * 14336.0;
      p_ptTail[11] = v21;
      p_ptParent[18] = ptQTask[16].tQTaskChildren.ptTail;
      p_ptParent[38] = ptQTask[16].tQTaskChildren.ptTail;
      *((float *)p_ptParent + 12) = ptQTaska * *(float *)&ptQTask[5].tQTaskChildren.ptMiddle;
      *((float *)p_ptParent + 13) = ptQTaska * *(float *)&ptQTask[5].tQTaskChildren.ptMiddle;
      *((float *)p_ptParent + 14) = ptQTaska * *(float *)&ptQTask[5].tQTaskChildren.ptMiddle;
      *((float *)p_ptParent + 32) = ptQTaska * *(float *)&ptQTask[5].tQTaskChildren.ptMiddle;
      *((float *)p_ptParent + 33) = ptQTaska * *(float *)&ptQTask[5].tQTaskChildren.ptMiddle;
      *((float *)p_ptParent + 34) = ptQTaska * *(float *)&ptQTask[5].tQTaskChildren.ptMiddle;
      ptQTask[4].ptPrev = (struct QTask_s *)((char *)ptQTask[4].ptPrev + 2);
    }
    ((void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[5][PolyListDynCubeObj_eQTaskType].pfHandler)(
      ptQTask,
      pxContext);
  }
}

// source: j/0/weapons/muzzleflash.c:375  [size]
void __cdecl MuzzleFlash_DeleteHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptMiddle; // ecx
  struct QTask_s *ptTail; // ecx

  ptMiddle = ptQTask[2].tQTaskChildren.ptMiddle;
  if ( ptMiddle )
    ptMiddle[2].tQTaskChildren.ptTail = ptQTask[2].tQTaskChildren.ptTail;
  else
    Game_ptGame->ptWorld->ptManualRedrawList = (struct DynCubeObj_s *)ptQTask[2].tQTaskChildren.ptTail;
  ptTail = ptQTask[2].tQTaskChildren.ptTail;
  if ( ptTail )
    ptTail[2].tQTaskChildren.ptMiddle = ptQTask[2].tQTaskChildren.ptMiddle;
}

// source: j/0/weapons/muzzleflash.c:391  [size]
void __cdecl MuzzleFlash_RemoveHandler(struct QTask_s *ptQTask, void *pxContext)
{
  QTask_Delete(ptQTask);
}

// source: j/0/weapons/muzzleflash.c:404  [anchor-mhash]
void __cdecl MuzzleFlash_RunHandler(struct QTask_s *ptQTask)
{
  double v1; // st7

  if ( ptQTask[16].tQTaskRefList.ptMiddle )
  {
    v1 = *(float *)&ptQTask[5].tQTaskChildren.ptMiddle - 0.30000001192092896;
    *(float *)&ptQTask[5].tQTaskChildren.ptMiddle = v1;
    *(float *)&ptQTask[15].ptParent = *(float *)&ptQTask[15].ptParent + 0.019999999552965164;
    if ( v1 <= 0.0 )
      QTask_Delete(ptQTask);
  }
}

// source: j/0/weapons/muzzleflash.c:434  [anchor-callee]
struct QTask_s *__cdecl MuzzleFlash_New(
        struct QTask_s *ptParent,
        struct TexInfo_s *ptFrontSprite,
        struct TexInfo_s *ptSideSprite,
        float vRadius,
        int nWeapon)
{
  struct MuzzleFlashCreateContext_t tContext; // [esp+0h] [ebp-10h] BYREF

  if ( ptFrontSprite || ptSideSprite )
  {
    tContext.ptFrontSprite = ptFrontSprite;
    tContext.ptSideSprite = ptSideSprite;
    tContext.vRadius = vRadius;
    tContext.nWeapon = nWeapon;
    return QTask_NewFn(ptParent, MuzzleFlash_eQTaskType, &tContext);
  }
  return (struct QTask_s *)ptFrontSprite;
}

// source: j/0/weapons/muzzleflash.c:459  [size]
unsigned __int16 __cdecl MuzzleFlash_GetQTaskType()
{
  return MuzzleFlash_eQTaskType;
}

// source: j/0/weapons/muzzleflash.c:472  [anchor-hash]
void __cdecl MuzzleFlash_Open()
{
  unsigned __int16 v0; // si

  v0 = QTask_NewQTaskType("MuzzleFlash", 672, PolyListDynCubeObj_eQTaskType, 0, 0);
  MuzzleFlash_eQTaskType = v0;
  QTask_LinkQTaskEventHandlerFn(v0, 0, MuzzleFlash_CreateHandler);
  QTask_LinkQTaskEventHandlerFn(v0, 5, MuzzleFlash_EnterHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 2, MuzzleFlash_DeleteHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 1, MuzzleFlash_RunHandler);
  QTask_LinkQTaskEventHandlerFn(v0, DynCubeObj_eDynCubeObjRegisterQTaskEvent, nullptr);
  QTask_LinkQTaskEventHandlerFn(v0, DynCubeObj_eDynCubeObjRemoveQTaskEvent, MuzzleFlash_RemoveHandler);
}

// source: j/0/weapons/muzzleflash.c:495  [size]
void __cdecl MuzzleFlash_Close()
{
  QTask_DeleteQTaskType(MuzzleFlash_eQTaskType);
}
