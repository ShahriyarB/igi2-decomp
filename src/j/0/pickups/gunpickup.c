/* j/0/pickups/gunpickup.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/pickups/gunpickup.c:150  [size]
void __cdecl GunPickup_GetSerializeInfoHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = 1;
  *((_DWORD *)pxContext + 1) = 1;
}

// source: j/0/pickups/gunpickup.c:169  [size]
void __cdecl GunPickup_GetSerializeParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = GunPickup_ptSerializeParameterList;
}

// source: j/0/pickups/gunpickup.c:187  [anchor-mhash]
void __cdecl GunPickup_DeSerializeHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct WeaponType_s *WeaponTypeFromID; // eax
  struct LODVirModel_s *LODVirModelExistsFn; // eax

  ((void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[Serialize_eDeSerializeQTaskEvent][SectorInteriorObject_eQTaskType].pfHandler)(
    ptQTask,
    pxContext);
  qmemcpy(&ptQTask[8].tQTaskChildren.ptTail, &ptQTask[1], 0x18u);
  WeaponTypeFromID = WeaponType_GetWeaponTypeFromID((int)ptQTask[10].tQTaskChildren.ptTail);
  if ( WeaponTypeFromID )
  {
    LODVirModelExistsFn = MTP_GetLODVirModelExistsFn(WeaponTypeFromID->zFixedModel);
    if ( LODVirModelExistsFn != *(struct LODVirModel_s **)&ptQTask[2].eQTaskType )
    {
      ModelObj_SetLODVirModel((struct ModelObj_s *)ptQTask, LODVirModelExistsFn, false);
      ptQTask[7].tQTaskRefList.ptHead = nullptr;
      ptQTask[7].tQTaskRefList.ptMiddle = nullptr;
      ptQTask[7].tQTaskRefList.ptTail = nullptr;
      ptQTask[7].ptParent = nullptr;
      *(_DWORD *)&ptQTask[7].eQTaskType = 0;
    }
  }
}

// source: j/0/pickups/gunpickup.c:218  [size]
void __cdecl GunPickup_GetGameItemDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *((_WORD *)pxContext + 1) = 40;
  *(_WORD *)pxContext = ptQTask[11].tQTaskChildren.ptMiddle;
  *((_WORD *)pxContext + 2) = GunPickup_eQTaskType;
  *(_DWORD *)((char *)pxContext + 6) = ptQTask[10].tQTaskChildren.ptTail;
  qmemcpy((char *)pxContext + 22, &ptQTask[8].tQTaskChildren.ptTail, 0x18u);
  *(_DWORD *)((char *)pxContext + 10) = ptQTask[8].ptNext;
  *(_DWORD *)((char *)pxContext + 14) = ptQTask[8].ptPrev;
  *(_DWORD *)((char *)pxContext + 18) = ptQTask[8].tQTaskChildren.ptHead;
}

// source: j/0/pickups/gunpickup.c:257  [anchor-mhash]
void __cdecl GunPickup_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct World_s *ptDynCubeObj; };
    struct { float ptDynCubeObja; };
    struct { char igi2_o2[24]; struct real64x3_t ptPos; };
    char igi2_extent[52];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct Game_s *v2; // eax
  double v3; // st7
  double v4; // st7
  int *v5; // eax
  int v6; // eax
  double v7; // st6
  bool v8; // zf

  v2 = Game_ptGame;
  LOBYTE(ptQTask[12].tQTaskRefList.ptHead) = 0;
  BYTE1(ptQTask[12].tQTaskRefList.ptHead) = 0;
  BYTE2(ptQTask[12].tQTaskRefList.ptHead) = 0;
  ptQTask[12].tQTaskChildren.ptHead = nullptr;
  ptQTask[12].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[12].tQTaskRefList.ptTail = nullptr;
  ptQTask[12].ptParent = (struct QTask_s *)1065353216;
  igi2_frame.ptDynCubeObj = v2->ptWorld;
  memset(&igi2_frame.ptPos, 0, sizeof(igi2_frame.ptPos));
  ModelObj_Init((struct ModelObj_s *)ptQTask, igi2_frame.ptDynCubeObj, nullptr);
  ptQTask[7].tQTaskChildren.ptHead = nullptr;
  ptQTask[7].tQTaskChildren.ptMiddle = (struct QTask_s *)2;
  ptQTask[7].tQTaskRefList.ptHead = nullptr;
  ptQTask[7].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[7].tQTaskRefList.ptTail = nullptr;
  ptQTask[7].ptParent = nullptr;
  *(_DWORD *)&ptQTask[7].eQTaskType = 0;
  if ( *(float *)&ptQTask[6].tQTaskChildren.ptHead <= (double)*(float *)&ptQTask[6].tQTaskChildren.ptMiddle )
    v3 = *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
  else
    v3 = *(float *)&ptQTask[6].tQTaskChildren.ptHead;
  if ( v3 >= *(float *)&ptQTask[6].ptPrev )
  {
    if ( *(float *)&ptQTask[6].tQTaskChildren.ptHead <= (double)*(float *)&ptQTask[6].tQTaskChildren.ptMiddle )
      v4 = *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
    else
      v4 = *(float *)&ptQTask[6].tQTaskChildren.ptHead;
  }
  else
  {
    v4 = *(float *)&ptQTask[6].ptPrev;
  }
  v5 = *(int **)&ptQTask[2].eQTaskType;
  if ( v5 && (v6 = *v5) != 0 )
    v7 = *(float *)(*(_DWORD *)(*(_DWORD *)(v6 + 12) + 12) + 120);
  else
    v7 = 1.0;
  igi2_frame.ptDynCubeObja = v4 * v7;
  World_RegisterDynCubeObjFirstTimeRadius(
    Game_ptGame->ptWorld,
    (struct DynCubeObj_s *)ptQTask,
    &igi2_frame.ptPos,
    igi2_frame.ptDynCubeObja,
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
  v8 = Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER;
  ptQTask[8].tQTaskChildren.ptTail = nullptr;
  ptQTask[8].tQTaskRefList.ptHead = nullptr;
  ptQTask[8].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[8].tQTaskRefList.ptTail = nullptr;
  ptQTask[8].ptParent = nullptr;
  *(_DWORD *)&ptQTask[8].eQTaskType = 0;
  ptQTask[9].ptNext = nullptr;
  ptQTask[9].ptPrev = nullptr;
  ptQTask[9].tQTaskChildren.ptHead = nullptr;
  ptQTask[9].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[9].tQTaskChildren.ptTail = nullptr;
  ptQTask[9].tQTaskRefList.ptHead = nullptr;
  ptQTask[10].tQTaskChildren.ptHead = nullptr;
  ptQTask[10].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[10].tQTaskChildren.ptTail = (struct QTask_s *)12;
  LOBYTE(ptQTask[10].tQTaskRefList.ptHead) = 0;
  strcpy((char *)&ptQTask[11].tQTaskChildren.ptMiddle + 2, "10 * GAME_FREQUENCY");
  ptQTask[12].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[12].tQTaskChildren.ptTail = nullptr;
  if ( v8 )
  {
    LOWORD(ptQTask[11].tQTaskChildren.ptMiddle) = NetworkGameItem_RegisterGameItem(
                                                    ptQTask,
                                                    0x28u,
                                                    GunPickup_iGameItemID);
    GunPickup_iGameItemID = 0;
  }
  QTaskList_Register(GameFunctions_ptPickupQTaskList, (struct QTaskList_s *)ptQTask);
  ptQTask[8].ptNext = nullptr;
  ptQTask[8].ptPrev = nullptr;
  ptQTask[8].tQTaskChildren.ptHead = nullptr;
  *(_DWORD *)&ptQTask[12].eQTaskType = 0;
}

// source: j/0/pickups/gunpickup.c:337  [anchor-caller]
void __cdecl GunPickup_RunHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { float ptDynCubeObj; };
    struct { float ptDynCubeObja; };
    struct { char igi2_o2[24]; float tReal32x3; };
    struct { char igi2_o3[28]; float tReal32x3_4; };
    struct { char igi2_o4[28]; float tReal32x3_4a; };
    struct { char igi2_o5[28]; float tReal32x3_4b; };
    struct { char igi2_o6[28]; float tReal32x3_4c; };
    struct { char igi2_o7[32]; float tReal32x3_8; };
    struct { char igi2_o8[32]; float tReal32x3_8a; };
    struct { char igi2_o9[32]; float tReal32x3_8b; };
    struct { char igi2_o10[32]; float tReal32x3_8c; };
    struct { char igi2_o11[32]; float tReal32x3_8d; };
    struct { char igi2_o12[32]; float tReal32x3_8e; };
    struct { char igi2_o13[32]; float tReal32x3_8f; };
    struct { char igi2_o14[36]; struct QReference_s *tDelta; };
    struct { char igi2_o15[36]; struct QReference_s *tDeltaa; };
    struct { char igi2_o16[36]; double tDeltab; };
    struct { char igi2_o17[36]; double tDeltac; };
    struct { char igi2_o18[40]; float tDelta_4; };
    struct { char igi2_o19[40]; float tDelta_4a; };
    struct { char igi2_o20[40]; float tDelta_4b; };
    struct { char igi2_o21[40]; float tDelta_4c; };
    struct { char igi2_o22[44]; float tDelta_8; };
    struct { char igi2_o23[44]; float tDelta_8a; };
    struct { char igi2_o24[44]; float tDelta_8b; };
    struct { char igi2_o25[44]; float tDelta_8c; };
    struct { char igi2_o26[52]; int nHits; };
    struct { char igi2_o27[52]; float nHitsa; };
    struct { char igi2_o28[52]; float nHitsb; };
    struct { char igi2_o29[56]; int vRadius; };
    struct { char igi2_o30[56]; float vRadiusa; };
    struct { char igi2_o31[56]; float vRadiusb; };
    struct { char igi2_o32[60]; struct QTask_s *vBeta; };
    struct { char igi2_o33[60]; float vBetaa; };
    struct { char igi2_o34[60]; float vBetab; };
    struct { char igi2_o35[60]; double vBetac; };
    struct { char igi2_o36[68]; double vGamma; };
    struct { char igi2_o37[76]; struct real32x9_t tReal32x9; };
    struct { char igi2_o38[116]; struct real64x3_t atNewPos[6]; };
    struct { char igi2_o39[260]; struct real32x9_t Real32x9_Multiply_tTemp; };
    struct { char igi2_o40[300]; struct ObjectCollisionEvaluateContext_t tContext; };
    struct { char igi2_o41[308]; struct QIntersection_s atIntersection[6]; };
    struct { char igi2_o42[1028]; struct real64x3_t atStartPos[6]; };
    char igi2_extent[1172];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *ptNetManagerQTask; // edx
  struct QTask_s *ptBombComputerHighlightQTask; // eax
  struct QTask_s *v3; // edi
  struct QTask_s *v4; // eax
  struct NetObjective_t *Objective; // eax
  unsigned __int16 v6; // dx
  struct QTask_s *FirstChildOfType; // eax
  int v8; // esi
  struct QTask_s *v9; // eax
  double v10; // st7
  double v11; // st7
  char *LocalizedString; // eax
  double v13; // st7
  double v14; // st7
  int *v15; // eax
  int v16; // eax
  double v17; // st6
  double v18; // st7
  double v19; // st6
  double v20; // st7
  double v21; // st5
  struct QReference_s *ptTail; // ecx
  struct QTask_s *ptParent; // edx
  double v24; // st6
  double v25; // st6
  struct QReference_s *v26; // ecx
  struct QTask_s *v27; // edx
  double *p_ptTail; // ebx
  double v29; // st7
  double v30; // st7
  double v31; // st6
  double v32; // st4
  double v33; // st3
  double v34; // st4
  double v35; // st3
  double v36; // st5
  double v37; // st4
  double v38; // st4
  double v39; // st7
  double v40; // st6
  double *p_vY; // esi
  float *p_vZ; // ecx
  __int16 v43; // ax
  double v44; // st5
  double v45; // st4
  float *p_ptMiddle; // edx
  double v47; // st5
  double v48; // st4
  double v49; // st4
  double v50; // st5
  bool v51; // zf
  float *v52; // ecx
  double v53; // st7
  long double v54; // st3
  double v55; // st7
  double v56; // st6
  long double v57; // st3
  struct Game_s *v58; // eax
  unsigned int v59; // edi
  unsigned int v60; // ecx
  int v61; // edi
  unsigned int v62; // edx
  char *v63; // eax
  struct QTask_s *v64; // eax
  struct QObj_s *ptHitObj; // eax
  unsigned __int16 eQTaskType; // ax
  double v67; // st7
  double v68; // st6
  double v69; // st7
  double v70; // st7
  double v71; // st7
  double v72; // st7
  int *v73; // eax
  int v74; // eax
  double v75; // st6

  if ( Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER
    && ptQTask[10].tQTaskChildren.ptTail == (struct QTask_s *)Script_ParseLineInt32("WEAPON_ID_C4BOMB") )
  {
    ptNetManagerQTask = Flow_ptFlow->ptNetManagerQTask;
    if ( NetMission_ptNetMission )
    {
      ptBombComputerHighlightQTask = NetMission_ptNetMission->ptBombComputerHighlightQTask;
      if ( ptBombComputerHighlightQTask )
      {
        qmemcpy(&ptBombComputerHighlightQTask[1], &ptQTask[1], 0x18u);
        *(double *)&ptBombComputerHighlightQTask[1].tQTaskChildren.ptTail = *(double *)&ptBombComputerHighlightQTask[1].tQTaskChildren.ptTail
                                                                          + 8192.0;
      }
    }
    if ( (int)ptNetManagerQTask[5].ptParent > 0 )
    {
      v3 = (struct QTask_s *)((char *)&ptQTask[12].tQTaskChildren.ptHead->ptNext + 1);
      ptQTask[12].tQTaskChildren.ptHead = v3;
      v4 = v3;
      if ( (int)v3 >= 30 * (int)ptNetManagerQTask[5].ptParent + 1 )
        v4 = (struct QTask_s *)(30 * (int)ptNetManagerQTask[5].ptParent + 1);
      ptQTask[12].tQTaskChildren.ptHead = v4;
      if ( v4 == (struct QTask_s *)(30 * (int)ptNetManagerQTask[5].ptParent) )
      {
        Objective = NetMission_GetObjective(1);
        v6 = SpawnArea_eQTaskType;
        FirstChildOfType = QTask_GetFirstChildOfType(&Objective->tQTask, SpawnArea_eQTaskType);
        if ( !FirstChildOfType )
        {
LABEL_14:
          LDebug_Error("No spawn area for attacking team exist on this objective\n");
          abort();
        }
        v8 = NetMission_eAttackingTeam;
        while ( FirstChildOfType[6].tQTaskChildren.ptHead != (struct QTask_s *)v8 )
        {
          FirstChildOfType = QTask_GetNextSiblingOfType(FirstChildOfType, v6);
          if ( !FirstChildOfType )
            goto LABEL_14;
        }
        v9 = QTask_GetFirstChildOfType(FirstChildOfType, SpawnPoint_eQTaskType);
        SpawnPoint_GetPositionAndOrientation(
          (struct real64x3_t *)&ptQTask[8].tQTaskChildren.ptTail,
          (float *)&igi2_frame.vGamma,
          v9);
        v10 = *(double *)&ptQTask[8].ptParent + 4096.0;
        BYTE1(ptQTask[12].tQTaskRefList.ptHead) = 1;
        *(double *)&ptQTask[8].ptParent = v10;
        if ( *(float *)&ptQTask[6].tQTaskChildren.ptHead <= (double)*(float *)&ptQTask[6].tQTaskChildren.ptMiddle )
          v11 = *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
        else
          v11 = *(float *)&ptQTask[6].tQTaskChildren.ptHead;
        if ( v11 >= *(float *)&ptQTask[6].ptPrev )
        {
          if ( *(float *)&ptQTask[6].tQTaskChildren.ptHead <= (double)*(float *)&ptQTask[6].tQTaskChildren.ptMiddle )
            igi2_frame.vBeta = ptQTask[6].tQTaskChildren.ptMiddle;
          else
            igi2_frame.vBeta = ptQTask[6].tQTaskChildren.ptHead;
        }
        else
        {
          igi2_frame.vBeta = ptQTask[6].ptPrev;
        }
        igi2_frame.ptDynCubeObj = Mesh3D_GetLODVirModelRadius(*(struct LODVirModel_s **)&ptQTask[2].eQTaskType) * *(float *)&igi2_frame.vBeta;
        World_MoveDynCubeObjRadius(
          Game_ptGame->ptWorld,
          (struct DynCubeObj_s *)ptQTask,
          (struct real64x3_t *)&ptQTask[8].tQTaskChildren.ptTail,
          igi2_frame.ptDynCubeObj);
        RigidDynCubeObj_UpdateAttachments((struct RigidDynCubeObj_t *)ptQTask);
        LocalizedString = Config_GetLocalizedString("mp/Bomb repositioned to spawn area on objective 1");
        StatusScreen_ShowCritical(LocalizedString, TEXTSCROLLER_COLOUR_RED);
      }
    }
  }
  if ( BYTE1(ptQTask[12].tQTaskRefList.ptHead) )
  {
    *(float *)&igi2_frame.vGamma = *(float *)&ptQTask[9].ptParent - 44.600887298583984;
    ptQTask[9].ptParent = (struct QTask_s *)LODWORD(igi2_frame.vGamma);
    if ( *(float *)&ptQTask[6].tQTaskChildren.ptHead <= (double)*(float *)&ptQTask[6].tQTaskChildren.ptMiddle )
      v13 = *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
    else
      v13 = *(float *)&ptQTask[6].tQTaskChildren.ptHead;
    if ( v13 >= *(float *)&ptQTask[6].ptPrev )
    {
      if ( *(float *)&ptQTask[6].tQTaskChildren.ptHead <= (double)*(float *)&ptQTask[6].tQTaskChildren.ptMiddle )
        v14 = *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
      else
        v14 = *(float *)&ptQTask[6].tQTaskChildren.ptHead;
    }
    else
    {
      v14 = *(float *)&ptQTask[6].ptPrev;
    }
    v15 = *(int **)&ptQTask[2].eQTaskType;
    if ( v15 && (v16 = *v15) != 0 )
      v17 = *(float *)(*(_DWORD *)(*(_DWORD *)(v16 + 12) + 12) + 120);
    else
      v17 = 1.0;
    v18 = v14 * v17;
    igi2_frame.vRadiusa = v18;
    igi2_frame.vBetab = *(float *)&ptQTask[12].ptParent * 0.0;
    igi2_frame.nHitsa = *(float *)&ptQTask[12].tQTaskRefList.ptMiddle * 0.0;
    v19 = v18;
    v20 = -igi2_frame.vRadiusa;
    v21 = v19 * *(float *)&ptQTask[12].tQTaskRefList.ptTail + igi2_frame.nHitsa + igi2_frame.vBetab;
    igi2_frame.tDelta = ptQTask[12].tQTaskRefList.ptMiddle;
    ptTail = ptQTask[12].tQTaskRefList.ptTail;
    ptParent = ptQTask[12].ptParent;
    igi2_frame.tDelta_4 = *(float *)&ptTail * v21;
    igi2_frame.tDelta_8 = *(float *)&ptParent * v21;
    igi2_frame.atNewPos[0].vX = -(*(float *)&igi2_frame.tDelta * v21);
    igi2_frame.atNewPos[0].vY = v19 - igi2_frame.tDelta_4;
    igi2_frame.atNewPos[0].vZ = -igi2_frame.tDelta_8;
    igi2_frame.vRadiusb = *(float *)&ptQTask[12].tQTaskRefList.ptTail * 0.0;
    v24 = *(float *)&ptQTask[12].ptParent * 819.2000122070312 + igi2_frame.vRadiusb + igi2_frame.nHitsa;
    igi2_frame.tDelta_4a = *(float *)&ptTail * v24;
    igi2_frame.tDelta_8a = *(float *)&ptParent * v24;
    igi2_frame.atNewPos[1].vX = -(*(float *)&igi2_frame.tDelta * v24);
    igi2_frame.atNewPos[1].vY = -igi2_frame.tDelta_4a;
    igi2_frame.atNewPos[1].vZ = 819.2000122070312 - igi2_frame.tDelta_8a;
    v25 = v20 * *(float *)&ptQTask[12].tQTaskRefList.ptTail + igi2_frame.nHitsa + igi2_frame.vBetab;
    v26 = ptQTask[12].tQTaskRefList.ptTail;
    igi2_frame.tDelta_4b = *(float *)&v26 * v25;
    igi2_frame.tDeltaa = ptQTask[12].tQTaskRefList.ptMiddle;
    v27 = ptQTask[12].ptParent;
    p_ptTail = (double *)&ptQTask[8].tQTaskChildren.ptTail;
    igi2_frame.tDelta_8b = *(float *)&v27 * v25;
    igi2_frame.atNewPos[2].vX = -(*(float *)&igi2_frame.tDeltaa * v25);
    qmemcpy(igi2_frame.atStartPos, &ptQTask[8].tQTaskChildren.ptTail, 0x18u);
    igi2_frame.atNewPos[2].vY = v20 - igi2_frame.tDelta_4b;
    igi2_frame.atNewPos[2].vZ = -igi2_frame.tDelta_8b;
    v29 = igi2_frame.vRadiusb - *(float *)&ptQTask[12].ptParent * 819.2000122070312 + igi2_frame.nHitsa;
    igi2_frame.tDelta_4c = *(float *)&v26 * v29;
    igi2_frame.tDelta_8c = *(float *)&v27 * v29;
    igi2_frame.atNewPos[3].vX = -(*(float *)&igi2_frame.tDeltaa * v29);
    igi2_frame.atNewPos[3].vY = -igi2_frame.tDelta_4c;
    igi2_frame.atNewPos[3].vZ = -819.2000122070312 - igi2_frame.tDelta_8c;
    igi2_frame.atNewPos[0].vX = igi2_frame.atNewPos[0].vX + *(double *)&ptQTask[8].tQTaskChildren.ptTail;
    igi2_frame.atNewPos[0].vY = igi2_frame.atNewPos[0].vY + *(double *)&ptQTask[8].tQTaskRefList.ptMiddle;
    igi2_frame.atNewPos[0].vZ = igi2_frame.atNewPos[0].vZ + *(double *)&ptQTask[8].ptParent;
    v30 = *(float *)&ptQTask[9].tQTaskRefList.ptMiddle;
    igi2_frame.atNewPos[0].vX = igi2_frame.atNewPos[0].vX + v30;
    v31 = *(float *)&ptQTask[9].tQTaskRefList.ptTail;
    igi2_frame.atNewPos[0].vY = igi2_frame.atNewPos[0].vY + v31;
    igi2_frame.vGamma = *(float *)&igi2_frame.vGamma;
    qmemcpy(&igi2_frame.atStartPos[1], &ptQTask[8].tQTaskChildren.ptTail, sizeof(struct real64x3_t));
    igi2_frame.atNewPos[0].vZ = igi2_frame.atNewPos[0].vZ + igi2_frame.vGamma;
    v32 = igi2_frame.atNewPos[1].vX + *(double *)&ptQTask[8].tQTaskChildren.ptTail;
    v33 = igi2_frame.atNewPos[1].vY + *(double *)&ptQTask[8].tQTaskRefList.ptMiddle;
    igi2_frame.atNewPos[1].vZ = igi2_frame.atNewPos[1].vZ + *(double *)&ptQTask[8].ptParent;
    qmemcpy(&igi2_frame.atStartPos[2], &ptQTask[8].tQTaskChildren.ptTail, sizeof(struct real64x3_t));
    igi2_frame.atNewPos[1].vX = v30 + v32;
    igi2_frame.atNewPos[1].vY = v31 + v33;
    igi2_frame.atNewPos[1].vZ = igi2_frame.atNewPos[1].vZ + igi2_frame.vGamma;
    qmemcpy(&igi2_frame.atStartPos[3], &ptQTask[8].tQTaskChildren.ptTail, sizeof(struct real64x3_t));
    v34 = igi2_frame.atNewPos[2].vX + *(double *)&ptQTask[8].tQTaskChildren.ptTail;
    v35 = igi2_frame.atNewPos[2].vY + *(double *)&ptQTask[8].tQTaskRefList.ptMiddle;
    igi2_frame.atNewPos[2].vZ = igi2_frame.atNewPos[2].vZ + *(double *)&ptQTask[8].ptParent;
    igi2_frame.atNewPos[2].vX = v30 + v34;
    qmemcpy(&igi2_frame.atStartPos[4], &ptQTask[8].tQTaskChildren.ptTail, sizeof(struct real64x3_t));
    igi2_frame.atNewPos[2].vY = v31 + v35;
    igi2_frame.atNewPos[2].vZ = igi2_frame.vGamma + igi2_frame.atNewPos[2].vZ;
    v36 = igi2_frame.atNewPos[3].vX + *(double *)&ptQTask[8].tQTaskChildren.ptTail;
    v37 = *(double *)&ptQTask[8].tQTaskRefList.ptMiddle - igi2_frame.tDelta_4c;
    qmemcpy(&igi2_frame.atStartPos[5], &ptQTask[8].tQTaskChildren.ptTail, sizeof(struct real64x3_t));
    igi2_frame.atNewPos[3].vY = v37;
    v38 = igi2_frame.atNewPos[3].vZ + *(double *)&ptQTask[8].ptParent;
    igi2_frame.atNewPos[3].vX = v30 + v36;
    igi2_frame.atNewPos[3].vY = v31 + igi2_frame.atNewPos[3].vY;
    igi2_frame.atNewPos[3].vZ = igi2_frame.vGamma + v38;
    qmemcpy(&igi2_frame.atNewPos[4], &ptQTask[8].tQTaskChildren.ptTail, sizeof(struct real64x3_t));
    igi2_frame.atNewPos[4].vZ = igi2_frame.atNewPos[4].vZ - 8192.0;
    qmemcpy(&igi2_frame.atNewPos[5], &ptQTask[8].tQTaskChildren.ptTail, sizeof(struct real64x3_t));
    igi2_frame.atNewPos[5].vZ = igi2_frame.atNewPos[5].vZ + 20480.0;
    igi2_frame.tContext.tCollisionEvaluateContext.ptQTask = ptQTask;
    World_TraceLinesSpecificMesh(
      Game_ptGame->ptWorld,
      igi2_frame.atIntersection,
      igi2_frame.atStartPos,
      igi2_frame.atNewPos,
      6,
      GameFunctions_eObjectCollisionEvaluateQTaskEvent,
      &igi2_frame.tContext.tCollisionEvaluateContext,
      Forest_bQTaskGroup | 0xD8000000,
      1);
    if ( !igi2_frame.atIntersection[0].isHit
      && !igi2_frame.atIntersection[1].isHit
      && !igi2_frame.atIntersection[2].isHit
      && !igi2_frame.atIntersection[3].isHit
      && !igi2_frame.atIntersection[4].isHit
      && !igi2_frame.atIntersection[5].isHit )
    {
      goto LABEL_107;
    }
    v39 = 0.0;
    igi2_frame.tReal32x9.tX.vZ = 0.0;
    v40 = 0.0;
    igi2_frame.nHits = 0;
    p_vY = &igi2_frame.atNewPos[0].vY;
    p_vZ = &igi2_frame.atIntersection[0].tNormal.vZ;
    igi2_frame.vRadius = 4;
    do
    {
      if ( *((_DWORD *)p_vZ + 7) )
      {
        v43 = *(_WORD *)(*((_DWORD *)p_vZ - 16) + 36);
        if ( v43 != Terrain_eQTaskType && v43 != Water_eQTaskType )
        {
          if ( *(p_vZ - 2) != 0.0 || *(p_vZ - 1) != 0.0 || *p_vZ != 0.0 )
          {
            v44 = *p_vZ;
            igi2_frame.tDeltab = *(p_vZ - 1);
            igi2_frame.vBetac = *(p_vZ - 2);
            *(float *)&igi2_frame.vGamma = sqrt(igi2_frame.vBetac * igi2_frame.vBetac + igi2_frame.tDeltab * igi2_frame.tDeltab + v44 * v44);
            v45 = 1.0 / *(float *)&igi2_frame.vGamma;
            *(p_vZ - 2) = igi2_frame.vBetac * v45;
            *(p_vZ - 1) = igi2_frame.tDeltab * v45;
            *p_vZ = v44 * v45;
          }
          p_ptMiddle = (float *)&ptQTask[9].tQTaskRefList.ptMiddle;
          v47 = *(p_vZ - 2) * *(float *)&ptQTask[9].tQTaskRefList.ptMiddle
              + *(p_vZ - 1) * *(float *)&ptQTask[9].tQTaskRefList.ptTail
              + *(float *)&ptQTask[9].ptParent * *p_vZ;
          v48 = *(p_vZ - 2);
          igi2_frame.tReal32x3_4 = *(p_vZ - 1);
          igi2_frame.tReal32x3_8 = *p_vZ;
          if ( v47 >= 0.0 )
          {
            v48 = v48 * -1.0;
            igi2_frame.tReal32x3_4 = igi2_frame.tReal32x3_4 * -1.0;
            igi2_frame.tReal32x3_8 = igi2_frame.tReal32x3_8 * -1.0;
          }
          igi2_frame.tReal32x3_8a = igi2_frame.tReal32x3_8 * v47;
          *p_ptMiddle = *p_ptMiddle - v48 * v47;
          *(float *)&ptQTask[9].tQTaskRefList.ptTail = *(float *)&ptQTask[9].tQTaskRefList.ptTail - igi2_frame.tReal32x3_4 * v47;
          *(float *)&ptQTask[9].ptParent = *(float *)&ptQTask[9].ptParent - igi2_frame.tReal32x3_8a;
          v49 = *(float *)&ptQTask[9].tQTaskRefList.ptTail * 0.008333333767950535;
          ++igi2_frame.nHits;
          igi2_frame.tReal32x3_8b = *(float *)&ptQTask[9].ptParent * 0.008333333767950535;
          *p_ptMiddle = *p_ptMiddle - *p_ptMiddle * 0.008333333767950535;
          *(float *)&ptQTask[9].tQTaskRefList.ptTail = *(float *)&ptQTask[9].tQTaskRefList.ptTail - v49;
          *(float *)&ptQTask[9].ptParent = *(float *)&ptQTask[9].ptParent - igi2_frame.tReal32x3_8b;
          igi2_frame.tReal32x3_4a = *((double *)p_vZ - 6) - *p_vY;
          igi2_frame.tReal32x3_8c = *((double *)p_vZ - 5) - p_vY[1];
          v39 = v39 + *((double *)p_vZ - 7) - *(p_vY - 1);
          v40 = v40 + igi2_frame.tReal32x3_4a;
          igi2_frame.tReal32x9.tX.vZ = igi2_frame.tReal32x3_8c + igi2_frame.tReal32x9.tX.vZ;
        }
      }
      p_vZ += 30;
      p_vY += 3;
      --igi2_frame.vRadius;
    }
    while ( igi2_frame.vRadius );
    if ( igi2_frame.nHits > 1 )
    {
      v50 = 1.0 / (double)igi2_frame.nHits;
      v39 = v39 * v50;
      v40 = v40 * v50;
      igi2_frame.tReal32x9.tX.vZ = v50 * igi2_frame.tReal32x9.tX.vZ;
    }
    v51 = igi2_frame.atIntersection[4].isHit == 0;
    *p_ptTail = v39 + *p_ptTail;
    *(double *)&ptQTask[8].tQTaskRefList.ptMiddle = v40 + *(double *)&ptQTask[8].tQTaskRefList.ptMiddle;
    *(double *)&ptQTask[8].ptParent = igi2_frame.tReal32x9.tX.vZ + *(double *)&ptQTask[8].ptParent;
    if ( !v51
      && (igi2_frame.atIntersection[4].ptHitObj->tQTask.eQTaskType != Water_eQTaskType
       || ptQTask[10].tQTaskChildren.ptTail == (struct QTask_s *)Script_ParseLineInt32("WEAPON_ID_C4BOMB")) )
    {
      v52 = (float *)&ptQTask[12].tQTaskRefList.ptMiddle;
      *(struct real32x3_t *)&ptQTask[12].tQTaskRefList.ptMiddle = igi2_frame.atIntersection[4].tNormal;
      if ( *(float *)&ptQTask[12].tQTaskRefList.ptMiddle != 0.0
        || *(float *)&ptQTask[12].tQTaskRefList.ptTail != 0.0
        || *(float *)&ptQTask[12].ptParent != 0.0 )
      {
        v53 = *(float *)&ptQTask[12].ptParent;
        igi2_frame.vGamma = *(float *)&ptQTask[12].tQTaskRefList.ptTail;
        igi2_frame.tDeltac = *v52;
        v54 = sqrt(igi2_frame.tDeltac * igi2_frame.tDeltac + igi2_frame.vGamma * igi2_frame.vGamma + v53 * v53);
        *v52 = igi2_frame.tDeltac * (1.0 / v54);
        *(float *)&ptQTask[12].tQTaskRefList.ptTail = igi2_frame.vGamma * (1.0 / v54);
        *(float *)&ptQTask[12].ptParent = v53 * (1.0 / v54);
      }
      v55 = igi2_frame.atStartPos[4].vZ - igi2_frame.atIntersection[4].tPos.vZ;
      if ( igi2_frame.atStartPos[4].vZ - igi2_frame.atIntersection[4].tPos.vZ < 2048.0 )
      {
        if ( *(float *)&ptQTask[9].ptParent >= -409.6000061035156 )
        {
          if ( *(float *)&ptQTask[9].ptParent <= 0.0 )
            v56 = *(float *)&ptQTask[9].ptParent;
          else
            v56 = 0.0;
        }
        else
        {
          v56 = -409.6000061035156;
        }
        *(float *)&ptQTask[9].ptParent = v56;
      }
      if ( v55 <= 819.2000122070312 )
      {
        if ( igi2_frame.atIntersection[4].tNormal.vX != 0.0
          || igi2_frame.atIntersection[4].tNormal.vY != 0.0
          || igi2_frame.atIntersection[4].tNormal.vZ != 0.0 )
        {
          igi2_frame.vGamma = igi2_frame.atIntersection[4].tNormal.vY;
          v57 = sqrt(
                  igi2_frame.atIntersection[4].tNormal.vX * igi2_frame.atIntersection[4].tNormal.vX
                + igi2_frame.atIntersection[4].tNormal.vY * igi2_frame.atIntersection[4].tNormal.vY
                + igi2_frame.atIntersection[4].tNormal.vZ * igi2_frame.atIntersection[4].tNormal.vZ);
          igi2_frame.atIntersection[4].tNormal.vX = igi2_frame.atIntersection[4].tNormal.vX * (1.0 / v57);
          igi2_frame.atIntersection[4].tNormal.vY = igi2_frame.atIntersection[4].tNormal.vY * (1.0 / v57);
          igi2_frame.atIntersection[4].tNormal.vZ = igi2_frame.atIntersection[4].tNormal.vZ * (1.0 / v57);
        }
        if ( !BYTE2(ptQTask[12].tQTaskRefList.ptHead) )
        {
          v58 = Game_ptGame;
          v59 = Game_ptGame->tRunRandomState.anRandom[1];
          v60 = (Game_ptGame->tRunRandomState.anRandom[0] >> 7) ^ Game_ptGame->tRunRandomState.anRandom[2];
          Game_ptGame->tRunRandomState.anRandom[2] = v60;
          v61 = v60 ^ v59;
          v62 = v61 + v58->tRunRandomState.anRandom[0];
          v58->tRunRandomState.anRandom[1] = v61;
          v58->tRunRandomState.anRandom[0] = v62;
          LODWORD(igi2_frame.vGamma) = (unsigned __int16)v62;
          v63 = "weapondrop_01";
          if ( (double)(unsigned __int16)v62 * 0.0000152587890625 <= 0.5 )
            v63 = "weapondrop_02";
          v64 = SoundSys_NewSoundFn(Level_ptDynamicQTask, v63);
          if ( v64 )
            ((void (__cdecl *)(struct QTask_s *, struct QTask_s **))QTask_aatQTaskFinalEvent[SoundSys_eSetPositionQTaskEvent][v64->eQTaskType].pfHandler)(
              v64,
              &ptQTask[8].tQTaskChildren.ptTail);
          BYTE2(ptQTask[12].tQTaskRefList.ptHead) = 1;
        }
        if ( igi2_frame.atIntersection[4].tNormal.vZ <= 0.8 )
        {
          v67 = igi2_frame.atIntersection[4].tNormal.vZ * *(float *)&ptQTask[9].ptParent
              + igi2_frame.atIntersection[4].tNormal.vY * *(float *)&ptQTask[9].tQTaskRefList.ptTail
              + igi2_frame.atIntersection[4].tNormal.vX * *(float *)&ptQTask[9].tQTaskRefList.ptMiddle;
          igi2_frame.tReal32x3_4b = igi2_frame.atIntersection[4].tNormal.vY * v67;
          igi2_frame.tReal32x3_8d = igi2_frame.atIntersection[4].tNormal.vZ * v67;
          *(float *)&ptQTask[9].tQTaskRefList.ptMiddle = *(float *)&ptQTask[9].tQTaskRefList.ptMiddle
                                                       - igi2_frame.atIntersection[4].tNormal.vX * v67;
          *(float *)&ptQTask[9].tQTaskRefList.ptTail = *(float *)&ptQTask[9].tQTaskRefList.ptTail - igi2_frame.tReal32x3_4b;
          *(float *)&ptQTask[9].ptParent = *(float *)&ptQTask[9].ptParent - igi2_frame.tReal32x3_8d;
          v68 = *(float *)&ptQTask[9].tQTaskRefList.ptTail * 0.008333333767950535;
          igi2_frame.tReal32x3_8e = *(float *)&ptQTask[9].ptParent * 0.008333333767950535;
          *(float *)&ptQTask[9].tQTaskRefList.ptMiddle = *(float *)&ptQTask[9].tQTaskRefList.ptMiddle
                                                       - *(float *)&ptQTask[9].tQTaskRefList.ptMiddle * 0.008333333767950535;
          *(float *)&ptQTask[9].tQTaskRefList.ptTail = *(float *)&ptQTask[9].tQTaskRefList.ptTail - v68;
          *(float *)&ptQTask[9].ptParent = *(float *)&ptQTask[9].ptParent - igi2_frame.tReal32x3_8e;
        }
        else
        {
          ptHitObj = igi2_frame.atIntersection[4].ptHitObj;
          ptQTask[9].tQTaskRefList.ptMiddle = nullptr;
          ptQTask[9].tQTaskRefList.ptTail = nullptr;
          ptQTask[9].ptParent = nullptr;
          eQTaskType = ptHitObj->tQTask.eQTaskType;
          if ( eQTaskType == Sector_eQTaskType || eQTaskType == Terrain_eQTaskType )
            BYTE1(ptQTask[12].tQTaskRefList.ptHead) = 0;
          *(double *)&ptQTask[8].ptParent = igi2_frame.atIntersection[4].tPos.vZ;
        }
        *(double *)&ptQTask[8].ptParent = *(double *)&ptQTask[8].ptParent
                                        - (*(double *)&ptQTask[8].ptParent
                                         - igi2_frame.atIntersection[4].tPos.vZ
                                         - 122.87999725341797);
        igi2_frame.tReal32x3 = igi2_frame.atIntersection[4].tNormal.vY * *(float *)&ptQTask[3].tQTaskChildren.ptTail
                  + igi2_frame.atIntersection[4].tNormal.vZ * *(float *)&ptQTask[3].tQTaskRefList.ptTail
                  + igi2_frame.atIntersection[4].tNormal.vX * *(float *)&ptQTask[3].ptPrev;
        if ( !strcmp((char *)&ptQTask[10].tQTaskRefList, "WEAPON_ID_C4BOMB") )
        {
          Real32x9_Create(&igi2_frame.tReal32x9, 0.0, 0.0, 0.0);
        }
        else
        {
          if ( igi2_frame.tReal32x3 > 0.0 || igi2_frame.tReal32x3 < 0.0 )
          {
            igi2_frame.tReal32x3_8f = igi2_frame.atIntersection[4].tNormal.vY * *(float *)&ptQTask[3].tQTaskRefList.ptMiddle
                         + igi2_frame.atIntersection[4].tNormal.vZ * *(float *)&ptQTask[3].eQTaskType
                         + igi2_frame.atIntersection[4].tNormal.vX * *(float *)&ptQTask[3].tQTaskChildren.ptMiddle;
            igi2_frame.vBetaa = -atan2(igi2_frame.tReal32x3_8f / igi2_frame.tReal32x3, 1.0);
          }
          else
          {
            igi2_frame.vBetaa = 0.0;
          }
          if ( igi2_frame.tReal32x3 > 0.0 || igi2_frame.tReal32x3 < 0.0 )
          {
            igi2_frame.tReal32x3_4c = igi2_frame.atIntersection[4].tNormal.vY * *(float *)&ptQTask[3].tQTaskRefList.ptHead
                         + igi2_frame.atIntersection[4].tNormal.vZ * *(float *)&ptQTask[3].ptParent
                         + igi2_frame.atIntersection[4].tNormal.vX * *(float *)&ptQTask[3].tQTaskChildren.ptHead;
            igi2_frame.nHitsb = atan2(igi2_frame.tReal32x3_4c / igi2_frame.tReal32x3, 1.0);
            Real32x9_Create(&igi2_frame.tReal32x9, 0.0, igi2_frame.vBetaa, igi2_frame.nHitsb);
          }
          else
          {
            Real32x9_Create(&igi2_frame.tReal32x9, 0.0, igi2_frame.vBetaa, 0.0);
          }
        }
        igi2_frame.Real32x9_Multiply_tTemp.tX.vX = igi2_frame.tReal32x9.tZ.vX * *(float *)&ptQTask[3].tQTaskChildren.ptMiddle
                                      + igi2_frame.tReal32x9.tY.vX * *(float *)&ptQTask[3].tQTaskChildren.ptHead
                                      + igi2_frame.tReal32x9.tX.vX * *(float *)&ptQTask[3].ptPrev;
        igi2_frame.Real32x9_Multiply_tTemp.tX.vY = igi2_frame.tReal32x9.tZ.vY * *(float *)&ptQTask[3].tQTaskChildren.ptMiddle
                                      + igi2_frame.tReal32x9.tY.vY * *(float *)&ptQTask[3].tQTaskChildren.ptHead
                                      + igi2_frame.tReal32x9.tX.vY * *(float *)&ptQTask[3].ptPrev;
        igi2_frame.Real32x9_Multiply_tTemp.tX.vZ = igi2_frame.tReal32x9.tZ.vZ * *(float *)&ptQTask[3].tQTaskChildren.ptMiddle
                                      + igi2_frame.tReal32x9.tY.vZ * *(float *)&ptQTask[3].tQTaskChildren.ptHead
                                      + igi2_frame.tReal32x9.tX.vZ * *(float *)&ptQTask[3].ptPrev;
        igi2_frame.Real32x9_Multiply_tTemp.tY.vX = igi2_frame.tReal32x9.tZ.vX * *(float *)&ptQTask[3].tQTaskRefList.ptMiddle
                                      + igi2_frame.tReal32x9.tX.vX * *(float *)&ptQTask[3].tQTaskChildren.ptTail
                                      + igi2_frame.tReal32x9.tY.vX * *(float *)&ptQTask[3].tQTaskRefList.ptHead;
        igi2_frame.Real32x9_Multiply_tTemp.tY.vY = igi2_frame.tReal32x9.tZ.vY * *(float *)&ptQTask[3].tQTaskRefList.ptMiddle
                                      + igi2_frame.tReal32x9.tX.vY * *(float *)&ptQTask[3].tQTaskChildren.ptTail
                                      + igi2_frame.tReal32x9.tY.vY * *(float *)&ptQTask[3].tQTaskRefList.ptHead;
        igi2_frame.Real32x9_Multiply_tTemp.tY.vZ = igi2_frame.tReal32x9.tZ.vZ * *(float *)&ptQTask[3].tQTaskRefList.ptMiddle
                                      + igi2_frame.tReal32x9.tX.vZ * *(float *)&ptQTask[3].tQTaskChildren.ptTail
                                      + igi2_frame.tReal32x9.tY.vZ * *(float *)&ptQTask[3].tQTaskRefList.ptHead;
        igi2_frame.Real32x9_Multiply_tTemp.tZ.vX = igi2_frame.tReal32x9.tZ.vX * *(float *)&ptQTask[3].eQTaskType
                                      + igi2_frame.tReal32x9.tY.vX * *(float *)&ptQTask[3].ptParent
                                      + igi2_frame.tReal32x9.tX.vX * *(float *)&ptQTask[3].tQTaskRefList.ptTail;
        v69 = igi2_frame.tReal32x9.tZ.vY * *(float *)&ptQTask[3].eQTaskType + igi2_frame.tReal32x9.tY.vY * *(float *)&ptQTask[3].ptParent;
        igi2_frame.Real32x9_Multiply_tTemp.nOps = (int)&ptQTask[4].ptNext->ptNext + igi2_frame.tReal32x9.nOps + 1;
        igi2_frame.Real32x9_Multiply_tTemp.tZ.vY = v69 + igi2_frame.tReal32x9.tX.vY * *(float *)&ptQTask[3].tQTaskRefList.ptTail;
        igi2_frame.Real32x9_Multiply_tTemp.tZ.vZ = igi2_frame.tReal32x9.tZ.vZ * *(float *)&ptQTask[3].eQTaskType
                                      + igi2_frame.tReal32x9.tY.vZ * *(float *)&ptQTask[3].ptParent
                                      + igi2_frame.tReal32x9.tX.vZ * *(float *)&ptQTask[3].tQTaskRefList.ptTail;
        qmemcpy(&ptQTask[3].ptPrev, &igi2_frame.Real32x9_Multiply_tTemp, sizeof(struct QTask_s));
      }
    }
    if ( !igi2_frame.atIntersection[5].isHit || igi2_frame.atIntersection[5].tNormal.vZ <= 0.0 )
      goto LABEL_107;
    if ( igi2_frame.atIntersection[5].ptHitObj->tQTask.eQTaskType == Water_eQTaskType )
    {
      if ( ptQTask[10].tQTaskChildren.ptTail == (struct QTask_s *)Script_ParseLineInt32("WEAPON_ID_C4BOMB") )
      {
        BYTE1(ptQTask[12].tQTaskRefList.ptHead) = 1;
LABEL_106:
        *(double *)&ptQTask[8].ptParent = igi2_frame.atIntersection[5].tPos.vZ + 2048.0;
      }
    }
    else if ( !igi2_frame.atIntersection[4].isHit || igi2_frame.atIntersection[4].tNormal.vZ <= 0.0 )
    {
      goto LABEL_106;
    }
LABEL_107:
    if ( *(float *)&ptQTask[9].ptParent <= -1228.800048828125 )
      v70 = -1228.800048828125;
    else
      v70 = *(float *)&ptQTask[9].ptParent;
    *(float *)&ptQTask[9].ptParent = v70;
    *p_ptTail = *(float *)&ptQTask[9].tQTaskRefList.ptMiddle + *p_ptTail;
    *(double *)&ptQTask[8].tQTaskRefList.ptMiddle = *(float *)&ptQTask[9].tQTaskRefList.ptTail
                                                  + *(double *)&ptQTask[8].tQTaskRefList.ptMiddle;
    *(double *)&ptQTask[8].ptParent = v70 + *(double *)&ptQTask[8].ptParent;
  }
  *(double *)&igi2_frame.tReal32x9.tX.vX = *(float *)&ptQTask[9].eQTaskType + *(double *)&ptQTask[8].tQTaskChildren.ptTail;
  *(double *)&igi2_frame.tReal32x9.tX.vZ = *(float *)&ptQTask[10].ptNext + *(double *)&ptQTask[8].tQTaskRefList.ptMiddle;
  *(double *)&igi2_frame.tReal32x9.tY.vY = *(float *)&ptQTask[10].ptPrev + *(double *)&ptQTask[8].ptParent;
  if ( *(float *)&ptQTask[6].tQTaskChildren.ptHead <= (double)*(float *)&ptQTask[6].tQTaskChildren.ptMiddle )
    v71 = *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
  else
    v71 = *(float *)&ptQTask[6].tQTaskChildren.ptHead;
  if ( v71 >= *(float *)&ptQTask[6].ptPrev )
  {
    if ( *(float *)&ptQTask[6].tQTaskChildren.ptHead <= (double)*(float *)&ptQTask[6].tQTaskChildren.ptMiddle )
      v72 = *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
    else
      v72 = *(float *)&ptQTask[6].tQTaskChildren.ptHead;
  }
  else
  {
    v72 = *(float *)&ptQTask[6].ptPrev;
  }
  v73 = *(int **)&ptQTask[2].eQTaskType;
  if ( v73 && (v74 = *v73) != 0 )
    v75 = *(float *)(*(_DWORD *)(*(_DWORD *)(v74 + 12) + 12) + 120);
  else
    v75 = 1.0;
  igi2_frame.ptDynCubeObja = v75 * v72;
  World_MoveDynCubeObjRadius(
    Game_ptGame->ptWorld,
    (struct DynCubeObj_s *)ptQTask,
    (struct real64x3_t *)&igi2_frame.tReal32x9,
    igi2_frame.ptDynCubeObja);
  RigidDynCubeObj_UpdateAttachments((struct RigidDynCubeObj_t *)ptQTask);
  if ( LOBYTE(ptQTask[12].tQTaskRefList.ptHead) )
    QTask_Delete(ptQTask);
}

// source: j/0/pickups/gunpickup.c:723  [size]
void __cdecl GunPickup_EnterHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ((void (__cdecl *)(struct QTask_s *, _DWORD))QTask_aatQTaskFinalEvent[5][SectorInteriorObject_eQTaskType].pfHandler)(
    ptQTask,
    0);
}

// source: j/0/pickups/gunpickup.c:743  [anchor-mhash]
void __cdecl GunPickup_DeleteHandler(struct QTask_s *ptQTask)
{
  if ( *(_DWORD *)&ptQTask[2].eQTaskType )
  {
    ModelObj_SetLODVirModel((struct ModelObj_s *)ptQTask, nullptr, false);
    ptQTask[7].tQTaskRefList.ptHead = nullptr;
    ptQTask[7].tQTaskRefList.ptMiddle = nullptr;
    ptQTask[7].tQTaskRefList.ptTail = nullptr;
    ptQTask[7].ptParent = nullptr;
    *(_DWORD *)&ptQTask[7].eQTaskType = 0;
  }
  QTaskList_Remove(GameFunctions_ptPickupQTaskList, ptQTask);
  SectorObject_RemoveInteriorDynCubeObj((struct DynCubeObj_s *)ptQTask);
  World_RemoveDynCubeObj(Game_ptGame->ptWorld, (struct DynCubeObj_s *)ptQTask);
  if ( Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER )
    NetworkGameItem_RemoveGameItem(LOWORD(ptQTask[11].tQTaskChildren.ptMiddle));
}

// source: j/0/pickups/gunpickup.c:775  [size]
void __cdecl GunPickup_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = GunPickup_ptParameterList;
}

// source: j/0/pickups/gunpickup.c:791  [anchor-mhash]
void __cdecl GunPickup_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { float ptDynCubeObj; };
    struct { char igi2_o1[20]; _DWORD v15[11]; };
    char igi2_extent[64];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct WeaponType_s *WeaponTypeFromID; // ebp
  enum WeaponCategory_e eWeaponCategory; // eax
  int v4; // eax
  struct QTask_s *v5; // ecx
  struct LODVirModel_s *LODVirModelExistsFn; // eax
  double v7; // st7
  double v8; // st7
  int *v9; // eax
  int v10; // eax
  double v11; // st6
  struct QTask_s *ptParent; // esi
  __int16 v13; // cx

  ptQTask[10].tQTaskChildren.ptTail = (struct QTask_s *)Script_ParseLineInt32((char *)&ptQTask[10].tQTaskRefList);
  if ( ptQTask[12].tQTaskChildren.ptMiddle != (struct QTask_s *)-1 )
    ptQTask[12].tQTaskChildren.ptMiddle = (struct QTask_s *)Script_ParseLineInt32((char *)&ptQTask[11].tQTaskChildren.ptMiddle + 2);
  WeaponTypeFromID = WeaponType_GetWeaponTypeFromID((int)ptQTask[10].tQTaskChildren.ptTail);
  if ( WeaponTypeFromID )
  {
    memset(igi2_frame.v15, 0, 0x28u);
    ((void (__cdecl *)(struct WeaponType_s *, _DWORD *))QTask_aatQTaskFinalEvent[WeaponType_eGetAmmoInfoQTaskEvent][WeaponTypeFromID->tQTask.eQTaskType].pfHandler)(
      WeaponTypeFromID,
      igi2_frame.v15);
    eWeaponCategory = WeaponTypeFromID->eWeaponCategory;
    if ( eWeaponCategory == WEAPONCATEGORY_GRENADE )
    {
      v4 = 1;
      ptQTask[8].ptPrev = (struct QTask_s *)1;
    }
    else if ( eWeaponCategory == WEAPONCATEGORY_MEDIPACK )
    {
      v4 = 1;
      ptQTask[8].ptPrev = (struct QTask_s *)1;
    }
    else
    {
      v4 = igi2_frame.v15[4];
      ptQTask[8].ptPrev = nullptr;
    }
    v5 = (struct QTask_s *)igi2_frame.v15[9];
    ptQTask[8].ptNext = (struct QTask_s *)v4;
    ptQTask[8].tQTaskChildren.ptHead = v5;
    qmemcpy(&ptQTask[9], &ptQTask[8].tQTaskChildren.ptTail, 0x18u);
    ptQTask[7].tQTaskChildren.ptHead = (struct QTask_s *)-1;
    LODVirModelExistsFn = MTP_GetLODVirModelExistsFn(WeaponTypeFromID->zFixedModel);
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
    if ( *(float *)&ptQTask[6].tQTaskChildren.ptHead <= (double)*(float *)&ptQTask[6].tQTaskChildren.ptMiddle )
      v7 = *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
    else
      v7 = *(float *)&ptQTask[6].tQTaskChildren.ptHead;
    if ( v7 >= *(float *)&ptQTask[6].ptPrev )
    {
      if ( *(float *)&ptQTask[6].tQTaskChildren.ptHead <= (double)*(float *)&ptQTask[6].tQTaskChildren.ptMiddle )
        v8 = *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
      else
        v8 = *(float *)&ptQTask[6].tQTaskChildren.ptHead;
    }
    else
    {
      v8 = *(float *)&ptQTask[6].ptPrev;
    }
    v9 = *(int **)&ptQTask[2].eQTaskType;
    if ( v9 && (v10 = *v9) != 0 )
      v11 = *(float *)(*(_DWORD *)(*(_DWORD *)(v10 + 12) + 12) + 120);
    else
      v11 = 1.0;
    igi2_frame.ptDynCubeObj = v8 * v11;
    World_MoveDynCubeObjRadius(
      Game_ptGame->ptWorld,
      (struct DynCubeObj_s *)ptQTask,
      (struct real64x3_t *)&ptQTask[8].tQTaskChildren.ptTail,
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
    v13 = Attach_eAttachEvent;
    ptQTask[5].tQTaskChildren.ptTail = (struct QTask_s *)-1;
    ptQTask[5].tQTaskRefList.ptHead = nullptr;
    QTask_TriggerQTaskEventParent(ptQTask, v13, &ptQTask[5].tQTaskChildren.ptTail);
    ModelObj_CalcRelativePosAndOrientation((struct ModelObj_s *)ptQTask);
    RigidDynCubeObj_UpdateAttachments((struct RigidDynCubeObj_t *)ptQTask);
  }
}

// source: j/0/pickups/gunpickup.c:917  [size]
void __cdecl GunPickup_UpdateAttachmentHandler(struct QTask_s *ptQTask)
{
  ((void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[Attach_eUpdateAttachmentEvent][SectorInteriorObject_eQTaskType].pfHandler)(ptQTask);
  qmemcpy(&ptQTask[8].tQTaskChildren.ptTail, &ptQTask[1], 0x18u);
}

// source: j/0/pickups/gunpickup.c:938  [size]
void __cdecl GunPickup_ObjectCollisionEvaluateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_BYTE *)pxContext = 0;
}

// source: j/0/pickups/gunpickup.c:965  [size]
void __cdecl GunPickup_GetNextZEvaluateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_BYTE *)pxContext = 0;
}

// source: j/0/pickups/gunpickup.c:986  [anchor-callee]
enum bool __cdecl GunPickup_IsAbleToPickup(
        struct QTask_s *ptQTask,
        struct real64x3_t *ptPos,
        float vRadiusTolerance,
        int eTeam)
{
  #pragma pack(push, 1)
  union
  {
    struct { double vHeight; };
    struct { char igi2_o1[8]; struct real64x3_t Real64x3_Rotate_tTemp; };
    struct { char igi2_o2[32]; struct AIDetectionLineOfSightContext_s tAIDetectionLineOfSightContext; };
    struct { char igi2_o3[48]; double v26; };
    struct { char igi2_o4[56]; double v27; };
    struct { char igi2_o5[64]; struct real64x3_t atEnd[3]; };
    char igi2_extent[136];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  double v5; // st7
  double v6; // st7
  int *v7; // eax
  int v8; // eax
  double v9; // st6
  double v10; // st7
  double v11; // st6
  double v12; // st5
  double v13; // st5
  double v14; // st4
  double v15; // st3
  double v16; // st2
  double v17; // st1
  double v18; // st6
  struct real64x3_t *v19; // esi
  double v20; // st7
  int v21; // ebx

  if ( BYTE1(ptQTask[12].tQTaskRefList.ptHead) && !BYTE2(ptQTask[12].tQTaskRefList.ptHead) )
    return false;
  if ( Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER
    && ptQTask[10].tQTaskChildren.ptTail == (struct QTask_s *)Script_ParseLineInt32("WEAPON_ID_C4BOMB")
    && NetMission_eAttackingTeam != eTeam )
  {
    return false;
  }
  v5 = *(float *)&ptQTask[6].tQTaskChildren.ptHead <= (double)*(float *)&ptQTask[6].tQTaskChildren.ptMiddle
     ? *(float *)&ptQTask[6].tQTaskChildren.ptMiddle
     : *(float *)&ptQTask[6].tQTaskChildren.ptHead;
  if ( v5 >= *(float *)&ptQTask[6].ptPrev )
    v6 = *(float *)&ptQTask[6].tQTaskChildren.ptHead <= (double)*(float *)&ptQTask[6].tQTaskChildren.ptMiddle
       ? *(float *)&ptQTask[6].tQTaskChildren.ptMiddle
       : *(float *)&ptQTask[6].tQTaskChildren.ptHead;
  else
    v6 = *(float *)&ptQTask[6].ptPrev;
  v7 = *(int **)&ptQTask[2].eQTaskType;
  if ( v7 && (v8 = *v7) != 0 )
    v9 = *(float *)(*(_DWORD *)(*(_DWORD *)(v8 + 12) + 12) + 120);
  else
    v9 = 1.0;
  v10 = v6 * v9;
  if ( v10 < 4096.0 )
    v10 = 4096.0;
  v11 = *(double *)&ptQTask[1].ptNext - ptPos->vX;
  v12 = *(double *)&ptQTask[1].tQTaskChildren.ptHead - ptPos->vY;
  igi2_frame.vHeight = *(double *)&ptQTask[1].tQTaskChildren.ptTail - ptPos->vZ;
  if ( vRadiusTolerance + v10 <= sqrt(v12 * v12 + v11 * v11) || -8192.0 - v10 >= igi2_frame.vHeight || v10 + 8192.0 <= igi2_frame.vHeight )
    return false;
  igi2_frame.atEnd[0].vY = -v10;
  v13 = *(float *)&ptQTask[3].tQTaskChildren.ptHead;
  v14 = *(float *)&ptQTask[3].tQTaskRefList.ptHead;
  igi2_frame.v27 = *(float *)&ptQTask[3].ptParent;
  v15 = *(float *)&ptQTask[3].tQTaskChildren.ptMiddle * 0.0;
  igi2_frame.v26 = *(float *)&ptQTask[3].ptPrev * 0.0;
  igi2_frame.Real64x3_Rotate_tTemp.vX = v13 * igi2_frame.atEnd[0].vY + igi2_frame.v26 + v15;
  v16 = *(float *)&ptQTask[3].tQTaskRefList.ptMiddle * 0.0;
  v17 = *(float *)&ptQTask[3].tQTaskChildren.ptTail * 0.0;
  igi2_frame.Real64x3_Rotate_tTemp.vY = v14 * igi2_frame.atEnd[0].vY + v17 + v16;
  igi2_frame.vHeight = *(float *)&ptQTask[3].eQTaskType * 0.0;
  *(double *)&igi2_frame.tAIDetectionLineOfSightContext.tCollisionEvaluateContext = *(float *)&ptQTask[3].tQTaskRefList.ptTail
                                                                       * 0.0;
  igi2_frame.Real64x3_Rotate_tTemp.vZ = igi2_frame.v27 * igi2_frame.atEnd[0].vY
                           + *(double *)&igi2_frame.tAIDetectionLineOfSightContext.tCollisionEvaluateContext
                           + igi2_frame.vHeight;
  qmemcpy(igi2_frame.atEnd, &igi2_frame.Real64x3_Rotate_tTemp, 0x18u);
  igi2_frame.atEnd[0].vX = igi2_frame.Real64x3_Rotate_tTemp.vX + *(double *)&ptQTask[1].ptNext;
  igi2_frame.atEnd[0].vY = igi2_frame.atEnd[0].vY + *(double *)&ptQTask[1].tQTaskChildren.ptHead;
  igi2_frame.atEnd[0].vZ = igi2_frame.atEnd[0].vZ + *(double *)&ptQTask[1].tQTaskChildren.ptTail;
  igi2_frame.Real64x3_Rotate_tTemp.vX = v13 * 0.0 + igi2_frame.v26 + v15;
  igi2_frame.Real64x3_Rotate_tTemp.vY = v14 * 0.0 + v17 + v16;
  igi2_frame.Real64x3_Rotate_tTemp.vZ = igi2_frame.v27 * 0.0 + *(double *)&igi2_frame.tAIDetectionLineOfSightContext.tCollisionEvaluateContext + igi2_frame.vHeight;
  qmemcpy(&igi2_frame.atEnd[1], &igi2_frame.Real64x3_Rotate_tTemp, sizeof(struct real64x3_t));
  igi2_frame.atEnd[1].vX = igi2_frame.Real64x3_Rotate_tTemp.vX + *(double *)&ptQTask[1].ptNext;
  igi2_frame.atEnd[1].vY = igi2_frame.atEnd[1].vY + *(double *)&ptQTask[1].tQTaskChildren.ptHead;
  igi2_frame.atEnd[1].vZ = igi2_frame.atEnd[1].vZ + *(double *)&ptQTask[1].tQTaskChildren.ptTail;
  igi2_frame.Real64x3_Rotate_tTemp.vX = v13 * v10 + igi2_frame.v26 + v15;
  igi2_frame.tAIDetectionLineOfSightContext.ptDetectorTask = ptQTask;
  igi2_frame.tAIDetectionLineOfSightContext.ptDetecteeTask = ptQTask;
  igi2_frame.Real64x3_Rotate_tTemp.vY = v14 * v10 + v17 + v16;
  v18 = igi2_frame.v27 * v10 + *(double *)&igi2_frame.tAIDetectionLineOfSightContext.tCollisionEvaluateContext;
  igi2_frame.tAIDetectionLineOfSightContext.tCollisionEvaluateContext.ptQTask = ptQTask;
  igi2_frame.Real64x3_Rotate_tTemp.vZ = v18 + igi2_frame.vHeight;
  qmemcpy(&igi2_frame.atEnd[2], &igi2_frame.Real64x3_Rotate_tTemp, sizeof(struct real64x3_t));
  igi2_frame.atEnd[2].vX = igi2_frame.Real64x3_Rotate_tTemp.vX + *(double *)&ptQTask[1].ptNext;
  v19 = igi2_frame.atEnd;
  igi2_frame.atEnd[2].vY = igi2_frame.atEnd[2].vY + *(double *)&ptQTask[1].tQTaskChildren.ptHead;
  v20 = igi2_frame.atEnd[2].vZ + *(double *)&ptQTask[1].tQTaskChildren.ptTail;
  v21 = 0;
  igi2_frame.atEnd[2].vZ = v20;
  while ( !World_LineOfSight(
             Game_ptGame->ptWorld,
             ptPos,
             v19,
             AIDetection_eLineOfSightQTaskEvent,
             &igi2_frame.tAIDetectionLineOfSightContext.tCollisionEvaluateContext,
             (unsigned int)&TerrainRender_atEdge[4623].iSplitVertex,
             WORLD_DYNCUBETREE_CATEGORY_ALL,
             (struct LineOfSightOutputContext_s *)&igi2_frame.vHeight) )
  {
    ++v21;
    ++v19;
    if ( v21 >= 3 )
      return false;
  }
  return true;
}

// source: j/0/pickups/gunpickup.c:1098  [anchor-callee]
void *__cdecl GunPickup_Pickup(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *ptNext; // ecx
  struct QTask_s *ptTail; // edx
  struct QTask_s *ptHead; // ecx
  int v5; // edx
  void *result; // eax
  int (__cdecl *pfHandler)(void *, struct GunPickupContext_t *); // ecx
  struct GunPickupContext_t tGunPickupContext; // [esp+4h] [ebp-18h] BYREF

  ptNext = ptQTask[8].ptNext;
  tGunPickupContext.anAmmoForFiretype[0] = (int)ptQTask[8].ptPrev;
  ptTail = ptQTask[10].tQTaskChildren.ptTail;
  tGunPickupContext.nAmmoInClip = (int)ptNext;
  ptHead = ptQTask[8].tQTaskChildren.ptHead;
  tGunPickupContext.iWeaponID = (int)ptTail;
  v5 = GunPickup_eGunPickupQTaskEvent;
  tGunPickupContext.anAmmoForFiretype[1] = (int)ptHead;
  tGunPickupContext.isExternalAdd = false;
  if ( Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER )
    ptQTask[12].tQTaskChildren.ptTail = ptQTask[12].tQTaskChildren.ptMiddle;
  result = *(void **)pxContext;
  pfHandler = (int (__cdecl *)(void *, struct GunPickupContext_t *))QTask_aatQTaskFinalEvent[v5][*((unsigned __int16 *)result
                                                                                                 + 18)].pfHandler;
  if ( pfHandler )
    result = (void *)pfHandler(result, &tGunPickupContext);
  LOBYTE(ptQTask[12].tQTaskRefList.ptHead) = 1;
  return result;
}

// source: j/0/pickups/gunpickup.c:1154  [anchor-caller]
void __cdecl GunPickup_PickupHandler(struct QTask_s *ptQTask, void *pxContext)
{
  int eTeam; // eax
  enum WeaponCategory_e eWeaponCategory; // eax
  struct QTask_s *v4; // ebp
  struct WeaponType_s *WeaponTypeFromID; // edx
  struct QTask_s *ptNext; // ecx
  struct AmmoTypeItem_s *AmmoTypeItemFromAmmoType; // eax
  int v8; // eax
  struct QTask_s *v9; // ebx
  struct QTask_s *ptPrev; // eax
  struct QTask_s *ptTail; // ebp
  struct QTask_s *v12; // eax
  struct WeaponType_s *v13; // ebp
  unsigned int ptMiddle_low; // edx
  struct QTask_s *v15; // eax
  struct NetManagerGameMessage_s ptGameMessage[5]; // [esp+10h] [ebp-2Ch] BYREF

  eTeam = 0;
  if ( Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER )
    eTeam = NetManager_GetClientFromHumanQTask(*(struct QTask_s **)pxContext)->eTeam;
  if ( GunPickup_IsAbleToPickup(ptQTask, (struct real64x3_t *)((char *)pxContext + 8), 0.0, eTeam) )
  {
    if ( (eWeaponCategory = WeaponType_GetWeaponTypeFromID((int)ptQTask[10].tQTaskChildren.ptTail)->eWeaponCategory,
          eWeaponCategory != WEAPONCATEGORY_FLASHBANG)
      && eWeaponCategory != WEAPONCATEGORY_GRENADE
      && eWeaponCategory != WEAPONCATEGORY_SMOKEGRENADE
      && eWeaponCategory != WEAPONCATEGORY_PROXIMITYMINE
      && eWeaponCategory != WEAPONCATEGORY_MEDIPACK
      || (v4 = *(struct QTask_s **)pxContext,
          WeaponTypeFromID = WeaponType_GetWeaponTypeFromID((int)ptQTask[10].tQTaskChildren.ptTail),
          memset(ptGameMessage, 0, sizeof(ptGameMessage)),
          ((void (__cdecl *)(struct WeaponType_s *, struct NetManagerGameMessage_s *))QTask_aatQTaskFinalEvent[WeaponType_eGetAmmoInfoQTaskEvent][WeaponTypeFromID->tQTask.eQTaskType].pfHandler)(
            WeaponTypeFromID,
            ptGameMessage),
          (ptNext = v4[33].ptNext) == nullptr)
      || !ptGameMessage[0].nLocalTime
      || (AmmoTypeItemFromAmmoType = Weapon_GetAmmoTypeItemFromAmmoType(
                                       ptNext,
                                       (char *)(ptGameMessage[0].nLocalTime + 40)),
          AmmoTypeItemFromAmmoType->nAmmoCount != AmmoTypeItemFromAmmoType->nAmmoLimit) )
    {
      v8 = *((_DWORD *)pxContext + 8);
      *((_DWORD *)pxContext + 9) = 1;
      if ( v8 )
      {
        if ( Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER )
        {
          v9 = *(struct QTask_s **)pxContext;
          if ( HumanPlayer_ptQTask == *(struct QTask_s **)pxContext )
          {
            ptPrev = v9[33].ptNext[1].ptPrev;
            if ( ptPrev )
              ptTail = ptPrev->tQTaskChildren.ptTail;
            else
              ptTail = nullptr;
            if ( ptTail[16].ptParent != (struct QTask_s *)WeaponType_GetWeaponTypeFromID((int)ptQTask[10].tQTaskChildren.ptTail)->eWeaponCategory
              || ((v12 = v9[33].ptNext[1].ptPrev) != nullptr
                ? (v13 = (struct WeaponType_s *)v12->tQTaskChildren.ptTail)
                : (v13 = nullptr),
                  v13 == WeaponType_GetWeaponTypeFromID((int)ptQTask[10].tQTaskChildren.ptTail)) )
            {
              if ( !*(_DWORD *)&ptQTask[12].eQTaskType )
              {
                ptGameMessage[0].eGameMessage = 1381060693;
                ptGameMessage[0].nLocalTime = NetManager_GetTimer();
                ptMiddle_low = LOWORD(ptQTask[11].tQTaskChildren.ptMiddle);
                v15 = ptQTask[10].tQTaskChildren.ptTail;
                ptGameMessage[2].eGameMessage = (unsigned int)Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle;
                ptGameMessage[1].eGameMessage = ptMiddle_low;
                ptGameMessage[1].nLocalTime = (int)v15;
                NetManager_SendGameMessage(
                  0,
                  ptGameMessage[2].eGameMessage,
                  NETWORKQUEUE_GUARANTEED,
                  ptGameMessage,
                  0x14u);
                *(_DWORD *)&ptQTask[12].eQTaskType = 1;
              }
            }
            else
            {
              v9[87].tQTaskChildren.ptTail = (struct QTask_s *)1;
              *(_DWORD *)&v9[86].eQTaskType = LOWORD(ptQTask[11].tQTaskChildren.ptMiddle);
              v9[87].ptNext = ptQTask[10].tQTaskChildren.ptTail;
            }
          }
        }
        else
        {
          GunPickup_Pickup(ptQTask, pxContext);
        }
      }
    }
  }
}

// source: j/0/pickups/gunpickup.c:1282  [size]
int __cdecl GunPickup_GetWeaponID(struct QTask_s *ptQTask)
{
  return (int)ptQTask[10].tQTaskChildren.ptTail;
}

// source: j/0/pickups/gunpickup.c:1299  [size]
void __cdecl GunPickup_SetGameItemID(int iGameItemID)
{
  GunPickup_iGameItemID = iGameItemID;
}

// source: j/0/pickups/gunpickup.c:1312  [size]
int __cdecl GunPickup_GetGameItemID(struct QTask_s *ptQTask)
{
  return LOWORD(ptQTask[11].tQTaskChildren.ptMiddle);
}

// source: j/0/pickups/gunpickup.c:1330  [size]
struct WeaponType_s *__cdecl GunPickup_GetWeaponType(struct QTask_s *ptQTask)
{
  return WeaponType_GetWeaponTypeFromID((int)ptQTask[10].tQTaskChildren.ptTail);
}

// source: j/0/pickups/gunpickup.c:1348  [size]
__int16 __cdecl GunPickup_GetGunPickupQTaskEvent()
{
  return GunPickup_eGunPickupQTaskEvent;
}

// source: j/0/pickups/gunpickup.c:1373  [anchor-callee]
struct QTask_s *__cdecl GunPickup_New(
        struct WeaponType_s *ptWeaponType,
        struct real64x3_t *ptPos,
        struct real32x9_t *ptOrientation,
        float vThrowGamma,
        enum bool isMoving,
        int nAmmoInClip,
        int *anAmmoCount,
        int ltcg_arg7)
{
  #pragma pack(push, 1)
  union
  {
    struct { float pvAlpha; };
    struct { char igi2_o1[4]; struct real32x9_t ptSource[2]; };
    char igi2_extent[92];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *v9; // ebp
  double vX; // st7
  double v11; // st7
  bool v12; // c3
  float vY; // edx
  double v14; // st7
  long double v15; // st4
  double v16; // st6
  long double v17; // st7
  double v18; // st7
  void (__cdecl *pfHandler)(struct QTask_s *, _DWORD); // eax

  igi2_frame.ptSource[0].tX.vX = 0.0;
  igi2_frame.pvAlpha = 0.0;
  igi2_frame.ptSource[0].tX.vY = 0.0;
  if ( Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER
    && GunPickup_iGameItemID
    && NetworkGameItem_GetNode(GunPickup_iGameItemID) )
  {
    return nullptr;
  }
  qmemcpy(&igi2_frame.ptSource[0].tY, ptPos, 0x18u);
  qmemcpy(&igi2_frame.ptSource[0].nOps, ptOrientation, sizeof(struct real32x9_t));
  v9 = QTask_NewFn(Level_ptDynamicQTask, GunPickup_eQTaskType, nullptr);
  qmemcpy(&v9[8].tQTaskChildren.ptTail, &igi2_frame.ptSource[0].tY, 0x18u);
  if ( !strcmp(ptWeaponType->zWeaponScriptID, "WEAPON_ID_C4BOMB") )
    v9[10].ptPrev = (struct QTask_s *)1142528410;
  else
    v9[10].ptPrev = nullptr;
  *(_DWORD *)&v9[9].eQTaskType = 0;
  v9[10].ptNext = nullptr;
  strcpy((char *)&v9[10].tQTaskRefList, ptWeaponType->zWeaponScriptID);
  BYTE1(v9[12].tQTaskRefList.ptHead) = isMoving;
  Real32x9_GetAngles((struct real32x9_t *)&igi2_frame.ptSource[0].nOps, &igi2_frame.ptSource[0].tX.vX, &igi2_frame.pvAlpha, &igi2_frame.ptSource[0].tX.vY);
  if ( !strcmp(ptWeaponType->zWeaponScriptID, "WEAPON_ID_C4BOMB") )
  {
    igi2_frame.pvAlpha = 0.0;
  }
  else
  {
    if ( igi2_frame.ptSource[0].tX.vX < -1.5707963705062866 || (vX = igi2_frame.ptSource[0].tX.vX, igi2_frame.ptSource[0].tX.vX = 0.0, vX > 1.5707963705062866) )
      igi2_frame.ptSource[0].tX.vX = 3.1415927410125732;
    v11 = igi2_frame.pvAlpha;
    igi2_frame.pvAlpha = -1.5707963705062866;
    if ( v11 >= 0.0 )
      igi2_frame.pvAlpha = 1.5707963705062866;
  }
  Real32x9_Create((struct real32x9_t *)&v9[3].ptPrev, igi2_frame.ptSource[0].tX.vX, igi2_frame.pvAlpha, igi2_frame.ptSource[0].tX.vY);
  Real32x9_Create((struct real32x9_t *)&igi2_frame.ptSource[0].tY, 0.0, 0.0, vThrowGamma);
  v12 = igi2_frame.ptSource[0].tY.vY == 0.0;
  vY = igi2_frame.ptSource[0].tZ.vY;
  v9[9].tQTaskRefList.ptMiddle = (struct QReference_s *)LODWORD(igi2_frame.ptSource[0].tY.vY);
  *(float *)&v9[9].tQTaskRefList.ptTail = vY;
  v9[9].ptParent = nullptr;
  if ( !v12 || igi2_frame.ptSource[0].tZ.vY != 0.0 )
  {
    v14 = igi2_frame.ptSource[0].tZ.vY;
    *(double *)&igi2_frame.ptSource[0].tX.vY = igi2_frame.ptSource[0].tY.vY;
    v15 = sqrt(igi2_frame.ptSource[0].tY.vY * igi2_frame.ptSource[0].tY.vY + igi2_frame.ptSource[0].tZ.vY * igi2_frame.ptSource[0].tZ.vY);
    *(float *)&v9[9].tQTaskRefList.ptMiddle = igi2_frame.ptSource[0].tY.vY * (1.0 / v15);
    v16 = v14;
    v17 = 1.0 / v15;
    *(float *)&v9[9].tQTaskRefList.ptTail = v16 * v17;
    *(float *)&v9[9].ptParent = v17 * 0.0;
  }
  v18 = *(float *)&v9[9].tQTaskRefList.ptMiddle * 614.4000244140625;
  v9[9].ptParent = (struct QTask_s *)1133021321;
  *(float *)&v9[9].tQTaskRefList.ptMiddle = v18;
  igi2_frame.ptSource[0].tX.vY = *(float *)&v9[9].tQTaskRefList.ptTail * 614.4000244140625;
  *(float *)&v9[9].tQTaskRefList.ptTail = igi2_frame.ptSource[0].tX.vY;
  if ( nAmmoInClip )
  {
    v9[9].ptParent = (struct QTask_s *)1116244105;
    *(float *)&v9[9].tQTaskRefList.ptMiddle = v18 * 0.25;
    *(float *)&v9[9].tQTaskRefList.ptTail = igi2_frame.ptSource[0].tX.vY * 0.25;
  }
  pfHandler = (void (__cdecl *)(struct QTask_s *, _DWORD))QTask_aatQTaskFinalEvent[ParameterList_eUpdateInternalDataQTaskEvent][v9->eQTaskType].pfHandler;
  if ( pfHandler )
    pfHandler(v9, 0);
  v9[8].ptNext = (struct QTask_s *)anAmmoCount;
  if ( ltcg_arg7 )
  {
    v9[8].ptPrev = *(struct QTask_s **)ltcg_arg7;
    v9[8].tQTaskChildren.ptHead = *(struct QTask_s **)(ltcg_arg7 + 4);
  }
  return v9;
}

// source: j/0/pickups/gunpickup.c:1526  [anchor-callee]
struct QTask_s *__cdecl GunPickup_NewFromWeapon(
        struct QTask_s *ptWeaponQTask,
        struct WeaponType_s *ptWeaponType,
        struct real64x3_t *ptPos,
        struct real32x9_t *ptOrientation,
        float vThrowGamma,
        enum bool isRemoveAmmoInPocket)
{
  #pragma pack(push, 1)
  union
  {
    struct { int ltcg_arg7[2]; };
    struct { char igi2_o1[8]; _BYTE v12[40]; };
    char igi2_extent[48];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct WeaponTypeItem_s *WeaponTypeItemFromWeaponType; // eax
  int *v7; // ebp
  int v8; // esi
  _BYTE *v9; // edi

  if ( !ptWeaponType )
    return nullptr;
  WeaponTypeItemFromWeaponType = Weapon_GetWeaponTypeItemFromWeaponType(ptWeaponQTask, ptWeaponType->zWeaponScriptID);
  if ( !WeaponTypeItemFromWeaponType )
    return nullptr;
  v7 = (int *)WeaponTypeItemFromWeaponType->anFireTypeAmmoCount[0];
  memset(igi2_frame.v12, 0, sizeof(igi2_frame.v12));
  ((void (__cdecl *)(struct WeaponType_s *, _BYTE *))QTask_aatQTaskFinalEvent[WeaponType_eGetAmmoInfoQTaskEvent][ptWeaponType->tQTask.eQTaskType].pfHandler)(
    ptWeaponType,
    igi2_frame.v12);
  v8 = 0;
  v9 = &igi2_frame.v12[4];
  do
  {
    if ( *(_DWORD *)v9 && isRemoveAmmoInPocket )
      igi2_frame.ltcg_arg7[v8] = Weapon_GetAmmoTypeItemFromAmmoType(ptWeaponQTask, (char *)(*(_DWORD *)v9 + 40))->nAmmoCount;
    else
      igi2_frame.ltcg_arg7[v8] = 0;
    ++v8;
    v9 += 20;
  }
  while ( v8 < 2 );
  return GunPickup_New(ptWeaponType, ptPos, ptOrientation, vThrowGamma, true, 0, v7, (int)igi2_frame.ltcg_arg7);
}

// source: j/0/pickups/gunpickup.c:1661  [anchor-callee]
struct QTask_s *__cdecl GunPickup_CreateFromItem(void *pxItem, unsigned __int16 iGameItemID)
{
  #pragma pack(push, 1)
  union
  {
    struct { int *v5; };
    struct { char igi2_o1[16]; struct real32x9_t ptOrientation; };
    char igi2_extent[56];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct WeaponType_s *WeaponTypeFromID; // eax

  WeaponTypeFromID = WeaponType_GetWeaponTypeFromID(*(_DWORD *)pxItem);
  GunPickup_iGameItemID = iGameItemID;
  igi2_frame.v5 = *((int **)pxItem + 1);
  igi2_frame.ptOrientation.tX.vX = 1.0;
  memset(&igi2_frame.ptOrientation.tX.vY, 0, 12);
  igi2_frame.ptOrientation.tY.vY = 1.0;
  memset(&igi2_frame.ptOrientation.tY.vZ, 0, 12);
  igi2_frame.ptOrientation.tZ.vZ = 1.0;
  igi2_frame.ptOrientation.nOps = 0;
  return GunPickup_New(
           WeaponTypeFromID,
           (struct real64x3_t *)((char *)pxItem + 16),
           &igi2_frame.ptOrientation,
           0.0,
           false,
           0,
           igi2_frame.v5,
           (int)pxItem + 8);
}

// source: j/0/pickups/gunpickup.c:1694  [size]
unsigned __int16 __cdecl GunPickup_GetQTaskType()
{
  return GunPickup_eQTaskType;
}

// source: j/0/pickups/gunpickup.c:1707  [size]
struct real64x3_t *__cdecl GunPickup_GetPos(struct QTask_s *ptQTask)
{
  return (struct real64x3_t *)&ptQTask[8].tQTaskChildren.ptTail;
}

int __cdecl sub_475F60(int a1)
{
  return *(_DWORD *)(a1 + 516);
}

int __cdecl sub_475F70(int result, int a2)
{
  *(_DWORD *)(a2 + 516) = result;
  return result;
}

// source: j/0/pickups/gunpickup.c:1723  [anchor-strings]
void __cdecl GunPickup_Open()
{
  __int16 v0; // ax
  unsigned __int16 v1; // si
  struct ParameterList_s *v2; // eax
  int v3; // edx

  GunPickup_eQTaskType = QTask_NewQTaskType("GunPickup", 520, RigidDynCubeObj_eQTaskType, 0, 0);
  v0 = QTask_NewQTaskEventFn(0, "GunPickup");
  v1 = GunPickup_eQTaskType;
  GunPickup_eGunPickupQTaskEvent = v0;
  QTask_LinkQTaskEventHandlerFn(
    GunPickup_eQTaskType,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveNoChildrenHandler);
  QTask_LinkQTaskEventHandlerFn(v1, 0, GunPickup_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 1, GunPickup_RunHandler);
  QTask_LinkQTaskEventHandlerFn(v1, 5, (void (__cdecl *)(struct QTask_s *, void *))GunPickup_EnterHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 2, GunPickup_DeleteHandler);
  QTask_LinkQTaskEventHandlerFn(
    v1,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))GunPickup_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(v1, ParameterList_eUpdateInternalDataQTaskEvent, GunPickup_UpdateInternalDataHandler);
  QTask_LinkQTaskEventHandlerFn(
    v1,
    GameFunctions_eObjectCollisionEvaluateQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))GunPickup_ObjectCollisionEvaluateHandler);
  QTask_LinkQTaskEventHandlerFn(
    v1,
    GameFunctions_eGetNextZEvaluateQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))GunPickup_GetNextZEvaluateHandler);
  QTask_LinkQTaskEventHandlerFn(v1, GameFunctions_ePickupQTaskEvent, GunPickup_PickupHandler);
  QTask_LinkQTaskEventHandlerFn(v1, 10, nullptr);
  QTask_LinkQTaskEventHandlerFn(v1, 9, nullptr);
  QTask_LinkQTaskEventHandlerFn(v1, 11, nullptr);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, Attach_eUpdateAttachmentEvent, GunPickup_UpdateAttachmentHandler);
  QTask_LinkQTaskEventHandlerFn(v1, NetworkGameItem_eGetGameItemDataQTaskEvent, GunPickup_GetGameItemDataHandler);
  QTask_LinkQTaskEventHandlerFn(
    v1,
    Serialize_eGetSerializeParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))GunPickup_GetSerializeParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(v1, Serialize_eDeSerializeQTaskEvent, GunPickup_DeSerializeHandler);
  QTask_LinkQTaskEventHandlerFn(
    v1,
    Serialize_eGetSerializeInfoQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))GunPickup_GetSerializeInfoHandler);
  v2 = (struct ParameterList_s *)Mem_AllocFn(92, 4);
  v2->ptParameterListItem = (struct ParameterListItem_s *)&v2[1];
  v3 = Level_eParameterTypeObjectPos;
  v2->nParameters = 0;
  v2->nMaxParameters = 4;
  GunPickup_ptParameterList = v2;
  ParameterList_AddParameter(v2, 0x150u, v3, "Position", 7u, nullptr);
  ParameterList_AddParameter(GunPickup_ptParameterList, 0x7Cu, Level_eParameterTypeReal32x9, "Orientation", 7u, nullptr);
  ParameterList_AddParameter(
    GunPickup_ptParameterList,
    0x1A4u,
    ParameterEnumList_eParameterTypeString32,
    "ID",
    7u,
    &WeaponType_tWeaponIDEnumList);
  ParameterList_AddParameter(
    GunPickup_ptParameterList,
    0x1C6u,
    Level_eParameterTypeString32,
    "Respawn Time",
    7u,
    nullptr);
  GunPickup_ptSerializeParameterList = ParameterList_Derive(ModelObjParameters_ptSerializeParameterList, 14);
  ParameterList_AddParameter(
    GunPickup_ptSerializeParameterList,
    0x140u,
    Level_eParameterTypeInt32,
    "nAmmoInClip",
    7u,
    nullptr);
  ParameterList_AddParameter(
    GunPickup_ptSerializeParameterList,
    0x144u,
    SerializeArray_eParameterType,
    "anAmmoForFiretype",
    7u,
    (void *)8);
  ParameterList_AddParameter(
    GunPickup_ptSerializeParameterList,
    0x168u,
    Level_eParameterTypeObjectPos,
    "tFallPos",
    7u,
    nullptr);
  ParameterList_AddParameter(
    GunPickup_ptSerializeParameterList,
    0x180u,
    Level_eParameterTypeReal32x3,
    "tVelocity",
    7u,
    nullptr);
  ParameterList_AddParameter(
    GunPickup_ptSerializeParameterList,
    0x198u,
    Level_eParameterTypeReal64,
    "vAcceleration",
    7u,
    nullptr);
  ParameterList_AddParameter(
    GunPickup_ptSerializeParameterList,
    0x1A0u,
    Level_eParameterTypeInt32,
    "iWeaponID",
    7u,
    nullptr);
  ParameterList_AddParameter(
    GunPickup_ptSerializeParameterList,
    0x1A4u,
    Level_eParameterTypeString32,
    "zWeaponID",
    7u,
    nullptr);
  ParameterList_AddParameter(
    GunPickup_ptSerializeParameterList,
    0x1C4u,
    Level_eParameterTypeInt16,
    "iGameItemID",
    7u,
    nullptr);
  ParameterList_AddParameter(
    GunPickup_ptSerializeParameterList,
    0x1C6u,
    Level_eParameterTypeString32,
    "zRespawnTime",
    7u,
    nullptr);
  ParameterList_AddParameter(
    GunPickup_ptSerializeParameterList,
    0x1ECu,
    Level_eParameterTypeInt32,
    "nRespawnTime",
    7u,
    nullptr);
  ParameterList_AddParameter(
    GunPickup_ptSerializeParameterList,
    0x1F0u,
    Level_eParameterTypeInt32,
    "nTicksToRespawn",
    7u,
    nullptr);
  ParameterList_AddParameter(
    GunPickup_ptSerializeParameterList,
    0x1F4u,
    Level_eParameterTypebool8,
    "isDelete",
    7u,
    nullptr);
  ParameterList_AddParameter(
    GunPickup_ptSerializeParameterList,
    0x1F5u,
    Level_eParameterTypebool8,
    "isMoving",
    7u,
    nullptr);
  ParameterList_AddParameter(
    GunPickup_ptSerializeParameterList,
    0x1F6u,
    Level_eParameterTypebool8,
    "isLanded",
    7u,
    nullptr);
}

// source: j/0/pickups/gunpickup.c:1798  [size]
void __cdecl GunPickup_Close()
{
  int v0; // esi
  int v1; // esi

  if ( GunPickup_ptParameterList )
  {
    v0 = *(_DWORD *)((unsigned int)&GunPickup_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
  if ( GunPickup_ptSerializeParameterList )
  {
    v1 = *(_DWORD *)((unsigned int)&GunPickup_ptSerializeParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v1);
    memset(*(void **)(v1 + 8), 0xCDu, *(_DWORD *)(v1 + 16));
    free((void *)v1);
  }
  QTask_DeleteQTaskEvent(GunPickup_eGunPickupQTaskEvent);
  QTask_DeleteQTaskType(GunPickup_eQTaskType);
}

void __cdecl sub_4764C0(struct QTask_s *a1, char *a2)
{
  *((_WORD *)a2 + 1) = 48;
  *(_WORD *)a2 = a1[16].tQTaskRefList.ptHead;
  *((_WORD *)a2 + 2) = Bomb_eQTaskType;
  qmemcpy(a2 + 6, &a1[8], 0x18u);
  *(_DWORD *)(a2 + 30) = a1[8].tQTaskRefList.ptTail;
  *(_DWORD *)(a2 + 34) = a1[9].ptNext;
  *(_DWORD *)(a2 + 38) = a1[9].tQTaskChildren.ptMiddle;
  *(float *)(a2 + 42) = (double)(int)a1[15].ptParent * 0.03333333507180214;
  *(float *)(a2 + 46) = (double)*(int *)&a1[15].eQTaskType * 0.03333333507180214;
}
