/* j/0/screens/statusscreen/statusscreen.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/screens/statusscreen/statusscreen.c:219  [anchor-strings]
void __cdecl StatusScreen_SetPingCB(int n20Ping, int n50Ping, int n80Ping, int nCurrentPing)
{
  char zTemp[256]; // [esp+0h] [ebp-100h] BYREF

  if ( StatusScreen_ptClientPingText )
  {
    _snprintf(zTemp, 0xFFu, "%d [%d] [%d] [%d]", nCurrentPing, n20Ping, n50Ping, n80Ping);
    Text_SetString(StatusScreen_ptClientPingText, zTemp);
  }
}

// source: j/0/screens/statusscreen/statusscreen.c:239  [size~]
void __cdecl StatusScreen_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { float v82; };
    struct { float v83; };
    struct { float v84; };
    struct { float v85; };
    struct { float v86; };
    struct { float v87; };
    struct { float v88; };
    struct { float v89; };
    struct { float v90; };
    struct { float v91; };
    struct { float v92; };
    struct { float v93; };
    struct { float v94; };
    struct { float v95; };
    struct { char igi2_o14[4]; float v100; };
    struct { char igi2_o15[4]; float v101; };
    struct { char igi2_o16[4]; float v102; };
    struct { char igi2_o17[4]; float v103; };
    struct { char igi2_o18[4]; float v104; };
    struct { char igi2_o19[4]; float v105; };
    struct { char igi2_o20[4]; float v106; };
    struct { char igi2_o21[4]; float v107; };
    struct { char igi2_o22[4]; float v108; };
    struct { char igi2_o23[4]; float v109; };
    struct { char igi2_o24[4]; float v96; };
    struct { char igi2_o25[4]; float v97; };
    struct { char igi2_o26[4]; float v98; };
    struct { char igi2_o27[4]; float v99; };
    struct { char igi2_o28[8]; char *pzName; };
    struct { char igi2_o29[8]; char *v111; };
    struct { char igi2_o30[28]; int nY; };
    struct { char igi2_o31[32]; char zFilename[4]; };
    struct { char igi2_o32[36]; int nX; };
    struct { char igi2_o33[40]; struct QTask_s ptParent; };
    struct { char igi2_o34[320]; char zString[256]; };
    char igi2_extent[576];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  char *v2; // ecx
  int v3; // eax
  struct QTask_s *v4; // eax
  void *v5; // eax
  char **v6; // edi
  struct QSprite_s *p_ptTail; // ebx
  char **v8; // edi
  struct QSprite_s *p_ptPrev; // ebx
  struct ManagedFont_s *FontByName; // edi
  unsigned int *p_nAllocated; // edi
  struct QObjectVector_s *v12; // ebx
  struct ManagedFont_s *v13; // edx
  char *v14; // eax
  char v15; // cl
  struct QSprite_s *ptFont; // eax
  bool v17; // zf
  struct QTask_s *v18; // eax
  struct QTask_s *v19; // eax
  struct StaticTilemap_s *v20; // eax
  struct QTask_s *v21; // eax
  struct QTask_s *v22; // eax
  struct QTask_s *ptPrev; // ecx
  struct QReference_s *ptTail; // edi
  struct QSprite_s *ptQSpriteFont3; // edx
  struct QReference_s *v26; // eax
  struct QReference_s *v27; // eax
  struct QReference_s *v28; // eax
  struct QTask_s *v29; // eax
  struct StaticTilemap_s *v30; // eax
  struct StaticTilemap_s *v31; // eax
  struct StaticTilemap_s *v32; // eax
  struct StaticTilemap_s *v33; // eax
  struct QReference_s **v34; // ebx
  struct StaticTilemap_s *v35; // eax
  float v36; // eax
  int v37; // edx
  struct QTask_s **p_ptMiddle; // ebx
  struct QReference_s *v39; // eax
  struct StaticTilemap_s *v40; // eax
  struct StaticTilemap_s *v41; // eax
  float v42; // eax
  int v43; // edx
  struct QReference_s *v44; // eax
  struct QReference_s *v45; // eax
  struct QTask_s *v46; // eax
  struct QTask_s *v47; // eax
  char *LocalizedStringForLanguage; // eax
  char *v49; // eax
  struct QTask_s *v50; // eax
  struct QTask_s *v51; // eax
  struct QTask_s *v52; // eax
  struct QTask_s *v53; // eax
  char *v54; // eax
  struct QTask_s *v55; // eax
  char *v56; // eax
  struct QReference_s *v57; // eax
  char *v58; // eax
  struct QReference_s *v59; // eax
  char *v60; // eax
  struct QReference_s *v61; // eax
  _DWORD *v62; // ebx
  struct StaticTilemap_s *v63; // eax
  struct StaticTilemap_s *v64; // eax
  struct StaticTilemap_s *v65; // eax
  struct StaticTilemap_s *v66; // eax
  struct StaticTilemap_s *v67; // eax
  struct StaticTilemap_s *v68; // eax
  struct StaticTilemap_s *v69; // eax
  struct StaticTilemap_s *v70; // eax
  struct QTask_s **v71; // eax
  int v72; // ecx
  struct QTask_s *v73; // eax
  double nWidth; // st7
  double nHeight; // st7
  double v76; // st7
  double v77; // st7
  struct QTask_s *v78; // eax
  struct QTask_s *v79; // eax
  struct QTask_s *v80; // eax
  struct QReference_s *v81; // eax

  *(float *)igi2_frame.zFilename = *(float *)&Display_tActiveMode.nWidth;
  igi2_frame.nX = Display_tActiveMode.nHeight;
  StatusScreen_ptStatusScreenQTask = ptQTask;
  QTask_NewFn(ptQTask, ActionMenuScreen_eQTaskType, nullptr);
  *(float *)&igi2_frame.ptParent.tQTaskChildren.ptHead = (float)*(int *)igi2_frame.zFilename;
  igi2_frame.ptParent.ptNext = nullptr;
  igi2_frame.ptParent.ptPrev = nullptr;
  *(float *)&igi2_frame.ptParent.tQTaskChildren.ptMiddle = (float)igi2_frame.nX;
  RenderContext_Alloc((struct RenderContext_s *)&ptQTask[1], 6);
  RenderContext_SetClippingRect((struct RenderContext_s *)&ptQTask[1], (struct ClippingRect_s *)&igi2_frame.ptParent);
  if ( Resource_IsLoadedInternal("STATUSSCREEN:status.res", (struct Resource_s **)igi2_frame.zFilename) )
  {
    v3 = *(_DWORD *)igi2_frame.zFilename;
    *(_DWORD *)(*(_DWORD *)igi2_frame.zFilename + 44) = 1;
    v4 = *(struct QTask_s **)(v3 + 52);
  }
  else
  {
    Game_MPRunNetwork(v2);
    v5 = File_Load("STATUSSCREEN:status.res", (unsigned int *)igi2_frame.zFilename);
    if ( !v5 )
    {
      LDebug_Error("Failed to load resource: '%s'", "STATUSSCREEN:status.res");
      abort();
    }
    v4 = (struct QTask_s *)Resource_ParseFile(File_zLastSubstitutedPath, v5, *(unsigned int *)igi2_frame.zFilename);
  }
  ptQTask[3].ptNext = v4;
  QSprite_Load((struct QSprite_s *)&ptQTask[3].ptPrev, "STATUSSCREEN:stance_crouching.spr");
  QSprite_Load((struct QSprite_s *)&ptQTask[3].tQTaskRefList.ptTail, "STATUSSCREEN:stance_flying.spr");
  QSprite_Load((struct QSprite_s *)&ptQTask[4].tQTaskChildren.ptMiddle, "STATUSSCREEN:stance_lying.spr");
  QSprite_Load((struct QSprite_s *)&ptQTask[4].eQTaskType, "STATUSSCREEN:stance_running.spr");
  QSprite_Load((struct QSprite_s *)&ptQTask[5].tQTaskRefList, "STATUSSCREEN:stance_standing.spr");
  QSprite_Load((struct QSprite_s *)&ptQTask[6].ptPrev, "STATUSSCREEN:cross.spr");
  QSprite_Load((struct QSprite_s *)&ptQTask[6].tQTaskRefList.ptTail, "STATUSSCREEN:powerbarbackground.spr");
  QSprite_Load((struct QSprite_s *)&ptQTask[7].tQTaskChildren.ptMiddle, "STATUSSCREEN:powerbar.spr");
  QSprite_Load((struct QSprite_s *)&ptQTask[7].eQTaskType, "STATUSSCREEN:visibilitymeter.spr");
  QSprite_Load((struct QSprite_s *)&ptQTask[8].tQTaskRefList, "STATUSSCREEN:visibilitybar.spr");
  QSprite_Load((struct QSprite_s *)&ptQTask[9].ptPrev, "STATUSSCREEN:visibilityalert.spr");
  v6 = StatusScreen_azQSpriteMessageIcon;
  p_ptTail = (struct QSprite_s *)&ptQTask[12].tQTaskRefList.ptTail;
  do
    QSprite_Load(p_ptTail++, *v6++);
  while ( (int)v6 < 7050736 );
  v8 = StatusScreen_azQSpriteActivateIcon;
  p_ptPrev = (struct QSprite_s *)&ptQTask[15].ptPrev;
  do
    QSprite_Load(p_ptPrev++, *v8++);
  while ( (int)v8 < 7050820 );
  FontByName = FontManager_FindFontByName("LOCAL:common/fonts/fontmp.fnt");
  if ( !FontByName )
  {
    p_nAllocated = &FontManager_ptQObjectVector->nAllocated;
    v12 = FontManager_ptQObjectVector;
    if ( FontManager_ptQObjectVector->nAllocated == FontManager_ptQObjectVector->nSize )
      QObjectVector_Realloc(FontManager_ptQObjectVector, FontManager_ptQObjectVector->nReallocSize);
    v13 = (struct ManagedFont_s *)v12->papxElement[(*p_nAllocated)++];
    memset(v13, 0, sizeof(struct ManagedFont_s));
    v14 = "LOCAL:common/fonts/fontmp.fnt";
    do
    {
      v15 = *v14;
      v14[(char *)v13 - "LOCAL:common/fonts/fontmp.fnt" + 4] = *v14;
      ++v14;
    }
    while ( v15 );
    FontByName = v13;
  }
  ptFont = FontByName->ptFont;
  v17 = FontByName->ptFont == nullptr;
  ++FontByName->nRefCount;
  if ( v17 )
  {
    if ( RenderMode_eActiveRenderMode == -1 )
    {
      ptFont = nullptr;
    }
    else
    {
      ptFont = Font_ForceLoad(FontByName->zFilename);
      FontByName->ptFont = ptFont;
    }
  }
  ptQTask[27].tQTaskRefList.ptTail = (struct QReference_s *)ptFont;
  *(_DWORD *)igi2_frame.zFilename = ptFont->atQAnimframe[ptFont->nQAnimframes].nHeight;
  *(float *)&ptQTask[53].tQTaskRefList.ptTail = (float)*(int *)igi2_frame.zFilename;
  v18 = (struct QTask_s *)Text_New(ComputerMenu_tComputerMenuResource.ptQSpriteFont3, 320.0, 240.0, "Test");
  ptQTask[28].tQTaskChildren.ptTail = v18;
  v18->tQTaskRefList.ptHead = (struct QReference_s *)1112329421;
  ptQTask[28].tQTaskChildren.ptTail->tQTaskRefList.ptMiddle = (struct QReference_s *)1117362586;
  ptQTask[28].tQTaskChildren.ptTail->tQTaskRefList.ptTail = (struct QReference_s *)1124073472;
  v19 = (struct QTask_s *)Text_New(ComputerMenu_tComputerMenuResource.ptQSpriteFont3, 320.0, 240.0, "Test");
  ptQTask[27].ptParent = v19;
  v19->tQTaskRefList.ptHead = (struct QReference_s *)1112329421;
  ptQTask[27].ptParent->tQTaskRefList.ptMiddle = (struct QReference_s *)1117362586;
  ptQTask[27].ptParent->tQTaskRefList.ptTail = (struct QReference_s *)1124073472;
  v20 = Text_New(ComputerMenu_tComputerMenuResource.ptQSpriteFont3, 320.0, 240.0, "Test");
  *(_DWORD *)&ptQTask[27].eQTaskType = v20;
  v20->vR = 51.20000076293945;
  *(_DWORD *)(*(_DWORD *)&ptQTask[27].eQTaskType + 24) = 1117362586;
  *(_DWORD *)(*(_DWORD *)&ptQTask[27].eQTaskType + 28) = 1124073472;
  v21 = (struct QTask_s *)Text_New(
                            ComputerMenu_tComputerMenuResource.ptQSpriteFont1,
                            0.0,
                            0.0,
                            (char *)&g_zInitialValue);
  ptQTask[28].tQTaskChildren.ptHead = v21;
  v21->ptParent = (struct QTask_s *)3;
  ptQTask[28].ptPrev = (struct QTask_s *)Text_New(ComputerMenu_tComputerMenuResource.ptQSpriteFont3, 0.0, 0.0, "0m");
  v22 = (struct QTask_s *)Text_New(ComputerMenu_tComputerMenuResource.ptQSpriteFont3, 0.0, 0.0, off_6962E0);
  ptPrev = ptQTask[28].ptPrev;
  ptQTask[28].ptNext = v22;
  ptPrev->tQTaskRefList.ptHead = (struct QReference_s *)1112329421;
  ptQTask[28].ptPrev->tQTaskRefList.ptMiddle = (struct QReference_s *)1117362586;
  ptQTask[28].ptPrev->tQTaskRefList.ptTail = (struct QReference_s *)1124073472;
  ptQTask[28].ptNext->tQTaskRefList.ptHead = (struct QReference_s *)1112329421;
  ptQTask[28].ptNext->tQTaskRefList.ptMiddle = (struct QReference_s *)1117362586;
  ptQTask[28].ptNext->tQTaskRefList.ptTail = (struct QReference_s *)1124073472;
  if ( Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER )
  {
    ptTail = ptQTask[27].tQTaskRefList.ptTail;
    Flow_ptFlow->ptNetManagerQTask[36].ptNext = (struct QTask_s *)StatusScreen_SetPingCB;
    ptQTask[28].tQTaskChildren.ptMiddle = (struct QTask_s *)Text_New(
                                                              (struct QSprite_s *)ptTail,
                                                              0.0,
                                                              0.0,
                                                              (char *)&g_zInitialValue);
    ptQSpriteFont3 = ComputerMenu_tComputerMenuResource.ptQSpriteFont3;
    *(float *)&igi2_frame.nX = (double)Display_tActiveMode.nWidth * 0.009999999776482582;
    *(float *)&igi2_frame.nY = (double)Display_tActiveMode.nHeight - 115.0;
    if ( Display_tActiveMode.nHeight >= 768 )
      ptQSpriteFont3 = (struct QSprite_s *)ptQTask[27].tQTaskRefList.ptTail;
    v26 = (struct QReference_s *)Text_New(ptQSpriteFont3, *(float *)&igi2_frame.nX, *(float *)&igi2_frame.nY, (char *)&g_zInitialValue);
    ptQTask[28].tQTaskRefList.ptHead = v26;
    v26[2].pxObject = nullptr;
    igi2_frame.v96 = (double)Display_tActiveMode.nHeight - 35.0;
    igi2_frame.v82 = (double)Display_tActiveMode.nWidth * 0.800000011920929;
    v27 = (struct QReference_s *)Text_New(
                                   (struct QSprite_s *)ptQTask[27].tQTaskRefList.ptTail,
                                   igi2_frame.v82,
                                   igi2_frame.v96,
                                   (char *)&g_zInitialValue);
    ptQTask[28].tQTaskRefList.ptMiddle = v27;
    v27[1].pxObject = (void *)1112329421;
    ptQTask[28].tQTaskRefList.ptMiddle[2].ptNext = (struct QReference_s *)1117362586;
    ptQTask[28].tQTaskRefList.ptMiddle[2].ptPrev = (struct QReference_s *)1124073472;
    ptQTask[28].tQTaskRefList.ptMiddle[2].pxObject = (void *)3;
    igi2_frame.v97 = (double)Display_tActiveMode.nHeight * 0.8500000238418579 - 20.0;
    igi2_frame.v83 = (double)Display_tActiveMode.nWidth * 0.5;
    v28 = (struct QReference_s *)Text_New(
                                   (struct QSprite_s *)ptQTask[27].tQTaskRefList.ptTail,
                                   igi2_frame.v83,
                                   igi2_frame.v97,
                                   (char *)&g_zInitialValue);
    ptQTask[28].tQTaskRefList.ptTail = v28;
    v28[3].ptNext = (struct QReference_s *)((int)v28[3].ptNext | 0x80);
    ptQTask[28].tQTaskRefList.ptTail[1].pxObject = (void *)1112329421;
    ptQTask[28].tQTaskRefList.ptTail[2].ptNext = (struct QReference_s *)1117362586;
    ptQTask[28].tQTaskRefList.ptTail[2].ptPrev = (struct QReference_s *)1124073472;
    ptQTask[28].tQTaskRefList.ptTail[2].pxObject = (void *)3;
    igi2_frame.v98 = (double)Display_tActiveMode.nHeight * 0.375;
    igi2_frame.v84 = (double)Display_tActiveMode.nWidth * 0.0234375;
    v29 = (struct QTask_s *)Text_New(
                              (struct QSprite_s *)ptQTask[27].tQTaskRefList.ptTail,
                              igi2_frame.v84,
                              igi2_frame.v98,
                              (char *)&g_zInitialValue);
    ptQTask[28].ptParent = v29;
    v29->tQTaskRefList.ptHead = (struct QReference_s *)1112329421;
    ptQTask[28].ptParent->tQTaskRefList.ptMiddle = (struct QReference_s *)1117362586;
    ptQTask[28].ptParent->tQTaskRefList.ptTail = (struct QReference_s *)1124073472;
    igi2_frame.v99 = (double)Display_tActiveMode.nHeight * 0.30000001192092896;
    igi2_frame.v85 = (double)Display_tActiveMode.nWidth * 0.5;
    v30 = Text_New((struct QSprite_s *)ptQTask[27].tQTaskRefList.ptTail, igi2_frame.v85, igi2_frame.v99, "Multiplayer Mode");
    *(_DWORD *)&ptQTask[28].eQTaskType = v30;
    v30->bQGraphicFlags |= 0x80u;
    igi2_frame.v100 = (double)Display_tActiveMode.nHeight * 0.4000000059604645;
    igi2_frame.v86 = (double)Display_tActiveMode.nWidth * 0.5;
    v31 = Text_New((struct QSprite_s *)ptQTask[27].tQTaskRefList.ptTail, igi2_frame.v86, igi2_frame.v100, "Multiplayer Mode");
    ptQTask[29].ptNext = (struct QTask_s *)v31;
    v31->bQGraphicFlags |= 0x80u;
    igi2_frame.v101 = (double)Display_tActiveMode.nHeight * 0.4000000059604645;
    igi2_frame.v87 = (double)Display_tActiveMode.nWidth * 0.5;
    v32 = Text_New((struct QSprite_s *)ptQTask[27].tQTaskRefList.ptTail, igi2_frame.v87, igi2_frame.v101, "Multiplayer Mode");
    ptQTask[29].ptPrev = (struct QTask_s *)v32;
    v32->bQGraphicFlags |= 0x80u;
    igi2_frame.v102 = (double)Display_tActiveMode.nHeight * 0.4000000059604645;
    igi2_frame.v88 = (double)Display_tActiveMode.nWidth * 0.5;
    v33 = Text_New(ComputerMenu_tComputerMenuResource.ptQSpriteFont3, igi2_frame.v88, igi2_frame.v102, "Player name");
    ptQTask[29].tQTaskChildren.ptHead = (struct QTask_s *)v33;
    v33->bQGraphicFlags |= 0x80u;
    *(float *)&igi2_frame.nY = 0.0;
    v34 = &ptQTask[29].tQTaskRefList.ptTail;
    do
    {
      *(_DWORD *)igi2_frame.zFilename = igi2_frame.nY + 2;
      igi2_frame.v103 = (double)(igi2_frame.nY + 2) * (*(float *)&ptQTask[53].tQTaskRefList.ptTail + 3.0)
           + (double)Display_tActiveMode.nHeight * 0.10000000149011612;
      igi2_frame.v89 = (double)Display_tActiveMode.nWidth * 0.5 - 280.0;
      v35 = Text_New((struct QSprite_s *)ptQTask[27].tQTaskRefList.ptTail, igi2_frame.v89, igi2_frame.v103, (char *)&g_zInitialValue);
      *v34 = (struct QReference_s *)v35;
      v35->vR = 51.20000076293945;
      v36 = *(float *)&igi2_frame.nY;
      (*v34)[2].ptNext = (struct QReference_s *)1117362586;
      v37 = (int)*v34++;
      *(_DWORD *)(v37 + 28) = 1124073472;
      igi2_frame.nY = LODWORD(v36) + 1;
    }
    while ( (int)(LODWORD(v36) + 1) < 9 );
    *(float *)&igi2_frame.nY = 0.0;
    p_ptMiddle = &ptQTask[31].tQTaskChildren.ptMiddle;
    do
    {
      v39 = ptQTask[27].tQTaskRefList.ptTail;
      *(float *)&igi2_frame.nX = (float)igi2_frame.nY;
      igi2_frame.v104 = (*(float *)&ptQTask[53].tQTaskRefList.ptTail + 3.0) * *(float *)&igi2_frame.nX
           + (double)Display_tActiveMode.nHeight * 0.5699999928474426;
      igi2_frame.v90 = (double)Display_tActiveMode.nWidth * 0.5 - 295.0;
      v40 = Text_New((struct QSprite_s *)v39, igi2_frame.v90, igi2_frame.v104, (char *)&g_zInitialValue);
      *(p_ptMiddle - 7) = (struct QTask_s *)v40;
      v40->vR = 51.20000076293945;
      (*(p_ptMiddle - 7))->tQTaskRefList.ptMiddle = (struct QReference_s *)1117362586;
      (*(p_ptMiddle - 7))->tQTaskRefList.ptTail = (struct QReference_s *)1124073472;
      igi2_frame.v105 = (*(float *)&ptQTask[53].tQTaskRefList.ptTail + 3.0) * *(float *)&igi2_frame.nX
           + (double)Display_tActiveMode.nHeight * 0.5699999928474426;
      igi2_frame.v91 = (double)Display_tActiveMode.nWidth * 0.5 + 20.0;
      v41 = Text_New((struct QSprite_s *)ptQTask[27].tQTaskRefList.ptTail, igi2_frame.v91, igi2_frame.v105, (char *)&g_zInitialValue);
      *p_ptMiddle = (struct QTask_s *)v41;
      v41->vR = 51.20000076293945;
      v42 = *(float *)&igi2_frame.nY;
      (*p_ptMiddle)->tQTaskRefList.ptMiddle = (struct QReference_s *)1117362586;
      v43 = (int)*p_ptMiddle++;
      *(_DWORD *)(v43 + 28) = 1124073472;
      igi2_frame.nY = LODWORD(v42) + 1;
    }
    while ( (int)(LODWORD(v42) + 1) < 7 );
    igi2_frame.v106 = (double)Display_tActiveMode.nHeight * 0.44999998807907104;
    igi2_frame.v92 = (double)Display_tActiveMode.nWidth * 0.5;
    v44 = (struct QReference_s *)Text_New(
                                   (struct QSprite_s *)ptQTask[27].tQTaskRefList.ptTail,
                                   igi2_frame.v92,
                                   igi2_frame.v106,
                                   "Current complete");
    ptQTask[29].tQTaskRefList.ptHead = v44;
    v44[1].pxObject = (void *)1112329421;
    ptQTask[29].tQTaskRefList.ptHead[2].ptNext = (struct QReference_s *)1117362586;
    ptQTask[29].tQTaskRefList.ptHead[2].ptPrev = (struct QReference_s *)1124073472;
    ptQTask[29].tQTaskRefList.ptHead[2].pxObject = nullptr;
    igi2_frame.v107 = (double)Display_tActiveMode.nHeight * 0.44999998807907104;
    igi2_frame.v93 = (double)Display_tActiveMode.nWidth * 0.5;
    v45 = (struct QReference_s *)Text_New(
                                   (struct QSprite_s *)ptQTask[27].tQTaskRefList.ptTail,
                                   igi2_frame.v93,
                                   igi2_frame.v107,
                                   "Player [Team] [Money]");
    ptQTask[29].tQTaskRefList.ptMiddle = v45;
    v45[1].pxObject = (void *)1098907648;
    ptQTask[29].tQTaskRefList.ptMiddle[2].ptNext = (struct QReference_s *)1119879168;
    ptQTask[29].tQTaskRefList.ptMiddle[2].ptPrev = (struct QReference_s *)1098907648;
    igi2_frame.v108 = (double)Display_tActiveMode.nHeight * 0.44999998807907104;
    igi2_frame.v94 = (double)Display_tActiveMode.nWidth * 0.5;
    v46 = (struct QTask_s *)Text_New((struct QSprite_s *)ptQTask[27].tQTaskRefList.ptTail, igi2_frame.v94, igi2_frame.v108, "[  ] [  ] [  ]");
    ptQTask[29].tQTaskChildren.ptMiddle = v46;
    v46->tQTaskRefList.ptHead = (struct QReference_s *)1119879168;
    ptQTask[29].tQTaskChildren.ptMiddle->tQTaskRefList.ptMiddle = (struct QReference_s *)1119879168;
    ptQTask[29].tQTaskChildren.ptMiddle->tQTaskRefList.ptTail = (struct QReference_s *)1098907648;
    igi2_frame.v109 = (double)Display_tActiveMode.nHeight * 0.11500000208616257;
    igi2_frame.v95 = (double)Display_tActiveMode.nWidth * 0.9100000262260437;
    v47 = (struct QTask_s *)Text_New(ComputerMenu_tComputerMenuResource.ptQSpriteFont3, igi2_frame.v95, igi2_frame.v109, "1 x Zoom");
    ptQTask[29].tQTaskChildren.ptTail = v47;
    v47->tQTaskRefList.ptHead = (struct QReference_s *)1112329421;
    ptQTask[29].tQTaskChildren.ptTail->tQTaskRefList.ptMiddle = (struct QReference_s *)1117362586;
    ptQTask[29].tQTaskChildren.ptTail->tQTaskRefList.ptTail = (struct QReference_s *)1124073472;
    igi2_frame.pzName = NetManager_atTeams[0].pzName;
    LocalizedStringForLanguage = Config_GetLocalizedStringForLanguage(
                                   "mp/Team",
                                   Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eLanguage,
                                   true);
    sprintf((char *const)&igi2_frame.ptParent.tQTaskRefList.ptMiddle, "%s: %s", LocalizedStringForLanguage, igi2_frame.pzName);
    igi2_frame.v111 = NetManager_atTeams[1].pzName;
    v49 = Config_GetLocalizedStringForLanguage(
            "mp/Team",
            Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eLanguage,
            true);
    sprintf(igi2_frame.zString, "%s: %s", v49, igi2_frame.v111);
    v50 = (struct QTask_s *)Text_New(
                              (struct QSprite_s *)ptTail,
                              0.0,
                              0.0,
                              (char *)&igi2_frame.ptParent.tQTaskRefList.ptMiddle);
    ptQTask[32].ptNext = v50;
    v50->tQTaskRefList.ptHead = (struct QReference_s *)1124073472;
    ptQTask[32].ptNext->tQTaskRefList.ptMiddle = (struct QReference_s *)1124073472;
    ptQTask[32].ptNext->tQTaskRefList.ptTail = (struct QReference_s *)1098907648;
    v51 = (struct QTask_s *)Text_New((struct QSprite_s *)ptTail, 0.0, 0.0, igi2_frame.zString);
    ptQTask[32].ptPrev = v51;
    v51->tQTaskRefList.ptHead = (struct QReference_s *)1124073472;
    ptQTask[32].ptPrev->tQTaskRefList.ptMiddle = (struct QReference_s *)1124073472;
    ptQTask[32].ptPrev->tQTaskRefList.ptTail = (struct QReference_s *)1098907648;
    v52 = (struct QTask_s *)Text_New((struct QSprite_s *)ptTail, 0.0, 0.0, "Score1");
    ptQTask[32].tQTaskChildren.ptHead = v52;
    v52->tQTaskRefList.ptHead = (struct QReference_s *)1098907648;
    ptQTask[32].tQTaskChildren.ptHead->tQTaskRefList.ptMiddle = (struct QReference_s *)1119879168;
    ptQTask[32].tQTaskChildren.ptHead->tQTaskRefList.ptTail = (struct QReference_s *)1098907648;
    v53 = (struct QTask_s *)Text_New((struct QSprite_s *)ptTail, 0.0, 0.0, "Score2");
    ptQTask[32].tQTaskChildren.ptMiddle = v53;
    v53->tQTaskRefList.ptHead = (struct QReference_s *)1098907648;
    ptQTask[32].tQTaskChildren.ptMiddle->tQTaskRefList.ptMiddle = (struct QReference_s *)1119879168;
    ptQTask[32].tQTaskChildren.ptMiddle->tQTaskRefList.ptTail = (struct QReference_s *)1098907648;
    v54 = Config_GetLocalizedStringForLanguage(
            "mp/Name",
            Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eLanguage,
            true);
    v55 = (struct QTask_s *)Text_New((struct QSprite_s *)ptTail, 0.0, 0.0, v54);
    ptQTask[32].tQTaskChildren.ptTail = v55;
    v55->tQTaskRefList.ptHead = (struct QReference_s *)1124073472;
    ptQTask[32].tQTaskChildren.ptTail->tQTaskRefList.ptMiddle = (struct QReference_s *)1124073472;
    ptQTask[32].tQTaskChildren.ptTail->tQTaskRefList.ptTail = (struct QReference_s *)1098907648;
    v56 = Config_GetLocalizedStringForLanguage(
            "mp/Kills/Deaths",
            Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eLanguage,
            true);
    v57 = (struct QReference_s *)Text_New((struct QSprite_s *)ptTail, 0.0, 0.0, v56);
    ptQTask[32].tQTaskRefList.ptHead = v57;
    v57[1].pxObject = (void *)1124073472;
    ptQTask[32].tQTaskRefList.ptHead[2].ptNext = (struct QReference_s *)1124073472;
    ptQTask[32].tQTaskRefList.ptHead[2].ptPrev = (struct QReference_s *)1098907648;
    v58 = Config_GetLocalizedStringForLanguage(
            "mp/Ping/PL",
            Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eLanguage,
            true);
    v59 = (struct QReference_s *)Text_New((struct QSprite_s *)ptTail, 0.0, 0.0, v58);
    ptQTask[32].tQTaskRefList.ptMiddle = v59;
    v59[1].pxObject = (void *)1124073472;
    ptQTask[32].tQTaskRefList.ptMiddle[2].ptNext = (struct QReference_s *)1124073472;
    ptQTask[32].tQTaskRefList.ptMiddle[2].ptPrev = (struct QReference_s *)1098907648;
    v60 = Config_GetLocalizedStringForLanguage(
            "computer/OBJECTIVES",
            Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eLanguage,
            true);
    v61 = (struct QReference_s *)Text_New((struct QSprite_s *)ptTail, 0.0, 0.0, v60);
    ptQTask[32].tQTaskRefList.ptTail = v61;
    v61[1].pxObject = (void *)1124073472;
    ptQTask[32].tQTaskRefList.ptTail[2].ptNext = (struct QReference_s *)1124073472;
    ptQTask[32].tQTaskRefList.ptTail[2].ptPrev = (struct QReference_s *)1098907648;
    ptQTask[32].ptParent = (struct QTask_s *)Text_New(
                                               (struct QSprite_s *)ptTail,
                                               0.0,
                                               0.0,
                                               "----------------------------------------------------------------------");
    v62 = &ptQTask[33].tQTaskChildren.ptMiddle;
    igi2_frame.nX = 16;
    do
    {
      *(v62 - 1) = Text_New((struct QSprite_s *)ptTail, 0.0, 0.0, "ID");
      *(v62 - 4) = Text_New((struct QSprite_s *)ptTail, 0.0, 0.0, "Name");
      *v62 = Text_New((struct QSprite_s *)ptTail, 0.0, 0.0, "Objectives");
      *(v62 - 2) = Text_New((struct QSprite_s *)ptTail, 0.0, 0.0, "Kills/Deaths");
      *(v62 - 3) = Text_New((struct QSprite_s *)ptTail, 0.0, 0.0, "Ping/PL");
      v62[79] = Text_New((struct QSprite_s *)ptTail, 0.0, 0.0, "ID");
      v62[76] = Text_New((struct QSprite_s *)ptTail, 0.0, 0.0, "Name");
      v62[80] = Text_New((struct QSprite_s *)ptTail, 0.0, 0.0, "Objectives");
      v62[78] = Text_New((struct QSprite_s *)ptTail, 0.0, 0.0, "Kills/Deaths");
      v62[77] = Text_New((struct QSprite_s *)ptTail, 0.0, 0.0, "Ping/PL");
      v62 += 5;
      --igi2_frame.nX;
    }
    while ( *(float *)&igi2_frame.nX != 0.0 );
    *(_DWORD *)&ptQTask[48].eQTaskType = 0;
    v63 = Text_New(ComputerMenu_tComputerMenuResource.ptQSpriteFont1, 0.0, 0.0, off_6961B4);
    v63->bQGraphicFlags |= 0x80u;
    v63->vR = 127.0;
    v63->vG = 127.0;
    StatusScreen_ptClientTrafficInText = v63;
    v63->vB = 127.0;
    v64 = Text_New(ComputerMenu_tComputerMenuResource.ptQSpriteFont1, 0.0, 0.0, off_6961B4);
    v64->bQGraphicFlags |= 0x80u;
    v64->vR = 127.0;
    v64->vG = 127.0;
    v64->vB = 127.0;
    StatusScreen_ptClientTrafficOutText = v64;
    v65 = Text_New(ComputerMenu_tComputerMenuResource.ptQSpriteFont3, 0.0, 0.0, off_6961B0);
    v65->bQGraphicFlags |= 0x80u;
    v65->vR = 127.0;
    v65->vG = 127.0;
    v65->vB = 127.0;
    StatusScreen_ptClientFpsText = v65;
    v66 = Text_New(ComputerMenu_tComputerMenuResource.ptQSpriteFont3, 0.0, 0.0, "PL");
    v66->bQGraphicFlags |= 0x80u;
    v66->vR = 127.0;
    v66->vG = 127.0;
    unk_74C648 = v66;
    v66->vB = 127.0;
    v67 = Text_New(ComputerMenu_tComputerMenuResource.ptQSpriteFont3, 0.0, 0.0, (char *)&g_zInitialValue);
    v67->bQGraphicFlags |= 0x80u;
    v67->vR = 127.0;
    v67->vG = 127.0;
    v67->vB = 127.0;
    StatusScreen_ptClientPingText = v67;
    v68 = Text_New(ComputerMenu_tComputerMenuResource.ptQSpriteFont3, 0.0, 0.0, off_6961B4);
    v68->vR = 127.0;
    v68->vG = 127.0;
    StatusScreen_ptClientLowTrafficInText = v68;
    v68->vB = 127.0;
    v69 = Text_New(ComputerMenu_tComputerMenuResource.ptQSpriteFont3, 0.0, 0.0, off_6961B4);
    v69->vR = 127.0;
    v69->vG = 127.0;
    StatusScreen_ptClientLowTrafficOutText = v69;
    v69->vB = 127.0;
    v70 = Text_New(ComputerMenu_tComputerMenuResource.ptQSpriteFont3, 0.0, 0.0, off_6961B4);
    v70->vR = 127.0;
    v70->vG = 127.0;
    StatusScreen_ptClientPLText = v70;
    v70->vB = 127.0;
  }
  else
  {
    ptQTask[28].tQTaskRefList.ptMiddle = nullptr;
    ptQTask[28].tQTaskRefList.ptTail = nullptr;
    ptQTask[28].ptParent = nullptr;
    ptQTask[28].tQTaskRefList.ptHead = nullptr;
    *(_DWORD *)&ptQTask[28].eQTaskType = 0;
    ptQTask[29].ptNext = nullptr;
    ptQTask[29].ptPrev = nullptr;
    ptQTask[28].tQTaskChildren.ptMiddle = nullptr;
    ptQTask[29].tQTaskChildren.ptTail = nullptr;
    ptQTask[29].tQTaskChildren.ptMiddle = nullptr;
    ptQTask[29].tQTaskRefList.ptMiddle = nullptr;
    ptQTask[29].tQTaskRefList.ptHead = nullptr;
    memset(&ptQTask[29].tQTaskRefList.ptTail, 0, 0x24u);
    v71 = &ptQTask[31].tQTaskChildren.ptMiddle;
    v72 = 7;
    do
    {
      *(v71 - 7) = nullptr;
      *v71++ = nullptr;
      --v72;
    }
    while ( v72 );
  }
  ptQTask[52].tQTaskChildren.ptTail = QTask_NewFn(ptQTask, StatusMessageScreen_eQTaskType, nullptr);
  ptQTask[52].tQTaskRefList.ptHead = nullptr;
  ptQTask[52].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[49].ptNext = nullptr;
  ptQTask[49].ptPrev = (struct QTask_s *)1212678144;
  WeaponType_LoadSprites();
  if ( Game_eGameMode != GAME_GAMEMODE_MULTIPLAYER )
  {
    ptQTask[52].tQTaskRefList.ptTail = nullptr;
    ptQTask[52].ptParent = nullptr;
    goto LABEL_60;
  }
  v73 = (struct QTask_s *)ptQTask[27].tQTaskRefList.ptTail;
  nWidth = (double)Display_tActiveMode.nWidth;
  igi2_frame.nX = Display_tActiveMode.nHeight;
  *(float *)igi2_frame.zFilename = nWidth;
  igi2_frame.ptParent.tQTaskChildren.ptTail = v73;
  *(float *)&igi2_frame.ptParent.ptNext = nWidth * 0.029999999329447746;
  igi2_frame.ptParent.tQTaskChildren.ptHead = (struct QTask_s *)410;
  nHeight = (double)Display_tActiveMode.nHeight;
  igi2_frame.ptParent.tQTaskChildren.ptMiddle = (struct QTask_s *)5;
  *(float *)&igi2_frame.nY = nHeight;
  *(float *)&igi2_frame.ptParent.ptPrev = nHeight * 0.07000000029802322;
  ptQTask[52].ptParent = QTask_NewFn(ptQTask, TextScroller_eQTaskType, &igi2_frame.ptParent);
  if ( igi2_frame.nX >= 768 )
    igi2_frame.ptParent.tQTaskChildren.ptTail = (struct QTask_s *)ptQTask[27].tQTaskRefList.ptTail;
  else
    igi2_frame.ptParent.tQTaskChildren.ptTail = (struct QTask_s *)ComputerMenu_tComputerMenuResource.ptQSpriteFont3;
  if ( igi2_frame.nX > 900 )
  {
    switch ( igi2_frame.nX )
    {
      case 960:
        v76 = *(float *)&igi2_frame.nY * 0.6800000071525574;
        goto LABEL_58;
      case 1024:
        v76 = *(float *)&igi2_frame.nY * 0.699999988079071;
        goto LABEL_58;
      case 1200:
        v77 = *(float *)&igi2_frame.nY;
        goto LABEL_55;
    }
LABEL_50:
    v77 = *(float *)&igi2_frame.nY;
    if ( igi2_frame.nX < 480 )
    {
      v76 = v77 * 0.4000000059604645;
      goto LABEL_58;
    }
    if ( igi2_frame.nX <= 1200 )
    {
      v76 = v77 * 0.550000011920929;
      goto LABEL_58;
    }
LABEL_55:
    v76 = v77 * 0.7400000095367432;
    goto LABEL_58;
  }
  if ( igi2_frame.nX == 900 )
  {
    v76 = *(float *)&igi2_frame.nY * 0.5600000023841858;
    goto LABEL_58;
  }
  if ( igi2_frame.nX > 768 )
  {
    if ( igi2_frame.nX == 864 )
    {
      v76 = *(float *)&igi2_frame.nY * 0.6600000262260437;
      goto LABEL_58;
    }
    goto LABEL_50;
  }
  if ( igi2_frame.nX != 768 )
  {
    if ( igi2_frame.nX == 480 )
    {
      v76 = *(float *)&igi2_frame.nY * 0.5099999904632568;
      goto LABEL_58;
    }
    if ( igi2_frame.nX != 600 )
      goto LABEL_50;
  }
  v76 = *(float *)&igi2_frame.nY * 0.6000000238418579;
LABEL_58:
  *(float *)&igi2_frame.ptParent.ptPrev = v76;
  *(float *)&igi2_frame.ptParent.ptNext = *(float *)igi2_frame.zFilename * 0.009999999776482582;
  ptQTask[52].tQTaskRefList.ptTail = (struct QReference_s *)QTask_NewFn(ptQTask, TextScroller_eQTaskType, &igi2_frame.ptParent);
LABEL_60:
  *(_DWORD *)&ptQTask[52].eQTaskType = 0;
  ptQTask[53].ptNext = (struct QTask_s *)1065353216;
  ptQTask[53].ptPrev = nullptr;
  LOWORD(igi2_frame.nY) = 87;
  v78 = (struct QTask_s *)Text_New(ComputerMenu_tComputerMenuResource.ptQSpriteFont3, 0.0, 0.0, (char *)&igi2_frame.nY);
  ptQTask[53].tQTaskChildren.ptHead = v78;
  v78->tQTaskRefList.ptHead = (struct QReference_s *)1112329421;
  ptQTask[53].tQTaskChildren.ptHead->tQTaskRefList.ptMiddle = (struct QReference_s *)1117362586;
  ptQTask[53].tQTaskChildren.ptHead->tQTaskRefList.ptTail = (struct QReference_s *)1124073472;
  LOBYTE(igi2_frame.nY) = 78;
  v79 = (struct QTask_s *)Text_New(ComputerMenu_tComputerMenuResource.ptQSpriteFont3, 0.0, 0.0, (char *)&igi2_frame.nY);
  ptQTask[53].tQTaskChildren.ptMiddle = v79;
  v79->tQTaskRefList.ptHead = (struct QReference_s *)1112329421;
  ptQTask[53].tQTaskChildren.ptMiddle->tQTaskRefList.ptMiddle = (struct QReference_s *)1117362586;
  ptQTask[53].tQTaskChildren.ptMiddle->tQTaskRefList.ptTail = (struct QReference_s *)1124073472;
  LOBYTE(igi2_frame.nY) = 69;
  v80 = (struct QTask_s *)Text_New(ComputerMenu_tComputerMenuResource.ptQSpriteFont3, 0.0, 0.0, (char *)&igi2_frame.nY);
  ptQTask[53].tQTaskChildren.ptTail = v80;
  v80->tQTaskRefList.ptHead = (struct QReference_s *)1112329421;
  ptQTask[53].tQTaskChildren.ptTail->tQTaskRefList.ptMiddle = (struct QReference_s *)1117362586;
  ptQTask[53].tQTaskChildren.ptTail->tQTaskRefList.ptTail = (struct QReference_s *)1124073472;
  LOBYTE(igi2_frame.nY) = 83;
  v81 = (struct QReference_s *)Text_New(ComputerMenu_tComputerMenuResource.ptQSpriteFont3, 0.0, 0.0, (char *)&igi2_frame.nY);
  ptQTask[53].tQTaskRefList.ptHead = v81;
  v81[1].pxObject = (void *)1112329421;
  ptQTask[53].tQTaskRefList.ptHead[2].ptNext = (struct QReference_s *)1117362586;
  ptQTask[53].tQTaskRefList.ptHead[2].ptPrev = (struct QReference_s *)1124073472;
  ptQTask[53].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[53].ptParent = nullptr;
}

// source: j/0/screens/statusscreen/statusscreen.c:820  [size]
void __cdecl StatusScreen_ShowCritical(char *zText, enum TextScrollerColour_e eColour)
{
  struct TextScroller_s *ptParent; // esi

  if ( !StatusScreen_ptStatusScreenQTask
    || (ptParent = (struct TextScroller_s *)StatusScreen_ptStatusScreenQTask[52].ptParent) == nullptr )
  {
    ptParent = nullptr;
  }
  SoundSys_PlaySimpleSoundFn("statusmessage", 0, nullptr);
  if ( ptParent )
    TextScroller_Add(ptParent, zText, eColour);
  NetManager_LogMessage(zText);
  NetManager_LogMessage("\r\n");
}

// source: j/0/screens/statusscreen/statusscreen.c:838  [anchor-callee]
void __cdecl StatusScreen_ShowMessage(char *zText, enum TextScrollerColour_e eColour)
{
  struct QReference_s *ptTail; // eax

  if ( StatusScreen_ptStatusScreenQTask )
  {
    ptTail = StatusScreen_ptStatusScreenQTask[52].tQTaskRefList.ptTail;
    if ( ptTail )
      TextScroller_Add((struct TextScroller_s *)ptTail, zText, eColour);
  }
  NetManager_LogMessage(zText);
  NetManager_LogMessage("\r\n");
}

// source: j/0/screens/statusscreen/statusscreen.c:856  [anchor-callee]
void __cdecl StatusScreen_ShowMonitorMessage(char *zText, enum TextScrollerColour_e eColour)
{
  struct TextScroller_s *ptParent; // esi

  if ( !StatusScreen_ptStatusScreenQTask
    || (ptParent = (struct TextScroller_s *)StatusScreen_ptStatusScreenQTask[52].ptParent) == nullptr )
  {
    ptParent = nullptr;
  }
  SoundSys_PlaySimpleSoundFn("statusmessage", 0, nullptr);
  if ( ptParent )
    TextScroller_Add(ptParent, zText, eColour);
  File_printf(NetManager_ptMultiplayerMonitorFile, zText);
  File_atDevice[NetManager_ptMultiplayerMonitorFile->eDeviceID].pfSync(
    NetManager_ptMultiplayerMonitorFile->eDeviceID,
    NetManager_ptMultiplayerMonitorFile,
    FILE_SYNC_FLUSH);
}

// source: j/0/screens/statusscreen/statusscreen.c:873  [anchor-mhash]
void __cdecl StatusScreen_RunHandler(struct QTask_s *ptQTask)
{
  double v1; // st7
  struct QTask_s *ptNext; // eax
  struct QTask_s *v3; // edx
  double v4; // st7
  double v5; // st7
  struct QTask_s *ptHead; // ecx
  int v7; // edx
  struct QTask_s *v8; // eax
  void (__cdecl *pfHandler)(struct QTask_s *); // eax
  int v10; // edx

  v1 = *(float *)&ptQTask[52].tQTaskRefList.ptHead + 0.06666667014360428;
  *(float *)&ptQTask[52].tQTaskRefList.ptHead = v1;
  if ( v1 > 2.0 )
    ptQTask[52].tQTaskRefList.ptHead = nullptr;
  ptNext = ptQTask[49].ptNext;
  if ( ptNext )
    ptQTask[49].ptNext = (struct QTask_s *)((char *)ptNext - 1);
  v3 = HumanPlayer_ptQTask;
  if ( HumanPlayer_ptQTask )
  {
    if ( *(float *)&HumanPlayer_ptQTask[20].tQTaskRefList.ptHead != 0.0
      && *(float *)&HumanPlayer_ptQTask[14].tQTaskChildren.ptHead == 0.0 )
    {
      v4 = *(float *)&ptQTask[49].ptPrev - 460800.0;
      if ( v4 < 204800.0 )
        v4 = 204800.0;
      *(float *)&ptQTask[49].ptPrev = v4;
    }
    if ( *(float *)&v3[20].tQTaskRefList.ptMiddle != 0.0 && *(float *)&v3[14].tQTaskChildren.ptMiddle == 0.0 )
    {
      v5 = *(float *)&ptQTask[49].ptPrev + 460800.0;
      if ( v5 > 2048000.0 )
        v5 = 2048000.0;
      *(float *)&ptQTask[49].ptPrev = v5;
    }
  }
  ptHead = ptQTask->tQTaskChildren.ptHead;
  if ( ptHead->ptNext && ptHead )
  {
    v7 = QTask_nProtectedQTaskStackOffset;
    do
    {
      if ( ptHead->ptNext )
        v8 = ptHead->ptNext->ptNext != nullptr ? ptHead->ptNext : nullptr;
      else
        v8 = nullptr;
      QTask_atProtectedQTaskStack[v7].ptQTask = v8;
      pfHandler = (void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[1][ptHead->eQTaskType].pfHandler;
      v10 = v7 + 1;
      QTask_nProtectedQTaskStackOffset = v10;
      if ( pfHandler )
      {
        pfHandler(ptHead);
        v10 = QTask_nProtectedQTaskStackOffset;
      }
      ptHead = (struct QTask_s *)dword_849C7DC[v10];
      v7 = v10 - 1;
      QTask_nProtectedQTaskStackOffset = v7;
    }
    while ( ptHead );
  }
}

// source: j/0/screens/statusscreen/statusscreen.c:923  [size~]
void __cdecl StatusScreen_DeleteHandler(struct QTask_s *ptQTask)
{
  struct QReference_s *ptHead; // eax
  struct QReference_s *ptMiddle; // eax
  struct QTask_s *v4; // eax
  struct QReference_s *ptTail; // eax
  struct QTask_s *ptParent; // eax
  struct StaticTilemap_s *v7; // eax
  struct QTask_s *ptNext; // eax
  struct QTask_s *ptPrev; // eax
  struct QTask_s *v10; // eax
  struct QTask_s *v11; // eax
  struct QTask_s *v12; // eax
  struct QReference_s *v13; // eax
  struct QReference_s *v14; // eax
  struct QTilemap_s ***p_ptTail; // esi
  struct QTilemap_s **v16; // edi
  int v17; // ebx
  struct QReference_s **p_ptMiddle; // esi
  struct QTilemap_s **v19; // edi
  int v20; // ebx
  struct QTilemap_s **v21; // edi
  int v22; // ebx
  struct QTilemap_s **v23; // esi
  int v24; // esi
  struct QTilemap_s **v25; // esi
  int v26; // esi
  struct QTilemap_s **v27; // esi
  int v28; // esi
  struct QTilemap_s **v29; // esi
  int v30; // esi
  struct QTilemap_s **v31; // esi
  int v32; // esi
  struct QTilemap_s **v33; // esi
  int v34; // esi
  struct QTilemap_s **v35; // esi
  int v36; // esi
  struct QTilemap_s **v37; // esi
  int v38; // esi
  struct QTilemap_s **v39; // esi
  int v40; // esi
  struct QTask_s **p_ptPrev; // esi
  struct QTilemap_s **v42; // edi
  int v43; // ebx
  struct QTilemap_s **v44; // edi
  int v45; // ebx
  struct QTilemap_s **v46; // edi
  int v47; // ebx
  struct QTilemap_s **v48; // edi
  int v49; // ebx
  struct QTilemap_s **v50; // edi
  int v51; // ebx
  struct QTilemap_s **v52; // edi
  int v53; // ebx
  struct QTilemap_s **v54; // edi
  int v55; // ebx
  struct QTilemap_s **v56; // edi
  int v57; // ebx
  struct QTilemap_s **v58; // edi
  int v59; // ebx
  struct QTilemap_s **v60; // edi
  int v61; // ebx
  struct StaticTilemap_s *v62; // esi
  int v63; // esi
  struct StaticTilemap_s *v64; // esi
  int v65; // esi
  struct StaticTilemap_s *v66; // esi
  int v67; // esi
  struct StaticTilemap_s *v68; // esi
  int v69; // esi
  struct StaticTilemap_s *v70; // esi
  int v71; // esi
  struct StaticTilemap_s *v72; // esi
  int v73; // esi
  struct StaticTilemap_s *v74; // esi
  int v75; // esi
  _DWORD *v76; // esi
  int v77; // esi
  struct QTilemap_s **v78; // edi
  int v79; // ebx
  struct QTilemap_s **v80; // edi
  int v81; // ebx
  struct QTilemap_s **v82; // edi
  int v83; // ebx
  struct QTilemap_s **v84; // edi
  int v85; // ebx
  struct QSprite_s *v86; // ebx
  int v87; // edi
  struct QSprite_s *v88; // ebx
  int v89; // edi
  struct QTask_s *v90; // edx
  struct Resource_s *v91; // ecx
  struct Resource_s *v92; // eax
  unsigned int nType; // eax
  int ptQTaska = *(int *)&ptQTask; // [esp+14h] [ebp+4h] ARGSLOT
  int ptQTaskb = *(int *)&ptQTask; // [esp+14h] [ebp+4h] ARGSLOT
  int ptQTaskc = *(int *)&ptQTask; // [esp+14h] [ebp+4h] ARGSLOT

  WeaponType_UnLoadSprites();
  Flow_ptFlow->ptNetManagerQTask[36].ptNext = nullptr;
  Text_Delete((struct StaticTilemap_s *)ptQTask[28].tQTaskChildren.ptHead);
  Text_Delete((struct StaticTilemap_s *)ptQTask[28].tQTaskChildren.ptTail);
  Text_Delete((struct StaticTilemap_s *)ptQTask[27].ptParent);
  Text_Delete(*(struct StaticTilemap_s **)&ptQTask[27].eQTaskType);
  Text_Delete((struct StaticTilemap_s *)ptQTask[28].ptPrev);
  Text_Delete((struct StaticTilemap_s *)ptQTask[28].ptNext);
  if ( Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER )
  {
    ptHead = ptQTask[28].tQTaskRefList.ptHead;
    if ( ptHead )
    {
      Text_Delete((struct StaticTilemap_s *)ptHead);
      ptQTask[28].tQTaskRefList.ptHead = nullptr;
    }
    ptMiddle = ptQTask[28].tQTaskRefList.ptMiddle;
    if ( ptMiddle )
    {
      Text_Delete((struct StaticTilemap_s *)ptMiddle);
      ptQTask[28].tQTaskRefList.ptMiddle = nullptr;
    }
    v4 = ptQTask[28].tQTaskChildren.ptMiddle;
    if ( v4 )
    {
      Text_Delete((struct StaticTilemap_s *)v4);
      ptQTask[28].tQTaskChildren.ptMiddle = nullptr;
    }
    ptTail = ptQTask[28].tQTaskRefList.ptTail;
    if ( ptTail )
    {
      Text_Delete((struct StaticTilemap_s *)ptTail);
      ptQTask[28].tQTaskRefList.ptTail = nullptr;
    }
    ptParent = ptQTask[28].ptParent;
    if ( ptParent )
    {
      Text_Delete((struct StaticTilemap_s *)ptParent);
      ptQTask[28].ptParent = nullptr;
    }
    v7 = *(struct StaticTilemap_s **)&ptQTask[28].eQTaskType;
    if ( v7 )
    {
      Text_Delete(v7);
      *(_DWORD *)&ptQTask[28].eQTaskType = 0;
    }
    ptNext = ptQTask[29].ptNext;
    if ( ptNext )
    {
      Text_Delete((struct StaticTilemap_s *)ptNext);
      ptQTask[29].ptNext = nullptr;
    }
    ptPrev = ptQTask[29].ptPrev;
    if ( ptPrev )
    {
      Text_Delete((struct StaticTilemap_s *)ptPrev);
      ptQTask[29].ptPrev = nullptr;
    }
    v10 = ptQTask[29].tQTaskChildren.ptHead;
    if ( v10 )
      Text_Delete((struct StaticTilemap_s *)v10);
    v11 = ptQTask[29].tQTaskChildren.ptMiddle;
    if ( v11 )
    {
      Text_Delete((struct StaticTilemap_s *)v11);
      ptQTask[29].tQTaskChildren.ptMiddle = nullptr;
    }
    v12 = ptQTask[29].tQTaskChildren.ptTail;
    if ( v12 )
    {
      Text_Delete((struct StaticTilemap_s *)v12);
      ptQTask[29].tQTaskChildren.ptTail = nullptr;
    }
    v13 = ptQTask[29].tQTaskRefList.ptMiddle;
    if ( v13 )
    {
      Text_Delete((struct StaticTilemap_s *)v13);
      ptQTask[29].tQTaskRefList.ptMiddle = nullptr;
    }
    v14 = ptQTask[29].tQTaskRefList.ptHead;
    if ( v14 )
    {
      Text_Delete((struct StaticTilemap_s *)v14);
      ptQTask[29].tQTaskRefList.ptHead = nullptr;
    }
    p_ptTail = (struct QTilemap_s ***)&ptQTask[29].tQTaskRefList.ptTail;
    ptQTaska = 9;
    do
    {
      v16 = *p_ptTail;
      if ( *p_ptTail )
      {
        QTilemap_Delete(*v16);
        v17 = *(_DWORD *)((unsigned int)(v16 - 1) & 0xFFFFFFFC);
        --Mem_nCurrentAllocations;
        Node_Remove((_DWORD **)v17);
        memset(*(void **)(v17 + 8), 0xCDu, *(_DWORD *)(v17 + 16));
        free((void *)v17);
        *p_ptTail = nullptr;
      }
      ++p_ptTail;
      --ptQTaska;
    }
    while ( ptQTaska );
    p_ptMiddle = &ptQTask[30].tQTaskRefList.ptMiddle;
    ptQTaskb = 7;
    do
    {
      v19 = (struct QTilemap_s **)*p_ptMiddle;
      if ( *p_ptMiddle )
      {
        QTilemap_Delete(*v19);
        v20 = *(_DWORD *)((unsigned int)(v19 - 1) & 0xFFFFFFFC);
        --Mem_nCurrentAllocations;
        Node_Remove((_DWORD **)v20);
        memset(*(void **)(v20 + 8), 0xCDu, *(_DWORD *)(v20 + 16));
        free((void *)v20);
        v21 = (struct QTilemap_s **)p_ptMiddle[7];
        QTilemap_Delete(*v21);
        v22 = *(_DWORD *)((unsigned int)(v21 - 1) & 0xFFFFFFFC);
        --Mem_nCurrentAllocations;
        Node_Remove((_DWORD **)v22);
        memset(*(void **)(v22 + 8), 0xCDu, *(_DWORD *)(v22 + 16));
        free((void *)v22);
        *p_ptMiddle = nullptr;
        p_ptMiddle[7] = nullptr;
      }
      ++p_ptMiddle;
      --ptQTaskb;
    }
    while ( ptQTaskb );
    v23 = (struct QTilemap_s **)ptQTask[32].ptNext;
    QTilemap_Delete(*v23);
    v24 = *(_DWORD *)((unsigned int)(v23 - 1) & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v24);
    memset(*(void **)(v24 + 8), 0xCDu, *(_DWORD *)(v24 + 16));
    free((void *)v24);
    v25 = (struct QTilemap_s **)ptQTask[32].ptPrev;
    QTilemap_Delete(*v25);
    v26 = *(_DWORD *)((unsigned int)(v25 - 1) & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v26);
    memset(*(void **)(v26 + 8), 0xCDu, *(_DWORD *)(v26 + 16));
    free((void *)v26);
    v27 = (struct QTilemap_s **)ptQTask[32].tQTaskChildren.ptHead;
    QTilemap_Delete(*v27);
    v28 = *(_DWORD *)((unsigned int)(v27 - 1) & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v28);
    memset(*(void **)(v28 + 8), 0xCDu, *(_DWORD *)(v28 + 16));
    free((void *)v28);
    v29 = (struct QTilemap_s **)ptQTask[32].tQTaskChildren.ptMiddle;
    QTilemap_Delete(*v29);
    v30 = *(_DWORD *)((unsigned int)(v29 - 1) & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v30);
    memset(*(void **)(v30 + 8), 0xCDu, *(_DWORD *)(v30 + 16));
    free((void *)v30);
    v31 = (struct QTilemap_s **)ptQTask[32].tQTaskChildren.ptTail;
    QTilemap_Delete(*v31);
    v32 = *(_DWORD *)((unsigned int)(v31 - 1) & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v32);
    memset(*(void **)(v32 + 8), 0xCDu, *(_DWORD *)(v32 + 16));
    free((void *)v32);
    v33 = (struct QTilemap_s **)ptQTask[32].tQTaskRefList.ptHead;
    QTilemap_Delete(*v33);
    v34 = *(_DWORD *)((unsigned int)(v33 - 1) & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v34);
    memset(*(void **)(v34 + 8), 0xCDu, *(_DWORD *)(v34 + 16));
    free((void *)v34);
    v35 = (struct QTilemap_s **)ptQTask[32].tQTaskRefList.ptMiddle;
    QTilemap_Delete(*v35);
    v36 = *(_DWORD *)((unsigned int)(v35 - 1) & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v36);
    memset(*(void **)(v36 + 8), 0xCDu, *(_DWORD *)(v36 + 16));
    free((void *)v36);
    v37 = (struct QTilemap_s **)ptQTask[32].tQTaskRefList.ptTail;
    QTilemap_Delete(*v37);
    --Mem_nCurrentAllocations;
    v38 = *(_DWORD *)((unsigned int)(v37 - 1) & 0xFFFFFFFC);
    Node_Remove((_DWORD **)v38);
    memset(*(void **)(v38 + 8), 0xCDu, *(_DWORD *)(v38 + 16));
    free((void *)v38);
    v39 = (struct QTilemap_s **)ptQTask[32].ptParent;
    QTilemap_Delete(*v39);
    v40 = *(_DWORD *)((unsigned int)(v39 - 1) & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v40);
    memset(*(void **)(v40 + 8), 0xCDu, *(_DWORD *)(v40 + 16));
    free((void *)v40);
    p_ptPrev = &ptQTask[33].ptPrev;
    ptQTaskc = 16;
    do
    {
      v42 = (struct QTilemap_s **)p_ptPrev[1];
      QTilemap_Delete(*v42);
      v43 = *(_DWORD *)((unsigned int)(v42 - 1) & 0xFFFFFFFC);
      --Mem_nCurrentAllocations;
      Node_Remove((_DWORD **)v43);
      memset(*(void **)(v43 + 8), 0xCDu, *(_DWORD *)(v43 + 16));
      free((void *)v43);
      v44 = (struct QTilemap_s **)*(p_ptPrev - 2);
      QTilemap_Delete(*v44);
      v45 = *(_DWORD *)((unsigned int)(v44 - 1) & 0xFFFFFFFC);
      --Mem_nCurrentAllocations;
      Node_Remove((_DWORD **)v45);
      memset(*(void **)(v45 + 8), 0xCDu, *(_DWORD *)(v45 + 16));
      free((void *)v45);
      v46 = (struct QTilemap_s **)*p_ptPrev;
      QTilemap_Delete((struct QTilemap_s *)(*p_ptPrev)->ptNext);
      v47 = *(_DWORD *)((unsigned int)(v46 - 1) & 0xFFFFFFFC);
      --Mem_nCurrentAllocations;
      Node_Remove((_DWORD **)v47);
      memset(*(void **)(v47 + 8), 0xCDu, *(_DWORD *)(v47 + 16));
      free((void *)v47);
      v48 = (struct QTilemap_s **)p_ptPrev[2];
      QTilemap_Delete(*v48);
      v49 = *(_DWORD *)((unsigned int)(v48 - 1) & 0xFFFFFFFC);
      --Mem_nCurrentAllocations;
      Node_Remove((_DWORD **)v49);
      memset(*(void **)(v49 + 8), 0xCDu, *(_DWORD *)(v49 + 16));
      free((void *)v49);
      v50 = (struct QTilemap_s **)*(p_ptPrev - 1);
      QTilemap_Delete(*v50);
      v51 = *(_DWORD *)((unsigned int)(v50 - 1) & 0xFFFFFFFC);
      --Mem_nCurrentAllocations;
      Node_Remove((_DWORD **)v51);
      memset(*(void **)(v51 + 8), 0xCDu, *(_DWORD *)(v51 + 16));
      free((void *)v51);
      v52 = (struct QTilemap_s **)p_ptPrev[81];
      QTilemap_Delete(*v52);
      v53 = *(_DWORD *)((unsigned int)(v52 - 1) & 0xFFFFFFFC);
      --Mem_nCurrentAllocations;
      Node_Remove((_DWORD **)v53);
      memset(*(void **)(v53 + 8), 0xCDu, *(_DWORD *)(v53 + 16));
      free((void *)v53);
      v54 = (struct QTilemap_s **)p_ptPrev[78];
      QTilemap_Delete(*v54);
      v55 = *(_DWORD *)((unsigned int)(v54 - 1) & 0xFFFFFFFC);
      --Mem_nCurrentAllocations;
      Node_Remove((_DWORD **)v55);
      memset(*(void **)(v55 + 8), 0xCDu, *(_DWORD *)(v55 + 16));
      free((void *)v55);
      v56 = (struct QTilemap_s **)p_ptPrev[80];
      QTilemap_Delete(*v56);
      --Mem_nCurrentAllocations;
      v57 = *(_DWORD *)((unsigned int)(v56 - 1) & 0xFFFFFFFC);
      Node_Remove((_DWORD **)v57);
      memset(*(void **)(v57 + 8), 0xCDu, *(_DWORD *)(v57 + 16));
      free((void *)v57);
      v58 = (struct QTilemap_s **)p_ptPrev[82];
      QTilemap_Delete(*v58);
      v59 = *(_DWORD *)((unsigned int)(v58 - 1) & 0xFFFFFFFC);
      --Mem_nCurrentAllocations;
      Node_Remove((_DWORD **)v59);
      memset(*(void **)(v59 + 8), 0xCDu, *(_DWORD *)(v59 + 16));
      free((void *)v59);
      v60 = (struct QTilemap_s **)p_ptPrev[79];
      QTilemap_Delete(*v60);
      v61 = *(_DWORD *)((unsigned int)(v60 - 1) & 0xFFFFFFFC);
      --Mem_nCurrentAllocations;
      Node_Remove((_DWORD **)v61);
      memset(*(void **)(v61 + 8), 0xCDu, *(_DWORD *)(v61 + 16));
      free((void *)v61);
      p_ptPrev += 5;
      --ptQTaskc;
    }
    while ( ptQTaskc );
    v62 = StatusScreen_ptClientFpsText;
    QTilemap_Delete(StatusScreen_ptClientFpsText->ptQTilemap);
    v63 = *(_DWORD *)((unsigned int)&v62[-1].bQGraphicFlags & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v63);
    memset(*(void **)(v63 + 8), 0xCDu, *(_DWORD *)(v63 + 16));
    free((void *)v63);
    v64 = StatusScreen_ptClientTrafficInText;
    QTilemap_Delete(StatusScreen_ptClientTrafficInText->ptQTilemap);
    v65 = *(_DWORD *)((unsigned int)&v64[-1].bQGraphicFlags & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v65);
    memset(*(void **)(v65 + 8), 0xCDu, *(_DWORD *)(v65 + 16));
    free((void *)v65);
    v66 = StatusScreen_ptClientTrafficOutText;
    QTilemap_Delete(StatusScreen_ptClientTrafficOutText->ptQTilemap);
    v67 = *(_DWORD *)((unsigned int)&v66[-1].bQGraphicFlags & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v67);
    memset(*(void **)(v67 + 8), 0xCDu, *(_DWORD *)(v67 + 16));
    free((void *)v67);
    v68 = StatusScreen_ptClientLowTrafficInText;
    QTilemap_Delete(StatusScreen_ptClientLowTrafficInText->ptQTilemap);
    v69 = *(_DWORD *)((unsigned int)&v68[-1].bQGraphicFlags & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v69);
    memset(*(void **)(v69 + 8), 0xCDu, *(_DWORD *)(v69 + 16));
    free((void *)v69);
    v70 = StatusScreen_ptClientLowTrafficOutText;
    QTilemap_Delete(StatusScreen_ptClientLowTrafficOutText->ptQTilemap);
    v71 = *(_DWORD *)((unsigned int)&v70[-1].bQGraphicFlags & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v71);
    memset(*(void **)(v71 + 8), 0xCDu, *(_DWORD *)(v71 + 16));
    free((void *)v71);
    v72 = StatusScreen_ptClientPLText;
    QTilemap_Delete(StatusScreen_ptClientPLText->ptQTilemap);
    v73 = *(_DWORD *)((unsigned int)&v72[-1].bQGraphicFlags & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v73);
    memset(*(void **)(v73 + 8), 0xCDu, *(_DWORD *)(v73 + 16));
    free((void *)v73);
    v74 = StatusScreen_ptClientPingText;
    QTilemap_Delete(StatusScreen_ptClientPingText->ptQTilemap);
    v75 = *(_DWORD *)((unsigned int)&v74[-1].bQGraphicFlags & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v75);
    memset(*(void **)(v75 + 8), 0xCDu, *(_DWORD *)(v75 + 16));
    free((void *)v75);
    v76 = dword_74C648;
    QTilemap_Delete((struct QTilemap_s *)*dword_74C648);
    v77 = *(_DWORD *)((unsigned int)(v76 - 1) & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v77);
    memset(*(void **)(v77 + 8), 0xCDu, *(_DWORD *)(v77 + 16));
    free((void *)v77);
    StatusScreen_ptClientPingText = nullptr;
  }
  v78 = (struct QTilemap_s **)ptQTask[53].tQTaskChildren.ptHead;
  QTilemap_Delete(*v78);
  v79 = *(_DWORD *)((unsigned int)(v78 - 1) & 0xFFFFFFFC);
  --Mem_nCurrentAllocations;
  Node_Remove((_DWORD **)v79);
  memset(*(void **)(v79 + 8), 0xCDu, *(_DWORD *)(v79 + 16));
  free((void *)v79);
  v80 = (struct QTilemap_s **)ptQTask[53].tQTaskChildren.ptMiddle;
  QTilemap_Delete(*v80);
  v81 = *(_DWORD *)((unsigned int)(v80 - 1) & 0xFFFFFFFC);
  --Mem_nCurrentAllocations;
  Node_Remove((_DWORD **)v81);
  memset(*(void **)(v81 + 8), 0xCDu, *(_DWORD *)(v81 + 16));
  free((void *)v81);
  v82 = (struct QTilemap_s **)ptQTask[53].tQTaskChildren.ptTail;
  QTilemap_Delete(*v82);
  v83 = *(_DWORD *)((unsigned int)(v82 - 1) & 0xFFFFFFFC);
  --Mem_nCurrentAllocations;
  Node_Remove((_DWORD **)v83);
  memset(*(void **)(v83 + 8), 0xCDu, *(_DWORD *)(v83 + 16));
  free((void *)v83);
  v84 = (struct QTilemap_s **)ptQTask[53].tQTaskRefList.ptHead;
  QTilemap_Delete(*v84);
  v85 = *(_DWORD *)((unsigned int)(v84 - 1) & 0xFFFFFFFC);
  --Mem_nCurrentAllocations;
  Node_Remove((_DWORD **)v85);
  memset(*(void **)(v85 + 8), 0xCDu, *(_DWORD *)(v85 + 16));
  free((void *)v85);
  QSprite_DeAlloc((struct QSprite_s *)&ptQTask[7].tQTaskChildren.ptMiddle);
  QSprite_DeAlloc((struct QSprite_s *)&ptQTask[6].tQTaskRefList.ptTail);
  QSprite_DeAlloc((struct QSprite_s *)&ptQTask[6].ptPrev);
  QSprite_DeAlloc((struct QSprite_s *)&ptQTask[7].eQTaskType);
  QSprite_DeAlloc((struct QSprite_s *)&ptQTask[8].tQTaskRefList);
  QSprite_DeAlloc((struct QSprite_s *)&ptQTask[9].ptPrev);
  QSprite_DeAlloc((struct QSprite_s *)&ptQTask[3].ptPrev);
  QSprite_DeAlloc((struct QSprite_s *)&ptQTask[3].tQTaskRefList.ptTail);
  QSprite_DeAlloc((struct QSprite_s *)&ptQTask[4].tQTaskChildren.ptMiddle);
  QSprite_DeAlloc((struct QSprite_s *)&ptQTask[4].eQTaskType);
  QSprite_DeAlloc((struct QSprite_s *)&ptQTask[5].tQTaskRefList);
  v86 = (struct QSprite_s *)&ptQTask[12].tQTaskRefList.ptTail;
  v87 = 4;
  do
  {
    QSprite_DeAlloc(v86++);
    --v87;
  }
  while ( v87 );
  v88 = (struct QSprite_s *)&ptQTask[15].ptPrev;
  v89 = 21;
  do
  {
    QSprite_DeAlloc(v88++);
    --v89;
  }
  while ( v89 );
  FontManager_DeleteFont((struct QSprite_s *)ptQTask[27].tQTaskRefList.ptTail);
  v90 = ptQTask[3].ptNext;
  ptQTask[27].tQTaskRefList.ptTail = nullptr;
  v91 = Resource_tResourceList.ptHead;
  v92 = Resource_tResourceList.ptHead->ptNext;
  if ( Resource_tResourceList.ptHead->ptNext )
  {
    while ( v91->pxData != v90 )
    {
      v91 = v92;
      v92 = v92->ptNext;
      if ( !v92 )
        goto LABEL_50;
    }
    nType = v91->nType;
    if ( nType != 3 && nType != 1 )
      Resource_Remove(v91);
  }
LABEL_50:
  RenderContext_DeAlloc((struct RenderContext_s *)&ptQTask[1]);
  StatusScreen_ptStatusScreenQTask = nullptr;
}

// source: j/0/screens/statusscreen/statusscreen.c:1147  [anchor-callee]
void __cdecl StatusScreen_SortByFrags(struct StatusScreen_t *ptStatusScreen)
{
  struct StatusScreen_t *v1; // edx
  int nScoreboardNumPlayers; // ecx
  int v3; // ebx
  struct Client_s **v4; // eax
  struct Client_s *v5; // ecx
  struct Client_s *v6; // edx
  int nTalkOffset; // esi
  int v8; // edi
  enum bool isChanged; // [esp+0h] [ebp-4h]

  v1 = ptStatusScreen;
  nScoreboardNumPlayers = ptStatusScreen->nScoreboardNumPlayers;
  if ( nScoreboardNumPlayers > 1 )
  {
    do
    {
      v3 = 0;
      isChanged = false;
      if ( nScoreboardNumPlayers - 1 <= 0 )
        break;
      v4 = &v1->aptScoreClient[1];
      do
      {
        v5 = *(v4 - 1);
        v6 = *v4;
        nTalkOffset = (*v4)->nTalkOffset;
        v8 = v5->nTalkOffset;
        if ( nTalkOffset > v8 || v6->nPoints > v5->nPoints && nTalkOffset == v8 )
        {
          *(v4 - 1) = v6;
          *v4 = v5;
          isChanged = true;
        }
        v1 = ptStatusScreen;
        nScoreboardNumPlayers = ptStatusScreen->nScoreboardNumPlayers;
        ++v3;
        ++v4;
      }
      while ( v3 < nScoreboardNumPlayers - 1 );
    }
    while ( isChanged );
  }
}

// source: j/0/screens/statusscreen/statusscreen.c:1197  [anchor-callee]
void __cdecl StatusScreen_DisplayScoreboard(struct StatusScreen_t *ptStatusScreen)
{
  #pragma pack(push, 1)
  union
  {
    struct { double v149; };
    struct { double v150; };
    struct { char igi2_o2[8]; int v151; };
    struct { char igi2_o3[8]; int v152; };
    struct { char igi2_o4[28]; struct Client_s **j; };
    struct { char igi2_o5[28]; int nHeight; };
    struct { char igi2_o6[28]; int v154; };
    struct { char igi2_o7[28]; int v155; };
    struct { char igi2_o8[28]; int v156; };
    struct { char igi2_o9[28]; struct QTilemap_s **v157; };
    struct { char igi2_o10[28]; struct QTilemap_s *v158; };
    struct { char igi2_o11[28]; __int16 **v159; };
    struct { char igi2_o12[28]; __int16 **v160; };
    struct { char igi2_o13[28]; __int16 **v161; };
    struct { char igi2_o14[28]; int v162; };
    struct { char igi2_o15[36]; struct ScoreText_t *v164; };
    struct { char igi2_o16[36]; int v165; };
    struct { char igi2_o17[36]; __int16 **v166; };
    struct { char igi2_o18[36]; struct QTilemap_s **v167; };
    struct { char igi2_o19[36]; __int16 **v168; };
    struct { char igi2_o20[36]; __int16 **v169; };
    struct { char igi2_o21[36]; __int16 **v170; };
    struct { char igi2_o22[44]; float v171; };
    struct { char igi2_o23[44]; float v172; };
    struct { char igi2_o24[44]; float v173; };
    struct { char igi2_o25[44]; float v174; };
    struct { char igi2_o26[44]; float v175; };
    struct { char igi2_o27[44]; float v176; };
    struct { char igi2_o28[48]; float v177; };
    struct { char igi2_o29[48]; float v178; };
    struct { char igi2_o30[48]; float v179; };
    struct { char igi2_o31[48]; float v180; };
    struct { char igi2_o32[48]; float v181; };
    struct { char igi2_o33[48]; float v182; };
    struct { char igi2_o34[52]; char v183[8]; };
    struct { char igi2_o35[60]; float v184; };
    struct { char igi2_o36[64]; struct Client_s *v185; };
    struct { char igi2_o37[68]; float v186; };
    struct { char igi2_o38[72]; int nWidth; };
    struct { char igi2_o39[76]; float v188; };
    struct { char igi2_o40[80]; int v189; };
    struct { char igi2_o41[84]; int eNetworkID; };
    struct { char igi2_o42[88]; struct Client_s *v191; };
    struct { char igi2_o43[92]; char Buffer[256]; };
    char igi2_extent[348];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct Client_s *ClientFromNetworkID; // esi
  struct StatusScreen_t *v2; // edi
  struct StaticTilemap_s *ptScoreTeam1Text; // eax
  struct StaticTilemap_s *v4; // eax
  struct QTask_s *FirstChildOfType; // eax
  int ptNext; // ecx
  char *LocalizedStringForLanguage; // eax
  struct StaticTilemap_s *ptScorePoints1Text; // eax
  struct StaticTilemap_s *ptScoreHead1Text; // eax
  struct StaticTilemap_s *v10; // eax
  double v11; // st7
  struct StaticTilemap_s *ptScoreHead2Text; // eax
  double v13; // st7
  struct StaticTilemap_s *ptScoreHead3Text; // eax
  double v15; // st7
  struct StaticTilemap_s *ptScoreHead4Text; // eax
  int nScoreboardNumPlayers; // eax
  struct ScoreText_t *atTeam1ScoreText; // eax
  int v19; // ebx
  int v20; // edx
  int v21; // ecx
  struct StaticTilemap_s **p_ptName; // esi
  struct WeaponTypeItem_s *WeaponTypeItemFromWeaponType; // eax
  __int16 **v24; // eax
  __int16 *v25; // edx
  struct QTilemap_s *v26; // edi
  unsigned __int8 v27; // dl
  int v28; // eax
  char *v29; // ecx
  int v30; // edi
  float v31; // esi
  __int16 **v32; // eax
  __int16 *v33; // edx
  struct QTilemap_s *v34; // ebx
  int v35; // eax
  char *v36; // edi
  int v37; // edx
  unsigned __int8 v38; // cl
  __int16 **v39; // eax
  __int16 *v40; // edx
  struct QTilemap_s *v41; // ebx
  int v42; // eax
  char *v43; // edi
  int v44; // edx
  unsigned __int8 v45; // cl
  __int16 **v46; // eax
  __int16 *v47; // edx
  struct QTilemap_s *v48; // ebx
  int v49; // eax
  char *v50; // edi
  int v51; // edx
  unsigned __int8 v52; // cl
  int v53; // eax
  double v54; // st7
  int v55; // eax
  int v56; // edx
  int v57; // ecx
  int v58; // edi
  __int16 *v59; // eax
  float *v60; // eax
  double v61; // st7
  int v62; // eax
  double v63; // st7
  int v64; // eax
  double v65; // st7
  int v66; // esi
  bool v67; // cc
  double v68; // st7
  struct StaticTilemap_s *ptScoreTeam2Text; // edx
  struct StaticTilemap_s *v70; // eax
  struct QTask_s *v71; // eax
  int ptPrev; // ecx
  char *v73; // eax
  __int16 **ptScorePoints2Text; // esi
  __int16 *v75; // edx
  struct QTilemap_s *v76; // ebx
  unsigned __int8 v77; // cl
  int v78; // eax
  char *i; // esi
  struct StaticTilemap_s *v80; // eax
  struct StaticTilemap_s *v81; // eax
  struct StaticTilemap_s *v82; // eax
  double v83; // st7
  struct StaticTilemap_s *v84; // eax
  double v85; // st7
  struct StaticTilemap_s *v86; // eax
  double v87; // st7
  struct StaticTilemap_s *v88; // eax
  struct QTilemap_s *ptQTilemap; // eax
  int v90; // ecx
  double v91; // st7
  int v92; // edx
  int v93; // eax
  struct Client_s *v94; // edi
  bool v95; // zf
  float v96; // esi
  int v97; // ebx
  char v98; // al
  struct WeaponTypeItem_s *v99; // eax
  __int16 **v100; // eax
  __int16 *v101; // edx
  struct QTilemap_s *v102; // edi
  int v103; // eax
  char *v104; // ecx
  int v105; // ebx
  unsigned __int8 v106; // dl
  int v107; // edx
  struct QTilemap_s *v108; // edi
  unsigned __int8 v109; // cl
  char *zPlayerName; // eax
  int anID; // edx
  unsigned __int8 *v112; // ebx
  __int16 **v113; // eax
  __int16 *v114; // edx
  struct QTilemap_s *v115; // ebx
  int v116; // eax
  char *v117; // edi
  int v118; // edx
  unsigned __int8 v119; // cl
  __int16 **v120; // eax
  __int16 *v121; // edx
  struct QTilemap_s *v122; // ebx
  int v123; // eax
  char *v124; // edi
  int v125; // edx
  unsigned __int8 v126; // cl
  __int16 **v127; // eax
  __int16 *v128; // edx
  struct QTilemap_s *v129; // ebx
  int v130; // eax
  char *v131; // edi
  int v132; // edx
  unsigned __int8 v133; // cl
  int v134; // eax
  double v135; // st7
  int v136; // eax
  int *v137; // edx
  int v138; // eax
  int v139; // ecx
  float v140; // edi
  __int16 *v141; // eax
  float *v142; // eax
  double v143; // st7
  int v144; // eax
  double v145; // st7
  int v146; // eax
  double v147; // st7
  int v148; // esi

  igi2_frame.nWidth = Display_tActiveMode.nWidth;
  igi2_frame.nHeight = Display_tActiveMode.nHeight;
  ClientFromNetworkID = NetManager_GetClientFromNetworkID((int)Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle);
  igi2_frame.v191 = ClientFromNetworkID;
  if ( ClientFromNetworkID )
  {
    v2 = ptStatusScreen;
    StatusScreen_SortByFrags(ptStatusScreen);
    igi2_frame.eNetworkID = ClientFromNetworkID->eNetworkID;
    igi2_frame.v184 = (double)igi2_frame.nWidth * 0.5;
    *(float *)&igi2_frame.nWidth = (double)igi2_frame.nHeight * 0.5;
    igi2_frame.v177 = *(float *)&igi2_frame.nWidth - (double)Display_tActiveMode.nHeight * 0.46000000834465027;
    *(_QWORD *)igi2_frame.v183 = (__int64)(igi2_frame.v184 - (double)Display_tActiveMode.nWidth * 0.30000001192092896);
    ptScoreTeam1Text = ptStatusScreen->ptScoreTeam1Text;
    igi2_frame.v186 = (float)*(int *)igi2_frame.v183;
    ptScoreTeam1Text->vX = igi2_frame.v186;
    *(_QWORD *)igi2_frame.v183 = (__int64)igi2_frame.v177;
    igi2_frame.v171 = (float)*(int *)igi2_frame.v183;
    ptStatusScreen->ptScoreTeam1Text->vY = igi2_frame.v171;
    v4 = ptStatusScreen->ptScoreTeam1Text;
    QTilemap_Register(
      v4->ptQTilemap,
      v4->vX,
      v4->vY,
      v4->vR,
      v4->vG,
      v4->vB,
      v4->vA,
      v4->vZ,
      v4->bQGraphicFlags | 0x40000000,
      v4->nPri);
    FirstChildOfType = QTask_GetFirstChildOfType(Flow_ptFlow->ptNetManagerQTask, TeamManager_eQTaskType);
    if ( FirstChildOfType )
      ptNext = (int)FirstChildOfType[1].ptNext;
    else
      ptNext = -1;
    igi2_frame.v151 = ptNext;
    LocalizedStringForLanguage = Config_GetLocalizedStringForLanguage(
                                   "mp/Score",
                                   Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eLanguage,
                                   true);
    sprintf(igi2_frame.Buffer, "%s: %d", LocalizedStringForLanguage, igi2_frame.v151);
    Text_SetString(ptStatusScreen->ptScorePoints1Text, igi2_frame.Buffer);
    ptStatusScreen->ptScorePoints1Text->bQGraphicFlags |= 0x80u;
    *(_QWORD *)igi2_frame.v183 = (__int64)((double)Display_tActiveMode.nWidth * 0.25 + igi2_frame.v184);
    ptStatusScreen->ptScorePoints1Text->vX = (float)*(int *)igi2_frame.v183;
    ptStatusScreen->ptScorePoints1Text->vY = igi2_frame.v171;
    ptScorePoints1Text = ptStatusScreen->ptScorePoints1Text;
    QTilemap_Register(
      ptScorePoints1Text->ptQTilemap,
      ptScorePoints1Text->vX,
      ptScorePoints1Text->vY,
      ptScorePoints1Text->vR,
      ptScorePoints1Text->vG,
      ptScorePoints1Text->vB,
      ptScorePoints1Text->vA,
      ptScorePoints1Text->vZ,
      ptScorePoints1Text->bQGraphicFlags | 0x40000000,
      ptScorePoints1Text->nPri);
    ptScoreHead1Text = ptStatusScreen->ptScoreHead1Text;
    igi2_frame.v154 = ptScoreHead1Text->ptQTilemap->nHeight
         * ptScoreHead1Text->ptQTilemap->ptQSprite->atQAnimframe[ptScoreHead1Text->ptQTilemap->ptQSprite->nQAnimframes].nHeight;
    ptScoreHead1Text->vX = igi2_frame.v186;
    igi2_frame.v178 = (double)igi2_frame.v154 + igi2_frame.v177 + 8.0;
    *(_QWORD *)igi2_frame.v183 = (__int64)igi2_frame.v178;
    igi2_frame.v172 = (float)*(int *)igi2_frame.v183;
    ptStatusScreen->ptScoreHead1Text->vY = igi2_frame.v172;
    v10 = ptStatusScreen->ptScoreHead1Text;
    QTilemap_Register(
      v10->ptQTilemap,
      v10->vX,
      v10->vY,
      v10->vR,
      v10->vG,
      v10->vB,
      v10->vA,
      v10->vZ,
      v10->bQGraphicFlags | 0x40000000,
      v10->nPri);
    v11 = (double)Display_tActiveMode.nWidth * 0.14000000059604645;
    ptStatusScreen->ptScoreHead2Text->bQGraphicFlags |= 0x80u;
    *(_QWORD *)igi2_frame.v183 = (__int64)(v11 + igi2_frame.v184);
    ptStatusScreen->ptScoreHead2Text->vX = (float)*(int *)igi2_frame.v183;
    ptStatusScreen->ptScoreHead2Text->vY = igi2_frame.v172;
    ptScoreHead2Text = ptStatusScreen->ptScoreHead2Text;
    QTilemap_Register(
      ptScoreHead2Text->ptQTilemap,
      ptScoreHead2Text->vX,
      ptScoreHead2Text->vY,
      ptScoreHead2Text->vR,
      ptScoreHead2Text->vG,
      ptScoreHead2Text->vB,
      ptScoreHead2Text->vA,
      ptScoreHead2Text->vZ,
      ptScoreHead2Text->bQGraphicFlags | 0x40000000,
      ptScoreHead2Text->nPri);
    v13 = (double)Display_tActiveMode.nWidth * 0.25;
    ptStatusScreen->ptScoreHead3Text->bQGraphicFlags |= 0x80u;
    *(_QWORD *)igi2_frame.v183 = (__int64)(v13 + igi2_frame.v184);
    ptStatusScreen->ptScoreHead3Text->vX = (float)*(int *)igi2_frame.v183;
    ptStatusScreen->ptScoreHead3Text->vY = igi2_frame.v172;
    ptScoreHead3Text = ptStatusScreen->ptScoreHead3Text;
    QTilemap_Register(
      ptScoreHead3Text->ptQTilemap,
      ptScoreHead3Text->vX,
      ptScoreHead3Text->vY,
      ptScoreHead3Text->vR,
      ptScoreHead3Text->vG,
      ptScoreHead3Text->vB,
      ptScoreHead3Text->vA,
      ptScoreHead3Text->vZ,
      ptScoreHead3Text->bQGraphicFlags | 0x40000000,
      ptScoreHead3Text->nPri);
    v15 = (double)Display_tActiveMode.nWidth * 0.019999999552965164;
    ptStatusScreen->ptScoreHead4Text->bQGraphicFlags |= 0x80u;
    *(_QWORD *)igi2_frame.v183 = (__int64)(v15 + igi2_frame.v184);
    ptStatusScreen->ptScoreHead4Text->vX = (float)*(int *)igi2_frame.v183;
    ptStatusScreen->ptScoreHead4Text->vY = igi2_frame.v172;
    ptScoreHead4Text = ptStatusScreen->ptScoreHead4Text;
    QTilemap_Register(
      ptScoreHead4Text->ptQTilemap,
      ptScoreHead4Text->vX,
      ptScoreHead4Text->vY,
      ptScoreHead4Text->vR,
      ptScoreHead4Text->vG,
      ptScoreHead4Text->vB,
      ptScoreHead4Text->vA,
      ptScoreHead4Text->vZ,
      ptScoreHead4Text->bQGraphicFlags | 0x40000000,
      ptScoreHead4Text->nPri);
    igi2_frame.v155 = ptStatusScreen->ptScoreHead1Text->ptQTilemap->nHeight
         * ptStatusScreen->ptScoreHead1Text->ptQTilemap->ptQSprite->atQAnimframe[ptStatusScreen->ptScoreHead1Text->ptQTilemap->ptQSprite->nQAnimframes].nHeight;
    igi2_frame.v179 = (double)igi2_frame.v155 + igi2_frame.v178 + (double)igi2_frame.v155;
    nScoreboardNumPlayers = ptStatusScreen->nScoreboardNumPlayers;
    igi2_frame.v189 = 0;
    if ( nScoreboardNumPlayers > 0 )
    {
      atTeam1ScoreText = ptStatusScreen->atTeam1ScoreText;
      LODWORD(igi2_frame.v186) = ptStatusScreen->aptScoreClient;
      do
      {
        v19 = *(_DWORD *)LODWORD(igi2_frame.v186);
        v20 = *(_DWORD *)(*(_DWORD *)LODWORD(igi2_frame.v186) + 60);
        v21 = *(_DWORD *)(*(_DWORD *)(*(_DWORD *)LODWORD(igi2_frame.v186) + 648) + 8);
        p_ptName = &atTeam1ScoreText->ptName;
        igi2_frame.v185 = *(struct Client_s **)LODWORD(igi2_frame.v186);
        igi2_frame.v188 = *(float *)&atTeam1ScoreText;
        igi2_frame.v156 = v21;
        if ( !v20 )
        {
          igi2_frame.v164 = atTeam1ScoreText + 1;
          if ( *(_BYTE *)(v21 + 1180) )
          {
            _snprintf(igi2_frame.v183, 7u, "S [%d]", *(_DWORD *)(v19 + 40));
          }
          else
          {
            WeaponTypeItemFromWeaponType = Weapon_GetWeaponTypeItemFromWeaponType(
                                             *(struct QTask_s **)(v21 + 1320),
                                             "WEAPON_ID_C4BOMB");
            if ( WeaponTypeItemFromWeaponType
              && WeaponTypeItemFromWeaponType->isActive
              && igi2_frame.v191->eTeam == NetMission_eAttackingTeam )
            {
              _snprintf(igi2_frame.v183, 7u, "B [%d]", *(_DWORD *)(v19 + 40));
            }
            else
            {
              _snprintf(igi2_frame.v183, 7u, "  [%d]", *(_DWORD *)(v19 + 40));
            }
          }
          if ( *(_DWORD *)(v19 + 40) == igi2_frame.eNetworkID )
          {
            p_ptName[3]->vR = 51.20000076293945;
            p_ptName[3]->vG = 76.80000305175781;
            p_ptName[3]->vB = 128.0;
            (*p_ptName)->vR = 51.20000076293945;
            (*p_ptName)->vG = 76.80000305175781;
            (*p_ptName)->vB = 128.0;
            p_ptName[1]->vR = 51.20000076293945;
            p_ptName[1]->vG = 76.80000305175781;
            p_ptName[1]->vB = 128.0;
            p_ptName[2]->vR = 51.20000076293945;
            p_ptName[2]->vG = 76.80000305175781;
            p_ptName[2]->vB = 128.0;
            p_ptName[4]->vR = 51.20000076293945;
            p_ptName[4]->vG = 76.80000305175781;
            p_ptName[4]->vB = 128.0;
          }
          else if ( *(_BYTE *)(igi2_frame.v156 + 1180) )
          {
            p_ptName[3]->vR = 128.0;
            p_ptName[3]->vG = 51.20000076293945;
            p_ptName[3]->vB = 38.400001525878906;
            (*p_ptName)->vR = 128.0;
            (*p_ptName)->vG = 51.20000076293945;
            (*p_ptName)->vB = 38.400001525878906;
            p_ptName[1]->vR = 128.0;
            p_ptName[1]->vG = 51.20000076293945;
            p_ptName[1]->vB = 38.400001525878906;
            p_ptName[2]->vR = 128.0;
            p_ptName[2]->vG = 51.20000076293945;
            p_ptName[2]->vB = 38.400001525878906;
            p_ptName[4]->vR = 128.0;
            p_ptName[4]->vG = 51.20000076293945;
            p_ptName[4]->vB = 38.400001525878906;
          }
          else
          {
            p_ptName[3]->vR = 128.0;
            p_ptName[3]->vG = 128.0;
            p_ptName[3]->vB = 128.0;
            (*p_ptName)->vR = 128.0;
            (*p_ptName)->vG = 128.0;
            (*p_ptName)->vB = 128.0;
            p_ptName[1]->vR = 128.0;
            p_ptName[1]->vG = 128.0;
            p_ptName[1]->vB = 128.0;
            p_ptName[2]->vR = 128.0;
            p_ptName[2]->vG = 128.0;
            p_ptName[2]->vB = 128.0;
            p_ptName[4]->vR = 128.0;
            p_ptName[4]->vG = 128.0;
            p_ptName[4]->vB = 128.0;
          }
          v24 = (__int16 **)p_ptName[3];
          v25 = *v24;
          igi2_frame.v157 = (struct QTilemap_s **)v24;
          memset(*((void **)*v24 + 3), 0, 2 * (*v24)[3]);
          memset(v25 + 8, 0, v25[3] * v25[2]);
          v26 = (struct QTilemap_s *)*v24;
          v27 = igi2_frame.v183[0];
          v28 = *(_DWORD *)(*((_DWORD *)*v24 + 2) + 12) + 16;
          igi2_frame.v158 = *igi2_frame.v157;
          v29 = igi2_frame.v183;
          if ( igi2_frame.v183[0] )
          {
            v30 = v26->anID - (unsigned __int8 *)igi2_frame.v183;
            do
            {
              v29[v30] = *(_BYTE *)(v27 + v28);
              v27 = *++v29;
            }
            while ( v27 );
            v26 = igi2_frame.v158;
          }
          QTilemap_UpdateGraphicWidth(v26, 0);
          Text_SetString(*p_ptName, igi2_frame.v185->zPlayerName);
          igi2_frame.v149 = *(float *)&igi2_frame.v185->tStats.nLostPacks;
          if ( StatusScreen_isShowNetStats )
            sprintf(
              igi2_frame.Buffer,
              "%d[%d][%d][%d]/%2.1f%s",
              igi2_frame.v185->tStats.nPing,
              igi2_frame.v185->tStats.vPacketLoss,
              igi2_frame.v185->tStats.nSentPacks,
              igi2_frame.v185->tStats.nReceivedPacks,
              igi2_frame.v149,
              "%");
          else
            sprintf(igi2_frame.Buffer, "%d/%2.1f%s", igi2_frame.v185->tStats.nPing, igi2_frame.v149, "%");
          v31 = igi2_frame.v188;
          v32 = *(__int16 ***)(LODWORD(igi2_frame.v188) + 4);
          v33 = *v32;
          igi2_frame.v159 = v32;
          memset(*((void **)*v32 + 3), 0, 2 * (*v32)[3]);
          memset(v33 + 8, 0, v33[3] * v33[2]);
          v34 = (struct QTilemap_s *)*v32;
          v35 = *(_DWORD *)(*((_DWORD *)*v32 + 2) + 12) + 16;
          v36 = igi2_frame.Buffer;
          if ( igi2_frame.Buffer[0] )
          {
            v37 = (char *)(*igi2_frame.v159 + 8) - igi2_frame.Buffer;
            v38 = igi2_frame.Buffer[0];
            do
            {
              v36[v37] = *(_BYTE *)(v38 + v35);
              v38 = *++v36;
            }
            while ( v38 );
          }
          QTilemap_UpdateGraphicWidth(v34, 0);
          sprintf(igi2_frame.Buffer, "%d/%d", igi2_frame.v185->nPoints, *(_DWORD *)&igi2_frame.v185->isTalk);
          v39 = *(__int16 ***)(LODWORD(v31) + 8);
          v40 = *v39;
          igi2_frame.v160 = v39;
          memset(*((void **)*v39 + 3), 0, 2 * (*v39)[3]);
          memset(v40 + 8, 0, v40[3] * v40[2]);
          v41 = (struct QTilemap_s *)*v39;
          v42 = *(_DWORD *)(*((_DWORD *)*v39 + 2) + 12) + 16;
          v43 = igi2_frame.Buffer;
          if ( igi2_frame.Buffer[0] )
          {
            v44 = (char *)(*igi2_frame.v160 + 8) - igi2_frame.Buffer;
            v45 = igi2_frame.Buffer[0];
            do
            {
              v43[v44] = *(_BYTE *)(v45 + v42);
              v45 = *++v43;
            }
            while ( v45 );
          }
          QTilemap_UpdateGraphicWidth(v41, 0);
          sprintf(igi2_frame.Buffer, (char *const)&g_ptNetManager.tReceiveCounters.tCounters[9].nBytes, igi2_frame.v185->nTalkOffset);
          v46 = *(__int16 ***)(LODWORD(v31) + 16);
          v47 = *v46;
          igi2_frame.v161 = v46;
          memset(*((void **)*v46 + 3), 0, 2 * (*v46)[3]);
          memset(v47 + 8, 0, v47[3] * v47[2]);
          v48 = (struct QTilemap_s *)*v46;
          v49 = *(_DWORD *)(*((_DWORD *)*v46 + 2) + 12) + 16;
          v50 = igi2_frame.Buffer;
          if ( igi2_frame.Buffer[0] )
          {
            v51 = (char *)(*igi2_frame.v161 + 8) - igi2_frame.Buffer;
            v52 = igi2_frame.Buffer[0];
            do
            {
              v50[v51] = *(_BYTE *)(v52 + v49);
              v52 = *++v50;
            }
            while ( v52 );
          }
          QTilemap_UpdateGraphicWidth(v48, 0);
          v53 = *(_DWORD *)(LODWORD(v31) + 12);
          v54 = igi2_frame.v184 - (double)Display_tActiveMode.nWidth * 0.30000001192092896;
          igi2_frame.v188 = v54;
          *(float *)(v53 + 4) = (float)(int)(__int64)v54;
          igi2_frame.v173 = (float)(__int64)igi2_frame.v179;
          *(float *)(*(_DWORD *)(LODWORD(v31) + 12) + 8) = igi2_frame.v173;
          v55 = *(_DWORD *)(LODWORD(v31) + 12);
          QTilemap_Register(
            *(struct QTilemap_s **)v55,
            *(float *)(v55 + 4),
            *(float *)(v55 + 8),
            *(float *)(v55 + 20),
            *(float *)(v55 + 24),
            *(float *)(v55 + 28),
            *(float *)(v55 + 16),
            *(float *)(v55 + 12),
            *(_DWORD *)(v55 + 36) | 0x40000000,
            *(_DWORD *)(v55 + 32));
          v56 = *(_DWORD *)(LODWORD(v31) + 12);
          v57 = *(__int16 *)(*(_DWORD *)v56 + 6);
          v58 = 0;
          igi2_frame.v162 = 0;
          if ( v57 > 0 )
          {
            v59 = *(__int16 **)(*(_DWORD *)v56 + 12);
            do
            {
              if ( *v59 > v58 )
                v58 = *v59;
              ++v59;
              --v57;
            }
            while ( v57 );
            igi2_frame.v162 = v58;
          }
          *(float *)(*(_DWORD *)LODWORD(v31) + 4) = (float)(int)(__int64)((double)igi2_frame.v162 + igi2_frame.v188 + 20.0);
          *(float *)(*(_DWORD *)LODWORD(v31) + 8) = igi2_frame.v173;
          v60 = *(float **)LODWORD(v31);
          QTilemap_Register(
            **(struct QTilemap_s ***)LODWORD(v31),
            v60[1],
            v60[2],
            v60[5],
            v60[6],
            v60[7],
            v60[4],
            v60[3],
            *(_DWORD *)(*(_DWORD *)LODWORD(v31) + 36) | 0x40000000,
            *(_DWORD *)(*(_DWORD *)LODWORD(v31) + 32));
          if ( igi2_frame.v185->nTalkOffset > 0 )
          {
            v61 = (double)Display_tActiveMode.nWidth * 0.019999999552965164;
            *(_DWORD *)(*(_DWORD *)(LODWORD(v31) + 16) + 36) |= 0x80u;
            *(float *)(*(_DWORD *)(LODWORD(v31) + 16) + 4) = (float)(int)(__int64)(v61 + igi2_frame.v184);
            *(float *)(*(_DWORD *)(LODWORD(v31) + 16) + 8) = igi2_frame.v173;
            v62 = *(_DWORD *)(LODWORD(v31) + 16);
            QTilemap_Register(
              *(struct QTilemap_s **)v62,
              *(float *)(v62 + 4),
              *(float *)(v62 + 8),
              *(float *)(v62 + 20),
              *(float *)(v62 + 24),
              *(float *)(v62 + 28),
              *(float *)(v62 + 16),
              *(float *)(v62 + 12),
              *(_DWORD *)(v62 + 36) | 0x40000000,
              *(_DWORD *)(v62 + 32));
          }
          v63 = (double)Display_tActiveMode.nWidth * 0.14000000059604645;
          *(_DWORD *)(*(_DWORD *)(LODWORD(v31) + 8) + 36) |= 0x80u;
          *(float *)(*(_DWORD *)(LODWORD(v31) + 8) + 4) = (float)(int)(__int64)(v63 + igi2_frame.v184);
          *(float *)(*(_DWORD *)(LODWORD(v31) + 8) + 8) = igi2_frame.v173;
          v64 = *(_DWORD *)(LODWORD(v31) + 8);
          QTilemap_Register(
            *(struct QTilemap_s **)v64,
            *(float *)(v64 + 4),
            *(float *)(v64 + 8),
            *(float *)(v64 + 20),
            *(float *)(v64 + 24),
            *(float *)(v64 + 28),
            *(float *)(v64 + 16),
            *(float *)(v64 + 12),
            *(_DWORD *)(v64 + 36) | 0x40000000,
            *(_DWORD *)(v64 + 32));
          v65 = (double)Display_tActiveMode.nWidth * 0.25;
          *(_DWORD *)(*(_DWORD *)(LODWORD(v31) + 4) + 36) |= 0x80u;
          *(float *)(*(_DWORD *)(LODWORD(v31) + 4) + 4) = (float)(int)(__int64)(v65 + igi2_frame.v184);
          *(float *)(*(_DWORD *)(LODWORD(v31) + 4) + 8) = igi2_frame.v173;
          v66 = *(_DWORD *)(LODWORD(v31) + 4);
          QTilemap_Register(
            *(struct QTilemap_s **)v66,
            *(float *)(v66 + 4),
            *(float *)(v66 + 8),
            *(float *)(v66 + 20),
            *(float *)(v66 + 24),
            *(float *)(v66 + 28),
            *(float *)(v66 + 16),
            *(float *)(v66 + 12),
            *(_DWORD *)(v66 + 36) | 0x40000000,
            *(_DWORD *)(v66 + 32));
          v2 = ptStatusScreen;
          atTeam1ScoreText = igi2_frame.v164;
          igi2_frame.v179 = (double)(ptStatusScreen->ptScoreHead1Text->ptQTilemap->nHeight
                        * ptStatusScreen->ptScoreHead1Text->ptQTilemap->ptQSprite->atQAnimframe[ptStatusScreen->ptScoreHead1Text->ptQTilemap->ptQSprite->nQAnimframes].nHeight)
               + igi2_frame.v179
               + 8.0;
        }
        v67 = ++igi2_frame.v189 < v2->nScoreboardNumPlayers;
        LODWORD(igi2_frame.v186) += 4;
      }
      while ( v67 );
    }
    v68 = (double)Display_tActiveMode.nWidth;
    igi2_frame.v180 = v68 * 0.009999999776482582 + *(float *)&igi2_frame.nWidth;
    *(_QWORD *)igi2_frame.v183 = (__int64)(igi2_frame.v184 - 0.30000001192092896 * v68);
    ptScoreTeam2Text = v2->ptScoreTeam2Text;
    igi2_frame.v186 = (float)*(int *)igi2_frame.v183;
    ptScoreTeam2Text->vX = igi2_frame.v186;
    *(_QWORD *)igi2_frame.v183 = (__int64)igi2_frame.v180;
    igi2_frame.v174 = (float)*(int *)igi2_frame.v183;
    v2->ptScoreTeam2Text->vY = igi2_frame.v174;
    v70 = v2->ptScoreTeam2Text;
    QTilemap_Register(
      v70->ptQTilemap,
      v70->vX,
      v70->vY,
      v70->vR,
      v70->vG,
      v70->vB,
      v70->vA,
      v70->vZ,
      v70->bQGraphicFlags | 0x40000000,
      v70->nPri);
    v71 = QTask_GetFirstChildOfType(Flow_ptFlow->ptNetManagerQTask, TeamManager_eQTaskType);
    if ( v71 )
      ptPrev = (int)v71[1].ptPrev;
    else
      ptPrev = -1;
    igi2_frame.v152 = ptPrev;
    v73 = Config_GetLocalizedStringForLanguage(
            "mp/Score",
            Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eLanguage,
            true);
    sprintf(igi2_frame.Buffer, "%s: %d", v73, igi2_frame.v152);
    ptScorePoints2Text = (__int16 **)v2->ptScorePoints2Text;
    v75 = *ptScorePoints2Text;
    memset(*((void **)*ptScorePoints2Text + 3), 0, 2 * (*ptScorePoints2Text)[3]);
    memset(v75 + 8, 0, v75[3] * v75[2]);
    v76 = (struct QTilemap_s *)*ptScorePoints2Text;
    v77 = igi2_frame.Buffer[0];
    v78 = *(_DWORD *)(*((_DWORD *)*ptScorePoints2Text + 2) + 12) + 16;
    for ( i = igi2_frame.Buffer; v77; ++i )
    {
      i[v76->anID - (unsigned __int8 *)igi2_frame.Buffer] = *(_BYTE *)(v77 + v78);
      v77 = i[1];
    }
    QTilemap_UpdateGraphicWidth(v76, 0);
    ptStatusScreen->ptScorePoints2Text->bQGraphicFlags |= 0x80u;
    *(_QWORD *)igi2_frame.v183 = (__int64)((double)Display_tActiveMode.nWidth * 0.25 + igi2_frame.v184);
    ptStatusScreen->ptScorePoints2Text->vX = (float)*(int *)igi2_frame.v183;
    ptStatusScreen->ptScorePoints2Text->vY = igi2_frame.v174;
    v80 = ptStatusScreen->ptScorePoints2Text;
    QTilemap_Register(
      v80->ptQTilemap,
      v80->vX,
      v80->vY,
      v80->vR,
      v80->vG,
      v80->vB,
      v80->vA,
      v80->vZ,
      v80->bQGraphicFlags | 0x40000000,
      v80->nPri);
    v81 = ptStatusScreen->ptScoreHead1Text;
    igi2_frame.v165 = v81->ptQTilemap->nHeight
         * v81->ptQTilemap->ptQSprite->atQAnimframe[v81->ptQTilemap->ptQSprite->nQAnimframes].nHeight;
    v81->vX = igi2_frame.v186;
    igi2_frame.v181 = (double)igi2_frame.v165 + igi2_frame.v180 + 8.0;
    *(_QWORD *)igi2_frame.v183 = (__int64)igi2_frame.v181;
    igi2_frame.v175 = (float)*(int *)igi2_frame.v183;
    ptStatusScreen->ptScoreHead1Text->vY = igi2_frame.v175;
    v82 = ptStatusScreen->ptScoreHead1Text;
    QTilemap_Register(
      v82->ptQTilemap,
      v82->vX,
      v82->vY,
      v82->vR,
      v82->vG,
      v82->vB,
      v82->vA,
      v82->vZ,
      v82->bQGraphicFlags | 0x40000000,
      v82->nPri);
    v83 = (double)Display_tActiveMode.nWidth * 0.14000000059604645;
    ptStatusScreen->ptScoreHead2Text->bQGraphicFlags |= 0x80u;
    *(_QWORD *)igi2_frame.v183 = (__int64)(v83 + igi2_frame.v184);
    ptStatusScreen->ptScoreHead2Text->vX = (float)*(int *)igi2_frame.v183;
    ptStatusScreen->ptScoreHead2Text->vY = igi2_frame.v175;
    v84 = ptStatusScreen->ptScoreHead2Text;
    QTilemap_Register(
      v84->ptQTilemap,
      v84->vX,
      v84->vY,
      v84->vR,
      v84->vG,
      v84->vB,
      v84->vA,
      v84->vZ,
      v84->bQGraphicFlags | 0x40000000,
      v84->nPri);
    v85 = (double)Display_tActiveMode.nWidth * 0.25;
    ptStatusScreen->ptScoreHead3Text->bQGraphicFlags |= 0x80u;
    *(_QWORD *)igi2_frame.v183 = (__int64)(v85 + igi2_frame.v184);
    ptStatusScreen->ptScoreHead3Text->vX = (float)*(int *)igi2_frame.v183;
    ptStatusScreen->ptScoreHead3Text->vY = igi2_frame.v175;
    v86 = ptStatusScreen->ptScoreHead3Text;
    QTilemap_Register(
      v86->ptQTilemap,
      v86->vX,
      v86->vY,
      v86->vR,
      v86->vG,
      v86->vB,
      v86->vA,
      v86->vZ,
      v86->bQGraphicFlags | 0x40000000,
      v86->nPri);
    v87 = (double)Display_tActiveMode.nWidth * 0.019999999552965164;
    ptStatusScreen->ptScoreHead4Text->bQGraphicFlags |= 0x80u;
    *(_QWORD *)igi2_frame.v183 = (__int64)(v87 + igi2_frame.v184);
    ptStatusScreen->ptScoreHead4Text->vX = (float)*(int *)igi2_frame.v183;
    ptStatusScreen->ptScoreHead4Text->vY = igi2_frame.v175;
    v88 = ptStatusScreen->ptScoreHead4Text;
    QTilemap_Register(
      v88->ptQTilemap,
      v88->vX,
      v88->vY,
      v88->vR,
      v88->vG,
      v88->vB,
      v88->vA,
      v88->vZ,
      v88->bQGraphicFlags | 0x40000000,
      v88->nPri);
    ptQTilemap = ptStatusScreen->ptScoreHead1Text->ptQTilemap;
    v90 = ptQTilemap->ptQSprite->atQAnimframe[ptQTilemap->ptQSprite->nQAnimframes].nHeight;
    v91 = (double)(ptQTilemap->nHeight * v90) + igi2_frame.v181;
    v92 = ptQTilemap->nHeight;
    v93 = ptStatusScreen->nScoreboardNumPlayers;
    igi2_frame.v189 = 0;
    igi2_frame.v182 = v91 + (double)(v92 * v90);
    if ( v93 > 0 )
    {
      LODWORD(igi2_frame.v186) = ptStatusScreen->atTeam2ScoreText;
      for ( igi2_frame.j = ptStatusScreen->aptScoreClient; ; ++igi2_frame.j )
      {
        v94 = *igi2_frame.j;
        v95 = (*igi2_frame.j)->eTeam == 1;
        v96 = igi2_frame.v186;
        v97 = *(_DWORD *)((*igi2_frame.j)->tReceiveTimeBuffer.nCounter + 8);
        igi2_frame.v185 = *igi2_frame.j;
        if ( v95 )
          break;
LABEL_94:
        v67 = ++igi2_frame.v189 < ptStatusScreen->nScoreboardNumPlayers;
        if ( !v67 )
          return;
      }
      v98 = *(_BYTE *)(v97 + 1180);
      LODWORD(igi2_frame.v186) += 20;
      if ( v98 )
      {
        _snprintf(igi2_frame.v183, 7u, "S [%d]", v94->eNetworkID);
      }
      else
      {
        v99 = Weapon_GetWeaponTypeItemFromWeaponType(*(struct QTask_s **)(v97 + 1320), "WEAPON_ID_C4BOMB");
        if ( v99 && v99->isActive && igi2_frame.v191->eTeam == NetMission_eAttackingTeam )
          _snprintf(igi2_frame.v183, 7u, "B [%d]", v94->eNetworkID);
        else
          _snprintf(igi2_frame.v183, 7u, "  [%d]", v94->eNetworkID);
      }
      if ( v94->eNetworkID == igi2_frame.eNetworkID )
      {
        *(_DWORD *)(*(_DWORD *)(LODWORD(v96) + 12) + 20) = 1112329421;
        *(_DWORD *)(*(_DWORD *)(LODWORD(v96) + 12) + 24) = 1117362586;
        *(_DWORD *)(*(_DWORD *)(LODWORD(v96) + 12) + 28) = 1124073472;
        *(_DWORD *)(*(_DWORD *)LODWORD(v96) + 20) = 1112329421;
        *(_DWORD *)(*(_DWORD *)LODWORD(v96) + 24) = 1117362586;
        *(_DWORD *)(*(_DWORD *)LODWORD(v96) + 28) = 1124073472;
        *(_DWORD *)(*(_DWORD *)(LODWORD(v96) + 4) + 20) = 1112329421;
        *(_DWORD *)(*(_DWORD *)(LODWORD(v96) + 4) + 24) = 1117362586;
        *(_DWORD *)(*(_DWORD *)(LODWORD(v96) + 4) + 28) = 1124073472;
        *(_DWORD *)(*(_DWORD *)(LODWORD(v96) + 8) + 20) = 1112329421;
        *(_DWORD *)(*(_DWORD *)(LODWORD(v96) + 8) + 24) = 1117362586;
        *(_DWORD *)(*(_DWORD *)(LODWORD(v96) + 8) + 28) = 1124073472;
        *(_DWORD *)(*(_DWORD *)(LODWORD(v96) + 16) + 20) = 1112329421;
        *(_DWORD *)(*(_DWORD *)(LODWORD(v96) + 16) + 24) = 1117362586;
      }
      else
      {
        if ( *(_BYTE *)(v97 + 1180) )
        {
          *(_DWORD *)(*(_DWORD *)(LODWORD(v96) + 12) + 20) = 1124073472;
          *(_DWORD *)(*(_DWORD *)(LODWORD(v96) + 12) + 24) = 1112329421;
          *(_DWORD *)(*(_DWORD *)(LODWORD(v96) + 12) + 28) = 1108973978;
          *(_DWORD *)(*(_DWORD *)LODWORD(v96) + 20) = 1124073472;
          *(_DWORD *)(*(_DWORD *)LODWORD(v96) + 24) = 1112329421;
          *(_DWORD *)(*(_DWORD *)LODWORD(v96) + 28) = 1108973978;
          *(_DWORD *)(*(_DWORD *)(LODWORD(v96) + 4) + 20) = 1124073472;
          *(_DWORD *)(*(_DWORD *)(LODWORD(v96) + 4) + 24) = 1112329421;
          *(_DWORD *)(*(_DWORD *)(LODWORD(v96) + 4) + 28) = 1108973978;
          *(_DWORD *)(*(_DWORD *)(LODWORD(v96) + 8) + 20) = 1124073472;
          *(_DWORD *)(*(_DWORD *)(LODWORD(v96) + 8) + 24) = 1112329421;
          *(_DWORD *)(*(_DWORD *)(LODWORD(v96) + 8) + 28) = 1108973978;
          *(_DWORD *)(*(_DWORD *)(LODWORD(v96) + 16) + 20) = 1124073472;
          *(_DWORD *)(*(_DWORD *)(LODWORD(v96) + 16) + 24) = 1112329421;
          *(_DWORD *)(*(_DWORD *)(LODWORD(v96) + 16) + 28) = 1108973978;
LABEL_67:
          v100 = *(__int16 ***)(LODWORD(v96) + 12);
          v101 = *v100;
          igi2_frame.v166 = v100;
          memset(*((void **)*v100 + 3), 0, 2 * (*v100)[3]);
          memset(v101 + 8, 0, v101[3] * v101[2]);
          v102 = (struct QTilemap_s *)*v100;
          v103 = *(_DWORD *)(*((_DWORD *)*v100 + 2) + 12) + 16;
          v104 = igi2_frame.v183;
          if ( igi2_frame.v183[0] )
          {
            v105 = (char *)(*igi2_frame.v166 + 8) - igi2_frame.v183;
            v106 = igi2_frame.v183[0];
            do
            {
              v104[v105] = *(_BYTE *)(v106 + v103);
              v106 = *++v104;
            }
            while ( v106 );
          }
          QTilemap_UpdateGraphicWidth(v102, 0);
          v107 = **(_DWORD **)LODWORD(v96);
          igi2_frame.v167 = *(struct QTilemap_s ***)LODWORD(v96);
          memset(*(void **)(v107 + 12), 0, 2 * *(__int16 *)(v107 + 6));
          memset((void *)(v107 + 16), 0, *(__int16 *)(v107 + 6) * *(__int16 *)(v107 + 4));
          v108 = *igi2_frame.v167;
          v109 = igi2_frame.v185->zPlayerName[0];
          zPlayerName = igi2_frame.v185->zPlayerName;
          anID = (int)(*igi2_frame.v167)->ptQSprite->ptQTilemap->anID;
          if ( v109 )
          {
            v112 = (unsigned __int8 *)((*igi2_frame.v167)->anID - (unsigned __int8 *)zPlayerName);
            do
            {
              v112[(_DWORD)zPlayerName] = *(_BYTE *)(v109 + anID);
              v109 = *++zPlayerName;
            }
            while ( v109 );
          }
          QTilemap_UpdateGraphicWidth(v108, 0);
          igi2_frame.v150 = *(float *)&igi2_frame.v185->tStats.nLostPacks;
          if ( StatusScreen_isShowNetStats )
            sprintf(
              igi2_frame.Buffer,
              "%d[%d][%d][%d]/%2.1f%s",
              igi2_frame.v185->tStats.nPing,
              igi2_frame.v185->tStats.vPacketLoss,
              igi2_frame.v185->tStats.nSentPacks,
              igi2_frame.v185->tStats.nReceivedPacks,
              igi2_frame.v150,
              "%");
          else
            sprintf(igi2_frame.Buffer, "%d/%2.1f%s", igi2_frame.v185->tStats.nPing, igi2_frame.v150, "%");
          v113 = *(__int16 ***)(LODWORD(v96) + 4);
          v114 = *v113;
          igi2_frame.v168 = v113;
          memset(*((void **)*v113 + 3), 0, 2 * (*v113)[3]);
          memset(v114 + 8, 0, v114[3] * v114[2]);
          v115 = (struct QTilemap_s *)*v113;
          v116 = *(_DWORD *)(*((_DWORD *)*v113 + 2) + 12) + 16;
          v117 = igi2_frame.Buffer;
          if ( igi2_frame.Buffer[0] )
          {
            v118 = (char *)(*igi2_frame.v168 + 8) - igi2_frame.Buffer;
            v119 = igi2_frame.Buffer[0];
            do
            {
              v117[v118] = *(_BYTE *)(v119 + v116);
              v119 = *++v117;
            }
            while ( v119 );
          }
          QTilemap_UpdateGraphicWidth(v115, 0);
          sprintf(igi2_frame.Buffer, "%d/%d", igi2_frame.v185->nPoints, *(_DWORD *)&igi2_frame.v185->isTalk);
          v120 = *(__int16 ***)(LODWORD(v96) + 8);
          v121 = *v120;
          igi2_frame.v169 = v120;
          memset(*((void **)*v120 + 3), 0, 2 * (*v120)[3]);
          memset(v121 + 8, 0, v121[3] * v121[2]);
          v122 = (struct QTilemap_s *)*v120;
          v123 = *(_DWORD *)(*((_DWORD *)*v120 + 2) + 12) + 16;
          v124 = igi2_frame.Buffer;
          if ( igi2_frame.Buffer[0] )
          {
            v125 = (char *)(*igi2_frame.v169 + 8) - igi2_frame.Buffer;
            v126 = igi2_frame.Buffer[0];
            do
            {
              v124[v125] = *(_BYTE *)(v126 + v123);
              v126 = *++v124;
            }
            while ( v126 );
          }
          QTilemap_UpdateGraphicWidth(v122, 0);
          sprintf(igi2_frame.Buffer, (char *const)&g_ptNetManager.tReceiveCounters.tCounters[9].nBytes, igi2_frame.v185->nTalkOffset);
          v127 = *(__int16 ***)(LODWORD(v96) + 16);
          v128 = *v127;
          igi2_frame.v170 = v127;
          memset(*((void **)*v127 + 3), 0, 2 * (*v127)[3]);
          memset(v128 + 8, 0, v128[3] * v128[2]);
          v129 = (struct QTilemap_s *)*v127;
          v130 = *(_DWORD *)(*((_DWORD *)*v127 + 2) + 12) + 16;
          v131 = igi2_frame.Buffer;
          if ( igi2_frame.Buffer[0] )
          {
            v132 = (char *)(*igi2_frame.v170 + 8) - igi2_frame.Buffer;
            v133 = igi2_frame.Buffer[0];
            do
            {
              v131[v132] = *(_BYTE *)(v133 + v130);
              v133 = *++v131;
            }
            while ( v133 );
          }
          QTilemap_UpdateGraphicWidth(v129, 0);
          v134 = *(_DWORD *)(LODWORD(v96) + 12);
          v135 = igi2_frame.v184 - (double)Display_tActiveMode.nWidth * 0.30000001192092896;
          igi2_frame.v188 = v135;
          *(float *)(v134 + 4) = (float)(int)(__int64)v135;
          igi2_frame.v176 = (float)(__int64)igi2_frame.v182;
          *(float *)(*(_DWORD *)(LODWORD(v96) + 12) + 8) = igi2_frame.v176;
          v136 = *(_DWORD *)(LODWORD(v96) + 12);
          QTilemap_Register(
            *(struct QTilemap_s **)v136,
            *(float *)(v136 + 4),
            *(float *)(v136 + 8),
            *(float *)(v136 + 20),
            *(float *)(v136 + 24),
            *(float *)(v136 + 28),
            *(float *)(v136 + 16),
            *(float *)(v136 + 12),
            *(_DWORD *)(v136 + 36) | 0x40000000,
            *(_DWORD *)(v136 + 32));
          v137 = *(int **)(LODWORD(v96) + 12);
          v138 = *v137;
          v139 = *(__int16 *)(*v137 + 6);
          v140 = 0.0;
          *(float *)&igi2_frame.nWidth = 0.0;
          if ( v139 > 0 )
          {
            v141 = *(__int16 **)(v138 + 12);
            do
            {
              if ( *v141 > SLODWORD(v140) )
                LODWORD(v140) = *v141;
              ++v141;
              --v139;
            }
            while ( v139 );
            *(float *)&igi2_frame.nWidth = v140;
          }
          *(float *)(*(_DWORD *)LODWORD(v96) + 4) = (float)(int)(__int64)((double)igi2_frame.nWidth + igi2_frame.v188 + 20.0);
          *(float *)(*(_DWORD *)LODWORD(v96) + 8) = igi2_frame.v176;
          v142 = *(float **)LODWORD(v96);
          QTilemap_Register(
            **(struct QTilemap_s ***)LODWORD(v96),
            v142[1],
            v142[2],
            v142[5],
            v142[6],
            v142[7],
            v142[4],
            v142[3],
            *(_DWORD *)(*(_DWORD *)LODWORD(v96) + 36) | 0x40000000,
            *(_DWORD *)(*(_DWORD *)LODWORD(v96) + 32));
          if ( igi2_frame.v185->nTalkOffset > 0 )
          {
            v143 = (double)Display_tActiveMode.nWidth * 0.019999999552965164;
            *(_DWORD *)(*(_DWORD *)(LODWORD(v96) + 16) + 36) |= 0x80u;
            *(float *)(*(_DWORD *)(LODWORD(v96) + 16) + 4) = (float)(int)(__int64)(v143 + igi2_frame.v184);
            *(float *)(*(_DWORD *)(LODWORD(v96) + 16) + 8) = igi2_frame.v176;
            v144 = *(_DWORD *)(LODWORD(v96) + 16);
            QTilemap_Register(
              *(struct QTilemap_s **)v144,
              *(float *)(v144 + 4),
              *(float *)(v144 + 8),
              *(float *)(v144 + 20),
              *(float *)(v144 + 24),
              *(float *)(v144 + 28),
              *(float *)(v144 + 16),
              *(float *)(v144 + 12),
              *(_DWORD *)(v144 + 36) | 0x40000000,
              *(_DWORD *)(v144 + 32));
          }
          v145 = (double)Display_tActiveMode.nWidth * 0.14000000059604645;
          *(_DWORD *)(*(_DWORD *)(LODWORD(v96) + 8) + 36) |= 0x80u;
          *(float *)(*(_DWORD *)(LODWORD(v96) + 8) + 4) = (float)(int)(__int64)(v145 + igi2_frame.v184);
          *(float *)(*(_DWORD *)(LODWORD(v96) + 8) + 8) = igi2_frame.v176;
          v146 = *(_DWORD *)(LODWORD(v96) + 8);
          QTilemap_Register(
            *(struct QTilemap_s **)v146,
            *(float *)(v146 + 4),
            *(float *)(v146 + 8),
            *(float *)(v146 + 20),
            *(float *)(v146 + 24),
            *(float *)(v146 + 28),
            *(float *)(v146 + 16),
            *(float *)(v146 + 12),
            *(_DWORD *)(v146 + 36) | 0x40000000,
            *(_DWORD *)(v146 + 32));
          v147 = (double)Display_tActiveMode.nWidth * 0.25;
          *(_DWORD *)(*(_DWORD *)(LODWORD(v96) + 4) + 36) |= 0x80u;
          *(float *)(*(_DWORD *)(LODWORD(v96) + 4) + 4) = (float)(int)(__int64)(v147 + igi2_frame.v184);
          *(float *)(*(_DWORD *)(LODWORD(v96) + 4) + 8) = igi2_frame.v176;
          v148 = *(_DWORD *)(LODWORD(v96) + 4);
          QTilemap_Register(
            *(struct QTilemap_s **)v148,
            *(float *)(v148 + 4),
            *(float *)(v148 + 8),
            *(float *)(v148 + 20),
            *(float *)(v148 + 24),
            *(float *)(v148 + 28),
            *(float *)(v148 + 16),
            *(float *)(v148 + 12),
            *(_DWORD *)(v148 + 36) | 0x40000000,
            *(_DWORD *)(v148 + 32));
          igi2_frame.v182 = (double)(ptStatusScreen->ptScoreHead2Text->ptQTilemap->nHeight
                        * ptStatusScreen->ptScoreHead2Text->ptQTilemap->ptQSprite->atQAnimframe[ptStatusScreen->ptScoreHead2Text->ptQTilemap->ptQSprite->nQAnimframes].nHeight)
               + igi2_frame.v182
               + 8.0;
          goto LABEL_94;
        }
        *(_DWORD *)(*(_DWORD *)(LODWORD(v96) + 12) + 20) = 1124073472;
        *(_DWORD *)(*(_DWORD *)(LODWORD(v96) + 12) + 24) = 1124073472;
        *(_DWORD *)(*(_DWORD *)(LODWORD(v96) + 12) + 28) = 1124073472;
        *(_DWORD *)(*(_DWORD *)LODWORD(v96) + 20) = 1124073472;
        *(_DWORD *)(*(_DWORD *)LODWORD(v96) + 24) = 1124073472;
        *(_DWORD *)(*(_DWORD *)LODWORD(v96) + 28) = 1124073472;
        *(_DWORD *)(*(_DWORD *)(LODWORD(v96) + 4) + 20) = 1124073472;
        *(_DWORD *)(*(_DWORD *)(LODWORD(v96) + 4) + 24) = 1124073472;
        *(_DWORD *)(*(_DWORD *)(LODWORD(v96) + 4) + 28) = 1124073472;
        *(_DWORD *)(*(_DWORD *)(LODWORD(v96) + 8) + 20) = 1124073472;
        *(_DWORD *)(*(_DWORD *)(LODWORD(v96) + 8) + 24) = 1124073472;
        *(_DWORD *)(*(_DWORD *)(LODWORD(v96) + 8) + 28) = 1124073472;
        *(_DWORD *)(*(_DWORD *)(LODWORD(v96) + 16) + 20) = 1124073472;
        *(_DWORD *)(*(_DWORD *)(LODWORD(v96) + 16) + 24) = 1124073472;
      }
      *(_DWORD *)(*(_DWORD *)(LODWORD(v96) + 16) + 28) = 1124073472;
      goto LABEL_67;
    }
  }
}

// source: j/0/screens/statusscreen/statusscreen.c:1557  [anchor-callee]
char *__cdecl StatusScreen_DrawLocator(
        struct StatusScreen_t *ptStatusScreen,
        float x,
        float y,
        float z,
        float alpha,
        float r,
        float g,
        float b,
        char *zText)
{
  double v9; // st7
  struct StaticTilemap_s *ptMPRemoteText; // eax
  struct StaticTilemap_s *v12; // edi
  char *result; // eax
  float xa = *(float *)&y; // [esp+1Ch] [ebp+8h] ARGSLOT

  v9 = (double)Display_tActiveMode.nWidth * x;
  xa = (double)Display_tActiveMode.nHeight * y;
  Text_SetString(ptStatusScreen->ptMPRemoteText, zText);
  ptStatusScreen->ptMPRemoteText->vX = (float)(int)(__int64)v9;
  ptMPRemoteText = ptStatusScreen->ptMPRemoteText;
  ptMPRemoteText->vY = (float)(int)(__int64)(xa
                                           - (double)(ptMPRemoteText->ptQTilemap->nHeight
                                                    * ptMPRemoteText->ptQTilemap->ptQSprite->atQAnimframe[ptMPRemoteText->ptQTilemap->ptQSprite->nQAnimframes].nHeight));
  ptStatusScreen->ptMPRemoteText->vR = r;
  ptStatusScreen->ptMPRemoteText->vG = g;
  ptStatusScreen->ptMPRemoteText->vB = b;
  ptStatusScreen->ptMPRemoteText->bQGraphicFlags |= 0x40000u;
  ptStatusScreen->ptMPRemoteText->vZ = 0.0;
  ptStatusScreen->ptMPRemoteText->bQGraphicFlags |= 0x80000u;
  ptStatusScreen->ptMPRemoteText->vA = alpha;
  v12 = ptStatusScreen->ptMPRemoteText;
  QTilemap_Register(
    v12->ptQTilemap,
    v12->vX,
    v12->vY,
    v12->vR,
    v12->vG,
    v12->vB,
    v12->vA,
    v12->vZ,
    v12->bQGraphicFlags | 0x40000000,
    v12->nPri);
  return result;
}

// source: j/0/screens/statusscreen/statusscreen.c:1647  [anchor-callee]
void __cdecl StatusScreen_DrawRadarMark(
        struct StatusScreen_t *ptStatusScreen,
        struct real64x3_t *ptPos,
        struct real32x3_t *ptRGB,
        float vAlphaChannel,
        int nPri)
{
  #pragma pack(push, 1)
  union
  {
    struct { float vX; };
    struct { char igi2_o1[4]; float vY; };
    struct { char igi2_o2[8]; float vWidth; };
    struct { char igi2_o3[12]; float vHeight; };
    struct { char igi2_o4[56]; int pvBeta; };
    struct { char igi2_o5[60]; float pvAlpha; };
    struct { char igi2_o6[64]; float ptSource; };
    struct { char igi2_o7[68]; double ptSource_4[3]; };
    struct { char igi2_o8[92]; struct real32x9_t ptSource_28; };
    char igi2_extent[132];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  double v5; // st7
  struct QTask_s **p_ptTail; // esi
  double v7; // st7
  long double v8; // st7
  long double v9; // st7
  double v10; // st7
  long double v11; // st6
  long double v12; // st3
  long double v13; // st4
  double nHeight; // st5
  float ptStatusScreena = *(float *)&ptStatusScreen; // [esp+88h] [ebp+4h] ARGSLOT
  struct real32x3_t v25; // 0:^10.12

  v5 = ptPos->vX - *(double *)&HumanPlayer_ptQTask[1].ptNext;
  *(float *)&igi2_frame.pvBeta = 0.0;
  igi2_frame.ptSource_4[0] = v5;
  igi2_frame.ptSource_4[1] = ptPos->vY - *(double *)&HumanPlayer_ptQTask[1].tQTaskChildren.ptHead;
  igi2_frame.ptSource_4[2] = ptPos->vZ - *(double *)&HumanPlayer_ptQTask[1].tQTaskChildren.ptTail;
  if ( NetManager_eMode == NETMANAGER_MODE_SPAWN )
    p_ptTail = &SpawnArea_ptActive[4].tQTaskChildren.ptTail;
  else
    p_ptTail = &HumanPlayer_ptQTask[3].ptPrev;
  qmemcpy(&igi2_frame.ptSource_28, p_ptTail, sizeof(igi2_frame.ptSource_28));
  Real32x9_GetAngles(&igi2_frame.ptSource_28, &igi2_frame.ptSource, &igi2_frame.pvAlpha, (float *)&igi2_frame.pvBeta);
  if ( NetManager_eMode == NETMANAGER_MODE_SPAWN )
    v7 = NetManager_vSpawnCamOffsetGamma + *(float *)&igi2_frame.pvBeta;
  else
    v7 = *(float *)&igi2_frame.pvBeta;
  v8 = -v7;
  *(float *)&igi2_frame.pvBeta = sin(v8);
  v9 = cos(v8);
  igi2_frame.ptSource_28.tX.vY = -*(float *)&igi2_frame.pvBeta;
  *(double *)&igi2_frame.ptSource_28.tX.vX = v9 * igi2_frame.ptSource_4[0] + igi2_frame.ptSource_28.tX.vY * igi2_frame.ptSource_4[1] + igi2_frame.ptSource_4[2] * 0.0;
  *(double *)&igi2_frame.ptSource_28.tX.vZ = v9 * igi2_frame.ptSource_4[1] + *(float *)&igi2_frame.pvBeta * igi2_frame.ptSource_4[0] + igi2_frame.ptSource_4[2] * 0.0;
  *(double *)&igi2_frame.ptSource_28.tY.vY = (igi2_frame.ptSource_4[1] + igi2_frame.ptSource_4[0]) * 0.0 + igi2_frame.ptSource_4[2];
  qmemcpy(igi2_frame.ptSource_4, &igi2_frame.ptSource_28, sizeof(igi2_frame.ptSource_4));
  v10 = *(double *)&igi2_frame.ptSource_28.tX.vX * (1.0 / ptStatusScreen->vRadarRange);
  igi2_frame.ptSource_4[1] = 1.0 / ptStatusScreen->vRadarRange * igi2_frame.ptSource_4[1];
  v11 = -igi2_frame.ptSource_4[1];
  v12 = sqrt(v10 * v10 + -igi2_frame.ptSource_4[1] * -igi2_frame.ptSource_4[1]);
  if ( v12 > 1.0 )
  {
    v13 = 1.0 / v12;
    v10 = v10 * v13;
    v11 = v11 * v13;
  }
  nHeight = (double)Display_tActiveMode.nHeight;
  ptStatusScreena = 0.0013020833721384406 * nHeight;
  v25 = *ptRGB;
  igi2_frame.vHeight = (float)(Display_tActiveMode.nHeight / 240);
  igi2_frame.pvBeta = Display_tActiveMode.nWidth / 320;
  igi2_frame.vWidth = (float)(Display_tActiveMode.nWidth / 320);
  igi2_frame.vY = ptStatusScreena * v11 * 59.0 + nHeight * 0.11500000208616257;
  igi2_frame.vX = ptStatusScreena * v10 * 59.0 + (double)Display_tActiveMode.nWidth * 0.9100000262260437;
  QSprite_RegisterBlankAZ(igi2_frame.vX, igi2_frame.vY, igi2_frame.vWidth, igi2_frame.vHeight, v25.vX, v25.vY, v25.vZ, vAlphaChannel, 0.0, 0x40000u, nPri);
}

// source: j/0/screens/statusscreen/statusscreen.c:1729  [anchor-callee]
void __cdecl StatusScreen_DrawRadarGfx(struct StatusScreen_t *ptStatusScreen)
{
  double nHeight; // st7
  double v2; // st7
  double v3; // st6
  double v4; // st7
  double v5; // st7
  double v6; // st6
  float v7; // [esp+0h] [ebp-58h]
  float v8; // [esp+4h] [ebp-54h]
  float v9; // [esp+4h] [ebp-54h]
  float v10; // [esp+4h] [ebp-54h]
  float vY3; // [esp+8h] [ebp-50h]
  float vY3a; // [esp+8h] [ebp-50h]
  float vY3b; // [esp+8h] [ebp-50h]
  float vX4; // [esp+Ch] [ebp-4Ch]
  float vX4a; // [esp+Ch] [ebp-4Ch]
  float vX4b; // [esp+Ch] [ebp-4Ch]
  float vY1; // [esp+10h] [ebp-48h]
  float vY1a; // [esp+10h] [ebp-48h]
  float vY1b; // [esp+10h] [ebp-48h]
  float vY1c; // [esp+10h] [ebp-48h]
  float vX2; // [esp+14h] [ebp-44h]
  float vX2a; // [esp+14h] [ebp-44h]
  float vX2b; // [esp+14h] [ebp-44h]
  float ptQSprite; // [esp+18h] [ebp-40h]
  float ptQSpritea; // [esp+18h] [ebp-40h]
  float ptQSpriteb; // [esp+18h] [ebp-40h]
  float vX1; // [esp+1Ch] [ebp-3Ch]
  float vX1a; // [esp+1Ch] [ebp-3Ch]
  float vX1b; // [esp+1Ch] [ebp-3Ch]
  float vX1c; // [esp+1Ch] [ebp-3Ch]
  float v31; // [esp+20h] [ebp-38h]
  float v32; // [esp+24h] [ebp-34h]
  float vY2; // [esp+28h] [ebp-30h]
  float vY2a; // [esp+28h] [ebp-30h]
  float vY2b; // [esp+28h] [ebp-30h]
  float vX3; // [esp+2Ch] [ebp-2Ch]
  float vX3a; // [esp+2Ch] [ebp-2Ch]
  float v38; // [esp+30h] [ebp-28h]
  float v39; // [esp+34h] [ebp-24h]
  float v40; // [esp+38h] [ebp-20h]
  float v41; // [esp+3Ch] [ebp-1Ch]
  float v42; // [esp+40h] [ebp-18h]
  float v43; // [esp+44h] [ebp-14h]
  float v44; // [esp+48h] [ebp-10h]
  float v45; // [esp+4Ch] [ebp-Ch]
  float v46; // [esp+50h] [ebp-8h]

  v31 = (double)Display_tActiveMode.nWidth * 0.9100000262260437 + 1.0;
  nHeight = (double)Display_tActiveMode.nHeight;
  v32 = 0.11500000208616257 * nHeight + 1.0;
  v2 = nHeight * 0.0013020833721384406;
  v8 = v2;
  v3 = v2 * -64.0;
  vX1 = v3;
  vY1 = v8 * 64.0;
  vX2 = v3;
  vY2 = v3;
  vX4 = vY1;
  ptQSprite = v3 + v31;
  vX1a = vX1 + v32;
  vY1a = vY1 + v31;
  vX2a = vX2 + v32;
  vY2a = vY2 + v31;
  vX3 = vX4 + v32;
  vY3 = vX4 + v31;
  QSprite_Register4(
    &ComputerMenu_tComputerMenuResource.tQSpriteHUD1,
    ptQSprite,
    vX1a,
    vY1a,
    vX2a,
    vY2a,
    vX3,
    vY3,
    vX3,
    128.0,
    128.0,
    128.0,
    0,
    (unsigned int)&MTP_atLODVirModel[49].atBoneVertexRefs[17].atVertexRefs[120],
    5);
  v4 = (double)Display_tActiveMode.nHeight * 0.0013020833721384406;
  ptQSpritea = -76.0 * v4;
  vX1b = v4 * -75.5;
  v9 = v4 * 77.0;
  vY1b = v9;
  vY3a = v9;
  v5 = v4 * 77.5;
  vX4a = v5;
  v10 = sin(*(float *)&HumanPlayer_ptQTask[34].tQTaskChildren.ptHead);
  v7 = cos(*(float *)&HumanPlayer_ptQTask[34].tQTaskChildren.ptHead);
  v6 = -v10;
  v46 = v6;
  v38 = v6 * vX1b + v7 * ptQSpritea;
  v39 = v7 * vX1b + v10 * ptQSpritea;
  v40 = v46 * vX1b + v7 * vY1b;
  v41 = v7 * vX1b + v10 * vY1b;
  v42 = v46 * v5 + v7 * ptQSpritea;
  v43 = v7 * v5 + v10 * ptQSpritea;
  v44 = v46 * vX4a + v7 * vY3a;
  v45 = v7 * vX4a + v10 * vY3a;
  ptQSpriteb = v38 + v31;
  vX1c = v39 + v32;
  vY1c = v40 + v31;
  vX2b = v41 + v32;
  vY2b = v42 + v31;
  vX3a = v43 + v32;
  vY3b = v44 + v31;
  vX4b = v45 + v32;
  QSprite_Register4(
    &ComputerMenu_tComputerMenuResource.tQSpriteHUD2,
    ptQSpriteb,
    vX1c,
    vY1c,
    vX2b,
    vY2b,
    vX3a,
    vY3b,
    vX4b,
    128.0,
    128.0,
    128.0,
    0,
    (unsigned int)&MTP_atLODVirModel[49].atBoneVertexRefs[17].atVertexRefs[120],
    0);
}

// source: j/0/screens/statusscreen/statusscreen.c:1813  [anchor-callee]
void __cdecl StatusScreen_DrawRadar(struct StatusScreen_t *ptStatusScreen)
{
  #pragma pack(push, 1)
  union
  {
    struct { int nObjective; };
    struct { char igi2_o1[4]; struct Client_s *ptLocalClient; };
    struct { char igi2_o2[8]; struct real32x3_t tRGB; };
    struct { char igi2_o3[20]; struct real64x3_t tPriPos; };
    struct { char igi2_o4[44]; struct real64x3_t tSecPos; };
    char igi2_extent[68];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct Flow_t *v1; // ebx
  struct QTask_s *v2; // esi
  struct Client_s *ClientFromNetworkID; // edi
  struct QTask_s *ptBombComputerHighlightQTask; // ecx
  int v5; // et2
  struct QTask_s *v6; // eax
  struct QTask_s *ptHead; // eax
  unsigned __int16 eQTaskType; // cx
  long double v9; // st6
  unsigned __int16 v10; // bx
  unsigned __int16 v11; // di
  int v12; // esi
  struct QTask_s *FirstChildOfType; // eax
  struct QTask_s *i; // esi
  struct QTask_s *eTeam; // eax
  int EnumObjectivePos; // esi

  v1 = Flow_ptFlow;
  v2 = nullptr;
  ClientFromNetworkID = NetManager_GetClientFromNetworkID((int)Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle);
  igi2_frame.ptLocalClient = ClientFromNetworkID;
  if ( NetMission_ptNetMission )
  {
    ptBombComputerHighlightQTask = NetMission_ptNetMission->ptBombComputerHighlightQTask;
    if ( ptBombComputerHighlightQTask )
    {
      if ( ClientFromNetworkID->eTeam == NetMission_eAttackingTeam && NetManager_eMode == NETMANAGER_MODE_PLAY )
      {
        v5 = v1->nTicks % 30;
        igi2_frame.tRGB.vX = 128.0;
        igi2_frame.tRGB.vY = (cos((double)v5 * 0.20943951606750488) + 1.0) * 0.5 * 80.0;
        igi2_frame.tRGB.vZ = igi2_frame.tRGB.vY;
        StatusScreen_DrawRadarMark(ptStatusScreen, (struct real64x3_t *)&ptBombComputerHighlightQTask[1], &igi2_frame.tRGB, 1.0, 1);
      }
    }
  }
  while ( 1 )
  {
    v6 = v2
       ? QTask_GetNextSiblingOfType(v2, Client_eQTaskType)
       : QTask_GetFirstChildOfType(Flow_ptFlow->ptNetManagerQTask, Client_eQTaskType);
    v2 = v6;
    if ( !v6 )
      break;
    if ( v6[1].tQTaskRefList.ptHead == (struct QReference_s *)ClientFromNetworkID->eTeam
      && v6[1].ptNext != Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle )
    {
      ptHead = v6[16].tQTaskChildren.ptHead->tQTaskChildren.ptHead;
      eQTaskType = ptHead->eQTaskType;
      igi2_frame.tRGB.vX = 128.0;
      igi2_frame.tRGB.vY = 128.0;
      igi2_frame.tRGB.vZ = 128.0;
      if ( eQTaskType != HumanRemote_eQTaskType )
        goto LABEL_16;
      if ( LOBYTE(ptHead[81].tQTaskRefList.ptTail) )
      {
        if ( *(int *)&ptHead[81].eQTaskType > 0 )
        {
          v9 = cos((double)*(int *)&ptHead[81].eQTaskType * 25.132741928100586 / (double)(int)ptHead[82].ptNext);
          igi2_frame.tRGB.vX = (1.0 - v9 * v9) * 128.0;
          igi2_frame.tRGB.vY = igi2_frame.tRGB.vX;
          igi2_frame.tRGB.vZ = igi2_frame.tRGB.vX;
        }
LABEL_16:
        StatusScreen_DrawRadarMark(ptStatusScreen, (struct real64x3_t *)&ptHead[1], &igi2_frame.tRGB, 1.0, 3);
      }
    }
  }
  if ( NetMission_eCurrentObjective > 0 )
  {
    v10 = NetObjective_eQTaskType;
    v11 = SpawnArea_eQTaskType;
    v12 = 1;
    igi2_frame.nObjective = 1;
    do
    {
      FirstChildOfType = QTask_GetFirstChildOfType(&NetMission_ptNetMission->tQTask, v10);
      if ( FirstChildOfType )
      {
        while ( FirstChildOfType[5].ptNext != (struct QTask_s *)v12 )
        {
          FirstChildOfType = QTask_GetNextSiblingOfType(FirstChildOfType, v10);
          if ( !FirstChildOfType )
            goto LABEL_30;
        }
        for ( i = QTask_GetFirstChildOfType(FirstChildOfType, v11); i; i = QTask_GetNextSiblingOfType(i, v11) )
        {
          eTeam = (struct QTask_s *)igi2_frame.ptLocalClient->eTeam;
          if ( i[6].tQTaskChildren.ptHead == eTeam
            && (eTeam == (struct QTask_s *)NetMission_eDefendingTeam || igi2_frame.nObjective <= NetMission_eCurrentObjective) )
          {
            igi2_frame.tRGB.vX = 128.0;
            igi2_frame.tRGB.vY = 128.0;
            igi2_frame.tRGB.vZ = 0.0;
            StatusScreen_DrawRadarMark(ptStatusScreen, (struct real64x3_t *)&i[2].tQTaskChildren, &igi2_frame.tRGB, 1.0, 4);
            v10 = NetObjective_eQTaskType;
            v11 = SpawnArea_eQTaskType;
          }
        }
        v12 = igi2_frame.nObjective;
      }
LABEL_30:
      igi2_frame.nObjective = ++v12;
    }
    while ( v12 <= 3 );
  }
  EnumObjectivePos = ComputerHilight_GetEnumObjectivePos(&igi2_frame.tPriPos, &igi2_frame.tSecPos, NetMission_eCurrentObjective);
  igi2_frame.tRGB.vX = 51.20000076293945;
  igi2_frame.tRGB.vY = 76.80000305175781;
  igi2_frame.tRGB.vZ = 128.0;
  if ( EnumObjectivePos >= 1 )
    StatusScreen_DrawRadarMark(ptStatusScreen, &igi2_frame.tPriPos, &igi2_frame.tRGB, 1.0, 2);
  if ( EnumObjectivePos == 2 )
    StatusScreen_DrawRadarMark(ptStatusScreen, &igi2_frame.tSecPos, &igi2_frame.tRGB, 1.0, 2);
  StatusScreen_DrawRadarGfx(ptStatusScreen);
}

// source: j/0/screens/statusscreen/statusscreen.c:1951  [anchor-mhash]
float __cdecl StatusScreen_GetCenterFade(float x, float y)
{
  double v2; // st7
  double v3; // st7
  float xa = *(float *)&x; // [esp+4h] [ebp+4h] ARGSLOT

  xa = x - 0.5;
  v2 = y - 0.5;
  if ( xa < 0.0 )
    xa = -xa;
  if ( v2 < 0.0 )
    v2 = -v2;
  if ( xa > v2 )
    v2 = xa;
  v3 = 1.0 - v2 * 3.0;
  if ( v3 <= 1.0 )
  {
    if ( v3 < 0.0 )
      return 0.0;
  }
  else
  {
    return 1.0;
  }
  return v3;
}

// source: j/0/screens/statusscreen/statusscreen.c:1984  [anchor-callee]
float __cdecl StatusScreen_GetFancyFade(int nTimer, int nInitTimer)
{
  double v2; // st7
  double v3; // st7

  v2 = 1.0 - (double)nTimer / (double)nInitTimer;
  if ( v2 < 0.8999999761581421 )
    return 1.0;
  v3 = 1.0 - (v2 - 0.8999999761581421) * 10.0;
  if ( v3 > 1.0 )
  {
    return 1.0;
  }
  else if ( v3 < 0.0 )
  {
    return 0.0;
  }
  return v3;
}

// source: j/0/screens/statusscreen/statusscreen.c:2262  [anchor-mhash]
void __cdecl StatusScreen_DrawBar(float x, float y, float yOffset, float vR, float vG, float vB)
{
  float vY1; // [esp+0h] [ebp-40h]
  float vY2; // [esp+Ch] [ebp-34h]
  float xa = *(float *)&x; // [esp+44h] [ebp+4h] ARGSLOT

  xa = (double)(Display_tActiveMode.nWidth - 303) + 10.0 + x;
  vY2 = 105.0 - yOffset;
  vY1 = 50.0 - y + 55.0 - yOffset;
  QSprite_RegisterLine(xa, vY1, 0.0, xa, vY2, 0.0, vR, vG, vB, vR, vG, vB, 1.0, 1.0, 0, 0);
}

// source: j/0/screens/statusscreen/statusscreen.c:2292  [anchor-caller]
void __cdecl StatusScreen_DrawLowLevelStats()
{
  #pragma pack(push, 1)
  union
  {
    struct { float vX1; };
    struct { float vX1a; };
    struct { float vX1b; };
    struct { float vX1c; };
    struct { float vX1d; };
    struct { char igi2_o5[4]; int v67; };
    struct { char igi2_o6[4]; float v68; };
    struct { char igi2_o7[12]; int vX2; };
    struct { char igi2_o8[12]; float vX2a; };
    struct { char igi2_o9[16]; float x; };
    struct { char igi2_o10[16]; float xa; };
    struct { char igi2_o11[20]; int v73; };
    struct { char igi2_o12[28]; int v74; };
    struct { char igi2_o13[32]; int v75; };
    struct { char igi2_o14[36]; DWORD v76; };
    struct { char igi2_o15[40]; int v77; };
    struct { char igi2_o16[44]; int v78; };
    struct { char igi2_o17[48]; char v79[12]; };
    struct { char igi2_o18[60]; char Buffer[260]; };
    char igi2_extent[320];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v0; // ebx
  int v1; // ebp
  DWORD PerformanceCounter; // eax
  double v3; // st7
  int v4; // ebx
  int v5; // esi
  double v6; // st7
  int v7; // eax
  int v8; // esi
  double v9; // st7
  int v10; // eax
  double v11; // st7
  double v12; // st7
  struct StaticTilemap_s *v13; // esi
  __int16 *ptQTilemap; // edx
  struct QTilemap_s *v15; // edi
  unsigned __int8 v16; // dl
  int anID; // eax
  char *v18; // ecx
  int v19; // ebp
  enum bool v20; // eax
  struct StaticTilemap_s *v21; // esi
  struct QTilemap_s *v22; // edx
  struct QTilemap_s *v23; // edi
  unsigned __int8 v24; // dl
  int v25; // ecx
  char *v26; // eax
  int v27; // ebp
  struct StaticTilemap_s *v28; // eax
  struct QTask_s *ptNetManagerQTask; // esi
  struct QTask_s *ptMiddle; // edi
  unsigned __int16 v31; // dx
  struct QTask_s *v32; // eax
  double v33; // st7
  int v34; // esi
  __int16 *v35; // edx
  struct QTilemap_s *v36; // edi
  unsigned __int8 v37; // dl
  int v38; // ecx
  char *v39; // eax
  int v40; // ebp
  double v41; // st7
  double v42; // st7
  struct QTask_s *v43; // eax
  double v44; // st7
  double v45; // st6
  struct StaticTilemap_s *v46; // esi
  __int16 *v47; // edx
  struct QTilemap_s *v48; // edi
  unsigned __int8 v49; // dl
  int v50; // eax
  char *v51; // ecx
  int v52; // ebp
  struct QTask_s *v53; // ecx
  double v54; // st7
  struct StaticTilemap_s *v55; // esi
  __int16 *v56; // edx
  struct QTilemap_s *v57; // edi
  unsigned __int8 v58; // dl
  int v59; // eax
  char *v60; // ecx
  int v61; // ebp

  v0 = Network_nSendStatIndex;
  igi2_frame.v77 = 1;
  igi2_frame.v78 = 1;
  v1 = 0;
  igi2_frame.v67 = Network_nReceiveStatIndex;
  igi2_frame.v75 = 0;
  if ( Timer_isPerformanceCounter )
    PerformanceCounter = Timer_GetPerformanceCounter();
  else
    PerformanceCounter = GetTickCount();
  v3 = (double)(Display_tActiveMode.nWidth - 303) + 10.0;
  igi2_frame.vX1d = v3;
  igi2_frame.v76 = PerformanceCounter - Timer_nStartTime;
  igi2_frame.vX2a = v3 + 260.0;
  QSprite_RegisterLine(igi2_frame.vX1d, 80.0, 0.0, igi2_frame.vX2a, 80.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 0, 0);
  QSprite_RegisterLine(igi2_frame.vX1d, 105.0, 0.0, igi2_frame.vX2a, 105.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 0, 0);
  v4 = v0 + 1;
  igi2_frame.v73 = v4;
  v5 = 200;
  do
  {
    if ( (int)(igi2_frame.v76 - Network_aSendStat[v4 % 200].nTime) >= 3000 )
    {
      igi2_frame.v77 = 0;
    }
    else
    {
      igi2_frame.x = (double)(int)(igi2_frame.v76 - Network_aSendStat[v4 % 200].nTime) * 0.08666666597127914;
      v6 = (double)Network_aSendStat[v4 % 200].nSize * 0.0555555559694767;
      igi2_frame.vX1 = v6;
      if ( v6 <= 50.0 )
      {
        v7 = 0;
      }
      else
      {
        v7 = 1;
        igi2_frame.vX1 = 50.0;
      }
      v1 += Network_aSendStat[v4 % 200].nSize;
      if ( Network_aSendStat[v4 % 200].eStatus )
      {
        StatusScreen_DrawBar(igi2_frame.x, igi2_frame.vX1, 0.0, 127.0, 0.0, 0.0);
      }
      else if ( v7 )
      {
        StatusScreen_DrawBar(igi2_frame.x, igi2_frame.vX1, 0.0, 0.0, 0.0, 127.0);
      }
      else
      {
        StatusScreen_DrawBar(igi2_frame.x, igi2_frame.vX1, 0.0, 127.0, 127.0, 0.0);
      }
    }
    ++v4;
    --v5;
  }
  while ( v5 );
  igi2_frame.v74 = v1;
  v8 = igi2_frame.v67 + 1;
  igi2_frame.vX2 = 200;
  do
  {
    if ( (int)(igi2_frame.v76 - Network_aReceiveStat[v8 % 200].nTime) >= 3000 )
    {
      igi2_frame.v78 = 0;
    }
    else
    {
      igi2_frame.xa = 260.0 - (double)(int)(igi2_frame.v76 - Network_aReceiveStat[v8 % 200].nTime) * 0.08666666597127914;
      v9 = (double)Network_aReceiveStat[v8 % 200].nSize * 0.0555555559694767;
      igi2_frame.vX1a = v9;
      if ( v9 <= 50.0 )
      {
        v10 = 0;
      }
      else
      {
        v10 = 1;
        igi2_frame.vX1a = 50.0;
      }
      igi2_frame.v75 += Network_aReceiveStat[v8 % 200].nSize;
      if ( Network_aReceiveStat[v8 % 200].eStatus )
      {
        StatusScreen_DrawBar(igi2_frame.xa, igi2_frame.vX1a, 25.0, 127.0, 0.0, 0.0);
      }
      else if ( v10 )
      {
        StatusScreen_DrawBar(igi2_frame.xa, igi2_frame.vX1a, 25.0, 0.0, 0.0, 127.0);
      }
      else
      {
        StatusScreen_DrawBar(igi2_frame.xa, igi2_frame.vX1a, 25.0, 127.0, 127.0, 0.0);
      }
    }
    ++v8;
    --igi2_frame.vX2;
  }
  while ( igi2_frame.vX2 );
  v11 = (double)igi2_frame.v75;
  if ( igi2_frame.v78 )
    v12 = v11 * 1000.0 / (double)(int)(igi2_frame.v76 - Network_aReceiveStat[(igi2_frame.v67 + 1) % 200].nTime);
  else
    v12 = v11 * 0.3333333432674408;
  _snprintf(igi2_frame.Buffer, 0xFFu, "%.1f kBps IN", v12 * 0.0009765625);
  v13 = StatusScreen_ptClientLowTrafficInText;
  StatusScreen_ptClientLowTrafficInText->vX = (float)(int)(__int64)((double)(Display_tActiveMode.nWidth - 303) + 15.0);
  v13->vY = 60.0;
  v13->vR = 127.0;
  v13->vG = 127.0;
  v13->vB = 127.0;
  ptQTilemap = (__int16 *)v13->ptQTilemap;
  memset(v13->ptQTilemap->anGraphicWidth, 0, 2 * v13->ptQTilemap->nHeight);
  memset(ptQTilemap + 8, 0, ptQTilemap[3] * ptQTilemap[2]);
  v15 = v13->ptQTilemap;
  v16 = igi2_frame.Buffer[0];
  anID = (int)v13->ptQTilemap->ptQSprite->ptQTilemap->anID;
  v18 = igi2_frame.Buffer;
  if ( igi2_frame.Buffer[0] )
  {
    v19 = v13->ptQTilemap->anID - (unsigned __int8 *)igi2_frame.Buffer;
    do
    {
      v18[v19] = *(_BYTE *)(v16 + anID);
      v16 = *++v18;
    }
    while ( v16 );
  }
  QTilemap_UpdateGraphicWidth(v15, 0);
  QTilemap_Register(
    v13->ptQTilemap,
    v13->vX,
    v13->vY,
    v13->vR,
    v13->vG,
    v13->vB,
    v13->vA,
    v13->vZ,
    v13->bQGraphicFlags | 0x40000000,
    v13->nPri);
  igi2_frame.vX1b = (double)(Display_tActiveMode.nWidth - 303) + 210.0;
  v20 = NetManager_PrintFPS(igi2_frame.Buffer);
  v21 = StatusScreen_ptClientFpsText;
  if ( v20 )
  {
    v22 = StatusScreen_ptClientFpsText->ptQTilemap;
    memset(
      StatusScreen_ptClientFpsText->ptQTilemap->anGraphicWidth,
      0,
      2 * StatusScreen_ptClientFpsText->ptQTilemap->nHeight);
    memset(v22->anID, 0, v22->nHeight * v22->nWidth);
    v23 = v21->ptQTilemap;
    v24 = igi2_frame.Buffer[0];
    v25 = (int)v21->ptQTilemap->ptQSprite->ptQTilemap->anID;
    v26 = igi2_frame.Buffer;
    if ( igi2_frame.Buffer[0] )
    {
      v27 = v21->ptQTilemap->anID - (unsigned __int8 *)igi2_frame.Buffer;
      do
      {
        v26[v27] = *(_BYTE *)(v24 + v25);
        v24 = *++v26;
      }
      while ( v24 );
    }
    QTilemap_UpdateGraphicWidth(v23, 0);
  }
  v21->vX = (float)(__int64)igi2_frame.vX1b;
  v21->vY = 60.0;
  QTilemap_Register(
    v21->ptQTilemap,
    v21->vX,
    60.0,
    v21->vR,
    v21->vG,
    v21->vB,
    v21->vA,
    v21->vZ,
    v21->bQGraphicFlags | 0x40000000,
    v21->nPri);
  v28 = StatusScreen_ptClientPingText;
  igi2_frame.v68 = (float)(int)(__int64)(igi2_frame.vX1b - 80.0);
  StatusScreen_ptClientPingText->vX = igi2_frame.v68;
  v28->vY = 60.0;
  QTilemap_Register(
    v28->ptQTilemap,
    v28->vX,
    60.0,
    v28->vR,
    v28->vG,
    v28->vB,
    v28->vA,
    v28->vZ,
    v28->bQGraphicFlags | 0x40000000,
    v28->nPri);
  ptNetManagerQTask = Flow_ptFlow->ptNetManagerQTask;
  ptMiddle = ptNetManagerQTask[6].tQTaskChildren.ptMiddle;
  v31 = Client_eQTaskType;
  v32 = nullptr;
  while ( 1 )
  {
    v32 = v32 ? QTask_GetNextSiblingOfType(v32, v31) : QTask_GetFirstChildOfType(ptNetManagerQTask, v31);
    if ( !v32 )
      break;
    if ( v32[1].ptNext == ptMiddle )
    {
      v33 = *(float *)&v32[7].ptNext;
      goto LABEL_47;
    }
  }
  v33 = 0.0;
LABEL_47:
  _snprintf(igi2_frame.v79, 0xAu, "%2.1f%s", v33, "%");
  v34 = dword_74C648;
  v35 = *(__int16 **)dword_74C648;
  memset(*(void **)(*(_DWORD *)dword_74C648 + 12), 0, 2 * *(__int16 *)(*(_DWORD *)dword_74C648 + 6));
  memset(v35 + 8, 0, v35[3] * v35[2]);
  v36 = *(struct QTilemap_s **)v34;
  v37 = igi2_frame.v79[0];
  v38 = *(_DWORD *)(*(_DWORD *)(*(_DWORD *)v34 + 8) + 12) + 16;
  v39 = igi2_frame.v79;
  if ( igi2_frame.v79[0] )
  {
    v40 = *(_DWORD *)v34 + 16 - (_DWORD)igi2_frame.v79;
    do
    {
      v39[v40] = *(_BYTE *)(v37 + v38);
      v37 = *++v39;
    }
    while ( v37 );
  }
  QTilemap_UpdateGraphicWidth(v36, 0);
  *(float *)(v34 + 4) = igi2_frame.v68;
  *(_DWORD *)(v34 + 8) = 1118437376;
  QTilemap_Register(
    *(struct QTilemap_s **)v34,
    *(float *)(v34 + 4),
    85.0,
    *(float *)(v34 + 20),
    *(float *)(v34 + 24),
    *(float *)(v34 + 28),
    *(float *)(v34 + 16),
    *(float *)(v34 + 12),
    *(_DWORD *)(v34 + 36) | 0x40000000,
    *(_DWORD *)(v34 + 32));
  v41 = (double)igi2_frame.v74;
  if ( igi2_frame.v77 )
    v42 = v41 * 1000.0 / (double)(int)(igi2_frame.v76 - Network_aSendStat[igi2_frame.v73 % 200].nTime);
  else
    v42 = v41 * 0.3333333432674408;
  v43 = Flow_ptFlow->ptNetManagerQTask;
  v44 = v42 * 0.0009765625;
  if ( v43 )
    v45 = *(float *)&v43[36].tQTaskChildren.ptHead;
  else
    v45 = 0.0;
  _snprintf(igi2_frame.Buffer, 0xFFu, "%.1f - %.1f kBps OUT", v44, v45);
  v46 = StatusScreen_ptClientLowTrafficOutText;
  igi2_frame.vX1c = (double)(Display_tActiveMode.nWidth - 303) + 15.0;
  StatusScreen_ptClientLowTrafficOutText->vX = (float)(__int64)igi2_frame.vX1c;
  v46->vY = 85.0;
  v46->vR = 127.0;
  v46->vG = 127.0;
  v46->vB = 127.0;
  v47 = (__int16 *)v46->ptQTilemap;
  memset(v46->ptQTilemap->anGraphicWidth, 0, 2 * v46->ptQTilemap->nHeight);
  memset(v47 + 8, 0, v47[3] * v47[2]);
  v48 = v46->ptQTilemap;
  v49 = igi2_frame.Buffer[0];
  v50 = (int)v46->ptQTilemap->ptQSprite->ptQTilemap->anID;
  v51 = igi2_frame.Buffer;
  if ( igi2_frame.Buffer[0] )
  {
    v52 = v46->ptQTilemap->anID - (unsigned __int8 *)igi2_frame.Buffer;
    do
    {
      v51[v52] = *(_BYTE *)(v49 + v50);
      v49 = *++v51;
    }
    while ( v49 );
  }
  QTilemap_UpdateGraphicWidth(v48, 0);
  QTilemap_Register(
    v46->ptQTilemap,
    v46->vX,
    v46->vY,
    v46->vR,
    v46->vG,
    v46->vB,
    v46->vA,
    v46->vZ,
    v46->bQGraphicFlags | 0x40000000,
    v46->nPri);
  v53 = Flow_ptFlow->ptNetManagerQTask;
  if ( !v53 || !v53[1].ptNext )
    goto LABEL_65;
  v54 = (double)(int)pValue_84b73b4 * 0.009999999776482582;
  if ( v54 <= 0.009999999776482582 )
    v54 = 0.009999999776482582;
  if ( *(float *)&v53[36].tQTaskChildren.ptHead > (double)(int)pValue_84b73b8 * v54 )
    _snprintf(igi2_frame.Buffer, 0xFFu, (char *const)&g_ptNetManager.tReceiveCounters.tCounters[25].nCounter);
  else
LABEL_65:
    _snprintf(igi2_frame.Buffer, 0xFFu, (char *const)&g_zInitialValue);
  v55 = StatusScreen_ptClientPLText;
  StatusScreen_ptClientPLText->vX = (float)(int)(__int64)(igi2_frame.vX1c + 170.0);
  v55->vY = 85.0;
  v55->vR = 127.0;
  v55->vG = 127.0;
  v55->vB = 127.0;
  v56 = (__int16 *)v55->ptQTilemap;
  memset(v55->ptQTilemap->anGraphicWidth, 0, 2 * v55->ptQTilemap->nHeight);
  memset(v56 + 8, 0, v56[3] * v56[2]);
  v57 = v55->ptQTilemap;
  v58 = igi2_frame.Buffer[0];
  v59 = (int)v55->ptQTilemap->ptQSprite->ptQTilemap->anID;
  v60 = igi2_frame.Buffer;
  if ( igi2_frame.Buffer[0] )
  {
    v61 = v55->ptQTilemap->anID - (unsigned __int8 *)igi2_frame.Buffer;
    do
    {
      v60[v61] = *(_BYTE *)(v58 + v59);
      v58 = *++v60;
    }
    while ( v58 );
  }
  QTilemap_UpdateGraphicWidth(v57, 0);
  QTilemap_Register(
    v55->ptQTilemap,
    v55->vX,
    v55->vY,
    v55->vR,
    v55->vG,
    v55->vB,
    v55->vA,
    v55->vZ,
    v55->bQGraphicFlags | 0x40000000,
    v55->nPri);
}

// source: j/0/screens/statusscreen/statusscreen.c:2748  [anchor-caller]
void __cdecl StatusScreen_DrawHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { float v91; };
    struct { float v92; };
    struct { float v93; };
    struct { float v94; };
    struct { char igi2_o4[4]; float vY; };
    struct { char igi2_o5[4]; float vYa; };
    struct { char igi2_o6[4]; float vYb; };
    struct { char igi2_o7[4]; float vYc; };
    struct { char igi2_o8[8]; float vWidth; };
    struct { char igi2_o9[12]; float vHeight; };
    struct { char igi2_o10[12]; float vHeighta; };
    struct { char igi2_o11[12]; float vHeightb; };
    struct { char igi2_o12[12]; float vHeightc; };
    struct { char igi2_o13[16]; float ptQSprite; };
    struct { char igi2_o14[20]; float vX; };
    struct { char igi2_o15[32]; struct QTask_s *ptNext; };
    struct { char igi2_o16[36]; char *v107; };
    struct { char igi2_o17[36]; int v108; };
    struct { char igi2_o18[36]; char *v109; };
    struct { char igi2_o19[40]; int WarmUpTimer; };
    struct { char igi2_o20[40]; struct QTask_s *ptPrev; };
    struct { char igi2_o21[40]; int v111; };
    struct { char igi2_o22[40]; int v112; };
    struct { char igi2_o23[40]; char *v113; };
    struct { char igi2_o24[40]; char *v115; };
    struct { char igi2_o25[40]; char *zPlayerName; };
    struct { char igi2_o26[60]; int StringWidth; };
    struct { char igi2_o27[60]; int v118; };
    struct { char igi2_o28[72]; char *zResourceName; };
    struct { char igi2_o29[72]; char *zResourceNamea; };
    struct { char igi2_o30[72]; int zResourceNameb; };
    struct { char igi2_o31[72]; float zResourceNamec; };
    struct { char igi2_o32[72]; char *zResourceNamed; };
    struct { char igi2_o33[72]; char *zResourceNamee; };
    struct { char igi2_o34[76]; struct QTask_s *v125; };
    struct { char igi2_o35[76]; int v126; };
    struct { char igi2_o36[76]; int v127; };
    struct { char igi2_o37[80]; struct QTask_s *ptTail; };
    struct { char igi2_o38[80]; float v129; };
    struct { char igi2_o39[80]; struct StaticTilemap_s **v130; };
    struct { char igi2_o40[80]; struct StaticTilemap_s **v131; };
    struct { char igi2_o41[84]; int ltcg_esi; };
    struct { char igi2_o42[84]; struct Client_s *ltcg_esia; };
    struct { char igi2_o43[84]; int ltcg_esib; };
    struct { char igi2_o44[88]; float v135; };
    struct { char igi2_o45[88]; float v136; };
    struct { char igi2_o46[88]; int v137; };
    struct { char igi2_o47[92]; int nWidth; };
    struct { char igi2_o48[96]; int nHeight; };
    struct { char igi2_o49[100]; struct StatusScreen_t *v140; };
    struct { char igi2_o50[104]; struct Client_s *v141; };
    struct { char igi2_o51[108]; struct StaticTilemap_s v142; };
    struct { char igi2_o52[364]; char Buffer[64]; };
    struct { char igi2_o53[428]; struct StaticTilemap_s ptQText; };
    struct { char igi2_o54[684]; struct StaticTilemap_s v145; };
    struct { char igi2_o55[940]; char Destination[1024]; };
    struct { char igi2_o56[1964]; char zStateString[256]; };
    char igi2_extent[2220];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QReference_s *ptHumanCameraQTaskRef; // ecx
  struct StatusScreen_t *v2; // ebx
  struct QTask_s *ptHead; // eax
  int v4; // edx
  struct QTask_s *v5; // ecx
  int v6; // esi
  void (__cdecl *pfHandler)(struct QTask_s *); // ecx
  int v8; // edx
  struct QReference_s *v9; // ebx
  int v10; // eax
  struct QTask_s *v11; // eax
  void (__cdecl *v12)(struct QTask_s *, struct StatusScreen_t **); // ecx
  int v13; // kr00_4
  int v14; // edx
  char *v15; // ecx
  char *v16; // eax
  char *LocalizedString; // eax
  double v18; // st7
  double v19; // st7
  enum NetManagerMode_e v20; // esi
  struct WeaponTypeItem_s *WeaponTypeItemFromWeaponType; // edi
  int v22; // esi
  char *v23; // eax
  struct WeaponType_s *ptWeaponType; // edi
  struct Client_s *v25; // eax
  int v26; // eax
  char *v27; // eax
  char *v28; // eax
  char *v29; // eax
  char *v30; // ecx
  char *v31; // eax
  char *v32; // eax
  char *v33; // eax
  char *v34; // edi
  char *v35; // eax
  char *v36; // eax
  double v37; // st7
  int v38; // eax
  char *v39; // eax
  struct StaticTilemap_s *v40; // eax
  struct QSprite_s *ptFont1; // esi
  char *v42; // edx
  unsigned int v43; // eax
  char *v44; // edi
  _WORD *v46; // edi
  char v47; // al
  char *v48; // eax
  char *v49; // eax
  int v50; // edx
  struct Objective_t *InactiveObjective; // esi
  struct Objective_t *Objective; // eax
  char *v53; // eax
  char *v54; // edi
  struct QSprite_s *v55; // esi
  char *v56; // edx
  unsigned int v57; // eax
  char *v58; // edi
  _WORD *v60; // edi
  char v61; // al
  bool v62; // zf
  char *v63; // eax
  char *v64; // edi
  struct QSprite_s *v65; // esi
  char *v66; // edx
  unsigned int v67; // eax
  char *v68; // edi
  _WORD *v70; // edi
  char v71; // al
  struct Client_s *ClientFromNetworkID; // eax
  char *v73; // eax
  char *v74; // eax
  struct QTask_s *ptParent; // esi
  char *v76; // eax
  char *v77; // eax
  char *v78; // eax
  struct StaticTilemap_s *ptMPModeCancelText; // eax
  char *v80; // eax
  char *v81; // eax
  int v82; // edi
  BOOL v83; // eax
  enum NetManagerMode_e v84; // esi
  struct QTask_s *v85; // eax
  struct QTask_s *ptMiddle; // edx
  struct StaticTilemap_s *ptMapStatQText; // ebx
  double v88; // st7
  double v89; // st6
  char *LocalizedStringForLanguage; // eax

  ptHumanCameraQTaskRef = Game_ptGame->ptHumanCameraQTaskRef;
  if ( ptHumanCameraQTaskRef )
    igi2_frame.ltcg_esi = (int)ptHumanCameraQTaskRef->pxObject;
  else
    igi2_frame.ltcg_esi = 0;
  v2 = (struct StatusScreen_t *)ptQTask;
  igi2_frame.zResourceName = (char *)&Game_ptGame->tQCamera;
  igi2_frame.nWidth = Display_tActiveMode.nWidth;
  igi2_frame.nHeight = Display_tActiveMode.nHeight;
  qmemcpy(&RenderContext_tActiveRenderContext, &ptQTask[1], sizeof(RenderContext_tActiveRenderContext));
  igi2_frame.v125 = HumanPlayer_ptQTask;
  igi2_frame.ptTail = nullptr;
  ++RenderContext_nActiveRenderContextTimeStamp;
  ptQTask[1].ptPrev = nullptr;
  ptQTask[1].ptNext = nullptr;
  List_AddTail(&ptQTask[1].ptNext, (int)&RenderContext_tDrawList);
  ptHead = ptQTask->tQTaskChildren.ptHead;
  if ( ptHead->ptNext && ptHead )
  {
    v4 = QTask_nProtectedQTaskStackOffset;
    do
    {
      if ( ptHead->ptNext )
        v5 = ptHead->ptNext->ptNext != nullptr ? ptHead->ptNext : nullptr;
      else
        v5 = nullptr;
      v6 = Screen_eDrawQTaskEvent;
      QTask_atProtectedQTaskStack[v4].ptQTask = v5;
      pfHandler = (void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[v6][ptHead->eQTaskType].pfHandler;
      v8 = v4 + 1;
      QTask_nProtectedQTaskStackOffset = v8;
      if ( pfHandler )
      {
        pfHandler(ptHead);
        v8 = QTask_nProtectedQTaskStackOffset;
      }
      ptHead = (struct QTask_s *)dword_849C7DC[v8];
      v4 = v8 - 1;
      QTask_nProtectedQTaskStackOffset = v4;
    }
    while ( ptHead );
  }
  if ( Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER )
  {
    v9 = ptQTask[28].tQTaskRefList.ptHead;
    QTilemap_Register(
      (struct QTilemap_s *)v9->ptNext,
      *(float *)&v9->ptPrev,
      *(float *)&v9->pxObject,
      *(float *)&v9[1].pxObject,
      *(float *)&v9[2].ptNext,
      *(float *)&v9[2].ptPrev,
      *(float *)&v9[1].ptPrev,
      *(float *)&v9[1].ptNext,
      (int)v9[3].ptNext | 0x40000000,
      (int)v9[2].pxObject);
    v2 = (struct StatusScreen_t *)ptQTask;
  }
  if ( igi2_frame.v125 )
    igi2_frame.ptTail = igi2_frame.v125[33].tQTaskChildren.ptTail;
  if ( *((_DWORD *)igi2_frame.zResourceName + 22) != igi2_frame.ltcg_esi )
    goto LABEL_115;
  if ( Computer_ptComputerQTask )
    goto LABEL_115;
  if ( !igi2_frame.ltcg_esi )
    goto LABEL_115;
  v10 = *(_DWORD *)(igi2_frame.ltcg_esi + 112);
  if ( !v10 )
    goto LABEL_115;
  v11 = *(struct QTask_s **)(v10 + 8);
  if ( *(_DWORD *)(igi2_frame.ltcg_esi + 240) == 6 )
    v11 = HumanPlayer_ptQTask;
  igi2_frame.v140 = v2;
  if ( v11 )
  {
    v12 = (void (__cdecl *)(struct QTask_s *, struct StatusScreen_t **))QTask_aatQTaskFinalEvent[StatusScreen_eStatusDisplayQTaskEvent][v11->eQTaskType].pfHandler;
    if ( v12 )
      v12(v11, &igi2_frame.v140);
  }
  if ( !igi2_frame.ptTail || igi2_frame.ptTail[16].tQTaskRefList.ptMiddle )
  {
LABEL_115:
    if ( Game_eGameMode != GAME_GAMEMODE_MULTIPLAYER )
      return;
    v82 = 0;
    v83 = (InputPort_atInputPort[0].tInput.bCurrentButton & 0x1000000000000LL) != 0;
    v84 = NetManager_eMode;
    v2[1].tQTask.ptNext = nullptr;
    if ( !v83 )
    {
      if ( v84 != NETMANAGER_MODE_COMPLETE )
      {
        if ( v84 != NETMANAGER_MODE_SPAWN )
        {
LABEL_128:
          if ( NetMission_GetMissionTimer() > 0 && v82 )
          {
            ComputerObjectives_GetStatusStrings((char *)&igi2_frame.v142, igi2_frame.zStateString, 255);
            LocalizedStringForLanguage = Config_GetLocalizedStringForLanguage(
                                           "Objective",
                                           Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eLanguage,
                                           true);
            _snprintf(
              (char *const)&igi2_frame.v145,
              0xFFu,
              "%s %d: %s",
              LocalizedStringForLanguage,
              NetMission_eCurrentObjective,
              (char *)&igi2_frame.v142);
            Text_SetString((struct StaticTilemap_s *)ptQTask[29].tQTaskRefList.ptHead, (char *)&igi2_frame.v145);
            ptQTask[29].tQTaskRefList.ptHead[3].ptNext = (struct QReference_s *)((int)ptQTask[29].tQTaskRefList.ptHead[3].ptNext
                                                                               | 0x80);
            *(float *)&ptQTask[29].tQTaskRefList.ptHead->ptPrev = (float)(int)(__int64)((double)igi2_frame.nWidth * 0.5);
            *(float *)&ptQTask[29].tQTaskRefList.ptHead->pxObject = (float)(int)(__int64)((double)igi2_frame.nHeight * 0.9549999833106995);
            Text_Register((struct StaticTilemap_s *)ptQTask[29].tQTaskRefList.ptHead);
          }
          if ( Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER )
          {
            if ( StatusScreen_isShowNetStats )
              StatusScreen_DrawLowLevelStats();
          }
          return;
        }
LABEL_127:
        v82 = 1;
        goto LABEL_128;
      }
      if ( v2->nObjectiveTextTimer )
        goto LABEL_128;
    }
    v85 = MenuManager_ptQTask;
    if ( MenuManager_ptQTask )
    {
      ptMiddle = MenuManager_ptQTask[1].tQTaskChildren.ptMiddle;
      if ( ptMiddle != (struct QTask_s *)10 && v84 != NETMANAGER_MODE_COMPLETE && ptMiddle != (struct QTask_s *)20 )
      {
        MenuManager_ptQTask[1].tQTaskChildren.ptHead = ptMiddle;
        v85[1].tQTaskChildren.ptMiddle = (struct QTask_s *)20;
      }
    }
    MapControl_PrintMapStat((char *)&igi2_frame.ptQText, 255);
    Text_SetString(v2->ptMapStatQText, (char *)&igi2_frame.ptQText);
    v2->ptMapStatQText->bQGraphicFlags |= 0x80u;
    v2->ptMapStatQText->vX = (float)(int)(__int64)((double)Display_tActiveMode.nWidth * 0.5);
    v2->ptMapStatQText->vY = (float)(int)(__int64)((double)Display_tActiveMode.nHeight * 0.009999990463256836);
    v2->ptMapStatQText->vR = 16.0;
    v2->ptMapStatQText->vG = 96.0;
    v2->ptMapStatQText->vB = 16.0;
    ptMapStatQText = v2->ptMapStatQText;
    QTilemap_Register(
      ptMapStatQText->ptQTilemap,
      ptMapStatQText->vX,
      ptMapStatQText->vY,
      ptMapStatQText->vR,
      ptMapStatQText->vG,
      ptMapStatQText->vB,
      ptMapStatQText->vA,
      ptMapStatQText->vZ,
      ptMapStatQText->bQGraphicFlags | 0x40000000,
      ptMapStatQText->nPri);
    StatusScreen_DisplayScoreboard((struct StatusScreen_t *)ptQTask);
    ptQTask[53].ptParent = (struct QTask_s *)1;
    v88 = (double)Display_tActiveMode.nHeight;
    v89 = (double)Display_tActiveMode.nWidth;
    igi2_frame.vHeightc = v88 * 0.9879999756813049;
    igi2_frame.vWidth = 0.6399999856948853 * v89;
    igi2_frame.vYc = v88 * 0.5 - v88 * 0.49399998784065247;
    igi2_frame.v94 = 0.5 * v89 - v89 * 0.3199999928474426;
    QSprite_RegisterBlankAZ(igi2_frame.v94, igi2_frame.vYc, igi2_frame.vWidth, igi2_frame.vHeightc, 0.0, 0.0, 0.0, 0.30000001192092896, 1.0, 0x10000000u, 0);
    if ( NetManager_eMode == NETMANAGER_MODE_WELCOME
      || NetManager_eMode == NETMANAGER_MODE_COMPLETE
      || NetManager_eMode == NETMANAGER_MODE_SELECTTEAM )
    {
      goto LABEL_128;
    }
    goto LABEL_127;
  }
  if ( LevelFlow_ptLevelFlow->isInterfaceTimer )
  {
    v13 = LevelFlow_GetInterfaceCountDownTimeTicks() / 30;
    v14 = LevelFlow_GetInterfaceCountDownTimeTicks() / 30 % 60;
    v15 = "s";
    if ( v14 == 1 )
      v15 = (char *)&g_zInitialValue;
    v16 = "s";
    if ( v13 / 60 == 1 )
      v16 = (char *)&g_zInitialValue;
    sprintf(igi2_frame.Buffer, "Until map change: %d minute%s, %d second%s", v13 / 60, v16, v14, v15);
    Text_SetString(v2->ptTimeLeftQText, igi2_frame.Buffer);
    igi2_frame.zResourceNamec = (double)igi2_frame.nWidth * 0.5;
    v2->ptTimeLeftQText->vX = (float)(__int64)igi2_frame.zResourceNamec;
    igi2_frame.v135 = (double)igi2_frame.nHeight * 0.9100000262260437;
    v2->ptTimeLeftQText->vY = (float)(__int64)igi2_frame.v135;
    Text_Register(v2->ptTimeLeftQText);
  }
  if ( Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER )
  {
    if ( NetMission_isWarmUp )
    {
      igi2_frame.WarmUpTimer = NetMission_GetWarmUpTimer();
      LocalizedString = Config_GetLocalizedString("mp/Countdown");
      _snprintf(igi2_frame.Buffer, 0x40u, "%s: %02d", LocalizedString, igi2_frame.WarmUpTimer);
    }
    else
    {
      NetMission_SetDesc(0x40u, igi2_frame.Buffer);
    }
    Text_SetString(v2->ptTimeLeftQText, igi2_frame.Buffer);
    v18 = (double)igi2_frame.nWidth;
    igi2_frame.v129 = v18;
    v2->ptTimeLeftQText->bQGraphicFlags |= 0x80u;
    v2->ptTimeLeftQText->vX = (float)(int)(__int64)(v18 * 0.5);
    v19 = (double)igi2_frame.nHeight;
    v2->ptTimeLeftQText->vY = (float)(int)(__int64)(v19 * 0.9100000262260437);
    Text_Register(v2->ptTimeLeftQText);
    v20 = NetManager_eMode;
    if ( NetManager_eMode != NETMANAGER_MODE_WELCOME )
    {
      igi2_frame.ltcg_esia = NetManager_GetClientFromNetworkID((int)Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle);
      if ( igi2_frame.v125
        && (v20 == NETMANAGER_MODE_SPAWN
         || !LOBYTE(igi2_frame.v125[29].tQTaskRefList.ptHead)
         && (v20 == NETMANAGER_MODE_PLAY || v20 == NETMANAGER_MODE_RADIO || v20 == NETMANAGER_MODE_SHOP)) )
      {
        WeaponTypeItemFromWeaponType = Weapon_GetWeaponTypeItemFromWeaponType(igi2_frame.v125[33].ptNext, "WEAPON_ID_C4BOMB");
        igi2_frame.zResourceNamed = (char *)(__int64)(v2->vRadarRange * 0.000244140625);
        v22 = 1 - (__int64)((v2->vRadarRange - 204800.0) * -2.1701389414374717e-06);
        StatusScreen_DrawRadar(v2);
        v23 = Config_GetLocalizedString("mp/Range");
        sprintf((char *const)&igi2_frame.ptQText, "%s %d/%d: %dm", v23, v22, 5, igi2_frame.zResourceNamed);
        Text_SetString(v2->ptRadarZoomText, (char *)&igi2_frame.ptQText);
        v2->ptRadarZoomText->bQGraphicFlags |= 0x80u;
        v2->ptRadarZoomText->vX = (float)(int)(__int64)((double)Display_tActiveMode.nWidth * 0.9100000262260437);
        v2->ptRadarZoomText->vY = (float)(int)(__int64)(0.0013020833721384406 * (double)Display_tActiveMode.nHeight * 154.0 * 0.5
                                                      + (double)Display_tActiveMode.nHeight * 0.11500000208616257
                                                      + 6.0);
        Text_Register(v2->ptRadarZoomText);
        if ( WeaponTypeItemFromWeaponType )
        {
          if ( WeaponTypeItemFromWeaponType->isActive )
          {
            ptWeaponType = WeaponTypeItemFromWeaponType->ptWeaponType;
            igi2_frame.vX = (double)Display_tActiveMode.nHeight * 0.9583333134651184
               - 2.0
               - 2.0
               - (double)ptWeaponType->tWeaponSprite.atQAnimframe[ptWeaponType->tWeaponSprite.nQAnimframes].nHeight
               * 2.5;
            igi2_frame.ptQSprite = (double)Display_tActiveMode.nWidth * 0.984375
                      - (double)ptWeaponType->tWeaponSprite.atQAnimframe[ptWeaponType->tWeaponSprite.nQAnimframes].nWidth;
            QSprite_Register(&ptWeaponType->tWeaponSprite, igi2_frame.ptQSprite, igi2_frame.vX, 128.0, 128.0, 128.0, 0, 0, 0);
          }
        }
      }
      if ( igi2_frame.ltcg_esia )
      {
        sprintf((char *const)&igi2_frame.v142, dword_6960A8, igi2_frame.ltcg_esia->nUpdateItemTime);
        Text_SetString(v2->ptMoneyText, (char *)&igi2_frame.v142);
        Text_Register(v2->ptMoneyText);
        v25 = *(struct Client_s **)(igi2_frame.ltcg_esia->tReceiveTimeBuffer.nCounter + 8);
        v2->ptSpawnCostText->vR = 51.20000076293945;
        v2->ptSpawnCostText->vG = 76.80000305175781;
        v2->ptSpawnCostText->vB = 128.0;
        if ( v25 )
        {
          if ( v25[1].zTalkString[24] )
          {
            if ( Client_isSpawnAffordable(v25, (int)igi2_frame.ltcg_esia) == false )
            {
              v2->ptSpawnCostText->vR = 96.0;
              v2->ptSpawnCostText->vG = 16.0;
              v2->ptSpawnCostText->vB = 16.0;
            }
            v26 = Client_CostToSpawn(igi2_frame.ltcg_esia);
            if ( v26 <= 0 )
            {
              v27 = Config_GetLocalizedString("mp/SPAWNFREE");
              sprintf((char *const)&igi2_frame.v142, v27);
            }
            else
            {
              igi2_frame.v111 = v26;
              igi2_frame.v107 = Config_GetLocalizedString("mp/SPAWNCOST");
              sprintf((char *const)&igi2_frame.v142, "%s: %d", igi2_frame.v107, igi2_frame.v111);
            }
          }
          else
          {
            v28 = Config_GetLocalizedString("mp/PLAYERALIVE");
            sprintf((char *const)&igi2_frame.v142, v28);
            sprintf((char *const)&igi2_frame.v142, (char *const)&g_zInitialValue, igi2_frame.v108, igi2_frame.v112);
          }
        }
        else
        {
          sprintf((char *const)&igi2_frame.v142, "?NO PLAYER");
        }
        Text_SetString(v2->ptSpawnCostText, (char *)&igi2_frame.v142);
        Text_Register(v2->ptSpawnCostText);
        if ( Netshop_isOpenToLocal() && NetManager_eMode == NETMANAGER_MODE_PLAY )
        {
          igi2_frame.v113 = Config_GetLocalizedString("mp/SHOPOPEN");
          sprintf((char *const)&igi2_frame.v142, igi2_frame.v113);
        }
        else
        {
          sprintf((char *const)&igi2_frame.v142, (char *const)&g_zInitialValue);
        }
        Text_SetString(v2->ptShopText, (char *)&igi2_frame.v142);
        v2->ptShopText->vX = (float)(int)(__int64)(igi2_frame.v129 * 0.0234375);
        igi2_frame.v136 = v19;
        v2->ptShopText->vY = (float)(int)(__int64)(igi2_frame.v136 * 0.375);
        Text_Register(v2->ptShopText);
        if ( NetManager_eMode == NETMANAGER_MODE_COMPLETE )
        {
          if ( MapControl_isChangeMapNow() )
          {
            v29 = Config_GetLocalizedString("mp/MapFinished");
            Text_SetString(v2->ptMPModeText, v29);
            v30 = "mp/NextMap";
          }
          else
          {
            v31 = Config_GetLocalizedString("mp/RoundFinished");
            Text_SetString(v2->ptMPModeText, v31);
            v30 = "mp/RestartingMap";
          }
          v32 = Config_GetLocalizedString(v30);
          Text_SetString(v2->ptMPModeSubText, v32);
          v2->ptMPModeText->vX = (float)(int)(__int64)((double)Display_tActiveMode.nWidth * 0.5);
          v2->ptMPModeText->vY = (float)(int)(__int64)((double)Display_tActiveMode.nHeight * 0.4399999976158142);
          v2->ptMPModeSubText->vX = (float)(int)(__int64)((double)Display_tActiveMode.nWidth * 0.5);
          v2->ptMPModeSubText->vY = (float)(int)(__int64)((double)Display_tActiveMode.nHeight * 0.4399999976158142 + 30.0);
          v2->ptMPModeText->vR = 128.0;
          v2->ptMPModeText->vG = 128.0;
          v2->ptMPModeText->vB = 128.0;
          v2->ptMPModeSubText->vR = 128.0;
          v2->ptMPModeSubText->vG = 128.0;
          v2->ptMPModeSubText->vB = 128.0;
          Text_Register(v2->ptMPModeText);
          Text_Register(v2->ptMPModeSubText);
        }
      }
    }
    switch ( NetManager_eMode )
    {
      case NETMANAGER_MODE_SPECTATE:
        ClientFromNetworkID = NetManager_GetClientFromNetworkID((int)Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptTail);
        if ( ClientFromNetworkID )
        {
          igi2_frame.zPlayerName = ClientFromNetworkID->zPlayerName;
          v73 = Config_GetLocalizedString("mp/Spectating");
          _snprintf((char *const)&igi2_frame.ptQText, 0xFFu, "%s %s\n", v73, igi2_frame.zPlayerName);
          Text_SetString(v2->ptMPModeText, (char *)&igi2_frame.ptQText);
          v74 = Config_GetLocalizedString("mp/switchplayer");
          Text_SetString(v2->ptMPModeSubText, v74);
          igi2_frame.v115 = Config_GetLocalizedString("mp/switchview");
          Text_SetString(v2->ptMPModeCancelText, igi2_frame.v115);
        }
        else
        {
          Text_SetString(v2->ptMPModeText, (char *)&g_zInitialValue);
          Text_SetString(v2->ptMPModeSubText, (char *)&g_zInitialValue);
          Text_SetString(v2->ptMPModeCancelText, (char *)&g_zInitialValue);
        }
        v2->ptMPModeText->vX = (float)(int)(__int64)((double)Display_tActiveMode.nWidth * 0.5);
        v2->ptMPModeText->vY = (float)(int)(__int64)((double)Display_tActiveMode.nHeight * 0.6700000166893005);
        v2->ptMPModeSubText->vX = (float)(int)(__int64)((double)Display_tActiveMode.nWidth * 0.5);
        v2->ptMPModeSubText->vY = (float)(int)(__int64)((double)Display_tActiveMode.nHeight * 0.699999988079071);
        v2->ptMPModeCancelText->vX = (float)(int)(__int64)((double)Display_tActiveMode.nWidth * 0.5);
        v2->ptMPModeCancelText->vY = (float)(int)(__int64)((double)Display_tActiveMode.nHeight * 0.7300000190734863);
        v2->ptMPModeText->vR = 16.0;
        v2->ptMPModeText->vG = 96.0;
        v2->ptMPModeText->vB = 16.0;
        v2->ptMPModeSubText->vR = 127.0;
        v2->ptMPModeSubText->vG = 127.0;
        v2->ptMPModeSubText->vB = 127.0;
        v2->ptMPModeCancelText->vR = 127.0;
        v2->ptMPModeCancelText->vG = 127.0;
        v2->ptMPModeCancelText->vB = 127.0;
        goto LABEL_112;
      case NETMANAGER_MODE_SPAWN:
        ptParent = SpawnArea_ptActive->ptParent;
        igi2_frame.ptPrev = SpawnArea_ptActive[6].ptPrev;
        igi2_frame.v109 = Config_GetLocalizedString("mp/Spawn Area");
        igi2_frame.ptNext = ptParent[5].ptNext;
        v76 = Config_GetLocalizedString("Objective");
        sprintf((char *const)&igi2_frame.ptQText, "%s [%d] - %s [%d]", v76, igi2_frame.ptNext, igi2_frame.v109, igi2_frame.ptPrev);
        Text_SetString(v2->ptMPModeText, (char *)&igi2_frame.ptQText);
        v77 = Config_GetLocalizedString("mp/selectspawn");
        Text_SetString(v2->ptMPModeSubText, v77);
        v78 = Config_GetLocalizedString("mp/presscancel");
        Text_SetString(v2->ptMPModeCancelText, v78);
        v2->ptMPModeText->vX = (float)(int)(__int64)((double)Display_tActiveMode.nWidth * 0.5);
        v2->ptMPModeText->vY = (float)(int)(__int64)((double)Display_tActiveMode.nHeight * 0.44999998807907104);
        v2->ptMPModeSubText->vX = (float)(int)(__int64)((double)Display_tActiveMode.nWidth * 0.5);
        v2->ptMPModeSubText->vY = (float)(int)(__int64)((double)Display_tActiveMode.nHeight * 0.550000011920929);
        v2->ptMPModeCancelText->vX = (float)(int)(__int64)((double)Display_tActiveMode.nWidth * 0.5);
        v2->ptMPModeCancelText->vY = (float)(int)(__int64)((double)Display_tActiveMode.nHeight * 0.5799999833106995);
        v2->ptMPModeText->vR = 128.0;
        v2->ptMPModeText->vG = 96.0;
        v2->ptMPModeText->vB = 0.0;
        if ( v2[1].tQTask.ptNext )
          goto LABEL_115;
LABEL_112:
        Text_Register(v2->ptMPModeText);
        Text_Register(v2->ptMPModeSubText);
        ptMPModeCancelText = v2->ptMPModeCancelText;
LABEL_114:
        Text_Register(ptMPModeCancelText);
        break;
      case NETMANAGER_MODE_DEAD:
        v80 = Config_GetLocalizedString("mp/YouDied");
        Text_SetString(v2->ptMPModeText, v80);
        v81 = Config_GetLocalizedString("mp/gotospec");
        Text_SetString(v2->ptMPModeSubText, v81);
        v2->ptMPModeText->vX = (float)(int)(__int64)((double)Display_tActiveMode.nWidth * 0.5);
        v2->ptMPModeText->vY = (float)(int)(__int64)((double)Display_tActiveMode.nHeight * 0.44999998807907104);
        v2->ptMPModeSubText->vX = (float)(int)(__int64)((double)Display_tActiveMode.nWidth * 0.5);
        v2->ptMPModeSubText->vY = (float)(int)(__int64)((double)Display_tActiveMode.nHeight * 0.550000011920929);
        v2->ptMPModeText->vR = 128.0;
        v2->ptMPModeText->vG = 96.0;
        v2->ptMPModeText->vB = 0.0;
        v2->ptMPModeText->vR = 128.0;
        v2->ptMPModeText->vG = 96.0;
        v2->ptMPModeText->vB = 0.0;
        Text_Register(v2->ptMPModeText);
        ptMPModeCancelText = v2->ptMPModeSubText;
        goto LABEL_114;
      case NETMANAGER_MODE_WELCOME:
        igi2_frame.v141 = NetManager_GetClientFromNetworkID((int)Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle);
        sprintf((char *const)&igi2_frame.ptQText, "Mission %02d Desc", Game_iMissionID);
        v33 = Config_GetLocalizedString((char *)&igi2_frame.ptQText);
        strncpy(igi2_frame.Destination, v33, 0x400u);
        v34 = strtok(igi2_frame.Destination, (char *)&Delimiter);
        sprintf((char *const)&igi2_frame.v142, "Mission %02d Name", Game_iMissionID);
        v35 = Config_GetLocalizedString((char *)&igi2_frame.v142);
        Text_SetString(v2->ptMPModeText, v35);
        v36 = Config_GetLocalizedString("mp/pressfire");
        Text_SetString(v2->ptMPModeSubText, v36);
        v2->ptMPModeText->vX = (float)(int)(__int64)((double)Display_tActiveMode.nWidth * 0.5);
        v2->ptMPModeText->vY = (float)(int)(__int64)((double)Display_tActiveMode.nHeight * 0.10000000149011612);
        v2->ptMPModeSubText->vX = (float)(int)(__int64)((double)Display_tActiveMode.nWidth * 0.5);
        v2->ptMPModeSubText->vY = (float)(int)(__int64)((double)Display_tActiveMode.nHeight * 0.8500000238418579);
        v2->ptMPModeText->vR = 127.0;
        v2->ptMPModeText->vG = 127.0;
        v2->ptMPModeText->vB = 127.0;
        v2->ptMPModeSubText->vR = 127.0;
        v2->ptMPModeSubText->vG = 127.0;
        v2->ptMPModeSubText->vB = 127.0;
        Text_Register(v2->ptMPModeText);
        Text_Register(v2->ptMPModeSubText);
        v37 = v2->vFont1Height + 3.0;
        igi2_frame.vHeight = 13.0 * v37;
        igi2_frame.vY = (double)Display_tActiveMode.nHeight * 0.10000000149011612 - v37;
        igi2_frame.v91 = (double)Display_tActiveMode.nWidth * 0.5 - 300.0;
        QSprite_RegisterBlankAZ(igi2_frame.v91, igi2_frame.vY, 600.0, igi2_frame.vHeight, 0.0, 0.0, 0.0, 0.25, 1.0, 0x80000u, 5);
        igi2_frame.v126 = 0;
        v38 = 0;
        do
        {
          if ( v38 )
          {
            for ( LOBYTE(igi2_frame.v142.ptQTilemap) = 0; v34; v34 = strtok(nullptr, (char *)&Delimiter) )
            {
              ptFont1 = v2->ptFont1;
              igi2_frame.zResourceNamee = (char *)Font_GetStringWidth(ptFont1, (char *)&igi2_frame.v142);
              if ( (int)&igi2_frame.zResourceNamee[Font_GetStringWidth(ptFont1, v34)] >= 550 )
                break;
              v42 = v34;
              v43 = strlen(v34) + 1;
              v44 = (char *)&igi2_frame.v141 + 3;
              while ( *++v44 )
                ;
              qmemcpy(v44, v42, v43);
              v46 = (_WORD *)((char *)&igi2_frame.v141 + 3);
              do
              {
                v47 = *((_BYTE *)v46 + 1);
                v46 = (_WORD *)((char *)v46 + 1);
              }
              while ( v47 );
              *v46 = 32;
            }
            Text_SetString(v2->aptMissionDesc[igi2_frame.v126], (char *)&igi2_frame.v142);
            v2->aptMissionDesc[igi2_frame.v126]->vR = 51.20000076293945;
            v2->aptMissionDesc[igi2_frame.v126]->vG = 76.80000305175781;
            v2->aptMissionDesc[igi2_frame.v126]->vB = 128.0;
            v40 = v2->aptMissionDesc[igi2_frame.v126];
          }
          else
          {
            v39 = Config_GetLocalizedString("mp/missiondesc");
            Text_SetString(v2->aptMissionDesc[0], v39);
            v2->aptMissionDesc[0]->vR = 115.19999694824219;
            v2->aptMissionDesc[0]->vG = 115.19999694824219;
            v2->aptMissionDesc[0]->vB = 128.0;
            v40 = v2->aptMissionDesc[0];
          }
          Text_Register(v40);
          v38 = ++igi2_frame.v126;
        }
        while ( igi2_frame.v126 < 9 );
        igi2_frame.vHeighta = (v2->vFont1Height + 3.0) * 8.0;
        igi2_frame.vYa = (double)Display_tActiveMode.nHeight * 0.5699999928474426 - 15.0;
        igi2_frame.v92 = (double)Display_tActiveMode.nWidth * 0.5 - 310.0;
        QSprite_RegisterBlankAZ(igi2_frame.v92, igi2_frame.vYa, 305.0, igi2_frame.vHeighta, 0.0, 0.0, 0.0, 0.25, 1.0, 0x80000u, 5);
        igi2_frame.vHeightb = (v2->vFont1Height + 3.0) * 8.0;
        igi2_frame.vYb = (double)Display_tActiveMode.nHeight * 0.5699999928474426 - 15.0;
        igi2_frame.v93 = (double)Display_tActiveMode.nWidth * 0.5 + 5.0;
        QSprite_RegisterBlankAZ(igi2_frame.v93, igi2_frame.vYb, 305.0, igi2_frame.vHeightb, 0.0, 0.0, 0.0, 0.25, 1.0, 0x80000u, 5);
        v48 = Config_GetLocalizedString("mp/igiobj");
        Text_SetString(v2->aptGoodObjText[0], v48);
        v2->aptGoodObjText[0]->vR = 115.19999694824219;
        v2->aptGoodObjText[0]->vG = 115.19999694824219;
        v2->aptGoodObjText[0]->vB = 128.0;
        Text_Register(v2->aptGoodObjText[0]);
        v49 = Config_GetLocalizedString("mp/conobj");
        Text_SetString(v2->aptBadObjText[0], v49);
        v2->aptBadObjText[0]->vR = 115.19999694824219;
        v2->aptBadObjText[0]->vG = 115.19999694824219;
        v2->aptBadObjText[0]->vB = 128.0;
        Text_Register(v2->aptBadObjText[0]);
        v50 = 0;
        igi2_frame.v127 = 0;
        igi2_frame.ltcg_esib = (int)&v2->aptBadObjText[1];
        while ( 1 )
        {
          if ( igi2_frame.v141->eTeam )
          {
            InactiveObjective = DefineComputerObjective_GetInactiveObjective(v50);
            Objective = DefineComputerObjective_GetObjective(v50);
          }
          else
          {
            InactiveObjective = DefineComputerObjective_GetObjective(v50);
            Objective = DefineComputerObjective_GetInactiveObjective(v50);
          }
          igi2_frame.zResourceNamea = (char *)Objective;
          if ( InactiveObjective )
          {
            v53 = Config_GetLocalizedString(InactiveObjective->zResource);
            sprintf(igi2_frame.Destination, "%d. %s", igi2_frame.v127 + 1, v53);
            v54 = strtok(igi2_frame.Destination, (char *)&Delimiter);
            igi2_frame.v130 = (struct StaticTilemap_s **)(igi2_frame.ltcg_esib - 28);
            igi2_frame.v137 = 2;
            do
            {
              for ( LOBYTE(igi2_frame.v142.ptQTilemap) = 0; v54; v54 = strtok(nullptr, (char *)&Delimiter) )
              {
                v55 = v2->ptFont1;
                igi2_frame.StringWidth = Font_GetStringWidth(v55, (char *)&igi2_frame.v142);
                if ( Font_GetStringWidth(v55, v54) + igi2_frame.StringWidth >= 270 )
                  break;
                v56 = v54;
                v57 = strlen(v54) + 1;
                v58 = (char *)&igi2_frame.v141 + 3;
                while ( *++v58 )
                  ;
                qmemcpy(v58, v56, v57);
                v60 = (_WORD *)((char *)&igi2_frame.v141 + 3);
                do
                {
                  v61 = *((_BYTE *)v60 + 1);
                  v60 = (_WORD *)((char *)v60 + 1);
                }
                while ( v61 );
                *v60 = 32;
              }
              Text_SetString(*igi2_frame.v130, (char *)&igi2_frame.v142);
              Text_Register(*igi2_frame.v130);
              v62 = igi2_frame.v137 == 1;
              ++igi2_frame.v130;
              --igi2_frame.v137;
            }
            while ( !v62 );
          }
          if ( igi2_frame.zResourceNamea )
          {
            v63 = Config_GetLocalizedString(igi2_frame.zResourceNamea);
            sprintf(igi2_frame.Destination, "%d. %s", igi2_frame.v127 + 1, v63);
            v64 = strtok(igi2_frame.Destination, (char *)&Delimiter);
            igi2_frame.v131 = (struct StaticTilemap_s **)igi2_frame.ltcg_esib;
            igi2_frame.zResourceNameb = 2;
            do
            {
              for ( LOBYTE(igi2_frame.v142.ptQTilemap) = 0; v64; v64 = strtok(nullptr, (char *)&Delimiter) )
              {
                v65 = v2->ptFont1;
                igi2_frame.v118 = Font_GetStringWidth(v65, (char *)&igi2_frame.v142);
                if ( Font_GetStringWidth(v65, v64) + igi2_frame.v118 >= 270 )
                  break;
                v66 = v64;
                v67 = strlen(v64) + 1;
                v68 = (char *)&igi2_frame.v141 + 3;
                while ( *++v68 )
                  ;
                qmemcpy(v68, v66, v67);
                v70 = (_WORD *)((char *)&igi2_frame.v141 + 3);
                do
                {
                  v71 = *((_BYTE *)v70 + 1);
                  v70 = (_WORD *)((char *)v70 + 1);
                }
                while ( v71 );
                *v70 = 32;
              }
              Text_SetString(*igi2_frame.v131, (char *)&igi2_frame.v142);
              Text_Register(*igi2_frame.v131);
              v62 = igi2_frame.zResourceNameb == 1;
              ++igi2_frame.v131;
              --igi2_frame.zResourceNameb;
            }
            while ( !v62 );
          }
          ++igi2_frame.v127;
          igi2_frame.ltcg_esib += 8;
          if ( igi2_frame.v127 + 1 >= 4 )
            break;
          v50 = igi2_frame.v127;
        }
        goto LABEL_115;
      default:
        goto LABEL_115;
    }
    goto LABEL_115;
  }
}

// source: j/0/screens/statusscreen/statusscreen.c:3506  [size]
struct StatusScreen_t *__cdecl StatusScreen_GetStatusScreen()
{
  return (struct StatusScreen_t *)StatusScreen_ptStatusScreenQTask;
}

// source: j/0/screens/statusscreen/statusscreen.c:3519  [size]
__int16 __cdecl StatusScreen_GetStatusDisplayQTaskEvent()
{
  return StatusScreen_eStatusDisplayQTaskEvent;
}

// source: j/0/screens/statusscreen/statusscreen.c:3534  [size]
char **__cdecl StatusScreen_GetMessageIconNameArray()
{
  return StatusScreen_azQSpriteMessageIcon;
}

// source: j/0/screens/statusscreen/statusscreen.c:3547  [size]
char **__cdecl StatusScreen_GetActivateIconPointerArray()
{
  return StatusScreen_azQSpriteActivateIconPointer;
}

// source: j/0/screens/statusscreen/statusscreen.c:3560  [size]
struct StatusScreen_t *__cdecl StatusScreen_ClearDisplayActivateIconAlpha(
        struct StatusScreen_t *ptStatusScreen)
{
  ptStatusScreen->vActivateIconAlpha = 0.0;
  return ptStatusScreen;
}

// source: j/0/screens/statusscreen/statusscreen.c:3573  [anchor-callee]
void __cdecl StatusScreen_SetTalkText(char *zText)
{
  Text_SetString((struct StaticTilemap_s *)StatusScreen_ptStatusScreenQTask[28].tQTaskRefList.ptHead, zText);
}

// source: j/0/screens/statusscreen/statusscreen.c:3586  [anchor-callee]
void __cdecl StatusScreen_SetTalkColour(float vR, float vG, float vB)
{
  struct QReference_s *ptHead; // eax

  if ( StatusScreen_ptStatusScreenQTask )
  {
    ptHead = StatusScreen_ptStatusScreenQTask[28].tQTaskRefList.ptHead;
    if ( ptHead )
    {
      ptHead[1].ptPrev = (struct QReference_s *)1065353216;
      *(float *)&ptHead[1].pxObject = vR * 128.0;
      *(float *)&ptHead[2].ptNext = vG * 128.0;
      *(float *)&ptHead[2].ptPrev = vB * 128.0;
    }
  }
}

// source: j/0/screens/statusscreen/statusscreen.c:3605  [size]
void __cdecl StatusScreen_AddScoreClient(struct Client_s *ptClient)
{
  struct QTask_s *v1; // eax

  v1 = StatusScreen_ptStatusScreenQTask;
  *((_DWORD *)&StatusScreen_ptStatusScreenQTask[49].tQTaskChildren.ptHead
  + *(_DWORD *)&StatusScreen_ptStatusScreenQTask[48].eQTaskType) = ptClient;
  ++*(_DWORD *)&v1[48].eQTaskType;
}

// source: j/0/screens/statusscreen/statusscreen.c:3623  [anchor-callee]
void __cdecl StatusScreen_RemoveScoreClient(struct Client_s *ptClient)
{
  struct QTask_s *v1; // eax
  int v2; // edx
  int v3; // ecx

  v1 = StatusScreen_ptStatusScreenQTask;
  v2 = 0;
  if ( StatusScreen_ptStatusScreenQTask )
  {
    v3 = 0;
    while ( *((struct Client_s **)&v1[49].tQTaskChildren.ptHead + v3) != ptClient )
    {
      if ( v2 )
        goto LABEL_6;
LABEL_9:
      if ( ++v3 >= 32 )
        return;
    }
    --*(_DWORD *)&v1[48].eQTaskType;
    v2 = 1;
LABEL_6:
    if ( v3 == 31 )
      v1[52].tQTaskChildren.ptMiddle = nullptr;
    else
      *((_DWORD *)&v1[49].tQTaskChildren.ptHead + v3) = *((_DWORD *)&v1[49].tQTaskChildren.ptMiddle + v3);
    goto LABEL_9;
  }
}

// source: j/0/screens/statusscreen/statusscreen.c:3666  [anchor-mhash]
void __cdecl StatusScreen_SetClientStats(struct ClientStats_s *ptStats)
{
  bool v1; // sf
  unsigned int v2; // eax

  v2 = (StatusScreen_nCurrentClientStat + 1) & 0x800000FF;
  v1 = StatusScreen_nCurrentClientStat + 1 < 0;
  qmemcpy((void *)(72 * StatusScreen_nCurrentClientStat + 7652952), ptStats, 0x48u);
  if ( v1 )
    v2 = (((_BYTE)v2 - 1) | 0xFFFFFF00) + 1;
  StatusScreen_nCurrentClientStat = v2;
}

// source: j/0/screens/statusscreen/statusscreen.c:3683  [anchor-mhash]
struct Result_s *__cdecl StatusScreen_SetNetStatsCB(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  struct Result_s *v3; // edi
  struct Result_s *v4; // esi
  int ltcg_ebx[6]; // [esp+0h] [ebp-18h] BYREF

  if ( ptArgList && ptArgList->nArguments == 1 )
    StatusScreen_isShowNetStats = (char)Script_EvalArgInt(ptArgList, 0);
  v4 = NetworkCommand_AnnounceBool(v3, StatusScreen_isShowNetStats, (int)ltcg_ebx);
  qmemcpy(retstr, v4, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/screens/statusscreen/statusscreen.c:3693  [anchor-hash]
void __cdecl StatusScreen_ToggleNetStats()
{
  StatusScreen_isShowNetStats = StatusScreen_isShowNetStats == false;
}

// source: j/0/screens/statusscreen/statusscreen.c:3708  [anchor-strings]
void __cdecl StatusScreen_Open()
{
  unsigned __int16 BaseQTaskType; // ax
  __int16 v1; // ax
  unsigned __int16 v2; // si

  BaseQTaskType = QTask_GetBaseQTaskType();
  StatusScreen_eQTaskType = QTask_NewQTaskType("StatusScreen", 2156, BaseQTaskType, 0, 0);
  v1 = QTask_NewQTaskEventFn(0x200u, "StatusDisplay");
  v2 = StatusScreen_eQTaskType;
  StatusScreen_eStatusDisplayQTaskEvent = v1;
  QTask_LinkQTaskEventHandlerFn(StatusScreen_eQTaskType, 0, StatusScreen_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v2, 1, StatusScreen_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v2, 2, StatusScreen_DeleteHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v2, Screen_eDrawQTaskEvent, StatusScreen_DrawHandler);
  File_RegisterAlias("STATUSSCREEN:", "LOCAL:screens/game/status/");
  qmemcpy(
    StatusScreen_azQSpriteActivateIconPointer,
    StatusScreen_azQSpriteActivateIcon,
    sizeof(StatusScreen_azQSpriteActivateIconPointer));
  Symbol_Register(
    "netstats",
    StatusScreen_SetNetStatsCB,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
}

// source: j/0/screens/statusscreen/statusscreen.c:3749  [anchor-hash]
void __cdecl StatusScreen_Close()
{
  QTask_DeleteQTaskEvent(StatusScreen_eStatusDisplayQTaskEvent);
  StatusScreen_eStatusDisplayQTaskEvent = 512;
  QTask_DeleteQTaskType(StatusScreen_eQTaskType);
  Symbol_Remove("netstats");
  File_RemoveAlias("STATUSSCREEN:");
}
