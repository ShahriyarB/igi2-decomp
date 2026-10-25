/* h/2/sound/soundmanager.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: h/2/sound/soundmanager.c:43  [size]
void __cdecl SoundManager_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  LOBYTE(ptQTask[1].ptNext) = 0;
  ptQTask[1].ptParent = nullptr;
}

// source: h/2/sound/soundmanager.c:62  [size]
void __cdecl SoundManager_RunHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptHead; // ecx
  int v2; // edx
  struct QTask_s *v3; // eax
  void (__cdecl *pfHandler)(struct QTask_s *); // eax
  int v5; // edx

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

// source: h/2/sound/soundmanager.c:76  [size]
void __cdecl SoundManager_DeleteHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptParent; // eax

  ptParent = ptQTask[1].ptParent;
  if ( ptParent )
    QReference_Delete((struct QReference_s *)ptParent, &QTask_tQTaskRefPool);
}

// source: h/2/sound/soundmanager.c:96  [anchor-mhash]
void __cdecl SoundManager_UpdateParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *ptParent; // esi
  __int16 v3; // ax
  void (__cdecl *pfHandler)(struct QTask_s *, void *); // eax

  ptParent = ptQTask->ptParent;
  v3 = SoundSys_eUpdateParameterListQTaskEvent;
  if ( SoundSys_eUpdateParameterListQTaskEvent == 512 )
  {
    v3 = QTask_NewQTaskEventFn(0, (char *)&g_zFileName.nRealFadeCount);
    SoundSys_eUpdateParameterListQTaskEvent = v3;
  }
  pfHandler = (void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[v3][ptParent->eQTaskType].pfHandler;
  if ( pfHandler )
    pfHandler(ptParent, pxContext);
}

// source: h/2/sound/soundmanager.c:116  [anchor-mhash]
void __cdecl SoundManager_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *ptParent; // ebx
  struct QReference_s **p_ptParent; // esi
  struct QTask_s *ptHead; // eax
  int v5; // edx
  struct QTask_s *v6; // ecx
  void (__cdecl *pfHandler)(struct QTask_s *, _DWORD); // ecx
  int v8; // edx
  struct QTask_s *v9; // edi
  __int16 v10; // ax
  void (__cdecl *v11)(struct QTask_s *, void **); // eax
  struct QTask_s *v12; // eax

  ptParent = ptQTask[1].ptParent;
  p_ptParent = (struct QReference_s **)&ptQTask[1].ptParent;
  if ( LOBYTE(ptQTask[1].ptNext) )
  {
    if ( !pxContext || !*(_DWORD *)pxContext )
    {
      ptHead = ptQTask->tQTaskChildren.ptHead;
      if ( ptHead->ptNext )
      {
        if ( ptHead )
        {
          v5 = QTask_nProtectedQTaskStackOffset;
          do
          {
            if ( ptHead->ptNext )
              v6 = ptHead->ptNext->ptNext != nullptr ? ptHead->ptNext : nullptr;
            else
              v6 = nullptr;
            QTask_atProtectedQTaskStack[v5].ptQTask = v6;
            pfHandler = (void (__cdecl *)(struct QTask_s *, _DWORD))QTask_aatQTaskFinalEvent[ParameterList_eUpdateInternalDataQTaskEvent][ptHead->eQTaskType].pfHandler;
            v8 = v5 + 1;
            QTask_nProtectedQTaskStackOffset = v8;
            if ( pfHandler )
            {
              pfHandler(ptHead, 0);
              v8 = QTask_nProtectedQTaskStackOffset;
            }
            ptHead = (struct QTask_s *)dword_849C7DC[v8];
            v5 = v8 - 1;
            QTask_nProtectedQTaskStackOffset = v5;
          }
          while ( ptHead );
        }
      }
    }
    if ( !ptParent )
      goto LABEL_22;
    v9 = ptParent->tQTaskChildren.ptHead;
    if ( !v9 )
      goto LABEL_22;
    v10 = SoundSys_eRequestSoundDefQTaskEvent;
    pxContext = nullptr;
    if ( SoundSys_eRequestSoundDefQTaskEvent == 512 )
    {
      v10 = QTask_NewQTaskEventFn(0, (char *)&g_zFileName.aptSelectableTABItems[31]);
      SoundSys_eRequestSoundDefQTaskEvent = v10;
    }
    v11 = (void (__cdecl *)(struct QTask_s *, void **))QTask_aatQTaskFinalEvent[v10][v9->eQTaskType].pfHandler;
    if ( v11 )
      v11(v9, &pxContext);
    if ( !pxContext || strcmp((char *)&ptQTask[1], (char *)pxContext) )
    {
LABEL_22:
      QTask_DeleteQTaskAndQTaskRefSafe(p_ptParent);
      v12 = SoundSys_NewSoundFn(ptQTask, (char *)&ptQTask[1]);
      *p_ptParent = QTask_NewQTaskRef(v12);
    }
  }
  else
  {
    QTask_DeleteQTaskAndQTaskRefSafe(p_ptParent);
  }
}

// source: h/2/sound/soundmanager.c:192  [size]
void __cdecl SoundManager_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = SoundManager_ptParameterList;
}

// source: h/2/sound/soundmanager.c:210  [anchor-hash]
void __cdecl SoundManager_Open()
{
  unsigned __int16 BaseQTaskType; // ax
  unsigned __int16 v1; // si
  __int16 v2; // ax
  struct ParameterList_s *v3; // eax
  int v4; // edx

  BaseQTaskType = QTask_GetBaseQTaskType();
  v1 = QTask_NewQTaskType("SoundManager", 76, BaseQTaskType, 0, 0);
  SoundManager_eQTaskType = v1;
  QTask_LinkQTaskEventHandlerFn(
    v1,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveNoChildrenHandler);
  QTask_LinkQTaskEventHandlerFn(v1, 0, (void (__cdecl *)(struct QTask_s *, void *))SoundManager_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 1, SoundManager_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 2, SoundManager_DeleteHandler);
  v2 = SoundSys_eUpdateParameterListQTaskEvent;
  if ( SoundSys_eUpdateParameterListQTaskEvent == 512 )
  {
    v2 = QTask_NewQTaskEventFn(0, (char *)&g_zFileName.nRealFadeCount);
    v1 = SoundManager_eQTaskType;
    SoundSys_eUpdateParameterListQTaskEvent = v2;
  }
  QTask_LinkQTaskEventHandlerFn(v1, v2, SoundManager_UpdateParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(v1, ParameterList_eUpdateInternalDataQTaskEvent, SoundManager_UpdateInternalDataHandler);
  QTask_LinkQTaskEventHandlerFn(
    v1,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))SoundManager_GetParameterListHandler);
  v3 = (struct ParameterList_s *)Mem_AllocFn(32, 4);
  v4 = Level_eParameterTypeString32;
  v3->ptParameterListItem = (struct ParameterListItem_s *)&v3[1];
  v3->nParameters = 0;
  v3->nMaxParameters = 1;
  SoundManager_ptParameterList = v3;
  ParameterList_AddParameter(v3, 0x28u, v4, "SoundDef", 7u, nullptr);
}

// source: h/2/sound/soundmanager.c:239  [size]
void __cdecl SoundManager_Close()
{
  int v0; // esi

  QTask_DeleteQTaskType(SoundManager_eQTaskType);
  if ( SoundManager_ptParameterList )
  {
    v0 = *(_DWORD *)((unsigned int)&SoundManager_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
}

// source: h/2/sound/soundmanager.c:256  [size]
unsigned __int16 __cdecl SoundManager_GetQTaskType()
{
  return SoundManager_eQTaskType;
}
