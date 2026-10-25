/* j/0/humanai/aisquad.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/humanai/aisquad.c:182  [anchor-hash]
void __cdecl AISquad_ClearVoiceLastPlayedTickTable()
{
  memset(AISQuad_anVoiceLastPlayedTickTable, 0, sizeof(AISQuad_anVoiceLastPlayedTickTable));
}

// source: j/0/humanai/aisquad.c:196  [anchor-hash]
int __cdecl AISquad_GetOrderDelay(struct AISquad_s *ptAISquad)
{
  int v1; // edx
  int v2; // ecx
  struct Game_s *v3; // eax
  unsigned int v4; // edi
  int v5; // edi
  unsigned int v6; // edi

  if ( ptAISquad->atEnemyTarget[7 * ptAISquad->tActionStack.nNumActions + 4].nTimer )
  {
    v1 = 6;
    v2 = 18;
  }
  else
  {
    v1 = 15;
    v2 = 30;
  }
  v3 = Game_ptGame;
  v4 = (Game_ptGame->tRunRandomState.anRandom[0] >> 7) ^ Game_ptGame->tRunRandomState.anRandom[2];
  Game_ptGame->tRunRandomState.anRandom[2] = v4;
  v5 = v4 ^ v3->tRunRandomState.anRandom[1];
  v3->tRunRandomState.anRandom[1] = v5;
  v6 = v5 + v3->tRunRandomState.anRandom[0];
  v3->tRunRandomState.anRandom[0] = v6;
  return v1 + (__int64)((double)(unsigned __int16)v6 * 0.0000152587890625 * (double)(v2 - v1));
}

// source: j/0/humanai/aisquad.c:231  [anchor-callee]
enum bool __cdecl AISquad_AddSoundToPlayingList(
        struct AISquad_s *ptAISquad,
        struct QTask_s *ptSound,
        struct HumanAI_s *ptMember)
{
  int nNumSoundsPlaying; // edi

  nNumSoundsPlaying = ptAISquad->nNumSoundsPlaying;
  if ( nNumSoundsPlaying >= 5 )
    return false;
  ptAISquad->atPlayingSoundList[nNumSoundsPlaying + 2].ptHumanAIQTask = &ptMember->tQTask;
  ptAISquad->atPlayingSoundList[nNumSoundsPlaying + 2].ptSoundQTaskRef = QTask_NewQTaskRef(ptSound);
  ++ptAISquad->nNumSoundsPlaying;
  return true;
}

// source: j/0/humanai/aisquad.c:256  [anchor-callee]
void __cdecl AISquad_MaintainPlayingSounds(struct AISquad_s *ptAISquad)
{
  int v1; // eax
  struct AISquadSoundItem_s *v2; // esi
  int nNumSoundsPlaying; // ebp
  void *pxObject; // eax
  struct MemPoolFreeItem_s *ptSoundQTaskRef; // eax
  int v6; // eax

  v1 = ptAISquad->nNumSoundsPlaying - 1;
  if ( v1 >= 0 )
  {
    v2 = &ptAISquad->atPlayingSoundList[v1 + 2];
    nNumSoundsPlaying = ptAISquad->nNumSoundsPlaying;
    while ( 1 )
    {
      pxObject = v2->ptSoundQTaskRef->pxObject;
      if ( LOBYTE(v2->ptHumanAIQTask->ptParent[29].tQTaskRefList.ptHead) )
        break;
      if ( !pxObject )
        goto LABEL_8;
LABEL_11:
      --v2;
      if ( !--nNumSoundsPlaying )
        return;
    }
    if ( pxObject )
      QTask_Delete((struct QTask_s *)v2->ptSoundQTaskRef->pxObject);
    v2->ptHumanAIQTask = nullptr;
LABEL_8:
    ptSoundQTaskRef = (struct MemPoolFreeItem_s *)v2->ptSoundQTaskRef;
    if ( v2->ptSoundQTaskRef->ptNext )
      ptSoundQTaskRef = (struct MemPoolFreeItem_s *)Node_Remove(ptSoundQTaskRef);
    --QTask_tQTaskRefPool.nAllocatedBlocks;
    ptSoundQTaskRef->ptNext = QTask_tQTaskRefPool.tMemPoolFreeList.ptHead;
    QTask_tQTaskRefPool.tMemPoolFreeList.ptHead = ptSoundQTaskRef;
    v2->ptSoundQTaskRef = nullptr;
    v6 = ptAISquad->nNumSoundsPlaying - 1;
    ptAISquad->nNumSoundsPlaying = v6;
    v2->ptSoundQTaskRef = ptAISquad->atPlayingSoundList[v6 + 2].ptSoundQTaskRef;
    v2->ptHumanAIQTask = ptAISquad->atPlayingSoundList[v6 + 2].ptHumanAIQTask;
    goto LABEL_11;
  }
}

// source: j/0/humanai/aisquad.c:308  [anchor-hash]
void __cdecl AISquad_ClearPlayingSoundsList(struct AISquad_s *ptAISquad)
{
  int v1; // edi
  struct AISquadSoundItem_s *v2; // esi

  v1 = 0;
  if ( ptAISquad->nNumSoundsPlaying > 0 )
  {
    v2 = &ptAISquad->atPlayingSoundList[2];
    do
    {
      QTask_DeleteQTaskAndQTaskRefSafe(&v2->ptSoundQTaskRef);
      ++v1;
      ++v2;
    }
    while ( v1 < ptAISquad->nNumSoundsPlaying );
  }
  ptAISquad->nNumSoundsPlaying = 0;
}

// source: j/0/humanai/aisquad.c:328  [anchor-callee]
int __cdecl AISquad_ClearTeamsMemberTimers(struct AISquad_s *ptAISquad, int iTeam)
{
  struct QTask_s *v2; // edx
  int result; // eax
  int v4; // ecx
  char *v5; // esi

  v2 = &ptAISquad->tQTask + iTeam;
  result = (int)v2[1].ptParent;
  v4 = 0;
  if ( result > 0 )
  {
    v5 = (char *)&v2[1];
    do
    {
      if ( *(_DWORD *)v5 )
        *(_DWORD *)(*(_DWORD *)(*(_DWORD *)v5 + 8) + 4444) = 0;
      result = (int)v2[1].ptParent;
      ++v4;
      v5 += 4;
    }
    while ( v4 < result );
  }
  return result;
}

// source: j/0/humanai/aisquad.c:355  [anchor-mhash]
struct QTask_s *__cdecl AISquad_GetClosestEventReceiver(
        struct AISquadEventContext_s *ptEvent)
{
  struct QTask_s *v1; // esi
  struct QReference_s **aptSquadMemberQTaskRef; // edi
  int nNumSquadMemberQTaskRefs; // ebx
  void *pxObject; // edx
  double *v5; // eax
  double v6; // st3
  long double v7; // st4
  float vClosest; // [esp+4h] [ebp-10h]
  float tDelta; // [esp+8h] [ebp-Ch]
  float tDelta_4; // [esp+Ch] [ebp-8h]

  v1 = nullptr;
  vClosest = 0.0;
  if ( ptEvent->nNumSquadMemberQTaskRefs > 0 )
  {
    aptSquadMemberQTaskRef = ptEvent->aptSquadMemberQTaskRef;
    nNumSquadMemberQTaskRefs = ptEvent->nNumSquadMemberQTaskRefs;
    do
    {
      pxObject = (*aptSquadMemberQTaskRef)->pxObject;
      if ( pxObject )
      {
        v5 = *((double **)pxObject + 8);
        tDelta = v5[5] - ptEvent->tPosition.vX;
        tDelta_4 = v5[6] - ptEvent->tPosition.vY;
        v6 = v5[7] - ptEvent->tPosition.vZ;
        v7 = sqrt(tDelta * tDelta + tDelta_4 * tDelta_4 + v6 * v6);
        if ( !v1 || v7 < vClosest )
        {
          vClosest = v7;
          v1 = (struct QTask_s *)(*aptSquadMemberQTaskRef)->pxObject;
        }
      }
      ++aptSquadMemberQTaskRef;
      --nNumSquadMemberQTaskRefs;
    }
    while ( nNumSquadMemberQTaskRefs );
  }
  return v1;
}

// source: j/0/humanai/aisquad.c:405  [anchor-hash]
void __cdecl AISquad_InitVoiceTable()
{
  strcpy(&AISquad_aazVoiceTable[32], "GV_02");
  strcpy(&AISquad_aazVoiceTable[96], "GV_02");
  strcpy(&AISquad_aazVoiceTable[160], "GV_06");
  strcpy(&AISquad_aazVoiceTable[192], "GV_07");
  strcpy(AISquad_aazVoiceTable, "GV_01");
  strcpy(&AISquad_aazVoiceTable[64], "GV_01");
  strcpy(&AISquad_aazVoiceTable[128], "GV_05");
  strcpy(&AISquad_aazVoiceTable[224], "GV_05");
  strcpy(&AISquad_aazVoiceTable[544], "GV_16");
  strcpy(&AISquad_aazVoiceTable[256], "GV_11");
  strcpy(&AISquad_aazVoiceTable[288], "GV_11");
  strcpy(&AISquad_aazVoiceTable[320], "GV_11");
  strcpy(&AISquad_aazVoiceTable[352], "GV_11");
  strcpy(&AISquad_aazVoiceTable[384], "GV_13");
  strcpy(&AISquad_aazVoiceTable[416], "GV_13");
  strcpy(&AISquad_aazVoiceTable[448], "GV_13");
  strcpy(&AISquad_aazVoiceTable[480], "GV_13");
  strcpy(&AISquad_aazVoiceTable[576], "GV_17");
  strcpy(&AISquad_aazVoiceTable[512], "GV_15");
  strcpy(&AISquad_aazVoiceTable[608], "GV_15");
  AISquad_aisVoiceDontPlayForSingleAI[0] = true;
  AISquad_aisVoiceDontPlayForSingleAI[1] = true;
  AISquad_aisVoiceDontPlayForSingleAI[2] = true;
  AISquad_aisVoiceDontPlayForSingleAI[3] = true;
  AISquad_aisVoiceDontPlayForSingleAI[4] = false;
  strcpy(&AISquad_aazVoiceTable[640], "GV_19");
  strcpy(&AISquad_aazVoiceTable[672], "GV_19");
  strcpy(&AISquad_aazVoiceTable[704], "GV_19");
  strcpy(&AISquad_aazVoiceTable[736], "GV_19");
  AISquad_aisVoiceDontPlayForSingleAI[5] = true;
  strcpy(&AISquad_aazVoiceTable[800], "GV_27");
  strcpy(&AISquad_aazVoiceTable[864], "GV_27");
  strcpy(&AISquad_aazVoiceTable[768], "GV_26");
  strcpy(&AISquad_aazVoiceTable[832], "GV_26");
  strcpy(&AISquad_aazVoiceTable[928], "GV_31");
  strcpy(&AISquad_aazVoiceTable[992], "GV_31");
  strcpy(&AISquad_aazVoiceTable[896], "GV_30");
  strcpy(&AISquad_aazVoiceTable[960], "GV_30");
  strcpy(&AISquad_aazVoiceTable[1056], "GV_35");
  strcpy(&AISquad_aazVoiceTable[1024], "GV_34");
  strcpy(&AISquad_aazVoiceTable[1120], "GV_34");
  strcpy(&AISquad_aazVoiceTable[1088], "GV_36");
  strcpy(&AISquad_aazVoiceTable[1152], "GV_40");
  strcpy(&AISquad_aazVoiceTable[1216], "GV_40");
  strcpy(&AISquad_aazVoiceTable[1280], "GV_47");
  strcpy(&AISquad_aazVoiceTable[1344], "GV_47");
  strcpy(&AISquad_aazVoiceTable[1184], "GV_41");
  strcpy(&AISquad_aazVoiceTable[1248], "GV_41");
  strcpy(&AISquad_aazVoiceTable[1920], "GV_49");
  strcpy(&AISquad_aazVoiceTable[1952], "GV_49");
  strcpy(&AISquad_aazVoiceTable[1984], "GV_49");
  strcpy(&AISquad_aazVoiceTable[2016], "GV_49");
  AISquad_aisVoiceDontPlayForSingleAI[6] = false;
  AISquad_aisVoiceDontPlayForSingleAI[7] = false;
  AISquad_aisVoiceDontPlayForSingleAI[8] = false;
  AISquad_aisVoiceDontPlayForSingleAI[9] = false;
  strcpy(&AISquad_aazVoiceTable[1312], "GV_48");
  strcpy(&AISquad_aazVoiceTable[1376], "GV_48");
  AISquad_aisVoiceDontPlayForSingleAI[10] = false;
  AISquad_aisVoiceDontPlayForSingleAI[15] = false;
  strcpy(&AISquad_aazVoiceTable[1408], "GV_62");
  strcpy(&AISquad_aazVoiceTable[1440], "GV_63");
  strcpy(&AISquad_aazVoiceTable[1472], "GV_64");
  strcpy(&AISquad_aazVoiceTable[1504], "GV_66");
  strcpy(&AISquad_aazVoiceTable[1536], "GV_75");
  strcpy(&AISquad_aazVoiceTable[1600], "GV_75");
  strcpy(&AISquad_aazVoiceTable[1664], "GV_80");
  strcpy(&AISquad_aazVoiceTable[1760], "GV_80");
  strcpy(&AISquad_aazVoiceTable[2048], "GV_87");
  strcpy(&AISquad_aazVoiceTable[2080], "GV_88");
  strcpy(&AISquad_aazVoiceTable[2112], "GV_89");
  strcpy(&AISquad_aazVoiceTable[1568], "GV_76");
  strcpy(&AISquad_aazVoiceTable[1632], "GV_76");
  strcpy(&AISquad_aazVoiceTable[2144], "GV_90");
  strcpy(&AISquad_aazVoiceTable[1696], "GV_81");
  strcpy(&AISquad_aazVoiceTable[1792], "GV_84");
  strcpy(&AISquad_aazVoiceTable[1824], "GV_84");
  strcpy(&AISquad_aazVoiceTable[1856], "GV_84");
  strcpy(&AISquad_aazVoiceTable[1888], "GV_84");
  strcpy(&AISquad_aazVoiceTable[2176], "GV_91");
  strcpy(&AISquad_aazVoiceTable[1728], "GV_82");
  strcpy(&AISquad_aazVoiceTable[2208], "GV_92");
  AISquad_aisVoiceDontPlayForSingleAI[11] = true;
  AISquad_aisVoiceDontPlayForSingleAI[12] = true;
  AISquad_aisVoiceDontPlayForSingleAI[13] = false;
  AISquad_aisVoiceDontPlayForSingleAI[16] = false;
  AISquad_aisVoiceDontPlayForSingleAI[14] = true;
  strcpy(&AISquad_aazVoiceTable[2240], "GV_93");
  strcpy(&AISquad_aazVoiceTable[2272], "GV_94");
  AISquad_aisVoiceDontPlayForSingleAI[17] = false;
  strcpy(&AISquad_aazVoiceTable[2304], "GV_60");
  strcpy(&AISquad_aazVoiceTable[2336], "GV_60");
  strcpy(&AISquad_aazVoiceTable[2368], "GV_60");
  strcpy(&AISquad_aazVoiceTable[2400], "GV_60");
  AISquad_aisVoiceDontPlayForSingleAI[18] = false;
}

// source: j/0/humanai/aisquad.c:534  [anchor-mhash]
int __cdecl AISquad_GetMemberIndexFromPointer(
        struct AISquad_s *ptAISquad,
        int iTeam,
        struct QTask_s *ptMemberToFindQTask)
{
  struct QTask_s *v3; // edx
  int ptParent; // ecx
  int result; // eax
  char *i; // edx

  v3 = &ptAISquad->tQTask + iTeam;
  ptParent = (int)v3[1].ptParent;
  result = 0;
  if ( ptParent <= 0 )
    return -1;
  for ( i = (char *)&v3[1]; *(struct QTask_s **)(*(_DWORD *)i + 8) != ptMemberToFindQTask; i += 4 )
  {
    if ( ++result >= ptParent )
      return -1;
  }
  return result;
}

// source: j/0/humanai/aisquad.c:561  [anchor-mhash]
int __cdecl AISquad_GetClosestMember(
        struct AISquad_s *ptAISquad,
        int iTeam,
        struct real64x3_t *ptPosition)
{
  struct QTask_s *v3; // eax
  int ptParent; // edi
  int v5; // esi
  int v6; // ecx
  char *v7; // ebx
  int v8; // eax
  double *v9; // eax
  double v10; // st3
  long double v11; // st4
  float tDelta; // [esp+8h] [ebp-Ch]
  float tDelta_4; // [esp+Ch] [ebp-8h]

  v3 = &ptAISquad->tQTask + iTeam;
  ptParent = (int)v3[1].ptParent;
  v5 = -1;
  v6 = 0;
  if ( ptParent > 0 )
  {
    v7 = (char *)&v3[1];
    do
    {
      v8 = *(_DWORD *)(*(_DWORD *)v7 + 8);
      if ( v8 )
      {
        v9 = *(double **)(v8 + 32);
        tDelta = ptPosition->vX - v9[5];
        tDelta_4 = ptPosition->vY - v9[6];
        v10 = ptPosition->vZ - v9[7];
        v11 = sqrt(tDelta * tDelta + tDelta_4 * tDelta_4 + v10 * v10);
        if ( v5 == -1 || *(float *)&ptAISquad < v11 )
        {
          *(float *)&ptAISquad = v11;
          v5 = v6;
        }
      }
      ++v6;
      v7 += 4;
    }
    while ( v6 < ptParent );
  }
  return v5;
}

// source: j/0/humanai/aisquad.c:612  [anchor-callee]
struct QTask_s *__cdecl AISquad_GetTeamLeader(struct QTask_s *ptQTask, int iTeam)
{
  struct QTask_s *v2; // eax

  v2 = &ptQTask[iTeam];
  if ( v2[1].ptParent )
    return v2[1].ptNext->tQTaskChildren.ptHead;
  else
    return nullptr;
}

// source: j/0/humanai/aisquad.c:637  [anchor-callee]
void __cdecl AISquad_ClearMembersPaths(struct QTask_s *ptQTask)
{
  struct QTask_s *v1; // ecx
  struct QTask_s **p_ptParent; // eax
  int v3; // ebp
  struct QTask_s **v4; // ebx
  struct HumanAI_s *ptHead; // edi
  bool v6; // cc
  int iT; // [esp+0h] [ebp-8h]
  struct QTask_s **v8; // [esp+4h] [ebp-4h]

  v1 = ptQTask;
  iT = 0;
  if ( (int)ptQTask[215].tQTaskRefList.ptTail > 0 )
  {
    p_ptParent = &ptQTask[1].ptParent;
    v8 = &ptQTask[1].ptParent;
    do
    {
      v3 = 0;
      if ( (int)*p_ptParent > 0 )
      {
        v4 = p_ptParent - 8;
        do
        {
          ptHead = (struct HumanAI_s *)(*v4)->tQTaskChildren.ptHead;
          if ( ptHead )
          {
            AIGraphAStarSearch_Clear(&ptHead->tAStarSearchData);
            LODWORD(ptHead->tCommon.tAimPosition.vZ) = HIDWORD(ptHead->tCommon.tAimPosition.vY);
            HumanAI_ClearMovementQueue(ptHead);
            p_ptParent = v8;
          }
          ++v3;
          ++v4;
        }
        while ( v3 < (int)*p_ptParent );
        v1 = ptQTask;
      }
      p_ptParent += 10;
      v6 = ++iT < (int)v1[215].tQTaskRefList.ptTail;
      v8 = p_ptParent;
    }
    while ( v6 );
  }
}

// source: j/0/humanai/aisquad.c:703  [anchor-mhash]
void __cdecl AISquad_RemoveEventFromMembersLists(struct QTask_s *ptQTask, int eEvent)
{
  struct QTask_s *v2; // eax
  int v3; // ebp
  struct QTask_s **p_ptParent; // ebx
  int v5; // edi
  struct QTask_s **v6; // esi
  struct HumanAI_s *ptHead; // eax

  v2 = ptQTask;
  v3 = 0;
  if ( (int)ptQTask[215].tQTaskRefList.ptTail > 0 )
  {
    p_ptParent = &ptQTask[1].ptParent;
    do
    {
      v5 = 0;
      if ( (int)*p_ptParent > 0 )
      {
        v6 = p_ptParent - 8;
        do
        {
          ptHead = (struct HumanAI_s *)(*v6)->tQTaskChildren.ptHead;
          if ( ptHead )
            HumanAI_RemoveEventsOfType(ptHead, eEvent);
          ++v5;
          ++v6;
        }
        while ( v5 < (int)*p_ptParent );
        v2 = ptQTask;
      }
      ++v3;
      p_ptParent += 10;
    }
    while ( v3 < (int)v2[215].tQTaskRefList.ptTail );
  }
}

// source: j/0/humanai/aisquad.c:736  [anchor-mhash]
struct QTask_s *__cdecl AISquad_FindSquadAreaCenter(
        struct QTask_s *ptQTask,
        struct real64x3_t *ptCenter)
{
  ptCenter->vX = 0.0;
  ptCenter->vY = 0.0;
  ptCenter->vZ = 0.0;
  if ( ptQTask[1].ptParent )
  {
    ptQTask = ptQTask[1].ptNext->tQTaskChildren.ptHead;
    if ( ptQTask )
    {
      ptQTask = ptQTask->ptParent;
      qmemcpy(ptCenter, &ptQTask[1], sizeof(struct real64x3_t));
    }
  }
  return ptQTask;
}

// source: j/0/humanai/aisquad.c:764  [anchor-callee]
void __cdecl AISquad_FindSquadAreaRadius(
        struct QTask_s *ptQTask,
        struct real64x3_t *ptCenter,
        float *pvRadius)
{
  struct QTask_s *v3; // eax
  int v4; // ebp
  struct QTask_s **p_ptParent; // edi
  int v6; // esi
  struct QTask_s **v7; // ecx
  double *ptParent; // eax
  double v9; // st3
  long double v10; // st4
  float tReal32x3; // [esp+4h] [ebp-Ch]
  float tReal32x3_4; // [esp+8h] [ebp-8h]

  v3 = ptQTask;
  *pvRadius = 0.0;
  v4 = 0;
  if ( (int)ptQTask[215].tQTaskRefList.ptTail > 0 )
  {
    p_ptParent = &ptQTask[1].ptParent;
    do
    {
      v6 = 0;
      if ( (int)*p_ptParent > 0 )
      {
        v7 = p_ptParent - 8;
        do
        {
          ptParent = (double *)(*v7)->tQTaskChildren.ptHead->ptParent;
          tReal32x3 = ptCenter->vX - ptParent[5];
          tReal32x3_4 = ptCenter->vY - ptParent[6];
          v9 = ptCenter->vZ - ptParent[7];
          v10 = sqrt(tReal32x3 * tReal32x3 + tReal32x3_4 * tReal32x3_4 + v9 * v9);
          if ( v10 > *pvRadius )
            *pvRadius = v10;
          ++v6;
          ++v7;
        }
        while ( v6 < (int)*p_ptParent );
        v3 = ptQTask;
      }
      ++v4;
      p_ptParent += 10;
    }
    while ( v4 < (int)v3[215].tQTaskRefList.ptTail );
  }
}

// source: j/0/humanai/aisquad.c:814  [size]
void __cdecl AISquad_RegisterScriptSymbolsHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { char zName[64]; };
    struct { char igi2_o1[64]; char zTemp[128]; };
    char igi2_extent[192];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)

  if ( !LOBYTE(ptQTask[218].ptNext) )
  {
    LOBYTE(ptQTask[218].ptNext) = 1;
    Level_GetUniqueQTaskNameFromTask(igi2_frame.zName, ptQTask);
    sprintf(igi2_frame.zTemp, "%s.isDead", igi2_frame.zName);
    Symbol_Register(
      igi2_frame.zTemp,
      (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_Int8,
      (char *)&ptQTask[218].ptNext + 1,
      1,
      QSCRIPT_SYMBOLCLASS_VARIABLE,
      QSCRIPT_SYMBOLTYPE_INT,
      QSCRIPT_SYMBOLLIFESPAN_FINITE);
  }
}

// source: j/0/humanai/aisquad.c:846  [anchor-mhash]
void __cdecl AISquad_RemoveScriptSymbolsHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { char zName[64]; };
    struct { char igi2_o1[64]; char zTemp[128]; };
    char igi2_extent[192];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)

  if ( LOBYTE(ptQTask[218].ptNext) )
  {
    LOBYTE(ptQTask[218].ptNext) = 0;
    Level_GetUniqueQTaskNameFromTask(igi2_frame.zName, ptQTask);
    sprintf(igi2_frame.zTemp, "%s.isDead", igi2_frame.zName);
    Symbol_Remove(igi2_frame.zTemp);
  }
}

// source: j/0/humanai/aisquad.c:877  [anchor-caller]
void __cdecl AISquad_PopMembersActionStacks(struct QTask_s *ptQTask)
{
  struct QTask_s *v1; // eax
  struct QTask_s **p_ptParent; // ebp
  int v3; // ebx
  struct QTask_s **v4; // esi
  struct HumanAI_s *ptHead; // edi
  int iI; // [esp+0h] [ebp-4h]

  v1 = ptQTask;
  iI = 0;
  if ( (int)ptQTask[215].tQTaskRefList.ptTail > 0 )
  {
    p_ptParent = &ptQTask[1].ptParent;
    do
    {
      v3 = 0;
      if ( (int)*p_ptParent > 0 )
      {
        v4 = p_ptParent - 8;
        do
        {
          ptHead = (struct HumanAI_s *)(*v4)->tQTaskChildren.ptHead;
          if ( ptHead )
            HumanAI_PopTopActionStackItems(ptHead);
          ++v3;
          ++v4;
        }
        while ( v3 < (int)*p_ptParent );
        v1 = ptQTask;
      }
      p_ptParent += 10;
      ++iI;
    }
    while ( iI < (int)v1[215].tQTaskRefList.ptTail );
  }
}

// source: j/0/humanai/aisquad.c:911  [anchor-callee]
void __cdecl AISquad_ClearMembersActionStacks(struct QTask_s *ptQTask)
{
  struct QTask_s *v1; // eax
  struct QTask_s **p_ptParent; // ebp
  int v3; // ebx
  struct QTask_s **v4; // esi
  struct HumanAI_s *ptHead; // edi
  int iI; // [esp+0h] [ebp-4h]

  v1 = ptQTask;
  iI = 0;
  if ( (int)ptQTask[215].tQTaskRefList.ptTail > 0 )
  {
    p_ptParent = &ptQTask[1].ptParent;
    do
    {
      v3 = 0;
      if ( (int)*p_ptParent > 0 )
      {
        v4 = p_ptParent - 8;
        do
        {
          ptHead = (struct HumanAI_s *)(*v4)->tQTaskChildren.ptHead;
          if ( ptHead )
            HumanAI_ClearActionStack(ptHead);
          ++v3;
          ++v4;
        }
        while ( v3 < (int)*p_ptParent );
        v1 = ptQTask;
      }
      p_ptParent += 10;
      ++iI;
    }
    while ( iI < (int)v1[215].tQTaskRefList.ptTail );
  }
}

// source: j/0/humanai/aisquad.c:945  [anchor-callee]
void __cdecl AISquad_RemoveLastEvent(struct QTask_s *ptQTask)
{
  int v1; // eax
  int v2; // ebx
  char *v3; // esi
  struct QReference_s *v4; // eax
  int v5; // ebx
  struct MemPoolFreeItem_s *v6; // eax

  v1 = *(_DWORD *)&ptQTask[215].eQTaskType;
  if ( v1 > 0 )
  {
    v2 = v1 - 1;
    v3 = (char *)&ptQTask[-2] + 112 * v1 - 32;
    v4 = *((struct QReference_s **)v3 + 41);
    if ( v4 )
      QReference_Delete(v4, &QTask_tQTaskRefPool);
    if ( *((_DWORD *)v3 + 32) )
    {
      v5 = 28 * v2;
      do
      {
        v6 = *((struct MemPoolFreeItem_s **)&ptQTask[3].tQTaskChildren.ptHead + v5 + *((_DWORD *)v3 + 32));
        if ( v6->ptNext )
          v6 = (struct MemPoolFreeItem_s *)Node_Remove(v6);
        --QTask_tQTaskRefPool.nAllocatedBlocks;
        v6->ptNext = QTask_tQTaskRefPool.tMemPoolFreeList.ptHead;
        QTask_tQTaskRefPool.tMemPoolFreeList.ptHead = v6;
      }
      while ( (*((_DWORD *)v3 + 32))-- != 1 );
    }
    --*(_DWORD *)&ptQTask[215].eQTaskType;
  }
}

// source: j/0/humanai/aisquad.c:982  [anchor-callee]
void __cdecl AISquad_ClearTargetLists(struct QTask_s *ptQTask)
{
  struct QTask_s *v1; // ebx
  int v2; // edi
  struct MemPoolFreeItem_s **p_tQTaskChildren; // esi
  struct MemPoolFreeItem_s *v4; // eax
  struct QReference_s *ptTail; // eax
  struct QTask_s **p_ptParent; // ebp
  int v7; // esi
  struct QTask_s **v8; // ebx
  int iI; // [esp+10h] [ebp-4h]

  v1 = ptQTask;
  v2 = 0;
  if ( (int)ptQTask[215].tQTaskRefList.ptMiddle > 0 )
  {
    p_tQTaskChildren = (struct MemPoolFreeItem_s **)&ptQTask[182].tQTaskChildren;
    do
    {
      v4 = *p_tQTaskChildren;
      if ( (*p_tQTaskChildren)->ptNext )
        v4 = (struct MemPoolFreeItem_s *)Node_Remove(v4);
      --QTask_tQTaskRefPool.nAllocatedBlocks;
      v4->ptNext = QTask_tQTaskRefPool.tMemPoolFreeList.ptHead;
      QTask_tQTaskRefPool.tMemPoolFreeList.ptHead = v4;
      *p_tQTaskChildren = nullptr;
      ++v2;
      p_tQTaskChildren += 10;
    }
    while ( v2 < (int)ptQTask[215].tQTaskRefList.ptMiddle );
  }
  ptTail = ptQTask[215].tQTaskRefList.ptTail;
  ptQTask[215].tQTaskRefList.ptMiddle = nullptr;
  iI = 0;
  if ( (int)ptTail > 0 )
  {
    p_ptParent = &ptQTask[1].ptParent;
    do
    {
      v7 = 0;
      if ( (int)*p_ptParent > 0 )
      {
        v8 = p_ptParent - 8;
        do
        {
          AIDetection_ClearDetection((struct AIDetection_s *)&(*v8)->tQTaskChildren.ptHead[222]);
          ++v7;
          ++v8;
        }
        while ( v7 < (int)*p_ptParent );
        v1 = ptQTask;
      }
      p_ptParent += 10;
      ++iI;
    }
    while ( iI < (int)v1[215].tQTaskRefList.ptTail );
  }
}

// source: j/0/humanai/aisquad.c:1021  [anchor-callee]
void __cdecl AISquad_SendFireOrder(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct HumanAI_s *v6; };
    struct { char igi2_o1[20]; struct QTask_s **p_ptParent; };
    struct { char igi2_o2[24]; int iCount; };
    struct { char igi2_o3[28]; struct AISquadOrderContext_s tOrderContext; };
    char igi2_extent[88];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v1; // esi
  int v2; // ebx
  int v3; // eax
  int v4; // ecx
  int v5; // edx

  v1 = 0;
  v2 = 0;
  v3 = 0;
  igi2_frame.iCount = 0;
  if ( ptQTask[215].tQTaskRefList.ptMiddle )
  {
    if ( (int)ptQTask[216].ptNext <= 0 )
    {
LABEL_14:
      if ( *(_DWORD *)&ptQTask[v2 + 1].eQTaskType == 1 )
      {
        igi2_frame.tOrderContext.uContext.tMoveToNodeContext.isRun = (int)ptQTask[215].tQTaskRefList.ptMiddle;
        igi2_frame.tOrderContext.uContext.tMoveToNodeContext.nNodeId = (int)&ptQTask[182].tQTaskChildren;
        igi2_frame.v6 = *(struct HumanAI_s **)(*((_DWORD *)&ptQTask[v2 + 1].ptNext + v3) + 8);
        igi2_frame.tOrderContext.eOrder = AISQUAD_ORDER_FIRE;
        igi2_frame.tOrderContext.iDelay = 0;
        HumanAIContent_ReceiveSquadOrder(igi2_frame.v6, &igi2_frame.tOrderContext);
      }
    }
    else
    {
      igi2_frame.p_ptParent = &ptQTask[1].ptParent;
      while ( 1 )
      {
        if ( v3 < (int)*igi2_frame.p_ptParent )
        {
          v4 = *(_DWORD *)(*((_DWORD *)&ptQTask[v1 + 1].ptNext + v3) + 8);
          if ( v4 )
          {
            v5 = *(_DWORD *)(v4 + 4752);
            if ( *(_DWORD *)v5 )
            {
              if ( v5
                && *(enum bool (__cdecl **)(struct HumanAI_s *, struct HumanAIActionStackItem_s *))(v5 + 44) == HumanAIContent_FireAtTargetPositionCB
                && !*(_DWORD *)(v4 + 29908)
                && *(_BYTE *)(v4 + 29905) )
              {
                break;
              }
            }
          }
        }
        ++v3;
        ++igi2_frame.iCount;
        if ( v3 >= (int)*igi2_frame.p_ptParent )
        {
          ++v2;
          ++v1;
          igi2_frame.p_ptParent += 10;
          v3 = 0;
        }
        if ( igi2_frame.iCount >= (int)ptQTask[216].ptNext )
          goto LABEL_14;
      }
    }
  }
}

// source: j/0/humanai/aisquad.c:1095  [anchor-callee]
int __cdecl AISquad_GetFirstMemberWithVisibleTarget(struct QTask_s *ptQTask, int iTeam)
{
  struct QTask_s *v2; // eax
  int ptParent; // edi
  int v4; // esi
  struct QTask_s *i; // ebx

  v2 = &ptQTask[iTeam];
  ptParent = (int)v2[1].ptParent;
  v4 = 0;
  if ( ptParent <= 0 )
    return -1;
  for ( i = v2 + 1;
        HumanAI_GetNumberOfVisibleTargets(i->ptNext->tQTaskChildren.ptHead) <= 0;
        i = (struct QTask_s *)((char *)i + 4) )
  {
    if ( ++v4 >= ptParent )
      return -1;
  }
  return v4;
}

// source: j/0/humanai/aisquad.c:1129  [anchor-callee]
int __cdecl AISquad_GetFirstMemberWithoutVisibleTarget(struct QTask_s *ptQTask, int iTeam)
{
  struct QTask_s *v2; // eax
  int ptParent; // edi
  int v4; // esi
  struct QTask_s *i; // ebx

  v2 = &ptQTask[iTeam];
  ptParent = (int)v2[1].ptParent;
  v4 = 0;
  if ( ptParent <= 0 )
    return -1;
  for ( i = v2 + 1;
        HumanAI_GetNumberOfVisibleTargets(i->ptNext->tQTaskChildren.ptHead);
        i = (struct QTask_s *)((char *)i + 4) )
  {
    if ( ++v4 >= ptParent )
      return -1;
  }
  return v4;
}

// source: j/0/humanai/aisquad.c:1163  [anchor-mhash]
int __cdecl AISquad_GetNumberOfMembersWithVisibleTargets(struct QTask_s *ptQTask, int iTeam)
{
  struct QTask_s *v2; // eax
  int v3; // ebx
  struct QTask_s *v4; // esi
  struct QTask_s *ptParent; // edi
  struct HumanAI_s *ptHead; // eax

  v2 = &ptQTask[iTeam];
  v3 = 0;
  if ( (int)v2[1].ptParent > 0 )
  {
    v4 = v2 + 1;
    ptParent = v2[1].ptParent;
    do
    {
      ptHead = (struct HumanAI_s *)v4->ptNext->tQTaskChildren.ptHead;
      if ( ptHead && HumanAI_GetTargetQTask(ptHead, true) )
        ++v3;
      v4 = (struct QTask_s *)((char *)v4 + 4);
      ptParent = (struct QTask_s *)((char *)ptParent - 1);
    }
    while ( ptParent );
  }
  return v3;
}

// source: j/0/humanai/aisquad.c:1198  [anchor-mhash]
int __cdecl AISquad_MakeTeamLeader(struct QTask_s *ptQTask, int iTeam, int iTeamMember)
{
  struct QTask_s *v3; // ecx
  int result; // eax
  struct QTask_s *ptNext; // esi

  v3 = &ptQTask[iTeam + 1];
  result = (int)&ptQTask[iTeam + 1] + 4 * iTeamMember;
  ptNext = v3->ptNext;
  v3->ptNext = *(struct QTask_s **)result;
  *(_DWORD *)result = ptNext;
  return result;
}

// source: j/0/humanai/aisquad.c:1222  [anchor-mhash]
void __cdecl AISquad_MakeMemberQTaskTeamLeader(
        struct QTask_s *ptQTask,
        int iTeam,
        struct QTask_s *ptMemberQTask)
{
  struct QTask_s *v3; // ecx
  int ptParent; // esi
  int v5; // eax
  struct QTask_s *v6; // ebx
  struct QTask_s *i; // edi
  struct QTask_s *ptNext; // ecx
  struct QTask_s **v9; // eax

  v3 = &ptQTask[iTeam];
  ptParent = (int)v3[1].ptParent;
  v5 = 0;
  if ( ptParent > 0 )
  {
    v6 = v3 + 1;
    for ( i = v3 + 1; !i->ptNext || i->ptNext->tQTaskChildren.ptHead != ptMemberQTask; i = (struct QTask_s *)((char *)i + 4) )
    {
      if ( ++v5 >= ptParent )
        return;
    }
    ptNext = v6->ptNext;
    v9 = &ptQTask[iTeam + 1].ptNext + v5;
    v6->ptNext = *v9;
    *v9 = ptNext;
  }
}

// source: j/0/humanai/aisquad.c:1253  [anchor-callee]
int __cdecl AISquad_GetMemberCount(struct QTask_s *ptQTask)
{
  struct QReference_s *ptTail; // edx
  int result; // eax
  _DWORD *p_ptParent; // ecx

  ptTail = ptQTask[215].tQTaskRefList.ptTail;
  result = 0;
  if ( (int)ptTail > 0 )
  {
    p_ptParent = &ptQTask[1].ptParent;
    do
    {
      result += *p_ptParent;
      p_ptParent += 10;
      ptTail = (struct QReference_s *)((char *)ptTail - 1);
    }
    while ( ptTail );
  }
  return result;
}

// source: j/0/humanai/aisquad.c:1283  [anchor-hash]
struct QTask_s *__cdecl AISquad_MakeOneTeam(struct QTask_s *ptQTask)
{
  int v1; // edx
  struct QTask_s *v2; // ecx

  v1 = 0;
  if ( (int)ptQTask[2].ptParent > 0 )
  {
    v2 = ptQTask + 2;
    do
    {
      *((_DWORD *)&ptQTask[1].ptNext + (int)ptQTask[1].ptParent) = v2->ptNext;
      v2->ptNext = nullptr;
      ++*(int *)&ptQTask[1].ptParent;
      ++v1;
      v2 = (struct QTask_s *)((char *)v2 + 4);
    }
    while ( v1 < (int)ptQTask[2].ptParent );
  }
  ptQTask[2].ptParent = nullptr;
  ptQTask[215].tQTaskRefList.ptTail = (struct QReference_s *)1;
  return ptQTask;
}

// source: j/0/humanai/aisquad.c:1316  [anchor-hash]
void __cdecl AISquad_MakeTwoTeams(struct QTask_s *ptQTask)
{
  struct QTask_s *ptParent; // kr00_4
  int v2; // ecx
  struct QTask_s *v3; // edi
  struct QTask_s *v4; // eax
  struct QTask_s *v5; // eax

  AISquad_MakeOneTeam(ptQTask);
  ptParent = ptQTask[1].ptParent;
  if ( (int)ptParent / 2 > 0 )
  {
    v2 = (int)ptParent / 2;
    do
    {
      v3 = ptQTask[2].ptParent;
      v4 = (struct QTask_s *)((char *)ptQTask[1].ptParent - 1);
      ptQTask[1].ptParent = v4;
      *((_DWORD *)&ptQTask[2].ptNext + (_DWORD)v3) = *((_DWORD *)&ptQTask[1].ptNext + (_DWORD)v4);
      v5 = ptQTask[1].ptParent;
      --v2;
      ++*(int *)&ptQTask[2].ptParent;
      *((_DWORD *)&ptQTask[1].ptNext + (_DWORD)v5) = 0;
    }
    while ( v2 );
  }
  ptQTask[215].tQTaskRefList.ptTail = (struct QReference_s *)2;
}

// source: j/0/humanai/aisquad.c:1345  [anchor-callee]
void __cdecl AISquad_UpdateMemberCount(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { int nSquadMembers; };
    struct { char igi2_o1[4]; int iI; };
    struct { char igi2_o2[8]; struct QReference_s *aptQTaskRef[8]; };
    char igi2_extent[40];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *v1; // edi
  int v2; // ebx
  int *p_ptParent; // esi
  int v4; // ebp
  struct MemPoolFreeItem_s **v5; // edi
  struct MemPoolFreeItem_s *v6; // eax
  struct MemPoolFreeItem_s *ptNext; // ecx
  int v8; // eax
  int *v9; // ecx
  int v10; // eax
  struct QTask_s **v11; // ecx
  struct QTask_s **v12; // edx
  int v13; // edx
  struct QTask_s *v14; // eax

  v1 = ptQTask;
  v2 = 0;
  igi2_frame.nSquadMembers = 0;
  igi2_frame.iI = 0;
  if ( (int)ptQTask[215].tQTaskRefList.ptTail > 0 )
  {
    p_ptParent = (int *)&ptQTask[1].ptParent;
    do
    {
      v4 = 0;
      if ( *p_ptParent > 0 )
      {
        v5 = (struct MemPoolFreeItem_s **)(p_ptParent - 8);
        do
        {
          v6 = *v5;
          ptNext = (*v5)[2].ptNext;
          if ( !ptNext || LOBYTE(ptNext[8].ptNext[295].ptNext) )
          {
            if ( v6->ptNext )
              v6 = (struct MemPoolFreeItem_s *)Node_Remove(v6);
            --QTask_tQTaskRefPool.nAllocatedBlocks;
            v6->ptNext = QTask_tQTaskRefPool.tMemPoolFreeList.ptHead;
            QTask_tQTaskRefPool.tMemPoolFreeList.ptHead = v6;
          }
          else
          {
            igi2_frame.aptQTaskRef[v4++] = (struct QReference_s *)v6;
            ++igi2_frame.nSquadMembers;
          }
          *v5 = nullptr;
          ++v2;
          ++v5;
        }
        while ( v2 < *p_ptParent );
        v1 = ptQTask;
      }
      v2 = 0;
      v8 = 0;
      *p_ptParent = v4;
      if ( v4 > 0 )
      {
        v9 = p_ptParent - 8;
        do
          *v9++ = (int)igi2_frame.aptQTaskRef[v8++];
        while ( v8 < *p_ptParent );
      }
      p_ptParent += 10;
      ++igi2_frame.iI;
    }
    while ( igi2_frame.iI < (int)v1[215].tQTaskRefList.ptTail );
  }
  v10 = 0;
  if ( (int)v1[215].tQTaskRefList.ptTail > 0 )
  {
    v11 = &v1[1].ptParent;
    v12 = &v1[1].ptParent;
    while ( *v12 )
    {
      ++v10;
      v12 += 10;
      if ( v10 >= (int)v1[215].tQTaskRefList.ptTail )
        goto LABEL_26;
    }
    v13 = 0;
    if ( (int)v1[2].ptParent > 0 )
    {
      v14 = v1 + 2;
      do
      {
        *((_DWORD *)&v1[1].ptNext + (_DWORD)*v11) = v14->ptNext;
        v14->ptNext = nullptr;
        *v11 = (struct QTask_s *)((char *)*v11 + 1);
        ++v13;
        v14 = (struct QTask_s *)((char *)v14 + 4);
      }
      while ( v13 < (int)v1[2].ptParent );
    }
    v1[2].ptParent = nullptr;
    v1[215].tQTaskRefList.ptTail = (struct QReference_s *)1;
  }
LABEL_26:
  BYTE1(v1[218].ptNext) = igi2_frame.nSquadMembers == 0;
  if ( !igi2_frame.nSquadMembers )
    AISquad_ClearTargetLists(v1);
}

// source: j/0/humanai/aisquad.c:1424  [anchor-callee]
void __cdecl AISquad_MaintainTargetList(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { int iI; };
    struct { char igi2_o1[4]; struct QReference_s *v9; };
    struct { char igi2_o2[8]; struct real64x3_t tLastTargetPos; };
    struct { char igi2_o3[32]; struct AISquadEventContext_s tEventContext; };
    char igi2_extent[148];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QReference_s *ptMiddle; // eax
  bool v2; // zf
  struct QTaskNodeList_s *p_tQTaskChildren; // ebp
  struct QReference_s *ptHead; // eax
  int ptTail; // ecx
  int v6; // edx
  struct QReference_s *v7; // eax

  ptMiddle = ptQTask[215].tQTaskRefList.ptMiddle;
  v2 = ptMiddle == nullptr;
  igi2_frame.iI = 0;
  igi2_frame.v9 = ptMiddle;
  if ( (int)ptMiddle > 0 )
  {
    p_tQTaskChildren = &ptQTask[182].tQTaskChildren;
    do
    {
      ptHead = (struct QReference_s *)p_tQTaskChildren->ptHead;
      if ( p_tQTaskChildren->ptHead->tQTaskChildren.ptHead )
      {
        ptTail = (int)p_tQTaskChildren[2].ptTail;
        v6 = 30 * (int)ptQTask[218].tQTaskRefList.ptHead;
        p_tQTaskChildren[2].ptTail = (struct QTask_s *)(ptTail + 1);
        if ( ptTail >= v6 )
        {
          qmemcpy(&igi2_frame.tLastTargetPos, (char *)ptHead->pxObject + 40, sizeof(igi2_frame.tLastTargetPos));
          QReference_Delete(ptHead, &QTask_tQTaskRefPool);
          v7 = (struct QReference_s *)((char *)ptQTask[215].tQTaskRefList.ptMiddle - 1);
          ptQTask[215].tQTaskRefList.ptMiddle = v7;
          qmemcpy(p_tQTaskChildren, &ptQTask[(int)v7 + 182].tQTaskChildren, 0x28u);
        }
        else
        {
          ++igi2_frame.iI;
          p_tQTaskChildren = (struct QTaskNodeList_s *)((char *)p_tQTaskChildren + 40);
        }
      }
    }
    while ( igi2_frame.iI < (int)ptQTask[215].tQTaskRefList.ptMiddle );
    v2 = igi2_frame.v9 == nullptr;
  }
  if ( !v2 && !ptQTask[215].tQTaskRefList.ptMiddle )
  {
    if ( ptQTask[218].ptPrev != (struct QTask_s *)2 )
      AISquad_PopMembersActionStacks(ptQTask);
    memset(&igi2_frame.tEventContext.nPriority, 0, 12);
    igi2_frame.tEventContext.ptReferenceQTaskRef = nullptr;
    igi2_frame.tEventContext.eEvent = 27;
    qmemcpy(&igi2_frame.tEventContext.tPosition, &igi2_frame.tLastTargetPos, sizeof(igi2_frame.tEventContext.tPosition));
    AISquad_ReceiveEvent(ptQTask, &igi2_frame.tEventContext);
  }
}

// source: j/0/humanai/aisquad.c:1498  [anchor-hash]
struct QTask_s *__cdecl AISquad_MaintainMisc(struct QTask_s *ptQTask)
{
  struct QReference_s *ptHead; // ecx
  int v2; // ecx
  struct QReference_s *ptTail; // esi
  _DWORD *p_ptParent; // edx
  struct QTask_s *ptNext; // edx
  struct QTask_s *v6; // ecx
  struct QTask_s *ptMiddle; // ecx
  struct QReference_s *v8; // ecx
  struct QReference_s *v9; // ecx
  struct QReference_s *v10; // ecx

  ptHead = ptQTask[215].tQTaskRefList.ptHead;
  if ( (int)ptHead > 0 )
    ptQTask[215].tQTaskRefList.ptHead = (struct QReference_s *)((char *)ptHead - 1);
  v2 = 0;
  if ( (int)ptQTask[215].tQTaskRefList.ptTail > 0 )
  {
    ptTail = ptQTask[215].tQTaskRefList.ptTail;
    p_ptParent = &ptQTask[1].ptParent;
    do
    {
      v2 += *p_ptParent;
      p_ptParent += 10;
      ptTail = (struct QReference_s *)((char *)ptTail - 1);
    }
    while ( ptTail );
  }
  ptNext = ptQTask[216].ptNext;
  if ( (int)ptNext >= v2 - 1 )
    ptQTask[216].ptNext = nullptr;
  else
    ptQTask[216].ptNext = (struct QTask_s *)((char *)&ptNext->ptNext + 1);
  v6 = ptQTask[216].tQTaskChildren.ptHead;
  if ( v6 )
    ptQTask[216].tQTaskChildren.ptHead = (struct QTask_s *)((char *)v6 - 1);
  ptMiddle = ptQTask[216].tQTaskChildren.ptMiddle;
  if ( ptMiddle )
    ptQTask[216].tQTaskChildren.ptMiddle = (struct QTask_s *)((char *)ptMiddle - 1);
  else
    ptQTask[216].tQTaskChildren.ptMiddle = (struct QTask_s *)60;
  v8 = ptQTask[216].tQTaskRefList.ptHead;
  if ( v8 )
  {
    ptQTask[216].tQTaskRefList.ptHead = (struct QReference_s *)((char *)v8 - 1);
  }
  else
  {
    v9 = ptQTask[216].tQTaskRefList.ptMiddle;
    if ( v9 )
      ptQTask[216].tQTaskRefList.ptMiddle = (struct QReference_s *)((char *)v9 - 1);
  }
  v10 = ptQTask[216].tQTaskRefList.ptTail;
  if ( v10 )
    ptQTask[216].tQTaskRefList.ptTail = (struct QReference_s *)((char *)v10 - 1);
  return ptQTask;
}

// source: j/0/humanai/aisquad.c:1544  [anchor-callee]
int __cdecl AISquad_SetFormation(struct QTask_s *ptQTask, int iTeam, enum AISquadFormation_e eFormation)
{
  struct QTask_s *v3; // edi
  struct QTask_s *ptParent; // eax
  int ptHead; // eax
  int result; // eax
  int i; // esi
  struct HumanAI_s *v8; // ebx
  void (__cdecl *pfRunCallback)(struct HumanAI_s *, struct HumanAIActionStackItem_s *); // eax
  int OrderDelay; // eax
  double v11; // st7
  __int32 v12; // ecx
  __int64 v13; // rax
  double v14; // st7
  float vY; // edx
  float vZ; // eax
  struct AISquadOrderContext_s tOrderContext; // [esp+10h] [ebp-3Ch] BYREF

  v3 = &ptQTask[iTeam];
  ptParent = v3[1].ptParent;
  tOrderContext.eOrder = AISQUAD_ORDER_FORMATION;
  if ( ptParent )
    ptHead = (int)v3[1].ptNext->tQTaskChildren.ptHead;
  else
    ptHead = 0;
  tOrderContext.uContext.tMoveToNodeContext.nNodeId = ptHead;
  result = (int)v3[1].ptParent;
  for ( i = 1; i < result; ++i )
  {
    v8 = *(struct HumanAI_s **)(*((_DWORD *)&v3[1].ptNext + i) + 8);
    pfRunCallback = v8->atActionStackItemList[0].pfRunCallback;
    if ( !*(_DWORD *)pfRunCallback
      || !pfRunCallback
      || *((void (__cdecl **)(struct HumanAI_s *, struct HumanAIActionStackItem_s *))pfRunCallback + 6) != HumanAIContent_MoveInFormationSquadOrderInitCB )
    {
      OrderDelay = AISquad_GetOrderDelay((struct AISquad_s *)ptQTask);
      v11 = *(float *)&ptQTask[218].ptParent;
      tOrderContext.iDelay = OrderDelay;
      v12 = i + 8 * eFormation;
      tOrderContext.uContext.tSetFormationContext.tRelativeDirection.vX = AISquad_aatFormationData[0][v12].tRelativeDirection.vX;
      v13 = *(_QWORD *)&AISquad_aatFormationData[0][v12].tRelativeDirection.vY;
      tOrderContext.uContext.tSetFormationContext.tRelativeDirection.vY = AISquad_aatFormationData[0][v12].tRelativeDirection.vY;
      tOrderContext.uContext.tLookInApproxDirectionOrderContext.nTimer = HIDWORD(v13);
      if ( v11 <= 0.0 )
        v14 = *(float *)&ptQTask[218].tQTaskRefList.ptTail;
      else
        v14 = *(float *)&ptQTask[218].ptParent;
      vY = AISquad_aatFormationData[0][v12].tRelativePosition.vY;
      vZ = AISquad_aatFormationData[0][v12].tRelativePosition.vZ;
      tOrderContext.uContext.tHoldAreaContext.tDirection.vY = AISquad_aatFormationData[0][v12].tRelativePosition.vX
                                                            * v14
                                                            * 4096.0;
      tOrderContext.uContext.tHoldAreaContext.tDirection.vZ = vY * v14 * 4096.0;
      tOrderContext.uContext.tSetFormationContext.tRelativePosition.vZ = vZ * v14 * 4096.0;
      HumanAIContent_ReceiveSquadOrder(v8, &tOrderContext);
    }
    result = (int)v3[1].ptParent;
  }
  return result;
}

// source: j/0/humanai/aisquad.c:1601  [anchor-callee]
void __cdecl AISquad_InitFormations()
{
  float *p_vY; // eax
  int v1; // eax
  float *v2; // ecx
  double v3; // st7
  double v4; // st6
  float *v5; // eax
  float *v6; // ebx
  long double v7; // st7
  double v8; // st7
  int v9; // ecx
  float *v10; // eax
  double v11; // st7
  double v12; // st7
  int v13; // eax
  float *v14; // ecx
  double v15; // st7
  int iI; // [esp+8h] [ebp-14h]
  int iIa; // [esp+8h] [ebp-14h]
  float tReal32x3; // [esp+10h] [ebp-Ch]
  float tReal32x3_4; // [esp+14h] [ebp-8h]

  p_vY = &AISquad_aatFormationData[0][0].tRelativeDirection.vY;
  do
  {
    *(p_vY - 1) = 0.0;
    *p_vY = 0.0;
    p_vY[1] = 0.0;
    *(p_vY - 4) = 0.0;
    *(p_vY - 3) = 0.0;
    *(p_vY - 2) = 0.0;
    p_vY += 7;
  }
  while ( (int)p_vY < 7672004 );
  *(_QWORD *)&AISquad_aatFormationData[1][0].tRelativeDirection.vY = 0;
  *(_QWORD *)&AISquad_aatFormationData[1][0].tRelativePosition.vX = 0;
  *(_QWORD *)&AISquad_aatFormationData[1][0].tRelativePosition.vZ = 0;
  v1 = 1;
  v2 = &AISquad_aatFormationData[1][1].tRelativeDirection.vY;
  do
  {
    if ( (v1 & 1) != 0 )
      v3 = -1.0;
    else
      v3 = 1.0;
    *(v2 - 1) = 0.0;
    v4 = (double)((v1 + 1) / 2);
    *v2 = 1.0;
    v2[1] = 0.0;
    *(v2 - 2) = 0.0;
    v2 += 7;
    ++v1;
    *(v2 - 11) = v4 * v3;
    *(v2 - 10) = v4 * -1.0;
  }
  while ( (int)v2 < 7672228 );
  *(_QWORD *)&AISquad_aatFormationData[2][0].tRelativeDirection.vY = 0;
  *(_QWORD *)&AISquad_aatFormationData[2][0].tRelativePosition.vX = 0;
  *(_QWORD *)&AISquad_aatFormationData[2][0].tRelativePosition.vZ = 0;
  iI = 1;
  v5 = &AISquad_aatFormationData[2][1].tRelativePosition.vY;
  do
  {
    v6 = v5 + 2;
    v5 += 7;
    v7 = (double)iI * 0.7853981852531433;
    tReal32x3 = -sin(v7);
    *(v5 - 8) = tReal32x3;
    *v6 = tReal32x3;
    tReal32x3_4 = cos(v7);
    *(v5 - 7) = tReal32x3_4;
    *(v5 - 6) = 0.0;
    v8 = *(v5 - 7) - 1.0;
    v6[1] = tReal32x3_4;
    v6[2] = 0.0;
    *(v5 - 7) = v8;
    ++iI;
  }
  while ( (int)v5 < 7672440 );
  v9 = 1;
  *(_QWORD *)&AISquad_aatFormationData[3][0].tRelativeDirection.vY = 0;
  *(_QWORD *)&AISquad_aatFormationData[3][0].tRelativePosition.vX = 0;
  *(_QWORD *)&AISquad_aatFormationData[3][0].tRelativePosition.vZ = 0;
  iIa = 1;
  v10 = &AISquad_aatFormationData[3][1].tRelativeDirection.vY;
  do
  {
    if ( (v9 & 1) != 0 )
      v11 = -1.0;
    else
      v11 = 1.0;
    *(v10 - 1) = v11;
    *v10 = 1.0;
    *(v10 - 4) = v11;
    v10[1] = 0.0;
    *(v10 - 2) = 0.0;
    ++v9;
    v10 += 7;
    v12 = (double)iIa * -1.0;
    iIa = v9;
    *(v10 - 10) = v12;
  }
  while ( (int)v10 < 7672676 );
  *(_QWORD *)&AISquad_aatFormationData[4][0].tRelativeDirection.vY = 0;
  *(_QWORD *)&AISquad_aatFormationData[4][0].tRelativePosition.vX = 0;
  *(_QWORD *)&AISquad_aatFormationData[4][0].tRelativePosition.vZ = 0;
  v13 = 1;
  v14 = &AISquad_aatFormationData[4][1].tRelativeDirection.vY;
  do
  {
    if ( (v13 & 1) != 0 )
      v15 = -1.0;
    else
      v15 = 1.0;
    *(v14 - 1) = 0.0;
    *v14 = 1.0;
    v14[1] = 0.0;
    *(v14 - 2) = 0.0;
    v14 += 7;
    *(v14 - 11) = (double)(++v13 / 2) * v15;
    *(v14 - 10) = (double)v13 * 0.5;
  }
  while ( (int)v14 < 7672900 );
}

// source: j/0/humanai/aisquad.c:1691  [anchor-mhash]
struct AISquadEventContext_s *__cdecl AISquad_GetCurrentEvent(struct QTask_s *ptQTask)
{
  int v1; // eax

  v1 = *(_DWORD *)&ptQTask[215].eQTaskType;
  if ( v1 <= 0 )
    return nullptr;
  else
    return (struct AISquadEventContext_s *)((char *)&ptQTask->tQTaskChildren + 112 * v1);
}

// source: j/0/humanai/aisquad.c:1719  [anchor-mhash]
struct AISquadOrderContext_s *__cdecl AISquad_SendOrderToSquad(
        struct QTask_s *ptQTask,
        struct AISquadOrderContext_s *ptOrder)
{
  struct AISquadOrderContext_s *result; // eax
  struct QTask_s **p_ptParent; // ebp
  int v5; // edi
  struct QTask_s **v6; // esi
  int iT; // [esp+4h] [ebp-4h]

  result = (struct AISquadOrderContext_s *)ptQTask;
  iT = 0;
  if ( (int)ptQTask[215].tQTaskRefList.ptTail > 0 )
  {
    p_ptParent = &ptQTask[1].ptParent;
    do
    {
      v5 = 0;
      if ( (int)*p_ptParent > 0 )
      {
        v6 = p_ptParent - 8;
        do
        {
          if ( (*v6)->tQTaskChildren.ptHead )
            HumanAIContent_ReceiveSquadOrder((struct HumanAI_s *)(*v6)->tQTaskChildren.ptHead, ptOrder);
          ++v5;
          ++v6;
        }
        while ( v5 < (int)*p_ptParent );
        result = (struct AISquadOrderContext_s *)ptQTask;
      }
      p_ptParent += 10;
      ++iT;
    }
    while ( iT < result[154].iDelay );
  }
  return result;
}

// source: j/0/humanai/aisquad.c:1753  [anchor-mhash]
int __cdecl AISquad_SendOrderToTeam(
        struct QTask_s *ptQTask,
        int iTeam,
        struct AISquadOrderContext_s *ptOrder)
{
  struct QTask_s *v3; // esi
  int result; // eax
  int v5; // edi
  struct QTask_s *v7; // ebp

  v3 = &ptQTask[iTeam];
  result = (int)v3[1].ptParent;
  v5 = 0;
  if ( result > 0 )
  {
    v7 = v3 + 1;
    do
    {
      if ( v7->ptNext->tQTaskChildren.ptHead )
        HumanAIContent_ReceiveSquadOrder((struct HumanAI_s *)v7->ptNext->tQTaskChildren.ptHead, ptOrder);
      result = (int)v3[1].ptParent;
      ++v5;
      v7 = (struct QTask_s *)((char *)v7 + 4);
    }
    while ( v5 < result );
  }
  return result;
}

// source: j/0/humanai/aisquad.c:1783  [anchor-callee]
float __cdecl AISquad_GetDistanceToTarget(struct QTask_s *ptQTask, int iTeam)
{
  int v2; // eax
  struct QTask_s *ptParent; // ecx
  struct QTask_s *v4; // eax
  struct QTask_s *ptHead; // eax
  double *v6; // ecx
  double *v7; // eax
  double v8; // st3
  float tReal32x3; // [esp+0h] [ebp-Ch]
  float tReal32x3_4; // [esp+4h] [ebp-8h]

  v2 = iTeam;
  ptParent = ptQTask[v2 + 1].ptParent;
  v4 = &ptQTask[v2];
  if ( ptParent
    && (ptHead = v4[1].ptNext->tQTaskChildren.ptHead) != nullptr
    && ptQTask[215].tQTaskRefList.ptMiddle
    && (v6 = (double *)ptHead->ptParent,
        (v7 = (double *)ptQTask[182].tQTaskChildren.ptHead->tQTaskChildren.ptHead) != nullptr) )
  {
    tReal32x3 = v6[5] - v7[5];
    tReal32x3_4 = v6[6] - v7[6];
    v8 = v6[7] - v7[7];
    return sqrt(tReal32x3 * tReal32x3 + tReal32x3_4 * tReal32x3_4 + v8 * v8);
  }
  else
  {
    return -1.0;
  }
}

// source: j/0/humanai/aisquad.c:1831  [anchor-mhash]
enum bool __cdecl AISquad_SquadActionDefaultDeInitHandler(
        struct QTask_s *ptQTask,
        struct AISquadActionChangeContext_s *ptActionChangeContext)
{
  int v2; // eax
  struct QTaskNodeList_s *p_tQTaskChildren; // esi
  struct QTask_s *ptParent; // eax
  struct QTask_s *ptHead; // eax
  int v6; // eax
  struct QTask_s **v7; // eax
  struct QTask_s *v8; // eax
  int v9; // eax
  struct real32x3_t *v10; // eax
  struct real32x3_t *p_tToSearchContext; // edi
  int v12; // eax
  char *v13; // eax
  int v14; // eax
  int v15; // eax
  int v16; // eax
  char *v17; // eax
  int v18; // eax
  struct QTask_s *ptTail; // eax

  v2 = 7 * (int)ptQTask[215].tQTaskChildren.ptHead;
  p_tQTaskChildren = &ptQTask[v2 + 180].tQTaskChildren;
  ptActionChangeContext->ePrevAction = (enum AISquadActions_e)ptQTask[v2 + 187].ptNext;
  switch ( (unsigned int)ptQTask[v2 + 187].ptNext )
  {
    case 1u:
    case 3u:
    case 7u:
    case 8u:
      if ( ptActionChangeContext->isDeserializing == false )
      {
        if ( ptQTask[1].ptParent )
          ptHead = ptQTask[1].ptNext->tQTaskChildren.ptHead;
        else
          ptHead = nullptr;
        AISquad_SelectAndPlaySoundAtMembersPos((struct AISquad_s *)ptQTask, 13, ptHead);
      }
      break;
    case 5u:
      ptParent = ptQTask[v2 + 180].ptParent;
      if ( ptParent )
      {
        QReference_Delete((struct QReference_s *)ptParent, &QTask_tQTaskRefPool);
        p_tQTaskChildren[2].ptHead = nullptr;
      }
      break;
    default:
      break;
  }
  switch ( ptActionChangeContext->eNextAction )
  {
    case AISQUAD_ACTION_INQUIRE:
      v6 = *(_DWORD *)&ptQTask[215].eQTaskType;
      if ( v6 <= 0 )
        v7 = nullptr;
      else
        v7 = &ptQTask->tQTaskChildren.ptHead + 28 * v6;
      qmemcpy(&ptActionChangeContext->tToInquireContext, v7 + 12, 0x18u);
      ptActionChangeContext->tToInquireContext.ptReceiverRef = nullptr;
      if ( v7[2] )
      {
        v8 = v7[3]->tQTaskChildren.ptHead;
        if ( v8 )
          ptActionChangeContext->tToInquireContext.ptReceiverRef = QTask_NewQTaskRef(v8);
      }
      break;
    case AISQUAD_ACTION_SEARCH_AREA:
      v15 = *(_DWORD *)&ptQTask[215].eQTaskType;
      if ( v15 <= 0 )
        v10 = nullptr;
      else
        v10 = (struct real32x3_t *)((char *)&ptQTask->tQTaskChildren + 112 * v15);
      p_tToSearchContext = (struct real32x3_t *)&ptActionChangeContext->tToSearchContext;
      goto LABEL_38;
    case AISQUAD_ACTION_MOVE:
      v9 = *(_DWORD *)&ptQTask[215].eQTaskType;
      if ( v9 <= 0 )
        v10 = nullptr;
      else
        v10 = (struct real32x3_t *)((char *)&ptQTask->tQTaskChildren + 112 * v9);
      p_tToSearchContext = (struct real32x3_t *)&ptActionChangeContext->tToMoveContext;
      goto LABEL_38;
    case AISQUAD_ACTION_LEAPFROG:
      v12 = *(_DWORD *)&ptQTask[215].eQTaskType;
      if ( v12 <= 0 )
        v13 = nullptr;
      else
        v13 = (char *)&ptQTask->tQTaskChildren + 112 * v12;
      qmemcpy(&ptActionChangeContext->tToLeapFrogContext, v13 + 48, 0x18u);
      v14 = *((_DWORD *)v13 + 11);
      if ( v14 )
        ptActionChangeContext->tToLeapFrogContext.ptTargetQTask = *(struct QTask_s **)(v14 + 8);
      else
        ptActionChangeContext->tToLeapFrogContext.ptTargetQTask = nullptr;
      break;
    case AISQUAD_ACTION_MOVE_SEARCH_IN_DIRECTION:
    case AISQUAD_ACTION_LOOK_SEARCH_IN_DIRECTION:
      v16 = *(_DWORD *)&ptQTask[215].eQTaskType;
      if ( v16 <= 0 )
        v17 = nullptr;
      else
        v17 = (char *)&ptQTask->tQTaskChildren + 112 * v16;
      qmemcpy(&ptActionChangeContext->tToSearchInDirectionContext, v17 + 48, 0x24u);
      break;
    case AISQUAD_ACTION_DANGER:
      v18 = *(_DWORD *)&ptQTask[215].eQTaskType;
      if ( v18 <= 0 )
        v10 = nullptr;
      else
        v10 = (struct real32x3_t *)((char *)&ptQTask->tQTaskChildren + 112 * v18);
      ptActionChangeContext->tToDangerContext.tDirection = v10[6];
      p_tToSearchContext = (struct real32x3_t *)&ptActionChangeContext->tToDangerContext;
LABEL_38:
      qmemcpy(p_tToSearchContext, &v10[4], 0x18u);
      break;
    default:
      break;
  }
  ptTail = p_tQTaskChildren[22].ptTail;
  if ( ptTail != (struct QTask_s *)6 && ptTail && ptActionChangeContext->isPopMembersStacks )
    AISquad_PopMembersActionStacks(ptQTask);
  if ( ptActionChangeContext->eNextAction == AISQUAD_ACTION_IDLE )
  {
    if ( ptActionChangeContext->isPopMembersStacks )
      AISquad_ClearMembersActionStacks(ptQTask);
    AISquad_RemoveEventFromMembersLists(ptQTask, 30);
  }
  return true;
}

// source: j/0/humanai/aisquad.c:1976  [anchor-mhash]
enum bool __cdecl AISquad_SquadActionDefaultEventHandler(struct QTask_s *ptQTask)
{
  int v1; // eax
  struct QTask_s *ptParent; // eax
  int v3; // edx
  struct QTask_s *v4; // eax

  v1 = *(_DWORD *)&ptQTask[215].eQTaskType;
  AISquad_ptCurrentAISquad = (struct AISquad_s *)ptQTask;
  if ( v1 )
  {
    while ( 1 )
    {
      Script_Execute((struct Script_s *)ptQTask[225].tQTaskChildren.ptTail);
      AISquad_RemoveLastEvent(ptQTask);
      if ( ((int)ptQTask[215].tQTaskChildren.ptTail & 1) != 0 )
      {
        if ( *(_DWORD *)&ptQTask[215].eQTaskType )
          break;
      }
      if ( !*(_DWORD *)&ptQTask[215].eQTaskType )
        goto LABEL_7;
    }
    do
    {
      AISquad_RemoveLastEvent(ptQTask);
      ptQTask[215].tQTaskChildren.ptTail = (struct QTask_s *)((int)ptQTask[215].tQTaskChildren.ptTail & ~1u);
    }
    while ( *(_DWORD *)&ptQTask[215].eQTaskType );
  }
LABEL_7:
  ptParent = ptQTask[215].ptParent;
  v3 = 0;
  AISquad_ptCurrentAISquad = nullptr;
  if ( (int)ptParent > 0 )
  {
    v4 = ptQTask + 3;
    do
    {
      qmemcpy(v4, &v4[89].tQTaskRefList.ptMiddle, 0x70u);
      ++v3;
      v4 = (struct QTask_s *)((char *)v4 + 112);
    }
    while ( v3 < (int)ptQTask[215].ptParent );
  }
  *(_DWORD *)&ptQTask[215].eQTaskType = ptQTask[215].ptParent;
  ptQTask[215].ptParent = nullptr;
  return true;
}

// source: j/0/humanai/aisquad.c:2027  [anchor-caller]
enum bool __cdecl AISquad_SquadActionIdleInitHandler(
        struct QTask_s *ptQTask,
        struct AISquadActionChangeContext_s *ptActionChangeContext)
{
  struct QTask_s *v2; // edx

  AISquad_MakeOneTeam(ptQTask);
  AISquad_ClearTargetLists(ptQTask);
  v2 = (struct QTask_s *)((int)ptQTask[215].tQTaskChildren.ptTail & 0xFFFFFFF9);
  *(_DWORD *)&ptQTask[1].eQTaskType = 1;
  ptQTask[215].tQTaskChildren.ptTail = v2;
  AISquad_ClearMembersActionStacks(ptQTask);
  return true;
}

// source: j/0/humanai/aisquad.c:2051  [size]
enum bool __cdecl AISquad_SquadActionIdleRunHandler(struct QTask_s *ptQTask)
{
  return true;
}

// source: j/0/humanai/aisquad.c:2070  [anchor-mhash]
enum bool __cdecl AISquad_SquadActionHoldAreaInitHandler(
        struct QTask_s *ptQTask,
        struct AISquadActionChangeContext_s *ptACtionChangeContext)
{
  struct QTaskNodeList_s *p_tQTaskChildren; // esi

  p_tQTaskChildren = &ptQTask[7 * (int)ptQTask[215].tQTaskChildren.ptHead + 180].tQTaskChildren;
  *(_DWORD *)&ptQTask[1].eQTaskType = 1;
  AISquad_MakeOneTeam(ptQTask);
  p_tQTaskChildren->ptHead = nullptr;
  return true;
}

// source: j/0/humanai/aisquad.c:2109  [anchor-mhash]
enum bool __cdecl AISquad_SquadActionHoldAreaRunHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct QTask_s *v20; };
    struct { char igi2_o1[4]; float v21; };
    struct { char igi2_o2[8]; int v22; };
    struct { char igi2_o3[12]; float v23; };
    struct { char igi2_o4[16]; float v24; };
    struct { char igi2_o5[20]; float v25; };
    struct { char igi2_o6[28]; float v26; };
    struct { char igi2_o7[32]; float v27; };
    struct { char igi2_o8[40]; struct AISquadOrderContext_s ptSquadOrder; };
    struct { char igi2_o9[96]; struct AISquadActionChangeContext_s v29; };
    char igi2_extent[312];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *v1; // edi
  struct QTaskNodeList_s *p_tQTaskChildren; // eax
  struct HumanAI_s *ptHead; // ebx
  void (__cdecl *pfRunCallback)(struct HumanAI_s *, struct HumanAIActionStackItem_s *); // eax
  double *ptParent; // esi
  int v6; // edi
  _DWORD *i; // edx
  int v8; // ecx
  double v9; // st3
  long double v10; // st4
  double *v11; // edx
  double *p_ptMiddle; // ecx
  struct QReference_s *ptMiddle; // edi
  double v14; // st3
  long double v15; // st4
  bool v16; // cc
  int v18; // ecx
  bool v19; // sf

  v1 = ptQTask;
  p_tQTaskChildren = &ptQTask[7 * (int)ptQTask[215].tQTaskChildren.ptHead + 180].tQTaskChildren;
  if ( (int)ptQTask[215].tQTaskRefList.ptMiddle <= 0 )
  {
    v18 = (int)&p_tQTaskChildren->ptHead->ptNext + 1;
    v19 = (int)&p_tQTaskChildren->ptHead[-4].tQTaskChildren.ptHead + 3 < 0;
    p_tQTaskChildren->ptHead = (struct QTask_s *)v18;
    if ( !(v19 ^ __OFSUB__(v18, 150) | (v18 == 150)) )
    {
      igi2_frame.v29.eNextAction = AISQUAD_ACTION_IDLE;
      igi2_frame.v29.isPopMembersStacks = true;
      igi2_frame.v29.isDeserializing = false;
      AISquad_PopActionStack(ptQTask, &igi2_frame.v29);
    }
    return true;
  }
  igi2_frame.v22 = 0;
  if ( (int)ptQTask[1].ptParent <= 0 )
    return true;
  igi2_frame.v20 = ptQTask + 1;
  do
  {
    if ( igi2_frame.v20->ptNext )
    {
      ptHead = (struct HumanAI_s *)igi2_frame.v20->ptNext->tQTaskChildren.ptHead;
      if ( ptHead )
      {
        pfRunCallback = ptHead->atActionStackItemList[0].pfRunCallback;
        if ( *(_DWORD *)pfRunCallback )
        {
          if ( pfRunCallback
            && *((void (__cdecl **)(struct HumanAI_s *, struct HumanAIActionStackItem_s *))pfRunCallback + 6) == HumanAIContent_CombatIdleInitCB )
          {
            ptParent = (double *)ptHead->tQTask.ptParent;
            v6 = 0;
            if ( !HumanAI_GetTargetQTask(ptHead, true) )
            {
              for ( i = (_DWORD *)ptHead->tAIDetection.atListItems[0].bQTaskMask; *i && i; i = (_DWORD *)*i )
              {
                v8 = *(_DWORD *)(i[2] + 8);
                if ( v8 )
                {
                  if ( !*(_BYTE *)(v8 + 1180) )
                  {
                    igi2_frame.v26 = ptParent[5] - *(double *)(v8 + 40);
                    igi2_frame.v27 = ptParent[6] - *(double *)(v8 + 48);
                    v9 = ptParent[7] - *(double *)(v8 + 56);
                    v10 = sqrt(igi2_frame.v26 * igi2_frame.v26 + igi2_frame.v27 * igi2_frame.v27 + v9 * v9);
                    if ( !v6 || v10 < igi2_frame.v23 )
                    {
                      igi2_frame.v23 = v10;
                      v6 = *(_DWORD *)(i[2] + 8);
                    }
                  }
                }
              }
              if ( !v6 )
              {
                v11 = nullptr;
                igi2_frame.v21 = 0.0;
                if ( (int)ptQTask[215].tQTaskRefList.ptMiddle > 0 )
                {
                  p_ptMiddle = (double *)&ptQTask[182].tQTaskRefList.ptMiddle;
                  ptMiddle = ptQTask[215].tQTaskRefList.ptMiddle;
                  do
                  {
                    igi2_frame.v24 = ptParent[5] - *(p_ptMiddle - 1);
                    igi2_frame.v25 = ptParent[6] - *p_ptMiddle;
                    v14 = ptParent[7] - p_ptMiddle[1];
                    v15 = sqrt(igi2_frame.v24 * igi2_frame.v24 + igi2_frame.v25 * igi2_frame.v25 + v14 * v14);
                    if ( !v11 || v15 < igi2_frame.v21 )
                    {
                      igi2_frame.v21 = v15;
                      v11 = p_ptMiddle - 2;
                    }
                    p_ptMiddle += 5;
                    ptMiddle = (struct QReference_s *)((char *)ptMiddle - 1);
                  }
                  while ( ptMiddle );
                  if ( v11 )
                  {
                    igi2_frame.ptSquadOrder.eOrder = AISQUAD_ORDER_LOOK_AT_POSITION;
                    igi2_frame.ptSquadOrder.iDelay = 0;
                    qmemcpy(&igi2_frame.ptSquadOrder.uContext, v11 + 1, 0x18u);
                    HumanAIContent_ReceiveSquadOrder(ptHead, &igi2_frame.ptSquadOrder);
                  }
                }
              }
            }
            v1 = ptQTask;
          }
        }
      }
    }
    v16 = ++igi2_frame.v22 < (int)v1[1].ptParent;
    igi2_frame.v20 = (struct QTask_s *)((char *)igi2_frame.v20 + 4);
  }
  while ( v16 );
  return true;
}

// source: j/0/humanai/aisquad.c:2192  [anchor-mhash]
enum bool __cdecl AISquad_SquadActionInquireInitHandler(
        struct QTask_s *ptQTask,
        struct AISquadActionChangeContext_s *ptActionChangeContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct QTask_s **p_ptTail; };
    struct { char igi2_o1[4]; struct AISquadOrderContext_s tOrderContext; };
    struct { char igi2_o2[60]; struct AISquadActionChangeContext_s tChangeContext; };
    char igi2_extent[280];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTaskNodeList_s *p_tQTaskChildren; // eax
  struct QReference_s *ptReceiverRef; // ebp
  int v4; // esi
  struct QTask_s *v5; // ecx
  struct QTask_s *ptNext; // eax
  struct QTask_s *ptParent; // eax
  struct HumanAI_s *ptHead; // eax

  p_tQTaskChildren = &ptQTask[7 * (int)ptQTask[215].tQTaskChildren.ptHead + 180].tQTaskChildren;
  p_tQTaskChildren->ptHead = nullptr;
  igi2_frame.p_ptTail = &p_tQTaskChildren->ptTail;
  qmemcpy(&p_tQTaskChildren->ptTail, &ptActionChangeContext->tToInquireContext, 0x18u);
  AISquad_MakeOneTeam(ptQTask);
  *(_DWORD *)&ptQTask[1].eQTaskType = 0;
  ptReceiverRef = ptActionChangeContext->tToInquireContext.ptReceiverRef;
  if ( !ptReceiverRef )
    goto LABEL_8;
  v4 = 0;
  if ( (int)ptQTask[1].ptParent <= 0 )
  {
LABEL_6:
    v4 = -1;
  }
  else
  {
    v5 = ptQTask + 1;
    while ( v5->ptNext->tQTaskChildren.ptHead != ptReceiverRef->pxObject )
    {
      ++v4;
      v5 = (struct QTask_s *)((char *)v5 + 4);
      if ( v4 >= (int)ptQTask[1].ptParent )
        goto LABEL_6;
    }
  }
  QReference_Delete(ptReceiverRef, &QTask_tQTaskRefPool);
  if ( v4 >= 0 )
  {
    ptNext = ptQTask[1].ptNext;
    ptQTask[1].ptNext = *(&ptQTask[1].ptNext + v4);
    *((_DWORD *)&ptQTask[1].ptNext + v4) = ptNext;
    igi2_frame.tOrderContext.eOrder = AISQUAD_ORDER_LOOK_AT_POSITION;
    igi2_frame.tOrderContext.iDelay = AISquad_GetOrderDelay((struct AISquad_s *)ptQTask);
    qmemcpy(&igi2_frame.tOrderContext.uContext, igi2_frame.p_ptTail, 0x18u);
    AISquad_SendOrderToSquad(ptQTask, &igi2_frame.tOrderContext);
    igi2_frame.tOrderContext.eOrder = AISQUAD_ORDER_INQUIRE;
    igi2_frame.tOrderContext.iDelay = AISquad_GetOrderDelay((struct AISquad_s *)ptQTask);
    ptParent = ptQTask[1].ptParent;
    qmemcpy(&igi2_frame.tOrderContext.uContext, &ptActionChangeContext->tToInquireContext, 0x18u);
    if ( ptParent )
      ptHead = (struct HumanAI_s *)ptQTask[1].ptNext->tQTaskChildren.ptHead;
    else
      ptHead = nullptr;
    HumanAIContent_ReceiveSquadOrder(ptHead, &igi2_frame.tOrderContext);
    return true;
  }
  else
  {
LABEL_8:
    igi2_frame.tChangeContext.eNextAction = AISQUAD_ACTION_IDLE;
    igi2_frame.tChangeContext.isDeserializing = false;
    igi2_frame.tChangeContext.isPopMembersStacks = true;
    AISquad_PopActionStack(ptQTask, &igi2_frame.tChangeContext);
    return false;
  }
}

// source: j/0/humanai/aisquad.c:2273  [anchor-mhash]
enum bool __cdecl AISquad_SquadActionInquireRunHandler(struct QTask_s *ptQTask)
{
  int v1; // ecx
  struct QTask_s *ptHead; // edx
  struct QTaskNodeList_s *p_tQTaskChildren; // ecx
  struct QReference_s *ptMiddle; // edx
  struct QTask_s *v6; // ecx
  struct QTask_s *v7; // esi
  struct AISquadEventContext_s tEventContext; // [esp+8h] [ebp-70h] BYREF

  v1 = 7 * (int)ptQTask[215].tQTaskChildren.ptHead;
  ptHead = ptQTask[v1 + 180].tQTaskChildren.ptHead;
  p_tQTaskChildren = &ptQTask[v1 + 180].tQTaskChildren;
  if ( (int)ptHead >= (int)(__int64)(*(float *)&ptQTask[217].ptParent * 30.0) )
  {
    ptMiddle = ptQTask[215].tQTaskRefList.ptMiddle;
    v6 = nullptr;
    tEventContext.eEvent = 29;
    memset(&tEventContext.nPriority, 0, 12);
    tEventContext.ptReferenceQTaskRef = nullptr;
    if ( ptMiddle )
    {
      v7 = (struct QTask_s *)((char *)ptQTask + 7296);
    }
    else
    {
      if ( ptQTask[1].ptParent )
        v6 = ptQTask[1].ptNext->tQTaskChildren.ptHead;
      v7 = v6->ptParent + 1;
    }
    qmemcpy(&tEventContext.tPosition, v7, sizeof(tEventContext.tPosition));
    AISquad_ReceiveEvent(ptQTask, &tEventContext);
    return true;
  }
  else
  {
    p_tQTaskChildren->ptHead = (struct QTask_s *)((char *)&ptHead->ptNext + 1);
    return true;
  }
}

// source: j/0/humanai/aisquad.c:2334  [anchor-caller]
enum bool __cdecl AISquad_SquadActionSearchAreaInitHandler(
        struct QTask_s *ptQTask,
        struct AISquadActionChangeContext_s *ptActionChangeContext)
{
  struct QTaskNodeList_s *p_tQTaskChildren; // ebp
  struct QTask_s *ptHead; // edi
  struct AISquadToSearchStateChangeContext_s *p_tToSearchContext; // esi
  enum GameDifficulty_e eDifficultyLevel; // eax
  __int32 v6; // eax
  struct QTask_s *aptLeaderQTask; // [esp+14h] [ebp-8h]
  struct QTask_s *aptLeaderQTask_4; // [esp+18h] [ebp-4h]

  p_tQTaskChildren = &ptQTask[7 * (int)ptQTask[215].tQTaskChildren.ptHead + 180].tQTaskChildren;
  AISquad_MakeTwoTeams(ptQTask);
  AISquad_ClearTargetLists(ptQTask);
  AISquad_ClearMembersPaths(ptQTask);
  AISquad_ClearMembersActionStacks(ptQTask);
  if ( ptQTask[1].ptParent )
  {
    ptHead = ptQTask[1].ptNext->tQTaskChildren.ptHead;
    aptLeaderQTask = ptHead;
  }
  else
  {
    aptLeaderQTask = nullptr;
    ptHead = nullptr;
  }
  if ( ptQTask[2].ptParent )
    aptLeaderQTask_4 = ptQTask[2].ptNext->tQTaskChildren.ptHead;
  else
    aptLeaderQTask_4 = nullptr;
  p_tToSearchContext = &ptActionChangeContext->tToSearchContext;
  AIGraph_GetClosestNode(
    (struct AIGraphNode_s **)&ptActionChangeContext,
    (struct AIGraph_t *)ptHead[728].tQTaskChildren.ptHead,
    &ptActionChangeContext->tToSearchContext.tPosition,
    false);
  if ( ptActionChangeContext )
    p_tQTaskChildren[2].ptMiddle = (struct QTask_s *)ptActionChangeContext->eNextAction;
  else
    p_tQTaskChildren[2].ptMiddle = (struct QTask_s *)ptHead[748].tQTaskRefList.ptTail;
  qmemcpy(&p_tQTaskChildren[2].ptTail, p_tToSearchContext, 0x18u);
  p_tQTaskChildren->ptHead = (struct QTask_s *)aptLeaderQTask[748].tQTaskRefList.ptTail;
  if ( aptLeaderQTask_4 )
    p_tQTaskChildren->ptMiddle = (struct QTask_s *)aptLeaderQTask_4[748].tQTaskRefList.ptTail;
  else
    p_tQTaskChildren->ptMiddle = (struct QTask_s *)-1;
  eDifficultyLevel = Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eDifficultyLevel;
  if ( eDifficultyLevel == GAMEDIFFICULTY_1 )
    goto LABEL_18;
  v6 = eDifficultyLevel - 1;
  if ( !v6 )
  {
    p_tQTaskChildren[1].ptTail = (struct QTask_s *)2;
    goto LABEL_19;
  }
  if ( v6 != 1 )
  {
LABEL_18:
    p_tQTaskChildren[1].ptTail = (struct QTask_s *)1;
    goto LABEL_19;
  }
  p_tQTaskChildren[1].ptTail = (struct QTask_s *)3;
LABEL_19:
  p_tQTaskChildren[1].ptMiddle = nullptr;
  p_tQTaskChildren[2].ptHead = nullptr;
  p_tQTaskChildren->ptTail = nullptr;
  p_tQTaskChildren[1].ptHead = (struct QTask_s *)4;
  *(_DWORD *)&ptQTask[1].eQTaskType = 0;
  *(_DWORD *)&ptQTask[2].eQTaskType = 0;
  AISquad_SetFormation(ptQTask, 0, AISQUAD_FORMATION_STAGGEREDCOLUMN);
  AISquad_SetFormation(ptQTask, 1, AISQUAD_FORMATION_STAGGEREDCOLUMN);
  return true;
}

// source: j/0/humanai/aisquad.c:2431  [anchor-mhash]
enum bool __cdecl AISquad_SquadActionSearchAreaRunHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct AIGraphNode_s *pptAIGraphNode; };
    struct { char igi2_o1[4]; struct HumanAI_s *ptHumanAI[3]; };
    struct { char igi2_o2[16]; float vY; };
    struct { char igi2_o3[20]; float v27; };
    struct { char igi2_o4[24]; _DWORD v28[3]; };
    struct { char igi2_o5[36]; struct AISquadOrderContext_s ptSquadOrder; };
    struct { char igi2_o6[92]; struct AIGraph_t ptAIGraph; };
    struct { char igi2_o7[324]; int v31; };
    struct { char igi2_o8[328]; int v32; };
    char igi2_extent[332];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTaskNodeList_s *p_tQTaskChildren; // esi
  struct QTask_s *ptParent; // eax
  struct HumanAI_s *ptHead; // ebx
  struct QTask_s *ptMiddle; // eax
  int v5; // eax
  int v6; // ebp
  struct HumanAI_s *v7; // ecx
  int v8; // eax
  int i; // edi
  struct HumanAI_s *v10; // ebp
  float vX; // edx
  float vZ; // ecx
  float *v13; // eax
  double v14; // st7
  struct AIGraph_t *v15; // ebx
  double v16; // st6
  double v17; // rax
  int j; // esi
  struct HumanAI_s *v19; // eax
  enum GameDifficulty_e eDifficultyLevel; // edi
  int v22; // eax
  int v23; // ecx

  p_tQTaskChildren = &ptQTask[7 * (int)ptQTask[215].tQTaskChildren.ptHead + 180].tQTaskChildren;
  ptParent = ptQTask[1].ptParent;
  igi2_frame.v28[0] = 1065353216;
  igi2_frame.v28[1] = 0x40000000;
  igi2_frame.v28[2] = 1077936128;
  if ( ptParent )
    igi2_frame.pptAIGraphNode = (struct AIGraphNode_s *)ptQTask[1].ptNext->tQTaskChildren.ptHead;
  else
    igi2_frame.pptAIGraphNode = nullptr;
  igi2_frame.ptHumanAI[0] = (struct HumanAI_s *)igi2_frame.pptAIGraphNode;
  if ( ptQTask[2].ptParent )
    ptHead = (struct HumanAI_s *)ptQTask[2].ptNext->tQTaskChildren.ptHead;
  else
    ptHead = nullptr;
  ptMiddle = ptQTask[216].tQTaskChildren.ptMiddle;
  igi2_frame.ptHumanAI[1] = ptHead;
  if ( !ptMiddle )
  {
    AISquad_SetFormation(ptQTask, 0, AISQUAD_FORMATION_STAGGEREDCOLUMN);
    AISquad_SetFormation(ptQTask, 1, AISQUAD_FORMATION_STAGGEREDCOLUMN);
  }
  v5 = 0;
  v6 = (char *)p_tQTaskChildren - (char *)igi2_frame.ptHumanAI;
  while ( 1 )
  {
    v7 = igi2_frame.ptHumanAI[v5];
    if ( v7 )
    {
      if ( *(struct HumanAI_s **)((char *)&igi2_frame.ptHumanAI[v5] + v6) != (struct HumanAI_s *)LODWORD(v7->tCommon.tAimPosition.vZ) )
        break;
    }
    if ( ++v5 >= 2 )
    {
      v8 = igi2_frame.pptAIGraphNode[50].tGraphNode.aptLinks[6] == (struct GraphLink_s *)p_tQTaskChildren->ptHead;
      if ( ptHead )
        v8 = ((struct QTask_s *)HIDWORD(ptHead->tCommon.tAimPosition.vY) == p_tQTaskChildren->ptMiddle)
           & (unsigned __int8)v8;
      if ( v8 )
      {
        if ( (int)p_tQTaskChildren[1].ptMiddle < 5 )
        {
          for ( i = 0; i < 2; ++i )
          {
            v10 = igi2_frame.ptHumanAI[i];
            if ( v10 )
            {
              vX = AISquad_atSearchPatternPos[*((_DWORD *)&p_tQTaskChildren->ptTail + i)].vX;
              vZ = AISquad_atSearchPatternPos[*((_DWORD *)&p_tQTaskChildren->ptTail + i)].vZ;
              igi2_frame.vY = AISquad_atSearchPatternPos[*((_DWORD *)&p_tQTaskChildren->ptTail + i)].vY;
              v13 = (float *)&igi2_frame.v28[(int)p_tQTaskChildren[2].ptHead];
              igi2_frame.ptHumanAI[2] = (struct HumanAI_s *)LODWORD(vX);
              v14 = vX * *v13;
              v15 = *(struct AIGraph_t **)&v10->zScriptFile[36];
              igi2_frame.v27 = vZ;
              v16 = igi2_frame.vY * *v13;
              igi2_frame.v27 = vZ * *v13;
              *(double *)&igi2_frame.ptAIGraph.tGraph.tQTask.ptNext = v14 + *(double *)&p_tQTaskChildren[2].ptTail;
              *(double *)&igi2_frame.ptAIGraph.tGraph.tQTask.tQTaskChildren.ptHead = v16 + *(double *)&p_tQTaskChildren[3].ptMiddle;
              *(double *)&igi2_frame.ptAIGraph.tGraph.tQTask.tQTaskChildren.ptTail = igi2_frame.v27 + *(double *)&p_tQTaskChildren[4].ptHead;
              AIGraph_GetClosestNode(&igi2_frame.pptAIGraphNode, v15, (struct real64x3_t *)&igi2_frame.ptAIGraph, false);
              if ( igi2_frame.pptAIGraphNode )
              {
                LODWORD(v17) = igi2_frame.pptAIGraphNode->tGraphNode.nID;
                *((_DWORD *)&p_tQTaskChildren->ptHead + i) = igi2_frame.pptAIGraphNode->tGraphNode.nID;
                HIDWORD(v17) = Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eDifficultyLevel != GAMEDIFFICULTY_1;
                igi2_frame.ptSquadOrder.eOrder = AISQUAD_ORDER_MOVE_TO_NODE;
                igi2_frame.ptSquadOrder.iDelay = 0;
                igi2_frame.ptSquadOrder.uContext.tWaitForLeapFrogContext.tTargetPosition.vX = v17;
                HumanAIContent_ReceiveSquadOrder(v10, &igi2_frame.ptSquadOrder);
              }
              if ( i )
              {
                v22 = (int)(&p_tQTaskChildren[1].ptHead[-1].isInMemPool + 1);
                p_tQTaskChildren[1].ptHead = (struct QTask_s *)v22;
                if ( v22 < 0 )
                  p_tQTaskChildren[1].ptHead = (struct QTask_s *)(v22 + 5);
              }
              else
              {
                ++p_tQTaskChildren->ptTail;
              }
            }
          }
          ++p_tQTaskChildren[1].ptMiddle;
          return true;
        }
        if ( (int)p_tQTaskChildren[1].ptTail > 1 )
        {
          if ( ptQTask[1].ptParent && ptQTask[1].ptNext->tQTaskChildren.ptHead )
            AISquad_SelectAndPlaySoundAtMembersPos(
              (struct AISquad_s *)ptQTask,
              3,
              ptQTask[1].ptNext->tQTaskChildren.ptHead);
          v23 = (int)&p_tQTaskChildren[2].ptHead->ptNext + 1;
          --p_tQTaskChildren[1].ptTail;
          p_tQTaskChildren[1].ptMiddle = nullptr;
          p_tQTaskChildren->ptTail = nullptr;
          p_tQTaskChildren[2].ptHead = (struct QTask_s *)v23;
          p_tQTaskChildren[1].ptHead = (struct QTask_s *)4;
          return true;
        }
        igi2_frame.v32 = 0;
        igi2_frame.ptAIGraph.tGraph.tQTask.tQTaskRefList.ptMiddle = nullptr;
        igi2_frame.v31 = 1;
        AISquad_PopActionStack(
          ptQTask,
          (struct AISquadActionChangeContext_s *)&igi2_frame.ptAIGraph.tGraph.tQTask.tQTaskRefList.ptMiddle);
      }
      return true;
    }
  }
  for ( j = 0; j < 2; ++j )
  {
    v19 = igi2_frame.ptHumanAI[j];
    if ( v19 )
    {
      eDifficultyLevel = Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eDifficultyLevel;
      igi2_frame.ptSquadOrder.uContext.tMoveToNodeContext.nNodeId = *(int *)((char *)&igi2_frame.ptHumanAI[j] + v6);
      igi2_frame.ptSquadOrder.eOrder = AISQUAD_ORDER_MOVE_TO_NODE;
      igi2_frame.ptSquadOrder.iDelay = 0;
      igi2_frame.ptSquadOrder.uContext.tMoveToNodeContext.isRun = eDifficultyLevel != GAMEDIFFICULTY_1;
      HumanAIContent_ReceiveSquadOrder(v19, &igi2_frame.ptSquadOrder);
    }
  }
  return true;
}

// source: j/0/humanai/aisquad.c:2605  [anchor-mhash]
enum bool __cdecl AISquad_SquadActionMoveInitHandler(
        struct QTask_s *ptQTask,
        struct AISquadActionChangeContext_s *ptActionChangeContext)
{
  struct AISquad_s *v2; // ebp
  struct QTaskNodeList_s *p_tQTaskChildren; // edi
  void *pxObject; // esi
  int OrderDelay; // eax
  struct QTask_s *ptHead; // ecx
  struct AISquadOrderContext_s tOrderContext; // [esp+10h] [ebp-3Ch] BYREF

  v2 = (struct AISquad_s *)ptQTask;
  p_tQTaskChildren = &ptQTask[7 * (int)ptQTask[215].tQTaskChildren.ptHead + 180].tQTaskChildren;
  AISquad_MakeOneTeam(ptQTask);
  if ( v2->atTeam[0].nMembers )
    pxObject = v2->atTeam[0].aptMemberRef[0]->pxObject;
  else
    pxObject = nullptr;
  AIGraph_GetClosestNode(
    (struct AIGraphNode_s **)&ptQTask,
    *((struct AIGraph_t **)pxObject + 7282),
    &ptActionChangeContext->tToMoveContext.tPosition,
    false);
  if ( ptQTask )
    p_tQTaskChildren->ptHead = ptQTask->ptNext;
  else
    p_tQTaskChildren->ptHead = *((struct QTask_s **)pxObject + 7487);
  if ( *((struct QTask_s **)pxObject + 7487) != p_tQTaskChildren->ptHead )
  {
    p_tQTaskChildren->ptTail = (struct QTask_s *)pxObject;
    p_tQTaskChildren->ptMiddle = (struct QTask_s *)-1;
    tOrderContext.eOrder = AISQUAD_ORDER_MOVE_TO_NODE;
    OrderDelay = AISquad_GetOrderDelay(v2);
    ptHead = p_tQTaskChildren->ptHead;
    tOrderContext.iDelay = OrderDelay;
    *(_QWORD *)&tOrderContext.uContext.tWaitForLeapFrogContext.tTargetPosition.vX = (unsigned int)ptHead | 0x100000000LL;
    HumanAIContent_ReceiveSquadOrder((struct HumanAI_s *)pxObject, &tOrderContext);
    AISquad_SetFormation(&v2->tQTask, 0, AISQUAD_FORMATION_STAGGEREDCOLUMN);
  }
  return true;
}

// source: j/0/humanai/aisquad.c:2669  [anchor-mhash]
enum bool __cdecl AISquad_SquadActionMoveRunHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct AISquadOrderContext_s tOrderContext; };
    struct { char igi2_o1[56]; struct AISquadActionChangeContext_s tChangeContext; };
    char igi2_extent[272];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTaskNodeList_s *p_tQTaskChildren; // edi
  struct HumanAI_s *ptHead; // esi
  void (__cdecl *pfRunCallback)(struct HumanAI_s *, struct HumanAIActionStackItem_s *); // eax
  int v5; // ebp
  int OrderDelay; // eax
  struct QTask_s *v7; // ecx

  p_tQTaskChildren = &ptQTask[7 * (int)ptQTask[215].tQTaskChildren.ptHead + 180].tQTaskChildren;
  if ( ptQTask[1].ptParent )
    ptHead = (struct HumanAI_s *)ptQTask[1].ptNext->tQTaskChildren.ptHead;
  else
    ptHead = nullptr;
  if ( (struct QTask_s *)HIDWORD(ptHead->tCommon.tAimPosition.vY) == p_tQTaskChildren->ptHead )
  {
    igi2_frame.tChangeContext.eNextAction = AISQUAD_ACTION_IDLE;
    igi2_frame.tChangeContext.isPopMembersStacks = true;
    igi2_frame.tChangeContext.isDeserializing = false;
    AISquad_PopActionStack(ptQTask, &igi2_frame.tChangeContext);
    return true;
  }
  if ( !ptQTask[216].tQTaskChildren.ptMiddle )
    AISquad_SetFormation(ptQTask, 0, AISQUAD_FORMATION_STAGGEREDCOLUMN);
  if ( ptHead != (struct HumanAI_s *)p_tQTaskChildren->ptTail )
    goto LABEL_17;
  pfRunCallback = ptHead->atActionStackItemList[0].pfRunCallback;
  if ( !*(_DWORD *)pfRunCallback )
    goto LABEL_15;
  if ( pfRunCallback
    && *((void (__cdecl **)(struct HumanAI_s *, struct HumanAIActionStackItem_s *))pfRunCallback + 6) == HumanAIContent_MoveToNodeSquadOrderInitCB )
  {
    return true;
  }
  if ( *(_DWORD *)pfRunCallback && pfRunCallback )
    v5 = *((_DWORD *)pfRunCallback + 3);
  else
LABEL_15:
    v5 = -1;
  if ( v5 != HumanAI_GetEventPriority(ptHead, 26) )
  {
LABEL_17:
    p_tQTaskChildren->ptTail = &ptHead->tQTask;
    igi2_frame.tOrderContext.eOrder = AISQUAD_ORDER_MOVE_TO_NODE;
    OrderDelay = AISquad_GetOrderDelay((struct AISquad_s *)ptQTask);
    v7 = p_tQTaskChildren->ptHead;
    igi2_frame.tOrderContext.iDelay = OrderDelay;
    *(_QWORD *)&igi2_frame.tOrderContext.uContext.tWaitForLeapFrogContext.tTargetPosition.vX = (unsigned int)v7 | 0x100000000LL;
    HumanAIContent_ReceiveSquadOrder(ptHead, &igi2_frame.tOrderContext);
  }
  return true;
}

// source: j/0/humanai/aisquad.c:2742  [anchor-callee]
void __cdecl AISquad_UpdateLeapfrogTeams(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { int v18; };
    struct { char igi2_o1[4]; struct QTask_s *v19; };
    struct { char igi2_o2[8]; float DistanceToTarget; };
    struct { char igi2_o3[12]; struct QTask_s *v21; };
    struct { char igi2_o4[16]; struct QTaskNodeList_s *v22; };
    struct { char igi2_o5[20]; _DWORD v23[8]; };
    char igi2_extent[52];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTaskNodeList_s *p_tQTaskChildren; // ebx
  struct QTask_s *ptMiddle; // edi
  int v3; // ebp
  int v4; // eax
  struct QTask_s *v5; // ecx
  struct QTask_s *ptParent; // ecx
  int v7; // eax
  int v8; // edi
  int v9; // ebx
  int v10; // eax
  int v11; // eax
  int v12; // eax
  int v13; // eax
  int v14; // eax
  struct QTask_s **p_ptParent; // eax
  int v16; // edx
  struct QTask_s *ptHead; // eax

  p_tQTaskChildren = &ptQTask[7 * (int)ptQTask[215].tQTaskChildren.ptHead + 180].tQTaskChildren;
  igi2_frame.v22 = p_tQTaskChildren;
  AISquad_MakeOneTeam(ptQTask);
  ptMiddle = p_tQTaskChildren->ptMiddle;
  v3 = 1 - (_DWORD)ptMiddle;
  igi2_frame.v19 = ptMiddle;
  igi2_frame.DistanceToTarget = AISquad_GetDistanceToTarget(ptQTask, 1 - (_DWORD)ptMiddle);
  v4 = 0;
  if ( (int)ptQTask[1].ptParent > 0 )
  {
    v5 = ptQTask + 1;
    do
    {
      igi2_frame.v23[v4] = v5->ptNext;
      v5->ptNext = nullptr;
      ++v4;
      v5 = (struct QTask_s *)((char *)v5 + 4);
    }
    while ( v4 < (int)ptQTask[1].ptParent );
  }
  ptParent = ptQTask[1].ptParent;
  v7 = 0;
  igi2_frame.v21 = ptParent;
  ptQTask[1].ptParent = nullptr;
  ptQTask[2].ptParent = nullptr;
  igi2_frame.v18 = 0;
  if ( (int)ptParent > 0 )
  {
    do
    {
      v8 = *(_DWORD *)(igi2_frame.v23[v7] + 8);
      if ( v8 )
      {
        v9 = *(_DWORD *)(v8 + 32);
        if ( HumanAI_GetTargetQTask((struct HumanAI_s *)v8, true)
          && (igi2_frame.DistanceToTarget < 122880.0
           || (v10 = *(_DWORD *)(v9 + 1320)) != 0
           && (v11 = *(_DWORD *)(v10 + 44)) != 0
           && (v12 = *(_DWORD *)(v11 + 16)) != 0
           && *(_DWORD *)(v12 + 672) == 3
           && *(_DWORD *)(v12 + 708) == 8
           || *(_DWORD *)(v9 + 1316) == 2
           || *(int *)(v8 + 4444) < 150)
          && ((v13 = *(_DWORD *)(*(_DWORD *)(v9 + 1320) + 44)) == 0
           || (v14 = *(_DWORD *)(v13 + 16)) == 0
           || *(_DWORD *)(v14 + 668) != 2)
          || *(_DWORD *)(v8 + 344) == 2 && *(_DWORD *)(v8 + 480) == *(_DWORD *)(v8 + 29948) )
        {
          p_ptParent = &ptQTask[v3 + 1].ptParent;
          v16 = (int)&(*p_ptParent)->tQTaskChildren.ptHead + 10 * v3 + 2;
        }
        else
        {
          p_ptParent = &ptQTask[(int)igi2_frame.v19 + 1].ptParent;
          v16 = (int)&(*p_ptParent)->tQTaskChildren.ptHead + 10 * (_DWORD)igi2_frame.v19 + 2;
        }
        *((_DWORD *)&ptQTask->ptNext + v16) = igi2_frame.v23[igi2_frame.v18];
        *p_ptParent = (struct QTask_s *)((char *)*p_ptParent + 1);
      }
      v7 = ++igi2_frame.v18;
    }
    while ( igi2_frame.v18 < (int)igi2_frame.v21 );
    p_tQTaskChildren = igi2_frame.v22;
    ptMiddle = igi2_frame.v19;
  }
  if ( ptQTask[(int)ptMiddle + 1].ptParent )
  {
    ptHead = ptQTask[(int)ptMiddle + 1].ptNext->tQTaskChildren.ptHead;
    if ( ptHead )
      p_tQTaskChildren->ptHead = (struct QTask_s *)ptHead[748].tQTaskRefList.ptTail;
  }
  ptQTask[215].tQTaskRefList.ptTail = (struct QReference_s *)2;
}

// source: j/0/humanai/aisquad.c:2849  [anchor-callee]
void __cdecl AISquad_FindSpreadOutCenter(struct AISquad_s *ptAISquad, struct real64x3_t *ptCenter)
{
  #pragma pack(push, 1)
  union
  {
    struct { int nCount; };
    struct { char igi2_o1[4]; float vLen; };
    struct { char igi2_o2[8]; struct QTask_s **ptQTask; };
    struct { char igi2_o3[12]; float vReal32; };
    struct { char igi2_o4[16]; float vSquadRadius; };
    struct { char igi2_o5[20]; struct real32x3_t tDelta; };
    struct { char igi2_o6[32]; struct real32x3_t tReal32x3; };
    struct { char igi2_o7[44]; struct real64x3_t tSquadCenter; };
    struct { char igi2_o8[68]; struct real64x3_t tReal64x3; };
    char igi2_extent[96];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct AISquad_s *v2; // esi
  int nMembers; // eax
  _DWORD *pxObject; // eax
  struct QTaskList_s *v5; // edi
  int v6; // ebp
  bool v7; // cc
  struct QTask_s *v8; // eax
  struct QTask_s *ptParent; // ecx
  struct QTask_s *ptHead; // ecx
  long double v11; // st7
  double v12; // st7
  double v13; // st7
  double v14; // st7

  v2 = ptAISquad;
  nMembers = ptAISquad->atTeam[0].nMembers;
  memset(&igi2_frame.tSquadCenter, 0, sizeof(igi2_frame.tSquadCenter));
  if ( nMembers )
  {
    pxObject = ptAISquad->atTeam[0].aptMemberRef[0]->pxObject;
    if ( pxObject )
    {
      qmemcpy(&igi2_frame.tSquadCenter, (void *)(pxObject[8] + 40), sizeof(igi2_frame.tSquadCenter));
      v2 = ptAISquad;
    }
  }
  AISquad_FindSquadAreaRadius(&v2->tQTask, &igi2_frame.tSquadCenter, &igi2_frame.vSquadRadius);
  v5 = AISquad_ptQTaskList;
  v6 = 0;
  v7 = AISquad_ptQTaskList->nTask <= 0;
  memset(&igi2_frame.tDelta, 0, sizeof(igi2_frame.tDelta));
  igi2_frame.nCount = 0;
  if ( !v7 )
  {
    igi2_frame.ptQTask = AISquad_ptQTaskList->ptQTask;
    do
    {
      v8 = *igi2_frame.ptQTask;
      if ( *igi2_frame.ptQTask != (struct QTask_s *)v2 && !BYTE1(v8[218].ptNext) )
      {
        ptParent = v8[1].ptParent;
        memset(&igi2_frame.tReal64x3, 0, sizeof(igi2_frame.tReal64x3));
        if ( ptParent )
        {
          ptHead = v8[1].ptNext->tQTaskChildren.ptHead;
          if ( ptHead )
          {
            qmemcpy(&igi2_frame.tReal64x3, &ptHead->ptParent[1], sizeof(igi2_frame.tReal64x3));
            v2 = ptAISquad;
            v5 = AISquad_ptQTaskList;
          }
        }
        AISquad_FindSquadAreaRadius(v8, &igi2_frame.tReal64x3, &igi2_frame.vReal32);
        igi2_frame.tReal32x3.vX = igi2_frame.tSquadCenter.vX - igi2_frame.tReal64x3.vX;
        igi2_frame.tReal32x3.vY = igi2_frame.tSquadCenter.vY - igi2_frame.tReal64x3.vY;
        igi2_frame.tReal32x3.vZ = igi2_frame.tSquadCenter.vZ - igi2_frame.tReal64x3.vZ;
        v11 = sqrt(
                igi2_frame.tReal32x3.vX * igi2_frame.tReal32x3.vX
              + igi2_frame.tReal32x3.vY * igi2_frame.tReal32x3.vY
              + (igi2_frame.tSquadCenter.vZ - igi2_frame.tReal64x3.vZ) * (igi2_frame.tSquadCenter.vZ - igi2_frame.tReal64x3.vZ));
        igi2_frame.vLen = v11;
        if ( v11 > 4096.0 )
        {
          v12 = igi2_frame.vReal32 + igi2_frame.vSquadRadius;
          if ( igi2_frame.vLen < v12 )
          {
            v13 = v12 / igi2_frame.vLen;
            ++igi2_frame.nCount;
            igi2_frame.tReal32x3.vY = v13 * igi2_frame.tReal32x3.vY;
            igi2_frame.tReal32x3.vZ = v13 * igi2_frame.tReal32x3.vZ;
            igi2_frame.tDelta.vX = igi2_frame.tReal32x3.vX * v13 + igi2_frame.tDelta.vX;
            igi2_frame.tDelta.vY = igi2_frame.tReal32x3.vY + igi2_frame.tDelta.vY;
            igi2_frame.tDelta.vZ = igi2_frame.tReal32x3.vZ + igi2_frame.tDelta.vZ;
          }
        }
      }
      ++v6;
      ++igi2_frame.ptQTask;
    }
    while ( v6 < v5->nTask );
    if ( igi2_frame.nCount )
    {
      v14 = 1.0 / (double)igi2_frame.nCount;
      igi2_frame.tDelta.vY = v14 * igi2_frame.tDelta.vY;
      igi2_frame.tDelta.vZ = v14 * igi2_frame.tDelta.vZ;
      igi2_frame.tSquadCenter.vX = igi2_frame.tDelta.vX * v14 + igi2_frame.tSquadCenter.vX;
      igi2_frame.tSquadCenter.vY = igi2_frame.tDelta.vY + igi2_frame.tSquadCenter.vY;
      igi2_frame.tSquadCenter.vZ = igi2_frame.tDelta.vZ + igi2_frame.tSquadCenter.vZ;
    }
  }
  qmemcpy(ptCenter, &igi2_frame.tSquadCenter, sizeof(struct real64x3_t));
}

// source: j/0/humanai/aisquad.c:2921  [anchor-caller]
void __cdecl AISquad_SpreadTeamSideways(
        struct QTask_s *ptQTask,
        struct real64x3_t *ptTargetPos,
        int nTeam,
        struct AISquadSpreadOutContext_s *ptContext)
{
  int v6; // eax
  int v7; // ebp
  struct QTask_s *v8; // ecx
  struct QTask_s *v9; // esi
  struct HumanAI_s *ptHead; // eax
  double v11; // st7
  double v12; // st7
  long double v13; // st4
  long double v14; // st7
  struct AIGraphNode_s *Node; // esi
  struct AIGraphNode_s *ClosestNodeFromStartingNode; // eax
  int v17; // esi
  int v18; // ecx
  struct QTask_s *v19; // edx
  int v20; // [esp+10h] [ebp-20h]
  struct QTask_s *ptParent; // [esp+14h] [ebp-1Ch]
  struct QTask_s *v22; // [esp+1Ch] [ebp-14h]
  struct QTask_s *v23; // [esp+20h] [ebp-10h]
  float v24; // [esp+24h] [ebp-Ch]
  float v25; // [esp+28h] [ebp-8h]

  v6 = *((_DWORD *)&ptQTask->ptNext + (int)&ptQTask[216].ptNext->tQTaskChildren.ptHead + 10 * nTeam + 2);
  if ( v6 )
    v7 = *(_DWORD *)(v6 + 8);
  else
    v7 = 0;
  v20 = 0;
  if ( v7 )
  {
    if ( ptContext->nUpdateTimer <= 0 )
    {
      if ( *(int *)(v7 + 4444) >= 150
        && Random_GetRandomNumberReal32(&Game_ptGame->tRunRandomState) >= 0.5
        && HumanAI_IsOnCoverNode((struct HumanAI_s *)v7) == false
        && HumanAI_IsOnTheWayToCoverNode((struct HumanAI_s *)v7) == false
        && HumanAI_IsActivating((struct HumanAI_s *)v7) == false
        && HumanAI_IsMoving((struct HumanAI_s *)v7) == false
        && HumanAI_IsShotGunSholdier((struct HumanAI_s *)v7) == false )
      {
        if ( HumanAI_IsLessThanPercentageAmmoLeftInWeapon((struct HumanAI_s *)v7, 30.0) )
        {
          v8 = &ptQTask[nTeam];
          v22 = v8;
          if ( (int)v8[1].ptParent > 0 )
          {
            v9 = v8 + 1;
            v23 = v8 + 1;
            ptParent = v8[1].ptParent;
            do
            {
              ptHead = (struct HumanAI_s *)v9->ptNext->tQTaskChildren.ptHead;
              if ( ptHead && HumanAI_GetTargetQTask(ptHead, true) )
                ++v20;
              v9 = (struct QTask_s *)((char *)v9 + 4);
              ptParent = (struct QTask_s *)((char *)ptParent - 1);
            }
            while ( ptParent );
            if ( v20 >= 2 )
            {
              v11 = ptTargetPos->vX - ptContext->tCenter.vX;
              v25 = ptTargetPos->vY - ptContext->tCenter.vY;
              if ( v11 != 0.0 || v25 != 0.0 )
              {
                v12 = -v11;
                v13 = sqrt(v25 * v25 + v12 * v12);
                v24 = v25 * (1.0 / v13);
                v14 = v12 * (1.0 / v13);
                ptContext->atPos[0].vX = v24 * *(float *)&ptQTask[218].tQTaskRefList.ptTail * -4096.0
                                       + ptContext->tCenter.vX;
                ptContext->atPos[0].vY = v14 * *(float *)&ptQTask[218].tQTaskRefList.ptTail * -4096.0
                                       + ptContext->tCenter.vY;
                ptContext->atPos[0].vZ = ptContext->tCenter.vZ;
                ptContext->atPos[1].vX = v24 * *(float *)&ptQTask[218].tQTaskRefList.ptTail * 4096.0
                                       + ptContext->tCenter.vX;
                ptContext->atPos[1].vY = v14 * *(float *)&ptQTask[218].tQTaskRefList.ptTail * 4096.0
                                       + ptContext->tCenter.vY;
                ptContext->atPos[1].vZ = ptContext->tCenter.vZ;
                ptContext->atPos[2].vX = v24 * *(float *)&ptQTask[218].tQTaskRefList.ptTail * -4096.0
                                       + ptContext->tCenter.vX;
                ptContext->atPos[2].vY = v14 * *(float *)&ptQTask[218].tQTaskRefList.ptTail * -4096.0
                                       + ptContext->tCenter.vY;
                ptContext->atPos[2].vZ = ptContext->tCenter.vZ;
                ptContext->atPos[3].vX = v24 * *(float *)&ptQTask[218].tQTaskRefList.ptTail * 4096.0
                                       + ptContext->tCenter.vX;
                ptContext->atPos[3].vY = v14 * *(float *)&ptQTask[218].tQTaskRefList.ptTail * 4096.0
                                       + ptContext->tCenter.vY;
                ptContext->atPos[3].vZ = ptContext->tCenter.vZ;
                ptContext->atPos[4].vX = v24 * *(float *)&ptQTask[218].tQTaskRefList.ptTail * -4096.0
                                       + ptContext->tCenter.vX;
                ptContext->atPos[4].vY = v14 * *(float *)&ptQTask[218].tQTaskRefList.ptTail * -4096.0
                                       + ptContext->tCenter.vY;
                ptContext->atPos[4].vZ = ptContext->tCenter.vZ;
                ptContext->atPos[5].vX = v24 * *(float *)&ptQTask[218].tQTaskRefList.ptTail * 4096.0
                                       + ptContext->tCenter.vX;
                ptContext->atPos[5].vY = v14 * *(float *)&ptQTask[218].tQTaskRefList.ptTail * 4096.0
                                       + ptContext->tCenter.vY;
                ptContext->atPos[5].vZ = ptContext->tCenter.vZ;
                ptContext->atPos[6].vX = v24 * *(float *)&ptQTask[218].tQTaskRefList.ptTail * -4096.0
                                       + ptContext->tCenter.vX;
                ptContext->atPos[6].vY = v14 * *(float *)&ptQTask[218].tQTaskRefList.ptTail * -4096.0
                                       + ptContext->tCenter.vY;
                ptContext->atPos[6].vZ = ptContext->tCenter.vZ;
                ptContext->atPos[7].vX = v24 * *(float *)&ptQTask[218].tQTaskRefList.ptTail * 4096.0
                                       + ptContext->tCenter.vX;
                ptContext->atPos[7].vY = v14 * *(float *)&ptQTask[218].tQTaskRefList.ptTail * 4096.0
                                       + ptContext->tCenter.vY;
                ptContext->atPos[7].vZ = ptContext->tCenter.vZ;
              }
              Node = (struct AIGraphNode_s *)Graph_GetNode(*(struct Graph_s **)(v7 + 29128), *(_DWORD *)(v7 + 29948));
              if ( Node )
              {
                ClosestNodeFromStartingNode = AIGraph_GetClosestNodeFromStartingNode(
                                                *(struct AIGraph_t **)(v7 + 29128),
                                                Node,
                                                &ptContext->atPos[(int)ptQTask[216].ptNext],
                                                50);
                if ( ClosestNodeFromStartingNode )
                {
                  v17 = (int)v22[1].ptParent;
                  v18 = 0;
                  if ( v17 <= 0 )
                  {
LABEL_31:
                    *(_DWORD *)(v7 + 29952) = ClosestNodeFromStartingNode->tGraphNode.nID;
                    *(_DWORD *)(v7 + 4444) = 0;
                    ptContext->nUpdateTimer = 150;
                  }
                  else
                  {
                    v19 = v23;
                    while ( v19->ptNext->tQTaskChildren.ptHead[748].tQTaskRefList.ptTail != (struct QReference_s *)ClosestNodeFromStartingNode->tGraphNode.nID )
                    {
                      ++v18;
                      v19 = (struct QTask_s *)((char *)v19 + 4);
                      if ( v18 >= v17 )
                        goto LABEL_31;
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
    else
    {
      --ptContext->nUpdateTimer;
    }
  }
}

// source: j/0/humanai/aisquad.c:3049  [anchor-caller]
void __cdecl AISquad_SquadActionLeapFrogAdvance(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct AIGraphNode_s *pptAIGraphNode; };
    struct { char igi2_o1[4]; struct QTask_s *ptHead; };
    struct { char igi2_o2[8]; struct QTask_s *ptTail; };
    struct { char igi2_o3[12]; struct AISquadOrderContext_s ptSquadOrder; };
    char igi2_extent[68];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTaskNodeList_s *p_tQTaskChildren; // ebx
  struct QTask_s *ptMiddle; // esi
  int v4; // edi
  double DistanceToTarget; // st7
  struct QTask_s *v7; // eax
  int v8; // eax
  struct QTask_s *ptParent; // eax
  struct QTask_s *v10; // edx
  int v11; // esi
  struct HumanAI_s *v12; // edi
  void (__cdecl *pfRunCallback)(struct HumanAI_s *, struct HumanAIActionStackItem_s *); // eax
  struct QTask_s *v14; // eax
  int v15; // edi
  int v16; // esi
  struct QTask_s *v17; // ebx
  struct QTask_s *v18; // eax
  struct QTask_s *v19; // eax
  struct QTask_s *v20; // ecx
  struct QTask_s *v21; // eax
  struct QTask_s *v22; // edi
  struct AIGraph_t *v23; // esi
  struct AIGraphNode_s *Node; // eax
  struct QTask_s *v25; // edi
  struct AIGraphNode_s *v26; // eax
  int v27; // edx
  int v28; // esi
  int FirstMemberWithoutVisibleTarget; // eax
  int v30; // ecx
  int v31; // edx
  int v32; // eax
  int v33; // eax
  struct QTask_s *TeamLeader; // eax
  struct QTask_s *v35; // eax
  struct QTask_s *v36; // ecx
  struct HumanAI_s *v37; // eax
  int *ptQTaska = *(int * *)&ptQTask; // [esp+5Ch] [ebp+4h] ARGSLOT

  p_tQTaskChildren = &ptQTask[7 * (int)ptQTask[215].tQTaskChildren.ptHead + 180].tQTaskChildren;
  ptMiddle = ptQTask[7 * (int)ptQTask[215].tQTaskChildren.ptHead + 180].tQTaskChildren.ptMiddle;
  v4 = 1 - (_DWORD)ptMiddle;
  ptQTaska = (int *)p_tQTaskChildren;
  DistanceToTarget = AISquad_GetDistanceToTarget(ptQTask, 1 - (_DWORD)ptMiddle);
  v7 = ptQTask[216].tQTaskChildren.ptMiddle;
  *(float *)&igi2_frame.pptAIGraphNode = DistanceToTarget;
  if ( !v7 )
    AISquad_SetFormation(ptQTask, (int)ptMiddle, AISQUAD_FORMATION_V);
  igi2_frame.ptHead = p_tQTaskChildren[2].ptHead->tQTaskChildren.ptHead;
  if ( igi2_frame.ptHead )
  {
    v8 = (int)p_tQTaskChildren[1].ptHead;
    if ( v8 > 0 )
    {
      p_tQTaskChildren[1].ptHead = (struct QTask_s *)(v8 - 1);
      return;
    }
    if ( *(float *)&igi2_frame.pptAIGraphNode > 122880.0 && (int)ptQTask[v4 + 1].ptParent > 1 )
    {
      AISquad_FindSpreadOutCenter((struct AISquad_s *)ptQTask, (struct real64x3_t *)&p_tQTaskChildren[3].ptMiddle);
      AISquad_SpreadTeamSideways(
        ptQTask,
        (struct real64x3_t *)&igi2_frame.ptHead[1],
        1 - (_DWORD)ptMiddle,
        (struct AISquadSpreadOutContext_s *)&p_tQTaskChildren[2].ptTail);
    }
    p_tQTaskChildren[1].ptHead = (struct QTask_s *)30;
    AISquad_UpdateLeapfrogTeams(ptQTask);
    ptParent = ptQTask[v4 + 1].ptParent;
    v10 = &ptQTask[v4];
    v11 = 0;
    igi2_frame.ptTail = v10;
    if ( (int)ptParent > 0 )
    {
      igi2_frame.pptAIGraphNode = (struct AIGraphNode_s *)&v10[1];
      do
      {
        v12 = *(struct HumanAI_s **)(igi2_frame.pptAIGraphNode->tGraphNode.nID + 8);
        if ( v12 )
        {
          pfRunCallback = v12->atActionStackItemList[0].pfRunCallback;
          if ( !*(_DWORD *)pfRunCallback
            || (!pfRunCallback
             || *((void (__cdecl **)(struct HumanAI_s *, struct HumanAIActionStackItem_s *))pfRunCallback + 6) != HumanAIContent_CombatIdleInitCB)
            && (!*(_DWORD *)pfRunCallback
             || !pfRunCallback
             || *((void (__cdecl **)(struct HumanAI_s *, struct HumanAIActionStackItem_s *))pfRunCallback + 6) != HumanAIContent_ActivateInitCB) )
          {
            HumanAI_PopTopActionStackItems(v12);
            p_tQTaskChildren = (struct QTaskNodeList_s *)ptQTaska;
            v10 = igi2_frame.ptTail;
          }
        }
        v14 = v10[1].ptParent;
        ++v11;
        igi2_frame.pptAIGraphNode = (struct AIGraphNode_s *)((char *)igi2_frame.pptAIGraphNode + 4);
      }
      while ( v11 < (int)v14 );
    }
    v15 = (int)v10[1].ptParent;
    v16 = 0;
    if ( v15 <= 0 )
    {
LABEL_27:
      if ( AISquad_GetFirstMemberWithVisibleTarget(ptQTask, (int)p_tQTaskChildren->ptMiddle) < 0 )
        return;
    }
    else
    {
      v17 = v10 + 1;
      while ( HumanAI_GetNumberOfVisibleTargets(v17->ptNext->tQTaskChildren.ptHead) <= 0 )
      {
        ++v16;
        v17 = (struct QTask_s *)((char *)v17 + 4);
        if ( v16 >= v15 )
          goto LABEL_26;
      }
      if ( v16 < 0 )
      {
LABEL_26:
        p_tQTaskChildren = (struct QTaskNodeList_s *)ptQTaska;
        goto LABEL_27;
      }
      p_tQTaskChildren = (struct QTaskNodeList_s *)ptQTaska;
    }
    v18 = p_tQTaskChildren->ptMiddle;
    if ( (int)ptQTask[(int)v18 + 1].ptParent > 0 )
    {
      v19 = (struct QTask_s *)(5 * (_DWORD)v18);
      v20 = *(&ptQTask[1].ptParent + 2 * (_DWORD)v19);
      v21 = (struct QTask_s *)((char *)ptQTask + 8 * (_DWORD)v19);
      v22 = v20 ? v21[1].ptNext->tQTaskChildren.ptHead : nullptr;
      v23 = (struct AIGraph_t *)v22[728].tQTaskChildren.ptHead;
      igi2_frame.ptTail = (struct QTask_s *)v22[748].tQTaskRefList.ptTail;
      Node = (struct AIGraphNode_s *)Graph_GetNode(&v23->tGraph, (int)igi2_frame.ptTail);
      v25 = v22[6].ptParent;
      igi2_frame.pptAIGraphNode = Node;
      if ( !v25->ptNext || !v25 )
      {
        AIGraph_GetClosestNode(&igi2_frame.pptAIGraphNode, v23, (struct real64x3_t *)&igi2_frame.ptHead[1], false);
        v26 = igi2_frame.pptAIGraphNode;
        if ( *(float *)&igi2_frame.pptAIGraphNode != 0.0 )
        {
          v27 = (int)igi2_frame.ptTail;
          *ptQTaska = igi2_frame.pptAIGraphNode->tGraphNode.nID;
          if ( v26->tGraphNode.nID != v27 )
          {
            v28 = ptQTaska[1];
            FirstMemberWithoutVisibleTarget = AISquad_GetFirstMemberWithoutVisibleTarget(ptQTask, v28);
            if ( FirstMemberWithoutVisibleTarget >= 0 )
            {
              v30 = 5 * v28 + 5;
              v31 = *((_DWORD *)&ptQTask->ptNext + 2 * v30);
              v32 = FirstMemberWithoutVisibleTarget + 2 * v30;
              *((_DWORD *)&ptQTask->ptNext + 2 * v30) = *((_DWORD *)&ptQTask->ptNext + v32);
              *((_DWORD *)&ptQTask->ptNext + v32) = v31;
            }
            v33 = ptQTaska[1];
            if ( ptQTask[v33 + 1].ptParent && ptQTask[v33 + 1].ptNext->tQTaskChildren.ptHead )
            {
              TeamLeader = AISquad_GetTeamLeader(ptQTask, v33);
              AISquad_SelectAndPlaySoundAtMembersPos((struct AISquad_s *)ptQTask, 11, TeamLeader);
            }
            igi2_frame.ptSquadOrder.eOrder = AISQUAD_ORDER_MOVE_TO_NODE;
            igi2_frame.ptSquadOrder.iDelay = AISquad_GetOrderDelay((struct AISquad_s *)ptQTask);
            igi2_frame.ptSquadOrder.uContext.tMoveToNodeContext.nNodeId = *ptQTaska;
            v35 = &ptQTask[ptQTaska[1]];
            v36 = v35[1].ptParent;
            igi2_frame.ptSquadOrder.uContext.tMoveToNodeContext.isRun = 1;
            if ( v36 )
              v37 = (struct HumanAI_s *)v35[1].ptNext->tQTaskChildren.ptHead;
            else
              v37 = nullptr;
            HumanAIContent_ReceiveSquadOrder(v37, &igi2_frame.ptSquadOrder);
            AISquad_SetFormation(ptQTask, ptQTaska[1], AISQUAD_FORMATION_V);
            AISquad_ClearTeamsMemberTimers((struct AISquad_s *)ptQTask, ptQTaska[1]);
          }
        }
      }
    }
  }
}

// source: j/0/humanai/aisquad.c:3201  [anchor-caller]
enum bool __cdecl AISquad_SquadActionLeapFrogInitHandler(
        struct QTask_s *ptQTask,
        struct AISquadActionChangeContext_s *ptActionChangeContext)
{
  struct QTaskNodeList_s *p_tQTaskChildren; // edi
  struct QTask_s **p_ptParent; // ecx
  int v4; // edx
  struct QTask_s *v5; // ebx
  struct QTask_s *ptHead; // eax
  struct QReference_s *ptTail; // edx
  struct QTask_s *v8; // eax
  struct QTask_s *ptTargetQTask; // eax
  int ptMiddle; // ecx

  p_tQTaskChildren = &ptQTask[7 * (int)ptQTask[215].tQTaskChildren.ptHead + 180].tQTaskChildren;
  AISquad_MakeOneTeam(ptQTask);
  p_ptParent = &ptQTask[1].ptParent;
  v4 = 0;
  if ( (int)ptQTask[1].ptParent > 0 )
  {
    v5 = ptQTask + 1;
    do
    {
      ptHead = v5->ptNext->tQTaskChildren.ptHead;
      if ( ptHead )
        ptHead[748].ptParent = (struct QTask_s *)ptHead[748].tQTaskRefList.ptTail;
      ++v4;
      v5 = (struct QTask_s *)((char *)v5 + 4);
    }
    while ( v4 < (int)*p_ptParent );
  }
  p_tQTaskChildren->ptHead = (struct QTask_s *)-1;
  ptTail = ptQTask[215].tQTaskRefList.ptTail;
  v8 = nullptr;
  if ( (int)ptTail > 0 )
  {
    do
    {
      v8 = (struct QTask_s *)((char *)v8 + (_DWORD)*p_ptParent);
      p_ptParent += 10;
      ptTail = (struct QReference_s *)((char *)ptTail - 1);
    }
    while ( ptTail );
  }
  p_tQTaskChildren->ptTail = v8;
  p_tQTaskChildren->ptMiddle = (struct QTask_s *)1;
  ptTargetQTask = ptActionChangeContext->tToLeapFrogContext.ptTargetQTask;
  if ( ptTargetQTask
    || (int)ptQTask[215].tQTaskRefList.ptMiddle > 0
    && (ptTargetQTask = ptQTask[182].tQTaskChildren.ptHead->tQTaskChildren.ptHead) != nullptr )
  {
    p_tQTaskChildren[2].ptHead = (struct QTask_s *)QTask_NewQTaskRef(ptTargetQTask);
  }
  else
  {
    p_tQTaskChildren[2].ptHead = nullptr;
  }
  p_tQTaskChildren[1].ptMiddle = (struct QTask_s *)-1;
  p_tQTaskChildren[1].ptTail = (struct QTask_s *)1184890880;
  p_tQTaskChildren[1].ptHead = nullptr;
  AISquad_FindSpreadOutCenter((struct AISquad_s *)ptQTask, (struct real64x3_t *)&p_tQTaskChildren[3].ptMiddle);
  ptMiddle = (int)p_tQTaskChildren->ptMiddle;
  p_tQTaskChildren[2].ptTail = nullptr;
  *(_DWORD *)&ptQTask[ptMiddle + 1].eQTaskType = 1;
  *(_DWORD *)&ptQTask[-(int)p_tQTaskChildren->ptMiddle + 2].eQTaskType = 1;
  AISquad_UpdateLeapfrogTeams(ptQTask);
  return true;
}

// source: j/0/humanai/aisquad.c:3290  [anchor-caller]
enum bool __cdecl AISquad_SquadActionLeapFrogRunHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptParent; // eax
  struct AISquadActionChangeContext_s tChangeContext; // [esp+8h] [ebp-D8h] BYREF

  ptParent = ptQTask[7 * (int)ptQTask[215].tQTaskChildren.ptHead + 180].ptParent;
  if ( ptParent && ptParent->tQTaskChildren.ptHead )
  {
    AISquad_SquadActionLeapFrogAdvance(ptQTask);
    return true;
  }
  else
  {
    tChangeContext.eNextAction = AISQUAD_ACTION_IDLE;
    tChangeContext.isDeserializing = false;
    tChangeContext.isPopMembersStacks = true;
    AISquad_PopActionStack(ptQTask, &tChangeContext);
    return true;
  }
}

// source: j/0/humanai/aisquad.c:3335  [anchor-mhash]
enum bool __cdecl AISquad_SquadActionPatrolInitHandler(
        struct QTask_s *ptQTask,
        struct AISquadActionChangeContext_s *ptActionChangeContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct AISquadOrderContext_s tOrderContext; };
    struct { char igi2_o1[56]; struct AISquadActionChangeContext_s tChangeContext; };
    char igi2_extent[276];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTaskNodeList_s *p_tQTaskChildren; // ebp
  struct HumanAI_s *ptHead; // esi
  int OrderDelay; // eax
  int nPatrolPathId; // ecx

  p_tQTaskChildren = &ptQTask[7 * (int)ptQTask[215].tQTaskChildren.ptHead + 180].tQTaskChildren;
  AISquad_MakeOneTeam(ptQTask);
  if ( ptQTask[1].ptParent && (ptHead = (struct HumanAI_s *)ptQTask[1].ptNext->tQTaskChildren.ptHead) != nullptr )
  {
    p_tQTaskChildren->ptHead = (struct QTask_s *)ptActionChangeContext->tToPatrolContext.nPatrolPathId;
    igi2_frame.tOrderContext.eOrder = AISQUAD_ORDER_PATROL;
    OrderDelay = AISquad_GetOrderDelay((struct AISquad_s *)ptQTask);
    nPatrolPathId = ptActionChangeContext->tToPatrolContext.nPatrolPathId;
    igi2_frame.tOrderContext.iDelay = OrderDelay;
    igi2_frame.tOrderContext.uContext.tMoveToNodeContext.nNodeId = nPatrolPathId;
    HumanAIContent_ReceiveSquadOrder(ptHead, &igi2_frame.tOrderContext);
    AISquad_SetFormation(ptQTask, 0, AISQUAD_FORMATION_STAGGEREDCOLUMN);
    return true;
  }
  else
  {
    igi2_frame.tChangeContext.eNextAction = AISQUAD_ACTION_IDLE;
    igi2_frame.tChangeContext.isPopMembersStacks = true;
    igi2_frame.tChangeContext.isDeserializing = false;
    AISquad_PopActionStack(ptQTask, &igi2_frame.tChangeContext);
    return false;
  }
}

// source: j/0/humanai/aisquad.c:3392  [anchor-mhash]
enum bool __cdecl AISquad_SquadActionPatrolRunHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *v1; // edi
  struct HumanAI_s *ptHead; // eax
  void (__cdecl *pfRunCallback)(struct HumanAI_s *, struct HumanAIActionStackItem_s *); // esi
  int v4; // ebx
  int v5; // ebp
  int v6; // ebp
  struct AISquadActionChangeContext_s tChangeContext; // [esp+18h] [ebp-D8h] BYREF

  v1 = ptQTask;
  if ( !ptQTask[1].ptParent || (ptHead = (struct HumanAI_s *)ptQTask[1].ptNext->tQTaskChildren.ptHead) == nullptr )
  {
LABEL_19:
    tChangeContext.eNextAction = AISQUAD_ACTION_IDLE;
    tChangeContext.isPopMembersStacks = true;
    tChangeContext.isDeserializing = false;
    AISquad_PopActionStack(v1, &tChangeContext);
    return true;
  }
  pfRunCallback = ptHead->atActionStackItemList[0].pfRunCallback;
  v4 = *(_DWORD *)pfRunCallback;
  if ( !*(_DWORD *)pfRunCallback )
    goto LABEL_9;
  if ( pfRunCallback
    && *((void (__cdecl **)(struct HumanAI_s *, struct HumanAIActionStackItem_s *))pfRunCallback + 6) == HumanAIContent_PatrolInitCB )
  {
    goto LABEL_11;
  }
  if ( v4 && pfRunCallback )
    v5 = *((_DWORD *)pfRunCallback + 3);
  else
LABEL_9:
    v5 = -1;
  v1 = ptQTask;
  if ( v5 != HumanAI_GetEventPriority(ptHead, 26) )
  {
    v6 = 1;
    goto LABEL_13;
  }
LABEL_11:
  v6 = 0;
LABEL_13:
  if ( !v1[216].tQTaskChildren.ptMiddle
    && v4
    && pfRunCallback
    && *((void (__cdecl **)(struct HumanAI_s *, struct HumanAIActionStackItem_s *))pfRunCallback + 6) == HumanAIContent_PatrolInitCB )
  {
    AISquad_SetFormation(v1, 0, AISQUAD_FORMATION_STAGGEREDCOLUMN);
  }
  if ( v6 )
    goto LABEL_19;
  return true;
}

// source: j/0/humanai/aisquad.c:3445  [anchor-mhash]
enum bool __cdecl AISquad_SquadActionMoveSearchInDirectionInitHandler(
        struct QTask_s *ptQTask,
        struct AISquadActionChangeContext_s *ptActionChangeContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct HumanAI_s *ptHumanAI; };
    struct { char igi2_o1[4]; struct AIGraphNode_s *pptAIGraphNode; };
    struct { char igi2_o2[8]; struct AISquadOrderContext_s ptSquadOrder; };
    struct { char igi2_o3[64]; struct AISquadActionChangeContext_s v11; };
    char igi2_extent[284];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTaskNodeList_s *p_tQTaskChildren; // esi
  struct QTask_s *ptHead; // ecx
  struct AIGraphNode_s *v4; // eax
  int nID; // ecx
  BOOL v6; // ecx

  p_tQTaskChildren = &ptQTask[7 * (int)ptQTask[215].tQTaskChildren.ptHead + 180].tQTaskChildren;
  AISquad_MakeOneTeam(ptQTask);
  if ( !ptQTask[1].ptParent
    || (ptHead = ptQTask[1].ptNext->tQTaskChildren.ptHead, (igi2_frame.ptHumanAI = (struct HumanAI_s *)ptHead) == nullptr)
    || ptActionChangeContext->tToSearchInDirectionContext.tDirection.vX == 0.0
    && ptActionChangeContext->tToSearchInDirectionContext.tDirection.vY == 0.0
    && ptActionChangeContext->tToSearchInDirectionContext.tDirection.vZ == 0.0 )
  {
    igi2_frame.v11.eNextAction = AISQUAD_ACTION_IDLE;
    igi2_frame.v11.isPopMembersStacks = true;
    igi2_frame.v11.isDeserializing = false;
    AISquad_PopActionStack(ptQTask, &igi2_frame.v11);
    return false;
  }
  else
  {
    AIGraph_GetClosestNode(
      &igi2_frame.pptAIGraphNode,
      (struct AIGraph_t *)ptHead[728].tQTaskChildren.ptHead,
      &ptActionChangeContext->tToSearchInDirectionContext.tPosition,
      false);
    v4 = igi2_frame.pptAIGraphNode;
    if ( igi2_frame.pptAIGraphNode )
      nID = igi2_frame.pptAIGraphNode->tGraphNode.nID;
    else
      nID = HIDWORD(igi2_frame.ptHumanAI->tCommon.tAimPosition.vY);
    p_tQTaskChildren[3].ptTail = (struct QTask_s *)nID;
    *(struct real32x3_t *)p_tQTaskChildren = ptActionChangeContext->tToSearchInDirectionContext.tDirection;
    Graph_GetNodePos((struct real64x3_t *)&p_tQTaskChildren[1].ptMiddle, &v4->tGraphNode);
    p_tQTaskChildren[3].ptMiddle = nullptr;
    AISquad_ClearMembersPaths(ptQTask);
    AISquad_ClearMembersActionStacks(ptQTask);
    v6 = Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eDifficultyLevel != GAMEDIFFICULTY_1;
    igi2_frame.ptSquadOrder.uContext.tMoveToNodeContext.nNodeId = (int)p_tQTaskChildren[3].ptTail;
    igi2_frame.ptSquadOrder.iDelay = 0;
    igi2_frame.ptSquadOrder.eOrder = AISQUAD_ORDER_MOVE_TO_NODE;
    igi2_frame.ptSquadOrder.uContext.tMoveToNodeContext.isRun = v6;
    HumanAIContent_ReceiveSquadOrder(igi2_frame.ptHumanAI, &igi2_frame.ptSquadOrder);
    AISquad_SetFormation(ptQTask, 0, AISQUAD_FORMATION_STAGGEREDCOLUMN);
    return true;
  }
}

// source: j/0/humanai/aisquad.c:3523  [anchor-mhash]
enum bool __cdecl AISquad_SquadActionMoveSearchInDirectionRunHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct AIGraphNode_s *pptAIGraphNode; };
    struct { char igi2_o1[4]; float v20; };
    struct { char igi2_o2[8]; float v21; };
    struct { char igi2_o3[12]; float v22; };
    struct { char igi2_o4[16]; struct AISquadEventContext_s v23; };
    struct { char igi2_o5[128]; struct real64x3_t ptPosition; };
    char igi2_extent[152];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTaskNodeList_s *p_tQTaskChildren; // ebp
  struct QTask_s *ptHead; // edi
  enum GameDifficulty_e eDifficultyLevel; // edx
  struct QTask_s *ptMiddle; // eax
  float v5; // eax
  float v6; // edx
  float v7; // ecx
  double *ptParent; // ebx
  double v10; // st3
  float v11; // edx
  float v12; // ecx
  long double v13; // st4
  double v14; // st7
  double v15; // st6
  struct AIGraph_t *v16; // ebx
  int OrderDelay; // eax
  int ptTail; // edx

  p_tQTaskChildren = &ptQTask[7 * (int)ptQTask[215].tQTaskChildren.ptHead + 180].tQTaskChildren;
  if ( ptQTask[1].ptParent )
    ptHead = ptQTask[1].ptNext->tQTaskChildren.ptHead;
  else
    ptHead = nullptr;
  if ( !ptQTask[216].tQTaskChildren.ptMiddle )
    AISquad_SetFormation(ptQTask, 0, AISQUAD_FORMATION_V);
  if ( p_tQTaskChildren[3].ptTail != ptHead[748].ptParent )
  {
    igi2_frame.v23.nNumSquadMemberQTaskRefs = (int)p_tQTaskChildren[3].ptTail;
    eDifficultyLevel = Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eDifficultyLevel;
    igi2_frame.v23.eEvent = 4;
    igi2_frame.v23.nPriority = 0;
    igi2_frame.v23.aptSquadMemberQTaskRef[0] = (struct QReference_s *)(eDifficultyLevel != GAMEDIFFICULTY_1);
    HumanAIContent_ReceiveSquadOrder((struct HumanAI_s *)ptHead, (struct AISquadOrderContext_s *)&igi2_frame.v23);
  }
  ptMiddle = p_tQTaskChildren[3].ptMiddle;
  if ( ptMiddle )
  {
    if ( ptMiddle == (struct QTask_s *)1
      && p_tQTaskChildren[3].ptTail == (struct QTask_s *)ptHead[748].tQTaskRefList.ptTail )
    {
      v5 = *(float *)&p_tQTaskChildren->ptHead;
      v6 = *(float *)&p_tQTaskChildren->ptTail;
      memset(&igi2_frame.v23.nPriority, 0, 12);
      igi2_frame.v23.ptReferenceQTaskRef = nullptr;
      igi2_frame.v23.eEvent = 43;
      qmemcpy(&igi2_frame.v23.tPosition, &p_tQTaskChildren[1].ptMiddle, sizeof(igi2_frame.v23.tPosition));
      v7 = *(float *)&p_tQTaskChildren->ptMiddle;
      igi2_frame.v23.tDirection.vX = v5;
      igi2_frame.v23.tDirection.vY = v7;
      igi2_frame.v23.tDirection.vZ = v6;
      AISquad_ReceiveEvent(ptQTask, &igi2_frame.v23);
    }
    return true;
  }
  ptParent = (double *)ptHead->ptParent;
  Graph_GetNode((struct Graph_s *)ptHead[728].tQTaskChildren.ptHead, (int)p_tQTaskChildren[3].ptTail);
  igi2_frame.v20 = *(double *)&p_tQTaskChildren[1].ptMiddle - ptParent[5];
  igi2_frame.v21 = *(double *)&p_tQTaskChildren[2].ptHead - ptParent[6];
  v10 = *(double *)&p_tQTaskChildren[2].ptTail - ptParent[7];
  if ( sqrt(igi2_frame.v20 * igi2_frame.v20 + igi2_frame.v21 * igi2_frame.v21 + v10 * v10) >= 8192.0 )
    return true;
  v11 = *(float *)&p_tQTaskChildren->ptHead;
  v12 = *(float *)&p_tQTaskChildren->ptTail;
  igi2_frame.v21 = *(float *)&p_tQTaskChildren->ptMiddle;
  igi2_frame.v22 = v12;
  igi2_frame.v20 = v11;
  v13 = sqrt(v11 * v11 + igi2_frame.v21 * igi2_frame.v21 + v12 * v12);
  if ( v13 <= 0.0 )
  {
    igi2_frame.v22 = 0.0;
    v14 = 0.0;
    v15 = 0.0;
  }
  else
  {
    *(float *)&igi2_frame.pptAIGraphNode = 122880.0 / v13;
    v14 = *(float *)&igi2_frame.pptAIGraphNode * igi2_frame.v20;
    v15 = *(float *)&igi2_frame.pptAIGraphNode * igi2_frame.v21;
    igi2_frame.v22 = *(float *)&igi2_frame.pptAIGraphNode * igi2_frame.v22;
  }
  v16 = (struct AIGraph_t *)ptHead[728].tQTaskChildren.ptHead;
  igi2_frame.ptPosition.vX = v14 + *(double *)&p_tQTaskChildren[1].ptMiddle;
  igi2_frame.ptPosition.vY = v15 + *(double *)&p_tQTaskChildren[2].ptHead;
  igi2_frame.ptPosition.vZ = igi2_frame.v22 + *(double *)&p_tQTaskChildren[2].ptTail;
  AIGraph_GetClosestNode(&igi2_frame.pptAIGraphNode, v16, &igi2_frame.ptPosition, false);
  if ( *(float *)&igi2_frame.pptAIGraphNode != 0.0 )
  {
    p_tQTaskChildren[3].ptTail = (struct QTask_s *)igi2_frame.pptAIGraphNode->tGraphNode.nID;
    igi2_frame.v23.eEvent = 4;
    OrderDelay = AISquad_GetOrderDelay((struct AISquad_s *)ptQTask);
    ptTail = (int)p_tQTaskChildren[3].ptTail;
    igi2_frame.v23.nPriority = OrderDelay;
    igi2_frame.v23.nNumSquadMemberQTaskRefs = ptTail;
    igi2_frame.v23.aptSquadMemberQTaskRef[0] = (struct QReference_s *)(Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eDifficultyLevel != GAMEDIFFICULTY_1);
    HumanAIContent_ReceiveSquadOrder((struct HumanAI_s *)ptHead, (struct AISquadOrderContext_s *)&igi2_frame.v23);
  }
  p_tQTaskChildren[3].ptMiddle = (struct QTask_s *)1;
  return true;
}

// source: j/0/humanai/aisquad.c:3666  [anchor-mhash]
enum bool __cdecl AISquad_SquadActionLookSearchInDirectionInitHandler(
        struct QTask_s *ptQTask,
        struct AISquadActionChangeContext_s *ptActionChangeContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct AISquadOrderContext_s tOrderContext; };
    struct { char igi2_o1[56]; struct AISquadActionChangeContext_s tChangeContext; };
    char igi2_extent[276];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTaskNodeList_s *p_tQTaskChildren; // esi
  struct HumanAI_s *ptHead; // ebx

  p_tQTaskChildren = &ptQTask[7 * (int)ptQTask[215].tQTaskChildren.ptHead + 180].tQTaskChildren;
  AISquad_MakeOneTeam(ptQTask);
  if ( !ptQTask[1].ptParent
    || (ptHead = (struct HumanAI_s *)ptQTask[1].ptNext->tQTaskChildren.ptHead) == nullptr
    || ptActionChangeContext->tToSearchInDirectionContext.tDirection.vX == 0.0
    && ptActionChangeContext->tToSearchInDirectionContext.tDirection.vY == 0.0
    && ptActionChangeContext->tToSearchInDirectionContext.tDirection.vZ == 0.0 )
  {
    igi2_frame.tChangeContext.eNextAction = AISQUAD_ACTION_IDLE;
    igi2_frame.tChangeContext.isPopMembersStacks = true;
    igi2_frame.tChangeContext.isDeserializing = false;
    AISquad_PopActionStack(ptQTask, &igi2_frame.tChangeContext);
    return false;
  }
  else
  {
    *(struct real32x3_t *)p_tQTaskChildren = ptActionChangeContext->tToSearchInDirectionContext.tDirection;
    p_tQTaskChildren[1].ptHead = nullptr;
    p_tQTaskChildren[1].ptMiddle = nullptr;
    p_tQTaskChildren[1].ptTail = (struct QTask_s *)-1;
    AISquad_ClearMembersPaths(ptQTask);
    igi2_frame.tOrderContext.eOrder = AISQUAD_ORDER_LOOK_AT_POSITION;
    igi2_frame.tOrderContext.iDelay = AISquad_GetOrderDelay((struct AISquad_s *)ptQTask);
    qmemcpy(&igi2_frame.tOrderContext.uContext, &ptActionChangeContext->tToSearchInDirectionContext, 0x18u);
    HumanAIContent_ReceiveSquadOrder(ptHead, &igi2_frame.tOrderContext);
    AISquad_SetFormation(ptQTask, 0, AISQUAD_FORMATION_V);
    return true;
  }
}

// source: j/0/humanai/aisquad.c:3728  [anchor-mhash]
enum bool __cdecl AISquad_SquadActionLookSearchInDirectionRunHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct AIGraphNode_s *ptAIGraphNode; };
    struct { char igi2_o1[4]; struct real32x3_t tReal32x3; };
    struct { char igi2_o2[16]; struct AISquadOrderContext_s tOrderContext; };
    struct { char igi2_o3[72]; struct real64x3_t tNewDest; };
    struct { char igi2_o4[96]; struct AISquadActionChangeContext_s tActionChangeContext; };
    char igi2_extent[312];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTaskNodeList_s *p_tQTaskChildren; // esi
  struct QTask_s *ptHead; // edi
  struct QTask_s *v3; // eax
  struct QTask_s *ptTail; // eax
  int OrderDelay; // eax
  struct QTask_s *v6; // edx
  int v8; // eax
  bool v9; // sf
  float v10; // edx
  float v11; // ecx
  long double v12; // st4
  double v13; // st7
  double v14; // st6
  double *ptParent; // eax
  struct AIGraph_t *v16; // ebx
  int v17; // eax
  struct QTask_s *v18; // edx

  p_tQTaskChildren = &ptQTask[7 * (int)ptQTask[215].tQTaskChildren.ptHead + 180].tQTaskChildren;
  if ( ptQTask[1].ptParent )
    ptHead = ptQTask[1].ptNext->tQTaskChildren.ptHead;
  else
    ptHead = nullptr;
  if ( !ptQTask[216].tQTaskChildren.ptMiddle )
    AISquad_SetFormation(ptQTask, 0, AISQUAD_FORMATION_V);
  v3 = p_tQTaskChildren[1].ptHead;
  if ( v3 )
  {
    if ( v3 != (struct QTask_s *)1 )
      return true;
    ptTail = p_tQTaskChildren[1].ptTail;
    if ( ptTail != ptHead[748].ptParent )
    {
      igi2_frame.tOrderContext.eOrder = AISQUAD_ORDER_MOVE_TO_NODE;
      OrderDelay = AISquad_GetOrderDelay((struct AISquad_s *)ptQTask);
      v6 = p_tQTaskChildren[1].ptTail;
      igi2_frame.tOrderContext.iDelay = OrderDelay;
      *(_QWORD *)&igi2_frame.tOrderContext.uContext.tWaitForLeapFrogContext.tTargetPosition.vX = (unsigned int)v6;
      HumanAIContent_ReceiveSquadOrder((struct HumanAI_s *)ptHead, &igi2_frame.tOrderContext);
      return true;
    }
    if ( ptTail != (struct QTask_s *)ptHead[748].tQTaskRefList.ptTail )
      return true;
    igi2_frame.tActionChangeContext.eNextAction = AISQUAD_ACTION_IDLE;
    igi2_frame.tActionChangeContext.isPopMembersStacks = true;
    igi2_frame.tActionChangeContext.isDeserializing = false;
    AISquad_PopActionStack(ptQTask, &igi2_frame.tActionChangeContext);
    return true;
  }
  else
  {
    v8 = (int)&p_tQTaskChildren[1].ptMiddle->ptNext + 1;
    v9 = (int)&p_tQTaskChildren[1].ptMiddle[-3].tQTaskRefList.ptTail + 3 < 0;
    p_tQTaskChildren[1].ptMiddle = (struct QTask_s *)v8;
    if ( v9 ^ __OFSUB__(v8, 90) | (v8 == 90) )
      return true;
    v10 = *(float *)&p_tQTaskChildren->ptHead;
    v11 = *(float *)&p_tQTaskChildren->ptTail;
    LODWORD(igi2_frame.tReal32x3.vY) = p_tQTaskChildren->ptMiddle;
    igi2_frame.tReal32x3.vZ = v11;
    igi2_frame.tReal32x3.vX = v10;
    v12 = sqrt(v10 * v10 + igi2_frame.tReal32x3.vY * igi2_frame.tReal32x3.vY + v11 * v11);
    if ( v12 <= 0.0 )
    {
      igi2_frame.tReal32x3.vZ = 0.0;
      v13 = 0.0;
      v14 = 0.0;
    }
    else
    {
      *(float *)&igi2_frame.ptAIGraphNode = 122880.0 / v12;
      v13 = *(float *)&igi2_frame.ptAIGraphNode * igi2_frame.tReal32x3.vX;
      v14 = *(float *)&igi2_frame.ptAIGraphNode * igi2_frame.tReal32x3.vY;
      igi2_frame.tReal32x3.vZ = *(float *)&igi2_frame.ptAIGraphNode * igi2_frame.tReal32x3.vZ;
    }
    ptParent = (double *)ptHead->ptParent;
    v16 = (struct AIGraph_t *)ptHead[728].tQTaskChildren.ptHead;
    igi2_frame.tNewDest.vX = v13 + ptParent[5];
    igi2_frame.tNewDest.vY = v14 + ptParent[6];
    igi2_frame.tNewDest.vZ = igi2_frame.tReal32x3.vZ + ptParent[7];
    AIGraph_GetClosestNode(&igi2_frame.ptAIGraphNode, v16, &igi2_frame.tNewDest, false);
    if ( *(float *)&igi2_frame.ptAIGraphNode != 0.0 )
    {
      p_tQTaskChildren[1].ptTail = (struct QTask_s *)igi2_frame.ptAIGraphNode->tGraphNode.nID;
      igi2_frame.tOrderContext.eOrder = AISQUAD_ORDER_MOVE_TO_NODE;
      v17 = AISquad_GetOrderDelay((struct AISquad_s *)ptQTask);
      v18 = p_tQTaskChildren[1].ptTail;
      igi2_frame.tOrderContext.iDelay = v17;
      *(_QWORD *)&igi2_frame.tOrderContext.uContext.tWaitForLeapFrogContext.tTargetPosition.vX = (unsigned int)v18;
      HumanAIContent_ReceiveSquadOrder((struct HumanAI_s *)ptHead, &igi2_frame.tOrderContext);
    }
    p_tQTaskChildren[1].ptHead = (struct QTask_s *)1;
    return true;
  }
}

// source: j/0/humanai/aisquad.c:3850  [anchor-mhash]
enum bool __cdecl AISquad_SquadActionDangerInitHandler(
        struct QTask_s *ptQTask,
        struct AISquadActionChangeContext_s *ptActionChangeContext)
{
  int v2; // eax
  struct QTaskNodeList_s *p_tQTaskChildren; // eax

  v2 = 7 * (int)ptQTask[215].tQTaskChildren.ptHead;
  ptQTask[v2 + 181].ptPrev = nullptr;
  ptQTask[v2 + 181].tQTaskChildren.ptHead = nullptr;
  p_tQTaskChildren = &ptQTask[v2 + 180].tQTaskChildren;
  p_tQTaskChildren[2] = (*(struct QTaskNodeList_s *)&ptActionChangeContext->tToDangerContext.tDirection);
  qmemcpy(p_tQTaskChildren, &ptActionChangeContext->tToDangerContext, 0x18u);
  if ( ((int)ptQTask[215].tQTaskChildren.ptTail & 2) != 0 )
  {
    p_tQTaskChildren[3].ptHead = (struct QTask_s *)2;
    p_tQTaskChildren[3].ptMiddle = (struct QTask_s *)(-1 - (__int64)(*(float *)&ptQTask[217].eQTaskType * -30.0));
  }
  else
  {
    AISquad_MakeOneTeam(ptQTask);
    AISquad_ClearMembersPaths(ptQTask);
    AISquad_PopMembersActionStacks(ptQTask);
  }
  ptQTask[215].tQTaskChildren.ptTail = (struct QTask_s *)((int)ptQTask[215].tQTaskChildren.ptTail | 2);
  return true;
}

// source: j/0/humanai/aisquad.c:3899  [anchor-mhash]
enum bool __cdecl AISquad_SquadActionDangerRunHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct QTaskNodeList_s *v29; };
    struct { char igi2_o1[12]; int v30; };
    struct { char igi2_o2[16]; struct AISquadActionChangeContext_s v31; };
    char igi2_extent[232];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTaskNodeList_s *p_tQTaskChildren; // ebx
  struct QTask_s *ptPrev; // eax
  char *v3; // eax
  struct QTask_s *v4; // edx
  struct Game_s *v5; // eax
  struct QTask_s *v6; // edi
  struct HumanAI_s *v7; // edx
  BOOL v8; // ecx
  int *v9; // ebx
  void (__cdecl *pfRunCallback)(struct HumanAI_s *, struct HumanAIActionStackItem_s *); // eax
  bool v11; // zf
  int v12; // eax
  int v13; // esi
  int v14; // eax
  struct QTask_s *v16; // ecx
  struct QTaskNodeList_s *v17; // ebx
  struct QTask_s *ptMiddle; // edx
  struct QTask_s *v19; // eax
  struct QTask_s *ptParent; // edi
  int v21; // edx
  struct QTask_s *v22; // ebp
  struct QTask_s *v23; // eax
  struct QTask_s *v24; // ecx
  struct QTask_s *v25; // eax
  double v26; // st7
  struct QTask_s *ptHead; // eax
  struct QReference_s *ptTail; // edx

  p_tQTaskChildren = &ptQTask[7 * (int)ptQTask[215].tQTaskChildren.ptHead + 180].tQTaskChildren;
  ptPrev = ptQTask[7 * (int)ptQTask[215].tQTaskChildren.ptHead + 181].ptPrev;
  igi2_frame.v29 = p_tQTaskChildren;
  if ( !ptPrev )
  {
    if ( (double)(int)ptQTask[7 * (int)ptQTask[215].tQTaskChildren.ptHead + 181].tQTaskChildren.ptHead < 15.0 )
    {
      ++ptQTask[7 * (int)ptQTask[215].tQTaskChildren.ptHead + 181].tQTaskChildren.ptHead;
      return true;
    }
    ptQTask[7 * (int)ptQTask[215].tQTaskChildren.ptHead + 181].tQTaskChildren.ptHead = nullptr;
    p_tQTaskChildren[3].ptHead = (struct QTask_s *)1;
    AISquad_ClearMembersPaths(ptQTask);
    AISquad_PopMembersActionStacks(ptQTask);
    igi2_frame.v31.eNextAction = AISQUAD_ACTION_LOOK_SEARCH_IN_DIRECTION|AISQUAD_ACTION_MOVE;
    igi2_frame.v31.ePrevAction = AISquad_GetOrderDelay((struct AISquad_s *)ptQTask);
    ptHead = p_tQTaskChildren[2].ptHead;
    ptTail = (struct QReference_s *)p_tQTaskChildren[2].ptTail;
    HIDWORD(igi2_frame.v31.tToInquireContext.tPosition.vZ) = p_tQTaskChildren[2].ptMiddle;
    LODWORD(igi2_frame.v31.tToInquireContext.tPosition.vZ) = ptHead;
    igi2_frame.v31.tToInquireContext.ptReceiverRef = ptTail;
    qmemcpy(&igi2_frame.v31.tToPatrolContext, p_tQTaskChildren, 0x18u);
    AISquad_SendOrderToSquad(ptQTask, (struct AISquadOrderContext_s *)&igi2_frame.v31);
    return true;
  }
  v3 = &ptPrev[-1].isInMemPool + 1;
  if ( !v3 )
  {
    ptParent = ptQTask[1].ptParent;
    v21 = 0;
    if ( (int)ptParent <= 0 )
    {
LABEL_29:
      v26 = (double)((unsigned int)&ptQTask[7 * (int)ptQTask[215].tQTaskChildren.ptHead + 181].tQTaskChildren.ptHead->ptNext
                   + 1);
      ++p_tQTaskChildren[3].ptMiddle;
      if ( v26 > 30.0 )
      {
        p_tQTaskChildren[3].ptHead = (struct QTask_s *)2;
        p_tQTaskChildren[3].ptMiddle = nullptr;
        return true;
      }
    }
    else
    {
      v22 = ptQTask + 1;
      while ( 1 )
      {
        v23 = v22->ptNext->tQTaskChildren.ptHead;
        v24 = v23[6].ptParent;
        if ( v24->ptNext )
        {
          if ( v24 )
            break;
        }
        v25 = v23[118].ptParent;
        if ( v25->ptNext )
        {
          if ( v25
            && (void (__cdecl *)(struct HumanAI_s *, struct HumanAIActionStackItem_s *))v25->tQTaskRefList.ptMiddle == HumanAIContent_ActivateInitCB )
          {
            break;
          }
        }
        ++v21;
        v22 = (struct QTask_s *)((char *)v22 + 4);
        if ( v21 >= (int)ptParent )
          goto LABEL_29;
      }
    }
    return true;
  }
  if ( v3 != (char *)1 )
    return true;
  v4 = (struct QTask_s *)((char *)&ptQTask[7 * (int)ptQTask[215].tQTaskChildren.ptHead + 181].tQTaskChildren.ptHead->ptNext
                        + 1);
  ptQTask[7 * (int)ptQTask[215].tQTaskChildren.ptHead + 181].tQTaskChildren.ptHead = v4;
  if ( v4 != (struct QTask_s *)1 )
  {
    v16 = (struct QTask_s *)(__int64)(*(float *)&ptQTask[217].eQTaskType * 30.0);
    if ( v4 == v16 )
    {
      AISquad_PopMembersActionStacks(ptQTask);
      memset(&igi2_frame.v31.ePrevAction, 0, 12);
      *((_DWORD *)&igi2_frame.v31.tToInquireContext.ptReceiverRef + 1) = 0;
      igi2_frame.v31.eNextAction = AISQUAD_ACTION_PATROL|0x20;
      qmemcpy(&igi2_frame.v31.tToSearchContext, p_tQTaskChildren, sizeof(igi2_frame.v31.tToSearchContext));
      v17 = p_tQTaskChildren + 2;
      ptMiddle = v17->ptMiddle;
      v19 = v17->ptTail;
      LODWORD(igi2_frame.v31.tToMoveContext.tPosition.vX) = v17->ptHead;
      LODWORD(igi2_frame.v31.tToMoveContext.tPosition.vY) = v19;
      HIDWORD(igi2_frame.v31.tToMoveContext.tPosition.vX) = ptMiddle;
      AISquad_ReceiveEvent(ptQTask, (struct AISquadEventContext_s *)&igi2_frame.v31);
      return true;
    }
    if ( (int)v4 > (int)v16 )
    {
      AISquad_PopMembersActionStacks(ptQTask);
      igi2_frame.v31.eNextAction = AISQUAD_ACTION_IDLE;
      igi2_frame.v31.isPopMembersStacks = true;
      igi2_frame.v31.isDeserializing = false;
      AISquad_PopActionStack(ptQTask, &igi2_frame.v31);
      return false;
    }
    return true;
  }
  igi2_frame.v30 = 0;
  if ( (int)ptQTask[1].ptParent <= 0 )
    return true;
  v5 = Game_ptGame;
  v6 = ptQTask + 1;
  do
  {
    v7 = (struct HumanAI_s *)v6->ptNext->tQTaskChildren.ptHead;
    v5->tRunRandomState.anRandom[2] ^= v5->tRunRandomState.anRandom[0] >> 7;
    v5->tRunRandomState.anRandom[1] ^= v5->tRunRandomState.anRandom[2];
    v5->tRunRandomState.anRandom[0] += v5->tRunRandomState.anRandom[1];
    v8 = (v5->tRunRandomState.anRandom[0] & 1) == 0;
    if ( v7 )
    {
      v9 = (int *)&p_tQTaskChildren[2];
      igi2_frame.v31.tToPatrolContext.nPatrolPathId = *v9;
      *((_DWORD *)&igi2_frame.v31.tToPatrolContext + 1) = v9[1];
      LODWORD(igi2_frame.v31.tToInquireContext.tPosition.vX) = v9[2];
      pfRunCallback = v7->atActionStackItemList[0].pfRunCallback;
      v11 = *(_DWORD *)pfRunCallback == 0;
      igi2_frame.v31.eNextAction = AISQUAD_ACTION_DANGER|AISQUAD_ACTION_MOVE;
      igi2_frame.v31.ePrevAction = AISQUAD_ACTION_IDLE;
      if ( !v11 )
      {
        if ( pfRunCallback )
        {
          if ( *((void (__cdecl **)(struct HumanAI_s *, struct HumanAIActionStackItem_s *))pfRunCallback + 7) == HumanAIContent_TakeCoverRunCB )
          {
            v12 = *((_DWORD *)pfRunCallback + 12);
            v13 = *(_DWORD *)(v12 + 48);
            v14 = v12 + 8;
            if ( v13 )
            {
              if ( (*(_BYTE *)(v13 + 4 * *(_DWORD *)(v14 + 36) + 12) & 4) != 0 )
                v8 = 0;
            }
          }
        }
      }
      HIDWORD(igi2_frame.v31.tToInquireContext.tPosition.vX) = v8;
      HumanAIContent_ReceiveSquadOrder(v7, (struct AISquadOrderContext_s *)&igi2_frame.v31);
      v5 = Game_ptGame;
      p_tQTaskChildren = igi2_frame.v29;
    }
    v6 = (struct QTask_s *)((char *)v6 + 4);
    ++igi2_frame.v30;
  }
  while ( igi2_frame.v30 < (int)ptQTask[1].ptParent );
  return true;
}

// source: j/0/humanai/aisquad.c:4081  [size]
void __cdecl AISquad_GetSerializeParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = AISquad_ptSerializeParameterList;
}

// source: j/0/humanai/aisquad.c:4101  [anchor-mhash]
void __cdecl AISquad_DeSerializeHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *v2; // ebx
  int v3; // esi
  struct MemPoolFreeItem_s **p_tQTaskChildren; // edi
  struct MemPoolFreeItem_s *v5; // eax
  int ptPrev; // eax
  int v7; // edi
  struct QReference_s **p_ptParent; // esi
  bool v9; // zf
  void (__cdecl *pfHandler)(struct QTask_s *, struct QTask_s **); // eax
  bool v11; // cc
  struct QTask_s **v12; // esi
  struct QTask_s *v13; // eax
  int v14; // eax
  struct QReference_s *v15; // eax
  unsigned int v16; // eax
  struct QReference_s *v17; // eax
  struct QTask_s *pxObject; // eax
  int ptHead; // ecx

  v2 = ptQTask;
  AISquad_ClearActionStack(ptQTask, false, true);
  memset(AISQuad_anVoiceLastPlayedTickTable, 0, sizeof(AISQuad_anVoiceLastPlayedTickTable));
  v3 = 0;
  if ( (int)v2[215].tQTaskRefList.ptMiddle > 0 )
  {
    p_tQTaskChildren = (struct MemPoolFreeItem_s **)&v2[182].tQTaskChildren;
    do
    {
      v5 = *p_tQTaskChildren;
      if ( (*p_tQTaskChildren)->ptNext )
        v5 = (struct MemPoolFreeItem_s *)Node_Remove(v5);
      --QTask_tQTaskRefPool.nAllocatedBlocks;
      v5->ptNext = QTask_tQTaskRefPool.tMemPoolFreeList.ptHead;
      QTask_tQTaskRefPool.tMemPoolFreeList.ptHead = v5;
      ++v3;
      p_tQTaskChildren += 10;
    }
    while ( v3 < (int)v2[215].tQTaskRefList.ptMiddle );
  }
  ptPrev = (int)v2[216].ptPrev;
  v7 = 0;
  v2[215].tQTaskRefList.ptMiddle = nullptr;
  if ( ptPrev > 0 )
  {
    p_ptParent = (struct QReference_s **)&v2[216].ptParent;
    do
    {
      QTask_DeleteQTaskAndQTaskRefSafe(p_ptParent);
      ++v7;
      p_ptParent += 2;
    }
    while ( v7 < (int)v2[216].ptPrev );
  }
  v9 = *(_DWORD *)&v2[215].eQTaskType == 0;
  v2[216].ptPrev = nullptr;
  if ( !v9 )
  {
    do
      AISquad_RemoveLastEvent(v2);
    while ( *(_DWORD *)&v2[215].eQTaskType );
  }
  pfHandler = (void (__cdecl *)(struct QTask_s *, struct QTask_s **))QTask_aatQTaskFinalEvent[Serialize_eGetSerializeParameterListQTaskEvent][v2->eQTaskType].pfHandler;
  ptQTask = nullptr;
  if ( pfHandler )
  {
    pfHandler(v2, &ptQTask);
    if ( ptQTask )
      Serialize_ParseParameterList(v2, (struct DeSerializeContext_s *)pxContext, (struct ParameterList_s *)ptQTask);
  }
  v11 = (int)v2[215].tQTaskChildren.ptHead <= 0;
  ptQTask = nullptr;
  if ( !v11 )
  {
    v12 = &v2[193].ptParent;
    do
    {
      v13 = v12[2];
      v12[3] = nullptr;
      switch ( (unsigned int)v13 )
      {
        case 0u:
          *(v12 - 2) = (struct QTask_s *)AISquad_SquadActionIdleInitHandler;
          *(v12 - 1) = (struct QTask_s *)AISquad_SquadActionIdleRunHandler;
          goto LABEL_35;
        case 1u:
          *(v12 - 2) = (struct QTask_s *)AISquad_SquadActionHoldAreaInitHandler;
          *(v12 - 1) = (struct QTask_s *)AISquad_SquadActionHoldAreaRunHandler;
          goto LABEL_35;
        case 2u:
          *(v12 - 2) = (struct QTask_s *)AISquad_SquadActionInquireInitHandler;
          *(v12 - 1) = (struct QTask_s *)AISquad_SquadActionInquireRunHandler;
          goto LABEL_35;
        case 3u:
          *(v12 - 2) = (struct QTask_s *)AISquad_SquadActionSearchAreaInitHandler;
          *(v12 - 1) = (struct QTask_s *)AISquad_SquadActionSearchAreaRunHandler;
          goto LABEL_35;
        case 4u:
          v14 = (int)*(v12 - 65);
          *v12 = (struct QTask_s *)AISquad_SquadActionDefaultDeInitHandler;
          v12[1] = (struct QTask_s *)AISquad_SquadActionDefaultEventHandler;
          *(v12 - 2) = (struct QTask_s *)AISquad_SquadActionMoveInitHandler;
          *(v12 - 1) = (struct QTask_s *)AISquad_SquadActionMoveRunHandler;
          if ( v14 <= -1 )
          {
            *(v12 - 64) = nullptr;
          }
          else if ( v14 < 4096 && (v15 = Level_atLevelQTaskID[v14]) != nullptr )
          {
            *(v12 - 64) = (struct QTask_s *)v15->pxObject;
          }
          else
          {
            *(v12 - 64) = nullptr;
          }
          break;
        case 5u:
          v16 = (unsigned int)*(v12 - 62);
          *v12 = (struct QTask_s *)AISquad_SquadActionDefaultDeInitHandler;
          v12[1] = (struct QTask_s *)AISquad_SquadActionDefaultEventHandler;
          *(v12 - 2) = (struct QTask_s *)AISquad_SquadActionLeapFrogInitHandler;
          *(v12 - 1) = (struct QTask_s *)AISquad_SquadActionLeapFrogRunHandler;
          *(v12 - 60) = nullptr;
          if ( v16 < 0x1000 )
          {
            v17 = Level_atLevelQTaskID[v16];
            if ( v17 )
            {
              pxObject = (struct QTask_s *)v17->pxObject;
              if ( pxObject )
                *(v12 - 60) = (struct QTask_s *)QTask_NewQTaskRef(pxObject);
            }
          }
          break;
        case 6u:
          *(v12 - 2) = (struct QTask_s *)AISquad_SquadActionPatrolInitHandler;
          *(v12 - 1) = (struct QTask_s *)AISquad_SquadActionPatrolRunHandler;
          goto LABEL_35;
        case 7u:
          *(v12 - 2) = (struct QTask_s *)AISquad_SquadActionMoveSearchInDirectionInitHandler;
          *(v12 - 1) = (struct QTask_s *)AISquad_SquadActionMoveSearchInDirectionRunHandler;
          goto LABEL_35;
        case 8u:
          *(v12 - 2) = (struct QTask_s *)AISquad_SquadActionLookSearchInDirectionInitHandler;
          *(v12 - 1) = (struct QTask_s *)AISquad_SquadActionLookSearchInDirectionRunHandler;
          goto LABEL_35;
        case 9u:
          *(v12 - 2) = (struct QTask_s *)AISquad_SquadActionDangerInitHandler;
          *(v12 - 1) = (struct QTask_s *)AISquad_SquadActionDangerRunHandler;
LABEL_35:
          *v12 = (struct QTask_s *)AISquad_SquadActionDefaultDeInitHandler;
          v12[1] = (struct QTask_s *)AISquad_SquadActionDefaultEventHandler;
          break;
        default:
          break;
      }
      ptHead = (int)v2[215].tQTaskChildren.ptHead;
      v12 += 70;
      ptQTask = (struct QTask_s *)((char *)ptQTask + 1);
    }
    while ( (int)ptQTask < ptHead );
  }
  AISquad_BuildTeamFromChildren(v2);
}

// source: j/0/humanai/aisquad.c:4260  [anchor-mhash]
void __cdecl AISquad_SerializeHandler(struct QTask_s *ptQTask, void *pxContext)
{
  int v2; // edi
  struct QTask_s **p_ptParent; // esi
  struct QTask_s *v4; // eax
  bool v5; // zf
  struct QTask_s *ptHead; // edx
  int v7; // eax
  struct QReference_s *v8; // ecx
  void *v9; // edx
  int v10; // eax
  struct QReference_s *v11; // ecx

  v2 = 0;
  if ( (int)ptQTask[215].tQTaskChildren.ptHead > 0 )
  {
    p_ptParent = &ptQTask[187].ptParent;
    do
    {
      if ( p_ptParent[62] == (struct QTask_s *)4 )
      {
        v9 = *(p_ptParent - 4);
        if ( v9 )
        {
          v10 = 0;
          while ( 1 )
          {
            v11 = Level_atLevelQTaskID[v10];
            if ( v11 )
            {
              if ( v11->pxObject == v9 )
                break;
            }
            if ( ++v10 >= 4096 )
            {
              v10 = -1;
              break;
            }
          }
          *(p_ptParent - 5) = (struct QTask_s *)v10;
        }
        else
        {
          *(p_ptParent - 5) = (struct QTask_s *)-1;
        }
      }
      else if ( p_ptParent[62] == (struct QTask_s *)5 )
      {
        v4 = *p_ptParent;
        v5 = *p_ptParent == nullptr;
        *(p_ptParent - 2) = (struct QTask_s *)-1;
        if ( !v5 )
        {
          ptHead = v4->tQTaskChildren.ptHead;
          if ( ptHead )
          {
            v7 = 0;
            while ( 1 )
            {
              v8 = Level_atLevelQTaskID[v7];
              if ( v8 )
              {
                if ( v8->pxObject == ptHead )
                  break;
              }
              if ( ++v7 >= 4096 )
              {
                v7 = -1;
                break;
              }
            }
            *(p_ptParent - 2) = (struct QTask_s *)v7;
          }
        }
      }
      ++v2;
      p_ptParent += 70;
    }
    while ( v2 < (int)ptQTask[215].tQTaskChildren.ptHead );
  }
  Serialize_SerializeHandler(ptQTask, pxContext);
}

// source: j/0/humanai/aisquad.c:4320  [anchor-mhash]
void __cdecl AISquad_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  unsigned __int16 *p_eQTaskType; // edx
  int v3; // ebp

  QTaskList_Register(AISquad_ptQTaskList, (struct QTaskList_s *)ptQTask);
  BYTE2(ptQTask[218].ptNext) = 1;
  p_eQTaskType = &ptQTask[1].eQTaskType;
  v3 = 2;
  do
  {
    memset(p_eQTaskType - 18, 0, 0x20u);
    *(_DWORD *)p_eQTaskType = 1;
    p_eQTaskType += 20;
    --v3;
  }
  while ( v3 );
  ptQTask[218].tQTaskRefList.ptMiddle = (struct QReference_s *)60;
  ptQTask[215].tQTaskChildren.ptTail = nullptr;
  *(_DWORD *)&ptQTask[215].eQTaskType = 0;
  ptQTask[215].ptParent = nullptr;
  ptQTask[215].tQTaskRefList.ptTail = nullptr;
  ptQTask[215].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[216].ptNext = nullptr;
  LOBYTE(ptQTask[218].ptNext) = 0;
  BYTE1(ptQTask[218].ptNext) = 0;
  ptQTask[215].tQTaskRefList.ptHead = nullptr;
  ptQTask[217].ptParent = (struct QTask_s *)1084227584;
  *(_DWORD *)&ptQTask[217].eQTaskType = 1092616192;
  ptQTask[216].ptPrev = nullptr;
  ptQTask[216].tQTaskChildren.ptHead = nullptr;
  ptQTask[216].tQTaskChildren.ptTail = nullptr;
  ptQTask[216].tQTaskRefList.ptTail = nullptr;
  ptQTask[215].tQTaskChildren.ptHead = nullptr;
  ptQTask[218].ptPrev = (struct QTask_s *)1;
  ptQTask[218].tQTaskChildren.ptHead = (struct QTask_s *)-1;
  ptQTask[218].tQTaskChildren.ptMiddle = (struct QTask_s *)-1;
  ptQTask[218].tQTaskChildren.ptTail = (struct QTask_s *)-1;
  ptQTask[216].tQTaskChildren.ptMiddle = (struct QTask_s *)((int)ptQTask % 60);
  ptQTask[218].tQTaskRefList.ptHead = (struct QReference_s *)5;
  ptQTask[225].tQTaskChildren.ptTail = nullptr;
  ptQTask[218].tQTaskRefList.ptTail = (struct QReference_s *)0x40000000;
  ptQTask[218].ptParent = nullptr;
  LOBYTE(ptQTask[219].ptNext) = 0;
  *(_DWORD *)&ptQTask[218].eQTaskType = 1106247680;
  ptQTask[216].tQTaskRefList.ptHead = nullptr;
  ptQTask[216].tQTaskRefList.ptMiddle = nullptr;
}

// source: j/0/humanai/aisquad.c:4390  [anchor-caller]
void __cdecl AISquad_DeleteHandler(struct QTask_s *ptQTask)
{
  struct QTask_s **p_ptParent; // ebx
  int v3; // ebp
  struct MemPoolFreeItem_s **v4; // esi
  struct MemPoolFreeItem_s *v5; // eax
  struct QTask_s *ptTail; // eax
  int v7; // esi
  struct MemPoolFreeItem_s **p_tQTaskChildren; // ebp
  struct MemPoolFreeItem_s *v9; // eax
  int v10; // ecx
  struct QReference_s *v11; // eax
  void (__cdecl *pfHandler)(struct QTask_s *); // eax
  int ptQTaska = *(int *)&ptQTask; // [esp+14h] [ebp+4h] ARGSLOT

  AISquad_ClearPlayingSoundsList((struct AISquad_s *)ptQTask);
  if ( BYTE2(ptQTask[218].ptNext) )
  {
    QTaskList_Remove(AISquad_ptQTaskList, ptQTask);
    BYTE2(ptQTask[218].ptNext) = 0;
  }
  AISquad_ClearActionStack(ptQTask, true, false);
  p_ptParent = &ptQTask[1].ptParent;
  ptQTaska = 2;
  do
  {
    v3 = 0;
    if ( (int)*p_ptParent > 0 )
    {
      v4 = (struct MemPoolFreeItem_s **)(p_ptParent - 8);
      do
      {
        v5 = *v4;
        if ( *v4 )
        {
          if ( v5->ptNext )
            v5 = (struct MemPoolFreeItem_s *)Node_Remove(v5);
          --QTask_tQTaskRefPool.nAllocatedBlocks;
          v5->ptNext = QTask_tQTaskRefPool.tMemPoolFreeList.ptHead;
          QTask_tQTaskRefPool.tMemPoolFreeList.ptHead = v5;
        }
        ++v3;
        ++v4;
      }
      while ( v3 < (int)*p_ptParent );
    }
    p_ptParent += 10;
    --ptQTaska;
  }
  while ( ptQTaska );
  ptTail = ptQTask[225].tQTaskChildren.ptTail;
  if ( ptTail )
    Script_Delete((struct Script_s *)ptTail);
  v7 = 0;
  if ( (int)ptQTask[215].tQTaskRefList.ptMiddle > 0 )
  {
    p_tQTaskChildren = (struct MemPoolFreeItem_s **)&ptQTask[182].tQTaskChildren;
    do
    {
      v9 = *p_tQTaskChildren;
      if ( (*p_tQTaskChildren)->ptNext )
        v9 = (struct MemPoolFreeItem_s *)Node_Remove(v9);
      --QTask_tQTaskRefPool.nAllocatedBlocks;
      v9->ptNext = QTask_tQTaskRefPool.tMemPoolFreeList.ptHead;
      QTask_tQTaskRefPool.tMemPoolFreeList.ptHead = v9;
      ++v7;
      p_tQTaskChildren += 10;
    }
    while ( v7 < (int)ptQTask[215].tQTaskRefList.ptMiddle );
  }
  while ( *(_DWORD *)&ptQTask[215].eQTaskType )
    AISquad_RemoveLastEvent(ptQTask);
  v10 = 0;
  while ( 1 )
  {
    v11 = Level_atLevelQTaskID[v10];
    if ( v11 )
    {
      if ( v11->pxObject == ptQTask )
        break;
    }
    if ( ++v10 >= 4096 )
      goto LABEL_29;
  }
  if ( v10 >= 0 )
  {
    pfHandler = (void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[Level_eRemoveLevelScriptSymbolsEvent][ptQTask->eQTaskType].pfHandler;
    if ( pfHandler )
      pfHandler(ptQTask);
  }
LABEL_29:
  memset(AISQuad_anVoiceLastPlayedTickTable, 0, sizeof(AISQuad_anVoiceLastPlayedTickTable));
}

// source: j/0/humanai/aisquad.c:4453  [size]
void __cdecl AISquad_UpdateAttachmentHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptHead; // ecx
  int v2; // edx
  struct QTask_s *v3; // eax
  int v4; // esi
  void (__cdecl *pfHandler)(struct QTask_s *); // eax
  int v6; // edx

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
      v4 = Attach_eUpdateAttachmentEvent;
      QTask_atProtectedQTaskStack[v2].ptQTask = v3;
      pfHandler = (void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[v4][ptHead->eQTaskType].pfHandler;
      v6 = v2 + 1;
      QTask_nProtectedQTaskStackOffset = v6;
      if ( pfHandler )
      {
        pfHandler(ptHead);
        v6 = QTask_nProtectedQTaskStackOffset;
      }
      ptHead = (struct QTask_s *)dword_849C7DC[v6];
      v2 = v6 - 1;
      QTask_nProtectedQTaskStackOffset = v2;
    }
    while ( ptHead );
  }
}

// source: j/0/humanai/aisquad.c:4466  [anchor-callee]
void __cdecl AISquad_SendSquadCombatIdleEvent(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { int iT; };
    struct { char igi2_o1[4]; struct QTask_s **v10; };
    struct { char igi2_o2[8]; struct HumanAIEventContext_t tEvent; };
    char igi2_extent[72];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *v1; // eax
  struct QTask_s **p_ptParent; // ecx
  int v3; // ebp
  struct QTask_s **v4; // ebx
  struct QTask_s *ptHead; // esi
  struct QTask_s *ptParent; // eax
  __int16 v7; // ax
  bool v8; // cc

  v1 = ptQTask;
  igi2_frame.iT = 0;
  if ( (int)ptQTask[215].tQTaskRefList.ptTail > 0 )
  {
    p_ptParent = &ptQTask[1].ptParent;
    igi2_frame.v10 = &ptQTask[1].ptParent;
    do
    {
      v3 = 0;
      if ( (int)*p_ptParent > 0 )
      {
        v4 = p_ptParent - 8;
        do
        {
          if ( *v4 )
          {
            ptHead = (*v4)->tQTaskChildren.ptHead;
            if ( ptHead )
            {
              ptParent = ptHead[118].ptParent;
              if ( !ptParent->ptNext
                || !ptParent
                || (void (__cdecl *)(struct HumanAI_s *, struct HumanAIActionStackItem_s *))ptParent->tQTaskRefList.ptMiddle != HumanAIContent_CombatIdleInitCB )
              {
                v7 = HumanAI_eSendEventQTaskEvent;
                igi2_frame.tEvent.eEvent = 30;
                memset(&igi2_frame.tEvent.eTeam, 0, 16);
                igi2_frame.tEvent.ptHumanOriginatorQTask = nullptr;
                igi2_frame.tEvent.ptReferenceQTask = nullptr;
                if ( HumanAI_eSendEventQTaskEvent == 512 )
                {
                  v7 = QTask_NewQTaskEventFn(0, "HumanAISendEvent");
                  HumanAI_eSendEventQTaskEvent = v7;
                }
                ((void (__cdecl *)(struct QTask_s *, struct HumanAIEventContext_t *))QTask_aatQTaskFinalEvent[v7][ptHead->eQTaskType].pfHandler)(
                  ptHead,
                  &igi2_frame.tEvent);
                p_ptParent = igi2_frame.v10;
              }
            }
          }
          ++v3;
          ++v4;
        }
        while ( v3 < (int)*p_ptParent );
        v1 = ptQTask;
      }
      p_ptParent += 10;
      v8 = ++igi2_frame.iT < (int)v1[215].tQTaskRefList.ptTail;
      igi2_frame.v10 = p_ptParent;
    }
    while ( v8 );
  }
}

// source: j/0/humanai/aisquad.c:4673  [anchor-callee]
struct QTask_s *__cdecl AISquad_PushIdleOntoActionStack(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct AISquadAction_s tAction; };
    struct { char igi2_o1[280]; struct AISquadActionChangeContext_s tActionChangeContext; };
    char igi2_extent[500];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *ptHead; // ecx
  int v2; // ecx

  igi2_frame.tAction.eAction = AISQUAD_ACTION_IDLE;
  igi2_frame.tAction.ptSwitchStateSoundQTaskRef = nullptr;
  igi2_frame.tActionChangeContext.eNextAction = AISQUAD_ACTION_IDLE;
  igi2_frame.tActionChangeContext.isDeserializing = false;
  ptHead = ptQTask[215].tQTaskChildren.ptHead;
  igi2_frame.tAction.pfDeInitHandler = AISquad_SquadActionDefaultDeInitHandler;
  igi2_frame.tAction.pfEventHandler = AISquad_SquadActionDefaultEventHandler;
  igi2_frame.tAction.pfInitHandler = AISquad_SquadActionIdleInitHandler;
  igi2_frame.tAction.pfRunHandler = (enum bool (__cdecl *)(struct QTask_s *))AISquad_SquadActionIdleRunHandler;
  igi2_frame.tActionChangeContext.isPopMembersStacks = true;
  if ( (int)ptHead < 4 )
  {
    qmemcpy(&ptQTask[7 * (int)ptHead + 187].tQTaskChildren, &igi2_frame.tAction, 0x118u);
    v2 = 7 * (int)++*(int *)&ptQTask[215].tQTaskChildren.ptHead;
    return ((struct QTask_s *(__cdecl *)(struct QTask_s *, struct AISquadActionChangeContext_s *))ptQTask[v2 + 186].tQTaskRefList.ptMiddle)(
             ptQTask,
             &igi2_frame.tActionChangeContext);
  }
  return ptQTask;
}

// source: j/0/humanai/aisquad.c:4707  [anchor-caller]
void __cdecl AISquad_RunHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptHead; // ecx
  int v2; // edx
  struct QTask_s *v3; // eax
  void (__cdecl *pfHandler)(struct QTask_s *); // eax
  int v5; // edx
  struct QTask_s *v6; // ecx
  int v7; // edx
  struct QTask_s *v8; // eax
  void (__cdecl *v9)(struct QTask_s *); // eax
  int v10; // edx

  AISquad_UpdateMemberCount(ptQTask);
  AISquad_MaintainPlayingSounds((struct AISquad_s *)ptQTask);
  if ( BYTE1(ptQTask[218].ptNext) )
  {
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
  else
  {
    if ( !ptQTask[215].tQTaskChildren.ptHead )
      AISquad_PushIdleOntoActionStack(ptQTask);
    AISquad_MaintainMisc(ptQTask);
    AISquad_SendFireOrder(ptQTask);
    AISquad_MaintainTargetList(ptQTask);
    if ( (int)ptQTask[215].tQTaskRefList.ptMiddle > 0 )
      AISquad_SendSquadCombatIdleEvent(ptQTask);
    if ( *(int *)&ptQTask[215].eQTaskType > 0 )
      (*(void (__cdecl **)(struct QTask_s *))&ptQTask[7 * (int)ptQTask[215].tQTaskChildren.ptHead + 186].eQTaskType)(ptQTask);
    if ( !ptQTask[215].tQTaskChildren.ptHead )
      AISquad_PushIdleOntoActionStack(ptQTask);
    AISquad_RunActionStack(ptQTask);
    v6 = ptQTask->tQTaskChildren.ptHead;
    if ( v6->ptNext && v6 )
    {
      v7 = QTask_nProtectedQTaskStackOffset;
      do
      {
        if ( v6->ptNext )
          v8 = v6->ptNext->ptNext != nullptr ? v6->ptNext : nullptr;
        else
          v8 = nullptr;
        QTask_atProtectedQTaskStack[v7].ptQTask = v8;
        v9 = (void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[1][v6->eQTaskType].pfHandler;
        v10 = v7 + 1;
        QTask_nProtectedQTaskStackOffset = v10;
        if ( v9 )
        {
          v9(v6);
          v10 = QTask_nProtectedQTaskStackOffset;
        }
        v6 = (struct QTask_s *)dword_849C7DC[v10];
        v7 = v10 - 1;
        QTask_nProtectedQTaskStackOffset = v7;
      }
      while ( v6 );
    }
  }
}

// source: j/0/humanai/aisquad.c:4771  [anchor-mhash]
void __cdecl AISquad_ClearTeams(struct QTask_s *ptQTask)
{
  struct QTask_s **p_ptParent; // esi
  int v2; // ebp
  int v3; // ebx
  struct MemPoolFreeItem_s **v4; // edi
  struct MemPoolFreeItem_s *v5; // eax

  p_ptParent = &ptQTask[1].ptParent;
  v2 = 2;
  do
  {
    v3 = 0;
    if ( (int)*p_ptParent > 0 )
    {
      v4 = (struct MemPoolFreeItem_s **)(p_ptParent - 8);
      do
      {
        v5 = *v4;
        if ( *v4 )
        {
          if ( v5->ptNext )
            v5 = (struct MemPoolFreeItem_s *)Node_Remove(v5);
          --QTask_tQTaskRefPool.nAllocatedBlocks;
          v5->ptNext = QTask_tQTaskRefPool.tMemPoolFreeList.ptHead;
          QTask_tQTaskRefPool.tMemPoolFreeList.ptHead = v5;
        }
        ++v3;
        ++v4;
      }
      while ( v3 < (int)*p_ptParent );
    }
    *p_ptParent = nullptr;
    p_ptParent += 10;
    --v2;
  }
  while ( v2 );
  ptQTask[215].tQTaskRefList.ptTail = nullptr;
}

// source: j/0/humanai/aisquad.c:4805  [anchor-mhash]
void __cdecl AISquad_BuildTeamFromChildren(struct QTask_s *ptQTask)
{
  int v1; // edi
  struct QTask_s *FirstChildOfType; // esi
  struct QTask_s *v3; // ebx
  struct QTask_s *v4; // eax

  AISquad_ClearTeams(ptQTask);
  v1 = 0;
  FirstChildOfType = QTask_GetFirstChildOfType(ptQTask, HumanSoldier_eQTaskType);
  ptQTask[1].ptParent = nullptr;
  if ( FirstChildOfType )
  {
    v3 = ptQTask + 1;
    do
    {
      if ( v1 >= 8 )
        break;
      v4 = QTask_GetFirstChildOfType(FirstChildOfType, HumanAI_eQTaskType);
      if ( v4 )
      {
        v3->ptNext = (struct QTask_s *)QTask_NewQTaskRef(v4);
        ++v1;
        v3 = (struct QTask_s *)((char *)v3 + 4);
      }
      FirstChildOfType = QTask_GetNextSiblingOfType(FirstChildOfType, HumanSoldier_eQTaskType);
    }
    while ( FirstChildOfType );
  }
  ptQTask[1].ptParent = (struct QTask_s *)v1;
  ptQTask[215].tQTaskRefList.ptTail = (struct QReference_s *)(v1 > 0);
}

// source: j/0/humanai/aisquad.c:4871  [anchor-mhash]
void __cdecl AISquad_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *ptTail; // eax
  int v3; // ecx
  struct QReference_s *v4; // eax
  int v5; // eax
  struct QReference_s *v6; // ecx
  char *v7; // eax
  char v8; // cl
  char zFilename[260]; // [esp+8h] [ebp-104h] BYREF

  ptTail = ptQTask[225].tQTaskChildren.ptTail;
  if ( ptTail )
  {
    Script_Delete((struct Script_s *)ptTail);
    ptQTask[225].tQTaskChildren.ptTail = nullptr;
  }
  v3 = 0;
  while ( 1 )
  {
    v4 = Level_atLevelQTaskID[v3];
    if ( v4 )
    {
      if ( v4->pxObject == ptQTask )
        break;
    }
    if ( ++v3 >= 4096 )
      goto LABEL_17;
  }
  if ( v3 != -1 )
  {
    v5 = 0;
    while ( 1 )
    {
      v6 = Level_atLevelQTaskID[v5];
      if ( v6 )
      {
        if ( v6->pxObject == ptQTask )
          break;
      }
      if ( ++v5 >= 4096 )
      {
        v5 = -1;
        break;
      }
    }
    sprintf(zFilename, "MISSION:AI/Squad_%d.qsc", v5);
    v7 = zFilename;
    do
    {
      v8 = *v7;
      v7[(char *)ptQTask - zFilename + 8760] = *v7;
      ++v7;
    }
    while ( v8 );
    ptQTask[225].tQTaskChildren.ptTail = (struct QTask_s *)Script_New(zFilename);
  }
LABEL_17:
  if ( *(float *)&ptQTask[218].tQTaskRefList.ptTail >= 0.0 )
  {
    if ( *(float *)&ptQTask[218].tQTaskRefList.ptTail <= 10.0 )
      ptQTask[218].tQTaskRefList.ptTail = ptQTask[218].tQTaskRefList.ptTail;
    else
      ptQTask[218].tQTaskRefList.ptTail = (struct QReference_s *)1092616192;
  }
  else
  {
    ptQTask[218].tQTaskRefList.ptTail = nullptr;
  }
}

void __cdecl sub_4A3570(struct QTask_s *ptQTask)
{
  struct QTask_s *v1; // eax
  struct QTask_s **v2; // edx

  AISquad_BuildTeamFromChildren(ptQTask);
  v1 = nullptr;
  if ( AISquad_ptQTaskList->nTask <= 0 )
  {
LABEL_5:
    v1 = nullptr;
  }
  else
  {
    v2 = AISquad_ptQTaskList->ptQTask;
    while ( *v2 != ptQTask )
    {
      v1 = (struct QTask_s *)((char *)v1 + 1);
      ++v2;
      if ( (int)v1 >= AISquad_ptQTaskList->nTask )
        goto LABEL_5;
    }
  }
  ptQTask[216].tQTaskChildren.ptTail = v1;
}

// source: j/0/humanai/aisquad.c:4937  [size]
void __cdecl AISquad_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = AISquad_ptParameterList;
}

// source: j/0/humanai/aisquad.c:4953  [size]
void __cdecl AISquad_ParentChangedHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *ptHead; // ecx
  int v3; // edx
  struct QTask_s *v4; // eax
  void (__cdecl *pfHandler)(struct QTask_s *, _DWORD); // eax
  int v6; // edx

  ptHead = ptQTask->tQTaskChildren.ptHead;
  if ( ptHead->ptNext && ptHead )
  {
    v3 = QTask_nProtectedQTaskStackOffset;
    do
    {
      if ( ptHead->ptNext )
        v4 = ptHead->ptNext->ptNext != nullptr ? ptHead->ptNext : nullptr;
      else
        v4 = nullptr;
      QTask_atProtectedQTaskStack[v3].ptQTask = v4;
      pfHandler = (void (__cdecl *)(struct QTask_s *, _DWORD))QTask_aatQTaskFinalEvent[4][ptHead->eQTaskType].pfHandler;
      v6 = v3 + 1;
      QTask_nProtectedQTaskStackOffset = v6;
      if ( pfHandler )
      {
        pfHandler(ptHead, 0);
        v6 = QTask_nProtectedQTaskStackOffset;
      }
      ptHead = (struct QTask_s *)dword_849C7DC[v6];
      v3 = v6 - 1;
      QTask_nProtectedQTaskStackOffset = v3;
    }
    while ( ptHead );
  }
}

// source: j/0/humanai/aisquad.c:4970  [anchor-mhash]
struct Result_s *__cdecl AISquad_SF_GetStateCB(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  int nNumActions; // eax
  struct Result_s *result; // eax
  struct Result_s Rs; // [esp+Ch] [ebp-18h] BYREF

  nNumActions = AISquad_ptCurrentAISquad->tActionStack.nNumActions;
  Rs.zResult = (char *)&g_zInitialValue;
  if ( nNumActions <= 0 )
  {
    result = retstr;
    Rs.nResult = 0;
    Rs.vResult = 0.0;
  }
  else
  {
    Rs.nResult = AISquad_ptCurrentAISquad->atEnemyTarget[7 * nNumActions + 4].nTimer;
    result = retstr;
    Rs.vResult = (double)Rs.nResult;
  }
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return result;
}

// source: j/0/humanai/aisquad.c:4995  [anchor-mhash]
struct Result_s *__cdecl AISquad_SF_GetEventCB(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  int nNumReceivedEvents; // eax
  int *v4; // eax
  double v5; // st7
  struct Result_s Rs; // [esp+Ch] [ebp-18h] BYREF

  nNumReceivedEvents = AISquad_ptCurrentAISquad->nNumReceivedEvents;
  if ( nNumReceivedEvents > 0
    && (v4 = (int *)((char *)&AISquad_ptCurrentAISquad->tQTask.tQTaskChildren + 112 * nNumReceivedEvents)) != nullptr )
  {
    v5 = (double)*v4;
    Rs.nResult = *v4;
    Rs.vResult = v5;
  }
  else
  {
    Rs.nResult = -1;
    Rs.vResult = -1.0;
  }
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/humanai/aisquad.c:5020  [anchor-mhash]
struct Result_s *__cdecl AISquad_SF_SwitchStateCB(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  #pragma pack(push, 1)
  union
  {
    struct { _DWORD v9[6]; };
    struct { char igi2_o1[24]; struct AISquadAction_s v10; };
    struct { char igi2_o2[304]; struct AISquadActionChangeContext_s ptQTask; };
    char igi2_extent[520];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int nArguments; // eax
  int v4; // esi
  struct QTask_s *pxObject; // eax
  struct QTask_s *v6; // eax
  enum AISquadActions_e v7; // esi

  nArguments = ptArgList->nArguments;
  if ( ptArgList->nArguments >= 1 && nArguments <= 2 )
  {
    igi2_frame.v10.ptSwitchStateSoundQTaskRef = nullptr;
    if ( nArguments == 2 )
    {
      v4 = Script_EvalArgInt(ptArgList, 1);
      if ( Script_EvalArgInt(ptArgList, 0) == 2 )
        AISQuad_anVoiceLastPlayedTickTable[v4] = 0;
      if ( AISquad_ptCurrentAISquad->atTeam[0].nMembers )
        pxObject = (struct QTask_s *)AISquad_ptCurrentAISquad->atTeam[0].aptMemberRef[0]->pxObject;
      else
        pxObject = nullptr;
      v6 = AISquad_SelectAndPlaySoundAtMembersPos(AISquad_ptCurrentAISquad, v4, pxObject);
      if ( v6 )
        igi2_frame.v10.ptSwitchStateSoundQTaskRef = QTask_NewQTaskRef(v6);
    }
    v7 = Script_EvalArgInt(ptArgList, 0);
    igi2_frame.ptQTask.eNextAction = v7;
    igi2_frame.ptQTask.isPopMembersStacks = true;
    igi2_frame.ptQTask.isDeserializing = false;
    AISquad_PopActionStack(&AISquad_ptCurrentAISquad->tQTask, &igi2_frame.ptQTask);
    AISquad_ClearActionStack(&AISquad_ptCurrentAISquad->tQTask, true, false);
    switch ( v7 )
    {
      case AISQUAD_ACTION_IDLE:
        igi2_frame.v10.eAction = AISQUAD_ACTION_IDLE;
        igi2_frame.v10.pfInitHandler = AISquad_SquadActionIdleInitHandler;
        igi2_frame.v10.pfRunHandler = (enum bool (__cdecl *)(struct QTask_s *))AISquad_SquadActionIdleRunHandler;
        goto LABEL_21;
      case AISQUAD_ACTION_HOLD_AREA:
        igi2_frame.v10.eAction = AISQUAD_ACTION_HOLD_AREA;
        igi2_frame.v10.pfInitHandler = AISquad_SquadActionHoldAreaInitHandler;
        igi2_frame.v10.pfRunHandler = AISquad_SquadActionHoldAreaRunHandler;
        goto LABEL_21;
      case AISQUAD_ACTION_INQUIRE:
        igi2_frame.v10.eAction = AISQUAD_ACTION_INQUIRE;
        igi2_frame.v10.pfInitHandler = AISquad_SquadActionInquireInitHandler;
        igi2_frame.v10.pfRunHandler = AISquad_SquadActionInquireRunHandler;
        goto LABEL_21;
      case AISQUAD_ACTION_SEARCH_AREA:
        igi2_frame.v10.eAction = AISQUAD_ACTION_SEARCH_AREA;
        igi2_frame.v10.pfInitHandler = AISquad_SquadActionSearchAreaInitHandler;
        igi2_frame.v10.pfRunHandler = AISquad_SquadActionSearchAreaRunHandler;
        goto LABEL_21;
      case AISQUAD_ACTION_MOVE:
        igi2_frame.v10.eAction = AISQUAD_ACTION_MOVE;
        igi2_frame.v10.pfInitHandler = AISquad_SquadActionMoveInitHandler;
        igi2_frame.v10.pfRunHandler = AISquad_SquadActionMoveRunHandler;
        goto LABEL_21;
      case AISQUAD_ACTION_LEAPFROG:
        igi2_frame.v10.eAction = AISQUAD_ACTION_LEAPFROG;
        igi2_frame.v10.pfInitHandler = AISquad_SquadActionLeapFrogInitHandler;
        igi2_frame.v10.pfRunHandler = AISquad_SquadActionLeapFrogRunHandler;
        goto LABEL_21;
      case AISQUAD_ACTION_MOVE_SEARCH_IN_DIRECTION:
        igi2_frame.v10.eAction = AISQUAD_ACTION_MOVE_SEARCH_IN_DIRECTION;
        igi2_frame.v10.pfInitHandler = AISquad_SquadActionMoveSearchInDirectionInitHandler;
        igi2_frame.v10.pfRunHandler = AISquad_SquadActionMoveSearchInDirectionRunHandler;
        goto LABEL_21;
      case AISQUAD_ACTION_LOOK_SEARCH_IN_DIRECTION:
        igi2_frame.v10.eAction = AISQUAD_ACTION_LOOK_SEARCH_IN_DIRECTION;
        igi2_frame.v10.pfInitHandler = AISquad_SquadActionLookSearchInDirectionInitHandler;
        igi2_frame.v10.pfRunHandler = AISquad_SquadActionLookSearchInDirectionRunHandler;
        goto LABEL_21;
      case AISQUAD_ACTION_DANGER:
        igi2_frame.v10.eAction = AISQUAD_ACTION_DANGER;
        igi2_frame.v10.pfInitHandler = AISquad_SquadActionDangerInitHandler;
        igi2_frame.v10.pfRunHandler = AISquad_SquadActionDangerRunHandler;
LABEL_21:
        igi2_frame.v10.pfDeInitHandler = AISquad_SquadActionDefaultDeInitHandler;
        igi2_frame.v10.pfEventHandler = AISquad_SquadActionDefaultEventHandler;
        AISquad_PushOntoActionStack(&AISquad_ptCurrentAISquad->tQTask, &igi2_frame.v10, &igi2_frame.ptQTask);
        break;
      default:
        break;
    }
  }
  igi2_frame.v9[4] = &g_zInitialValue;
  igi2_frame.v9[3] = 1072693248;
  igi2_frame.v9[2] = 0;
  igi2_frame.v9[0] = 1;
  qmemcpy(retstr, igi2_frame.v9, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/humanai/aisquad.c:5205  [size]
struct Result_s *__cdecl AISquad_SF_GetSquadTypeCB(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  Rs.nResult = AISquad_ptCurrentAISquad->tEditVariables.nTargetTimeout;
  Rs.vResult = (double)Rs.nResult;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/humanai/aisquad.c:5219  [anchor-mhash]
struct Result_s *__cdecl AISquad_SF_HasTargetCB(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  int nNumTargets; // ecx
  struct Result_s *result; // eax
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  nNumTargets = AISquad_ptCurrentAISquad->nNumTargets;
  result = retstr;
  Rs.zResult = (char *)&g_zInitialValue;
  LODWORD(Rs.vResult) = 0;
  if ( nNumTargets <= 0 )
  {
    Rs.nResult = 0;
    HIDWORD(Rs.vResult) = 0;
  }
  else
  {
    Rs.nResult = 1;
    HIDWORD(Rs.vResult) = 1072693248;
  }
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return result;
}

// source: j/0/humanai/aisquad.c:5239  [anchor-mhash]
struct Result_s *__cdecl AISquad_SF_ReceiverLookAtEventCB(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  #pragma pack(push, 1)
  union
  {
    struct { char *v13; };
    struct { char igi2_o1[4]; int v14; };
    struct { char igi2_o2[8]; _DWORD v15[6]; };
    struct { char igi2_o3[32]; struct AISquadOrderContext_s ptSquadOrder; };
    char igi2_extent[88];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct AISquad_s *v3; // eax
  int nNumReceivedEvents; // ebp
  char *v5; // ebp
  struct HumanAI_s *v6; // ebx
  int nAnimationMinimumDelay; // ecx
  int v8; // esi
  int v9; // eax
  int *v10; // edx
  bool v11; // cc

  v3 = AISquad_ptCurrentAISquad;
  nNumReceivedEvents = AISquad_ptCurrentAISquad->nNumReceivedEvents;
  if ( nNumReceivedEvents <= 0 )
    v5 = nullptr;
  else
    v5 = (char *)&AISquad_ptCurrentAISquad->tQTask.tQTaskChildren + 112 * nNumReceivedEvents;
  igi2_frame.v14 = 0;
  if ( *((int *)v5 + 2) > 0 )
  {
    igi2_frame.v13 = v5 + 12;
    do
    {
      v6 = *(struct HumanAI_s **)(*(_DWORD *)igi2_frame.v13 + 8);
      if ( v6 )
      {
        igi2_frame.ptSquadOrder.eOrder = AISQUAD_ORDER_LOOK_AT_EVENT;
        igi2_frame.ptSquadOrder.iDelay = AISquad_GetOrderDelay(v3);
        qmemcpy(&igi2_frame.ptSquadOrder.uContext, v5 + 48, 0x18u);
        nAnimationMinimumDelay = v6->nAnimationMinimumDelay;
        v8 = -1;
        v9 = 0;
        if ( nAnimationMinimumDelay > 0 )
        {
          v10 = &v6->anEventPriorityList[6];
          while ( *v10 != 46 )
          {
            ++v9;
            ++v10;
            if ( v9 >= nAnimationMinimumDelay )
              goto LABEL_13;
          }
          v8 = v9;
        }
LABEL_13:
        igi2_frame.ptSquadOrder.uContext.tLookInApproxDirectionOrderContext.nTimer = v8;
        HumanAIContent_ReceiveSquadOrder(v6, &igi2_frame.ptSquadOrder);
        v3 = AISquad_ptCurrentAISquad;
      }
      v11 = ++igi2_frame.v14 < (int)(*((_DWORD *)v5 + 2));
      igi2_frame.v13 += 4;
    }
    while ( v11 );
  }
  igi2_frame.v15[0] = 1;
  igi2_frame.v15[2] = 0;
  igi2_frame.v15[3] = 1072693248;
  igi2_frame.v15[4] = &g_zInitialValue;
  qmemcpy(retstr, igi2_frame.v15, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/humanai/aisquad.c:5280  [anchor-mhash]
struct Result_s *__cdecl AISquad_SF_ReceiverLookInApproxEventDirectionCB(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  #pragma pack(push, 1)
  union
  {
    struct { char *v13; };
    struct { char igi2_o1[4]; int v14; };
    struct { char igi2_o2[8]; _DWORD v15[6]; };
    struct { char igi2_o3[32]; struct AISquadOrderContext_s ptSquadOrder; };
    char igi2_extent[88];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct AISquad_s *v3; // eax
  int nNumReceivedEvents; // ebp
  char *v5; // ebp
  struct HumanAI_s *v6; // ebx
  int nAnimationMinimumDelay; // eax
  float v8; // esi
  float v9; // ecx
  int *v10; // edx
  bool v11; // cc

  v3 = AISquad_ptCurrentAISquad;
  nNumReceivedEvents = AISquad_ptCurrentAISquad->nNumReceivedEvents;
  if ( nNumReceivedEvents <= 0 )
    v5 = nullptr;
  else
    v5 = (char *)&AISquad_ptCurrentAISquad->tQTask.tQTaskChildren + 112 * nNumReceivedEvents;
  igi2_frame.v14 = 0;
  if ( *((int *)v5 + 2) > 0 )
  {
    igi2_frame.v13 = v5 + 12;
    do
    {
      v6 = *(struct HumanAI_s **)(*(_DWORD *)igi2_frame.v13 + 8);
      if ( v6 )
      {
        igi2_frame.ptSquadOrder.eOrder = AISQUAD_ORDER_LOOK_IN_APPROX_DIRECTION;
        igi2_frame.ptSquadOrder.iDelay = AISquad_GetOrderDelay(v3);
        nAnimationMinimumDelay = v6->nAnimationMinimumDelay;
        qmemcpy(&igi2_frame.ptSquadOrder.uContext, v5 + 48, 0x18u);
        v8 = IGI2_FLOAT_BITS(0xffffffffu);
        v9 = 0.0;
        *(_QWORD *)&igi2_frame.ptSquadOrder.uContext.tHoldAreaContext.tPosition.vY = 0x6000001C2LL;
        if ( nAnimationMinimumDelay > 0 )
        {
          v10 = &v6->anEventPriorityList[6];
          while ( *v10 != 46 )
          {
            ++LODWORD(v9);
            ++v10;
            if ( SLODWORD(v9) >= nAnimationMinimumDelay )
              goto LABEL_13;
          }
          v8 = v9;
        }
LABEL_13:
        igi2_frame.ptSquadOrder.uContext.tTakeCoverOrderContext.tDirection.vZ = v8;
        HumanAIContent_ReceiveSquadOrder(v6, &igi2_frame.ptSquadOrder);
        v3 = AISquad_ptCurrentAISquad;
      }
      v11 = ++igi2_frame.v14 < (int)(*((_DWORD *)v5 + 2));
      igi2_frame.v13 += 4;
    }
    while ( v11 );
  }
  igi2_frame.v15[0] = 1;
  igi2_frame.v15[2] = 0;
  igi2_frame.v15[3] = 1072693248;
  igi2_frame.v15[4] = &g_zInitialValue;
  qmemcpy(retstr, igi2_frame.v15, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/humanai/aisquad.c:5325  [anchor-caller]
struct Result_s *__cdecl AISquad_SF_TriggerAlarmCB(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct HumanAI_s *ptClosestHumanAI; };
    struct { char igi2_o1[4]; float vClosestDist; };
    struct { char igi2_o2[8]; int v26; };
    struct { char igi2_o3[12]; struct AISquad_s *ptAISquad; };
    struct { char igi2_o4[16]; struct Result_s Rs; };
    struct { char igi2_o5[40]; struct real64x3_t tAlarmTriggerPos; };
    struct { char igi2_o6[64]; struct AISquadOrderContext_s tOrderContext; };
    char igi2_extent[120];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct AISquad_s *v3; // ebx
  unsigned int nTenseTimeout; // ecx
  int vFormationDistance_low; // eax
  struct QReference_s *v6; // ecx
  _DWORD *pxObject; // ecx
  struct QTask_s *QTaskFromLevelQTaskID; // eax
  int nMembers; // esi
  int *p_nMembers; // edi
  struct AISquadTeam_s *atTeam; // edx
  void *v12; // ecx
  double *v13; // eax
  long double v14; // st4
  int v15; // eax
  struct AISquadTeam_s *v16; // esi
  struct AISquadTeam_s *v17; // edx
  struct HumanAI_s *v18; // ecx
  struct QReference_s *v19; // ecx
  void (__cdecl *pfRunCallback)(struct HumanAI_s *, struct HumanAIActionStackItem_s *); // eax
  int v21; // eax
  struct QTask_s *v22; // edi

  v3 = AISquad_ptCurrentAISquad;
  nTenseTimeout = AISquad_ptCurrentAISquad->tEditVariables.nTenseTimeout;
  igi2_frame.ptClosestHumanAI = nullptr;
  igi2_frame.vClosestDist = 0.0;
  igi2_frame.ptAISquad = AISquad_ptCurrentAISquad;
  if ( nTenseTimeout != -1 )
  {
    vFormationDistance_low = LODWORD(AISquad_ptCurrentAISquad->tEditVariables.vFormationDistance);
    if ( vFormationDistance_low != -1 && nTenseTimeout < 0x1000 )
    {
      v6 = Level_atLevelQTaskID[nTenseTimeout];
      if ( v6 )
      {
        pxObject = v6->pxObject;
        if ( pxObject )
        {
          if ( !pxObject[193] )
          {
            QTaskFromLevelQTaskID = Level_GetQTaskFromLevelQTaskID(vFormationDistance_low);
            if ( QTaskFromLevelQTaskID )
            {
              qmemcpy(&igi2_frame.tAlarmTriggerPos, &QTaskFromLevelQTaskID[1], sizeof(igi2_frame.tAlarmTriggerPos));
              nMembers = v3->atTeam[0].nMembers;
              p_nMembers = &v3->atTeam[0].nMembers;
              if ( nMembers > 0 )
              {
                atTeam = v3->atTeam;
                igi2_frame.v26 = v3->atTeam[0].nMembers;
                do
                {
                  v12 = atTeam->aptMemberRef[0]->pxObject;
                  if ( v12 )
                  {
                    v13 = *((double **)v12 + 8);
                    *(float *)&igi2_frame.Rs.nResult = v13[5] - igi2_frame.tAlarmTriggerPos.vX;
                    *((float *)&igi2_frame.Rs.nResult + 1) = v13[6] - igi2_frame.tAlarmTriggerPos.vY;
                    v14 = sqrt(
                            *(float *)&igi2_frame.Rs.nResult * *(float *)&igi2_frame.Rs.nResult
                          + *((float *)&igi2_frame.Rs.nResult + 1) * *((float *)&igi2_frame.Rs.nResult + 1)
                          + (v13[7] - igi2_frame.tAlarmTriggerPos.vZ) * (v13[7] - igi2_frame.tAlarmTriggerPos.vZ));
                    if ( !igi2_frame.ptClosestHumanAI || v14 < igi2_frame.vClosestDist )
                    {
                      igi2_frame.vClosestDist = v14;
                      igi2_frame.ptClosestHumanAI = (struct HumanAI_s *)v12;
                    }
                  }
                  atTeam = (struct AISquadTeam_s *)((char *)atTeam + 4);
                  --igi2_frame.v26;
                }
                while ( igi2_frame.v26 );
              }
              v15 = 0;
              if ( nMembers > 0 )
              {
                v16 = v3->atTeam;
                v17 = v3->atTeam;
                while ( 1 )
                {
                  v18 = (struct HumanAI_s *)v17->aptMemberRef[0]->pxObject;
                  if ( v18 )
                  {
                    if ( v18 != igi2_frame.ptClosestHumanAI )
                      break;
                  }
                  ++v15;
                  v17 = (struct AISquadTeam_s *)((char *)v17 + 4);
                  if ( v15 >= *p_nMembers )
                    goto LABEL_22;
                }
                v19 = v16->aptMemberRef[0];
                v16->aptMemberRef[0] = v3->atTeam[0].aptMemberRef[v15];
                v3->atTeam[0].aptMemberRef[v15] = v19;
              }
LABEL_22:
              if ( igi2_frame.ptClosestHumanAI )
              {
                if ( *(float *)&v3->tEditVariables.zScriptFileName[12] * 4096.0 > igi2_frame.vClosestDist )
                {
                  pfRunCallback = igi2_frame.ptClosestHumanAI->atActionStackItemList[0].pfRunCallback;
                  if ( !*(_DWORD *)pfRunCallback
                    || !pfRunCallback
                    || *((void (__cdecl **)(struct HumanAI_s *, struct HumanAIActionStackItem_s *))pfRunCallback + 6) != HumanAIContent_ActivateInitCB )
                  {
                    v21 = LODWORD(v3->tEditVariables.vFormationDistance);
                    igi2_frame.tOrderContext.eOrder = AISQUAD_ORDER_ACTIVATE;
                    igi2_frame.tOrderContext.iDelay = 0;
                    igi2_frame.tOrderContext.uContext.tMoveToNodeContext.nNodeId = v21;
                    HumanAIContent_ReceiveSquadOrder(igi2_frame.ptClosestHumanAI, &igi2_frame.tOrderContext);
                    if ( *p_nMembers > 1 )
                    {
                      v22 = HumanAI_PlaySoundAtPosition(&igi2_frame.ptClosestHumanAI->tQTask, "gv_22_03", false);
                      if ( v22 )
                      {
                        if ( AISquad_AddSoundToPlayingList(igi2_frame.ptAISquad, v22, igi2_frame.ptClosestHumanAI) == false )
                          QTask_Delete(v22);
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
  igi2_frame.Rs.zResult = (char *)&g_zInitialValue;
  igi2_frame.Rs.vResult = 1.0;
  igi2_frame.Rs.nResult = 1;
  qmemcpy(retstr, &igi2_frame.Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/humanai/aisquad.c:5461  [anchor-mhash]
struct Result_s *__cdecl AISquad_SF_ManStationaryGunCB(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct HumanAI_s *ptClosestHumanAI; };
    struct { char igi2_o1[4]; float vClosestDist; };
    struct { char igi2_o2[8]; struct AISquadTeam_s *v18; };
    struct { char igi2_o3[12]; int v19; };
    struct { char igi2_o4[16]; int v20; };
    struct { char igi2_o5[20]; float tReal32x3; };
    struct { char igi2_o6[24]; float tReal32x3_4; };
    struct { char igi2_o7[32]; struct real64x3_t tGunPos; };
    struct { char igi2_o8[56]; struct AISquadOrderContext_s tOrderContext; };
    char igi2_extent[112];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  float vOverrideFormationDistance; // eax
  struct QReference_s *v4; // eax
  float *pxObject; // ebx
  int nMembers; // eax
  struct AISquadTeam_s *atTeam; // edx
  struct HumanAI_s *v8; // esi
  void (__cdecl *pfRunCallback)(struct HumanAI_s *, struct HumanAIActionStackItem_s *); // eax
  double *ptParent; // edi
  double *TargetQTask; // eax
  long double v12; // st4
  bool v13; // zf
  void (__cdecl *v14)(struct HumanAI_s *, struct HumanAIActionStackItem_s *); // eax

  vOverrideFormationDistance = AISquad_ptCurrentAISquad->tEditVariables.vOverrideFormationDistance;
  igi2_frame.ptClosestHumanAI = nullptr;
  igi2_frame.vClosestDist = 0.0;
  igi2_frame.v20 = LODWORD(vOverrideFormationDistance);
  if ( LODWORD(vOverrideFormationDistance) < 0x1000 )
  {
    v4 = Level_atLevelQTaskID[LODWORD(vOverrideFormationDistance)];
    if ( v4 )
    {
      pxObject = (float *)v4->pxObject;
      if ( pxObject )
      {
        if ( !*((_BYTE *)pxObject + 592) )
        {
          nMembers = AISquad_ptCurrentAISquad->atTeam[0].nMembers;
          qmemcpy(&igi2_frame.tGunPos, pxObject + 10, sizeof(igi2_frame.tGunPos));
          if ( nMembers > 0 )
          {
            atTeam = AISquad_ptCurrentAISquad->atTeam;
            igi2_frame.v18 = AISquad_ptCurrentAISquad->atTeam;
            igi2_frame.v19 = nMembers;
            do
            {
              v8 = (struct HumanAI_s *)atTeam->aptMemberRef[0]->pxObject;
              if ( v8 )
              {
                pfRunCallback = v8->atActionStackItemList[0].pfRunCallback;
                if ( !*(_DWORD *)pfRunCallback
                  || !pfRunCallback
                  || *((void (__cdecl **)(struct HumanAI_s *, struct HumanAIActionStackItem_s *))pfRunCallback
                     + 6) != HumanAIContent_CombatStationaryGunInitCB )
                {
                  ptParent = (double *)v8->tQTask.ptParent;
                  TargetQTask = (double *)HumanAI_GetTargetQTask(v8, true);
                  if ( TargetQTask )
                  {
                    if ( pxObject[111] * (TargetQTask[7] - igi2_frame.tGunPos.vZ)
                       + pxObject[108] * (TargetQTask[6] - igi2_frame.tGunPos.vY)
                       + pxObject[105] * (TargetQTask[5] - igi2_frame.tGunPos.vX) >= 0.0 )
                    {
                      igi2_frame.tReal32x3 = ptParent[5] - igi2_frame.tGunPos.vX;
                      igi2_frame.tReal32x3_4 = ptParent[6] - igi2_frame.tGunPos.vY;
                      v12 = sqrt(
                              igi2_frame.tReal32x3 * igi2_frame.tReal32x3
                            + igi2_frame.tReal32x3_4 * igi2_frame.tReal32x3_4
                            + (ptParent[7] - igi2_frame.tGunPos.vZ) * (ptParent[7] - igi2_frame.tGunPos.vZ));
                      if ( !igi2_frame.ptClosestHumanAI || v12 < igi2_frame.vClosestDist )
                      {
                        igi2_frame.vClosestDist = v12;
                        igi2_frame.ptClosestHumanAI = v8;
                      }
                    }
                  }
                }
              }
              atTeam = (struct AISquadTeam_s *)&igi2_frame.v18->aptMemberRef[1];
              v13 = igi2_frame.v19 == 1;
              igi2_frame.v18 = (struct AISquadTeam_s *)((char *)igi2_frame.v18 + 4);
              --igi2_frame.v19;
            }
            while ( !v13 );
            if ( igi2_frame.ptClosestHumanAI )
            {
              if ( *(float *)&AISquad_ptCurrentAISquad->tEditVariables.zScriptFileName[12] * 4096.0 > igi2_frame.vClosestDist )
              {
                v14 = igi2_frame.ptClosestHumanAI->atActionStackItemList[0].pfRunCallback;
                if ( !*(_DWORD *)v14
                  || !v14
                  || *((void (__cdecl **)(struct HumanAI_s *, struct HumanAIActionStackItem_s *))v14 + 6) != HumanAIContent_ActivateInitCB )
                {
                  igi2_frame.tOrderContext.eOrder = AISQUAD_ORDER_ACTIVATE;
                  igi2_frame.tOrderContext.iDelay = 0;
                  igi2_frame.tOrderContext.uContext.tMoveToNodeContext.nNodeId = igi2_frame.v20;
                  HumanAIContent_ReceiveSquadOrder(igi2_frame.ptClosestHumanAI, &igi2_frame.tOrderContext);
                }
              }
            }
          }
        }
      }
    }
  }
  LODWORD(igi2_frame.tGunPos.vZ) = &g_zInitialValue;
  igi2_frame.tGunPos.vY = 1.0;
  LODWORD(igi2_frame.tGunPos.vX) = 1;
  qmemcpy(retstr, &igi2_frame.tGunPos, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/humanai/aisquad.c:5575  [anchor-mhash]
struct Result_s *__cdecl AISquad_SF_MoveToNodeCB(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct Result_s Rs; };
    struct { char igi2_o1[28]; struct AISquad_s *ptAISquad; };
    struct { char igi2_o2[32]; struct AISquadAction_s tAction; };
    struct { char igi2_o3[312]; struct AISquadActionChangeContext_s tActionChangeContext; };
    char igi2_extent[528];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  bool v3; // zf
  struct QReference_s *v4; // eax
  struct Graph_s **pxObject; // edi
  int v6; // ebx
  struct GraphNode_s *Node; // esi

  v3 = ptArgList->nArguments == 1;
  igi2_frame.ptAISquad = AISquad_ptCurrentAISquad;
  if ( !v3 )
    goto LABEL_6;
  if ( !AISquad_ptCurrentAISquad->atTeam[0].nMembers
    || (v4 = AISquad_ptCurrentAISquad->atTeam[0].aptMemberRef[0]) == nullptr
    || (pxObject = (struct Graph_s **)v4->pxObject) == nullptr )
  {
    igi2_frame.Rs.nResult = 0;
    goto LABEL_11;
  }
  v6 = Script_EvalArgInt(ptArgList, 0);
  Node = Graph_GetNode(pxObject[7282], v6);
  if ( !Node )
  {
LABEL_6:
    igi2_frame.Rs.nResult = 0;
LABEL_11:
    HIDWORD(igi2_frame.Rs.vResult) = 0;
    goto LABEL_12;
  }
  if ( pxObject[7487] != (struct Graph_s *)v6 )
  {
    AISquad_ClearActionStack(&igi2_frame.ptAISquad->tQTask, true, false);
    igi2_frame.tActionChangeContext.eNextAction = AISQUAD_ACTION_MOVE;
    igi2_frame.tActionChangeContext.isPopMembersStacks = true;
    igi2_frame.tActionChangeContext.isDeserializing = false;
    Graph_GetNodePos(&igi2_frame.tActionChangeContext.tToMoveContext.tPosition, Node);
    igi2_frame.tAction.eAction = AISQUAD_ACTION_MOVE;
    igi2_frame.tAction.pfDeInitHandler = AISquad_SquadActionDefaultDeInitHandler;
    igi2_frame.tAction.pfEventHandler = AISquad_SquadActionDefaultEventHandler;
    igi2_frame.tAction.pfInitHandler = AISquad_SquadActionMoveInitHandler;
    igi2_frame.tAction.pfRunHandler = AISquad_SquadActionMoveRunHandler;
    igi2_frame.tAction.ptSwitchStateSoundQTaskRef = nullptr;
    AISquad_PushOntoActionStack(&igi2_frame.ptAISquad->tQTask, &igi2_frame.tAction, &igi2_frame.tActionChangeContext);
  }
  igi2_frame.Rs.nResult = 1;
  HIDWORD(igi2_frame.Rs.vResult) = 1072693248;
LABEL_12:
  LODWORD(igi2_frame.Rs.vResult) = 0;
  igi2_frame.Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &igi2_frame.Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/humanai/aisquad.c:5650  [anchor-mhash]
struct Result_s *__cdecl AISquad_SF_PatrolCB(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct Result_s Rs; };
    struct { char igi2_o1[24]; struct AISquadAction_s tAction; };
    struct { char igi2_o2[304]; struct AISquadActionChangeContext_s tActionChangeContext; };
    char igi2_extent[520];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct AISquad_s *v3; // edi
  struct QReference_s *v4; // eax
  int v5; // esi

  v3 = AISquad_ptCurrentAISquad;
  if ( ptArgList->nArguments == 1 )
  {
    if ( AISquad_ptCurrentAISquad->atTeam[0].nMembers
      && (v4 = AISquad_ptCurrentAISquad->atTeam[0].aptMemberRef[0]) != nullptr
      && v4->pxObject )
    {
      v5 = Script_EvalArgInt(ptArgList, 0);
      AISquad_ClearActionStack(&v3->tQTask, true, false);
      igi2_frame.tActionChangeContext.eNextAction = AISQUAD_ACTION_PATROL;
      igi2_frame.tActionChangeContext.isPopMembersStacks = true;
      igi2_frame.tActionChangeContext.isDeserializing = false;
      igi2_frame.tActionChangeContext.tToPatrolContext.nPatrolPathId = v5;
      igi2_frame.tAction.eAction = AISQUAD_ACTION_PATROL;
      igi2_frame.tAction.pfDeInitHandler = AISquad_SquadActionDefaultDeInitHandler;
      igi2_frame.tAction.pfEventHandler = AISquad_SquadActionDefaultEventHandler;
      igi2_frame.tAction.pfInitHandler = AISquad_SquadActionPatrolInitHandler;
      igi2_frame.tAction.pfRunHandler = AISquad_SquadActionPatrolRunHandler;
      igi2_frame.tAction.ptSwitchStateSoundQTaskRef = nullptr;
      AISquad_PushOntoActionStack(&v3->tQTask, &igi2_frame.tAction, &igi2_frame.tActionChangeContext);
      igi2_frame.Rs.nResult = 1;
      HIDWORD(igi2_frame.Rs.vResult) = 1072693248;
    }
    else
    {
      HIDWORD(igi2_frame.Rs.vResult) = 0;
      igi2_frame.Rs.nResult = 0;
    }
  }
  else
  {
    igi2_frame.Rs.nResult = 0;
    HIDWORD(igi2_frame.Rs.vResult) = 0;
  }
  igi2_frame.Rs.zResult = (char *)&g_zInitialValue;
  LODWORD(igi2_frame.Rs.vResult) = 0;
  qmemcpy(retstr, &igi2_frame.Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/humanai/aisquad.c:5715  [anchor-mhash]
struct Result_s *__cdecl AISquad_SF_ThrowGrenadeCB(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  #pragma pack(push, 1)
  union
  {
    struct { int v12; };
    struct { char igi2_o1[4]; int v13; };
    struct { char igi2_o2[8]; int *v14; };
    struct { char igi2_o3[12]; struct AISquad_s *v15; };
    struct { char igi2_o4[28]; int *p_nNumTeams; };
    struct { char igi2_o5[32]; struct real64x3_t ptTargetPos; };
    struct { char igi2_o6[56]; struct AISquadOrderContext_s ptSquadOrder; };
    char igi2_extent[112];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int *p_nMembers; // ecx
  int v4; // ebx
  struct QReference_s *v5; // edx
  int v6; // edi
  int v7; // edx
  int v8; // esi
  double *v9; // eax
  bool v10; // cc

  p_nMembers = &AISquad_ptCurrentAISquad->atTeam[0].nMembers;
  v4 = 0;
  igi2_frame.v15 = AISquad_ptCurrentAISquad;
  if ( AISquad_ptCurrentAISquad->atTeam[0].nMembers
    && (v5 = AISquad_ptCurrentAISquad->atTeam[0].aptMemberRef[0]) != nullptr
    && v5->pxObject )
  {
    igi2_frame.v13 = 0;
    igi2_frame.p_nNumTeams = &AISquad_ptCurrentAISquad->nNumTeams;
    if ( AISquad_ptCurrentAISquad->nNumTeams > 0 )
    {
      igi2_frame.v12 = 10;
      igi2_frame.v14 = &AISquad_ptCurrentAISquad->atTeam[0].nMembers;
      do
      {
        if ( v4 >= 2 )
          break;
        v6 = 0;
        if ( *p_nMembers > 0 )
        {
          do
          {
            if ( v4 >= 2 )
              break;
            v7 = *((_DWORD *)&igi2_frame.v15->tQTask.ptNext + v6 + igi2_frame.v12);
            v8 = *(_DWORD *)(v7 + 8);
            if ( v8 )
            {
              if ( *(_BYTE *)(v8 + 29904) )
              {
                HumanAI_GetTargetPosition(&igi2_frame.ptTargetPos, *(struct HumanAI_s **)(v7 + 8));
                if ( !Real64x3_NullVector(&igi2_frame.ptTargetPos) )
                {
                  v9 = *(double **)(v8 + 32);
                  if ( sqrt(
                         (igi2_frame.ptTargetPos.vX - v9[5]) * (igi2_frame.ptTargetPos.vX - v9[5])
                       + (igi2_frame.ptTargetPos.vY - v9[6]) * (igi2_frame.ptTargetPos.vY - v9[6])
                       + (igi2_frame.ptTargetPos.vZ - v9[7]) * (igi2_frame.ptTargetPos.vZ - v9[7])) < 204800.0 )
                  {
                    igi2_frame.ptSquadOrder.eOrder = AISQUAD_ORDER_THROWGRENADE;
                    igi2_frame.ptSquadOrder.iDelay = 0;
                    HumanAIContent_ReceiveSquadOrder((struct HumanAI_s *)v8, &igi2_frame.ptSquadOrder);
                    ++v4;
                  }
                }
              }
            }
            p_nMembers = igi2_frame.v14;
            ++v6;
          }
          while ( v6 < *igi2_frame.v14 );
        }
        p_nMembers += 10;
        v10 = ++igi2_frame.v13 < *igi2_frame.p_nNumTeams;
        igi2_frame.v14 = p_nMembers;
        igi2_frame.v12 += 10;
      }
      while ( v10 );
    }
    LODWORD(igi2_frame.ptTargetPos.vX) = 1;
    HIDWORD(igi2_frame.ptTargetPos.vY) = 1072693248;
  }
  else
  {
    HIDWORD(igi2_frame.ptTargetPos.vY) = 0;
    LODWORD(igi2_frame.ptTargetPos.vX) = 0;
  }
  LODWORD(igi2_frame.ptTargetPos.vY) = 0;
  LODWORD(igi2_frame.ptTargetPos.vZ) = &g_zInitialValue;
  qmemcpy(retstr, &igi2_frame.ptTargetPos, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/humanai/aisquad.c:5773  [anchor-mhash]
struct Result_s *__cdecl AISquad_SF_GetCurrentPatrolIDCB(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  unsigned int v3; // ecx
  int *v4; // eax
  bool v5; // zf
  struct Result_s *result; // eax
  double v7; // st7
  struct Result_s Rs; // [esp+Ch] [ebp-18h] BYREF

  v3 = 280 * AISquad_ptCurrentAISquad->tActionStack.nNumActions;
  v4 = (int *)&AISquad_ptCurrentAISquad->atScriptReceivedSquadEvent[31].aptSquadMemberQTaskRef[v3 / 4 + 5];
  v5 = AISquad_ptCurrentAISquad->atEnemyTarget[v3 / 0x28 + 4].nTimer == 6;
  Rs.zResult = (char *)&g_zInitialValue;
  if ( v5 )
  {
    v7 = (double)*v4;
    Rs.nResult = *v4;
    result = retstr;
    Rs.vResult = v7;
  }
  else
  {
    result = retstr;
    Rs.nResult = -1;
    Rs.vResult = -1.0;
  }
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return result;
}

// source: j/0/humanai/aisquad.c:5804  [anchor-mhash]
struct Result_s *__cdecl AISquad_SF_GetEventSpecificInt32(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  int nNumReceivedEvents; // eax
  char *v4; // eax
  struct Result_s Rs; // [esp+Ch] [ebp-18h] BYREF

  nNumReceivedEvents = AISquad_ptCurrentAISquad->nNumReceivedEvents;
  if ( nNumReceivedEvents > 0
    && (v4 = (char *)&AISquad_ptCurrentAISquad->tQTask.tQTaskChildren + 112 * nNumReceivedEvents) != nullptr )
  {
    Rs.nResult = *((_DWORD *)v4 + 22);
    Rs.vResult = (double)Rs.nResult;
  }
  else
  {
    Rs.nResult = -1;
    Rs.vResult = -1.0;
  }
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/humanai/aisquad.c:5830  [anchor-mhash]
struct Result_s *__cdecl AISquad_SF_GetDistanceToEvent(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  #pragma pack(push, 1)
  union
  {
    struct { float vDistance; };
    struct { char igi2_o1[8]; struct Result_s Rs; };
    char igi2_extent[32];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int nNumReceivedEvents; // eax
  char *v4; // ecx
  int v5; // eax
  char *v6; // edx
  int v7; // esi
  int v8; // eax
  double *v9; // eax
  double v10; // st3
  long double v11; // st4
  double v12; // st6

  nNumReceivedEvents = AISquad_ptCurrentAISquad->nNumReceivedEvents;
  igi2_frame.vDistance = 3.4028234663852886e+38;
  if ( nNumReceivedEvents > 0
    && (v4 = (char *)&AISquad_ptCurrentAISquad->tQTask.tQTaskChildren + 112 * nNumReceivedEvents,
        (struct AISquad_s *)((char *)AISquad_ptCurrentAISquad + 112 * nNumReceivedEvents) != (struct AISquad_s *)-8)
    && (v5 = *((_DWORD *)&AISquad_ptCurrentAISquad->tQTask.tQTaskChildren.ptTail + 28 * nNumReceivedEvents)) != 0 )
  {
    if ( v5 > 0 )
    {
      v6 = v4 + 12;
      v7 = *((_DWORD *)v4 + 2);
      do
      {
        v8 = *(_DWORD *)(*(_DWORD *)v6 + 8);
        if ( v8 )
        {
          v9 = *(double **)(v8 + 32);
          *(float *)&igi2_frame.Rs.nResult = v9[5] - *((double *)v4 + 6);
          *((float *)&igi2_frame.Rs.nResult + 1) = v9[6] - *((double *)v4 + 7);
          v10 = v9[7] - *((double *)v4 + 8);
          v11 = sqrt(
                  *(float *)&igi2_frame.Rs.nResult * *(float *)&igi2_frame.Rs.nResult
                + *((float *)&igi2_frame.Rs.nResult + 1) * *((float *)&igi2_frame.Rs.nResult + 1)
                + v10 * v10);
          if ( v11 < igi2_frame.vDistance )
            igi2_frame.vDistance = v11;
        }
        v6 += 4;
        --v7;
      }
      while ( v7 );
    }
    v12 = igi2_frame.vDistance * 0.000244140625;
    igi2_frame.Rs.nResult = (__int64)v12;
    igi2_frame.Rs.vResult = v12;
  }
  else
  {
    igi2_frame.Rs.nResult = -1;
    igi2_frame.Rs.vResult = -1.0;
  }
  igi2_frame.Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &igi2_frame.Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/humanai/aisquad.c:5895  [size]
struct Result_s *__cdecl AISquad_SF_DefaultHandlerCB(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  Script_Execute(AISquad_ptDefaultScript);
  Rs.nResult = 1;
  Rs.vResult = 1.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/humanai/aisquad.c:5911  [anchor-mhash]
struct Result_s *__cdecl AISquad_SF_ReceiverHasTarget(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  #pragma pack(push, 1)
  union
  {
    struct { int isHasTarget; };
    struct { char igi2_o1[4]; struct Result_s Rs; };
    char igi2_extent[28];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct AISquad_s *v3; // ecx
  int nNumReceivedEvents; // eax
  int v5; // ebx
  char *v6; // eax
  int v7; // ebp
  char *v8; // edi
  struct HumanAI_s *v9; // esi
  unsigned int bQTaskMask; // eax

  v3 = AISquad_ptCurrentAISquad;
  nNumReceivedEvents = AISquad_ptCurrentAISquad->nNumReceivedEvents;
  v5 = 0;
  igi2_frame.isHasTarget = 1;
  if ( nNumReceivedEvents <= 0 )
    v6 = nullptr;
  else
    v6 = (char *)&AISquad_ptCurrentAISquad->tQTask.tQTaskChildren + 112 * nNumReceivedEvents;
  v7 = *((_DWORD *)v6 + 2);
  if ( !v7 )
  {
    igi2_frame.Rs.nResult = 0;
    igi2_frame.Rs.vResult = 0.0;
    goto LABEL_17;
  }
  if ( v7 <= 0 )
    goto LABEL_16;
  v8 = v6 + 12;
  while ( 1 )
  {
    v9 = *(struct HumanAI_s **)(*(_DWORD *)v8 + 8);
    if ( v9 )
      break;
LABEL_19:
    ++v5;
    v8 += 4;
    if ( v5 >= v7 )
      goto LABEL_16;
  }
  if ( HumanAI_GetTargetQTask(v9, (enum bool)(v3->tEditVariables.nTargetTimeout != 2)) )
  {
LABEL_18:
    v3 = AISquad_ptCurrentAISquad;
    goto LABEL_19;
  }
  bQTaskMask = v9->tAIDetection.atListItems[0].bQTaskMask;
  if ( *(_DWORD *)bQTaskMask && bQTaskMask )
  {
    while ( !*(_BYTE *)(bQTaskMask + 57) )
    {
      bQTaskMask = *(_DWORD *)bQTaskMask;
      if ( !*(_DWORD *)bQTaskMask || !bQTaskMask )
        goto LABEL_15;
    }
    goto LABEL_18;
  }
LABEL_15:
  igi2_frame.isHasTarget = 0;
LABEL_16:
  igi2_frame.Rs.nResult = igi2_frame.isHasTarget;
  igi2_frame.Rs.vResult = (double)igi2_frame.isHasTarget;
LABEL_17:
  igi2_frame.Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &igi2_frame.Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/humanai/aisquad.c:5961  [anchor-mhash]
struct Result_s *__cdecl AISquad_SF_SelectAndPlaySoundAtReceiversPos(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  int nNumReceivedEvents; // eax
  struct AISquadEventContext_s *v4; // ecx
  struct QTask_s *ClosestEventReceiver; // esi
  int v6; // eax
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  if ( ptArgList->nArguments == 1 )
  {
    nNumReceivedEvents = AISquad_ptCurrentAISquad->nNumReceivedEvents;
    if ( nNumReceivedEvents <= 0 )
      v4 = nullptr;
    else
      v4 = (struct AISquadEventContext_s *)((char *)&AISquad_ptCurrentAISquad->tQTask.tQTaskChildren
                                          + 112 * nNumReceivedEvents);
    ClosestEventReceiver = AISquad_GetClosestEventReceiver(v4);
    if ( ClosestEventReceiver )
    {
      v6 = Script_EvalArgInt(ptArgList, 0);
      if ( v6 >= 0 )
      {
        if ( v6 > 19 )
          v6 = 19;
      }
      else
      {
        v6 = 0;
      }
      AISquad_SelectAndPlaySoundAtMembersPos(AISquad_ptCurrentAISquad, v6, ClosestEventReceiver);
    }
    Rs.nResult = 0;
    HIDWORD(Rs.vResult) = 0;
  }
  else
  {
    Rs.nResult = 1;
    HIDWORD(Rs.vResult) = 1072693248;
  }
  LODWORD(Rs.vResult) = 0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/humanai/aisquad.c:6008  [anchor-mhash]
struct Result_s *__cdecl AISquad_SF_TriggerEvent(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct Result_s Rs; };
    struct { char igi2_o1[24]; struct HumanAIEventContext_t tContext; };
    char igi2_extent[88];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct ArgList_s *v3; // edi
  int nNumReceivedEvents; // eax
  char *v5; // ebx
  struct ArgList_s *v6; // esi
  double v7; // st7
  int v8; // eax
  int v9; // eax

  v3 = ptArgList;
  if ( ptArgList->nArguments == 2 )
  {
    nNumReceivedEvents = AISquad_ptCurrentAISquad->nNumReceivedEvents;
    if ( nNumReceivedEvents <= 0 )
      v5 = nullptr;
    else
      v5 = (char *)&AISquad_ptCurrentAISquad->tQTask.tQTaskChildren + 112 * nNumReceivedEvents;
    if ( ptArgList->isQVM )
    {
      *(float *)&ptArgList = 0.0;
      QVM_EvalArg(&ptArgList, 4, v3, 0, 1);
      v6 = ptArgList;
    }
    else
    {
      v6 = (struct ArgList_s *)Expression_EvalInt(*ptArgList->aptExpression);
    }
    if ( v3->isQVM )
    {
      *(float *)&ptArgList = 0.0;
      QVM_EvalArg(&ptArgList, 4, v3, 1, 2);
      v7 = *(float *)&ptArgList;
    }
    else
    {
      v7 = Expression_EvalFloat((struct QExpression_s *)*((_DWORD *)v3->aptExpression + 1));
    }
    *(float *)&ptArgList = v7;
    if ( v6 == (struct ArgList_s *)41 )
    {
      if ( *((_DWORD *)v5 + 2) )
      {
        v8 = *(_DWORD *)(*((_DWORD *)v5 + 3) + 8);
        if ( v8 )
        {
          v9 = *(_DWORD *)(v8 + 32);
          igi2_frame.tContext.eEvent = 41;
          igi2_frame.tContext.bFlags = 1314;
          igi2_frame.tContext.vRadius = *(float *)&ptArgList * 4096.0;
          igi2_frame.tContext.ptHumanOriginatorQTask = (struct QTask_s *)v9;
          igi2_frame.tContext.ptPosition = (struct real64x3_t *)(v9 + 40);
          igi2_frame.tContext.ptReferenceQTask = nullptr;
          igi2_frame.tContext.eTeam = *(_DWORD *)(v9 + 428);
          HumanAI_SendEvent(&igi2_frame.tContext);
        }
      }
    }
    igi2_frame.Rs.nResult = 0;
    HIDWORD(igi2_frame.Rs.vResult) = 0;
  }
  else
  {
    igi2_frame.Rs.nResult = 1;
    HIDWORD(igi2_frame.Rs.vResult) = 1072693248;
  }
  igi2_frame.Rs.zResult = (char *)&g_zInitialValue;
  LODWORD(igi2_frame.Rs.vResult) = 0;
  qmemcpy(retstr, &igi2_frame.Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/humanai/aisquad.c:6073  [anchor-strings]
struct QTask_s *__cdecl AISquad_SelectAndPlaySoundAtMembersPos(
        struct AISquad_s *ptAISquad,
        int nSoundSample,
        struct QTask_s *ptMemberQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { char v21; };
    struct { char igi2_o1[1]; char zSound[32]; };
    struct { char igi2_o2[33]; char zTemp[32]; };
    char igi2_extent[65];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int nTick; // edi
  struct QTask_s *ptParent; // ebx
  int v5; // esi
  struct RandomState_s *p_tRunRandomState; // eax
  char *v7; // eax
  char *v8; // edx
  char v9; // cl
  int v10; // ecx
  struct QTask_s *i; // eax
  int v12; // et2
  char *v13; // edi
  unsigned int v15; // eax
  char *v16; // edi
  struct QTask_s *v18; // eax
  struct QTask_s *v19; // edi

  if ( !ptMemberQTask )
    return nullptr;
  if ( !LevelFlow_ptLevelFlow )
    return nullptr;
  nTick = LevelFlow_ptLevelFlow->nTick;
  ptParent = ptMemberQTask->ptParent;
  v5 = nSoundSample;
  if ( nTick - AISQuad_anVoiceLastPlayedTickTable[nSoundSample] < 150
    || AISquad_aisVoiceDontPlayForSingleAI[nSoundSample] && AISquad_GetMemberCount(&ptAISquad->tQTask) == 1 )
  {
    return nullptr;
  }
  if ( ptParent[76].tQTaskChildren.ptHead )
    return nullptr;
  p_tRunRandomState = &Game_ptGame->tRunRandomState;
  AISQuad_anVoiceLastPlayedTickTable[v5] = nTick;
  v7 = &AISquad_aazVoiceTable[8 * v5 + 32 * Random_GetRandomNumberBelowLimit(p_tRunRandomState, 4)];
  v8 = (char *)(igi2_frame.zSound - v7);
  do
  {
    v9 = *v7;
    v7[(_DWORD)v8] = *v7;
    ++v7;
  }
  while ( v9 );
  v10 = 0;
  for ( i = ptMemberQTask; (int)i > 0; v10 += v12 )
  {
    v12 = (int)i % 10;
    i = (struct QTask_s *)((int)i / 10);
  }
  sprintf(igi2_frame.zTemp, "%0.2d", v10 % 2 + 1);
  v13 = &igi2_frame.v21;
  while ( *++v13 )
    ;
  *(_WORD *)v13 = 95;
  v15 = strlen(igi2_frame.zTemp) + 1;
  v16 = &igi2_frame.v21;
  while ( *++v16 )
    ;
  qmemcpy(v16, igi2_frame.zTemp, v15);
  v18 = HumanAI_PlaySoundAtPosition(ptMemberQTask, igi2_frame.zSound, true);
  v19 = v18;
  if ( v18 && AISquad_AddSoundToPlayingList(ptAISquad, v18, (struct HumanAI_s *)ptMemberQTask) == false )
  {
    QTask_Delete(v19);
    return nullptr;
  }
  return v19;
}

// source: j/0/humanai/aisquad.c:6158  [anchor-hash]
void __cdecl AISquad_RegisterScriptValues()
{
  Symbol_Register(
    "AIType_Offensive",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)1,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIType_Defensive",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    nullptr,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIType_OnVehicle",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)2,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AISquadState_Idle",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    nullptr,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AISquadState_HoldArea",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)1,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AISquadState_Inquire",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)2,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AISquadState_SearchArea",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)3,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AISquadState_Move",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)4,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AISquadState_Leapfrog",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)5,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AISquadState_Patrol",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)6,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AISquadState_MoveSearchInDirection",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)7,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AISquadState_LookSearchInDirection",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)8,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AISquadState_Danger",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)9,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIVoice_HurryUp",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    nullptr,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIVoice_Acknowledge",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)1,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIVoice_HoldArea",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)2,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIVoice_SearchArea",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)3,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIVoice_RaiseAlarm",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)4,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIVoice_ManStationaryGun",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)5,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIVoice_EnemySpotted",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)6,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIVoice_EnemyFound",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)7,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIVoice_EnemyDetected",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)8,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIVoice_GunShotHeard",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)9,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIVoice_WhatsThat",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)0xA,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIVoice_Engaging",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)0xB,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIVoice_Grenade",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)0xC,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIVoice_LostTarget",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)0xD,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIVoice_TakeCover",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)0xE,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIVoice_Stop",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)0xF,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIVoice_BackToIdle",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)0x10,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIVoice_FalseAlarm",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)0x11,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AIVoice_ManDown",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)0x12,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AISquad_GetState",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))AISquad_SF_GetStateCB,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AISquad_GetEvent",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))AISquad_SF_GetEventCB,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AISquad_SwitchState",
    AISquad_SF_SwitchStateCB,
    nullptr,
    -1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AISquad_GetSquadType",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))AISquad_SF_GetSquadTypeCB,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AISquad_HasTarget",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))AISquad_SF_HasTargetCB,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AISquad_ReceiverLookAtEvent",
    AISquad_SF_ReceiverLookAtEventCB,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AISquad_ReceiverLookInApproxEventDirection",
    AISquad_SF_ReceiverLookInApproxEventDirectionCB,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AISquad_TriggerAlarm",
    AISquad_SF_TriggerAlarmCB,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AISquad_ManStationaryGun",
    AISquad_SF_ManStationaryGunCB,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AISquad_MoveToNode",
    AISquad_SF_MoveToNodeCB,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AISquad_Patrol",
    AISquad_SF_PatrolCB,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AISquad_ThrowGrenade",
    AISquad_SF_ThrowGrenadeCB,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AISquad_GetCurrentPatrolID",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))AISquad_SF_GetCurrentPatrolIDCB,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AISquad_GetEventSpecificInt32",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))AISquad_SF_GetEventSpecificInt32,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AISquad_GetDistanceToEvent",
    AISquad_SF_GetDistanceToEvent,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AISquad_DefaultHandler",
    AISquad_SF_DefaultHandlerCB,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AISquad_ReceiverHasTarget",
    AISquad_SF_ReceiverHasTarget,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AISquad_PlaySoundAtReceiversPos",
    AISquad_SF_SelectAndPlaySoundAtReceiversPos,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AISquad_TriggerEvent",
    AISquad_SF_TriggerEvent,
    nullptr,
    2,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
}

// source: j/0/humanai/aisquad.c:6229  [anchor-hash]
void __cdecl AISquad_DeleteScriptValues()
{
  Symbol_Remove("AIType_Offensive");
  Symbol_Remove("AIType_Defensive");
  Symbol_Remove("AIType_OnVehicle");
  Symbol_Remove("AIVoice_HurryUp");
  Symbol_Remove("AIVoice_Acknowledge");
  Symbol_Remove("AIVoice_HoldArea");
  Symbol_Remove("AIVoice_SearchArea");
  Symbol_Remove("AIVoice_RaiseAlarm");
  Symbol_Remove("AIVoice_ManStationaryGun");
  Symbol_Remove("AIVoice_EnemySpotted");
  Symbol_Remove("AIVoice_EnemyFound");
  Symbol_Remove("AIVoice_EnemyDetected");
  Symbol_Remove("AIVoice_GunShotHeard");
  Symbol_Remove("AIVoice_WhatsThat");
  Symbol_Remove("AIVoice_Engaging");
  Symbol_Remove("AIVoice_Grenade");
  Symbol_Remove("AIVoice_LostTarget");
  Symbol_Remove("AIVoice_TakeCover");
  Symbol_Remove("AIVoice_Stop");
  Symbol_Remove("AIVoice_BackToIdle");
  Symbol_Remove("AIVoice_FalseAlarm");
  Symbol_Remove("AIVoice_ManDown");
  Symbol_Remove("AISquadState_Idle");
  Symbol_Remove("AISquadState_HoldArea");
  Symbol_Remove("AISquadState_Inquire");
  Symbol_Remove("AISquadState_SearchArea");
  Symbol_Remove("AISquadState_Move");
  Symbol_Remove("AISquadState_Leapfrog");
  Symbol_Remove("AISquadState_Patrol");
  Symbol_Remove("AISquadState_MoveSearchInDirection");
  Symbol_Remove("AISquadState_LookSearchInDirection");
  Symbol_Remove("AISquadState_Danger");
  Symbol_Remove("AISquad_GetState");
  Symbol_Remove("AISquad_GetEvent");
  Symbol_Remove("AISquad_SwitchState");
  Symbol_Remove("AISquad_GetSquadType");
  Symbol_Remove("AISquad_HasTarget");
  Symbol_Remove("AISquad_ReceiverLookAtEvent");
  Symbol_Remove("AISquad_ReceiverLookInApproxEventDirection");
  Symbol_Remove("AISquad_TriggerAlarm");
  Symbol_Remove("AISquad_ManStationaryGun");
  Symbol_Remove("AISquad_MoveToNode");
  Symbol_Remove("AISquad_Patrol");
  Symbol_Remove("AISquad_ThrowGrenade");
  Symbol_Remove("AISquad_GetCurrentPatrolID");
  Symbol_Remove("AISquad_GetEventSpecificInt32");
  Symbol_Remove("AISquad_GetDistanceToEvent");
  Symbol_Remove("AISquad_DefaultHandler");
  Symbol_Remove("AISquad_ReceiverHasTarget");
  Symbol_Remove("AISquad_PlaySoundAtReceiversPos");
  Symbol_Remove("AISquad_TriggerEvent");
}

// source: j/0/humanai/aisquad.c:6308  [size]
unsigned __int16 __cdecl AISquad_GetQTaskType()
{
  return AISquad_eQTaskType;
}

// source: j/0/humanai/aisquad.c:6322  [anchor-mhash]
void __cdecl AISquad_RegisterQTaskHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *ptHead; // eax
  int v3; // edx
  struct QTask_s *v4; // ecx
  void (__cdecl *pfHandler)(struct QTask_s *, void *); // ecx
  int v6; // edx

  if ( !BYTE2(ptQTask[218].ptNext) )
  {
    QTaskList_Register(AISquad_ptQTaskList, (struct QTaskList_s *)ptQTask);
    BYTE2(ptQTask[218].ptNext) = 1;
  }
  ptHead = ptQTask->tQTaskChildren.ptHead;
  if ( ptHead->ptNext && ptHead )
  {
    v3 = QTask_nProtectedQTaskStackOffset;
    do
    {
      if ( ptHead->ptNext )
        v4 = ptHead->ptNext->ptNext != nullptr ? ptHead->ptNext : nullptr;
      else
        v4 = nullptr;
      QTask_atProtectedQTaskStack[v3].ptQTask = v4;
      pfHandler = (void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[DynCubeObj_eDynCubeObjRegisterQTaskEvent][ptHead->eQTaskType].pfHandler;
      v6 = v3 + 1;
      QTask_nProtectedQTaskStackOffset = v6;
      if ( pfHandler )
      {
        pfHandler(ptHead, pxContext);
        v6 = QTask_nProtectedQTaskStackOffset;
      }
      ptHead = (struct QTask_s *)dword_849C7DC[v6];
      v3 = v6 - 1;
      QTask_nProtectedQTaskStackOffset = v3;
    }
    while ( ptHead );
  }
}

// source: j/0/humanai/aisquad.c:6344  [anchor-mhash]
void __cdecl AISquad_RemoveQTaskHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *ptHead; // eax
  int v3; // edx
  struct QTask_s *v4; // ecx
  void (__cdecl *pfHandler)(struct QTask_s *, void *); // ecx
  int v6; // edx

  if ( BYTE2(ptQTask[218].ptNext) )
  {
    QTaskList_Remove(AISquad_ptQTaskList, ptQTask);
    BYTE2(ptQTask[218].ptNext) = 0;
  }
  ptHead = ptQTask->tQTaskChildren.ptHead;
  if ( ptHead->ptNext && ptHead )
  {
    v3 = QTask_nProtectedQTaskStackOffset;
    do
    {
      if ( ptHead->ptNext )
        v4 = ptHead->ptNext->ptNext != nullptr ? ptHead->ptNext : nullptr;
      else
        v4 = nullptr;
      QTask_atProtectedQTaskStack[v3].ptQTask = v4;
      pfHandler = (void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[DynCubeObj_eDynCubeObjRemoveQTaskEvent][ptHead->eQTaskType].pfHandler;
      v6 = v3 + 1;
      QTask_nProtectedQTaskStackOffset = v6;
      if ( pfHandler )
      {
        pfHandler(ptHead, pxContext);
        v6 = QTask_nProtectedQTaskStackOffset;
      }
      ptHead = (struct QTask_s *)dword_849C7DC[v6];
      v3 = v6 - 1;
      QTask_nProtectedQTaskStackOffset = v3;
    }
    while ( ptHead );
  }
}

// source: j/0/humanai/aisquad.c:6367  [size]
void __cdecl AISquad_MagicObjEnterEventHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *ptHead; // eax
  int v3; // edx
  struct QTask_s *v4; // ecx
  void (__cdecl *pfHandler)(struct QTask_s *, void *); // ecx
  int v6; // edx

  ptHead = ptQTask->tQTaskChildren.ptHead;
  if ( ptHead->ptNext && ptHead )
  {
    v3 = QTask_nProtectedQTaskStackOffset;
    do
    {
      if ( ptHead->ptNext )
        v4 = ptHead->ptNext->ptNext != nullptr ? ptHead->ptNext : nullptr;
      else
        v4 = nullptr;
      QTask_atProtectedQTaskStack[v3].ptQTask = v4;
      pfHandler = (void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[MagicObj_eMagicObjEnterEvent][ptHead->eQTaskType].pfHandler;
      v6 = v3 + 1;
      QTask_nProtectedQTaskStackOffset = v6;
      if ( pfHandler )
      {
        pfHandler(ptHead, pxContext);
        v6 = QTask_nProtectedQTaskStackOffset;
      }
      ptHead = (struct QTask_s *)dword_849C7DC[v6];
      v3 = v6 - 1;
      QTask_nProtectedQTaskStackOffset = v3;
    }
    while ( ptHead );
  }
}

// source: j/0/humanai/aisquad.c:6381  [anchor-refs]
void __cdecl AISquad_DrawComputerObjectQTaskHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *ptHead; // esi
  __int16 v3; // ax
  struct QTask_s *v4; // ecx
  int v5; // edx
  void (__cdecl *pfHandler)(struct QTask_s *, void *); // ecx

  ptHead = ptQTask->tQTaskChildren.ptHead;
  if ( ptHead->ptNext && ptHead )
  {
    v3 = ComputerObject_eDrawComputerObjectQTaskEvent;
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
        v3 = QTask_NewQTaskEventFn(0x200u, "DrawComputerObject");
        ComputerObject_eDrawComputerObjectQTaskEvent = v3;
      }
      pfHandler = (void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[v3][ptHead->eQTaskType].pfHandler;
      if ( pfHandler )
      {
        pfHandler(ptHead, pxContext);
        v3 = ComputerObject_eDrawComputerObjectQTaskEvent;
      }
      ptHead = (struct QTask_s *)dword_849C7DC[QTask_nProtectedQTaskStackOffset--];
    }
    while ( ptHead );
  }
}

// source: j/0/humanai/aisquad.c:6413  [anchor-hash]
void __cdecl AISquad_Open()
{
  unsigned __int16 BaseQTaskType; // ax
  unsigned __int16 v1; // si
  __int16 v2; // ax
  _DWORD *v3; // esi
  _DWORD *v4; // esi
  _DWORD *v5; // esi
  struct ParameterList_s *v6; // eax
  int v7; // edx
  struct ParameterList_s *v8; // eax
  int v9; // edx

  AISquad_ptQTaskList = QTaskList_New(100);
  BaseQTaskType = QTask_GetBaseQTaskType();
  v1 = QTask_NewQTaskType("AISquad", 9024, BaseQTaskType, 0, 0);
  AISquad_eQTaskType = v1;
  QTask_LinkQTaskEventHandlerFn(v1, 0, AISquad_CreateHandler);
  QTask_LinkQTaskEventHandlerFn(v1, ParameterList_eUpdateInternalDataQTaskEvent, AISquad_UpdateInternalDataHandler);
  QTask_LinkQTaskEventHandlerFn(
    v1,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))AISquad_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(v1, DynCubeObj_eDynCubeObjRegisterQTaskEvent, AISquad_RegisterQTaskHandler);
  QTask_LinkQTaskEventHandlerFn(v1, DynCubeObj_eDynCubeObjRemoveQTaskEvent, AISquad_RemoveQTaskHandler);
  QTask_LinkQTaskEventHandlerFn(v1, MagicObj_eMagicObjEnterEvent, AISquad_MagicObjEnterEventHandler);
  v2 = ComputerObject_eDrawComputerObjectQTaskEvent;
  if ( ComputerObject_eDrawComputerObjectQTaskEvent == 512 )
  {
    v2 = QTask_NewQTaskEventFn(0x200u, "DrawComputerObject");
    v1 = AISquad_eQTaskType;
    ComputerObject_eDrawComputerObjectQTaskEvent = v2;
  }
  QTask_LinkQTaskEventHandlerFn(v1, v2, AISquad_DrawComputerObjectQTaskHandler);
  QTask_LinkQTaskEventHandlerFn(v1, 4, AISquad_ParentChangedHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 2, AISquad_DeleteHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 1, AISquad_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(
    v1,
    Level_eRegisterLevelScriptSymbolsEvent,
    AISquad_RegisterScriptSymbolsHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, Level_eRemoveLevelScriptSymbolsEvent, AISquad_RemoveScriptSymbolsHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, Level_eUpdateInternalDataAfterLoadEvent, sub_4A3570);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, Attach_eUpdateAttachmentEvent, AISquad_UpdateAttachmentHandler);
  QTask_LinkQTaskEventHandlerFn(
    v1,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveHandler);
  AISquad_RegisterScriptValues();
  AISquad_tSquadTypeCategoryEnumList.pfEnumItemsCallback = ParameterEnumList_EnumerateItemsCallback;
  AISquad_tSquadTypeCategoryEnumList.ptHead = (struct ParameterEnumItem_s *)&AISquad_tSquadTypeCategoryEnumList.ptMiddle;
  AISquad_tSquadTypeCategoryEnumList.ptTail = (struct ParameterEnumItem_s *)&AISquad_tSquadTypeCategoryEnumList;
  AISquad_tSquadTypeCategoryEnumList.ptMiddle = nullptr;
  v3 = Mem_AllocFn(18444, 4);
  v3[1] = 0;
  *v3 = 0;
  v3[4610] = "AIType_Offensive";
  Wildcard_CreateNFA("AIType_Offensive", v3 + 2, (char *)v3 + 10248);
  List_AddTail(v3, (int)&AISquad_tSquadTypeCategoryEnumList);
  v4 = Mem_AllocFn(18444, 4);
  v4[1] = 0;
  *v4 = 0;
  v4[4610] = "AIType_Defensive";
  Wildcard_CreateNFA("AIType_Defensive", v4 + 2, (char *)v4 + 10248);
  List_AddTail(v4, (int)&AISquad_tSquadTypeCategoryEnumList);
  v5 = Mem_AllocFn(18444, 4);
  v5[1] = 0;
  *v5 = 0;
  v5[4610] = "AIType_OnVehicle";
  Wildcard_CreateNFA("AIType_OnVehicle", v5 + 2, (char *)v5 + 10248);
  List_AddTail(v5, (int)&AISquad_tSquadTypeCategoryEnumList);
  v6 = (struct ParameterList_s *)Mem_AllocFn(232, 4);
  v7 = Level_eParameterTypeReal32;
  v6->ptParameterListItem = (struct ParameterListItem_s *)&v6[1];
  v6->nParameters = 0;
  v6->nMaxParameters = 11;
  AISquad_ptParameterList = v6;
  ParameterList_AddParameter(v6, 0x222Cu, v7, "Formation Distance", 7u, nullptr);
  ParameterList_AddParameter(
    AISquad_ptParameterList,
    0x2214u,
    ParameterEnumList_eParameterTypeInt32,
    "SquadType",
    7u,
    &AISquad_tSquadTypeCategoryEnumList);
  ParameterList_AddParameter(AISquad_ptParameterList, 0x221Cu, Level_eParameterTypeInt32, "AlarmTriggerID", 7u, nullptr);
  ParameterList_AddParameter(AISquad_ptParameterList, 0x2218u, Level_eParameterTypeInt32, "AlarmControlID", 7u, nullptr);
  ParameterList_AddParameter(
    AISquad_ptParameterList,
    0x2220u,
    Level_eParameterTypeInt32,
    "StationaryGunID",
    7u,
    nullptr);
  ParameterList_AddParameter(
    AISquad_ptParameterList,
    0x2238u,
    Level_eParameterTypeScriptFile,
    "Script File",
    2u,
    nullptr);
  ParameterList_AddParameter(
    AISquad_ptParameterList,
    0x2234u,
    Level_eParameterTypeReal32,
    "Max Run Distance Alarm/Gun (m)",
    7u,
    nullptr);
  ParameterList_AddParameter(
    AISquad_ptParameterList,
    0x2224u,
    Level_eParameterTypeInt32,
    "TargetTimeout (sec)",
    7u,
    nullptr);
  ParameterList_AddParameter(
    AISquad_ptParameterList,
    0x2228u,
    Level_eParameterTypeInt32,
    "TenseTimeout (sec)",
    7u,
    nullptr);
  LOWORD(v5) = AISquad_eQTaskType;
  QTask_LinkQTaskEventHandlerFn(
    AISquad_eQTaskType,
    Serialize_eGetSerializeParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))AISquad_GetSerializeParameterListHandler);
  QTask_LinkQTaskEventHandlerFn((unsigned __int16)v5, Serialize_eDeSerializeQTaskEvent, AISquad_DeSerializeHandler);
  QTask_LinkQTaskEventHandlerFn((unsigned __int16)v5, Serialize_eSerializeQTaskEvent, AISquad_SerializeHandler);
  v8 = (struct ParameterList_s *)Mem_AllocFn(172, 4);
  v9 = Level_eParameterTypebool8;
  v8->ptParameterListItem = (struct ParameterListItem_s *)&v8[1];
  v8->nParameters = 0;
  v8->nMaxParameters = 8;
  AISquad_ptSerializeParameterList = v8;
  ParameterList_AddParameter(v8, 0x2211u, v9, "Dead", 7u, nullptr);
  ParameterList_AddParameter(AISquad_ptSerializeParameterList, 0x21A8u, Level_eParameterTypeInt32, "Flags", 7u, nullptr);
  ParameterList_AddParameter(
    AISquad_ptSerializeParameterList,
    0x21C8u,
    Level_eParameterTypeInt32,
    "TenseTimer",
    7u,
    nullptr);
  ParameterList_AddParameter(
    AISquad_ptSerializeParameterList,
    0x21DCu,
    Level_eParameterTypeInt32,
    "RushTimer",
    7u,
    nullptr);
  ParameterList_AddParameter(
    AISquad_ptSerializeParameterList,
    0x21D4u,
    Level_eParameterTypeInt32,
    "DisallowIncreaseSuspicionTimer",
    7u,
    nullptr);
  ParameterList_AddParameter(
    AISquad_ptSerializeParameterList,
    0x21D8u,
    Level_eParameterTypeInt32,
    "SuspicionLevel",
    7u,
    nullptr);
  ParameterList_AddParameter(
    AISquad_ptSerializeParameterList,
    0x21A0u,
    Level_eParameterTypeInt32,
    "NumActions",
    7u,
    nullptr);
  ParameterList_AddParameter(
    AISquad_ptSerializeParameterList,
    0x1D40u,
    SerializeArray_eParameterType,
    "ActionStack",
    7u,
    (void *)0x460);
  AISquad_InitFormations();
  AISquad_InitVoiceTable();
  AISquad_ptRunHandlerProfileRegion = nullptr;
  AISquad_ptDefaultScript = Script_New("LOCAL:common/ai/squaddefault.qsc");
  Symbol_Register(
    "AISquad_nSquadState",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_Int,
    &AISquad_nScriptSquadState,
    4,
    QSCRIPT_SYMBOLCLASS_VARIABLE,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_FINITE);
  Symbol_Register(
    "AISquad_nEvent",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_Int,
    &AISquad_nScriptEvent,
    4,
    QSCRIPT_SYMBOLCLASS_VARIABLE,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_FINITE);
}

// source: j/0/humanai/aisquad.c:6495  [anchor-hash]
void __cdecl AISquad_Close()
{
  int v0; // esi
  int v1; // esi

  Symbol_Remove("AISquad_nSquadState");
  Symbol_Remove("AISquad_nEvent");
  QTaskList_Delete(AISquad_ptQTaskList);
  if ( AISquad_ptDefaultScript )
    Script_Delete(AISquad_ptDefaultScript);
  if ( AISquad_ptSerializeParameterList )
  {
    v0 = *(_DWORD *)((unsigned int)&AISquad_ptSerializeParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
  if ( AISquad_ptParameterList )
  {
    v1 = *(_DWORD *)((unsigned int)&AISquad_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v1);
    memset(*(void **)(v1 + 8), 0xCDu, *(_DWORD *)(v1 + 16));
    free((void *)v1);
  }
  QTask_DeleteQTaskType(AISquad_eQTaskType);
  AISquad_DeleteScriptValues();
  ParameterEnumList_DeAlloc(&AISquad_tSquadTypeCategoryEnumList);
}

// source: j/0/humanai/aisquad.c:6530  [anchor-callee]
void __cdecl AISquad_PopActionStack(
        struct QTask_s *ptQTask,
        struct AISquadActionChangeContext_s *ptActionChangeContext)
{
  struct QTask_s *ptHead; // eax
  struct QTaskNodeList_s *p_tQTaskChildren; // esi
  struct QReference_s *v4; // eax

  ptHead = ptQTask[215].tQTaskChildren.ptHead;
  if ( ptHead )
  {
    p_tQTaskChildren = &ptQTask[7 * (int)ptHead + 180].tQTaskChildren;
    ((void (__cdecl *)(struct QTask_s *, struct AISquadActionChangeContext_s *))ptQTask[7 * (int)ptHead + 186].ptParent)(
      ptQTask,
      ptActionChangeContext);
    v4 = (struct QReference_s *)p_tQTaskChildren[23].ptHead;
    if ( v4 )
    {
      QReference_Delete(v4, &QTask_tQTaskRefPool);
      p_tQTaskChildren[23].ptHead = nullptr;
    }
    --*(int *)&ptQTask[215].tQTaskChildren.ptHead;
  }
}

// source: j/0/humanai/aisquad.c:6554  [anchor-mhash]
struct QTask_s *__cdecl AISquad_PushOntoActionStack(
        struct QTask_s *ptQTask,
        struct AISquadAction_s *ptAction,
        struct AISquadActionChangeContext_s *ptActionChangeContext)
{
  struct QTask_s *ptHead; // ecx
  int v4; // ecx

  ptHead = ptQTask[215].tQTaskChildren.ptHead;
  if ( (int)ptHead < 4 )
  {
    qmemcpy(&ptQTask[7 * (int)ptHead + 187].tQTaskChildren, ptAction, 0x118u);
    v4 = 7 * (int)++*(int *)&ptQTask[215].tQTaskChildren.ptHead;
    return (struct QTask_s *)((int (__cdecl *)(struct QTask_s *, struct AISquadActionChangeContext_s *))ptQTask[v4 + 186].tQTaskRefList.ptMiddle)(
                               ptQTask,
                               ptActionChangeContext);
  }
  return ptQTask;
}

// source: j/0/humanai/aisquad.c:6580  [anchor-callee]
enum bool __cdecl AISquad_ClearActionStack(
        struct QTask_s *ptQTask,
        enum bool isPopMemberStacks,
        enum bool isDeserializing)
{
  enum bool result; // eax
  struct QTask_s *ptHead; // eax
  int v5; // eax
  struct QTaskNodeList_s *p_tQTaskChildren; // esi
  struct QReference_s *v7; // eax
  struct AISquadActionChangeContext_s tActionChangeContext; // [esp+8h] [ebp-DCh] BYREF

  tActionChangeContext.isPopMembersStacks = isPopMemberStacks;
  result = (enum bool)ptQTask[215].tQTaskChildren.ptHead;
  tActionChangeContext.eNextAction = AISQUAD_ACTION_IDLE;
  for ( tActionChangeContext.isDeserializing = isDeserializing;
        result;
        result = (enum bool)ptQTask[215].tQTaskChildren.ptHead )
  {
    ptHead = ptQTask[215].tQTaskChildren.ptHead;
    if ( ptHead )
    {
      v5 = 7 * (_DWORD)ptHead;
      p_tQTaskChildren = &ptQTask[v5 + 180].tQTaskChildren;
      ((void (__cdecl *)(struct QTask_s *, struct AISquadActionChangeContext_s *))ptQTask[v5 + 186].ptParent)(
        ptQTask,
        &tActionChangeContext);
      v7 = (struct QReference_s *)p_tQTaskChildren[23].ptHead;
      if ( v7 )
      {
        QReference_Delete(v7, &QTask_tQTaskRefPool);
        p_tQTaskChildren[23].ptHead = nullptr;
      }
      --*(int *)&ptQTask[215].tQTaskChildren.ptHead;
    }
  }
  return result;
}

// source: j/0/humanai/aisquad.c:6605  [anchor-hash]
struct QTask_s *__cdecl AISquad_ProcessEvents(struct QTask_s *ptQTask)
{
  if ( *(int *)&ptQTask[215].eQTaskType > 0 )
    return (struct QTask_s *)(*(int (__cdecl **)(struct QTask_s *))&ptQTask[7 * (int)ptQTask[215].tQTaskChildren.ptHead
                                                                          + 186].eQTaskType)(ptQTask);
  return ptQTask;
}

// source: j/0/humanai/aisquad.c:6624  [anchor-callee]
void __cdecl AISquad_RunActionStack(struct QTask_s *ptQTask)
{
  struct QTask_s *ptHead; // eax
  struct QTaskNodeList_s *p_tQTaskChildren; // esi
  struct QTask_s *ptPrev; // eax
  struct QReference_s *v4; // eax

  ptHead = ptQTask[215].tQTaskChildren.ptHead;
  if ( (int)ptHead > 0 )
  {
    p_tQTaskChildren = &ptQTask[7 * (int)ptHead + 180].tQTaskChildren;
    ptPrev = ptQTask[7 * (int)ptHead + 187].ptPrev;
    if ( ptPrev )
    {
      if ( !ptPrev->tQTaskChildren.ptHead )
      {
        v4 = (struct QReference_s *)p_tQTaskChildren[23].ptHead;
        if ( v4 )
        {
          QReference_Delete(v4, &QTask_tQTaskRefPool);
          p_tQTaskChildren[23].ptHead = nullptr;
        }
      }
    }
    else
    {
      ((void (__cdecl *)(struct QTask_s *))p_tQTaskChildren[21].ptTail)(ptQTask);
    }
  }
}

// source: j/0/humanai/aisquad.c:6660  [anchor-mhash]
enum bool __cdecl AISquad_TargetSeenBySquad(
        struct QTask_s *ptQTask,
        struct QTask_s *ptTargetQTask)
{
  struct QReference_s *ptMiddle; // esi
  int v3; // ecx
  struct QTaskNodeList_s *i; // edx

  ptMiddle = ptQTask[215].tQTaskRefList.ptMiddle;
  v3 = 0;
  if ( (int)ptMiddle <= 0 )
    return false;
  for ( i = &ptQTask[182].tQTaskChildren;
        !i->ptHead || i->ptHead->tQTaskChildren.ptHead != ptTargetQTask;
        i = (struct QTaskNodeList_s *)((char *)i + 40) )
  {
    if ( ++v3 >= (int)ptMiddle )
      return false;
  }
  return true;
}

// source: j/0/humanai/aisquad.c:6693  [anchor-callee]
enum bool __cdecl AISquad_TargetSeenByOtherSquads(struct QTask_s *ptQTask, struct QTask_s *ptTargetQTask)
{
  int nTask; // edx
  int v3; // edi
  struct QTask_s **i; // ebx
  struct QTask_s *v5; // eax
  int ptMiddle; // esi
  int v7; // ecx
  struct QTaskNodeList_s *p_tQTaskChildren; // edx

  nTask = AISquad_ptQTaskList->nTask;
  v3 = 0;
  if ( AISquad_ptQTaskList->nTask <= 0 )
    return false;
  for ( i = AISquad_ptQTaskList->ptQTask; ; ++i )
  {
    v5 = *i;
    if ( *i != ptQTask )
    {
      ptMiddle = (int)v5[215].tQTaskRefList.ptMiddle;
      v7 = 0;
      if ( ptMiddle > 0 )
        break;
    }
LABEL_10:
    if ( ++v3 >= nTask )
      return false;
  }
  p_tQTaskChildren = &v5[182].tQTaskChildren;
  while ( !p_tQTaskChildren->ptHead || p_tQTaskChildren->ptHead->tQTaskChildren.ptHead != ptTargetQTask )
  {
    ++v7;
    p_tQTaskChildren = (struct QTaskNodeList_s *)((char *)p_tQTaskChildren + 40);
    if ( v7 >= ptMiddle )
    {
      nTask = AISquad_ptQTaskList->nTask;
      goto LABEL_10;
    }
  }
  return true;
}

// source: j/0/humanai/aisquad.c:6724  [anchor-callee]
struct QTask_s *__cdecl AISquad_ReceiveEvent(
        struct QTask_s *ptQTask,
        struct AISquadEventContext_s *ptEvent)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct QTask_s *v24; };
    struct { int v25; };
    struct { int v26; };
    struct { char igi2_o3[4]; _BYTE v27[112]; };
    char igi2_extent[116];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *result; // eax
  int eEvent; // eax
  struct QReference_s *ptReferenceQTaskRef; // ecx
  struct QReference_s *ptMiddle; // esi
  int v7; // eax
  struct QTask_s *v8; // edx
  struct QTaskNodeList_s *p_tQTaskChildren; // ecx
  struct QTask_s *pxObject; // esi
  struct QTask_s *ptTail; // eax
  int v12; // esi
  int v13; // eax
  struct QTask_s *v14; // ecx
  char *v15; // eax
  _DWORD *v16; // ebx
  struct QTask_s *ptParent; // eax
  struct QReference_s **p_ptMiddle; // ecx
  char *v19; // eax
  struct QReference_s *v20; // eax
  struct QTask_s *v21; // eax
  struct QReference_s *v22; // eax
  int v23; // edx

  if ( AISquad_ptCurrentAISquad )
    result = *(struct QTask_s **)&ptQTask[215].eQTaskType;
  else
    result = ptQTask[215].ptParent;
  if ( (int)result >= 32 )
    return result;
  eEvent = ptEvent->eEvent;
  if ( ptEvent->eEvent == 21 || eEvent == 14 || eEvent == 22 )
    ptQTask[216].tQTaskChildren.ptHead = (struct QTask_s *)(30 * (int)ptQTask[218].tQTaskRefList.ptMiddle);
  if ( ptQTask[216].tQTaskRefList.ptTail )
  {
    result = (struct QTask_s *)ptEvent->eEvent;
    if ( ptEvent->eEvent >= 9 && ((int)result <= 11 || result == (struct QTask_s *)15) )
      return result;
  }
  if ( ptEvent->eEvent == 21 )
  {
    ptReferenceQTaskRef = ptEvent->ptReferenceQTaskRef;
    if ( ptReferenceQTaskRef )
    {
      ptMiddle = ptQTask[215].tQTaskRefList.ptMiddle;
      v7 = 0;
      if ( (int)ptMiddle <= 0 )
      {
LABEL_19:
        if ( (int)ptMiddle < 5 )
        {
          if ( !ptMiddle )
          {
            AISquad_PopMembersActionStacks(ptQTask);
            pxObject = (struct QTask_s *)ptEvent->ptReferenceQTaskRef->pxObject;
            if ( QTask_IsQTaskTypeDerived(pxObject->eQTaskType, HumanPlayer_eQTaskType) )
            {
              if ( AISquad_TargetSeenByOtherSquads(ptQTask, pxObject) == false )
              {
                ptTail = ptQTask[215].tQTaskChildren.ptTail;
                if ( ((unsigned __int8)ptTail & 4) == 0 )
                {
                  ptQTask[215].tQTaskChildren.ptTail = (struct QTask_s *)((unsigned int)ptTail | 4);
                  sub_4C9E00((int)pxObject);
                }
              }
            }
          }
          ptQTask[(int)&ptQTask[215].tQTaskRefList.ptMiddle[15].ptNext + 3].ptNext = nullptr;
          ptQTask[(int)ptQTask[215].tQTaskRefList.ptMiddle + 182].tQTaskChildren.ptHead = (struct QTask_s *)QTask_NewQTaskRef((struct QTask_s *)ptEvent->ptReferenceQTaskRef->pxObject);
          qmemcpy(
            &ptQTask[(int)(*(int *)&ptQTask[215].tQTaskRefList.ptMiddle)++ + 182].tQTaskChildren.ptTail,
            &ptEvent->tPosition,
            0x18u);
        }
      }
      else
      {
        v8 = (struct QTask_s *)ptReferenceQTaskRef->pxObject;
        p_tQTaskChildren = &ptQTask[182].tQTaskChildren;
        while ( p_tQTaskChildren->ptHead->tQTaskChildren.ptHead != v8 )
        {
          ++v7;
          p_tQTaskChildren = (struct QTaskNodeList_s *)((char *)p_tQTaskChildren + 40);
          if ( v7 >= (int)ptQTask[215].tQTaskRefList.ptMiddle )
            goto LABEL_19;
        }
        ptQTask[v7 + 183].ptNext = nullptr;
        qmemcpy(&ptQTask[v7 + 182].tQTaskChildren.ptTail, &ptEvent->tPosition, 0x18u);
      }
    }
  }
  v12 = 0;
  if ( !AISquad_ptCurrentAISquad )
  {
    v13 = *(_DWORD *)&ptQTask[215].eQTaskType;
    if ( v13 > 0 )
    {
      v14 = ptQTask + 3;
      while ( v14->ptNext != (struct QTask_s *)ptEvent->eEvent || ptEvent->nNumSquadMemberQTaskRefs != 1 )
      {
        ++v12;
        v14 = (struct QTask_s *)((char *)v14 + 112);
        if ( v12 >= (int)(*(_DWORD *)&ptQTask[215].eQTaskType) )
          goto LABEL_32;
      }
      result = (struct QTask_s *)ptEvent->aptSquadMemberQTaskRef[0]->pxObject;
      igi2_frame.v25 = *((_DWORD *)&ptQTask[3].tQTaskChildren.ptHead + 28 * v12);
      if ( igi2_frame.v25 < 8 )
      {
        result = (struct QTask_s *)QTask_NewQTaskRef(result);
        *((_DWORD *)&ptQTask[3].tQTaskChildren.ptMiddle + 28 * v12 + igi2_frame.v25) = result;
        ++*((_DWORD *)&ptQTask[3].tQTaskChildren.ptHead + 28 * v12);
      }
      return result;
    }
LABEL_32:
    igi2_frame.v24 = *(struct QTask_s **)&ptQTask[215].eQTaskType;
    *(_DWORD *)&ptQTask[215].eQTaskType = v13 + 1;
    v15 = (char *)ptQTask + 112 * v13;
    v16 = v15 + 120;
    *((_DWORD *)v15 + 30) = ptEvent->eEvent;
    *((_DWORD *)v15 + 31) = ptEvent->nPriority;
LABEL_42:
    v20 = ptEvent->ptReferenceQTaskRef;
    if ( v20 && (v21 = (struct QTask_s *)v20->pxObject) != nullptr )
      v16[11] = QTask_NewQTaskRef(v21);
    else
      v16[11] = 0;
    if ( ptEvent->nNumSquadMemberQTaskRefs == 1 )
    {
      v22 = QTask_NewQTaskRef((struct QTask_s *)ptEvent->aptSquadMemberQTaskRef[0]->pxObject);
      v16[2] = 1;
    }
    else
    {
      v22 = nullptr;
      v16[2] = 0;
    }
    v16[3] = v22;
    qmemcpy(v16 + 12, &ptEvent->tPosition, 0x20u);
    result = (struct QTask_s *)LODWORD(ptEvent->tDirection.vZ);
    v23 = (int)igi2_frame.v24;
    v16[20] = result;
    qmemcpy(v16 + 22, &ptEvent->uSpecificData, 0x18u);
    if ( (int)igi2_frame.v24 > 0 )
    {
      do
      {
        if ( (int)(v16[1]) <= (int)(*(v16 - 27)) )
          break;
        qmemcpy(igi2_frame.v27, v16, sizeof(igi2_frame.v27));
        result = (struct QTask_s *)(v16 - 28);
        qmemcpy(v16, v16 - 28, 0x70u);
        --v23;
        qmemcpy(v16 - 28, igi2_frame.v27, 0x70u);
      }
      while ( v23 > 0 );
    }
    return result;
  }
  ptParent = ptQTask[215].ptParent;
  if ( (int)ptParent <= 0 )
  {
LABEL_41:
    igi2_frame.v24 = ptQTask[215].ptParent;
    ptQTask[215].ptParent = (struct QTask_s *)((char *)&ptParent->ptNext + 1);
    v19 = (char *)ptQTask + 112 * (_DWORD)ptParent;
    v16 = v19 + 3704;
    *((_DWORD *)v19 + 926) = ptEvent->eEvent;
    *((_DWORD *)v19 + 927) = ptEvent->nPriority;
    goto LABEL_42;
  }
  p_ptMiddle = &ptQTask[92].tQTaskRefList.ptMiddle;
  while ( *p_ptMiddle != (struct QReference_s *)ptEvent->eEvent || ptEvent->nNumSquadMemberQTaskRefs != 1 )
  {
    ++v12;
    p_ptMiddle += 28;
    if ( v12 >= (int)ptQTask[215].ptParent )
      goto LABEL_41;
  }
  result = (struct QTask_s *)ptEvent->aptSquadMemberQTaskRef[0]->pxObject;
  igi2_frame.v26 = *((_DWORD *)&ptQTask[92].ptParent + 28 * v12);
  if ( igi2_frame.v26 < 8 )
  {
    result = (struct QTask_s *)QTask_NewQTaskRef(result);
    *((_DWORD *)&ptQTask[92].eQTaskType + 28 * v12 + igi2_frame.v26) = result;
    ++*((_DWORD *)&ptQTask[92].ptParent + 28 * v12);
  }
  return result;
}

// source: j/0/humanai/aisquad.c:6970  [anchor-callee]
enum AISquadActions_e __cdecl AISquad_GetState(struct QTask_s *ptQTask)
{
  struct QTask_s *ptHead; // eax

  ptHead = ptQTask[215].tQTaskChildren.ptHead;
  if ( (int)ptHead <= 0 )
    return AISQUAD_ACTION_IDLE;
  else
    return (enum AISquadActions_e)ptQTask[7 * (int)ptHead + 187].ptNext;
}

// source: j/0/humanai/aisquad.c:6995  [anchor-mhash]
struct QTask_s *__cdecl AISquad_GetTargetQTask(struct QTask_s *ptQTask, int iI)
{
  if ( (int)ptQTask[215].tQTaskRefList.ptMiddle <= iI )
    return nullptr;
  else
    return ptQTask[iI + 182].tQTaskChildren.ptHead->tQTaskChildren.ptHead;
}

// source: j/0/humanai/aisquad.c:7011  [anchor-mhash]
enum bool __cdecl AISquad_GetLastTargetPosition(
        struct QTask_s *ptQTask,
        int iTarget,
        struct real64x3_t *ptReal64x3)
{
  if ( (int)ptQTask[215].tQTaskRefList.ptMiddle <= iTarget )
    return false;
  qmemcpy(ptReal64x3, &ptQTask[iTarget + 182].tQTaskChildren.ptTail, sizeof(struct real64x3_t));
  return true;
}

// source: j/0/humanai/aisquad.c:7037  [size]
enum AISquadType_e __cdecl AISquad_GetSquadType(struct QTask_s *ptQTask)
{
  return (enum AISquadType_e)ptQTask[218].ptPrev;
}

// source: j/0/humanai/aisquad.c:7054  [anchor-mhash]
int __cdecl AISquad_GetNumberOfMembersInPose(struct QTask_s *ptQTask, int ePose)
{
  int result; // eax
  int *p_ptParent; // edi
  struct QReference_s *ptTail; // ebx
  int *v5; // edx
  int v6; // esi
  int v7; // ecx

  result = 0;
  if ( (int)ptQTask[215].tQTaskRefList.ptTail > 0 )
  {
    p_ptParent = (int *)&ptQTask[1].ptParent;
    ptTail = ptQTask[215].tQTaskRefList.ptTail;
    do
    {
      if ( *p_ptParent > 0 )
      {
        v5 = p_ptParent - 8;
        v6 = *p_ptParent;
        do
        {
          v7 = *(_DWORD *)(*v5 + 8);
          if ( v7 )
          {
            if ( *(_DWORD *)(*(_DWORD *)(v7 + 32) + 1316) == ePose )
              ++result;
          }
          ++v5;
          --v6;
        }
        while ( v6 );
      }
      p_ptParent += 10;
      ptTail = (struct QReference_s *)((char *)ptTail - 1);
    }
    while ( ptTail );
  }
  return result;
}

// source: j/0/humanai/aisquad.c:7096  [anchor-callee]
void __cdecl AISquad_SetMemberFlags(struct QTask_s *ptQTask, int bFlags)
{
  int v2; // edi
  struct QTask_s **p_ptParent; // esi
  int v4; // edx
  struct QTask_s **v5; // ecx
  struct QTask_s *ptHead; // eax

  v2 = 0;
  if ( (int)ptQTask[215].tQTaskRefList.ptTail > 0 )
  {
    p_ptParent = &ptQTask[1].ptParent;
    do
    {
      v4 = 0;
      if ( (int)*p_ptParent > 0 )
      {
        v5 = p_ptParent - 8;
        do
        {
          ptHead = (*v5)->tQTaskChildren.ptHead;
          if ( ptHead )
            ptHead[99].tQTaskRefList.ptHead = (struct QReference_s *)((int)ptHead[99].tQTaskRefList.ptHead | bFlags);
          ++v4;
          ++v5;
        }
        while ( v4 < (int)*p_ptParent );
      }
      ++v2;
      p_ptParent += 10;
    }
    while ( v2 < (int)ptQTask[215].tQTaskRefList.ptTail );
  }
}

// source: j/0/humanai/aisquad.c:7129  [anchor-callee]
enum bool __cdecl AISquad_IsTeamLeader(
        struct QTask_s *ptSquadQTask,
        struct QTask_s *ptMemberQTask)
{
  struct QReference_s *ptTail; // esi
  int v3; // edx
  struct QTask_s *i; // eax
  struct QTask_s *v5; // ecx

  ptTail = ptSquadQTask[215].tQTaskRefList.ptTail;
  v3 = 0;
  if ( (int)ptTail <= 0 )
    return false;
  for ( i = ptSquadQTask + 1; ; ++i )
  {
    v5 = i->ptParent ? i->ptNext->tQTaskChildren.ptHead : nullptr;
    if ( ptMemberQTask == v5 )
      break;
    if ( ++v3 >= (int)ptTail )
      return false;
  }
  return true;
}

// source: j/0/humanai/aisquad.c:7233  [size~]
int __cdecl AISquad_RefreshTeamFormationPositions(struct QTask_s *ptSquadQTask, int iTeam)
{
  int v2; // edi
  int v3; // ecx
  bool v4; // sf
  struct AISquadEventContext_s ptQTask; // [esp+8h] [ebp-70h] BYREF

  if ( !*(_DWORD *)(iTeam + 8660) )
  {
    v2 = *(_DWORD *)(iTeam + 8664) + 300;
    v3 = v2;
    v4 = (int)(*(_DWORD *)(iTeam + 8664) - 330) < 0;
    *(_DWORD *)(iTeam + 8660) = 90;
    *(_DWORD *)(iTeam + 8664) = v2;
    if ( !(v4 ^ __OFSUB__(v2, 630) | (v2 == 630)) )
    {
      if ( v2 >= 930 )
        v3 = 930;
      *(_DWORD *)(iTeam + 8664) = v3;
      ptQTask.eEvent = 46;
      memset(&ptQTask.nPriority, 0, 12);
      ptQTask.ptReferenceQTaskRef = nullptr;
      qmemcpy(&ptQTask.tPosition, ptSquadQTask, sizeof(ptQTask.tPosition));
      return (int)AISquad_ReceiveEvent((struct QTask_s *)iTeam, &ptQTask);
    }
  }
  return iTeam;
}
