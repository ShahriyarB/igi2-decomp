/* h/2/wind.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: h/2/wind.c:91  [anchor-mhash]
void __cdecl Wind_ComputeWind(float vTime, float *pvWind)
{
  struct Wind_s *v2; // ecx
  long double vGustUpperClamp; // st7

  v2 = Wind_ptWindTask;
  vGustUpperClamp = (sin(vTime * Wind_ptWindTask->vGustSecondaryFrequency * 6.2831854820251465)
                   + sin(vTime * Wind_ptWindTask->vGustFrequency * 6.2831854820251465))
                  * Wind_ptWindTask->vGustAmplitude
                  * 0.5;
  if ( Wind_ptWindTask->vGustLowerClamp <= vGustUpperClamp )
  {
    if ( Wind_ptWindTask->vGustUpperClamp < vGustUpperClamp )
      vGustUpperClamp = Wind_ptWindTask->vGustUpperClamp;
  }
  else
  {
    vGustUpperClamp = Wind_ptWindTask->vGustLowerClamp;
  }
  pvWind[1] = vGustUpperClamp;
  *pvWind = vGustUpperClamp;
  pvWind[1] = (sin(vTime * v2->vMainFrequency * 6.2831854820251465) + sin(vTime * v2->vSecondaryFrequency * 6.2831854820251465))
            * v2->vMainAmplitude
            * 0.5
            + v2->vConstantStrength
            + vGustUpperClamp;
  *pvWind = (sin(vTime * v2->vMainFrequency * 6.2831854820251465 + v2->vPhaseShift)
           + sin(v2->vMainFrequency * v2->vSecondaryFrequency * vTime * 6.2831854820251465))
          * v2->vMainAmplitude
          * 0.5
          + v2->vConstantStrength
          + vGustUpperClamp;
}

// source: h/2/wind.c:110  [anchor-hash]
void __cdecl Wind_RunHandler(struct QTask_s *ptQTask)
{
  g_vTime = g_vTime + 0.03333333507180214;
}

void __cdecl sub_5FC9E0(struct Wind_s *a1)
{
  if ( !Wind_ptWindTask )
  {
    Wind_ptWindTask = a1;
    a1->vWindSpeed = 1.0;
    a1->vConstantStrength = 0.0;
    a1->vGustAmplitude = 1.5;
    a1->vGustFrequency = 0.10000000149011612;
    a1->vGustLowerClamp = 0.0;
    a1->vGustUpperClamp = 1.0;
    a1->vMainAmplitude = 0.20000000298023224;
    a1->vMainFrequency = 0.30000001192092896;
    a1->vPhaseShift = 0.20000000298023224;
    a1->vWindGamma = 1.0;
    a1->isPreview = 0;
  }
}

void __cdecl sub_5FCA50(struct QTask_s *a1)
{
  Wind_ptWindTask = nullptr;
}

void __cdecl sub_5FCA60(struct Wind_s *a1)
{
  sub_5FC9E0(a1);
}

// source: h/2/wind.c:178  [size]
void __cdecl Wind_DeleteHandler(struct QTask_s *ptQTask)
{
  Wind_ptWindTask = nullptr;
}

// source: h/2/wind.c:194  [anchor-mhash]
void __cdecl Wind_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  double v2; // st7
  unsigned int v3; // edx
  unsigned int v4; // edx

  if ( *(float *)&ptQTask[9].tQTaskChildren.ptTail == 0.0 )
  {
    if ( *(float *)&ptQTask[9].tQTaskChildren.ptHead == 0.0 )
      goto LABEL_6;
    v2 = Direct3D_vScale * *(float *)&ptQTask[9].tQTaskChildren.ptHead;
  }
  else
  {
    v2 = Direct3D_vScale * *(float *)&ptQTask[9].tQTaskChildren.ptTail;
  }
  *(float *)&ptQTask[9].eQTaskType = v2 * 81920.0;
LABEL_6:
  if ( *(float *)&ptQTask[9].eQTaskType == 0.0 )
    *(_DWORD *)&ptQTask[9].eQTaskType = 1065353216;
  if ( *(float *)&ptQTask[10].ptPrev == 0.0 )
  {
    v3 = (Wind_tRandomState.anRandom[0] >> 7) ^ Wind_tRandomState.anRandom[2];
    Wind_tRandomState.anRandom[0] += v3 ^ Wind_tRandomState.anRandom[1];
    Wind_tRandomState.anRandom[2] = v3;
    Wind_tRandomState.anRandom[1] ^= v3;
    *(float *)&ptQTask[10].ptPrev = ((double)LOWORD(Wind_tRandomState.anRandom[0]) * 0.0000152587890625 + 1.0)
                                  * 0.4000000059604645
                                  * *(float *)&ptQTask[9].tQTaskChildren.ptMiddle;
  }
  if ( *(float *)&ptQTask[10].tQTaskChildren.ptHead == 0.0 )
  {
    v4 = (Wind_tRandomState.anRandom[0] >> 7) ^ Wind_tRandomState.anRandom[2];
    Wind_tRandomState.anRandom[0] += v4 ^ Wind_tRandomState.anRandom[1];
    Wind_tRandomState.anRandom[2] = v4;
    Wind_tRandomState.anRandom[1] ^= v4;
    *(float *)&ptQTask[10].tQTaskChildren.ptHead = ((double)LOWORD(Wind_tRandomState.anRandom[0]) * 0.0000152587890625
                                                  + 1.0)
                                                 * 0.4000000059604645
                                                 * *(float *)&ptQTask[9].tQTaskRefList.ptHead;
  }
  *(float *)&ptQTask[10].tQTaskRefList.ptHead = cos(*(float *)&ptQTask[10].ptNext);
  *(float *)&ptQTask[10].tQTaskRefList.ptMiddle = sin(*(float *)&ptQTask[10].ptNext);
}

// source: h/2/wind.c:235  [size]
void __cdecl Wind_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = Wind_ptParameterList;
}

// source: h/2/wind.c:252  [anchor-mhash]
void __cdecl Wind_GetWindVector(
        struct real32x3_t *ptPos,
        struct real32x3_t *ptWindVector,
        int iChannel)
{
  struct Wind_s *v3; // eax
  double v4; // st7
  double v5; // st7

  v3 = Wind_ptWindTask;
  if ( Wind_ptWindTask )
  {
    v4 = (ptPos->vY * Wind_ptWindTask->tWindDirection.vY + ptPos->vX * Wind_ptWindTask->tWindDirection.vX - Wind_vX1)
       * Wind_ptWindTask->avInterpolationCoeffs[iChannel]
       + Wind_avNearPoint[iChannel];
    ptWindVector->vX = v4 * Wind_ptWindTask->tWindDirection.vX;
    v5 = v4 * v3->tWindDirection.vY;
    ptWindVector->vZ = 0.0;
    ptWindVector->vY = v5;
  }
  else
  {
    ptWindVector->vX = 0.0;
    ptWindVector->vY = 0.0;
    ptWindVector->vZ = 0.0;
  }
}

// source: h/2/wind.c:280  [anchor-mhash]
void __cdecl Wind_Init(struct real32x3_t *ptPos, float vRadius)
{
  struct Wind_s *v2; // esi
  double v3; // st7
  double v4; // st7
  double v5; // st7
  float vTime; // [esp+0h] [ebp-Ch]
  float vTimea; // [esp+0h] [ebp-Ch]
  float vX; // [esp+8h] [ebp-4h]

  v2 = Wind_ptWindTask;
  if ( Wind_ptWindTask )
  {
    v3 = Wind_ptWindTask->tWindDirection.vY * ptPos->vY + Wind_ptWindTask->tWindDirection.vX * ptPos->vX;
    vX = v3;
    v4 = v3 - vRadius;
    Wind_vX1 = v4;
    vTime = v4 / Wind_ptWindTask->vWindSpeed + g_vTime;
    Wind_ComputeWind(vTime, Wind_avNearPoint);
    vTimea = (vX + vRadius) / v2->vWindSpeed + g_vTime;
    Wind_ComputeWind(vTimea, Wind_avFarPoint);
    v5 = 1.0 / vRadius;
    v2->avInterpolationCoeffs[0] = (Wind_avFarPoint[0] - Wind_avNearPoint[0]) * v5 * 0.5;
    v2->avInterpolationCoeffs[1] = (Wind_avFarPoint[1] - Wind_avNearPoint[1]) * v5 * 0.5;
  }
}

// source: h/2/wind.c:310  [size]
unsigned __int16 __cdecl Wind_GetQTaskType()
{
  return Wind_eQTaskType;
}

// source: h/2/wind.c:323  [anchor-strings]
void __cdecl Wind_Open()
{
  unsigned __int16 BaseQTaskType; // ax
  unsigned __int16 v1; // si
  struct ParameterList_s *v2; // eax
  int v3; // edx

  BaseQTaskType = QTask_GetBaseQTaskType();
  v1 = QTask_NewQTaskType("Wind", 432, BaseQTaskType, 0, 0);
  Wind_eQTaskType = v1;
  QTask_LinkQTaskEventHandlerFn(v1, 0, (void (__cdecl *)(struct QTask_s *, void *))sub_5FC9E0);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 2, (void (__cdecl *)(struct QTask_s *))sub_5FCA50);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 1, (void (__cdecl *)(struct QTask_s *))Wind_RunHandler);
  QTask_LinkQTaskEventHandlerFn(v1, ParameterList_eUpdateInternalDataQTaskEvent, Wind_UpdateInternalDataHandler);
  QTask_LinkQTaskEventHandlerFn(
    v1,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Wind_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(
    v1,
    DynCubeObj_eDynCubeObjRemoveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Wind_DeleteHandler);
  QTask_LinkQTaskEventHandlerFn(
    v1,
    DynCubeObj_eDynCubeObjRegisterQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))sub_5FCA60);
  QTask_LinkQTaskEventHandlerFn(
    v1,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveHandler);
  v2 = (struct ParameterList_s *)Mem_AllocFn(212, 4);
  v3 = Level_eParameterTypeReal32;
  v2->ptParameterListItem = (struct ParameterListItem_s *)&v2[1];
  v2->nParameters = 0;
  v2->nMaxParameters = 10;
  Wind_ptParameterList = v2;
  ParameterList_AddParameter(v2, 0x174u, v3, "Main Frequency", 7u, nullptr);
  ParameterList_AddParameter(Wind_ptParameterList, 0x17Cu, Level_eParameterTypeReal32, "Gust Frequency", 7u, nullptr);
  ParameterList_AddParameter(Wind_ptParameterList, 0x170u, Level_eParameterTypeReal32, "Main Amplitude", 7u, nullptr);
  ParameterList_AddParameter(Wind_ptParameterList, 0x178u, Level_eParameterTypeReal32, "Gust Amplitude", 7u, nullptr);
  ParameterList_AddParameter(Wind_ptParameterList, 0x16Cu, Level_eParameterTypeReal32, "Constant Strength", 7u, nullptr);
  ParameterList_AddParameter(Wind_ptParameterList, 0x180u, Level_eParameterTypeReal32, "Gust Lower Clamp", 7u, nullptr);
  ParameterList_AddParameter(Wind_ptParameterList, 0x184u, Level_eParameterTypeReal32, "Gust Upper Clamp", 7u, nullptr);
  ParameterList_AddParameter(
    Wind_ptParameterList,
    0x188u,
    Level_eParameterTypeReal32,
    "Phase shift between morph channels",
    7u,
    nullptr);
  ParameterList_AddParameter(Wind_ptParameterList, 0x190u, Level_eParameterTypeAngle, "Wind direction", 7u, nullptr);
  ParameterList_AddParameter(Wind_ptParameterList, 0x168u, Level_eParameterTypebool8, "Preview", 7u, nullptr);
  Wind_tRandomState.anRandom[0] = -923264994;
  Wind_tRandomState.anRandom[1] = -1158219946;
  Wind_tRandomState.anRandom[2] = 2045577933;
}

// source: h/2/wind.c:366  [size]
void __cdecl Wind_Close()
{
  int v0; // esi

  if ( Wind_ptParameterList )
  {
    v0 = *(_DWORD *)((unsigned int)&Wind_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
  QTask_DeleteQTaskType(Wind_eQTaskType);
}
