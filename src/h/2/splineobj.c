/* h/2/splineobj.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: h/2/splineobj.c:135  [anchor-mhash]
void __cdecl SplineObjWaypoint_SetRelativeOrientation(struct SplineObjWaypoint_s *ptSplineObjWaypoint)
{
  struct QTask_s *FirstParentDerivedOfType; // eax
  double v2; // st7
  struct QTask_s *ptTail; // edx
  struct QReference_s *v4; // ecx
  struct QTask_s *ptHead; // edx
  struct QReference_s *v6; // ecx
  struct QTask_s *ptParent; // edx
  struct QTask_s *ptMiddle; // ecx
  struct QReference_s *v9; // edx
  int v10; // ecx
  struct QTask_s *ptNext; // edx
  double v12; // st7
  double v13; // st6
  _BYTE Real64x3_RotateInverse_tTemp[40]; // [esp+8h] [ebp-2Ch] BYREF

  FirstParentDerivedOfType = QTask_GetFirstParentDerivedOfType(
                               ptSplineObjWaypoint->tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask.ptParent,
                               RigidDynCubeObj_eQTaskType);
  if ( FirstParentDerivedOfType )
  {
    ptSplineObjWaypoint->tRelativePos.vX = ptSplineObjWaypoint->tPos.vX - *(double *)&FirstParentDerivedOfType[1].ptNext;
    ptSplineObjWaypoint->tRelativePos.vY = ptSplineObjWaypoint->tPos.vY
                                         - *(double *)&FirstParentDerivedOfType[1].tQTaskChildren.ptHead;
    v2 = ptSplineObjWaypoint->tPos.vZ - *(double *)&FirstParentDerivedOfType[1].tQTaskChildren.ptTail;
    ptSplineObjWaypoint->tRelativePos.vZ = v2;
    *(double *)Real64x3_RotateInverse_tTemp = *(float *)&FirstParentDerivedOfType[3].ptPrev
                                            * ptSplineObjWaypoint->tRelativePos.vX
                                            + *(float *)&FirstParentDerivedOfType[3].tQTaskRefList.ptTail * v2
                                            + *(float *)&FirstParentDerivedOfType[3].tQTaskChildren.ptTail
                                            * ptSplineObjWaypoint->tRelativePos.vY;
    *(double *)&Real64x3_RotateInverse_tTemp[8] = *(float *)&FirstParentDerivedOfType[3].ptParent * v2
                                                + *(float *)&FirstParentDerivedOfType[3].tQTaskChildren.ptHead
                                                * ptSplineObjWaypoint->tRelativePos.vX
                                                + *(float *)&FirstParentDerivedOfType[3].tQTaskRefList.ptHead
                                                * ptSplineObjWaypoint->tRelativePos.vY;
    *(double *)&Real64x3_RotateInverse_tTemp[16] = *(float *)&FirstParentDerivedOfType[3].eQTaskType * v2
                                                 + *(float *)&FirstParentDerivedOfType[3].tQTaskChildren.ptMiddle
                                                 * ptSplineObjWaypoint->tRelativePos.vX
                                                 + *(float *)&FirstParentDerivedOfType[3].tQTaskRefList.ptMiddle
                                                 * ptSplineObjWaypoint->tRelativePos.vY;
    qmemcpy(&ptSplineObjWaypoint->tRelativePos, Real64x3_RotateInverse_tTemp, sizeof(ptSplineObjWaypoint->tRelativePos));
    ptTail = FirstParentDerivedOfType[3].tQTaskChildren.ptTail;
    *(_DWORD *)Real64x3_RotateInverse_tTemp = FirstParentDerivedOfType[3].ptPrev;
    v4 = FirstParentDerivedOfType[3].tQTaskRefList.ptTail;
    *(_DWORD *)&Real64x3_RotateInverse_tTemp[4] = ptTail;
    ptHead = FirstParentDerivedOfType[3].tQTaskChildren.ptHead;
    *(_DWORD *)&Real64x3_RotateInverse_tTemp[8] = v4;
    v6 = FirstParentDerivedOfType[3].tQTaskRefList.ptHead;
    *(_DWORD *)&Real64x3_RotateInverse_tTemp[12] = ptHead;
    ptParent = FirstParentDerivedOfType[3].ptParent;
    *(_DWORD *)&Real64x3_RotateInverse_tTemp[16] = v6;
    ptMiddle = FirstParentDerivedOfType[3].tQTaskChildren.ptMiddle;
    *(_DWORD *)&Real64x3_RotateInverse_tTemp[20] = ptParent;
    v9 = FirstParentDerivedOfType[3].tQTaskRefList.ptMiddle;
    *(_DWORD *)&Real64x3_RotateInverse_tTemp[24] = ptMiddle;
    v10 = *(_DWORD *)&FirstParentDerivedOfType[3].eQTaskType;
    *(_DWORD *)&Real64x3_RotateInverse_tTemp[28] = v9;
    ptNext = FirstParentDerivedOfType[4].ptNext;
    *(_DWORD *)&Real64x3_RotateInverse_tTemp[32] = v10;
    *(_DWORD *)&Real64x3_RotateInverse_tTemp[36] = ptNext;
    qmemcpy(
      &ptSplineObjWaypoint->tRelativeOrientation,
      Real64x3_RotateInverse_tTemp,
      sizeof(ptSplineObjWaypoint->tRelativeOrientation));
    *(float *)Real64x3_RotateInverse_tTemp = ptSplineObjWaypoint->tRelativeOrientation.tZ.vX
                                           * ptSplineObjWaypoint->tOrientation.tX.vZ
                                           + ptSplineObjWaypoint->tOrientation.tX.vY
                                           * ptSplineObjWaypoint->tRelativeOrientation.tY.vX
                                           + ptSplineObjWaypoint->tOrientation.tX.vX
                                           * ptSplineObjWaypoint->tRelativeOrientation.tX.vX;
    v12 = ptSplineObjWaypoint->tRelativeOrientation.tX.vY * ptSplineObjWaypoint->tOrientation.tX.vX
        + ptSplineObjWaypoint->tOrientation.tX.vY * ptSplineObjWaypoint->tRelativeOrientation.tY.vY;
    v13 = ptSplineObjWaypoint->tRelativeOrientation.tZ.vY * ptSplineObjWaypoint->tOrientation.tX.vZ;
    *(_DWORD *)&Real64x3_RotateInverse_tTemp[36] = ptSplineObjWaypoint->tRelativeOrientation.nOps
                                                 + ptSplineObjWaypoint->tOrientation.nOps
                                                 + 1;
    *(float *)&Real64x3_RotateInverse_tTemp[4] = v12 + v13;
    *(float *)&Real64x3_RotateInverse_tTemp[8] = ptSplineObjWaypoint->tRelativeOrientation.tX.vZ
                                               * ptSplineObjWaypoint->tOrientation.tX.vX
                                               + ptSplineObjWaypoint->tOrientation.tX.vY
                                               * ptSplineObjWaypoint->tRelativeOrientation.tY.vZ
                                               + ptSplineObjWaypoint->tRelativeOrientation.tZ.vZ
                                               * ptSplineObjWaypoint->tOrientation.tX.vZ;
    *(float *)&Real64x3_RotateInverse_tTemp[12] = ptSplineObjWaypoint->tRelativeOrientation.tZ.vX
                                                * ptSplineObjWaypoint->tOrientation.tY.vZ
                                                + ptSplineObjWaypoint->tRelativeOrientation.tX.vX
                                                * ptSplineObjWaypoint->tOrientation.tY.vX
                                                + ptSplineObjWaypoint->tRelativeOrientation.tY.vX
                                                * ptSplineObjWaypoint->tOrientation.tY.vY;
    *(float *)&Real64x3_RotateInverse_tTemp[16] = ptSplineObjWaypoint->tRelativeOrientation.tZ.vY
                                                * ptSplineObjWaypoint->tOrientation.tY.vZ
                                                + ptSplineObjWaypoint->tRelativeOrientation.tY.vY
                                                * ptSplineObjWaypoint->tOrientation.tY.vY
                                                + ptSplineObjWaypoint->tRelativeOrientation.tX.vY
                                                * ptSplineObjWaypoint->tOrientation.tY.vX;
    *(float *)&Real64x3_RotateInverse_tTemp[20] = ptSplineObjWaypoint->tRelativeOrientation.tZ.vZ
                                                * ptSplineObjWaypoint->tOrientation.tY.vZ
                                                + ptSplineObjWaypoint->tRelativeOrientation.tY.vZ
                                                * ptSplineObjWaypoint->tOrientation.tY.vY
                                                + ptSplineObjWaypoint->tRelativeOrientation.tX.vZ
                                                * ptSplineObjWaypoint->tOrientation.tY.vX;
    *(float *)&Real64x3_RotateInverse_tTemp[24] = ptSplineObjWaypoint->tOrientation.tZ.vY
                                                * ptSplineObjWaypoint->tRelativeOrientation.tY.vX
                                                + ptSplineObjWaypoint->tRelativeOrientation.tZ.vX
                                                * ptSplineObjWaypoint->tOrientation.tZ.vZ
                                                + ptSplineObjWaypoint->tRelativeOrientation.tX.vX
                                                * ptSplineObjWaypoint->tOrientation.tZ.vX;
    *(float *)&Real64x3_RotateInverse_tTemp[28] = ptSplineObjWaypoint->tRelativeOrientation.tX.vY
                                                * ptSplineObjWaypoint->tOrientation.tZ.vX
                                                + ptSplineObjWaypoint->tOrientation.tZ.vZ
                                                * ptSplineObjWaypoint->tRelativeOrientation.tZ.vY
                                                + ptSplineObjWaypoint->tOrientation.tZ.vY
                                                * ptSplineObjWaypoint->tRelativeOrientation.tY.vY;
    *(float *)&Real64x3_RotateInverse_tTemp[32] = ptSplineObjWaypoint->tRelativeOrientation.tX.vZ
                                                * ptSplineObjWaypoint->tOrientation.tZ.vX
                                                + ptSplineObjWaypoint->tOrientation.tZ.vZ
                                                * ptSplineObjWaypoint->tRelativeOrientation.tZ.vZ
                                                + ptSplineObjWaypoint->tOrientation.tZ.vY
                                                * ptSplineObjWaypoint->tRelativeOrientation.tY.vZ;
    qmemcpy(
      &ptSplineObjWaypoint->tRelativeOrientation,
      Real64x3_RotateInverse_tTemp,
      sizeof(ptSplineObjWaypoint->tRelativeOrientation));
  }
  else
  {
    ptSplineObjWaypoint->tRelativePos.vX = 0.0;
    ptSplineObjWaypoint->tRelativePos.vY = 0.0;
    ptSplineObjWaypoint->tRelativePos.vZ = 0.0;
    ptSplineObjWaypoint->tRelativeOrientation.tX.vX = 1.0;
    ptSplineObjWaypoint->tRelativeOrientation.tX.vY = 0.0;
    ptSplineObjWaypoint->tRelativeOrientation.tX.vZ = 0.0;
    ptSplineObjWaypoint->tRelativeOrientation.tY.vX = 0.0;
    ptSplineObjWaypoint->tRelativeOrientation.tY.vY = 1.0;
    ptSplineObjWaypoint->tRelativeOrientation.tY.vZ = 0.0;
    ptSplineObjWaypoint->tRelativeOrientation.tZ.vX = 0.0;
    ptSplineObjWaypoint->tRelativeOrientation.tZ.vY = 0.0;
    ptSplineObjWaypoint->tRelativeOrientation.tZ.vZ = 1.0;
    ptSplineObjWaypoint->tRelativeOrientation.nOps = 0;
  }
}

// source: h/2/splineobj.c:183  [anchor-mhash]
void __cdecl SplineObj_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ptQTask[1].ptNext = nullptr;
  BYTE2(ptQTask[2].ptPrev) = 0;
  BYTE1(ptQTask[2].ptPrev) = 0;
  LOBYTE(ptQTask[2].ptPrev) = 0;
  ptQTask[1].tQTaskChildren.ptHead = nullptr;
  ptQTask[1].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[1].tQTaskChildren.ptTail = nullptr;
  ptQTask[1].tQTaskRefList.ptHead = nullptr;
  ptQTask[1].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[1].tQTaskRefList.ptTail = nullptr;
  ptQTask[1].ptParent = nullptr;
  ptQTask[1].ptPrev = (struct QTask_s *)20;
  *(_DWORD *)&ptQTask[1].eQTaskType = 1078530011;
  ptQTask[2].ptNext = (struct QTask_s *)1078530011;
}

// source: h/2/splineobj.c:217  [size]
void __cdecl SplineObj_DeleteHandler(struct QTask_s *ptQTask)
{
  ;
}

// source: h/2/splineobj.c:232  [anchor-mhash]
void __cdecl SplineObj_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { float v39; };
    struct { float v40; };
    struct { char igi2_o2[16]; float Real32x3_Rotate_tTempa; };
    struct { char igi2_o3[20]; float Real32x3_Rotate_tTemp_4a; };
    struct { char igi2_o4[24]; float Real32x3_Rotate_tTemp_8a; };
    struct { char igi2_o5[28]; float v48; };
    struct { char igi2_o6[32]; float v49; };
    struct { char igi2_o7[40]; struct real32x9_t Real32x9_Multiply_tTemp; };
    struct { char igi2_o8[80]; struct real32x9_t Real32x9_Normalize_tTemp; };
    char igi2_extent[120];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  _DWORD *v2; // ebx
  struct QTask_s *v3; // esi
  struct QTask_s *ptHead; // eax
  unsigned __int16 v5; // di
  struct QTask_s *FirstChildOfType; // eax
  struct QTask_s *NextSiblingOfType; // edx
  double *p_tQTaskChildren; // ebx
  long double v9; // st7
  long double v10; // st7
  double v11; // st6
  double v12; // st5
  double v13; // st4
  double v14; // st3
  double v15; // st5
  double v16; // st5
  int nOps; // eax
  bool v18; // sf
  double v19; // st5
  double v20; // st5
  long double v21; // st2
  long double v22; // st2
  long double v23; // st5
  unsigned __int16 v24; // cx
  double v25; // st7
  double v26; // st6
  double v27; // st5
  long double v28; // rt2
  long double v29; // st3
  struct QTask_s *i; // eax
  struct QTask_s *ptTail; // eax
  struct QTask_s *v32; // ecx
  int v33; // eax
  int v34; // edx
  struct QTask_s *v35; // ecx
  int v36; // esi
  void (__cdecl *pfHandler)(int, _DWORD *); // ecx
  int v38; // edx
  struct real32x3_t tTemp_; // 0:^1C.12
  struct real32x3_t Real32x3_Rotate_tTemp; // 0:^28.12

  v2 = pxContext;
  if ( pxContext && *(_DWORD *)pxContext )
  {
    v3 = ptQTask;
    ptQTask[1].tQTaskRefList.ptMiddle = (struct QReference_s *)ptQTask[1].tQTaskChildren.ptMiddle;
    ptHead = (struct QTask_s *)ptQTask[1].tQTaskRefList.ptHead;
    ptQTask[1].tQTaskRefList.ptTail = (struct QReference_s *)ptQTask[1].tQTaskChildren.ptTail;
    ptQTask[1].ptParent = ptHead;
    ptQTask[2].ptNext = *(struct QTask_s **)&ptQTask[1].eQTaskType;
  }
  else
  {
    v3 = ptQTask;
  }
  v5 = SplineObjWaypoint_eQTaskType;
  if ( *(float *)&v3[1].eQTaskType != *(float *)&v3[2].ptNext )
  {
    FirstChildOfType = QTask_GetFirstChildOfType(v3, SplineObjWaypoint_eQTaskType);
    NextSiblingOfType = FirstChildOfType;
    if ( FirstChildOfType )
    {
      p_tQTaskChildren = (double *)&FirstChildOfType[8].tQTaskChildren;
      v9 = *(float *)&v3[1].eQTaskType - *(float *)&v3[2].ptNext;
      igi2_frame.v39 = sin(v9);
      v10 = cos(v9);
      v11 = -igi2_frame.v39;
      do
      {
        v12 = *(double *)&NextSiblingOfType[8].tQTaskChildren.ptHead - *p_tQTaskChildren;
        v13 = *(double *)&NextSiblingOfType[8].tQTaskChildren.ptTail - p_tQTaskChildren[1];
        v14 = *(double *)&NextSiblingOfType[8].tQTaskRefList.ptMiddle - p_tQTaskChildren[2];
        igi2_frame.v48 = v10 * v12 + v11 * v13 + 0.0 * v14;
        igi2_frame.v49 = v10 * v13 + igi2_frame.v39 * v12 + 0.0 * v14;
        *(double *)&NextSiblingOfType[8].tQTaskChildren.ptHead = igi2_frame.v48 + *p_tQTaskChildren;
        *(double *)&NextSiblingOfType[8].tQTaskChildren.ptTail = igi2_frame.v49 + p_tQTaskChildren[1];
        *(double *)&NextSiblingOfType[8].tQTaskRefList.ptMiddle = v14 + (v12 + v13) * 0.0 + p_tQTaskChildren[2];
        v15 = *(float *)&NextSiblingOfType[9].ptNext * 0.0;
        igi2_frame.Real32x9_Multiply_tTemp.tX.vX = igi2_frame.v39 * *(float *)&NextSiblingOfType[8].eQTaskType
                                      + v10 * *(float *)&NextSiblingOfType[8].ptParent
                                      + v15;
        igi2_frame.Real32x9_Multiply_tTemp.tX.vY = v10 * *(float *)&NextSiblingOfType[8].eQTaskType
                                      + v11 * *(float *)&NextSiblingOfType[8].ptParent
                                      + v15;
        igi2_frame.Real32x9_Multiply_tTemp.tX.vZ = (*(float *)&NextSiblingOfType[8].ptParent
                                       + *(float *)&NextSiblingOfType[8].eQTaskType)
                                      * 0.0
                                      + *(float *)&NextSiblingOfType[9].ptNext;
        v16 = *(float *)&NextSiblingOfType[9].tQTaskChildren.ptMiddle * 0.0;
        igi2_frame.Real32x9_Multiply_tTemp.tY.vX = v10 * *(float *)&NextSiblingOfType[9].ptPrev
                                      + igi2_frame.v39 * *(float *)&NextSiblingOfType[9].tQTaskChildren.ptHead
                                      + v16;
        igi2_frame.Real32x9_Multiply_tTemp.tY.vY = v10 * *(float *)&NextSiblingOfType[9].tQTaskChildren.ptHead
                                      + v11 * *(float *)&NextSiblingOfType[9].ptPrev
                                      + v16;
        v18 = (int)&NextSiblingOfType[9].tQTaskRefList.ptTail[-84].pxObject + 1 < 0;
        v19 = *(float *)&NextSiblingOfType[9].ptPrev + *(float *)&NextSiblingOfType[9].tQTaskChildren.ptHead;
        igi2_frame.Real32x9_Multiply_tTemp.nOps = (int)&NextSiblingOfType[9].tQTaskRefList.ptTail->ptNext + 1;
        nOps = igi2_frame.Real32x9_Multiply_tTemp.nOps;
        igi2_frame.Real32x9_Multiply_tTemp.tY.vZ = v19 * 0.0 + *(float *)&NextSiblingOfType[9].tQTaskChildren.ptMiddle;
        v20 = *(float *)&NextSiblingOfType[9].tQTaskRefList.ptMiddle * 0.0;
        igi2_frame.Real32x9_Multiply_tTemp.tZ.vX = igi2_frame.v39 * *(float *)&NextSiblingOfType[9].tQTaskRefList.ptHead
                                      + v10 * *(float *)&NextSiblingOfType[9].tQTaskChildren.ptTail
                                      + v20;
        igi2_frame.Real32x9_Multiply_tTemp.tZ.vY = v10 * *(float *)&NextSiblingOfType[9].tQTaskRefList.ptHead
                                      + v11 * *(float *)&NextSiblingOfType[9].tQTaskChildren.ptTail
                                      + v20;
        igi2_frame.Real32x9_Multiply_tTemp.tZ.vZ = (*(float *)&NextSiblingOfType[9].tQTaskRefList.ptHead
                                       + *(float *)&NextSiblingOfType[9].tQTaskChildren.ptTail)
                                      * 0.0
                                      + *(float *)&NextSiblingOfType[9].tQTaskRefList.ptMiddle;
        qmemcpy(&NextSiblingOfType[8].ptParent, &igi2_frame.Real32x9_Multiply_tTemp, sizeof(struct QTask_s));
        if ( !(v18 ^ __OFSUB__(nOps, 1000) | (nOps == 1000)) )
        {
          igi2_frame.Real32x9_Normalize_tTemp.tX = igi2_frame.Real32x9_Multiply_tTemp.tX;
          if ( igi2_frame.Real32x9_Multiply_tTemp.tX.vX != 0.0
            || igi2_frame.Real32x9_Multiply_tTemp.tX.vY != 0.0
            || igi2_frame.Real32x9_Multiply_tTemp.tX.vZ != 0.0 )
          {
            v21 = sqrt(
                    igi2_frame.Real32x9_Multiply_tTemp.tX.vX * igi2_frame.Real32x9_Multiply_tTemp.tX.vX
                  + igi2_frame.Real32x9_Multiply_tTemp.tX.vY * igi2_frame.Real32x9_Multiply_tTemp.tX.vY
                  + igi2_frame.Real32x9_Multiply_tTemp.tX.vZ * igi2_frame.Real32x9_Multiply_tTemp.tX.vZ);
            igi2_frame.Real32x9_Normalize_tTemp.tX.vX = igi2_frame.Real32x9_Multiply_tTemp.tX.vX * (1.0 / v21);
            igi2_frame.Real32x9_Normalize_tTemp.tX.vY = igi2_frame.Real32x9_Normalize_tTemp.tX.vY * (1.0 / v21);
            igi2_frame.Real32x9_Normalize_tTemp.tX.vZ = igi2_frame.Real32x9_Normalize_tTemp.tX.vZ * (1.0 / v21);
          }
          tTemp_.vX = igi2_frame.Real32x9_Multiply_tTemp.tZ.vY * igi2_frame.Real32x9_Multiply_tTemp.tX.vZ
                    - igi2_frame.Real32x9_Multiply_tTemp.tZ.vZ * igi2_frame.Real32x9_Multiply_tTemp.tX.vY;
          tTemp_.vY = -(igi2_frame.Real32x9_Multiply_tTemp.tZ.vX * igi2_frame.Real32x9_Multiply_tTemp.tX.vZ
                      - igi2_frame.Real32x9_Multiply_tTemp.tZ.vZ * igi2_frame.Real32x9_Multiply_tTemp.tX.vX);
          tTemp_.vZ = igi2_frame.Real32x9_Multiply_tTemp.tZ.vX * igi2_frame.Real32x9_Multiply_tTemp.tX.vY
                    - igi2_frame.Real32x9_Multiply_tTemp.tZ.vY * igi2_frame.Real32x9_Multiply_tTemp.tX.vX;
          igi2_frame.Real32x9_Normalize_tTemp.tY = tTemp_;
          Real32x3_Rotate_tTemp.vX = tTemp_.vZ * igi2_frame.Real32x9_Normalize_tTemp.tX.vY
                                   - tTemp_.vY * igi2_frame.Real32x9_Normalize_tTemp.tX.vZ;
          Real32x3_Rotate_tTemp.vY = -(tTemp_.vZ * igi2_frame.Real32x9_Normalize_tTemp.tX.vX
                                     - tTemp_.vX * igi2_frame.Real32x9_Normalize_tTemp.tX.vZ);
          Real32x3_Rotate_tTemp.vZ = tTemp_.vY * igi2_frame.Real32x9_Normalize_tTemp.tX.vX
                                   - tTemp_.vX * igi2_frame.Real32x9_Normalize_tTemp.tX.vY;
          igi2_frame.Real32x9_Normalize_tTemp.tZ = Real32x3_Rotate_tTemp;
          if ( tTemp_.vX != 0.0 || tTemp_.vY != 0.0 || tTemp_.vZ != 0.0 )
          {
            v22 = sqrt(tTemp_.vZ * tTemp_.vZ + tTemp_.vY * tTemp_.vY + tTemp_.vX * tTemp_.vX);
            igi2_frame.Real32x9_Normalize_tTemp.tY.vX = tTemp_.vX * (1.0 / v22);
            igi2_frame.Real32x9_Normalize_tTemp.tY.vY = igi2_frame.Real32x9_Normalize_tTemp.tY.vY * (1.0 / v22);
            igi2_frame.Real32x9_Normalize_tTemp.tY.vZ = igi2_frame.Real32x9_Normalize_tTemp.tY.vZ * (1.0 / v22);
          }
          if ( Real32x3_Rotate_tTemp.vX != 0.0 || Real32x3_Rotate_tTemp.vY != 0.0 || Real32x3_Rotate_tTemp.vZ != 0.0 )
          {
            v23 = 1.0
                / sqrt(
                    Real32x3_Rotate_tTemp.vX * Real32x3_Rotate_tTemp.vX
                  + Real32x3_Rotate_tTemp.vY * Real32x3_Rotate_tTemp.vY
                  + Real32x3_Rotate_tTemp.vZ * Real32x3_Rotate_tTemp.vZ);
            igi2_frame.Real32x9_Normalize_tTemp.tZ.vX = Real32x3_Rotate_tTemp.vX * v23;
            igi2_frame.Real32x9_Normalize_tTemp.tZ.vY = igi2_frame.Real32x9_Normalize_tTemp.tZ.vY * v23;
            igi2_frame.Real32x9_Normalize_tTemp.tZ.vZ = igi2_frame.Real32x9_Normalize_tTemp.tZ.vZ * v23;
          }
          qmemcpy(&igi2_frame.Real32x9_Multiply_tTemp, &igi2_frame.Real32x9_Normalize_tTemp, sizeof(igi2_frame.Real32x9_Multiply_tTemp));
          igi2_frame.Real32x9_Multiply_tTemp.nOps = 0;
        }
        v24 = SplineObjWaypoint_eQTaskType;
        NextSiblingOfType = QTask_GetNextSiblingOfType(NextSiblingOfType, SplineObjWaypoint_eQTaskType);
      }
      while ( NextSiblingOfType );
      v3 = ptQTask;
      v2 = pxContext;
      v5 = v24;
    }
    v3[2].ptNext = *(struct QTask_s **)&v3[1].eQTaskType;
  }
  if ( *(float *)&v3[1].tQTaskChildren.ptMiddle != *(float *)&v3[1].tQTaskRefList.ptMiddle
    || *(float *)&v3[1].tQTaskChildren.ptTail != *(float *)&v3[1].tQTaskRefList.ptTail
    || *(float *)&v3[1].tQTaskRefList.ptHead != *(float *)&v3[1].ptParent )
  {
    v25 = *(float *)&v3[1].tQTaskChildren.ptMiddle - *(float *)&v3[1].tQTaskRefList.ptMiddle;
    v26 = *(float *)&v3[1].tQTaskChildren.ptTail - *(float *)&v3[1].tQTaskRefList.ptTail;
    v27 = *(float *)&v3[1].tQTaskRefList.ptHead - *(float *)&v3[1].ptParent;
    v28 = sin(*(float *)&v3[1].eQTaskType);
    v29 = cos(*(float *)&v3[1].eQTaskType);
    igi2_frame.Real32x9_Normalize_tTemp.tX.vY = -v28;
    igi2_frame.v40 = v27 * 0.0;
    igi2_frame.Real32x3_Rotate_tTempa = v29 * v25 + igi2_frame.Real32x9_Normalize_tTemp.tX.vY * v26 + igi2_frame.v40;
    igi2_frame.Real32x3_Rotate_tTemp_4a = v29 * v26 + v28 * v25 + igi2_frame.v40;
    for ( i = QTask_GetFirstChildOfType(v3, v5); i; i = QTask_GetNextSiblingOfType(i, v5) )
    {
      *(double *)&i[8].tQTaskChildren.ptHead = igi2_frame.Real32x3_Rotate_tTempa + *(double *)&i[8].tQTaskChildren.ptHead;
      *(double *)&i[8].tQTaskChildren.ptTail = igi2_frame.Real32x3_Rotate_tTemp_4a + *(double *)&i[8].tQTaskChildren.ptTail;
      igi2_frame.Real32x3_Rotate_tTemp_8a = (v26 + v25) * 0.0 + v27;
      *(double *)&i[8].tQTaskRefList.ptMiddle = igi2_frame.Real32x3_Rotate_tTemp_8a + *(double *)&i[8].tQTaskRefList.ptMiddle;
    }
    ptTail = v3[1].tQTaskChildren.ptTail;
    v32 = (struct QTask_s *)v3[1].tQTaskRefList.ptHead;
    v3[1].tQTaskRefList.ptMiddle = (struct QReference_s *)v3[1].tQTaskChildren.ptMiddle;
    v3[1].tQTaskRefList.ptTail = (struct QReference_s *)ptTail;
    v3[1].ptParent = v32;
  }
  if ( (int)v3[1].ptNext < 0 )
    v3[1].ptNext = nullptr;
  if ( !v2 || !*v2 )
  {
    v33 = (int)v3->tQTaskChildren.ptHead;
    if ( *(_DWORD *)v33 )
    {
      if ( v33 )
      {
        v34 = QTask_nProtectedQTaskStackOffset;
        do
        {
          if ( *(_DWORD *)v33 )
            v35 = **(_DWORD **)v33 != 0 ? *(struct QTask_s **)v33 : nullptr;
          else
            v35 = nullptr;
          v36 = ParameterList_eUpdateInternalDataQTaskEvent;
          QTask_atProtectedQTaskStack[v34].ptQTask = v35;
          pfHandler = (void (__cdecl *)(int, _DWORD *))QTask_aatQTaskFinalEvent[v36][*(unsigned __int16 *)(v33 + 36)].pfHandler;
          v38 = v34 + 1;
          QTask_nProtectedQTaskStackOffset = v38;
          if ( pfHandler )
          {
            pfHandler(v33, v2);
            v38 = QTask_nProtectedQTaskStackOffset;
          }
          v33 = dword_849C7DC[v38];
          v34 = v38 - 1;
          QTask_nProtectedQTaskStackOffset = v34;
        }
        while ( v33 );
      }
    }
  }
}

// source: h/2/splineobj.c:343  [size]
void __cdecl SplineObj_UpdateInternalDataAfterLoadHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptHead; // eax
  int v2; // edx
  struct QTask_s *v3; // ecx
  void (__cdecl *pfHandler)(struct QTask_s *, _DWORD); // ecx
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
      pfHandler = (void (__cdecl *)(struct QTask_s *, _DWORD))QTask_aatQTaskFinalEvent[ParameterList_eUpdateInternalDataQTaskEvent][ptHead->eQTaskType].pfHandler;
      v5 = v2 + 1;
      QTask_nProtectedQTaskStackOffset = v5;
      if ( pfHandler )
      {
        pfHandler(ptHead, 0);
        v5 = QTask_nProtectedQTaskStackOffset;
      }
      ptHead = (struct QTask_s *)dword_849C7DC[v5];
      v2 = v5 - 1;
      QTask_nProtectedQTaskStackOffset = v2;
    }
    while ( ptHead );
  }
}

// source: h/2/splineobj.c:361  [size]
void __cdecl SplineObj_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = SplineObj_ptParameterList;
}

// source: h/2/splineobj.c:378  [anchor-mhash]
void __cdecl SplineObj_GetCameraTargetInfoHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *FirstChildOfType; // eax
  double v3; // st7
  double v4; // st7
  int *v5; // ebx
  int v6; // ebx
  double v7; // st6

  FirstChildOfType = QTask_GetFirstChildOfType(ptQTask, SplineObjWaypoint_eQTaskType);
  *(_DWORD *)pxContext = 0;
  *((_DWORD *)pxContext + 1) = 0;
  *((_DWORD *)pxContext + 2) = 0;
  *((_DWORD *)pxContext + 3) = 0;
  *((_DWORD *)pxContext + 4) = 0;
  *((_DWORD *)pxContext + 5) = 0;
  *((_DWORD *)pxContext + 19) = 1166016512;
  if ( FirstChildOfType )
  {
    qmemcpy(pxContext, &FirstChildOfType[8].tQTaskChildren, 0x18u);
    if ( *(float *)&FirstChildOfType[6].tQTaskChildren.ptHead <= (double)*(float *)&FirstChildOfType[6].tQTaskChildren.ptMiddle )
      v3 = *(float *)&FirstChildOfType[6].tQTaskChildren.ptMiddle;
    else
      v3 = *(float *)&FirstChildOfType[6].tQTaskChildren.ptHead;
    if ( v3 >= *(float *)&FirstChildOfType[6].ptPrev )
    {
      if ( *(float *)&FirstChildOfType[6].tQTaskChildren.ptHead <= (double)*(float *)&FirstChildOfType[6].tQTaskChildren.ptMiddle )
        v4 = *(float *)&FirstChildOfType[6].tQTaskChildren.ptMiddle;
      else
        v4 = *(float *)&FirstChildOfType[6].tQTaskChildren.ptHead;
    }
    else
    {
      v4 = *(float *)&FirstChildOfType[6].ptPrev;
    }
    v5 = *(int **)&FirstChildOfType[2].eQTaskType;
    if ( v5 && (v6 = *v5) != 0 )
      v7 = *(float *)(*(_DWORD *)(*(_DWORD *)(v6 + 12) + 12) + 120);
    else
      v7 = 1.0;
    *((float *)pxContext + 19) = v4 * v7;
  }
  *((_DWORD *)pxContext + 6) = 0;
  *((_DWORD *)pxContext + 7) = 0;
  *((_DWORD *)pxContext + 8) = 0;
  *((_DWORD *)pxContext + 10) = 0;
  *((_DWORD *)pxContext + 11) = 0;
  *((_DWORD *)pxContext + 12) = 0;
  *((_DWORD *)pxContext + 14) = 0;
  *((_DWORD *)pxContext + 15) = 0;
  *((_DWORD *)pxContext + 16) = 0;
  *((_DWORD *)pxContext + 18) = 0;
  *((_DWORD *)pxContext + 20) = 0;
  *((_DWORD *)pxContext + 9) = 1065353216;
  *((_DWORD *)pxContext + 13) = 1065353216;
  *((_DWORD *)pxContext + 17) = 1065353216;
}

// source: h/2/splineobj.c:435  [anchor-caller]
void __cdecl SplineObj_GetPosAndMatrix(
        int nQTaskID,
        struct real32x9_t *ptMatrix,
        struct real64x3_t *ptPos,
        char *pisValid,
        float vDistance,
        int nNumTailPoints,
        float *pvDistanceToNext,
        struct real32x3_t *ptDisplacement)
{
  #pragma pack(push, 1)
  union
  {
    struct { float x; };
    struct { float xa; };
    struct { float xb; };
    struct { float xc; };
    struct { char igi2_o4[20]; float vT; };
    struct { char igi2_o5[20]; float vTa; };
    struct { char igi2_o6[20]; float vTb; };
    struct { char igi2_o7[20]; float vTc; };
    struct { char igi2_o8[20]; float vTd; };
    struct { char igi2_o9[24]; float vXW; };
    struct { char igi2_o10[24]; float vXWa; };
    struct { char igi2_o11[24]; float vXWb; };
    struct { char igi2_o12[24]; float vXWc; };
    struct { char igi2_o13[24]; float vXWd; };
    struct { char igi2_o14[28]; float vTempDistance; };
    struct { char igi2_o15[28]; float vTempDistancea; };
    struct { char igi2_o16[32]; float vYW; };
    struct { char igi2_o17[32]; float vYWa; };
    struct { char igi2_o18[32]; float vYWb; };
    struct { char igi2_o19[32]; float vYWc; };
    struct { char igi2_o20[36]; double vBeta; };
    struct { char igi2_o21[36]; float vBetaa; };
    struct { char igi2_o22[36]; double vBetab; };
    struct { char igi2_o23[36]; float vBetac; };
    struct { char igi2_o24[36]; float vBetad; };
    struct { char igi2_o25[36]; float vBetae; };
    struct { char igi2_o26[44]; double vCurrentSquaredDistance1; };
    struct { char igi2_o27[44]; float vCurrentSquaredDistance1a; };
    struct { char igi2_o28[44]; float vCurrentSquaredDistance1b; };
    struct { char igi2_o29[44]; double vCurrentSquaredDistance1c; };
    struct { char igi2_o30[44]; float vCurrentSquaredDistance1d; };
    struct { char igi2_o31[44]; float vCurrentSquaredDistance1e; };
    struct { char igi2_o32[44]; float vCurrentSquaredDistance1f; };
    struct { char igi2_o33[52]; int aiNext[3]; };
    struct { char igi2_o34[72]; int iPoint; };
    struct { char igi2_o35[76]; struct real64x3_t tTempWorldPos1; };
    struct { char igi2_o36[100]; struct Quat32_t tFinalQuat; };
    struct { char igi2_o37[120]; float vCurrentTailPointDistance; };
    struct { char igi2_o38[124]; struct real64x3_t tTempWorldPos0; };
    struct { char igi2_o39[152]; struct SplineObjWaypoint_s *ptWaypoint; };
    struct { char igi2_o40[156]; float *p_vZ; };
    struct { char igi2_o41[160]; float *v195; };
    struct { char igi2_o42[164]; float *v196; };
    struct { char igi2_o43[168]; float *v197; };
    struct { char igi2_o44[172]; float *v198; };
    struct { char igi2_o45[176]; float *v199; };
    struct { char igi2_o46[180]; struct Quat32_t tQuat1; };
    struct { char igi2_o47[200]; struct Quat32_t tQuat0; };
    struct { char igi2_o48[220]; struct real32x3_t tTempPos; };
    struct { char igi2_o49[232]; _DWORD v203[3]; };
    struct { char igi2_o50[244]; _DWORD v204[3]; };
    struct { char igi2_o51[256]; struct real32x3_t Real32x3_Rotate_tTemp; };
    struct { char igi2_o52[272]; float v206; };
    struct { char igi2_o53[276]; float v207; };
    struct { char igi2_o54[284]; float v208; };
    struct { char igi2_o55[288]; float v209; };
    struct { char igi2_o56[296]; float v210; };
    struct { char igi2_o57[300]; float v211; };
    struct { char igi2_o58[312]; float v212; };
    struct { char igi2_o59[324]; float v213; };
    struct { char igi2_o60[336]; float v214; };
    struct { char igi2_o61[348]; float v215; };
    struct { char igi2_o62[360]; float v216; };
    char igi2_extent[364];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct real64x3_t *v8; // ebp
  int v9; // ebx
  struct QReference_s *v10; // eax
  float *pxObject; // esi
  struct SplineObjWaypoint_s *FirstChildOfType; // edx
  double v13; // st7
  double v14; // st6
  int v15; // eax
  struct real64x3_t *p_tPos; // edx
  struct real64x3_t *v17; // edi
  struct SplineObjWaypoint_s *NextSiblingOfType; // eax
  struct SplineObjSegment_s *ptSegment; // ebp
  double v20; // st6
  double v21; // st6
  int v22; // ecx
  struct real64x3_t *v23; // eax
  float *avAreaLength; // ecx
  double v25; // st6
  int v26; // ebx
  float *v27; // eax
  struct real64x3_t *v28; // esi
  double v29; // st6
  double v30; // st6
  float *v31; // ecx
  double v32; // st5
  double v33; // st5
  double v34; // st5
  double v35; // st4
  struct real32x9_t *v36; // eax
  struct QTask_s *v37; // ecx
  double v38; // st7
  long double v39; // st7
  long double v40; // st7
  int v41; // edx
  struct real64x3_t *v42; // ecx
  double v43; // st7
  bool v44; // c0
  bool v45; // c3
  int v46; // edx
  int v47; // esi
  double v48; // st7
  double v49; // st6
  int v50; // eax
  double v51; // st7
  double v52; // st7
  long double v53; // st7
  long double v54; // st7
  double v55; // st7
  bool v56; // c0
  bool v57; // c3
  int v58; // edx
  int v59; // esi
  double v60; // st7
  double v61; // st6
  int v62; // eax
  double v63; // st7
  double v64; // st6
  double v65; // st5
  double v66; // st7
  struct real32x3_t *v67; // edx
  double v68; // st6
  double v69; // st5
  double v70; // st7
  struct real64x3_t *v71; // edi
  float *v72; // eax
  double v73; // st7
  double v74; // st6
  double vX; // st7
  double vY; // st6
  double v77; // st5
  float *v78; // eax
  double v79; // st4
  double v80; // st4
  double v81; // st7
  struct SplineObjWaypoint_s *PrevSiblingOfType; // eax
  struct SplineObjSegment_s *v83; // ecx
  int nAreas; // ebx
  float *v85; // eax
  double v86; // st6
  double v87; // st5
  double v88; // st5
  double v89; // st5
  float *v90; // eax
  double v91; // st5
  double v92; // st5
  double v93; // st4
  double v94; // st3
  long double v95; // st7
  double v96; // st6
  double v97; // st7
  double v98; // st7
  long double v99; // st7
  double v100; // st6
  float *v101; // eax
  double v102; // st7
  double v103; // st6
  double v104; // st5
  float *v105; // eax
  double v106; // st4
  double v107; // st4
  struct SplineObjWaypoint_s *v108; // eax
  struct SplineObjSegment_s *v109; // ecx
  float *v110; // eax
  double v111; // st6
  double v112; // st5
  double v113; // st5
  double v114; // st5
  float *v115; // eax
  double v116; // st5
  double v117; // st4
  double v118; // st5
  double v119; // st4
  double v120; // st3
  long double v121; // st7
  long double v122; // st7
  long double v123; // st7
  struct QTask_s *v124; // ecx
  double v125; // st7
  long double v126; // st7
  long double v127; // st7
  double v128; // st7
  bool v129; // c0
  bool v130; // c3
  int v131; // edx
  int v132; // esi
  double v133; // st7
  double v134; // st6
  int v135; // eax
  double v136; // st7
  double v137; // st7
  long double v138; // st7
  long double v139; // st7
  double v140; // st7
  bool v141; // c0
  bool v142; // c3
  int v143; // edx
  int v144; // esi
  double v145; // st7
  double v146; // st6
  int v147; // eax
  double v148; // st7
  double v149; // st6
  double v150; // st5
  double v151; // st7
  int nOps; // edx
  struct real32x9_t *atAreaOrientation; // esi
  struct real32x9_t *ptMatrixa = *(struct real32x9_t * *)&ptPos; // [esp+174h] [ebp+8h] ARGSLOT

  v8 = ptPos;
  v9 = 0;
  igi2_frame.vTempDistance = 0.0;
  if ( (unsigned int)nQTaskID >= 0x1000
    || (v10 = Level_atLevelQTaskID[nQTaskID]) == nullptr
    || (pxObject = (float *)v10->pxObject) == nullptr )
  {
LABEL_28:
    *pisValid = 0;
    return;
  }
  FirstChildOfType = (struct SplineObjWaypoint_s *)QTask_GetFirstChildOfType(
                                                     (struct QTask_s *)v10->pxObject,
                                                     SplineObjWaypoint_eQTaskType);
  igi2_frame.ptWaypoint = FirstChildOfType;
  if ( !FirstChildOfType )
    goto LABEL_29;
  if ( pxObject[12] == 0.0 )
    goto LABEL_13;
  v13 = vDistance;
  if ( vDistance < 0.0 )
  {
    do
      v13 = v13 + pxObject[12];
    while ( v13 < 0.0 );
    vDistance = v13;
  }
  v14 = pxObject[12];
  if ( v13 >= v14 )
  {
    do
      v13 = v13 - v14;
    while ( v13 >= v14 );
    vDistance = v13;
  }
  if ( v13 == 0.0 )
  {
LABEL_13:
    if ( ptMatrix )
      qmemcpy(ptMatrix, &FirstChildOfType->tOrientation, sizeof(struct real32x9_t));
    v15 = nNumTailPoints + 1;
    if ( nNumTailPoints + 1 <= 0 )
      goto LABEL_126;
    p_tPos = &FirstChildOfType->tPos;
    do
    {
      v17 = v8++;
      --v15;
      qmemcpy(v17, p_tPos, sizeof(struct real64x3_t));
    }
    while ( v15 );
    *pisValid = 1;
    return;
  }
  if ( v13 <= 0.0 )
  {
LABEL_29:
    *pisValid = 0;
    return;
  }
  do
  {
    NextSiblingOfType = (struct SplineObjWaypoint_s *)QTask_GetNextSiblingOfType(
                                                        &igi2_frame.ptWaypoint->tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask,
                                                        SplineObjWaypoint_eQTaskType);
    if ( !NextSiblingOfType )
      goto LABEL_28;
    ptSegment = NextSiblingOfType->ptSegment;
    v20 = igi2_frame.vTempDistance + ptSegment->vLength;
    igi2_frame.ptWaypoint = NextSiblingOfType;
    igi2_frame.vTempDistance = v20;
  }
  while ( v20 < v13 );
  v21 = igi2_frame.vTempDistance - ptSegment->vLength;
  if ( v21 == v13 )
  {
    v22 = nNumTailPoints + 1;
    if ( nNumTailPoints + 1 > 0 )
    {
      v23 = ptPos;
      do
      {
        ++v23;
        --v22;
        v23[-1].vX = ptSegment->atAreaPos[0].vX + ptSegment->tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos.vX;
        v23[-1].vY = ptSegment->atAreaPos[0].vY + ptSegment->tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos.vY;
        v23[-1].vZ = ptSegment->atAreaPos[0].vZ + ptSegment->tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos.vZ;
      }
      while ( v22 );
    }
    if ( !ptMatrix )
      goto LABEL_126;
    qmemcpy(ptMatrix, ptSegment->atAreaOrientation, sizeof(struct real32x9_t));
    *pisValid = 1;
    return;
  }
  if ( v21 >= v13 )
  {
LABEL_34:
    v25 = v21 - *((float *)&ptSegment->atAreaOrientation[20].nOps + v9);
    v26 = v9 - 1;
    v27 = (float *)((char *)ptSegment + 12 * v26);
    igi2_frame.vTempDistancea = v25;
    igi2_frame.v199 = v27 + 85;
    v28 = ptPos;
    v29 = (v13 - v25) / ptSegment->avAreaLength[v26];
    igi2_frame.v196 = v27 + 88;
    igi2_frame.vT = v29;
    v30 = (v27[88] - v27[85]) * igi2_frame.vT + v27[85];
    v31 = v27 + 89;
    v32 = v27[89];
    v27 += 86;
    v33 = v32 - *v27;
    igi2_frame.v195 = v31;
    igi2_frame.v198 = v27;
    igi2_frame.p_vZ = &ptSegment->atAreaPos[v26 + 1].vZ;
    v34 = v33 * igi2_frame.vT + *v27;
    v35 = *igi2_frame.p_vZ;
    igi2_frame.v197 = &ptSegment->atAreaPos[v26].vZ;
    v36 = ptMatrix;
    igi2_frame.tTempPos.vZ = (v35 - *igi2_frame.v197) * igi2_frame.vT + *igi2_frame.v197;
    ptPos->vX = v30 + ptSegment->tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos.vX;
    ptPos->vY = v34 + ptSegment->tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos.vY;
    ptPos->vZ = igi2_frame.tTempPos.vZ + ptSegment->tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos.vZ;
    if ( ptMatrix )
    {
      v37 = &ptSegment->tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask + v26;
      v38 = *(float *)&v37[15].tQTaskRefList.ptMiddle
          + *(float *)&v37[15].tQTaskChildren.ptHead
          + *(float *)&v37[14].ptParent;
      if ( v38 <= 0.0 )
      {
        igi2_frame.aiNext[0] = 1;
        v43 = *(float *)&v37[15].tQTaskChildren.ptHead;
        igi2_frame.aiNext[1] = 2;
        v44 = v43 < *(float *)&v37[14].ptParent;
        v45 = v43 == *(float *)&v37[14].ptParent;
        igi2_frame.aiNext[2] = 0;
        v46 = !v44 && !v45;
        if ( *(float *)&v37[15].tQTaskRefList.ptMiddle > (double)*((float *)&v37[14].ptParent + 4 * v46) )
          v46 = 2;
        v47 = igi2_frame.aiNext[v46];
        v48 = sqrt(
                *((float *)&v37[14].ptParent + 4 * v46)
              - *((float *)&v37[14].ptParent + 4 * v47)
              - *((float *)&v37[14].ptParent + 4 * igi2_frame.aiNext[v47])
              + 1.0);
        *(&igi2_frame.tQuat0.vX + v46) = 0.5 * v48;
        if ( v48 != 0.0 )
          v48 = 0.5 / v48;
        v49 = *((float *)&v37[14].ptParent + 3 * v47 + v46) + *((float *)&v37[14].ptParent + 3 * v46 + v47);
        v50 = igi2_frame.aiNext[v47];
        igi2_frame.iPoint = 3 * v50;
        *(&igi2_frame.tQuat0.vX + v47) = v49 * v48;
        *(&igi2_frame.tQuat0.vX + v50) = (*((float *)&v37[14].ptParent + 3 * v50 + v46)
                             + *((float *)&v37[14].ptParent + 3 * v46 + v50))
                            * v48;
        igi2_frame.tQuat0.vW = -((*((float *)&v37[14].ptParent + 3 * v47 + v50) - *((float *)&v37[14].ptParent + v47 + igi2_frame.iPoint))
                    * v48);
      }
      else
      {
        v39 = sqrt(v38 + 1.0);
        igi2_frame.tQuat0.vW = 0.5 * v39;
        v40 = 0.5 / v39;
        igi2_frame.tQuat0.vX = -((*(float *)&v37[15].tQTaskChildren.ptMiddle - *(float *)&v37[15].tQTaskRefList.ptHead) * v40);
        igi2_frame.tQuat0.vY = -((*(float *)&v37[15].tQTaskChildren.ptTail - ptSegment->atAreaOrientation[v26].tX.vZ) * v40);
        igi2_frame.tQuat0.vZ = -((*(float *)&v37[14].eQTaskType - *(float *)&v37[15].ptPrev) * v40);
      }
      v51 = *(float *)&v37[16].tQTaskRefList.ptMiddle;
      igi2_frame.tQuat0.nOps = (int)v37[15].tQTaskRefList.ptTail;
      v52 = v51 + *(float *)&v37[16].tQTaskChildren.ptHead + *(float *)&v37[15].ptParent;
      if ( v52 <= 0.0 )
      {
        v55 = *(float *)&v37[16].tQTaskChildren.ptHead;
        igi2_frame.aiNext[0] = 1;
        v56 = v55 < *(float *)&v37[15].ptParent;
        v57 = v55 == *(float *)&v37[15].ptParent;
        igi2_frame.aiNext[1] = 2;
        igi2_frame.aiNext[2] = 0;
        v58 = !v56 && !v57;
        if ( *(float *)&v37[16].tQTaskRefList.ptMiddle > (double)*((float *)&v37[15].ptParent + 4 * v58) )
          v58 = 2;
        v59 = igi2_frame.aiNext[v58];
        v60 = sqrt(
                *((float *)&v37[15].ptParent + 4 * v58)
              - *((float *)&v37[15].ptParent + 4 * v59)
              - *((float *)&v37[15].ptParent + 4 * igi2_frame.aiNext[v59])
              + 1.0);
        *(&igi2_frame.tQuat1.vX + v58) = 0.5 * v60;
        if ( v60 != 0.0 )
          v60 = 0.5 / v60;
        v61 = *((float *)&v37[15].ptParent + 3 * v59 + v58) + *((float *)&v37[15].ptParent + 3 * v58 + v59);
        v62 = igi2_frame.aiNext[v59];
        igi2_frame.iPoint = 3 * v62;
        *(&igi2_frame.tQuat1.vX + v59) = v61 * v60;
        *(&igi2_frame.tQuat1.vX + v62) = (*((float *)&v37[15].ptParent + 3 * v62 + v58)
                             + *((float *)&v37[15].ptParent + 3 * v58 + v62))
                            * v60;
        igi2_frame.tQuat1.vW = -((*((float *)&v37[15].ptParent + 3 * v59 + v62) - *((float *)&v37[15].ptParent + v59 + igi2_frame.iPoint))
                    * v60);
      }
      else
      {
        v53 = sqrt(v52 + 1.0);
        igi2_frame.tQuat1.vW = 0.5 * v53;
        v54 = 0.5 / v53;
        igi2_frame.tQuat1.vX = -((*(float *)&v37[16].tQTaskChildren.ptMiddle - *(float *)&v37[16].tQTaskRefList.ptHead) * v54);
        igi2_frame.tQuat1.vY = -((*(float *)&v37[16].tQTaskChildren.ptTail - ptSegment->atAreaOrientation[v26 + 1].tX.vZ) * v54);
        igi2_frame.tQuat1.vZ = -((*(float *)&v37[15].eQTaskType - *(float *)&v37[16].ptPrev) * v54);
      }
      igi2_frame.tQuat1.nOps = (int)v37[16].tQTaskRefList.ptTail;
      Quat32_SLERP(&igi2_frame.tFinalQuat, &igi2_frame.tQuat0, &igi2_frame.tQuat1, igi2_frame.vT);
      v36 = ptMatrix;
      v63 = igi2_frame.tFinalQuat.vX * igi2_frame.tFinalQuat.vX + igi2_frame.tFinalQuat.vX * igi2_frame.tFinalQuat.vX;
      v64 = igi2_frame.tFinalQuat.vY * igi2_frame.tFinalQuat.vX + igi2_frame.tFinalQuat.vY * igi2_frame.tFinalQuat.vX;
      *(float *)igi2_frame.aiNext = igi2_frame.tFinalQuat.vZ * igi2_frame.tFinalQuat.vX + igi2_frame.tFinalQuat.vZ * igi2_frame.tFinalQuat.vX;
      igi2_frame.vXWc = igi2_frame.tFinalQuat.vW * igi2_frame.tFinalQuat.vX + igi2_frame.tFinalQuat.vW * igi2_frame.tFinalQuat.vX;
      igi2_frame.vTc = igi2_frame.tFinalQuat.vY * igi2_frame.tFinalQuat.vY + igi2_frame.tFinalQuat.vY * igi2_frame.tFinalQuat.vY;
      igi2_frame.vCurrentTailPointDistance = igi2_frame.tFinalQuat.vZ * igi2_frame.tFinalQuat.vY + igi2_frame.tFinalQuat.vZ * igi2_frame.tFinalQuat.vY;
      igi2_frame.vYWb = igi2_frame.tFinalQuat.vW * igi2_frame.tFinalQuat.vY + igi2_frame.tFinalQuat.vW * igi2_frame.tFinalQuat.vY;
      *(float *)&igi2_frame.iPoint = igi2_frame.tFinalQuat.vZ * igi2_frame.tFinalQuat.vZ + igi2_frame.tFinalQuat.vZ * igi2_frame.tFinalQuat.vZ;
      v65 = igi2_frame.tFinalQuat.vW * igi2_frame.tFinalQuat.vZ + igi2_frame.tFinalQuat.vW * igi2_frame.tFinalQuat.vZ;
      ptMatrix->tX.vX = 1.0 - igi2_frame.vTc - *(float *)&igi2_frame.iPoint;
      ptMatrix->tX.vY = v64 - v65;
      ptMatrix->tX.vZ = igi2_frame.vYWb + *(float *)igi2_frame.aiNext;
      ptMatrix->tY.vX = v65 + v64;
      v66 = 1.0 - v63;
      ptMatrix->tY.vY = v66 - *(float *)&igi2_frame.iPoint;
      ptMatrix->tY.vZ = igi2_frame.vCurrentTailPointDistance - igi2_frame.vXWc;
      ptMatrix->tZ.vX = *(float *)igi2_frame.aiNext - igi2_frame.vYWb;
      ptMatrix->tZ.vY = igi2_frame.vCurrentTailPointDistance + igi2_frame.vXWc;
      ptMatrix->tZ.vZ = v66 - igi2_frame.vTc;
      v13 = vDistance;
      v28 = ptPos;
      ptMatrix->nOps = igi2_frame.tFinalQuat.nOps;
    }
    v67 = ptDisplacement;
    if ( ptDisplacement )
    {
      v68 = v36->tX.vZ * ptDisplacement->vZ + v36->tX.vY * ptDisplacement->vY + v36->tX.vX * ptDisplacement->vX;
      v69 = v36->tY.vZ * ptDisplacement->vZ + v36->tY.vX * ptDisplacement->vX + v36->tY.vY * ptDisplacement->vY;
      igi2_frame.tTempPos.vZ = v36->tZ.vZ * ptDisplacement->vZ + v36->tZ.vX * ptDisplacement->vX + v36->tZ.vY * ptDisplacement->vY;
      v28->vX = v68 + v28->vX;
      v28->vY = v69 + v28->vY;
      v28->vZ = igi2_frame.tTempPos.vZ + v28->vZ;
    }
    igi2_frame.vCurrentTailPointDistance = v13;
    *(float *)&igi2_frame.iPoint = 0.0;
    if ( nNumTailPoints <= 0 )
      goto LABEL_126;
    while ( 1 )
    {
      v70 = pvDistanceToNext[igi2_frame.iPoint];
      igi2_frame.vTa = pvDistanceToNext[igi2_frame.iPoint];
      v71 = v28++;
      ptMatrixa = (struct real32x9_t *)v28;
      igi2_frame.vXW = v70 * v70;
      igi2_frame.vCurrentTailPointDistance = igi2_frame.vCurrentTailPointDistance + v70;
      if ( ptMatrix )
        ++ptMatrix;
      if ( v70 < 0.0 )
      {
        igi2_frame.vCurrentSquaredDistance1 = *igi2_frame.v199 + ptSegment->tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos.vX;
        igi2_frame.tTempWorldPos0.vX = igi2_frame.vCurrentSquaredDistance1;
        *(double *)igi2_frame.aiNext = *igi2_frame.v198 + ptSegment->tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos.vY;
        igi2_frame.tTempWorldPos0.vY = *(double *)igi2_frame.aiNext;
        igi2_frame.vBeta = *igi2_frame.v197 + ptSegment->tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos.vZ;
        igi2_frame.tTempWorldPos0.vZ = igi2_frame.vBeta;
        if ( v67 )
        {
          v72 = (float *)(&ptSegment->tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask + v26);
          v73 = ptSegment->atAreaOrientation[v26].tX.vZ * v67->vZ + v72[148] * v67->vX + v72[149] * v67->vY;
          v74 = v72[153] * v67->vZ + v72[151] * v67->vX + v72[152] * v67->vY;
          igi2_frame.v214 = v72[156] * v67->vZ + v72[154] * v67->vX + v72[155] * v67->vY;
          igi2_frame.tTempWorldPos0.vX = v73 + igi2_frame.tTempWorldPos0.vX;
          igi2_frame.tTempWorldPos0.vY = v74 + igi2_frame.tTempWorldPos0.vY;
          igi2_frame.tTempWorldPos0.vZ = igi2_frame.v214 + igi2_frame.tTempWorldPos0.vZ;
        }
        if ( Real64x3_SquaredDistance(v71, &igi2_frame.tTempWorldPos0) <= igi2_frame.vXW )
        {
          v81 = igi2_frame.vTempDistancea;
          do
          {
            if ( v26 )
            {
              v81 = v81 - *((float *)&ptSegment->atAreaOrientation[20].nOps + v26--);
            }
            else
            {
              PrevSiblingOfType = (struct SplineObjWaypoint_s *)QTask_GetPrevSiblingOfType(
                                                                  &igi2_frame.ptWaypoint->tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask,
                                                                  SplineObjWaypoint_eQTaskType);
              v83 = PrevSiblingOfType->ptSegment;
              v67 = ptDisplacement;
              if ( !v83 )
                goto LABEL_118;
              nAreas = v83->nAreas;
              v81 = v81 - *((float *)&v83->atAreaOrientation[20].nOps + nAreas);
              v26 = nAreas - 1;
              igi2_frame.ptWaypoint = PrevSiblingOfType;
              ptSegment = v83;
            }
            v85 = (float *)((char *)ptSegment + 12 * v26);
            v86 = v85[85] + ptSegment->tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos.vX;
            igi2_frame.v199 = v85 + 85;
            igi2_frame.v198 = v85 + 86;
            igi2_frame.tTempWorldPos0.vX = v86;
            v87 = v85[86] + ptSegment->tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos.vY;
            igi2_frame.v197 = &ptSegment->atAreaPos[v26].vZ;
            igi2_frame.tTempWorldPos0.vY = v87;
            v88 = *igi2_frame.v197 + ptSegment->tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos.vZ;
            igi2_frame.v195 = v85 + 89;
            igi2_frame.tTempWorldPos0.vZ = v88;
            igi2_frame.v196 = v85 + 88;
            igi2_frame.tTempWorldPos1.vX = v85[88] + ptSegment->tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos.vX;
            v89 = v85[89] + ptSegment->tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos.vY;
            igi2_frame.p_vZ = &ptSegment->atAreaPos[v26 + 1].vZ;
            igi2_frame.tTempWorldPos1.vY = v89;
            igi2_frame.tTempWorldPos1.vZ = *igi2_frame.p_vZ + ptSegment->tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos.vZ;
            if ( v67 )
            {
              v90 = (float *)(&ptSegment->tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask + v26);
              v91 = ptSegment->atAreaOrientation[v26].tX.vZ * v67->vZ + v90[148] * v67->vX + v90[149] * v67->vY;
              igi2_frame.v206 = v90[153] * v67->vZ + v90[151] * v67->vX + v90[152] * v67->vY;
              igi2_frame.v207 = v90[156] * v67->vZ + v90[154] * v67->vX + v90[155] * v67->vY;
              v86 = v86 + v91;
              igi2_frame.tTempWorldPos0.vX = v86;
              igi2_frame.tTempWorldPos0.vY = igi2_frame.v206 + igi2_frame.tTempWorldPos0.vY;
              igi2_frame.tTempWorldPos0.vZ = igi2_frame.v207 + igi2_frame.tTempWorldPos0.vZ;
              v92 = ptSegment->atAreaOrientation[v26 + 1].tX.vZ * v67->vZ + v90[158] * v67->vX + v90[159] * v67->vY;
              v93 = v90[163] * v67->vZ + v90[161] * v67->vX + v90[162] * v67->vY;
              igi2_frame.v216 = v90[166] * v67->vZ + v90[164] * v67->vX + v90[165] * v67->vY;
              igi2_frame.tTempWorldPos1.vX = v92 + igi2_frame.tTempWorldPos1.vX;
              igi2_frame.tTempWorldPos1.vY = v93 + igi2_frame.tTempWorldPos1.vY;
              igi2_frame.tTempWorldPos1.vZ = igi2_frame.v216 + igi2_frame.tTempWorldPos1.vZ;
            }
            igi2_frame.vYW = (v71->vZ - igi2_frame.tTempWorldPos0.vZ) * (v71->vZ - igi2_frame.tTempWorldPos0.vZ)
                + (v71->vY - igi2_frame.tTempWorldPos0.vY) * (v71->vY - igi2_frame.tTempWorldPos0.vY)
                + (v71->vX - v86) * (v71->vX - v86);
            v94 = (v71->vZ - igi2_frame.tTempWorldPos1.vZ) * (v71->vZ - igi2_frame.tTempWorldPos1.vZ)
                + (v71->vY - igi2_frame.tTempWorldPos1.vY) * (v71->vY - igi2_frame.tTempWorldPos1.vY)
                + (v71->vX - igi2_frame.tTempWorldPos1.vX) * (v71->vX - igi2_frame.tTempWorldPos1.vX);
            igi2_frame.vCurrentSquaredDistance1a = v94;
          }
          while ( igi2_frame.vYW > (double)igi2_frame.vXW == v94 > igi2_frame.vXW );
          igi2_frame.vTempDistancea = v81;
          igi2_frame.vXWa = ptSegment->avAreaLength[v26];
          *(float *)igi2_frame.aiNext = sqrt(igi2_frame.vCurrentSquaredDistance1a);
          igi2_frame.x = (igi2_frame.vYW - igi2_frame.vCurrentSquaredDistance1a - igi2_frame.vXWa * igi2_frame.vXWa) / (*(float *)igi2_frame.aiNext * igi2_frame.vXWa * -2.0);
          v95 = Real32_Acos(igi2_frame.x);
          v96 = igi2_frame.vTa;
          if ( igi2_frame.vTa < 0.0 )
            v96 = -v96;
          igi2_frame.vCurrentSquaredDistance1b = sin(v95);
          igi2_frame.vBetac = 3.1415927410125732 - v95;
          igi2_frame.xa = igi2_frame.vCurrentSquaredDistance1b / v96 * *(float *)igi2_frame.aiNext;
          v97 = igi2_frame.vBetac - Real32_Asin(igi2_frame.xa);
          igi2_frame.vBetaa = v97;
          if ( v97 <= 0.001 )
          {
            v99 = sqrt(igi2_frame.vYW);
            v100 = igi2_frame.vTa;
            if ( igi2_frame.vTa < 0.0 )
              v100 = -v100;
            igi2_frame.vTb = (v100 - v99) / (*(float *)igi2_frame.aiNext - v99);
          }
          else
          {
            v98 = igi2_frame.vTa;
            if ( igi2_frame.vTa < 0.0 )
              v98 = -v98;
            igi2_frame.vTb = 1.0 - sin(igi2_frame.vBetaa) * v98 / igi2_frame.vCurrentSquaredDistance1b / igi2_frame.vXWa;
          }
LABEL_101:
          vX = igi2_frame.tTempWorldPos0.vX;
          v67 = ptDisplacement;
          vY = igi2_frame.tTempWorldPos0.vY;
          v77 = igi2_frame.tTempWorldPos1.vX;
        }
        else
        {
          igi2_frame.tTempWorldPos0.vZ = igi2_frame.vBeta;
          igi2_frame.vTb = (igi2_frame.vCurrentTailPointDistance - igi2_frame.vTempDistancea) / ptSegment->avAreaLength[v26];
          vX = igi2_frame.vCurrentSquaredDistance1;
          vY = *(double *)igi2_frame.aiNext;
          v77 = *igi2_frame.v196 + ptSegment->tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos.vX;
          igi2_frame.tTempWorldPos1.vY = *igi2_frame.v195 + ptSegment->tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos.vY;
          igi2_frame.tTempWorldPos1.vZ = *igi2_frame.p_vZ + ptSegment->tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos.vZ;
          if ( v67 )
          {
            v78 = (float *)(&ptSegment->tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask + v26);
            v79 = ptSegment->atAreaOrientation[v26].tX.vZ * v67->vZ + v78[148] * v67->vX + v78[149] * v67->vY;
            igi2_frame.v208 = v78[153] * v67->vZ + v78[151] * v67->vX + v78[152] * v67->vY;
            igi2_frame.v209 = v78[156] * v67->vZ + v78[154] * v67->vX + v78[155] * v67->vY;
            vX = igi2_frame.vCurrentSquaredDistance1 + v79;
            vY = *(double *)igi2_frame.aiNext + igi2_frame.v208;
            igi2_frame.tTempWorldPos0.vZ = igi2_frame.v209 + igi2_frame.tTempWorldPos0.vZ;
            v80 = ptSegment->atAreaOrientation[v26 + 1].tX.vZ * v67->vZ + v78[158] * v67->vX + v78[159] * v67->vY;
            igi2_frame.Real32x3_Rotate_tTemp.vY = v78[163] * v67->vZ + v78[161] * v67->vX + v78[162] * v67->vY;
            igi2_frame.Real32x3_Rotate_tTemp.vZ = v78[166] * v67->vZ + v78[164] * v67->vX + v78[165] * v67->vY;
            v77 = v77 + v80;
            igi2_frame.tTempWorldPos1.vY = igi2_frame.Real32x3_Rotate_tTemp.vY + igi2_frame.tTempWorldPos1.vY;
            igi2_frame.tTempWorldPos1.vZ = igi2_frame.Real32x3_Rotate_tTemp.vZ + igi2_frame.tTempWorldPos1.vZ;
          }
        }
LABEL_102:
        v28->vX = (v77 - vX) * igi2_frame.vTb + vX;
        v28->vY = (igi2_frame.tTempWorldPos1.vY - vY) * igi2_frame.vTb + vY;
        v28->vZ = (igi2_frame.tTempWorldPos1.vZ - igi2_frame.tTempWorldPos0.vZ) * igi2_frame.vTb + igi2_frame.tTempWorldPos0.vZ;
        if ( ptMatrix )
        {
          v124 = &ptSegment->tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask + v26;
          v125 = *(float *)&v124[15].tQTaskRefList.ptMiddle
               + *(float *)&v124[15].tQTaskChildren.ptHead
               + *(float *)&v124[14].ptParent;
          if ( v125 <= 0.0 )
          {
            v128 = *(float *)&v124[15].tQTaskChildren.ptHead;
            igi2_frame.v203[0] = 1;
            v129 = v128 < *(float *)&v124[14].ptParent;
            v130 = v128 == *(float *)&v124[14].ptParent;
            igi2_frame.v203[1] = 2;
            igi2_frame.v203[2] = 0;
            v131 = !v129 && !v130;
            if ( *(float *)&v124[15].tQTaskRefList.ptMiddle > (double)*((float *)&v124[14].ptParent + 4 * v131) )
              v131 = 2;
            v132 = igi2_frame.v203[v131];
            v133 = sqrt(
                     *((float *)&v124[14].ptParent + 4 * v131)
                   - *((float *)&v124[14].ptParent + 4 * v132)
                   - *((float *)&v124[14].ptParent + 4 * igi2_frame.v203[v132])
                   + 1.0);
            *(&igi2_frame.tQuat0.vX + v131) = 0.5 * v133;
            if ( v133 != 0.0 )
              v133 = 0.5 / v133;
            v134 = *((float *)&v124[14].ptParent + 3 * v132 + v131) + *((float *)&v124[14].ptParent + 3 * v131 + v132);
            v135 = igi2_frame.v203[v132];
            igi2_frame.aiNext[0] = 3 * v135;
            *(&igi2_frame.tQuat0.vX + v132) = v134 * v133;
            *(&igi2_frame.tQuat0.vX + v135) = (*((float *)&v124[14].ptParent + 3 * v135 + v131)
                                  + *((float *)&v124[14].ptParent + 3 * v131 + v135))
                                 * v133;
            igi2_frame.tQuat0.vW = -((*((float *)&v124[14].ptParent + 3 * v132 + v135)
                         - *((float *)&v124[14].ptParent + v132 + igi2_frame.aiNext[0]))
                        * v133);
          }
          else
          {
            v126 = sqrt(v125 + 1.0);
            igi2_frame.tQuat0.vW = 0.5 * v126;
            v127 = 0.5 / v126;
            igi2_frame.tQuat0.vX = -((*(float *)&v124[15].tQTaskChildren.ptMiddle - *(float *)&v124[15].tQTaskRefList.ptHead) * v127);
            igi2_frame.tQuat0.vY = -((*(float *)&v124[15].tQTaskChildren.ptTail - ptSegment->atAreaOrientation[v26].tX.vZ) * v127);
            igi2_frame.tQuat0.vZ = -((*(float *)&v124[14].eQTaskType - *(float *)&v124[15].ptPrev) * v127);
          }
          v136 = *(float *)&v124[16].tQTaskRefList.ptMiddle;
          igi2_frame.tQuat0.nOps = (int)v124[15].tQTaskRefList.ptTail;
          v137 = v136 + *(float *)&v124[16].tQTaskChildren.ptHead + *(float *)&v124[15].ptParent;
          if ( v137 <= 0.0 )
          {
            v140 = *(float *)&v124[16].tQTaskChildren.ptHead;
            igi2_frame.v204[0] = 1;
            v141 = v140 < *(float *)&v124[15].ptParent;
            v142 = v140 == *(float *)&v124[15].ptParent;
            igi2_frame.v204[1] = 2;
            igi2_frame.v204[2] = 0;
            v143 = !v141 && !v142;
            if ( *(float *)&v124[16].tQTaskRefList.ptMiddle > (double)*((float *)&v124[15].ptParent + 4 * v143) )
              v143 = 2;
            v144 = igi2_frame.v204[v143];
            v145 = sqrt(
                     *((float *)&v124[15].ptParent + 4 * v143)
                   - *((float *)&v124[15].ptParent + 4 * v144)
                   - *((float *)&v124[15].ptParent + 4 * igi2_frame.v204[v144])
                   + 1.0);
            *(&igi2_frame.tQuat1.vX + v143) = 0.5 * v145;
            if ( v145 != 0.0 )
              v145 = 0.5 / v145;
            v146 = *((float *)&v124[15].ptParent + 3 * v144 + v143) + *((float *)&v124[15].ptParent + 3 * v143 + v144);
            v147 = igi2_frame.v204[v144];
            igi2_frame.aiNext[0] = 3 * v147;
            *(&igi2_frame.tQuat1.vX + v144) = v146 * v145;
            *(&igi2_frame.tQuat1.vX + v147) = (*((float *)&v124[15].ptParent + 3 * v147 + v143)
                                  + *((float *)&v124[15].ptParent + 3 * v143 + v147))
                                 * v145;
            igi2_frame.tQuat1.vW = -((*((float *)&v124[15].ptParent + 3 * v144 + v147)
                         - *((float *)&v124[15].ptParent + igi2_frame.aiNext[0] + v144))
                        * v145);
          }
          else
          {
            v138 = sqrt(v137 + 1.0);
            igi2_frame.tQuat1.vW = 0.5 * v138;
            v139 = 0.5 / v138;
            igi2_frame.tQuat1.vX = -((*(float *)&v124[16].tQTaskChildren.ptMiddle - *(float *)&v124[16].tQTaskRefList.ptHead) * v139);
            igi2_frame.tQuat1.vY = -((*(float *)&v124[16].tQTaskChildren.ptTail - ptSegment->atAreaOrientation[v26 + 1].tX.vZ)
                        * v139);
            igi2_frame.tQuat1.vZ = -((*(float *)&v124[15].eQTaskType - *(float *)&v124[16].ptPrev) * v139);
          }
          igi2_frame.tQuat1.nOps = (int)v124[16].tQTaskRefList.ptTail;
          Quat32_SLERP(&igi2_frame.tFinalQuat, &igi2_frame.tQuat0, &igi2_frame.tQuat1, igi2_frame.vTb);
          v148 = igi2_frame.tFinalQuat.vX * igi2_frame.tFinalQuat.vX + igi2_frame.tFinalQuat.vX * igi2_frame.tFinalQuat.vX;
          v149 = igi2_frame.tFinalQuat.vY * igi2_frame.tFinalQuat.vX + igi2_frame.tFinalQuat.vY * igi2_frame.tFinalQuat.vX;
          *(float *)igi2_frame.aiNext = igi2_frame.tFinalQuat.vZ * igi2_frame.tFinalQuat.vX + igi2_frame.tFinalQuat.vZ * igi2_frame.tFinalQuat.vX;
          igi2_frame.vXWd = igi2_frame.tFinalQuat.vW * igi2_frame.tFinalQuat.vX + igi2_frame.tFinalQuat.vW * igi2_frame.tFinalQuat.vX;
          igi2_frame.vBetae = igi2_frame.tFinalQuat.vY * igi2_frame.tFinalQuat.vY + igi2_frame.tFinalQuat.vY * igi2_frame.tFinalQuat.vY;
          igi2_frame.vTd = igi2_frame.tFinalQuat.vZ * igi2_frame.tFinalQuat.vY + igi2_frame.tFinalQuat.vZ * igi2_frame.tFinalQuat.vY;
          igi2_frame.vYWc = igi2_frame.tFinalQuat.vW * igi2_frame.tFinalQuat.vY + igi2_frame.tFinalQuat.vW * igi2_frame.tFinalQuat.vY;
          igi2_frame.vCurrentSquaredDistance1f = igi2_frame.tFinalQuat.vZ * igi2_frame.tFinalQuat.vZ + igi2_frame.tFinalQuat.vZ * igi2_frame.tFinalQuat.vZ;
          v150 = igi2_frame.tFinalQuat.vW * igi2_frame.tFinalQuat.vZ + igi2_frame.tFinalQuat.vW * igi2_frame.tFinalQuat.vZ;
          ptMatrix->tX.vX = 1.0 - igi2_frame.vBetae - igi2_frame.vCurrentSquaredDistance1f;
          ptMatrix->tX.vY = v149 - v150;
          ptMatrix->tX.vZ = *(float *)igi2_frame.aiNext + igi2_frame.vYWc;
          ptMatrix->tY.vX = v149 + v150;
          v151 = 1.0 - v148;
          ptMatrix->tY.vY = v151 - igi2_frame.vCurrentSquaredDistance1f;
          ptMatrix->tY.vZ = igi2_frame.vTd - igi2_frame.vXWd;
          ptMatrix->tZ.vX = *(float *)igi2_frame.aiNext - igi2_frame.vYWc;
          ptMatrix->tZ.vY = igi2_frame.vXWd + igi2_frame.vTd;
          nOps = igi2_frame.tFinalQuat.nOps;
          ptMatrix->tZ.vZ = v151 - igi2_frame.vBetae;
          ptMatrix->nOps = nOps;
          v67 = ptDisplacement;
          goto LABEL_124;
        }
        goto LABEL_125;
      }
      *(double *)igi2_frame.aiNext = *igi2_frame.v196 + ptSegment->tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos.vX;
      igi2_frame.tTempWorldPos1.vX = *(double *)igi2_frame.aiNext;
      igi2_frame.vBetab = *igi2_frame.v195 + ptSegment->tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos.vY;
      igi2_frame.tTempWorldPos1.vY = igi2_frame.vBetab;
      igi2_frame.vCurrentSquaredDistance1c = *igi2_frame.p_vZ + ptSegment->tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos.vZ;
      igi2_frame.tTempWorldPos1.vZ = igi2_frame.vCurrentSquaredDistance1c;
      if ( v67 )
      {
        v101 = (float *)(&ptSegment->tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask + v26);
        v102 = ptSegment->atAreaOrientation[v26 + 1].tX.vZ * v67->vZ + v101[158] * v67->vX + v101[159] * v67->vY;
        v103 = v101[163] * v67->vZ + v101[161] * v67->vX + v101[162] * v67->vY;
        igi2_frame.v215 = v101[166] * v67->vZ + v101[164] * v67->vX + v101[165] * v67->vY;
        igi2_frame.tTempWorldPos1.vX = v102 + igi2_frame.tTempWorldPos1.vX;
        igi2_frame.tTempWorldPos1.vY = v103 + igi2_frame.tTempWorldPos1.vY;
        igi2_frame.tTempWorldPos1.vZ = igi2_frame.v215 + igi2_frame.tTempWorldPos1.vZ;
      }
      if ( Real64x3_SquaredDistance(v71, &igi2_frame.tTempWorldPos1) > igi2_frame.vXW )
      {
        igi2_frame.vTb = (igi2_frame.vCurrentTailPointDistance - igi2_frame.vTempDistancea) / ptSegment->avAreaLength[v26];
        vX = *igi2_frame.v199 + ptSegment->tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos.vX;
        vY = *igi2_frame.v198 + ptSegment->tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos.vY;
        v104 = *igi2_frame.v197 + ptSegment->tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos.vZ;
        igi2_frame.tTempWorldPos1.vY = igi2_frame.vBetab;
        igi2_frame.tTempWorldPos0.vZ = v104;
        igi2_frame.tTempWorldPos1.vZ = igi2_frame.vCurrentSquaredDistance1c;
        v77 = *(double *)igi2_frame.aiNext;
        if ( v67 )
        {
          v105 = (float *)(&ptSegment->tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask + v26);
          v106 = ptSegment->atAreaOrientation[v26].tX.vZ * v67->vZ + v105[148] * v67->vX + v105[149] * v67->vY;
          igi2_frame.v210 = v105[153] * v67->vZ + v105[151] * v67->vX + v105[152] * v67->vY;
          igi2_frame.v211 = v105[156] * v67->vZ + v105[154] * v67->vX + v105[155] * v67->vY;
          vX = vX + v106;
          vY = vY + igi2_frame.v210;
          igi2_frame.tTempWorldPos0.vZ = igi2_frame.v211 + igi2_frame.tTempWorldPos0.vZ;
          v107 = ptSegment->atAreaOrientation[v26 + 1].tX.vZ * v67->vZ + v105[158] * v67->vX + v105[159] * v67->vY;
          igi2_frame.tTempPos.vY = v105[163] * v67->vZ + v105[161] * v67->vX + v105[162] * v67->vY;
          igi2_frame.tTempPos.vZ = v105[166] * v67->vZ + v105[164] * v67->vX + v105[165] * v67->vY;
          v77 = *(double *)igi2_frame.aiNext + v107;
          igi2_frame.tTempWorldPos1.vY = igi2_frame.tTempPos.vY + igi2_frame.tTempWorldPos1.vY;
          igi2_frame.tTempWorldPos1.vZ = igi2_frame.tTempPos.vZ + igi2_frame.tTempWorldPos1.vZ;
        }
        goto LABEL_102;
      }
      v81 = igi2_frame.vTempDistancea;
      while ( v26 < ptSegment->nAreas - 1 )
      {
        v81 = v81 + ptSegment->avAreaLength[v26++];
LABEL_94:
        v110 = (float *)((char *)ptSegment + 12 * v26);
        v111 = v110[85] + ptSegment->tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos.vX;
        igi2_frame.v199 = v110 + 85;
        igi2_frame.v198 = v110 + 86;
        igi2_frame.tTempWorldPos0.vX = v111;
        v112 = v110[86] + ptSegment->tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos.vY;
        igi2_frame.v197 = &ptSegment->atAreaPos[v26].vZ;
        igi2_frame.tTempWorldPos0.vY = v112;
        v113 = *igi2_frame.v197 + ptSegment->tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos.vZ;
        igi2_frame.v195 = v110 + 89;
        igi2_frame.tTempWorldPos0.vZ = v113;
        igi2_frame.v196 = v110 + 88;
        igi2_frame.tTempWorldPos1.vX = v110[88] + ptSegment->tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos.vX;
        v114 = v110[89] + ptSegment->tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos.vY;
        igi2_frame.p_vZ = &ptSegment->atAreaPos[v26 + 1].vZ;
        igi2_frame.tTempWorldPos1.vY = v114;
        igi2_frame.tTempWorldPos1.vZ = *igi2_frame.p_vZ + ptSegment->tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos.vZ;
        if ( v67 )
        {
          v115 = (float *)(&ptSegment->tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask + v26);
          v116 = ptSegment->atAreaOrientation[v26].tX.vZ * v67->vZ + v115[148] * v67->vX + v115[149] * v67->vY;
          v117 = v115[153] * v67->vZ + v115[151] * v67->vX + v115[152] * v67->vY;
          igi2_frame.v213 = v115[156] * v67->vZ + v115[154] * v67->vX + v115[155] * v67->vY;
          igi2_frame.tTempWorldPos0.vX = v111 + v116;
          v111 = igi2_frame.tTempWorldPos0.vX;
          igi2_frame.tTempWorldPos0.vY = v117 + igi2_frame.tTempWorldPos0.vY;
          igi2_frame.tTempWorldPos0.vZ = igi2_frame.v213 + igi2_frame.tTempWorldPos0.vZ;
          v118 = ptSegment->atAreaOrientation[v26 + 1].tX.vZ * v67->vZ + v115[158] * v67->vX + v115[159] * v67->vY;
          v119 = v115[163] * v67->vZ + v115[161] * v67->vX + v115[162] * v67->vY;
          igi2_frame.v212 = v115[166] * v67->vZ + v115[164] * v67->vX + v115[165] * v67->vY;
          igi2_frame.tTempWorldPos1.vX = v118 + igi2_frame.tTempWorldPos1.vX;
          igi2_frame.tTempWorldPos1.vY = v119 + igi2_frame.tTempWorldPos1.vY;
          igi2_frame.tTempWorldPos1.vZ = igi2_frame.v212 + igi2_frame.tTempWorldPos1.vZ;
        }
        v120 = (v71->vZ - igi2_frame.tTempWorldPos0.vZ) * (v71->vZ - igi2_frame.tTempWorldPos0.vZ)
             + (v71->vY - igi2_frame.tTempWorldPos0.vY) * (v71->vY - igi2_frame.tTempWorldPos0.vY)
             + (v71->vX - v111) * (v71->vX - v111);
        igi2_frame.vCurrentSquaredDistance1d = v120;
        *(float *)igi2_frame.aiNext = (v71->vZ - igi2_frame.tTempWorldPos1.vZ) * (v71->vZ - igi2_frame.tTempWorldPos1.vZ)
                         + (v71->vY - igi2_frame.tTempWorldPos1.vY) * (v71->vY - igi2_frame.tTempWorldPos1.vY)
                         + (v71->vX - igi2_frame.tTempWorldPos1.vX) * (v71->vX - igi2_frame.tTempWorldPos1.vX);
        if ( v120 > igi2_frame.vXW != *(float *)igi2_frame.aiNext > (double)igi2_frame.vXW )
        {
          igi2_frame.vTempDistancea = v81;
          igi2_frame.vXWb = ptSegment->avAreaLength[v26];
          igi2_frame.vYWa = sqrt(igi2_frame.vCurrentSquaredDistance1d);
          igi2_frame.xb = (*(float *)igi2_frame.aiNext - igi2_frame.vCurrentSquaredDistance1d - igi2_frame.vXWb * igi2_frame.vXWb) / (igi2_frame.vYWa * igi2_frame.vXWb * -2.0);
          v121 = Real32_Acos(igi2_frame.xb);
          igi2_frame.vCurrentSquaredDistance1e = sin(v121);
          igi2_frame.vBetad = 3.1415927410125732 - v121;
          igi2_frame.xc = igi2_frame.vCurrentSquaredDistance1e / igi2_frame.vTa * igi2_frame.vYWa;
          v122 = igi2_frame.vBetad - Real32_Asin(igi2_frame.xc);
          if ( v122 <= 0.001 )
            v123 = (igi2_frame.vTa - igi2_frame.vYWa) / (sqrt(*(float *)igi2_frame.aiNext) - igi2_frame.vYWa);
          else
            v123 = sin(v122) * igi2_frame.vTa / igi2_frame.vCurrentSquaredDistance1e / igi2_frame.vXWb;
          igi2_frame.vTb = v123;
          goto LABEL_101;
        }
      }
      v108 = (struct SplineObjWaypoint_s *)QTask_GetNextSiblingOfType(
                                             &igi2_frame.ptWaypoint->tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask,
                                             SplineObjWaypoint_eQTaskType);
      if ( v108 )
      {
        v109 = v108->ptSegment;
        if ( v109 )
          break;
      }
LABEL_118:
      igi2_frame.vTempDistancea = v81;
      if ( igi2_frame.vTa >= 0.0 )
      {
        v28->vX = ptSegment->atAreaPos[ptSegment->nAreas].vX
                + ptSegment->tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos.vX;
        v28->vY = ptSegment->atAreaPos[ptSegment->nAreas].vY
                + ptSegment->tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos.vY;
        v28->vZ = ptSegment->atAreaPos[ptSegment->nAreas].vZ
                + ptSegment->tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos.vZ;
        if ( !ptMatrix )
          goto LABEL_125;
        atAreaOrientation = &ptSegment->atAreaOrientation[ptSegment->nAreas];
      }
      else
      {
        v28->vX = ptSegment->atAreaPos[0].vX + ptSegment->tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos.vX;
        v28->vY = ptSegment->atAreaPos[0].vY + ptSegment->tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos.vY;
        v28->vZ = ptSegment->atAreaPos[0].vZ + ptSegment->tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos.vZ;
        if ( !ptMatrix )
          goto LABEL_125;
        atAreaOrientation = ptSegment->atAreaOrientation;
      }
      qmemcpy(ptMatrix, atAreaOrientation, sizeof(struct real32x9_t));
LABEL_124:
      v28 = (struct real64x3_t *)ptMatrixa;
LABEL_125:
      if ( ++igi2_frame.iPoint >= nNumTailPoints )
      {
LABEL_126:
        *pisValid = 1;
        return;
      }
    }
    v81 = v81 + ptSegment->avAreaLength[v26];
    igi2_frame.ptWaypoint = v108;
    ptSegment = v109;
    v26 = 0;
    goto LABEL_94;
  }
  avAreaLength = ptSegment->avAreaLength;
  while ( v9 < ptSegment->nAreas )
  {
    v21 = v21 + *avAreaLength;
    ++v9;
    ++avAreaLength;
    if ( v21 >= v13 )
      goto LABEL_34;
  }
  v41 = nNumTailPoints + 1;
  if ( nNumTailPoints + 1 > 0 )
  {
    v42 = ptPos;
    do
    {
      ++v42;
      v42[-1].vX = ptSegment->atAreaPos[ptSegment->nAreas].vX
                 + ptSegment->tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos.vX;
      v42[-1].vY = ptSegment->atAreaPos[ptSegment->nAreas].vY
                 + ptSegment->tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos.vY;
      --v41;
      v42[-1].vZ = ptSegment->atAreaPos[ptSegment->nAreas].vZ
                 + ptSegment->tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos.vZ;
    }
    while ( v41 );
  }
  if ( !ptMatrix )
    goto LABEL_126;
  qmemcpy(ptMatrix, &ptSegment->atAreaOrientation[ptSegment->nAreas], sizeof(struct real32x9_t));
  *pisValid = 1;
}

// source: h/2/splineobj.c:969  [size]
void *__cdecl SplineObjWaypoint_CollisionEvalHandler(
        struct QTask_s *ptQTask,
        void *pxContext)
{
  *(_BYTE *)pxContext = 0;
  return pxContext;
}

// source: h/2/splineobj.c:986  [anchor-mhash]
void __cdecl SplineObjWaypoint_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  unsigned __int16 v2; // cx
  struct QTask_s *PrevSiblingOfType; // eax
  struct QTask_s *v5; // edx
  struct QTask_s *NextSiblingOfType; // eax
  struct QTask_s *v7; // edx
  struct QTask_s **v8; // eax
  char v9; // cl
  struct QTask_s **v10; // eax
  char v11; // cl
  double v12; // st7
  double v13; // st6
  double v14; // st5
  long double v15; // st7
  long double v16; // rt1
  long double v17; // st5
  struct QTask_s *v18; // eax
  struct QTask_s *v19; // eax
  double v20; // st5
  double v21; // st7
  struct QTask_s **p_ptTail; // eax
  char v23; // cl
  struct QTask_s **p_ptParent; // eax
  char v25; // cl
  long double v26; // st7
  struct QTask_s *ptPrev; // eax
  long double v28; // st6
  long double v29; // st7
  long double v30; // rt2
  long double v31; // st6
  struct QTask_s *ptNext; // edx
  double v33; // st6
  long double v34; // st7
  double v35; // st6
  double v36; // st5
  struct LODVirModel_s *LODVirModelExistsFn; // eax
  struct QTask_s *v38; // ecx
  unsigned __int16 v39; // cx
  int v40; // edx
  struct QTask_s *v41; // eax
  char isUpdateNext; // [esp+13h] [ebp-11h]
  struct SplineObj_s *ptSplineObj; // [esp+14h] [ebp-10h]
  float tVector_4; // [esp+1Ch] [ebp-8h]
  float tVector_8; // [esp+20h] [ebp-4h]
  float tVector_8a; // [esp+20h] [ebp-4h]
  float tVector_8b; // [esp+20h] [ebp-4h]
  float ptQTaska = *(float *)&ptQTask; // [esp+28h] [ebp+4h] ARGSLOT

  v2 = SplineObjWaypoint_eQTaskType;
  ptSplineObj = (struct SplineObj_s *)ptQTask->ptParent;
  isUpdateNext = 0;
  PrevSiblingOfType = QTask_GetPrevSiblingOfType(ptQTask, SplineObjWaypoint_eQTaskType);
  v5 = PrevSiblingOfType;
  if ( PrevSiblingOfType )
  {
    p_ptTail = &PrevSiblingOfType[11].tQTaskChildren.ptTail;
    do
    {
      v23 = *(_BYTE *)p_ptTail;
      *((_BYTE *)p_ptTail + ((char *)ptQTask - (char *)v5)) = *(_BYTE *)p_ptTail;
      p_ptTail = (struct QTask_s **)((char *)p_ptTail + 1);
    }
    while ( v23 );
    p_ptParent = &v5[11].ptParent;
    do
    {
      v25 = *(_BYTE *)p_ptParent;
      *((_BYTE *)p_ptParent + ((char *)ptQTask - (char *)v5)) = *(_BYTE *)p_ptParent;
      p_ptParent = (struct QTask_s **)((char *)p_ptParent + 1);
    }
    while ( v25 );
    qmemcpy(&ptQTask[8].tQTaskChildren, &v5[8].tQTaskChildren, 0x18u);
    qmemcpy(&ptQTask[8].ptParent, &v5[8].ptParent, sizeof(struct QTask_s));
    v26 = *(float *)&ptQTask[8].ptParent;
    ptPrev = ptQTask[9].ptPrev;
    BYTE1(ptQTask[12].tQTaskChildren.ptTail) = BYTE1(v5[12].tQTaskChildren.ptTail);
    tVector_4 = *(float *)&ptPrev;
    BYTE1(ptQTask[12].tQTaskRefList.ptHead) = BYTE1(v5[12].tQTaskRefList.ptHead);
    tVector_8a = *(float *)&ptQTask[9].tQTaskChildren.ptTail;
    if ( v26 != 0.0 || *(float *)&ptPrev != 0.0 || tVector_8a != 0.0 )
    {
      v28 = v26;
      v29 = 1.0 / sqrt(v26 * v26 + *(float *)&ptPrev * *(float *)&ptPrev + tVector_8a * tVector_8a);
      v30 = v28 * v29;
      v31 = v29;
      v26 = v30;
      tVector_4 = *(float *)&ptPrev * v31;
      tVector_8a = tVector_8a * v31;
    }
    ptNext = v5[8].ptNext;
    if ( ptNext )
    {
      v33 = *(float *)&ptNext[8].tQTaskChildren.ptTail - *(float *)&ptNext[8].tQTaskChildren.ptMiddle;
      ptQTaska = v33;
      v34 = v26 * v33;
      v35 = ptQTaska * tVector_4;
      v36 = ptQTaska;
    }
    else
    {
      v34 = v26 * SplineObj_vDefaultSegmentLength;
      v35 = SplineObj_vDefaultSegmentLength * tVector_4;
      v36 = SplineObj_vDefaultSegmentLength;
    }
    tVector_8b = v36 * tVector_8a;
    *(long double *)&ptQTask[8].tQTaskChildren.ptHead = v34 + *(double *)&ptQTask[8].tQTaskChildren.ptHead;
    *(double *)&ptQTask[8].tQTaskChildren.ptTail = v35 + *(double *)&ptQTask[8].tQTaskChildren.ptTail;
    v21 = tVector_8b + *(double *)&ptQTask[8].tQTaskRefList.ptMiddle;
    goto LABEL_30;
  }
  NextSiblingOfType = QTask_GetNextSiblingOfType(ptQTask, v2);
  v7 = NextSiblingOfType;
  if ( !NextSiblingOfType )
  {
    LOBYTE(ptQTask[11].tQTaskChildren.ptTail) = 0;
    LOBYTE(ptQTask[11].ptParent) = 0;
    ptQTask[8].tQTaskChildren.ptHead = nullptr;
    ptQTask[8].tQTaskChildren.ptMiddle = nullptr;
    ptQTask[8].tQTaskChildren.ptTail = nullptr;
    ptQTask[8].tQTaskRefList.ptHead = nullptr;
    ptQTask[8].tQTaskRefList.ptMiddle = nullptr;
    ptQTask[8].tQTaskRefList.ptTail = nullptr;
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
    BYTE1(ptQTask[12].tQTaskChildren.ptTail) = 0;
    BYTE1(ptQTask[12].tQTaskRefList.ptHead) = 0;
    goto LABEL_31;
  }
  v8 = &NextSiblingOfType[11].tQTaskChildren.ptTail;
  do
  {
    v9 = *(_BYTE *)v8;
    *((_BYTE *)v8 + ((char *)ptQTask - (char *)v7)) = *(_BYTE *)v8;
    v8 = (struct QTask_s **)((char *)v8 + 1);
  }
  while ( v9 );
  v10 = &v7[11].ptParent;
  do
  {
    v11 = *(_BYTE *)v10;
    *((_BYTE *)v10 + ((char *)ptQTask - (char *)v7)) = *(_BYTE *)v10;
    v10 = (struct QTask_s **)((char *)v10 + 1);
  }
  while ( v11 );
  qmemcpy(&ptQTask[8].tQTaskChildren, &v7[8].tQTaskChildren, 0x18u);
  qmemcpy(&ptQTask[8].ptParent, &v7[8].ptParent, sizeof(struct QTask_s));
  v12 = *(float *)&ptQTask[8].ptParent;
  v13 = *(float *)&ptQTask[9].ptPrev;
  tVector_8 = *(float *)&ptQTask[9].tQTaskChildren.ptTail;
  BYTE1(ptQTask[12].tQTaskChildren.ptTail) = BYTE1(v7[12].tQTaskChildren.ptTail);
  if ( v12 != 0.0 || v13 != 0.0 || tVector_8 != 0.0 )
  {
    v14 = v12;
    v15 = 1.0 / sqrt(v12 * v12 + v13 * v13 + tVector_8 * tVector_8);
    v16 = v14 * v15;
    v17 = v15;
    v12 = v16;
    v13 = v13 * v17;
    tVector_8 = tVector_8 * v17;
  }
  v18 = QTask_GetNextSiblingOfType(v7, SplineObjWaypoint_eQTaskType);
  if ( !v18 )
  {
    v12 = v12 * SplineObj_vDefaultSegmentLength;
    v13 = v13 * SplineObj_vDefaultSegmentLength;
    v20 = SplineObj_vDefaultSegmentLength;
    goto LABEL_16;
  }
  v19 = v18[8].ptNext;
  if ( v19 )
  {
    v20 = *(float *)&v19[8].tQTaskChildren.ptTail - *(float *)&v19[8].tQTaskChildren.ptMiddle;
    v12 = v12 * v20;
    v13 = v13 * v20;
LABEL_16:
    tVector_8 = v20 * tVector_8;
  }
  isUpdateNext = 1;
  *(double *)&ptQTask[8].tQTaskChildren.ptHead = *(double *)&ptQTask[8].tQTaskChildren.ptHead - v12;
  *(double *)&ptQTask[8].tQTaskChildren.ptTail = *(double *)&ptQTask[8].tQTaskChildren.ptTail - v13;
  v21 = *(double *)&ptQTask[8].tQTaskRefList.ptMiddle - tVector_8;
LABEL_30:
  *(double *)&ptQTask[8].tQTaskRefList.ptMiddle = v21;
LABEL_31:
  ptQTask[8].ptNext = nullptr;
  BYTE2(ptQTask[12].tQTaskChildren.ptTail) = ptSplineObj->isLinear;
  ptQTask[12].tQTaskChildren.ptHead = (struct QTask_s *)ptSplineObj->nNumAreas;
  LOBYTE(ptQTask[12].tQTaskRefList.ptHead) = 0;
  LOBYTE(ptQTask[12].tQTaskChildren.ptTail) = 0;
  LODVirModelExistsFn = MTP_GetLODVirModelExistsFn((char *)&ptQTask[11].tQTaskChildren.ptTail);
  if ( !LODVirModelExistsFn )
    LODVirModelExistsFn = nullptr;
  ModelObj_Init((struct ModelObj_s *)ptQTask, World_ptActiveWorld, LODVirModelExistsFn);
  v38 = (struct QTask_s *)World_ptActiveWorld;
  ptQTask[7].tQTaskChildren.ptHead = nullptr;
  ptQTask[7].tQTaskChildren.ptMiddle = (struct QTask_s *)2;
  ptQTask[7].tQTaskRefList.ptHead = nullptr;
  ptQTask[7].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[7].tQTaskRefList.ptTail = nullptr;
  ptQTask[7].ptParent = nullptr;
  *(_DWORD *)&ptQTask[7].eQTaskType = 0;
  ptQTask[12].tQTaskChildren.ptMiddle = v38;
  if ( isUpdateNext )
  {
    v39 = SplineObjWaypoint_eQTaskType;
    v40 = 511 * ParameterList_eUpdateInternalDataQTaskEvent
        + QTask_GetNextSiblingOfType(ptQTask, SplineObjWaypoint_eQTaskType)->eQTaskType;
    v41 = QTask_GetNextSiblingOfType(ptQTask, v39);
    ((void (__cdecl *)(struct QTask_s *, _DWORD))QTask_aatQTaskFinalEvent[0][v40].pfHandler)(v41, 0);
  }
}

// source: h/2/splineobj.c:1127  [anchor-mhash]
void __cdecl SplineObjWaypoint_DeleteHandler(struct QTask_s *ptQTask)
{
  unsigned __int16 v1; // cx
  struct QTask_s *NextSiblingOfType; // edi
  struct QTask_s *PrevSiblingOfType; // ebp
  struct QTask_s *FirstChildOfType; // eax
  char v6; // al
  struct QTask_s *ptQTaska = *(struct QTask_s * *)&ptQTask; // [esp+10h] [ebp+4h] ARGSLOT

  v1 = SplineObjWaypoint_eQTaskType;
  ptQTaska = ptQTask->ptParent;
  NextSiblingOfType = QTask_GetNextSiblingOfType(ptQTask, SplineObjWaypoint_eQTaskType);
  PrevSiblingOfType = QTask_GetPrevSiblingOfType(ptQTask, v1);
  FirstChildOfType = QTask_GetFirstChildOfType(ptQTask, v1);
  ptQTask[8].ptNext = FirstChildOfType;
  if ( FirstChildOfType )
    QTask_Delete(FirstChildOfType);
  if ( PrevSiblingOfType )
  {
    if ( NextSiblingOfType )
    {
      v6 = BYTE2(NextSiblingOfType[12].tQTaskChildren.ptTail) || BYTE1(NextSiblingOfType[12].tQTaskChildren.ptTail);
      SplineObjSegment_Update(
        (struct SplineObjSegment_s *)NextSiblingOfType[8].ptNext,
        (struct real64x3_t *)&PrevSiblingOfType[8].tQTaskChildren,
        (struct real64x3_t *)&NextSiblingOfType[8].tQTaskChildren,
        (struct real32x9_t *)&PrevSiblingOfType[8].ptParent,
        (struct real32x9_t *)&NextSiblingOfType[8].ptParent,
        v6,
        (char)NextSiblingOfType[12].tQTaskRefList.ptHead,
        (int)NextSiblingOfType[12].tQTaskChildren.ptHead,
        (int)ptQTaska[1].ptNext,
        (char *)&NextSiblingOfType[11].ptParent);
    }
  }
  else if ( NextSiblingOfType )
  {
    QTask_Delete(NextSiblingOfType[8].ptNext);
    NextSiblingOfType[8].ptNext = nullptr;
  }
  if ( LOBYTE(ptQTask[12].tQTaskChildren.ptTail) )
    World_RemoveDynCubeObj((struct World_s *)ptQTask[12].tQTaskChildren.ptMiddle, (struct DynCubeObj_s *)ptQTask);
}

// source: h/2/splineobj.c:1194  [anchor-mhash]
void __cdecl SplineObjWaypoint_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct DynCubeObj_s *ptDynCubeObj; };
    struct { char igi2_o1[24]; struct SplineObjWaypoint_s *ptPrevWaypoint; };
    struct { char igi2_o2[28]; struct SplineObj_s *ptSplineObj; };
    struct { char igi2_o3[32]; struct SplineObjWaypoint_s *ptWaypoint; };
    struct { char igi2_o4[36]; struct SplineObjWaypoint_s *ptFirstWaypoint; };
    struct { char igi2_o5[40]; int nNumSegments; };
    struct { char igi2_o6[44]; struct real64x3_t *ptEndPos; };
    struct { char igi2_o7[48]; double vScale[3]; };
    struct { char igi2_o8[72]; struct real32x3_t tTemp; };
    struct { char igi2_o9[88]; struct real32x9_t Real32x9_Normalize_tTemp; };
    char igi2_extent[128];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  unsigned __int16 v2; // cx
  struct SplineObjWaypoint_s *v3; // ebx
  struct SplineObjWaypoint_s *NextSiblingOfType; // esi
  struct SplineObjWaypoint_s *PrevSiblingOfType; // eax
  struct SplineObj_s *ptParent; // edi
  double v7; // st7
  double v8; // st6
  double v9; // st7
  double v10; // st6
  float *p_ptParent; // edx
  double v12; // st7
  double v13; // st6
  long double v14; // st7
  float *p_ptTail; // ecx
  double v16; // st7
  double v17; // st7
  float v18; // esi
  long double v19; // st4
  double v20; // st7
  double v21; // st6
  long double v22; // st4
  long double v23; // st7
  char v24; // cl
  int ptHead; // ecx
  int nNumAreas; // edx
  int v27; // esi
  struct QTask_s *ptNext; // ecx
  double v29; // st7
  double v30; // st6
  double v31; // st5
  double v32; // st2
  long double v33; // st1
  long double v34; // st2
  double v35; // rtt
  long double v36; // st6
  char isDisplayWaypoints; // al
  double v38; // st7
  double v39; // st7
  int *v40; // eax
  int v41; // eax
  double v42; // st6
  char ptTail; // al
  struct LODVirModel_s *LODVirModelExistsFn; // eax
  struct QTask_s **v45; // eax
  char v46; // cl
  int *v47; // eax
  int v48; // eax
  struct SplineObjSegment_s *v49; // esi
  char v50; // al
  char v51; // al
  char v52; // al
  struct SplineObjWaypoint_s *v53; // eax
  struct SplineObjSegment_s *ptSegment; // esi
  char v55; // cl
  char isAligned; // cl
  int v57; // edi
  struct SplineObjWaypoint_s *v58; // esi
  struct SplineObjWaypoint_s *v59; // eax
  struct SplineObjWaypoint_s *v60; // esi
  unsigned __int16 v61; // cx
  struct SplineObjWaypoint_s *v62; // eax
  double v63; // st7
  double vY; // st6
  double v65; // st6
  double v66; // st5
  struct SplineObjSegment_s *v67; // edi
  struct QTask_s *v68; // eax
  char v69; // cl
  struct SplineObjWaypoint_s *v70; // eax
  struct LODVirModel_s *ptLODVirModel; // eax
  struct VirModel_s *v72; // eax
  struct SplineObjSegment_s *v73; // edi
  struct QTask_s *v74; // eax
  char v75; // cl
  struct SplineObjWaypoint_s *v76; // eax
  struct SplineObjSegment_s *v77; // edi
  struct QTask_s *v78; // eax
  char v79; // cl
  struct QTask_s *v80; // eax
  struct SplineObjSegment_s *v81; // esi
  char v82; // cl
  unsigned __int16 v83; // dx
  struct QTask_s *FirstChildOfType; // eax
  struct QTask_s *i; // eax
  struct QTask_s *v86; // ecx

  v2 = SplineObjWaypoint_eQTaskType;
  v3 = (struct SplineObjWaypoint_s *)ptQTask;
  NextSiblingOfType = (struct SplineObjWaypoint_s *)QTask_GetNextSiblingOfType(ptQTask, SplineObjWaypoint_eQTaskType);
  igi2_frame.ptWaypoint = NextSiblingOfType;
  PrevSiblingOfType = (struct SplineObjWaypoint_s *)QTask_GetPrevSiblingOfType(ptQTask, v2);
  ptParent = (struct SplineObj_s *)ptQTask->ptParent;
  igi2_frame.ptPrevWaypoint = PrevSiblingOfType;
  igi2_frame.ptSplineObj = ptParent;
  if ( (ptParent->isAutoOrientation || BYTE1(ptQTask[12].tQTaskRefList.ptHead))
    && (PrevSiblingOfType || NextSiblingOfType) )
  {
    if ( ptParent->isLinear )
      goto LABEL_37;
    memset(igi2_frame.vScale, 0, 12);
    if ( PrevSiblingOfType )
    {
      v7 = *(double *)&ptQTask[8].tQTaskChildren.ptHead - PrevSiblingOfType->tPos.vX;
      v8 = *(double *)&ptQTask[8].tQTaskChildren.ptTail - PrevSiblingOfType->tPos.vY;
      igi2_frame.tTemp.vZ = *(double *)&ptQTask[8].tQTaskRefList.ptMiddle - PrevSiblingOfType->tPos.vZ;
      *(float *)igi2_frame.vScale = v7;
      *(float *)&igi2_frame.vScale[1] = igi2_frame.tTemp.vZ;
      *((float *)igi2_frame.vScale + 1) = v8;
    }
    if ( NextSiblingOfType )
    {
      v9 = NextSiblingOfType->tPos.vX - *(double *)&ptQTask[8].tQTaskChildren.ptHead;
      v10 = NextSiblingOfType->tPos.vY - *(double *)&ptQTask[8].tQTaskChildren.ptTail;
      igi2_frame.tTemp.vZ = NextSiblingOfType->tPos.vZ - *(double *)&ptQTask[8].tQTaskRefList.ptMiddle;
      *(float *)igi2_frame.vScale = v9 + *(float *)igi2_frame.vScale;
      *((float *)igi2_frame.vScale + 1) = v10 + *((float *)igi2_frame.vScale + 1);
      *(float *)&igi2_frame.vScale[1] = igi2_frame.tTemp.vZ + *(float *)&igi2_frame.vScale[1];
    }
    if ( *(float *)igi2_frame.vScale == 0.0 && *((float *)igi2_frame.vScale + 1) == 0.0 && *(float *)&igi2_frame.vScale[1] == 0.0 )
    {
      p_ptParent = (float *)&ptQTask[8].ptParent;
      ptQTask[8].ptParent = (struct QTask_s *)1065353216;
      *(_DWORD *)&ptQTask[8].eQTaskType = 0;
      ptQTask[9].ptNext = nullptr;
    }
    else
    {
      p_ptParent = (float *)&ptQTask[8].ptParent;
      *(double *)&ptQTask[8].ptParent = igi2_frame.vScale[0];
      ptQTask[9].ptNext = (struct QTask_s *)LODWORD(igi2_frame.vScale[1]);
    }
    if ( *p_ptParent == 0.0 && *(float *)&ptQTask[8].eQTaskType == 0.0 )
    {
      ptQTask[9].ptPrev = nullptr;
      ptQTask[9].tQTaskChildren.ptHead = (struct QTask_s *)1065353216;
      ptQTask[9].tQTaskChildren.ptMiddle = nullptr;
    }
    else
    {
      v12 = *(float *)&ptQTask[8].eQTaskType;
      ptQTask[9].tQTaskChildren.ptMiddle = nullptr;
      *(float *)&ptQTask[9].ptPrev = v12;
      *(float *)&igi2_frame.nNumSegments = -*p_ptParent;
      ptQTask[9].tQTaskChildren.ptHead = (struct QTask_s *)igi2_frame.nNumSegments;
      if ( v12 != 0.0 || *(float *)&igi2_frame.nNumSegments != 0.0 )
      {
        v13 = v12;
        v14 = 1.0 / sqrt(v12 * v12 + *(float *)&igi2_frame.nNumSegments * *(float *)&igi2_frame.nNumSegments);
        *(float *)&ptQTask[9].ptPrev = v13 * v14;
        *(float *)&ptQTask[9].tQTaskChildren.ptHead = *(float *)&igi2_frame.nNumSegments * v14;
        *(float *)&ptQTask[9].tQTaskChildren.ptMiddle = v14 * 0.0;
      }
    }
    p_ptTail = (float *)&ptQTask[9].tQTaskChildren.ptTail;
    igi2_frame.tTemp.vX = *(float *)&ptQTask[9].tQTaskChildren.ptHead * *(float *)&ptQTask[9].ptNext
             - *(float *)&ptQTask[9].tQTaskChildren.ptMiddle * *(float *)&ptQTask[8].eQTaskType;
    v16 = *(float *)&ptQTask[9].ptPrev * *(float *)&ptQTask[9].ptNext;
    ptQTask[9].tQTaskChildren.ptTail = (struct QTask_s *)LODWORD(igi2_frame.tTemp.vX);
    igi2_frame.tTemp.vY = -(v16 - *(float *)&ptQTask[9].tQTaskChildren.ptMiddle * *p_ptParent);
    v17 = *(float *)&ptQTask[9].ptPrev;
    ptQTask[9].tQTaskRefList.ptHead = (struct QReference_s *)LODWORD(igi2_frame.tTemp.vY);
    igi2_frame.tTemp.vZ = v17 * *(float *)&ptQTask[8].eQTaskType - *(float *)&ptQTask[9].tQTaskChildren.ptHead * *p_ptParent;
    ptQTask[9].tQTaskRefList.ptMiddle = (struct QReference_s *)LODWORD(igi2_frame.tTemp.vZ);
    igi2_frame.Real32x9_Normalize_tTemp.tX.vX = *p_ptParent;
    v18 = p_ptParent[1];
    igi2_frame.Real32x9_Normalize_tTemp.tX.vZ = p_ptParent[2];
    igi2_frame.Real32x9_Normalize_tTemp.tX.vY = v18;
    if ( igi2_frame.Real32x9_Normalize_tTemp.tX.vX != 0.0
      || igi2_frame.Real32x9_Normalize_tTemp.tX.vY != 0.0
      || igi2_frame.Real32x9_Normalize_tTemp.tX.vZ != 0.0 )
    {
      v19 = sqrt(
              igi2_frame.Real32x9_Normalize_tTemp.tX.vX * igi2_frame.Real32x9_Normalize_tTemp.tX.vX
            + igi2_frame.Real32x9_Normalize_tTemp.tX.vY * igi2_frame.Real32x9_Normalize_tTemp.tX.vY
            + igi2_frame.Real32x9_Normalize_tTemp.tX.vZ * igi2_frame.Real32x9_Normalize_tTemp.tX.vZ);
      igi2_frame.Real32x9_Normalize_tTemp.tX.vX = igi2_frame.Real32x9_Normalize_tTemp.tX.vX * (1.0 / v19);
      igi2_frame.Real32x9_Normalize_tTemp.tX.vY = igi2_frame.Real32x9_Normalize_tTemp.tX.vY * (1.0 / v19);
      igi2_frame.Real32x9_Normalize_tTemp.tX.vZ = igi2_frame.Real32x9_Normalize_tTemp.tX.vZ * (1.0 / v19);
    }
    *(float *)igi2_frame.vScale = *(float *)&ptQTask[9].tQTaskRefList.ptHead * *(float *)&ptQTask[9].ptNext
                     - *(float *)&ptQTask[8].eQTaskType * *(float *)&ptQTask[9].tQTaskRefList.ptMiddle;
    *((float *)igi2_frame.vScale + 1) = -(*(float *)&ptQTask[9].ptNext * *p_ptTail
                             - *p_ptParent * *(float *)&ptQTask[9].tQTaskRefList.ptMiddle);
    v20 = *(float *)&ptQTask[8].eQTaskType * *p_ptTail;
    v21 = *(float *)&ptQTask[9].tQTaskRefList.ptHead;
    *(double *)&igi2_frame.Real32x9_Normalize_tTemp.tY.vX = igi2_frame.vScale[0];
    *(float *)&igi2_frame.vScale[1] = v20 - v21 * *p_ptParent;
    igi2_frame.Real32x9_Normalize_tTemp.tY.vZ = *(float *)&igi2_frame.vScale[1];
    igi2_frame.tTemp.vX = *(float *)&igi2_frame.vScale[1] * igi2_frame.Real32x9_Normalize_tTemp.tX.vY
             - *((float *)igi2_frame.vScale + 1) * igi2_frame.Real32x9_Normalize_tTemp.tX.vZ;
    igi2_frame.tTemp.vY = -(*(float *)&igi2_frame.vScale[1] * igi2_frame.Real32x9_Normalize_tTemp.tX.vX
               - *(float *)igi2_frame.vScale * igi2_frame.Real32x9_Normalize_tTemp.tX.vZ);
    igi2_frame.tTemp.vZ = *((float *)igi2_frame.vScale + 1) * igi2_frame.Real32x9_Normalize_tTemp.tX.vX
             - *(float *)igi2_frame.vScale * igi2_frame.Real32x9_Normalize_tTemp.tX.vY;
    igi2_frame.Real32x9_Normalize_tTemp.tZ = igi2_frame.tTemp;
    if ( *(float *)igi2_frame.vScale != 0.0 || *((float *)igi2_frame.vScale + 1) != 0.0 || *(float *)&igi2_frame.vScale[1] != 0.0 )
    {
      v22 = sqrt(
              *(float *)&igi2_frame.vScale[1] * *(float *)&igi2_frame.vScale[1]
            + *((float *)igi2_frame.vScale + 1) * *((float *)igi2_frame.vScale + 1)
            + *(float *)igi2_frame.vScale * *(float *)igi2_frame.vScale);
      igi2_frame.Real32x9_Normalize_tTemp.tY.vX = *(float *)igi2_frame.vScale * (1.0 / v22);
      igi2_frame.Real32x9_Normalize_tTemp.tY.vY = igi2_frame.Real32x9_Normalize_tTemp.tY.vY * (1.0 / v22);
      igi2_frame.Real32x9_Normalize_tTemp.tY.vZ = igi2_frame.Real32x9_Normalize_tTemp.tY.vZ * (1.0 / v22);
    }
    if ( igi2_frame.tTemp.vX != 0.0 || igi2_frame.tTemp.vY != 0.0 || igi2_frame.tTemp.vZ != 0.0 )
    {
      v23 = 1.0 / sqrt(igi2_frame.tTemp.vX * igi2_frame.tTemp.vX + igi2_frame.tTemp.vY * igi2_frame.tTemp.vY + igi2_frame.tTemp.vZ * igi2_frame.tTemp.vZ);
      igi2_frame.Real32x9_Normalize_tTemp.tZ.vX = igi2_frame.tTemp.vX * v23;
      igi2_frame.Real32x9_Normalize_tTemp.tZ.vY = igi2_frame.Real32x9_Normalize_tTemp.tZ.vY * v23;
      igi2_frame.Real32x9_Normalize_tTemp.tZ.vZ = igi2_frame.Real32x9_Normalize_tTemp.tZ.vZ * v23;
    }
    qmemcpy(p_ptParent, &igi2_frame.Real32x9_Normalize_tTemp, 0x28u);
    igi2_frame.Real32x9_Normalize_tTemp.tX.vX = *p_ptParent;
    LODWORD(igi2_frame.Real32x9_Normalize_tTemp.tX.vY) = ptQTask[9].ptPrev;
    LODWORD(igi2_frame.Real32x9_Normalize_tTemp.tX.vZ) = ptQTask[9].tQTaskChildren.ptTail;
    igi2_frame.Real32x9_Normalize_tTemp.tY.vX = *(float *)&ptQTask[8].eQTaskType;
    LODWORD(igi2_frame.Real32x9_Normalize_tTemp.tY.vY) = ptQTask[9].tQTaskChildren.ptHead;
    LODWORD(igi2_frame.Real32x9_Normalize_tTemp.tY.vZ) = ptQTask[9].tQTaskRefList.ptHead;
    LODWORD(igi2_frame.Real32x9_Normalize_tTemp.tZ.vX) = ptQTask[9].ptNext;
    LODWORD(igi2_frame.Real32x9_Normalize_tTemp.tZ.vY) = ptQTask[9].tQTaskChildren.ptMiddle;
    LODWORD(igi2_frame.Real32x9_Normalize_tTemp.tZ.vZ) = ptQTask[9].tQTaskRefList.ptMiddle;
    ptQTask[9].tQTaskRefList.ptTail = nullptr;
    igi2_frame.Real32x9_Normalize_tTemp.nOps = 0;
    qmemcpy(p_ptParent, &igi2_frame.Real32x9_Normalize_tTemp, 0x28u);
  }
  if ( !ptParent->isLinear && !BYTE1(ptQTask[12].tQTaskChildren.ptTail) )
  {
    v24 = 0;
    goto LABEL_38;
  }
LABEL_37:
  v24 = 1;
LABEL_38:
  BYTE2(ptQTask[12].tQTaskChildren.ptTail) = v24;
  ptHead = (int)ptQTask[12].tQTaskChildren.ptHead;
  nNumAreas = ptParent->nNumAreas;
  v27 = ptHead;
  if ( ptHead >= nNumAreas )
    v27 = ptParent->nNumAreas;
  if ( v27 <= 20 )
  {
    if ( ptHead >= nNumAreas )
      ptHead = ptParent->nNumAreas;
  }
  else
  {
    ptHead = 20;
  }
  ptQTask[12].tQTaskChildren.ptHead = (struct QTask_s *)ptHead;
  if ( ptParent->isSnapLength )
  {
    if ( PrevSiblingOfType )
    {
      ptNext = ptQTask[8].ptNext;
      if ( ptNext )
      {
        v29 = *(double *)&ptQTask[8].tQTaskChildren.ptHead - PrevSiblingOfType->tPos.vX;
        v30 = *(double *)&ptQTask[8].tQTaskChildren.ptTail - PrevSiblingOfType->tPos.vY;
        v31 = *(double *)&ptQTask[8].tQTaskRefList.ptMiddle - PrevSiblingOfType->tPos.vZ;
        igi2_frame.tTemp.vZ = v31;
        v32 = *(float *)&ptNext[8].tQTaskChildren.ptTail - *(float *)&ptNext[8].tQTaskChildren.ptMiddle;
        v33 = sqrt(v29 * v29 + v30 * v30 + v31 * v31);
        *(float *)&igi2_frame.ptEndPos = v33;
        v34 = v32 / v33;
        igi2_frame.vScale[0] = v34;
        v35 = v30;
        igi2_frame.tTemp.vX = v29 * v34;
        v36 = igi2_frame.tTemp.vZ * v34;
        *(double *)&ptQTask[8].tQTaskChildren.ptHead = igi2_frame.tTemp.vX + PrevSiblingOfType->tPos.vX;
        *(long double *)&ptQTask[8].tQTaskChildren.ptTail = v35 * v34 + PrevSiblingOfType->tPos.vY;
        *(long double *)&ptQTask[8].tQTaskRefList.ptMiddle = v36 + PrevSiblingOfType->tPos.vZ;
      }
    }
  }
  isDisplayWaypoints = ptParent->isDisplayWaypoints;
  if ( LOBYTE(ptQTask[12].tQTaskChildren.ptTail) )
  {
    if ( !isDisplayWaypoints )
    {
      World_RemoveDynCubeObj((struct World_s *)ptQTask[2].ptParent, (struct DynCubeObj_s *)ptQTask);
      LOBYTE(ptQTask[12].tQTaskChildren.ptTail) = 0;
    }
  }
  else if ( isDisplayWaypoints )
  {
    if ( *(float *)&ptQTask[6].tQTaskChildren.ptHead <= (double)*(float *)&ptQTask[6].tQTaskChildren.ptMiddle )
      v38 = *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
    else
      v38 = *(float *)&ptQTask[6].tQTaskChildren.ptHead;
    if ( v38 >= *(float *)&ptQTask[6].ptPrev )
    {
      if ( *(float *)&ptQTask[6].tQTaskChildren.ptHead <= (double)*(float *)&ptQTask[6].tQTaskChildren.ptMiddle )
        v39 = *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
      else
        v39 = *(float *)&ptQTask[6].tQTaskChildren.ptHead;
    }
    else
    {
      v39 = *(float *)&ptQTask[6].ptPrev;
    }
    v40 = *(int **)&ptQTask[2].eQTaskType;
    if ( v40 && (v41 = *v40) != 0 )
      v42 = *(float *)(*(_DWORD *)(*(_DWORD *)(v41 + 12) + 12) + 120);
    else
      v42 = 1.0;
    *(float *)&igi2_frame.ptDynCubeObj = v39 * v42;
    World_RegisterDynCubeObjFirstTimeRadius(
      World_ptActiveWorld,
      (struct DynCubeObj_s *)ptQTask,
      (struct real64x3_t *)&ptQTask[8].tQTaskChildren,
      *(float *)&igi2_frame.ptDynCubeObj,
      WORLD_DYNCUBETREE_CATEGORY_STATIONARY);
    LOBYTE(ptQTask[12].tQTaskChildren.ptTail) = 1;
  }
  ptTail = (char)ptQTask[11].tQTaskChildren.ptTail;
  igi2_frame.nNumSegments = (int)&ptQTask[8].ptParent;
  qmemcpy(&ptQTask[3].ptPrev, &ptQTask[8].ptParent, sizeof(struct QTask_s));
  if ( ptTail != 42 && ptTail )
  {
    LODVirModelExistsFn = MTP_GetLODVirModelExistsFn((char *)&ptQTask[11].tQTaskChildren.ptTail);
    if ( LODVirModelExistsFn )
    {
      *(_DWORD *)&ptQTask[2].eQTaskType = LODVirModelExistsFn;
    }
    else
    {
      v45 = &ptQTask[11].tQTaskChildren.ptTail;
      do
      {
        v46 = *(_BYTE *)v45;
        *((_BYTE *)v45 + ((char *)&igi2_frame.tTemp - (char *)&ptQTask[11].tQTaskChildren.ptTail)) = *(_BYTE *)v45;
        v45 = (struct QTask_s **)((char *)v45 + 1);
      }
      while ( v46 );
      sprintf((char *const)&ptQTask[11].tQTaskChildren.ptTail, "*%s", (char *)&igi2_frame.tTemp);
    }
  }
  if ( LOBYTE(ptQTask[12].tQTaskChildren.ptTail) )
  {
    v47 = *(int **)&ptQTask[2].eQTaskType;
    if ( v47 && (v48 = *v47) != 0 )
      World_MoveDynCubeObjRadius(
        (struct World_s *)ptQTask[12].tQTaskChildren.ptMiddle,
        (struct DynCubeObj_s *)ptQTask,
        (struct real64x3_t *)&ptQTask[8].tQTaskChildren,
        *(float *)(*(_DWORD *)(*(_DWORD *)(v48 + 12) + 12) + 120));
    else
      World_MoveDynCubeObjRadius(
        (struct World_s *)ptQTask[12].tQTaskChildren.ptMiddle,
        (struct DynCubeObj_s *)ptQTask,
        (struct real64x3_t *)&ptQTask[8].tQTaskChildren,
        1.0);
  }
  if ( igi2_frame.ptPrevWaypoint )
  {
    v49 = (struct SplineObjSegment_s *)ptQTask[8].ptNext;
    v50 = BYTE2(ptQTask[12].tQTaskChildren.ptTail);
    if ( v49 )
    {
      v52 = v50 || BYTE1(ptQTask[12].tQTaskChildren.ptTail);
      SplineObjSegment_Update(
        v49,
        &igi2_frame.ptPrevWaypoint->tPos,
        (struct real64x3_t *)&ptQTask[8].tQTaskChildren,
        &igi2_frame.ptPrevWaypoint->tOrientation,
        (struct real32x9_t *)igi2_frame.nNumSegments,
        v52,
        (char)ptQTask[12].tQTaskRefList.ptHead,
        (int)ptQTask[12].tQTaskChildren.ptHead,
        ptParent->iCollisionLOD,
        (char *)&ptQTask[11].ptParent);
      v3 = (struct SplineObjWaypoint_s *)ptQTask;
    }
    else
    {
      v51 = v50 || BYTE1(ptQTask[12].tQTaskChildren.ptTail);
      ptQTask[8].ptNext = (struct QTask_s *)SplineObjSegment_New(
                                              ptQTask,
                                              (struct World_s *)ptQTask[12].tQTaskChildren.ptMiddle,
                                              &igi2_frame.ptPrevWaypoint->tPos,
                                              (struct real64x3_t *)&ptQTask[8].tQTaskChildren,
                                              &igi2_frame.ptPrevWaypoint->tOrientation,
                                              (struct real32x9_t *)igi2_frame.nNumSegments,
                                              v51,
                                              (char)ptQTask[12].tQTaskRefList.ptHead,
                                              (int)ptQTask[12].tQTaskChildren.ptHead,
                                              ptParent->iCollisionLOD,
                                              (char *)&ptQTask[11].ptParent);
    }
  }
  else if ( ptQTask[8].ptNext )
  {
    QTask_Delete(ptQTask[8].ptNext);
    ptQTask[8].ptNext = nullptr;
  }
  v53 = igi2_frame.ptWaypoint;
  if ( igi2_frame.ptWaypoint )
  {
    ptSegment = igi2_frame.ptWaypoint->ptSegment;
    if ( ptSegment )
    {
      v55 = igi2_frame.ptWaypoint->isLinear || igi2_frame.ptWaypoint->isAligned;
      SplineObjSegment_Update(
        ptSegment,
        &v3->tPos,
        &igi2_frame.ptWaypoint->tPos,
        (struct real32x9_t *)igi2_frame.nNumSegments,
        &igi2_frame.ptWaypoint->tOrientation,
        v55,
        igi2_frame.ptWaypoint->isFlip,
        igi2_frame.ptWaypoint->nNumAreas,
        ptParent->iCollisionLOD,
        igi2_frame.ptWaypoint->zSegmentModel);
      v53 = igi2_frame.ptWaypoint;
      v3 = (struct SplineObjWaypoint_s *)ptQTask;
    }
  }
  isAligned = v3->isAligned;
  if ( !isAligned )
  {
    if ( !v53 || !igi2_frame.ptWaypoint->isAligned )
      goto LABEL_147;
    v53 = igi2_frame.ptWaypoint;
  }
  *(float *)&v57 = 0.0;
  *(float *)&igi2_frame.nNumSegments = 0.0;
  if ( isAligned )
  {
    v58 = v3;
    igi2_frame.ptPrevWaypoint = v3;
  }
  else
  {
    v58 = v53;
    igi2_frame.ptPrevWaypoint = v53;
  }
  igi2_frame.ptFirstWaypoint = v58;
  v59 = (struct SplineObjWaypoint_s *)QTask_GetPrevSiblingOfType(
                                        &v58->tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask,
                                        SplineObjWaypoint_eQTaskType);
  if ( v58->isAligned )
  {
    do
    {
      if ( !v59 )
        break;
      v60 = v59;
      igi2_frame.ptFirstWaypoint = v59;
      v59 = (struct SplineObjWaypoint_s *)QTask_GetPrevSiblingOfType(
                                            &v59->tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask,
                                            SplineObjWaypoint_eQTaskType);
      ++v57;
    }
    while ( v60->isAligned );
    igi2_frame.nNumSegments = v57;
  }
  v61 = SplineObjWaypoint_eQTaskType;
  v62 = (struct SplineObjWaypoint_s *)QTask_GetNextSiblingOfType(
                                        &igi2_frame.ptPrevWaypoint->tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask,
                                        SplineObjWaypoint_eQTaskType);
  if ( v62 )
  {
    do
    {
      if ( !v62->isAligned )
        break;
      igi2_frame.ptPrevWaypoint = v62;
      v62 = (struct SplineObjWaypoint_s *)QTask_GetNextSiblingOfType(
                                            &v62->tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask,
                                            v61);
      ++v57;
    }
    while ( v62 );
    igi2_frame.nNumSegments = v57;
  }
  if ( igi2_frame.ptFirstWaypoint != igi2_frame.ptPrevWaypoint )
  {
    igi2_frame.ptWaypoint = (struct SplineObjWaypoint_s *)QTask_GetNextSiblingOfType(
                                                 &igi2_frame.ptFirstWaypoint->tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask,
                                                 SplineObjWaypoint_eQTaskType);
    v63 = igi2_frame.ptPrevWaypoint->tPos.vX - igi2_frame.ptFirstWaypoint->tPos.vX;
    vY = igi2_frame.ptPrevWaypoint->tPos.vY;
    igi2_frame.ptEndPos = &igi2_frame.ptPrevWaypoint->tPos;
    v65 = vY - igi2_frame.ptFirstWaypoint->tPos.vY;
    igi2_frame.tTemp.vZ = igi2_frame.ptPrevWaypoint->tPos.vZ - igi2_frame.ptFirstWaypoint->tPos.vZ;
    v66 = 1.0 / (double)igi2_frame.nNumSegments;
    *(float *)&igi2_frame.nNumSegments = v66;
    igi2_frame.tTemp.vX = v66 * v63;
    igi2_frame.tTemp.vY = *(float *)&igi2_frame.nNumSegments * v65;
    igi2_frame.tTemp.vZ = *(float *)&igi2_frame.nNumSegments * igi2_frame.tTemp.vZ;
    Real32x3_GetAngles(&igi2_frame.tTemp, (float *)igi2_frame.vScale, (float *)&igi2_frame.nNumSegments);
    Real32x9_Create(&igi2_frame.Real32x9_Normalize_tTemp, 0.0, *(float *)igi2_frame.vScale, *(float *)&igi2_frame.nNumSegments);
    qmemcpy(igi2_frame.vScale, &igi2_frame.ptFirstWaypoint->tPos, sizeof(igi2_frame.vScale));
    qmemcpy(&igi2_frame.ptFirstWaypoint->tOrientation, &igi2_frame.Real32x9_Normalize_tTemp, sizeof(igi2_frame.ptFirstWaypoint->tOrientation));
    qmemcpy(
      &igi2_frame.ptFirstWaypoint->tRigidDynCubeObj.tModelObj.tOrientation,
      &igi2_frame.Real32x9_Normalize_tTemp,
      sizeof(igi2_frame.ptFirstWaypoint->tRigidDynCubeObj.tModelObj.tOrientation));
    v67 = igi2_frame.ptFirstWaypoint->ptSegment;
    if ( v67 )
    {
      v68 = QTask_GetPrevSiblingOfType(
              &igi2_frame.ptFirstWaypoint->tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask,
              SplineObjWaypoint_eQTaskType);
      v69 = igi2_frame.ptFirstWaypoint->isLinear || igi2_frame.ptFirstWaypoint->isAligned;
      SplineObjSegment_Update(
        v67,
        (struct real64x3_t *)&v68[8].tQTaskChildren,
        &igi2_frame.ptFirstWaypoint->tPos,
        (struct real32x9_t *)&v68[8].ptParent,
        &igi2_frame.ptFirstWaypoint->tOrientation,
        v69,
        igi2_frame.ptFirstWaypoint->isFlip,
        igi2_frame.ptFirstWaypoint->nNumAreas,
        igi2_frame.ptSplineObj->iCollisionLOD,
        igi2_frame.ptFirstWaypoint->zSegmentModel);
      v3 = (struct SplineObjWaypoint_s *)ptQTask;
    }
    for ( ;
          igi2_frame.ptWaypoint != igi2_frame.ptPrevWaypoint;
          igi2_frame.ptWaypoint = (struct SplineObjWaypoint_s *)QTask_GetNextSiblingOfType(
                                                       &v70->tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask,
                                                       SplineObjWaypoint_eQTaskType) )
    {
      v70 = igi2_frame.ptWaypoint;
      igi2_frame.vScale[0] = igi2_frame.tTemp.vX + igi2_frame.vScale[0];
      qmemcpy(&igi2_frame.ptWaypoint->tOrientation, &igi2_frame.Real32x9_Normalize_tTemp, sizeof(igi2_frame.ptWaypoint->tOrientation));
      igi2_frame.vScale[1] = igi2_frame.tTemp.vY + igi2_frame.vScale[1];
      igi2_frame.vScale[2] = igi2_frame.tTemp.vZ + igi2_frame.vScale[2];
      qmemcpy(&igi2_frame.ptWaypoint->tPos, igi2_frame.vScale, sizeof(igi2_frame.ptWaypoint->tPos));
      qmemcpy(
        &igi2_frame.ptWaypoint->tRigidDynCubeObj.tModelObj.tOrientation,
        &igi2_frame.Real32x9_Normalize_tTemp,
        sizeof(igi2_frame.ptWaypoint->tRigidDynCubeObj.tModelObj.tOrientation));
      if ( igi2_frame.ptWaypoint->isRegistered )
      {
        ptLODVirModel = igi2_frame.ptWaypoint->tRigidDynCubeObj.tModelObj.ptLODVirModel;
        if ( ptLODVirModel && (v72 = ptLODVirModel->aptVirModel[0]) != nullptr )
          igi2_frame.nNumSegments = SLODWORD(v72->ptModel->ptMesh->vRadius);
        else
          *(float *)&igi2_frame.nNumSegments = 1.0;
        World_MoveDynCubeObjRadius(
          igi2_frame.ptWaypoint->ptWorld,
          &igi2_frame.ptWaypoint->tRigidDynCubeObj.tModelObj.tDynCubeObj,
          &igi2_frame.ptWaypoint->tPos,
          *(float *)&igi2_frame.nNumSegments);
        v70 = igi2_frame.ptWaypoint;
      }
      v73 = v70->ptSegment;
      if ( v73 )
      {
        v74 = QTask_GetPrevSiblingOfType(
                &igi2_frame.ptWaypoint->tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask,
                SplineObjWaypoint_eQTaskType);
        v75 = igi2_frame.ptWaypoint->isLinear || igi2_frame.ptWaypoint->isAligned;
        SplineObjSegment_Update(
          v73,
          (struct real64x3_t *)&v74[8].tQTaskChildren,
          &igi2_frame.ptWaypoint->tPos,
          (struct real32x9_t *)&v74[8].ptParent,
          &igi2_frame.ptWaypoint->tOrientation,
          v75,
          igi2_frame.ptWaypoint->isFlip,
          igi2_frame.ptWaypoint->nNumAreas,
          igi2_frame.ptSplineObj->iCollisionLOD,
          igi2_frame.ptWaypoint->zSegmentModel);
        v3 = (struct SplineObjWaypoint_s *)ptQTask;
        v70 = igi2_frame.ptWaypoint;
      }
    }
    v76 = igi2_frame.ptPrevWaypoint;
    igi2_frame.nNumSegments = (int)&igi2_frame.ptPrevWaypoint->tOrientation;
    qmemcpy(&igi2_frame.ptPrevWaypoint->tOrientation, &igi2_frame.Real32x9_Normalize_tTemp, sizeof(igi2_frame.ptPrevWaypoint->tOrientation));
    qmemcpy(
      &igi2_frame.ptPrevWaypoint->tRigidDynCubeObj.tModelObj.tOrientation,
      &igi2_frame.Real32x9_Normalize_tTemp,
      sizeof(igi2_frame.ptPrevWaypoint->tRigidDynCubeObj.tModelObj.tOrientation));
    v77 = igi2_frame.ptPrevWaypoint->ptSegment;
    if ( v77 )
    {
      v78 = QTask_GetPrevSiblingOfType(
              &igi2_frame.ptPrevWaypoint->tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask,
              SplineObjWaypoint_eQTaskType);
      v79 = igi2_frame.ptPrevWaypoint->isLinear || igi2_frame.ptPrevWaypoint->isAligned;
      SplineObjSegment_Update(
        v77,
        (struct real64x3_t *)&v78[8].tQTaskChildren,
        igi2_frame.ptEndPos,
        (struct real32x9_t *)&v78[8].ptParent,
        (struct real32x9_t *)igi2_frame.nNumSegments,
        v79,
        igi2_frame.ptPrevWaypoint->isFlip,
        igi2_frame.ptPrevWaypoint->nNumAreas,
        igi2_frame.ptSplineObj->iCollisionLOD,
        igi2_frame.ptPrevWaypoint->zSegmentModel);
      v3 = (struct SplineObjWaypoint_s *)ptQTask;
      v76 = igi2_frame.ptPrevWaypoint;
    }
    v80 = QTask_GetNextSiblingOfType(
            &v76->tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask,
            SplineObjWaypoint_eQTaskType);
    if ( v80 )
    {
      v81 = (struct SplineObjSegment_s *)v80[8].ptNext;
      if ( v81 )
      {
        v82 = BYTE2(v80[12].tQTaskChildren.ptTail) || BYTE1(v80[12].tQTaskChildren.ptTail);
        SplineObjSegment_Update(
          v81,
          igi2_frame.ptEndPos,
          (struct real64x3_t *)&v80[8].tQTaskChildren,
          (struct real32x9_t *)igi2_frame.nNumSegments,
          (struct real32x9_t *)&v80[8].ptParent,
          v82,
          (char)v80[12].tQTaskRefList.ptHead,
          (int)v80[12].tQTaskChildren.ptHead,
          igi2_frame.ptSplineObj->iCollisionLOD,
          (char *)&v80[11].ptParent);
        v3 = (struct SplineObjWaypoint_s *)ptQTask;
      }
    }
  }
LABEL_147:
  v83 = SplineObjWaypoint_eQTaskType;
  FirstChildOfType = QTask_GetFirstChildOfType(&igi2_frame.ptSplineObj->tQTask, SplineObjWaypoint_eQTaskType);
  igi2_frame.ptSplineObj->vLength = 0.0;
  if ( FirstChildOfType )
  {
    for ( i = QTask_GetNextSiblingOfType(FirstChildOfType, v83); i; i = QTask_GetNextSiblingOfType(i, v83) )
    {
      v86 = i[8].ptNext;
      if ( v86 )
        igi2_frame.ptSplineObj->vLength = *(float *)&v86[8].tQTaskChildren.ptHead + igi2_frame.ptSplineObj->vLength;
    }
  }
  SplineObjWaypoint_SetRelativeOrientation(v3);
}

// source: h/2/splineobj.c:1618  [size]
void __cdecl SplineObjWaypoint_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = SplineObjWaypoint_ptParameterList;
}

// source: h/2/splineobj.c:1635  [size]
void __cdecl SplineObjWaypoint_GetCameraTargetInfoHandler(struct QTask_s *ptQTask, void *pxContext)
{
  double v2; // st7
  double v3; // st7
  int *v4; // ebx
  int v5; // ebx
  double v6; // st6

  qmemcpy(pxContext, &ptQTask[8].tQTaskChildren, 0x18u);
  *((_DWORD *)pxContext + 9) = 1065353216;
  *((_DWORD *)pxContext + 13) = 1065353216;
  *((_DWORD *)pxContext + 17) = 1065353216;
  *((_DWORD *)pxContext + 6) = 0;
  *((_DWORD *)pxContext + 7) = 0;
  *((_DWORD *)pxContext + 8) = 0;
  *((_DWORD *)pxContext + 10) = 0;
  *((_DWORD *)pxContext + 11) = 0;
  *((_DWORD *)pxContext + 12) = 0;
  *((_DWORD *)pxContext + 14) = 0;
  *((_DWORD *)pxContext + 15) = 0;
  *((_DWORD *)pxContext + 16) = 0;
  *((_DWORD *)pxContext + 18) = 0;
  if ( *(float *)&ptQTask[6].tQTaskChildren.ptHead <= (double)*(float *)&ptQTask[6].tQTaskChildren.ptMiddle )
    v2 = *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
  else
    v2 = *(float *)&ptQTask[6].tQTaskChildren.ptHead;
  if ( v2 >= *(float *)&ptQTask[6].ptPrev )
  {
    if ( *(float *)&ptQTask[6].tQTaskChildren.ptHead <= (double)*(float *)&ptQTask[6].tQTaskChildren.ptMiddle )
      v3 = *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
    else
      v3 = *(float *)&ptQTask[6].tQTaskChildren.ptHead;
  }
  else
  {
    v3 = *(float *)&ptQTask[6].ptPrev;
  }
  v4 = *(int **)&ptQTask[2].eQTaskType;
  if ( v4 && (v5 = *v4) != 0 )
  {
    v6 = v3 * *(float *)(*(_DWORD *)(*(_DWORD *)(v5 + 12) + 12) + 120);
    *((_DWORD *)pxContext + 20) = 0;
    *((float *)pxContext + 19) = v6;
  }
  else
  {
    *((_DWORD *)pxContext + 20) = 0;
    *((float *)pxContext + 19) = v3 * 1.0;
  }
}

// source: h/2/splineobj.c:1671  [anchor-strings]
void __cdecl SplineObjWaypoint_PrintQTaskInfoHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *ptNext; // eax

  ptNext = ptQTask[8].ptNext;
  if ( ptNext )
  {
    sprintf(
      SplineObj_zQTaskInfo,
      "Segment length: %f meter\n",
      *(float *)&ptNext[8].tQTaskChildren.ptHead * 0.000244140625);
    sprintf(
      SplineObj_zQTaskInfo,
      "%sModel length: %f meter\n",
      SplineObj_zQTaskInfo,
      (*(float *)&ptQTask[8].ptNext[8].tQTaskChildren.ptTail - *(float *)&ptQTask[8].ptNext[8].tQTaskChildren.ptMiddle)
    * 0.000244140625);
    *(_DWORD *)pxContext = SplineObj_zQTaskInfo;
  }
}

// source: h/2/splineobj.c:1696  [size]
void __cdecl SplineObjWaypoint_TraceLinesHandler(struct QTask_s *ptQTask, void *pxContext)
{
  if ( BYTE1(ptQTask->ptParent[2].ptPrev) )
    ((void (__cdecl *)())QTask_aatQTaskFinalEvent[10][RigidDynCubeObj_eQTaskType].pfHandler)(ptQTask, pxContext);
}

// source: h/2/splineobj.c:1721  [size]
void __cdecl SplineObjWaypoint_LineOfSightHandler(struct QTask_s *ptQTask, void *pxContext)
{
  if ( BYTE1(ptQTask->ptParent[2].ptPrev) )
    ((void (__cdecl *)())QTask_aatQTaskFinalEvent[9][RigidDynCubeObj_eQTaskType].pfHandler)(ptQTask, pxContext);
}

// source: h/2/splineobj.c:1746  [size]
void __cdecl SplineObjWaypoint_GetNextZHandler(struct QTask_s *ptQTask, void *pxContext)
{
  if ( BYTE1(ptQTask->ptParent[2].ptPrev) )
    ((void (__cdecl *)())QTask_aatQTaskFinalEvent[11][RigidDynCubeObj_eQTaskType].pfHandler)(ptQTask, pxContext);
}

// source: h/2/splineobj.c:1771  [size]
void __cdecl SplineObjWaypoint_GetMaterialHandler(struct QTask_s *ptQTask, void *pxContext)
{
  if ( BYTE1(ptQTask->ptParent[2].ptPrev) )
    ((void (__cdecl *)())QTask_aatQTaskFinalEvent[12][RigidDynCubeObj_eQTaskType].pfHandler)(ptQTask, pxContext);
}

// source: h/2/splineobj.c:1796  [anchor-mhash]
void __cdecl SplineObjWaypoint_RegisterHandler(struct QTask_s *ptQTask, void *pxContext)
{
  double v2; // st7
  double v3; // st7
  int *v4; // eax
  int v5; // eax
  double v6; // st6
  float ptDynCubeObj; // [esp+0h] [ebp-10h]

  if ( BYTE1(ptQTask->ptParent[2].ptPrev) )
  {
    if ( *(float *)&ptQTask[6].tQTaskChildren.ptHead <= (double)*(float *)&ptQTask[6].tQTaskChildren.ptMiddle )
      v2 = *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
    else
      v2 = *(float *)&ptQTask[6].tQTaskChildren.ptHead;
    if ( v2 >= *(float *)&ptQTask[6].ptPrev )
    {
      if ( *(float *)&ptQTask[6].tQTaskChildren.ptHead <= (double)*(float *)&ptQTask[6].tQTaskChildren.ptMiddle )
        v3 = *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
      else
        v3 = *(float *)&ptQTask[6].tQTaskChildren.ptHead;
    }
    else
    {
      v3 = *(float *)&ptQTask[6].ptPrev;
    }
    v4 = *(int **)&ptQTask[2].eQTaskType;
    if ( v4 && (v5 = *v4) != 0 )
      v6 = *(float *)(*(_DWORD *)(*(_DWORD *)(v5 + 12) + 12) + 120);
    else
      v6 = 1.0;
    ptDynCubeObj = v3 * v6;
    World_RegisterDynCubeObjFirstTimeRadius(
      World_ptActiveWorld,
      (struct DynCubeObj_s *)ptQTask,
      (struct real64x3_t *)&ptQTask[8].tQTaskChildren,
      ptDynCubeObj,
      WORLD_DYNCUBETREE_CATEGORY_STATIONARY);
    LOBYTE(ptQTask[12].tQTaskChildren.ptTail) = 1;
  }
}

// source: h/2/splineobj.c:1819  [anchor-mhash]
void __cdecl SplineObjWaypoint_RemoveHandler(struct QTask_s *ptQTask, void *pxContext)
{
  if ( !BYTE1(ptQTask->ptParent[2].ptPrev) )
  {
    World_RemoveDynCubeObj((struct World_s *)ptQTask[2].ptParent, (struct DynCubeObj_s *)ptQTask);
    LOBYTE(ptQTask[12].tQTaskChildren.ptTail) = 0;
  }
}

// source: h/2/splineobj.c:1842  [size]
void __cdecl SplineObjWaypoint_EnumerateLightmapHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *ptHead; // eax
  int v3; // edx
  struct QTask_s *v4; // ecx
  void (__cdecl *pfHandler)(struct QTask_s *, void *); // ecx
  int v6; // edx

  if ( BYTE1(ptQTask->ptParent[2].ptPrev) )
    ((void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[Lightmap_eEnumerateQTaskEvent][RigidDynCubeObj_eQTaskType].pfHandler)(
      ptQTask,
      pxContext);
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
      pfHandler = (void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[Lightmap_eEnumerateQTaskEvent][ptHead->eQTaskType].pfHandler;
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

// source: h/2/splineobj.c:1867  [size]
void __cdecl SplineObjWaypoint_EnumerateEnvmapHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *ptHead; // eax
  int v3; // edx
  struct QTask_s *v4; // ecx
  void (__cdecl *pfHandler)(struct QTask_s *, void *); // ecx
  int v6; // edx

  if ( BYTE1(ptQTask->ptParent[2].ptPrev) )
    ((void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[Envmap_eEnumerateQTaskEvent][RigidDynCubeObj_eQTaskType].pfHandler)(
      ptQTask,
      pxContext);
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
      pfHandler = (void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[Envmap_eEnumerateQTaskEvent][ptHead->eQTaskType].pfHandler;
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

// source: h/2/splineobj.c:1893  [size]
unsigned __int16 __cdecl SplineObj_GetQTaskType()
{
  return SplineObj_eQTaskType;
}

// source: h/2/splineobj.c:1907  [size]
unsigned __int16 __cdecl SplineObjWaypoint_GetQTaskType()
{
  return SplineObjWaypoint_eQTaskType;
}

// source: h/2/splineobj.c:1920  [anchor-mhash]
float __cdecl SplineObj_GetTotalLength(int nSplineObjQTaskID)
{
  struct QReference_s *v1; // eax
  struct QTask_s *pxObject; // eax
  double v3; // st7
  unsigned __int16 v4; // dx
  struct QTask_s *i; // eax
  struct QTask_s *ptNext; // ecx

  if ( (unsigned int)nSplineObjQTaskID < 0x1000 && (v1 = Level_atLevelQTaskID[nSplineObjQTaskID]) != nullptr )
    pxObject = (struct QTask_s *)v1->pxObject;
  else
    pxObject = nullptr;
  v3 = 0.0;
  if ( pxObject )
  {
    v4 = SplineObjWaypoint_eQTaskType;
    for ( i = QTask_GetFirstChildOfType(pxObject, SplineObjWaypoint_eQTaskType); i; i = QTask_GetNextSiblingOfType(
                                                                                          i,
                                                                                          v4) )
    {
      ptNext = i[8].ptNext;
      if ( ptNext )
        v3 = v3 + *(float *)&ptNext[8].tQTaskChildren.ptHead;
    }
  }
  else
  {
    return 0.0;
  }
  return v3;
}

// source: h/2/splineobj.c:1958  [anchor-hash]
int __cdecl SplineObj_GetNumberOfWaypoint(int nSplineObjQTaskID)
{
  struct QReference_s *v1; // eax
  int result; // eax
  int v3; // esi
  unsigned __int16 v4; // dx
  struct QTask_s *i; // eax

  if ( (unsigned int)nSplineObjQTaskID < 0x1000 && (v1 = Level_atLevelQTaskID[nSplineObjQTaskID]) != nullptr )
    result = (int)v1->pxObject;
  else
    result = 0;
  v3 = 0;
  if ( result )
  {
    v4 = SplineObjWaypoint_eQTaskType;
    for ( i = QTask_GetFirstChildOfType((struct QTask_s *)result, SplineObjWaypoint_eQTaskType);
          i;
          i = QTask_GetNextSiblingOfType(i, v4) )
    {
      ++v3;
    }
    return v3;
  }
  return result;
}

// source: h/2/splineobj.c:1993  [anchor-mhash]
float __cdecl SplineObj_GetLengthToWaypoint(int nSplineObjQTaskID, int iWaypoint)
{
  struct QReference_s *v2; // eax
  struct QTask_s *pxObject; // eax
  double v4; // st7
  int v5; // esi
  unsigned __int16 v6; // dx
  struct QTask_s *i; // eax
  struct QTask_s *ptNext; // ecx

  if ( (unsigned int)nSplineObjQTaskID < 0x1000 && (v2 = Level_atLevelQTaskID[nSplineObjQTaskID]) != nullptr )
    pxObject = (struct QTask_s *)v2->pxObject;
  else
    pxObject = nullptr;
  v4 = 0.0;
  v5 = 0;
  if ( pxObject )
  {
    v6 = SplineObjWaypoint_eQTaskType;
    for ( i = QTask_GetFirstChildOfType(pxObject, SplineObjWaypoint_eQTaskType); i; i = QTask_GetNextSiblingOfType(
                                                                                          i,
                                                                                          v6) )
    {
      if ( v5 == iWaypoint + 1 )
        break;
      ptNext = i[8].ptNext;
      if ( ptNext )
        v4 = v4 + *(float *)&ptNext[8].tQTaskChildren.ptHead;
      ++v5;
    }
  }
  else
  {
    return 0.0;
  }
  return v4;
}

// source: h/2/splineobj.c:2037  [anchor-hash]
int __cdecl SplineObj_IsLinear(int nSplineObjQTaskID)
{
  struct QReference_s *v1; // eax

  if ( (unsigned int)nSplineObjQTaskID < 0x1000 && (v1 = Level_atLevelQTaskID[nSplineObjQTaskID]) != nullptr )
    return *((char *)v1->pxObject + 86);
  else
    return MEMORY[0x56];
}

// source: h/2/splineobj.c:2055  [anchor-mhash]
int __cdecl SplineObj_GetWaypointPosition(
        struct real64x3_t *ptPos,
        int nSplineObjQTaskID,
        int iWaypoint)
{
  struct QReference_s *v4; // eax
  struct QTask_s *pxObject; // eax
  unsigned __int16 v6; // dx
  int result; // eax

  if ( (unsigned int)nSplineObjQTaskID < 0x1000 && (v4 = Level_atLevelQTaskID[nSplineObjQTaskID]) != nullptr )
    pxObject = (struct QTask_s *)v4->pxObject;
  else
    pxObject = nullptr;
  v6 = SplineObjWaypoint_eQTaskType;
  for ( result = (int)QTask_GetFirstChildOfType(pxObject, SplineObjWaypoint_eQTaskType); iWaypoint; --iWaypoint )
    result = (int)QTask_GetNextSiblingOfType((struct QTask_s *)result, v6);
  qmemcpy(ptPos, (void *)(result + 328), sizeof(struct real64x3_t));
  return result;
}

// source: h/2/splineobj.c:2138  [anchor-strings]
void __cdecl SplineObj_Open()
{
  unsigned __int16 BaseQTaskType; // ax
  unsigned __int16 v1; // ax
  unsigned __int16 v2; // di
  unsigned __int16 v3; // si
  __int16 v4; // bx
  __int16 v5; // bp
  struct ParameterList_s *v6; // eax
  int v7; // edx
  struct ParameterList_s *v8; // eax
  int v9; // edx

  BaseQTaskType = QTask_GetBaseQTaskType();
  SplineObj_eQTaskType = QTask_NewQTaskType("SplineObj", 88, BaseQTaskType, 0, 0);
  v1 = QTask_NewQTaskType("SplineObjWaypoint", 504, RigidDynCubeObj_eQTaskType, 0, 0);
  v2 = SplineObj_eQTaskType;
  v3 = v1;
  SplineObjWaypoint_eQTaskType = v1;
  QTask_LinkQTaskEventHandlerFn(
    SplineObj_eQTaskType,
    0,
    (void (__cdecl *)(struct QTask_s *, void *))SplineObj_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v2, 2, (void (__cdecl *)(struct QTask_s *))SplineObj_DeleteHandler);
  v4 = ParameterList_eUpdateInternalDataQTaskEvent;
  QTask_LinkQTaskEventHandlerFn(v2, ParameterList_eUpdateInternalDataQTaskEvent, SplineObj_UpdateInternalDataHandler);
  v5 = ParameterList_eGetParameterListQTaskEvent;
  QTask_LinkQTaskEventHandlerFn(
    v2,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))SplineObj_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(v2, 8, SplineObj_GetCameraTargetInfoHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(
    v2,
    Level_eUpdateInternalDataAfterLoadEvent,
    SplineObj_UpdateInternalDataAfterLoadHandler);
  QTask_LinkQTaskEventHandlerFn(v3, 0, SplineObjWaypoint_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v3, 2, SplineObjWaypoint_DeleteHandler);
  QTask_LinkQTaskEventHandlerFn(v3, v4, SplineObjWaypoint_UpdateInternalDataHandler);
  QTask_LinkQTaskEventHandlerFn(
    v3,
    v5,
    (void (__cdecl *)(struct QTask_s *, void *))SplineObjWaypoint_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(v3, 8, SplineObjWaypoint_GetCameraTargetInfoHandler);
  QTask_LinkQTaskEventHandlerFn(v3, Level_ePrintQTaskInfoQTaskEvent, SplineObjWaypoint_PrintQTaskInfoHandler);
  QTask_LinkQTaskEventHandlerFn(v3, 10, SplineObjWaypoint_TraceLinesHandler);
  QTask_LinkQTaskEventHandlerFn(v3, 9, SplineObjWaypoint_LineOfSightHandler);
  QTask_LinkQTaskEventHandlerFn(v3, 11, SplineObjWaypoint_GetNextZHandler);
  QTask_LinkQTaskEventHandlerFn(v3, 12, SplineObjWaypoint_GetMaterialHandler);
  QTask_LinkQTaskEventHandlerFn(v3, DynCubeObj_eDynCubeObjRegisterQTaskEvent, SplineObjWaypoint_RegisterHandler);
  QTask_LinkQTaskEventHandlerFn(v3, DynCubeObj_eDynCubeObjRemoveQTaskEvent, SplineObjWaypoint_RemoveHandler);
  QTask_LinkQTaskEventHandlerFn(v3, Lightmap_eEnumerateQTaskEvent, SplineObjWaypoint_EnumerateLightmapHandler);
  QTask_LinkQTaskEventHandlerFn(v3, Envmap_eEnumerateQTaskEvent, SplineObjWaypoint_EnumerateEnvmapHandler);
  dword_7BDB9E0 = 0;
  dword_7BDB9E4 = 0x40000000;
  dword_7BDB9E8 = 0;
  dword_7BDB9EC = 1077149696;
  v6 = (struct ParameterList_s *)Mem_AllocFn(172, 4);
  v7 = Level_eParameterTypebool8;
  v6->ptParameterListItem = (struct ParameterListItem_s *)&v6[1];
  v6->nParameters = 0;
  v6->nMaxParameters = 8;
  SplineObj_ptParameterList = v6;
  ParameterList_AddParameter(v6, 0x56u, v7, "Linear Segments", 7u, nullptr);
  ParameterList_AddParameter(
    SplineObj_ptParameterList,
    0x55u,
    Level_eParameterTypebool8,
    "Display waypoints",
    7u,
    nullptr);
  ParameterList_AddParameter(SplineObj_ptParameterList, 0x54u, Level_eParameterTypebool8, "Snap Length", 7u, nullptr);
  ParameterList_AddParameter(
    SplineObj_ptParameterList,
    0x57u,
    Level_eParameterTypebool8,
    "Automatic Orientation",
    7u,
    nullptr);
  ParameterList_AddParameter(
    SplineObj_ptParameterList,
    0x2Cu,
    Level_eParameterTypeInt32,
    "Number of Matrices / Segment",
    7u,
    &dword_7BDB9E0);
  ParameterList_AddParameter(SplineObj_ptParameterList, 0x28u, Level_eParameterTypeInt32, "Collision LOD", 7u, nullptr);
  ParameterList_AddParameter(SplineObj_ptParameterList, 0x34u, Level_eParameterTypeReal32x3, "Position", 7u, nullptr);
  ParameterList_AddParameter(
    SplineObj_ptParameterList,
    0x4Cu,
    Level_eParameterTypeAngle,
    "Gamma Orientation",
    7u,
    nullptr);
  v8 = (struct ParameterList_s *)Mem_AllocFn(172, 4);
  v8->ptParameterListItem = (struct ParameterListItem_s *)&v8[1];
  v9 = Level_eParameterTypeReal32x9;
  v8->nParameters = 0;
  v8->nMaxParameters = 8;
  SplineObjWaypoint_ptParameterList = v8;
  ParameterList_AddParameter(v8, 0x160u, v9, "Orientation", 7u, nullptr);
  ParameterList_AddParameter(
    SplineObjWaypoint_ptParameterList,
    0x148u,
    Level_eParameterTypeObjectPos,
    "Position",
    7u,
    nullptr);
  ParameterList_AddParameter(
    SplineObjWaypoint_ptParameterList,
    0x1C8u,
    Level_eParameterTypeString16,
    "Waypoint Model",
    7u,
    nullptr);
  ParameterList_AddParameter(
    SplineObjWaypoint_ptParameterList,
    0x1D8u,
    Level_eParameterTypeString16,
    "Segment Model",
    7u,
    nullptr);
  ParameterList_AddParameter(
    SplineObjWaypoint_ptParameterList,
    0x1E8u,
    Level_eParameterTypeInt32,
    "NumAreas",
    7u,
    &dword_7BDB9E0);
  ParameterList_AddParameter(SplineObjWaypoint_ptParameterList, 0x1F1u, Level_eParameterTypebool8, "Align", 7u, nullptr);
  ParameterList_AddParameter(SplineObjWaypoint_ptParameterList, 0x1F4u, Level_eParameterTypebool8, "Flip", 7u, nullptr);
  ParameterList_AddParameter(
    SplineObjWaypoint_ptParameterList,
    0x1F5u,
    Level_eParameterTypebool8,
    "Automatic Orientation",
    7u,
    nullptr);
}

// source: h/2/splineobj.c:2213  [size]
void __cdecl SplineObj_Close()
{
  int v0; // esi
  int v1; // esi

  QTask_DeleteQTaskType(SplineObj_eQTaskType);
  QTask_DeleteQTaskType(SplineObjWaypoint_eQTaskType);
  if ( SplineObj_ptParameterList )
  {
    v0 = *(_DWORD *)((unsigned int)&SplineObj_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
  if ( SplineObjWaypoint_ptParameterList )
  {
    v1 = *(_DWORD *)((unsigned int)&SplineObjWaypoint_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v1);
    memset(*(void **)(v1 + 8), 0xCDu, *(_DWORD *)(v1 + 16));
    free((void *)v1);
  }
}
