/* j/0/screens/missionscorescreen.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/screens/missionscorescreen.c:114  [anchor-mhash]
void __cdecl MissionScoreScreen_DeleteHandler(struct QTask_s *ptQTask)
{
  struct QTilemap_s ***p_ptPrev; // ebx
  int v2; // ebp
  struct QTilemap_s **v3; // esi
  int v4; // esi
  struct QTilemap_s **ptNext; // esi
  int v6; // esi
  int v7; // [esp+10h] [ebp-4h]

  RenderContext_DeAlloc((struct RenderContext_s *)&ptQTask[1].tQTaskChildren);
  p_ptPrev = (struct QTilemap_s ***)&ptQTask[5].ptPrev;
  v7 = 3;
  do
  {
    v2 = 6;
    do
    {
      v3 = *p_ptPrev;
      QTilemap_Delete(**p_ptPrev);
      v4 = *(_DWORD *)((unsigned int)(v3 - 1) & 0xFFFFFFFC);
      --Mem_nCurrentAllocations;
      Node_Remove((_DWORD **)v4);
      memset(*(void **)(v4 + 8), 0xCDu, *(_DWORD *)(v4 + 16));
      free((void *)v4);
      ++p_ptPrev;
      --v2;
    }
    while ( v2 );
    --v7;
  }
  while ( v7 );
  ptNext = (struct QTilemap_s **)ptQTask[5].ptNext;
  QTilemap_Delete(*ptNext);
  v6 = *(_DWORD *)((unsigned int)(ptNext - 1) & 0xFFFFFFFC);
  --Mem_nCurrentAllocations;
  Node_Remove((_DWORD **)v6);
  memset(*(void **)(v6 + 8), 0xCDu, *(_DWORD *)(v6 + 16));
  free((void *)v6);
  FontManager_DeleteFont((struct QSprite_s *)ptQTask[1].ptPrev);
  FontManager_DeleteFont((struct QSprite_s *)ptQTask[1].ptNext);
}

// source: j/0/screens/missionscorescreen.c:144  [anchor-hash]
void __cdecl MissionScoreScreen_RunHandler(struct QTask_s *ptQTask)
{
  if ( (Keyboard_tKeyboard.anCurrentKey[57] & 0x80u) != 0 && (Keyboard_tKeyboard.anPreviousKey[57] & 0x80) == 0 )
    QTask_Delete(ptQTask);
}

// source: j/0/screens/missionscorescreen.c:163  [anchor-mhash]
void __cdecl MissionScoreScreen_DrawHandler(struct QTask_s *ptQTask)
{
  struct QTilemap_s ***p_ptPrev; // esi
  int v3; // edi
  struct QTask_s *ptNext; // eax
  float *p_ptParent; // esi
  int v6; // edi
  float vX; // [esp+0h] [ebp-68h]
  float vY; // [esp+4h] [ebp-64h]
  float vYa; // [esp+4h] [ebp-64h]
  float vX2; // [esp+28h] [ebp-40h]
  int ptQTaska = *(int *)&ptQTask; // [esp+6Ch] [ebp+4h] ARGSLOT

  if ( ptQTask[3].tQTaskChildren.ptHead )
  {
    qmemcpy(&RenderContext_tActiveRenderContext, &ptQTask[1].tQTaskChildren, sizeof(RenderContext_tActiveRenderContext));
    ++RenderContext_nActiveRenderContextTimeStamp;
    ptQTask[1].tQTaskChildren.ptMiddle = nullptr;
    ptQTask[1].tQTaskChildren.ptHead = nullptr;
    List_AddTail(&ptQTask[1].tQTaskChildren.ptHead, (int)&RenderContext_tDrawList);
  }
  if ( ptQTask[3].tQTaskChildren.ptMiddle )
    QSprite_RegisterBlank4RGBAZ(
      *(float *)&ptQTask[4].tQTaskChildren.ptHead,
      *(float *)&ptQTask[4].tQTaskChildren.ptMiddle,
      *(float *)&ptQTask[4].ptParent,
      *(float *)&ptQTask[4].eQTaskType,
      64.0,
      64.0,
      128.0,
      64.0,
      64.0,
      128.0,
      64.0,
      64.0,
      75.0,
      64.0,
      64.0,
      75.0,
      0.5,
      0.5,
      0.30000001192092896,
      0.30000001192092896,
      1.0,
      0x10000000u,
      -1);
  p_ptPrev = (struct QTilemap_s ***)&ptQTask[5].ptPrev;
  ptQTaska = 3;
  do
  {
    v3 = 6;
    do
    {
      QTilemap_Register(
        **p_ptPrev,
        *((float *)*p_ptPrev + 1),
        *((float *)*p_ptPrev + 2),
        *((float *)*p_ptPrev + 5),
        *((float *)*p_ptPrev + 6),
        *((float *)*p_ptPrev + 7),
        *((float *)*p_ptPrev + 4),
        *((float *)*p_ptPrev + 3),
        (unsigned int)(*p_ptPrev)[9] | 0x40000000,
        (int)(*p_ptPrev)[8]);
      ++p_ptPrev;
      --v3;
    }
    while ( v3 );
    --ptQTaska;
  }
  while ( ptQTaska );
  ptNext = ptQTask[5].ptNext;
  QTilemap_Register(
    (struct QTilemap_s *)ptNext->ptNext,
    *(float *)&ptNext->ptPrev,
    *(float *)&ptNext->tQTaskChildren.ptHead,
    *(float *)&ptNext->tQTaskRefList.ptHead,
    *(float *)&ptNext->tQTaskRefList.ptMiddle,
    *(float *)&ptNext->tQTaskRefList.ptTail,
    *(float *)&ptNext->tQTaskChildren.ptTail,
    *(float *)&ptNext->tQTaskChildren.ptMiddle,
    *(_DWORD *)&ptNext->eQTaskType | 0x40000000,
    (int)ptNext->ptParent);
  if ( ptQTask[3].ptPrev )
  {
    p_ptParent = (float *)&ptQTask[3].ptParent;
    v6 = 2;
    do
    {
      vX2 = p_ptParent[2] + *(p_ptParent - 2);
      QSprite_RegisterLine(
        *(p_ptParent - 2),
        *p_ptParent,
        1.0,
        vX2,
        *p_ptParent,
        1.0,
        64.0,
        64.0,
        64.0,
        64.0,
        64.0,
        64.0,
        1.0,
        1.0,
        0,
        0);
      ++p_ptParent;
      --v6;
    }
    while ( v6 );
  }
  if ( ptQTask[3].tQTaskChildren.ptMiddle )
  {
    QSprite_RegisterBlank4RGBAZ(
      *(float *)&ptQTask[4].tQTaskChildren.ptHead,
      *(float *)&ptQTask[4].tQTaskChildren.ptMiddle,
      *(float *)&ptQTask[4].ptParent,
      1.0,
      64.0,
      64.0,
      128.0,
      64.0,
      64.0,
      128.0,
      64.0,
      64.0,
      128.0,
      64.0,
      64.0,
      128.0,
      0.9900000095367432,
      0.9900000095367432,
      0.9900000095367432,
      0.9900000095367432,
      1.0,
      0x10000000u,
      -1);
    QSprite_RegisterBlank4RGBAZ(
      *(float *)&ptQTask[4].tQTaskChildren.ptHead,
      *(float *)&ptQTask[4].tQTaskChildren.ptMiddle,
      1.0,
      *(float *)&ptQTask[4].eQTaskType,
      64.0,
      64.0,
      128.0,
      64.0,
      64.0,
      128.0,
      64.0,
      64.0,
      128.0,
      64.0,
      64.0,
      128.0,
      0.9900000095367432,
      0.9900000095367432,
      0.9900000095367432,
      0.9900000095367432,
      1.0,
      0x10000000u,
      -1);
    vY = *(float *)&ptQTask[4].eQTaskType + *(float *)&ptQTask[4].tQTaskChildren.ptMiddle;
    QSprite_RegisterBlank4RGBAZ(
      *(float *)&ptQTask[4].tQTaskChildren.ptHead,
      vY,
      *(float *)&ptQTask[4].ptParent,
      1.0,
      64.0,
      64.0,
      128.0,
      64.0,
      64.0,
      128.0,
      64.0,
      64.0,
      128.0,
      64.0,
      64.0,
      128.0,
      0.9900000095367432,
      0.9900000095367432,
      0.9900000095367432,
      0.9900000095367432,
      1.0,
      0x10000000u,
      -1);
    vX = *(float *)&ptQTask[4].tQTaskChildren.ptHead + *(float *)&ptQTask[4].ptParent;
    QSprite_RegisterBlank4RGBAZ(
      vX,
      *(float *)&ptQTask[4].tQTaskChildren.ptMiddle,
      1.0,
      *(float *)&ptQTask[4].eQTaskType,
      64.0,
      64.0,
      128.0,
      64.0,
      64.0,
      128.0,
      64.0,
      64.0,
      128.0,
      64.0,
      64.0,
      128.0,
      0.9900000095367432,
      0.9900000095367432,
      0.9900000095367432,
      0.9900000095367432,
      1.0,
      0x10000000u,
      -1);
    vYa = *(float *)&ptQTask[4].eQTaskType * 0.10000000149011612 + *(float *)&ptQTask[4].tQTaskChildren.ptMiddle;
    QSprite_RegisterBlank4RGBAZ(
      *(float *)&ptQTask[4].tQTaskChildren.ptHead,
      vYa,
      *(float *)&ptQTask[4].ptParent,
      1.0,
      64.0,
      64.0,
      128.0,
      64.0,
      64.0,
      128.0,
      64.0,
      64.0,
      128.0,
      64.0,
      64.0,
      128.0,
      0.9900000095367432,
      0.9900000095367432,
      0.9900000095367432,
      0.9900000095367432,
      1.0,
      0x10000000u,
      -1);
  }
}

// source: j/0/screens/missionscorescreen.c:263  [size]
struct QTask_s *__cdecl MissionScoreScreen_GetSize(
        struct QTask_s *ptQTask,
        float *pvWidth,
        float *pvHeight)
{
  struct QTask_s *result; // eax

  *pvWidth = *(float *)&ptQTask[4].tQTaskRefList.ptMiddle;
  result = (struct QTask_s *)ptQTask[4].tQTaskRefList.ptTail;
  *(_DWORD *)pvHeight = result;
  return result;
}

// source: j/0/screens/missionscorescreen.c:284  [size]
struct QTask_s *__cdecl MissionScoreScreen_GetPos(
        struct QTask_s *ptQTask,
        float *pvX,
        float *pvY)
{
  struct QTask_s *result; // eax

  *pvX = *(float *)&ptQTask[4].tQTaskChildren.ptTail;
  result = (struct QTask_s *)ptQTask[4].tQTaskRefList.ptHead;
  *(_DWORD *)pvY = result;
  return result;
}

// source: j/0/screens/missionscorescreen.c:305  [size]
unsigned __int16 __cdecl MissionScoreScreen_GetQTaskType()
{
  return MissionScoreScreen_eQTaskType;
}

// source: j/0/screens/missionscorescreen.c:318  [anchor-hash]
void __cdecl MissionScoreScreen_Open()
{
  unsigned __int16 BaseQTaskType; // ax
  unsigned __int16 v1; // si

  BaseQTaskType = QTask_GetBaseQTaskType();
  v1 = QTask_NewQTaskType("MissionScoreScreen", 276, BaseQTaskType, 0, 0);
  MissionScoreScreen_eQTaskType = v1;
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 2, MissionScoreScreen_DeleteHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 1, MissionScoreScreen_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, Screen_eDrawQTaskEvent, MissionScoreScreen_DrawHandler);
}

// source: j/0/screens/missionscorescreen.c:337  [size]
void __cdecl MissionScoreScreen_Close()
{
  QTask_DeleteQTaskType(MissionScoreScreen_eQTaskType);
}

// source: j/0/screens/missionscorescreen.c:361  [anchor-strings]
struct QTask_s *__cdecl MissionScoreScreen_New(
        struct QTask_s *ptParent,
        struct HumanMissionScoreData_s *ptScoreData,
        struct MissionScoreSettings_s *ptScoreSettings,
        unsigned int bFlags,
        int nX,
        int nY,
        int nWidth,
        int nHeight,
        char *zTitleFont,
        char *zFont)
{
  #pragma pack(push, 1)
  union
  {
    struct { char *p_ptMiddle; };
    struct { char igi2_o1[4]; char *v72; };
    struct { char igi2_o2[4]; char *v73; };
    struct { char igi2_o3[4]; char *v74; };
    struct { char igi2_o4[36]; int v75; };
    struct { char igi2_o5[48]; int v76; };
    struct { char igi2_o6[48]; int v77; };
    struct { char igi2_o7[48]; float v78; };
    struct { char igi2_o8[52]; int v79; };
    struct { char igi2_o9[52]; int v80; };
    struct { char igi2_o10[52]; float v81; };
    struct { char igi2_o11[52]; float v82; };
    struct { char igi2_o12[52]; float v83; };
    struct { char igi2_o13[52]; float v84; };
    struct { char igi2_o14[52]; float v85; };
    struct { char igi2_o15[52]; float v86; };
    struct { char igi2_o16[52]; float v87; };
    struct { char igi2_o17[52]; float v88; };
    struct { char igi2_o18[64]; int v89; };
    struct { char igi2_o19[64]; float v90; };
    struct { char igi2_o20[64]; float v91; };
    struct { char igi2_o21[68]; float v92; };
    struct { char igi2_o22[68]; float v93; };
    struct { char igi2_o23[72]; int v94; };
    struct { char igi2_o24[72]; float v95; };
    struct { char igi2_o25[76]; float v96; };
    struct { char igi2_o26[80]; int v97; };
    struct { char igi2_o27[80]; float v98; };
    struct { char igi2_o28[84]; float v99[2]; };
    struct { char igi2_o29[92]; float v100; };
    struct { char igi2_o30[96]; float v101; };
    struct { char igi2_o31[100]; float v102; };
    struct { char igi2_o32[104]; float v103; };
    struct { char igi2_o33[108]; _DWORD v104[3]; };
    struct { char igi2_o34[120]; int v105; };
    struct { char igi2_o35[124]; struct HumanMissionScoreData_s v106; };
    char igi2_extent[404];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  char v10; // bl
  struct QTask_s *v12; // esi
  double v13; // st7
  char *LocalizedStringForLanguage; // eax
  struct StaticTilemap_s *v15; // eax
  int Rank; // eax
  int v17; // ecx
  float *v18; // edi
  struct MissionScoreSettings_s *v19; // edx
  double v20; // st7
  char *v21; // eax
  int v22; // ecx
  char *v23; // eax
  unsigned int nShots; // ecx
  unsigned int v25; // eax
  char *v26; // eax
  unsigned int v27; // eax
  char *v28; // eax
  char *v29; // eax
  struct StaticTilemap_s *v30; // eax
  double v31; // st7
  struct QTask_s **v32; // ecx
  float v33; // edx
  struct QTask_s *ptNext; // ecx
  int ptPrev_high; // eax
  int ptNext_low; // edi
  struct QTask_s *ptMiddle; // ebx
  int v38; // edx
  double v39; // st7
  int v40; // eax
  int v41; // edx
  struct QTask_s *v42; // ecx
  int v43; // edi
  double v44; // st7
  float *v45; // ebx
  int v46; // edi
  int v47; // eax
  int v48; // ecx
  double v49; // st7
  __int16 *v50; // edx
  double v51; // st6
  double v52; // st5
  double v53; // st4
  __int16 *v54; // edx
  double v55; // st3
  float v56; // eax
  double v57; // st4
  struct QTask_s *ptPrev; // ecx
  double v59; // st5
  struct QTask_s *ptHead; // ecx
  double v61; // st5
  struct QTask_s *v62; // ecx
  double v63; // st5
  struct QTask_s *ptTail; // ecx
  double v65; // st5
  double v66; // st4
  float v67; // eax
  struct QReference_s *v68; // ecx
  double v69; // st5
  struct QReference_s *v70; // ecx

  v10 = bFlags;
  if ( !ptScoreSettings && !ptScoreData )
    return nullptr;
  v12 = QTask_NewFn(ptParent, MissionScoreScreen_eQTaskType, nullptr);
  v12[3].tQTaskChildren.ptHead = (struct QTask_s *)((v10 & 1) == 0);
  v12[3].tQTaskChildren.ptMiddle = (struct QTask_s *)((v10 & 2) == 0);
  v12[3].ptPrev = (struct QTask_s *)((v10 & 8) == 0);
  igi2_frame.v75 = v10 & 4;
  if ( (v10 & 4) != 0 )
  {
    *(float *)&v12[4].ptParent = (float)nWidth;
    *(float *)&v12[4].eQTaskType = (float)nHeight;
    *(float *)&v12[4].tQTaskChildren.ptHead = (float)nX;
    v13 = (double)nY;
  }
  else
  {
    *(float *)&v12[4].ptParent = (float)Display_tActiveMode.nWidth;
    *(float *)&v12[4].eQTaskType = (double)Display_tActiveMode.nHeight * 0.5 - 36.0;
    *(float *)&v12[4].tQTaskChildren.ptHead = *(float *)&v12[4].ptParent * 0.5;
    v13 = (double)Display_tActiveMode.nHeight * 0.44999998807907104;
  }
  *(float *)&v12[4].tQTaskChildren.ptMiddle = v13;
  igi2_frame.v106.eGameDifficulty = 0;
  *(float *)&igi2_frame.v106.nSpotted = (float)Display_tActiveMode.nWidth;
  igi2_frame.v106.iMissionID = 0;
  *(float *)&igi2_frame.v106.nShots = (float)Display_tActiveMode.nHeight;
  RenderContext_Alloc((struct RenderContext_s *)&v12[1].tQTaskChildren, 1);
  RenderContext_SetClippingRect((struct RenderContext_s *)&v12[1].tQTaskChildren, (struct ClippingRect_s *)&igi2_frame.v106);
  v12[1].ptPrev = (struct QTask_s *)FontManager_LoadFont(zFont);
  v12[1].ptNext = (struct QTask_s *)FontManager_LoadFont(zTitleFont);
  igi2_frame.v96 = (float)*((__int16 *)&v12[1].ptPrev->tQTaskChildren.ptHead->tQTaskChildren.ptMiddle
               + 18 * LOWORD(v12[1].ptPrev->tQTaskRefList.ptHead)
               + 1);
  if ( v12[3].ptPrev )
  {
    LocalizedStringForLanguage = Config_GetLocalizedStringForLanguage(
                                   "Mission Stats",
                                   Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eLanguage,
                                   true);
    sprintf((char *const)&igi2_frame.v106.nGameLoads, LocalizedStringForLanguage);
  }
  else
  {
    LOBYTE(igi2_frame.v106.nGameLoads) = 0;
  }
  strupr((char *)&igi2_frame.v106.nGameLoads);
  v15 = Text_New((struct QSprite_s *)v12[1].ptNext, 0.0, 0.0, (char *)&igi2_frame.v106.nGameLoads);
  v12[5].ptNext = (struct QTask_s *)v15;
  v15->bQGraphicFlags |= 0x40000u;
  v12[5].ptNext->tQTaskChildren.ptMiddle = (struct QTask_s *)1056964608;
  igi2_frame.v92 = (float)(SHIWORD(v12[5].ptNext->ptNext->ptPrev)
              * *((__int16 *)&v12[5].ptNext->ptNext->tQTaskChildren.ptHead->tQTaskChildren.ptHead->tQTaskChildren.ptMiddle
                + 18 * LOWORD(v12[5].ptNext->ptNext->tQTaskChildren.ptHead->tQTaskRefList.ptHead)
                + 1));
  Rank = MissionScoreSettings_GetRank(ptScoreSettings, ptScoreData, (int)&igi2_frame.v106);
  igi2_frame.v97 = Rank;
  if ( Rank >= 2 )
    igi2_frame.v94 = -1;
  else
    igi2_frame.v94 = Rank + 1;
  igi2_frame.v76 = 0;
  igi2_frame.v99[0] = 128.0;
  igi2_frame.v99[1] = 128.0;
  igi2_frame.v100 = 128.0;
  igi2_frame.v104[0] = 1124073472;
  igi2_frame.v104[1] = 0;
  igi2_frame.v104[2] = 0;
  do
  {
    *(&igi2_frame.v101 + igi2_frame.v76) = 0.0;
    igi2_frame.v89 = 0;
    igi2_frame.v105 = 3 * igi2_frame.v76;
    do
    {
      v17 = 0;
      v18 = igi2_frame.v99;
      switch ( igi2_frame.v89 )
      {
        case 1:
          v19 = ptScoreSettings;
          v20 = ptScoreSettings->atMissionRankRequirement[0].avRequired[0];
          goto LABEL_20;
        case 2:
          v19 = ptScoreSettings;
          v20 = ptScoreSettings->atMissionRankRequirement[0].avRequired[1];
          goto LABEL_20;
        case 3:
          v19 = ptScoreSettings;
          v20 = ptScoreSettings->atMissionRankRequirement[0].avRequired[3];
          goto LABEL_20;
        case 4:
          v19 = ptScoreSettings;
          v20 = ptScoreSettings->atMissionRankRequirement[0].avRequired[4];
LABEL_20:
          if ( v20 < 0.0 )
            v17 = 1;
          break;
        default:
          v19 = ptScoreSettings;
          break;
      }
      LOBYTE(igi2_frame.v106.nGameLoads) = 0;
      if ( !v17 )
      {
        if ( igi2_frame.v76 )
        {
          if ( igi2_frame.v76 == 1 )
          {
            switch ( igi2_frame.v89 )
            {
              case 0:
                v23 = Config_GetLocalizedStringForLanguage(
                        "Achieved",
                        Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eLanguage,
                        true);
                sprintf((char *const)&igi2_frame.v106.nGameLoads, v23);
                break;
              case 1:
                Game_GetTimeStringFromGameTicks((char *)&igi2_frame.v106.nGameLoads, 0x100u, ptScoreData->nTime);
                if ( !igi2_frame.v106.eGameDifficulty )
                  goto LABEL_39;
                v18 = igi2_frame.v99;
                break;
              case 2:
                sprintf((char *const)&igi2_frame.v106.nGameLoads, "%i", ptScoreData->nSpotted);
                if ( !igi2_frame.v106.iMissionID )
                  goto LABEL_39;
                v18 = igi2_frame.v99;
                break;
              case 3:
                sprintf((char *const)&igi2_frame.v106.nGameLoads, "%i%%", ptScoreData->nHealth != 0 ? ptScoreData->nHealth : 0);
                if ( !igi2_frame.v106.nShots )
                  goto LABEL_39;
                v18 = igi2_frame.v99;
                break;
              case 4:
                nShots = ptScoreData->nShots;
                if ( nShots )
                {
                  v25 = 100 * ptScoreData->nHits / nShots;
                  if ( v25 >= 0x64 )
                    v25 = 100;
                  sprintf((char *const)&igi2_frame.v106.nGameLoads, "%i%%", v25);
                }
                else
                {
                  v26 = Config_GetLocalizedStringForLanguage(
                          "Not Available",
                          Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eLanguage,
                          true);
                  sprintf(
                    (char *const)&igi2_frame.v106.nGameLoads,
                    (char *const)&stru_6A4CDC.tDebugConsoleLineList.ptMiddle,
                    v26);
                }
                if ( igi2_frame.v106.nKills )
                  v18 = igi2_frame.v99;
                else
LABEL_39:
                  v18 = (float *)igi2_frame.v104;
                break;
              case 5:
                if ( igi2_frame.v97 >= 0 )
                  v27 = ptScoreData->eGameDifficulty + igi2_frame.v97 + 2 * ptScoreData->eGameDifficulty + 1;
                else
                  v27 = 0;
                igi2_frame.v72 = Config_GetLocalizedStringForLanguage(
                        MissionScoreSettings_azRank[v27],
                        Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eLanguage,
                        true);
                igi2_frame.p_ptMiddle = (char *)&stru_6A4CDC.tDebugConsoleLineList.ptMiddle;
                goto LABEL_64;
              default:
                break;
            }
          }
          else if ( igi2_frame.v76 == 2 && igi2_frame.v94 >= 0 )
          {
            switch ( igi2_frame.v89 )
            {
              case 0:
                v21 = Config_GetLocalizedStringForLanguage(
                        "Target",
                        Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eLanguage,
                        true);
                sprintf((char *const)&igi2_frame.v106.nGameLoads, v21);
                break;
              case 1:
                Game_GetTimeStringFromGameTicks(
                  (char *)&igi2_frame.v106.nGameLoads,
                  0x100u,
                  30 * (__int64)v19->atMissionRankRequirement[igi2_frame.v94].avRequired[0]);
                break;
              case 2:
                sprintf(
                  (char *const)&igi2_frame.v106.nGameLoads,
                  "%i",
                  (unsigned int)(__int64)v19->atMissionRankRequirement[igi2_frame.v94].avRequired[1]);
                break;
              case 3:
                v22 = (__int64)v19->atMissionRankRequirement[igi2_frame.v94].avRequired[3];
                goto LABEL_33;
              case 4:
                v22 = (__int64)v19->atMissionRankRequirement[igi2_frame.v94].avRequired[4];
LABEL_33:
                sprintf((char *const)&igi2_frame.v106.nGameLoads, "%i%%", v22);
                break;
              default:
                break;
            }
          }
        }
        else
        {
          switch ( igi2_frame.v89 )
          {
            case 0:
              igi2_frame.v73 = Config_GetLocalizedStringForLanguage(
                      "Category",
                      Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eLanguage,
                      true);
              sprintf(
                (char *const)&igi2_frame.v106.nGameLoads,
                (char *const)&stru_6A4CDC.tDebugConsoleLineList.ptMiddle,
                igi2_frame.v73);
              break;
            case 1:
              v28 = Config_GetLocalizedStringForLanguage(
                      "Time To Complete Mission",
                      Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eLanguage,
                      true);
              goto LABEL_61;
            case 2:
              v29 = Config_GetLocalizedStringForLanguage(
                      "Times Spotted",
                      Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eLanguage,
                      true);
              goto LABEL_63;
            case 3:
              igi2_frame.v74 = Config_GetLocalizedStringForLanguage(
                      "Health",
                      Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eLanguage,
                      true);
              sprintf((char *const)&igi2_frame.v106.nGameLoads, "%s:", igi2_frame.v74);
              break;
            case 4:
              v28 = Config_GetLocalizedStringForLanguage(
                      "Accuracy",
                      Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eLanguage,
                      true);
LABEL_61:
              sprintf((char *const)&igi2_frame.v106.nGameLoads, "%s:", v28);
              break;
            case 5:
              v29 = Config_GetLocalizedStringForLanguage(
                      "Rank",
                      Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eLanguage,
                      true);
LABEL_63:
              igi2_frame.v72 = v29;
              igi2_frame.p_ptMiddle = "%s:";
LABEL_64:
              sprintf((char *const)&igi2_frame.v106.nGameLoads, igi2_frame.p_ptMiddle, igi2_frame.v72);
              break;
            default:
              break;
          }
        }
      }
      v30 = Text_New((struct QSprite_s *)v12[1].ptPrev, 0.0, 0.0, (char *)&igi2_frame.v106.nGameLoads);
      v31 = v18[1];
      v32 = &v12[5].ptPrev + 2 * igi2_frame.v105 + igi2_frame.v89;
      v33 = *v18;
      *v32 = (struct QTask_s *)v30;
      v30->vR = v33;
      *(float *)&(*v32)->tQTaskRefList.ptMiddle = v31;
      *(float *)&(*v32)->tQTaskRefList.ptTail = v18[2];
      ptNext = (*v32)->ptNext;
      ptPrev_high = SHIWORD(ptNext->ptPrev);
      ptNext_low = 0;
      igi2_frame.v79 = 0;
      if ( ptPrev_high > 0 )
      {
        ptMiddle = ptNext->tQTaskChildren.ptMiddle;
        do
        {
          if ( SLOWORD(ptMiddle->ptNext) > ptNext_low )
            ptNext_low = SLOWORD(ptMiddle->ptNext);
          ptMiddle = (struct QTask_s *)((char *)ptMiddle + 2);
          --ptPrev_high;
        }
        while ( ptPrev_high );
        igi2_frame.v79 = ptNext_low;
      }
      v38 = igi2_frame.v76;
      if ( (double)igi2_frame.v79 >= *(&igi2_frame.v101 + igi2_frame.v76) )
      {
        v40 = SHIWORD(ptNext->ptPrev);
        v41 = 0;
        igi2_frame.v80 = 0;
        if ( v40 > 0 )
        {
          v42 = ptNext->tQTaskChildren.ptMiddle;
          v43 = v40;
          do
          {
            if ( SLOWORD(v42->ptNext) > v41 )
              v41 = SLOWORD(v42->ptNext);
            v42 = (struct QTask_s *)((char *)v42 + 2);
            --v43;
          }
          while ( v43 );
          igi2_frame.v80 = v41;
        }
        v39 = (double)igi2_frame.v80;
        v38 = igi2_frame.v76;
      }
      else
      {
        v39 = *(&igi2_frame.v101 + igi2_frame.v76);
      }
      *(&igi2_frame.v101 + v38) = v39;
      ++igi2_frame.v89;
    }
    while ( igi2_frame.v89 < 6 );
    igi2_frame.v76 = v38 + 1;
    igi2_frame.v92 = igi2_frame.v92 + igi2_frame.v96;
  }
  while ( v38 + 1 < 3 );
  if ( v12[3].ptPrev )
  {
    v44 = igi2_frame.v96 + 16.0;
    igi2_frame.v90 = v44;
    igi2_frame.v92 = v44 + igi2_frame.v92 + 7.0;
  }
  else
  {
    igi2_frame.v90 = 0.0;
  }
  v45 = (float *)v12[5].ptNext;
  v46 = 0;
  v47 = *(_DWORD *)v45;
  v48 = *(__int16 *)(*(_DWORD *)v45 + 6);
  igi2_frame.v77 = 0;
  if ( igi2_frame.v75 )
  {
    v49 = *(float *)&v12[4].tQTaskChildren.ptMiddle;
    igi2_frame.v81 = *(float *)&v12[4].tQTaskChildren.ptMiddle;
    if ( v48 > 0 )
    {
      v50 = *(__int16 **)(v47 + 12);
      do
      {
        if ( *v50 > v46 )
          v46 = *v50;
        ++v50;
        --v48;
      }
      while ( v48 );
      igi2_frame.v77 = v46;
    }
    v45[1] = (float)(int)(__int64)(*(float *)&v12[4].ptParent * 0.5
                                 + *(float *)&v12[4].tQTaskChildren.ptHead
                                 - (double)igi2_frame.v77 * 0.5);
    *(float *)&v12[5].ptNext->tQTaskChildren.ptHead = (float)(__int64)*(float *)&v12[4].tQTaskChildren.ptMiddle;
    v51 = *(float *)&v12[5].ptNext->ptPrev;
    v52 = igi2_frame.v81 + igi2_frame.v90;
    igi2_frame.v99[0] = *(float *)&v12[4].tQTaskChildren.ptHead + 5.0;
    v53 = igi2_frame.v101 + *(float *)&v12[4].tQTaskChildren.ptHead + 30.0;
    igi2_frame.v100 = igi2_frame.v102 + v53 + 30.0;
    igi2_frame.v95 = igi2_frame.v102 + igi2_frame.v101 + 30.0;
    if ( igi2_frame.v103 > 0.0 )
      igi2_frame.v95 = igi2_frame.v103 + igi2_frame.v95 + 30.0;
  }
  else
  {
    v49 = *(float *)&v12[4].tQTaskChildren.ptMiddle - igi2_frame.v92 * 0.5;
    igi2_frame.v82 = v49;
    if ( v48 > 0 )
    {
      v54 = *(__int16 **)(v47 + 12);
      do
      {
        if ( *v54 > v46 )
          v46 = *v54;
        ++v54;
        --v48;
      }
      while ( v48 );
      igi2_frame.v77 = v46;
    }
    v45[1] = (float)(int)(__int64)(*(float *)&v12[4].tQTaskChildren.ptHead - (double)igi2_frame.v77 * 0.5);
    *(float *)&v12[5].ptNext->tQTaskChildren.ptHead = (float)(__int64)igi2_frame.v82;
    v51 = *(float *)&v12[5].ptNext->ptPrev;
    v52 = igi2_frame.v82 + igi2_frame.v90;
    igi2_frame.v95 = igi2_frame.v102 + igi2_frame.v101 + 30.0;
    if ( igi2_frame.v103 > 0.0 )
      igi2_frame.v95 = igi2_frame.v103 + igi2_frame.v95 + 30.0;
    igi2_frame.v99[0] = *(float *)&v12[4].tQTaskChildren.ptHead - igi2_frame.v95 * 0.5;
    v53 = igi2_frame.v101 + igi2_frame.v99[0] + 30.0;
    igi2_frame.v100 = igi2_frame.v102 + v53 + 30.0;
  }
  igi2_frame.v93 = (float)(__int64)igi2_frame.v99[0];
  *(float *)&v12[5].ptPrev->ptPrev = igi2_frame.v93;
  igi2_frame.v91 = (float)(int)(__int64)v53;
  igi2_frame.v78 = (float)(__int64)igi2_frame.v100;
  v55 = (double)(int)(__int64)v52;
  *(float *)&v12[5].ptPrev->tQTaskChildren.ptHead = v55;
  *(float *)&v12[5].tQTaskRefList.ptTail->ptPrev = igi2_frame.v91;
  *(float *)&v12[5].tQTaskRefList.ptTail->pxObject = v55;
  *(float *)&v12[6].tQTaskChildren.ptMiddle->ptPrev = igi2_frame.v78;
  v56 = igi2_frame.v99[0];
  *(float *)&v12[6].tQTaskChildren.ptMiddle->tQTaskChildren.ptHead = v55;
  v57 = igi2_frame.v96 + 2.0;
  *(float *)&v12[3].tQTaskRefList.ptMiddle = v56;
  igi2_frame.v98 = v57;
  *(float *)&v12[3].ptParent = v57 + v52;
  *(float *)&v12[4].ptNext = igi2_frame.v95;
  ptPrev = v12[5].ptPrev;
  if ( v51 >= *(float *)&ptPrev->ptPrev )
    v51 = *(float *)&ptPrev->ptPrev;
  *(float *)&v12[5].tQTaskChildren.ptHead->ptPrev = igi2_frame.v93;
  igi2_frame.v83 = v52 + 3.0;
  igi2_frame.v84 = igi2_frame.v83 + igi2_frame.v96;
  v59 = (double)(int)(__int64)igi2_frame.v84;
  *(float *)&v12[5].tQTaskChildren.ptHead->tQTaskChildren.ptHead = v59;
  *(float *)&v12[5].ptParent->ptPrev = igi2_frame.v91;
  *(float *)&v12[5].ptParent->tQTaskChildren.ptHead = v59;
  *(float *)&v12[6].tQTaskChildren.ptTail->ptPrev = igi2_frame.v78;
  *(float *)&v12[6].tQTaskChildren.ptTail->tQTaskChildren.ptHead = v59;
  ptHead = v12[5].tQTaskChildren.ptHead;
  if ( v51 >= *(float *)&ptHead->ptPrev )
    v51 = *(float *)&ptHead->ptPrev;
  *(float *)&v12[5].tQTaskChildren.ptMiddle->ptPrev = igi2_frame.v93;
  igi2_frame.v85 = igi2_frame.v84 + igi2_frame.v96;
  v61 = (double)(int)(__int64)igi2_frame.v85;
  *(float *)&v12[5].tQTaskChildren.ptMiddle->tQTaskChildren.ptHead = v61;
  *(float *)(*(_DWORD *)&v12[5].eQTaskType + 4) = igi2_frame.v91;
  *(float *)(*(_DWORD *)&v12[5].eQTaskType + 8) = v61;
  *(float *)&v12[6].tQTaskRefList.ptHead->ptPrev = igi2_frame.v78;
  *(float *)&v12[6].tQTaskRefList.ptHead->pxObject = v61;
  v62 = v12[5].tQTaskChildren.ptMiddle;
  if ( v51 >= *(float *)&v62->ptPrev )
    v51 = *(float *)&v62->ptPrev;
  *(float *)&v12[5].tQTaskChildren.ptTail->ptPrev = igi2_frame.v93;
  igi2_frame.v86 = igi2_frame.v85 + igi2_frame.v96;
  v63 = (double)(int)(__int64)igi2_frame.v86;
  *(float *)&v12[5].tQTaskChildren.ptTail->tQTaskChildren.ptHead = v63;
  *(float *)&v12[6].ptNext->ptPrev = igi2_frame.v91;
  *(float *)&v12[6].ptNext->tQTaskChildren.ptHead = v63;
  *(float *)&v12[6].tQTaskRefList.ptMiddle->ptPrev = igi2_frame.v78;
  *(float *)&v12[6].tQTaskRefList.ptMiddle->pxObject = v63;
  ptTail = v12[5].tQTaskChildren.ptTail;
  if ( v51 >= *(float *)&ptTail->ptPrev )
    v51 = *(float *)&ptTail->ptPrev;
  v65 = igi2_frame.v86 + igi2_frame.v96;
  *(float *)&v12[5].tQTaskRefList.ptHead->ptPrev = igi2_frame.v93;
  v66 = (double)(int)(__int64)v65;
  *(float *)&v12[5].tQTaskRefList.ptHead->pxObject = v66;
  *(float *)&v12[6].ptPrev->ptPrev = igi2_frame.v91;
  *(float *)&v12[6].ptPrev->tQTaskChildren.ptHead = v66;
  *(float *)&v12[6].tQTaskRefList.ptTail->ptPrev = igi2_frame.v78;
  v67 = igi2_frame.v99[0];
  *(float *)&v12[6].tQTaskRefList.ptTail->pxObject = v66;
  *(float *)&v12[3].tQTaskRefList.ptTail = v67;
  *(float *)&v12[3].eQTaskType = igi2_frame.v98 + v65;
  *(float *)&v12[4].ptPrev = igi2_frame.v95;
  v68 = v12[5].tQTaskRefList.ptHead;
  if ( v51 >= *(float *)&v68->ptPrev )
    v51 = *(float *)&v68->ptPrev;
  *(float *)&v12[5].tQTaskRefList.ptMiddle->ptPrev = igi2_frame.v93;
  igi2_frame.v87 = v65 + 3.0;
  igi2_frame.v88 = igi2_frame.v87 + igi2_frame.v96;
  v69 = (double)(int)(__int64)igi2_frame.v88;
  *(float *)&v12[5].tQTaskRefList.ptMiddle->pxObject = v69;
  *(float *)&v12[6].tQTaskChildren.ptHead->ptPrev = igi2_frame.v91;
  *(float *)&v12[6].tQTaskChildren.ptHead->tQTaskChildren.ptHead = v69;
  *(float *)&v12[6].ptParent->ptPrev = igi2_frame.v78;
  *(float *)&v12[6].ptParent->tQTaskChildren.ptHead = v69;
  v70 = v12[5].tQTaskRefList.ptMiddle;
  if ( v51 >= *(float *)&v70->ptPrev )
    v51 = *(float *)&v70->ptPrev;
  *(float *)&v12[4].tQTaskRefList.ptMiddle = igi2_frame.v95;
  *(float *)&v12[4].tQTaskRefList.ptTail = igi2_frame.v88 + igi2_frame.v96 - v49;
  *(float *)&v12[4].tQTaskChildren.ptTail = v51;
  *(float *)&v12[4].tQTaskRefList.ptHead = v49;
  return v12;
}
