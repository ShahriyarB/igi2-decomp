/* j/0/vehicles/plane.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/vehicles/plane.c:142  [size]
struct Plane_s *__cdecl Plane_RemoveSounds(struct Plane_s *ptPlane)
{
  struct Plane_s *result; // eax

  QTask_DeleteQTaskAndQTaskRefSafe(&ptPlane->ptEngineSoundDefQTaskRef);
  return result;
}

// source: j/0/vehicles/plane.c:155  [anchor-caller]
void __cdecl Plane_AddWheelForces(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { float ptDynCubeObj; };
    struct { char igi2_o1[20]; unsigned int iTracePos; };
    struct { char igi2_o2[20]; int iTracePosa; };
    struct { char igi2_o3[24]; struct real32x3_t *v44; };
    struct { char igi2_o4[24]; int v45; };
    struct { char igi2_o5[28]; double vMaxHardCollisionDistance; };
    struct { char igi2_o6[28]; double vMaxHardCollisionDistancea; };
    struct { char igi2_o7[28]; double vMaxHardCollisionDistanceb; };
    struct { char igi2_o8[28]; double vMaxHardCollisionDistancec; };
    struct { char igi2_o9[28]; double vMaxHardCollisionDistanced; };
    struct { char igi2_o10[36]; struct real64x3_t aptGear; };
    struct { char igi2_o11[60]; int isHardContact; };
    struct { char igi2_o12[64]; int nTracePos; };
    struct { char igi2_o13[68]; double avTraceLength[4]; };
    struct { char igi2_o14[100]; struct CollisionEvaluateContext_s tContext; };
    struct { char igi2_o15[108]; struct real64x3_t atTracePos[4]; };
    struct { char igi2_o16[204]; struct real32x3_t atForcePos[4]; };
    struct { char igi2_o17[252]; struct real64x3_t atTracePosStop[4]; };
    struct { char igi2_o18[348]; struct QIntersection_s atIntersection[4]; };
    char igi2_extent[828];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *ptNext; // eax
  struct RigidDynCubeObj_t *FirstChildOfType; // ebx
  struct real32x3_t *v3; // esi
  int v4; // edx
  int eQTaskType; // edi
  unsigned __int16 v6; // cx
  int v7; // edi
  int v8; // eax
  double v9; // st7
  double vY; // st7
  double v11; // st7
  double v12; // st7
  int v13; // esi
  double v14; // st7
  int v15; // ecx
  struct real32x3_t *v16; // ebx
  double *p_vDistance; // edx
  double v18; // st6
  float vZ; // ecx
  struct QTask_s *ptMiddle; // eax
  double v21; // st6
  float v22; // ecx
  struct QTask_s *v23; // eax
  double v24; // st6
  float v25; // ecx
  struct QTask_s *v26; // eax
  double v27; // st6
  float v28; // ecx
  struct QTask_s *v29; // eax
  bool v30; // cc
  struct real32x3_t *v31; // ebx
  double *v32; // edx
  double v33; // st6
  float v34; // ecx
  struct QTask_s *v35; // eax
  double v36; // st7
  double v37; // st7
  int *v38; // eax
  int v39; // eax
  double v40; // st6

  ptNext = ptQTask[3].ptNext;
  igi2_frame.nTracePos = 0;
  FirstChildOfType = (struct RigidDynCubeObj_t *)QTask_GetFirstChildOfType(ptNext, Gear_eQTaskType);
  igi2_frame.isHardContact = 0;
  if ( FirstChildOfType )
  {
    v3 = igi2_frame.atForcePos;
    v4 = 0;
    igi2_frame.v44 = igi2_frame.atForcePos;
    for ( igi2_frame.iTracePos = 0; v4 < 96; v4 = igi2_frame.iTracePos )
    {
      eQTaskType = FirstChildOfType->tModelObj.tDynCubeObj.tQObj.tQTask.eQTaskType;
      if ( QTask_IsQTaskTypeDerived(
             FirstChildOfType->tModelObj.tDynCubeObj.tQObj.tQTask.eQTaskType,
             RigidDynCubeObj_eQTaskType) )
      {
        RigidDynCubeObj_GetMagicVertexPos(FirstChildOfType, 0, (struct real64x3_t *)((char *)igi2_frame.atTracePos + v4));
        v4 = igi2_frame.iTracePos;
      }
      else if ( QTask_IsQTaskTypeDerived(eQTaskType, BoneDynCubeObj_eQTaskType) )
      {
        BoneDynCubeObj_GetMagicVertexPos(
          (struct BoneDynCubeObj_s *)FirstChildOfType,
          0,
          (struct real64x3_t *)((char *)igi2_frame.atTracePos + v4));
        v3 = igi2_frame.v44;
        v4 = igi2_frame.iTracePos;
      }
      else
      {
        *(_DWORD *)((char *)&igi2_frame.atTracePos[0].vX + v4) = 0;
        *(_DWORD *)((char *)&igi2_frame.atTracePos[0].vX + v4 + 4) = 0;
        *(_DWORD *)((char *)&igi2_frame.atTracePos[0].vY + v4) = 0;
        *(_DWORD *)((char *)&igi2_frame.atTracePos[0].vY + v4 + 4) = 0;
        *(_DWORD *)((char *)&igi2_frame.atTracePos[0].vZ + v4) = 0;
        *(_DWORD *)((char *)&igi2_frame.atTracePos[0].vZ + v4 + 4) = 0;
      }
      v6 = RigidDynCubeObj_eQTaskType;
      *(double *)((char *)&igi2_frame.atTracePos[0].vZ + v4) = *(double *)((char *)&igi2_frame.atTracePos[0].vZ + v4) + 8192.0;
      v7 = FirstChildOfType->tModelObj.tDynCubeObj.tQObj.tQTask.eQTaskType;
      if ( QTask_IsQTaskTypeDerived(FirstChildOfType->tModelObj.tDynCubeObj.tQObj.tQTask.eQTaskType, v6) )
      {
        RigidDynCubeObj_GetMagicVertexLocalPos(FirstChildOfType, 0, v3);
        v3 = igi2_frame.v44;
        v4 = igi2_frame.iTracePos;
      }
      else if ( QTask_IsQTaskTypeDerived(v7, BoneDynCubeObj_eQTaskType) )
      {
        BoneDynCubeObj_GetMagicVertexLocalPos((struct BoneDynCubeObj_s *)FirstChildOfType, 0, v3);
        v3 = igi2_frame.v44;
        v4 = igi2_frame.iTracePos;
      }
      else
      {
        v3->vX = 0.0;
        v3->vY = 0.0;
        v3->vZ = 0.0;
      }
      v8 = igi2_frame.nTracePos;
      v9 = FirstChildOfType->tModelObj.tRelativePos.vX + v3->vX;
      LODWORD(igi2_frame.avTraceLength[igi2_frame.nTracePos]) = 0;
      v3->vX = v9;
      HIDWORD(igi2_frame.avTraceLength[v8]) = -1061158912;
      vY = FirstChildOfType->tModelObj.tRelativePos.vY;
      *((_DWORD *)&igi2_frame.aptGear.vX + v8) = FirstChildOfType;
      v11 = vY + v3->vY;
      igi2_frame.nTracePos = v8 + 1;
      v3->vY = v11;
      v3->vZ = FirstChildOfType->tModelObj.tRelativePos.vZ + v3->vZ;
      qmemcpy((char *)igi2_frame.atTracePosStop + v4, &igi2_frame.atTracePos[igi2_frame.iTracePos / 0x18], sizeof(struct real64x3_t));
      v12 = *(double *)&igi2_frame.atForcePos[igi2_frame.iTracePos / 0xC + 5].vY - 8192.0;
      igi2_frame.iTracePos += 24;
      ++igi2_frame.v44;
      *(double *)&igi2_frame.atForcePos[igi2_frame.iTracePos / 0xC + 3].vY = v12;
      FirstChildOfType = (struct RigidDynCubeObj_t *)QTask_GetNextSiblingOfType(
                                                       &FirstChildOfType->tModelObj.tDynCubeObj.tQObj.tQTask,
                                                       Gear_eQTaskType);
      if ( !FirstChildOfType )
        break;
      v3 = igi2_frame.v44;
    }
    v13 = igi2_frame.nTracePos;
    if ( igi2_frame.nTracePos )
    {
      igi2_frame.tContext.ptQTask = ptQTask;
      World_TraceLines(
        Game_ptGame->ptWorld,
        igi2_frame.atIntersection,
        igi2_frame.atTracePos,
        igi2_frame.atTracePosStop,
        igi2_frame.nTracePos,
        13,
        &igi2_frame.tContext,
        0xFFFFFFFF);
      v14 = -1.7976931348623157e+308;
      v15 = 0;
      igi2_frame.iTracePosa = 0;
      if ( v13 >= 4 )
      {
        igi2_frame.v45 = 3;
        v16 = &igi2_frame.atForcePos[1];
        p_vDistance = &igi2_frame.atIntersection[0].vDistance;
        do
        {
          if ( *((_DWORD *)p_vDistance - 1) )
          {
            v18 = igi2_frame.avTraceLength[v15];
            if ( v18 < 0.0 )
              v18 = -v18;
            if ( v18 >= *p_vDistance )
            {
              igi2_frame.aptGear.vX = 0.0;
              if ( *p_vDistance >= 7577.6 )
              {
                *(float *)&igi2_frame.aptGear.vY = (8192.0 - *p_vDistance)
                                      * 0.0016276041666666667
                                      * *(float *)(*(_DWORD *)&ptQTask[12].eQTaskType + 8)
                                      * 17.840354919433594;
              }
              else
              {
                *(float *)&igi2_frame.aptGear.vY = ((7577.60009765625 - *p_vDistance) * 0.0001319678995059803 + 1.0)
                                      * *(float *)(*(_DWORD *)&ptQTask[12].eQTaskType + 8)
                                      * 17.840354919433594;
                igi2_frame.vMaxHardCollisionDistance = 7577.6 - *p_vDistance;
                if ( v14 < igi2_frame.vMaxHardCollisionDistance )
                  v14 = igi2_frame.vMaxHardCollisionDistance;
                igi2_frame.isHardContact = 1;
              }
              HIDWORD(igi2_frame.aptGear.vY) = LODWORD(v16[-1].vX);
              vZ = v16[-1].vZ;
              *(float *)&igi2_frame.aptGear.vZ = v16[-1].vY;
              ptMiddle = ptQTask[10].tQTaskChildren.ptMiddle;
              *((float *)&igi2_frame.aptGear.vZ + 1) = vZ;
              qmemcpy((char *)ptQTask[10].ptPrev + 24 * (_DWORD)ptMiddle, &igi2_frame.aptGear, 0x18u);
              ++*(int *)&ptQTask[10].tQTaskChildren.ptMiddle;
              v15 = igi2_frame.iTracePosa;
              *(float *)&ptQTask[8].tQTaskRefList.ptMiddle = *(float *)&ptQTask[47].tQTaskRefList.ptMiddle
                                                           * *(float *)&ptQTask[8].tQTaskRefList.ptMiddle
                                                           * 0.800000011920929;
              *(float *)&ptQTask[8].tQTaskRefList.ptTail = *(float *)&ptQTask[47].tQTaskRefList.ptMiddle
                                                         * *(float *)&ptQTask[8].tQTaskRefList.ptTail
                                                         * 0.800000011920929;
              *(float *)&ptQTask[9].tQTaskChildren.ptHead = *(float *)&ptQTask[9].tQTaskChildren.ptHead * 0.9800000190734863;
              *(float *)&ptQTask[9].tQTaskChildren.ptMiddle = *(float *)&ptQTask[9].tQTaskChildren.ptMiddle * 0.9800000190734863;
              *(float *)&ptQTask[9].tQTaskChildren.ptTail = *(float *)&ptQTask[9].tQTaskChildren.ptTail * 0.9800000190734863;
            }
          }
          if ( *((_DWORD *)p_vDistance + 29) )
          {
            v21 = igi2_frame.avTraceLength[v15 + 1];
            if ( v21 < 0.0 )
              v21 = -v21;
            if ( v21 >= p_vDistance[15] )
            {
              igi2_frame.aptGear.vX = 0.0;
              if ( p_vDistance[15] >= 7577.6 )
              {
                *(float *)&igi2_frame.aptGear.vY = (8192.0 - p_vDistance[15])
                                      * 0.0016276041666666667
                                      * *(float *)(*(_DWORD *)&ptQTask[12].eQTaskType + 8)
                                      * 17.840354919433594;
              }
              else
              {
                *(float *)&igi2_frame.aptGear.vY = ((7577.60009765625 - p_vDistance[15]) * 0.0001319678995059803 + 1.0)
                                      * *(float *)(*(_DWORD *)&ptQTask[12].eQTaskType + 8)
                                      * 17.840354919433594;
                igi2_frame.vMaxHardCollisionDistancea = 7577.6 - p_vDistance[15];
                if ( v14 < igi2_frame.vMaxHardCollisionDistancea )
                  v14 = igi2_frame.vMaxHardCollisionDistancea;
                igi2_frame.isHardContact = 1;
              }
              HIDWORD(igi2_frame.aptGear.vY) = LODWORD(v16->vX);
              v22 = v16->vY;
              HIDWORD(igi2_frame.aptGear.vZ) = LODWORD(v16->vZ);
              v23 = ptQTask[10].tQTaskChildren.ptMiddle;
              *(float *)&igi2_frame.aptGear.vZ = v22;
              qmemcpy((char *)ptQTask[10].ptPrev + 24 * (_DWORD)v23, &igi2_frame.aptGear, 0x18u);
              ++*(int *)&ptQTask[10].tQTaskChildren.ptMiddle;
              v15 = igi2_frame.iTracePosa;
              *(float *)&ptQTask[8].tQTaskRefList.ptMiddle = *(float *)&ptQTask[47].tQTaskRefList.ptMiddle
                                                           * *(float *)&ptQTask[8].tQTaskRefList.ptMiddle
                                                           * 0.800000011920929;
              *(float *)&ptQTask[8].tQTaskRefList.ptTail = *(float *)&ptQTask[47].tQTaskRefList.ptMiddle
                                                         * *(float *)&ptQTask[8].tQTaskRefList.ptTail
                                                         * 0.800000011920929;
              *(float *)&ptQTask[9].tQTaskChildren.ptHead = *(float *)&ptQTask[9].tQTaskChildren.ptHead * 0.9800000190734863;
              *(float *)&ptQTask[9].tQTaskChildren.ptMiddle = *(float *)&ptQTask[9].tQTaskChildren.ptMiddle * 0.9800000190734863;
              *(float *)&ptQTask[9].tQTaskChildren.ptTail = *(float *)&ptQTask[9].tQTaskChildren.ptTail * 0.9800000190734863;
            }
          }
          if ( *((_DWORD *)p_vDistance + 59) )
          {
            v24 = igi2_frame.avTraceLength[v15 + 2];
            if ( v24 < 0.0 )
              v24 = -v24;
            if ( v24 >= p_vDistance[30] )
            {
              igi2_frame.aptGear.vX = 0.0;
              if ( p_vDistance[30] >= 7577.6 )
              {
                *(float *)&igi2_frame.aptGear.vY = (8192.0 - p_vDistance[30])
                                      * 0.0016276041666666667
                                      * *(float *)(*(_DWORD *)&ptQTask[12].eQTaskType + 8)
                                      * 17.840354919433594;
              }
              else
              {
                *(float *)&igi2_frame.aptGear.vY = ((7577.60009765625 - p_vDistance[30]) * 0.0001319678995059803 + 1.0)
                                      * *(float *)(*(_DWORD *)&ptQTask[12].eQTaskType + 8)
                                      * 17.840354919433594;
                igi2_frame.vMaxHardCollisionDistanceb = 7577.6 - p_vDistance[30];
                if ( v14 < igi2_frame.vMaxHardCollisionDistanceb )
                  v14 = igi2_frame.vMaxHardCollisionDistanceb;
                igi2_frame.isHardContact = 1;
              }
              HIDWORD(igi2_frame.aptGear.vY) = LODWORD(v16[1].vX);
              v25 = v16[1].vZ;
              *(float *)&igi2_frame.aptGear.vZ = v16[1].vY;
              v26 = ptQTask[10].tQTaskChildren.ptMiddle;
              *((float *)&igi2_frame.aptGear.vZ + 1) = v25;
              qmemcpy((char *)ptQTask[10].ptPrev + 24 * (_DWORD)v26, &igi2_frame.aptGear, 0x18u);
              ++*(int *)&ptQTask[10].tQTaskChildren.ptMiddle;
              v15 = igi2_frame.iTracePosa;
              *(float *)&ptQTask[8].tQTaskRefList.ptMiddle = *(float *)&ptQTask[47].tQTaskRefList.ptMiddle
                                                           * *(float *)&ptQTask[8].tQTaskRefList.ptMiddle
                                                           * 0.800000011920929;
              *(float *)&ptQTask[8].tQTaskRefList.ptTail = *(float *)&ptQTask[47].tQTaskRefList.ptMiddle
                                                         * *(float *)&ptQTask[8].tQTaskRefList.ptTail
                                                         * 0.800000011920929;
              *(float *)&ptQTask[9].tQTaskChildren.ptHead = *(float *)&ptQTask[9].tQTaskChildren.ptHead * 0.9800000190734863;
              *(float *)&ptQTask[9].tQTaskChildren.ptMiddle = *(float *)&ptQTask[9].tQTaskChildren.ptMiddle * 0.9800000190734863;
              *(float *)&ptQTask[9].tQTaskChildren.ptTail = *(float *)&ptQTask[9].tQTaskChildren.ptTail * 0.9800000190734863;
            }
          }
          if ( *((_DWORD *)p_vDistance + 89) )
          {
            v27 = igi2_frame.avTraceLength[v15 + 3];
            if ( v27 < 0.0 )
              v27 = -v27;
            if ( v27 >= p_vDistance[45] )
            {
              igi2_frame.aptGear.vX = 0.0;
              if ( p_vDistance[45] >= 7577.6 )
              {
                *(float *)&igi2_frame.aptGear.vY = (8192.0 - p_vDistance[45])
                                      * 0.0016276041666666667
                                      * *(float *)(*(_DWORD *)&ptQTask[12].eQTaskType + 8)
                                      * 17.840354919433594;
              }
              else
              {
                *(float *)&igi2_frame.aptGear.vY = ((7577.60009765625 - p_vDistance[45]) * 0.0001319678995059803 + 1.0)
                                      * *(float *)(*(_DWORD *)&ptQTask[12].eQTaskType + 8)
                                      * 17.840354919433594;
                igi2_frame.vMaxHardCollisionDistancec = 7577.6 - p_vDistance[45];
                if ( v14 < igi2_frame.vMaxHardCollisionDistancec )
                  v14 = igi2_frame.vMaxHardCollisionDistancec;
                igi2_frame.isHardContact = 1;
              }
              HIDWORD(igi2_frame.aptGear.vY) = LODWORD(v16[2].vX);
              v28 = v16[2].vY;
              HIDWORD(igi2_frame.aptGear.vZ) = LODWORD(v16[2].vZ);
              v29 = ptQTask[10].tQTaskChildren.ptMiddle;
              *(float *)&igi2_frame.aptGear.vZ = v28;
              qmemcpy((char *)ptQTask[10].ptPrev + 24 * (_DWORD)v29, &igi2_frame.aptGear, 0x18u);
              ++*(int *)&ptQTask[10].tQTaskChildren.ptMiddle;
              v15 = igi2_frame.iTracePosa;
              *(float *)&ptQTask[8].tQTaskRefList.ptMiddle = *(float *)&ptQTask[47].tQTaskRefList.ptMiddle
                                                           * *(float *)&ptQTask[8].tQTaskRefList.ptMiddle
                                                           * 0.800000011920929;
              *(float *)&ptQTask[8].tQTaskRefList.ptTail = *(float *)&ptQTask[47].tQTaskRefList.ptMiddle
                                                         * *(float *)&ptQTask[8].tQTaskRefList.ptTail
                                                         * 0.800000011920929;
              *(float *)&ptQTask[9].tQTaskChildren.ptHead = *(float *)&ptQTask[9].tQTaskChildren.ptHead * 0.9800000190734863;
              *(float *)&ptQTask[9].tQTaskChildren.ptMiddle = *(float *)&ptQTask[9].tQTaskChildren.ptMiddle * 0.9800000190734863;
              *(float *)&ptQTask[9].tQTaskChildren.ptTail = *(float *)&ptQTask[9].tQTaskChildren.ptTail * 0.9800000190734863;
            }
          }
          v13 = igi2_frame.nTracePos;
          v15 += 4;
          p_vDistance += 60;
          v16 += 4;
          v30 = igi2_frame.v45 + 4 < igi2_frame.nTracePos;
          igi2_frame.iTracePosa = v15;
          igi2_frame.v45 += 4;
        }
        while ( v30 );
      }
      if ( v15 < v13 )
      {
        v31 = &igi2_frame.atForcePos[v15];
        v32 = &igi2_frame.atIntersection[v15].vDistance;
        do
        {
          if ( *((_DWORD *)v32 - 1) )
          {
            v33 = igi2_frame.avTraceLength[v15];
            if ( v33 < 0.0 )
              v33 = -v33;
            if ( v33 >= *v32 )
            {
              igi2_frame.aptGear.vX = 0.0;
              if ( *v32 >= 7577.6 )
              {
                *(float *)&igi2_frame.aptGear.vY = (8192.0 - *v32)
                                      * 0.0016276041666666667
                                      * *(float *)(*(_DWORD *)&ptQTask[12].eQTaskType + 8)
                                      * 17.840354919433594;
              }
              else
              {
                *(float *)&igi2_frame.aptGear.vY = ((7577.60009765625 - *v32) * 0.0001319678995059803 + 1.0)
                                      * *(float *)(*(_DWORD *)&ptQTask[12].eQTaskType + 8)
                                      * 17.840354919433594;
                igi2_frame.vMaxHardCollisionDistanced = 7577.6 - *v32;
                if ( v14 < igi2_frame.vMaxHardCollisionDistanced )
                  v14 = igi2_frame.vMaxHardCollisionDistanced;
                igi2_frame.isHardContact = 1;
              }
              HIDWORD(igi2_frame.aptGear.vY) = LODWORD(v31->vX);
              v34 = v31->vY;
              HIDWORD(igi2_frame.aptGear.vZ) = LODWORD(v31->vZ);
              v35 = ptQTask[10].tQTaskChildren.ptMiddle;
              *(float *)&igi2_frame.aptGear.vZ = v34;
              qmemcpy((char *)ptQTask[10].ptPrev + 24 * (_DWORD)v35, &igi2_frame.aptGear, 0x18u);
              ++*(int *)&ptQTask[10].tQTaskChildren.ptMiddle;
              v15 = igi2_frame.iTracePosa;
              *(float *)&ptQTask[8].tQTaskRefList.ptMiddle = *(float *)&ptQTask[47].tQTaskRefList.ptMiddle
                                                           * *(float *)&ptQTask[8].tQTaskRefList.ptMiddle
                                                           * 0.800000011920929;
              *(float *)&ptQTask[8].tQTaskRefList.ptTail = *(float *)&ptQTask[47].tQTaskRefList.ptMiddle
                                                         * *(float *)&ptQTask[8].tQTaskRefList.ptTail
                                                         * 0.800000011920929;
              *(float *)&ptQTask[9].tQTaskChildren.ptHead = *(float *)&ptQTask[9].tQTaskChildren.ptHead * 0.9800000190734863;
              *(float *)&ptQTask[9].tQTaskChildren.ptMiddle = *(float *)&ptQTask[9].tQTaskChildren.ptMiddle * 0.9800000190734863;
              *(float *)&ptQTask[9].tQTaskChildren.ptTail = *(float *)&ptQTask[9].tQTaskChildren.ptTail * 0.9800000190734863;
            }
          }
          ++v15;
          v32 += 15;
          ++v31;
          igi2_frame.iTracePosa = v15;
        }
        while ( v15 < igi2_frame.nTracePos );
      }
      if ( igi2_frame.isHardContact )
      {
        qmemcpy(&igi2_frame.aptGear, &ptQTask[1], sizeof(igi2_frame.aptGear));
        igi2_frame.aptGear.vZ = igi2_frame.aptGear.vZ + v14;
        if ( *(float *)&ptQTask[6].tQTaskChildren.ptHead <= (double)*(float *)&ptQTask[6].tQTaskChildren.ptMiddle )
          v36 = *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
        else
          v36 = *(float *)&ptQTask[6].tQTaskChildren.ptHead;
        if ( v36 >= *(float *)&ptQTask[6].ptPrev )
        {
          if ( *(float *)&ptQTask[6].tQTaskChildren.ptHead <= (double)*(float *)&ptQTask[6].tQTaskChildren.ptMiddle )
            v37 = *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
          else
            v37 = *(float *)&ptQTask[6].tQTaskChildren.ptHead;
        }
        else
        {
          v37 = *(float *)&ptQTask[6].ptPrev;
        }
        v38 = *(int **)&ptQTask[2].eQTaskType;
        if ( v38 && (v39 = *v38) != 0 )
          v40 = *(float *)(*(_DWORD *)(*(_DWORD *)(v39 + 12) + 12) + 120);
        else
          v40 = 1.0;
        igi2_frame.ptDynCubeObj = v37 * v40;
        World_MoveDynCubeObjRadius(Game_ptGame->ptWorld, (struct DynCubeObj_s *)ptQTask, &igi2_frame.aptGear, igi2_frame.ptDynCubeObj);
      }
    }
  }
}

// source: j/0/vehicles/plane.c:350  [anchor-mhash]
struct Plane_s *__cdecl Plane_InitWings(struct Plane_s *ptPlane)
{
  char *pxData; // edx
  struct Wing_t *atWing; // ebp
  char *v3; // ebx
  double v4; // st7
  float vZ; // ebx
  double v6; // st6
  float vX; // ebp
  float v8; // ecx
  int iWing; // [esp+10h] [ebp-4h]

  pxData = (char *)ptPlane->tVehicle.tPhysicsObj.ptType->pxData;
  iWing = 0;
  if ( *((int *)pxData + 10) > 0 )
  {
    atWing = ptPlane->atWing;
    v3 = pxData + 44;
    do
    {
      qmemcpy(atWing, v3, sizeof(struct Wing_t));
      v3 += 28;
      ++atWing;
      ++iWing;
    }
    while ( iWing < (int)(*((_DWORD *)pxData + 10)) );
  }
  v4 = ptPlane->atWing[2].vArea * 0.5;
  ptPlane->atWing[3].tNormal.vX = ptPlane->atWing[2].tNormal.vX;
  ptPlane->atWing[3].vArea = v4;
  vZ = ptPlane->atWing[2].tNormal.vZ;
  v6 = -ptPlane->atWing[2].tPos.vY;
  ptPlane->atWing[3].tNormal.vY = ptPlane->atWing[2].tNormal.vY;
  ptPlane->atWing[3].tPos.vY = v6;
  vX = ptPlane->atWing[2].tNormal.vX;
  ptPlane->atWing[3].tNormal.vZ = vZ;
  ptPlane->atWing[4].vArea = v4;
  ptPlane->atWing[3].tPos.vZ = ptPlane->atWing[2].tPos.vZ;
  ptPlane->atWing[4].tPos.vY = v6;
  ptPlane->atWing[4].tNormal.vX = vX;
  v8 = ptPlane->atWing[2].tNormal.vZ;
  ptPlane->atWing[4].tNormal.vY = ptPlane->atWing[2].tNormal.vY;
  ptPlane->atWing[4].tNormal.vZ = v8;
  ptPlane->atWing[4].tPos.vZ = ptPlane->atWing[2].tPos.vZ;
  ptPlane->atWing[3].tPos.vX = 16384.0;
  ptPlane->atWing[4].tPos.vX = -16384.0;
  qmemcpy(pxData + 128, &ptPlane->atWing[3], 0x1Cu);
  qmemcpy(pxData + 156, &ptPlane->atWing[4], 0x1Cu);
  return ptPlane;
}

// source: j/0/vehicles/plane.c:397  [anchor-callee]
struct Plane_s *__cdecl Plane_InitParameters(struct Plane_s *ptPlane)
{
  struct PhysicsObjType_s *ptType; // edx
  char isOriginalGearOut; // cl

  ptType = ptPlane->tVehicle.tPhysicsObj.ptType;
  ptPlane->isCockpitShieldUp = ptPlane->isOriginalCockpitShieldUp;
  isOriginalGearOut = ptPlane->isOriginalGearOut;
  ptPlane->isGearOut = isOriginalGearOut;
  ptPlane->nGearState = isOriginalGearOut;
  ptPlane->nHatchState = isOriginalGearOut;
  ptPlane->tVehicle.isBreak = 0;
  ptPlane->isCatapult = 0;
  ptPlane->isForceZ = 0;
  if ( ptType )
    return Plane_InitWings(ptPlane);
  return ptPlane;
}

// source: j/0/vehicles/plane.c:422  [anchor-mhash]
void __cdecl Plane_Init(struct QTask_s *ptQTask)
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
  struct QTask_s *v6; // eax

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
  v6 = (struct QTask_s *)Mem_AllocFn(12, 4);
  if ( v6 )
  {
    v6->ptNext = (struct QTask_s *)2;
    v6->ptPrev = nullptr;
    v6->tQTaskChildren.ptHead = nullptr;
  }
  ptQTask[54].tQTaskChildren.ptHead = v6;
  ptQTask[54].tQTaskRefList.ptHead = nullptr;
  LOBYTE(ptQTask[10].tQTaskRefList.ptHead) = 0;
  Vehicle_Create((struct Vehicle_s *)ptQTask);
  ptQTask[48].tQTaskChildren.ptTail = (struct QTask_s *)1065353216;
  LOBYTE(ptQTask[54].tQTaskChildren.ptTail) = 0;
  BYTE1(ptQTask[54].tQTaskChildren.ptTail) = 1;
  Plane_InitParameters((struct Plane_s *)ptQTask);
}

// source: j/0/vehicles/plane.c:480  [anchor-mhash]
void __cdecl Plane_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  Plane_Init(ptQTask);
  ptQTask[54].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[54].tQTaskRefList.ptTail = nullptr;
  ptQTask[54].ptParent = nullptr;
  ptQTask[56].tQTaskRefList.ptHead = nullptr;
}

// source: j/0/vehicles/plane.c:500  [anchor-mhash]
void __cdecl Plane_RunHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *v1; // eax
  struct QTask_s *ptHead; // ecx
  int v3; // edx
  struct QTask_s *v4; // eax
  void (__cdecl *pfHandler)(struct QTask_s *); // eax
  int v6; // edx

  if ( ptQTask[54].tQTaskRefList.ptMiddle
    && ptQTask[54].tQTaskRefList.ptTail->ptNext
    && ptQTask[54].ptParent
    && !(unsigned int)(__int64)Level_RunLevelExpression(
                                 (struct LevelExpression_s *)&ptQTask[54].tQTaskRefList.ptMiddle,
                                 ptQTask) )
  {
    QTask_DeleteQTaskAndQTaskRefSafe(&ptQTask[54].tQTaskRefList.ptHead);
  }
  else if ( !ptQTask[54].tQTaskRefList.ptHead )
  {
    v1 = SoundSys_NewSoundFn(ptQTask, "su27");
    if ( v1 )
      ptQTask[54].tQTaskRefList.ptHead = QTask_NewQTaskRef(v1);
  }
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
      pfHandler = (void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[1][ptHead->eQTaskType].pfHandler;
      v6 = v3 + 1;
      QTask_nProtectedQTaskStackOffset = v6;
      if ( pfHandler )
      {
        pfHandler(ptHead);
        v6 = QTask_nProtectedQTaskStackOffset;
      }
      ptHead = (struct QTask_s *)dword_849C7DC[v6];
      v3 = v6 - 1;
      QTask_nProtectedQTaskStackOffset = v3;
    }
    while ( ptHead );
  }
}

// source: j/0/vehicles/plane.c:550  [anchor-mhash]
void __cdecl Plane_DeleteHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptHead; // eax
  int v2; // esi

  if ( ptQTask[3].ptNext )
  {
    QTask_Delete(ptQTask[3].ptNext);
    ptQTask[3].ptNext = nullptr;
  }
  *(_DWORD *)&ptQTask[12].eQTaskType = 0;
  Physics_DeAlloc((struct Physics_s *)&ptQTask[8]);
  World_RemoveDynCubeObj(Game_ptGame->ptWorld, (struct DynCubeObj_s *)ptQTask);
  ptHead = ptQTask[54].tQTaskChildren.ptHead;
  if ( ptHead )
  {
    v2 = *(_DWORD *)((unsigned int)&ptHead[-1].eQTaskType & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v2);
    memset(*(void **)(v2 + 8), 0xCDu, *(_DWORD *)(v2 + 16));
    free((void *)v2);
  }
  Level_DeinitLevelExpression((struct LevelExpression_s *)&ptQTask[54].tQTaskRefList.ptMiddle);
  QTask_DeleteQTaskAndQTaskRefSafe(&ptQTask[54].tQTaskRefList.ptHead);
}

// source: j/0/vehicles/plane.c:587  [size]
void __cdecl Plane_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = Plane_ptParameterList;
}

// source: j/0/vehicles/plane.c:603  [anchor-caller]
void __cdecl Plane_Move(struct Plane_s *ptPlane)
{
  #pragma pack(push, 1)
  union
  {
    struct { float vBetaInertia; };
    struct { float vBetaInertiaa; };
    struct { char igi2_o2[4]; float vGammaInertia[2]; };
    struct { char igi2_o3[12]; struct real32x3_t tWindVelocity; };
    struct { char igi2_o4[24]; struct real32x9_t tFlaps1; };
    char igi2_extent[64];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct PhysicsObjType_s *ptType; // edx
  void *pxData; // ebx
  double v4; // st7
  int v5; // eax
  char *p_isActive; // esi
  double vRealThrust; // st6
  float v8; // eax
  float v9; // ecx
  double vIdealDeltaAlpha; // st6
  double v11; // rt1
  double vIdealDeltaBeta; // st6
  double vIdealDeltaGamma; // st6
  double v14; // st7
  double v15; // st7
  double v16; // st6
  long double v17; // st5
  long double v18; // st7
  long double v19; // rt2
  long double v20; // st6
  double v21; // st4
  double v22; // st3
  double v23; // st2
  long double v24; // rt0
  long double v25; // st6
  struct PointForce_s *v26; // edi
  int nContact; // eax
  double v28; // st7
  long double v29; // st7
  long double v30; // st6
  struct PointForce_s *v31; // edi
  int v32; // ebx
  float vY; // eax
  float vZ; // ecx
  struct QTask_s *ptMagicObjContainer; // eax
  int ptHead; // ecx
  int v37; // edx
  struct QTask_s *v38; // eax
  int v39; // esi
  void (__cdecl *pfHandler)(int, struct real32x3_t *); // eax
  int v41; // edx
  struct SoundSysChannelList_t *ptChannelList; // eax
  float ptPlanea = *(float *)&ptPlane; // [esp+54h] [ebp+4h] ARGSLOT
  float ptPlanee = *(float *)&ptPlane; // [esp+54h] [ebp+4h] ARGSLOT
  float ptPlaneb = *(float *)&ptPlane; // [esp+54h] [ebp+4h] ARGSLOT
  float ptPlanec = *(float *)&ptPlane; // [esp+54h] [ebp+4h] ARGSLOT
  float ptPlanef = *(float *)&ptPlane; // [esp+54h] [ebp+4h] ARGSLOT
  float ptPlaned = *(float *)&ptPlane; // [esp+54h] [ebp+4h] ARGSLOT

  ptType = ptPlane->tVehicle.tPhysicsObj.ptType;
  pxData = ptType->pxData;
  v4 = ptPlane->tVehicle.tPhysicsObj.tPhysics.vCMSpeed / (*((float *)pxData + 7) * 37.925926208496094);
  if ( v4 >= 0.0 )
  {
    if ( v4 > 1.0 )
      v4 = 1.0;
  }
  else
  {
    v4 = 0.0;
  }
  v5 = 0;
  if ( ptType->nCollPoint > 0 )
  {
    p_isActive = &ptPlane->tVehicle.tPhysicsObj.atCollPoint[0].isActive;
    do
    {
      *p_isActive = ptPlane->isGearOut == 0;
      ++v5;
      p_isActive += 56;
    }
    while ( v5 < ptType->nCollPoint );
  }
  if ( ptPlane->tVehicle.vRealThrust >= 0.800000011920929 )
    igi2_frame.vBetaInertia = *((float *)pxData + 8);
  else
    igi2_frame.vBetaInertia = *((float *)pxData + 9);
  vRealThrust = ptPlane->tVehicle.vRealThrust;
  if ( ptPlane->tVehicle.tPhysicsObj.nContact && ptPlane->tVehicle.vIdealThrust < 1.0 )
    ptPlanea = ptPlane->tVehicle.vIdealThrust - 0.6000000238418579;
  else
    ptPlanea = ptPlane->tVehicle.vIdealThrust;
  if ( vRealThrust < ptPlanea )
  {
    vRealThrust = vRealThrust + igi2_frame.vBetaInertia;
    if ( vRealThrust <= ptPlanea )
      goto LABEL_21;
    goto LABEL_20;
  }
  if ( vRealThrust > ptPlanea )
  {
    vRealThrust = vRealThrust - igi2_frame.vBetaInertia;
    if ( vRealThrust < ptPlanea )
LABEL_20:
      vRealThrust = ptPlanea;
  }
LABEL_21:
  if ( vRealThrust < 0.0010000000474974513 )
    vRealThrust = 0.0;
  v8 = *((float *)pxData + 4);
  ptPlanee = *((float *)pxData + 2);
  v9 = *((float *)pxData + 6);
  ptPlane->tVehicle.vRealThrust = vRealThrust;
  vIdealDeltaAlpha = ptPlane->tVehicle.vIdealDeltaAlpha;
  igi2_frame.vGammaInertia[0] = v9;
  v11 = 0.9950000047683716 - v4 * 0.0008299999753944576;
  ptPlaneb = (vIdealDeltaAlpha * (1.0 - ptPlanee) + ptPlanee * ptPlane->tVehicle.vRealDeltaAlpha) * v11;
  vIdealDeltaBeta = ptPlane->tVehicle.vIdealDeltaBeta;
  ptPlane->tVehicle.vRealDeltaAlpha = ptPlaneb;
  igi2_frame.vBetaInertiaa = (vIdealDeltaBeta * (1.0 - v8) + v8 * ptPlane->tVehicle.vRealDeltaBeta) * v11;
  vIdealDeltaGamma = ptPlane->tVehicle.vIdealDeltaGamma;
  ptPlane->tVehicle.vRealDeltaBeta = igi2_frame.vBetaInertiaa;
  v14 = v11 * (vIdealDeltaGamma * (1.0 - igi2_frame.vGammaInertia[0]) + igi2_frame.vGammaInertia[0] * ptPlane->tVehicle.vRealDeltaGamma);
  ptPlane->tVehicle.vRealDeltaGamma = v14;
  if ( (ptPlaneb != 0.0 || igi2_frame.vBetaInertiaa != 0.0 || v14 != 0.0)
    && (!ptPlane->tVehicle.tPhysicsObj.nContact || ptPlane->tVehicle.tPhysicsObj.tPhysics.vCMSpeed >= 10.0) )
  {
    v15 = ptPlaneb * *((float *)pxData + 1) * 0.008726646192371845;
    v16 = igi2_frame.vBetaInertiaa * *((float *)pxData + 3) * 0.008726646192371845;
    v17 = -(v16 + v15);
    if ( v17 >= *((float *)pxData + 1) )
      v17 = *((float *)pxData + 1);
    igi2_frame.vGammaInertia[0] = sin(v17);
    ptPlanec = cos(v17);
    igi2_frame.tFlaps1.tY.vZ = -igi2_frame.vGammaInertia[0];
    v18 = v16 - v15;
    if ( v18 >= *((float *)pxData + 1) )
      v18 = *((float *)pxData + 1);
    v19 = sin(v18);
    v20 = cos(v18);
    igi2_frame.tWindVelocity.vX = (*((float *)pxData + 35) + *((float *)pxData + 34)) * 0.0 + *((float *)pxData + 33);
    v21 = *((float *)pxData + 33) * 0.0;
    igi2_frame.tWindVelocity.vY = ptPlanec * *((float *)pxData + 34) + igi2_frame.tFlaps1.tY.vZ * *((float *)pxData + 35) + v21;
    v22 = ptPlanec * *((float *)pxData + 35);
    v23 = igi2_frame.vGammaInertia[0] * *((float *)pxData + 34);
    ptPlane->atWing[3].tNormal.vX = igi2_frame.tWindVelocity.vX;
    ptPlane->atWing[3].tNormal.vY = igi2_frame.tWindVelocity.vY;
    igi2_frame.tWindVelocity.vZ = v22 + v23 + v21;
    ptPlane->atWing[3].tNormal.vZ = igi2_frame.tWindVelocity.vZ;
    igi2_frame.tWindVelocity.vX = (*((float *)pxData + 42) + *((float *)pxData + 41)) * 0.0 + *((float *)pxData + 40);
    ptPlanef = *((float *)pxData + 40) * 0.0;
    igi2_frame.tWindVelocity.vY = v20 * *((float *)pxData + 41) + -v19 * *((float *)pxData + 42) + ptPlanef;
    v24 = v20 * *((float *)pxData + 42);
    v25 = v19 * *((float *)pxData + 41);
    ptPlane->atWing[4].tNormal.vX = igi2_frame.tWindVelocity.vX;
    ptPlane->atWing[4].tNormal.vY = igi2_frame.tWindVelocity.vY;
    igi2_frame.tWindVelocity.vZ = v24 + v25 + ptPlanef;
    ptPlane->atWing[4].tNormal.vZ = igi2_frame.tWindVelocity.vZ;
  }
  if ( ptPlane->tVehicle.isBreak )
  {
    ptPlane->atWing[1].vArea = *((float *)pxData + 18) * 3.0;
    ptPlane->atWing[3].vArea = *((float *)pxData + 25) * 0.375;
    ptPlane->atWing[4].vArea = *((float *)pxData + 25) * 0.375;
    ptPlane->atWing[2].vArea = *((float *)pxData + 25) * 0.75;
  }
  else
  {
    ptPlane->atWing[1].vArea = *((float *)pxData + 18);
    ptPlane->atWing[3].vArea = *((float *)pxData + 32);
    ptPlane->atWing[4].vArea = *((float *)pxData + 39);
    ptPlane->atWing[2].vArea = *((float *)pxData + 25);
  }
  if ( ptPlane->isCatapult )
  {
    v26 = &ptPlane->tVehicle.tPhysicsObj.tPhysics.ptForces[ptPlane->tVehicle.tPhysicsObj.tPhysics.nForces];
    igi2_frame.tFlaps1.tX.vY = ptType->vMass * 6489.42919921875;
    igi2_frame.tFlaps1.tX.vX = 0.0;
    memset(&igi2_frame.tFlaps1.tX.vZ, 0, 16);
    qmemcpy(v26, &igi2_frame.tFlaps1, sizeof(struct PointForce_s));
    ++ptPlane->tVehicle.tPhysicsObj.tPhysics.nForces;
  }
  if ( ptPlane->tVehicle.vRealThrust != 0.0 )
  {
    nContact = ptPlane->tVehicle.tPhysicsObj.nContact;
    v28 = *((float *)pxData + 5) * ptPlane->tVehicle.vRealDeltaGamma;
    igi2_frame.tFlaps1.tX.vX = 0.0;
    igi2_frame.tFlaps1.tX.vZ = 0.0;
    ptPlaned = v28 * 0.008726646259971651;
    igi2_frame.tFlaps1.tX.vY = ptType->vMass * ptPlane->tVehicle.vRealThrust * 44.600887298583984;
    if ( !nContact )
    {
      v29 = sin(ptPlaned);
      v30 = cos(ptPlaned);
      igi2_frame.tWindVelocity.vX = -v29 * igi2_frame.tFlaps1.tX.vY + v30 * 0.0;
      igi2_frame.tWindVelocity.vY = v30 * igi2_frame.tFlaps1.tX.vY + v29 * 0.0;
      igi2_frame.tWindVelocity.vZ = igi2_frame.tFlaps1.tX.vY * 0.0;
      igi2_frame.tFlaps1.tX = igi2_frame.tWindVelocity;
    }
    v31 = &ptPlane->tVehicle.tPhysicsObj.tPhysics.ptForces[ptPlane->tVehicle.tPhysicsObj.tPhysics.nForces];
    igi2_frame.tFlaps1.tY.vX = 0.0;
    igi2_frame.tFlaps1.tY.vY = 40960.0;
    igi2_frame.tFlaps1.tY.vZ = 0.0;
    qmemcpy(v31, &igi2_frame.tFlaps1, sizeof(struct PointForce_s));
    ++ptPlane->tVehicle.tPhysicsObj.tPhysics.nForces;
  }
  Plane_AddWheelForces(&ptPlane->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask);
  if ( !PhysicsObj_IsIdle(&ptPlane->tVehicle.tPhysicsObj) )
  {
    v32 = *((_DWORD *)pxData + 10);
    LODWORD(igi2_frame.vGammaInertia[1]) = ptPlane;
    if ( v32 && (!ptPlane->tVehicle.tPhysicsObj.nContact || ptPlane->tVehicle.tPhysicsObj.tPhysics.vCMSpeed > 1137.77783203125) )
    {
      igi2_frame.tWindVelocity.vX = ptPlane->tVehicle.tPhysicsObj.tPhysics.tCMVel.vX;
      vY = ptPlane->tVehicle.tPhysicsObj.tPhysics.tCMVel.vY;
      vZ = ptPlane->tVehicle.tPhysicsObj.tPhysics.tCMVel.vZ;
      igi2_frame.tWindVelocity.vX = -igi2_frame.tWindVelocity.vX;
      igi2_frame.tWindVelocity.vY = -vY;
      igi2_frame.tWindVelocity.vZ = -vZ;
      Wing_ApplyAirResistance(
        ptPlane->atWing,
        v32,
        0.00032699998700991273,
        &ptPlane->tVehicle.tPhysicsObj.tPhysics,
        &ptPlane->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation,
        &igi2_frame.tWindVelocity);
    }
    PhysicsObj_Update(
      &ptPlane->tVehicle.tPhysicsObj,
      44.600887298583984,
      1.0,
      0.9200000166893005,
      Game_ptGame->ptWorld,
      13,
      igi2_frame.vGammaInertia);
  }
  ptMagicObjContainer = ptPlane->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.ptMagicObjContainer;
  if ( ptMagicObjContainer )
  {
    LODWORD(igi2_frame.tWindVelocity.vX) = &ptPlane->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos;
    LODWORD(igi2_frame.tWindVelocity.vY) = &ptPlane->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation;
    LODWORD(igi2_frame.tWindVelocity.vZ) = ptPlane;
    ptHead = (int)ptMagicObjContainer->tQTaskChildren.ptHead;
    if ( *(_DWORD *)ptHead )
    {
      if ( ptHead )
      {
        v37 = QTask_nProtectedQTaskStackOffset;
        do
        {
          if ( *(_DWORD *)ptHead )
            v38 = **(_DWORD **)ptHead != 0 ? *(struct QTask_s **)ptHead : nullptr;
          else
            v38 = nullptr;
          v39 = MagicObj_eUpdateMagicObjEvent;
          QTask_atProtectedQTaskStack[v37].ptQTask = v38;
          pfHandler = (void (__cdecl *)(int, struct real32x3_t *))QTask_aatQTaskFinalEvent[v39][*(unsigned __int16 *)(ptHead + 36)].pfHandler;
          v41 = v37 + 1;
          QTask_nProtectedQTaskStackOffset = v41;
          if ( pfHandler )
          {
            pfHandler(ptHead, &igi2_frame.tWindVelocity);
            v41 = QTask_nProtectedQTaskStackOffset;
          }
          ptHead = dword_849C7DC[v41];
          v37 = v41 - 1;
          QTask_nProtectedQTaskStackOffset = v37;
        }
        while ( ptHead );
      }
    }
  }
  ptChannelList = ptPlane->ptChannelList;
  if ( ptChannelList )
  {
    ptChannelList->auData[0].vChannelData = ptPlane->tVehicle.vRealThrust;
    ptPlane->ptChannelList->auData[1].vChannelData = (float)(ptPlane->tVehicle.vRealThrust > 0.009999999776482582);
  }
}

// source: j/0/vehicles/plane.c:897  [anchor-caller]
void __cdecl Plane_UpdateAnimDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { float ptDynCubeObj; };
    struct { char igi2_o1[20]; struct real32x3_t Real32x3_Rotate_tTemp; };
    char igi2_extent[40];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *v2; // edx
  int v3; // eax
  int v4; // eax
  int v5; // eax
  bool v6; // cc
  double v7; // st7
  double v8; // st7
  int *v9; // eax
  int v10; // eax
  double v11; // st6
  struct PhysicsObjType_s *v12; // eax
  struct QTask_s *ptTail; // ecx
  struct QTask_s *ptNext; // eax
  struct QTask_s *v15; // eax
  struct Physics_s *v16; // eax
  float *p_ptMiddle; // ecx
  double v18; // st7
  double v19; // st6
  double v20; // st7
  double v21; // st6
  float vZ; // edx
  struct QTask_s *v23; // eax
  int ptHead; // ecx
  int v25; // edx
  struct QTask_s *v26; // eax
  void (__cdecl *pfHandler)(int, struct real32x3_t *); // eax
  int v28; // edx
  struct QTask_s *v29; // ebx

  v2 = *(struct QTask_s **)(*((_DWORD *)pxContext + 1) + 12);
  if ( v2 != (struct QTask_s *)-1082130432 )
    ptQTask[48].ptNext = v2;
  ptQTask[48].ptPrev = **((struct QTask_s ***)pxContext + 1);
  ptQTask[48].tQTaskChildren.ptHead = *(struct QTask_s **)(*((_DWORD *)pxContext + 1) + 4);
  ptQTask[48].tQTaskChildren.ptMiddle = *(struct QTask_s **)(*((_DWORD *)pxContext + 1) + 8);
  v3 = *((_DWORD *)pxContext + 1);
  if ( *(_DWORD *)(v3 + 20) != -1082130432 )
  {
    *(_QWORD *)&igi2_frame.Real32x3_Rotate_tTemp.vX = (__int64)*(float *)(v3 + 20);
    LOBYTE(ptQTask[54].tQTaskChildren.ptMiddle) ^= LOBYTE(igi2_frame.Real32x3_Rotate_tTemp.vX);
  }
  v4 = *((_DWORD *)pxContext + 1);
  if ( *(_DWORD *)(v4 + 24) != -1082130432 )
  {
    *(_QWORD *)&igi2_frame.Real32x3_Rotate_tTemp.vX = (__int64)*(float *)(v4 + 24);
    BYTE1(ptQTask[54].tQTaskChildren.ptMiddle) ^= LOBYTE(igi2_frame.Real32x3_Rotate_tTemp.vX);
  }
  LOBYTE(ptQTask[48].tQTaskRefList.ptHead) = *(float *)(*((_DWORD *)pxContext + 1) + 28) != -1.0;
  BYTE2(ptQTask[54].tQTaskChildren.ptMiddle) = *(float *)(*((_DWORD *)pxContext + 1) + 32) != -1.0;
  v5 = *((_DWORD *)pxContext + 1);
  if ( *(_DWORD *)(v5 + 36) != -1082130432 )
  {
    *(_QWORD *)&igi2_frame.Real32x3_Rotate_tTemp.vX = (__int64)*(float *)(v5 + 36);
    HIBYTE(ptQTask[54].tQTaskChildren.ptMiddle) ^= LOBYTE(igi2_frame.Real32x3_Rotate_tTemp.vX);
  }
  v6 = (int)(*(_DWORD *)pxContext) <= 0;
  if ( !*(_DWORD *)pxContext )
  {
    if ( *(float *)&ptQTask[6].tQTaskChildren.ptHead <= (double)*(float *)&ptQTask[6].tQTaskChildren.ptMiddle )
      v7 = *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
    else
      v7 = *(float *)&ptQTask[6].tQTaskChildren.ptHead;
    if ( v7 >= *(float *)&ptQTask[6].ptPrev )
    {
      if ( *(float *)&ptQTask[6].tQTaskChildren.ptHead <= (double)*(float *)&ptQTask[6].tQTaskChildren.ptMiddle )
        v8 = *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
      else
        v8 = *(float *)&ptQTask[6].tQTaskChildren.ptHead;
    }
    else
    {
      v8 = *(float *)&ptQTask[6].ptPrev;
    }
    v9 = *(int **)&ptQTask[2].eQTaskType;
    if ( v9 && (v10 = *v9) != 0 )
      v11 = *(float *)(*(_DWORD *)(*(_DWORD *)(v10 + 12) + 12) + 120);
    else
      v11 = 1.0;
    igi2_frame.ptDynCubeObj = v8 * v11;
    World_MoveDynCubeObjRadius(
      Game_ptGame->ptWorld,
      (struct DynCubeObj_s *)ptQTask,
      (struct real64x3_t *)&ptQTask[11],
      igi2_frame.ptDynCubeObj);
    v12 = *(struct PhysicsObjType_s **)&ptQTask[12].eQTaskType;
    qmemcpy(&ptQTask[3].ptPrev, &ptQTask[11].eQTaskType, sizeof(struct QTask_s));
    PhysicsObj_Init(ptQTask, v12);
    ptTail = ptQTask[48].tQTaskChildren.ptTail;
    ptQTask[47].tQTaskRefList.ptMiddle = (struct QReference_s *)ptTail;
    ptNext = ptQTask[3].ptNext;
    ptQTask[47].tQTaskRefList.ptTail = nullptr;
    ptQTask[47].ptParent = nullptr;
    *(_DWORD *)&ptQTask[47].eQTaskType = 0;
    ptQTask[48].ptPrev = nullptr;
    ptQTask[48].tQTaskChildren.ptHead = nullptr;
    ptQTask[48].tQTaskChildren.ptMiddle = nullptr;
    ptQTask[48].ptNext = ptTail;
    if ( ptNext )
    {
      QTask_Delete(ptNext);
      ptQTask[3].ptNext = nullptr;
    }
    v15 = QTask_NewFn(nullptr, MagicObjContainer_eQTaskType, nullptr);
    v15[1].ptNext = ptQTask;
    ptQTask[3].ptNext = v15;
    ModelObj_CreateAttachObjects((struct ModelObj_s *)ptQTask, v15, ptQTask, false, true);
    Plane_InitParameters((struct Plane_s *)ptQTask);
    if ( *(float *)&ptQTask[11].tQTaskRefList.ptMiddle == 0.0
      && *(float *)&ptQTask[11].tQTaskRefList.ptTail == 0.0
      && *(float *)&ptQTask[11].ptParent == 0.0 )
    {
      v16 = (struct Physics_s *)&ptQTask[8];
      p_ptMiddle = (float *)&ptQTask[8].tQTaskRefList.ptMiddle;
      v18 = **(float **)(*(_DWORD *)&ptQTask[12].eQTaskType + 724)
          * *(float *)&ptQTask[47].tQTaskRefList.ptMiddle
          * 30.340740203857422;
      igi2_frame.Real32x3_Rotate_tTemp.vX = (*(float *)&ptQTask[3].tQTaskChildren.ptMiddle + *(float *)&ptQTask[3].ptPrev) * 0.0
                               + v18 * *(float *)&ptQTask[3].tQTaskChildren.ptHead;
      igi2_frame.Real32x3_Rotate_tTemp.vY = (*(float *)&ptQTask[3].tQTaskRefList.ptMiddle
                                + *(float *)&ptQTask[3].tQTaskChildren.ptTail)
                               * 0.0
                               + v18 * *(float *)&ptQTask[3].tQTaskRefList.ptHead;
      v19 = v18;
      v20 = (*(float *)&ptQTask[3].eQTaskType + *(float *)&ptQTask[3].tQTaskRefList.ptTail) * 0.0;
      v21 = v19 * *(float *)&ptQTask[3].ptParent;
      ptQTask[8].tQTaskRefList.ptMiddle = (struct QReference_s *)LODWORD(igi2_frame.Real32x3_Rotate_tTemp.vX);
      ptQTask[8].tQTaskRefList.ptTail = (struct QReference_s *)LODWORD(igi2_frame.Real32x3_Rotate_tTemp.vY);
      igi2_frame.Real32x3_Rotate_tTemp.vZ = v20 + v21;
      vZ = igi2_frame.Real32x3_Rotate_tTemp.vZ;
    }
    else
    {
      v16 = (struct Physics_s *)&ptQTask[8];
      p_ptMiddle = (float *)&ptQTask[8].tQTaskRefList.ptMiddle;
      ptQTask[8].tQTaskRefList.ptMiddle = ptQTask[11].tQTaskRefList.ptMiddle;
      ptQTask[8].tQTaskRefList.ptTail = ptQTask[11].tQTaskRefList.ptTail;
      vZ = *(float *)&ptQTask[11].ptParent;
    }
    p_ptMiddle[2] = vZ;
    Physics_UpdateSpeedApproximation(v16);
    v23 = ptQTask[3].ptNext;
    if ( v23 )
    {
      LODWORD(igi2_frame.Real32x3_Rotate_tTemp.vX) = &ptQTask[1];
      LODWORD(igi2_frame.Real32x3_Rotate_tTemp.vY) = &ptQTask[3].ptPrev;
      LODWORD(igi2_frame.Real32x3_Rotate_tTemp.vZ) = ptQTask;
      ptHead = (int)v23->tQTaskChildren.ptHead;
      if ( *(_DWORD *)ptHead )
      {
        if ( ptHead )
        {
          v25 = QTask_nProtectedQTaskStackOffset;
          do
          {
            if ( *(_DWORD *)ptHead )
              v26 = **(_DWORD **)ptHead != 0 ? *(struct QTask_s **)ptHead : nullptr;
            else
              v26 = nullptr;
            QTask_atProtectedQTaskStack[v25].ptQTask = v26;
            pfHandler = (void (__cdecl *)(int, struct real32x3_t *))QTask_aatQTaskFinalEvent[MagicObj_eUpdateMagicObjEvent][*(unsigned __int16 *)(ptHead + 36)].pfHandler;
            v28 = v25 + 1;
            QTask_nProtectedQTaskStackOffset = v28;
            if ( pfHandler )
            {
              pfHandler(ptHead, &igi2_frame.Real32x3_Rotate_tTemp);
              v28 = QTask_nProtectedQTaskStackOffset;
            }
            ptHead = dword_849C7DC[v28];
            v25 = v28 - 1;
            QTask_nProtectedQTaskStackOffset = v25;
          }
          while ( ptHead );
        }
      }
    }
    v6 = (int)(*(_DWORD *)pxContext) <= 0;
  }
  if ( !v6 )
  {
    Plane_Move((struct Plane_s *)ptQTask);
    v29 = ptQTask[3].ptNext;
    if ( v29 )
      ((void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[1][v29->eQTaskType].pfHandler)(v29);
  }
}

// source: j/0/vehicles/plane.c:1048  [anchor-mhash]
void __cdecl Plane_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { float ptDynCubeObj; };
    struct { char igi2_o1[24]; float Real32x3_Rotate_tTemp; };
    struct { char igi2_o2[28]; float Real32x3_Rotate_tTemp_4; };
    struct { char igi2_o3[32]; float Real32x3_Rotate_tTemp_8; };
    struct { char igi2_o4[36]; char zTempModel[128]; };
    struct { char igi2_o5[164]; char zString[132]; };
    char igi2_extent[296];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  char *p_tQTaskRefList; // edi
  struct LODVirModel_s *LODVirModelExistsFn; // eax
  struct LODVirModel_s *v4; // esi
  struct PhysicsObjType_s *Type; // eax
  char *v6; // eax
  char v7; // cl
  struct QTask_s *ptTail; // ecx
  double v9; // st7
  int v10; // eax
  double v11; // st7
  double v12; // st6
  double v13; // st7
  double v14; // st6
  double v15; // st7
  double v16; // st7
  int *v17; // eax
  int v18; // eax
  double v19; // st6
  unsigned __int16 v20; // ax
  struct QTask_s *v21; // eax
  struct QTask_s *ptHead; // eax
  int v23; // edx
  struct QTask_s *v24; // ecx
  void (__cdecl *pfHandler)(struct QTask_s *, _DWORD); // ecx
  int v26; // edx

  p_tQTaskRefList = (char *)&ptQTask[10].tQTaskRefList;
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
    Type = PhysicsObjType_FindType(p_tQTaskRefList);
    PhysicsObj_Init(ptQTask, Type);
    Plane_InitParameters((struct Plane_s *)ptQTask);
  }
  else if ( *p_tQTaskRefList && BYTE1(ptQTask[10].tQTaskRefList.ptHead) != 42 )
  {
    sprintf(igi2_frame.zString, "Model \"%s\" not available", p_tQTaskRefList);
    v6 = (char *)&ptQTask[10].tQTaskRefList;
    do
    {
      v7 = *v6;
      v6[igi2_frame.zTempModel - p_tQTaskRefList] = *v6;
      ++v6;
    }
    while ( v7 );
    sprintf(p_tQTaskRefList, "** %s **", igi2_frame.zTempModel);
  }
  ptTail = ptQTask[48].tQTaskChildren.ptTail;
  v9 = *(float *)&ptQTask[11].tQTaskRefList.ptMiddle;
  ptQTask[47].tQTaskRefList.ptMiddle = (struct QReference_s *)ptTail;
  ptQTask[48].ptNext = ptTail;
  if ( v9 == 0.0 && *(float *)&ptQTask[11].tQTaskRefList.ptTail == 0.0 && *(float *)&ptQTask[11].ptParent == 0.0 )
  {
    v10 = *(_DWORD *)&ptQTask[12].eQTaskType;
    if ( !v10 )
      goto LABEL_22;
    v11 = *(float *)&ptTail * **(float **)(v10 + 724) * 30.340740203857422;
    igi2_frame.Real32x3_Rotate_tTemp = (*(float *)&ptQTask[3].tQTaskChildren.ptMiddle + *(float *)&ptQTask[3].ptPrev) * 0.0
                          + v11 * *(float *)&ptQTask[3].tQTaskChildren.ptHead;
    igi2_frame.Real32x3_Rotate_tTemp_4 = (*(float *)&ptQTask[3].tQTaskRefList.ptMiddle + *(float *)&ptQTask[3].tQTaskChildren.ptTail)
                            * 0.0
                            + v11 * *(float *)&ptQTask[3].tQTaskRefList.ptHead;
    v12 = v11;
    v13 = (*(float *)&ptQTask[3].eQTaskType + *(float *)&ptQTask[3].tQTaskRefList.ptTail) * 0.0;
    v14 = v12 * *(float *)&ptQTask[3].ptParent;
    *(float *)&ptQTask[8].tQTaskRefList.ptMiddle = igi2_frame.Real32x3_Rotate_tTemp;
    *(float *)&ptQTask[8].tQTaskRefList.ptTail = igi2_frame.Real32x3_Rotate_tTemp_4;
    igi2_frame.Real32x3_Rotate_tTemp_8 = v13 + v14;
    *(float *)&ptQTask[8].ptParent = igi2_frame.Real32x3_Rotate_tTemp_8;
  }
  else
  {
    ptQTask[8].tQTaskRefList.ptMiddle = ptQTask[11].tQTaskRefList.ptMiddle;
    ptQTask[8].tQTaskRefList.ptTail = ptQTask[11].tQTaskRefList.ptTail;
    ptQTask[8].ptParent = ptQTask[11].ptParent;
  }
  Physics_UpdateSpeedApproximation((struct Physics_s *)&ptQTask[8]);
LABEL_22:
  if ( *(float *)&ptQTask[6].tQTaskChildren.ptHead <= (double)*(float *)&ptQTask[6].tQTaskChildren.ptMiddle )
    v15 = *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
  else
    v15 = *(float *)&ptQTask[6].tQTaskChildren.ptHead;
  if ( v15 >= *(float *)&ptQTask[6].ptPrev )
  {
    if ( *(float *)&ptQTask[6].tQTaskChildren.ptHead <= (double)*(float *)&ptQTask[6].tQTaskChildren.ptMiddle )
      v16 = *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
    else
      v16 = *(float *)&ptQTask[6].tQTaskChildren.ptHead;
  }
  else
  {
    v16 = *(float *)&ptQTask[6].ptPrev;
  }
  v17 = *(int **)&ptQTask[2].eQTaskType;
  if ( v17 && (v18 = *v17) != 0 )
    v19 = *(float *)(*(_DWORD *)(*(_DWORD *)(v18 + 12) + 12) + 120);
  else
    v19 = 1.0;
  igi2_frame.ptDynCubeObj = v16 * v19;
  World_MoveDynCubeObjRadius(
    Game_ptGame->ptWorld,
    (struct DynCubeObj_s *)ptQTask,
    (struct real64x3_t *)&ptQTask[11],
    igi2_frame.ptDynCubeObj);
  v20 = MagicObjContainer_eQTaskType;
  qmemcpy(&ptQTask[3].ptPrev, &ptQTask[11].eQTaskType, sizeof(struct QTask_s));
  v21 = QTask_NewFn(nullptr, v20, nullptr);
  v21[1].ptNext = ptQTask;
  ptQTask[3].ptNext = v21;
  ModelObj_CreateAttachObjects((struct ModelObj_s *)ptQTask, v21, ptQTask, false, true);
  ptHead = ptQTask[3].ptNext->tQTaskChildren.ptHead;
  if ( ptHead->ptNext && ptHead )
  {
    v23 = QTask_nProtectedQTaskStackOffset;
    do
    {
      if ( ptHead->ptNext )
        v24 = ptHead->ptNext->ptNext != nullptr ? ptHead->ptNext : nullptr;
      else
        v24 = nullptr;
      QTask_atProtectedQTaskStack[v23].ptQTask = v24;
      pfHandler = (void (__cdecl *)(struct QTask_s *, _DWORD))QTask_aatQTaskFinalEvent[ParameterList_eUpdateInternalDataQTaskEvent][ptHead->eQTaskType].pfHandler;
      v26 = v23 + 1;
      QTask_nProtectedQTaskStackOffset = v26;
      if ( pfHandler )
      {
        pfHandler(ptHead, 0);
        v26 = QTask_nProtectedQTaskStackOffset;
      }
      ptHead = (struct QTask_s *)dword_849C7DC[v26];
      v23 = v26 - 1;
      QTask_nProtectedQTaskStackOffset = v23;
    }
    while ( ptHead );
  }
  Level_CompileLevelExpression((struct LevelExpression_s *)&ptQTask[54].tQTaskRefList.ptMiddle, ptQTask);
}

// source: j/0/vehicles/plane.c:1176  [size]
void __cdecl Plane_SoundUpdateParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = ptQTask + 1;
  *((_DWORD *)pxContext + 1) = 0;
  *((_DWORD *)pxContext + 2) = ptQTask[54].tQTaskChildren.ptHead;
}

// source: j/0/vehicles/plane.c:1200  [size]
void __cdecl Plane_GetKeyframeSizeHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = 120;
}

// source: j/0/vehicles/plane.c:1216  [size]
void __cdecl Plane_GetChannelDescriptionHandler(struct QTask_s *ptQTask, void *pxContext)
{
  int v2; // eax

  v2 = *(_DWORD *)pxContext;
  if ( *(int *)pxContext < 0 || v2 >= 10 )
    *((_DWORD *)pxContext + 1) = 0;
  else
    *((_DWORD *)pxContext + 1) = 16 * v2 + 7044520;
}

// source: j/0/vehicles/plane.c:1245  [anchor-mhash]
void __cdecl Plane_ReadChannelsHandler(struct QTask_s *ptQTask, void *pxContext)
{
  double v2; // st7
  double v3; // st7

  if ( (Keyboard_tKeyboard.anCurrentKey[157] & 0x80u) == 0 && (Keyboard_tKeyboard.anCurrentKey[29] & 0x80) == 0 )
  {
    *(float *)(*(_DWORD *)pxContext + 4) = (float)((Keyboard_tKeyboard.anCurrentKey[205] >> 7)
                                                 - (Keyboard_tKeyboard.anCurrentKey[203] >> 7));
    **(float **)pxContext = (float)((Keyboard_tKeyboard.anCurrentKey[208] >> 7)
                                  - (Keyboard_tKeyboard.anCurrentKey[200] >> 7));
  }
  *(float *)(*(_DWORD *)pxContext + 8) = (float)((Keyboard_tKeyboard.anCurrentKey[45] >> 7)
                                               - (Keyboard_tKeyboard.anCurrentKey[44] >> 7));
  *(_DWORD *)(*(_DWORD *)pxContext + 12) = -1082130432;
  if ( (Keyboard_tKeyboard.anCurrentKey[41] & 0x80) != 0 )
    *(_DWORD *)(*(_DWORD *)pxContext + 12) = 0;
  if ( (Keyboard_tKeyboard.anCurrentKey[2] & 0x80) != 0 )
    *(_DWORD *)(*(_DWORD *)pxContext + 12) = 1061997773;
  if ( (Keyboard_tKeyboard.anCurrentKey[3] & 0x80) != 0 )
    *(_DWORD *)(*(_DWORD *)pxContext + 12) = 1062836634;
  if ( (Keyboard_tKeyboard.anCurrentKey[4] & 0x80) != 0 )
    *(_DWORD *)(*(_DWORD *)pxContext + 12) = 1063675494;
  if ( (Keyboard_tKeyboard.anCurrentKey[5] & 0x80) != 0 )
    *(_DWORD *)(*(_DWORD *)pxContext + 12) = 1064514355;
  if ( (Keyboard_tKeyboard.anCurrentKey[6] & 0x80) != 0 )
    *(_DWORD *)(*(_DWORD *)pxContext + 12) = 1065353216;
  if ( (Keyboard_tKeyboard.anCurrentKey[7] & 0x80) != 0 )
    *(_DWORD *)(*(_DWORD *)pxContext + 12) = 1065772646;
  if ( (Keyboard_tKeyboard.anCurrentKey[8] & 0x80) != 0 )
    *(_DWORD *)(*(_DWORD *)pxContext + 12) = 1066192077;
  if ( (Keyboard_tKeyboard.anCurrentKey[9] & 0x80) != 0 )
    *(_DWORD *)(*(_DWORD *)pxContext + 12) = 1066611507;
  if ( (Keyboard_tKeyboard.anCurrentKey[10] & 0x80) != 0 )
    *(_DWORD *)(*(_DWORD *)pxContext + 12) = 1067030938;
  if ( (Keyboard_tKeyboard.anCurrentKey[11] & 0x80) != 0 )
    *(_DWORD *)(*(_DWORD *)pxContext + 12) = 1067450368;
  if ( (Keyboard_tKeyboard.anCurrentKey[49] & 0x80) != 0 && (Keyboard_tKeyboard.anPreviousKey[49] & 0x80) == 0 )
  {
    v2 = *(float *)&ptQTask[48].ptNext - 0.01;
    if ( v2 < 0.8 )
      v2 = 0.8;
    *(float *)(*(_DWORD *)pxContext + 12) = v2;
  }
  if ( (Keyboard_tKeyboard.anCurrentKey[50] & 0x80) != 0 && (Keyboard_tKeyboard.anPreviousKey[50] & 0x80) == 0 )
  {
    v3 = *(float *)&ptQTask[48].ptNext + 0.01;
    if ( v3 > 1.25 )
      v3 = 1.25;
    *(float *)(*(_DWORD *)pxContext + 12) = v3;
  }
  *(_DWORD *)(*(_DWORD *)pxContext + 20) = -1082130432;
  if ( (Keyboard_tKeyboard.anCurrentKey[46] & 0x80) != 0 && (Keyboard_tKeyboard.anPreviousKey[46] & 0x80) == 0 )
    *(_DWORD *)(*(_DWORD *)pxContext + 20) = 1065353216;
  *(_DWORD *)(*(_DWORD *)pxContext + 24) = -1082130432;
  if ( (Keyboard_tKeyboard.anCurrentKey[34] & 0x80) != 0 && (Keyboard_tKeyboard.anPreviousKey[34] & 0x80) == 0 )
    *(_DWORD *)(*(_DWORD *)pxContext + 24) = 1065353216;
  *(_DWORD *)(*(_DWORD *)pxContext + 28) = -1082130432;
  if ( (Keyboard_tKeyboard.anCurrentKey[48] & 0x80) != 0 )
    *(_DWORD *)(*(_DWORD *)pxContext + 28) = 1065353216;
  *(_DWORD *)(*(_DWORD *)pxContext + 32) = -1082130432;
  if ( (Keyboard_tKeyboard.anCurrentKey[37] & 0x80) != 0 && (Keyboard_tKeyboard.anPreviousKey[37] & 0x80) == 0 )
    *(_DWORD *)(*(_DWORD *)pxContext + 32) = 1065353216;
  *(_DWORD *)(*(_DWORD *)pxContext + 36) = -1082130432;
  if ( (Keyboard_tKeyboard.anCurrentKey[16] & 0x80) != 0 && (Keyboard_tKeyboard.anPreviousKey[16] & 0x80) == 0 )
    *(_DWORD *)(*(_DWORD *)pxContext + 36) = 1065353216;
}

// source: j/0/vehicles/plane.c:1426  [anchor-mhash]
void __cdecl Plane_RestoreKeyframeHandler(struct QTask_s *ptQTask, void *pxContext)
{
  int v2; // esi
  double v3; // st7
  bool v4; // c0
  bool v5; // c3
  double v6; // st7
  double v7; // st7
  int *v8; // eax
  int v9; // eax
  double v10; // st6
  float ptDynCubeObj; // [esp+0h] [ebp-8h]

  v2 = *(_DWORD *)pxContext;
  Vehicle_RestoreKeyframeHandler(ptQTask, pxContext);
  v3 = *(float *)&ptQTask[6].tQTaskChildren.ptHead;
  v4 = v3 < *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
  v5 = v3 == *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
  LOBYTE(ptQTask[54].tQTaskChildren.ptMiddle) = *(_BYTE *)(v2 + 112);
  BYTE1(ptQTask[54].tQTaskChildren.ptMiddle) = *(_BYTE *)(v2 + 113);
  LOBYTE(ptQTask[48].tQTaskRefList.ptHead) = *(_BYTE *)(v2 + 114);
  BYTE2(ptQTask[54].tQTaskChildren.ptMiddle) = *(_BYTE *)(v2 + 115);
  HIBYTE(ptQTask[54].tQTaskChildren.ptMiddle) = *(_BYTE *)(v2 + 116);
  if ( v4 || v5 )
    v6 = *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
  else
    v6 = *(float *)&ptQTask[6].tQTaskChildren.ptHead;
  if ( v6 >= *(float *)&ptQTask[6].ptPrev )
  {
    if ( *(float *)&ptQTask[6].tQTaskChildren.ptHead <= (double)*(float *)&ptQTask[6].tQTaskChildren.ptMiddle )
      v7 = *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
    else
      v7 = *(float *)&ptQTask[6].tQTaskChildren.ptHead;
  }
  else
  {
    v7 = *(float *)&ptQTask[6].ptPrev;
  }
  v8 = *(int **)&ptQTask[2].eQTaskType;
  if ( v8 && (v9 = *v8) != 0 )
    v10 = *(float *)(*(_DWORD *)(*(_DWORD *)(v9 + 12) + 12) + 120);
  else
    v10 = 1.0;
  ptDynCubeObj = v7 * v10;
  World_MoveDynCubeObjRadius(
    Game_ptGame->ptWorld,
    (struct DynCubeObj_s *)ptQTask,
    (struct real64x3_t *)(v2 + 16),
    ptDynCubeObj);
}

// source: j/0/vehicles/plane.c:1476  [anchor-mhash]
void __cdecl Plane_SaveKeyframeHandler(struct QTask_s *ptQTask, void *pxContext)
{
  _BYTE *v2; // esi

  v2 = *(_BYTE **)pxContext;
  Vehicle_SaveKeyframeHandler(ptQTask, pxContext);
  v2[112] = ptQTask[54].tQTaskChildren.ptMiddle;
  v2[113] = BYTE1(ptQTask[54].tQTaskChildren.ptMiddle);
  v2[114] = ptQTask[48].tQTaskRefList.ptHead;
  v2[115] = BYTE2(ptQTask[54].tQTaskChildren.ptMiddle);
  v2[116] = HIBYTE(ptQTask[54].tQTaskChildren.ptMiddle);
}

// source: j/0/vehicles/plane.c:1644  [anchor-strings]
void __cdecl Plane_Open()
{
  unsigned __int16 v0; // si
  __int16 v1; // ax
  struct ParameterList_s *v2; // eax

  v0 = QTask_NewQTaskType("Plane", 2264, Vehicle_eQTaskType, 0, 0);
  Plane_eQTaskType = v0;
  QTask_LinkQTaskEventHandlerFn(v0, 0, Plane_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 1, Plane_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 2, Plane_DeleteHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Plane_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(v0, ParameterList_eUpdateInternalDataQTaskEvent, Plane_UpdateInternalDataHandler);
  v1 = SoundSys_eUpdateParameterListQTaskEvent;
  if ( SoundSys_eUpdateParameterListQTaskEvent == 512 )
  {
    v1 = QTask_NewQTaskEventFn(0, (char *)&g_zFileName.nRealFadeCount);
    v0 = Plane_eQTaskType;
    SoundSys_eUpdateParameterListQTaskEvent = v1;
  }
  QTask_LinkQTaskEventHandlerFn(v0, v1, Plane_SoundUpdateParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(v0, AnimQTask_eUpdateAnimDataEvent, Plane_UpdateAnimDataHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    AnimQTask_eGetChannelDescriptionEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Plane_GetChannelDescriptionHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    AnimQTask_eGetKeyframeSizeEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Plane_GetKeyframeSizeHandler);
  QTask_LinkQTaskEventHandlerFn(v0, AnimQTask_eReadChannelsEvent, Plane_ReadChannelsHandler);
  QTask_LinkQTaskEventHandlerFn(v0, AnimQTask_eRestoreKeyframeEvent, Plane_RestoreKeyframeHandler);
  QTask_LinkQTaskEventHandlerFn(v0, AnimQTask_eSaveKeyframeEvent, Plane_SaveKeyframeHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveHandler);
  v2 = (struct ParameterList_s *)Mem_AllocFn(212, 4);
  v2->ptParameterListItem = (struct ParameterListItem_s *)&v2[1];
  v2->nParameters = 0;
  v2->nMaxParameters = 10;
  Plane_ptParameterList = v2;
  ParameterList_AddParameter(v2, 0x1B8u, Level_eParameterTypeObjectPos, "Position", 7u, nullptr);
  ParameterList_AddParameter(Plane_ptParameterList, 0x1DCu, Level_eParameterTypeReal32x9, "Orientation", 7u, nullptr);
  ParameterList_AddParameter(Plane_ptParameterList, 0x790u, Level_eParameterTypeReal32, "Original Thrust", 7u, nullptr);
  ParameterList_AddParameter(Plane_ptParameterList, 0x1D0u, Level_eParameterTypeReal32x3, "Speed", 7u, nullptr);
  ParameterList_AddParameter(Plane_ptParameterList, 0x1A4u, Level_eParameterTypeString16, "Model", 7u, nullptr);
  ParameterList_AddParameter(Plane_ptParameterList, 0x881u, Level_eParameterTypebool8, "Gear", 7u, nullptr);
  ParameterList_AddParameter(
    Plane_ptParameterList,
    0x880u,
    Level_eParameterTypebool8,
    (char *)&stru_68FBBC.ptParent,
    7u,
    nullptr);
  ParameterList_AddParameter(
    Plane_ptParameterList,
    0x728u,
    Level_eParameterTypebool8,
    "Collision detection",
    7u,
    nullptr);
  ParameterList_AddParameter(Plane_ptParameterList, 0x729u, Level_eParameterTypebool8, "Force Z", 7u, nullptr);
  ParameterList_AddParameter(Plane_ptParameterList, 0x888u, Level_eParameterTypeVarString, "Play sound", 7u, nullptr);
  Symbol_Register(
    (char *)&stru_68FBBC.tQTaskChildren.ptTail,
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)Plane_eQTaskType,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Plane_RandomState.anRandom[0] = -923067897;
  Plane_RandomState.anRandom[1] = 971667286;
  Plane_RandomState.anRandom[2] = 2146516173;
}

// source: j/0/vehicles/plane.c:1708  [size]
void __cdecl Plane_Close()
{
  int v0; // esi

  if ( Plane_ptParameterList )
  {
    v0 = *(_DWORD *)((unsigned int)&Plane_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
  QTask_DeleteQTaskType(Plane_eQTaskType);
}

// source: j/0/vehicles/plane.c:1725  [size]
unsigned __int16 __cdecl Plane_GetQTaskType()
{
  return Plane_eQTaskType;
}
