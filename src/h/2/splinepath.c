/* h/2/splinepath.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: h/2/splinepath.c:144  [size]
void __cdecl SplinePath_SetFlowFrequency(float vFrequency)
{
  SplinePath_vFlowFrequency = vFrequency;
}

// source: h/2/splinepath.c:157  [size]
enum bool __cdecl SplinePath_SetDisplay(enum bool isDisplay)
{
  SplinePath_isDisplay = isDisplay;
  return isDisplay;
}

// source: h/2/splinepath.c:174  [anchor-mhash]
void __cdecl SplinePathNodeQTask_GetCameraTargetInfoHandler(struct QTask_s *ptQTask, void *pxContext)
{
  char *v2; // eax

  qmemcpy(pxContext, &ptQTask[1], 0x18u);
  *((_DWORD *)pxContext + 6) = 0;
  *((_DWORD *)pxContext + 7) = 0;
  *((_DWORD *)pxContext + 8) = 0;
  qmemcpy((char *)pxContext + 36, &ptQTask[1].tQTaskRefList.ptMiddle, 0x28u);
  *((_DWORD *)pxContext + 19) = 1184890880;
  v2 = *((char **)pxContext + 20);
  if ( v2 )
    strcpy(v2, "SplinePathNode");
}

// source: h/2/splinepath.c:211  [size]
void __cdecl SplinePathNodeQTask_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = SplinePathNodeQTask_ptParameterList;
}

// source: h/2/splinepath.c:227  [anchor-mhash]
void __cdecl SplinePathNodeQTask_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *ptParent; // esi
  double v3; // st7
  struct QTask_s *v4; // eax

  ptParent = ptQTask->ptParent;
  if ( *(float *)&ptQTask[3].ptParent <= 0.0 )
    v3 = 0.0;
  else
    v3 = *(float *)&ptQTask[3].ptParent;
  v4 = ptQTask->ptParent;
  *(float *)&ptQTask[3].ptParent = v3;
  SplinePathDynCubeObj_ResetPath(v4);
  SplinePathDynCubeObj_InitPath(ptParent);
  SplinePathDynCubeObj_UpdateOrientations(ptParent);
}

// source: h/2/splinepath.c:286  [anchor-mhash]
void __cdecl SplinePathNodeQTask_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ptQTask[1].tQTaskRefList.ptTail = nullptr;
  ptQTask[1].ptParent = nullptr;
  *(_DWORD *)&ptQTask[1].eQTaskType = 0;
  ptQTask[2].ptPrev = nullptr;
  ptQTask[2].tQTaskChildren.ptHead = nullptr;
  ptQTask[2].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[2].tQTaskRefList.ptHead = nullptr;
  ptQTask[1].ptNext = nullptr;
  ptQTask[1].ptPrev = nullptr;
  ptQTask[1].tQTaskChildren.ptHead = nullptr;
  ptQTask[1].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[1].tQTaskChildren.ptTail = nullptr;
  ptQTask[1].tQTaskRefList.ptHead = nullptr;
  ptQTask[2].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[2].tQTaskRefList.ptTail = nullptr;
  ptQTask[2].ptParent = nullptr;
  ptQTask[3].ptNext = nullptr;
  ptQTask[3].tQTaskChildren.ptHead = nullptr;
  ptQTask[3].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[3].tQTaskChildren.ptTail = nullptr;
  ptQTask[3].tQTaskRefList.ptHead = nullptr;
  ptQTask[3].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[3].tQTaskRefList.ptTail = nullptr;
  ptQTask[4].ptNext = nullptr;
  ptQTask[3].ptParent = nullptr;
  *(_DWORD *)&ptQTask[3].eQTaskType = 0;
  LOBYTE(ptQTask[5].ptPrev) = 0;
  ptQTask[1].tQTaskRefList.ptMiddle = (struct QReference_s *)1065353216;
  ptQTask[2].ptNext = (struct QTask_s *)1065353216;
  ptQTask[2].tQTaskChildren.ptTail = (struct QTask_s *)1065353216;
  *(_DWORD *)&ptQTask[2].eQTaskType = 1065353216;
  BYTE1(ptQTask[5].ptPrev) = 1;
  memset(&ptQTask[4].ptPrev, 0, sizeof(struct QTask_s));
}

// source: h/2/splinepath.c:341  [anchor-caller]
void __cdecl SplinePathNodeQTask_DeleteHandler(struct QTask_s *ptQTask)
{
  SplinePathDynCubeObj_RemoveNode(
    (struct SplinePathDynCubeObj_s *)ptQTask->ptParent,
    (struct SplinePathNodeQTask_s *)ptQTask);
}

// source: h/2/splinepath.c:389  [anchor-hash]
void __cdecl SplinePathNodeQTask_Open()
{
  unsigned __int16 BaseQTaskType; // ax
  unsigned __int16 v1; // si
  struct ParameterList_s *v2; // eax
  int v3; // edx

  BaseQTaskType = QTask_GetBaseQTaskType();
  v1 = QTask_NewQTaskType("SplinePathNodeQTask", 208, BaseQTaskType, 0, 0);
  SplinePathNodeQTask_eQTaskType = v1;
  QTask_LinkQTaskEventHandlerFn(v1, 0, SplinePathNodeQTask_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 2, SplinePathNodeQTask_DeleteHandler);
  QTask_LinkQTaskEventHandlerFn(
    v1,
    ParameterList_eUpdateInternalDataQTaskEvent,
    SplinePathNodeQTask_UpdateInternalDataHandler);
  QTask_LinkQTaskEventHandlerFn(
    v1,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))SplinePathNodeQTask_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(v1, 8, SplinePathNodeQTask_GetCameraTargetInfoHandler);
  v2 = (struct ParameterList_s *)Mem_AllocFn(152, 4);
  v3 = Level_eParameterTypeObjectPos;
  v2->ptParameterListItem = (struct ParameterListItem_s *)&v2[1];
  v2->nParameters = 0;
  v2->nMaxParameters = 7;
  SplinePathNodeQTask_ptParameterList = v2;
  ParameterList_AddParameter(v2, 0x28u, v3, "Position", 7u, nullptr);
  ParameterList_AddParameter(
    SplinePathNodeQTask_ptParameterList,
    0x40u,
    Level_eParameterTypeReal32x9,
    "Orientation",
    7u,
    nullptr);
  ParameterList_AddParameter(
    SplinePathNodeQTask_ptParameterList,
    0xCCu,
    Level_eParameterTypebool8,
    "Use Free Orientation",
    7u,
    nullptr);
  ParameterList_AddParameter(
    SplinePathNodeQTask_ptParameterList,
    0x98u,
    Level_eParameterTypeReal32,
    "Speed (KMH)",
    7u,
    nullptr);
  ParameterList_AddParameter(
    SplinePathNodeQTask_ptParameterList,
    0x9Cu,
    Level_eParameterTypeReal32,
    "Time from start (Sec)",
    7u,
    nullptr);
  ParameterList_AddParameter(
    SplinePathNodeQTask_ptParameterList,
    0x80u,
    Level_eParameterTypeReal64x3,
    "Tangent",
    7u,
    nullptr);
  ParameterList_AddParameter(
    SplinePathNodeQTask_ptParameterList,
    0xCDu,
    Level_eParameterTypebool8,
    "UseComputedTangent",
    7u,
    nullptr);
  QTask_LinkQTaskEventHandlerFn(
    SplinePathNodeQTask_eQTaskType,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveNoChildrenHandler);
}

// source: h/2/splinepath.c:433  [anchor-callee]
void __cdecl SplinePathNodeQTask_Close()
{
  int v0; // esi

  if ( SplinePathNodeQTask_ptParameterList )
  {
    v0 = *(_DWORD *)((unsigned int)&SplinePathNodeQTask_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
  QTask_DeleteQTaskType(SplinePathNodeQTask_eQTaskType);
  SplinePathNodeQTask_eQTaskType = 512;
}

// source: h/2/splinepath.c:452  [size]
float __cdecl SplinePathNodeQTask_GetSpeed(struct QTask_s *ptQTask)
{
  return *(float *)&ptQTask[3].ptParent;
}

// source: h/2/splinepath.c:471  [size]
float __cdecl SplinePathNodeQTask_GetDistanceToNext(struct QTask_s *ptQTask)
{
  return *(float *)&ptQTask[4].ptNext;
}

// source: h/2/splinepath.c:492  [anchor-mhash]
void __cdecl SplinePathNodeQTask_LimitOrientation(struct SplinePathNodeQTask_s *ptNode)
{
  double vX; // st7
  double vY; // st5
  double vZ; // st4
  long double v4; // st6
  long double v5; // st6
  long double v6; // st6
  double v7; // st5
  long double v8; // st7
  long double v9; // rt1
  long double v10; // st5
  float v11; // [esp+8h] [ebp-38h]
  float v12; // [esp+Ch] [ebp-34h]
  float tZa; // [esp+10h] [ebp-30h]
  float tZ; // [esp+10h] [ebp-30h]
  float tZ_4a; // [esp+14h] [ebp-2Ch]
  float tZ_4; // [esp+14h] [ebp-2Ch]
  float tZ_8a; // [esp+18h] [ebp-28h]
  float tZ_8; // [esp+18h] [ebp-28h]
  float tX; // [esp+1Ch] [ebp-24h]
  float tX_4; // [esp+20h] [ebp-20h]
  float tX_8; // [esp+24h] [ebp-1Ch]
  float tTemp_; // [esp+28h] [ebp-18h]
  float tTemp_a; // [esp+28h] [ebp-18h]
  float tTemp__4; // [esp+2Ch] [ebp-14h]
  float tTemp__4a; // [esp+2Ch] [ebp-14h]
  float tTemp__8; // [esp+30h] [ebp-10h]
  float tTemp__8a; // [esp+30h] [ebp-10h]
  float tTemp__8b; // [esp+30h] [ebp-10h]
  float tY; // [esp+34h] [ebp-Ch]
  float tY_4; // [esp+38h] [ebp-8h]
  float tY_8a; // [esp+3Ch] [ebp-4h]
  float tY_8; // [esp+3Ch] [ebp-4h]

  if ( ptNode->tTangent.vX == 0.0 && ptNode->tTangent.vY == 0.0 && ptNode->tTangent.vZ == 0.0 )
  {
    ptNode->tOrientation.tX.vX = 1.0;
    ptNode->tOrientation.tX.vY = 0.0;
    ptNode->tOrientation.tX.vZ = 0.0;
    ptNode->tOrientation.tY.vX = 0.0;
    ptNode->tOrientation.tY.vY = 1.0;
    ptNode->tOrientation.tZ.vX = 0.0;
    ptNode->tOrientation.tZ.vY = 0.0;
    ptNode->tOrientation.nOps = 0;
    ptNode->tOrientation.tY.vZ = 0.0;
    ptNode->tOrientation.tZ.vZ = 1.0;
  }
  else if ( !ptNode->isFreeOrientation )
  {
    vX = ptNode->tTangent.vX;
    vY = ptNode->tTangent.vY;
    tZa = ptNode->tOrientation.tX.vZ;
    v11 = vY;
    vZ = ptNode->tTangent.vZ;
    tZ_8a = ptNode->tOrientation.tZ.vZ;
    v12 = vZ;
    tZ_4a = ptNode->tOrientation.tY.vZ;
    tTemp_ = vY * tZ_8a - vZ * tZ_4a;
    tX = tTemp_;
    tTemp__4 = -(vX * tZ_8a - vZ * tZa);
    tX_4 = tTemp__4;
    tTemp__8 = vX * tZ_4a - vY * tZa;
    tX_8 = tTemp__8;
    if ( tTemp_ == 0.0 && tTemp__4 == 0.0 && tTemp__8 == 0.0 )
    {
      tTemp__8a = v11 - vX * 0.0;
      tZ = 0.0 * v12 - v11 * 0.0;
      tZ_4 = -(v12 - vX * 0.0);
      tZ_8 = tTemp__8a;
      tTemp_a = v11 * tTemp__8a - v12 * tZ_4;
      tX = tTemp_a;
      tTemp__4a = -(vX * tTemp__8a - v12 * tZ);
      tX_4 = tTemp__4a;
      tTemp__8b = vX * tZ_4 - v11 * tZ;
      tX_8 = tTemp__8b;
    }
    else
    {
      tY = tTemp__4 * vZ - tTemp__8 * vY;
      tZ = tY;
      tY_4 = -(tTemp_ * vZ - tTemp__8 * vX);
      tZ_4 = tY_4;
      tY_8a = tTemp_ * vY - tTemp__4 * vX;
      tZ_8 = tY_8a;
    }
    if ( tZ != 0.0 || tZ_4 != 0.0 || tZ_8 != 0.0 )
    {
      v4 = 1.0 / sqrt(tZ * tZ + tZ_4 * tZ_4 + tZ_8 * tZ_8);
      tZ = tZ * v4;
      tZ_4 = tZ_4 * v4;
      tZ_8 = tZ_8 * v4;
    }
    if ( tX != 0.0 || tX_4 != 0.0 || tX_8 != 0.0 )
    {
      v5 = 1.0 / sqrt(tX * tX + tX_4 * tX_4 + tX_8 * tX_8);
      tX = tX * v5;
      tX_4 = tX_4 * v5;
      tX_8 = tX_8 * v5;
    }
    v6 = v11;
    tY_8 = vZ;
    if ( vX != 0.0 || v6 != 0.0 || v12 != 0.0 )
    {
      v7 = vX;
      v8 = 1.0 / sqrt(vX * vX + v6 * v6 + v12 * v12);
      v9 = v7 * v8;
      v10 = v8;
      vX = v9;
      v6 = v6 * v10;
      tY_8 = v12 * v10;
    }
    ptNode->tOrientation.tX.vY = vX;
    ptNode->tOrientation.tX.vX = tX;
    ptNode->tOrientation.tY.vY = v6;
    ptNode->tOrientation.tY.vX = tX_4;
    ptNode->tOrientation.tZ.vX = tX_8;
    ptNode->tOrientation.tZ.vY = tY_8;
    ptNode->tOrientation.tX.vZ = tZ;
    ptNode->tOrientation.tY.vZ = tZ_4;
    ptNode->tOrientation.tZ.vZ = tZ_8;
  }
}

// source: h/2/splinepath.c:588  [anchor-mhash]
float __cdecl SplinePathNodeQTask_GetEstimatedTPerMeter(struct QTask_s *ptQTask, float vT)
{
  int v2; // eax

  v2 = (__int64)(vT * 10.0);
  if ( v2 >= 0 )
  {
    if ( v2 > 9 )
      v2 = 9;
  }
  else
  {
    v2 = 0;
  }
  return 1.0 / (*((float *)&ptQTask[4].ptPrev + v2) * 10.0);
}

// source: h/2/splinepath.c:624  [size]
void __cdecl SplinePathDynCubeObj_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = SplinePathDynCubeObj_ptParameterList;
}

// source: h/2/splinepath.c:642  [anchor-mhash]
void __cdecl SplinePathDynCubeObj_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  memset(&ptQTask[2].ptParent, 0, 0x190u);
  ptQTask[12].ptParent = nullptr;
  *(_DWORD *)&ptQTask[12].eQTaskType = 0;
  LOBYTE(ptQTask[13].ptNext) = 1;
}

// source: h/2/splinepath.c:685  [size]
void __cdecl SplinePathDynCubeObj_DeleteHandler(struct QTask_s *ptQTask)
{
  ;
}

// source: h/2/splinepath.c:705  [size]
void __cdecl SplinePathDynCubeObj_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ;
}

// source: h/2/splinepath.c:911  [anchor-mhash]
struct QTask_s *__cdecl SplinePathDynCubeObj_ResetPath(struct QTask_s *ptQTask)
{
  struct QTask_s *ptHead; // edx
  struct QTask_s *ptNext; // ecx
  unsigned __int16 v3; // di
  struct QTask_s *ptParent; // esi

  ptHead = ptQTask->tQTaskChildren.ptHead;
  ptQTask[12].ptParent = nullptr;
  ptNext = ptHead->ptNext;
  if ( ptHead->ptNext )
  {
    v3 = SplinePathNodeQTask_eQTaskType;
    do
    {
      if ( ptHead->eQTaskType == v3 )
      {
        ptParent = ptQTask[12].ptParent;
        if ( (int)ptParent < 100 )
        {
          *((_DWORD *)&ptQTask[2].ptParent + (_DWORD)ptParent) = ptHead;
          ++*(int *)&ptQTask[12].ptParent;
        }
      }
      ptHead = ptNext;
      ptNext = ptNext->ptNext;
    }
    while ( ptNext );
  }
  return ptQTask;
}

// source: h/2/splinepath.c:945  [anchor-mhash]
struct SplinePathDynCubeObj_s *__cdecl SplinePathDynCubeObj_RemoveNode(
        struct SplinePathDynCubeObj_s *ptSplinePathDynCubeObj,
        struct SplinePathNodeQTask_s *ptSplinePathNodeQTask)
{
  int nNumNodes; // esi
  int v3; // ecx
  struct SplinePathNodeQTask_s **i; // edx
  int v5; // edx
  struct SplinePathNodeQTask_s **v6; // ecx

  nNumNodes = ptSplinePathDynCubeObj->nNumNodes;
  v3 = 0;
  if ( nNumNodes > 0 )
  {
    for ( i = ptSplinePathDynCubeObj->aptNode; *i != ptSplinePathNodeQTask; ++i )
    {
      if ( ++v3 >= ptSplinePathDynCubeObj->nNumNodes )
        return ptSplinePathDynCubeObj;
    }
    v5 = v3;
    if ( v3 < nNumNodes - 1 )
    {
      v6 = &ptSplinePathDynCubeObj->aptNode[v3];
      do
      {
        *v6 = v6[1];
        ++v5;
        ++v6;
      }
      while ( v5 < ptSplinePathDynCubeObj->nNumNodes - 1 );
    }
    *((_DWORD *)&ptSplinePathDynCubeObj->tDynCubeObj.iRenderGroup + ptSplinePathDynCubeObj->nNumNodes--) = 0;
    SplinePathDynCubeObj_InitPath(&ptSplinePathDynCubeObj->tDynCubeObj.tQObj.tQTask);
  }
  return ptSplinePathDynCubeObj;
}

// source: h/2/splinepath.c:981  [anchor-mhash]
struct real64x3_t *__cdecl SplinePathDynCubeObj_GetInterpolatedPosition(
        struct real64x3_t *retstr,
        struct QTask_s *ptQTask,
        int nSegment,
        float vT,
        int ltcg_eax)
{
  #pragma pack(push, 1)
  union
  {
    struct { float v12; };
    struct { char igi2_o1[4]; float v13; };
    struct { char igi2_o2[8]; struct real64x3_t tP; };
    char igi2_extent[32];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  double v5; // st7
  double *v7; // ecx
  double *v8; // edx
  double v9; // st6
  double v10; // st7
  float retstra = *(float *)&retstr; // [esp+24h] [ebp+4h] ARGSLOT

  v5 = *(float *)&retstr * *(float *)&retstr;
  v7 = *((double **)&ptQTask[2].ptParent + nSegment);
  v8 = *((double **)&ptQTask[2].eQTaskType + nSegment);
  v9 = *(float *)&retstr * v5;
  igi2_frame.v13 = v9 - (v5 + v5) + *(float *)&retstr;
  igi2_frame.v12 = v9 + v9 - v5 * 3.0 + 1.0;
  retstra = v9 - v5;
  v10 = v9 * -2.0 + v5 * 3.0;
  igi2_frame.tP.vX = v10 * v8[5] + retstra * v8[16] + igi2_frame.v12 * v7[5] + igi2_frame.v13 * v7[16];
  igi2_frame.tP.vY = v10 * v8[6] + retstra * v8[17] + igi2_frame.v12 * v7[6] + igi2_frame.v13 * v7[17];
  igi2_frame.tP.vZ = v10 * v8[7] + retstra * v8[18] + igi2_frame.v12 * v7[7] + igi2_frame.v13 * v7[18];
  qmemcpy((void *)ltcg_eax, &igi2_frame.tP, 0x18u);
  return (struct real64x3_t *)ltcg_eax;
}

// source: h/2/splinepath.c:1020  [anchor-mhash]
struct real32x3_t *__cdecl SplinePathDynCubeObj_GetInterpolatedTangent(
        struct real32x3_t *retstr,
        struct QTask_s *ptQTask,
        int nSegment,
        float vT,
        int ltcg_eax)
{
  double *v5; // ecx
  double v6; // st7
  double *v7; // edx
  double v8; // st5
  double v9; // st7
  double v10; // st6
  float v12; // [esp+0h] [ebp-1Ch]
  float v13; // [esp+4h] [ebp-18h]
  float v14; // [esp+8h] [ebp-14h]
  float tT; // [esp+10h] [ebp-Ch]
  float tT_4; // [esp+14h] [ebp-8h]
  float tT_8; // [esp+18h] [ebp-4h]
  float retstra = *(float *)&retstr; // [esp+20h] [ebp+4h] ARGSLOT

  v5 = *((double **)&ptQTask[2].ptParent + nSegment);
  v6 = *(float *)&retstr * *(float *)&retstr;
  v7 = *((double **)&ptQTask[2].eQTaskType + nSegment);
  v14 = 3.0 * v6 - *(float *)&retstr * 4.0 + 1.0;
  v8 = *(float *)&retstr * 6.0;
  v13 = v6 * -6.0 + v8;
  v12 = v6 * 6.0 - v8;
  retstra = 3.0 * v6 - (*(float *)&retstr + *(float *)&retstr);
  tT = v13 * v7[5] + v12 * v5[5] + v7[16] * retstra + v5[16] * v14;
  tT_4 = v13 * v7[6] + v12 * v5[6] + v7[17] * retstra + v5[17] * v14;
  v9 = v13 * v7[7] + v12 * v5[7] + v7[18] * retstra;
  v10 = v5[18];
  *(float *)ltcg_eax = tT;
  *(float *)(ltcg_eax + 4) = tT_4;
  tT_8 = v9 + v10 * v14;
  *(float *)(ltcg_eax + 8) = tT_8;
  return (struct real32x3_t *)ltcg_eax;
}

// source: h/2/splinepath.c:1058  [anchor-mhash]
struct QTask_s *__cdecl SplinePathDynCubeObj_GetInterpolatedOrientation(
        struct QTask_s *ptQTask,
        struct real32x9_t *ptOrientation,
        int nSegment,
        float vT)
{
  #pragma pack(push, 1)
  union
  {
    struct { float v19; };
    struct { char igi2_o1[16]; float vZZ; };
    struct { char igi2_o2[20]; float vXZ; };
    struct { char igi2_o3[24]; float vYW; };
    struct { char igi2_o4[28]; float vYZ; };
    struct { char igi2_o5[32]; float vXW; };
    struct { char igi2_o6[36]; float vYY; };
    struct { char igi2_o7[44]; float tTangent_4; };
    struct { char igi2_o8[48]; float tTangent_8; };
    struct { char igi2_o9[52]; float tX; };
    struct { char igi2_o10[56]; float tX_4; };
    struct { char igi2_o11[64]; float tTemp_; };
    struct { char igi2_o12[64]; float tTemp_a; };
    struct { char igi2_o13[68]; float tTemp__4; };
    struct { char igi2_o14[68]; float tTemp__4a; };
    struct { char igi2_o15[72]; float tTemp__8; };
    struct { char igi2_o16[72]; float tTemp__8a; };
    struct { char igi2_o17[76]; struct Quat32_t tInterpolated; };
    struct { char igi2_o18[96]; struct real32x9_t tOrientation; };
    char igi2_extent[136];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v5; // ebx
  struct QTask_s *result; // eax
  double v7; // st6
  double v8; // st5
  double v9; // st7
  struct real32x3_t *InterpolatedTangent; // eax
  long double vX; // st7
  long double v12; // st6
  long double v13; // st3
  long double v14; // st6
  long double v15; // st2
  long double vZ; // st5
  float v17; // ecx
  float vY; // edx

  v5 = *((_DWORD *)&ptQTask[2].eQTaskType + nSegment);
  Quat32_SLERP(
    &igi2_frame.tInterpolated,
    (struct Quat32_t *)(*((_DWORD *)&ptQTask[2].ptParent + nSegment) + 104),
    (struct Quat32_t *)(v5 + 104),
    vT);
  v7 = igi2_frame.tInterpolated.vY * igi2_frame.tInterpolated.vX + igi2_frame.tInterpolated.vY * igi2_frame.tInterpolated.vX;
  igi2_frame.vXZ = igi2_frame.tInterpolated.vZ * igi2_frame.tInterpolated.vX + igi2_frame.tInterpolated.vZ * igi2_frame.tInterpolated.vX;
  igi2_frame.vXW = igi2_frame.tInterpolated.vW * igi2_frame.tInterpolated.vX + igi2_frame.tInterpolated.vW * igi2_frame.tInterpolated.vX;
  igi2_frame.vYY = igi2_frame.tInterpolated.vY * igi2_frame.tInterpolated.vY + igi2_frame.tInterpolated.vY * igi2_frame.tInterpolated.vY;
  igi2_frame.vYZ = igi2_frame.tInterpolated.vZ * igi2_frame.tInterpolated.vY + igi2_frame.tInterpolated.vZ * igi2_frame.tInterpolated.vY;
  igi2_frame.vYW = igi2_frame.tInterpolated.vW * igi2_frame.tInterpolated.vY + igi2_frame.tInterpolated.vW * igi2_frame.tInterpolated.vY;
  igi2_frame.vZZ = igi2_frame.tInterpolated.vZ * igi2_frame.tInterpolated.vZ + igi2_frame.tInterpolated.vZ * igi2_frame.tInterpolated.vZ;
  v8 = igi2_frame.tInterpolated.vW * igi2_frame.tInterpolated.vZ + igi2_frame.tInterpolated.vW * igi2_frame.tInterpolated.vZ;
  igi2_frame.tOrientation.tX.vX = 1.0 - igi2_frame.vYY - igi2_frame.vZZ;
  igi2_frame.tOrientation.tX.vY = v7 - v8;
  igi2_frame.tOrientation.tX.vZ = igi2_frame.vYW + igi2_frame.vXZ;
  igi2_frame.tOrientation.tY.vX = v8 + v7;
  v9 = 1.0 - (igi2_frame.tInterpolated.vX * igi2_frame.tInterpolated.vX + igi2_frame.tInterpolated.vX * igi2_frame.tInterpolated.vX);
  igi2_frame.tOrientation.tY.vY = v9 - igi2_frame.vZZ;
  igi2_frame.tOrientation.tY.vZ = igi2_frame.vYZ - igi2_frame.vXW;
  igi2_frame.tOrientation.tZ.vX = igi2_frame.vXZ - igi2_frame.vYW;
  igi2_frame.tOrientation.tZ.vY = igi2_frame.vYZ + igi2_frame.vXW;
  igi2_frame.tOrientation.nOps = igi2_frame.tInterpolated.nOps;
  igi2_frame.tOrientation.tZ.vZ = v9 - igi2_frame.vYY;
  if ( v5 == -204 )
  {
    InterpolatedTangent = SplinePathDynCubeObj_GetInterpolatedTangent(
                            (struct real32x3_t *)LODWORD(vT),
                            ptQTask,
                            nSegment,
                            igi2_frame.v19,
                            (int)&igi2_frame.tInterpolated);
    vX = InterpolatedTangent->vX;
    igi2_frame.tTangent_8 = InterpolatedTangent->vZ;
    igi2_frame.tTangent_4 = InterpolatedTangent->vY;
    if ( vX != 0.0 || igi2_frame.tTangent_4 != 0.0 || igi2_frame.tTangent_8 != 0.0 )
    {
      v12 = 1.0 / sqrt(vX * vX + igi2_frame.tTangent_4 * igi2_frame.tTangent_4 + igi2_frame.tTangent_8 * igi2_frame.tTangent_8);
      vX = InterpolatedTangent->vX * v12;
      igi2_frame.tTangent_4 = igi2_frame.tTangent_4 * v12;
      igi2_frame.tTangent_8 = igi2_frame.tTangent_8 * v12;
    }
    igi2_frame.tTemp_ = igi2_frame.tTangent_4 * igi2_frame.tOrientation.tZ.vZ - igi2_frame.tTangent_8 * igi2_frame.tOrientation.tY.vZ;
    igi2_frame.tX = igi2_frame.tTemp_;
    igi2_frame.tTemp__4 = -(igi2_frame.tOrientation.tZ.vZ * vX - igi2_frame.tTangent_8 * igi2_frame.tOrientation.tX.vZ);
    igi2_frame.tX_4 = igi2_frame.tTemp__4;
    igi2_frame.tTemp__8 = igi2_frame.tOrientation.tY.vZ * vX - igi2_frame.tTangent_4 * igi2_frame.tOrientation.tX.vZ;
    if ( igi2_frame.tTemp_ == 0.0 && igi2_frame.tTemp__4 == 0.0 && igi2_frame.tTemp__8 == 0.0 )
    {
      v14 = igi2_frame.tTemp__8;
    }
    else
    {
      v13 = sqrt(igi2_frame.tTemp_ * igi2_frame.tTemp_ + igi2_frame.tTemp__4 * igi2_frame.tTemp__4 + igi2_frame.tTemp__8 * igi2_frame.tTemp__8);
      igi2_frame.tX = igi2_frame.tTemp_ * (1.0 / v13);
      igi2_frame.tX_4 = igi2_frame.tTemp__4 * (1.0 / v13);
      v14 = 1.0 / v13 * igi2_frame.tTemp__8;
    }
    igi2_frame.tTemp_a = igi2_frame.tX_4 * igi2_frame.tTangent_8 - v14 * igi2_frame.tTangent_4;
    igi2_frame.tInterpolated.vX = igi2_frame.tTemp_a;
    igi2_frame.tTemp__4a = -(igi2_frame.tX * igi2_frame.tTangent_8 - v14 * vX);
    igi2_frame.tInterpolated.vY = igi2_frame.tTemp__4a;
    igi2_frame.tTemp__8a = igi2_frame.tX * igi2_frame.tTangent_4 - igi2_frame.tX_4 * vX;
    igi2_frame.tInterpolated.vZ = igi2_frame.tTemp__8a;
    if ( igi2_frame.tTemp_a == 0.0 && igi2_frame.tTemp__4a == 0.0 && igi2_frame.tTemp__8a == 0.0 )
    {
      vZ = igi2_frame.tInterpolated.vZ;
    }
    else
    {
      v15 = sqrt(igi2_frame.tTemp_a * igi2_frame.tTemp_a + igi2_frame.tTemp__4a * igi2_frame.tTemp__4a + igi2_frame.tTemp__8a * igi2_frame.tTemp__8a);
      igi2_frame.tInterpolated.vX = igi2_frame.tTemp_a * (1.0 / v15);
      igi2_frame.tInterpolated.vY = igi2_frame.tInterpolated.vY * (1.0 / v15);
      vZ = 1.0 / v15 * igi2_frame.tInterpolated.vZ;
    }
    ptOrientation->tZ.vX = v14;
    ptOrientation->tX.vY = vX;
    ptOrientation->tX.vX = igi2_frame.tX;
    ptOrientation->tZ.vZ = vZ;
    ptOrientation->tY.vX = igi2_frame.tX_4;
    ptOrientation->tY.vY = igi2_frame.tTangent_4;
    v17 = igi2_frame.tInterpolated.vX;
    ptOrientation->tZ.vY = igi2_frame.tTangent_8;
    vY = igi2_frame.tInterpolated.vY;
    ptOrientation->tX.vZ = v17;
    ptOrientation->tY.vZ = vY;
    return (struct QTask_s *)ptOrientation;
  }
  else
  {
    qmemcpy(ptOrientation, &igi2_frame.tOrientation, sizeof(struct real32x9_t));
  }
  return result;
}

// source: h/2/splinepath.c:1117  [anchor-mhash]
void __cdecl SplinePathDynCubeObj_InitPath(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { float v16; };
    struct { char igi2_o1[16]; float vT; };
    struct { char igi2_o2[16]; float vTa; };
    struct { char igi2_o3[20]; struct QTask_s **v19; };
    struct { char igi2_o4[24]; int nJ; };
    struct { char igi2_o5[24]; int nJa; };
    struct { char igi2_o6[28]; int nI; };
    struct { char igi2_o7[32]; int v23; };
    struct { char igi2_o8[36]; char *v24; };
    struct { char igi2_o9[48]; struct real64x3_t atPos[2]; };
    struct { char igi2_o10[96]; int v26[6]; };
    struct { char igi2_o11[120]; int v27[6]; };
    struct { char igi2_o12[144]; int ltcg_eax[6]; };
    char igi2_extent[168];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *v1; // eax
  struct QTask_s *ptParent; // esi
  struct QTask_s *v3; // ecx
  int v4; // ecx
  int v5; // edi
  unsigned __int16 *p_eQTaskType; // ecx
  int v7; // ebx
  struct QTask_s **p_ptParent; // ecx
  struct QTask_s *v9; // edx
  struct QTask_s **v10; // ecx
  struct QTask_s *v11; // esi
  double v12; // st7
  struct real64x3_t *InterpolatedPosition; // eax
  int i; // ebx
  bool v15; // cc

  v1 = ptQTask;
  ptParent = ptQTask[12].ptParent;
  if ( (int)ptParent >= 3 )
  {
    v3 = ptQTask[2].ptParent;
    if ( BYTE1(v3[5].ptPrev) )
    {
      *(double *)&v3[3].tQTaskChildren.ptHead = *(double *)(*(_DWORD *)&ptQTask[2].eQTaskType + 40)
                                              - *(double *)&v3[1].ptNext;
      *(double *)&ptQTask[2].ptParent[3].tQTaskChildren.ptTail = *(double *)(*(_DWORD *)&ptQTask[2].eQTaskType + 48)
                                                               - *(double *)&ptQTask[2].ptParent[1].tQTaskChildren.ptHead;
      *(double *)&ptQTask[2].ptParent[3].tQTaskRefList.ptMiddle = *(double *)(*(_DWORD *)&ptQTask[2].eQTaskType + 56)
                                                                - *(double *)&ptQTask[2].ptParent[1].tQTaskChildren.ptTail;
    }
    v4 = *((_DWORD *)&ptQTask[2].tQTaskRefList.ptTail + (_DWORD)ptParent);
    if ( *(_BYTE *)(v4 + 205) )
    {
      *(double *)(v4 + 128) = *(double *)(v4 + 40)
                            - *(double *)(*((_DWORD *)&ptQTask[2].tQTaskRefList.ptMiddle + (_DWORD)ptParent) + 40);
      *(double *)(*((_DWORD *)&ptQTask[2].tQTaskRefList.ptTail + (_DWORD)ptParent) + 136) = *(double *)(*((_DWORD *)&ptQTask[2].tQTaskRefList.ptTail + (_DWORD)ptParent) + 48)
                                                                                          - *(double *)(*((_DWORD *)&ptQTask[2].tQTaskRefList.ptMiddle + (_DWORD)ptParent) + 48);
      *(double *)(*((_DWORD *)&ptQTask[2].tQTaskRefList.ptTail + (_DWORD)ptParent) + 144) = *(double *)(*((_DWORD *)&ptQTask[2].tQTaskRefList.ptTail + (_DWORD)ptParent) + 56)
                                                                                          - *(double *)(*((_DWORD *)&ptQTask[2].tQTaskRefList.ptMiddle + (_DWORD)ptParent) + 56);
    }
    v5 = (int)(&ptParent[-1].isInMemPool + 1);
    igi2_frame.v24 = &ptParent[-1].isInMemPool + 1;
    p_eQTaskType = &ptQTask[2].eQTaskType;
    igi2_frame.nJ = (int)&ptParent[-1].isInMemPool;
    do
    {
      if ( *(_BYTE *)(*(_DWORD *)p_eQTaskType + 205) )
      {
        *(double *)(*(_DWORD *)p_eQTaskType + 128) = *(double *)(*((_DWORD *)p_eQTaskType + 1) + 40)
                                                   - *(double *)(*((_DWORD *)p_eQTaskType - 1) + 40);
        *(double *)(*(_DWORD *)p_eQTaskType + 136) = *(double *)(*((_DWORD *)p_eQTaskType + 1) + 48)
                                                   - *(double *)(*((_DWORD *)p_eQTaskType - 1) + 48);
        v5 = (int)(&ptParent[-1].isInMemPool + 1);
        *(double *)(*(_DWORD *)p_eQTaskType + 144) = *(double *)(*((_DWORD *)p_eQTaskType + 1) + 56)
                                                   - *(double *)(*((_DWORD *)p_eQTaskType - 1) + 56);
        *(double *)(*(_DWORD *)p_eQTaskType + 128) = *(double *)(*(_DWORD *)p_eQTaskType + 128) * 0.5;
        *(double *)(*(_DWORD *)p_eQTaskType + 136) = *(double *)(*(_DWORD *)p_eQTaskType + 136) * 0.5;
        *(double *)(*(_DWORD *)p_eQTaskType + 144) = *(double *)(*(_DWORD *)p_eQTaskType + 144) * 0.5;
      }
      p_eQTaskType += 2;
      --igi2_frame.nJ;
    }
    while ( igi2_frame.nJ );
    v7 = 0;
    *(_DWORD *)(*((_DWORD *)&ptQTask[2].tQTaskRefList.ptTail + (_DWORD)ptParent) + 160) = 0;
    p_ptParent = &ptQTask[2].ptParent;
    *(_DWORD *)&ptQTask[2].ptParent[3].eQTaskType = 0;
    igi2_frame.nI = 0;
    if ( v5 > 0 )
    {
      igi2_frame.v19 = &ptQTask[2].ptParent;
      while ( 1 )
      {
        (*p_ptParent)[4].ptNext = nullptr;
        v9 = *p_ptParent + 1;
        qmemcpy(igi2_frame.atPos, v9, 0x18u);
        igi2_frame.vT = 0.0;
        qmemcpy(&igi2_frame.atPos[1], v9, sizeof(struct real64x3_t));
        while ( 1 )
        {
          igi2_frame.vT = igi2_frame.vT + 0.009999999776482582;
          qmemcpy(
            &igi2_frame.atPos[v7++ & 1],
            SplinePathDynCubeObj_GetInterpolatedPosition((struct real64x3_t *)LODWORD(igi2_frame.vT), v1, igi2_frame.nI, igi2_frame.v16, (int)igi2_frame.ltcg_eax),
            sizeof(struct real64x3_t));
          *(float *)&(*igi2_frame.v19)[4].ptNext = sqrt(
                                          (igi2_frame.atPos[0].vX - igi2_frame.atPos[1].vX) * (igi2_frame.atPos[0].vX - igi2_frame.atPos[1].vX)
                                        + (igi2_frame.atPos[0].vY - igi2_frame.atPos[1].vY) * (igi2_frame.atPos[0].vY - igi2_frame.atPos[1].vY)
                                        + (igi2_frame.atPos[0].vZ - igi2_frame.atPos[1].vZ) * (igi2_frame.atPos[0].vZ - igi2_frame.atPos[1].vZ))
                                      + *(float *)&(*igi2_frame.v19)[4].ptNext;
          if ( v7 >= 100 )
            break;
          v1 = ptQTask;
        }
        v10 = igi2_frame.v19;
        v11 = igi2_frame.v19[1];
        v12 = *(float *)&(*igi2_frame.v19)[3].ptParent * 0.2777777910232544 + *(float *)&v11[3].ptParent * 0.2777777910232544;
        if ( v12 <= 0.0 )
          *(_DWORD *)&v11[3].eQTaskType = 0;
        else
          *(float *)&v11[3].eQTaskType = *(float *)&(*igi2_frame.v19)[4].ptNext * 0.00048828125 / v12
                                       + *(float *)&(*igi2_frame.v19)[3].eQTaskType;
        igi2_frame.nJa = 0;
        igi2_frame.v23 = 164;
        while ( 1 )
        {
          *(struct QTask_s **)((char *)&(*v10)->ptNext + igi2_frame.v23) = nullptr;
          igi2_frame.vTa = (double)igi2_frame.nJa * 0.10000000149011612;
          InterpolatedPosition = SplinePathDynCubeObj_GetInterpolatedPosition(
                                   (struct real64x3_t *)LODWORD(igi2_frame.vTa),
                                   ptQTask,
                                   igi2_frame.nI,
                                   igi2_frame.v16,
                                   (int)igi2_frame.v26);
          qmemcpy(igi2_frame.atPos, InterpolatedPosition, 0x18u);
          qmemcpy(&igi2_frame.atPos[1], InterpolatedPosition, sizeof(struct real64x3_t));
          for ( i = 0; i < 20; ++i )
          {
            igi2_frame.vTa = igi2_frame.vTa + 0.004999999888241291;
            qmemcpy(
              &igi2_frame.atPos[i & 1],
              SplinePathDynCubeObj_GetInterpolatedPosition(
                (struct real64x3_t *)LODWORD(igi2_frame.vTa),
                ptQTask,
                igi2_frame.nI,
                igi2_frame.v16,
                (int)igi2_frame.v27),
              sizeof(struct real64x3_t));
            *(float *)((char *)&(*igi2_frame.v19)->ptNext + igi2_frame.v23) = sqrt(
                                                          (igi2_frame.atPos[0].vX - igi2_frame.atPos[1].vX) * (igi2_frame.atPos[0].vX - igi2_frame.atPos[1].vX)
                                                        + (igi2_frame.atPos[0].vY - igi2_frame.atPos[1].vY) * (igi2_frame.atPos[0].vY - igi2_frame.atPos[1].vY)
                                                        + (igi2_frame.atPos[0].vZ - igi2_frame.atPos[1].vZ) * (igi2_frame.atPos[0].vZ - igi2_frame.atPos[1].vZ))
                                                      + *(float *)((char *)&(*igi2_frame.v19)->ptNext + igi2_frame.v23);
          }
          v15 = igi2_frame.v23 + 4 < 204;
          ++igi2_frame.nJa;
          igi2_frame.v23 += 4;
          if ( !v15 )
            break;
          v10 = igi2_frame.v19;
        }
        v15 = ++igi2_frame.nI < (int)igi2_frame.v24;
        ++igi2_frame.v19;
        if ( !v15 )
          break;
        p_ptParent = igi2_frame.v19;
        v1 = ptQTask;
        v7 = 0;
      }
    }
  }
}

// source: h/2/splinepath.c:1251  [anchor-mhash]
void __cdecl SplinePathDynCubeObj_UpdateOrientations(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { int nI; };
    struct { char igi2_o1[4]; struct SplinePathNodeQTask_s **v18; };
    struct { char igi2_o2[8]; int aiNext[3]; };
    char igi2_extent[20];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *v1; // edi
  struct SplinePathNodeQTask_s **p_ptParent; // esi
  struct SplinePathNodeQTask_s *v3; // ecx
  double v4; // st7
  long double v5; // st7
  long double v6; // st7
  double vY; // st7
  bool v8; // c0
  bool v9; // c3
  int v10; // edx
  int v11; // edi
  int v12; // esi
  double v13; // st7
  int v14; // eax
  int v15; // ebx
  bool v16; // cc

  v1 = ptQTask;
  igi2_frame.nI = 0;
  if ( (int)ptQTask[12].ptParent > 0 )
  {
    p_ptParent = (struct SplinePathNodeQTask_s **)&ptQTask[2].ptParent;
    igi2_frame.v18 = (struct SplinePathNodeQTask_s **)&ptQTask[2].ptParent;
    do
    {
      SplinePathNodeQTask_LimitOrientation(*p_ptParent);
      v3 = *p_ptParent;
      v4 = (*p_ptParent)->tOrientation.tZ.vZ + (*p_ptParent)->tOrientation.tY.vY + (*p_ptParent)->tOrientation.tX.vX;
      if ( v4 <= 0.0 )
      {
        vY = v3->tOrientation.tY.vY;
        igi2_frame.aiNext[0] = 1;
        v8 = vY < v3->tOrientation.tX.vX;
        v9 = vY == v3->tOrientation.tX.vX;
        igi2_frame.aiNext[1] = 2;
        igi2_frame.aiNext[2] = 0;
        v10 = !v8 && !v9;
        if ( v3->tOrientation.tZ.vZ > (double)*(&v3->tOrientation.tX.vX + 4 * v10) )
          v10 = 2;
        v11 = igi2_frame.aiNext[v10];
        v12 = igi2_frame.aiNext[v11];
        v13 = sqrt(
                *(&v3->tOrientation.tX.vX + 4 * v10)
              - *(&v3->tOrientation.tX.vX + 4 * v11)
              - *(&v3->tOrientation.tX.vX + 4 * v12)
              + 1.0);
        *(&v3->tQuatOrientation.vX + v10) = 0.5 * v13;
        if ( v13 != 0.0 )
          v13 = 0.5 / v13;
        *(&v3->tQuatOrientation.vX + v11) = (*(&v3->tOrientation.tX.vX + 3 * v11 + v10)
                                           + *(&v3->tOrientation.tX.vX + 3 * v10 + v11))
                                          * v13;
        v14 = v12 + 3 * v11;
        v15 = v11 + 3 * v12;
        v1 = ptQTask;
        *(&v3->tQuatOrientation.vX + v12) = (*(&v3->tOrientation.tX.vX + 3 * v12 + v10)
                                           + *(&v3->tOrientation.tX.vX + 3 * v10 + v12))
                                          * v13;
        p_ptParent = igi2_frame.v18;
        v3->tQuatOrientation.vW = -((*(&v3->tOrientation.tX.vX + v14) - *(&v3->tOrientation.tX.vX + v15)) * v13);
      }
      else
      {
        v5 = sqrt(v4 + 1.0);
        v3->tQuatOrientation.vW = 0.5 * v5;
        v6 = 0.5 / v5;
        (*p_ptParent)->tQuatOrientation.vX = -(((*p_ptParent)->tOrientation.tY.vZ - (*p_ptParent)->tOrientation.tZ.vY)
                                             * v6);
        (*p_ptParent)->tQuatOrientation.vY = -(((*p_ptParent)->tOrientation.tZ.vX - (*p_ptParent)->tOrientation.tX.vZ)
                                             * v6);
        (*p_ptParent)->tQuatOrientation.vZ = -(((*p_ptParent)->tOrientation.tX.vY - (*p_ptParent)->tOrientation.tY.vX)
                                             * v6);
      }
      (*p_ptParent)->tQuatOrientation.nOps = (*p_ptParent)->tOrientation.nOps;
      ++p_ptParent;
      v16 = ++igi2_frame.nI < (int)v1[12].ptParent;
      igi2_frame.v18 = p_ptParent;
    }
    while ( v16 );
  }
}

// source: h/2/splinepath.c:1281  [size]
int __cdecl SplinePathDynCubeObj_GetNodeCount(struct QTask_s *ptQTask)
{
  return (int)ptQTask[12].ptParent;
}

// source: h/2/splinepath.c:1299  [size]
struct QTask_s *__cdecl SplinePathDynCubeObj_GetNode(
        struct QTask_s *ptQTask,
        int iNode)
{
  return *(&ptQTask[2].ptParent + iNode);
}

// source: h/2/splinepath.c:1319  [size]
unsigned __int16 __cdecl SplinePathDynCubeObj_GetQTaskType()
{
  return SplinePathDynCubeObj_eQTaskType;
}

// source: h/2/splinepath.c:1332  [anchor-hash]
void __cdecl SplinePathDynCubeObj_Open()
{
  unsigned __int16 BaseQTaskType; // ax
  unsigned __int16 v1; // si
  struct ParameterList_s *v2; // eax
  int v3; // edx

  BaseQTaskType = QTask_GetBaseQTaskType();
  v1 = QTask_NewQTaskType("SplinePathDynCubeObj", 528, BaseQTaskType, 0, 0);
  SplinePathDynCubeObj_eQTaskType = v1;
  QTask_LinkQTaskEventHandlerFn(
    v1,
    ParameterList_eUpdateInternalDataQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))SplinePathDynCubeObj_UpdateInternalDataHandler);
  QTask_LinkQTaskEventHandlerFn(v1, 0, SplinePathDynCubeObj_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 2, (void (__cdecl *)(struct QTask_s *))SplinePathDynCubeObj_DeleteHandler);
  QTask_LinkQTaskEventHandlerFn(
    v1,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))SplinePathDynCubeObj_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(
    v1,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveHandler);
  v2 = (struct ParameterList_s *)Mem_AllocFn(32, 4);
  v3 = Level_eParameterTypebool8;
  v2->ptParameterListItem = (struct ParameterListItem_s *)&v2[1];
  v2->nParameters = 0;
  v2->nMaxParameters = 1;
  SplinePathDynCubeObj_ptParameterList = v2;
  ParameterList_AddParameter(v2, 0x208u, v3, "Show in editor", 7u, nullptr);
  SplinePathNodeQTask_Open();
}

// source: h/2/splinepath.c:1370  [anchor-hash]
void __cdecl SplinePathDynCubeObj_Close()
{
  int v0; // esi

  SplinePathNodeQTask_Close();
  QTask_DeleteQTaskType(SplinePathDynCubeObj_eQTaskType);
  SplinePathDynCubeObj_eQTaskType = 512;
  if ( SplinePathDynCubeObj_ptParameterList )
  {
    v0 = *(_DWORD *)((unsigned int)&SplinePathDynCubeObj_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
}
