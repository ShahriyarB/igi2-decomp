/* h/2/vehicletype.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: h/2/vehicletype.c:28  [size]
void __cdecl VehicleType_Open()
{
  ;
}

// source: h/2/vehicletype.c:41  [size]
void __cdecl VehicleType_Close()
{
  ;
}

// source: h/2/vehicletype.c:54  [anchor-mhash]
void __cdecl VehicleType_DefineVehicleType(
        struct VehicleType_s *ptVehicleType,
        int *pnArg,
        struct ArgList_s *ptArgList)
{
  #pragma pack(push, 1)
  union
  {
    struct { float ptWing; };
    struct { char igi2_o1[4]; float vArea; };
    struct { char igi2_o2[8]; float vPosX; };
    struct { char igi2_o3[12]; float vPosY; };
    struct { char igi2_o4[16]; float vPosZ; };
    struct { char igi2_o5[20]; float vNormalX; };
    struct { char igi2_o6[24]; float vNormalY; };
    struct { char igi2_o7[32]; int eDataType; };
    struct { char igi2_o8[36]; float pxData; };
    struct { char igi2_o9[40]; float v65; };
    struct { char igi2_o10[44]; float v66; };
    struct { char igi2_o11[48]; float v67; };
    struct { char igi2_o12[52]; float v68; };
    struct { char igi2_o13[56]; float v69; };
    struct { char igi2_o14[60]; float v70; };
    struct { char igi2_o15[64]; int iWing; };
    struct { char igi2_o16[68]; double v72; };
    struct { char igi2_o17[76]; double v73; };
    struct { char igi2_o18[84]; double v74; };
    struct { char igi2_o19[92]; double v75; };
    struct { char igi2_o20[100]; double v76; };
    struct { char igi2_o21[108]; double v77; };
    char igi2_extent[116];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v4; // eax
  double v5; // st7
  int v6; // eax
  double v7; // st7
  int v8; // eax
  double v9; // st7
  int v10; // eax
  double v11; // st7
  int v12; // eax
  double v13; // st7
  int v14; // eax
  double v15; // st7
  int v16; // eax
  double v17; // st7
  int v18; // eax
  double v19; // st7
  int v20; // eax
  double v21; // st7
  int v22; // eax
  double v23; // st7
  int v24; // eax
  int v25; // eax
  int v26; // eax
  double v27; // st7
  int v28; // eax
  int v29; // eax
  double v30; // st7
  int v31; // eax
  int v32; // eax
  double v33; // st7
  int v34; // eax
  int v35; // eax
  double v36; // st7
  int v37; // eax
  int v38; // eax
  double v39; // st7
  int v40; // eax
  int v41; // eax
  double v42; // st7
  int isQVM; // ecx
  int v44; // eax
  double v45; // st7
  int v46; // ecx
  int v47; // eax
  int v48; // edx
  int nWing; // ecx
  int v50; // eax
  double v51; // st7
  int v52; // eax
  double v53; // st7
  int v54; // eax
  double v55; // st7

  v4 = (*pnArg)++;
  if ( ptArgList->isQVM )
  {
    *(float *)&igi2_frame.eDataType = 0.0;
    QVM_EvalArg(&igi2_frame.eDataType, 4, ptArgList, v4, 2);
    v5 = *(float *)&igi2_frame.eDataType;
  }
  else
  {
    v5 = Expression_EvalFloat(ptArgList->aptExpression[v4]);
  }
  ptVehicleType->vMaxSpeed = v5;
  v6 = (*pnArg)++;
  if ( ptArgList->isQVM )
  {
    *(float *)&igi2_frame.eDataType = 0.0;
    QVM_EvalArg(&igi2_frame.eDataType, 4, ptArgList, v6, 2);
    v7 = *(float *)&igi2_frame.eDataType;
  }
  else
  {
    v7 = Expression_EvalFloat(ptArgList->aptExpression[v6]);
  }
  ptVehicleType->vMaxDeltaAlpha = v7;
  v8 = (*pnArg)++;
  if ( ptArgList->isQVM )
  {
    *(float *)&igi2_frame.eDataType = 0.0;
    QVM_EvalArg(&igi2_frame.eDataType, 4, ptArgList, v8, 2);
    v9 = *(float *)&igi2_frame.eDataType;
  }
  else
  {
    v9 = Expression_EvalFloat(ptArgList->aptExpression[v8]);
  }
  ptVehicleType->vDeltaAlphaInertia = v9;
  v10 = (*pnArg)++;
  if ( ptArgList->isQVM )
  {
    *(float *)&igi2_frame.eDataType = 0.0;
    QVM_EvalArg(&igi2_frame.eDataType, 4, ptArgList, v10, 2);
    v11 = *(float *)&igi2_frame.eDataType;
  }
  else
  {
    v11 = Expression_EvalFloat(ptArgList->aptExpression[v10]);
  }
  ptVehicleType->vMaxDeltaBeta = v11;
  v12 = (*pnArg)++;
  if ( ptArgList->isQVM )
  {
    *(float *)&igi2_frame.eDataType = 0.0;
    QVM_EvalArg(&igi2_frame.eDataType, 4, ptArgList, v12, 2);
    v13 = *(float *)&igi2_frame.eDataType;
  }
  else
  {
    v13 = Expression_EvalFloat(ptArgList->aptExpression[v12]);
  }
  ptVehicleType->vDeltaBetaInertia = v13;
  v14 = (*pnArg)++;
  if ( ptArgList->isQVM )
  {
    *(float *)&igi2_frame.eDataType = 0.0;
    QVM_EvalArg(&igi2_frame.eDataType, 4, ptArgList, v14, 2);
    v15 = *(float *)&igi2_frame.eDataType;
  }
  else
  {
    v15 = Expression_EvalFloat(ptArgList->aptExpression[v14]);
  }
  ptVehicleType->vMaxDeltaGamma = v15;
  v16 = (*pnArg)++;
  if ( ptArgList->isQVM )
  {
    *(float *)&igi2_frame.eDataType = 0.0;
    QVM_EvalArg(&igi2_frame.eDataType, 4, ptArgList, v16, 2);
    v17 = *(float *)&igi2_frame.eDataType;
  }
  else
  {
    v17 = Expression_EvalFloat(ptArgList->aptExpression[v16]);
  }
  ptVehicleType->vDeltaGammaInertia = v17;
  v18 = (*pnArg)++;
  if ( ptArgList->isQVM )
  {
    *(float *)&igi2_frame.eDataType = 0.0;
    QVM_EvalArg(&igi2_frame.eDataType, 4, ptArgList, v18, 2);
    v19 = *(float *)&igi2_frame.eDataType;
  }
  else
  {
    v19 = Expression_EvalFloat(ptArgList->aptExpression[v18]);
  }
  ptVehicleType->vMaxThrust = v19;
  v20 = (*pnArg)++;
  if ( ptArgList->isQVM )
  {
    *(float *)&igi2_frame.eDataType = 0.0;
    QVM_EvalArg(&igi2_frame.eDataType, 4, ptArgList, v20, 2);
    v21 = *(float *)&igi2_frame.eDataType;
  }
  else
  {
    v21 = Expression_EvalFloat(ptArgList->aptExpression[v20]);
  }
  ptVehicleType->vThrustInertia = v21;
  v22 = (*pnArg)++;
  if ( ptArgList->isQVM )
  {
    *(float *)&igi2_frame.eDataType = 0.0;
    QVM_EvalArg(&igi2_frame.eDataType, 4, ptArgList, v22, 2);
    v23 = *(float *)&igi2_frame.eDataType;
  }
  else
  {
    v23 = Expression_EvalFloat(ptArgList->aptExpression[v22]);
  }
  ptVehicleType->vThrustStartStopInertia = v23;
  v24 = (*pnArg)++;
  if ( ptArgList->isQVM )
  {
    *(float *)&igi2_frame.eDataType = 0.0;
    QVM_EvalArg(&igi2_frame.eDataType, 4, ptArgList, v24, 1);
    v25 = igi2_frame.eDataType;
  }
  else
  {
    v25 = Expression_EvalInt(ptArgList->aptExpression[v24]);
  }
  ptVehicleType->nWing = v25;
  *(float *)&igi2_frame.iWing = 0.0;
  if ( v25 > 0 )
  {
    igi2_frame.eDataType = (int)ptVehicleType->atWing;
    do
    {
      v26 = *pnArg + 6;
      if ( ptArgList->isQVM )
      {
        igi2_frame.pxData = 0.0;
        QVM_EvalArg(&igi2_frame.pxData, 4, ptArgList, v26, 2);
        v27 = igi2_frame.pxData;
      }
      else
      {
        v27 = Expression_EvalFloat(ptArgList->aptExpression[v26]);
      }
      v28 = *pnArg;
      igi2_frame.v72 = v27;
      v29 = v28 + 5;
      if ( ptArgList->isQVM )
      {
        igi2_frame.v65 = 0.0;
        QVM_EvalArg(&igi2_frame.v65, 4, ptArgList, v29, 2);
        v30 = igi2_frame.v65;
      }
      else
      {
        v30 = Expression_EvalFloat(ptArgList->aptExpression[v29]);
      }
      v31 = *pnArg;
      igi2_frame.v73 = v30;
      v32 = v31 + 4;
      if ( ptArgList->isQVM )
      {
        igi2_frame.v66 = 0.0;
        QVM_EvalArg(&igi2_frame.v66, 4, ptArgList, v32, 2);
        v33 = igi2_frame.v66;
      }
      else
      {
        v33 = Expression_EvalFloat(ptArgList->aptExpression[v32]);
      }
      v34 = *pnArg;
      igi2_frame.v74 = v33;
      v35 = v34 + 3;
      if ( ptArgList->isQVM )
      {
        igi2_frame.v67 = 0.0;
        QVM_EvalArg(&igi2_frame.v67, 4, ptArgList, v35, 2);
        v36 = igi2_frame.v67;
      }
      else
      {
        v36 = Expression_EvalFloat(ptArgList->aptExpression[v35]);
      }
      v37 = *pnArg;
      igi2_frame.v75 = v36;
      v38 = v37 + 2;
      if ( ptArgList->isQVM )
      {
        igi2_frame.v68 = 0.0;
        QVM_EvalArg(&igi2_frame.v68, 4, ptArgList, v38, 2);
        v39 = igi2_frame.v68;
      }
      else
      {
        v39 = Expression_EvalFloat(ptArgList->aptExpression[v38]);
      }
      v40 = *pnArg;
      igi2_frame.v76 = v39;
      v41 = v40 + 1;
      if ( ptArgList->isQVM )
      {
        igi2_frame.v69 = 0.0;
        QVM_EvalArg(&igi2_frame.v69, 4, ptArgList, v41, 2);
        v42 = igi2_frame.v69;
      }
      else
      {
        v42 = Expression_EvalFloat(ptArgList->aptExpression[v41]);
      }
      isQVM = ptArgList->isQVM;
      igi2_frame.v77 = v42;
      v44 = *pnArg;
      if ( isQVM )
      {
        igi2_frame.v70 = 0.0;
        QVM_EvalArg(&igi2_frame.v70, 4, ptArgList, v44, 2);
        v45 = igi2_frame.v70;
      }
      else
      {
        v45 = Expression_EvalFloat(ptArgList->aptExpression[v44]);
      }
      igi2_frame.vNormalY = igi2_frame.v72;
      igi2_frame.vNormalX = igi2_frame.v73;
      igi2_frame.vPosZ = igi2_frame.v74;
      igi2_frame.vPosY = igi2_frame.v75 * 4096.0;
      igi2_frame.vPosX = igi2_frame.v76 * 4096.0;
      igi2_frame.vArea = igi2_frame.v77 * 4096.0;
      v46 = igi2_frame.eDataType;
      igi2_frame.ptWing = v45;
      Wing_Init((struct Wing_t *)igi2_frame.eDataType, igi2_frame.ptWing, igi2_frame.vArea, igi2_frame.vPosX, igi2_frame.vPosY, igi2_frame.vPosZ, igi2_frame.vNormalX, igi2_frame.vNormalY);
      v47 = igi2_frame.iWing;
      *pnArg += 7;
      v48 = v46;
      nWing = ptVehicleType->nWing;
      igi2_frame.iWing = v47 + 1;
      igi2_frame.eDataType = v48 + 28;
    }
    while ( v47 + 1 < nWing );
  }
  v50 = (*pnArg)++;
  if ( ptArgList->isQVM )
  {
    *(float *)&igi2_frame.iWing = 0.0;
    QVM_EvalArg(&igi2_frame.iWing, 4, ptArgList, v50, 2);
    v51 = *(float *)&igi2_frame.iWing;
  }
  else
  {
    v51 = Expression_EvalFloat(ptArgList->aptExpression[v50]);
  }
  ptVehicleType->vViewconeLength = v51 * 4096.0;
  v52 = (*pnArg)++;
  if ( ptArgList->isQVM )
  {
    *(float *)&igi2_frame.iWing = 0.0;
    QVM_EvalArg(&igi2_frame.iWing, 4, ptArgList, v52, 2);
    v53 = *(float *)&igi2_frame.iWing;
  }
  else
  {
    v53 = Expression_EvalFloat(ptArgList->aptExpression[v52]);
  }
  ptVehicleType->vViewconeAlpha = v53 * 0.5 * 0.01745329238474369;
  v54 = (*pnArg)++;
  if ( ptArgList->isQVM )
  {
    *(float *)&igi2_frame.iWing = 0.0;
    QVM_EvalArg(&igi2_frame.iWing, 4, ptArgList, v54, 2);
    v55 = *(float *)&igi2_frame.iWing;
  }
  else
  {
    v55 = Expression_EvalFloat(ptArgList->aptExpression[v54]);
  }
  ptVehicleType->vViewconeGamma = v55 * 0.5 * 0.01745329238474369;
}
