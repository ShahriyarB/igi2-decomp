/* j/0/effects/tracerbullet.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/effects/tracerbullet.c:122  [anchor-mhash]
void __cdecl Tracerbullet_InitRandomPolys(struct QTask_s *ptQTask)
{
  _DWORD *p_eQTaskType; // edi
  struct QTask_s **p_ptParent; // esi
  float *v3; // ebx
  float *p_vY; // ecx
  struct TracerbulletPoly_s *v5; // edx
  _DWORD *p_ptPrev; // eax

  p_eQTaskType = &ptQTask[6].eQTaskType;
  p_ptParent = &ptQTask[5].ptParent;
  v3 = &Tracerbullet_atTracerbulletPoly[0].avAlpha[1];
  p_vY = &Tracerbullet_atTracerbulletPoly[0].atMapPos[0].vY;
  v5 = Tracerbullet_atTracerbulletPoly;
  p_ptPrev = &ptQTask[5].ptPrev;
  do
  {
    *p_ptPrev = v5;
    p_ptPrev[3] = v5->atColor;
    *(p_ptParent - 1) = *((struct QTask_s **)p_vY - 1);
    *p_ptParent = *(struct QTask_s **)p_vY;
    p_ptPrev[12] = *((_DWORD *)v3 - 1);
    p_ptPrev[4] = &v5->atColor[1];
    p_ptPrev[1] = &v5->atPos[1];
    p_ptParent[1] = *((struct QTask_s **)p_vY + 1);
    p_ptParent[2] = *((struct QTask_s **)p_vY + 2);
    p_ptPrev[13] = *(_DWORD *)v3;
    p_ptPrev[5] = &v5->atColor[2];
    p_ptPrev[2] = &v5->atPos[2];
    p_ptParent[3] = *((struct QTask_s **)p_vY + 3);
    p_ptParent[4] = *((struct QTask_s **)p_vY + 4);
    p_ptPrev[14] = *((_DWORD *)v3 + 1);
    p_eQTaskType[1] = ptQTask[13].tQTaskChildren.ptHead;
    *p_eQTaskType = ptQTask[13].ptPrev;
    *(p_eQTaskType - 3) = 0;
    *(p_eQTaskType - 2) = 0;
    *(p_eQTaskType - 1) = 1065353216;
    p_vY += 30;
    ++v5;
    p_ptParent += 20;
    v3 += 30;
    p_ptPrev += 20;
    p_eQTaskType += 20;
  }
  while ( (int)p_vY < 7676112 );
}

// source: j/0/effects/tracerbullet.c:157  [anchor-mhash]
void __cdecl Tracerbullet_InitTracerbulletPolys()
{
  float *p_vY; // eax
  _DWORD *v1; // esi
  _DWORD *v2; // ecx
  float *v3; // edx
  int v4; // edi

  p_vY = &Tracerbullet_atTracerbulletPoly[0].tNormal.vY;
  do
  {
    v1 = p_vY + 8;
    v2 = p_vY + 3;
    v3 = p_vY - 10;
    v4 = 3;
    do
    {
      *v3 = 1.0;
      v3[1] = 1.0;
      v3[2] = 1.0;
      *(v2 - 1) = 0;
      *v2 = 0;
      *(p_vY - 1) = 0.0;
      *p_vY = 0.0;
      p_vY[1] = 1.0;
      *v1 = 1056964608;
      v3 += 3;
      v2 += 2;
      ++v1;
      --v4;
    }
    while ( v4 );
    p_vY += 30;
  }
  while ( (int)p_vY < 7676100 );
  Tracerbullet_atTracerbulletPoly[0].atMapPos[0].vX = 0.0;
  Tracerbullet_atTracerbulletPoly[0].atMapPos[0].vY = 0.0;
  Tracerbullet_atTracerbulletTexCoord[1].vX = 1.0;
  Tracerbullet_atTracerbulletPoly[0].atMapPos[1].vX = 1.0;
  Tracerbullet_atTracerbulletPoly[0].atMapPos[1].vY = 0.0;
  Tracerbullet_atTracerbulletPoly[0].atMapPos[2].vX = 0.0;
  Tracerbullet_atTracerbulletTexCoord[3].vY = 1.0;
  Tracerbullet_atTracerbulletPoly[0].atMapPos[2].vY = 1.0;
  Tracerbullet_atTracerbulletPoly[1].atPos[2].vX = 0.0;
  Tracerbullet_atTracerbulletVertex[2].vY = 61440.0;
  Tracerbullet_atTracerbulletPoly[1].atPos[2].vY = 61440.0;
  Tracerbullet_atTracerbulletVertex[2].vZ = 122.87999725341797;
  Tracerbullet_atTracerbulletPoly[1].atPos[2].vZ = 122.87999725341797;
  Tracerbullet_atTracerbulletPoly[1].atMapPos[0].vX = 0.0;
  Tracerbullet_atTracerbulletPoly[1].atMapPos[0].vY = 1.0;
  Tracerbullet_atTracerbulletPoly[1].atMapPos[1].vX = 1.0;
  Tracerbullet_atTracerbulletPoly[1].atMapPos[1].vY = 0.0;
  Tracerbullet_atTracerbulletTexCoord[2].vX = 1.0;
  Tracerbullet_atTracerbulletPoly[1].atMapPos[2].vX = 1.0;
  Tracerbullet_atTracerbulletTexCoord[2].vY = 1.0;
  Tracerbullet_atTracerbulletPoly[1].atMapPos[2].vY = 1.0;
  Tracerbullet_atTracerbulletTexCoord[0].vX = 0.0;
  Tracerbullet_atTracerbulletTexCoord[0].vY = 0.0;
  Tracerbullet_atTracerbulletTexCoord[1].vY = 0.0;
  Tracerbullet_atTracerbulletTexCoord[3].vX = 0.0;
  Tracerbullet_atTracerbulletVertex[0].vX = 0.0;
  Tracerbullet_atTracerbulletVertex[0].vY = 0.0;
  Tracerbullet_atTracerbulletVertex[0].vZ = 0.0;
  Tracerbullet_atTracerbulletVertex[1].vX = 0.0;
  Tracerbullet_atTracerbulletVertex[1].vY = 61440.0;
  Tracerbullet_atTracerbulletVertex[1].vZ = 0.0;
  Tracerbullet_atTracerbulletVertex[2].vX = 0.0;
  Tracerbullet_atTracerbulletVertex[3].vX = 0.0;
  Tracerbullet_atTracerbulletVertex[3].vY = 0.0;
  Tracerbullet_atTracerbulletVertex[3].vZ = 122.87999725341797;
  Tracerbullet_atTracerbulletPoly[0].atPos[0].vY = 0.0;
  Tracerbullet_atTracerbulletPoly[2].atPos[1].vX = 0.0;
  Tracerbullet_atTracerbulletPoly[2].atPos[1].vY = 0.0;
  Tracerbullet_atTracerbulletPoly[2].atPos[1].vZ = 0.0;
  Tracerbullet_atTracerbulletPoly[0].atPos[0].vX = 0.0;
  Tracerbullet_atTracerbulletPoly[0].atPos[0].vZ = 0.0;
  Tracerbullet_atTracerbulletPoly[0].atPos[1].vX = 0.0;
  Tracerbullet_atTracerbulletPoly[0].atPos[1].vY = 61440.0;
  Tracerbullet_atTracerbulletPoly[0].atPos[1].vZ = 0.0;
  Tracerbullet_atTracerbulletPoly[0].atPos[2].vX = 0.0;
  Tracerbullet_atTracerbulletPoly[0].atPos[2].vY = 0.0;
  Tracerbullet_atTracerbulletPoly[0].atPos[2].vZ = 122.87999725341797;
  Tracerbullet_atTracerbulletPoly[1].atPos[0].vX = 0.0;
  Tracerbullet_atTracerbulletPoly[1].atPos[0].vY = 0.0;
  Tracerbullet_atTracerbulletPoly[1].atPos[0].vZ = 122.87999725341797;
  Tracerbullet_atTracerbulletPoly[1].atPos[1].vX = 0.0;
  Tracerbullet_atTracerbulletPoly[1].atPos[1].vY = 61440.0;
  Tracerbullet_atTracerbulletPoly[1].atPos[1].vZ = 0.0;
  Tracerbullet_atTracerbulletPoly[2].atPos[0].vX = 0.0;
  Tracerbullet_atTracerbulletPoly[2].atPos[0].vY = 61440.0;
  Tracerbullet_atTracerbulletPoly[2].atPos[0].vZ = 0.0;
  Tracerbullet_atTracerbulletPoly[2].atPos[2].vX = 0.0;
  Tracerbullet_atTracerbulletPoly[2].atPos[2].vY = 0.0;
  Tracerbullet_atTracerbulletPoly[2].atPos[2].vZ = 122.87999725341797;
  Tracerbullet_atTracerbulletPoly[3].atPos[0].vY = 61440.0;
  Tracerbullet_atTracerbulletPoly[3].atPos[0].vZ = 0.0;
  Tracerbullet_atTracerbulletPoly[2].atMapPos[0].vX = 1.0;
  Tracerbullet_atTracerbulletPoly[3].atPos[2].vY = 61440.0;
  Tracerbullet_atTracerbulletPoly[3].atPos[2].vZ = 122.87999725341797;
  Tracerbullet_atTracerbulletPoly[2].atMapPos[0].vY = 0.0;
  Tracerbullet_atTracerbulletPoly[2].atMapPos[1].vX = 0.0;
  Tracerbullet_atTracerbulletPoly[2].atMapPos[1].vY = 0.0;
  Tracerbullet_atTracerbulletPoly[2].atMapPos[2].vX = 0.0;
  Tracerbullet_atTracerbulletPoly[3].atPos[0].vX = 0.0;
  Tracerbullet_atTracerbulletPoly[3].atPos[1].vY = 0.0;
  Tracerbullet_atTracerbulletPoly[3].atPos[2].vX = 0.0;
  Tracerbullet_atTracerbulletPoly[3].atPos[1].vX = 0.0;
  Tracerbullet_atTracerbulletPoly[2].atMapPos[2].vY = 1.0;
  Tracerbullet_atTracerbulletPoly[3].atMapPos[0].vX = 1.0;
  Tracerbullet_atTracerbulletPoly[3].atMapPos[0].vY = 0.0;
  Tracerbullet_atTracerbulletPoly[3].atMapPos[1].vY = 1.0;
  Tracerbullet_atTracerbulletPoly[3].atPos[1].vZ = 122.87999725341797;
  Tracerbullet_atTracerbulletPoly[3].atMapPos[1].vX = 0.0;
  Tracerbullet_atTracerbulletPoly[3].atMapPos[2].vX = 1.0;
  Tracerbullet_atTracerbulletPoly[3].atMapPos[2].vY = 1.0;
}

// source: j/0/effects/tracerbullet.c:240  [anchor-mhash]
void __cdecl Tracerbullet_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct Game_s *v2; // ecx
  struct World_s *ptWorld; // ecx
  struct DynCubeObj_s *ptManualRedrawList; // esi
  struct DynCubeObj_s *ptPrev; // edx

  memset(&ptQTask[1], 0, 0x48u);
  ptQTask[2].ptParent = (struct QTask_s *)1065353216;
  ptQTask[3].tQTaskChildren.ptHead = (struct QTask_s *)1065353216;
  ptQTask[3].tQTaskRefList.ptMiddle = (struct QReference_s *)1065353216;
  v2 = Game_ptGame;
  ptQTask[2].tQTaskRefList.ptTail = (struct QReference_s *)5;
  ptQTask[3].ptParent = nullptr;
  *(_DWORD *)&ptQTask[3].eQTaskType = 0;
  ptQTask[4].ptNext = nullptr;
  ptQTask[4].ptPrev = nullptr;
  ptQTask[4].tQTaskChildren.ptHead = nullptr;
  ptQTask[4].tQTaskChildren.ptMiddle = nullptr;
  *(_DWORD *)&ptQTask[2].eQTaskType = 0;
  ptQTask[3].ptNext = nullptr;
  ptQTask[3].ptPrev = nullptr;
  ptQTask[3].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[3].tQTaskChildren.ptTail = nullptr;
  ptQTask[3].tQTaskRefList.ptHead = nullptr;
  ptQTask[3].tQTaskRefList.ptTail = nullptr;
  ptQTask[4].tQTaskChildren.ptTail = nullptr;
  ptQTask[4].tQTaskRefList.ptHead = nullptr;
  ptQTask[4].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[4].tQTaskRefList.ptTail = nullptr;
  ptQTask[4].ptParent = nullptr;
  *(_DWORD *)&ptQTask[4].eQTaskType = 0;
  ptQTask[5].ptNext = nullptr;
  ptQTask[13].ptPrev = nullptr;
  ptQTask[13].tQTaskChildren.ptHead = nullptr;
  ptWorld = v2->ptWorld;
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

// source: j/0/effects/tracerbullet.c:269  [size]
void __cdecl Tracerbullet_DeleteHandler(struct QTask_s *ptQTask)
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

// source: j/0/effects/tracerbullet.c:285  [anchor-mhash]
void __cdecl Tracerbullet_RunHandler(struct QTask_s *ptQTask)
{
  double v1; // st7
  double v2; // st7

  v1 = *(float *)&ptQTask[4].tQTaskChildren.ptTail + *(double *)&ptQTask[3].ptParent;
  qmemcpy(&ptQTask[1], &ptQTask[3].ptParent, 0x18u);
  *(double *)&ptQTask[3].ptParent = v1;
  *(double *)&ptQTask[4].ptNext = *(float *)&ptQTask[4].tQTaskRefList.ptHead + *(double *)&ptQTask[4].ptNext;
  *(double *)&ptQTask[4].tQTaskChildren.ptHead = *(float *)&ptQTask[4].tQTaskRefList.ptMiddle
                                               + *(double *)&ptQTask[4].tQTaskChildren.ptHead;
  v2 = *(float *)&ptQTask[4].tQTaskRefList.ptTail + *(float *)&ptQTask[4].eQTaskType;
  *(_DWORD *)&ptQTask[1].eQTaskType = 1166016512;
  *(float *)&ptQTask[4].eQTaskType = v2;
  if ( v2 >= *(float *)&ptQTask[4].ptParent )
    QTask_Delete(ptQTask);
}

// source: j/0/effects/tracerbullet.c:314  [anchor-mhash]
void __cdecl Tracerbullet_EnterHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { float vScreenWidth; };
    struct { char igi2_o1[4]; float vScreenHeight; };
    struct { char igi2_o2[8]; float avReal32[2]; };
    struct { char igi2_o3[16]; struct real32x3_t tReal32x3; };
    struct { char igi2_o4[28]; struct real32x2_t atReal32x2[2]; };
    struct { char igi2_o5[44]; struct real64x3_t tReal64x3; };
    char igi2_extent[68];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  double v2; // st7
  double v3; // st6
  double v4; // st7
  BOOL v5; // ecx
  double vY; // st7
  float *p_vY; // ecx

  igi2_frame.vScreenHeight = RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vHeight;
  igi2_frame.vScreenWidth = RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vWidth;
  if ( *(float *)&ptQTask[4].eQTaskType >= 40960.0 )
  {
    qmemcpy(&igi2_frame.tReal64x3, &ptQTask[3].ptParent, sizeof(igi2_frame.tReal64x3));
    TransContext_ProjectWorldPos2(&TransContext_tActiveTransContext, igi2_frame.atReal32x2, igi2_frame.avReal32, &igi2_frame.tReal64x3);
    v2 = *(float *)&ptQTask[2].eQTaskType;
    LODWORD(igi2_frame.tReal32x3.vZ) = ptQTask[3].tQTaskRefList.ptHead;
    v3 = v2;
    v4 = *(float *)&ptQTask[3].tQTaskChildren.ptHead;
    igi2_frame.tReal32x3.vX = v3 * 61440.0;
    igi2_frame.tReal64x3.vX = igi2_frame.tReal32x3.vX + igi2_frame.tReal64x3.vX;
    igi2_frame.tReal64x3.vY = v4 * 61440.0 + igi2_frame.tReal64x3.vY;
    igi2_frame.tReal64x3.vZ = igi2_frame.tReal32x3.vZ * 61440.0 + igi2_frame.tReal64x3.vZ;
    TransContext_ProjectWorldPos2(&TransContext_tActiveTransContext, &igi2_frame.atReal32x2[1], &igi2_frame.avReal32[1], &igi2_frame.tReal64x3);
    if ( igi2_frame.avReal32[0] > 0.0 == igi2_frame.avReal32[1] > 0.0
      || (v5 = igi2_frame.avReal32[0] >= (double)igi2_frame.avReal32[1], igi2_frame.atReal32x2[v5].vX <= 0.0)
      || igi2_frame.atReal32x2[v5].vX >= (double)igi2_frame.vScreenWidth
      || (vY = igi2_frame.atReal32x2[v5].vY, p_vY = &igi2_frame.atReal32x2[v5].vY, vY <= 0.0)
      || *p_vY >= (double)igi2_frame.vScreenHeight )
    {
      qmemcpy(&ptQTask[5].ptNext[1], &ptQTask[3].ptParent, 0x18u);
      ((void (__cdecl *)(struct QTask_s *, _DWORD))QTask_aatQTaskFinalEvent[5][ptQTask[5].ptNext->eQTaskType].pfHandler)(
        ptQTask[5].ptNext,
        0);
    }
  }
}

// source: j/0/effects/tracerbullet.c:378  [size]
unsigned __int16 __cdecl Tracerbullet_GetQTaskType()
{
  return Tracerbullet_eQTaskType;
}

// source: j/0/effects/tracerbullet.c:391  [anchor-hash]
void __cdecl Tracerbullet_Open()
{
  unsigned __int16 v0; // si

  v0 = QTask_NewQTaskType("Tracerbullet", 536, DynCubeObj_eQTaskType, 0, 0);
  Tracerbullet_eQTaskType = v0;
  QTask_LinkQTaskEventHandlerFn(v0, 0, Tracerbullet_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 2, Tracerbullet_DeleteHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 1, Tracerbullet_RunHandler);
  QTask_LinkQTaskEventHandlerFn(v0, 5, Tracerbullet_EnterHandler);
  Tracerbullet_InitTracerbulletPolys();
}

// source: j/0/effects/tracerbullet.c:413  [size]
void __cdecl Tracerbullet_Close()
{
  QTask_DeleteQTaskType(Tracerbullet_eQTaskType);
}

// source: j/0/effects/tracerbullet.c:434  [anchor-mhash]
void __cdecl Tracerbullet_New(
        struct QTask_s *ptParent,
        struct TexInfo_s *ptTexInfo,
        struct PalInfo *ptPalInfo,
        struct real64x3_t *ptStart,
        struct real64x3_t *ptEnd,
        float vVelocity)
{
  double v7; // st7
  long double v8; // st4
  struct QTask_s *v9; // ebx
  long double v10; // st7
  long double v11; // st6
  long double v12; // st4
  double v13; // st6
  double v14; // st6
  double v15; // st7
  double v16; // st6
  float v17; // [esp+10h] [ebp-48h]
  float v18; // [esp+14h] [ebp-44h]
  float v19; // [esp+18h] [ebp-40h]
  float vReal32; // [esp+20h] [ebp-38h]
  float v21; // [esp+24h] [ebp-34h]
  float tReal32x3; // [esp+28h] [ebp-30h]
  float tReal32x3_4; // [esp+2Ch] [ebp-2Ch]
  float tReal32x3_8; // [esp+30h] [ebp-28h]
  float tY; // [esp+34h] [ebp-24h]
  float tYa; // [esp+34h] [ebp-24h]
  float tYb; // [esp+34h] [ebp-24h]
  float tY_4; // [esp+38h] [ebp-20h]
  float tY_4a; // [esp+38h] [ebp-20h]
  float tY_4b; // [esp+38h] [ebp-20h]
  float tY_8; // [esp+3Ch] [ebp-1Ch]
  float tY_8a; // [esp+3Ch] [ebp-1Ch]
  float tZ; // [esp+40h] [ebp-18h]
  float tZ_4; // [esp+44h] [ebp-14h]
  float tZ_8; // [esp+48h] [ebp-10h]
  float tX; // [esp+4Ch] [ebp-Ch]
  float tX_4; // [esp+50h] [ebp-8h]

  tReal32x3 = ptEnd->vX - ptStart->vX;
  tReal32x3_4 = ptEnd->vY - ptStart->vY;
  v7 = ptEnd->vZ - ptStart->vZ;
  tReal32x3_8 = v7;
  v8 = sqrt(tReal32x3 * tReal32x3 + tReal32x3_4 * tReal32x3_4 + v7 * v7);
  v21 = v8;
  vReal32 = v8;
  if ( v8 <= 0.0 )
    return;
  tZ = 0.0;
  tZ_4 = 0.0;
  tZ_8 = 1.0;
  v9 = QTask_NewFn(ptParent, Tracerbullet_eQTaskType, nullptr);
  v17 = tReal32x3_8 * 0.0;
  tY = tReal32x3_4 - v17;
  tX = tY;
  tY_4 = -(tReal32x3 - v17);
  tX_4 = tY_4;
  v18 = tReal32x3 * 0.0;
  v19 = tReal32x3_4 * 0.0;
  tY_8 = v18 - v19;
  if ( tY != 0.0 )
    goto LABEL_12;
  if ( tY_4 == 0.0 && tY_8 == 0.0 )
  {
    v10 = 0.0;
    tX = 1.0;
    tX_4 = 0.0;
    tYa = v19 - v17;
    tZ = tYa;
    tY_4a = -(v18 - tReal32x3_8);
    tZ_4 = tY_4a;
    tY_8a = v18 - tReal32x3_4;
    tZ_8 = tY_8a;
    if ( tYa != 0.0 || tY_4a != 0.0 || tY_8a != 0.0 )
    {
      v11 = 1.0 / sqrt(tYa * tYa + tY_4a * tY_4a + tY_8a * tY_8a);
      tZ = tYa * v11;
      tZ_4 = tY_4a * v11;
      tZ_8 = tY_8a * v11;
    }
    goto LABEL_14;
  }
  if ( tY == 0.0 && tY_4 == 0.0 && tY_8 == 0.0 )
  {
    v10 = tY_8;
  }
  else
  {
LABEL_12:
    v12 = sqrt(tY * tY + tY_4 * tY_4 + tY_8 * tY_8);
    tX = tY * (1.0 / v12);
    tX_4 = tY_4 * (1.0 / v12);
    v10 = 1.0 / v12 * tY_8;
  }
LABEL_14:
  tYb = tReal32x3;
  tY_4b = tReal32x3_4;
  if ( tReal32x3 == 0.0 && tReal32x3_4 == 0.0 && tReal32x3_8 == 0.0 )
  {
    v14 = tReal32x3_8;
  }
  else
  {
    v13 = 1.0 / v21;
    tYb = tReal32x3 * v13;
    tY_4b = tReal32x3_4 * v13;
    v14 = v13 * tReal32x3_8;
  }
  *(float *)&v9[3].tQTaskChildren.ptTail = v10;
  *(float *)&v9[2].ptParent = tX;
  *(float *)&v9[3].tQTaskRefList.ptHead = v14;
  *(float *)&v9[2].eQTaskType = tYb;
  v15 = 1.0 / vReal32;
  *(float *)&v9[3].ptPrev = tX_4;
  *(float *)&v9[3].ptNext = tZ;
  *(float *)&v9[3].tQTaskChildren.ptHead = tY_4b;
  *(float *)&v9[3].tQTaskRefList.ptMiddle = tZ_8;
  *(float *)&v9[3].tQTaskChildren.ptMiddle = tZ_4;
  qmemcpy(&v9[3].ptParent, ptStart, 0x18u);
  *(float *)&v9[4].ptParent = vReal32;
  *(float *)&v9[4].tQTaskChildren.ptTail = tReal32x3;
  *(float *)&v9[4].tQTaskRefList.ptHead = tReal32x3_4;
  *(float *)&v9[4].tQTaskRefList.ptMiddle = tReal32x3_8;
  v9[13].tQTaskChildren.ptHead = (struct QTask_s *)ptPalInfo;
  v16 = vVelocity * 136.53334045410156;
  *(float *)&v9[4].tQTaskRefList.ptTail = v16;
  *(float *)&v9[4].tQTaskChildren.ptTail = v16 * v15 * *(float *)&v9[4].tQTaskChildren.ptTail;
  v9[13].ptPrev = (struct QTask_s *)ptTexInfo;
  *(float *)&v9[4].tQTaskRefList.ptHead = v16 * v15 * *(float *)&v9[4].tQTaskRefList.ptHead;
  *(float *)&v9[4].tQTaskRefList.ptMiddle = v16 * v15 * *(float *)&v9[4].tQTaskRefList.ptMiddle;
  Tracerbullet_InitRandomPolys(v9);
  v9[5].ptNext = (struct QTask_s *)PolyListDynCubeObj_New(
                                     Game_ptGame->ptWorld,
                                     v9,
                                     (struct real64x3_t *)&v9[3].ptParent,
                                     (struct real32x9_t *)&v9[2].ptParent,
                                     (struct RandomPoly_t *)&v9[5].ptPrev,
                                     4,
                                     8u,
                                     0,
                                     0,
                                     0,
                                     nullptr,
                                     nullptr);
}
