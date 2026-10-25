/* j/0/flow.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/flow.c:105  [size]
void __cdecl Flow_ParseScreenshotCmdLineArgs(char *zArg)
{
  Flow_isScreenGrab = 1;
}

// source: j/0/flow.c:118  [anchor-hash]
void __cdecl Flow_ReloadSettingsHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct Script_s *v2; // eax
  struct Script_s *v3; // esi
  struct GameMaterial_s *v4; // eax
  struct QMaterial_t **aptQMaterial; // ecx

  GameMaterial_RemoveAll();
  v2 = Script_New("LOCAL:material/material.qsc");
  v3 = v2;
  if ( !v2 )
  {
    LDebug_Error("GameMaterial_LoadParameters: Couldn't load script \"%s\"", "LOCAL:material/material.qsc");
    abort();
  }
  Script_Execute(v2);
  Script_Delete(v3);
  v4 = GameMaterial_atGameMaterial;
  aptQMaterial = Game_ptGame->ptWorld->aptQMaterial;
  do
  {
    *aptQMaterial = &v4->tQMaterial;
    ++v4;
    ++aptQMaterial;
  }
  while ( (int)v4 < 7505672 );
}

// source: j/0/flow.c:134  [size]
void __cdecl Flow_ActivateDeactivateCB(enum bool isActivate, void *pxContext)
{
  ;
}

// source: j/0/flow.c:160  [anchor-strings]
void __cdecl Flow_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { int v20; };
    struct { char igi2_o1[4]; int v21; };
    char igi2_extent[8];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  unsigned __int16 BaseQTaskType; // ax
  struct QTask_s *v3; // eax
  struct Flow_t *v4; // eax
  struct Script_s *v5; // eax
  struct Script_s *v6; // esi
  struct QTask_s *QTask; // eax
  struct QTask_s *v8; // eax
  struct QTask_s *v9; // eax
  struct Flow_t *v10; // edi
  unsigned __int16 v11; // ax
  struct QTask_s *v12; // edi
  bool v13; // zf
  struct QTask_s *v14; // eax
  struct Flow_t *v15; // edi
  struct QTask_s *v16; // eax
  struct Flow_t *v17; // edi
  int v18; // esi
  enum InputPortDevice_e v19; // ecx

  LOBYTE(ptQTask[2].tQTaskChildren.ptHead) = 0;
  BYTE1(ptQTask[2].tQTaskChildren.ptHead) = 0;
  BYTE2(ptQTask[2].tQTaskChildren.ptHead) = 0;
  Flow_ptFlow = (struct Flow_t *)ptQTask;
  Flow_isForbidDrawOneTick = 1;
  ptQTask[2].tQTaskRefList.ptHead = nullptr;
  BaseQTaskType = QTask_GetBaseQTaskType();
  v3 = QTask_NewFn(nullptr, BaseQTaskType, nullptr);
  Flow_ptFlow->ptAlwaysRunQTask = v3;
  QTask_SetAlwaysRunQTask(v3);
  Flow_SetFrequency(30);
  v4 = Flow_ptFlow;
  Flow_ptFlow->nTicksSinceRedraw = 0;
  v4->nSkipTime = 0;
  v4->nDrawTime = 0;
  v4->nDrawnFrames = 0;
  Config_Load("LOCAL:config.qsc");
  if ( Flow_iOverrideActivePlayerProfile >= 0 )
  {
    if ( Flow_iOverrideActivePlayerProfile < Config_tConfig.nPlayerProfiles )
      Config_tConfig.iActiveProfile = Flow_iOverrideActivePlayerProfile;
    Flow_iOverrideActivePlayerProfile = -1;
  }
  AmmoType_ptContainer = QTask_NewFn(&Flow_ptFlow->tQTask, AmmoTypeContainer_eQTaskType, nullptr);
  Level_LoadQTask(AmmoType_ptContainer, "LOCAL:weapons/ammo.qsc", false);
  WeaponType_ptContainer = QTask_NewFn(&Flow_ptFlow->tQTask, WeaponTypeContainer_eQTaskType, nullptr);
  Level_LoadQTask(WeaponType_ptContainer, "weapons/weapon.qsc", false);
  GameMaterial_RemoveAll();
  v5 = Script_New("LOCAL:material/material.qsc");
  v6 = v5;
  if ( !v5 )
  {
    LDebug_Error("GameMaterial_LoadParameters: Couldn't load script \"%s\"", "LOCAL:material/material.qsc");
    abort();
  }
  Script_Execute(v5);
  Script_Delete(v6);
  MagicObjConfigContainer_zFilename = "magicobjconfig.qsc";
  QTask = Level_LoadQTask(ptQTask, "magicobjconfig.qsc", false);
  if ( !QTask )
    QTask = QTask_NewFn(ptQTask, MagicObjConfigContainer_eQTaskType, nullptr);
  Level_ClearQTaskIDRecursive(QTask);
  MagicObjConfigContainer_zFilename = "editormagicobjconfig.qsc";
  v8 = Level_LoadQTask(ptQTask, "editormagicobjconfig.qsc", false);
  if ( !v8 )
    v8 = QTask_NewFn(ptQTask, MagicObjConfigContainer_eQTaskType, nullptr);
  Level_ClearQTaskIDRecursive(v8);
  MagicObjConfigContainer_zFilename = nullptr;
  igi2_frame.v20 = (int)AnimTrigger_ProcessFileCB;
  igi2_frame.v21 = 0;
  File_DirList(
    "LOCAL:animtrigger",
    (void (__cdecl *)(struct FileDirListCallbackContext_s *, void *))Script_DirListCallback,
    &igi2_frame.v20);
  igi2_frame.v20 = (int)PhysicsObjType_ProcessFileCB;
  igi2_frame.v21 = 0;
  File_DirList(
    "LOCAL:physicsobj",
    (void (__cdecl *)(struct FileDirListCallbackContext_s *, void *))Script_DirListCallback,
    &igi2_frame.v20);
  QTask_NewFn(ptQTask, ModelLODSettingsContainer_eQTaskType, nullptr);
  HumanAIConfig_LoadSettings(ptQTask);
  v9 = QTask_NewFn(ptQTask, HumanPlayerConfig_eQTaskType, nullptr);
  if ( v9 )
  {
    HumanPlayerConfig_ptHumanPlayerConfigQTask = v9;
    Level_LoadQTask(v9, "LOCAL:humanplayer/humanplayer.qsc", false);
  }
  v10 = Flow_ptFlow;
  v11 = Screen_eQTaskType;
  Flow_ptFlow->eCurrentEvent = 0;
  v10->eRequestedEvent = 0;
  v12 = QTask_NewFn(&v10->tQTask, v11, nullptr);
  v13 = Flow_isScreenGrab == 0;
  Flow_ptFlow->ptScreenQTask = v12;
  if ( !v13 )
    QTask_NewFn(v12, ScreenGrab_eQTaskType, nullptr);
  v14 = QTask_NewFn(&Flow_ptFlow->tQTask, InputPort_eQTaskType, nullptr);
  v15 = Flow_ptFlow;
  Flow_ptFlow->ptInputPortQTask = v14;
  v16 = QTask_NewFn(&v15->tQTask, NetManager_eQTaskType, nullptr);
  v17 = Flow_ptFlow;
  Flow_ptFlow->ptNetManagerQTask = v16;
  v18 = (int)&v16[32].tQTaskChildren.ptTail->ptNext + 1;
  v16[32].tQTaskChildren.ptTail = (struct QTask_s *)v18;
  *((_DWORD *)&v16[31].tQTaskChildren.ptTail + v18) = 0;
  QTask_NewFn(&v17->tQTask, SoundSys_eSystemControlQTaskType, nullptr);
  if ( Keyboard_tKeyboard.isConnected )
  {
    v19 = INPUTPORT_DEVICE_NONE;
    if ( Mouse_tMouse.isConnected )
      v19 = INPUTPORT_DEVICE_MOUSE;
    InputPort_Init(
      INPUTPORT_0,
      Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tInputOptions.nRemapButton,
      Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tInputOptions.atRemapButtonTable,
      v19,
      0.029999999329447746,
      0.0010000000474974513,
      0.0010000000474974513,
      0.029999999329447746,
      0.0010000000474974513,
      0.0010000000474974513,
      0.029999999329447746,
      0.0010000000474974513,
      0.0010000000474974513,
      0.029999999329447746,
      0.0010000000474974513,
      0.0010000000474974513);
    InputPort_atInputPort[0].isActive = true;
  }
  AppContext_tAppContext.pxActivateCallbackContext = nullptr;
  AppContext_tAppContext.pfActivateCallback = (void (__cdecl *)(enum bool, void *))Flow_ActivateDeactivateCB;
}

// source: j/0/flow.c:305  [anchor-hash]
void __cdecl Flow_RunNetwork()
{
  ((void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[1][Flow_ptFlow->ptNetManagerQTask->eQTaskType].pfHandler)(Flow_ptFlow->ptNetManagerQTask);
}

// source: j/0/flow.c:321  [size]
void __cdecl Flow_RunNetworkInterrupt()
{
  NetManager_RunNetworkInterrupt();
}

// source: j/0/flow.c:336  [anchor-strings]
void __cdecl Flow_RunHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { char *v91; };
    struct { char *v92; };
    struct { char *v93; };
    struct { char *v94; };
    struct { char *v95; };
    struct { char *v96; };
    struct { char *v97; };
    struct { char *v98; };
    struct { char *v99; };
    struct { char igi2_o9[16]; int v100; };
    struct { char igi2_o10[16]; BOOL v101; };
    struct { char igi2_o11[20]; struct QTask_s ptParent; };
    struct { char igi2_o12[73]; char v103; };
    struct { char igi2_o13[76]; char zText[256]; };
    char igi2_extent[332];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct Node_s *v1; // eax
  struct Node_s *v2; // ecx
  int v3; // eax
  struct Flow_t *v4; // ecx
  struct QReference_s *v5; // esi
  double v6; // st7
  int nTicks; // eax
  int v8; // edx
  struct QTask_s *ptNext; // ebx
  struct QTask_s *v10; // ecx
  bool v11; // zf
  int v12; // edx
  struct QTask_s *v13; // eax
  void (__cdecl *v14)(struct QTask_s *); // eax
  int v15; // edx
  struct QTask_s *v16; // ecx
  int v17; // edx
  struct QTask_s *v18; // eax
  void (__cdecl *v19)(struct QTask_s *); // eax
  int v20; // edx
  BOOL v21; // edi
  struct QTaskList_s *v22; // edx
  int v23; // ebx
  int v24; // edi
  void (__cdecl *v25)(_DWORD); // ecx
  struct QTask_s *v26; // ecx
  int v27; // edx
  struct QTask_s *v28; // eax
  int v29; // edi
  void (__cdecl *v30)(struct QTask_s *); // eax
  int v31; // edx
  int v32; // ecx
  struct Flow_t *v33; // eax
  struct QTask_s *ptHead; // ecx
  int v35; // edx
  struct QTask_s *v36; // eax
  void (__cdecl *pfHandler)(struct QTask_s *); // eax
  int v38; // edx
  struct QTask_s *v39; // ecx
  int v40; // edx
  struct QTask_s *v41; // eax
  void (__cdecl *v42)(struct QTask_s *); // eax
  int v43; // edx
  struct QTask_s *v44; // ecx
  int v45; // edx
  struct QTask_s *v46; // eax
  int v47; // esi
  void (__cdecl *v48)(struct QTask_s *); // eax
  int v49; // edx
  int eRequestedEvent; // edi
  struct QTask_s *ptScreenQTask; // ecx
  struct QTask_s *v52; // ecx
  void *v53; // eax
  char *v54; // eax
  struct Flow_t *v55; // ecx
  char *v56; // eax
  struct QTask_s *ptNetManagerQTask; // eax
  struct QReference_s *v58; // ebx
  BOOL v59; // esi
  void *pxLoadingScreen; // eax
  void *v61; // eax
  int v62; // edi
  char *v63; // eax
  struct QTask_s *v64; // eax
  int v65; // ecx
  int ServerPort; // eax
  char *LocalizedString; // eax
  char *v68; // eax
  char *v69; // eax
  struct Flow_t *v70; // edi
  struct Flow_t *v71; // esi
  struct Client_s *ClientFromNetworkID; // eax
  struct Client_s *v73; // eax
  BOOL v74; // edi
  char *v75; // eax
  char *v76; // eax
  char *v77; // eax
  char *v78; // eax
  char *v79; // eax
  void *v80; // eax
  char *v81; // eax
  enum bool v82; // esi
  char *v83; // eax
  char *v84; // eax
  void **p_pxLoadingScreen; // edi
  void *v86; // eax
  void *v87; // eax
  struct QTask_s *v88; // ecx
  struct Flow_t *v89; // ecx
  struct QTask_s *v90; // ecx

  if ( (Keyboard_tKeyboard.anCurrentKey[67] & 0x80u) != 0
    && (Keyboard_tKeyboard.anPreviousKey[67] & 0x80) == 0
    && (Keyboard_tKeyboard.anCurrentKey[29] & 0x80) != 0
    && (Keyboard_tKeyboard.anCurrentKey[42] & 0x80) != 0 )
  {
    v1 = sub_416790(0);
    if ( v1 )
    {
      do
      {
        v2 = v1;
        v1 = v1->ptNext;
      }
      while ( v1->ptNext && v1 );
      Config_UpdateActiveMissionID((int)v2[1].ptNext);
    }
  }
  ((void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[1][Flow_ptFlow->ptNetManagerQTask->eQTaskType].pfHandler)(Flow_ptFlow->ptNetManagerQTask);
  if ( AppContext_isFixmeSmall || ScreenGrab_isRecord[0] || ScreenGrab_isGrabSingle[0] || g_bContinue )
  {
    ptHead = ptQTask->tQTaskChildren.ptHead;
    if ( ptHead->ptNext && ptHead )
    {
      v35 = QTask_nProtectedQTaskStackOffset;
      do
      {
        if ( ptHead->ptNext )
          v36 = ptHead->ptNext->ptNext != nullptr ? ptHead->ptNext : nullptr;
        else
          v36 = nullptr;
        QTask_atProtectedQTaskStack[v35].ptQTask = v36;
        pfHandler = (void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[1][ptHead->eQTaskType].pfHandler;
        v38 = v35 + 1;
        QTask_nProtectedQTaskStackOffset = v38;
        if ( pfHandler )
        {
          pfHandler(ptHead);
          v38 = QTask_nProtectedQTaskStackOffset;
        }
        ptHead = (struct QTask_s *)dword_849C7DC[v38];
        v35 = v38 - 1;
        QTask_nProtectedQTaskStackOffset = v35;
      }
      while ( ptHead );
    }
    NetManager_RunNetworkInterrupt();
    v39 = Flow_ptFlow->ptAlwaysRunQTask->tQTaskChildren.ptHead;
    if ( v39->ptNext && v39 )
    {
      v40 = QTask_nProtectedQTaskStackOffset;
      do
      {
        if ( v39->ptNext )
          v41 = v39->ptNext->ptNext != nullptr ? v39->ptNext : nullptr;
        else
          v41 = nullptr;
        QTask_atProtectedQTaskStack[v40].ptQTask = v41;
        v42 = (void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[1][v39->eQTaskType].pfHandler;
        v43 = v40 + 1;
        QTask_nProtectedQTaskStackOffset = v43;
        if ( v42 )
        {
          v42(v39);
          v43 = QTask_nProtectedQTaskStackOffset;
        }
        v39 = (struct QTask_s *)dword_849C7DC[v43];
        v40 = v43 - 1;
        QTask_nProtectedQTaskStackOffset = v40;
      }
      while ( v39 );
    }
    NetManager_RunNetworkInterrupt();
    v4 = Flow_ptFlow;
    v11 = g_bContinue == 0;
    ++Flow_ptFlow->nTicks;
    if ( v11
      && (AppContext_tAppContext.isActive == false || AppContext_tAppContext.isDebugged)
      && AppContext_tAppContext.isServer == false
      && !Flow_isForbidDrawOneTick )
    {
      v44 = ptQTask->tQTaskChildren.ptHead;
      if ( v44->ptNext && v44 )
      {
        v45 = QTask_nProtectedQTaskStackOffset;
        do
        {
          if ( v44->ptNext )
            v46 = v44->ptNext->ptNext != nullptr ? v44->ptNext : nullptr;
          else
            v46 = nullptr;
          v47 = Screen_eDrawQTaskEvent;
          QTask_atProtectedQTaskStack[v45].ptQTask = v46;
          v48 = (void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[v47][v44->eQTaskType].pfHandler;
          v49 = v45 + 1;
          QTask_nProtectedQTaskStackOffset = v49;
          if ( v48 )
          {
            v48(v44);
            v49 = QTask_nProtectedQTaskStackOffset;
          }
          v44 = (struct QTask_s *)dword_849C7DC[v49];
          v45 = v49 - 1;
          QTask_nProtectedQTaskStackOffset = v45;
        }
        while ( v44 );
      }
      NetManager_RunNetworkInterrupt();
      v4 = Flow_ptFlow;
    }
    ++v4->nTicksDrawn;
  }
  else
  {
    v3 = Timer_Read();
    v4 = Flow_ptFlow;
    v5 = (struct QReference_s *)v3;
    v6 = 1000.0 / (double)Flow_ptFlow->nFrequency;
    nTicks = Flow_ptFlow->nTicks;
    v8 = Flow_ptFlow->nStartTime + Flow_ptFlow->nSkipTime;
    igi2_frame.v100 = nTicks;
    igi2_frame.ptParent.tQTaskRefList.ptHead = v5;
    *(_QWORD *)&igi2_frame.ptParent.ptNext = (__int64)(v6 * (double)nTicks + (double)v8);
    ptNext = igi2_frame.ptParent.ptNext;
    if ( (int)v5 <= (int)igi2_frame.ptParent.ptNext || Flow_ptFlow->nTicksSinceRedraw > 10 )
    {
      v21 = Game_IsPaused() == false
         && (int)v5 + v4->nDrawTime < (int)igi2_frame.ptParent.ptNext
         && v4->isDrawInterpolateEnabled
         || !v4->isDrawn;
      if ( AppContext_tAppContext.isServer )
      {
        Sleep(1u);
        v4 = Flow_ptFlow;
      }
      if ( v21 && !Flow_isForbidDrawOneTick )
      {
        if ( v4->isDrawn )
        {
          sub_4274B0();
          InputPort_Update(Flow_ptFlow->ptInputPortQTask);
          v22 = Flow_ptDrawInterpolateQTaskList;
          Flow_ptFlow->isDrawInterpolateFrame = 1;
          v23 = 0;
          if ( v22->nTask > 0 )
          {
            v24 = 8;
            do
            {
              v25 = (void (__cdecl *)(_DWORD))QTask_aatQTaskFinalEvent[Flow_eDrawInterpolateQTaskEvent][*(unsigned __int16 *)(*(int *)((char *)&v22->nTask + v24) + 36)].pfHandler;
              if ( v25 )
              {
                v25(*(int *)((char *)&v22->nTask + v24));
                v22 = Flow_ptDrawInterpolateQTaskList;
              }
              ++v23;
              v24 += 4;
            }
            while ( v23 < v22->nTask );
            v5 = igi2_frame.ptParent.tQTaskRefList.ptHead;
          }
          Flow_ptFlow->isDrawInterpolateFrame = 0;
          NetManager_RunNetworkInterrupt();
          v4 = Flow_ptFlow;
          ptNext = igi2_frame.ptParent.ptNext;
        }
        if ( (AppContext_tAppContext.isActive == false || AppContext_tAppContext.isDebugged)
          && AppContext_tAppContext.isServer == false )
        {
          v26 = ptQTask->tQTaskChildren.ptHead;
          if ( v26->ptNext && v26 )
          {
            v27 = QTask_nProtectedQTaskStackOffset;
            do
            {
              if ( v26->ptNext )
                v28 = v26->ptNext->ptNext != nullptr ? v26->ptNext : nullptr;
              else
                v28 = nullptr;
              v29 = Screen_eDrawQTaskEvent;
              QTask_atProtectedQTaskStack[v27].ptQTask = v28;
              v30 = (void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[v29][v26->eQTaskType].pfHandler;
              v31 = v27 + 1;
              QTask_nProtectedQTaskStackOffset = v31;
              if ( v30 )
              {
                v30(v26);
                v31 = QTask_nProtectedQTaskStackOffset;
              }
              v26 = (struct QTask_s *)dword_849C7DC[v31];
              v27 = v31 - 1;
              QTask_nProtectedQTaskStackOffset = v27;
            }
            while ( v26 );
          }
          v32 = Timer_Read();
          v33 = Flow_ptFlow;
          Flow_ptFlow->nDrawTime = v32 - (_DWORD)v5;
          ++v33->nDrawnFrames;
          NetManager_RunNetworkInterrupt();
          v4 = Flow_ptFlow;
        }
        if ( (int)v5 > (int)ptNext )
          v4->nSkipTime += (char *)v5 - (char *)ptNext;
        ++v4->nTicksDrawn;
      }
      v4->isDrawn = 1;
      v4->nTicksSinceRedraw = 0;
    }
    else
    {
      World_nTraceLines = 0;
      World_nTraceLinesActual = 0;
      World_nLineOfSights = 0;
      if ( nTicks >= 2 )
      {
        SoundSys_isDontAddSoundToPlayList = 0;
      }
      else
      {
        Flow_SuspendTiming();
        v4 = Flow_ptFlow;
        SoundSys_isDontAddSoundToPlayList = 1;
      }
      v4->isDrawInterpolateEnabled = 0;
      v10 = ptQTask->tQTaskChildren.ptHead;
      v11 = v10->ptNext == nullptr;
      CutScene_isRunning = 0;
      if ( !v11 && v10 )
      {
        v12 = QTask_nProtectedQTaskStackOffset;
        do
        {
          if ( v10->ptNext )
            v13 = v10->ptNext->ptNext != nullptr ? v10->ptNext : nullptr;
          else
            v13 = nullptr;
          QTask_atProtectedQTaskStack[v12].ptQTask = v13;
          v14 = (void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[1][v10->eQTaskType].pfHandler;
          v15 = v12 + 1;
          QTask_nProtectedQTaskStackOffset = v15;
          if ( v14 )
          {
            v14(v10);
            v15 = QTask_nProtectedQTaskStackOffset;
          }
          v10 = (struct QTask_s *)dword_849C7DC[v15];
          v12 = v15 - 1;
          QTask_nProtectedQTaskStackOffset = v12;
        }
        while ( v10 );
      }
      NetManager_RunNetworkInterrupt();
      v16 = Flow_ptFlow->ptAlwaysRunQTask->tQTaskChildren.ptHead;
      if ( v16->ptNext && v16 )
      {
        v17 = QTask_nProtectedQTaskStackOffset;
        do
        {
          if ( v16->ptNext )
            v18 = v16->ptNext->ptNext != nullptr ? v16->ptNext : nullptr;
          else
            v18 = nullptr;
          QTask_atProtectedQTaskStack[v17].ptQTask = v18;
          v19 = (void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[1][v16->eQTaskType].pfHandler;
          v20 = v17 + 1;
          QTask_nProtectedQTaskStackOffset = v20;
          if ( v19 )
          {
            v19(v16);
            v20 = QTask_nProtectedQTaskStackOffset;
          }
          v16 = (struct QTask_s *)dword_849C7DC[v20];
          v17 = v20 - 1;
          QTask_nProtectedQTaskStackOffset = v17;
        }
        while ( v16 );
      }
      NetManager_RunNetworkInterrupt();
      v4 = Flow_ptFlow;
      if ( Flow_isForbidDrawOneTick )
      {
        Flow_ptFlow->isDrawInterpolateEnabled = 0;
        Flow_isForbidDrawOneTick = 0;
      }
      if ( igi2_frame.v100 < 2 )
      {
        Flow_ResumeTiming();
        v4 = Flow_ptFlow;
      }
      ++v4->nTicks;
      v4->isDrawn = 0;
      v4->nDrawnFrames = 0;
      ++v4->nTicksSinceRedraw;
    }
  }
  eRequestedEvent = v4->eRequestedEvent;
  if ( eRequestedEvent )
  {
    v4->eCurrentEvent = eRequestedEvent;
    Flow_isForbidDrawOneTick = 1;
    v4->eRequestedEvent = 0;
    switch ( eRequestedEvent )
    {
      case 1:
        if ( Game_ptGame )
          QTask_Delete(&Game_ptGame->tQTask);
        goto LABEL_114;
      case 2:
      case 9:
        ptScreenQTask = v4->ptScreenQTask;
        igi2_frame.ptParent.ptPrev = (struct QTask_s *)IntroScreen_azIntroMoviesToPlay;
        igi2_frame.ptParent.ptNext = (struct QTask_s *)2;
        igi2_frame.ptParent.tQTaskChildren.ptHead = nullptr;
        QTask_NewFn(ptScreenQTask, IntroScreen_eQTaskType, &igi2_frame.ptParent);
        goto LABEL_229;
      case 3:
        goto LABEL_121;
      case 4:
        Game_SetDisplayMode();
        StatusMessageScreen_LoadResource();
        if ( Game_eGameMode )
        {
          if ( Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER )
          {
            ptNetManagerQTask = Flow_ptFlow->ptNetManagerQTask;
            igi2_frame.ptParent.tQTaskRefList.ptHead = (struct QReference_s *)ptNetManagerQTask[9].tQTaskChildren.ptTail;
            v58 = igi2_frame.ptParent.tQTaskRefList.ptHead;
            ptNetManagerQTask[8].tQTaskRefList.ptMiddle = nullptr;
            ptNetManagerQTask[9].tQTaskRefList.ptMiddle = (struct QReference_s *)-1;
            NetManager_LogMessage((char *)&stru_6A1E00.tServerGameSettings.nMissionTime);
            if ( v58 )
            {
              v59 = Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle == nullptr;
              igi2_frame.v101 = v59;
            }
            else
            {
              igi2_frame.v101 = NetManager_nSelectedSession == -1;
              v59 = igi2_frame.v101;
            }
            pxLoadingScreen = Flow_ptFlow->pxLoadingScreen;
            if ( pxLoadingScreen )
              LoadingScreen_Delete(pxLoadingScreen);
            if ( v59 )
            {
              if ( !v58 )
              {
                NetManager_InitSessionData();
LABEL_150:
                Game_iMissionID = NetManager_GetMissionID();
              }
            }
            else if ( !v58 )
            {
              goto LABEL_150;
            }
            NetManager_LogMessage("Created loading screen\n");
            v61 = LoadingScreen_New(10, Game_iMissionID, true);
            Flow_ptFlow->pxLoadingScreen = v61;
            LoadingScreen_SetTextColour(v61, 1.0, 1.0, 1.0);
            if ( !v58 && !v59 )
            {
              if ( NetManager_IsSelectedSessionNonProtected() == false )
              {
                igi2_frame.ptParent.ptNext = (struct QTask_s *)strlen(ClientConfig_tClientConfig.zPlayerPassword);
                if ( !igi2_frame.ptParent.ptNext )
                {
                  v62 = 1;
                  goto LABEL_156;
                }
              }
              v62 = 0;
              if ( NetManager_IsSelectedSessionCompatible() == false
                || NetManager_IsSelectedSessionNonFull() == false )
              {
LABEL_156:
                NetManager_LogMessage("Aborting game lanch, selected game is not joinable\n");
                if ( NetManager_IsSelectedSessionCompatible() )
                {
                  if ( v62 )
                  {
                    LocalizedString = (char *)Config_GetLocalizedString("mp/load_access_password");
                    LoadingScreen_UpdateText(Flow_ptFlow->pxLoadingScreen, LocalizedString);
                  }
                  else if ( NetManager_IsSelectedSessionNonFull() )
                  {
                    LoadingScreen_UpdateText(Flow_ptFlow->pxLoadingScreen, "Unforseen error path, exiting");
                  }
                  else
                  {
                    v68 = (char *)Config_GetLocalizedString("mp/load_game_not_joinable_full");
                    LoadingScreen_UpdateText(Flow_ptFlow->pxLoadingScreen, v68);
                  }
                }
                else
                {
                  Config_SetLocalizedPhrase(
                    igi2_frame.zText,
                    "mp/load_game_not_joinable_version",
                    g_zPlayer1,
                    (char *)(240 * NetManager_nSelectedSession + 7359244),
                    nullptr);
                  LoadingScreen_UpdateText(Flow_ptFlow->pxLoadingScreen, igi2_frame.zText);
                }
                Network_CloseGlobalUDPSocket();
                NetManager_LogMessage("Game socket closed\n");
                Sleep(0x1388u);
                LoadingScreen_Delete(Flow_ptFlow->pxLoadingScreen);
                Flow_ptFlow->pxLoadingScreen = nullptr;
                StatusMessageScreen_FreeResource();
                v4 = Flow_ptFlow;
                Flow_ptFlow->eRequestedEvent = 6;
                goto LABEL_223;
              }
              v63 = (char *)Config_GetLocalizedString("mp/load_access_ok");
              LoadingScreen_UpdateText(Flow_ptFlow->pxLoadingScreen, v63);
              NetManager_CopySelectedServerSettings();
            }
            v64 = Flow_ptFlow->ptNetManagerQTask;
            v65 = (int)&v64[32].tQTaskChildren.ptTail->ptNext + 1;
            v64[32].tQTaskChildren.ptTail = (struct QTask_s *)v65;
            *((_DWORD *)&v64[31].tQTaskChildren.ptTail + v65) = 1;
            if ( !v58 )
            {
              NetManager_ClearRunTimers();
              if ( v59 )
              {
                ServerPort = NetManager_GetServerPort();
                NetManager_SetupNetworkPartForServer(ServerPort);
              }
              else
              {
                NetManager_SetupLocalClientNetwork();
              }
              if ( !Flow_ptFlow->ptNetManagerQTask[9].tQTaskChildren.ptTail )
              {
                NetManager_LogMessage("Could not connect, aborting...\n");
                v69 = (char *)Config_GetLocalizedString("mp/load_connect_failed");
                LoadingScreen_UpdateText(Flow_ptFlow->pxLoadingScreen, v69);
                Sleep(0x1388u);
                LoadingScreen_Delete(Flow_ptFlow->pxLoadingScreen);
                Flow_ptFlow->pxLoadingScreen = nullptr;
                StatusMessageScreen_FreeResource();
                NetManager_LogMessage("Closing socket\n");
                Network_CloseGlobalUDPSocket();
                v4 = Flow_ptFlow;
                Flow_ptFlow->eRequestedEvent = 6;
                --v4->ptNetManagerQTask[32].tQTaskChildren.ptTail;
                goto LABEL_223;
              }
              NetManager_InitData();
            }
            if ( !v59 )
              MapControl_ClearClientState();
            NetManager_InitCommonSettings();
            Sleep(0x1F4u);
            v70 = Flow_ptFlow;
            LoadingScreen_SetTextColour(Flow_ptFlow->pxLoadingScreen, 1.0, 1.0, 1.0);
            LoadingScreen_UpdateText(v70->pxLoadingScreen, (char *)&g_zInitialValue);
            Sleep(0x1F4u);
            Game_New(ptQTask, Flow_ptFlow->pxLoadingScreen);
            LoadingScreen_SetTextColour(Flow_ptFlow->pxLoadingScreen, 1.0, 1.0, 1.0);
            Flow_SetFrequency(30);
            if ( igi2_frame.v101 )
              NetManager_UpdateServerSettings();
            else
              MapControl_ClearClientState();
            v71 = Flow_ptFlow;
            ClientFromNetworkID = NetManager_GetClientFromNetworkID((int)Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle);
            if ( ClientFromNetworkID )
              NetManager_eTeam = ClientFromNetworkID->eTeam;
            NetManager_eMode = NETMANAGER_MODE_WELCOME;
            LOBYTE(MenuManager_ptQTask[243].eQTaskType) = 1;
            if ( v58 )
            {
              NetManager_ResurrectHumans();
              NetManager_FillScoreboard();
              v71 = Flow_ptFlow;
              v73 = NetManager_GetClientFromNetworkID((int)Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle);
              if ( v73 )
                NetManager_eTeam = v73->eTeam;
              NetManager_eMode = NETMANAGER_MODE_WELCOME;
              LOBYTE(MenuManager_ptQTask[243].eQTaskType) = 1;
            }
            v74 = igi2_frame.v101;
            if ( igi2_frame.v101 )
            {
              if ( !v58 )
                NetManager_StartServerClient();
              MapControl_ServerReset();
              TeamManager_ClearScore();
              v71 = Flow_ptFlow;
            }
            --v71->ptNetManagerQTask[32].tQTaskChildren.ptTail;
            if ( igi2_frame.v101 )
            {
              QTask_GetFirstChildOfType(v71->ptNetManagerQTask, MapControl_eQTaskType)[1].ptParent = nullptr;
              NetManager_LogMessage("MapControl_SetLoading(): set to FALSE\n");
              NetManager_SendScoreUpdate();
            }
            NetManager_SetStartGameStatus(true);
            if ( !v58 )
            {
              NetManager_ResetAllInput();
              NetManager_LogMessage("First time loading: Reset the input timer\n");
            }
            if ( !igi2_frame.v101 )
            {
              if ( !v58 )
                goto LABEL_203;
              NetManager_LogMessage("Waiting for server to finish loading map...\n");
              v75 = (char *)Config_GetLocalizedString("mp/load_server_map_wait");
              LoadingScreen_UpdateText(Flow_ptFlow->pxLoadingScreen, v75);
              if ( NetManager_WaitUntilState(false, 2, 0.15000000596046448, 50) == false )
              {
                v76 = (char *)Config_GetLocalizedString("mp/load_server_map_failed");
                LoadingScreen_UpdateText(Flow_ptFlow->pxLoadingScreen, v76);
                Sleep(0x1388u);
                LoadingScreen_Delete(Flow_ptFlow->pxLoadingScreen);
                Flow_ptFlow->pxLoadingScreen = nullptr;
                NetManager_LeaveGame();
                NetManager_Quit();
                return;
              }
              NetManager_LogMessage("Server finished loading map\n");
              v77 = (char *)Config_GetLocalizedString("mp/load_server_map_OK");
              LoadingScreen_UpdateText(Flow_ptFlow->pxLoadingScreen, v77);
              v58 = igi2_frame.ptParent.tQTaskRefList.ptHead;
              v74 = igi2_frame.v101;
            }
            if ( v58 )
            {
LABEL_201:
              v4 = Flow_ptFlow;
              v80 = Flow_ptFlow->pxLoadingScreen;
              if ( !v80 )
                goto LABEL_223;
              LoadingScreen_Delete(v80);
              Flow_ptFlow->pxLoadingScreen = nullptr;
              NetManager_LogMessage("Deleted loading screen\n");
              goto LABEL_222;
            }
            if ( v74 )
            {
              v78 = (char *)Config_GetLocalizedString("mp/load_gamespy");
              LoadingScreen_UpdateText(Flow_ptFlow->pxLoadingScreen, v78);
              NetManager_CreateASE();
              v79 = (char *)Config_GetLocalizedString("mp/load_ASE");
              LoadingScreen_UpdateText(Flow_ptFlow->pxLoadingScreen, v79);
              NetManager_CreateGameSpy();
              NetManager_StartConsoleListener();
              goto LABEL_201;
            }
LABEL_203:
            NetManager_LogMessage("Flow: Waiting for server to respond to connect request...\n");
            v81 = (char *)Config_GetLocalizedString("mp/load_accept_wait");
            LoadingScreen_UpdateText(Flow_ptFlow->pxLoadingScreen, v81);
            v82 = NetManager_BlockClientConnect(50, 4500);
            if ( v82 == false )
            {
              v83 = (char *)Config_GetLocalizedString("mp/load_lostcontact");
              LoadingScreen_UpdateText(Flow_ptFlow->pxLoadingScreen, v83);
              NetManager_LogMessage("Flow: Client did not receive any connect response from server\n");
            }
            if ( NetManager_IsNetworkConnected() == false || v82 == false )
            {
              switch ( Network_nLastConnectionResponse )
              {
                case 0u:
                  igi2_frame.v91 = Config_GetLocalizedString("mp/load_access_unknown");
                  _snprintf(igi2_frame.zText, 0xFFu, "[0] %s", igi2_frame.v91);
                  break;
                case 1u:
                  igi2_frame.v92 = Config_GetLocalizedString("mp/load_access_password");
                  _snprintf(igi2_frame.zText, 0xFFu, "[1] %s", igi2_frame.v92);
                  break;
                case 2u:
                  igi2_frame.v93 = Config_GetLocalizedString("mp/load_access_banned");
                  _snprintf(igi2_frame.zText, 0xFFu, "[2] %s", igi2_frame.v93);
                  break;
                case 3u:
                  igi2_frame.v94 = Config_GetLocalizedString("mp/load_access_full");
                  _snprintf(igi2_frame.zText, 0xFFu, "[3] %s", igi2_frame.v94);
                  break;
                case 4u:
                  igi2_frame.v95 = Config_GetLocalizedString("mp/load_access_wrongmap");
                  _snprintf(igi2_frame.zText, 0xFFu, "[4] %s", igi2_frame.v95);
                  break;
                case 5u:
                  igi2_frame.v96 = Config_GetLocalizedString("mp/load_access_noID");
                  _snprintf(igi2_frame.zText, 0xFFu, "[5] %s", igi2_frame.v96);
                  break;
                case 6u:
                  igi2_frame.v97 = Config_GetLocalizedString("mp/load_access_IN_USE");
                  _snprintf(igi2_frame.zText, 0xFFu, "[6] %s", igi2_frame.v97);
                  break;
                case 8u:
                  igi2_frame.v98 = Config_GetLocalizedString("mp/load_access_noresponse");
                  _snprintf(igi2_frame.zText, 0xFFu, "[7] %s", igi2_frame.v98);
                  break;
                default:
                  igi2_frame.v99 = Config_GetLocalizedString("mp/load_access_unknown");
                  _snprintf(igi2_frame.zText, 0xFFu, "[8] %s", igi2_frame.v99);
                  break;
              }
              NetManager_LogMessage(igi2_frame.zText);
              LoadingScreen_UpdateText(Flow_ptFlow->pxLoadingScreen, igi2_frame.zText);
              Sleep(0x1388u);
              LoadingScreen_Delete(Flow_ptFlow->pxLoadingScreen);
              Flow_ptFlow->pxLoadingScreen = nullptr;
              NetManager_AbortInit();
              v4 = Flow_ptFlow;
              Flow_ptFlow->eRequestedEvent = 6;
LABEL_223:
              v87 = v4->pxLoadingScreen;
              if ( v87 )
              {
                LoadingScreen_Delete(v87);
                Flow_ptFlow->pxLoadingScreen = nullptr;
                NetManager_LogMessage("Deleted loading screen\n");
LABEL_229:
                v4 = Flow_ptFlow;
              }
              break;
            }
            v84 = (char *)Config_GetLocalizedString("mp/load_initcontact");
            LoadingScreen_UpdateText(Flow_ptFlow->pxLoadingScreen, v84);
            NetManager_LogMessage("Flow: Client connection success\n");
            goto LABEL_201;
          }
        }
        else
        {
          p_pxLoadingScreen = &Flow_ptFlow->pxLoadingScreen;
          if ( !Flow_ptFlow->pxLoadingScreen )
          {
            NetManager_LogMessage("Created loading screen\n");
            v86 = LoadingScreen_New(10, Game_iMissionID, true);
            p_pxLoadingScreen = &Flow_ptFlow->pxLoadingScreen;
            Flow_ptFlow->pxLoadingScreen = v86;
            LoadingScreen_SetTextColour(v86, 1.0, 1.0, 1.0);
          }
          Game_New(ptQTask, *p_pxLoadingScreen);
          LoadingScreen_Delete(Flow_ptFlow->pxLoadingScreen);
          Flow_ptFlow->pxLoadingScreen = nullptr;
          NetManager_LogMessage("Deleted loading screen\n");
          Flow_SetFrequency(30);
        }
LABEL_222:
        v4 = Flow_ptFlow;
        goto LABEL_223;
      case 5:
        if ( Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER )
        {
          v88 = v4->ptNetManagerQTask;
          v88[8].tQTaskRefList.ptMiddle = nullptr;
          v88[9].tQTaskRefList.ptMiddle = (struct QReference_s *)-1;
          NetManager_LogMessage((char *)&stru_6A1E00.tServerGameSettings.nMissionTime);
        }
        Game_Restart();
        NetManager_SetStartGameStatus(true);
        Flow_SetFrequency(30);
        v89 = Flow_ptFlow;
        Flow_ptFlow->eCurrentEvent = 4;
        Timer_nTicks = v89->nTicks;
        return;
      case 6:
      case 7:
        if ( Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER )
        {
          v52 = v4->ptNetManagerQTask;
          v52[8].tQTaskRefList.ptMiddle = nullptr;
          v52[9].tQTaskRefList.ptMiddle = (struct QReference_s *)-1;
          NetManager_LogMessage((char *)&stru_6A1E00.tServerGameSettings.nMissionTime);
          v4 = Flow_ptFlow;
        }
        if ( Game_ptGame )
        {
          QTask_Delete(&Game_ptGame->tQTask);
          v4 = Flow_ptFlow;
        }
        v4->eCurrentEvent = 3;
LABEL_121:
        if ( Game_eGameMode && AppContext_tAppContext.isEditorState == false )
        {
          v4->eRequestedEvent = 1;
          Timer_nTicks = v4->nTicks;
          return;
        }
        Game_LoadFontResource("LOCAL:common/fonts/fonts_med.res");
        if ( !MenuManager_ptQTask )
          MenuManager_New(Flow_ptFlow->ptScreenQTask, "LOCAL:menusystem\\mainmenu.qsc", true, true, true);
        Game_UnloadFontResource();
        if ( Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER )
        {
          if ( eRequestedEvent == 6 )
          {
            MenuManager_PushScreen(900, 2, 0);
            MenuManager_PushScreen(917, 2, 0);
            MenuManager_PushScreen(924, 2, 0);
          }
          else if ( eRequestedEvent == 7 )
          {
            MenuManager_PushScreen(900, 2, 0);
            MenuManager_PushScreen(917, 2, 0);
            MenuManager_PushScreen(919, 2, 0);
          }
        }
        goto LABEL_229;
      case 8:
        v90 = v4->ptScreenQTask;
        igi2_frame.ptParent.ptPrev = (struct QTask_s *)IntroScreen_azOutroMoviesToPlay;
        igi2_frame.ptParent.ptNext = (struct QTask_s *)1;
        igi2_frame.ptParent.tQTaskChildren.ptHead = (struct QTask_s *)1;
        QTask_NewFn(v90, IntroScreen_eQTaskType, &igi2_frame.ptParent);
        dword_6C02F8 = 1;
        goto LABEL_229;
      case 10:
        strncpy(ClientConfig_tClientConfig.zPlayerName, AppContext_tAppContext.zPlayer, 0x40u);
        igi2_frame.ptParent.tQTaskRefList.ptHead = (struct QReference_s *)strlen(ClientConfig_tClientConfig.zPlayerPassword);
        if ( !igi2_frame.ptParent.tQTaskRefList.ptHead )
          strncpy(ClientConfig_tClientConfig.zPlayerPassword, AppContext_tAppContext.zPassword, 0x40u);
        Game_SetDisplayMode();
        StatusMessageScreen_LoadResource();
        if ( !Flow_ptFlow->pxLoadingScreen )
        {
          NetManager_LogMessage("Created loading screen\n");
          v53 = LoadingScreen_New(10, Game_iMissionID, true);
          Flow_ptFlow->pxLoadingScreen = v53;
          LoadingScreen_SetTextColour(v53, 1.0, 1.0, 1.0);
        }
        _snprintf(
          (char *const)&igi2_frame.ptParent.tQTaskRefList.ptMiddle,
          0x1Eu,
          "[%s:%d]",
          AppContext_tAppContext.zIP,
          AppContext_tAppContext.nPort);
        igi2_frame.v103 = 0;
        Config_SetLocalizedPhrase(
          igi2_frame.zText,
          "mp/load_response_wait",
          (char *)&igi2_frame.ptParent.tQTaskRefList.ptMiddle,
          nullptr,
          nullptr);
        LoadingScreen_UpdateText(Flow_ptFlow->pxLoadingScreen, igi2_frame.zText);
        NetManager_LogMessage("Flow: Waiting for server response....(max 25 seconds)\n");
        if ( NetManager_FindSession(AppContext_tAppContext.zIP, AppContext_tAppContext.nPort, 25000) )
        {
          NetManager_LogMessage("Flow: Found game at ip:port, starting client...\n");
          v54 = (char *)Config_GetLocalizedString("mp/load_game_found");
          LoadingScreen_UpdateText(Flow_ptFlow->pxLoadingScreen, v54);
          v55 = Flow_ptFlow;
          Flow_ptFlow->eRequestedEvent = 4;
        }
        else
        {
          NetManager_LogMessage("Flow: Could not find game at given socket, exiting to menu...\n");
          v56 = (char *)Config_GetLocalizedString("mp/load_game_not_found");
          LoadingScreen_UpdateText(Flow_ptFlow->pxLoadingScreen, v56);
          Sleep(0x1388u);
          LoadingScreen_Delete(Flow_ptFlow->pxLoadingScreen);
          Flow_ptFlow->pxLoadingScreen = nullptr;
          NetManager_LogMessage("Deleted loading screen\n");
          v55 = Flow_ptFlow;
          Flow_ptFlow->eRequestedEvent = 6;
        }
        Timer_nTicks = v55->nTicks;
        return;
      case 11:
LABEL_114:
        longjmp(App_tLongJumpEnv, 1);
      default:
        break;
    }
  }
  Timer_nTicks = v4->nTicks;
}

// source: j/0/flow.c:1215  [anchor-mhash]
void __cdecl Flow_DeleteHandler(struct QTask_s *ptQTask)
{
  AppContext_tAppContext.pfActivateCallback = nullptr;
  AppContext_tAppContext.pxActivateCallbackContext = nullptr;
  Config_Save("LOCAL:config.qsc");
  PhysicsObjType_Delete();
  QTask_Delete(Flow_ptFlow->ptAlwaysRunQTask);
  Flow_ptFlow = nullptr;
}

// source: j/0/flow.c:1241  [anchor-hash]
void __cdecl Flow_NetSave()
{
  if ( Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER )
    NetworkConfig_Save("networkconfig.cfg");
}

// source: j/0/flow.c:1250  [size]
void __cdecl Flow_NetLoad()
{
  NetworkConfig_Load("networkconfig.cfg");
}

// source: j/0/flow.c:1259  [anchor-hash]
void __cdecl Flow_LeaveNetGame()
{
  if ( Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER )
    NetManager_LeaveGame();
}

// source: j/0/flow.c:1282  [anchor-mhash]
struct Result_s *__cdecl Flow_RequestEventCB(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  struct ArgList_s *v3; // edi
  struct ArgList_s *v4; // eax
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  v3 = ptArgList;
  if ( ptArgList->isQVM )
  {
    ptArgList = nullptr;
    QVM_EvalArg(&ptArgList, 4, v3, 0, 1);
    v4 = ptArgList;
  }
  else
  {
    v4 = (struct ArgList_s *)Expression_EvalInt(*ptArgList->aptExpression);
  }
  Flow_ptFlow->eRequestedEvent = (int)v4;
  Rs.nResult = 1;
  Rs.vResult = 1.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/flow.c:1311  [size]
unsigned __int16 __cdecl Flow_GetQTaskType()
{
  return Flow_eQTaskType;
}

// source: j/0/flow.c:1327  [size]
struct QTask_s *__cdecl Flow_New(struct QTask_s *ptParent)
{
  return QTask_NewFn(ptParent, Flow_eQTaskType, nullptr);
}

// source: j/0/flow.c:1343  [anchor-callee]
void __cdecl Flow_SetFrequency(int nFrequency)
{
  DWORD PerformanceCounter; // eax
  struct Flow_t *v2; // ecx

  if ( Timer_isPerformanceCounter )
    PerformanceCounter = Timer_GetPerformanceCounter();
  else
    PerformanceCounter = GetTickCount();
  v2 = Flow_ptFlow;
  Flow_ptFlow->nStartTime = PerformanceCounter - Timer_nStartTime;
  v2->nSkipTime = 0;
  v2->nTicks = 0;
  v2->nTicksDrawn = 0;
  v2->nFrequency = nFrequency;
  v2->isDrawn = 1;
  SoundSys_nFrequency = nFrequency;
  Sound_nFrequency = nFrequency;
}

// source: j/0/flow.c:1365  [size]
int __cdecl Flow_GetFrequency()
{
  return Flow_ptFlow->nFrequency;
}

// source: j/0/flow.c:1378  [size]
struct Flow_t *__cdecl Flow_GetQTask()
{
  return Flow_ptFlow;
}

// source: j/0/flow.c:1393  [size]
struct QTask_s *__cdecl Flow_GetScreenQTask()
{
  return Flow_ptFlow->ptScreenQTask;
}

// source: j/0/flow.c:1409  [size]
struct QTask_s *__cdecl Flow_GetInputPortQTask()
{
  return Flow_ptFlow->ptInputPortQTask;
}

// source: j/0/flow.c:1425  [size]
struct QTask_s *__cdecl Flow_GetNetManagerQTask()
{
  return Flow_ptFlow->ptNetManagerQTask;
}

// source: j/0/flow.c:1441  [anchor-hash]
enum bool __cdecl Flow_IsNetManagerQTask()
{
  return Flow_ptFlow && Flow_ptFlow->ptNetManagerQTask;
}

// source: j/0/flow.c:1454  [size]
enum FlowEvent_e __cdecl Flow_GetActiveEvent()
{
  return Flow_ptFlow->eCurrentEvent;
}

// source: j/0/flow.c:1469  [size]
void __cdecl Flow_RequestEvent(enum FlowEvent_e eFlowEvent)
{
  Flow_ptFlow->eRequestedEvent = eFlowEvent;
}

// source: j/0/flow.c:1484  [size]
int __cdecl Flow_GetTicks()
{
  return Flow_ptFlow->nTicks;
}

// source: j/0/flow.c:1499  [size]
int __cdecl Flow_GetTicksDrawn()
{
  return Flow_ptFlow->nTicksDrawn;
}

// source: j/0/flow.c:1514  [anchor-hash]
void __cdecl Flow_SuspendTiming()
{
  DWORD PerformanceCounter; // eax

  if ( !Flow_nSuspendRefCount )
  {
    if ( Timer_isPerformanceCounter )
      PerformanceCounter = Timer_GetPerformanceCounter();
    else
      PerformanceCounter = GetTickCount();
    Flow_nSuspendTime = PerformanceCounter - Timer_nStartTime;
  }
  ++Flow_nSuspendRefCount;
}

// source: j/0/flow.c:1532  [anchor-mhash]
void __cdecl Flow_ResumeTiming()
{
  DWORD PerformanceCounter; // eax

  if ( !--Flow_nSuspendRefCount )
  {
    if ( Timer_isPerformanceCounter )
      PerformanceCounter = Timer_GetPerformanceCounter();
    else
      PerformanceCounter = GetTickCount();
    Flow_ptFlow->nSkipTime += PerformanceCounter - Timer_nStartTime - Flow_nSuspendTime;
    Flow_nSuspendTime = 0;
  }
}

// source: j/0/flow.c:1554  [size]
void __cdecl Flow_CheckDebugRestartTimer()
{
  ;
}

// source: j/0/flow.c:1590  [size]
int __cdecl Flow_SetOverrideActivePlayerProfile(int iOverrideActivePlayerProfile)
{
  Flow_iOverrideActivePlayerProfile = iOverrideActivePlayerProfile;
  return iOverrideActivePlayerProfile;
}

// source: j/0/flow.c:1606  [anchor-strings]
void __cdecl Flow_Open()
{
  unsigned __int16 BaseQTaskType; // ax
  unsigned __int16 v1; // si

  BaseQTaskType = QTask_GetBaseQTaskType();
  v1 = QTask_NewQTaskType("Flow", 104, BaseQTaskType, 0, 0);
  Flow_eQTaskType = v1;
  QTask_LinkQTaskEventHandlerFn(v1, 0, Flow_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 1, Flow_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 2, Flow_DeleteHandler);
  Flow_eDrawInterpolateQTaskEvent = QTask_NewQTaskEventNoContextFn(0, "Flow-DrawInterpolate");
  Flow_ptDrawInterpolateQTaskList = QTaskList_New(255);
  Symbol_Register(
    "FLOW_EVENT_QUIT",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)1,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "FLOW_EVENT_INTRO",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)2,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "FLOW_EVENT_MAINMENU",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)3,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "FLOW_EVENT_GAME",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)4,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "FLOW_EVENT_RESTART_GAME",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)5,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "Flow_RequestEvent",
    Flow_RequestEventCB,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "Flow_IsPlayCredits",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))pfSymbolParse__,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  AppMain_FindPrefix(
    AppContext_tAppContext.zCmdLine,
    "screenshot",
    (void (__cdecl *)(char *))Flow_ParseScreenshotCmdLineArgs);
}

// source: j/0/flow.c:1668  [size]
int __cdecl Flow_GetDrawInterpolateQTaskEvent()
{
  return Flow_eDrawInterpolateQTaskEvent;
}

// source: j/0/flow.c:1683  [size]
struct QTaskList_s *__cdecl Flow_GetDrawInterpolateQTaskList()
{
  return Flow_ptDrawInterpolateQTaskList;
}

// source: j/0/flow.c:1696  [size]
void __cdecl Flow_EnableDrawInterpolation(enum bool isEnabled)
{
  Flow_ptFlow->isDrawInterpolateEnabled = isEnabled != false;
}

// source: j/0/flow.c:1716  [size]
enum bool __cdecl Flow_IsDrawInterpolateFrame()
{
  return Flow_ptFlow->isDrawInterpolateFrame;
}
