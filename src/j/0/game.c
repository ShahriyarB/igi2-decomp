/* j/0/game.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/game.c:123  [anchor-callee]
void __cdecl Game_KillSoundTasks(struct QTask_s *ptParent)
{
  struct QTask_s *ptHead; // edi
  struct QTask_s *v2; // esi

  if ( ptParent )
  {
    ptHead = ptParent->tQTaskChildren.ptHead;
    if ( ptHead->ptNext )
    {
      if ( ptHead )
      {
        do
        {
          Game_KillSoundTasks(ptHead);
          if ( ptHead->ptNext )
            v2 = ptHead->ptNext->ptNext != nullptr ? ptHead->ptNext : nullptr;
          else
            v2 = nullptr;
          if ( QTask_IsQTaskTypeDerived(ptHead->eQTaskType, SoundDefBase_eQTaskType) )
            QTask_Delete(ptHead);
          ptHead = v2;
        }
        while ( v2 );
      }
    }
  }
}

// source: j/0/game.c:153  [size]
void __cdecl Game_LoadFontsDirListCallback(
        struct FileDirListCallbackContext_s *ptDirListCallbackContext,
        void *pxContext)
{
  FontManager_LoadFont(ptDirListCallbackContext->zFilename);
}

// source: j/0/game.c:166  [anchor-mhash]
void __cdecl Game_UnloadFontsDirListCallback(
        struct FileDirListCallbackContext_s *ptDirListCallbackContext,
        void *pxContext)
{
  struct ManagedFont_s *FontByName; // eax
  struct ManagedFont_s *v3; // esi
  struct QSprite_s *ptFont; // eax

  FontByName = FontManager_FindFontByName(ptDirListCallbackContext->zFilename);
  v3 = FontByName;
  if ( FontByName )
  {
    if ( FontByName->nRefCount-- == 1 )
    {
      ptFont = FontByName->ptFont;
      if ( v3->ptFont )
        Font_ForceDelete(ptFont);
      QObjectVector_RemoveElement(
        FontManager_ptQObjectVector,
        *(_DWORD *)((char *)v3 + FontManager_ptQObjectVector->nElementSize - 4));
    }
  }
}

// source: j/0/game.c:179  [anchor-strings]
void __cdecl Game_UnloadFontResource()
{
  int v0; // eax
  char zFilename[4]; // [esp+4h] [ebp-4h] BYREF

  Resource_DirList("LOCAL:common/fonts", Game_UnloadFontsDirListCallback, nullptr);
  if ( Resource_IsLoadedInternal(Game_pzFontResource, (struct Resource_s **)zFilename) )
  {
    v0 = *(_DWORD *)(*(_DWORD *)zFilename + 36);
    if ( v0 != 3 && v0 != 1 )
      Resource_Remove(*(struct Resource_s **)zFilename);
  }
}

// source: j/0/game.c:194  [anchor-strings]
void __cdecl Game_LoadFontResource(char *pzFontResource)
{
  char *v1; // ebx
  char *v2; // ecx
  void *v3; // eax
  char zFilename[4]; // [esp+8h] [ebp-4h] BYREF

  v1 = pzFontResource;
  if ( !pzFontResource )
  {
    if ( Display_tActiveMode.nWidth > 800 )
    {
      v1 = "LOCAL:common/fonts/fonts_med.res";
      if ( Display_tActiveMode.nWidth >= 1280 )
        v1 = "LOCAL:common/fonts/fonts_hi.res";
    }
    else
    {
      v1 = "LOCAL:common/fonts/fonts_lo.res";
    }
  }
  Game_pzFontResource = v1;
  if ( Resource_IsLoadedInternal(v1, (struct Resource_s **)zFilename) )
  {
    *(_DWORD *)(*(_DWORD *)zFilename + 44) = 1;
  }
  else
  {
    Game_MPRunNetwork(v2);
    v3 = File_Load(v1, (unsigned int *)zFilename);
    if ( !v3 )
    {
      LDebug_Error("Failed to load resource: '%s'", v1);
      abort();
    }
    Resource_ParseFile(File_zLastSubstitutedPath, v3, *(unsigned int *)zFilename);
  }
  Resource_DirList("LOCAL:common/fonts", Game_LoadFontsDirListCallback, nullptr);
}

// source: j/0/game.c:231  [anchor-mhash]
char *__cdecl Game_GetCarryoverFilename(char *zFilename, int nMissionID)
{
  sprintf(
    zFilename,
    "savegames/missions/co%02d%02d%02d.qsc",
    Config_tConfig.iActiveProfile,
    Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eDifficultyLevel,
    nMissionID);
  return zFilename;
}

// source: j/0/game.c:260  [anchor-caller]
void __cdecl Game_SaveCarryover(int nMissionID)
{
  #pragma pack(push, 1)
  union
  {
    struct { enum GameDifficulty_e eDifficultyLevel; };
    struct { char igi2_o1[24]; struct SaveGame_s ptSaveGame; };
    struct { char igi2_o2[40]; char Buffer[264]; };
    char igi2_extent[304];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  void *pxObject; // edi
  int v2; // eax

  if ( Level_atLevelQTaskID[0] )
  {
    pxObject = Level_atLevelQTaskID[0]->pxObject;
    if ( pxObject )
    {
      if ( QTask_IsQTaskTypeDerived(*((_WORD *)pxObject + 18), HumanPlayer_eQTaskType) && !*((_BYTE *)pxObject + 1180) )
      {
        v2 = *((_DWORD *)pxObject + 865);
        if ( v2 )
          Weapon_Activate(*((struct QTask_s **)pxObject + 330), (char *)(v2 + 84), true);
        memset(&igi2_frame.ptSaveGame, 0, sizeof(igi2_frame.ptSaveGame));
        igi2_frame.eDifficultyLevel = Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eDifficultyLevel;
        igi2_frame.ptSaveGame.isValid = 1;
        igi2_frame.ptSaveGame.nMissionID = nMissionID;
        igi2_frame.ptSaveGame.nVersion = 63;
        Serialize_isForceSerializeChildren = true;
        sprintf(
          igi2_frame.Buffer,
          "savegames/missions/co%02d%02d%02d.qsc",
          Config_tConfig.iActiveProfile,
          igi2_frame.eDifficultyLevel,
          nMissionID);
        SaveGame_Create(igi2_frame.Buffer, *((struct QTask_s **)pxObject + 330), &igi2_frame.ptSaveGame, nullptr);
        Serialize_isForceSerializeChildren = false;
      }
    }
  }
}

// source: j/0/game.c:304  [anchor-callee]
void __cdecl Game_LoadCarryOver(int nMissionID)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct SaveGame_s tSaveGame; };
    struct { char igi2_o1[16]; char zFilename[264]; };
    char igi2_extent[280];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *pxObject; // esi

  if ( Level_atLevelQTaskID[0] )
  {
    pxObject = (struct QTask_s *)Level_atLevelQTaskID[0]->pxObject;
    if ( pxObject )
    {
      if ( QTask_IsQTaskTypeDerived(pxObject->eQTaskType, HumanPlayer_eQTaskType)
        && BYTE2(pxObject[80].tQTaskRefList.ptMiddle) )
      {
        sprintf(
          igi2_frame.zFilename,
          "savegames/missions/co%02d%02d%02d.qsc",
          Config_tConfig.iActiveProfile,
          Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eDifficultyLevel,
          nMissionID);
        if ( SaveGame_LoadFile(&igi2_frame.tSaveGame, igi2_frame.zFilename, true, nullptr) )
          SaveGame_LoadFile(&igi2_frame.tSaveGame, igi2_frame.zFilename, false, pxObject);
      }
    }
  }
}

// source: j/0/game.c:342  [anchor-callee]
void __cdecl Game_MPRunNetwork(char *zDesc)
{
  DWORD PerformanceCounter; // eax
  struct Flow_t *v2; // edx

  if ( Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER
    && Game_ptGame
    && (AppContext_tAppContext.isServer || QTask_GetFirstChildOfType(Flow_ptFlow->ptNetManagerQTask, Client_eQTaskType)) )
  {
    if ( Timer_isPerformanceCounter )
      Timer_GetPerformanceCounter();
    else
      GetTickCount();
    if ( Timer_isPerformanceCounter )
      PerformanceCounter = Timer_GetPerformanceCounter();
    else
      PerformanceCounter = GetTickCount();
    v2 = Flow_ptFlow;
    Game_ptGame[1].tQTask.ptNext = (struct QTask_s *)(PerformanceCounter - Timer_nStartTime);
    ((void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[1][v2->ptNetManagerQTask->eQTaskType].pfHandler)(v2->ptNetManagerQTask);
  }
}

// source: j/0/game.c:386  [anchor-callee]
void __cdecl Game_SaveCarryoverMP(int nMissionID)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct QTask_s *ptNext; };
    struct { char igi2_o1[44]; struct Client_s *ptClient; };
    struct { char igi2_o2[48]; struct SaveGame_s tSaveGame; };
    struct { char igi2_o3[64]; char zFilename[264]; };
    char igi2_extent[328];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  char *v1; // ecx
  struct QTask_s *p_tQTask; // esi
  int v3; // ebx
  unsigned __int16 v4; // dx
  struct QTask_s *v5; // eax
  struct QTask_s *ptHead; // eax
  struct QTask_s *v7; // esi

  p_tQTask = nullptr;
  v3 = 0;
  Game_MPRunNetwork(v1);
  v4 = Client_eQTaskType;
  while ( 1 )
  {
    v5 = p_tQTask
       ? QTask_GetNextSiblingOfType(p_tQTask, v4)
       : QTask_GetFirstChildOfType(Flow_ptFlow->ptNetManagerQTask, v4);
    igi2_frame.ptClient = (struct Client_s *)v5;
    if ( !v5 )
      break;
    ptHead = v5[16].tQTaskChildren.ptHead;
    if ( ptHead )
    {
      v7 = ptHead->tQTaskChildren.ptHead;
      if ( v7 )
      {
        if ( QTask_IsQTaskTypeDerived(v7->eQTaskType, Human_eQTaskType) )
        {
          sprintf(igi2_frame.zFilename, "savegames/missions/comp%02d%02d.qsc", nMissionID, v3);
          memset(&igi2_frame.tSaveGame, 0, 12);
          igi2_frame.tSaveGame.isValid = 1;
          Serialize_isForceSerializeChildren = true;
          igi2_frame.ptNext = v7[33].ptNext;
          igi2_frame.tSaveGame.nMissionID = nMissionID;
          igi2_frame.tSaveGame.nVersion = 63;
          SaveGame_Create(igi2_frame.zFilename, igi2_frame.ptNext, &igi2_frame.tSaveGame, nullptr);
          v4 = Client_eQTaskType;
          Serialize_isForceSerializeChildren = false;
          ++v3;
        }
      }
    }
    p_tQTask = &igi2_frame.ptClient->tQTask;
  }
}

// source: j/0/game.c:438  [anchor-callee]
void __cdecl Game_LoadCarryOverMP(int nMissionID)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct SaveGame_s tSaveGame; };
    struct { char igi2_o1[16]; char zFilename[264]; };
    char igi2_extent[280];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *v1; // ebx
  int i; // ebp
  struct QTask_s *v3; // eax
  struct QTask_s *ptHead; // eax
  struct QTask_s *v5; // esi
  struct QTask_s *ptPrev; // eax
  struct QTask_s *ptTail; // edx
  unsigned __int16 v8; // cx
  unsigned __int16 eQTaskType; // ax

  v1 = nullptr;
  for ( i = 0; ; ++i )
  {
    v3 = v1
       ? QTask_GetNextSiblingOfType(v1, Client_eQTaskType)
       : QTask_GetFirstChildOfType(Flow_ptFlow->ptNetManagerQTask, Client_eQTaskType);
    v1 = v3;
    if ( !v3 )
      break;
    ptHead = v3[16].tQTaskChildren.ptHead;
    if ( ptHead )
    {
      v5 = ptHead->tQTaskChildren.ptHead;
      if ( v5 )
      {
        if ( QTask_IsQTaskTypeDerived(v5->eQTaskType, Human_eQTaskType) )
        {
          sprintf(igi2_frame.zFilename, "savegames/missions/comp%02d%02d.qsc", nMissionID, i);
          if ( SaveGame_LoadFile(&igi2_frame.tSaveGame, igi2_frame.zFilename, true, nullptr) )
          {
            SaveGame_LoadFile(&igi2_frame.tSaveGame, igi2_frame.zFilename, false, v5);
            ptPrev = v5[33].ptNext[1].ptPrev;
            if ( ptPrev )
            {
              ptTail = ptPrev->tQTaskChildren.ptTail;
              if ( ptTail )
              {
                v8 = HumanPlayer_eQTaskType;
                eQTaskType = v5->eQTaskType;
                *(float *)&v5[20].tQTaskChildren.ptTail = (float)(int)ptTail[3].tQTaskRefList.ptTail;
                if ( QTask_IsQTaskTypeDerived(eQTaskType, v8) )
                {
                  v5[76].ptParent = (struct QTask_s *)ptTail[3].tQTaskRefList.ptTail;
                  HumanPlayer_SelectWeapon(v5, 0);
                }
              }
            }
          }
        }
      }
    }
  }
}

// source: j/0/game.c:499  [anchor-mhash]
void __cdecl Game_DeleteTerrainLightmaps(struct QTask_s *ptQTask)
{
  struct QTask_s *ptHead; // esi
  struct QTask_s *v2; // ecx

  ptHead = ptQTask->tQTaskChildren.ptHead;
  if ( ptHead->ptNext && ptHead )
  {
    do
    {
      v2 = ptHead;
      if ( ptHead->ptNext )
        ptHead = ptHead->ptNext->ptNext != nullptr ? ptHead->ptNext : nullptr;
      else
        ptHead = nullptr;
      if ( v2->eQTaskType == TerrainLightMap_eQTaskType )
        QTask_Delete(v2);
      else
        Game_DeleteTerrainLightmaps(v2);
    }
    while ( ptHead );
  }
}

// source: j/0/game.c:591  [anchor-mhash]
struct Result_s *__cdecl Game_DisablePlayerInputCB(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  struct QReference_s **v3; // esi
  int v4; // ebp
  _BYTE *pxObject; // edx
  struct Result_s Rs; // [esp+Ch] [ebp-18h] BYREF

  v3 = &Game_ptGame->aptPlayerQTaskRef[2];
  v4 = 4;
  do
  {
    if ( *v3 )
    {
      pxObject = (*v3)->pxObject;
      if ( pxObject )
      {
        memset(pxObject + 512, 0, 0xFCu);
        memset(pxObject + 764, 0, 0xFCu);
        pxObject[1016] = 1;
      }
    }
    ++v3;
    --v4;
  }
  while ( v4 );
  Rs.nResult = 1;
  Rs.vResult = 1.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/game.c:620  [anchor-mhash]
struct Result_s *__cdecl Game_EnablePlayerInputCB(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  struct Game_s *v3; // ecx
  struct QReference_s *v4; // eax
  _BYTE *pxObject; // eax
  struct QReference_s *v6; // eax
  _BYTE *v7; // eax
  int nScore; // eax
  int v9; // eax
  int v10; // eax
  int v11; // eax
  struct Result_s Rs; // [esp+0h] [ebp-18h] BYREF

  v3 = Game_ptGame;
  v4 = Game_ptGame->aptPlayerQTaskRef[2];
  if ( v4 )
  {
    pxObject = v4->pxObject;
    if ( pxObject )
      pxObject[1016] = 0;
  }
  v6 = v3->aptPlayerQTaskRef[3];
  if ( v6 )
  {
    v7 = v6->pxObject;
    if ( v7 )
      v7[1016] = 0;
  }
  nScore = v3->atPlayerStatus[0].nScore;
  if ( nScore )
  {
    v9 = *(_DWORD *)(nScore + 8);
    if ( v9 )
      *(_BYTE *)(v9 + 1016) = 0;
  }
  v10 = v3->atPlayerStatus[1].nScore;
  if ( v10 )
  {
    v11 = *(_DWORD *)(v10 + 8);
    if ( v11 )
      *(_BYTE *)(v11 + 1016) = 0;
  }
  Rs.nResult = 1;
  Rs.vResult = 1.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/game.c:649  [size]
void __cdecl Game_SetDisplayMode()
{
  int v0; // edx
  int nDisplayWidth; // eax
  char *v2; // ecx
  char *v3; // ecx
  struct DisplayMode_s tDisplayMode; // [esp+8h] [ebp-128h] BYREF

  v0 = 2752 * Config_tConfig.iActiveProfile + 7392072;
  memset(&tDisplayMode, 0, sizeof(tDisplayMode));
  nDisplayWidth = Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGraphicOptions.nDisplayWidth;
  tDisplayMode.nHeight = Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGraphicOptions.nDisplayHeight;
  tDisplayMode.nBitsPerPixel = Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGraphicOptions.nDisplayDepth;
  tDisplayMode.eRenderMode = Direct3D_eRenderMode;
  tDisplayMode.nWidth = nDisplayWidth;
  v2 = (char *)(2752 * Config_tConfig.iActiveProfile + 7392400);
  tDisplayMode.isCleared = 1;
  tDisplayMode.nBackBuffers = 1;
  tDisplayMode.isZBuffer = 1;
  if ( 2752 * Config_tConfig.iActiveProfile == -7392400 )
    v2 = (char *)&g_zInitialValue;
  strcpy(tDisplayMode.zDeviceDescription, v2);
  v3 = (char *)(v0 + 72);
  if ( v0 == -72 )
    v3 = (char *)&g_zInitialValue;
  strcpy(tDisplayMode.zDeviceIdentifier, v3);
  tDisplayMode.isLockableBackbuffer = 0;
  Display_SetMode(&tDisplayMode);
  Display_tBackgroundColor.nX = 170;
  Display_tBackgroundColor.nY = 132;
  Display_tBackgroundColor.nZ = 132;
}

// source: j/0/game.c:720  [size]
struct Result_s *__cdecl Game_SetGameModeCB(
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
  Game_eGameMode = (enum GameMode_e)v4;
  Rs.nResult = 1;
  Rs.vResult = 1.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/game.c:737  [size]
struct Result_s *__cdecl Game_GetGameModeCB(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  Rs.nResult = Game_eGameMode;
  Rs.vResult = (double)(int)Game_eGameMode;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/game.c:750  [size]
enum GameMode_e __cdecl Game_SetGameMode(enum GameMode_e eGameMode)
{
  Game_eGameMode = eGameMode;
  return eGameMode;
}

// source: j/0/game.c:763  [size]
struct Result_s *__cdecl Game_SetMissionCB(
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
  Game_iMissionID = (int)v4;
  Rs.nResult = 1;
  Rs.vResult = 1.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/game.c:782  [size]
struct Result_s *__cdecl Game_UpdateVolumeCB(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  Sound_SetVolumeCD(
    Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tSoundOptions.vMusicVolume,
    Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tSoundOptions.vMusicVolume);
  Sound_vSSMasterVolume = Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tSoundOptions.vSoundEffectsVolume;
  Rs.nResult = 1;
  Rs.vResult = 1.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/game.c:799  [size]
struct Result_s *__cdecl Game_SetMusicVolumeCB(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  struct ArgList_s *v3; // edi
  double v4; // st7
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  v3 = ptArgList;
  if ( ptArgList->isQVM )
  {
    *(float *)&ptArgList = 0.0;
    QVM_EvalArg(&ptArgList, 4, v3, 0, 2);
    v4 = *(float *)&ptArgList;
  }
  else
  {
    v4 = Expression_EvalFloat(*ptArgList->aptExpression);
  }
  *(float *)&ptArgList = v4;
  Sound_SetVolumeCD(*(float *)&ptArgList, *(float *)&ptArgList);
  Rs.nResult = 1;
  Rs.vResult = 1.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/game.c:820  [size]
struct Result_s *__cdecl Game_SetSFXVolumeCB(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  struct ArgList_s *v3; // edi
  double v4; // st7
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  v3 = ptArgList;
  if ( ptArgList->isQVM )
  {
    *(float *)&ptArgList = 0.0;
    QVM_EvalArg(&ptArgList, 4, v3, 0, 2);
    v4 = *(float *)&ptArgList;
  }
  else
  {
    v4 = Expression_EvalFloat(*ptArgList->aptExpression);
  }
  Sound_vSSMasterVolume = v4;
  Rs.nResult = 1;
  Rs.vResult = 1.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/game.c:841  [anchor-mhash]
struct Result_s *__cdecl Game_EnableMusicCB(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  struct Result_s Rs; // [esp+0h] [ebp-18h] BYREF

  if ( AppContext_tAppContext.isServer == false )
    Game_isMusicEnabled = 1;
  Rs.nResult = 1;
  Rs.vResult = 1.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/game.c:859  [size]
struct Result_s *__cdecl Game_DisableMusicCB(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  Rs.nResult = 1;
  Rs.vResult = 1.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  Game_isMusicEnabled = 0;
  return retstr;
}

// source: j/0/game.c:874  [anchor-mhash]
struct Result_s *__cdecl Game_CutsceneDeleteCB(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  struct QTaskList_s *i; // eax
  struct Result_s Rs; // [esp+0h] [ebp-18h] BYREF

  for ( i = GameFunctions_ptCutsceneDeleteQTaskList;
        GameFunctions_ptCutsceneDeleteQTaskList->nTask;
        i = GameFunctions_ptCutsceneDeleteQTaskList )
  {
    QTask_Delete(i->ptQTask[0]);
  }
  Rs.nResult = 1;
  Rs.vResult = 1.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/game.c:896  [size]
void __cdecl Game_ParseLevelCB(char *zArg)
{
  Game_iMissionID = atoi(zArg);
  AppContext_tAppContext.isEditorState = false;
}

// source: j/0/game.c:913  [anchor-strings]
char *__cdecl Game_GetLoadFont(char *zName, char *zPrefix)
{
  int nWidth; // ebp
  char *v3; // edi

  nWidth = Display_tActiveMode.nWidth;
  strcpy(zName, "common/fonts/loadfont");
  strcat(zName, zPrefix);
  v3 = zName - 1;
  if ( nWidth >= 800 )
  {
    if ( nWidth >= 1024 )
    {
      if ( nWidth >= 1280 )
      {
        while ( *++v3 )
          ;
        strcpy(v3, "1280");
      }
      else
      {
        while ( *++v3 )
          ;
        strcpy(v3, "1024");
      }
    }
    else
    {
      while ( *++v3 )
        ;
      *(_DWORD *)v3 = 3158072;
    }
  }
  else
  {
    while ( *++v3 )
      ;
    *(_DWORD *)v3 = 3159094;
  }
  strcat(zName, ".fnt");
  return (char *)1953392174;
}

// source: j/0/game.c:949  [anchor-strings]
char *__cdecl Game_GetLocalizedSoundDir(char *zBasePath)
{
  struct File_s *v1; // eax

  sprintf(
    g_zOpenMode,
    "%s/%s/sounds.res",
    zBasePath,
    (char *)(16 * Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eLanguage + 6828784));
  v1 = File_New(g_zOpenMode, "r");
  if ( v1 )
  {
    if ( v1 == &File_tDummyAsyncFile )
      File_tDummyAsyncFile.isAsync = false;
    else
      File_atDevice[v1->eDeviceID].pfDelete(v1->eDeviceID, v1);
    sprintf(
      g_zOpenMode,
      "%s/%s",
      zBasePath,
      (char *)(16 * Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eLanguage + 6828784));
    return g_zOpenMode;
  }
  else
  {
    sprintf(g_zOpenMode, "%s/ENGLISH", zBasePath);
    return g_zOpenMode;
  }
}

// source: j/0/game.c:976  [anchor-caller]
void __cdecl Game_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { char zFilename[4]; };
    struct { char igi2_o1[4]; char ArgList[256]; };
    struct { char igi2_o2[260]; char Buffer[264]; };
    char igi2_extent[524];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  DWORD PerformanceCounter; // eax
  DWORD v3; // eax
  struct Mission_s *ptHead; // ecx
  struct Node_s *ptNext; // eax
  int v6; // edx
  int v7; // eax
  char v8; // cl
  bool v9; // zf
  struct Game_s *v10; // eax
  struct World_s *v11; // eax
  struct Game_s *v12; // edx
  struct GameMaterial_s *v13; // eax
  struct QMaterial_t **aptQMaterial; // ecx
  char *v15; // ecx
  char *v16; // ecx
  int v17; // eax
  char v18; // cl
  char *v19; // ecx
  int v20; // eax
  char v21; // cl
  char *v22; // ecx
  void (__cdecl *v23)(void *); // eax
  char *LocalizedSoundDir; // eax
  char *v25; // ecx
  char *v26; // eax
  char *v27; // ecx
  char *v28; // eax
  char *v29; // ecx
  char *v30; // ecx
  int v31; // eax
  struct Sample_s *v32; // eax
  void *v33; // eax
  char *v34; // ecx
  char *v35; // ecx
  unsigned int v36; // eax
  void *v37; // eax
  void *v38; // eax
  struct Game_s *v39; // ecx
  char *v40; // ecx
  char *v41; // ecx
  char *v42; // ecx
  char *v43; // ecx
  struct QTask_s *v44; // eax
  struct Game_s *v45; // ecx
  char *v46; // ecx
  char *v47; // ecx
  char *v48; // ecx
  char *v49; // ecx
  char *v50; // ecx
  void *v51; // eax
  struct Game_s *v52; // esi
  enum InputPortDevice_e v53; // ecx
  struct QViewportQTask_s *ptPrev; // eax
  char *v55; // ecx
  char *v56; // ecx
  char *v57; // ecx
  struct QHashTable_s *v58; // eax
  struct QHashTable_s *v59; // esi
  int v60; // eax
  unsigned int v61; // eax
  struct Game_s *v62; // ecx
  struct QReference_s *v63; // eax
  char *pxObject; // edx

  Game_ptGame = (struct Game_s *)ptQTask;
  *(_DWORD *)&ptQTask[9].eQTaskType = 0;
  if ( Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER )
  {
    Text_SetString(*((struct StaticTilemap_s **)pxContext + 7), "Setting 3D Sound provider...");
    LoadingScreen_UpdateScreen((struct LoadingScreen_s *)pxContext);
    LoadingScreen_UpdateScreen((struct LoadingScreen_s *)pxContext);
    LoadingScreen_UpdateScreen((struct LoadingScreen_s *)pxContext);
  }
  Sound_Set3DProvider(Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tSoundOptions.i3DSoundProvider);
  Flow_SetFrequency(30);
  if ( Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER )
  {
    Text_SetString(*((struct StaticTilemap_s **)pxContext + 7), (char *)&g_ptQText.vR);
    LoadingScreen_UpdateScreen((struct LoadingScreen_s *)pxContext);
    LoadingScreen_UpdateScreen((struct LoadingScreen_s *)pxContext);
    LoadingScreen_UpdateScreen((struct LoadingScreen_s *)pxContext);
  }
  if ( !Flow_nSuspendRefCount )
  {
    if ( Timer_isPerformanceCounter )
      PerformanceCounter = Timer_GetPerformanceCounter();
    else
      PerformanceCounter = GetTickCount();
    Flow_nSuspendTime = PerformanceCounter - Timer_nStartTime;
  }
  ++Flow_nSuspendRefCount;
  if ( Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER )
  {
    v3 = Timer_isPerformanceCounter ? Timer_GetPerformanceCounter() : GetTickCount();
    Game_ptGame[1].tQTask.ptNext = (struct QTask_s *)(v3 - Timer_nStartTime);
    if ( Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER )
    {
      Text_SetString(*((struct StaticTilemap_s **)pxContext + 7), (char *)&g_ptQText);
      LoadingScreen_UpdateScreen((struct LoadingScreen_s *)pxContext);
      LoadingScreen_UpdateScreen((struct LoadingScreen_s *)pxContext);
      LoadingScreen_UpdateScreen((struct LoadingScreen_s *)pxContext);
    }
  }
  ptHead = (struct Mission_s *)Mission_tMissions.ptHead;
  ptNext = Mission_tMissions.ptHead->ptNext;
  v6 = Game_iMissionID;
  if ( Mission_tMissions.ptHead->ptNext )
  {
    while ( ptHead->iID != Game_iMissionID )
    {
      ptHead = (struct Mission_s *)ptNext;
      ptNext = ptNext->ptNext;
      if ( !ptNext )
        goto LABEL_19;
    }
  }
  else
  {
LABEL_19:
    ptHead = nullptr;
  }
  Game_ptGame->ptMission = ptHead;
  if ( !ptHead )
  {
    LDebug_Error("The mission ID %d does not exist.", v6);
    goto LABEL_22;
  }
  sprintf(igi2_frame.Buffer, "LOCAL:%s/", ptHead->zMissionDirectory);
  File_RegisterAlias("MISSION:", igi2_frame.Buffer);
  sprintf(igi2_frame.ArgList, "LOCAL:common/");
  v7 = 0;
  do
  {
    v8 = igi2_frame.ArgList[v7];
    MTP_zRootDir[v7++] = v8;
  }
  while ( v8 );
  v9 = Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER;
  v10 = Game_ptGame;
  Game_ptGame->eGameStatus = GAME_GAMESTATUS_INPROGRESS;
  if ( v9 )
  {
    Text_SetString(*((struct StaticTilemap_s **)pxContext + 7), "Initiating camera...");
    LoadingScreen_UpdateScreen((struct LoadingScreen_s *)pxContext);
    LoadingScreen_UpdateScreen((struct LoadingScreen_s *)pxContext);
    LoadingScreen_UpdateScreen((struct LoadingScreen_s *)pxContext);
    v10 = Game_ptGame;
  }
  v10->tQCamera.ptSetCameraQTask = nullptr;
  v10->tQCamera.nLastFrameNumber = -1082130432;
  LODWORD(v10->tQCamera.tPos.vX) = 0;
  HIDWORD(v10->tQCamera.tPos.vX) = 0;
  LODWORD(v10->tQCamera.tPos.vY) = 0;
  HIDWORD(v10->tQCamera.tPos.vY) = 0;
  LODWORD(v10->tQCamera.tPos.vZ) = 0;
  HIDWORD(v10->tQCamera.tPos.vZ) = 0;
  v10->tQCamera.tMatrix.tX.vX = 1.0;
  v10->tQCamera.tMatrix.tX.vY = 0.0;
  v10->tQCamera.tMatrix.tX.vZ = 0.0;
  v10->tQCamera.tMatrix.tY.vX = 0.0;
  v10->tQCamera.tMatrix.tY.vY = 1.0;
  v10->tQCamera.tMatrix.tY.vZ = 0.0;
  v10->tQCamera.tMatrix.tZ.vX = 0.0;
  v10->tQCamera.tMatrix.tZ.vY = 0.0;
  v10->tQCamera.tMatrix.tZ.vZ = 1.0;
  v10->tQCamera.tMatrix.nOps = 0;
  v10->tQCamera.vHeightFactor = 409.6000061035156;
  Config_SetGameToCurrentPerformanceLevel();
  if ( Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER )
  {
    Text_SetString(*((struct StaticTilemap_s **)pxContext + 7), "Initiating weapon handlers...");
    LoadingScreen_UpdateScreen((struct LoadingScreen_s *)pxContext);
    LoadingScreen_UpdateScreen((struct LoadingScreen_s *)pxContext);
    LoadingScreen_UpdateScreen((struct LoadingScreen_s *)pxContext);
  }
  Weapon_InitHandlers();
  if ( Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER )
  {
    Text_SetString(*((struct StaticTilemap_s **)pxContext + 7), (char *)&stru_6A5CC4.nPri);
    LoadingScreen_UpdateScreen((struct LoadingScreen_s *)pxContext);
    LoadingScreen_UpdateScreen((struct LoadingScreen_s *)pxContext);
    LoadingScreen_UpdateScreen((struct LoadingScreen_s *)pxContext);
  }
  v11 = World_New(3500);
  v12 = Game_ptGame;
  Game_ptGame->ptWorld = v11;
  v9 = Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER;
  v12->pxTexturesResource = nullptr;
  if ( v9 )
  {
    Text_SetString(*((struct StaticTilemap_s **)pxContext + 7), (char *)&stru_6A5CC4);
    LoadingScreen_UpdateScreen((struct LoadingScreen_s *)pxContext);
    LoadingScreen_UpdateScreen((struct LoadingScreen_s *)pxContext);
    LoadingScreen_UpdateScreen((struct LoadingScreen_s *)pxContext);
    v12 = Game_ptGame;
  }
  v13 = GameMaterial_atGameMaterial;
  aptQMaterial = v12->ptWorld->aptQMaterial;
  do
  {
    *aptQMaterial = &v13->tQMaterial;
    ++v13;
    ++aptQMaterial;
  }
  while ( (int)v13 < 7505672 );
  World_ptActiveWorld = v12->ptWorld;
  if ( Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER )
  {
    Text_SetString(*((struct StaticTilemap_s **)pxContext + 7), (char *)&stru_6A5C9C);
    LoadingScreen_UpdateScreen((struct LoadingScreen_s *)pxContext);
    LoadingScreen_UpdateScreen((struct LoadingScreen_s *)pxContext);
    LoadingScreen_UpdateScreen((struct LoadingScreen_s *)pxContext);
  }
  MTP_nLODVirModel = MTP_nLODVirModelInOpen;
  Game_MPRunNetwork((char *)MTP_nLODVirModelInOpen);
  if ( Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER )
  {
    Text_SetString(*((struct StaticTilemap_s **)pxContext + 7), (char *)&stru_6A5C64);
    LoadingScreen_UpdateScreen((struct LoadingScreen_s *)pxContext);
    LoadingScreen_UpdateScreen((struct LoadingScreen_s *)pxContext);
    LoadingScreen_UpdateScreen((struct LoadingScreen_s *)pxContext);
  }
  Game_ptGame->ptCommonMTP = MTP_Load("common");
  Game_MPRunNetwork(v15);
  if ( Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER )
  {
    Text_SetString(*((struct StaticTilemap_s **)pxContext + 7), (char *)&stru_6A5C2C);
    LoadingScreen_UpdateScreen((struct LoadingScreen_s *)pxContext);
    LoadingScreen_UpdateScreen((struct LoadingScreen_s *)pxContext);
    LoadingScreen_UpdateScreen((struct LoadingScreen_s *)pxContext);
  }
  Game_ptGame->ptNewMTP = MTP_Load(g_pzName_0);
  ++*((_DWORD *)pxContext + 1);
  LoadingScreen_UpdateScreen((struct LoadingScreen_s *)pxContext);
  Game_MPRunNetwork(v16);
  if ( Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER )
  {
    Text_SetString(*((struct StaticTilemap_s **)pxContext + 7), (char *)&stru_6A5BF4);
    LoadingScreen_UpdateScreen((struct LoadingScreen_s *)pxContext);
    LoadingScreen_UpdateScreen((struct LoadingScreen_s *)pxContext);
    LoadingScreen_UpdateScreen((struct LoadingScreen_s *)pxContext);
  }
  sprintf(igi2_frame.ArgList, "LOCAL:%s/", Game_ptGame->ptMission->zCommonModelsDirectory);
  v17 = 0;
  do
  {
    v18 = igi2_frame.ArgList[v17];
    MTP_zRootDir[v17++] = v18;
  }
  while ( v18 );
  Game_ptGame->ptLocationMTP = MTP_Load(Game_ptGame->ptMission->zCommonModelsResourceName);
  ++*((_DWORD *)pxContext + 1);
  LoadingScreen_UpdateScreen((struct LoadingScreen_s *)pxContext);
  Game_MPRunNetwork(v19);
  if ( Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER )
  {
    Text_SetString(*((struct StaticTilemap_s **)pxContext + 7), (char *)&stru_6A5BA4.vB);
    LoadingScreen_UpdateScreen((struct LoadingScreen_s *)pxContext);
    LoadingScreen_UpdateScreen((struct LoadingScreen_s *)pxContext);
    LoadingScreen_UpdateScreen((struct LoadingScreen_s *)pxContext);
  }
  sprintf(igi2_frame.ArgList, "LOCAL:%s/", Game_ptGame->ptMission->zMissionModelsDirectory);
  v20 = 0;
  do
  {
    v21 = igi2_frame.ArgList[v20];
    MTP_zRootDir[v20++] = v21;
  }
  while ( v21 );
  Level_ptMTP = MTP_Load(Game_ptGame->ptMission->zMissionModelsResourceName);
  ++*((_DWORD *)pxContext + 1);
  LoadingScreen_UpdateScreen((struct LoadingScreen_s *)pxContext);
  v23 = RenderMode_tActiveRenderMode.apfRenderModeMethod[MTP_eInitModelsRenderModeMethod];
  if ( v23 )
    v23(nullptr);
  if ( AppContext_tAppContext.isServer == false )
  {
    Game_MPRunNetwork(v22);
    if ( Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER )
    {
      Text_SetString(*((struct StaticTilemap_s **)pxContext + 7), (char *)&stru_6A5BA4);
      LoadingScreen_UpdateScreen((struct LoadingScreen_s *)pxContext);
      LoadingScreen_UpdateScreen((struct LoadingScreen_s *)pxContext);
      LoadingScreen_UpdateScreen((struct LoadingScreen_s *)pxContext);
    }
    File_DirList((char *)&stru_6A5B74.vB, SoundSys_ScanDirectoryDirListRegisterCallback, nullptr);
    LocalizedSoundDir = Game_GetLocalizedSoundDir((char *)&stru_6A5B74.vB);
    File_DirList(LocalizedSoundDir, SoundSys_ScanDirectoryDirListRegisterCallback, nullptr);
    Game_MPRunNetwork(v25);
    if ( Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER )
    {
      Text_SetString(*((struct StaticTilemap_s **)pxContext + 7), (char *)&stru_6A5B74);
      LoadingScreen_UpdateScreen((struct LoadingScreen_s *)pxContext);
      LoadingScreen_UpdateScreen((struct LoadingScreen_s *)pxContext);
      LoadingScreen_UpdateScreen((struct LoadingScreen_s *)pxContext);
    }
    sprintf(igi2_frame.ArgList, (char *const)&stru_6A5B48.vB, Game_ptGame->ptMission->zCommonModelsDirectory);
    File_DirList(igi2_frame.ArgList, SoundSys_ScanDirectoryDirListRegisterCallback, nullptr);
    v26 = Game_GetLocalizedSoundDir(igi2_frame.ArgList);
    File_DirList(v26, SoundSys_ScanDirectoryDirListRegisterCallback, nullptr);
    Game_MPRunNetwork(v27);
    if ( Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER )
    {
      Text_SetString(*((struct StaticTilemap_s **)pxContext + 7), (char *)&stru_6A5B48);
      LoadingScreen_UpdateScreen((struct LoadingScreen_s *)pxContext);
      LoadingScreen_UpdateScreen((struct LoadingScreen_s *)pxContext);
      LoadingScreen_UpdateScreen((struct LoadingScreen_s *)pxContext);
    }
    File_DirList((char *)&stru_6A5B20.vG, SoundSys_ScanDirectoryDirListRegisterCallback, nullptr);
    v28 = Game_GetLocalizedSoundDir((char *)&stru_6A5B20.vG);
    File_DirList(v28, SoundSys_ScanDirectoryDirListRegisterCallback, nullptr);
  }
  ++*((_DWORD *)pxContext + 1);
  LoadingScreen_UpdateScreen((struct LoadingScreen_s *)pxContext);
  Game_MPRunNetwork(v29);
  if ( Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER )
  {
    Text_SetString(*((struct StaticTilemap_s **)pxContext + 7), (char *)&stru_6A5B20);
    LoadingScreen_UpdateScreen((struct LoadingScreen_s *)pxContext);
    LoadingScreen_UpdateScreen((struct LoadingScreen_s *)pxContext);
    LoadingScreen_UpdateScreen((struct LoadingScreen_s *)pxContext);
  }
  if ( Resource_IsLoadedInternal("LOCAL:common/sprites/sprites.res", (struct Resource_s **)igi2_frame.zFilename) )
  {
    v31 = *(_DWORD *)igi2_frame.zFilename;
    *(_DWORD *)(*(_DWORD *)igi2_frame.zFilename + 44) = 1;
    v32 = *(struct Sample_s **)(v31 + 52);
  }
  else
  {
    Game_MPRunNetwork(v30);
    v33 = File_Load("LOCAL:common/sprites/sprites.res", (unsigned int *)igi2_frame.zFilename);
    if ( !v33 )
    {
      LDebug_Error("Failed to load resource: '%s'", "LOCAL:common/sprites/sprites.res");
      goto LABEL_22;
    }
    v32 = (struct Sample_s *)Resource_ParseFile(File_zLastSubstitutedPath, v33, *(unsigned int *)igi2_frame.zFilename);
  }
  Game_ptGame->tMusicRequest.ptSample = v32;
  GameFunctions_LoadGameSprites();
  ++*((_DWORD *)pxContext + 1);
  LoadingScreen_UpdateScreen((struct LoadingScreen_s *)pxContext);
  if ( AppContext_tAppContext.isServer == false )
  {
    Game_MPRunNetwork(v34);
    if ( Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER )
    {
      Text_SetString(*((struct StaticTilemap_s **)pxContext + 7), (char *)&stru_6A5AB4);
      LoadingScreen_UpdateScreen((struct LoadingScreen_s *)pxContext);
      LoadingScreen_UpdateScreen((struct LoadingScreen_s *)pxContext);
      LoadingScreen_UpdateScreen((struct LoadingScreen_s *)pxContext);
    }
    if ( Resource_IsLoadedInternal("LOCAL:common/textures/textures.res", (struct Resource_s **)igi2_frame.zFilename) )
    {
      v36 = *(_DWORD *)igi2_frame.zFilename;
      *(_DWORD *)(*(_DWORD *)igi2_frame.zFilename + 44) = 1;
      v37 = *(void **)(v36 + 52);
    }
    else
    {
      Game_MPRunNetwork(v35);
      v38 = File_Load("LOCAL:common/textures/textures.res", (unsigned int *)igi2_frame.zFilename);
      if ( !v38 )
      {
        LDebug_Error("Failed to load resource: '%s'", "LOCAL:common/textures/textures.res");
        goto LABEL_22;
      }
      v37 = Resource_ParseFile(File_zLastSubstitutedPath, v38, *(unsigned int *)igi2_frame.zFilename);
    }
    v39 = Game_ptGame;
    Game_ptGame->tMusicRequest.nSoundID = (unsigned int)v37;
    Game_MPRunNetwork((char *)v39);
    if ( Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER )
    {
      Text_SetString(*((struct StaticTilemap_s **)pxContext + 7), (char *)&stru_6A5A54.nPri);
      LoadingScreen_UpdateScreen((struct LoadingScreen_s *)pxContext);
      LoadingScreen_UpdateScreen((struct LoadingScreen_s *)pxContext);
      LoadingScreen_UpdateScreen((struct LoadingScreen_s *)pxContext);
    }
    Direct3DRender_LoadEffectTextures();
    Game_MPRunNetwork(v40);
    if ( Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER )
    {
      Text_SetString(*((struct StaticTilemap_s **)pxContext + 7), (char *)&stru_6A5A54);
      LoadingScreen_UpdateScreen((struct LoadingScreen_s *)pxContext);
      LoadingScreen_UpdateScreen((struct LoadingScreen_s *)pxContext);
      LoadingScreen_UpdateScreen((struct LoadingScreen_s *)pxContext);
    }
    LensflareItemQTask_InitResources("LOCAL:common/textures/lens0");
    Game_MPRunNetwork(v41);
    if ( Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER )
    {
      Text_SetString(*((struct StaticTilemap_s **)pxContext + 7), "Loading game textures...");
      LoadingScreen_UpdateScreen((struct LoadingScreen_s *)pxContext);
      LoadingScreen_UpdateScreen((struct LoadingScreen_s *)pxContext);
      LoadingScreen_UpdateScreen((struct LoadingScreen_s *)pxContext);
    }
    GameFunctions_LoadGameTextures();
    ++*((_DWORD *)pxContext + 1);
    LoadingScreen_UpdateScreen((struct LoadingScreen_s *)pxContext);
  }
  Game_MPRunNetwork(v34);
  if ( Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER )
  {
    Text_SetString(*((struct StaticTilemap_s **)pxContext + 7), "Loading fonts...");
    LoadingScreen_UpdateScreen((struct LoadingScreen_s *)pxContext);
    LoadingScreen_UpdateScreen((struct LoadingScreen_s *)pxContext);
    LoadingScreen_UpdateScreen((struct LoadingScreen_s *)pxContext);
  }
  Game_LoadFontResource(nullptr);
  Game_MPRunNetwork(v42);
  if ( Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER )
  {
    Text_SetString(*((struct StaticTilemap_s **)pxContext + 7), "Loading computer menu resource...");
    LoadingScreen_UpdateScreen((struct LoadingScreen_s *)pxContext);
    LoadingScreen_UpdateScreen((struct LoadingScreen_s *)pxContext);
    LoadingScreen_UpdateScreen((struct LoadingScreen_s *)pxContext);
  }
  ComputerMenu_LoadComputerMenuResource();
  ++*((_DWORD *)pxContext + 1);
  LoadingScreen_UpdateScreen((struct LoadingScreen_s *)pxContext);
  ++*((_DWORD *)pxContext + 1);
  LoadingScreen_UpdateScreen((struct LoadingScreen_s *)pxContext);
  Game_MPRunNetwork(v43);
  if ( Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER )
  {
    Text_SetString(*((struct StaticTilemap_s **)pxContext + 7), "Starting game screen task...");
    LoadingScreen_UpdateScreen((struct LoadingScreen_s *)pxContext);
    LoadingScreen_UpdateScreen((struct LoadingScreen_s *)pxContext);
    LoadingScreen_UpdateScreen((struct LoadingScreen_s *)pxContext);
  }
  v44 = QTask_NewFn(Flow_ptFlow->ptScreenQTask, GameScreen_eQTaskType, nullptr);
  v45 = Game_ptGame;
  Game_ptGame->ptGameScreenQTask = v44;
  Game_MPRunNetwork((char *)v45);
  if ( Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER )
  {
    Text_SetString(*((struct StaticTilemap_s **)pxContext + 7), "Starting level task...");
    LoadingScreen_UpdateScreen((struct LoadingScreen_s *)pxContext);
    LoadingScreen_UpdateScreen((struct LoadingScreen_s *)pxContext);
    LoadingScreen_UpdateScreen((struct LoadingScreen_s *)pxContext);
  }
  Game_ptGame->ptLevelQTask = QTask_NewFn(ptQTask, Level_eLevelQTaskType, nullptr);
  WeaponType_MakeWeaponTypeAnimTables();
  ++*((_DWORD *)pxContext + 1);
  LoadingScreen_UpdateScreen((struct LoadingScreen_s *)pxContext);
  if ( AppContext_tAppContext.isServer == false )
  {
    Game_MPRunNetwork(v46);
    if ( Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER )
    {
      Text_SetString(*((struct StaticTilemap_s **)pxContext + 7), (char *)&stru_6A5974.vB);
      LoadingScreen_UpdateScreen((struct LoadingScreen_s *)pxContext);
      LoadingScreen_UpdateScreen((struct LoadingScreen_s *)pxContext);
      LoadingScreen_UpdateScreen((struct LoadingScreen_s *)pxContext);
    }
    SoundSys_isEditorEnabled = 0;
    Game_MPRunNetwork(v47);
    if ( Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER )
    {
      Text_SetString(*((struct StaticTilemap_s **)pxContext + 7), (char *)&stru_6A5974);
      LoadingScreen_UpdateScreen((struct LoadingScreen_s *)pxContext);
      LoadingScreen_UpdateScreen((struct LoadingScreen_s *)pxContext);
      LoadingScreen_UpdateScreen((struct LoadingScreen_s *)pxContext);
    }
    SoundSys_NewSoundDefParentQTask(ptQTask, "LOCAL:common/sounds/");
    sprintf(igi2_frame.ArgList, (char *const)&stru_6A5B48.vB, Game_ptGame->ptMission->zCommonModelsDirectory);
    Game_MPRunNetwork(v48);
    if ( Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER )
    {
      Text_SetString(*((struct StaticTilemap_s **)pxContext + 7), (char *)&stru_6A5910);
      LoadingScreen_UpdateScreen((struct LoadingScreen_s *)pxContext);
      LoadingScreen_UpdateScreen((struct LoadingScreen_s *)pxContext);
      LoadingScreen_UpdateScreen((struct LoadingScreen_s *)pxContext);
    }
    SoundSys_NewSoundDefParentQTask(ptQTask, igi2_frame.ArgList);
    Game_MPRunNetwork(v49);
    if ( Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER )
    {
      Text_SetString(*((struct StaticTilemap_s **)pxContext + 7), (char *)&stru_6A58AC.nPri);
      LoadingScreen_UpdateScreen((struct LoadingScreen_s *)pxContext);
      LoadingScreen_UpdateScreen((struct LoadingScreen_s *)pxContext);
      LoadingScreen_UpdateScreen((struct LoadingScreen_s *)pxContext);
    }
    SoundSys_NewSoundDefParentQTask(ptQTask, (char *)&stru_6A58AC.vA);
  }
  if ( Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER )
  {
    Text_SetString(*((struct StaticTilemap_s **)pxContext + 7), (char *)&stru_6A58AC);
    LoadingScreen_UpdateScreen((struct LoadingScreen_s *)pxContext);
    LoadingScreen_UpdateScreen((struct LoadingScreen_s *)pxContext);
    LoadingScreen_UpdateScreen((struct LoadingScreen_s *)pxContext);
  }
  LightmapInfo_LoadResource();
  if ( Resource_IsLoadedInternal("MISSION:heightmaps/heightmaps.res", nullptr)
    || File_Exists("MISSION:heightmaps/heightmaps.res") )
  {
    if ( Resource_IsLoadedInternal("MISSION:heightmaps/heightmaps.res", (struct Resource_s **)igi2_frame.zFilename) )
    {
      *(_DWORD *)(*(_DWORD *)igi2_frame.zFilename + 44) = 1;
      goto LABEL_108;
    }
    Game_MPRunNetwork(v50);
    v51 = File_Load("MISSION:heightmaps/heightmaps.res", (unsigned int *)igi2_frame.zFilename);
    if ( !v51 )
    {
      LDebug_Error("Failed to load resource: '%s'", "MISSION:heightmaps/heightmaps.res");
LABEL_22:
      abort();
    }
    Resource_ParseFile(File_zLastSubstitutedPath, v51, *(unsigned int *)igi2_frame.zFilename);
  }
LABEL_108:
  v52 = Game_ptGame;
  v53 = INPUTPORT_DEVICE_NONE;
  Game_ptGame->ptQEditorQTask = nullptr;
  AnimController_nTicksPerFrame = 160;
  if ( Keyboard_tKeyboard.isConnected )
  {
    if ( Mouse_tMouse.isConnected )
      v53 = INPUTPORT_DEVICE_MOUSE;
    InputPort_Init(
      INPUTPORT_0,
      Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tInputOptions.nRemapButton,
      Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tInputOptions.atRemapButtonTable,
      v53,
      0.10000000149011612,
      0.036666665226221085,
      0.036666665226221085,
      0.10000000149011612,
      0.036666665226221085,
      0.036666665226221085,
      0.10000000149011612,
      0.036666665226221085,
      0.036666665226221085,
      0.10000000149011612,
      0.036666665226221085,
      0.036666665226221085);
    InputPort_atInputPort[0].isActive = true;
  }
  EnvironmentSound_ptCamera = &v52->tQCamera;
  Game_MPRunNetwork((char *)v53);
  if ( Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER )
  {
    Text_SetString(*((struct StaticTilemap_s **)pxContext + 7), "Updating LOD settings...");
    LoadingScreen_UpdateScreen((struct LoadingScreen_s *)pxContext);
    LoadingScreen_UpdateScreen((struct LoadingScreen_s *)pxContext);
    LoadingScreen_UpdateScreen((struct LoadingScreen_s *)pxContext);
  }
  if ( ModelLODSettingsContainer_ptQTask )
    QTask_TriggerQTaskEventRecursively(
      &ModelLODSettingsContainer_ptQTask->tQTask,
      ParameterList_eUpdateInternalDataQTaskEvent,
      nullptr);
  if ( LocalModelLODSettingsContainer_ptQTask )
    QTask_TriggerQTaskEventRecursively(
      &LocalModelLODSettingsContainer_ptQTask->tQTask,
      ParameterList_eUpdateInternalDataQTaskEvent,
      nullptr);
  ptPrev = (struct QViewportQTask_s *)Game_ptGame->ptGameScreenQTask[1].ptPrev;
  CutScene_ptDefaultQCamera = &Game_ptGame->tQCamera;
  CutScene_nFrequency = 30;
  CutScene_ptQViewportQTask = ptPrev;
  HumanSoldier_InitDamagePartTable();
  Game_MPRunNetwork(v55);
  if ( Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER )
  {
    Text_SetString(*((struct StaticTilemap_s **)pxContext + 7), "Loading objects...");
    LoadingScreen_UpdateScreen((struct LoadingScreen_s *)pxContext);
    LoadingScreen_UpdateScreen((struct LoadingScreen_s *)pxContext);
    LoadingScreen_UpdateScreen((struct LoadingScreen_s *)pxContext);
  }
  Level_LoadObjects(igi2_frame.Buffer, 30);
  Game_MPRunNetwork(v56);
  if ( Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER )
  {
    Text_SetString(*((struct StaticTilemap_s **)pxContext + 7), (char *)&stru_6A5810.vR);
    LoadingScreen_UpdateScreen((struct LoadingScreen_s *)pxContext);
    LoadingScreen_UpdateScreen((struct LoadingScreen_s *)pxContext);
    LoadingScreen_UpdateScreen((struct LoadingScreen_s *)pxContext);
  }
  Game_LoadCarryOver(Game_iMissionID);
  QTask_TriggerQTaskEventRecursivelyNoContext(ptQTask, Human_eUpdateInternalDataAfterCarryoverQTaskEvent);
  ++*((_DWORD *)pxContext + 1);
  LoadingScreen_UpdateScreen((struct LoadingScreen_s *)pxContext);
  if ( AppContext_tAppContext.isServer == false )
  {
    Game_MPRunNetwork(v57);
    if ( Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER )
    {
      Text_SetString(*((struct StaticTilemap_s **)pxContext + 7), (char *)&stru_6A5810);
      LoadingScreen_UpdateScreen((struct LoadingScreen_s *)pxContext);
      LoadingScreen_UpdateScreen((struct LoadingScreen_s *)pxContext);
      LoadingScreen_UpdateScreen((struct LoadingScreen_s *)pxContext);
    }
    v58 = Sound_ptSampleHashTable;
    *(&Game_ptGame->tMusicRequest.bFlags + 1) = 0;
    v59 = v58;
    v60 = v58->tPrivate.pfHashFunction(v58->tPrivate.nHashTableSize, &unk_6A5804);
    v61 = ((int  (__cdecl *)(struct QHashTable_s *, unsigned int, const void *))Sound_ptSampleHashTable->tPrivate.pfFindElement)(v59, v60, (const void *)(&unk_6A5804));
    v62 = Game_ptGame;
    Game_ptGame->tMusicRequest.bFlags = v61;
    LODWORD(v62->tMusicRequest.tModify.tAttr.vVolume) = 48;
    Sound_DefaultSoundModify((struct SoundModify_t *)&v62->tMusicRequest.tModify.tAttr.vPan);
  }
  Game_MPRunNetwork(v57);
  if ( Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER )
  {
    Text_SetString(*((struct StaticTilemap_s **)pxContext + 7), "Loading debugconsole task...");
    LoadingScreen_UpdateScreen((struct LoadingScreen_s *)pxContext);
    LoadingScreen_UpdateScreen((struct LoadingScreen_s *)pxContext);
    LoadingScreen_UpdateScreen((struct LoadingScreen_s *)pxContext);
  }
  DebugConsoleTask_LoadQTask(Flow_ptFlow->ptScreenQTask);
  v63 = Game_ptMissionScoreScreenQTaskRef;
  if ( Game_ptMissionScoreScreenQTaskRef )
  {
    if ( Game_ptMissionScoreScreenQTaskRef->pxObject )
    {
      QTask_Delete((struct QTask_s *)Game_ptMissionScoreScreenQTaskRef->pxObject);
      v63 = Game_ptMissionScoreScreenQTaskRef;
    }
    if ( v63 )
    {
      QReference_Delete(v63, &QTask_tQTaskRefPool);
      Game_ptMissionScoreScreenQTaskRef = nullptr;
    }
  }
  if ( Game_nMenuLoadFromSlot >= 0 )
  {
    if ( Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER )
    {
      Text_SetString(*((struct StaticTilemap_s **)pxContext + 7), "Loading savegame...");
      LoadingScreen_UpdateScreen((struct LoadingScreen_s *)pxContext);
      LoadingScreen_UpdateScreen((struct LoadingScreen_s *)pxContext);
      LoadingScreen_UpdateScreen((struct LoadingScreen_s *)pxContext);
    }
    Game_LoadFromSlot(Game_nMenuLoadFromSlot);
    Game_nMenuLoadFromSlot = -1;
  }
  if ( Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER )
  {
    Text_SetString(*((struct StaticTilemap_s **)pxContext + 7), (char *)&stru_6A5798.vB);
    LoadingScreen_UpdateScreen((struct LoadingScreen_s *)pxContext);
    LoadingScreen_UpdateScreen((struct LoadingScreen_s *)pxContext);
    LoadingScreen_UpdateScreen((struct LoadingScreen_s *)pxContext);
  }
  Game_UnloadFontResource();
  if ( Game_eGameMode == GAME_GAMEMODE_SINGLEPLAYER )
  {
    if ( Level_atLevelQTaskID[0] )
    {
      pxObject = (char *)Level_atLevelQTaskID[0]->pxObject;
      if ( pxObject )
      {
        if ( QTask_IsQTaskTypeDerived(*((_WORD *)pxObject + 18), Human_eQTaskType) )
          MissionScoreSettings_UpdateMissionStats((struct HumanMissionScoreData_s *)(pxObject + 472));
      }
    }
  }
  Flow_ResumeTiming();
  if ( Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER )
  {
    Text_SetString(*((struct StaticTilemap_s **)pxContext + 7), (char *)&stru_6A5798);
    LoadingScreen_UpdateScreen((struct LoadingScreen_s *)pxContext);
    LoadingScreen_UpdateScreen((struct LoadingScreen_s *)pxContext);
    LoadingScreen_UpdateScreen((struct LoadingScreen_s *)pxContext);
  }
}

// source: j/0/game.c:1380  [anchor-caller]
void __cdecl Game_MPChangeMap(struct QTask_s *ptQTask)
{
  DWORD PerformanceCounter; // eax
  char *v2; // ecx
  struct LoadingScreen_s *v3; // edi
  struct StaticTilemap_s *ptStateText; // ecx
  char *v5; // ecx
  char *v6; // ecx

  if ( Timer_isPerformanceCounter )
    PerformanceCounter = Timer_GetPerformanceCounter();
  else
    PerformanceCounter = GetTickCount();
  Game_ptGame[1].tQTask.ptNext = (struct QTask_s *)(PerformanceCounter - Timer_nStartTime);
  NetManager_LogMessage("GAME_MPCHANGEMAP\n");
  Game_MPRunNetwork(v2);
  v3 = (struct LoadingScreen_s *)LoadingScreen_New(1, Game_iMissionID, true);
  v3->ptStateText->vR = 128.0;
  v3->ptStateText->vG = 128.0;
  ptStateText = v3->ptStateText;
  ptStateText->vB = 128.0;
  Game_MPRunNetwork((char *)ptStateText);
  if ( Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER )
  {
    Text_SetString(v3->ptStateText, "Saving config...");
    LoadingScreen_UpdateScreen(v3);
    LoadingScreen_UpdateScreen(v3);
    LoadingScreen_UpdateScreen(v3);
  }
  Config_Save("LOCAL:config.qsc");
  Game_MPRunNetwork(v5);
  if ( Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER )
  {
    Text_SetString(v3->ptStateText, "Saving network config...");
    LoadingScreen_UpdateScreen(v3);
    LoadingScreen_UpdateScreen(v3);
    LoadingScreen_UpdateScreen(v3);
  }
  NetworkConfig_Save("networkconfig.cfg");
  Flow_ptFlow->eRequestedEvent = 4;
  Game_MPRunNetwork(v6);
  if ( Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER )
  {
    Text_SetString(v3->ptStateText, "Deleting game...");
    LoadingScreen_UpdateScreen(v3);
    LoadingScreen_UpdateScreen(v3);
    LoadingScreen_UpdateScreen(v3);
  }
  QTask_Delete(ptQTask);
  LoadingScreen_Delete(v3);
}

// source: j/0/game.c:1431  [anchor-caller]
void __cdecl Game_RunHandler(struct QTask_s *ptQTask)
{
  enum GameMode_e v1; // eax
  struct Game_s *v2; // ecx
  struct QTask_s *ptNetManagerQTask; // eax
  int v4; // ecx
  char *pxObject; // eax
  struct Node_s *ptHead; // eax
  bool v7; // zf
  void *v8; // esi
  struct QTask_s *v9; // ecx
  int v10; // edx
  struct QTask_s *v11; // eax
  void (__cdecl *pfHandler)(struct QTask_s *); // eax
  int v13; // edx
  int v14; // [esp-8h] [ebp-18h]

  v1 = Game_eGameMode;
  v2 = Game_ptGame;
  if ( Game_eGameMode == GAME_GAMEMODE_SINGLEPLAYER
    && (Keyboard_tKeyboard.anCurrentKey[88] & 0x80u) != 0
    && (Keyboard_tKeyboard.anPreviousKey[88] & 0x80) == 0
    && (Keyboard_tKeyboard.anCurrentKey[29] & 0x80) != 0
    && (Keyboard_tKeyboard.anCurrentKey[42] & 0x80) != 0 )
  {
    Game_ptGame->eGameStatus = GAME_GAMESTATUS_COMPLETED;
    v2[1].tQTask.ptPrev = (struct QTask_s *)1;
  }
  if ( v2->eGameStatus == GAME_GAMESTATUS_COMPLETED )
  {
    if ( v1 == GAME_GAMEMODE_MULTIPLAYER )
    {
      ptNetManagerQTask = Flow_ptFlow->ptNetManagerQTask;
      v4 = (int)&ptNetManagerQTask[32].tQTaskChildren.ptTail->ptNext + 1;
      ptNetManagerQTask[32].tQTaskChildren.ptTail = (struct QTask_s *)v4;
      *((_DWORD *)&ptNetManagerQTask[31].tQTaskChildren.ptTail + v4) = 1;
      Game_SaveCarryoverMP(Game_iMissionID);
      Game_MPChangeMap(ptQTask);
      --Flow_ptFlow->ptNetManagerQTask[32].tQTaskChildren.ptTail;
    }
    else
    {
      if ( Level_atLevelQTaskID[0] )
        pxObject = (char *)Level_atLevelQTaskID[0]->pxObject;
      else
        pxObject = nullptr;
      if ( v2[1].tQTask.ptPrev )
        v2[1].tQTask.ptPrev = nullptr;
      else
        MissionScoreSettings_UpdateMissionStats((struct HumanMissionScoreData_s *)(pxObject + 472));
      if ( !Mission_tMissionList.ptHead->ptNext )
        goto LABEL_17;
      ptHead = Mission_tMissionList.ptHead;
      if ( !Mission_tMissionList.ptHead )
        goto LABEL_17;
      while ( 1 )
      {
        v7 = ptHead[1].ptNext == (struct Node_s *)Game_iMissionID;
        ptHead = ptHead->ptNext;
        if ( v7 )
          break;
        if ( !ptHead->ptNext || !ptHead )
          goto LABEL_17;
      }
      if ( ptHead->ptNext && ptHead )
      {
        Game_iMissionID = (int)ptHead[1].ptNext;
        Config_UpdateActiveMissionID(Game_iMissionID);
        Config_Save("LOCAL:config.qsc");
        Game_SaveCarryover(Game_iMissionID);
        v14 = Game_iMissionID;
        Flow_ptFlow->eRequestedEvent = 4;
        v8 = LoadingScreen_New(1, v14, true);
        QTask_Delete(ptQTask);
        LoadingScreen_Delete(v8);
      }
      else
      {
LABEL_17:
        Flow_ptFlow->eRequestedEvent = 8;
        QTask_Delete(ptQTask);
      }
    }
  }
  else
  {
    if ( !LOBYTE(ptQTask[6].tQTaskRefList.ptMiddle) )
    {
      v9 = ptQTask->tQTaskChildren.ptHead;
      if ( v9->ptNext )
      {
        if ( v9 )
        {
          v10 = QTask_nProtectedQTaskStackOffset;
          do
          {
            if ( v9->ptNext )
              v11 = v9->ptNext->ptNext != nullptr ? v9->ptNext : nullptr;
            else
              v11 = nullptr;
            QTask_atProtectedQTaskStack[v10].ptQTask = v11;
            pfHandler = (void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[1][v9->eQTaskType].pfHandler;
            v13 = v10 + 1;
            QTask_nProtectedQTaskStackOffset = v13;
            if ( pfHandler )
            {
              pfHandler(v9);
              v13 = QTask_nProtectedQTaskStackOffset;
            }
            v9 = (struct QTask_s *)dword_849C7DC[v13];
            v10 = v13 - 1;
            QTask_nProtectedQTaskStackOffset = v10;
          }
          while ( v9 );
        }
      }
    }
    if ( Game_isMusicEnabled )
      SoundSys_RequestSoundFn((struct SoundSysRequest_s *)&ptQTask[7]);
    else
      ptQTask[7].ptPrev = nullptr;
  }
}

// source: j/0/game.c:1580  [anchor-caller]
void __cdecl Game_DeleteHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { char zFilename[4]; };
    struct { char igi2_o1[4]; char zDirectory[256]; };
    char igi2_extent[260];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *v1; // ecx
  DWORD PerformanceCounter; // eax
  struct Flow_t *v3; // edx
  struct QTask_s *ptNetManagerQTask; // eax
  char *pxObject; // ecx
  struct QReference_s *v6; // eax
  char *v7; // ecx
  char *v8; // ecx
  int v9; // eax
  char *v10; // ecx
  char *v11; // ecx
  char *v12; // ecx
  struct Resource_s *ptHead; // ecx
  struct Resource_s *ptNext; // eax
  unsigned int nType; // eax
  char *v16; // ecx
  char *v17; // ecx
  struct Resource_s *v18; // ecx
  struct Resource_s *v19; // eax
  unsigned int v20; // eax
  char *v21; // ecx
  void (__cdecl *v22)(void *); // eax
  char *v23; // ecx
  char *LocalizedSoundDir; // eax
  char *v25; // ecx
  char *v26; // eax
  char *v27; // ecx
  char *v28; // eax
  char *v29; // ecx
  char *v30; // ecx
  char *v31; // ecx
  char *v32; // ecx

  if ( Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER )
  {
    if ( Timer_isPerformanceCounter )
      PerformanceCounter = Timer_GetPerformanceCounter();
    else
      PerformanceCounter = GetTickCount();
    v3 = Flow_ptFlow;
    Game_ptGame[1].tQTask.ptNext = (struct QTask_s *)(PerformanceCounter - Timer_nStartTime);
    ptNetManagerQTask = v3->ptNetManagerQTask;
    v1 = (struct QTask_s *)((char *)&ptNetManagerQTask[32].tQTaskChildren.ptTail->ptNext + 1);
    ptNetManagerQTask[32].tQTaskChildren.ptTail = v1;
    *((_DWORD *)&ptNetManagerQTask[31].tQTaskChildren.ptTail + (_DWORD)v1) = 1;
  }
  Game_MPRunNetwork((char *)v1);
  v6 = DebugConsoleTask_ptQTaskRef;
  if ( DebugConsoleTask_ptQTaskRef )
  {
    pxObject = (char *)DebugConsoleTask_ptQTaskRef->pxObject;
    if ( pxObject )
    {
      QTask_Delete((struct QTask_s *)DebugConsoleTask_ptQTaskRef->pxObject);
      v6 = DebugConsoleTask_ptQTaskRef;
    }
    if ( v6 )
    {
      QReference_Delete(v6, &QTask_tQTaskRefPool);
      DebugConsoleTask_ptQTaskRef = nullptr;
    }
  }
  Game_MPRunNetwork(pxObject);
  SoundSys_ClearPlayList();
  Game_MPRunNetwork(v7);
  if ( Level_ptQLevelQTask )
    QTask_DeleteChildren(&Level_ptQLevelQTask->tQTask);
  memset(Level_aisLevelQTaskAllocated, 0, sizeof(Level_aisLevelQTaskAllocated));
  if ( Game_ptGame->ptQEditorQTask )
    QTask_Delete(Game_ptGame->ptQEditorQTask);
  if ( Resource_IsLoadedInternal("MISSION:heightmaps/heightmaps.res", (struct Resource_s **)igi2_frame.zFilename) )
  {
    v8 = *(char **)igi2_frame.zFilename;
    v9 = *(_DWORD *)(*(_DWORD *)igi2_frame.zFilename + 36);
    if ( v9 != 3 && v9 != 1 )
      Resource_Remove(*(struct Resource_s **)igi2_frame.zFilename);
  }
  Game_MPRunNetwork(v8);
  LightmapInfo_FreeResource();
  Game_MPRunNetwork(v10);
  QTask_Delete(Game_ptGame->ptGameScreenQTask);
  Game_MPRunNetwork(v11);
  LensflareItemQTask_DeinitResources();
  Game_MPRunNetwork(v12);
  GameFunctions_FreeGameSprites();
  ptHead = Resource_tResourceList.ptHead;
  ptNext = Resource_tResourceList.ptHead->ptNext;
  if ( Resource_tResourceList.ptHead->ptNext )
  {
    while ( ptHead->pxData != Game_ptGame->tMusicRequest.ptSample )
    {
      ptHead = ptNext;
      ptNext = ptNext->ptNext;
      if ( !ptNext )
        goto LABEL_26;
    }
    nType = ptHead->nType;
    if ( nType != 3 && nType != 1 )
      Resource_Remove(ptHead);
  }
LABEL_26:
  Game_MPRunNetwork((char *)ptHead);
  Direct3DRender_FreeEffectTextures();
  Game_MPRunNetwork(v16);
  GameFunctions_FreeGameTextures();
  Game_MPRunNetwork(v17);
  v18 = Resource_tResourceList.ptHead;
  v19 = Resource_tResourceList.ptHead->ptNext;
  if ( Resource_tResourceList.ptHead->ptNext )
  {
    while ( v18->pxData != (void *)Game_ptGame->tMusicRequest.nSoundID )
    {
      v18 = v19;
      v19 = v19->ptNext;
      if ( !v19 )
        goto LABEL_33;
    }
    v20 = v18->nType;
    if ( v20 != 3 && v20 != 1 )
      Resource_Remove(v18);
  }
LABEL_33:
  Game_MPRunNetwork((char *)v18);
  ComputerMenu_FreeComputerMenuResource();
  StatusMessageScreen_FreeResource();
  v22 = RenderMode_tActiveRenderMode.apfRenderModeMethod[MTP_eDeinitModelsRenderModeMethod];
  if ( v22 )
    v22(nullptr);
  Game_MPRunNetwork(v21);
  MTP_Free(Level_ptMTP);
  Game_MPRunNetwork(v23);
  File_DirList((char *)&stru_6A5B20.vG, SoundSys_ScanDirectoryDirListRemoveCallback, nullptr);
  LocalizedSoundDir = Game_GetLocalizedSoundDir((char *)&stru_6A5B20.vG);
  File_DirList(LocalizedSoundDir, SoundSys_ScanDirectoryDirListRemoveCallback, nullptr);
  Game_MPRunNetwork(v25);
  sprintf(igi2_frame.zDirectory, (char *const)&stru_6A5B48.vB, Game_ptGame->ptMission->zCommonModelsDirectory, unk_6A5564);
  File_DirList(igi2_frame.zDirectory, SoundSys_ScanDirectoryDirListRemoveCallback, nullptr);
  v26 = Game_GetLocalizedSoundDir(igi2_frame.zDirectory);
  File_DirList(v26, SoundSys_ScanDirectoryDirListRemoveCallback, nullptr);
  Game_MPRunNetwork(v27);
  File_DirList((char *)&stru_6A5B74.vB, SoundSys_ScanDirectoryDirListRemoveCallback, nullptr);
  v28 = Game_GetLocalizedSoundDir((char *)&stru_6A5B74.vB);
  File_DirList(v28, SoundSys_ScanDirectoryDirListRemoveCallback, nullptr);
  Game_MPRunNetwork(v29);
  MTP_Free(Game_ptGame->ptLocationMTP);
  Game_MPRunNetwork(v30);
  MTP_Free(Game_ptGame->ptNewMTP);
  Game_MPRunNetwork(v31);
  MTP_Free(Game_ptGame->ptCommonMTP);
  Game_MPRunNetwork(v32);
  World_Delete(Game_ptGame->ptWorld);
  File_RemoveAlias("MISSION:");
  Game_ptGame = nullptr;
  if ( Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER )
    --Flow_ptFlow->ptNetManagerQTask[32].tQTaskChildren.ptTail;
}

// source: j/0/game.c:1723  [size]
unsigned __int16 __cdecl Game_GetQTaskType()
{
  return Game_eQTaskType;
}

// source: j/0/game.c:1737  [anchor-hash]
struct Game_s *__cdecl Game_New(struct QTask_s *ptParent, void *pxContext)
{
  QTask_NewFn(ptParent, Game_eQTaskType, pxContext);
  return Game_ptGame;
}

// source: j/0/game.c:1753  [size]
struct World_s *__cdecl Game_GetWorld()
{
  return Game_ptGame->ptWorld;
}

// source: j/0/game.c:1766  [anchor-callee]
struct QTask_s *__cdecl Game_GetPlayerQTask(int iPlayer)
{
  struct QReference_s *v1; // ecx
  struct QTask_s *result; // eax

  v1 = Game_ptGame->aptPlayerQTaskRef[iPlayer + 2];
  result = nullptr;
  if ( v1 )
    return (struct QTask_s *)v1->pxObject;
  return result;
}

// source: j/0/game.c:1790  [size]
struct RandomState_s *__cdecl Game_GetRandomState()
{
  return &Game_ptGame->tRunRandomState;
}

// source: j/0/game.c:1806  [anchor-hash]
struct RandomState_s *__cdecl Game_GetDrawRandomState()
{
  return &Game_ptGame->tDrawRandomState;
}

// source: j/0/game.c:1822  [size]
struct Game_s *__cdecl Game_GetGame()
{
  return Game_ptGame;
}

// source: j/0/game.c:1837  [size]
enum bool __cdecl Game_IsGame()
{
  return Game_ptGame != nullptr;
}

// source: j/0/game.c:1850  [size]
enum GameMode_e __cdecl Game_GetGameMode()
{
  return Game_eGameMode;
}

// source: j/0/game.c:1863  [size]
int __cdecl Game_SetGameMission(int idMission)
{
  Game_iMissionID = idMission;
  return idMission;
}

// source: j/0/game.c:1876  [size]
int __cdecl Game_GetGameMission()
{
  return Game_iMissionID;
}

// source: j/0/game.c:1889  [size]
void __cdecl Game_SetGameStatus(enum GameStatus_e eGameStatus)
{
  Game_ptGame->eGameStatus = eGameStatus;
}

// source: j/0/game.c:1904  [size]
enum GameStatus_e __cdecl Game_GetGameStatus()
{
  return Game_ptGame->eGameStatus;
}

// source: j/0/game.c:1919  [anchor-callee]
enum bool __cdecl Game_IsPaused()
{
  if ( Game_ptGame )
    return SLOBYTE(Game_ptGame->pxSpritesResource);
  else
    return false;
}

// source: j/0/game.c:1936  [anchor-callee]
void __cdecl Game_SetPaused(enum bool isPaused)
{
  if ( Game_eGameMode != GAME_GAMEMODE_MULTIPLAYER )
    LOBYTE(Game_ptGame->pxSpritesResource) = isPaused;
}

// source: j/0/game.c:1956  [size]
enum bool __cdecl Game_PlayerInvincible()
{
  return false;
}

// source: j/0/game.c:1969  [anchor-caller]
void __cdecl Game_RefreshAfterLevelLoad()
{
  struct Game_s *v0; // eax
  struct MemPoolFreeItem_s **v1; // esi
  struct QReference_s **v2; // edx
  struct QTask_s *v3; // edi
  struct MemPoolFreeItem_s *v4; // eax
  struct QReference_s *v5; // eax
  struct Game_s *v6; // edi
  struct QTask_s *v7; // eax
  struct Flow_t *v8; // ecx
  struct QTask_s *v9; // esi
  struct LevelFlow_s *v10; // eax
  struct QReference_s *v11; // eax
  struct Game_s *v12; // edi
  struct QTask_s *pxObject; // eax
  struct QTask_s *ptPrev; // esi
  struct QTask_s *ptHead; // ebp
  struct QTask_s *v16; // eax
  float nFrameNumber; // [esp+0h] [ebp-18h]
  struct QTask_s *ptPlayerQTask; // [esp+14h] [ebp-4h]
  struct QTask_s *ptPlayerQTaska; // [esp+14h] [ebp-4h]

  MTP_GetLODVirModelExistsFn("none")->nLOD = 0;
  v0 = Game_ptGame;
  Game_ptGame->tRunRandomState.anRandom[0] = -923067897;
  v0->tRunRandomState.anRandom[1] = 971667286;
  v0->tRunRandomState.anRandom[2] = 2146516173;
  v0->tDrawRandomState.anRandom[0] = -923067897;
  v0->tDrawRandomState.anRandom[1] = 971667286;
  v0->tDrawRandomState.anRandom[2] = 2146516173;
  v0->tRunRandomState.anRandom[0] = -773192938;
  v0->tRunRandomState.anRandom[1] = -965544106;
  v0->tRunRandomState.anRandom[2] = 1572805325;
  v0->tDrawRandomState.anRandom[0] = -773192938;
  v0->tDrawRandomState.anRandom[1] = -965544106;
  v0->tDrawRandomState.anRandom[2] = 1572805325;
  LOBYTE(v0->pxSpritesResource) = 0;
  v1 = (struct MemPoolFreeItem_s **)&v0->aptPlayerQTaskRef[2];
  v2 = &v0->aptPlayerQTaskRef[2];
  v0->aptPlayerQTaskRef[2] = nullptr;
  v0->aptPlayerQTaskRef[3] = nullptr;
  v0->atPlayerStatus[0].nScore = 0;
  v0 = (struct Game_s *)((char *)v0 + 248);
  v2[3] = nullptr;
  v0->tQTask.ptNext = nullptr;
  v0->tQTask.ptPrev = nullptr;
  v0->tQTask.tQTaskChildren.ptHead = nullptr;
  v0->tQTask.tQTaskChildren.ptMiddle = nullptr;
  if ( Level_atLevelQTaskID[0] )
  {
    ptPlayerQTask = (struct QTask_s *)Level_atLevelQTaskID[0]->pxObject;
    v3 = ptPlayerQTask;
  }
  else
  {
    v3 = nullptr;
    ptPlayerQTask = nullptr;
  }
  v4 = *v1;
  if ( *v1 )
  {
    if ( v4->ptNext )
      v4 = (struct MemPoolFreeItem_s *)Node_Remove(v4);
    --QTask_tQTaskRefPool.nAllocatedBlocks;
    v4->ptNext = QTask_tQTaskRefPool.tMemPoolFreeList.ptHead;
    QTask_tQTaskRefPool.tMemPoolFreeList.ptHead = v4;
    *v1 = nullptr;
  }
  if ( v3 )
    Game_ptGame->aptPlayerQTaskRef[2] = QTask_NewQTaskRef(v3);
  v5 = QTask_NewQTaskRef(nullptr);
  v6 = Game_ptGame;
  Game_ptGame->ptDebugCameraQTaskRef = v5;
  v7 = QTask_NewFn(&v6->tQTask, HumanCamera_eQTaskType, nullptr);
  v8 = Flow_ptFlow;
  v9 = v7;
  v10 = LevelFlow_ptLevelFlow;
  v9[2].tQTaskRefList.ptTail = (struct QReference_s *)&v6->tQCamera;
  nFrameNumber = (double)v10->nTimeOfDayTick / ((double)v8->nFrequency * 3600.0) + v10->vStartTime;
  QCamera_Set(
    &v6->tQCamera,
    (struct real64x3_t *)&v9[1],
    (struct real32x9_t *)&v9[1].tQTaskRefList.ptMiddle,
    *(float *)&v9[2].tQTaskRefList.ptMiddle,
    1.0,
    300.0,
    Screen_nFrameNumber,
    v9,
    nFrameNumber,
    0);
  v11 = QTask_NewQTaskRef(v9);
  v12 = Game_ptGame;
  Game_ptGame->ptHumanCameraQTaskRef = v11;
  if ( ptPlayerQTask )
  {
    if ( v11 )
      pxObject = (struct QTask_s *)v11->pxObject;
    else
      pxObject = nullptr;
    HumanCamera_SetHumanQTask(pxObject, ptPlayerQTask);
    v12 = Game_ptGame;
  }
  ptPrev = v12->ptGameScreenQTask[1].ptPrev;
  ptHead = ptPrev[2].tQTaskChildren.ptHead;
  ptPlayerQTaska = (struct QTask_s *)v12->ptWorld;
  v16 = QTask_NewFn(&v12->tQTask, Microphone_eQTaskType, nullptr);
  v16[1].ptNext = (struct QTask_s *)1065353216;
  v16[1].tQTaskChildren.ptTail = (struct QTask_s *)1065353216;
  v16[1].ptParent = (struct QTask_s *)1065353216;
  v16[3].tQTaskChildren.ptHead = ptPlayerQTaska;
  v16[1].ptPrev = nullptr;
  v16[1].tQTaskChildren.ptHead = nullptr;
  v16[1].tQTaskChildren.ptMiddle = nullptr;
  v16[1].tQTaskRefList.ptHead = nullptr;
  v16[1].tQTaskRefList.ptMiddle = nullptr;
  v16[1].tQTaskRefList.ptTail = nullptr;
  *(_DWORD *)&v16[1].eQTaskType = 0;
  v16[3].tQTaskRefList.ptTail = (struct QReference_s *)&ptPrev[8].tQTaskRefList.ptMiddle;
  v16[3].tQTaskRefList.ptMiddle = (struct QReference_s *)&ptHead[1];
  v16[3].tQTaskRefList.ptHead = (struct QReference_s *)ptHead;
  ptPrev[10].tQTaskRefList.ptHead = (struct QReference_s *)v16;
  Game_ptGame->ptMicrophoneQTaskRef = QTask_NewQTaskRef(v16);
  Sound_SetVolumeCD(
    Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tSoundOptions.vMusicVolume,
    Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tSoundOptions.vMusicVolume);
  Sound_vSSMasterVolume = Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tSoundOptions.vSoundEffectsVolume;
  if ( AppContext_tAppContext.isLightmapsDisabled == false || AppContext_tAppContext.isTerrainLightmapsUsed )
    Game_DeleteTerrainLightmaps(Level_ptStaticQTask);
}

// source: j/0/game.c:2068  [anchor-mhash]
void __cdecl Game_RefreshAfterLevelDelete()
{
  struct StatusMessageScreen_s *ptTail; // ebx
  int v1; // esi
  char *p_isUsed; // edi
  int i; // edi
  _DWORD *v4; // esi
  struct QReference_s *v5; // eax

  if ( StatusScreen_ptStatusScreenQTask )
  {
    ptTail = (struct StatusMessageScreen_s *)StatusScreen_ptStatusScreenQTask[52].tQTaskChildren.ptTail;
    v1 = 0;
    p_isUsed = &ptTail->atRegisteredMessage[0].isUsed;
    do
    {
      if ( *p_isUsed )
        StatusMessageScreen_RemoveMessage(ptTail, v1);
      ++v1;
      p_isUsed += 4148;
    }
    while ( v1 < 24 );
  }
  QTask_DeleteQTaskAndQTaskRefSafe(&Game_ptGame->ptDebugCameraQTaskRef);
  QTask_DeleteQTaskAndQTaskRefSafe(&Game_ptGame->ptHumanCameraQTaskRef);
  QTask_DeleteQTaskAndQTaskRefSafe(&Game_ptGame->ptMicrophoneQTaskRef);
  for ( i = 232; i < 248; i += 4 )
  {
    v4 = (struct QTask_s **)((char *)&Game_ptGame->tQTask.ptNext + i);
    v5 = *(struct QReference_s **)((char *)&Game_ptGame->tQTask.ptNext + i);
    if ( v5 )
    {
      QReference_Delete(v5, &QTask_tQTaskRefPool);
      *v4 = 0;
    }
  }
}

// source: j/0/game.c:2104  [anchor-callee]
void __cdecl Game_Restart()
{
  DWORD PerformanceCounter; // eax
  struct QReference_s *ptMicrophoneQTaskRef; // eax
  void *pxObject; // esi
  struct QReference_s *v3; // eax
  enum GameMode_e v4; // eax
  DWORD TickCount; // eax
  struct LoadingScreen_s *v6; // ebp
  struct StaticTilemap_s *ptStateText; // ecx
  char *v8; // ecx
  char *v9; // ecx
  struct StatusMessageScreen_s *ptTail; // ebx
  int v11; // esi
  char *p_isUsed; // edi
  char *v13; // ecx
  char *v14; // ecx
  char *v15; // ecx
  DWORD v16; // eax

  if ( !Flow_nSuspendRefCount )
  {
    if ( Timer_isPerformanceCounter )
      PerformanceCounter = Timer_GetPerformanceCounter();
    else
      PerformanceCounter = GetTickCount();
    Flow_nSuspendTime = PerformanceCounter - Timer_nStartTime;
  }
  ptMicrophoneQTaskRef = Game_ptGame->ptMicrophoneQTaskRef;
  ++Flow_nSuspendRefCount;
  if ( ptMicrophoneQTaskRef )
  {
    pxObject = ptMicrophoneQTaskRef->pxObject;
    if ( pxObject )
    {
      v3 = *((struct QReference_s **)pxObject + 38);
      if ( v3 )
      {
        QReference_Delete(v3, &QTask_tQTaskRefPool);
        *((_DWORD *)pxObject + 38) = 0;
      }
    }
  }
  v4 = Game_eGameMode;
  if ( Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER )
  {
    if ( Timer_isPerformanceCounter )
      TickCount = Timer_GetPerformanceCounter();
    else
      TickCount = GetTickCount();
    Game_ptGame[1].tQTask.ptNext = (struct QTask_s *)(TickCount - Timer_nStartTime);
    v4 = Game_eGameMode;
  }
  if ( v4 )
  {
    if ( v4 == GAME_GAMEMODE_MULTIPLAYER )
      Game_SaveCarryoverMP(Game_iMissionID);
  }
  else if ( Game_nMenuLoadFromSlot >= 0 )
  {
    Game_LoadFromSlot(Game_nMenuLoadFromSlot);
    Game_nMenuLoadFromSlot = -1;
    goto LABEL_47;
  }
  v6 = (struct LoadingScreen_s *)LoadingScreen_New(5, Game_iMissionID, true);
  v6->ptStateText->vR = 128.0;
  v6->ptStateText->vG = 128.0;
  ptStateText = v6->ptStateText;
  ptStateText->vB = 128.0;
  if ( Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER )
  {
    Text_SetString(v6->ptStateText, "Clearing sounds...");
    LoadingScreen_UpdateScreen(v6);
    LoadingScreen_UpdateScreen(v6);
    LoadingScreen_UpdateScreen(v6);
  }
  Game_MPRunNetwork((char *)ptStateText);
  SoundSys_ClearPlayList();
  ++v6->nActiveProgress;
  LoadingScreen_UpdateScreen(v6);
  if ( Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER )
  {
    Text_SetString(v6->ptStateText, "Removing status messages...");
    LoadingScreen_UpdateScreen(v6);
    LoadingScreen_UpdateScreen(v6);
    LoadingScreen_UpdateScreen(v6);
  }
  Game_MPRunNetwork(v8);
  ptTail = (struct StatusMessageScreen_s *)StatusScreen_ptStatusScreenQTask[52].tQTaskChildren.ptTail;
  v11 = 0;
  p_isUsed = &ptTail->atRegisteredMessage[0].isUsed;
  do
  {
    if ( *p_isUsed )
      StatusMessageScreen_RemoveMessage(ptTail, v11);
    ++v11;
    p_isUsed += 4148;
  }
  while ( v11 < 24 );
  if ( Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER )
  {
    Text_SetString(v6->ptStateText, "Clearing computer log...");
    LoadingScreen_UpdateScreen(v6);
    LoadingScreen_UpdateScreen(v6);
    LoadingScreen_UpdateScreen(v6);
  }
  Game_MPRunNetwork(v9);
  ComputerLog_ClearLog();
  ++v6->nActiveProgress;
  LoadingScreen_UpdateScreen(v6);
  if ( Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER )
  {
    Text_SetString(v6->ptStateText, "Freeing objects...");
    LoadingScreen_UpdateScreen(v6);
    LoadingScreen_UpdateScreen(v6);
    LoadingScreen_UpdateScreen(v6);
  }
  Game_MPRunNetwork(v13);
  if ( Level_ptQLevelQTask )
    QTask_DeleteChildren(&Level_ptQLevelQTask->tQTask);
  memset(Level_aisLevelQTaskAllocated, 0, sizeof(Level_aisLevelQTaskAllocated));
  ++v6->nActiveProgress;
  LoadingScreen_UpdateScreen(v6);
  if ( Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER )
  {
    Text_SetString(v6->ptStateText, "Updating LOD settings...");
    LoadingScreen_UpdateScreen(v6);
    LoadingScreen_UpdateScreen(v6);
    LoadingScreen_UpdateScreen(v6);
  }
  Game_MPRunNetwork(v14);
  if ( ModelLODSettingsContainer_ptQTask )
    QTask_TriggerQTaskEventRecursively(
      &ModelLODSettingsContainer_ptQTask->tQTask,
      ParameterList_eUpdateInternalDataQTaskEvent,
      nullptr);
  if ( LocalModelLODSettingsContainer_ptQTask )
    QTask_TriggerQTaskEventRecursively(
      &LocalModelLODSettingsContainer_ptQTask->tQTask,
      ParameterList_eUpdateInternalDataQTaskEvent,
      nullptr);
  if ( Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER )
  {
    Text_SetString(v6->ptStateText, (char *)&stru_6A5458.vB);
    LoadingScreen_UpdateScreen(v6);
    LoadingScreen_UpdateScreen(v6);
    LoadingScreen_UpdateScreen(v6);
  }
  Game_MPRunNetwork(v15);
  Level_LoadObjects("MISSION:", 30);
  if ( Game_eGameMode != GAME_GAMEMODE_MULTIPLAYER )
    Game_LoadCarryOver(Game_iMissionID);
  QTask_TriggerQTaskEventRecursivelyNoContext(&Game_ptGame->tQTask, Human_eUpdateInternalDataAfterCarryoverQTaskEvent);
  ++v6->nActiveProgress;
  LoadingScreen_UpdateScreen(v6);
  ++v6->nActiveProgress;
  LoadingScreen_UpdateScreen(v6);
  if ( Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER )
  {
    Text_SetString(v6->ptStateText, (char *)&stru_6A5458);
    LoadingScreen_UpdateScreen(v6);
    LoadingScreen_UpdateScreen(v6);
    LoadingScreen_UpdateScreen(v6);
  }
  LoadingScreen_Delete(v6);
LABEL_47:
  if ( !--Flow_nSuspendRefCount )
  {
    if ( Timer_isPerformanceCounter )
      v16 = Timer_GetPerformanceCounter();
    else
      v16 = GetTickCount();
    Flow_ptFlow->nSkipTime += v16 - Timer_nStartTime - Flow_nSuspendTime;
    Flow_nSuspendTime = 0;
  }
}

// source: j/0/game.c:2205  [size]
int __cdecl Game_GetDefaultMissionID()
{
  return 0;
}

// source: j/0/game.c:2218  [anchor-caller]
void __cdecl Game_CreateMissionScoreScreen()
{
  char *pxObject; // esi
  struct MissionScoreSettings_s *FirstChildOfType; // eax
  struct QTask_s *v2; // eax
  char zLoadFont[260]; // [esp+0h] [ebp-104h] BYREF

  if ( Game_ptMissionScoreScreenQTaskRef )
  {
    QReference_Delete(Game_ptMissionScoreScreenQTaskRef, &QTask_tQTaskRefPool);
    Game_ptMissionScoreScreenQTaskRef = nullptr;
  }
  if ( Game_eGameMode == GAME_GAMEMODE_SINGLEPLAYER )
  {
    if ( Level_atLevelQTaskID[0] )
    {
      pxObject = (char *)Level_atLevelQTaskID[0]->pxObject;
      if ( pxObject )
      {
        if ( QTask_IsQTaskTypeDerived(*((_WORD *)pxObject + 18), Human_eQTaskType) )
        {
          Game_GetLoadFont(zLoadFont, off_6A5454);
          if ( !Level_ptQLevelQTask
            || (FirstChildOfType = (struct MissionScoreSettings_s *)QTask_GetFirstChildOfType(
                                                                      &Level_ptQLevelQTask->tQTask,
                                                                      MissionScoreSettings_eQTaskType)) == nullptr )
          {
            FirstChildOfType = nullptr;
          }
          v2 = MissionScoreScreen_New(
                 nullptr,
                 (struct HumanMissionScoreData_s *)(pxObject + 472),
                 FirstChildOfType,
                 2u,
                 0,
                 0,
                 0,
                 0,
                 zLoadFont,
                 zLoadFont);
          Game_ptMissionScoreScreenQTaskRef = QTask_NewQTaskRef(v2);
        }
      }
    }
  }
}

// source: j/0/game.c:2246  [anchor-hash]
struct QTask_s *__cdecl Game_GetMissionScoreScreen()
{
  if ( Game_ptMissionScoreScreenQTaskRef )
    return (struct QTask_s *)Game_ptMissionScoreScreenQTaskRef->pxObject;
  else
    return nullptr;
}

// source: j/0/game.c:2259  [anchor-hash]
struct QTask_s *__cdecl Game_GetHumanCamera()
{
  struct QReference_s *ptHumanCameraQTaskRef; // eax

  ptHumanCameraQTaskRef = Game_ptGame->ptHumanCameraQTaskRef;
  if ( ptHumanCameraQTaskRef )
    return (struct QTask_s *)ptHumanCameraQTaskRef->pxObject;
  else
    return nullptr;
}

// source: j/0/game.c:2272  [anchor-hash]
int __cdecl Game_GetAvailableSaveGameSlots()
{
  enum GameDifficulty_e eDifficultyLevel; // eax

  if ( 2752 * Config_tConfig.iActiveProfile == -7392072 )
    return 0;
  eDifficultyLevel = Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eDifficultyLevel;
  if ( eDifficultyLevel == GAMEDIFFICULTY_1 )
    return 3;
  if ( eDifficultyLevel != GAMEDIFFICULTY_2 )
    return 0;
  return 2;
}

// source: j/0/game.c:2307  [anchor-mhash]
char *__cdecl Game_CreateSaveFilenameForSlotEx(
        char *zBuffer,
        unsigned int nBufferSize,
        int iSlot,
        int iPlayerProfile,
        int iMissionID)
{
  sprintf(
    zBuffer,
    (char *const)&g_ptParentQTask.tQTaskRefList,
    iPlayerProfile,
    Config_tConfig.atPlayerProfile[iPlayerProfile].tGameOptions.eDifficultyLevel,
    iMissionID,
    iSlot);
  return zBuffer;
}

// source: j/0/game.c:2335  [anchor-strings]
enum bool __cdecl Game_ParseSaveGameFilename(
        int *piPlayerProfile,
        int *piDifficultyLevel,
        int *piMissionID,
        int *piSlot,
        char *zFilename)
{
  #pragma pack(push, 1)
  union
  {
    struct { int iPlayerProfile; };
    struct { char igi2_o1[4]; int iDifficultyLevel; };
    struct { char igi2_o2[8]; int iMissionID; };
    struct { char igi2_o3[12]; int iSlot; };
    char igi2_extent[16];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)

  if ( scprintf(zFilename, &g_ptParentQTask.tQTaskChildren, &igi2_frame.iPlayerProfile, &igi2_frame.iDifficultyLevel, &igi2_frame.iMissionID, &igi2_frame.iSlot) != 4 )
    return false;
  if ( piPlayerProfile )
    *piPlayerProfile = igi2_frame.iPlayerProfile;
  if ( piDifficultyLevel )
    *piDifficultyLevel = igi2_frame.iDifficultyLevel;
  if ( piMissionID )
    *piMissionID = igi2_frame.iMissionID;
  if ( piSlot )
    *piSlot = igi2_frame.iSlot;
  return true;
}

// source: j/0/game.c:2375  [anchor-mhash]
char *__cdecl Game_CreateSaveFilenameForSlot(char *zBuffer, unsigned int nBufferSize, int iSlot)
{
  char *v3; // esi

  sprintf(
    v3,
    (char *const)&g_ptParentQTask.tQTaskRefList,
    Config_tConfig.iActiveProfile,
    Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eDifficultyLevel,
    Game_iMissionID);
}

// source: j/0/game.c:2388  [anchor-callee]
void __cdecl Game_SaveToSlot(int iSlot)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct SaveGame_s ptSaveGame; };
    struct { char igi2_o1[16]; char Buffer[264]; };
    char igi2_extent[280];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  DWORD PerformanceCounter; // eax
  struct Game_s *v2; // edi
  _DWORD *pxObject; // esi
  int v4; // edx
  DWORD TickCount; // eax

  if ( !Flow_nSuspendRefCount )
  {
    if ( Timer_isPerformanceCounter )
      PerformanceCounter = Timer_GetPerformanceCounter();
    else
      PerformanceCounter = GetTickCount();
    Flow_nSuspendTime = PerformanceCounter - Timer_nStartTime;
  }
  ++Flow_nSuspendRefCount;
  if ( !Level_atLevelQTaskID[0] )
    goto LABEL_10;
  if ( !Level_atLevelQTaskID[0]->pxObject )
    goto LABEL_10;
  v2 = Game_ptGame;
  pxObject = Level_atLevelQTaskID[0]->pxObject;
  sprintf(
    igi2_frame.Buffer,
    (char *const)&g_ptParentQTask.tQTaskRefList,
    Config_tConfig.iActiveProfile,
    Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eDifficultyLevel,
    Game_iMissionID,
    iSlot);
  v4 = pxObject[125];
  igi2_frame.ptSaveGame.isValid = 1;
  igi2_frame.ptSaveGame.nMissionID = Game_iMissionID;
  igi2_frame.ptSaveGame.nVersion = 63;
  igi2_frame.ptSaveGame.nTicks = v4;
  if ( SaveGame_Create(igi2_frame.Buffer, &v2->tQTask, &igi2_frame.ptSaveGame, (char *)&g_ptParentQTask) )
    StatusMessage_New(
      Level_ptDynamicQTask,
      "Saving complete",
      (char *)&g_zInitialValue,
      (char *)&g_zInitialValue,
      true);
  else
LABEL_10:
    StatusMessage_New(
      Level_ptDynamicQTask,
      "Saving failed",
      (char *)&g_zInitialValue,
      (char *)&g_zInitialValue,
      true);
  if ( !--Flow_nSuspendRefCount )
  {
    if ( Timer_isPerformanceCounter )
      TickCount = Timer_GetPerformanceCounter();
    else
      TickCount = GetTickCount();
    Flow_ptFlow->nSkipTime += TickCount - Timer_nStartTime - Flow_nSuspendTime;
    Flow_nSuspendTime = 0;
  }
}

// source: j/0/game.c:2426  [anchor-caller]
enum bool __cdecl Game_LoadFromSlot(int iSlot)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct SaveGame_s ptSaveGame; };
    struct { char igi2_o1[16]; char Buffer[264]; };
    char igi2_extent[280];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  enum bool v1; // ebp
  DWORD PerformanceCounter; // eax
  struct QTaskList_s *v3; // edi
  struct QTask_s **ptQTask; // esi
  struct StatusMessageScreen_s *ptTail; // ebx
  int v6; // esi
  char *p_isUsed; // edi
  struct QTaskList_s *v8; // edi
  struct QTask_s **v9; // esi
  DWORD TickCount; // eax

  v1 = false;
  if ( !Flow_nSuspendRefCount )
  {
    if ( Timer_isPerformanceCounter )
      PerformanceCounter = Timer_GetPerformanceCounter();
    else
      PerformanceCounter = GetTickCount();
    Flow_nSuspendTime = PerformanceCounter - Timer_nStartTime;
  }
  ++Flow_nSuspendRefCount;
  sprintf(
    igi2_frame.Buffer,
    (char *const)&g_ptParentQTask.tQTaskRefList,
    Config_tConfig.iActiveProfile,
    Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eDifficultyLevel,
    Game_iMissionID,
    iSlot);
  if ( SaveGame_LoadFile(&igi2_frame.ptSaveGame, igi2_frame.Buffer, true, nullptr) )
  {
    Missile_DeleteAllSmoke();
    Game_KillSoundTasks(Game_ptGame->ptLevelQTask);
    BulletHole_DeleteAll();
    v3 = Mine_ptMineQTaskList;
    if ( Mine_ptMineQTaskList->nTask )
    {
      ptQTask = Mine_ptMineQTaskList->ptQTask;
      do
        QTask_Delete(*ptQTask);
      while ( v3->nTask );
    }
    ptTail = (struct StatusMessageScreen_s *)StatusScreen_ptStatusScreenQTask[52].tQTaskChildren.ptTail;
    v6 = 0;
    p_isUsed = &ptTail->atRegisteredMessage[0].isUsed;
    do
    {
      if ( *p_isUsed )
        StatusMessageScreen_RemoveMessage(ptTail, v6);
      ++v6;
      p_isUsed += 4148;
    }
    while ( v6 < 24 );
    StatusMessage_CleanUp();
    ComputerLog_ClearLog();
    QTask_DeleteQTaskAndQTaskRefSafe(&g_pptQTaskRef);
    v8 = GameFunctions_ptPickupQTaskList;
    if ( GameFunctions_ptPickupQTaskList->nTask )
    {
      v9 = GameFunctions_ptPickupQTaskList->ptQTask;
      do
        QTask_Delete(*v9);
      while ( v8->nTask );
    }
    if ( SaveGame_LoadFile(&igi2_frame.ptSaveGame, igi2_frame.Buffer, false, &Game_ptGame->tQTask) )
    {
      StatusMessage_New(
        Level_ptDynamicQTask,
        "Loading complete",
        (char *)&g_zInitialValue,
        (char *)&g_zInitialValue,
        true);
      v1 = true;
    }
    else
    {
      StatusMessage_New(
        Level_ptDynamicQTask,
        "Loading failed",
        (char *)&g_zInitialValue,
        (char *)&g_zInitialValue,
        true);
    }
  }
  if ( !--Flow_nSuspendRefCount )
  {
    if ( Timer_isPerformanceCounter )
      TickCount = Timer_GetPerformanceCounter();
    else
      TickCount = GetTickCount();
    Flow_ptFlow->nSkipTime += TickCount - Timer_nStartTime - Flow_nSuspendTime;
    Flow_nSuspendTime = 0;
  }
  return v1;
}

// source: j/0/game.c:2514  [anchor-callee]
enum bool __cdecl Game_FindNewestSaveGame(int *piSlot)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct FileTime_s tFileTime; };
    struct { char igi2_o1[8]; struct FileTime_s tTempFileTime; };
    struct { char igi2_o2[16]; struct SaveGame_s tSaveGame; };
    struct { char igi2_o3[32]; char zFilename[264]; };
    char igi2_extent[296];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v1; // ebx
  int i; // esi

  igi2_frame.tFileTime.tFileTime.dwLowDateTime = 0;
  v1 = 0;
  igi2_frame.tFileTime.tFileTime.dwHighDateTime = 0;
  for ( i = 0; i <= 5; ++i )
  {
    sprintf(
      igi2_frame.zFilename,
      (char *const)&g_ptParentQTask.tQTaskRefList,
      Config_tConfig.iActiveProfile,
      Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eDifficultyLevel,
      Game_iMissionID,
      i);
    if ( SaveGame_LoadFile(&igi2_frame.tSaveGame, igi2_frame.zFilename, true, nullptr) )
    {
      File_GetFileTime(&igi2_frame.tTempFileTime, igi2_frame.zFilename);
      if ( CompareFileTime(&igi2_frame.tFileTime.tFileTime, &igi2_frame.tTempFileTime.tFileTime) < 0 )
      {
        v1 = i + 1;
        igi2_frame.tFileTime = igi2_frame.tTempFileTime;
      }
    }
  }
  if ( !v1 )
    return false;
  *piSlot = v1 - 1;
  return true;
}

// source: j/0/game.c:2564  [size]
enum bool __cdecl Game_CheckQuickSave(int *piSlot)
{
  return false;
}

// source: j/0/game.c:2596  [size]
enum bool __cdecl Game_GetSaveGameTimeDateString(
        struct SaveGame_s *ptSaveGame,
        char *zBuffer,
        unsigned int nBufferSize,
        char *zFilename)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct FileTime_s tFileTime; };
    struct { char igi2_o1[8]; struct _FILETIME tLocalFileTime; };
    struct { char igi2_o2[16]; struct _SYSTEMTIME tSystemTime; };
    struct { char igi2_o3[32]; char zTime[256]; };
    struct { char igi2_o4[288]; char zDate[256]; };
    char igi2_extent[544];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)

  *zBuffer = 0;
  if ( SaveGame_LoadFile(ptSaveGame, zFilename, true, nullptr) == false )
    return false;
  File_GetFileTime(&igi2_frame.tFileTime, zFilename);
  FileTimeToLocalFileTime(&igi2_frame.tFileTime.tFileTime, &igi2_frame.tLocalFileTime);
  FileTimeToSystemTime(&igi2_frame.tLocalFileTime, &igi2_frame.tSystemTime);
  GetDateFormatA(0x400u, 1u, &igi2_frame.tSystemTime, nullptr, igi2_frame.zDate, 256);
  GetTimeFormatA(0x400u, 0, &igi2_frame.tSystemTime, nullptr, igi2_frame.zTime, 256);
  _snprintf(zBuffer, nBufferSize, "(%s %s)", igi2_frame.zDate, igi2_frame.zTime);
  return true;
}

// source: j/0/game.c:2637  [anchor-strings]
int __cdecl Game_GetTimeStringFromGameTicks(char *zBuffer, unsigned int nBufferSize, int nTicks)
{
  return _snprintf(
           zBuffer,
           nBufferSize,
           "%d:%02d:%02d",
           nTicks / 30 / 3600,
           nTicks / 30 % 3600 / 60,
           nTicks / 30 % 3600 % 60);
}

// source: j/0/game.c:2663  [anchor-strings]
void __cdecl Game_GetSaveGameInfoString(
        char *zBuffer,
        unsigned int nBufferSize,
        struct SaveGame_s *ptSaveGame)
{
  #pragma pack(push, 1)
  union
  {
    struct { char *LocalizedStringForLanguage; };
    struct { char igi2_o1[8]; char zTime[256]; };
    char igi2_extent[264];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)

  Game_GetTimeStringFromGameTicks(igi2_frame.zTime, 0x100u, ptSaveGame->nTicks);
  igi2_frame.LocalizedStringForLanguage = Config_GetLocalizedStringForLanguage(
                                 "menusystem/Mission Time",
                                 Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eLanguage,
                                 true);
  _snprintf(zBuffer, nBufferSize, "%s: %s", igi2_frame.LocalizedStringForLanguage, igi2_frame.zTime);
}

// source: j/0/game.c:2686  [anchor-mhash]
struct Result_s *__cdecl Game_GetNumberOfValidSaveGames(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  #pragma pack(push, 1)
  union
  {
    struct { int nSaveGames; };
    struct { char igi2_o1[4]; int iMissionID; };
    struct { char igi2_o2[8]; struct PlayerProfile_s *v8; };
    struct { char igi2_o3[12]; _BYTE tSaveGame[24]; };
    struct { char igi2_o4[36]; char zFilename[264]; };
    char igi2_extent[300];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int iActiveProfile; // ebx
  int v4; // esi

  iActiveProfile = Config_tConfig.iActiveProfile;
  v4 = 0;
  if ( ptArgList->isQVM )
  {
    igi2_frame.nSaveGames = 0;
    QVM_EvalArg(&igi2_frame.nSaveGames, 4, ptArgList, 0, 1);
    igi2_frame.iMissionID = igi2_frame.nSaveGames;
  }
  else
  {
    igi2_frame.iMissionID = Expression_EvalInt(*ptArgList->aptExpression);
  }
  igi2_frame.nSaveGames = 0;
  igi2_frame.v8 = &Config_tConfig.atPlayerProfile[iActiveProfile];
  do
  {
    sprintf(
      igi2_frame.zFilename,
      (char *const)&g_ptParentQTask.tQTaskRefList,
      iActiveProfile,
      igi2_frame.v8->tGameOptions.eDifficultyLevel,
      igi2_frame.iMissionID,
      v4);
    if ( SaveGame_LoadFile((struct SaveGame_s *)igi2_frame.tSaveGame, igi2_frame.zFilename, true, nullptr) )
      ++igi2_frame.nSaveGames;
    ++v4;
  }
  while ( v4 < 5 );
  *(double *)&igi2_frame.tSaveGame[8] = (double)igi2_frame.nSaveGames;
  *(_DWORD *)igi2_frame.tSaveGame = igi2_frame.nSaveGames;
  *(_DWORD *)&igi2_frame.tSaveGame[16] = &g_zInitialValue;
  qmemcpy(retstr, igi2_frame.tSaveGame, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/game.c:2725  [anchor-caller]
struct Result_s *__cdecl Game_FillSaveGameScrollListBox(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  #pragma pack(push, 1)
  union
  {
    struct { int iPlayerProfile; };
    struct { char igi2_o1[4]; struct PlayerProfile_s *v8; };
    struct { char igi2_o2[8]; _BYTE tSaveGame[24]; };
    struct { char igi2_o3[32]; char zDesc[256]; };
    struct { char igi2_o4[288]; char zTimeDate[256]; };
    struct { char igi2_o5[544]; char zBuffer[256]; };
    struct { char igi2_o6[800]; char zFilename[260]; };
    struct { char igi2_o7[1060]; char zItem[512]; };
    char igi2_extent[1572];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v3; // ebp
  char *LocalizedStringForLanguage; // eax
  char *v5; // eax

  igi2_frame.iPlayerProfile = Config_tConfig.iActiveProfile;
  v3 = 0;
  igi2_frame.v8 = &Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile];
  do
  {
    sprintf(
      igi2_frame.zFilename,
      (char *const)&g_ptParentQTask.tQTaskRefList,
      igi2_frame.iPlayerProfile,
      igi2_frame.v8->tGameOptions.eDifficultyLevel,
      Game_iMissionID,
      v3);
    if ( Game_GetSaveGameTimeDateString((struct SaveGame_s *)igi2_frame.tSaveGame, igi2_frame.zTimeDate, 0x100u, igi2_frame.zFilename) )
    {
      Game_GetTimeStringFromGameTicks(igi2_frame.zBuffer, 0x100u, *(int *)&igi2_frame.tSaveGame[8]);
      LocalizedStringForLanguage = Config_GetLocalizedStringForLanguage(
                                     "menusystem/Mission Time",
                                     Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eLanguage,
                                     true);
      _snprintf(igi2_frame.zDesc, 0x100u, "%s: %s", LocalizedStringForLanguage, igi2_frame.zBuffer);
      if ( v3 >= 5 )
      {
        v5 = Config_GetLocalizedStringForLanguage(
               "menusystem/Quicksave",
               Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eLanguage,
               true);
        sprintf(igi2_frame.zItem, "%s [%s] %s", igi2_frame.zTimeDate, v5, igi2_frame.zDesc);
      }
      else
      {
        sprintf(igi2_frame.zItem, "%s %s", igi2_frame.zTimeDate, igi2_frame.zDesc);
      }
      ScrollListBox_AddItemEx(igi2_frame.zItem, v3, false);
    }
    ++v3;
  }
  while ( v3 <= 5 );
  ScrollListBox_AddItemEx(
    "menusystem/Restart Mission",
    (int)&MTP_atLODVirModel[23].atBoneVertexRefs[14].atVertexRefs[398].iVertex + 2,
    true);
  *(_DWORD *)igi2_frame.tSaveGame = 0;
  *(_DWORD *)&igi2_frame.tSaveGame[8] = 0;
  *(_DWORD *)&igi2_frame.tSaveGame[12] = 0;
  *(_DWORD *)&igi2_frame.tSaveGame[16] = &g_zInitialValue;
  qmemcpy(retstr, igi2_frame.tSaveGame, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/game.c:2775  [anchor-mhash]
struct Result_s *__cdecl Game_SetMenuLoadFromSlot(
        struct Result_s *retstr,
        void *pxContext,
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
  Game_nMenuLoadFromSlot = (int)v4;
  if ( v4 == (struct ArgList_s *)((char *)&MTP_atLODVirModel[23].atBoneVertexRefs[14].atVertexRefs[398].iVertex + 2) )
    Game_nMenuLoadFromSlot = -1;
  Rs.nResult = 0;
  Rs.vResult = 0.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/game.c:2793  [size]
int __cdecl Game_SetLoadFromSlot(int iSlot)
{
  Game_nMenuLoadFromSlot = iSlot;
  return iSlot;
}

// source: j/0/game.c:2806  [anchor-caller]
struct Result_s *__cdecl Game_GetNewestSaveGameSlot(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  #pragma pack(push, 1)
  union
  {
    struct { int iSlot; };
    struct { char igi2_o1[4]; struct Result_s Rs; };
    char igi2_extent[28];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)

  if ( Game_FindNewestSaveGame(&igi2_frame.iSlot) == false )
    igi2_frame.iSlot = (int)&MTP_atLODVirModel[23].atBoneVertexRefs[14].atVertexRefs[398].iVertex + 2;
  igi2_frame.Rs.vResult = (double)igi2_frame.iSlot;
  igi2_frame.Rs.nResult = igi2_frame.iSlot;
  igi2_frame.Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &igi2_frame.Rs, sizeof(struct Result_s));
  return retstr;
}

struct QTask_s *sub_40A180()
{
  struct QTask_s *ptHead; // eax

  ptHead = Game_ptGame->ptGameScreenQTask[1].tQTaskChildren.ptHead;
  if ( ptHead )
    return ptHead->tQTaskChildren.ptHead;
  else
    return nullptr;
}

// source: j/0/game.c:2845  [anchor-strings]
void __cdecl Game_Open()
{
  unsigned __int16 BaseQTaskType; // ax
  unsigned __int16 v1; // si

  AppMain_FindPrefix(AppContext_tAppContext.zCmdLine, "Level", Game_ParseLevelCB);
  if ( AppContext_tAppContext.nPort > 0 || AppContext_tAppContext.isServer || AppContext_tAppContext.isDrawingDisabled )
  {
    Game_eGameMode = GAME_GAMEMODE_MULTIPLAYER;
    AppContext_tAppContext.isEditorState = false;
  }
  else
  {
    Game_eGameMode = GAME_GAMEMODE_SINGLEPLAYER;
  }
  BaseQTaskType = QTask_GetBaseQTaskType();
  v1 = QTask_NewQTaskType("Game", 400, BaseQTaskType, 0, 0);
  Game_eQTaskType = v1;
  QTask_LinkQTaskEventHandlerFn(v1, 0, Game_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 1, Game_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 2, Game_DeleteHandler);
  Symbol_Register(
    "GAME_FREQUENCY",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)0x1E,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "WORLD_METER",
    Script_Float,
    &Game_vWorldMeter,
    8,
    QSCRIPT_SYMBOLCLASS_VARIABLE,
    QSCRIPT_SYMBOLTYPE_FLOAT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "MATH_PI",
    Script_Float,
    &Game_vMathPI,
    8,
    QSCRIPT_SYMBOLCLASS_VARIABLE,
    QSCRIPT_SYMBOLTYPE_FLOAT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "GAME_GAMEMODE_SINGLEPLAYER",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    nullptr,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "GAME_GAMEMODE_MULTIPLAYER",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)1,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "Game_SetGameMode",
    Game_SetGameModeCB,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "Game_GetGameMode",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Game_GetGameModeCB,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "Game_SetMission",
    Game_SetMissionCB,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "Game_UpdateVolume",
    Game_UpdateVolumeCB,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "Game_DisablePlayerInput",
    Game_DisablePlayerInputCB,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "Game_EnablePlayerInput",
    Game_EnablePlayerInputCB,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "Game_SetMusicVolume",
    Game_SetMusicVolumeCB,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "Game_SetSFXVolume",
    Game_SetSFXVolumeCB,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "Game_EnableMusic",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Game_EnableMusicCB,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "Game_DisableMusic",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Game_DisableMusicCB,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "Game_CutsceneDelete",
    Game_CutsceneDeleteCB,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  HandiCamFilter_zCounterFont = "LOCAL:common/fonts/font3.fnt";
  HandiCamFilter_nCounterXOffset = 117;
  HandiCamFilter_nCounterYOffset = 20;
  HandiCamFilter_zBatterySprite = "LOCAL:common/sprites/battery.spr";
  HandiCamFilter_nBatteryXOffset = 4;
  HandiCamFilter_nBatteryYOffset = 2;
  BandFilter_zCameraFont = "LOCAL:common/fonts/font3.fnt";
  BandFilter_vXFactor = 0.8999999761581421;
  BandFilter_vYFactor = 0.20000000298023224;
  BandFilter_vXOffset = -50.0;
  BandFilter_vYOffset = 0.0;
  SplinePath_vFlowFrequency = 30.0;
  Symbol_Register(
    "Game_GetNumberOfValidSaveGames",
    Game_GetNumberOfValidSaveGames,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "Game_FillSaveGameScrollListBox",
    Game_FillSaveGameScrollListBox,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "Game_SetMenuLoadFromSlot",
    Game_SetMenuLoadFromSlot,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "Game_GetNewestSaveGameSlot",
    Game_GetNewestSaveGameSlot,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
}

// source: j/0/game.c:2926  [anchor-hash]
void __cdecl Game_Close()
{
  QTask_DeleteQTaskType(Game_eQTaskType);
  if ( Game_ptMissionScoreScreenQTaskRef )
  {
    QReference_Delete(Game_ptMissionScoreScreenQTaskRef, &QTask_tQTaskRefPool);
    Game_ptMissionScoreScreenQTaskRef = nullptr;
  }
}
