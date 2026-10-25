/* j/0/weapons/binocularoverlay.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/weapons/binocularoverlay.c:635  [size]
enum bool __cdecl BinocularOverlay_InfraEnabled()
{
  return isInfraEnabled;
}

// source: j/0/weapons/binocularoverlay.c:642  [size]
enum bool __cdecl BinocularOverlay_EnableInfra(enum bool isOn)
{
  isInfraEnabled = isOn;
  return isOn;
}

// source: j/0/weapons/binocularoverlay.c:649  [anchor-mhash]
void __cdecl TransContext_ProjectWorldPosEx(
        struct TransContext_s *ptTransContext,
        struct real32x2_t *ptDest,
        float *pvDist,
        struct real64x3_t *ptPos)
{
  double v4; // st7
  double v5; // st6
  double v6; // st5
  double v7; // st7
  double v8; // st7
  float Real32x3_Rotate_tTemp; // [esp+4h] [ebp-Ch]
  float Real32x3_Rotate_tTemp_4; // [esp+8h] [ebp-8h]

  v4 = ptPos->vX - ptTransContext->tPos.vX;
  v5 = ptPos->vY - ptTransContext->tPos.vY;
  v6 = ptPos->vZ - ptTransContext->tPos.vZ;
  Real32x3_Rotate_tTemp = v6 * ptTransContext->tMatrix.tX.vZ
                        + v5 * ptTransContext->tMatrix.tX.vY
                        + v4 * ptTransContext->tMatrix.tX.vX;
  Real32x3_Rotate_tTemp_4 = v6 * ptTransContext->tMatrix.tY.vZ
                          + v5 * ptTransContext->tMatrix.tY.vY
                          + v4 * ptTransContext->tMatrix.tY.vX;
  v7 = v6 * ptTransContext->tMatrix.tZ.vZ + v5 * ptTransContext->tMatrix.tZ.vY + v4 * ptTransContext->tMatrix.tZ.vX;
  *pvDist = v7;
  if ( v7 > 0.0 )
  {
    v8 = 1.0 / v7;
    ptDest->vX = ptTransContext->vScreenFOVX * Real32x3_Rotate_tTemp * v8 + ptTransContext->vScreenOriginX;
    ptDest->vY = ptTransContext->vScreenFOVY * Real32x3_Rotate_tTemp_4 * v8 + ptTransContext->vScreenOriginY;
  }
}

// source: j/0/weapons/binocularoverlay.c:681  [size]
struct TransContext_s *__cdecl TransContext_ProjectRotatedPosEx(
        struct TransContext_s *ptTransContext,
        struct real32x2_t *ptDest,
        struct real32x3_t *ptPos)
{
  double v3; // st7

  v3 = 1.0 / ptPos->vZ;
  ptDest->vX = ptTransContext->vScreenFOVX * ptPos->vX * v3 + ptTransContext->vScreenOriginX;
  ptDest->vY = ptTransContext->vScreenFOVY * ptPos->vY * v3 + ptTransContext->vScreenOriginY;
  return ptTransContext;
}

// source: j/0/weapons/binocularoverlay.c:701  [size]
void __cdecl TransContext_ProjectDirEx(
        struct TransContext_s *ptTransContext,
        struct real32x2_t *ptDest,
        float *pvDist,
        struct real32x3_t *ptDir)
{
  double v4; // st7
  double v5; // st6
  double v6; // st5
  double v7; // rt0

  v4 = ptTransContext->tMatrix.tX.vZ * ptDir->vZ
     + ptTransContext->tMatrix.tX.vY * ptDir->vY
     + ptTransContext->tMatrix.tX.vX * ptDir->vX;
  v5 = ptTransContext->tMatrix.tY.vZ * ptDir->vZ
     + ptTransContext->tMatrix.tY.vX * ptDir->vX
     + ptTransContext->tMatrix.tY.vY * ptDir->vY;
  v6 = ptTransContext->tMatrix.tZ.vZ * ptDir->vZ
     + ptTransContext->tMatrix.tZ.vX * ptDir->vX
     + ptTransContext->tMatrix.tZ.vY * ptDir->vY;
  *pvDist = v6;
  if ( v6 > 0.0 )
  {
    v7 = 1.0 / v6;
    ptDest->vX = v4 * ptTransContext->vScreenFOVX * v7 + ptTransContext->vScreenOriginX;
    ptDest->vY = v5 * ptTransContext->vScreenFOVY * v7 + ptTransContext->vScreenOriginY;
  }
}

// source: j/0/weapons/binocularoverlay.c:731  [size]
struct real32x2_t *__cdecl TransContext_ProjectSizeEx(
        struct TransContext_s *ptTransContext,
        struct real32x2_t *ptDest,
        struct real32x2_t *ptSize,
        float vDist)
{
  double v4; // st7

  v4 = 1.0 / vDist;
  ptDest->vX = ptTransContext->vScreenFOVX * ptSize->vX * v4;
  ptDest->vY = ptTransContext->vScreenFOVY * ptSize->vY * v4;
  return ptSize;
}

// source: j/0/weapons/binocularoverlay.c:756  [anchor-mhash]
void __cdecl VectorText_Init(struct VectorText_s *ptVectorText, int nMorphSpeed)
{
  struct AlphaVector_s *atAlphaVectorCurrent; // eax
  int v3; // edx
  struct AlphaVector_s *v4; // edi

  atAlphaVectorCurrent = ptVectorText->atAlphaVectorCurrent;
  v3 = 64;
  do
  {
    qmemcpy(&atAlphaVectorCurrent[64], &AV_SPACE, sizeof(struct AlphaVector_s));
    qmemcpy(atAlphaVectorCurrent, &AV_SPACE, sizeof(struct AlphaVector_s));
    v4 = atAlphaVectorCurrent - 64;
    ++atAlphaVectorCurrent;
    --v3;
    qmemcpy(v4, &AV_SPACE, sizeof(struct AlphaVector_s));
  }
  while ( v3 );
  ptVectorText->nMorphSpeed = nMorphSpeed;
}

// source: j/0/weapons/binocularoverlay.c:889  [anchor-mhash]
struct VUMeter_s *__cdecl VUMeter_Init(
        struct VUMeter_s *ptVUMeter,
        int nUpdateFrequency,
        float vFalloff)
{
  ptVUMeter->vCurrentValue = 0.0;
  ptVUMeter->vPeakValue = 0.0;
  ptVUMeter->vFalloff = 0.0;
  ptVUMeter->nTimer = 0;
  ptVUMeter->nUpdateFrequency = 0;
  ptVUMeter->nUpdateFrequency = nUpdateFrequency;
  ptVUMeter->vFalloff = vFalloff;
  return ptVUMeter;
}

// source: j/0/weapons/binocularoverlay.c:993  [anchor-mhash]
int __cdecl BinocularOverlay_RegisterObservedTask(
        struct QTask_s *ptQTask,
        struct QTask_s *ptRegisterQTask,
        float vDistance,
        float vRadius,
        struct real32x2_t *ptProjectedPos,
        int isOccluded,
        int isFriendly,
        int isDead)
{
  unsigned int v8; // eax
  struct QTask_s **p_tQTaskRefList; // ecx
  int v10; // eax
  char *v11; // esi
  unsigned int v12; // eax
  struct QReferenceList_s *v13; // ecx
  int v14; // ecx
  float *i; // edx
  DWORD PerformanceCounter; // eax
  bool v18; // zf
  DWORD TickCount; // eax

  v8 = 0;
  p_tQTaskRefList = (struct QTask_s **)&ptQTask[283].tQTaskRefList;
  while ( *p_tQTaskRefList != ptRegisterQTask )
  {
    ++v8;
    p_tQTaskRefList += 11;
    if ( v8 >= 0xA )
      goto LABEL_6;
  }
  v10 = 44 * v8;
  v11 = (char *)&ptQTask[283].tQTaskRefList + v10;
  if ( (struct QTask_s *)((char *)ptQTask + v10) != (struct QTask_s *)-11340 )
    goto LABEL_19;
LABEL_6:
  v12 = 0;
  v13 = &ptQTask[283].tQTaskRefList;
  do
  {
    if ( !v13->ptHead )
    {
      v11 = (char *)&ptQTask[283].tQTaskRefList + 44 * v12;
      goto LABEL_15;
    }
    ++v12;
    v13 = (struct QReferenceList_s *)((char *)v13 + 44);
  }
  while ( v12 < 0xA );
  v14 = 0;
  for ( i = (float *)&ptQTask[284].ptPrev; *i <= (double)vDistance; i += 11 )
  {
    if ( (unsigned int)++v14 >= 0xA )
      return 0;
  }
  v11 = (char *)&ptQTask[283].tQTaskRefList + 44 * v14;
LABEL_15:
  if ( Timer_isPerformanceCounter )
    PerformanceCounter = Timer_GetPerformanceCounter();
  else
    PerformanceCounter = GetTickCount();
  *((_DWORD *)v11 + 8) = PerformanceCounter - Timer_nStartTime;
LABEL_19:
  *((float *)v11 + 6) = vDistance;
  v18 = Timer_isPerformanceCounter == 0;
  *(_DWORD *)v11 = ptRegisterQTask;
  *((_DWORD *)v11 + 4) = 1;
  *((float *)v11 + 5) = vRadius;
  *((_DWORD *)v11 + 3) = isOccluded;
  if ( v18 )
    TickCount = GetTickCount();
  else
    TickCount = Timer_GetPerformanceCounter();
  *((_DWORD *)v11 + 7) = TickCount - Timer_nStartTime;
  *((_DWORD *)v11 + 2) = isFriendly;
  *((_DWORD *)v11 + 1) = isDead;
  *(struct real32x2_t *)(v11 + 36) = *ptProjectedPos;
  return 1;
}

// source: j/0/weapons/binocularoverlay.c:1069  [anchor-mhash]
void __cdecl BinocularOverlay_TrackMovement(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { float vThickness; };
    struct { char igi2_o1[4]; float vGamma; };
    struct { char igi2_o2[36]; float vRadius; };
    struct { char igi2_o3[36]; int vRadiusa; };
    struct { char igi2_o4[40]; float pvDist; };
    struct { char igi2_o5[44]; struct QTask_s **v25; };
    struct { char igi2_o6[48]; float vOrientation; };
    struct { char igi2_o7[52]; struct LineOfSightOutputContext_s tOutputContext; };
    struct { char igi2_o8[60]; struct real32x2_t tScreenPos; };
    struct { char igi2_o9[68]; struct real32x3_t Real32x3_Rotate_tTemp; };
    struct { char igi2_o10[80]; struct real32x3_t tRotatedPos; };
    struct { char igi2_o11[92]; struct WeaponCollisionEvaluateContext_t tEvaluateContext; };
    struct { char igi2_o12[112]; struct real64x3_t tHumanPos; };
    struct { char igi2_o13[136]; struct real64x3_t tHeadPos; };
    char igi2_extent[160];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  unsigned __int16 v1; // cx
  struct QTask_s *v2; // edi
  struct QTask_s *v3; // ebp
  unsigned __int16 *p_eQTaskType; // eax
  int v5; // ecx
  float v6; // eax
  struct QTask_s **v7; // ecx
  struct QTask_s *v8; // ebx
  struct Game_s *v9; // edx
  bool v10; // zf
  struct QTask_s **p_ptParent; // esi
  int v12; // ebx
  DWORD PerformanceCounter; // eax
  DWORD v14; // eax
  int v15; // eax
  double v16; // st7
  double v17; // st7
  double v18; // st6
  double v19; // st5

  v1 = Human_eQTaskType;
  v2 = ptQTask;
  *(_DWORD *)&ptQTask[7].eQTaskType = 0;
  ptQTask[7].ptParent = nullptr;
  v3 = ptQTask;
  if ( QTask_IsQTaskTypeDerived(ptQTask->eQTaskType, v1) )
  {
LABEL_4:
    p_eQTaskType = &ptQTask[283].eQTaskType;
    v5 = 10;
    do
    {
      *(_DWORD *)p_eQTaskType = 0;
      p_eQTaskType += 22;
      --v5;
    }
    while ( v5 );
    v6 = *(float *)&Human_ptQTaskList->nTask;
    if ( Human_ptQTaskList->nTask > 0 )
    {
      v7 = Human_ptQTaskList->ptQTask;
      igi2_frame.v25 = Human_ptQTaskList->ptQTask;
      igi2_frame.vOrientation = v6;
      do
      {
        v8 = *v7;
        if ( *v7 && v8 != v3 && BYTE1(v8[29].tQTaskRefList.ptHead) && !LOBYTE(v8[29].tQTaskRefList.ptHead) )
        {
          qmemcpy(&igi2_frame.tHeadPos, &v8[33].tQTaskChildren.ptTail[10].tQTaskChildren, sizeof(igi2_frame.tHeadPos));
          qmemcpy(&igi2_frame.tHumanPos, &v8[1], sizeof(igi2_frame.tHumanPos));
          igi2_frame.vRadius = *(float *)&v8[8].ptNext;
          igi2_frame.Real32x3_Rotate_tTemp.vX = TransContext_tActiveTransContext.tMatrix.tX.vZ
                                   * (igi2_frame.tHumanPos.vZ - TransContext_tActiveTransContext.tPos.vZ)
                                   + TransContext_tActiveTransContext.tMatrix.tX.vY
                                   * (igi2_frame.tHumanPos.vY - TransContext_tActiveTransContext.tPos.vY)
                                   + TransContext_tActiveTransContext.tMatrix.tX.vX
                                   * (igi2_frame.tHumanPos.vX - TransContext_tActiveTransContext.tPos.vX);
          igi2_frame.Real32x3_Rotate_tTemp.vY = TransContext_tActiveTransContext.tMatrix.tY.vZ
                                   * (igi2_frame.tHumanPos.vZ - TransContext_tActiveTransContext.tPos.vZ)
                                   + TransContext_tActiveTransContext.tMatrix.tY.vY
                                   * (igi2_frame.tHumanPos.vY - TransContext_tActiveTransContext.tPos.vY)
                                   + TransContext_tActiveTransContext.tMatrix.tY.vX
                                   * (igi2_frame.tHumanPos.vX - TransContext_tActiveTransContext.tPos.vX);
          igi2_frame.Real32x3_Rotate_tTemp.vZ = TransContext_tActiveTransContext.tMatrix.tZ.vX
                                   * (igi2_frame.tHumanPos.vX - TransContext_tActiveTransContext.tPos.vX)
                                   + TransContext_tActiveTransContext.tMatrix.tZ.vZ
                                   * (igi2_frame.tHumanPos.vZ - TransContext_tActiveTransContext.tPos.vZ)
                                   + TransContext_tActiveTransContext.tMatrix.tZ.vY
                                   * (igi2_frame.tHumanPos.vY - TransContext_tActiveTransContext.tPos.vY);
          igi2_frame.tRotatedPos = igi2_frame.Real32x3_Rotate_tTemp;
          if ( Mesh3D_ExcludeObject(&igi2_frame.tRotatedPos, igi2_frame.vRadius, nullptr) == false )
          {
            v9 = Game_ptGame;
            ++*(int *)&ptQTask[7].ptParent;
            igi2_frame.tEvaluateContext.ptIgnore1QTask = v3;
            igi2_frame.tEvaluateContext.ptIgnore2QTask = v8;
            igi2_frame.tEvaluateContext.tCollisionEvaluateContext.ptQTask = v3;
            igi2_frame.tEvaluateContext.vHitProbability = 1.0;
            World_LineOfSight(
              v9->ptWorld,
              &TransContext_tActiveTransContext.tPos,
              &igi2_frame.tHeadPos,
              GameFunctions_eWeaponCollisionEvaluateQTaskEvent,
              &igi2_frame.tEvaluateContext.tCollisionEvaluateContext,
              0xFFFFFFFF,
              WORLD_DYNCUBETREE_CATEGORY_ALL,
              &igi2_frame.tOutputContext);
            TransContext_ProjectWorldPosEx(&TransContext_tActiveTransContext, &igi2_frame.tScreenPos, &igi2_frame.pvDist, &igi2_frame.tHumanPos);
            if ( igi2_frame.pvDist > 0.0 )
              BinocularOverlay_RegisterObservedTask(
                ptQTask,
                v8,
                igi2_frame.pvDist,
                igi2_frame.vRadius,
                &igi2_frame.tScreenPos,
                igi2_frame.tOutputContext.vTransparency == 0.0,
                v8[10].tQTaskRefList.ptTail != (struct QReference_s *)1,
                SLOBYTE(v8[29].tQTaskRefList.ptHead));
          }
          v2 = ptQTask;
        }
        v7 = igi2_frame.v25 + 1;
        v10 = LODWORD(igi2_frame.vOrientation) == 1;
        ++igi2_frame.v25;
        --LODWORD(igi2_frame.vOrientation);
      }
      while ( !v10 );
    }
    p_ptParent = &v2[283].ptParent;
    v12 = 10;
    while ( 1 )
    {
      if ( Timer_isPerformanceCounter )
        PerformanceCounter = Timer_GetPerformanceCounter();
      else
        PerformanceCounter = GetTickCount();
      v14 = PerformanceCounter - Timer_nStartTime;
      if ( !p_ptParent[1] )
      {
        if ( (int)(v14 - (_DWORD)p_ptParent[4]) > 3000 )
          *(p_ptParent - 3) = nullptr;
        goto LABEL_36;
      }
      if ( !*p_ptParent )
        break;
LABEL_36:
      p_ptParent += 11;
      if ( !--v12 )
        return;
    }
    ++*(_DWORD *)&v2[7].eQTaskType;
    if ( *(p_ptParent - 2) )
    {
      igi2_frame.Real32x3_Rotate_tTemp.vX = 0.0;
      igi2_frame.Real32x3_Rotate_tTemp.vZ = 128.0;
    }
    else
    {
      v10 = *(p_ptParent - 1) == nullptr;
      igi2_frame.Real32x3_Rotate_tTemp.vZ = 0.0;
      if ( !v10 )
      {
        igi2_frame.Real32x3_Rotate_tTemp.vX = 0.0;
        igi2_frame.Real32x3_Rotate_tTemp.vY = 128.0;
LABEL_29:
        v15 = v14 - (_DWORD)p_ptParent[5];
        if ( v15 >= 0 )
        {
          igi2_frame.vRadiusa = 250;
          if ( v15 <= 250 )
            igi2_frame.vRadiusa = v15;
        }
        else
        {
          igi2_frame.vRadiusa = 0;
        }
        LODWORD(igi2_frame.tScreenPos.vX) = p_ptParent[2];
        v16 = (double)igi2_frame.vRadiusa * 0.004000000189989805;
        igi2_frame.vOrientation = 1.5707963705062866 * v16;
        v17 = (1.0 - v16) * 10.0 + 1.0;
        v18 = *((float *)p_ptParent + 2);
        v19 = 1.0 / *((float *)p_ptParent + 3);
        igi2_frame.tOutputContext.vTransparency = TransContext_tActiveTransContext.vScreenFOVX * igi2_frame.tScreenPos.vX * v19;
        igi2_frame.vGamma = v18 * TransContext_tActiveTransContext.vScreenFOVY * v19 * v17;
        igi2_frame.vThickness = igi2_frame.tOutputContext.vTransparency * v17;
        QSprite_RegisterLineMesh(
          BinocularOverlay_atBox,
          5,
          *((float *)p_ptParent + 6),
          *((float *)p_ptParent + 7),
          1.0,
          igi2_frame.Real32x3_Rotate_tTemp.vX,
          igi2_frame.Real32x3_Rotate_tTemp.vY,
          igi2_frame.Real32x3_Rotate_tTemp.vZ,
          0.5,
          1.0,
          igi2_frame.vOrientation,
          igi2_frame.vThickness,
          igi2_frame.vGamma,
          0,
          1);
        goto LABEL_36;
      }
      igi2_frame.Real32x3_Rotate_tTemp.vX = 64.0;
    }
    igi2_frame.Real32x3_Rotate_tTemp.vY = 0.0;
    goto LABEL_29;
  }
  while ( 1 )
  {
    v3 = v3->ptParent;
    if ( !v3 )
      break;
    if ( QTask_IsQTaskTypeDerived(v3->eQTaskType, v1) )
      goto LABEL_4;
  }
}

// source: j/0/weapons/binocularoverlay.c:1271  [anchor-mhash]
void __cdecl BinocularOverlay_DrawCompass(struct BinocularOverlay_s *ptBinocularOverlay)
{
  #pragma pack(push, 1)
  union
  {
    struct { float vG; };
    struct { char igi2_o1[4]; float v28; };
    struct { char igi2_o2[8]; float v29; };
    struct { char igi2_o3[12]; float vZ; };
    struct { char igi2_o4[16]; unsigned int v31; };
    struct { char igi2_o5[16]; unsigned int v32; };
    struct { char igi2_o6[20]; int nPri; };
    struct { char igi2_o7[20]; int v34; };
    struct { char igi2_o8[36]; float vX; };
    struct { char igi2_o9[36]; float vXa; };
    struct { char igi2_o10[40]; int nWidth; };
    struct { char igi2_o11[40]; int nWidtha; };
    struct { char igi2_o12[44]; int vTextHeight; };
    struct { char igi2_o13[44]; float vTextHeighta; };
    struct { char igi2_o14[48]; __int64 vOrientation; };
    struct { char igi2_o15[56]; __int64 vX1; };
    struct { char igi2_o16[68]; float vPitch; };
    struct { char igi2_o17[72]; __int64 vY1; };
    struct { char igi2_o18[80]; float v45; };
    struct { char igi2_o19[84]; struct ClippingRect_s tRect; };
    struct { char igi2_o20[108]; struct QVertexStripContext_s tStrip; };
    struct { char igi2_o21[128]; struct QVertex_s atQVertex[3]; };
    char igi2_extent[240];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct BinocularOverlay_s *v1; // edi
  double v2; // st7
  int v3; // edx
  double v4; // st7
  int v5; // ebx
  struct StaticTilemap_s *v6; // esi
  double v7; // st7
  double v8; // st7
  struct QTilemap_s *ptQTilemap; // ebx
  int v10; // edx
  __int16 *anGraphicWidth; // ecx
  int nHeight; // edi
  double v13; // st7
  float vA; // edx
  float vB; // eax
  float v16; // edi
  float vR; // edx
  float v18; // eax
  double v19; // st7
  unsigned int bQGraphicFlags; // ecx
  struct QTilemap_s *v21; // ebx
  float v22; // eax
  float v23; // edx
  float v24; // ecx
  double v25; // st7
  double v26; // st7

  v1 = ptBinocularOverlay;
  igi2_frame.nWidtha = Display_tActiveMode.nWidth;
  Real32x3_GetAngles(&ptBinocularOverlay->tDirection, &igi2_frame.vPitch, (float *)&igi2_frame.vOrientation);
  v2 = (double)igi2_frame.nWidtha;
  v3 = v1->atDirection[0]->ptQTilemap->nHeight
     * v1->atDirection[0]->ptQTilemap->ptQSprite->atQAnimframe[v1->atDirection[0]->ptQTilemap->ptQSprite->nQAnimframes].nHeight;
  igi2_frame.tRect.vX = 0.625 * v2;
  igi2_frame.tRect.vY = (double)Display_tActiveMode.nHeight * 0.7916666865348816;
  igi2_frame.tRect.vWidth = v2 * 0.28125;
  igi2_frame.tRect.vHeight = (double)v3 + (double)v3 + 26.0;
  igi2_frame.tRect.vHalfWidth = igi2_frame.tRect.vWidth * 0.5;
  igi2_frame.tRect.vHalfHeight = igi2_frame.tRect.vHeight * 0.5;
  igi2_frame.vPitch = igi2_frame.tRect.vWidth * 0.015625;
  v4 = *(float *)&igi2_frame.vOrientation;
  if ( *(float *)&igi2_frame.vOrientation < 0.0 )
    v4 = v4 + 6.2831854820251465;
  v5 = 0;
  igi2_frame.nWidth = 0;
  igi2_frame.vX = igi2_frame.tRect.vWidth * v4 * 0.15915493667125702;
  igi2_frame.v45 = igi2_frame.tRect.vHalfHeight + igi2_frame.tRect.vY;
  do
  {
    v6 = nullptr;
    if ( (v5 & 0xF) != 0 )
    {
      if ( (v5 & 7) != 0 )
        v7 = 4.0;
      else
        v7 = 8.0;
    }
    else
    {
      v7 = 12.0;
      v6 = v1->atDirection[v5 >> 4];
    }
    v8 = v7 * 0.5;
    *(float *)&igi2_frame.vOrientation = igi2_frame.tRect.vHalfHeight + v8 + igi2_frame.tRect.vY;
    *(float *)&igi2_frame.vX1 = igi2_frame.vX + igi2_frame.tRect.vX;
    *(float *)&igi2_frame.vY1 = igi2_frame.v45 - v8;
    QSprite_RegisterLine(
      *(float *)&igi2_frame.vX1,
      *(float *)&igi2_frame.vY1,
      1.0,
      *(float *)&igi2_frame.vX1,
      *(float *)&igi2_frame.vOrientation,
      1.0,
      0.0,
      64.0,
      0.0,
      0.0,
      64.0,
      0.0,
      1.0,
      1.0,
      0,
      1);
    if ( v6 )
    {
      ptQTilemap = v6->ptQTilemap;
      v10 = 0;
      igi2_frame.vTextHeight = 0;
      if ( v6->ptQTilemap->nHeight > 0 )
      {
        anGraphicWidth = ptQTilemap->anGraphicWidth;
        nHeight = v6->ptQTilemap->nHeight;
        do
        {
          if ( *anGraphicWidth > v10 )
            v10 = *anGraphicWidth;
          ++anGraphicWidth;
          --nHeight;
        }
        while ( nHeight );
        igi2_frame.vTextHeight = v10;
      }
      v13 = (double)igi2_frame.vTextHeight;
      igi2_frame.nPri = v6->nPri;
      vA = v6->vA;
      igi2_frame.vTextHeighta = (float)(ptQTilemap->nHeight
                           * ptQTilemap->ptQSprite->atQAnimframe[ptQTilemap->ptQSprite->nQAnimframes].nHeight);
      igi2_frame.vX1 = (__int64)(*(float *)&igi2_frame.vX1 - 0.5 * v13);
      igi2_frame.v31 = v6->bQGraphicFlags | 0x40000000;
      vB = v6->vB;
      *(float *)&igi2_frame.vX1 = (float)(int)igi2_frame.vX1;
      v6->vX = *(float *)&igi2_frame.vX1;
      v16 = *(float *)&igi2_frame.vX1;
      igi2_frame.vY1 = (__int64)(*(float *)&igi2_frame.vY1 - igi2_frame.vTextHeighta - 2.0);
      igi2_frame.vZ = v6->vZ;
      igi2_frame.v29 = vA;
      vR = v6->vR;
      igi2_frame.v28 = vB;
      igi2_frame.vG = v6->vG;
      *(float *)&igi2_frame.vY1 = (float)(int)igi2_frame.vY1;
      v18 = *(float *)&igi2_frame.vY1;
      v6->vY = *(float *)&igi2_frame.vY1;
      QTilemap_Register(ptQTilemap, v16, v18, vR, igi2_frame.vG, igi2_frame.v28, igi2_frame.v29, igi2_frame.vZ, igi2_frame.v31, igi2_frame.nPri);
      v19 = *(float *)&igi2_frame.vOrientation + 2.0;
      v6->vX = v16;
      igi2_frame.vOrientation = (__int64)v19;
      bQGraphicFlags = v6->bQGraphicFlags;
      v21 = v6->ptQTilemap;
      igi2_frame.v34 = v6->nPri;
      v22 = v6->vA;
      LODWORD(igi2_frame.vOrientation) = (__int64)v19;
      v23 = v6->vZ;
      igi2_frame.v32 = bQGraphicFlags | 0x40000000;
      *(float *)&igi2_frame.vOrientation = (float)(int)igi2_frame.vOrientation;
      v24 = v6->vB;
      v6->vY = *(float *)&igi2_frame.vOrientation;
      QTilemap_Register(v21, v16, *(float *)&igi2_frame.vOrientation, v6->vR, v6->vG, v24, v22, v23, igi2_frame.v32, igi2_frame.v34);
      v5 = igi2_frame.nWidth;
      v1 = ptBinocularOverlay;
    }
    v25 = igi2_frame.vX + igi2_frame.vPitch;
    igi2_frame.vX = v25;
    if ( v25 >= igi2_frame.tRect.vWidth )
      igi2_frame.vX = igi2_frame.vX - igi2_frame.tRect.vWidth;
    igi2_frame.nWidth = ++v5;
  }
  while ( v5 < 64 );
  igi2_frame.atQVertex[0].vA = 1.0;
  igi2_frame.atQVertex[0].vR = 0.0;
  igi2_frame.atQVertex[0].vG = 64.0;
  igi2_frame.atQVertex[0].vB = 0.0;
  igi2_frame.vXa = igi2_frame.tRect.vHalfWidth + igi2_frame.tRect.vX;
  igi2_frame.atQVertex[0].vU = 0.0;
  igi2_frame.atQVertex[0].vV = 0.0;
  igi2_frame.atQVertex[0].vZ = 1.0;
  qmemcpy(&igi2_frame.atQVertex[1], igi2_frame.atQVertex, sizeof(struct QVertex_s));
  qmemcpy(&igi2_frame.atQVertex[2], igi2_frame.atQVertex, sizeof(struct QVertex_s));
  igi2_frame.atQVertex[0].vY = igi2_frame.tRect.vY + 4.0;
  igi2_frame.vPitch = igi2_frame.vXa - 4.0;
  igi2_frame.atQVertex[1].vX = igi2_frame.vPitch;
  igi2_frame.v45 = igi2_frame.vXa + 4.0;
  igi2_frame.atQVertex[2].vX = igi2_frame.v45;
  igi2_frame.atQVertex[0].vX = igi2_frame.vXa;
  igi2_frame.tStrip.atQVertex = igi2_frame.atQVertex;
  igi2_frame.atQVertex[1].vY = igi2_frame.tRect.vY;
  igi2_frame.tStrip.bFlags = (unsigned int)&MTP_atLODVirModel[3].atBoneVertexRefs[26].atVertexRefs[479];
  igi2_frame.tStrip.isLine = 0;
  igi2_frame.tStrip.nDepth = 0;
  igi2_frame.tStrip.nStripLength = 3;
  QVertex_ptActiveTexture = nullptr;
  igi2_frame.atQVertex[2].vY = igi2_frame.tRect.vY;
  RenderMode_tActiveRenderMode.apfRenderModeMethod[QVertex_eRegisterQVertexStripMethod](&igi2_frame.tStrip);
  v26 = igi2_frame.tRect.vHeight + igi2_frame.tRect.vY;
  igi2_frame.atQVertex[0].vX = igi2_frame.vXa;
  igi2_frame.atQVertex[1].vX = igi2_frame.vPitch;
  igi2_frame.atQVertex[0].vY = v26 - 4.0;
  igi2_frame.atQVertex[2].vX = igi2_frame.v45;
  igi2_frame.atQVertex[1].vY = v26;
  igi2_frame.atQVertex[2].vY = v26;
  RenderMode_tActiveRenderMode.apfRenderModeMethod[QVertex_eRegisterQVertexStripMethod](&igi2_frame.tStrip);
}

// source: j/0/weapons/binocularoverlay.c:1426  [anchor-caller]
void __cdecl BinocularOverlay_Draw(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { float ptQSprite; };
    struct { float ptQSpritea; };
    struct { char igi2_o2[12]; float v14; };
    struct { char igi2_o3[16]; float nWidth; };
    struct { char igi2_o4[20]; float vY1; };
    struct { char igi2_o5[24]; float v17; };
    struct { char igi2_o6[28]; float vX3; };
    struct { char igi2_o7[32]; struct real64x3_t ptEnd; };
    struct { char igi2_o8[60]; struct CollisionEvaluateContext_s nNumPoints; };
    struct { char igi2_o9[68]; struct QTask_s *ptParent; };
    struct { char igi2_o10[72]; struct QTask_s *v22; };
    struct { char igi2_o11[76]; int v23; };
    struct { char igi2_o12[80]; struct QIntersection_s ptIntersection; };
    struct { char igi2_o13[200]; double v25; };
    struct { char igi2_o14[224]; char Buffer[128]; };
    char igi2_extent[352];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct GameSprite_t *v1; // edi
  int nQAnimframes; // eax
  struct QSprite_s *p_tQSprite; // edi
  double nHeight; // st7
  float v5; // esi
  double v6; // st7
  double v7; // st6
  double v8; // st5
  struct QTask_s *v9; // edx
  char *LocalizedStringForLanguage; // eax
  float *ptNext; // eax

  if ( isInfraEnabled )
  {
    v1 = BinocularOverlay_ptInfraGameSprite;
    isDrawInfra = true;
  }
  else
  {
    v1 = BinocularOverlay_ptBinoGameSprite;
    isDrawInfra = false;
  }
  nQAnimframes = v1->tQSprite.nQAnimframes;
  p_tQSprite = &v1->tQSprite;
  igi2_frame.nWidth = (float)Display_tActiveMode.nWidth;
  igi2_frame.v17 = igi2_frame.nWidth / (double)p_tQSprite->atQAnimframe[nQAnimframes].nWidth;
  nHeight = (double)Display_tActiveMode.nHeight;
  igi2_frame.v14 = nHeight;
  igi2_frame.vX3 = nHeight + igi2_frame.v17;
  igi2_frame.vY1 = igi2_frame.nWidth * 0.5;
  igi2_frame.ptQSprite = -igi2_frame.v17;
  v5 = igi2_frame.ptQSprite;
  QSprite_Register4(
    p_tQSprite,
    igi2_frame.ptQSprite,
    igi2_frame.ptQSprite,
    igi2_frame.vY1,
    igi2_frame.ptQSprite,
    igi2_frame.ptQSprite,
    igi2_frame.vX3,
    igi2_frame.vY1,
    igi2_frame.vX3,
    128.0,
    128.0,
    128.0,
    0,
    (unsigned int)&MTP_atLODVirModel[45].atBoneVertexRefs[20].atVertexRefs[781],
    1);
  igi2_frame.ptQSpritea = igi2_frame.nWidth + igi2_frame.v17;
  QSprite_Register4(
    p_tQSprite,
    igi2_frame.ptQSpritea,
    v5,
    igi2_frame.vY1,
    v5,
    igi2_frame.ptQSpritea,
    igi2_frame.vX3,
    igi2_frame.vY1,
    igi2_frame.vX3,
    128.0,
    128.0,
    128.0,
    0,
    (unsigned int)&MTP_atLODVirModel[45].atBoneVertexRefs[20].atVertexRefs[781],
    1);
  if ( !isInfraEnabled )
  {
    v6 = *(float *)&ptQTask[3].tQTaskChildren.ptMiddle;
    v7 = *(float *)&ptQTask[3].tQTaskChildren.ptTail;
    igi2_frame.ptParent = ptQTask->ptParent;
    v8 = *(float *)&ptQTask[3].tQTaskRefList.ptHead;
    igi2_frame.nNumPoints.ptQTask = ptQTask;
    v9 = igi2_frame.ptParent->ptParent;
    qmemcpy(&igi2_frame.ptIntersection, &ptQTask[2].tQTaskRefList.ptMiddle, 0x18u);
    igi2_frame.ptEnd.vX = v6 * 4096000.0;
    igi2_frame.ptEnd.vX = *(double *)&igi2_frame.ptIntersection.ptHitObj + igi2_frame.ptEnd.vX;
    igi2_frame.ptEnd.vY = igi2_frame.ptIntersection.tPos.vX + v7 * 4096000.0;
    igi2_frame.v22 = v9;
    igi2_frame.ptEnd.vZ = igi2_frame.ptIntersection.tPos.vY + v8 * 4096000.0;
    igi2_frame.v23 = 1065353216;
    World_TraceLines(
      Game_ptGame->ptWorld,
      (struct QIntersection_s *)&igi2_frame.ptIntersection.tPos.vZ,
      (struct real64x3_t *)&igi2_frame.ptIntersection,
      &igi2_frame.ptEnd,
      1,
      GameFunctions_eWeaponCollisionEvaluateQTaskEvent,
      &igi2_frame.nNumPoints,
      0xD8000000);
    if ( *((_DWORD *)&igi2_frame.ptIntersection.vLight + 1) )
    {
      *(double *)&ptQTask[294].tQTaskRefList.ptMiddle = igi2_frame.v25;
    }
    else
    {
      ptQTask[294].tQTaskRefList.ptMiddle = nullptr;
      ptQTask[294].tQTaskRefList.ptTail = (struct QReference_s *)1095712768;
    }
    LocalizedStringForLanguage = Config_GetLocalizedStringForLanguage(
                                   "weapons/strings/Binoculars/range",
                                   Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eLanguage,
                                   true);
    if ( *((_DWORD *)&igi2_frame.ptIntersection.vLight + 1) )
      sprintf(igi2_frame.Buffer, "%s: %0.f%s", LocalizedStringForLanguage, igi2_frame.v25 * 0.000244140625, "m");
    else
      sprintf(igi2_frame.Buffer, "%s: %0.f+%s", LocalizedStringForLanguage, 1000.0, "m");
    Text_SetString((struct StaticTilemap_s *)ptQTask[1].ptNext, igi2_frame.Buffer);
    *(float *)&ptQTask[1].ptNext->ptPrev = (float)(int)(__int64)(igi2_frame.nWidth * 0.46875);
    ptNext = (float *)ptQTask[1].ptNext;
    ptNext[2] = (float)(int)(__int64)(igi2_frame.v14 * 0.7291666865348816
                                    - (double)(*(__int16 *)(*(_DWORD *)ptNext + 6)
                                             * *(__int16 *)(*(_DWORD *)(*(_DWORD *)(*(_DWORD *)ptNext + 8) + 8)
                                                          + 36
                                                          * *(unsigned __int16 *)(*(_DWORD *)(*(_DWORD *)ptNext + 8) + 20)
                                                          + 14)));
    if ( ptQTask[294].tQTaskRefList.ptHead )
      Text_Register((struct StaticTilemap_s *)ptQTask[1].ptNext);
    BinocularOverlay_DrawCompass((struct BinocularOverlay_s *)ptQTask);
    BinocularOverlay_TrackMovement(ptQTask);
  }
}

// source: j/0/weapons/binocularoverlay.c:1597  [anchor-mhash]
void __cdecl BinocularOverlay_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QReference_s **p_ptTail; // eax
  int v3; // ecx
  struct QReference_s **v4; // ebp
  struct QTask_s *v5; // eax
  char zString[4]; // [esp+10h] [ebp-4h] BYREF

  zString[1] = 0;
  p_ptTail = &ptQTask[277].tQTaskRefList.ptTail;
  v3 = 12;
  do
  {
    v4 = p_ptTail - 2;
    *v4 = nullptr;
    v4[1] = nullptr;
    *p_ptTail = nullptr;
    p_ptTail[1] = nullptr;
    p_ptTail[2] = nullptr;
    p_ptTail[2] = (struct QReference_s *)30;
    *p_ptTail = (struct QReference_s *)1017370378;
    p_ptTail += 5;
    --v3;
  }
  while ( v3 );
  ptQTask[1].ptNext = (struct QTask_s *)Text_New(
                                          ComputerMenu_tComputerMenuResource.ptQSpriteFont3,
                                          0.0,
                                          0.0,
                                          (char *)&g_zInitialValue);
  ptQTask[1].tQTaskRefList.ptHead = (struct QReference_s *)Text_New(
                                                             ComputerMenu_tComputerMenuResource.ptQSpriteFont3,
                                                             0.0,
                                                             0.0,
                                                             (char *)&g_zInitialValue);
  zString[0] = 87;
  ptQTask[1].ptPrev = (struct QTask_s *)Text_New(ComputerMenu_tComputerMenuResource.ptQSpriteFont3, 0.0, 0.0, zString);
  zString[0] = 78;
  ptQTask[1].tQTaskChildren.ptHead = (struct QTask_s *)Text_New(
                                                         ComputerMenu_tComputerMenuResource.ptQSpriteFont3,
                                                         0.0,
                                                         0.0,
                                                         zString);
  zString[0] = 69;
  ptQTask[1].tQTaskChildren.ptMiddle = (struct QTask_s *)Text_New(
                                                           ComputerMenu_tComputerMenuResource.ptQSpriteFont3,
                                                           0.0,
                                                           0.0,
                                                           zString);
  zString[0] = 83;
  v5 = (struct QTask_s *)Text_New(ComputerMenu_tComputerMenuResource.ptQSpriteFont3, 0.0, 0.0, zString);
  ptQTask[2].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[2].tQTaskRefList.ptTail = nullptr;
  ptQTask[2].ptParent = nullptr;
  *(_DWORD *)&ptQTask[2].eQTaskType = 0;
  ptQTask[3].ptNext = nullptr;
  ptQTask[3].ptPrev = nullptr;
  ptQTask[3].tQTaskChildren.ptTail = nullptr;
  ptQTask[3].tQTaskRefList.ptHead = nullptr;
  ptQTask[1].tQTaskChildren.ptTail = v5;
  ptQTask[3].tQTaskChildren.ptMiddle = (struct QTask_s *)1065353216;
  ptQTask[8].ptNext = (struct QTask_s *)-923067897;
  ptQTask[8].ptPrev = (struct QTask_s *)971667286;
  ptQTask[8].tQTaskChildren.ptHead = (struct QTask_s *)2146516173;
  VectorText_Init((struct VectorText_s *)&ptQTask[8].tQTaskRefList, 9);
  ptQTask[8].tQTaskChildren.ptTail = nullptr;
  ptQTask[8].tQTaskChildren.ptMiddle = nullptr;
  memset(&ptQTask[283].tQTaskRefList, 0, 0x1B8u);
  dword_79EE5E0 = (int)Game_ptGame->ptGameScreenQTask[1].ptPrev[2].tQTaskChildren.ptHead[1].tQTaskRefList.ptTail;
  ptQTask[294].tQTaskRefList.ptHead = (struct QReference_s *)1;
  ptQTask[294].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[294].tQTaskRefList.ptTail = nullptr;
}

void __cdecl sub_5263D0(struct QTask_s *a1)
{
  struct QTask_s *ptHead; // ecx

  ptHead = Game_ptGame->ptGameScreenQTask[1].ptPrev[2].tQTaskChildren.ptHead;
  if ( isInfraEnabled || *(double *)&a1[294].tQTaskRefList.ptMiddle < 4096.0 )
    ptHead[1].tQTaskRefList.ptTail = (struct QReference_s *)dword_79EE5E0;
  else
    ptHead[1].tQTaskRefList.ptTail = (struct QReference_s *)1150917018;
}

void __cdecl sub_526410(struct QTask_s *a1)
{
  struct QTask_s *ptHead; // eax

  Text_Delete((struct StaticTilemap_s *)a1[1].ptNext);
  Text_Delete((struct StaticTilemap_s *)a1[1].tQTaskRefList.ptHead);
  Text_Delete((struct StaticTilemap_s *)a1[1].ptPrev);
  Text_Delete((struct StaticTilemap_s *)a1[1].tQTaskChildren.ptHead);
  Text_Delete((struct StaticTilemap_s *)a1[1].tQTaskChildren.ptMiddle);
  Text_Delete((struct StaticTilemap_s *)a1[1].tQTaskChildren.ptTail);
  ptHead = Game_ptGame->ptGameScreenQTask[1].ptPrev[2].tQTaskChildren.ptHead;
  isDrawInfra = false;
  ptHead[1].tQTaskRefList.ptTail = (struct QReference_s *)dword_79EE5E0;
}

// source: j/0/weapons/binocularoverlay.c:1698  [anchor-mhash]
void __cdecl BinocularOverlay_StatusDisplayHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct TransContext_s *v2; // eax

  v2 = TransContext_Create(
         (struct TransContext_s *)&ptQTask[3].tQTaskRefList.ptMiddle,
         (struct real32x9_t *)&ptQTask[1].tQTaskRefList.ptMiddle,
         (struct real64x3_t *)&ptQTask[2].tQTaskRefList.ptMiddle,
         *(float *)&ptQTask[3].tQTaskChildren.ptHead);
  TransContext_SetActiveTransContext(v2);
  BinocularOverlay_Draw(ptQTask);
  TransContext_isValid = 0;
}

// source: j/0/weapons/binocularoverlay.c:1722  [anchor-mhash]
void __cdecl BinocularOverlay_DrawHandler(struct QTask_s *ptQTask)
{
  qmemcpy(&ptQTask[2].tQTaskRefList.ptMiddle, &TransContext_tActiveTransContext.tPos, 0x18u);
  *(struct real32x3_t *)&ptQTask[3].tQTaskChildren.ptMiddle = TransContext_tActiveTransContext.tMatrix.tZ;
  BinocularOverlay_Draw(ptQTask);
}

// source: j/0/weapons/binocularoverlay.c:1742  [size]
void __cdecl BinocularOverlay_PositionOverlayHandler(struct QTask_s *ptQTask, void *pxContext)
{
  double v3; // st7
  double v4; // st7
  float Real32x3_Rotate_tTemp; // [esp+Ch] [ebp-Ch]
  float Real32x3_Rotate_tTemp_4; // [esp+10h] [ebp-8h]
  float Real32x3_Rotate_tTemp_8; // [esp+14h] [ebp-4h]

  qmemcpy(&ptQTask[2].tQTaskRefList.ptMiddle, *(void **)pxContext, 0x18u);
  qmemcpy(&ptQTask[1].tQTaskRefList.ptMiddle, *((void **)pxContext + 1), sizeof(struct QTask_s));
  Real32x3_Rotate_tTemp = (*(float *)&ptQTask[1].ptParent + *(float *)&ptQTask[1].tQTaskRefList.ptMiddle) * 0.0
                        + *(float *)&ptQTask[1].tQTaskRefList.ptTail;
  v3 = *(float *)&ptQTask[2].ptPrev + *(float *)&ptQTask[1].eQTaskType;
  ptQTask[3].tQTaskChildren.ptTail = (struct QTask_s *)1065353216;
  ptQTask[3].tQTaskRefList.ptHead = nullptr;
  ptQTask[3].tQTaskChildren.ptMiddle = nullptr;
  Real32x3_Rotate_tTemp_4 = v3 * 0.0 + *(float *)&ptQTask[2].ptNext;
  v4 = (*(float *)&ptQTask[2].tQTaskChildren.ptTail + *(float *)&ptQTask[2].tQTaskChildren.ptHead) * 0.0
     + *(float *)&ptQTask[2].tQTaskChildren.ptMiddle;
  *(float *)&ptQTask[3].tQTaskChildren.ptMiddle = Real32x3_Rotate_tTemp;
  *(float *)&ptQTask[3].tQTaskChildren.ptTail = Real32x3_Rotate_tTemp_4;
  Real32x3_Rotate_tTemp_8 = v4;
  *(float *)&ptQTask[3].tQTaskRefList.ptHead = Real32x3_Rotate_tTemp_8;
}

// source: j/0/weapons/binocularoverlay.c:1771  [anchor-hash]
void __cdecl BinocularOverlay_Open()
{
  unsigned __int16 BaseQTaskType; // ax
  unsigned __int16 v1; // si

  BaseQTaskType = QTask_GetBaseQTaskType();
  v1 = QTask_NewQTaskType("BinocularOverlay", 11792, BaseQTaskType, 0, 0);
  BinocularOverlay_eQTaskType = v1;
  QTask_LinkQTaskEventHandlerFn(v1, 0, BinocularOverlay_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 1, sub_5263D0);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 2, sub_526410);
  QTask_LinkQTaskEventHandlerFn(v1, StatusScreen_eStatusDisplayQTaskEvent, BinocularOverlay_StatusDisplayHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, Screen_eDrawQTaskEvent, BinocularOverlay_DrawHandler);
  QTask_LinkQTaskEventHandlerFn(v1, Weapon_ePositionOverlayQTaskEvent, BinocularOverlay_PositionOverlayHandler);
  BinocularOverlay_ptInfraGameSprite = GameFunctions_RegisterGameSprite("infravision.spr");
  BinocularOverlay_ptBinoGameSprite = GameFunctions_RegisterGameSprite("binoculars.spr");
  Symbol_Register(
    "TASKTYPE_BINOCULAROVERLAY",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)BinocularOverlay_eQTaskType,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
}
