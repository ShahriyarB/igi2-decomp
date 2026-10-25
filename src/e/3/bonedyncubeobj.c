/* e/3/bonedyncubeobj.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: e/3/bonedyncubeobj.c:63  [anchor-mhash]
void __cdecl BoneDynCubeObj_SLERP(
        struct Quat32_t *ptDest,
        struct Quat32_t *ptSource1,
        struct Quat32_t *ptSource2,
        float t,
        int nBones)
{
  int v8; // ebp
  double v9; // st7
  long double v10; // st7
  long double v11; // st6
  long double v12; // rt0
  long double v13; // st5
  float v14; // [esp+Ch] [ebp-8h]
  float vDot; // [esp+10h] [ebp-4h]

  if ( nBones > 0 )
  {
    v8 = nBones;
    v14 = 1.0 - t;
    do
    {
      v9 = ptSource2->vW * ptSource1->vW
         + ptSource1->vX * ptSource2->vX
         + ptSource2->vY * ptSource1->vY
         + ptSource2->vZ * ptSource1->vZ;
      if ( v9 <= 0.9999899864196777 )
      {
        vDot = v9;
        v10 = acos(vDot);
        v11 = sin(v14 * v10);
        v12 = sin(v10 * t);
        v13 = 1.0 / sin(v10);
        ptDest->vX = (v11 * ptSource1->vX + v12 * ptSource2->vX) * v13;
        ptDest->vY = (v12 * ptSource2->vY + v11 * ptSource1->vY) * v13;
        ptDest->vZ = (v12 * ptSource2->vZ + v11 * ptSource1->vZ) * v13;
        ptDest->vW = (v12 * ptSource2->vW + v11 * ptSource1->vW) * v13;
      }
      else
      {
        ptDest->vX = t * ptSource2->vX + v14 * ptSource1->vX;
        ptDest->vY = v14 * ptSource1->vY + t * ptSource2->vY;
        ptDest->vZ = v14 * ptSource1->vZ + t * ptSource2->vZ;
        ptDest->vW = t * ptSource2->vW + v14 * ptSource1->vW;
      }
      ++ptSource1;
      ++ptSource2;
      ++ptDest;
      --v8;
    }
    while ( v8 );
  }
}

// source: e/3/bonedyncubeobj.c:112  [anchor-callee]
void __cdecl BoneDynCubeObj_UpdateHierarchy(struct BoneDynCubeObj_s *ptBoneDynCubeObj)
{
  struct BoneDynCubeObj_s *v1; // ecx
  struct real32x3_t *ptHierarchyTranslations; // ebx
  unsigned __int8 *v3; // ebp
  struct Bone_s *patBone; // esi
  float *p_vX; // edi
  struct QTask_s *ptHead; // edx
  int v7; // eax
  struct QTask_s *v8; // ecx
  int v9; // ebp
  void (__cdecl *pfHandler)(struct QTask_s *); // ecx
  int v11; // eax
  float *v12; // ecx
  int v13; // ebp
  void (__cdecl *pfCallback)(struct BoneDynCubeObj_s *, struct Bone_s *, struct Bone_s *); // ecx
  double vX; // st7
  double v16; // st6
  double v17; // st6
  double v18; // st5
  double v19; // st5
  double v20; // st4
  double v21; // st5
  double v22; // st5
  double v23; // st4
  double v24; // st5
  double v25; // st5
  double v26; // st7
  double v27; // st7
  double v28; // st6
  double v29; // st5
  double v30; // st4
  double v31; // st3
  double v32; // st2
  struct QTask_s *v33; // edx
  struct QTask_s *v34; // ecx
  int v35; // esi
  void (__cdecl *v36)(struct QTask_s *); // ecx
  int v37; // eax
  struct QTask_s *ptMagicObjContainer; // ecx
  int v39; // ecx
  struct QTask_s *v40; // edx
  int v41; // esi
  void (__cdecl *v42)(int); // edx
  int v43; // eax
  unsigned __int8 *pcHierarchy; // [esp+10h] [ebp-1Ch]
  unsigned __int8 *pcHierarchya; // [esp+10h] [ebp-1Ch]
  float vJ; // [esp+14h] [ebp-18h]
  float vJa; // [esp+14h] [ebp-18h]
  float vXZ; // [esp+18h] [ebp-14h]
  float vYW; // [esp+1Ch] [ebp-10h]
  float vYZ; // [esp+20h] [ebp-Ch]
  float vXW; // [esp+24h] [ebp-8h]
  int nChildren; // [esp+28h] [ebp-4h]
  float nChildrena; // [esp+28h] [ebp-4h]
  float nChildrenb; // [esp+28h] [ebp-4h]

  v1 = ptBoneDynCubeObj;
  ptHierarchyTranslations = ptBoneDynCubeObj->ptHierarchyTranslations;
  v3 = ptBoneDynCubeObj->pcHierarchy;
  patBone = ptBoneDynCubeObj->patBone;
  pcHierarchy = v3;
  p_vX = &patBone->tTranslation.vX;
  if ( ptBoneDynCubeObj->isTouched && v3 )
  {
    ptHead = ptBoneDynCubeObj->tModelObj.tDynCubeObj.tQObj.tQTask.tQTaskChildren.ptHead;
    if ( ptHead->ptNext && ptHead )
    {
      v7 = QTask_nProtectedQTaskStackOffset;
      do
      {
        if ( ptHead->ptNext )
          v8 = ptHead->ptNext->ptNext != nullptr ? ptHead->ptNext : nullptr;
        else
          v8 = nullptr;
        v9 = BoneDynCubeObj_eInterpolateQTaskEvent;
        QTask_atProtectedQTaskStack[v7].ptQTask = v8;
        pfHandler = (void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[v9][ptHead->eQTaskType].pfHandler;
        v11 = v7 + 1;
        QTask_nProtectedQTaskStackOffset = v11;
        if ( pfHandler )
        {
          pfHandler(ptHead);
          v11 = QTask_nProtectedQTaskStackOffset;
        }
        ptHead = (struct QTask_s *)dword_849C7DC[v11];
        v7 = v11 - 1;
        QTask_nProtectedQTaskStackOffset = v7;
      }
      while ( ptHead );
      v1 = ptBoneDynCubeObj;
      v3 = pcHierarchy;
    }
    else
    {
      v7 = QTask_nProtectedQTaskStackOffset;
    }
    nChildren = *v3;
    v12 = &v1->tRootTranslation.vX;
    pcHierarchya = v3 + 1;
    patBone->tTranslation.vX = *v12;
    patBone->tTranslation.vY = v12[1];
    v13 = nChildren;
    for ( patBone->tTranslation.vZ = v12[2];
          ;
          patBone->tTranslation.vZ = p_vX[11] * ptHierarchyTranslations->vY
                                   + p_vX[10] * ptHierarchyTranslations->vX
                                   + p_vX[12] * ptHierarchyTranslations->vZ
                                   + p_vX[2] )
    {
      pfCallback = patBone->pfCallback;
      if ( pfCallback )
      {
        pfCallback(ptBoneDynCubeObj, (struct Bone_s *)p_vX, patBone);
        v7 = QTask_nProtectedQTaskStackOffset;
      }
      vX = patBone->tOrientation.vX;
      ++patBone;
      ++ptHierarchyTranslations;
      v16 = patBone[-1].tOrientation.vY * patBone[-1].tOrientation.vX;
      v17 = v16 + v16;
      v18 = patBone[-1].tOrientation.vZ * patBone[-1].tOrientation.vX;
      vXZ = v18 + v18;
      v19 = patBone[-1].tOrientation.vW * patBone[-1].tOrientation.vX;
      vXW = v19 + v19;
      v20 = patBone[-1].tOrientation.vY * patBone[-1].tOrientation.vY;
      nChildrena = v20 + v20;
      v21 = patBone[-1].tOrientation.vY * patBone[-1].tOrientation.vZ;
      vYZ = v21 + v21;
      v22 = patBone[-1].tOrientation.vW * patBone[-1].tOrientation.vY;
      vYW = v22 + v22;
      v23 = patBone[-1].tOrientation.vZ * patBone[-1].tOrientation.vZ;
      vJ = v23 + v23;
      v24 = patBone[-1].tOrientation.vW * patBone[-1].tOrientation.vZ;
      v25 = v24 + v24;
      patBone[-1].tMatrix.tX.vX = 1.0 - nChildrena - vJ;
      patBone[-1].tMatrix.tX.vY = v17 - v25;
      patBone[-1].tMatrix.tX.vZ = vYW + vXZ;
      patBone[-1].tMatrix.tY.vX = v25 + v17;
      v26 = 1.0 - (vX * vX + vX * vX);
      patBone[-1].tMatrix.tY.vY = v26 - vJ;
      patBone[-1].tMatrix.tY.vZ = vYZ - vXW;
      patBone[-1].tMatrix.tZ.vX = vXZ - vYW;
      patBone[-1].tMatrix.tZ.vY = vYZ + vXW;
      patBone[-1].tMatrix.tZ.vZ = v26 - nChildrena;
      if ( v13 <= 0 )
        break;
LABEL_20:
      --v13;
      v27 = (p_vX[16] - p_vX[15]) * (patBone->tOrientation.vY - patBone->tOrientation.vZ);
      v28 = (patBone->tOrientation.vY + patBone->tOrientation.vZ) * (p_vX[17] - p_vX[14]);
      v29 = (p_vX[16] + p_vX[15]) * (patBone->tOrientation.vW - patBone->tOrientation.vX);
      nChildrenb = (patBone->tOrientation.vY + patBone->tOrientation.vX) * (p_vX[16] + p_vX[14]);
      v30 = (patBone->tOrientation.vW - patBone->tOrientation.vZ) * (p_vX[17] + p_vX[15]);
      v31 = (p_vX[17] - p_vX[15]) * (patBone->tOrientation.vW + patBone->tOrientation.vZ);
      v32 = v31 + v30 + nChildrenb;
      vJa = ((p_vX[16] - p_vX[14]) * (patBone->tOrientation.vX - patBone->tOrientation.vY) + v32) * 0.5;
      patBone->tOrientation.vX = (p_vX[14] + p_vX[17]) * (patBone->tOrientation.vW + patBone->tOrientation.vX)
                               + vJa
                               - v32;
      patBone->tOrientation.vY = vJa + v28 - v31;
      patBone->tOrientation.vZ = vJa + v29 - v30;
      patBone->tOrientation.vW = vJa + v27 - nChildrenb;
      patBone->tTranslation.vX = p_vX[5] * ptHierarchyTranslations->vY
                               + p_vX[4] * ptHierarchyTranslations->vX
                               + p_vX[6] * ptHierarchyTranslations->vZ
                               + *p_vX;
      patBone->tTranslation.vY = p_vX[8] * ptHierarchyTranslations->vY
                               + p_vX[7] * ptHierarchyTranslations->vX
                               + p_vX[9] * ptHierarchyTranslations->vZ
                               + p_vX[1];
    }
    while ( 1 )
    {
      p_vX += 20;
      if ( p_vX == (float *)patBone )
        break;
      v13 = *pcHierarchya++;
      if ( v13 )
        goto LABEL_20;
    }
    v33 = ptBoneDynCubeObj->tModelObj.tDynCubeObj.tQObj.tQTask.tQTaskChildren.ptHead;
    ptBoneDynCubeObj->isTouched = 0;
    if ( v33->ptNext && v33 )
    {
      do
      {
        if ( v33->ptNext )
          v34 = v33->ptNext->ptNext != nullptr ? v33->ptNext : nullptr;
        else
          v34 = nullptr;
        v35 = Attach_eUpdateAttachmentEvent;
        QTask_atProtectedQTaskStack[v7].ptQTask = v34;
        v36 = (void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[v35][v33->eQTaskType].pfHandler;
        v37 = v7 + 1;
        QTask_nProtectedQTaskStackOffset = v37;
        if ( v36 )
        {
          v36(v33);
          v37 = QTask_nProtectedQTaskStackOffset;
        }
        v33 = (struct QTask_s *)dword_849C7DC[v37];
        v7 = v37 - 1;
        QTask_nProtectedQTaskStackOffset = v7;
      }
      while ( v33 );
    }
    ptMagicObjContainer = ptBoneDynCubeObj->tModelObj.ptMagicObjContainer;
    if ( ptMagicObjContainer )
    {
      v39 = (int)ptMagicObjContainer->tQTaskChildren.ptHead;
      if ( *(_DWORD *)v39 )
      {
        for ( ; v39; QTask_nProtectedQTaskStackOffset = v7 )
        {
          if ( *(_DWORD *)v39 )
            v40 = **(_DWORD **)v39 != 0 ? *(struct QTask_s **)v39 : nullptr;
          else
            v40 = nullptr;
          v41 = Attach_eUpdateAttachmentEvent;
          QTask_atProtectedQTaskStack[v7].ptQTask = v40;
          v42 = (void (__cdecl *)(int))QTask_aatQTaskFinalEvent[v41][*(unsigned __int16 *)(v39 + 36)].pfHandler;
          v43 = v7 + 1;
          QTask_nProtectedQTaskStackOffset = v43;
          if ( v42 )
          {
            v42(v39);
            v43 = QTask_nProtectedQTaskStackOffset;
          }
          v39 = dword_849C7DC[v43];
          v7 = v43 - 1;
        }
      }
    }
  }
}

// source: e/3/bonedyncubeobj.c:260  [anchor-mhash]
void __cdecl BoneDynCubeObj_DebugDraw(struct BoneDynCubeObj_s *ptBoneDynCubeObj)
{
  #pragma pack(push, 1)
  union
  {
    struct { unsigned __int8 *pcHierarchy; };
    struct { unsigned __int8 *pcHierarchya; };
    struct { char igi2_o2[4]; int nChildren; };
    struct { char igi2_o3[8]; struct Bone_s *ptSource; };
    struct { char igi2_o4[12]; int iBone; };
    struct { char igi2_o5[16]; struct Bone_s *ptDest; };
    struct { char igi2_o6[20]; struct real64x3_t *v18; };
    struct { char igi2_o7[24]; struct real32x3_t tColor; };
    struct { char igi2_o8[36]; struct real64x3_t tStart; };
    struct { char igi2_o9[60]; struct real64x3_t tEnd; };
    char igi2_extent[84];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct Bone_s *patBone; // eax
  struct real64x3_t *p_tPos; // ebx
  int v3; // esi
  int v4; // edx
  double vX; // st7
  struct Bone_s *v6; // esi
  float *p_vX; // eax
  bool v8; // zf
  int v9; // ecx
  double v10; // st7
  double v11; // st7

  patBone = ptBoneDynCubeObj->patBone;
  p_tPos = &ptBoneDynCubeObj->tModelObj.tDynCubeObj.tQObj.tPos;
  igi2_frame.pcHierarchya = ptBoneDynCubeObj->pcHierarchy;
  qmemcpy(&igi2_frame.tStart, &ptBoneDynCubeObj->tModelObj.tDynCubeObj.tQObj.tPos, sizeof(igi2_frame.tStart));
  v3 = *igi2_frame.pcHierarchya;
  v4 = 0;
  igi2_frame.ptSource = patBone;
  igi2_frame.ptDest = patBone;
  igi2_frame.iBone = 0;
  igi2_frame.tColor.vX = 1.0;
  igi2_frame.tColor.vY = 0.0;
  igi2_frame.tColor.vZ = 0.0;
  igi2_frame.v18 = &ptBoneDynCubeObj->tModelObj.tDynCubeObj.tQObj.tPos;
  igi2_frame.nChildren = v3;
  igi2_frame.pcHierarchy = igi2_frame.pcHierarchya + 1;
  while ( 1 )
  {
    vX = patBone->tTranslation.vX;
    qmemcpy(&igi2_frame.tEnd, p_tPos, sizeof(igi2_frame.tEnd));
    igi2_frame.tEnd.vX = vX + igi2_frame.tEnd.vX;
    igi2_frame.tEnd.vY = patBone->tTranslation.vY + igi2_frame.tEnd.vY;
    igi2_frame.tEnd.vZ = patBone->tTranslation.vZ + igi2_frame.tEnd.vZ;
    if ( v4 == 1 )
    {
      igi2_frame.tColor.vX = 0.0;
      igi2_frame.tColor.vZ = 1.0;
    }
    if ( v4 == 4 )
    {
      igi2_frame.tColor.vX = 0.0;
      igi2_frame.tColor.vZ = 1.0;
    }
    if ( v4 == 7 )
    {
      igi2_frame.tColor.vX = 0.0;
      igi2_frame.tColor.vZ = 1.0;
    }
    if ( v4 == 10 )
    {
      igi2_frame.tColor.vX = 0.0;
      igi2_frame.tColor.vZ = 1.0;
    }
    if ( v4 == 15 )
    {
      igi2_frame.tColor.vX = 0.0;
      igi2_frame.tColor.vZ = 1.0;
    }
    Line_RegisterLine3D(&igi2_frame.tStart, &igi2_frame.tEnd, &igi2_frame.tColor, 1.0, &igi2_frame.tColor, 1.0);
    v6 = igi2_frame.ptDest + 1;
    igi2_frame.tColor.vX = 1.0;
    igi2_frame.tColor.vY = 1.0;
    igi2_frame.tColor.vZ = 0.0;
    ++igi2_frame.iBone;
    ++igi2_frame.ptDest;
    if ( igi2_frame.nChildren <= 0 )
      break;
    p_vX = &igi2_frame.ptSource->tTranslation.vX;
LABEL_17:
    v10 = *p_vX;
    p_tPos = igi2_frame.v18;
    v4 = igi2_frame.iBone;
    --igi2_frame.nChildren;
    qmemcpy(&igi2_frame.tStart, igi2_frame.v18, sizeof(igi2_frame.tStart));
    igi2_frame.tStart.vX = v10 + igi2_frame.tStart.vX;
    igi2_frame.tStart.vY = p_vX[1] + igi2_frame.tStart.vY;
    v11 = p_vX[2] + igi2_frame.tStart.vZ;
    patBone = igi2_frame.ptDest;
    igi2_frame.tStart.vZ = v11;
  }
  while ( 1 )
  {
    p_vX = &igi2_frame.ptSource[1].tTranslation.vX;
    v8 = v6 == &igi2_frame.ptSource[1];
    ++igi2_frame.ptSource;
    if ( v8 )
      break;
    v9 = *igi2_frame.pcHierarchy;
    igi2_frame.tColor.vZ = 0.0;
    igi2_frame.nChildren = v9;
    ++igi2_frame.pcHierarchy;
    if ( v9 )
      goto LABEL_17;
  }
}

// source: e/3/bonedyncubeobj.c:329  [anchor-mhash]
struct BoneDynCubeObj_s *__cdecl BoneDynCubeObj_CreateAttachObjects(
        struct BoneDynCubeObj_s *ptBoneDynCubeObj,
        struct QTask_s *ptParent,
        struct QTask_s *ptCreator)
{
  struct BoneDynCubeObj_s *result; // eax
  int ptPrev_high; // edi
  int v6; // esi

  result = (struct BoneDynCubeObj_s *)ptBoneDynCubeObj->tModelObj.ptLODVirModel;
  if ( result )
  {
    result = (struct BoneDynCubeObj_s *)result->tModelObj.tDynCubeObj.tQObj.tQTask.ptNext;
    ptPrev_high = SHIWORD(result->tModelObj.tDynCubeObj.tQObj.tQTask.tQTaskChildren.ptMiddle->tQTaskChildren.ptMiddle[3].ptPrev);
    if ( ptPrev_high > 0 )
    {
      v6 = 0;
      do
      {
        result = (struct BoneDynCubeObj_s *)ModelObj_CreateAttachObject(
                                              &ptBoneDynCubeObj->tModelObj,
                                              ptParent,
                                              ptCreator,
                                              &ptBoneDynCubeObj->tModelObj.ptLODVirModel->aptVirModel[0]->ptModel->ptMesh->ptAttachObject[v6++],
                                              true,
                                              true);
        --ptPrev_high;
      }
      while ( ptPrev_high );
    }
  }
  return result;
}

// source: e/3/bonedyncubeobj.c:373  [anchor-mhash]
enum bool __cdecl BoneDynCubeObj_SphereIntersectionCheck(
        struct BoneDynCubeObj_s *ptBoneDynCubeObj,
        struct real64x3_t *ptStartPos,
        struct real64x3_t *ptEndPos)
{
  double v3; // st7
  float v4; // eax
  float v5; // eax
  float v6; // eax
  float v7; // eax
  float v8; // eax
  double v9; // st6
  enum bool result; // eax
  float vRadius; // [esp+8h] [ebp-60h]
  float vRadiusa; // [esp+8h] [ebp-60h]
  float v13; // [esp+Ch] [ebp-5Ch]
  float tStartPos; // [esp+18h] [ebp-50h]
  float tStartPos_4; // [esp+1Ch] [ebp-4Ch]
  float tStartPos_8a; // [esp+20h] [ebp-48h]
  float tStartPos_8; // [esp+20h] [ebp-48h]
  float tEndPosa; // [esp+28h] [ebp-40h]
  float tEndPos; // [esp+28h] [ebp-40h]
  float tEndPos_4a; // [esp+2Ch] [ebp-3Ch]
  float tEndPos_4; // [esp+2Ch] [ebp-3Ch]
  float tEndPos_8a; // [esp+30h] [ebp-38h]
  float tEndPos_8; // [esp+30h] [ebp-38h]
  float tCurrentDelta; // [esp+38h] [ebp-30h]
  float tCurrentDeltaa; // [esp+38h] [ebp-30h]
  float tCurrentDelta_4; // [esp+3Ch] [ebp-2Ch]
  float tCurrentDelta_4a; // [esp+3Ch] [ebp-2Ch]
  float tCurrentDelta_8; // [esp+40h] [ebp-28h]
  float tCurrentDelta_8a; // [esp+40h] [ebp-28h]
  float tDelta; // [esp+44h] [ebp-24h]
  float tDelta_4; // [esp+48h] [ebp-20h]
  float tDelta_8; // [esp+4Ch] [ebp-1Ch]
  float tMax; // [esp+50h] [ebp-18h]
  float tMax_4; // [esp+54h] [ebp-14h]
  float tMin_4; // [esp+60h] [ebp-8h]
  float tMin_8; // [esp+64h] [ebp-4h]

  vRadius = ptBoneDynCubeObj->vRadius;
  tStartPos_8a = ptStartPos->vZ - ptBoneDynCubeObj->tModelObj.tDynCubeObj.tQObj.tPos.vZ;
  tEndPosa = ptEndPos->vX - ptBoneDynCubeObj->tModelObj.tDynCubeObj.tQObj.tPos.vX;
  tEndPos_4a = ptEndPos->vY - ptBoneDynCubeObj->tModelObj.tDynCubeObj.tQObj.tPos.vY;
  tEndPos_8a = ptEndPos->vZ - ptBoneDynCubeObj->tModelObj.tDynCubeObj.tQObj.tPos.vZ;
  tCurrentDelta = ptBoneDynCubeObj->tModelObj.tOrientation.tX.vY * ptBoneDynCubeObj->tRootTranslation.vY
                + ptBoneDynCubeObj->tModelObj.tOrientation.tX.vX * ptBoneDynCubeObj->tRootTranslation.vX
                + ptBoneDynCubeObj->tModelObj.tOrientation.tX.vZ * ptBoneDynCubeObj->tRootTranslation.vZ;
  tCurrentDelta_4 = ptBoneDynCubeObj->tModelObj.tOrientation.tY.vY * ptBoneDynCubeObj->tRootTranslation.vY
                  + ptBoneDynCubeObj->tModelObj.tOrientation.tY.vX * ptBoneDynCubeObj->tRootTranslation.vX
                  + ptBoneDynCubeObj->tModelObj.tOrientation.tY.vZ * ptBoneDynCubeObj->tRootTranslation.vZ;
  tCurrentDelta_8 = ptBoneDynCubeObj->tModelObj.tOrientation.tZ.vY * ptBoneDynCubeObj->tRootTranslation.vY
                  + ptBoneDynCubeObj->tModelObj.tOrientation.tZ.vX * ptBoneDynCubeObj->tRootTranslation.vX
                  + ptBoneDynCubeObj->tModelObj.tOrientation.tZ.vZ * ptBoneDynCubeObj->tRootTranslation.vZ;
  tStartPos = ptStartPos->vX - ptBoneDynCubeObj->tModelObj.tDynCubeObj.tQObj.tPos.vX - tCurrentDelta;
  tStartPos_4 = ptStartPos->vY - ptBoneDynCubeObj->tModelObj.tDynCubeObj.tQObj.tPos.vY - tCurrentDelta_4;
  tStartPos_8 = tStartPos_8a - tCurrentDelta_8;
  tEndPos = tEndPosa - tCurrentDelta;
  tEndPos_4 = tEndPos_4a - tCurrentDelta_4;
  tEndPos_8 = tEndPos_8a - tCurrentDelta_8;
  if ( tStartPos >= (double)tEndPos )
    v3 = tEndPos;
  else
    v3 = tStartPos;
  v4 = ptStartPos->vY - ptBoneDynCubeObj->tModelObj.tDynCubeObj.tQObj.tPos.vY - tCurrentDelta_4;
  if ( tStartPos_4 >= (double)tEndPos_4 )
    v4 = tEndPos_4;
  tMin_4 = v4;
  v5 = tStartPos_8;
  if ( tStartPos_8 >= (double)tEndPos_8 )
    v5 = tEndPos_8;
  tMin_8 = v5;
  v6 = tStartPos;
  if ( tStartPos <= (double)tEndPos )
    v6 = tEndPos;
  tMax = v6;
  v7 = tStartPos_4;
  if ( tStartPos_4 <= (double)tEndPos_4 )
    v7 = tEndPos_4;
  tMax_4 = v7;
  v8 = tStartPos_8;
  if ( tStartPos_8 <= (double)tEndPos_8 )
    v8 = tEndPos_8;
  tDelta = ptEndPos->vX - ptStartPos->vX;
  tDelta_4 = ptEndPos->vY - ptStartPos->vY;
  tDelta_8 = ptEndPos->vZ - ptStartPos->vZ;
  tCurrentDeltaa = -tStartPos;
  tCurrentDelta_4a = -tStartPos_4;
  v9 = -tStartPos_8;
  tCurrentDelta_8a = v9;
  v13 = tCurrentDelta_8a * tDelta_8 + tCurrentDelta_4a * tDelta_4 + tCurrentDeltaa * tDelta;
  result = false;
  if ( vRadius * vRadius >= tCurrentDeltaa * tCurrentDeltaa
                          + tCurrentDelta_4a * tCurrentDelta_4a
                          + v9 * v9
                          - 1.0 / (tDelta * tDelta + tDelta_4 * tDelta_4 + tDelta_8 * tDelta_8) * (v13 * v13)
    && v3 <= vRadius
    && tMin_4 <= (double)vRadius
    && tMin_8 <= (double)vRadius )
  {
    vRadiusa = -vRadius;
    if ( tMax >= (double)vRadiusa && tMax_4 >= (double)vRadiusa && v8 >= (double)vRadiusa )
      return true;
  }
  return result;
}

// source: e/3/bonedyncubeobj.c:449  [size]
void __cdecl BoneDynCubeObj_RunHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptHead; // ecx
  int v2; // edx
  struct QTask_s *v3; // eax
  void (__cdecl *pfHandler)(struct QTask_s *); // eax
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
      pfHandler = (void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[1][ptHead->eQTaskType].pfHandler;
      v5 = v2 + 1;
      QTask_nProtectedQTaskStackOffset = v5;
      if ( pfHandler )
      {
        pfHandler(ptHead);
        v5 = QTask_nProtectedQTaskStackOffset;
      }
      ptHead = (struct QTask_s *)dword_849C7DC[v5];
      v2 = v5 - 1;
      QTask_nProtectedQTaskStackOffset = v2;
    }
    while ( ptHead );
  }
}

// source: e/3/bonedyncubeobj.c:466  [anchor-mhash]
void __cdecl BoneDynCubeObj_DeleteHandler(struct QTask_s *ptQTask)
{
  World_RemoveDynCubeObj(World_ptActiveWorld, (struct DynCubeObj_s *)ptQTask);
  BoneDynCubeObj_SetLODVirModel((struct BoneDynCubeObj_s *)ptQTask, nullptr);
}

// source: e/3/bonedyncubeobj.c:488  [anchor-mhash]
void __cdecl BoneDynCubeObj_AttachHandler(struct QTask_s *ptQTask, void *pxContext)
{
  int v2; // eax
  int v3; // esi
  int v4; // eax
  struct QTask_s **p_ptPrev; // eax
  struct QTask_s *v6; // edx

  v2 = *((_DWORD *)pxContext + 1);
  v3 = 0;
  if ( v2 < 0 )
  {
    p_ptPrev = &ptQTask[3].ptPrev;
    v6 = ptQTask + 1;
    *((_DWORD *)pxContext + 5) = 0;
  }
  else
  {
    v4 = 80 * v2;
    *((_DWORD *)pxContext + 5) = *(_DWORD *)&ptQTask[7].eQTaskType + v4 + 16;
    v3 = v4 + *(_DWORD *)&ptQTask[7].eQTaskType;
    p_ptPrev = &ptQTask[3].ptPrev;
    v6 = ptQTask + 1;
  }
  *((_DWORD *)pxContext + 4) = v3;
  *((_DWORD *)pxContext + 3) = p_ptPrev;
  *((_DWORD *)pxContext + 2) = v6;
}

// source: e/3/bonedyncubeobj.c:524  [size]
void __cdecl BoneDynCubeObj_CollisionEvaluateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_BYTE *)pxContext = *((_DWORD *)pxContext + 1) != (_DWORD)ptQTask;
}

// source: e/3/bonedyncubeobj.c:540  [anchor-mhash]
void __cdecl BoneDynCubeObj_TraceLinesHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { float v103; };
    struct { float v104; };
    struct { float v105; };
    struct { float v106; };
    struct { float *v107; };
    struct { float v108; };
    struct { float v109; };
    struct { float v110; };
    struct { char igi2_o8[4]; int v111; };
    struct { char igi2_o9[4]; int v112; };
    struct { char igi2_o10[4]; float *v113; };
    struct { char igi2_o11[4]; float v114; };
    struct { char igi2_o12[10]; bool v115; };
    struct { char igi2_o13[11]; char v116; };
    struct { char igi2_o14[12]; int i; };
    struct { char igi2_o15[12]; float v118; };
    struct { char igi2_o16[12]; unsigned __int16 *v119; };
    struct { char igi2_o17[12]; struct QMaterial_t *v120; };
    struct { char igi2_o18[19]; char v121; };
    struct { char igi2_o19[20]; int v122; };
    struct { char igi2_o20[20]; int v123; };
    struct { char igi2_o21[20]; int v124; };
    struct { char igi2_o22[20]; float v125; };
    struct { char igi2_o23[20]; float v126; };
    struct { char igi2_o24[24]; float v127; };
    struct { char igi2_o25[28]; float v128; };
    struct { char igi2_o26[32]; float v129; };
    struct { char igi2_o27[36]; float v130; };
    struct { char igi2_o28[40]; float v131; };
    struct { char igi2_o29[44]; float v132; };
    struct { char igi2_o30[51]; char v133; };
    struct { char igi2_o31[52]; double v134; };
    struct { char igi2_o32[52]; double v135; };
    struct { char igi2_o33[52]; double v136; };
    struct { char igi2_o34[60]; float v137; };
    struct { char igi2_o35[60]; float v138; };
    struct { char igi2_o36[60]; float v139; };
    struct { char igi2_o37[60]; float v140; };
    struct { char igi2_o38[60]; float v141; };
    struct { char igi2_o39[64]; float v142; };
    struct { char igi2_o40[64]; float v143; };
    struct { char igi2_o41[64]; float v144; };
    struct { char igi2_o42[64]; float v145; };
    struct { char igi2_o43[64]; float v146; };
    struct { char igi2_o44[68]; float v147; };
    struct { char igi2_o45[68]; float v148; };
    struct { char igi2_o46[68]; float v149; };
    struct { char igi2_o47[68]; float v150; };
    struct { char igi2_o48[68]; float v151; };
    struct { char igi2_o49[72]; float v152; };
    struct { char igi2_o50[76]; float v153; };
    struct { char igi2_o51[80]; float v154; };
    struct { char igi2_o52[84]; float v155; };
    struct { char igi2_o53[88]; float v156; };
    struct { char igi2_o54[92]; float v157; };
    struct { char igi2_o55[96]; int *v158; };
    struct { char igi2_o56[100]; double v159; };
    struct { char igi2_o57[100]; float v160; };
    struct { char igi2_o58[100]; float v161; };
    struct { char igi2_o59[100]; float v162; };
    struct { char igi2_o60[112]; float v163; };
    struct { char igi2_o61[116]; float v164; };
    struct { char igi2_o62[120]; float v165; };
    struct { char igi2_o63[128]; float v166; };
    struct { char igi2_o64[136]; float *v167; };
    struct { char igi2_o65[136]; float v168; };
    struct { char igi2_o66[140]; double v169; };
    struct { char igi2_o67[140]; double v170; };
    struct { char igi2_o68[140]; double v171; };
    struct { char igi2_o69[152]; float v172; };
    struct { char igi2_o70[156]; float v173; };
    struct { char igi2_o71[160]; float v174; };
    struct { char igi2_o72[164]; struct real64x3_t *ptStartPos; };
    struct { char igi2_o73[168]; int v176; };
    struct { char igi2_o74[168]; float *v177; };
    struct { char igi2_o75[172]; struct real64x3_t *ptEndPos; };
    struct { char igi2_o76[176]; unsigned __int16 *v179; };
    struct { char igi2_o77[180]; int v180; };
    struct { char igi2_o78[184]; float v181; };
    struct { char igi2_o79[184]; float *v182; };
    struct { char igi2_o80[188]; double v183; };
    struct { char igi2_o81[204]; float v184; };
    struct { char igi2_o82[204]; float v185; };
    struct { char igi2_o83[204]; float v186; };
    struct { char igi2_o84[204]; float v187; };
    struct { char igi2_o85[204]; float v188; };
    struct { char igi2_o86[208]; float v189; };
    struct { char igi2_o87[212]; float v190; };
    struct { char igi2_o88[216]; float v191; };
    struct { char igi2_o89[220]; int v192; };
    struct { char igi2_o90[224]; int v193; };
    struct { char igi2_o91[228]; double v194; };
    struct { char igi2_o92[236]; double v195; };
    struct { char igi2_o93[244]; double v196; };
    struct { char igi2_o94[252]; double v197; };
    struct { char igi2_o95[260]; double v198; };
    struct { char igi2_o96[268]; double v199; };
    struct { char igi2_o97[276]; float v200; };
    struct { char igi2_o98[280]; float v201; };
    struct { char igi2_o99[288]; float v202; };
    struct { char igi2_o100[292]; float v203; };
    struct { char igi2_o101[296]; float v204; };
    struct { char igi2_o102[300]; float v205; };
    struct { char igi2_o103[304]; float v206; };
    struct { char igi2_o104[308]; float v207; };
    struct { char igi2_o105[312]; float v208; };
    struct { char igi2_o106[324]; _DWORD v209[4096]; };
    struct { char igi2_o107[16708]; _DWORD v210[12288]; };
    char igi2_extent[65860];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v2; // eax
  float *v3; // ebx
  int v4; // eax
  int v5; // edx
  int v6; // ecx
  bool v7; // zf
  int *v8; // ecx
  int v9; // esi
  __int16 v10; // ax
  void (__cdecl *pfHandler)(struct QTask_s *, _DWORD); // eax
  double v12; // st7
  double v13; // st7
  double v14; // st7
  double v15; // st7
  double v16; // st7
  double v17; // st7
  int v18; // ecx
  double v19; // st7
  int v20; // edx
  int v21; // eax
  int v22; // edx
  double v23; // st7
  float *v24; // eax
  double v25; // st7
  int v26; // esi
  double v27; // st6
  double v28; // st7
  double v29; // st6
  float *v30; // eax
  float *v31; // ebx
  int v32; // eax
  double v33; // st7
  float *v34; // eax
  double v35; // st7
  double v36; // st6
  double v37; // st7
  double v38; // st6
  float *v39; // eax
  int v40; // eax
  double v41; // st7
  float *v42; // eax
  double v43; // st7
  double v44; // st6
  double v45; // st7
  double v46; // st6
  float *v47; // eax
  int v48; // eax
  double v49; // st7
  float *v50; // eax
  double v51; // st7
  double v52; // st6
  double v53; // st7
  double v54; // st6
  float *v55; // eax
  int v56; // eax
  int v57; // edx
  double v58; // st7
  float *v59; // eax
  double v60; // st7
  double v61; // st6
  double v62; // st7
  double v63; // st6
  float *v64; // eax
  float *v65; // edx
  double v66; // st7
  double v67; // st7
  double v68; // st7
  double v69; // st7
  double v70; // st6
  double v71; // st7
  double v72; // st7
  double v73; // st6
  double v74; // st7
  double v75; // st7
  double v76; // st7
  double v77; // st6
  double v78; // st7
  double v79; // st7
  double v80; // st6
  double v81; // st7
  double v82; // st7
  char v83; // al
  double v84; // st7
  double v85; // st7
  double v86; // st7
  double v87; // st7
  double v88; // st7
  double v89; // st7
  unsigned __int16 v90; // ax
  double v91; // st7
  double v92; // st6
  double v93; // st5
  double v94; // st4
  double v95; // st7
  double v96; // st5
  double v97; // st7
  double v98; // st7
  double v99; // st6
  double v100; // st6
  int v101; // eax
  int v102; // edx

  igi2_frame.v111 = *((_DWORD *)pxContext + 9);
  igi2_frame.ptEndPos = *((struct real64x3_t **)pxContext + 1);
  v2 = *(_DWORD *)&ptQTask[2].eQTaskType;
  igi2_frame.ptStartPos = *(struct real64x3_t **)pxContext;
  v3 = (float *)igi2_frame.v210;
  igi2_frame.v192 = 0;
  if ( v2 )
  {
    v4 = *(_DWORD *)(*(_DWORD *)(*(_DWORD *)v2 + 12) + 12);
    if ( !*(_DWORD *)(v4 + 40) )
    {
      v5 = *(_DWORD *)(v4 + 44);
      v6 = 32 * *((_DWORD *)pxContext + 5);
      v7 = v5 + v6 == 0;
      v8 = (int *)(v5 + v6);
      igi2_frame.v158 = v8;
      if ( !v7 )
      {
        if ( *v8 )
        {
          BoneDynCubeObj_UpdateHierarchy((struct BoneDynCubeObj_s *)ptQTask);
          v9 = igi2_frame.v158[5];
          igi2_frame.v180 = igi2_frame.v158[1];
          v10 = *((_WORD *)pxContext + 6);
          if ( v10 == 512
            || (pfHandler = (void (__cdecl *)(struct QTask_s *, _DWORD))QTask_aatQTaskFinalEvent[v10][ptQTask->eQTaskType].pfHandler) == nullptr
            || (pfHandler(ptQTask, *((_DWORD *)pxContext + 4)), **((_BYTE **)pxContext + 4)) )
          {
            igi2_frame.v193 = 0;
            if ( *((int *)pxContext + 2) > 0 )
            {
              while ( 1 )
              {
                if ( *(_DWORD *)(igi2_frame.v111 + 92) )
                  igi2_frame.v115 = *(_DWORD *)(igi2_frame.v111 + 80) != 0;
                else
                  igi2_frame.v115 = 0;
                igi2_frame.v121 = *(_BYTE *)(igi2_frame.v111 + 92);
                igi2_frame.v133 = 0;
                if ( BoneDynCubeObj_SphereIntersectionCheck((struct BoneDynCubeObj_s *)ptQTask, igi2_frame.ptStartPos, igi2_frame.ptEndPos) == false )
                {
                  v18 = igi2_frame.v111;
                  goto LABEL_155;
                }
                igi2_frame.v130 = igi2_frame.ptStartPos->vX - *(double *)&ptQTask[1].ptNext;
                igi2_frame.v131 = igi2_frame.ptStartPos->vY - *(double *)&ptQTask[1].tQTaskChildren.ptHead;
                igi2_frame.v132 = igi2_frame.ptStartPos->vZ - *(double *)&ptQTask[1].tQTaskChildren.ptTail;
                igi2_frame.v155 = igi2_frame.ptEndPos->vX - *(double *)&ptQTask[1].ptNext;
                igi2_frame.v156 = igi2_frame.ptEndPos->vY - *(double *)&ptQTask[1].tQTaskChildren.ptHead;
                igi2_frame.v157 = igi2_frame.ptEndPos->vZ - *(double *)&ptQTask[1].tQTaskChildren.ptTail;
                if ( igi2_frame.v130 >= (double)igi2_frame.v155 )
                  v12 = igi2_frame.v155;
                else
                  v12 = igi2_frame.v130;
                igi2_frame.v197 = v12 - 40.959999084472656;
                if ( igi2_frame.v131 >= (double)igi2_frame.v156 )
                  v13 = igi2_frame.v156;
                else
                  v13 = igi2_frame.v131;
                igi2_frame.v198 = v13 - 40.959999084472656;
                if ( igi2_frame.v132 >= (double)igi2_frame.v157 )
                  v14 = igi2_frame.v157;
                else
                  v14 = igi2_frame.v132;
                igi2_frame.v199 = v14 - 40.959999084472656;
                if ( igi2_frame.v130 <= (double)igi2_frame.v155 )
                  v15 = igi2_frame.v155;
                else
                  v15 = igi2_frame.v130;
                igi2_frame.v194 = v15 + 40.959999084472656;
                if ( igi2_frame.v131 <= (double)igi2_frame.v156 )
                  v16 = igi2_frame.v156;
                else
                  v16 = igi2_frame.v131;
                igi2_frame.v195 = v16 + 40.959999084472656;
                if ( igi2_frame.v132 <= (double)igi2_frame.v157 )
                  v17 = igi2_frame.v157;
                else
                  v17 = igi2_frame.v132;
                igi2_frame.v164 = igi2_frame.ptEndPos->vY - *(double *)&ptQTask[1].tQTaskChildren.ptHead;
                igi2_frame.v196 = v17 + 40.959999084472656;
                igi2_frame.v189 = igi2_frame.ptEndPos->vX - igi2_frame.ptStartPos->vX;
                igi2_frame.v190 = igi2_frame.ptEndPos->vY - igi2_frame.ptStartPos->vY;
                igi2_frame.v191 = igi2_frame.ptEndPos->vZ - igi2_frame.ptStartPos->vZ;
                igi2_frame.v165 = igi2_frame.ptEndPos->vZ - *(double *)&ptQTask[1].tQTaskChildren.ptTail;
                v18 = igi2_frame.v111;
                igi2_frame.v163 = igi2_frame.ptEndPos->vX - *(double *)&ptQTask[1].ptNext;
                igi2_frame.v181 = sqrt((igi2_frame.v155 - igi2_frame.v130) * (igi2_frame.v155 - igi2_frame.v130) + (igi2_frame.v156 - igi2_frame.v131) * (igi2_frame.v156 - igi2_frame.v131) + (igi2_frame.v157 - igi2_frame.v132)
                                                                                          * (igi2_frame.v157 - igi2_frame.v132));
                if ( igi2_frame.v121 )
                {
                  igi2_frame.v163 = *(double *)(igi2_frame.v111 + 8) - *(double *)&ptQTask[1].ptNext;
                  igi2_frame.v164 = *(double *)(igi2_frame.v111 + 16) - *(double *)&ptQTask[1].tQTaskChildren.ptHead;
                  v19 = *(double *)(igi2_frame.v111 + 24) - *(double *)&ptQTask[1].tQTaskChildren.ptTail;
                  igi2_frame.v165 = v19;
                  igi2_frame.v183 = sqrt((igi2_frame.v163 - igi2_frame.v130) * (igi2_frame.v163 - igi2_frame.v130) + (igi2_frame.v164 - igi2_frame.v131) * (igi2_frame.v164 - igi2_frame.v131) + (v19 - igi2_frame.v132)
                                                                                            * (v19 - igi2_frame.v132));
                }
                if ( !igi2_frame.v192 )
                {
                  v20 = igi2_frame.v180;
                  igi2_frame.v112 = 0;
                  if ( igi2_frame.v180 >= 4 )
                  {
                    for ( igi2_frame.i = 3; igi2_frame.i < igi2_frame.v180; igi2_frame.i += 4 )
                    {
                      v21 = *(_DWORD *)&ptQTask[7].eQTaskType;
                      v22 = 80 * *(_DWORD *)(v9 + 12);
                      v23 = *(float *)(v21 + v22 + 20);
                      v24 = (float *)(v22 + v21);
                      v25 = v23 * *(float *)(v9 + 4);
                      v26 = v9 + 20;
                      v27 = v24[8] * *(float *)(v26 - 16)
                          + v24[9] * *(float *)(v26 - 12)
                          + v24[7] * *(float *)(v26 - 20);
                      igi2_frame.v184 = v24[11] * *(float *)(v26 - 16)
                           + v24[12] * *(float *)(v26 - 12)
                           + v24[10] * *(float *)(v26 - 20);
                      igi2_frame.v103 = v25 + v24[6] * *(float *)(v26 - 12) + v24[4] * *(float *)(v26 - 20) + *v24;
                      *v3 = igi2_frame.v103;
                      v28 = v27 + v24[1];
                      v3[1] = v28;
                      v29 = igi2_frame.v184 + v24[2];
                      v30 = v3;
                      v31 = v3 + 3;
                      *(v31 - 1) = v29;
                      igi2_frame.v137 = v29 * *(float *)&ptQTask[3].tQTaskChildren.ptMiddle
                           + v28 * *(float *)&ptQTask[3].tQTaskChildren.ptHead
                           + igi2_frame.v103 * *(float *)&ptQTask[3].ptPrev;
                      *v30 = igi2_frame.v137;
                      igi2_frame.v142 = v28 * *(float *)&ptQTask[3].tQTaskRefList.ptHead
                           + v29 * *(float *)&ptQTask[3].tQTaskRefList.ptMiddle
                           + igi2_frame.v103 * *(float *)&ptQTask[3].tQTaskChildren.ptTail;
                      v30[1] = igi2_frame.v142;
                      igi2_frame.v147 = v28 * *(float *)&ptQTask[3].ptParent
                           + v29 * *(float *)&ptQTask[3].eQTaskType
                           + igi2_frame.v103 * *(float *)&ptQTask[3].tQTaskRefList.ptTail;
                      v30[2] = igi2_frame.v147;
                      igi2_frame.v209[igi2_frame.v112] = *(_DWORD *)(v26 - 8);
                      igi2_frame.v122 = *(_DWORD *)(v26 + 12);
                      v32 = *(_DWORD *)&ptQTask[7].eQTaskType;
                      v33 = *(float *)(v32 + 80 * igi2_frame.v122 + 20);
                      v34 = (float *)(80 * igi2_frame.v122 + v32);
                      v35 = v33 * *(float *)(v26 + 4);
                      v26 += 20;
                      v36 = v34[8] * *(float *)(v26 - 16)
                          + v34[9] * *(float *)(v26 - 12)
                          + v34[7] * *(float *)(v26 - 20);
                      igi2_frame.v185 = v34[11] * *(float *)(v26 - 16)
                           + v34[12] * *(float *)(v26 - 12)
                           + v34[10] * *(float *)(v26 - 20);
                      igi2_frame.v104 = v35 + v34[6] * *(float *)(v26 - 12) + v34[4] * *(float *)(v26 - 20) + *v34;
                      *v31 = igi2_frame.v104;
                      v37 = v36 + v34[1];
                      v31[1] = v37;
                      v38 = igi2_frame.v185 + v34[2];
                      v39 = v31;
                      v31 += 3;
                      *(v31 - 1) = v38;
                      igi2_frame.v138 = v38 * *(float *)&ptQTask[3].tQTaskChildren.ptMiddle
                           + v37 * *(float *)&ptQTask[3].tQTaskChildren.ptHead
                           + igi2_frame.v104 * *(float *)&ptQTask[3].ptPrev;
                      *v39 = igi2_frame.v138;
                      igi2_frame.v143 = v37 * *(float *)&ptQTask[3].tQTaskRefList.ptHead
                           + v38 * *(float *)&ptQTask[3].tQTaskRefList.ptMiddle
                           + igi2_frame.v104 * *(float *)&ptQTask[3].tQTaskChildren.ptTail;
                      v39[1] = igi2_frame.v143;
                      igi2_frame.v148 = v37 * *(float *)&ptQTask[3].ptParent
                           + v38 * *(float *)&ptQTask[3].eQTaskType
                           + igi2_frame.v104 * *(float *)&ptQTask[3].tQTaskRefList.ptTail;
                      v39[2] = igi2_frame.v148;
                      igi2_frame.v209[igi2_frame.v112 + 1] = igi2_frame.v122;
                      igi2_frame.v123 = *(_DWORD *)(v26 + 12);
                      v40 = *(_DWORD *)&ptQTask[7].eQTaskType;
                      v41 = *(float *)(v40 + 80 * igi2_frame.v123 + 20);
                      v42 = (float *)(80 * igi2_frame.v123 + v40);
                      v43 = v41 * *(float *)(v26 + 4);
                      v26 += 20;
                      v44 = v42[8] * *(float *)(v26 - 16)
                          + v42[9] * *(float *)(v26 - 12)
                          + v42[7] * *(float *)(v26 - 20);
                      igi2_frame.v186 = v42[11] * *(float *)(v26 - 16)
                           + v42[12] * *(float *)(v26 - 12)
                           + v42[10] * *(float *)(v26 - 20);
                      igi2_frame.v105 = v43 + v42[6] * *(float *)(v26 - 12) + v42[4] * *(float *)(v26 - 20) + *v42;
                      *v31 = igi2_frame.v105;
                      v45 = v44 + v42[1];
                      v31[1] = v45;
                      v46 = igi2_frame.v186 + v42[2];
                      v47 = v31;
                      v31 += 3;
                      *(v31 - 1) = v46;
                      igi2_frame.v139 = v46 * *(float *)&ptQTask[3].tQTaskChildren.ptMiddle
                           + v45 * *(float *)&ptQTask[3].tQTaskChildren.ptHead
                           + igi2_frame.v105 * *(float *)&ptQTask[3].ptPrev;
                      *v47 = igi2_frame.v139;
                      igi2_frame.v144 = v45 * *(float *)&ptQTask[3].tQTaskRefList.ptHead
                           + v46 * *(float *)&ptQTask[3].tQTaskRefList.ptMiddle
                           + igi2_frame.v105 * *(float *)&ptQTask[3].tQTaskChildren.ptTail;
                      v47[1] = igi2_frame.v144;
                      igi2_frame.v149 = v45 * *(float *)&ptQTask[3].ptParent
                           + v46 * *(float *)&ptQTask[3].eQTaskType
                           + igi2_frame.v105 * *(float *)&ptQTask[3].tQTaskRefList.ptTail;
                      v47[2] = igi2_frame.v149;
                      igi2_frame.v209[igi2_frame.v112 + 2] = igi2_frame.v123;
                      igi2_frame.v124 = *(_DWORD *)(v26 + 12);
                      v48 = *(_DWORD *)&ptQTask[7].eQTaskType;
                      v49 = *(float *)(v48 + 80 * igi2_frame.v124 + 20);
                      v50 = (float *)(80 * igi2_frame.v124 + v48);
                      v51 = v49 * *(float *)(v26 + 4);
                      v9 = v26 + 20;
                      v52 = v50[8] * *(float *)(v9 - 16) + v50[9] * *(float *)(v9 - 12) + v50[7] * *(float *)(v9 - 20);
                      igi2_frame.v187 = v50[11] * *(float *)(v9 - 16)
                           + v50[12] * *(float *)(v9 - 12)
                           + v50[10] * *(float *)(v9 - 20);
                      igi2_frame.v106 = v51 + v50[6] * *(float *)(v9 - 12) + v50[4] * *(float *)(v9 - 20) + *v50;
                      *v31 = igi2_frame.v106;
                      v53 = v52 + v50[1];
                      v31[1] = v53;
                      v54 = igi2_frame.v187 + v50[2];
                      v55 = v31;
                      v3 = v31 + 3;
                      *(v3 - 1) = v54;
                      igi2_frame.v140 = v54 * *(float *)&ptQTask[3].tQTaskChildren.ptMiddle
                           + v53 * *(float *)&ptQTask[3].tQTaskChildren.ptHead
                           + igi2_frame.v106 * *(float *)&ptQTask[3].ptPrev;
                      *v55 = igi2_frame.v140;
                      igi2_frame.v145 = v53 * *(float *)&ptQTask[3].tQTaskRefList.ptHead
                           + v54 * *(float *)&ptQTask[3].tQTaskRefList.ptMiddle
                           + igi2_frame.v106 * *(float *)&ptQTask[3].tQTaskChildren.ptTail;
                      v55[1] = igi2_frame.v145;
                      igi2_frame.v150 = v53 * *(float *)&ptQTask[3].ptParent
                           + v54 * *(float *)&ptQTask[3].eQTaskType
                           + igi2_frame.v106 * *(float *)&ptQTask[3].tQTaskRefList.ptTail;
                      v55[2] = igi2_frame.v150;
                      igi2_frame.v209[igi2_frame.v112 + 3] = igi2_frame.v124;
                      v20 = igi2_frame.v180;
                      igi2_frame.v112 += 4;
                    }
                  }
                  if ( igi2_frame.v112 < v20 )
                  {
                    do
                    {
                      v56 = *(_DWORD *)&ptQTask[7].eQTaskType;
                      v57 = 80 * *(_DWORD *)(v9 + 12);
                      v58 = *(float *)(v56 + v57 + 24);
                      v59 = (float *)(v57 + v56);
                      v60 = v58 * *(float *)(v9 + 8);
                      v9 += 20;
                      v61 = v59[9] * *(float *)(v9 - 12) + v59[8] * *(float *)(v9 - 16) + v59[7] * *(float *)(v9 - 20);
                      igi2_frame.v188 = v59[12] * *(float *)(v9 - 12)
                           + v59[11] * *(float *)(v9 - 16)
                           + v59[10] * *(float *)(v9 - 20);
                      igi2_frame.v118 = v60 + v59[5] * *(float *)(v9 - 16) + v59[4] * *(float *)(v9 - 20) + *v59;
                      *v3 = igi2_frame.v118;
                      v62 = v61 + v59[1];
                      v3[1] = v62;
                      v63 = igi2_frame.v188 + v59[2];
                      v64 = v3;
                      v3 += 3;
                      *(v3 - 1) = v63;
                      igi2_frame.v141 = v62 * *(float *)&ptQTask[3].tQTaskChildren.ptHead
                           + igi2_frame.v118 * *(float *)&ptQTask[3].ptPrev
                           + v63 * *(float *)&ptQTask[3].tQTaskChildren.ptMiddle;
                      *v64 = igi2_frame.v141;
                      igi2_frame.v146 = v62 * *(float *)&ptQTask[3].tQTaskRefList.ptHead
                           + v63 * *(float *)&ptQTask[3].tQTaskRefList.ptMiddle
                           + igi2_frame.v118 * *(float *)&ptQTask[3].tQTaskChildren.ptTail;
                      v64[1] = igi2_frame.v146;
                      igi2_frame.v151 = v62 * *(float *)&ptQTask[3].ptParent
                           + v63 * *(float *)&ptQTask[3].eQTaskType
                           + igi2_frame.v118 * *(float *)&ptQTask[3].tQTaskRefList.ptTail;
                      v64[2] = igi2_frame.v151;
                      igi2_frame.v209[igi2_frame.v112++] = *(_DWORD *)(v9 - 8);
                    }
                    while ( igi2_frame.v112 < igi2_frame.v180 );
                  }
                  igi2_frame.v192 = 1;
                }
                igi2_frame.v176 = 0;
                igi2_frame.v119 = (unsigned __int16 *)igi2_frame.v158[4];
                if ( *igi2_frame.v158 > 0 )
                  break;
LABEL_155:
                ++igi2_frame.ptStartPos;
                igi2_frame.v111 = v18 + 120;
                ++igi2_frame.ptEndPos;
                if ( ++igi2_frame.v193 >= (int)(*((_DWORD *)pxContext + 2)) )
                  return;
              }
              while ( 1 )
              {
                igi2_frame.v107 = (float *)&igi2_frame.v210[3 * igi2_frame.v119[1]];
                v65 = (float *)&igi2_frame.v210[3 * *igi2_frame.v119];
                igi2_frame.v113 = (float *)&igi2_frame.v210[3 * igi2_frame.v119[2]];
                igi2_frame.v169 = *v65;
                if ( igi2_frame.v197 > igi2_frame.v169 && *igi2_frame.v107 < igi2_frame.v197 && *igi2_frame.v113 < igi2_frame.v197 )
                  goto LABEL_140;
                igi2_frame.v134 = v65[1];
                if ( igi2_frame.v198 > igi2_frame.v134 && igi2_frame.v107[1] < igi2_frame.v198 && igi2_frame.v113[1] < igi2_frame.v198 )
                  goto LABEL_140;
                igi2_frame.v159 = v65[2];
                if ( igi2_frame.v199 > igi2_frame.v159 && igi2_frame.v107[2] < igi2_frame.v199 && igi2_frame.v113[2] < igi2_frame.v199 )
                  goto LABEL_140;
                if ( igi2_frame.v194 < igi2_frame.v169 && *igi2_frame.v107 > igi2_frame.v194 && *igi2_frame.v113 > igi2_frame.v194 )
                  goto LABEL_140;
                if ( igi2_frame.v195 < igi2_frame.v134 && igi2_frame.v107[1] > igi2_frame.v195 && igi2_frame.v113[1] > igi2_frame.v195 )
                  goto LABEL_140;
                if ( igi2_frame.v196 < igi2_frame.v159 && igi2_frame.v107[2] > igi2_frame.v196 && igi2_frame.v113[2] > igi2_frame.v196 )
                  goto LABEL_140;
                igi2_frame.v127 = *igi2_frame.v113 - *v65;
                igi2_frame.v128 = igi2_frame.v113[1] - v65[1];
                igi2_frame.v129 = igi2_frame.v113[2] - v65[2];
                igi2_frame.v172 = *igi2_frame.v107 - *v65;
                igi2_frame.v173 = igi2_frame.v107[1] - v65[1];
                v66 = igi2_frame.v107[2] - v65[2];
                igi2_frame.v174 = v66;
                igi2_frame.v160 = v66 * igi2_frame.v128 - igi2_frame.v173 * igi2_frame.v129;
                v67 = igi2_frame.v174 * igi2_frame.v127 - igi2_frame.v172 * igi2_frame.v129;
                igi2_frame.v125 = v67;
                igi2_frame.v166 = -v67;
                igi2_frame.v108 = igi2_frame.v173 * igi2_frame.v127 - igi2_frame.v172 * igi2_frame.v128;
                igi2_frame.v170 = igi2_frame.v108 * igi2_frame.v191 + igi2_frame.v166 * igi2_frame.v190 + igi2_frame.v160 * igi2_frame.v189;
                if ( igi2_frame.v170 == 0.0 )
                  goto LABEL_140;
                v68 = ((v65[1] - igi2_frame.v131) * igi2_frame.v166 + (*v65 - igi2_frame.v130) * igi2_frame.v160 + (v65[2] - igi2_frame.v132) * igi2_frame.v108) / igi2_frame.v170;
                igi2_frame.v114 = v68;
                if ( v68 < 0.0 || igi2_frame.v114 > 1.0 )
                  goto LABEL_140;
                igi2_frame.v152 = igi2_frame.v114 * igi2_frame.v189 + igi2_frame.v130;
                igi2_frame.v153 = igi2_frame.v114 * igi2_frame.v190 + igi2_frame.v131;
                igi2_frame.v154 = igi2_frame.v114 * igi2_frame.v191 + igi2_frame.v132;
                if ( igi2_frame.v160 >= 0.0 )
                  igi2_frame.v208 = igi2_frame.v160;
                else
                  igi2_frame.v208 = -igi2_frame.v160;
                v69 = igi2_frame.v166;
                if ( igi2_frame.v166 < 0.0 )
                  v69 = -v69;
                v70 = igi2_frame.v108;
                if ( igi2_frame.v108 < 0.0 )
                  v70 = -v70;
                if ( igi2_frame.v208 > v69 && igi2_frame.v208 > v70 )
                  break;
                if ( v69 > v70 )
                {
                  v75 = igi2_frame.v125;
                  if ( igi2_frame.v125 == 0.0 )
                    goto LABEL_140;
                  igi2_frame.v126 = igi2_frame.v154 - v65[2];
                  igi2_frame.v109 = igi2_frame.v152 - *v65;
                  igi2_frame.v135 = (igi2_frame.v127 * igi2_frame.v126 - igi2_frame.v129 * igi2_frame.v109) / v75;
                  if ( igi2_frame.v135 < 0.0 || igi2_frame.v135 > 1.0 )
                    goto LABEL_140;
                  v76 = igi2_frame.v127;
                  if ( igi2_frame.v127 < 0.0 )
                    v76 = -v76;
                  v77 = igi2_frame.v129;
                  if ( igi2_frame.v129 < 0.0 )
                    v77 = -v77;
                  if ( v76 > v77 )
                  {
                    v74 = (igi2_frame.v109 - igi2_frame.v172 * igi2_frame.v135) / igi2_frame.v127;
                    goto LABEL_92;
                  }
LABEL_90:
                  if ( igi2_frame.v129 == 0.0 )
                    goto LABEL_140;
                  v74 = (igi2_frame.v126 - igi2_frame.v174 * igi2_frame.v135) / igi2_frame.v129;
                  goto LABEL_92;
                }
                v78 = igi2_frame.v108;
                if ( igi2_frame.v108 == 0.0 )
                  goto LABEL_140;
                igi2_frame.v162 = igi2_frame.v153 - v65[1];
                igi2_frame.v110 = igi2_frame.v152 - *v65;
                igi2_frame.v136 = (igi2_frame.v127 * igi2_frame.v162 - igi2_frame.v128 * igi2_frame.v110) / v78;
                if ( igi2_frame.v136 < 0.0 || igi2_frame.v136 > 1.0 )
                  goto LABEL_140;
                v79 = igi2_frame.v127;
                if ( igi2_frame.v127 < 0.0 )
                  v79 = -v79;
                v80 = igi2_frame.v128;
                if ( igi2_frame.v128 < 0.0 )
                  v80 = -v80;
                if ( v79 <= v80 )
                {
                  if ( igi2_frame.v128 == 0.0 )
                    goto LABEL_140;
                  v81 = (igi2_frame.v162 - igi2_frame.v173 * igi2_frame.v136) / igi2_frame.v128;
                }
                else
                {
                  v81 = (igi2_frame.v110 - igi2_frame.v172 * igi2_frame.v136) / igi2_frame.v127;
                }
                if ( v81 < 0.0 || igi2_frame.v136 + v81 > 1.0 )
                  goto LABEL_140;
LABEL_108:
                v82 = igi2_frame.v114 * igi2_frame.v181;
                if ( !igi2_frame.v121 )
                {
                  igi2_frame.v116 = 0;
LABEL_121:
                  igi2_frame.v183 = v82;
                  igi2_frame.v163 = igi2_frame.v114 * igi2_frame.v189 + igi2_frame.v130;
                  igi2_frame.v115 = igi2_frame.v170 < 0.0;
                  igi2_frame.v165 = igi2_frame.v114 * igi2_frame.v191 + igi2_frame.v132;
                  igi2_frame.v179 = igi2_frame.v119;
                  igi2_frame.v133 = 1;
                  igi2_frame.v121 = 1;
                  igi2_frame.v164 = igi2_frame.v114 * igi2_frame.v190 + igi2_frame.v131;
                  if ( igi2_frame.v130 >= (double)igi2_frame.v152 )
                    v84 = igi2_frame.v152;
                  else
                    v84 = igi2_frame.v130;
                  igi2_frame.v197 = v84 - 40.959999084472656;
                  if ( igi2_frame.v131 >= (double)igi2_frame.v153 )
                    v85 = igi2_frame.v153;
                  else
                    v85 = igi2_frame.v131;
                  igi2_frame.v198 = v85 - 40.959999084472656;
                  if ( igi2_frame.v132 >= (double)igi2_frame.v154 )
                    v86 = igi2_frame.v154;
                  else
                    v86 = igi2_frame.v132;
                  igi2_frame.v199 = v86 - 40.959999084472656;
                  if ( igi2_frame.v130 <= (double)igi2_frame.v152 )
                    v87 = igi2_frame.v152;
                  else
                    v87 = igi2_frame.v130;
                  igi2_frame.v194 = v87 + 40.959999084472656;
                  if ( igi2_frame.v131 <= (double)igi2_frame.v153 )
                    v88 = igi2_frame.v153;
                  else
                    v88 = igi2_frame.v131;
                  igi2_frame.v195 = v88 + 40.959999084472656;
                  if ( igi2_frame.v132 <= (double)igi2_frame.v154 )
                    v89 = igi2_frame.v154 + 40.959999084472656;
                  else
                    v89 = igi2_frame.v132 + 40.959999084472656;
                  igi2_frame.v196 = v89;
                  goto LABEL_140;
                }
                if ( v82 + 40.96 < igi2_frame.v183 )
                {
                  igi2_frame.v116 = 0;
                  goto LABEL_121;
                }
                if ( v82 >= igi2_frame.v183 )
                {
                  if ( v82 - 40.96 >= igi2_frame.v183 )
                    goto LABEL_140;
                  if ( igi2_frame.v170 < 0.0 )
                  {
                    v83 = 1;
                    if ( !igi2_frame.v115 )
                      goto LABEL_120;
                  }
                }
                else if ( igi2_frame.v170 < 0.0 || !igi2_frame.v115 )
                {
                  v83 = 1;
                  goto LABEL_120;
                }
                v83 = 0;
LABEL_120:
                igi2_frame.v116 = 1;
                if ( v83 )
                  goto LABEL_121;
LABEL_140:
                igi2_frame.v119 += 6;
                if ( ++igi2_frame.v176 >= *igi2_frame.v158 )
                {
                  if ( igi2_frame.v133 && (!*(_DWORD *)(v18 + 92) || igi2_frame.v183 < *(double *)(v18 + 96)) )
                  {
                    igi2_frame.v182 = (float *)&igi2_frame.v210[3 * *igi2_frame.v179];
                    igi2_frame.v177 = (float *)&igi2_frame.v210[3 * igi2_frame.v179[1]];
                    igi2_frame.v167 = (float *)&igi2_frame.v210[3 * igi2_frame.v179[2]];
                    v90 = *(_WORD *)(igi2_frame.v158[6] + 16 * igi2_frame.v179[3] + 12);
                    if ( v90 == 0xFFFF )
                      igi2_frame.v120 = World_ptActiveWorld->aptQMaterial[1];
                    else
                      igi2_frame.v120 = World_ptActiveWorld->aptQMaterial[v90];
                    v91 = *igi2_frame.v167 - *igi2_frame.v182;
                    v92 = igi2_frame.v167[1] - igi2_frame.v182[1];
                    v93 = igi2_frame.v167[2] - igi2_frame.v182[2];
                    igi2_frame.v200 = *igi2_frame.v177 - *igi2_frame.v182;
                    igi2_frame.v201 = igi2_frame.v177[1] - igi2_frame.v182[1];
                    v94 = igi2_frame.v177[2] - igi2_frame.v182[2];
                    igi2_frame.v205 = v94 * v92 - igi2_frame.v201 * v93;
                    *(float *)(v18 + 56) = igi2_frame.v205;
                    igi2_frame.v206 = -(v94 * v91 - igi2_frame.v200 * v93);
                    *(float *)(v18 + 60) = igi2_frame.v206;
                    igi2_frame.v207 = igi2_frame.v201 * v91 - igi2_frame.v200 * v92;
                    *(float *)(v18 + 64) = igi2_frame.v207;
                    if ( *(float *)(v18 + 56) != 0.0 || *(float *)(v18 + 60) != 0.0 || *(float *)(v18 + 64) != 0.0 )
                    {
                      v95 = *(float *)(v18 + 64);
                      v96 = *(float *)(v18 + 60);
                      igi2_frame.v168 = sqrt(*(float *)(v18 + 56) * *(float *)(v18 + 56) + v96 * v96 + v95 * v95);
                      igi2_frame.v171 = 1.0 / igi2_frame.v168;
                      *(float *)(v18 + 56) = igi2_frame.v171 * *(float *)(v18 + 56);
                      *(float *)(v18 + 60) = igi2_frame.v171 * v96;
                      *(float *)(v18 + 64) = igi2_frame.v171 * v95;
                    }
                    *(double *)(v18 + 8) = igi2_frame.v163 + *(double *)&ptQTask[1].ptNext;
                    *(double *)(v18 + 16) = igi2_frame.v164 + *(double *)&ptQTask[1].tQTaskChildren.ptHead;
                    v97 = igi2_frame.v165 + *(double *)&ptQTask[1].tQTaskChildren.ptTail;
                    *(float *)(v18 + 32) = igi2_frame.v163;
                    *(float *)(v18 + 36) = igi2_frame.v164;
                    *(double *)(v18 + 24) = v97;
                    *(float *)(v18 + 40) = igi2_frame.v165;
                    igi2_frame.v202 = *(float *)&ptQTask[3].tQTaskRefList.ptTail * *(float *)(v18 + 64)
                         + *(float *)&ptQTask[3].tQTaskChildren.ptTail * *(float *)(v18 + 60)
                         + *(float *)&ptQTask[3].ptPrev * *(float *)(v18 + 56);
                    igi2_frame.v203 = *(float *)&ptQTask[3].ptParent * *(float *)(v18 + 64)
                         + *(float *)&ptQTask[3].tQTaskRefList.ptHead * *(float *)(v18 + 60)
                         + *(float *)&ptQTask[3].tQTaskChildren.ptHead * *(float *)(v18 + 56);
                    v98 = *(float *)&ptQTask[3].eQTaskType * *(float *)(v18 + 64)
                        + *(float *)&ptQTask[3].tQTaskRefList.ptMiddle * *(float *)(v18 + 60);
                    v99 = *(float *)&ptQTask[3].tQTaskChildren.ptMiddle;
                    *(float *)(v18 + 44) = igi2_frame.v202;
                    v100 = v99 * *(float *)(v18 + 56);
                    *(float *)(v18 + 48) = igi2_frame.v203;
                    *(_DWORD *)v18 = ptQTask;
                    *(_DWORD *)(v18 + 92) = 1;
                    igi2_frame.v204 = v98 + v100;
                    *(float *)(v18 + 52) = igi2_frame.v204;
                    *(_DWORD *)(v18 + 80) = igi2_frame.v115 ? igi2_frame.v120 : nullptr;
                    *(_DWORD *)(v18 + 88) = igi2_frame.v116;
                    *(_DWORD *)(v18 + 84) = igi2_frame.v115 ? nullptr : igi2_frame.v120;
                    *(double *)(v18 + 96) = igi2_frame.v183;
                    *(_DWORD *)(v18 + 72) = ((int)igi2_frame.v179 - igi2_frame.v158[4]) / 12;
                    *(_DWORD *)(v18 + 112) = 1065353216;
                    v101 = igi2_frame.v209[*igi2_frame.v179];
                    *(_DWORD *)(v18 + 68) = v101;
                    v102 = igi2_frame.v209[igi2_frame.v179[1]];
                    if ( v102 != v101 && v102 == igi2_frame.v209[igi2_frame.v179[2]] )
                      *(_DWORD *)(v18 + 68) = v102;
                  }
                  goto LABEL_155;
                }
              }
              v71 = igi2_frame.v160;
              if ( igi2_frame.v160 == 0.0 )
                goto LABEL_140;
              igi2_frame.v126 = igi2_frame.v154 - v65[2];
              igi2_frame.v161 = igi2_frame.v153 - v65[1];
              igi2_frame.v135 = (igi2_frame.v128 * igi2_frame.v126 - igi2_frame.v129 * igi2_frame.v161) / v71;
              if ( igi2_frame.v135 < 0.0 || igi2_frame.v135 > 1.0 )
                goto LABEL_140;
              v72 = igi2_frame.v128;
              if ( igi2_frame.v128 < 0.0 )
                v72 = -v72;
              v73 = igi2_frame.v129;
              if ( igi2_frame.v129 < 0.0 )
                v73 = -v73;
              if ( v72 > v73 )
              {
                v74 = (igi2_frame.v161 - igi2_frame.v173 * igi2_frame.v135) / igi2_frame.v128;
LABEL_92:
                if ( v74 < 0.0 || igi2_frame.v135 + v74 > 1.0 )
                  goto LABEL_140;
                goto LABEL_108;
              }
              goto LABEL_90;
            }
          }
        }
      }
    }
  }
}

// source: e/3/bonedyncubeobj.c:1088  [anchor-mhash]
void __cdecl BoneDynCubeObj_LineOfSightHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct real64x3_t *ptEndPos; };
    struct { float ptEndPosa; };
    struct { float ptEndPosb; };
    struct { char igi2_o3[4]; struct real64x3_t *ptStartPos; };
    struct { char igi2_o4[4]; int ptStartPosa; };
    struct { char igi2_o5[4]; float ptStartPosb; };
    struct { char igi2_o6[4]; float ptStartPosc; };
    struct { char igi2_o7[4]; float ptStartPosd; };
    struct { char igi2_o8[8]; int nVertexPos; };
    struct { char igi2_o9[8]; int nVertexPosa; };
    struct { char igi2_o10[8]; int nVertexPosb; };
    struct { char igi2_o11[8]; int nVertexPosc; };
    struct { char igi2_o12[12]; float tEdge0; };
    struct { char igi2_o13[16]; float tEdge0_4; };
    struct { char igi2_o14[20]; float tEdge0_8; };
    struct { char igi2_o15[24]; float tEndPos; };
    struct { char igi2_o16[28]; float tEndPos_4; };
    struct { char igi2_o17[28]; float tEndPos_4a; };
    struct { char igi2_o18[32]; float tEndPos_8; };
    struct { char igi2_o19[36]; float Real32x3_Rotate_tTemp; };
    struct { char igi2_o20[40]; float Real32x3_Rotate_tTemp_4; };
    struct { char igi2_o21[44]; float Real32x3_Rotate_tTemp_8; };
    struct { char igi2_o22[44]; float Real32x3_Rotate_tTemp_8a; };
    struct { char igi2_o23[44]; float Real32x3_Rotate_tTemp_8b; };
    struct { char igi2_o24[44]; float Real32x3_Rotate_tTemp_8c; };
    struct { char igi2_o25[44]; float Real32x3_Rotate_tTemp_8d; };
    struct { char igi2_o26[44]; float Real32x3_Rotate_tTemp_8e; };
    struct { char igi2_o27[48]; float tStartPos; };
    struct { char igi2_o28[52]; float tStartPos_4; };
    struct { char igi2_o29[56]; float tStartPos_8; };
    struct { char igi2_o30[60]; struct MultiMesh_Mesh_t *ptCollMesh; };
    struct { char igi2_o31[64]; float tDelta; };
    struct { char igi2_o32[68]; float tDelta_4; };
    struct { char igi2_o33[72]; float tDelta_8; };
    struct { char igi2_o34[76]; float tPos; };
    struct { char igi2_o35[80]; float tPos_4; };
    struct { char igi2_o36[84]; float tPos_8; };
    struct { char igi2_o37[88]; float v111; };
    struct { char igi2_o38[88]; double vY; };
    struct { char igi2_o39[100]; int iFace; };
    struct { char igi2_o40[104]; float v114; };
    struct { char igi2_o41[104]; double vX; };
    struct { char igi2_o42[116]; float tAbsNormal; };
    struct { char igi2_o43[128]; double tMin; };
    struct { char igi2_o44[136]; double tMin_8; };
    struct { char igi2_o45[152]; unsigned int anBone[4096]; };
    struct { char igi2_o46[16536]; struct real32x3_t atVertexList[4096]; };
    char igi2_extent[65688];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v2; // eax
  struct real32x3_t *v3; // edi
  int v4; // eax
  struct MultiMesh_Vertex_t *ptVertex; // esi
  __int16 v6; // ax
  void (__cdecl *pfHandler)(struct QTask_s *, _DWORD); // eax
  double v8; // st7
  double v9; // st7
  double v10; // st7
  double v11; // st7
  double v12; // st6
  double v13; // st6
  double v14; // st5
  double v15; // st5
  double v16; // st4
  double v17; // st4
  int v18; // ecx
  int v19; // edx
  unsigned int iBone; // ebx
  float *v21; // eax
  double v22; // st3
  unsigned int v23; // ebx
  double v24; // st2
  double v25; // st3
  double v26; // st2
  double v27; // st3
  float *v28; // eax
  unsigned int v29; // ebx
  double v30; // st2
  double v31; // st3
  float *v32; // eax
  double v33; // st3
  unsigned int v34; // ebx
  double v35; // st2
  double v36; // st3
  double v37; // st2
  double v38; // st3
  float *v39; // eax
  double v40; // rtt
  bool v41; // cc
  int v42; // ebx
  unsigned int v43; // edx
  float *v44; // eax
  double v45; // st3
  double v46; // st2
  double v47; // rt0
  unsigned __int16 *aiVertex; // edx
  struct real32x3_t *v49; // ecx
  struct real32x3_t *v50; // esi
  struct real32x3_t *v51; // edi
  double vZ; // st3
  double v53; // st3
  double v54; // st3
  double v55; // st3
  double v56; // st3
  double v57; // st3
  double v58; // st2
  double v59; // st3
  double v60; // st3
  double v61; // st2
  double v62; // st1
  double v63; // st2
  double v64; // st3
  double v65; // st2
  double v66; // st1
  double v67; // st3
  double v68; // st2
  double v69; // st1
  double v70; // st2
  int iMaterial; // eax
  float *v72; // ecx

  v2 = *(_DWORD *)&ptQTask[2].eQTaskType;
  igi2_frame.ptStartPos = *(struct real64x3_t **)pxContext;
  igi2_frame.ptEndPos = *((struct real64x3_t **)pxContext + 1);
  v3 = igi2_frame.atVertexList;
  if ( v2 )
  {
    v4 = *(_DWORD *)(*(_DWORD *)(*(_DWORD *)v2 + 12) + 12);
    if ( !*(_DWORD *)(v4 + 40) )
    {
      igi2_frame.ptCollMesh = *(struct MultiMesh_Mesh_t **)(v4 + 44);
      if ( igi2_frame.ptCollMesh )
      {
        BoneDynCubeObj_UpdateHierarchy((struct BoneDynCubeObj_s *)ptQTask);
        ptVertex = igi2_frame.ptCollMesh->ptVertex;
        v6 = *((_WORD *)pxContext + 4);
        igi2_frame.nVertexPos = igi2_frame.ptCollMesh->nNumVertices;
        if ( v6 == 512
          || (pfHandler = (void (__cdecl *)(struct QTask_s *, _DWORD))QTask_aatQTaskFinalEvent[v6][ptQTask->eQTaskType].pfHandler) == nullptr
          || (pfHandler(ptQTask, *((_DWORD *)pxContext + 3)), **((_BYTE **)pxContext + 3)) )
        {
          if ( BoneDynCubeObj_SphereIntersectionCheck((struct BoneDynCubeObj_s *)ptQTask, igi2_frame.ptStartPos, igi2_frame.ptEndPos) )
          {
            igi2_frame.tStartPos = igi2_frame.ptStartPos->vX - *(double *)&ptQTask[1].ptNext;
            igi2_frame.tStartPos_4 = igi2_frame.ptStartPos->vY - *(double *)&ptQTask[1].tQTaskChildren.ptHead;
            igi2_frame.tStartPos_8 = igi2_frame.ptStartPos->vZ - *(double *)&ptQTask[1].tQTaskChildren.ptTail;
            igi2_frame.tEndPos = igi2_frame.ptEndPos->vX - *(double *)&ptQTask[1].ptNext;
            igi2_frame.tEndPos_4 = igi2_frame.ptEndPos->vY - *(double *)&ptQTask[1].tQTaskChildren.ptHead;
            igi2_frame.tEndPos_8 = igi2_frame.ptEndPos->vZ - *(double *)&ptQTask[1].tQTaskChildren.ptTail;
            if ( igi2_frame.tStartPos >= (double)igi2_frame.tEndPos )
              v8 = igi2_frame.tEndPos;
            else
              v8 = igi2_frame.tStartPos;
            igi2_frame.tMin = v8 - 40.959999084472656;
            if ( igi2_frame.tStartPos_4 >= (double)igi2_frame.tEndPos_4 )
              v9 = igi2_frame.tEndPos_4;
            else
              v9 = igi2_frame.tStartPos_4;
            igi2_frame.tMin_8 = v9 - 40.959999084472656;
            if ( igi2_frame.tStartPos_8 >= (double)igi2_frame.tEndPos_8 )
              v10 = igi2_frame.tEndPos_8;
            else
              v10 = igi2_frame.tStartPos_8;
            v11 = v10 - 40.959999084472656;
            if ( igi2_frame.tStartPos <= (double)igi2_frame.tEndPos )
              v12 = igi2_frame.tEndPos;
            else
              v12 = igi2_frame.tStartPos;
            v13 = v12 + 40.959999084472656;
            if ( igi2_frame.tStartPos_4 <= (double)igi2_frame.tEndPos_4 )
              v14 = igi2_frame.tEndPos_4;
            else
              v14 = igi2_frame.tStartPos_4;
            v15 = v14 + 40.959999084472656;
            if ( igi2_frame.tStartPos_8 <= (double)igi2_frame.tEndPos_8 )
              v16 = igi2_frame.tEndPos_8;
            else
              v16 = igi2_frame.tStartPos_8;
            v17 = v16 + 40.959999084472656;
            igi2_frame.tDelta = igi2_frame.ptEndPos->vX - igi2_frame.ptStartPos->vX;
            igi2_frame.tDelta_4 = igi2_frame.ptEndPos->vY - igi2_frame.ptStartPos->vY;
            v18 = 0;
            igi2_frame.tDelta_8 = igi2_frame.ptEndPos->vZ - igi2_frame.ptStartPos->vZ;
            if ( igi2_frame.nVertexPos >= 4 )
            {
              v19 = *(_DWORD *)&ptQTask[7].eQTaskType;
              igi2_frame.ptStartPosa = 3;
              do
              {
                iBone = ptVertex->u.iBone;
                v21 = (float *)(v19 + 80 * iBone);
                v22 = v21[6] * ptVertex->tPos.vZ;
                igi2_frame.anBone[v18] = iBone;
                v23 = ptVertex[1].u.iBone;
                v24 = v21[5] * ptVertex->tPos.vY;
                igi2_frame.anBone[v18 + 1] = v23;
                v25 = v22 + v24 + v21[4] * ptVertex->tPos.vX;
                v26 = v21[9] * ptVertex->tPos.vZ + v21[8] * ptVertex->tPos.vY + v21[7] * ptVertex->tPos.vX;
                igi2_frame.Real32x3_Rotate_tTemp_8a = v21[12] * ptVertex->tPos.vZ
                                         + v21[11] * ptVertex->tPos.vY
                                         + v21[10] * ptVertex->tPos.vX;
                v3->vX = v25 + *v21;
                v3->vY = v26 + v21[1];
                v27 = igi2_frame.Real32x3_Rotate_tTemp_8a + v21[2];
                v28 = (float *)(v19 + 80 * v23);
                v3->vZ = v27;
                v29 = ptVertex[2].u.iBone;
                v30 = v28[9] * ptVertex[1].tPos.vZ + v28[8] * ptVertex[1].tPos.vY + v28[7] * ptVertex[1].tPos.vX;
                igi2_frame.Real32x3_Rotate_tTemp_8b = v28[12] * ptVertex[1].tPos.vZ
                                         + v28[11] * ptVertex[1].tPos.vY
                                         + v28[10] * ptVertex[1].tPos.vX;
                v3[1].vX = v28[6] * ptVertex[1].tPos.vZ
                         + v28[5] * ptVertex[1].tPos.vY
                         + v28[4] * ptVertex[1].tPos.vX
                         + *v28;
                v3[1].vY = v30 + v28[1];
                v31 = igi2_frame.Real32x3_Rotate_tTemp_8b + v28[2];
                v32 = (float *)(v19 + 80 * v29);
                v3[1].vZ = v31;
                v33 = v32[6] * ptVertex[2].tPos.vZ;
                igi2_frame.anBone[v18 + 2] = v29;
                v34 = ptVertex[3].u.iBone;
                v35 = v32[5] * ptVertex[2].tPos.vY;
                igi2_frame.anBone[v18 + 3] = v34;
                v18 += 4;
                v3 += 4;
                ptVertex += 4;
                v36 = v33 + v35 + v32[4] * ptVertex[-2].tPos.vX;
                v37 = v32[9] * ptVertex[-2].tPos.vZ + v32[8] * ptVertex[-2].tPos.vY + v32[7] * ptVertex[-2].tPos.vX;
                igi2_frame.Real32x3_Rotate_tTemp_8c = v32[12] * ptVertex[-2].tPos.vZ
                                         + v32[11] * ptVertex[-2].tPos.vY
                                         + v32[10] * ptVertex[-2].tPos.vX;
                v3[-2].vX = v36 + *v32;
                v3[-2].vY = v37 + v32[1];
                v38 = igi2_frame.Real32x3_Rotate_tTemp_8c + v32[2];
                v39 = (float *)(v19 + 80 * v34);
                v3[-2].vZ = v38;
                igi2_frame.Real32x3_Rotate_tTemp_8d = v39[11] * ptVertex[-1].tPos.vY
                                         + v39[10] * ptVertex[-1].tPos.vX
                                         + v39[12] * ptVertex[-1].tPos.vZ;
                v40 = v39[8] * ptVertex[-1].tPos.vY + v39[7] * ptVertex[-1].tPos.vX + v39[9] * ptVertex[-1].tPos.vZ;
                v3[-1].vX = v39[5] * ptVertex[-1].tPos.vY
                          + v39[4] * ptVertex[-1].tPos.vX
                          + v39[6] * ptVertex[-1].tPos.vZ
                          + *v39;
                v3[-1].vY = v40 + v39[1];
                v41 = igi2_frame.ptStartPosa + 4 < igi2_frame.nVertexPos;
                v3[-1].vZ = igi2_frame.Real32x3_Rotate_tTemp_8d + v39[2];
                igi2_frame.ptStartPosa += 4;
              }
              while ( v41 );
            }
            if ( v18 < igi2_frame.nVertexPos )
            {
              v42 = *(_DWORD *)&ptQTask[7].eQTaskType;
              do
              {
                v43 = ptVertex->u.iBone;
                v44 = (float *)(v42 + 80 * v43);
                v45 = v44[6] * ptVertex->tPos.vZ;
                ++ptVertex;
                ++v3;
                v46 = v44[5] * ptVertex[-1].tPos.vY;
                igi2_frame.anBone[v18++] = v43;
                igi2_frame.Real32x3_Rotate_tTemp_8e = v44[12] * ptVertex[-1].tPos.vZ
                                         + v44[11] * ptVertex[-1].tPos.vY
                                         + v44[10] * ptVertex[-1].tPos.vX;
                v47 = v44[9] * ptVertex[-1].tPos.vZ + v44[8] * ptVertex[-1].tPos.vY + v44[7] * ptVertex[-1].tPos.vX;
                v3[-1].vX = v45 + v46 + v44[4] * ptVertex[-1].tPos.vX + *v44;
                v3[-1].vY = v47 + v44[1];
                v3[-1].vZ = igi2_frame.Real32x3_Rotate_tTemp_8e + v44[2];
              }
              while ( v18 < igi2_frame.nVertexPos );
            }
            aiVertex = igi2_frame.ptCollMesh->ptFace->aiVertex;
            for ( igi2_frame.iFace = 0; igi2_frame.iFace < igi2_frame.ptCollMesh->nNumFaces; ++igi2_frame.iFace )
            {
              v49 = &igi2_frame.atVertexList[*aiVertex];
              igi2_frame.vX = v49->vX;
              v50 = &igi2_frame.atVertexList[aiVertex[1]];
              v51 = &igi2_frame.atVertexList[aiVertex[2]];
              if ( igi2_frame.tMin > igi2_frame.vX && v50->vX < igi2_frame.tMin && v51->vX < igi2_frame.tMin )
                goto LABEL_106;
              igi2_frame.vY = v49->vY;
              if ( igi2_frame.tMin_8 > igi2_frame.vY && v50->vY < igi2_frame.tMin_8 && v51->vY < igi2_frame.tMin_8 )
                goto LABEL_106;
              vZ = v49->vZ;
              if ( v11 > vZ && v11 > v50->vZ && v11 > v51->vZ )
                goto LABEL_106;
              if ( v13 < igi2_frame.vX && v13 < v50->vX && v13 < v51->vX )
                goto LABEL_106;
              if ( v15 < igi2_frame.vY && v15 < v50->vY && v15 < v51->vY )
                goto LABEL_106;
              if ( v17 < vZ && v17 < v50->vZ && v17 < v51->vZ )
                goto LABEL_106;
              igi2_frame.tEdge0 = v51->vX - v49->vX;
              igi2_frame.tEdge0_4 = v51->vY - v49->vY;
              igi2_frame.tEdge0_8 = v51->vZ - v49->vZ;
              igi2_frame.Real32x3_Rotate_tTemp = v50->vX - v49->vX;
              igi2_frame.Real32x3_Rotate_tTemp_4 = v50->vY - v49->vY;
              v53 = v50->vZ - v49->vZ;
              igi2_frame.Real32x3_Rotate_tTemp_8 = v53;
              *(float *)&igi2_frame.nVertexPosa = v53 * igi2_frame.tEdge0_4 - igi2_frame.Real32x3_Rotate_tTemp_4 * igi2_frame.tEdge0_8;
              v54 = igi2_frame.Real32x3_Rotate_tTemp_8 * igi2_frame.tEdge0 - igi2_frame.Real32x3_Rotate_tTemp * igi2_frame.tEdge0_8;
              igi2_frame.ptStartPosb = v54;
              igi2_frame.tEndPos_4a = -v54;
              igi2_frame.v111 = igi2_frame.Real32x3_Rotate_tTemp_4 * igi2_frame.tEdge0 - igi2_frame.Real32x3_Rotate_tTemp * igi2_frame.tEdge0_4;
              v55 = igi2_frame.v111 * igi2_frame.tDelta_8 + igi2_frame.tEndPos_4a * igi2_frame.tDelta_4 + *(float *)&igi2_frame.nVertexPosa * igi2_frame.tDelta;
              igi2_frame.v114 = v55;
              if ( v55 == 0.0 )
                goto LABEL_106;
              v56 = ((v49->vX - igi2_frame.tStartPos) * *(float *)&igi2_frame.nVertexPosa
                   + (v49->vY - igi2_frame.tStartPos_4) * igi2_frame.tEndPos_4a
                   + (v49->vZ - igi2_frame.tStartPos_8) * igi2_frame.v111)
                  / v55;
              igi2_frame.ptEndPosa = v56;
              if ( v56 < 0.0 || igi2_frame.ptEndPosa > 1.0 )
                goto LABEL_106;
              igi2_frame.tPos = igi2_frame.ptEndPosa * igi2_frame.tDelta + igi2_frame.tStartPos;
              igi2_frame.tPos_4 = igi2_frame.ptEndPosa * igi2_frame.tDelta_4 + igi2_frame.tStartPos_4;
              igi2_frame.tPos_8 = igi2_frame.ptEndPosa * igi2_frame.tDelta_8 + igi2_frame.tStartPos_8;
              if ( *(float *)&igi2_frame.nVertexPosa >= 0.0 )
                igi2_frame.tAbsNormal = *(float *)&igi2_frame.nVertexPosa;
              else
                igi2_frame.tAbsNormal = -*(float *)&igi2_frame.nVertexPosa;
              v57 = igi2_frame.tEndPos_4a;
              if ( igi2_frame.tEndPos_4a < 0.0 )
                v57 = -v57;
              v58 = igi2_frame.v111;
              if ( igi2_frame.v111 < 0.0 )
                v58 = -v58;
              if ( igi2_frame.tAbsNormal <= v57 || igi2_frame.tAbsNormal <= v58 )
              {
                if ( v57 <= v58 )
                {
                  if ( igi2_frame.v111 == 0.0 )
                    goto LABEL_106;
                  *(float *)&igi2_frame.nVertexPosc = igi2_frame.tPos_4 - v49->vY;
                  igi2_frame.ptStartPosd = igi2_frame.tPos - v49->vX;
                  v67 = (*(float *)&igi2_frame.nVertexPosc * igi2_frame.tEdge0 - igi2_frame.ptStartPosd * igi2_frame.tEdge0_4) / igi2_frame.v111;
                  if ( v67 < 0.0 || v67 > 1.0 )
                    goto LABEL_106;
                  v68 = igi2_frame.tEdge0;
                  if ( igi2_frame.tEdge0 < 0.0 )
                    v68 = -v68;
                  v69 = igi2_frame.tEdge0_4;
                  if ( igi2_frame.tEdge0_4 < 0.0 )
                    v69 = -v69;
                  if ( v68 <= v69 )
                  {
                    if ( igi2_frame.tEdge0_4 == 0.0 )
                      goto LABEL_106;
                    v70 = (*(float *)&igi2_frame.nVertexPosc - igi2_frame.Real32x3_Rotate_tTemp_4 * v67) / igi2_frame.tEdge0_4;
                  }
                  else
                  {
                    v70 = (igi2_frame.ptStartPosd - igi2_frame.Real32x3_Rotate_tTemp * v67) / igi2_frame.tEdge0;
                  }
                  if ( v70 < 0.0 || v70 + v67 > 1.0 )
                    goto LABEL_106;
                  goto LABEL_100;
                }
                v64 = igi2_frame.ptStartPosb;
                if ( igi2_frame.ptStartPosb == 0.0 )
                  goto LABEL_106;
                igi2_frame.ptEndPosb = igi2_frame.tPos_8 - v49->vZ;
                igi2_frame.ptStartPosc = igi2_frame.tPos - v49->vX;
                v60 = (igi2_frame.ptEndPosb * igi2_frame.tEdge0 - igi2_frame.ptStartPosc * igi2_frame.tEdge0_8) / v64;
                if ( v60 < 0.0 || v60 > 1.0 )
                  goto LABEL_106;
                v65 = igi2_frame.tEdge0;
                if ( igi2_frame.tEdge0 < 0.0 )
                  v65 = -v65;
                v66 = igi2_frame.tEdge0_8;
                if ( igi2_frame.tEdge0_8 < 0.0 )
                  v66 = -v66;
                if ( v65 <= v66 )
                {
LABEL_82:
                  if ( igi2_frame.tEdge0_8 == 0.0 )
                    goto LABEL_106;
                  v63 = (igi2_frame.ptEndPosb - igi2_frame.Real32x3_Rotate_tTemp_8 * v60) / igi2_frame.tEdge0_8;
                  goto LABEL_84;
                }
                v63 = (igi2_frame.ptStartPosc - igi2_frame.Real32x3_Rotate_tTemp * v60) / igi2_frame.tEdge0;
              }
              else
              {
                v59 = *(float *)&igi2_frame.nVertexPosa;
                if ( *(float *)&igi2_frame.nVertexPosa == 0.0 )
                  goto LABEL_106;
                igi2_frame.ptEndPosb = igi2_frame.tPos_8 - v49->vZ;
                *(float *)&igi2_frame.nVertexPosb = igi2_frame.tPos_4 - v49->vY;
                v60 = (igi2_frame.ptEndPosb * igi2_frame.tEdge0_4 - *(float *)&igi2_frame.nVertexPosb * igi2_frame.tEdge0_8) / v59;
                if ( v60 < 0.0 || v60 > 1.0 )
                  goto LABEL_106;
                v61 = igi2_frame.tEdge0_4;
                if ( igi2_frame.tEdge0_4 < 0.0 )
                  v61 = -v61;
                v62 = igi2_frame.tEdge0_8;
                if ( igi2_frame.tEdge0_8 < 0.0 )
                  v62 = -v62;
                if ( v61 <= v62 )
                  goto LABEL_82;
                v63 = (*(float *)&igi2_frame.nVertexPosb - igi2_frame.Real32x3_Rotate_tTemp_4 * v60) / igi2_frame.tEdge0_4;
              }
LABEL_84:
              if ( v63 < 0.0 || v63 + v60 > 1.0 )
                goto LABEL_106;
LABEL_100:
              *((_BYTE *)pxContext + 20) = 1;
              iMaterial = igi2_frame.ptCollMesh->ptMaterial[aiVertex[3]].iMaterial;
              if ( iMaterial == 0xFFFF )
                goto LABEL_104;
              v72 = *(float **)(*((_DWORD *)pxContext + 4) + 4 * iMaterial + 88);
              if ( igi2_frame.v114 < 0.0 )
                *((float *)pxContext + 8) = *((float *)pxContext + 8) * *v72;
              if ( *v72 == 0.0 )
              {
LABEL_104:
                *((_DWORD *)pxContext + 8) = 0;
                return;
              }
LABEL_106:
              aiVertex += 6;
            }
          }
        }
      }
    }
  }
}

// source: e/3/bonedyncubeobj.c:1498  [anchor-mhash]
void __cdecl BoneDynCubeObj_GetCameraTargetInfoHandler(struct QTask_s *ptQTask, void *pxContext)
{
  _DWORD *v2; // eax

  qmemcpy(pxContext, &ptQTask[1], 0x18u);
  *((_DWORD *)pxContext + 6) = 0;
  *((_DWORD *)pxContext + 7) = 0;
  *((_DWORD *)pxContext + 8) = 0;
  qmemcpy((char *)pxContext + 36, &ptQTask[3].ptPrev, 0x28u);
  *((_DWORD *)pxContext + 19) = ptQTask[8].ptNext;
  v2 = *((_DWORD **)pxContext + 20);
  if ( v2 )
  {
    *v2 = 1701736258;
    v2[1] = 1784827680;
    v2[2] = (char *)&HumanAI_atMovementQueueItems[760].tNode.ptPrev + 1;
  }
}

// source: e/3/bonedyncubeobj.c:1539  [anchor-mhash]
void __cdecl BoneDynCubeObj_RegisterHandler(struct QTask_s *ptQTask, void *pxContext)
{
  double v2; // st7
  double v3; // st6
  double v4; // st5
  struct QTask_s *ptHead; // ecx
  int v6; // eax
  struct QTask_s *v7; // edx
  void (__cdecl *pfHandler)(struct QTask_s *, void *); // edx
  int v9; // eax
  struct QTask_s *ptNext; // edi
  int v11; // ecx
  struct QTask_s *v12; // edx
  void (__cdecl *v13)(int, void *); // edx
  int v14; // eax
  float ptDynCubeObj; // [esp+0h] [ebp-14h]

  if ( !ptQTask[2].tQTaskChildren.ptHead )
  {
    v2 = *(float *)&ptQTask[7].tQTaskRefList.ptMiddle;
    v3 = *(float *)&ptQTask[7].tQTaskRefList.ptHead;
    v4 = *(float *)&ptQTask[7].tQTaskChildren.ptTail;
    ptQTask[2].ptParent = *((struct QTask_s **)pxContext + 1);
    ptDynCubeObj = sqrt(v4 * v4 + v3 * v3 + v2 * v2) + *(float *)&ptQTask[8].ptNext;
    World_RegisterDynCubeObjFirstTimeRadius(
      *((struct World_s **)pxContext + 1),
      (struct DynCubeObj_s *)ptQTask,
      (struct real64x3_t *)&ptQTask[1],
      ptDynCubeObj,
      *((enum DynCubeTreeCategory_enum *)pxContext + 2));
    ptHead = ptQTask->tQTaskChildren.ptHead;
    if ( ptHead->ptNext && ptHead )
    {
      v6 = QTask_nProtectedQTaskStackOffset;
      do
      {
        if ( ptHead->ptNext )
          v7 = ptHead->ptNext->ptNext != nullptr ? ptHead->ptNext : nullptr;
        else
          v7 = nullptr;
        QTask_atProtectedQTaskStack[v6].ptQTask = v7;
        pfHandler = (void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[DynCubeObj_eDynCubeObjRegisterQTaskEvent][ptHead->eQTaskType].pfHandler;
        v9 = v6 + 1;
        QTask_nProtectedQTaskStackOffset = v9;
        if ( pfHandler )
        {
          pfHandler(ptHead, pxContext);
          v9 = QTask_nProtectedQTaskStackOffset;
        }
        ptHead = (struct QTask_s *)dword_849C7DC[v9];
        v6 = v9 - 1;
        QTask_nProtectedQTaskStackOffset = v6;
      }
      while ( ptHead );
    }
    else
    {
      v6 = QTask_nProtectedQTaskStackOffset;
    }
    ptNext = ptQTask[3].ptNext;
    if ( ptNext )
    {
      v11 = (int)ptNext->tQTaskChildren.ptHead;
      if ( *(_DWORD *)v11 )
      {
        for ( ; v11; QTask_nProtectedQTaskStackOffset = v6 )
        {
          if ( *(_DWORD *)v11 )
            v12 = **(_DWORD **)v11 != 0 ? *(struct QTask_s **)v11 : nullptr;
          else
            v12 = nullptr;
          QTask_atProtectedQTaskStack[v6].ptQTask = v12;
          v13 = (void (__cdecl *)(int, void *))QTask_aatQTaskFinalEvent[DynCubeObj_eDynCubeObjRegisterQTaskEvent][*(unsigned __int16 *)(v11 + 36)].pfHandler;
          v14 = v6 + 1;
          QTask_nProtectedQTaskStackOffset = v14;
          if ( v13 )
          {
            v13(v11, pxContext);
            v14 = QTask_nProtectedQTaskStackOffset;
          }
          v11 = dword_849C7DC[v14];
          v6 = v14 - 1;
        }
      }
    }
  }
}

// source: e/3/bonedyncubeobj.c:1579  [anchor-mhash]
void __cdecl BoneDynCubeObj_SetPositionHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *ptHead; // ecx
  int v3; // edx
  struct QTask_s *v4; // eax
  int v5; // esi
  void (__cdecl *pfHandler)(struct QTask_s *); // eax
  int v7; // edx
  float ptDynCubeObj; // [esp+0h] [ebp-10h]

  ptDynCubeObj = sqrt(
                   *(float *)&ptQTask[7].tQTaskChildren.ptTail * *(float *)&ptQTask[7].tQTaskChildren.ptTail
                 + *(float *)&ptQTask[7].tQTaskRefList.ptHead * *(float *)&ptQTask[7].tQTaskRefList.ptHead
                 + *(float *)&ptQTask[7].tQTaskRefList.ptMiddle * *(float *)&ptQTask[7].tQTaskRefList.ptMiddle)
               + *(float *)&ptQTask[8].ptNext;
  World_MoveDynCubeObjRadius(
    World_ptActiveWorld,
    (struct DynCubeObj_s *)ptQTask,
    (struct real64x3_t *)pxContext,
    ptDynCubeObj);
  qmemcpy(&ptQTask[3].ptPrev, (char *)pxContext + 24, sizeof(struct QTask_s));
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
      v5 = Attach_eUpdateAttachmentEvent;
      QTask_atProtectedQTaskStack[v3].ptQTask = v4;
      pfHandler = (void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[v5][ptHead->eQTaskType].pfHandler;
      v7 = v3 + 1;
      QTask_nProtectedQTaskStackOffset = v7;
      if ( pfHandler )
      {
        pfHandler(ptHead);
        v7 = QTask_nProtectedQTaskStackOffset;
      }
      ptHead = (struct QTask_s *)dword_849C7DC[v7];
      v3 = v7 - 1;
      QTask_nProtectedQTaskStackOffset = v3;
    }
    while ( ptHead );
  }
}

// source: e/3/bonedyncubeobj.c:1643  [anchor-strings]
void __cdecl BoneDynCubeObj_GenericOpen()
{
  __int16 v0; // ax
  unsigned __int16 v1; // si
  __int16 v2; // di

  BoneDynCubeObj_eQTaskType = QTask_NewQTaskType("BoneDynCubeObj", 400, ModelObj_eQTaskType, 0, 0);
  BoneDynCubeObj_eInterpolateQTaskEvent = QTask_NewQTaskEventNoContextFn(BoneDynCubeObj_eQTaskType, "Interpolate");
  v0 = QTask_NewQTaskEventFn(BoneDynCubeObj_eQTaskType, "CollisionEval");
  v1 = BoneDynCubeObj_eQTaskType;
  v2 = v0;
  BoneDynCubeObj_eQTaskCollisionEvalEvent = v0;
  QTask_LinkQTaskEventHandlerNoContextFn(BoneDynCubeObj_eQTaskType, 1, BoneDynCubeObj_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 2, BoneDynCubeObj_DeleteHandler);
  QTask_LinkQTaskEventHandlerFn(v1, 5, BoneDynCubeObj_EnterHandler);
  QTask_LinkQTaskEventHandlerFn(v1, 8, BoneDynCubeObj_GetCameraTargetInfoHandler);
  QTask_LinkQTaskEventHandlerFn(v1, 10, BoneDynCubeObj_TraceLinesHandler);
  QTask_LinkQTaskEventHandlerFn(v1, 9, BoneDynCubeObj_LineOfSightHandler);
  QTask_LinkQTaskEventHandlerFn(v1, v2, BoneDynCubeObj_CollisionEvaluateHandler);
  QTask_LinkQTaskEventHandlerFn(v1, DynCubeObj_eDynCubeObjRegisterQTaskEvent, BoneDynCubeObj_RegisterHandler);
  QTask_LinkQTaskEventHandlerFn(v1, 7, BoneDynCubeObj_SetPositionHandler);
  QTask_LinkQTaskEventHandlerFn(v1, Attach_eAttachEvent, BoneDynCubeObj_AttachHandler);
  BoneDynCubeObj_ptUpdateHierarchyProfileRegion = nullptr;
  BoneDynCubeObj_ptUpdateHierarchyProfileRegionWOChildren = nullptr;
}

// source: e/3/bonedyncubeobj.c:1681  [size]
void __cdecl BoneDynCubeObj_GenericClose()
{
  QTask_DeleteQTaskType(BoneDynCubeObj_eQTaskType);
  BoneDynCubeObj_eQTaskType = 512;
  QTask_DeleteQTaskEvent(BoneDynCubeObj_eQTaskCollisionEvalEvent);
  BoneDynCubeObj_eQTaskCollisionEvalEvent = 512;
  QTask_DeleteQTaskEventNoContext(BoneDynCubeObj_eInterpolateQTaskEvent);
  BoneDynCubeObj_eInterpolateQTaskEvent = 512;
}

// source: e/3/bonedyncubeobj.c:1706  [size]
unsigned __int16 __cdecl BoneDynCubeObj_GetQTaskType()
{
  return BoneDynCubeObj_eQTaskType;
}

// source: e/3/bonedyncubeobj.c:1721  [size]
int __cdecl BoneDynCubeObj_GetInterpolateQTaskEvent()
{
  return BoneDynCubeObj_eInterpolateQTaskEvent;
}

// source: e/3/bonedyncubeobj.c:1739  [anchor-mhash]
struct QTask_s *__cdecl BoneDynCubeObj_New(
        struct QTask_s *ptParent,
        struct World_s *ptWorld,
        struct real64x3_t *ptPos,
        char *zModel)
{
  struct BoneDynCubeObj_s *v5; // edi
  struct LODVirModel_s *LODVirModelExistsFn; // eax
  float ptDynCubeObj; // [esp+0h] [ebp-10h]

  v5 = (struct BoneDynCubeObj_s *)QTask_NewFn(ptParent, BoneDynCubeObj_eQTaskType, nullptr);
  BoneDynCubeObj_Init(v5, ptWorld);
  LODVirModelExistsFn = MTP_GetLODVirModelExistsFn(zModel);
  if ( !LODVirModelExistsFn )
  {
    LDebug_Error("VirModel \"%s\" not available", zModel);
    abort();
  }
  BoneDynCubeObj_SetLODVirModel(v5, LODVirModelExistsFn);
  ptDynCubeObj = sqrt(
                   v5->tRootTranslation.vX * v5->tRootTranslation.vX
                 + v5->tRootTranslation.vY * v5->tRootTranslation.vY
                 + v5->tRootTranslation.vZ * v5->tRootTranslation.vZ)
               + v5->vRadius;
  World_RegisterDynCubeObjFirstTimeRadius(
    ptWorld,
    &v5->tModelObj.tDynCubeObj,
    ptPos,
    ptDynCubeObj,
    WORLD_DYNCUBETREE_CATEGORY_MOBILE);
  BoneDynCubeObj_CreateAttachObjects(
    v5,
    &v5->tModelObj.tDynCubeObj.tQObj.tQTask,
    &v5->tModelObj.tDynCubeObj.tQObj.tQTask);
  return &v5->tModelObj.tDynCubeObj.tQObj.tQTask;
}

// source: e/3/bonedyncubeobj.c:1788  [anchor-mhash]
void __cdecl BoneDynCubeObj_Init(
        struct BoneDynCubeObj_s *ptBoneDynCubeObj,
        struct World_s *ptWorld)
{
  ModelObj_Init(&ptBoneDynCubeObj->tModelObj, ptWorld, ptBoneDynCubeObj->tModelObj.ptLODVirModel);
  ptBoneDynCubeObj->tRootTranslation.vX = 0.0;
  ptBoneDynCubeObj->tRootTranslation.vY = 0.0;
  ptBoneDynCubeObj->tRootTranslation.vZ = 0.0;
  ptBoneDynCubeObj->patBone = nullptr;
  ptBoneDynCubeObj->vRadius = 1.0;
  memset(ptBoneDynCubeObj->avMorphWeights, 0, sizeof(ptBoneDynCubeObj->avMorphWeights));
  ptBoneDynCubeObj->abBloodStains = nullptr;
  ptBoneDynCubeObj->nHierarchyUseCount = 0;
}

// source: e/3/bonedyncubeobj.c:1822  [anchor-hash]
struct BoneDynCubeObj_s *__cdecl BoneDynCubeObj_DeInit(struct BoneDynCubeObj_s *ptBoneDynCubeObj)
{
  return BoneDynCubeObj_SetLODVirModel(ptBoneDynCubeObj, nullptr);
}

// source: e/3/bonedyncubeobj.c:1835  [anchor-callee]
struct BoneDynCubeObj_s *__cdecl BoneDynCubeObj_SetLODVirModel(
        struct BoneDynCubeObj_s *ptBoneDynCubeObj,
        struct LODVirModel_s *ptLODVirModel)
{
  struct LODVirModel_s *v2; // ebp
  struct BoneDynCubeObj_s *v3; // esi
  struct Bone_s *patBone; // eax
  int v5; // ebp
  struct Mesh3D_Mesh_t *ptMesh; // edi
  double vRadius; // st7
  float *p_vX; // ecx
  __int16 nBones; // ax
  int v10; // eax
  _DWORD *v11; // edx
  _DWORD *v12; // ecx
  int v13; // [esp+8h] [ebp-8h]
  int i; // [esp+Ch] [ebp-4h]

  v2 = ptLODVirModel;
  v3 = ptBoneDynCubeObj;
  if ( ptBoneDynCubeObj->tModelObj.ptLODVirModel != ptLODVirModel )
  {
    if ( !ptLODVirModel || ptLODVirModel->aptVirModel[0]->ptModel->ptMesh->pcHierarchy != ptBoneDynCubeObj->pcHierarchy )
    {
      patBone = ptBoneDynCubeObj->patBone;
      if ( patBone )
      {
        --Mem_nCurrentAllocations;
        v5 = *(_DWORD *)((unsigned int)&patBone[-1].pfCallback & 0xFFFFFFFC);
        Node_Remove((_DWORD **)v5);
        memset(*(void **)(v5 + 8), 0xCDu, *(_DWORD *)(v5 + 16));
        free((void *)v5);
        v2 = ptLODVirModel;
        v3->patBone = nullptr;
      }
      v3->pcHierarchy = nullptr;
    }
    if ( v2 )
    {
      ptMesh = v2->aptVirModel[0]->ptModel->ptMesh;
      v3->ptHierarchyTranslations = ptMesh->ptBoneTranslations;
      if ( v2->aptVirModel[0] )
        vRadius = v2->aptVirModel[0]->ptModel->ptMesh->vRadius;
      else
        vRadius = 1.0;
      v3->vRadius = vRadius;
      v3->nBones = ptMesh->nBones;
      v3->isTouched = 1;
      if ( ptMesh->nBones <= 0 )
      {
        v3->tRootTranslation.vX = 0.0;
        v3->tRootTranslation.vY = 0.0;
        v3->tRootTranslation.vZ = 0.0;
      }
      else
      {
        p_vX = &ptMesh->ptBoneTranslations->vX;
        v3->tRootTranslation.vX = *p_vX;
        v3->tRootTranslation.vY = p_vX[1];
        v3->tRootTranslation.vZ = p_vX[2];
      }
      nBones = ptMesh->nBones;
      if ( nBones > 0 && v2->aptVirModel[0]->ptModel->ptMesh->pcHierarchy != v3->pcHierarchy )
      {
        v3->patBone = (struct Bone_s *)Mem_AllocFn(80 * nBones, 16);
        v3->pcHierarchy = ptMesh->pcHierarchy;
        i = 0;
        if ( ptMesh->nBones > 0 )
        {
          v10 = 0;
          v13 = 0;
          do
          {
            v3->patBone[v10].tOrientation.vX = 0.0;
            v3->patBone[v10].tOrientation.vY = 0.0;
            v3->patBone[v10].tOrientation.vZ = 0.0;
            v3->patBone[v10].tOrientation.vW = 1.0;
            v3->patBone[v10].tOrientation.nOps = 0;
            v3->patBone[v10].tMatrix.tX.vX = 1.0;
            v3->patBone[v10].tMatrix.tX.vY = 0.0;
            v3->patBone[v10].tMatrix.tX.vZ = 0.0;
            v3->patBone[v10].tMatrix.tY.vX = 0.0;
            v3->patBone[v10].tMatrix.tY.vY = 1.0;
            v3->patBone[v10].tMatrix.tY.vZ = 0.0;
            v3->patBone[v10].tMatrix.tZ.vX = 0.0;
            v3->patBone[v10].tMatrix.tZ.vY = 0.0;
            v3->patBone[v10].tMatrix.tZ.vZ = 1.0;
            v3->patBone[v10].tMatrix.nOps = 0;
            v11 = (_DWORD *)&v3->ptHierarchyTranslations[v13].vX;
            v12 = (_DWORD *)&v3->patBone[v10].tTranslation.vX;
            *v12 = *v11;
            v12[1] = v11[1];
            v12[2] = v11[2];
            v3->patBone[v10].vPadding1 = 0.0;
            v3->patBone[v10++].pfCallback = nullptr;
            ++i;
            ++v13;
          }
          while ( i < ptMesh->nBones );
          v2 = ptLODVirModel;
        }
      }
    }
    else
    {
      v3->vRadius = 1.0;
      v3->nBones = 0;
      v3->isTouched = 0;
      v3->ptHierarchyTranslations = nullptr;
    }
    ModelObj_SetLODVirModel(&v3->tModelObj, v2, false);
    if ( v2 )
      BoneDynCubeObj_InitBloodStains(v3);
    else
      BoneDynCubeObj_DeInitBloodStains(v3);
  }
  return ptBoneDynCubeObj;
}

// source: e/3/bonedyncubeobj.c:2064  [anchor-callee]
float __cdecl BoneDynCubeObj_GetRadius(struct BoneDynCubeObj_s *ptBoneDynCubeObj)
{
  return sqrt(
           ptBoneDynCubeObj->tRootTranslation.vX * ptBoneDynCubeObj->tRootTranslation.vX
         + ptBoneDynCubeObj->tRootTranslation.vY * ptBoneDynCubeObj->tRootTranslation.vY
         + ptBoneDynCubeObj->tRootTranslation.vZ * ptBoneDynCubeObj->tRootTranslation.vZ)
       + ptBoneDynCubeObj->vRadius;
}

// source: e/3/bonedyncubeobj.c:2080  [anchor-mhash]
enum bool __cdecl BoneDynCubeObj_Exclude(
        struct BoneDynCubeObj_s *ptBoneDynCubeObj,
        enum bool *pisTotallyInside)
{
  #pragma pack(push, 1)
  union
  {
    struct { float vRadius; };
    struct { char igi2_o1[4]; struct real32x3_t tPos; };
    struct { char igi2_o2[16]; struct real32x3_t Real32x3_Rotate_tTemp; };
    char igi2_extent[28];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct LODVirModel_s *ptLODVirModel; // edx
  float *p_vVersion; // eax
  double v4; // st7
  double v5; // st6
  double v6; // st5
  double v7; // st7
  double vY; // st7
  double vX; // st7

  ptLODVirModel = ptBoneDynCubeObj->tModelObj.ptLODVirModel;
  igi2_frame.tPos.vX = ptBoneDynCubeObj->tModelObj.tDynCubeObj.tQObj.tPos.vX - TransContext_tActiveTransContext.tPos.vX;
  igi2_frame.tPos.vY = ptBoneDynCubeObj->tModelObj.tDynCubeObj.tQObj.tPos.vY - TransContext_tActiveTransContext.tPos.vY;
  igi2_frame.tPos.vZ = ptBoneDynCubeObj->tModelObj.tDynCubeObj.tQObj.tPos.vZ - TransContext_tActiveTransContext.tPos.vZ;
  if ( ptLODVirModel )
  {
    p_vVersion = &ptLODVirModel->aptVirModel[0]->ptModel->ptMesh->vVersion;
    v4 = p_vVersion[12] + ptBoneDynCubeObj->tRootTranslation.vX;
    v5 = p_vVersion[13] + ptBoneDynCubeObj->tRootTranslation.vY;
    v6 = p_vVersion[14] + ptBoneDynCubeObj->tRootTranslation.vZ;
    igi2_frame.Real32x3_Rotate_tTemp.vX = v6 * ptBoneDynCubeObj->tModelObj.tOrientation.tX.vZ
                             + v5 * ptBoneDynCubeObj->tModelObj.tOrientation.tX.vY
                             + v4 * ptBoneDynCubeObj->tModelObj.tOrientation.tX.vX;
    igi2_frame.Real32x3_Rotate_tTemp.vY = v6 * ptBoneDynCubeObj->tModelObj.tOrientation.tY.vZ
                             + v5 * ptBoneDynCubeObj->tModelObj.tOrientation.tY.vY
                             + v4 * ptBoneDynCubeObj->tModelObj.tOrientation.tY.vX;
    v7 = v6 * ptBoneDynCubeObj->tModelObj.tOrientation.tZ.vZ
       + v5 * ptBoneDynCubeObj->tModelObj.tOrientation.tZ.vY
       + v4 * ptBoneDynCubeObj->tModelObj.tOrientation.tZ.vX;
    igi2_frame.tPos.vX = igi2_frame.Real32x3_Rotate_tTemp.vX + igi2_frame.tPos.vX;
    igi2_frame.tPos.vY = igi2_frame.Real32x3_Rotate_tTemp.vY + igi2_frame.tPos.vY;
    igi2_frame.tPos.vZ = v7 + igi2_frame.tPos.vZ;
    if ( ptBoneDynCubeObj->tModelObj.tScale.vX <= (double)ptBoneDynCubeObj->tModelObj.tScale.vY )
      vY = ptBoneDynCubeObj->tModelObj.tScale.vY;
    else
      vY = ptBoneDynCubeObj->tModelObj.tScale.vX;
    if ( vY <= ptBoneDynCubeObj->tModelObj.tScale.vZ )
    {
      igi2_frame.vRadius = ptBoneDynCubeObj->tModelObj.tScale.vZ
              * ptLODVirModel->aptVirModel[0]->ptModel->ptMesh->tRenderMeshSphere.vRadius;
    }
    else
    {
      if ( ptBoneDynCubeObj->tModelObj.tScale.vX <= (double)ptBoneDynCubeObj->tModelObj.tScale.vY )
        vX = ptBoneDynCubeObj->tModelObj.tScale.vY;
      else
        vX = ptBoneDynCubeObj->tModelObj.tScale.vX;
      igi2_frame.vRadius = vX * ptLODVirModel->aptVirModel[0]->ptModel->ptMesh->tRenderMeshSphere.vRadius;
    }
  }
  else
  {
    igi2_frame.vRadius = 1.0;
  }
  igi2_frame.Real32x3_Rotate_tTemp.vX = TransContext_tActiveTransContext.tMatrix.tX.vZ * igi2_frame.tPos.vZ
                           + TransContext_tActiveTransContext.tMatrix.tX.vY * igi2_frame.tPos.vY
                           + TransContext_tActiveTransContext.tMatrix.tX.vX * igi2_frame.tPos.vX;
  igi2_frame.Real32x3_Rotate_tTemp.vY = TransContext_tActiveTransContext.tMatrix.tY.vZ * igi2_frame.tPos.vZ
                           + TransContext_tActiveTransContext.tMatrix.tY.vY * igi2_frame.tPos.vY
                           + TransContext_tActiveTransContext.tMatrix.tY.vX * igi2_frame.tPos.vX;
  igi2_frame.Real32x3_Rotate_tTemp.vZ = TransContext_tActiveTransContext.tMatrix.tZ.vZ * igi2_frame.tPos.vZ
                           + TransContext_tActiveTransContext.tMatrix.tZ.vY * igi2_frame.tPos.vY
                           + TransContext_tActiveTransContext.tMatrix.tZ.vX * igi2_frame.tPos.vX;
  igi2_frame.tPos = igi2_frame.Real32x3_Rotate_tTemp;
  return Mesh3D_ExcludeObject(&igi2_frame.tPos, igi2_frame.vRadius, pisTotallyInside);
}

int __cdecl sub_580CA0(int result, double *a2)
{
  double v2; // rt0
  float v3; // [esp+8h] [ebp-4h]

  v3 = *(float *)(result + 152) * *(float *)(result + 300)
     + *(float *)(result + 148) * *(float *)(result + 296)
     + *(float *)(result + 156) * *(float *)(result + 304);
  v2 = *(float *)(result + 140) * *(float *)(result + 300)
     + *(float *)(result + 136) * *(float *)(result + 296)
     + *(float *)(result + 144) * *(float *)(result + 304);
  *a2 = *(float *)(result + 128) * *(float *)(result + 300)
      + *(float *)(result + 124) * *(float *)(result + 296)
      + *(float *)(result + 132) * *(float *)(result + 304)
      + *(double *)(result + 40);
  a2[1] = v2 + *(double *)(result + 48);
  a2[2] = v3 + *(double *)(result + 56);
  return result;
}

// source: e/3/bonedyncubeobj.c:2121  [anchor-callee]
void __cdecl BoneDynCubeObj_GetBonePosition(
        struct BoneDynCubeObj_s *ptBoneDynCubeObj,
        struct real32x3_t *ptPos,
        int nBone)
{
  float *v3; // eax
  double v4; // rt0
  float v6; // [esp+Ch] [ebp-4h]

  BoneDynCubeObj_UpdateHierarchy(ptPos);
  v3 = (float *)(LODWORD(ptPos[26].vY) + 80 * nBone);
  v6 = ptPos[13].vX * v3[2] + ptPos[12].vZ * v3[1] + ptPos[12].vY * *v3;
  v4 = ptPos[12].vX * v3[2] + ptPos[11].vZ * v3[1] + ptPos[11].vY * *v3;
  *(double *)&ptBoneDynCubeObj->tModelObj.tDynCubeObj.tQObj.tQTask.ptNext = ptPos[11].vX * v3[2]
                                                                          + ptPos[10].vZ * v3[1]
                                                                          + ptPos[10].vY * *v3
                                                                          + *(double *)&ptPos[3].vY;
  *(double *)&ptBoneDynCubeObj->tModelObj.tDynCubeObj.tQObj.tQTask.tQTaskChildren.ptHead = v4 + *(double *)&ptPos[4].vX;
  *(double *)&ptBoneDynCubeObj->tModelObj.tDynCubeObj.tQObj.tQTask.tQTaskChildren.ptTail = v6 + *(double *)&ptPos[4].vZ;
}

// source: e/3/bonedyncubeobj.c:2190  [anchor-mhash]
char *__cdecl BoneDynCubeObj_GetBonePositionFromName(
        struct BoneDynCubeObj_s *ptBoneDynCubeObj,
        struct real32x3_t *ptPos,
        char *zName)
{
  int Bone; // eax
  char *result; // eax

  Bone = Hierarchy_GetBone(ptBoneDynCubeObj->pcHierarchy, zName);
  BoneDynCubeObj_GetBonePosition((struct BoneDynCubeObj_s *)ptPos, (struct real32x3_t *)ptBoneDynCubeObj, Bone);
  return result;
}

int __cdecl BoneDynCubeObj_GetBoneWorldPositionFromName(
        struct BoneDynCubeObj_s *ptBoneDynCubeObj,
        int a2,
        float *a3)
{
  struct Bone_s *v5; // eax
  int nOps; // edx
  double v7; // st7
  double v8; // st6
  int result; // eax
  float v10[10]; // [esp+8h] [ebp-28h] BYREF

  BoneDynCubeObj_UpdateHierarchy(ptBoneDynCubeObj);
  v5 = &ptBoneDynCubeObj->patBone[a2];
  v10[0] = ptBoneDynCubeObj->tModelObj.tOrientation.tX.vY * v5->tMatrix.tY.vX
         + ptBoneDynCubeObj->tModelObj.tOrientation.tX.vX * v5->tMatrix.tX.vX
         + ptBoneDynCubeObj->tModelObj.tOrientation.tX.vZ * v5->tMatrix.tZ.vX;
  v10[1] = v5->tMatrix.tY.vY * ptBoneDynCubeObj->tModelObj.tOrientation.tX.vY
         + ptBoneDynCubeObj->tModelObj.tOrientation.tX.vZ * v5->tMatrix.tZ.vY
         + v5->tMatrix.tX.vY * ptBoneDynCubeObj->tModelObj.tOrientation.tX.vX;
  v10[2] = v5->tMatrix.tX.vZ * ptBoneDynCubeObj->tModelObj.tOrientation.tX.vX
         + ptBoneDynCubeObj->tModelObj.tOrientation.tX.vZ * v5->tMatrix.tZ.vZ
         + ptBoneDynCubeObj->tModelObj.tOrientation.tX.vY * v5->tMatrix.tY.vZ;
  v10[3] = ptBoneDynCubeObj->tModelObj.tOrientation.tY.vY * v5->tMatrix.tY.vX
         + ptBoneDynCubeObj->tModelObj.tOrientation.tY.vZ * v5->tMatrix.tZ.vX
         + v5->tMatrix.tX.vX * ptBoneDynCubeObj->tModelObj.tOrientation.tY.vX;
  v10[4] = v5->tMatrix.tX.vY * ptBoneDynCubeObj->tModelObj.tOrientation.tY.vX
         + ptBoneDynCubeObj->tModelObj.tOrientation.tY.vZ * v5->tMatrix.tZ.vY
         + ptBoneDynCubeObj->tModelObj.tOrientation.tY.vY * v5->tMatrix.tY.vY;
  v10[5] = ptBoneDynCubeObj->tModelObj.tOrientation.tY.vZ * v5->tMatrix.tZ.vZ
         + ptBoneDynCubeObj->tModelObj.tOrientation.tY.vY * v5->tMatrix.tY.vZ
         + v5->tMatrix.tX.vZ * ptBoneDynCubeObj->tModelObj.tOrientation.tY.vX;
  v10[6] = ptBoneDynCubeObj->tModelObj.tOrientation.tZ.vX * v5->tMatrix.tX.vX
         + ptBoneDynCubeObj->tModelObj.tOrientation.tZ.vY * v5->tMatrix.tY.vX
         + ptBoneDynCubeObj->tModelObj.tOrientation.tZ.vZ * v5->tMatrix.tZ.vX;
  nOps = v5->tMatrix.nOps;
  v10[7] = ptBoneDynCubeObj->tModelObj.tOrientation.tZ.vX * v5->tMatrix.tX.vY
         + ptBoneDynCubeObj->tModelObj.tOrientation.tZ.vZ * v5->tMatrix.tZ.vY
         + ptBoneDynCubeObj->tModelObj.tOrientation.tZ.vY * v5->tMatrix.tY.vY;
  v7 = ptBoneDynCubeObj->tModelObj.tOrientation.tZ.vZ * v5->tMatrix.tZ.vZ
     + ptBoneDynCubeObj->tModelObj.tOrientation.tZ.vY * v5->tMatrix.tY.vZ;
  v8 = ptBoneDynCubeObj->tModelObj.tOrientation.tZ.vX * v5->tMatrix.tX.vZ;
  result = ptBoneDynCubeObj->tModelObj.tOrientation.nOps;
  LODWORD(v10[9]) = nOps + result + 1;
  v10[8] = v7 + v8;
  qmemcpy(a3, v10, 0x28u);
  return result;
}

// source: e/3/bonedyncubeobj.c:2235  [anchor-callee]
unsigned int __cdecl BoneDynCubeObj_GetMagicVertexLocalPos(
        struct BoneDynCubeObj_s *ptBoneDynCubeObj,
        unsigned int iMagicVertex,
        struct real32x3_t *ptPos)
{
  unsigned int result; // eax
  unsigned int v5; // esi
  struct Bone_s *v6; // eax
  struct real32x3_t struct_real32x3_t; // 0:^8.12

  result = (unsigned int)ptBoneDynCubeObj->tModelObj.ptLODVirModel;
  if ( result
    && (result = *(_DWORD *)(*(_DWORD *)(*(_DWORD *)result + 12) + 12), iMagicVertex < *(__int16 *)(result + 124))
    && (v5 = *(_DWORD *)(result + 140) + 16 * iMagicVertex) != 0
    && (result = *(_DWORD *)(v5 + 12), result <= ptBoneDynCubeObj->nBones) )
  {
    if ( ptBoneDynCubeObj->isTouched )
      BoneDynCubeObj_UpdateHierarchy(ptBoneDynCubeObj);
    v6 = &ptBoneDynCubeObj->patBone[*(_DWORD *)(v5 + 12)];
    struct_real32x3_t.vX = v6->tMatrix.tX.vZ * *(float *)(v5 + 8)
                         + v6->tMatrix.tX.vY * *(float *)(v5 + 4)
                         + v6->tMatrix.tX.vX * *(float *)v5;
    struct_real32x3_t.vY = v6->tMatrix.tY.vZ * *(float *)(v5 + 8)
                         + v6->tMatrix.tY.vY * *(float *)(v5 + 4)
                         + v6->tMatrix.tY.vX * *(float *)v5;
    struct_real32x3_t.vZ = v6->tMatrix.tZ.vZ * *(float *)(v5 + 8)
                         + v6->tMatrix.tZ.vY * *(float *)(v5 + 4)
                         + v6->tMatrix.tZ.vX * *(float *)v5;
    *ptPos = struct_real32x3_t;
    ptPos->vX = ptBoneDynCubeObj->patBone[*(_DWORD *)(v5 + 12)].tTranslation.vX + ptPos->vX;
    ptPos->vY = ptBoneDynCubeObj->patBone[*(_DWORD *)(v5 + 12)].tTranslation.vY + ptPos->vY;
    result = 80 * *(_DWORD *)(v5 + 12);
    ptPos->vZ = *(float *)((char *)&ptBoneDynCubeObj->patBone->tTranslation.vZ + result) + ptPos->vZ;
    ptPos->vX = ptBoneDynCubeObj->tModelObj.tScale.vX * ptPos->vX;
    ptPos->vY = ptBoneDynCubeObj->tModelObj.tScale.vY * ptPos->vY;
    ptPos->vZ = ptBoneDynCubeObj->tModelObj.tScale.vZ * ptPos->vZ;
  }
  else
  {
    ptPos->vX = 0.0;
    ptPos->vY = 0.0;
    ptPos->vZ = 0.0;
  }
  return result;
}

// source: e/3/bonedyncubeobj.c:2275  [anchor-callee]
unsigned int __cdecl BoneDynCubeObj_GetMagicVertexPos(
        struct BoneDynCubeObj_s *ptBoneDynCubeObj,
        unsigned int iMagicVertex,
        struct real64x3_t *ptPos)
{
  unsigned int result; // eax
  double v5; // st7
  double v6; // st6
  struct real32x3_t tLocalPos; // [esp+8h] [ebp-Ch] BYREF

  result = BoneDynCubeObj_GetMagicVertexLocalPos(ptBoneDynCubeObj, iMagicVertex, &tLocalPos);
  v5 = tLocalPos.vZ * ptBoneDynCubeObj->tModelObj.tOrientation.tX.vZ
     + tLocalPos.vY * ptBoneDynCubeObj->tModelObj.tOrientation.tX.vY
     + tLocalPos.vX * ptBoneDynCubeObj->tModelObj.tOrientation.tX.vX;
  v6 = tLocalPos.vZ * ptBoneDynCubeObj->tModelObj.tOrientation.tY.vZ
     + tLocalPos.vY * ptBoneDynCubeObj->tModelObj.tOrientation.tY.vY
     + tLocalPos.vX * ptBoneDynCubeObj->tModelObj.tOrientation.tY.vX;
  tLocalPos.vZ = tLocalPos.vZ * ptBoneDynCubeObj->tModelObj.tOrientation.tZ.vZ
               + tLocalPos.vY * ptBoneDynCubeObj->tModelObj.tOrientation.tZ.vY
               + tLocalPos.vX * ptBoneDynCubeObj->tModelObj.tOrientation.tZ.vX;
  ptPos->vX = v5 + ptBoneDynCubeObj->tModelObj.tDynCubeObj.tQObj.tPos.vX;
  ptPos->vY = v6 + ptBoneDynCubeObj->tModelObj.tDynCubeObj.tQObj.tPos.vY;
  ptPos->vZ = tLocalPos.vZ + ptBoneDynCubeObj->tModelObj.tDynCubeObj.tQObj.tPos.vZ;
  return result;
}

// source: e/3/bonedyncubeobj.c:2296  [size]
unsigned int __cdecl BoneDynCubeObj_SetBoneCallback(
        struct BoneDynCubeObj_s *ptBoneDynCubeObj,
        unsigned int iBone,
        void (__cdecl *pfCallback)(struct BoneDynCubeObj_s *, struct Bone_s *, struct Bone_s *))
{
  unsigned int result; // eax

  result = iBone;
  ptBoneDynCubeObj->patBone[result].pfCallback = pfCallback;
  return result * 80;
}

// source: e/3/bonedyncubeobj.c:2311  [size]
int __cdecl BoneDynCubeObj_GetCreateBruiseRenderModeMethod()
{
  return BoneDynCubeObj_eCreateBruiseRenderModeMethode;
}
