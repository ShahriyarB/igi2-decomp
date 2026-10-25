/* e/3/shadow.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: e/3/shadow.c:105  [anchor-mhash]
void __cdecl Shadow_RunHandler(struct QTask_s *ptQTask)
{
  if ( *(float *)&ptQTask[1].tQTaskRefList.ptTail < (double)*(float *)&ptQTask[1].ptParent )
    *(float *)&ptQTask[1].tQTaskRefList.ptTail = *(float *)&ptQTask[1].eQTaskType
                                               + *(float *)&ptQTask[1].tQTaskRefList.ptTail;
}

// source: e/3/shadow.c:124  [size]
void __cdecl Shadow_DeleteHandler(struct QTask_s *ptQTask)
{
  QTask_Delete(ptQTask[3].tQTaskChildren.ptTail);
}

// source: e/3/shadow.c:141  [size]
void __cdecl Shadow_MagicObjEnterHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { float v22; };
    struct { char igi2_o1[4]; float v23; };
    struct { char igi2_o2[8]; float v24; };
    struct { char igi2_o3[12]; float v25; };
    struct { char igi2_o4[16]; float v26; };
    struct { char igi2_o5[20]; float Real32x3_Rotate_tTemp; };
    struct { char igi2_o6[20]; float Real32x3_Rotate_tTempa; };
    struct { char igi2_o7[20]; float Real32x3_Rotate_tTempb; };
    struct { char igi2_o8[20]; float Real32x3_Rotate_tTempc; };
    struct { char igi2_o9[24]; float Real32x3_Rotate_tTemp_4; };
    struct { char igi2_o10[24]; float Real32x3_Rotate_tTemp_4a; };
    struct { char igi2_o11[24]; float Real32x3_Rotate_tTemp_4b; };
    struct { char igi2_o12[24]; float Real32x3_Rotate_tTemp_4c; };
    struct { char igi2_o13[28]; float Real32x3_Rotate_tTemp_8; };
    struct { char igi2_o14[28]; float Real32x3_Rotate_tTemp_8a; };
    struct { char igi2_o15[28]; float Real32x3_Rotate_tTemp_8b; };
    struct { char igi2_o16[28]; float Real32x3_Rotate_tTemp_8c; };
    struct { char igi2_o17[32]; struct real32x9_t tMatrix; };
    char igi2_extent[72];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  double v3; // st7
  float *p_tQTaskRefList; // eax
  struct QTask_s *ptNext; // edx
  struct real32x3_t *ptHead; // eax
  double v7; // st7
  struct QReference_s *ptTail; // ecx
  double v9; // st6
  double v10; // st5
  double v11; // st4
  double v12; // st3
  double v13; // st2
  double v14; // rt1
  double v15; // st5
  struct QTask_s *v16; // edi
  struct QTask_s *ptPrev; // esi
  double vY; // st5
  double v19; // st5
  double v20; // st4
  struct QTask_s *ptMiddle; // eax
  float ptQTaska = *(float *)&ptQTask; // [esp+50h] [ebp+4h] ARGSLOT

  if ( ptQTask[1].tQTaskChildren.ptHead->ptNext && ptQTask[1].tQTaskChildren.ptMiddle->ptNext )
  {
    v3 = (1.0 - *(float *)&ptQTask[1].tQTaskChildren.ptTail->ptNext / *(float *)&ptQTask[1].tQTaskRefList.ptMiddle)
       * 0.800000011920929;
    if ( v3 >= 0.30000001192092896 )
    {
      if ( v3 >= 0.0 )
      {
        if ( v3 > 1.0 )
          v3 = 1.0;
      }
      else
      {
        v3 = 0.0;
      }
    }
    else
    {
      v3 = 0.30000001192092896;
    }
    p_tQTaskRefList = (float *)&ptQTask[7].tQTaskRefList;
    if ( ptQTask[7].ptParent )
    {
      ptNext = ptQTask[2].ptNext;
      *(_DWORD *)p_tQTaskRefList = ptNext;
      ptQTask[7].tQTaskRefList.ptMiddle = (struct QReference_s *)ptNext;
      ptQTask[7].tQTaskRefList.ptTail = (struct QReference_s *)ptNext;
    }
    else
    {
      qmemcpy(&ptQTask[7].tQTaskRefList, "fff?fff?fff?", sizeof(ptQTask[7].tQTaskRefList));
    }
    *p_tQTaskRefList = v3 * *p_tQTaskRefList;
    ptHead = (struct real32x3_t *)ptQTask[1].tQTaskRefList.ptHead;
    *(float *)&ptQTask[7].tQTaskRefList.ptMiddle = v3 * *(float *)&ptQTask[7].tQTaskRefList.ptMiddle;
    *(float *)&ptQTask[7].tQTaskRefList.ptTail = v3 * *(float *)&ptQTask[7].tQTaskRefList.ptTail;
    Real32x9_FromReal32x3(&igi2_frame.tMatrix, ptHead);
    v7 = -*(float *)&ptQTask[1].tQTaskRefList.ptTail;
    ptQTask[2].ptPrev = (struct QTask_s *)ptQTask[1].tQTaskRefList.ptTail;
    *(float *)&ptQTask[2].tQTaskChildren.ptHead = v7;
    ptTail = ptQTask[1].tQTaskRefList.ptTail;
    *(float *)&ptQTask[2].tQTaskChildren.ptTail = v7;
    *(float *)&ptQTask[2].tQTaskRefList.ptHead = v7;
    ptQTask[2].tQTaskChildren.ptMiddle = (struct QTask_s *)1092616192;
    *(float *)&ptQTask[3].ptNext = v7;
    ptQTask[2].tQTaskRefList.ptMiddle = (struct QReference_s *)1092616192;
    v9 = *(float *)&ptQTask[1].tQTaskRefList.ptTail;
    *(_DWORD *)&ptQTask[2].eQTaskType = 1092616192;
    *(float *)&ptQTask[3].ptPrev = v9;
    ptQTask[3].tQTaskChildren.ptHead = (struct QTask_s *)1092616192;
    v10 = igi2_frame.tMatrix.tX.vZ * 10.0;
    ptQTask[2].tQTaskRefList.ptTail = ptTail;
    ptQTask[2].ptParent = (struct QTask_s *)ptTail;
    v11 = v7 * igi2_frame.tMatrix.tX.vY;
    igi2_frame.Real32x3_Rotate_tTemp = igi2_frame.tMatrix.tX.vX * *(float *)&ptQTask[2].ptPrev + v11 + v10;
    ptQTaska = igi2_frame.tMatrix.tY.vZ * 10.0;
    v12 = v7 * igi2_frame.tMatrix.tY.vY;
    igi2_frame.Real32x3_Rotate_tTemp_4 = igi2_frame.tMatrix.tY.vX * *(float *)&ptQTask[2].ptPrev + v12 + ptQTaska;
    igi2_frame.v22 = igi2_frame.tMatrix.tZ.vZ * 10.0;
    igi2_frame.v23 = v7 * igi2_frame.tMatrix.tZ.vY;
    v13 = igi2_frame.tMatrix.tZ.vX * *(float *)&ptQTask[2].ptPrev;
    *(float *)&ptQTask[2].ptPrev = igi2_frame.Real32x3_Rotate_tTemp;
    *(float *)&ptQTask[2].tQTaskChildren.ptHead = igi2_frame.Real32x3_Rotate_tTemp_4;
    igi2_frame.Real32x3_Rotate_tTemp_8 = v13 + igi2_frame.v23 + igi2_frame.v22;
    *(float *)&ptQTask[2].tQTaskChildren.ptMiddle = igi2_frame.Real32x3_Rotate_tTemp_8;
    igi2_frame.v24 = v7 * igi2_frame.tMatrix.tX.vX;
    igi2_frame.Real32x3_Rotate_tTempa = v11 + igi2_frame.v24 + v10;
    igi2_frame.v25 = v7 * igi2_frame.tMatrix.tY.vX;
    igi2_frame.Real32x3_Rotate_tTemp_4a = v12 + igi2_frame.v25 + ptQTaska;
    v14 = v10;
    v15 = v7 * igi2_frame.tMatrix.tZ.vX;
    *(float *)&ptQTask[2].tQTaskChildren.ptTail = igi2_frame.Real32x3_Rotate_tTempa;
    v16 = ptQTask[3].tQTaskChildren.ptTail;
    ptPrev = ptQTask[1].ptPrev;
    igi2_frame.v26 = v15;
    *(float *)&ptQTask[2].tQTaskRefList.ptHead = igi2_frame.Real32x3_Rotate_tTemp_4a;
    igi2_frame.Real32x3_Rotate_tTemp_8a = igi2_frame.v23 + igi2_frame.v26 + igi2_frame.v22;
    vY = igi2_frame.tMatrix.tX.vY;
    *(float *)&ptQTask[2].tQTaskRefList.ptMiddle = igi2_frame.Real32x3_Rotate_tTemp_8a;
    igi2_frame.Real32x3_Rotate_tTempb = vY * *(float *)&ptQTask[2].ptParent
                           + igi2_frame.tMatrix.tX.vX * *(float *)&ptQTask[2].tQTaskRefList.ptTail
                           + v14;
    igi2_frame.Real32x3_Rotate_tTemp_4b = igi2_frame.tMatrix.tY.vY * *(float *)&ptQTask[2].ptParent
                             + igi2_frame.tMatrix.tY.vX * *(float *)&ptQTask[2].tQTaskRefList.ptTail
                             + ptQTaska;
    v19 = igi2_frame.tMatrix.tZ.vY * *(float *)&ptQTask[2].ptParent;
    v20 = igi2_frame.tMatrix.tZ.vX * *(float *)&ptQTask[2].tQTaskRefList.ptTail;
    *(float *)&ptQTask[2].tQTaskRefList.ptTail = igi2_frame.Real32x3_Rotate_tTempb;
    *(float *)&ptQTask[2].ptParent = igi2_frame.Real32x3_Rotate_tTemp_4b;
    igi2_frame.Real32x3_Rotate_tTemp_8b = v19 + v20 + igi2_frame.v22;
    *(float *)&ptQTask[2].eQTaskType = igi2_frame.Real32x3_Rotate_tTemp_8b;
    igi2_frame.Real32x3_Rotate_tTempc = v9 * igi2_frame.tMatrix.tX.vY + igi2_frame.v24 + v14;
    *(float *)&ptQTask[3].ptNext = igi2_frame.Real32x3_Rotate_tTempc;
    igi2_frame.Real32x3_Rotate_tTemp_4c = igi2_frame.tMatrix.tY.vY * v9 + igi2_frame.v25 + ptQTaska;
    *(float *)&ptQTask[3].ptPrev = igi2_frame.Real32x3_Rotate_tTemp_4c;
    igi2_frame.Real32x3_Rotate_tTemp_8c = v9 * igi2_frame.tMatrix.tZ.vY + igi2_frame.v26 + igi2_frame.v22;
    *(float *)&ptQTask[3].tQTaskChildren.ptHead = igi2_frame.Real32x3_Rotate_tTemp_8c;
    qmemcpy(&v16[1], ptPrev, 0x18u);
    ptMiddle = ptQTask[3].tQTaskChildren.ptMiddle;
    ptQTask[5].tQTaskChildren.ptMiddle = ptMiddle;
    ptQTask[7].tQTaskChildren.ptMiddle = ptMiddle;
    ((void (__cdecl *)(struct QTask_s *, _DWORD))QTask_aatQTaskFinalEvent[5][ptQTask[3].tQTaskChildren.ptTail->eQTaskType].pfHandler)(
      ptQTask[3].tQTaskChildren.ptTail,
      0);
  }
}

// source: e/3/shadow.c:214  [anchor-strings]
void __cdecl Shadow_Open()
{
  unsigned __int16 BaseQTaskType; // ax
  unsigned __int16 v1; // si

  BaseQTaskType = QTask_GetBaseQTaskType();
  v1 = QTask_NewQTaskType("Shadow", 316, BaseQTaskType, 0, 0);
  Shadow_eQTaskType = v1;
  QTask_LinkQTaskEventHandlerFn(v1, MagicObj_eMagicObjEnterEvent, Shadow_MagicObjEnterHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 1, (void (__cdecl *)(struct QTask_s *))Shadow_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 2, Shadow_DeleteHandler);
}

// source: e/3/shadow.c:233  [size]
void __cdecl Shadow_Close()
{
  QTask_DeleteQTaskType(Shadow_eQTaskType);
}

// source: e/3/shadow.c:255  [anchor-callee]
struct QTask_s *__cdecl Shadow_New(
        struct QTask_s *ptParent,
        struct real64x3_t *ptPos,
        enum bool *pisEnabled,
        enum bool *pisPosValid,
        float *pvDistance,
        struct real32x3_t *ptNormal,
        float vMaxDistance,
        float vRadius,
        struct TexInfo_s *ptTexInfo)
{
  struct QTask_s *v10; // ebx
  struct real32x3_t *ptNext; // eax
  struct QTask_s *v13; // eax
  struct real32x3_t *ptNormala = *(struct real32x3_t * *)&vRadius; // [esp+28h] [ebp+18h] ARGSLOT

  v10 = QTask_NewFn(ptParent, Shadow_eQTaskType, nullptr);
  v10[1].ptNext = (struct QTask_s *)World_ptActiveWorld;
  v10[1].tQTaskChildren.ptHead = (struct QTask_s *)pisEnabled;
  v10[1].tQTaskChildren.ptTail = (struct QTask_s *)pvDistance;
  v10[1].tQTaskChildren.ptMiddle = (struct QTask_s *)pisPosValid;
  v10[1].tQTaskRefList.ptHead = (struct QReference_s *)ptNormal;
  *(float *)&v10[1].ptParent = vRadius;
  ptNext = (struct real32x3_t *)v10[1].ptNext;
  *(float *)&v10[1].tQTaskRefList.ptMiddle = vMaxDistance;
  ptNormala = ptNext;
  LOWORD(ptNext) = PolyListDynCubeObj_eQTaskType;
  v10[1].ptPrev = (struct QTask_s *)ptPos;
  *(float *)&v10[1].tQTaskRefList.ptTail = vRadius;
  v10[3].tQTaskChildren.ptMiddle = (struct QTask_s *)ptTexInfo;
  v13 = QTask_NewFn(nullptr, (unsigned __int16)ptNext, nullptr);
  v13[2].ptParent = (struct QTask_s *)ptNormala;
  v13[4].ptPrev = (struct QTask_s *)2;
  v13[4].tQTaskChildren.ptHead = (struct QTask_s *)0x200000;
  v13[4].tQTaskChildren.ptTail = nullptr;
  v13[4].tQTaskChildren.ptMiddle = nullptr;
  v13[4].tQTaskRefList.ptTail = nullptr;
  v13[4].tQTaskRefList.ptMiddle = nullptr;
  v13[4].ptNext = nullptr;
  *(_DWORD *)&v13[4].eQTaskType = 0;
  v13[4].tQTaskRefList.ptHead = (struct QReference_s *)1;
  v13[4].ptParent = (struct QTask_s *)1;
  *(_DWORD *)&v13[2].eQTaskType = (char *)v10 + 140;
  qmemcpy(&v13[1], ptPos, 0x18u);
  qmemcpy(&v13[3], &Shadow_tMatrix, sizeof(struct QTask_s));
  v10[3].tQTaskRefList.ptHead = (struct QReference_s *)&v10[2].ptPrev;
  v10[3].tQTaskChildren.ptTail = v13;
  v10[3].ptParent = (struct QTask_s *)((char *)v10 + 300);
  *(_DWORD *)&v10[3].eQTaskType = (char *)v10 + 300;
  v10[4].ptNext = (struct QTask_s *)((char *)v10 + 300);
  v10[3].tQTaskRefList.ptMiddle = (struct QReference_s *)&v10[2].tQTaskChildren.ptTail;
  v10[3].tQTaskRefList.ptTail = (struct QReference_s *)&v10[2].tQTaskRefList.ptTail;
  v10[4].tQTaskRefList.ptTail = (struct QReference_s *)1065353216;
  v10[4].ptParent = (struct QTask_s *)1065353216;
  *(_DWORD *)&v10[4].eQTaskType = 1065353216;
  v10[5].tQTaskChildren.ptMiddle = nullptr;
  v10[4].ptPrev = nullptr;
  v10[4].tQTaskChildren.ptHead = nullptr;
  v10[4].tQTaskChildren.ptMiddle = nullptr;
  v10[4].tQTaskChildren.ptTail = (struct QTask_s *)1065353216;
  v10[4].tQTaskRefList.ptHead = (struct QReference_s *)1065353216;
  v10[4].tQTaskRefList.ptMiddle = nullptr;
  v10[5].tQTaskRefList.ptTail = (struct QReference_s *)&v10[2].tQTaskRefList.ptTail;
  v10[5].tQTaskRefList.ptHead = (struct QReference_s *)&v10[2].tQTaskChildren.ptTail;
  v10[7].tQTaskChildren.ptMiddle = nullptr;
  v10[6].ptPrev = nullptr;
  v10[6].tQTaskRefList.ptMiddle = nullptr;
  v10[5].ptParent = (struct QTask_s *)((char *)v10 + 300);
  *(_DWORD *)&v10[5].eQTaskType = (char *)v10 + 300;
  v10[6].ptNext = (struct QTask_s *)((char *)v10 + 300);
  v10[5].tQTaskRefList.ptMiddle = (struct QReference_s *)&v10[3];
  v10[6].tQTaskRefList.ptTail = (struct QReference_s *)1065353216;
  v10[6].ptParent = (struct QTask_s *)1065353216;
  *(_DWORD *)&v10[6].eQTaskType = 1065353216;
  v10[6].tQTaskChildren.ptHead = (struct QTask_s *)1065353216;
  v10[6].tQTaskChildren.ptMiddle = (struct QTask_s *)1065353216;
  v10[6].tQTaskChildren.ptTail = (struct QTask_s *)1065353216;
  v10[6].tQTaskRefList.ptHead = (struct QReference_s *)1065353216;
  return v10;
}

// source: e/3/shadow.c:341  [size]
struct TexInfo_s *__cdecl Shadow_ResetTexture(
        struct QTask_s *ptShadowQTask,
        struct TexInfo_s *ptTexInfo)
{
  ptShadowQTask[3].tQTaskChildren.ptMiddle = (struct QTask_s *)ptTexInfo;
  return ptTexInfo;
}

// source: e/3/shadow.c:361  [size]
struct QTask_s *__cdecl Shadow_StretchFromPoint(
        struct QTask_s *ptShadowQTask,
        float vDuration)
{
  ptShadowQTask[1].tQTaskRefList.ptTail = nullptr;
  *(float *)&ptShadowQTask[1].eQTaskType = *(float *)&ptShadowQTask[1].ptParent / (vDuration * 30.0);
  return ptShadowQTask;
}

// source: e/3/shadow.c:382  [size]
struct QTask_s *__cdecl Shadow_SetLight(struct QTask_s *ptShadowQTask, float vLight)
{
  ptShadowQTask[7].ptParent = (struct QTask_s *)1;
  *(float *)&ptShadowQTask[2].ptNext = vLight;
  return ptShadowQTask;
}
