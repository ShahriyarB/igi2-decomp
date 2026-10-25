/* h/2/cutscene.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: h/2/cutscene.c:84  [anchor-callee]
void __cdecl CutScene_RegisterCutSceneCamera(
        struct CutSceneCamera_s *ptCutSceneCamera,
        int *pnCutSceneCamera,
        struct QTask_s *ptQTask,
        float *pvTime,
        float vTimeScale)
{
  unsigned __int16 v5; // dx
  struct EditCamera_s *v6; // edi
  struct QTask_s *FirstChildOfType; // eax
  struct QTask_s *NextSiblingOfType; // eax

  v5 = EditCamera_eQTaskType;
  v6 = (struct EditCamera_s *)ptQTask;
  if ( ptQTask->eQTaskType == EditCamera_eQTaskType )
  {
    do
    {
      ptCutSceneCamera[*pnCutSceneCamera].ptEditCamera = v6;
      ptCutSceneCamera[*pnCutSceneCamera].vTime = *pvTime;
      *pvTime = vTimeScale * v6->vDuration + *pvTime;
      ++*pnCutSceneCamera;
      FirstChildOfType = QTask_GetFirstChildOfType(&v6->tEditorRigidObj.tQTask, v5);
      if ( FirstChildOfType )
      {
        CutScene_RegisterCutSceneCamera(ptCutSceneCamera, pnCutSceneCamera, FirstChildOfType, pvTime, vTimeScale);
        v5 = EditCamera_eQTaskType;
      }
      NextSiblingOfType = QTask_GetNextSiblingOfType(&v6->tEditorRigidObj.tQTask, v5);
      if ( !NextSiblingOfType )
        break;
      v6 = (struct EditCamera_s *)NextSiblingOfType;
    }
    while ( NextSiblingOfType->eQTaskType == v5 );
  }
}

// source: h/2/cutscene.c:148  [anchor-mhash]
struct CutSceneCamera_s *__cdecl CutScene_GetCutSceneCamera(
        struct CutSceneCamera_s *atCutSceneCamera,
        int nTotal,
        int iActive)
{
  if ( iActive < 0 )
    iActive = 0;
  if ( iActive < nTotal )
    return &atCutSceneCamera[iActive];
  else
    return &atCutSceneCamera[nTotal - 1];
}

// source: h/2/cutscene.c:180  [anchor-callee]
double __cdecl CutScene_InterpolateScalar(
        double vValue0,
        double vValue1,
        double vValue2,
        double vValue3,
        double vTime0,
        double vTime1,
        double vTime2,
        double vTime3,
        double vTime)
{
  double v10; // st6
  double v11; // st4
  double tHermite_16; // [esp+10h] [ebp-14h]
  double tHermite_24; // [esp+18h] [ebp-Ch]
  double vValue1a = *(double *)&vValue1; // [esp+30h] [ebp+Ch] ARGSLOT
  double vValue2a = *(double *)&vValue2; // [esp+38h] [ebp+14h] ARGSLOT
  double vTime0a = *(double *)&vTime0; // [esp+48h] [ebp+24h] ARGSLOT

  vValue1a = (vValue3 - vValue1) * 0.5;
  v10 = 0.0;
  if ( vTime2 - vTime0 == 0.0 )
    vTime0a = 0.0;
  else
    vTime0a = (vTime1 - vTime0 + vTime1 - vTime0) / (vTime2 - vTime0) * ((vValue2 - vValue0) * 0.5);
  if ( vTime3 - vTime1 == 0.0 )
    v11 = 0.0;
  else
    v11 = (vTime2 - vTime1 + vTime2 - vTime1) / (vTime3 - vTime1) * vValue1a;
  tHermite_16 = vValue1 + vValue1 - (vValue2 + vValue2) + v11 + vTime0a;
  tHermite_24 = vValue2 * 3.0 - vValue1 * 3.0 - (vTime0a + vTime0a) - v11;
  vValue2a = vTime2 - vTime1;
  if ( vValue2a != 0.0 )
    v10 = (vTime - vTime1) / vValue2a;
  return vValue1 + v10 * v10 * v10 * tHermite_16 + tHermite_24 * (v10 * v10) + v10 * vTime0a;
}

// source: h/2/cutscene.c:232  [anchor-caller]
// local variable allocation has failed, the output may be wrong!
void __cdecl CutScene_InterpolateCamera(
        struct CutScene_t *ptCutScene,
        struct CutSceneCamera_s **pptCutSceneCamera,
        double vTime,
        double vTotalTime,
        char isCameraJustChanged)
{
  #pragma pack(push, 1)
  union
  {
    struct { float vTime3_4; };
    struct { char igi2_o1[4]; float v52; };
    struct { char igi2_o2[8]; float v53; };
    struct { char igi2_o3[8]; float v54; };
    struct { char igi2_o4[28]; float vHeightFactorFade; };
    struct { char igi2_o5[28]; float vHeightFactorFadea; };
    struct { char igi2_o6[28]; float vHeightFactorFadeb; };
    struct { char igi2_o7[32]; float vLightTime2; };
    struct { char igi2_o8[32]; float vLightTime2a; };
    struct { char igi2_o9[36]; float vNoise; };
    struct { char igi2_o10[36]; float vNoisea; };
    struct { char igi2_o11[44]; float vStartHeightFactorFade; };
    struct { char igi2_o12[44]; float vStartHeightFactorFadea; };
    struct { char igi2_o13[48]; float vHeightFactor; };
    struct { char igi2_o14[48]; float vHeightFactora; };
    struct { char igi2_o15[52]; float vFOV; };
    struct { char igi2_o16[52]; float vFOVa; };
    struct { char igi2_o17[56]; struct real32x9_t tOrientation; };
    struct { char igi2_o18[96]; struct real32x3_t tColor; };
    struct { char igi2_o19[108]; struct real32x9_t tShakeOrientation; };
    struct { char igi2_o20[148]; struct real64x3_t tPos; };
    struct { char igi2_o21[172]; float v72; };
    struct { char igi2_o22[176]; float vGamma; };
    struct { char igi2_o23[180]; float vBeta; };
    struct { char igi2_o24[184]; float vLightTime; };
    struct { char igi2_o25[188]; struct real32x9_t Real32x9_Multiply_tTemp; };
    char igi2_extent[228];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct EditCamera_s *ptEditCamera; // edx
  struct CutSceneCamera_s *v6; // ebx
  struct CutSceneCamera_s *v7; // ebp
  struct CutSceneCamera_s *v8; // eax
  struct EditCamera_s *v9; // esi
  struct EditCamera_s *v10; // ecx
  struct EditCamera_s *v11; // edi
  double v12; // st7
  double v13; // st7
  float vY; // eax
  float vZ; // ecx
  int iLinkQTaskID; // eax
  struct real64x3_t *p_tPos; // esi
  struct real64x3_t *p_tLastPos; // edi
  struct EditCamera_s *v19; // ecx
  int iTargetQTaskID; // eax
  struct real32x9_t *p_tOrientation; // esi
  struct real32x9_t *p_tLastOrientation; // edi
  double v23; // st7
  unsigned int v24; // ecx
  unsigned int v25; // edx
  unsigned int v26; // eax
  double v27; // st7
  int v28; // ecx
  int v29; // edx
  unsigned int v30; // eax
  double v31; // st7
  int v32; // ecx
  int v33; // edx
  unsigned int v34; // eax
  double v35; // st7
  int v36; // ecx
  int v37; // edx
  unsigned int v38; // eax
  double v39; // st7
  int v40; // ecx
  int v41; // edx
  unsigned int v42; // eax
  int v43; // ecx
  int v44; // edx
  struct CutSceneCamera_s *v45; // ecx
  struct CutSceneCamera_s *v46; // edx
  int nFilterId; // ecx
  struct EditCamera_s *v48; // eax
  struct QTask_s *ptBandFilter; // ecx
  struct QTask_s *ptLineFilter; // eax

  ptEditCamera = (*pptCutSceneCamera)->ptEditCamera;
  v6 = pptCutSceneCamera[1];
  v7 = pptCutSceneCamera[2];
  v8 = pptCutSceneCamera[3];
  v9 = v6->ptEditCamera;
  igi2_frame.vNoise = ptEditCamera->vLightTime;
  igi2_frame.vHeightFactorFade = v6->ptEditCamera->vLightTime;
  v10 = v7->ptEditCamera;
  igi2_frame.vLightTime2 = v7->ptEditCamera->vLightTime;
  v11 = v8->ptEditCamera;
  igi2_frame.vStartHeightFactorFade = 1.0;
  igi2_frame.vHeightFactor = v8->ptEditCamera->vLightTime;
  if ( igi2_frame.vNoise < 0.0 )
    igi2_frame.vNoise = ptCutScene->vLightTime;
  if ( igi2_frame.vHeightFactorFade < 0.0 )
    igi2_frame.vHeightFactorFade = ptCutScene->vLightTime;
  if ( igi2_frame.vLightTime2 < 0.0 )
    igi2_frame.vLightTime2 = ptCutScene->vLightTime;
  if ( v8->ptEditCamera->vLightTime < 0.0 )
    igi2_frame.vHeightFactor = ptCutScene->vLightTime;
  igi2_frame.tPos.vX = CutScene_InterpolateScalar(
              ptEditCamera->tPos.vX,
              v9->tPos.vX,
              v10->tPos.vX,
              v11->tPos.vX,
              (*pptCutSceneCamera)->vTime,
              v6->vTime,
              v7->vTime,
              pptCutSceneCamera[3]->vTime,
              COERCE_DOUBLE(__PAIR64__(LODWORD(vTotalTime), HIDWORD(vTime))));
  igi2_frame.tPos.vY = CutScene_InterpolateScalar(
              ptEditCamera->tPos.vY,
              v9->tPos.vY,
              v10->tPos.vY,
              v11->tPos.vY,
              (*pptCutSceneCamera)->vTime,
              v6->vTime,
              v7->vTime,
              pptCutSceneCamera[3]->vTime,
              COERCE_DOUBLE(__PAIR64__(LODWORD(vTotalTime), HIDWORD(vTime))));
  igi2_frame.tPos.vZ = CutScene_InterpolateScalar(
              ptEditCamera->tPos.vZ,
              v9->tPos.vZ,
              v10->tPos.vZ,
              v11->tPos.vZ,
              (*pptCutSceneCamera)->vTime,
              v6->vTime,
              v7->vTime,
              pptCutSceneCamera[3]->vTime,
              COERCE_DOUBLE(__PAIR64__(LODWORD(vTotalTime), HIDWORD(vTime))));
  igi2_frame.v72 = CutScene_InterpolateScalar(
          ptEditCamera->vAlpha,
          v9->vAlpha,
          v10->vAlpha,
          v11->vAlpha,
          (*pptCutSceneCamera)->vTime,
          v6->vTime,
          v7->vTime,
          pptCutSceneCamera[3]->vTime,
          COERCE_DOUBLE(__PAIR64__(LODWORD(vTotalTime), HIDWORD(vTime))));
  igi2_frame.vBeta = CutScene_InterpolateScalar(
            ptEditCamera->vBeta,
            v9->vBeta,
            v10->vBeta,
            v11->vBeta,
            (*pptCutSceneCamera)->vTime,
            v6->vTime,
            v7->vTime,
            pptCutSceneCamera[3]->vTime,
            COERCE_DOUBLE(__PAIR64__(LODWORD(vTotalTime), HIDWORD(vTime))));
  igi2_frame.vGamma = CutScene_InterpolateScalar(
             ptEditCamera->vGamma,
             v9->vGamma,
             v10->vGamma,
             v11->vGamma,
             (*pptCutSceneCamera)->vTime,
             v6->vTime,
             v7->vTime,
             pptCutSceneCamera[3]->vTime,
             COERCE_DOUBLE(__PAIR64__(LODWORD(vTotalTime), HIDWORD(vTime))));
  igi2_frame.vFOV = CutScene_InterpolateScalar(
           ptEditCamera->vFOV,
           v9->vFOV,
           v10->vFOV,
           v11->vFOV,
           (*pptCutSceneCamera)->vTime,
           v6->vTime,
           v7->vTime,
           pptCutSceneCamera[3]->vTime,
           COERCE_DOUBLE(__PAIR64__(LODWORD(vTotalTime), HIDWORD(vTime))));
  igi2_frame.vLightTime = CutScene_InterpolateScalar(
                 igi2_frame.vNoise,
                 igi2_frame.vHeightFactorFade,
                 igi2_frame.vLightTime2,
                 igi2_frame.vHeightFactor,
                 (*pptCutSceneCamera)->vTime,
                 v6->vTime,
                 v7->vTime,
                 pptCutSceneCamera[3]->vTime,
                 COERCE_DOUBLE(__PAIR64__(LODWORD(vTotalTime), HIDWORD(vTime))));
  igi2_frame.vLightTime2a = CutScene_InterpolateScalar(
                   ptEditCamera->vCameraShake,
                   v9->vCameraShake,
                   v10->vCameraShake,
                   v11->vCameraShake,
                   (*pptCutSceneCamera)->vTime,
                   v6->vTime,
                   v7->vTime,
                   pptCutSceneCamera[3]->vTime,
                   COERCE_DOUBLE(__PAIR64__(LODWORD(vTotalTime), HIDWORD(vTime))));
  igi2_frame.vNoisea = CutScene_InterpolateScalar(
              ptEditCamera->vFilterNoise,
              v9->vFilterNoise,
              v10->vFilterNoise,
              v11->vFilterNoise,
              (*pptCutSceneCamera)->vTime,
              v6->vTime,
              v7->vTime,
              pptCutSceneCamera[3]->vTime,
              COERCE_DOUBLE(__PAIR64__(LODWORD(vTotalTime), HIDWORD(vTime))));
  v12 = v7->vTime - v6->vTime;
  igi2_frame.vHeightFactorFadea = v12;
  if ( v12 != 0.0 )
  {
    if ( !ptCutScene->ptBandFilter || igi2_frame.vNoisea != 0.0 )
    {
      v13 = (*(double *)((char *)&vTime + 4) - v6->vTime) / igi2_frame.vHeightFactorFadea;
      goto LABEL_18;
    }
    if ( igi2_frame.vHeightFactorFadea > 0.5 )
    {
      v13 = (*(double *)((char *)&vTime + 4) - v6->vTime) / (igi2_frame.vHeightFactorFadea - 0.5);
      if ( v13 < 0.0 )
      {
        v13 = 0.0;
LABEL_18:
        igi2_frame.tColor.vX = (v10->tFilterColor.vX - v9->tFilterColor.vX) * v13 + v9->tFilterColor.vX;
        igi2_frame.tColor.vY = (v10->tFilterColor.vY - v9->tFilterColor.vY) * v13 + v9->tFilterColor.vY;
        igi2_frame.tColor.vZ = (v10->tFilterColor.vZ - v9->tFilterColor.vZ) * v13 + v9->tFilterColor.vZ;
        goto LABEL_20;
      }
      if ( v13 <= 1.0 )
        goto LABEL_18;
    }
    v13 = 1.0;
    goto LABEL_18;
  }
  vY = v9->tFilterColor.vY;
  vZ = v9->tFilterColor.vZ;
  igi2_frame.tColor.vX = v9->tFilterColor.vX;
  igi2_frame.tColor.vY = vY;
  igi2_frame.tColor.vZ = vZ;
LABEL_20:
  Real32x9_Create(&igi2_frame.tOrientation, igi2_frame.v72, igi2_frame.vBeta, igi2_frame.vGamma);
  iLinkQTaskID = v9->iLinkQTaskID;
  if ( iLinkQTaskID >= 0 )
  {
    if ( LOBYTE(vTime) || v9->isUpdateLink )
    {
      EditCamera_TransformRelativeToLinkQTask(
        &igi2_frame.tPos,
        &igi2_frame.tOrientation,
        &v9->tTargetPos,
        &v9->tTargetOrientation,
        iLinkQTaskID);
      p_tLastPos = &ptCutScene->tLastPos;
      p_tPos = &igi2_frame.tPos;
    }
    else
    {
      p_tPos = &ptCutScene->tLastPos;
      p_tLastPos = &igi2_frame.tPos;
    }
    qmemcpy(p_tLastPos, p_tPos, sizeof(struct real64x3_t));
  }
  v19 = pptCutSceneCamera[1]->ptEditCamera;
  iTargetQTaskID = v19->iTargetQTaskID;
  if ( iTargetQTaskID >= 0 )
  {
    if ( LOBYTE(vTime) || v19->isUpdateTarget )
    {
      EditCamera_FollowTarget(&igi2_frame.tPos, &igi2_frame.tOrientation, iTargetQTaskID);
      p_tLastOrientation = &ptCutScene->tLastOrientation;
      p_tOrientation = &igi2_frame.tOrientation;
    }
    else
    {
      p_tOrientation = &ptCutScene->tLastOrientation;
      p_tLastOrientation = &igi2_frame.tOrientation;
    }
    qmemcpy(p_tLastOrientation, p_tOrientation, sizeof(struct real32x9_t));
  }
  if ( ptCutScene->vHeightFactorFadeInTime != 0.0
    && ptCutScene->vHeightFactorFadeInTime > *(double *)((char *)&vTime + 4) )
  {
    igi2_frame.vStartHeightFactorFade = *(double *)((char *)&vTime + 4) / ptCutScene->vHeightFactorFadeInTime;
  }
  if ( ptCutScene->vHeightFactorFadeOutTime == 0.0
    || *(double *)((char *)&vTotalTime + 4) - *(double *)((char *)&vTime + 4) >= ptCutScene->vHeightFactorFadeOutTime )
  {
    v23 = 1.0;
  }
  else
  {
    v23 = (*(double *)((char *)&vTotalTime + 4) - *(double *)((char *)&vTime + 4))
        / ptCutScene->vHeightFactorFadeOutTime;
  }
  if ( igi2_frame.vStartHeightFactorFade >= v23 )
    igi2_frame.vHeightFactorFadeb = v23;
  else
    igi2_frame.vHeightFactorFadeb = igi2_frame.vStartHeightFactorFade;
  if ( igi2_frame.vHeightFactorFadeb >= 0.0 )
  {
    if ( igi2_frame.vHeightFactorFadeb > 1.0 )
      igi2_frame.vHeightFactorFadeb = 1.0;
  }
  else
  {
    igi2_frame.vHeightFactorFadeb = 0.0;
  }
  v24 = (CutScene_tRandomState.anRandom[0] >> 7) ^ CutScene_tRandomState.anRandom[2];
  v25 = v24 ^ CutScene_tRandomState.anRandom[1];
  v26 = (v24 ^ CutScene_tRandomState.anRandom[1]) + CutScene_tRandomState.anRandom[0];
  v27 = (double)(unsigned __int16)((v24 ^ LOWORD(CutScene_tRandomState.anRandom[1]))
                                 + LOWORD(CutScene_tRandomState.anRandom[0]));
  v28 = (v26 >> 7) ^ v24;
  v29 = v28 ^ v25;
  v30 = v29 + v26;
  igi2_frame.tPos.vX = (0.5 - v27 * 0.0000152587890625) * igi2_frame.vLightTime2a * 4096.0 + igi2_frame.tPos.vX;
  v31 = (double)(unsigned __int16)v30;
  v32 = (v30 >> 7) ^ v28;
  v33 = v32 ^ v29;
  v34 = v33 + v30;
  igi2_frame.tPos.vY = (0.5 - v31 * 0.0000152587890625) * igi2_frame.vLightTime2a * 4096.0 + igi2_frame.tPos.vY;
  v35 = (double)(unsigned __int16)v34;
  v36 = (v34 >> 7) ^ v32;
  v37 = v36 ^ v33;
  v38 = v37 + v34;
  igi2_frame.tPos.vZ = (0.5 - v35 * 0.0000152587890625) * igi2_frame.vLightTime2a * 4096.0 + igi2_frame.tPos.vZ;
  v39 = (double)(unsigned __int16)v38 * 0.0000152587890625;
  v40 = (v38 >> 7) ^ v36;
  v41 = v40 ^ v37;
  v42 = v41 + v38;
  v43 = (v42 >> 7) ^ v40;
  v44 = v43 ^ v41;
  CutScene_tRandomState.anRandom[0] = v44 + v42;
  igi2_frame.v53 = (0.5 - v39) * igi2_frame.vLightTime2a * 0.5340707898139954;
  CutScene_tRandomState.anRandom[2] = v43;
  CutScene_tRandomState.anRandom[1] = v44;
  igi2_frame.v52 = (0.5 - (double)(unsigned __int16)v42 * 0.0000152587890625) * igi2_frame.vLightTime2a * 0.5340707898139954;
  igi2_frame.vTime3_4 = (0.5 - (double)(unsigned __int16)(v44 + v42) * 0.0000152587890625) * igi2_frame.vLightTime2a * 0.5340707898139954;
  Real32x9_Create(&igi2_frame.tShakeOrientation, igi2_frame.vTime3_4, igi2_frame.v52, igi2_frame.v53);
  igi2_frame.Real32x9_Multiply_tTemp.tX.vX = igi2_frame.tShakeOrientation.tZ.vX * igi2_frame.tOrientation.tX.vZ
                                + igi2_frame.tShakeOrientation.tY.vX * igi2_frame.tOrientation.tX.vY
                                + igi2_frame.tShakeOrientation.tX.vX * igi2_frame.tOrientation.tX.vX;
  igi2_frame.Real32x9_Multiply_tTemp.tX.vY = igi2_frame.tShakeOrientation.tZ.vY * igi2_frame.tOrientation.tX.vZ
                                + igi2_frame.tShakeOrientation.tY.vY * igi2_frame.tOrientation.tX.vY
                                + igi2_frame.tShakeOrientation.tX.vY * igi2_frame.tOrientation.tX.vX;
  igi2_frame.Real32x9_Multiply_tTemp.tX.vZ = igi2_frame.tShakeOrientation.tZ.vZ * igi2_frame.tOrientation.tX.vZ
                                + igi2_frame.tShakeOrientation.tY.vZ * igi2_frame.tOrientation.tX.vY
                                + igi2_frame.tShakeOrientation.tX.vZ * igi2_frame.tOrientation.tX.vX;
  igi2_frame.Real32x9_Multiply_tTemp.tY.vX = igi2_frame.tOrientation.tY.vZ * igi2_frame.tShakeOrientation.tZ.vX
                                + igi2_frame.tOrientation.tY.vY * igi2_frame.tShakeOrientation.tY.vX
                                + igi2_frame.tOrientation.tY.vX * igi2_frame.tShakeOrientation.tX.vX;
  igi2_frame.Real32x9_Multiply_tTemp.tY.vY = igi2_frame.tOrientation.tY.vZ * igi2_frame.tShakeOrientation.tZ.vY
                                + igi2_frame.tOrientation.tY.vY * igi2_frame.tShakeOrientation.tY.vY
                                + igi2_frame.tOrientation.tY.vX * igi2_frame.tShakeOrientation.tX.vY;
  igi2_frame.Real32x9_Multiply_tTemp.tY.vZ = igi2_frame.tOrientation.tY.vZ * igi2_frame.tShakeOrientation.tZ.vZ
                                + igi2_frame.tOrientation.tY.vY * igi2_frame.tShakeOrientation.tY.vZ
                                + igi2_frame.tOrientation.tY.vX * igi2_frame.tShakeOrientation.tX.vZ;
  igi2_frame.Real32x9_Multiply_tTemp.tZ.vX = igi2_frame.tOrientation.tZ.vZ * igi2_frame.tShakeOrientation.tZ.vX
                                + igi2_frame.tOrientation.tZ.vY * igi2_frame.tShakeOrientation.tY.vX
                                + igi2_frame.tOrientation.tZ.vX * igi2_frame.tShakeOrientation.tX.vX;
  igi2_frame.Real32x9_Multiply_tTemp.nOps = igi2_frame.tShakeOrientation.nOps + igi2_frame.tOrientation.nOps + 1;
  igi2_frame.Real32x9_Multiply_tTemp.tZ.vY = igi2_frame.tOrientation.tZ.vZ * igi2_frame.tShakeOrientation.tZ.vY
                                + igi2_frame.tOrientation.tZ.vY * igi2_frame.tShakeOrientation.tY.vY
                                + igi2_frame.tOrientation.tZ.vX * igi2_frame.tShakeOrientation.tX.vY;
  igi2_frame.Real32x9_Multiply_tTemp.tZ.vZ = igi2_frame.tOrientation.tZ.vZ * igi2_frame.tShakeOrientation.tZ.vZ
                                + igi2_frame.tOrientation.tZ.vY * igi2_frame.tShakeOrientation.tY.vZ
                                + igi2_frame.tOrientation.tZ.vX * igi2_frame.tShakeOrientation.tX.vZ;
  qmemcpy(&igi2_frame.tOrientation, &igi2_frame.Real32x9_Multiply_tTemp, sizeof(igi2_frame.tOrientation));
  igi2_frame.vHeightFactora = igi2_frame.vHeightFactorFadeb * ptCutScene->vHeightFactor + 1.0 - igi2_frame.vHeightFactorFadeb;
  QCamera_Set(
    CutScene_ptDefaultQCamera,
    &igi2_frame.tPos,
    &igi2_frame.tOrientation,
    igi2_frame.vFOV,
    1.0,
    1000.0,
    Screen_nFrameNumber,
    nullptr,
    igi2_frame.vLightTime,
    0);
  if ( !ptCutScene->isRunByAnimtask )
  {
    if ( CutScene_ptQViewportQTask && LOBYTE(vTime) )
    {
      if ( ptCutScene->ptLineFilter )
      {
        QTask_Delete(ptCutScene->ptLineFilter);
        ptCutScene->ptLineFilter = nullptr;
      }
      v45 = pptCutSceneCamera[1];
      if ( v45->ptEditCamera->nFilterId == 1 )
        ptCutScene->ptLineFilter = LineFilter_New(
                                     &CutScene_ptQViewportQTask->tQTask,
                                     v45->ptEditCamera->tFilterColor.vX,
                                     v45->ptEditCamera->tFilterColor.vY,
                                     v45->ptEditCamera->tFilterColor.vZ,
                                     614.4000244140625,
                                     1);
      if ( pptCutSceneCamera[1]->ptEditCamera->nFilterId == 3 )
        BandFilter_UpdateCameraNr();
      if ( ptCutScene->ptBandFilter )
      {
        QTask_Delete(ptCutScene->ptBandFilter);
        ptCutScene->ptBandFilter = nullptr;
      }
      v46 = pptCutSceneCamera[1];
      nFilterId = v46->ptEditCamera->nFilterId;
      if ( nFilterId == 2 || nFilterId == 3 )
        ptCutScene->ptBandFilter = BandFilter_New(
                                     &CutScene_ptQViewportQTask->tQTask,
                                     614.4000244140625,
                                     v46->ptEditCamera->tFilterColor.vX,
                                     v46->ptEditCamera->tFilterColor.vY,
                                     v46->ptEditCamera->tFilterColor.vZ,
                                     60,
                                     90,
                                     igi2_frame.vNoisea);
      if ( ptCutScene->ptHandiCamFilter )
      {
        QTask_Delete(ptCutScene->ptHandiCamFilter);
        ptCutScene->ptHandiCamFilter = nullptr;
      }
      v48 = pptCutSceneCamera[1]->ptEditCamera;
      if ( v48->nFilterId == 4 )
        ptCutScene->ptHandiCamFilter = HandiCamFilter_New(
                                         &CutScene_ptQViewportQTask->tQTask,
                                         v48->tFilterColor.vX,
                                         v48->tFilterColor.vY,
                                         v48->tFilterColor.vZ,
                                         614.4000244140625);
    }
    ptBandFilter = ptCutScene->ptBandFilter;
    if ( ptBandFilter )
      BandFilter_SetColor(ptBandFilter, igi2_frame.tColor.vX, igi2_frame.tColor.vY, igi2_frame.tColor.vZ);
    ptLineFilter = ptCutScene->ptLineFilter;
    if ( ptLineFilter )
      *(float *)&ptLineFilter[1].tQTaskChildren.ptTail = igi2_frame.vNoisea;
    if ( !CutScene_ptQViewportQTask || igi2_frame.vHeightFactora == 1.0 )
    {
      if ( ptCutScene->ptBorderFilter )
      {
        QTask_Delete(ptCutScene->ptBorderFilter);
        ptCutScene->ptBorderFilter = nullptr;
      }
    }
    else
    {
      igi2_frame.vStartHeightFactorFadea = (double)Display_tActiveMode.nHeight + 1.0;
      if ( !ptCutScene->ptBorderFilter )
      {
        igi2_frame.v54 = (1.0 - igi2_frame.vHeightFactora) * igi2_frame.vStartHeightFactorFadea * 0.5 + 1.0;
        igi2_frame.vFOVa = (double)Display_tActiveMode.nWidth + 1.0;
        ptCutScene->ptBorderFilter = WideScreenFilter_New(
                                       &CutScene_ptQViewportQTask->tQTask,
                                       0.0,
                                       0.0,
                                       0.0,
                                       409.6000061035156,
                                       igi2_frame.vFOVa,
                                       igi2_frame.vStartHeightFactorFadea,
                                       0.0,
                                       0.0,
                                       igi2_frame.v54);
      }
    }
  }
}

// source: h/2/cutscene.c:668  [anchor-callee]
void __cdecl CutScene_AdjustAngles(struct CutSceneCamera_s *ptCutSceneCamera, int nCutSceneCamera)
{
  struct CutSceneCamera_s *v2; // ecx
  int v3; // esi
  float *i; // edx
  float *j; // edx
  float *k; // edx
  float *m; // edx
  float *n; // edx
  float *ii; // edx
  float v10; // edx
  float vAlpha; // [esp+4h] [ebp-Ch]
  float vBeta; // [esp+8h] [ebp-8h]
  float vGamma; // [esp+Ch] [ebp-4h]

  vAlpha = ptCutSceneCamera->ptEditCamera->vAlpha;
  vBeta = ptCutSceneCamera->ptEditCamera->vBeta;
  vGamma = ptCutSceneCamera->ptEditCamera->vGamma;
  if ( nCutSceneCamera > 1 )
  {
    v2 = ptCutSceneCamera + 1;
    v3 = nCutSceneCamera - 1;
    do
    {
      for ( i = &v2->ptEditCamera->vAlpha; *i - vAlpha > 3.1415926535897944; i = &v2->ptEditCamera->vAlpha )
        *i = *i - 6.2831854820251465;
      for ( j = &v2->ptEditCamera->vAlpha; *j - vAlpha < -3.1415926535897944; j = &v2->ptEditCamera->vAlpha )
        *j = *j + 6.2831854820251465;
      vAlpha = v2->ptEditCamera->vAlpha;
      for ( k = &v2->ptEditCamera->vBeta; *k - vBeta > 3.1415926535897944; k = &v2->ptEditCamera->vBeta )
        *k = *k - 6.2831854820251465;
      for ( m = &v2->ptEditCamera->vBeta; *m - vBeta < -3.1415926535897944; m = &v2->ptEditCamera->vBeta )
        *m = *m + 6.2831854820251465;
      vBeta = v2->ptEditCamera->vBeta;
      for ( n = &v2->ptEditCamera->vGamma; *n - vGamma > 3.1415926535897944; n = &v2->ptEditCamera->vGamma )
        *n = *n - 6.2831854820251465;
      for ( ii = &v2->ptEditCamera->vGamma; *ii - vGamma < -3.1415926535897944; ii = &v2->ptEditCamera->vGamma )
        *ii = *ii + 6.2831854820251465;
      v10 = v2->ptEditCamera->vGamma;
      ++v2;
      --v3;
      vGamma = v10;
    }
    while ( v3 );
  }
}

// source: h/2/cutscene.c:729  [anchor-caller]
void __cdecl CutScene_SetCamera(struct CutScene_t *ptCutScene)
{
  #pragma pack(push, 1)
  union
  {
    struct { _BYTE v16[20]; };
    struct { char igi2_o1[16]; float vTimeScale; };
    struct { char igi2_o2[40]; float vTotalTime; };
    struct { char igi2_o3[44]; float vTime; };
    struct { char igi2_o4[48]; int nCutSceneCamera; };
    struct { char igi2_o5[52]; struct CutSceneCamera_s *aptFinalCutSceneCamera[4]; };
    struct { char igi2_o6[72]; int isCameraJustChanged; };
    struct { char igi2_o7[76]; struct CutSceneCamera_s atCutSceneCamera[100]; };
    char igi2_extent[876];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  unsigned __int16 v1; // dx
  double nTick; // st7
  char v3; // bl
  int v4; // esi
  struct QTask_s *FirstChildOfType; // eax
  int v6; // edi
  int i; // ecx
  double v8; // st7
  int v9; // eax
  struct CutSceneCamera_s *v10; // ebx
  int v11; // eax
  struct CutSceneCamera_s *v12; // edx
  int v13; // eax
  struct CutSceneCamera_s *v14; // ecx
  int v15; // eax

  *(float *)igi2_frame.aptFinalCutSceneCamera = (float)CutScene_nFrequency;
  v1 = EditCamera_eQTaskType;
  nTick = (double)ptCutScene->nTick;
  v3 = 0;
  igi2_frame.nCutSceneCamera = 0;
  v4 = -1;
  LOBYTE(igi2_frame.isCameraJustChanged) = 0;
  igi2_frame.vTotalTime = 0.0;
  igi2_frame.vTime = nTick / *(float *)igi2_frame.aptFinalCutSceneCamera;
  if ( QTask_GetFirstChildOfType(&ptCutScene->tEditorRigidObj.tQTask, EditCamera_eQTaskType) )
  {
    igi2_frame.vTimeScale = ptCutScene->vTimeScale;
    FirstChildOfType = QTask_GetFirstChildOfType(&ptCutScene->tEditorRigidObj.tQTask, v1);
    CutScene_RegisterCutSceneCamera(igi2_frame.atCutSceneCamera, &igi2_frame.nCutSceneCamera, FirstChildOfType, &igi2_frame.vTotalTime, igi2_frame.vTimeScale);
    if ( igi2_frame.nCutSceneCamera )
    {
      CutScene_AdjustAngles(igi2_frame.atCutSceneCamera, igi2_frame.nCutSceneCamera);
      v6 = igi2_frame.nCutSceneCamera;
      for ( i = 0; i < igi2_frame.nCutSceneCamera; ++i )
      {
        if ( v3 )
          break;
        if ( igi2_frame.atCutSceneCamera[i].vTime > (double)igi2_frame.vTime )
          v3 = 1;
        else
          v4 = i;
      }
      if ( igi2_frame.vTime > (double)igi2_frame.vTotalTime )
      {
        v8 = *(float *)igi2_frame.aptFinalCutSceneCamera;
        ptCutScene->isFinished = 1;
        *(_QWORD *)igi2_frame.aptFinalCutSceneCamera = (__int64)(v8 * igi2_frame.vTotalTime);
        ptCutScene->nTick = (int)igi2_frame.aptFinalCutSceneCamera[0];
        ptCutScene->iLastLastActive = -1;
      }
      if ( ptCutScene->iLastLastActive != v4 )
      {
        ptCutScene->iLastLastActive = v4;
        LOBYTE(igi2_frame.isCameraJustChanged) = 1;
      }
      v9 = v4 - 1;
      if ( v4 - 1 < 0 )
        v9 = 0;
      if ( v9 >= v6 )
        v9 = v6 - 1;
      v10 = &igi2_frame.atCutSceneCamera[v9];
      igi2_frame.aptFinalCutSceneCamera[0] = v10;
      v11 = v4;
      if ( v4 < 0 )
        v11 = 0;
      if ( v11 >= v6 )
        v11 = v6 - 1;
      v12 = &igi2_frame.atCutSceneCamera[v11];
      v13 = v4 + 1;
      igi2_frame.aptFinalCutSceneCamera[1] = v12;
      if ( v4 + 1 < 0 )
        v13 = 0;
      if ( v13 >= v6 )
        v13 = v6 - 1;
      v14 = &igi2_frame.atCutSceneCamera[v13];
      v15 = v4 + 2;
      igi2_frame.aptFinalCutSceneCamera[2] = v14;
      if ( v4 + 2 < 0 )
        v15 = 0;
      if ( v15 >= v6 )
        v15 = v6 - 1;
      igi2_frame.aptFinalCutSceneCamera[3] = &igi2_frame.atCutSceneCamera[v15];
      if ( !v10->ptEditCamera->isSmoothToNext )
        igi2_frame.aptFinalCutSceneCamera[0] = v12;
      if ( !v12->ptEditCamera->isSmoothToNext )
      {
        v14 = v12;
        igi2_frame.aptFinalCutSceneCamera[2] = v12;
      }
      if ( !v14->ptEditCamera->isSmoothToNext )
        igi2_frame.aptFinalCutSceneCamera[3] = v14;
      *(double *)&igi2_frame.v16[12] = igi2_frame.vTotalTime;
      *(double *)&igi2_frame.v16[4] = igi2_frame.vTime;
      *(_DWORD *)igi2_frame.v16 = igi2_frame.isCameraJustChanged;
      CutScene_InterpolateCamera(
        ptCutScene,
        igi2_frame.aptFinalCutSceneCamera,
        *(double *)igi2_frame.v16,
        *(double *)&igi2_frame.v16[8],
        BYTE4(igi2_frame.vTotalTime));
    }
  }
}

// source: h/2/cutscene.c:884  [anchor-mhash]
void __cdecl CutScene_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *v2; // esi

  ptQTask[3].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[3].tQTaskChildren.ptTail = nullptr;
  ptQTask[3].tQTaskRefList.ptHead = nullptr;
  ptQTask[5].tQTaskChildren.ptHead = nullptr;
  ptQTask[5].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[5].tQTaskChildren.ptTail = nullptr;
  ptQTask[5].tQTaskRefList.ptHead = nullptr;
  ptQTask[7].tQTaskChildren.ptHead = nullptr;
  ptQTask[7].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[7].tQTaskChildren.ptTail = nullptr;
  ptQTask[7].tQTaskRefList.ptHead = nullptr;
  ptQTask[9].tQTaskChildren.ptHead = nullptr;
  ptQTask[9].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[9].tQTaskChildren.ptTail = nullptr;
  ptQTask[9].tQTaskRefList.ptHead = nullptr;
  ptQTask[11].tQTaskChildren.ptHead = nullptr;
  ptQTask[11].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[11].tQTaskChildren.ptTail = nullptr;
  ptQTask[11].tQTaskRefList.ptHead = nullptr;
  ptQTask[13].tQTaskChildren.ptHead = nullptr;
  v2 = (struct QTask_s *)CutScene_ptDefaultQCamera;
  ptQTask[1].tQTaskRefList.ptMiddle = (struct QReference_s *)1065353216;
  ptQTask[2].ptNext = (struct QTask_s *)1065353216;
  ptQTask[2].tQTaskChildren.ptTail = (struct QTask_s *)1065353216;
  ptQTask[3].ptNext = (struct QTask_s *)1065353216;
  *(_DWORD *)&ptQTask[2].eQTaskType = 1065353216;
  ptQTask[15].tQTaskChildren.ptHead = v2;
  ptQTask[1].ptNext = nullptr;
  ptQTask[1].ptPrev = nullptr;
  ptQTask[1].tQTaskChildren.ptHead = nullptr;
  ptQTask[1].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[1].tQTaskChildren.ptTail = nullptr;
  ptQTask[1].tQTaskRefList.ptHead = nullptr;
  ptQTask[1].tQTaskRefList.ptTail = nullptr;
  ptQTask[1].ptParent = nullptr;
  *(_DWORD *)&ptQTask[1].eQTaskType = 0;
  ptQTask[2].ptPrev = nullptr;
  ptQTask[2].tQTaskChildren.ptHead = nullptr;
  ptQTask[2].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[2].tQTaskRefList.ptHead = nullptr;
  BYTE2(ptQTask[2].tQTaskRefList.ptMiddle) = 0;
  LOBYTE(ptQTask[2].tQTaskRefList.ptMiddle) = 0;
  BYTE1(ptQTask[15].tQTaskRefList.ptTail) = 1;
  BYTE1(ptQTask[2].tQTaskRefList.ptMiddle) = 0;
  ptQTask[2].tQTaskRefList.ptTail = nullptr;
  ptQTask[2].ptParent = nullptr;
  ptQTask[13].tQTaskChildren.ptTail = nullptr;
  ptQTask[13].tQTaskChildren.ptMiddle = (struct QTask_s *)-1;
  ptQTask[15].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[15].tQTaskRefList.ptHead = nullptr;
  ptQTask[15].tQTaskChildren.ptTail = nullptr;
  ptQTask[15].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[15].ptParent = (struct QTask_s *)-1;
}

// source: h/2/cutscene.c:954  [size]
void __cdecl CutScene_GetSerializeParameterListHandler(
        struct QTask_s *ptQTask,
        struct GetSerializeParameterListContext_s *ptGetSerializeParameterListContext)
{
  ptGetSerializeParameterListContext->tReturn.ptParameterList = CutScene_ptSerializeParameterList;
}

// source: h/2/cutscene.c:967  [anchor-refs]
void __cdecl CutScene_RegisterScriptSymbolsHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { char zName[64]; };
    struct { char igi2_o1[64]; char zTemp[128]; };
    char igi2_extent[192];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)

  if ( !BYTE2(ptQTask[2].tQTaskRefList.ptMiddle) )
  {
    BYTE2(ptQTask[2].tQTaskRefList.ptMiddle) = 1;
    Level_GetUniqueQTaskNameFromTask(igi2_frame.zName, ptQTask);
    sprintf(igi2_frame.zTemp, "%s.isRun", igi2_frame.zName);
    Symbol_Register(
      igi2_frame.zTemp,
      (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_Int8,
      &ptQTask[2].tQTaskRefList.ptMiddle,
      1,
      QSCRIPT_SYMBOLCLASS_VARIABLE,
      QSCRIPT_SYMBOLTYPE_INT,
      QSCRIPT_SYMBOLLIFESPAN_FINITE);
    sprintf(igi2_frame.zTemp, "%s.isFinished", igi2_frame.zName);
    Symbol_Register(
      igi2_frame.zTemp,
      (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_Int8,
      (char *)&ptQTask[2].tQTaskRefList.ptMiddle + 1,
      1,
      QSCRIPT_SYMBOLCLASS_VARIABLE,
      QSCRIPT_SYMBOLTYPE_INT,
      QSCRIPT_SYMBOLLIFESPAN_FINITE);
    sprintf(igi2_frame.zTemp, "%s.nTick", igi2_frame.zName);
    Symbol_Register(
      igi2_frame.zTemp,
      (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_Int,
      &ptQTask[2].tQTaskRefList.ptTail,
      4,
      QSCRIPT_SYMBOLCLASS_VARIABLE,
      QSCRIPT_SYMBOLTYPE_INT,
      QSCRIPT_SYMBOLLIFESPAN_FINITE);
  }
}

// source: h/2/cutscene.c:1003  [anchor-mhash]
void __cdecl CutScene_RemoveScriptSymbolsHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { char zName[64]; };
    struct { char igi2_o1[64]; char zTemp[128]; };
    char igi2_extent[192];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)

  if ( BYTE2(ptQTask[2].tQTaskRefList.ptMiddle) )
  {
    Level_GetUniqueQTaskNameFromTask(igi2_frame.zName, ptQTask);
    BYTE2(ptQTask[2].tQTaskRefList.ptMiddle) = 0;
    sprintf(igi2_frame.zTemp, "%s.isRun", igi2_frame.zName);
    Symbol_Remove(igi2_frame.zTemp);
    sprintf(igi2_frame.zTemp, "%s.isFinished", igi2_frame.zName);
    Symbol_Remove(igi2_frame.zTemp);
    sprintf(igi2_frame.zTemp, "%s.nTick", igi2_frame.zName);
    Symbol_Remove(igi2_frame.zTemp);
    BYTE2(ptQTask[2].tQTaskRefList.ptMiddle) = 0;
  }
}

// source: h/2/cutscene.c:1043  [anchor-mhash]
void __cdecl CutScene_DeleteHandler(struct QTask_s *ptQTask)
{
  int v1; // ecx
  struct QReference_s *v2; // eax
  void (__cdecl *pfHandler)(struct QTask_s *); // eax

  v1 = 0;
  while ( 1 )
  {
    v2 = Level_atLevelQTaskID[v1];
    if ( v2 )
    {
      if ( v2->pxObject == ptQTask )
        break;
    }
    if ( ++v1 >= 4096 )
      goto LABEL_9;
  }
  if ( v1 >= 0 )
  {
    pfHandler = (void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[Level_eRemoveLevelScriptSymbolsEvent][ptQTask->eQTaskType].pfHandler;
    if ( pfHandler )
      pfHandler(ptQTask);
  }
LABEL_9:
  Level_DeinitLevelExpression((struct LevelExpression_s *)&ptQTask[3].tQTaskChildren.ptMiddle);
  Level_DeinitLevelExpression((struct LevelExpression_s *)&ptQTask[5].tQTaskChildren.ptMiddle);
  Level_DeinitLevelExpression((struct LevelExpression_s *)&ptQTask[7].tQTaskChildren.ptMiddle);
  Level_DeinitLevelExpression((struct LevelExpression_s *)&ptQTask[9].tQTaskChildren.ptMiddle);
  Level_DeinitLevelExpression((struct LevelExpression_s *)&ptQTask[11].tQTaskChildren.ptMiddle);
  if ( ptQTask[15].tQTaskChildren.ptMiddle )
  {
    QTask_Delete(ptQTask[15].tQTaskChildren.ptMiddle);
    ptQTask[15].tQTaskChildren.ptMiddle = nullptr;
  }
  if ( ptQTask[15].tQTaskRefList.ptHead )
  {
    QTask_Delete((struct QTask_s *)ptQTask[15].tQTaskRefList.ptHead);
    ptQTask[15].tQTaskRefList.ptHead = nullptr;
  }
  if ( ptQTask[15].tQTaskRefList.ptMiddle )
  {
    QTask_Delete((struct QTask_s *)ptQTask[15].tQTaskRefList.ptMiddle);
    ptQTask[15].tQTaskRefList.ptMiddle = nullptr;
  }
  if ( ptQTask[15].tQTaskChildren.ptTail )
  {
    QTask_Delete(ptQTask[15].tQTaskChildren.ptTail);
    ptQTask[15].tQTaskChildren.ptTail = nullptr;
  }
}

// source: h/2/cutscene.c:1106  [size]
void __cdecl CutScene_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = CutScene_ptParameterList;
}

// source: h/2/cutscene.c:1122  [anchor-caller]
void __cdecl CutScene_RunHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptHead; // ecx
  int v2; // edx
  struct QTask_s *v3; // eax
  void (__cdecl *pfHandler)(struct QTask_s *); // eax
  int v5; // edx
  struct QTask_s *ptMiddle; // ecx
  struct QTask_s *v7; // eax
  double v8; // st7
  struct QReference_s *ptTail; // ecx
  int v10; // eax
  struct QTask_s *v11; // ecx

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
  if ( ptQTask[3].tQTaskChildren.ptMiddle && ptQTask[3].tQTaskChildren.ptTail->ptNext && ptQTask[3].tQTaskRefList.ptHead )
    LOBYTE(ptQTask[2].tQTaskRefList.ptMiddle) = (__int64)Level_RunLevelExpression(
                                                           (struct LevelExpression_s *)&ptQTask[3].tQTaskChildren.ptMiddle,
                                                           ptQTask);
  else
    LOBYTE(ptQTask[2].tQTaskRefList.ptMiddle) = 1;
  ptMiddle = ptQTask[5].tQTaskChildren.ptMiddle;
  CutScene_isRunning |= SLOBYTE(ptQTask[2].tQTaskRefList.ptMiddle);
  if ( ptMiddle
    && ptQTask[5].tQTaskChildren.ptTail->ptNext
    && ptQTask[5].tQTaskRefList.ptHead
    && (unsigned __int8)(__int64)Level_RunLevelExpression(
                                   (struct LevelExpression_s *)&ptQTask[5].tQTaskChildren.ptMiddle,
                                   ptQTask) )
  {
    ptQTask[2].tQTaskRefList.ptTail = nullptr;
    BYTE1(ptQTask[2].tQTaskRefList.ptMiddle) = 0;
  }
  v7 = (struct QTask_s *)Screen_nFrameNumber;
  if ( BYTE1(ptQTask[15].tQTaskRefList.ptTail) )
  {
    if ( LOBYTE(ptQTask[2].tQTaskRefList.ptMiddle) )
    {
LABEL_24:
      LOBYTE(ptQTask[15].tQTaskRefList.ptTail) = 0;
      CutScene_SetCamera((struct CutScene_t *)ptQTask);
      if ( ptQTask[7].tQTaskChildren.ptMiddle
        && ptQTask[7].tQTaskChildren.ptTail->ptNext
        && ptQTask[7].tQTaskRefList.ptHead )
      {
        v8 = Level_RunLevelExpression((struct LevelExpression_s *)&ptQTask[7].tQTaskChildren.ptMiddle, ptQTask);
        ptTail = ptQTask[2].tQTaskRefList.ptTail;
        v10 = (__int64)(v8 * (double)CutScene_nFrequency);
        ptQTask[2].tQTaskRefList.ptTail = (struct QReference_s *)((char *)ptTail + v10);
        if ( (int)ptTail + v10 < 0 )
          ptQTask[2].tQTaskRefList.ptTail = nullptr;
      }
      else
      {
        ++*(int *)&ptQTask[2].tQTaskRefList.ptTail;
      }
      goto LABEL_39;
    }
    ptQTask[15].ptParent = (struct QTask_s *)Screen_nFrameNumber;
  }
  if ( LOBYTE(ptQTask[2].tQTaskRefList.ptMiddle) )
    goto LABEL_24;
  if ( ptQTask[15].ptParent != v7 )
  {
    if ( ptQTask[15].tQTaskChildren.ptTail )
    {
      QTask_Delete(ptQTask[15].tQTaskChildren.ptTail);
      ptQTask[15].tQTaskChildren.ptTail = nullptr;
    }
    if ( ptQTask[15].tQTaskChildren.ptMiddle )
    {
      QTask_Delete(ptQTask[15].tQTaskChildren.ptMiddle);
      ptQTask[15].tQTaskChildren.ptMiddle = nullptr;
    }
    if ( ptQTask[15].tQTaskRefList.ptHead )
    {
      QTask_Delete((struct QTask_s *)ptQTask[15].tQTaskRefList.ptHead);
      ptQTask[15].tQTaskRefList.ptHead = nullptr;
    }
    if ( ptQTask[15].tQTaskRefList.ptMiddle )
    {
      QTask_Delete((struct QTask_s *)ptQTask[15].tQTaskRefList.ptMiddle);
      ptQTask[15].tQTaskRefList.ptMiddle = nullptr;
    }
  }
LABEL_39:
  if ( BYTE1(ptQTask[15].tQTaskRefList.ptTail) )
    goto LABEL_54;
  if ( LOBYTE(ptQTask[2].tQTaskRefList.ptMiddle) )
  {
    v11 = ptQTask[9].tQTaskChildren.ptMiddle;
    isDrawInfra = false;
    if ( v11 )
    {
      if ( ptQTask[9].tQTaskChildren.ptTail->ptNext && ptQTask[9].tQTaskRefList.ptHead )
        Level_RunLevelExpression((struct LevelExpression_s *)&ptQTask[9].tQTaskChildren.ptMiddle, ptQTask);
    }
  }
  if ( BYTE1(ptQTask[15].tQTaskRefList.ptTail) )
  {
LABEL_54:
    if ( !LOBYTE(ptQTask[2].tQTaskRefList.ptMiddle)
      && ptQTask[11].tQTaskChildren.ptMiddle
      && ptQTask[11].tQTaskChildren.ptTail->ptNext
      && ptQTask[11].tQTaskRefList.ptHead )
    {
      Level_RunLevelExpression((struct LevelExpression_s *)&ptQTask[11].tQTaskChildren.ptMiddle, ptQTask);
    }
  }
  BYTE1(ptQTask[15].tQTaskRefList.ptTail) = ptQTask[2].tQTaskRefList.ptMiddle;
}

// source: h/2/cutscene.c:1240  [anchor-mhash]
void __cdecl CutScene_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *ptHead; // eax
  int v3; // edx
  struct QTask_s *v4; // ecx
  void (__cdecl *pfHandler)(struct QTask_s *, _DWORD); // ecx
  int v6; // edx

  if ( *(float *)&ptQTask[3].ptPrev < 0.0 )
    ptQTask[3].ptPrev = nullptr;
  if ( *(float *)&ptQTask[3].tQTaskChildren.ptHead < 0.0 )
    ptQTask[3].tQTaskChildren.ptHead = nullptr;
  ptQTask[2].tQTaskRefList.ptTail = (struct QReference_s *)(__int64)((double)CutScene_nFrequency
                                                                   * *(float *)&ptQTask[2].ptParent);
  if ( !pxContext || !*(_DWORD *)pxContext )
  {
    ptHead = ptQTask->tQTaskChildren.ptHead;
    if ( ptHead->ptNext )
    {
      if ( ptHead )
      {
        v3 = QTask_nProtectedQTaskStackOffset;
        do
        {
          if ( ptHead->ptNext )
            v4 = ptHead->ptNext->ptNext != nullptr ? ptHead->ptNext : nullptr;
          else
            v4 = nullptr;
          QTask_atProtectedQTaskStack[v3].ptQTask = v4;
          pfHandler = (void (__cdecl *)(struct QTask_s *, _DWORD))QTask_aatQTaskFinalEvent[ParameterList_eUpdateInternalDataQTaskEvent][ptHead->eQTaskType].pfHandler;
          v6 = v3 + 1;
          QTask_nProtectedQTaskStackOffset = v6;
          if ( pfHandler )
          {
            pfHandler(ptHead, 0);
            v6 = QTask_nProtectedQTaskStackOffset;
          }
          ptHead = (struct QTask_s *)dword_849C7DC[v6];
          v3 = v6 - 1;
          QTask_nProtectedQTaskStackOffset = v3;
        }
        while ( ptHead );
      }
    }
  }
  Level_CompileLevelExpression((struct LevelExpression_s *)&ptQTask[3].tQTaskChildren.ptMiddle, ptQTask);
  Level_CompileLevelExpression((struct LevelExpression_s *)&ptQTask[5].tQTaskChildren.ptMiddle, ptQTask);
  Level_CompileLevelExpression((struct LevelExpression_s *)&ptQTask[7].tQTaskChildren.ptMiddle, ptQTask);
  Level_CompileLevelExpression((struct LevelExpression_s *)&ptQTask[9].tQTaskChildren.ptMiddle, ptQTask);
  Level_CompileLevelExpression((struct LevelExpression_s *)&ptQTask[11].tQTaskChildren.ptMiddle, ptQTask);
}

// source: h/2/cutscene.c:1298  [size]
void __cdecl CutScene_GetKeyframeSizeHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = 0;
}

// source: h/2/cutscene.c:1314  [size]
void __cdecl CutScene_GetChannelDescriptionHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *((_DWORD *)pxContext + 1) = 0;
}

// source: h/2/cutscene.c:1330  [size]
void __cdecl CutScene_ReadChannelsHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ;
}

// source: h/2/cutscene.c:1342  [size]
void __cdecl CutScene_RestoreKeyframeHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ;
}

// source: h/2/cutscene.c:1354  [size]
void __cdecl CutScene_SaveKeyframeHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ;
}

// source: h/2/cutscene.c:1366  [anchor-mhash]
void __cdecl CutScene_UpdateAnimDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ptQTask[2].tQTaskRefList.ptTail = *(struct QReference_s **)pxContext;
  LOBYTE(ptQTask[15].tQTaskRefList.ptTail) = 1;
  CutScene_SetCamera((struct CutScene_t *)ptQTask);
}

// source: h/2/cutscene.c:1387  [anchor-mhash]
void __cdecl CutScene_RemoveHandler(struct QTask_s *ptQTask, void *pxContext)
{
  if ( ptQTask[15].tQTaskChildren.ptTail )
  {
    QTask_Delete(ptQTask[15].tQTaskChildren.ptTail);
    ptQTask[15].tQTaskChildren.ptTail = nullptr;
  }
  if ( ptQTask[15].tQTaskChildren.ptMiddle )
  {
    QTask_Delete(ptQTask[15].tQTaskChildren.ptMiddle);
    ptQTask[15].tQTaskChildren.ptMiddle = nullptr;
  }
  if ( ptQTask[15].tQTaskRefList.ptHead )
  {
    QTask_Delete((struct QTask_s *)ptQTask[15].tQTaskRefList.ptHead);
    ptQTask[15].tQTaskRefList.ptHead = nullptr;
  }
  if ( ptQTask[15].tQTaskRefList.ptMiddle )
  {
    QTask_Delete((struct QTask_s *)ptQTask[15].tQTaskRefList.ptMiddle);
    ptQTask[15].tQTaskRefList.ptMiddle = nullptr;
  }
  LOBYTE(ptQTask[2].tQTaskRefList.ptMiddle) = 0;
}

// source: h/2/cutscene.c:1468  [anchor-strings]
void __cdecl CutScene_Open()
{
  unsigned __int16 v0; // si
  struct ParameterList_s *v1; // eax
  int v2; // edx
  struct ParameterList_s *v3; // eax
  int v4; // edx

  dword_729560 = 0;
  dword_729564 = 0;
  dword_729568 = 0;
  dword_72956C = 1077149696;
  CutScene_ptLODVirModel = MTP_GetLODVirModel("1721_01_1");
  v0 = QTask_NewQTaskType("CutScene", 640, EditorRigidObj_eQTaskType, 0, 0);
  CutScene_eQTaskType = v0;
  QTask_LinkQTaskEventHandlerFn(
    v0,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveHandler);
  QTask_LinkQTaskEventHandlerFn(v0, 0, CutScene_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 1, CutScene_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 2, CutScene_DeleteHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))CutScene_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(v0, ParameterList_eUpdateInternalDataQTaskEvent, CutScene_UpdateInternalDataHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(
    v0,
    Level_eRegisterLevelScriptSymbolsEvent,
    CutScene_RegisterScriptSymbolsHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, Level_eRemoveLevelScriptSymbolsEvent, CutScene_RemoveScriptSymbolsHandler);
  QTask_LinkQTaskEventHandlerFn(v0, AnimQTask_eUpdateAnimDataEvent, CutScene_UpdateAnimDataHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    AnimQTask_eGetChannelDescriptionEvent,
    (void (__cdecl *)(struct QTask_s *, void *))CutScene_GetChannelDescriptionHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    AnimQTask_eGetKeyframeSizeEvent,
    (void (__cdecl *)(struct QTask_s *, void *))CutScene_GetKeyframeSizeHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    AnimQTask_eReadChannelsEvent,
    (void (__cdecl *)(struct QTask_s *, void *))CutScene_ReadChannelsHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    AnimQTask_eRestoreKeyframeEvent,
    (void (__cdecl *)(struct QTask_s *, void *))CutScene_RestoreKeyframeHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    AnimQTask_eSaveKeyframeEvent,
    (void (__cdecl *)(struct QTask_s *, void *))CutScene_SaveKeyframeHandler);
  QTask_LinkQTaskEventHandlerFn(v0, DynCubeObj_eDynCubeObjRemoveQTaskEvent, CutScene_RemoveHandler);
  v1 = (struct ParameterList_s *)Mem_AllocFn(272, 4);
  v2 = Level_eParameterTypeObjectPos;
  v1->ptParameterListItem = (struct ParameterListItem_s *)&v1[1];
  v1->nParameters = 0;
  v1->nMaxParameters = 13;
  CutScene_ptParameterList = v1;
  ParameterList_AddParameter(v1, 0x28u, v2, "Position", 7u, nullptr);
  ParameterList_AddParameter(CutScene_ptParameterList, 0x40u, Level_eParameterTypeReal32x9, "Orientation", 7u, nullptr);
  ParameterList_AddParameter(CutScene_ptParameterList, 0x84u, Level_eParameterTypeVarString, off_6A50D8, 7u, nullptr);
  ParameterList_AddParameter(CutScene_ptParameterList, 0xD4u, Level_eParameterTypeVarString, "Reset", 7u, nullptr);
  ParameterList_AddParameter(
    CutScene_ptParameterList,
    0x124u,
    Level_eParameterTypeVarString,
    "Time delta (seconds)",
    7u,
    nullptr);
  ParameterList_AddParameter(
    CutScene_ptParameterList,
    0x70u,
    Level_eParameterTypeReal32,
    "Start time (seconds)",
    7u,
    nullptr);
  ParameterList_AddParameter(CutScene_ptParameterList, 0x74u, Level_eParameterTypeReal32, "Time scale", 7u, nullptr);
  ParameterList_AddParameter(
    CutScene_ptParameterList,
    0x78u,
    Level_eParameterTypeReal32,
    "Viewport height factor",
    7u,
    nullptr);
  ParameterList_AddParameter(
    CutScene_ptParameterList,
    0x7Cu,
    Level_eParameterTypeReal32,
    "Viewport height factor fade in time",
    7u,
    &dword_729560);
  ParameterList_AddParameter(
    CutScene_ptParameterList,
    0x80u,
    Level_eParameterTypeReal32,
    "Viewport height factor fade out time",
    7u,
    &dword_729560);
  ParameterList_AddParameter(
    CutScene_ptParameterList,
    0x218u,
    Level_eParameterTypeReal32,
    "Time of day",
    7u,
    &dword_729560);
  ParameterList_AddParameter(
    CutScene_ptParameterList,
    0x174u,
    Level_eParameterTypeVarString,
    "Start expression",
    7u,
    nullptr);
  ParameterList_AddParameter(
    CutScene_ptParameterList,
    0x1C4u,
    Level_eParameterTypeVarString,
    "Stop expression",
    7u,
    nullptr);
  QTask_LinkQTaskEventHandlerFn(
    CutScene_eQTaskType,
    Serialize_eGetSerializeParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))CutScene_GetSerializeParameterListHandler);
  v3 = (struct ParameterList_s *)Mem_AllocFn(72, 4);
  v4 = Level_eParameterTypebool8;
  v3->ptParameterListItem = (struct ParameterListItem_s *)&v3[1];
  v3->nParameters = 0;
  v3->nMaxParameters = 3;
  CutScene_ptSerializeParameterList = v3;
  ParameterList_AddParameter(v3, 0x68u, v4, "isRun", 7u, nullptr);
  ParameterList_AddParameter(
    CutScene_ptSerializeParameterList,
    0x69u,
    Level_eParameterTypebool8,
    "isFinished",
    7u,
    nullptr);
  ParameterList_AddParameter(CutScene_ptSerializeParameterList, 0x6Cu, Level_eParameterTypeInt32, "nTick", 7u, nullptr);
  Symbol_Register(
    "TASKTYPE_CUTSCENE",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)CutScene_eQTaskType,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  CutScene_tRandomState.anRandom[0] = -923067897;
  CutScene_tRandomState.anRandom[1] = 971667286;
  CutScene_tRandomState.anRandom[2] = 2146516173;
}

// source: h/2/cutscene.c:1551  [size]
void __cdecl CutScene_Close()
{
  int v0; // esi
  int v1; // esi

  if ( CutScene_ptSerializeParameterList )
  {
    v0 = *(_DWORD *)((unsigned int)&CutScene_ptSerializeParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
  if ( CutScene_ptParameterList )
  {
    v1 = *(_DWORD *)((unsigned int)&CutScene_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v1);
    memset(*(void **)(v1 + 8), 0xCDu, *(_DWORD *)(v1 + 16));
    free((void *)v1);
  }
  QTask_DeleteQTaskType(CutScene_eQTaskType);
}

// source: h/2/cutscene.c:1566  [size]
unsigned __int16 __cdecl CutScene_GetQTaskType()
{
  return CutScene_eQTaskType;
}

// source: h/2/cutscene.c:1581  [size]
struct QCamera_s *__cdecl CutScene_GetQCamera(struct QTask_s *ptQTask)
{
  return (struct QCamera_s *)ptQTask[15].tQTaskChildren.ptHead;
}

// source: h/2/cutscene.c:1600  [size]
struct QCamera_s *__cdecl CutScene_SetDefaultQCamera(struct QCamera_s *ptQCamera)
{
  CutScene_ptDefaultQCamera = ptQCamera;
  return ptQCamera;
}

// source: h/2/cutscene.c:1615  [size]
struct QViewportQTask_s *__cdecl CutScene_SetDefaultQViewportQTask(
        struct QViewportQTask_s *ptQViewportQTask)
{
  CutScene_ptQViewportQTask = ptQViewportQTask;
  return ptQViewportQTask;
}

// source: h/2/cutscene.c:1630  [size]
int __cdecl CutScene_SetFrequency(int nFrequency)
{
  CutScene_nFrequency = nFrequency;
  return nFrequency;
}

// source: h/2/cutscene.c:1643  [size]
int __cdecl CutScene_IsRunning()
{
  return CutScene_isRunning;
}

// source: h/2/cutscene.c:1660  [size]
int __cdecl CutScene_SetRunning(int isRunning)
{
  CutScene_isRunning = isRunning;
  return isRunning;
}
