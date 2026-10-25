/* j/0/objects/radardish.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/objects/radardish.c:92  [anchor-mhash]
void __cdecl RadarDish_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *v2; // eax
  struct QTask_s *v3; // eax
  struct QTask_s *v4; // eax

  ((void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[0][RigidMagicObj_eQTaskType].pfHandler)(
    ptQTask,
    pxContext);
  v2 = *((struct QTask_s **)pxContext + 38);
  ptQTask[8].tQTaskChildren.ptHead = v2;
  ptQTask[8].tQTaskChildren.ptMiddle = v2->ptParent;
  ptQTask[8].tQTaskChildren.ptTail = v2->ptParent;
  ptQTask[8].tQTaskRefList.ptHead = nullptr;
  ptQTask[9].tQTaskRefList.ptTail = nullptr;
  v3 = (struct QTask_s *)Mem_AllocFn(8, 4);
  if ( v3 )
  {
    v3->ptNext = (struct QTask_s *)1;
    v3->ptPrev = nullptr;
  }
  ptQTask[9].ptParent = v3;
  v4 = SoundSys_NewSoundFn(ptQTask, (char *)ptQTask[8].tQTaskChildren.ptHead);
  if ( v4 )
    ptQTask[9].tQTaskRefList.ptTail = QTask_NewQTaskRef(v4);
}

// source: j/0/objects/radardish.c:150  [anchor-mhash]
void __cdecl RadarDish_DeleteHandler(struct QTask_s *ptQTask)
{
  struct QReference_s *ptTail; // eax
  struct QTask_s *ptParent; // eax

  World_RemoveDynCubeObj((struct World_s *)ptQTask[2].ptParent, (struct DynCubeObj_s *)ptQTask);
  ptTail = ptQTask[9].tQTaskRefList.ptTail;
  if ( ptTail )
    QReference_Delete(ptTail, &QTask_tQTaskRefPool);
  ptParent = ptQTask[9].ptParent;
  if ( ptParent )
    SoundSys_DeleteChannelList((struct SoundSysChannelList_t *)ptParent);
}

// source: j/0/objects/radardish.c:182  [anchor-mhash]
void __cdecl RadarDish_RunHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { float v18; };
    struct { char igi2_o1[4]; struct real32x9_t Real32x9_Multiply_tTemp; };
    struct { char igi2_o2[44]; struct real32x9_t tRotation; };
    char igi2_extent[84];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *ptHead; // ecx
  int v3; // edx
  struct QTask_s *v4; // eax
  void (__cdecl *pfHandler)(struct QTask_s *); // eax
  int v6; // edx
  double v7; // st7
  double v8; // st7
  double v9; // st7
  double v10; // st7
  long double v11; // st7
  long double v12; // rt0
  double v13; // st6
  double v14; // st6
  struct QTask_s *ptParent; // eax
  double v16; // st7
  struct QTask_s *v17; // ebx
  float ptQTaska = *(float *)&ptQTask; // [esp+64h] [ebp+4h] ARGSLOT

  ptHead = ptQTask->tQTaskChildren.ptHead;
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
      pfHandler = (void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[1][ptHead->eQTaskType].pfHandler;
      v6 = v3 + 1;
      QTask_nProtectedQTaskStackOffset = v6;
      if ( pfHandler )
      {
        pfHandler(ptHead);
        v6 = QTask_nProtectedQTaskStackOffset;
      }
      ptHead = (struct QTask_s *)dword_849C7DC[v6];
      v3 = v6 - 1;
      QTask_nProtectedQTaskStackOffset = v3;
    }
    while ( ptHead );
  }
  if ( *(float *)&ptQTask[8].tQTaskChildren.ptTail != *(float *)&ptQTask[8].tQTaskChildren.ptMiddle )
  {
    if ( *(float *)&ptQTask[8].tQTaskChildren.ptTail >= (double)*(float *)&ptQTask[8].tQTaskChildren.ptMiddle )
    {
      if ( *(float *)&ptQTask[8].tQTaskChildren.ptTail > (double)*(float *)&ptQTask[8].tQTaskChildren.ptMiddle )
      {
        v8 = *(float *)&ptQTask[8].tQTaskChildren.ptTail
           - *(float *)&ptQTask[8].tQTaskChildren.ptHead->eQTaskType * 0.03333333507180214;
        *(float *)&ptQTask[8].tQTaskChildren.ptTail = v8;
        if ( v8 < *(float *)&ptQTask[8].tQTaskChildren.ptMiddle )
          ptQTask[8].tQTaskChildren.ptTail = ptQTask[8].tQTaskChildren.ptMiddle;
      }
    }
    else
    {
      v7 = *(float *)&ptQTask[8].tQTaskChildren.ptHead->eQTaskType * 0.03333333507180214
         + *(float *)&ptQTask[8].tQTaskChildren.ptTail;
      *(float *)&ptQTask[8].tQTaskChildren.ptTail = v7;
      if ( v7 > *(float *)&ptQTask[8].tQTaskChildren.ptMiddle )
        ptQTask[8].tQTaskChildren.ptTail = ptQTask[8].tQTaskChildren.ptMiddle;
    }
  }
  v9 = *(float *)&ptQTask[8].tQTaskChildren.ptTail * 0.03333333507180214 + *(float *)&ptQTask[8].tQTaskRefList.ptHead;
  *(float *)&ptQTask[8].tQTaskRefList.ptHead = v9;
  if ( v9 >= 360.0 )
  {
    v10 = *(float *)&ptQTask[8].tQTaskRefList.ptHead;
    do
      v10 = v10 - 360.0;
    while ( v10 >= 360.0 );
    *(float *)&ptQTask[8].tQTaskRefList.ptHead = v10;
  }
  v11 = *(float *)&ptQTask[8].tQTaskRefList.ptHead * 0.01745329238474369;
  v12 = sin(v11);
  ptQTaska = cos(v11);
  igi2_frame.tRotation.tX.vY = -v12;
  v13 = *(float *)&ptQTask[8].ptParent * 0.0;
  igi2_frame.Real32x9_Multiply_tTemp.tX.vX = ptQTaska * *(float *)&ptQTask[8].tQTaskRefList.ptMiddle
                                + v12 * *(float *)&ptQTask[8].tQTaskRefList.ptTail
                                + v13;
  igi2_frame.Real32x9_Multiply_tTemp.tX.vY = ptQTaska * *(float *)&ptQTask[8].tQTaskRefList.ptTail
                                + igi2_frame.tRotation.tX.vY * *(float *)&ptQTask[8].tQTaskRefList.ptMiddle
                                + v13;
  igi2_frame.Real32x9_Multiply_tTemp.tX.vZ = (*(float *)&ptQTask[8].tQTaskRefList.ptTail
                                 + *(float *)&ptQTask[8].tQTaskRefList.ptMiddle)
                                * 0.0
                                + *(float *)&ptQTask[8].ptParent;
  v14 = *(float *)&ptQTask[9].ptPrev * 0.0;
  igi2_frame.Real32x9_Multiply_tTemp.tY.vX = ptQTaska * *(float *)&ptQTask[8].eQTaskType + v12 * *(float *)&ptQTask[9].ptNext + v14;
  igi2_frame.Real32x9_Multiply_tTemp.tY.vY = igi2_frame.tRotation.tX.vY * *(float *)&ptQTask[8].eQTaskType
                                + ptQTaska * *(float *)&ptQTask[9].ptNext
                                + v14;
  igi2_frame.Real32x9_Multiply_tTemp.tY.vZ = (*(float *)&ptQTask[8].eQTaskType + *(float *)&ptQTask[9].ptNext) * 0.0
                                + *(float *)&ptQTask[9].ptPrev;
  igi2_frame.v18 = *(float *)&ptQTask[9].tQTaskChildren.ptTail * 0.0;
  igi2_frame.Real32x9_Multiply_tTemp.tZ.vX = ptQTaska * *(float *)&ptQTask[9].tQTaskChildren.ptHead
                                + v12 * *(float *)&ptQTask[9].tQTaskChildren.ptMiddle
                                + igi2_frame.v18;
  igi2_frame.Real32x9_Multiply_tTemp.tZ.vY = ptQTaska * *(float *)&ptQTask[9].tQTaskChildren.ptMiddle
                                + igi2_frame.tRotation.tX.vY * *(float *)&ptQTask[9].tQTaskChildren.ptHead
                                + igi2_frame.v18;
  ptParent = ptQTask[9].ptParent;
  v16 = (*(float *)&ptQTask[9].tQTaskChildren.ptHead + *(float *)&ptQTask[9].tQTaskChildren.ptMiddle) * 0.0
      + *(float *)&ptQTask[9].tQTaskChildren.ptTail;
  igi2_frame.Real32x9_Multiply_tTemp.nOps = (int)&ptQTask[9].tQTaskRefList.ptHead->ptNext + 1;
  igi2_frame.Real32x9_Multiply_tTemp.tZ.vZ = v16;
  qmemcpy(&ptQTask[3].ptPrev, &igi2_frame.Real32x9_Multiply_tTemp, sizeof(struct QTask_s));
  if ( ptParent )
  {
    *(float *)&ptParent->ptPrev = *(float *)&ptQTask[8].tQTaskChildren.ptTail
                                / *(float *)&ptQTask[8].tQTaskChildren.ptHead->ptParent;
    v17 = ptQTask[9].ptParent;
    if ( *(float *)&v17->ptPrev >= 0.0 )
    {
      if ( *(float *)&v17->ptPrev > 1.0 )
        v17->ptPrev = (struct QTask_s *)1065353216;
    }
    else
    {
      v17->ptPrev = nullptr;
    }
  }
}

// source: j/0/objects/radardish.c:230  [anchor-mhash]
void __cdecl RadarDish_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *ptHead; // eax
  int v3; // edx
  struct QTask_s *v4; // ecx
  void (__cdecl *pfHandler)(struct QTask_s *, _DWORD); // ecx
  int v6; // edx

  qmemcpy(&ptQTask[8].tQTaskRefList.ptMiddle, &ptQTask[3].ptPrev, sizeof(struct QTask_s));
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
}

// source: j/0/objects/radardish.c:257  [anchor-mhash]
void __cdecl RadarDish_ParseMagicObjParametersHandler(struct QTask_s *ptQTask, void *pxContext)
{
  void *v2; // ebp
  float *v3; // ebx
  int v4; // esi
  struct ArgList_s *v5; // edi
  struct ArgList_s *v6; // edi
  int v7; // esi
  double v8; // st7
  struct ArgList_s *v9; // ebp
  int v10; // esi

  v2 = pxContext;
  v3 = *(float **)pxContext;
  v4 = *((_DWORD *)pxContext + 2);
  v5 = *((struct ArgList_s **)pxContext + 1);
  if ( v5->isQVM )
  {
    *(_BYTE *)v3 = 0;
    QVM_EvalArg(v3, 32, v5, v4, 3);
  }
  else
  {
    Expression_EvalString(v5->aptExpression[v4], (char *)v3, 32);
  }
  v6 = *((struct ArgList_s **)v2 + 1);
  v7 = v4 + 1;
  if ( v6->isQVM )
  {
    *(float *)&pxContext = 0.0;
    QVM_EvalArg(&pxContext, 4, v6, v7, 2);
    v8 = *(float *)&pxContext;
  }
  else
  {
    v8 = Expression_EvalFloat(v6->aptExpression[v7]);
  }
  v3[8] = v8;
  v9 = *((struct ArgList_s **)v2 + 1);
  v10 = v7 + 1;
  if ( v9->isQVM )
  {
    *(float *)&pxContext = 0.0;
    QVM_EvalArg(&pxContext, 4, v9, v10, 2);
    v3[9] = *(float *)&pxContext;
  }
  else
  {
    v3[9] = Expression_EvalFloat(v9->aptExpression[v10]);
  }
}

// source: j/0/objects/radardish.c:282  [size]
void __cdecl RadarDish_GetMagicObjParameterSizeHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = 40;
}

// source: j/0/objects/radardish.c:298  [size]
void __cdecl RadarDish_WeaponHitHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ptQTask[8].tQTaskChildren.ptMiddle = nullptr;
}

// source: j/0/objects/radardish.c:317  [size]
void __cdecl RadarDish_SoundUpdateParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = ptQTask + 1;
  *((_DWORD *)pxContext + 1) = (char *)ptQTask + 124;
  *((_DWORD *)pxContext + 2) = ptQTask[9].ptParent;
}

// source: j/0/objects/radardish.c:343  [anchor-strings]
void __cdecl RadarDish_Open()
{
  unsigned __int16 v0; // si
  __int16 v1; // ax
  _DWORD *v2; // esi

  v0 = QTask_NewQTaskType("RadarDish", 400, RigidMagicObj_eQTaskType, 0, 0);
  RadarDish_eQTaskType = v0;
  QTask_LinkQTaskEventHandlerFn(v0, 0, RadarDish_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 1, RadarDish_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 2, RadarDish_DeleteHandler);
  QTask_LinkQTaskEventHandlerFn(v0, ParameterList_eUpdateInternalDataQTaskEvent, RadarDish_UpdateInternalDataHandler);
  QTask_LinkQTaskEventHandlerFn(v0, MagicObj_eGetParseMagicObjParametersEvent, RadarDish_ParseMagicObjParametersHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    MagicObj_eGetMagicObjParameterSizeEvent,
    (void (__cdecl *)(struct QTask_s *, void *))RadarDish_GetMagicObjParameterSizeHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    GameFunctions_eWeaponHitQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))RadarDish_WeaponHitHandler);
  v1 = SoundSys_eUpdateParameterListQTaskEvent;
  if ( SoundSys_eUpdateParameterListQTaskEvent == 512 )
  {
    v1 = QTask_NewQTaskEventFn(0, (char *)&g_zFileName.nRealFadeCount);
    v0 = RadarDish_eQTaskType;
    SoundSys_eUpdateParameterListQTaskEvent = v1;
  }
  QTask_LinkQTaskEventHandlerFn(v0, v1, RadarDish_SoundUpdateParameterListHandler);
  Symbol_Register(
    "TASKTYPE_RADARDISH",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)v0,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  v2 = Mem_AllocFn(18444, 4);
  v2[1] = 0;
  *v2 = 0;
  v2[4610] = "TASKTYPE_RADARDISH";
  Wildcard_CreateNFA("TASKTYPE_RADARDISH", v2 + 2, (char *)v2 + 10248);
  List_AddTail(v2, (int)&MagicObjConfig_tTaskTypeEnumList);
}

// source: j/0/objects/radardish.c:379  [size]
void __cdecl RadarDish_Close()
{
  QTask_DeleteQTaskType(RadarDish_eQTaskType);
}
