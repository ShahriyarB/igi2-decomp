/* f/1/sound/sounddeftriggeronce.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: f/1/sound/sounddeftriggeronce.c:46  [anchor-hash]
struct SoundDefTriggerOnce_s *__cdecl SoundDefTriggerOnce_InitSound(
        struct SoundDefTriggerOnce_s *ptSound)
{
  ptSound->vBaseVolume = 1.0;
  ptSound->vRelativeVolume = 1.0;
  ptSound->vPitch = 1.0;
  ptSound->vFalloffEnd = 1.0;
  ptSound->vViewRadius = 1.0;
  ptSound->tPos.vX = 0.0;
  ptSound->tPos.vY = 0.0;
  ptSound->tPos.vZ = 0.0;
  ptSound->tRealPos.vX = 0.0;
  ptSound->tRealPos.vY = 0.0;
  ptSound->tRealPos.vZ = 0.0;
  ptSound->vFalloffBegin = 0.0;
  ptSound->vMinPlayLength = -1.0;
  ptSound->nTriggerChannel = -1;
  ptSound->nVolumeChannel = -1;
  ptSound->nPitchChannel = -1;
  ptSound->nSoundChannel = -1;
  ptSound->isLooped = 0;
  ptSound->isReversed = 0;
  ptSound->isDefinition = 0;
  ptSound->zSoundDef[0] = 0;
  ptSound->zSound[0] = 0;
  return ptSound;
}

// source: f/1/sound/sounddeftriggeronce.c:80  [size]
void __cdecl SoundDefTriggerOnce_MicTriggerHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QReference_s *ptMiddle; // edx
  double v3; // st5
  double v4; // st4

  if ( !BYTE2(ptQTask[6].tQTaskChildren.ptTail) || !*((_BYTE *)pxContext + 4) )
  {
    if ( HIBYTE(ptQTask[8].ptNext) )
    {
      ptMiddle = ptQTask[1].tQTaskRefList.ptMiddle;
      if ( ((unsigned __int8)ptMiddle & 2) == 0
        || (v3 = *(double *)(*(_DWORD *)pxContext + 88) - *(double *)&ptQTask[4].tQTaskChildren.ptTail,
            v4 = *(double *)(*(_DWORD *)pxContext + 96) - *(double *)&ptQTask[4].tQTaskRefList.ptMiddle,
            *(float *)&ptQTask[5].eQTaskType * 4096.0 * (*(float *)&ptQTask[5].eQTaskType * 4096.0) >= v4 * v4 + v3 * v3 + (*(double *)(*(_DWORD *)pxContext + 80) - *(double *)&ptQTask[4].tQTaskChildren.ptHead) * (*(double *)(*(_DWORD *)pxContext + 80) - *(double *)&ptQTask[4].tQTaskChildren.ptHead)) )
      {
        ptQTask[1].tQTaskRefList.ptMiddle = (struct QReference_s *)((unsigned int)ptMiddle & 0xFFFFFFEF
                                                                  | (LOBYTE(ptQTask[6].tQTaskChildren.ptTail) != 0
                                                                   ? 0x10
                                                                   : 0));
        SoundSys_RequestSoundFn((struct SoundSysRequest_s *)&ptQTask[1].tQTaskChildren.ptTail);
      }
    }
  }
}

// source: f/1/sound/sounddeftriggeronce.c:145  [size]
void __cdecl SoundDefTriggerOnce_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  int v2; // eax
  char *v3; // ecx
  char v4; // dl
  char *v5; // eax
  int v6; // edx
  char v7; // cl

  ((void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[0][SoundDefBase_eQTaskType].pfHandler)(
    ptQTask,
    pxContext);
  SoundDefTriggerOnce_InitSound((struct SoundDefTriggerOnce_s *)ptQTask);
  if ( pxContext )
  {
    v2 = *(_DWORD *)pxContext;
    qmemcpy(&ptQTask[4].ptParent, (void *)(*(_DWORD *)pxContext + 192), 0x18u);
    qmemcpy(&ptQTask[4].tQTaskChildren, (void *)(v2 + 168), 0x18u);
    ptQTask[5].tQTaskChildren.ptTail = *(struct QTask_s **)(v2 + 216);
    ptQTask[5].tQTaskRefList.ptTail = *(struct QReference_s **)(v2 + 228);
    ptQTask[5].ptParent = *(struct QTask_s **)(v2 + 232);
    *(_DWORD *)&ptQTask[5].eQTaskType = *(_DWORD *)(v2 + 236);
    ptQTask[8].tQTaskChildren.ptHead = *(struct QTask_s **)(v2 + 328);
    ptQTask[6].ptNext = *(struct QTask_s **)(v2 + 240);
    ptQTask[6].ptPrev = *(struct QTask_s **)(v2 + 244);
    ptQTask[6].tQTaskChildren.ptHead = *(struct QTask_s **)(v2 + 248);
    ptQTask[6].tQTaskChildren.ptMiddle = *(struct QTask_s **)(v2 + 252);
    LOBYTE(ptQTask[6].tQTaskChildren.ptTail) = *(_BYTE *)(v2 + 256);
    BYTE1(ptQTask[6].tQTaskChildren.ptTail) = *(_BYTE *)(v2 + 257);
    v3 = (char *)(v2 + 259);
    BYTE2(ptQTask[6].tQTaskChildren.ptTail) = *((_BYTE *)pxContext + 4);
    do
    {
      v4 = *v3;
      v3[(_DWORD)ptQTask - v2] = *v3;
      ++v3;
    }
    while ( v4 );
    v5 = (char *)(v2 + 291);
    v6 = (char *)&ptQTask[7].tQTaskChildren.ptHead + 3 - v5;
    do
    {
      v7 = *v5;
      v5[v6] = *v5;
      ++v5;
    }
    while ( v7 );
  }
  else
  {
    BYTE2(ptQTask[6].tQTaskChildren.ptTail) = 1;
  }
  HIBYTE(ptQTask[8].ptNext) = 0;
  ptQTask[8].ptPrev = nullptr;
  SoundSys_InitRequest(
    (struct SoundSysRequest_s *)&ptQTask[1].tQTaskChildren.ptTail,
    (char *)&ptQTask[7].tQTaskChildren.ptHead + 3,
    2u);
  if ( !BYTE2(ptQTask[6].tQTaskChildren.ptTail) )
    QTaskList_Register(SoundSys_ptSoundQTaskList, (struct QTaskList_s *)ptQTask);
  SoundDefTriggerOnce_Move(ptQTask);
}

// source: f/1/sound/sounddeftriggeronce.c:223  [anchor-mhash]
void __cdecl SoundDefTriggerOnce_RunHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptHead; // ecx
  int v2; // edx
  struct QTask_s *v3; // eax
  void (__cdecl *pfHandler)(struct QTask_s *); // eax
  int v5; // edx

  if ( HIBYTE(ptQTask[8].ptNext) )
  {
    SoundDefTriggerOnce_Move(ptQTask);
    *(float *)&ptQTask[8].ptPrev = 1.0 / (double)(int)SoundSys_nFrequency + *(float *)&ptQTask[8].ptPrev;
  }
  else
  {
    SoundDefTriggerOnce_Move(ptQTask);
  }
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
}

// source: f/1/sound/sounddeftriggeronce.c:270  [size]
void __cdecl SoundDefTriggerOnce_DeleteHandler(struct QTask_s *ptQTask)
{
  ((void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[2][SoundDefBase_eQTaskType].pfHandler)(ptQTask);
  if ( !BYTE2(ptQTask[6].tQTaskChildren.ptTail) )
    QTaskList_Remove(SoundSys_ptSoundQTaskList, ptQTask);
}

// source: f/1/sound/sounddeftriggeronce.c:300  [anchor-strings]
void __cdecl SoundDefTriggerOnce_SaveHandler(struct QTask_s *ptQTask, void *pxContext)
{
  int i; // ecx
  char *v3; // ecx
  char *v4; // eax
  char *v5; // edi
  char *v6; // edi
  char zTemp[1024]; // [esp+48h] [ebp-400h] BYREF

  for ( i = 0; i < (int)(*((_DWORD *)pxContext + 1)); ++i )
    strcat(*(char **)pxContext, "  ");
  v3 = "TRUE";
  if ( !BYTE1(ptQTask[6].tQTaskChildren.ptTail) )
    v3 = "FALSE";
  v4 = "TRUE";
  if ( !LOBYTE(ptQTask[6].tQTaskChildren.ptTail) )
    v4 = "FALSE";
  sprintf(
    zTemp,
    "%s(\"%s\", \"%s\", %8.08f, %8.08f, %8.08f, %8.08f, %8.08f, %8.08f, %8.08f, %d, %d, %d, %d, %s, %s",
    &g_zFileName.zMenuResourcePath[112],
    (char *)&ptQTask[6].tQTaskChildren.ptTail + 3,
    (char *)&ptQTask[7].tQTaskChildren.ptHead + 3,
    *(double *)&ptQTask[4].ptParent,
    *(double *)&ptQTask[5].ptNext,
    *(double *)&ptQTask[5].tQTaskChildren.ptHead,
    *(float *)&ptQTask[5].tQTaskChildren.ptTail,
    *(float *)&ptQTask[5].tQTaskRefList.ptTail,
    *(float *)&ptQTask[5].ptParent,
    *(float *)&ptQTask[8].tQTaskChildren.ptHead,
    ptQTask[6].ptNext,
    ptQTask[6].ptPrev,
    ptQTask[6].tQTaskChildren.ptHead,
    ptQTask[6].tQTaskChildren.ptMiddle,
    v4,
    v3);
  strcat(*(char **)pxContext, zTemp);
  v5 = *(char **)pxContext;
  if ( *((_DWORD *)pxContext + 1) )
  {
    v6 = v5 - 1;
    if ( ptQTask == (ptQTask->ptParent->tQTaskChildren.ptTail->ptPrev != nullptr
                   ? ptQTask->ptParent->tQTaskChildren.ptTail
                   : nullptr) )
    {
      while ( *++v6 )
        ;
      *(_WORD *)v6 = g_zSpriteName_0.tQTaskChildren.ptMiddle;
    }
    else
    {
      while ( *++v6 )
        ;
      strcpy(v6, "),\r\n");
    }
  }
  else
  {
    strcat(v5, ");\r\n");
  }
}

// source: f/1/sound/sounddeftriggeronce.c:365  [size]
void __cdecl SoundDefTriggerOnce_FindSoundDefHandler(struct QTask_s *ptQTask, void *pxContext)
{
  if ( !*((_DWORD *)pxContext + 1)
    && !strcmp(*(char **)pxContext, (char *)&ptQTask[6].tQTaskChildren.ptTail + 3) )
  {
    *((_DWORD *)pxContext + 1) = ptQTask;
  }
}

// source: f/1/sound/sounddeftriggeronce.c:396  [size]
void __cdecl SoundDefTriggerOnce_RequestSoundDefHandler(struct QTask_s *ptQTask, void *pxContext)
{
  if ( HIBYTE(ptQTask[6].tQTaskChildren.ptTail) )
    *(_DWORD *)pxContext = (char *)ptQTask + 259;
}

// source: f/1/sound/sounddeftriggeronce.c:421  [size]
void __cdecl SoundDefTriggerOnce_SetPositionHandler(struct QTask_s *ptQTask, void *pxContext)
{
  qmemcpy(&ptQTask[4].ptParent, pxContext, 0x18u);
}

// source: f/1/sound/sounddeftriggeronce.c:439  [size]
void __cdecl SoundDefTriggerOnce_SetVolumeHandler(struct QTask_s *ptQTask, void *pxContext)
{
  if ( *(float *)pxContext >= 0.0 )
    ptQTask[5].tQTaskChildren.ptTail = *(struct QTask_s **)pxContext;
  if ( *((float *)pxContext + 1) >= 0.0 )
    ptQTask[5].tQTaskRefList.ptHead = *((struct QReference_s **)pxContext + 1);
}

// source: f/1/sound/sounddeftriggeronce.c:468  [size]
void __cdecl SoundDefTriggerOnce_SetPitchHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ptQTask[5].tQTaskRefList.ptMiddle = *(struct QReference_s **)pxContext;
}

// source: f/1/sound/sounddeftriggeronce.c:489  [size]
void __cdecl SoundDefTriggerOnce_SetRelativeToMicrophoneHandler(
        struct QTask_s *ptQTask,
        void *pxContext)
{
  struct QReference_s *ptMiddle; // ecx

  ptMiddle = ptQTask[1].tQTaskRefList.ptMiddle;
  if ( *(_BYTE *)pxContext )
    ptQTask[1].tQTaskRefList.ptMiddle = (struct QReference_s *)((unsigned int)ptMiddle & 0xFFFFFFFD);
  else
    ptQTask[1].tQTaskRefList.ptMiddle = (struct QReference_s *)((unsigned int)ptMiddle | 2);
}

// source: f/1/sound/sounddeftriggeronce.c:517  [size]
void __cdecl SoundDefTriggerOnce_GetSoundRadiusHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *ptParent; // ecx
  long double v3; // st7

  ptParent = ptQTask->ptParent;
  if ( ptParent && ptParent->eQTaskType == SoundDefGroup_eCreateQTaskType )
    v3 = sqrt(
           *(double *)&ptQTask[4].ptParent * *(double *)&ptQTask[4].ptParent
         + *(double *)&ptQTask[5].ptNext * *(double *)&ptQTask[5].ptNext
         + *(double *)&ptQTask[5].tQTaskChildren.ptHead * *(double *)&ptQTask[5].tQTaskChildren.ptHead)
       + *(float *)&ptQTask[5].eQTaskType;
  else
    v3 = *(float *)&ptQTask[5].eQTaskType;
  if ( v3 > *(float *)pxContext )
    *(float *)pxContext = v3;
}

// source: f/1/sound/sounddeftriggeronce.c:563  [size]
void __cdecl SoundDefTriggerOnce_GetSoundLengthHandler(struct QTask_s *ptQTask, void *pxContext)
{
  int v2; // eax

  v2 = (__int64)(Sound_GetSampleDuration((struct Sample_s *)ptQTask[1].tQTaskChildren.ptTail)
               * (double)(int)SoundSys_nFrequency);
  if ( v2 > (int)(*(_DWORD *)pxContext) )
    *(_DWORD *)pxContext = v2;
}

// source: f/1/sound/sounddeftriggeronce.c:603  [size]
unsigned __int16 __cdecl SoundDefTriggerOnce_GetQTaskType()
{
  return SoundDefTriggerOnce_eQTaskType;
}

// source: f/1/sound/sounddeftriggeronce.c:618  [size]
unsigned __int16 __cdecl SoundDefTriggerOnce_GetCreateQTaskType()
{
  return SoundDefTriggerOnce_eCreateQTaskType;
}

// source: f/1/sound/sounddeftriggeronce.c:633  [size]
void __cdecl SoundDefTriggerOnce_SetCreateQTaskType(unsigned __int16 eQTaskType)
{
  SoundDefTriggerOnce_eCreateQTaskType = eQTaskType;
}

// source: f/1/sound/sounddeftriggeronce.c:650  [size]
struct Result_s *__cdecl SoundDefTriggerOnce_ScriptParseCB(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct Result_s Rs; };
    struct { char igi2_o1[24]; struct SoundSysCreateSoundContext_t tCreateContext; };
    struct { char igi2_o2[32]; struct SoundDefTriggerOnce_s tSoundDefTriggerOnceTemplate; };
    char igi2_extent[368];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)

  if ( AppContext_tAppContext.isServer )
  {
    igi2_frame.Rs.nResult = 0;
    HIDWORD(igi2_frame.Rs.vResult) = 0;
  }
  else
  {
    igi2_frame.tCreateContext.ptSoundDef = (struct QTask_s *)&igi2_frame.tSoundDefTriggerOnceTemplate;
    igi2_frame.tCreateContext.isDefinition = 1;
    SoundDefTriggerOnce_InitSound(&igi2_frame.tSoundDefTriggerOnceTemplate);
    if ( ptArgList->isQVM )
    {
      igi2_frame.tSoundDefTriggerOnceTemplate.zSoundDef[0] = 0;
      QVM_EvalArg(igi2_frame.tSoundDefTriggerOnceTemplate.zSoundDef, 32, ptArgList, 0, 3);
    }
    else
    {
      Expression_EvalString(*ptArgList->aptExpression, igi2_frame.tSoundDefTriggerOnceTemplate.zSoundDef, 32);
    }
    if ( ptArgList->isQVM )
    {
      igi2_frame.tSoundDefTriggerOnceTemplate.zSound[0] = 0;
      QVM_EvalArg(igi2_frame.tSoundDefTriggerOnceTemplate.zSound, 32, ptArgList, 1, 3);
    }
    else
    {
      Expression_EvalString(ptArgList->aptExpression[1], igi2_frame.tSoundDefTriggerOnceTemplate.zSound, 32);
    }
    igi2_frame.tSoundDefTriggerOnceTemplate.tPos.vX = Script_EvalArgFloat(ptArgList, 2);
    igi2_frame.tSoundDefTriggerOnceTemplate.tPos.vY = Script_EvalArgFloat(ptArgList, 3);
    igi2_frame.tSoundDefTriggerOnceTemplate.tPos.vZ = Script_EvalArgFloat(ptArgList, 4);
    igi2_frame.tSoundDefTriggerOnceTemplate.vBaseVolume = Script_EvalArgFloat(ptArgList, 5);
    igi2_frame.tSoundDefTriggerOnceTemplate.vFalloffBegin = Script_EvalArgFloat(ptArgList, 6);
    igi2_frame.tSoundDefTriggerOnceTemplate.vFalloffEnd = Script_EvalArgFloat(ptArgList, 7);
    igi2_frame.tSoundDefTriggerOnceTemplate.vMinPlayLength = Script_EvalArgFloat(ptArgList, 8);
    igi2_frame.tSoundDefTriggerOnceTemplate.nTriggerChannel = Script_EvalArgInt(ptArgList, 9);
    igi2_frame.tSoundDefTriggerOnceTemplate.nVolumeChannel = Script_EvalArgInt(ptArgList, 10);
    igi2_frame.tSoundDefTriggerOnceTemplate.nPitchChannel = Script_EvalArgInt(ptArgList, 11);
    igi2_frame.tSoundDefTriggerOnceTemplate.nSoundChannel = Script_EvalArgInt(ptArgList, 12);
    igi2_frame.tSoundDefTriggerOnceTemplate.isLooped = Script_EvalArgInt(ptArgList, 13);
    igi2_frame.tSoundDefTriggerOnceTemplate.isReversed = Script_EvalArgInt(ptArgList, 14);
    igi2_frame.tSoundDefTriggerOnceTemplate.isDefinition = 1;
    QTask_NewFn((struct QTask_s *)pxContext, SoundDefTriggerOnce_eCreateQTaskType, &igi2_frame.tCreateContext);
    igi2_frame.Rs.nResult = 15;
    HIDWORD(igi2_frame.Rs.vResult) = 1076756480;
  }
  igi2_frame.Rs.zResult = (char *)&g_zInitialValue;
  LODWORD(igi2_frame.Rs.vResult) = 0;
  qmemcpy(retstr, &igi2_frame.Rs, sizeof(struct Result_s));
  return retstr;
}

// source: f/1/sound/sounddeftriggeronce.c:722  [anchor-callee]
void __cdecl SoundDefTriggerOnce_Move(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct SoundSysParameterList_t tParameterList; };
    struct { char igi2_o1[12]; struct real64x3_t Real64x3_Rotate_tTemp; };
    char igi2_extent[36];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  __int16 v1; // ax
  struct real32x9_t *ptParentOrientation; // edx
  struct QTask_s *ptParent; // esi
  void (__cdecl *pfHandler)(struct QTask_s *, struct SoundSysParameterList_t *); // eax
  double *p_tQTaskChildren; // eax
  struct real64x3_t *ptParentPos; // ecx
  struct SoundSysChannelList_t *ptChannelList; // ecx
  struct QTask_s *ptPrev; // eax
  struct QTask_s *ptHead; // eax
  struct QTask_s *ptNext; // eax
  double vChannelData; // st7
  struct QTask_s *ptMiddle; // eax
  char *pzChannelData; // ecx
  double v15; // st7
  double v16; // st7
  double v17; // st7
  char ptNext_high; // al
  char ptQTaska = *(char *)&ptQTask; // [esp+4Ch] [ebp+4h] ARGSLOT

  v1 = SoundSys_eUpdateParameterListQTaskEvent;
  ptParentOrientation = nullptr;
  ptParent = ptQTask->ptParent;
  ptQTaska = 0;
  memset(&igi2_frame.tParameterList, 0, sizeof(igi2_frame.tParameterList));
  if ( SoundSys_eUpdateParameterListQTaskEvent == 512 )
  {
    v1 = QTask_NewQTaskEventFn(0, (char *)&g_zFileName.nRealFadeCount);
    ptParentOrientation = igi2_frame.tParameterList.ptParentOrientation;
    SoundSys_eUpdateParameterListQTaskEvent = v1;
  }
  pfHandler = (void (__cdecl *)(struct QTask_s *, struct SoundSysParameterList_t *))QTask_aatQTaskFinalEvent[v1][ptParent->eQTaskType].pfHandler;
  if ( pfHandler )
  {
    pfHandler(ptParent, &igi2_frame.tParameterList);
    ptParentOrientation = igi2_frame.tParameterList.ptParentOrientation;
  }
  ptQTask[1].ptParent = (struct QTask_s *)1065353216;
  *(_DWORD *)&ptQTask[1].eQTaskType = 1065353216;
  p_tQTaskChildren = (double *)&ptQTask[4].tQTaskChildren;
  ptQTask[2].ptNext = nullptr;
  ptQTask[2].tQTaskChildren.ptHead = nullptr;
  ptQTask[2].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[2].tQTaskChildren.ptTail = nullptr;
  ptQTask[2].tQTaskRefList.ptHead = (struct QReference_s *)1072693248;
  ptQTask[2].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[2].ptParent = nullptr;
  *(_DWORD *)&ptQTask[2].eQTaskType = 0;
  ptQTask[3].ptNext = nullptr;
  ptQTask[3].ptPrev = nullptr;
  ptQTask[3].tQTaskChildren.ptHead = nullptr;
  ptQTask[3].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[3].tQTaskChildren.ptTail = nullptr;
  ptQTask[3].tQTaskRefList.ptHead = nullptr;
  ptQTask[3].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[3].tQTaskRefList.ptTail = nullptr;
  ptQTask[3].ptParent = nullptr;
  *(_DWORD *)&ptQTask[3].eQTaskType = 0;
  ptQTask[4].ptNext = nullptr;
  qmemcpy(&ptQTask[4].tQTaskChildren, &ptQTask[4].ptParent, 0x18u);
  if ( ptParentOrientation )
  {
    igi2_frame.Real64x3_Rotate_tTemp.vX = ptParentOrientation->tX.vY * *(double *)&ptQTask[4].tQTaskChildren.ptTail
                             + ptParentOrientation->tX.vZ * *(double *)&ptQTask[4].tQTaskRefList.ptMiddle
                             + ptParentOrientation->tX.vX * *p_tQTaskChildren;
    igi2_frame.Real64x3_Rotate_tTemp.vY = ptParentOrientation->tY.vY * *(double *)&ptQTask[4].tQTaskChildren.ptTail
                             + ptParentOrientation->tY.vZ * *(double *)&ptQTask[4].tQTaskRefList.ptMiddle
                             + ptParentOrientation->tY.vX * *p_tQTaskChildren;
    igi2_frame.Real64x3_Rotate_tTemp.vZ = ptParentOrientation->tZ.vY * *(double *)&ptQTask[4].tQTaskChildren.ptTail
                             + ptParentOrientation->tZ.vZ * *(double *)&ptQTask[4].tQTaskRefList.ptMiddle
                             + ptParentOrientation->tZ.vX * *p_tQTaskChildren;
    qmemcpy(p_tQTaskChildren, &igi2_frame.Real64x3_Rotate_tTemp, 0x18u);
  }
  ptParentPos = igi2_frame.tParameterList.ptParentPos;
  if ( igi2_frame.tParameterList.ptParentPos )
  {
    *p_tQTaskChildren = igi2_frame.tParameterList.ptParentPos->vX + *p_tQTaskChildren;
    *(double *)&ptQTask[4].tQTaskChildren.ptTail = ptParentPos->vY + *(double *)&ptQTask[4].tQTaskChildren.ptTail;
    *(double *)&ptQTask[4].tQTaskRefList.ptMiddle = ptParentPos->vZ + *(double *)&ptQTask[4].tQTaskRefList.ptMiddle;
  }
  ptChannelList = igi2_frame.tParameterList.ptChannelList;
  if ( igi2_frame.tParameterList.ptChannelList )
  {
    ptPrev = ptQTask[6].ptPrev;
    if ( ptPrev != (struct QTask_s *)-1 )
      ptQTask[1].ptParent = (struct QTask_s *)igi2_frame.tParameterList.ptChannelList->auData[(_DWORD)ptPrev].nChannelData;
    ptHead = ptQTask[6].tQTaskChildren.ptHead;
    if ( ptHead != (struct QTask_s *)-1 )
      *(_DWORD *)&ptQTask[1].eQTaskType = LODWORD(ptChannelList->auData[(_DWORD)ptHead].vChannelData);
    ptNext = ptQTask[6].ptNext;
    if ( ptNext != (struct QTask_s *)-1 )
    {
      vChannelData = ptChannelList->auData[(_DWORD)ptNext].vChannelData;
      if ( BYTE1(ptQTask[6].tQTaskChildren.ptTail) )
      {
        ptChannelList = igi2_frame.tParameterList.ptChannelList;
        ptQTaska = vChannelData == 0.0;
      }
      else
      {
        ptQTaska = (__int64)vChannelData;
      }
    }
    ptMiddle = ptQTask[6].tQTaskChildren.ptMiddle;
    if ( ptMiddle != (struct QTask_s *)-1 )
    {
      pzChannelData = ptChannelList->auData[(_DWORD)ptMiddle].pzChannelData;
      if ( pzChannelData )
      {
        if ( strcmp(pzChannelData, (char *)&ptQTask[7].tQTaskChildren.ptHead + 3) )
        {
          strcpy((char *)&ptQTask[7].tQTaskChildren.ptHead + 3, pzChannelData);
          SoundSys_InitRequest(
            (struct SoundSysRequest_s *)&ptQTask[1].tQTaskChildren.ptTail,
            igi2_frame.tParameterList.ptChannelList->auData[(int)ptQTask[6].tQTaskChildren.ptMiddle].pzChannelData,
            (unsigned int)ptQTask[1].tQTaskRefList.ptMiddle);
          ptQTask[8].ptPrev = nullptr;
        }
      }
    }
  }
  if ( *(float *)&ptQTask[5].tQTaskChildren.ptTail >= 0.0 )
  {
    if ( *(float *)&ptQTask[5].tQTaskChildren.ptTail > 1.0 )
      ptQTask[5].tQTaskChildren.ptTail = (struct QTask_s *)1065353216;
  }
  else
  {
    ptQTask[5].tQTaskChildren.ptTail = nullptr;
  }
  if ( *(float *)&ptQTask[5].tQTaskRefList.ptHead >= 0.0 )
  {
    if ( *(float *)&ptQTask[5].tQTaskRefList.ptHead > 1.0 )
      ptQTask[5].tQTaskRefList.ptHead = (struct QReference_s *)1065353216;
  }
  else
  {
    ptQTask[5].tQTaskRefList.ptHead = nullptr;
  }
  v15 = *(float *)&ptQTask[5].tQTaskRefList.ptHead
      * *(float *)&ptQTask[5].tQTaskChildren.ptTail
      * *(float *)&ptQTask[1].ptParent;
  ptQTask[4].ptNext = ptQTask[8].ptPrev;
  qmemcpy(&ptQTask[2].ptParent, &ptQTask[4].tQTaskChildren, 0x18u);
  *(float *)&ptQTask[1].ptParent = v15;
  *(double *)&ptQTask[2].tQTaskChildren.ptHead = *(float *)&ptQTask[5].tQTaskRefList.ptTail
                                               * *(float *)&ptQTask[1].ptPrev;
  *(double *)&ptQTask[2].tQTaskChildren.ptTail = *(float *)&ptQTask[5].ptParent * *(float *)&ptQTask[1].ptPrev;
  ptQTask[3].tQTaskChildren.ptTail = nullptr;
  v16 = *(float *)&ptQTask[5].tQTaskRefList.ptMiddle;
  ptQTask[3].tQTaskRefList.ptHead = nullptr;
  v17 = v16 * *(float *)&ptQTask[1].eQTaskType;
  ptQTask[3].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[3].tQTaskRefList.ptTail = nullptr;
  ptQTask[3].ptParent = nullptr;
  *(float *)&ptQTask[1].eQTaskType = v17;
  *(_DWORD *)&ptQTask[3].eQTaskType = 0;
  if ( *(float *)&ptQTask[1].ptParent >= 0.0 )
  {
    if ( *(float *)&ptQTask[1].ptParent > 1.0 )
      ptQTask[1].ptParent = (struct QTask_s *)1065353216;
  }
  else
  {
    ptQTask[1].ptParent = nullptr;
  }
  ptNext_high = HIBYTE(ptQTask[8].ptNext);
  *(float *)&ptQTask[5].eQTaskType = *(double *)&ptQTask[2].tQTaskChildren.ptTail;
  if ( ptNext_high )
  {
    if ( *(float *)&ptQTask[8].tQTaskChildren.ptHead >= 0.0 )
    {
      if ( *(float *)&ptQTask[8].ptPrev < (double)*(float *)&ptQTask[8].tQTaskChildren.ptHead )
        return;
      goto LABEL_40;
    }
    if ( LOBYTE(ptQTask[6].tQTaskChildren.ptTail)
      || !SoundSys_SoundPlaying((struct SoundSysRequest_s *)&ptQTask[1].tQTaskChildren.ptTail) )
    {
LABEL_40:
      if ( !ptQTaska )
        HIBYTE(ptQTask[8].ptNext) = 0;
    }
  }
  else if ( ptQTaska )
  {
    ptQTask[8].ptPrev = nullptr;
    HIBYTE(ptQTask[8].ptNext) = 1;
  }
}

// source: f/1/sound/sounddeftriggeronce.c:880  [anchor-hash]
void __cdecl SoundDefTriggerOnce_Open()
{
  unsigned __int16 v0; // si
  __int16 v1; // ax
  __int16 v2; // ax
  __int16 v3; // ax
  __int16 v4; // ax
  __int16 v5; // ax
  __int16 v6; // ax
  __int16 v7; // ax
  __int16 v8; // ax
  __int16 v9; // ax

  v0 = QTask_NewQTaskType("SoundDefTriggerOnce", 336, SoundDefBase_eQTaskType, 512, 0);
  SoundDefTriggerOnce_eQTaskType = v0;
  SoundDefTriggerOnce_eCreateQTaskType = v0;
  QTask_LinkQTaskEventHandlerFn(v0, 0, SoundDefTriggerOnce_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 1, SoundDefTriggerOnce_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 2, SoundDefTriggerOnce_DeleteHandler);
  QTask_LinkQTaskEventHandlerFn(v0, Microphone_eTriggerEvent, SoundDefTriggerOnce_MicTriggerHandler);
  v1 = SoundSys_eSaveQTaskEvent;
  if ( SoundSys_eSaveQTaskEvent == 512 )
  {
    v1 = QTask_NewQTaskEventFn(0, &g_zFileName.zMenuResourcePath[16]);
    v0 = SoundDefTriggerOnce_eQTaskType;
    SoundSys_eSaveQTaskEvent = v1;
  }
  QTask_LinkQTaskEventHandlerFn(v0, v1, SoundDefTriggerOnce_SaveHandler);
  v2 = SoundSys_eFindSoundDefQTaskEvent;
  if ( SoundSys_eFindSoundDefQTaskEvent == 512 )
  {
    v2 = QTask_NewQTaskEventFn(0, (char *)&g_zFileName.iActiveTABItem);
    v0 = SoundDefTriggerOnce_eQTaskType;
    SoundSys_eFindSoundDefQTaskEvent = v2;
  }
  QTask_LinkQTaskEventHandlerFn(v0, v2, SoundDefTriggerOnce_FindSoundDefHandler);
  v3 = SoundSys_eRequestSoundDefQTaskEvent;
  if ( SoundSys_eRequestSoundDefQTaskEvent == 512 )
  {
    v3 = QTask_NewQTaskEventFn(0, (char *)&g_zFileName.aptSelectableTABItems[31]);
    v0 = SoundDefTriggerOnce_eQTaskType;
    SoundSys_eRequestSoundDefQTaskEvent = v3;
  }
  QTask_LinkQTaskEventHandlerFn(
    v0,
    v3,
    (void (__cdecl *)(struct QTask_s *, void *))SoundDefTriggerOnce_RequestSoundDefHandler);
  v4 = SoundSys_eSetPositionQTaskEvent;
  if ( SoundSys_eSetPositionQTaskEvent == 512 )
  {
    v4 = QTask_NewQTaskEventFn(0, (char *)&g_zFileName.aptSelectableTABItems[26]);
    v0 = SoundDefTriggerOnce_eQTaskType;
    SoundSys_eSetPositionQTaskEvent = v4;
  }
  QTask_LinkQTaskEventHandlerFn(
    v0,
    v4,
    (void (__cdecl *)(struct QTask_s *, void *))SoundDefTriggerOnce_SetPositionHandler);
  v5 = SoundSys_eSetVolumeQTaskEvent;
  if ( SoundSys_eSetVolumeQTaskEvent == 512 )
  {
    v5 = QTask_NewQTaskEventFn(0, (char *)&g_zFileName.aptSelectableTABItems[18]);
    v0 = SoundDefTriggerOnce_eQTaskType;
    SoundSys_eSetVolumeQTaskEvent = v5;
  }
  QTask_LinkQTaskEventHandlerFn(v0, v5, SoundDefTriggerOnce_SetVolumeHandler);
  v6 = SoundSys_eSetPitchQTaskEvent;
  if ( SoundSys_eSetPitchQTaskEvent == 512 )
  {
    v6 = QTask_NewQTaskEventFn(0, (char *)&g_zFileName.aptSelectableTABItems[14]);
    v0 = SoundDefTriggerOnce_eQTaskType;
    SoundSys_eSetPitchQTaskEvent = v6;
  }
  QTask_LinkQTaskEventHandlerFn(v0, v6, SoundDefTriggerOnce_SetPitchHandler);
  v7 = SoundSys_eSetRelativeToMicrophoneQTaskEvent;
  if ( SoundSys_eSetRelativeToMicrophoneQTaskEvent == 512 )
  {
    v7 = QTask_NewQTaskEventFn(0, (char *)&g_zFileName.aptSelectableTABItems[6]);
    v0 = SoundDefTriggerOnce_eQTaskType;
    SoundSys_eSetRelativeToMicrophoneQTaskEvent = v7;
  }
  QTask_LinkQTaskEventHandlerFn(
    v0,
    v7,
    (void (__cdecl *)(struct QTask_s *, void *))SoundDefTriggerOnce_SetRelativeToMicrophoneHandler);
  v8 = SoundSys_eGetSoundRadiusQTaskEvent;
  if ( SoundSys_eGetSoundRadiusQTaskEvent == 512 )
  {
    v8 = QTask_NewQTaskEventFn(0, (char *)&g_zFileName.aptSelectableTABItems[2]);
    v0 = SoundDefTriggerOnce_eQTaskType;
    SoundSys_eGetSoundRadiusQTaskEvent = v8;
  }
  QTask_LinkQTaskEventHandlerFn(
    v0,
    v8,
    (void (__cdecl *)(struct QTask_s *, void *))SoundDefTriggerOnce_GetSoundRadiusHandler);
  v9 = SoundSys_eGetSoundLengthQTaskEvent;
  if ( SoundSys_eGetSoundLengthQTaskEvent == 512 )
  {
    v9 = QTask_NewQTaskEventFn(0, (char *)&g_zFileName.aptSelectableItems[30]);
    v0 = SoundDefTriggerOnce_eQTaskType;
    SoundSys_eGetSoundLengthQTaskEvent = v9;
  }
  QTask_LinkQTaskEventHandlerFn(v0, v9, SoundDefTriggerOnce_GetSoundLengthHandler);
}

// source: f/1/sound/sounddeftriggeronce.c:907  [size]
void __cdecl SoundDefTriggerOnce_Close()
{
  QTask_DeleteQTaskType(SoundDefTriggerOnce_eQTaskType);
  SoundDefTriggerOnce_eQTaskType = 512;
  SoundDefTriggerOnce_eCreateQTaskType = 512;
}
