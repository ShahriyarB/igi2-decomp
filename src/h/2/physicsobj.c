/* h/2/physicsobj.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: h/2/physicsobj.c:53  [anchor-callee]
enum bool __cdecl PhysicsObj_AssertNoIntersection(
        struct PhysicsObj_s *ptPhysicsObj,
        struct World_s *ptWorld,
        struct real64x3_t *ptNewPos,
        __int16 eCollisionEvalEvent,
        void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { float v37; };
    struct { float v38; };
    struct { float v39; };
    struct { float v40; };
    struct { float v41; };
    struct { char igi2_o5[8]; int iCollPoint; };
    struct { char igi2_o6[8]; double iCollPointa; };
    struct { char igi2_o7[8]; double iCollPointb; };
    struct { char igi2_o8[8]; double iCollPointc; };
    struct { char igi2_o9[8]; double iCollPointd; };
    struct { char igi2_o10[8]; double iCollPointe; };
    struct { char igi2_o11[28]; float Real32x3_Rotate_tTemp_8; };
    struct { char igi2_o12[28]; float Real32x3_Rotate_tTemp_8a; };
    struct { char igi2_o13[32]; double avDistance[22]; };
    struct { char igi2_o14[208]; int aiCollPoint[22]; };
    struct { char igi2_o15[296]; struct real64x3_t atCheckPointWorldStart[22]; };
    struct { char igi2_o16[824]; struct QIntersection_s atQIntersection[22]; };
    char igi2_extent[312];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v5; // edi
  int v6; // ebx
  double *p_vZ; // ebp
  double *p_vY; // edx
  struct real64x3_t *v9; // ecx
  float *v10; // eax
  double vZ; // st7
  double v12; // st7
  double vY; // st6
  double v14; // rt0
  double v15; // st7
  double v16; // st6
  double v17; // rt1
  double v18; // st7
  int v19; // ebx
  int v20; // ebp
  double *v21; // edx
  double *v22; // ecx
  double v23; // st6
  double v24; // st4
  double v25; // st6
  double v26; // st4
  double v27; // st6
  double v28; // st4
  double v29; // st6
  double v30; // st4
  double *v31; // ecx
  double *v32; // edx
  int v33; // edi
  double v34; // st6
  double v35; // st4

  v5 = 0;
  v6 = 0;
  igi2_frame.iCollPoint = 0;
  p_vZ = &igi2_frame.atCheckPointWorldStart[0].vZ;
  p_vY = &igi2_frame.atCheckPointWorldStart[0].vY;
  v9 = igi2_frame.atCheckPointWorldStart;
  v10 = &ptPhysicsObj->atCollPoint[0].tPos.vZ;
  do
  {
    if ( *((_BYTE *)v10 + 5) && *((_BYTE *)v10 + 4) )
    {
      vZ = ptPhysicsObj->tRigidDynCubeObj.tModelObj.tOrientation.tX.vZ;
      igi2_frame.aiCollPoint[v5] = v6;
      v12 = vZ * *v10;
      LODWORD(igi2_frame.avDistance[v5]) = 0;
      vY = ptPhysicsObj->tRigidDynCubeObj.tModelObj.tOrientation.tX.vY;
      HIDWORD(igi2_frame.avDistance[v5++]) = -1063256064;
      ++v9;
      p_vY += 3;
      p_vZ += 3;
      igi2_frame.Real32x3_Rotate_tTemp_8 = ptPhysicsObj->tRigidDynCubeObj.tModelObj.tOrientation.tZ.vZ * *v10
                              + ptPhysicsObj->tRigidDynCubeObj.tModelObj.tOrientation.tZ.vY * *(v10 - 1)
                              + ptPhysicsObj->tRigidDynCubeObj.tModelObj.tOrientation.tZ.vX * *(v10 - 2);
      v14 = ptPhysicsObj->tRigidDynCubeObj.tModelObj.tOrientation.tY.vZ * *v10
          + ptPhysicsObj->tRigidDynCubeObj.tModelObj.tOrientation.tY.vY * *(v10 - 1)
          + ptPhysicsObj->tRigidDynCubeObj.tModelObj.tOrientation.tY.vX * *(v10 - 2);
      v9[-1].vX = v12
                + vY * *(v10 - 1)
                + ptPhysicsObj->tRigidDynCubeObj.tModelObj.tOrientation.tX.vX * *(v10 - 2)
                + ptPhysicsObj->tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos.vX;
      *(p_vY - 3) = v14 + ptPhysicsObj->tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos.vY;
      *(p_vZ - 3) = igi2_frame.Real32x3_Rotate_tTemp_8
                  + ptPhysicsObj->tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos.vZ
                  + 2048.0;
    }
    if ( *((_BYTE *)v10 + 61) && *((_BYTE *)v10 + 60) )
    {
      v15 = ptPhysicsObj->tRigidDynCubeObj.tModelObj.tOrientation.tX.vZ * v10[14];
      igi2_frame.aiCollPoint[v5] = v6 + 1;
      v6 = igi2_frame.iCollPoint;
      v16 = ptPhysicsObj->tRigidDynCubeObj.tModelObj.tOrientation.tX.vY * v10[13];
      LODWORD(igi2_frame.avDistance[v5]) = 0;
      HIDWORD(igi2_frame.avDistance[v5++]) = -1063256064;
      ++v9;
      p_vY += 3;
      p_vZ += 3;
      igi2_frame.Real32x3_Rotate_tTemp_8a = ptPhysicsObj->tRigidDynCubeObj.tModelObj.tOrientation.tZ.vZ * v10[14]
                               + ptPhysicsObj->tRigidDynCubeObj.tModelObj.tOrientation.tZ.vY * v10[13]
                               + ptPhysicsObj->tRigidDynCubeObj.tModelObj.tOrientation.tZ.vX * v10[12];
      v17 = ptPhysicsObj->tRigidDynCubeObj.tModelObj.tOrientation.tY.vZ * v10[14]
          + ptPhysicsObj->tRigidDynCubeObj.tModelObj.tOrientation.tY.vY * v10[13]
          + ptPhysicsObj->tRigidDynCubeObj.tModelObj.tOrientation.tY.vX * v10[12];
      v9[-1].vX = v15
                + v16
                + ptPhysicsObj->tRigidDynCubeObj.tModelObj.tOrientation.tX.vX * v10[12]
                + ptPhysicsObj->tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos.vX;
      *(p_vY - 3) = v17 + ptPhysicsObj->tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos.vY;
      *(p_vZ - 3) = igi2_frame.Real32x3_Rotate_tTemp_8a
                  + ptPhysicsObj->tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos.vZ
                  + 2048.0;
    }
    v6 += 2;
    v10 += 28;
    igi2_frame.iCollPoint = v6;
  }
  while ( v6 < 22 );
  if ( !v5 )
    return false;
  World_GetNextZNoMaterial(
    ptWorld,
    igi2_frame.atQIntersection,
    igi2_frame.atCheckPointWorldStart,
    v5,
    igi2_frame.avDistance,
    eCollisionEvalEvent,
    (struct CollisionEvaluateContext_s *)pxContext,
    ptPhysicsObj->nCollisionTaskGroups);
  v18 = 0.0;
  v19 = 0;
  if ( v5 >= 4 )
  {
    v20 = 3;
    v21 = &igi2_frame.atCheckPointWorldStart[1].vZ;
    v22 = &igi2_frame.atQIntersection[0].tPos.vZ;
    do
    {
      if ( *((_DWORD *)v22 + 17) )
      {
        igi2_frame.iCollPointa = 2048.0 - (*(v21 - 3) - *v22);
        if ( igi2_frame.iCollPointa > v18 )
          v18 = igi2_frame.iCollPointa;
        v23 = *((float *)v22 + 10) * ptPhysicsObj->tPhysics.tCMVel.vZ
            + *((float *)v22 + 9) * ptPhysicsObj->tPhysics.tCMVel.vY
            + *((float *)v22 + 8) * ptPhysicsObj->tPhysics.tCMVel.vX;
        if ( v23 < 0.0 )
        {
          v24 = *((float *)v22 + 9) * v23;
          igi2_frame.v37 = *((float *)v22 + 10) * v23;
          ptPhysicsObj->tPhysics.tCMVel.vX = ptPhysicsObj->tPhysics.tCMVel.vX - *((float *)v22 + 8) * v23;
          ptPhysicsObj->tPhysics.tCMVel.vY = ptPhysicsObj->tPhysics.tCMVel.vY - v24;
          ptPhysicsObj->tPhysics.tCMVel.vZ = ptPhysicsObj->tPhysics.tCMVel.vZ - igi2_frame.v37;
        }
      }
      if ( *((_DWORD *)v22 + 47) )
      {
        igi2_frame.iCollPointb = 2048.0 - (*v21 - v22[15]);
        if ( igi2_frame.iCollPointb > v18 )
          v18 = igi2_frame.iCollPointb;
        v25 = *((float *)v22 + 40) * ptPhysicsObj->tPhysics.tCMVel.vZ
            + *((float *)v22 + 39) * ptPhysicsObj->tPhysics.tCMVel.vY
            + *((float *)v22 + 38) * ptPhysicsObj->tPhysics.tCMVel.vX;
        if ( v25 < 0.0 )
        {
          v26 = *((float *)v22 + 39) * v25;
          igi2_frame.v38 = *((float *)v22 + 40) * v25;
          ptPhysicsObj->tPhysics.tCMVel.vX = ptPhysicsObj->tPhysics.tCMVel.vX - *((float *)v22 + 38) * v25;
          ptPhysicsObj->tPhysics.tCMVel.vY = ptPhysicsObj->tPhysics.tCMVel.vY - v26;
          ptPhysicsObj->tPhysics.tCMVel.vZ = ptPhysicsObj->tPhysics.tCMVel.vZ - igi2_frame.v38;
        }
      }
      if ( *((_DWORD *)v22 + 77) )
      {
        igi2_frame.iCollPointc = 2048.0 - (v21[3] - v22[30]);
        if ( igi2_frame.iCollPointc > v18 )
          v18 = igi2_frame.iCollPointc;
        v27 = *((float *)v22 + 70) * ptPhysicsObj->tPhysics.tCMVel.vZ
            + *((float *)v22 + 69) * ptPhysicsObj->tPhysics.tCMVel.vY
            + *((float *)v22 + 68) * ptPhysicsObj->tPhysics.tCMVel.vX;
        if ( v27 < 0.0 )
        {
          v28 = *((float *)v22 + 69) * v27;
          igi2_frame.v39 = *((float *)v22 + 70) * v27;
          ptPhysicsObj->tPhysics.tCMVel.vX = ptPhysicsObj->tPhysics.tCMVel.vX - *((float *)v22 + 68) * v27;
          ptPhysicsObj->tPhysics.tCMVel.vY = ptPhysicsObj->tPhysics.tCMVel.vY - v28;
          ptPhysicsObj->tPhysics.tCMVel.vZ = ptPhysicsObj->tPhysics.tCMVel.vZ - igi2_frame.v39;
        }
      }
      if ( *((_DWORD *)v22 + 107) )
      {
        igi2_frame.iCollPointd = 2048.0 - (v21[6] - v22[45]);
        if ( igi2_frame.iCollPointd > v18 )
          v18 = igi2_frame.iCollPointd;
        v29 = *((float *)v22 + 100) * ptPhysicsObj->tPhysics.tCMVel.vZ
            + *((float *)v22 + 99) * ptPhysicsObj->tPhysics.tCMVel.vY
            + *((float *)v22 + 98) * ptPhysicsObj->tPhysics.tCMVel.vX;
        if ( v29 < 0.0 )
        {
          v30 = *((float *)v22 + 99) * v29;
          igi2_frame.v40 = *((float *)v22 + 100) * v29;
          ptPhysicsObj->tPhysics.tCMVel.vX = ptPhysicsObj->tPhysics.tCMVel.vX - *((float *)v22 + 98) * v29;
          ptPhysicsObj->tPhysics.tCMVel.vY = ptPhysicsObj->tPhysics.tCMVel.vY - v30;
          ptPhysicsObj->tPhysics.tCMVel.vZ = ptPhysicsObj->tPhysics.tCMVel.vZ - igi2_frame.v40;
        }
      }
      v20 += 4;
      v19 += 4;
      v21 += 12;
      v22 += 60;
    }
    while ( v20 < v5 );
  }
  if ( v19 < v5 )
  {
    v31 = &igi2_frame.atQIntersection[v19].tPos.vZ;
    v32 = &igi2_frame.atCheckPointWorldStart[v19].vZ;
    v33 = v5 - v19;
    do
    {
      if ( *((_DWORD *)v31 + 17) )
      {
        igi2_frame.iCollPointe = 2048.0 - (*v32 - *v31);
        if ( igi2_frame.iCollPointe > v18 )
          v18 = igi2_frame.iCollPointe;
        v34 = *((float *)v31 + 9) * ptPhysicsObj->tPhysics.tCMVel.vY
            + *((float *)v31 + 10) * ptPhysicsObj->tPhysics.tCMVel.vZ
            + *((float *)v31 + 8) * ptPhysicsObj->tPhysics.tCMVel.vX;
        if ( v34 < 0.0 )
        {
          v35 = *((float *)v31 + 9) * v34;
          igi2_frame.v41 = *((float *)v31 + 10) * v34;
          ptPhysicsObj->tPhysics.tCMVel.vX = ptPhysicsObj->tPhysics.tCMVel.vX - *((float *)v31 + 8) * v34;
          ptPhysicsObj->tPhysics.tCMVel.vY = ptPhysicsObj->tPhysics.tCMVel.vY - v35;
          ptPhysicsObj->tPhysics.tCMVel.vZ = ptPhysicsObj->tPhysics.tCMVel.vZ - igi2_frame.v41;
        }
      }
      v32 += 3;
      v31 += 15;
      --v33;
    }
    while ( v33 );
  }
  ptNewPos->vZ = v18 + ptNewPos->vZ;
  return v18 > 0.0;
}

// source: h/2/physicsobj.c:214  [anchor-caller]
int __cdecl PhysicsObj_Collision(
        struct PhysicsObj_s *ptPhysicsObj,
        struct real32x3_t *ptNormal,
        struct real32x3_t *ptPoint,
        float *pvVelocityRelation,
        float vGravity,
        int iCollPoint,
        char isInsideMaterial)
{
  int result; // eax

  PhysicsObj_CollisionResponse(
    &ptPhysicsObj->tPhysics,
    &ptPhysicsObj->tRigidDynCubeObj.tModelObj.tOrientation,
    ptNormal,
    ptPoint,
    *pvVelocityRelation,
    vGravity,
    ptPhysicsObj->atCollPoint[iCollPoint].vBounceFactor);
  return result;
}

// source: h/2/physicsobj.c:250  [anchor-caller]
struct PhysicsObj_s *__cdecl PhysicsObj_Friction(
        struct PhysicsObj_s *ptPhysicsObj,
        struct World_s *ptWorld,
        struct real32x3_t *ptNormal,
        float vGravity,
        int iCollPoint,
        struct real32x3_t *ptPoint,
        float vAngMomFriction)
{
  struct PhysicsObj_s *result; // eax

  PhysicsObj_FrictionResponse(
    &ptPhysicsObj->tPhysics,
    ptNormal,
    vGravity,
    ptPhysicsObj->atCollPoint[iCollPoint].vFrictionY,
    vAngMomFriction);
  return result;
}

// source: h/2/physicsobj.c:276  [anchor-strings]
__declspec(noreturn) void __cdecl PhysicsObj_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  LDebug_Error("PhysicsObj create handler must be overloaded");
  abort();
}

// source: h/2/physicsobj.c:289  [anchor-strings]
__declspec(noreturn) void __cdecl PhysicsObj_DeleteHandler(struct QTask_s *ptQTask)
{
  LDebug_Error("PhysicsObj delete handler must be overloaded");
  abort();
}

// source: h/2/physicsobj.c:302  [anchor-strings]
__declspec(noreturn) void __cdecl PhysicsObj_RunHandler(struct QTask_s *ptQTask)
{
  LDebug_Error("PhysicsObj run handler must be overloaded");
  abort();
}

// source: h/2/physicsobj.c:315  [size]
void __cdecl PhysicsObj_CollisionEvalHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_BYTE *)pxContext = *((_DWORD *)pxContext + 1) != (_DWORD)ptQTask;
}

// source: h/2/physicsobj.c:331  [anchor-mhash]
void __cdecl PhysicsObj_GetUpdateOrientationHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { double Real64x3_Rotate_tTemp_8; };
    struct { char igi2_o1[8]; double Real64x3_Rotate_tTemp_16; };
    struct { char igi2_o2[16]; _BYTE tDeltaOldWorld[40]; };
    struct { char igi2_o3[56]; struct real64x3_t tDeltaTrans; };
    struct { char igi2_o4[84]; struct QReference_s *ptTail; };
    struct { char igi2_o5[88]; struct QTask_s *ptNext; };
    char igi2_extent[96];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  double v3; // st7
  double *v4; // edx
  double v5; // st6
  double v6; // st5
  double v7; // st4
  double v8; // st3
  double v9; // st2
  double v10; // st7
  double v11; // st6
  double v12; // st5
  double v13; // st4
  double v14; // st3
  double v15; // st2
  struct QTask_s *ptPrev; // edx
  double v17; // st7
  double v18; // st6

  v3 = *(double *)&ptQTask[1].ptNext - *(double *)&ptQTask[45].tQTaskChildren.ptHead;
  v4 = *(double **)pxContext;
  igi2_frame.tDeltaTrans.vY = *(double *)&ptQTask[1].tQTaskChildren.ptHead - *(double *)&ptQTask[45].tQTaskChildren.ptTail;
  igi2_frame.tDeltaTrans.vZ = *(double *)&ptQTask[1].tQTaskChildren.ptTail - *(double *)&ptQTask[45].tQTaskRefList.ptMiddle;
  v5 = *v4 - *(double *)&ptQTask[45].tQTaskChildren.ptHead;
  v6 = v4[1] - *(double *)&ptQTask[45].tQTaskChildren.ptTail;
  *(double *)&igi2_frame.tDeltaOldWorld[16] = v4[2] - *(double *)&ptQTask[45].tQTaskRefList.ptMiddle;
  v7 = *(float *)&ptQTask[44].tQTaskRefList.ptHead * v6
     + *(float *)&ptQTask[44].ptParent * *(double *)&igi2_frame.tDeltaOldWorld[16]
     + *(float *)&ptQTask[44].tQTaskChildren.ptHead * v5;
  v8 = *(float *)&ptQTask[44].tQTaskRefList.ptMiddle * v6
     + *(float *)&ptQTask[44].eQTaskType * *(double *)&igi2_frame.tDeltaOldWorld[16]
     + *(float *)&ptQTask[44].tQTaskChildren.ptMiddle * v5;
  v9 = *(float *)&ptQTask[44].tQTaskRefList.ptTail * v6
     + *(float *)&ptQTask[45].ptNext * *(double *)&igi2_frame.tDeltaOldWorld[16]
     + *(float *)&ptQTask[44].tQTaskChildren.ptTail * v5;
  igi2_frame.Real64x3_Rotate_tTemp_8 = *(float *)&ptQTask[3].tQTaskRefList.ptHead * v8
                          + *(float *)&ptQTask[3].tQTaskRefList.ptMiddle * v9
                          + *(float *)&ptQTask[3].tQTaskChildren.ptTail * v7;
  igi2_frame.Real64x3_Rotate_tTemp_16 = *(float *)&ptQTask[3].ptParent * v8
                           + *(float *)&ptQTask[3].eQTaskType * v9
                           + *(float *)&ptQTask[3].tQTaskRefList.ptTail * v7;
  *((double *)pxContext + 1) = *(float *)&ptQTask[3].tQTaskChildren.ptHead * v8
                             + *(float *)&ptQTask[3].tQTaskChildren.ptMiddle * v9
                             + *(float *)&ptQTask[3].ptPrev * v7
                             + v3
                             - v5;
  *((double *)pxContext + 2) = igi2_frame.Real64x3_Rotate_tTemp_8 + igi2_frame.tDeltaTrans.vY - v6;
  *((double *)pxContext + 3) = igi2_frame.Real64x3_Rotate_tTemp_16 + igi2_frame.tDeltaTrans.vZ - *(double *)&igi2_frame.tDeltaOldWorld[16];
  v10 = *(float *)&ptQTask[44].tQTaskChildren.ptHead;
  LODWORD(igi2_frame.tDeltaTrans.vY) = ptQTask[44].ptParent;
  v11 = *(float *)&ptQTask[44].tQTaskRefList.ptHead;
  v12 = *(float *)&ptQTask[44].tQTaskChildren.ptMiddle;
  LODWORD(igi2_frame.tDeltaTrans.vZ) = ptQTask[44].tQTaskRefList.ptMiddle;
  v13 = *(float *)&ptQTask[44].tQTaskChildren.ptTail;
  HIDWORD(igi2_frame.tDeltaTrans.vZ) = *(_DWORD *)&ptQTask[44].eQTaskType;
  v14 = v12 * *(float *)&ptQTask[3].tQTaskChildren.ptHead;
  igi2_frame.ptTail = ptQTask[44].tQTaskRefList.ptTail;
  v15 = v13 * *(float *)&ptQTask[3].tQTaskChildren.ptMiddle;
  igi2_frame.ptNext = ptQTask[45].ptNext;
  ptPrev = ptQTask[45].ptPrev;
  *(float *)igi2_frame.tDeltaOldWorld = v14 + v15 + v10 * *(float *)&ptQTask[3].ptPrev;
  *(float *)&igi2_frame.tDeltaOldWorld[4] = *(float *)&igi2_frame.tDeltaTrans.vZ * *(float *)&ptQTask[3].tQTaskChildren.ptHead
                               + *(float *)&igi2_frame.ptTail * *(float *)&ptQTask[3].tQTaskChildren.ptMiddle
                               + v11 * *(float *)&ptQTask[3].ptPrev;
  *(float *)&igi2_frame.tDeltaOldWorld[8] = *((float *)&igi2_frame.tDeltaTrans.vZ + 1) * *(float *)&ptQTask[3].tQTaskChildren.ptHead
                               + *(float *)&igi2_frame.ptNext * *(float *)&ptQTask[3].tQTaskChildren.ptMiddle
                               + *(float *)&igi2_frame.tDeltaTrans.vY * *(float *)&ptQTask[3].ptPrev;
  *(float *)&igi2_frame.tDeltaOldWorld[12] = v12 * *(float *)&ptQTask[3].tQTaskRefList.ptHead
                                + v13 * *(float *)&ptQTask[3].tQTaskRefList.ptMiddle
                                + v10 * *(float *)&ptQTask[3].tQTaskChildren.ptTail;
  *(float *)&igi2_frame.tDeltaOldWorld[16] = *(float *)&igi2_frame.tDeltaTrans.vZ * *(float *)&ptQTask[3].tQTaskRefList.ptHead
                                + *(float *)&igi2_frame.ptTail * *(float *)&ptQTask[3].tQTaskRefList.ptMiddle
                                + v11 * *(float *)&ptQTask[3].tQTaskChildren.ptTail;
  *(float *)&igi2_frame.tDeltaOldWorld[20] = *((float *)&igi2_frame.tDeltaTrans.vZ + 1) * *(float *)&ptQTask[3].tQTaskRefList.ptHead
                                + *(float *)&igi2_frame.ptNext * *(float *)&ptQTask[3].tQTaskRefList.ptMiddle
                                + *(float *)&igi2_frame.tDeltaTrans.vY * *(float *)&ptQTask[3].tQTaskChildren.ptTail;
  *(float *)&igi2_frame.tDeltaOldWorld[24] = v12 * *(float *)&ptQTask[3].ptParent
                                + v13 * *(float *)&ptQTask[3].eQTaskType
                                + v10 * *(float *)&ptQTask[3].tQTaskRefList.ptTail;
  *(float *)&igi2_frame.tDeltaOldWorld[28] = *(float *)&igi2_frame.tDeltaTrans.vZ * *(float *)&ptQTask[3].ptParent
                                + *(float *)&igi2_frame.ptTail * *(float *)&ptQTask[3].eQTaskType
                                + v11 * *(float *)&ptQTask[3].tQTaskRefList.ptTail;
  v17 = *((float *)&igi2_frame.tDeltaTrans.vZ + 1) * *(float *)&ptQTask[3].ptParent
      + *(float *)&igi2_frame.ptNext * *(float *)&ptQTask[3].eQTaskType;
  v18 = *(float *)&igi2_frame.tDeltaTrans.vY * *(float *)&ptQTask[3].tQTaskRefList.ptTail;
  *(_DWORD *)&igi2_frame.tDeltaOldWorld[36] = (char *)&ptQTask[4].ptNext->ptNext + (unsigned int)ptPrev + 1;
  *(float *)&igi2_frame.tDeltaOldWorld[32] = v17 + v18;
  qmemcpy((char *)pxContext + 32, igi2_frame.tDeltaOldWorld, 0x28u);
}

// source: h/2/physicsobj.c:398  [size]
void __cdecl PhysicsObj_PhysicsObjTypeDeleteHandler(struct QTask_s *ptQTask, void *pxContext)
{
  int v2; // eax
  int v3; // esi

  v2 = *(_DWORD *)(*(_DWORD *)pxContext + 724);
  if ( v2 )
  {
    v3 = *(_DWORD *)((v2 - 4) & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v3);
    memset(*(void **)(v3 + 8), 0xCDu, *(_DWORD *)(v3 + 16));
    free((void *)v3);
    *(_DWORD *)(*(_DWORD *)pxContext + 724) = 0;
  }
}

// source: h/2/physicsobj.c:459  [anchor-strings]
void __cdecl PhysicsObj_Open()
{
  __int16 v0; // ax
  unsigned __int16 v1; // si

  PhysicsObj_eQTaskType = QTask_NewQTaskType("PhysicsObj", 1904, RigidDynCubeObj_eQTaskType, 0, 0);
  PhysicsObj_eMove = QTask_NewQTaskEventFn(0, "PhysicsObjMove");
  PhysicsObj_eUpdateOrientation = QTask_NewQTaskEventFn(0, "PhysicsObjUpdateOrientation");
  v0 = QTask_NewQTaskEventFn(0, "PhysicsObjHit");
  v1 = PhysicsObj_eQTaskType;
  PhysicsObj_eHit = v0;
  QTask_LinkQTaskEventHandlerFn(
    PhysicsObj_eQTaskType,
    0,
    (void (__cdecl *)(struct QTask_s *, void *))PhysicsObj_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 2, (void (__cdecl *)(struct QTask_s *))PhysicsObj_DeleteHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 1, (void (__cdecl *)(struct QTask_s *))PhysicsObj_RunHandler);
  QTask_LinkQTaskEventHandlerFn(v1, 13, PhysicsObj_CollisionEvalHandler);
  QTask_LinkQTaskEventHandlerFn(v1, PhysicsObj_eUpdateOrientation, PhysicsObj_GetUpdateOrientationHandler);
  QTask_LinkQTaskEventHandlerFn(v1, PhysicsObjType_ePhysicsObjTypeDeleteEvent, PhysicsObj_PhysicsObjTypeDeleteHandler);
  PhysicsObj_ptPhysicsObjUpdate = nullptr;
}

// source: h/2/physicsobj.c:490  [size]
void __cdecl PhysicsObj_Close()
{
  QTask_DeleteQTaskEvent(PhysicsObj_eMove);
  QTask_DeleteQTaskEvent(PhysicsObj_eUpdateOrientation);
  QTask_DeleteQTaskEvent(PhysicsObj_eHit);
  QTask_DeleteQTaskType(PhysicsObj_eQTaskType);
}

// source: h/2/physicsobj.c:509  [size]
unsigned __int16 __cdecl PhysicsObj_GetQTaskType()
{
  return PhysicsObj_eQTaskType;
}

// source: h/2/physicsobj.c:524  [anchor-callee]
void __cdecl PhysicsObj_Create(struct QTask_s *ptQTask)
{
  _BYTE *v1; // ecx
  int v2; // edx

  *(_DWORD *)&ptQTask[11].eQTaskType = 1065353216;
  ptQTask[12].tQTaskChildren.ptMiddle = (struct QTask_s *)1065353216;
  ptQTask[12].tQTaskRefList.ptTail = (struct QReference_s *)1065353216;
  ptQTask[11].ptNext = nullptr;
  ptQTask[11].ptPrev = nullptr;
  ptQTask[11].tQTaskChildren.ptHead = nullptr;
  ptQTask[11].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[11].tQTaskChildren.ptTail = nullptr;
  ptQTask[11].tQTaskRefList.ptHead = nullptr;
  ptQTask[11].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[11].tQTaskRefList.ptTail = nullptr;
  ptQTask[11].ptParent = nullptr;
  ptQTask[12].ptNext = nullptr;
  ptQTask[12].ptPrev = nullptr;
  ptQTask[12].tQTaskChildren.ptHead = nullptr;
  ptQTask[12].tQTaskChildren.ptTail = nullptr;
  ptQTask[12].tQTaskRefList.ptHead = nullptr;
  ptQTask[12].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[12].ptParent = nullptr;
  *(_DWORD *)&ptQTask[12].eQTaskType = 0;
  ptQTask[13].ptNext = nullptr;
  ptQTask[44].ptNext = nullptr;
  LOBYTE(ptQTask[44].ptPrev) = 0;
  LOBYTE(ptQTask[45].ptParent) = 1;
  BYTE1(ptQTask[45].ptParent) = 0;
  v1 = (char *)&ptQTask[13].ptParent + 1;
  v2 = 22;
  do
  {
    *v1 = 0;
    v1 += 56;
    --v2;
  }
  while ( v2 );
  ptQTask[8].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[8].tQTaskRefList.ptTail = nullptr;
  ptQTask[8].ptParent = nullptr;
  *(_DWORD *)&ptQTask[8].eQTaskType = 0;
  ptQTask[9].ptNext = nullptr;
  ptQTask[9].ptPrev = nullptr;
  ptQTask[9].tQTaskChildren.ptHead = nullptr;
  ptQTask[9].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[9].tQTaskChildren.ptTail = nullptr;
  ptQTask[9].tQTaskRefList.ptHead = nullptr;
  ptQTask[9].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[9].tQTaskRefList.ptTail = nullptr;
  ptQTask[9].ptParent = nullptr;
  *(_DWORD *)&ptQTask[9].eQTaskType = 0;
  ptQTask[10].ptNext = nullptr;
  ptQTask[8].tQTaskChildren.ptHead = nullptr;
  ptQTask[10].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[10].tQTaskChildren.ptTail = nullptr;
  ptQTask[8].tQTaskChildren.ptMiddle = (struct QTask_s *)770676047;
  ptQTask[8].tQTaskChildren.ptTail = (struct QTask_s *)785422920;
  ptQTask[8].tQTaskRefList.ptHead = (struct QReference_s *)769046967;
  ptQTask[8].ptNext = (struct QTask_s *)1148846080;
  ptQTask[8].ptPrev = (struct QTask_s *)981668463;
  ptQTask[10].tQTaskChildren.ptHead = (struct QTask_s *)32;
  ptQTask[10].ptPrev = (struct QTask_s *)Mem_AllocFn(768, 4);
  qmemcpy(&ptQTask[45].tQTaskChildren, &ptQTask[1], 0x18u);
  qmemcpy(&ptQTask[44].tQTaskChildren, &ptQTask[3].ptPrev, sizeof(struct QTask_s));
}

// source: h/2/physicsobj.c:571  [anchor-caller]
struct PhysicsObjType_s *__cdecl PhysicsObj_Init(
        struct QTask_s *ptQTask,
        struct PhysicsObjType_s *ptType)
{
  int v4; // ebx
  struct real32x3_t *Size; // edi
  int v6; // eax
  _BYTE *v7; // eax
  int v8; // ecx
  struct QTaskNodeList_s *p_tQTaskChildren; // edi
  float vX; // [esp+0h] [ebp-1Ch]
  float vY; // [esp+4h] [ebp-18h]
  float vZ; // [esp+8h] [ebp-14h]
  struct QTask_s *ptQTaska = *(struct QTask_s * *)&ptQTask; // [esp+20h] [ebp+4h] ARGSLOT

  v4 = 0;
  if ( ptType )
  {
    *(_DWORD *)&ptQTask[12].eQTaskType = ptType;
    Size = PhysicsObjType_GetSize(ptType);
    vZ = PhysicsObjType_GetSize(ptType)->vZ * 4096.0;
    vY = PhysicsObjType_GetSize(*(struct PhysicsObjType_s **)&ptQTask[12].eQTaskType)->vY * 4096.0;
    vX = Size->vX * 4096.0;
    Physics_InitBox((struct Physics_s *)&ptQTask[8], *(float *)(*(_DWORD *)&ptQTask[12].eQTaskType + 8), vX, vY, vZ);
    v6 = *(_DWORD *)&ptQTask[12].eQTaskType;
    *(float *)&ptQTask[8].tQTaskChildren.ptMiddle = *(float *)&ptQTask[8].tQTaskChildren.ptMiddle * 1.0099999904632568;
    *(float *)&ptQTask[8].tQTaskChildren.ptTail = *(float *)&ptQTask[8].tQTaskChildren.ptTail * 1.0099999904632568;
    *(float *)&ptQTask[8].tQTaskRefList.ptHead = *(float *)&ptQTask[8].tQTaskRefList.ptHead * 1.0099999904632568;
    ptQTask[44].ptNext = *(struct QTask_s **)(v6 + 328);
    v7 = (char *)&ptQTask[13].ptParent + 1;
    v8 = 22;
    do
    {
      *v7 = 0;
      v7 += 56;
      --v8;
    }
    while ( v8 );
    ptQTaska = nullptr;
    if ( (int)ptQTask[44].ptNext > 0 )
    {
      p_tQTaskChildren = &ptQTask[13].tQTaskChildren;
      do
      {
        p_tQTaskChildren->ptMiddle = *(struct QTask_s **)(v4 + *(_DWORD *)&ptQTask[12].eQTaskType + 340);
        p_tQTaskChildren->ptHead = *(struct QTask_s **)(v4 + *(_DWORD *)&ptQTask[12].eQTaskType + 336);
        p_tQTaskChildren->ptTail = *(struct QTask_s **)(v4 + *(_DWORD *)&ptQTask[12].eQTaskType + 344);
        LOBYTE(p_tQTaskChildren[2].ptHead) = 1;
        BYTE1(p_tQTaskChildren[2].ptHead) = 1;
        BYTE2(p_tQTaskChildren[2].ptHead) = 0;
        p_tQTaskChildren[2].ptMiddle = *(struct QTask_s **)(v4 + *(_DWORD *)&ptQTask[12].eQTaskType + 348);
        p_tQTaskChildren[2].ptTail = *(struct QTask_s **)(v4 + *(_DWORD *)&ptQTask[12].eQTaskType + 352);
        p_tQTaskChildren[4].ptMiddle = nullptr;
        RigidDynCubeObj_GetMagicVertexLocalPos(
          (struct RigidDynCubeObj_t *)ptQTask,
          *(_DWORD *)(v4 + *(_DWORD *)&ptQTask[12].eQTaskType + 332),
          (struct real32x3_t *)&p_tQTaskChildren[1]);
        p_tQTaskChildren = (struct QTaskNodeList_s *)((char *)p_tQTaskChildren + 56);
        v4 += 24;
        ptQTaska = (struct QTask_s *)((char *)ptQTaska + 1);
      }
      while ( (int)ptQTaska < (int)ptQTask[44].ptNext );
    }
  }
  else
  {
    Physics_InitBox((struct Physics_s *)&ptQTask[8], 1000.0, 9420.7998046875, 20070.400390625, 6144.0);
    ptQTask[44].ptNext = nullptr;
  }
  qmemcpy(&ptQTask[45].tQTaskChildren, &ptQTask[1], 0x18u);
  qmemcpy(&ptQTask[44].tQTaskChildren, &ptQTask[3].ptPrev, sizeof(struct QTask_s));
  ptQTask[13].ptNext = nullptr;
  ptQTask[47].ptNext = nullptr;
  ptQTask[47].ptPrev = nullptr;
  ptQTask[47].tQTaskChildren.ptHead = nullptr;
  ptQTask[47].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[47].tQTaskChildren.ptTail = nullptr;
  ptQTask[47].tQTaskRefList.ptHead = nullptr;
  ptQTask[46].ptNext = nullptr;
  ptQTask[46].ptPrev = nullptr;
  ptQTask[46].tQTaskChildren.ptHead = nullptr;
  ptQTask[46].tQTaskChildren.ptTail = nullptr;
  ptQTask[46].tQTaskRefList.ptHead = nullptr;
  ptQTask[46].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[46].ptParent = nullptr;
  LOBYTE(ptQTask[44].ptPrev) = 0;
  ptQTask[13].ptPrev = (struct QTask_s *)-1;
  *(_DWORD *)&ptQTask[45].eQTaskType = 1065353216;
  ptQTask[46].tQTaskChildren.ptMiddle = (struct QTask_s *)1065353216;
  ptQTask[46].tQTaskRefList.ptTail = (struct QReference_s *)1065353216;
  return (struct PhysicsObjType_s *)1065353216;
}

// source: h/2/physicsobj.c:657  [size]
struct QTask_s *__cdecl PhysicsObj_Delete(struct QTask_s *ptQTask)
{
  struct QTask_s *result; // eax

  *(_DWORD *)&ptQTask[12].eQTaskType = 0;
  Physics_DeAlloc((struct Physics_s *)&ptQTask[8]);
  return result;
}

// source: h/2/physicsobj.c:682  [anchor-callee]
enum PhysicsObjCollision_e __cdecl PhysicsObj_AddContactForces(
        struct PhysicsObj_s *ptPhysicsObj,
        float vGravity,
        float vAngMomFriction,
        struct World_s *ptWorld,
        __int16 eCollisionEvalEvent,
        void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { int v48; };
    struct { char igi2_o1[12]; struct real32x3_t *ptNormal; };
    struct { char igi2_o2[36]; int i; };
    struct { char igi2_o3[36]; int *p_isHit; };
    struct { char igi2_o4[40]; int iCollPoint; };
    struct { char igi2_o5[40]; int iCollPointa; };
    struct { char igi2_o6[44]; char *vVeloctiyRelation; };
    struct { char igi2_o7[44]; float vVeloctiyRelationa; };
    struct { char igi2_o8[48]; struct real32x3_t tTemp; };
    struct { char igi2_o9[64]; int nCollPoint; };
    struct { char igi2_o10[68]; struct real32x3_t Real32x3_Rotate_tTemp; };
    struct { char igi2_o11[80]; int isPenetrate; };
    struct { char igi2_o12[84]; enum PhysicsObjCollision_e eCollision; };
    struct { char igi2_o13[88]; double v61; };
    struct { char igi2_o14[96]; double v62; };
    struct { char igi2_o15[104]; struct real32x3_t atCheckPointLocal[22]; };
    struct { char igi2_o16[368]; int aiCollPoint[22]; };
    struct { char igi2_o17[456]; struct real32x3_t atPointVelocity[22]; };
    struct { char igi2_o18[720]; struct real64x3_t atCheckPointWorldStop[22]; };
    struct { char igi2_o19[1248]; struct real64x3_t atCheckPointWorldStart[22]; };
    struct { char igi2_o20[1776]; struct QIntersection_s atIntersection[22]; };
    char igi2_extent[4420];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v6; // eax
  int v7; // ecx
  char *p_isActive; // eax
  unsigned int v9; // edi
  unsigned int v10; // esi
  double vZ; // st7
  float *v12; // eax
  struct real32x3_t *v13; // edx
  float v14; // ebx
  float v15; // eax
  double v16; // st7
  double v17; // st6
  int v18; // eax
  double v19; // st7
  double v20; // st7
  int v21; // esi
  int *v23; // edi
  bool v24; // zf
  int *v25; // edx
  int v26; // eax
  BOOL v27; // ebx
  int v28; // ecx
  int vZ_low; // edx
  void (__cdecl *pfHandler)(int, struct real32x3_t *); // eax
  int v31; // eax
  int v32; // ecx
  char *v33; // ecx
  int *v34; // ebx
  long double v35; // st4
  int *v36; // ecx
  struct Physics_s *p_tPhysics; // esi
  double v38; // st7
  enum PhysicsObjCollision_e v40; // eax
  int v41; // ebx
  int nContact; // edi
  float *v43; // eax
  struct real32x3_t *v44; // edi
  float v45; // ecx
  double v46; // st7
  double v47; // st7

  v6 = ptPhysicsObj->nCollPoint;
  v7 = 0;
  igi2_frame.eCollision = PHYSICSOBJ_COLL_NONE;
  igi2_frame.nCollPoint = 0;
  igi2_frame.isPenetrate = 0;
  if ( !v6 )
    return PHYSICSOBJ_COLL_NONE;
  igi2_frame.p_isHit = &igi2_frame.atIntersection[0].isHit;
  p_isActive = &ptPhysicsObj->atCollPoint[0].isActive;
  v9 = 0;
  igi2_frame.iCollPoint = 0;
  igi2_frame.vVeloctiyRelation = &ptPhysicsObj->atCollPoint[0].isActive;
  v10 = 0;
  do
  {
    *igi2_frame.p_isHit = 0;
    if ( p_isActive[1] && *p_isActive )
    {
      p_isActive[2] = 0;
      vZ = ptPhysicsObj->tRigidDynCubeObj.tModelObj.tOrientation.tX.vZ;
      v12 = (float *)(p_isActive - 12);
      v13 = &igi2_frame.atCheckPointLocal[v9 / 3];
      v13->vX = *v12;
      v14 = v12[1];
      v15 = v12[2];
      v13->vY = v14;
      v13->vZ = v15;
      igi2_frame.Real32x3_Rotate_tTemp.vX = vZ * igi2_frame.atCheckPointLocal[v9 / 3].vZ
                               + ptPhysicsObj->tRigidDynCubeObj.tModelObj.tOrientation.tX.vY
                               * igi2_frame.atCheckPointLocal[v9 / 3].vY
                               + ptPhysicsObj->tRigidDynCubeObj.tModelObj.tOrientation.tX.vX
                               * igi2_frame.atCheckPointLocal[v9 / 3].vX;
      igi2_frame.Real32x3_Rotate_tTemp.vY = ptPhysicsObj->tRigidDynCubeObj.tModelObj.tOrientation.tY.vZ
                               * igi2_frame.atCheckPointLocal[v9 / 3].vZ
                               + ptPhysicsObj->tRigidDynCubeObj.tModelObj.tOrientation.tY.vY
                               * igi2_frame.atCheckPointLocal[v9 / 3].vY
                               + ptPhysicsObj->tRigidDynCubeObj.tModelObj.tOrientation.tY.vX
                               * igi2_frame.atCheckPointLocal[v9 / 3].vX;
      v16 = ptPhysicsObj->tRigidDynCubeObj.tModelObj.tOrientation.tZ.vZ * igi2_frame.atCheckPointLocal[v9 / 3].vZ
          + ptPhysicsObj->tRigidDynCubeObj.tModelObj.tOrientation.tZ.vY * igi2_frame.atCheckPointLocal[v9 / 3].vY;
      v17 = ptPhysicsObj->tRigidDynCubeObj.tModelObj.tOrientation.tZ.vX * igi2_frame.atCheckPointLocal[v9 / 3].vX;
      v13->vX = igi2_frame.Real32x3_Rotate_tTemp.vX;
      v13->vY = igi2_frame.Real32x3_Rotate_tTemp.vY;
      igi2_frame.Real32x3_Rotate_tTemp.vZ = v16 + v17;
      v13->vZ = igi2_frame.Real32x3_Rotate_tTemp.vZ;
      igi2_frame.v61 = igi2_frame.atCheckPointLocal[v9 / 3].vX + ptPhysicsObj->tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos.vX;
      igi2_frame.atCheckPointWorldStart[v10 / 2].vX = igi2_frame.v61;
      igi2_frame.v62 = igi2_frame.atCheckPointLocal[v9 / 3].vY + ptPhysicsObj->tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos.vY;
      igi2_frame.atCheckPointWorldStart[v10 / 2].vY = igi2_frame.v62;
      *(double *)&igi2_frame.tTemp.vX = igi2_frame.atCheckPointLocal[v9 / 3].vZ
                           + ptPhysicsObj->tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos.vZ;
      igi2_frame.atCheckPointWorldStart[v10 / 2].vZ = *(double *)&igi2_frame.tTemp.vX;
      Physics_GetPointVelocity(&igi2_frame.atPointVelocity[v9 / 3], &ptPhysicsObj->tPhysics, &igi2_frame.atCheckPointLocal[v9 / 3]);
      v18 = igi2_frame.nCollPoint;
      v19 = igi2_frame.atPointVelocity[v9 / 3].vX + igi2_frame.v61;
      v7 = igi2_frame.iCollPoint;
      igi2_frame.aiCollPoint[igi2_frame.nCollPoint] = igi2_frame.iCollPoint;
      igi2_frame.atCheckPointWorldStop[v10 / 2].vX = v19;
      igi2_frame.nCollPoint = v18 + 1;
      p_isActive = igi2_frame.vVeloctiyRelation;
      v20 = igi2_frame.atPointVelocity[v9 / 3].vY + igi2_frame.v62;
      v9 += 3;
      v10 += 2;
      *(double *)&igi2_frame.atPointVelocity[v10 + 20].vZ = v20;
      *(double *)&igi2_frame.atPointVelocity[v10 + 21].vY = *(float *)&igi2_frame.aiCollPoint[v9 + 21] + *(double *)&igi2_frame.tTemp.vX;
    }
    ++v7;
    p_isActive += 56;
    igi2_frame.iCollPoint = v7;
    igi2_frame.p_isHit += 30;
    igi2_frame.vVeloctiyRelation = p_isActive;
  }
  while ( v7 < 22 );
  v21 = igi2_frame.nCollPoint;
  if ( !igi2_frame.nCollPoint )
    return PHYSICSOBJ_COLL_NONE;
  igi2_frame.ptNormal = (struct real32x3_t *)ptPhysicsObj->nCollisionTaskGroups;
  igi2_frame.v48 = igi2_frame.nCollPoint;
  ptPhysicsObj->nContact = 0;
  World_TraceLines(
    ptWorld,
    igi2_frame.atIntersection,
    igi2_frame.atCheckPointWorldStart,
    igi2_frame.atCheckPointWorldStop,
    igi2_frame.v48,
    eCollisionEvalEvent,
    (struct CollisionEvaluateContext_s *)pxContext,
    (unsigned int)igi2_frame.ptNormal);
  igi2_frame.iCollPointa = 0;
  if ( v21 > 0 )
  {
    v23 = &igi2_frame.atIntersection[0].isHit;
    for ( igi2_frame.i = 0; ; ++igi2_frame.i )
    {
      v24 = *v23 == 0;
      v25 = v23 - 23;
      LODWORD(igi2_frame.v61) = v23 - 23;
      if ( !v24 )
      {
        v26 = *(v23 - 2);
        v27 = 0;
        if ( v26 )
          v27 = *(float *)(v26 + 12) != 0.0;
        v28 = *v25;
        if ( *v25 )
        {
          LODWORD(igi2_frame.Real32x3_Rotate_tTemp.vY) = v23 - 23;
          vZ_low = 0;
          LODWORD(igi2_frame.Real32x3_Rotate_tTemp.vX) = ptPhysicsObj;
          igi2_frame.Real32x3_Rotate_tTemp.vZ = 0.0;
          pfHandler = (void (__cdecl *)(int, struct real32x3_t *))QTask_aatQTaskFinalEvent[PhysicsObj_eHit][*(unsigned __int16 *)(v28 + 36)].pfHandler;
          if ( pfHandler )
          {
            pfHandler(v28, &igi2_frame.Real32x3_Rotate_tTemp);
            vZ_low = LODWORD(igi2_frame.Real32x3_Rotate_tTemp.vZ);
          }
          igi2_frame.isPenetrate = vZ_low;
          if ( vZ_low )
            goto LABEL_21;
        }
        if ( !v27
          && sqrt(
               igi2_frame.atPointVelocity[igi2_frame.i].vY * igi2_frame.atPointVelocity[igi2_frame.i].vY
             + igi2_frame.atPointVelocity[igi2_frame.i].vX * igi2_frame.atPointVelocity[igi2_frame.i].vX
             + igi2_frame.atPointVelocity[igi2_frame.i].vZ * igi2_frame.atPointVelocity[igi2_frame.i].vZ)
           + 40.959999084472656 <= *(double *)(v23 + 1) )
        {
LABEL_21:
          v31 = 0;
        }
        else
        {
          v31 = 1;
        }
        *v23 = v31;
        if ( v31 )
        {
          v32 = igi2_frame.aiCollPoint[igi2_frame.iCollPointa];
          ptPhysicsObj->atCollPoint[v32].vDistance = *(double *)(v23 + 1);
          v33 = (char *)ptPhysicsObj + v32 * 56;
          v34 = v23 - 9;
          if ( *((float *)v23 - 9) != 0.0 || *((float *)v23 - 8) != 0.0 || *((float *)v23 - 7) != 0.0 )
          {
            v35 = sqrt(
                    *(float *)v34 * *(float *)v34
                  + *((float *)v23 - 8) * *((float *)v23 - 8)
                  + *((float *)v23 - 7) * *((float *)v23 - 7));
            *(float *)v34 = *(float *)v34 * (1.0 / v35);
            *((float *)v23 - 8) = *((float *)v23 - 8) * (1.0 / v35);
            *((float *)v23 - 7) = *((float *)v23 - 7) * (1.0 / v35);
          }
          v36 = (int *)(v33 + 564);
          *v36 = *v34;
          v36[1] = v34[1];
          v36[2] = v34[2];
          p_tPhysics = &ptPhysicsObj->tPhysics;
          Physics_GetPointVelocity(&igi2_frame.tTemp, &ptPhysicsObj->tPhysics, &igi2_frame.atCheckPointLocal[igi2_frame.i]);
          v38 = igi2_frame.tTemp.vX * *(float *)v34 + igi2_frame.tTemp.vZ * *((float *)v23 - 7) + igi2_frame.tTemp.vY * *((float *)v23 - 8);
          igi2_frame.vVeloctiyRelationa = v38;
          if ( v38 <= 1.0 )
            break;
        }
      }
      v23 += 30;
      if ( ++igi2_frame.iCollPointa >= igi2_frame.nCollPoint )
        return igi2_frame.eCollision;
    }
    v40 = PHYSICSOBJ_COLL_CONTACT;
    if ( igi2_frame.vVeloctiyRelationa <= -1.0 )
      v40 = PHYSICSOBJ_COLL_COLL;
    v41 = igi2_frame.aiCollPoint[igi2_frame.iCollPointa];
    nContact = ptPhysicsObj->nContact;
    igi2_frame.eCollision = v40;
    v43 = (float *)((char *)ptPhysicsObj + 56 * v41);
    ptPhysicsObj->nContact = nContact + 1;
    v44 = (struct real32x3_t *)LODWORD(igi2_frame.v61);
    *((_BYTE *)v43 + 554) = 1;
    v44 = (struct real32x3_t *)((char *)v44 + 56);
    PhysicsObj_CollisionResponse(
      p_tPhysics,
      &ptPhysicsObj->tRigidDynCubeObj.tModelObj.tOrientation,
      v44,
      &igi2_frame.atCheckPointLocal[igi2_frame.iCollPointa],
      igi2_frame.vVeloctiyRelationa,
      vGravity,
      v43[134]);
    PhysicsObj_FrictionResponse(p_tPhysics, v44, vGravity, ptPhysicsObj->atCollPoint[v41].vFrictionY, vAngMomFriction);
    if ( igi2_frame.isPenetrate )
    {
      igi2_frame.tTemp.vX = ptPhysicsObj->tPhysics.tCMVel.vX;
      v45 = ptPhysicsObj->tPhysics.tCMVel.vZ;
      igi2_frame.tTemp.vY = ptPhysicsObj->tPhysics.tCMVel.vY;
      igi2_frame.tTemp.vX = igi2_frame.tTemp.vX * 0.25;
      igi2_frame.tTemp.vZ = v45;
      v46 = igi2_frame.tTemp.vY * 0.25;
      ptPhysicsObj->tPhysics.tCMVel.vX = igi2_frame.tTemp.vX;
      igi2_frame.tTemp.vY = v46;
      v47 = igi2_frame.tTemp.vZ;
      ptPhysicsObj->tPhysics.tCMVel.vY = igi2_frame.tTemp.vY;
      igi2_frame.tTemp.vZ = v47 * 0.25;
      ptPhysicsObj->tPhysics.tCMVel.vZ = igi2_frame.tTemp.vZ;
      Physics_UpdateSpeedApproximation(&ptPhysicsObj->tPhysics);
    }
  }
  return igi2_frame.eCollision;
}

// source: h/2/physicsobj.c:919  [anchor-callee]
int __cdecl PhysicsObj_AddNonContactForces(
        struct PhysicsObj_s *ptPhysicsObj,
        float vGravity,
        float vAirResictance,
        float vAngMomResictance,
        struct World_s *ptWorld)
{
  #pragma pack(push, 1)
  union
  {
    struct { float tVelocity; };
    struct { char igi2_o1[4]; float tVelocity_4; };
    struct { char igi2_o2[8]; float tVelocity_8; };
    struct { char igi2_o3[12]; struct PointForce_s tForce; };
    char igi2_extent[40];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct Physics_s *p_tPhysics; // ebx
  double v6; // st7
  double v7; // st6
  double vZ; // st6
  double v9; // rt0
  double v10; // st6
  int v11; // esi
  struct real32x3_t struct_real32x3_t; // 0:^C.12

  p_tPhysics = &ptPhysicsObj->tPhysics;
  v6 = -(vGravity * ptPhysicsObj->ptType->vMass);
  v7 = ptPhysicsObj->tRigidDynCubeObj.tModelObj.tOrientation.tY.vX
     + ptPhysicsObj->tRigidDynCubeObj.tModelObj.tOrientation.tX.vX;
  memset(&igi2_frame.tForce.tPoint, 0, sizeof(igi2_frame.tForce.tPoint));
  igi2_frame.tVelocity = v7 * 0.0 + v6 * ptPhysicsObj->tRigidDynCubeObj.tModelObj.tOrientation.tZ.vX;
  igi2_frame.tVelocity_4 = (ptPhysicsObj->tRigidDynCubeObj.tModelObj.tOrientation.tY.vY
               + ptPhysicsObj->tRigidDynCubeObj.tModelObj.tOrientation.tX.vY)
              * 0.0
              + v6 * ptPhysicsObj->tRigidDynCubeObj.tModelObj.tOrientation.tZ.vY;
  vZ = ptPhysicsObj->tRigidDynCubeObj.tModelObj.tOrientation.tY.vZ;
  igi2_frame.tForce.tForce.vY = igi2_frame.tVelocity_4;
  v9 = (vZ + ptPhysicsObj->tRigidDynCubeObj.tModelObj.tOrientation.tX.vZ) * 0.0;
  v10 = v6 * ptPhysicsObj->tRigidDynCubeObj.tModelObj.tOrientation.tZ.vZ;
  igi2_frame.tForce.tForce.vX = igi2_frame.tVelocity;
  igi2_frame.tVelocity_8 = v9 + v10;
  igi2_frame.tForce.tForce.vZ = igi2_frame.tVelocity_8;
  qmemcpy(
    &ptPhysicsObj->tPhysics.ptForces[ptPhysicsObj->tPhysics.nForces++],
    &igi2_frame.tForce,
    sizeof(ptPhysicsObj->tPhysics.ptForces[ptPhysicsObj->tPhysics.nForces++]));
  v11 = Physics_Update(&ptPhysicsObj->tPhysics, &ptPhysicsObj->tRigidDynCubeObj.tModelObj.tOrientation);
  struct_real32x3_t.vX = p_tPhysics->tAngMom.vX * vAngMomResictance;
  struct_real32x3_t.vY = p_tPhysics->tAngMom.vY * vAngMomResictance;
  struct_real32x3_t.vZ = p_tPhysics->tAngMom.vZ * vAngMomResictance;
  p_tPhysics->tAngMom = struct_real32x3_t;
  struct_real32x3_t.vX = p_tPhysics->tCMVel.vX * vAirResictance;
  struct_real32x3_t.vY = p_tPhysics->tCMVel.vY * vAirResictance;
  struct_real32x3_t.vZ = p_tPhysics->tCMVel.vZ * vAirResictance;
  p_tPhysics->tCMVel = struct_real32x3_t;
  Physics_UpdateSpeedApproximation(p_tPhysics);
  return v11;
}

// source: h/2/physicsobj.c:978  [anchor-callee]
void __cdecl PhysicsObj_Update(
        struct PhysicsObj_s *ptPhysicsObj,
        float vGravity,
        float vAirResictance,
        float vAngMomResictance,
        struct World_s *ptWorld,
        __int16 eCollisionEvalEvent,
        void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { float ptDynCubeObj; };
    struct { char igi2_o1[16]; float tSpeed; };
    struct { char igi2_o2[16]; float tSpeeda; };
    struct { char igi2_o3[20]; float tSpeed_4; };
    struct { char igi2_o4[20]; float tSpeed_4a; };
    struct { char igi2_o5[24]; float tSpeed_8; };
    struct { char igi2_o6[24]; float tSpeed_8a; };
    struct { char igi2_o7[28]; struct real64x3_t tNewPos; };
    struct { char igi2_o8[52]; struct real32x9_t tOldOrientation; };
    char igi2_extent[96];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct real32x9_t *p_tOrientation; // ebp
  float vY; // esi
  double v9; // st7
  double v10; // st7
  double v11; // st7
  double v12; // st7
  double vX; // st7
  double v14; // st7
  double v15; // st6
  float vZ; // eax
  double v17; // st7
  double v18; // st7
  struct LODVirModel_s *ptLODVirModel; // eax
  struct VirModel_s *v20; // eax
  double vRadius; // st6
  double v22; // st7
  float v23; // ecx
  float v24; // eax
  double v25; // st7
  double v26; // st7
  float v27; // ecx
  float v28; // eax
  float v29; // ecx
  double v30; // st7
  float v31; // eax
  float v32; // ecx
  double v33; // st7
  float v34; // eax
  int nOps; // ecx
  int v36; // ecx
  double v37; // st7

  p_tOrientation = &ptPhysicsObj->tRigidDynCubeObj.tModelObj.tOrientation;
  qmemcpy(&igi2_frame.tOldOrientation, &ptPhysicsObj->tRigidDynCubeObj.tModelObj.tOrientation, sizeof(igi2_frame.tOldOrientation));
  qmemcpy(&igi2_frame.tNewPos, &ptPhysicsObj->tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos, sizeof(igi2_frame.tNewPos));
  PhysicsObj_AddNonContactForces(ptPhysicsObj, vGravity, vAirResictance, vAngMomResictance, ptWorld);
  if ( ptPhysicsObj->isCollDetectionEnabled )
    PhysicsObj_AddContactForces(ptPhysicsObj, vGravity, vAngMomResictance, ptWorld, eCollisionEvalEvent, pxContext);
  if ( ptPhysicsObj->isForceZ )
  {
    vY = ptPhysicsObj->tPhysics.tCMVel.vY;
    ptPhysicsObj->tPhysics.tCMVel.vX = ptPhysicsObj->tPhysics.tCMVel.vX;
    ptPhysicsObj->tPhysics.tCMVel.vY = vY;
    ptPhysicsObj->tPhysics.tCMVel.vZ = 0.0;
    Physics_UpdateSpeedApproximation(&ptPhysicsObj->tPhysics);
  }
  if ( ptPhysicsObj->tPhysics.vCMSpeed > 40.959999084472656 )
  {
    igi2_frame.tNewPos.vX = ptPhysicsObj->tPhysics.tCMVel.vX + igi2_frame.tNewPos.vX;
    igi2_frame.tNewPos.vY = ptPhysicsObj->tPhysics.tCMVel.vY + igi2_frame.tNewPos.vY;
    igi2_frame.tNewPos.vZ = ptPhysicsObj->tPhysics.tCMVel.vZ + igi2_frame.tNewPos.vZ;
  }
  if ( ptPhysicsObj->isForceZ )
  {
    igi2_frame.tSpeed = igi2_frame.tOldOrientation.tZ.vZ * ptPhysicsObj->tRigidDynCubeObj.tModelObj.tOrientation.tY.vY
           - igi2_frame.tOldOrientation.tZ.vY * ptPhysicsObj->tRigidDynCubeObj.tModelObj.tOrientation.tY.vZ;
    v9 = igi2_frame.tOldOrientation.tZ.vZ * ptPhysicsObj->tRigidDynCubeObj.tModelObj.tOrientation.tY.vX;
    p_tOrientation->tX.vX = igi2_frame.tSpeed;
    igi2_frame.tSpeed_4 = -(v9 - igi2_frame.tOldOrientation.tZ.vX * ptPhysicsObj->tRigidDynCubeObj.tModelObj.tOrientation.tY.vZ);
    v10 = igi2_frame.tOldOrientation.tZ.vY;
    ptPhysicsObj->tRigidDynCubeObj.tModelObj.tOrientation.tX.vY = igi2_frame.tSpeed_4;
    igi2_frame.tSpeed_8 = v10 * ptPhysicsObj->tRigidDynCubeObj.tModelObj.tOrientation.tY.vX
             - igi2_frame.tOldOrientation.tZ.vX * ptPhysicsObj->tRigidDynCubeObj.tModelObj.tOrientation.tY.vY;
    v11 = igi2_frame.tOldOrientation.tZ.vY;
    ptPhysicsObj->tRigidDynCubeObj.tModelObj.tOrientation.tX.vZ = igi2_frame.tSpeed_8;
    igi2_frame.tSpeeda = v11 * ptPhysicsObj->tRigidDynCubeObj.tModelObj.tOrientation.tX.vZ
            - igi2_frame.tOldOrientation.tZ.vZ * ptPhysicsObj->tRigidDynCubeObj.tModelObj.tOrientation.tX.vY;
    v12 = igi2_frame.tOldOrientation.tZ.vX * ptPhysicsObj->tRigidDynCubeObj.tModelObj.tOrientation.tX.vZ;
    ptPhysicsObj->tRigidDynCubeObj.tModelObj.tOrientation.tY.vX = igi2_frame.tSpeeda;
    igi2_frame.tSpeed_4a = -(v12 - igi2_frame.tOldOrientation.tZ.vZ * p_tOrientation->tX.vX);
    vX = igi2_frame.tOldOrientation.tZ.vX;
    ptPhysicsObj->tRigidDynCubeObj.tModelObj.tOrientation.tY.vY = igi2_frame.tSpeed_4a;
    v14 = vX * ptPhysicsObj->tRigidDynCubeObj.tModelObj.tOrientation.tX.vY;
    v15 = igi2_frame.tOldOrientation.tZ.vY;
    ptPhysicsObj->tRigidDynCubeObj.tModelObj.tOrientation.tZ.vX = igi2_frame.tOldOrientation.tZ.vX;
    vZ = igi2_frame.tOldOrientation.tZ.vZ;
    igi2_frame.tSpeed_8a = v14 - v15 * p_tOrientation->tX.vX;
    ptPhysicsObj->tRigidDynCubeObj.tModelObj.tOrientation.tY.vZ = igi2_frame.tSpeed_8a;
    ptPhysicsObj->tRigidDynCubeObj.tModelObj.tOrientation.tZ.vY = igi2_frame.tOldOrientation.tZ.vY;
    ptPhysicsObj->tRigidDynCubeObj.tModelObj.tOrientation.tZ.vZ = vZ;
  }
  PhysicsObj_AssertNoIntersection(ptPhysicsObj, ptWorld, &igi2_frame.tNewPos, eCollisionEvalEvent, pxContext);
  if ( ptPhysicsObj->tRigidDynCubeObj.tModelObj.tScale.vY <= (double)ptPhysicsObj->tRigidDynCubeObj.tModelObj.tScale.vZ )
    v17 = ptPhysicsObj->tRigidDynCubeObj.tModelObj.tScale.vZ;
  else
    v17 = ptPhysicsObj->tRigidDynCubeObj.tModelObj.tScale.vY;
  if ( v17 >= ptPhysicsObj->tRigidDynCubeObj.tModelObj.tScale.vX )
  {
    if ( ptPhysicsObj->tRigidDynCubeObj.tModelObj.tScale.vY <= (double)ptPhysicsObj->tRigidDynCubeObj.tModelObj.tScale.vZ )
      v18 = ptPhysicsObj->tRigidDynCubeObj.tModelObj.tScale.vZ;
    else
      v18 = ptPhysicsObj->tRigidDynCubeObj.tModelObj.tScale.vY;
  }
  else
  {
    v18 = ptPhysicsObj->tRigidDynCubeObj.tModelObj.tScale.vX;
  }
  ptLODVirModel = ptPhysicsObj->tRigidDynCubeObj.tModelObj.ptLODVirModel;
  if ( ptLODVirModel && (v20 = ptLODVirModel->aptVirModel[0]) != nullptr )
    vRadius = v20->ptModel->ptMesh->vRadius;
  else
    vRadius = 1.0;
  igi2_frame.ptDynCubeObj = vRadius * v18;
  World_MoveDynCubeObjRadius(ptWorld, &ptPhysicsObj->tRigidDynCubeObj.tModelObj.tDynCubeObj, &igi2_frame.tNewPos, igi2_frame.ptDynCubeObj);
  v22 = ptPhysicsObj->tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos.vX - ptPhysicsObj->tLastPosition.vX;
  v23 = ptPhysicsObj->tLastOrientation.tY.vX;
  igi2_frame.tOldOrientation.tX.vX = ptPhysicsObj->tLastOrientation.tX.vX;
  v24 = ptPhysicsObj->tLastOrientation.tZ.vX;
  ptPhysicsObj->tDeltaPosition.vX = v22;
  v25 = ptPhysicsObj->tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos.vY;
  igi2_frame.tOldOrientation.tX.vY = v23;
  v26 = v25 - ptPhysicsObj->tLastPosition.vY;
  v27 = ptPhysicsObj->tLastOrientation.tX.vY;
  igi2_frame.tOldOrientation.tX.vZ = v24;
  v28 = ptPhysicsObj->tLastOrientation.tY.vY;
  ptPhysicsObj->tDeltaPosition.vY = v26;
  igi2_frame.tOldOrientation.tY.vX = v27;
  v29 = ptPhysicsObj->tLastOrientation.tZ.vY;
  v30 = ptPhysicsObj->tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos.vZ - ptPhysicsObj->tLastPosition.vZ;
  igi2_frame.tOldOrientation.tY.vY = v28;
  v31 = ptPhysicsObj->tLastOrientation.tX.vZ;
  igi2_frame.tOldOrientation.tY.vZ = v29;
  v32 = ptPhysicsObj->tLastOrientation.tY.vZ;
  ptPhysicsObj->tDeltaPosition.vZ = v30;
  v33 = ptPhysicsObj->tRigidDynCubeObj.tModelObj.tOrientation.tX.vY;
  igi2_frame.tOldOrientation.tZ.vX = v31;
  v34 = ptPhysicsObj->tLastOrientation.tZ.vZ;
  igi2_frame.tOldOrientation.tZ.vY = v32;
  nOps = ptPhysicsObj->tLastOrientation.nOps;
  igi2_frame.tOldOrientation.tZ.vZ = v34;
  igi2_frame.tOldOrientation.nOps = nOps;
  qmemcpy(&ptPhysicsObj->tDeltaOrientation, &igi2_frame.tOldOrientation, sizeof(ptPhysicsObj->tDeltaOrientation));
  igi2_frame.tOldOrientation.tX.vX = v33 * ptPhysicsObj->tDeltaOrientation.tY.vX
                        + ptPhysicsObj->tDeltaOrientation.tX.vX * p_tOrientation->tX.vX
                        + ptPhysicsObj->tRigidDynCubeObj.tModelObj.tOrientation.tX.vZ
                        * ptPhysicsObj->tDeltaOrientation.tZ.vX;
  igi2_frame.tOldOrientation.tX.vY = ptPhysicsObj->tDeltaOrientation.tZ.vY
                        * ptPhysicsObj->tRigidDynCubeObj.tModelObj.tOrientation.tX.vZ
                        + p_tOrientation->tX.vX * ptPhysicsObj->tDeltaOrientation.tX.vY
                        + ptPhysicsObj->tDeltaOrientation.tY.vY
                        * ptPhysicsObj->tRigidDynCubeObj.tModelObj.tOrientation.tX.vY;
  igi2_frame.tOldOrientation.tX.vZ = ptPhysicsObj->tDeltaOrientation.tZ.vZ
                        * ptPhysicsObj->tRigidDynCubeObj.tModelObj.tOrientation.tX.vZ
                        + ptPhysicsObj->tDeltaOrientation.tX.vZ * p_tOrientation->tX.vX
                        + ptPhysicsObj->tDeltaOrientation.tY.vZ
                        * ptPhysicsObj->tRigidDynCubeObj.tModelObj.tOrientation.tX.vY;
  v36 = ptPhysicsObj->tDeltaOrientation.nOps + ptPhysicsObj->tRigidDynCubeObj.tModelObj.tOrientation.nOps + 1;
  igi2_frame.tOldOrientation.tY.vX = ptPhysicsObj->tDeltaOrientation.tZ.vX
                        * ptPhysicsObj->tRigidDynCubeObj.tModelObj.tOrientation.tY.vZ
                        + ptPhysicsObj->tDeltaOrientation.tX.vX
                        * ptPhysicsObj->tRigidDynCubeObj.tModelObj.tOrientation.tY.vX
                        + ptPhysicsObj->tRigidDynCubeObj.tModelObj.tOrientation.tY.vY
                        * ptPhysicsObj->tDeltaOrientation.tY.vX;
  v37 = ptPhysicsObj->tRigidDynCubeObj.tModelObj.tOrientation.tY.vX;
  igi2_frame.tOldOrientation.nOps = v36;
  igi2_frame.tOldOrientation.tY.vY = v37 * ptPhysicsObj->tDeltaOrientation.tX.vY
                        + ptPhysicsObj->tDeltaOrientation.tZ.vY
                        * ptPhysicsObj->tRigidDynCubeObj.tModelObj.tOrientation.tY.vZ
                        + ptPhysicsObj->tDeltaOrientation.tY.vY
                        * ptPhysicsObj->tRigidDynCubeObj.tModelObj.tOrientation.tY.vY;
  igi2_frame.tOldOrientation.tY.vZ = ptPhysicsObj->tDeltaOrientation.tX.vZ
                        * ptPhysicsObj->tRigidDynCubeObj.tModelObj.tOrientation.tY.vX
                        + ptPhysicsObj->tDeltaOrientation.tZ.vZ
                        * ptPhysicsObj->tRigidDynCubeObj.tModelObj.tOrientation.tY.vZ
                        + ptPhysicsObj->tDeltaOrientation.tY.vZ
                        * ptPhysicsObj->tRigidDynCubeObj.tModelObj.tOrientation.tY.vY;
  igi2_frame.tOldOrientation.tZ.vX = ptPhysicsObj->tDeltaOrientation.tZ.vX
                        * ptPhysicsObj->tRigidDynCubeObj.tModelObj.tOrientation.tZ.vZ
                        + ptPhysicsObj->tDeltaOrientation.tX.vX
                        * ptPhysicsObj->tRigidDynCubeObj.tModelObj.tOrientation.tZ.vX
                        + ptPhysicsObj->tDeltaOrientation.tY.vX
                        * ptPhysicsObj->tRigidDynCubeObj.tModelObj.tOrientation.tZ.vY;
  igi2_frame.tOldOrientation.tZ.vY = ptPhysicsObj->tDeltaOrientation.tZ.vY
                        * ptPhysicsObj->tRigidDynCubeObj.tModelObj.tOrientation.tZ.vZ
                        + ptPhysicsObj->tDeltaOrientation.tY.vY
                        * ptPhysicsObj->tRigidDynCubeObj.tModelObj.tOrientation.tZ.vY
                        + ptPhysicsObj->tRigidDynCubeObj.tModelObj.tOrientation.tZ.vX
                        * ptPhysicsObj->tDeltaOrientation.tX.vY;
  igi2_frame.tOldOrientation.tZ.vZ = ptPhysicsObj->tDeltaOrientation.tZ.vZ
                        * ptPhysicsObj->tRigidDynCubeObj.tModelObj.tOrientation.tZ.vZ
                        + ptPhysicsObj->tDeltaOrientation.tY.vZ
                        * ptPhysicsObj->tRigidDynCubeObj.tModelObj.tOrientation.tZ.vY
                        + ptPhysicsObj->tDeltaOrientation.tX.vZ
                        * ptPhysicsObj->tRigidDynCubeObj.tModelObj.tOrientation.tZ.vX;
  qmemcpy(&ptPhysicsObj->tDeltaOrientation, &igi2_frame.tOldOrientation, sizeof(ptPhysicsObj->tDeltaOrientation));
  qmemcpy(
    &ptPhysicsObj->tLastPosition,
    &ptPhysicsObj->tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos,
    sizeof(ptPhysicsObj->tLastPosition));
  qmemcpy(&ptPhysicsObj->tLastOrientation, p_tOrientation, sizeof(ptPhysicsObj->tLastOrientation));
  RigidDynCubeObj_UpdateAttachments(&ptPhysicsObj->tRigidDynCubeObj);
}

// source: h/2/physicsobj.c:1127  [anchor-callee]
int __cdecl PhysicsObj_IsIdle(struct PhysicsObj_s *ptPhysicsObj)
{
  int nContact; // edx
  int isMovingCollPoint; // eax
  struct PhysicsObjType_s *ptType; // edx
  int result; // eax

  nContact = ptPhysicsObj->nContact;
  isMovingCollPoint = ptPhysicsObj->isMovingCollPoint;
  ptPhysicsObj->isMovingCollPoint = 0;
  result = false;
  if ( nContact > 0 && !isMovingCollPoint && !ptPhysicsObj->tPhysics.nForces )
  {
    ptType = ptPhysicsObj->ptType;
    if ( ptPhysicsObj->tPhysics.vCMSpeed < (double)ptType->vRestSpeed
      && ptPhysicsObj->tPhysics.tAngVel.vX * ptPhysicsObj->tPhysics.tAngVel.vX
       + ptPhysicsObj->tPhysics.tAngVel.vY * ptPhysicsObj->tPhysics.tAngVel.vY
       + ptPhysicsObj->tPhysics.tAngVel.vZ * ptPhysicsObj->tPhysics.tAngVel.vZ < ptType->vRestAngMomSquared )
    {
      return true;
    }
  }
  return result;
}

// source: h/2/physicsobj.c:1153  [anchor-mhash]
int __cdecl PhysicsObj_AddCollPoint(
        struct PhysicsObj_s *ptPhysicsObj,
        struct PhysicsObjCollPoint_s *ptCollPoint)
{
  int result; // eax
  char *i; // ecx
  char *v4; // edx

  result = 0;
  for ( i = &ptPhysicsObj->atCollPoint[0].isUsed; *i; i += 56 )
  {
    if ( ++result >= 22 )
      return 0;
  }
  v4 = (char *)ptPhysicsObj + 56 * result;
  qmemcpy(v4 + 528, ptCollPoint, 0x38u);
  v4[553] = 1;
  ++ptPhysicsObj->nCollPoint;
  return result;
}

// source: h/2/physicsobj.c:1183  [size]
int __cdecl PhysicsObj_RemoveCollPoint(
        struct PhysicsObj_s *ptPhysicsObj,
        int iCollPoint)
{
  int result; // eax

  result = iCollPoint;
  --ptPhysicsObj->nCollPoint;
  ptPhysicsObj->atCollPoint[result].isUsed = 0;
  return result * 56;
}

// source: h/2/physicsobj.c:1200  [size]
__int16 __cdecl PhysicsObj_GetMoveQTaskEvent()
{
  return PhysicsObj_eMove;
}

// source: h/2/physicsobj.c:1213  [size]
__int16 __cdecl PhysicsObj_GetUpdateOrientationQTaskEvent()
{
  return PhysicsObj_eUpdateOrientation;
}

// source: h/2/physicsobj.c:1226  [size]
__int16 __cdecl PhysicsObj_GetHitQTaskEvent()
{
  return PhysicsObj_eHit;
}

// source: h/2/physicsobj.c:1242  [anchor-mhash]
void __cdecl PhysicsObj_TriggerMoveEvent(
        struct PhysicsObj_s *ptPhysicsObj,
        struct World_s *ptWorld,
        __int16 eCollisionEvalEvent)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct real64x3_t tRadius; };
    struct { char igi2_o1[24]; struct real64x3_t tMax; };
    struct { char igi2_o2[48]; struct real64x3_t tMin; };
    char igi2_extent[72];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  double vZ; // st7
  double vY; // st7
  struct LODVirModel_s *ptLODVirModel; // edx
  double vRadius; // st6
  double v7; // st7
  double vX; // st7
  double v9; // st6
  double v10; // st7
  double v11; // st7
  struct VirModel_s *v12; // edx
  double v13; // st6
  double v14; // st7
  double v15; // st6
  double v16; // st5
  double v17; // st4
  double v18; // st3
  double v19; // st2
  double v20; // st1
  double v21; // st4
  double v22; // st5

  if ( ptPhysicsObj->tRigidDynCubeObj.tModelObj.tScale.vY <= (double)ptPhysicsObj->tRigidDynCubeObj.tModelObj.tScale.vZ )
    vZ = ptPhysicsObj->tRigidDynCubeObj.tModelObj.tScale.vZ;
  else
    vZ = ptPhysicsObj->tRigidDynCubeObj.tModelObj.tScale.vY;
  if ( vZ >= ptPhysicsObj->tRigidDynCubeObj.tModelObj.tScale.vX )
  {
    if ( ptPhysicsObj->tRigidDynCubeObj.tModelObj.tScale.vY <= (double)ptPhysicsObj->tRigidDynCubeObj.tModelObj.tScale.vZ )
      vY = ptPhysicsObj->tRigidDynCubeObj.tModelObj.tScale.vZ;
    else
      vY = ptPhysicsObj->tRigidDynCubeObj.tModelObj.tScale.vY;
  }
  else
  {
    vY = ptPhysicsObj->tRigidDynCubeObj.tModelObj.tScale.vX;
  }
  ptLODVirModel = ptPhysicsObj->tRigidDynCubeObj.tModelObj.ptLODVirModel;
  if ( ptLODVirModel && ptLODVirModel->aptVirModel[0] )
    vRadius = ptLODVirModel->aptVirModel[0]->ptModel->ptMesh->vRadius;
  else
    vRadius = 1.0;
  igi2_frame.tRadius.vX = vY * vRadius;
  if ( ptPhysicsObj->tRigidDynCubeObj.tModelObj.tScale.vY <= (double)ptPhysicsObj->tRigidDynCubeObj.tModelObj.tScale.vZ )
    v7 = ptPhysicsObj->tRigidDynCubeObj.tModelObj.tScale.vZ;
  else
    v7 = ptPhysicsObj->tRigidDynCubeObj.tModelObj.tScale.vY;
  if ( v7 >= ptPhysicsObj->tRigidDynCubeObj.tModelObj.tScale.vX )
  {
    if ( ptPhysicsObj->tRigidDynCubeObj.tModelObj.tScale.vY <= (double)ptPhysicsObj->tRigidDynCubeObj.tModelObj.tScale.vZ )
      vX = ptPhysicsObj->tRigidDynCubeObj.tModelObj.tScale.vZ;
    else
      vX = ptPhysicsObj->tRigidDynCubeObj.tModelObj.tScale.vY;
  }
  else
  {
    vX = ptPhysicsObj->tRigidDynCubeObj.tModelObj.tScale.vX;
  }
  if ( ptLODVirModel && ptLODVirModel->aptVirModel[0] )
    v9 = ptLODVirModel->aptVirModel[0]->ptModel->ptMesh->vRadius;
  else
    v9 = 1.0;
  igi2_frame.tRadius.vY = vX * v9;
  if ( ptPhysicsObj->tRigidDynCubeObj.tModelObj.tScale.vY <= (double)ptPhysicsObj->tRigidDynCubeObj.tModelObj.tScale.vZ )
    v10 = ptPhysicsObj->tRigidDynCubeObj.tModelObj.tScale.vZ;
  else
    v10 = ptPhysicsObj->tRigidDynCubeObj.tModelObj.tScale.vY;
  if ( v10 >= ptPhysicsObj->tRigidDynCubeObj.tModelObj.tScale.vX )
  {
    if ( ptPhysicsObj->tRigidDynCubeObj.tModelObj.tScale.vY <= (double)ptPhysicsObj->tRigidDynCubeObj.tModelObj.tScale.vZ )
      v11 = ptPhysicsObj->tRigidDynCubeObj.tModelObj.tScale.vZ;
    else
      v11 = ptPhysicsObj->tRigidDynCubeObj.tModelObj.tScale.vY;
  }
  else
  {
    v11 = ptPhysicsObj->tRigidDynCubeObj.tModelObj.tScale.vX;
  }
  if ( ptLODVirModel && (v12 = ptLODVirModel->aptVirModel[0]) != nullptr )
    v13 = v12->ptModel->ptMesh->vRadius;
  else
    v13 = 1.0;
  v14 = v11 * v13;
  if ( ptPhysicsObj->tLastPosition.vX >= ptPhysicsObj->tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos.vX )
    v15 = ptPhysicsObj->tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos.vX;
  else
    v15 = ptPhysicsObj->tLastPosition.vX;
  if ( ptPhysicsObj->tLastPosition.vY >= ptPhysicsObj->tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos.vY )
    v16 = ptPhysicsObj->tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos.vY;
  else
    v16 = ptPhysicsObj->tLastPosition.vY;
  if ( ptPhysicsObj->tLastPosition.vZ >= ptPhysicsObj->tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos.vZ )
    v17 = ptPhysicsObj->tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos.vZ;
  else
    v17 = ptPhysicsObj->tLastPosition.vZ;
  if ( ptPhysicsObj->tLastPosition.vX <= ptPhysicsObj->tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos.vX )
    v18 = ptPhysicsObj->tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos.vX;
  else
    v18 = ptPhysicsObj->tLastPosition.vX;
  if ( ptPhysicsObj->tLastPosition.vY <= ptPhysicsObj->tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos.vY )
    v19 = ptPhysicsObj->tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos.vY;
  else
    v19 = ptPhysicsObj->tLastPosition.vY;
  if ( ptPhysicsObj->tLastPosition.vZ <= ptPhysicsObj->tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos.vZ )
    v20 = ptPhysicsObj->tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos.vZ;
  else
    v20 = ptPhysicsObj->tLastPosition.vZ;
  igi2_frame.tMin.vX = v15 - igi2_frame.tRadius.vX;
  igi2_frame.tMin.vY = v16 - igi2_frame.tRadius.vY;
  igi2_frame.tMin.vZ = v17 - v14;
  v21 = v18 + igi2_frame.tRadius.vX;
  LODWORD(igi2_frame.tRadius.vX) = ptPhysicsObj;
  HIDWORD(igi2_frame.tRadius.vX) = ptWorld;
  igi2_frame.tMax.vX = v21;
  v22 = v19 + igi2_frame.tRadius.vY;
  LOWORD(igi2_frame.tRadius.vY) = eCollisionEvalEvent;
  igi2_frame.tMax.vY = v22;
  igi2_frame.tMax.vZ = v20 + v14;
  World_TriggerQTaskEventMinMaxXyzSpecificTree(
    World_ptActiveWorld,
    PhysicsObj_eMove,
    &igi2_frame.tRadius,
    &igi2_frame.tMin,
    &igi2_frame.tMax,
    0xFFFFFFFF,
    WORLD_DYNCUBETREE_STATIONARY);
}

// source: h/2/physicsobj.c:1298  [anchor-mhash]
enum PhysicsObjCollision_e __cdecl PhysicsObj_IsCollision(
        struct real32x3_t *ptNormal,
        struct Physics_s *ptPhysics,
        struct real32x3_t *ptPoint,
        struct real32x9_t *ptOrientation,
        float *pvVelocityRealtion)
{
  double v5; // st7
  enum PhysicsObjCollision_e result; // eax
  struct real32x3_t tPointVel; // [esp+0h] [ebp-Ch] BYREF

  Physics_GetPointVelocity(&tPointVel, ptPhysics, ptPoint);
  v5 = tPointVel.vZ * ptNormal->vZ + tPointVel.vY * ptNormal->vY + tPointVel.vX * ptNormal->vX;
  *pvVelocityRealtion = v5;
  if ( v5 > 1.0 )
    return PHYSICSOBJ_COLL_NONE;
  result = PHYSICSOBJ_COLL_CONTACT;
  if ( v5 <= -1.0 )
    return PHYSICSOBJ_COLL_COLL;
  return result;
}

// source: h/2/physicsobj.c:1339  [anchor-callee]
void __cdecl PhysicsObj_CollisionResponse(
        struct Physics_s *ptPhysics,
        struct real32x9_t *ptOrientation,
        struct real32x3_t *ptNormal,
        struct real32x3_t *ptPoint,
        float vVelocityRelation,
        float vGravity,
        float vCoefficientOfRestitution)
{
  double vIxxInv; // st7
  double vIyyInv; // st6
  double v9; // st5
  double v10; // st4
  double v11; // st3
  double v12; // st5
  double v13; // rt2
  double v14; // st4
  double v15; // st5
  double v16; // st5
  double v17; // st5
  double v18; // st4
  double v19; // st3
  double v20; // st5
  double v21; // st4
  double v22; // rt2
  double v23; // st4
  struct real32x3_t *p_tCMVel; // ebx
  long double v25; // st7
  double v26; // st7
  double v27; // st7
  float v28; // [esp+4h] [ebp-4Ch]
  float v29; // [esp+4h] [ebp-4Ch]
  float v30; // [esp+8h] [ebp-48h]
  float v31; // [esp+8h] [ebp-48h]
  float v32; // [esp+Ch] [ebp-44h]
  float tForcea; // [esp+10h] [ebp-40h]
  float tForceb; // [esp+10h] [ebp-40h]
  float tForcec; // [esp+10h] [ebp-40h]
  float tForce_4a; // [esp+14h] [ebp-3Ch]
  float tForce_4b; // [esp+14h] [ebp-3Ch]
  float tForce_8a; // [esp+18h] [ebp-38h]
  float tForce_8b; // [esp+18h] [ebp-38h]
  float tForce_8c; // [esp+18h] [ebp-38h]
  float tLinMom; // [esp+1Ch] [ebp-34h]
  float tLinMoma; // [esp+1Ch] [ebp-34h]
  float tLinMomb; // [esp+1Ch] [ebp-34h]
  float tLinMom_4; // [esp+20h] [ebp-30h]
  float tLinMom_4a; // [esp+20h] [ebp-30h]
  float tLinMom_4b; // [esp+20h] [ebp-30h]
  float tLinMom_8; // [esp+24h] [ebp-2Ch]
  float tInertiaTensorInv_32; // [esp+48h] [ebp-8h]
  float ptPhysicsa = *(float *)&vVelocityRelation; // [esp+54h] [ebp+4h] ARGSLOT
  float ptNormala = *(float *)&vCoefficientOfRestitution; // [esp+5Ch] [ebp+Ch] ARGSLOT
  float ptNormalb = *(float *)&vCoefficientOfRestitution; // [esp+5Ch] [ebp+Ch] ARGSLOT
  struct real32x3_t struct_real32x3_ta; // 0:^10.12
  struct real32x3_t tForce; // 0:^10.12
  struct real32x3_t struct_real32x3_t; // 0:^1C.12

  vIxxInv = ptPhysics->vIxxInv;
  vIyyInv = ptPhysics->vIyyInv;
  tInertiaTensorInv_32 = ptPhysics->vIzzInv;
  v9 = ptNormal->vZ * ptPoint->vY - ptPoint->vZ * ptNormal->vY;
  v10 = -(ptNormal->vZ * ptPoint->vX - ptPoint->vZ * ptNormal->vX);
  v11 = ptNormal->vY * ptPoint->vX - ptNormal->vX * ptPoint->vY;
  tLinMom = v9 * ptOrientation->tX.vX + v11 * ptOrientation->tZ.vX + v10 * ptOrientation->tY.vX;
  tLinMom_4 = v9 * ptOrientation->tX.vY + v11 * ptOrientation->tZ.vY + v10 * ptOrientation->tY.vY;
  v12 = v11 * ptOrientation->tZ.vZ + v10 * ptOrientation->tY.vZ + v9 * ptOrientation->tX.vZ;
  v30 = tLinMom_4 * 0.0;
  tForcea = vIxxInv * tLinMom + v30 + 0.0 * v12;
  v28 = tLinMom * 0.0;
  v13 = 0.0 * v12 + vIyyInv * tLinMom_4 + v28;
  v14 = v12 * tInertiaTensorInv_32 + v28 + v30;
  tLinMoma = tForcea * ptOrientation->tX.vX + v13 * ptOrientation->tX.vY + v14 * ptOrientation->tX.vZ;
  tLinMom_4a = v14 * ptOrientation->tY.vZ + v13 * ptOrientation->tY.vY + tForcea * ptOrientation->tY.vX;
  v15 = v14 * ptOrientation->tZ.vZ + v13 * ptOrientation->tZ.vY + tForcea * ptOrientation->tZ.vX;
  tLinMom_8 = tLinMoma * ptPoint->vY - tLinMom_4a * ptPoint->vX;
  ptNormala = -((vCoefficientOfRestitution + 1.0) * vVelocityRelation)
            / ((tLinMom_4a * ptPoint->vZ - v15 * ptPoint->vY) * ptNormal->vX
             + -(tLinMoma * ptPoint->vZ - v15 * ptPoint->vX) * ptNormal->vY
             + tLinMom_8 * ptNormal->vZ
             + ptPhysics->vMInv);
  tForceb = ptNormal->vX * ptNormala;
  tForce_4a = ptNormal->vY * ptNormala;
  v16 = ptNormal->vZ * ptNormala;
  tForce_8a = v16;
  v17 = v16 * ptPoint->vY - tForce_4a * ptPoint->vZ;
  v18 = -(tForce_8a * ptPoint->vX - tForceb * ptPoint->vZ);
  v19 = tForce_4a * ptPoint->vX - tForceb * ptPoint->vY;
  tLinMomb = v19 * ptOrientation->tZ.vX + v18 * ptOrientation->tY.vX + v17 * ptOrientation->tX.vX;
  tLinMom_4b = v17 * ptOrientation->tX.vY + v19 * ptOrientation->tZ.vY + v18 * ptOrientation->tY.vY;
  v20 = v17 * ptOrientation->tX.vZ + v19 * ptOrientation->tZ.vZ + v18 * ptOrientation->tY.vZ;
  v21 = tLinMomb + ptPhysics->tAngMom.vX;
  ptPhysics->tAngMom.vX = v21;
  ptNormalb = tLinMom_4b + ptPhysics->tAngMom.vY;
  v22 = v21;
  v23 = v20 + ptPhysics->tAngMom.vZ;
  ptPhysics->tAngMom.vY = ptNormalb;
  ptPhysicsa = v23;
  ptPhysics->tAngMom.vZ = ptPhysicsa;
  v31 = ptPhysicsa * 0.0;
  v32 = ptNormalb * 0.0;
  struct_real32x3_t.vX = v22 * vIxxInv + v32 + v31;
  v29 = v22 * 0.0;
  struct_real32x3_t.vY = ptNormalb * vIyyInv + v29 + v31;
  struct_real32x3_t.vZ = ptPhysicsa * tInertiaTensorInv_32 + v29 + v32;
  ptPhysics->tAngVel = struct_real32x3_t;
  p_tCMVel = &ptPhysics->tCMVel;
  struct_real32x3_t.vX = ptPhysics->tAngVel.vZ * ptOrientation->tX.vZ
                       + ptPhysics->tAngVel.vY * ptOrientation->tX.vY
                       + ptOrientation->tX.vX * ptPhysics->tAngVel.vX;
  struct_real32x3_t.vY = ptPhysics->tAngVel.vZ * ptOrientation->tY.vZ
                       + ptPhysics->tAngVel.vY * ptOrientation->tY.vY
                       + ptPhysics->tAngVel.vX * ptOrientation->tY.vX;
  struct_real32x3_t.vZ = ptPhysics->tAngVel.vZ * ptOrientation->tZ.vZ
                       + ptPhysics->tAngVel.vY * ptOrientation->tZ.vY
                       + ptPhysics->tAngVel.vX * ptOrientation->tZ.vX;
  ptPhysics->tAngVel = struct_real32x3_t;
  struct_real32x3_t.vZ = tForce_8a * ptPhysics->vMInv;
  struct_real32x3_ta.vX = ptPhysics->tCMVel.vX + tForceb * ptPhysics->vMInv;
  struct_real32x3_ta.vY = ptPhysics->tCMVel.vY + tForce_4a * ptPhysics->vMInv;
  struct_real32x3_ta.vZ = ptPhysics->tCMVel.vZ + struct_real32x3_t.vZ;
  ptPhysics->tCMVel = struct_real32x3_ta;
  Physics_UpdateSpeedApproximation(ptPhysics);
  tForce = *ptNormal;
  if ( ptNormal->vX != 0.0 || tForce.vY != 0.0 || tForce.vZ != 0.0 )
  {
    v25 = 1.0 / sqrt(tForce.vX * tForce.vX + tForce.vY * tForce.vY + tForce.vZ * tForce.vZ);
    tForce.vX = tForce.vX * v25;
    tForce.vY = tForce.vY * v25;
    tForce.vZ = tForce.vZ * v25;
  }
  v26 = tForce.vZ * ptPhysics->tCMVel.vZ + tForce.vY * ptPhysics->tCMVel.vY + tForce.vX * p_tCMVel->vX;
  if ( v26 < 0.0 )
  {
    tForce_8b = -(v26 * tForce.vZ);
    tForcec = p_tCMVel->vX - tForce.vX * v26;
    tForce_4b = ptPhysics->tCMVel.vY - v26 * tForce.vY;
    v27 = tForce_8b + ptPhysics->tCMVel.vZ;
    p_tCMVel->vX = tForcec;
    ptPhysics->tCMVel.vY = tForce_4b;
    tForce_8c = v27;
    ptPhysics->tCMVel.vZ = tForce_8c;
    Physics_UpdateSpeedApproximation(ptPhysics);
  }
}

// source: h/2/physicsobj.c:1440  [anchor-callee]
void __cdecl PhysicsObj_FrictionResponse(
        struct Physics_s *ptPhysics,
        struct real32x3_t *ptNormal,
        float vGravity,
        float vCoefficientOfFriction,
        float vCoefficientOfAngMomFriction)
{
  double v5; // st7
  double v6; // st7
  float vZ; // eax
  double v8; // st6
  double v9; // st5
  double v10; // st6
  double v11; // st6
  double v12; // st6
  double v13; // st5
  double v14; // st6
  float tFrictionForceb; // [esp+0h] [ebp-18h]
  float tFrictionForce; // [esp+0h] [ebp-18h]
  float tFrictionForcea; // [esp+0h] [ebp-18h]
  float tFrictionForcec; // [esp+0h] [ebp-18h]
  float tFrictionForce_4b; // [esp+4h] [ebp-14h]
  float tFrictionForce_4; // [esp+4h] [ebp-14h]
  float tFrictionForce_4a; // [esp+4h] [ebp-14h]
  float tFrictionForce_4c; // [esp+4h] [ebp-14h]
  float tFrictionForce_8; // [esp+8h] [ebp-10h]
  float tAngMom; // [esp+Ch] [ebp-Ch]
  float tAngMoma; // [esp+Ch] [ebp-Ch]
  float tAngMom_4; // [esp+10h] [ebp-8h]
  float tAngMom_4a; // [esp+10h] [ebp-8h]
  float tAngMom_8; // [esp+14h] [ebp-4h]
  float tAngMom_8a; // [esp+14h] [ebp-4h]
  float ptPhysicsa = *(float *)&vGravity; // [esp+1Ch] [ebp+4h] ARGSLOT
  float ptPhysicsb = *(float *)&vGravity; // [esp+1Ch] [ebp+4h] ARGSLOT
  struct real32x3_t struct_real32x3_t; // 0:^C.12

  v5 = vGravity * ptNormal->vZ;
  if ( v5 < 0.0 )
    v5 = -v5;
  if ( v5 != 0.0 )
  {
    v6 = v5 * vCoefficientOfFriction;
    tFrictionForceb = ptPhysics->tCMVelDir.vX;
    vZ = ptPhysics->tCMVelDir.vZ;
    tFrictionForce_4b = ptPhysics->tCMVelDir.vY;
    tAngMom = tFrictionForce_4b * ptNormal->vZ - vZ * ptNormal->vY;
    tAngMom_4 = -(tFrictionForceb * ptNormal->vZ - vZ * ptNormal->vX);
    v8 = tFrictionForceb;
    tFrictionForce = tAngMom;
    v9 = tFrictionForce_4b;
    tFrictionForce_4 = tAngMom_4;
    tAngMom_8 = v8 * ptNormal->vY - v9 * ptNormal->vX;
    ptPhysicsa = sqrt(tAngMom_4 * tAngMom_4 + tAngMom_8 * tAngMom_8 + tAngMom * tAngMom);
    if ( ptPhysicsa >= 9.999999747378752e-06 )
    {
      if ( tAngMom == 0.0 && tAngMom_4 == 0.0 && tAngMom_8 == 0.0 )
      {
        v11 = tAngMom_8;
      }
      else
      {
        v10 = 1.0 / ptPhysicsa;
        tFrictionForce = tAngMom * v10;
        tFrictionForce_4 = tAngMom_4 * v10;
        v11 = v10 * tAngMom_8;
      }
      tAngMoma = tFrictionForce_4 * ptNormal->vZ - v11 * ptNormal->vY;
      tAngMom_4a = -(tFrictionForce * ptNormal->vZ - v11 * ptNormal->vX);
      v12 = tFrictionForce;
      tFrictionForcea = tAngMoma;
      v13 = tFrictionForce_4 * ptNormal->vX;
      tFrictionForce_4a = tAngMom_4a;
      tAngMom_8a = v12 * ptNormal->vY - v13;
      tFrictionForce_8 = tAngMom_8a;
    }
    else
    {
      tFrictionForcea = 0.0;
      tFrictionForce_4a = 0.0;
      tFrictionForce_8 = 0.0;
    }
    v14 = tFrictionForce_4a * ptPhysics->tCMVel.vY
        + tFrictionForcea * ptPhysics->tCMVel.vX
        + tFrictionForce_8 * ptPhysics->tCMVel.vZ;
    ptPhysicsb = v14;
    if ( v14 < 0.0 )
      v14 = -v14;
    if ( v6 > v14 )
    {
      v6 = ptPhysicsb;
      if ( ptPhysicsb < 0.0 )
        v6 = -v6;
    }
    tFrictionForcec = tFrictionForcea * v6;
    tFrictionForce_4c = tFrictionForce_4a * v6;
    struct_real32x3_t.vX = tFrictionForcec + ptPhysics->tCMVel.vX;
    struct_real32x3_t.vY = tFrictionForce_4c + ptPhysics->tCMVel.vY;
    struct_real32x3_t.vZ = v6 * tFrictionForce_8 + ptPhysics->tCMVel.vZ;
    ptPhysics->tCMVel = struct_real32x3_t;
    Physics_UpdateSpeedApproximation(ptPhysics);
    struct_real32x3_t.vX = ptPhysics->tAngMom.vX * vCoefficientOfAngMomFriction;
    struct_real32x3_t.vY = ptPhysics->tAngMom.vY * vCoefficientOfAngMomFriction;
    struct_real32x3_t.vZ = ptPhysics->tAngMom.vZ * vCoefficientOfAngMomFriction;
    ptPhysics->tAngMom = struct_real32x3_t;
  }
}
