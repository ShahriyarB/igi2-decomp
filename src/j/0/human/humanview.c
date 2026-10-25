/* j/0/human/humanview.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/human/humanview.c:56  [size]
void __cdecl HumanView_GetSerializeParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = HumanView_ptSerializeParameterList;
}

// source: j/0/human/humanview.c:74  [anchor-mhash]
void __cdecl HumanView_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct LODVirModel_s *LODVirModelExistsFn; // eax
  struct Model_s *v3; // ecx
  struct Mesh3D_Mesh_t *v4; // ecx
  struct Model_s *ptModel; // ecx
  struct Mesh3D_Mesh_t *ptMesh; // ecx
  struct QReference_s *v7; // eax
  _DWORD v8[2]; // [esp+8h] [ebp-8h] BYREF

  BoneDynCubeObj_Init((struct BoneDynCubeObj_s *)ptQTask, Game_ptGame->ptWorld);
  LODVirModelExistsFn = MTP_GetLODVirModelExistsFn(*(char **)pxContext);
  if ( !LODVirModelExistsFn
    || LODVirModelExistsFn->nLOD <= 0
    || !LODVirModelExistsFn->aptVirModel[0]
    || (v3 = LODVirModelExistsFn->aptVirModel[0]->ptModel) == nullptr
    || (v4 = v3->ptMesh) == nullptr
    || v4->eRenderMeshType != MESH3D_RENDERMESHTYPE_DIRECT3D_BONE )
  {
    LODVirModelExistsFn = MTP_GetLODVirModelExistsFn("005_01_1");
    if ( !LODVirModelExistsFn
      || LODVirModelExistsFn->nLOD <= 0
      || !LODVirModelExistsFn->aptVirModel[0]
      || (ptModel = LODVirModelExistsFn->aptVirModel[0]->ptModel) == nullptr
      || (ptMesh = ptModel->ptMesh) == nullptr
      || ptMesh->eRenderMeshType != MESH3D_RENDERMESHTYPE_DIRECT3D_BONE )
    {
      LODVirModelExistsFn = nullptr;
    }
  }
  ptQTask[2].tQTaskRefList.ptTail = (struct QReference_s *)9;
  BoneDynCubeObj_SetLODVirModel((struct BoneDynCubeObj_s *)ptQTask, LODVirModelExistsFn);
  v8[1] = ptQTask[7].tQTaskRefList.ptTail;
  v8[0] = ptQTask;
  v7 = (struct QReference_s *)QTask_NewFn(ptQTask, AnimController_eQTaskType, v8);
  ptQTask[16].tQTaskRefList.ptTail = v7;
  v7[3].pxObject = (void *)((int)v7[3].pxObject & ~2u);
  ptQTask[16].tQTaskRefList.ptTail[3].pxObject = (void *)((int)ptQTask[16].tQTaskRefList.ptTail[3].pxObject | 8);
  ptQTask[16].tQTaskRefList.ptTail[3].pxObject = (void *)((int)ptQTask[16].tQTaskRefList.ptTail[3].pxObject | 0x80);
  LOBYTE(ptQTask[10].ptNext) = 0;
  BYTE1(ptQTask[10].ptNext) = 0;
  *(_DWORD *)&ptQTask[11].eQTaskType = 0;
  ptQTask[12].ptNext = nullptr;
  ptQTask[12].ptPrev = nullptr;
  ptQTask[12].tQTaskRefList.ptHead = nullptr;
  ptQTask[12].tQTaskChildren.ptHead = nullptr;
  ptQTask[12].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[12].tQTaskChildren.ptTail = nullptr;
  ptQTask[12].tQTaskRefList.ptMiddle = nullptr;
  LOBYTE(ptQTask[12].tQTaskRefList.ptTail) = 0;
  BYTE1(ptQTask[12].tQTaskRefList.ptTail) = 1;
  BYTE2(ptQTask[12].tQTaskRefList.ptTail) = 0;
  ptQTask[14].tQTaskChildren.ptTail = nullptr;
  ptQTask[14].tQTaskRefList.ptHead = nullptr;
  ptQTask[14].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[14].tQTaskRefList.ptTail = nullptr;
  ptQTask[14].ptParent = nullptr;
  *(_DWORD *)&ptQTask[14].eQTaskType = 0;
  ptQTask[15].ptNext = nullptr;
  ptQTask[15].tQTaskChildren.ptTail = nullptr;
  HumanView_ClearObjectOrientation(ptQTask);
  ptQTask[16].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[19].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[19].tQTaskChildren.ptTail = nullptr;
  ptQTask[11].ptParent = nullptr;
  ptQTask[12].tQTaskRefList.ptHead = nullptr;
  ptQTask[17].tQTaskChildren.ptTail = nullptr;
  ptQTask[17].tQTaskRefList.ptHead = nullptr;
  ptQTask[17].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[17].tQTaskRefList.ptTail = nullptr;
  ptQTask[17].ptParent = nullptr;
  *(_DWORD *)&ptQTask[17].eQTaskType = 0;
  ptQTask[19].ptNext = nullptr;
  ptQTask[19].ptPrev = nullptr;
  ptQTask[19].tQTaskChildren.ptHead = nullptr;
  ptQTask[18].ptNext = (struct QTask_s *)1065353216;
  ptQTask[18].ptPrev = nullptr;
  ptQTask[18].tQTaskChildren.ptHead = nullptr;
  ptQTask[18].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[18].tQTaskChildren.ptTail = (struct QTask_s *)1065353216;
  ptQTask[18].tQTaskRefList.ptHead = nullptr;
  ptQTask[18].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[18].tQTaskRefList.ptTail = nullptr;
  ptQTask[18].ptParent = (struct QTask_s *)1065353216;
  *(float *)&ptQTask[16].tQTaskChildren.ptHead = tan(0.7853981852531433);
  *(float *)&ptQTask[16].tQTaskRefList.ptHead = tan(0.5235987901687622);
  *(_DWORD *)&ptQTask[18].eQTaskType = 0;
}

// source: j/0/human/humanview.c:174  [anchor-mhash]
void __cdecl HumanView_RunHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *FirstChildOfType; // eax
  double *p_ptTail; // edx
  struct QTask_s **p_ptPrev; // esi
  double v4; // st7
  double v5; // st7
  double v6; // st7
  double v7[3]; // [esp+4h] [ebp-18h] BYREF

  if ( BYTE1(ptQTask[10].ptNext) )
  {
    ((void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[1][BoneDynCubeObj_eQTaskType].pfHandler)(ptQTask);
    FirstChildOfType = QTask_GetFirstChildOfType(
                         (struct QTask_s *)ptQTask[16].tQTaskRefList.ptTail,
                         WeaponMagicObj_eQTaskType);
    p_ptTail = (double *)&ptQTask[17].tQTaskChildren.ptTail;
    qmemcpy(v7, &ptQTask[17].tQTaskChildren.ptTail, sizeof(v7));
    if ( FirstChildOfType )
    {
      qmemcpy(p_ptTail, &FirstChildOfType[1], 0x18u);
      p_ptPrev = &FirstChildOfType[3].ptPrev;
    }
    else
    {
      qmemcpy(p_ptTail, &ptQTask[1], 0x18u);
      p_ptPrev = &ptQTask[3].ptPrev;
    }
    v4 = *p_ptTail - v7[0];
    qmemcpy(&ptQTask[18], p_ptPrev, sizeof(struct QTask_s));
    *(float *)&ptQTask[19].ptNext = v4;
    *(float *)&ptQTask[19].ptPrev = *(double *)&ptQTask[17].tQTaskRefList.ptMiddle - v7[1];
    *(float *)&ptQTask[19].tQTaskChildren.ptHead = *(double *)&ptQTask[17].ptParent - v7[2];
  }
  if ( ptQTask[16].tQTaskRefList.ptMiddle )
  {
    if ( *(float *)&ptQTask[16].tQTaskChildren.ptHead >= (double)*(float *)&ptQTask[16].tQTaskChildren.ptMiddle )
    {
      if ( *(float *)&ptQTask[16].tQTaskChildren.ptHead > (double)*(float *)&ptQTask[16].tQTaskChildren.ptMiddle )
      {
        v6 = *(float *)&ptQTask[16].tQTaskChildren.ptHead - *(float *)&ptQTask[16].tQTaskChildren.ptTail;
        *(float *)&ptQTask[16].tQTaskChildren.ptHead = v6;
        if ( v6 < *(float *)&ptQTask[16].tQTaskChildren.ptMiddle )
          ptQTask[16].tQTaskChildren.ptHead = ptQTask[16].tQTaskChildren.ptMiddle;
      }
    }
    else
    {
      v5 = *(float *)&ptQTask[16].tQTaskChildren.ptTail + *(float *)&ptQTask[16].tQTaskChildren.ptHead;
      *(float *)&ptQTask[16].tQTaskChildren.ptHead = v5;
      if ( v5 > *(float *)&ptQTask[16].tQTaskChildren.ptMiddle )
        ptQTask[16].tQTaskChildren.ptHead = ptQTask[16].tQTaskChildren.ptMiddle;
    }
  }
}

void __cdecl sub_4E0A40(struct BoneDynCubeObj_s *a1)
{
  BoneDynCubeObj_SetLODVirModel(a1, nullptr);
  BYTE1(a1[1].tModelObj.tDynCubeObj.tQObj.tQTask.ptNext) = 0;
}

void __cdecl sub_4E0A60(struct QTask_s *a1, void *a2)
{
  struct QReference_s *ptHumanCameraQTaskRef; // eax
  struct QTask_s *ptParent; // edx
  struct QTask_s *pxObject; // eax
  struct QTask_s *v5; // ecx
  struct QReference_s *ptTail; // eax
  void (__cdecl *pfHandler)(struct QReference_s *, _DWORD); // ecx

  ptHumanCameraQTaskRef = Game_ptGame->ptHumanCameraQTaskRef;
  ptParent = a1->ptParent;
  if ( ptHumanCameraQTaskRef )
    pxObject = (struct QTask_s *)ptHumanCameraQTaskRef->pxObject;
  else
    pxObject = nullptr;
  v5 = pxObject[2].ptParent;
  if ( v5
    && !LOBYTE(ptParent[33].tQTaskRefList.ptMiddle)
    && !Computer_ptComputerQTask
    && !a1[16].tQTaskRefList.ptMiddle
    && ViewportQTask_ptActiveViewportQTask[2].tQTaskChildren.ptHead[2].tQTaskChildren.ptHead == pxObject
    && v5->tQTaskChildren.ptHead == ptParent
    && pxObject[6].ptNext == (struct QTask_s *)1 )
  {
    ((void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[5][BoneDynCubeObj_eQTaskType].pfHandler)(
      a1,
      a2);
    ptTail = a1[16].tQTaskRefList.ptTail;
    pfHandler = (void (__cdecl *)(struct QReference_s *, _DWORD))QTask_aatQTaskFinalEvent[MagicObj_eMagicObjEnterEvent][LOWORD(ptTail[3].ptNext)].pfHandler;
    if ( pfHandler )
      pfHandler(ptTail, 0);
  }
}

void __cdecl sub_4E0B20(struct QTask_s *a1, void *a2)
{
  struct QTask_s *ptHead; // eax
  int v3; // edx
  struct QTask_s *v4; // ecx
  void (__cdecl *pfHandler)(struct QTask_s *, void *); // ecx
  int v6; // edx

  BYTE1(a1[10].ptNext) = 0;
  ptHead = a1->tQTaskChildren.ptHead;
  if ( ptHead->ptNext && ptHead )
  {
    v3 = QTask_nProtectedQTaskStackOffset;
    do
    {
      if ( ptHead->ptNext )
        v4 = ptHead->ptNext->ptNext != nullptr ? ptHead->ptNext : nullptr;
      else
        v4 = nullptr;
      QTask_atProtectedQTaskStack[v3].ptQTask = v4;
      pfHandler = (void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[DynCubeObj_eDynCubeObjRemoveQTaskEvent][ptHead->eQTaskType].pfHandler;
      v6 = v3 + 1;
      QTask_nProtectedQTaskStackOffset = v6;
      if ( pfHandler )
      {
        pfHandler(ptHead, a2);
        v6 = QTask_nProtectedQTaskStackOffset;
      }
      ptHead = (struct QTask_s *)dword_849C7DC[v6];
      v3 = v6 - 1;
      QTask_nProtectedQTaskStackOffset = v3;
    }
    while ( ptHead );
  }
}

void __cdecl sub_4E0BB0(struct QTask_s *a1, void *a2)
{
  struct QTask_s *ptHead; // eax
  int v3; // edx
  struct QTask_s *v4; // ecx
  void (__cdecl *pfHandler)(struct QTask_s *, void *); // ecx
  int v6; // edx

  if ( LOBYTE(a1[10].ptNext) )
    BYTE1(a1[10].ptNext) = 1;
  ptHead = a1->tQTaskChildren.ptHead;
  if ( ptHead->ptNext && ptHead )
  {
    v3 = QTask_nProtectedQTaskStackOffset;
    do
    {
      if ( ptHead->ptNext )
        v4 = ptHead->ptNext->ptNext != nullptr ? ptHead->ptNext : nullptr;
      else
        v4 = nullptr;
      QTask_atProtectedQTaskStack[v3].ptQTask = v4;
      pfHandler = (void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[DynCubeObj_eDynCubeObjRegisterQTaskEvent][ptHead->eQTaskType].pfHandler;
      v6 = v3 + 1;
      QTask_nProtectedQTaskStackOffset = v6;
      if ( pfHandler )
      {
        pfHandler(ptHead, a2);
        v6 = QTask_nProtectedQTaskStackOffset;
      }
      ptHead = (struct QTask_s *)dword_849C7DC[v6];
      v3 = v6 - 1;
      QTask_nProtectedQTaskStackOffset = v3;
    }
    while ( ptHead );
  }
}

void __cdecl sub_4E0C40(struct QTask_s *a1, void *a2)
{
  *(_BYTE *)a2 = 0;
}

// source: j/0/human/humanview.c:354  [size]
void __cdecl HumanView_WeaponCollisionEvaluateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_BYTE *)pxContext = 0;
}

// source: j/0/human/humanview.c:374  [size]
void __cdecl HumanView_ObjectCollisionEvaluateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_BYTE *)pxContext = 0;
}

void __cdecl sub_4E0C70(struct QTask_s *a1, _DWORD *a2)
{
  struct QTask_s *v2; // eax
  struct QTask_s *ptParent; // edx
  struct QTask_s *v4; // eax

  v2 = (struct QTask_s *)a2[2];
  *(_BYTE *)a2 = v2 != a1
              && (ptParent = a1->ptParent, v2 != ptParent)
              && (v4 = (struct QTask_s *)a2[3], v4 != a1)
              && v4 != ptParent;
}

void __cdecl sub_4E0CA0(struct QTask_s *a1, _DWORD *a2)
{
  *a2 = (char *)a1 + 408;
  a2[1] = (char *)a1 + 432;
  a2[2] = 0;
}

// source: j/0/human/humanview.c:571  [size]
struct QTask_s *__cdecl HumanView_LockOrientation(struct QTask_s *ptHumanViewQTask)
{
  LOBYTE(ptHumanViewQTask[12].tQTaskRefList.ptTail) = 1;
  return ptHumanViewQTask;
}

// source: j/0/human/humanview.c:588  [size]
struct QTask_s *__cdecl HumanView_UnlockOrientation(struct QTask_s *ptHumanViewQTask)
{
  LOBYTE(ptHumanViewQTask[12].tQTaskRefList.ptTail) = 0;
  return ptHumanViewQTask;
}

// source: j/0/human/humanview.c:605  [size]
struct QTask_s *__cdecl HumanView_ClearOrientation(struct QTask_s *ptHumanViewQTask)
{
  *(_DWORD *)&ptHumanViewQTask[11].eQTaskType = 0;
  ptHumanViewQTask[12].ptNext = nullptr;
  ptHumanViewQTask[12].ptPrev = nullptr;
  ptHumanViewQTask[12].tQTaskRefList.ptHead = nullptr;
  ptHumanViewQTask[12].tQTaskChildren.ptHead = nullptr;
  ptHumanViewQTask[12].tQTaskChildren.ptMiddle = nullptr;
  ptHumanViewQTask[12].tQTaskChildren.ptTail = nullptr;
  ptHumanViewQTask[12].tQTaskRefList.ptMiddle = nullptr;
  return ptHumanViewQTask;
}

// source: j/0/human/humanview.c:630  [anchor-mhash]
struct QTask_s *__cdecl HumanView_ClearObjectOrientation(
        struct QTask_s *ptHumanViewQTask)
{
  ptHumanViewQTask[15].tQTaskRefList.ptMiddle = nullptr;
  ptHumanViewQTask[15].tQTaskRefList.ptTail = nullptr;
  *(_DWORD *)&ptHumanViewQTask[15].eQTaskType = 0;
  ptHumanViewQTask[16].ptNext = nullptr;
  ptHumanViewQTask[10].ptParent = (struct QTask_s *)1065353216;
  *(_DWORD *)&ptHumanViewQTask[10].eQTaskType = 0;
  ptHumanViewQTask[11].ptNext = nullptr;
  ptHumanViewQTask[11].ptPrev = nullptr;
  ptHumanViewQTask[11].tQTaskChildren.ptHead = (struct QTask_s *)1065353216;
  ptHumanViewQTask[11].tQTaskChildren.ptMiddle = nullptr;
  ptHumanViewQTask[11].tQTaskChildren.ptTail = nullptr;
  ptHumanViewQTask[11].tQTaskRefList.ptHead = nullptr;
  ptHumanViewQTask[11].tQTaskRefList.ptMiddle = (struct QReference_s *)1065353216;
  ptHumanViewQTask[11].tQTaskRefList.ptTail = nullptr;
  return ptHumanViewQTask;
}

// source: j/0/human/humanview.c:657  [size]
struct QTask_s *__cdecl HumanView_SetIdealObjectOrientation(
        struct QTask_s *ptHumanViewQTask,
        float vIdealObjectAlpha,
        float vIdealObjectGamma,
        float vStepAlpha,
        float vStepGamma)
{
  *(float *)&ptHumanViewQTask[15].tQTaskRefList.ptTail = vIdealObjectAlpha;
  *(float *)&ptHumanViewQTask[16].ptNext = vIdealObjectGamma;
  *(float *)&ptHumanViewQTask[15].ptParent = vStepAlpha;
  *(float *)&ptHumanViewQTask[16].ptPrev = vStepGamma;
  return ptHumanViewQTask;
}

// source: j/0/human/humanview.c:682  [size]
struct QTask_s *__cdecl HumanView_SetRealObjectOrientation(
        struct QTask_s *ptHumanViewQTask,
        float vRealObjectAlpha,
        float vRealObjectGamma)
{
  *(float *)&ptHumanViewQTask[15].tQTaskRefList.ptTail = vRealObjectAlpha;
  *(float *)&ptHumanViewQTask[16].ptNext = vRealObjectGamma;
  *(float *)&ptHumanViewQTask[15].tQTaskRefList.ptMiddle = vRealObjectAlpha;
  *(float *)&ptHumanViewQTask[15].eQTaskType = vRealObjectGamma;
  return ptHumanViewQTask;
}

// source: j/0/human/humanview.c:704  [anchor-mhash]
char __cdecl HumanView_IsObjectRealObjectIdeal(struct QTask_s *ptHumanViewQTask)
{
  return *(float *)&ptHumanViewQTask[15].tQTaskRefList.ptMiddle == *(float *)&ptHumanViewQTask[15].tQTaskRefList.ptTail
      && *(float *)&ptHumanViewQTask[15].eQTaskType == *(float *)&ptHumanViewQTask[16].ptNext;
}

// source: j/0/human/humanview.c:729  [anchor-callee]
void __cdecl HumanView_UpdateView(
        struct QTask_s *ptHumanViewQTask,
        struct QTask_s *ptHumanQTask)
{
  double v2; // st7
  double v3; // st6
  double v4; // st7
  double v5; // st7
  float vDeltaAlpha; // [esp+0h] [ebp-8h]
  float vDeltaAlphaa; // [esp+0h] [ebp-8h]
  float v8; // [esp+4h] [ebp-4h]

  v8 = tan(0.7853981852531433);
  v2 = *(float *)&ptHumanQTask[19].tQTaskChildren.ptHead;
  if ( *(float *)&ptHumanViewQTask[16].tQTaskChildren.ptHead == v8 )
    v2 = (v2 + *(float *)&ptHumanQTask[12].eQTaskType) * 0.5;
  if ( LOBYTE(ptHumanViewQTask[12].tQTaskRefList.ptTail) )
    v2 = 0.0;
  vDeltaAlpha = 3.1415927410125732 * v2 * *(float *)&ptHumanViewQTask[16].tQTaskChildren.ptHead;
  v3 = v2;
  if ( v2 < 0.0 )
    v3 = -v2;
  if ( v3 < 0.05999999865889549 )
  {
    if ( v2 < 0.0 )
      v2 = -v2;
    vDeltaAlpha = vDeltaAlpha / (2.0 - v2 * 16.666666666666668);
  }
  v4 = vDeltaAlpha + *(float *)&ptHumanViewQTask[12].ptNext;
  *(float *)&ptHumanViewQTask[12].ptNext = v4;
  if ( v4 >= -1.4835299253463745 )
  {
    if ( v4 > 1.4835299253463745 )
      ptHumanViewQTask[12].ptNext = (struct QTask_s *)1069409359;
  }
  else
  {
    ptHumanViewQTask[12].ptNext = (struct QTask_s *)-1078074289;
  }
  v5 = *(float *)&ptHumanViewQTask[12].tQTaskRefList.ptHead
     + *(float *)&ptHumanViewQTask[12].ptPrev
     + *(float *)&ptHumanViewQTask[12].ptNext;
  *(float *)&ptHumanViewQTask[11].eQTaskType = v5;
  vDeltaAlphaa = *(float *)&ptHumanViewQTask[12].tQTaskChildren.ptTail
               + *(float *)&ptHumanViewQTask[12].tQTaskChildren.ptMiddle;
  *(float *)&ptHumanViewQTask[12].tQTaskChildren.ptHead = vDeltaAlphaa;
  if ( *(float *)&ptHumanQTask[21].ptNext != 0.0 )
  {
    *(float *)&ptHumanViewQTask[16].tQTaskChildren.ptHead = *(float *)&ptHumanViewQTask[16].tQTaskChildren.ptHead
                                                          * 0.9599999785423279;
    *(float *)&ptHumanViewQTask[16].tQTaskRefList.ptHead = *(float *)&ptHumanViewQTask[16].tQTaskRefList.ptHead
                                                         * 0.9599999785423279;
  }
  if ( *(float *)&ptHumanQTask[21].ptPrev != 0.0 )
  {
    *(float *)&ptHumanViewQTask[16].tQTaskChildren.ptHead = *(float *)&ptHumanViewQTask[16].tQTaskChildren.ptHead
                                                          * 1.0416667461395264;
    *(float *)&ptHumanViewQTask[16].tQTaskRefList.ptHead = *(float *)&ptHumanViewQTask[16].tQTaskRefList.ptHead
                                                         * 1.0416667461395264;
  }
  if ( *(float *)&ptHumanQTask[21].tQTaskChildren.ptHead != 0.0 )
  {
    *(float *)&ptHumanViewQTask[16].tQTaskChildren.ptHead = v8;
    *(float *)&ptHumanViewQTask[16].tQTaskRefList.ptHead = tan(0.5235987901687622);
  }
  if ( v5 >= -1.4835299253463745 )
  {
    if ( v5 > 1.4835299253463745 )
      *(_DWORD *)&ptHumanViewQTask[11].eQTaskType = 1069409359;
  }
  else
  {
    *(_DWORD *)&ptHumanViewQTask[11].eQTaskType = -1078074289;
  }
  if ( vDeltaAlphaa >= -1.5707963705062866 )
  {
    if ( vDeltaAlphaa > 1.5707963705062866 )
      ptHumanViewQTask[12].tQTaskChildren.ptHead = (struct QTask_s *)1070141403;
  }
  else
  {
    ptHumanViewQTask[12].tQTaskChildren.ptHead = (struct QTask_s *)-1077342245;
  }
}

// source: j/0/human/humanview.c:822  [anchor-callee]
void __cdecl HumanView_UpdateBody(
        struct QTask_s *ptHumanViewQTask,
        struct QTask_s *ptHumanQTask,
        enum bool isUpdateAnim)
{
  #pragma pack(push, 1)
  union
  {
    struct { float ptDynCubeObj; };
    struct { char igi2_o1[24]; float vAlpha; };
    struct { char igi2_o2[24]; int vAlphaa; };
    struct { char igi2_o3[24]; float vAlphab; };
    struct { char igi2_o4[28]; int nNumPoints[2]; };
    struct { char igi2_o5[36]; float v73; };
    struct { char igi2_o6[44]; struct real32x9_t ptIntersection; };
    struct { char igi2_o7[88]; float ptIntersection_44; };
    struct { char igi2_o8[92]; float ptIntersection_48; };
    struct { char igi2_o9[96]; float ptIntersection_52; };
    struct { char igi2_o10[100]; float ptIntersection_56; };
    struct { char igi2_o11[104]; float ptIntersection_60; };
    struct { char igi2_o12[108]; struct real64x3_t ptIntersection_64; };
    struct { char igi2_o13[132]; _BYTE ptIntersection_88[40]; };
    struct { char igi2_o14[172]; struct QIntersection_s v82; };
    char igi2_extent[292];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct Game_s *v3; // ebx
  double v4; // st7
  unsigned int v5; // edi
  unsigned int v6; // edx
  double v7; // st7
  int v8; // ecx
  unsigned int v9; // edi
  double v10; // st7
  int v11; // eax
  unsigned int v12; // edx
  int v13; // edi
  double v14; // st7
  unsigned int v15; // edx
  double v16; // st7
  double v17; // st6
  double v18; // st5
  unsigned int v19; // esi
  int v20; // eax
  int v21; // edi
  unsigned int v22; // esi
  double v23; // st4
  int v24; // edi
  int v25; // esi
  unsigned int v26; // edx
  double v27; // st4
  double v28; // st4
  double v29; // st4
  double v30; // st4
  long double v31; // st4
  double v32; // st4
  double v33; // st5
  double v34; // st4
  double v35; // rt0
  double v36; // st6
  double v37; // st7
  double v38; // st6
  char v39; // al
  double v40; // st7
  double v41; // st6
  double v42; // st7
  double v43; // st6
  double v44; // st5
  char v45; // fps^1
  double v46; // st7
  bool v47; // c0
  char v48; // c2
  bool v49; // c3
  char v50; // ah
  double v52; // st7
  unsigned __int8 v53; // c0
  unsigned __int8 v54; // c2
  double v55; // st7
  double v56; // st7
  double v57; // st7
  double v58; // st7
  double v59; // st7
  double v60; // st7
  double v61; // st6
  double v62; // st7
  double v63; // st7
  double v64; // st7
  double v65; // st7
  double v66; // st7
  struct World_s *ptWorld; // eax

  v3 = Game_ptGame;
  v4 = *(float *)&ptHumanQTask[33].tQTaskRefList.ptTail + *(float *)&ptHumanViewQTask[11].eQTaskType;
  igi2_frame.ptIntersection_52 = 0.0;
  igi2_frame.ptIntersection_56 = 0.0;
  igi2_frame.ptIntersection_60 = 0.0;
  igi2_frame.ptIntersection_44 = v4;
  igi2_frame.vAlpha = 0.0;
  igi2_frame.ptIntersection_48 = *(float *)&ptHumanQTask[34].ptPrev + *(float *)&ptHumanViewQTask[12].tQTaskChildren.ptHead;
  if ( *(float *)&ptHumanViewQTask[15].ptNext != 0.0 )
  {
    v5 = (Game_ptGame->tRunRandomState.anRandom[0] >> 7)
       ^ Game_ptGame->tRunRandomState.anRandom[2]
       ^ Game_ptGame->tRunRandomState.anRandom[1];
    v6 = v5 + Game_ptGame->tRunRandomState.anRandom[0];
    v7 = (double)(unsigned __int16)(((Game_ptGame->tRunRandomState.anRandom[0] >> 7)
                                   ^ LOWORD(Game_ptGame->tRunRandomState.anRandom[2])
                                   ^ LOWORD(Game_ptGame->tRunRandomState.anRandom[1]))
                                  + LOWORD(Game_ptGame->tRunRandomState.anRandom[0]));
    Game_ptGame->tRunRandomState.anRandom[2] ^= Game_ptGame->tRunRandomState.anRandom[0] >> 7;
    v3->tRunRandomState.anRandom[1] = v5;
    v3->tRunRandomState.anRandom[0] = v6;
    v8 = (v3->tRunRandomState.anRandom[0] >> 7) ^ v3->tRunRandomState.anRandom[2] ^ v3->tRunRandomState.anRandom[1];
    v9 = v8 + v3->tRunRandomState.anRandom[0];
    v10 = (v7 * 0.0000152587890625 - 0.5 + v7 * 0.0000152587890625 - 0.5)
        * *(float *)&ptHumanViewQTask[15].tQTaskChildren.ptHead
        * *(float *)&ptHumanViewQTask[15].ptNext
        + igi2_frame.ptIntersection_44;
    igi2_frame.vAlphaa = (unsigned __int16)(((v3->tRunRandomState.anRandom[0] >> 7)
                                ^ LOWORD(v3->tRunRandomState.anRandom[2])
                                ^ LOWORD(v3->tRunRandomState.anRandom[1]))
                               + LOWORD(v3->tRunRandomState.anRandom[0]));
    v3->tRunRandomState.anRandom[2] ^= v3->tRunRandomState.anRandom[0] >> 7;
    v3->tRunRandomState.anRandom[1] = v8;
    igi2_frame.ptIntersection_44 = v10;
    v3->tRunRandomState.anRandom[0] = v9;
    v11 = (v3->tRunRandomState.anRandom[0] >> 7) ^ v3->tRunRandomState.anRandom[2];
    v12 = v3->tRunRandomState.anRandom[0];
    v13 = v11 ^ v3->tRunRandomState.anRandom[1];
    v14 = ((double)igi2_frame.vAlphaa * 0.0000152587890625 - 0.5 + (double)igi2_frame.vAlphaa * 0.0000152587890625 - 0.5)
        * *(float *)&ptHumanViewQTask[15].tQTaskChildren.ptHead
        * *(float *)&ptHumanViewQTask[15].ptNext;
    v3->tRunRandomState.anRandom[2] = v11;
    v15 = v13 + v12;
    igi2_frame.vAlpha = v14;
    igi2_frame.nNumPoints[0] = (unsigned __int16)v15;
    v3->tRunRandomState.anRandom[1] = v13;
    v3->tRunRandomState.anRandom[0] = v15;
    igi2_frame.ptIntersection_48 = ((double)(unsigned __int16)v15 * 0.0000152587890625
                       - 0.5
                       + (double)(unsigned __int16)v15 * 0.0000152587890625
                       - 0.5)
                      * *(float *)&ptHumanViewQTask[15].tQTaskChildren.ptHead
                      * *(float *)&ptHumanViewQTask[15].ptNext
                      + igi2_frame.ptIntersection_48;
  }
  Real32x9_Create((struct real32x9_t *)&ptHumanViewQTask[10].ptParent, igi2_frame.ptIntersection_44, igi2_frame.vAlpha, igi2_frame.ptIntersection_48);
  HumanView_GetOriginalViewPosition(&igi2_frame.ptIntersection_64, ptHumanQTask);
  v16 = *(float *)&ptHumanViewQTask[14].tQTaskChildren.ptTail;
  v17 = *(float *)&ptHumanViewQTask[14].tQTaskRefList.ptHead;
  v18 = *(float *)&ptHumanViewQTask[14].tQTaskRefList.ptMiddle;
  if ( *(float *)&ptHumanViewQTask[15].ptNext != 0.0 )
  {
    v19 = v3->tRunRandomState.anRandom[0];
    v20 = (v19 >> 7) ^ v3->tRunRandomState.anRandom[2];
    v21 = v20 ^ v3->tRunRandomState.anRandom[1];
    v3->tRunRandomState.anRandom[2] = v20;
    v22 = v21 + v19;
    igi2_frame.nNumPoints[0] = (unsigned __int16)v22;
    v23 = (double)(unsigned __int16)v22;
    v3->tRunRandomState.anRandom[1] = v21;
    v3->tRunRandomState.anRandom[0] = v22;
    v24 = (v3->tRunRandomState.anRandom[0] >> 7) ^ v3->tRunRandomState.anRandom[2];
    v25 = v24 ^ v3->tRunRandomState.anRandom[1];
    v26 = v25 + v3->tRunRandomState.anRandom[0];
    v27 = (v23 * 0.0000152587890625 - 0.5 + v23 * 0.0000152587890625 - 0.5)
        * *(float *)&ptHumanViewQTask[15].ptPrev
        * *(float *)&ptHumanViewQTask[15].ptNext;
    igi2_frame.nNumPoints[0] = (unsigned __int16)(((v3->tRunRandomState.anRandom[0] >> 7)
                                      ^ LOWORD(v3->tRunRandomState.anRandom[2])
                                      ^ LOWORD(v3->tRunRandomState.anRandom[1]))
                                     + LOWORD(v3->tRunRandomState.anRandom[0]));
    v16 = v16 + v27;
    v3->tRunRandomState.anRandom[2] = v24;
    v28 = (double)igi2_frame.nNumPoints[0];
    v3->tRunRandomState.anRandom[1] = v25;
    v3->tRunRandomState.anRandom[0] = v26;
    v18 = v18
        + (v28 * 0.0000152587890625 - 0.5 + v28 * 0.0000152587890625 - 0.5)
        * *(float *)&ptHumanViewQTask[15].ptPrev
        * *(float *)&ptHumanViewQTask[15].ptNext;
    if ( *(float *)&ptHumanViewQTask[15].ptNext >= 0.0 )
    {
      if ( *(float *)&ptHumanViewQTask[15].ptNext > 0.0 )
      {
        v30 = *(float *)&ptHumanViewQTask[15].ptNext - *(float *)&ptHumanViewQTask[15].tQTaskChildren.ptMiddle;
        *(float *)&ptHumanViewQTask[15].ptNext = v30;
        if ( v30 < 0.0 )
          goto LABEL_9;
      }
    }
    else
    {
      v29 = *(float *)&ptHumanViewQTask[15].tQTaskChildren.ptMiddle + *(float *)&ptHumanViewQTask[15].ptNext;
      *(float *)&ptHumanViewQTask[15].ptNext = v29;
      if ( v29 > 0.0 )
LABEL_9:
        ptHumanViewQTask[15].ptNext = nullptr;
    }
  }
  if ( *(float *)&ptHumanViewQTask[15].tQTaskChildren.ptTail != 0.0 )
  {
    v31 = sin(*(float *)&ptHumanViewQTask[15].tQTaskRefList.ptHead);
    v18 = v18 + *(float *)&ptHumanViewQTask[15].tQTaskChildren.ptTail * v31;
    igi2_frame.ptIntersection_60 = *(float *)&ptHumanViewQTask[15].tQTaskChildren.ptTail * 0.075 * v31;
    v32 = *(float *)&ptHumanViewQTask[15].tQTaskRefList.ptHead + 0.20943951606750488;
    *(float *)&ptHumanViewQTask[15].tQTaskRefList.ptHead = v32;
    if ( v32 >= 3.1415927410125732 )
      ptHumanViewQTask[15].tQTaskChildren.ptTail = nullptr;
  }
  if ( v16 != 0.0 || v17 != 0.0 || v18 != 0.0 )
  {
    igi2_frame.vAlphab = v18;
    v33 = v17 * *(float *)&ptHumanViewQTask[10].eQTaskType + v16 * *(float *)&ptHumanViewQTask[10].ptParent;
    v34 = *(float *)&ptHumanViewQTask[11].ptNext;
    qmemcpy(&igi2_frame.ptIntersection, &igi2_frame.ptIntersection_64, 0x18u);
    *(float *)igi2_frame.nNumPoints = v33 + v34 * 0.0;
    v35 = v17 * *(float *)&ptHumanViewQTask[11].tQTaskChildren.ptHead;
    v36 = v16 * *(float *)&ptHumanViewQTask[11].ptPrev;
    igi2_frame.nNumPoints[1] = (int)ptHumanQTask;
    v37 = v35 + v36 + *(float *)&ptHumanViewQTask[11].tQTaskChildren.ptMiddle * 0.0;
    *(double *)igi2_frame.ptIntersection_88 = *(float *)igi2_frame.nNumPoints + igi2_frame.ptIntersection_64.vX;
    *(double *)&igi2_frame.ptIntersection_88[8] = v37 + igi2_frame.ptIntersection_64.vY;
    *(double *)&igi2_frame.ptIntersection_88[16] = igi2_frame.vAlphab + igi2_frame.ptIntersection_64.vZ;
    World_TraceLinesSpecificMesh(
      v3->ptWorld,
      &igi2_frame.v82,
      (struct real64x3_t *)&igi2_frame.ptIntersection,
      (struct real64x3_t *)igi2_frame.ptIntersection_88,
      1,
      GameFunctions_eObjectCollisionEvaluateQTaskEvent,
      (struct CollisionEvaluateContext_s *)igi2_frame.nNumPoints,
      0xFFFFFFFF,
      1);
    if ( igi2_frame.v82.isHit )
    {
      *(double *)&igi2_frame.ptIntersection_88[8] = igi2_frame.v82.tPos.vY - *(double *)&igi2_frame.ptIntersection.tX.vZ;
      *(double *)igi2_frame.nNumPoints = sqrt(
                                *(double *)&igi2_frame.ptIntersection_88[8] * *(double *)&igi2_frame.ptIntersection_88[8]
                              + (igi2_frame.v82.tPos.vZ - *(double *)&igi2_frame.ptIntersection.tY.vY)
                              * (igi2_frame.v82.tPos.vZ - *(double *)&igi2_frame.ptIntersection.tY.vY)
                              + (igi2_frame.v82.tPos.vX - *(double *)&igi2_frame.ptIntersection.tX.vX)
                              * (igi2_frame.v82.tPos.vX - *(double *)&igi2_frame.ptIntersection.tX.vX));
      *(double *)igi2_frame.ptIntersection_88 = 1.0 / *(double *)igi2_frame.nNumPoints * (igi2_frame.v82.tPos.vX - *(double *)&igi2_frame.ptIntersection.tX.vX);
      *(double *)&igi2_frame.ptIntersection_88[8] = *(double *)&igi2_frame.ptIntersection_88[8] * (1.0 / *(double *)igi2_frame.nNumPoints);
      v38 = *(double *)igi2_frame.nNumPoints - 204.8;
      if ( *(double *)igi2_frame.nNumPoints - 204.8 < 0.0 )
        v38 = 0.0;
      v3 = Game_ptGame;
      *(double *)igi2_frame.ptIntersection_88 = *(double *)igi2_frame.ptIntersection_88 * v38;
      *(double *)&igi2_frame.ptIntersection_88[8] = *(double *)&igi2_frame.ptIntersection_88[8] * v38;
      igi2_frame.ptIntersection_64.vX = *(double *)igi2_frame.ptIntersection_88 + *(double *)&igi2_frame.ptIntersection.tX.vX;
      igi2_frame.ptIntersection_64.vY = *(double *)&igi2_frame.ptIntersection_88[8] + *(double *)&igi2_frame.ptIntersection.tX.vZ;
      igi2_frame.ptIntersection_64.vZ = 1.0 / *(double *)igi2_frame.nNumPoints * (igi2_frame.v82.tPos.vZ - *(double *)&igi2_frame.ptIntersection.tY.vY) * v38
                           + *(double *)&igi2_frame.ptIntersection.tY.vY;
    }
    else
    {
      v3 = Game_ptGame;
      qmemcpy(&igi2_frame.ptIntersection_64, igi2_frame.ptIntersection_88, sizeof(igi2_frame.ptIntersection_64));
    }
  }
  v39 = BYTE1(ptHumanViewQTask[10].ptNext);
  qmemcpy(&ptHumanViewQTask[10].tQTaskChildren, &igi2_frame.ptIntersection_64, 0x18u);
  if ( v39 )
  {
    v40 = (*(float *)&ptHumanViewQTask[10].ptParent + *(float *)&ptHumanViewQTask[11].ptNext) * 0.0;
    v41 = *(float *)&ptHumanViewQTask[10].eQTaskType * 2048.0;
    qmemcpy(igi2_frame.ptIntersection_88, &igi2_frame.ptIntersection_64, 0x18u);
    v42 = v40 + v41;
    v43 = (*(float *)&ptHumanViewQTask[11].tQTaskChildren.ptMiddle + *(float *)&ptHumanViewQTask[11].ptPrev) * 0.0
        + *(float *)&ptHumanViewQTask[11].tQTaskChildren.ptHead * 2048.0;
    v44 = *(float *)&ptHumanViewQTask[11].tQTaskRefList.ptMiddle + *(float *)&ptHumanViewQTask[11].tQTaskChildren.ptTail;
    igi2_frame.nNumPoints[1] = (int)ptHumanQTask;
    igi2_frame.v73 = v44 * 0.0 + *(float *)&ptHumanViewQTask[11].tQTaskRefList.ptHead * 2048.0;
    *(double *)&igi2_frame.ptIntersection.tX.vX = v42 + igi2_frame.ptIntersection_64.vX;
    *(double *)&igi2_frame.ptIntersection.tX.vZ = v43 + igi2_frame.ptIntersection_64.vY;
    *(double *)&igi2_frame.ptIntersection.tY.vY = igi2_frame.v73 + igi2_frame.ptIntersection_64.vZ;
    World_TraceLines(
      v3->ptWorld,
      &igi2_frame.v82,
      (struct real64x3_t *)igi2_frame.ptIntersection_88,
      (struct real64x3_t *)&igi2_frame.ptIntersection,
      1,
      GameFunctions_eObjectCollisionEvaluateQTaskEvent,
      (struct CollisionEvaluateContext_s *)igi2_frame.nNumPoints,
      0xFFFFFFFF);
    if ( igi2_frame.v82.isHit )
      *(float *)&ptHumanViewQTask[19].tQTaskChildren.ptMiddle = -(2048.0 - igi2_frame.v82.vDistance);
    else
      ptHumanViewQTask[19].tQTaskChildren.ptMiddle = nullptr;
    v46 = *(float *)&ptHumanViewQTask[19].tQTaskChildren.ptMiddle;
    v47 = v46 < 0.0;
    v48 = 0;
    v49 = v46 == 0.0;
    v45 = (char)(v47 | (v48 << 2) | (v49 << 6));
    v50 = v45;
    v52 = *(float *)&ptHumanViewQTask[19].tQTaskChildren.ptTail;
    if ( __SETP__(v50 & 0x44, 0) )
    {
      if ( v53 | v54 )
      {
        v57 = v52 + 113.77777862548828;
        *(float *)&ptHumanViewQTask[19].tQTaskChildren.ptTail = v57;
        if ( v57 > *(float *)&ptHumanViewQTask[19].tQTaskChildren.ptMiddle )
          ptHumanViewQTask[19].tQTaskChildren.ptTail = ptHumanViewQTask[19].tQTaskChildren.ptMiddle;
        goto LABEL_38;
      }
      if ( v52 > *(float *)&ptHumanViewQTask[19].tQTaskChildren.ptMiddle )
      {
        v58 = *(float *)&ptHumanViewQTask[19].tQTaskChildren.ptTail - 113.77777862548828;
        *(float *)&ptHumanViewQTask[19].tQTaskChildren.ptTail = v58;
        if ( v58 < *(float *)&ptHumanViewQTask[19].tQTaskChildren.ptMiddle )
LABEL_37:
          ptHumanViewQTask[19].tQTaskChildren.ptTail = ptHumanViewQTask[19].tQTaskChildren.ptMiddle;
      }
    }
    else
    {
      if ( !(v53 | v54) )
      {
        if ( v52 > *(float *)&ptHumanViewQTask[19].tQTaskChildren.ptMiddle )
        {
          v56 = *(float *)&ptHumanViewQTask[19].tQTaskChildren.ptTail - 75.85185241699219;
          *(float *)&ptHumanViewQTask[19].tQTaskChildren.ptTail = v56;
          if ( v56 < *(float *)&ptHumanViewQTask[19].tQTaskChildren.ptMiddle )
            ptHumanViewQTask[19].tQTaskChildren.ptTail = ptHumanViewQTask[19].tQTaskChildren.ptMiddle;
        }
        goto LABEL_38;
      }
      v55 = v52 + 75.85185241699219;
      *(float *)&ptHumanViewQTask[19].tQTaskChildren.ptTail = v55;
      if ( v55 > *(float *)&ptHumanViewQTask[19].tQTaskChildren.ptMiddle )
        goto LABEL_37;
    }
LABEL_38:
    v59 = *(float *)&ptHumanViewQTask[10].ptParent + *(float *)&ptHumanViewQTask[11].ptNext;
    igi2_frame.nNumPoints[1] = (int)ptHumanViewQTask[19].tQTaskChildren.ptTail;
    v3 = Game_ptGame;
    v60 = v59 * 0.0 + *(float *)&igi2_frame.nNumPoints[1] * *(float *)&ptHumanViewQTask[10].eQTaskType;
    v61 = (*(float *)&ptHumanViewQTask[11].tQTaskChildren.ptMiddle + *(float *)&ptHumanViewQTask[11].ptPrev) * 0.0
        + *(float *)&igi2_frame.nNumPoints[1] * *(float *)&ptHumanViewQTask[11].tQTaskChildren.ptHead;
    igi2_frame.v73 = (*(float *)&ptHumanViewQTask[11].tQTaskRefList.ptMiddle + *(float *)&ptHumanViewQTask[11].tQTaskChildren.ptTail)
        * 0.0
        + *(float *)&igi2_frame.nNumPoints[1] * *(float *)&ptHumanViewQTask[11].tQTaskRefList.ptHead;
    igi2_frame.ptIntersection_52 = v60;
    igi2_frame.ptIntersection_56 = v61;
    igi2_frame.ptIntersection_60 = igi2_frame.v73 + igi2_frame.ptIntersection_60;
  }
  if ( *(float *)&ptHumanViewQTask[15].tQTaskRefList.ptMiddle != *(float *)&ptHumanViewQTask[15].tQTaskRefList.ptTail
    || *(float *)&ptHumanViewQTask[15].eQTaskType != *(float *)&ptHumanViewQTask[16].ptNext )
  {
    if ( *(float *)&ptHumanViewQTask[15].tQTaskRefList.ptMiddle >= (double)*(float *)&ptHumanViewQTask[15].tQTaskRefList.ptTail )
    {
      if ( *(float *)&ptHumanViewQTask[15].tQTaskRefList.ptMiddle > (double)*(float *)&ptHumanViewQTask[15].tQTaskRefList.ptTail )
      {
        v63 = *(float *)&ptHumanViewQTask[15].tQTaskRefList.ptMiddle - *(float *)&ptHumanViewQTask[15].ptParent;
        *(float *)&ptHumanViewQTask[15].tQTaskRefList.ptMiddle = v63;
        if ( v63 < *(float *)&ptHumanViewQTask[15].tQTaskRefList.ptTail )
          ptHumanViewQTask[15].tQTaskRefList.ptMiddle = ptHumanViewQTask[15].tQTaskRefList.ptTail;
      }
    }
    else
    {
      v62 = *(float *)&ptHumanViewQTask[15].ptParent + *(float *)&ptHumanViewQTask[15].tQTaskRefList.ptMiddle;
      *(float *)&ptHumanViewQTask[15].tQTaskRefList.ptMiddle = v62;
      if ( v62 > *(float *)&ptHumanViewQTask[15].tQTaskRefList.ptTail )
        ptHumanViewQTask[15].tQTaskRefList.ptMiddle = ptHumanViewQTask[15].tQTaskRefList.ptTail;
    }
    if ( *(float *)&ptHumanViewQTask[15].eQTaskType >= (double)*(float *)&ptHumanViewQTask[16].ptNext )
    {
      if ( *(float *)&ptHumanViewQTask[15].eQTaskType > (double)*(float *)&ptHumanViewQTask[16].ptNext )
      {
        v65 = *(float *)&ptHumanViewQTask[15].eQTaskType - *(float *)&ptHumanViewQTask[16].ptPrev;
        *(float *)&ptHumanViewQTask[15].eQTaskType = v65;
        if ( v65 < *(float *)&ptHumanViewQTask[16].ptNext )
          *(_DWORD *)&ptHumanViewQTask[15].eQTaskType = ptHumanViewQTask[16].ptNext;
      }
    }
    else
    {
      v64 = *(float *)&ptHumanViewQTask[16].ptPrev + *(float *)&ptHumanViewQTask[15].eQTaskType;
      *(float *)&ptHumanViewQTask[15].eQTaskType = v64;
      if ( v64 > *(float *)&ptHumanViewQTask[16].ptNext )
        *(_DWORD *)&ptHumanViewQTask[15].eQTaskType = ptHumanViewQTask[16].ptNext;
    }
  }
  if ( BYTE1(ptHumanViewQTask[10].ptNext) )
  {
    Real32x9_Create(
      &igi2_frame.ptIntersection,
      *(float *)&ptHumanViewQTask[15].tQTaskRefList.ptMiddle,
      0.0,
      *(float *)&ptHumanViewQTask[15].eQTaskType);
    *(float *)igi2_frame.ptIntersection_88 = igi2_frame.ptIntersection.tZ.vX * *(float *)&ptHumanViewQTask[11].ptNext
                                + igi2_frame.ptIntersection.tY.vX * *(float *)&ptHumanViewQTask[10].eQTaskType
                                + igi2_frame.ptIntersection.tX.vX * *(float *)&ptHumanViewQTask[10].ptParent;
    *(float *)&igi2_frame.ptIntersection_88[4] = igi2_frame.ptIntersection.tZ.vY * *(float *)&ptHumanViewQTask[11].ptNext
                                    + igi2_frame.ptIntersection.tY.vY * *(float *)&ptHumanViewQTask[10].eQTaskType
                                    + igi2_frame.ptIntersection.tX.vY * *(float *)&ptHumanViewQTask[10].ptParent;
    *(float *)&igi2_frame.ptIntersection_88[8] = igi2_frame.ptIntersection.tZ.vZ * *(float *)&ptHumanViewQTask[11].ptNext
                                    + igi2_frame.ptIntersection.tY.vZ * *(float *)&ptHumanViewQTask[10].eQTaskType
                                    + igi2_frame.ptIntersection.tX.vZ * *(float *)&ptHumanViewQTask[10].ptParent;
    *(float *)&igi2_frame.ptIntersection_88[12] = igi2_frame.ptIntersection.tZ.vX * *(float *)&ptHumanViewQTask[11].tQTaskChildren.ptMiddle
                                     + igi2_frame.ptIntersection.tX.vX * *(float *)&ptHumanViewQTask[11].ptPrev
                                     + igi2_frame.ptIntersection.tY.vX * *(float *)&ptHumanViewQTask[11].tQTaskChildren.ptHead;
    *(float *)&igi2_frame.ptIntersection_88[16] = igi2_frame.ptIntersection.tZ.vY * *(float *)&ptHumanViewQTask[11].tQTaskChildren.ptMiddle
                                     + igi2_frame.ptIntersection.tX.vY * *(float *)&ptHumanViewQTask[11].ptPrev
                                     + igi2_frame.ptIntersection.tY.vY * *(float *)&ptHumanViewQTask[11].tQTaskChildren.ptHead;
    *(float *)&igi2_frame.ptIntersection_88[20] = igi2_frame.ptIntersection.tZ.vZ * *(float *)&ptHumanViewQTask[11].tQTaskChildren.ptMiddle
                                     + igi2_frame.ptIntersection.tX.vZ * *(float *)&ptHumanViewQTask[11].ptPrev
                                     + igi2_frame.ptIntersection.tY.vZ * *(float *)&ptHumanViewQTask[11].tQTaskChildren.ptHead;
    *(float *)&igi2_frame.ptIntersection_88[24] = igi2_frame.ptIntersection.tZ.vX * *(float *)&ptHumanViewQTask[11].tQTaskRefList.ptMiddle
                                     + igi2_frame.ptIntersection.tX.vX * *(float *)&ptHumanViewQTask[11].tQTaskChildren.ptTail
                                     + igi2_frame.ptIntersection.tY.vX * *(float *)&ptHumanViewQTask[11].tQTaskRefList.ptHead;
    v66 = igi2_frame.ptIntersection.tZ.vY * *(float *)&ptHumanViewQTask[11].tQTaskRefList.ptMiddle
        + igi2_frame.ptIntersection.tX.vY * *(float *)&ptHumanViewQTask[11].tQTaskChildren.ptTail;
    *(_DWORD *)&igi2_frame.ptIntersection_88[36] = (char *)&ptHumanViewQTask[11].tQTaskRefList.ptTail->ptNext
                                      + igi2_frame.ptIntersection.nOps
                                      + 1;
    *(float *)&igi2_frame.ptIntersection_88[28] = v66 + igi2_frame.ptIntersection.tY.vY * *(float *)&ptHumanViewQTask[11].tQTaskRefList.ptHead;
    *(float *)&igi2_frame.ptIntersection_88[32] = igi2_frame.ptIntersection.tZ.vZ * *(float *)&ptHumanViewQTask[11].tQTaskRefList.ptMiddle
                                     + igi2_frame.ptIntersection.tX.vZ * *(float *)&ptHumanViewQTask[11].tQTaskChildren.ptTail
                                     + igi2_frame.ptIntersection.tY.vZ * *(float *)&ptHumanViewQTask[11].tQTaskRefList.ptHead;
    qmemcpy(&ptHumanViewQTask[3].ptPrev, igi2_frame.ptIntersection_88, sizeof(struct QTask_s));
    if ( isUpdateAnim )
    {
      AnimController_Step(
        (struct AnimController_t *)ptHumanViewQTask[16].tQTaskRefList.ptTail,
        (int)ptHumanViewQTask[16].tQTaskRefList.ptTail[5].ptPrev
      + (unsigned int)ptHumanViewQTask[16].tQTaskRefList.ptTail[5].pxObject);
      v3 = Game_ptGame;
    }
    qmemcpy(&igi2_frame.ptIntersection_64, &ptHumanQTask[33].tQTaskChildren.ptTail[10].tQTaskChildren, sizeof(igi2_frame.ptIntersection_64));
    igi2_frame.ptIntersection_64.vX = igi2_frame.ptIntersection_52 + igi2_frame.ptIntersection_64.vX;
    igi2_frame.ptIntersection_64.vY = igi2_frame.ptIntersection_56 + igi2_frame.ptIntersection_64.vY;
    ptWorld = v3->ptWorld;
    igi2_frame.ptIntersection_64.vZ = igi2_frame.ptIntersection_60 + igi2_frame.ptIntersection_64.vZ;
    igi2_frame.ptDynCubeObj = sqrt(
                     *(float *)&ptHumanViewQTask[7].tQTaskChildren.ptTail
                   * *(float *)&ptHumanViewQTask[7].tQTaskChildren.ptTail
                   + *(float *)&ptHumanViewQTask[7].tQTaskRefList.ptHead
                   * *(float *)&ptHumanViewQTask[7].tQTaskRefList.ptHead
                   + *(float *)&ptHumanViewQTask[7].tQTaskRefList.ptMiddle
                   * *(float *)&ptHumanViewQTask[7].tQTaskRefList.ptMiddle)
                 + *(float *)&ptHumanViewQTask[8].ptNext;
    World_MoveDynCubeObjRadius(ptWorld, (struct DynCubeObj_s *)ptHumanViewQTask, &igi2_frame.ptIntersection_64, igi2_frame.ptDynCubeObj);
    ModelObj_UpdateAttachments((struct ModelObj_s *)ptHumanViewQTask);
  }
}

// source: j/0/human/humanview.c:1155  [anchor-callee]
void __cdecl HumanView_PopPosition(struct QTask_s *ptHumanViewQTask, struct QTask_s *ptHumanQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { float ptDynCubeObj; };
    struct { char igi2_o1[12]; struct real64x3_t tPos; };
    char igi2_extent[36];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  double v2; // st7
  double v3; // st6
  double v4; // st5

  if ( BYTE1(ptHumanViewQTask[10].ptNext) )
  {
    v2 = *(float *)&ptHumanViewQTask[7].tQTaskRefList.ptMiddle;
    v3 = *(float *)&ptHumanViewQTask[7].tQTaskRefList.ptHead;
    v4 = *(float *)&ptHumanViewQTask[7].tQTaskChildren.ptTail;
    qmemcpy(&igi2_frame.tPos, &ptHumanViewQTask[10].tQTaskChildren, sizeof(igi2_frame.tPos));
    igi2_frame.ptDynCubeObj = sqrt(v4 * v4 + v3 * v3 + v2 * v2) + *(float *)&ptHumanViewQTask[8].ptNext;
    World_MoveDynCubeObjRadius(Game_ptGame->ptWorld, (struct DynCubeObj_s *)ptHumanViewQTask, &igi2_frame.tPos, igi2_frame.ptDynCubeObj);
    ModelObj_UpdateAttachments((struct ModelObj_s *)ptHumanViewQTask);
  }
}

// source: j/0/human/humanview.c:1206  [size]
struct QTask_s *__cdecl HumanView_GetViewPosition(
        struct real64x3_t *ptPos,
        struct QTask_s *ptHumanViewQTask)
{
  qmemcpy(ptPos, &ptHumanViewQTask[10].tQTaskChildren, sizeof(struct real64x3_t));
  return ptHumanViewQTask;
}

// source: j/0/human/humanview.c:1223  [anchor-callee]
struct real64x3_t *__cdecl HumanView_GetOriginalViewPosition(
        struct real64x3_t *ptPos,
        struct QTask_s *ptHumanQTask)
{
  int v2; // edx
  int v3; // edx

  v2 = *(_DWORD *)&ptHumanQTask[32].eQTaskType;
  if ( v2 )
  {
    v3 = v2 - 1;
    if ( v3 )
    {
      if ( v3 == 1 )
      {
        ptPos->vZ = 1228.800048828125;
        ptPos->vX = *(double *)&ptHumanQTask[1].ptNext;
        ptPos->vY = *(double *)&ptHumanQTask[1].tQTaskChildren.ptHead;
        ptPos->vZ = *(double *)&ptHumanQTask[1].tQTaskChildren.ptTail + 1228.800048828125;
      }
    }
    else
    {
      ptPos->vZ = 4096.0;
      ptPos->vX = *(double *)&ptHumanQTask[1].ptNext;
      ptPos->vY = *(double *)&ptHumanQTask[1].tQTaskChildren.ptHead;
      ptPos->vZ = *(double *)&ptHumanQTask[1].tQTaskChildren.ptTail + 4096.0;
    }
  }
  else
  {
    ptPos->vZ = 6922.240234375;
    ptPos->vX = *(double *)&ptHumanQTask[1].ptNext;
    ptPos->vY = *(double *)&ptHumanQTask[1].tQTaskChildren.ptHead;
    ptPos->vZ = *(double *)&ptHumanQTask[1].tQTaskChildren.ptTail + 6922.240234375;
  }
  return ptPos;
}

// source: j/0/human/humanview.c:1274  [size]
struct QTask_s *__cdecl HumanView_GetViewOrientation(
        struct real32x9_t *ptOrientation,
        struct QTask_s *ptHumanViewQTask)
{
  qmemcpy(ptOrientation, &ptHumanViewQTask[10].ptParent, sizeof(struct real32x9_t));
  return ptHumanViewQTask;
}

// source: j/0/human/humanview.c:1291  [size]
struct QTask_s *__cdecl HumanView_GetViewDirection(
        struct real32x3_t *ptDirection,
        struct QTask_s *ptHumanViewQTask)
{
  struct QTask_s *result; // eax

  ptDirection->vX = *(float *)&ptHumanViewQTask[10].eQTaskType;
  LODWORD(ptDirection->vY) = ptHumanViewQTask[11].tQTaskChildren.ptHead;
  result = (struct QTask_s *)ptHumanViewQTask[11].tQTaskRefList.ptHead;
  LODWORD(ptDirection->vZ) = result;
  return result;
}

// source: j/0/human/humanview.c:1308  [anchor-mhash]
struct QTask_s *__cdecl HumanView_OverrideView(
        struct QTask_s *ptHumanViewQTask,
        struct real64x3_t *ptPos,
        struct real32x9_t *ptOrientation)
{
  BYTE2(ptHumanViewQTask[12].tQTaskRefList.ptTail) = 1;
  qmemcpy(&ptHumanViewQTask[12].ptParent, ptPos, 0x18u);
  qmemcpy(&ptHumanViewQTask[13].tQTaskChildren.ptTail, ptOrientation, sizeof(struct QTask_s));
  return ptHumanViewQTask;
}

// source: j/0/human/humanview.c:1331  [size]
struct QTask_s *__cdecl HumanView_ClearOverrideView(struct QTask_s *ptHumanViewQTask)
{
  BYTE2(ptHumanViewQTask[12].tQTaskRefList.ptTail) = 0;
  return ptHumanViewQTask;
}

// source: j/0/human/humanview.c:1351  [anchor-mhash]
struct QTask_s *__cdecl HumanView_ApplyShake(
        struct QTask_s *ptHumanViewQTask,
        float vShakeRange,
        float vShakeAngle,
        int vShakeTime)
{
  ptHumanViewQTask[15].ptNext = (struct QTask_s *)1065353216;
  *(float *)&ptHumanViewQTask[15].ptPrev = vShakeRange;
  *(float *)&ptHumanViewQTask[15].tQTaskChildren.ptHead = vShakeAngle;
  *(float *)&ptHumanViewQTask[15].tQTaskChildren.ptMiddle = 1.0 / (double)vShakeTime;
  return ptHumanViewQTask;
}

// source: j/0/human/humanview.c:1372  [size]
struct QTask_s *__cdecl HumanView_ApplyImpact(
        struct QTask_s *ptHumanViewQTask,
        float vImpactOffset)
{
  *(float *)&ptHumanViewQTask[15].tQTaskChildren.ptTail = vImpactOffset;
  ptHumanViewQTask[15].tQTaskRefList.ptHead = nullptr;
  return ptHumanViewQTask;
}

// source: j/0/human/humanview.c:1390  [size]
struct QTask_s *__cdecl HumanView_EnableZoomMode(struct QTask_s *ptHumanViewQTask)
{
  ptHumanViewQTask[16].tQTaskRefList.ptMiddle = (struct QReference_s *)1;
  return ptHumanViewQTask;
}

// source: j/0/human/humanview.c:1406  [anchor-callee]
struct QTask_s *__cdecl HumanView_DisableZoomMode(struct QTask_s *ptHumanViewQTask)
{
  ptHumanViewQTask[16].tQTaskRefList.ptMiddle = nullptr;
  *(float *)&ptHumanViewQTask[16].tQTaskChildren.ptHead = tan(0.7853981852531433);
  *(float *)&ptHumanViewQTask[16].tQTaskRefList.ptHead = tan(0.5235987901687622);
  return ptHumanViewQTask;
}

unsigned __int16 sub_4E1EB0()
{
  return HumanView_eQTaskType;
}

// source: j/0/human/humanview.c:1426  [anchor-strings]
void __cdecl HumanView_Open()
{
  unsigned __int16 v0; // si
  __int16 v1; // ax
  struct ParameterList_s *v2; // eax
  int v3; // edx

  v0 = QTask_NewQTaskType("HumanView", 784, BoneDynCubeObj_eQTaskType, 0, 0);
  HumanView_eQTaskType = v0;
  QTask_LinkQTaskEventHandlerFn(v0, 0, HumanView_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 1, HumanView_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 2, (void (__cdecl *)(struct QTask_s *))sub_4E0A40);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, Attach_eUpdateAttachmentEvent, nullptr);
  QTask_LinkQTaskEventHandlerFn(v0, 5, sub_4E0A60);
  QTask_LinkQTaskEventHandlerFn(v0, DynCubeObj_eDynCubeObjRemoveQTaskEvent, sub_4E0B20);
  QTask_LinkQTaskEventHandlerFn(v0, DynCubeObj_eDynCubeObjRegisterQTaskEvent, sub_4E0BB0);
  QTask_LinkQTaskEventHandlerFn(v0, 8, nullptr);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    GameFunctions_eWeaponCollisionEvaluateQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))sub_4E0C40);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    GameFunctions_eObjectCollisionEvaluateQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))HumanView_WeaponCollisionEvaluateHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    GameFunctions_eGetNextZEvaluateQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))HumanView_ObjectCollisionEvaluateHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    AIDetection_eLineOfSightQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))sub_4E0C70);
  v1 = SoundSys_eUpdateParameterListQTaskEvent;
  if ( SoundSys_eUpdateParameterListQTaskEvent == 512 )
  {
    v1 = QTask_NewQTaskEventFn(0, (char *)&g_zFileName.nRealFadeCount);
    v0 = HumanView_eQTaskType;
    SoundSys_eUpdateParameterListQTaskEvent = v1;
  }
  QTask_LinkQTaskEventHandlerFn(v0, v1, (void (__cdecl *)(struct QTask_s *, void *))sub_4E0CA0);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    Serialize_eGetSerializeParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))HumanView_GetSerializeParameterListHandler);
  v2 = (struct ParameterList_s *)Mem_AllocFn(732, 4);
  v3 = Level_eParameterTypebool8;
  v2->ptParameterListItem = (struct ParameterListItem_s *)&v2[1];
  v2->nParameters = 0;
  v2->nMaxParameters = 36;
  HumanView_ptSerializeParameterList = v2;
  ParameterList_AddParameter(v2, 0x190u, v3, "isObjectEnabled", 7u, nullptr);
  ParameterList_AddParameter(
    HumanView_ptSerializeParameterList,
    0x191u,
    Level_eParameterTypebool8,
    "isObjectRegistered",
    7u,
    nullptr);
  ParameterList_AddParameter(
    HumanView_ptSerializeParameterList,
    0x198u,
    Level_eParameterTypeReal64x3,
    "tPos",
    7u,
    nullptr);
  ParameterList_AddParameter(
    HumanView_ptSerializeParameterList,
    0x1B0u,
    Level_eParameterTypeReal32x9,
    "tOrientation",
    7u,
    nullptr);
  ParameterList_AddParameter(
    HumanView_ptSerializeParameterList,
    0x1DCu,
    Level_eParameterTypeReal32,
    "vViewAlpha",
    7u,
    nullptr);
  ParameterList_AddParameter(
    HumanView_ptSerializeParameterList,
    0x1E0u,
    Level_eParameterTypeReal32,
    "vIdealViewAlpha",
    7u,
    nullptr);
  ParameterList_AddParameter(
    HumanView_ptSerializeParameterList,
    0x1E4u,
    Level_eParameterTypeReal32,
    "vOffsetViewAlpha",
    7u,
    nullptr);
  ParameterList_AddParameter(
    HumanView_ptSerializeParameterList,
    0x1E8u,
    Level_eParameterTypeReal32,
    "vViewGamma",
    7u,
    nullptr);
  ParameterList_AddParameter(
    HumanView_ptSerializeParameterList,
    0x1ECu,
    Level_eParameterTypeReal32,
    "vIdealViewGamma",
    7u,
    nullptr);
  ParameterList_AddParameter(
    HumanView_ptSerializeParameterList,
    0x1F0u,
    Level_eParameterTypeReal32,
    "vOffsetViewGamma",
    7u,
    nullptr);
  ParameterList_AddParameter(
    HumanView_ptSerializeParameterList,
    0x1FCu,
    Level_eParameterTypebool8,
    "isLockOrientation",
    7u,
    nullptr);
  ParameterList_AddParameter(
    HumanView_ptSerializeParameterList,
    0x1FDu,
    Level_eParameterTypebool8,
    "isCropOffset",
    7u,
    nullptr);
  ParameterList_AddParameter(
    HumanView_ptSerializeParameterList,
    0x1FEu,
    Level_eParameterTypebool8,
    "isOverride",
    7u,
    nullptr);
  ParameterList_AddParameter(
    HumanView_ptSerializeParameterList,
    0x200u,
    Level_eParameterTypeReal64x3,
    "tOverridePos",
    7u,
    nullptr);
  ParameterList_AddParameter(
    HumanView_ptSerializeParameterList,
    0x240u,
    Level_eParameterTypeReal32x3,
    "tPeekOffset",
    7u,
    nullptr);
  ParameterList_AddParameter(
    HumanView_ptSerializeParameterList,
    0x24Cu,
    Level_eParameterTypeReal32x3,
    "tPeekSpeed",
    7u,
    nullptr);
  ParameterList_AddParameter(
    HumanView_ptSerializeParameterList,
    0x258u,
    Level_eParameterTypeReal32,
    "vShakeFactor",
    7u,
    nullptr);
  ParameterList_AddParameter(
    HumanView_ptSerializeParameterList,
    0x25Cu,
    Level_eParameterTypeReal32,
    "vShakeRange",
    7u,
    nullptr);
  ParameterList_AddParameter(
    HumanView_ptSerializeParameterList,
    0x260u,
    Level_eParameterTypeReal32,
    "vShakeAngle",
    7u,
    nullptr);
  ParameterList_AddParameter(
    HumanView_ptSerializeParameterList,
    0x264u,
    Level_eParameterTypeReal32,
    "vShakeTime",
    7u,
    nullptr);
  ParameterList_AddParameter(
    HumanView_ptSerializeParameterList,
    0x268u,
    Level_eParameterTypeReal32,
    "vImpactOffset",
    7u,
    nullptr);
  ParameterList_AddParameter(
    HumanView_ptSerializeParameterList,
    0x26Cu,
    Level_eParameterTypeReal32,
    "vImpactAngle",
    7u,
    nullptr);
  ParameterList_AddParameter(
    HumanView_ptSerializeParameterList,
    0x270u,
    Level_eParameterTypeReal32,
    "vObjectAlpha",
    7u,
    nullptr);
  ParameterList_AddParameter(
    HumanView_ptSerializeParameterList,
    0x274u,
    Level_eParameterTypeReal32,
    "vIdealObjectAlpha",
    7u,
    nullptr);
  ParameterList_AddParameter(
    HumanView_ptSerializeParameterList,
    0x278u,
    Level_eParameterTypeReal32,
    "vStepAlpha",
    7u,
    nullptr);
  ParameterList_AddParameter(
    HumanView_ptSerializeParameterList,
    0x27Cu,
    Level_eParameterTypeReal32,
    "vObjectGamma",
    7u,
    nullptr);
  ParameterList_AddParameter(
    HumanView_ptSerializeParameterList,
    0x280u,
    Level_eParameterTypeReal32,
    "vIdealObjectGamma",
    7u,
    nullptr);
  ParameterList_AddParameter(
    HumanView_ptSerializeParameterList,
    0x284u,
    Level_eParameterTypeReal32,
    "vStepGamma",
    7u,
    nullptr);
  ParameterList_AddParameter(
    HumanView_ptSerializeParameterList,
    0x288u,
    Level_eParameterTypeReal32,
    "vFOV",
    7u,
    nullptr);
  ParameterList_AddParameter(
    HumanView_ptSerializeParameterList,
    0x294u,
    Level_eParameterTypeReal32,
    "vObjectFOV",
    7u,
    nullptr);
  ParameterList_AddParameter(
    HumanView_ptSerializeParameterList,
    0x298u,
    Level_eParameterTypebool8,
    "isZoomMode",
    7u,
    nullptr);
  ParameterList_AddParameter(
    HumanView_ptSerializeParameterList,
    0x2A0u,
    Level_eParameterTypeReal32x3,
    "tTranslation",
    7u,
    nullptr);
  ParameterList_AddParameter(
    HumanView_ptSerializeParameterList,
    0x2ACu,
    Level_eParameterTypeReal32x3,
    "tDeltaTranslation",
    7u,
    nullptr);
  ParameterList_AddParameter(
    HumanView_ptSerializeParameterList,
    0x304u,
    Level_eParameterTypeReal32,
    (char *)&stru_6908E0.eQTaskType,
    7u,
    nullptr);
  ParameterList_AddParameter(
    HumanView_ptSerializeParameterList,
    0x308u,
    Level_eParameterTypeReal32,
    (char *)&stru_6908E0.tQTaskRefList,
    7u,
    nullptr);
}

// source: j/0/human/humanview.c:1495  [size]
void __cdecl HumanView_Close()
{
  int v0; // esi

  QTask_DeleteQTaskType(HumanView_eQTaskType);
  if ( HumanView_ptSerializeParameterList )
  {
    v0 = *(_DWORD *)((unsigned int)&HumanView_ptSerializeParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
}
