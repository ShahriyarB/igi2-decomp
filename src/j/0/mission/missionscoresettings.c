/* j/0/mission/missionscoresettings.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/mission/missionscoresettings.c:89  [anchor-mhash]
void __cdecl MissionScoreSettings_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  memset(&ptQTask[1], 0, 0x3Cu);
}

// source: j/0/mission/missionscoresettings.c:115  [size]
void __cdecl MissionScoreSettings_DeleteHandler(struct QTask_s *ptQTask)
{
  ;
}

// source: j/0/mission/missionscoresettings.c:130  [size]
void __cdecl MissionScoreSettings_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ;
}

// source: j/0/mission/missionscoresettings.c:145  [size]
void __cdecl MissionScoreSettings_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = MissionScoreSettings_ptParameterList;
}

// source: j/0/mission/missionscoresettings.c:163  [anchor-mhash]
struct HumanMissionScoreData_s *__cdecl MissionScoreSettings_Init(
        struct HumanMissionScoreData_s *ptHumanMissionScoreData)
{
  enum GameDifficulty_e eDifficultyLevel; // edx

  eDifficultyLevel = Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eDifficultyLevel;
  ptHumanMissionScoreData->iMissionID = Game_iMissionID;
  ptHumanMissionScoreData->eGameDifficulty = eDifficultyLevel;
  ptHumanMissionScoreData->nGameLoads = 0;
  ptHumanMissionScoreData->nHits = 0;
  ptHumanMissionScoreData->nKills = 0;
  ptHumanMissionScoreData->nShots = 0;
  ptHumanMissionScoreData->nSpotted = 0;
  ptHumanMissionScoreData->nTime = 0;
  ptHumanMissionScoreData->nTimesAlarmTriggered = 0;
  ptHumanMissionScoreData->nHealth = 0;
  return ptHumanMissionScoreData;
}

// source: j/0/mission/missionscoresettings.c:185  [size]
unsigned __int16 __cdecl MissionScoreSettings_GetQTaskType()
{
  return MissionScoreSettings_eQTaskType;
}

// source: j/0/mission/missionscoresettings.c:198  [anchor-hash]
struct MissionScoreSettings_s *__cdecl MissionScoreSettings_Get()
{
  struct MissionScoreSettings_s *result; // eax

  if ( !Level_ptQLevelQTask )
    return nullptr;
  result = (struct MissionScoreSettings_s *)QTask_GetFirstChildOfType(
                                              &Level_ptQLevelQTask->tQTask,
                                              MissionScoreSettings_eQTaskType);
  if ( !result )
    return nullptr;
  return result;
}

// source: j/0/mission/missionscoresettings.c:228  [anchor-mhash]
char *__cdecl MissionScoreSettings_GetRankDesc(
        int iRank,
        int eGameDifficulty)
{
  if ( iRank >= 0 )
    return (&(&MissionScoreSettings_azRank[2 * eGameDifficulty + 1])[eGameDifficulty])[iRank];
  else
    return MissionScoreSettings_azRank[0];
}

// source: j/0/mission/missionscoresettings.c:254  [anchor-callee]
int __cdecl MissionScoreSettings_GetRank(
        struct MissionScoreSettings_s *ptScoreSettings,
        struct HumanMissionScoreData_s *ptScoreData,
        int ltcg_arg1)
{
  #pragma pack(push, 1)
  union
  {
    struct { int v10; };
    struct { char igi2_o1[8]; int v11; };
    struct { char igi2_o2[12]; float *v12; };
    struct { char igi2_o3[28]; _DWORD v13[5]; };
    char igi2_extent[48];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  float *v3; // esi
  int v4; // edi
  int v5; // ecx
  unsigned int nShots; // ecx
  signed int v7; // eax
  bool v8; // sf

  memset(igi2_frame.v13, 0, sizeof(igi2_frame.v13));
  if ( !ptScoreData->nTime )
    goto LABEL_27;
  if ( ltcg_arg1 )
  {
    *(_DWORD *)ltcg_arg1 = 1;
    *(_DWORD *)(ltcg_arg1 + 4) = 1;
    *(_DWORD *)(ltcg_arg1 + 8) = 1;
    *(_DWORD *)(ltcg_arg1 + 12) = 1;
    *(_DWORD *)(ltcg_arg1 + 16) = 1;
  }
  v3 = &ptScoreSettings->atMissionRankRequirement[2].avRequired[3];
  igi2_frame.v11 = 2;
  igi2_frame.v12 = &ptScoreSettings->atMissionRankRequirement[2].avRequired[3];
  do
  {
    memset(igi2_frame.v13, 0, sizeof(igi2_frame.v13));
    v4 = 0;
    v5 = 0;
    igi2_frame.v10 = 0;
    do
    {
      if ( ptScoreSettings->atMissionRankRequirement[0].avRequired[v5] < 0.0 )
        goto LABEL_22;
      switch ( v5 )
      {
        case 0:
          if ( (__int64)*(v3 - 3) >= ptScoreData->nTime / 0x1E )
            igi2_frame.v13[0] = 1;
          else
            v4 = 1;
          break;
        case 1:
          if ( (__int64)*(v3 - 2) >= (int)ptScoreData->nSpotted )
            igi2_frame.v13[1] = 1;
          else
            v4 = 1;
          break;
        case 3:
          if ( (__int64)*v3 <= (int)ptScoreData->nHealth )
            igi2_frame.v13[3] = 1;
          else
            v4 = 1;
          break;
        case 4:
          nShots = ptScoreData->nShots;
          if ( nShots )
          {
            v7 = 100 * ptScoreData->nHits / nShots;
            v5 = igi2_frame.v10;
            if ( (__int64)v3[1] > v7 )
            {
              v4 = 1;
              break;
            }
          }
          else
          {
            v5 = igi2_frame.v10;
          }
          igi2_frame.v13[4] = 1;
          break;
        default:
          break;
      }
LABEL_22:
      igi2_frame.v10 = ++v5;
    }
    while ( v5 < 5 );
    if ( !v4 )
      return igi2_frame.v11;
    if ( ltcg_arg1 )
    {
      qmemcpy((void *)ltcg_arg1, igi2_frame.v13, 0x14u);
      v3 = igi2_frame.v12;
    }
    v3 -= 5;
    v8 = --igi2_frame.v11 < 0;
    igi2_frame.v12 = v3;
  }
  while ( !v8 );
LABEL_27:
  if ( ltcg_arg1 )
    qmemcpy((void *)ltcg_arg1, igi2_frame.v13, 0x14u);
  return -1;
}

// source: j/0/mission/missionscoresettings.c:342  [anchor-caller]
void __cdecl MissionScoreSettings_UpdateMissionStats(struct HumanMissionScoreData_s *ptHumanMissionScoreData)
{
  unsigned int iMissionID; // ebx
  struct MissionScoreSettings_s *FirstChildOfType; // esi
  struct HumanMissionScoreData_s *MissionStats; // eax
  int Rank; // ebp

  iMissionID = ptHumanMissionScoreData->iMissionID;
  if ( Level_ptQLevelQTask )
  {
    FirstChildOfType = (struct MissionScoreSettings_s *)QTask_GetFirstChildOfType(
                                                          &Level_ptQLevelQTask->tQTask,
                                                          MissionScoreSettings_eQTaskType);
    if ( FirstChildOfType )
    {
      if ( !Config_GetMissionStats(iMissionID)
        || (MissionStats = Config_GetMissionStats(iMissionID),
            ptHumanMissionScoreData->eGameDifficulty >= MissionStats->eGameDifficulty)
        && ptHumanMissionScoreData->nTime
        && (Rank = MissionScoreSettings_GetRank(FirstChildOfType, MissionStats, 0),
            MissionScoreSettings_GetRank(FirstChildOfType, ptHumanMissionScoreData, 0) >= Rank) )
      {
        Config_UpdateMissionStats(ptHumanMissionScoreData, FirstChildOfType);
      }
    }
  }
}

// source: j/0/mission/missionscoresettings.c:384  [anchor-strings]
void __cdecl MissionScoreSettings_Open()
{
  #pragma pack(push, 1)
  union
  {
    struct { struct ParameterList_s *ptParameterList; };
    struct { char igi2_o1[4]; int v7; };
    struct { char igi2_o2[8]; char *ArgList; };
    struct { char igi2_o3[12]; char *azRankParameterName[3]; };
    char igi2_extent[24];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  unsigned __int16 BaseQTaskType; // ax
  unsigned __int16 v1; // si
  struct ParameterList_s *v2; // eax
  char *v3; // ebx
  int v4; // ebp
  bool v5; // cc

  BaseQTaskType = QTask_GetBaseQTaskType();
  v1 = QTask_NewQTaskType("MissionScoreSettings", 100, BaseQTaskType, 0, 0);
  MissionScoreSettings_eQTaskType = v1;
  QTask_LinkQTaskEventHandlerFn(v1, 0, (void (__cdecl *)(struct QTask_s *, void *))MissionScoreSettings_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 2, (void (__cdecl *)(struct QTask_s *))MissionScoreSettings_DeleteHandler);
  QTask_LinkQTaskEventHandlerFn(
    v1,
    ParameterList_eUpdateInternalDataQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))MissionScoreSettings_UpdateInternalDataHandler);
  QTask_LinkQTaskEventHandlerFn(
    v1,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))MissionScoreSettings_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(
    v1,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveHandler);
  v2 = (struct ParameterList_s *)Mem_AllocFn(312, 4);
  v2->nParameters = 0;
  v2->nMaxParameters = 15;
  v2->ptParameterListItem = (struct ParameterListItem_s *)&v2[1];
  MissionScoreSettings_ptParameterList = v2;
  igi2_frame.azRankParameterName[0] = "Bodyguard";
  igi2_frame.azRankParameterName[1] = (char *)&g_zSpriteName_0.eQTaskType;
  igi2_frame.azRankParameterName[2] = (char *)&g_zSpriteName_0.tQTaskRefList;
  igi2_frame.ArgList = MissionScoreSettings_azItemRequirementDesc;
  igi2_frame.v7 = 40;
  do
  {
    v3 = igi2_frame.ArgList;
    v4 = 0;
    igi2_frame.ptParameterList = (struct ParameterList_s *)igi2_frame.v7;
    do
    {
      strcat(v3, " (");
      qmemcpy(
        &v3[strlen(v3)],
        igi2_frame.azRankParameterName[v4],
        &igi2_frame.azRankParameterName[v4][strlen(igi2_frame.azRankParameterName[v4]) + 1] - igi2_frame.azRankParameterName[v4]);
      *(_WORD *)&v3[strlen(v3)] = g_zSpriteName_0.tQTaskChildren.ptMiddle;
      ParameterList_AddParameter(
        MissionScoreSettings_ptParameterList,
        (unsigned int)igi2_frame.ptParameterList,
        Level_eParameterTypeReal32,
        v3,
        7u,
        nullptr);
      ++v4;
      v3 += 500;
      igi2_frame.ptParameterList = (struct ParameterList_s *)((char *)igi2_frame.ptParameterList + 20);
    }
    while ( v4 < 3 );
    v5 = igi2_frame.v7 + 4 < 60;
    igi2_frame.v7 += 4;
    igi2_frame.ArgList += 100;
  }
  while ( v5 );
}

// source: j/0/mission/missionscoresettings.c:433  [size]
void __cdecl MissionScoreSettings_Close()
{
  int v0; // esi

  if ( MissionScoreSettings_ptParameterList )
  {
    v0 = *(_DWORD *)((unsigned int)&MissionScoreSettings_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
  QTask_DeleteQTaskType(MissionScoreSettings_eQTaskType);
}
