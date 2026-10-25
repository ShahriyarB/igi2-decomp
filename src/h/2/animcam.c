/* h/2/animcam.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: h/2/animcam.c:263  [size]
void __cdecl AnimCam_RunNoneCamera(struct AnimCam_s *ptAnimCam)
{
  LOBYTE(ptAnimCam->aiQTaskRef[1]) = 0;
  *((_BYTE *)&ptAnimCam->tAnimCamState.eAnimCamMatrixMode + 7) = 0;
}

// source: h/2/animcam.c:277  [anchor-mhash]
void __cdecl AnimCam_RunRelativeCamera(struct AnimCam_s *ptAnimCam)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct real32x9_t tDeltaOrientation; };
    struct { char igi2_o1[40]; struct real64x3_t tPos; };
    struct { char igi2_o2[64]; struct real32x9_t tDisplacementOrientation; };
    struct { char igi2_o3[104]; struct GetCameraTargetInfoContext_s tGetCameraTargetInfoContext; };
    struct { char igi2_o4[192]; struct real32x9_t tOrientation; };
    struct { char igi2_o5[232]; struct real32x9_t Real32x9_Multiply_tTemp; };
    char igi2_extent[272];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  unsigned int vX_low; // eax
  struct QReference_s *v2; // eax
  unsigned __int16 *pxObject; // eax
  void (__cdecl *pfHandler)(unsigned __int16 *, struct GetCameraTargetInfoContext_s *); // ecx
  double v5; // st7
  double v6; // st6
  double v7; // st7
  double v8; // st6
  double v9; // st5
  double v10; // st6

  vX_low = LODWORD(ptAnimCam->tAnimCamState.tPosA.vX);
  igi2_frame.tOrientation.tX.vX = 1.0;
  memset(&igi2_frame.tOrientation.tX.vY, 0, 12);
  igi2_frame.tOrientation.tY.vY = 1.0;
  memset(&igi2_frame.tOrientation.tY.vZ, 0, 12);
  igi2_frame.tOrientation.tZ.vZ = 1.0;
  igi2_frame.tOrientation.nOps = 0;
  igi2_frame.tDisplacementOrientation.tX.vX = 1.0;
  memset(&igi2_frame.tDisplacementOrientation.tX.vY, 0, 12);
  igi2_frame.tDisplacementOrientation.tY.vY = 1.0;
  memset(&igi2_frame.tDisplacementOrientation.tY.vZ, 0, 12);
  igi2_frame.tDisplacementOrientation.tZ.vZ = 1.0;
  memset(&igi2_frame.tPos, 0, sizeof(igi2_frame.tPos));
  if ( vX_low < 0x1000 )
  {
    v2 = Level_atLevelQTaskID[vX_low];
    if ( v2 )
    {
      pxObject = (unsigned __int16 *)v2->pxObject;
      if ( pxObject )
      {
        pfHandler = (void (__cdecl *)(unsigned __int16 *, struct GetCameraTargetInfoContext_s *))QTask_aatQTaskFinalEvent[8][pxObject[18]].pfHandler;
        igi2_frame.tGetCameraTargetInfoContext.zName = nullptr;
        if ( pfHandler )
        {
          pfHandler(pxObject, &igi2_frame.tGetCameraTargetInfoContext);
          qmemcpy(&igi2_frame.tPos, &igi2_frame.tGetCameraTargetInfoContext, sizeof(igi2_frame.tPos));
          qmemcpy(
            &igi2_frame.tDisplacementOrientation,
            &igi2_frame.tGetCameraTargetInfoContext.tOrientation,
            sizeof(igi2_frame.tDisplacementOrientation));
          Real32x9_CreateAlpha(&igi2_frame.tDeltaOrientation, -1.5707963705062866);
          igi2_frame.Real32x9_Multiply_tTemp.tX.vX = igi2_frame.tGetCameraTargetInfoContext.tOrientation.tX.vZ * igi2_frame.tDeltaOrientation.tZ.vX
                                        + igi2_frame.tGetCameraTargetInfoContext.tOrientation.tX.vY * igi2_frame.tDeltaOrientation.tY.vX
                                        + igi2_frame.tGetCameraTargetInfoContext.tOrientation.tX.vX * igi2_frame.tDeltaOrientation.tX.vX;
          igi2_frame.Real32x9_Multiply_tTemp.tX.vY = igi2_frame.tGetCameraTargetInfoContext.tOrientation.tX.vZ * igi2_frame.tDeltaOrientation.tZ.vY
                                        + igi2_frame.tGetCameraTargetInfoContext.tOrientation.tX.vY * igi2_frame.tDeltaOrientation.tY.vY
                                        + igi2_frame.tGetCameraTargetInfoContext.tOrientation.tX.vX * igi2_frame.tDeltaOrientation.tX.vY;
          igi2_frame.Real32x9_Multiply_tTemp.tX.vZ = igi2_frame.tGetCameraTargetInfoContext.tOrientation.tX.vZ * igi2_frame.tDeltaOrientation.tZ.vZ
                                        + igi2_frame.tGetCameraTargetInfoContext.tOrientation.tX.vY * igi2_frame.tDeltaOrientation.tY.vZ
                                        + igi2_frame.tGetCameraTargetInfoContext.tOrientation.tX.vX * igi2_frame.tDeltaOrientation.tX.vZ;
          igi2_frame.Real32x9_Multiply_tTemp.tY.vX = igi2_frame.tGetCameraTargetInfoContext.tOrientation.tY.vZ * igi2_frame.tDeltaOrientation.tZ.vX
                                        + igi2_frame.tGetCameraTargetInfoContext.tOrientation.tY.vY * igi2_frame.tDeltaOrientation.tY.vX
                                        + igi2_frame.tGetCameraTargetInfoContext.tOrientation.tY.vX * igi2_frame.tDeltaOrientation.tX.vX;
          igi2_frame.Real32x9_Multiply_tTemp.tY.vY = igi2_frame.tGetCameraTargetInfoContext.tOrientation.tY.vZ * igi2_frame.tDeltaOrientation.tZ.vY
                                        + igi2_frame.tGetCameraTargetInfoContext.tOrientation.tY.vY * igi2_frame.tDeltaOrientation.tY.vY
                                        + igi2_frame.tGetCameraTargetInfoContext.tOrientation.tY.vX * igi2_frame.tDeltaOrientation.tX.vY;
          igi2_frame.Real32x9_Multiply_tTemp.tY.vZ = igi2_frame.tGetCameraTargetInfoContext.tOrientation.tY.vZ * igi2_frame.tDeltaOrientation.tZ.vZ
                                        + igi2_frame.tGetCameraTargetInfoContext.tOrientation.tY.vY * igi2_frame.tDeltaOrientation.tY.vZ
                                        + igi2_frame.tGetCameraTargetInfoContext.tOrientation.tY.vX * igi2_frame.tDeltaOrientation.tX.vZ;
          igi2_frame.Real32x9_Multiply_tTemp.nOps = igi2_frame.tGetCameraTargetInfoContext.tOrientation.nOps + igi2_frame.tDeltaOrientation.nOps + 1;
          igi2_frame.Real32x9_Multiply_tTemp.tZ.vX = igi2_frame.tGetCameraTargetInfoContext.tOrientation.tZ.vZ * igi2_frame.tDeltaOrientation.tZ.vX
                                        + igi2_frame.tGetCameraTargetInfoContext.tOrientation.tZ.vY * igi2_frame.tDeltaOrientation.tY.vX
                                        + igi2_frame.tGetCameraTargetInfoContext.tOrientation.tZ.vX * igi2_frame.tDeltaOrientation.tX.vX;
          igi2_frame.Real32x9_Multiply_tTemp.tZ.vY = igi2_frame.tGetCameraTargetInfoContext.tOrientation.tZ.vZ * igi2_frame.tDeltaOrientation.tZ.vY
                                        + igi2_frame.tGetCameraTargetInfoContext.tOrientation.tZ.vY * igi2_frame.tDeltaOrientation.tY.vY
                                        + igi2_frame.tGetCameraTargetInfoContext.tOrientation.tZ.vX * igi2_frame.tDeltaOrientation.tX.vY;
          igi2_frame.Real32x9_Multiply_tTemp.tZ.vZ = igi2_frame.tGetCameraTargetInfoContext.tOrientation.tZ.vZ * igi2_frame.tDeltaOrientation.tZ.vZ
                                        + igi2_frame.tGetCameraTargetInfoContext.tOrientation.tZ.vY * igi2_frame.tDeltaOrientation.tY.vZ
                                        + igi2_frame.tGetCameraTargetInfoContext.tOrientation.tZ.vX * igi2_frame.tDeltaOrientation.tX.vZ;
          qmemcpy(&igi2_frame.tOrientation, &igi2_frame.Real32x9_Multiply_tTemp, sizeof(igi2_frame.tOrientation));
        }
      }
    }
  }
  v5 = igi2_frame.tDisplacementOrientation.tX.vY * ptAnimCam->tAnimCamState.tDisplacement.vZ;
  v6 = igi2_frame.tDisplacementOrientation.tX.vX * ptAnimCam->tAnimCamState.tDisplacement.vY;
  qmemcpy(&ptAnimCam->tWantedOrientation.tX.vZ, &igi2_frame.tOrientation, 0x28u);
  v7 = v5 + v6 + igi2_frame.tDisplacementOrientation.tX.vZ * ptAnimCam->tAnimCamState.tDeltaDisplacement.vX;
  v8 = igi2_frame.tDisplacementOrientation.tY.vY * ptAnimCam->tAnimCamState.tDisplacement.vZ;
  v9 = igi2_frame.tDisplacementOrientation.tY.vX * ptAnimCam->tAnimCamState.tDisplacement.vY;
  ptAnimCam->aiQTaskRef[0] = 1065353216;
  v10 = v8 + v9 + igi2_frame.tDisplacementOrientation.tY.vZ * ptAnimCam->tAnimCamState.tDeltaDisplacement.vX;
  *(double *)&igi2_frame.tDeltaOrientation.tY.vY = igi2_frame.tDisplacementOrientation.tZ.vY * ptAnimCam->tAnimCamState.tDisplacement.vZ
                                      + igi2_frame.tDisplacementOrientation.tZ.vX * ptAnimCam->tAnimCamState.tDisplacement.vY
                                      + igi2_frame.tDisplacementOrientation.tZ.vZ * ptAnimCam->tAnimCamState.tDeltaDisplacement.vX;
  igi2_frame.tPos.vX = v7 + igi2_frame.tPos.vX;
  igi2_frame.tPos.vY = v10 + igi2_frame.tPos.vY;
  igi2_frame.tPos.vZ = *(double *)&igi2_frame.tDeltaOrientation.tY.vY + igi2_frame.tPos.vZ;
  qmemcpy(&ptAnimCam->tWantedPos.vY, &igi2_frame.tPos, 0x18u);
  ptAnimCam->tAnimCamState.tDisplacement.vY = ptAnimCam->tAnimCamState.tDeltaDisplacement.vY
                                            + ptAnimCam->tAnimCamState.tDisplacement.vY;
  ptAnimCam->tAnimCamState.tDisplacement.vZ = ptAnimCam->tAnimCamState.tDeltaDisplacement.vZ
                                            + ptAnimCam->tAnimCamState.tDisplacement.vZ;
  ptAnimCam->tAnimCamState.tDeltaDisplacement.vX = *(double *)&ptAnimCam->tAnimCamState.vUpdateTargetFactor
                                                 + ptAnimCam->tAnimCamState.tDeltaDisplacement.vX;
}

// source: h/2/animcam.c:353  [anchor-mhash]
void __cdecl AnimCam_RunAimCamera(struct AnimCam_s *ptAnimCam)
{
  #pragma pack(push, 1)
  union
  {
    struct { float tTemp_; };
    struct { float tTemp_a; };
    struct { char igi2_o2[4]; float tTemp__4; };
    struct { char igi2_o3[4]; float tTemp__4a; };
    struct { char igi2_o4[8]; float tTemp__8; };
    struct { char igi2_o5[8]; float tTemp__8a; };
    struct { char igi2_o6[15]; char isIgnoreDisplacement; };
    struct { char igi2_o7[16]; float v41; };
    struct { char igi2_o8[16]; float v42; };
    struct { char igi2_o9[20]; float v43; };
    struct { char igi2_o10[20]; float v44; };
    struct { char igi2_o11[24]; float v45; };
    struct { char igi2_o12[24]; float v46; };
    struct { char igi2_o13[32]; float tForward_4; };
    struct { char igi2_o14[36]; float tForward_8; };
    struct { char igi2_o15[40]; float v49; };
    struct { char igi2_o16[44]; float Real32x9_Normalize_tTemp; };
    struct { char igi2_o17[48]; float Real32x9_Normalize_tTemp_4; };
    struct { char igi2_o18[52]; float Real32x9_Normalize_tTemp_8; };
    struct { char igi2_o19[56]; float Real32x9_Normalize_tTemp_12; };
    struct { char igi2_o20[60]; float Real32x9_Normalize_tTemp_16; };
    struct { char igi2_o21[64]; float Real32x9_Normalize_tTemp_20; };
    struct { char igi2_o22[68]; float Real32x9_Normalize_tTemp_24; };
    struct { char igi2_o23[72]; float Real32x9_Normalize_tTemp_28; };
    struct { char igi2_o24[84]; float v58; };
    struct { char igi2_o25[88]; _BYTE tPos1[40]; };
    struct { char igi2_o26[128]; struct real64x3_t Real64x3_Rotate_tTemp; };
    struct { char igi2_o27[152]; struct real64x3_t tPos0; };
    struct { char igi2_o28[176]; struct real64x3_t tPos; };
    struct { char igi2_o29[200]; struct real32x9_t tOrientation; };
    struct { char igi2_o30[240]; struct real32x9_t tTilt; };
    struct { char igi2_o31[280]; struct GetCameraTargetInfoContext_s tGetCameraTargetInfoContext; };
    char igi2_extent[368];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int vX_low; // eax
  struct QReference_s *v2; // eax
  unsigned __int16 *pxObject; // eax
  void (__cdecl *pfHandler)(unsigned __int16 *, struct GetCameraTargetInfoContext_s *); // ecx
  struct GetCameraTargetInfoContext_s *p_vY; // esi
  struct real64x3_t *v6; // esi
  struct real64x3_t *p_tPos0; // edi
  unsigned int vX_high; // eax
  struct QReference_s *v9; // eax
  unsigned __int16 *v10; // eax
  void (__cdecl *v11)(unsigned __int16 *, struct GetCameraTargetInfoContext_s *); // ecx
  void *v12; // esi
  void *v13; // edi
  double v14; // st7
  long double v15; // st7
  long double v16; // st6
  long double v17; // st7
  long double v18; // rt1
  long double v19; // st6
  double v20; // st6
  long double v21; // st3
  long double v22; // st6
  long double v23; // st2
  long double v24; // st5
  long double v25; // st4
  long double v26; // st7
  long double v27; // st4
  long double v28; // st7
  double v29; // st6
  double v30; // st6
  double v31; // st6
  double v32; // st7
  double v33; // st7

  vX_low = LODWORD(ptAnimCam->tAnimCamState.tPosA.vX);
  igi2_frame.isIgnoreDisplacement = 0;
  memset(&igi2_frame.tPos, 0, sizeof(igi2_frame.tPos));
  memset(&igi2_frame.tPos0, 0, sizeof(igi2_frame.tPos0));
  memset(igi2_frame.tPos1, 0, 24);
  if ( vX_low < 0 )
  {
    p_vY = (struct GetCameraTargetInfoContext_s *)&ptAnimCam->tAnimCamState.tDisplacement.vY;
    igi2_frame.isIgnoreDisplacement = 1;
  }
  else
  {
    if ( vX_low >= 4096 )
      goto LABEL_9;
    v2 = Level_atLevelQTaskID[vX_low];
    if ( !v2 )
      goto LABEL_9;
    pxObject = (unsigned __int16 *)v2->pxObject;
    if ( !pxObject )
      goto LABEL_9;
    pfHandler = (void (__cdecl *)(unsigned __int16 *, struct GetCameraTargetInfoContext_s *))QTask_aatQTaskFinalEvent[8][pxObject[18]].pfHandler;
    igi2_frame.tGetCameraTargetInfoContext.zName = nullptr;
    if ( !pfHandler )
      goto LABEL_9;
    pfHandler(pxObject, &igi2_frame.tGetCameraTargetInfoContext);
    p_vY = &igi2_frame.tGetCameraTargetInfoContext;
  }
  qmemcpy(&igi2_frame.tPos0, p_vY, sizeof(igi2_frame.tPos0));
LABEL_9:
  if ( LOBYTE(ptAnimCam->tAnimCamState.tDisplacement.vX) && *((_BYTE *)&ptAnimCam->tAnimCamState.eAnimCamMatrixMode + 4) )
  {
    v6 = (struct real64x3_t *)&ptAnimCam->tAnimCamState.tPosA.vY;
    p_tPos0 = &igi2_frame.tPos0;
  }
  else
  {
    p_tPos0 = (struct real64x3_t *)&ptAnimCam->tAnimCamState.tPosA.vY;
    v6 = &igi2_frame.tPos0;
    LOBYTE(ptAnimCam->tAnimCamState.tDisplacement.vX) = 1;
  }
  vX_high = HIDWORD(ptAnimCam->tAnimCamState.tPosA.vX);
  qmemcpy(p_tPos0, v6, sizeof(struct real64x3_t));
  if ( vX_high < 0x1000 )
  {
    v9 = Level_atLevelQTaskID[vX_high];
    if ( v9 )
    {
      v10 = (unsigned __int16 *)v9->pxObject;
      if ( v10 )
      {
        v11 = (void (__cdecl *)(unsigned __int16 *, struct GetCameraTargetInfoContext_s *))QTask_aatQTaskFinalEvent[8][v10[18]].pfHandler;
        igi2_frame.tGetCameraTargetInfoContext.zName = nullptr;
        if ( v11 )
        {
          v11(v10, &igi2_frame.tGetCameraTargetInfoContext);
          qmemcpy(igi2_frame.tPos1, &igi2_frame.tGetCameraTargetInfoContext, 0x18u);
        }
      }
    }
  }
  if ( BYTE1(ptAnimCam->tAnimCamState.tDisplacement.vX) && *((_BYTE *)&ptAnimCam->tAnimCamState.eAnimCamMatrixMode + 5) )
  {
    v12 = &ptAnimCam->tAnimCamState.tPosB.vY;
    v13 = igi2_frame.tPos1;
  }
  else
  {
    v13 = &ptAnimCam->tAnimCamState.tPosB.vY;
    v12 = igi2_frame.tPos1;
    BYTE1(ptAnimCam->tAnimCamState.tDisplacement.vX) = 1;
  }
  qmemcpy(v13, v12, 0x18u);
  v14 = *(double *)igi2_frame.tPos1;
  *((float *)&igi2_frame.Real64x3_Rotate_tTemp.vX + 1) = *(double *)&igi2_frame.tPos1[8];
  *(float *)&igi2_frame.Real64x3_Rotate_tTemp.vY = *(double *)&igi2_frame.tPos1[16];
  *(float *)&igi2_frame.tPos1[4] = igi2_frame.tPos0.vY;
  *(float *)&igi2_frame.tPos1[8] = igi2_frame.tPos0.vZ;
  v15 = v14 - igi2_frame.tPos0.vX;
  igi2_frame.tForward_4 = *((float *)&igi2_frame.Real64x3_Rotate_tTemp.vX + 1) - *(float *)&igi2_frame.tPos1[4];
  igi2_frame.tForward_8 = *(float *)&igi2_frame.Real64x3_Rotate_tTemp.vY - *(float *)&igi2_frame.tPos1[8];
  if ( v15 != 0.0 )
    goto LABEL_29;
  if ( igi2_frame.tForward_4 == 0.0 && igi2_frame.tForward_8 == 0.0 )
  {
    v15 = 1.0;
    goto LABEL_30;
  }
  if ( v15 != 0.0 || igi2_frame.tForward_4 != 0.0 || igi2_frame.tForward_8 != 0.0 )
  {
LABEL_29:
    v16 = v15;
    v17 = 1.0 / sqrt(v15 * v15 + igi2_frame.tForward_4 * igi2_frame.tForward_4 + igi2_frame.tForward_8 * igi2_frame.tForward_8);
    v18 = v16 * v17;
    v19 = v17;
    v15 = v18;
    igi2_frame.tForward_4 = igi2_frame.tForward_4 * v19;
    igi2_frame.tForward_8 = igi2_frame.tForward_8 * v19;
  }
LABEL_30:
  v20 = igi2_frame.tForward_8 * 0.0;
  igi2_frame.tTemp_ = igi2_frame.tForward_4 - v20;
  *(float *)igi2_frame.tPos1 = igi2_frame.tTemp_;
  igi2_frame.tTemp__4 = -(v15 - v20);
  *(float *)&igi2_frame.tPos1[4] = igi2_frame.tTemp__4;
  igi2_frame.tTemp__8 = 0.0 * v15 - igi2_frame.tForward_4 * 0.0;
  *(float *)&igi2_frame.tPos1[8] = igi2_frame.tTemp__8;
  igi2_frame.v41 = igi2_frame.tTemp__4 * igi2_frame.tForward_8 - igi2_frame.tTemp__8 * igi2_frame.tForward_4;
  *(float *)&igi2_frame.Real64x3_Rotate_tTemp.vX = igi2_frame.v41;
  igi2_frame.v43 = -(igi2_frame.tTemp_ * igi2_frame.tForward_8 - igi2_frame.tTemp__8 * v15);
  *((float *)&igi2_frame.Real64x3_Rotate_tTemp.vX + 1) = igi2_frame.v43;
  igi2_frame.v45 = igi2_frame.tTemp_ * igi2_frame.tForward_4 - igi2_frame.tTemp__4 * v15;
  *(float *)&igi2_frame.Real64x3_Rotate_tTemp.vY = igi2_frame.v45;
  if ( igi2_frame.tTemp_ == 0.0 && igi2_frame.tTemp__4 == 0.0 && igi2_frame.tTemp__8 == 0.0 )
  {
    v22 = *(float *)&igi2_frame.tPos1[8];
  }
  else
  {
    v21 = sqrt(igi2_frame.tTemp__4 * igi2_frame.tTemp__4 + igi2_frame.tTemp__8 * igi2_frame.tTemp__8 + igi2_frame.tTemp_ * igi2_frame.tTemp_);
    *(float *)igi2_frame.tPos1 = igi2_frame.tTemp_ * (1.0 / v21);
    v22 = 1.0 / v21 * *(float *)&igi2_frame.tPos1[8];
  }
  if ( igi2_frame.v41 == 0.0 && igi2_frame.v43 == 0.0 && igi2_frame.v45 == 0.0 )
  {
    v24 = *(float *)&igi2_frame.Real64x3_Rotate_tTemp.vY;
  }
  else
  {
    v23 = sqrt(igi2_frame.v41 * igi2_frame.v41 + igi2_frame.v43 * igi2_frame.v43 + igi2_frame.v45 * igi2_frame.v45);
    *(float *)&igi2_frame.Real64x3_Rotate_tTemp.vX = igi2_frame.v41 * (1.0 / v23);
    v24 = 1.0 / v23 * *(float *)&igi2_frame.Real64x3_Rotate_tTemp.vY;
  }
  igi2_frame.tOrientation.tX.vY = v15;
  igi2_frame.tOrientation.tX.vX = *(float *)igi2_frame.tPos1;
  igi2_frame.Real32x9_Normalize_tTemp_4 = igi2_frame.tOrientation.tX.vY;
  igi2_frame.tOrientation.tX.vZ = *(float *)&igi2_frame.Real64x3_Rotate_tTemp.vX;
  igi2_frame.Real32x9_Normalize_tTemp = *(float *)igi2_frame.tPos1;
  igi2_frame.Real32x9_Normalize_tTemp_8 = *(float *)&igi2_frame.Real64x3_Rotate_tTemp.vX;
  igi2_frame.v58 = sin(-1.5707963705062866);
  igi2_frame.v49 = cos(-1.5707963705062866);
  igi2_frame.tTilt.tY.vZ = -igi2_frame.v58;
  if ( *(float *)igi2_frame.tPos1 != 0.0 || v15 != 0.0 || *(float *)&igi2_frame.Real64x3_Rotate_tTemp.vX != 0.0 )
  {
    v25 = 1.0
        / sqrt(
            *(float *)igi2_frame.tPos1 * *(float *)igi2_frame.tPos1
          + v15 * v15
          + *(float *)&igi2_frame.Real64x3_Rotate_tTemp.vX * *(float *)&igi2_frame.Real64x3_Rotate_tTemp.vX);
    igi2_frame.Real32x9_Normalize_tTemp = *(float *)igi2_frame.tPos1 * v25;
    igi2_frame.Real32x9_Normalize_tTemp_4 = igi2_frame.tOrientation.tX.vY * v25;
    igi2_frame.Real32x9_Normalize_tTemp_8 = *(float *)&igi2_frame.Real64x3_Rotate_tTemp.vX * v25;
  }
  igi2_frame.tTemp_a = *(float *)&igi2_frame.Real64x3_Rotate_tTemp.vX * igi2_frame.tForward_8 - v24 * v15;
  igi2_frame.Real32x9_Normalize_tTemp_12 = igi2_frame.tTemp_a;
  igi2_frame.tTemp__4a = -(v22 * *(float *)&igi2_frame.Real64x3_Rotate_tTemp.vX - *(float *)igi2_frame.tPos1 * v24);
  igi2_frame.Real32x9_Normalize_tTemp_16 = igi2_frame.tTemp__4a;
  igi2_frame.tTemp__8a = v22 * v15 - *(float *)igi2_frame.tPos1 * igi2_frame.tForward_8;
  igi2_frame.Real32x9_Normalize_tTemp_20 = igi2_frame.tTemp__8a;
  igi2_frame.v42 = igi2_frame.tTemp__8a * igi2_frame.Real32x9_Normalize_tTemp_4 - igi2_frame.tTemp__4a * igi2_frame.Real32x9_Normalize_tTemp_8;
  igi2_frame.Real32x9_Normalize_tTemp_24 = igi2_frame.v42;
  igi2_frame.v44 = -(igi2_frame.tTemp__8a * igi2_frame.Real32x9_Normalize_tTemp - igi2_frame.tTemp_a * igi2_frame.Real32x9_Normalize_tTemp_8);
  igi2_frame.Real32x9_Normalize_tTemp_28 = igi2_frame.v44;
  igi2_frame.v46 = igi2_frame.tTemp__4a * igi2_frame.Real32x9_Normalize_tTemp - igi2_frame.tTemp_a * igi2_frame.Real32x9_Normalize_tTemp_4;
  if ( igi2_frame.tTemp_a != 0.0 || igi2_frame.tTemp__4a != 0.0 || igi2_frame.tTemp__8a != 0.0 )
  {
    v26 = 1.0 / sqrt(igi2_frame.tTemp__8a * igi2_frame.tTemp__8a + igi2_frame.tTemp__4a * igi2_frame.tTemp__4a + igi2_frame.tTemp_a * igi2_frame.tTemp_a);
    igi2_frame.Real32x9_Normalize_tTemp_12 = igi2_frame.tTemp_a * v26;
    igi2_frame.Real32x9_Normalize_tTemp_16 = igi2_frame.tTemp__4a * v26;
    igi2_frame.Real32x9_Normalize_tTemp_20 = igi2_frame.tTemp__8a * v26;
  }
  if ( igi2_frame.v42 == 0.0 && igi2_frame.v44 == 0.0 && igi2_frame.v46 == 0.0 )
  {
    v28 = igi2_frame.v46;
  }
  else
  {
    v27 = sqrt(igi2_frame.v42 * igi2_frame.v42 + igi2_frame.v44 * igi2_frame.v44 + igi2_frame.v46 * igi2_frame.v46);
    igi2_frame.Real32x9_Normalize_tTemp_24 = igi2_frame.v42 * (1.0 / v27);
    igi2_frame.Real32x9_Normalize_tTemp_28 = igi2_frame.v44 * (1.0 / v27);
    v28 = 1.0 / v27 * igi2_frame.v46;
  }
  *(_DWORD *)&igi2_frame.tPos1[36] = 1;
  *(float *)igi2_frame.tPos1 = (igi2_frame.Real32x9_Normalize_tTemp_8 + igi2_frame.Real32x9_Normalize_tTemp_4) * 0.0 + igi2_frame.Real32x9_Normalize_tTemp;
  v29 = igi2_frame.Real32x9_Normalize_tTemp * 0.0;
  *(float *)&igi2_frame.tPos1[4] = igi2_frame.v58 * igi2_frame.Real32x9_Normalize_tTemp_8 + igi2_frame.v49 * igi2_frame.Real32x9_Normalize_tTemp_4 + v29;
  *(float *)&igi2_frame.tPos1[8] = igi2_frame.v49 * igi2_frame.Real32x9_Normalize_tTemp_8 + igi2_frame.tTilt.tY.vZ * igi2_frame.Real32x9_Normalize_tTemp_4 + v29;
  *(float *)&igi2_frame.tPos1[12] = (igi2_frame.Real32x9_Normalize_tTemp_16 + igi2_frame.Real32x9_Normalize_tTemp_20) * 0.0 + igi2_frame.Real32x9_Normalize_tTemp_12;
  v30 = igi2_frame.Real32x9_Normalize_tTemp_12 * 0.0;
  *(float *)&igi2_frame.tPos1[16] = igi2_frame.v49 * igi2_frame.Real32x9_Normalize_tTemp_16 + igi2_frame.v58 * igi2_frame.Real32x9_Normalize_tTemp_20 + v30;
  *(float *)&igi2_frame.tPos1[20] = igi2_frame.v49 * igi2_frame.Real32x9_Normalize_tTemp_20 + igi2_frame.tTilt.tY.vZ * igi2_frame.Real32x9_Normalize_tTemp_16 + v30;
  *(float *)&igi2_frame.tPos1[24] = (igi2_frame.Real32x9_Normalize_tTemp_28 + v28) * 0.0 + igi2_frame.Real32x9_Normalize_tTemp_24;
  v31 = igi2_frame.Real32x9_Normalize_tTemp_24 * 0.0;
  *(float *)&igi2_frame.tPos1[28] = igi2_frame.v58 * v28 + igi2_frame.v49 * igi2_frame.Real32x9_Normalize_tTemp_28 + v31;
  *(float *)&igi2_frame.tPos1[32] = igi2_frame.v49 * v28 + igi2_frame.tTilt.tY.vZ * igi2_frame.Real32x9_Normalize_tTemp_28 + v31;
  if ( !igi2_frame.isIgnoreDisplacement )
  {
    igi2_frame.Real64x3_Rotate_tTemp.vX = *(float *)&igi2_frame.tPos1[4] * ptAnimCam->tAnimCamState.tDisplacement.vZ
                             + *(float *)&igi2_frame.tPos1[8] * ptAnimCam->tAnimCamState.tDeltaDisplacement.vX
                             + *(float *)igi2_frame.tPos1 * ptAnimCam->tAnimCamState.tDisplacement.vY;
    igi2_frame.Real64x3_Rotate_tTemp.vY = *(float *)&igi2_frame.tPos1[16] * ptAnimCam->tAnimCamState.tDisplacement.vZ
                             + *(float *)&igi2_frame.tPos1[20] * ptAnimCam->tAnimCamState.tDeltaDisplacement.vX
                             + *(float *)&igi2_frame.tPos1[12] * ptAnimCam->tAnimCamState.tDisplacement.vY;
    igi2_frame.Real64x3_Rotate_tTemp.vZ = *(float *)&igi2_frame.tPos1[28] * ptAnimCam->tAnimCamState.tDisplacement.vZ
                             + *(float *)&igi2_frame.tPos1[32] * ptAnimCam->tAnimCamState.tDeltaDisplacement.vX
                             + *(float *)&igi2_frame.tPos1[24] * ptAnimCam->tAnimCamState.tDisplacement.vY;
    qmemcpy(&igi2_frame.tPos, &igi2_frame.Real64x3_Rotate_tTemp, sizeof(igi2_frame.tPos));
  }
  v32 = igi2_frame.tPos0.vX + igi2_frame.tPos.vX;
  qmemcpy(&ptAnimCam->tWantedOrientation.tX.vZ, igi2_frame.tPos1, 0x28u);
  igi2_frame.tPos.vX = v32;
  igi2_frame.tPos.vY = igi2_frame.tPos0.vY + igi2_frame.tPos.vY;
  igi2_frame.tPos.vZ = igi2_frame.tPos0.vZ + igi2_frame.tPos.vZ;
  v33 = ptAnimCam->tAnimCamState.tDeltaDisplacement.vY + ptAnimCam->tAnimCamState.tDisplacement.vY;
  qmemcpy(&ptAnimCam->tWantedPos.vY, &igi2_frame.tPos, 0x18u);
  ptAnimCam->tAnimCamState.tDisplacement.vY = v33;
  ptAnimCam->tAnimCamState.tDisplacement.vZ = ptAnimCam->tAnimCamState.tDeltaDisplacement.vZ
                                            + ptAnimCam->tAnimCamState.tDisplacement.vZ;
  ptAnimCam->tAnimCamState.tDeltaDisplacement.vX = *(double *)&ptAnimCam->tAnimCamState.vUpdateTargetFactor
                                                 + ptAnimCam->tAnimCamState.tDeltaDisplacement.vX;
  ptAnimCam->aiQTaskRef[0] = 1065353216;
}

// source: h/2/animcam.c:534  [size]
void __cdecl AnimCam_RunCircleCamera(struct AnimCam_s *ptAnimCam)
{
  ;
}

// source: h/2/animcam.c:546  [size]
void __cdecl AnimCam_RunFlybyCamera(struct AnimCam_s *ptAnimCam)
{
  ;
}

// source: h/2/animcam.c:560  [anchor-callee]
struct AnimCam_s *__cdecl AnimCam_Init(struct AnimCam_s *ptAnimCam)
{
  LOBYTE(ptAnimCam->aiQTaskRef[1]) = 0;
  *((_BYTE *)&ptAnimCam->tAnimCamState.eAnimCamMatrixMode + 7) = 1;
  ptAnimCam->tAnimCamState.iObjectA = (int)AnimCam_RunRelativeCamera;
  ptAnimCam->tAnimCamState.tPosA.vX = IGI2_DOUBLE_BITS(0xffffffffffffffffull);
  ptAnimCam->tAnimCamState.tDisplacement.vY = 0.0;
  ptAnimCam->tAnimCamState.tDisplacement.vZ = 0.0;
  ptAnimCam->tAnimCamState.tDeltaDisplacement.vX = 0.0;
  ptAnimCam->tAnimCamState.tDeltaDisplacement.vY = 0.0;
  ptAnimCam->tAnimCamState.tDeltaDisplacement.vZ = 0.0;
  ptAnimCam->tAnimCamState.vUpdateTargetFactor = 0.0;
  ptAnimCam->tAnimCamState.vAlpha = 0.0;
  LOWORD(ptAnimCam->tAnimCamState.tDisplacement.vX) = 0;
  ptAnimCam->tAnimCamState.vDeltaAlpha = 0.0;
  ptAnimCam->tAnimCamState.vBeta = 0.0;
  ptAnimCam->tAnimCamState.vDeltaBeta = 0.0;
  ptAnimCam->tAnimCamState.vGamma = 0.0;
  ptAnimCam->tAnimCamState.vDeltaGamma = 0.0;
  ptAnimCam->tAnimCamState.vRadius = 0.0;
  ptAnimCam->tAnimCamState.vDeltaRadius = 0.0;
  *(_DWORD *)&ptAnimCam->tAnimCamState.isLockAlpha = 0;
  ptAnimCam->tAnimCamState.eAnimCamMatrixMode = ANIMCAM_MATRIXMODE_WORLD;
  *((_BYTE *)&ptAnimCam->tAnimCamState.eAnimCamMatrixMode + 4) = 0;
  *((_BYTE *)&ptAnimCam->tAnimCamState.eAnimCamMatrixMode + 5) = 0;
  *((_BYTE *)&ptAnimCam->tAnimCamState.eAnimCamMatrixMode + 6) = 0;
  *(_DWORD *)ptAnimCam->zMode = 1;
  return ptAnimCam;
}

// source: h/2/animcam.c:601  [anchor-callee]
void __cdecl AnimCam_Move(struct AnimCam_s *ptAnimCam)
{
  float v1; // [esp-14h] [ebp-1Ch]

  ((void (*)(void))ptAnimCam->tAnimCamState.iObjectA)();
  v1 = *(float *)ptAnimCam->aiQTaskRef;
  ptAnimCam->tAnimCamState.iObjectB = ptAnimCam->tAnimCamState.iObjectA;
  QCamera_Set(
    (struct QCamera_s *)LODWORD(ptAnimCam->tWantedOrientation.tX.vY),
    (struct real64x3_t *)&ptAnimCam->tWantedPos.vY,
    (struct real32x9_t *)&ptAnimCam->tWantedOrientation.tX.vZ,
    v1,
    1.0,
    0.0,
    Screen_nFrameNumber,
    nullptr,
    0.0,
    0);
}

// source: h/2/animcam.c:632  [anchor-mhash]
void __cdecl AnimCam_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  memset(&ptQTask[5].ptParent, 0xFFu, sizeof(struct QTask_s));
  ptQTask[11].tQTaskChildren.ptTail = (struct QTask_s *)-1;
  ptQTask[11].tQTaskRefList.ptHead = (struct QReference_s *)-1;
  ptQTask[3].ptParent = nullptr;
  ptQTask[11].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[11].tQTaskRefList.ptTail = nullptr;
  ptQTask[11].ptParent = nullptr;
  *(_DWORD *)&ptQTask[11].eQTaskType = 0;
  ptQTask[12].ptNext = nullptr;
  ptQTask[12].ptPrev = nullptr;
  ptQTask[12].tQTaskChildren.ptHead = nullptr;
  ptQTask[12].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[12].tQTaskChildren.ptTail = nullptr;
  ptQTask[12].tQTaskRefList.ptHead = nullptr;
  ptQTask[12].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[12].tQTaskRefList.ptTail = nullptr;
  ptQTask[12].ptParent = nullptr;
  *(_DWORD *)&ptQTask[12].eQTaskType = 0;
  ptQTask[13].ptNext = nullptr;
  ptQTask[13].ptPrev = nullptr;
  ptQTask[13].tQTaskChildren.ptHead = nullptr;
  ptQTask[13].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[13].tQTaskChildren.ptTail = nullptr;
  ptQTask[13].tQTaskRefList.ptHead = nullptr;
  ptQTask[13].tQTaskRefList.ptMiddle = nullptr;
  LOBYTE(ptQTask[13].tQTaskRefList.ptTail) = 0;
  BYTE1(ptQTask[13].tQTaskRefList.ptTail) = 0;
  BYTE2(ptQTask[13].tQTaskRefList.ptTail) = 0;
  strcpy((char *)&ptQTask[11], "(Default)");
  AnimCam_Init((struct AnimCam_s *)ptQTask);
}

// source: h/2/animcam.c:684  [size]
void __cdecl AnimCam_DeleteHandler(struct QTask_s *ptQTask)
{
  ;
}

// source: h/2/animcam.c:698  [size]
void __cdecl AnimCam_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = AnimCam_ptParameterList;
}

// source: h/2/animcam.c:714  [anchor-strings]
void __cdecl AnimCam_UpdateAnimDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct AnimCam_s *v2; // eax
  char ptTail_high; // cl
  struct QTask_s *v4; // edx
  char v5; // cl
  int v6; // edx
  int v7; // edx
  int v8; // edx
  int v9; // edx
  int v10; // edx
  int v11; // edx
  int v12; // edx
  int v13; // edx
  struct QTask_s *v14; // esi
  int v15; // esi
  struct QTask_s *v16; // esi
  struct QTask_s *v17; // esi
  struct QTask_s *v18; // esi
  struct QTask_s *v19; // esi
  struct QTask_s *v20; // esi
  struct QReference_s *v21; // esi
  struct QReference_s *v22; // esi
  int v23; // edx
  int v24; // edx
  int v25; // edx
  int v26; // edx
  bool v27; // cc

  v2 = (struct AnimCam_s *)ptQTask;
  ptTail_high = HIBYTE(ptQTask[10].tQTaskRefList.ptTail);
  LOBYTE(ptQTask[5].tQTaskRefList.ptTail) = 0;
  if ( ptTail_high )
    LOBYTE(ptQTask[5].tQTaskRefList.ptTail) = 1;
  switch ( (__int64)**((float **)pxContext + 1) )
  {
    case 0LL:
      ptQTask[6].ptParent = (struct QTask_s *)AnimCam_RunFlybyCamera;
      strcpy((char *)&ptQTask[11], "Flyby");
      break;
    case 1LL:
      ptQTask[6].ptParent = (struct QTask_s *)AnimCam_RunCircleCamera;
      v4 = ptQTask + 11;
      ptQTask[11].ptNext = (struct QTask_s *)unk_6839E0;
      LOWORD(ptQTask[11].ptPrev) = unk_6839E4;
      v5 = unk_6839E6;
      goto LABEL_9;
    case 2LL:
      ptQTask[6].ptParent = (struct QTask_s *)AnimCam_RunAimCamera;
      ptQTask[11].ptNext = (struct QTask_s *)&QTask_aaisHandlerSetDirectly[89705];
      break;
    case 3LL:
      ptQTask[6].ptParent = (struct QTask_s *)AnimCam_RunRelativeCamera;
      strcpy((char *)&ptQTask[11], "Relative");
      break;
    case 4LL:
      ptQTask[6].ptParent = (struct QTask_s *)AnimCam_RunNoneCamera;
      v4 = ptQTask + 11;
      ptQTask[11].ptNext = (struct QTask_s *)unk_6839D8;
      LOWORD(ptQTask[11].ptPrev) = unk_6839DC;
      v5 = unk_6839DE;
LABEL_9:
      BYTE2(v4->ptPrev) = v5;
      break;
    default:
      break;
  }
  v6 = *((_DWORD *)pxContext + 1);
  if ( *(_DWORD *)(v6 + 4) != -998653952 )
    ptQTask[7].ptNext = (struct QTask_s *)(__int64)*(float *)(v6 + 4);
  v7 = *((_DWORD *)pxContext + 1);
  if ( *(_DWORD *)(v7 + 8) != -998653952 )
    ptQTask[7].ptPrev = (struct QTask_s *)(__int64)*(float *)(v7 + 8);
  v8 = *((_DWORD *)pxContext + 1);
  if ( *(_DWORD *)(v8 + 12) != -998653952 )
    *(double *)&ptQTask[8].tQTaskRefList.ptMiddle = *(float *)(v8 + 12);
  v9 = *((_DWORD *)pxContext + 1);
  if ( *(_DWORD *)(v9 + 16) != -998653952 )
    *(double *)&ptQTask[8].ptParent = *(float *)(v9 + 16);
  v10 = *((_DWORD *)pxContext + 1);
  if ( *(_DWORD *)(v10 + 20) != -998653952 )
    *(double *)&ptQTask[9].ptNext = *(float *)(v10 + 20);
  v11 = *((_DWORD *)pxContext + 1);
  if ( *(_DWORD *)(v11 + 24) != -998653952 )
    *(double *)&ptQTask[9].tQTaskChildren.ptHead = *(float *)(v11 + 24);
  v12 = *((_DWORD *)pxContext + 1);
  if ( *(_DWORD *)(v12 + 28) != -998653952 )
    *(double *)&ptQTask[9].tQTaskChildren.ptTail = *(float *)(v12 + 28);
  v13 = *((_DWORD *)pxContext + 1);
  if ( *(_DWORD *)(v13 + 32) != -998653952 )
    *(double *)&ptQTask[9].tQTaskRefList.ptMiddle = *(float *)(v13 + 32);
  v14 = *(struct QTask_s **)(*((_DWORD *)pxContext + 1) + 36);
  if ( v14 != (struct QTask_s *)-998653952 )
    ptQTask[9].ptParent = v14;
  v15 = *(_DWORD *)(*((_DWORD *)pxContext + 1) + 40);
  if ( v15 != -998653952 )
    *(_DWORD *)&ptQTask[9].eQTaskType = v15;
  v16 = *(struct QTask_s **)(*((_DWORD *)pxContext + 1) + 44);
  if ( v16 != (struct QTask_s *)-998653952 )
    ptQTask[10].ptNext = v16;
  v17 = *(struct QTask_s **)(*((_DWORD *)pxContext + 1) + 48);
  if ( v17 != (struct QTask_s *)-998653952 )
    ptQTask[10].ptPrev = v17;
  v18 = *(struct QTask_s **)(*((_DWORD *)pxContext + 1) + 52);
  if ( v18 != (struct QTask_s *)-998653952 )
    ptQTask[10].tQTaskChildren.ptHead = v18;
  v19 = *(struct QTask_s **)(*((_DWORD *)pxContext + 1) + 56);
  if ( v19 != (struct QTask_s *)-998653952 )
    ptQTask[10].tQTaskChildren.ptMiddle = v19;
  v20 = *(struct QTask_s **)(*((_DWORD *)pxContext + 1) + 60);
  if ( v20 != (struct QTask_s *)-998653952 )
    ptQTask[10].tQTaskChildren.ptTail = v20;
  v21 = *(struct QReference_s **)(*((_DWORD *)pxContext + 1) + 64);
  if ( v21 != (struct QReference_s *)-998653952 )
    ptQTask[10].tQTaskRefList.ptHead = v21;
  v22 = *(struct QReference_s **)(*((_DWORD *)pxContext + 1) + 68);
  if ( v22 != (struct QReference_s *)-998653952 )
    ptQTask[10].tQTaskRefList.ptMiddle = v22;
  v23 = *((_DWORD *)pxContext + 1);
  if ( *(_DWORD *)(v23 + 72) != -998653952 )
    LOBYTE(ptQTask[10].tQTaskRefList.ptTail) = (__int64)*(float *)(v23 + 72);
  v24 = *((_DWORD *)pxContext + 1);
  if ( *(_DWORD *)(v24 + 76) != -998653952 )
    BYTE1(ptQTask[10].tQTaskRefList.ptTail) = (__int64)*(float *)(v24 + 76);
  v25 = *((_DWORD *)pxContext + 1);
  if ( *(_DWORD *)(v25 + 80) != -998653952 )
    BYTE2(ptQTask[10].tQTaskRefList.ptTail) = (__int64)*(float *)(v25 + 80);
  v26 = *((_DWORD *)pxContext + 1);
  if ( *(_DWORD *)(v26 + 84) != -998653952 )
    ptQTask[10].ptParent = (struct QTask_s *)(__int64)*(float *)(v26 + 84);
  v27 = (int)(*(_DWORD *)pxContext) <= 0;
  if ( !*(_DWORD *)pxContext )
  {
    v2 = AnimCam_Init((struct AnimCam_s *)ptQTask);
    v27 = (int)(*(_DWORD *)pxContext) <= 0;
  }
  if ( !v27 )
    AnimCam_Move(v2);
}

// source: h/2/animcam.c:906  [size]
void __cdecl AnimCam_GetChannelDescriptionHandler(struct QTask_s *ptQTask, void *pxContext)
{
  int v2; // eax

  v2 = *(_DWORD *)pxContext;
  if ( *(int *)pxContext < 0 || v2 >= 22 )
    *((_DWORD *)pxContext + 1) = 0;
  else
    *((_DWORD *)pxContext + 1) = 16 * v2 + 7012112;
}

// source: h/2/animcam.c:938  [anchor-mhash]
struct AnimCam_s *__cdecl AnimCam_ChangeReadChannelsParameters(
        struct QTask_s *ptQTask,
        struct AnimCam_s *ptAnimCam,
        struct ReadChannelsContext_s *ptReadChannelsContext)
{
  struct real64x3_t *p_tEditDisplacement; // ecx

  LOBYTE(ptAnimCam->aiQTaskRef[1]) = 1;
  if ( (Keyboard_tKeyboard.anCurrentKey[29] & 0x80u) != 0 || (Keyboard_tKeyboard.anCurrentKey[157] & 0x80) != 0 )
  {
    p_tEditDisplacement = &ptAnimCam->tEditDisplacement;
    if ( (Keyboard_tKeyboard.anCurrentKey[42] & 0x80) != 0 || (Keyboard_tKeyboard.anCurrentKey[54] & 0x80) != 0 )
      p_tEditDisplacement = (struct real64x3_t *)((char *)&ptAnimCam->tEditDisplacement.vX + 4);
    if ( (Keyboard_tKeyboard.anCurrentKey[11] & 0x80) != 0 )
      LODWORD(p_tEditDisplacement->vX) = ptAnimCam->aiQTaskRef[2];
    if ( (Keyboard_tKeyboard.anCurrentKey[2] & 0x80) != 0 )
      LODWORD(p_tEditDisplacement->vX) = ptAnimCam->aiQTaskRef[3];
    if ( (Keyboard_tKeyboard.anCurrentKey[3] & 0x80) != 0 )
      LODWORD(p_tEditDisplacement->vX) = ptAnimCam->aiQTaskRef[4];
    if ( (Keyboard_tKeyboard.anCurrentKey[4] & 0x80) != 0 )
      LODWORD(p_tEditDisplacement->vX) = ptAnimCam->aiQTaskRef[5];
    if ( (Keyboard_tKeyboard.anCurrentKey[5] & 0x80) != 0 )
      LODWORD(p_tEditDisplacement->vX) = ptAnimCam->aiQTaskRef[6];
    if ( (Keyboard_tKeyboard.anCurrentKey[6] & 0x80) != 0 )
      LODWORD(p_tEditDisplacement->vX) = ptAnimCam->aiQTaskRef[7];
    if ( (Keyboard_tKeyboard.anCurrentKey[7] & 0x80) != 0 )
      LODWORD(p_tEditDisplacement->vX) = ptAnimCam->aiQTaskRef[8];
    if ( (Keyboard_tKeyboard.anCurrentKey[8] & 0x80) != 0 )
      LODWORD(p_tEditDisplacement->vX) = ptAnimCam->aiQTaskRef[9];
    if ( (Keyboard_tKeyboard.anCurrentKey[9] & 0x80) != 0 )
      LODWORD(p_tEditDisplacement->vX) = ptAnimCam->tAnimCamState.pfRunAnimCam;
    if ( (Keyboard_tKeyboard.anCurrentKey[10] & 0x80) != 0 )
      LODWORD(p_tEditDisplacement->vX) = ptAnimCam->tAnimCamState.pfLastRunAnimCam;
  }
  if ( (Keyboard_tKeyboard.anCurrentKey[10] & 0x80) != 0 )
    ptAnimCam->vEditDeltaAlpha = 0.0;
  if ( (Keyboard_tKeyboard.anCurrentKey[47] & 0x80) != 0 && (Keyboard_tKeyboard.anPreviousKey[47] & 0x80) == 0 )
    *((_BYTE *)&ptAnimCam->eAnimCamMatrixMode + 4) ^= 1u;
  if ( (Keyboard_tKeyboard.anCurrentKey[48] & 0x80) != 0 && (Keyboard_tKeyboard.anPreviousKey[48] & 0x80) == 0 )
    *((_BYTE *)&ptAnimCam->eAnimCamMatrixMode + 5) ^= 1u;
  if ( (Keyboard_tKeyboard.anCurrentKey[49] & 0x80) != 0 && (Keyboard_tKeyboard.anPreviousKey[49] & 0x80) == 0 )
    *((_BYTE *)&ptAnimCam->eAnimCamMatrixMode + 6) ^= 1u;
  return ptAnimCam;
}

// source: h/2/animcam.c:1052  [anchor-mhash]
void __cdecl AnimCam_SetCameraModes(
        struct AnimCam_s *ptAnimCam,
        struct ReadChannelsContext_s *ptReadChannelsContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { double tPos; };
    struct { char igi2_o1[8]; double tPos_8; };
    struct { char igi2_o2[16]; double tPos_16; };
    struct { char igi2_o3[48]; struct GetCameraTargetInfoContext_s tGetCameraTargetInfoContext; };
    char igi2_extent[136];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  unsigned int vX_high; // eax
  struct QReference_s *v3; // eax
  unsigned __int16 *pxObject; // eax
  void (__cdecl *pfHandler)(unsigned __int16 *, struct GetCameraTargetInfoContext_s *); // ecx
  double v6; // st7

  if ( (Keyboard_tKeyboard.anCurrentKey[33] & 0x80u) != 0 && (Keyboard_tKeyboard.anPreviousKey[33] & 0x80) == 0 )
  {
    vX_high = HIDWORD(ptAnimCam->tEditDisplacement.vX);
    if ( vX_high < 0x1000
      && (v3 = Level_atLevelQTaskID[vX_high]) != nullptr
      && (pxObject = (unsigned __int16 *)v3->pxObject) != nullptr
      && (pfHandler = (void (__cdecl *)(unsigned __int16 *, struct GetCameraTargetInfoContext_s *))QTask_aatQTaskFinalEvent[8][pxObject[18]].pfHandler,
          igi2_frame.tGetCameraTargetInfoContext.zName = nullptr,
          pfHandler) )
    {
      pfHandler(pxObject, &igi2_frame.tGetCameraTargetInfoContext);
      igi2_frame.tPos = igi2_frame.tGetCameraTargetInfoContext.tPos.vX
           + igi2_frame.tGetCameraTargetInfoContext.tOrientation.tX.vX * 40960.0
           + igi2_frame.tGetCameraTargetInfoContext.tOrientation.tX.vY * 204800.0;
      igi2_frame.tPos_8 = igi2_frame.tGetCameraTargetInfoContext.tPos.vY
             + igi2_frame.tGetCameraTargetInfoContext.tOrientation.tY.vX * 40960.0
             + igi2_frame.tGetCameraTargetInfoContext.tOrientation.tY.vY * 204800.0;
      v6 = igi2_frame.tGetCameraTargetInfoContext.tPos.vZ
         + igi2_frame.tGetCameraTargetInfoContext.tOrientation.tZ.vX * 40960.0
         + igi2_frame.tGetCameraTargetInfoContext.tOrientation.tZ.vY * 204800.0;
    }
    else
    {
      v6 = igi2_frame.tPos_16;
    }
    *ptReadChannelsContext->pvChannel = 2.0;
    *((_DWORD *)ptReadChannelsContext->pvChannel + 1) = -1082130432;
    ptReadChannelsContext->pvChannel[2] = (float)SHIDWORD(ptAnimCam->tEditDisplacement.vX);
    ptReadChannelsContext->pvChannel[3] = igi2_frame.tPos;
    ptReadChannelsContext->pvChannel[4] = igi2_frame.tPos_8;
    ptReadChannelsContext->pvChannel[5] = v6;
    ptReadChannelsContext->pvChannel[6] = ptAnimCam->tEditDeltaDisplacement.vY;
    ptReadChannelsContext->pvChannel[7] = ptAnimCam->tEditDeltaDisplacement.vZ;
    ptReadChannelsContext->pvChannel[8] = *(double *)&ptAnimCam->vEditUpdateTargetFactor;
    ptReadChannelsContext->pvChannel[18] = (float)*((char *)&ptAnimCam->eAnimCamMatrixMode + 4);
    ptReadChannelsContext->pvChannel[19] = (float)*((char *)&ptAnimCam->eAnimCamMatrixMode + 5);
    ptReadChannelsContext->pvChannel[20] = (float)*((char *)&ptAnimCam->eAnimCamMatrixMode + 6);
  }
  if ( (Keyboard_tKeyboard.anCurrentKey[46] & 0x80) != 0 && (Keyboard_tKeyboard.anPreviousKey[46] & 0x80) == 0 )
  {
    *ptReadChannelsContext->pvChannel = 1.0;
    ptReadChannelsContext->pvChannel[1] = (float)SLODWORD(ptAnimCam->tEditDisplacement.vX);
    ptReadChannelsContext->pvChannel[2] = (float)SHIDWORD(ptAnimCam->tEditDisplacement.vX);
    ptReadChannelsContext->pvChannel[3] = ptAnimCam->tEditDisplacement.vY;
    ptReadChannelsContext->pvChannel[4] = ptAnimCam->tEditDisplacement.vZ;
    ptReadChannelsContext->pvChannel[5] = ptAnimCam->tEditDeltaDisplacement.vX;
    ptReadChannelsContext->pvChannel[6] = ptAnimCam->tEditDeltaDisplacement.vY;
    ptReadChannelsContext->pvChannel[7] = ptAnimCam->tEditDeltaDisplacement.vZ;
    ptReadChannelsContext->pvChannel[8] = *(double *)&ptAnimCam->vEditUpdateTargetFactor;
    ptReadChannelsContext->pvChannel[18] = (float)*((char *)&ptAnimCam->eAnimCamMatrixMode + 4);
    ptReadChannelsContext->pvChannel[19] = (float)*((char *)&ptAnimCam->eAnimCamMatrixMode + 5);
    ptReadChannelsContext->pvChannel[20] = (float)*((char *)&ptAnimCam->eAnimCamMatrixMode + 6);
  }
  if ( (Keyboard_tKeyboard.anCurrentKey[30] & 0x80) != 0 && (Keyboard_tKeyboard.anPreviousKey[30] & 0x80) == 0 )
  {
    *ptReadChannelsContext->pvChannel = 2.0;
    ptReadChannelsContext->pvChannel[1] = (float)SLODWORD(ptAnimCam->tEditDisplacement.vX);
    ptReadChannelsContext->pvChannel[2] = (float)SHIDWORD(ptAnimCam->tEditDisplacement.vX);
    ptReadChannelsContext->pvChannel[3] = ptAnimCam->tEditDisplacement.vY;
    ptReadChannelsContext->pvChannel[4] = ptAnimCam->tEditDisplacement.vZ;
    ptReadChannelsContext->pvChannel[5] = ptAnimCam->tEditDeltaDisplacement.vX;
    ptReadChannelsContext->pvChannel[6] = ptAnimCam->tEditDeltaDisplacement.vY;
    ptReadChannelsContext->pvChannel[7] = ptAnimCam->tEditDeltaDisplacement.vZ;
    ptReadChannelsContext->pvChannel[8] = *(double *)&ptAnimCam->vEditUpdateTargetFactor;
    ptReadChannelsContext->pvChannel[18] = (float)*((char *)&ptAnimCam->eAnimCamMatrixMode + 4);
    ptReadChannelsContext->pvChannel[19] = (float)*((char *)&ptAnimCam->eAnimCamMatrixMode + 5);
    ptReadChannelsContext->pvChannel[20] = (float)*((char *)&ptAnimCam->eAnimCamMatrixMode + 6);
  }
  if ( (Keyboard_tKeyboard.anCurrentKey[19] & 0x80) != 0 && (Keyboard_tKeyboard.anPreviousKey[19] & 0x80) == 0 )
  {
    *ptReadChannelsContext->pvChannel = 3.0;
    ptReadChannelsContext->pvChannel[1] = (float)SLODWORD(ptAnimCam->tEditDisplacement.vX);
    ptReadChannelsContext->pvChannel[2] = (float)SHIDWORD(ptAnimCam->tEditDisplacement.vX);
    ptReadChannelsContext->pvChannel[3] = ptAnimCam->tEditDisplacement.vY;
    ptReadChannelsContext->pvChannel[4] = ptAnimCam->tEditDisplacement.vZ;
    ptReadChannelsContext->pvChannel[5] = ptAnimCam->tEditDeltaDisplacement.vX;
    ptReadChannelsContext->pvChannel[6] = ptAnimCam->tEditDeltaDisplacement.vY;
    ptReadChannelsContext->pvChannel[7] = ptAnimCam->tEditDeltaDisplacement.vZ;
    ptReadChannelsContext->pvChannel[8] = *(double *)&ptAnimCam->vEditUpdateTargetFactor;
    ptReadChannelsContext->pvChannel[18] = (float)*((char *)&ptAnimCam->eAnimCamMatrixMode + 4);
    ptReadChannelsContext->pvChannel[19] = (float)*((char *)&ptAnimCam->eAnimCamMatrixMode + 5);
    ptReadChannelsContext->pvChannel[20] = (float)*((char *)&ptAnimCam->eAnimCamMatrixMode + 6);
  }
  if ( (Keyboard_tKeyboard.anCurrentKey[18] & 0x80) != 0 )
    *ptReadChannelsContext->pvChannel = 4.0;
}

// source: h/2/animcam.c:1224  [size]
void __cdecl AnimCam_DisplayStatus(
        struct AnimCam_s *ptAnimCam,
        struct ReadChannelsContext_s *ptReadChannelsContext)
{
  ;
}

// source: h/2/animcam.c:1281  [anchor-mhash]
void __cdecl AnimCam_ReadChannelsHandler(struct QTask_s *ptQTask, void *pxContext)
{
  int i; // eax
  struct AnimCam_s *v3; // eax

  for ( i = 0; i < 88; i += 4 )
    *(_DWORD *)(i + *(_DWORD *)pxContext) = -998653952;
  v3 = AnimCam_ChangeReadChannelsParameters(
         ptQTask,
         (struct AnimCam_s *)ptQTask,
         (struct ReadChannelsContext_s *)pxContext);
  AnimCam_SetCameraModes(v3, (struct ReadChannelsContext_s *)pxContext);
}

// source: h/2/animcam.c:1319  [anchor-caller]
void __cdecl AnimCam_RunHandler(struct QTask_s *ptQTask)
{
  bool v1; // zf

  if ( (Keyboard_tKeyboard.anCurrentKey[57] & 0x80u) != 0 )
    HIBYTE(ptQTask[10].tQTaskRefList.ptTail) = 0;
  v1 = HIBYTE(ptQTask[10].tQTaskRefList.ptTail) == 0;
  LOBYTE(ptQTask[5].tQTaskRefList.ptTail) = 0;
  if ( !v1 )
    LOBYTE(ptQTask[5].tQTaskRefList.ptTail) = 1;
  AnimCam_Move((struct AnimCam_s *)ptQTask);
}

// source: h/2/animcam.c:1352  [size]
void __cdecl AnimCam_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ;
}

// source: h/2/animcam.c:1364  [size]
void __cdecl AnimCam_GetKeyframeSizeHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = 168;
}

// source: h/2/animcam.c:1380  [size]
void __cdecl AnimCam_SaveKeyframeHandler(struct QTask_s *ptQTask, void *pxContext)
{
  qmemcpy(*(void **)pxContext, &ptQTask[6].ptParent, 0xA8u);
}

// source: h/2/animcam.c:1428  [size]
void __cdecl AnimCam_RestoreKeyframeHandler(struct QTask_s *ptQTask, void *pxContext)
{
  qmemcpy(&ptQTask[6].ptParent, *(void **)pxContext, 0xA8u);
}

// source: h/2/animcam.c:1484  [anchor-strings]
void __cdecl AnimCam_Open()
{
  unsigned __int16 v0; // si
  struct ParameterList_s *v1; // eax
  int v2; // edx

  v0 = QTask_NewQTaskType("AnimCam", 560, CamQTask_eQTaskType, 0, 0);
  AnimCam_eQTaskType = v0;
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 1, AnimCam_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 2, (void (__cdecl *)(struct QTask_s *))AnimCam_DeleteHandler);
  QTask_LinkQTaskEventHandlerFn(v0, 0, AnimCam_CreateHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))AnimCam_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    ParameterList_eUpdateInternalDataQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))AnimCam_UpdateInternalDataHandler);
  QTask_LinkQTaskEventHandlerFn(v0, AnimQTask_eUpdateAnimDataEvent, AnimCam_UpdateAnimDataHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    AnimQTask_eGetChannelDescriptionEvent,
    (void (__cdecl *)(struct QTask_s *, void *))AnimCam_GetChannelDescriptionHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    AnimQTask_eGetKeyframeSizeEvent,
    (void (__cdecl *)(struct QTask_s *, void *))AnimCam_GetKeyframeSizeHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    AnimQTask_eSaveKeyframeEvent,
    (void (__cdecl *)(struct QTask_s *, void *))AnimCam_SaveKeyframeHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    AnimQTask_eRestoreKeyframeEvent,
    (void (__cdecl *)(struct QTask_s *, void *))AnimCam_RestoreKeyframeHandler);
  QTask_LinkQTaskEventHandlerFn(v0, AnimQTask_eReadChannelsEvent, AnimCam_ReadChannelsHandler);
  v1 = (struct ParameterList_s *)Mem_AllocFn(212, 4);
  v2 = Level_eParameterTypeInt32;
  v1->ptParameterListItem = (struct ParameterListItem_s *)&v1[1];
  v1->nParameters = 0;
  v1->nMaxParameters = 10;
  AnimCam_ptParameterList = v1;
  ParameterList_AddParameter(v1, 0xE8u, v2, "TargetID 0", 7u, nullptr);
  ParameterList_AddParameter(AnimCam_ptParameterList, 0xECu, Level_eParameterTypeInt32, "TargetID 1", 7u, nullptr);
  ParameterList_AddParameter(AnimCam_ptParameterList, 0xF0u, Level_eParameterTypeInt32, "TargetID 2", 7u, nullptr);
  ParameterList_AddParameter(AnimCam_ptParameterList, 0xF4u, Level_eParameterTypeInt32, "TargetID 3", 7u, nullptr);
  ParameterList_AddParameter(AnimCam_ptParameterList, 0xF8u, Level_eParameterTypeInt32, "TargetID 4", 7u, nullptr);
  ParameterList_AddParameter(AnimCam_ptParameterList, 0xFCu, Level_eParameterTypeInt32, "TargetID 5", 7u, nullptr);
  ParameterList_AddParameter(AnimCam_ptParameterList, 0x100u, Level_eParameterTypeInt32, "TargetID 6", 7u, nullptr);
  ParameterList_AddParameter(AnimCam_ptParameterList, 0x104u, Level_eParameterTypeInt32, "TargetID 7", 7u, nullptr);
  ParameterList_AddParameter(AnimCam_ptParameterList, 0x108u, Level_eParameterTypeInt32, "TargetID 8", 7u, nullptr);
  ParameterList_AddParameter(AnimCam_ptParameterList, 0x10Cu, Level_eParameterTypeInt32, "TargetID 9", 7u, nullptr);
}

// source: h/2/animcam.c:1528  [size]
void __cdecl AnimCam_Close()
{
  int v0; // esi

  if ( AnimCam_ptParameterList )
  {
    v0 = *(_DWORD *)((unsigned int)&AnimCam_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
  QTask_DeleteQTaskType(AnimCam_eQTaskType);
}

// source: h/2/animcam.c:1547  [size]
struct QTask_s *__cdecl AnimCam_New(struct QTask_s *ptParent, struct QCamera_s *ptQCamera)
{
  struct QTask_s *result; // eax

  result = QTask_NewFn(ptParent, AnimCam_eQTaskType, nullptr);
  result[3].ptParent = (struct QTask_s *)ptQCamera;
  return result;
}
