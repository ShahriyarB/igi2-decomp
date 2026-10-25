/* j/0/objects/scamera.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/objects/scamera.c:289  [size]
void __cdecl SCamera_GetSerializeParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = SCamera_ptSerializeParameterList;
}

// source: j/0/objects/scamera.c:307  [size]
void __cdecl SCameraLens_GetSerializeParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = SCameraLens_ptSerializeParameterList;
}

// source: j/0/objects/scamera.c:325  [anchor-mhash]
void __cdecl SCameraLens_DeSerializeHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ((void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[Serialize_eDeSerializeQTaskEvent][SectorInteriorObject_eQTaskType].pfHandler)(
    ptQTask,
    pxContext);
  QTask_DeleteQTaskAndQTaskRefSafe((struct QReference_s **)&ptQTask[512].eQTaskType);
  QTask_DeleteQTaskAndQTaskRefSafe((struct QReference_s **)&ptQTask[512].ptParent);
  QTask_DeleteQTaskAndQTaskRefSafe(&ptQTask[512].tQTaskRefList.ptTail);
  AIDetection_ClearDetection((struct AIDetection_s *)&ptQTask[11].ptParent);
}

// source: j/0/objects/scamera.c:345  [anchor-mhash]
void __cdecl SCamera_DeSerializeHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct LODVirModel_s *LODVirModelExistsFn; // eax
  struct ModelObj_s *ptTail; // esi
  struct QTask_s **p_ptMiddle; // esi

  ((void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[Serialize_eDeSerializeQTaskEvent][SectorInteriorObject_eQTaskType].pfHandler)(
    ptQTask,
    pxContext);
  if ( LOBYTE(ptQTask[11].tQTaskChildren.ptMiddle) )
  {
    LODVirModelExistsFn = MTP_GetLODVirModelExistsFn((char *)&ptQTask[9].ptParent);
    ptTail = (struct ModelObj_s *)ptQTask[10].tQTaskRefList.ptTail;
    if ( LODVirModelExistsFn == ptTail->ptLODVirModel )
      return;
  }
  else
  {
    LODVirModelExistsFn = MTP_GetLODVirModelExistsFn((char *)&ptQTask[9].tQTaskChildren.ptTail);
    ptTail = (struct ModelObj_s *)ptQTask[10].tQTaskRefList.ptTail;
    if ( LODVirModelExistsFn == ptTail->ptLODVirModel )
      return;
  }
  ModelObj_SetLODVirModel(ptTail, LODVirModelExistsFn, false);
  p_ptMiddle = &ptTail[1].tDynCubeObj.tQObj.tQTask.tQTaskChildren.ptMiddle;
  *p_ptMiddle = nullptr;
  p_ptMiddle[1] = nullptr;
  p_ptMiddle[2] = nullptr;
  p_ptMiddle[3] = nullptr;
  p_ptMiddle[4] = nullptr;
}

// source: j/0/objects/scamera.c:383  [anchor-mhash]
void __cdecl SCamera_SerializeHandler(struct QTask_s *ptQTask, void *pxContext)
{
  Serialize_SerializeChild(ptQTask, (struct QTask_s *)ptQTask[10].tQTaskRefList.ptTail, pxContext);
  ((void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[Serialize_eSerializeQTaskEvent][SectorInteriorObject_eQTaskType].pfHandler)(
    ptQTask,
    pxContext);
}

// source: j/0/objects/scamera.c:400  [anchor-mhash]
struct QTask_s *__cdecl SCamera_GetTargetPos(
        struct real64x3_t *ptPosition,
        struct QTask_s *ptTargetQTask)
{
  unsigned __int16 eQTaskType; // dx
  struct QTask_s *result; // eax

  eQTaskType = ptTargetQTask->eQTaskType;
  result = (struct QTask_s *)QTask_IsQTaskTypeDerived(eQTaskType, Human_eQTaskType);
  if ( result )
    return (struct QTask_s *)HumanView_GetOriginalViewPosition(ptPosition, ptTargetQTask);
  if ( eQTaskType == SCamera_eQTaskType )
    qmemcpy(ptPosition, &ptTargetQTask[8], sizeof(struct real64x3_t));
  return result;
}

// source: j/0/objects/scamera.c:449  [anchor-strings]
void __cdecl SCamera_SCameraLensPlayDetectionSound(struct QTask_s *ptQTask)
{
  struct QReference_s *ptParent; // eax
  struct QTask_s *ptPrev; // ebp
  struct QReference_s **p_ptParent; // esi
  void *pxObject; // ebx
  struct QTask_s *v5; // eax
  char *v6; // eax
  struct QTask_s *v7; // eax

  ptParent = (struct QReference_s *)ptQTask[512].ptParent;
  ptPrev = ptQTask[513].ptPrev;
  p_ptParent = (struct QReference_s **)&ptQTask[512].ptParent;
  pxObject = nullptr;
  if ( ptParent )
  {
    pxObject = ptParent->pxObject;
    if ( !pxObject )
    {
      QReference_Delete(ptParent, &QTask_tQTaskRefPool);
      *p_ptParent = nullptr;
    }
  }
  if ( ptPrev[11].ptPrev )
  {
    ptQTask[11].ptParent = (struct QTask_s *)((int)ptQTask[11].ptParent | 2);
    if ( !pxObject )
    {
      v5 = SoundSys_NewSoundFn(ptQTask, "camera_beep_s");
      *p_ptParent = QTask_NewQTaskRef(v5);
    }
  }
  else
  {
    ptQTask[11].ptParent = (struct QTask_s *)((int)ptQTask[11].ptParent & ~2u);
    QTask_DeleteQTaskAndQTaskRefSafe(p_ptParent);
  }
  if ( BYTE1(ptPrev[11].ptNext) )
  {
    if ( !*(_DWORD *)&ptQTask[512].eQTaskType )
    {
      if ( *(_DWORD *)&ptPrev[10].eQTaskType )
        v6 = "camera_beep_al";
      else
        v6 = "camera_beep_l";
      v7 = SoundSys_NewSoundFn(ptQTask, v6);
      *(_DWORD *)&ptQTask[512].eQTaskType = QTask_NewQTaskRef(v7);
    }
  }
  else
  {
    QTask_DeleteQTaskAndQTaskRefSafe((struct QReference_s **)&ptQTask[512].eQTaskType);
  }
}

// source: j/0/objects/scamera.c:523  [anchor-strings]
void __cdecl SCamera_RotateLens(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct real64x3_t v29; };
    struct { char igi2_o1[40]; struct real64x3_t tTargetPos; };
    struct { char igi2_o2[68]; struct QTask_s *vOldGamma; };
    char igi2_extent[72];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *ptPrev; // eax
  struct QTask_s *v3; // ebx
  struct QTask_s *ptHead; // edi
  struct QTask_s *ptParent; // eax
  struct QTask_s *ptNext; // esi
  unsigned __int16 v7; // cx
  int v8; // edx
  struct QReference_s *v9; // ecx
  struct QReference_s *v10; // edx
  int i; // eax
  bool v12; // zf
  enum GameDifficulty_e eDifficultyLevel; // edx
  struct QTask_s *v14; // eax
  unsigned __int16 eQTaskType; // dx
  double v16; // st7
  double v17; // st6
  double v18; // st5
  double v19; // st7
  double v20; // st6
  double v21; // st7
  struct QReference_s *v22; // eax
  struct QReference_s *ptMiddle; // eax
  struct QTask_s *v24; // eax
  double v25; // st7
  double v26; // st7
  struct QTask_s *ptTail; // ecx
  struct QTask_s *v28; // eax
  struct QTask_s *ptQTaska = *(struct QTask_s * *)&ptQTask; // [esp+34h] [ebp+4h] ARGSLOT
  struct QTask_s *ptQTaskc = *(struct QTask_s * *)&ptQTask; // [esp+34h] [ebp+4h] ARGSLOT
  int ptQTaskb = *(int *)&ptQTask; // [esp+34h] [ebp+4h] ARGSLOT

  ptPrev = ptQTask[8].ptPrev;
  v3 = ptQTask[513].ptPrev;
  ptHead = nullptr;
  BYTE1(v3[11].ptNext) = 0;
  *(_DWORD *)&v3[10].eQTaskType = 0;
  igi2_frame.vOldGamma = ptPrev;
  ptParent = ptQTask[12].ptParent;
  ptNext = ptParent->ptNext;
  if ( !ptParent->ptNext )
    goto LABEL_15;
  v7 = HumanSoldier_eQTaskType;
  while ( 2 )
  {
    v8 = 0;
    while ( !*((_BYTE *)&ptParent[1].tQTaskChildren.ptHead + v8 + 3) )
    {
      if ( ++v8 >= 3 )
        goto LABEL_11;
    }
    ptHead = ptParent->tQTaskChildren.ptHead->tQTaskChildren.ptHead;
    if ( QTask_IsQTaskTypeDerived(ptHead->eQTaskType, v7) == false )
    {
LABEL_14:
      *(_DWORD *)&v3[10].eQTaskType = 1;
      break;
    }
    if ( !BYTE1(ptHead[75].tQTaskRefList.ptTail) || v3[11].ptPrev )
    {
      BYTE1(ptHead[75].tQTaskRefList.ptTail) = 1;
      goto LABEL_14;
    }
    ptHead = nullptr;
LABEL_11:
    ptParent = ptNext;
    ptNext = ptNext->ptNext;
    if ( ptNext )
      continue;
    break;
  }
LABEL_15:
  v9 = ptQTask[12].tQTaskRefList.ptHead;
  v10 = v9->ptNext;
  if ( v9->ptNext )
  {
    while ( 2 )
    {
      for ( i = 0; i < 3; ++i )
      {
        if ( *((_BYTE *)&v9[4].ptNext + i + 3) )
        {
          ptHead = *((struct QTask_s **)v9->pxObject + 2);
          *(_DWORD *)&v3[10].eQTaskType = 0;
          goto LABEL_22;
        }
      }
      v9 = v10;
      v10 = v10->ptNext;
      if ( v10 )
        continue;
      break;
    }
  }
LABEL_22:
  if ( ptHead )
  {
    if ( (struct QTask_s *)ptQTask[512].tQTaskRefList.ptHead != ptHead )
    {
      v12 = Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER;
      ptQTask[512].tQTaskRefList.ptHead = (struct QReference_s *)ptHead;
      if ( v12 )
      {
        v3[11].ptPrev = nullptr;
      }
      else
      {
        eDifficultyLevel = Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eDifficultyLevel;
        igi2_frame.tTargetPos.vX = 0.007812501851731213;
        LODWORD(igi2_frame.tTargetPos.vY) = 1061158912;
        *(_QWORD *)&igi2_frame.tTargetPos.vX = (__int64)(*((float *)&igi2_frame.tTargetPos.vX + eDifficultyLevel) * 90.0);
        v3[11].ptPrev = (struct QTask_s *)LODWORD(igi2_frame.tTargetPos.vX);
      }
    }
    v14 = v3[11].ptPrev;
    if ( v14 )
      v3[11].ptPrev = (struct QTask_s *)((char *)v14 - 1);
    if ( !v3[11].ptPrev )
      BYTE1(v3[11].ptNext) = 1;
    eQTaskType = ptHead->eQTaskType;
    if ( QTask_IsQTaskTypeDerived(eQTaskType, Human_eQTaskType) )
    {
      HumanView_GetOriginalViewPosition(&igi2_frame.tTargetPos, ptHead);
    }
    else if ( eQTaskType == SCamera_eQTaskType )
    {
      qmemcpy(&igi2_frame.tTargetPos, &ptHead[8], sizeof(igi2_frame.tTargetPos));
    }
    v16 = igi2_frame.tTargetPos.vX - *(double *)&ptQTask[1].ptNext;
    v17 = igi2_frame.tTargetPos.vY - *(double *)&ptQTask[1].tQTaskChildren.ptHead;
    v18 = igi2_frame.tTargetPos.vZ - *(double *)&ptQTask[1].tQTaskChildren.ptTail;
    igi2_frame.tTargetPos.vX = *(float *)&ptQTask[3].tQTaskRefList.ptTail * v18
                  + *(float *)&ptQTask[3].tQTaskChildren.ptTail * v17
                  + *(float *)&ptQTask[3].ptPrev * v16;
    igi2_frame.tTargetPos.vY = *(float *)&ptQTask[3].ptParent * v18
                  + *(float *)&ptQTask[3].tQTaskRefList.ptHead * v17
                  + *(float *)&ptQTask[3].tQTaskChildren.ptHead * v16;
    igi2_frame.tTargetPos.vZ = *(float *)&ptQTask[3].eQTaskType * v18
                  + *(float *)&ptQTask[3].tQTaskRefList.ptMiddle * v17
                  + *(float *)&ptQTask[3].tQTaskChildren.ptMiddle * v16;
    qmemcpy(&igi2_frame.v29, &igi2_frame.tTargetPos, sizeof(igi2_frame.v29));
    v19 = GameFunctions_CalcGamma(igi2_frame.v29);
    v20 = v19;
    if ( v19 < 0.0 )
      v20 = -v19;
    if ( v20 > 0.0872664675116539 )
    {
      if ( v19 >= -0.013089969754219055 )
      {
        if ( v19 > 0.013089969754219055 )
          v19 = 0.013089969754219055;
      }
      else
      {
        v19 = -0.013089969754219055;
      }
      *(float *)&ptQTaska = v19 + *(float *)&ptQTask[8].ptPrev;
      ptQTask[8].ptPrev = ptQTaska;
      LODWORD(igi2_frame.tTargetPos.vX) = -SLOWORD(v3[10].tQTaskChildren.ptHead);
      v21 = (double)SLODWORD(igi2_frame.tTargetPos.vX) * 0.01745329238474369;
      if ( v21 <= *(float *)&ptQTaska )
      {
        LODWORD(igi2_frame.tTargetPos.vX) = SHIWORD(v3[10].tQTaskChildren.ptHead);
        v21 = (double)SLODWORD(igi2_frame.tTargetPos.vX) * 0.01745329238474369;
        if ( v21 >= *(float *)&ptQTaska )
          v21 = *(float *)&ptQTaska;
      }
      *(float *)&ptQTask[8].ptPrev = v21;
    }
  }
  else
  {
    v3[11].ptPrev = nullptr;
    if ( ptQTask[512].tQTaskRefList.ptHead )
    {
      v22 = Game_eGameMode != GAME_GAMEMODE_MULTIPLAYER ? (struct QReference_s *)0xFFFFFF10 : nullptr;
      ptQTask[512].tQTaskRefList.ptHead = nullptr;
      ptQTask[512].tQTaskRefList.ptMiddle = v22 + 25;
    }
    ptMiddle = ptQTask[512].tQTaskRefList.ptMiddle;
    if ( ptMiddle )
      ptQTask[512].tQTaskRefList.ptMiddle = (struct QReference_s *)((char *)ptMiddle - 1);
    if ( !ptQTask[512].tQTaskRefList.ptMiddle )
    {
      if ( !ptQTask[8].tQTaskChildren.ptTail )
      {
        ptQTaskc = (struct QTask_s *)SHIWORD(v3[10].tQTaskChildren.ptHead);
        ptQTask[8].tQTaskChildren.ptTail = (struct QTask_s *)1;
        *(float *)&ptQTask[8].tQTaskChildren.ptHead = (double)(int)ptQTaskc * 0.01745329238474369;
      }
      v24 = ptQTask[8].tQTaskChildren.ptMiddle;
      if ( v24 )
      {
        ptQTask[8].tQTaskChildren.ptMiddle = (struct QTask_s *)((char *)v24 - 1);
      }
      else
      {
        if ( *(float *)&ptQTask[8].ptPrev >= (double)*(float *)&ptQTask[8].tQTaskChildren.ptHead )
        {
          if ( *(float *)&ptQTask[8].ptPrev > (double)*(float *)&ptQTask[8].tQTaskChildren.ptHead )
          {
            v26 = *(float *)&ptQTask[8].ptPrev
                - (double)SLOWORD(v3[10].tQTaskChildren.ptMiddle) * 0.01745329238474369 * 0.03333333507180214;
            *(float *)&ptQTask[8].ptPrev = v26;
            if ( v26 < *(float *)&ptQTask[8].tQTaskChildren.ptHead )
              ptQTask[8].ptPrev = ptQTask[8].tQTaskChildren.ptHead;
          }
        }
        else
        {
          v25 = (double)SLOWORD(v3[10].tQTaskChildren.ptMiddle) * 0.01745329238474369 * 0.03333333507180214
              + *(float *)&ptQTask[8].ptPrev;
          *(float *)&ptQTask[8].ptPrev = v25;
          if ( v25 > *(float *)&ptQTask[8].tQTaskChildren.ptHead )
            ptQTask[8].ptPrev = ptQTask[8].tQTaskChildren.ptHead;
        }
        if ( *(float *)&ptQTask[8].ptPrev == *(float *)&ptQTask[8].tQTaskChildren.ptHead )
        {
          *(_QWORD *)&igi2_frame.tTargetPos.vX = (__int64)(*(float *)&v3[10].tQTaskChildren.ptTail * 30.0);
          ptTail = ptQTask[8].tQTaskChildren.ptTail;
          ptQTask[8].tQTaskChildren.ptMiddle = (struct QTask_s *)LODWORD(igi2_frame.tTargetPos.vX);
          if ( ptTail == (struct QTask_s *)-1 )
          {
            ptQTaskb = SHIWORD(v3[10].tQTaskChildren.ptHead);
            ptQTask[8].tQTaskChildren.ptTail = (struct QTask_s *)1;
          }
          else
          {
            ptQTaskb = -SLOWORD(v3[10].tQTaskChildren.ptHead);
            ptQTask[8].tQTaskChildren.ptTail = (struct QTask_s *)-1;
          }
          *(float *)&ptQTask[8].tQTaskChildren.ptHead = (double)ptQTaskb * 0.01745329238474369;
        }
      }
    }
  }
  if ( *(float *)&igi2_frame.vOldGamma == *(float *)&ptQTask[8].ptPrev )
  {
    QTask_DeleteQTaskAndQTaskRefSafe(&ptQTask[512].tQTaskRefList.ptTail);
  }
  else if ( !ptQTask[512].tQTaskRefList.ptTail )
  {
    v28 = SoundSys_NewSoundFn(ptQTask, "camera_move");
    ptQTask[512].tQTaskRefList.ptTail = QTask_NewQTaskRef(v28);
  }
}

// source: j/0/objects/scamera.c:783  [anchor-mhash]
void __cdecl SCamera_SCameraLensCreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { float ptDynCubeObj; };
    struct { char igi2_o1[24]; struct real64x3_t ptPos; };
    char igi2_extent[52];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  double v2; // st7
  double v3; // st7
  int *v4; // eax
  int v5; // eax
  double v6; // st6
  bool v7; // zf
  int *p_ptParent; // esi
  struct AIDetection_s *v9; // ecx
  int v10; // eax

  memset(&igi2_frame.ptPos, 0, sizeof(igi2_frame.ptPos));
  QTaskList_Register(GameFunctions_ptExplosionQTaskList, (struct QTaskList_s *)ptQTask);
  QTaskList_Register(SCamera_ptSCameraLensQTaskList, (struct QTaskList_s *)ptQTask);
  ModelObj_Init((struct ModelObj_s *)ptQTask, Game_ptGame->ptWorld, nullptr);
  ptQTask[7].tQTaskChildren.ptHead = nullptr;
  ptQTask[7].tQTaskChildren.ptMiddle = (struct QTask_s *)2;
  ptQTask[7].tQTaskRefList.ptHead = nullptr;
  ptQTask[7].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[7].tQTaskRefList.ptTail = nullptr;
  ptQTask[7].ptParent = nullptr;
  *(_DWORD *)&ptQTask[7].eQTaskType = 0;
  if ( *(float *)&ptQTask[6].tQTaskChildren.ptHead <= (double)*(float *)&ptQTask[6].tQTaskChildren.ptMiddle )
    v2 = *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
  else
    v2 = *(float *)&ptQTask[6].tQTaskChildren.ptHead;
  if ( v2 >= *(float *)&ptQTask[6].ptPrev )
  {
    if ( *(float *)&ptQTask[6].tQTaskChildren.ptHead <= (double)*(float *)&ptQTask[6].tQTaskChildren.ptMiddle )
      v3 = *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
    else
      v3 = *(float *)&ptQTask[6].tQTaskChildren.ptHead;
  }
  else
  {
    v3 = *(float *)&ptQTask[6].ptPrev;
  }
  v4 = *(int **)&ptQTask[2].eQTaskType;
  if ( v4 && (v5 = *v4) != 0 )
    v6 = *(float *)(*(_DWORD *)(*(_DWORD *)(v5 + 12) + 12) + 120);
  else
    v6 = 1.0;
  igi2_frame.ptDynCubeObj = v3 * v6;
  World_RegisterDynCubeObjFirstTimeRadius(
    Game_ptGame->ptWorld,
    (struct DynCubeObj_s *)ptQTask,
    &igi2_frame.ptPos,
    igi2_frame.ptDynCubeObj,
    WORLD_DYNCUBETREE_CATEGORY_STATIONARY);
  if ( ptQTask[7].tQTaskChildren.ptTail )
  {
    ptQTask[2].tQTaskRefList.ptHead = nullptr;
    ptQTask[2].tQTaskRefList.ptMiddle = nullptr;
  }
  else
  {
    SectorObject_RegisterInteriorDynCubeObjSpecificSectorObject(
      (struct World_s *)ptQTask[2].ptParent,
      nullptr,
      (struct DynCubeObj_s *)ptQTask,
      (struct real64x3_t *)&ptQTask[1]);
  }
  v7 = Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER;
  p_ptParent = (int *)&ptQTask[11].ptParent;
  ptQTask[513].ptPrev = ptQTask->ptParent;
  ptQTask[8].ptNext = nullptr;
  ptQTask[8].ptPrev = nullptr;
  ptQTask[8].tQTaskChildren.ptHead = nullptr;
  ptQTask[8].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[8].tQTaskChildren.ptTail = nullptr;
  v9 = (struct AIDetection_s *)&ptQTask[11].ptParent;
  if ( v7 )
    AIDetection_InitDetection(
      v9,
      NetMission_eDefendingTeam,
      4u,
      SCamera_bAIDetectionQTaskMask | Human_bAIDetectionQTaskMask,
      4,
      8);
  else
    AIDetection_InitDetection(v9, 1, 6u, SCamera_bAIDetectionQTaskMask | Human_bAIDetectionQTaskMask, 4, 8);
  v10 = *p_ptParent;
  ptQTask[512].tQTaskRefList.ptHead = nullptr;
  ptQTask[512].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[512].tQTaskRefList.ptTail = nullptr;
  ptQTask[512].ptParent = nullptr;
  *(_DWORD *)&ptQTask[512].eQTaskType = 0;
  ptQTask[8].tQTaskRefList.ptHead = nullptr;
  LOBYTE(ptQTask[513].ptNext) = 0;
  ptQTask[513].tQTaskChildren.ptHead = nullptr;
  LOBYTE(ptQTask[513].tQTaskChildren.ptTail) = 0;
  ptQTask[513].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[513].tQTaskRefList.ptHead = nullptr;
  BYTE1(ptQTask[513].tQTaskChildren.ptTail) = 0;
  ptQTask[8].tQTaskRefList.ptMiddle = (struct QReference_s *)1056964608;
  *p_ptParent = v10 | 1;
}

// source: j/0/objects/scamera.c:863  [anchor-callee]
float __cdecl SCamera_LimitAngle(float vAngle)
{
  double v1; // st7

  v1 = vAngle - (double)(int)(__int64)(vAngle * 0.15915493667125702) * 6.2831854820251465;
  if ( v1 >= -3.1415927410125732 )
  {
    if ( v1 >= 3.1415927410125732 )
      return v1 - 6.2831854820251465;
  }
  else
  {
    return v1 + 6.2831854820251465;
  }
  return v1;
}

// source: j/0/objects/scamera.c:889  [anchor-strings]
void __cdecl SCamera_SCameraLensRunHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { float vBeta; };
    struct { char igi2_o1[28]; struct real64x3_t ptPos; };
    struct { char igi2_o2[52]; struct HumanAIEventContext_t ptEventContext; };
    char igi2_extent[116];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *ptHead; // eax
  struct QTask_s *ptPrev; // edi
  int v4; // eax
  struct QTask_s *ptMiddle; // eax
  struct QReference_s *v6; // eax
  struct QReference_s *v7; // eax
  struct QTask_s *ptTail; // edx
  double v9; // st7
  double v10; // st7
  double v11; // st7
  double v12; // st7
  double v13; // st7
  double v14; // st7
  bool v15; // zf
  struct LODVirModel_s *LODVirModelExistsFn; // eax
  struct QTask_s *v17; // ebp
  int v18; // ecx
  int v19; // edx
  struct QTask_s *v20; // eax
  void (__cdecl *pfHandler)(int); // eax
  int v22; // edx
  struct QTask_s *ptQTaska = *(struct QTask_s * *)&ptQTask; // [esp+78h] [ebp+4h] ARGSLOT

  ptHead = ptQTask[513].tQTaskChildren.ptHead;
  ptPrev = ptQTask[513].ptPrev;
  if ( ptHead )
  {
    ptQTask[513].tQTaskChildren.ptHead = (struct QTask_s *)((char *)ptHead - 1);
  }
  else
  {
    v4 = LOBYTE(ptQTask[513].tQTaskChildren.ptTail) ^ 1;
    ptQTask[513].tQTaskChildren.ptHead = (struct QTask_s *)7;
    LOBYTE(ptQTask[513].tQTaskChildren.ptTail) = v4;
  }
  ptMiddle = ptQTask[513].tQTaskChildren.ptMiddle;
  if ( ptMiddle )
  {
    ptQTask[513].tQTaskChildren.ptMiddle = (struct QTask_s *)((char *)ptMiddle - 1);
  }
  else
  {
    v6 = (struct QReference_s *)((char *)&ptQTask[513].tQTaskRefList.ptHead->ptNext + 1);
    ptQTask[513].tQTaskChildren.ptMiddle = (struct QTask_s *)7;
    ptQTask[513].tQTaskRefList.ptHead = v6;
    if ( (int)v6 > ComputerMenu_tComputerMenuResource.atQSpriteHilight[18].nQAnimframes - 1 )
      ptQTask[513].tQTaskRefList.ptHead = nullptr;
  }
  if ( BYTE1(ptPrev[11].ptNext) )
  {
    if ( !BYTE2(ptPrev[11].ptNext) )
    {
      if ( dword_834DED8 )
      {
        if ( *(_DWORD *)(dword_834DED8 + 776) )
        {
          v7 = ptQTask[512].tQTaskRefList.ptHead;
          if ( v7 )
          {
            ptTail = ptQTask[512].tQTaskChildren.ptTail;
            igi2_frame.ptEventContext.bFlags = 0;
            igi2_frame.ptEventContext.eEvent = 45;
            igi2_frame.ptEventContext.vRadius = 0.0;
            igi2_frame.ptEventContext.ptPosition = (struct real64x3_t *)&v7[3].ptPrev;
            memset(&igi2_frame.ptEventContext.tDirection, 0, 20);
            igi2_frame.ptEventContext.eTeam = (int)ptTail;
            HumanAI_SendEvent(&igi2_frame.ptEventContext);
          }
        }
      }
    }
  }
  BYTE2(ptPrev[11].ptNext) = BYTE1(ptPrev[11].ptNext);
  *(float *)&ptQTaska = SCamera_LimitAngle(*(float *)&ptQTask[8].ptNext);
  ptQTask[8].ptNext = ptQTaska;
  if ( LOBYTE(ptPrev[11].ptNext) )
  {
    v12 = *(float *)&ptQTaska;
    if ( *(float *)&ptQTaska >= (double)*(float *)&ptPrev[9].tQTaskChildren.ptHead )
    {
      if ( v12 > *(float *)&ptPrev[9].tQTaskChildren.ptHead )
      {
        v14 = *(float *)&ptQTaska - 0.04363323375582695;
        *(float *)&ptQTask[8].ptNext = v14;
        if ( v14 < *(float *)&ptPrev[9].tQTaskChildren.ptHead )
          ptQTask[8].ptNext = ptPrev[9].tQTaskChildren.ptHead;
      }
    }
    else
    {
      v13 = v12 + 0.04363323375582695;
      *(float *)&ptQTask[8].ptNext = v13;
      if ( v13 > *(float *)&ptPrev[9].tQTaskChildren.ptHead )
        ptQTask[8].ptNext = ptPrev[9].tQTaskChildren.ptHead;
    }
    GameFunctions_GetMagicVertex(&igi2_frame.ptPos, ptQTask, 1);
    qmemcpy(&ptQTask[8].ptParent, &igi2_frame.ptPos, 0x18u);
    qmemcpy(&ptQTask[9].tQTaskChildren.ptTail, &ptQTask[3].ptPrev, sizeof(struct QTask_s));
    v15 = Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER;
    LOBYTE(ptQTask[11].tQTaskRefList.ptMiddle) = 0;
    if ( v15 )
      AIDetection_RunDetection(
        (struct AIDetection_s *)&ptQTask[11].ptParent,
        (struct AIDetectionView_s *)&ptQTask[8].ptParent,
        ptQTask[513].ptPrev,
        NetMission_eDefendingTeam);
    else
      AIDetection_RunDetection(
        (struct AIDetection_s *)&ptQTask[11].ptParent,
        (struct AIDetectionView_s *)&ptQTask[8].ptParent,
        ptQTask[513].ptPrev,
        1);
    SCamera_RotateLens(ptQTask);
    SCamera_SCameraLensPlayDetectionSound(ptQTask);
  }
  else
  {
    v9 = SCamera_LimitAngle(*(float *)&ptQTaska);
    *(float *)&ptQTask[8].ptNext = v9;
    if ( v9 >= -1.3089969158172607 )
    {
      if ( v9 > -1.3089969158172607 )
      {
        v11 = v9 - 0.04363323375582695;
        *(float *)&ptQTask[8].ptNext = v11;
        if ( v11 < -1.3089969158172607 )
          ptQTask[8].ptNext = (struct QTask_s *)-1079538378;
      }
    }
    else
    {
      v10 = v9 + 0.04363323375582695;
      *(float *)&ptQTask[8].ptNext = v10;
      if ( v10 > -1.3089969158172607 )
        ptQTask[8].ptNext = (struct QTask_s *)-1079538378;
    }
    BYTE1(ptPrev[11].ptNext) = 0;
    QTask_DeleteQTaskAndQTaskRefSafe(&ptQTask[512].tQTaskRefList.ptTail);
    QTask_DeleteQTaskAndQTaskRefSafe((struct QReference_s **)&ptQTask[512].ptParent);
    QTask_DeleteQTaskAndQTaskRefSafe((struct QReference_s **)&ptQTask[512].eQTaskType);
  }
  if ( LOBYTE(ptQTask[513].ptNext) )
  {
    LOBYTE(ptQTask[513].ptNext) = 0;
    LOBYTE(ptPrev[11].tQTaskChildren.ptMiddle) = 1;
    LODVirModelExistsFn = MTP_GetLODVirModelExistsFn((char *)&ptPrev[9].ptParent);
    if ( !LODVirModelExistsFn )
      LODVirModelExistsFn = nullptr;
    if ( LODVirModelExistsFn != *(struct LODVirModel_s **)&ptQTask[2].eQTaskType )
    {
      ModelObj_SetLODVirModel((struct ModelObj_s *)ptQTask, LODVirModelExistsFn, false);
      ptQTask[7].tQTaskRefList.ptHead = nullptr;
      ptQTask[7].tQTaskRefList.ptMiddle = nullptr;
      ptQTask[7].tQTaskRefList.ptTail = nullptr;
      ptQTask[7].ptParent = nullptr;
      *(_DWORD *)&ptQTask[7].eQTaskType = 0;
    }
    Explosion0_New(
      (struct real64x3_t *)&ptQTask[1],
      1,
      0,
      0.25,
      2048.0,
      0.0,
      0.0,
      7,
      3,
      nullptr,
      "1009_01_1",
      "explo_camera",
      20,
      0x402u,
      49152.0,
      nullptr,
      nullptr,
      EXPLOSIONDAMAGE_LINEAR_FALLOFF);
  }
  igi2_frame.vBeta = *(float *)&ptQTask[8].ptPrev
        + *(float *)&ptPrev[8].tQTaskRefList.ptMiddle
        + *(float *)&ptPrev[9].tQTaskChildren.ptMiddle;
  Real32x9_Create((struct real32x9_t *)&ptQTask[3].ptPrev, *(float *)&ptQTask[8].ptNext, 0.0, igi2_frame.vBeta);
  v17 = ptQTask->tQTaskChildren.ptHead;
  if ( v17->ptNext )
  {
    v18 = (int)v17;
    if ( v17 )
    {
      v19 = QTask_nProtectedQTaskStackOffset;
      do
      {
        if ( *(_DWORD *)v18 )
          v20 = **(_DWORD **)v18 != 0 ? *(struct QTask_s **)v18 : nullptr;
        else
          v20 = nullptr;
        QTask_atProtectedQTaskStack[v19].ptQTask = v20;
        pfHandler = (void (__cdecl *)(int))QTask_aatQTaskFinalEvent[1][*(unsigned __int16 *)(v18 + 36)].pfHandler;
        v22 = v19 + 1;
        QTask_nProtectedQTaskStackOffset = v22;
        if ( pfHandler )
        {
          pfHandler(v18);
          v22 = QTask_nProtectedQTaskStackOffset;
        }
        v18 = dword_849C7DC[v22];
        v19 = v22 - 1;
        QTask_nProtectedQTaskStackOffset = v19;
      }
      while ( v18 );
    }
  }
}

// source: j/0/objects/scamera.c:1071  [anchor-mhash]
void __cdecl SCamera_SCameraLensDeleteHandler(struct QTask_s *ptQTask)
{
  QTask_DeleteQTaskAndQTaskRefSafe(&ptQTask[512].tQTaskRefList.ptTail);
  QTask_DeleteQTaskAndQTaskRefSafe((struct QReference_s **)&ptQTask[512].ptParent);
  QTask_DeleteQTaskAndQTaskRefSafe((struct QReference_s **)&ptQTask[512].eQTaskType);
  QTaskList_Remove(GameFunctions_ptExplosionQTaskList, ptQTask);
  QTaskList_Remove(SCamera_ptSCameraLensQTaskList, ptQTask);
  SectorObject_RemoveInteriorDynCubeObj((struct DynCubeObj_s *)ptQTask);
  World_RemoveDynCubeObj((struct World_s *)ptQTask[2].ptParent, (struct DynCubeObj_s *)ptQTask);
  AIDetection_ClearDetection((struct AIDetection_s *)&ptQTask[11].ptParent);
}

// source: j/0/objects/scamera.c:1104  [anchor-caller]
void __cdecl SCamera_SCameraLensUpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { float ptDynCubeObj; };
    struct { float ptDynCubeObja; };
    struct { char igi2_o2[20]; double *p_ptParent; };
    struct { char igi2_o3[28]; struct real64x3_t ptPos; };
    char igi2_extent[56];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *ptPrev; // ebp
  struct LODVirModel_s *LODVirModelExistsFn; // eax
  double v5; // st7
  double v6; // st7
  int *v7; // eax
  int v8; // eax
  double v9; // st6
  struct QTask_s *ptParent; // ebx
  __int16 ptHead; // ax
  __int16 ptHead_high; // ax
  float ptQTaska = *(float *)&ptQTask; // [esp+3Ch] [ebp+4h] ARGSLOT

  ptPrev = ptQTask[513].ptPrev;
  igi2_frame.p_ptParent = (double *)&ptQTask[8].ptParent;
  LODVirModelExistsFn = MTP_GetLODVirModelExistsFn((char *)&ptPrev[9].tQTaskChildren.ptTail);
  if ( LODVirModelExistsFn != *(struct LODVirModel_s **)&ptQTask[2].eQTaskType )
  {
    ModelObj_SetLODVirModel((struct ModelObj_s *)ptQTask, LODVirModelExistsFn, false);
    ptQTask[7].tQTaskRefList.ptHead = nullptr;
    ptQTask[7].tQTaskRefList.ptMiddle = nullptr;
    ptQTask[7].tQTaskRefList.ptTail = nullptr;
    ptQTask[7].ptParent = nullptr;
    *(_DWORD *)&ptQTask[7].eQTaskType = 0;
  }
  GameFunctions_GetMagicVertex(&igi2_frame.ptPos, ptQTask[513].ptPrev, 0);
  if ( *(float *)&ptQTask[6].tQTaskChildren.ptHead <= (double)*(float *)&ptQTask[6].tQTaskChildren.ptMiddle )
    v5 = *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
  else
    v5 = *(float *)&ptQTask[6].tQTaskChildren.ptHead;
  if ( v5 >= *(float *)&ptQTask[6].ptPrev )
  {
    if ( *(float *)&ptQTask[6].tQTaskChildren.ptHead <= (double)*(float *)&ptQTask[6].tQTaskChildren.ptMiddle )
      v6 = *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
    else
      v6 = *(float *)&ptQTask[6].tQTaskChildren.ptHead;
  }
  else
  {
    v6 = *(float *)&ptQTask[6].ptPrev;
  }
  v7 = *(int **)&ptQTask[2].eQTaskType;
  if ( v7 && (v8 = *v7) != 0 )
    v9 = *(float *)(*(_DWORD *)(*(_DWORD *)(v8 + 12) + 12) + 120);
  else
    v9 = 1.0;
  igi2_frame.ptDynCubeObj = v6 * v9;
  World_MoveDynCubeObjRadius(
    (struct World_s *)ptQTask[2].ptParent,
    (struct DynCubeObj_s *)ptQTask,
    &igi2_frame.ptPos,
    igi2_frame.ptDynCubeObj);
  ptParent = ptQTask[2].ptParent;
  SectorObject_RemoveInteriorDynCubeObj((struct DynCubeObj_s *)ptQTask);
  if ( ptQTask[7].tQTaskChildren.ptTail )
  {
    ptQTask[2].tQTaskRefList.ptHead = nullptr;
    ptQTask[2].tQTaskRefList.ptMiddle = nullptr;
  }
  else
  {
    SectorObject_RegisterInteriorDynCubeObjSpecificSectorObject(
      (struct World_s *)ptParent,
      nullptr,
      (struct DynCubeObj_s *)ptQTask,
      (struct real64x3_t *)&ptQTask[1]);
  }
  ptQTaska = SCamera_LimitAngle(*(float *)&ptPrev[9].tQTaskChildren.ptHead);
  *(float *)&ptPrev[9].tQTaskChildren.ptHead = ptQTaska;
  *(float *)&ptQTask[8].ptNext = ptQTaska;
  igi2_frame.ptDynCubeObja = *(float *)&ptPrev[8].tQTaskRefList.ptMiddle + *(float *)&ptPrev[9].tQTaskChildren.ptMiddle;
  Real32x9_Create((struct real32x9_t *)&ptQTask[3].ptPrev, ptQTaska, 0.0, igi2_frame.ptDynCubeObja);
  GameFunctions_GetMagicVertex(&igi2_frame.ptPos, ptQTask, 1);
  qmemcpy(igi2_frame.p_ptParent, &igi2_frame.ptPos, 0x18u);
  qmemcpy(igi2_frame.p_ptParent + 3, &ptQTask[3].ptPrev, 0x28u);
  igi2_frame.p_ptParent[8] = (double)(SLOWORD(ptPrev[10].tQTaskRefList.ptHead) / 2) * 0.01745329238474369;
  igi2_frame.p_ptParent[9] = (double)(SHIWORD(ptPrev[10].tQTaskRefList.ptHead) / 2) * 0.01745329238474369;
  igi2_frame.p_ptParent[10] = *(float *)&ptPrev[10].tQTaskRefList.ptMiddle * 4096.0;
  ptHead = (__int16)ptPrev[10].tQTaskChildren.ptHead;
  if ( ptHead <= 0 )
    ptHead = 0;
  LOWORD(ptPrev[10].tQTaskChildren.ptHead) = ptHead;
  ptHead_high = HIWORD(ptPrev[10].tQTaskChildren.ptHead);
  if ( ptHead_high <= 0 )
    HIWORD(ptPrev[10].tQTaskChildren.ptHead) = 0;
  else
    HIWORD(ptPrev[10].tQTaskChildren.ptHead) = ptHead_high;
}

// source: j/0/objects/scamera.c:1179  [size~]
void __cdecl SCamera_SCameraLensUpdateInternalDataAfterLoadHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptParent; // esi

  ptParent = ptQTask[2].ptParent;
  SectorObject_RemoveInteriorDynCubeObj((struct DynCubeObj_s *)ptQTask);
  if ( ptQTask[7].tQTaskChildren.ptTail )
  {
    ptQTask[2].tQTaskRefList.ptHead = nullptr;
    ptQTask[2].tQTaskRefList.ptMiddle = nullptr;
  }
  else
  {
    SectorObject_RegisterInteriorDynCubeObjSpecificSectorObject(
      (struct World_s *)ptParent,
      nullptr,
      (struct DynCubeObj_s *)ptQTask,
      (struct real64x3_t *)&ptQTask[1]);
  }
}

void __cdecl sub_499270(struct QTask_s *a1, float *a2)
{
  struct QTask_s *v2; // edx
  float *v3; // esi
  double v4; // st7
  int v5; // ecx
  int v6; // eax
  void (__cdecl *pfHandler)(int, struct QTask_s **); // eax

  v2 = a1;
  if ( !LOBYTE(a1[513].ptPrev[11].tQTaskChildren.ptMiddle) )
  {
    v3 = a2;
    v4 = a2[1] + *(float *)&a1[8].tQTaskRefList.ptHead;
    *(float *)&a1[8].tQTaskRefList.ptHead = v4;
    if ( v4 >= *(float *)&v2[8].tQTaskRefList.ptMiddle )
      LOBYTE(v2[513].ptNext) = 1;
    v5 = *((_DWORD *)v3 + 5);
    if ( v5 )
    {
      v6 = *((_DWORD *)v3 + 7);
      if ( v6 )
      {
        if ( *(_BYTE *)(v6 + 177) )
        {
          a1 = v2;
          pfHandler = (void (__cdecl *)(int, struct QTask_s **))QTask_aatQTaskFinalEvent[Human_eHitByYouQTaskEvent][*(unsigned __int16 *)(v5 + 36)].pfHandler;
          if ( pfHandler )
            pfHandler(v5, &a1);
        }
      }
    }
  }
}

// source: j/0/objects/scamera.c:1248  [anchor-mhash]
void __cdecl SCamera_SCameraLensExplosionHitHandler(struct QTask_s *ptQTask, void *pxContext)
{
  double v2; // st7
  double v3; // st7
  int *v4; // eax
  int v5; // eax
  double v6; // st6
  double v7; // st7
  float ptExplosionHitContext; // [esp+0h] [ebp-Ch]

  if ( !LOBYTE(ptQTask[513].ptPrev[11].tQTaskChildren.ptMiddle) )
  {
    if ( *(float *)&ptQTask[6].tQTaskChildren.ptHead <= (double)*(float *)&ptQTask[6].tQTaskChildren.ptMiddle )
      v2 = *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
    else
      v2 = *(float *)&ptQTask[6].tQTaskChildren.ptHead;
    if ( v2 >= *(float *)&ptQTask[6].ptPrev )
    {
      if ( *(float *)&ptQTask[6].tQTaskChildren.ptHead <= (double)*(float *)&ptQTask[6].tQTaskChildren.ptMiddle )
        v3 = *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
      else
        v3 = *(float *)&ptQTask[6].tQTaskChildren.ptHead;
    }
    else
    {
      v3 = *(float *)&ptQTask[6].ptPrev;
    }
    v4 = *(int **)&ptQTask[2].eQTaskType;
    if ( v4 && (v5 = *v4) != 0 )
      v6 = *(float *)(*(_DWORD *)(*(_DWORD *)(v5 + 12) + 12) + 120);
    else
      v6 = 1.0;
    ptExplosionHitContext = v3 * v6;
    v7 = GameFunctions_ResolveExplosionHit(
           (struct ExplosionHitContext_t *)pxContext,
           ptQTask,
           (struct real64x3_t *)&ptQTask[1],
           ptExplosionHitContext,
           true)
       + *(float *)&ptQTask[8].tQTaskRefList.ptHead;
    *(float *)&ptQTask[8].tQTaskRefList.ptHead = v7;
    if ( v7 >= *(float *)&ptQTask[8].tQTaskRefList.ptMiddle )
      LOBYTE(ptQTask[513].ptNext) = 1;
  }
}

// source: j/0/objects/scamera.c:1297  [anchor-mhash]
void __cdecl SCamera_SCameraLensAIDetectionLineOfSightHandler(
        struct QTask_s *ptQTask,
        void *pxContext)
{
  struct QTask_s *ptPrev; // eax

  ptPrev = ptQTask[513].ptPrev;
  *(_BYTE *)pxContext = *((struct QTask_s **)pxContext + 2) != ptPrev && *((struct QTask_s **)pxContext + 3) != ptPrev;
}

// source: j/0/objects/scamera.c:1325  [anchor-mhash]
void __cdecl SCamera_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { float ptDynCubeObj; };
    struct { char igi2_o1[24]; struct real64x3_t ptPos; };
    char igi2_extent[52];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  double v2; // st7
  double v3; // st7
  int *v4; // eax
  int v5; // eax
  double v6; // st6
  unsigned __int16 v7; // ax
  struct QTask_s *v8; // eax

  memset(&igi2_frame.ptPos, 0, sizeof(igi2_frame.ptPos));
  ModelObj_Init((struct ModelObj_s *)ptQTask, World_ptActiveWorld, nullptr);
  ptQTask[7].tQTaskChildren.ptHead = nullptr;
  ptQTask[7].tQTaskChildren.ptMiddle = (struct QTask_s *)2;
  ptQTask[7].tQTaskRefList.ptHead = nullptr;
  ptQTask[7].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[7].tQTaskRefList.ptTail = nullptr;
  ptQTask[7].ptParent = nullptr;
  *(_DWORD *)&ptQTask[7].eQTaskType = 0;
  if ( *(float *)&ptQTask[6].tQTaskChildren.ptHead <= (double)*(float *)&ptQTask[6].tQTaskChildren.ptMiddle )
    v2 = *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
  else
    v2 = *(float *)&ptQTask[6].tQTaskChildren.ptHead;
  if ( v2 >= *(float *)&ptQTask[6].ptPrev )
  {
    if ( *(float *)&ptQTask[6].tQTaskChildren.ptHead <= (double)*(float *)&ptQTask[6].tQTaskChildren.ptMiddle )
      v3 = *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
    else
      v3 = *(float *)&ptQTask[6].tQTaskChildren.ptHead;
  }
  else
  {
    v3 = *(float *)&ptQTask[6].ptPrev;
  }
  v4 = *(int **)&ptQTask[2].eQTaskType;
  if ( v4 && (v5 = *v4) != 0 )
    v6 = *(float *)(*(_DWORD *)(*(_DWORD *)(v5 + 12) + 12) + 120);
  else
    v6 = 1.0;
  igi2_frame.ptDynCubeObj = v3 * v6;
  World_RegisterDynCubeObjFirstTimeRadius(
    World_ptActiveWorld,
    (struct DynCubeObj_s *)ptQTask,
    &igi2_frame.ptPos,
    igi2_frame.ptDynCubeObj,
    WORLD_DYNCUBETREE_CATEGORY_STATIONARY);
  if ( ptQTask[7].tQTaskChildren.ptTail )
  {
    ptQTask[2].tQTaskRefList.ptHead = nullptr;
    ptQTask[2].tQTaskRefList.ptMiddle = nullptr;
  }
  else
  {
    SectorObject_RegisterInteriorDynCubeObjSpecificSectorObject(
      (struct World_s *)ptQTask[2].ptParent,
      nullptr,
      (struct DynCubeObj_s *)ptQTask,
      (struct real64x3_t *)&ptQTask[1]);
  }
  ptQTask[8].ptNext = nullptr;
  ptQTask[8].ptPrev = nullptr;
  ptQTask[8].tQTaskChildren.ptHead = nullptr;
  ptQTask[8].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[8].tQTaskChildren.ptTail = nullptr;
  ptQTask[8].tQTaskRefList.ptHead = nullptr;
  ptQTask[8].tQTaskRefList.ptMiddle = nullptr;
  strcpy((char *)&ptQTask[8].tQTaskRefList.ptTail, "335_01_1");
  ptQTask[9].ptPrev = (struct QTask_s *)1;
  ptQTask[9].tQTaskChildren.ptHead = nullptr;
  ptQTask[9].tQTaskChildren.ptMiddle = nullptr;
  strcpy((char *)&ptQTask[9].tQTaskChildren.ptTail, "335_02_1");
  strcpy((char *)&ptQTask[9].ptParent, "335_03_1");
  LOWORD(ptQTask[10].tQTaskChildren.ptHead) = 45;
  HIWORD(ptQTask[10].tQTaskChildren.ptHead) = 45;
  LOWORD(ptQTask[10].tQTaskChildren.ptMiddle) = 45;
  LOWORD(ptQTask[10].tQTaskRefList.ptHead) = 90;
  HIWORD(ptQTask[10].tQTaskRefList.ptHead) = 90;
  v7 = SCamera_eSCameraLensQTaskType;
  ptQTask[10].tQTaskChildren.ptTail = (struct QTask_s *)1065353216;
  ptQTask[10].tQTaskRefList.ptMiddle = (struct QReference_s *)1092616192;
  v8 = QTask_NewFn(ptQTask, v7, nullptr);
  *(_DWORD *)&ptQTask[10].eQTaskType = 0;
  LOBYTE(ptQTask[11].ptNext) = 0;
  BYTE1(ptQTask[11].ptNext) = 0;
  BYTE2(ptQTask[11].ptNext) = 0;
  ptQTask[11].ptPrev = nullptr;
  LOBYTE(ptQTask[11].tQTaskChildren.ptMiddle) = 0;
  ptQTask[11].tQTaskChildren.ptHead = nullptr;
  BYTE1(ptQTask[11].tQTaskChildren.ptMiddle) = 0;
  ptQTask[10].tQTaskRefList.ptTail = (struct QReference_s *)v8;
  ptQTask[11].tQTaskChildren.ptTail = nullptr;
  ptQTask[11].tQTaskRefList.ptHead = nullptr;
  ptQTask[11].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[13].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[13].tQTaskChildren.ptTail = (struct QTask_s *)1056964608;
}

// source: j/0/objects/scamera.c:1418  [anchor-mhash]
void __cdecl SCamera_RunHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptHead; // ecx
  int v2; // edx
  struct QTask_s *v3; // eax
  void (__cdecl *pfHandler)(struct QTask_s *); // eax
  int v5; // edx
  struct QTask_s *v6; // eax
  struct HumanAIEventContext_t tEventContext; // [esp+18h] [ebp-40h] BYREF

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
  if ( LOBYTE(ptQTask[11].tQTaskChildren.ptMiddle) )
  {
    v6 = ptQTask[11].tQTaskChildren.ptHead;
    LOBYTE(ptQTask[11].ptNext) = 0;
    if ( v6 )
    {
      ptQTask[11].tQTaskChildren.ptHead = (struct QTask_s *)((char *)v6 - 1);
    }
    else
    {
      tEventContext.ptReferenceQTask = nullptr;
      tEventContext.ptHumanOriginatorQTask = nullptr;
      tEventContext.eEvent = 35;
      tEventContext.eTeam = -1;
      tEventContext.bFlags = 131;
      tEventContext.ptPosition = (struct real64x3_t *)&ptQTask[1];
      tEventContext.vRadius = 40960.0;
      HumanAI_SendEvent(&tEventContext);
      ptQTask[11].tQTaskChildren.ptHead = (struct QTask_s *)30;
    }
  }
  else if ( ptQTask[11].tQTaskChildren.ptTail && ptQTask[11].tQTaskRefList.ptHead->ptNext )
  {
    if ( ptQTask[11].tQTaskRefList.ptMiddle )
      LOBYTE(ptQTask[11].ptNext) = (__int64)Level_RunLevelExpression(
                                              (struct LevelExpression_s *)&ptQTask[11].tQTaskChildren.ptTail,
                                              ptQTask);
  }
}

// source: j/0/objects/scamera.c:1478  [anchor-mhash]
void __cdecl SCamera_DeleteHandler(struct QTask_s *ptQTask)
{
  int v1; // ecx
  struct QReference_s *v2; // eax
  void (__cdecl *pfHandler)(struct QTask_s *); // eax

  v1 = 0;
  while ( 1 )
  {
    v2 = Level_atLevelQTaskID[v1];
    if ( v2 )
    {
      if ( v2->pxObject == ptQTask )
        break;
    }
    if ( ++v1 >= 4096 )
      goto LABEL_9;
  }
  if ( v1 >= 0 )
  {
    pfHandler = (void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[Level_eRemoveLevelScriptSymbolsEvent][ptQTask->eQTaskType].pfHandler;
    if ( pfHandler )
      pfHandler(ptQTask);
  }
LABEL_9:
  Level_DeinitLevelExpression((struct LevelExpression_s *)&ptQTask[11].tQTaskChildren.ptTail);
  SectorObject_RemoveInteriorDynCubeObj((struct DynCubeObj_s *)ptQTask);
  World_RemoveDynCubeObj((struct World_s *)ptQTask[2].ptParent, (struct DynCubeObj_s *)ptQTask);
}

// source: j/0/objects/scamera.c:1509  [size]
void __cdecl SCamera_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = SCamera_ptParameterList;
}

// source: j/0/objects/scamera.c:1525  [anchor-mhash]
void __cdecl SCamera_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct LODVirModel_s *LODVirModelExistsFn; // eax
  double v4; // st7
  double v5; // st7
  int *v6; // eax
  int v7; // eax
  double v8; // st6
  struct QTask_s *ptParent; // ebx
  long double v10; // st7
  long double v11; // st6
  struct QTask_s *ptHead; // eax
  int v13; // edx
  struct QTask_s *v14; // ecx
  void (__cdecl *pfHandler)(struct QTask_s *, void *); // ecx
  int v16; // edx
  float ptDynCubeObj; // [esp+0h] [ebp-18h]
  struct QReference_s *ptTail; // [esp+14h] [ebp-4h]
  struct QTask_s *ptQTaska = *(struct QTask_s * *)&ptQTask; // [esp+1Ch] [ebp+4h] ARGSLOT

  ptTail = ptQTask[10].tQTaskRefList.ptTail;
  LODVirModelExistsFn = MTP_GetLODVirModelExistsFn((char *)&ptQTask[8].tQTaskRefList.ptTail);
  if ( LODVirModelExistsFn != *(struct LODVirModel_s **)&ptQTask[2].eQTaskType )
  {
    ModelObj_SetLODVirModel((struct ModelObj_s *)ptQTask, LODVirModelExistsFn, false);
    ptQTask[7].tQTaskRefList.ptHead = nullptr;
    ptQTask[7].tQTaskRefList.ptMiddle = nullptr;
    ptQTask[7].tQTaskRefList.ptTail = nullptr;
    ptQTask[7].ptParent = nullptr;
    *(_DWORD *)&ptQTask[7].eQTaskType = 0;
  }
  if ( *(float *)&ptQTask[6].tQTaskChildren.ptHead <= (double)*(float *)&ptQTask[6].tQTaskChildren.ptMiddle )
    v4 = *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
  else
    v4 = *(float *)&ptQTask[6].tQTaskChildren.ptHead;
  if ( v4 >= *(float *)&ptQTask[6].ptPrev )
  {
    if ( *(float *)&ptQTask[6].tQTaskChildren.ptHead <= (double)*(float *)&ptQTask[6].tQTaskChildren.ptMiddle )
      v5 = *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
    else
      v5 = *(float *)&ptQTask[6].tQTaskChildren.ptHead;
  }
  else
  {
    v5 = *(float *)&ptQTask[6].ptPrev;
  }
  v6 = *(int **)&ptQTask[2].eQTaskType;
  if ( v6 && (v7 = *v6) != 0 )
    v8 = *(float *)(*(_DWORD *)(*(_DWORD *)(v7 + 12) + 12) + 120);
  else
    v8 = 1.0;
  ptDynCubeObj = v5 * v8;
  World_MoveDynCubeObjRadius(
    (struct World_s *)ptQTask[2].ptParent,
    (struct DynCubeObj_s *)ptQTask,
    (struct real64x3_t *)&ptQTask[8],
    ptDynCubeObj);
  ptParent = ptQTask[2].ptParent;
  SectorObject_RemoveInteriorDynCubeObj((struct DynCubeObj_s *)ptQTask);
  if ( ptQTask[7].tQTaskChildren.ptTail )
  {
    ptQTask[2].tQTaskRefList.ptHead = nullptr;
    ptQTask[2].tQTaskRefList.ptMiddle = nullptr;
  }
  else
  {
    SectorObject_RegisterInteriorDynCubeObjSpecificSectorObject(
      (struct World_s *)ptParent,
      nullptr,
      (struct DynCubeObj_s *)ptQTask,
      (struct real64x3_t *)&ptQTask[1]);
  }
  ptQTaska = (struct QTask_s *)ptQTask[8].tQTaskRefList.ptMiddle;
  v10 = sin(*(float *)&ptQTaska);
  ptQTask[3].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[3].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[3].tQTaskRefList.ptTail = nullptr;
  ptQTask[3].ptParent = nullptr;
  *(_DWORD *)&ptQTask[3].eQTaskType = 1065353216;
  ptQTask[4].ptNext = nullptr;
  v11 = cos(*(float *)&ptQTaska);
  *(float *)&ptQTask[3].ptPrev = v11;
  *(float *)&ptQTask[3].tQTaskChildren.ptHead = -v10;
  *(float *)&ptQTask[3].tQTaskChildren.ptTail = v10;
  *(float *)&ptQTask[3].tQTaskRefList.ptHead = v11;
  Level_CompileLevelExpression((struct LevelExpression_s *)&ptQTask[11].tQTaskChildren.ptTail, ptQTask);
  ptTail[28].pxObject = ptQTask[13].tQTaskChildren.ptTail;
  ptHead = ptQTask->tQTaskChildren.ptHead;
  if ( ptHead->ptNext && ptHead )
  {
    v13 = QTask_nProtectedQTaskStackOffset;
    do
    {
      if ( ptHead->ptNext )
        v14 = ptHead->ptNext->ptNext != nullptr ? ptHead->ptNext : nullptr;
      else
        v14 = nullptr;
      QTask_atProtectedQTaskStack[v13].ptQTask = v14;
      pfHandler = (void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[ParameterList_eUpdateInternalDataQTaskEvent][ptHead->eQTaskType].pfHandler;
      v16 = v13 + 1;
      QTask_nProtectedQTaskStackOffset = v16;
      if ( pfHandler )
      {
        pfHandler(ptHead, pxContext);
        v16 = QTask_nProtectedQTaskStackOffset;
      }
      ptHead = (struct QTask_s *)dword_849C7DC[v16];
      v13 = v16 - 1;
      QTask_nProtectedQTaskStackOffset = v13;
    }
    while ( ptHead );
  }
}

// source: j/0/objects/scamera.c:1584  [size~]
void __cdecl SCamera_UpdateInternalDataAfterLoadHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptParent; // esi

  ptParent = ptQTask[2].ptParent;
  SectorObject_RemoveInteriorDynCubeObj((struct DynCubeObj_s *)ptQTask);
  if ( ptQTask[7].tQTaskChildren.ptTail )
  {
    ptQTask[2].tQTaskRefList.ptHead = nullptr;
    ptQTask[2].tQTaskRefList.ptMiddle = nullptr;
  }
  else
  {
    SectorObject_RegisterInteriorDynCubeObjSpecificSectorObject(
      (struct World_s *)ptParent,
      nullptr,
      (struct DynCubeObj_s *)ptQTask,
      (struct real64x3_t *)&ptQTask[1]);
  }
}

// source: j/0/objects/scamera.c:1630  [size]
void __cdecl SCamera_UpdateAttachmentHandler(struct QTask_s *ptQTask)
{
  float v1; // ecx
  struct QTask_s *v2; // edi
  long double v3; // st7
  long double v4; // st6
  float vAlpha; // [esp+0h] [ebp-4h] BYREF

  vAlpha = v1;
  v2 = ptQTask;
  ((void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[Attach_eUpdateAttachmentEvent][SectorInteriorObject_eQTaskType].pfHandler)(ptQTask);
  Real32x9_GetAngles(
    (struct real32x9_t *)&v2[3].ptPrev,
    &vAlpha,
    (float *)&ptQTask,
    (float *)&v2[8].tQTaskRefList.ptMiddle);
  ptQTask = (struct QTask_s *)v2[8].tQTaskRefList.ptMiddle;
  v3 = sin(*(float *)&ptQTask);
  v2[3].tQTaskChildren.ptMiddle = nullptr;
  v2[3].tQTaskRefList.ptMiddle = nullptr;
  v2[3].tQTaskRefList.ptTail = nullptr;
  v2[3].ptParent = nullptr;
  *(_DWORD *)&v2[3].eQTaskType = 1065353216;
  v2[4].ptNext = nullptr;
  v4 = cos(*(float *)&ptQTask);
  *(float *)&v2[3].ptPrev = v4;
  *(float *)&v2[3].tQTaskChildren.ptHead = -v3;
  *(float *)&v2[3].tQTaskChildren.ptTail = v3;
  *(float *)&v2[3].tQTaskRefList.ptHead = v4;
  qmemcpy(&v2[8], &v2[1], 0x18u);
}

// source: j/0/objects/scamera.c:1656  [size]
void __cdecl SCamera_RegisterScriptSymbolsHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { char zName[64]; };
    struct { char igi2_o1[64]; char zTemp[128]; };
    char igi2_extent[192];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)

  if ( !BYTE1(ptQTask[11].tQTaskChildren.ptMiddle) )
  {
    BYTE1(ptQTask[11].tQTaskChildren.ptMiddle) = 1;
    Level_GetUniqueQTaskNameFromTask(igi2_frame.zName, ptQTask);
    sprintf(igi2_frame.zTemp, "%s.isDetection", igi2_frame.zName);
    Symbol_Register(
      igi2_frame.zTemp,
      (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_Int8,
      (char *)&ptQTask[11].ptNext + 1,
      1,
      QSCRIPT_SYMBOLCLASS_VARIABLE,
      QSCRIPT_SYMBOLTYPE_INT,
      QSCRIPT_SYMBOLLIFESPAN_FINITE);
    sprintf(igi2_frame.zTemp, "%s.isLastDetection", igi2_frame.zName);
    Symbol_Register(
      igi2_frame.zTemp,
      (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_Int8,
      (char *)&ptQTask[11].ptNext + 2,
      1,
      QSCRIPT_SYMBOLCLASS_VARIABLE,
      QSCRIPT_SYMBOLTYPE_INT,
      QSCRIPT_SYMBOLLIFESPAN_FINITE);
    sprintf(igi2_frame.zTemp, "%s.nDetectionTime", igi2_frame.zName);
    Symbol_Register(
      igi2_frame.zTemp,
      (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_Int,
      &ptQTask[11].ptPrev,
      4,
      QSCRIPT_SYMBOLCLASS_VARIABLE,
      QSCRIPT_SYMBOLTYPE_INT,
      QSCRIPT_SYMBOLLIFESPAN_FINITE);
    sprintf(igi2_frame.zTemp, "%s.isExploded", igi2_frame.zName);
    Symbol_Register(
      igi2_frame.zTemp,
      (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_Int8,
      &ptQTask[11].tQTaskChildren.ptMiddle,
      1,
      QSCRIPT_SYMBOLCLASS_VARIABLE,
      QSCRIPT_SYMBOLTYPE_INT,
      QSCRIPT_SYMBOLLIFESPAN_FINITE);
  }
}

// source: j/0/objects/scamera.c:1695  [size]
void __cdecl SCamera_RemoveScriptSymbolsHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { char zName[64]; };
    struct { char igi2_o1[64]; char zTemp[128]; };
    char igi2_extent[192];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)

  if ( BYTE1(ptQTask[11].tQTaskChildren.ptMiddle) )
  {
    Level_GetUniqueQTaskNameFromTask(igi2_frame.zName, ptQTask);
    BYTE1(ptQTask[11].tQTaskChildren.ptMiddle) = 0;
    sprintf(igi2_frame.zTemp, "%s.isDetection", igi2_frame.zName);
    Symbol_Remove(igi2_frame.zTemp);
    sprintf(igi2_frame.zTemp, "%s.isLastDetection", igi2_frame.zName);
    Symbol_Remove(igi2_frame.zTemp);
    sprintf(igi2_frame.zTemp, "%s.nDetectionTime", igi2_frame.zName);
    Symbol_Remove(igi2_frame.zTemp);
    sprintf(igi2_frame.zTemp, "%s.isExploded", igi2_frame.zName);
    Symbol_Remove(igi2_frame.zTemp);
  }
}

// source: j/0/objects/scamera.c:1736  [anchor-mhash]
void __cdecl SCamera_AIDetectionGetInfoHandler(struct QTask_s *ptQTask, void *pxContext)
{
  char ptMiddle; // bl

  *(_DWORD *)pxContext = SCamera_bAIDetectionQTaskMask;
  if ( Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER )
    *((_DWORD *)pxContext + 20) = NetMission_eDefendingTeam;
  else
    *((_DWORD *)pxContext + 20) = 1;
  ptMiddle = (char)ptQTask[11].tQTaskChildren.ptMiddle;
  *((_BYTE *)pxContext + 85) = 1;
  *((_BYTE *)pxContext + 84) = ptMiddle == 0;
  qmemcpy((char *)pxContext + 8, &ptQTask[1], 0x18u);
  qmemcpy((char *)pxContext + 32, &ptQTask[1], 0x18u);
  qmemcpy((char *)pxContext + 56, &ptQTask[1], 0x18u);
}

// source: j/0/objects/scamera.c:1779  [size]
void __cdecl SCamera_AIDetectionLineOfSightHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_BYTE *)pxContext = *((struct QTask_s **)pxContext + 2) != ptQTask && *((struct QTask_s **)pxContext + 3) != ptQTask;
}

// source: j/0/objects/scamera.c:1807  [anchor-mhash]
void __cdecl SCamera_SCameraLensEnterHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { float vY4; };
    struct { char igi2_o1[4]; float vA; };
    struct { char igi2_o2[8]; float v11; };
    struct { char igi2_o3[12]; struct real32x2_t vY3; };
    struct { char igi2_o4[20]; struct QSprite_s *vY2; };
    struct { char igi2_o5[24]; float vX3; };
    struct { char igi2_o6[28]; float vY1; };
    struct { char igi2_o7[32]; float vX2; };
    struct { char igi2_o8[36]; struct QSprite_s *ptQSprite; };
    struct { char igi2_o9[40]; float vX1; };
    struct { char igi2_o10[44]; struct real64x3_t ptPos; };
    char igi2_extent[72];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *ptPrev; // esi
  double v4; // st7
  double v5; // st6
  double v6; // st5
  double v7; // st7
  double v8; // st7
  float ptQTaska = *(float *)&ptQTask; // [esp+58h] [ebp+4h] ARGSLOT

  ptPrev = ptQTask[513].ptPrev;
  if ( LOBYTE(ptPrev[11].ptNext) )
  {
    GameFunctions_GetMagicVertex(&igi2_frame.ptPos, ptQTask, 0);
    TransContext_ProjectWorldPos2(&TransContext_tActiveTransContext, &igi2_frame.vY3, &igi2_frame.vA, &igi2_frame.ptPos);
    if ( igi2_frame.vA > 0.0 )
    {
      if ( BYTE1(ptPrev[11].ptNext) || ptPrev[11].ptPrev )
      {
        igi2_frame.vY4 = 128.0;
        ptQTaska = 0.0;
        if ( !LOBYTE(ptQTask[513].tQTaskChildren.ptTail) )
        {
          v4 = 512.0;
          v5 = 512.0;
          goto LABEL_13;
        }
      }
      else
      {
        if ( !strncmp((char *)&ptPrev[9].tQTaskChildren.ptTail, "313", 3u) )
        {
          igi2_frame.vY4 = 100.0;
          ptQTaska = 100.0;
        }
        else
        {
          igi2_frame.vY4 = 0.0;
          ptQTaska = 128.0;
        }
        if ( !LOBYTE(ptQTask[513].tQTaskChildren.ptTail) )
        {
          v4 = 512.0;
          v5 = 512.0;
          igi2_frame.vY4 = igi2_frame.vY4 * 0.5;
          ptQTaska = ptQTaska * 0.5;
          goto LABEL_13;
        }
      }
      v4 = 1024.0;
      v5 = 1024.0;
LABEL_13:
      v6 = v4 * TransContext_tActiveTransContext.vScreenFOVX;
      v7 = 1.0 / igi2_frame.vA;
      igi2_frame.vY1 = v6 * v7;
      v8 = v5 * TransContext_tActiveTransContext.vScreenFOVY * v7;
      *(float *)&igi2_frame.ptQSprite = igi2_frame.vY3.vX - igi2_frame.vY1;
      igi2_frame.vX1 = igi2_frame.vY3.vY - v8;
      igi2_frame.v11 = igi2_frame.vY3.vX + igi2_frame.vY1;
      igi2_frame.vY1 = igi2_frame.v11;
      igi2_frame.vY3.vX = igi2_frame.v11;
      igi2_frame.vX2 = igi2_frame.vX1;
      igi2_frame.vY2 = igi2_frame.ptQSprite;
      igi2_frame.vX3 = v8 + igi2_frame.vY3.vY;
      igi2_frame.vY3.vY = igi2_frame.vX3;
      QSprite_Register4AZ(
        &SCamera_ptLightGameSprite->tQSprite,
        *(float *)&igi2_frame.ptQSprite,
        igi2_frame.vX1,
        igi2_frame.v11,
        igi2_frame.vX1,
        *(float *)&igi2_frame.ptQSprite,
        igi2_frame.vX3,
        igi2_frame.v11,
        igi2_frame.vX3,
        igi2_frame.vY4,
        ptQTaska,
        0.0,
        0.5,
        igi2_frame.vA,
        0,
        (unsigned int)&MTP_atLODVirModel[46].atBoneVertexRefs[36].atVertexRefs[235],
        0);
    }
  }
  ((void (__cdecl *)(struct QTask_s *, _DWORD))QTask_aatQTaskFinalEvent[5][RigidDynCubeObj_eQTaskType].pfHandler)(
    ptQTask,
    0);
}

// source: j/0/objects/scamera.c:2017  [anchor-caller]
void __cdecl SCamera_SCameraLensDrawComputerObjectHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct real32x3_t Real32x3_RotateInverse_tTemp; };
    struct { char igi2_o1[12]; struct real32x3_t tRGB; };
    struct { char igi2_o2[24]; struct real32x3_t tRelativePos; };
    char igi2_extent[36];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *ptPrev; // esi
  int v3; // edx
  double v4; // st7
  double v5; // st6
  double v6; // st5
  float *v7; // eax
  struct QReference_s *ptHead; // edi
  struct QSprite_s *v9; // esi
  int v10; // eax
  struct QTask_s *ptQTaska = *(struct QTask_s * *)&ptQTask; // [esp+2Ch] [ebp+4h] ARGSLOT

  ptPrev = ptQTask[513].ptPrev;
  if ( !LOBYTE(ptPrev[11].tQTaskChildren.ptMiddle) && ptPrev[9].ptPrev && Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER )
  {
    if ( ptQTask[512].tQTaskRefList.ptHead )
    {
      igi2_frame.tRGB.vX = 128.0;
      igi2_frame.tRGB.vY = 0.0;
    }
    else if ( ptQTask[512].tQTaskRefList.ptMiddle )
    {
      v3 = Flow_ptFlow->nTicks % 30;
      igi2_frame.tRGB.vY = 0.0;
      igi2_frame.tRGB.vX = (sin((double)v3 * 0.03333333507180214 * 6.2831854820251465) + 1.0) * 64.0;
    }
    else
    {
      igi2_frame.tRGB.vX = 0.0;
      igi2_frame.tRGB.vY = 128.0;
    }
    v4 = *(double *)&ptQTask[1].ptNext - *(double *)*(_DWORD *)pxContext;
    v5 = *(double *)&ptQTask[1].tQTaskChildren.ptHead - *(double *)(*(_DWORD *)pxContext + 8);
    v6 = *(double *)&ptQTask[1].tQTaskChildren.ptTail - *(double *)(*(_DWORD *)pxContext + 16);
    v7 = *((float **)pxContext + 1);
    igi2_frame.Real32x3_RotateInverse_tTemp.vX = v6 * v7[6] + v5 * v7[3] + v4 * *v7;
    igi2_frame.Real32x3_RotateInverse_tTemp.vY = v6 * v7[7] + v5 * v7[4] + v4 * v7[1];
    igi2_frame.Real32x3_RotateInverse_tTemp.vZ = v6 * v7[8] + v5 * v7[5] + v4 * v7[2];
    igi2_frame.tRelativePos = igi2_frame.Real32x3_RotateInverse_tTemp;
    if ( LOBYTE(ptPrev[11].ptNext) )
    {
      ptHead = ptQTask[513].tQTaskRefList.ptHead;
      v9 = &ComputerMenu_tComputerMenuResource.atQSpriteHilight[18];
    }
    else
    {
      v9 = &ComputerMenu_tComputerMenuResource.atQSpriteHilight[17];
      ptHead = nullptr;
    }
    ComputerObject_ProjectRotatedPos(
      (struct real32x2_t *)&igi2_frame.Real32x3_RotateInverse_tTemp,
      &igi2_frame.tRelativePos,
      (struct DrawComputerObjectContext_s *)pxContext,
      false);
    v10 = (int)&v9->atQAnimframe[v9->nQAnimframes];
    ptQTaska = (struct QTask_s *)*(__int16 *)(v10 + 14);
    igi2_frame.Real32x3_RotateInverse_tTemp.vX = igi2_frame.Real32x3_RotateInverse_tTemp.vX - (double)*(__int16 *)(v10 + 12) * 0.5;
    igi2_frame.Real32x3_RotateInverse_tTemp.vY = igi2_frame.Real32x3_RotateInverse_tTemp.vY - (double)(int)ptQTaska * 0.5;
    QSprite_RegisterAZ(
      v9,
      igi2_frame.Real32x3_RotateInverse_tTemp.vX,
      igi2_frame.Real32x3_RotateInverse_tTemp.vY,
      igi2_frame.tRGB.vX,
      igi2_frame.tRGB.vY,
      0.0,
      1.0,
      532.47998046875,
      (int)ptHead,
      0x400C0000u,
      -1);
  }
}

// source: j/0/objects/scamera.c:2127  [anchor-mhash]
void __cdecl SCamera_SCameraLensDrawCameraConeHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { int vGamma; };
    struct { char igi2_o1[4]; struct SCamera_s *ptSCamera; };
    struct { char igi2_o2[8]; int vBeta; };
    struct { char igi2_o3[12]; struct real32x2_t vAlpha; };
    struct { char igi2_o4[20]; struct real64x3_t tDelta; };
    struct { char igi2_o5[44]; struct real64x3_t tPos1; };
    struct { char igi2_o6[68]; struct real64x3_t tPos0; };
    struct { char igi2_o7[92]; struct real32x9_t tOrientation; };
    struct { char igi2_o8[132]; struct QVertex_s atQVertex[3]; };
    struct { char igi2_o9[244]; struct real64x3_t tPos; };
    struct { char igi2_o10[268]; struct ObjectCollisionEvaluateContext_t tObjectCollisionEvaluateContext; };
    struct { char igi2_o11[276]; struct real64x3_t Real64x3_Rotate_tTemp; };
    struct { char igi2_o12[300]; struct QIntersection_s tIntersection; };
    struct { char igi2_o13[420]; struct real64x3_t atPos1[12]; };
    char igi2_extent[712];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct SCamera_s *ptPrev; // eax
  struct real64x3_t *v3; // ebp
  int v4; // ebx
  double v5; // st7
  long double v6; // st3
  struct real64x3_t *v7; // edi
  struct real64x3_t *v8; // ebx

  ptPrev = (struct SCamera_s *)ptQTask[513].ptPrev;
  igi2_frame.ptSCamera = ptPrev;
  if ( Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER && ptQTask[512].tQTaskRefList.ptHead
    || BYTE1(ptQTask[513].tQTaskChildren.ptTail) )
  {
    BYTE1(ptQTask[513].tQTaskChildren.ptTail) = 0;
    if ( !ptPrev->isDestroyed )
    {
      GameFunctions_GetMagicVertex(&igi2_frame.tPos, ptQTask, 1);
      qmemcpy(&igi2_frame.tOrientation, &ptQTask[3].ptPrev, sizeof(igi2_frame.tOrientation));
      Real32x9_GetAngles(&igi2_frame.tOrientation, &igi2_frame.vAlpha.vX, (float *)&igi2_frame.vBeta, (float *)&igi2_frame.vGamma);
      igi2_frame.vBeta = igi2_frame.ptSCamera->tSCameraLensParameters.nViewGamma;
      igi2_frame.tObjectCollisionEvaluateContext.tCollisionEvaluateContext.ptQTask = ptQTask;
      v3 = igi2_frame.atPos1;
      v4 = 12;
      v5 = (double)igi2_frame.vBeta * 0.01745329238474369;
      *(float *)&igi2_frame.vGamma = 0.5 * v5 + *(float *)&igi2_frame.vGamma;
      *(float *)&igi2_frame.vBeta = v5 * 0.0833333358168602;
      do
      {
        igi2_frame.tPos1.vY = igi2_frame.ptSCamera->tSCameraLensParameters.vViewLength * 4096.0;
        qmemcpy(&igi2_frame.tPos0, &igi2_frame.tPos, sizeof(igi2_frame.tPos0));
        Real32x9_Create(&igi2_frame.tOrientation, 0.0, 0.0, *(float *)&igi2_frame.vGamma);
        igi2_frame.Real64x3_Rotate_tTemp.vX = (igi2_frame.tOrientation.tX.vZ + igi2_frame.tOrientation.tX.vX) * 0.0 + igi2_frame.tOrientation.tX.vY * igi2_frame.tPos1.vY;
        igi2_frame.Real64x3_Rotate_tTemp.vY = (igi2_frame.tOrientation.tY.vZ + igi2_frame.tOrientation.tY.vX) * 0.0 + igi2_frame.tOrientation.tY.vY * igi2_frame.tPos1.vY;
        igi2_frame.Real64x3_Rotate_tTemp.vZ = (igi2_frame.tOrientation.tZ.vZ + igi2_frame.tOrientation.tZ.vX) * 0.0 + igi2_frame.tOrientation.tZ.vY * igi2_frame.tPos1.vY;
        qmemcpy(&igi2_frame.tPos1, &igi2_frame.Real64x3_Rotate_tTemp, sizeof(igi2_frame.tPos1));
        igi2_frame.tPos1.vX = igi2_frame.tPos.vX + igi2_frame.Real64x3_Rotate_tTemp.vX;
        igi2_frame.tPos1.vY = igi2_frame.tPos.vY + igi2_frame.tPos1.vY;
        igi2_frame.tPos1.vZ = igi2_frame.tPos.vZ + igi2_frame.tPos1.vZ;
        while ( 1 )
        {
          World_TraceLines(
            Game_ptGame->ptWorld,
            &igi2_frame.tIntersection,
            &igi2_frame.tPos0,
            &igi2_frame.tPos1,
            1,
            GameFunctions_eObjectCollisionEvaluateQTaskEvent,
            &igi2_frame.tObjectCollisionEvaluateContext.tCollisionEvaluateContext,
            0xFFFFFFFF);
          if ( !igi2_frame.tIntersection.isHit )
            break;
          if ( !igi2_frame.tIntersection.isDoubleFace
            || !igi2_frame.tIntersection.ptEnterMaterial
            || igi2_frame.tIntersection.ptEnterMaterial->vTransparency <= 0.0 )
          {
            qmemcpy(&igi2_frame.tPos1, &igi2_frame.tIntersection.tPos, sizeof(igi2_frame.tPos1));
            break;
          }
          igi2_frame.tDelta.vY = igi2_frame.tIntersection.tPos.vY - igi2_frame.tPos0.vY;
          v6 = 1.0
             / sqrt(
                 igi2_frame.tDelta.vY * igi2_frame.tDelta.vY
               + (igi2_frame.tIntersection.tPos.vZ - igi2_frame.tPos0.vZ) * (igi2_frame.tIntersection.tPos.vZ - igi2_frame.tPos0.vZ)
               + (igi2_frame.tIntersection.tPos.vX - igi2_frame.tPos0.vX) * (igi2_frame.tIntersection.tPos.vX - igi2_frame.tPos0.vX));
          igi2_frame.tDelta.vX = v6 * (igi2_frame.tIntersection.tPos.vX - igi2_frame.tPos0.vX);
          igi2_frame.tDelta.vY = igi2_frame.tDelta.vY * v6;
          igi2_frame.tDelta.vY = igi2_frame.tDelta.vY * 20.48;
          igi2_frame.tDelta.vZ = v6 * (igi2_frame.tIntersection.tPos.vZ - igi2_frame.tPos0.vZ) * 20.48;
          igi2_frame.tPos0.vX = igi2_frame.tDelta.vX * 20.48 + igi2_frame.tIntersection.tPos.vX;
          igi2_frame.tPos0.vY = igi2_frame.tDelta.vY + igi2_frame.tIntersection.tPos.vY;
          igi2_frame.tPos0.vZ = igi2_frame.tDelta.vZ + igi2_frame.tIntersection.tPos.vZ;
        }
        v7 = v3++;
        --v4;
        *(float *)&igi2_frame.vGamma = *(float *)&igi2_frame.vGamma - *(float *)&igi2_frame.vBeta;
        qmemcpy(v7, &igi2_frame.tPos1, sizeof(struct real64x3_t));
      }
      while ( v4 );
      QVertex_ptActiveTexture = nullptr;
      QVertex_ptActivePalette = nullptr;
      igi2_frame.tDelta.vX = 3.5;
      *(_QWORD *)&igi2_frame.tDelta.vY = 0x3FFFFFFFFLL;
      LODWORD(igi2_frame.tDelta.vZ) = igi2_frame.atQVertex;
      ComputerObject_ProjectWorldPos(
        &igi2_frame.vAlpha,
        (float *)&igi2_frame.ptSCamera,
        &igi2_frame.tPos,
        (struct DrawComputerObjectContext_s *)pxContext);
      igi2_frame.atQVertex[0].vX = igi2_frame.vAlpha.vX;
      igi2_frame.atQVertex[0].vY = igi2_frame.vAlpha.vY;
      igi2_frame.atQVertex[0].vZ = 532.47998046875;
      igi2_frame.atQVertex[0].vR = 1.0;
      igi2_frame.atQVertex[0].vG = 0.0;
      igi2_frame.atQVertex[0].vB = 0.0;
      igi2_frame.atQVertex[0].vA = 0.3499999940395355;
      igi2_frame.atQVertex[0].vU = 0.0;
      igi2_frame.atQVertex[0].vV = 0.0;
      v8 = &igi2_frame.atPos1[1];
      igi2_frame.vGamma = 11;
      do
      {
        ComputerObject_ProjectWorldPos(
          &igi2_frame.vAlpha,
          (float *)&igi2_frame.ptSCamera,
          v8 - 1,
          (struct DrawComputerObjectContext_s *)pxContext);
        igi2_frame.atQVertex[1].vY = igi2_frame.vAlpha.vY;
        igi2_frame.atQVertex[1].vX = igi2_frame.vAlpha.vX;
        igi2_frame.atQVertex[1].vZ = 532.47998046875;
        igi2_frame.atQVertex[1].vR = 1.0;
        igi2_frame.atQVertex[1].vG = 0.0;
        igi2_frame.atQVertex[1].vB = 0.0;
        igi2_frame.atQVertex[1].vA = 0.3499999940395355;
        igi2_frame.atQVertex[1].vU = 0.0;
        igi2_frame.atQVertex[1].vV = 0.0;
        ComputerObject_ProjectWorldPos(
          &igi2_frame.vAlpha,
          (float *)&igi2_frame.ptSCamera,
          v8,
          (struct DrawComputerObjectContext_s *)pxContext);
        igi2_frame.atQVertex[2].vX = igi2_frame.vAlpha.vX;
        igi2_frame.atQVertex[2].vY = igi2_frame.vAlpha.vY;
        igi2_frame.atQVertex[2].vZ = 532.47998046875;
        igi2_frame.atQVertex[2].vR = 1.0;
        igi2_frame.atQVertex[2].vG = 0.0;
        igi2_frame.atQVertex[2].vB = 0.0;
        igi2_frame.atQVertex[2].vA = 0.3499999940395355;
        igi2_frame.atQVertex[2].vU = 0.0;
        igi2_frame.atQVertex[2].vV = 0.0;
        RenderMode_tActiveRenderMode.apfRenderModeMethod[QVertex_eRegisterQVertexStripMethod](&igi2_frame.tDelta);
        ++v8;
        --igi2_frame.vGamma;
      }
      while ( *(float *)&igi2_frame.vGamma != 0.0 );
    }
  }
}

// source: j/0/objects/scamera.c:2444  [anchor-mhash]
void __cdecl SCamera_SCameraLensRegisterHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { float ptDynCubeObj; };
    struct { char igi2_o1[24]; struct real64x3_t ptPos; };
    char igi2_extent[52];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  double v2; // st7
  double v3; // st7
  int *v4; // eax
  int v5; // eax
  double v6; // st6
  struct QTask_s *ptHead; // eax
  int v8; // edx
  struct QTask_s *v9; // ecx
  void (__cdecl *pfHandler)(struct QTask_s *, void *); // ecx
  int v11; // edx

  if ( !ptQTask[2].tQTaskChildren.ptHead )
  {
    GameFunctions_GetMagicVertex(&igi2_frame.ptPos, ptQTask[513].ptPrev, 0);
    v2 = *(float *)&ptQTask[6].tQTaskChildren.ptHead <= (double)*(float *)&ptQTask[6].tQTaskChildren.ptMiddle
       ? *(float *)&ptQTask[6].tQTaskChildren.ptMiddle
       : *(float *)&ptQTask[6].tQTaskChildren.ptHead;
    if ( v2 >= *(float *)&ptQTask[6].ptPrev )
      v3 = *(float *)&ptQTask[6].tQTaskChildren.ptHead <= (double)*(float *)&ptQTask[6].tQTaskChildren.ptMiddle
         ? *(float *)&ptQTask[6].tQTaskChildren.ptMiddle
         : *(float *)&ptQTask[6].tQTaskChildren.ptHead;
    else
      v3 = *(float *)&ptQTask[6].ptPrev;
    v4 = *(int **)&ptQTask[2].eQTaskType;
    if ( v4 && (v5 = *v4) != 0 )
      v6 = *(float *)(*(_DWORD *)(*(_DWORD *)(v5 + 12) + 12) + 120);
    else
      v6 = 1.0;
    igi2_frame.ptDynCubeObj = v3 * v6;
    World_RegisterDynCubeObjFirstTimeRadius(
      *((struct World_s **)pxContext + 1),
      (struct DynCubeObj_s *)ptQTask,
      &igi2_frame.ptPos,
      igi2_frame.ptDynCubeObj,
      WORLD_DYNCUBETREE_CATEGORY_STATIONARY);
    if ( ptQTask[7].tQTaskChildren.ptTail )
    {
      ptQTask[2].tQTaskRefList.ptHead = nullptr;
      ptQTask[2].tQTaskRefList.ptMiddle = nullptr;
    }
    else
    {
      SectorObject_RegisterInteriorDynCubeObjSpecificSectorObject(
        (struct World_s *)ptQTask[2].ptParent,
        nullptr,
        (struct DynCubeObj_s *)ptQTask,
        (struct real64x3_t *)&ptQTask[1]);
    }
    ptHead = ptQTask->tQTaskChildren.ptHead;
    if ( ptHead->ptNext )
    {
      if ( ptHead )
      {
        v8 = QTask_nProtectedQTaskStackOffset;
        do
        {
          if ( ptHead->ptNext )
            v9 = ptHead->ptNext->ptNext != nullptr ? ptHead->ptNext : nullptr;
          else
            v9 = nullptr;
          QTask_atProtectedQTaskStack[v8].ptQTask = v9;
          pfHandler = (void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[DynCubeObj_eDynCubeObjRegisterQTaskEvent][ptHead->eQTaskType].pfHandler;
          v11 = v8 + 1;
          QTask_nProtectedQTaskStackOffset = v11;
          if ( pfHandler )
          {
            pfHandler(ptHead, pxContext);
            v11 = QTask_nProtectedQTaskStackOffset;
          }
          ptHead = (struct QTask_s *)dword_849C7DC[v11];
          v8 = v11 - 1;
          QTask_nProtectedQTaskStackOffset = v8;
        }
        while ( ptHead );
      }
    }
  }
}

void __cdecl sub_49A790(struct DynCubeObj_s *a1, struct World_s **a2)
{
  struct QTask_s *ptHead; // eax
  int v3; // edx
  struct QTask_s *v4; // ecx
  void (__cdecl *pfHandler)(struct QTask_s *, struct World_s **); // ecx
  int v6; // edx

  if ( a1->ptDynCubeObjTreeItem )
  {
    QTask_DeleteQTaskAndQTaskRefSafe((struct QReference_s **)&a1[183].tQObj.tQTask.tQTaskChildren.ptMiddle);
    QTask_DeleteQTaskAndQTaskRefSafe((struct QReference_s **)&a1[183].tQObj.tQTask.tQTaskChildren.ptTail);
    QTask_DeleteQTaskAndQTaskRefSafe(&a1[183].tQObj.tQTask.tQTaskRefList.ptHead);
    ptHead = a1->tQObj.tQTask.tQTaskChildren.ptHead;
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
        pfHandler = (void (__cdecl *)(struct QTask_s *, struct World_s **))QTask_aatQTaskFinalEvent[DynCubeObj_eDynCubeObjRemoveQTaskEvent][ptHead->eQTaskType].pfHandler;
        v6 = v3 + 1;
        QTask_nProtectedQTaskStackOffset = v6;
        if ( pfHandler )
        {
          pfHandler(ptHead, a2);
          v6 = QTask_nProtectedQTaskStackOffset;
        }
        ptHead = (struct QTask_s *)dword_849C7DC[v6];
        v3 = v6 - 1;
        QTask_nProtectedQTaskStackOffset = v3;
      }
      while ( ptHead );
    }
    SectorObject_RemoveInteriorDynCubeObj(a1);
    World_RemoveDynCubeObj(*a2, a1);
  }
}

// source: j/0/objects/scamera.c:2533  [size]
struct QTaskList_s *__cdecl SCamera_SCameraLensGetQTaskList()
{
  return SCamera_ptSCameraLensQTaskList;
}

// source: j/0/objects/scamera.c:2548  [size]
unsigned int __cdecl SCamera_GetAIDetectionQTaskMask()
{
  return SCamera_bAIDetectionQTaskMask;
}

// source: j/0/objects/scamera.c:2563  [size]
struct real64x3_t *__cdecl SCamera_SCameraLensGetPosition(struct QTask_s *ptQTask)
{
  return (struct real64x3_t *)&ptQTask[1];
}

// source: j/0/objects/scamera.c:2579  [size]
struct QTask_s *__cdecl SCamera_ShowConeThisFrame(struct QTask_s *ptQTask)
{
  BYTE1(ptQTask[513].tQTaskChildren.ptTail) = 1;
  return ptQTask;
}

// source: j/0/objects/scamera.c:2595  [anchor-strings]
void __cdecl SCamera_Open()
{
  unsigned __int16 v0; // si
  struct ParameterList_s *v1; // eax
  int v2; // edx
  unsigned __int16 v3; // si
  __int16 v4; // ax
  __int16 v5; // ax
  unsigned __int16 v6; // si
  __int16 v7; // di
  unsigned __int16 v8; // si
  unsigned __int16 v9; // si

  v0 = QTask_NewQTaskType("SCamera", 544, SectorInteriorObject_eQTaskType, 0, 0);
  SCamera_eQTaskType = v0;
  QTask_LinkQTaskEventHandlerFn(
    v0,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveHandler);
  QTask_LinkQTaskEventHandlerFn(v0, 0, SCamera_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 1, SCamera_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 2, SCamera_DeleteHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))SCamera_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(v0, ParameterList_eUpdateInternalDataQTaskEvent, SCamera_UpdateInternalDataHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(
    v0,
    Level_eUpdateInternalDataAfterLoadEvent,
    SCamera_UpdateInternalDataAfterLoadHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(
    v0,
    Level_eRegisterLevelScriptSymbolsEvent,
    SCamera_RegisterScriptSymbolsHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, Level_eRemoveLevelScriptSymbolsEvent, SCamera_RemoveScriptSymbolsHandler);
  QTask_LinkQTaskEventHandlerFn(v0, AIDetection_eGetDetectionInfoQTaskEvent, SCamera_AIDetectionGetInfoHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    AIDetection_eLineOfSightQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))SCamera_AIDetectionLineOfSightHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, Attach_eUpdateAttachmentEvent, SCamera_UpdateAttachmentHandler);
  v1 = (struct ParameterList_s *)Mem_AllocFn(352, 4);
  v2 = Level_eParameterTypeObjectPos;
  v1->ptParameterListItem = (struct ParameterListItem_s *)&v1[1];
  v1->nParameters = 0;
  v1->nMaxParameters = 17;
  SCamera_ptParameterList = v1;
  ParameterList_AddParameter(v1, 0x140u, v2, "Holder Position", 7u, nullptr);
  ParameterList_AddParameter(SCamera_ptParameterList, 0x158u, Level_eParameterTypeAngle, "Holder Gamma", 7u, nullptr);
  ParameterList_AddParameter(SCamera_ptParameterList, 0x15Cu, Level_eParameterTypeString16, "Holder Model", 7u, nullptr);
  ParameterList_AddParameter(
    SCamera_ptParameterList,
    0x16Cu,
    Level_eParameterTypebool8,
    "Camera Visible on Computer",
    7u,
    nullptr);
  ParameterList_AddParameter(SCamera_ptParameterList, 0x170u, Level_eParameterTypeAngle, "Camera Alpha", 7u, nullptr);
  ParameterList_AddParameter(SCamera_ptParameterList, 0x174u, Level_eParameterTypeAngle, "Camera Gamma", 7u, nullptr);
  ParameterList_AddParameter(SCamera_ptParameterList, 0x178u, Level_eParameterTypeString16, "Camera Model", 7u, nullptr);
  ParameterList_AddParameter(
    SCamera_ptParameterList,
    0x188u,
    Level_eParameterTypeString16,
    "Camera Destroyed Model",
    7u,
    nullptr);
  ParameterList_AddParameter(
    SCamera_ptParameterList,
    0x198u,
    Level_eParameterTypeInt16,
    "Rotate Gamma Left(d)",
    7u,
    nullptr);
  ParameterList_AddParameter(
    SCamera_ptParameterList,
    0x19Au,
    Level_eParameterTypeInt16,
    "Rotate Gamma Right(d)",
    7u,
    nullptr);
  ParameterList_AddParameter(
    SCamera_ptParameterList,
    0x19Cu,
    Level_eParameterTypeInt16,
    "Rotate Gamma Speed (d/s)",
    7u,
    nullptr);
  ParameterList_AddParameter(
    SCamera_ptParameterList,
    0x1A0u,
    Level_eParameterTypeReal32,
    "Gamma Delay (s)",
    7u,
    nullptr);
  ParameterList_AddParameter(
    SCamera_ptParameterList,
    0x1A4u,
    Level_eParameterTypeInt16,
    "Viewcone Alpha (d)",
    7u,
    nullptr);
  ParameterList_AddParameter(
    SCamera_ptParameterList,
    0x1A6u,
    Level_eParameterTypeInt16,
    "Viewcone Gamma (d)",
    7u,
    nullptr);
  ParameterList_AddParameter(
    SCamera_ptParameterList,
    0x1A8u,
    Level_eParameterTypeReal32,
    "Viewcone length (m)",
    7u,
    nullptr);
  ParameterList_AddParameter(
    SCamera_ptParameterList,
    0x1C8u,
    Level_eParameterTypeVarString,
    "On Expression",
    7u,
    nullptr);
  ParameterList_AddParameterMinMax(
    SCamera_ptParameterList,
    0x218u,
    Level_eParameterTypeReal32,
    "Max damage factor",
    7u,
    0.0,
    50.0);
  v3 = QTask_NewQTaskType("SCameraLens", 20544, SectorInteriorObject_eQTaskType, 0, 0);
  SCamera_eSCameraLensQTaskType = v3;
  QTask_LinkQTaskEventHandlerFn(v3, 0, SCamera_SCameraLensCreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v3, 1, SCamera_SCameraLensRunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v3, 2, SCamera_SCameraLensDeleteHandler);
  QTask_LinkQTaskEventHandlerFn(
    v3,
    ParameterList_eUpdateInternalDataQTaskEvent,
    SCamera_SCameraLensUpdateInternalDataHandler);
  QTask_LinkQTaskEventHandlerFn(
    v3,
    GameFunctions_eWeaponHitQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))sub_499270);
  QTask_LinkQTaskEventHandlerFn(v3, GameFunctions_eExplosionHitQTaskEvent, SCamera_SCameraLensExplosionHitHandler);
  QTask_LinkQTaskEventHandlerFn(
    v3,
    AIDetection_eLineOfSightQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))SCamera_SCameraLensAIDetectionLineOfSightHandler);
  QTask_LinkQTaskEventHandlerFn(v3, 5, SCamera_SCameraLensEnterHandler);
  v4 = ComputerObject_eDrawComputerObjectQTaskEvent;
  if ( ComputerObject_eDrawComputerObjectQTaskEvent == 512 )
  {
    v4 = QTask_NewQTaskEventFn(0x200u, "DrawComputerObject");
    v3 = SCamera_eSCameraLensQTaskType;
    ComputerObject_eDrawComputerObjectQTaskEvent = v4;
  }
  QTask_LinkQTaskEventHandlerFn(v3, v4, SCamera_SCameraLensDrawComputerObjectHandler);
  v5 = ComputerObject_eDrawCameraConeQTaskEvent;
  if ( ComputerObject_eDrawCameraConeQTaskEvent == 512 )
  {
    v5 = QTask_NewQTaskEventFn(0x200u, "DrawCameraCone");
    v3 = SCamera_eSCameraLensQTaskType;
    ComputerObject_eDrawCameraConeQTaskEvent = v5;
  }
  QTask_LinkQTaskEventHandlerFn(v3, v5, SCamera_SCameraLensDrawCameraConeHandler);
  QTask_LinkQTaskEventHandlerFn(
    v3,
    DynCubeObj_eDynCubeObjRemoveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))sub_49A790);
  QTask_LinkQTaskEventHandlerFn(v3, DynCubeObj_eDynCubeObjRegisterQTaskEvent, SCamera_SCameraLensRegisterHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(
    v3,
    Level_eUpdateInternalDataAfterLoadEvent,
    SCamera_SCameraLensUpdateInternalDataAfterLoadHandler);
  SCamera_ptLightGameSprite = GameFunctions_RegisterGameSprite("alarmlight.spr");
  SCamera_ptSCameraLensQTaskList = QTaskList_New(64);
  v6 = QTask_NewQTaskType("SCameraLensViewCone", 328, RigidMagicObj_eQTaskType, 0, 0);
  SCamera_eSCameraLensViewConeQTaskType = v6;
  QTask_LinkQTaskEventHandlerFn(v6, GameFunctions_eWeaponHitQTaskEvent, nullptr);
  QTask_LinkQTaskEventHandlerFn(v6, GameFunctions_eExplosionHitQTaskEvent, nullptr);
  QTask_LinkQTaskEventHandlerFn(v6, AIDetection_eLineOfSightQTaskEvent, nullptr);
  QTask_LinkQTaskEventHandlerFn(v6, 13, nullptr);
  QTask_LinkQTaskEventHandlerFn(v6, 11, nullptr);
  QTask_LinkQTaskEventHandlerFn(v6, 12, nullptr);
  v7 = QCube_eGetClosestVertexQTaskEvent;
  QTask_LinkQTaskEventHandlerFn(v6, QCube_eGetClosestVertexQTaskEvent, nullptr);
  QTask_LinkQTaskEventHandlerFn(v6, 10, nullptr);
  QTask_LinkQTaskEventHandlerFn(v6, 9, nullptr);
  QTask_LinkQTaskEventHandlerFn(v6, 13, nullptr);
  QTask_LinkQTaskEventHandlerFn(v6, v7, nullptr);
  Symbol_Register(
    "TASKTYPE_SCAMERALENSVIEWCONE",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)v6,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  v8 = SCamera_eQTaskType;
  SCamera_bAIDetectionQTaskMask = AIDetection_AllocateQTaskMask(SCamera_eQTaskType);
  QTask_LinkQTaskEventHandlerFn(
    v8,
    Serialize_eGetSerializeParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))SCamera_GetSerializeParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(v8, Serialize_eDeSerializeQTaskEvent, SCamera_DeSerializeHandler);
  QTask_LinkQTaskEventHandlerFn(v8, Serialize_eSerializeQTaskEvent, SCamera_SerializeHandler);
  SCamera_ptSerializeParameterList = ParameterList_Derive(ModelObjParameters_ptSerializeParameterList, 6);
  ParameterList_AddParameter(
    SCamera_ptSerializeParameterList,
    0x1B4u,
    Level_eParameterTypebool8,
    "isDeadFriend",
    7u,
    nullptr);
  ParameterList_AddParameter(SCamera_ptSerializeParameterList, 0x1B8u, Level_eParameterTypebool8, "isOn", 7u, nullptr);
  ParameterList_AddParameter(
    SCamera_ptSerializeParameterList,
    0x1B9u,
    Level_eParameterTypebool8,
    "isDetection",
    7u,
    nullptr);
  ParameterList_AddParameter(
    SCamera_ptSerializeParameterList,
    0x1BAu,
    Level_eParameterTypebool8,
    "isLastDetection",
    7u,
    nullptr);
  ParameterList_AddParameter(
    SCamera_ptSerializeParameterList,
    0x1BCu,
    Level_eParameterTypeInt32,
    "nDetectionTime",
    7u,
    nullptr);
  ParameterList_AddParameter(
    SCamera_ptSerializeParameterList,
    0x1C4u,
    Level_eParameterTypebool8,
    "isDestroyed",
    7u,
    nullptr);
  v9 = SCamera_eSCameraLensQTaskType;
  QTask_LinkQTaskEventHandlerFn(
    SCamera_eSCameraLensQTaskType,
    Serialize_eGetSerializeParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))SCameraLens_GetSerializeParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(v9, Serialize_eDeSerializeQTaskEvent, SCameraLens_DeSerializeHandler);
  SCameraLens_ptSerializeParameterList = ParameterList_Derive(ModelObjParameters_ptSerializeParameterList, 15);
  ParameterList_AddParameter(
    SCameraLens_ptSerializeParameterList,
    0x140u,
    Level_eParameterTypeReal32,
    "vAlpha",
    7u,
    nullptr);
  ParameterList_AddParameter(
    SCameraLens_ptSerializeParameterList,
    0x144u,
    Level_eParameterTypeReal32,
    "vGamma",
    7u,
    nullptr);
  ParameterList_AddParameter(
    SCameraLens_ptSerializeParameterList,
    0x148u,
    Level_eParameterTypeReal32,
    "vIdealGamma",
    7u,
    nullptr);
  ParameterList_AddParameter(
    SCameraLens_ptSerializeParameterList,
    0x14Cu,
    Level_eParameterTypeInt32,
    "nGammaDelay",
    7u,
    nullptr);
  ParameterList_AddParameter(
    SCameraLens_ptSerializeParameterList,
    0x150u,
    Level_eParameterTypeInt32,
    "nRotateDirection",
    7u,
    nullptr);
  ParameterList_AddParameter(
    SCameraLens_ptSerializeParameterList,
    0x154u,
    Level_eParameterTypeReal32,
    "vDamage",
    7u,
    nullptr);
  ParameterList_AddParameter(
    SCameraLens_ptSerializeParameterList,
    0x158u,
    Level_eParameterTypeReal32,
    "vMaxDamage",
    7u,
    nullptr);
  ParameterList_AddParameter(
    SCameraLens_ptSerializeParameterList,
    0x5010u,
    Level_eParameterTypeInt32,
    "eTeam",
    7u,
    nullptr);
  ParameterList_AddParameter(
    SCameraLens_ptSerializeParameterList,
    0x5018u,
    Level_eParameterTypeInt32,
    "nTrackTimeOut",
    7u,
    nullptr);
  ParameterList_AddParameter(
    SCameraLens_ptSerializeParameterList,
    0x5028u,
    Level_eParameterTypebool8,
    "isExplode",
    7u,
    nullptr);
  ParameterList_AddParameter(
    SCameraLens_ptSerializeParameterList,
    0x5030u,
    Level_eParameterTypeInt32,
    "nSizeTimer",
    7u,
    nullptr);
  ParameterList_AddParameter(
    SCameraLens_ptSerializeParameterList,
    0x5034u,
    Level_eParameterTypeInt32,
    "nFrameTimer",
    7u,
    nullptr);
  ParameterList_AddParameter(
    SCameraLens_ptSerializeParameterList,
    0x5038u,
    Level_eParameterTypebool8,
    "isBig",
    7u,
    nullptr);
  ParameterList_AddParameter(
    SCameraLens_ptSerializeParameterList,
    0x5039u,
    Level_eParameterTypebool8,
    "isShowConeThisFrame",
    7u,
    nullptr);
  ParameterList_AddParameter(
    SCameraLens_ptSerializeParameterList,
    0x503Cu,
    Level_eParameterTypeInt32,
    "nFrame",
    7u,
    nullptr);
}

// source: j/0/objects/scamera.c:2733  [size]
void __cdecl SCamera_Close()
{
  int v0; // esi
  int v1; // esi
  int v2; // esi

  if ( SCamera_ptParameterList )
  {
    v0 = *(_DWORD *)((unsigned int)&SCamera_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
  if ( SCamera_ptSerializeParameterList )
  {
    v1 = *(_DWORD *)((unsigned int)&SCamera_ptSerializeParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v1);
    memset(*(void **)(v1 + 8), 0xCDu, *(_DWORD *)(v1 + 16));
    free((void *)v1);
  }
  if ( SCameraLens_ptSerializeParameterList )
  {
    v2 = *(_DWORD *)((unsigned int)&SCameraLens_ptSerializeParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v2);
    memset(*(void **)(v2 + 8), 0xCDu, *(_DWORD *)(v2 + 16));
    free((void *)v2);
  }
  QTask_DeleteQTaskType(SCamera_eSCameraLensViewConeQTaskType);
  QTask_DeleteQTaskType(SCamera_eSCameraLensQTaskType);
  QTask_DeleteQTaskType(SCamera_eQTaskType);
  QTaskList_Delete(SCamera_ptSCameraLensQTaskList);
}
