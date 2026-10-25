/* j/0/objects/bullethole.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/objects/bullethole.c:138  [anchor-mhash]
void __cdecl BulletHole_GetObjectBoundingSphereHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *ptTail; // eax
  void (__cdecl *pfHandler)(struct QTask_s *, ...); // ecx

  ptTail = ptQTask[1481].tQTaskChildren.ptTail;
  if ( ptTail )
  {
    pfHandler = (void (__cdecl *)(struct QTask_s *, ...))QTask_aatQTaskFinalEvent[SLOWORD(ShadowVolume_vIntensity)][ptTail->eQTaskType].pfHandler;
    if ( pfHandler )
      pfHandler(ptQTask[1481].tQTaskChildren.ptTail, pxContext);
  }
}

// source: j/0/objects/bullethole.c:157  [size]
void __cdecl BulletHole_MagicObjEnterHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *v2; // edi
  struct QTask_s *ptMiddle; // eax
  struct QTask_s **p_ptParent; // ecx
  struct QTask_s *ptPrev; // esi
  struct QTask_s *v6; // eax
  int iCount; // [esp+Ch] [ebp-8h]
  struct PolyListDynCubeObj_t *ptPolyListDynCubeObj; // [esp+10h] [ebp-4h]

  v2 = ptQTask;
  ptMiddle = ptQTask[1481].tQTaskChildren.ptMiddle;
  ptPolyListDynCubeObj = (struct PolyListDynCubeObj_t *)ptMiddle;
  if ( LOBYTE(ptQTask[1481].eQTaskType) )
  {
    ptMiddle[4].ptPrev = nullptr;
    iCount = 0;
    if ( (int)ptQTask[481].tQTaskChildren.ptHead > 0 )
    {
      p_ptParent = &ptQTask[2].ptParent;
      do
      {
        if ( p_ptParent[3] != (struct QTask_s *)-1 )
        {
          ptPrev = ptMiddle[4].ptPrev;
          if ( (int)&ptPrev->ptNext + 1 < 500 )
          {
            v6 = &v2[2 * (int)ptPrev];
            v6[482].ptParent = *(p_ptParent - 18);
            *(_DWORD *)&v6[482].eQTaskType = *(p_ptParent - 17);
            v6[483].ptNext = *(p_ptParent - 16);
            v6[484].ptParent = *(p_ptParent - 18);
            *(_DWORD *)&v6[484].eQTaskType = *(p_ptParent - 17);
            v6[485].ptNext = *(p_ptParent - 16);
            v6[481].tQTaskRefList.ptMiddle = (struct QReference_s *)p_ptParent;
            v6[481].tQTaskRefList.ptTail = (struct QReference_s *)p_ptParent;
            v6[481].ptParent = (struct QTask_s *)p_ptParent;
            v6[483].tQTaskRefList.ptMiddle = (struct QReference_s *)p_ptParent;
            v6[483].tQTaskRefList.ptTail = (struct QReference_s *)p_ptParent;
            v6[483].ptParent = (struct QTask_s *)p_ptParent;
            v6[481].tQTaskChildren.ptMiddle = (struct QTask_s *)(p_ptParent - 12);
            v6[481].tQTaskChildren.ptTail = (struct QTask_s *)(p_ptParent - 9);
            v6[481].tQTaskRefList.ptHead = (struct QReference_s *)(p_ptParent - 6);
            v6[483].tQTaskChildren.ptMiddle = (struct QTask_s *)(p_ptParent - 9);
            v6[483].tQTaskRefList.ptHead = (struct QReference_s *)(p_ptParent - 6);
            v2 = ptQTask;
            v6[483].tQTaskChildren.ptTail = (struct QTask_s *)(p_ptParent - 3);
            *(_DWORD *)&v6[481].eQTaskType = 0;
            v6[482].ptNext = nullptr;
            v6[482].ptPrev = nullptr;
            v6[482].tQTaskChildren.ptHead = (struct QTask_s *)1065353216;
            v6[482].tQTaskChildren.ptMiddle = (struct QTask_s *)1065353216;
            v6[482].tQTaskChildren.ptTail = nullptr;
            *(_DWORD *)&v6[483].eQTaskType = 0;
            v6[484].ptNext = (struct QTask_s *)1065353216;
            v6[484].ptPrev = (struct QTask_s *)1065353216;
            v6[484].tQTaskChildren.ptHead = (struct QTask_s *)1065353216;
            v6[484].tQTaskChildren.ptMiddle = (struct QTask_s *)1065353216;
            v6[484].tQTaskChildren.ptTail = nullptr;
            v6[482].tQTaskRefList.ptHead = (struct QReference_s *)1065353216;
            v6[482].tQTaskRefList.ptMiddle = (struct QReference_s *)1065353216;
            v6[482].tQTaskRefList.ptTail = (struct QReference_s *)1065353216;
            v6[484].tQTaskRefList.ptHead = (struct QReference_s *)1065353216;
            v6[484].tQTaskRefList.ptMiddle = (struct QReference_s *)1065353216;
            v6[484].tQTaskRefList.ptTail = (struct QReference_s *)1065353216;
            v6[483].ptPrev = p_ptParent[4];
            v6[485].ptPrev = p_ptParent[4];
            ptMiddle = &ptPolyListDynCubeObj->tDynCubeObj.tQObj.tQTask;
            ptPolyListDynCubeObj->nNumPolys += 2;
          }
        }
        p_ptParent += 24;
        ++iCount;
      }
      while ( iCount < (int)v2[481].tQTaskChildren.ptHead );
    }
    LOBYTE(v2[1481].eQTaskType) = 0;
  }
  qmemcpy(&ptMiddle[1], pxContext, 0x18u);
  qmemcpy(&ptMiddle[3], (char *)pxContext + 24, sizeof(struct QTask_s));
  ((void (__cdecl *)(struct QTask_s *, _DWORD))QTask_aatQTaskFinalEvent[5][ptMiddle->eQTaskType].pfHandler)(ptMiddle, 0);
}

// source: j/0/objects/bullethole.c:253  [anchor-mhash]
void __cdecl BulletHole_DeleteHandler(struct QTask_s *ptQTask)
{
  QObjectVector_RemoveElement(
    BulletHole_tBulletHolePool,
    *(_DWORD *)((char *)ptQTask[1481].tQTaskRefList.ptHead + BulletHole_tBulletHolePool->nElementSize - 4));
  QVector_RemoveElementByPointer(BulletHole_ptTasks, ptQTask);
}

// source: j/0/objects/bullethole.c:278  [anchor-mhash]
int __cdecl BulletHole_AddItem(
        struct real64x3_t *ptPos,
        struct real32x9_t *ptOrientation,
        struct BulletHole_s *ptBulletHole,
        struct Hole_t *ptHole,
        struct QIntersection_s *ptIntersection,
        int nBulletHoleType,
        struct TexInfo_s *ptTexInfo,
        float vRadius)
{
  #pragma pack(push, 1)
  union
  {
    struct { float Real32x3_Rotate_tTemp; };
    struct { float Real32x3_Rotate_tTempa; };
    struct { float Real32x3_Rotate_tTempb; };
    struct { char igi2_o3[4]; float Real32x3_Rotate_tTemp_4; };
    struct { char igi2_o4[4]; float Real32x3_Rotate_tTemp_4a; };
    struct { char igi2_o5[4]; float Real32x3_Rotate_tTemp_4b; };
    struct { char igi2_o6[4]; float Real32x3_Rotate_tTemp_4c; };
    struct { char igi2_o7[8]; float Real32x3_Rotate_tTemp_8; };
    struct { char igi2_o8[8]; float Real32x3_Rotate_tTemp_8a; };
    struct { char igi2_o9[8]; float Real32x3_Rotate_tTemp_8b; };
    struct { char igi2_o10[8]; float Real32x3_Rotate_tTemp_8c; };
    struct { char igi2_o11[12]; float v50; };
    struct { char igi2_o12[16]; float v51; };
    struct { char igi2_o13[16]; float v52; };
    struct { char igi2_o14[20]; struct real64x3_t tTempStart3; };
    struct { char igi2_o15[48]; float v54; };
    struct { char igi2_o16[52]; float v55; };
    struct { char igi2_o17[56]; float v56; };
    struct { char igi2_o18[60]; float v57; };
    struct { char igi2_o19[64]; float v58; };
    struct { char igi2_o20[68]; float v59; };
    struct { char igi2_o21[72]; float v60; };
    struct { char igi2_o22[76]; struct real64x3_t tTempStart2; };
    struct { char igi2_o23[100]; struct real64x3_t tTempStart1; };
    struct { char igi2_o24[124]; struct real32x9_t tMatrix; };
    struct { char igi2_o25[164]; struct real64x3_t tTempStart0; };
    struct { char igi2_o26[188]; struct real64x3_t tTempEnd0; };
    struct { char igi2_o27[212]; struct real64x3_t tTempEnd2; };
    struct { char igi2_o28[236]; struct real64x3_t tTempEnd1; };
    char igi2_extent[264];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  long double v9; // st7
  double v10; // st7
  double v11; // st7
  double v12; // st6
  double v13; // st5
  double vZ; // st5
  double v15; // st5
  double v16; // st4
  double v17; // st4
  double v18; // st6
  double v19; // st5
  double vY; // st5
  double v21; // st5
  double v22; // st4
  double v23; // st4
  double v24; // st3
  double v25; // st3
  double v26; // st3
  double v27; // st7
  struct real32x3_t *p_tNormal; // esi
  long double vX; // st7
  long double v30; // st6
  double v31; // st6
  double v32; // st4
  double v33; // st4
  double v34; // st4
  bool v35; // bp
  bool v36; // bp
  int v37; // ebp
  int result; // eax
  struct real32x3_t struct_real32x3_t; // 0:^20.12

  ptHole->nType = nBulletHoleType;
  ptHole->ptTexInfo = ptTexInfo;
  ptHole->vRadius = vRadius;
  ptHole->tCenterPos = ptIntersection->tLocalPos;
  ptHole->tNormal = ptIntersection->tLocalNormal;
  if ( ptHole->tNormal.vX != 0.0 || ptHole->tNormal.vY != 0.0 || ptHole->tNormal.vZ != 0.0 )
  {
    v9 = 1.0
       / sqrt(
           ptHole->tNormal.vX * ptHole->tNormal.vX
         + ptHole->tNormal.vY * ptHole->tNormal.vY
         + ptHole->tNormal.vZ * ptHole->tNormal.vZ);
    ptHole->tNormal.vX = ptHole->tNormal.vX * v9;
    ptHole->tNormal.vY = ptHole->tNormal.vY * v9;
    ptHole->tNormal.vZ = ptHole->tNormal.vZ * v9;
  }
  v10 = -vRadius;
  ptHole->tPos0.vX = vRadius;
  ptHole->tPos0.vY = v10;
  ptHole->tPos1.vX = v10;
  ptHole->tPos1.vY = v10;
  ptHole->tPos0.vZ = 12.288000106811523;
  igi2_frame.v50 = v10;
  ptHole->tPos1.vZ = 12.288000106811523;
  ptHole->tPos3.vX = v10;
  ptHole->tPos2.vY = vRadius;
  ptHole->tPos2.vZ = 12.288000106811523;
  ptHole->tPos3.vZ = 12.288000106811523;
  ptHole->tPos2.vX = vRadius;
  ptHole->tPos3.vY = vRadius;
  Real32x9_FromReal32x3(&igi2_frame.tMatrix, &ptIntersection->tLocalNormal);
  v11 = igi2_frame.tMatrix.tX.vZ * 12.288000106811523;
  v12 = igi2_frame.v50 * igi2_frame.tMatrix.tX.vY;
  v13 = igi2_frame.tMatrix.tX.vX * vRadius;
  igi2_frame.v60 = v13;
  igi2_frame.Real32x3_Rotate_tTemp = v13 + v12 + v11;
  vZ = igi2_frame.tMatrix.tY.vZ;
  ptHole->tPos0.vX = igi2_frame.Real32x3_Rotate_tTemp;
  igi2_frame.v55 = vZ * 12.288000106811523;
  v15 = igi2_frame.v50 * igi2_frame.tMatrix.tY.vY;
  v16 = igi2_frame.tMatrix.tY.vX * vRadius;
  igi2_frame.v51 = v16;
  igi2_frame.Real32x3_Rotate_tTemp_4a = v16 + v15 + igi2_frame.v55;
  v17 = igi2_frame.tMatrix.tZ.vZ;
  ptHole->tPos0.vY = igi2_frame.Real32x3_Rotate_tTemp_4a;
  igi2_frame.v54 = v17 * 12.288000106811523;
  igi2_frame.v59 = igi2_frame.v50 * igi2_frame.tMatrix.tZ.vY;
  igi2_frame.v57 = igi2_frame.tMatrix.tZ.vX * vRadius;
  igi2_frame.Real32x3_Rotate_tTemp_8a = igi2_frame.v59 + igi2_frame.v57 + igi2_frame.v54;
  ptHole->tPos0.vZ = igi2_frame.Real32x3_Rotate_tTemp_8a;
  igi2_frame.v58 = igi2_frame.v50 * igi2_frame.tMatrix.tX.vX;
  igi2_frame.Real32x3_Rotate_tTempa = v12 + igi2_frame.v58 + v11;
  igi2_frame.v56 = igi2_frame.v50 * igi2_frame.tMatrix.tY.vX;
  igi2_frame.Real32x3_Rotate_tTemp_4b = v15 + igi2_frame.v56 + igi2_frame.v55;
  v18 = igi2_frame.v50 * igi2_frame.tMatrix.tZ.vX;
  v19 = igi2_frame.v59 + v18;
  ptHole->tPos1.vX = igi2_frame.Real32x3_Rotate_tTempa;
  ptHole->tPos1.vY = igi2_frame.Real32x3_Rotate_tTemp_4b;
  igi2_frame.Real32x3_Rotate_tTemp_8b = v19 + igi2_frame.v54;
  vY = igi2_frame.tMatrix.tX.vY;
  ptHole->tPos1.vZ = igi2_frame.Real32x3_Rotate_tTemp_8b;
  v21 = vY * vRadius + v11;
  igi2_frame.Real32x3_Rotate_tTempb = igi2_frame.v60 + v21;
  v22 = igi2_frame.tMatrix.tY.vY;
  ptHole->tPos2.vX = igi2_frame.Real32x3_Rotate_tTempb;
  v23 = v22 * vRadius + igi2_frame.v55;
  igi2_frame.Real32x3_Rotate_tTemp_4c = igi2_frame.v51 + v23;
  v24 = igi2_frame.tMatrix.tZ.vY;
  ptHole->tPos2.vY = igi2_frame.Real32x3_Rotate_tTemp_4c;
  v25 = v24 * vRadius + igi2_frame.v54;
  igi2_frame.v52 = v25;
  igi2_frame.Real32x3_Rotate_tTemp_8c = v25 + igi2_frame.v57;
  v26 = igi2_frame.v58;
  ptHole->tPos2.vZ = igi2_frame.Real32x3_Rotate_tTemp_8c;
  struct_real32x3_t.vX = v26 + v21;
  struct_real32x3_t.vY = igi2_frame.v56 + v23;
  struct_real32x3_t.vZ = v18 + igi2_frame.v52;
  ptHole->tPos3 = struct_real32x3_t;
  ptHole->tPos0.vX = ptHole->tPos0.vX + ptIntersection->tLocalPos.vX;
  ptHole->tPos0.vY = ptIntersection->tLocalPos.vY + ptHole->tPos0.vY;
  ptHole->tPos0.vZ = ptHole->tPos0.vZ + ptIntersection->tLocalPos.vZ;
  ptHole->tPos1.vX = ptIntersection->tLocalPos.vX + ptHole->tPos1.vX;
  ptHole->tPos1.vY = ptHole->tPos1.vY + ptIntersection->tLocalPos.vY;
  ptHole->tPos1.vZ = ptIntersection->tLocalPos.vZ + ptHole->tPos1.vZ;
  ptHole->tPos2.vX = ptHole->tPos2.vX + ptIntersection->tLocalPos.vX;
  ptHole->tPos2.vY = ptIntersection->tLocalPos.vY + ptHole->tPos2.vY;
  v27 = ptHole->tPos2.vZ + ptIntersection->tLocalPos.vZ;
  p_tNormal = &ptIntersection->tNormal;
  ptHole->tPos2.vZ = v27;
  ptHole->tPos3.vX = p_tNormal[-2].vX + ptHole->tPos3.vX;
  ptHole->tPos3.vY = ptHole->tPos3.vY + p_tNormal[-2].vY;
  ptHole->tPos3.vZ = p_tNormal[-2].vZ + ptHole->tPos3.vZ;
  ptHole->tLight.vX = p_tNormal[4].vZ * 0.5;
  ptHole->tLight.vY = p_tNormal[4].vZ * 0.5;
  ptHole->tLight.vZ = p_tNormal[4].vZ * 0.5;
  ptBulletHole->isChanged = 1;
  vX = p_tNormal->vX;
  igi2_frame.Real32x3_Rotate_tTemp_8 = p_tNormal->vZ;
  igi2_frame.Real32x3_Rotate_tTemp_4 = p_tNormal->vY;
  if ( vX != 0.0 || igi2_frame.Real32x3_Rotate_tTemp_4 != 0.0 || igi2_frame.Real32x3_Rotate_tTemp_8 != 0.0 )
  {
    v30 = 24.576000213623047
        / sqrt(
            vX * vX
          + igi2_frame.Real32x3_Rotate_tTemp_4 * igi2_frame.Real32x3_Rotate_tTemp_4
          + igi2_frame.Real32x3_Rotate_tTemp_8 * igi2_frame.Real32x3_Rotate_tTemp_8);
    vX = p_tNormal->vX * v30;
    igi2_frame.Real32x3_Rotate_tTemp_4 = igi2_frame.Real32x3_Rotate_tTemp_4 * v30;
    igi2_frame.Real32x3_Rotate_tTemp_8 = igi2_frame.Real32x3_Rotate_tTemp_8 * v30;
  }
  v31 = ptHole->tPos0.vX;
  igi2_frame.tTempStart0.vY = ptHole->tPos0.vY;
  igi2_frame.tTempStart0.vZ = ptHole->tPos0.vZ;
  igi2_frame.tTempStart3.vX = ptOrientation->tX.vY * igi2_frame.tTempStart0.vY
                 + ptOrientation->tX.vZ * igi2_frame.tTempStart0.vZ
                 + ptOrientation->tX.vX * v31;
  igi2_frame.tTempStart3.vY = ptOrientation->tY.vY * igi2_frame.tTempStart0.vY
                 + ptOrientation->tY.vZ * igi2_frame.tTempStart0.vZ
                 + ptOrientation->tY.vX * v31;
  igi2_frame.tTempStart3.vZ = ptOrientation->tZ.vZ * igi2_frame.tTempStart0.vZ
                 + ptOrientation->tZ.vX * v31
                 + ptOrientation->tZ.vY * igi2_frame.tTempStart0.vY;
  qmemcpy(&igi2_frame.tTempStart0, &igi2_frame.tTempStart3, sizeof(igi2_frame.tTempStart0));
  igi2_frame.tTempStart0.vX = igi2_frame.tTempStart3.vX + ptPos->vX;
  igi2_frame.tTempStart0.vY = igi2_frame.tTempStart0.vY + ptPos->vY;
  igi2_frame.tTempStart0.vZ = igi2_frame.tTempStart0.vZ + ptPos->vZ;
  v32 = ptHole->tPos1.vX;
  igi2_frame.tTempStart1.vY = ptHole->tPos1.vY;
  igi2_frame.tTempStart1.vZ = ptHole->tPos1.vZ;
  igi2_frame.tTempStart3.vX = ptOrientation->tX.vY * igi2_frame.tTempStart1.vY
                 + ptOrientation->tX.vZ * igi2_frame.tTempStart1.vZ
                 + ptOrientation->tX.vX * v32;
  igi2_frame.tTempStart3.vY = ptOrientation->tY.vY * igi2_frame.tTempStart1.vY
                 + ptOrientation->tY.vZ * igi2_frame.tTempStart1.vZ
                 + ptOrientation->tY.vX * v32;
  igi2_frame.tTempStart3.vZ = ptOrientation->tZ.vZ * igi2_frame.tTempStart1.vZ
                 + ptOrientation->tZ.vX * v32
                 + ptOrientation->tZ.vY * igi2_frame.tTempStart1.vY;
  qmemcpy(&igi2_frame.tTempStart1, &igi2_frame.tTempStart3, sizeof(igi2_frame.tTempStart1));
  igi2_frame.tTempStart1.vX = igi2_frame.tTempStart3.vX + ptPos->vX;
  igi2_frame.tTempStart1.vY = igi2_frame.tTempStart1.vY + ptPos->vY;
  igi2_frame.tTempStart1.vZ = igi2_frame.tTempStart1.vZ + ptPos->vZ;
  v33 = ptHole->tPos2.vX;
  igi2_frame.tTempStart2.vY = ptHole->tPos2.vY;
  igi2_frame.tTempStart2.vZ = ptHole->tPos2.vZ;
  igi2_frame.tTempStart3.vX = ptOrientation->tX.vY * igi2_frame.tTempStart2.vY
                 + ptOrientation->tX.vZ * igi2_frame.tTempStart2.vZ
                 + ptOrientation->tX.vX * v33;
  igi2_frame.tTempStart3.vY = ptOrientation->tY.vY * igi2_frame.tTempStart2.vY
                 + ptOrientation->tY.vZ * igi2_frame.tTempStart2.vZ
                 + ptOrientation->tY.vX * v33;
  igi2_frame.tTempStart3.vZ = ptOrientation->tZ.vZ * igi2_frame.tTempStart2.vZ
                 + ptOrientation->tZ.vX * v33
                 + ptOrientation->tZ.vY * igi2_frame.tTempStart2.vY;
  qmemcpy(&igi2_frame.tTempStart2, &igi2_frame.tTempStart3, sizeof(igi2_frame.tTempStart2));
  igi2_frame.tTempStart2.vX = igi2_frame.tTempStart3.vX + ptPos->vX;
  igi2_frame.tTempStart2.vY = igi2_frame.tTempStart2.vY + ptPos->vY;
  igi2_frame.tTempStart2.vZ = igi2_frame.tTempStart2.vZ + ptPos->vZ;
  v34 = ptHole->tPos3.vX;
  igi2_frame.tTempStart3.vY = ptHole->tPos3.vY;
  igi2_frame.tTempStart3.vZ = ptHole->tPos3.vZ;
  igi2_frame.tTempEnd0.vX = ptOrientation->tX.vZ * igi2_frame.tTempStart3.vZ
               + ptOrientation->tX.vX * v34
               + ptOrientation->tX.vY * igi2_frame.tTempStart3.vY;
  igi2_frame.tTempEnd0.vY = ptOrientation->tY.vZ * igi2_frame.tTempStart3.vZ
               + ptOrientation->tY.vX * v34
               + ptOrientation->tY.vY * igi2_frame.tTempStart3.vY;
  igi2_frame.tTempEnd0.vZ = ptOrientation->tZ.vX * v34
               + ptOrientation->tZ.vY * igi2_frame.tTempStart3.vY
               + ptOrientation->tZ.vZ * igi2_frame.tTempStart3.vZ;
  qmemcpy(&igi2_frame.tTempStart3, &igi2_frame.tTempEnd0, sizeof(igi2_frame.tTempStart3));
  igi2_frame.tTempStart3.vX = igi2_frame.tTempEnd0.vX + ptPos->vX;
  igi2_frame.tTempStart3.vY = igi2_frame.tTempStart3.vY + ptPos->vY;
  igi2_frame.tTempStart3.vZ = igi2_frame.tTempStart3.vZ + ptPos->vZ;
  igi2_frame.tTempEnd0.vX = igi2_frame.tTempStart0.vX - vX;
  igi2_frame.tTempEnd0.vY = igi2_frame.tTempStart0.vY - igi2_frame.Real32x3_Rotate_tTemp_4;
  igi2_frame.tTempEnd0.vZ = igi2_frame.tTempStart0.vZ - igi2_frame.Real32x3_Rotate_tTemp_8;
  igi2_frame.tTempEnd1.vX = igi2_frame.tTempStart1.vX - vX;
  igi2_frame.tTempEnd1.vY = igi2_frame.tTempStart1.vY - igi2_frame.Real32x3_Rotate_tTemp_4;
  igi2_frame.tTempEnd1.vZ = igi2_frame.tTempStart1.vZ - igi2_frame.Real32x3_Rotate_tTemp_8;
  igi2_frame.tTempEnd2.vX = igi2_frame.tTempStart2.vX - vX;
  igi2_frame.tTempEnd2.vY = igi2_frame.tTempStart2.vY - igi2_frame.Real32x3_Rotate_tTemp_4;
  igi2_frame.tTempEnd2.vZ = igi2_frame.tTempStart2.vZ - igi2_frame.Real32x3_Rotate_tTemp_8;
  *(double *)&igi2_frame.tMatrix.tX.vX = igi2_frame.tTempStart3.vX - vX;
  *(double *)&igi2_frame.tMatrix.tX.vZ = igi2_frame.tTempStart3.vY - igi2_frame.Real32x3_Rotate_tTemp_4;
  *(double *)&igi2_frame.tMatrix.tY.vY = igi2_frame.tTempStart3.vZ - igi2_frame.Real32x3_Rotate_tTemp_8;
  v35 = World_LineOfSight(
          World_ptActiveWorld,
          &igi2_frame.tTempStart0,
          &igi2_frame.tTempEnd0,
          512,
          nullptr,
          0xFFFFFFFF,
          WORLD_DYNCUBETREE_CATEGORY_ALL,
          nullptr) == 0;
  v36 = World_LineOfSight(
          World_ptActiveWorld,
          &igi2_frame.tTempStart1,
          &igi2_frame.tTempEnd1,
          512,
          nullptr,
          0xFFFFFFFF,
          WORLD_DYNCUBETREE_CATEGORY_ALL,
          nullptr) == 0
     && v35;
  v37 = World_LineOfSight(
          World_ptActiveWorld,
          &igi2_frame.tTempStart2,
          &igi2_frame.tTempEnd2,
          512,
          nullptr,
          0xFFFFFFFF,
          WORLD_DYNCUBETREE_CATEGORY_ALL,
          nullptr) == 0
     && v36;
  result = World_LineOfSight(
             World_ptActiveWorld,
             &igi2_frame.tTempStart3,
             (struct real64x3_t *)&igi2_frame.tMatrix,
             512,
             nullptr,
             0xFFFFFFFF,
             WORLD_DYNCUBETREE_CATEGORY_ALL,
             nullptr) == 0;
  if ( (result & v37) == 0 )
    ptHole->nType = -1;
  return result;
}

// source: j/0/objects/bullethole.c:389  [anchor-caller]
void __cdecl BulletHole_CreateBulletHoleGoddammit(
        struct QTask_s *ptParent,
        void *pxContext,
        struct real64x3_t *ptPos,
        struct real32x9_t *ptOrientation)
{
  struct QIntersection_s *v4; // edx
  struct QObjectVector_s *v5; // esi
  signed int nAllocated; // eax
  signed int v7; // ecx
  void **v8; // edi
  struct BulletHole_s *v9; // esi
  struct QTask_s ***papxElement; // esi
  struct QTask_s *v11; // edi
  unsigned int v12; // edx
  int v13; // ebx
  struct QTask_s *v14; // eax
  struct QTask_s *v15; // eax
  struct QVector_s *v16; // ebx
  unsigned int nElements; // esi
  struct QTask_s *v18; // edi
  void **v19; // eax
  struct QObjectVector_s *v20; // ebx
  unsigned int *p_nAllocated; // esi
  struct QTask_s **v22; // ecx
  struct Game_s *v23; // ecx
  struct QTask_s *ptWorld; // esi
  struct QTask_s *v25; // ebx
  DWORD PerformanceCounter; // eax
  int nNewest; // edi
  int v28; // ecx
  double v29; // st7
  double v30; // st6
  double v31; // st5
  long double v32; // st7
  long double v33; // st7
  int v34; // edi
  int p_vZ; // ecx
  double v36; // st7
  double v37; // st6
  double v38; // st5
  long double v39; // st7
  long double v40; // st7
  int nHoles; // eax
  int nOldest; // eax
  int v43; // ecx
  int v44; // eax
  struct Hole_t *v45; // ebx
  struct BulletHole_s *ptBulletHole; // [esp+Ch] [ebp-Ch]
  float ptBulletHolea; // [esp+Ch] [ebp-Ch]
  float ptBulletHoleb; // [esp+Ch] [ebp-Ch]
  unsigned int v49; // [esp+10h] [ebp-8h]
  struct QIntersection_s *ptIntersection; // [esp+14h] [ebp-4h]

  v4 = *(struct QIntersection_s **)pxContext;
  v5 = BulletHole_tBulletHolePool;
  nAllocated = BulletHole_tBulletHolePool->nAllocated;
  v7 = 0;
  ptIntersection = *(struct QIntersection_s **)pxContext;
  if ( nAllocated <= 0 )
  {
LABEL_6:
    if ( nAllocated == 100 )
    {
      papxElement = (struct QTask_s ***)v5->papxElement;
      v11 = nullptr;
      v12 = -1;
      v13 = 100;
      do
      {
        v14 = **papxElement;
        if ( v14[1481].ptParent <= (struct QTask_s *)v12 )
        {
          v11 = **papxElement;
          v12 = (unsigned int)v14[1481].ptParent;
        }
        ++papxElement;
        --v13;
      }
      while ( v13 );
      QTask_Delete(v11);
    }
    v15 = QTask_NewFn(ptParent, BulletHole_eQTaskType, nullptr);
    v16 = BulletHole_ptTasks;
    nElements = BulletHole_ptTasks->tPrivate.nElements;
    v18 = v15;
    ptBulletHole = (struct BulletHole_s *)v15;
    v49 = BulletHole_ptTasks->tPrivate.nElements;
    if ( BulletHole_ptTasks->tPrivate.nElements == BulletHole_ptTasks->tPrivate.nArraySize )
    {
      QVector_Realloc(BulletHole_ptTasks, 1u);
      nElements = v49;
    }
    if ( nElements < v16->tPrivate.nElements - 1 )
      memmove(
        &v16->tPrivate.papxElement[nElements + 1],
        &v16->tPrivate.papxElement[nElements],
        4 * (v16->tPrivate.nElements - nElements));
    v19 = v16->tPrivate.papxElement;
    ++v16->tPrivate.nElements;
    v20 = BulletHole_tBulletHolePool;
    v19[nElements] = v18;
    p_nAllocated = &v20->nAllocated;
    if ( v20->nAllocated == v20->nSize )
      QObjectVector_Realloc(v20, v20->nReallocSize);
    v22 = (struct QTask_s **)v20->papxElement[(*p_nAllocated)++];
    v18[1481].tQTaskRefList.ptHead = (struct QReference_s *)v22;
    *v22 = v18;
    v23 = Game_ptGame;
    v18[1481].tQTaskChildren.ptTail = ptParent;
    ptWorld = (struct QTask_s *)v23->ptWorld;
    v25 = QTask_NewFn(v18, PolyListDynCubeObj_eQTaskType, nullptr);
    *(_DWORD *)&v25[2].eQTaskType = ptBulletHole->atPoly;
    v25[2].ptParent = ptWorld;
    v25[4].ptPrev = nullptr;
    v25[4].tQTaskChildren.ptHead = (struct QTask_s *)0x200000;
    v25[4].tQTaskChildren.ptTail = nullptr;
    v25[4].tQTaskChildren.ptMiddle = nullptr;
    v25[4].tQTaskRefList.ptHead = (struct QReference_s *)1;
    v25[4].tQTaskRefList.ptTail = nullptr;
    v25[4].tQTaskRefList.ptMiddle = nullptr;
    v25[4].ptNext = nullptr;
    v25[4].ptParent = (struct QTask_s *)1;
    *(_DWORD *)&v25[4].eQTaskType = QTask_NewQTaskRef(&ptBulletHole->tQTask);
    qmemcpy(&v25[1], ptPos, 0x18u);
    qmemcpy(&v25[3], ptOrientation, sizeof(struct QTask_s));
    ptBulletHole->ptPolyListDynCubeObj = (struct PolyListDynCubeObj_t *)v25;
    v25[4].ptNext = (struct QTask_s *)2;
    ptBulletHole->nNewest = 0;
    ptBulletHole->nOldest = 0;
    ptBulletHole->nHoles = 1;
    BulletHole_AddItem(
      ptPos,
      ptOrientation,
      ptBulletHole,
      ptBulletHole->atHole,
      ptIntersection,
      0,
      *((struct TexInfo_s **)pxContext + 2),
      *((float *)pxContext + 3));
    if ( Timer_isPerformanceCounter )
      PerformanceCounter = Timer_GetPerformanceCounter();
    else
      PerformanceCounter = GetTickCount();
    ptBulletHole->nTimeStamp = PerformanceCounter - Timer_nStartTime;
  }
  else
  {
    v8 = BulletHole_tBulletHolePool->papxElement;
    while ( 1 )
    {
      v9 = *(struct BulletHole_s **)*v8;
      if ( v9->ptParent == ptParent )
        break;
      ++v7;
      ++v8;
      if ( v7 >= nAllocated )
      {
        v5 = BulletHole_tBulletHolePool;
        goto LABEL_6;
      }
    }
    nNewest = v9->nNewest;
    if ( nNewest < 0 )
    {
LABEL_34:
      v34 = v9->nHoles - 1;
      if ( v34 <= v9->nNewest )
      {
LABEL_48:
        nHoles = v9->nHoles;
        if ( nHoles == 200 )
        {
          nOldest = v9->nOldest;
          v43 = nOldest;
          v9->nNewest = nOldest;
          v44 = nOldest + 1;
          v45 = &v9->atHole[v43];
          v9->nOldest = v44;
          if ( v44 >= 200 )
            v44 -= 200;
          v9->nOldest = v44;
        }
        else
        {
          v9->nNewest = nHoles;
          v45 = &v9->atHole[nHoles];
          v9->nHoles = nHoles + 1;
        }
        BulletHole_AddItem(
          ptPos,
          ptOrientation,
          v9,
          v45,
          v4,
          0,
          *((struct TexInfo_s **)pxContext + 2),
          *((float *)pxContext + 3));
        if ( Timer_isPerformanceCounter )
          v9->nTimeStamp = Timer_GetPerformanceCounter() - Timer_nStartTime;
        else
          v9->nTimeStamp = GetTickCount() - Timer_nStartTime;
      }
      else
      {
        p_vZ = (int)&v9->atHole[v34].tNormal.vZ;
        while ( 1 )
        {
          if ( *(_DWORD *)(p_vZ + 76) != -1 )
          {
            v36 = *(float *)(p_vZ + 12) - v4->tLocalPos.vZ;
            v37 = *(float *)(p_vZ + 8) - v4->tLocalPos.vY;
            v38 = *(float *)(p_vZ + 4) - v4->tLocalPos.vX;
            ptBulletHoleb = *(float *)(p_vZ + 84) * 1.5;
            if ( ptBulletHoleb * ptBulletHoleb > v38 * v38 + v37 * v37 + v36 * v36 )
            {
              if ( v4->tLocalNormal.vX != 0.0 || v4->tLocalNormal.vY != 0.0 || v4->tLocalNormal.vZ != 0.0 )
              {
                v39 = 1.0
                    / sqrt(
                        v4->tLocalNormal.vX * v4->tLocalNormal.vX
                      + v4->tLocalNormal.vY * v4->tLocalNormal.vY
                      + v4->tLocalNormal.vZ * v4->tLocalNormal.vZ);
                v4->tLocalNormal.vX = v4->tLocalNormal.vX * v39;
                v4->tLocalNormal.vY = v4->tLocalNormal.vY * v39;
                v4->tLocalNormal.vZ = v4->tLocalNormal.vZ * v39;
              }
              if ( *(float *)(p_vZ - 8) != 0.0 || *(float *)(p_vZ - 4) != 0.0 || *(float *)p_vZ != 0.0 )
              {
                v40 = 1.0
                    / sqrt(
                        *(float *)(p_vZ - 8) * *(float *)(p_vZ - 8)
                      + *(float *)(p_vZ - 4) * *(float *)(p_vZ - 4)
                      + *(float *)p_vZ * *(float *)p_vZ);
                *(float *)(p_vZ - 8) = *(float *)(p_vZ - 8) * v40;
                *(float *)(p_vZ - 4) = *(float *)(p_vZ - 4) * v40;
                *(float *)p_vZ = *(float *)p_vZ * v40;
              }
              if ( v4->tLocalNormal.vY * *(float *)(p_vZ - 4)
                 + v4->tLocalNormal.vZ * *(float *)p_vZ
                 + v4->tLocalNormal.vX * *(float *)(p_vZ - 8) > 0.8999999761581421 )
                break;
            }
          }
          --v34;
          p_vZ -= 96;
          if ( v34 <= v9->nNewest )
            goto LABEL_48;
        }
      }
    }
    else
    {
      v28 = (int)&v9->atHole[nNewest].tNormal.vZ;
      while ( 1 )
      {
        if ( *(_DWORD *)(v28 + 76) != -1 )
        {
          v29 = *(float *)(v28 + 12) - v4->tLocalPos.vZ;
          v30 = *(float *)(v28 + 8) - v4->tLocalPos.vY;
          v31 = *(float *)(v28 + 4) - v4->tLocalPos.vX;
          ptBulletHolea = *(float *)(v28 + 84) * 1.5;
          if ( ptBulletHolea * ptBulletHolea > v31 * v31 + v30 * v30 + v29 * v29 )
          {
            if ( v4->tLocalNormal.vX != 0.0 || v4->tLocalNormal.vY != 0.0 || v4->tLocalNormal.vZ != 0.0 )
            {
              v32 = 1.0
                  / sqrt(
                      v4->tLocalNormal.vX * v4->tLocalNormal.vX
                    + v4->tLocalNormal.vY * v4->tLocalNormal.vY
                    + v4->tLocalNormal.vZ * v4->tLocalNormal.vZ);
              v4->tLocalNormal.vX = v4->tLocalNormal.vX * v32;
              v4->tLocalNormal.vY = v4->tLocalNormal.vY * v32;
              v4->tLocalNormal.vZ = v4->tLocalNormal.vZ * v32;
            }
            if ( *(float *)(v28 - 8) != 0.0 || *(float *)(v28 - 4) != 0.0 || *(float *)v28 != 0.0 )
            {
              v33 = 1.0
                  / sqrt(
                      *(float *)(v28 - 8) * *(float *)(v28 - 8)
                    + *(float *)(v28 - 4) * *(float *)(v28 - 4)
                    + *(float *)v28 * *(float *)v28);
              *(float *)(v28 - 8) = *(float *)(v28 - 8) * v33;
              *(float *)(v28 - 4) = *(float *)(v28 - 4) * v33;
              *(float *)v28 = *(float *)v28 * v33;
            }
            if ( v4->tLocalNormal.vX * *(float *)(v28 - 8)
               + v4->tLocalNormal.vY * *(float *)(v28 - 4)
               + *(float *)v28 * v4->tLocalNormal.vZ > 0.8999999761581421 )
              break;
          }
        }
        --nNewest;
        v28 -= 96;
        if ( nNewest < 0 )
          goto LABEL_34;
      }
    }
  }
}

// source: j/0/objects/bullethole.c:592  [anchor-mhash]
void __cdecl RigidDynCubeObj_CreateBulletHoleHandler(struct QTask_s *ptQTask, void *pxContext)
{
  BulletHole_CreateBulletHoleGoddammit(
    ptQTask,
    pxContext,
    (struct real64x3_t *)&ptQTask[1],
    (struct real32x9_t *)&ptQTask[3].ptPrev);
}

// source: j/0/objects/bullethole.c:605  [anchor-mhash]
void __cdecl BoneDynCubeObj_CreateBulletHoleHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QIntersection_s *v2; // ecx
  struct BoneDynCubeObj_CreateBruiseContext_s tCreateBruiseContext; // [esp+0h] [ebp-4h] BYREF

  tCreateBruiseContext.ptIntersection = v2;
  if ( Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.isBlood )
  {
    tCreateBruiseContext.ptIntersection = *(struct QIntersection_s **)pxContext;
    RenderMode_tActiveRenderMode.apfRenderModeMethod[BoneDynCubeObj_eCreateBruiseRenderModeMethode](&tCreateBruiseContext);
  }
}

// source: j/0/objects/bullethole.c:630  [anchor-mhash]
void __cdecl SplineObjSegment_CreateBulletHoleHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct real32x9_t tOrientation; // [esp+0h] [ebp-28h] BYREF

  tOrientation.tX.vX = 1.0;
  memset(&tOrientation.tX.vY, 0, 12);
  tOrientation.tY.vY = 1.0;
  memset(&tOrientation.tY.vZ, 0, 12);
  tOrientation.tZ.vZ = 1.0;
  tOrientation.nOps = 0;
  BulletHole_CreateBulletHoleGoddammit(ptQTask, pxContext, (struct real64x3_t *)&ptQTask[1], &tOrientation);
}

// source: j/0/objects/bullethole.c:647  [size]
// attributes: thunk
void __cdecl BulletHole_ChangeModelHandler(struct QTask_s *ptQTask)
{
  QTask_Delete(ptQTask);
}

// source: j/0/objects/bullethole.c:663  [anchor-hash]
void __cdecl BulletHole_DeleteAll()
{
  struct QVector_s *v0; // ecx
  unsigned int i; // eax

  v0 = BulletHole_ptTasks;
  for ( i = BulletHole_ptTasks->tPrivate.nElements;
        BulletHole_ptTasks->tPrivate.nElements;
        i = BulletHole_ptTasks->tPrivate.nElements )
  {
    QTask_Delete((struct QTask_s *)v0->tPrivate.papxElement[i - 1]);
    v0 = BulletHole_ptTasks;
  }
}

// source: j/0/objects/bullethole.c:679  [anchor-strings]
void __cdecl BulletHole_Open()
{
  __int16 v0; // si
  unsigned __int16 BaseQTaskType; // ax
  unsigned __int16 v2; // si
  struct QObjectVector_s *v3; // esi
  void **v4; // esi
  struct QVector_s *v5; // eax

  v0 = QTask_NewQTaskEventFn(0, "CreateBulletHole");
  BulletHole_eCreateBulletHoleTaskEvent = v0;
  QTask_LinkQTaskEventHandlerFn(RigidDynCubeObj_eQTaskType, v0, RigidDynCubeObj_CreateBulletHoleHandler);
  QTask_LinkQTaskEventHandlerFn(SplineObjSegment_eQTaskType, v0, SplineObjSegment_CreateBulletHoleHandler);
  QTask_LinkQTaskEventHandlerFn(BoneDynCubeObj_eQTaskType, v0, BoneDynCubeObj_CreateBulletHoleHandler);
  BaseQTaskType = QTask_GetBaseQTaskType();
  v2 = QTask_NewQTaskType("BulletHole", 59280, BaseQTaskType, 0, 0);
  BulletHole_eQTaskType = v2;
  QTask_LinkQTaskEventHandlerFn(v2, MagicObj_eMagicObjEnterEvent, BulletHole_MagicObjEnterHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v2, 2, BulletHole_DeleteHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v2, Mesh3D_eChangeModelQTaskEventNoContext, BulletHole_ChangeModelHandler);
  QTask_LinkQTaskEventHandlerFn(v2, SLOWORD(ShadowVolume_vIntensity), BulletHole_GetObjectBoundingSphereHandler);
  v3 = (struct QObjectVector_s *)Mem_AllocFn(52, 4);
  v3->isStrictOrder = true;
  v3->nSize = 0;
  v3->nAllocated = 0;
  v3->nReallocSize = 0;
  v3->papxElement = nullptr;
  v3->nElementSize = 8;
  v3->tMemPool.nBlocks = 0;
  v3->tMemPool.nAllocatedBlocks = 0;
  v3->tMemPool.nAlignment = 4;
  v3->tMemPool.nBlockSize = 8;
  v3->tMemPool.nReAllocBlocks = 0;
  v3->tMemPool.tMemPoolFreeList.ptHead = nullptr;
  v3->tMemPool.tMemPoolSegmentList.ptHead = nullptr;
  MemPool_ReAlloc(&v3->tMemPool, 0x64u);
  QObjectVector_Realloc(v3, 0x64u);
  BulletHole_tBulletHolePool = v3;
  v4 = (void **)Mem_AllocFn(256, 4);
  v5 = (struct QVector_s *)Mem_AllocFn(24, 4);
  v5->tPrivate.nElements = 0;
  v5->tPrivate.isPrivateMem = false;
  v5->tPrivate.isStrictOrder = false;
  v5->tPrivate.papxElement = v4;
  v5->tPrivate.nArraySize = 64;
  v5->tPrivate.nReallocSize = 64;
  BulletHole_ptTasks = v5;
}

// source: j/0/objects/bullethole.c:712  [size]
void __cdecl BulletHole_Close()
{
  QVector_Delete(BulletHole_ptTasks);
  QObjectVector_Delete(BulletHole_tBulletHolePool);
  QTask_DeleteQTaskType(BulletHole_eQTaskType);
  QTask_DeleteQTaskEvent(BulletHole_eCreateBulletHoleTaskEvent);
  BulletHole_eCreateBulletHoleTaskEvent = 512;
}

// source: j/0/objects/bullethole.c:729  [size]
__int16 __cdecl BulletHole_GetCreateBulletHoleTaskEvent()
{
  return BulletHole_eCreateBulletHoleTaskEvent;
}
