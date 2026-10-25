/* f/1/sound/sounddefsound.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: f/1/sound/sounddefsound.c:48  [size]
struct SoundDefSound_s *__cdecl SoundDefSound_InitSound(
        struct SoundDefSound_s *ptSound)
{
  ptSound->tPos.vX = 0.0;
  ptSound->tPos.vY = 0.0;
  ptSound->tPos.vZ = 0.0;
  ptSound->tRealPos.vX = 0.0;
  ptSound->tRealPos.vY = 0.0;
  ptSound->tRealPos.vZ = 0.0;
  ptSound->tSpeed.vX = 0.0;
  ptSound->tSpeed.vY = 0.0;
  ptSound->tSpeed.vZ = 0.0;
  ptSound->vFalloffEnd = 10.0;
  ptSound->vMinPlayLength = -1.0;
  ptSound->isLooped = 0;
  ptSound->isDefinition = 0;
  ptSound->zSoundDef[0] = 0;
  ptSound->zSound[0] = 0;
  ptSound->nVolumeChannel = -1;
  ptSound->nPitchChannel = -1;
  ptSound->nSoundChannel = -1;
  ptSound->vBaseVolume = 1.0;
  ptSound->vRelativeVolume = 1.0;
  ptSound->vPitch = 1.0;
  ptSound->vFalloffBegin = 1.0;
  ptSound->vViewRadius = 1.0;
  ptSound->tSound.tModify.tAttr.vVolume = 1.0;
  ptSound->tSound.tModify.tAttr.vPitch = 1.0;
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

// source: f/1/sound/sounddefsound.c:88  [size~]
void __cdecl SoundDefSound_MicTriggerHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QReference_s *ptMiddle; // edx
  double v3; // st3
  bool v4; // cf
  unsigned int v5; // eax
  float v6; // [esp+0h] [ebp-Ch]
  float v7; // [esp+4h] [ebp-8h]

  if ( !HIBYTE(ptQTask[6].eQTaskType) || !*((_BYTE *)pxContext + 4) )
  {
    ptMiddle = ptQTask[1].tQTaskRefList.ptMiddle;
    if ( ((unsigned __int8)ptMiddle & 2) == 0
      || (v6 = *(double *)(*(_DWORD *)pxContext + 80) - *(double *)&ptQTask[4].ptParent,
          v7 = *(double *)(*(_DWORD *)pxContext + 88) - *(double *)&ptQTask[5].ptNext,
          v3 = *(double *)(*(_DWORD *)pxContext + 96) - *(double *)&ptQTask[5].tQTaskChildren.ptHead,
          *(float *)&ptQTask[6].ptParent * 4096.0 >= sqrt(v6 * v6 + v7 * v7 + v3 * v3)) )
    {
      v4 = LOBYTE(ptQTask[6].eQTaskType) != 0;
      ptQTask[2].tQTaskRefList.ptMiddle = nullptr;
      ptQTask[1].tQTaskRefList.ptMiddle = (struct QReference_s *)((unsigned int)ptMiddle & 0xFFFFFFEF | (v4 ? 0x10 : 0));
      if ( !SoundSys_isSoundDisabled )
      {
        if ( !ptQTask[1].tQTaskRefList.ptHead )
        {
          v5 = SoundSys_nCurrentID;
          ptQTask[1].tQTaskRefList.ptHead = (struct QReference_s *)SoundSys_nCurrentID;
          SoundSys_nCurrentID = v5 + 1;
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

// source: f/1/sound/sounddefsound.c:159  [size]
void __cdecl SoundDefSound_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  int v2; // eax
  char *v3; // ecx
  char v4; // dl
  char *v5; // eax
  int v6; // edx
  char v7; // cl
  struct QTask_s *ptNext; // eax

  ((void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[0][SoundDefBase_eQTaskType].pfHandler)(
    ptQTask,
    pxContext);
  SoundDefSound_InitSound((struct SoundDefSound_s *)ptQTask);
  if ( pxContext )
  {
    v2 = *(_DWORD *)pxContext;
    ptQTask[6].ptNext = *(struct QTask_s **)(*(_DWORD *)pxContext + 240);
    ptQTask[6].ptPrev = *(struct QTask_s **)(v2 + 244);
    ptQTask[6].tQTaskChildren = *(struct QTaskNodeList_s *)(v2 + 248);
    ptQTask[6].tQTaskRefList = *(struct QReferenceList_s *)(v2 + 260);
    ptQTask[6].ptParent = *(struct QTask_s **)(v2 + 272);
    ptQTask[8].tQTaskRefList.ptTail = *(struct QReference_s **)(v2 + 348);
    LOBYTE(ptQTask[6].eQTaskType) = *(_BYTE *)(v2 + 276);
    v3 = (char *)(v2 + 278);
    HIBYTE(ptQTask[6].eQTaskType) = *((_BYTE *)pxContext + 4);
    do
    {
      v4 = *v3;
      v3[(_DWORD)ptQTask - v2] = *v3;
      ++v3;
    }
    while ( v4 );
    v5 = (char *)(v2 + 310);
    v6 = (char *)&ptQTask[7].tQTaskRefList.ptTail + 2 - v5;
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
    HIBYTE(ptQTask[6].eQTaskType) = 1;
  }
  ptQTask[8].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[9].tQTaskRefList.ptHead = nullptr;
  SoundSys_InitRequest(
    (struct SoundSysRequest_s *)&ptQTask[1].tQTaskChildren.ptTail,
    (char *)&ptQTask[7].tQTaskRefList.ptTail + 2,
    2u);
  if ( !HIBYTE(ptQTask[6].eQTaskType) )
    QTaskList_Register(SoundSys_ptSoundQTaskList, (struct QTaskList_s *)ptQTask);
  memset(&ptQTask[8].ptParent, 0, 0x1Cu);
  QTask_TriggerQTaskEventParent(ptQTask, Attach_eAttachEvent, &ptQTask[8].ptParent);
  ptNext = ptQTask[9].ptNext;
  if ( ptNext )
  {
    qmemcpy(&ptQTask[4].ptParent, ptNext, 0x18u);
    qmemcpy(&ptQTask[2].ptParent, ptNext, 0x18u);
  }
  SoundDefSound_Modify(ptQTask);
}

// source: f/1/sound/sounddefsound.c:236  [size]
void __cdecl SoundDefSound_RunHandler(struct QTask_s *ptQTask)
{
  bool v1; // zf

  qmemcpy(&ptQTask[3].tQTaskChildren.ptTail, &ptQTask[4].tQTaskChildren, 0x18u);
  ptQTask[4].tQTaskChildren.ptHead = nullptr;
  ptQTask[4].tQTaskChildren.ptMiddle = nullptr;
  v1 = LOBYTE(ptQTask[6].eQTaskType) == 0;
  ptQTask[4].tQTaskChildren.ptTail = nullptr;
  ptQTask[4].tQTaskRefList.ptHead = nullptr;
  ptQTask[4].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[4].tQTaskRefList.ptTail = nullptr;
  if ( v1 )
  {
    if ( Sound_GetSampleDuration((struct Sample_s *)ptQTask[1].tQTaskChildren.ptTail) > (double)*(float *)&ptQTask[8].tQTaskRefList.ptMiddle
      || SoundSys_SoundPlaying((struct SoundSysRequest_s *)&ptQTask[1].tQTaskChildren.ptTail) )
    {
      SoundDefSound_Modify(ptQTask);
      *(float *)&ptQTask[8].tQTaskRefList.ptMiddle = 1.0 / (double)(int)SoundSys_nFrequency
                                                   + *(float *)&ptQTask[8].tQTaskRefList.ptMiddle;
    }
    else
    {
      QTask_Delete(ptQTask);
    }
  }
  else
  {
    SoundDefSound_Modify(ptQTask);
  }
}

// source: f/1/sound/sounddefsound.c:283  [size]
void __cdecl SoundDefSound_DeleteHandler(struct QTask_s *ptQTask)
{
  ((void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[2][SoundDefBase_eQTaskType].pfHandler)(ptQTask);
  if ( !HIBYTE(ptQTask[6].eQTaskType) )
    QTaskList_Remove(SoundSys_ptSoundQTaskList, ptQTask);
}

// source: f/1/sound/sounddefsound.c:306  [anchor-strings]
void __cdecl SoundDefSound_SaveHandler(struct QTask_s *ptQTask, void *pxContext)
{
  int i; // ecx
  char *v3; // eax
  char *v4; // edi
  char *v5; // edi
  char zTemp[1024]; // [esp+40h] [ebp-400h] BYREF

  for ( i = 0; i < (int)(*((_DWORD *)pxContext + 1)); ++i )
    strcat(*(char **)pxContext, "  ");
  v3 = "TRUE";
  if ( !LOBYTE(ptQTask[6].eQTaskType) )
    v3 = "FALSE";
  sprintf(
    zTemp,
    "%s(\"%s\", \"%s\", %8.08f, %8.08f, %8.08f, %8.08f, %8.08f, %8.08f, %d, %d, %d, %8.08f, %s",
    &g_zFileName.zMenuResourcePath[144],
    &ptQTask[6].isInMemPool,
    (char *)&ptQTask[7].tQTaskRefList.ptTail + 2,
    *(double *)&ptQTask[5].tQTaskChildren.ptTail,
    *(double *)&ptQTask[5].tQTaskRefList.ptMiddle,
    *(double *)&ptQTask[5].ptParent,
    *(float *)&ptQTask[6].tQTaskChildren.ptMiddle,
    *(float *)&ptQTask[6].tQTaskRefList.ptMiddle,
    *(float *)&ptQTask[6].tQTaskRefList.ptTail,
    ptQTask[6].ptNext,
    ptQTask[6].ptPrev,
    ptQTask[6].tQTaskChildren.ptHead,
    *(float *)&ptQTask[8].tQTaskRefList.ptTail,
    v3);
  strcat(*(char **)pxContext, zTemp);
  v4 = *(char **)pxContext;
  if ( *((_DWORD *)pxContext + 1) )
  {
    v5 = v4 - 1;
    if ( ptQTask == (ptQTask->ptParent->tQTaskChildren.ptTail->ptPrev != nullptr
                   ? ptQTask->ptParent->tQTaskChildren.ptTail
                   : nullptr) )
    {
      while ( *++v5 )
        ;
      *(_WORD *)v5 = g_zSpriteName_0.tQTaskChildren.ptMiddle;
    }
    else
    {
      while ( *++v5 )
        ;
      strcpy(v5, "),\r\n");
    }
  }
  else
  {
    strcat(v4, ");\r\n");
  }
}

// source: f/1/sound/sounddefsound.c:369  [size]
void __cdecl SoundDefSound_FindSoundDefHandler(struct QTask_s *ptQTask, void *pxContext)
{
  if ( !*((_DWORD *)pxContext + 1) && !strcmp(*(char **)pxContext, &ptQTask[6].isInMemPool) )
    *((_DWORD *)pxContext + 1) = ptQTask;
}

// source: f/1/sound/sounddefsound.c:399  [size]
void __cdecl SoundDefSound_RequestSoundDefHandler(struct QTask_s *ptQTask, void *pxContext)
{
  if ( ptQTask[6].isInMemPool )
    *(_DWORD *)pxContext = (char *)ptQTask + 278;
}

// source: f/1/sound/sounddefsound.c:424  [anchor-mhash]
void __cdecl SoundDefSound_SetPositionHandler(struct QTask_s *ptQTask, void *pxContext)
{
  qmemcpy(&ptQTask[4].ptParent, pxContext, 0x18u);
  qmemcpy(&ptQTask[2].ptParent, pxContext, 0x18u);
  ptQTask[4].tQTaskChildren.ptHead = nullptr;
  ptQTask[4].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[4].tQTaskChildren.ptTail = nullptr;
  ptQTask[4].tQTaskRefList.ptHead = nullptr;
  ptQTask[4].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[4].tQTaskRefList.ptTail = nullptr;
}

// source: f/1/sound/sounddefsound.c:444  [size]
void __cdecl SoundDefSound_SetSectorHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ptQTask[9].tQTaskRefList.ptHead = (struct QReference_s *)pxContext;
}

// source: f/1/sound/sounddefsound.c:460  [size]
void __cdecl SoundDefSound_SetVolumeHandler(struct QTask_s *ptQTask, void *pxContext)
{
  if ( *(float *)pxContext >= 0.0 )
    ptQTask[6].tQTaskChildren.ptMiddle = *(struct QTask_s **)pxContext;
  if ( *((float *)pxContext + 1) >= 0.0 )
    ptQTask[6].tQTaskChildren.ptTail = *((struct QTask_s **)pxContext + 1);
}

// source: f/1/sound/sounddefsound.c:489  [size]
void __cdecl SoundDefSound_SetPitchHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ptQTask[6].tQTaskRefList.ptHead = *(struct QReference_s **)pxContext;
}

// source: f/1/sound/sounddefsound.c:510  [size]
void __cdecl SoundDefSound_SetRelativeToMicrophoneHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QReference_s *ptMiddle; // ecx

  ptMiddle = ptQTask[1].tQTaskRefList.ptMiddle;
  if ( *(_BYTE *)pxContext )
    ptQTask[1].tQTaskRefList.ptMiddle = (struct QReference_s *)((unsigned int)ptMiddle & 0xFFFFFFFD);
  else
    ptQTask[1].tQTaskRefList.ptMiddle = (struct QReference_s *)((unsigned int)ptMiddle | 2);
}

// source: f/1/sound/sounddefsound.c:538  [size]
void __cdecl SoundDefSound_GetSoundRadiusHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *ptParent; // ecx
  long double v3; // st7

  ptParent = ptQTask->ptParent;
  if ( ptParent && ptParent->eQTaskType == SoundDefGroup_eCreateQTaskType )
    v3 = sqrt(
           *(double *)&ptQTask[5].tQTaskChildren.ptTail * *(double *)&ptQTask[5].tQTaskChildren.ptTail
         + *(double *)&ptQTask[5].tQTaskRefList.ptMiddle * *(double *)&ptQTask[5].tQTaskRefList.ptMiddle
         + *(double *)&ptQTask[5].ptParent * *(double *)&ptQTask[5].ptParent)
       + *(float *)&ptQTask[6].ptParent;
  else
    v3 = *(float *)&ptQTask[6].ptParent;
  if ( v3 > *(float *)pxContext )
    *(float *)pxContext = v3;
}

// source: f/1/sound/sounddefsound.c:584  [size]
void __cdecl SoundDefSound_GetSoundLengthHandler(struct QTask_s *ptQTask, void *pxContext)
{
  int v2; // eax

  v2 = (__int64)(Sound_GetSampleDuration((struct Sample_s *)ptQTask[1].tQTaskChildren.ptTail)
               * (double)(int)SoundSys_nFrequency);
  if ( v2 > (int)(*(_DWORD *)pxContext) )
    *(_DWORD *)pxContext = v2;
}

// source: f/1/sound/sounddefsound.c:618  [anchor-mhash]
void __cdecl SoundDefSound_UpdateAttachmentHandler(struct QTask_s *ptQTask)
{
  double *ptNext; // edx
  double v2; // rt0
  double tDelta_16; // [esp+18h] [ebp-8h]

  ptNext = (double *)ptQTask[9].ptNext;
  tDelta_16 = ptNext[2] - *(double *)&ptQTask[5].tQTaskChildren.ptHead;
  v2 = ptNext[1] - *(double *)&ptQTask[5].ptNext;
  *(double *)&ptQTask[4].tQTaskChildren.ptHead = *ptNext
                                               - *(double *)&ptQTask[4].ptParent
                                               + *(double *)&ptQTask[4].tQTaskChildren.ptHead;
  *(double *)&ptQTask[4].tQTaskChildren.ptTail = v2 + *(double *)&ptQTask[4].tQTaskChildren.ptTail;
  *(double *)&ptQTask[4].tQTaskRefList.ptMiddle = tDelta_16 + *(double *)&ptQTask[4].tQTaskRefList.ptMiddle;
  qmemcpy(&ptQTask[4].ptParent, ptNext, 0x18u);
  qmemcpy(&ptQTask[2].ptParent, ptNext, 0x18u);
}

// source: f/1/sound/sounddefsound.c:644  [size]
unsigned __int16 __cdecl SoundDefSound_GetCreateQTaskType()
{
  return SoundDefSound_eCreateQTaskType;
}

// source: f/1/sound/sounddefsound.c:659  [size]
void __cdecl SoundDefSound_SetCreateQTaskType(unsigned __int16 eQTaskType)
{
  SoundDefSound_eCreateQTaskType = eQTaskType;
}

// source: f/1/sound/sounddefsound.c:676  [size]
struct Result_s *__cdecl SoundDefSound_ScriptParseCB(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct Result_s Rs; };
    struct { char igi2_o1[24]; struct SoundSysCreateSoundContext_t tCreateContext; };
    struct { char igi2_o2[32]; struct SoundDefSound_s tSoundDefSoundTemplate; };
    char igi2_extent[416];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)

  if ( AppContext_tAppContext.isServer )
  {
    igi2_frame.Rs.nResult = 0;
    HIDWORD(igi2_frame.Rs.vResult) = 0;
  }
  else
  {
    igi2_frame.tCreateContext.ptSoundDef = (struct QTask_s *)&igi2_frame.tSoundDefSoundTemplate;
    igi2_frame.tCreateContext.isDefinition = 1;
    SoundDefSound_InitSound(&igi2_frame.tSoundDefSoundTemplate);
    if ( ptArgList->isQVM )
    {
      igi2_frame.tSoundDefSoundTemplate.zSoundDef[0] = 0;
      QVM_EvalArg(igi2_frame.tSoundDefSoundTemplate.zSoundDef, 32, ptArgList, 0, 3);
    }
    else
    {
      Expression_EvalString(*ptArgList->aptExpression, igi2_frame.tSoundDefSoundTemplate.zSoundDef, 32);
    }
    if ( ptArgList->isQVM )
    {
      igi2_frame.tSoundDefSoundTemplate.zSound[0] = 0;
      QVM_EvalArg(igi2_frame.tSoundDefSoundTemplate.zSound, 32, ptArgList, 1, 3);
    }
    else
    {
      Expression_EvalString(ptArgList->aptExpression[1], igi2_frame.tSoundDefSoundTemplate.zSound, 32);
    }
    igi2_frame.tSoundDefSoundTemplate.tPos.vX = Script_EvalArgFloat(ptArgList, 2);
    igi2_frame.tSoundDefSoundTemplate.tPos.vY = Script_EvalArgFloat(ptArgList, 3);
    igi2_frame.tSoundDefSoundTemplate.tPos.vZ = Script_EvalArgFloat(ptArgList, 4);
    igi2_frame.tSoundDefSoundTemplate.vBaseVolume = Script_EvalArgFloat(ptArgList, 5);
    igi2_frame.tSoundDefSoundTemplate.vFalloffBegin = Script_EvalArgFloat(ptArgList, 6);
    igi2_frame.tSoundDefSoundTemplate.vFalloffEnd = Script_EvalArgFloat(ptArgList, 7);
    if ( igi2_frame.tSoundDefSoundTemplate.vFalloffBegin == 0.0 )
      igi2_frame.tSoundDefSoundTemplate.vFalloffBegin = igi2_frame.tSoundDefSoundTemplate.vFalloffEnd * 0.019999999552965164;
    igi2_frame.tSoundDefSoundTemplate.nVolumeChannel = Script_EvalArgInt(ptArgList, 8);
    igi2_frame.tSoundDefSoundTemplate.nPitchChannel = Script_EvalArgInt(ptArgList, 9);
    igi2_frame.tSoundDefSoundTemplate.nSoundChannel = Script_EvalArgInt(ptArgList, 10);
    igi2_frame.tSoundDefSoundTemplate.vMinPlayLength = Script_EvalArgFloat(ptArgList, 11);
    igi2_frame.tSoundDefSoundTemplate.isLooped = Script_EvalArgInt(ptArgList, 12);
    igi2_frame.tSoundDefSoundTemplate.isDefinition = 1;
    QTask_NewFn((struct QTask_s *)pxContext, SoundDefSound_eCreateQTaskType, &igi2_frame.tCreateContext);
    igi2_frame.Rs.nResult = 13;
    HIDWORD(igi2_frame.Rs.vResult) = 1076494336;
  }
  igi2_frame.Rs.zResult = (char *)&g_zInitialValue;
  LODWORD(igi2_frame.Rs.vResult) = 0;
  qmemcpy(retstr, &igi2_frame.Rs, sizeof(struct Result_s));
  return retstr;
}

// source: f/1/sound/sounddefsound.c:753  [size]
void __cdecl SoundDefSound_Modify(struct QTask_s *ptQTask)
{
  __int16 v1; // ax
  struct SoundSysChannelList_t *ptChannelList; // ecx
  struct QTask_s *ptParent; // esi
  void (__cdecl *pfHandler)(struct QTask_s *, struct SoundSysParameterList_t *); // eax
  struct QTask_s *ptNext; // eax
  struct QTask_s *ptPrev; // eax
  struct QTask_s *ptHead; // eax
  char *pzChannelData; // ebp
  double v9; // st7
  double v10; // st7
  struct SoundSysParameterList_t tParameterList; // [esp+4h] [ebp-Ch] BYREF

  v1 = SoundSys_eUpdateParameterListQTaskEvent;
  ptChannelList = nullptr;
  ptParent = ptQTask->ptParent;
  memset(&tParameterList, 0, sizeof(tParameterList));
  if ( SoundSys_eUpdateParameterListQTaskEvent == 512 )
  {
    v1 = QTask_NewQTaskEventFn(0, (char *)&g_zFileName.nRealFadeCount);
    ptChannelList = tParameterList.ptChannelList;
    SoundSys_eUpdateParameterListQTaskEvent = v1;
  }
  pfHandler = (void (__cdecl *)(struct QTask_s *, struct SoundSysParameterList_t *))QTask_aatQTaskFinalEvent[v1][ptParent->eQTaskType].pfHandler;
  if ( pfHandler )
  {
    pfHandler(ptParent, &tParameterList);
    ptChannelList = tParameterList.ptChannelList;
  }
  if ( ptChannelList )
  {
    ptNext = ptQTask[6].ptNext;
    if ( ptNext != (struct QTask_s *)-1 )
      ptQTask[1].ptParent = (struct QTask_s *)LODWORD(ptChannelList->auData[(_DWORD)ptNext].vChannelData);
    ptPrev = ptQTask[6].ptPrev;
    if ( ptPrev != (struct QTask_s *)-1 )
      *(_DWORD *)&ptQTask[1].eQTaskType = LODWORD(ptChannelList->auData[(_DWORD)ptPrev].vChannelData);
    ptHead = ptQTask[6].tQTaskChildren.ptHead;
    if ( ptHead != (struct QTask_s *)-1 )
    {
      pzChannelData = ptChannelList->auData[(_DWORD)ptHead].pzChannelData;
      if ( pzChannelData )
      {
        if ( strcmp(
               ptChannelList->auData[(_DWORD)ptHead].pzChannelData,
               (char *)&ptQTask[7].tQTaskRefList.ptTail + 2) )
        {
          strcpy((char *)&ptQTask[7].tQTaskRefList.ptTail + 2, pzChannelData);
          SoundSys_InitRequest(
            (struct SoundSysRequest_s *)&ptQTask[1].tQTaskChildren.ptTail,
            (char *)&ptQTask[7].tQTaskRefList.ptTail + 2,
            (unsigned int)ptQTask[1].tQTaskRefList.ptMiddle);
        }
      }
    }
  }
  if ( *(float *)&ptQTask[6].tQTaskChildren.ptMiddle >= 0.0 )
  {
    if ( *(float *)&ptQTask[6].tQTaskChildren.ptMiddle > 1.0 )
      ptQTask[6].tQTaskChildren.ptMiddle = (struct QTask_s *)1065353216;
  }
  else
  {
    ptQTask[6].tQTaskChildren.ptMiddle = nullptr;
  }
  if ( *(float *)&ptQTask[6].tQTaskChildren.ptTail >= 0.0 )
  {
    if ( *(float *)&ptQTask[6].tQTaskChildren.ptTail > 1.0 )
      ptQTask[6].tQTaskChildren.ptTail = (struct QTask_s *)1065353216;
  }
  else
  {
    ptQTask[6].tQTaskChildren.ptTail = nullptr;
  }
  v9 = *(float *)&ptQTask[6].tQTaskChildren.ptTail * *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
  ptQTask[4].ptNext = (struct QTask_s *)ptQTask[8].tQTaskRefList.ptMiddle;
  *(float *)&ptQTask[1].ptParent = v9;
  *(double *)&ptQTask[2].tQTaskChildren.ptHead = *(float *)&ptQTask[6].tQTaskRefList.ptMiddle
                                               * *(float *)&ptQTask[1].ptPrev;
  *(double *)&ptQTask[2].tQTaskChildren.ptTail = *(float *)&ptQTask[6].tQTaskRefList.ptTail
                                               * *(float *)&ptQTask[1].ptPrev;
  *(float *)&ptQTask[1].eQTaskType = *(float *)&ptQTask[6].tQTaskRefList.ptHead * *(float *)&ptQTask[1].eQTaskType;
  if ( *(float *)&ptQTask[1].ptParent >= 0.0 )
  {
    if ( *(float *)&ptQTask[1].ptParent > 1.0 )
      ptQTask[1].ptParent = (struct QTask_s *)1065353216;
    *(float *)&ptQTask[6].ptParent = *(double *)&ptQTask[2].tQTaskChildren.ptTail;
  }
  else
  {
    v10 = *(double *)&ptQTask[2].tQTaskChildren.ptTail;
    ptQTask[1].ptParent = nullptr;
    *(float *)&ptQTask[6].ptParent = v10;
  }
}

// source: f/1/sound/sounddefsound.c:834  [anchor-strings]
void __cdecl SoundDefSound_Open()
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
  __int16 v10; // ax

  v0 = QTask_NewQTaskType("SoundDefSound", 384, SoundDefBase_eQTaskType, 512, 0);
  SoundDefSound_eQTaskType = v0;
  SoundDefSound_eCreateQTaskType = v0;
  QTask_LinkQTaskEventHandlerFn(v0, 0, SoundDefSound_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 1, SoundDefSound_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 2, SoundDefSound_DeleteHandler);
  QTask_LinkQTaskEventHandlerFn(v0, Microphone_eTriggerEvent, SoundDefSound_MicTriggerHandler);
  v1 = SoundSys_eSaveQTaskEvent;
  if ( SoundSys_eSaveQTaskEvent == 512 )
  {
    v1 = QTask_NewQTaskEventFn(0, &g_zFileName.zMenuResourcePath[16]);
    v0 = SoundDefSound_eQTaskType;
    SoundSys_eSaveQTaskEvent = v1;
  }
  QTask_LinkQTaskEventHandlerFn(v0, v1, SoundDefSound_SaveHandler);
  v2 = SoundSys_eFindSoundDefQTaskEvent;
  if ( SoundSys_eFindSoundDefQTaskEvent == 512 )
  {
    v2 = QTask_NewQTaskEventFn(0, (char *)&g_zFileName.iActiveTABItem);
    v0 = SoundDefSound_eQTaskType;
    SoundSys_eFindSoundDefQTaskEvent = v2;
  }
  QTask_LinkQTaskEventHandlerFn(v0, v2, SoundDefSound_FindSoundDefHandler);
  v3 = SoundSys_eRequestSoundDefQTaskEvent;
  if ( SoundSys_eRequestSoundDefQTaskEvent == 512 )
  {
    v3 = QTask_NewQTaskEventFn(0, (char *)&g_zFileName.aptSelectableTABItems[31]);
    v0 = SoundDefSound_eQTaskType;
    SoundSys_eRequestSoundDefQTaskEvent = v3;
  }
  QTask_LinkQTaskEventHandlerFn(
    v0,
    v3,
    (void (__cdecl *)(struct QTask_s *, void *))SoundDefSound_RequestSoundDefHandler);
  v4 = SoundSys_eSetPositionQTaskEvent;
  if ( SoundSys_eSetPositionQTaskEvent == 512 )
  {
    v4 = QTask_NewQTaskEventFn(0, (char *)&g_zFileName.aptSelectableTABItems[26]);
    v0 = SoundDefSound_eQTaskType;
    SoundSys_eSetPositionQTaskEvent = v4;
  }
  QTask_LinkQTaskEventHandlerFn(v0, v4, SoundDefSound_SetPositionHandler);
  v5 = SoundSys_eSetSectorQTaskEvent;
  if ( SoundSys_eSetSectorQTaskEvent == 512 )
  {
    v5 = QTask_NewQTaskEventFn(0, (char *)&g_zFileName.aptSelectableTABItems[22]);
    v0 = SoundDefSound_eQTaskType;
    SoundSys_eSetSectorQTaskEvent = v5;
  }
  QTask_LinkQTaskEventHandlerFn(v0, v5, (void (__cdecl *)(struct QTask_s *, void *))SoundDefSound_SetSectorHandler);
  v6 = SoundSys_eSetVolumeQTaskEvent;
  if ( SoundSys_eSetVolumeQTaskEvent == 512 )
  {
    v6 = QTask_NewQTaskEventFn(0, (char *)&g_zFileName.aptSelectableTABItems[18]);
    v0 = SoundDefSound_eQTaskType;
    SoundSys_eSetVolumeQTaskEvent = v6;
  }
  QTask_LinkQTaskEventHandlerFn(v0, v6, SoundDefSound_SetVolumeHandler);
  v7 = SoundSys_eSetPitchQTaskEvent;
  if ( SoundSys_eSetPitchQTaskEvent == 512 )
  {
    v7 = QTask_NewQTaskEventFn(0, (char *)&g_zFileName.aptSelectableTABItems[14]);
    v0 = SoundDefSound_eQTaskType;
    SoundSys_eSetPitchQTaskEvent = v7;
  }
  QTask_LinkQTaskEventHandlerFn(v0, v7, SoundDefSound_SetPitchHandler);
  v8 = SoundSys_eSetRelativeToMicrophoneQTaskEvent;
  if ( SoundSys_eSetRelativeToMicrophoneQTaskEvent == 512 )
  {
    v8 = QTask_NewQTaskEventFn(0, (char *)&g_zFileName.aptSelectableTABItems[6]);
    v0 = SoundDefSound_eQTaskType;
    SoundSys_eSetRelativeToMicrophoneQTaskEvent = v8;
  }
  QTask_LinkQTaskEventHandlerFn(
    v0,
    v8,
    (void (__cdecl *)(struct QTask_s *, void *))SoundDefSound_SetRelativeToMicrophoneHandler);
  v9 = SoundSys_eGetSoundRadiusQTaskEvent;
  if ( SoundSys_eGetSoundRadiusQTaskEvent == 512 )
  {
    v9 = QTask_NewQTaskEventFn(0, (char *)&g_zFileName.aptSelectableTABItems[2]);
    v0 = SoundDefSound_eQTaskType;
    SoundSys_eGetSoundRadiusQTaskEvent = v9;
  }
  QTask_LinkQTaskEventHandlerFn(v0, v9, (void (__cdecl *)(struct QTask_s *, void *))SoundDefSound_GetSoundRadiusHandler);
  v10 = SoundSys_eGetSoundLengthQTaskEvent;
  if ( SoundSys_eGetSoundLengthQTaskEvent == 512 )
  {
    v10 = QTask_NewQTaskEventFn(0, (char *)&g_zFileName.aptSelectableItems[30]);
    v0 = SoundDefSound_eQTaskType;
    SoundSys_eGetSoundLengthQTaskEvent = v10;
  }
  QTask_LinkQTaskEventHandlerFn(v0, v10, SoundDefSound_GetSoundLengthHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, Attach_eUpdateAttachmentEvent, SoundDefSound_UpdateAttachmentHandler);
}

// source: f/1/sound/sounddefsound.c:865  [size]
void __cdecl SoundDefSound_Close()
{
  QTask_DeleteQTaskType(SoundDefSound_eQTaskType);
  SoundDefSound_eQTaskType = 512;
  SoundDefSound_eCreateQTaskType = 512;
}

// source: f/1/sound/sounddefsound.c:883  [size]
unsigned __int16 __cdecl SoundDefSound_GetQTaskType()
{
  return SoundDefSound_eQTaskType;
}
