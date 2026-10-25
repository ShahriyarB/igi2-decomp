/* j/0/human/human.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/human/human.c:200  [anchor-callee]
struct QTask_s *__cdecl Human_PlaySound(
        struct Human_s *ptHuman,
        char *pzSoundDef,
        struct real64x3_t *ptPos)
{
  struct QReference_s *v4; // ecx
  struct Human_s *pxObject; // edx
  struct QTask_s *v7; // eax
  struct QTask_s *v8; // esi

  v4 = Game_ptGame->aptPlayerQTaskRef[2];
  pxObject = nullptr;
  if ( v4 )
    pxObject = (struct Human_s *)v4->pxObject;
  if ( ptHuman == pxObject )
    return SoundSys_NewSoundFn(ptHuman->ptHumanViewQTask, pzSoundDef);
  if ( !ptPos )
    return SoundSys_NewSoundFn(&ptHuman->tBoneDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask, pzSoundDef);
  if ( !Level_ptDynamicQTask )
    return nullptr;
  v7 = SoundSys_NewSoundFn(Level_ptDynamicQTask, pzSoundDef);
  v8 = v7;
  if ( v7 )
    SoundSys_SetSoundPosition(v7, ptPos);
  return v8;
}

// source: j/0/human/human.c:248  [anchor-caller]
struct Result_s *__cdecl Human_PopPositionScriptFunction(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  #pragma pack(push, 1)
  union
  {
    struct { unsigned int pxData; };
    struct { char igi2_o1[4]; struct Result_s Rs; };
    char igi2_extent[28];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  unsigned int v3; // eax
  struct QReference_s *v4; // eax
  struct QTask_s *pxObject; // esi
  struct QReference_s *v6; // eax
  struct QTask_s *v7; // ecx

  if ( ptArgList->nArguments == 4 )
  {
    if ( ptArgList->isQVM )
    {
      igi2_frame.pxData = 0;
      QVM_EvalArg(&igi2_frame.pxData, 4, ptArgList, 0, 1);
      v3 = igi2_frame.pxData;
    }
    else
    {
      v3 = Expression_EvalInt(*ptArgList->aptExpression);
    }
    if ( v3 < 0x1000 )
    {
      v4 = Level_atLevelQTaskID[v3];
      if ( v4 )
      {
        pxObject = (struct QTask_s *)v4->pxObject;
        if ( pxObject )
        {
          if ( QTask_IsQTaskTypeDerived(pxObject->eQTaskType, Human_eQTaskType) )
          {
            *(double *)&igi2_frame.Rs.nResult = Script_EvalArgFloat(ptArgList, 1) * 4096.0;
            igi2_frame.Rs.vResult = Script_EvalArgFloat(ptArgList, 2) * 4096.0;
            *(double *)&igi2_frame.Rs.zResult = Script_EvalArgFloat(ptArgList, 3) * 4096.0;
            Human_SetGroundTask(pxObject, nullptr);
            Human_PopPosition(pxObject, (struct real64x3_t *)&igi2_frame.Rs);
            v6 = Game_ptGame->aptPlayerQTaskRef[2];
            v7 = nullptr;
            if ( v6 )
              v7 = (struct QTask_s *)v6->pxObject;
            if ( pxObject == v7 )
              HumanPlayer_GoToDefaultState(pxObject);
          }
        }
      }
    }
  }
  igi2_frame.Rs.zResult = (char *)&g_zInitialValue;
  igi2_frame.Rs.vResult = 0.0;
  igi2_frame.Rs.nResult = 0;
  qmemcpy(retstr, &igi2_frame.Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/human/human.c:293  [anchor-mhash]
struct Result_s *__cdecl Human_AddWeaponCB(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct Result_s Rs; };
    struct { char igi2_o1[24]; char zWeaponType[1024]; };
    char igi2_extent[1048];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)

  if ( pxContext && Game_eGameMode != GAME_GAMEMODE_MULTIPLAYER )
  {
    if ( ptArgList->isQVM )
    {
      igi2_frame.zWeaponType[0] = 0;
      QVM_EvalArg(igi2_frame.zWeaponType, 1024, ptArgList, 0, 3);
    }
    else
    {
      Expression_EvalString(*ptArgList->aptExpression, igi2_frame.zWeaponType, 1024);
    }
    if ( igi2_frame.zWeaponType[0] )
      Weapon_EnableWeaponType((struct QTask_s *)pxContext, igi2_frame.zWeaponType, true);
  }
  igi2_frame.Rs.zResult = (char *)&g_zInitialValue;
  igi2_frame.Rs.vResult = 1.0;
  igi2_frame.Rs.nResult = 1;
  qmemcpy(retstr, &igi2_frame.Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/human/human.c:322  [anchor-mhash]
struct Result_s *__cdecl Human_AddAmmoCB(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct Result_s Rs; };
    struct { char igi2_o1[24]; char zAmmoType[1024]; };
    char igi2_extent[1048];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v3; // eax

  if ( !pxContext || Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER )
  {
LABEL_9:
    igi2_frame.Rs.nResult = 2;
    HIDWORD(igi2_frame.Rs.vResult) = 0x40000000;
    goto LABEL_10;
  }
  if ( ptArgList->nArguments == 2 )
  {
    if ( ptArgList->isQVM )
    {
      igi2_frame.zAmmoType[0] = 0;
      QVM_EvalArg(igi2_frame.zAmmoType, 1024, ptArgList, 0, 3);
    }
    else
    {
      Expression_EvalString(*ptArgList->aptExpression, igi2_frame.zAmmoType, 1024);
    }
    v3 = Script_EvalArgInt(ptArgList, 1);
    Weapon_AddAmmoToAmmoType((struct QTask_s *)pxContext, igi2_frame.zAmmoType, v3);
    goto LABEL_9;
  }
  igi2_frame.Rs.nResult = 0;
  HIDWORD(igi2_frame.Rs.vResult) = 0;
LABEL_10:
  LODWORD(igi2_frame.Rs.vResult) = 0;
  igi2_frame.Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &igi2_frame.Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/human/human.c:362  [anchor-caller]
struct Result_s *__cdecl Human_AddAmmoForWeaponCB(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  #pragma pack(push, 1)
  union
  {
    struct { int nAmmoCount; };
    struct { char igi2_o1[4]; struct WeaponTypeGetAmmoInfoContext_s tWeaponTypeGetAmmoInfoContext; };
    struct { char igi2_o2[44]; char zWeaponType[256]; };
    char igi2_extent[300];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v3; // ebx
  int v4; // eax
  struct WeaponType_s *WeaponTypeFromID; // esi
  struct AmmoType_s *ptAmmoType; // eax

  if ( ptArgList->nArguments >= 2 )
  {
    if ( pxContext )
    {
      v3 = 1;
      if ( Game_eGameMode != GAME_GAMEMODE_MULTIPLAYER )
      {
        if ( ptArgList->isQVM )
        {
          igi2_frame.zWeaponType[0] = 0;
          QVM_EvalArg(igi2_frame.zWeaponType, 256, ptArgList, 0, 3);
        }
        else
        {
          Expression_EvalString(*ptArgList->aptExpression, igi2_frame.zWeaponType, 256);
        }
        igi2_frame.nAmmoCount = Script_EvalArgInt(ptArgList, 1);
        if ( ptArgList->nArguments <= 2 || Script_EvalArgInt(ptArgList, 2) < 0 )
        {
          v3 = 0;
        }
        else if ( Script_EvalArgInt(ptArgList, 2) <= 1 )
        {
          v3 = Script_EvalArgInt(ptArgList, 2);
        }
        v4 = Script_ParseLineInt32(igi2_frame.zWeaponType);
        WeaponTypeFromID = WeaponType_GetWeaponTypeFromID(v4);
        if ( WeaponTypeFromID )
        {
          memset(&igi2_frame.tWeaponTypeGetAmmoInfoContext, 0, sizeof(igi2_frame.tWeaponTypeGetAmmoInfoContext));
          WeaponType_GetAmmoInfo(WeaponTypeFromID, &igi2_frame.tWeaponTypeGetAmmoInfoContext);
          ptAmmoType = igi2_frame.tWeaponTypeGetAmmoInfoContext.atAmmoItem[v3].tOut.ptAmmoType;
          if ( ptAmmoType )
            Weapon_AddAmmoToAmmoType((struct QTask_s *)pxContext, ptAmmoType->zAmmoTypeScriptID, igi2_frame.nAmmoCount);
        }
      }
    }
  }
  igi2_frame.tWeaponTypeGetAmmoInfoContext.atAmmoItem[0].tIn.ptParametersQTask = nullptr;
  igi2_frame.tWeaponTypeGetAmmoInfoContext.atAmmoItem[0].tOut.nRoundsToFire = 0;
  igi2_frame.tWeaponTypeGetAmmoInfoContext.atAmmoItem[0].tOut.nBulletsPerRound = 0;
  igi2_frame.tWeaponTypeGetAmmoInfoContext.atAmmoItem[0].tOut.nRoundsPerClip = (int)&g_zInitialValue;
  qmemcpy(retstr, &igi2_frame.tWeaponTypeGetAmmoInfoContext, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/human/human.c:408  [anchor-mhash]
struct Result_s *__cdecl Human_GetCutSceneDeltaTimeCB(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  struct QReference_s *pxObject; // eax
  double v4; // st6
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  pxObject = Level_atLevelQTaskID[0];
  if ( Level_atLevelQTaskID[0] )
    pxObject = (struct QReference_s *)Level_atLevelQTaskID[0]->pxObject;
  v4 = *(float *)&pxObject[63].pxObject * 1.5;
  Rs.zResult = (char *)&g_zInitialValue;
  Rs.nResult = (__int64)v4;
  Rs.vResult = v4;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/human/human.c:456  [anchor-callee]
void __cdecl Human_ObjectCollision(
        struct QTask_s *ptQTask,
        struct real64x3_t *ptPos0,
        struct real64x3_t *ptPos1,
        struct real32x3_t *ptSpeed,
        unsigned int *pbSignal)
{
  #pragma pack(push, 1)
  union
  {
    struct { float v117; };
    struct { float v118; };
    struct { float v119; };
    struct { float v120; };
    struct { float v121; };
    struct { float v122; };
    struct { float v123; };
    struct { float v124; };
    struct { char igi2_o8[4]; float v125; };
    struct { char igi2_o9[4]; float v126; };
    struct { char igi2_o10[4]; float v127; };
    struct { char igi2_o11[4]; float v128; };
    struct { char igi2_o12[4]; float v129; };
    struct { char igi2_o13[4]; float v130; };
    struct { char igi2_o14[4]; float v131; };
    struct { char igi2_o15[4]; float v132; };
    struct { char igi2_o16[4]; float v133; };
    struct { char igi2_o17[4]; float v134; };
    struct { char igi2_o18[4]; float v135; };
    struct { char igi2_o19[4]; float v136; };
    struct { char igi2_o20[4]; float v137; };
    struct { char igi2_o21[4]; float v138; };
    struct { char igi2_o22[8]; float v139; };
    struct { char igi2_o23[8]; float v140; };
    struct { char igi2_o24[8]; float v141; };
    struct { char igi2_o25[8]; float v142; };
    struct { char igi2_o26[8]; float v143; };
    struct { char igi2_o27[8]; float v144; };
    struct { char igi2_o28[8]; float v145; };
    struct { char igi2_o29[8]; float v146; };
    struct { char igi2_o30[8]; float v147; };
    struct { char igi2_o31[8]; float v148; };
    struct { char igi2_o32[8]; float v149; };
    struct { char igi2_o33[8]; float v150; };
    struct { char igi2_o34[8]; float v151; };
    struct { char igi2_o35[8]; float v152; };
    struct { char igi2_o36[12]; float v153; };
    struct { char igi2_o37[12]; float v154; };
    struct { char igi2_o38[12]; float v155; };
    struct { char igi2_o39[12]; float v156; };
    struct { char igi2_o40[12]; float v157; };
    struct { char igi2_o41[16]; struct QTask_s *ptHead; };
    struct { char igi2_o42[16]; float v159; };
    struct { char igi2_o43[16]; float v160; };
    struct { char igi2_o44[16]; float v161; };
    struct { char igi2_o45[16]; float v162; };
    struct { char igi2_o46[16]; float v163; };
    struct { char igi2_o47[20]; struct QReference_s *v164; };
    struct { char igi2_o48[20]; float v165; };
    struct { char igi2_o49[20]; float v166; };
    struct { char igi2_o50[20]; float v167; };
    struct { char igi2_o51[20]; float v168; };
    struct { char igi2_o52[20]; float v169; };
    struct { char igi2_o53[24]; float v170; };
    struct { char igi2_o54[24]; float v171; };
    struct { char igi2_o55[24]; float v172; };
    struct { char igi2_o56[28]; float v173; };
    struct { char igi2_o57[28]; float v174; };
    struct { char igi2_o58[28]; float v175; };
    struct { char igi2_o59[32]; float v176; };
    struct { char igi2_o60[32]; float v177; };
    struct { char igi2_o61[32]; float v178; };
    struct { char igi2_o62[32]; float v179; };
    struct { char igi2_o63[32]; float v180; };
    struct { char igi2_o64[36]; float v181; };
    struct { char igi2_o65[36]; float v182; };
    struct { char igi2_o66[36]; float v183; };
    struct { char igi2_o67[36]; float v184; };
    struct { char igi2_o68[40]; float v186; };
    struct { char igi2_o69[40]; float vX; };
    struct { char igi2_o70[44]; float v188; };
    struct { char igi2_o71[44]; float vY; };
    struct { char igi2_o72[48]; float v190; };
    struct { char igi2_o73[48]; float vZ; };
    struct { char igi2_o74[52]; int v191; };
    struct { char igi2_o75[52]; int v192; };
    struct { char igi2_o76[56]; float v193; };
    struct { char igi2_o77[60]; float v194; };
    struct { char igi2_o78[68]; float v195; };
    struct { char igi2_o79[68]; int v196; };
    struct { char igi2_o80[72]; int v197; };
    struct { char igi2_o81[76]; float v198; };
    struct { char igi2_o82[80]; float v199; };
    struct { char igi2_o83[88]; double v200; };
    struct { char igi2_o84[96]; float v201; };
    struct { char igi2_o85[100]; float v202; };
    struct { char igi2_o86[104]; float v203; };
    struct { char igi2_o87[108]; float v204; };
    struct { char igi2_o88[112]; float v205; };
    struct { char igi2_o89[116]; float v206; };
    struct { char igi2_o90[120]; float v207; };
    struct { char igi2_o91[124]; float v208; };
    struct { char igi2_o92[128]; double nNumPoints; };
    struct { char igi2_o93[140]; struct real64x3_t *v210; };
    struct { char igi2_o94[144]; float v211[10]; };
    struct { char igi2_o95[184]; int v212; };
    struct { char igi2_o96[188]; int v213; };
    struct { char igi2_o97[192]; int v214; };
    struct { char igi2_o98[196]; int v215; };
    struct { char igi2_o99[200]; int v216; };
    struct { char igi2_o100[204]; int v217; };
    struct { char igi2_o101[208]; int v218; };
    struct { char igi2_o102[212]; int v219; };
    struct { char igi2_o103[216]; int v220; };
    struct { char igi2_o104[220]; int v221; };
    struct { char igi2_o105[224]; int v222; };
    struct { char igi2_o106[228]; int v223; };
    struct { char igi2_o107[232]; int v224; };
    struct { char igi2_o108[236]; int v225; };
    struct { char igi2_o109[240]; int v226; };
    struct { char igi2_o110[244]; int v227; };
    struct { char igi2_o111[248]; int v228; };
    struct { char igi2_o112[252]; int v229; };
    struct { char igi2_o113[256]; int v230; };
    struct { char igi2_o114[260]; int v231; };
    struct { char igi2_o115[264]; int v232; };
    struct { char igi2_o116[268]; int v233; };
    struct { char igi2_o117[272]; int v234; };
    struct { char igi2_o118[276]; int v235; };
    struct { char igi2_o119[284]; _DWORD v236[9]; };
    struct { char igi2_o120[320]; _DWORD v237[9]; };
    struct { char igi2_o121[356]; _DWORD v238[9]; };
    struct { char igi2_o122[392]; _DWORD v239[8]; };
    struct { char igi2_o123[424]; double v240; };
    struct { char igi2_o124[432]; int v241; };
    struct { char igi2_o125[436]; int v242; };
    struct { char igi2_o126[440]; int v243; };
    struct { char igi2_o127[444]; int v244; };
    struct { char igi2_o128[448]; double v245; };
    struct { char igi2_o129[456]; int v246; };
    struct { char igi2_o130[460]; int v247; };
    struct { char igi2_o131[464]; int v248; };
    struct { char igi2_o132[468]; int v249; };
    struct { char igi2_o133[472]; double v250; };
    struct { char igi2_o134[480]; int v251; };
    struct { char igi2_o135[484]; int v252; };
    struct { char igi2_o136[496]; double v253; };
    struct { char igi2_o137[504]; struct QIntersection_s ptIntersection; };
    struct { char igi2_o138[1096]; double v255[10]; };
    struct { char igi2_o139[1176]; struct real64x3_t ptEnd[28]; };
    struct { char igi2_o140[1848]; double v257[84]; };
    struct { char igi2_o141[2520]; struct QIntersection_s v258[28]; };
    char igi2_extent[5880];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v5; // ebx
  double v6; // st7
  double v7; // st6
  long double v8; // st3
  long double v9; // st4
  long double v10; // st3
  long double v11; // st5
  long double v12; // st3
  long double v13; // st3
  long double v14; // st5
  long double v15; // st2
  long double v16; // st5
  int v17; // eax
  int v18; // eax
  struct QReference_s *ptMiddle; // edx
  float *v20; // ebp
  _DWORD *v21; // esi
  _WORD *pxObject; // edx
  int v23; // ecx
  float *v24; // eax
  double v25; // st5
  double v26; // st4
  double v27; // st5
  double v28; // st4
  float *v29; // edx
  long double v30; // st7
  float *v31; // ecx
  double v32; // st6
  double v33; // st5
  struct real64x3_t *v34; // esi
  double v35; // st6
  unsigned int v36; // eax
  double v37; // st5
  double v38; // st4
  double v39; // st3
  int v40; // ebx
  unsigned int v41; // eax
  float v42; // edi
  float v43; // edi
  float v44; // edi
  double v45; // st2
  float v46; // ecx
  unsigned int v47; // eax
  double v48; // st3
  unsigned int v49; // eax
  float v50; // edi
  float v51; // edi
  float v52; // edi
  double v53; // st2
  float v54; // ecx
  unsigned int v55; // eax
  double v56; // st3
  unsigned int v57; // eax
  float v58; // edi
  double v59; // st2
  float v60; // ecx
  unsigned int v61; // eax
  double v62; // st3
  unsigned int v63; // eax
  float v64; // ecx
  double v65; // st3
  unsigned int v66; // eax
  struct real64x3_t *v67; // esi
  double *v68; // edi
  double v69; // st7
  char *v70; // esi
  double *v71; // edi
  int v72; // ebx
  int v73; // edx
  struct QTask_s *v74; // esi
  double v75; // st7
  int v76; // ecx
  int v77; // eax
  double v78; // st6
  double v79; // st7
  int v80; // eax
  int v81; // ecx
  double v82; // st7
  int v83; // edx
  int v84; // ebp
  double v85; // st6
  double v86; // st5
  struct real32x3_t *p_tNormal; // ecx
  int v88; // ebx
  bool v89; // cc
  double v90; // st4
  double v91; // st4
  float v92; // edx
  int v93; // eax
  double v94; // st4
  char v95; // al
  char ptPrev; // al
  long double v97; // st2
  long double v98; // st4
  long double v99; // st3
  long double v100; // st2
  long double v101; // st4
  long double v102; // st3
  double v103; // st4
  double v104; // st3
  long double v105; // st2
  long double v106; // st4
  long double v107; // st3
  struct real64x3_t *v108; // eax
  struct real64x3_t *v109; // ebp
  double v110; // st4
  int v111; // edx
  float *p_vZ; // esi
  double v113; // st6
  int v114; // ecx
  double v115; // st2
  double v116; // st6

  igi2_frame.v236[0] = 0;
  igi2_frame.v236[1] = 0;
  igi2_frame.v236[2] = 1154272461;
  igi2_frame.v236[3] = 0;
  igi2_frame.v236[4] = 0;
  igi2_frame.v236[5] = 1166016512;
  igi2_frame.v236[6] = 0;
  igi2_frame.v236[7] = 0;
  igi2_frame.v236[8] = 1171888538;
  igi2_frame.v238[0] = 0;
  igi2_frame.v238[1] = 0;
  igi2_frame.v238[2] = 1154272461;
  igi2_frame.v238[3] = 0;
  igi2_frame.v238[4] = 0;
  igi2_frame.v238[5] = 1162661069;
  igi2_frame.v238[6] = 0;
  igi2_frame.v238[7] = 0;
  igi2_frame.v238[8] = 1167694234;
  igi2_frame.v237[0] = 0;
  igi2_frame.v237[1] = 0;
  igi2_frame.v237[2] = 1149239296;
  igi2_frame.v237[3] = 0;
  igi2_frame.v237[4] = 0;
  igi2_frame.v237[5] = 1152594739;
  igi2_frame.v237[6] = 0;
  igi2_frame.v237[7] = 0;
  igi2_frame.v237[8] = 1154272461;
  igi2_frame.v239[0] = -1009988403;
  igi2_frame.v239[1] = 1137495245;
  igi2_frame.v239[2] = 0;
  igi2_frame.v239[3] = 0;
  igi2_frame.v239[4] = 1137495245;
  igi2_frame.v239[5] = 0;
  igi2_frame.v239[6] = 1137495245;
  igi2_frame.v239[7] = 1137495245;
  igi2_frame.v240 = 4.1505178563893e18;
  igi2_frame.v241 = 0;
  igi2_frame.v242 = 0;
  igi2_frame.v243 = 1137495245;
  igi2_frame.v244 = -1009988403;
  igi2_frame.v245 = 0.0;
  igi2_frame.v246 = -1009988403;
  igi2_frame.v247 = 0;
  igi2_frame.v248 = -1009988403;
  igi2_frame.v249 = -1009988403;
  igi2_frame.v250 = -4.1505178563893e18;
  igi2_frame.v251 = 0;
  igi2_frame.v252 = 0;
  igi2_frame.v212 = -1009988403;
  igi2_frame.v213 = 1137495245;
  igi2_frame.v214 = 0;
  igi2_frame.v215 = 0;
  igi2_frame.v216 = 1137495245;
  igi2_frame.v217 = 0;
  igi2_frame.v218 = 1137495245;
  igi2_frame.v219 = 1137495245;
  igi2_frame.v220 = 0;
  igi2_frame.v221 = 1137495245;
  igi2_frame.v222 = 0;
  igi2_frame.v223 = 0;
  igi2_frame.v224 = 1137495245;
  igi2_frame.v225 = -1009988403;
  igi2_frame.v226 = 0;
  igi2_frame.v227 = 0;
  igi2_frame.v228 = -1009988403;
  igi2_frame.v229 = 0;
  igi2_frame.v230 = -1009988403;
  igi2_frame.v231 = -1009988403;
  igi2_frame.v232 = 0;
  igi2_frame.v233 = -1009988403;
  igi2_frame.v234 = 0;
  igi2_frame.v235 = 0;
  *pbSignal &= ~4u;
  LOBYTE(ptQTask[50].ptPrev) = 15;
  v5 = 0;
  igi2_frame.v193 = ptPos1->vX - ptPos0->vX;
  igi2_frame.v198 = 0.0;
  igi2_frame.ptHead = ptQTask[3].tQTaskChildren.ptHead;
  igi2_frame.v194 = ptPos1->vY - ptPos0->vY;
  igi2_frame.v199 = 0.0;
  igi2_frame.v197 = 0;
  v6 = igi2_frame.v194 * igi2_frame.v194;
  v7 = igi2_frame.v193 * igi2_frame.v193;
  igi2_frame.v195 = sqrt(v7 + v6);
  igi2_frame.v164 = ptQTask[3].tQTaskRefList.ptHead;
  v8 = sqrt(*(float *)&igi2_frame.ptHead * *(float *)&igi2_frame.ptHead + *(float *)&igi2_frame.v164 * *(float *)&igi2_frame.v164);
  if ( v8 <= 0.0 )
  {
    qmemcpy(igi2_frame.v211, &ptQTask[3].ptPrev, sizeof(igi2_frame.v211));
  }
  else
  {
    igi2_frame.v211[2] = 0.0;
    igi2_frame.v211[5] = 0.0;
    igi2_frame.v211[8] = 1.0;
    v9 = *(float *)&igi2_frame.ptHead * (1.0 / v8);
    v10 = 1.0 / v8;
    v11 = v10 * *(float *)&igi2_frame.v164;
    v12 = v10 * 0.0;
    igi2_frame.v211[1] = v9;
    igi2_frame.v211[4] = v11;
    igi2_frame.v211[7] = v12;
    v13 = v12 * 0.0;
    igi2_frame.v173 = v11 - v13;
    igi2_frame.v159 = igi2_frame.v173;
    igi2_frame.v176 = -(v9 - v13);
    igi2_frame.v165 = igi2_frame.v176;
    v14 = v9 * 0.0 - v11 * 0.0;
    igi2_frame.v181 = v14;
    v15 = sqrt(igi2_frame.v173 * igi2_frame.v173 + igi2_frame.v176 * igi2_frame.v176 + v14 * v14);
    if ( v15 == 0.0 )
    {
      v16 = igi2_frame.v181;
    }
    else
    {
      igi2_frame.v159 = igi2_frame.v173 * (1.0 / v15);
      igi2_frame.v165 = igi2_frame.v176 * (1.0 / v15);
      v16 = 1.0 / v15 * igi2_frame.v181;
    }
    igi2_frame.v211[6] = v16;
    igi2_frame.v211[0] = igi2_frame.v159;
    igi2_frame.v211[3] = igi2_frame.v165;
  }
  v17 = *(_DWORD *)&ptQTask[32].eQTaskType;
  if ( v17 )
  {
    v18 = v17 - 1;
    if ( v18 )
    {
      if ( v18 != 1 )
        return;
      ptMiddle = ptQTask[44].tQTaskRefList.ptMiddle;
      v20 = (float *)&igi2_frame.v212;
      v21 = igi2_frame.v237;
      if ( ptMiddle )
      {
        pxObject = ptMiddle->pxObject;
        if ( pxObject )
        {
          if ( QTask_IsQTaskTypeDerived(pxObject[18], Vehicle_eQTaskType) )
          {
            igi2_frame.v213 = 1157627904;
            igi2_frame.v212 = -1001599795;
            igi2_frame.v216 = 1157627904;
            igi2_frame.v215 = 0;
            igi2_frame.v219 = 1157627904;
            igi2_frame.v218 = 1145883853;
            igi2_frame.v222 = 0;
            igi2_frame.v221 = 1145883853;
            igi2_frame.v225 = -989855744;
            igi2_frame.v224 = 1145883853;
            igi2_frame.v228 = -989855744;
            igi2_frame.v227 = 0;
            igi2_frame.v231 = -989855744;
            igi2_frame.v230 = -1001599795;
            igi2_frame.v234 = 0;
            igi2_frame.v233 = -1001599795;
          }
        }
      }
      goto LABEL_17;
    }
    v21 = igi2_frame.v238;
  }
  else
  {
    v21 = igi2_frame.v236;
  }
  v20 = (float *)igi2_frame.v239;
LABEL_17:
  v23 = 0;
  v24 = v20 + 1;
  do
  {
    v25 = v24[1];
    ++v23;
    v26 = *v24;
    v24 += 3;
    *((float *)&igi2_frame.v200 + v23 + 1) = igi2_frame.v195 / sqrt(v26 * v26 + *(v24 - 4) * *(v24 - 4) + v25 * v25) + 1.0;
    igi2_frame.v160 = igi2_frame.v211[0] * *(v24 - 4) + igi2_frame.v211[2] * *(v24 - 2) + igi2_frame.v211[1] * *(v24 - 3);
    igi2_frame.v166 = igi2_frame.v211[3] * *(v24 - 4) + igi2_frame.v211[5] * *(v24 - 2) + igi2_frame.v211[4] * *(v24 - 3);
    v27 = igi2_frame.v211[6] * *(v24 - 4) + igi2_frame.v211[8] * *(v24 - 2);
    v28 = igi2_frame.v211[7] * *(v24 - 3);
    *(v24 - 4) = igi2_frame.v160;
    *(v24 - 3) = igi2_frame.v166;
    igi2_frame.v170 = v27 + v28;
    *(v24 - 2) = igi2_frame.v170;
  }
  while ( v23 < 8 );
  v29 = (float *)(v21 + 2);
  igi2_frame.v191 = 3;
  v30 = sqrt(v6 + v7);
  do
  {
    v31 = v29 - 2;
    igi2_frame.v174 = igi2_frame.v211[0] * *(v29 - 2) + igi2_frame.v211[1] * *(v29 - 1) + igi2_frame.v211[2] * *v29;
    igi2_frame.v177 = igi2_frame.v211[3] * *(v29 - 2) + igi2_frame.v211[4] * *(v29 - 1) + igi2_frame.v211[5] * *v29;
    v32 = igi2_frame.v211[6] * *(v29 - 2) + igi2_frame.v211[7] * *(v29 - 1);
    v33 = igi2_frame.v211[8] * *v29;
    *v31 = igi2_frame.v174;
    v31[1] = igi2_frame.v177;
    igi2_frame.v182 = v32 + v33;
    *v29 = igi2_frame.v182;
    v34 = ptPos0;
    v35 = *(v29 - 2) + ptPos0->vX;
    v36 = 24 * v5;
    v37 = *(v29 - 1) + ptPos0->vY;
    igi2_frame.v117 = *v20;
    igi2_frame.nNumPoints = v37;
    v38 = *v29 + ptPos0->vZ;
    igi2_frame.v125 = v20[1];
    igi2_frame.v139 = v20[2];
    igi2_frame.v200 = v38;
    *(double *)((char *)&igi2_frame.ptIntersection.ptHitObj + v36) = v35;
    *(double *)((char *)&igi2_frame.ptIntersection.tPos.vX + v36) = v37;
    *(double *)((char *)&igi2_frame.ptIntersection.tPos.vY + v36) = v38;
    igi2_frame.v257[v36 / 8] = igi2_frame.v117 + v35;
    igi2_frame.v257[v36 / 8 + 1] = igi2_frame.v125 + v37;
    igi2_frame.v257[v36 / 8 + 2] = igi2_frame.v139 + v38;
    igi2_frame.v140 = igi2_frame.v201 * igi2_frame.v139;
    v39 = igi2_frame.v201 * igi2_frame.v125;
    igi2_frame.ptEnd[v36 / 0x18].vX = igi2_frame.v201 * igi2_frame.v117 + v35;
    igi2_frame.ptEnd[v36 / 0x18].vY = v39 + v37;
    igi2_frame.ptEnd[v36 / 0x18].vZ = igi2_frame.v140 + v38;
    v40 = v5 + 1;
    v41 = 24 * v40;
    *(double *)((char *)&igi2_frame.ptIntersection.ptHitObj + v41) = v35;
    v42 = v20[3];
    *(double *)((char *)&igi2_frame.ptIntersection.tPos.vX + v41) = v37;
    igi2_frame.v118 = v42;
    v43 = v20[4];
    *(double *)((char *)&igi2_frame.ptIntersection.tPos.vY + v41) = v38;
    igi2_frame.v126 = v43;
    igi2_frame.v141 = v20[5];
    ++v40;
    igi2_frame.v257[v41 / 8] = igi2_frame.v118 + v35;
    v44 = v20[6];
    igi2_frame.v257[v41 / 8 + 1] = igi2_frame.v126 + v37;
    igi2_frame.v257[v41 / 8 + 2] = igi2_frame.v141 + v38;
    v45 = igi2_frame.v202 * igi2_frame.v126;
    v46 = v20[8];
    igi2_frame.v127 = v20[7];
    igi2_frame.v142 = igi2_frame.v202 * igi2_frame.v141;
    igi2_frame.ptEnd[v41 / 0x18].vX = igi2_frame.v202 * igi2_frame.v118 + v35;
    igi2_frame.ptEnd[v41 / 0x18].vY = v45 + v37;
    igi2_frame.ptEnd[v41 / 0x18].vZ = igi2_frame.v142 + v38;
    v47 = 24 * v40;
    *(double *)((char *)&igi2_frame.ptIntersection.ptHitObj + v47) = v35;
    ++v40;
    *(double *)((char *)&igi2_frame.ptIntersection.tPos.vX + v47) = v37;
    *(double *)((char *)&igi2_frame.ptIntersection.tPos.vY + v47) = v38;
    igi2_frame.v257[v47 / 8] = v44 + v35;
    igi2_frame.v257[v47 / 8 + 1] = igi2_frame.v127 + v37;
    igi2_frame.v257[v47 / 8 + 2] = v46 + v38;
    igi2_frame.v143 = igi2_frame.v203 * v46;
    v48 = igi2_frame.v203 * igi2_frame.v127;
    igi2_frame.ptEnd[v47 / 0x18].vX = igi2_frame.v203 * v44 + v35;
    igi2_frame.ptEnd[v47 / 0x18].vY = v48 + v37;
    igi2_frame.ptEnd[v47 / 0x18].vZ = igi2_frame.v143 + v38;
    v49 = 24 * v40;
    *(double *)((char *)&igi2_frame.ptIntersection.ptHitObj + v49) = v35;
    v50 = v20[9];
    *(double *)((char *)&igi2_frame.ptIntersection.tPos.vX + v49) = v37;
    igi2_frame.v119 = v50;
    v51 = v20[10];
    *(double *)((char *)&igi2_frame.ptIntersection.tPos.vY + v49) = v38;
    igi2_frame.v128 = v51;
    igi2_frame.v144 = v20[11];
    ++v40;
    igi2_frame.v257[v49 / 8] = igi2_frame.v119 + v35;
    v52 = v20[12];
    igi2_frame.v257[v49 / 8 + 1] = igi2_frame.v128 + v37;
    igi2_frame.v257[v49 / 8 + 2] = igi2_frame.v144 + v38;
    v53 = igi2_frame.v204 * igi2_frame.v128;
    v54 = v20[14];
    igi2_frame.v129 = v20[13];
    igi2_frame.v145 = igi2_frame.v204 * igi2_frame.v144;
    igi2_frame.ptEnd[v49 / 0x18].vX = igi2_frame.v204 * igi2_frame.v119 + v35;
    igi2_frame.ptEnd[v49 / 0x18].vY = v53 + v37;
    igi2_frame.ptEnd[v49 / 0x18].vZ = igi2_frame.v145 + v38;
    v55 = 24 * v40;
    *(double *)((char *)&igi2_frame.ptIntersection.ptHitObj + v55) = v35;
    ++v40;
    *(double *)((char *)&igi2_frame.ptIntersection.tPos.vX + v55) = v37;
    *(double *)((char *)&igi2_frame.ptIntersection.tPos.vY + v55) = v38;
    igi2_frame.v257[v55 / 8] = v52 + v35;
    igi2_frame.v257[v55 / 8 + 1] = igi2_frame.v129 + v37;
    igi2_frame.v257[v55 / 8 + 2] = v54 + v38;
    igi2_frame.v146 = igi2_frame.v205 * v54;
    v56 = igi2_frame.v205 * igi2_frame.v129;
    igi2_frame.ptEnd[v55 / 0x18].vX = igi2_frame.v205 * v52 + v35;
    igi2_frame.ptEnd[v55 / 0x18].vY = v56 + v37;
    igi2_frame.ptEnd[v55 / 0x18].vZ = igi2_frame.v146 + v38;
    v57 = 24 * v40;
    *(double *)((char *)&igi2_frame.ptIntersection.ptHitObj + v57) = v35;
    *(double *)((char *)&igi2_frame.ptIntersection.tPos.vX + v57) = v37;
    igi2_frame.v120 = v20[15];
    *(double *)((char *)&igi2_frame.ptIntersection.tPos.vY + v57) = v38;
    igi2_frame.v130 = v20[16];
    igi2_frame.v147 = v20[17];
    ++v40;
    igi2_frame.v257[v57 / 8] = igi2_frame.v120 + v35;
    v58 = v20[18];
    igi2_frame.v257[v57 / 8 + 1] = igi2_frame.v130 + v37;
    igi2_frame.v257[v57 / 8 + 2] = igi2_frame.v147 + v38;
    v59 = igi2_frame.v206 * igi2_frame.v130;
    v60 = v20[20];
    igi2_frame.v131 = v20[19];
    igi2_frame.v148 = igi2_frame.v206 * igi2_frame.v147;
    igi2_frame.ptEnd[v57 / 0x18].vX = igi2_frame.v206 * igi2_frame.v120 + v35;
    igi2_frame.ptEnd[v57 / 0x18].vY = v59 + v37;
    igi2_frame.ptEnd[v57 / 0x18].vZ = igi2_frame.v148 + v38;
    v61 = 24 * v40;
    *(double *)((char *)&igi2_frame.ptIntersection.ptHitObj + v61) = v35;
    ++v40;
    *(double *)((char *)&igi2_frame.ptIntersection.tPos.vX + v61) = v37;
    *(double *)((char *)&igi2_frame.ptIntersection.tPos.vY + v61) = v38;
    igi2_frame.v257[v61 / 8] = v58 + v35;
    igi2_frame.v257[v61 / 8 + 1] = igi2_frame.v131 + v37;
    igi2_frame.v257[v61 / 8 + 2] = v60 + v38;
    igi2_frame.v149 = igi2_frame.v207 * v60;
    v62 = igi2_frame.v207 * igi2_frame.v131;
    igi2_frame.ptEnd[v61 / 0x18].vX = igi2_frame.v207 * v58 + v35;
    igi2_frame.ptEnd[v61 / 0x18].vY = v62 + v37;
    igi2_frame.ptEnd[v61 / 0x18].vZ = igi2_frame.v149 + v38;
    v63 = 24 * v40;
    *(double *)((char *)&igi2_frame.ptIntersection.ptHitObj + v63) = v35;
    *(double *)((char *)&igi2_frame.ptIntersection.tPos.vX + v63) = v37;
    *(double *)((char *)&igi2_frame.ptIntersection.tPos.vY + v63) = v38;
    igi2_frame.v121 = v20[21];
    v64 = v20[23];
    igi2_frame.v132 = v20[22];
    igi2_frame.v257[v63 / 8] = igi2_frame.v121 + v35;
    v5 = v40 + 1;
    igi2_frame.v257[v63 / 8 + 1] = igi2_frame.v132 + v37;
    igi2_frame.v257[v63 / 8 + 2] = v64 + v38;
    igi2_frame.v150 = igi2_frame.v208 * v64;
    v65 = igi2_frame.v208 * igi2_frame.v132;
    igi2_frame.ptEnd[v63 / 0x18].vX = igi2_frame.v208 * igi2_frame.v121 + v35;
    igi2_frame.ptEnd[v63 / 0x18].vY = v65 + v37;
    igi2_frame.ptEnd[v63 / 0x18].vZ = igi2_frame.v150 + v38;
    if ( igi2_frame.v193 != 0.0 || igi2_frame.v194 != 0.0 )
    {
      v66 = 24 * v5;
      v67 = &igi2_frame.ptEnd[v5];
      v68 = &igi2_frame.v257[3 * v5++];
      igi2_frame.v161 = igi2_frame.v193 * (1.0 / v30) * 409.6000061035156;
      igi2_frame.v167 = igi2_frame.v194 * (1.0 / v30) * 409.6000061035156;
      igi2_frame.v171 = 0.0 * (1.0 / v30) * 409.6000061035156;
      *(double *)((char *)&igi2_frame.ptIntersection.ptHitObj + v66) = v35;
      *(double *)((char *)&igi2_frame.ptIntersection.tPos.vX + v66) = v37;
      *(double *)((char *)&igi2_frame.ptIntersection.tPos.vY + v66) = igi2_frame.v200;
      v67->vX = igi2_frame.v161 + v35;
      igi2_frame.ptEnd[v66 / 0x18].vY = igi2_frame.v167 + igi2_frame.nNumPoints;
      igi2_frame.ptEnd[v66 / 0x18].vZ = igi2_frame.v171 + igi2_frame.v200;
      qmemcpy(v68, v67, 0x18u);
      v34 = ptPos0;
    }
    v29 += 3;
    --igi2_frame.v191;
  }
  while ( igi2_frame.v191 );
  qmemcpy((char *)&igi2_frame.ptIntersection + 24 * v5, v34, 0x18u);
  *(&igi2_frame.ptIntersection.tPos.vY + 3 * v5) = *(&igi2_frame.ptIntersection.tPos.vY + 3 * v5) + 409.6000061035156;
  qmemcpy(&igi2_frame.ptEnd[v5], (char *)&igi2_frame.ptIntersection + 24 * v5, sizeof(struct real64x3_t));
  v69 = igi2_frame.ptEnd[v5].vZ + 10240.0;
  igi2_frame.ptEnd[v5].vZ = v69;
  igi2_frame.v200 = v69 + 409.6000061035156;
  v70 = (char *)&igi2_frame.ptIntersection + 24 * v5;
  v71 = &igi2_frame.v257[3 * v5];
  v72 = v5 + 1;
  v73 = 0;
  qmemcpy(v71, v70, 0x18u);
  v74 = ptQTask;
  if ( v72 >= 4 )
  {
    v75 = *(float *)&ptQTask[44].ptPrev;
    v76 = 3;
    v77 = 0;
    do
    {
      v76 += 4;
      v78 = v75 + *(double *)((char *)&igi2_frame.ptIntersection.tPos.vY + v77 * 8);
      v73 += 4;
      v77 += 12;
      *(double *)((char *)&igi2_frame.v240 + v77 * 8) = v78;
      igi2_frame.v255[v77] = v75 + igi2_frame.v255[v77];
      *(double *)((char *)&igi2_frame.v245 + v77 * 8) = v75 + *(double *)((char *)&igi2_frame.v245 + v77 * 8);
      igi2_frame.v255[v77 + 3] = v75 + igi2_frame.v255[v77 + 3];
      *(double *)((char *)&igi2_frame.v250 + v77 * 8) = v75 + *(double *)((char *)&igi2_frame.v250 + v77 * 8);
      igi2_frame.v255[v77 + 6] = v75 + igi2_frame.v255[v77 + 6];
      *(double *)((char *)&igi2_frame.v253 + v77 * 8) = v75 + *(double *)((char *)&igi2_frame.v253 + v77 * 8);
      igi2_frame.v255[v77 + 9] = v75 + igi2_frame.v255[v77 + 9];
    }
    while ( v76 < v72 );
  }
  if ( v73 < v72 )
  {
    v79 = *(float *)&ptQTask[44].ptPrev;
    v80 = 3 * v73;
    v81 = v72 - v73;
    do
    {
      v80 += 3;
      --v81;
      *(double *)((char *)&igi2_frame.v253 + v80 * 8) = v79 + *(double *)((char *)&igi2_frame.v253 + v80 * 8);
      igi2_frame.v255[v80 + 9] = v79 + igi2_frame.v255[v80 + 9];
    }
    while ( v81 );
  }
  HIDWORD(igi2_frame.nNumPoints) = ptQTask;
  World_TraceLinesSpecificMesh(
    Game_ptGame->ptWorld,
    igi2_frame.v258,
    (struct real64x3_t *)&igi2_frame.ptIntersection,
    igi2_frame.ptEnd,
    v72,
    GameFunctions_eObjectCollisionEvaluateQTaskEvent,
    (struct CollisionEvaluateContext_s *)&igi2_frame.nNumPoints,
    Forest_bQTaskGroup | 0x18000000,
    1);
  v82 = igi2_frame.v193;
  v83 = v72 - 1;
  v84 = v72 - 1;
  igi2_frame.v192 = 0;
  LODWORD(igi2_frame.nNumPoints) = v72 - 1;
  igi2_frame.v196 = v72 - 1;
  if ( v72 - 1 < 0 )
    goto LABEL_82;
  v85 = igi2_frame.v194;
  v86 = 0.0;
  igi2_frame.v210 = igi2_frame.ptEnd;
  p_tNormal = &igi2_frame.v258[v84].tNormal;
  v88 = 3 * v84;
  while ( 1 )
  {
    if ( !LODWORD(p_tNormal[3].vX) )
      goto LABEL_73;
    if ( *(double *)((char *)&igi2_frame.ptIntersection.tPos.vY + v88 * 8) >= igi2_frame.v200 )
      goto LABEL_73;
    igi2_frame.vX = p_tNormal->vX;
    igi2_frame.vZ = p_tNormal->vZ;
    igi2_frame.vY = p_tNormal->vY;
    igi2_frame.v153 = sqrt(igi2_frame.vX * igi2_frame.vX + igi2_frame.vY * igi2_frame.vY + igi2_frame.vZ * igi2_frame.vZ);
    if ( igi2_frame.v153 == 0.0 )
      goto LABEL_73;
    v89 = v84 < v83;
    v90 = 1.0 / igi2_frame.v153;
    igi2_frame.v186 = igi2_frame.vX * v90;
    igi2_frame.v188 = igi2_frame.vY * v90;
    igi2_frame.v190 = v90 * igi2_frame.vZ;
    if ( v84 == v83 )
    {
      if ( igi2_frame.v190 < 0.0 )
      {
        v91 = *(double *)&p_tNormal[-3].vY - *(double *)((char *)&igi2_frame.ptIntersection.tPos.vY + v88 * 8);
        v92 = p_tNormal[-3].vY;
        HIDWORD(igi2_frame.v200) = LODWORD(p_tNormal[-3].vZ);
        v93 = *(_DWORD *)&v74[32].eQTaskType;
        v94 = v91 + 409.6000061035156;
        *(float *)&igi2_frame.v200 = v92;
        if ( v93 < 0 )
          return;
        if ( v93 <= 1 )
        {
          if ( v94 < 7372.7998046875 )
            LOBYTE(v74[50].ptPrev) &= ~1u;
          if ( v94 >= 9420.7998046875 )
            goto LABEL_51;
          ptPrev = (char)v74[50].ptPrev;
        }
        else
        {
          if ( v93 != 2 )
            return;
          if ( v94 < 6144.0 )
          {
            v95 = (int)v74[50].ptPrev & 0xF4;
LABEL_50:
            LOBYTE(v74[50].ptPrev) = v95;
LABEL_51:
            if ( ptPos1->vZ > ptPos0->vZ )
              ptPos1->vZ = ptPos0->vZ;
            if ( v94 < *(float *)&v74[44].tQTaskChildren.ptHead + 1228.800048828125 )
            {
              igi2_frame.v133 = p_tNormal->vY;
              v97 = sqrt(p_tNormal->vX * p_tNormal->vX + igi2_frame.v133 * igi2_frame.v133);
              if ( v97 > 0.009999999776482582 )
              {
                igi2_frame.v122 = p_tNormal->vX * (1.0 / v97);
                igi2_frame.v134 = igi2_frame.v133 * (1.0 / v97);
                v98 = 1.0 / v97 * 0.0;
                v99 = v98 * v86 + igi2_frame.v134 * v85 + igi2_frame.v122 * v82;
                igi2_frame.v154 = v99;
                if ( v99 < 0.0 )
                {
                  igi2_frame.v135 = igi2_frame.v134 * igi2_frame.v154;
                  igi2_frame.v151 = v98 * igi2_frame.v154;
                  v82 = v82 - igi2_frame.v122 * igi2_frame.v154;
                  v85 = v85 - igi2_frame.v135;
                  v86 = v86 - igi2_frame.v151;
                }
              }
              if ( *(_DWORD *)&v74[42].eQTaskType )
              {
                igi2_frame.v123 = *(float *)&v74[42].ptNext;
                igi2_frame.v136 = *(float *)&v74[42].ptPrev;
                v100 = sqrt(igi2_frame.v123 * igi2_frame.v123 + igi2_frame.v136 * igi2_frame.v136);
                if ( v100 > 0.009999999776482582 )
                {
                  igi2_frame.v124 = igi2_frame.v123 * (1.0 / v100);
                  igi2_frame.v137 = igi2_frame.v136 * (1.0 / v100);
                  v101 = 1.0 / v100 * 0.0;
                  v102 = v101 * v86 + igi2_frame.v137 * v85 + igi2_frame.v124 * v82;
                  igi2_frame.v155 = v102;
                  if ( v102 < 0.0 )
                  {
                    igi2_frame.v138 = igi2_frame.v137 * igi2_frame.v155;
                    igi2_frame.v152 = v101 * igi2_frame.v155;
                    v82 = v82 - igi2_frame.v124 * igi2_frame.v155;
                    v85 = v85 - igi2_frame.v138;
                    v86 = v86 - igi2_frame.v152;
                  }
                }
              }
            }
            goto LABEL_73;
          }
          ptPrev = (char)v74[50].ptPrev;
          if ( v94 < 7372.7998046875 )
          {
            v95 = ptPrev & 0xF6;
            goto LABEL_50;
          }
        }
        v95 = ptPrev & 0xF7;
        goto LABEL_50;
      }
      v89 = v84 < v83;
    }
    if ( v89 )
    {
      igi2_frame.v162 = *(double *)&p_tNormal[-4].vX - igi2_frame.v257[v88];
      igi2_frame.v168 = *(double *)&p_tNormal[-4].vZ - igi2_frame.v257[v88 + 1];
      igi2_frame.v172 = *(double *)&p_tNormal[-3].vY - igi2_frame.v257[v88 + 2];
      if ( igi2_frame.v172 * (igi2_frame.v257[v88 + 2] - *(double *)((char *)&igi2_frame.ptIntersection.tPos.vY + v88 * 8))
         + (igi2_frame.v257[v88 + 1] - *(double *)((char *)&igi2_frame.ptIntersection.tPos.vX + v88 * 8)) * igi2_frame.v168
         + (igi2_frame.v257[v88] - *(double *)((char *)&igi2_frame.ptIntersection.ptHitObj + v88 * 8)) * igi2_frame.v162 < 0.0 )
      {
        igi2_frame.v156 = igi2_frame.v172 * igi2_frame.v190 + igi2_frame.v168 * igi2_frame.v188 + igi2_frame.v162 * igi2_frame.v186;
        v103 = igi2_frame.v156 * igi2_frame.v186;
        if ( igi2_frame.v156 <= 0.0 )
        {
          v103 = -v103;
          v104 = -(igi2_frame.v156 * igi2_frame.v188);
        }
        else
        {
          v104 = igi2_frame.v156 * igi2_frame.v188;
        }
        ++igi2_frame.v197;
        igi2_frame.v198 = v103 + igi2_frame.v198;
        igi2_frame.v199 = v104 + igi2_frame.v199;
      }
    }
    *pbSignal |= 4u;
    v105 = sqrt(igi2_frame.v186 * igi2_frame.v186 + igi2_frame.v188 * igi2_frame.v188);
    if ( v105 != 0.0 )
    {
      igi2_frame.v175 = igi2_frame.v186 * (1.0 / v105);
      igi2_frame.v178 = igi2_frame.v188 * (1.0 / v105);
      v106 = 1.0 / v105 * 0.0;
      v107 = v106 * v86 + igi2_frame.v178 * v85 + igi2_frame.v175 * v82;
      igi2_frame.v157 = v107;
      if ( v107 < 0.0 )
      {
        igi2_frame.v239[igi2_frame.v192] = v84;
        v108 = igi2_frame.v210;
        v109 = igi2_frame.v210;
        *(float *)&igi2_frame.v210->vX = igi2_frame.v186;
        *((float *)&v109->vX + 1) = igi2_frame.v188;
        igi2_frame.v179 = igi2_frame.v178 * igi2_frame.v157;
        *(float *)&v109->vY = igi2_frame.v190;
        ++igi2_frame.v192;
        v84 = igi2_frame.v196;
        igi2_frame.v183 = v106 * igi2_frame.v157;
        igi2_frame.v210 = (struct real64x3_t *)((char *)&v108->vY + 4);
        v82 = v82 - igi2_frame.v175 * igi2_frame.v157;
        v85 = v85 - igi2_frame.v179;
        v86 = v86 - igi2_frame.v183;
      }
    }
    v110 = igi2_frame.v190 * v86 + igi2_frame.v188 * v85 + igi2_frame.v186 * v82;
    v74 = ptQTask;
    if ( v110 < 0.0 )
    {
      igi2_frame.v180 = igi2_frame.v188 * v110;
      igi2_frame.v184 = igi2_frame.v190 * v110;
      v82 = v82 - igi2_frame.v186 * v110;
      v85 = v85 - igi2_frame.v180;
      v86 = v86 - igi2_frame.v184;
    }
LABEL_73:
    --v84;
    p_tNormal -= 10;
    v88 -= 3;
    igi2_frame.v196 = v84;
    if ( v84 < 0 )
      break;
    v83 = LODWORD(igi2_frame.nNumPoints);
  }
  igi2_frame.v194 = v85;
  if ( igi2_frame.v192 > 1 )
  {
    v111 = 1;
    p_vZ = (float *)&igi2_frame.ptEnd[0].vZ;
    while ( 1 )
    {
      v113 = *(float *)&igi2_frame.ptEnd[0].vY * p_vZ[1]
           + *(float *)&igi2_frame.ptEnd[0].vX * *(p_vZ - 1)
           + *((float *)&igi2_frame.ptEnd[0].vX + 1) * *p_vZ;
      if ( v113 < 0.8999999761581421 )
      {
        if ( v113 >= 0.0 )
          break;
        v114 = igi2_frame.v239[v111];
        igi2_frame.v163 = igi2_frame.v258[igi2_frame.v239[0]].tPos.vX - igi2_frame.v258[v114].tPos.vX;
        igi2_frame.v169 = igi2_frame.v258[igi2_frame.v239[0]].tPos.vY - igi2_frame.v258[v114].tPos.vY;
        v115 = igi2_frame.v258[igi2_frame.v239[0]].tPos.vZ - igi2_frame.v258[v114].tPos.vZ;
        if ( sqrt(igi2_frame.v163 * igi2_frame.v163 + igi2_frame.v169 * igi2_frame.v169 + v115 * v115) < 2048.0 )
          break;
      }
      ++v111;
      p_vZ += 3;
      if ( v111 >= igi2_frame.v192 )
        goto LABEL_80;
    }
    igi2_frame.v194 = 0.0;
    v82 = 0.0;
  }
LABEL_80:
  if ( igi2_frame.v197 )
  {
    v116 = 1.0 / (double)igi2_frame.v197;
    igi2_frame.v198 = igi2_frame.v198 * v116;
    igi2_frame.v199 = v116 * igi2_frame.v199;
  }
LABEL_82:
  ptPos1->vX = v82 + igi2_frame.v198 + ptPos0->vX;
  ptPos1->vY = igi2_frame.v194 + igi2_frame.v199 + ptPos0->vY;
  ptSpeed->vX = ptPos1->vX - ptPos0->vX;
  ptSpeed->vY = ptPos1->vY - ptPos0->vY;
  ptSpeed->vZ = ptPos1->vZ - ptPos0->vZ;
}

// source: j/0/human/human.c:831  [anchor-callee]
void __cdecl Human_GroundCollision(
        struct QTask_s *ptQTask,
        struct real64x3_t *ptPos0,
        struct real64x3_t *ptPos1,
        struct real32x3_t *ptSpeed,
        unsigned int *pbSignal,
        float vTolerance)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct World_s *ptWorld; };
    struct { char igi2_o1[56]; int v47; };
    struct { char igi2_o2[56]; struct GraphNode_s *v48; };
    struct { char igi2_o3[60]; double pvDistance; };
    struct { char igi2_o4[68]; float v50; };
    struct { char igi2_o5[72]; int v51; };
    struct { char igi2_o6[76]; struct GraphNode_s *v52; };
    struct { char igi2_o7[80]; struct QTask_s *v53; };
    struct { char igi2_o8[84]; float v54; };
    struct { char igi2_o9[88]; float v55; };
    struct { char igi2_o10[92]; float v56; };
    struct { char igi2_o11[100]; struct real64x3_t ptPosition; };
    struct { char igi2_o12[124]; int v58; };
    struct { char igi2_o13[128]; int v59; };
    struct { char igi2_o14[132]; int v60; };
    struct { char igi2_o15[136]; _DWORD *v61; };
    struct { char igi2_o16[140]; struct real64x3_t v62; };
    struct { char igi2_o17[164]; struct real64x3_t v63; };
    struct { char igi2_o18[188]; struct CollisionEvaluateContext_s ptEvalContext; };
    struct { char igi2_o19[196]; double v65; };
    struct { char igi2_o20[204]; struct QIntersection_s ptIntersection[2]; };
    struct { char igi2_o21[444]; struct real64x3_t ptStart; };
    struct { char igi2_o22[468]; _BYTE v68[24]; };
    struct { char igi2_o23[492]; _DWORD v69[23]; };
    struct { char igi2_o24[584]; int v70; };
    struct { char igi2_o25[604]; float v71; };
    char igi2_extent[616];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct real64x3_t *v6; // edx
  double v7; // st7
  struct QTask_s *ptParent; // ebx
  int vX_high; // ecx
  double v10; // st7
  unsigned int vY_low; // eax
  struct Graph_s *ptHead; // esi
  struct GraphNode_s *Node; // eax
  struct QTask_s *v14; // ecx
  int v15; // ebx
  int v16; // ebx
  struct GraphNode_s *v17; // edi
  int v18; // eax
  struct QTask_s *v19; // ebx
  struct Graph_s *v20; // esi
  int ptMiddle; // eax
  struct real64x3_t *v22; // edx
  int ptTail; // eax
  struct GraphNode_s *v24; // eax
  double v25; // st6
  double v26; // st5
  double v27; // st4
  double v28; // st7
  long double v29; // st6
  long double v30; // st6
  struct QObj_s *ptHitObj; // ebx
  double vDistance; // st7
  struct QReference_s *v33; // eax
  double v34; // st7
  float *p_tQTaskRefList; // ecx
  long double v36; // st7
  void (__cdecl *pfHandler)(struct QObj_s *, struct real64x3_t *); // eax
  double v38; // st7
  double v39; // st7
  struct QReference_s *v40; // eax
  double v41; // st7
  double v42; // st6
  double v43; // st7
  long double v44; // st7
  double v45; // st6

  v6 = ptPos1;
  memset(&ptQTask[40].tQTaskRefList.ptMiddle, 0, 0x78u);
  v7 = *(float *)&ptQTask[44].tQTaskChildren.ptHead;
  ptParent = ptQTask[48].ptParent;
  ptQTask[43].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[43].tQTaskRefList.ptTail = (struct QReference_s *)1104150528;
  vX_high = HIDWORD(ptPos1->vX);
  v10 = v7 + ptPos1->vZ;
  LODWORD(igi2_frame.ptStart.vX) = LODWORD(ptPos1->vX);
  vY_low = LODWORD(ptPos1->vY);
  HIDWORD(igi2_frame.ptStart.vX) = vX_high;
  igi2_frame.ptStart.vZ = v10;
  igi2_frame.v47 = 0;
  *(_QWORD *)&igi2_frame.ptStart.vY = __PAIR64__(HIDWORD(ptPos1->vY), vY_low);
  igi2_frame.ptIntersection[0].vLight = 0.0;
  igi2_frame.ptIntersection[1].vLight = 0.0;
  igi2_frame.v53 = ptParent;
  if ( ptParent && !LOBYTE(ptQTask[29].tQTaskRefList.ptHead) )
  {
    memset(igi2_frame.ptIntersection, 0, sizeof(igi2_frame.ptIntersection));
    ptQTask[43].tQTaskRefList.ptMiddle = nullptr;
    ptQTask[43].tQTaskRefList.ptTail = nullptr;
    ptHead = (struct Graph_s *)ptParent[728].tQTaskChildren.ptHead;
    if ( ptHead )
    {
      Node = Graph_GetNode(ptHead, (int)ptParent[748].tQTaskRefList.ptTail);
      v14 = ptParent[6].ptParent;
      v15 = -(v14->ptNext != nullptr);
      igi2_frame.v48 = Node;
      igi2_frame.v52 = nullptr;
      v16 = (unsigned int)v14 & v15;
      Graph_GetNodePos(&igi2_frame.ptPosition, Node);
      qmemcpy(&igi2_frame.ptIntersection[0].tPos, ptPos0, sizeof(igi2_frame.ptIntersection[0].tPos));
      v17 = igi2_frame.v48;
      igi2_frame.ptIntersection[0].ptEnterMaterial = igi2_frame.v48->ptGroundMaterial;
      igi2_frame.ptIntersection[0].isHit = 1;
      igi2_frame.ptIntersection[0].tNormal.vX = 0.0;
      igi2_frame.ptIntersection[0].tNormal.vY = 0.0;
      igi2_frame.ptIntersection[0].tNormal.vZ = 1.0;
      if ( v16 )
      {
        v18 = *(_DWORD *)(v16 + 36);
        v19 = igi2_frame.v53;
        igi2_frame.v52 = Graph_GetNode((struct Graph_s *)igi2_frame.v53[728].tQTaskChildren.ptHead, v18);
        Graph_GetNodePos(&igi2_frame.v62, igi2_frame.v52);
      }
      else
      {
        v19 = igi2_frame.v53;
        qmemcpy(&igi2_frame.v62, &igi2_frame.ptPosition, sizeof(igi2_frame.v62));
        v17 = igi2_frame.v48;
      }
      v20 = (struct Graph_s *)v19[728].tQTaskChildren.ptHead;
      if ( v19[12].tQTaskChildren.ptTail )
      {
        ptMiddle = (int)v19[12].tQTaskChildren.ptHead;
        if ( ptMiddle == v17->nID )
          ptMiddle = (int)v19[12].tQTaskChildren.ptMiddle;
        igi2_frame.v52 = Graph_GetNode(v20, ptMiddle);
        Graph_GetNodePos(&igi2_frame.v62, igi2_frame.v52);
        v22 = ptPos0;
      }
      else
      {
        ptTail = (int)v19[748].tQTaskRefList.ptMiddle;
        if ( ptTail == -1 )
          ptTail = (int)v19[748].tQTaskRefList.ptTail;
        v24 = Graph_GetNode(v20, ptTail);
        Graph_GetNodePos(&igi2_frame.v63, v24);
        v22 = ptPos0;
        igi2_frame.v55 = igi2_frame.ptPosition.vY - igi2_frame.v63.vY;
        igi2_frame.v56 = igi2_frame.ptPosition.vZ - igi2_frame.v63.vZ;
        *(float *)&igi2_frame.pvDistance = ptPos0->vX - igi2_frame.v63.vX;
        *((float *)&igi2_frame.pvDistance + 1) = ptPos0->vY - igi2_frame.v63.vY;
        v25 = ptPos0->vZ - igi2_frame.v63.vZ;
        v26 = *((float *)&igi2_frame.pvDistance + 1);
        v27 = *(float *)&igi2_frame.pvDistance;
        igi2_frame.pvDistance = igi2_frame.v56;
        igi2_frame.v65 = igi2_frame.ptPosition.vX - igi2_frame.v63.vX;
        if ( sqrt(igi2_frame.v65 * igi2_frame.v65 + igi2_frame.v55 * igi2_frame.v55 + igi2_frame.v56 * igi2_frame.v56) > sqrt(v26 * v26 + v25 * v25 + v27 * v27) )
        {
          qmemcpy(&igi2_frame.v62, &igi2_frame.ptPosition, sizeof(igi2_frame.v62));
          qmemcpy(&igi2_frame.ptPosition, &igi2_frame.v63, sizeof(igi2_frame.ptPosition));
          v17 = igi2_frame.v48;
        }
      }
      igi2_frame.v54 = igi2_frame.v62.vX - igi2_frame.ptPosition.vX;
      igi2_frame.v55 = igi2_frame.v62.vY - igi2_frame.ptPosition.vY;
      v28 = igi2_frame.v62.vZ - igi2_frame.ptPosition.vZ;
      *(float *)&igi2_frame.pvDistance = v22->vX - igi2_frame.ptPosition.vX;
      *((float *)&igi2_frame.pvDistance + 1) = v22->vY - igi2_frame.ptPosition.vY;
      igi2_frame.v50 = v22->vZ - igi2_frame.ptPosition.vZ;
      v29 = sqrt(igi2_frame.v54 * igi2_frame.v54 + igi2_frame.v55 * igi2_frame.v55 + (igi2_frame.v62.vZ - igi2_frame.ptPosition.vZ) * (igi2_frame.v62.vZ - igi2_frame.ptPosition.vZ));
      if ( v29 <= 0.0
        || (v30 = sqrt(
                    *(float *)&igi2_frame.pvDistance * *(float *)&igi2_frame.pvDistance
                  + *((float *)&igi2_frame.pvDistance + 1) * *((float *)&igi2_frame.pvDistance + 1)
                  + igi2_frame.v50 * igi2_frame.v50)
                / v29,
            v30 < 0.0) )
      {
        v30 = 0.0;
      }
      else if ( v30 > 1.0 )
      {
        v30 = 1.0;
      }
      if ( igi2_frame.v52 )
        *(float *)&ptQTask[49].ptParent = (igi2_frame.v52->vLightValue - v17->vLightValue) * v30 + v17->vLightValue;
      else
        ptQTask[49].ptParent = (struct QTask_s *)LODWORD(v17->vLightValue);
      ptParent = igi2_frame.v53;
      v6 = ptPos1;
      igi2_frame.ptIntersection[0].tPos.vZ = v30 * v28 + igi2_frame.ptPosition.vZ;
    }
    ptHitObj = (struct QObj_s *)ptParent[728].tQTaskChildren.ptHead;
    igi2_frame.ptIntersection[0].ptHitObj = ptHitObj;
    igi2_frame.v47 = 1;
    goto LABEL_43;
  }
  qmemcpy(igi2_frame.v68, ptPos1, sizeof(igi2_frame.v68));
  igi2_frame.ptEvalContext.ptQTask = ptQTask;
  igi2_frame.ptWorld = Game_ptGame->ptWorld;
  igi2_frame.pvDistance = -40960.0;
  igi2_frame.v50 = 0.0;
  igi2_frame.v51 = 1086324736;
  World_GetNextZSpecificMesh(
    igi2_frame.ptWorld,
    igi2_frame.ptIntersection,
    &igi2_frame.ptStart,
    2,
    &igi2_frame.pvDistance,
    GameFunctions_eGetNextZEvaluateQTaskEvent,
    &igi2_frame.ptEvalContext,
    0xFFFFFFFF,
    1);
  if ( igi2_frame.ptIntersection[1].isHit )
  {
    if ( igi2_frame.ptIntersection[1].tNormal.vZ < 0.0 )
    {
      vDistance = igi2_frame.ptIntersection[1].vDistance;
      *(double *)&ptQTask[44].tQTaskChildren.ptTail = igi2_frame.ptIntersection[1].vDistance;
      if ( vDistance < 7372.8 )
        *pbSignal |= 8u;
    }
  }
  if ( !igi2_frame.ptIntersection[0].isHit )
  {
    igi2_frame.pvDistance = 40960.0;
    World_GetNextZSpecificMesh(
      Game_ptGame->ptWorld,
      igi2_frame.ptIntersection,
      &igi2_frame.ptStart,
      1,
      &igi2_frame.pvDistance,
      GameFunctions_eGetNextZEvaluateQTaskEvent,
      &igi2_frame.ptEvalContext,
      0xFFFFFFFF,
      1);
    if ( !igi2_frame.ptIntersection[0].isHit )
      goto LABEL_33;
    if ( igi2_frame.ptIntersection[0].tNormal.vZ < 0.0 )
    {
      igi2_frame.ptIntersection[0].isHit = 0;
      goto LABEL_33;
    }
    ptHitObj = igi2_frame.ptIntersection[0].ptHitObj;
    v6 = ptPos1;
LABEL_43:
    if ( !igi2_frame.ptIntersection[0].isHit )
      goto LABEL_54;
    goto LABEL_46;
  }
  ptHitObj = igi2_frame.ptIntersection[0].ptHitObj;
  v6 = ptPos1;
LABEL_46:
  if ( ptHitObj && (!ptQTask[48].ptParent || LOBYTE(ptQTask[29].tQTaskRefList.ptHead)) )
  {
    qmemcpy(&igi2_frame.v62, &igi2_frame.ptIntersection[0].tPos, sizeof(igi2_frame.v62));
    igi2_frame.v62.vZ = igi2_frame.ptIntersection[0].tPos.vZ + 1638.4;
    LODWORD(igi2_frame.ptPosition.vX) = &igi2_frame.v62;
    qmemcpy(&igi2_frame.v63, &igi2_frame.v62, sizeof(igi2_frame.v63));
    igi2_frame.v63.vZ = igi2_frame.v62.vZ - 3686.4;
    HIDWORD(igi2_frame.ptPosition.vX) = &igi2_frame.v63;
    igi2_frame.v61 = igi2_frame.v69;
    igi2_frame.v70 = 0;
    igi2_frame.v69[0] = 0;
    WORD2(igi2_frame.ptPosition.vY) = 512;
    igi2_frame.ptPosition.vZ = 0.0;
    LODWORD(igi2_frame.ptPosition.vY) = 1;
    igi2_frame.v59 = 0;
    igi2_frame.v58 = 0;
    igi2_frame.v60 = 1094861636;
    pfHandler = (void (__cdecl *)(struct QObj_s *, struct real64x3_t *))QTask_aatQTaskFinalEvent[11][ptHitObj->tQTask.eQTaskType].pfHandler;
    if ( pfHandler )
    {
      pfHandler(ptHitObj, &igi2_frame.ptPosition);
      ptHitObj = igi2_frame.ptIntersection[0].ptHitObj;
      if ( igi2_frame.v70 )
      {
        v38 = igi2_frame.v71 - *(float *)&ptQTask[49].ptParent;
        igi2_frame.ptIntersection[0].ptEnterMaterial = (struct QMaterial_t *)igi2_frame.v69[20];
        *(float *)&ptQTask[49].ptParent = v38 * 0.5 + *(float *)&ptQTask[49].ptParent;
      }
      v6 = ptPos1;
    }
  }
  v39 = v6->vZ - igi2_frame.ptIntersection[0].tPos.vZ;
  *(double *)&ptQTask[43].tQTaskRefList.ptMiddle = v39;
  if ( v39 <= vTolerance )
    goto LABEL_55;
LABEL_54:
  if ( igi2_frame.v47 )
  {
LABEL_55:
    if ( igi2_frame.ptIntersection[0].tNormal.vZ < 0.0 )
    {
      igi2_frame.ptIntersection[0].tNormal.vX = -igi2_frame.ptIntersection[0].tNormal.vX;
      igi2_frame.ptIntersection[0].tNormal.vY = -igi2_frame.ptIntersection[0].tNormal.vY;
      igi2_frame.ptIntersection[0].tNormal.vZ = -igi2_frame.ptIntersection[0].tNormal.vZ;
      igi2_frame.ptIntersection[0].tLocalNormal.vX = -igi2_frame.ptIntersection[0].tLocalNormal.vX;
      igi2_frame.ptIntersection[0].tLocalNormal.vY = -igi2_frame.ptIntersection[0].tLocalNormal.vY;
      igi2_frame.ptIntersection[0].tLocalNormal.vZ = -igi2_frame.ptIntersection[0].tLocalNormal.vZ;
    }
    *pbSignal |= 2u;
    if ( !LOBYTE(ptQTask[29].tQTaskRefList.ptHead)
      || igi2_frame.ptIntersection[0].tPos.vZ > *(double *)&ptQTask[1].tQTaskChildren.ptTail )
    {
      v6->vZ = igi2_frame.ptIntersection[0].tPos.vZ;
    }
    if ( ptHitObj )
    {
      Human_SetGroundTask(ptQTask, &ptHitObj->tQTask);
      v6 = ptPos1;
    }
    else
    {
      v40 = ptQTask[44].tQTaskRefList.ptMiddle;
      if ( v40 && v40->pxObject )
      {
        QReference_Delete(v40, &QTask_tQTaskRefPool);
        v6 = ptPos1;
        ptQTask[44].tQTaskRefList.ptMiddle = nullptr;
        HIBYTE(ptQTask[74].ptPrev) = 0;
      }
    }
    v41 = v6->vX - ptPos0->vX;
    v42 = v6->vY - ptPos0->vY;
    if ( v41 == 0.0 && v42 == 0.0 )
    {
      v43 = 0.0;
    }
    else
    {
      v44 = sqrt(v41 * v41 + v42 * v42);
      v45 = v6->vZ - ptPos0->vZ;
      v43 = Real64_Asin(v45 / sqrt(v45 * v45 + v44 * v44));
    }
    *(float *)&ptQTask[43].eQTaskType = v43;
    *(float *)&ptQTask[44].ptNext = v43 * 0.6366197466850281;
    goto LABEL_36;
  }
LABEL_33:
  *pbSignal &= ~2u;
  v33 = ptQTask[44].tQTaskRefList.ptMiddle;
  if ( v33 && v33->pxObject )
  {
    QReference_Delete(v33, &QTask_tQTaskRefPool);
    ptQTask[44].tQTaskRefList.ptMiddle = nullptr;
    HIBYTE(ptQTask[74].ptPrev) = 0;
  }
LABEL_36:
  qmemcpy(&ptQTask[40].tQTaskRefList.ptMiddle, igi2_frame.ptIntersection, 0x78u);
  if ( igi2_frame.ptIntersection[0].isHit )
  {
    v34 = *(float *)&ptQTask[7].tQTaskChildren.ptTail;
    qmemcpy(&ptQTask[47].tQTaskChildren, &igi2_frame.ptIntersection[0].tPos, 0x18u);
    *(double *)&ptQTask[47].tQTaskChildren.ptHead = v34 + *(double *)&ptQTask[47].tQTaskChildren.ptHead;
    *(double *)&ptQTask[47].tQTaskChildren.ptTail = *(float *)&ptQTask[7].tQTaskRefList.ptHead
                                                  + *(double *)&ptQTask[47].tQTaskChildren.ptTail;
    *(float *)&ptQTask[48].tQTaskChildren.ptTail = *(double *)&ptQTask[43].tQTaskRefList.ptMiddle;
    p_tQTaskRefList = (float *)&ptQTask[48].tQTaskRefList;
    ptQTask[48].tQTaskRefList = (*(struct QReferenceList_s *)&igi2_frame.ptIntersection[0].tNormal);
    if ( *(float *)&ptQTask[48].tQTaskRefList.ptHead != 0.0
      || *(float *)&ptQTask[48].tQTaskRefList.ptMiddle != 0.0
      || *(float *)&ptQTask[48].tQTaskRefList.ptTail != 0.0 )
    {
      v36 = 1.0
          / sqrt(
              *p_tQTaskRefList * *p_tQTaskRefList
            + *(float *)&ptQTask[48].tQTaskRefList.ptMiddle * *(float *)&ptQTask[48].tQTaskRefList.ptMiddle
            + *(float *)&ptQTask[48].tQTaskRefList.ptTail * *(float *)&ptQTask[48].tQTaskRefList.ptTail);
      *p_tQTaskRefList = *p_tQTaskRefList * v36;
      *(float *)&ptQTask[48].tQTaskRefList.ptMiddle = *(float *)&ptQTask[48].tQTaskRefList.ptMiddle * v36;
      *(float *)&ptQTask[48].tQTaskRefList.ptTail = *(float *)&ptQTask[48].tQTaskRefList.ptTail * v36;
    }
    ptQTask[48].tQTaskChildren.ptHead = (struct QTask_s *)1;
  }
  else
  {
    ptQTask[47].tQTaskChildren.ptHead = nullptr;
    ptQTask[47].tQTaskChildren.ptMiddle = nullptr;
    ptQTask[47].tQTaskChildren.ptTail = nullptr;
    ptQTask[47].tQTaskRefList.ptHead = nullptr;
    ptQTask[47].tQTaskRefList.ptMiddle = nullptr;
    ptQTask[47].tQTaskRefList.ptTail = nullptr;
    ptQTask[48].tQTaskChildren.ptHead = nullptr;
  }
}

// source: j/0/human/human.c:1266  [anchor-callee]
void __cdecl Human_HumanCollision(
        struct QTask_s *ptQTask,
        struct real64x3_t *ptPos0,
        struct real64x3_t *ptPos1,
        struct real32x3_t *ptSpeed)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct QTask_s **v14; };
    struct { char igi2_o1[4]; struct QTaskList_s *ptQTaskList; };
    struct { char igi2_o2[8]; struct HumanAIEventContext_t tEventContext; };
    char igi2_extent[76];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s **v5; // eax
  struct QTask_s *v6; // ecx
  double v7; // st6
  double v8; // st5
  long double v9; // st7
  double v10; // st4
  struct QReference_s *ptTail; // edx
  struct real64x3_t *p_tQTaskChildren; // eax
  bool v13; // cc
  struct QTask_s *ptQTaska = *(struct QTask_s * *)&ptPos0; // [esp+58h] [ebp+4h] ARGSLOT

  igi2_frame.ptQTaskList = Human_ptQTaskList;
  ptQTaska = nullptr;
  if ( Human_ptQTaskList->nTask > 0 )
  {
    v5 = Human_ptQTaskList->ptQTask;
    igi2_frame.v14 = Human_ptQTaskList->ptQTask;
    do
    {
      v6 = *v5;
      if ( BYTE1((*v5)[29].tQTaskRefList.ptHead) && !LOBYTE(v6[29].tQTaskRefList.ptHead) && v6 != ptQTask )
      {
        v8 = ptPos1->vZ - *(double *)&v6[1].tQTaskChildren.ptTail;
        if ( v8 < 0.0 )
          v8 = -v8;
        if ( v8 < 7372.8 )
        {
          v7 = ptPos1->vY - *(double *)&v6[1].tQTaskChildren.ptHead;
          v9 = sqrt(v7 * v7 + (ptPos1->vX - *(double *)&v6[1].ptNext) * (ptPos1->vX - *(double *)&v6[1].ptNext));
          if ( v9 < 3072.0 )
          {
            v10 = ptPos0->vY - *(double *)&v6[1].tQTaskChildren.ptHead;
            if ( v9 < sqrt(v10 * v10 + (ptPos0->vX - *(double *)&v6[1].ptNext) * (ptPos0->vX - *(double *)&v6[1].ptNext)) )
            {
              ptPos1->vX = ptPos0->vX;
              ptPos1->vY = ptPos0->vY;
              if ( ptQTask->eQTaskType == HumanPlayer_eQTaskType )
              {
                ptTail = ptQTask[10].tQTaskRefList.ptTail;
                p_tQTaskChildren = (struct real64x3_t *)&ptQTask[33].tQTaskChildren.ptTail[10].tQTaskChildren;
                igi2_frame.tEventContext.eEvent = 9;
                igi2_frame.tEventContext.eTeam = (int)ptTail;
                igi2_frame.tEventContext.bFlags = 1090;
                igi2_frame.tEventContext.vRadius = 12288.0;
                igi2_frame.tEventContext.ptPosition = p_tQTaskChildren;
                igi2_frame.tEventContext.ptReferenceQTask = ptQTask;
                igi2_frame.tEventContext.ptHumanOriginatorQTask = ptQTask;
                HumanAI_SendEvent(&igi2_frame.tEventContext);
              }
            }
          }
        }
      }
      v5 = igi2_frame.v14 + 1;
      v13 = (int)&ptQTaska->ptNext + 1 < igi2_frame.ptQTaskList->nTask;
      ptQTaska = (struct QTask_s *)((char *)ptQTaska + 1);
      ++igi2_frame.v14;
    }
    while ( v13 );
  }
  ptSpeed->vX = ptPos1->vX - ptPos0->vX;
  ptSpeed->vY = ptPos1->vY - ptPos0->vY;
  ptSpeed->vZ = ptPos1->vZ - ptPos0->vZ;
}

// source: j/0/human/human.c:1362  [anchor-caller]
void __cdecl Human_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTaskList_s *v2; // ebx
  int v3; // edi
  bool v4; // zf
  int v5; // eax
  struct QReference_s *v6; // ecx
  int v7; // ebp
  struct QTask_s *v8; // eax
  int i; // ebp
  struct AmmoType_s *AmmoTypeFromID; // eax
  struct AmmoTypeItem_s *AmmoTypeItemFromAmmoType; // eax
  int nMaxAmmo; // ecx
  int nAmmoCount; // edx
  struct QTask_s *eDifficultyLevel; // edx
  int v15; // ecx
  struct TexInfo_s *p_tTexInfo; // [esp-4h] [ebp-14h]

  if ( Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER && !pxContext )
    LOBYTE(ptQTask[46].eQTaskType) = 1;
  BoneDynCubeObj_Init((struct BoneDynCubeObj_s *)ptQTask, Game_ptGame->ptWorld);
  v2 = Human_ptQTaskList;
  *(_DWORD *)&ptQTask[6].eQTaskType = 2;
  ptQTask[2].tQTaskRefList.ptTail = (struct QReference_s *)9;
  QTaskList_RegisterSafe(v2, ptQTask);
  QTaskList_Register(AIDetection_ptDetectionQTaskList, (struct QTaskList_s *)ptQTask);
  QTaskList_Register(GameFunctions_ptExplosionQTaskList, (struct QTaskList_s *)ptQTask);
  v3 = 0;
  while ( HumanCamera_atHumanList[v3].isUsed )
  {
    if ( ++v3 >= 128 )
      goto LABEL_9;
  }
  HumanCamera_atHumanList[v3].ptHumanQTaskRef = QTask_NewQTaskRef(ptQTask);
  HumanCamera_atHumanList[v3].isUsed = 1;
LABEL_9:
  ptQTask[29].tQTaskRefList.ptMiddle = (struct QReference_s *)1065353216;
  ptQTask[29].tQTaskRefList.ptTail = nullptr;
  ptQTask[29].ptParent = nullptr;
  *(_DWORD *)&ptQTask[29].eQTaskType = 0;
  ptQTask[30].ptNext = (struct QTask_s *)1065353216;
  ptQTask[30].ptPrev = nullptr;
  ptQTask[30].tQTaskChildren.ptHead = nullptr;
  ptQTask[30].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[30].tQTaskChildren.ptTail = (struct QTask_s *)1065353216;
  ptQTask[30].tQTaskRefList.ptHead = nullptr;
  memset(&ptQTask[12].ptParent, 0, 0xFCu);
  memset(&ptQTask[19].ptPrev, 0, 0xFCu);
  LOBYTE(ptQTask[25].tQTaskChildren.ptTail) = 0;
  LOBYTE(ptQTask[32].tQTaskRefList.ptTail) = 0;
  ptQTask[32].ptParent = nullptr;
  *(_DWORD *)&ptQTask[32].eQTaskType = 0;
  ptQTask[33].tQTaskRefList.ptHead = (struct QReference_s *)1;
  LOBYTE(ptQTask[33].tQTaskRefList.ptMiddle) = 0;
  ptQTask[33].tQTaskRefList.ptTail = nullptr;
  ptQTask[33].ptParent = nullptr;
  *(_DWORD *)&ptQTask[33].eQTaskType = 0;
  ptQTask[34].ptNext = nullptr;
  ptQTask[34].ptPrev = nullptr;
  ptQTask[34].tQTaskChildren.ptHead = nullptr;
  ptQTask[43].ptParent = nullptr;
  LOBYTE(ptQTask[34].tQTaskChildren.ptMiddle) = 0;
  ptQTask[36].ptPrev = nullptr;
  ptQTask[36].tQTaskChildren.ptHead = nullptr;
  ptQTask[36].tQTaskChildren.ptMiddle = nullptr;
  LOBYTE(ptQTask[36].tQTaskChildren.ptTail) = 0;
  BYTE1(ptQTask[36].tQTaskChildren.ptTail) = 0;
  ptQTask[36].tQTaskRefList.ptHead = (struct QReference_s *)1065353216;
  LOBYTE(ptQTask[36].tQTaskRefList.ptMiddle) = 1;
  ptQTask[38].ptPrev = nullptr;
  ptQTask[38].tQTaskChildren.ptHead = nullptr;
  ptQTask[38].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[38].tQTaskChildren.ptTail = nullptr;
  ptQTask[38].tQTaskRefList.ptHead = nullptr;
  ptQTask[38].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[38].tQTaskRefList.ptTail = nullptr;
  ptQTask[38].ptParent = nullptr;
  *(_DWORD *)&ptQTask[38].eQTaskType = 0;
  ptQTask[37].ptParent = nullptr;
  *(_DWORD *)&ptQTask[37].eQTaskType = 0;
  ptQTask[38].ptNext = nullptr;
  ptQTask[39].ptNext = nullptr;
  ptQTask[39].ptPrev = nullptr;
  ptQTask[39].tQTaskChildren.ptHead = nullptr;
  ptQTask[37].tQTaskChildren.ptHead = nullptr;
  ptQTask[37].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[37].tQTaskChildren.ptTail = nullptr;
  ptQTask[37].tQTaskRefList.ptHead = nullptr;
  ptQTask[37].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[37].tQTaskRefList.ptTail = nullptr;
  ptQTask[50].tQTaskRefList.ptHead = nullptr;
  ptQTask[50].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[50].tQTaskRefList.ptTail = nullptr;
  BYTE1(ptQTask[40].tQTaskChildren.ptMiddle) = 1;
  BYTE2(ptQTask[40].tQTaskChildren.ptMiddle) = 0;
  HIBYTE(ptQTask[40].tQTaskChildren.ptMiddle) = 0;
  LOBYTE(ptQTask[40].tQTaskChildren.ptTail) = 0;
  BYTE2(ptQTask[50].ptNext) = 0;
  HIBYTE(ptQTask[50].ptNext) = 0;
  ptQTask[48].ptPrev = nullptr;
  memset(&ptQTask[40].tQTaskRefList.ptMiddle, 0, 0x78u);
  LOBYTE(ptQTask[40].tQTaskChildren.ptMiddle) = 0;
  ptQTask[43].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[43].tQTaskRefList.ptTail = (struct QReference_s *)1104150528;
  *(_DWORD *)&ptQTask[43].eQTaskType = 0;
  ptQTask[44].tQTaskChildren.ptTail = nullptr;
  ptQTask[44].tQTaskRefList.ptHead = (struct QReference_s *)1104150528;
  v4 = Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER;
  ptQTask[44].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[44].tQTaskRefList.ptTail = nullptr;
  ptQTask[46].tQTaskChildren.ptTail = nullptr;
  ptQTask[46].tQTaskRefList.ptHead = nullptr;
  LOBYTE(ptQTask[46].tQTaskRefList.ptMiddle) = 0;
  BYTE1(ptQTask[46].tQTaskRefList.ptMiddle) = 0;
  ptQTask[46].tQTaskRefList.ptTail = nullptr;
  *(_DWORD *)&ptQTask[48].eQTaskType = 0;
  ptQTask[49].ptNext = (struct QTask_s *)-1;
  ptQTask[49].ptPrev = (struct QTask_s *)-1;
  ptQTask[49].tQTaskChildren.ptHead = nullptr;
  if ( v4 )
  {
    LOBYTE(ptQTask[29].tQTaskRefList.ptHead) = 1;
    BYTE1(ptQTask[29].tQTaskRefList.ptHead) = 0;
  }
  else
  {
    LOBYTE(ptQTask[29].tQTaskRefList.ptHead) = 0;
    BYTE1(ptQTask[29].tQTaskRefList.ptHead) = 1;
  }
  ptQTask[10].ptNext = nullptr;
  ptQTask[10].ptPrev = nullptr;
  ptQTask[10].tQTaskChildren.ptHead = nullptr;
  ptQTask[10].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[10].tQTaskChildren.ptTail = nullptr;
  ptQTask[10].tQTaskRefList.ptHead = nullptr;
  ptQTask[10].tQTaskRefList.ptMiddle = nullptr;
  LOBYTE(ptQTask[10].ptParent) = 0;
  strcpy((char *)&ptQTask[11].tQTaskChildren, "005_01_1");
  ptQTask[10].tQTaskRefList.ptTail = (struct QReference_s *)-1;
  ptQTask[11].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[46].ptParent = (struct QTask_s *)-1;
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
      v7 = -1;
      goto LABEL_17;
    }
  }
  v7 = v5;
LABEL_17:
  v8 = QTask_NewFn(ptQTask, Weapon_eQTaskType, nullptr);
  v8[16].tQTaskRefList.ptTail = (struct QReference_s *)v7;
  ptQTask[33].ptNext = v8;
  Weapon_SetHumanOperator(v8, ptQTask);
  v4 = ptQTask[33].ptNext == nullptr;
  BYTE1(ptQTask[33].tQTaskChildren.ptHead) = 0;
  BYTE2(ptQTask[33].tQTaskChildren.ptHead) = 0;
  HIBYTE(ptQTask[33].tQTaskChildren.ptHead) = 0;
  LOBYTE(ptQTask[33].tQTaskChildren.ptHead) = 1;
  ptQTask[33].tQTaskChildren.ptMiddle = (struct QTask_s *)1065353216;
  if ( !v4 )
  {
    for ( i = 0; i < HumanPlayer_tAmmoLimit.nAmmoLimit; ++i )
    {
      AmmoTypeFromID = AmmoType_GetAmmoTypeFromID(HumanPlayer_tAmmoLimit.atAmmoLimit[i].nAmmoID);
      AmmoTypeItemFromAmmoType = Weapon_GetAmmoTypeItemFromAmmoType(
                                   ptQTask[33].ptNext,
                                   AmmoTypeFromID->zAmmoTypeScriptID);
      if ( AmmoTypeItemFromAmmoType )
      {
        nMaxAmmo = HumanPlayer_tAmmoLimit.atAmmoLimit[i].nMaxAmmo;
        AmmoTypeItemFromAmmoType->nAmmoLimit = nMaxAmmo;
        if ( nMaxAmmo != -1 )
        {
          nAmmoCount = AmmoTypeItemFromAmmoType->nAmmoCount;
          if ( nAmmoCount >= 0 )
          {
            if ( nAmmoCount > nMaxAmmo )
              AmmoTypeItemFromAmmoType->nAmmoCount = nMaxAmmo;
          }
          else
          {
            AmmoTypeItemFromAmmoType->nAmmoCount = 0;
          }
        }
      }
    }
  }
  p_tTexInfo = &Human_ptShadow->tTexInfo;
  ptQTask[33].tQTaskChildren.ptTail = nullptr;
  ptQTask[47].ptNext = Shadow_New(
                         ptQTask,
                         (struct real64x3_t *)&ptQTask[47].tQTaskChildren,
                         (enum bool *)&ptQTask[47].eQTaskType,
                         (enum bool *)&ptQTask[48].tQTaskChildren,
                         (float *)&ptQTask[48].tQTaskChildren.ptTail,
                         (struct real32x3_t *)&ptQTask[48].tQTaskRefList,
                         40960.0,
                         1843.199951171875,
                         p_tTexInfo);
  ptQTask[48].ptNext = nullptr;
  ptQTask[48].tQTaskChildren.ptHead = nullptr;
  ptQTask[47].ptParent = nullptr;
  ptQTask[48].ptParent = nullptr;
  LOBYTE(ptQTask[46].eQTaskType) = 0;
  *(_DWORD *)&ptQTask[47].eQTaskType = 1;
  LOBYTE(ptQTask[49].tQTaskChildren.ptMiddle) = 0;
  BYTE1(ptQTask[50].ptNext) = 0;
  LOBYTE(ptQTask[50].ptNext) = 1;
  ptQTask[49].tQTaskRefList.ptMiddle = (struct QReference_s *)1065353216;
  ptQTask[49].tQTaskChildren.ptTail = nullptr;
  ptQTask[49].ptParent = (struct QTask_s *)1065353216;
  ptQTask[44].ptPrev = nullptr;
  ptQTask[44].tQTaskChildren.ptHead = nullptr;
  ptQTask[45].tQTaskChildren.ptTail = (struct QTask_s *)1065353216;
  ptQTask[45].tQTaskRefList.ptHead = nullptr;
  ptQTask[45].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[45].tQTaskRefList.ptTail = nullptr;
  ptQTask[45].ptParent = (struct QTask_s *)1065353216;
  *(_DWORD *)&ptQTask[45].eQTaskType = 0;
  ptQTask[46].ptNext = nullptr;
  ptQTask[46].ptPrev = nullptr;
  ptQTask[46].tQTaskChildren.ptHead = (struct QTask_s *)1065353216;
  ptQTask[46].tQTaskChildren.ptMiddle = nullptr;
  eDifficultyLevel = (struct QTask_s *)Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eDifficultyLevel;
  v15 = Game_iMissionID;
  ptQTask[12].tQTaskChildren.ptTail = nullptr;
  ptQTask[12].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[12].tQTaskChildren.ptHead = nullptr;
  ptQTask[12].ptPrev = nullptr;
  ptQTask[12].ptNext = nullptr;
  ptQTask[12].tQTaskRefList.ptHead = nullptr;
  ptQTask[12].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[12].tQTaskRefList.ptTail = nullptr;
  ptQTask[11].ptParent = eDifficultyLevel;
  *(_DWORD *)&ptQTask[11].eQTaskType = v15;
  ptQTask[49].tQTaskRefList.ptHead = nullptr;
  ptQTask[49].tQTaskRefList.ptTail = (struct QReference_s *)1145883853;
  ptQTask[50].ptParent = nullptr;
  *(_DWORD *)&ptQTask[50].eQTaskType = 0;
  ptQTask[51].ptNext = (struct QTask_s *)1065353216;
  LOBYTE(ptQTask[50].ptPrev) = 15;
  ptQTask[51].ptPrev = nullptr;
  ptQTask[51].tQTaskChildren.ptHead = nullptr;
  ptQTask[51].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[51].tQTaskChildren.ptTail = nullptr;
  ptQTask[51].tQTaskRefList.ptHead = nullptr;
  ptQTask[51].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[51].ptParent = nullptr;
  LOBYTE(ptQTask[74].ptPrev) = 0;
  LOBYTE(ptQTask[74].tQTaskChildren.ptHead) = 0;
  ptQTask[74].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[74].tQTaskChildren.ptTail = nullptr;
}

// source: j/0/human/human.c:1682  [anchor-mhash]
void __cdecl Human_KilledByYouHandler(struct QTask_s *ptQTask, void *pxContext)
{
  int v2; // edx

  v2 = *(_DWORD *)pxContext;
  if ( QTask_IsQTaskTypeDerived(*(_WORD *)(*(_DWORD *)pxContext + 36), Human_eQTaskType) )
  {
    if ( ptQTask[10].tQTaskRefList.ptTail != *(struct QReference_s **)(v2 + 428) )
      ++*(int *)&ptQTask[12].tQTaskChildren.ptHead;
  }
}

// source: j/0/human/human.c:1711  [anchor-mhash]
void __cdecl Human_HitByYouHandler(struct QTask_s *ptQTask, void *pxContext)
{
  int v2; // edx

  v2 = *(_DWORD *)pxContext;
  if ( QTask_IsQTaskTypeDerived(*(_WORD *)(*(_DWORD *)pxContext + 36), Human_eQTaskType) == false
    || ptQTask[10].tQTaskRefList.ptTail != *(struct QReference_s **)(v2 + 428) )
  {
    ++*(int *)&ptQTask[12].tQTaskChildren.ptMiddle;
  }
}

// source: j/0/human/human.c:1740  [anchor-mhash]
void __cdecl Human_MaintainCough(struct Human_s *ptHuman)
{
  int v1; // eax
  struct QTask_s *v2; // edi
  struct QReference_s *v3; // eax

  if ( LOBYTE(ptHuman->ptSectorQTask) )
  {
    v1 = *((_DWORD *)&ptHuman->ptSectorQTask + 1);
    if ( !v1 || !*(_DWORD *)(v1 + 8) )
    {
      v2 = SoundSys_NewSoundFn(ptHuman->ptHumanViewQTask, "cough");
      v3 = *((struct QReference_s **)&ptHuman->ptSectorQTask + 1);
      if ( v3 )
      {
        QReference_Delete(v3, &QTask_tQTaskRefPool);
        *((_DWORD *)&ptHuman->ptSectorQTask + 1) = 0;
      }
      if ( v2 )
        *((_DWORD *)&ptHuman->ptSectorQTask + 1) = QTask_NewQTaskRef(v2);
    }
  }
  LOBYTE(ptHuman->ptSectorQTask) = 0;
}

// source: j/0/human/human.c:1765  [anchor-mhash]
void __cdecl Human_SmokeAreaHandler(struct QTask_s *ptQTask, void *pxContext)
{
  double v2; // st3
  float tReal32x3; // [esp+0h] [ebp-Ch]
  float tReal32x3_4; // [esp+4h] [ebp-8h]

  tReal32x3 = *(double *)&ptQTask[1].ptNext - *(double *)pxContext;
  tReal32x3_4 = *(double *)&ptQTask[1].tQTaskChildren.ptHead - *((double *)pxContext + 1);
  v2 = *(double *)&ptQTask[1].tQTaskChildren.ptTail - *((double *)pxContext + 2);
  if ( sqrt(tReal32x3 * tReal32x3 + tReal32x3_4 * tReal32x3_4 + v2 * v2) <= *((float *)pxContext + 6) )
    LOBYTE(ptQTask[74].tQTaskChildren.ptHead) = 1;
}

// source: j/0/human/human.c:1790  [anchor-caller]
void __cdecl Human_RunHandler(struct QTask_s *ptQTask)
{
  struct NetMission_t *v1; // eax
  struct QTask_s *ptBombComputerHighlightQTask; // eax
  struct QTask_s *ptTail; // eax
  double v4; // st7
  struct QReference_s *v5; // eax
  struct QTask_s *ptNext; // eax
  struct GameTexture_s *v7; // edx
  struct QTask_s *v8; // eax
  struct QTask_s *v9; // eax
  double v10; // st7

  if ( Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER )
  {
    v1 = NetMission_ptNetMission;
    qmemcpy((char *)&ptQTask[52] + 24 * (Flow_ptFlow->nTicks % 30), &ptQTask[1], 0x18u);
    if ( v1 )
    {
      if ( v1->ptBombComputerHighlightQTask && Weapon_IsWeaponSelectable(ptQTask[33].ptNext, "WEAPON_ID_C4BOMB") )
      {
        if ( NetMission_ptNetMission )
          ptBombComputerHighlightQTask = NetMission_ptNetMission->ptBombComputerHighlightQTask;
        else
          ptBombComputerHighlightQTask = nullptr;
        qmemcpy(&ptBombComputerHighlightQTask[1], &ptQTask[1], 0x18u);
        *(double *)&ptBombComputerHighlightQTask[1].tQTaskChildren.ptTail = *(double *)&ptBombComputerHighlightQTask[1].tQTaskChildren.ptTail
                                                                          + 8192.0;
      }
    }
  }
  ptTail = ptQTask[49].tQTaskChildren.ptTail;
  if ( ptTail )
  {
    v4 = *(float *)&ptQTask[51].ptPrev * 0.800000011920929;
    ptQTask[49].tQTaskChildren.ptTail = (struct QTask_s *)((char *)ptTail - 1);
    *(float *)&ptQTask[51].ptPrev = v4;
    *(float *)&ptQTask[51].tQTaskChildren.ptHead = *(float *)&ptQTask[51].tQTaskChildren.ptHead * 0.800000011920929;
    *(float *)&ptQTask[51].tQTaskChildren.ptMiddle = *(float *)&ptQTask[51].tQTaskChildren.ptMiddle * 0.800000011920929;
  }
  else
  {
    ptQTask[51].ptPrev = nullptr;
    ptQTask[51].tQTaskChildren.ptHead = nullptr;
    ptQTask[51].tQTaskChildren.ptMiddle = nullptr;
  }
  if ( !*(_DWORD *)&ptQTask[2].eQTaskType )
    LOBYTE(ptQTask[46].eQTaskType) = 1;
  if ( LOBYTE(ptQTask[46].eQTaskType) )
  {
    QTask_Delete(ptQTask);
  }
  else
  {
    if ( BYTE1(ptQTask[29].tQTaskRefList.ptHead) )
    {
      v5 = (struct QReference_s *)((char *)&ptQTask[12].tQTaskRefList.ptHead->ptNext + 1);
      ++*(int *)&ptQTask[49].tQTaskRefList.ptHead;
      ptQTask[12].tQTaskRefList.ptHead = v5;
    }
    if ( LOBYTE(ptQTask[29].tQTaskRefList.ptHead) && !HIBYTE(ptQTask[50].ptNext) && BYTE2(ptQTask[50].ptNext) )
    {
      if ( Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.isBlood )
      {
        if ( !ptQTask[48].ptPrev )
        {
          ptNext = ptQTask[47].ptNext;
          v7 = Human_ptBloodPuddle;
          ptQTask[48].ptNext = (struct QTask_s *)1;
          *(_DWORD *)&ptQTask[47].eQTaskType = 1;
          ptNext[3].tQTaskChildren.ptMiddle = (struct QTask_s *)&v7->tTexInfo;
          v8 = ptQTask[47].ptNext;
          v8[2].ptNext = ptQTask[49].ptParent;
          v8[7].ptParent = (struct QTask_s *)1;
          v9 = ptQTask[47].ptNext;
          v10 = *(float *)&v9[1].ptParent;
          v9[1].tQTaskRefList.ptTail = nullptr;
          *(float *)&v9[1].eQTaskType = v10 * 0.006666666828095913;
        }
      }
      HIBYTE(ptQTask[50].ptNext) = 1;
    }
    ptQTask[47].ptParent = nullptr;
    Human_MaintainCough((struct Human_s *)ptQTask);
    ((void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[1][BoneDynCubeObj_eQTaskType].pfHandler)(ptQTask);
  }
}

// source: j/0/human/human.c:1937  [anchor-caller]
void __cdecl Human_DeleteHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *v1; // ebp
  struct QTaskList_s *v2; // ebx
  struct QReference_s *ptMiddle; // eax
  int v4; // esi
  struct QReference_s *v5; // eax
  struct QReference_s *ptTail; // eax
  struct QReference_s *ptHead; // eax
  struct QReference_s *v8; // eax
  struct QReference_s *v9; // eax
  struct QReference_s *v10; // eax
  int v11; // ecx
  struct QReference_s *v12; // eax
  void (__cdecl *pfHandler)(struct QTask_s *); // eax

  v1 = ptQTask;
  QTask_DeleteQTaskAndQTaskRefSafe((struct QReference_s **)&ptQTask[74].tQTaskChildren.ptMiddle);
  v1[34].tQTaskChildren.ptTail = nullptr;
  v1[34].tQTaskRefList.ptHead = nullptr;
  v1[35].ptNext = nullptr;
  v1[35].ptPrev = nullptr;
  v1[35].tQTaskChildren.ptHead = nullptr;
  v1[34].tQTaskRefList.ptMiddle = nullptr;
  v1[34].tQTaskRefList.ptTail = nullptr;
  v1[34].ptParent = nullptr;
  *(_DWORD *)&v1[34].eQTaskType = 0;
  HumanAnim_DeInit(v1);
  BoneDynCubeObj_SetLODVirModel((struct BoneDynCubeObj_s *)v1, nullptr);
  QTaskList_Remove(GameFunctions_ptExplosionQTaskList, v1);
  QTaskList_RemoveSafe(Human_ptQTaskList, v1);
  v2 = AIDetection_ptDetectionQTaskList;
  if ( QTaskList_IsQTaskRegistered(AIDetection_ptDetectionQTaskList, (int *)&ptQTask, v1) )
    QTaskList_Remove(v2, v1);
  HumanCamera_RemoveHumanFromCameraList(v1);
  ptMiddle = v1[11].tQTaskRefList.ptMiddle;
  if ( ptMiddle )
  {
    v4 = *(_DWORD *)((unsigned int)&ptMiddle[-1].pxObject & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v4);
    memset(*(void **)(v4 + 8), 0xCDu, *(_DWORD *)(v4 + 16));
    free((void *)v4);
    v1[11].tQTaskRefList.ptMiddle = nullptr;
  }
  v5 = v1[44].tQTaskRefList.ptMiddle;
  if ( v5 )
    QReference_Delete(v5, &QTask_tQTaskRefPool);
  ptTail = (struct QReference_s *)v1[46].tQTaskChildren.ptTail;
  if ( ptTail )
    QReference_Delete(ptTail, &QTask_tQTaskRefPool);
  ptHead = v1[46].tQTaskRefList.ptHead;
  if ( ptHead )
    QReference_Delete(ptHead, &QTask_tQTaskRefPool);
  v8 = (struct QReference_s *)v1[29].tQTaskChildren.ptMiddle;
  if ( v8 )
    QReference_Delete(v8, &QTask_tQTaskRefPool);
  v9 = (struct QReference_s *)v1[29].tQTaskChildren.ptTail;
  if ( v9 )
    QReference_Delete(v9, &QTask_tQTaskRefPool);
  v10 = *(struct QReference_s **)&v1[48].eQTaskType;
  if ( v10 )
    QReference_Delete(v10, &QTask_tQTaskRefPool);
  v11 = 0;
  while ( 1 )
  {
    v12 = Level_atLevelQTaskID[v11];
    if ( v12 )
    {
      if ( v12->pxObject == v1 )
        break;
    }
    if ( ++v11 >= 4096 )
      return;
  }
  if ( v11 >= 0 )
  {
    pfHandler = (void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[Level_eRemoveLevelScriptSymbolsEvent][v1->eQTaskType].pfHandler;
    if ( pfHandler )
      pfHandler(v1);
  }
}

// source: j/0/human/human.c:2032  [anchor-mhash]
void __cdecl Human_GetClosestVertexHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QReference_s *ptHumanCameraQTaskRef; // eax
  struct QTask_s *pxObject; // eax

  ptHumanCameraQTaskRef = Game_ptGame->ptHumanCameraQTaskRef;
  if ( ptHumanCameraQTaskRef )
    pxObject = (struct QTask_s *)ptHumanCameraQTaskRef->pxObject;
  else
    pxObject = nullptr;
  if ( ViewportQTask_ptActiveViewportQTask[2].tQTaskChildren.ptHead[2].tQTaskChildren.ptHead != pxObject
    || pxObject[2].ptParent->tQTaskChildren.ptHead != ptQTask
    || pxObject[6].ptNext != (struct QTask_s *)1 )
  {
    ((void (__cdecl *)())QTask_aatQTaskFinalEvent[QCube_eGetClosestVertexQTaskEvent][BoneDynCubeObj_eQTaskType].pfHandler)(ptQTask, pxContext);
  }
}

// source: j/0/human/human.c:2073  [anchor-mhash]
void __cdecl Human_GetShadowInfoHandler(struct QTask_s *ptQTask, void *pxData)
{
  _DWORD *v2; // eax
  struct QTask_s *ptTail; // edi
  BOOL v4; // ecx
  bool v5; // zf
  long double v6; // st7
  struct real64x3_t a1; // [esp+10h] [ebp-18h] BYREF

  v2 = pxData;
  ptTail = ptQTask[74].tQTaskChildren.ptTail;
  *((_DWORD *)pxData + 4) = ptQTask;
  if ( *(_DWORD *)&ptQTask[32].eQTaskType == 2 )
  {
    *((_DWORD *)pxData + 3) = 0;
    *(_DWORD *)&ptQTask[47].eQTaskType = 0;
  }
  else if ( ptTail )
  {
    *((_DWORD *)pxData + 3) = 0;
    *(_DWORD *)&ptQTask[47].eQTaskType = !ptQTask[48].ptNext || HIBYTE(ptQTask[50].ptNext) && !ptQTask[48].ptPrev;
  }
  else
  {
    v4 = HIBYTE(ptQTask[50].ptNext) && !ptQTask[48].ptPrev;
    *(_DWORD *)&ptQTask[47].eQTaskType = v4;
    v5 = *((_DWORD *)pxData + 2) == 0;
    *((_DWORD *)pxData + 3) = 1;
    if ( !v5 )
    {
      if ( !ptQTask[47].ptParent )
      {
        qmemcpy(&a1, &ptQTask[1], sizeof(a1));
        a1.vZ = a1.vZ + 7372.8;
        v6 = sub_5C5840(&a1, Game_ptGame->ptWorld, 204800.0);
        v2 = pxData;
        *(float *)&ptQTask[48].tQTaskChildren.ptMiddle = v6 + 6144.0;
      }
      v2[1] = ptQTask[48].tQTaskChildren.ptMiddle;
    }
  }
}

// source: j/0/human/human.c:2127  [anchor-caller]
void __cdecl Human_EnterHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct QTask_s *v30; };
    struct { char igi2_o1[4]; struct Dirlight_s *ptDirlight; };
    struct { char igi2_o2[8]; enum bool pisTotallyInside; };
    struct { char igi2_o3[12]; struct real32x2_t tDisplayAreaMax; };
    struct { char igi2_o4[20]; struct QTask_s *ptHead; };
    struct { char igi2_o5[24]; struct QTask_s *ptTail; };
    struct { char igi2_o6[28]; struct Dirlight_s *v36; };
    struct { char igi2_o7[32]; struct real32x3_t ptDir; };
    struct { char igi2_o8[44]; struct Ambientlight_t ptAmbientlight; };
    struct { char igi2_o9[56]; _BYTE v39[40]; };
    char igi2_extent[96];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *v2; // ebx
  struct QReference_s *ptHumanCameraQTaskRef; // eax
  struct QTask_s *pxObject; // edx
  float vX; // ebp
  struct Dirlight_s *v6; // esi
  struct Client_s *ClientFromHumanQTask; // esi
  struct Client_s *v8; // eax
  struct QTask_s *ptParent; // eax
  struct QTask_s *v10; // eax
  struct QTask_s *v11; // edi
  struct QTask_s *ptPrev; // eax
  int i; // esi
  struct real32x2_t *v14; // eax
  enum bool v15; // eax
  struct QTask_s *v16; // ecx
  unsigned int *p_nAllocated; // edi
  int v18; // esi
  void ***p_papxElement; // ebp
  struct real32x2_t *v20; // eax
  enum bool v21; // eax
  bool v22; // cc
  double v23; // st7
  double v24; // st7
  double v25; // st6
  float v26; // eax
  float v27; // edx
  struct Dirlight_s *v28; // eax
  struct QTask_s *v29; // eax

  v2 = ptQTask;
  igi2_frame.ptTail = ptQTask[33].tQTaskChildren.ptTail;
  ptHumanCameraQTaskRef = Game_ptGame->ptHumanCameraQTaskRef;
  if ( ptHumanCameraQTaskRef )
  {
    pxObject = (struct QTask_s *)ptHumanCameraQTaskRef->pxObject;
    igi2_frame.v30 = pxObject;
  }
  else
  {
    igi2_frame.v30 = nullptr;
    pxObject = nullptr;
  }
  vX = RenderContext_tActiveRenderContext.tDisplayAreaMin.vX;
  igi2_frame.ptHead = ViewportQTask_ptActiveViewportQTask[2].tQTaskChildren.ptHead;
  igi2_frame.ptDir.vY = RenderContext_tActiveRenderContext.tDisplayAreaMin.vY;
  igi2_frame.tDisplayAreaMax = RenderContext_tActiveRenderContext.tDisplayAreaMax;
  igi2_frame.pisTotallyInside = false;
  igi2_frame.v36 = nullptr;
  v6 = SkyDome_ptDirlight;
  igi2_frame.ptDir.vX = RenderContext_tActiveRenderContext.tDisplayAreaMin.vX;
  ptQTask = (struct QTask_s *)1;
  igi2_frame.ptDirlight = SkyDome_ptDirlight;
  if ( Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER && HumanPlayer_ptQTask )
  {
    ClientFromHumanQTask = NetManager_GetClientFromHumanQTask(HumanPlayer_ptQTask);
    v8 = NetManager_GetClientFromHumanQTask(v2);
    if ( v8 != ClientFromHumanQTask
      && ClientFromHumanQTask->ptHumanQTaskRef
      && ClientFromHumanQTask->eNetworkIDSpectate == v8->eNetworkID )
    {
      return;
    }
    v6 = igi2_frame.ptDirlight;
    pxObject = igi2_frame.v30;
  }
  ptParent = pxObject[2].ptParent;
  if ( !ptParent
    || igi2_frame.ptHead[2].tQTaskChildren.ptHead == pxObject
    && ptParent->tQTaskChildren.ptHead == v2
    && pxObject[6].ptNext == (struct QTask_s *)1 )
  {
    if ( !igi2_frame.ptTail || !LOBYTE(igi2_frame.ptTail[10].ptNext) || !BYTE1(igi2_frame.ptTail[10].ptNext) )
      return;
    goto LABEL_39;
  }
  if ( (QCube_ptInsideSectorObject || ModelObj_vLODBias > 0.0)
    && ((v10 = v2[48].ptParent) != nullptr && !v10[725].ptParent || v2->eQTaskType == HumanRemote_eQTaskType)
    && v2[7].ptPrev
    && !isInfraEnabled )
  {
    v11 = v2[74].tQTaskChildren.ptTail;
    if ( v11 )
    {
      if ( !v11[9].ptParent )
        return;
      ptPrev = v11[8].ptPrev;
      for ( i = 0; i < (int)(*(_DWORD *)&ptPrev->eQTaskType); ++i )
      {
        v14 = *((struct real32x2_t **)&ptPrev[1].tQTaskChildren.ptHead->ptNext + i);
        RenderContext_tActiveRenderContext.tDisplayAreaMin = *v14;
        RenderContext_tActiveRenderContext.tDisplayAreaMax = v14[1];
        ++RenderContext_nActiveRenderContextTimeStamp;
        v15 = BoneDynCubeObj_Exclude((struct BoneDynCubeObj_s *)v2, &igi2_frame.pisTotallyInside);
        v16 = (struct QTask_s *)(v15 & (unsigned int)ptQTask);
        ptPrev = v11[8].ptPrev;
        ptQTask = v16;
      }
      v6 = igi2_frame.ptDirlight;
      RenderContext_tActiveRenderContext.tDisplayAreaMax = igi2_frame.tDisplayAreaMax;
      RenderContext_tActiveRenderContext.tDisplayAreaMin.vX = vX;
      RenderContext_tActiveRenderContext.tDisplayAreaMin.vY = igi2_frame.ptDir.vY;
      ++RenderContext_nActiveRenderContextTimeStamp;
      goto LABEL_34;
    }
    if ( Clipping_tClipData.tClipWindows.ptClipWindowsList )
    {
      p_nAllocated = &Clipping_tClipData.tClipWindows.ptClipWindowsList->nAllocated;
      v18 = 0;
      if ( (int)Clipping_tClipData.tClipWindows.ptClipWindowsList->nAllocated > 0 )
      {
        p_papxElement = &Clipping_tClipData.tClipWindows.ptClipWindowsList->papxElement;
        do
        {
          v20 = (struct real32x2_t *)(*p_papxElement)[v18];
          RenderContext_tActiveRenderContext.tDisplayAreaMin = *v20;
          RenderContext_tActiveRenderContext.tDisplayAreaMax = v20[1];
          ++RenderContext_nActiveRenderContextTimeStamp;
          v21 = BoneDynCubeObj_Exclude((struct BoneDynCubeObj_s *)v2, &igi2_frame.pisTotallyInside);
          v22 = ++v18 < (int)*p_nAllocated;
          ptQTask = (struct QTask_s *)(v21 & (unsigned int)ptQTask);
        }
        while ( v22 );
        vX = igi2_frame.ptDir.vX;
      }
      v6 = igi2_frame.ptDirlight;
      RenderContext_tActiveRenderContext.tDisplayAreaMax = igi2_frame.tDisplayAreaMax;
      RenderContext_tActiveRenderContext.tDisplayAreaMin.vX = vX;
      RenderContext_tActiveRenderContext.tDisplayAreaMin.vY = igi2_frame.ptDir.vY;
      ++RenderContext_nActiveRenderContextTimeStamp;
      goto LABEL_34;
    }
    if ( QCube_ptInsideSectorObject )
      return;
  }
  *(float *)&ptQTask = COERCE_FLOAT(BoneDynCubeObj_Exclude((struct BoneDynCubeObj_s *)v2, &igi2_frame.pisTotallyInside));
LABEL_34:
  if ( *(float *)&ptQTask != 0.0 )
    return;
  pxObject = igi2_frame.v30;
LABEL_39:
  v2[46].ptParent = (struct QTask_s *)Flow_ptFlow->nTicksDrawn;
  if ( v6 )
  {
    igi2_frame.ptAmbientlight = (*(struct Ambientlight_t *)&Mesh3D_atAmbientColor[1]);
    igi2_frame.tDisplayAreaMax.vX = (Mesh3D_atAmbientColor[1].vZ + Mesh3D_atAmbientColor[1].vY + Mesh3D_atAmbientColor[1].vX)
                       * 0.3333333432674408;
    v23 = (v6->tFrontColor.vY + v6->tFrontColor.vZ + v6->tFrontColor.vX) * 0.1666666716337204;
    *(float *)&ptQTask = v23;
    if ( v23 > 0.0 && (v24 = (*(float *)&v2[49].ptParent - igi2_frame.tDisplayAreaMax.vX) / *(float *)&ptQTask, v24 >= 0.0) )
    {
      if ( v24 > 1.0 )
        v24 = 1.0;
    }
    else
    {
      v24 = 0.0;
    }
    v25 = *(float *)&v2[49].ptParent - *(float *)&ptQTask * v24 - igi2_frame.tDisplayAreaMax.vX;
    if ( v25 > 0.0 )
    {
      igi2_frame.ptAmbientlight.tColor.vX = igi2_frame.ptAmbientlight.tColor.vX + v25;
      igi2_frame.ptAmbientlight.tColor.vY = igi2_frame.ptAmbientlight.tColor.vY + v25;
      igi2_frame.ptAmbientlight.tColor.vZ = v25 + igi2_frame.ptAmbientlight.tColor.vZ;
      if ( igi2_frame.ptAmbientlight.tColor.vX >= 0.0 )
      {
        if ( igi2_frame.ptAmbientlight.tColor.vX > 1.0 )
          igi2_frame.ptAmbientlight.tColor.vX = 1.0;
      }
      else
      {
        igi2_frame.ptAmbientlight.tColor.vX = 0.0;
      }
      if ( igi2_frame.ptAmbientlight.tColor.vY >= 0.0 )
      {
        if ( igi2_frame.ptAmbientlight.tColor.vY > 1.0 )
          igi2_frame.ptAmbientlight.tColor.vY = 1.0;
      }
      else
      {
        igi2_frame.ptAmbientlight.tColor.vY = 0.0;
      }
      if ( igi2_frame.ptAmbientlight.tColor.vZ >= 0.0 )
      {
        if ( igi2_frame.ptAmbientlight.tColor.vZ > 1.0 )
          igi2_frame.ptAmbientlight.tColor.vZ = 1.0;
      }
      else
      {
        igi2_frame.ptAmbientlight.tColor.vZ = 0.0;
      }
    }
    qmemcpy(igi2_frame.v39, v6, sizeof(igi2_frame.v39));
    v6 = igi2_frame.ptDirlight;
    igi2_frame.ptDirlight->tFrontColor.vX = v24 * igi2_frame.ptDirlight->tFrontColor.vX;
    igi2_frame.ptDirlight->tFrontColor.vY = v24 * igi2_frame.ptDirlight->tFrontColor.vY;
    igi2_frame.ptDirlight->tFrontColor.vZ = v24 * igi2_frame.ptDirlight->tFrontColor.vZ;
    Lightsource_UpdateDirlight(igi2_frame.ptDirlight);
    Lightsource_SetAmbientlight(&igi2_frame.ptAmbientlight);
    pxObject = igi2_frame.v30;
  }
  if ( *(float *)&v2[51].ptPrev != 0.0 )
  {
    v26 = *(float *)&v2[3].tQTaskRefList.ptHead;
    LODWORD(igi2_frame.ptDir.vX) = v2[3].tQTaskChildren.ptHead;
    v27 = *(float *)&v2[3].ptParent;
    igi2_frame.ptDir.vY = v26;
    igi2_frame.ptDir.vZ = v27;
    v28 = Lightsource_NewDirlight(
            &igi2_frame.ptDir,
            (struct real32x3_t *)&v2[51].ptPrev,
            (struct real32x3_t *)&v2[51].ptPrev,
            0,
            1);
    pxObject = igi2_frame.v30;
    igi2_frame.v36 = v28;
  }
  v29 = pxObject[2].ptParent;
  ptQTask = (struct QTask_s *)1;
  if ( !v29
    || igi2_frame.ptHead[2].tQTaskChildren.ptHead == pxObject
    && v29->tQTaskChildren.ptHead == v2
    && pxObject[6].ptNext == (struct QTask_s *)1 )
  {
    if ( igi2_frame.ptTail && LOBYTE(igi2_frame.ptTail[10].ptNext) && BYTE1(igi2_frame.ptTail[10].ptNext) )
      ((void (__cdecl *)(struct QTask_s *, struct QTask_s **))QTask_aatQTaskFinalEvent[5][HumanView_eQTaskType].pfHandler)(
        igi2_frame.ptTail,
        &ptQTask);
  }
  else
  {
    ((void (__cdecl *)(struct QTask_s *, struct QTask_s **))QTask_aatQTaskFinalEvent[5][BoneDynCubeObj_eQTaskType].pfHandler)(
      v2,
      &ptQTask);
  }
  if ( v6 )
  {
    qmemcpy(igi2_frame.ptDirlight, igi2_frame.v39, sizeof(struct Dirlight_s));
    Lightsource_UpdateDirlight(igi2_frame.ptDirlight);
    igi2_frame.ptAmbientlight = (*(struct Ambientlight_t *)&Mesh3D_atAmbientColor[1]);
    Lightsource_SetAmbientlight(&igi2_frame.ptAmbientlight);
  }
  if ( igi2_frame.v36 )
    Lightsource_DeleteDirlight(igi2_frame.v36);
}

// source: j/0/human/human.c:2483  [anchor-mhash]
void __cdecl Human_TraceLinesHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { float ptDynCubeObj; };
    struct { float ptDynCubeObja; };
    struct { char igi2_o2[24]; struct real64x3_t tOldPos; };
    struct { char igi2_o3[48]; struct real64x3_t tPos; };
    char igi2_extent[72];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v2; // kr00_4
  __int16 v3; // ax
  void (__cdecl *pfHandler)(struct QTask_s *, _DWORD); // eax
  int nTicks; // eax
  int v6; // edx
  struct QTask_s *v7; // esi

  if ( Game_eGameMode != GAME_GAMEMODE_MULTIPLAYER
    || Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle
    || Human_nFireTimeStamp <= 0 )
  {
    ((void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[10][BoneDynCubeObj_eQTaskType].pfHandler)(
      ptQTask,
      pxContext);
  }
  else
  {
    v2 = NetManager_GetTimer() - Human_nFireTimeStamp;
    v3 = *((_WORD *)pxContext + 6);
    if ( v3 == 512
      || (pfHandler = (void (__cdecl *)(struct QTask_s *, _DWORD))QTask_aatQTaskFinalEvent[v3][ptQTask->eQTaskType].pfHandler) == nullptr
      || (pfHandler(ptQTask, *((_DWORD *)pxContext + 4)), **((_BYTE **)pxContext + 4)) )
    {
      nTicks = Flow_ptFlow->nTicks;
      qmemcpy(&igi2_frame.tPos, &ptQTask[1], sizeof(igi2_frame.tPos));
      v6 = nTicks % 30 - v2 / 30 + (nTicks % 30 - v2 / 30 < 0 ? 0x1E : 0);
      if ( v6 <= 0 || v6 >= 30 )
        v7 = ptQTask + 1;
      else
        v7 = (struct QTask_s *)((char *)ptQTask + 24 * v6 + 2080);
      qmemcpy(&igi2_frame.tOldPos, v7, sizeof(igi2_frame.tOldPos));
      igi2_frame.ptDynCubeObj = BoneDynCubeObj_GetRadius((struct BoneDynCubeObj_s *)ptQTask);
      World_MoveDynCubeObjRadius(Game_ptGame->ptWorld, (struct DynCubeObj_s *)ptQTask, &igi2_frame.tOldPos, igi2_frame.ptDynCubeObj);
      ((void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[10][BoneDynCubeObj_eQTaskType].pfHandler)(
        ptQTask,
        pxContext);
      igi2_frame.ptDynCubeObja = BoneDynCubeObj_GetRadius((struct BoneDynCubeObj_s *)ptQTask);
      World_MoveDynCubeObjRadius(Game_ptGame->ptWorld, (struct DynCubeObj_s *)ptQTask, &igi2_frame.tPos, igi2_frame.ptDynCubeObja);
    }
  }
}

// source: j/0/human/human.c:2581  [anchor-mhash]
void __cdecl Human_LineOfSightHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *ptTail; // ecx
  __int16 v3; // ax
  void (__cdecl *pfHandler)(struct QTask_s *, _DWORD); // eax

  ptTail = ptQTask[33].tQTaskChildren.ptTail;
  v3 = *((_WORD *)pxContext + 4);
  if ( v3 == 512 )
  {
    if ( LOBYTE(ptQTask[33].tQTaskRefList.ptMiddle)
      || ptQTask[33].tQTaskRefList.ptHead != (struct QReference_s *)1
      || !ptTail
      || !LOBYTE(ptTail[10].ptNext)
      || !BYTE1(ptTail[10].ptNext) )
    {
      goto LABEL_10;
    }
  }
  else
  {
    pfHandler = (void (__cdecl *)(struct QTask_s *, _DWORD))QTask_aatQTaskFinalEvent[v3][ptQTask->eQTaskType].pfHandler;
    if ( !pfHandler || (pfHandler(ptQTask, *((_DWORD *)pxContext + 3)), **((_BYTE **)pxContext + 3)) )
LABEL_10:
      ((void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[9][BoneDynCubeObj_eQTaskType].pfHandler)(
        ptQTask,
        pxContext);
  }
}

// source: j/0/human/human.c:2634  [size]
void __cdecl Human_WeaponGetParentParametersHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { float ptDest; };
    struct { char igi2_o1[4]; float vAlpha; };
    struct { char igi2_o2[8]; float vBeta; };
    struct { char igi2_o3[28]; struct real64x3_t tRotation; };
    struct { char igi2_o4[52]; struct real64x3_t ptSpeed; };
    char igi2_extent[76];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  DWORD PerformanceCounter; // eax
  int v3; // eax
  DWORD TickCount; // eax

  if ( QTask_IsQTaskTypeDerived(ptQTask->eQTaskType, HumanRemote_eQTaskType) )
  {
    if ( Timer_isPerformanceCounter )
      Timer_GetPerformanceCounter();
    else
      GetTickCount();
    if ( Timer_isPerformanceCounter )
      PerformanceCounter = Timer_GetPerformanceCounter();
    else
      PerformanceCounter = GetTickCount();
    Spline_ExtraFromEnd(
      (struct real64x3_t *)pxContext,
      &igi2_frame.tRotation,
      (struct Spline_s *)&ptQTask[74].tQTaskRefList.ptMiddle,
      PerformanceCounter - Timer_nStartTime);
    v3 = *(_DWORD *)&ptQTask[32].eQTaskType;
    if ( v3 )
    {
      if ( v3 == 1 )
      {
        *((_DWORD *)pxContext + 4) = 0;
        *((_DWORD *)pxContext + 5) = 1085276160;
      }
    }
    else
    {
      *((double *)pxContext + 2) = *((double *)pxContext + 2) + 6922.240234375;
    }
    if ( Timer_isPerformanceCounter )
      TickCount = Timer_GetPerformanceCounter();
    else
      TickCount = GetTickCount();
    Spline_ExtraFromEnd(
      &igi2_frame.tRotation,
      &igi2_frame.ptSpeed,
      (struct Spline_s *)&ptQTask[77].tQTaskChildren,
      TickCount - Timer_nStartTime);
    igi2_frame.vBeta = igi2_frame.tRotation.vZ;
    igi2_frame.vAlpha = igi2_frame.tRotation.vY;
    igi2_frame.ptDest = igi2_frame.tRotation.vX;
    Real32x9_Create((struct real32x9_t *)((char *)pxContext + 24), igi2_frame.ptDest, igi2_frame.vAlpha, igi2_frame.vBeta);
  }
  else
  {
    qmemcpy(pxContext, &ptQTask[33].tQTaskChildren.ptTail[10].tQTaskChildren, 0x18u);
    qmemcpy((char *)pxContext + 24, &ptQTask[33].tQTaskChildren.ptTail[10].ptParent, 0x28u);
  }
}

// source: j/0/human/human.c:2778  [size]
void __cdecl Human_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = Human_ptParameterList;
}

// source: j/0/human/human.c:2794  [anchor-caller]
void __cdecl Human_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *v2; // ebx
  struct real64x3_t *v3; // ebp
  long double v4; // st7
  struct Game_s *v5; // edx
  long double v6; // st7
  long double v7; // st6
  __int16 v8; // cx
  struct QTask_s *v9; // eax
  int v10; // edx
  struct QTask_s *v11; // edi
  float ptDynCubeObj; // [esp+0h] [ebp-14h]

  v2 = ptQTask;
  v3 = (struct real64x3_t *)&ptQTask[10];
  Human_UpdateModel((struct Human_s *)ptQTask);
  if ( v2[33].tQTaskChildren.ptTail )
    QTask_Delete(v2[33].tQTaskChildren.ptTail);
  ptQTask = (struct QTask_s *)((char *)v2 + 448);
  v2[33].tQTaskChildren.ptTail = QTask_NewFn(v2, HumanView_eQTaskType, &ptQTask);
  v4 = *(float *)&v3[1].vX;
  v2[34].tQTaskChildren.ptHead = (struct QTask_s *)LODWORD(v3[1].vX);
  v5 = Game_ptGame;
  *(float *)&v2[34].ptPrev = v4;
  v2[3].tQTaskChildren.ptMiddle = nullptr;
  *(float *)&ptQTask = v4;
  v2[3].tQTaskRefList.ptMiddle = nullptr;
  v6 = sin(v4);
  v2[3].tQTaskRefList.ptTail = nullptr;
  v2[3].ptParent = nullptr;
  v2[4].ptNext = nullptr;
  *(_DWORD *)&v2[3].eQTaskType = 1065353216;
  v7 = cos(*(float *)&ptQTask);
  *(float *)&v2[3].ptPrev = v7;
  *(float *)&v2[3].tQTaskChildren.ptHead = -v6;
  *(float *)&v2[3].tQTaskChildren.ptTail = v6;
  *(float *)&v2[3].tQTaskRefList.ptHead = v7;
  ptDynCubeObj = sqrt(
                   *(float *)&v2[7].tQTaskChildren.ptTail * *(float *)&v2[7].tQTaskChildren.ptTail
                 + *(float *)&v2[7].tQTaskRefList.ptHead * *(float *)&v2[7].tQTaskRefList.ptHead
                 + *(float *)&v2[7].tQTaskRefList.ptMiddle * *(float *)&v2[7].tQTaskRefList.ptMiddle)
               + *(float *)&v2[8].ptNext;
  World_MoveDynCubeObjRadius(v5->ptWorld, (struct DynCubeObj_s *)v2, v3, ptDynCubeObj);
  v8 = Attach_eAttachEvent;
  v2[5].tQTaskChildren.ptTail = (struct QTask_s *)-1;
  v2[5].tQTaskRefList.ptHead = nullptr;
  QTask_TriggerQTaskEventParent(v2, v8, &v2[5].tQTaskChildren.ptTail);
  ModelObj_CalcRelativePosAndOrientation((struct ModelObj_s *)v2);
  v9 = v2 + 52;
  v10 = 30;
  do
  {
    v11 = v9;
    v9 = (struct QTask_s *)((char *)v9 + 24);
    --v10;
    qmemcpy(v11, v3, 0x18u);
  }
  while ( v10 );
  v2[47].ptParent = nullptr;
}

// source: j/0/human/human.c:2846  [anchor-mhash]
void __cdecl Human_UpdateInternalDataAfterCarryoverHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptNext; // eax

  if ( ptQTask[11].tQTaskRefList.ptMiddle )
  {
    ptNext = ptQTask[33].ptNext;
    if ( ptNext )
    {
      Script_SetSymbolContext("Human_AddWeapon", ptNext);
      Script_SetSymbolContext("Human_AddAmmo", ptQTask[33].ptNext);
      Script_SetSymbolContext("Human_AddAmmoForWeapon", ptQTask[33].ptNext);
      Script_ParseLineInt32((char *)ptQTask[11].tQTaskRefList.ptMiddle);
      Script_SetSymbolContext("Human_AddAmmoForWeapon", nullptr);
      Script_SetSymbolContext("Human_AddWeapon", nullptr);
      Script_SetSymbolContext("Human_AddAmmo", nullptr);
    }
  }
}

// source: j/0/human/human.c:2875  [size]
void __cdecl Human_EvaluateCollisionHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_BYTE *)pxContext = 0;
}

// source: j/0/human/human.c:2891  [size]
void __cdecl Humam_NodeLinkCheckHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_BYTE *)pxContext = 0;
}

// source: j/0/human/human.c:2907  [anchor-mhash]
void __cdecl Human_WeaponCollisionEvaluateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { char v18; };
    struct { char igi2_o1[1]; char zWhizzbySound[32]; };
    struct { char igi2_o2[33]; char zTemp[32]; };
    char igi2_extent[65];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct Game_s *v2; // esi
  struct QTask_s *v3; // ebx
  struct LevelFlow_s *v4; // edi
  unsigned int v5; // ecx
  unsigned int v6; // ebx
  int v7; // eax
  int v8; // ebx
  unsigned int v9; // eax
  char *v10; // edi
  char *v12; // edi
  char *v13; // esi
  char v14; // cl
  struct Game_s *v15; // eax
  struct QReference_s *v16; // eax
  struct QTask_s *pxObject; // ecx

  v2 = Game_ptGame;
  if ( ptQTask == *((struct QTask_s **)pxContext + 1) )
    goto LABEL_13;
  if ( ptQTask == *((struct QTask_s **)pxContext + 2) )
    goto LABEL_13;
  v3 = *((struct QTask_s **)pxContext + 3);
  if ( ptQTask == v3 )
    goto LABEL_13;
  if ( Game_eGameMode )
  {
    if ( !v3 || QTask_IsQTaskTypeDerived(v3->eQTaskType, Human_eQTaskType) )
      goto LABEL_12;
  }
  else if ( Human_IsPlayer(ptQTask) == false )
  {
    if ( v3 && v3[10].tQTaskRefList.ptTail == ptQTask[10].tQTaskRefList.ptTail )
    {
      *(_BYTE *)pxContext = 0;
      return;
    }
    goto LABEL_12;
  }
  if ( Random_GetRandomNumberReal32(&v2->tRunRandomState) > (double)*((float *)pxContext + 4) )
  {
LABEL_13:
    *(_BYTE *)pxContext = 0;
    goto LABEL_14;
  }
LABEL_12:
  *(_BYTE *)pxContext = 1;
LABEL_14:
  if ( HumanPlayer_ptQTask == ptQTask
    && *((struct QTask_s **)pxContext + 2) != ptQTask
    && *((struct QTask_s **)pxContext + 3) != ptQTask )
  {
    v4 = LevelFlow_ptLevelFlow;
    strcpy(igi2_frame.zWhizzbySound, "whizzby_");
    memset(&igi2_frame.zWhizzbySound[9], 0, 23);
    if ( (double)(LevelFlow_ptLevelFlow->nTick - dword_79EE1C4) >= 15.0
      || Random_GetRandomNumberReal32(&v2->tRunRandomState) >= 0.5 )
    {
      v5 = v2->tRunRandomState.anRandom[0];
      v6 = v2->tRunRandomState.anRandom[1];
      dword_79EE1C4 = v4->nTick;
      v7 = (v5 >> 7) ^ v2->tRunRandomState.anRandom[2];
      v8 = v7 ^ v6;
      v2->tRunRandomState.anRandom[2] = v7;
      v2->tRunRandomState.anRandom[1] = v8;
      v2->tRunRandomState.anRandom[0] = v8 + v5;
      sprintf(igi2_frame.zTemp, "%02i", (v8 + v5) % 0xC);
      v9 = strlen(igi2_frame.zTemp) + 1;
      v10 = &igi2_frame.v18;
      while ( *++v10 )
        ;
      qmemcpy(v10, igi2_frame.zTemp, 4 * (v9 >> 2));
      v13 = &igi2_frame.zTemp[4 * (v9 >> 2)];
      v12 = &v10[4 * (v9 >> 2)];
      v14 = v9;
      v15 = Game_ptGame;
      qmemcpy(v12, v13, v14 & 3);
      v16 = v15->aptPlayerQTaskRef[2];
      pxObject = nullptr;
      if ( v16 )
        pxObject = (struct QTask_s *)v16->pxObject;
      if ( ptQTask == pxObject )
        SoundSys_NewSoundFn(ptQTask[33].tQTaskChildren.ptTail, igi2_frame.zWhizzbySound);
      else
        SoundSys_NewSoundFn(ptQTask, igi2_frame.zWhizzbySound);
    }
  }
}

// source: j/0/human/human.c:3019  [size]
void __cdecl Human_ObjectCollisionEvaluateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_BYTE *)pxContext = 0;
}

// source: j/0/human/human.c:3039  [size]
void __cdecl Human_Particle2DCollisionEvaluateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_BYTE *)pxContext = 0;
}

// source: j/0/human/human.c:3059  [anchor-mhash]
void __cdecl Human_ExplosionHitHandler(struct QTask_s *ptQTask, void *pxContext)
{
  double v2; // st7
  double v3; // st7
  int v4; // esi
  float ptExplosionHitContext; // [esp+0h] [ebp-10h]

  if ( BYTE1(ptQTask[29].tQTaskRefList.ptHead) )
  {
    ptQTask[29].tQTaskChildren.ptHead = (struct QTask_s *)13;
    ptExplosionHitContext = (sqrt(
                               *(float *)&ptQTask[7].tQTaskChildren.ptTail * *(float *)&ptQTask[7].tQTaskChildren.ptTail
                             + *(float *)&ptQTask[7].tQTaskRefList.ptHead * *(float *)&ptQTask[7].tQTaskRefList.ptHead
                             + *(float *)&ptQTask[7].tQTaskRefList.ptMiddle
                             * *(float *)&ptQTask[7].tQTaskRefList.ptMiddle)
                           + *(float *)&ptQTask[8].ptNext)
                          * 0.3333333432674408;
    v2 = GameFunctions_ResolveExplosionHit(
           (struct ExplosionHitContext_t *)pxContext,
           ptQTask,
           (struct real64x3_t *)&ptQTask[1],
           ptExplosionHitContext,
           true);
    if ( v2 != 0.0 )
    {
      v3 = v2 * *(float *)&ptQTask[28].tQTaskRefList.ptHead;
      *(float *)&ptQTask[28].tQTaskChildren.ptTail = v3 + *(float *)&ptQTask[28].tQTaskChildren.ptTail;
      *(float *)&ptQTask[25].tQTaskRefList.ptHead = v3 + *(float *)&ptQTask[25].tQTaskRefList.ptHead;
      v4 = *(_DWORD *)&ptQTask[30].eQTaskType;
      Human_UpdateDie((struct Human_s *)ptQTask);
      *(_DWORD *)&ptQTask[30].eQTaskType = v4;
    }
  }
}

// source: j/0/human/human.c:3149  [anchor-mhash]
void __cdecl Human_DeathZoneHitTestHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { _DWORD v12[2]; };
    struct { char igi2_o1[8]; double v13; };
    struct { char igi2_o2[16]; double v14; };
    struct { char igi2_o3[24]; int v15; };
    struct { char igi2_o4[28]; int v16; };
    struct { char igi2_o5[32]; int v17; };
    struct { char igi2_o6[36]; char *v18; };
    struct { char igi2_o7[40]; double v19[3]; };
    struct { char igi2_o8[64]; double a2[3]; };
    struct { char igi2_o9[88]; char v21; };
    struct { char igi2_o10[168]; int v22; };
    struct { char igi2_o11[172]; int v23; };
    struct { char igi2_o12[180]; int v24; };
    char igi2_extent[208];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v2; // edx
  char v3; // al
  double v4; // st6
  double v5; // st6
  int *v6; // eax
  int v7; // eax
  double v8; // st5
  float *v9; // eax
  double v10; // st7
  struct QTask_s *ptParent; // eax

  sub_580CA0((int)ptQTask, igi2_frame.a2);
  v2 = *(_DWORD *)pxContext;
  v3 = BYTE1(ptQTask[29].tQTaskRefList.ptHead);
  qmemcpy(igi2_frame.v19, (void *)(*(_DWORD *)pxContext + 40), sizeof(igi2_frame.v19));
  igi2_frame.v13 = igi2_frame.v19[1] - igi2_frame.a2[1];
  igi2_frame.v14 = igi2_frame.v19[2] - igi2_frame.a2[2];
  if ( v3 )
  {
    v4 = *(float *)(v2 + 248) <= (double)*(float *)(v2 + 252) ? *(float *)(v2 + 252) : *(float *)(v2 + 248);
    if ( v4 >= *(float *)(v2 + 244) )
      v5 = *(float *)(v2 + 248) <= (double)*(float *)(v2 + 252) ? *(float *)(v2 + 252) : *(float *)(v2 + 248);
    else
      v5 = *(float *)(v2 + 244);
    v6 = *(int **)(v2 + 116);
    if ( v6 && (v7 = *v6) != 0 )
      v8 = *(float *)(*(_DWORD *)(*(_DWORD *)(v7 + 12) + 12) + 120);
    else
      v8 = 1.0;
    if ( sqrt(igi2_frame.v13 * igi2_frame.v13 + igi2_frame.v14 * igi2_frame.v14 + (igi2_frame.v19[0] - igi2_frame.a2[0]) * (igi2_frame.v19[0] - igi2_frame.a2[0])) <= v5 * v8 )
    {
      igi2_frame.v12[0] = igi2_frame.a2;
      igi2_frame.v18 = &igi2_frame.v21;
      igi2_frame.v12[1] = igi2_frame.v19;
      WORD2(igi2_frame.v13) = 512;
      igi2_frame.v14 = 0.0;
      LODWORD(igi2_frame.v13) = 1;
      igi2_frame.v16 = 0;
      igi2_frame.v15 = 0;
      igi2_frame.v17 = 1094861636;
      igi2_frame.v24 = 0;
      igi2_frame.v22 = 0;
      igi2_frame.v23 = 0;
      ((void (__cdecl *)(int, _DWORD *))QTask_aatQTaskFinalEvent[10][RigidDynCubeObj_eQTaskType].pfHandler)(v2, igi2_frame.v12);
      if ( !igi2_frame.v24 || igi2_frame.v23 )
      {
        v9 = *((float **)pxContext + 1);
        if ( sqrt(*v9 * *v9 + v9[1] * v9[1] + v9[2] * v9[2]) >= 50.0 )
          v10 = 10000.0;
        else
          v10 = 0.0;
        ptQTask[29].tQTaskChildren.ptHead = (struct QTask_s *)13;
        ptParent = ptQTask[48].ptParent;
        if ( !ptParent || !BYTE1(ptParent[111].tQTaskChildren.ptMiddle) )
        {
          *(float *)&ptQTask[28].tQTaskChildren.ptTail = v10 + *(float *)&ptQTask[28].tQTaskChildren.ptTail;
          *(float *)&ptQTask[25].tQTaskRefList.ptHead = v10 + *(float *)&ptQTask[25].tQTaskRefList.ptHead;
          Human_UpdateDie((struct Human_s *)ptQTask);
        }
      }
    }
  }
}

// source: j/0/human/human.c:3285  [size~]
void __cdecl Human_GetHumanCameraInfoHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { float ptDynCubeObj; };
    struct { float ptDynCubeObja; };
    struct { char igi2_o2[16]; struct QTask_s *ptTail; };
    struct { char igi2_o3[20]; struct real64x3_t ptPos; };
    struct { char igi2_o4[44]; struct real64x3_t ptNewPos; };
    char igi2_extent[68];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QReference_s *ptHead; // eax

  igi2_frame.ptTail = ptQTask[33].tQTaskChildren.ptTail;
  if ( Flow_ptFlow->isDrawInterpolateFrame )
  {
    if ( QTask_IsQTaskTypeDerived(ptQTask->eQTaskType, HumanRemote_eQTaskType) )
    {
      HumanRemote_MoveInWorld((struct HumanRemote_t *)ptQTask);
      ModelObj_UpdateAttachments((struct ModelObj_s *)ptQTask);
      HumanView_UpdateView(ptQTask[33].tQTaskChildren.ptTail, ptQTask);
      HumanView_UpdateBody(ptQTask[33].tQTaskChildren.ptTail, ptQTask, false);
    }
    if ( QTask_IsQTaskTypeDerived(ptQTask->eQTaskType, HumanPlayer_eQTaskType) )
    {
      qmemcpy(&igi2_frame.ptNewPos, &ptQTask[1], sizeof(igi2_frame.ptNewPos));
      HumanPlayer_ExtrapolatePos((struct Human_s *)ptQTask, &igi2_frame.ptPos);
      igi2_frame.ptDynCubeObj = sqrt(
                       *(float *)&ptQTask[7].tQTaskChildren.ptTail * *(float *)&ptQTask[7].tQTaskChildren.ptTail
                     + *(float *)&ptQTask[7].tQTaskRefList.ptHead * *(float *)&ptQTask[7].tQTaskRefList.ptHead
                     + *(float *)&ptQTask[7].tQTaskRefList.ptMiddle * *(float *)&ptQTask[7].tQTaskRefList.ptMiddle)
                   + *(float *)&ptQTask[8].ptNext;
      World_MoveDynCubeObjRadius(Game_ptGame->ptWorld, (struct DynCubeObj_s *)ptQTask, &igi2_frame.ptPos, igi2_frame.ptDynCubeObj);
      Human_UpdateBody(ptQTask);
      HumanView_UpdateView(ptQTask[33].tQTaskChildren.ptTail, ptQTask);
      HumanPlayer_CheckViewCollision((struct HumanPlayer_t *)ptQTask);
      HumanView_UpdateBody(ptQTask[33].tQTaskChildren.ptTail, ptQTask, false);
      igi2_frame.ptDynCubeObja = sqrt(
                        *(float *)&ptQTask[7].tQTaskChildren.ptTail * *(float *)&ptQTask[7].tQTaskChildren.ptTail
                      + *(float *)&ptQTask[7].tQTaskRefList.ptHead * *(float *)&ptQTask[7].tQTaskRefList.ptHead
                      + *(float *)&ptQTask[7].tQTaskRefList.ptMiddle * *(float *)&ptQTask[7].tQTaskRefList.ptMiddle)
                    + *(float *)&ptQTask[8].ptNext;
      World_MoveDynCubeObjRadius(Game_ptGame->ptWorld, (struct DynCubeObj_s *)ptQTask, &igi2_frame.ptNewPos, igi2_frame.ptDynCubeObja);
    }
  }
  qmemcpy(pxContext, &ptQTask[33].tQTaskChildren.ptTail[10].tQTaskChildren, 0x18u);
  qmemcpy((char *)pxContext + 24, &ptQTask[33].tQTaskChildren.ptTail[10].ptParent, 0x28u);
  *((_DWORD *)pxContext + 16) = igi2_frame.ptTail[16].tQTaskChildren.ptHead;
  qmemcpy((char *)pxContext + 68, &ptQTask[3].ptPrev, 0x28u);
  *((_DWORD *)pxContext + 27) = igi2_frame.ptTail[16].tQTaskRefList.ptHead;
  *((_DWORD *)pxContext + 28) = ptQTask[33].tQTaskRefList.ptHead;
  if ( *(float *)&ptQTask[21].tQTaskChildren.ptMiddle != 0.0 && *(float *)&ptQTask[15].ptNext == 0.0 )
    LOBYTE(ptQTask[33].tQTaskRefList.ptMiddle) ^= 1u;
  ptHead = ptQTask[33].tQTaskRefList.ptHead;
  if ( ptHead == (struct QReference_s *)3 || ptHead == (struct QReference_s *)5 )
    sub_580CA0((int)ptQTask, (double *)pxContext);
  if ( LOBYTE(ptQTask[33].tQTaskRefList.ptMiddle) )
  {
    *((_DWORD *)pxContext + 28) = 2;
  }
  else if ( BYTE2(igi2_frame.ptTail[12].tQTaskRefList.ptTail) )
  {
    qmemcpy(pxContext, &igi2_frame.ptTail[12].ptParent, 0x18u);
    qmemcpy((char *)pxContext + 24, &igi2_frame.ptTail[13].tQTaskChildren.ptTail, 0x28u);
    *((_DWORD *)pxContext + 28) = 4;
  }
}

void __cdecl sub_50AAC0(struct QTask_s *a1, struct QTask_s **a2)
{
  struct QTask_s *ptHead; // esi
  __int16 v3; // ax
  struct QTask_s *v4; // ecx
  int v5; // edx
  void (__cdecl *pfHandler)(struct QTask_s *, struct QTask_s **); // ecx

  if ( a1 != a2[8] || a1 != a2[9] )
  {
    ptHead = a1->tQTaskChildren.ptHead;
    if ( ptHead->ptNext )
    {
      if ( ptHead )
      {
        v3 = HumanAI_eSendEventQTaskEvent;
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
            v3 = QTask_NewQTaskEventFn(0, "HumanAISendEvent");
            HumanAI_eSendEventQTaskEvent = v3;
          }
          pfHandler = (void (__cdecl *)(struct QTask_s *, struct QTask_s **))QTask_aatQTaskFinalEvent[v3][ptHead->eQTaskType].pfHandler;
          if ( pfHandler )
          {
            pfHandler(ptHead, a2);
            v3 = HumanAI_eSendEventQTaskEvent;
          }
          ptHead = (struct QTask_s *)dword_849C7DC[QTask_nProtectedQTaskStackOffset--];
        }
        while ( ptHead );
      }
    }
  }
}

// source: j/0/human/human.c:3437  [anchor-caller]
void __cdecl Human_AIDetectionGetInfoHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct real64x3_t *OriginalViewPosition; // eax
  double v3; // st7

  *(_DWORD *)pxContext = Human_bAIDetectionQTaskMask;
  *((_DWORD *)pxContext + 20) = ptQTask[10].tQTaskRefList.ptTail;
  *((_BYTE *)pxContext + 84) = LOBYTE(ptQTask[29].tQTaskRefList.ptHead) == 0;
  *((_BYTE *)pxContext + 85) = BYTE1(ptQTask[29].tQTaskRefList.ptHead);
  OriginalViewPosition = HumanView_GetOriginalViewPosition((struct real64x3_t *)((char *)pxContext + 8), ptQTask);
  qmemcpy((char *)pxContext + 56, &ptQTask[1], 0x18u);
  v3 = *((double *)pxContext + 9) + 409.6000061035156;
  *((double *)pxContext + 9) = v3;
  *((double *)pxContext + 4) = (OriginalViewPosition->vX + *((double *)pxContext + 7)) * 0.5;
  *((double *)pxContext + 5) = (*((double *)pxContext + 8) + *((double *)pxContext + 2)) * 0.5;
  *((double *)pxContext + 6) = (v3 + *((double *)pxContext + 3)) * 0.5;
}

// source: j/0/human/human.c:3475  [size]
void __cdecl Human_AIDetectionLineOfSightHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_BYTE *)pxContext = *((struct QTask_s **)pxContext + 2) != ptQTask && *((struct QTask_s **)pxContext + 3) != ptQTask;
}

// source: j/0/human/human.c:3500  [anchor-mhash]
void __cdecl Human_AICheckFirePathHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct real64x3_t tDelta; };
    struct { char igi2_o1[24]; struct real64x3_t Real64x3_RotateInverse_tTemp; };
    char igi2_extent[48];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  double *v2; // eax
  double v3; // st6
  double v4; // st5
  float *v5; // eax
  long double v6; // st7
  unsigned int vY_low; // ecx

  if ( *(struct QTask_s **)pxContext != ptQTask
    && *((struct QReference_s **)pxContext + 12) == ptQTask[10].tQTaskRefList.ptTail )
  {
    v2 = *((double **)pxContext + 1);
    igi2_frame.tDelta.vX = *(double *)&ptQTask[1].ptNext - *v2;
    v3 = *(double *)&ptQTask[1].tQTaskChildren.ptHead - v2[1];
    v4 = *(double *)&ptQTask[1].tQTaskChildren.ptTail - v2[2];
    v5 = *((float **)pxContext + 2);
    igi2_frame.tDelta.vZ = v4;
    igi2_frame.Real64x3_RotateInverse_tTemp.vX = v5[6] * v4 + v5[3] * v3 + *v5 * igi2_frame.tDelta.vX;
    igi2_frame.Real64x3_RotateInverse_tTemp.vY = v5[7] * v4 + v5[4] * v3 + v5[1] * igi2_frame.tDelta.vX;
    igi2_frame.Real64x3_RotateInverse_tTemp.vZ = v5[8] * v4 + v5[5] * v3 + v5[2] * igi2_frame.tDelta.vX;
    qmemcpy(&igi2_frame.tDelta, &igi2_frame.Real64x3_RotateInverse_tTemp, sizeof(igi2_frame.tDelta));
    igi2_frame.tDelta.vY = 0.0;
    v6 = sqrt(igi2_frame.tDelta.vZ * igi2_frame.tDelta.vZ + igi2_frame.tDelta.vX * igi2_frame.tDelta.vX);
    if ( *((double *)pxContext + 2) < 0.0 || v6 < *((double *)pxContext + 2) )
    {
      vY_low = LODWORD(igi2_frame.Real64x3_RotateInverse_tTemp.vY);
      *((long double *)pxContext + 2) = v6;
      *(_QWORD *)&igi2_frame.tDelta.vY = __PAIR64__(HIDWORD(igi2_frame.Real64x3_RotateInverse_tTemp.vY), vY_low);
      qmemcpy((char *)pxContext + 24, &igi2_frame.tDelta, 0x18u);
    }
  }
}

// source: j/0/human/human.c:3552  [anchor-caller]
void __cdecl Human_AmmoPickupHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct AmmoType_s *AmmoTypeFromID; // eax
  struct AmmoTypeItem_s *AmmoTypeItemFromAmmoType; // eax
  int v4; // edi
  int nAmmoLimit; // ecx

  if ( ptQTask[33].ptNext && (!LOBYTE(ptQTask[29].tQTaskRefList.ptHead) || *((_DWORD *)pxContext + 2)) )
  {
    AmmoTypeFromID = AmmoType_GetAmmoTypeFromID(*(_DWORD *)pxContext);
    AmmoTypeItemFromAmmoType = Weapon_GetAmmoTypeItemFromAmmoType(ptQTask[33].ptNext, AmmoTypeFromID->zAmmoTypeScriptID);
    if ( AmmoTypeItemFromAmmoType )
    {
      v4 = *((_DWORD *)pxContext + 1) + AmmoTypeItemFromAmmoType->nAmmoCount;
      nAmmoLimit = AmmoTypeItemFromAmmoType->nAmmoLimit;
      AmmoTypeItemFromAmmoType->nAmmoCount = v4;
      if ( nAmmoLimit != -1 )
      {
        if ( v4 < 0 )
        {
          AmmoTypeItemFromAmmoType->nAmmoCount = 0;
          Human_PlaySound((struct Human_s *)ptQTask, "weaponpickup_1", (struct real64x3_t *)&ptQTask[1]);
          return;
        }
        if ( v4 > nAmmoLimit )
          AmmoTypeItemFromAmmoType->nAmmoCount = nAmmoLimit;
      }
    }
    Human_PlaySound((struct Human_s *)ptQTask, "weaponpickup_1", (struct real64x3_t *)&ptQTask[1]);
  }
}

struct QTask_s *__cdecl sub_50ADD0(
        int a1,
        struct WeaponType_s *ptWeaponType,
        int *anAmmoCount,
        int ltcg_arg7)
{
  #pragma pack(push, 1)
  union
  {
    struct { float pvBeta; };
    struct { char igi2_o1[4]; float pvAlpha; };
    struct { char igi2_o2[8]; float ptSource[17]; };
    struct { char igi2_o3[76]; struct real32x9_t ptPos; };
    char igi2_extent[116];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *v4; // ebx

  if ( !ptWeaponType )
    return nullptr;
  v4 = *(struct QTask_s **)(a1 + 32);
  HumanAnim_GetWeaponPositionAndOrientation(v4, (struct real64x3_t *)&igi2_frame.ptSource[1], &igi2_frame.ptPos);
  qmemcpy(&igi2_frame.ptSource[7], &v4[3].ptPrev, 0x28u);
  Real32x9_GetAngles((struct real32x9_t *)&igi2_frame.ptSource[7], igi2_frame.ptSource, &igi2_frame.pvAlpha, &igi2_frame.pvBeta);
  return GunPickup_New(
           ptWeaponType,
           (struct real64x3_t *)&igi2_frame.ptSource[1],
           &igi2_frame.ptPos,
           igi2_frame.pvBeta,
           true,
           1,
           anAmmoCount,
           ltcg_arg7);
}

// source: j/0/human/human.c:3596  [anchor-caller]
struct QTask_s *__cdecl Human_CreateGunPickupFromGameDifficulty(
        struct QTask_s *ptWeaponQTask,
        struct WeaponType_s *ptWeaponType)
{
  #pragma pack(push, 1)
  union
  {
    struct { int *v6; };
    struct { char igi2_o1[16]; int anAmmoCount[2]; };
    char igi2_extent[24];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  enum GameDifficulty_e eDifficultyLevel; // eax
  __int32 v3; // eax
  BOOL v4; // ecx

  if ( 2752 * Config_tConfig.iActiveProfile == -7392072 )
    return nullptr;
  eDifficultyLevel = Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eDifficultyLevel;
  if ( eDifficultyLevel )
  {
    v3 = eDifficultyLevel - 1;
    if ( v3 )
    {
      if ( v3 == 1 )
        igi2_frame.anAmmoCount[0] = 1061997773;
      else
        igi2_frame.anAmmoCount[0] = 0;
    }
    else
    {
      igi2_frame.anAmmoCount[0] = 1063675494;
    }
  }
  else
  {
    igi2_frame.anAmmoCount[0] = 1065353216;
  }
  WeaponType_CalcGunPickupAmmo(igi2_frame.anAmmoCount, ptWeaponType, *(float *)igi2_frame.anAmmoCount);
  v4 = ptWeaponType->eWeaponCategory == WEAPONCATEGORY_GRENADE;
  igi2_frame.v6 = (int *)igi2_frame.anAmmoCount[0];
  igi2_frame.anAmmoCount[1] = 1;
  igi2_frame.anAmmoCount[0] = v4;
  return sub_50ADD0((int)ptWeaponQTask, ptWeaponType, igi2_frame.v6, (int)igi2_frame.anAmmoCount);
}

// source: j/0/human/human.c:3653  [anchor-caller]
void __cdecl Human_PickupGun(
        struct QTask_s *ptQTask,
        struct WeaponType_s *ptWeaponType,
        struct GunPickupContext_t *ptGunPickupContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { _DWORD v16[10]; };
    struct { char igi2_o1[40]; char Buffer[256]; };
    char igi2_extent[296];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *v3; // edi
  struct Client_s *ClientFromHumanQTask; // esi
  struct Client_s *ClientFromNetworkID; // eax
  enum TextScrollerColour_e v6; // ecx
  char *v7; // esi
  char *LocalizedString; // eax
  _DWORD *v9; // edi
  int *anAmmoForFiretype; // esi
  int v11; // ebx
  struct AmmoTypeItem_s *AmmoTypeItemFromAmmoType; // eax
  int v13; // ecx
  int nAmmoLimit; // edx
  enum WeaponCategory_e eWeaponCategory; // eax

  v3 = ptQTask;
  if ( Weapon_EnableWeaponType(ptQTask[33].ptNext, ptWeaponType->zWeaponScriptID, false) )
  {
    if ( Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER
      && ptGunPickupContext->iWeaponID == Script_ParseLineInt32("WEAPON_ID_C4BOMB") )
    {
      ClientFromHumanQTask = NetManager_GetClientFromHumanQTask(ptQTask);
      ClientFromNetworkID = NetManager_GetClientFromNetworkID((int)Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle);
      if ( !ClientFromNetworkID || ClientFromNetworkID->eTeam != NetMission_eAttackingTeam )
        goto LABEL_8;
      Config_SetLocalizedPhrase(igi2_frame.Buffer, "mp/BOMB_PICKED_UP", ClientFromHumanQTask->zPlayerName, nullptr, nullptr);
      v6 = TEXTSCROLLER_COLOUR_YELLOW;
      v7 = igi2_frame.Buffer;
    }
    else
    {
      if ( ptQTask != HumanPlayer_ptQTask )
        goto LABEL_9;
      sprintf(igi2_frame.Buffer, "PICKEDUPWEAPON%s", ptWeaponType->zName);
      if ( Game_eGameMode != GAME_GAMEMODE_MULTIPLAYER )
      {
        StatusMessage_New(
          Level_ptDynamicQTask,
          igi2_frame.Buffer,
          (char *)&g_zInitialValue,
          (char *)&g_zInitialValue,
          true);
        goto LABEL_9;
      }
      if ( ptWeaponType->eWeaponType == WEAPONTYPE_C4BOMB )
      {
LABEL_9:
        Weapon_SetAmmoForWeapon(
          v3[33].ptNext,
          ptWeaponType->zWeaponScriptID,
          ptGunPickupContext->nAmmoInClip,
          ptGunPickupContext->anAmmoForFiretype);
        goto LABEL_32;
      }
      LocalizedString = Config_GetLocalizedString(igi2_frame.Buffer);
      v6 = TEXTSCROLLER_COLOUR_BLUE;
      v7 = (char *)LocalizedString;
    }
    StatusScreen_ShowMessage(v7, v6);
LABEL_8:
    v3 = ptQTask;
    goto LABEL_9;
  }
  memset(igi2_frame.v16, 0, sizeof(igi2_frame.v16));
  ((void (__cdecl *)(struct WeaponType_s *, _DWORD *))QTask_aatQTaskFinalEvent[WeaponType_eGetAmmoInfoQTaskEvent][ptWeaponType->tQTask.eQTaskType].pfHandler)(
    ptWeaponType,
    igi2_frame.v16);
  v9 = &igi2_frame.v16[1];
  anAmmoForFiretype = ptGunPickupContext->anAmmoForFiretype;
  v11 = 2;
  do
  {
    if ( *v9 )
    {
      AmmoTypeItemFromAmmoType = Weapon_GetAmmoTypeItemFromAmmoType(ptQTask[33].ptNext, (char *)(*v9 + 40));
      if ( AmmoTypeItemFromAmmoType )
      {
        v13 = AmmoTypeItemFromAmmoType->nAmmoCount + *anAmmoForFiretype;
        nAmmoLimit = AmmoTypeItemFromAmmoType->nAmmoLimit;
        AmmoTypeItemFromAmmoType->nAmmoCount = v13;
        if ( nAmmoLimit != -1 )
        {
          if ( v13 >= 0 )
          {
            if ( v13 > nAmmoLimit )
              AmmoTypeItemFromAmmoType->nAmmoCount = nAmmoLimit;
          }
          else
          {
            AmmoTypeItemFromAmmoType->nAmmoCount = 0;
          }
        }
      }
    }
    v9 += 5;
    ++anAmmoForFiretype;
    --v11;
  }
  while ( v11 );
  if ( igi2_frame.v16[1] )
  {
    eWeaponCategory = ptWeaponType->eWeaponCategory;
    if ( eWeaponCategory != WEAPONCATEGORY_FLASHBANG
      && eWeaponCategory != WEAPONCATEGORY_GRENADE
      && eWeaponCategory != WEAPONCATEGORY_SMOKEGRENADE
      && eWeaponCategory != WEAPONCATEGORY_PROXIMITYMINE
      && eWeaponCategory != WEAPONCATEGORY_MEDIPACK )
    {
      Weapon_AddAmmoToAmmoType(ptQTask[33].ptNext, (char *)(igi2_frame.v16[1] + 40), ptGunPickupContext->nAmmoInClip);
    }
  }
  v3 = ptQTask;
LABEL_32:
  if ( Game_eGameMode != GAME_GAMEMODE_MULTIPLAYER
    || v3->eQTaskType != HumanRemote_eQTaskType
    || LOBYTE(v3[81].tQTaskRefList.ptTail) && !LOBYTE(v3[29].tQTaskRefList.ptHead) )
  {
    Human_PlaySound((struct Human_s *)ptQTask, "weaponpickup_1", (struct real64x3_t *)&v3[1]);
  }
}

// source: j/0/human/human.c:3740  [anchor-caller]
void __cdecl Human_GunPickupHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct WeaponType_s *WeaponTypeFromID; // eax

  WeaponTypeFromID = WeaponType_GetWeaponTypeFromID(*((_DWORD *)pxContext + 3));
  if ( ptQTask[33].ptNext && (!LOBYTE(ptQTask[29].tQTaskRefList.ptHead) || *((_DWORD *)pxContext + 5)) )
    Human_PickupGun(ptQTask, WeaponTypeFromID, (struct GunPickupContext_t *)pxContext);
}

// source: j/0/human/human.c:3772  [size]
void __cdecl Human_PhysicsObjMoveHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ;
}

// source: j/0/human/human.c:3833  [anchor-mhash]
void __cdecl Human_DrawComputerObjectHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct CollisionEvaluateContext_s ptEvalContext; };
    struct { char igi2_o1[8]; float v11; };
    struct { char igi2_o2[12]; struct real32x3_t ptRotatedPos; };
    struct { char igi2_o3[24]; struct CollisionEvaluateContext_s v13; };
    struct { char igi2_o4[32]; int v14; };
    struct { char igi2_o5[36]; struct QTask_s *v15; };
    struct { char igi2_o6[40]; double a2[3]; };
    struct { char igi2_o7[64]; struct real64x3_t ptEnd; };
    char igi2_extent[88];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v2; // eax
  int v3; // ecx
  double *v4; // eax
  double v5; // st7
  float *v6; // eax
  double v7; // st7
  double v8; // st6
  struct real64x3_t *v9; // edi

  if ( !LOBYTE(ptQTask[29].tQTaskRefList.ptHead) )
  {
    v2 = sub_580CA0((int)ptQTask, igi2_frame.a2);
    qmemcpy(&igi2_frame.ptEnd, igi2_frame.a2, sizeof(igi2_frame.ptEnd));
    igi2_frame.ptEnd.vZ = igi2_frame.a2[2] + 4096.0;
    *((_DWORD *)pxContext + 4) = v2 + 124;
    *((_DWORD *)pxContext + 3) = igi2_frame.a2;
    *((_DWORD *)pxContext + 5) = 1164338790;
    *((_DWORD *)pxContext + 7) = 3;
    v3 = *(_DWORD *)(v2 + 428);
    if ( !v3 || v3 == 2 )
      *((_DWORD *)pxContext + 8) = 3;
    else
      *((_DWORD *)pxContext + 8) = 4;
    if ( *(_BYTE *)(v2 + 1181) )
    {
      v4 = *(double **)pxContext;
      igi2_frame.ptRotatedPos.vX = igi2_frame.a2[0] - *(double *)*(_DWORD *)pxContext;
      igi2_frame.ptRotatedPos.vY = igi2_frame.a2[1] - v4[1];
      v5 = igi2_frame.a2[2] - v4[2];
      v6 = *((float **)pxContext + 1);
      igi2_frame.ptRotatedPos.vZ = v5;
      *(float *)&igi2_frame.ptEvalContext.isEvaluate = igi2_frame.ptRotatedPos.vZ * v6[6] + igi2_frame.ptRotatedPos.vY * v6[3] + igi2_frame.ptRotatedPos.vX * *v6;
      *(float *)&igi2_frame.ptEvalContext.ptQTask = igi2_frame.ptRotatedPos.vZ * v6[7] + igi2_frame.ptRotatedPos.vY * v6[4] + igi2_frame.ptRotatedPos.vX * v6[1];
      v7 = igi2_frame.ptRotatedPos.vZ * v6[8] + igi2_frame.ptRotatedPos.vY * v6[5];
      v8 = igi2_frame.ptRotatedPos.vX * v6[2];
      *(struct CollisionEvaluateContext_s *)&igi2_frame.ptRotatedPos.vX = igi2_frame.ptEvalContext;
      igi2_frame.v11 = v7 + v8;
      igi2_frame.ptRotatedPos.vZ = igi2_frame.v11;
      if ( Mesh3D_ExcludeObject(&igi2_frame.ptRotatedPos, 3686.39990234375, nullptr) == false )
      {
        v9 = *(struct real64x3_t **)pxContext;
        igi2_frame.v15 = ptQTask;
        igi2_frame.v13.ptQTask = nullptr;
        igi2_frame.v14 = 0;
        World_LineOfSight(
          Game_ptGame->ptWorld,
          v9,
          &igi2_frame.ptEnd,
          AIDetection_eLineOfSightQTaskEvent,
          &igi2_frame.v13,
          0xFFFFFFFF,
          WORLD_DYNCUBETREE_CATEGORY_ALL,
          (struct LineOfSightOutputContext_s *)&igi2_frame.ptEvalContext);
        if ( *(float *)&igi2_frame.ptEvalContext.isEvaluate != 0.0 )
          ComputerObject_DrawMarker((struct DrawComputerObjectContext_s *)pxContext);
      }
    }
  }
}

// source: j/0/human/human.c:3929  [size]
void __cdecl Human_StatusDisplayHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ;
}

// source: j/0/human/human.c:3941  [size]
void __cdecl Human_SoundUpdateParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = ptQTask + 1;
  *((_DWORD *)pxContext + 1) = (char *)ptQTask + 124;
  *((_DWORD *)pxContext + 2) = 0;
}

// source: j/0/human/human.c:3965  [anchor-caller]
void __cdecl Human_EvaluateGunShotHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { int v18; };
    struct { char igi2_o1[4]; struct real32x3_t tReal32x3; };
    struct { char igi2_o2[16]; struct real64x3_t tObjectPos; };
    struct { char igi2_o3[40]; struct HumanAIEventContext_t tEventContext; };
    struct { char igi2_o4[104]; struct real64x3_t atIntersection[32]; };
    char igi2_extent[872];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s **v2; // ebx
  int v3; // eax
  struct QTask_s *v4; // edi
  struct QTask_s *v5; // edx
  int ptTail; // esi
  unsigned __int16 eQTaskType; // ax
  int HearableIntersections; // eax
  int v9; // esi
  struct QTask_s *ptParent; // edi
  struct QTask_s *v11; // eax
  double *v12; // ecx
  double v13; // st7
  int v14; // edx
  struct QTask_s *v15; // eax
  struct QTask_s *ptHead; // eax
  __int16 v17; // ax

  v2 = (struct QTask_s **)pxContext;
  v3 = *((_DWORD *)pxContext + 2);
  v4 = ptQTask;
  if ( !v3 )
    goto LABEL_7;
  v5 = *(struct QTask_s **)(v3 + 8);
  ptTail = 1;
  if ( v5 != ptQTask )
  {
    if ( v5 && QTask_IsQTaskTypeDerived(v5->eQTaskType, Human_eQTaskType) )
      ptTail = (int)v5[10].tQTaskRefList.ptTail;
    if ( ptQTask[10].tQTaskRefList.ptTail != (struct QReference_s *)ptTail )
    {
LABEL_7:
      eQTaskType = ptQTask->eQTaskType;
      if ( eQTaskType == HumanSoldier_eQTaskType )
      {
        HumanSoldier_GetCheapHeadBonePosition(ptQTask, &igi2_frame.tReal32x3, &igi2_frame.tObjectPos);
      }
      else
      {
        if ( eQTaskType == HumanPlayer_eQTaskType )
        {
          BoneDynCubeObj_GetBonePosition(
            (struct BoneDynCubeObj_s *)&igi2_frame.tObjectPos,
            (struct real32x3_t *)ptQTask,
            (int)ptQTask[35].tQTaskRefList.ptMiddle);
          v2 = (struct QTask_s **)pxContext;
        }
        else
        {
          qmemcpy(&igi2_frame.tObjectPos, &ptQTask[1], sizeof(igi2_frame.tObjectPos));
        }
        v4 = ptQTask;
      }
      HearableIntersections = GunShot_FindHearableIntersections(igi2_frame.atIntersection, 32, *v2, &igi2_frame.tObjectPos);
      if ( HearableIntersections > 0 )
      {
        v9 = 176;
        igi2_frame.v18 = HearableIntersections;
        do
        {
          if ( QTask_IsQTaskTypeDerived(v4->eQTaskType, Human_eQTaskType) )
          {
            ptParent = v4[48].ptParent;
            if ( ptParent )
            {
              v11 = *v2;
              v12 = *(double **)((char *)&(*v2)->ptNext + v9);
              igi2_frame.tReal32x3.vX = igi2_frame.tObjectPos.vX - v12[2];
              igi2_frame.tReal32x3.vY = igi2_frame.tObjectPos.vY - v12[3];
              v13 = igi2_frame.tObjectPos.vZ - v12[4];
              igi2_frame.tReal32x3.vZ = v13;
              igi2_frame.tEventContext.eEvent = 19;
              igi2_frame.tEventContext.eTeam = 0;
              igi2_frame.tEventContext.bFlags = 1090;
              igi2_frame.tEventContext.vRadius = sqrt(igi2_frame.tReal32x3.vX * igi2_frame.tReal32x3.vX + igi2_frame.tReal32x3.vY * igi2_frame.tReal32x3.vY + v13 * v13)
                                    + 4096.0;
              v14 = *(int *)((char *)&v11->ptNext + v9);
              igi2_frame.tEventContext.ptReferenceQTask = v11;
              igi2_frame.tEventContext.tDirection.vX = igi2_frame.tReal32x3.vX;
              igi2_frame.tEventContext.tDirection.vZ = igi2_frame.tReal32x3.vZ;
              v15 = v2[2];
              igi2_frame.tEventContext.ptPosition = (struct real64x3_t *)(v14 + 16);
              igi2_frame.tEventContext.tDirection.vY = igi2_frame.tReal32x3.vY;
              if ( v15 )
              {
                ptHead = v15->tQTaskChildren.ptHead;
                igi2_frame.tEventContext.ptHumanOriginatorQTask = ptHead;
                if ( ptHead )
                  igi2_frame.tEventContext.eTeam = (int)ptHead[10].tQTaskRefList.ptTail;
              }
              else
              {
                igi2_frame.tEventContext.ptHumanOriginatorQTask = nullptr;
              }
              v17 = HumanAI_eSendEventQTaskEvent;
              if ( HumanAI_eSendEventQTaskEvent == 512 )
              {
                v17 = QTask_NewQTaskEventFn(0, "HumanAISendEvent");
                HumanAI_eSendEventQTaskEvent = v17;
              }
              ((void (__cdecl *)(struct QTask_s *, struct HumanAIEventContext_t *))QTask_aatQTaskFinalEvent[v17][ptParent->eQTaskType].pfHandler)(
                ptParent,
                &igi2_frame.tEventContext);
            }
            v4 = ptQTask;
          }
          v9 += 4;
          --igi2_frame.v18;
        }
        while ( igi2_frame.v18 );
      }
    }
  }
}

// source: j/0/human/human.c:4081  [size]
void __cdecl Human_GetGrenadeHeldTimeHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = 0;
}

// source: j/0/human/human.c:4106  [size~]
void __cdecl Human_RegisterScriptSymbolsHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { char zUniqueQTaskName[64]; };
    struct { char igi2_o1[64]; char Buffer[128]; };
    char igi2_extent[192];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)

  if ( !LOBYTE(ptQTask[49].tQTaskChildren.ptMiddle) )
  {
    LOBYTE(ptQTask[49].tQTaskChildren.ptMiddle) = 1;
    Level_GetUniqueQTaskNameFromTask(igi2_frame.zUniqueQTaskName, ptQTask);
    sprintf(igi2_frame.Buffer, "%s.isDead", igi2_frame.zUniqueQTaskName);
    Symbol_Register(
      igi2_frame.Buffer,
      (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_Int8,
      &ptQTask[29].tQTaskRefList,
      1,
      QSCRIPT_SYMBOLCLASS_VARIABLE,
      QSCRIPT_SYMBOLTYPE_INT,
      QSCRIPT_SYMBOLLIFESPAN_FINITE);
    sprintf(igi2_frame.Buffer, "%s.eTeam", igi2_frame.zUniqueQTaskName);
    Symbol_Register(
      igi2_frame.Buffer,
      (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_Int,
      &ptQTask[10].tQTaskRefList.ptTail,
      4,
      QSCRIPT_SYMBOLCLASS_VARIABLE,
      QSCRIPT_SYMBOLTYPE_INT,
      QSCRIPT_SYMBOLLIFESPAN_FINITE);
    sprintf(igi2_frame.Buffer, "%s.nSpotted", igi2_frame.zUniqueQTaskName);
    Symbol_Register(
      igi2_frame.Buffer,
      (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_Int,
      &ptQTask[12],
      4,
      QSCRIPT_SYMBOLCLASS_VARIABLE,
      QSCRIPT_SYMBOLTYPE_INT,
      QSCRIPT_SYMBOLLIFESPAN_FINITE);
  }
}

// source: j/0/human/human.c:4139  [size~]
void __cdecl Human_RemoveScriptSymbolsHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { char zUniqueQTaskName[64]; };
    struct { char igi2_o1[64]; char Buffer[128]; };
    char igi2_extent[192];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)

  if ( LOBYTE(ptQTask[49].tQTaskChildren.ptMiddle) )
  {
    Level_GetUniqueQTaskNameFromTask(igi2_frame.zUniqueQTaskName, ptQTask);
    sprintf(igi2_frame.Buffer, "%s.isDead", igi2_frame.zUniqueQTaskName);
    Symbol_Remove(igi2_frame.Buffer);
    sprintf(igi2_frame.Buffer, "%s.eTeam", igi2_frame.zUniqueQTaskName);
    Symbol_Remove(igi2_frame.Buffer);
    sprintf(igi2_frame.Buffer, "%s.nSpotted", igi2_frame.zUniqueQTaskName);
    Symbol_Remove(igi2_frame.Buffer);
    LOBYTE(ptQTask[49].tQTaskChildren.ptMiddle) = 0;
  }
}

// source: j/0/human/human.c:4174  [anchor-caller]
void __cdecl Human_RegisterDynCubeObjHandler(struct QTask_s *ptQTask, void *pxContext)
{
  int v2; // eax

  v2 = BoneDynCubeObj_eQTaskType + 511 * DynCubeObj_eDynCubeObjRegisterQTaskEvent;
  BYTE1(ptQTask[29].tQTaskRefList.ptHead) = 1;
  ((void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[0][v2].pfHandler)(ptQTask, pxContext);
  QTaskList_RegisterSafe(Human_ptQTaskList, ptQTask);
}

// source: j/0/human/human.c:4196  [anchor-caller]
void __cdecl Human_RemoveDynCubeObjHandler(struct QTask_s *ptQTask, void *pxContext)
{
  int v2; // eax

  v2 = BoneDynCubeObj_eQTaskType + 511 * DynCubeObj_eDynCubeObjRemoveQTaskEvent;
  BYTE1(ptQTask[29].tQTaskRefList.ptHead) = 0;
  ((void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[0][v2].pfHandler)(ptQTask, pxContext);
  QTaskList_RemoveSafe(Human_ptQTaskList, ptQTask);
}

// source: j/0/human/human.c:4218  [size]
void __cdecl Human_ComputerMapFollowQTaskEventHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_BYTE *)pxContext = ptQTask[10].tQTaskRefList.ptTail == (struct QReference_s *)1;
}

// source: j/0/human/human.c:4237  [anchor-mhash]
void __cdecl Human_AreaActivateTeamCB(struct AreaActivateContext_s *ptContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct QTask_s *ptTail; };
    struct { char igi2_o1[4]; struct real64x3_t ptPos; };
    char igi2_extent[28];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  enum GameMode_e v1; // edx
  struct QTask_s *ptAreaActivateQTask; // eax
  struct QReference_s *ptHead; // ebx
  int v5; // ebp
  int v6; // edi
  struct QTask_s *v7; // ecx
  struct Client_s *ClientFromHumanQTask; // eax
  int nHitCount; // eax
  struct AreaActivateContext_s *ptContexta = *(struct AreaActivateContext_s * *)&ptContext; // [esp+28h] [ebp+4h] ARGSLOT

  v1 = Game_eGameMode;
  ptAreaActivateQTask = ptContext->ptAreaActivateQTask;
  igi2_frame.ptTail = ptContext->ptAreaActivateQTask[4].tQTaskChildren.ptTail;
  if ( Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER && Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle )
  {
    HIBYTE(ptAreaActivateQTask[4].tQTaskRefList.ptTail) = Game_eGameMode;
    return;
  }
  ptHead = ptAreaActivateQTask[4].tQTaskRefList.ptHead;
  if ( Human_ptQTaskList->nTask > 0 )
  {
    v5 = 8;
    for ( ptContexta = (struct AreaActivateContext_s *)Human_ptQTaskList->nTask;
          ptContexta;
          ptContexta = (struct AreaActivateContext_s *)((char *)ptContexta - 1) )
    {
      v6 = *(int *)((char *)&Human_ptQTaskList->nTask + v5);
      if ( ((unsigned int)ptHead & Human_abAreaActivateCriteriaHuman[*(_DWORD *)(v6 + 428)]) == 0 )
        goto LABEL_16;
      sub_580CA0(*(int *)((char *)&Human_ptQTaskList->nTask + v5), &igi2_frame.ptPos.vX);
      if ( *(_DWORD *)(v6 + 1952) )
      {
        if ( *(_BYTE *)(v6 + 1180) )
          goto LABEL_16;
      }
      v7 = ptContext->ptAreaActivateQTask;
      if ( !AreaActivateQTask_IsInsideArea(ptContext->ptAreaActivateQTask, &igi2_frame.ptPos) )
        goto LABEL_16;
      if ( v1 == GAME_GAMEMODE_MULTIPLAYER )
      {
        if ( Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle )
        {
          HIBYTE(v7[4].tQTaskRefList.ptTail) = 1;
          goto LABEL_16;
        }
        ClientFromHumanQTask = NetManager_GetClientFromHumanQTask((struct QTask_s *)v6);
        if ( ClientFromHumanQTask )
          ptContext->nClientID = ClientFromHumanQTask->eNetworkID;
        v1 = Game_eGameMode;
      }
      ++ptContext->nHitCount;
LABEL_16:
      v5 += 4;
    }
  }
  if ( v1 == GAME_GAMEMODE_MULTIPLAYER && !Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle )
  {
    nHitCount = ptContext->nHitCount;
    if ( (struct QTask_s *)nHitCount != igi2_frame.ptTail )
      Server_SendAreaActivateMessage(ptContext->ptAreaActivateQTask, nHitCount, ptContext->nClientID);
  }
}

// source: j/0/human/human.c:4329  [anchor-mhash]
void __cdecl Human_AreaActivateAllHumansCB(struct AreaActivateContext_s *ptContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct QTask_s *ptTail; };
    struct { char igi2_o1[4]; struct real64x3_t ptPos; };
    char igi2_extent[28];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  enum GameMode_e v1; // edx
  struct Flow_t *v2; // ebp
  int v4; // ebx
  int v5; // edi
  struct Client_s *ClientFromHumanQTask; // eax
  int nHitCount; // eax
  struct AreaActivateContext_s *ptContexta = *(struct AreaActivateContext_s * *)&ptContext; // [esp+2Ch] [ebp+4h] ARGSLOT

  v1 = Game_eGameMode;
  v2 = Flow_ptFlow;
  igi2_frame.ptTail = ptContext->ptAreaActivateQTask[4].tQTaskChildren.ptTail;
  if ( Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER && Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle )
  {
    HIBYTE(ptContext->ptAreaActivateQTask[4].tQTaskRefList.ptTail) = 1;
    return;
  }
  if ( Human_ptQTaskList->nTask > 0 )
  {
    v4 = 8;
    ptContexta = (struct AreaActivateContext_s *)Human_ptQTaskList->nTask;
    while ( 1 )
    {
      v5 = *(int *)((char *)&Human_ptQTaskList->nTask + v4);
      if ( !*(_BYTE *)(v5 + 1181) )
        goto LABEL_14;
      sub_580CA0(*(int *)((char *)&Human_ptQTaskList->nTask + v4), &igi2_frame.ptPos.vX);
      if ( !AreaActivateQTask_IsInsideArea(ptContext->ptAreaActivateQTask, &igi2_frame.ptPos) )
        goto LABEL_14;
      if ( v1 != GAME_GAMEMODE_MULTIPLAYER )
        goto LABEL_13;
      if ( !v2->ptNetManagerQTask[6].tQTaskChildren.ptMiddle )
        break;
LABEL_14:
      v4 += 4;
      ptContexta = (struct AreaActivateContext_s *)((char *)ptContexta - 1);
      if ( !ptContexta )
        goto LABEL_15;
    }
    ClientFromHumanQTask = NetManager_GetClientFromHumanQTask((struct QTask_s *)v5);
    if ( ClientFromHumanQTask )
      ptContext->nClientID = ClientFromHumanQTask->eNetworkID;
    v1 = Game_eGameMode;
    v2 = Flow_ptFlow;
LABEL_13:
    ++ptContext->nHitCount;
    goto LABEL_14;
  }
LABEL_15:
  if ( v1 == GAME_GAMEMODE_MULTIPLAYER && !v2->ptNetManagerQTask[6].tQTaskChildren.ptMiddle )
  {
    nHitCount = ptContext->nHitCount;
    if ( (struct QTask_s *)nHitCount != igi2_frame.ptTail )
      Server_SendAreaActivateMessage(ptContext->ptAreaActivateQTask, nHitCount, ptContext->nClientID);
  }
}

// source: j/0/human/human.c:4464  [anchor-mhash]
void __cdecl Human_GetWeaponObjectHandler(struct QTask_s *ptQTask, void *pxContext)
{
  int v2; // ebp
  struct QTask_s *ptTail; // edi
  struct QTask_s *ptHead; // eax
  unsigned __int16 v5; // dx
  struct QTask_s *FirstChildOfType; // eax
  int v7; // eax
  struct QTask_s *NextSiblingOfType; // eax

  v2 = *((_DWORD *)pxContext + 1);
  ptTail = ptQTask[33].tQTaskChildren.ptTail;
  if ( ptQTask->eQTaskType != HumanPlayer_eQTaskType
    || LOBYTE(ptQTask[33].tQTaskRefList.ptMiddle)
    || BYTE2(ptTail[12].tQTaskRefList.ptTail)
    || ptQTask[33].tQTaskRefList.ptHead != (struct QReference_s *)1 )
  {
    if ( ptQTask[34].tQTaskRefList.ptHead )
      ptHead = (struct QTask_s *)ptQTask[34].tQTaskRefList.ptHead;
    else
      ptHead = ptQTask[34].tQTaskChildren.ptTail;
    *((_DWORD *)pxContext + 2) = 0;
  }
  else
  {
    BoneDynCubeObj_UpdateHierarchy((struct BoneDynCubeObj_s *)ptQTask[33].tQTaskChildren.ptTail);
    ptHead = (struct QTask_s *)ptTail[16].tQTaskRefList.ptTail;
    *((_DWORD *)pxContext + 2) = 1;
  }
  v5 = WeaponMagicObj_eQTaskType;
  FirstChildOfType = QTask_GetFirstChildOfType(ptHead, WeaponMagicObj_eQTaskType);
  *(_DWORD *)pxContext = FirstChildOfType;
  if ( FirstChildOfType )
  {
    while ( 1 )
    {
      v7 = v2--;
      if ( v7 <= 0 )
        break;
      NextSiblingOfType = QTask_GetNextSiblingOfType(*(struct QTask_s **)pxContext, v5);
      if ( !NextSiblingOfType )
        break;
      *(_DWORD *)pxContext = NextSiblingOfType;
    }
  }
}

// source: j/0/human/human.c:4518  [anchor-strings]
void __cdecl HumanShadow_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *ptParent; // edx
  unsigned __int16 v3; // cx
  unsigned __int16 v4; // di
  unsigned __int16 eQTaskType; // si

  ptParent = ptQTask->ptParent;
  if ( ptParent )
  {
    v3 = Human_eQTaskType;
    v4 = MagicObjContainer_eQTaskType;
    while ( 1 )
    {
      eQTaskType = ptParent->eQTaskType;
      if ( QTask_IsQTaskTypeDerived(eQTaskType, v3) )
        break;
      if ( eQTaskType == v4 )
        ptParent = ptParent[1].ptNext;
      else
        ptParent = ptParent->ptParent;
      if ( !ptParent )
        goto LABEL_11;
    }
    if ( ptParent->eQTaskType == HumanPlayer_eQTaskType )
      *(_DWORD *)pxContext = "shadowhi_1";
  }
LABEL_11:
  ((void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[0][ShadowVolume_eQTaskType].pfHandler)(
    ptQTask,
    pxContext);
}

int __cdecl sub_50BAF0(int result)
{
  *(_BYTE *)(result + 1180) = 0;
  *(_BYTE *)(result + 2002) = 1;
  *(_BYTE *)(result + 2003) = 0;
  *(_DWORD *)(result + 1916) = 1;
  *(_DWORD *)(result + 1920) = 0;
  *(_DWORD *)(result + 1924) = 0;
  *(_DWORD *)(result + 1912) = 0;
  return result;
}

// source: j/0/human/human.c:4559  [anchor-strings]
void __cdecl Human_MakeLadderFootstepSound(struct QTask_s *ptQTask)
{
  struct QReference_s *ptHead; // eax
  int v2; // ecx
  bool v3; // zf
  char zSound[32]; // [esp+4h] [ebp-20h] BYREF

  ptHead = ptQTask[51].tQTaskRefList.ptHead;
  v2 = dword_6B7D08[(_DWORD)ptHead];
  v3 = (*(_DWORD *)&ptQTask[30].eQTaskType & 0x40000) == 0;
  ptQTask[51].tQTaskRefList.ptHead = (struct QReference_s *)(((unsigned int)&ptHead->ptNext + 1) % 0xC);
  if ( v3 )
  {
    sprintf(zSound, "walk_ladder_%d", v2 + 1);
    Human_PlaySound((struct Human_s *)ptQTask, zSound, (struct real64x3_t *)&ptQTask[1]);
  }
}

// source: j/0/human/human.c:4601  [size]
unsigned __int16 __cdecl Human_GetQTaskType()
{
  return Human_eQTaskType;
}

// source: j/0/human/human.c:4617  [anchor-mhash]
enum bool __cdecl Human_isInsideSpawnArea(struct Human_s *ptHuman)
{
  return SpawnArea_isInsideAnyActiveSpawnAreaForTeam(
           ptHuman->tHumanParameters.eTeam,
           &ptHuman->tBoneDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos);
}

// source: j/0/human/human.c:4634  [anchor-refs]
__int16 __cdecl Human_GetHumanUpdateQTaskEvent()
{
  __int16 result; // ax

  result = Human_eHumanUpdateQTaskEvent;
  if ( Human_eHumanUpdateQTaskEvent == 512 )
  {
    result = QTask_NewQTaskEventFn(0, "HumanUpdate");
    Human_eHumanUpdateQTaskEvent = result;
  }
  return result;
}

// source: j/0/human/human.c:4654  [anchor-strings]
__int16 __cdecl Human_GetHumanWeaponFireQTaskEvent()
{
  __int16 result; // ax

  result = Human_eHumanWeaponFireQTaskEvent;
  if ( Human_eHumanWeaponFireQTaskEvent == 512 )
  {
    result = QTask_NewQTaskEventFn(0, "HumanWeaponFire");
    Human_eHumanWeaponFireQTaskEvent = result;
  }
  return result;
}

// source: j/0/human/human.c:4674  [anchor-strings]
__int16 __cdecl Human_GetHumanWeaponReloadQTaskEvent()
{
  __int16 result; // ax

  result = Human_eHumanWeaponReloadQTaskEvent;
  if ( Human_eHumanWeaponReloadQTaskEvent == 512 )
  {
    result = QTask_NewQTaskEventFn(0, "HumanWeaponReload");
    Human_eHumanWeaponReloadQTaskEvent = result;
  }
  return result;
}

// source: j/0/human/human.c:4694  [size]
__int16 __cdecl Human_GetEvaluateGunShotQTaskEvent()
{
  return Human_eEvaluateGunShotQTaskEvent;
}

// source: j/0/human/human.c:4709  [size]
__int16 __cdecl Human_GetCloseCombatDamageQTaskEvent()
{
  return Human_eCloseCombatDamageQTaskEvent;
}

// source: j/0/human/human.c:4724  [size]
__int16 __cdecl Human_GetKilledByYouQTaskEvent()
{
  return Human_eKilledByYouQTaskEvent;
}

// source: j/0/human/human.c:4739  [size]
__int16 __cdecl Human_GetHitByYouQTaskEvent()
{
  return Human_eHitByYouQTaskEvent;
}

// source: j/0/human/human.c:4757  [size]
struct ParameterList_s *__cdecl Human_GetParameterList()
{
  return Human_ptParameterList;
}

// source: j/0/human/human.c:4772  [size]
struct QTaskList_s *__cdecl Human_GetHumanQTaskList()
{
  return Human_ptQTaskList;
}

// source: j/0/human/human.c:4787  [size]
struct QTask_s *__cdecl Human_SetHumanAIQTask(
        struct QTask_s *ptHumanQTask,
        struct QTask_s *ptHumanAIQTask)
{
  ptHumanQTask[48].ptParent = ptHumanAIQTask;
  return ptHumanAIQTask;
}

// source: j/0/human/human.c:4852  [size]
void Human_PrintDebugTextOnPlayer(struct QTask_s *ptQTask, int nLine, char *zFormat, ...)
{
  ;
}

// source: j/0/human/human.c:4906  [size]
struct QTask_s *__cdecl Human_Delete(struct QTask_s *ptQTask)
{
  LOBYTE(ptQTask[46].eQTaskType) = 1;
  return ptQTask;
}

// source: j/0/human/human.c:4924  [anchor-mhash]
void __cdecl Human_UpdateActivate(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { float pxContext; };
    struct { char igi2_o1[4]; struct ActivateContext_t tActivateContext; };
    struct { char igi2_o2[52]; struct EvaluateActivateContext_t tEvaluateActivateContext; };
    char igi2_extent[188];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *ptTail; // eax
  struct QTask_s *v2; // eax
  struct QReference_s *v3; // eax
  struct QTask_s *pxObject; // ecx
  double v5; // st7
  double v6; // st7
  double v7; // st6
  double v8; // st5
  struct QTask_s *v9; // eax
  struct QTask_s *ptBestQTask; // esi
  struct QReference_s *ptHead; // eax
  unsigned __int16 *v12; // eax

  ptTail = ptQTask[46].tQTaskChildren.ptTail;
  if ( ptTail )
  {
    QReference_Delete((struct QReference_s *)ptTail, &QTask_tQTaskRefPool);
    ptQTask[46].tQTaskChildren.ptTail = nullptr;
  }
  if ( (ptQTask[30].eQTaskType & 2) != 0 && !LOBYTE(ptQTask[46].tQTaskRefList.ptMiddle) )
  {
    v2 = ptQTask[33].tQTaskChildren.ptTail;
    igi2_frame.tEvaluateActivateContext.ptQTask = ptQTask;
    qmemcpy(&igi2_frame.tEvaluateActivateContext.tViewPos, &v2[10].tQTaskChildren, sizeof(igi2_frame.tEvaluateActivateContext.tViewPos));
    qmemcpy(
      &igi2_frame.tEvaluateActivateContext.tViewOrientation,
      &v2[10].ptParent,
      sizeof(igi2_frame.tEvaluateActivateContext.tViewOrientation));
    qmemcpy(
      &igi2_frame.tEvaluateActivateContext.tObjectOrientation,
      &ptQTask[3].ptPrev,
      sizeof(igi2_frame.tEvaluateActivateContext.tObjectOrientation));
    v3 = Game_ptGame->aptPlayerQTaskRef[2];
    pxObject = nullptr;
    if ( v3 )
      pxObject = (struct QTask_s *)v3->pxObject;
    if ( ptQTask == pxObject )
      v5 = 0.7853981852531433;
    else
      v5 = 3.1415927410125732;
    igi2_frame.tEvaluateActivateContext.vBestAlpha = v5;
    igi2_frame.tEvaluateActivateContext.vBestGamma = v5;
    v6 = *(float *)&ptQTask[7].tQTaskRefList.ptMiddle;
    igi2_frame.tEvaluateActivateContext.vBestLength = 8192.0;
    v7 = *(float *)&ptQTask[7].tQTaskRefList.ptHead;
    v8 = *(float *)&ptQTask[7].tQTaskChildren.ptTail;
    igi2_frame.tEvaluateActivateContext.ptBestQTask = nullptr;
    igi2_frame.pxContext = sqrt(v8 * v8 + v7 * v7 + v6 * v6) + *(float *)&ptQTask[8].ptNext;
    World_TriggerQTaskEventSphereSpecificTree(
      Game_ptGame->ptWorld,
      GameFunctions_eEvaluateActivateQTaskEvent,
      &igi2_frame.tEvaluateActivateContext,
      (struct real64x3_t *)&ptQTask[1],
      igi2_frame.pxContext,
      0xFFFFFFFF,
      WORLD_DYNCUBETREE_STATIONARY);
    v9 = ptQTask[46].tQTaskChildren.ptTail;
    ptBestQTask = igi2_frame.tEvaluateActivateContext.ptBestQTask;
    if ( v9 )
    {
      QReference_Delete((struct QReference_s *)v9, &QTask_tQTaskRefPool);
      ptQTask[46].tQTaskChildren.ptTail = nullptr;
    }
    if ( ptBestQTask )
      ptQTask[46].tQTaskChildren.ptTail = (struct QTask_s *)QTask_NewQTaskRef(ptBestQTask);
  }
  ptHead = ptQTask[46].tQTaskRefList.ptHead;
  if ( ptHead )
  {
    v12 = (unsigned __int16 *)ptHead->pxObject;
    if ( v12 )
    {
      igi2_frame.tActivateContext.ptHumanQTask = ptQTask;
      qmemcpy(&igi2_frame.tActivateContext.tPos, &ptQTask[1], sizeof(igi2_frame.tActivateContext.tPos));
      igi2_frame.tActivateContext.pvLastChannel = (float *)&ptQTask[12].ptParent;
      igi2_frame.tActivateContext.pvChannel = (float *)&ptQTask[19].ptPrev;
      igi2_frame.tActivateContext.nActivateTime = (int)ptQTask[46].tQTaskRefList.ptTail;
      ((void (__cdecl *)(unsigned __int16 *, struct ActivateContext_t *))QTask_aatQTaskFinalEvent[GameFunctions_eActivateQTaskEvent][v12[18]].pfHandler)(
        v12,
        &igi2_frame.tActivateContext);
      ++*(int *)&ptQTask[46].tQTaskRefList.ptTail;
    }
  }
}

// source: j/0/human/human.c:5025  [anchor-mhash]
void __cdecl Human_NotifyPositionUpdated(struct Human_s *ptHuman)
{
  if ( Timer_isPerformanceCounter )
    LODWORD(ptHuman->atOldPos[0].vX) = Timer_GetPerformanceCounter() - Timer_nStartTime;
  else
    LODWORD(ptHuman->atOldPos[0].vX) = GetTickCount() - Timer_nStartTime;
}

// source: j/0/human/human.c:5039  [anchor-caller]
void __cdecl Human_UpdateBody(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { float ptDest; };
    struct { char igi2_o1[4]; float vAlpha; };
    struct { char igi2_o2[32]; float ptSource; };
    struct { char igi2_o3[36]; struct QTask_s *ptSource_4; };
    struct { char igi2_o4[40]; struct real32x9_t ptSource_8; };
    struct { char igi2_o5[80]; int v30; };
    struct { char igi2_o6[84]; struct QTask_s *pvAlpha; };
    struct { char igi2_o7[88]; struct real32x3_t vGamma; };
    struct { char igi2_o8[100]; struct real64x3_t ptCenterPosition; };
    struct { char igi2_o9[124]; struct real32x9_t v34; };
    char igi2_extent[164];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QReference_s *ptTail; // eax
  struct QTask_s *v2; // esi
  double v3; // st7
  double v4; // st6
  struct QTask_s *v5; // ecx
  struct QTask_s *v6; // eax
  struct QTask_s *v7; // edx
  int ptMiddle_low; // eax
  double v9; // st7
  double v10; // st7
  double v11; // st7
  double v12; // st7
  double v13; // st7
  double v14; // st7
  double v15; // st6
  double v16; // st6
  double v17; // st5
  double v18; // rt0
  double v19; // st6
  float *p_ptPrev; // edi
  double v21; // st6
  double v22; // st6
  double v23; // st7
  double v24; // st6

  ptTail = ptQTask[44].tQTaskRefList.ptTail;
  v2 = ptQTask[33].tQTaskChildren.ptTail;
  igi2_frame.v30 = 0;
  if ( ptTail )
  {
    igi2_frame.ptSource_8.tX.vX = *(float *)&ptTail[10].ptPrev * *(float *)&ptQTask[45].tQTaskChildren.ptTail
                     + *(float *)&ptQTask[46].ptNext * *(float *)&ptTail[11].ptNext
                     + *(float *)&ptTail[10].pxObject * *(float *)&ptQTask[45].tQTaskRefList.ptTail;
    igi2_frame.ptSource_8.tX.vY = *(float *)&ptTail[10].ptPrev * *(float *)&ptQTask[45].tQTaskRefList.ptHead
                     + *(float *)&ptQTask[46].ptPrev * *(float *)&ptTail[11].ptNext
                     + *(float *)&ptTail[10].pxObject * *(float *)&ptQTask[45].ptParent;
    igi2_frame.ptSource_8.tX.vZ = *(float *)&ptTail[10].ptPrev * *(float *)&ptQTask[45].tQTaskRefList.ptMiddle
                     + *(float *)&ptQTask[46].tQTaskChildren.ptHead * *(float *)&ptTail[11].ptNext
                     + *(float *)&ptTail[10].pxObject * *(float *)&ptQTask[45].eQTaskType;
    igi2_frame.ptSource_8.tY.vX = *(float *)&ptQTask[45].tQTaskRefList.ptTail * *(float *)&ptTail[11].pxObject
                     + *(float *)&ptQTask[45].tQTaskChildren.ptTail * *(float *)&ptTail[11].ptPrev
                     + *(float *)&ptQTask[46].ptNext * *(float *)&ptTail[12].ptNext;
    igi2_frame.ptSource_8.tY.vY = *(float *)&ptQTask[45].ptParent * *(float *)&ptTail[11].pxObject
                     + *(float *)&ptQTask[45].tQTaskRefList.ptHead * *(float *)&ptTail[11].ptPrev
                     + *(float *)&ptQTask[46].ptPrev * *(float *)&ptTail[12].ptNext;
    igi2_frame.ptSource_8.tY.vZ = *(float *)&ptQTask[45].eQTaskType * *(float *)&ptTail[11].pxObject
                     + *(float *)&ptQTask[45].tQTaskRefList.ptMiddle * *(float *)&ptTail[11].ptPrev
                     + *(float *)&ptQTask[46].tQTaskChildren.ptHead * *(float *)&ptTail[12].ptNext;
    igi2_frame.ptSource_8.tZ.vX = *(float *)&ptQTask[46].ptNext * *(float *)&ptTail[13].ptNext
                     + *(float *)&ptQTask[45].tQTaskRefList.ptTail * *(float *)&ptTail[12].pxObject
                     + *(float *)&ptQTask[45].tQTaskChildren.ptTail * *(float *)&ptTail[12].ptPrev;
    igi2_frame.ptSource_8.tZ.vY = *(float *)&ptQTask[46].ptPrev * *(float *)&ptTail[13].ptNext
                     + *(float *)&ptQTask[45].ptParent * *(float *)&ptTail[12].pxObject
                     + *(float *)&ptQTask[45].tQTaskRefList.ptHead * *(float *)&ptTail[12].ptPrev;
    v3 = *(float *)&ptQTask[46].tQTaskChildren.ptHead * *(float *)&ptTail[13].ptNext
       + *(float *)&ptQTask[45].eQTaskType * *(float *)&ptTail[12].pxObject;
    v4 = *(float *)&ptQTask[45].tQTaskRefList.ptMiddle * *(float *)&ptTail[12].ptPrev;
    igi2_frame.ptSource_8.nOps = (int)&ptQTask[46].tQTaskChildren.ptMiddle->ptNext + (unsigned int)ptTail[13].ptPrev + 1;
    igi2_frame.ptSource_8.tZ.vZ = v3 + v4;
    qmemcpy(&igi2_frame.v34, &igi2_frame.ptSource_8, sizeof(igi2_frame.v34));
    Real32x9_GetAngles(&igi2_frame.v34, &igi2_frame.ptSource, (float *)&igi2_frame.pvAlpha, (float *)&igi2_frame.ptSource_4);
    v5 = (struct QTask_s *)LODWORD(igi2_frame.ptSource);
    v6 = igi2_frame.pvAlpha;
    *(float *)&ptQTask[33].tQTaskRefList.ptTail = igi2_frame.ptSource;
    v7 = igi2_frame.ptSource_4;
    ptQTask[33].ptParent = v5;
    ptQTask[34].ptNext = v6;
    *(_DWORD *)&ptQTask[33].eQTaskType = v6;
    ptQTask[34].tQTaskChildren.ptHead = v7;
    ptQTask[34].ptPrev = v7;
    goto LABEL_30;
  }
  ptMiddle_low = LOBYTE(ptQTask[34].tQTaskChildren.ptMiddle);
  igi2_frame.ptSource = *(float *)&ptQTask[19].ptPrev;
  if ( (_BYTE)ptMiddle_low )
  {
    igi2_frame.ptSource = 0.0;
  }
  else if ( igi2_frame.ptSource < 0.0 )
  {
    v9 = -igi2_frame.ptSource;
    goto LABEL_6;
  }
  v9 = igi2_frame.ptSource;
LABEL_6:
  if ( v9 > 0.0 )
  {
    igi2_frame.v30 = 1;
    Human_UpdatePlatformMovement(ptQTask, false, true, nullptr);
  }
  v10 = igi2_frame.ptSource;
  ptQTask[33].ptParent = nullptr;
  ptQTask[33].tQTaskRefList.ptTail = nullptr;
  ptQTask[34].ptNext = nullptr;
  *(_DWORD *)&ptQTask[33].eQTaskType = 0;
  v11 = -(v10 * 3.1415927410125732) * *(float *)&v2[16].tQTaskChildren.ptHead;
  igi2_frame.ptSource = v11;
  if ( v11 != 0.0 && *(_DWORD *)&ptQTask[32].eQTaskType == 2 )
  {
    if ( v11 < 0.0 )
      v12 = -1.0;
    else
      v12 = 1.0;
    *((float *)&igi2_frame.ptCenterPosition.vY + 1) = -204.8000030517578 * v12;
    *(float *)&igi2_frame.ptCenterPosition.vX = v12 * 204.8000030517578;
    igi2_frame.ptCenterPosition.vZ = 1.0625327229682655e+21;
    HIDWORD(igi2_frame.ptCenterPosition.vX) = -1001599795;
    LODWORD(igi2_frame.ptCenterPosition.vY) = 1145883853;
    if ( Human_IsGammaRotationAllowed(
           ptQTask,
           (struct real32x9_t *)&ptQTask[3].ptPrev,
           (struct real64x3_t *)&ptQTask[1],
           (struct real32x3_t *)((char *)&igi2_frame.ptCenterPosition.vY + 4),
           (struct real32x3_t *)&igi2_frame.ptCenterPosition,
           igi2_frame.ptSource,
           (int *)&igi2_frame.ptSource_4,
           &igi2_frame.vGamma) )
    {
      v11 = igi2_frame.ptSource;
    }
    else
    {
      if ( (((unsigned __int8)igi2_frame.ptSource_4 & 1) == 0 || ((unsigned __int8)igi2_frame.ptSource_4 & 2) == 0)
        && (((unsigned __int8)igi2_frame.ptSource_4 & 4) == 0 || ((unsigned __int8)igi2_frame.ptSource_4 & 8) == 0) )
      {
        v13 = igi2_frame.ptSource;
        if ( igi2_frame.ptSource < 0.0 )
          v13 = -v13;
        v14 = v13 * igi2_frame.vGamma.vX * 81.91999816894531;
        v15 = igi2_frame.ptSource;
        if ( igi2_frame.ptSource < 0.0 )
          v15 = -v15;
        v16 = v15 * igi2_frame.vGamma.vY * 81.91999816894531;
        v17 = igi2_frame.ptSource;
        if ( igi2_frame.ptSource < 0.0 )
          v17 = -v17;
        v18 = v17 * igi2_frame.vGamma.vZ * 81.91999816894531;
        *(float *)&ptQTask[36].ptPrev = v14 + *(float *)&ptQTask[36].ptPrev;
        *(float *)&ptQTask[36].tQTaskChildren.ptHead = v16 + *(float *)&ptQTask[36].tQTaskChildren.ptHead;
        *(float *)&ptQTask[36].tQTaskChildren.ptMiddle = v18 + *(float *)&ptQTask[36].tQTaskChildren.ptMiddle;
      }
      v11 = 0.0;
    }
  }
  v19 = v11 + *(float *)&ptQTask[34].tQTaskChildren.ptHead;
  *(float *)&ptQTask[34].tQTaskChildren.ptHead = v19;
  *(float *)&ptQTask[43].ptParent = v11;
  *(float *)&ptQTask[34].ptPrev = v19;
LABEL_30:
  p_ptPrev = (float *)&ptQTask[3].ptPrev;
  Real32x9_Create(
    (struct real32x9_t *)&ptQTask[3].ptPrev,
    *(float *)&ptQTask[33].tQTaskRefList.ptTail,
    *(float *)&ptQTask[33].eQTaskType,
    *(float *)&ptQTask[34].ptPrev);
  if ( LOBYTE(ptQTask[29].tQTaskRefList.ptHead) || *(_DWORD *)&ptQTask[32].eQTaskType == 2 )
  {
    igi2_frame.vGamma.vX = *(float *)&ptQTask[51].ptNext * *(float *)&ptQTask[3].tQTaskRefList.ptTail
              + *(float *)&ptQTask[50].eQTaskType * *(float *)&ptQTask[3].tQTaskChildren.ptTail
              + *p_ptPrev * *(float *)&ptQTask[50].ptParent;
    v21 = *(float *)&ptQTask[51].ptNext * *(float *)&ptQTask[3].eQTaskType
        + *(float *)&ptQTask[50].eQTaskType * *(float *)&ptQTask[3].tQTaskRefList.ptMiddle
        + *(float *)&ptQTask[50].ptParent * *(float *)&ptQTask[3].tQTaskChildren.ptMiddle;
    if ( v21 != 0.0 )
    {
      v22 = 1.0 / v21;
      igi2_frame.vAlpha = atan2(igi2_frame.vGamma.vX * v22, 1.0);
      igi2_frame.ptDest = -atan2(
                  (*(float *)&ptQTask[51].ptNext * *(float *)&ptQTask[3].ptParent
                 + *(float *)&ptQTask[50].eQTaskType * *(float *)&ptQTask[3].tQTaskRefList.ptHead
                 + *(float *)&ptQTask[3].tQTaskChildren.ptHead * *(float *)&ptQTask[50].ptParent)
                * v22,
                  1.0);
      Real32x9_Create(&igi2_frame.ptSource_8, igi2_frame.ptDest, igi2_frame.vAlpha, 0.0);
      igi2_frame.v34.tX.vX = igi2_frame.ptSource_8.tZ.vX * *(float *)&ptQTask[3].tQTaskChildren.ptMiddle
                + igi2_frame.ptSource_8.tY.vX * *(float *)&ptQTask[3].tQTaskChildren.ptHead
                + igi2_frame.ptSource_8.tX.vX * *p_ptPrev;
      igi2_frame.v34.tX.vY = igi2_frame.ptSource_8.tZ.vY * *(float *)&ptQTask[3].tQTaskChildren.ptMiddle
                + igi2_frame.ptSource_8.tY.vY * *(float *)&ptQTask[3].tQTaskChildren.ptHead
                + igi2_frame.ptSource_8.tX.vY * *p_ptPrev;
      igi2_frame.v34.tX.vZ = igi2_frame.ptSource_8.tZ.vZ * *(float *)&ptQTask[3].tQTaskChildren.ptMiddle
                + igi2_frame.ptSource_8.tY.vZ * *(float *)&ptQTask[3].tQTaskChildren.ptHead
                + igi2_frame.ptSource_8.tX.vZ * *p_ptPrev;
      igi2_frame.v34.tY.vX = igi2_frame.ptSource_8.tY.vX * *(float *)&ptQTask[3].tQTaskRefList.ptHead
                + igi2_frame.ptSource_8.tX.vX * *(float *)&ptQTask[3].tQTaskChildren.ptTail
                + igi2_frame.ptSource_8.tZ.vX * *(float *)&ptQTask[3].tQTaskRefList.ptMiddle;
      igi2_frame.v34.tY.vY = igi2_frame.ptSource_8.tY.vY * *(float *)&ptQTask[3].tQTaskRefList.ptHead
                + igi2_frame.ptSource_8.tX.vY * *(float *)&ptQTask[3].tQTaskChildren.ptTail
                + igi2_frame.ptSource_8.tZ.vY * *(float *)&ptQTask[3].tQTaskRefList.ptMiddle;
      igi2_frame.v34.tY.vZ = igi2_frame.ptSource_8.tY.vZ * *(float *)&ptQTask[3].tQTaskRefList.ptHead
                + igi2_frame.ptSource_8.tX.vZ * *(float *)&ptQTask[3].tQTaskChildren.ptTail
                + igi2_frame.ptSource_8.tZ.vZ * *(float *)&ptQTask[3].tQTaskRefList.ptMiddle;
      v23 = igi2_frame.ptSource_8.tZ.vX * *(float *)&ptQTask[3].eQTaskType;
      v24 = igi2_frame.ptSource_8.tX.vX * *(float *)&ptQTask[3].tQTaskRefList.ptTail;
      igi2_frame.v34.nOps = (int)&ptQTask[4].ptNext->ptNext + igi2_frame.ptSource_8.nOps + 1;
      igi2_frame.v34.tZ.vX = v23 + v24 + igi2_frame.ptSource_8.tY.vX * *(float *)&ptQTask[3].ptParent;
      igi2_frame.v34.tZ.vY = igi2_frame.ptSource_8.tZ.vY * *(float *)&ptQTask[3].eQTaskType
                + igi2_frame.ptSource_8.tX.vY * *(float *)&ptQTask[3].tQTaskRefList.ptTail
                + igi2_frame.ptSource_8.tY.vY * *(float *)&ptQTask[3].ptParent;
      igi2_frame.v34.tZ.vZ = igi2_frame.ptSource_8.tZ.vZ * *(float *)&ptQTask[3].eQTaskType
                + igi2_frame.ptSource_8.tX.vZ * *(float *)&ptQTask[3].tQTaskRefList.ptTail
                + igi2_frame.ptSource_8.tY.vZ * *(float *)&ptQTask[3].ptParent;
      qmemcpy(p_ptPrev, &igi2_frame.v34, 0x28u);
    }
  }
  if ( igi2_frame.v30 )
    Human_UpdatePlatformPos(ptQTask, false, true);
}

// source: j/0/human/human.c:5229  [anchor-caller]
void __cdecl Human_Move(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { float ptDynCubeObj; };
    struct { char igi2_o1[20]; struct real32x3_t ptSpeed; };
    struct { char igi2_o2[32]; unsigned int pbSignal; };
    struct { char igi2_o3[36]; float v34; };
    struct { char igi2_o4[40]; enum bool v35; };
    struct { char igi2_o5[44]; float v36; };
    struct { char igi2_o6[48]; enum bool isForceUpdatePosition; };
    struct { char igi2_o7[52]; struct real64x3_t ptPos1; };
    struct { char igi2_o8[76]; struct real64x3_t ptPos0; };
    struct { char igi2_o9[100]; float v40[34]; };
    char igi2_extent[236];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *ptPrev; // edx
  struct QTask_s *ptHead; // eax
  struct QReference_s *ptMiddle; // edx
  unsigned __int16 *pxObject; // edx
  void (__cdecl *pfHandler)(unsigned __int16 *, float *); // eax
  double vX; // st7
  bool v7; // zf
  float *p_tQTaskRefList; // ecx
  long double v9; // st6
  double v10; // st6
  struct QTask_s *v11; // edx
  double v12; // st6
  char ptTail; // al
  double v14; // st6
  double v15; // st5
  double v16; // st7
  char v17; // al
  struct QTask_s *v18; // edi
  double v19; // st7
  double v20; // st6
  double v21; // st5
  struct Game_s *v22; // ecx
  float v23; // eax
  float vY; // ecx
  float vZ; // edx
  double v26; // st7
  enum bool v27; // eax
  enum bool v28; // ecx
  double v29; // st7
  double v30; // st6

  igi2_frame.isForceUpdatePosition = false;
  igi2_frame.v35 = false;
  ptPrev = ptQTask[38].ptPrev;
  igi2_frame.pbSignal = *(_DWORD *)&ptQTask[30].eQTaskType;
  ptHead = ptQTask[38].tQTaskChildren.ptHead;
  LODWORD(igi2_frame.ptSpeed.vZ) = ptQTask[38].tQTaskChildren.ptMiddle;
  LODWORD(igi2_frame.ptSpeed.vX) = ptPrev;
  LODWORD(igi2_frame.ptSpeed.vY) = ptHead;
  qmemcpy(&igi2_frame.ptPos0, &ptQTask[1], sizeof(igi2_frame.ptPos0));
  Human_UpdatePlatformMovement(ptQTask, true, true, &igi2_frame.ptPos0);
  ptMiddle = ptQTask[44].tQTaskRefList.ptMiddle;
  if ( ptMiddle && ptMiddle->pxObject )
  {
    memset(igi2_frame.v40, 0, sizeof(igi2_frame.v40));
    qmemcpy(&igi2_frame.v40[4], &ptQTask[40].tQTaskRefList.ptMiddle, 0x78u);
    pxObject = (unsigned __int16 *)ptMiddle->pxObject;
    pfHandler = (void (__cdecl *)(unsigned __int16 *, float *))QTask_aatQTaskFinalEvent[ConveyorBelt_ePushObjectQTaskEvent][pxObject[18]].pfHandler;
    if ( pfHandler )
      pfHandler(pxObject, igi2_frame.v40);
    vX = igi2_frame.v40[0] + igi2_frame.ptSpeed.vX;
    igi2_frame.ptSpeed.vY = igi2_frame.v40[1] + igi2_frame.ptSpeed.vY;
    igi2_frame.ptSpeed.vZ = igi2_frame.v40[2] + igi2_frame.ptSpeed.vZ;
    LOBYTE(ptQTask[74].ptPrev) = igi2_frame.v40[0] != 0.0 || igi2_frame.v40[1] != 0.0 || igi2_frame.v40[2] != 0.0;
  }
  else
  {
    vX = igi2_frame.ptSpeed.vX;
  }
  v7 = *(_DWORD *)&ptQTask[42].eQTaskType == 0;
  p_tQTaskRefList = (float *)&ptQTask[37].tQTaskRefList;
  ptQTask[37].tQTaskRefList.ptHead = nullptr;
  ptQTask[37].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[37].tQTaskRefList.ptTail = nullptr;
  if ( !v7 && (igi2_frame.pbSignal & 2) != 0 )
  {
    v9 = sin(*(float *)&ptQTask[42].tQTaskChildren.ptHead * 1.5707963705062866);
    *(float *)&ptQTask[36].ptPrev = v9 * *(float *)&ptQTask[36].ptPrev;
    *(float *)&ptQTask[36].tQTaskChildren.ptHead = v9 * *(float *)&ptQTask[36].tQTaskChildren.ptHead;
    *(float *)&ptQTask[36].tQTaskChildren.ptMiddle = v9 * *(float *)&ptQTask[36].tQTaskChildren.ptMiddle;
    if ( *(float *)&ptQTask[42].tQTaskChildren.ptHead < 0.6427900195121765 )
    {
      v10 = *(float *)&ptQTask[42].tQTaskChildren.ptHead;
      *p_tQTaskRefList = *(float *)&ptQTask[42].ptNext;
      v11 = ptQTask[42].tQTaskChildren.ptHead;
      ptQTask[37].tQTaskRefList.ptMiddle = (struct QReference_s *)ptQTask[42].ptPrev;
      ptQTask[37].tQTaskRefList.ptTail = (struct QReference_s *)v11;
      *p_tQTaskRefList = v10 * *p_tQTaskRefList * 2275.0;
      *(float *)&ptQTask[37].tQTaskRefList.ptMiddle = *(float *)&ptQTask[42].tQTaskChildren.ptHead
                                                    * *(float *)&ptQTask[37].tQTaskRefList.ptMiddle
                                                    * 2275.0;
      v12 = (*(float *)&ptQTask[42].tQTaskChildren.ptHead * *(float *)&ptQTask[37].tQTaskRefList.ptTail - 1.0) * 2275.0;
      *(float *)&ptQTask[37].tQTaskRefList.ptTail = v12;
      if ( v12 >= -409.6000061035156 )
      {
        if ( v12 > 0.0 )
          v12 = 0.0;
      }
      else
      {
        v12 = -409.6000061035156;
      }
      *(float *)&ptQTask[37].tQTaskRefList.ptTail = v12;
    }
  }
  ptTail = (char)ptQTask[36].tQTaskChildren.ptTail;
  v14 = (*p_tQTaskRefList - *(float *)&ptQTask[37].tQTaskChildren.ptHead) * 0.10000000149011612
      + *(float *)&ptQTask[37].tQTaskChildren.ptHead;
  *(float *)&ptQTask[37].tQTaskChildren.ptHead = v14;
  igi2_frame.v36 = (*(float *)&ptQTask[37].tQTaskRefList.ptMiddle - *(float *)&ptQTask[37].tQTaskChildren.ptMiddle) * 0.10000000149011612
      + *(float *)&ptQTask[37].tQTaskChildren.ptMiddle;
  *(float *)&ptQTask[37].tQTaskChildren.ptMiddle = igi2_frame.v36;
  igi2_frame.v34 = (*(float *)&ptQTask[37].tQTaskRefList.ptTail - *(float *)&ptQTask[37].tQTaskChildren.ptTail) * 0.10000000149011612
      + *(float *)&ptQTask[37].tQTaskChildren.ptTail;
  *(float *)&ptQTask[37].tQTaskChildren.ptTail = igi2_frame.v34;
  if ( !ptTail )
  {
    vX = vX + *(float *)&ptQTask[36].ptPrev;
    igi2_frame.ptSpeed.vY = igi2_frame.ptSpeed.vY + *(float *)&ptQTask[36].tQTaskChildren.ptHead;
    igi2_frame.ptSpeed.vZ = igi2_frame.ptSpeed.vZ + *(float *)&ptQTask[36].tQTaskChildren.ptMiddle;
    if ( vX != 0.0 || igi2_frame.ptSpeed.vY != 0.0 || igi2_frame.ptSpeed.vZ != 0.0 )
    {
      igi2_frame.v35 = true;
      igi2_frame.isForceUpdatePosition = true;
    }
    ptQTask[36].ptPrev = nullptr;
    ptQTask[36].tQTaskChildren.ptHead = nullptr;
    ptQTask[36].tQTaskChildren.ptMiddle = nullptr;
  }
  igi2_frame.ptSpeed.vY = igi2_frame.v36 + igi2_frame.ptSpeed.vY;
  igi2_frame.ptSpeed.vZ = igi2_frame.v34 + igi2_frame.ptSpeed.vZ;
  v15 = *(float *)&ptQTask[38].tQTaskChildren.ptTail * 0.8999999761581421;
  *(float *)&ptQTask[38].tQTaskChildren.ptTail = v15;
  igi2_frame.v34 = *(float *)&ptQTask[38].tQTaskRefList.ptHead * 0.8999999761581421;
  *(float *)&ptQTask[38].tQTaskRefList.ptHead = igi2_frame.v34;
  igi2_frame.v36 = *(float *)&ptQTask[38].tQTaskRefList.ptMiddle * 0.8999999761581421;
  *(float *)&ptQTask[38].tQTaskRefList.ptMiddle = igi2_frame.v36;
  igi2_frame.ptSpeed.vX = v15 + v14 + vX;
  ptQTask[37].ptParent = (struct QTask_s *)LODWORD(igi2_frame.ptSpeed.vX);
  igi2_frame.ptSpeed.vY = igi2_frame.v34 + igi2_frame.ptSpeed.vY;
  v16 = igi2_frame.v36;
  *(float *)&ptQTask[37].eQTaskType = igi2_frame.ptSpeed.vY;
  igi2_frame.ptSpeed.vZ = v16 + igi2_frame.ptSpeed.vZ;
  ptQTask[38].ptNext = (struct QTask_s *)LODWORD(igi2_frame.ptSpeed.vZ);
  if ( HIBYTE(ptQTask[74].ptPrev) )
  {
    *(float *)&ptQTask[37].ptParent = *(float *)&ptQTask[71].ptParent + *(float *)&ptQTask[37].ptParent;
    *(float *)&ptQTask[37].eQTaskType = *(float *)&ptQTask[71].eQTaskType + *(float *)&ptQTask[37].eQTaskType;
    *(float *)&ptQTask[38].ptNext = *(float *)&ptQTask[72].ptNext + *(float *)&ptQTask[38].ptNext;
  }
  v17 = (char)ptQTask[40].tQTaskChildren.ptMiddle;
  igi2_frame.ptPos1.vX = igi2_frame.ptSpeed.vX + igi2_frame.ptPos0.vX;
  igi2_frame.pbSignal &= ~8u;
  igi2_frame.ptPos1.vY = igi2_frame.ptSpeed.vY + igi2_frame.ptPos0.vY;
  igi2_frame.ptPos1.vZ = igi2_frame.ptSpeed.vZ + igi2_frame.ptPos0.vZ;
  if ( !v17 )
  {
    if ( BYTE2(ptQTask[40].tQTaskChildren.ptMiddle) )
      Human_ObjectCollision(ptQTask, &igi2_frame.ptPos0, &igi2_frame.ptPos1, &igi2_frame.ptSpeed, &igi2_frame.pbSignal);
    if ( BYTE1(ptQTask[40].tQTaskChildren.ptMiddle) )
      Human_GroundCollision(ptQTask, &igi2_frame.ptPos0, &igi2_frame.ptPos1, &igi2_frame.ptSpeed, &igi2_frame.pbSignal, *(float *)&ptQTask[49].tQTaskRefList.ptTail);
    if ( LOBYTE(ptQTask[40].tQTaskChildren.ptTail) )
      Human_HumanCollision(ptQTask, &igi2_frame.ptPos0, &igi2_frame.ptPos1, &igi2_frame.ptSpeed);
  }
  if ( LOBYTE(ptQTask[29].tQTaskRefList.ptHead) )
  {
    v18 = (struct QTask_s *)ptQTask[40].tQTaskRefList.ptMiddle;
    if ( v18 )
      Human_SetGroundTask(ptQTask, v18);
    if ( !BYTE2(ptQTask[50].ptNext) )
    {
      Human_InterpolateZAxisToAveragedGroundNormal(ptQTask);
      qmemcpy(&ptQTask[29].tQTaskRefList.ptMiddle, &ptQTask[3].ptPrev, sizeof(struct QTask_s));
      Human_HandleDeathCollision(ptQTask, &igi2_frame.ptPos0, &igi2_frame.ptPos1);
      igi2_frame.v35 = true;
      igi2_frame.isForceUpdatePosition = true;
    }
  }
  else
  {
    ptQTask[50].tQTaskChildren.ptHead = nullptr;
    ptQTask[50].tQTaskChildren.ptMiddle = nullptr;
    ptQTask[50].tQTaskChildren.ptTail = nullptr;
  }
  v19 = *(float *)&ptQTask[7].tQTaskRefList.ptMiddle;
  v20 = *(float *)&ptQTask[7].tQTaskRefList.ptHead;
  v21 = *(float *)&ptQTask[7].tQTaskChildren.ptTail;
  v22 = Game_ptGame;
  *(_DWORD *)&ptQTask[30].eQTaskType = igi2_frame.pbSignal;
  igi2_frame.ptDynCubeObj = sqrt(v21 * v21 + v20 * v20 + v19 * v19) + *(float *)&ptQTask[8].ptNext;
  World_MoveDynCubeObjRadius(v22->ptWorld, (struct DynCubeObj_s *)ptQTask, &igi2_frame.ptPos1, igi2_frame.ptDynCubeObj);
  ModelObj_UpdateAttachments((struct ModelObj_s *)ptQTask);
  v23 = igi2_frame.ptSpeed.vX;
  vY = igi2_frame.ptSpeed.vY;
  vZ = igi2_frame.ptSpeed.vZ;
  *(float *)&ptQTask[40].ptNext = igi2_frame.ptSpeed.vX - *(float *)&ptQTask[38].tQTaskRefList.ptTail;
  *(float *)&ptQTask[40].ptPrev = igi2_frame.ptSpeed.vY - *(float *)&ptQTask[38].ptParent;
  v26 = igi2_frame.ptSpeed.vZ - *(float *)&ptQTask[38].eQTaskType;
  *(float *)&ptQTask[38].tQTaskRefList.ptTail = v23;
  v27 = igi2_frame.isForceUpdatePosition;
  *(float *)&ptQTask[38].ptParent = vY;
  v28 = igi2_frame.v35;
  *(float *)&ptQTask[40].tQTaskChildren.ptHead = v26;
  *(float *)&ptQTask[38].eQTaskType = vZ;
  Human_UpdatePlatformPos(ptQTask, v28, v27);
  qmemcpy(&igi2_frame.ptPos1, &ptQTask[1], sizeof(igi2_frame.ptPos1));
  v29 = igi2_frame.ptPos1.vX - *(double *)&ptQTask[39].tQTaskChildren.ptTail;
  v30 = igi2_frame.ptPos1.vY - *(double *)&ptQTask[39].tQTaskRefList.ptMiddle;
  igi2_frame.ptPos1.vZ = igi2_frame.ptPos1.vZ - *(double *)&ptQTask[39].ptParent;
  *(float *)&ptQTask[39].ptNext = v29;
  *(float *)&ptQTask[39].ptPrev = v30;
  *(float *)&ptQTask[39].tQTaskChildren.ptHead = igi2_frame.ptPos1.vZ;
  qmemcpy(&ptQTask[39].tQTaskChildren.ptTail, &ptQTask[1], 0x18u);
}

// source: j/0/human/human.c:5439  [anchor-mhash]
void __cdecl Human_Attach(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { float ptDynCubeObj; };
    struct { char igi2_o1[20]; double v12[3]; };
    struct { char igi2_o2[44]; struct real64x3_t ptNewPos; };
    char igi2_extent[68];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QReference_s *ptTail; // eax
  struct QTask_s *ptHead; // edx
  char v3; // cl
  double v4; // st7
  double v5; // st7
  double v6; // st7
  double v7; // st6
  double v8; // st7
  double v9; // st6
  double v10; // st5

  ptTail = ptQTask[44].tQTaskRefList.ptTail;
  LODWORD(igi2_frame.v12[0]) = ptQTask[38].ptPrev;
  ptHead = ptQTask[38].tQTaskChildren.ptHead;
  LODWORD(igi2_frame.v12[1]) = ptQTask[38].tQTaskChildren.ptMiddle;
  v3 = (char)ptQTask[36].tQTaskChildren.ptTail;
  HIDWORD(igi2_frame.v12[0]) = ptHead;
  if ( v3 )
  {
    v6 = *(float *)&igi2_frame.v12[1];
  }
  else
  {
    v4 = *(float *)igi2_frame.v12 + *(float *)&ptQTask[36].ptPrev;
    ptQTask[36].ptPrev = nullptr;
    *(float *)igi2_frame.v12 = v4;
    v5 = *((float *)igi2_frame.v12 + 1) + *(float *)&ptQTask[36].tQTaskChildren.ptHead;
    ptQTask[36].tQTaskChildren.ptHead = nullptr;
    *((float *)igi2_frame.v12 + 1) = v5;
    v6 = *(float *)&igi2_frame.v12[1] + *(float *)&ptQTask[36].tQTaskChildren.ptMiddle;
    ptQTask[36].tQTaskChildren.ptMiddle = nullptr;
  }
  v7 = *(float *)igi2_frame.v12 * *(float *)&ptTail[10].ptPrev
     + v6 * *(float *)&ptTail[12].ptPrev
     + *((float *)igi2_frame.v12 + 1) * *(float *)&ptTail[11].ptPrev;
  *((float *)&igi2_frame.ptNewPos.vX + 1) = v6 * *(float *)&ptTail[12].pxObject
                               + *((float *)igi2_frame.v12 + 1) * *(float *)&ptTail[11].pxObject
                               + *(float *)igi2_frame.v12 * *(float *)&ptTail[10].pxObject;
  *(float *)&igi2_frame.ptNewPos.vY = *(float *)igi2_frame.v12 * *(float *)&ptTail[11].ptNext
                         + v6 * *(float *)&ptTail[13].ptNext
                         + *((float *)igi2_frame.v12 + 1) * *(float *)&ptTail[12].ptNext;
  v8 = v7 + *(double *)&ptQTask[44].ptParent;
  *(double *)&ptQTask[44].ptParent = v8;
  v9 = *((float *)&igi2_frame.ptNewPos.vX + 1) + *(double *)&ptQTask[45].ptNext;
  *(double *)&ptQTask[45].ptNext = v9;
  v10 = *(float *)&igi2_frame.ptNewPos.vY + *(double *)&ptQTask[45].tQTaskChildren.ptHead;
  *(double *)&ptQTask[45].tQTaskChildren.ptHead = v10;
  igi2_frame.v12[0] = *(float *)&ptTail[11].ptNext * v10 + *(float *)&ptTail[10].ptPrev * v8 + *(float *)&ptTail[10].pxObject * v9;
  igi2_frame.v12[1] = *(float *)&ptTail[11].pxObject * v9 + *(float *)&ptTail[12].ptNext * v10 + *(float *)&ptTail[11].ptPrev * v8;
  igi2_frame.v12[2] = *(float *)&ptTail[12].pxObject * v9 + *(float *)&ptTail[13].ptNext * v10 + *(float *)&ptTail[12].ptPrev * v8;
  qmemcpy(&igi2_frame.ptNewPos, igi2_frame.v12, sizeof(igi2_frame.ptNewPos));
  igi2_frame.ptNewPos.vX = igi2_frame.v12[0] + *(double *)&ptTail[3].ptPrev;
  igi2_frame.ptNewPos.vY = igi2_frame.ptNewPos.vY + *(double *)&ptTail[4].ptNext;
  igi2_frame.ptNewPos.vZ = igi2_frame.ptNewPos.vZ + *(double *)&ptTail[4].pxObject;
  igi2_frame.ptDynCubeObj = sqrt(
                   *(float *)&ptQTask[7].tQTaskChildren.ptTail * *(float *)&ptQTask[7].tQTaskChildren.ptTail
                 + *(float *)&ptQTask[7].tQTaskRefList.ptHead * *(float *)&ptQTask[7].tQTaskRefList.ptHead
                 + *(float *)&ptQTask[7].tQTaskRefList.ptMiddle * *(float *)&ptQTask[7].tQTaskRefList.ptMiddle)
               + *(float *)&ptQTask[8].ptNext;
  World_MoveDynCubeObjRadius(Game_ptGame->ptWorld, (struct DynCubeObj_s *)ptQTask, &igi2_frame.ptNewPos, igi2_frame.ptDynCubeObj);
  ModelObj_UpdateAttachments((struct ModelObj_s *)ptQTask);
  ptQTask[36].ptPrev = nullptr;
  ptQTask[36].tQTaskChildren.ptHead = nullptr;
  ptQTask[36].tQTaskChildren.ptMiddle = nullptr;
}

// source: j/0/human/human.c:5485  [anchor-callee]
struct QTask_s *__cdecl Human_Notify(struct QTask_s *ptQTask)
{
  int v1; // esi
  long double v2; // st7
  struct QTask_s *result; // eax
  int v4; // edi
  struct NotifyContext_t tNotifyContext; // [esp+8h] [ebp-2Ch] BYREF

  tNotifyContext.ptQTask = ptQTask;
  qmemcpy(&tNotifyContext.tPos, &ptQTask[1], sizeof(tNotifyContext.tPos));
  tNotifyContext.tPos.vZ = tNotifyContext.tPos.vZ + 4096.0;
  v1 = 0;
  v2 = sqrt(
         *(float *)&ptQTask[7].tQTaskChildren.ptTail * *(float *)&ptQTask[7].tQTaskChildren.ptTail
       + *(float *)&ptQTask[7].tQTaskRefList.ptHead * *(float *)&ptQTask[7].tQTaskRefList.ptHead
       + *(float *)&ptQTask[7].tQTaskRefList.ptMiddle * *(float *)&ptQTask[7].tQTaskRefList.ptMiddle)
     + *(float *)&ptQTask[8].ptNext;
  result = (struct QTask_s *)GameFunctions_ptNotifyQTaskList;
  tNotifyContext.vRadius = v2;
  if ( GameFunctions_ptNotifyQTaskList->nTask > 0 )
  {
    v4 = 8;
    do
    {
      ((void (__cdecl *)(_DWORD, struct NotifyContext_t *))QTask_aatQTaskFinalEvent[GameFunctions_eNotifyQTaskEvent][(*(struct QTask_s **)((char *)&result->ptNext + v4))->eQTaskType].pfHandler)(
        *(struct QTask_s **)((char *)&result->ptNext + v4),
        &tNotifyContext);
      result = (struct QTask_s *)GameFunctions_ptNotifyQTaskList;
      ++v1;
      v4 += 4;
    }
    while ( v1 < GameFunctions_ptNotifyQTaskList->nTask );
  }
  return result;
}

// source: j/0/human/human.c:5520  [size]
int __cdecl Human_GetState(struct QTask_s *ptQTask)
{
  return (int)ptQTask[31].ptPrev;
}

// source: j/0/human/human.c:5538  [size]
int __cdecl Human_GetTeam(struct QTask_s *ptQTask)
{
  return (int)ptQTask[10].tQTaskRefList.ptTail;
}

// source: j/0/human/human.c:5556  [size]
struct real64x3_t *__cdecl Human_GetPos(struct QTask_s *ptHumanQTask)
{
  return (struct real64x3_t *)&ptHumanQTask[1];
}

// source: j/0/human/human.c:5574  [size]
struct real32x9_t *__cdecl Human_GetOrientation(struct QTask_s *ptHumanQTask)
{
  return (struct real32x9_t *)&ptHumanQTask[3].ptPrev;
}

// source: j/0/human/human.c:5592  [anchor-mhash]
enum bool __cdecl Human_IsPlayer(struct QTask_s *ptQTask)
{
  struct QReference_s *v1; // eax
  struct QTask_s *pxObject; // ecx

  v1 = Game_ptGame->aptPlayerQTaskRef[2];
  pxObject = nullptr;
  if ( v1 )
    pxObject = (struct QTask_s *)v1->pxObject;
  return ptQTask == pxObject;
}

// source: j/0/human/human.c:5615  [anchor-mhash]
enum bool __cdecl Human_IsAI(struct QTask_s *ptQTask)
{
  enum bool result; // eax

  result = QTask_IsQTaskTypeDerived(ptQTask->eQTaskType, Human_eQTaskType);
  if ( result )
    return ptQTask[48].ptParent != nullptr;
  return result;
}

// source: j/0/human/human.c:5646  [size]
enum bool __cdecl Human_IsDead(struct QTask_s *ptQTask)
{
  return SLOBYTE(ptQTask[29].tQTaskRefList.ptHead);
}

// source: j/0/human/human.c:5664  [size]
enum bool __cdecl Human_IsActive(struct QTask_s *ptQTask)
{
  return SBYTE1(ptQTask[29].tQTaskRefList.ptHead);
}

// source: j/0/human/human.c:5682  [anchor-callee]
void __cdecl Human_PopPosition(struct QTask_s *ptQTask, struct real64x3_t *ptPos)
{
  #pragma pack(push, 1)
  union
  {
    struct { float ptDynCubeObj; };
    struct { char igi2_o1[20]; double v14[5]; };
    struct { char igi2_o2[60]; _QWORD v15[5]; };
    char igi2_extent[104];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QReference_s *ptMiddle; // eax
  char *pxObject; // edx
  unsigned __int16 v4; // si
  void *v5; // esi
  void *v6; // eax
  double v7; // st7
  unsigned int v8; // eax
  unsigned int v9; // edx
  int v10; // eax
  bool v11; // zf
  double v12; // st7

  igi2_frame.ptDynCubeObj = sqrt(
                   *(float *)&ptQTask[7].tQTaskChildren.ptTail * *(float *)&ptQTask[7].tQTaskChildren.ptTail
                 + *(float *)&ptQTask[7].tQTaskRefList.ptHead * *(float *)&ptQTask[7].tQTaskRefList.ptHead
                 + *(float *)&ptQTask[7].tQTaskRefList.ptMiddle * *(float *)&ptQTask[7].tQTaskRefList.ptMiddle)
               + *(float *)&ptQTask[8].ptNext;
  World_MoveDynCubeObjRadius(Game_ptGame->ptWorld, (struct DynCubeObj_s *)ptQTask, ptPos, igi2_frame.ptDynCubeObj);
  ModelObj_UpdateAttachments((struct ModelObj_s *)ptQTask);
  HumanView_PopPosition(ptQTask[33].tQTaskChildren.ptTail, ptQTask);
  *(double *)&ptQTask[47].tQTaskChildren.ptHead = ptPos->vX;
  *(double *)&ptQTask[47].tQTaskChildren.ptTail = ptPos->vY;
  ptQTask[38].tQTaskChildren.ptTail = nullptr;
  ptQTask[38].tQTaskRefList.ptHead = nullptr;
  ptQTask[38].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[51].tQTaskChildren.ptTail = (struct QTask_s *)1;
  ptMiddle = ptQTask[44].tQTaskRefList.ptMiddle;
  if ( ptMiddle )
  {
    pxObject = (char *)ptMiddle->pxObject;
    if ( pxObject )
    {
      v4 = *((_WORD *)pxObject + 18);
      if ( QTask_IsQTaskTypeDerived(v4, RigidDynCubeObj_eQTaskType) )
      {
        qmemcpy(igi2_frame.v15, pxObject + 124, sizeof(igi2_frame.v15));
        v5 = pxObject + 40;
      }
      else
      {
        if ( QTask_IsQTaskTypeDerived(v4, Graph_eQTaskType) == false
          || (v6 = *((void **)pxObject + 13)) == nullptr )
        {
          HIBYTE(ptQTask[74].ptPrev) = 0;
          return;
        }
        qmemcpy(igi2_frame.v15, *((void **)pxObject + 14), sizeof(igi2_frame.v15));
        v5 = v6;
      }
      v7 = *(double *)&ptQTask[1].ptNext;
      v8 = igi2_frame.v15[3];
      v9 = HIDWORD(igi2_frame.v15[1]);
      qmemcpy(igi2_frame.v14, v5, 0x18u);
      *(double *)&ptQTask[70].ptNext = v7 - igi2_frame.v14[0];
      *(double *)&ptQTask[70].tQTaskChildren.ptHead = *(double *)&ptQTask[1].tQTaskChildren.ptHead - igi2_frame.v14[1];
      *(double *)&ptQTask[70].tQTaskChildren.ptTail = *(double *)&ptQTask[1].tQTaskChildren.ptTail - igi2_frame.v14[2];
      qmemcpy(&ptQTask[71].tQTaskChildren, igi2_frame.v14, 0x18u);
      qmemcpy(&ptQTask[70].tQTaskRefList.ptMiddle, igi2_frame.v14, 0x18u);
      *(_QWORD *)&igi2_frame.v14[0] = __PAIR64__(v9, igi2_frame.v15[0]);
      *(_QWORD *)&igi2_frame.v14[1] = __PAIR64__(HIDWORD(igi2_frame.v15[0]), v8);
      *(_QWORD *)&igi2_frame.v14[2] = __PAIR64__(HIDWORD(igi2_frame.v15[3]), igi2_frame.v15[2]);
      *(_QWORD *)&igi2_frame.v14[3] = __PAIR64__(HIDWORD(igi2_frame.v15[2]), igi2_frame.v15[1]);
      igi2_frame.v14[4] = *(double *)&igi2_frame.v15[4];
      v10 = HIDWORD(igi2_frame.v15[4]);
      qmemcpy(&ptQTask[72].ptPrev, igi2_frame.v14, sizeof(struct QTask_s));
      v11 = BYTE1(ptQTask[74].ptPrev) == 0;
      ptQTask[71].ptParent = nullptr;
      *(_DWORD *)&ptQTask[71].eQTaskType = 0;
      ptQTask[72].ptNext = nullptr;
      if ( !v11 )
      {
        *(float *)igi2_frame.v14 = *(float *)&igi2_frame.v15[3] * *(float *)&ptQTask[3].tQTaskRefList.ptTail
                      + *(float *)igi2_frame.v15 * *(float *)&ptQTask[3].ptPrev
                      + *((float *)&igi2_frame.v15[1] + 1) * *(float *)&ptQTask[3].tQTaskChildren.ptTail;
        *((float *)igi2_frame.v14 + 1) = *(float *)&igi2_frame.v15[3] * *(float *)&ptQTask[3].ptParent
                            + *(float *)igi2_frame.v15 * *(float *)&ptQTask[3].tQTaskChildren.ptHead
                            + *((float *)&igi2_frame.v15[1] + 1) * *(float *)&ptQTask[3].tQTaskRefList.ptHead;
        *(float *)&igi2_frame.v14[1] = *(float *)&igi2_frame.v15[3] * *(float *)&ptQTask[3].eQTaskType
                          + *(float *)igi2_frame.v15 * *(float *)&ptQTask[3].tQTaskChildren.ptMiddle
                          + *((float *)&igi2_frame.v15[1] + 1) * *(float *)&ptQTask[3].tQTaskRefList.ptMiddle;
        *((float *)&igi2_frame.v14[1] + 1) = *((float *)&igi2_frame.v15[3] + 1) * *(float *)&ptQTask[3].tQTaskRefList.ptTail
                                + *((float *)igi2_frame.v15 + 1) * *(float *)&ptQTask[3].ptPrev
                                + *(float *)&igi2_frame.v15[2] * *(float *)&ptQTask[3].tQTaskChildren.ptTail;
        *(float *)&igi2_frame.v14[2] = *((float *)&igi2_frame.v15[3] + 1) * *(float *)&ptQTask[3].ptParent
                          + *((float *)igi2_frame.v15 + 1) * *(float *)&ptQTask[3].tQTaskChildren.ptHead
                          + *(float *)&igi2_frame.v15[2] * *(float *)&ptQTask[3].tQTaskRefList.ptHead;
        *((float *)&igi2_frame.v14[2] + 1) = *((float *)&igi2_frame.v15[3] + 1) * *(float *)&ptQTask[3].eQTaskType
                                + *((float *)igi2_frame.v15 + 1) * *(float *)&ptQTask[3].tQTaskChildren.ptMiddle
                                + *(float *)&igi2_frame.v15[2] * *(float *)&ptQTask[3].tQTaskRefList.ptMiddle;
        *(float *)&igi2_frame.v14[3] = *(float *)&igi2_frame.v15[4] * *(float *)&ptQTask[3].tQTaskRefList.ptTail
                          + *(float *)&igi2_frame.v15[1] * *(float *)&ptQTask[3].ptPrev
                          + *((float *)&igi2_frame.v15[2] + 1) * *(float *)&ptQTask[3].tQTaskChildren.ptTail;
        *((float *)&igi2_frame.v14[3] + 1) = *(float *)&igi2_frame.v15[4] * *(float *)&ptQTask[3].ptParent
                                + *(float *)&igi2_frame.v15[1] * *(float *)&ptQTask[3].tQTaskChildren.ptHead
                                + *((float *)&igi2_frame.v15[2] + 1) * *(float *)&ptQTask[3].tQTaskRefList.ptHead;
        v12 = *(float *)&igi2_frame.v15[4] * *(float *)&ptQTask[3].eQTaskType
            + *(float *)&igi2_frame.v15[1] * *(float *)&ptQTask[3].tQTaskChildren.ptMiddle;
        HIDWORD(igi2_frame.v14[4]) = (char *)&ptQTask[4].ptNext->ptNext + v10 + 1;
        *(float *)&igi2_frame.v14[4] = v12 + *((float *)&igi2_frame.v15[2] + 1) * *(float *)&ptQTask[3].tQTaskRefList.ptMiddle;
        qmemcpy(&ptQTask[73].ptPrev, igi2_frame.v14, sizeof(struct QTask_s));
      }
      BYTE1(ptQTask[74].ptPrev) = 0;
      HIBYTE(ptQTask[74].ptPrev) = 1;
    }
  }
}

// source: j/0/human/human.c:5721  [anchor-callee]
void __cdecl Human_PopOrientation(struct QTask_s *ptQTask, float vGamma)
{
  long double v2; // st7
  long double v3; // st6

  v2 = sin(vGamma);
  *(float *)&ptQTask[34].tQTaskChildren.ptHead = vGamma;
  *(float *)&ptQTask[34].ptPrev = vGamma;
  ptQTask[3].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[3].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[3].tQTaskRefList.ptTail = nullptr;
  ptQTask[3].ptParent = nullptr;
  *(_DWORD *)&ptQTask[3].eQTaskType = 1065353216;
  ptQTask[4].ptNext = nullptr;
  v3 = cos(vGamma);
  *(float *)&ptQTask[3].ptPrev = v3;
  *(float *)&ptQTask[3].tQTaskChildren.ptHead = -v2;
  *(float *)&ptQTask[3].tQTaskChildren.ptTail = v2;
  *(float *)&ptQTask[3].tQTaskRefList.ptHead = v3;
  BoneDynCubeObj_UpdateHierarchy((struct BoneDynCubeObj_s *)ptQTask);
  ptQTask[51].tQTaskChildren.ptTail = (struct QTask_s *)1;
  Human_UpdatePlatformPos(ptQTask, false, true);
}

// source: j/0/human/human.c:5753  [anchor-callee]
void __cdecl Human_SnapToGround(struct QTask_s *ptQTask)
{
  struct real64x3_t tPos; // [esp+8h] [ebp-1Ch] BYREF

  qmemcpy(&tPos, &ptQTask[1], sizeof(tPos));
  Human_GroundCollision(
    ptQTask,
    &tPos,
    &tPos,
    (struct real32x3_t *)&tPos,
    (unsigned int *)&ptQTask[30].eQTaskType,
    4096000.0);
  Human_PopPosition(ptQTask, &tPos);
}

// source: j/0/human/human.c:5788  [anchor-mhash]
void __cdecl Human_SnapFromGround(struct QTask_s *ptQTask)
{
  struct QReference_s *ptMiddle; // eax

  ptMiddle = ptQTask[44].tQTaskRefList.ptMiddle;
  *(_DWORD *)&ptQTask[30].eQTaskType &= ~2u;
  if ( ptMiddle && ptMiddle->pxObject )
  {
    QReference_Delete(ptMiddle, &QTask_tQTaskRefPool);
    ptQTask[44].tQTaskRefList.ptMiddle = nullptr;
    HIBYTE(ptQTask[74].ptPrev) = 0;
  }
  *(_DWORD *)&ptQTask[42].eQTaskType = 0;
}

// source: j/0/human/human.c:5820  [anchor-mhash]
struct real32x9_t *__cdecl Human_AttachToTask(
        struct QTask_s *ptQTask,
        struct QTask_s *ptAttachQTask,
        struct real64x3_t *ptAttachPos,
        struct real32x9_t *ptAttachOrientation)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct real64x3_t Real64x3_RotateInverse_tTemp; };
    struct { char igi2_o1[24]; struct QTask_s *ptMiddle; };
    struct { char igi2_o2[28]; struct QReference_s *v22; };
    struct { char igi2_o3[32]; float v23; };
    struct { char igi2_o4[40]; struct real32x9_t Real32x9_Multiply_tTemp; };
    char igi2_extent[84];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  double v4; // st7
  double v5; // st6
  double v6; // st5
  double v7; // st7
  double v8; // st6
  double v9; // st5
  double v10; // st4
  double v11; // st3
  double v12; // st4
  double v13; // st3
  float v14; // ecx
  struct QTask_s *ptNext; // edx
  double v16; // st4
  double v17; // st7
  double v18; // st6
  struct real32x9_t *result; // eax

  ptQTask[44].tQTaskRefList.ptTail = (struct QReference_s *)ptAttachQTask;
  v4 = ptAttachPos->vX - *(double *)&ptAttachQTask[1].ptNext;
  v5 = ptAttachPos->vY - *(double *)&ptAttachQTask[1].tQTaskChildren.ptHead;
  v6 = ptAttachPos->vZ - *(double *)&ptAttachQTask[1].tQTaskChildren.ptTail;
  igi2_frame.Real64x3_RotateInverse_tTemp.vX = *(float *)&ptAttachQTask[3].tQTaskChildren.ptTail * v5
                                  + *(float *)&ptAttachQTask[3].tQTaskRefList.ptTail * v6
                                  + *(float *)&ptAttachQTask[3].ptPrev * v4;
  igi2_frame.Real64x3_RotateInverse_tTemp.vY = *(float *)&ptAttachQTask[3].tQTaskRefList.ptHead * v5
                                  + *(float *)&ptAttachQTask[3].ptParent * v6
                                  + *(float *)&ptAttachQTask[3].tQTaskChildren.ptHead * v4;
  igi2_frame.Real64x3_RotateInverse_tTemp.vZ = *(float *)&ptAttachQTask[3].tQTaskRefList.ptMiddle * v5
                                  + *(float *)&ptAttachQTask[3].eQTaskType * v6
                                  + *(float *)&ptAttachQTask[3].tQTaskChildren.ptMiddle * v4;
  qmemcpy(&ptQTask[44].ptParent, &igi2_frame.Real64x3_RotateInverse_tTemp, 0x18u);
  v7 = *(float *)&ptAttachQTask[3].ptPrev;
  v8 = *(float *)&ptAttachQTask[3].tQTaskChildren.ptTail;
  v9 = *(float *)&ptAttachQTask[3].tQTaskRefList.ptTail;
  v10 = v9 * ptAttachOrientation->tZ.vX;
  v11 = v8 * ptAttachOrientation->tY.vX;
  HIDWORD(igi2_frame.Real64x3_RotateInverse_tTemp.vY) = ptAttachQTask[3].tQTaskChildren.ptHead;
  v12 = v10 + v11;
  LODWORD(igi2_frame.Real64x3_RotateInverse_tTemp.vZ) = ptAttachQTask[3].tQTaskRefList.ptHead;
  v13 = v7 * ptAttachOrientation->tX.vX;
  HIDWORD(igi2_frame.Real64x3_RotateInverse_tTemp.vZ) = ptAttachQTask[3].ptParent;
  igi2_frame.ptMiddle = ptAttachQTask[3].tQTaskChildren.ptMiddle;
  igi2_frame.v22 = ptAttachQTask[3].tQTaskRefList.ptMiddle;
  igi2_frame.Real32x9_Multiply_tTemp.tX.vX = v12 + v13;
  v14 = *(float *)&ptAttachQTask[3].eQTaskType;
  ptNext = ptAttachQTask[4].ptNext;
  v16 = v7 * ptAttachOrientation->tX.vY;
  igi2_frame.v23 = v14;
  igi2_frame.Real32x9_Multiply_tTemp.tX.vY = v16 + v9 * ptAttachOrientation->tZ.vY + v8 * ptAttachOrientation->tY.vY;
  igi2_frame.Real32x9_Multiply_tTemp.tX.vZ = v9 * ptAttachOrientation->tZ.vZ
                                + v8 * ptAttachOrientation->tY.vZ
                                + v7 * ptAttachOrientation->tX.vZ;
  igi2_frame.Real32x9_Multiply_tTemp.tY.vX = *((float *)&igi2_frame.Real64x3_RotateInverse_tTemp.vZ + 1) * ptAttachOrientation->tZ.vX
                                + *(float *)&igi2_frame.Real64x3_RotateInverse_tTemp.vZ * ptAttachOrientation->tY.vX
                                + *((float *)&igi2_frame.Real64x3_RotateInverse_tTemp.vY + 1) * ptAttachOrientation->tX.vX;
  igi2_frame.Real32x9_Multiply_tTemp.tY.vY = *((float *)&igi2_frame.Real64x3_RotateInverse_tTemp.vY + 1) * ptAttachOrientation->tX.vY
                                + *((float *)&igi2_frame.Real64x3_RotateInverse_tTemp.vZ + 1) * ptAttachOrientation->tZ.vY
                                + *(float *)&igi2_frame.Real64x3_RotateInverse_tTemp.vZ * ptAttachOrientation->tY.vY;
  igi2_frame.Real32x9_Multiply_tTemp.tY.vZ = *((float *)&igi2_frame.Real64x3_RotateInverse_tTemp.vZ + 1) * ptAttachOrientation->tZ.vZ
                                + *(float *)&igi2_frame.Real64x3_RotateInverse_tTemp.vZ * ptAttachOrientation->tY.vZ
                                + *((float *)&igi2_frame.Real64x3_RotateInverse_tTemp.vY + 1) * ptAttachOrientation->tX.vZ;
  igi2_frame.Real32x9_Multiply_tTemp.tZ.vX = v14 * ptAttachOrientation->tZ.vX
                                + *(float *)&igi2_frame.v22 * ptAttachOrientation->tY.vX
                                + *(float *)&igi2_frame.ptMiddle * ptAttachOrientation->tX.vX;
  igi2_frame.Real32x9_Multiply_tTemp.tZ.vY = *(float *)&igi2_frame.ptMiddle * ptAttachOrientation->tX.vY
                                + v14 * ptAttachOrientation->tZ.vY
                                + *(float *)&igi2_frame.v22 * ptAttachOrientation->tY.vY;
  v17 = v14 * ptAttachOrientation->tZ.vZ + *(float *)&igi2_frame.v22 * ptAttachOrientation->tY.vZ;
  v18 = *(float *)&igi2_frame.ptMiddle * ptAttachOrientation->tX.vZ;
  result = (struct real32x9_t *)ptAttachOrientation->nOps;
  igi2_frame.Real32x9_Multiply_tTemp.nOps = (int)&ptNext->ptNext + (_DWORD)result + 1;
  ptQTask[48].ptNext = (struct QTask_s *)1;
  *(_DWORD *)&ptQTask[47].eQTaskType = 0;
  igi2_frame.Real32x9_Multiply_tTemp.tZ.vZ = v17 + v18;
  qmemcpy(&ptQTask[45].tQTaskChildren.ptTail, &igi2_frame.Real32x9_Multiply_tTemp, sizeof(struct QTask_s));
  return result;
}

// source: j/0/human/human.c:5861  [size]
struct QTask_s *__cdecl Human_DetachFromTask(struct QTask_s *ptQTask)
{
  ptQTask[44].tQTaskRefList.ptTail = nullptr;
  ptQTask[48].ptNext = nullptr;
  *(_DWORD *)&ptQTask[47].eQTaskType = 1;
  return ptQTask;
}

// source: j/0/human/human.c:5881  [size]
struct QTask_s *__cdecl Human_DisableCollision(struct QTask_s *ptQTask)
{
  LOBYTE(ptQTask[40].tQTaskChildren.ptMiddle) = 1;
  return ptQTask;
}

// source: j/0/human/human.c:5898  [size]
struct QTask_s *__cdecl Human_EnableCollision(struct QTask_s *ptQTask)
{
  LOBYTE(ptQTask[40].tQTaskChildren.ptMiddle) = 0;
  return ptQTask;
}

// source: j/0/human/human.c:5915  [size]
struct QTask_s *__cdecl Human_DisableDeltaTranslation(struct QTask_s *ptQTask)
{
  LOBYTE(ptQTask[36].tQTaskChildren.ptTail) = 1;
  ptQTask[36].ptPrev = nullptr;
  ptQTask[36].tQTaskChildren.ptHead = nullptr;
  ptQTask[36].tQTaskChildren.ptMiddle = nullptr;
  return ptQTask;
}

// source: j/0/human/human.c:5933  [size]
struct QTask_s *__cdecl Human_EnableDeltaTranslation(struct QTask_s *ptQTask)
{
  LOBYTE(ptQTask[36].tQTaskChildren.ptTail) = 0;
  return ptQTask;
}

// source: j/0/human/human.c:5950  [size]
struct QTask_s *__cdecl Human_DisableDeltaTranslationScale(struct QTask_s *ptQTask)
{
  BYTE1(ptQTask[36].tQTaskChildren.ptTail) = 1;
  return ptQTask;
}

// source: j/0/human/human.c:5967  [size]
struct QTask_s *__cdecl Human_EnableDeltaTranslationScale(struct QTask_s *ptQTask)
{
  BYTE1(ptQTask[36].tQTaskChildren.ptTail) = 0;
  return ptQTask;
}

// source: j/0/human/human.c:5984  [anchor-mhash]
void __cdecl Human_LockChannel(struct QTask_s *ptQTask)
{
  memset(&ptQTask[12].ptParent, 0, 0xFCu);
  memset(&ptQTask[19].ptPrev, 0, 0xFCu);
  LOBYTE(ptQTask[25].tQTaskChildren.ptTail) = 1;
}

// source: j/0/human/human.c:6005  [size]
struct QTask_s *__cdecl Human_UnlockChannel(struct QTask_s *ptQTask)
{
  LOBYTE(ptQTask[25].tQTaskChildren.ptTail) = 0;
  return ptQTask;
}

// source: j/0/human/human.c:6022  [size]
struct QTask_s *__cdecl Human_LockOrientation(struct QTask_s *ptQTask)
{
  LOBYTE(ptQTask[34].tQTaskChildren.ptMiddle) = 1;
  return ptQTask;
}

// source: j/0/human/human.c:6039  [size]
struct QTask_s *__cdecl Human_UnlockOrientation(struct QTask_s *ptQTask)
{
  LOBYTE(ptQTask[34].tQTaskChildren.ptMiddle) = 0;
  return ptQTask;
}

// source: j/0/human/human.c:6056  [size]
struct QTask_s *__cdecl Human_LockActivate(struct QTask_s *ptQTask)
{
  LOBYTE(ptQTask[46].tQTaskRefList.ptMiddle) = 1;
  return ptQTask;
}

// source: j/0/human/human.c:6073  [size]
struct QTask_s *__cdecl Human_UnlockActivate(struct QTask_s *ptQTask)
{
  LOBYTE(ptQTask[46].tQTaskRefList.ptMiddle) = 0;
  BYTE1(ptQTask[46].tQTaskRefList.ptMiddle) = 1;
  return ptQTask;
}

// source: j/0/human/human.c:6095  [anchor-callee]
void __cdecl Human_UpdatePlatformMovement(
        struct QTask_s *ptQTask,
        enum bool isUpdatePosition,
        enum bool isUpdateOrientation,
        struct real64x3_t *ptNewPos)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct real32x9_t tPlatformOrientation; };
    struct { char igi2_o1[44]; struct real32x9_t Real32x9_Multiply_tTemp; };
    struct { char igi2_o2[84]; struct QTask_s *vGamma; };
    struct { char igi2_o3[88]; struct real64x3_t tPlatformPos; };
    struct { char igi2_o4[112]; float vAlpha; };
    struct { char igi2_o5[116]; float vBeta; };
    struct { char igi2_o6[120]; struct real32x9_t tNewOrientation; };
    char igi2_extent[160];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QReference_s *ptMiddle; // eax
  char *pxObject; // edx
  unsigned __int16 v6; // si
  void *v7; // esi
  void *v8; // eax
  double v9; // st7
  double v10; // st6
  struct QTask_s *v11; // ecx
  double vX; // st7
  double v13; // st7
  double v14; // st6
  double v15; // st5
  double v16; // st4
  double vZ; // st3
  double v18; // st7
  double v19; // st6
  double v20; // st7
  double v21; // st6
  double v22; // st5

  if ( ptQTask[51].tQTaskChildren.ptTail )
  {
    ptQTask[51].tQTaskChildren.ptTail = nullptr;
    return;
  }
  if ( HIBYTE(ptQTask[74].ptPrev) )
  {
    ptMiddle = ptQTask[44].tQTaskRefList.ptMiddle;
    if ( ptMiddle )
    {
      pxObject = (char *)ptMiddle->pxObject;
      if ( pxObject )
      {
        v6 = *((_WORD *)pxObject + 18);
        if ( QTask_IsQTaskTypeDerived(v6, RigidDynCubeObj_eQTaskType) )
        {
          qmemcpy(&igi2_frame.tPlatformOrientation, pxObject + 124, sizeof(igi2_frame.tPlatformOrientation));
          v7 = pxObject + 40;
        }
        else
        {
          if ( QTask_IsQTaskTypeDerived(v6, Graph_eQTaskType) == false )
            return;
          v8 = *((void **)pxObject + 13);
          if ( !v8 )
            return;
          qmemcpy(&igi2_frame.tPlatformOrientation, *((void **)pxObject + 14), sizeof(igi2_frame.tPlatformOrientation));
          v7 = v8;
        }
        qmemcpy(&igi2_frame.tPlatformPos, v7, sizeof(igi2_frame.tPlatformPos));
        if ( isUpdateOrientation )
        {
          igi2_frame.Real32x9_Multiply_tTemp.tX.vX = igi2_frame.tPlatformOrientation.tX.vZ * *(float *)&ptQTask[73].tQTaskRefList.ptTail
                                        + igi2_frame.tPlatformOrientation.tX.vX * *(float *)&ptQTask[73].ptPrev
                                        + igi2_frame.tPlatformOrientation.tX.vY * *(float *)&ptQTask[73].tQTaskChildren.ptTail;
          igi2_frame.Real32x9_Multiply_tTemp.tX.vY = igi2_frame.tPlatformOrientation.tX.vZ * *(float *)&ptQTask[73].ptParent
                                        + igi2_frame.tPlatformOrientation.tX.vX * *(float *)&ptQTask[73].tQTaskChildren.ptHead
                                        + igi2_frame.tPlatformOrientation.tX.vY * *(float *)&ptQTask[73].tQTaskRefList.ptHead;
          igi2_frame.Real32x9_Multiply_tTemp.tX.vZ = igi2_frame.tPlatformOrientation.tX.vZ * *(float *)&ptQTask[73].eQTaskType
                                        + igi2_frame.tPlatformOrientation.tX.vX * *(float *)&ptQTask[73].tQTaskChildren.ptMiddle
                                        + igi2_frame.tPlatformOrientation.tX.vY * *(float *)&ptQTask[73].tQTaskRefList.ptMiddle;
          igi2_frame.Real32x9_Multiply_tTemp.tY.vX = igi2_frame.tPlatformOrientation.tY.vZ * *(float *)&ptQTask[73].tQTaskRefList.ptTail
                                        + igi2_frame.tPlatformOrientation.tY.vX * *(float *)&ptQTask[73].ptPrev
                                        + igi2_frame.tPlatformOrientation.tY.vY * *(float *)&ptQTask[73].tQTaskChildren.ptTail;
          igi2_frame.Real32x9_Multiply_tTemp.tY.vY = igi2_frame.tPlatformOrientation.tY.vZ * *(float *)&ptQTask[73].ptParent
                                        + igi2_frame.tPlatformOrientation.tY.vX * *(float *)&ptQTask[73].tQTaskChildren.ptHead
                                        + igi2_frame.tPlatformOrientation.tY.vY * *(float *)&ptQTask[73].tQTaskRefList.ptHead;
          igi2_frame.Real32x9_Multiply_tTemp.tY.vZ = igi2_frame.tPlatformOrientation.tY.vZ * *(float *)&ptQTask[73].eQTaskType
                                        + igi2_frame.tPlatformOrientation.tY.vX * *(float *)&ptQTask[73].tQTaskChildren.ptMiddle
                                        + igi2_frame.tPlatformOrientation.tY.vY * *(float *)&ptQTask[73].tQTaskRefList.ptMiddle;
          igi2_frame.Real32x9_Multiply_tTemp.tZ.vX = igi2_frame.tPlatformOrientation.tZ.vZ * *(float *)&ptQTask[73].tQTaskRefList.ptTail
                                        + igi2_frame.tPlatformOrientation.tZ.vX * *(float *)&ptQTask[73].ptPrev
                                        + igi2_frame.tPlatformOrientation.tZ.vY * *(float *)&ptQTask[73].tQTaskChildren.ptTail;
          igi2_frame.Real32x9_Multiply_tTemp.tZ.vY = igi2_frame.tPlatformOrientation.tZ.vZ * *(float *)&ptQTask[73].ptParent
                                        + igi2_frame.tPlatformOrientation.tZ.vX * *(float *)&ptQTask[73].tQTaskChildren.ptHead
                                        + igi2_frame.tPlatformOrientation.tZ.vY * *(float *)&ptQTask[73].tQTaskRefList.ptHead;
          v9 = igi2_frame.tPlatformOrientation.tZ.vZ * *(float *)&ptQTask[73].eQTaskType;
          v10 = igi2_frame.tPlatformOrientation.tZ.vX * *(float *)&ptQTask[73].tQTaskChildren.ptMiddle;
          igi2_frame.Real32x9_Multiply_tTemp.nOps = (int)&ptQTask[74].ptNext->ptNext + igi2_frame.tPlatformOrientation.nOps + 1;
          igi2_frame.Real32x9_Multiply_tTemp.tZ.vZ = v9
                                        + v10
                                        + igi2_frame.tPlatformOrientation.tZ.vY * *(float *)&ptQTask[73].tQTaskRefList.ptMiddle;
          qmemcpy(&igi2_frame.tNewOrientation, &igi2_frame.Real32x9_Multiply_tTemp, sizeof(igi2_frame.tNewOrientation));
          Real32x9_GetAngles(&igi2_frame.tNewOrientation, &igi2_frame.vAlpha, &igi2_frame.vBeta, (float *)&igi2_frame.vGamma);
          v11 = igi2_frame.vGamma;
          ptQTask[34].ptPrev = ptQTask[34].tQTaskChildren.ptHead;
          ptQTask[34].tQTaskChildren.ptHead = v11;
        }
        if ( isUpdatePosition )
        {
          vX = igi2_frame.tPlatformOrientation.tZ.vX;
          qmemcpy(ptNewPos, &igi2_frame.tPlatformPos, sizeof(struct real64x3_t));
          v13 = vX * *(float *)&ptQTask[72].tQTaskChildren.ptMiddle
              + igi2_frame.tPlatformOrientation.tX.vX * *(float *)&ptQTask[72].ptPrev
              + igi2_frame.tPlatformOrientation.tY.vX * *(float *)&ptQTask[72].tQTaskChildren.ptHead;
          v14 = igi2_frame.tPlatformOrientation.tZ.vY * *(float *)&ptQTask[72].tQTaskChildren.ptMiddle
              + igi2_frame.tPlatformOrientation.tX.vY * *(float *)&ptQTask[72].ptPrev
              + igi2_frame.tPlatformOrientation.tY.vY * *(float *)&ptQTask[72].tQTaskChildren.ptHead;
          v15 = igi2_frame.tPlatformOrientation.tZ.vZ * *(float *)&ptQTask[72].tQTaskChildren.ptMiddle
              + igi2_frame.tPlatformOrientation.tX.vZ * *(float *)&ptQTask[72].ptPrev
              + igi2_frame.tPlatformOrientation.tY.vZ * *(float *)&ptQTask[72].tQTaskChildren.ptHead;
          igi2_frame.Real32x9_Multiply_tTemp.tY.vX = igi2_frame.tPlatformOrientation.tZ.vX * *(float *)&ptQTask[72].tQTaskRefList.ptMiddle
                                        + igi2_frame.tPlatformOrientation.tX.vX * *(float *)&ptQTask[72].tQTaskChildren.ptTail
                                        + igi2_frame.tPlatformOrientation.tY.vX * *(float *)&ptQTask[72].tQTaskRefList.ptHead;
          igi2_frame.Real32x9_Multiply_tTemp.tY.vY = igi2_frame.tPlatformOrientation.tZ.vY * *(float *)&ptQTask[72].tQTaskRefList.ptMiddle
                                        + igi2_frame.tPlatformOrientation.tX.vY * *(float *)&ptQTask[72].tQTaskChildren.ptTail
                                        + igi2_frame.tPlatformOrientation.tY.vY * *(float *)&ptQTask[72].tQTaskRefList.ptHead;
          igi2_frame.Real32x9_Multiply_tTemp.tY.vZ = igi2_frame.tPlatformOrientation.tZ.vZ * *(float *)&ptQTask[72].tQTaskRefList.ptMiddle
                                        + igi2_frame.tPlatformOrientation.tX.vZ * *(float *)&ptQTask[72].tQTaskChildren.ptTail
                                        + igi2_frame.tPlatformOrientation.tY.vZ * *(float *)&ptQTask[72].tQTaskRefList.ptHead;
          igi2_frame.Real32x9_Multiply_tTemp.tZ.vX = igi2_frame.tPlatformOrientation.tZ.vX * *(float *)&ptQTask[72].eQTaskType
                                        + igi2_frame.tPlatformOrientation.tX.vX * *(float *)&ptQTask[72].tQTaskRefList.ptTail
                                        + igi2_frame.tPlatformOrientation.tY.vX * *(float *)&ptQTask[72].ptParent;
          igi2_frame.Real32x9_Multiply_tTemp.tZ.vY = igi2_frame.tPlatformOrientation.tZ.vY * *(float *)&ptQTask[72].eQTaskType
                                        + igi2_frame.tPlatformOrientation.tX.vY * *(float *)&ptQTask[72].tQTaskRefList.ptTail
                                        + igi2_frame.tPlatformOrientation.tY.vY * *(float *)&ptQTask[72].ptParent;
          v16 = igi2_frame.tPlatformOrientation.tZ.vZ * *(float *)&ptQTask[72].eQTaskType
              + igi2_frame.tPlatformOrientation.tX.vZ * *(float *)&ptQTask[72].tQTaskRefList.ptTail;
          vZ = igi2_frame.tPlatformOrientation.tY.vZ;
          qmemcpy(&igi2_frame.tPlatformOrientation, &ptQTask[70], 0x18u);
          igi2_frame.Real32x9_Multiply_tTemp.tZ.vZ = v16 + vZ * *(float *)&ptQTask[72].ptParent;
          v18 = v15 * *(double *)&igi2_frame.tPlatformOrientation.tY.vY
              + v14 * *(double *)&igi2_frame.tPlatformOrientation.tX.vZ
              + v13 * *(double *)&igi2_frame.tPlatformOrientation.tX.vX;
          v19 = igi2_frame.Real32x9_Multiply_tTemp.tY.vZ * *(double *)&igi2_frame.tPlatformOrientation.tY.vY
              + igi2_frame.Real32x9_Multiply_tTemp.tY.vY * *(double *)&igi2_frame.tPlatformOrientation.tX.vZ
              + igi2_frame.Real32x9_Multiply_tTemp.tY.vX * *(double *)&igi2_frame.tPlatformOrientation.tX.vX;
          *(double *)&igi2_frame.tPlatformOrientation.tY.vY = igi2_frame.Real32x9_Multiply_tTemp.tZ.vZ
                                                 * *(double *)&igi2_frame.tPlatformOrientation.tY.vY
                                                 + igi2_frame.Real32x9_Multiply_tTemp.tZ.vY
                                                 * *(double *)&igi2_frame.tPlatformOrientation.tX.vZ
                                                 + igi2_frame.Real32x9_Multiply_tTemp.tZ.vX
                                                 * *(double *)&igi2_frame.tPlatformOrientation.tX.vX;
          ptNewPos->vX = v18 + ptNewPos->vX;
          ptNewPos->vY = v19 + ptNewPos->vY;
          ptNewPos->vZ = *(double *)&igi2_frame.tPlatformOrientation.tY.vY + ptNewPos->vZ;
          v20 = igi2_frame.tPlatformPos.vX - *(double *)&ptQTask[70].tQTaskRefList.ptMiddle;
          *(double *)&igi2_frame.tPlatformOrientation.tX.vX = v20;
          v21 = igi2_frame.tPlatformPos.vY - *(double *)&ptQTask[70].ptParent;
          *(double *)&igi2_frame.tPlatformOrientation.tX.vZ = v21;
          v22 = igi2_frame.tPlatformPos.vZ - *(double *)&ptQTask[71].ptNext;
          qmemcpy(&ptQTask[70].tQTaskRefList.ptMiddle, &igi2_frame.tPlatformPos, 0x18u);
          *(double *)&igi2_frame.tPlatformOrientation.tY.vY = v22;
          *(float *)&ptQTask[71].ptParent = v20;
          *(float *)&ptQTask[71].eQTaskType = v21;
          *(float *)&ptQTask[72].ptNext = *(double *)&igi2_frame.tPlatformOrientation.tY.vY;
          BYTE2(ptQTask[74].ptPrev) = Real64x3_Len((struct real64x3_t *)&igi2_frame.tPlatformOrientation) != 0.0;
          qmemcpy(&ptQTask[71].tQTaskChildren, &igi2_frame.tPlatformPos, 0x18u);
        }
      }
    }
  }
}

// source: j/0/human/human.c:6198  [anchor-callee]
void __cdecl Human_SetGroundTask(struct QTask_s *ptQTask, struct QTask_s *ptGroundQTask)
{
  struct QReference_s *ptMiddle; // eax
  struct QTask_s *pxObject; // eax
  struct QReference_s *v4; // eax
  struct QReference_s *v5; // eax
  unsigned __int16 v6; // cx
  unsigned __int16 eQTaskType; // dx

  ptMiddle = ptQTask[44].tQTaskRefList.ptMiddle;
  if ( ptMiddle )
    pxObject = (struct QTask_s *)ptMiddle->pxObject;
  else
    pxObject = nullptr;
  if ( ptGroundQTask != pxObject )
  {
    v4 = ptQTask[44].tQTaskRefList.ptMiddle;
    if ( v4 )
    {
      QReference_Delete(v4, &QTask_tQTaskRefPool);
      ptQTask[44].tQTaskRefList.ptMiddle = nullptr;
    }
    HIBYTE(ptQTask[74].ptPrev) = 0;
    if ( ptGroundQTask )
    {
      v5 = QTask_NewQTaskRef(ptGroundQTask);
      v6 = RigidDynCubeObj_eQTaskType;
      ptQTask[44].tQTaskRefList.ptMiddle = v5;
      eQTaskType = ptGroundQTask->eQTaskType;
      if ( QTask_IsQTaskTypeDerived(eQTaskType, v6) || QTask_IsQTaskTypeDerived(eQTaskType, Graph_eQTaskType) )
      {
        HIBYTE(ptQTask[74].ptPrev) = 1;
        BYTE1(ptQTask[74].ptPrev) = 1;
        BYTE2(ptQTask[74].ptPrev) = 1;
      }
    }
  }
}

// source: j/0/human/human.c:6240  [anchor-callee]
void __cdecl Human_UpdatePlatformPos(
        struct QTask_s *ptQTask,
        enum bool isForceUpdatePosition,
        enum bool isForceUpdateOrientation)
{
  #pragma pack(push, 1)
  union
  {
    struct { _BYTE tPlatformPos[40]; };
    struct { char igi2_o1[40]; struct real32x9_t tPlatformOrientation; };
    char igi2_extent[84];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QReference_s *ptMiddle; // eax
  char *pxObject; // ebp
  unsigned __int16 v5; // si
  void *v6; // esi
  void *v7; // eax
  bool v8; // zf
  int nOps; // eax
  double v10; // st7
  double v11; // st7

  if ( BYTE1(ptQTask[74].ptPrev) || isForceUpdatePosition || isForceUpdateOrientation )
  {
    ptMiddle = ptQTask[44].tQTaskRefList.ptMiddle;
    if ( ptMiddle )
    {
      pxObject = (char *)ptMiddle->pxObject;
      if ( pxObject )
      {
        v5 = *((_WORD *)pxObject + 18);
        if ( QTask_IsQTaskTypeDerived(v5, RigidDynCubeObj_eQTaskType) )
        {
          qmemcpy(&igi2_frame.tPlatformOrientation, pxObject + 124, sizeof(igi2_frame.tPlatformOrientation));
          v6 = pxObject + 40;
        }
        else
        {
          if ( QTask_IsQTaskTypeDerived(v5, Graph_eQTaskType) == false
            || (v7 = *((void **)pxObject + 13)) == nullptr )
          {
            HIBYTE(ptQTask[74].ptPrev) = 0;
            return;
          }
          qmemcpy(&igi2_frame.tPlatformOrientation, *((void **)pxObject + 14), sizeof(igi2_frame.tPlatformOrientation));
          v6 = v7;
        }
        v8 = BYTE1(ptQTask[74].ptPrev) == 0;
        nOps = igi2_frame.tPlatformOrientation.nOps;
        qmemcpy(igi2_frame.tPlatformPos, v6, 0x18u);
        if ( !v8 || isForceUpdatePosition )
        {
          v10 = *(double *)&ptQTask[1].ptNext - *(double *)igi2_frame.tPlatformPos;
          qmemcpy(&ptQTask[71].tQTaskChildren, igi2_frame.tPlatformPos, 0x18u);
          *(double *)&ptQTask[70].ptNext = v10;
          *(double *)&ptQTask[70].tQTaskChildren.ptHead = *(double *)&ptQTask[1].tQTaskChildren.ptHead
                                                        - *(double *)&igi2_frame.tPlatformPos[8];
          *(double *)&ptQTask[70].tQTaskChildren.ptTail = *(double *)&ptQTask[1].tQTaskChildren.ptTail
                                                        - *(double *)&igi2_frame.tPlatformPos[16];
          qmemcpy(&ptQTask[70].tQTaskRefList.ptMiddle, igi2_frame.tPlatformPos, 0x18u);
          *(float *)igi2_frame.tPlatformPos = igi2_frame.tPlatformOrientation.tX.vX;
          *(float *)&igi2_frame.tPlatformPos[4] = igi2_frame.tPlatformOrientation.tY.vX;
          *(float *)&igi2_frame.tPlatformPos[8] = igi2_frame.tPlatformOrientation.tZ.vX;
          *(float *)&igi2_frame.tPlatformPos[12] = igi2_frame.tPlatformOrientation.tX.vY;
          *(float *)&igi2_frame.tPlatformPos[16] = igi2_frame.tPlatformOrientation.tY.vY;
          *(float *)&igi2_frame.tPlatformPos[20] = igi2_frame.tPlatformOrientation.tZ.vY;
          *(float *)&igi2_frame.tPlatformPos[24] = igi2_frame.tPlatformOrientation.tX.vZ;
          *(float *)&igi2_frame.tPlatformPos[28] = igi2_frame.tPlatformOrientation.tY.vZ;
          *(float *)&igi2_frame.tPlatformPos[32] = igi2_frame.tPlatformOrientation.tZ.vZ;
          *(_DWORD *)&igi2_frame.tPlatformPos[36] = nOps;
          ptQTask[71].ptParent = nullptr;
          *(_DWORD *)&ptQTask[71].eQTaskType = 0;
          ptQTask[72].ptNext = nullptr;
          qmemcpy(&ptQTask[72].ptPrev, igi2_frame.tPlatformPos, sizeof(struct QTask_s));
        }
        if ( BYTE1(ptQTask[74].ptPrev) || isForceUpdateOrientation )
        {
          *(float *)igi2_frame.tPlatformPos = igi2_frame.tPlatformOrientation.tZ.vX * *(float *)&ptQTask[3].tQTaskRefList.ptTail
                                 + igi2_frame.tPlatformOrientation.tX.vX * *(float *)&ptQTask[3].ptPrev
                                 + igi2_frame.tPlatformOrientation.tY.vX * *(float *)&ptQTask[3].tQTaskChildren.ptTail;
          *(float *)&igi2_frame.tPlatformPos[4] = igi2_frame.tPlatformOrientation.tZ.vX * *(float *)&ptQTask[3].ptParent
                                     + igi2_frame.tPlatformOrientation.tX.vX * *(float *)&ptQTask[3].tQTaskChildren.ptHead
                                     + igi2_frame.tPlatformOrientation.tY.vX * *(float *)&ptQTask[3].tQTaskRefList.ptHead;
          *(float *)&igi2_frame.tPlatformPos[8] = igi2_frame.tPlatformOrientation.tZ.vX * *(float *)&ptQTask[3].eQTaskType
                                     + igi2_frame.tPlatformOrientation.tX.vX * *(float *)&ptQTask[3].tQTaskChildren.ptMiddle
                                     + igi2_frame.tPlatformOrientation.tY.vX * *(float *)&ptQTask[3].tQTaskRefList.ptMiddle;
          *(float *)&igi2_frame.tPlatformPos[12] = igi2_frame.tPlatformOrientation.tZ.vY * *(float *)&ptQTask[3].tQTaskRefList.ptTail
                                      + igi2_frame.tPlatformOrientation.tX.vY * *(float *)&ptQTask[3].ptPrev
                                      + igi2_frame.tPlatformOrientation.tY.vY * *(float *)&ptQTask[3].tQTaskChildren.ptTail;
          *(float *)&igi2_frame.tPlatformPos[16] = igi2_frame.tPlatformOrientation.tZ.vY * *(float *)&ptQTask[3].ptParent
                                      + igi2_frame.tPlatformOrientation.tX.vY * *(float *)&ptQTask[3].tQTaskChildren.ptHead
                                      + igi2_frame.tPlatformOrientation.tY.vY * *(float *)&ptQTask[3].tQTaskRefList.ptHead;
          *(float *)&igi2_frame.tPlatformPos[20] = igi2_frame.tPlatformOrientation.tZ.vY * *(float *)&ptQTask[3].eQTaskType
                                      + igi2_frame.tPlatformOrientation.tX.vY * *(float *)&ptQTask[3].tQTaskChildren.ptMiddle
                                      + igi2_frame.tPlatformOrientation.tY.vY * *(float *)&ptQTask[3].tQTaskRefList.ptMiddle;
          *(float *)&igi2_frame.tPlatformPos[24] = igi2_frame.tPlatformOrientation.tZ.vZ * *(float *)&ptQTask[3].tQTaskRefList.ptTail
                                      + igi2_frame.tPlatformOrientation.tX.vZ * *(float *)&ptQTask[3].ptPrev
                                      + igi2_frame.tPlatformOrientation.tY.vZ * *(float *)&ptQTask[3].tQTaskChildren.ptTail;
          *(float *)&igi2_frame.tPlatformPos[28] = igi2_frame.tPlatformOrientation.tZ.vZ * *(float *)&ptQTask[3].ptParent
                                      + igi2_frame.tPlatformOrientation.tX.vZ * *(float *)&ptQTask[3].tQTaskChildren.ptHead
                                      + igi2_frame.tPlatformOrientation.tY.vZ * *(float *)&ptQTask[3].tQTaskRefList.ptHead;
          v11 = igi2_frame.tPlatformOrientation.tZ.vZ * *(float *)&ptQTask[3].eQTaskType
              + igi2_frame.tPlatformOrientation.tX.vZ * *(float *)&ptQTask[3].tQTaskChildren.ptMiddle;
          *(_DWORD *)&igi2_frame.tPlatformPos[36] = (char *)&ptQTask[4].ptNext->ptNext + nOps + 1;
          *(float *)&igi2_frame.tPlatformPos[32] = v11 + igi2_frame.tPlatformOrientation.tY.vZ * *(float *)&ptQTask[3].tQTaskRefList.ptMiddle;
          qmemcpy(&ptQTask[73].ptPrev, igi2_frame.tPlatformPos, sizeof(struct QTask_s));
        }
        BYTE1(ptQTask[74].ptPrev) = 0;
        HIBYTE(ptQTask[74].ptPrev) = 1;
      }
    }
  }
}

// source: j/0/human/human.c:6303  [size]
struct QTask_s *__cdecl Human_GetGroundTask(struct QTask_s *ptQTask)
{
  struct QReference_s *ptMiddle; // eax

  ptMiddle = ptQTask[44].tQTaskRefList.ptMiddle;
  if ( ptMiddle )
    return (struct QTask_s *)ptMiddle->pxObject;
  else
    return nullptr;
}

// source: j/0/human/human.c:6319  [size]
void __cdecl Human_SetActivateTask(struct QTask_s *ptQTask, struct QTask_s *ptActivateQTask)
{
  struct QReference_s *ptHead; // eax

  ptHead = ptQTask[46].tQTaskRefList.ptHead;
  if ( ptHead )
  {
    QReference_Delete(ptHead, &QTask_tQTaskRefPool);
    ptQTask[46].tQTaskRefList.ptHead = nullptr;
  }
  if ( ptActivateQTask )
    ptQTask[46].tQTaskRefList.ptHead = QTask_NewQTaskRef(ptActivateQTask);
}

// source: j/0/human/human.c:6347  [size]
struct QTask_s *__cdecl Human_GetActivateTask(struct QTask_s *ptQTask)
{
  struct QReference_s *ptHead; // ecx
  struct QTask_s *result; // eax

  ptHead = ptQTask[46].tQTaskRefList.ptHead;
  result = nullptr;
  if ( ptHead )
    return (struct QTask_s *)ptHead->pxObject;
  return result;
}

// source: j/0/human/human.c:6372  [anchor-callee]
void __cdecl Human_SetEvaluateActivateTask(
        struct QTask_s *ptQTask,
        struct QTask_s *ptEvaluateActivateQTask)
{
  struct QTask_s *ptTail; // eax

  ptTail = ptQTask[46].tQTaskChildren.ptTail;
  if ( ptTail )
  {
    QReference_Delete((struct QReference_s *)ptTail, &QTask_tQTaskRefPool);
    ptQTask[46].tQTaskChildren.ptTail = nullptr;
  }
  if ( ptEvaluateActivateQTask )
    ptQTask[46].tQTaskChildren.ptTail = (struct QTask_s *)QTask_NewQTaskRef(ptEvaluateActivateQTask);
}

// source: j/0/human/human.c:6395  [anchor-callee]
struct QTask_s *__cdecl Human_GetEvaluateActivateTask(struct QTask_s *ptQTask)
{
  struct QTask_s *ptTail; // eax

  ptTail = ptQTask[46].tQTaskChildren.ptTail;
  if ( ptTail )
    return ptTail->tQTaskChildren.ptHead;
  else
    return nullptr;
}

// source: j/0/human/human.c:6411  [size]
int __cdecl Human_SetHumanCameraMode(struct QTask_s *ptQTask, int eHumanCameraMode)
{
  ptQTask[33].tQTaskRefList.ptHead = (struct QReference_s *)eHumanCameraMode;
  return eHumanCameraMode;
}

// source: j/0/human/human.c:6428  [anchor-mhash]
void __cdecl Human_RunningControl(struct QTask_s *ptQTask, float vTweakTimeStep)
{
  double v2; // st7

  v2 = *(float *)&ptQTask[44].ptNext;
  if ( v2 >= -0.20000000298023224 )
  {
    if ( v2 > 1.0 )
      v2 = 1.0;
  }
  else
  {
    v2 = -0.20000000298023224;
  }
  ptQTask[34].tQTaskChildren.ptTail[1].tQTaskRefList.ptTail = (struct QReference_s *)(__int64)((1.0 - v2)
                                                                                             * (double)AnimController_nTicksPerFrame
                                                                                             * vTweakTimeStep);
}

// source: j/0/human/human.c:6457  [anchor-mhash]
struct QTask_s *__cdecl Human_InAirControl(struct QTask_s *ptQTask)
{
  *(float *)&ptQTask[38].ptPrev = *(float *)&ptQTask[38].ptPrev * 0.9900000095367432;
  *(float *)&ptQTask[38].tQTaskChildren.ptHead = *(float *)&ptQTask[38].tQTaskChildren.ptHead * 0.9900000095367432;
  *(float *)&ptQTask[38].tQTaskChildren.ptMiddle = (*(float *)&ptQTask[38].tQTaskChildren.ptMiddle - 84.74169158935547)
                                                 * 0.9900000095367432;
  return ptQTask;
}

// source: j/0/human/human.c:6477  [anchor-callee]
void __cdecl Human_HitSound(struct QTask_s *ptQTask, char **azSounds, int nNumSounds)
{
  struct Game_s *v3; // ecx
  int nTicks; // eax
  unsigned int v5; // edx
  int v6; // edx
  double v7; // st7
  int v8; // eax
  int v9; // edx
  unsigned int v10; // ebx
  unsigned int v11; // edx
  struct QReference_s *v12; // ecx
  struct QTask_s *pxObject; // ebx
  char *v14; // eax
  struct QTask_s *v15; // eax

  if ( Flow_ptFlow->nTicks >= (int)ptQTask[49].ptNext )
  {
    QTask_DeleteQTaskAndQTaskRefSafe((struct QReference_s **)&ptQTask[48].eQTaskType);
    v3 = Game_ptGame;
    nTicks = Flow_ptFlow->nTicks;
    v5 = (Game_ptGame->tRunRandomState.anRandom[0] >> 7) ^ Game_ptGame->tRunRandomState.anRandom[2];
    Game_ptGame->tRunRandomState.anRandom[2] = v5;
    v6 = v5 ^ v3->tRunRandomState.anRandom[1];
    v3->tRunRandomState.anRandom[1] = v6;
    v7 = (double)(unsigned __int16)(v6 + LOWORD(v3->tRunRandomState.anRandom[0]));
    v3->tRunRandomState.anRandom[0] += v6;
    ptQTask[49].ptNext = (struct QTask_s *)(nTicks - (__int64)(v7 * 0.0000152587890625 * -30.0) + 30);
    v8 = (v3->tRunRandomState.anRandom[0] >> 7) ^ v3->tRunRandomState.anRandom[2];
    v9 = v8 ^ v3->tRunRandomState.anRandom[1];
    v3->tRunRandomState.anRandom[2] = v8;
    v10 = v9 + v3->tRunRandomState.anRandom[0];
    v3->tRunRandomState.anRandom[1] = v9;
    v11 = v10 % nNumSounds;
    v3->tRunRandomState.anRandom[0] = v10;
    v12 = v3->aptPlayerQTaskRef[2];
    pxObject = nullptr;
    v14 = azSounds[v11];
    if ( v12 )
      pxObject = (struct QTask_s *)v12->pxObject;
    if ( ptQTask == pxObject )
      v15 = SoundSys_NewSoundFn(ptQTask[33].tQTaskChildren.ptTail, v14);
    else
      v15 = SoundSys_NewSoundFn(ptQTask, v14);
    *(_DWORD *)&ptQTask[48].eQTaskType = QTask_NewQTaskRef(v15);
  }
}

// source: j/0/human/human.c:6513  [anchor-callee]
void __cdecl Human_PlayDeathSound(struct QTask_s *ptQTask, char *zSoundDefPrefix, int nNumSounds)
{
  struct Game_s *v3; // eax
  unsigned int v4; // esi
  unsigned int v5; // ecx
  int v6; // esi
  unsigned int v7; // edx
  struct QReference_s *v8; // eax
  struct QTask_s *pxObject; // ecx
  char zSoundDef[32]; // [esp+4h] [ebp-20h] BYREF

  QTask_DeleteQTaskAndQTaskRefSafe((struct QReference_s **)&ptQTask[48].eQTaskType);
  v3 = Game_ptGame;
  v4 = Game_ptGame->tRunRandomState.anRandom[1];
  v5 = (Game_ptGame->tRunRandomState.anRandom[0] >> 7) ^ Game_ptGame->tRunRandomState.anRandom[2];
  Game_ptGame->tRunRandomState.anRandom[2] = v5;
  v6 = v5 ^ v4;
  v7 = v6 + v3->tRunRandomState.anRandom[0];
  v3->tRunRandomState.anRandom[0] = v7;
  v3->tRunRandomState.anRandom[1] = v6;
  sprintf(zSoundDef, "%s%d", zSoundDefPrefix, v7 % nNumSounds);
  v8 = Game_ptGame->aptPlayerQTaskRef[2];
  pxObject = nullptr;
  if ( v8 )
    pxObject = (struct QTask_s *)v8->pxObject;
  if ( ptQTask == pxObject )
    SoundSys_NewSoundFn(ptQTask[33].tQTaskChildren.ptTail, zSoundDef);
  else
    SoundSys_NewSoundFn(ptQTask, zSoundDef);
}

// source: j/0/human/human.c:6549  [anchor-strings]
void __cdecl Human_TriggerAnimTriggerHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct Human_s *v2; // esi
  int v3; // eax
  unsigned int v4; // eax
  int v5; // ebx
  double v6; // st7
  struct QTask_s *v7; // eax
  int nState; // eax
  struct QMaterial_t *v9; // eax
  struct real32x3_t *p_tColor; // ecx
  struct QTask_s *v11; // eax
  struct QTask_s *v12; // edi
  struct QMaterial_t *ptEnterMaterial; // eax
  float pxContexta = *(float *)&pxContext; // [esp+14h] [ebp+8h] ARGSLOT

  v2 = *(struct Human_s **)pxContext;
  v3 = *((_DWORD *)pxContext + 2);
  if ( v3 == 13 )
  {
    if ( v2->tGroundIntersection.isHit )
    {
      ptEnterMaterial = v2->tGroundIntersection.ptEnterMaterial;
      if ( ptEnterMaterial )
      {
        Human_PlaySound(
          *(struct Human_s **)pxContext,
          (char *)&ptEnterMaterial[dword_834DDD4 + 19].tColor,
          &v2->tGroundIntersection.tPos);
        dword_834DDD4 = (dword_834DDD4 + 1) % 3;
      }
    }
  }
  else
  {
    if ( v3 != 1010 )
    {
      LDebug_Error("Unknown animtrigger for human: %d", *((_DWORD *)pxContext + 2));
      abort();
    }
    if ( v2->tGroundIntersection.isHit && !v2->isDead )
    {
      v4 = *(_DWORD *)&v2->isSymbolsCreated;
      v5 = Human_anFeetSoundSequence[v4++];
      *(_DWORD *)&v2->isSymbolsCreated = v4;
      if ( v4 >= 0x1F )
        *(_DWORD *)&v2->isSymbolsCreated = 0;
      if ( *(float *)&v2->iWaterIndex <= 0.0 )
      {
        if ( v2->tBoneDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask.eQTaskType != HumanPlayer_eQTaskType
          || (nState = v2->tState.nState, nState != 1) && nState != 24 )
        {
          v9 = v2->tGroundIntersection.ptEnterMaterial;
          if ( v9 )
          {
            p_tColor = &v9[10].tColor;
            if ( !*(&v2->bAllowedStance + 1) )
              p_tColor = &v9[2].tColor;
            v11 = Human_PlaySound(v2, (char *)p_tColor + 32 * v5, &v2->tGroundIntersection.tPos);
            v12 = v11;
            if ( v11 )
            {
              if ( Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER )
                v11[1].ptPrev = (struct QTask_s *)1069547520;
              if ( v2->ePose == 1 )
                SoundSys_SetSoundVolumes(v11, -1.0, 0.5);
              SoundSys_SetSoundSector(v12, v2[1].tBoneDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask.ptNext);
            }
          }
        }
      }
      else
      {
        Human_PlaySound(v2, (&off_6B7D38)[v5], &v2->tGroundIntersection.tPos);
        v6 = *(float *)&v2->iWaterIndex * 0.00017438616487197578;
        if ( v6 >= 0.0 )
        {
          if ( v6 <= 1.0 )
            pxContexta = v6;
          else
            pxContexta = 1.0;
        }
        else
        {
          pxContexta = 0.0;
        }
        v7 = Human_PlaySound(v2, (&off_6B7D58)[v5 & 1], &v2->tGroundIntersection.tPos);
        if ( v7 )
          SoundSys_SetSoundVolumes(v7, -1.0, pxContexta);
      }
    }
  }
}

// source: j/0/human/human.c:6683  [size]
struct QTask_s *__cdecl Human_DisableShadow(struct QTask_s *ptQTask)
{
  ptQTask[48].ptNext = (struct QTask_s *)1;
  *(_DWORD *)&ptQTask[47].eQTaskType = 0;
  return ptQTask;
}

// source: j/0/human/human.c:6701  [size]
struct QTask_s *__cdecl Human_EnableShadow(struct QTask_s *ptQTask)
{
  ptQTask[48].ptNext = nullptr;
  *(_DWORD *)&ptQTask[47].eQTaskType = 1;
  return ptQTask;
}

// source: j/0/human/human.c:6719  [size]
unsigned int __cdecl Human_GetAIDetectionQTaskMask()
{
  return Human_bAIDetectionQTaskMask;
}

// source: j/0/human/human.c:6734  [anchor-mhash]
struct QTask_s *__cdecl Human_MoveOnGround(struct QTask_s *ptQTask, float vSpeed, float vGamma)
{
  #pragma pack(push, 1)
  union
  {
    struct { float Real32x3_Rotate_tTemp; };
    struct { char igi2_o1[4]; float Real32x3_Rotate_tTemp_4; };
    struct { char igi2_o2[8]; float Real32x3_Rotate_tTemp_8; };
    struct { char igi2_o3[12]; struct real32x9_t tMatrix; };
    char igi2_extent[56];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  double v4; // st7
  double v5; // st6
  double v6; // st5
  double v7; // rt0
  double v8; // st5
  double v9; // st6

  Real32x9_Create(&igi2_frame.tMatrix, 0.0, 0.0, vGamma);
  ptQTask = (struct QTask_s *)((char *)ptQTask + 1444);
  v4 = (igi2_frame.tMatrix.tX.vZ + igi2_frame.tMatrix.tX.vX) * 0.0 + igi2_frame.tMatrix.tX.vY * vSpeed;
  v5 = (igi2_frame.tMatrix.tY.vZ + igi2_frame.tMatrix.tY.vX) * 0.0 + igi2_frame.tMatrix.tY.vY * vSpeed;
  v6 = (igi2_frame.tMatrix.tZ.vZ + igi2_frame.tMatrix.tZ.vX) * 0.0 + igi2_frame.tMatrix.tZ.vY * vSpeed;
  igi2_frame.Real32x3_Rotate_tTemp = v6 * *(float *)&ptQTask[-33].tQTaskChildren.ptHead
                        + v5 * *(float *)&ptQTask[-33].ptPrev
                        + v4 * *(float *)&ptQTask[-33].ptNext;
  igi2_frame.Real32x3_Rotate_tTemp_4 = v6 * *(float *)&ptQTask[-33].tQTaskRefList.ptHead
                          + v5 * *(float *)&ptQTask[-33].tQTaskChildren.ptTail
                          + v4 * *(float *)&ptQTask[-33].tQTaskChildren.ptMiddle;
  v7 = v6 * *(float *)&ptQTask[-33].ptParent;
  v8 = v5 * *(float *)&ptQTask[-33].tQTaskRefList.ptTail;
  v9 = v4 * *(float *)&ptQTask[-33].tQTaskRefList.ptMiddle;
  *(float *)&ptQTask->ptNext = igi2_frame.Real32x3_Rotate_tTemp;
  *(float *)&ptQTask->ptPrev = igi2_frame.Real32x3_Rotate_tTemp_4;
  igi2_frame.Real32x3_Rotate_tTemp_8 = v7 + v8 + v9;
  *(float *)&ptQTask->tQTaskChildren.ptHead = igi2_frame.Real32x3_Rotate_tTemp_8;
  return (struct QTask_s *)LODWORD(igi2_frame.Real32x3_Rotate_tTemp_8);
}

// source: j/0/human/human.c:6759  [anchor-callee]
struct QTask_s *__cdecl Human_MoveFree(
        struct QTask_s *ptQTask,
        float vSpeed,
        struct real32x3_t *ptUnitVector,
        enum bool isPop)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct real64x3_t tMove; };
    struct { char igi2_o1[28]; struct real32x3_t Real32x3_Rotate_tTemp; };
    char igi2_extent[44];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  float vY; // edx
  float vZ; // ecx
  double v6; // st7
  double v7; // st6
  struct QTask_s *result; // eax
  float v9; // edx
  double v10; // st7
  double v11; // st6

  *(float *)&igi2_frame.tMove.vX = ptUnitVector->vX;
  vY = ptUnitVector->vY;
  vZ = ptUnitVector->vZ;
  *(float *)&igi2_frame.tMove.vX = *(float *)&igi2_frame.tMove.vX * vSpeed;
  *((float *)&igi2_frame.tMove.vX + 1) = vY * vSpeed;
  *(float *)&igi2_frame.tMove.vY = vZ * vSpeed;
  v6 = *(float *)&igi2_frame.tMove.vY * *(float *)&ptQTask[3].tQTaskChildren.ptMiddle
     + *((float *)&igi2_frame.tMove.vX + 1) * *(float *)&ptQTask[3].tQTaskChildren.ptHead
     + *(float *)&igi2_frame.tMove.vX * *(float *)&ptQTask[3].ptPrev;
  if ( isPop )
  {
    v7 = *(float *)&igi2_frame.tMove.vY * *(float *)&ptQTask[3].tQTaskRefList.ptMiddle
       + *((float *)&igi2_frame.tMove.vX + 1) * *(float *)&ptQTask[3].tQTaskRefList.ptHead
       + *(float *)&igi2_frame.tMove.vX * *(float *)&ptQTask[3].tQTaskChildren.ptTail;
    igi2_frame.Real32x3_Rotate_tTemp.vZ = *(float *)&igi2_frame.tMove.vY * *(float *)&ptQTask[3].eQTaskType
                             + *((float *)&igi2_frame.tMove.vX + 1) * *(float *)&ptQTask[3].ptParent
                             + *(float *)&igi2_frame.tMove.vX * *(float *)&ptQTask[3].tQTaskRefList.ptTail;
    igi2_frame.tMove.vX = v6 + *(double *)&ptQTask[1].ptNext;
    igi2_frame.tMove.vY = v7 + *(double *)&ptQTask[1].tQTaskChildren.ptHead;
    igi2_frame.tMove.vZ = igi2_frame.Real32x3_Rotate_tTemp.vZ + *(double *)&ptQTask[1].tQTaskChildren.ptTail;
    Human_PopPosition(ptQTask, &igi2_frame.tMove);
  }
  else
  {
    igi2_frame.Real32x3_Rotate_tTemp.vX = v6;
    result = (struct QTask_s *)((char *)ptQTask + 1444);
    igi2_frame.Real32x3_Rotate_tTemp.vY = *(float *)&igi2_frame.tMove.vY * *(float *)&result[-33].tQTaskRefList.ptHead
                             + *((float *)&igi2_frame.tMove.vX + 1) * *(float *)&result[-33].tQTaskChildren.ptTail
                             + *(float *)&igi2_frame.tMove.vX * *(float *)&result[-33].tQTaskChildren.ptMiddle;
    v9 = igi2_frame.Real32x3_Rotate_tTemp.vY;
    v10 = *(float *)&igi2_frame.tMove.vY * *(float *)&result[-33].ptParent
        + *((float *)&igi2_frame.tMove.vX + 1) * *(float *)&result[-33].tQTaskRefList.ptTail;
    v11 = *(float *)&igi2_frame.tMove.vX * *(float *)&result[-33].tQTaskRefList.ptMiddle;
    result->ptNext = (struct QTask_s *)LODWORD(igi2_frame.Real32x3_Rotate_tTemp.vX);
    *(float *)&result->ptPrev = v9;
    igi2_frame.Real32x3_Rotate_tTemp.vZ = v10 + v11;
    result->tQTaskChildren.ptHead = (struct QTask_s *)LODWORD(igi2_frame.Real32x3_Rotate_tTemp.vZ);
  }
  return result;
}

// source: j/0/human/human.c:6792  [anchor-mhash]
struct WeaponType_s *__cdecl Human_GetNextEnabledWeaponTypeSameCategoryFromGunPickup(
        struct QTask_s *ptHumanQTask,
        struct QTask_s *ptGunPickup,
        struct WeaponType_s *ptSkipWeaponType)
{
  struct WeaponType_s *WeaponTypeFromID; // eax

  WeaponTypeFromID = WeaponType_GetWeaponTypeFromID((int)ptGunPickup[10].tQTaskChildren.ptTail);
  return Weapon_GetNextEnabledWeaponTypeFromCategory(
           ptHumanQTask[33].ptNext,
           WeaponTypeFromID->eWeaponCategory,
           ptSkipWeaponType);
}

// source: j/0/human/human.c:6817  [anchor-callee]
struct QTask_s *__cdecl Human_GetWeaponTypeAnimPtr(struct QTask_s *ptQTask)
{
  struct QTask_s *ptNext; // eax
  struct QTask_s *ptPrev; // eax
  struct QTask_s *ptTail; // ecx
  struct QTask_s *result; // eax

  ptNext = ptQTask[33].ptNext;
  if ( !ptNext )
    return nullptr;
  ptPrev = ptNext[1].ptPrev;
  if ( !ptPrev )
    return nullptr;
  ptTail = ptPrev->tQTaskChildren.ptTail;
  if ( !ptTail )
    return nullptr;
  result = ptTail[48].tQTaskChildren.ptHead;
  if ( ptQTask[7].tQTaskRefList.ptTail != *(struct QReference_s **)&result[24].eQTaskType )
    return ptTail[48].tQTaskChildren.ptMiddle;
  return result;
}

// source: j/0/human/human.c:6854  [size]
struct ParameterList_s *__cdecl Human_GetSerializeParameterList()
{
  return Human_ptSerializeParameterList;
}

// source: j/0/human/human.c:6867  [size]
struct ParameterList_s *__cdecl Human_GetSerializeStateParameterList()
{
  return Human_ptSerializeStateParameterList;
}

// source: j/0/human/human.c:6884  [anchor-strings]
void __cdecl Human_MakeRandomFaceModel(char *pzModel)
{
  int v1; // ebp

  v1 = dword_79EE2C8 % 3 + 1;
  ++dword_79EE2C8;
  if ( !strcmp(pzModel, "ch_rsg_1") || !strcmp(pzModel, "rsg_1") )
    sprintf(pzModel, "rsg%d_1", v1);
  if ( !strcmp(pzModel, "resg_1") || !strcmp(pzModel, "ch_resg_1") )
    sprintf(pzModel, "resg%d_1", v1);
  if ( !strcmp(pzModel, "libgu_1") )
    sprintf(pzModel, "libgu%d_1", v1);
  if ( !strcmp(pzModel, "les_1") )
    sprintf(pzModel, "les%d_1", v1);
  if ( !strcmp(pzModel, "chn_1") )
    sprintf(pzModel, "chn%d_1", v1);
  if ( !strcmp(pzModel, "csf_1") )
    sprintf(pzModel, "csf%d_1", v1);
}

// source: j/0/human/human.c:6939  [anchor-strings]
struct Human_s *__cdecl Human_UpdateModel(struct Human_s *ptHuman)
{
  int v2; // eax
  struct LODVirModel_s *LODVirModelExistsFn; // eax
  struct Model_s *ptModel; // ecx
  struct Mesh3D_Mesh_t *ptMesh; // ecx
  struct LODVirModel_s *v6; // esi
  struct Human_s *result; // eax

  if ( ptHuman->tBoneDynCubeObj.tModelObj.ptLODVirModel )
    HumanAnim_DeInit(&ptHuman->tBoneDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask);
  Human_MakeRandomFaceModel(ptHuman->tHumanParameters.zModel);
  if ( Game_eGameMode != GAME_GAMEMODE_MULTIPLAYER )
  {
    v2 = ModelObj_nDisabledAttachObjects;
    ModelObj_apzDisabledAttachObjects[ModelObj_nDisabledAttachObjects] = "bombbackpack";
    ModelObj_nDisabledAttachObjects = v2 + 1;
  }
  LODVirModelExistsFn = MTP_GetLODVirModelExistsFn(ptHuman->tHumanParameters.zModel);
  if ( LODVirModelExistsFn
    && LODVirModelExistsFn->nLOD > 0
    && LODVirModelExistsFn->aptVirModel[0]
    && (ptModel = LODVirModelExistsFn->aptVirModel[0]->ptModel) != nullptr
    && (ptMesh = ptModel->ptMesh) != nullptr
    && ptMesh->eRenderMeshType == MESH3D_RENDERMESHTYPE_DIRECT3D_BONE )
  {
    v6 = LODVirModelExistsFn;
  }
  else
  {
    v6 = nullptr;
  }
  BoneDynCubeObj_SetLODVirModel(&ptHuman->tBoneDynCubeObj, v6);
  if ( v6 )
    HumanAnim_Init(&ptHuman->tBoneDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask, true);
  if ( Game_eGameMode != GAME_GAMEMODE_MULTIPLAYER )
    ModelObj_nDisabledAttachObjects = 0;
  ModelObj_UpdateAttachments(&ptHuman->tBoneDynCubeObj.tModelObj);
  result = (struct Human_s *)ptHuman->ptWeaponQTask;
  result->tBoneDynCubeObj.tModelObj.tDynCubeObj.ptPrev = (struct DynCubeObj_s *)ptHuman->tHumanParameters.eTeam;
  return result;
}

// source: j/0/human/human.c:6989  [size]
int __cdecl Human_SetIgnoreLightEffectOnVisibilityTimer(
        struct QTask_s *ptQTask,
        int nTime)
{
  ptQTask[49].tQTaskChildren.ptTail = (struct QTask_s *)nTime;
  return nTime;
}

// source: j/0/human/human.c:7006  [size]
void __cdecl Human_SetRunning(struct QTask_s *ptQTask, enum bool isRunning)
{
  BYTE1(ptQTask[50].ptNext) = isRunning;
}

// source: j/0/human/human.c:7023  [anchor-callee]
struct Human_s *__cdecl Human_SetTeam(struct Human_s *ptHuman, int eTeam, char *pzModel)
{
  int v3; // esi
  char v4; // dl

  v3 = ptHuman->tHumanParameters.zModel - pzModel;
  do
  {
    v4 = *pzModel;
    pzModel[v3] = *pzModel;
    ++pzModel;
  }
  while ( v4 );
  ptHuman->tHumanParameters.eTeam = eTeam;
  return Human_UpdateModel(ptHuman);
}

// source: j/0/human/human.c:7047  [anchor-strings]
void __cdecl Human_CheckBoneCollision(struct Human_s *ptHuman)
{
  #pragma pack(push, 1)
  union
  {
    struct { int nHits; };
    struct { int nHitsa; };
    struct { char igi2_o2[4]; struct ObjectCollisionEvaluateContext_t tObjectCollisionEvaluateContext; };
    struct { char igi2_o3[12]; int iLowestHit; };
    struct { char igi2_o4[16]; char *azBone[11]; };
    struct { char igi2_o5[60]; double v27; };
    struct { char igi2_o6[72]; struct real32x3_t tHitToEnd; };
    struct { char igi2_o7[84]; struct real64x3_t atStart[14]; };
    struct { char igi2_o8[420]; struct real64x3_t atEnd[14]; };
    struct { char igi2_o9[756]; struct QIntersection_s atIntersection[14]; };
    char igi2_extent[2436];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int iLowerBackBone; // ebx
  struct real64x3_t *v2; // eax
  int v3; // edx
  struct real64x3_t *v4; // edi
  struct real64x3_t *v5; // edi
  int Bone; // eax
  double vX; // st7
  double vY; // st6
  double vZ; // st5
  double *p_vY; // eax
  int v11; // ecx
  int v12; // esi
  int v13; // ebx
  int v14; // ecx
  double *v15; // edx
  double v16; // st7
  double v17; // st6
  double v18; // st5
  long double v19; // st2
  double v20; // st7
  double v21; // st7

  iLowerBackBone = ptHuman->tHumanAnim.iLowerBackBone;
  igi2_frame.iLowestHit = -1;
  igi2_frame.azBone[0] = "lower left leg";
  igi2_frame.azBone[1] = "left toe end";
  igi2_frame.azBone[2] = "lower right leg";
  igi2_frame.azBone[3] = "right toe end";
  igi2_frame.azBone[4] = "head end";
  igi2_frame.azBone[5] = "upper left arm";
  igi2_frame.azBone[6] = "lower left arm";
  igi2_frame.azBone[7] = "lower left fingers";
  igi2_frame.azBone[8] = "upper right arm";
  igi2_frame.azBone[9] = "lower right arm";
  igi2_frame.azBone[10] = "lower right fingers";
  BoneDynCubeObj_GetBonePosition((struct BoneDynCubeObj_s *)igi2_frame.atStart, (struct real32x3_t *)ptHuman, iLowerBackBone);
  v2 = &igi2_frame.atStart[1];
  v3 = 13;
  igi2_frame.atStart[0].vZ = igi2_frame.atStart[0].vZ + 819.2000122070312;
  do
  {
    v4 = v2++;
    --v3;
    qmemcpy(v4, igi2_frame.atStart, sizeof(struct real64x3_t));
  }
  while ( v3 );
  igi2_frame.nHits = 0;
  v5 = igi2_frame.atEnd;
  do
  {
    Bone = Hierarchy_GetBone(ptHuman->tBoneDynCubeObj.pcHierarchy, igi2_frame.azBone[igi2_frame.nHits]);
    BoneDynCubeObj_GetBonePosition((struct BoneDynCubeObj_s *)v5++, (struct real32x3_t *)ptHuman, Bone);
    ++igi2_frame.nHits;
  }
  while ( igi2_frame.nHits < 11 );
  igi2_frame.atEnd[11].vY = igi2_frame.atStart[11].vY;
  igi2_frame.atEnd[11].vZ = igi2_frame.atStart[11].vZ - 1433.5999755859375;
  igi2_frame.atEnd[11].vX = igi2_frame.atStart[11].vX;
  igi2_frame.atEnd[12].vZ = igi2_frame.atStart[12].vZ - 12288.0;
  igi2_frame.atEnd[12].vX = igi2_frame.atStart[12].vX;
  qmemcpy(&igi2_frame.atStart[13], &ptHuman->tBoneDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos, sizeof(struct real64x3_t));
  igi2_frame.atEnd[13].vZ = igi2_frame.atStart[13].vZ + 61440.0;
  vX = ptHuman->tSpeed.vX;
  vY = ptHuman->tSpeed.vY;
  vZ = ptHuman->tSpeed.vZ;
  igi2_frame.atEnd[13].vX = igi2_frame.atStart[13].vX;
  igi2_frame.atEnd[12].vY = igi2_frame.atStart[12].vY;
  igi2_frame.atEnd[13].vY = igi2_frame.atStart[13].vY;
  igi2_frame.tObjectCollisionEvaluateContext.tCollisionEvaluateContext.ptQTask = &ptHuman->tBoneDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask;
  p_vY = &igi2_frame.atEnd[0].vY;
  v11 = 2;
  do
  {
    p_vY += 21;
    --v11;
    *(p_vY - 22) = vX + *(p_vY - 22);
    *(p_vY - 21) = vY + *(p_vY - 21);
    *(p_vY - 20) = vZ + *(p_vY - 20);
    *(p_vY - 19) = vX + *(p_vY - 19);
    *(p_vY - 18) = vY + *(p_vY - 18);
    *(p_vY - 17) = vZ + *(p_vY - 17);
    *(p_vY - 16) = vX + *(p_vY - 16);
    *(p_vY - 15) = vY + *(p_vY - 15);
    *(p_vY - 14) = vZ + *(p_vY - 14);
    *(p_vY - 13) = vX + *(p_vY - 13);
    *(p_vY - 12) = vY + *(p_vY - 12);
    *(p_vY - 11) = vZ + *(p_vY - 11);
    *(p_vY - 10) = vX + *(p_vY - 10);
    *(p_vY - 9) = vY + *(p_vY - 9);
    *(p_vY - 8) = vZ + *(p_vY - 8);
    *(p_vY - 7) = vX + *(p_vY - 7);
    *(p_vY - 6) = vY + *(p_vY - 6);
    *(p_vY - 5) = vZ + *(p_vY - 5);
    *(p_vY - 4) = vX + *(p_vY - 4);
    *(p_vY - 3) = vY + *(p_vY - 3);
    *(p_vY - 2) = vZ + *(p_vY - 2);
  }
  while ( v11 );
  World_TraceLinesSpecificMesh(
    Game_ptGame->ptWorld,
    igi2_frame.atIntersection,
    igi2_frame.atStart,
    igi2_frame.atEnd,
    14,
    GameFunctions_eObjectCollisionEvaluateQTaskEvent,
    &igi2_frame.tObjectCollisionEvaluateContext.tCollisionEvaluateContext,
    Forest_bQTaskGroup | 0x98000000,
    1);
  v12 = 0;
  ptHuman->tBoneCollisionData.tDeltaMovement.vY = 0.0;
  ptHuman->tBoneCollisionData.tDeltaMovement.vZ = 0.0;
  ptHuman->tDeathDirection.vX = 0.0;
  igi2_frame.nHitsa = 0;
  v13 = -120;
  v14 = 0;
  v15 = &igi2_frame.atEnd[0].vY;
  do
  {
    if ( igi2_frame.atIntersection[v14].isHit && igi2_frame.atIntersection[v14].tNormal.vZ > -0.5 )
    {
      if ( igi2_frame.atIntersection[v14].tPos.vZ < igi2_frame.atStart[0].vZ
        && (igi2_frame.iLowestHit < 0 || igi2_frame.atIntersection[v14].tPos.vZ < *(double *)((char *)&igi2_frame.atIntersection[0].tPos.vZ + v13)) )
      {
        igi2_frame.iLowestHit = v12;
        v13 = v14 * 120;
      }
      v16 = *(v15 - 1) - igi2_frame.atIntersection[v14].tPos.vX;
      v17 = *v15 - igi2_frame.atIntersection[v14].tPos.vY;
      igi2_frame.tHitToEnd.vZ = v15[1] - igi2_frame.atIntersection[v14].tPos.vZ;
      if ( igi2_frame.atIntersection[v14].tNormal.vX != 0.0
        || igi2_frame.atIntersection[v14].tNormal.vY != 0.0
        || igi2_frame.atIntersection[v14].tNormal.vZ != 0.0 )
      {
        v18 = igi2_frame.atIntersection[v14].tNormal.vZ;
        igi2_frame.v27 = igi2_frame.atIntersection[v14].tNormal.vY;
        *(double *)&igi2_frame.tObjectCollisionEvaluateContext = igi2_frame.atIntersection[v14].tNormal.vX;
        v19 = sqrt(
                v18 * v18
              + *(double *)&igi2_frame.tObjectCollisionEvaluateContext * *(double *)&igi2_frame.tObjectCollisionEvaluateContext
              + igi2_frame.v27 * igi2_frame.v27);
        igi2_frame.atIntersection[v14].tNormal.vX = *(double *)&igi2_frame.tObjectCollisionEvaluateContext * (1.0 / v19);
        igi2_frame.atIntersection[v14].tNormal.vY = igi2_frame.v27 * (1.0 / v19);
        igi2_frame.atIntersection[v14].tNormal.vZ = v18 * (1.0 / v19);
      }
      *(float *)&igi2_frame.tObjectCollisionEvaluateContext.tCollisionEvaluateContext.isEvaluate = igi2_frame.tHitToEnd.vZ
                                                                                      * igi2_frame.atIntersection[v14].tNormal.vZ
                                                                                      + v16
                                                                                      * igi2_frame.atIntersection[v14].tNormal.vX
                                                                                      + v17
                                                                                      * igi2_frame.atIntersection[v14].tNormal.vY;
      if ( v14 != 12 && *(float *)&igi2_frame.tObjectCollisionEvaluateContext.tCollisionEvaluateContext.isEvaluate < 0.0 )
      {
        ptHuman->tBoneCollisionData.tDeltaMovement.vY = ptHuman->tBoneCollisionData.tDeltaMovement.vY
                                                      - *(float *)&igi2_frame.tObjectCollisionEvaluateContext.tCollisionEvaluateContext.isEvaluate
                                                      * igi2_frame.atIntersection[v14].tNormal.vX;
        ptHuman->tBoneCollisionData.tDeltaMovement.vZ = ptHuman->tBoneCollisionData.tDeltaMovement.vZ
                                                      - *(float *)&igi2_frame.tObjectCollisionEvaluateContext.tCollisionEvaluateContext.isEvaluate
                                                      * igi2_frame.atIntersection[v14].tNormal.vY;
        if ( v14 == 11 || v14 < 4 )
        {
          v20 = -(*(float *)&igi2_frame.tObjectCollisionEvaluateContext.tCollisionEvaluateContext.isEvaluate
                * igi2_frame.atIntersection[v14].tNormal.vZ);
          if ( v20 <= ptHuman->tDeathDirection.vX )
            v20 = ptHuman->tDeathDirection.vX;
          ptHuman->tDeathDirection.vX = v20;
        }
        ++igi2_frame.nHitsa;
      }
    }
    ++v14;
    ++v12;
    v15 += 3;
  }
  while ( v14 < 14 );
  if ( igi2_frame.nHitsa > 1 )
  {
    v21 = 1.0 / (double)igi2_frame.nHitsa;
    ptHuman->tBoneCollisionData.tDeltaMovement.vY = v21 * ptHuman->tBoneCollisionData.tDeltaMovement.vY;
    ptHuman->tBoneCollisionData.tDeltaMovement.vZ = v21 * ptHuman->tBoneCollisionData.tDeltaMovement.vZ;
  }
}

// source: j/0/human/human.c:7213  [anchor-mhash]
struct QTask_s *__cdecl Human_GetTarget(struct QTask_s *ptHumanQTask)
{
  struct HumanAI_s *ptParent; // eax

  if ( ptHumanQTask && (ptParent = (struct HumanAI_s *)ptHumanQTask[48].ptParent) != nullptr )
    return HumanAI_GetTargetQTask(ptParent, true);
  else
    return nullptr;
}

// source: j/0/human/human.c:7238  [anchor-mhash]
struct Human_s *__cdecl Human_ResolveDamage(
        struct Human_s *ptHuman,
        enum DamagePart_e eDamagePart,
        float vHitDamage)
{
  double v3; // st7

  ptHuman->tHumanDamage.eDamagePart = eDamagePart;
  v3 = vHitDamage * ptHuman->tHumanDamage.atDamagePart[eDamagePart].vDamageMultiplier;
  ptHuman->tHumanDamage.atDamagePart[eDamagePart].vDamage = v3 + ptHuman->tHumanDamage.atDamagePart[eDamagePart].vDamage;
  ptHuman->tHumanDamage.vDamage = v3 + ptHuman->tHumanDamage.vDamage;
  return ptHuman;
}

// source: j/0/human/human.c:7283  [anchor-callee]
void __cdecl Human_UpdateDie(struct Human_s *ptHuman)
{
  struct QTask_s *ptWeaponQTask; // eax
  struct QTask_s *ptPrev; // ecx
  struct QTask_s *ptTail; // esi
  struct QTask_s *v5; // eax
  struct QTask_s *ptParent; // eax
  struct Client_s *ClientFromHumanQTask; // eax
  struct WeaponTypeItem_s *WeaponTypeItemFromWeaponType; // eax
  struct WeaponType_s *ptWeaponType; // eax
  struct Client_s *v10; // eax
  struct QTask_s *v11; // esi
  struct QTask_s *ptHead; // eax
  struct QTask_s *v13; // eax
  unsigned int v14; // eax
  int v15; // [esp-4h] [ebp-Ch]
  int eID; // [esp-4h] [ebp-Ch]

  if ( ptHuman->tHumanDamage.vDamage >= (double)ptHuman->tHumanDamage.vMaxDamage && !ptHuman->isDead )
  {
    if ( Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER && !Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle )
    {
      ptWeaponQTask = ptHuman->ptWeaponQTask;
      ptPrev = ptWeaponQTask[1].ptPrev;
      if ( ptPrev )
        ptTail = ptPrev->tQTaskChildren.ptTail;
      else
        ptTail = nullptr;
      ptWeaponQTask[2].ptParent = (struct QTask_s *)1;
      ptWeaponQTask[1].tQTaskChildren.ptTail = nullptr;
      v5 = ptHuman->ptWeaponQTask;
      v5[3].tQTaskRefList.ptHead = (struct QReference_s *)1;
      v5[1].tQTaskChildren.ptTail = nullptr;
      if ( ptTail )
      {
        ptParent = ptTail[16].ptParent;
        if ( ptParent != (struct QTask_s *)1 && ptParent != (struct QTask_s *)12 )
        {
          v15 = (int)ptTail[3].tQTaskRefList.ptTail;
          ClientFromHumanQTask = NetManager_GetClientFromHumanQTask(&ptHuman->tBoneDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask);
          NetManager_DropWeapon(ClientFromHumanQTask->eNetworkID, v15);
        }
      }
      if ( ptTail[16].tQTaskRefList.ptTail != (struct QReference_s *)8
        && ptHuman->tHumanParameters.eTeam == NetMission_eAttackingTeam )
      {
        WeaponTypeItemFromWeaponType = Weapon_GetWeaponTypeItemFromWeaponType(
                                         ptHuman->ptWeaponQTask,
                                         "WEAPON_ID_C4BOMB");
        if ( WeaponTypeItemFromWeaponType->isActive )
        {
          ptWeaponType = WeaponTypeItemFromWeaponType->ptWeaponType;
          if ( ptWeaponType )
          {
            eID = ptWeaponType->eID;
            v10 = NetManager_GetClientFromHumanQTask(&ptHuman->tBoneDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask);
            NetManager_DropWeapon(v10->eNetworkID, eID);
          }
        }
      }
    }
    v11 = ptHuman->ptWeaponQTask;
    ptHead = v11[4].tQTaskChildren.ptHead;
    if ( ptHead )
    {
      v13 = ptHead->tQTaskChildren.ptHead;
      if ( v13 )
        QTask_Delete(v13);
      QReference_Delete((struct QReference_s *)v11[4].tQTaskChildren.ptHead, &QTask_tQTaskRefPool);
      v11[4].tQTaskChildren.ptHead = nullptr;
    }
    v14 = ptHuman->tState.bSignal | 0x20000;
    ptHuman->isDead = 1;
    ptHuman->tState.bSignal = v14;
  }
}

// source: j/0/human/human.c:7371  [anchor-caller]
void __cdecl Human_HandleDeathCollision(
        struct QTask_s *ptQTask,
        struct real64x3_t *ptPos0,
        struct real64x3_t *ptPos1)
{
  char ptHead; // al
  struct QTask_s *ptParent; // edi
  bool v5; // dl
  double v6; // st7
  float *p_ptPrev; // edi
  double v8; // st7
  float *p_tQTaskChildren; // ecx
  double v10; // rt0
  long double v11; // st7
  double v12; // st7
  double v13; // st7
  double v14; // st7
  float tDelta; // [esp+8h] [ebp-18h]
  float tDelta_4; // [esp+Ch] [ebp-14h]
  float tDelta_8a; // [esp+10h] [ebp-10h]
  float tDelta_8; // [esp+10h] [ebp-10h]
  float tDelta_8b; // [esp+10h] [ebp-10h]
  struct QTask_s *tSpeed; // [esp+14h] [ebp-Ch]
  struct QTask_s *tSpeed_4; // [esp+18h] [ebp-8h]
  float tSpeed_8; // [esp+1Ch] [ebp-4h]

  ptHead = (char)ptQTask[29].tQTaskRefList.ptHead;
  ptQTask[50].tQTaskChildren.ptHead = nullptr;
  ptQTask[50].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[50].tQTaskChildren.ptTail = nullptr;
  if ( ptHead )
  {
    ptParent = ptQTask[32].ptParent;
    BYTE2(ptQTask[40].tQTaskChildren.ptMiddle) = 0;
    v5 = (int)ptParent > 150 && LOBYTE(ptQTask[32].tQTaskRefList.ptTail);
    v6 = *(double *)&ptQTask[43].tQTaskRefList.ptMiddle;
    BYTE2(ptQTask[50].ptNext) = v5;
    if ( v6 < 2048.0 )
      ptQTask[32].ptParent = (struct QTask_s *)((char *)&ptParent->ptNext + 1);
    if ( v5 )
    {
      ptQTask[38].ptPrev = nullptr;
      ptQTask[38].tQTaskChildren.ptHead = nullptr;
      ptQTask[38].tQTaskChildren.ptMiddle = nullptr;
    }
    else
    {
      p_ptPrev = (float *)&ptQTask[38].ptPrev;
      tSpeed = ptQTask[38].ptPrev;
      tSpeed_4 = ptQTask[38].tQTaskChildren.ptHead;
      tSpeed_8 = *(float *)&ptQTask[38].tQTaskChildren.ptMiddle - 44.600887298583984;
      *(float *)&ptQTask[38].ptPrev = ptPos1->vX - ptPos0->vX;
      *(float *)&ptQTask[38].tQTaskChildren.ptHead = ptPos1->vY - ptPos0->vY;
      v8 = ptPos1->vZ - ptPos0->vZ;
      *(float *)&ptQTask[38].tQTaskChildren.ptMiddle = v8;
      if ( v8 >= 0.0 )
        v8 = 0.0;
      *(float *)&ptQTask[38].tQTaskChildren.ptMiddle = v8 - 44.600887298583984;
      Human_CheckBoneCollision((struct Human_s *)ptQTask);
      p_tQTaskChildren = (float *)&ptQTask[50].tQTaskChildren;
      tDelta_8a = *(float *)&ptQTask[38].tQTaskChildren.ptMiddle + *(float *)&ptQTask[50].tQTaskChildren.ptTail;
      v10 = *(float *)&ptQTask[38].tQTaskChildren.ptHead + *(float *)&ptQTask[50].tQTaskChildren.ptMiddle;
      ptPos1->vX = *p_ptPrev + *(float *)&ptQTask[50].tQTaskChildren.ptHead + ptPos0->vX;
      ptPos1->vY = v10 + ptPos0->vY;
      ptPos1->vZ = tDelta_8a + ptPos0->vZ;
      *(float *)&ptQTask[38].tQTaskChildren.ptMiddle = tSpeed_8;
      if ( *(float *)&ptQTask[50].tQTaskChildren.ptHead == 0.0
        && *(float *)&ptQTask[50].tQTaskChildren.ptMiddle == 0.0
        && *(float *)&ptQTask[50].tQTaskChildren.ptTail == 0.0 )
      {
        *(_DWORD *)p_ptPrev = tSpeed;
        ptQTask[38].tQTaskChildren.ptHead = tSpeed_4;
        *(float *)&ptQTask[38].tQTaskChildren.ptMiddle = tSpeed_8;
      }
      else
      {
        tDelta = *p_tQTaskChildren;
        tDelta_4 = *(float *)&ptQTask[50].tQTaskChildren.ptMiddle;
        tDelta_8 = *(float *)&ptQTask[50].tQTaskChildren.ptTail;
        if ( *p_tQTaskChildren != 0.0 || tDelta_4 != 0.0 || tDelta_8 != 0.0 )
        {
          v11 = 1.0 / sqrt(tDelta * tDelta + tDelta_4 * tDelta_4 + tDelta_8 * tDelta_8);
          tDelta = tDelta * v11;
          tDelta_4 = tDelta_4 * v11;
          tDelta_8 = tDelta_8 * v11;
        }
        v12 = tDelta * *p_ptPrev + tDelta_4 * *(float *)&ptQTask[38].tQTaskChildren.ptHead + tDelta_8 * tSpeed_8;
        if ( v12 < 0.0 )
        {
          tDelta_8b = v12 * tDelta_8;
          *p_ptPrev = *p_ptPrev - tDelta * v12;
          *(float *)&ptQTask[38].tQTaskChildren.ptHead = *(float *)&ptQTask[38].tQTaskChildren.ptHead - v12 * tDelta_4;
          *(float *)&ptQTask[38].tQTaskChildren.ptMiddle = tSpeed_8 - tDelta_8b;
        }
      }
      v13 = *p_ptPrev;
      if ( v13 < 0.0 )
        v13 = -v13;
      if ( v13 < 27.30666732788086 )
      {
        v14 = *(float *)&ptQTask[38].tQTaskChildren.ptHead;
        if ( v14 < 0.0 )
          v14 = -v14;
        if ( v14 < 27.30666732788086 )
        {
          *p_ptPrev = 0.0;
          ptQTask[38].tQTaskChildren.ptHead = nullptr;
        }
      }
      if ( *(double *)&ptQTask[43].tQTaskRefList.ptMiddle < 2048.0 )
      {
        *p_ptPrev = *p_ptPrev * 0.699999988079071;
        *(float *)&ptQTask[38].tQTaskChildren.ptHead = *(float *)&ptQTask[38].tQTaskChildren.ptHead * 0.699999988079071;
      }
    }
    ptQTask[50].tQTaskChildren.ptHead = nullptr;
    ptQTask[50].tQTaskChildren.ptMiddle = nullptr;
    ptQTask[50].tQTaskChildren.ptTail = nullptr;
  }
}

// source: j/0/human/human.c:7464  [anchor-callee]
void __cdecl Human_InterpolateZAxisToAveragedGroundNormal(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct real32x3_t tReal32x3; };
    struct { char igi2_o1[12]; double avLength[2]; };
    struct { char igi2_o2[28]; struct real64x3_t atStartPos[1]; };
    struct { char igi2_o3[52]; struct QIntersection_s atIntersection[1]; };
    char igi2_extent[176];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  long double v1; // st7
  long double v2; // st6
  long double v3; // st7
  double v4; // st6
  double v5; // st6
  double vY; // st7
  int v7; // eax
  long double vX; // st7
  long double v9; // st6
  double v10; // st6

  LODWORD(igi2_frame.tReal32x3.vY) = ptQTask;
  v1 = sin(0.0) * 409.6000061035156;
  v2 = cos(0.0) * 409.6000061035156;
  *(float *)igi2_frame.avLength = v2 * *(float *)&ptQTask[3].tQTaskChildren.ptHead
                     + v1 * *(float *)&ptQTask[3].ptPrev
                     + *(float *)&ptQTask[3].tQTaskChildren.ptMiddle * 409.6000061035156;
  *((float *)igi2_frame.avLength + 1) = v2 * *(float *)&ptQTask[3].tQTaskRefList.ptHead
                           + v1 * *(float *)&ptQTask[3].tQTaskChildren.ptTail
                           + *(float *)&ptQTask[3].tQTaskRefList.ptMiddle * 409.6000061035156;
  v3 = v2 * *(float *)&ptQTask[3].ptParent
     + v1 * *(float *)&ptQTask[3].tQTaskRefList.ptTail
     + *(float *)&ptQTask[3].eQTaskType * 409.6000061035156;
  v4 = *(float *)igi2_frame.avLength;
  LODWORD(igi2_frame.avLength[0]) = 0;
  igi2_frame.atStartPos[0].vX = v4 + *(double *)&ptQTask[1].ptNext;
  v5 = *((float *)igi2_frame.avLength + 1);
  HIDWORD(igi2_frame.avLength[0]) = -1060634624;
  igi2_frame.atStartPos[0].vY = v5 + *(double *)&ptQTask[1].tQTaskChildren.ptHead;
  igi2_frame.atStartPos[0].vZ = v3 + *(double *)&ptQTask[1].tQTaskChildren.ptTail;
  World_GetNextZSpecificMesh(
    World_ptActiveWorld,
    igi2_frame.atIntersection,
    igi2_frame.atStartPos,
    1,
    igi2_frame.avLength,
    GameFunctions_eGetNextZEvaluateQTaskEvent,
    (struct CollisionEvaluateContext_s *)&igi2_frame.tReal32x3,
    0x98000000,
    1);
  vY = 0.0;
  v7 = 0;
  LODWORD(igi2_frame.avLength[0]) = 0;
  igi2_frame.tReal32x3.vX = 0.0;
  igi2_frame.tReal32x3.vZ = 0.0;
  if ( igi2_frame.atIntersection[0].isHit )
  {
    vX = igi2_frame.atIntersection[0].tNormal.vX;
    if ( igi2_frame.atIntersection[0].tNormal.vX != 0.0
      || igi2_frame.atIntersection[0].tNormal.vY != 0.0
      || igi2_frame.atIntersection[0].tNormal.vZ != 0.0 )
    {
      v9 = 1.0
         / sqrt(
             vX * vX
           + igi2_frame.atIntersection[0].tNormal.vY * igi2_frame.atIntersection[0].tNormal.vY
           + igi2_frame.atIntersection[0].tNormal.vZ * igi2_frame.atIntersection[0].tNormal.vZ);
      vX = igi2_frame.atIntersection[0].tNormal.vX * v9;
      igi2_frame.atIntersection[0].tNormal.vY = igi2_frame.atIntersection[0].tNormal.vY * v9;
      igi2_frame.atIntersection[0].tNormal.vZ = igi2_frame.atIntersection[0].tNormal.vZ * v9;
    }
    igi2_frame.tReal32x3.vX = vX;
    vY = igi2_frame.atIntersection[0].tNormal.vY;
    igi2_frame.tReal32x3.vZ = igi2_frame.atIntersection[0].tNormal.vZ;
    v7 = 1;
    LODWORD(igi2_frame.avLength[0]) = 1;
  }
  if ( v7 )
  {
    v10 = 1.0 / (double)SLODWORD(igi2_frame.avLength[0]);
    igi2_frame.tReal32x3.vY = v10 * vY;
    igi2_frame.tReal32x3.vZ = v10 * igi2_frame.tReal32x3.vZ;
    *(float *)&ptQTask[50].ptParent = (igi2_frame.tReal32x3.vX * v10 - *(float *)&ptQTask[50].ptParent) * 0.03333333507180214
                                    + *(float *)&ptQTask[50].ptParent;
    *(float *)&ptQTask[50].eQTaskType = (igi2_frame.tReal32x3.vY - *(float *)&ptQTask[50].eQTaskType) * 0.03333333507180214
                                      + *(float *)&ptQTask[50].eQTaskType;
    *(float *)&ptQTask[51].ptNext = (igi2_frame.tReal32x3.vZ - *(float *)&ptQTask[51].ptNext) * 0.03333333507180214
                                  + *(float *)&ptQTask[51].ptNext;
  }
}

// source: j/0/human/human.c:7542  [anchor-mhash]
void __cdecl Human_UpdatePosition(struct QTask_s *ptQTask)
{
  struct QReference_s *ptMiddle; // eax

  ptMiddle = ptQTask[44].tQTaskRefList.ptMiddle;
  if ( ptMiddle )
  {
    if ( ptMiddle->pxObject )
    {
      QReference_Delete(ptMiddle, &QTask_tQTaskRefPool);
      ptQTask[44].tQTaskRefList.ptMiddle = nullptr;
      HIBYTE(ptQTask[74].ptPrev) = 0;
    }
  }
}

// source: j/0/human/human.c:7555  [anchor-caller]
void __cdecl Human_Open()
{
  struct QTaskList_s *v0; // eax
  unsigned __int16 v1; // si
  __int16 v2; // ax
  __int16 v3; // ax
  __int16 v4; // ax
  __int16 v5; // ax
  __int16 v6; // ax
  struct ParameterList_s *v7; // eax
  int v8; // edx
  int v9; // edi
  char *v10; // esi
  int i; // esi
  int v12; // ecx
  unsigned int v13; // eax
  struct ParameterList_s *v14; // eax
  int v15; // edx
  struct ParameterList_s *v16; // ebx
  int v17; // esi
  struct ParameterList_s *v18; // eax
  struct ParameterListItem_s *ptParameterListItem; // esi
  unsigned int v20; // edx
  int *v21; // edi
  unsigned int *v22; // esi
  char v23; // cl
  int v24; // edx

  QTask_AllocateSystemGroup(1u);
  Human_eQTaskType = QTask_NewQTaskType("Human", 2984, BoneDynCubeObj_eQTaskType, 0, 0);
  QTask_SetQTaskTypeGroup(Human_eQTaskType, 1u);
  Human_eHumanUpdateQTaskEvent = QTask_NewQTaskEventFn(0, "HumanUpdate");
  Human_eEvaluateGunShotQTaskEvent = QTask_NewQTaskEventFn(0, "HumanEvaluateGunShot");
  Human_eCloseCombatDamageQTaskEvent = QTask_NewQTaskEventFn(0, "HumanCloseCombatDamage");
  Human_eKilledByYouQTaskEvent = QTask_NewQTaskEventFn(0, "HumanKilledByYou");
  Human_eHitByYouQTaskEvent = QTask_NewQTaskEventFn(0, "HumanHitByYou");
  Human_eUpdateInternalDataAfterCarryoverQTaskEvent = QTask_NewQTaskEventNoContextFn(0, "HumanUpdateAfterCarryover");
  v0 = QTaskList_New(128);
  v1 = Human_eQTaskType;
  Human_ptQTaskList = v0;
  QTask_LinkQTaskEventHandlerFn(Human_eQTaskType, Weapon_eGetWeaponObjectEvent, Human_GetWeaponObjectHandler);
  QTask_LinkQTaskEventHandlerFn(v1, Human_eKilledByYouQTaskEvent, Human_KilledByYouHandler);
  QTask_LinkQTaskEventHandlerFn(v1, Human_eHitByYouQTaskEvent, Human_HitByYouHandler);
  QTask_LinkQTaskEventHandlerFn(v1, 0, Human_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 1, Human_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 2, Human_DeleteHandler);
  QTask_LinkQTaskEventHandlerFn(v1, 5, Human_EnterHandler);
  QTask_LinkQTaskEventHandlerFn(v1, QCube_eGetClosestVertexQTaskEvent, Human_GetClosestVertexHandler);
  QTask_LinkQTaskEventHandlerFn(v1, 10, Human_TraceLinesHandler);
  QTask_LinkQTaskEventHandlerFn(v1, 9, Human_LineOfSightHandler);
  QTask_LinkQTaskEventHandlerFn(v1, Weapon_eGetParentParametersQTaskEvent, Human_WeaponGetParentParametersHandler);
  QTask_LinkQTaskEventHandlerFn(
    v1,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Human_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(v1, ParameterList_eUpdateInternalDataQTaskEvent, Human_UpdateInternalDataHandler);
  QTask_LinkQTaskEventHandlerFn(
    v1,
    GameFunctions_eWeaponCollisionEvaluateQTaskEvent,
    Human_WeaponCollisionEvaluateHandler);
  QTask_LinkQTaskEventHandlerFn(
    v1,
    GameFunctions_eObjectCollisionEvaluateQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Human_ObjectCollisionEvaluateHandler);
  QTask_LinkQTaskEventHandlerFn(
    v1,
    Particle2DDynCubeObj_eParticle2DCollisionEvaluateQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Human_Particle2DCollisionEvaluateHandler);
  QTask_LinkQTaskEventHandlerFn(v1, GameFunctions_eExplosionHitQTaskEvent, Human_ExplosionHitHandler);
  QTask_LinkQTaskEventHandlerFn(v1, DeathZone_eDeathZoneHitTestEvent, Human_DeathZoneHitTestHandler);
  QTask_LinkQTaskEventHandlerFn(v1, GameFunctions_eGetNextZEvaluateQTaskEvent, GameFunctions_GetNextZEvaluateHandler);
  QTask_LinkQTaskEventHandlerFn(v1, HumanCamera_eGetHumanCameraInfoQTaskEvent, Human_GetHumanCameraInfoHandler);
  v2 = HumanAI_eSendEventQTaskEvent;
  if ( HumanAI_eSendEventQTaskEvent == 512 )
  {
    v2 = QTask_NewQTaskEventFn(0, "HumanAISendEvent");
    v1 = Human_eQTaskType;
    HumanAI_eSendEventQTaskEvent = v2;
  }
  QTask_LinkQTaskEventHandlerFn(v1, v2, (void (__cdecl *)(struct QTask_s *, void *))sub_50AAC0);
  QTask_LinkQTaskEventHandlerFn(v1, AIDetection_eGetDetectionInfoQTaskEvent, Human_AIDetectionGetInfoHandler);
  QTask_LinkQTaskEventHandlerFn(
    v1,
    AIDetection_eLineOfSightQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Human_AIDetectionLineOfSightHandler);
  v3 = HumanAI_eCheckFirePathQTaskEvent;
  if ( HumanAI_eCheckFirePathQTaskEvent == 512 )
  {
    v3 = QTask_NewQTaskEventFn(0, "HumanAICheckFirePath");
    v1 = Human_eQTaskType;
    HumanAI_eCheckFirePathQTaskEvent = v3;
  }
  QTask_LinkQTaskEventHandlerFn(v1, v3, Human_AICheckFirePathHandler);
  QTask_LinkQTaskEventHandlerFn(v1, AmmoPickup_eAmmoPickupQTaskEvent, Human_AmmoPickupHandler);
  QTask_LinkQTaskEventHandlerFn(v1, GunPickup_eGunPickupQTaskEvent, Human_GunPickupHandler);
  QTask_LinkQTaskEventHandlerFn(
    v1,
    PhysicsObj_eMove,
    (void (__cdecl *)(struct QTask_s *, void *))Human_PhysicsObjMoveHandler);
  v4 = ComputerObject_eDrawComputerObjectQTaskEvent;
  if ( ComputerObject_eDrawComputerObjectQTaskEvent == 512 )
  {
    v4 = QTask_NewQTaskEventFn(0x200u, "DrawComputerObject");
    v1 = Human_eQTaskType;
    ComputerObject_eDrawComputerObjectQTaskEvent = v4;
  }
  QTask_LinkQTaskEventHandlerFn(v1, v4, Human_DrawComputerObjectHandler);
  QTask_LinkQTaskEventHandlerFn(
    v1,
    StatusScreen_eStatusDisplayQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Human_StatusDisplayHandler);
  v5 = SoundSys_eUpdateParameterListQTaskEvent;
  if ( SoundSys_eUpdateParameterListQTaskEvent == 512 )
  {
    v5 = QTask_NewQTaskEventFn(0, (char *)&g_zFileName.nRealFadeCount);
    v1 = Human_eQTaskType;
    SoundSys_eUpdateParameterListQTaskEvent = v5;
  }
  QTask_LinkQTaskEventHandlerFn(v1, v5, Human_SoundUpdateParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(v1, Human_eEvaluateGunShotQTaskEvent, Human_EvaluateGunShotHandler);
  QTask_LinkQTaskEventHandlerFn(
    v1,
    Grenade_eGetGrenadeHeldTimeQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Human_GetGrenadeHeldTimeHandler);
  QTask_LinkQTaskEventHandlerFn(v1, 13, (void (__cdecl *)(struct QTask_s *, void *))Human_EvaluateCollisionHandler);
  v6 = AIGraph_eNodeLinkCheckQTaskEvent;
  if ( AIGraph_eNodeLinkCheckQTaskEvent == 512 )
  {
    v6 = QTask_NewQTaskEventFn(0, "AIGraph_NodeLinkCheck");
    v1 = Human_eQTaskType;
    AIGraph_eNodeLinkCheckQTaskEvent = v6;
  }
  QTask_LinkQTaskEventHandlerFn(v1, v6, (void (__cdecl *)(struct QTask_s *, void *))Humam_NodeLinkCheckHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, Level_eRegisterLevelScriptSymbolsEvent, Human_RegisterScriptSymbolsHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, Level_eRemoveLevelScriptSymbolsEvent, Human_RemoveScriptSymbolsHandler);
  QTask_LinkQTaskEventHandlerFn(v1, DynCubeObj_eDynCubeObjRegisterQTaskEvent, Human_RegisterDynCubeObjHandler);
  QTask_LinkQTaskEventHandlerFn(v1, DynCubeObj_eDynCubeObjRemoveQTaskEvent, Human_RemoveDynCubeObjHandler);
  QTask_LinkQTaskEventHandlerFn(v1, ComputerMap_eFollowQTaskEvent, Human_ComputerMapFollowQTaskEventHandler);
  QTask_LinkQTaskEventHandlerFn(v1, AnimTrigger_eTriggerAnimTriggerQTaskEvent, Human_TriggerAnimTriggerHandler);
  QTask_LinkQTaskEventHandlerFn(v1, ShadowVolume_eGetShadowInfoEvent, Human_GetShadowInfoHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(
    v1,
    Human_eUpdateInternalDataAfterCarryoverQTaskEvent,
    Human_UpdateInternalDataAfterCarryoverHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, Attach_eUpdateAttachmentEvent, nullptr);
  QTask_LinkQTaskEventHandlerFn(
    v1,
    Grenade_eSmokeAreaQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Human_SmokeAreaHandler);
  v7 = (struct ParameterList_s *)Mem_AllocFn(112, 4);
  v8 = Level_eParameterTypeObjectPos;
  v7->ptParameterListItem = (struct ParameterListItem_s *)&v7[1];
  v7->nParameters = 0;
  v7->nMaxParameters = 5;
  Human_ptParameterList = v7;
  ParameterList_AddParameter(v7, 0x190u, v8, "Position", 7u, nullptr);
  ParameterList_AddParameter(Human_ptParameterList, 0x1A8u, Level_eParameterTypeAngle, "Gamma", 7u, nullptr);
  ParameterList_AddParameter(Human_ptParameterList, 0x1B0u, Level_eParameterTypeString16, "Model", 7u, nullptr);
  ParameterList_AddParameter(Human_ptParameterList, 0x1ACu, Level_eParameterTypeInt32, "Team", 7u, nullptr);
  ParameterList_AddParameter(Human_ptParameterList, 0x1D0u, Level_eParameterTypeVarString, "Weapon", 7u, nullptr);
  Symbol_Register(
    "Human_AddWeapon",
    Human_AddWeaponCB,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "Human_AddAmmo",
    Human_AddAmmoCB,
    nullptr,
    2,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "Human_AddAmmoForWeapon",
    Human_AddAmmoForWeaponCB,
    nullptr,
    -1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "Human_PopPosition",
    Human_PopPositionScriptFunction,
    nullptr,
    4,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Human_bAreaActivateCriteriaHuman = AreaActivateQTask_RegisterCriteria("CRITERIA_HUMAN", Human_AreaActivateAllHumansCB);
  v9 = 0;
  v10 = g_pfAreaActivateCB;
  do
  {
    sprintf(v10, "CRITERIA_HUMAN%d", v9);
    Human_abAreaActivateCriteriaHuman[v9] = AreaActivateQTask_RegisterCriteria(v10, Human_AreaActivateTeamCB);
    v10 += 32;
    ++v9;
  }
  while ( (int)v10 < 127853256 );
  for ( i = 0; i < 2; ++i )
    Symbol_Register(
      Human_apzTeamStrings[i],
      (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
      (void *)i,
      4,
      QSCRIPT_SYMBOLCLASS_CONSTANT,
      QSCRIPT_SYMBOLTYPE_INT,
      QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Human_ptUpdateActivateProfileRegion = nullptr;
  Human_ptMoveProfileRegion = nullptr;
  Human_ptNotifyProfileRegion = nullptr;
  Human_ptGroundCollisionProfileRegion = nullptr;
  Human_ptUpdateBodyProfileRegion = nullptr;
  Human_ptObjectCollisionProfileRegion = nullptr;
  Human_ptCollisionProfileRegion = nullptr;
  Human_ptMoveUpdateAttachmentsProfileRegion = nullptr;
  Symbol_Register(
    "Human_GetCutSceneDeltaTime",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Human_GetCutSceneDeltaTimeCB,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Human_ptShadow = GameFunctions_RegisterGameTexture("shadow1.tex");
  Human_ptBloodPuddle = GameFunctions_RegisterGameTexture("bloodpool.tex");
  v12 = 0;
  while ( AIDetection_aeMaskQTaskTypeList[v12] != 512 )
  {
    if ( ++v12 >= 32 )
    {
      v13 = 0;
      goto LABEL_19;
    }
  }
  AIDetection_aeMaskQTaskTypeList[v12] = Human_eQTaskType;
  v13 = 1 << v12;
LABEL_19:
  Human_bAIDetectionQTaskMask = v13;
  Symbol_Register(
    "TASKTYPE_HUMAN",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)Human_eQTaskType,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "HUMANANIM_TRIGGER_OPENDRAWER",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    nullptr,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "HUMANANIM_TRIGGER_CLOSEDRAWER",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)1,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "HUMANANIM_TRIGGER_DROPWEAPON",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)2,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "HUMANANIM_TRIGGER_THROWGRENADE",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)3,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "HUMANANIM_TRIGGER_TIMEGRENADE",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)4,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "HUMANANIM_TRIGGER_EMPTYBARREL",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)5,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "HUMANANIM_TRIGGER_LOADBARREL",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)6,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "HUMANANIM_TRIGGER_STOPANIMATION",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)8,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "HUMANANIM_TRIGGER_FEETSOUND",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)0x3F2,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "HUMANANIM_TRIGGER_THROWGRENADE_CREATE",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)9,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "HUMANANIM_TRIGGER_THROWGRENADE_ACTIVATE",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)0xA,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "HUMANANIM_TRIGGER_THROWGRENADE_RELEASE",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)0xB,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "HUMANANIM_TRIGGER_CLOSECOMBAT_DEALDAMAGE",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)0xC,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "HUMANANIM_TRIGGER_DEADBODY_SOUND",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)0xD,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  v14 = (struct ParameterList_s *)Mem_AllocFn(132, 4);
  v15 = Level_eParameterTypeInt32;
  v14->ptParameterListItem = (struct ParameterListItem_s *)&v14[1];
  v14->nParameters = 0;
  v14->nMaxParameters = 6;
  Human_ptSerializeStateParameterList = v14;
  ParameterList_AddParameter(v14, 0xCu, v15, "bStateSignal", 7u, nullptr);
  ParameterList_AddParameter(
    Human_ptSerializeStateParameterList,
    0x20u,
    Level_eParameterTypeInt32,
    "nStateCompletedSequence",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Human_ptSerializeStateParameterList,
    0x10u,
    Level_eParameterTypeInt32,
    "nStatePreviousState",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Human_ptSerializeStateParameterList,
    0x1Cu,
    Level_eParameterTypeInt32,
    "nStateSequence",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Human_ptSerializeStateParameterList,
    0x14u,
    Level_eParameterTypeInt32,
    "nStateState",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Human_ptSerializeStateParameterList,
    0x28u,
    SerializeArray_eParameterType,
    "atStateSequenceWork",
    7u,
    (void *)0x28);
  v16 = ModelObjParameters_ptSerializeParameterList;
  v17 = ModelObjParameters_ptSerializeParameterList->nParameters + 82;
  v18 = (struct ParameterList_s *)Mem_AllocFn(20 * v17 + 12, 4);
  v18->nParameters = 0;
  v18->nMaxParameters = v17;
  v18->ptParameterListItem = (struct ParameterListItem_s *)&v18[1];
  ptParameterListItem = v16->ptParameterListItem;
  v20 = 20 * v16->nParameters;
  qmemcpy(&v18[1], ptParameterListItem, 4 * (v20 >> 2));
  v22 = &ptParameterListItem->nOffset + (v20 >> 2);
  v21 = &v18[1].nParameters + (v20 >> 2);
  v23 = v20;
  v24 = SerializeArray_eParameterType;
  qmemcpy(v21, v22, v23 & 3);
  v18->nParameters = v16->nParameters;
  Human_ptSerializeParameterList = v18;
  ParameterList_AddParameter(v18, 0x200u, v24, "avLastChannel", 7u, (void *)0xFC);
  ParameterList_AddParameter(
    Human_ptSerializeParameterList,
    0x2FCu,
    SerializeArray_eParameterType,
    "avChannel",
    7u,
    (void *)0xFC);
  ParameterList_AddParameter(Human_ptSerializeParameterList, 0x3FCu, Level_eParameterTypeReal32, "Damage", 7u, nullptr);
  ParameterList_AddParameter(
    Human_ptSerializeParameterList,
    0x3F8u,
    Level_eParameterTypebool8,
    "isLockChannel",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Human_ptSerializeParameterList,
    0x51Cu,
    Level_eParameterTypebool8,
    "isDeathAnimationDone",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Human_ptSerializeParameterList,
    0x530u,
    Level_eParameterTypebool8,
    "isWeaponReady",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Human_ptSerializeParameterList,
    0x531u,
    Level_eParameterTypebool8,
    "isWeaponFire",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Human_ptSerializeParameterList,
    0x532u,
    Level_eParameterTypebool8,
    "isWeaponAlternateFire",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Human_ptSerializeParameterList,
    0x533u,
    Level_eParameterTypebool8,
    "isWeaponFired",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Human_ptSerializeParameterList,
    0x540u,
    Level_eParameterTypebool8,
    "isThirdPerson",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Human_ptSerializeParameterList,
    0x55Cu,
    Level_eParameterTypebool8,
    "isLockOrientation",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Human_ptSerializeParameterList,
    0x5B0u,
    Level_eParameterTypebool8,
    "isDisableDeltaTranslation",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Human_ptSerializeParameterList,
    0x5B1u,
    Level_eParameterTypebool8,
    "isDisableDeltaTranslationScale",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Human_ptSerializeParameterList,
    0x5B8u,
    Level_eParameterTypebool8,
    "isRotateUpperBody",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Human_ptSerializeParameterList,
    0x64Cu,
    Level_eParameterTypebool8,
    "isDisableCollision",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Human_ptSerializeParameterList,
    0x64Du,
    Level_eParameterTypebool8,
    "isGroundCollision",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Human_ptSerializeParameterList,
    0x64Eu,
    Level_eParameterTypebool8,
    "isObjectCollision",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Human_ptSerializeParameterList,
    0x64Fu,
    Level_eParameterTypebool8,
    "isRoofCollision",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Human_ptSerializeParameterList,
    0x650u,
    Level_eParameterTypebool8,
    "isHumanCollision",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Human_ptSerializeParameterList,
    0x748u,
    Level_eParameterTypebool8,
    "isLockActivate",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Human_ptSerializeParameterList,
    0x749u,
    Level_eParameterTypebool8,
    "isCheckActivateButton",
    7u,
    nullptr);
  ParameterList_AddParameter(Human_ptSerializeParameterList, 0x754u, Level_eParameterTypebool8, "isDelete", 7u, nullptr);
  ParameterList_AddParameter(Human_ptSerializeParameterList, 0x780u, Level_eParameterTypebool8, "isShadow", 7u, nullptr);
  ParameterList_AddParameter(
    Human_ptSerializeParameterList,
    0x788u,
    Level_eParameterTypebool8,
    "isShadowPosValid",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Human_ptSerializeParameterList,
    0x7B4u,
    Level_eParameterTypebool8,
    "isSymbolsCreated",
    7u,
    nullptr);
  ParameterList_AddParameter(Human_ptSerializeParameterList, 0x49Cu, Level_eParameterTypebool8, "isDead", 7u, nullptr);
  ParameterList_AddParameter(Human_ptSerializeParameterList, 0x524u, Level_eParameterTypeInt32, "ePose", 7u, nullptr);
  ParameterList_AddParameter(
    Human_ptSerializeParameterList,
    0x53Cu,
    Level_eParameterTypeInt32,
    "eHumanCameraMode",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Human_ptSerializeParameterList,
    0x74Cu,
    Level_eParameterTypeInt32,
    "nActivateTime",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Human_ptSerializeParameterList,
    0x750u,
    Level_eParameterTypeInt32,
    "nLastDrawTick",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Human_ptSerializeParameterList,
    0x7A8u,
    Level_eParameterTypeInt32,
    "nNextHitTick",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Human_ptSerializeParameterList,
    0x7ACu,
    Level_eParameterTypeInt32,
    "nNextGunShotMissTick",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Human_ptSerializeParameterList,
    0x7B0u,
    Level_eParameterTypeInt32,
    "nFeetSoundSequence",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Human_ptSerializeParameterList,
    0x534u,
    Level_eParameterTypeReal32,
    "vWeaponHitProbability",
    7u,
    nullptr);
  ParameterList_AddParameter(Human_ptSerializeParameterList, 0x544u, Level_eParameterTypeReal32, "vAlpha", 7u, nullptr);
  ParameterList_AddParameter(
    Human_ptSerializeParameterList,
    0x548u,
    Level_eParameterTypeReal32,
    "vIdealAlpha",
    7u,
    nullptr);
  ParameterList_AddParameter(Human_ptSerializeParameterList, 0x54Cu, Level_eParameterTypeReal32, "vBeta", 7u, nullptr);
  ParameterList_AddParameter(
    Human_ptSerializeParameterList,
    0x550u,
    Level_eParameterTypeReal32,
    "vIdealBeta",
    7u,
    nullptr);
  ParameterList_AddParameter(Human_ptSerializeParameterList, 0x554u, Level_eParameterTypeReal32, "vGamma", 7u, nullptr);
  ParameterList_AddParameter(
    Human_ptSerializeParameterList,
    0x558u,
    Level_eParameterTypeReal32,
    "vIdealGamma",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Human_ptSerializeParameterList,
    0x5B4u,
    Level_eParameterTypeReal32,
    "vAnimTimeScale",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Human_ptSerializeParameterList,
    0x6DCu,
    Level_eParameterTypeReal32,
    "vGroundAngle",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Human_ptSerializeParameterList,
    0x6E0u,
    Level_eParameterTypeReal32,
    "vGroundAngleFactor",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Human_ptSerializeParameterList,
    0x790u,
    Level_eParameterTypeReal32,
    "vShadowDistance",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Human_ptSerializeParameterList,
    0x7C0u,
    Level_eParameterTypeReal32,
    "vVisibilityFactor",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Human_ptSerializeParameterList,
    0x5A4u,
    Level_eParameterTypeReal32x3,
    "tDeltaTranslation",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Human_ptSerializeParameterList,
    0x5F4u,
    Level_eParameterTypeReal32x3,
    "tSpeed",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Human_ptSerializeParameterList,
    0x600u,
    Level_eParameterTypeReal32x3,
    "tImpactSpeed",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Human_ptSerializeParameterList,
    0x60Cu,
    Level_eParameterTypeReal32x3,
    "tTotalSpeed",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Human_ptSerializeParameterList,
    0x794u,
    Level_eParameterTypeReal32x3,
    "tShadowNormal",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Human_ptSerializeParameterList,
    0x5BCu,
    Level_eParameterTypeQuat32,
    "tUpperBodyOrientation",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Human_ptSerializeParameterList,
    0x6D0u,
    Level_eParameterTypeReal64,
    "vDistanceToGround",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Human_ptSerializeParameterList,
    0x6F0u,
    Level_eParameterTypeReal64,
    "vDistanceToRoof",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Human_ptSerializeParameterList,
    0x700u,
    Level_eParameterTypeReal64x3,
    "tAttachPos",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Human_ptSerializeParameterList,
    0x760u,
    Level_eParameterTypeReal64x3,
    "tShadowPos",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Human_ptSerializeParameterList,
    0x718u,
    Level_eParameterTypeReal32x9,
    "tAttachOrientation",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Human_ptSerializeParameterList,
    0x1D8u,
    Level_eParameterTypeInt32,
    "eGameDifficulty",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Human_ptSerializeParameterList,
    0x1DCu,
    Level_eParameterTypeInt32,
    "iMissionID",
    7u,
    nullptr);
  ParameterList_AddParameter(Human_ptSerializeParameterList, 0x1E0u, Level_eParameterTypeInt32, "nSpotted", 7u, nullptr);
  ParameterList_AddParameter(Human_ptSerializeParameterList, 0x1E4u, Level_eParameterTypeInt32, "nShots", 7u, nullptr);
  ParameterList_AddParameter(Human_ptSerializeParameterList, 0x1E8u, Level_eParameterTypeInt32, "nKills", 7u, nullptr);
  ParameterList_AddParameter(Human_ptSerializeParameterList, 0x1ECu, Level_eParameterTypeInt32, "nHits", 7u, nullptr);
  ParameterList_AddParameter(
    Human_ptSerializeParameterList,
    0x1F0u,
    Level_eParameterTypeInt32,
    "nGameLoads",
    7u,
    nullptr);
  ParameterList_AddParameter(Human_ptSerializeParameterList, 0x1F4u, Level_eParameterTypeInt32, "nTime", 7u, nullptr);
  ParameterList_AddParameter(
    Human_ptSerializeParameterList,
    0x1F8u,
    Level_eParameterTypeInt32,
    "nTimesAlarmTriggered",
    7u,
    nullptr);
  ParameterList_AddParameter(Human_ptSerializeParameterList, 0x1FCu, Level_eParameterTypeInt32, "nHealth", 7u, nullptr);
  ParameterList_AddParameter(
    Human_ptSerializeParameterList,
    0x80Cu,
    Level_eParameterTypeInt32,
    "nClimbLadderSoundSequence",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Human_ptSerializeParameterList,
    0x4C8u,
    SerializeStruct_eParameterType,
    "State",
    7u,
    Human_ptSerializeStateParameterList);
  ParameterList_AddParameter(
    Human_ptSerializeParameterList,
    0x6F8u,
    SerializeQTaskRef_eParameterType,
    "ptGroundQTaskRef",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Human_ptSerializeParameterList,
    0xAF0u,
    Level_eParameterTypeReal64x3,
    "tGroundRelativePos",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Human_ptSerializeParameterList,
    0xB08u,
    Level_eParameterTypeReal64x3,
    "tGroundPrevPos",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Human_ptSerializeParameterList,
    0xB20u,
    Level_eParameterTypeReal64x3,
    "tGroundOriginalPos",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Human_ptSerializeParameterList,
    0xB38u,
    Level_eParameterTypeReal32x3,
    "tGroundSpeed",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Human_ptSerializeParameterList,
    0xB44u,
    SerializeArray_eParameterType,
    "tGroundInverseOriginalOrientation",
    7u,
    (void *)0x28);
  ParameterList_AddParameter(
    Human_ptSerializeParameterList,
    0xB6Cu,
    SerializeArray_eParameterType,
    "tGroundRelativeOrientation",
    7u,
    (void *)0x28);
  ParameterList_AddParameter(
    Human_ptSerializeParameterList,
    0xB95u,
    Level_eParameterTypebool8,
    "isUpdatePlatformPos",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Human_ptSerializeParameterList,
    0xB96u,
    Level_eParameterTypebool8,
    "isPlatformMoving",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Human_ptSerializeParameterList,
    0xB97u,
    Level_eParameterTypebool8,
    "isGroundRigidObj",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Human_ptSerializeParameterList,
    0xB94u,
    Level_eParameterTypebool8,
    "isProtectedFromFallDamage",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Human_ptSerializeParameterList,
    0x690u,
    Level_eParameterTypeReal32x3,
    "tGroundNormal",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Human_ptSerializeParameterList,
    0x5D0u,
    Level_eParameterTypeReal32x3,
    "tSlidingSpeed",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Human_ptSerializeParameterList,
    0x4A0u,
    Level_eParameterTypeReal32x9,
    "tDeadOrientation",
    7u,
    nullptr);
  LOWORD(v22) = QTask_NewQTaskType("HumanShadow", 264, ShadowVolume_eQTaskType, 0, 0);
  HumanShadow_eQTaskType = (unsigned __int16)v22;
  QTask_LinkQTaskEventHandlerFn((unsigned __int16)v22, 0, HumanShadow_CreateHandler);
  Symbol_Register(
    "TASKTYPE_HUMANSHADOW",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)(unsigned __int16)v22,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
}

// source: j/0/human/human.c:7816  [anchor-hash]
void __cdecl Human_Close()
{
  int v0; // esi
  int v1; // esi
  int v2; // esi
  int v3; // ecx
  int i; // eax
  int v5; // eax
  int *v6; // esi
  int v7; // ecx
  int j; // eax
  int v9; // eax
  char **v10; // esi

  QTaskList_Delete(Human_ptQTaskList);
  if ( Human_ptParameterList )
  {
    v0 = *(_DWORD *)((unsigned int)&Human_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
  if ( Human_ptSerializeParameterList )
  {
    v1 = *(_DWORD *)((unsigned int)&Human_ptSerializeParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v1);
    memset(*(void **)(v1 + 8), 0xCDu, *(_DWORD *)(v1 + 16));
    free((void *)v1);
  }
  if ( Human_ptSerializeStateParameterList )
  {
    v2 = *(_DWORD *)((unsigned int)&Human_ptSerializeStateParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v2);
    memset(*(void **)(v2 + 8), 0xCDu, *(_DWORD *)(v2 + 16));
    free((void *)v2);
  }
  QTask_DeleteQTaskEvent(Human_eHumanUpdateQTaskEvent);
  if ( Human_eHumanWeaponFireQTaskEvent != 512 )
    QTask_DeleteQTaskEvent(Human_eHumanWeaponFireQTaskEvent);
  if ( Human_eHumanWeaponReloadQTaskEvent != 512 )
    QTask_DeleteQTaskEvent(Human_eHumanWeaponReloadQTaskEvent);
  QTask_DeleteQTaskEvent(Human_eHitByYouQTaskEvent);
  QTask_DeleteQTaskEvent(Human_eKilledByYouQTaskEvent);
  QTask_DeleteQTaskEvent(Human_eEvaluateGunShotQTaskEvent);
  QTask_DeleteQTaskEvent(Human_eCloseCombatDamageQTaskEvent);
  QTask_DeleteQTaskEventNoContext(Human_eUpdateInternalDataAfterCarryoverQTaskEvent);
  QTask_DeleteQTaskType(Human_eQTaskType);
  v3 = Human_bAreaActivateCriteriaHuman;
  for ( i = 0; (v3 & 1) == 0; ++i )
    v3 >>= 1;
  v5 = i;
  AreaActivate_atCriteria[v5].isUsed = 0;
  Symbol_Remove(AreaActivate_atCriteria[v5].zName);
  v6 = Human_abAreaActivateCriteriaHuman;
  do
  {
    v7 = *v6;
    for ( j = 0; (v7 & 1) == 0; ++j )
      v7 >>= 1;
    v9 = j;
    AreaActivate_atCriteria[v9].isUsed = 0;
    Symbol_Remove(AreaActivate_atCriteria[v9].zName);
    ++v6;
  }
  while ( (int)v6 < 127853292 );
  v10 = Human_apzTeamStrings;
  do
    Symbol_Remove(*v10++);
  while ( (int)v10 < 7044356 );
  QTask_FreeGroup(1u);
  QTask_DeleteQTaskType(HumanShadow_eQTaskType);
  Symbol_Remove("TASKTYPE_HUMANSHADOW");
}

// source: j/0/human/human.c:7905  [anchor-callee]
enum bool __cdecl Human_IsGammaRotationAllowed(
        struct QTask_s *ptQTask,
        struct real32x9_t *ptOrientation,
        struct real64x3_t *ptCenterPosition,
        struct real32x3_t *ptLocalFrontPoint,
        struct real32x3_t *ptLocalRearPoint,
        float vGamma,
        int *pbHitBits,
        struct real32x3_t *ptAvgHitNormal)
{
  #pragma pack(push, 1)
  union
  {
    struct { int nNumLines; };
    struct { char igi2_o1[4]; struct real64x3_t *v34; };
    struct { char igi2_o2[8]; double *p_vZ; };
    struct { char igi2_o3[12]; float Real32x3_Rotate_tTemp; };
    struct { char igi2_o4[12]; float Real32x3_Rotate_tTempa; };
    struct { char igi2_o5[16]; float Real32x3_Rotate_tTemp_4; };
    struct { char igi2_o6[16]; float Real32x3_Rotate_tTemp_4a; };
    struct { char igi2_o7[20]; float Real32x3_Rotate_tTemp_8; };
    struct { char igi2_o8[24]; struct real64x3_t *v41; };
    struct { char igi2_o9[28]; enum bool isAllowed; };
    struct { char igi2_o10[32]; int nHits; };
    struct { char igi2_o11[36]; double *p_vY; };
    struct { char igi2_o12[40]; struct ObjectCollisionEvaluateContext_t tObjectCollisionEvaluateContext; };
    struct { char igi2_o13[48]; float v46; };
    struct { char igi2_o14[52]; float v47; };
    struct { char igi2_o15[56]; float v48; };
    struct { char igi2_o16[60]; float vGammaSign; };
    struct { char igi2_o17[64]; float v50; };
    struct { char igi2_o18[68]; float v51; };
    struct { char igi2_o19[76]; float v52; };
    struct { char igi2_o20[88]; struct real64x3_t tStart; };
    struct { char igi2_o21[112]; struct real64x3_t atEnd[72]; };
    struct { char igi2_o22[1840]; struct real64x3_t atStart[72]; };
    struct { char igi2_o23[3568]; struct QIntersection_s atIntersection[72]; };
    char igi2_extent[12212];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct real32x3_t *v8; // esi
  double vZ; // st7
  double v10; // st6
  struct real64x3_t *v11; // edi
  double v12; // st6
  double v13; // st7
  long double v14; // st6
  long double v15; // st5
  double v16; // st3
  double v17; // st3
  long double v18; // st4
  long double v19; // st3
  long double v20; // st6
  double v21; // st5
  long double v22; // st6
  struct real32x3_t *p_tNormal; // ecx
  double v24; // st7
  double v25; // st7
  int v26; // eax
  int v27; // edx
  int v28; // eax
  double vX; // st7
  long double v30; // st7
  enum bool result; // eax
  double v32; // st7

  *pbHitBits = 0;
  v8 = ptAvgHitNormal;
  ptAvgHitNormal->vX = 0.0;
  ptAvgHitNormal->vY = 0.0;
  ptAvgHitNormal->vZ = 0.0;
  vZ = ptLocalFrontPoint->vZ;
  v10 = ptOrientation->tX.vX + ptOrientation->tX.vY;
  v11 = ptCenterPosition;
  igi2_frame.isAllowed = true;
  igi2_frame.nHits = 0;
  igi2_frame.vGammaSign = 1.0;
  v12 = v10 * 0.0 + vZ * ptOrientation->tX.vZ;
  igi2_frame.v47 = (ptOrientation->tY.vX + ptOrientation->tY.vY) * 0.0 + vZ * ptOrientation->tY.vZ;
  igi2_frame.v48 = (ptOrientation->tZ.vX + ptOrientation->tZ.vY) * 0.0 + vZ * ptOrientation->tZ.vZ;
  igi2_frame.tStart.vX = v12 + ptCenterPosition->vX;
  igi2_frame.tStart.vY = igi2_frame.v47 + ptCenterPosition->vY;
  igi2_frame.tStart.vZ = igi2_frame.v48 + ptCenterPosition->vZ;
  if ( vGamma < 0.0 )
  {
    igi2_frame.vGammaSign = -1.0;
    vGamma = -vGamma;
  }
  v13 = 0.0;
  igi2_frame.nNumLines = 0;
  if ( vGamma != 0.0 )
  {
    igi2_frame.p_vZ = &igi2_frame.atEnd[0].vZ;
    igi2_frame.p_vY = &igi2_frame.atEnd[0].vY;
    igi2_frame.v41 = igi2_frame.atEnd;
    igi2_frame.v34 = igi2_frame.atStart;
    do
    {
      if ( vGamma <= 0.1745329350233078 )
      {
        v13 = v13 + vGamma;
        vGamma = 0.0;
      }
      else
      {
        v13 = v13 + 0.1745329350233078;
        vGamma = vGamma - 0.1745329350233078;
      }
      if ( igi2_frame.nNumLines >= 71 )
        break;
      qmemcpy(igi2_frame.v34, &igi2_frame.tStart, sizeof(struct real64x3_t));
      v14 = sin(igi2_frame.vGammaSign * v13);
      v15 = cos(igi2_frame.vGammaSign * v13);
      v16 = ptLocalFrontPoint->vZ * 0.0;
      igi2_frame.Real32x3_Rotate_tTemp = -v14 * ptLocalFrontPoint->vY + v15 * ptLocalFrontPoint->vX + v16;
      igi2_frame.Real32x3_Rotate_tTemp_4 = v15 * ptLocalFrontPoint->vY + v14 * ptLocalFrontPoint->vX + v16;
      v17 = (ptLocalFrontPoint->vX + ptLocalFrontPoint->vY) * 0.0 + ptLocalFrontPoint->vZ;
      igi2_frame.v46 = v17 * ptOrientation->tX.vZ
          + igi2_frame.Real32x3_Rotate_tTemp_4 * ptOrientation->tX.vY
          + igi2_frame.Real32x3_Rotate_tTemp * ptOrientation->tX.vX;
      igi2_frame.v47 = igi2_frame.Real32x3_Rotate_tTemp * ptOrientation->tY.vX
          + v17 * ptOrientation->tY.vZ
          + igi2_frame.Real32x3_Rotate_tTemp_4 * ptOrientation->tY.vY;
      igi2_frame.v48 = igi2_frame.Real32x3_Rotate_tTemp * ptOrientation->tZ.vX
          + v17 * ptOrientation->tZ.vZ
          + igi2_frame.Real32x3_Rotate_tTemp_4 * ptOrientation->tZ.vY;
      igi2_frame.v41->vX = igi2_frame.v46 + ptCenterPosition->vX;
      *igi2_frame.p_vY = igi2_frame.v47 + ptCenterPosition->vY;
      *igi2_frame.p_vZ = igi2_frame.v48 + ptCenterPosition->vZ;
      *(float *)&igi2_frame.tObjectCollisionEvaluateContext.tCollisionEvaluateContext.isEvaluate = ptLocalRearPoint->vZ * 0.0;
      v18 = v15 * ptLocalRearPoint->vX;
      v19 = -v14 * ptLocalRearPoint->vY;
      qmemcpy(&igi2_frame.v34[1], &igi2_frame.tStart, sizeof(struct real64x3_t));
      igi2_frame.v52 = v18 + v19 + *(float *)&igi2_frame.tObjectCollisionEvaluateContext.tCollisionEvaluateContext.isEvaluate;
      igi2_frame.nNumLines += 2;
      v20 = v15 * ptLocalRearPoint->vY
          + v14 * ptLocalRearPoint->vX
          + *(float *)&igi2_frame.tObjectCollisionEvaluateContext.tCollisionEvaluateContext.isEvaluate;
      igi2_frame.v34 += 2;
      igi2_frame.v41 += 2;
      igi2_frame.p_vY += 6;
      v21 = (ptLocalRearPoint->vY + ptLocalRearPoint->vX) * 0.0 + ptLocalRearPoint->vZ;
      igi2_frame.v50 = v21 * ptOrientation->tX.vZ + v20 * ptOrientation->tX.vY + igi2_frame.v52 * ptOrientation->tX.vX;
      igi2_frame.v51 = igi2_frame.v52 * ptOrientation->tY.vX + v21 * ptOrientation->tY.vZ + v20 * ptOrientation->tY.vY;
      v22 = igi2_frame.v52 * ptOrientation->tZ.vX + v21 * ptOrientation->tZ.vZ + v20 * ptOrientation->tZ.vY;
      igi2_frame.v41[-1].vX = igi2_frame.v50 + ptCenterPosition->vX;
      *(igi2_frame.p_vY - 3) = igi2_frame.v51 + ptCenterPosition->vY;
      igi2_frame.p_vZ += 6;
      *(igi2_frame.p_vZ - 3) = v22 + ptCenterPosition->vZ;
      v8 = ptAvgHitNormal;
      v11 = ptCenterPosition;
    }
    while ( vGamma != 0.0 );
  }
  igi2_frame.tObjectCollisionEvaluateContext.tCollisionEvaluateContext.ptQTask = ptQTask;
  World_TraceLinesSpecificMesh(
    Game_ptGame->ptWorld,
    igi2_frame.atIntersection,
    igi2_frame.atStart,
    igi2_frame.atEnd,
    igi2_frame.nNumLines,
    GameFunctions_eObjectCollisionEvaluateQTaskEvent,
    &igi2_frame.tObjectCollisionEvaluateContext.tCollisionEvaluateContext,
    Forest_bQTaskGroup | 0x18000000,
    1);
  if ( igi2_frame.nNumLines <= 0 )
    return true;
  p_tNormal = &igi2_frame.atIntersection[0].tNormal;
  *(_DWORD *)&igi2_frame.tObjectCollisionEvaluateContext.tCollisionEvaluateContext.isEvaluate = igi2_frame.nNumLines;
  do
  {
    if ( LODWORD(p_tNormal[3].vX) )
    {
      v24 = p_tNormal->vZ;
      if ( v24 < 0.0 )
        v24 = -v24;
      if ( v24 < 0.5 )
      {
        igi2_frame.isAllowed = false;
        igi2_frame.Real32x3_Rotate_tTempa = *(double *)&p_tNormal[-4].vX - v11->vX;
        igi2_frame.Real32x3_Rotate_tTemp_4a = *(double *)&p_tNormal[-4].vZ - v11->vY;
        igi2_frame.Real32x3_Rotate_tTemp_8 = *(double *)&p_tNormal[-3].vY - v11->vZ;
        v25 = igi2_frame.Real32x3_Rotate_tTemp_4a * ptOrientation->tY.vX
            + igi2_frame.Real32x3_Rotate_tTemp_8 * ptOrientation->tZ.vX
            + igi2_frame.Real32x3_Rotate_tTempa * ptOrientation->tX.vX;
        v26 = 1;
        if ( igi2_frame.Real32x3_Rotate_tTemp_4a * ptOrientation->tY.vY
           + igi2_frame.Real32x3_Rotate_tTempa * ptOrientation->tX.vY
           + igi2_frame.Real32x3_Rotate_tTemp_8 * ptOrientation->tZ.vY < 0.0 )
          v26 = 2;
        v27 = v26 | *pbHitBits;
        *pbHitBits = v27;
        v28 = 4;
        if ( v25 < 0.0 )
          v28 = 8;
        vX = p_tNormal->vX;
        ++igi2_frame.nHits;
        *pbHitBits = v28 | v27;
        if ( vX != 0.0 || p_tNormal->vY != 0.0 || p_tNormal->vZ != 0.0 )
        {
          v30 = 1.0
              / sqrt(p_tNormal->vZ * p_tNormal->vZ + p_tNormal->vY * p_tNormal->vY + p_tNormal->vX * p_tNormal->vX);
          p_tNormal->vX = p_tNormal->vX * v30;
          p_tNormal->vY = p_tNormal->vY * v30;
          p_tNormal->vZ = p_tNormal->vZ * v30;
        }
        v8->vX = v8->vX + p_tNormal->vX;
        v8->vY = v8->vY + p_tNormal->vY;
        v8->vZ = p_tNormal->vZ + v8->vZ;
      }
    }
    p_tNormal += 10;
    --*(_DWORD *)&igi2_frame.tObjectCollisionEvaluateContext.tCollisionEvaluateContext.isEvaluate;
  }
  while ( *(_DWORD *)&igi2_frame.tObjectCollisionEvaluateContext.tCollisionEvaluateContext.isEvaluate );
  result = igi2_frame.isAllowed;
  if ( igi2_frame.nHits )
  {
    v32 = 1.0 / (double)igi2_frame.nHits;
    v8->vX = v32 * v8->vX;
    v8->vY = v32 * v8->vY;
    v8->vZ = v32 * v8->vZ;
  }
  return result;
}

// source: j/0/human/human.c:8042  [anchor-strings]
void __cdecl Human_CreateSwimStrokeSound(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { char zSound[32]; };
    struct { char igi2_o1[32]; int v6; };
    struct { char igi2_o2[36]; int v7; };
    struct { char igi2_o3[40]; int v8; };
    struct { char igi2_o4[44]; int v9; };
    char igi2_extent[48];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v1; // eax
  bool v2; // cf
  struct QReference_s *v3; // eax
  struct QTask_s *pxObject; // ecx

  *(_DWORD *)&igi2_frame.zSound[12] = 4;
  *(_DWORD *)&igi2_frame.zSound[28] = 4;
  igi2_frame.v8 = 4;
  v1 = dword_79EE2F0 + 1;
  v2 = (unsigned int)(dword_79EE2F0 + 1) < 0xC;
  *(_DWORD *)igi2_frame.zSound = 1;
  *(_DWORD *)&igi2_frame.zSound[4] = 2;
  *(_DWORD *)&igi2_frame.zSound[8] = 3;
  *(_DWORD *)&igi2_frame.zSound[16] = 2;
  *(_DWORD *)&igi2_frame.zSound[20] = 3;
  *(_DWORD *)&igi2_frame.zSound[24] = 1;
  igi2_frame.v6 = 2;
  igi2_frame.v7 = 1;
  igi2_frame.v9 = 3;
  ++dword_79EE2F0;
  if ( !v2 )
  {
    v1 = 0;
    dword_79EE2F0 = 0;
  }
  sprintf(igi2_frame.zSound, "swim_%02d", *(_DWORD *)&igi2_frame.zSound[4 * v1]);
  v3 = Game_ptGame->aptPlayerQTaskRef[2];
  pxObject = nullptr;
  if ( v3 )
    pxObject = (struct QTask_s *)v3->pxObject;
  if ( ptQTask == pxObject )
    SoundSys_NewSoundFn(ptQTask[33].tQTaskChildren.ptTail, igi2_frame.zSound);
  else
    SoundSys_NewSoundFn(ptQTask, igi2_frame.zSound);
}

// source: j/0/human/human.c:8076  [size]
enum bool __cdecl Human_IsOnMovingPlatform(struct Human_s *ptHuman)
{
  return HIBYTE(ptHuman->ptCoughRef) && BYTE2(ptHuman->ptCoughRef);
}

// source: j/0/human/human.c:8098  [size]
int __cdecl Human_SetFireTimeStamp(int nTimeStamp)
{
  Human_nFireTimeStamp = nTimeStamp;
  return nTimeStamp;
}

// source: j/0/human/human.c:8111  [size]
int __cdecl Human_GetUpdateAfterCarryOverQTaskEvent()
{
  return Human_eUpdateInternalDataAfterCarryoverQTaskEvent;
}

// source: j/0/human/human.c:8127  [anchor-hash]
unsigned __int8 *__cdecl Human_GetHierarchy(struct Human_s *ptHuman)
{
  struct LODVirModel_s *ptLODVirModel; // eax
  struct VirModel_s *v2; // eax
  struct Model_s *ptModel; // eax
  struct Mesh3D_Mesh_t *ptMesh; // eax

  ptLODVirModel = ptHuman->tBoneDynCubeObj.tModelObj.ptLODVirModel;
  if ( ptLODVirModel
    && (v2 = ptLODVirModel->aptVirModel[0]) != nullptr
    && (ptModel = v2->ptModel) != nullptr
    && (ptMesh = ptModel->ptMesh) != nullptr )
  {
    return ptMesh->pcHierarchy;
  }
  else
  {
    return nullptr;
  }
}

// source: j/0/human/human.c:8155  [anchor-mhash]
enum bool __cdecl Human_IsLaserDesignatorActive(struct Human_s *ptHuman)
{
  struct QTask_s *ptWeaponQTask; // eax
  struct QTask_s *ptPrev; // eax
  struct QTask_s *ptTail; // eax

  ptWeaponQTask = ptHuman->ptWeaponQTask;
  return ptWeaponQTask
      && (ptPrev = ptWeaponQTask[1].ptPrev) != nullptr
      && (ptTail = ptPrev->tQTaskChildren.ptTail) != nullptr
      && ptTail[16].ptParent == (struct QTask_s *)10;
}

// source: j/0/human/human.c:8180  [anchor-callee]
enum bool __cdecl Human_IsZoomFireModeActive(struct Human_s *ptHuman)
{
  struct QTask_s *ptWeaponQTask; // eax
  struct QTask_s *ptPrev; // eax
  struct QTask_s *ptTail; // eax
  enum bool result; // eax

  ptWeaponQTask = ptHuman->ptWeaponQTask;
  result = false;
  if ( ptWeaponQTask )
  {
    if ( ptWeaponQTask[4].ptNext )
    {
      ptPrev = ptWeaponQTask[1].ptPrev;
      if ( ptPrev )
      {
        ptTail = ptPrev->tQTaskChildren.ptTail;
        if ( ptTail )
        {
          if ( ptTail[33].ptNext == (struct QTask_s *)Zoom_eQTaskType )
            return true;
        }
      }
    }
  }
  return result;
}

// source: j/0/human/human.c:8208  [anchor-mhash]
struct QTask_s *__cdecl Human_GetSector(struct Human_s *ptHuman)
{
  struct GetSectorContext_t tSectorContext; // [esp+0h] [ebp-3Ch] BYREF

  tSectorContext.ptInsideSector = nullptr;
  tSectorContext.ptInsideSectorObject = nullptr;
  tSectorContext.ptPos = &ptHuman->tBoneDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos;
  tSectorContext.isTolerance = 1;
  World_TriggerQTaskEventXyzSpecificTree(
    World_ptActiveWorld,
    QCube_eGetSectorQTaskEvent,
    &tSectorContext,
    &ptHuman->tBoneDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos,
    0xFFFFFFFF,
    WORLD_DYNCUBETREE_STATIONARY);
  return &tSectorContext.ptInsideSector->tQObj.tQTask;
}
