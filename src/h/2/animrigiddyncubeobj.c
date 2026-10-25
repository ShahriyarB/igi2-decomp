/* h/2/animrigiddyncubeobj.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: h/2/animrigiddyncubeobj.c:108  [size]
void __cdecl AnimRigidDynCubeObj_GetChannelDescriptionHandler(
        struct QTask_s *ptQTask,
        void *pxContext)
{
  int v2; // eax

  v2 = *(_DWORD *)pxContext;
  if ( *(int *)pxContext < 0 || v2 >= 22 )
    *((_DWORD *)pxContext + 1) = 0;
  else
    *((_DWORD *)pxContext + 1) = 16 * v2 + 7012544;
}

// source: h/2/animrigiddyncubeobj.c:139  [size]
void __cdecl AnimRigidDynCubeObj_GetKeyframeSizeHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = 64;
}

// source: h/2/animrigiddyncubeobj.c:157  [anchor-mhash]
void __cdecl AnimRigidDynCubeObj_SaveKeyframeHandler(struct QTask_s *ptQTask, void *pxContext)
{
  int v2; // eax

  v2 = *(_DWORD *)pxContext;
  qmemcpy(*((void **)pxContext + 2), &ptQTask[1], 0x18u);
  qmemcpy((void *)(v2 + 24), &ptQTask[3].ptPrev, 0x28u);
  qmemcpy((void *)v2, &ptQTask[1], 0x18u);
}

// source: h/2/animrigiddyncubeobj.c:189  [anchor-mhash]
void __cdecl AnimRigidDynCubeObj_RestoreKeyframeHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct real64x3_t *v2; // ebx
  bool v3; // zf
  double v4; // st7
  double v5; // st7
  int *v6; // eax
  int v7; // eax
  double v8; // st6
  float ptDynCubeObj; // [esp+0h] [ebp-10h]

  v2 = *(struct real64x3_t **)pxContext;
  v3 = *(float *)&ptQTask[6].tQTaskChildren.ptHead > (double)*(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
  qmemcpy(&ptQTask[3].ptPrev, (void *)(*(_DWORD *)pxContext + 24), sizeof(struct QTask_s));
  if ( v3 )
    v4 = *(float *)&ptQTask[6].tQTaskChildren.ptHead;
  else
    v4 = *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
  if ( v4 >= *(float *)&ptQTask[6].ptPrev )
  {
    if ( *(float *)&ptQTask[6].tQTaskChildren.ptHead <= (double)*(float *)&ptQTask[6].tQTaskChildren.ptMiddle )
      v5 = *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
    else
      v5 = *(float *)&ptQTask[6].tQTaskChildren.ptHead;
  }
  else
  {
    v5 = *(float *)&ptQTask[6].ptPrev;
  }
  v6 = *(int **)&ptQTask[2].eQTaskType;
  if ( v6 && (v7 = *v6) != 0 )
    v8 = *(float *)(*(_DWORD *)(*(_DWORD *)(v7 + 12) + 12) + 120);
  else
    v8 = 1.0;
  ptDynCubeObj = v5 * v8;
  World_MoveDynCubeObjRadius((struct World_s *)ptQTask[2].ptParent, (struct DynCubeObj_s *)ptQTask, v2, ptDynCubeObj);
}

// source: h/2/animrigiddyncubeobj.c:221  [anchor-mhash]
void __cdecl AnimRigidDynCubeObj_UpdateAnimDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { float ptDest; };
    struct { char igi2_o1[4]; float vAlpha; };
    struct { char igi2_o2[8]; float ptDynCubeObj; };
    struct { char igi2_o3[8]; float ptDynCubeObja; };
    struct { char igi2_o4[8]; float ptDynCubeObjb; };
    struct { char igi2_o5[32]; struct QTask_s *tVector_4; };
    struct { char igi2_o6[36]; struct QReference_s *tVector_8; };
    struct { char igi2_o7[36]; float tVector_8a; };
    struct { char igi2_o8[44]; struct real64x3_t Real64x3_Rotate_tTemp; };
    struct { char igi2_o9[68]; struct real32x9_t tMatrix; };
    struct { char igi2_o10[108]; struct real32x9_t Real32x9_Multiply_tTemp; };
    char igi2_extent[148];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  void *v2; // eax
  double v3; // st7
  bool v4; // c0
  bool v5; // c3
  double v6; // st7
  double v7; // st7
  int *v8; // eax
  int v9; // eax
  double v10; // st6
  float *v11; // ecx
  float *p_ptPrev; // edi
  double v13; // st7
  double v14; // st6
  float *v15; // ecx
  struct QTask_s *ptParent; // edx
  double v17; // st7
  double v18; // st6
  float v19; // edx
  double v20; // st6
  double v21; // st5
  double v22; // st7
  double v23; // st6
  float *v24; // esi
  int v25; // eax
  struct QReference_s *v26; // eax
  float *pxObject; // edx
  double v28; // st7
  double v29; // st7
  double v30; // st6
  float *v31; // ecx
  double v32; // st7
  double v33; // st7
  double v34; // st7
  double v35; // st7
  double v36; // st7
  int *v37; // eax
  int v38; // eax
  double v39; // st6

  v2 = pxContext;
  if ( !*(_DWORD *)pxContext )
  {
    v3 = *(float *)&ptQTask[6].tQTaskChildren.ptHead;
    v4 = v3 < *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
    v5 = v3 == *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
    qmemcpy(&ptQTask[3].ptPrev, &ptQTask[8].tQTaskRefList.ptMiddle, sizeof(struct QTask_s));
    qmemcpy(&ptQTask[9].tQTaskRefList.ptMiddle, &ptQTask[8].tQTaskRefList.ptMiddle, sizeof(struct QTask_s));
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
    igi2_frame.ptDynCubeObj = v10 * v7;
    World_MoveDynCubeObjRadius(
      (struct World_s *)ptQTask[2].ptParent,
      (struct DynCubeObj_s *)ptQTask,
      (struct real64x3_t *)&ptQTask[8],
      igi2_frame.ptDynCubeObj);
    v2 = pxContext;
  }
  v11 = *((float **)v2 + 1);
  p_ptPrev = (float *)&ptQTask[3].ptPrev;
  v13 = v11[3] * 0.0009765625;
  v14 = v11[4] * 0.0009765625;
  *(float *)&igi2_frame.Real64x3_Rotate_tTemp.vY = v11[5] * 0.0009765625;
  v11[3] = v11[6] + v11[3];
  *(float *)(*((_DWORD *)v2 + 1) + 16) = *(float *)(*((_DWORD *)v2 + 1) + 28) + *(float *)(*((_DWORD *)v2 + 1) + 16);
  *(float *)(*((_DWORD *)v2 + 1) + 20) = *(float *)(*((_DWORD *)v2 + 1) + 32) + *(float *)(*((_DWORD *)v2 + 1) + 20);
  igi2_frame.tVector_4 = ptQTask[3].tQTaskChildren.ptTail;
  v15 = *((float **)v2 + 1);
  igi2_frame.tVector_8 = ptQTask[3].tQTaskRefList.ptTail;
  ptParent = ptQTask[3].ptParent;
  *(float *)&igi2_frame.Real64x3_Rotate_tTemp.vX = *(float *)&ptQTask[3].ptPrev * v15[9] * 0.0009765625 + v13;
  v17 = *(float *)&igi2_frame.tVector_4 * v15[9] * 0.0009765625 + v14;
  v18 = *(float *)&igi2_frame.tVector_8;
  igi2_frame.tVector_8a = *(float *)&ptParent;
  v19 = *(float *)&ptQTask[3].eQTaskType;
  v20 = v18 * v15[9] * 0.0009765625 + *(float *)&igi2_frame.Real64x3_Rotate_tTemp.vY;
  v21 = *(float *)&ptQTask[3].tQTaskRefList.ptHead;
  *(float *)&igi2_frame.Real64x3_Rotate_tTemp.vX = *(float *)&ptQTask[3].tQTaskChildren.ptHead * v15[10] * 0.0009765625
                                      + *(float *)&igi2_frame.Real64x3_Rotate_tTemp.vX;
  *((float *)&igi2_frame.Real64x3_Rotate_tTemp.vX + 1) = v21 * v15[10] * 0.0009765625 + v17;
  v22 = igi2_frame.tVector_8a * v15[10] * 0.0009765625 + v20;
  v23 = *(float *)&ptQTask[3].tQTaskRefList.ptMiddle;
  *(float *)&igi2_frame.Real64x3_Rotate_tTemp.vX = *(float *)&ptQTask[3].tQTaskChildren.ptMiddle * v15[11] * 0.0009765625
                                      + *(float *)&igi2_frame.Real64x3_Rotate_tTemp.vX;
  *((float *)&igi2_frame.Real64x3_Rotate_tTemp.vX + 1) = v23 * v15[11] * 0.0009765625 + *((float *)&igi2_frame.Real64x3_Rotate_tTemp.vX + 1);
  *(float *)&igi2_frame.Real64x3_Rotate_tTemp.vY = v19 * v15[11] * 0.0009765625 + v22;
  *v15 = *(float *)&igi2_frame.Real64x3_Rotate_tTemp.vX + *v15;
  *(float *)(*((_DWORD *)v2 + 1) + 4) = *((float *)&igi2_frame.Real64x3_Rotate_tTemp.vX + 1) + *(float *)(*((_DWORD *)v2 + 1) + 4);
  *(float *)(*((_DWORD *)v2 + 1) + 8) = *(float *)&igi2_frame.Real64x3_Rotate_tTemp.vY + *(float *)(*((_DWORD *)v2 + 1) + 8);
  *(float *)(*((_DWORD *)v2 + 1) + 36) = *(float *)(*((_DWORD *)v2 + 1) + 48) + *(float *)(*((_DWORD *)v2 + 1) + 36);
  *(float *)(*((_DWORD *)v2 + 1) + 40) = *(float *)(*((_DWORD *)v2 + 1) + 52) + *(float *)(*((_DWORD *)v2 + 1) + 40);
  *(float *)(*((_DWORD *)v2 + 1) + 44) = *(float *)(*((_DWORD *)v2 + 1) + 56) + *(float *)(*((_DWORD *)v2 + 1) + 44);
  *(float *)(*((_DWORD *)v2 + 1) + 60) = *(float *)(*((_DWORD *)v2 + 1) + 72) + *(float *)(*((_DWORD *)v2 + 1) + 60);
  *(float *)(*((_DWORD *)v2 + 1) + 64) = *(float *)(*((_DWORD *)v2 + 1) + 76) + *(float *)(*((_DWORD *)v2 + 1) + 64);
  *(float *)(*((_DWORD *)v2 + 1) + 68) = *(float *)(*((_DWORD *)v2 + 1) + 80) + *(float *)(*((_DWORD *)v2 + 1) + 68);
  v24 = *((float **)v2 + 1);
  igi2_frame.ptDynCubeObja = v24[17] * 0.0009765625 * 3.1415926535897944 * 0.000244140625;
  igi2_frame.vAlpha = v24[16] * 0.0009765625 * 3.1415926535897944 * 0.000244140625;
  igi2_frame.ptDest = v24[15] * 0.0009765625 * 3.1415926535897944 * 0.000244140625;
  Real32x9_Create(&igi2_frame.tMatrix, igi2_frame.ptDest, igi2_frame.vAlpha, igi2_frame.ptDynCubeObja);
  v25 = (__int64)v24[21];
  if ( v25 > 0
    && v25 < 4096
    && (v26 = Level_atLevelQTaskID[v25]) != nullptr
    && (pxObject = (float *)v26->pxObject) != nullptr )
  {
    QTask_IsQTaskTypeDerived(*((_WORD *)pxObject + 18), RigidDynCubeObj_eQTaskType);
    igi2_frame.Real32x9_Multiply_tTemp.tX.vX = igi2_frame.tMatrix.tZ.vX * *(float *)&ptQTask[9].ptParent
                                  + igi2_frame.tMatrix.tY.vX * *(float *)&ptQTask[9].tQTaskRefList.ptTail
                                  + igi2_frame.tMatrix.tX.vX * *(float *)&ptQTask[9].tQTaskRefList.ptMiddle;
    igi2_frame.Real32x9_Multiply_tTemp.tX.vY = igi2_frame.tMatrix.tZ.vY * *(float *)&ptQTask[9].ptParent
                                  + igi2_frame.tMatrix.tY.vY * *(float *)&ptQTask[9].tQTaskRefList.ptTail
                                  + igi2_frame.tMatrix.tX.vY * *(float *)&ptQTask[9].tQTaskRefList.ptMiddle;
    igi2_frame.Real32x9_Multiply_tTemp.tX.vZ = igi2_frame.tMatrix.tZ.vZ * *(float *)&ptQTask[9].ptParent
                                  + igi2_frame.tMatrix.tY.vZ * *(float *)&ptQTask[9].tQTaskRefList.ptTail
                                  + igi2_frame.tMatrix.tX.vZ * *(float *)&ptQTask[9].tQTaskRefList.ptMiddle;
    igi2_frame.Real32x9_Multiply_tTemp.tY.vX = igi2_frame.tMatrix.tZ.vX * *(float *)&ptQTask[10].ptPrev
                                  + igi2_frame.tMatrix.tX.vX * *(float *)&ptQTask[9].eQTaskType
                                  + igi2_frame.tMatrix.tY.vX * *(float *)&ptQTask[10].ptNext;
    igi2_frame.Real32x9_Multiply_tTemp.tY.vY = igi2_frame.tMatrix.tZ.vY * *(float *)&ptQTask[10].ptPrev
                                  + igi2_frame.tMatrix.tX.vY * *(float *)&ptQTask[9].eQTaskType
                                  + igi2_frame.tMatrix.tY.vY * *(float *)&ptQTask[10].ptNext;
    igi2_frame.Real32x9_Multiply_tTemp.tY.vZ = igi2_frame.tMatrix.tZ.vZ * *(float *)&ptQTask[10].ptPrev
                                  + igi2_frame.tMatrix.tX.vZ * *(float *)&ptQTask[9].eQTaskType
                                  + igi2_frame.tMatrix.tY.vZ * *(float *)&ptQTask[10].ptNext;
    igi2_frame.Real32x9_Multiply_tTemp.tZ.vX = igi2_frame.tMatrix.tY.vX * *(float *)&ptQTask[10].tQTaskChildren.ptMiddle
                                  + igi2_frame.tMatrix.tZ.vX * *(float *)&ptQTask[10].tQTaskChildren.ptTail
                                  + igi2_frame.tMatrix.tX.vX * *(float *)&ptQTask[10].tQTaskChildren.ptHead;
    igi2_frame.Real32x9_Multiply_tTemp.tZ.vY = igi2_frame.tMatrix.tZ.vY * *(float *)&ptQTask[10].tQTaskChildren.ptTail
                                  + igi2_frame.tMatrix.tX.vY * *(float *)&ptQTask[10].tQTaskChildren.ptHead
                                  + igi2_frame.tMatrix.tY.vY * *(float *)&ptQTask[10].tQTaskChildren.ptMiddle;
    v28 = igi2_frame.tMatrix.tZ.vZ * *(float *)&ptQTask[10].tQTaskChildren.ptTail;
    igi2_frame.Real32x9_Multiply_tTemp.nOps = (int)&ptQTask[10].tQTaskRefList.ptHead->ptNext + igi2_frame.tMatrix.nOps + 1;
    igi2_frame.Real32x9_Multiply_tTemp.tZ.vZ = v28
                                  + igi2_frame.tMatrix.tX.vZ * *(float *)&ptQTask[10].tQTaskChildren.ptHead
                                  + igi2_frame.tMatrix.tY.vZ * *(float *)&ptQTask[10].tQTaskChildren.ptMiddle;
    qmemcpy(&ptQTask[9].tQTaskRefList.ptMiddle, &igi2_frame.Real32x9_Multiply_tTemp, sizeof(struct QTask_s));
    igi2_frame.Real32x9_Multiply_tTemp.tX.vX = *(float *)&ptQTask[9].eQTaskType * pxObject[32]
                                  + pxObject[33] * *(float *)&ptQTask[10].tQTaskChildren.ptHead
                                  + pxObject[31] * *(float *)&ptQTask[9].tQTaskRefList.ptMiddle;
    igi2_frame.Real32x9_Multiply_tTemp.tX.vY = *(float *)&ptQTask[10].tQTaskChildren.ptMiddle * pxObject[33]
                                  + *(float *)&ptQTask[9].tQTaskRefList.ptTail * pxObject[31]
                                  + pxObject[32] * *(float *)&ptQTask[10].ptNext;
    igi2_frame.Real32x9_Multiply_tTemp.tX.vZ = *(float *)&ptQTask[10].ptPrev * pxObject[32]
                                  + pxObject[33] * *(float *)&ptQTask[10].tQTaskChildren.ptTail
                                  + *(float *)&ptQTask[9].ptParent * pxObject[31];
    igi2_frame.Real32x9_Multiply_tTemp.tY.vX = *(float *)&ptQTask[9].eQTaskType * pxObject[35]
                                  + pxObject[34] * *(float *)&ptQTask[9].tQTaskRefList.ptMiddle
                                  + *(float *)&ptQTask[10].tQTaskChildren.ptHead * pxObject[36];
    igi2_frame.Real32x9_Multiply_tTemp.tY.vY = *(float *)&ptQTask[10].tQTaskChildren.ptMiddle * pxObject[36]
                                  + *(float *)&ptQTask[9].tQTaskRefList.ptTail * pxObject[34]
                                  + *(float *)&ptQTask[10].ptNext * pxObject[35];
    igi2_frame.Real32x9_Multiply_tTemp.tY.vZ = *(float *)&ptQTask[10].ptPrev * pxObject[35]
                                  + *(float *)&ptQTask[10].tQTaskChildren.ptTail * pxObject[36]
                                  + *(float *)&ptQTask[9].ptParent * pxObject[34];
    v29 = pxObject[39] * *(float *)&ptQTask[10].tQTaskChildren.ptHead + pxObject[38] * *(float *)&ptQTask[9].eQTaskType;
    v30 = *(float *)&ptQTask[9].tQTaskRefList.ptMiddle * pxObject[37];
    igi2_frame.Real32x9_Multiply_tTemp.nOps = (int)&ptQTask[10].tQTaskRefList.ptHead->ptNext + *((_DWORD *)pxObject + 40) + 1;
    igi2_frame.Real32x9_Multiply_tTemp.tZ.vX = v29 + v30;
    igi2_frame.Real32x9_Multiply_tTemp.tZ.vY = pxObject[38] * *(float *)&ptQTask[10].ptNext
                                  + *(float *)&ptQTask[10].tQTaskChildren.ptMiddle * pxObject[39]
                                  + *(float *)&ptQTask[9].tQTaskRefList.ptTail * pxObject[37];
    igi2_frame.Real32x9_Multiply_tTemp.tZ.vZ = pxObject[39] * *(float *)&ptQTask[10].tQTaskChildren.ptTail
                                  + pxObject[38] * *(float *)&ptQTask[10].ptPrev
                                  + *(float *)&ptQTask[9].ptParent * pxObject[37];
    qmemcpy(&ptQTask[3].ptPrev, &igi2_frame.Real32x9_Multiply_tTemp, sizeof(struct QTask_s));
    **((float **)pxContext + 1) = *(float *)&igi2_frame.Real64x3_Rotate_tTemp.vX + **((float **)pxContext + 1);
    *(float *)(*((_DWORD *)pxContext + 1) + 4) = *((float *)&igi2_frame.Real64x3_Rotate_tTemp.vX + 1)
                                               + *(float *)(*((_DWORD *)pxContext + 1) + 4);
    *(float *)(*((_DWORD *)pxContext + 1) + 8) = *(float *)&igi2_frame.Real64x3_Rotate_tTemp.vY
                                               + *(float *)(*((_DWORD *)pxContext + 1) + 8);
    v31 = *((float **)pxContext + 1);
    v32 = *v31;
    *(double *)&igi2_frame.tMatrix.tX.vZ = v31[1];
    *(double *)&igi2_frame.tMatrix.tY.vY = v31[2];
    igi2_frame.Real64x3_Rotate_tTemp.vX = pxObject[33] * *(double *)&igi2_frame.tMatrix.tY.vY
                             + pxObject[32] * *(double *)&igi2_frame.tMatrix.tX.vZ
                             + pxObject[31] * v32;
    igi2_frame.Real64x3_Rotate_tTemp.vY = pxObject[36] * *(double *)&igi2_frame.tMatrix.tY.vY
                             + pxObject[35] * *(double *)&igi2_frame.tMatrix.tX.vZ
                             + pxObject[34] * v32;
    igi2_frame.Real64x3_Rotate_tTemp.vZ = pxObject[37] * v32
                             + pxObject[39] * *(double *)&igi2_frame.tMatrix.tY.vY
                             + pxObject[38] * *(double *)&igi2_frame.tMatrix.tX.vZ;
    qmemcpy(&igi2_frame.tMatrix, &igi2_frame.Real64x3_Rotate_tTemp, 0x18u);
    *(double *)&igi2_frame.tMatrix.tX.vX = igi2_frame.Real64x3_Rotate_tTemp.vX + *((double *)pxObject + 5);
    *(double *)&igi2_frame.tMatrix.tX.vZ = *(double *)&igi2_frame.tMatrix.tX.vZ + *((double *)pxObject + 6);
    v33 = *(double *)&igi2_frame.tMatrix.tY.vY + *((double *)pxObject + 7);
  }
  else
  {
    igi2_frame.Real32x9_Multiply_tTemp.tX.vX = igi2_frame.tMatrix.tY.vX * *(float *)&ptQTask[3].tQTaskChildren.ptHead
                                  + igi2_frame.tMatrix.tX.vX * *p_ptPrev
                                  + igi2_frame.tMatrix.tZ.vX * *(float *)&ptQTask[3].tQTaskChildren.ptMiddle;
    igi2_frame.Real32x9_Multiply_tTemp.tX.vY = igi2_frame.tMatrix.tZ.vY * *(float *)&ptQTask[3].tQTaskChildren.ptMiddle
                                  + igi2_frame.tMatrix.tY.vY * *(float *)&ptQTask[3].tQTaskChildren.ptHead
                                  + igi2_frame.tMatrix.tX.vY * *p_ptPrev;
    igi2_frame.Real32x9_Multiply_tTemp.tX.vZ = igi2_frame.tMatrix.tZ.vZ * *(float *)&ptQTask[3].tQTaskChildren.ptMiddle
                                  + igi2_frame.tMatrix.tY.vZ * *(float *)&ptQTask[3].tQTaskChildren.ptHead
                                  + igi2_frame.tMatrix.tX.vZ * *p_ptPrev;
    igi2_frame.Real32x9_Multiply_tTemp.tY.vX = igi2_frame.tMatrix.tX.vX * *(float *)&ptQTask[3].tQTaskChildren.ptTail
                                  + igi2_frame.tMatrix.tY.vX * *(float *)&ptQTask[3].tQTaskRefList.ptHead
                                  + igi2_frame.tMatrix.tZ.vX * *(float *)&ptQTask[3].tQTaskRefList.ptMiddle;
    igi2_frame.Real32x9_Multiply_tTemp.tY.vY = igi2_frame.tMatrix.tY.vY * *(float *)&ptQTask[3].tQTaskRefList.ptHead
                                  + igi2_frame.tMatrix.tZ.vY * *(float *)&ptQTask[3].tQTaskRefList.ptMiddle
                                  + igi2_frame.tMatrix.tX.vY * *(float *)&ptQTask[3].tQTaskChildren.ptTail;
    igi2_frame.Real32x9_Multiply_tTemp.tY.vZ = igi2_frame.tMatrix.tY.vZ * *(float *)&ptQTask[3].tQTaskRefList.ptHead
                                  + igi2_frame.tMatrix.tZ.vZ * *(float *)&ptQTask[3].tQTaskRefList.ptMiddle
                                  + igi2_frame.tMatrix.tX.vZ * *(float *)&ptQTask[3].tQTaskChildren.ptTail;
    igi2_frame.Real32x9_Multiply_tTemp.tZ.vX = igi2_frame.tMatrix.tY.vX * *(float *)&ptQTask[3].ptParent
                                  + igi2_frame.tMatrix.tZ.vX * *(float *)&ptQTask[3].eQTaskType
                                  + igi2_frame.tMatrix.tX.vX * *(float *)&ptQTask[3].tQTaskRefList.ptTail;
    igi2_frame.Real32x9_Multiply_tTemp.tZ.vY = igi2_frame.tMatrix.tZ.vY * *(float *)&ptQTask[3].eQTaskType
                                  + igi2_frame.tMatrix.tX.vY * *(float *)&ptQTask[3].tQTaskRefList.ptTail
                                  + igi2_frame.tMatrix.tY.vY * *(float *)&ptQTask[3].ptParent;
    v34 = igi2_frame.tMatrix.tZ.vZ * *(float *)&ptQTask[3].eQTaskType + igi2_frame.tMatrix.tX.vZ * *(float *)&ptQTask[3].tQTaskRefList.ptTail;
    igi2_frame.Real32x9_Multiply_tTemp.nOps = (int)&ptQTask[4].ptNext->ptNext + igi2_frame.tMatrix.nOps + 1;
    igi2_frame.Real32x9_Multiply_tTemp.tZ.vZ = v34 + igi2_frame.tMatrix.tY.vZ * *(float *)&ptQTask[3].ptParent;
    qmemcpy(p_ptPrev, &igi2_frame.Real32x9_Multiply_tTemp, 0x28u);
    *(double *)&igi2_frame.tMatrix.tX.vX = *(float *)&igi2_frame.Real64x3_Rotate_tTemp.vX + *(double *)&ptQTask[1].ptNext;
    *(double *)&igi2_frame.tMatrix.tX.vZ = *((float *)&igi2_frame.Real64x3_Rotate_tTemp.vX + 1) + *(double *)&ptQTask[1].tQTaskChildren.ptHead;
    v33 = *(float *)&igi2_frame.Real64x3_Rotate_tTemp.vY + *(double *)&ptQTask[1].tQTaskChildren.ptTail;
  }
  *(double *)&igi2_frame.tMatrix.tY.vY = v33;
  if ( *(float *)&ptQTask[6].tQTaskChildren.ptHead <= (double)*(float *)&ptQTask[6].tQTaskChildren.ptMiddle )
    v35 = *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
  else
    v35 = *(float *)&ptQTask[6].tQTaskChildren.ptHead;
  if ( v35 >= *(float *)&ptQTask[6].ptPrev )
  {
    if ( *(float *)&ptQTask[6].tQTaskChildren.ptHead <= (double)*(float *)&ptQTask[6].tQTaskChildren.ptMiddle )
      v36 = *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
    else
      v36 = *(float *)&ptQTask[6].tQTaskChildren.ptHead;
  }
  else
  {
    v36 = *(float *)&ptQTask[6].ptPrev;
  }
  v37 = *(int **)&ptQTask[2].eQTaskType;
  if ( v37 && (v38 = *v37) != 0 )
    v39 = *(float *)(*(_DWORD *)(*(_DWORD *)(v38 + 12) + 12) + 120);
  else
    v39 = 1.0;
  igi2_frame.ptDynCubeObjb = v39 * v36;
  World_MoveDynCubeObjRadius(
    (struct World_s *)ptQTask[2].ptParent,
    (struct DynCubeObj_s *)ptQTask,
    (struct real64x3_t *)&igi2_frame.tMatrix,
    igi2_frame.ptDynCubeObjb);
}

// source: h/2/animrigiddyncubeobj.c:407  [size]
void __cdecl AnimRigidDynCubeObj_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ;
}

// source: h/2/animrigiddyncubeobj.c:421  [size]
void __cdecl AnimRigidDynCubeObj_RunHandler(struct QTask_s *ptQTask)
{
  ;
}

// source: h/2/animrigiddyncubeobj.c:435  [size]
void __cdecl AnimRigidDynCubeObj_DeleteHandler(struct QTask_s *ptQTask)
{
  ;
}

// source: h/2/animrigiddyncubeobj.c:451  [anchor-strings]
void __cdecl AnimRigidDynCubeObj_Open()
{
  unsigned __int16 v0; // si

  v0 = QTask_NewQTaskType("AnimRigidDynCubeObj", 424, RigidDynCubeObj_eQTaskType, 0, 0);
  AnimRigidDynCubeObj_eQTaskType = v0;
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 1, (void (__cdecl *)(struct QTask_s *))AnimRigidDynCubeObj_RunHandler);
  QTask_LinkQTaskEventHandlerFn(v0, 0, (void (__cdecl *)(struct QTask_s *, void *))AnimRigidDynCubeObj_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 2, (void (__cdecl *)(struct QTask_s *))AnimRigidDynCubeObj_DeleteHandler);
  QTask_LinkQTaskEventHandlerFn(v0, AnimQTask_eUpdateAnimDataEvent, AnimRigidDynCubeObj_UpdateAnimDataHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    AnimQTask_eGetChannelDescriptionEvent,
    (void (__cdecl *)(struct QTask_s *, void *))AnimRigidDynCubeObj_GetChannelDescriptionHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    AnimQTask_eGetKeyframeSizeEvent,
    (void (__cdecl *)(struct QTask_s *, void *))AnimRigidDynCubeObj_GetKeyframeSizeHandler);
  QTask_LinkQTaskEventHandlerFn(v0, AnimQTask_eSaveKeyframeEvent, AnimRigidDynCubeObj_SaveKeyframeHandler);
  QTask_LinkQTaskEventHandlerFn(v0, AnimQTask_eRestoreKeyframeEvent, AnimRigidDynCubeObj_RestoreKeyframeHandler);
}

// source: h/2/animrigiddyncubeobj.c:476  [size]
void __cdecl AnimRigidDynCubeObj_Close()
{
  QTask_DeleteQTaskType(AnimRigidDynCubeObj_eQTaskType);
}

// source: h/2/animrigiddyncubeobj.c:492  [size]
unsigned __int16 __cdecl AnimRigidDynCubeObj_GetQTaskType()
{
  return AnimRigidDynCubeObj_eQTaskType;
}
