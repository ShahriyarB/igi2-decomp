/* j/0/vehicles/missile.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/vehicles/missile.c:157  [size]
void __cdecl Missile_DeleteSmokeCallback(struct QReference_s *ptQTaskRef, void *pxUnused)
{
  QTask_DeleteQTaskAndQTaskRefSafe(&ptQTaskRef);
}

// source: j/0/vehicles/missile.c:170  [anchor-hash]
void __cdecl Missile_DeleteAllSmoke()
{
  struct QReference_s *v0; // ecx
  unsigned int v1; // edi
  struct QVector_s *v2; // ebx
  void ***p_papxElement; // ebp
  struct QReference_s *pptQTaskRef; // [esp+0h] [ebp-4h] BYREF

  pptQTaskRef = v0;
  v1 = 0;
  v2 = Missile_ptSmokeQVector;
  if ( Missile_ptSmokeQVector->tPrivate.nElements )
  {
    p_papxElement = &Missile_ptSmokeQVector->tPrivate.papxElement;
    do
    {
      pptQTaskRef = (struct QReference_s *)(*p_papxElement)[v1];
      QTask_DeleteQTaskAndQTaskRefSafe(&pptQTaskRef);
      ++v1;
    }
    while ( v1 < v2->tPrivate.nElements );
    Missile_ptSmokeQVector->tPrivate.nElements = 0;
  }
  else
  {
    Missile_ptSmokeQVector->tPrivate.nElements = 0;
  }
}

// source: j/0/vehicles/missile.c:184  [anchor-mhash]
void __cdecl Missile_DeSerializeDoneHandler(struct QTask_s *ptQTask, void *pxContext)
{
  QTask_DeleteQTaskAndQTaskRefSafe((struct QReference_s **)&ptQTask[55].ptParent);
  QTask_Delete(ptQTask);
}

// source: j/0/vehicles/missile.c:201  [anchor-callee]
struct QTask_s *__cdecl Missile_InitSound(struct QTask_s *ptQTask)
{
  struct QTask_s *result; // eax
  struct QTask_s *v3; // esi
  struct QTask_s *v4; // eax
  int v5; // ecx

  result = SoundSys_NewSoundFn(ptQTask, (char *)(*(_DWORD *)(*(_DWORD *)&ptQTask[12].eQTaskType + 724) + 572));
  v3 = result;
  if ( result )
  {
    v4 = (struct QTask_s *)QTask_NewQTaskRef(result);
    v5 = 511 * SoundSys_eSetPositionQTaskEvent;
    ptQTask[56].ptParent = v4;
    return ((struct QTask_s *(__cdecl *)(struct QTask_s *, struct QTask_s *))QTask_aatQTaskFinalEvent[0][v3->eQTaskType + v5].pfHandler)(
             v3,
             &ptQTask[1]);
  }
  return result;
}

// source: j/0/vehicles/missile.c:230  [anchor-mhash]
void __cdecl Missile_UpdateSound(struct QTask_s *ptQTask)
{
  struct QTask_s *ptParent; // eax
  struct QTask_s *ptHead; // eax

  ptParent = ptQTask[56].ptParent;
  if ( ptParent )
  {
    ptHead = ptParent->tQTaskChildren.ptHead;
    if ( ptHead )
      ((void (__cdecl *)(struct QTask_s *, struct QTask_s *))QTask_aatQTaskFinalEvent[SoundSys_eSetPositionQTaskEvent][ptHead->eQTaskType].pfHandler)(
        ptHead,
        &ptQTask[1]);
  }
}

// source: j/0/vehicles/missile.c:254  [anchor-callee]
void __cdecl Missile_InitSmoke(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { unsigned int vDelta; };
    struct { struct QReference_s *vDeltaa; };
    struct { float vDeltab; };
    struct { char igi2_o3[4]; struct real32x2_t tvSize; };
    struct { char igi2_o4[12]; char tvRGB[13]; };
    struct { char igi2_o5[25]; char tvAccel_1; };
    struct { char igi2_o6[26]; __int16 tvAccel_2; };
    struct { char igi2_o7[28]; int tvAccel_4; };
    struct { char igi2_o8[32]; int tvAccel_8; };
    char igi2_extent[40];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v1; // eax
  struct QReference_s *v2; // edx
  double v3; // st7
  struct QSprite_s *v4; // eax
  struct World_s *ptWorld; // ecx
  struct QTask_s *v6; // ebp
  struct QTask_s *v7; // eax
  struct QVector_s *v8; // ecx
  unsigned int nElements; // eax
  unsigned int v10; // ebx
  int v11; // esi
  struct QReference_s *v12; // eax
  unsigned int v13; // eax
  struct QReference_s *v14; // eax
  unsigned int v15; // ebp
  struct QVector_s *v16; // ebx

  v1 = *(_DWORD *)(*(_DWORD *)&ptQTask[12].eQTaskType + 724);
  *(_DWORD *)&ptQTask[55].eQTaskType = 1036831949;
  ptQTask[56].ptNext = (struct QTask_s *)1036831949;
  ptQTask[56].ptPrev = (struct QTask_s *)1036831949;
  ptQTask[56].tQTaskChildren.ptTail = *(struct QTask_s **)(v1 + 308);
  v2 = *(struct QReference_s **)(v1 + 300);
  ptQTask[56].tQTaskRefList.ptHead = v2;
  ptQTask[56].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[56].tQTaskRefList.ptTail = *(struct QReference_s **)(v1 + 312);
  ptQTask[56].tQTaskChildren.ptMiddle = (struct QTask_s *)1241120768;
  v3 = *(float *)(v1 + 304) / *(float *)(v1 + 300);
  v4 = *(struct QSprite_s **)(v1 + 588);
  LODWORD(igi2_frame.tvSize.vX) = v2;
  LODWORD(igi2_frame.tvSize.vY) = v2;
  ptWorld = Game_ptGame->ptWorld;
  igi2_frame.tvAccel_1 = 0;
  igi2_frame.tvAccel_2 = 0;
  igi2_frame.tvAccel_4 = 0;
  igi2_frame.tvAccel_8 = 1018324815;
  strcpy(igi2_frame.tvRGB, "33KA33KA33KA");
  igi2_frame.vDeltab = (v3 - 1.0) / (*(float *)&ptQTask[56].tQTaskRefList.ptTail * 30.0);
  v6 = Particle2DDynCubeObj_New(
         Level_ptDynamicQTask,
         ptWorld,
         v4 + 1,
         (struct real32x3_t *)&igi2_frame.tvRGB[12],
         (struct real32x3_t *)igi2_frame.tvRGB,
         &igi2_frame.tvSize,
         2048000.0,
         (int)&MTP_atLODVirModel[48].atBoneVertexRefs[1].atVertexRefs[668],
         0,
         igi2_frame.vDeltab,
         0.0,
         2000,
         nullptr);
  v7 = (struct QTask_s *)QTask_NewQTaskRef(v6);
  v8 = Missile_ptSmokeQVector;
  ptQTask[55].ptParent = v7;
  nElements = v8->tPrivate.nElements;
  if ( v8->tPrivate.nElements )
  {
    v10 = nElements - 1;
    v11 = 4 * nElements - 4;
    igi2_frame.vDelta = v8->tPrivate.nElements;
    do
    {
      v12 = *(struct QReference_s **)((char *)v8->tPrivate.papxElement + v11);
      if ( !v12->pxObject )
      {
        QReference_Delete(v12, &QTask_tQTaskRefPool);
        v8 = Missile_ptSmokeQVector;
        v13 = Missile_ptSmokeQVector->tPrivate.nElements - 1;
        Missile_ptSmokeQVector->tPrivate.nElements = v13;
        if ( v10 < v13 )
        {
          if ( v8->tPrivate.isStrictOrder )
          {
            memmove((char *)v8->tPrivate.papxElement + v11, (char *)v8->tPrivate.papxElement + v11 + 4, 4 * (v13 - v10));
            v8 = Missile_ptSmokeQVector;
          }
          else
          {
            *(void **)((char *)v8->tPrivate.papxElement + v11) = v8->tPrivate.papxElement[v13];
          }
        }
      }
      v11 -= 4;
      --v10;
      --igi2_frame.vDelta;
    }
    while ( igi2_frame.vDelta );
  }
  v14 = QTask_NewQTaskRef(v6);
  v15 = Missile_ptSmokeQVector->tPrivate.nElements;
  igi2_frame.vDeltaa = v14;
  v16 = Missile_ptSmokeQVector;
  if ( Missile_ptSmokeQVector->tPrivate.nElements == Missile_ptSmokeQVector->tPrivate.nArraySize )
    QVector_Realloc(Missile_ptSmokeQVector, 1u);
  if ( v15 < v16->tPrivate.nElements - 1 )
    memmove(&v16->tPrivate.papxElement[v15 + 1], &v16->tPrivate.papxElement[v15], 4 * (v16->tPrivate.nElements - v15));
  ++v16->tPrivate.nElements;
  v16->tPrivate.papxElement[v15] = igi2_frame.vDeltaa;
  BYTE1(ptQTask[55].ptParent->tQTaskChildren.ptHead[6].tQTaskRefList.ptHead) = 1;
  ptQTask[56].tQTaskChildren.ptHead = nullptr;
}

// source: j/0/vehicles/missile.c:343  [anchor-callee]
void __cdecl Missile_AddSmoke(struct Missile_s *ptMissile)
{
  #pragma pack(push, 1)
  union
  {
    struct { float ptVel; };
    struct { char igi2_o1[4]; float vIntensity; };
    struct { char igi2_o2[16]; int v39; };
    struct { char igi2_o3[40]; float v40; };
    struct { char igi2_o4[44]; struct real32x3_t tLocalPos; };
    struct { char igi2_o5[64]; struct real32x3_t tPartVel; };
    struct { char igi2_o6[76]; struct real64x3_t tPartPos; };
    struct { char igi2_o7[100]; struct real64x3_t tSpeed; };
    char igi2_extent[124];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v2; // edx
  float vX; // ecx
  unsigned int v4; // ecx
  double v5; // st7
  int nMagicVertex; // eax
  double v7; // st7
  double v8; // st6
  double v9; // st6
  double v10; // st7
  float vY; // ecx
  float vZ; // edx
  int v13; // eax
  double v14; // st7
  double v15; // st6
  double v16; // st5
  unsigned int v17; // ecx
  unsigned int v18; // edx
  unsigned int v19; // eax
  int v20; // ecx
  int v21; // edx
  unsigned int v22; // eax
  int v23; // ecx
  int v24; // edx
  unsigned int v25; // eax
  int v26; // ecx
  int v27; // edx
  unsigned int v28; // eax
  int vX_low; // esi
  double v30; // st7
  int v31; // ecx
  int v32; // edx
  unsigned int v33; // eax
  int v34; // ecx
  int v35; // edx
  bool v36; // zf
  float ptMissilea = *(float *)&ptMissile; // [esp+80h] [ebp+4h] ARGSLOT
  int ptMissileb = *(int *)&ptMissile; // [esp+80h] [ebp+4h] ARGSLOT
  float ptMissiled = *(float *)&ptMissile; // [esp+80h] [ebp+4h] ARGSLOT
  struct Missile_s *ptMissilec = *(struct Missile_s * *)&ptMissile; // [esp+80h] [ebp+4h] ARGSLOT

  v2 = ptMissile->tSmoke.nTickMoreSmoke + 1;
  *(_QWORD *)&igi2_frame.tLocalPos.vX = (__int64)ptMissile->tSmoke.vDensity;
  vX = igi2_frame.tLocalPos.vX;
  ptMissile->tSmoke.nTickMoreSmoke = v2;
  if ( v2 >= SLODWORD(vX) )
  {
    v4 = (Missile_tRandomState.anRandom[0] >> 7) ^ Missile_tRandomState.anRandom[2];
    Missile_tRandomState.anRandom[0] += v4 ^ Missile_tRandomState.anRandom[1];
    v5 = (double)LOWORD(Missile_tRandomState.anRandom[0]);
    Missile_tRandomState.anRandom[2] = v4;
    Missile_tRandomState.anRandom[1] ^= v4;
    nMagicVertex = ptMissile->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.ptLODVirModel->aptVirModel[0]->ptModel->ptMesh->nMagicVertex;
    ptMissilea = ptMissile->tVehicle.tPhysicsObj.tPhysics.vCMSpeed;
    ptMissile->tSmoke.nTickMoreSmoke = 0;
    igi2_frame.v40 = v5 * 0.0000152587890625 * 0.30000001192092896 + 0.15000000596046448;
    if ( nMagicVertex )
    {
      if ( nMagicVertex == 1 )
      {
        GameFunctions_GetMagicVertexLocal(
          &igi2_frame.tLocalPos,
          &ptMissile->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask,
          0);
        v7 = -igi2_frame.tLocalPos.vY;
        v8 = igi2_frame.tLocalPos.vZ * ptMissile->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tX.vZ;
        qmemcpy(
          &igi2_frame.tPartPos,
          &ptMissile->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos,
          sizeof(igi2_frame.tPartPos));
        v9 = v8
           + igi2_frame.tLocalPos.vX * ptMissile->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tX.vX
           + v7 * ptMissile->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tX.vY;
        igi2_frame.tPartVel.vY = igi2_frame.tLocalPos.vZ * ptMissile->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tY.vZ
                    + igi2_frame.tLocalPos.vX * ptMissile->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tY.vX
                    + v7 * ptMissile->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tY.vY;
        igi2_frame.tPartVel.vZ = igi2_frame.tLocalPos.vZ * ptMissile->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tZ.vZ
                    + igi2_frame.tLocalPos.vX * ptMissile->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tZ.vX
                    + v7 * ptMissile->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tZ.vY;
        igi2_frame.tPartPos.vX = v9 + igi2_frame.tPartPos.vX;
        igi2_frame.tPartPos.vY = igi2_frame.tPartVel.vY + igi2_frame.tPartPos.vY;
        igi2_frame.tPartPos.vZ = igi2_frame.tPartVel.vZ + igi2_frame.tPartPos.vZ;
      }
      else
      {
        GameFunctions_GetMagicVertex(
          &igi2_frame.tPartPos,
          &ptMissile->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask,
          1);
      }
    }
    else
    {
      qmemcpy(
        &igi2_frame.tPartPos,
        &ptMissile->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos,
        sizeof(igi2_frame.tPartPos));
    }
    v10 = ptMissilea / ptMissile->tSmoke.vSize;
    vY = ptMissile->tVehicle.tPhysicsObj.tPhysics.tCMVelDir.vY;
    vZ = ptMissile->tVehicle.tPhysicsObj.tPhysics.tCMVelDir.vZ;
    igi2_frame.tPartVel.vX = ptMissile->tVehicle.tPhysicsObj.tPhysics.tCMVelDir.vX;
    igi2_frame.tPartVel.vY = vY;
    igi2_frame.tPartVel.vZ = vZ;
    *(_QWORD *)&igi2_frame.tLocalPos.vX = (__int64)v10;
    v13 = (__int64)v10;
    ptMissileb = v13;
    if ( v13 <= 1 )
    {
      v13 = 1;
      ptMissileb = 1;
    }
    v14 = ptMissile->tVehicle.tPhysicsObj.tPhysics.tCMVel.vX;
    v15 = ptMissile->tVehicle.tPhysicsObj.tPhysics.tCMVel.vY;
    igi2_frame.tSpeed.vZ = ptMissile->tVehicle.tPhysicsObj.tPhysics.tCMVel.vZ;
    v16 = 1.0 / (double)ptMissileb;
    ptMissiled = v16;
    igi2_frame.tSpeed.vX = v16 * v14;
    igi2_frame.tSpeed.vY = ptMissiled * v15;
    igi2_frame.tSpeed.vZ = ptMissiled * igi2_frame.tSpeed.vZ;
    ptMissilec = (struct Missile_s *)v13;
    do
    {
      v17 = (Missile_tRandomState.anRandom[0] >> 7) ^ Missile_tRandomState.anRandom[2];
      v18 = v17 ^ Missile_tRandomState.anRandom[1];
      v19 = (v17 ^ Missile_tRandomState.anRandom[1]) + Missile_tRandomState.anRandom[0];
      v20 = (v19 >> 7) ^ v17;
      v21 = v20 ^ v18;
      v22 = v21 + v19;
      v23 = (v22 >> 7) ^ v20;
      v24 = v23 ^ v21;
      v25 = v24 + v22;
      Missile_tRandomState.anRandom[2] = v23;
      v26 = (v25 >> 7) ^ v23;
      Missile_tRandomState.anRandom[1] = v24;
      Missile_tRandomState.anRandom[0] = v25;
      v27 = v26 ^ v24;
      v28 = v27 + v25;
      *(_QWORD *)&igi2_frame.tLocalPos.vX = (__int64)(ptMissile->tSmoke.vLifeTime * 3.0);
      vX_low = LODWORD(igi2_frame.tLocalPos.vX);
      LODWORD(igi2_frame.tLocalPos.vX) = (unsigned __int16)v28;
      v30 = (double)(unsigned __int16)v28;
      Missile_tRandomState.anRandom[2] = v26;
      Missile_tRandomState.anRandom[1] = v27;
      Missile_tRandomState.anRandom[0] = v28;
      v31 = (v28 >> 7) ^ v26;
      v32 = v31 ^ v27;
      v33 = v32 + v28;
      *(_QWORD *)&igi2_frame.tLocalPos.vX = (__int64)((v30 * 0.0000152587890625 * 0.30000001192092896 + 0.6000000238418579)
                                         * ptMissile->tSmoke.vLifeTime
                                         * 30.0);
      v34 = (v33 >> 7) ^ v31;
      igi2_frame.v39 = LODWORD(igi2_frame.tLocalPos.vX);
      v35 = v34 ^ v32;
      Missile_tRandomState.anRandom[0] = v35 + v33;
      igi2_frame.vIntensity = (double)(unsigned __int16)v33 * 0.0000152587890625 * 6.2831854820251465;
      LODWORD(igi2_frame.tLocalPos.vX) = (unsigned __int16)(v35 + v33);
      Missile_tRandomState.anRandom[2] = v34;
      Missile_tRandomState.anRandom[1] = v35;
      igi2_frame.ptVel = (0.5 - (double)SLODWORD(igi2_frame.tLocalPos.vX) * 0.0000152587890625) * 0.03769911453127861;
      Particle2DDynCubeObj_AddParticle(
        (struct QTask_s *)ptMissile->tSmoke.ptParticleQTask->pxObject,
        &igi2_frame.tPartPos,
        &igi2_frame.tPartVel,
        igi2_frame.v40,
        igi2_frame.ptVel,
        igi2_frame.vIntensity,
        1.0,
        vX_low,
        igi2_frame.v39);
      v36 = ptMissilec == (struct Missile_s *)1;
      igi2_frame.tPartPos.vX = igi2_frame.tSpeed.vX + igi2_frame.tPartPos.vX;
      ptMissilec = (struct Missile_s *)((char *)ptMissilec - 1);
      igi2_frame.tPartPos.vY = igi2_frame.tSpeed.vY + igi2_frame.tPartPos.vY;
      igi2_frame.tPartPos.vZ = igi2_frame.tSpeed.vZ + igi2_frame.tPartPos.vZ;
    }
    while ( !v36 );
  }
}

// source: j/0/vehicles/missile.c:463  [size]
struct Missile_s *__cdecl Missile_MoveDirectCB(
        struct Missile_s *ptMissile,
        struct real64x3_t *ptTarget)
{
  ptMissile->tVehicle.vIdealDeltaAlpha = 0.0;
  ptMissile->tVehicle.vIdealDeltaGamma = 0.0;
  return ptMissile;
}

// source: j/0/vehicles/missile.c:477  [anchor-callee]
void __cdecl Missile_MoveHindCB(struct Missile_s *ptMissile)
{
  #pragma pack(push, 1)
  union
  {
    struct { double vDot; };
    struct { char igi2_o1[8]; struct real64x3_t tTarget; };
    struct { char igi2_o2[32]; struct real64x3_t tAdd; };
    char igi2_extent[60];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  double v1; // st7
  double v2; // st6
  long double v3; // st5

  v1 = ptMissile->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos.vX - ptMissile->tTarget.vX;
  v2 = ptMissile->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos.vY - ptMissile->tTarget.vY;
  igi2_frame.tTarget.vZ = ptMissile->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos.vZ
             - ptMissile->tTarget.vZ;
  igi2_frame.vDot = igi2_frame.tTarget.vZ * ptMissile->tDelta.vZ + v2 * ptMissile->tDelta.vY + v1 * ptMissile->tDelta.vX;
  igi2_frame.tTarget.vX = igi2_frame.vDot * v1;
  igi2_frame.tTarget.vY = igi2_frame.vDot * v2;
  igi2_frame.tTarget.vZ = igi2_frame.vDot * igi2_frame.tTarget.vZ;
  qmemcpy(&igi2_frame.tAdd, &igi2_frame.tTarget, sizeof(igi2_frame.tAdd));
  v3 = 1.0 / sqrt(igi2_frame.tTarget.vY * igi2_frame.tTarget.vY + igi2_frame.tTarget.vZ * igi2_frame.tTarget.vZ + igi2_frame.tTarget.vX * igi2_frame.tTarget.vX);
  igi2_frame.tAdd.vY = v3 * igi2_frame.tAdd.vY * 12288.0;
  igi2_frame.tAdd.vZ = v3 * igi2_frame.tAdd.vZ * 12288.0;
  igi2_frame.tTarget.vX = igi2_frame.tTarget.vX * v3 * 12288.0 + igi2_frame.tTarget.vX;
  igi2_frame.tTarget.vY = igi2_frame.tAdd.vY + igi2_frame.tTarget.vY;
  igi2_frame.tTarget.vZ = igi2_frame.tAdd.vZ + igi2_frame.tTarget.vZ;
  Missile_MoveTowardsTarget(ptMissile, &igi2_frame.tTarget);
}

// source: j/0/vehicles/missile.c:504  [anchor-callee]
struct Missile_s *__cdecl Missile_MoveKeyboardCB(struct Missile_s *ptMissile)
{
  ptMissile->tVehicle.vIdealDeltaGamma = (float)((Keyboard_tKeyboard.anCurrentKey[205] >> 7)
                                               - (Keyboard_tKeyboard.anCurrentKey[203] >> 7));
  ptMissile->tVehicle.vIdealDeltaAlpha = (float)((Keyboard_tKeyboard.anCurrentKey[208] >> 7)
                                               - (Keyboard_tKeyboard.anCurrentKey[200] >> 7));
  return ptMissile;
}

// source: j/0/vehicles/missile.c:521  [anchor-callee]
struct real64x3_t *__cdecl Missile_MoveBallisticCB(
        struct Missile_s *ptMissile,
        struct real64x3_t *ptTarget)
{
  double v2; // st7
  double v3; // st6
  double vY; // st5
  struct real64x3_t *result; // eax
  struct real64x3_t tTargetPos; // [esp+8h] [ebp-1Ch] BYREF

  v2 = ptTarget->vX - ptMissile->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos.vX;
  tTargetPos.vX = v2;
  tTargetPos.vY = ptTarget->vY - ptMissile->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos.vY;
  v3 = ptTarget->vZ - ptMissile->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos.vZ;
  vY = tTargetPos.vY;
  qmemcpy(&tTargetPos, ptTarget, sizeof(tTargetPos));
  tTargetPos.vZ = sqrt(vY * vY + v3 * v3 + v2 * v2) * 0.125 + tTargetPos.vZ;
  Missile_MoveTowardsTarget(ptMissile, &tTargetPos);
  return result;
}

// source: j/0/vehicles/missile.c:559  [anchor-callee]
struct real64x3_t *__cdecl Missile_MoveAntiTankCB(
        struct Missile_s *ptMissile,
        struct real64x3_t *ptTarget)
{
  double v2; // st7
  double v3; // st6
  struct real64x3_t *result; // eax
  struct real64x3_t tTargetPos; // [esp+8h] [ebp-1Ch] BYREF

  v2 = ptTarget->vX - ptMissile->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos.vX;
  tTargetPos.vX = v2;
  v3 = ptTarget->vY - ptMissile->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos.vY;
  qmemcpy(&tTargetPos, ptTarget, sizeof(tTargetPos));
  if ( sqrt(v3 * v3 + v2 * v2) <= 122880.0 )
    return Missile_MoveBallisticCB(ptMissile, &tTargetPos);
  tTargetPos.vZ = tTargetPos.vZ + 102400.0;
  Missile_MoveTowardsTarget(ptMissile, &tTargetPos);
  return result;
}

// source: j/0/vehicles/missile.c:604  [anchor-callee]
void __cdecl Missile_MoveTowardsTarget(
        struct Missile_s *ptMissile,
        struct real64x3_t *ptTarget)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct real64x3_t v6; };
    struct { char igi2_o1[32]; double vAlpha; };
    struct { char igi2_o2[40]; struct real64x3_t Real64x3_RotateInverse_tTemp; };
    char igi2_extent[68];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  double v2; // st7
  double v3; // st6
  double v4; // st5
  double v5; // st7

  v2 = ptTarget->vX - ptMissile->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos.vX;
  v3 = ptTarget->vY - ptMissile->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos.vY;
  v4 = ptTarget->vZ - ptMissile->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos.vZ;
  igi2_frame.Real64x3_RotateInverse_tTemp.vX = ptMissile->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tZ.vX * v4
                                  + ptMissile->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tY.vX * v3
                                  + ptMissile->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tX.vX * v2;
  igi2_frame.Real64x3_RotateInverse_tTemp.vY = ptMissile->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tZ.vY * v4
                                  + ptMissile->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tY.vY * v3
                                  + ptMissile->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tX.vY * v2;
  igi2_frame.Real64x3_RotateInverse_tTemp.vZ = ptMissile->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tZ.vZ * v4
                                  + ptMissile->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tY.vZ * v3
                                  + ptMissile->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tX.vZ * v2;
  qmemcpy(&igi2_frame.v6, &igi2_frame.Real64x3_RotateInverse_tTemp, sizeof(igi2_frame.v6));
  igi2_frame.vAlpha = GameFunctions_CalcAlpha(igi2_frame.v6);
  qmemcpy(&igi2_frame.v6, &igi2_frame.Real64x3_RotateInverse_tTemp, sizeof(igi2_frame.v6));
  v5 = GameFunctions_CalcGamma(igi2_frame.v6);
  if ( igi2_frame.vAlpha >= -1.0 )
  {
    if ( igi2_frame.vAlpha <= 1.0 )
      goto LABEL_6;
    HIDWORD(igi2_frame.vAlpha) = 1072693248;
  }
  else
  {
    HIDWORD(igi2_frame.vAlpha) = -1074790400;
  }
  LODWORD(igi2_frame.vAlpha) = 0;
LABEL_6:
  if ( v5 >= -1.0 )
  {
    if ( v5 > 1.0 )
      v5 = 1.0;
  }
  else
  {
    v5 = -1.0;
  }
  ptMissile->tVehicle.vIdealDeltaAlpha = igi2_frame.vAlpha;
  ptMissile->tVehicle.vIdealDeltaGamma = v5;
}

// source: j/0/vehicles/missile.c:649  [anchor-callee]
void __cdecl Missile_InitWings(struct Missile_s *ptMissile)
{
  struct Missile_s *v1; // edx
  _DWORD *pxData; // ebp
  int v3; // ebx
  struct Wing_t *atWing; // edx
  char *v5; // eax

  v1 = ptMissile;
  pxData = ptMissile->tVehicle.tPhysicsObj.ptType->pxData;
  v3 = 0;
  if ( (int)pxData[10] > 0 )
  {
    atWing = ptMissile->atWing;
    v5 = (char *)(pxData + 11);
    do
    {
      qmemcpy(atWing, v5, sizeof(struct Wing_t));
      ++v3;
      v5 += 28;
      ++atWing;
    }
    while ( v3 < (int)(pxData[10]) );
    v1 = ptMissile;
  }
  qmemcpy(&v1->atWing[2], v1->atWing, sizeof(v1->atWing[2]));
  ptMissile->atWing[2].tPos.vY = -ptMissile->atWing[2].tPos.vY;
  qmemcpy(&ptMissile->atWing[3], &ptMissile->atWing[1], sizeof(ptMissile->atWing[3]));
  ptMissile->atWing[3].tPos.vY = -ptMissile->atWing[3].tPos.vY;
}

// source: j/0/vehicles/missile.c:677  [anchor-mhash]
void __cdecl Missile_Init(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct World_s *ptDynCubeObj; };
    struct { float ptDynCubeObja; };
    struct { char igi2_o2[16]; struct real64x3_t tVNull; };
    char igi2_extent[44];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  double v1; // st7
  double v2; // st7
  int *v3; // eax
  int v4; // eax
  double v5; // st6

  igi2_frame.ptDynCubeObj = Game_ptGame->ptWorld;
  memset(&igi2_frame.tVNull, 0, sizeof(igi2_frame.tVNull));
  ModelObj_Init((struct ModelObj_s *)ptQTask, igi2_frame.ptDynCubeObj, nullptr);
  ptQTask[7].tQTaskChildren.ptHead = nullptr;
  ptQTask[7].tQTaskChildren.ptMiddle = (struct QTask_s *)2;
  ptQTask[7].tQTaskRefList.ptHead = nullptr;
  ptQTask[7].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[7].tQTaskRefList.ptTail = nullptr;
  ptQTask[7].ptParent = nullptr;
  *(_DWORD *)&ptQTask[7].eQTaskType = 0;
  if ( *(float *)&ptQTask[6].tQTaskChildren.ptHead <= (double)*(float *)&ptQTask[6].tQTaskChildren.ptMiddle )
    v1 = *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
  else
    v1 = *(float *)&ptQTask[6].tQTaskChildren.ptHead;
  if ( v1 >= *(float *)&ptQTask[6].ptPrev )
  {
    if ( *(float *)&ptQTask[6].tQTaskChildren.ptHead <= (double)*(float *)&ptQTask[6].tQTaskChildren.ptMiddle )
      v2 = *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
    else
      v2 = *(float *)&ptQTask[6].tQTaskChildren.ptHead;
  }
  else
  {
    v2 = *(float *)&ptQTask[6].ptPrev;
  }
  v3 = *(int **)&ptQTask[2].eQTaskType;
  if ( v3 && (v4 = *v3) != 0 )
    v5 = *(float *)(*(_DWORD *)(*(_DWORD *)(v4 + 12) + 12) + 120);
  else
    v5 = 1.0;
  igi2_frame.ptDynCubeObja = v2 * v5;
  World_RegisterDynCubeObjFirstTimeRadius(
    Game_ptGame->ptWorld,
    (struct DynCubeObj_s *)ptQTask,
    &igi2_frame.tVNull,
    igi2_frame.ptDynCubeObja,
    WORLD_DYNCUBETREE_CATEGORY_MOBILE);
  LOBYTE(ptQTask[10].tQTaskRefList.ptHead) = 0;
  Vehicle_Create((struct Vehicle_s *)ptQTask);
  ptQTask[48].tQTaskChildren.ptTail = nullptr;
  ptQTask[55].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[55].tQTaskRefList.ptHead = nullptr;
  ptQTask[55].tQTaskChildren.ptTail = nullptr;
  ptQTask[56].ptParent = nullptr;
  *(_DWORD *)&ptQTask[56].eQTaskType = 0;
  ptQTask[55].ptParent = nullptr;
}

// source: j/0/vehicles/missile.c:723  [anchor-caller]
void __cdecl Missile_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  Missile_Init(ptQTask);
}

// source: j/0/vehicles/missile.c:737  [anchor-strings]
void __cdecl Missile_RunHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct World_s *ptWorld; };
    struct { struct World_s *v18; };
    struct { char igi2_o2[20]; struct WeaponType_s *v19; };
    struct { char igi2_o3[48]; double vDistance; };
    struct { char igi2_o4[60]; struct GetNextZEvaluateContext_t tGetNextZEvaluateContext; };
    struct { char igi2_o5[68]; struct MissileType_s *ptMissileType; };
    struct { char igi2_o6[72]; struct real64x3_t tCollPos; };
    struct { char igi2_o7[96]; struct QIntersection_s tIntersection; };
    char igi2_extent[216];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v1; // ebx
  struct QReference_s *ptMiddle; // eax
  char *pxObject; // eax
  int v4; // eax
  struct QTask_s *ptParent; // eax
  struct QTask_s *ptHead; // eax
  struct QTask_s *ptNext; // eax
  struct QTask_s *v8; // ecx
  int v9; // edx
  struct QTask_s *v10; // eax
  void (__cdecl *pfHandler)(_DWORD); // eax
  int v12; // edx
  struct QTask_s *ptTail; // eax
  struct QTask_s *v14; // ebx
  int v15; // ecx
  _BYTE *v16; // eax

  v1 = *(_DWORD *)(*(_DWORD *)&ptQTask[12].eQTaskType + 724);
  ptMiddle = ptQTask[55].tQTaskRefList.ptMiddle;
  igi2_frame.ptMissileType = (struct MissileType_s *)v1;
  if ( ptMiddle )
  {
    pxObject = (char *)ptMiddle->pxObject;
    if ( pxObject )
      qmemcpy(&ptQTask[54].tQTaskChildren, pxObject + 40, 0x18u);
  }
  v4 = *(_DWORD *)(v1 + 284);
  if ( v4 )
  {
    switch ( v4 )
    {
      case 1:
        Missile_MoveHindCB((struct Missile_s *)ptQTask);
        break;
      case 2:
        Missile_MoveBallisticCB((struct Missile_s *)ptQTask, (struct real64x3_t *)&ptQTask[54].tQTaskChildren);
        break;
      case 3:
        Missile_MoveAntiTankCB((struct Missile_s *)ptQTask, (struct real64x3_t *)&ptQTask[54].tQTaskChildren);
        break;
      case 4:
        Missile_MoveKeyboardCB((struct Missile_s *)ptQTask);
        break;
    }
  }
  else
  {
    ptQTask[48].ptPrev = nullptr;
    ptQTask[48].tQTaskChildren.ptMiddle = nullptr;
  }
  if ( *(float *)&ptQTask[55].tQTaskRefList.ptTail != 0.0 && *(_DWORD *)(v1 + 280) )
    Missile_AddSmoke((struct Missile_s *)ptQTask);
  Missile_Move((struct Missile_s *)ptQTask);
  ptParent = ptQTask[56].ptParent;
  if ( ptParent )
  {
    ptHead = ptParent->tQTaskChildren.ptHead;
    if ( ptHead )
      ((void (__cdecl *)(struct QTask_s *, struct QTask_s *))QTask_aatQTaskFinalEvent[SoundSys_eSetPositionQTaskEvent][ptHead->eQTaskType].pfHandler)(
        ptHead,
        &ptQTask[1]);
  }
  ptNext = ptQTask[3].ptNext;
  if ( ptNext )
    ((void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[1][ptNext->eQTaskType].pfHandler)(ptQTask[3].ptNext);
  v8 = ptQTask->tQTaskChildren.ptHead;
  if ( v8->ptNext && v8 )
  {
    v9 = QTask_nProtectedQTaskStackOffset;
    do
    {
      if ( v8->ptNext )
        v10 = v8->ptNext->ptNext != nullptr ? v8->ptNext : nullptr;
      else
        v10 = nullptr;
      QTask_atProtectedQTaskStack[v9].ptQTask = v10;
      pfHandler = (void (__cdecl *)(_DWORD))QTask_aatQTaskFinalEvent[1][v8->eQTaskType].pfHandler;
      v12 = v9 + 1;
      QTask_nProtectedQTaskStackOffset = v12;
      if ( pfHandler )
      {
        pfHandler(v8);
        v12 = QTask_nProtectedQTaskStackOffset;
      }
      v8 = (struct QTask_s *)dword_849C7DC[v12];
      v9 = v12 - 1;
      QTask_nProtectedQTaskStackOffset = v9;
    }
    while ( v8 );
  }
  if ( ptQTask[13].ptNext )
  {
    ptTail = ptQTask[55].tQTaskChildren.ptTail;
    if ( ptTail )
      v14 = ptTail->tQTaskChildren.ptHead;
    else
      v14 = nullptr;
    v15 = 0;
    v16 = (char *)&ptQTask[15].tQTaskChildren.ptHead + 2;
    do
    {
      if ( *(v16 - 56) )
        break;
      if ( *v16 )
        break;
      v15 += 2;
      v16 += 112;
    }
    while ( v15 < 22 );
    qmemcpy(&igi2_frame.tCollPos, &ptQTask[1], sizeof(igi2_frame.tCollPos));
    igi2_frame.tGetNextZEvaluateContext.tCollisionEvaluateContext.ptQTask = ptQTask;
    igi2_frame.ptWorld = Game_ptGame->ptWorld;
    igi2_frame.vDistance = -12288.0;
    World_GetNextZNoMaterial(
      igi2_frame.ptWorld,
      &igi2_frame.tIntersection,
      &igi2_frame.tCollPos,
      1,
      &igi2_frame.vDistance,
      13,
      &igi2_frame.tGetNextZEvaluateContext.tCollisionEvaluateContext,
      0xFFFFFFFF);
    igi2_frame.v19 = *(struct WeaponType_s **)&ptQTask[56].eQTaskType;
    if ( igi2_frame.ptMissileType->eMissileType == MISSILE_TYPE_MISSILE_BALLISTIC )
      Explosion0_New(
        &igi2_frame.tCollPos,
        1,
        1,
        0.6000000238418579,
        40960.0,
        40960.0,
        6144.0,
        10,
        5,
        &igi2_frame.tIntersection,
        "1009_01_1",
        "explo_03_l",
        20,
        0x402u,
        307200.0,
        igi2_frame.v19,
        v14,
        EXPLOSIONDAMAGE_LINEAR_FALLOFF);
    else
      Explosion0_New(
        &igi2_frame.tCollPos,
        1,
        1,
        5.0,
        8192.0,
        12288.0,
        6144.0,
        10,
        5,
        &igi2_frame.tIntersection,
        "1009_01_1",
        "explo_03_l",
        20,
        0x402u,
        307200.0,
        igi2_frame.v19,
        v14,
        EXPLOSIONDAMAGE_LINEAR_FALLOFF);
    goto LABEL_44;
  }
  if ( (LevelFlow_ptLevelFlow->nTick & 0x1F) == 0 )
  {
    qmemcpy(&igi2_frame.tCollPos, &ptQTask[1], sizeof(igi2_frame.tCollPos));
    igi2_frame.tGetNextZEvaluateContext.tCollisionEvaluateContext.ptQTask = ptQTask;
    igi2_frame.v18 = Game_ptGame->ptWorld;
    igi2_frame.vDistance = -4096000.0;
    World_GetNextZNoMaterial(
      igi2_frame.v18,
      &igi2_frame.tIntersection,
      &igi2_frame.tCollPos,
      1,
      &igi2_frame.vDistance,
      13,
      &igi2_frame.tGetNextZEvaluateContext.tCollisionEvaluateContext,
      0xFFFFFFFF);
    if ( !igi2_frame.tIntersection.isHit )
LABEL_44:
      QTask_Delete(ptQTask);
  }
}

// source: j/0/vehicles/missile.c:963  [anchor-mhash]
void __cdecl Missile_DeleteHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptParent; // eax
  struct QTask_s *ptTail; // eax
  struct QReference_s *ptHead; // eax
  struct QReference_s *ptMiddle; // eax

  if ( ptQTask[3].ptNext )
  {
    QTask_Delete(ptQTask[3].ptNext);
    ptQTask[3].ptNext = nullptr;
  }
  *(_DWORD *)&ptQTask[12].eQTaskType = 0;
  Physics_DeAlloc((struct Physics_s *)&ptQTask[8]);
  ptParent = ptQTask[55].ptParent;
  if ( ptParent )
  {
    QReference_Delete((struct QReference_s *)ptParent, &QTask_tQTaskRefPool);
    ptQTask[55].ptParent = nullptr;
  }
  ptTail = ptQTask[55].tQTaskChildren.ptTail;
  if ( ptTail )
  {
    QReference_Delete((struct QReference_s *)ptTail, &QTask_tQTaskRefPool);
    ptQTask[55].tQTaskChildren.ptTail = nullptr;
  }
  ptHead = ptQTask[55].tQTaskRefList.ptHead;
  if ( ptHead )
  {
    QReference_Delete(ptHead, &QTask_tQTaskRefPool);
    ptQTask[55].tQTaskRefList.ptHead = nullptr;
  }
  ptMiddle = ptQTask[55].tQTaskRefList.ptMiddle;
  if ( ptMiddle )
  {
    QReference_Delete(ptMiddle, &QTask_tQTaskRefPool);
    ptQTask[55].tQTaskRefList.ptMiddle = nullptr;
  }
  QTask_DeleteQTaskAndQTaskRefSafe((struct QReference_s **)&ptQTask[56].ptParent);
  World_RemoveDynCubeObj(Game_ptGame->ptWorld, (struct DynCubeObj_s *)ptQTask);
}

// source: j/0/vehicles/missile.c:992  [anchor-callee]
void __cdecl Missile_Move(struct Missile_s *ptMissile)
{
  #pragma pack(push, 1)
  union
  {
    struct { float ptDest; };
    struct { char igi2_o1[4]; float vAlpha; };
    struct { char igi2_o2[8]; float vBeta; };
    struct { char igi2_o3[32]; float vBetaInertia; };
    struct { char igi2_o4[40]; struct real32x3_t tWindVelocity; };
    struct { char igi2_o5[52]; struct real32x9_t Real32x9_Multiply_tTemp; };
    struct { char igi2_o6[92]; float v58[10]; };
    char igi2_extent[132];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  void *pxData; // ebx
  double vRealThrust; // st7
  float v4; // eax
  float v5; // ecx
  float v6; // edx
  double v7; // st7
  double v8; // st6
  unsigned int v9; // ecx
  unsigned int v10; // edx
  unsigned int v11; // eax
  double v12; // st7
  int v13; // ecx
  int v14; // edx
  unsigned int v15; // eax
  int v16; // ecx
  int v17; // edx
  double v18; // st7
  struct PointForce_s *v19; // edi
  double v20; // st7
  double v21; // st7
  struct QReference_s *ptCreatorQTaskRef; // eax
  long double v23; // st7
  long double v24; // st6
  long double v25; // rt0
  long double v26; // st5
  double v27; // st3
  double v28; // st3
  double v29; // st7
  long double v30; // st4
  long double v31; // st5
  long double v32; // st4
  long double v33; // st7
  double v34; // st6
  double v35; // st5
  double v36; // st5
  double v37; // st5
  double v38; // rt0
  long double v39; // rt1
  double v40; // st5
  struct QReference_s *ptIgnoreQTaskRef; // eax
  int v42; // eax
  float vY; // edx
  float vZ; // ecx
  struct QTask_s *ptMagicObjContainer; // eax
  int ptHead; // ecx
  int v47; // edx
  struct QTask_s *v48; // eax
  int v49; // esi
  void (__cdecl *pfHandler)(int, struct real32x3_t *); // eax
  int v51; // edx
  float ptMissilea = *(float *)&ptMissile; // [esp+88h] [ebp+4h] ARGSLOT
  float ptMissileb = *(float *)&ptMissile; // [esp+88h] [ebp+4h] ARGSLOT
  float ptMissilec = *(float *)&ptMissile; // [esp+88h] [ebp+4h] ARGSLOT

  pxData = ptMissile->tVehicle.tPhysicsObj.ptType->pxData;
  if ( ptMissile->tVehicle.vRealThrust >= 0.699999988079071 )
    igi2_frame.vBetaInertia = *((float *)pxData + 8);
  else
    igi2_frame.vBetaInertia = *((float *)pxData + 9);
  vRealThrust = ptMissile->tVehicle.vRealThrust;
  ptMissilea = ptMissile->tVehicle.vIdealThrust;
  if ( vRealThrust < ptMissilea )
  {
    vRealThrust = vRealThrust + igi2_frame.vBetaInertia;
    if ( vRealThrust <= ptMissilea )
      goto LABEL_10;
    goto LABEL_9;
  }
  if ( vRealThrust > ptMissilea )
  {
    vRealThrust = vRealThrust - igi2_frame.vBetaInertia;
    if ( vRealThrust < ptMissilea )
LABEL_9:
      vRealThrust = ptMissilea;
  }
LABEL_10:
  if ( vRealThrust < 0.0010000000474974513 )
    vRealThrust = 0.0;
  v4 = *((float *)pxData + 6);
  v5 = *((float *)pxData + 2);
  v6 = *((float *)pxData + 4);
  ptMissile->tVehicle.vRealThrust = vRealThrust;
  v7 = ptMissile->tVehicle.vIdealDeltaAlpha * (1.0 - v5) + v5 * ptMissile->tVehicle.vRealDeltaAlpha;
  ptMissile->tVehicle.vRealDeltaAlpha = v7;
  v8 = ptMissile->tVehicle.vIdealDeltaBeta * (1.0 - v6) + v6 * ptMissile->tVehicle.vRealDeltaBeta;
  ptMissile->tVehicle.vRealDeltaBeta = v8;
  ptMissileb = ptMissile->tVehicle.vIdealDeltaGamma * (1.0 - v4) + v4 * ptMissile->tVehicle.vRealDeltaGamma;
  ptMissile->tVehicle.vRealDeltaGamma = ptMissileb;
  if ( v7 != 0.0 || v8 != 0.0 || ptMissileb != 0.0 )
  {
    v23 = v7 * *((float *)pxData + 1) * 0.01745329238474369;
    v24 = ptMissileb * *((float *)pxData + 5) * 0.01745329238474369;
    v25 = sin(v23);
    v26 = cos(v23);
    igi2_frame.Real32x9_Multiply_tTemp.tX.vX = (ptMissile->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tX.vZ
                                   + ptMissile->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tX.vY)
                                  * 0.0
                                  + ptMissile->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tX.vX;
    v27 = ptMissile->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tX.vX * 0.0;
    igi2_frame.Real32x9_Multiply_tTemp.tX.vY = v26 * ptMissile->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tX.vY
                                  + v25 * ptMissile->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tX.vZ
                                  + v27;
    igi2_frame.Real32x9_Multiply_tTemp.tX.vZ = -v25 * ptMissile->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tX.vY
                                  + v26 * ptMissile->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tX.vZ
                                  + v27;
    igi2_frame.Real32x9_Multiply_tTemp.tY.vX = (ptMissile->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tY.vZ
                                   + ptMissile->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tY.vY)
                                  * 0.0
                                  + ptMissile->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tY.vX;
    v28 = ptMissile->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tY.vX * 0.0;
    igi2_frame.Real32x9_Multiply_tTemp.tY.vY = v25 * ptMissile->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tY.vZ
                                  + v26 * ptMissile->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tY.vY
                                  + v28;
    igi2_frame.Real32x9_Multiply_tTemp.tY.vZ = v26 * ptMissile->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tY.vZ
                                  + -v25 * ptMissile->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tY.vY
                                  + v28;
    igi2_frame.Real32x9_Multiply_tTemp.tZ.vX = (ptMissile->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tZ.vY
                                   + ptMissile->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tZ.vZ)
                                  * 0.0
                                  + ptMissile->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tZ.vX;
    v29 = ptMissile->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tZ.vX * 0.0;
    igi2_frame.Real32x9_Multiply_tTemp.tZ.vY = v26 * ptMissile->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tZ.vY
                                  + v25 * ptMissile->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tZ.vZ
                                  + v29;
    v30 = v26;
    v31 = -v25 * ptMissile->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tZ.vY;
    v32 = v30 * ptMissile->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tZ.vZ;
    igi2_frame.Real32x9_Multiply_tTemp.nOps = ptMissile->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.nOps + 1;
    igi2_frame.Real32x9_Multiply_tTemp.tZ.vZ = v31 + v32 + v29;
    qmemcpy(
      &ptMissile->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation,
      &igi2_frame.Real32x9_Multiply_tTemp,
      sizeof(ptMissile->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation));
    ptMissilec = sin(v24);
    v33 = cos(v24);
    v34 = -ptMissilec;
    v35 = ptMissile->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tX.vZ * 0.0;
    igi2_frame.Real32x9_Multiply_tTemp.tX.vX = v33 * ptMissile->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tX.vX
                                  + ptMissilec
                                  * ptMissile->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tX.vY
                                  + v35;
    igi2_frame.Real32x9_Multiply_tTemp.tX.vY = v34 * ptMissile->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tX.vX
                                  + v33 * ptMissile->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tX.vY
                                  + v35;
    igi2_frame.Real32x9_Multiply_tTemp.tX.vZ = (ptMissile->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tX.vX
                                   + ptMissile->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tX.vY)
                                  * 0.0
                                  + ptMissile->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tX.vZ;
    v36 = ptMissile->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tY.vZ * 0.0;
    igi2_frame.Real32x9_Multiply_tTemp.tY.vX = v33 * ptMissile->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tY.vX
                                  + ptMissilec
                                  * ptMissile->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tY.vY
                                  + v36;
    igi2_frame.Real32x9_Multiply_tTemp.tY.vY = v34 * ptMissile->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tY.vX
                                  + v33 * ptMissile->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tY.vY
                                  + v36;
    igi2_frame.Real32x9_Multiply_tTemp.tY.vZ = (ptMissile->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tY.vX
                                   + ptMissile->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tY.vY)
                                  * 0.0
                                  + ptMissile->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tY.vZ;
    v37 = ptMissile->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tZ.vZ * 0.0;
    igi2_frame.Real32x9_Multiply_tTemp.tZ.vX = ptMissilec
                                  * ptMissile->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tZ.vY
                                  + v33 * ptMissile->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tZ.vX
                                  + v37;
    v38 = v37;
    v39 = v33 * ptMissile->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tZ.vY;
    v40 = v34 * ptMissile->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tZ.vX;
    igi2_frame.Real32x9_Multiply_tTemp.nOps = ptMissile->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.nOps + 1;
    igi2_frame.Real32x9_Multiply_tTemp.tZ.vY = v39 + v40 + v38;
    igi2_frame.Real32x9_Multiply_tTemp.tZ.vZ = (ptMissile->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tZ.vY
                                   + ptMissile->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tZ.vX)
                                  * 0.0
                                  + ptMissile->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tZ.vZ;
    qmemcpy(
      &ptMissile->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation,
      &igi2_frame.Real32x9_Multiply_tTemp,
      sizeof(ptMissile->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation));
  }
  if ( ptMissile->vFuel == 0.0 )
  {
    v9 = (Missile_tRandomState.anRandom[0] >> 7) ^ Missile_tRandomState.anRandom[2];
    v10 = v9 ^ Missile_tRandomState.anRandom[1];
    v11 = (v9 ^ Missile_tRandomState.anRandom[1]) + Missile_tRandomState.anRandom[0];
    v12 = (double)(unsigned __int16)((v9 ^ LOWORD(Missile_tRandomState.anRandom[1]))
                                   + LOWORD(Missile_tRandomState.anRandom[0]))
        * 0.0000152587890625;
    v13 = (v11 >> 7) ^ v9;
    v14 = v13 ^ v10;
    v15 = v14 + v11;
    v16 = (v15 >> 7) ^ v13;
    v17 = v16 ^ v14;
    Missile_tRandomState.anRandom[0] = v17 + v15;
    Missile_tRandomState.anRandom[2] = v16;
    Missile_tRandomState.anRandom[1] = v17;
    igi2_frame.vBeta = (0.30000001192092896 - (double)(unsigned __int16)(v17 + v15) * 0.0000152587890625) * 0.10000000149011612;
    igi2_frame.vAlpha = (0.699999988079071 - (double)(unsigned __int16)v15 * 0.0000152587890625) * 0.10000000149011612;
    igi2_frame.ptDest = (0.5 - v12) * 0.10000000149011612;
    Real32x9_Create(&igi2_frame.Real32x9_Multiply_tTemp, igi2_frame.ptDest, igi2_frame.vAlpha, igi2_frame.vBeta);
    igi2_frame.v58[0] = igi2_frame.Real32x9_Multiply_tTemp.tZ.vX
           * ptMissile->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tX.vZ
           + igi2_frame.Real32x9_Multiply_tTemp.tY.vX
           * ptMissile->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tX.vY
           + igi2_frame.Real32x9_Multiply_tTemp.tX.vX
           * ptMissile->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tX.vX;
    igi2_frame.v58[1] = igi2_frame.Real32x9_Multiply_tTemp.tZ.vY
           * ptMissile->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tX.vZ
           + igi2_frame.Real32x9_Multiply_tTemp.tY.vY
           * ptMissile->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tX.vY
           + igi2_frame.Real32x9_Multiply_tTemp.tX.vY
           * ptMissile->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tX.vX;
    igi2_frame.v58[2] = igi2_frame.Real32x9_Multiply_tTemp.tZ.vZ
           * ptMissile->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tX.vZ
           + igi2_frame.Real32x9_Multiply_tTemp.tY.vZ
           * ptMissile->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tX.vY
           + igi2_frame.Real32x9_Multiply_tTemp.tX.vZ
           * ptMissile->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tX.vX;
    igi2_frame.v58[3] = igi2_frame.Real32x9_Multiply_tTemp.tZ.vX
           * ptMissile->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tY.vZ
           + igi2_frame.Real32x9_Multiply_tTemp.tX.vX
           * ptMissile->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tY.vX
           + igi2_frame.Real32x9_Multiply_tTemp.tY.vX
           * ptMissile->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tY.vY;
    igi2_frame.v58[4] = igi2_frame.Real32x9_Multiply_tTemp.tZ.vY
           * ptMissile->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tY.vZ
           + igi2_frame.Real32x9_Multiply_tTemp.tX.vY
           * ptMissile->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tY.vX
           + igi2_frame.Real32x9_Multiply_tTemp.tY.vY
           * ptMissile->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tY.vY;
    v18 = igi2_frame.Real32x9_Multiply_tTemp.tZ.vZ * ptMissile->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tY.vZ
        + igi2_frame.Real32x9_Multiply_tTemp.tX.vZ * ptMissile->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tY.vX;
    LODWORD(igi2_frame.v58[9]) = ptMissile->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.nOps
                    + igi2_frame.Real32x9_Multiply_tTemp.nOps
                    + 1;
    igi2_frame.v58[5] = v18
           + igi2_frame.Real32x9_Multiply_tTemp.tY.vZ
           * ptMissile->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tY.vY;
    igi2_frame.v58[6] = igi2_frame.Real32x9_Multiply_tTemp.tY.vX
           * ptMissile->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tZ.vY
           + igi2_frame.Real32x9_Multiply_tTemp.tZ.vX
           * ptMissile->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tZ.vZ
           + igi2_frame.Real32x9_Multiply_tTemp.tX.vX
           * ptMissile->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tZ.vX;
    igi2_frame.v58[7] = igi2_frame.Real32x9_Multiply_tTemp.tY.vY
           * ptMissile->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tZ.vY
           + igi2_frame.Real32x9_Multiply_tTemp.tZ.vY
           * ptMissile->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tZ.vZ
           + igi2_frame.Real32x9_Multiply_tTemp.tX.vY
           * ptMissile->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tZ.vX;
    igi2_frame.v58[8] = igi2_frame.Real32x9_Multiply_tTemp.tY.vZ
           * ptMissile->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tZ.vY
           + igi2_frame.Real32x9_Multiply_tTemp.tZ.vZ
           * ptMissile->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tZ.vZ
           + igi2_frame.Real32x9_Multiply_tTemp.tX.vZ
           * ptMissile->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tZ.vX;
    qmemcpy(
      &ptMissile->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation,
      igi2_frame.v58,
      sizeof(ptMissile->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation));
  }
  if ( ptMissile->tVehicle.vRealThrust != 0.0 && ptMissile->vFuel != 0.0 )
  {
    v19 = &ptMissile->tVehicle.tPhysicsObj.tPhysics.ptForces[ptMissile->tVehicle.tPhysicsObj.tPhysics.nForces];
    v20 = *((float *)pxData + 7) * ptMissile->tVehicle.vRealThrust * 44.600887298583984;
    igi2_frame.Real32x9_Multiply_tTemp.tX.vX = 0.0;
    igi2_frame.Real32x9_Multiply_tTemp.tX.vY = v20;
    memset(&igi2_frame.Real32x9_Multiply_tTemp.tX.vZ, 0, 16);
    qmemcpy(v19, &igi2_frame.Real32x9_Multiply_tTemp, sizeof(struct PointForce_s));
    ++ptMissile->tVehicle.tPhysicsObj.tPhysics.nForces;
  }
  v21 = ptMissile->vFuel - *((float *)pxData + 73);
  ptMissile->vFuel = v21;
  if ( v21 < 0.0 )
    v21 = 0.0;
  ptMissile->vFuel = v21;
  if ( !PhysicsObj_IsIdle(&ptMissile->tVehicle.tPhysicsObj) )
  {
    ptCreatorQTaskRef = ptMissile->ptCreatorQTaskRef;
    LODWORD(igi2_frame.Real32x9_Multiply_tTemp.tX.vY) = ptMissile;
    if ( ptCreatorQTaskRef )
      LODWORD(igi2_frame.Real32x9_Multiply_tTemp.tX.vZ) = ptCreatorQTaskRef->pxObject;
    else
      igi2_frame.Real32x9_Multiply_tTemp.tX.vZ = 0.0;
    ptIgnoreQTaskRef = ptMissile->ptIgnoreQTaskRef;
    if ( ptIgnoreQTaskRef )
      LODWORD(igi2_frame.Real32x9_Multiply_tTemp.tY.vX) = ptIgnoreQTaskRef->pxObject;
    else
      igi2_frame.Real32x9_Multiply_tTemp.tY.vX = 0.0;
    v42 = *((_DWORD *)pxData + 10);
    igi2_frame.Real32x9_Multiply_tTemp.tY.vY = 1.0;
    if ( v42 )
    {
      igi2_frame.tWindVelocity.vX = ptMissile->tVehicle.tPhysicsObj.tPhysics.tCMVel.vX;
      vY = ptMissile->tVehicle.tPhysicsObj.tPhysics.tCMVel.vY;
      vZ = ptMissile->tVehicle.tPhysicsObj.tPhysics.tCMVel.vZ;
      igi2_frame.tWindVelocity.vX = -igi2_frame.tWindVelocity.vX;
      igi2_frame.tWindVelocity.vY = -vY;
      igi2_frame.tWindVelocity.vZ = -vZ;
      Wing_ApplyAirResistance(
        ptMissile->atWing,
        v42,
        0.00032699998700991273,
        &ptMissile->tVehicle.tPhysicsObj.tPhysics,
        &ptMissile->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation,
        &igi2_frame.tWindVelocity);
    }
    PhysicsObj_Update(
      &ptMissile->tVehicle.tPhysicsObj,
      44.600887298583984,
      0.949999988079071,
      0.9200000166893005,
      Game_ptGame->ptWorld,
      GameFunctions_eWeaponCollisionEvaluateQTaskEvent,
      &igi2_frame.Real32x9_Multiply_tTemp);
  }
  ptMagicObjContainer = ptMissile->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.ptMagicObjContainer;
  if ( ptMagicObjContainer )
  {
    LODWORD(igi2_frame.tWindVelocity.vX) = &ptMissile->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos;
    LODWORD(igi2_frame.tWindVelocity.vY) = &ptMissile->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation;
    LODWORD(igi2_frame.tWindVelocity.vZ) = ptMissile;
    ptHead = (int)ptMagicObjContainer->tQTaskChildren.ptHead;
    if ( *(_DWORD *)ptHead )
    {
      if ( ptHead )
      {
        v47 = QTask_nProtectedQTaskStackOffset;
        do
        {
          if ( *(_DWORD *)ptHead )
            v48 = **(_DWORD **)ptHead != 0 ? *(struct QTask_s **)ptHead : nullptr;
          else
            v48 = nullptr;
          v49 = MagicObj_eUpdateMagicObjEvent;
          QTask_atProtectedQTaskStack[v47].ptQTask = v48;
          pfHandler = (void (__cdecl *)(int, struct real32x3_t *))QTask_aatQTaskFinalEvent[v49][*(unsigned __int16 *)(ptHead + 36)].pfHandler;
          v51 = v47 + 1;
          QTask_nProtectedQTaskStackOffset = v51;
          if ( pfHandler )
          {
            pfHandler(ptHead, &igi2_frame.tWindVelocity);
            v51 = QTask_nProtectedQTaskStackOffset;
          }
          ptHead = dword_849C7DC[v51];
          v47 = v51 - 1;
          QTask_nProtectedQTaskStackOffset = v47;
        }
        while ( ptHead );
      }
    }
  }
}

// source: j/0/vehicles/missile.c:1235  [anchor-mhash]
void __cdecl Missile_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { float ptDynCubeObj; };
    struct { char igi2_o1[20]; char zTempModel[128]; };
    struct { char igi2_o2[148]; char zString[132]; };
    char igi2_extent[280];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QReferenceList_s *p_tQTaskRefList; // edi
  struct LODVirModel_s *LODVirModelExistsFn; // eax
  struct LODVirModel_s *v4; // esi
  struct PhysicsObjType_s *Type; // eax
  char *v6; // eax
  char v7; // cl
  double v8; // st7
  bool v9; // c0
  bool v10; // c3
  struct QTask_s *ptTail; // edx
  double v12; // st7
  double v13; // st7
  int *v14; // eax
  int v15; // eax
  double v16; // st6
  struct QTask_s *v17; // eax
  struct QTask_s *ptHead; // eax
  int v19; // edx
  struct QTask_s *v20; // ecx
  void (__cdecl *pfHandler)(struct QTask_s *, _DWORD); // ecx
  int v22; // edx

  qmemcpy(&ptQTask[11].eQTaskType, &ptQTask[3].ptPrev, sizeof(struct QTask_s));
  p_tQTaskRefList = &ptQTask[10].tQTaskRefList;
  LODVirModelExistsFn = MTP_GetLODVirModelExistsFn((char *)&ptQTask[10].tQTaskRefList);
  if ( LODVirModelExistsFn )
    v4 = LODVirModelExistsFn;
  else
    v4 = nullptr;
  if ( ptQTask[3].ptNext )
  {
    QTask_Delete(ptQTask[3].ptNext);
    ptQTask[3].ptNext = nullptr;
  }
  if ( v4 )
  {
    if ( v4 != *(struct LODVirModel_s **)&ptQTask[2].eQTaskType )
    {
      ModelObj_SetLODVirModel((struct ModelObj_s *)ptQTask, v4, false);
      ptQTask[7].tQTaskRefList.ptHead = nullptr;
      ptQTask[7].tQTaskRefList.ptMiddle = nullptr;
      ptQTask[7].tQTaskRefList.ptTail = nullptr;
      ptQTask[7].ptParent = nullptr;
      *(_DWORD *)&ptQTask[7].eQTaskType = 0;
    }
    Type = PhysicsObjType_FindType((char *)&ptQTask[10].tQTaskRefList);
    PhysicsObj_Init(ptQTask, Type);
  }
  else if ( LOBYTE(p_tQTaskRefList->ptHead) && BYTE1(ptQTask[10].tQTaskRefList.ptHead) != 42 )
  {
    sprintf(igi2_frame.zString, "Model \"%s\" not available", (char *)&ptQTask[10].tQTaskRefList);
    v6 = (char *)&ptQTask[10].tQTaskRefList;
    do
    {
      v7 = *v6;
      v6[igi2_frame.zTempModel - (char *)p_tQTaskRefList] = *v6;
      ++v6;
    }
    while ( v7 );
    sprintf((char *const)&ptQTask[10].tQTaskRefList, "** %s **", igi2_frame.zTempModel);
  }
  v8 = *(float *)&ptQTask[6].tQTaskChildren.ptHead;
  v9 = v8 < *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
  v10 = v8 == *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
  ptTail = ptQTask[48].tQTaskChildren.ptTail;
  ptQTask[48].ptNext = ptTail;
  ptQTask[47].tQTaskRefList.ptMiddle = (struct QReference_s *)ptTail;
  if ( v9 || v10 )
    v12 = *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
  else
    v12 = *(float *)&ptQTask[6].tQTaskChildren.ptHead;
  if ( v12 >= *(float *)&ptQTask[6].ptPrev )
  {
    if ( *(float *)&ptQTask[6].tQTaskChildren.ptHead <= (double)*(float *)&ptQTask[6].tQTaskChildren.ptMiddle )
      v13 = *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
    else
      v13 = *(float *)&ptQTask[6].tQTaskChildren.ptHead;
  }
  else
  {
    v13 = *(float *)&ptQTask[6].ptPrev;
  }
  v14 = *(int **)&ptQTask[2].eQTaskType;
  if ( v14 && (v15 = *v14) != 0 )
    v16 = *(float *)(*(_DWORD *)(*(_DWORD *)(v15 + 12) + 12) + 120);
  else
    v16 = 1.0;
  igi2_frame.ptDynCubeObj = v13 * v16;
  World_MoveDynCubeObjRadius(
    Game_ptGame->ptWorld,
    (struct DynCubeObj_s *)ptQTask,
    (struct real64x3_t *)&ptQTask[11],
    igi2_frame.ptDynCubeObj);
  v17 = QTask_NewFn(nullptr, MagicObjContainer_eQTaskType, nullptr);
  v17[1].ptNext = ptQTask;
  ptQTask[3].ptNext = v17;
  ModelObj_CreateAttachObjects((struct ModelObj_s *)ptQTask, v17, ptQTask, false, true);
  ptHead = ptQTask[3].ptNext->tQTaskChildren.ptHead;
  if ( ptHead->ptNext && ptHead )
  {
    v19 = QTask_nProtectedQTaskStackOffset;
    do
    {
      if ( ptHead->ptNext )
        v20 = ptHead->ptNext->ptNext != nullptr ? ptHead->ptNext : nullptr;
      else
        v20 = nullptr;
      QTask_atProtectedQTaskStack[v19].ptQTask = v20;
      pfHandler = (void (__cdecl *)(struct QTask_s *, _DWORD))QTask_aatQTaskFinalEvent[ParameterList_eUpdateInternalDataQTaskEvent][ptHead->eQTaskType].pfHandler;
      v22 = v19 + 1;
      QTask_nProtectedQTaskStackOffset = v22;
      if ( pfHandler )
      {
        pfHandler(ptHead, 0);
        v22 = QTask_nProtectedQTaskStackOffset;
      }
      ptHead = (struct QTask_s *)dword_849C7DC[v22];
      v19 = v22 - 1;
      QTask_nProtectedQTaskStackOffset = v19;
    }
    while ( ptHead );
  }
}

// source: j/0/vehicles/missile.c:1327  [size]
void __cdecl Missile_GetGetPhysicsObjTypeSizeHandler(struct QTask_s *ptQTask, void *pxData)
{
  *(_DWORD *)pxData = 592;
}

// source: j/0/vehicles/missile.c:1343  [anchor-caller]
void __cdecl Missile_ParsePhysicsObjTypeHandler(struct QTask_s *ptQTask, void *pxContext)
{
  _DWORD *v2; // esi
  int v3; // ebp
  struct ArgList_s *v4; // edi
  int v5; // eax
  void *v6; // eax
  int v7; // eax
  void *v8; // eax
  int v9; // eax
  double v10; // st7
  int v11; // eax
  double v12; // st7
  int v13; // eax
  double v14; // st7
  int v15; // eax
  double v16; // st7
  int v17; // eax
  double v18; // st7
  int v19; // eax
  double v20; // st7
  int v21; // eax
  double v22; // st7
  int v23; // eax
  char *v24; // ebx
  int v25; // eax

  v2 = pxContext;
  v3 = *(_DWORD *)pxContext;
  v4 = *((struct ArgList_s **)pxContext + 1);
  ((void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[PhysicsObjType_eParsePhysicsObjTypeEvent][Vehicle_eQTaskType].pfHandler)(
    ptQTask,
    pxContext);
  v5 = v2[2];
  v2[2] = v5 + 1;
  if ( v4->isQVM )
  {
    *(float *)&pxContext = 0.0;
    QVM_EvalArg(&pxContext, 4, v4, v5, 1);
    v6 = pxContext;
  }
  else
  {
    v6 = (void *)Expression_EvalInt(v4->aptExpression[v5]);
  }
  *(_DWORD *)(v3 + 280) = v6;
  v7 = v2[2];
  v2[2] = v7 + 1;
  if ( v4->isQVM )
  {
    *(float *)&pxContext = 0.0;
    QVM_EvalArg(&pxContext, 4, v4, v7, 1);
    v8 = pxContext;
  }
  else
  {
    v8 = (void *)Expression_EvalInt(v4->aptExpression[v7]);
  }
  *(_DWORD *)(v3 + 284) = v8;
  v9 = v2[2];
  v2[2] = v9 + 1;
  if ( v4->isQVM )
  {
    *(float *)&pxContext = 0.0;
    QVM_EvalArg(&pxContext, 4, v4, v9, 2);
    v10 = *(float *)&pxContext;
  }
  else
  {
    v10 = Expression_EvalFloat(v4->aptExpression[v9]);
  }
  *(float *)(v3 + 288) = v10;
  v11 = v2[2];
  v2[2] = v11 + 1;
  if ( v4->isQVM )
  {
    *(float *)&pxContext = 0.0;
    QVM_EvalArg(&pxContext, 4, v4, v11, 2);
    v12 = *(float *)&pxContext;
  }
  else
  {
    v12 = Expression_EvalFloat(v4->aptExpression[v11]);
  }
  *(float *)(v3 + 292) = v12 * 0.03333333507180214;
  v13 = v2[2];
  v2[2] = v13 + 1;
  if ( v4->isQVM )
  {
    *(float *)&pxContext = 0.0;
    QVM_EvalArg(&pxContext, 4, v4, v13, 2);
    v14 = *(float *)&pxContext;
  }
  else
  {
    v14 = Expression_EvalFloat(v4->aptExpression[v13]);
  }
  *(float *)(v3 + 296) = v14;
  v15 = v2[2];
  v2[2] = v15 + 1;
  if ( v4->isQVM )
  {
    *(float *)&pxContext = 0.0;
    QVM_EvalArg(&pxContext, 4, v4, v15, 2);
    v16 = *(float *)&pxContext;
  }
  else
  {
    v16 = Expression_EvalFloat(v4->aptExpression[v15]);
  }
  *(float *)(v3 + 300) = v16 * 4096.0;
  v17 = v2[2];
  v2[2] = v17 + 1;
  if ( v4->isQVM )
  {
    *(float *)&pxContext = 0.0;
    QVM_EvalArg(&pxContext, 4, v4, v17, 2);
    v18 = *(float *)&pxContext;
  }
  else
  {
    v18 = Expression_EvalFloat(v4->aptExpression[v17]);
  }
  *(float *)(v3 + 304) = v18 * 4096.0;
  v19 = v2[2];
  v2[2] = v19 + 1;
  if ( v4->isQVM )
  {
    *(float *)&pxContext = 0.0;
    QVM_EvalArg(&pxContext, 4, v4, v19, 2);
    v20 = *(float *)&pxContext;
  }
  else
  {
    v20 = Expression_EvalFloat(v4->aptExpression[v19]);
  }
  *(float *)(v3 + 308) = v20;
  v21 = v2[2];
  v2[2] = v21 + 1;
  if ( v4->isQVM )
  {
    *(float *)&pxContext = 0.0;
    QVM_EvalArg(&pxContext, 4, v4, v21, 2);
    v22 = *(float *)&pxContext;
  }
  else
  {
    v22 = Expression_EvalFloat(v4->aptExpression[v21]);
  }
  *(float *)(v3 + 312) = v22;
  v23 = v2[2];
  v2[2] = v23 + 1;
  v24 = (char *)(v3 + 316);
  if ( v4->isQVM )
  {
    *v24 = 0;
    QVM_EvalArg((void *)(v3 + 316), 256, v4, v23, 3);
  }
  else
  {
    Expression_EvalString(v4->aptExpression[v23], (char *)(v3 + 316), 256);
  }
  v25 = v2[2];
  v2[2] = v25 + 1;
  if ( v4->isQVM )
  {
    *(_BYTE *)(v3 + 572) = 0;
    QVM_EvalArg((void *)(v3 + 572), 16, v4, v25, 3);
  }
  else
  {
    Expression_EvalString(v4->aptExpression[v25], (char *)(v3 + 572), 16);
  }
  *(_DWORD *)(v3 + 588) = GameFunctions_RegisterGameSprite(v24);
}

// source: j/0/vehicles/missile.c:1389  [size]
void __cdecl Missile_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = Missile_ptParameterList;
}

// source: j/0/vehicles/missile.c:1405  [anchor-caller]
void __cdecl Missile_CreateProjectileHandler(struct QTask_s *ptQTask, void *pxContext)
{
  Missile_New(
    Level_ptDynamicQTask,
    *((struct QTask_s **)pxContext + 1),
    *((struct QTask_s **)pxContext + 3),
    *((struct real64x3_t **)pxContext + 4),
    *((struct real32x9_t **)pxContext + 8),
    *((float *)pxContext + 10),
    nullptr,
    *(struct QTask_s **)pxContext,
    (char *)(*((_DWORD *)pxContext + 17) + 40),
    *((struct WeaponType_s **)pxContext + 15));
}

// source: j/0/vehicles/missile.c:1464  [anchor-mhash]
void __cdecl Missile_WeaponCollisionEvaluateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_BYTE *)pxContext = ptQTask != *((struct QTask_s **)pxContext + 1)
                     && ptQTask != *((struct QTask_s **)pxContext + 2)
                     && ptQTask != *((struct QTask_s **)pxContext + 3)
                     && ptQTask->eQTaskType != Missile_eQTaskType;
}

// source: j/0/vehicles/missile.c:1493  [size]
void __cdecl Missile_CollisionEvalEvent(struct QTask_s *ptQTask, void *pxContext)
{
  *(_BYTE *)pxContext = 0;
}

// source: j/0/vehicles/missile.c:1509  [anchor-strings]
void __cdecl Missile_CreateWeaponTypeParametersHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *v2; // esi
  struct QTask_s *v3; // edi
  struct QTask_s *v4; // eax
  struct StaticTilemap_s *p_tQTaskRefList; // eax
  int v6; // esi
  char ptQTilemap; // cl

  v2 = QTask_NewFn(nullptr, Missile_eMissileParametersQTaskType, nullptr);
  *((_DWORD *)pxContext + 2) = v2;
  v2[1].tQTaskChildren.ptTail = nullptr;
  v2[1].tQTaskRefList.ptHead = nullptr;
  v3 = *((struct QTask_s **)pxContext + 1);
  v4 = TagItem_Find(v3, (char *)&stru_68BC20);
  if ( v4
    || (v4 = TagItem_NewString16(v3, (char *)&stru_68BC20, (char *)&stru_68BC20.tQTaskChildren.ptTail)) != nullptr )
  {
    p_tQTaskRefList = (struct StaticTilemap_s *)&v4[7].tQTaskRefList;
  }
  else
  {
    p_tQTaskRefList = &g_zInitialValue;
  }
  v6 = (char *)v2 - (char *)p_tQTaskRefList;
  do
  {
    ptQTilemap = (char)p_tQTaskRefList->ptQTilemap;
    *((_BYTE *)&p_tQTaskRefList[1].ptQTilemap + v6) = p_tQTaskRefList->ptQTilemap;
    p_tQTaskRefList = (struct StaticTilemap_s *)((char *)p_tQTaskRefList + 1);
  }
  while ( ptQTilemap );
}

// source: j/0/vehicles/missile.c:1541  [size]
unsigned __int16 __cdecl Missile_GetQTaskType()
{
  return Missile_eQTaskType;
}

// source: j/0/vehicles/missile.c:1564  [anchor-callee]
struct QTask_s *__cdecl Missile_New(
        struct QTask_s *ptParent,
        struct QTask_s *ptCreatorQTask,
        struct QTask_s *ptIgnoreQTask,
        struct real64x3_t *ptPosition,
        struct real32x9_t *ptOrientation,
        float vInitVelocity,
        struct real64x3_t *ptTargetPos,
        struct QTask_s *ptTargetTask,
        char *zModel,
        struct WeaponType_s *ptWeaponType)
{
  struct QTask_s *v11; // ebp
  struct LODVirModel_s *LODVirModelExistsFn; // eax
  double v13; // st7
  double v14; // st7
  int *v15; // eax
  int v16; // eax
  double v17; // st6
  struct PhysicsObjType_s *Type; // esi
  struct QTask_s *v19; // eax
  int v20; // esi
  int v21; // eax
  struct real32x9_t *v22; // eax
  double vY; // rt0
  double v24; // st6
  double v25; // st7
  double v26; // rt2
  double v27; // st6
  double v28; // st6
  float ptDynCubeObj; // [esp+0h] [ebp-30h]
  float tVelocity; // [esp+14h] [ebp-1Ch]
  float tVelocitya; // [esp+14h] [ebp-1Ch]
  float tVelocity_4; // [esp+18h] [ebp-18h]
  float tVelocity_8; // [esp+1Ch] [ebp-14h]
  float tVelocity_8a; // [esp+1Ch] [ebp-14h]

  v11 = QTask_NewFn(ptParent, Missile_eQTaskType, nullptr);
  qmemcpy(&v11[3].ptPrev, ptOrientation, sizeof(struct QTask_s));
  LODVirModelExistsFn = MTP_GetLODVirModelExistsFn(zModel);
  if ( !LODVirModelExistsFn )
  {
    LDebug_Error("VirModel \"%s\" not available", zModel);
    abort();
  }
  if ( LODVirModelExistsFn != *(struct LODVirModel_s **)&v11[2].eQTaskType )
  {
    ModelObj_SetLODVirModel((struct ModelObj_s *)v11, LODVirModelExistsFn, false);
    v11[7].tQTaskRefList.ptHead = nullptr;
    v11[7].tQTaskRefList.ptMiddle = nullptr;
    v11[7].tQTaskRefList.ptTail = nullptr;
    v11[7].ptParent = nullptr;
    *(_DWORD *)&v11[7].eQTaskType = 0;
  }
  if ( *(float *)&v11[6].tQTaskChildren.ptHead <= (double)*(float *)&v11[6].tQTaskChildren.ptMiddle )
    v13 = *(float *)&v11[6].tQTaskChildren.ptMiddle;
  else
    v13 = *(float *)&v11[6].tQTaskChildren.ptHead;
  if ( v13 >= *(float *)&v11[6].ptPrev )
  {
    if ( *(float *)&v11[6].tQTaskChildren.ptHead <= (double)*(float *)&v11[6].tQTaskChildren.ptMiddle )
      v14 = *(float *)&v11[6].tQTaskChildren.ptMiddle;
    else
      v14 = *(float *)&v11[6].tQTaskChildren.ptHead;
  }
  else
  {
    v14 = *(float *)&v11[6].ptPrev;
  }
  v15 = *(int **)&v11[2].eQTaskType;
  if ( v15 && (v16 = *v15) != 0 )
    v17 = *(float *)(*(_DWORD *)(*(_DWORD *)(v16 + 12) + 12) + 120);
  else
    v17 = 1.0;
  ptDynCubeObj = v17 * v14;
  World_MoveDynCubeObjRadius(Game_ptGame->ptWorld, (struct DynCubeObj_s *)v11, ptPosition, ptDynCubeObj);
  Type = PhysicsObjType_FindType(zModel);
  PhysicsObj_Init(v11, Type);
  v11[55].tQTaskRefList.ptTail = *((struct QReference_s **)Type->pxData + 72);
  Missile_InitWings((struct Missile_s *)v11);
  strcpy((char *)&v11[10].tQTaskRefList, zModel);
  v11[48].ptNext = (struct QTask_s *)1065353216;
  v11[47].tQTaskRefList.ptMiddle = (struct QReference_s *)1065353216;
  if ( v11[3].ptNext )
  {
    QTask_Delete(v11[3].ptNext);
    v11[3].ptNext = nullptr;
  }
  v19 = QTask_NewFn(nullptr, MagicObjContainer_eQTaskType, nullptr);
  v19[1].ptNext = v11;
  v11[3].ptNext = v19;
  ModelObj_CreateAttachObjects((struct ModelObj_s *)v11, v19, v11, false, true);
  Missile_InitSmoke(v11);
  Missile_InitSound(v11);
  v20 = *(_DWORD *)(*(_DWORD *)&v11[12].eQTaskType + 724);
  v11[55].tQTaskChildren.ptTail = nullptr;
  if ( ptCreatorQTask )
    v11[55].tQTaskChildren.ptTail = (struct QTask_s *)QTask_NewQTaskRef(ptCreatorQTask);
  v11[55].tQTaskRefList.ptHead = nullptr;
  if ( ptIgnoreQTask )
    v11[55].tQTaskRefList.ptHead = QTask_NewQTaskRef(ptIgnoreQTask);
  v21 = *(_DWORD *)(v20 + 284);
  if ( !v21 )
  {
    v22 = ptOrientation;
    vY = ptOrientation->tY.vY;
    v24 = ptOrientation->tZ.vY * 4096000.0;
    *(double *)&v11[54].tQTaskChildren.ptHead = ptOrientation->tX.vY * 4096000.0 + ptPosition->vX;
    *(double *)&v11[54].tQTaskChildren.ptTail = vY * 4096000.0 + ptPosition->vY;
    v25 = v24 + ptPosition->vZ;
LABEL_33:
    *(double *)&v11[54].tQTaskRefList.ptMiddle = v25;
    goto LABEL_34;
  }
  if ( v21 == 1 )
  {
    *(double *)&v11[54].ptParent = ptTargetPos->vX - ptPosition->vX;
    *(double *)&v11[55].ptNext = ptTargetPos->vY - ptPosition->vY;
    *(double *)&v11[55].tQTaskChildren.ptHead = ptTargetPos->vZ - ptPosition->vZ;
    qmemcpy(&v11[54].tQTaskChildren, ptPosition, 0x18u);
    *(double *)&v11[54].tQTaskChildren.ptHead = *(double *)&v11[54].ptParent + *(double *)&v11[54].tQTaskChildren.ptHead;
    *(double *)&v11[54].tQTaskChildren.ptTail = *(double *)&v11[55].ptNext + *(double *)&v11[54].tQTaskChildren.ptTail;
    v25 = *(double *)&v11[55].tQTaskChildren.ptHead + *(double *)&v11[54].tQTaskRefList.ptMiddle;
LABEL_32:
    v22 = ptOrientation;
    goto LABEL_33;
  }
  if ( ptTargetTask )
  {
    v11[55].tQTaskRefList.ptMiddle = QTask_NewQTaskRef(ptTargetTask);
    v22 = ptOrientation;
  }
  else
  {
    if ( !ptTargetPos )
    {
      v26 = *(float *)&v11[3].tQTaskRefList.ptHead;
      tVelocity = *(float *)&v11[3].tQTaskChildren.ptHead * 40960000.0;
      v27 = *(float *)&v11[3].ptParent * 40960000.0;
      *(double *)&v11[54].tQTaskChildren.ptHead = tVelocity + *(double *)&v11[1].ptNext;
      *(double *)&v11[54].tQTaskChildren.ptTail = v26 * 40960000.0 + *(double *)&v11[1].tQTaskChildren.ptHead;
      v25 = v27 + *(double *)&v11[1].tQTaskChildren.ptTail;
      goto LABEL_32;
    }
    v22 = ptOrientation;
    qmemcpy(&v11[54].tQTaskChildren, ptTargetPos, 0x18u);
  }
LABEL_34:
  v28 = v22->tY.vY;
  tVelocity_8 = v22->tZ.vY;
  tVelocitya = v22->tX.vY * vInitVelocity * 136.53334045410156;
  *(float *)&v11[8].tQTaskRefList.ptMiddle = tVelocitya;
  tVelocity_4 = v28 * vInitVelocity * 136.53334045410156;
  *(float *)&v11[8].tQTaskRefList.ptTail = tVelocity_4;
  tVelocity_8a = tVelocity_8 * vInitVelocity * 136.53334045410156;
  *(float *)&v11[8].ptParent = tVelocity_8a;
  Physics_UpdateSpeedApproximation((struct Physics_s *)&v11[8]);
  *(_DWORD *)&v11[56].eQTaskType = ptWeaponType;
  return v11;
}

// source: j/0/vehicles/missile.c:1761  [anchor-strings]
void __cdecl Missile_Open()
{
  unsigned __int16 v0; // ax
  unsigned __int16 v1; // si
  struct ParameterList_s *v2; // eax
  int v3; // edx
  void **v4; // esi
  struct QVector_s *v5; // eax

  Missile_eQTaskType = QTask_NewQTaskType("Missile", 2280, Vehicle_eQTaskType, 0, 0);
  v0 = QTask_NewQTaskType("MissileParameters", 64, WeaponTypeParameters_eQTaskType, 0, 0);
  v1 = Missile_eQTaskType;
  Missile_eMissileParametersQTaskType = v0;
  QTask_LinkQTaskEventHandlerFn(Missile_eQTaskType, 0, Missile_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 1, Missile_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 2, Missile_DeleteHandler);
  QTask_LinkQTaskEventHandlerFn(
    v1,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Missile_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(v1, ParameterList_eUpdateInternalDataQTaskEvent, Missile_UpdateInternalDataHandler);
  QTask_LinkQTaskEventHandlerFn(v1, PhysicsObjType_eParsePhysicsObjTypeEvent, Missile_ParsePhysicsObjTypeHandler);
  QTask_LinkQTaskEventHandlerFn(
    v1,
    PhysicsObjType_eGetPhysicsObjTypeSizeEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Missile_GetGetPhysicsObjTypeSizeHandler);
  QTask_LinkQTaskEventHandlerFn(
    v1,
    GameFunctions_eWeaponCollisionEvaluateQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Missile_WeaponCollisionEvaluateHandler);
  QTask_LinkQTaskEventHandlerFn(v1, PhysicsObj_eMove, nullptr);
  QTask_LinkQTaskEventHandlerFn(v1, 13, (void (__cdecl *)(struct QTask_s *, void *))Missile_CollisionEvalEvent);
  QTask_LinkQTaskEventHandlerFn(v1, WeaponType_eCreateParametersQTaskEvent, Missile_CreateWeaponTypeParametersHandler);
  QTask_LinkQTaskEventHandlerFn(v1, Weapon_eCreateProjectileQTaskEvent, Missile_CreateProjectileHandler);
  QTask_LinkQTaskEventHandlerFn(v1, Serialize_eDeSerializeDoneQTaskEvent, Missile_DeSerializeDoneHandler);
  v2 = (struct ParameterList_s *)Mem_AllocFn(72, 4);
  v2->ptParameterListItem = (struct ParameterListItem_s *)&v2[1];
  v3 = Level_eParameterTypeObjectPos;
  v2->nParameters = 0;
  v2->nMaxParameters = 3;
  Missile_ptParameterList = v2;
  ParameterList_AddParameter(v2, 0x1B8u, v3, "Position", 7u, nullptr);
  ParameterList_AddParameter(Missile_ptParameterList, 0x7Cu, Level_eParameterTypeReal32x9, "Orientation", 7u, nullptr);
  ParameterList_AddParameter(Missile_ptParameterList, 0x1A4u, Level_eParameterTypeString16, "Model", 7u, nullptr);
  Symbol_Register(
    "TASKTYPE_MISSILE",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)Missile_eQTaskType,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "MISSILE_SMOKE_NONE",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    nullptr,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "MISSILE_SMOKE_NORMAL",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)1,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "MISSILE_TYPE_MISSILE_DIRECT",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    nullptr,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "MISSILE_TYPE_MISSILE_BALLISTIC",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)2,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "MISSILE_TYPE_MISSILE_ANTITANK",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)3,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "MISSILE_TYPE_MISSILE_KEYBOARD",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)4,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "MISSILE_TYPE_BOMB",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)5,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "MISSILE_TYPE_HIND_HELICOPTER",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)1,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Missile_tRandomState.anRandom[0] = -923067897;
  Missile_tRandomState.anRandom[1] = 971667286;
  Missile_tRandomState.anRandom[2] = 2146516173;
  v4 = (void **)Mem_AllocFn(128, 4);
  v5 = (struct QVector_s *)Mem_AllocFn(24, 4);
  v5->tPrivate.papxElement = v4;
  v5->tPrivate.nArraySize = 32;
  v5->tPrivate.nReallocSize = 32;
  v5->tPrivate.nElements = 0;
  v5->tPrivate.isPrivateMem = false;
  v5->tPrivate.isStrictOrder = true;
  Missile_ptSmokeQVector = v5;
}

// source: j/0/vehicles/missile.c:1824  [anchor-hash]
void __cdecl Missile_Close()
{
  int v0; // esi

  Missile_DeleteAllSmoke();
  QVector_Delete(Missile_ptSmokeQVector);
  if ( Missile_ptParameterList )
  {
    v0 = *(_DWORD *)((unsigned int)&Missile_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
  QTask_DeleteQTaskType(Missile_eQTaskType);
  QTask_DeleteQTaskType(Missile_eMissileParametersQTaskType);
}
