/* j/0/config.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/config.c:523  [anchor-mhash]
void __cdecl Config_SetGamma(float vGamma)
{
  float vGammaa = *(float *)&vGamma; // [esp+4h] [ebp+4h] ARGSLOT

  vGammaa = 1.0 - vGamma;
  if ( vGammaa >= 0.10000000149011612 )
  {
    if ( vGammaa > 1.0 )
      vGammaa = 1.0;
    Direct3D_SetGamma(vGammaa);
  }
  else
  {
    Direct3D_SetGamma(0.10000000149011612);
  }
}

// source: j/0/config.c:538  [anchor-mhash]
struct Result_s *__cdecl Config_ParseVersion(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  struct ArgList_s *v3; // edi
  struct ArgList_s *v4; // eax
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  v3 = ptArgList;
  if ( ptArgList->nArguments == 1 )
  {
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
    Script_isBreakEnabled = (int)v4 < 5;
  }
  Rs.nResult = 0;
  Rs.vResult = 0.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/config.c:566  [anchor-callee]
void __cdecl Config_SetPlayerProfileDefaults(int iPlayerProfile)
{
  int v1; // edx

  v1 = iPlayerProfile;
  memset(&Config_tConfig.atPlayerProfile[v1], 0, sizeof(Config_tConfig.atPlayerProfile[v1]));
  Config_tConfig.atPlayerProfile[v1].tSoundOptions.i3DSoundProvider = provider_activeindex;
  Config_tConfig.atPlayerProfile[v1].tGraphicOptions.vCrossHairThickness = 1.0;
  Config_tConfig.atPlayerProfile[v1].tGraphicOptions.vCrossHairR = 1.0;
  *((_DWORD *)&Config_tConfig.atPlayerProfile[v1].tSoundOptions + 5) = 0;
  Config_tConfig.atPlayerProfile[v1].tGraphicOptions.vCrossHairG = 0.25;
  Config_tConfig.atPlayerProfile[v1].tGraphicOptions.vCrossHairB = 0.0;
  Config_tConfig.atPlayerProfile[v1].tGraphicOptions.eTextureFilteringMode = 0;
  Config_tConfig.atPlayerProfile[v1].tGraphicOptions.eAntialiasingMode = 0;
  Config_tConfig.atPlayerProfile[v1].tGraphicOptions.eDetailLevel = GFXOPTIONS_DETAIL_HIGH;
  qmemcpy(
    &Config_tConfig.atPlayerProfile[v1].tGraphicOptions.tGfxOptions,
    &GfxOptions_atDefaultOptions[3],
    sizeof(Config_tConfig.atPlayerProfile[v1].tGraphicOptions.tGfxOptions));
}

// source: j/0/config.c:587  [anchor-hash]
char *__cdecl Config_GetMissionStatsEntryDesc(int iMissionID)
{
  sprintf(byte_70CB00, &g_zFileName.atPictureResources[22].zResourceFilename[32], iMissionID);
  return byte_70CB00;
}

// source: j/0/config.c:604  [size]
int __cdecl Config_GetActiveMissionFromPlayerProfile(int iPlayerProfile)
{
  return Config_tConfig.atPlayerProfile[iPlayerProfile].anActiveMission[Config_tConfig.atPlayerProfile[iPlayerProfile].tGameOptions.eDifficultyLevel];
}

// source: j/0/config.c:617  [anchor-mhash]
void __cdecl Config_FreeMissionStatsEntry(
        struct QHashTable_s *ptHashTable,
        char *zKey,
        struct ConfigMissionStats_s *ptConfigMissionStats,
        void *pxUnused)
{
  unsigned int v4; // eax
  int v5; // esi

  v4 = ptHashTable->tPrivate.pfHashFunction(ptHashTable->tPrivate.nHashTableSize, zKey);
  ((void  (__cdecl *)(struct QHashTable_s *, unsigned int, const void *))ptHashTable->tPrivate.pfDeleteElement)(ptHashTable, v4, (const void *)(zKey));
  if ( ptConfigMissionStats )
  {
    v5 = *(_DWORD *)((unsigned int)&ptConfigMissionStats[-1].tMissionScoreSettings.atMissionRankRequirement[2].avRequired[4]
                   & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v5);
    memset(*(void **)(v5 + 8), 0xCDu, *(_DWORD *)(v5 + 16));
    free((void *)v5);
  }
}

// source: j/0/config.c:631  [anchor-mhash]
int __cdecl Config_FreePlayerProfileResources(int iPlayerProfile)
{
  struct QHashTable_s **p_ptMissionStatsHashTable; // esi
  int result; // eax

  p_ptMissionStatsHashTable = &Config_tConfig.atPlayerProfile[iPlayerProfile].ptMissionStatsHashTable;
  result = (int)*p_ptMissionStatsHashTable;
  if ( *p_ptMissionStatsHashTable )
  {
    if ( *(_DWORD *)result )
      (*(void (__cdecl **)(int, void (__cdecl *)(struct QHashTable_s *, char *, struct ConfigMissionStats_s *, void *), _DWORD))(result + 36))(
        result,
        Config_FreeMissionStatsEntry,
        0);
    QHashTable_Delete(*p_ptMissionStatsHashTable);
    *p_ptMissionStatsHashTable = nullptr;
  }
  return result;
}

// source: j/0/config.c:649  [anchor-callee]
int __cdecl Config_AllocatePlayerProfileResources(int iPlayerProfile)
{
  struct QHashTable_s **p_ptMissionStatsHashTable; // ebp
  struct QHashTable_s *v2; // eax
  struct QHashTable_s *v3; // esi
  void *v4; // edi
  int result; // eax

  p_ptMissionStatsHashTable = &Config_tConfig.atPlayerProfile[iPlayerProfile].ptMissionStatsHashTable;
  v2 = *p_ptMissionStatsHashTable;
  if ( *p_ptMissionStatsHashTable )
  {
    if ( v2->tPrivate.nEntries )
      v2->tPrivate.pfMap(
        v2,
        (void (__cdecl *)(struct QHashTable_s *, void *, void *, void *))Config_FreeMissionStatsEntry,
        nullptr);
    QHashTable_Delete(*p_ptMissionStatsHashTable);
    *p_ptMissionStatsHashTable = nullptr;
  }
  v3 = (struct QHashTable_s *)Mem_AllocFn(40, 4);
  v3->tPrivate.nHashTableSize = 512;
  v3->tPrivate.pfHashFunction = QHashTable_StringHashFunction;
  v3->tPrivate.pfCompareKey = QHashTable_StringCompareKeyFunction;
  v3->tPrivate.pfDuplicateKey = QHashTable_StringDuplicateKeyFunction;
  v3->tPrivate.pfCreateElement = QHashTable_CreateElementChained;
  v3->tPrivate.pfFindElement = QHashTable_FindElementChained;
  v3->tPrivate.pfDeleteElement = QHashTable_DeleteElementChained;
  v3->tPrivate.pfMap = QHashTable_MapChained;
  v3->tPrivate.nEntries = 0;
  v4 = Mem_AllocFn(6144, 4);
  v3->tPrivate.papxElement = v4;
  result = 0;
  memset(v4, 0, 0x1800u);
  do
  {
    *(_DWORD *)((char *)v3->tPrivate.papxElement + result) = (char *)v3->tPrivate.papxElement + result + 4;
    *(_DWORD *)((char *)v3->tPrivate.papxElement + result + 8) = (char *)v3->tPrivate.papxElement + result;
    *(_DWORD *)((char *)v3->tPrivate.papxElement + result + 4) = 0;
    *(_DWORD *)((char *)v3->tPrivate.papxElement + result + 12) = (char *)v3->tPrivate.papxElement + result + 16;
    *(_DWORD *)((char *)v3->tPrivate.papxElement + result + 20) = (char *)v3->tPrivate.papxElement + result + 12;
    *(_DWORD *)((char *)v3->tPrivate.papxElement + result + 16) = 0;
    *(_DWORD *)((char *)v3->tPrivate.papxElement + result + 24) = (char *)v3->tPrivate.papxElement + result + 28;
    *(_DWORD *)((char *)v3->tPrivate.papxElement + result + 32) = (char *)v3->tPrivate.papxElement + result + 24;
    *(_DWORD *)((char *)v3->tPrivate.papxElement + result + 28) = 0;
    *(_DWORD *)((char *)v3->tPrivate.papxElement + result + 36) = (char *)v3->tPrivate.papxElement + result + 40;
    *(_DWORD *)((char *)v3->tPrivate.papxElement + result + 44) = (char *)v3->tPrivate.papxElement + result + 36;
    *(_DWORD *)((char *)v3->tPrivate.papxElement + result + 40) = 0;
    *(_DWORD *)((char *)v3->tPrivate.papxElement + result + 48) = (char *)v3->tPrivate.papxElement + result + 52;
    *(_DWORD *)((char *)v3->tPrivate.papxElement + result + 56) = (char *)v3->tPrivate.papxElement + result + 48;
    *(_DWORD *)((char *)v3->tPrivate.papxElement + result + 52) = 0;
    *(_DWORD *)((char *)v3->tPrivate.papxElement + result + 60) = (char *)v3->tPrivate.papxElement + result + 64;
    *(_DWORD *)((char *)v3->tPrivate.papxElement + result + 68) = (char *)v3->tPrivate.papxElement + result + 60;
    *(_DWORD *)((char *)v3->tPrivate.papxElement + result + 64) = 0;
    *(_DWORD *)((char *)v3->tPrivate.papxElement + result + 72) = (char *)v3->tPrivate.papxElement + result + 76;
    *(_DWORD *)((char *)v3->tPrivate.papxElement + result + 80) = (char *)v3->tPrivate.papxElement + result + 72;
    *(_DWORD *)((char *)v3->tPrivate.papxElement + result + 76) = 0;
    *(_DWORD *)((char *)v3->tPrivate.papxElement + result + 84) = (char *)v3->tPrivate.papxElement + result + 88;
    *(_DWORD *)((char *)v3->tPrivate.papxElement + result + 92) = (char *)v3->tPrivate.papxElement + result + 84;
    *(_DWORD *)((char *)v3->tPrivate.papxElement + result + 88) = 0;
    result += 96;
  }
  while ( (unsigned int)result < 0x1800 );
  *p_ptMissionStatsHashTable = v3;
  return result;
}

// source: j/0/config.c:663  [anchor-callee]
void __cdecl Config_FreeAllPlayerProfileResources()
{
  struct QHashTable_s **p_ptMissionStatsHashTable; // ebp
  struct QHashTable_s *v1; // eax
  struct QHashTable_s *v2; // ebx
  int v3; // esi
  int i; // [esp+0h] [ebp-4h]

  i = 0;
  if ( Config_tConfig.nPlayerProfiles > 0 )
  {
    p_ptMissionStatsHashTable = &Config_tConfig.atPlayerProfile[0].ptMissionStatsHashTable;
    do
    {
      v1 = *p_ptMissionStatsHashTable;
      if ( *p_ptMissionStatsHashTable )
      {
        if ( v1->tPrivate.nEntries )
          v1->tPrivate.pfMap(
            v1,
            (void (__cdecl *)(struct QHashTable_s *, void *, void *, void *))Config_FreeMissionStatsEntry,
            nullptr);
        v2 = *p_ptMissionStatsHashTable;
        QHashTable_DeAlloc(*p_ptMissionStatsHashTable);
        if ( v2 )
        {
          v3 = *(_DWORD *)((unsigned int)&v2[-1].tPrivate.pfMap & 0xFFFFFFFC);
          --Mem_nCurrentAllocations;
          Node_Remove((_DWORD **)v3);
          memset(*(void **)(v3 + 8), 0xCDu, *(_DWORD *)(v3 + 16));
          free((void *)v3);
        }
        *p_ptMissionStatsHashTable = nullptr;
      }
      p_ptMissionStatsHashTable += 688;
      ++i;
    }
    while ( i < Config_tConfig.nPlayerProfiles );
  }
}

// source: j/0/config.c:682  [size]
struct GraphicOptions_s *__cdecl Config_GetActiveGraphicOptions()
{
  return (struct GraphicOptions_s *)(2752 * Config_tConfig.iActiveProfile + 7392084);
}

// source: j/0/config.c:698  [size]
struct SoundOptions_t *__cdecl Config_GetActiveSoundOptions()
{
  return (struct SoundOptions_t *)(2752 * Config_tConfig.iActiveProfile + 7392688);
}

// source: j/0/config.c:713  [anchor-mhash]
struct Result_s *__cdecl Config_GameOptionsIsHideInventory(
        struct Result_s *retstr,
        void *pxUnused,
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
  *((_BYTE *)&Config_atDisplayDevice[4].tDisplayModeList[34].nWidth + 2752 * Config_tConfig.nPlayerProfiles) = v4 != nullptr;
  Rs.nResult = 0;
  Rs.vResult = 0.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/config.c:727  [anchor-strings]
int __cdecl Config_SavePlayerGame(struct File_s *ptFile, int iPlayer)
{
  int v2; // esi
  int v3; // edi
  int v4; // edi
  char *v5; // eax
  int v6; // edi
  char *v7; // eax
  int v8; // eax
  char zBuffer[256]; // [esp+8h] [ebp-100h] BYREF

  v2 = iPlayer;
  v3 = sprintf(
         zBuffer,
         &g_zFileName.atPictureResources[22].zResourceFilename[20],
         Config_zGameOptionsGameLanguage,
         16 * Config_tConfig.atPlayerProfile[iPlayer].tGameOptions.eLanguage + 6828784);
  v4 = sprintf(
         &zBuffer[v3],
         &g_zFileName.atPictureResources[22].zResourceFilename[20],
         Config_zGameOptionsGameDifficultyLevel,
         16 * Config_tConfig.atPlayerProfile[v2].tGameOptions.eDifficultyLevel + 6828880)
     + v3;
  v5 = "TRUE";
  if ( !Config_tConfig.atPlayerProfile[v2].tGameOptions.isBlood )
    v5 = "FALSE";
  v6 = sprintf(
         &zBuffer[v4],
         &g_zFileName.atPictureResources[22].zResourceFilename[20],
         Config_zGameOptionsGameBlood,
         v5)
     + v4;
  v7 = "TRUE";
  if ( !Config_tConfig.atPlayerProfile[v2].tGameOptions.isHideInventory )
    v7 = "FALSE";
  v8 = sprintf(
         &zBuffer[v6],
         &g_zFileName.atPictureResources[22].zResourceFilename[20],
         Config_zGameOptionsGameIsHideInventory,
         v7);
  return File_atDevice[ptFile->eDeviceID].pfWrite(ptFile->eDeviceID, ptFile, zBuffer, v8 + v6);
}

// source: j/0/config.c:774  [anchor-strings]
int __cdecl Config_SavePlayerSound(struct File_s *ptFile, int iPlayer)
{
  int v2; // esi
  int v3; // edi
  int v4; // eax
  int v5; // edi
  int v6; // edi
  int v7; // eax
  char Buffer[2048]; // [esp+10h] [ebp-800h] BYREF

  v2 = iPlayer;
  v3 = sprintf(
         Buffer,
         &g_zFileName.atPictureResources[22].zResourceFilename[4],
         Config_zGameOptionsSoundSpeech,
         Config_tConfig.atPlayerProfile[iPlayer].tSoundOptions.isSpeech,
         Config_tConfig.atPlayerProfile[iPlayer].tSoundOptions.vSpeechVolume);
  v4 = sprintf(
         &Buffer[v3],
         &g_zFileName.atPictureResources[22].zResourceFilename[4],
         Config_zGameOptionsSoundMusic,
         Config_tConfig.atPlayerProfile[v2].tSoundOptions.isMusic,
         *(float *)(v2 * 2752 + 7392692));
  v5 = sprintf(
         &Buffer[v4 + v3],
         &g_zFileName.atPictureResources[22].zResourceFilename[4],
         Config_zGameOptionsSoundFX,
         Config_tConfig.atPlayerProfile[v2].tSoundOptions.isSoundEffects,
         *(float *)(v2 * 2752 + 7392688))
     + v4
     + v3;
  v6 = sprintf(
         &Buffer[v5],
         &g_zFileName.atPictureResources[21].zResourceFilename[60],
         Config_zGameOptions3DProvider,
         Config_tConfig.atPlayerProfile[v2].tSoundOptions.i3DSoundProvider)
     + v5;
  v7 = sprintf(
         &Buffer[v6],
         &g_zFileName.atPictureResources[21].zResourceFilename[60],
         off_6BA0C4,
         *((_DWORD *)&Config_tConfig.atPlayerProfile[v2].tSoundOptions + 5));
  return File_atDevice[ptFile->eDeviceID].pfWrite(ptFile->eDeviceID, ptFile, Buffer, v7 + v6);
}

// source: j/0/config.c:823  [anchor-strings]
struct File_s *__cdecl Config_SavePlayerGraphic(struct File_s *ptFile, int iPlayer)
{
  int v2; // edi
  int v4; // ebx
  int v5; // ebx
  int v6; // ebx
  int v7; // ebx
  int v8; // ebx
  int v9; // eax
  char zBuffer[2048]; // [esp+28h] [ebp-800h] BYREF

  v2 = 2752 * iPlayer;
  v4 = sprintf(
         zBuffer,
         &g_zFileName.atPictureResources[21].zResourceFilename[40],
         Config_zGameOptionsGraphicDisplay,
         Config_tConfig.atPlayerProfile[iPlayer].tGraphicOptions.nDisplayWidth,
         Config_tConfig.atPlayerProfile[iPlayer].tGraphicOptions.nDisplayHeight,
         Config_tConfig.atPlayerProfile[iPlayer].tGraphicOptions.nDisplayDepth);
  v5 = sprintf(
         &zBuffer[v4],
         &g_zFileName.atPictureResources[21].zResourceFilename[28],
         Config_zGameOptionsGraphicDevice,
         Config_tConfig.atPlayerProfile[v2 / 0xAC0u].tGraphicOptions.zDeviceIdentifier)
     + v4;
  v6 = sprintf(
         &zBuffer[v5],
         &g_zFileName.atPictureResources[21].zResourceFilename[16],
         Config_zGameOptionsGraphicGamma,
         *(float *)(v2 + 7392672))
     + v5;
  v7 = sprintf(
         &zBuffer[v6],
         &g_zFileName.atPictureResources[21].zResourceFilename[16],
         Config_zGameOptionsGraphicCrossHairAlpha,
         *(float *)(v2 + 7392676))
     + v6;
  v8 = sprintf(
         &zBuffer[v7],
         &g_zFileName.atPictureResources[21].zResourceFilename[16],
         Config_zGameOptionsGraphicCrossHairThickness,
         *(float *)(v2 + 7392656))
     + v7;
  v9 = sprintf(
         &zBuffer[v8],
         (char *const)&g_zFileName.atPictureResources[20].ptPicture,
         Config_zGameOptionsGraphicCrossHairColour,
         *(float *)(v2 + 7392660),
         *(float *)(v2 + 7392664),
         *(float *)(v2 + 7392668));
  File_atDevice[ptFile->eDeviceID].pfWrite(ptFile->eDeviceID, ptFile, zBuffer, v9 + v8);
  File_printf(ptFile, &g_zFileName.atPictureResources[22].zResourceFilename[20]);
  return (struct File_s *)GfxOptions_WriteGraphicOptions(ptFile, &Config_tConfig.atPlayerProfile[v2 / 0xAC0u]);
}

// source: j/0/config.c:890  [anchor-strings]
int __cdecl Config_SavePlayerInput(struct File_s *ptFile, int iPlayer)
{
  #pragma pack(push, 1)
  union
  {
    struct { int v17; };
    struct { char igi2_o1[4]; int v18; };
    struct { char igi2_o2[12]; char Buffer[256]; };
    char igi2_extent[268];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v3; // edi
  unsigned int v4; // eax
  unsigned int v5; // eax
  int result; // eax
  struct InputOptions_s *v7; // esi
  int v8; // ebx
  int v9; // ecx
  unsigned __int64 *p_bInputButton; // eax
  int v11; // edi
  int v12; // ecx
  enum InputPortDevice_e *p_eInputPortDevice; // eax
  int v14; // edx
  int *v15; // ecx
  unsigned int v16; // ebx

  v3 = 2752 * iPlayer;
  igi2_frame.v17 = 2752 * iPlayer;
  v4 = sprintf(
         igi2_frame.Buffer,
         &g_zFileName.atPictureResources[21].zResourceFilename[60],
         Config_zGameOptionsInputInvertMouse,
         Config_tConfig.atPlayerProfile[iPlayer].tInputOptions.isInvertMouse);
  File_atDevice[ptFile->eDeviceID].pfWrite(ptFile->eDeviceID, ptFile, igi2_frame.Buffer, v4);
  v5 = sprintf(
         igi2_frame.Buffer,
         &g_zFileName.atPictureResources[21].zResourceFilename[16],
         Config_zGameOptionsInputMouseSentivity,
         *(float *)(v3 + 7394768));
  File_atDevice[ptFile->eDeviceID].pfWrite(ptFile->eDeviceID, ptFile, igi2_frame.Buffer, v5);
  result = *(_DWORD *)((char *)&Config_tConfig.atPlayerProfile[0].tInputOptions.atRemapButtonTable[128].bInputButton + v3);
  igi2_frame.v18 = 0;
  if ( result > 0 )
  {
    v7 = (struct InputOptions_s *)((char *)&Config_tConfig.atPlayerProfile[0].tInputOptions + v3);
    do
    {
      if ( v7->atRemapButtonTable[0].bInputButton )
      {
        v8 = sprintf(
               igi2_frame.Buffer,
               &g_zFileName.atPictureResources[20].zResourceFilename[60],
               Config_zGameOptionsInputRemapButton);
        v9 = 0;
        p_bInputButton = &Config_atInputButton[0].bInputButton;
        while ( *(_DWORD *)p_bInputButton != LODWORD(v7->atRemapButtonTable[0].bInputButton)
             || *((_DWORD *)p_bInputButton + 1) != HIDWORD(v7->atRemapButtonTable[0].bInputButton) )
        {
          p_bInputButton += 5;
          ++v9;
          if ( (int)p_bInputButton >= 7055688 )
            goto LABEL_8;
        }
        if ( v9 >= 53 )
        {
LABEL_8:
          v11 = 1;
          goto LABEL_9;
        }
        v11 = 0;
        v8 += sprintf(&igi2_frame.Buffer[v8], &g_zFileName.atPictureResources[20].zResourceFilename[56], 40 * v9 + 7053536);
LABEL_9:
        v12 = 0;
        p_eInputPortDevice = &Config_atInputPortDevice[0].eInputPortDevice;
        while ( *p_eInputPortDevice != v7->atRemapButtonTable[0].eInputPortDevice )
        {
          p_eInputPortDevice += 9;
          ++v12;
          if ( (int)p_eInputPortDevice >= 7057124 )
            goto LABEL_12;
        }
        if ( v12 >= 3 )
        {
LABEL_12:
          v11 = 1;
          goto LABEL_13;
        }
        v8 += sprintf(&igi2_frame.Buffer[v8], &g_zFileName.atPictureResources[20].zResourceFilename[56], 36 * v12 + 7056984);
LABEL_13:
        v14 = 0;
        v15 = &dword_6BAEE8;
        while ( *v15 != (v7->atRemapButtonTable[0].nDeviceSource | (v7->atRemapButtonTable[0].eInputPortDevice << 30)) )
        {
          v15 += 9;
          ++v14;
          if ( (int)v15 >= 7061196 )
            goto LABEL_24;
        }
        if ( v14 < 113 )
        {
          v16 = sprintf(&igi2_frame.Buffer[v8], &g_zFileName.atPictureResources[20].zResourceFilename[48], 36 * v14 + 7057096) + v8;
          if ( !v11 )
            File_atDevice[ptFile->eDeviceID].pfWrite(ptFile->eDeviceID, ptFile, igi2_frame.Buffer, v16);
        }
LABEL_24:
        v3 = igi2_frame.v17;
      }
      result = igi2_frame.v18 + 1;
      v7 = (struct InputOptions_s *)((char *)v7 + 16);
      ++igi2_frame.v18;
    }
    while ( igi2_frame.v18 < *(_DWORD *)((char *)&Config_tConfig.atPlayerProfile[0].tInputOptions.atRemapButtonTable[128].bInputButton
                            + v3) );
  }
  return result;
}

// source: j/0/config.c:1043  [anchor-strings]
void __cdecl Config_WritePlayerMissionDataCallback(
        struct QHashTable_s *ptHashTable,
        char *zKey,
        struct ConfigMissionStats_s *ptConfigMissionStats,
        struct File_s *ptFile)
{
  struct MissionRankRequirement_s *atMissionRankRequirement; // edi
  int v5; // ebx
  int v6; // [esp+14h] [ebp-4h]

  File_printf(ptFile, &g_zFileName.atPictureResources[20].zResourceFilename[4]);
  atMissionRankRequirement = ptConfigMissionStats->tMissionScoreSettings.atMissionRankRequirement;
  v6 = 3;
  do
  {
    v5 = 5;
    do
    {
      File_printf(ptFile, (char *)&g_zFileName.atPictureResources[19].ptPicture);
      atMissionRankRequirement = (struct MissionRankRequirement_s *)((char *)atMissionRankRequirement + 4);
      --v5;
    }
    while ( v5 );
    --v6;
  }
  while ( v6 );
  File_printf(ptFile, &g_zFileName.atPictureResources[19].zResourceFilename[56]);
}

// source: j/0/config.c:1081  [anchor-refs]
struct Result_s *__cdecl Config_ParsePlayerMissionData(
        struct Result_s *retstr,
        void *pxUnused,
        struct ArgList_s *ptArgList)
{
  #pragma pack(push, 1)
  union
  {
    struct { float *v10; };
    struct { char igi2_o1[4]; float pxData; };
    struct { char igi2_o2[8]; int v12; };
    struct { char igi2_o3[12]; int v13; };
    struct { char igi2_o4[16]; struct PlayerProfile_s *ptPlayerProfile; };
    struct { char igi2_o5[20]; struct Result_s Rs; };
    char igi2_extent[44];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  _DWORD *v3; // esi
  int v4; // ebx
  float *v5; // eax
  double v6; // st7
  struct QHashTable_s *ptMissionStatsHashTable; // edi
  int v8; // eax

  if ( ptArgList->nArguments == 25 )
  {
    igi2_frame.ptPlayerProfile = (struct PlayerProfile_s *)(&Config_atDisplayDevice[4].tDisplayModeList[33].nHeight
                                               + 688 * Config_tConfig.nPlayerProfiles);
    v3 = Mem_AllocFn(140, 4);
    v3[1] = Script_EvalArgInt(ptArgList, 0);
    *v3 = Script_EvalArgInt(ptArgList, 1);
    v3[6] = Script_EvalArgInt(ptArgList, 2);
    v3[9] = Script_EvalArgInt(ptArgList, 3);
    v3[5] = Script_EvalArgInt(ptArgList, 4);
    v3[4] = Script_EvalArgInt(ptArgList, 5);
    v3[3] = Script_EvalArgInt(ptArgList, 6);
    v3[2] = Script_EvalArgInt(ptArgList, 7);
    v3[7] = Script_EvalArgInt(ptArgList, 8);
    v3[8] = Script_EvalArgInt(ptArgList, 9);
    v4 = 10;
    v5 = (float *)(v3 + 20);
    igi2_frame.v13 = 3;
    do
    {
      igi2_frame.v10 = v5;
      igi2_frame.v12 = 5;
      do
      {
        if ( ptArgList->isQVM )
        {
          igi2_frame.pxData = 0.0;
          QVM_EvalArg(&igi2_frame.pxData, 4, ptArgList, v4, 2);
          v6 = igi2_frame.pxData;
        }
        else
        {
          v6 = Expression_EvalFloat(ptArgList->aptExpression[v4]);
        }
        *igi2_frame.v10++ = v6;
        ++v4;
        --igi2_frame.v12;
      }
      while ( igi2_frame.v12 );
      v5 = igi2_frame.v10;
      --igi2_frame.v13;
    }
    while ( igi2_frame.v13 );
    sprintf(byte_70CB00, &g_zFileName.atPictureResources[22].zResourceFilename[32], v3[1]);
    ptMissionStatsHashTable = igi2_frame.ptPlayerProfile->ptMissionStatsHashTable;
    v8 = ptMissionStatsHashTable->tPrivate.pfHashFunction(ptMissionStatsHashTable->tPrivate.nHashTableSize, byte_70CB00);
    ptMissionStatsHashTable->tPrivate.pfCreateElement(ptMissionStatsHashTable, v8, (const void *)(byte_70CB00), (const void *)(v3));
  }
  igi2_frame.Rs.nResult = 0;
  igi2_frame.Rs.vResult = 0.0;
  igi2_frame.Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &igi2_frame.Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/config.c:1133  [anchor-mhash]
int __cdecl Config_SavePlayerMissionData(struct File_s *ptFile, int iPlayer)
{
  int result; // eax

  result = (int)Config_tConfig.atPlayerProfile[iPlayer].ptMissionStatsHashTable;
  if ( *(_DWORD *)result )
    return (*(int (__cdecl **)(int, void (__cdecl *)(struct QHashTable_s *, char *, struct ConfigMissionStats_s *, struct File_s *), struct File_s *))(result + 36))(
             result,
             Config_WritePlayerMissionDataCallback,
             ptFile);
  return result;
}

// source: j/0/config.c:1147  [anchor-strings]
struct File_s *__cdecl Config_SavePlayerProfile(struct File_s *ptFile, int iPlayer)
{
  unsigned int v3; // eax
  int v4; // esi
  int *anActiveMission; // edi
  unsigned int v6; // eax
  struct File_s *result; // eax
  struct QHashTable_s *ptMissionStatsHashTable; // ebp
  char zBuffer[256]; // [esp+10h] [ebp-100h] BYREF

  v3 = sprintf(
         zBuffer,
         &g_zFileName.atPictureResources[21].zResourceFilename[28],
         Config_zGameOptionsPlayer,
         Config_tConfig.atPlayerProfile[iPlayer].zCallSign);
  File_atDevice[ptFile->eDeviceID].pfWrite(ptFile->eDeviceID, ptFile, zBuffer, v3);
  v4 = 0;
  anActiveMission = Config_tConfig.atPlayerProfile[iPlayer].anActiveMission;
  do
  {
    v6 = sprintf(
           zBuffer,
           &g_zFileName.atPictureResources[19].zResourceFilename[40],
           Config_zGameOptionsActiveMission,
           v4,
           *anActiveMission);
    File_atDevice[ptFile->eDeviceID].pfWrite(ptFile->eDeviceID, ptFile, zBuffer, v6);
    ++v4;
    ++anActiveMission;
  }
  while ( v4 < 3 );
  Config_SavePlayerInput(ptFile, iPlayer);
  Config_SavePlayerGraphic(ptFile, iPlayer);
  Config_SavePlayerGame(ptFile, iPlayer);
  result = (struct File_s *)Config_SavePlayerSound(ptFile, iPlayer);
  ptMissionStatsHashTable = Config_tConfig.atPlayerProfile[iPlayer].ptMissionStatsHashTable;
  if ( ptMissionStatsHashTable->tPrivate.nEntries )
    return ((struct File_s *(__cdecl *)(struct QHashTable_s *, void (__cdecl *)(struct QHashTable_s *, char *, struct ConfigMissionStats_s *, struct File_s *), struct File_s *))ptMissionStatsHashTable->tPrivate.pfMap)(
             ptMissionStatsHashTable,
             Config_WritePlayerMissionDataCallback,
             ptFile);
  return result;
}

// source: j/0/config.c:1189  [anchor-strings]
void __cdecl Config_DefaultGameOptions()
{
  int iActiveProfile; // eax
  struct InputOptions_s *p_tInputOptions; // edi
  struct Result_s v2; // [esp+Ch] [ebp-18h] BYREF

  strcpy(Config_tConfig.atPlayerProfile[0].zCallSign, "David Jones");
  Config_tConfig.atPlayerProfile[0].anActiveMission[0] = 0;
  Config_tConfig.atPlayerProfile[0].anActiveMission[1] = 0;
  Config_tConfig.nPlayerProfiles = 1;
  Config_tConfig.iActiveProfile = 0;
  Config_tConfig.atPlayerProfile[0].anActiveMission[2] = 0;
  Config_tConfig.atPlayerProfile[0].tGameOptions.eDifficultyLevel = GAMEDIFFICULTY_2;
  if ( !_stricmp(AppContext_tAppContext.zCountry, &g_zFileName.atPictureResources[19].zResourceFilename[24]) )
  {
    Config_tConfig.atPlayerProfile[0].tGameOptions.eLanguage = GAMELANGUAGE_GERMAN;
  }
  else if ( !_stricmp(AppContext_tAppContext.zCountry, &g_zFileName.atPictureResources[19].zResourceFilename[16]) )
  {
    Config_tConfig.atPlayerProfile[0].tGameOptions.eLanguage = GAMELANGUAGE_FRENCH;
  }
  else if ( !_stricmp(AppContext_tAppContext.zCountry, &g_zFileName.atPictureResources[19].zResourceFilename[8]) )
  {
    Config_tConfig.atPlayerProfile[0].tGameOptions.eLanguage = GAMELANGUAGE_SPANISH;
  }
  else if ( !_stricmp(AppContext_tAppContext.zCountry, g_zFileName.atPictureResources[19].zResourceFilename) )
  {
    Config_tConfig.atPlayerProfile[0].tGameOptions.eLanguage = GAMELANGUAGE_ITALIAN;
  }
  else
  {
    Config_tConfig.atPlayerProfile[0].tGameOptions.eLanguage = _stricmp(
                                                                 AppContext_tAppContext.zCountry,
                                                                 &g_zFileName.atPictureResources[18].zResourceFilename[60]) != 0
                                                             ? GAMELANGUAGE_ENGLISH
                                                             : GAMELANGUAGE_USA;
  }
  Config_tConfig.atPlayerProfile[0].tGameOptions.isBlood = 1;
  Config_ResetGraphicOptions(&v2, nullptr, nullptr);
  iActiveProfile = Config_tConfig.iActiveProfile;
  *((_DWORD *)&Config_tConfig.atPlayerProfile[0].tSoundOptions + 5) = 0;
  Config_tConfig.atPlayerProfile[0].tSoundOptions.isMusic = 1;
  Config_tConfig.atPlayerProfile[0].tSoundOptions.isReverseStereo = 0;
  Config_tConfig.atPlayerProfile[0].tSoundOptions.isSoundEffects = 1;
  Config_tConfig.atPlayerProfile[0].tSoundOptions.isSpeech = 1;
  Config_tConfig.atPlayerProfile[0].tSoundOptions.vMusicVolume = 0.800000011920929;
  Config_tConfig.atPlayerProfile[0].tSoundOptions.vSoundEffectsVolume = 1.0;
  Config_tConfig.atPlayerProfile[0].tSoundOptions.vSpeechVolume = 1.0;
  Config_tConfig.atPlayerProfile[0].tSoundOptions.i3DSoundProvider = provider_activeindex;
  p_tInputOptions = &Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tInputOptions;
  Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tInputOptions.nRemapButton = 83;
  qmemcpy(p_tInputOptions, Config_atDefaultRemapButtonTable, 0x530u);
  Config_tConfig.atPlayerProfile[iActiveProfile].tInputOptions.isInvertMouse = 1;
  Config_tConfig.atPlayerProfile[iActiveProfile].tInputOptions.vMouseSensitivity = 0.4000000059604645;
  Config_FreeAllPlayerProfileResources();
  Config_AllocatePlayerProfileResources(0);
}

// source: j/0/config.c:1447  [size]
void __cdecl Config_VerifyControlConfig()
{
  ;
}

// source: j/0/config.c:1508  [anchor-strings]
void __cdecl Config_VerifyGraphicConfig()
{
  struct GraphicOptions_s *p_tGraphicOptions; // edi
  int v1; // eax
  struct ConfigDisplayDevice_s *v2; // ebp
  char *zDesc; // eax
  char v4; // cl
  struct ConfigDisplayDevice_s *v5; // eax
  char v6; // cl
  int v7; // eax
  int nDisplayWidth; // ebp
  struct ConfigDisplayMode_s *tDisplayModeList; // esi
  int nNumDisplayModes; // eax
  struct ConfigDisplayMode_s *v11; // ebx
  int v12; // edi
  signed int v13; // ecx
  struct GraphicOptions_s *v14; // eax
  int nHeight; // edx
  int nDepth; // ecx
  struct GraphicOptions_s *v17; // [esp+0h] [ebp-14h]
  int v18; // [esp+4h] [ebp-10h]
  int v19; // [esp+8h] [ebp-Ch]
  int nDisplayDepth; // [esp+Ch] [ebp-8h]
  int nDisplayHeight; // [esp+10h] [ebp-4h]

  if ( AppContext_tAppContext.isMainMenu == false )
  {
    v19 = 0;
    if ( Config_tConfig.nPlayerProfiles > 0 )
    {
      p_tGraphicOptions = &Config_tConfig.atPlayerProfile[0].tGraphicOptions;
      v17 = &Config_tConfig.atPlayerProfile[0].tGraphicOptions;
      while ( 1 )
      {
        if ( !Config_nNumDisplayDevices )
        {
          LDebug_Error(&g_zFileName.atPictureResources[18].zResourceFilename[8]);
          abort();
        }
        v1 = 0;
        if ( Config_nNumDisplayDevices <= 0 )
        {
LABEL_10:
          zDesc = Config_atDisplayDevice[0].tDisplayDevice.zDesc;
          do
          {
            v4 = *zDesc;
            zDesc[(char *)p_tGraphicOptions - Config_atDisplayDevice[0].tDisplayDevice.zDesc + 316] = *zDesc;
            ++zDesc;
          }
          while ( v4 );
          v5 = Config_atDisplayDevice;
          do
          {
            v6 = v5->tDisplayDevice.zIdentifier[0];
            v5->tDisplayDevice.zIdentifier[(char *)p_tGraphicOptions - (char *)Config_atDisplayDevice + 60] = v5->tDisplayDevice.zIdentifier[0];
            v5 = (struct ConfigDisplayDevice_s *)((char *)v5 + 1);
          }
          while ( v6 );
          v1 = 0;
        }
        else
        {
          v2 = Config_atDisplayDevice;
          while ( strcmp(p_tGraphicOptions->zDeviceIdentifier, v2->tDisplayDevice.zIdentifier) )
          {
            ++v1;
            ++v2;
            if ( v1 >= Config_nNumDisplayDevices )
              goto LABEL_10;
          }
        }
        v7 = v1;
        nDisplayWidth = p_tGraphicOptions->nDisplayWidth;
        tDisplayModeList = Config_atDisplayDevice[v7].tDisplayModeList;
        nNumDisplayModes = Config_atDisplayDevice[v7].nNumDisplayModes;
        v11 = nullptr;
        nDisplayHeight = p_tGraphicOptions->nDisplayHeight;
        nDisplayDepth = p_tGraphicOptions->nDisplayDepth;
        v12 = 0x7FFFFFFF;
        if ( nNumDisplayModes <= 0 )
          goto LABEL_22;
        v18 = nNumDisplayModes;
        do
        {
          v13 = abs32(tDisplayModeList->nWidth - nDisplayWidth)
              + abs32(tDisplayModeList->nHeight - nDisplayHeight)
              + (abs32(tDisplayModeList->nDepth - nDisplayDepth) << 24);
          if ( v13 < v12 )
          {
            v11 = tDisplayModeList;
            v12 = v13;
          }
          ++tDisplayModeList;
          --v18;
        }
        while ( v18 );
        if ( v11 )
        {
          v14 = v17;
          nHeight = v11->nHeight;
          v17->nDisplayWidth = v11->nWidth;
          nDepth = v11->nDepth;
          v17->nDisplayHeight = nHeight;
          v17->nDisplayDepth = nDepth;
        }
        else
        {
LABEL_22:
          v14 = v17;
          v17->nDisplayWidth = 1024;
          v17->nDisplayHeight = 768;
          v17->nDisplayDepth = 32;
        }
        v17 = (struct GraphicOptions_s *)((char *)v14 + 2752);
        if ( ++v19 >= Config_tConfig.nPlayerProfiles )
          break;
        p_tGraphicOptions = (struct GraphicOptions_s *)((char *)v14 + 2752);
      }
    }
  }
}

// source: j/0/config.c:1611  [anchor-caller]
struct Result_s *__cdecl Config_GameOptionsStart(
        struct Result_s *retstr,
        void *pxUnUsed,
        struct ArgList_s *ptArgList)
{
  struct ArgList_s *v3; // edi
  struct ArgList_s *v4; // eax
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  Config_FreeAllPlayerProfileResources();
  v3 = ptArgList;
  Config_tConfig.nPlayerProfiles = 0;
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
  Config_tConfig.iActiveProfile = (int)v4;
  Rs.nResult = 0;
  Rs.vResult = 0.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/config.c:1629  [anchor-caller]
struct Result_s *__cdecl Config_GameOptionsPlayer(
        struct Result_s *retstr,
        void *pxUnUsed,
        struct ArgList_s *ptArgList)
{
  _BYTE *v3; // eax
  struct Result_s Rs; // [esp+Ch] [ebp-18h] BYREF

  ++Config_tConfig.nPlayerProfiles;
  dword_70CB08[688 * Config_tConfig.nPlayerProfiles] = 0;
  dword_70CB38[688 * Config_tConfig.nPlayerProfiles] = 0;
  dword_70CB3C[688 * Config_tConfig.nPlayerProfiles] = 0;
  *(&Config_tConfig.nPlayerProfiles + 688 * Config_tConfig.nPlayerProfiles) = 0;
  Config_AllocatePlayerProfileResources(Config_tConfig.nPlayerProfiles - 1);
  v3 = (char *)&unk_70CB18 + 2752 * Config_tConfig.nPlayerProfiles;
  if ( ptArgList->isQVM )
  {
    *v3 = 0;
    QVM_EvalArg(v3, 32, ptArgList, 0, 3);
  }
  else
  {
    Expression_EvalString(*ptArgList->aptExpression, (char *)&unk_70CB18 + 2752 * Config_tConfig.nPlayerProfiles, 32);
  }
  Rs.nResult = 0;
  Rs.vResult = 0.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/config.c:1658  [anchor-mhash]
struct Result_s *__cdecl Config_GameOptionsActiveMission(
        struct Result_s *retstr,
        void *pxUnUsed,
        struct ArgList_s *ptArgList)
{
  struct ArgList_s *v3; // edi
  struct ArgList_s *v4; // esi
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
  if ( (unsigned int)v4 <= 2 )
    dword_70CB38[(_DWORD)v4 + 688 * Config_tConfig.nPlayerProfiles] = Script_EvalArgInt(v3, 1);
  Rs.nResult = 0;
  Rs.vResult = 0.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/config.c:1683  [anchor-mhash]
unsigned int __cdecl Config_GetActionFromInputButton(unsigned __int64 bButton)
{
  unsigned int result; // eax
  unsigned int v2; // ecx

  result = 0;
  v2 = 0;
  while ( __PAIR64__(HIDWORD(Config_atInputButton[v2].bInputButton), Config_atInputButton[v2].bInputButton) != bButton )
  {
    ++v2;
    ++result;
    if ( v2 >= 53 )
      return 0;
  }
  return result;
}

// source: j/0/config.c:1709  [anchor-hash]
unsigned __int64 __cdecl Config_GetActionInputButton(unsigned int iAction)
{
  int v1; // eax
  int v2; // ecx
  unsigned __int64 result; // rax

  v2 = v1;
  LODWORD(result) = Config_atInputButton[v1].bInputButton;
  HIDWORD(result) = HIDWORD(Config_atInputButton[v2].bInputButton);
  return result;
}

// source: j/0/config.c:1726  [size]
char *__cdecl Config_GetActionName(unsigned int iAction)
{
  return (char *)(40 * iAction + 7053536);
}

// source: j/0/config.c:1741  [anchor-mhash]
struct Result_s *__cdecl Config_GameOptionsInputRemapButton(
        struct Result_s *retstr,
        void *pxUnUsed,
        struct ArgList_s *ptArgList)
{
  int *v3; // ebx
  struct ArgList_s *v4; // edi
  int v5; // esi
  struct ArgList_s *v6; // eax
  struct ArgList_s *v7; // eax
  struct ArgList_s *v8; // eax
  int v9; // edx
  bool v10; // zf
  struct ArgList_s *v11; // ebp
  struct ArgList_s *v12; // eax
  int v13; // eax
  unsigned int v14; // edx
  int *v15; // ecx
  _BYTE tRemapButton[24]; // [esp+10h] [ebp-18h] BYREF

  v3 = &dword_70CB08[688 * Config_tConfig.nPlayerProfiles];
  v4 = ptArgList;
  v5 = 16 * (172 * Config_tConfig.nPlayerProfiles + *v3 - 172) + 7392712;
  if ( ptArgList->isQVM )
  {
    ptArgList = nullptr;
    QVM_EvalArg(&ptArgList, 4, v4, 0, 1);
    v6 = ptArgList;
  }
  else
  {
    v6 = (struct ArgList_s *)Expression_EvalInt(*ptArgList->aptExpression);
  }
  if ( (int)v6 >= 0 )
  {
    if ( v4->isQVM )
    {
      ptArgList = nullptr;
      QVM_EvalArg(&ptArgList, 4, v4, 0, 1);
      v7 = ptArgList;
    }
    else
    {
      v7 = (struct ArgList_s *)Expression_EvalInt(*v4->aptExpression);
    }
    v8 = (struct ArgList_s *)(5 * (_DWORD)v7);
    v9 = *(_DWORD *)&Config_atInputButton[0].zButton[8 * (_DWORD)v8 + 36];
    v10 = v4->isQVM == 0;
    *(_DWORD *)tRemapButton = *(_DWORD *)&Config_atInputButton[0].zButton[8 * (_DWORD)v8 + 32];
    *(_DWORD *)&tRemapButton[4] = v9;
    if ( v10 )
    {
      v11 = (struct ArgList_s *)Expression_EvalInt(v4->aptExpression[1]);
    }
    else
    {
      ptArgList = nullptr;
      QVM_EvalArg(&ptArgList, 4, v4, 1, 1);
      v11 = ptArgList;
    }
    if ( v4->isQVM )
    {
      ptArgList = nullptr;
      QVM_EvalArg(&ptArgList, 4, v4, 2, 1);
      v12 = ptArgList;
    }
    else
    {
      v12 = (struct ArgList_s *)Expression_EvalInt(v4->aptExpression[2]);
    }
    v13 = (unsigned int)v12 & 0x3FFFFFFF;
    v14 = 0;
    if ( *v3 )
    {
      v15 = &Config_atDisplayDevice[4].tDisplayModeList[87].nDepth + 688 * Config_tConfig.nPlayerProfiles;
      while ( (struct ArgList_s *)*(v15 - 1) != v11 || *v15 != v13 )
      {
        ++v14;
        v15 += 4;
        if ( v14 >= *v3 )
          goto LABEL_20;
      }
    }
    else
    {
LABEL_20:
      *(_QWORD *)v5 = *(_QWORD *)tRemapButton;
      *(_DWORD *)(v5 + 8) = v11;
      *(_DWORD *)(v5 + 12) = v13;
      ++*v3;
    }
    *(_DWORD *)tRemapButton = 0;
  }
  else
  {
    *(_DWORD *)tRemapButton = 0;
  }
  *(_DWORD *)&tRemapButton[16] = &g_zInitialValue;
  *(_DWORD *)&tRemapButton[12] = 0;
  *(_DWORD *)&tRemapButton[8] = 0;
  qmemcpy(retstr, tRemapButton, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/config.c:1783  [size]
struct Result_s *__cdecl Config_GameOptionsInputInvertMouse(
        struct Result_s *retstr,
        void *pxUnUsed,
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
  dword_70CB0C[688 * Config_tConfig.nPlayerProfiles] = (int)v4;
  Rs.nResult = 0;
  Rs.vResult = 0.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/config.c:1801  [size]
struct Result_s *__cdecl Config_GameOptionsInputMouseSensitivity(
        struct Result_s *retstr,
        void *pxUnUsed,
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
  *((float *)&unk_70CB10 + 688 * Config_tConfig.nPlayerProfiles) = v4;
  Rs.nResult = 0;
  Rs.vResult = 0.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/config.c:1820  [anchor-mhash]
struct Result_s *__cdecl Config_GameOptionsGraphicDisplay(
        struct Result_s *retstr,
        void *pxUnUsed,
        struct ArgList_s *ptArgList)
{
  struct ArgList_s *v3; // edi
  struct ArgList_s *v4; // eax
  struct ArgList_s *v5; // eax
  struct ArgList_s *v6; // eax
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  v3 = ptArgList;
  if ( AppContext_tAppContext.isMainMenu )
  {
    *(&Config_atDisplayDevice[4].tDisplayModeList[38].nWidth + 688 * Config_tConfig.nPlayerProfiles) = 640;
    *(&Config_atDisplayDevice[4].tDisplayModeList[38].nHeight + 688 * Config_tConfig.nPlayerProfiles) = 480;
  }
  else
  {
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
    *(&Config_atDisplayDevice[4].tDisplayModeList[38].nWidth + 688 * Config_tConfig.nPlayerProfiles) = (int)v4;
    if ( v3->isQVM )
    {
      ptArgList = nullptr;
      QVM_EvalArg(&ptArgList, 4, v3, 1, 1);
      v5 = ptArgList;
    }
    else
    {
      v5 = (struct ArgList_s *)Expression_EvalInt(v3->aptExpression[1]);
    }
    *(&Config_atDisplayDevice[4].tDisplayModeList[38].nHeight + 688 * Config_tConfig.nPlayerProfiles) = (int)v5;
  }
  if ( v3->isQVM )
  {
    ptArgList = nullptr;
    QVM_EvalArg(&ptArgList, 4, v3, 2, 1);
    v6 = ptArgList;
  }
  else
  {
    v6 = (struct ArgList_s *)Expression_EvalInt(v3->aptExpression[2]);
  }
  *(&Config_atDisplayDevice[4].tDisplayModeList[38].nDepth + 688 * Config_tConfig.nPlayerProfiles) = (int)v6;
  Rs.nResult = 0;
  Rs.vResult = 0.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/config.c:1848  [size~]
struct Result_s *__cdecl Config_GameOptionsGameLanguage(
        struct Result_s *retstr,
        void *pxUnUsed,
        struct ArgList_s *ptArgList)
{
  struct ArgList_s *v3; // edi
  struct ArgList_s *v4; // eax
  _DWORD v6[6]; // [esp+8h] [ebp-18h] BYREF

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
  *(&Config_atDisplayDevice[4].tDisplayModeList[33].nDepth + 688 * Config_tConfig.nPlayerProfiles) = (int)v4;
  v6[0] = 0;
  v6[2] = 0;
  v6[3] = 0;
  v6[4] = &g_zInitialValue;
  qmemcpy(retstr, v6, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/config.c:1881  [size]
struct Result_s *__cdecl Config_GameOptionsCrosshairThickness(
        struct Result_s *retstr,
        void *pxUnused,
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
  *((float *)&Config_atDisplayDevice[4].tDisplayModeList[82].nWidth + 688 * Config_tConfig.nPlayerProfiles) = v4;
  Rs.nResult = 0;
  Rs.vResult = 0.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/config.c:1895  [anchor-mhash]
struct Result_s *__cdecl Config_GameOptionsCrosshairColour(
        struct Result_s *retstr,
        void *pxUnused,
        struct ArgList_s *ptArgList)
{
  #pragma pack(push, 1)
  union
  {
    struct { float pxData; };
    struct { char igi2_o1[4]; struct Result_s Rs; };
    char igi2_extent[28];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  double v3; // st7
  double v4; // st7
  double v5; // st7

  if ( ptArgList->isQVM )
  {
    igi2_frame.pxData = 0.0;
    QVM_EvalArg(&igi2_frame.pxData, 4, ptArgList, 0, 2);
    v3 = igi2_frame.pxData;
  }
  else
  {
    v3 = Expression_EvalFloat(*ptArgList->aptExpression);
  }
  *((float *)&Config_atDisplayDevice[4].tDisplayModeList[82].nHeight + 688 * Config_tConfig.nPlayerProfiles) = v3;
  if ( ptArgList->isQVM )
  {
    igi2_frame.pxData = 0.0;
    QVM_EvalArg(&igi2_frame.pxData, 4, ptArgList, 1, 2);
    v4 = igi2_frame.pxData;
  }
  else
  {
    v4 = Expression_EvalFloat((struct QExpression_s *)*((_DWORD *)ptArgList->aptExpression + 1));
  }
  *((float *)&Config_atDisplayDevice[4].tDisplayModeList[82].nDepth + 688 * Config_tConfig.nPlayerProfiles) = v4;
  if ( ptArgList->isQVM )
  {
    igi2_frame.pxData = 0.0;
    QVM_EvalArg(&igi2_frame.pxData, 4, ptArgList, 2, 2);
    v5 = igi2_frame.pxData;
  }
  else
  {
    v5 = Expression_EvalFloat((struct QExpression_s *)*((_DWORD *)ptArgList->aptExpression + 2));
  }
  *((float *)&Config_atDisplayDevice[4].tDisplayModeList[83].nWidth + 688 * Config_tConfig.nPlayerProfiles) = v5;
  igi2_frame.Rs.nResult = 0;
  igi2_frame.Rs.vResult = 0.0;
  igi2_frame.Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &igi2_frame.Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/config.c:1911  [size]
struct Result_s *__cdecl Config_GameOptionsGameDifficultyLevel(
        struct Result_s *retstr,
        void *pxUnUsed,
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
  *(&Config_atDisplayDevice[4].tDisplayModeList[33].nHeight + 688 * Config_tConfig.nPlayerProfiles) = (int)v4;
  Rs.nResult = 0;
  Rs.vResult = 0.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/config.c:1929  [size]
struct Result_s *__cdecl Config_GameOptionsContentControlPW(
        struct Result_s *retstr,
        void *pxUnUsed,
        struct ArgList_s *ptArgList)
{
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  if ( ptArgList->isQVM )
  {
    Config_tConfig.zContentControlPassword[0] = 0;
    QVM_EvalArg(Config_tConfig.zContentControlPassword, 32, ptArgList, 0, 3);
  }
  else
  {
    Expression_EvalString(*ptArgList->aptExpression, Config_tConfig.zContentControlPassword, 32);
  }
  Rs.nResult = 0;
  Rs.vResult = 0.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/config.c:1952  [size~]
struct Result_s *__cdecl Config_IsGermany(
        struct Result_s *retstr,
        void *pxUnused,
        struct ArgList_s *ptArgList)
{
  _DWORD v4[6]; // [esp+8h] [ebp-18h] BYREF

  v4[0] = 0;
  v4[2] = 0;
  v4[3] = 0;
  v4[4] = &g_zInitialValue;
  qmemcpy(retstr, v4, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/config.c:1965  [anchor-callee]
struct Result_s *__cdecl Config_ResetGraphicOptions(
        struct Result_s *retstr,
        void *pxUnused,
        struct ArgList_s *ptArgList)
{
  enum bool isMainMenu; // eax
  struct GfxOptions_s *v4; // edi
  int v5; // esi
  _DWORD v7[6]; // [esp+Ch] [ebp-18h] BYREF

  Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGraphicOptions.isLensflares = 1;
  Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGraphicOptions.isParticles = 1;
  Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGraphicOptions.isTransparency = 1;
  isMainMenu = AppContext_tAppContext.isMainMenu;
  Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGraphicOptions.nDisplayDepth = 32;
  if ( isMainMenu )
  {
    Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGraphicOptions.nDisplayWidth = 640;
    Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGraphicOptions.nDisplayHeight = 480;
  }
  else
  {
    Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGraphicOptions.nDisplayWidth = 1024;
    Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGraphicOptions.nDisplayHeight = 768;
  }
  Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGraphicOptions.zDevice[0] = 0;
  Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGraphicOptions.zDeviceIdentifier[0] = 0;
  Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGraphicOptions.vGamma = 0.0;
  Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGraphicOptions.vCrossHairAlpha = 1.0;
  Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGraphicOptions.vCrossHairThickness = 1.0;
  Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGraphicOptions.vCrossHairR = 1.0;
  Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGraphicOptions.vCrossHairG = 0.25;
  Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGraphicOptions.vCrossHairB = 0.0;
  Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGraphicOptions.eTextureFilteringMode = 1;
  Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGraphicOptions.eAntialiasingMode = 0;
  v4 = (struct GfxOptions_s *)(2752 * Config_tConfig.iActiveProfile + 7392088);
  Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGraphicOptions.eDetailLevel = GFXOPTIONS_DETAIL_HIGH;
  qmemcpy(v4, &GfxOptions_atDefaultOptions[3], sizeof(struct GfxOptions_s));
  Config_SetGamma(Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGraphicOptions.vGamma);
  v5 = 2752 * Config_tConfig.iActiveProfile + 7392072;
  *(_BYTE *)(v5 + 68) = Direct3D_IsSoftwareVertexShadersByDefault();
  v7[0] = 0;
  v7[2] = 0;
  v7[3] = 0;
  v7[4] = &g_zInitialValue;
  qmemcpy(retstr, v7, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/config.c:2007  [anchor-strings]
void __cdecl Config_SaveContentControlPW(struct File_s *ptFile)
{
  unsigned int v1; // eax
  char zBuffer[256]; // [esp+0h] [ebp-100h] BYREF

  v1 = sprintf(
         zBuffer,
         &g_zFileName.atPictureResources[21].zResourceFilename[28],
         Config_zGameOptionsContentControlPW,
         Config_tConfig.zContentControlPassword);
  File_atDevice[ptFile->eDeviceID].pfWrite(ptFile->eDeviceID, ptFile, zBuffer, v1);
}

// source: j/0/config.c:2033  [size]
struct Result_s *__cdecl Config_SetContentControlPassword(
        struct Result_s *retstr,
        void *pxUnUsed,
        struct ArgList_s *ptArgList)
{
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  if ( ptArgList->isQVM )
  {
    Config_tConfig.zContentControlPassword[0] = 0;
    QVM_EvalArg(Config_tConfig.zContentControlPassword, 32, ptArgList, 0, 3);
  }
  else
  {
    Expression_EvalString(*ptArgList->aptExpression, Config_tConfig.zContentControlPassword, 32);
  }
  Rs.nResult = 0;
  Rs.vResult = 0.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/config.c:2052  [size]
struct Result_s *__cdecl Config_GetContentControlPassword(
        struct Result_s *retstr,
        void *pxUnUsed,
        struct ArgList_s *ptArgList)
{
  char *zContentControlPassword; // eax
  int v4; // edx
  char v5; // cl
  struct Result_s Rs; // [esp+0h] [ebp-18h] BYREF

  zContentControlPassword = Config_tConfig.zContentControlPassword;
  v4 = InputBox_ptActiveInputBox->zInputString - Config_tConfig.zContentControlPassword;
  do
  {
    v5 = *zContentControlPassword;
    zContentControlPassword[v4] = *zContentControlPassword;
    ++zContentControlPassword;
  }
  while ( v5 );
  Rs.nResult = 0;
  Rs.vResult = 0.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/config.c:2071  [anchor-mhash]
struct Result_s *__cdecl Config_VerifyContentControlPassword(
        struct Result_s *retstr,
        void *pxUnUsed,
        struct ArgList_s *ptArgList)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct Result_s Rs; };
    struct { char igi2_o1[24]; char zPassword[32]; };
    char igi2_extent[56];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)

  if ( ptArgList->isQVM )
  {
    igi2_frame.zPassword[0] = 0;
    QVM_EvalArg(igi2_frame.zPassword, 32, ptArgList, 0, 3);
  }
  else
  {
    Expression_EvalString(*ptArgList->aptExpression, igi2_frame.zPassword, 32);
  }
  igi2_frame.Rs.nResult = strcmp(igi2_frame.zPassword, Config_tConfig.zContentControlPassword) == 0;
  igi2_frame.Rs.zResult = (char *)&g_zInitialValue;
  igi2_frame.Rs.vResult = (double)(strcmp(igi2_frame.zPassword, Config_tConfig.zContentControlPassword) == 0);
  qmemcpy(retstr, &igi2_frame.Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/config.c:2093  [anchor-mhash]
struct Result_s *__cdecl Config_IsContentControlPasswordEnabled(
        struct Result_s *retstr,
        void *pxUnUsed,
        struct ArgList_s *ptArgList)
{
  unsigned int v3; // kr00_4
  struct Result_s Rs; // [esp+4h] [ebp-18h] BYREF

  Rs.nResult = strlen(Config_tConfig.zContentControlPassword);
  v3 = strlen(Config_tConfig.zContentControlPassword);
  Rs.vResult = (double)v3;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/config.c:2108  [size]
struct Result_s *__cdecl Config_GameOptionsGameBlood(
        struct Result_s *retstr,
        void *pxUnUsed,
        struct ArgList_s *ptArgList)
{
  struct ArgList_s *v3; // edi
  char v4; // al
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  v3 = ptArgList;
  if ( ptArgList->isQVM )
  {
    ptArgList = nullptr;
    QVM_EvalArg(&ptArgList, 4, v3, 0, 1);
    v4 = (char)ptArgList;
  }
  else
  {
    v4 = Expression_EvalInt(*ptArgList->aptExpression);
  }
  *((_BYTE *)&Config_atDisplayDevice[4].tDisplayModeList[34].nWidth + 2752 * Config_tConfig.nPlayerProfiles + 1) = v4;
  Rs.nResult = 0;
  Rs.vResult = 0.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/config.c:2126  [size]
struct Result_s *__cdecl Config_GameOptionsSoundsSpeech(
        struct Result_s *retstr,
        void *pxUnUsed,
        struct ArgList_s *ptArgList)
{
  struct ArgList_s *v3; // edi
  char v4; // al
  double v5; // st7
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  v3 = ptArgList;
  if ( ptArgList->isQVM )
  {
    *(float *)&ptArgList = 0.0;
    QVM_EvalArg(&ptArgList, 4, v3, 0, 1);
    v4 = (char)ptArgList;
  }
  else
  {
    v4 = Expression_EvalInt(*ptArgList->aptExpression);
  }
  *((_BYTE *)&Config_atDisplayDevice[4].tDisplayModeList[86].nWidth + 2752 * Config_tConfig.nPlayerProfiles + 2) = v4;
  if ( v3->isQVM )
  {
    *(float *)&ptArgList = 0.0;
    QVM_EvalArg(&ptArgList, 4, v3, 1, 2);
    v5 = *(float *)&ptArgList;
  }
  else
  {
    v5 = Expression_EvalFloat((struct QExpression_s *)*((_DWORD *)v3->aptExpression + 1));
  }
  Rs.nResult = 0;
  *((float *)&Config_atDisplayDevice[4].tDisplayModeList[85].nHeight + 688 * Config_tConfig.nPlayerProfiles) = v5;
  Rs.vResult = 0.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/config.c:2145  [size]
struct Result_s *__cdecl Config_GameOptionsSoundsMusic(
        struct Result_s *retstr,
        void *pxUnUsed,
        struct ArgList_s *ptArgList)
{
  struct ArgList_s *v3; // edi
  char v4; // al
  double v5; // st7
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  v3 = ptArgList;
  if ( ptArgList->isQVM )
  {
    *(float *)&ptArgList = 0.0;
    QVM_EvalArg(&ptArgList, 4, v3, 0, 1);
    v4 = (char)ptArgList;
  }
  else
  {
    v4 = Expression_EvalInt(*ptArgList->aptExpression);
  }
  *((_BYTE *)&Config_atDisplayDevice[4].tDisplayModeList[86].nWidth + 2752 * Config_tConfig.nPlayerProfiles + 1) = v4;
  if ( v3->isQVM )
  {
    *(float *)&ptArgList = 0.0;
    QVM_EvalArg(&ptArgList, 4, v3, 1, 2);
    v5 = *(float *)&ptArgList;
  }
  else
  {
    v5 = Expression_EvalFloat((struct QExpression_s *)*((_DWORD *)v3->aptExpression + 1));
  }
  Rs.nResult = 0;
  *((float *)&Config_atDisplayDevice[4].tDisplayModeList[85].nWidth + 688 * Config_tConfig.nPlayerProfiles) = v5;
  Rs.vResult = 0.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/config.c:2164  [size]
struct Result_s *__cdecl Config_GameOptionsSoundsFX(
        struct Result_s *retstr,
        void *pxUnUsed,
        struct ArgList_s *ptArgList)
{
  struct ArgList_s *v3; // edi
  char v4; // al
  double v5; // st7
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  v3 = ptArgList;
  if ( ptArgList->isQVM )
  {
    *(float *)&ptArgList = 0.0;
    QVM_EvalArg(&ptArgList, 4, v3, 0, 1);
    v4 = (char)ptArgList;
  }
  else
  {
    v4 = Expression_EvalInt(*ptArgList->aptExpression);
  }
  *((_BYTE *)&Config_atDisplayDevice[4].tDisplayModeList[86].nWidth + 2752 * Config_tConfig.nPlayerProfiles) = v4;
  if ( v3->isQVM )
  {
    *(float *)&ptArgList = 0.0;
    QVM_EvalArg(&ptArgList, 4, v3, 1, 2);
    v5 = *(float *)&ptArgList;
  }
  else
  {
    v5 = Expression_EvalFloat((struct QExpression_s *)*((_DWORD *)v3->aptExpression + 1));
  }
  Rs.nResult = 0;
  *((float *)&Config_atDisplayDevice[4].tDisplayModeList[84].nDepth + 688 * Config_tConfig.nPlayerProfiles) = v5;
  Rs.vResult = 0.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/config.c:2183  [size]
struct Result_s *__cdecl Config_GameOptions3DSoundProvider(
        struct Result_s *retstr,
        void *pxUnused,
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
  *(&Config_atDisplayDevice[4].tDisplayModeList[85].nDepth + 688 * Config_tConfig.nPlayerProfiles) = (int)v4;
  Rs.nResult = 0;
  Rs.vResult = 0.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

struct Result_s *__cdecl sub_42A050(struct Result_s *retstr)
{
  char *LocalizedStringForLanguage; // eax
  char *v2; // eax
  char *v3; // eax
  char *v4; // eax
  char *v5; // eax
  _DWORD v7[6]; // [esp+Ch] [ebp-18h] BYREF

  LocalizedStringForLanguage = Config_GetLocalizedStringForLanguage(
                                 (char *)&g_zFileName.atPictureResources[17].ptPicture,
                                 Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eLanguage,
                                 true);
  ListBox_AddItem(LocalizedStringForLanguage, 0);
  v2 = Config_GetLocalizedStringForLanguage(
         &g_zFileName.atPictureResources[17].zResourceFilename[52],
         Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eLanguage,
         true);
  ListBox_AddItem(v2, 3);
  v3 = Config_GetLocalizedStringForLanguage(
         &g_zFileName.atPictureResources[17].zResourceFilename[40],
         Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eLanguage,
         true);
  ListBox_AddItem(v3, 1);
  v4 = Config_GetLocalizedStringForLanguage(
         &g_zFileName.atPictureResources[17].zResourceFilename[28],
         Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eLanguage,
         true);
  ListBox_AddItem(v4, 4);
  v5 = Config_GetLocalizedStringForLanguage(
         &g_zFileName.atPictureResources[17].zResourceFilename[16],
         Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eLanguage,
         true);
  ListBox_AddItem(v5, 5);
  v7[0] = 0;
  v7[2] = 0;
  v7[3] = 0;
  v7[4] = &g_zInitialValue;
  qmemcpy(retstr, v7, sizeof(struct Result_s));
  return retstr;
}

struct Result_s *__cdecl sub_42A160(struct Result_s *retstr, void *a2, struct ArgList_s *pxData)
{
  struct ArgList_s *v3; // edi
  struct ArgList_s *v4; // eax
  _DWORD v6[6]; // [esp+8h] [ebp-18h] BYREF

  v3 = pxData;
  if ( pxData->isQVM )
  {
    pxData = nullptr;
    QVM_EvalArg(&pxData, 4, v3, 0, 1);
    v4 = pxData;
  }
  else
  {
    v4 = (struct ArgList_s *)Expression_EvalInt(*pxData->aptExpression);
  }
  *(&Config_atDisplayDevice[4].tDisplayModeList[86].nHeight + 688 * Config_tConfig.nPlayerProfiles) = (int)v4;
  AIL_set_3D_speaker_type(
    Sound_hMiles3DProvider,
    *(&Config_atDisplayDevice[4].tDisplayModeList[86].nHeight + 688 * Config_tConfig.nPlayerProfiles));
  v6[0] = 0;
  v6[2] = 0;
  v6[3] = 0;
  v6[4] = &g_zInitialValue;
  qmemcpy(retstr, v6, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/config.c:2197  [anchor-strings]
struct Result_s *__cdecl Config_FillDifficultyLevelListBox(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  char *LocalizedStringForLanguage; // eax
  char *v4; // eax
  char *v5; // eax
  struct Result_s Rs; // [esp+Ch] [ebp-18h] BYREF

  LocalizedStringForLanguage = Config_GetLocalizedStringForLanguage(
                                 &g_zFileName.atPictureResources[17].zResourceFilename[8],
                                 Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eLanguage,
                                 true);
  ListBox_AddItem(LocalizedStringForLanguage, 0);
  v4 = Config_GetLocalizedStringForLanguage(
         g_zFileName.atPictureResources[17].zResourceFilename,
         Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eLanguage,
         true);
  ListBox_AddItem(v4, 1);
  v5 = Config_GetLocalizedStringForLanguage(
         &g_zFileName.atPictureResources[16].zResourceFilename[60],
         Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eLanguage,
         true);
  ListBox_AddItem(v5, 2);
  Rs.nResult = 0;
  Rs.vResult = 0.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/config.c:2213  [size]
struct Result_s *__cdecl Config_GetActiveDifficultyLevelScriptFunction(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  struct Result_s Rs; // [esp+Ch] [ebp-18h] BYREF

  Rs.nResult = Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eDifficultyLevel;
  Rs.vResult = (double)Rs.nResult;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/config.c:2226  [size]
struct Result_s *__cdecl Config_SetActiveDifficultyLevelScriptFunction(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  struct ArgList_s *v3; // edi
  struct ArgList_s *v4; // eax
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  v3 = ptArgList;
  if ( ptArgList->nArguments == 1 )
  {
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
    Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eDifficultyLevel = (enum GameDifficulty_e)v4;
  }
  Rs.nResult = 0;
  Rs.vResult = 0.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/config.c:2243  [size]
struct Result_s *__cdecl Config_Fill3DProviderScrollListBox(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  unsigned int i; // ebx
  struct Result_s Rs; // [esp+Ch] [ebp-18h] BYREF

  for ( i = 0; i < provider_count; ++i )
    ScrollListBox_AddItemEx(provider_names[i], i, false);
  Rs.nResult = 0;
  Rs.vResult = 0.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/config.c:2268  [size]
struct Result_s *__cdecl Config_GetActive3DProvider(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  struct Result_s Rs; // [esp+Ch] [ebp-18h] BYREF

  Rs.nResult = Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tSoundOptions.i3DSoundProvider;
  Rs.vResult = (double)Rs.nResult;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/config.c:2281  [size]
struct Result_s *__cdecl Config_SetActive3DProvider(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  #pragma pack(push, 1)
  union
  {
    struct { int nError; };
    struct { char igi2_o1[4]; struct Result_s Rs; };
    char igi2_extent[28];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct ArgList_s *v3; // edi
  int v4; // eax
  struct ArgList_s *v5; // eax

  v3 = ptArgList;
  v4 = 0;
  igi2_frame.nError = 0;
  if ( ptArgList->nArguments == 1 )
  {
    if ( ptArgList->isQVM )
    {
      ptArgList = nullptr;
      QVM_EvalArg(&ptArgList, 4, v3, 0, 1);
      v5 = ptArgList;
    }
    else
    {
      v5 = (struct ArgList_s *)Expression_EvalInt(*ptArgList->aptExpression);
    }
    v4 = Sound_Set3DProvider((int)v5);
    igi2_frame.nError = v4;
    Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tSoundOptions.i3DSoundProvider = provider_activeindex;
  }
  igi2_frame.Rs.nResult = v4;
  igi2_frame.Rs.vResult = (double)igi2_frame.nError;
  igi2_frame.Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &igi2_frame.Rs, sizeof(struct Result_s));
  return retstr;
}

struct Result_s *__cdecl sub_42A500(struct Result_s *retstr)
{
  double v2[3]; // [esp+Ch] [ebp-18h] BYREF

  LODWORD(v2[0]) = *((_DWORD *)&Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tSoundOptions + 5);
  v2[1] = (double)SLODWORD(v2[0]);
  LODWORD(v2[2]) = &g_zInitialValue;
  qmemcpy(retstr, v2, sizeof(struct Result_s));
  return retstr;
}

struct Result_s *__cdecl sub_42A550(struct Result_s *retstr, void *a2, struct ArgList_s *pxData)
{
  #pragma pack(push, 1)
  union
  {
    struct { unsigned int v6; };
    struct { char igi2_o1[16]; _DWORD v7[6]; };
    char igi2_extent[40];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct ArgList_s *v3; // edi
  struct ArgList_s *v4; // eax

  v3 = pxData;
  if ( pxData->nArguments == 1 )
  {
    if ( pxData->isQVM )
    {
      pxData = nullptr;
      QVM_EvalArg(&pxData, 4, v3, 0, 1);
      v4 = pxData;
    }
    else
    {
      v4 = (struct ArgList_s *)Expression_EvalInt(*pxData->aptExpression);
    }
    igi2_frame.v6 = Sound_hMiles3DProvider;
    *((_DWORD *)&Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tSoundOptions + 5) = v4;
    AIL_set_3D_speaker_type(igi2_frame.v6, v4);
  }
  igi2_frame.v7[0] = 0;
  igi2_frame.v7[2] = 0;
  igi2_frame.v7[3] = 0;
  igi2_frame.v7[4] = &g_zInitialValue;
  qmemcpy(retstr, igi2_frame.v7, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/config.c:2305  [anchor-strings]
void __cdecl Config_SetConfig()
{
  #pragma pack(push, 1)
  union
  {
    struct { float vMusicVolume; };
    struct { char igi2_o1[24]; char zAlias[256]; };
    char igi2_extent[280];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int isForceSoftwareVertexProcessing; // edx

  if ( byte_6BBEAC )
    File_RemoveAlias(&g_zFileName.atPictureResources[16].zResourceFilename[48]);
  sprintf(
    igi2_frame.zAlias,
    &g_zFileName.atPictureResources[16].zResourceFilename[28],
    16 * Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eLanguage + 6828784);
  File_RegisterAlias(&g_zFileName.atPictureResources[16].zResourceFilename[48], igi2_frame.zAlias);
  igi2_frame.vMusicVolume = Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tSoundOptions.vMusicVolume;
  byte_6BBEAC = 1;
  Sound_SetVolumeCD(igi2_frame.vMusicVolume, igi2_frame.vMusicVolume);
  isForceSoftwareVertexProcessing = Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGraphicOptions.isForceSoftwareVertexProcessing;
  Sound_vSSMasterVolume = Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tSoundOptions.vSoundEffectsVolume;
  Direct3D_isSoftwareVS = isForceSoftwareVertexProcessing;
}

// source: j/0/config.c:2334  [anchor-mhash]
struct Result_s *__cdecl Config_GameOptionsGraphicDevice(
        struct Result_s *retstr,
        void *pxUnUsed,
        struct ArgList_s *ptArgList)
{
  int *v3; // eax
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  v3 = &Config_atDisplayDevice[4].tDisplayModeList[39].nHeight + 688 * Config_tConfig.nPlayerProfiles;
  if ( ptArgList->isQVM )
  {
    *(_BYTE *)v3 = 0;
    QVM_EvalArg(v3, 256, ptArgList, 0, 3);
  }
  else
  {
    Expression_EvalString(
      *ptArgList->aptExpression,
      (char *)&Config_atDisplayDevice[4].tDisplayModeList[39].nHeight + 2752 * Config_tConfig.nPlayerProfiles,
      256);
  }
  Rs.nResult = 0;
  Rs.vResult = 0.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/config.c:2349  [size]
struct Result_s *__cdecl Config_GameOptionsGraphicGamma(
        struct Result_s *retstr,
        void *pxUnUsed,
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
  *((float *)&Config_atDisplayDevice[4].tDisplayModeList[83].nHeight + 688 * Config_tConfig.nPlayerProfiles) = v4;
  Rs.nResult = 0;
  Rs.vResult = 0.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/config.c:2364  [size]
struct Result_s *__cdecl Config_GameOptionsGraphicCrossHairAlpha(
        struct Result_s *retstr,
        void *pxUnUsed,
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
  *((float *)&Config_atDisplayDevice[4].tDisplayModeList[83].nDepth + 688 * Config_tConfig.nPlayerProfiles) = v4;
  Rs.nResult = 0;
  Rs.vResult = 0.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/config.c:2379  [anchor-mhash]
struct Result_s *__cdecl Config_GameOptionsInputSetInvertMouse(
        struct Result_s *retstr,
        void *pxUnUsed,
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
  Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tInputOptions.isInvertMouse = v4 == 0.0;
  Rs.nResult = 0;
  Rs.vResult = 0.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/config.c:2394  [anchor-mhash]
struct Result_s *__cdecl Config_GameOptionsGraphicsSetThickCrosshair(
        struct Result_s *retstr,
        void *pxUnused,
        struct ArgList_s *ptArgList)
{
  struct ArgList_s *v3; // edi
  double v4; // st7
  double v5; // st7
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
  if ( v4 == 0.0 )
    v5 = 1.0;
  else
    v5 = 2.0;
  Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGraphicOptions.vCrossHairThickness = v5;
  Rs.nResult = 0;
  Rs.vResult = 0.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/config.c:2408  [anchor-mhash]
struct Result_s *__cdecl Config_GameOptionsGraphicsGetThickCrosshair(
        struct Result_s *retstr,
        void *pxUnused,
        struct ArgList_s *ptArgList)
{
  struct Result_s Rs; // [esp+4h] [ebp-18h] BYREF

  Rs.nResult = Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGraphicOptions.vCrossHairThickness == 2.0;
  Rs.vResult = (double)(Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGraphicOptions.vCrossHairThickness == 2.0);
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/config.c:2421  [anchor-mhash]
struct Result_s *__cdecl Config_GameOptionsInputGetInvertMouse(
        struct Result_s *retstr,
        void *pxUnUsed,
        struct ArgList_s *ptArgList)
{
  BOOL v3; // ecx
  struct Result_s Rs; // [esp+Ch] [ebp-18h] BYREF

  v3 = Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tInputOptions.isInvertMouse == 0;
  Rs.zResult = (char *)&g_zInitialValue;
  Rs.nResult = v3;
  Rs.vResult = (double)v3;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/config.c:2434  [size]
struct Result_s *__cdecl Config_GameOptionsGfxGetForceSoftwareVertexProcessing(
        struct Result_s *retstr,
        void *pxUnused,
        struct ArgList_s *ptArgList)
{
  struct Result_s Rs; // [esp+Ch] [ebp-18h] BYREF

  Rs.nResult = Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGraphicOptions.isForceSoftwareVertexProcessing;
  Rs.vResult = (double)Rs.nResult;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/config.c:2447  [anchor-mhash]
struct Result_s *__cdecl Config_GameOptionsGfxSetForceSoftwareVertexProcessing(
        struct Result_s *retstr,
        void *pxUnused,
        struct ArgList_s *ptArgList)
{
  struct ArgList_s *v3; // edi
  char v4; // al
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  v3 = ptArgList;
  if ( ptArgList->isQVM )
  {
    ptArgList = nullptr;
    QVM_EvalArg(&ptArgList, 4, v3, 0, 1);
    v4 = (char)ptArgList;
  }
  else
  {
    v4 = Expression_EvalInt(*ptArgList->aptExpression);
  }
  Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGraphicOptions.isForceSoftwareVertexProcessing = v4;
  Direct3D_isSoftwareVS = Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGraphicOptions.isForceSoftwareVertexProcessing;
  Rs.nResult = 0;
  Rs.vResult = 0.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/config.c:2462  [size]
struct Result_s *__cdecl Config_GameOptionsForceSoftwareVertexProcessing(
        struct Result_s *retstr,
        void *pxUnused,
        struct ArgList_s *ptArgList)
{
  struct ArgList_s *v3; // edi
  char v4; // al
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  v3 = ptArgList;
  if ( ptArgList->isQVM )
  {
    ptArgList = nullptr;
    QVM_EvalArg(&ptArgList, 4, v3, 0, 1);
    v4 = (char)ptArgList;
  }
  else
  {
    v4 = Expression_EvalInt(*ptArgList->aptExpression);
  }
  *((_BYTE *)&Config_atDisplayDevice[4].tDisplayModeList[39].nWidth + 2752 * Config_tConfig.nPlayerProfiles) = v4;
  Rs.nResult = 0;
  Rs.vResult = 0.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/config.c:2476  [size]
struct Result_s *__cdecl Config_GameOptionsInputSetMouseSensitivity(
        struct Result_s *retstr,
        void *pxUnUsed,
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
  Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tInputOptions.vMouseSensitivity = v4;
  Rs.nResult = 0;
  Rs.vResult = 0.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/config.c:2492  [size]
struct Result_s *__cdecl Config_GameOptionsInputGetMouseSensitivity(
        struct Result_s *retstr,
        void *pxUnUsed,
        struct ArgList_s *ptArgList)
{
  #pragma pack(push, 1)
  union
  {
    struct { __int64 vMouseSensitivity; };
    struct { char igi2_o1[8]; struct Result_s Rs; };
    char igi2_extent[32];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)

  igi2_frame.vMouseSensitivity = (__int64)Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tInputOptions.vMouseSensitivity;
  igi2_frame.Rs.vResult = Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tInputOptions.vMouseSensitivity;
  igi2_frame.Rs.nResult = igi2_frame.vMouseSensitivity;
  igi2_frame.Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &igi2_frame.Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/config.c:2505  [anchor-mhash]
struct Result_s *__cdecl Config_GameOptionsInputSetBloodEnabled(
        struct Result_s *retstr,
        void *pxUnUsed,
        struct ArgList_s *ptArgList)
{
  struct ArgList_s *v3; // edi
  double v4; // st7
  struct Result_s Rs; // [esp+10h] [ebp-18h] BYREF

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
  Rs.nResult = 0;
  Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.isBlood = (__int64)v4;
  Rs.vResult = 0.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/config.c:2520  [size]
struct Result_s *__cdecl Config_GameOptionsInputGetBloodEnabled(
        struct Result_s *retstr,
        void *pxUnUsed,
        struct ArgList_s *ptArgList)
{
  struct Result_s Rs; // [esp+Ch] [ebp-18h] BYREF

  Rs.nResult = Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.isBlood;
  Rs.vResult = (double)Rs.nResult;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/config.c:2533  [size~]
void __cdecl Config_EnumDisplayModeCB(struct DisplayMode_s *ptDisplayMode)
{
  char *zDeviceIdentifier; // edx
  int v3; // edi
  int *v4; // eax
  struct DisplayMode_s *ptDisplayModea = *(struct DisplayMode_s * *)&ptDisplayMode; // [esp+8h] [ebp+4h] ARGSLOT

  zDeviceIdentifier = ptDisplayMode->zDeviceIdentifier;
  if ( ptDisplayMode != (struct DisplayMode_s *)-28
    && ptDisplayMode->nWidth >= 640
    && ptDisplayMode->nHeight >= 480
    && ptDisplayMode->nBitsPerPixel >= 16
    && Config_nNumDisplayDevices > 0 )
  {
    v3 = 0;
    ptDisplayModea = (struct DisplayMode_s *)Config_nNumDisplayDevices;
    do
    {
      if ( !strcmp(zDeviceIdentifier, Config_atDisplayDevice[v3].tDisplayDevice.zIdentifier) )
      {
        v4 = (int *)((char *)&Config_atDisplayDevice[0].tDisplayModeList[Config_atDisplayDevice[v3].nNumDisplayModes].nWidth
                   + v3 * 3332);
        *v4 = ptDisplayMode->nWidth;
        v4[1] = ptDisplayMode->nHeight;
        v4[2] = ptDisplayMode->nBitsPerPixel;
        ++Config_atDisplayDevice[v3].nNumDisplayModes;
      }
      ++v3;
      ptDisplayModea = (struct DisplayMode_s *)((char *)ptDisplayModea - 1);
    }
    while ( ptDisplayModea );
  }
}

// source: j/0/config.c:2568  [anchor-strings]
struct Result_s *__cdecl Config_FillScreenResolutionListBox(
        struct Result_s *retstr,
        void *pxUnUsed,
        struct ArgList_s *ptArgList)
{
  #pragma pack(push, 1)
  union
  {
    struct { int pxData; };
    struct { char igi2_o1[4]; _DWORD v10[6]; };
    struct { char igi2_o2[28]; char Buffer[256]; };
    char igi2_extent[284];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v3; // ebp
  int v4; // eax
  int v5; // edi
  struct ConfigDisplayMode_s *tDisplayModeList; // esi
  int nHeight; // ecx

  v3 = 0;
  if ( ptArgList->isQVM )
  {
    igi2_frame.pxData = 0;
    QVM_EvalArg(&igi2_frame.pxData, 4, ptArgList, 0, 1);
    v4 = igi2_frame.pxData;
  }
  else
  {
    v4 = Expression_EvalInt(*ptArgList->aptExpression);
  }
  v5 = v4;
  tDisplayModeList = Config_atDisplayDevice[v4].tDisplayModeList;
  if ( Config_atDisplayDevice[v4].nNumDisplayModes > 0 )
  {
    do
    {
      if ( tDisplayModeList->nWidth )
      {
        nHeight = tDisplayModeList->nHeight;
        if ( nHeight )
        {
          if ( tDisplayModeList->nDepth )
          {
            sprintf(
              igi2_frame.Buffer,
              &g_zFileName.atPictureResources[16].zResourceFilename[16],
              tDisplayModeList->nWidth,
              nHeight,
              tDisplayModeList->nDepth);
            ListBox_AddItem(
              igi2_frame.Buffer,
              tDisplayModeList->nHeight | ((tDisplayModeList->nWidth | (tDisplayModeList->nDepth << 13)) << 13));
          }
        }
      }
      ++tDisplayModeList;
      ++v3;
    }
    while ( v3 < Config_atDisplayDevice[v5].nNumDisplayModes );
  }
  igi2_frame.v10[0] = 0;
  igi2_frame.v10[2] = 0;
  igi2_frame.v10[3] = 0;
  igi2_frame.v10[4] = &g_zInitialValue;
  qmemcpy(retstr, igi2_frame.v10, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/config.c:2604  [anchor-mhash]
struct Result_s *__cdecl Config_GraphicOptionsSetResolution(
        struct Result_s *retstr,
        void *pxUnUsed,
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
  Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGraphicOptions.nDisplayDepth = ((int)v4 >> 26) & 0x3F;
  Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGraphicOptions.nDisplayWidth = ((int)v4 >> 13) & 0x1FFF;
  Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGraphicOptions.nDisplayHeight = (unsigned __int16)v4
                                                                                               & 0x1FFF;
  Rs.nResult = 0;
  Rs.vResult = 0.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/config.c:2624  [anchor-mhash]
struct Result_s *__cdecl Config_GraphicOptionsGetResolution(
        struct Result_s *retstr,
        void *pxUnUsed,
        struct ArgList_s *ptArgList)
{
  #pragma pack(push, 1)
  union
  {
    struct { int nDepth; };
    struct { char igi2_o1[4]; struct Result_s Rs; };
    char igi2_extent[28];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct ArgList_s *v3; // edi
  struct ConfigDisplayMode_s *v4; // ebp
  struct ArgList_s *v5; // eax
  int v6; // eax
  struct ConfigDisplayMode_s *tDisplayModeList; // esi
  struct ArgList_s *nNumDisplayModes; // eax
  int v9; // edi
  int v10; // ebx
  signed int v11; // ecx

  v3 = ptArgList;
  v4 = nullptr;
  if ( ptArgList->isQVM )
  {
    ptArgList = nullptr;
    QVM_EvalArg(&ptArgList, 4, v3, 0, 1);
    v5 = ptArgList;
  }
  else
  {
    v5 = (struct ArgList_s *)Expression_EvalInt(*ptArgList->aptExpression);
  }
  v6 = (int)v5;
  tDisplayModeList = Config_atDisplayDevice[v6].tDisplayModeList;
  nNumDisplayModes = (struct ArgList_s *)Config_atDisplayDevice[v6].nNumDisplayModes;
  igi2_frame.nDepth = Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGraphicOptions.nDisplayDepth;
  v9 = 0x7FFFFFFF;
  if ( (int)nNumDisplayModes > 0 )
  {
    v10 = Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGraphicOptions.nDisplayWidth
        * Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGraphicOptions.nDisplayHeight;
    ptArgList = nNumDisplayModes;
    do
    {
      v11 = (abs32(tDisplayModeList->nDepth - igi2_frame.nDepth) << 24)
          + abs32(tDisplayModeList->nWidth * tDisplayModeList->nHeight - v10);
      if ( v11 < v9 )
      {
        v4 = tDisplayModeList;
        v9 = v11;
      }
      ++tDisplayModeList;
      ptArgList = (struct ArgList_s *)((char *)ptArgList - 1);
    }
    while ( ptArgList );
  }
  ptArgList = (struct ArgList_s *)(v4->nHeight | ((v4->nWidth | (v4->nDepth << 13)) << 13));
  igi2_frame.Rs.nResult = (int)ptArgList;
  igi2_frame.Rs.vResult = (double)(int)ptArgList;
  igi2_frame.Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &igi2_frame.Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/config.c:2665  [size]
struct Result_s *__cdecl Config_LanguageScriptCB(
        struct Result_s *retstr,
        void *pxUnUsed,
        struct ArgList_s *ptArgList)
{
  struct ArgList_s *v3; // edi
  struct ArgList_s *v4; // esi
  char *LocalizedStringForLanguage; // eax
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
  if ( (int)v4 >= 6 )
  {
    Rs.nResult = 0;
    HIDWORD(Rs.vResult) = 0;
  }
  else
  {
    LocalizedStringForLanguage = Config_GetLocalizedStringForLanguage(
                                   (char *)(16 * (_DWORD)v4 + 6828784),
                                   Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eLanguage,
                                   true);
    MenuText_SetText((int)v4, LocalizedStringForLanguage);
    Rs.nResult = 1;
    HIDWORD(Rs.vResult) = 1072693248;
  }
  Rs.zResult = (char *)&g_zInitialValue;
  LODWORD(Rs.vResult) = 0;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/config.c:2689  [size]
struct Result_s *__cdecl Config_FillRenderDeviceListBox(
        struct Result_s *retstr,
        void *pxUnUsed,
        struct ArgList_s *ptArgList)
{
  int v3; // ebx
  char *zDesc; // esi
  struct Result_s Rs; // [esp+Ch] [ebp-18h] BYREF

  v3 = 0;
  if ( Config_nNumDisplayDevices > 0 )
  {
    zDesc = Config_atDisplayDevice[0].tDisplayDevice.zDesc;
    do
    {
      ListBox_AddItem(zDesc, v3++);
      zDesc += 3332;
    }
    while ( v3 < Config_nNumDisplayDevices );
  }
  Rs.nResult = 0;
  Rs.vResult = 0.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/config.c:2714  [anchor-strings]
struct Result_s *__cdecl Config_TestFillListBox(
        struct Result_s *retstr,
        void *pxUnUsed,
        struct ArgList_s *ptArgList)
{
  struct Result_s Rs; // [esp+Ch] [ebp-18h] BYREF

  ScrollListBox_AddItemEx(&g_zFileName.atPictureResources[16].zResourceFilename[8], 1, true);
  ScrollListBox_AddItemEx(g_zFileName.atPictureResources[16].zResourceFilename, 2, true);
  ScrollListBox_AddItemEx(&g_zFileName.atPictureResources[15].zResourceFilename[60], 3, true);
  ScrollListBox_AddItemEx(&g_zFileName.atPictureResources[15].zResourceFilename[52], 4, true);
  ScrollListBox_AddItemEx(&g_zFileName.atPictureResources[15].zResourceFilename[44], 5, true);
  ScrollListBox_AddItemEx(&g_zFileName.atPictureResources[15].zResourceFilename[36], 6, true);
  ScrollListBox_AddItemEx(&g_zFileName.atPictureResources[15].zResourceFilename[28], 7, true);
  ScrollListBox_AddItemEx(&g_zFileName.atPictureResources[15].zResourceFilename[20], 8, true);
  ScrollListBox_AddItemEx(&g_zFileName.atPictureResources[15].zResourceFilename[12], 9, true);
  ScrollListBox_AddItemEx(&g_zFileName.atPictureResources[15].zResourceFilename[4], 10, true);
  Rs.nResult = 1;
  Rs.vResult = 1.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/config.c:2743  [anchor-mhash]
struct Result_s *__cdecl Config_GraphicOptionsGetDevice(
        struct Result_s *retstr,
        void *pxUnUsed,
        struct ArgList_s *ptArgList)
{
  int v3; // ebp
  struct ConfigDisplayDevice_s *v4; // edi
  struct Result_s Rs; // [esp+14h] [ebp-18h] BYREF

  v3 = 0;
  if ( Config_nNumDisplayDevices <= 0 )
  {
LABEL_5:
    Rs.nResult = 0;
    Rs.vResult = 0.0;
  }
  else
  {
    v4 = Config_atDisplayDevice;
    while ( strcmp(
              Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGraphicOptions.zDeviceIdentifier,
              v4->tDisplayDevice.zIdentifier) )
    {
      ++v3;
      ++v4;
      if ( v3 >= Config_nNumDisplayDevices )
        goto LABEL_5;
    }
    Rs.nResult = v3;
    Rs.vResult = (double)v3;
  }
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/config.c:2768  [anchor-mhash]
struct Result_s *__cdecl Config_GraphicOptionsSetDevice(
        struct Result_s *retstr,
        void *pxUnUsed,
        struct ArgList_s *ptArgList)
{
  struct ArgList_s *v3; // edi
  struct ArgList_s *v4; // eax
  int v5; // esi
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
  v5 = (int)v4;
  strcpy(
    (char *)(2752 * Config_tConfig.iActiveProfile + 7392400),
    Config_atDisplayDevice[(_DWORD)v4].tDisplayDevice.zDesc);
  strcpy(
    (char *)(2752 * Config_tConfig.iActiveProfile + 7392144),
    Config_atDisplayDevice[v5].tDisplayDevice.zIdentifier);
  Rs.nResult = 0;
  Rs.vResult = 0.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/config.c:2788  [anchor-mhash]
struct Result_s *__cdecl Config_GraphicOptionsSetGamma(
        struct Result_s *retstr,
        void *pxUnUsed,
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
  Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGraphicOptions.vGamma = v4;
  Config_SetGamma(Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGraphicOptions.vGamma);
  Rs.nResult = 0;
  Rs.vResult = 0.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/config.c:2803  [size]
struct Result_s *__cdecl Config_GraphicOptionsGetGamma(
        struct Result_s *retstr,
        void *pxUnUsed,
        struct ArgList_s *ptArgList)
{
  #pragma pack(push, 1)
  union
  {
    struct { __int64 vGamma; };
    struct { char igi2_o1[8]; struct Result_s Rs; };
    char igi2_extent[32];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)

  igi2_frame.vGamma = (__int64)Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGraphicOptions.vGamma;
  igi2_frame.Rs.vResult = Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGraphicOptions.vGamma;
  igi2_frame.Rs.nResult = igi2_frame.vGamma;
  igi2_frame.Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &igi2_frame.Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/config.c:2816  [size]
struct Result_s *__cdecl Config_GraphicOptionsSetCrossHairAlpha(
        struct Result_s *retstr,
        void *pxUnUsed,
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
  Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGraphicOptions.vCrossHairAlpha = v4;
  Rs.nResult = 0;
  Rs.vResult = 0.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/config.c:2831  [size]
struct Result_s *__cdecl Config_GraphicOptionsGetCrossHairAlpha(
        struct Result_s *retstr,
        void *pxUnUsed,
        struct ArgList_s *ptArgList)
{
  #pragma pack(push, 1)
  union
  {
    struct { __int64 vCrossHairAlpha; };
    struct { char igi2_o1[8]; struct Result_s Rs; };
    char igi2_extent[32];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)

  igi2_frame.vCrossHairAlpha = (__int64)Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGraphicOptions.vCrossHairAlpha;
  igi2_frame.Rs.vResult = Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGraphicOptions.vCrossHairAlpha;
  igi2_frame.Rs.nResult = igi2_frame.vCrossHairAlpha;
  igi2_frame.Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &igi2_frame.Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/config.c:2844  [size]
struct Result_s *__cdecl Config_GraphicOptionsSetCrossHairColourR(
        struct Result_s *retstr,
        void *pxUnUsed,
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
  Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGraphicOptions.vCrossHairR = v4;
  Rs.nResult = 0;
  Rs.vResult = 0.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/config.c:2859  [size]
struct Result_s *__cdecl Config_GraphicOptionsSetCrossHairColourG(
        struct Result_s *retstr,
        void *pxUnUsed,
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
  Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGraphicOptions.vCrossHairG = v4;
  Rs.nResult = 0;
  Rs.vResult = 0.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/config.c:2874  [size]
struct Result_s *__cdecl Config_GraphicOptionsSetCrossHairColourB(
        struct Result_s *retstr,
        void *pxUnUsed,
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
  Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGraphicOptions.vCrossHairB = v4;
  Rs.nResult = 0;
  Rs.vResult = 0.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/config.c:2889  [size]
struct Result_s *__cdecl Config_GraphicOptionsGetCrossHairColourR(
        struct Result_s *retstr,
        void *pxUnUsed,
        struct ArgList_s *ptArgList)
{
  #pragma pack(push, 1)
  union
  {
    struct { __int64 vCrossHairR; };
    struct { char igi2_o1[8]; struct Result_s Rs; };
    char igi2_extent[32];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)

  igi2_frame.vCrossHairR = (__int64)Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGraphicOptions.vCrossHairR;
  igi2_frame.Rs.vResult = Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGraphicOptions.vCrossHairR;
  igi2_frame.Rs.nResult = igi2_frame.vCrossHairR;
  igi2_frame.Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &igi2_frame.Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/config.c:2902  [size]
struct Result_s *__cdecl Config_GraphicOptionsGetCrossHairColourG(
        struct Result_s *retstr,
        void *pxUnUsed,
        struct ArgList_s *ptArgList)
{
  #pragma pack(push, 1)
  union
  {
    struct { __int64 vCrossHairG; };
    struct { char igi2_o1[8]; struct Result_s Rs; };
    char igi2_extent[32];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)

  igi2_frame.vCrossHairG = (__int64)Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGraphicOptions.vCrossHairG;
  igi2_frame.Rs.vResult = Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGraphicOptions.vCrossHairG;
  igi2_frame.Rs.nResult = igi2_frame.vCrossHairG;
  igi2_frame.Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &igi2_frame.Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/config.c:2915  [size]
struct Result_s *__cdecl Config_GraphicOptionsGetCrossHairColourB(
        struct Result_s *retstr,
        void *pxUnUsed,
        struct ArgList_s *ptArgList)
{
  #pragma pack(push, 1)
  union
  {
    struct { __int64 vCrossHairB; };
    struct { char igi2_o1[8]; struct Result_s Rs; };
    char igi2_extent[32];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)

  igi2_frame.vCrossHairB = (__int64)Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGraphicOptions.vCrossHairB;
  igi2_frame.Rs.vResult = Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGraphicOptions.vCrossHairB;
  igi2_frame.Rs.nResult = igi2_frame.vCrossHairB;
  igi2_frame.Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &igi2_frame.Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/config.c:2928  [size]
struct Result_s *__cdecl Config_GraphicOptionsSetTransparency(
        struct Result_s *retstr,
        void *pxUnUsed,
        struct ArgList_s *ptArgList)
{
  struct ArgList_s *v3; // edi
  char v4; // al
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  v3 = ptArgList;
  if ( ptArgList->isQVM )
  {
    ptArgList = nullptr;
    QVM_EvalArg(&ptArgList, 4, v3, 0, 1);
    v4 = (char)ptArgList;
  }
  else
  {
    v4 = Expression_EvalInt(*ptArgList->aptExpression);
  }
  Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGraphicOptions.isTransparency = v4;
  Rs.nResult = 0;
  Rs.vResult = 0.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/config.c:2943  [size]
struct Result_s *__cdecl Config_GraphicOptionsGetTransparency(
        struct Result_s *retstr,
        void *pxUnUsed,
        struct ArgList_s *ptArgList)
{
  struct Result_s Rs; // [esp+Ch] [ebp-18h] BYREF

  Rs.nResult = Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGraphicOptions.isTransparency;
  Rs.vResult = (double)Rs.nResult;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/config.c:2956  [size]
struct Result_s *__cdecl Config_SoundOptionsSetSoundEffects(
        struct Result_s *retstr,
        void *pxUnUsed,
        struct ArgList_s *ptArgList)
{
  struct ArgList_s *v3; // edi
  char v4; // al
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  v3 = ptArgList;
  if ( ptArgList->isQVM )
  {
    ptArgList = nullptr;
    QVM_EvalArg(&ptArgList, 4, v3, 0, 1);
    v4 = (char)ptArgList;
  }
  else
  {
    v4 = Expression_EvalInt(*ptArgList->aptExpression);
  }
  Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tSoundOptions.isSoundEffects = v4;
  Rs.nResult = 0;
  Rs.vResult = 0.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/config.c:2971  [size]
struct Result_s *__cdecl Config_SoundOptionsGetSoundEffects(
        struct Result_s *retstr,
        void *pxUnUsed,
        struct ArgList_s *ptArgList)
{
  struct Result_s Rs; // [esp+Ch] [ebp-18h] BYREF

  Rs.nResult = Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tSoundOptions.isSoundEffects;
  Rs.vResult = (double)Rs.nResult;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/config.c:2984  [size]
struct Result_s *__cdecl Config_SoundOptionsSetSoundEffectsVolume(
        struct Result_s *retstr,
        void *pxUnUsed,
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
  Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tSoundOptions.vSoundEffectsVolume = v4;
  Rs.nResult = 0;
  Rs.vResult = 0.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/config.c:2999  [size]
struct Result_s *__cdecl Config_SoundOptionsGetSoundEffectsVolume(
        struct Result_s *retstr,
        void *pxUnUsed,
        struct ArgList_s *ptArgList)
{
  #pragma pack(push, 1)
  union
  {
    struct { __int64 vSoundEffectsVolume; };
    struct { char igi2_o1[8]; struct Result_s Rs; };
    char igi2_extent[32];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)

  igi2_frame.vSoundEffectsVolume = (__int64)Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tSoundOptions.vSoundEffectsVolume;
  igi2_frame.Rs.vResult = Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tSoundOptions.vSoundEffectsVolume;
  igi2_frame.Rs.nResult = igi2_frame.vSoundEffectsVolume;
  igi2_frame.Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &igi2_frame.Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/config.c:3012  [size]
struct Result_s *__cdecl Config_SoundOptionsSetMusic(
        struct Result_s *retstr,
        void *pxUnUsed,
        struct ArgList_s *ptArgList)
{
  struct ArgList_s *v3; // edi
  char v4; // al
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  v3 = ptArgList;
  if ( ptArgList->isQVM )
  {
    ptArgList = nullptr;
    QVM_EvalArg(&ptArgList, 4, v3, 0, 1);
    v4 = (char)ptArgList;
  }
  else
  {
    v4 = Expression_EvalInt(*ptArgList->aptExpression);
  }
  Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tSoundOptions.isMusic = v4;
  Rs.nResult = 0;
  Rs.vResult = 0.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/config.c:3027  [size]
struct Result_s *__cdecl Config_SoundOptionsGetMusic(
        struct Result_s *retstr,
        void *pxUnUsed,
        struct ArgList_s *ptArgList)
{
  struct Result_s Rs; // [esp+Ch] [ebp-18h] BYREF

  Rs.nResult = Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tSoundOptions.isMusic;
  Rs.vResult = (double)Rs.nResult;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/config.c:3040  [size]
struct Result_s *__cdecl Config_SoundOptionsSetMusicVolume(
        struct Result_s *retstr,
        void *pxUnUsed,
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
  Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tSoundOptions.vMusicVolume = v4;
  Rs.nResult = 0;
  Rs.vResult = 0.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/config.c:3055  [size]
struct Result_s *__cdecl Config_SoundOptionsGetMusicVolume(
        struct Result_s *retstr,
        void *pxUnUsed,
        struct ArgList_s *ptArgList)
{
  #pragma pack(push, 1)
  union
  {
    struct { __int64 vMusicVolume; };
    struct { char igi2_o1[8]; struct Result_s Rs; };
    char igi2_extent[32];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)

  igi2_frame.vMusicVolume = (__int64)Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tSoundOptions.vMusicVolume;
  igi2_frame.Rs.vResult = Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tSoundOptions.vMusicVolume;
  igi2_frame.Rs.nResult = igi2_frame.vMusicVolume;
  igi2_frame.Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &igi2_frame.Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/config.c:3068  [size]
struct Result_s *__cdecl Config_SoundOptionsSetSpeech(
        struct Result_s *retstr,
        void *pxUnUsed,
        struct ArgList_s *ptArgList)
{
  struct ArgList_s *v3; // edi
  char v4; // al
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  v3 = ptArgList;
  if ( ptArgList->isQVM )
  {
    ptArgList = nullptr;
    QVM_EvalArg(&ptArgList, 4, v3, 0, 1);
    v4 = (char)ptArgList;
  }
  else
  {
    v4 = Expression_EvalInt(*ptArgList->aptExpression);
  }
  Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tSoundOptions.isSpeech = v4;
  Rs.nResult = 0;
  Rs.vResult = 0.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/config.c:3083  [size]
struct Result_s *__cdecl Config_SoundOptionsGetSpeech(
        struct Result_s *retstr,
        void *pxUnUsed,
        struct ArgList_s *ptArgList)
{
  struct Result_s Rs; // [esp+Ch] [ebp-18h] BYREF

  Rs.nResult = Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tSoundOptions.isSpeech;
  Rs.vResult = (double)Rs.nResult;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/config.c:3096  [size]
struct Result_s *__cdecl Config_SoundOptionsSetSpeechVolume(
        struct Result_s *retstr,
        void *pxUnUsed,
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
  Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tSoundOptions.vSoundEffectsVolume = v4;
  Rs.nResult = 0;
  Rs.vResult = 0.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/config.c:3111  [size]
struct Result_s *__cdecl Config_SoundOptionsGetSpeechVolume(
        struct Result_s *retstr,
        void *pxUnUsed,
        struct ArgList_s *ptArgList)
{
  #pragma pack(push, 1)
  union
  {
    struct { __int64 vSoundEffectsVolume; };
    struct { char igi2_o1[8]; struct Result_s Rs; };
    char igi2_extent[32];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)

  igi2_frame.vSoundEffectsVolume = (__int64)Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tSoundOptions.vSoundEffectsVolume;
  igi2_frame.Rs.vResult = Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tSoundOptions.vSoundEffectsVolume;
  igi2_frame.Rs.nResult = igi2_frame.vSoundEffectsVolume;
  igi2_frame.Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &igi2_frame.Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/config.c:3124  [size]
struct Result_s *__cdecl Config_SoundOptionsSetReverseStereo(
        struct Result_s *retstr,
        void *pxUnUsed,
        struct ArgList_s *ptArgList)
{
  struct ArgList_s *v3; // edi
  char v4; // al
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  v3 = ptArgList;
  if ( ptArgList->isQVM )
  {
    ptArgList = nullptr;
    QVM_EvalArg(&ptArgList, 4, v3, 0, 1);
    v4 = (char)ptArgList;
  }
  else
  {
    v4 = Expression_EvalInt(*ptArgList->aptExpression);
  }
  Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tSoundOptions.isReverseStereo = v4;
  Rs.nResult = 0;
  Rs.vResult = 0.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/config.c:3139  [size]
struct Result_s *__cdecl Config_SoundOptionsGetReverseStereo(
        struct Result_s *retstr,
        void *pxUnUsed,
        struct ArgList_s *ptArgList)
{
  struct Result_s Rs; // [esp+Ch] [ebp-18h] BYREF

  Rs.nResult = Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tSoundOptions.isReverseStereo;
  Rs.vResult = (double)Rs.nResult;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/config.c:3152  [size]
struct Result_s *__cdecl Config_FillPlayerProfileListBox(
        struct Result_s *retstr,
        void *pxUnUsed,
        struct ArgList_s *ptArgList)
{
  int v3; // ebx
  char *zCallSign; // esi
  struct Result_s Rs; // [esp+Ch] [ebp-18h] BYREF

  v3 = 0;
  if ( Config_tConfig.nPlayerProfiles > 0 )
  {
    zCallSign = Config_tConfig.atPlayerProfile[0].zCallSign;
    do
    {
      ListBox_AddItem(zCallSign, v3++);
      zCallSign += 2752;
    }
    while ( v3 < Config_tConfig.nPlayerProfiles );
  }
  Rs.nResult = 0;
  Rs.vResult = 0.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/config.c:3174  [size]
struct Result_s *__cdecl Config_GetActivePlayerProfileIndexScriptFunction(
        struct Result_s *retstr,
        void *pxUnUsed,
        struct ArgList_s *ptArgList)
{
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  Rs.nResult = Config_tConfig.iActiveProfile;
  Rs.vResult = (double)Config_tConfig.iActiveProfile;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/config.c:3187  [size]
struct Result_s *__cdecl Config_SetActivePlayerProfileIndexScriptFunction(
        struct Result_s *retstr,
        void *pxUnUsed,
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
  Config_tConfig.iActiveProfile = (int)v4;
  Rs.nResult = 1;
  Rs.vResult = 1.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/config.c:3202  [anchor-caller]
struct Result_s *__cdecl Config_CreateNewPlayerProfile(
        struct Result_s *retstr,
        void *pxUnused,
        struct ArgList_s *ptArgList)
{
  #pragma pack(push, 1)
  union
  {
    struct { __int32 pxData; };
    struct { char igi2_o1[4]; char zName[32]; };
    char igi2_extent[36];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct ArgList_s *v3; // esi
  unsigned int v4; // eax
  char v5; // cl
  int v7; // edi
  char *zCallSign; // esi
  _DWORD *v9; // eax
  int v10; // ebx
  int v11; // eax
  enum GameDifficulty_e v12; // eax

  if ( Config_tConfig.nPlayerProfiles >= 16 )
    goto LABEL_9;
  v3 = ptArgList;
  if ( ptArgList->isQVM )
  {
    igi2_frame.zName[0] = 0;
    QVM_EvalArg(igi2_frame.zName, 32, ptArgList, 0, 3);
  }
  else
  {
    Expression_EvalString(*ptArgList->aptExpression, igi2_frame.zName, 32);
  }
  v4 = strlen(igi2_frame.zName);
  if ( !v4 )
  {
LABEL_9:
    *(_DWORD *)igi2_frame.zName = 0;
    *(_DWORD *)&igi2_frame.zName[12] = 0;
    goto LABEL_10;
  }
  while ( 1 )
  {
    v5 = igi2_frame.zName[v4 - 1];
    if ( v5 != 32 && v5 != 9 )
      break;
    if ( !--v4 )
      goto LABEL_9;
  }
  igi2_frame.zName[v4] = 0;
  v7 = 0;
  if ( Config_tConfig.nPlayerProfiles > 0 )
  {
    zCallSign = Config_tConfig.atPlayerProfile[0].zCallSign;
    while ( _stricmp(igi2_frame.zName, zCallSign) )
    {
      ++v7;
      zCallSign += 2752;
      if ( v7 >= Config_tConfig.nPlayerProfiles )
      {
        if ( Config_tConfig.nPlayerProfiles <= 0 )
        {
          v3 = ptArgList;
          goto LABEL_24;
        }
        v9 = (_DWORD *)(2752 * Config_tConfig.iActiveProfile + 7392072);
        v10 = 2752 * Config_tConfig.nPlayerProfiles + 7392072;
        *(_DWORD *)v10 = Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eDifficultyLevel;
        *(_DWORD *)(v10 + 4) = v9[1];
        *(_DWORD *)(v10 + 8) = v9[2];
        qmemcpy((void *)(v10 + 12), v9 + 3, 0x25Cu);
        qmemcpy((void *)(v10 + 616), v9 + 154, 0x18u);
        qmemcpy((void *)(v10 + 640), v9 + 160, 0x810u);
        if ( ptArgList->isQVM )
        {
          igi2_frame.pxData = 0;
          QVM_EvalArg(&igi2_frame.pxData, 4, ptArgList, 1, 1);
          v11 = igi2_frame.pxData;
        }
        else
        {
          v11 = Expression_EvalInt(ptArgList->aptExpression[1]);
        }
        *(_DWORD *)v10 = v11;
        Config_tConfig.iActiveProfile = Config_tConfig.nPlayerProfiles++;
        if ( ptArgList->isQVM )
        {
          *(_BYTE *)(v10 + 2704) = 0;
          QVM_EvalArg((void *)(v10 + 2704), 32, ptArgList, 0, 3);
        }
        else
        {
          Expression_EvalString(*ptArgList->aptExpression, (char *)(v10 + 2704), 32);
        }
        *(_DWORD *)(v10 + 2736) = 0;
        *(_DWORD *)(v10 + 2740) = 0;
        *(_DWORD *)(v10 + 2744) = 0;
        Config_AllocatePlayerProfileResources(Config_tConfig.nPlayerProfiles - 1);
        goto LABEL_31;
      }
    }
    goto LABEL_9;
  }
LABEL_24:
  Config_DefaultGameOptions();
  if ( v3->isQVM )
  {
    Config_tConfig.atPlayerProfile[0].zCallSign[0] = 0;
    QVM_EvalArg(Config_tConfig.atPlayerProfile[0].zCallSign, 32, v3, 0, 3);
  }
  else
  {
    Expression_EvalString(*v3->aptExpression, Config_tConfig.atPlayerProfile[0].zCallSign, 32);
  }
  if ( v3->isQVM )
  {
    igi2_frame.pxData = 0;
    QVM_EvalArg(&igi2_frame.pxData, 4, v3, 1, 1);
    v12 = igi2_frame.pxData;
  }
  else
  {
    v12 = Expression_EvalInt(v3->aptExpression[1]);
  }
  Config_tConfig.atPlayerProfile[0].tGameOptions.eDifficultyLevel = v12;
LABEL_31:
  *(_DWORD *)igi2_frame.zName = 1;
  *(_DWORD *)&igi2_frame.zName[12] = 1072693248;
LABEL_10:
  *(_DWORD *)&igi2_frame.zName[16] = &g_zInitialValue;
  *(_DWORD *)&igi2_frame.zName[8] = 0;
  qmemcpy(retstr, igi2_frame.zName, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/config.c:3296  [anchor-mhash]
struct Result_s *__cdecl Config_DeletePlayerProfile(
        struct Result_s *retstr,
        void *pxUnused,
        struct ArgList_s *ptArgList)
{
  struct ArgList_s *v3; // edi
  struct ArgList_s *v4; // edi
  struct QHashTable_s **p_ptMissionStatsHashTable; // esi
  struct QHashTable_s *v6; // eax
  int v7; // edx
  char *v8; // eax
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
  if ( (int)v4 >= Config_tConfig.nPlayerProfiles )
  {
    Rs.nResult = 0;
    HIDWORD(Rs.vResult) = 0;
  }
  else
  {
    p_ptMissionStatsHashTable = &Config_tConfig.atPlayerProfile[(_DWORD)v4].ptMissionStatsHashTable;
    v6 = *p_ptMissionStatsHashTable;
    if ( *p_ptMissionStatsHashTable )
    {
      if ( v6->tPrivate.nEntries )
        v6->tPrivate.pfMap(
          v6,
          (void (__cdecl *)(struct QHashTable_s *, void *, void *, void *))Config_FreeMissionStatsEntry,
          nullptr);
      QHashTable_Delete(*p_ptMissionStatsHashTable);
      *p_ptMissionStatsHashTable = nullptr;
    }
    if ( Config_tConfig.iActiveProfile >= (int)v4 && Config_tConfig.iActiveProfile > 0 )
      --Config_tConfig.iActiveProfile;
    v7 = (int)&v4->nArguments + 1;
    if ( (int)&v4->nArguments + 1 < Config_tConfig.nPlayerProfiles )
    {
      v8 = (char *)(2752 * v7 + 7392072);
      do
      {
        qmemcpy(v8 - 2752, v8, 0xAC0u);
        ++v7;
        v8 += 2752;
      }
      while ( v7 < Config_tConfig.nPlayerProfiles );
    }
    Config_SetPlayerProfileDefaults(v7 - 1);
    --Config_tConfig.nPlayerProfiles;
    Rs.nResult = 1;
    HIDWORD(Rs.vResult) = 1072693248;
  }
  Rs.zResult = (char *)&g_zInitialValue;
  LODWORD(Rs.vResult) = 0;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/config.c:3341  [size]
struct Result_s *__cdecl Config_GetNumberOfPlayerProfiles(
        struct Result_s *retstr,
        void *pxUnused,
        struct ArgList_s *ptArgList)
{
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  Rs.nResult = Config_tConfig.nPlayerProfiles;
  Rs.vResult = (double)Config_tConfig.nPlayerProfiles;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/config.c:3354  [anchor-mhash]
struct Result_s *__cdecl Config_FillMissionSelectionBox(
        struct Result_s *retstr,
        void *pxUnUsed,
        struct ArgList_s *ptArgList)
{
  struct Node_s *ptHead; // esi
  int v4; // edi
  int v5; // ebp
  struct Result_s Rs; // [esp+Ch] [ebp-18h] BYREF

  ptHead = Mission_tMissionList.ptHead;
  if ( !Mission_tMissionList.ptHead->ptNext )
    ptHead = nullptr;
  v4 = 0;
  v5 = 1;
  while ( ptHead )
  {
    if ( !v5 )
      break;
    ScrollListBox_AddItemEx((char *)&ptHead[1].ptPrev[2], (int)ptHead[1].ptNext, true);
    if ( v4 == Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].anActiveMission[Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eDifficultyLevel] )
      v5 = 0;
    else
      ++v4;
    ptHead = ptHead->ptNext;
    if ( !ptHead->ptNext )
      break;
  }
  Rs.nResult = 0;
  Rs.vResult = 0.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/config.c:3398  [anchor-mhash]
struct Result_s *__cdecl Config_FillMissionPictureBox(
        struct Result_s *retstr,
        void *pxUnUsed,
        struct ArgList_s *ptArgList)
{
  #pragma pack(push, 1)
  union
  {
    struct { int iProgress; };
    struct { char igi2_o1[4]; int isContinue; };
    struct { char igi2_o2[8]; struct Result_s Rs; };
    char igi2_extent[32];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct Node_s *ptHead; // ebx
  struct PictureBox_s *v4; // esi
  int nPicture; // eax
  struct Node_s *ptPrev; // ebp
  struct Node_s *ptNext; // edi
  int zItem; // edx
  int v9; // ecx
  int *p_nItemID; // eax
  struct Node_s *v11; // eax
  int v12; // edx
  char v13; // cl

  ptHead = Mission_tMissionList.ptHead;
  if ( !Mission_tMissionList.ptHead->ptNext )
    ptHead = nullptr;
  igi2_frame.isContinue = 1;
  igi2_frame.iProgress = 0;
  if ( ptHead )
  {
    v4 = PictureBox_ptActivePictureBox;
    do
    {
      if ( !igi2_frame.isContinue )
        break;
      nPicture = v4->nPicture;
      ptPrev = ptHead[1].ptPrev;
      ptNext = ptHead[1].ptNext;
      zItem = (int)v4->atPictureBoxItem[nPicture].zItem;
      v9 = 0;
      if ( nPicture <= 0 )
      {
LABEL_10:
        v11 = ptPrev + 146;
        *(_DWORD *)(zItem + 64) = ptNext;
        v12 = zItem - (_DWORD)(ptPrev + 146);
        do
        {
          v13 = (char)v11->ptNext;
          *((_BYTE *)&v11->ptNext + v12) = v11->ptNext;
          v11 = (struct Node_s *)((char *)v11 + 1);
        }
        while ( v13 );
        ++v4->nPicture;
      }
      else
      {
        p_nItemID = &v4->atPictureBoxItem[0].nItemID;
        while ( (struct Node_s *)*p_nItemID != ptNext )
        {
          ++v9;
          p_nItemID += 18;
          if ( v9 >= v4->nPicture )
            goto LABEL_10;
        }
      }
      if ( igi2_frame.iProgress == Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].anActiveMission[Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eDifficultyLevel] )
        igi2_frame.isContinue = 0;
      else
        ++igi2_frame.iProgress;
      ptHead = ptHead->ptNext;
      if ( !ptHead->ptNext )
        break;
    }
    while ( ptHead );
  }
  igi2_frame.Rs.nResult = 0;
  igi2_frame.Rs.vResult = 0.0;
  igi2_frame.Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &igi2_frame.Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/config.c:3441  [anchor-mhash]
struct Result_s *__cdecl Config_FillMissionTextBox(
        struct Result_s *retstr,
        void *pxUnUsed,
        struct ArgList_s *ptArgList)
{
  struct Node_s *ptHead; // esi
  int v4; // edi
  int v5; // ebp
  struct Result_s Rs; // [esp+Ch] [ebp-18h] BYREF

  ptHead = Mission_tMissionList.ptHead;
  if ( !Mission_tMissionList.ptHead->ptNext )
    ptHead = nullptr;
  v4 = 0;
  v5 = 1;
  while ( ptHead )
  {
    if ( !v5 )
      break;
    TextBox_AddItem((char *)&ptHead[1].ptPrev[6], (int)ptHead[1].ptNext);
    if ( v4 == Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].anActiveMission[Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eDifficultyLevel] )
      v5 = 0;
    else
      ++v4;
    ptHead = ptHead->ptNext;
    if ( !ptHead->ptNext )
      break;
  }
  Rs.nResult = 0;
  Rs.vResult = 0.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/config.c:3485  [anchor-mhash]
struct Result_s *__cdecl Config_PlayerGetActiveMission(
        struct Result_s *retstr,
        void *pxUnUsed,
        struct ArgList_s *ptArgList)
{
  struct ArgList_s *v3; // edi
  struct ArgList_s *v4; // eax
  struct Node_s *ptHead; // esi
  struct Node_s *ptNext; // ecx
  int v7; // eax
  int v8; // edx
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
  ptHead = Mission_tMissionList.ptHead;
  ptNext = Mission_tMissionList.ptHead->ptNext;
  v7 = Config_tConfig.atPlayerProfile[(_DWORD)v4].anActiveMission[Config_tConfig.atPlayerProfile[(_DWORD)v4].tGameOptions.eDifficultyLevel];
  v8 = 0;
  if ( !Mission_tMissionList.ptHead->ptNext )
    goto LABEL_7;
  while ( v7 != v8 )
  {
    ptHead = ptNext;
    ptNext = ptNext->ptNext;
    ++v8;
    if ( !ptNext )
      goto LABEL_7;
  }
  if ( ptHead )
  {
    Rs.nResult = (int)ptHead[1].ptNext;
    ptArgList = (struct ArgList_s *)Rs.nResult;
  }
  else
  {
LABEL_7:
    Rs.nResult = -1;
    ptArgList = (struct ArgList_s *)-1;
  }
  Rs.vResult = (double)(int)ptArgList;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/config.c:3505  [size]
struct Result_s *__cdecl Config_GameOptionsOK(
        struct Result_s *retstr,
        enum bool *pisOK,
        struct ArgList_s *ptArgList)
{
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  *pisOK = true;
  Rs.nResult = 0;
  Rs.vResult = 0.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/config.c:3524  [anchor-strings]
void __cdecl Config_Load(char *zConfigFileName)
{
  struct Script_s *v1; // eax
  struct Script_s *v2; // esi
  int iActiveProfile; // ebx
  int v4; // esi
  int i; // edi
  enum bool isOK; // [esp+Ch] [ebp-4h] BYREF

  Config_FreeAllPlayerProfileResources();
  isOK = false;
  Config_DefaultGameOptions();
  Symbol_Register(
    &g_zFileName.atPictureResources[14].zResourceFilename[60],
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Config_GameOptionsOK,
    &isOK,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  v1 = Script_New(zConfigFileName);
  v2 = v1;
  if ( v1 )
  {
    Script_Execute(v1);
    Script_Delete(v2);
  }
  if ( isOK == false )
    Config_DefaultGameOptions();
  Symbol_Remove(&g_zFileName.atPictureResources[14].zResourceFilename[60]);
  iActiveProfile = Config_tConfig.iActiveProfile;
  v4 = 0;
  for ( i = Config_tConfig.nPlayerProfiles; v4 < i; ++v4 )
  {
    Config_tConfig.iActiveProfile = v4;
    Config_VerifyGraphicConfig();
  }
  Config_tConfig.iActiveProfile = iActiveProfile;
  Config_SetConfig();
}

// source: j/0/config.c:3567  [anchor-strings]
void __cdecl Config_Save(char *zConfigFileName)
{
  struct File_s *v1; // esi
  unsigned int v2; // eax
  unsigned int v3; // eax
  int i; // edi
  char Buffer[260]; // [esp+Ch] [ebp-104h] BYREF

  v1 = File_New(zConfigFileName, "w");
  if ( v1 )
  {
    File_printf(v1, &g_zFileName.atPictureResources[14].zResourceFilename[40]);
    File_printf(v1, &g_zFileName.atPictureResources[14].zResourceFilename[20]);
    v2 = sprintf(
           Buffer,
           &g_zFileName.atPictureResources[21].zResourceFilename[60],
           Config_zGameOptionsStart,
           Config_tConfig.iActiveProfile);
    File_atDevice[v1->eDeviceID].pfWrite(v1->eDeviceID, v1, Buffer, v2);
    v3 = sprintf(
           Buffer,
           &g_zFileName.atPictureResources[21].zResourceFilename[28],
           Config_zGameOptionsContentControlPW,
           Config_tConfig.zContentControlPassword);
    File_atDevice[v1->eDeviceID].pfWrite(v1->eDeviceID, v1, Buffer, v3);
    for ( i = 0; i < Config_tConfig.nPlayerProfiles; ++i )
      Config_SavePlayerProfile(v1, i);
    File_printf(v1, &g_zFileName.atPictureResources[14].zResourceFilename[12]);
    if ( v1 == &File_tDummyAsyncFile )
      File_tDummyAsyncFile.isAsync = false;
    else
      File_atDevice[v1->eDeviceID].pfDelete(v1->eDeviceID, v1);
    Script_Compile(zConfigFileName);
    if ( AppContext_tAppContext.isQVMUsed )
      File_Remove(zConfigFileName);
  }
}

// source: j/0/config.c:3608  [size]
struct RemapButton_t *__cdecl Config_GetDefaultRemapButtonTable()
{
  return Config_atDefaultRemapButtonTable;
}

// source: j/0/config.c:3621  [size]
unsigned int __cdecl Config_GetDefaultNumRemapButtons()
{
  return 83;
}

// source: j/0/config.c:3634  [size]
struct RemapButton_t *__cdecl Config_GetActivePlayerRemapButtonTable()
{
  return (struct RemapButton_t *)(2752 * Config_tConfig.iActiveProfile + 7392712);
}

// source: j/0/config.c:3649  [anchor-callee]
unsigned int __cdecl Config_GetActivePlayerRemappedButton(unsigned __int64 bInputButton)
{
  unsigned int nRemapButton; // edx
  int v2; // ecx
  struct InputOptions_s *i; // eax

  nRemapButton = Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tInputOptions.nRemapButton;
  v2 = 0;
  if ( !nRemapButton )
    return 0;
  for ( i = &Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tInputOptions;
        i->atRemapButtonTable[0].bInputButton != bInputButton;
        i = (struct InputOptions_s *)((char *)i + 16) )
  {
    if ( ++v2 >= nRemapButton )
      return 0;
  }
  return Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tInputOptions.atRemapButtonTable[v2].nDeviceSource;
}

// source: j/0/config.c:3719  [size~]
unsigned int __cdecl Config_GetInputNameAndCode(
        unsigned int iIndex,
        int *code,
        char **string)
{
  char *LocalizedStringForLanguage; // eax

  LocalizedStringForLanguage = Config_GetLocalizedStringForLanguage(
                                 (char *)(36 * iIndex + 7057096),
                                 Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eLanguage,
                                 true);
  strncpy((char *)string, LocalizedStringForLanguage, code);
  *((_BYTE *)code + (_DWORD)string - 1) = 0;
  return (unsigned int)string;
}

// source: j/0/config.c:3742  [size]
unsigned int __cdecl Config_GetNumInputCodes()
{
  return 113;
}

// source: j/0/config.c:3755  [size]
unsigned int __cdecl Config_GetNumActions()
{
  return 53;
}

// source: j/0/config.c:3768  [size]
float __cdecl Config_GetSoundEffectsVolume()
{
  return Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tSoundOptions.vSoundEffectsVolume;
}

// source: j/0/config.c:3781  [size]
float __cdecl Config_GetMusicVolume()
{
  return Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tSoundOptions.vMusicVolume;
}

// source: j/0/config.c:3794  [size]
float __cdecl Config_GetSpeechVolume()
{
  return Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tSoundOptions.vSpeechVolume;
}

// source: j/0/config.c:3807  [size]
enum GameLanguage_e __cdecl Config_GetActiveGameLanguage()
{
  return Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eLanguage;
}

// source: j/0/config.c:3820  [size]
void __cdecl Config_SetActiveGameLanguage(enum GameLanguage_e eLanguage)
{
  Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eLanguage = eLanguage;
  Config_SetConfig();
}

// source: j/0/config.c:3836  [size]
unsigned int __cdecl Config_GetNumLanguages()
{
  return 6;
}

// source: j/0/config.c:3849  [size]
char *__cdecl Config_GetLanguageName(int iLanguageIndex)
{
  return (char *)(16 * iLanguageIndex + 6828784);
}

// source: j/0/config.c:3862  [anchor-callee]
char *__cdecl Config_GetLocalizedStringForLanguage(
        char *zResourceName,
        enum GameLanguage_e eGameLanguage,
        enum bool isExists)
{
  #pragma pack(push, 1)
  union
  {
    struct { char zFilename[4]; };
    struct { char igi2_o1[4]; char Source[256]; };
    char igi2_extent[260];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  unsigned int v3; // eax
  char *v4; // edi
  char *v6; // ecx
  void *v7; // eax
  char *v9; // ecx
  unsigned int v10; // eax
  struct MissingResource_s *v11; // esi

  strcpy(igi2_frame.Source, "GLOBAL:");
  v3 = strlen(zResourceName) + 1;
  v4 = &igi2_frame.zFilename[3];
  while ( *++v4 )
    ;
  qmemcpy(v4, zResourceName, v3);
  if ( Resource_IsLoadedInternal(igi2_frame.Source, nullptr) )
  {
    if ( Resource_IsLoadedInternal(igi2_frame.Source, (struct Resource_s **)igi2_frame.zFilename) == false )
    {
      Game_MPRunNetwork(v6);
      v7 = File_Load(igi2_frame.Source, (unsigned int *)igi2_frame.zFilename);
      if ( !v7 )
        goto LABEL_6;
      return (char *)Resource_ParseFile(File_zLastSubstitutedPath, v7, *(unsigned int *)igi2_frame.zFilename);
    }
LABEL_10:
    v10 = *(_DWORD *)igi2_frame.zFilename;
    *(_DWORD *)(*(_DWORD *)igi2_frame.zFilename + 44) = 1;
    return *(char **)(v10 + 52);
  }
  strcpy(igi2_frame.Source, "LOCAL:");
  strncat(igi2_frame.Source, (char *)(16 * eGameLanguage + 6828784), 0x100u);
  strncat(igi2_frame.Source, &g_zFileName.atPictureResources[13].zResourceFilename[60], 0x100u);
  strncat(igi2_frame.Source, zResourceName, 0x100u);
  if ( Resource_IsLoadedInternal(igi2_frame.Source, nullptr) )
  {
    if ( Resource_IsLoadedInternal(igi2_frame.Source, (struct Resource_s **)igi2_frame.zFilename) == false )
    {
      Game_MPRunNetwork(v9);
      v7 = File_Load(igi2_frame.Source, (unsigned int *)igi2_frame.zFilename);
      if ( !v7 )
      {
LABEL_6:
        LDebug_Error("Failed to load resource: '%s'", igi2_frame.Source);
        abort();
      }
      return (char *)Resource_ParseFile(File_zLastSubstitutedPath, v7, *(unsigned int *)igi2_frame.zFilename);
    }
    goto LABEL_10;
  }
  if ( isExists == false )
    return nullptr;
  v11 = ptMissingResourceList;
  if ( !ptMissingResourceList )
    goto LABEL_19;
  while ( strncmp(v11->zName, igi2_frame.Source, 0x100u) )
  {
    v11 = v11->ptNext;
    if ( !v11 )
      goto LABEL_19;
  }
  if ( !v11 )
  {
LABEL_19:
    v11 = (struct MissingResource_s *)Mem_AllocFn(516, 4);
    strncpy(v11->zName, igi2_frame.Source, 0x100u);
    v11->zString[0] = 0;
    strncat(v11->zString, zResourceName, 0x100u);
    v11->ptNext = ptMissingResourceList;
    ptMissingResourceList = v11;
  }
  return v11->zString;
}

// source: j/0/config.c:3950  [anchor-callee]
char *__cdecl Config_GetLocalizedString(char *zResourceName)
{
  return Config_GetLocalizedStringForLanguage(
           zResourceName,
           Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eLanguage,
           true);
}

// source: j/0/config.c:3963  [anchor-callee]
void __cdecl Config_SetLocalizedPhrase(
        char *zText,
        char *zFormatText,
        char *zPlayer1,
        char *zPlayer2,
        char *zEnd)
{
  #pragma pack(push, 1)
  union
  {
    struct { char *v10; };
    struct { char igi2_o1[4]; char *v11; };
    struct { char igi2_o2[8]; char zTranslatedText[256]; };
    char igi2_extent[264];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  char *LocalizedStringForLanguage; // eax
  char *v6; // esi
  char *v7; // edi
  char v8; // bl
  char v9; // al

  *zText = 0;
  LocalizedStringForLanguage = Config_GetLocalizedStringForLanguage(
                                 zFormatText,
                                 Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eLanguage,
                                 true);
  strncpy(igi2_frame.zTranslatedText, LocalizedStringForLanguage, 0xFFu);
  if ( igi2_frame.zTranslatedText[0] )
  {
    v6 = igi2_frame.zTranslatedText;
    v7 = &igi2_frame.zTranslatedText[1];
    igi2_frame.v10 = igi2_frame.zTranslatedText;
    igi2_frame.v11 = &igi2_frame.zTranslatedText[1];
    do
    {
      if ( *v6 == 47 )
      {
        v8 = *v7;
        if ( *v7 == 49 )
        {
          strcat(zText, zPlayer1);
          v6 = igi2_frame.v10;
        }
        if ( v8 == 50 )
        {
          strcat(zText, zPlayer2);
          v6 = igi2_frame.v10;
        }
        v7 = igi2_frame.v11 + 1;
        ++v6;
      }
      else
      {
        strncat(zText, v6, 1u);
      }
      v9 = v6[1];
      ++v7;
      ++v6;
      igi2_frame.v11 = v7;
      igi2_frame.v10 = v6;
    }
    while ( v9 );
  }
  if ( zEnd )
  {
    strcat(zText, " [");
    strcat(zText, zEnd);
    *(_WORD *)&zText[strlen(zText)] = *(_WORD *)&g_zFileName.atPictureResources[13].zResourceFilename[52];
  }
}

// source: j/0/config.c:4011  [size]
char *__cdecl Config_GetDifficultyName(int iDifficultyIndex)
{
  return (char *)(16 * iDifficultyIndex + 6828880);
}

// source: j/0/config.c:4024  [anchor-callee]
void __cdecl Config_UpdateActiveMissionID(int nActiveMissionID)
{
  struct Node_s *ptNext; // eax
  struct Node_s *v2; // ecx
  struct Node_s *ptHead; // esi
  int v4; // edx
  struct Node_s *v5; // ecx
  int v6; // eax
  enum GameDifficulty_e eDifficultyLevel; // esi
  __int32 v8; // ecx
  int v9; // edx
  int *v10; // ecx
  enum GameDifficulty_e v11; // edx
  __int32 v12; // ecx
  int v13; // edi
  int *v14; // ecx

  ptNext = Mission_tMissionList.ptHead->ptNext;
  v2 = Mission_tMissionList.ptHead->ptNext;
  ptHead = Mission_tMissionList.ptHead;
  if ( Mission_tMissionList.ptHead->ptNext )
  {
    while ( ptHead[1].ptNext != (struct Node_s *)nActiveMissionID )
    {
      ptHead = v2;
      v2 = v2->ptNext;
      if ( !v2 )
        return;
    }
    v4 = 0;
    v5 = Mission_tMissionList.ptHead;
    if ( ptNext )
    {
      while ( ptHead != v5 )
      {
        v5 = ptNext;
        ptNext = ptNext->ptNext;
        ++v4;
        if ( !ptNext )
          goto LABEL_8;
      }
      v6 = v4;
    }
    else
    {
LABEL_8:
      v6 = -1;
    }
    eDifficultyLevel = Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eDifficultyLevel;
    v8 = eDifficultyLevel + 688 * Config_tConfig.iActiveProfile;
    v9 = Config_tConfig.atPlayerProfile[0].anActiveMission[v8];
    v10 = (int *)(4 * v8 + 7394808);
    if ( v9 < v6 )
    {
      v11 = GAMEDIFFICULTY_1;
      for ( *v10 = v6; v11 < eDifficultyLevel; ++v11 )
      {
        v12 = v11 + 688 * Config_tConfig.iActiveProfile;
        v13 = Config_tConfig.atPlayerProfile[0].anActiveMission[v12];
        v14 = (int *)(4 * v12 + 7394808);
        if ( v13 < v6 )
          *v14 = v6;
      }
    }
  }
}

// source: j/0/config.c:4067  [anchor-caller]
void __cdecl Config_SetGameToCurrentPerformanceLevel()
{
  #pragma pack(push, 1)
  union
  {
    struct { float vGamma; };
    struct { char igi2_o1[20]; struct SetLODContext_t tSetLODContext; };
    char igi2_extent[24];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v0; // ebx
  void *v1; // esi
  double v2; // st7
  enum Direct3DRender_FilteringType_e v3; // esi
  int v4; // eax
  int v5; // eax
  int v6; // esi
  int v7; // eax
  float v8; // ecx
  int nMaxAntialiasingLevel32; // eax
  int v10; // ebx

  v0 = 2752 * Config_tConfig.iActiveProfile + 7392072;
  v1 = (void *)(2752 * Config_tConfig.iActiveProfile + 7392088);
  GfxOptions_eDetailLevel = Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGraphicOptions.eDetailLevel;
  if ( GfxOptions_eDetailLevel != GFXOPTIONS_DETAIL_CUSTOM || 2752 * Config_tConfig.iActiveProfile == -7392088 )
    v1 = (void *)(40 * GfxOptions_eDetailLevel + 6828624);
  qmemcpy(&GfxOptions_tActiveOptions, v1, sizeof(GfxOptions_tActiveOptions));
  if ( GfxOptions_tActiveOptions.eTextureDetail == GFXOPTIONS_TEXTUREDETAIL_LOW )
  {
    igi2_frame.tSetLODContext.nLOD = 1;
  }
  else if ( GfxOptions_tActiveOptions.eTextureDetail == GFXOPTIONS_TEXTUREDETAIL_ULTRALOW )
  {
    igi2_frame.tSetLODContext.nLOD = 2;
  }
  else
  {
    igi2_frame.tSetLODContext.nLOD = 0;
  }
  RenderMode_tActiveRenderMode.apfRenderModeMethod[Texture_eSetLODMethod](&igi2_frame.tSetLODContext);
  v2 = 1.0 - GfxOptions_tActiveOptions.vModelDetail;
  ModelObj_vLODBias = v2;
  igi2_frame.vGamma = Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGraphicOptions.vGamma;
  ModelObj_vActualLODBiasSquared = (v2 * 4.0 + 1.0) * (v2 * 4.0 + 1.0);
  Config_SetGamma(igi2_frame.vGamma);
  Texture_isCompression = GfxOptions_tActiveOptions.isTextureCompression;
  ForestRender_isAlphaBlend = GfxOptions_tActiveOptions.isHighQualityForests;
  v3 = *(_DWORD *)(v0 + 612);
  ForestRender_isWind = GfxOptions_tActiveOptions.isWindOnForests;
  v4 = *(char *)(v0 + 68);
  GunShot_isDisableGunShotEffects = GfxOptions_tActiveOptions.isBulletHitEffects == false;
  LensflareQTask_isDisabled = GfxOptions_tActiveOptions.isLensFlares == false;
  Direct3D_isSoftwareVS = v4;
  if ( v3 >= Direct3DRender_SetFilteringMode(v3) )
    v5 = Direct3DRender_SetFilteringMode(v3);
  else
    v5 = v3;
  v6 = *(_DWORD *)(v0 + 48);
  *(_DWORD *)(v0 + 612) = v5;
  if ( v6 >= WaterRender_SetQualityLevel(v6) )
    v7 = WaterRender_SetQualityLevel(v6);
  else
    v7 = v6;
  v8 = *(float *)(v0 + 52);
  *(_DWORD *)(v0 + 48) = v7;
  nMaxAntialiasingLevel32 = Direct3D_tAntialiasingCaps.nMaxAntialiasingLevel32;
  v10 = 2 * *(_DWORD *)(v0 + 608);
  Terrain_vManualDetail = v8;
  if ( v10 < Direct3D_tAntialiasingCaps.nMaxAntialiasingLevel32 )
    nMaxAntialiasingLevel32 = v10;
  Direct3D_nAntialiasingLevel = 2 * (nMaxAntialiasingLevel32 / 2);
}

// source: j/0/config.c:4121  [size]
int __cdecl Config_GetActivePlayerProfileIndex()
{
  return Config_tConfig.iActiveProfile;
}

// source: j/0/config.c:4240  [anchor-callee]
struct HumanMissionScoreData_s *__cdecl Config_GetMissionStats(int iMissionID)
{
  struct QHashTable_s *ptMissionStatsHashTable; // esi
  int v2; // eax

  sprintf(byte_70CB00, &g_zFileName.atPictureResources[22].zResourceFilename[32], iMissionID);
  ptMissionStatsHashTable = Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].ptMissionStatsHashTable;
  v2 = ptMissionStatsHashTable->tPrivate.pfHashFunction(ptMissionStatsHashTable->tPrivate.nHashTableSize, byte_70CB00);
  return ((struct HumanMissionScoreData_s * (__cdecl *)(struct QHashTable_s *, unsigned int, const void *))ptMissionStatsHashTable->tPrivate.pfFindElement)(ptMissionStatsHashTable, v2, (const void *)(byte_70CB00));
}

// source: j/0/config.c:4266  [anchor-callee]
struct MissionScoreSettings_s *__cdecl Config_GetMissionScoreSettings(int iMissionID)
{
  struct QHashTable_s *ptMissionStatsHashTable; // esi
  int v2; // eax
  int v3; // eax

  sprintf(byte_70CB00, &g_zFileName.atPictureResources[22].zResourceFilename[32], iMissionID);
  ptMissionStatsHashTable = Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].ptMissionStatsHashTable;
  v2 = ptMissionStatsHashTable->tPrivate.pfHashFunction(ptMissionStatsHashTable->tPrivate.nHashTableSize, byte_70CB00);
  v3 = ((int  (__cdecl *)(struct QHashTable_s *, unsigned int, const void *))ptMissionStatsHashTable->tPrivate.pfFindElement)(ptMissionStatsHashTable, v2, (const void *)(byte_70CB00));
  if ( v3 )
    return (struct MissionScoreSettings_s *)(v3 + 40);
  else
    return nullptr;
}

// source: j/0/config.c:4291  [anchor-strings]
struct HumanMissionScoreData_s *__cdecl Config_UpdateMissionStats(
        struct HumanMissionScoreData_s *ptHumanMissionScoreData,
        struct MissionScoreSettings_s *ptMissionScoreSettings)
{
  struct QHashTable_s *ptMissionStatsHashTable; // edi
  int v4; // eax
  struct HumanMissionScoreData_s *v5; // edi
  struct HumanMissionScoreData_s *result; // eax
  struct HumanMissionScoreData_s *v7; // ebx
  struct QHashTable_s *v8; // edi
  int v9; // eax

  sprintf(byte_70CB00, &g_zFileName.atPictureResources[22].zResourceFilename[32], ptHumanMissionScoreData->iMissionID);
  ptMissionStatsHashTable = Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].ptMissionStatsHashTable;
  v4 = ptMissionStatsHashTable->tPrivate.pfHashFunction(ptMissionStatsHashTable->tPrivate.nHashTableSize, byte_70CB00);
  v5 = (struct HumanMissionScoreData_s *)((int  (__cdecl *)(struct QHashTable_s *, unsigned int, const void *))ptMissionStatsHashTable->tPrivate.pfFindElement)(ptMissionStatsHashTable, v4, (const void *)(byte_70CB00));
  result = (struct HumanMissionScoreData_s *)Config_GetMissionScoreSettings(ptHumanMissionScoreData->iMissionID);
  if ( !v5 )
  {
    v7 = (struct HumanMissionScoreData_s *)Mem_AllocFn(140, 4);
    sprintf(byte_70CB00, &g_zFileName.atPictureResources[22].zResourceFilename[32], ptHumanMissionScoreData->iMissionID);
    v8 = Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].ptMissionStatsHashTable;
    v9 = v8->tPrivate.pfHashFunction(v8->tPrivate.nHashTableSize, byte_70CB00);
    v8->tPrivate.pfCreateElement(v8, v9, (const void *)(byte_70CB00), (const void *)(v7));
    v5 = v7;
    result = v7 + 1;
  }
  qmemcpy(v5, ptHumanMissionScoreData, sizeof(struct HumanMissionScoreData_s));
  qmemcpy(result, ptMissionScoreSettings, 0x64u);
  return result;
}

// source: j/0/config.c:4336  [anchor-mhash]
void __cdecl Config_EnumerateMissionStatsCallback(
        struct QHashTable_s *ptHashTable,
        char *zKey,
        struct ConfigMissionStats_s *ptConfigMissionStats,
        struct ConfigMissionStatsEnumContext_s *ptContext)
{
  ptContext->pfCallback(ptConfigMissionStats, ptContext->pxContext);
}

// source: j/0/config.c:4349  [anchor-mhash]
void __cdecl Config_EnumerateMissionStats(
        void (__cdecl *pfCallback)(struct HumanMissionScoreData_s *, void *),
        void *pxContext)
{
  struct QHashTable_s *ptMissionStatsHashTable; // eax
  struct ConfigMissionStatsEnumContext_s tContext; // [esp+0h] [ebp-8h] BYREF

  tContext.pfCallback = pfCallback;
  ptMissionStatsHashTable = Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].ptMissionStatsHashTable;
  tContext.pxContext = pxContext;
  if ( ptMissionStatsHashTable->tPrivate.nEntries )
    ptMissionStatsHashTable->tPrivate.pfMap(
      ptMissionStatsHashTable,
      (void (__cdecl *)(struct QHashTable_s *, void *, void *, void *))Config_EnumerateMissionStatsCallback,
      &tContext);
}

// source: j/0/config.c:4370  [size]
int __cdecl Config_GetActiveMission()
{
  return Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].anActiveMission[Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eDifficultyLevel];
}

// source: j/0/config.c:4383  [size]
void __cdecl Config_HideInventory(enum bool isHideInventory)
{
  Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.isHideInventory = isHideInventory;
}

// source: j/0/config.c:4396  [size]
enum bool __cdecl Config_IsInventoryHidden()
{
  return Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.isHideInventory;
}

// source: j/0/config.c:4409  [anchor-mhash]
struct PlayerProfile_s *__cdecl Config_GetPlayerProfileBeingProcessed()
{
  if ( Config_tConfig.nPlayerProfiles )
    return (struct PlayerProfile_s *)(&Config_atDisplayDevice[4].tDisplayModeList[33].nHeight
                                    + 688 * Config_tConfig.nPlayerProfiles);
  else
    return nullptr;
}

// source: j/0/config.c:4426  [anchor-strings]
struct Result_s *__cdecl Config_GetCrossHairs(
        struct Result_s *retstr,
        void *pxUnUsed,
        struct ArgList_s *ptArgList)
{
  struct Result_s Rs; // [esp+Ch] [ebp-18h] BYREF

  PictureBox_AddItem(&g_zFileName.atPictureResources[13].zResourceFilename[36], 0);
  PictureBox_AddItem(&g_zFileName.atPictureResources[13].zResourceFilename[20], 1);
  Rs.nResult = 0;
  Rs.vResult = 0.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/config.c:4442  [anchor-mhash]
struct Result_s *__cdecl Config_GetActiveCrossHair(
        struct Result_s *retstr,
        void *pxUnUsed,
        struct ArgList_s *ptArgList)
{
  double v3; // st7
  struct Result_s *result; // eax
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  v3 = *((float *)&Config_atDisplayDevice[4].tDisplayModeList[82].nWidth + 688 * Config_tConfig.nPlayerProfiles);
  Rs.zResult = (char *)&g_zInitialValue;
  LODWORD(Rs.vResult) = 0;
  result = retstr;
  if ( v3 == 2.0 )
  {
    Rs.nResult = 1;
    HIDWORD(Rs.vResult) = 1072693248;
  }
  else
  {
    Rs.nResult = 0;
    HIDWORD(Rs.vResult) = 0;
  }
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return result;
}

// source: j/0/config.c:4462  [anchor-mhash]
struct Result_s *__cdecl Config_GetRGBA(
        struct Result_s *retstr,
        void *pxUnUsed,
        struct ArgList_s *ptArgList)
{
  double vCrossHairAlpha; // st7
  double vCrossHairB; // st6
  double vCrossHairG; // st5
  double vCrossHairR; // st4
  struct PictureBox_s *v7; // eax
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  vCrossHairAlpha = Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGraphicOptions.vCrossHairAlpha;
  vCrossHairB = Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGraphicOptions.vCrossHairB;
  vCrossHairG = Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGraphicOptions.vCrossHairG;
  Rs.nResult = 0;
  vCrossHairR = Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGraphicOptions.vCrossHairR;
  v7 = PictureBox_ptActivePictureBox;
  LODWORD(Rs.vResult) = 0;
  PictureBox_ptActivePictureBox->vR = vCrossHairR;
  HIDWORD(Rs.vResult) = 0;
  Rs.zResult = (char *)&g_zInitialValue;
  v7->vG = vCrossHairG;
  v7->vB = vCrossHairB;
  v7->vA = vCrossHairAlpha;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/config.c:4481  [anchor-caller]
struct Result_s *__cdecl Config_LoadConfig(
        struct Result_s *retstr,
        void *pxUnUsed,
        struct ArgList_s *ptArgList)
{
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  Config_Load("LOCAL:config.qsc");
  Rs.nResult = 0;
  Rs.vResult = 0.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/config.c:4496  [anchor-mhash]
struct Result_s *__cdecl Config_SaveConfig(
        struct Result_s *retstr,
        void *pxUnUsed,
        struct ArgList_s *ptArgList)
{
  struct Result_s Rs; // [esp+Ch] [ebp-18h] BYREF

  Config_Save("LOCAL:config.qsc");
  Rs.nResult = 0;
  Rs.vResult = 0.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/config.c:4511  [size~]
void __cdecl Config_Open()
{
  #pragma pack(push, 1)
  union
  {
    struct { int v27; };
    struct { char igi2_o1[4]; _DWORD v28[3]; };
    struct { char igi2_o2[16]; _BYTE v29[1280]; };
    char igi2_extent[1296];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct ConfigInputButton_s *v0; // ebx
  int v1; // edi
  char *v2; // ecx
  unsigned int i; // eax
  struct ConfigInputPortDevice_s *v4; // ebx
  int v5; // esi
  struct ConfigDeviceSource_s *v6; // ebx
  int v7; // esi
  char *v8; // esi
  char *v9; // ebx
  char *v10; // esi
  char *v11; // ebx
  enum RenderMode_enum v12; // ebp
  void (__cdecl *v13)(void *); // eax
  int v14; // ebx
  int *p_nNumDisplayModes; // eax
  _BYTE *v16; // edx
  int *v17; // edi
  void *v18; // esi
  struct DisplayMode_s *v19; // esi
  int v20; // edi
  enum RenderMode_enum v21; // eax
  void *v22; // eax
  unsigned int v23; // ebx
  struct GfxOptions_s *p_tGfxOptions; // edx
  int v25; // ebp
  struct GfxOptions_s *v26; // edi

  Symbol_Register(
    Config_zGameOptionsStart,
    Config_GameOptionsStart,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    Config_zGameOptionsPlayer,
    Config_GameOptionsPlayer,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    Config_zGameOptionsInputRemapButton,
    Config_GameOptionsInputRemapButton,
    nullptr,
    3,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    Config_zGameOptionsInputInvertMouse,
    Config_GameOptionsInputInvertMouse,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    Config_zGameOptionsInputMouseSentivity,
    Config_GameOptionsInputMouseSensitivity,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    Config_zGameOptionsGraphicDisplay,
    Config_GameOptionsGraphicDisplay,
    nullptr,
    3,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    Config_zGameOptionsGraphicDevice,
    Config_GameOptionsGraphicDevice,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    Config_zGameOptionsGraphicGamma,
    Config_GameOptionsGraphicGamma,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    Config_zGameOptionsGraphicCrossHairAlpha,
    Config_GameOptionsGraphicCrossHairAlpha,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    Config_zGameOptionsGameLanguage,
    Config_GameOptionsGameLanguage,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    Config_zGameOptionsGameDifficultyLevel,
    Config_GameOptionsGameDifficultyLevel,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    Config_zGameOptionsGameBlood,
    Config_GameOptionsGameBlood,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    Config_zGameOptionsGameIsHideInventory,
    Config_GameOptionsIsHideInventory,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    Config_zGameOptionsSoundSpeech,
    Config_GameOptionsSoundsSpeech,
    nullptr,
    2,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    Config_zGameOptionsSoundMusic,
    Config_GameOptionsSoundsMusic,
    nullptr,
    2,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    Config_zGameOptionsSoundFX,
    Config_GameOptionsSoundsFX,
    nullptr,
    2,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    Config_zGameOptions3DProvider,
    Config_GameOptions3DSoundProvider,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    off_6BA0C4,
    sub_42A160,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    Config_zGameOptionsActiveMission,
    Config_GameOptionsActiveMission,
    nullptr,
    2,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    Config_zGameOptionsContentControlPW,
    Config_GameOptionsContentControlPW,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    Config_zGameOptionsPlayerMissionStats,
    Config_ParsePlayerMissionData,
    nullptr,
    25,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    Config_zGameOptionsGraphicCrossHairThickness,
    Config_GameOptionsCrosshairThickness,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    Config_zGameOptionsGraphicCrossHairColour,
    Config_GameOptionsCrosshairColour,
    nullptr,
    3,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    Config_zGameOptionsGraphicForceSoftwareVP,
    Config_GameOptionsForceSoftwareVertexProcessing,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &g_zFileName.atPictureResources[13].zResourceFilename[8],
    Config_ParseVersion,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &g_zFileName.atPictureResources[12].zResourceFilename[44],
    Config_FillPlayerProfileListBox,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &g_zFileName.atPictureResources[12].zResourceFilename[8],
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Config_GetActivePlayerProfileIndexScriptFunction,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &g_zFileName.atPictureResources[11].zResourceFilename[40],
    Config_SetActivePlayerProfileIndexScriptFunction,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &g_zFileName.atPictureResources[11].zResourceFilename[8],
    Config_CreateNewPlayerProfile,
    nullptr,
    2,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &g_zFileName.atPictureResources[10].zResourceFilename[48],
    Config_DeletePlayerProfile,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &g_zFileName.atPictureResources[10].zResourceFilename[16],
    Config_PlayerGetActiveMission,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &g_zFileName.atPictureResources[9].zResourceFilename[48],
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Config_GetNumberOfPlayerProfiles,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &g_zFileName.atPictureResources[9].zResourceFilename[12],
    Config_FillDifficultyLevelListBox,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &g_zFileName.atPictureResources[8].zResourceFilename[48],
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Config_GetActiveDifficultyLevelScriptFunction,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &g_zFileName.atPictureResources[8].zResourceFilename[16],
    Config_SetActiveDifficultyLevelScriptFunction,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &g_zFileName.atPictureResources[7].zResourceFilename[48],
    Config_Fill3DProviderScrollListBox,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &g_zFileName.atPictureResources[7].zResourceFilename[20],
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Config_GetActive3DProvider,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &g_zFileName.atPictureResources[6].zResourceFilename[60],
    Config_SetActive3DProvider,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &g_zFileName.atPictureResources[6].zResourceFilename[28],
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))sub_42A050,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    (char *)&g_zFileName.atPictureResources[5].ptPicture,
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))sub_42A500,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &g_zFileName.atPictureResources[5].zResourceFilename[32],
    sub_42A550,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    g_zFileName.atPictureResources[5].zResourceFilename,
    Config_FillMissionSelectionBox,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &g_zFileName.atPictureResources[4].zResourceFilename[36],
    Config_FillMissionPictureBox,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &g_zFileName.atPictureResources[4].zResourceFilename[8],
    Config_FillMissionTextBox,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &g_zFileName.atPictureResources[3].zResourceFilename[40],
    Config_FillScreenResolutionListBox,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &g_zFileName.atPictureResources[3].zResourceFilename[8],
    Config_FillRenderDeviceListBox,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &g_zFileName.atPictureResources[2].zResourceFilename[52],
    Config_TestFillListBox,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &g_zFileName.atPictureResources[2].zResourceFilename[28],
    Config_LanguageScriptCB,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &g_zFileName.atPictureResources[1].zResourceFilename[56],
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Config_GameOptionsInputGetInvertMouse,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &g_zFileName.atPictureResources[1].zResourceFilename[12],
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Config_GameOptionsInputGetMouseSensitivity,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &g_zFileName.atPictureResources[0].zResourceFilename[40],
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Config_GameOptionsInputGetBloodEnabled,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    (char *)&g_zFileName.atSpriteResources[63].tSprite.nQAnimframes,
    Config_GameOptionsGraphicsSetThickCrosshair,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &g_zFileName.atSpriteResources[63].zResourceFilename[40],
    Config_GameOptionsGraphicsGetThickCrosshair,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    (char *)&g_zFileName.atSpriteResources[62].tSprite.atQAnimframe,
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Config_GameOptionsGfxGetForceSoftwareVertexProcessing,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &g_zFileName.atSpriteResources[62].zResourceFilename[16],
    Config_GameOptionsGfxSetForceSoftwareVertexProcessing,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    (char *)&g_zFileName.atSpriteResources[61].tSprite,
    Config_GameOptionsInputSetInvertMouse,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &g_zFileName.atSpriteResources[61].zResourceFilename[20],
    Config_GameOptionsInputSetMouseSensitivity,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    (char *)&g_zFileName.atSpriteResources[60].tSprite.atTexInfo,
    Config_GameOptionsInputSetBloodEnabled,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &g_zFileName.atSpriteResources[60].zResourceFilename[32],
    Config_GraphicOptionsSetResolution,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    (char *)&g_zFileName.atSpriteResources[59].tSprite.nTextures,
    Config_GraphicOptionsSetTransparency,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &g_zFileName.atSpriteResources[59].zResourceFilename[48],
    Config_GraphicOptionsSetDevice,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &g_zFileName.atSpriteResources[59].zResourceFilename[16],
    Config_GraphicOptionsSetGamma,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_FLOAT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    (char *)&g_zFileName.atSpriteResources[58].tSprite.atTexInfo,
    Config_GraphicOptionsGetResolution,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &g_zFileName.atSpriteResources[58].zResourceFilename[28],
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Config_GraphicOptionsGetTransparency,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    (char *)&g_zFileName.atSpriteResources[57].tSprite.nQAnimframes,
    Config_GraphicOptionsGetDevice,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &g_zFileName.atSpriteResources[57].zResourceFilename[52],
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Config_GraphicOptionsGetGamma,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &g_zFileName.atSpriteResources[57].zResourceFilename[12],
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Config_GraphicOptionsGetCrossHairAlpha,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &g_zFileName.atSpriteResources[56].zResourceFilename[60],
    Config_GraphicOptionsSetCrossHairAlpha,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &g_zFileName.atSpriteResources[56].zResourceFilename[16],
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Config_GraphicOptionsGetCrossHairColourR,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &g_zFileName.atSpriteResources[55].zResourceFilename[60],
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Config_GraphicOptionsGetCrossHairColourG,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &g_zFileName.atSpriteResources[55].zResourceFilename[16],
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Config_GraphicOptionsGetCrossHairColourB,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &g_zFileName.atSpriteResources[54].zResourceFilename[60],
    Config_GraphicOptionsSetCrossHairColourR,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &g_zFileName.atSpriteResources[54].zResourceFilename[16],
    Config_GraphicOptionsSetCrossHairColourG,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &g_zFileName.atSpriteResources[53].zResourceFilename[60],
    Config_GraphicOptionsSetCrossHairColourB,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &g_zFileName.atSpriteResources[53].zResourceFilename[24],
    Config_SoundOptionsSetSoundEffects,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    (char *)&g_zFileName.atSpriteResources[52].tSprite.atTexInfo,
    Config_SoundOptionsSetSoundEffectsVolume,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &g_zFileName.atSpriteResources[52].zResourceFilename[40],
    Config_SoundOptionsSetMusic,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &g_zFileName.atSpriteResources[52].zResourceFilename[4],
    Config_SoundOptionsSetMusicVolume,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &g_zFileName.atSpriteResources[51].zResourceFilename[60],
    Config_SoundOptionsSetSpeech,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &g_zFileName.atSpriteResources[51].zResourceFilename[24],
    Config_SoundOptionsSetSpeechVolume,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    (char *)&g_zFileName.atSpriteResources[50].tSprite.ptQTilemap,
    Config_SoundOptionsSetReverseStereo,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &g_zFileName.atSpriteResources[50].zResourceFilename[40],
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Config_SoundOptionsGetSoundEffects,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    (char *)&g_zFileName.atSpriteResources[49].tSprite.nQAnimframes,
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Config_SoundOptionsGetSoundEffectsVolume,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &g_zFileName.atSpriteResources[49].zResourceFilename[56],
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Config_SoundOptionsGetMusic,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &g_zFileName.atSpriteResources[49].zResourceFilename[20],
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Config_SoundOptionsGetMusicVolume,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    (char *)&g_zFileName.atSpriteResources[48].tSprite.ptQTilemap,
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Config_SoundOptionsGetSpeech,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &g_zFileName.atSpriteResources[48].zResourceFilename[40],
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Config_SoundOptionsGetSpeechVolume,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &g_zFileName.atSpriteResources[48].zResourceFilename[4],
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Config_SoundOptionsGetReverseStereo,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &g_zFileName.atSpriteResources[47].zResourceFilename[56],
    Config_SetContentControlPassword,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &g_zFileName.atSpriteResources[47].zResourceFilename[20],
    Config_GetContentControlPassword,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    (char *)&g_zFileName.atSpriteResources[46].tSprite.atQAnimframe,
    Config_VerifyContentControlPassword,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &g_zFileName.atSpriteResources[46].zResourceFilename[32],
    Config_IsContentControlPasswordEnabled,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &g_zFileName.atSpriteResources[46].zResourceFilename[12],
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Config_IsGermany,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    (char *)&g_zFileName.atSpriteResources[45].tSprite.atQAnimframe,
    Config_ResetGraphicOptions,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &g_zFileName.atSpriteResources[45].zResourceFilename[48],
    Config_GetCrossHairs,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &g_zFileName.atSpriteResources[45].zResourceFilename[20],
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Config_GetActiveCrossHair,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &g_zFileName.atSpriteResources[45].zResourceFilename[4],
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Config_GetRGBA,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    (char *)&g_zFileName.atSpriteResources[44].tSprite.atQAnimframe,
    Config_LoadConfig,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &g_zFileName.atSpriteResources[44].zResourceFilename[52],
    Config_SaveConfig,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &g_zFileName.atSpriteResources[44].zResourceFilename[32],
    nullptr,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  v0 = Config_atInputButton;
  v1 = 53;
  do
  {
    v2 = nullptr;
    for ( i = 0; i < 53; ++i )
    {
      if ( __PAIR64__(HIDWORD(Config_atInputButton[i].bInputButton), Config_atInputButton[i].bInputButton) == v0->bInputButton )
      {
        v22 = v2;
        goto LABEL_7;
      }
      ++v2;
    }
    v22 = nullptr;
LABEL_7:
    Symbol_Register(
      v0->zButton,
      (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
      v22,
      4,
      QSCRIPT_SYMBOLCLASS_CONSTANT,
      QSCRIPT_SYMBOLTYPE_INT,
      QSCRIPT_SYMBOLLIFESPAN_INFINITE);
    ++v0;
    --v1;
  }
  while ( v1 );
  Symbol_Register(
    &g_zFileName.atSpriteResources[44].zResourceFilename[20],
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)0xFFFFFFFF,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  v4 = Config_atInputPortDevice;
  v5 = 3;
  do
  {
    Symbol_Register(
      v4->zInputPortDevice,
      (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
      (void *)v4->eInputPortDevice,
      4,
      QSCRIPT_SYMBOLCLASS_CONSTANT,
      QSCRIPT_SYMBOLTYPE_INT,
      QSCRIPT_SYMBOLLIFESPAN_INFINITE);
    ++v4;
    --v5;
  }
  while ( v5 );
  v6 = Config_atDeviceSource;
  v7 = 113;
  do
  {
    Symbol_Register(
      v6->zDeviceSource,
      (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
      (void *)v6->nDeviceSource,
      4,
      QSCRIPT_SYMBOLCLASS_CONSTANT,
      QSCRIPT_SYMBOLTYPE_INT,
      QSCRIPT_SYMBOLLIFESPAN_INFINITE);
    ++v6;
    --v7;
  }
  while ( v7 );
  v8 = nullptr;
  v9 = Config_azGameLanguage;
  do
  {
    Symbol_Register(
      v9,
      (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
      v8,
      4,
      QSCRIPT_SYMBOLCLASS_CONSTANT,
      QSCRIPT_SYMBOLTYPE_INT,
      QSCRIPT_SYMBOLLIFESPAN_INFINITE);
    v9 += 16;
    ++v8;
  }
  while ( (int)v9 < 6828880 );
  v10 = nullptr;
  v11 = Config_azGameDifficulty;
  do
  {
    Symbol_Register(
      v11,
      (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
      v10,
      4,
      QSCRIPT_SYMBOLCLASS_CONSTANT,
      QSCRIPT_SYMBOLTYPE_INT,
      QSCRIPT_SYMBOLLIFESPAN_INFINITE);
    v11 += 16;
    ++v10;
  }
  while ( (int)v11 < 6828928 );
  v12 = RenderMode_eActiveRenderMode;
  RenderMode_aeRenderModeStack[--RenderMode_nSP] = RenderMode_eActiveRenderMode;
  if ( Direct3D_eRenderMode != v12 )
  {
    v12 = Direct3D_eRenderMode;
    qmemcpy(
      &RenderMode_tActiveRenderMode,
      (void *)(520 * Direct3D_eRenderMode + 139167712),
      sizeof(RenderMode_tActiveRenderMode));
    RenderMode_eActiveRenderMode = Direct3D_eRenderMode;
  }
  igi2_frame.v28[1] = &igi2_frame.v27;
  v13 = RenderMode_tActiveRenderMode.apfRenderModeMethod[Display_eEnumDevicesMethod];
  v14 = 0;
  igi2_frame.v27 = 0;
  igi2_frame.v28[0] = igi2_frame.v29;
  igi2_frame.v28[2] = 5;
  if ( v13 )
  {
    v13(igi2_frame.v28);
    v12 = RenderMode_eActiveRenderMode;
    v14 = igi2_frame.v27;
  }
  Config_nNumDisplayDevices = v14;
  if ( v14 > 0 )
  {
    p_nNumDisplayModes = &Config_atDisplayDevice[0].nNumDisplayModes;
    v16 = igi2_frame.v29;
    do
    {
      v17 = p_nNumDisplayModes - 832;
      v18 = v16;
      *p_nNumDisplayModes = 0;
      v16 += 256;
      p_nNumDisplayModes += 833;
      --v14;
      qmemcpy(v17, v18, 0x100u);
    }
    while ( v14 );
  }
  if ( Display_nModes > 0 )
  {
    v19 = Display_atMode;
    v20 = Display_nModes;
    do
    {
      if ( Display_tActiveMode.eRenderMode == v19->eRenderMode && Config_EnumDisplayModeCB )
        Config_EnumDisplayModeCB(v19);
      ++v19;
      --v20;
    }
    while ( v20 );
  }
  v21 = RenderMode_aeRenderModeStack[RenderMode_nSP];
  if ( v21 == -1 )
  {
    RenderMode_eActiveRenderMode = -1;
  }
  else
  {
    ++RenderMode_nSP;
    if ( v21 != v12 )
    {
      qmemcpy(
        &RenderMode_tActiveRenderMode,
        (void *)(520 * v21 + 139167712),
        sizeof(RenderMode_tActiveRenderMode));
      RenderMode_eActiveRenderMode = v21;
    }
  }
  v23 = provider_activeindex;
  Config_tConfig.zContentControlPassword[0] = 0;
  p_tGfxOptions = &Config_tConfig.atPlayerProfile[0].tGraphicOptions.tGfxOptions;
  v25 = 16;
  do
  {
    memset(&p_tGfxOptions[-1].isLensFlares, 0, 0xAC0u);
    p_tGfxOptions[14].isStencilShadows = 1065353216;
    p_tGfxOptions[14].isTextureCompression = 1065353216;
    p_tGfxOptions[15].isTextureCompression = v23;
    p_tGfxOptions[15].isWindOnForests = false;
    p_tGfxOptions[14].isHighQualityForests = 1048576000;
    p_tGfxOptions[14].isWindOnForests = false;
    p_tGfxOptions[14].vTerrainDetail = 0.0;
    p_tGfxOptions[14].eWaterQualityLevel = WATERRENDER_QUALITY_NORMAL;
    v26 = p_tGfxOptions;
    p_tGfxOptions[-1].vTerrainDetail = 0.0;
    p_tGfxOptions = (struct GfxOptions_s *)((char *)p_tGfxOptions + 2752);
    --v25;
    qmemcpy(v26, &GfxOptions_atDefaultOptions[3], sizeof(struct GfxOptions_s));
  }
  while ( v25 );
}

// source: j/0/config.c:4718  [anchor-hash]
void __cdecl Config_Close()
{
  struct MissingResource_s *v0; // esi
  struct MissingResource_s *ptNext; // ebp
  int v2; // esi

  v0 = ptMissingResourceList;
  Config_FreeAllPlayerProfileResources();
  if ( byte_6BBEAC )
    File_RemoveAlias(&g_zFileName.atPictureResources[16].zResourceFilename[48]);
  if ( v0 )
  {
    do
    {
      ptNext = v0->ptNext;
      v2 = *(_DWORD *)((unsigned int)&v0[-1].zString[252] & 0xFFFFFFFC);
      --Mem_nCurrentAllocations;
      Node_Remove((_DWORD **)v2);
      memset(*(void **)(v2 + 8), 0xCDu, *(_DWORD *)(v2 + 16));
      free((void *)v2);
      v0 = ptNext;
    }
    while ( ptNext );
  }
  ptMissingResourceList = nullptr;
}

int sub_42E780()
{
  return 1;
}
