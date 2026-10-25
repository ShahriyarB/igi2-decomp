/* f/1/sound/sounddefgroup.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: f/1/sound/sounddefgroup.c:45  [anchor-mhash]
void __cdecl SoundDefGroup_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  int v2; // edx
  char *v3; // eax
  char *v4; // edx
  char v5; // cl

  ptQTask[2].ptNext = nullptr;
  ptQTask[2].ptPrev = nullptr;
  ptQTask[2].tQTaskChildren.ptHead = nullptr;
  ptQTask[2].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[2].tQTaskChildren.ptTail = nullptr;
  ptQTask[2].tQTaskRefList.ptHead = nullptr;
  if ( pxContext )
  {
    v2 = *(_DWORD *)pxContext;
    LOBYTE(ptQTask[1].ptNext) = *((_BYTE *)pxContext + 4);
    v3 = (char *)(v2 + 41);
    v4 = (char *)ptQTask - v2;
    do
    {
      v5 = *v3;
      v3[(_DWORD)v4] = *v3;
      ++v3;
    }
    while ( v5 );
  }
  else
  {
    BYTE1(ptQTask[1].ptNext) = 0;
    LOBYTE(ptQTask[1].ptNext) = 1;
  }
}

// source: f/1/sound/sounddefgroup.c:90  [anchor-mhash]
void __cdecl SoundDefGroup_RunHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptHead; // ecx
  int v2; // edx
  struct QTask_s *v3; // eax
  void (__cdecl *pfHandler)(struct QTask_s *); // eax
  int v5; // edx
  struct QTask_s *v6; // eax

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
  v6 = ptQTask->tQTaskChildren.ptHead;
  if ( (!v6->ptNext || !v6) && !LOBYTE(ptQTask[1].ptNext) )
    QTask_Delete(ptQTask);
}

// source: f/1/sound/sounddefgroup.c:123  [size]
void __cdecl SoundDefGroup_DeleteHandler(struct QTask_s *ptQTask)
{
  ;
}

// source: f/1/sound/sounddefgroup.c:147  [anchor-strings]
void __cdecl SoundDefGroup_SaveHandler(struct QTask_s *ptQTask, void *pxContext)
{
  int i; // ecx
  struct QTask_s *ptHead; // eax
  struct QTask_s *v4; // esi
  __int16 v5; // ax
  struct QTask_s *v6; // ecx
  int v7; // edx
  void (__cdecl *pfHandler)(struct QTask_s *, void *); // ecx
  char *v9; // edi
  int v10; // eax
  char *v11; // edi
  char zTemp[1024]; // [esp+Ch] [ebp-400h] BYREF

  for ( i = 0; i < (int)(*((_DWORD *)pxContext + 1)); ++i )
    strcat(*(char **)pxContext, "  ");
  sprintf(zTemp, "%s(\"%s\"", &g_zFileName.zMenuResourcePath[156], (char *)&ptQTask[1].ptNext + 1);
  strcat(*(char **)pxContext, zTemp);
  ++*((_DWORD *)pxContext + 1);
  ptHead = ptQTask->tQTaskChildren.ptHead;
  if ( ptHead->ptNext )
  {
    if ( ptHead )
    {
      strcat(*(char **)pxContext, ",\r\n");
      v4 = ptQTask->tQTaskChildren.ptHead;
      if ( v4->ptNext )
      {
        if ( v4 )
        {
          v5 = SoundSys_eSaveQTaskEvent;
          do
          {
            if ( v4->ptNext )
              v6 = v4->ptNext->ptNext != nullptr ? v4->ptNext : nullptr;
            else
              v6 = nullptr;
            v7 = QTask_nProtectedQTaskStackOffset;
            QTask_atProtectedQTaskStack[QTask_nProtectedQTaskStackOffset].ptQTask = v6;
            QTask_nProtectedQTaskStackOffset = v7 + 1;
            if ( v5 == 512 )
            {
              v5 = QTask_NewQTaskEventFn(0, &g_zFileName.zMenuResourcePath[16]);
              SoundSys_eSaveQTaskEvent = v5;
            }
            pfHandler = (void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[v5][v4->eQTaskType].pfHandler;
            if ( pfHandler )
            {
              pfHandler(v4, pxContext);
              v5 = SoundSys_eSaveQTaskEvent;
            }
            v4 = (struct QTask_s *)dword_849C7DC[QTask_nProtectedQTaskStackOffset--];
          }
          while ( v4 );
        }
      }
    }
  }
  v9 = *(char **)pxContext;
  v10 = *((_DWORD *)pxContext + 1) - 1;
  *((_DWORD *)pxContext + 1) = v10;
  if ( v10 )
  {
    v11 = v9 - 1;
    if ( ptQTask == (ptQTask->ptParent->tQTaskChildren.ptTail->ptPrev != nullptr
                   ? ptQTask->ptParent->tQTaskChildren.ptTail
                   : nullptr) )
    {
      while ( *++v11 )
        ;
      *(_WORD *)v11 = g_zSpriteName_0.tQTaskChildren.ptMiddle;
    }
    else
    {
      while ( *++v11 )
        ;
      strcpy(v11, "),\r\n");
    }
  }
  else
  {
    strcat(v9, ");\r\n");
  }
}

// source: f/1/sound/sounddefgroup.c:213  [anchor-mhash]
void __cdecl SoundDefGroup_UpdateParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  __int16 v2; // ax
  struct QTask_s *ptParent; // esi
  void (__cdecl *pfHandler)(struct QTask_s *, void *); // eax

  v2 = SoundSys_eUpdateParameterListQTaskEvent;
  ptParent = ptQTask->ptParent;
  if ( SoundSys_eUpdateParameterListQTaskEvent == 512 )
  {
    v2 = QTask_NewQTaskEventFn(0, (char *)&g_zFileName.nRealFadeCount);
    SoundSys_eUpdateParameterListQTaskEvent = v2;
  }
  pfHandler = (void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[v2][ptParent->eQTaskType].pfHandler;
  if ( pfHandler )
    pfHandler(ptParent, pxContext);
  if ( !*(_DWORD *)pxContext )
    *(_DWORD *)pxContext = ptQTask + 2;
}

// source: f/1/sound/sounddefgroup.c:245  [anchor-mhash]
void __cdecl SoundDefGroup_FindSoundDefHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *ptHead; // esi
  __int16 v3; // ax
  struct QTask_s *v4; // ecx
  int v5; // edx
  void (__cdecl *pfHandler)(struct QTask_s *, void *); // ecx

  if ( !*((_DWORD *)pxContext + 1) )
  {
    if ( !strcmp(*(char **)pxContext, (char *)&ptQTask[1].ptNext + 1) )
    {
      *((_DWORD *)pxContext + 1) = ptQTask;
    }
    else
    {
      ptHead = ptQTask->tQTaskChildren.ptHead;
      if ( ptHead->ptNext && ptHead )
      {
        v3 = SoundSys_eFindSoundDefQTaskEvent;
        do
        {
          if ( ptHead->ptNext )
            v4 = ptHead->ptNext->ptNext != nullptr ? ptHead->ptNext : nullptr;
          else
            v4 = nullptr;
          v5 = QTask_nProtectedQTaskStackOffset;
          QTask_atProtectedQTaskStack[QTask_nProtectedQTaskStackOffset].ptQTask = v4;
          QTask_nProtectedQTaskStackOffset = v5 + 1;
          if ( v3 == 512 )
          {
            v3 = QTask_NewQTaskEventFn(0, (char *)&g_zFileName.iActiveTABItem);
            SoundSys_eFindSoundDefQTaskEvent = v3;
          }
          pfHandler = (void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[v3][ptHead->eQTaskType].pfHandler;
          if ( pfHandler )
          {
            pfHandler(ptHead, pxContext);
            v3 = SoundSys_eFindSoundDefQTaskEvent;
          }
          ptHead = (struct QTask_s *)dword_849C7DC[QTask_nProtectedQTaskStackOffset--];
        }
        while ( ptHead );
      }
    }
  }
}

// source: f/1/sound/sounddefgroup.c:279  [size]
void __cdecl SoundDefGroup_RequestSoundDefHandler(struct QTask_s *ptQTask, void *pxContext)
{
  if ( BYTE1(ptQTask[1].ptNext) )
    *(_DWORD *)pxContext = (char *)ptQTask + 41;
}

// source: f/1/sound/sounddefgroup.c:304  [size]
void __cdecl SoundDefGroup_SetPositionHandler(struct QTask_s *ptQTask, void *pxContext)
{
  qmemcpy(&ptQTask[2], pxContext, 0x18u);
}

// source: f/1/sound/sounddefgroup.c:322  [size]
void __cdecl SoundDefGroup_SetVolumeHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *ptHead; // esi
  __int16 v3; // ax
  struct QTask_s *v4; // ecx
  int v5; // edx
  void (__cdecl *pfHandler)(struct QTask_s *, void *); // ecx

  ptHead = ptQTask->tQTaskChildren.ptHead;
  if ( ptHead->ptNext && ptHead )
  {
    v3 = SoundSys_eSetVolumeQTaskEvent;
    do
    {
      if ( ptHead->ptNext )
        v4 = ptHead->ptNext->ptNext != nullptr ? ptHead->ptNext : nullptr;
      else
        v4 = nullptr;
      v5 = QTask_nProtectedQTaskStackOffset;
      QTask_atProtectedQTaskStack[QTask_nProtectedQTaskStackOffset].ptQTask = v4;
      QTask_nProtectedQTaskStackOffset = v5 + 1;
      if ( v3 == 512 )
      {
        v3 = QTask_NewQTaskEventFn(0, (char *)&g_zFileName.aptSelectableTABItems[18]);
        SoundSys_eSetVolumeQTaskEvent = v3;
      }
      pfHandler = (void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[v3][ptHead->eQTaskType].pfHandler;
      if ( pfHandler )
      {
        pfHandler(ptHead, pxContext);
        v3 = SoundSys_eSetVolumeQTaskEvent;
      }
      ptHead = (struct QTask_s *)dword_849C7DC[QTask_nProtectedQTaskStackOffset--];
    }
    while ( ptHead );
  }
}

// source: f/1/sound/sounddefgroup.c:336  [size]
void __cdecl SoundDefGroup_SetPitchHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *ptHead; // esi
  __int16 v3; // ax
  struct QTask_s *v4; // ecx
  int v5; // edx
  void (__cdecl *pfHandler)(struct QTask_s *, void *); // ecx

  ptHead = ptQTask->tQTaskChildren.ptHead;
  if ( ptHead->ptNext && ptHead )
  {
    v3 = SoundSys_eSetPitchQTaskEvent;
    do
    {
      if ( ptHead->ptNext )
        v4 = ptHead->ptNext->ptNext != nullptr ? ptHead->ptNext : nullptr;
      else
        v4 = nullptr;
      v5 = QTask_nProtectedQTaskStackOffset;
      QTask_atProtectedQTaskStack[QTask_nProtectedQTaskStackOffset].ptQTask = v4;
      QTask_nProtectedQTaskStackOffset = v5 + 1;
      if ( v3 == 512 )
      {
        v3 = QTask_NewQTaskEventFn(0, (char *)&g_zFileName.aptSelectableTABItems[14]);
        SoundSys_eSetPitchQTaskEvent = v3;
      }
      pfHandler = (void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[v3][ptHead->eQTaskType].pfHandler;
      if ( pfHandler )
      {
        pfHandler(ptHead, pxContext);
        v3 = SoundSys_eSetPitchQTaskEvent;
      }
      ptHead = (struct QTask_s *)dword_849C7DC[QTask_nProtectedQTaskStackOffset--];
    }
    while ( ptHead );
  }
}

// source: f/1/sound/sounddefgroup.c:350  [size]
void __cdecl SoundDefGraph_SetRelativeToMicrophoneHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *ptHead; // esi
  __int16 v3; // ax
  struct QTask_s *v4; // ecx
  int v5; // edx
  void (__cdecl *pfHandler)(struct QTask_s *, void *); // ecx

  ptHead = ptQTask->tQTaskChildren.ptHead;
  if ( ptHead->ptNext && ptHead )
  {
    v3 = SoundSys_eSetRelativeToMicrophoneQTaskEvent;
    do
    {
      if ( ptHead->ptNext )
        v4 = ptHead->ptNext->ptNext != nullptr ? ptHead->ptNext : nullptr;
      else
        v4 = nullptr;
      v5 = QTask_nProtectedQTaskStackOffset;
      QTask_atProtectedQTaskStack[QTask_nProtectedQTaskStackOffset].ptQTask = v4;
      QTask_nProtectedQTaskStackOffset = v5 + 1;
      if ( v3 == 512 )
      {
        v3 = QTask_NewQTaskEventFn(0, (char *)&g_zFileName.aptSelectableTABItems[6]);
        SoundSys_eSetRelativeToMicrophoneQTaskEvent = v3;
      }
      pfHandler = (void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[v3][ptHead->eQTaskType].pfHandler;
      if ( pfHandler )
      {
        pfHandler(ptHead, pxContext);
        v3 = SoundSys_eSetRelativeToMicrophoneQTaskEvent;
      }
      ptHead = (struct QTask_s *)dword_849C7DC[QTask_nProtectedQTaskStackOffset--];
    }
    while ( ptHead );
  }
}

// source: f/1/sound/sounddefgroup.c:364  [size]
void __cdecl SoundDefGroup_GetSoundRadiusHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *ptHead; // esi
  __int16 v3; // ax
  struct QTask_s *v4; // ecx
  int v5; // edx
  void (__cdecl *pfHandler)(struct QTask_s *, void *); // ecx

  ptHead = ptQTask->tQTaskChildren.ptHead;
  if ( ptHead->ptNext && ptHead )
  {
    v3 = SoundSys_eGetSoundRadiusQTaskEvent;
    do
    {
      if ( ptHead->ptNext )
        v4 = ptHead->ptNext->ptNext != nullptr ? ptHead->ptNext : nullptr;
      else
        v4 = nullptr;
      v5 = QTask_nProtectedQTaskStackOffset;
      QTask_atProtectedQTaskStack[QTask_nProtectedQTaskStackOffset].ptQTask = v4;
      QTask_nProtectedQTaskStackOffset = v5 + 1;
      if ( v3 == 512 )
      {
        v3 = QTask_NewQTaskEventFn(0, (char *)&g_zFileName.aptSelectableTABItems[2]);
        SoundSys_eGetSoundRadiusQTaskEvent = v3;
      }
      pfHandler = (void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[v3][ptHead->eQTaskType].pfHandler;
      if ( pfHandler )
      {
        pfHandler(ptHead, pxContext);
        v3 = SoundSys_eGetSoundRadiusQTaskEvent;
      }
      ptHead = (struct QTask_s *)dword_849C7DC[QTask_nProtectedQTaskStackOffset--];
    }
    while ( ptHead );
  }
}

// source: f/1/sound/sounddefgroup.c:378  [size]
void __cdecl SoundDefGroup_GetSoundLengthHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *ptHead; // esi
  __int16 v3; // ax
  struct QTask_s *v4; // ecx
  int v5; // edx
  void (__cdecl *pfHandler)(struct QTask_s *, void *); // ecx

  ptHead = ptQTask->tQTaskChildren.ptHead;
  if ( ptHead->ptNext && ptHead )
  {
    v3 = SoundSys_eGetSoundLengthQTaskEvent;
    do
    {
      if ( ptHead->ptNext )
        v4 = ptHead->ptNext->ptNext != nullptr ? ptHead->ptNext : nullptr;
      else
        v4 = nullptr;
      v5 = QTask_nProtectedQTaskStackOffset;
      QTask_atProtectedQTaskStack[QTask_nProtectedQTaskStackOffset].ptQTask = v4;
      QTask_nProtectedQTaskStackOffset = v5 + 1;
      if ( v3 == 512 )
      {
        v3 = QTask_NewQTaskEventFn(0, (char *)&g_zFileName.aptSelectableItems[30]);
        SoundSys_eGetSoundLengthQTaskEvent = v3;
      }
      pfHandler = (void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[v3][ptHead->eQTaskType].pfHandler;
      if ( pfHandler )
      {
        pfHandler(ptHead, pxContext);
        v3 = SoundSys_eGetSoundLengthQTaskEvent;
      }
      ptHead = (struct QTask_s *)dword_849C7DC[QTask_nProtectedQTaskStackOffset--];
    }
    while ( ptHead );
  }
}

// source: f/1/sound/sounddefgroup.c:398  [anchor-hash]
void __cdecl SoundDefGroup_Open()
{
  unsigned __int16 BaseQTaskType; // ax
  unsigned __int16 v1; // si
  __int16 v2; // ax
  __int16 v3; // ax
  __int16 v4; // ax
  __int16 v5; // ax
  __int16 v6; // ax
  __int16 v7; // ax
  __int16 v8; // ax
  __int16 v9; // ax
  __int16 v10; // ax
  __int16 v11; // ax

  BaseQTaskType = QTask_GetBaseQTaskType();
  v1 = QTask_NewQTaskType("SoundDefGroup", 104, BaseQTaskType, 512, 0);
  SoundDefGroup_eQTaskType = v1;
  SoundDefGroup_eCreateQTaskType = v1;
  QTask_LinkQTaskEventHandlerFn(v1, 0, SoundDefGroup_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 1, SoundDefGroup_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 2, (void (__cdecl *)(struct QTask_s *))SoundDefGroup_DeleteHandler);
  v2 = SoundSys_eSaveQTaskEvent;
  if ( SoundSys_eSaveQTaskEvent == 512 )
  {
    v2 = QTask_NewQTaskEventFn(0, &g_zFileName.zMenuResourcePath[16]);
    v1 = SoundDefGroup_eQTaskType;
    SoundSys_eSaveQTaskEvent = v2;
  }
  QTask_LinkQTaskEventHandlerFn(v1, v2, SoundDefGroup_SaveHandler);
  v3 = SoundSys_eUpdateParameterListQTaskEvent;
  if ( SoundSys_eUpdateParameterListQTaskEvent == 512 )
  {
    v3 = QTask_NewQTaskEventFn(0, (char *)&g_zFileName.nRealFadeCount);
    v1 = SoundDefGroup_eQTaskType;
    SoundSys_eUpdateParameterListQTaskEvent = v3;
  }
  QTask_LinkQTaskEventHandlerFn(v1, v3, SoundDefGroup_UpdateParameterListHandler);
  v4 = SoundSys_eFindSoundDefQTaskEvent;
  if ( SoundSys_eFindSoundDefQTaskEvent == 512 )
  {
    v4 = QTask_NewQTaskEventFn(0, (char *)&g_zFileName.iActiveTABItem);
    v1 = SoundDefGroup_eQTaskType;
    SoundSys_eFindSoundDefQTaskEvent = v4;
  }
  QTask_LinkQTaskEventHandlerFn(v1, v4, SoundDefGroup_FindSoundDefHandler);
  v5 = SoundSys_eRequestSoundDefQTaskEvent;
  if ( SoundSys_eRequestSoundDefQTaskEvent == 512 )
  {
    v5 = QTask_NewQTaskEventFn(0, (char *)&g_zFileName.aptSelectableTABItems[31]);
    v1 = SoundDefGroup_eQTaskType;
    SoundSys_eRequestSoundDefQTaskEvent = v5;
  }
  QTask_LinkQTaskEventHandlerFn(
    v1,
    v5,
    (void (__cdecl *)(struct QTask_s *, void *))SoundDefGroup_RequestSoundDefHandler);
  v6 = SoundSys_eSetPositionQTaskEvent;
  if ( SoundSys_eSetPositionQTaskEvent == 512 )
  {
    v6 = QTask_NewQTaskEventFn(0, (char *)&g_zFileName.aptSelectableTABItems[26]);
    v1 = SoundDefGroup_eQTaskType;
    SoundSys_eSetPositionQTaskEvent = v6;
  }
  QTask_LinkQTaskEventHandlerFn(v1, v6, (void (__cdecl *)(struct QTask_s *, void *))SoundDefGroup_SetPositionHandler);
  v7 = SoundSys_eSetVolumeQTaskEvent;
  if ( SoundSys_eSetVolumeQTaskEvent == 512 )
  {
    v7 = QTask_NewQTaskEventFn(0, (char *)&g_zFileName.aptSelectableTABItems[18]);
    v1 = SoundDefGroup_eQTaskType;
    SoundSys_eSetVolumeQTaskEvent = v7;
  }
  QTask_LinkQTaskEventHandlerFn(v1, v7, SoundDefGroup_SetVolumeHandler);
  v8 = SoundSys_eSetPitchQTaskEvent;
  if ( SoundSys_eSetPitchQTaskEvent == 512 )
  {
    v8 = QTask_NewQTaskEventFn(0, (char *)&g_zFileName.aptSelectableTABItems[14]);
    v1 = SoundDefGroup_eQTaskType;
    SoundSys_eSetPitchQTaskEvent = v8;
  }
  QTask_LinkQTaskEventHandlerFn(v1, v8, SoundDefGroup_SetPitchHandler);
  v9 = SoundSys_eSetRelativeToMicrophoneQTaskEvent;
  if ( SoundSys_eSetRelativeToMicrophoneQTaskEvent == 512 )
  {
    v9 = QTask_NewQTaskEventFn(0, (char *)&g_zFileName.aptSelectableTABItems[6]);
    v1 = SoundDefGroup_eQTaskType;
    SoundSys_eSetRelativeToMicrophoneQTaskEvent = v9;
  }
  QTask_LinkQTaskEventHandlerFn(v1, v9, SoundDefGraph_SetRelativeToMicrophoneHandler);
  v10 = SoundSys_eGetSoundRadiusQTaskEvent;
  if ( SoundSys_eGetSoundRadiusQTaskEvent == 512 )
  {
    v10 = QTask_NewQTaskEventFn(0, (char *)&g_zFileName.aptSelectableTABItems[2]);
    v1 = SoundDefGroup_eQTaskType;
    SoundSys_eGetSoundRadiusQTaskEvent = v10;
  }
  QTask_LinkQTaskEventHandlerFn(v1, v10, SoundDefGroup_GetSoundRadiusHandler);
  v11 = SoundSys_eGetSoundLengthQTaskEvent;
  if ( SoundSys_eGetSoundLengthQTaskEvent == 512 )
  {
    v11 = QTask_NewQTaskEventFn(0, (char *)&g_zFileName.aptSelectableItems[30]);
    v1 = SoundDefGroup_eQTaskType;
    SoundSys_eGetSoundLengthQTaskEvent = v11;
  }
  QTask_LinkQTaskEventHandlerFn(v1, v11, SoundDefGroup_GetSoundLengthHandler);
}

// source: f/1/sound/sounddefgroup.c:427  [size]
void __cdecl SoundDefGroup_Close()
{
  QTask_DeleteQTaskType(SoundDefGroup_eQTaskType);
  SoundDefGroup_eQTaskType = 512;
  SoundDefGroup_eCreateQTaskType = 512;
}

// source: f/1/sound/sounddefgroup.c:444  [size]
unsigned __int16 __cdecl SoundDefGroup_GetQTaskType()
{
  return SoundDefGroup_eQTaskType;
}

// source: f/1/sound/sounddefgroup.c:459  [size]
unsigned __int16 __cdecl SoundDefGroup_GetCreateQTaskType()
{
  return SoundDefGroup_eCreateQTaskType;
}

// source: f/1/sound/sounddefgroup.c:474  [size]
void __cdecl SoundDefGroup_SetCreateQTaskType(unsigned __int16 eQTaskType)
{
  SoundDefGroup_eCreateQTaskType = eQTaskType;
}

// source: f/1/sound/sounddefgroup.c:491  [size]
struct Result_s *__cdecl SoundDefGroup_ScriptParseCB(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  #pragma pack(push, 1)
  union
  {
    struct { int iArg; };
    struct { char igi2_o1[4]; struct SoundSysCreateSoundContext_t tCreateContext; };
    struct { char igi2_o2[12]; struct Result_s Rs; };
    struct { char igi2_o3[36]; struct SoundDefGroup_s tSoundDefGroupTemplate; };
    char igi2_extent[140];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int isQVM; // eax
  int v4; // ebx
  struct QTask_s *v5; // esi

  if ( AppContext_tAppContext.isServer )
  {
    igi2_frame.Rs.nResult = 0;
    igi2_frame.Rs.vResult = 0.0;
  }
  else
  {
    igi2_frame.tCreateContext.ptSoundDef = (struct QTask_s *)&igi2_frame.tSoundDefGroupTemplate;
    isQVM = ptArgList->isQVM;
    igi2_frame.tCreateContext.isDefinition = 1;
    if ( isQVM )
    {
      igi2_frame.tSoundDefGroupTemplate.zSoundDef[0] = 0;
      QVM_EvalArg(igi2_frame.tSoundDefGroupTemplate.zSoundDef, 32, ptArgList, 0, 3);
    }
    else
    {
      Expression_EvalString(*ptArgList->aptExpression, igi2_frame.tSoundDefGroupTemplate.zSoundDef, 32);
    }
    v4 = 1;
    igi2_frame.iArg = 1;
    igi2_frame.tSoundDefGroupTemplate.isDefinition = 1;
    v5 = QTask_NewFn((struct QTask_s *)pxContext, SoundDefGroup_eCreateQTaskType, &igi2_frame.tCreateContext);
    Script_SetSymbolContext(&g_zFileName.zMenuResourcePath[156], v5);
    Script_SetSymbolContext(&g_zFileName.zMenuResourcePath[144], v5);
    Script_SetSymbolContext(&g_zFileName.zMenuResourcePath[132], v5);
    Script_SetSymbolContext(&g_zFileName.zMenuResourcePath[112], v5);
    if ( ptArgList->nArguments > 1 )
    {
      do
      {
        if ( ptArgList->isQVM )
        {
          igi2_frame.iArg = 0;
          QVM_EvalArg(&igi2_frame.iArg, 4, ptArgList, v4, 1);
        }
        else
        {
          Expression_EvalInt(ptArgList->aptExpression[v4]);
        }
        ++v4;
      }
      while ( v4 < ptArgList->nArguments );
      igi2_frame.iArg = v4;
    }
    Script_SetSymbolContext(&g_zFileName.zMenuResourcePath[156], pxContext);
    Script_SetSymbolContext(&g_zFileName.zMenuResourcePath[144], pxContext);
    Script_SetSymbolContext(&g_zFileName.zMenuResourcePath[132], pxContext);
    Script_SetSymbolContext(&g_zFileName.zMenuResourcePath[112], pxContext);
    igi2_frame.Rs.nResult = v4;
    igi2_frame.Rs.vResult = (double)igi2_frame.iArg;
  }
  igi2_frame.Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &igi2_frame.Rs, sizeof(struct Result_s));
  return retstr;
}
