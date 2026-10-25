/* f/2/pc/pc_spriteparticle.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: f/2/pc/pc_spriteparticle.c:89  [anchor-mhash]
void __cdecl SpriteParticle_Update(struct QParticleSystem_s *ptSystem)
{
  struct QTask_s *ptNext; // eax
  int v2; // eax
  char ptMiddle; // cl

  ptNext = ptSystem[1].tDynCubeObj.tQObj.tQTask.ptNext;
  if ( ptNext )
    v2 = ((int (__cdecl *)(struct real64x3_t *))ptNext)(&ptSystem->tCameraPos);
  else
    v2 = 255;
  ptMiddle = (char)ptSystem[1].tDynCubeObj.tQObj.tQTask.tQTaskRefList.ptMiddle;
  ptSystem[1].tDynCubeObj.tQObj.tQTask.tQTaskChildren.ptMiddle = (struct QTask_s *)v2;
  ptSystem[1].tDynCubeObj.tQObj.tQTask.tQTaskChildren.ptHead = (struct QTask_s *)v2;
  if ( ptMiddle )
    LOBYTE(ptSystem[1].tDynCubeObj.tQObj.tQTask.tQTaskRefList.ptMiddle) = 0;
}

// source: f/2/pc/pc_spriteparticle.c:134  [anchor-mhash]
void __cdecl SpriteParticle_Draw(struct QParticleSystem_s *ptSystem, struct real64x3_t *ptPos)
{
  struct QReference_s *ptHead; // ecx
  struct QSpriteEx_s *ptPrev; // esi
  double v4; // st7
  double *i; // ebx
  double v6; // rt0
  int v7; // eax
  int v8; // ecx
  double v9; // st7
  double v10; // st6
  double v11; // st7
  int v12; // eax
  int v13; // eax
  float v14; // ecx
  float v15; // eax
  float v16; // edx
  float v17; // eax
  float v18; // [esp-Ch] [ebp-B4h]
  float v19; // [esp-8h] [ebp-B0h]
  float v20; // [esp-4h] [ebp-ACh]
  float vX1; // [esp+10h] [ebp-98h]
  float vX1a; // [esp+10h] [ebp-98h]
  float vX1b; // [esp+10h] [ebp-98h]
  float vX1c; // [esp+10h] [ebp-98h]
  float vY1a; // [esp+18h] [ebp-90h]
  float vY1b; // [esp+18h] [ebp-90h]
  float vY1; // [esp+18h] [ebp-90h]
  float vX2; // [esp+20h] [ebp-88h]
  float vX2a; // [esp+20h] [ebp-88h]
  float vX2b; // [esp+20h] [ebp-88h]
  float vX2c; // [esp+20h] [ebp-88h]
  float ptQSpriteExa; // [esp+28h] [ebp-80h]
  float ptQSpriteExb; // [esp+28h] [ebp-80h]
  float ptQSpriteEx; // [esp+28h] [ebp-80h]
  float tProj2; // [esp+34h] [ebp-74h]
  float tProj2_4; // [esp+38h] [ebp-70h]
  float tProj1; // [esp+3Ch] [ebp-6Ch]
  float tProj1_4; // [esp+40h] [ebp-68h]
  int nSizeHalf; // [esp+44h] [ebp-64h]
  int nBrightness; // [esp+48h] [ebp-60h]
  float nBrightnessa; // [esp+48h] [ebp-60h]
  float Real32x3_Rotate_tTemp; // [esp+54h] [ebp-54h]
  float Real32x3_Rotate_tTemp_4; // [esp+58h] [ebp-50h]
  float Real32x3_Rotate_tTemp_8; // [esp+5Ch] [ebp-4Ch]
  struct QTask_s *nSpriteSize; // [esp+60h] [ebp-48h]
  int nFadeValue; // [esp+64h] [ebp-44h]
  int nFadeRate; // [esp+68h] [ebp-40h]
  float tRotatedPos; // [esp+6Ch] [ebp-3Ch]
  double tDisplacement; // [esp+78h] [ebp-30h]
  double tDisplacement_8; // [esp+80h] [ebp-28h]
  double tDisplacement_16; // [esp+88h] [ebp-20h]
  double tTmpPos1_16; // [esp+A0h] [ebp-8h]

  ptHead = ptSystem[1].tDynCubeObj.tQObj.tQTask.tQTaskRefList.ptHead;
  ptPrev = (struct QSpriteEx_s *)ptSystem[1].tDynCubeObj.tQObj.tQTask.ptPrev;
  nSpriteSize = ptSystem[1].tDynCubeObj.tQObj.tQTask.tQTaskChildren.ptTail;
  nFadeRate = (int)ptHead;
  nFadeValue = (int)ptSystem[1].tDynCubeObj.tQObj.tQTask.tQTaskChildren.ptHead;
  if ( nFadeValue )
  {
    v4 = (double)(ptSystem->nSize / 2);
    nSizeHalf = 0;
    tDisplacement = ptPos->vX - v4;
    tDisplacement_8 = ptPos->vY - v4;
    tDisplacement_16 = ptPos->vZ - v4;
    if ( ptSystem->nParticles > 0 )
    {
      for ( i = &ptSystem->atParticle->tPos.vZ; ; i += 5 )
      {
        tTmpPos1_16 = tDisplacement_16 + *i;
        v6 = tDisplacement_8 + *(i - 1);
        tRotatedPos = tDisplacement + *(i - 2) - TransContext_tActiveTransContext.tPos.vX;
        Real32x3_Rotate_tTemp = TransContext_tActiveTransContext.tMatrix.tX.vZ
                              * (tTmpPos1_16 - TransContext_tActiveTransContext.tPos.vZ)
                              + TransContext_tActiveTransContext.tMatrix.tX.vY
                              * (v6 - TransContext_tActiveTransContext.tPos.vY)
                              + TransContext_tActiveTransContext.tMatrix.tX.vX * tRotatedPos;
        Real32x3_Rotate_tTemp_4 = TransContext_tActiveTransContext.tMatrix.tY.vZ
                                * (tTmpPos1_16 - TransContext_tActiveTransContext.tPos.vZ)
                                + TransContext_tActiveTransContext.tMatrix.tY.vY
                                * (v6 - TransContext_tActiveTransContext.tPos.vY)
                                + TransContext_tActiveTransContext.tMatrix.tY.vX * tRotatedPos;
        Real32x3_Rotate_tTemp_8 = TransContext_tActiveTransContext.tMatrix.tZ.vZ
                                * (tTmpPos1_16 - TransContext_tActiveTransContext.tPos.vZ)
                                + TransContext_tActiveTransContext.tMatrix.tZ.vY
                                * (v6 - TransContext_tActiveTransContext.tPos.vY)
                                + TransContext_tActiveTransContext.tMatrix.tZ.vX * tRotatedPos;
        v7 = (__int64)Real32x3_Rotate_tTemp_8;
        if ( v7 < (int)ptHead )
          v8 = 128 - (v7 << 7) / (int)ptHead;
        else
          v8 = 0;
        nBrightness = v8;
        if ( Real32x3_Rotate_tTemp_8 > 0.0 )
        {
          if ( !v8 )
            goto LABEL_30;
          v9 = 1.0 / Real32x3_Rotate_tTemp_8;
          tProj1 = TransContext_tActiveTransContext.vScreenFOVX * Real32x3_Rotate_tTemp * v9
                 + TransContext_tActiveTransContext.vScreenOriginX;
          tProj1_4 = Real32x3_Rotate_tTemp_4 * TransContext_tActiveTransContext.vScreenFOVY * v9
                   + TransContext_tActiveTransContext.vScreenOriginY;
          v10 = (double)(int)nSpriteSize;
          tProj2 = (Real32x3_Rotate_tTemp + v10) * TransContext_tActiveTransContext.vScreenFOVX * v9
                 + TransContext_tActiveTransContext.vScreenOriginX;
          tProj2_4 = (v10 + Real32x3_Rotate_tTemp_4) * TransContext_tActiveTransContext.vScreenFOVY * v9
                   + TransContext_tActiveTransContext.vScreenOriginY;
        }
        if ( v8 )
        {
          if ( nFadeValue < 255 )
          {
            v8 = (nFadeValue * v8) >> 8;
            nBrightness = v8;
          }
          if ( v8 >= 128 )
            nBrightness = 128;
          v11 = tProj2 - tProj1;
          if ( v11 < 0.0 )
            v11 = -v11;
          if ( Real32x3_Rotate_tTemp_8 > 0.0 && v11 < 1024.0 )
            break;
        }
LABEL_30:
        if ( ++nSizeHalf >= ptSystem->nParticles )
          return;
        ptHead = (struct QReference_s *)nFadeRate;
      }
      v12 = *((_DWORD *)i + 4);
      if ( v12 )
      {
        v13 = v12 - 1;
        if ( v13 )
        {
          if ( v13 == 1 )
          {
            vX2a = (float)(__int16)(__int64)tProj1_4;
            vY1b = (float)(__int16)(__int64)tProj2;
            vX1a = (float)(__int16)(__int64)tProj2_4;
            ptQSpriteExb = (float)(__int16)(__int64)tProj1;
            QSpriteEx_SetVertices(ptPrev, ptQSpriteExb, vX1a, ptQSpriteExb, vX2a, vY1b, vX1a, vY1b, vX2a);
LABEL_29:
            nBrightnessa = (float)nBrightness;
            QSpriteEx_SetVertexColours(
              ptPrev,
              nBrightnessa,
              nBrightnessa,
              nBrightnessa,
              nBrightnessa,
              nBrightnessa,
              nBrightnessa,
              nBrightnessa,
              nBrightnessa,
              nBrightnessa,
              nBrightnessa,
              nBrightnessa,
              nBrightnessa);
            ptPrev->nPri = Viewport_GetLogZ(Real32x3_Rotate_tTemp_8);
            QSpriteEx_Register(ptPrev, 0);
            goto LABEL_30;
          }
          vX1 = (float)(__int16)(__int64)tProj2_4;
          vY1a = (float)(__int16)(__int64)tProj2;
          v20 = vX1;
          ptQSpriteExa = (float)(__int16)(__int64)tProj1;
          v14 = vY1a;
          v19 = vY1a;
          v18 = vX1;
          v15 = ptQSpriteExa;
          vX2 = (float)(__int16)(__int64)tProj1_4;
          v16 = vX2;
LABEL_28:
          QSpriteEx_SetVertices(ptPrev, v15, v16, v14, v16, v15, v18, v19, v20);
          goto LABEL_29;
        }
        vX1b = (float)(__int16)(__int64)tProj2_4;
        ptQSpriteEx = (float)(__int16)(__int64)tProj1;
        vY1 = (float)(__int16)(__int64)tProj2;
        v17 = vX1b;
        vX2b = (float)(__int16)(__int64)tProj1_4;
        v16 = vX2b;
      }
      else
      {
        vX2c = (float)(__int16)(__int64)tProj1_4;
        ptQSpriteEx = (float)(__int16)(__int64)tProj1;
        v17 = vX2c;
        vY1 = (float)(__int16)(__int64)tProj2;
        vX1c = (float)(__int16)(__int64)tProj2_4;
        v16 = vX1c;
      }
      v14 = ptQSpriteEx;
      v20 = v17;
      v19 = ptQSpriteEx;
      v18 = v17;
      v15 = vY1;
      goto LABEL_28;
    }
  }
}

// source: f/2/pc/pc_spriteparticle.c:293  [anchor-hash]
void __cdecl SpriteParticle_Open()
{
  SpriteParticle_eQTaskType = QTask_NewQTaskType("SpriteParticleSystemDynCubeObj", 224, ParticleSystem_eQTaskType, 0, 0);
  SpriteParticle_isInitialised = 1;
}

// source: f/2/pc/pc_spriteparticle.c:310  [size]
void __cdecl SpriteParticle_Close()
{
  QTask_DeleteQTaskType(SpriteParticle_eQTaskType);
  SpriteParticle_isInitialised = 0;
}

// source: f/2/pc/pc_spriteparticle.c:334  [anchor-mhash]
struct QParticleSystem_s *__cdecl SpriteParticle_New(
        struct QTask_s *ptParent,
        int nParticles,
        int nBoxSize,
        int nDepth,
        int nSpriteSize,
        int nFadeDepth,
        struct QSpriteEx_s *ptSprite,
        int (__cdecl *pfSpriteParticleFadeCallback)(struct real64x3_t *),
        struct World_s *ptWorld)
{
  struct QParticleSystem_s *result; // eax
  int v11; // ecx
  int v12; // ecx
  int v13; // edx

  result = ParticleSystem_New(
             ptParent,
             nParticles,
             nBoxSize,
             40,
             nDepth,
             SpriteParticle_Update,
             SpriteParticle_Draw,
             ptWorld,
             SpriteParticle_eQTaskType);
  result[1].tDynCubeObj.tQObj.tQTask.ptPrev = (struct QTask_s *)ptSprite;
  v11 = nBoxSize * (nDepth - 2);
  if ( nBoxSize > v11 )
    v11 = nBoxSize;
  result[1].tDynCubeObj.tQObj.tQTask.tQTaskRefList.ptHead = (struct QReference_s *)v11;
  result[1].tDynCubeObj.tQObj.tQTask.ptNext = (struct QTask_s *)pfSpriteParticleFadeCallback;
  v12 = 0;
  result[1].tDynCubeObj.tQObj.tQTask.tQTaskChildren.ptTail = (struct QTask_s *)nSpriteSize;
  LOBYTE(result[1].tDynCubeObj.tQObj.tQTask.tQTaskRefList.ptMiddle) = 1;
  if ( nParticles > 0 )
  {
    v13 = 0;
    do
    {
      *(_DWORD *)((char *)&result->atParticle[1].tPos.vX + v13) = v12++ & 3;
      v13 += 40;
    }
    while ( v12 < nParticles );
  }
  return result;
}

// source: f/2/pc/pc_spriteparticle.c:380  [size]
void __cdecl SpriteParticle_Delete(struct QParticleSystem_s *ptQParticleSystem)
{
  QTask_Delete(&ptQParticleSystem->tDynCubeObj.tQObj.tQTask);
}
