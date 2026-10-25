/* f/1/sound/sounddefgraph.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: f/1/sound/sounddefgraph.c:50  [size]
struct SoundDefGraph_s *__cdecl SoundDefGraph_InitSound(
        struct SoundDefGraph_s *ptSound)
{
  float *avPitchEnvelope; // edx
  int v2; // edi
  unsigned int v3; // edx

  ptSound->nVolumeChannel = -1;
  ptSound->nPitchChannel = -1;
  ptSound->nPitchOffsetChannel = -1;
  ptSound->nSoundChannel = -1;
  ptSound->tPos.vX = 0.0;
  ptSound->tPos.vY = 0.0;
  ptSound->tPos.vZ = 0.0;
  ptSound->tRealPos.vX = 0.0;
  ptSound->tRealPos.vY = 0.0;
  ptSound->tRealPos.vZ = 0.0;
  ptSound->vBaseVolume = 1.0;
  ptSound->vRelativeVolume = 1.0;
  ptSound->vPitch = 1.0;
  ptSound->vFalloffBegin = 0.0;
  ptSound->vFalloffEnd = 1.0;
  ptSound->vViewRadius = 1.0;
  avPitchEnvelope = ptSound->avPitchEnvelope;
  v2 = 11;
  do
  {
    *(avPitchEnvelope - 11) = 1.0;
    *avPitchEnvelope++ = 1.0;
    --v2;
  }
  while ( v2 );
  v3 = SoundSys_nCurrentID;
  ptSound->zSoundDef[0] = 0;
  ptSound->zSound[0] = 0;
  ptSound->isDefinition = 0;
  ptSound->tSound.nSoundID = v3;
  ptSound->tSound.ptSample = nullptr;
  ptSound->tSound.bFlags = 0;
  ptSound->tSound.tModify.tAttr.vVolume = 1.0;
  ptSound->tSound.tModify.tAttr.vPitch = 1.0;
  SoundSys_nCurrentID = v3 + 1;
  ptSound->tSound.tModify.tAttr.vPan = 0.0;
  ptSound->tSound.tModify.tAttr.vFalloffBegin = 0.0;
  ptSound->tSound.tModify.tAttr.vFalloffEnd = 1.0;
  ptSound->tSound.tModify.tAttr.vOcclusion = 0.0;
  ptSound->tSound.tModify.tPos.vX = 0.0;
  ptSound->tSound.tModify.tPos.vY = 0.0;
  ptSound->tSound.tModify.tPos.vZ = 0.0;
  ptSound->tSound.tModify.tSpeed.vX = 0.0;
  ptSound->tSound.tModify.tSpeed.vY = 0.0;
  ptSound->tSound.tModify.tSpeed.vZ = 0.0;
  ptSound->tSound.tModify.vPlayPos = 0.0;
  return ptSound;
}

// source: f/1/sound/sounddefgraph.c:95  [size]
void __cdecl SoundDefGraph_MicTriggerHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QReference_s *ptMiddle; // edx
  double v3; // st5
  double v4; // st4
  bool v5; // zf
  unsigned int v6; // eax

  if ( !LOBYTE(ptQTask[6].ptPrev) || !*((_BYTE *)pxContext + 4) )
  {
    ptMiddle = ptQTask[1].tQTaskRefList.ptMiddle;
    if ( ((unsigned __int8)ptMiddle & 2) == 0
      || (v3 = *(double *)(*(_DWORD *)pxContext + 88) - *(double *)&ptQTask[4].tQTaskChildren.ptTail,
          v4 = *(double *)(*(_DWORD *)pxContext + 96) - *(double *)&ptQTask[4].tQTaskRefList.ptMiddle,
          *(float *)&ptQTask[6].ptNext * 4096.0 * (*(float *)&ptQTask[6].ptNext * 4096.0) >= v4 * v4
                                                                                           + v3 * v3
                                                                                           + (*(double *)(*(_DWORD *)pxContext + 80)
                                                                                            - *(double *)&ptQTask[4].tQTaskChildren.ptHead)
                                                                                           * (*(double *)(*(_DWORD *)pxContext + 80)
                                                                                            - *(double *)&ptQTask[4].tQTaskChildren.ptHead)) )
    {
      v5 = SoundSys_isSoundDisabled == 0;
      ptQTask[1].tQTaskRefList.ptMiddle = (struct QReference_s *)((unsigned int)ptMiddle | 0x10);
      if ( v5 )
      {
        if ( !ptQTask[1].tQTaskRefList.ptHead )
        {
          v6 = SoundSys_nCurrentID;
          ptQTask[1].tQTaskRefList.ptHead = (struct QReference_s *)SoundSys_nCurrentID;
          SoundSys_nCurrentID = v6 + 1;
        }
        SoundSys_AddSoundToRequestlist(
          (unsigned int)ptQTask[1].tQTaskRefList.ptHead,
          (struct Sample_s *)ptQTask[1].tQTaskChildren.ptTail,
          (unsigned int)ptQTask[1].tQTaskRefList.ptMiddle,
          (struct SoundModify_t *)&ptQTask[1].ptParent);
      }
    }
  }
}

// source: f/1/sound/sounddefgraph.c:154  [size]
void __cdecl SoundDefGraph_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  int v2; // eax
  char *v3; // esi
  char v4; // cl
  char *v5; // eax
  int v6; // edx
  char v7; // cl

  ((void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[0][SoundDefBase_eQTaskType].pfHandler)(
    ptQTask,
    pxContext);
  SoundDefGraph_InitSound((struct SoundDefGraph_s *)ptQTask);
  if ( pxContext )
  {
    v2 = *(_DWORD *)pxContext;
    qmemcpy(&ptQTask[4].ptParent, (void *)(*(_DWORD *)pxContext + 192), 0x18u);
    qmemcpy(&ptQTask[4].tQTaskChildren, (void *)(v2 + 192), 0x18u);
    ptQTask[5].tQTaskChildren.ptTail = *(struct QTask_s **)(v2 + 216);
    ptQTask[5].tQTaskRefList.ptHead = *(struct QReference_s **)(v2 + 220);
    ptQTask[5].tQTaskRefList.ptMiddle = *(struct QReference_s **)(v2 + 224);
    ptQTask[5].ptParent = *(struct QTask_s **)(v2 + 232);
    *(_DWORD *)&ptQTask[5].eQTaskType = *(_DWORD *)(v2 + 236);
    ptQTask[6].ptNext = *(struct QTask_s **)(v2 + 240);
    ptQTask[6].tQTaskChildren = *(struct QTaskNodeList_s *)(v2 + 248);
    ptQTask[6].tQTaskRefList.ptHead = *(struct QReference_s **)(v2 + 260);
    qmemcpy(&ptQTask[6].tQTaskRefList.ptMiddle, (void *)(v2 + 264), 0x2Cu);
    qmemcpy(&ptQTask[7].tQTaskRefList.ptTail, (void *)(v2 + 308), 0x2Cu);
    v3 = (char *)(v2 + 352);
    do
    {
      v4 = *v3;
      v3[(_DWORD)ptQTask - v2] = *v3;
      ++v3;
    }
    while ( v4 );
    v5 = (char *)(v2 + 384);
    v6 = (char *)&ptQTask[9].tQTaskRefList.ptMiddle - v5;
    do
    {
      v7 = *v5;
      v5[v6] = *v5;
      ++v5;
    }
    while ( v7 );
    LOBYTE(ptQTask[6].ptPrev) = *((_BYTE *)pxContext + 4);
  }
  else
  {
    LOBYTE(ptQTask[6].ptPrev) = 1;
  }
  SoundSys_InitRequest(
    (struct SoundSysRequest_s *)&ptQTask[1].tQTaskChildren.ptTail,
    (char *)&ptQTask[9].tQTaskRefList.ptMiddle,
    0x12u);
  if ( !LOBYTE(ptQTask[6].ptPrev) )
    QTaskList_Register(SoundSys_ptSoundQTaskList, (struct QTaskList_s *)ptQTask);
  SoundDefGraph_Move(ptQTask);
}

// source: f/1/sound/sounddefgraph.c:229  [size]
// attributes: thunk
void __cdecl SoundDefGraph_RunHandler(struct QTask_s *ptQTask)
{
  SoundDefGraph_Move(ptQTask);
}

// source: f/1/sound/sounddefgraph.c:255  [size]
void __cdecl SoundDefGraph_DeleteHandler(struct QTask_s *ptQTask)
{
  ((void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[2][SoundDefBase_eQTaskType].pfHandler)(ptQTask);
  if ( !LOBYTE(ptQTask[6].ptPrev) )
    QTaskList_Remove(SoundSys_ptSoundQTaskList, ptQTask);
}

// source: f/1/sound/sounddefgraph.c:286  [anchor-strings]
void __cdecl SoundDefGraph_SaveHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { int v10; };
    struct { int v9; };
    struct { char igi2_o2[4]; char zTemp[1024]; };
    char igi2_extent[1028];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int i; // ecx
  float *p_ptMiddle; // ebx
  float *p_ptTail; // ebx
  char *v5; // edi
  char *v6; // edi

  for ( i = 0; i < (int)(*((_DWORD *)pxContext + 1)); ++i )
    strcat(*(char **)pxContext, "  ");
  sprintf(
    igi2_frame.zTemp,
    "%s(\"%s\", \"%s\", %8.08f, %8.08f, %8.08f, %8.08f, %8.08f, %8.08f, %d, %d, %d, %d",
    &g_zFileName.zMenuResourcePath[132],
    (char *)&ptQTask[8].ptParent,
    (char *)&ptQTask[9].tQTaskRefList.ptMiddle,
    *(double *)&ptQTask[4].ptParent,
    *(double *)&ptQTask[5].ptNext,
    *(double *)&ptQTask[5].tQTaskChildren.ptHead,
    *(float *)&ptQTask[5].tQTaskChildren.ptTail,
    *(float *)&ptQTask[5].ptParent,
    *(float *)&ptQTask[5].eQTaskType,
    ptQTask[6].tQTaskChildren.ptHead,
    ptQTask[6].tQTaskChildren.ptMiddle,
    ptQTask[6].tQTaskRefList.ptHead,
    ptQTask[6].tQTaskChildren.ptTail);
  strcat(*(char **)pxContext, igi2_frame.zTemp);
  p_ptMiddle = (float *)&ptQTask[6].tQTaskRefList.ptMiddle;
  igi2_frame.v9 = 11;
  do
  {
    sprintf(igi2_frame.zTemp, ", %8.08f", *p_ptMiddle);
    strcat(*(char **)pxContext, igi2_frame.zTemp);
    ++p_ptMiddle;
    --igi2_frame.v9;
  }
  while ( igi2_frame.v9 );
  p_ptTail = (float *)&ptQTask[7].tQTaskRefList.ptTail;
  igi2_frame.v10 = 11;
  do
  {
    sprintf(igi2_frame.zTemp, ", %8.08f", *p_ptTail);
    strcat(*(char **)pxContext, igi2_frame.zTemp);
    ++p_ptTail;
    --igi2_frame.v10;
  }
  while ( igi2_frame.v10 );
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

// source: f/1/sound/sounddefgraph.c:360  [size]
void __cdecl SoundDefGraph_FindSoundDefHandler(struct QTask_s *ptQTask, void *pxContext)
{
  if ( !*((_DWORD *)pxContext + 1) && !strcmp(*(char **)pxContext, (char *)&ptQTask[8].ptParent) )
    *((_DWORD *)pxContext + 1) = ptQTask;
}

// source: f/1/sound/sounddefgraph.c:390  [size]
void __cdecl SoundDefGraph_RequestSoundDefHandler(struct QTask_s *ptQTask, void *pxContext)
{
  if ( LOBYTE(ptQTask[8].ptParent) )
    *(_DWORD *)pxContext = (char *)ptQTask + 352;
}

// source: f/1/sound/sounddefgraph.c:415  [size]
void __cdecl SoundDefGraph_SetPositionHandler(struct QTask_s *ptQTask, void *pxContext)
{
  qmemcpy(&ptQTask[4].ptParent, pxContext, 0x18u);
}

// source: f/1/sound/sounddefgraph.c:433  [size]
void __cdecl SoundDefGraph_SetVolumeHandler(struct QTask_s *ptQTask, void *pxContext)
{
  if ( *(float *)pxContext >= 0.0 )
    ptQTask[5].tQTaskChildren.ptTail = *(struct QTask_s **)pxContext;
  if ( *((float *)pxContext + 1) >= 0.0 )
    ptQTask[5].tQTaskRefList.ptHead = *((struct QReference_s **)pxContext + 1);
}

// source: f/1/sound/sounddefgraph.c:462  [size]
void __cdecl SoundDefGraph_SetPitchHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)&ptQTask[1].eQTaskType = *(_DWORD *)pxContext;
}

// source: f/1/sound/sounddefgraph.c:483  [size]
void __cdecl SoundDefGraph_SetRelativeToMicrophoneHandler__sounddefgraph(
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

// source: f/1/sound/sounddefgraph.c:511  [size]
void __cdecl SoundDefGraph_GetSoundRadiusHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *ptParent; // ecx
  long double v3; // st7

  ptParent = ptQTask->ptParent;
  if ( ptParent && ptParent->eQTaskType == SoundDefGroup_eCreateQTaskType )
    v3 = sqrt(
           *(double *)&ptQTask[4].ptParent * *(double *)&ptQTask[4].ptParent
         + *(double *)&ptQTask[5].ptNext * *(double *)&ptQTask[5].ptNext
         + *(double *)&ptQTask[5].tQTaskChildren.ptHead * *(double *)&ptQTask[5].tQTaskChildren.ptHead)
       + *(float *)&ptQTask[6].ptNext;
  else
    v3 = *(float *)&ptQTask[6].ptNext;
  if ( v3 > *(float *)pxContext )
    *(float *)pxContext = v3;
}

// source: f/1/sound/sounddefgraph.c:557  [size]
void __cdecl SoundDefGraph_GetSoundLengthHandler(struct QTask_s *ptQTask, void *pxContext)
{
  int v2; // eax

  v2 = (__int64)(Sound_GetSampleDuration((struct Sample_s *)ptQTask[1].tQTaskChildren.ptTail)
               * (double)(int)SoundSys_nFrequency);
  if ( v2 > (int)(*(_DWORD *)pxContext) )
    *(_DWORD *)pxContext = v2;
}

// source: f/1/sound/sounddefgraph.c:593  [size]
unsigned __int16 __cdecl SoundDefGraph_GetQTaskType()
{
  return SoundDefGraph_eQTaskType;
}

// source: f/1/sound/sounddefgraph.c:608  [size]
unsigned __int16 __cdecl SoundDefGraph_GetCreateQTaskType()
{
  return SoundDefGraph_eCreateQTaskType;
}

// source: f/1/sound/sounddefgraph.c:623  [size]
void __cdecl SoundDefGraph_SetCreateQTaskType(unsigned __int16 eQTaskType)
{
  SoundDefGraph_eCreateQTaskType = eQTaskType;
}

// source: f/1/sound/sounddefgraph.c:640  [size]
struct Result_s *__cdecl SoundDefGraph_ScriptParseCB(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  #pragma pack(push, 1)
  union
  {
    struct { int iArg; };
    struct { char igi2_o1[4]; float pxData; };
    struct { char igi2_o2[8]; struct SoundSysCreateSoundContext_t tCreateContext; };
    struct { char igi2_o3[16]; struct Result_s Rs; };
    struct { char igi2_o4[40]; struct SoundDefGraph_s tGraphTemplate; };
    char igi2_extent[456];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v3; // esi
  int v4; // ebx
  double v5; // st7
  int v6; // eax
  int i; // ebx
  double v8; // st7

  if ( AppContext_tAppContext.isServer )
  {
    igi2_frame.Rs.nResult = 0;
    igi2_frame.Rs.vResult = 0.0;
  }
  else
  {
    igi2_frame.tCreateContext.ptSoundDef = (struct QTask_s *)&igi2_frame.tGraphTemplate;
    igi2_frame.tCreateContext.isDefinition = 1;
    SoundDefGraph_InitSound(&igi2_frame.tGraphTemplate);
    if ( ptArgList->isQVM )
    {
      igi2_frame.tGraphTemplate.zSoundDef[0] = 0;
      QVM_EvalArg(igi2_frame.tGraphTemplate.zSoundDef, 32, ptArgList, 0, 3);
    }
    else
    {
      Expression_EvalString(*ptArgList->aptExpression, igi2_frame.tGraphTemplate.zSoundDef, 32);
    }
    if ( ptArgList->isQVM )
    {
      igi2_frame.tGraphTemplate.zSound[0] = 0;
      QVM_EvalArg(igi2_frame.tGraphTemplate.zSound, 32, ptArgList, 1, 3);
    }
    else
    {
      Expression_EvalString(ptArgList->aptExpression[1], igi2_frame.tGraphTemplate.zSound, 32);
    }
    igi2_frame.tGraphTemplate.tPos.vX = Script_EvalArgFloat(ptArgList, 2);
    igi2_frame.tGraphTemplate.tPos.vY = Script_EvalArgFloat(ptArgList, 3);
    igi2_frame.tGraphTemplate.tPos.vZ = Script_EvalArgFloat(ptArgList, 4);
    igi2_frame.tGraphTemplate.vBaseVolume = Script_EvalArgFloat(ptArgList, 5);
    igi2_frame.tGraphTemplate.vFalloffBegin = Script_EvalArgFloat(ptArgList, 6);
    igi2_frame.tGraphTemplate.vFalloffEnd = Script_EvalArgFloat(ptArgList, 7);
    igi2_frame.tGraphTemplate.nVolumeChannel = Script_EvalArgInt(ptArgList, 8);
    igi2_frame.tGraphTemplate.nPitchChannel = Script_EvalArgInt(ptArgList, 9);
    igi2_frame.tGraphTemplate.nSoundChannel = Script_EvalArgInt(ptArgList, 10);
    igi2_frame.tGraphTemplate.nPitchOffsetChannel = Script_EvalArgInt(ptArgList, 11);
    v3 = 12;
    v4 = 12;
    igi2_frame.iArg = 11;
    do
    {
      if ( ptArgList->isQVM )
      {
        igi2_frame.pxData = 0.0;
        QVM_EvalArg(&igi2_frame.pxData, 4, ptArgList, v3, 2);
        v5 = igi2_frame.pxData;
      }
      else
      {
        v5 = Expression_EvalFloat(ptArgList->aptExpression[v4]);
      }
      v6 = igi2_frame.iArg;
      *(float *)((char *)&igi2_frame.tGraphTemplate.vBaseVolume + v4 * 4) = v5;
      ++v3;
      ++v4;
      igi2_frame.iArg = v6 - 1;
    }
    while ( v6 != 1 );
    for ( i = 0; i < 11; ++i )
    {
      if ( ptArgList->isQVM )
      {
        *(float *)&igi2_frame.iArg = 0.0;
        QVM_EvalArg(&igi2_frame.iArg, 4, ptArgList, v3, 2);
        v8 = *(float *)&igi2_frame.iArg;
      }
      else
      {
        v8 = Expression_EvalFloat(ptArgList->aptExpression[v3]);
      }
      ++v3;
      igi2_frame.tGraphTemplate.avPitchEnvelope[i] = v8;
    }
    igi2_frame.iArg = v3;
    igi2_frame.tGraphTemplate.isDefinition = 1;
    QTask_NewFn((struct QTask_s *)pxContext, SoundDefGraph_eCreateQTaskType, &igi2_frame.tCreateContext);
    igi2_frame.Rs.nResult = v3;
    igi2_frame.Rs.vResult = (double)igi2_frame.iArg;
  }
  igi2_frame.Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &igi2_frame.Rs, sizeof(struct Result_s));
  return retstr;
}

// source: f/1/sound/sounddefgraph.c:718  [anchor-caller]
void __cdecl SoundDefGraph_Move(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct SoundSysParameterList_t tParameterList; };
    struct { char igi2_o1[12]; struct real64x3_t Real64x3_Rotate_tTemp; };
    char igi2_extent[36];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  __int16 v1; // cx
  struct real32x9_t *ptParentOrientation; // eax
  struct QTask_s *ptParent; // edi
  void (__cdecl *pfHandler)(struct QTask_s *, struct SoundSysParameterList_t *); // ecx
  struct QTask_s **p_ptParent; // ebx
  double *p_tQTaskChildren; // edx
  struct real64x3_t *ptParentPos; // eax
  struct SoundSysChannelList_t *ptChannelList; // ecx
  struct QTask_s *ptHead; // edx
  struct QTask_s *ptMiddle; // eax
  struct QTask_s *ptTail; // eax
  struct QReference_s *v12; // eax
  char *pzChannelData; // edx
  double v14; // st7
  double v15; // st7
  double v16; // st7
  double v17; // st7
  double v18; // st7

  v1 = SoundSys_eUpdateParameterListQTaskEvent;
  ptParentOrientation = nullptr;
  ptParent = ptQTask->ptParent;
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
  p_ptParent = &ptQTask[1].ptParent;
  ptQTask[2].ptNext = nullptr;
  ptQTask[2].tQTaskChildren.ptHead = nullptr;
  ptQTask[2].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[2].tQTaskChildren.ptTail = nullptr;
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
  p_tQTaskChildren = (double *)&ptQTask[4].tQTaskChildren;
  ptQTask[1].ptParent = (struct QTask_s *)1065353216;
  *(_DWORD *)&ptQTask[1].eQTaskType = 1065353216;
  ptQTask[2].tQTaskRefList.ptHead = (struct QReference_s *)1072693248;
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
    ptHead = ptQTask[6].tQTaskChildren.ptHead;
    if ( ptHead != (struct QTask_s *)-1 )
    {
      if ( igi2_frame.tParameterList.ptChannelList->auData[(_DWORD)ptHead].vChannelData < 0.0 )
      {
        *p_ptParent = nullptr;
      }
      else
      {
        SoundSys_CalculateParameterFromEnvelope(
          (float *)&ptQTask[1].ptParent,
          (float *)&ptQTask[6].tQTaskRefList.ptMiddle,
          igi2_frame.tParameterList.ptChannelList->auData[(_DWORD)ptHead].vChannelData);
        ptChannelList = igi2_frame.tParameterList.ptChannelList;
      }
    }
    ptMiddle = ptQTask[6].tQTaskChildren.ptMiddle;
    if ( ptMiddle != (struct QTask_s *)-1 )
    {
      SoundSys_CalculateParameterFromEnvelope(
        (float *)&ptQTask[1].eQTaskType,
        (float *)&ptQTask[7].tQTaskRefList.ptTail,
        ptChannelList->auData[(_DWORD)ptMiddle].vChannelData);
      ptChannelList = igi2_frame.tParameterList.ptChannelList;
    }
    ptTail = ptQTask[6].tQTaskChildren.ptTail;
    if ( ptTail != (struct QTask_s *)-1 )
      *(float *)&ptQTask[1].eQTaskType = ptChannelList->auData[(_DWORD)ptTail].vChannelData
                                       + *(float *)&ptQTask[1].eQTaskType;
    v12 = ptQTask[6].tQTaskRefList.ptHead;
    if ( v12 != (struct QReference_s *)-1 )
    {
      pzChannelData = ptChannelList->auData[(_DWORD)v12].pzChannelData;
      if ( pzChannelData )
      {
        if ( strcmp(ptChannelList->auData[(_DWORD)v12].pzChannelData, (char *)&ptQTask[9].tQTaskRefList.ptMiddle) )
        {
          strcpy((char *)&ptQTask[9].tQTaskRefList.ptMiddle, pzChannelData);
          SoundSys_InitRequest(
            (struct SoundSysRequest_s *)&ptQTask[1].tQTaskChildren.ptTail,
            (char *)&ptQTask[9].tQTaskRefList.ptMiddle,
            0x12u);
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
  v14 = *(float *)&ptQTask[5].tQTaskRefList.ptHead * *(float *)&ptQTask[5].tQTaskChildren.ptTail;
  qmemcpy(&ptQTask[2].ptParent, &ptQTask[4].tQTaskChildren, 0x18u);
  v15 = v14 * *(float *)p_ptParent;
  ptQTask[3].tQTaskChildren.ptTail = nullptr;
  ptQTask[3].tQTaskRefList.ptHead = nullptr;
  ptQTask[3].tQTaskRefList.ptMiddle = nullptr;
  *(float *)p_ptParent = v15;
  ptQTask[3].tQTaskRefList.ptTail = nullptr;
  v16 = *(float *)&ptQTask[5].tQTaskRefList.ptMiddle;
  ptQTask[3].ptParent = nullptr;
  v17 = v16 * *(float *)&ptQTask[1].eQTaskType;
  *(_DWORD *)&ptQTask[3].eQTaskType = 0;
  *(float *)&ptQTask[1].eQTaskType = v17;
  *(double *)&ptQTask[2].tQTaskChildren.ptHead = *(float *)&ptQTask[5].ptParent * *(float *)&ptQTask[1].ptPrev;
  *(double *)&ptQTask[2].tQTaskChildren.ptTail = *(float *)&ptQTask[5].eQTaskType * *(float *)&ptQTask[1].ptPrev;
  if ( *(float *)p_ptParent >= 0.0 )
  {
    if ( *(float *)p_ptParent > 1.0 )
      *p_ptParent = (struct QTask_s *)1065353216;
    *(float *)&ptQTask[6].ptNext = *(double *)&ptQTask[2].tQTaskChildren.ptTail;
  }
  else
  {
    v18 = *(double *)&ptQTask[2].tQTaskChildren.ptTail;
    *p_ptParent = nullptr;
    *(float *)&ptQTask[6].ptNext = v18;
  }
}

// source: f/1/sound/sounddefgraph.c:836  [anchor-hash]
void __cdecl SoundDefGraph_Open()
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

  v0 = QTask_NewQTaskType("SoundDefGraph", 416, SoundDefBase_eQTaskType, 512, 0);
  SoundDefGraph_eQTaskType = v0;
  SoundDefGraph_eCreateQTaskType = v0;
  QTask_LinkQTaskEventHandlerFn(v0, 0, SoundDefGraph_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 1, SoundDefGraph_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 2, SoundDefGraph_DeleteHandler);
  QTask_LinkQTaskEventHandlerFn(v0, Microphone_eTriggerEvent, SoundDefGraph_MicTriggerHandler);
  v1 = SoundSys_eSaveQTaskEvent;
  if ( SoundSys_eSaveQTaskEvent == 512 )
  {
    v1 = QTask_NewQTaskEventFn(0, &g_zFileName.zMenuResourcePath[16]);
    v0 = SoundDefGraph_eQTaskType;
    SoundSys_eSaveQTaskEvent = v1;
  }
  QTask_LinkQTaskEventHandlerFn(v0, v1, SoundDefGraph_SaveHandler);
  v2 = SoundSys_eFindSoundDefQTaskEvent;
  if ( SoundSys_eFindSoundDefQTaskEvent == 512 )
  {
    v2 = QTask_NewQTaskEventFn(0, (char *)&g_zFileName.iActiveTABItem);
    v0 = SoundDefGraph_eQTaskType;
    SoundSys_eFindSoundDefQTaskEvent = v2;
  }
  QTask_LinkQTaskEventHandlerFn(v0, v2, SoundDefGraph_FindSoundDefHandler);
  v3 = SoundSys_eRequestSoundDefQTaskEvent;
  if ( SoundSys_eRequestSoundDefQTaskEvent == 512 )
  {
    v3 = QTask_NewQTaskEventFn(0, (char *)&g_zFileName.aptSelectableTABItems[31]);
    v0 = SoundDefGraph_eQTaskType;
    SoundSys_eRequestSoundDefQTaskEvent = v3;
  }
  QTask_LinkQTaskEventHandlerFn(
    v0,
    v3,
    (void (__cdecl *)(struct QTask_s *, void *))SoundDefGraph_RequestSoundDefHandler);
  v4 = SoundSys_eSetPositionQTaskEvent;
  if ( SoundSys_eSetPositionQTaskEvent == 512 )
  {
    v4 = QTask_NewQTaskEventFn(0, (char *)&g_zFileName.aptSelectableTABItems[26]);
    v0 = SoundDefGraph_eQTaskType;
    SoundSys_eSetPositionQTaskEvent = v4;
  }
  QTask_LinkQTaskEventHandlerFn(v0, v4, (void (__cdecl *)(struct QTask_s *, void *))SoundDefGraph_SetPositionHandler);
  v5 = SoundSys_eSetVolumeQTaskEvent;
  if ( SoundSys_eSetVolumeQTaskEvent == 512 )
  {
    v5 = QTask_NewQTaskEventFn(0, (char *)&g_zFileName.aptSelectableTABItems[18]);
    v0 = SoundDefGraph_eQTaskType;
    SoundSys_eSetVolumeQTaskEvent = v5;
  }
  QTask_LinkQTaskEventHandlerFn(v0, v5, SoundDefGraph_SetVolumeHandler);
  v6 = SoundSys_eSetPitchQTaskEvent;
  if ( SoundSys_eSetPitchQTaskEvent == 512 )
  {
    v6 = QTask_NewQTaskEventFn(0, (char *)&g_zFileName.aptSelectableTABItems[14]);
    v0 = SoundDefGraph_eQTaskType;
    SoundSys_eSetPitchQTaskEvent = v6;
  }
  QTask_LinkQTaskEventHandlerFn(v0, v6, SoundDefGraph_SetPitchHandler);
  v7 = SoundSys_eSetRelativeToMicrophoneQTaskEvent;
  if ( SoundSys_eSetRelativeToMicrophoneQTaskEvent == 512 )
  {
    v7 = QTask_NewQTaskEventFn(0, (char *)&g_zFileName.aptSelectableTABItems[6]);
    v0 = SoundDefGraph_eQTaskType;
    SoundSys_eSetRelativeToMicrophoneQTaskEvent = v7;
  }
  QTask_LinkQTaskEventHandlerFn(
    v0,
    v7,
    (void (__cdecl *)(struct QTask_s *, void *))SoundDefGraph_SetRelativeToMicrophoneHandler__sounddefgraph);
  v8 = SoundSys_eGetSoundRadiusQTaskEvent;
  if ( SoundSys_eGetSoundRadiusQTaskEvent == 512 )
  {
    v8 = QTask_NewQTaskEventFn(0, (char *)&g_zFileName.aptSelectableTABItems[2]);
    v0 = SoundDefGraph_eQTaskType;
    SoundSys_eGetSoundRadiusQTaskEvent = v8;
  }
  QTask_LinkQTaskEventHandlerFn(v0, v8, (void (__cdecl *)(struct QTask_s *, void *))SoundDefGraph_GetSoundRadiusHandler);
  v9 = SoundSys_eGetSoundLengthQTaskEvent;
  if ( SoundSys_eGetSoundLengthQTaskEvent == 512 )
  {
    v9 = QTask_NewQTaskEventFn(0, (char *)&g_zFileName.aptSelectableItems[30]);
    v0 = SoundDefGraph_eQTaskType;
    SoundSys_eGetSoundLengthQTaskEvent = v9;
  }
  QTask_LinkQTaskEventHandlerFn(v0, v9, SoundDefGraph_GetSoundLengthHandler);
}

int __cdecl SoundDefGraph_Close(int a1)
{
  QTask_DeleteQTaskType(SoundDefGraph_eQTaskType);
  SoundDefGraph_eQTaskType = 512;
  SoundDefGraph_eCreateQTaskType = 512;
  return 512;
}

_BYTE *__cdecl String_Tokenize(_BYTE *a1, char *a2)
{
  BOOL v3; // ebp
  int v4; // eax
  char v5; // dl
  bool v6; // zf
  _BYTE *v7; // ebx
  int v8; // ecx
  char v10; // cl
  _BYTE *v11; // esi
  int i; // ecx

  v3 = 0;
  v4 = strlen(a2);
  if ( a1 )
    dword_7B778E4 = (int)a1;
  else
    a1 = (_BYTE *)dword_7B778E4;
  v5 = *a1;
  v6 = *a1 == 0;
  v7 = a1;
  dword_7B778E8 = (int)a1;
  if ( v6 )
    return v7 == a1 ? nullptr : v7;
  while ( 1 )
  {
    if ( v5 == 34 )
      v3 = !v3;
    if ( !v3 )
    {
      v8 = 0;
      if ( v4 > 0 )
        break;
    }
LABEL_11:
    v5 = *++a1;
    dword_7B778E4 = (int)a1;
    if ( !v5 )
      return v7 == a1 ? nullptr : v7;
  }
  while ( v5 != a2[v8] )
  {
    if ( ++v8 >= v4 )
      goto LABEL_11;
  }
  *a1 = 0;
  v10 = a1[1];
  v11 = a1 + 1;
  dword_7B778E4 = (int)v11;
  if ( v10 )
  {
    for ( i = 0; i < v4; ++i )
    {
      if ( *v11 == a2[i] )
        ++v11;
    }
    dword_7B778E4 = (int)v11;
  }
  return v7;
}

int __cdecl String_GetWordEx(int a1, _BYTE *a2, _DWORD *a3, int a4, int a5)
{
  int v5; // ebp
  int v6; // esi
  int v7; // ecx
  char v8; // dl
  char v9; // dl
  int v10; // ecx
  char v11; // al
  char v12; // al
  int v13; // ecx
  char v14; // al
  int v15; // ecx
  int v16; // ecx
  char v17; // dl
  char v18; // al
  char v19; // al
  int v21; // eax
  int v22; // ebp
  int v23; // esi
  char v24; // dl
  int v25; // ecx
  int v26; // ebp
  char v27; // dl
  int v28; // eax
  int v29; // edx
  char v30; // dl
  char v31; // dl
  int v32; // [esp+8h] [ebp-Ch]
  int v33; // [esp+Ch] [ebp-8h]
  int a4a = *(int *)&a4; // [esp+1Ch] [ebp+8h] ARGSLOT

  v5 = a4;
  v6 = 0;
  v7 = 0;
  if ( !a4 )
    return 0;
  a4a = 0;
  while ( 1 )
  {
    v8 = *(_BYTE *)(v7 + a1);
    if ( v8 != 32 && v8 != 9 && v8 != 10 && v8 != 13 )
      break;
    ++v7;
  }
  v9 = *(_BYTE *)(v7 + a1);
  if ( v9 != 34 )
  {
    v32 = 0;
    v33 = 0;
    if ( v9 < 48 || v9 > 57 )
    {
      if ( v9 == 36 )
      {
        ++v7;
        --v5;
        v33 = 1;
        v32 = 1;
        *a2 = 36;
        v6 = 1;
        if ( !v5 )
          return 0;
      }
    }
    else
    {
      v33 = 1;
      if ( v9 == 48 )
      {
        v24 = *(_BYTE *)(v7 + a1 + 1);
        if ( v24 == 120 || v24 == 88 )
        {
          v25 = v7 + 1;
          v26 = v5 - 1;
          v32 = 1;
          *a2 = 48;
          if ( !v26 )
            return 0;
          v27 = *(_BYTE *)(v25 + a1);
          v7 = v25 + 1;
          v5 = v26 - 1;
          a2[1] = v27;
          v6 = 2;
          if ( !v5 )
            return 0;
        }
      }
    }
    v28 = 0;
    while ( 1 )
    {
      if ( v32 )
      {
        LOBYTE(v29) = *(_BYTE *)(v7 + a1);
        if ( ((char)v29 < 48 || (char)v29 > 57)
          && ((char)v29 < 97 || (char)v29 > 102)
          && ((char)v29 < 65 || (char)v29 > 70) )
        {
          goto LABEL_29;
        }
      }
      else if ( v33 )
      {
        if ( *(_BYTE *)(v7 + a1) == 46 )
        {
          a2[v6++] = 46;
          ++v7;
          if ( !--v5 )
            return 0;
        }
        v30 = *(_BYTE *)(v7 + a1);
        if ( v30 == 101 || v30 == 69 )
        {
          if ( v28 )
            goto LABEL_29;
          a2[v6++] = v30;
          ++v7;
          if ( !--v5 )
            return 0;
          v31 = *(_BYTE *)(v7 + a1);
          if ( v31 == 43 || v31 == 45 )
          {
            a2[v6++] = v31;
            ++v7;
            if ( !--v5 )
              return 0;
          }
          v28 = 1;
        }
        LOBYTE(v29) = *(_BYTE *)(v7 + a1);
        if ( (char)v29 < 48 || (char)v29 > 57 )
          goto LABEL_29;
      }
      else
      {
        v29 = *(unsigned __int8 *)(v7 + a1);
        if ( ((char)v29 < 48 || (char)v29 > 57)
          && ((char)v29 < 97 || (char)v29 > 122)
          && ((char)v29 < 65 || (char)v29 > 90)
          && (_BYTE)v29 != 95
          && (_BYTE)v29 != 46 )
        {
          goto LABEL_29;
        }
      }
      a2[v6++] = v29;
      ++v7;
      if ( !--v5 )
        return 0;
      a4a = 1;
    }
  }
  v10 = v7 + 1;
  if ( !a5 )
  {
    *a2 = 34;
    v21 = *(unsigned __int8 *)(v10 + a1);
    v22 = v5 - 1;
    v23 = 1;
    if ( (_BYTE)v21 != 34 )
    {
      while ( v22 )
      {
        if ( !(_BYTE)v21 )
          break;
        if ( (_BYTE)v21 == 92 )
        {
          a2[v23++] = 92;
          ++v10;
          if ( !--v22 )
            break;
          LOBYTE(v21) = *(_BYTE *)(v10 + a1);
          if ( !(_BYTE)v21 )
            break;
        }
        a2[v23] = v21;
        LOBYTE(v21) = *(_BYTE *)(v10 + a1 + 1);
        ++v23;
        ++v10;
        --v22;
        if ( (_BYTE)v21 == 34 )
          goto LABEL_39;
      }
      return 0;
    }
LABEL_39:
    if ( v22 )
    {
      a2[v23] = *(_BYTE *)(v10 + a1);
      v6 = v23 + 1;
      goto LABEL_28;
    }
    return 0;
  }
  v11 = *(_BYTE *)(v10 + a1);
  if ( v11 != 34 )
  {
    while ( v5 && v11 )
    {
      if ( v11 == 92 )
      {
        v12 = *(_BYTE *)(v10 + a1 + 1);
        v13 = v10 + 1;
        --v5;
        switch ( v12 )
        {
          case 'X':
          case 'x':
            v14 = *(_BYTE *)(v13 + a1 + 1);
            v15 = v13 + 1;
            if ( v14 > 57 )
              v14 += 9;
            v16 = v15 + 1;
            v17 = 16 * v14;
            v18 = *(_BYTE *)(v16 + a1);
            if ( v18 <= 57 )
              v19 = v18 & 0xF;
            else
              v19 = (v18 & 0xF) + 9;
            a2[v6++] = v19 | v17;
            v10 = v16 + 1;
            break;
          case 'b':
            a2[v6++] = 8;
            v10 = v13 + 1;
            break;
          case 'n':
            a2[v6++] = 10;
            v10 = v13 + 1;
            break;
          case 'r':
            a2[v6++] = 13;
            v10 = v13 + 1;
            break;
          case 't':
            a2[v6++] = 9;
            v10 = v13 + 1;
            break;
          default:
            a2[v6++] = v12;
            v10 = v13 + 1;
            break;
        }
      }
      else
      {
        a2[v6++] = v11;
        ++v10;
        --v5;
      }
      v11 = *(_BYTE *)(v10 + a1);
      if ( v11 == 34 )
        goto LABEL_28;
    }
    return 0;
  }
LABEL_28:
  v7 = v10 + 1;
  a4a = 1;
LABEL_29:
  a2[v6] = 0;
  if ( a3 )
    *a3 = a1 + v7;
  return a4a;
}

int __cdecl String_GetInteger(int a1, int a2)
{
  char v2; // al
  int result; // eax
  unsigned __int8 *v4; // edx
  int v5; // ecx
  int v6; // eax

  if ( *(_BYTE *)a2 != 36 )
  {
    if ( *(_BYTE *)a2 != 48 )
      return atoi((char *)a2);
    v2 = *(_BYTE *)(a2 + 1);
    if ( v2 != 120 && v2 != 88 )
      return atoi((char *)a2);
    ++a2;
  }
  v4 = (unsigned __int8 *)(a2 + 1);
  v5 = *v4;
  for ( result = 0; (_BYTE)v5; ++v4 )
  {
    v6 = 16 * result;
    if ( (char)v5 <= 57 )
      result = (v5 & 0xF) + v6;
    else
      result = v6 + (v5 & 0xF) + 9;
    LOBYTE(v5) = v4[1];
  }
  return result;
}

double __cdecl String_GetReal(char *a1)
{
  return atof(a1);
}

void __cdecl String_UpperInPlace(char *zString)
{
  char v1; // al

  if ( *zString )
  {
    do
    {
      v1 = *zString;
      if ( *zString >= 97 && v1 <= 122 )
        *zString = v1 - 32;
    }
    while ( *++zString );
  }
}

int __cdecl String_Compare(_BYTE *a1, char *a2, int a3)
{
  char *v3; // ebp
  char v5; // al
  bool v6; // zf
  int v7; // eax
  int v8; // eax
  char *v9; // eax
  char v10; // cl
  char v11; // cl
  int i; // edi
  int j; // esi
  int v16; // esi
  int v17; // esi
  char *a2a = *(char * *)&a2; // [esp+14h] [ebp+4h] ARGSLOT

  v3 = a2;
  v5 = *a2;
  v6 = *a2 == 0;
  a2a = nullptr;
  if ( v6 )
    return (int)a2a;
  while ( *a1 )
  {
    if ( _mb_cur_max_6aece0 <= 1 )
      v7 = pctype_6aecec[v5] & 4;
    else
      v7 = isctype(v5, 4);
    if ( v7 && (_mb_cur_max_6aece0 <= 1 ? (v8 = pctype_6aecec[(char)*a1] & 4) : (v8 = isctype((char)*a1, 4)), v8) )
    {
      v9 = nullptr;
      if ( *v3 == 48 )
      {
        do
        {
          v10 = *++v3;
          ++v9;
        }
        while ( v10 == 48 );
      }
      if ( *a1 == 48 )
      {
        do
        {
          v11 = *++a1;
          --v9;
        }
        while ( v11 == 48 );
      }
      if ( !a2a && v9 )
        a2a = v9;
      for ( i = 0; _mb_cur_max_6aece0 <= 1 ? pctype_6aecec[v3[i]] & 4 : isctype(v3[i], 4); ++i )
        ;
      for ( j = 0; _mb_cur_max_6aece0 <= 1 ? pctype_6aecec[(char)a1[j]] & 4 : isctype((char)a1[j], 4); ++j )
        ;
      if ( i != j )
        return i - j;
      if ( i )
      {
        while ( *v3 == *a1 )
        {
          --i;
          ++v3;
          ++a1;
          if ( !i )
            goto LABEL_40;
        }
        return *v3 - (char)*a1;
      }
    }
    else
    {
      if ( a3 )
      {
        v16 = toupper(*v3);
        if ( v16 != toupper((char)*a1) )
        {
          v17 = toupper(*v3);
          return v17 - toupper((char)*a1);
        }
      }
      else if ( *v3 != *a1 )
      {
        return *v3 - (char)*a1;
      }
      ++v3;
      ++a1;
    }
LABEL_40:
    v5 = *v3;
    if ( !*v3 )
      return (int)a2a;
  }
  return 1;
}
