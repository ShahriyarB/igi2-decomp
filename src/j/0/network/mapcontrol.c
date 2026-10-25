/* j/0/network/mapcontrol.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/network/mapcontrol.c:42  [size]
struct MapControl_s *__cdecl MapControl_GetControl()
{
  return (struct MapControl_s *)QTask_GetFirstChildOfType(Flow_ptFlow->ptNetManagerQTask, MapControl_eQTaskType);
}

// source: j/0/network/mapcontrol.c:61  [size]
unsigned __int16 __cdecl MapControl_GetQTaskType()
{
  return MapControl_eQTaskType;
}

// source: j/0/network/mapcontrol.c:75  [size]
struct QTask_s *__cdecl MapControl_New(
        struct QTask_s *ptParentQTask,
        struct MapControlCreateContext_s *ptCreateContext)
{
  return QTask_NewFn(ptParentQTask, MapControl_eQTaskType, ptCreateContext);
}

// source: j/0/network/mapcontrol.c:96  [size]
void __cdecl MapControl_RunHandler(struct QTask_s *ptQTask)
{
  ;
}

// source: j/0/network/mapcontrol.c:110  [anchor-hash]
void __cdecl MapControl_SetLoading(enum bool isLoading)
{
  QTask_GetFirstChildOfType(Flow_ptFlow->ptNetManagerQTask, MapControl_eQTaskType)[1].ptParent = (struct QTask_s *)isLoading;
  if ( isLoading )
    NetManager_LogMessage("MapControl_SetLoading(): set toTRUE\n");
  else
    NetManager_LogMessage("MapControl_SetLoading(): set to FALSE\n");
}

// source: j/0/network/mapcontrol.c:139  [anchor-hash]
enum bool __cdecl MapControl_IsLoading()
{
  return (enum bool)QTask_GetFirstChildOfType(Flow_ptFlow->ptNetManagerQTask, MapControl_eQTaskType)[1].ptParent;
}

// source: j/0/network/mapcontrol.c:157  [anchor-hash]
void __cdecl MapControl_SendTimedScoreUpdate(struct MapControl_s *ptControl)
{
  DWORD PerformanceCounter; // eax
  int v2; // eax

  if ( Timer_isPerformanceCounter )
    PerformanceCounter = Timer_GetPerformanceCounter();
  else
    PerformanceCounter = GetTickCount();
  v2 = PerformanceCounter - Timer_nStartTime;
  if ( v2 - ptControl->nLastUpdateTime > ptControl->nUpdateInterval )
  {
    ptControl->nLastUpdateTime = v2;
    NetManager_SendScoreUpdate();
  }
}

// source: j/0/network/mapcontrol.c:180  [anchor-mhash]
void __cdecl MapControl_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  bool v2; // zf
  DWORD TickCount; // eax

  v2 = Timer_isPerformanceCounter == 0;
  ptQTask[1].tQTaskRefList.ptHead = (struct QReference_s *)10000;
  if ( v2 )
    TickCount = GetTickCount();
  else
    TickCount = Timer_GetPerformanceCounter();
  ptQTask[1].tQTaskRefList.ptMiddle = (struct QReference_s *)(TickCount - Timer_nStartTime);
  ptQTask[1].tQTaskRefList.ptTail = nullptr;
  ptQTask[1].ptParent = nullptr;
}

// source: j/0/network/mapcontrol.c:204  [size]
void __cdecl MapControl_VerifyConfig()
{
  ;
}

// source: j/0/network/mapcontrol.c:233  [anchor-callee]
struct ServerConfig_s *__cdecl MapControl_LoadServerConfig(struct ServerConfig_s *ptConfig)
{
  char nMapMaxTime; // bl
  int nMapMaxTeamScore; // esi
  struct ServerConfig_s *result; // eax
  char nObjectiveMaxTime; // [esp+1h] [ebp-1h]

  nMapMaxTime = ptConfig->nMapMaxTime;
  nMapMaxTeamScore = ptConfig->nMapMaxTeamScore;
  nObjectiveMaxTime = ptConfig->nObjectiveMaxTime;
  result = (struct ServerConfig_s *)QTask_GetFirstChildOfType(Flow_ptFlow->ptNetManagerQTask, MapControl_eQTaskType);
  if ( !nMapMaxTime )
    nMapMaxTime = -1;
  if ( !nMapMaxTeamScore )
    nMapMaxTeamScore = -1;
  if ( !nObjectiveMaxTime )
    nObjectiveMaxTime = -1;
  if ( nMapMaxTeamScore > 0 )
    nMapMaxTeamScore *= 60000;
  *(_DWORD *)&result->zServerName[44] = nMapMaxTeamScore;
  *(_DWORD *)&result->zServerName[40] = nMapMaxTime;
  *(_DWORD *)&result->zServerName[48] = nObjectiveMaxTime;
  *(_DWORD *)&result->zServerPassword[4] = 1;
  return result;
}

// source: j/0/network/mapcontrol.c:272  [anchor-mhash]
void __cdecl MapControl_ServerReset()
{
  struct QTask_s *ptNetManagerQTask; // edi
  struct QTask_s *FirstChildOfType; // esi
  DWORD PerformanceCounter; // eax
  DWORD v3; // eax
  struct QTask_s *ptPrev; // ecx

  ptNetManagerQTask = Flow_ptFlow->ptNetManagerQTask;
  FirstChildOfType = QTask_GetFirstChildOfType(ptNetManagerQTask, MapControl_eQTaskType);
  if ( Timer_isPerformanceCounter )
    PerformanceCounter = Timer_GetPerformanceCounter();
  else
    PerformanceCounter = GetTickCount();
  v3 = PerformanceCounter - Timer_nStartTime;
  ptPrev = FirstChildOfType[1].ptPrev;
  if ( ptPrev == (struct QTask_s *)-1 )
    FirstChildOfType[1].tQTaskChildren.ptTail = (struct QTask_s *)-1;
  else
    FirstChildOfType[1].tQTaskChildren.ptTail = (struct QTask_s *)((char *)ptPrev + ((char *)ptNetManagerQTask[6].tQTaskRefList.ptMiddle - (char *)ptNetManagerQTask[6].tQTaskRefList.ptTail) + v3);
  FirstChildOfType[1].tQTaskChildren.ptMiddle = (struct QTask_s *)1;
}

// source: j/0/network/mapcontrol.c:304  [anchor-hash]
void __cdecl MapControl_ServerRoundComplete()
{
  struct QTask_s *FirstChildOfType; // eax

  FirstChildOfType = QTask_GetFirstChildOfType(Flow_ptFlow->ptNetManagerQTask, MapControl_eQTaskType);
  ++*(int *)&FirstChildOfType[1].tQTaskChildren.ptMiddle;
}

// source: j/0/network/mapcontrol.c:324  [anchor-callee]
enum bool __cdecl MapControl_isChangeMapNow()
{
  struct QTask_s *ptNetManagerQTask; // edi
  struct QTask_s *FirstChildOfType; // ebx
  DWORD v2; // eax
  int v3; // esi
  int MaxScore; // eax
  struct QTask_s *ptNext; // ecx
  BOOL v6; // edx
  struct QTask_s *ptTail; // ecx
  BOOL v8; // ecx
  struct QTask_s *ptHead; // ebx
  BOOL v10; // eax

  ptNetManagerQTask = Flow_ptFlow->ptNetManagerQTask;
  FirstChildOfType = QTask_GetFirstChildOfType(ptNetManagerQTask, MapControl_eQTaskType);
  if ( !FirstChildOfType[1].tQTaskRefList.ptTail )
    return false;
  v2 = Timer_isPerformanceCounter ? Timer_GetPerformanceCounter() : GetTickCount();
  v3 = v2
     - Timer_nStartTime
     + (char *)ptNetManagerQTask[6].tQTaskRefList.ptMiddle
     - (char *)ptNetManagerQTask[6].tQTaskRefList.ptTail;
  MaxScore = TeamManager_GetMaxScore();
  ptNext = FirstChildOfType[1].ptNext;
  v6 = ptNext != (struct QTask_s *)-1 && (int)FirstChildOfType[1].tQTaskChildren.ptMiddle > (int)ptNext;
  ptTail = FirstChildOfType[1].tQTaskChildren.ptTail;
  v8 = ptTail != (struct QTask_s *)-1 && v3 > (int)ptTail;
  ptHead = FirstChildOfType[1].tQTaskChildren.ptHead;
  v10 = ptHead != (struct QTask_s *)-1 && MaxScore >= (int)ptHead;
  return v6 || v8 || v10;
}

// source: j/0/network/mapcontrol.c:356  [anchor-caller]
void __cdecl MapControl_PrintMapStat(char *zString, int length)
{
  #pragma pack(push, 1)
  union
  {
    struct { char v24[20]; };
    struct { char igi2_o1[20]; char Destination[20]; };
    struct { char igi2_o2[40]; char Buffer[20]; };
    struct { char igi2_o3[60]; char v27[40]; };
    char igi2_extent[100];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct Flow_t *v2; // esi
  struct QTask_s *FirstChildOfType; // ebx
  struct QTask_s *ptNetManagerQTask; // edi
  DWORD PerformanceCounter; // eax
  int v6; // esi
  int MaxScore; // edi
  struct QTask_s *ptNext; // eax
  struct QTask_s *ptMiddle; // ecx
  char *LocalizedStringForLanguage; // eax
  struct QTask_s *ptHead; // eax
  struct QTask_s *v12; // ecx
  char *v13; // eax
  int v14; // edx
  char *v15; // eax
  enum GameLanguage_e eLanguage; // esi
  char *v17; // edi
  char *v18; // ebx
  char *v19; // ebp
  char *v20; // eax
  enum GameLanguage_e v21; // esi
  char *v22; // edi
  char *v23; // eax

  v2 = Flow_ptFlow;
  FirstChildOfType = QTask_GetFirstChildOfType(Flow_ptFlow->ptNetManagerQTask, MapControl_eQTaskType);
  if ( FirstChildOfType[1].tQTaskRefList.ptTail )
  {
    ptNetManagerQTask = v2->ptNetManagerQTask;
    if ( Timer_isPerformanceCounter )
      PerformanceCounter = Timer_GetPerformanceCounter();
    else
      PerformanceCounter = GetTickCount();
    v6 = PerformanceCounter
       - Timer_nStartTime
       + (char *)ptNetManagerQTask[6].tQTaskRefList.ptMiddle
       - (char *)ptNetManagerQTask[6].tQTaskRefList.ptTail;
    MaxScore = TeamManager_GetMaxScore();
    sprintf(igi2_frame.Buffer, byte_69AF88);
    ptNext = FirstChildOfType[1].ptNext;
    if ( ptNext == (struct QTask_s *)-1 )
    {
      LocalizedStringForLanguage = Config_GetLocalizedStringForLanguage(
                                     "mp/OFF",
                                     Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eLanguage,
                                     true);
      strncpy(igi2_frame.Destination, LocalizedStringForLanguage, 0x14u);
    }
    else
    {
      ptMiddle = FirstChildOfType[1].tQTaskChildren.ptMiddle;
      if ( (int)ptMiddle >= (int)ptNext )
        ptMiddle = FirstChildOfType[1].ptNext;
      _snprintf(igi2_frame.Destination, 0x14u, "(%d/%d)", ptMiddle, FirstChildOfType[1].ptNext);
    }
    ptHead = FirstChildOfType[1].tQTaskChildren.ptHead;
    if ( ptHead == (struct QTask_s *)-1 )
    {
      v13 = Config_GetLocalizedStringForLanguage(
              "mp/OFF",
              Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eLanguage,
              true);
      strncpy(igi2_frame.v24, v13, 0x14u);
    }
    else
    {
      v12 = (struct QTask_s *)MaxScore;
      if ( MaxScore >= (int)ptHead )
        v12 = FirstChildOfType[1].tQTaskChildren.ptHead;
      _snprintf(igi2_frame.v24, 0x14u, "(%d/%d)", v12, FirstChildOfType[1].tQTaskChildren.ptHead);
    }
    if ( FirstChildOfType[1].ptPrev == (struct QTask_s *)-1 )
    {
      v15 = Config_GetLocalizedStringForLanguage(
              "mp/OFF",
              Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eLanguage,
              true);
      strncpy(igi2_frame.v27, v15, 0x14u);
    }
    else
    {
      v14 = ((int)FirstChildOfType[1].tQTaskChildren.ptTail - v6) / 1000;
      if ( v14 <= 0 )
        _snprintf(igi2_frame.v27, 0x28u, "00:00");
      else
        _snprintf(igi2_frame.v27, 0x28u, "%02d:%02d", v14 / 60, v14 % 60);
    }
    eLanguage = Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eLanguage;
    v17 = Config_GetLocalizedStringForLanguage("mp/Score", eLanguage, true);
    v18 = Config_GetLocalizedStringForLanguage(
            "mp/Round",
            Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eLanguage,
            true);
    v19 = Config_GetLocalizedStringForLanguage(
            "mp/MapState",
            Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eLanguage,
            true);
    v20 = Config_GetLocalizedStringForLanguage("mp/Time", eLanguage, true);
    _snprintf(zString, length, "%s%s [%s %s %s %s %s %s]", v19, igi2_frame.Buffer, v18, igi2_frame.Destination, v17, igi2_frame.v24, v20, igi2_frame.v27);
  }
  else
  {
    v21 = Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eLanguage;
    v22 = Config_GetLocalizedStringForLanguage("mp/MapState", v21, true);
    v23 = Config_GetLocalizedStringForLanguage("mp/WaitingforData", v21, true);
    sprintf(zString, "%s [%s...]", v22, v23);
  }
}

int __cdecl sub_44B380(char *a1, size_t BufferCount)
{
  #pragma pack(push, 1)
  union
  {
    struct { char v14[20]; };
    struct { char igi2_o1[20]; char Buffer[20]; };
    struct { char igi2_o2[40]; char v16[40]; };
    char igi2_extent[80];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct Flow_t *v2; // esi
  struct QTask_s *FirstChildOfType; // edi
  struct QTask_s *ptNetManagerQTask; // ebx
  DWORD PerformanceCounter; // eax
  int v6; // esi
  int MaxScore; // ebx
  struct QTask_s *ptNext; // eax
  struct QTask_s *ptMiddle; // ecx
  struct QTask_s *ptHead; // eax
  struct QTask_s *v11; // ecx
  int v12; // eax

  v2 = Flow_ptFlow;
  FirstChildOfType = QTask_GetFirstChildOfType(Flow_ptFlow->ptNetManagerQTask, MapControl_eQTaskType);
  if ( !FirstChildOfType[1].tQTaskRefList.ptTail )
    return _snprintf(a1, BufferCount, "NO DATA");
  ptNetManagerQTask = v2->ptNetManagerQTask;
  if ( Timer_isPerformanceCounter )
    PerformanceCounter = Timer_GetPerformanceCounter();
  else
    PerformanceCounter = GetTickCount();
  v6 = PerformanceCounter
     - Timer_nStartTime
     + (char *)ptNetManagerQTask[6].tQTaskRefList.ptMiddle
     - (char *)ptNetManagerQTask[6].tQTaskRefList.ptTail;
  MaxScore = TeamManager_GetMaxScore();
  ptNext = FirstChildOfType[1].ptNext;
  if ( ptNext == (struct QTask_s *)-1 )
  {
    _snprintf(igi2_frame.Buffer, 0x14u, (char *const)&g_zInitialValue);
  }
  else
  {
    ptMiddle = FirstChildOfType[1].tQTaskChildren.ptMiddle;
    if ( (int)ptMiddle >= (int)ptNext )
      ptMiddle = FirstChildOfType[1].ptNext;
    _snprintf(igi2_frame.Buffer, 0x14u, "roundlimit_%d/%d", ptMiddle, FirstChildOfType[1].ptNext);
  }
  ptHead = FirstChildOfType[1].tQTaskChildren.ptHead;
  if ( ptHead == (struct QTask_s *)-1 )
  {
    _snprintf(igi2_frame.v14, 0x14u, (char *const)&g_zInitialValue);
  }
  else
  {
    v11 = (struct QTask_s *)MaxScore;
    if ( MaxScore >= (int)ptHead )
      v11 = FirstChildOfType[1].tQTaskChildren.ptHead;
    _snprintf(igi2_frame.v14, 0x14u, "scorelimit_%d/%d", v11, FirstChildOfType[1].tQTaskChildren.ptHead);
  }
  if ( FirstChildOfType[1].ptPrev == (struct QTask_s *)-1 )
  {
    _snprintf(igi2_frame.v16, 0x28u, (char *const)&g_zInitialValue);
  }
  else
  {
    v12 = ((int)FirstChildOfType[1].tQTaskChildren.ptTail - v6) / 1000;
    if ( v12 <= 0 )
      _snprintf(igi2_frame.v16, 0x28u, "timeleft_00:00");
    else
      _snprintf(igi2_frame.v16, 0x28u, "timeleft_%02d:%02d", v12 / 60, v12 % 60);
  }
  return _snprintf(a1, BufferCount, "%s  %s  %s", igi2_frame.Buffer, igi2_frame.v14, igi2_frame.v16);
}

// source: j/0/network/mapcontrol.c:442  [anchor-hash]
void __cdecl MapControl_ClearClientState()
{
  QTask_GetFirstChildOfType(Flow_ptFlow->ptNetManagerQTask, MapControl_eQTaskType)[1].tQTaskRefList.ptTail = nullptr;
}

// source: j/0/network/mapcontrol.c:464  [anchor-mhash]
void __cdecl MapControl_ReadState(struct NetManagerGameSettings_s *ptSettings)
{
  struct QTask_s *FirstChildOfType; // eax

  FirstChildOfType = QTask_GetFirstChildOfType(Flow_ptFlow->ptNetManagerQTask, MapControl_eQTaskType);
  FirstChildOfType[1].ptNext = (struct QTask_s *)ptSettings->nMaxRounds;
  if ( (int)FirstChildOfType[1].ptPrev <= 0 )
    FirstChildOfType[1].ptPrev = (struct QTask_s *)ptSettings->nMapMaxTime;
  else
    FirstChildOfType[1].ptPrev = (struct QTask_s *)(60000 * ptSettings->nMapMaxTime);
  FirstChildOfType[1].tQTaskChildren.ptHead = (struct QTask_s *)ptSettings->nMaxTeamScore;
  FirstChildOfType[1].tQTaskChildren.ptMiddle = (struct QTask_s *)ptSettings->nRound;
  FirstChildOfType[1].tQTaskChildren.ptTail = (struct QTask_s *)ptSettings->nMapEndTime;
  FirstChildOfType[1].tQTaskRefList.ptTail = (struct QReference_s *)1;
}

// source: j/0/network/mapcontrol.c:502  [anchor-callee]
void __cdecl MapControl_WriteState(struct NetManagerGameSettings_s *ptSettings)
{
  struct QTask_s *FirstChildOfType; // eax

  FirstChildOfType = QTask_GetFirstChildOfType(Flow_ptFlow->ptNetManagerQTask, MapControl_eQTaskType);
  ptSettings->nMaxRounds = (char)FirstChildOfType[1].ptNext;
  ptSettings->nMapMaxTime = (int)FirstChildOfType[1].ptPrev;
  ptSettings->nMaxTeamScore = (char)FirstChildOfType[1].tQTaskChildren.ptHead;
  ptSettings->nRound = (char)FirstChildOfType[1].tQTaskChildren.ptMiddle;
  ptSettings->nMapEndTime = (int)FirstChildOfType[1].tQTaskChildren.ptTail;
}

// source: j/0/network/mapcontrol.c:527  [anchor-hash]
void __cdecl MapControl_WriteToScoreUpdate(struct NetManagerGameMessageTeamScore_t *ptTeamScore)
{
  struct QTask_s *FirstChildOfType; // eax

  FirstChildOfType = QTask_GetFirstChildOfType(Flow_ptFlow->ptNetManagerQTask, MapControl_eQTaskType);
  ptTeamScore->nMapEndTime = (int)FirstChildOfType[1].tQTaskChildren.ptTail;
  ptTeamScore->nRound = (int)FirstChildOfType[1].tQTaskChildren.ptMiddle;
  ptTeamScore->isLoading = (char)FirstChildOfType[1].ptParent;
}

// source: j/0/network/mapcontrol.c:551  [anchor-hash]
void __cdecl MapControl_ReadFromScoreUpdate(struct NetManagerGameMessageTeamScore_t *ptTeamScore)
{
  struct QTask_s *FirstChildOfType; // eax

  FirstChildOfType = QTask_GetFirstChildOfType(Flow_ptFlow->ptNetManagerQTask, MapControl_eQTaskType);
  FirstChildOfType[1].tQTaskChildren.ptTail = (struct QTask_s *)ptTeamScore->nMapEndTime;
  FirstChildOfType[1].tQTaskChildren.ptMiddle = (struct QTask_s *)ptTeamScore->nRound;
  FirstChildOfType[1].tQTaskRefList.ptTail = (struct QReference_s *)1;
  FirstChildOfType[1].ptParent = (struct QTask_s *)ptTeamScore->isLoading;
}

// source: j/0/network/mapcontrol.c:574  [size]
void __cdecl MapControl_Close()
{
  QTask_DeleteQTaskType(MapControl_eQTaskType);
}

// source: j/0/network/mapcontrol.c:588  [anchor-hash]
void __cdecl MapControl_Open()
{
  unsigned __int16 BaseQTaskType; // ax
  unsigned __int16 v1; // si

  BaseQTaskType = QTask_GetBaseQTaskType();
  v1 = QTask_NewQTaskType("MapControl", 76, BaseQTaskType, 0, 0);
  MapControl_eQTaskType = v1;
  QTask_LinkQTaskEventHandlerFn(v1, 0, MapControl_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 1, (void (__cdecl *)(struct QTask_s *))MapControl_RunHandler);
}
