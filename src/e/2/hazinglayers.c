/* e/2/hazinglayers.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: e/2/hazinglayers.c:61  [anchor-mhash]
struct HazingDynCubeObj_t *__cdecl Hazinglayers_New(
        struct real64x3_t *ptMin,
        struct real64x3_t *ptMax,
        struct real32x3_t *ptColor,
        float vDensity,
        double vMinZ,
        double vMaxZ)
{
  struct QTask_s *v6; // esi
  struct World_s *v7; // edx
  struct real64x3_t tPos; // [esp+10h] [ebp-18h] BYREF

  v6 = QTask_NewFn(nullptr, Hazinglayers_eQTaskType, nullptr);
  *(float *)&v6[2].eQTaskType = vDensity;
  if ( ptColor )
  {
    *(struct real32x3_t *)&v6[3].tQTaskChildren.ptTail = *ptColor;
  }
  else
  {
    v6[3].tQTaskChildren.ptTail = nullptr;
    v6[3].tQTaskRefList.ptHead = nullptr;
    v6[3].tQTaskRefList.ptMiddle = nullptr;
  }
  v6[3].ptNext = (struct QTask_s *)LODWORD(vMinZ);
  *(_QWORD *)&v6[3].ptPrev = __PAIR64__(LODWORD(vMaxZ), HIDWORD(vMinZ));
  v7 = World_ptActiveWorld;
  v6[3].tQTaskChildren.ptMiddle = (struct QTask_s *)HIDWORD(vMaxZ);
  v6[2].ptParent = (struct QTask_s *)v7;
  v6[3].tQTaskRefList.ptTail = nullptr;
  tPos.vX = (ptMax->vX - ptMin->vX) * 0.5 + ptMin->vX;
  tPos.vY = (ptMax->vY - ptMin->vY) * 0.5 + ptMin->vY;
  tPos.vZ = (ptMax->vZ - ptMin->vZ) * 0.5 + ptMin->vZ;
  World_RegisterDynCubeObjFirstTimeMinMaxXYZ(
    v7,
    (struct DynCubeObj_s *)v6,
    &tPos,
    ptMin,
    ptMax,
    WORLD_DYNCUBETREE_CATEGORY_TERRAINMODIFIERS);
  return (struct HazingDynCubeObj_t *)v6;
}

// source: e/2/hazinglayers.c:107  [anchor-mhash]
void __cdecl Hazinglayers_Update(
        struct HazingDynCubeObj_t *ptObj,
        struct real64x3_t *ptMin,
        struct real64x3_t *ptMax,
        struct real32x3_t *ptColor,
        float vDensity,
        double vMinZ,
        double vMaxZ)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct World_s *ptWorld; };
    struct { char igi2_o1[28]; struct real64x3_t tPos; };
    char igi2_extent[56];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)

  ptObj->vDensity = vDensity;
  if ( ptColor )
  {
    ptObj->tColor = *ptColor;
  }
  else
  {
    ptObj->tColor.vX = 0.0;
    ptObj->tColor.vY = 0.0;
    ptObj->tColor.vZ = 0.0;
  }
  ptObj->vMinZ = vMinZ;
  ptObj->vMaxZ = vMaxZ;
  igi2_frame.tPos.vX = (ptMax->vX - ptMin->vX) * 0.5 + ptMin->vX;
  igi2_frame.tPos.vY = (ptMax->vY - ptMin->vY) * 0.5 + ptMin->vY;
  igi2_frame.ptWorld = ptObj->ptWorld;
  igi2_frame.tPos.vZ = (ptMax->vZ - ptMin->vZ) * 0.5 + ptMin->vZ;
  World_MoveDynCubeObjMinMaxXYZ(igi2_frame.ptWorld, &ptObj->tDynCubeObj, &igi2_frame.tPos, ptMin, ptMax);
}

// source: e/2/hazinglayers.c:143  [anchor-hash]
void __cdecl Hazinglayers_Delete(struct HazingDynCubeObj_t *ptObj)
{
  World_RemoveDynCubeObj(ptObj->ptWorld, &ptObj->tDynCubeObj);
  QTask_Delete(&ptObj->tDynCubeObj.tQObj.tQTask);
}

// source: e/2/hazinglayers.c:159  [size]
void __cdecl Hazinglayers_EnterCameraCubeHandler(struct QTask_s *ptQTask, void *pxData)
{
  int v2; // ecx

  v2 = Hazinglayers_iHazingStack;
  Hazinglayers_aptHazingStack[Hazinglayers_iHazingStack] = (struct HazingDynCubeObj_t *)ptQTask;
  Hazinglayers_iHazingStack = v2 + 1;
  ptQTask[3].tQTaskRefList.ptTail = (struct QReference_s *)1;
}

// source: e/2/hazinglayers.c:184  [anchor-mhash]
void __cdecl Hazinglayers_EnterHandler(struct QTask_s *ptQTask, void *pxData)
{
  int v2; // eax

  if ( !ptQTask[3].tQTaskRefList.ptTail )
  {
    v2 = Hazinglayers_iHazingStack;
    Hazinglayers_aptHazingStack[Hazinglayers_iHazingStack] = (struct HazingDynCubeObj_t *)ptQTask;
    Hazinglayers_iHazingStack = v2 + 1;
  }
}

// source: e/2/hazinglayers.c:209  [size]
void __cdecl Hazinglayers_LeaveCameraCubeHandler(struct QTask_s *ptQTask, void *pxData)
{
  --Hazinglayers_iHazingStack;
  ptQTask[3].tQTaskRefList.ptTail = nullptr;
}

// source: e/2/hazinglayers.c:233  [size]
void __cdecl Hazinglayers_LeaveHandler(struct QTask_s *ptQTask, void *pxContext)
{
  if ( !ptQTask[3].tQTaskRefList.ptTail )
    --Hazinglayers_iHazingStack;
}

// source: e/2/hazinglayers.c:257  [anchor-mhash]
struct HazingDynCubeObj_t ***__cdecl Hazinglayers_CreateHazingList(
        struct HazingDynCubeObj_t ***ppptHazingList,
        int *pnNumHazingBox)
{
  int v2; // edx
  struct HazingDynCubeObj_t **v3; // edi
  struct HazingDynCubeObj_t ***result; // eax

  v2 = Hazinglayers_iHazingBuffer;
  v3 = (struct HazingDynCubeObj_t **)(4 * Hazinglayers_iHazingBuffer + 129834072);
  *ppptHazingList = v3;
  result = (struct HazingDynCubeObj_t ***)Hazinglayers_iHazingStack;
  qmemcpy(v3, Hazinglayers_aptHazingStack, 4 * Hazinglayers_iHazingStack);
  *pnNumHazingBox = (int)result;
  Hazinglayers_iHazingBuffer = (int)result + v2;
  return result;
}

// source: e/2/hazinglayers.c:281  [anchor-hash]
void __cdecl Hazinglayers_Open()
{
  unsigned __int16 v0; // si

  v0 = QTask_NewQTaskType("Hazinglayers", 152, ShadowVolume_nShadow, 0, 0);
  Hazinglayers_eQTaskType = v0;
  QTask_LinkQTaskEventHandlerFn(v0, 17, (void (__cdecl *)(struct QTask_s *, void *))Hazinglayers_EnterCameraCubeHandler);
  QTask_LinkQTaskEventHandlerFn(v0, 18, (void (__cdecl *)(struct QTask_s *, void *))Hazinglayers_LeaveCameraCubeHandler);
  QTask_LinkQTaskEventHandlerFn(v0, 5, (void (__cdecl *)(struct QTask_s *, void *))Hazinglayers_EnterHandler);
  QTask_LinkQTaskEventHandlerFn(v0, 6, (void (__cdecl *)(struct QTask_s *, void *))Hazinglayers_LeaveHandler);
}

// source: e/2/hazinglayers.c:299  [size]
void __cdecl Hazinglayers_Close()
{
  QTask_DeleteQTaskType(Hazinglayers_eQTaskType);
}

// source: e/2/hazinglayers.c:316  [size]
void __cdecl Hazinglayers_ResetList()
{
  Hazinglayers_iHazingBuffer = 0;
}

// source: e/2/hazinglayers.c:331  [anchor-strings]
void __cdecl Hazinglayers_TraceLine(
        struct real32x3_t *ptFogColor,
        float *pvFogIntensity,
        struct real64x3_t *ptStart,
        struct real64x3_t *ptStop,
        struct HazingDynCubeObj_t **pptHazingList,
        int nNumHazingBox)
{
  #pragma pack(push, 1)
  union
  {
    struct { float vFogColorLen; };
    struct { char igi2_o1[4]; float vT; };
    struct { char igi2_o2[8]; float vLen; };
    struct { char igi2_o3[8]; float vLena; };
    struct { char igi2_o4[8]; float vLenb; };
    struct { char igi2_o5[12]; int iCount; };
    struct { char igi2_o6[16]; double v47; };
    struct { char igi2_o7[16]; double v48; };
    struct { char igi2_o8[16]; double v49; };
    struct { char igi2_o9[28]; struct real32x3_t tDelta; };
    char igi2_extent[40];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct real64x3_t *v6; // ecx
  double v7; // st7
  struct HazingDynCubeObj_t *v8; // esi
  double v9; // st7
  double v10; // st7
  double v11; // st6
  double v12; // st7
  double v13; // st7
  double v14; // st7
  double v15; // st7
  char v16; // fps^1
  double v17; // st7
  bool v18; // c0
  char v19; // c2
  bool v20; // c3
  char v21; // ah
  double v22; // st7
  bool v23; // c0
  bool v24; // c3
  double v25; // st7
  double v26; // st7
  double v27; // st7
  double v28; // st6
  double vMaxZ; // st7
  char v30; // fps^1
  double v31; // st7
  bool v32; // c0
  char v33; // c2
  bool v34; // c3
  char v35; // ah
  double vZ; // st7
  bool v37; // c0
  bool v38; // c3
  double v39; // st7
  double vMinZ; // st7

  v6 = ptStart;
  igi2_frame.tDelta.vX = ptStop->vX - ptStart->vX;
  igi2_frame.tDelta.vY = ptStop->vY - ptStart->vY;
  igi2_frame.iCount = 0;
  v7 = ptStop->vZ - ptStart->vZ;
  ptFogColor->vX = 0.0;
  ptFogColor->vY = 0.0;
  igi2_frame.tDelta.vZ = v7;
  ptFogColor->vZ = 0.0;
  *pvFogIntensity = 0.0;
  if ( nNumHazingBox > 0 )
  {
    while ( 1 )
    {
      v8 = pptHazingList[igi2_frame.iCount];
      igi2_frame.vT = 1.0;
      igi2_frame.v47 = v8->vMaxZ - v8->vMinZ;
      igi2_frame.vLen = 1.0 / (igi2_frame.v47 * 0.30000001192092896);
      if ( igi2_frame.tDelta.vZ > 0.0 && ptStop->vZ > v8->vMaxZ )
      {
        igi2_frame.vT = (v8->vMaxZ - v6->vZ) * igi2_frame.vLen;
        if ( igi2_frame.vT >= 0.0 )
        {
          if ( igi2_frame.vT > 1.0 )
            igi2_frame.vT = 1.0;
        }
        else
        {
          igi2_frame.vT = 0.0;
        }
      }
      if ( igi2_frame.tDelta.vZ < 0.0 && ptStop->vZ < v8->vMinZ )
      {
        igi2_frame.vT = (v6->vZ - v8->vMinZ) * igi2_frame.vLen;
        if ( igi2_frame.vT >= 0.0 )
        {
          if ( igi2_frame.vT > 1.0 )
            igi2_frame.vT = 1.0;
        }
        else
        {
          igi2_frame.vT = 0.0;
        }
      }
      v9 = Real32x3_FastLen(&igi2_frame.tDelta);
      igi2_frame.vLena = v9;
      if ( v9 > 0.0
        && (ptStart->vZ > v8->vMinZ || ptStop->vZ > v8->vMinZ)
        && (ptStart->vZ < v8->vMaxZ || ptStop->vZ < v8->vMaxZ) )
      {
        if ( (ptStart->vZ > v8->vMinZ || ptStop->vZ < v8->vMaxZ) && (ptStart->vZ < v8->vMaxZ || ptStop->vZ > v8->vMinZ) )
        {
          if ( ptStart->vZ <= v8->vMinZ
            || ptStop->vZ >= v8->vMaxZ
            || ptStart->vZ >= v8->vMaxZ
            || ptStop->vZ <= v8->vMinZ )
          {
            if ( ptStart->vZ <= v8->vMinZ
              || ptStart->vZ >= v8->vMaxZ
              || ptStop->vZ > v8->vMinZ && ptStop->vZ < v8->vMaxZ )
            {
              if ( ptStop->vZ <= v8->vMinZ
                || ptStop->vZ >= v8->vMaxZ
                || ptStart->vZ > v8->vMinZ && ptStart->vZ < v8->vMaxZ )
              {
                LDebug_Error("Fog layer logic error");
                abort();
              }
              if ( ptStart->vZ > v8->vMinZ )
                vMaxZ = v8->vMaxZ;
              else
                vMaxZ = v8->vMinZ;
              v31 = vMaxZ - ptStop->vZ;
              v32 = v31 < 0.0;
              v33 = 0;
              v34 = v31 == 0.0;
              v16 = (char)(v32 | (v33 << 2) | (v34 << 6));
              v35 = v30;
              vZ = ptStart->vZ;
              v37 = vZ < v8->vMinZ;
              v38 = vZ == v8->vMinZ;
              v16 = (char)(v37 | (0 << 2) | (v38 << 6));
              if ( __SETP__(v35 & 5, 0) )
              {
                if ( v37 || v38 )
                  vMinZ = v8->vMinZ;
                else
                  vMinZ = v8->vMaxZ;
                v39 = vMinZ - ptStop->vZ;
              }
              else if ( v37 || v38 )
              {
                v39 = -(v8->vMinZ - ptStop->vZ);
              }
              else
              {
                v39 = -(v8->vMaxZ - ptStop->vZ);
              }
              igi2_frame.v49 = v39;
              v27 = igi2_frame.tDelta.vZ;
              if ( igi2_frame.tDelta.vZ < 0.0 )
                v27 = -v27;
              v28 = igi2_frame.vLena * igi2_frame.v49;
            }
            else
            {
              if ( ptStop->vZ > v8->vMinZ )
                v15 = v8->vMaxZ;
              else
                v15 = v8->vMinZ;
              v17 = v15 - ptStart->vZ;
              v18 = v17 < 0.0;
                v16 = (char)(v18 | (0 << 2) | (0 << 6));
              v19 = 0;
              v20 = v17 == 0.0;
              v16 = (char)(0 | (v19 << 2) | (v20 << 6));
              v21 = v16;
              v22 = ptStop->vZ;
              v23 = v22 < v8->vMinZ;
              v24 = v22 == v8->vMinZ;
              v16 = (char)(v23 | (0 << 2) | (v24 << 6));
              if ( __SETP__(v21 & 5, 0) )
              {
                if ( v23 || v24 )
                  v26 = v8->vMinZ;
                else
                  v26 = v8->vMaxZ;
                v25 = v26 - ptStart->vZ;
              }
              else if ( v23 || v24 )
              {
                v25 = -(v8->vMinZ - ptStart->vZ);
              }
              else
              {
                v25 = -(v8->vMaxZ - ptStart->vZ);
              }
              igi2_frame.v48 = v25;
              v27 = igi2_frame.tDelta.vZ;
              if ( igi2_frame.tDelta.vZ < 0.0 )
                v27 = -v27;
              v28 = igi2_frame.vLena * igi2_frame.v48;
            }
            igi2_frame.vLenb = v28 / v27 * v8->vDensity;
            v14 = igi2_frame.vLenb;
          }
          else
          {
            v14 = igi2_frame.vLena * v8->vDensity;
            igi2_frame.vLenb = v14;
          }
          *pvFogIntensity = v14 * igi2_frame.vT + *pvFogIntensity;
          if ( igi2_frame.vLenb != 0.0 )
          {
            v13 = igi2_frame.vLenb + igi2_frame.vFogColorLen;
            goto LABEL_75;
          }
        }
        else
        {
          v10 = igi2_frame.v47;
          if ( igi2_frame.v47 < 0.0 )
            v10 = -igi2_frame.v47;
          v11 = igi2_frame.tDelta.vZ;
          if ( igi2_frame.tDelta.vZ < 0.0 )
            v11 = -v11;
          v12 = v10 * igi2_frame.vLena / v11 * v8->vDensity;
          igi2_frame.vLenb = v12;
          *pvFogIntensity = v12 * igi2_frame.vT + *pvFogIntensity;
          if ( igi2_frame.vLenb != 0.0 )
          {
            v13 = igi2_frame.vFogColorLen + igi2_frame.vLenb;
LABEL_75:
            ptFogColor->vX = (igi2_frame.vLenb * v8->tColor.vX + igi2_frame.vFogColorLen * ptFogColor->vX) * (1.0 / v13);
            ptFogColor->vY = (igi2_frame.vLenb * v8->tColor.vY + igi2_frame.vFogColorLen * ptFogColor->vY) * (1.0 / v13);
            ptFogColor->vZ = (igi2_frame.vLenb * v8->tColor.vZ + igi2_frame.vFogColorLen * ptFogColor->vZ) * (1.0 / v13);
            igi2_frame.vFogColorLen = v13;
          }
        }
      }
      if ( ++igi2_frame.iCount >= nNumHazingBox )
        return;
      v6 = ptStart;
    }
  }
}

// source: e/2/hazinglayers.c:462  [anchor-caller]
void __cdecl World_GetFogValue(
        float *pvFogValue,
        struct real64x3_t *ptPos,
        float vZ,
        float vDensity,
        struct HazingDynCubeObj_t **pptHazingList,
        int nNumHazingBox)
{
  int v6; // ebx
  int v7; // edx
  double v8; // st7
  double v9; // st7
  struct real32x3_t tColor; // [esp+Ch] [ebp-Ch] BYREF

  if ( !pptHazingList )
  {
    v6 = Hazinglayers_iHazingBuffer;
    v7 = Hazinglayers_iHazingStack;
    pptHazingList = (struct HazingDynCubeObj_t **)(4 * Hazinglayers_iHazingBuffer + 129834072);
    qmemcpy(pptHazingList, Hazinglayers_aptHazingStack, 4 * Hazinglayers_iHazingStack);
    nNumHazingBox = v7;
    Hazinglayers_iHazingBuffer = v7 + v6;
  }
  Hazinglayers_TraceLine(
    &tColor,
    pvFogValue,
    &TransContext_tActiveTransContext.tPos,
    ptPos,
    pptHazingList,
    nNumHazingBox);
  v8 = TransContext_tActiveTransContext.vFOVX * 0.8299999833106995 + 0.17000000178813934;
  if ( v8 < 1.0 )
    vZ = v8 * vZ;
  *pvFogValue = *pvFogValue * 1.52587890625e-05;
  v9 = ((double)Viewport_GetLogZ(vZ) - 130.0) * vDensity * 1.52587890625e-05 + *pvFogValue;
  *pvFogValue = v9;
  if ( v9 >= 0.0 )
  {
    if ( v9 <= 1.0 )
      *pvFogValue = v9;
    else
      *pvFogValue = 1.0;
  }
  else
  {
    *pvFogValue = 0.0;
  }
}
