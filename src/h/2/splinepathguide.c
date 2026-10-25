/* h/2/splinepathguide.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: h/2/splinepathguide.c:102  [anchor-mhash]
struct Result_s *__cdecl SplinePathGuideQTask_SetRunningScriptFunction(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  struct SplinePathGuideQTask_s *v3; // esi
  unsigned int v4; // eax
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  v3 = SplinePathGuideQTask_ptSplinePathGuideQTask;
  if ( SplinePathGuideQTask_ptSplinePathGuideQTask )
  {
    if ( ptArgList->nArguments <= 0 || Script_EvalArgInt(ptArgList, 0) )
      v4 = v3->bFlags | 1;
    else
      v4 = v3->bFlags & 0xFFFFFFFE;
    v3->bFlags = v4;
  }
  Rs.nResult = 0;
  Rs.vResult = 0.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: h/2/splinepathguide.c:138  [size]
void __cdecl SplinePathGuideQTask_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  bool v2; // c0
  bool v3; // c3
  double v4; // st7
  struct QTask_s *ptMiddle; // eax
  struct QTask_s *v6; // eax
  double v7; // st7
  double v8; // st7
  struct QTask_s *ptPrev; // eax
  struct QReference_s *v10; // eax
  _WORD *pxObject; // edx
  unsigned __int16 v12; // si
  void *pfHandler; // eax

  v2 = *(float *)&ptQTask[2].tQTaskChildren.ptTail > 0.0;
  v3 = 0.0 == *(float *)&ptQTask[2].tQTaskChildren.ptTail;
  SplinePath_isDisplay = false;
  if ( v2 || v3 )
  {
    if ( *(float *)&ptQTask[2].tQTaskChildren.ptTail <= 1.0 )
      v4 = *(float *)&ptQTask[2].tQTaskChildren.ptTail;
    else
      v4 = 1.0;
  }
  else
  {
    v4 = 0.0;
  }
  *(float *)&ptQTask[2].tQTaskChildren.ptTail = v4;
  if ( v4 > 0.0 )
    SplinePathGuideQTask_PlaceAtStartPosition(ptQTask);
  ptMiddle = ptQTask[1].tQTaskChildren.ptMiddle;
  if ( ptQTask[1].tQTaskRefList.ptHead )
    v6 = (struct QTask_s *)((unsigned int)ptMiddle | 1);
  else
    v6 = (struct QTask_s *)((unsigned int)ptMiddle & 0xFFFFFFFE);
  v7 = *(float *)&ptQTask[2].tQTaskChildren.ptMiddle;
  ptQTask[1].tQTaskChildren.ptMiddle = v6;
  if ( v7 <= 0.0 )
    v8 = 0.0;
  else
    v8 = *(float *)&ptQTask[2].tQTaskChildren.ptMiddle;
  ptPrev = ptQTask[1].ptPrev;
  *(float *)&ptQTask[2].tQTaskChildren.ptMiddle = v8;
  *(double *)&ptQTask[1].ptParent = v8;
  if ( (int)ptPrev > 0 && (int)ptPrev < 4096 )
  {
    v10 = Level_atLevelQTaskID[(_DWORD)ptPrev];
    if ( v10 )
    {
      pxObject = v10->pxObject;
      if ( pxObject )
      {
        v12 = pxObject[18];
        if ( QTask_IsQTaskTypeDerived(v12, ModelObj_eQTaskType) )
        {
          pfHandler = QTask_aatQTaskFinalEvent[SplinePathGuideQTask_eConnectedToGuideEvent][v12].pfHandler;
          if ( pfHandler )
            ((void (__cdecl *)(_WORD *, _DWORD))pfHandler)(pxObject, 0);
        }
        else
        {
          ptQTask[1].ptPrev = (struct QTask_s *)-1;
        }
      }
    }
  }
}

// source: h/2/splinepathguide.c:194  [size]
void __cdecl SplinePathGuideQTask_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = SplinePathGuideQTask_ptParameterList;
}

// source: h/2/splinepathguide.c:211  [size]
void __cdecl SplinePathGuideQTask_GetSerializeParameterListHandler(
        struct QTask_s *ptQTask,
        void *pxContext)
{
  *(_DWORD *)pxContext = SplinePathGuideQTask_ptSerializeParameterList;
}

// source: h/2/splinepathguide.c:230  [size]
void __cdecl SplinePathGuideQTask_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ptQTask[1].ptNext = (struct QTask_s *)-1;
  ptQTask[1].ptPrev = (struct QTask_s *)-1;
  ptQTask[1].tQTaskChildren.ptHead = nullptr;
  ptQTask[1].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[2].tQTaskChildren.ptHead = nullptr;
  ptQTask[2].tQTaskChildren.ptMiddle = (struct QTask_s *)1065353216;
  ptQTask[1].ptParent = nullptr;
  *(_DWORD *)&ptQTask[1].eQTaskType = 1072693248;
  ptQTask[2].tQTaskChildren.ptTail = nullptr;
  ptQTask[2].ptNext = nullptr;
  ptQTask[2].ptPrev = nullptr;
  ptQTask[1].tQTaskChildren.ptTail = nullptr;
  ptQTask[1].tQTaskRefList.ptHead = nullptr;
  ptQTask[1].tQTaskRefList.ptMiddle = nullptr;
  QTaskList_Register(SplinePathGuideQTask_ptTaskList, (struct QTaskList_s *)ptQTask);
}

// source: h/2/splinepathguide.c:260  [anchor-mhash]
void __cdecl SplinePathGuideQTask_DeleteHandler(struct QTask_s *ptQTask)
{
  int v1; // eax
  struct QReference_s *v2; // ecx
  void (__cdecl *pfHandler)(struct QTask_s *); // eax

  QTaskList_Remove(SplinePathGuideQTask_ptTaskList, ptQTask);
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
      return;
  }
  if ( v1 >= 0 )
  {
    pfHandler = (void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[Level_eRemoveLevelScriptSymbolsEvent][ptQTask->eQTaskType].pfHandler;
    if ( pfHandler )
      pfHandler(ptQTask);
  }
}

// source: h/2/splinepathguide.c:279  [anchor-caller]
void __cdecl SplinePathGuideQTask_RunHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { float v20; };
    struct { char igi2_o1[20]; int nPathNumNodes; };
    struct { char igi2_o2[24]; struct QTask_s *v22; };
    struct { char igi2_o3[24]; struct QTask_s *v23; };
    struct { char igi2_o4[28]; struct real32x3_t tVelocity; };
    struct { char igi2_o5[40]; struct real64x3_t tReal64x3; };
    struct { char igi2_o6[64]; int ltcg_eax[6]; };
    char igi2_extent[88];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *ptHead; // eax
  bool v3; // zf
  int v4; // edx
  struct QTask_s *v5; // ecx
  int eQTaskType; // ecx
  struct QTask_s *ptMiddle; // eax
  struct QTask_s *ptNext; // eax
  struct QReference_s *v9; // eax
  struct QTask_s *pxObject; // edi
  struct QTask_s *ptPrev; // eax
  struct QTask_s *QTaskFromLevelQTaskID; // eax
  struct ModelObj_s *v13; // ebx
  struct QTask_s *v14; // ebp
  int v15; // ecx
  int v16; // edx
  double v17; // st7
  double v18; // st7
  void (__cdecl *pfHandler)(struct ModelObj_s *, struct real32x3_t *); // eax
  float ptQTaskb = *(float *)&ptQTask; // [esp+5Ch] [ebp+4h] ARGSLOT
  struct QTask_s *ptQTaska = *(struct QTask_s * *)&ptQTask; // [esp+5Ch] [ebp+4h] ARGSLOT

  ptHead = ptQTask->tQTaskChildren.ptHead;
  *(float *)&ptQTask[2].tQTaskChildren.ptMiddle = *(double *)&ptQTask[1].ptParent;
  v3 = ptHead->ptNext == nullptr;
  SplinePathGuideQTask_ptSplinePathGuideQTask = (struct SplinePathGuideQTask_s *)ptQTask;
  if ( !v3 && ptHead )
  {
    v4 = QTask_nProtectedQTaskStackOffset;
    do
    {
      if ( ptHead->ptNext )
        v5 = ptHead->ptNext->ptNext != nullptr ? ptHead->ptNext : nullptr;
      else
        v5 = nullptr;
      QTask_atProtectedQTaskStack[v4].ptQTask = v5;
      eQTaskType = ptHead->eQTaskType;
      QTask_nProtectedQTaskStackOffset = v4 + 1;
      ((void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[1][eQTaskType].pfHandler)(ptHead);
      ptHead = (struct QTask_s *)dword_849C7DC[QTask_nProtectedQTaskStackOffset];
      v4 = --QTask_nProtectedQTaskStackOffset;
    }
    while ( ptHead );
  }
  ptMiddle = ptQTask[1].tQTaskChildren.ptMiddle;
  SplinePathGuideQTask_ptSplinePathGuideQTask = nullptr;
  igi2_frame.v22 = ptMiddle;
  if ( ((unsigned __int8)ptMiddle & 1) != 0 )
  {
    ptNext = ptQTask[1].ptNext;
    if ( (unsigned int)ptNext < 0x1000 )
    {
      v9 = Level_atLevelQTaskID[(_DWORD)ptNext];
      if ( v9 )
      {
        pxObject = (struct QTask_s *)v9->pxObject;
        if ( pxObject )
        {
          if ( QTask_IsQTaskTypeDerived(pxObject->eQTaskType, SplinePathDynCubeObj_eQTaskType) )
          {
            ptPrev = ptQTask[1].ptPrev;
            if ( (int)ptPrev >= 0 )
            {
              QTaskFromLevelQTaskID = Level_GetQTaskFromLevelQTaskID((int)ptPrev);
              v13 = (struct ModelObj_s *)QTaskFromLevelQTaskID;
              if ( QTaskFromLevelQTaskID )
              {
                if ( QTask_IsQTaskTypeDerived(QTaskFromLevelQTaskID->eQTaskType, ModelObj_eQTaskType) )
                {
                  v14 = ptQTask[1].tQTaskChildren.ptHead;
                  v15 = *((_DWORD *)&pxObject[2].ptParent + (_DWORD)v14);
                  if ( v15 )
                  {
                    v16 = *((_DWORD *)&pxObject[2].eQTaskType + (_DWORD)v14);
                    if ( v16 )
                    {
                      igi2_frame.nPathNumNodes = (int)pxObject[12].ptParent;
                      if ( igi2_frame.nPathNumNodes >= 3 )
                      {
                        ptQTaskb = *(float *)(v15 + 152);
                        v17 = SplinePathNodeQTask_GetEstimatedTPerMeter(
                                (struct QTask_s *)v15,
                                *(float *)&ptQTask[2].tQTaskChildren.ptHead)
                            * (4096000.0
                             / (SplinePath_vFlowFrequency
                              * 3600.0)
                             * ((*(float *)(v16 + 152) - ptQTaskb) * *(float *)&ptQTask[2].tQTaskChildren.ptHead
                              + ptQTaskb)
                             * *(float *)&ptQTask[2].tQTaskChildren.ptMiddle)
                            + *(float *)&ptQTask[2].tQTaskChildren.ptHead;
                        *(float *)&ptQTask[2].tQTaskChildren.ptHead = v17;
                        if ( v17 > 1.0 )
                        {
                          *(float *)&ptQTask[2].tQTaskChildren.ptHead = v17 - 1.0;
                          v18 = *(float *)(v15 + 160);
                          ptQTask[1].tQTaskChildren.ptHead = (struct QTask_s *)((char *)&v14->ptNext + 1);
                          *(float *)&ptQTask[2].tQTaskChildren.ptHead = v18
                                                                      * *(float *)&ptQTask[2].tQTaskChildren.ptHead
                                                                      / *(float *)(v16 + 160);
                          if ( (int)&v14->ptNext + 1 >= igi2_frame.nPathNumNodes - 1 )
                          {
                            if ( ptQTask[1].tQTaskChildren.ptTail )
                            {
                              ptQTask[2].tQTaskChildren.ptHead = nullptr;
                              ptQTask[1].tQTaskChildren.ptHead = nullptr;
                            }
                            else
                            {
                              ptQTask[2].tQTaskChildren.ptHead = (struct QTask_s *)1065353216;
                              ptQTask[1].tQTaskChildren.ptHead = (struct QTask_s *)(igi2_frame.nPathNumNodes - 2);
                              ptQTask[1].tQTaskChildren.ptMiddle = (struct QTask_s *)((unsigned int)igi2_frame.v22 & 0xFFFFFFFE);
                            }
                          }
                        }
                        if ( *(float *)&ptQTask[2].tQTaskChildren.ptHead >= 1.0 )
                          *(float *)&ptQTaska = 1.0;
                        else
                          ptQTaska = ptQTask[2].tQTaskChildren.ptHead;
                        igi2_frame.v23 = ptQTask[1].tQTaskChildren.ptHead;
                        *(double *)&ptQTask[2].ptNext = (double)(int)igi2_frame.v23 + *(float *)&ptQTaska;
                        ptQTask[2].tQTaskChildren.ptHead = ptQTaska;
                        SplinePathDynCubeObj_GetInterpolatedOrientation(
                          pxObject,
                          &v13->tOrientation,
                          (int)igi2_frame.v23,
                          *(float *)&ptQTaska);
                        qmemcpy(
                          &igi2_frame.tReal64x3,
                          SplinePathDynCubeObj_GetInterpolatedPosition(
                            (struct real64x3_t *)ptQTask[2].tQTaskChildren.ptHead,
                            pxObject,
                            (int)ptQTask[1].tQTaskChildren.ptHead,
                            igi2_frame.v20,
                            (int)igi2_frame.ltcg_eax),
                          sizeof(igi2_frame.tReal64x3));
                        igi2_frame.tVelocity.vX = igi2_frame.tReal64x3.vX - v13->tDynCubeObj.tQObj.tPos.vX;
                        igi2_frame.tVelocity.vY = igi2_frame.tReal64x3.vY - v13->tDynCubeObj.tQObj.tPos.vY;
                        igi2_frame.tVelocity.vZ = igi2_frame.tReal64x3.vZ - v13->tDynCubeObj.tQObj.tPos.vZ;
                        World_MoveDynCubeObjRadius(
                          World_ptActiveWorld,
                          &v13->tDynCubeObj,
                          &igi2_frame.tReal64x3,
                          v13->tDynCubeObj.tQObj.vRealRadius);
                        pfHandler = (void (__cdecl *)(struct ModelObj_s *, struct real32x3_t *))QTask_aatQTaskFinalEvent[SplinePathGuideQTask_ePositionChangedEvent][v13->tDynCubeObj.tQObj.tQTask.eQTaskType].pfHandler;
                        if ( pfHandler )
                          pfHandler(v13, &igi2_frame.tVelocity);
                        ModelObj_UpdateAttachments(v13);
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
}

// source: h/2/splinepathguide.c:434  [size]
void __cdecl SplinePathGuideQTask_RegisterScriptSymbolsHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { char zName[64]; };
    struct { char igi2_o1[64]; char zTemp[128]; };
    char igi2_extent[192];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)

  if ( !ptQTask[1].tQTaskRefList.ptMiddle )
  {
    ptQTask[1].tQTaskRefList.ptMiddle = (struct QReference_s *)1;
    Level_GetUniqueQTaskNameFromTask(igi2_frame.zName, ptQTask);
    sprintf(igi2_frame.zTemp, "%s.vPosition", igi2_frame.zName);
    Symbol_Register(
      igi2_frame.zTemp,
      Script_Float,
      &ptQTask[2],
      8,
      QSCRIPT_SYMBOLCLASS_VARIABLE,
      QSCRIPT_SYMBOLTYPE_FLOAT,
      QSCRIPT_SYMBOLLIFESPAN_FINITE);
    sprintf(igi2_frame.zTemp, "%s.vSpeed", igi2_frame.zName);
    Symbol_Register(
      igi2_frame.zTemp,
      Script_Float,
      &ptQTask[1].ptParent,
      8,
      QSCRIPT_SYMBOLCLASS_VARIABLE,
      QSCRIPT_SYMBOLTYPE_FLOAT,
      QSCRIPT_SYMBOLLIFESPAN_FINITE);
  }
}

// source: h/2/splinepathguide.c:465  [size]
void __cdecl SplinePathGuideQTask_RemoveScriptSymbolsHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { char zName[64]; };
    struct { char igi2_o1[64]; char zTemp[128]; };
    char igi2_extent[192];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)

  if ( ptQTask[1].tQTaskRefList.ptMiddle )
  {
    ptQTask[1].tQTaskRefList.ptMiddle = nullptr;
    Level_GetUniqueQTaskNameFromTask(igi2_frame.zName, ptQTask);
    sprintf(igi2_frame.zTemp, "%s.vPosition", igi2_frame.zName);
    Symbol_Remove(igi2_frame.zTemp);
    sprintf(igi2_frame.zTemp, "%s.vSpeed", igi2_frame.zName);
    Symbol_Remove(igi2_frame.zTemp);
  }
}

// source: h/2/splinepathguide.c:497  [size]
// attributes: thunk
void __cdecl SplinePathGuideQTask_SerializeHandler(struct QTask_s *ptQTask, void *pxContext)
{
  Serialize_SerializeHandler(ptQTask, pxContext);
}

// source: h/2/splinepathguide.c:510  [anchor-mhash]
void __cdecl SplinePathGuideQTask_DeSerializeHandler(struct QTask_s *ptQTask, void *pxContext)
{
  Serialize_DeSerializeHandler(ptQTask, pxContext);
  *(double *)&ptQTask[2].ptNext = (double)(int)ptQTask[1].tQTaskChildren.ptHead
                                + *(float *)&ptQTask[2].tQTaskChildren.ptHead;
}

// source: h/2/splinepathguide.c:529  [size]
struct QTask_s *__cdecl SplinePathGuideQTask_SetScale(
        struct QTask_s *ptQTask,
        float vScale)
{
  *(double *)&ptQTask[1].ptParent = vScale;
  *(float *)&ptQTask[2].tQTaskChildren.ptMiddle = vScale;
  return ptQTask;
}

// source: h/2/splinepathguide.c:547  [anchor-callee]
void __cdecl SplinePathGuideQTask_PlaceAtStartPosition(struct QTask_s *ptQTask)
{
  struct QTask_s *ptNext; // eax
  struct QReference_s *v2; // eax
  char *pxObject; // esi
  int v4; // eax
  double v5; // st7
  int v6; // edx
  char *v7; // eax
  int v8; // ecx
  double v9; // st7
  struct QTask_s *v10; // ecx
  char *i; // esi
  double v12; // st6
  double v13; // st7

  ptNext = ptQTask[1].ptNext;
  if ( (unsigned int)ptNext < 0x1000 )
  {
    v2 = Level_atLevelQTaskID[(_DWORD)ptNext];
    if ( v2 )
    {
      pxObject = (char *)v2->pxObject;
      if ( pxObject )
      {
        if ( QTask_IsQTaskTypeDerived(*((_WORD *)pxObject + 18), SplinePathDynCubeObj_eQTaskType) )
        {
          v4 = *((_DWORD *)pxObject + 128);
          if ( v4 >= 3 )
          {
            v5 = 0.0;
            v6 = v4 - 1;
            v7 = pxObject + 112;
            v8 = v6;
            do
            {
              v5 = v5 + *(float *)(*(_DWORD *)v7 + 160);
              v7 += 4;
              --v8;
            }
            while ( v8 );
            v9 = v5 * *(float *)&ptQTask[2].tQTaskChildren.ptTail;
            v10 = nullptr;
            if ( v6 > 0 )
            {
              for ( i = pxObject + 112; ; i += 4 )
              {
                v12 = *(float *)(*(_DWORD *)i + 160);
                if ( v9 <= v12 )
                  break;
                v10 = (struct QTask_s *)((char *)v10 + 1);
                v9 = v9 - v12;
                if ( (int)v10 >= v6 )
                  return;
              }
              v13 = v9 / v12;
              ptQTask[1].tQTaskChildren.ptHead = v10;
              *(float *)&ptQTask[2].tQTaskChildren.ptHead = v13;
              *(double *)&ptQTask[2].ptNext = (double)(int)v10 + v13;
            }
          }
        }
      }
    }
  }
}

// source: h/2/splinepathguide.c:630  [size]
__int16 __cdecl SplinePathGuideQTask_GetPositionChangedEvent()
{
  return SplinePathGuideQTask_ePositionChangedEvent;
}

// source: h/2/splinepathguide.c:644  [size]
__int16 __cdecl SplinePathGuideQTask_ConnectedToGuideEvent()
{
  return SplinePathGuideQTask_eConnectedToGuideEvent;
}

// source: h/2/splinepathguide.c:658  [anchor-hash]
void __cdecl SplinePathGuideQTask_RestartRunningGuides()
{
  struct QTaskList_s *v0; // ebx
  int v1; // ebp
  struct QTask_s **ptQTask; // esi

  v0 = SplinePathGuideQTask_ptTaskList;
  v1 = 0;
  if ( SplinePathGuideQTask_ptTaskList->nTask > 0 )
  {
    ptQTask = SplinePathGuideQTask_ptTaskList->ptQTask;
    do
    {
      if ( ((int)(*ptQTask)[1].tQTaskChildren.ptMiddle & 1) != 0 )
        SplinePathGuideQTask_PlaceAtStartPosition(*ptQTask);
      ++v1;
      ++ptQTask;
    }
    while ( v1 < v0->nTask );
  }
}

// source: h/2/splinepathguide.c:691  [size]
void __cdecl SplinePathGuideQTask_NotifyGuidedObjects()
{
  struct QTaskList_s *v0; // edx
  int v1; // edi
  int v2; // esi
  int v3; // eax
  struct QReference_s *v4; // eax
  unsigned __int16 *pxObject; // eax
  void (__cdecl *pfHandler)(unsigned __int16 *, _DWORD); // ecx

  v0 = SplinePathGuideQTask_ptTaskList;
  v1 = 0;
  if ( SplinePathGuideQTask_ptTaskList->nTask > 0 )
  {
    v2 = 8;
    do
    {
      v3 = *(_DWORD *)(*(int *)((char *)&v0->nTask + v2) + 44);
      if ( v3 > 0 && v3 < 4096 )
      {
        v4 = Level_atLevelQTaskID[v3];
        if ( v4 )
        {
          pxObject = (unsigned __int16 *)v4->pxObject;
          if ( pxObject )
          {
            pfHandler = (void (__cdecl *)(unsigned __int16 *, _DWORD))QTask_aatQTaskFinalEvent[SplinePathGuideQTask_eConnectedToGuideEvent][pxObject[18]].pfHandler;
            if ( pfHandler )
            {
              pfHandler(pxObject, 0);
              v0 = SplinePathGuideQTask_ptTaskList;
            }
          }
        }
      }
      ++v1;
      v2 += 4;
    }
    while ( v1 < v0->nTask );
  }
}

// source: h/2/splinepathguide.c:734  [anchor-callee]
void __cdecl SplinePathGuideQTask_Open()
{
  unsigned __int16 BaseQTaskType; // ax
  __int16 v1; // ax
  unsigned __int16 v2; // si
  struct ParameterList_s *v3; // eax
  unsigned __int16 v4; // si
  struct ParameterList_s *v5; // eax

  BaseQTaskType = QTask_GetBaseQTaskType();
  SplinePathGuideQTask_eQTaskType = QTask_NewQTaskType("SplinePathGuideQTask", 104, BaseQTaskType, 0, 0);
  SplinePathGuideQTask_ePositionChangedEvent = QTask_NewQTaskEventFn(0, "SplinePathChangedPosition");
  v1 = QTask_NewQTaskEventFn(0, "SplinePathConnectObject");
  v2 = SplinePathGuideQTask_eQTaskType;
  SplinePathGuideQTask_eConnectedToGuideEvent = v1;
  QTask_LinkQTaskEventHandlerNoContextFn(SplinePathGuideQTask_eQTaskType, 1, SplinePathGuideQTask_RunHandler);
  QTask_LinkQTaskEventHandlerFn(v2, 0, SplinePathGuideQTask_CreateHandler);
  QTask_LinkQTaskEventHandlerFn(
    v2,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))SplinePathGuideQTask_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(
    v2,
    ParameterList_eUpdateInternalDataQTaskEvent,
    SplinePathGuideQTask_UpdateInternalDataHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v2, 2, SplinePathGuideQTask_DeleteHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(
    v2,
    Level_eRegisterLevelScriptSymbolsEvent,
    SplinePathGuideQTask_RegisterScriptSymbolsHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(
    v2,
    Level_eRemoveLevelScriptSymbolsEvent,
    SplinePathGuideQTask_RemoveScriptSymbolsHandler);
  v3 = (struct ParameterList_s *)Mem_AllocFn(112, 4);
  v3->nParameters = 0;
  v3->nMaxParameters = 5;
  v3->ptParameterListItem = (struct ParameterListItem_s *)&v3[1];
  SplinePathGuideQTask_ptParameterList = v3;
  ParameterList_AddParameter(v3, 0x28u, Level_eParameterTypeInt32, "Path ID", 7u, nullptr);
  ParameterList_AddParameter(
    SplinePathGuideQTask_ptParameterList,
    0x2Cu,
    Level_eParameterTypeInt32,
    "RigidObject ID",
    7u,
    nullptr);
  ParameterList_AddParameter(
    SplinePathGuideQTask_ptParameterList,
    0x38u,
    Level_eParameterTypebool8,
    "Looping",
    7u,
    nullptr);
  ParameterList_AddParameter(
    SplinePathGuideQTask_ptParameterList,
    0x3Cu,
    Level_eParameterTypebool8,
    "RunFromStart",
    7u,
    nullptr);
  ParameterList_AddParameterMinMax(
    SplinePathGuideQTask_ptParameterList,
    0x60u,
    Level_eParameterTypeReal32,
    "Startposition",
    7u,
    0.0,
    1.0);
  v4 = SplinePathGuideQTask_eQTaskType;
  QTask_LinkQTaskEventHandlerFn(
    SplinePathGuideQTask_eQTaskType,
    Serialize_eGetSerializeParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))SplinePathGuideQTask_GetSerializeParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(v4, Serialize_eDeSerializeQTaskEvent, SplinePathGuideQTask_DeSerializeHandler);
  QTask_LinkQTaskEventHandlerFn(v4, Serialize_eSerializeQTaskEvent, SplinePathGuideQTask_SerializeHandler);
  v5 = (struct ParameterList_s *)Mem_AllocFn(112, 4);
  v5->nParameters = 0;
  v5->nMaxParameters = 5;
  v5->ptParameterListItem = (struct ParameterListItem_s *)&v5[1];
  SplinePathGuideQTask_ptSerializeParameterList = v5;
  ParameterList_AddParameter(v5, 0x28u, Level_eParameterTypeInt32, "PathID", 7u, nullptr);
  ParameterList_AddParameter(
    SplinePathGuideQTask_ptSerializeParameterList,
    0x2Cu,
    Level_eParameterTypeInt32,
    "ObjectID",
    7u,
    nullptr);
  ParameterList_AddParameter(
    SplinePathGuideQTask_ptSerializeParameterList,
    0x30u,
    Level_eParameterTypeInt32,
    "CurrentSegment",
    7u,
    nullptr);
  ParameterList_AddParameter(
    SplinePathGuideQTask_ptSerializeParameterList,
    0x34u,
    Level_eParameterTypeInt32,
    "Flags",
    7u,
    nullptr);
  ParameterList_AddParameter(
    SplinePathGuideQTask_ptSerializeParameterList,
    0x58u,
    Level_eParameterTypeReal32,
    "T",
    7u,
    nullptr);
  QTask_LinkQTaskEventHandlerFn(
    SplinePathGuideQTask_eQTaskType,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveHandler);
  SplinePathGuideQTask_ptTaskList = QTaskList_New(100);
  Symbol_Register(
    "SplinePathGuide_SetRunning",
    SplinePathGuideQTask_SetRunningScriptFunction,
    nullptr,
    -1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
}

// source: h/2/splinepathguide.c:799  [anchor-strings]
void __cdecl SplinePathGuideQTask_Close()
{
  int v0; // esi
  int v1; // esi

  Symbol_Remove("SplinePathGuide_SetRunning");
  QTaskList_Delete(SplinePathGuideQTask_ptTaskList);
  if ( SplinePathGuideQTask_ptSerializeParameterList )
  {
    v0 = *(_DWORD *)((unsigned int)&SplinePathGuideQTask_ptSerializeParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
  if ( SplinePathGuideQTask_ptParameterList )
  {
    v1 = *(_DWORD *)((unsigned int)&SplinePathGuideQTask_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v1);
    memset(*(void **)(v1 + 8), 0xCDu, *(_DWORD *)(v1 + 16));
    free((void *)v1);
  }
  QTask_DeleteQTaskEvent(SplinePathGuideQTask_ePositionChangedEvent);
  SplinePathGuideQTask_ePositionChangedEvent = 512;
  QTask_DeleteQTaskEvent(SplinePathGuideQTask_eConnectedToGuideEvent);
  SplinePathGuideQTask_eConnectedToGuideEvent = 512;
  QTask_DeleteQTaskType(SplinePathGuideQTask_eQTaskType);
  SplinePathGuideQTask_eQTaskType = 512;
}
