/* j/0/computer/computermenu.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/computer/computermenu.c:114  [anchor-mhash]
void __cdecl ComputerMenu_TextItemActivateCB(
        struct MenuItem_s *ptMenuItem,
        struct MenuItemActivateContext_s *ptMenuItemActivateContext)
{
  struct QTask_s *v2; // eax

  if ( ptMenuItem->isActivated && !ptMenuItem->isActive )
    SoundSys_PlaySimpleSoundDefFn("mapcomp_05", 1u, nullptr);
  v2 = ComputerMenu_ptComputerMenuQTask;
  if ( LOBYTE(ComputerMenu_ptComputerMenuQTask[1].tQTaskChildren.ptMiddle) )
  {
    ptMenuItem->isActive = 0;
    ptMenuItem->isDisabled = 1;
  }
  else
  {
    ptMenuItem->isDisabled = 0;
    if ( ((int)v2[1].tQTaskRefList.ptHead & 0x10) != 0 )
    {
      SoundSys_PlaySimpleSoundDefFn("mapcomp_01", 1u, nullptr);
      switch ( ptMenuItemActivateContext->eMenuItem )
      {
        case 1:
          ComputerMenu_ptComputerMenuQTask[1].tQTaskRefList.ptTail = (struct QReference_s *)1;
          break;
        case 2:
          ComputerMenu_ptComputerMenuQTask[1].tQTaskRefList.ptTail = (struct QReference_s *)2;
          break;
        case 3:
          ComputerMenu_ptComputerMenuQTask[1].tQTaskRefList.ptTail = (struct QReference_s *)3;
          break;
        case 4:
          ComputerMenu_ptComputerMenuQTask[1].tQTaskRefList.ptTail = (struct QReference_s *)4;
          break;
        default:
          return;
      }
    }
  }
}

// source: j/0/computer/computermenu.c:161  [anchor-mhash]
void __cdecl ComputerMenu_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  double nHeight; // st7
  double v3; // st6

  nHeight = (double)Display_tActiveMode.nHeight;
  ComputerMenu_ptComputerMenuQTask = ptQTask;
  v3 = (double)Display_tActiveMode.nWidth * 0.5;
  ptQTask[1].ptNext = nullptr;
  LOBYTE(ptQTask[1].tQTaskChildren.ptMiddle) = 0;
  ptQTask[1].tQTaskChildren.ptTail = nullptr;
  *(float *)&ptQTask[1].ptPrev = v3;
  ptQTask[1].tQTaskRefList.ptHead = nullptr;
  ptQTask[1].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[1].tQTaskRefList.ptTail = nullptr;
  ptQTask[1].ptParent = nullptr;
  ComputerMenu_vMouseSpeedX = 0.0;
  *(float *)&ptQTask[1].tQTaskChildren.ptHead = nHeight * 0.5;
  ComputerMenu_vMouseSpeedY = 0.0;
}

// source: j/0/computer/computermenu.c:204  [anchor-caller]
void __cdecl ComputerMenu_RunHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { float nWidth; };
    struct { char igi2_o1[4]; float nHeight; };
    struct { char igi2_o2[8]; int v31; };
    struct { char igi2_o3[12]; float v32; };
    struct { char igi2_o4[16]; float v33; };
    struct { char igi2_o5[20]; int v34; };
    struct { char igi2_o6[28]; struct MenuItemInputContext_s ptMenuItemInputContext; };
    char igi2_extent[40];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *ptParent; // ebx
  unsigned int v2; // ebp
  struct QTask_s *FirstChildOfType; // eax
  double v5; // st7
  char ptMiddle; // al
  double v7; // st7
  double v8; // st6
  double v9; // st6
  struct QTask_s *ptNext; // eax
  struct QTask_s *v11; // eax
  struct QTask_s *v12; // eax
  struct QTask_s *v13; // eax
  struct QTask_s *v14; // eax
  struct QTask_s *v15; // eax
  struct QTask_s *ptHead; // edx
  struct QTask_s *v17; // eax
  struct QTask_s *v18; // eax
  double v19; // st7
  struct QTask_s *v20; // eax
  struct QTask_s *v21; // esi
  __int16 v22; // ax
  struct QReference_s *v23; // edx
  struct QTask_s *v24; // ecx
  int v25; // edx
  struct QTask_s *v26; // eax
  void (__cdecl *pfHandler)(struct QTask_s *); // eax
  int v28; // edx
  float ptQTaskb = *(float *)&ptQTask; // [esp+30h] [ebp+4h] ARGSLOT
  float ptQTaska = *(float *)&ptQTask; // [esp+30h] [ebp+4h] ARGSLOT

  ptParent = Computer_ptComputerQTask->ptParent;
  igi2_frame.nWidth = (float)Display_tActiveMode.nWidth;
  v2 = 0;
  igi2_frame.nHeight = (float)Display_tActiveMode.nHeight;
  igi2_frame.v34 = 0;
  igi2_frame.v31 = 0;
  if ( Game_ptGame && LOBYTE(Game_ptGame->pxSpritesResource) )
  {
    FirstChildOfType = QTask_GetFirstChildOfType(ptQTask, ComputerMap_eQTaskType);
    if ( FirstChildOfType )
      ((void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[1][FirstChildOfType->eQTaskType].pfHandler)(FirstChildOfType);
    return;
  }
  if ( ptQTask[1].tQTaskRefList.ptTail )
  {
    QTask_DeleteChildren(ptQTask);
    ComputerMenu_New((enum ComputerMenu_e)ptQTask[1].tQTaskRefList.ptTail);
    ptQTask[1].tQTaskRefList.ptTail = nullptr;
  }
  if ( Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tInputOptions.isInvertMouse )
    v5 = -1.0;
  else
    v5 = 1.0;
  ptMiddle = (char)ptQTask[1].tQTaskChildren.ptMiddle;
  ptQTaskb = *(float *)&ptParent[19].ptPrev + *(float *)&ptParent[19].ptPrev;
  ComputerMenu_vMouseSpeedX = ptQTaskb - ComputerMenu_vMouseSpeedX + ComputerMenu_vMouseSpeedX;
  ptQTaska = ComputerMenu_vMouseSpeedX;
  v7 = v5 * *(float *)&ptParent[19].tQTaskChildren.ptHead
     + v5 * *(float *)&ptParent[19].tQTaskChildren.ptHead
     - ComputerMenu_vMouseSpeedY
     + ComputerMenu_vMouseSpeedY;
  ComputerMenu_vMouseSpeedY = v7;
  if ( !ptMiddle )
  {
    igi2_frame.v32 = ComputerMenu_vMouseSpeedX * igi2_frame.nWidth * 0.5 + *(float *)&ptQTask[1].ptPrev;
    *(float *)&ptQTask[1].ptPrev = igi2_frame.v32;
    igi2_frame.v33 = v7 * igi2_frame.nHeight * 0.5 + *(float *)&ptQTask[1].tQTaskChildren.ptHead;
    *(float *)&ptQTask[1].tQTaskChildren.ptHead = igi2_frame.v33;
    v8 = igi2_frame.nWidth * 0.125;
    if ( v8 <= igi2_frame.v32 )
    {
      v8 = igi2_frame.nWidth - igi2_frame.nWidth * 0.109375;
      if ( v8 >= igi2_frame.v32 )
        v8 = igi2_frame.v32;
    }
    *(float *)&ptQTask[1].ptPrev = v8;
    v9 = igi2_frame.nHeight * 0.0833333358168602;
    if ( v9 <= igi2_frame.v33 )
    {
      v9 = igi2_frame.nHeight - igi2_frame.nHeight * 0.2083333283662796;
      if ( v9 >= igi2_frame.v33 )
        v9 = igi2_frame.v33;
    }
    *(float *)&ptQTask[1].tQTaskChildren.ptHead = v9;
    if ( ptQTaska != 0.0 || v7 != 0.0 )
    {
      ptNext = ComputerMenu_ptComputerMenuQTask[1].ptNext;
      v11 = ptNext ? ptNext->tQTaskChildren.ptHead : nullptr;
      if ( MenuItem_GetActiveMenuItem(v11) )
      {
        v12 = ComputerMenu_ptComputerMenuQTask[1].ptNext;
        if ( v12 )
          ptQTask[1].ptParent = (struct QTask_s *)MenuItem_GetActiveMenuItem(v12->tQTaskChildren.ptHead)->eMenuItem;
        else
          ptQTask[1].ptParent = (struct QTask_s *)MenuItem_GetActiveMenuItem(nullptr)->eMenuItem;
      }
    }
  }
  if ( (Mouse_tMouse.bButton & 1) != 0
    || (Keyboard_tKeyboard.anCurrentKey[28] & 0x80) != 0 && (Keyboard_tKeyboard.anPreviousKey[28] & 0x80) == 0 )
  {
    v2 = 16;
    if ( (Mouse_tMouse.bButton & 1) != 0 )
      igi2_frame.v34 = 1;
  }
  if ( (Mouse_tMouse.bButton & 2) != 0 )
    v2 |= 0x20u;
  if ( (Keyboard_tKeyboard.anCurrentKey[200] & 0x80) != 0 && (Keyboard_tKeyboard.anPreviousKey[200] & 0x80) == 0 )
  {
    v2 |= 1u;
    igi2_frame.v31 = 1;
  }
  if ( (Keyboard_tKeyboard.anCurrentKey[208] & 0x80) != 0 && (Keyboard_tKeyboard.anPreviousKey[208] & 0x80) == 0 )
  {
    v2 |= 2u;
    igi2_frame.v31 = 1;
  }
  if ( (Keyboard_tKeyboard.anCurrentKey[203] & 0x80) != 0 && (Keyboard_tKeyboard.anPreviousKey[203] & 0x80) == 0 )
  {
    v2 |= 4u;
    igi2_frame.v31 = 1;
  }
  if ( (Keyboard_tKeyboard.anCurrentKey[205] & 0x80) != 0 && (Keyboard_tKeyboard.anPreviousKey[205] & 0x80) == 0 )
  {
    v2 |= 8u;
LABEL_46:
    if ( ptQTask[1].ptParent )
    {
      v13 = ComputerMenu_ptComputerMenuQTask[1].ptNext;
      v14 = v13 ? v13->tQTaskChildren.ptHead : nullptr;
      if ( !MenuItem_GetActiveMenuItem(v14) )
      {
        v15 = ComputerMenu_ptComputerMenuQTask[1].ptNext;
        if ( v15 )
          ptHead = v15->tQTaskChildren.ptHead;
        else
          ptHead = nullptr;
        MenuItem_Activate(ptHead, (int)ptQTask[1].ptParent);
      }
    }
    goto LABEL_55;
  }
  if ( igi2_frame.v31 )
    goto LABEL_46;
LABEL_55:
  memset(&igi2_frame.ptMenuItemInputContext, 0, sizeof(igi2_frame.ptMenuItemInputContext));
  if ( igi2_frame.v34 )
  {
    v17 = ComputerMenu_ptComputerMenuQTask[1].ptNext;
    if ( v17 )
      v18 = v17->tQTaskChildren.ptHead;
    else
      v18 = nullptr;
    MenuItemQTask_SetMenuItemInput(v18, &igi2_frame.ptMenuItemInputContext);
  }
  v19 = *(float *)&ptQTask[1].ptPrev;
  igi2_frame.ptMenuItemInputContext.bButton = v2;
  igi2_frame.ptMenuItemInputContext.nMouseX = (__int64)v19;
  igi2_frame.ptMenuItemInputContext.nMouseY = (__int64)*(float *)&ptQTask[1].tQTaskChildren.ptHead;
  if ( (Keyboard_tKeyboard.anCurrentKey[29] & 0x80) != 0 || (Keyboard_tKeyboard.anCurrentKey[157] & 0x80) != 0 )
    igi2_frame.ptMenuItemInputContext.bButton = v2 & 0xFFFFFFF0;
  v20 = ComputerMenu_ptComputerMenuQTask[1].ptNext;
  if ( v20 )
    v21 = v20->tQTaskChildren.ptHead;
  else
    v21 = nullptr;
  v22 = MenuItemQTask_eMenuItemInputQTaskEvent;
  if ( MenuItemQTask_eMenuItemInputQTaskEvent == 512 )
  {
    v22 = QTask_NewQTaskEventFn(0, "MenuItem Input");
    MenuItemQTask_eMenuItemInputQTaskEvent = v22;
  }
  ((void (__cdecl *)(struct QTask_s *, struct MenuItemInputContext_s *))QTask_aatQTaskFinalEvent[v22][v21->eQTaskType].pfHandler)(
    v21,
    &igi2_frame.ptMenuItemInputContext);
  v23 = (struct QReference_s *)((int)ptQTask[1].tQTaskChildren.ptTail & ~v2);
  ptQTask[1].tQTaskRefList.ptHead = (struct QReference_s *)(v2 & ~(int)ptQTask[1].tQTaskChildren.ptTail);
  v24 = ptQTask->tQTaskChildren.ptHead;
  ptQTask[1].tQTaskRefList.ptMiddle = v23;
  ptQTask[1].tQTaskChildren.ptTail = (struct QTask_s *)v2;
  if ( v24->ptNext && v24 )
  {
    v25 = QTask_nProtectedQTaskStackOffset;
    do
    {
      if ( v24->ptNext )
        v26 = v24->ptNext->ptNext != nullptr ? v24->ptNext : nullptr;
      else
        v26 = nullptr;
      QTask_atProtectedQTaskStack[v25].ptQTask = v26;
      pfHandler = (void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[1][v24->eQTaskType].pfHandler;
      v28 = v25 + 1;
      QTask_nProtectedQTaskStackOffset = v28;
      if ( pfHandler )
      {
        pfHandler(v24);
        v28 = QTask_nProtectedQTaskStackOffset;
      }
      v24 = (struct QTask_s *)dword_849C7DC[v28];
      v25 = v28 - 1;
      QTask_nProtectedQTaskStackOffset = v25;
    }
    while ( v24 );
  }
}

// source: j/0/computer/computermenu.c:348  [anchor-mhash]
void __cdecl ComputerMenu_DeleteHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptNext; // eax

  ptNext = ptQTask[1].ptNext;
  if ( ptNext )
  {
    QReference_Delete((struct QReference_s *)ptNext, &QTask_tQTaskRefPool);
    ptQTask[1].ptNext = nullptr;
  }
  ComputerMenu_ptComputerMenuQTask = nullptr;
  ComputerMenu_eActiveMenu = COMPUTERMENU_NONE;
}

// source: j/0/computer/computermenu.c:368  [anchor-caller]
void __cdecl ComputerMenu_DrawHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { float vX; };
    struct { char igi2_o1[4]; float vY; };
    struct { char igi2_o2[8]; float vWidth; };
    struct { char igi2_o3[12]; float vHeight; };
    struct { char igi2_o4[40]; float nDisplayWidth; };
    struct { char igi2_o5[40]; float nDisplayWidtha; };
    struct { char igi2_o6[44]; float bFlags; };
    struct { char igi2_o7[44]; float bFlagsa; };
    struct { char igi2_o8[48]; int nDisplayHeight; };
    struct { char igi2_o9[52]; struct real32x2_t tPos; };
    char igi2_extent[60];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  char *v1; // ecx
  struct QTask_s *ptHead; // ecx
  int v3; // edx
  struct QTask_s *v4; // eax
  int v5; // esi
  void (__cdecl *pfHandler)(struct QTask_s *); // eax
  int v7; // edx
  struct QSprite_s *p_tQSpritePointerHand; // ecx
  struct QTask_s *ptPrev; // edx
  int nQAnimframes; // eax
  int v11; // eax
  struct Game_s *v12; // eax
  unsigned int v13; // ecx
  unsigned int v14; // edi
  int v15; // edx
  struct QTask_s *ptQTaskb = *(struct QTask_s * *)&ptQTask; // [esp+40h] [ebp+4h] ARGSLOT
  struct QTask_s *ptQTaska = *(struct QTask_s * *)&ptQTask; // [esp+40h] [ebp+4h] ARGSLOT
  float ptQTaskc = *(float *)&ptQTask; // [esp+40h] [ebp+4h] ARGSLOT

  igi2_frame.bFlags = (float)Display_tActiveMode.nHeight;
  igi2_frame.nDisplayWidth = (float)Display_tActiveMode.nWidth;
  igi2_frame.vHeight = igi2_frame.bFlags * 0.125;
  igi2_frame.vWidth = igi2_frame.nDisplayWidth * 0.15625;
  igi2_frame.vY = igi2_frame.bFlags * 0.675000011920929;
  igi2_frame.vX = igi2_frame.nDisplayWidth * 0.14374999701976776;
  QSprite_RegisterBlankZ(igi2_frame.vX, igi2_frame.vY, igi2_frame.vWidth, igi2_frame.vHeight, 80.0, 80.0, 80.0, 0xC0040000, -1, 542.47998046875);
  igi2_frame.nDisplayHeight = ComputerMenu_isBroken;
  RenderMode_tActiveRenderMode.apfRenderModeMethod[ComputerFilter_eRenderModeMethod](&igi2_frame.nDisplayHeight);
  if ( igi2_frame.nDisplayHeight != ComputerMenu_isBroken )
  {
    v1 = "mcbroken_02";
    if ( !dword_79EF4E4 )
      v1 = "mcbroken_01";
    SoundSys_PlaySimpleSoundFn(v1, 0, nullptr);
    dword_79EF4E4 = 1 - dword_79EF4E4;
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
      v5 = Screen_eDrawQTaskEvent;
      QTask_atProtectedQTaskStack[v3].ptQTask = v4;
      pfHandler = (void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[v5][ptHead->eQTaskType].pfHandler;
      v7 = v3 + 1;
      QTask_nProtectedQTaskStackOffset = v7;
      if ( pfHandler )
      {
        pfHandler(ptHead);
        v7 = QTask_nProtectedQTaskStackOffset;
      }
      ptHead = (struct QTask_s *)dword_849C7DC[v7];
      v3 = v7 - 1;
      QTask_nProtectedQTaskStackOffset = v3;
    }
    while ( ptHead );
  }
  p_tQSpritePointerHand = &ComputerMenu_tComputerMenuResource.tQSpritePointerHand;
  if ( !LOBYTE(ptQTask[1].tQTaskChildren.ptMiddle) )
    p_tQSpritePointerHand = &ComputerMenu_tComputerMenuResource.tQSpritePointer;
  ptPrev = ptQTask[1].ptPrev;
  LODWORD(igi2_frame.tPos.vY) = ptQTask[1].tQTaskChildren.ptHead;
  nQAnimframes = p_tQSpritePointerHand->nQAnimframes;
  LODWORD(igi2_frame.tPos.vX) = ptPrev;
  v11 = (int)&p_tQSpritePointerHand->atQAnimframe[nQAnimframes];
  ptQTaskb = (struct QTask_s *)*(__int16 *)(v11 + 14);
  igi2_frame.tPos.vX = *(float *)&ptPrev - (double)*(__int16 *)(v11 + 12) * 0.5;
  igi2_frame.tPos.vY = igi2_frame.tPos.vY - (double)(int)ptQTaskb * 0.5;
  QSprite_RegisterAZ(p_tQSpritePointerHand, igi2_frame.tPos.vX, igi2_frame.tPos.vY, 128.0, 128.0, 128.0, 1.0, 512.47998046875, 0, 0x400C0000u, -1);
  QSprite_Register4AZ(
    &ComputerMenu_tComputerMenuResource.tQSpriteOverlay,
    0.0,
    0.0,
    igi2_frame.nDisplayWidth,
    0.0,
    0.0,
    igi2_frame.bFlags,
    igi2_frame.nDisplayWidth,
    igi2_frame.bFlags,
    128.0,
    128.0,
    128.0,
    1.0,
    512.47998046875,
    0,
    0x410C0000u,
    -1);
  v12 = Game_ptGame;
  v13 = (Game_ptGame->tDrawRandomState.anRandom[0] >> 7)
      ^ Game_ptGame->tDrawRandomState.anRandom[2]
      ^ Game_ptGame->tDrawRandomState.anRandom[1];
  v14 = v13 + Game_ptGame->tDrawRandomState.anRandom[0];
  Game_ptGame->tDrawRandomState.anRandom[2] ^= Game_ptGame->tDrawRandomState.anRandom[0] >> 7;
  v12->tDrawRandomState.anRandom[1] = v13;
  v12->tDrawRandomState.anRandom[0] = v14;
  v15 = (int)(v14 % 0xC) % 12;
  ptQTaska = (struct QTask_s *)v15;
  dword_79EEF14 = v14 % 0xC + 1;
  if ( v15 >= 6 )
    ptQTaska = (struct QTask_s *)(12 - v15);
  ptQTaskc = ((double)(int)ptQTaska * 0.013333332724869251 + 0.30000001192092896) * 128.0;
  *(float *)&igi2_frame.nDisplayHeight = igi2_frame.bFlags * 0.9333333373069763;
  igi2_frame.tPos.vX = igi2_frame.nDisplayWidth * 0.3187499940395355;
  igi2_frame.nDisplayWidtha = igi2_frame.nDisplayWidth * 0.21875;
  igi2_frame.bFlagsa = igi2_frame.bFlags * 0.800000011920929;
  QSprite_Register4AZ(
    &ComputerMenu_tComputerMenuResource.tQSpriteGlow,
    igi2_frame.nDisplayWidtha,
    igi2_frame.bFlagsa,
    igi2_frame.tPos.vX,
    igi2_frame.bFlagsa,
    igi2_frame.nDisplayWidtha,
    *(float *)&igi2_frame.nDisplayHeight,
    igi2_frame.tPos.vX,
    *(float *)&igi2_frame.nDisplayHeight,
    ptQTaskc,
    ptQTaskc,
    ptQTaskc,
    1.0,
    1.0,
    0,
    (unsigned int)&MTP_atLODVirModel[45].atBoneVertexRefs[20].atVertexRefs[783],
    -1);
}

// source: j/0/computer/computermenu.c:535  [anchor-hash]
void __cdecl ComputerMenu_Open()
{
  unsigned __int16 BaseQTaskType; // ax
  unsigned __int16 v1; // si

  BaseQTaskType = QTask_GetBaseQTaskType();
  v1 = QTask_NewQTaskType("ComputerMenu", 76, BaseQTaskType, 0, 0);
  ComputerMenu_eQTaskType = v1;
  QTask_LinkQTaskEventHandlerFn(v1, 0, (void (__cdecl *)(struct QTask_s *, void *))ComputerMenu_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 1, ComputerMenu_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 2, ComputerMenu_DeleteHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, Screen_eDrawQTaskEvent, ComputerMenu_DrawHandler);
  File_RegisterAlias("COMPUTER:", "LOCAL:computer/");
}

// source: j/0/computer/computermenu.c:558  [anchor-strings]
void __cdecl ComputerMenu_Close()
{
  QTask_DeleteQTaskType(ComputerMenu_eQTaskType);
  File_RemoveAlias("COMPUTER:");
}

// source: j/0/computer/computermenu.c:575  [anchor-hash]
void __cdecl ComputerMenu_New(enum ComputerMenu_e eComputerMenu)
{
  struct QTask_s *v1; // edi

  v1 = ComputerMenu_ptComputerMenuQTask;
  ComputerMenu_eActiveMenu = eComputerMenu;
  if ( !ComputerMenu_ptComputerMenuQTask )
  {
    QTask_NewFn(Game_ptGame->ptGameScreenQTask[1].ptPrev, ComputerMenu_eQTaskType, nullptr);
    v1 = ComputerMenu_ptComputerMenuQTask;
  }
  switch ( eComputerMenu )
  {
    case COMPUTERMENU_MAP:
      if ( ComputerPlan_ptComputerPlanVector->tPrivate.nElements )
        QTask_NewFn(v1, ComputerPlanMenu_eQTaskType, nullptr);
      else
        QTask_NewFn(v1, ComputerMap_eQTaskType, nullptr);
      break;
    case COMPUTERMENU_OBJECTIVES:
      QTask_NewFn(v1, ComputerObjectives_eQTaskType, nullptr);
      break;
    case COMPUTERMENU_LOG:
      QTask_NewFn(v1, ComputerLog_eQTaskType, nullptr);
      break;
    case COMPUTERMENU_SAVE:
      QTask_NewFn(v1, ComputerSaveMenu_eQTaskType, nullptr);
      break;
    default:
      LDebug_Error("No New function for menu!!");
      abort();
  }
}

// source: j/0/computer/computermenu.c:631  [anchor-hash]
enum bool __cdecl ComputerMenu_GotoMenu(enum ComputerMenu_e eComputerMenu)
{
  if ( ComputerMenu_eActiveMenu == eComputerMenu )
    return true;
  if ( eComputerMenu == COMPUTERMENU_MAP && !Computer_isEnabled )
    return ComputerMenu_eActiveMenu == COMPUTERMENU_OBJECTIVES;
  ComputerMenu_ptComputerMenuQTask[1].tQTaskRefList.ptTail = (struct QReference_s *)eComputerMenu;
  return false;
}

// source: j/0/computer/computermenu.c:653  [size]
struct QTask_s *__cdecl ComputerMenu_GetComputerMenuQTask()
{
  return ComputerMenu_ptComputerMenuQTask;
}

// source: j/0/computer/computermenu.c:666  [size]
struct ComputerMenu_t *__cdecl ComputerMenu_GetComputerMenu()
{
  return (struct ComputerMenu_t *)ComputerMenu_ptComputerMenuQTask;
}

// source: j/0/computer/computermenu.c:681  [anchor-hash]
struct QTask_s *__cdecl ComputerMenu_GetMenuItemQTask()
{
  struct QTask_s *ptNext; // eax

  ptNext = ComputerMenu_ptComputerMenuQTask[1].ptNext;
  if ( ptNext )
    return ptNext->tQTaskChildren.ptHead;
  else
    return nullptr;
}

// source: j/0/computer/computermenu.c:697  [anchor-mhash]
void __cdecl ComputerMenu_SetMenuItemQTask(struct QTask_s *ptMenuItemQTask)
{
  struct QTask_s *ptNext; // eax
  struct QTask_s *v2; // esi

  ptNext = ComputerMenu_ptComputerMenuQTask[1].ptNext;
  v2 = ComputerMenu_ptComputerMenuQTask + 1;
  if ( ptNext )
  {
    QReference_Delete((struct QReference_s *)ptNext, &QTask_tQTaskRefPool);
    v2->ptNext = nullptr;
  }
  if ( ptMenuItemQTask )
    v2->ptNext = (struct QTask_s *)QTask_NewQTaskRef(ptMenuItemQTask);
}

// source: j/0/computer/computermenu.c:717  [anchor-refs]
void __cdecl ComputerMenu_LoadComputerMenuResource()
{
  char *v0; // ecx
  int v1; // eax
  void *v2; // eax
  void *v3; // eax
  char *v4; // ecx
  unsigned int v5; // eax
  void *v6; // eax
  void *v7; // eax
  char *v8; // ecx
  unsigned int v9; // eax
  void *v10; // eax
  void *v11; // eax
  struct QSprite_s *atQSpriteHilight; // edi
  int v13; // esi
  char zFilename[4]; // [esp+8h] [ebp-4h] BYREF

  if ( Resource_IsLoadedInternal("COMPUTER:computer.res", (struct Resource_s **)zFilename) )
  {
    v1 = *(_DWORD *)zFilename;
    *(_DWORD *)(*(_DWORD *)zFilename + 44) = 1;
    v2 = *(void **)(v1 + 52);
  }
  else
  {
    Game_MPRunNetwork(v0);
    v3 = File_Load("COMPUTER:computer.res", (unsigned int *)zFilename);
    if ( !v3 )
    {
      LDebug_Error("Failed to load resource: '%s'", "COMPUTER:computer.res");
      goto LABEL_5;
    }
    v2 = Resource_ParseFile(File_zLastSubstitutedPath, v3, *(unsigned int *)zFilename);
  }
  ComputerMenu_tComputerMenuResource.pxMenusResource = v2;
  if ( Resource_IsLoadedInternal("LANGUAGE:computer.res", (struct Resource_s **)zFilename) )
  {
    v5 = *(_DWORD *)zFilename;
    *(_DWORD *)(*(_DWORD *)zFilename + 44) = 1;
    v6 = *(void **)(v5 + 52);
  }
  else
  {
    Game_MPRunNetwork(v4);
    v7 = File_Load("LANGUAGE:computer.res", (unsigned int *)zFilename);
    if ( !v7 )
    {
      LDebug_Error("Failed to load resource: '%s'", "LANGUAGE:computer.res");
      goto LABEL_5;
    }
    v6 = Resource_ParseFile(File_zLastSubstitutedPath, v7, *(unsigned int *)zFilename);
  }
  ComputerMenu_tComputerMenuResource.pxLanguageResource = v6;
  if ( Resource_IsLoadedInternal("LANGUAGE:objectives.res", (struct Resource_s **)zFilename) )
  {
    v9 = *(_DWORD *)zFilename;
    *(_DWORD *)(*(_DWORD *)zFilename + 44) = 1;
    v10 = *(void **)(v9 + 52);
    goto LABEL_17;
  }
  Game_MPRunNetwork(v8);
  v11 = File_Load("LANGUAGE:objectives.res", (unsigned int *)zFilename);
  if ( !v11 )
  {
    LDebug_Error("Failed to load resource: '%s'", "LANGUAGE:objectives.res");
LABEL_5:
    abort();
  }
  v10 = Resource_ParseFile(File_zLastSubstitutedPath, v11, *(unsigned int *)zFilename);
LABEL_17:
  ComputerMenu_tComputerMenuResource.pxObjectivesResource = v10;
  if ( Game_ptGame->ptMission->iID == 17 )
  {
    QSprite_Load(&ComputerMenu_tComputerMenuResource.tQSpriteOverlay, "COMPUTER:overlay_broken.spr");
    ComputerMenu_isBroken = 1;
  }
  else
  {
    QSprite_Load(&ComputerMenu_tComputerMenuResource.tQSpriteOverlay, "COMPUTER:overlay.spr");
    ComputerMenu_isBroken = 0;
  }
  ComputerMenu_tComputerMenuResource.ptQSpriteFont3 = FontManager_LoadFont("LOCAL:common/fonts/font1.fnt");
  ComputerMenu_tComputerMenuResource.ptQSpriteFont2 = FontManager_LoadFont("LOCAL:common/fonts/font2.fnt");
  ComputerMenu_tComputerMenuResource.ptQSpriteFont1 = FontManager_LoadFont("LOCAL:common/fonts/font3.fnt");
  ComputerMenu_tComputerMenuResource.ptQSpriteFont4 = FontManager_LoadFont("LOCAL:common/fonts/font4.fnt");
  QSprite_Load(&ComputerMenu_tComputerMenuResource.tQSpriteBattery, "COMPUTER:battery.spr");
  QSprite_Load(&ComputerMenu_tComputerMenuResource.tQSpriteGlow, "COMPUTER:glowsprite.spr");
  QSprite_Load(&ComputerMenu_tComputerMenuResource.tQSpritePointer, "COMPUTER:pointer.spr");
  QSprite_Load(&ComputerMenu_tComputerMenuResource.tQSpritePointerHand, "COMPUTER:pointer_hand.spr");
  QSprite_Load(&ComputerMenu_tComputerMenuResource.tQSpriteArrow1_1, "COMPUTER:arrow1_1.spr");
  QSprite_Load(&ComputerMenu_tComputerMenuResource.tQSpriteArrow1_2, "COMPUTER:arrow1_2.spr");
  QSprite_Load(&ComputerMenu_tComputerMenuResource.tQSpriteArrow1_3, "COMPUTER:arrow1_3.spr");
  QSprite_Load(&ComputerMenu_tComputerMenuResource.tQSpriteArrow2_1, "COMPUTER:arrow2_1.spr");
  QSprite_Load(&ComputerMenu_tComputerMenuResource.tQSpriteArrow2_2, "COMPUTER:arrow2_2.spr");
  QSprite_Load(&ComputerMenu_tComputerMenuResource.tQSpriteArrow2_3, "COMPUTER:arrow2_3.spr");
  QSprite_Load(&ComputerMenu_tComputerMenuResource.tQSpriteArrow3_1, "COMPUTER:arrow3_1.spr");
  QSprite_Load(&ComputerMenu_tComputerMenuResource.tQSpriteArrow3_2, "COMPUTER:arrow3_2.spr");
  QSprite_Load(&ComputerMenu_tComputerMenuResource.tQSpriteArrow3_3, "COMPUTER:arrow3_3.spr");
  QSprite_Load(&ComputerMenu_tComputerMenuResource.tQSpriteArrow4_1, "COMPUTER:arrow4_1.spr");
  QSprite_Load(&ComputerMenu_tComputerMenuResource.tQSpriteArrow4_2, "COMPUTER:arrow4_2.spr");
  QSprite_Load(&ComputerMenu_tComputerMenuResource.tQSpriteArrow4_3, "COMPUTER:arrow4_3.spr");
  QSprite_Load(&ComputerMenu_tComputerMenuResource.tQSpriteArrowUp_1, "COMPUTER:arrowup_1.spr");
  QSprite_Load(&ComputerMenu_tComputerMenuResource.tQSpriteArrowUp_2, "COMPUTER:arrowup_2.spr");
  QSprite_Load(&ComputerMenu_tComputerMenuResource.tQSpriteArrowUp_3, "COMPUTER:arrowup_3.spr");
  QSprite_Load(&ComputerMenu_tComputerMenuResource.tQSpriteArrowDown_1, "COMPUTER:arrowdown_1.spr");
  QSprite_Load(&ComputerMenu_tComputerMenuResource.tQSpriteArrowDown_2, "COMPUTER:arrowdown_2.spr");
  QSprite_Load(&ComputerMenu_tComputerMenuResource.tQSpriteArrowDown_3, "COMPUTER:arrowdown_3.spr");
  QSprite_Load(&ComputerMenu_tComputerMenuResource.tQSpritePlus_1, "COMPUTER:plus_1.spr");
  QSprite_Load(&ComputerMenu_tComputerMenuResource.tQSpritePlus_2, "COMPUTER:plus_2.spr");
  QSprite_Load(&ComputerMenu_tComputerMenuResource.tQSpritePlus_3, "COMPUTER:plus_3.spr");
  QSprite_Load(&ComputerMenu_tComputerMenuResource.tQSpriteMinus_1, "COMPUTER:minus_1.spr");
  QSprite_Load(&ComputerMenu_tComputerMenuResource.tQSpriteMinus_2, "COMPUTER:minus_2.spr");
  QSprite_Load(&ComputerMenu_tComputerMenuResource.tQSpriteMinus_3, "COMPUTER:minus_3.spr");
  QSprite_Load(&ComputerMenu_tComputerMenuResource.tQSpriteSphere_1, "COMPUTER:sphere_1.spr");
  QSprite_Load(&ComputerMenu_tComputerMenuResource.tQSpriteSphere_2, "COMPUTER:sphere_2.spr");
  QSprite_Load(&ComputerMenu_tComputerMenuResource.tQSpriteSphere_3, "COMPUTER:sphere_3.spr");
  QSprite_Load(&ComputerMenu_tComputerMenuResource.tQSpriteObjective_1, "COMPUTER:objective_1.spr");
  QSprite_Load(&ComputerMenu_tComputerMenuResource.tQSpriteObjective_2, "COMPUTER:objective_2.spr");
  QSprite_Load(&ComputerMenu_tComputerMenuResource.tQSpriteHUD1, "COMPUTER:hud_1.spr");
  QSprite_Load(&ComputerMenu_tComputerMenuResource.tQSpriteHUD2, "COMPUTER:hud_2.spr");
  QSprite_Load(&ComputerMenu_tComputerMenuResource.tQSpriteCompass, "COMPUTER:compass.spr");
  atQSpriteHilight = ComputerMenu_tComputerMenuResource.atQSpriteHilight;
  v13 = 0;
  do
  {
    QSprite_Load(atQSpriteHilight, ComputerMenu_azSpriteHilight[v13]);
    ComputerMenu_tComputerMenuResource.azQSpriteHilight[v13] = ComputerMenu_azSpriteHilight[v13];
    ++atQSpriteHilight;
    ++v13;
  }
  while ( (int)atQSpriteHilight < 127857812 );
}

// source: j/0/computer/computermenu.c:804  [size]
void __cdecl ComputerMenu_FreeComputerMenuResource()
{
  struct QSprite_s *atQSpriteHilight; // ebx
  struct Resource_s *ptHead; // edx
  struct Resource_s *ptNext; // eax
  struct Resource_s *v3; // ecx
  unsigned int nType; // eax
  struct Resource_s *v5; // eax
  struct Resource_s *v6; // ecx
  unsigned int v7; // eax
  struct Resource_s *v8; // eax
  struct Resource_s *v9; // ecx
  unsigned int v10; // eax

  atQSpriteHilight = ComputerMenu_tComputerMenuResource.atQSpriteHilight;
  do
    QSprite_DeAlloc(atQSpriteHilight++);
  while ( (int)atQSpriteHilight < 127857812 );
  QSprite_DeAlloc(&ComputerMenu_tComputerMenuResource.tQSpriteCompass);
  QSprite_DeAlloc(&ComputerMenu_tComputerMenuResource.tQSpriteBattery);
  QSprite_DeAlloc(&ComputerMenu_tComputerMenuResource.tQSpriteGlow);
  QSprite_DeAlloc(&ComputerMenu_tComputerMenuResource.tQSpritePointer);
  QSprite_DeAlloc(&ComputerMenu_tComputerMenuResource.tQSpritePointerHand);
  QSprite_DeAlloc(&ComputerMenu_tComputerMenuResource.tQSpriteArrow1_1);
  QSprite_DeAlloc(&ComputerMenu_tComputerMenuResource.tQSpriteArrow1_2);
  QSprite_DeAlloc(&ComputerMenu_tComputerMenuResource.tQSpriteArrow1_3);
  QSprite_DeAlloc(&ComputerMenu_tComputerMenuResource.tQSpriteArrow2_1);
  QSprite_DeAlloc(&ComputerMenu_tComputerMenuResource.tQSpriteArrow2_2);
  QSprite_DeAlloc(&ComputerMenu_tComputerMenuResource.tQSpriteArrow2_3);
  QSprite_DeAlloc(&ComputerMenu_tComputerMenuResource.tQSpriteArrow3_1);
  QSprite_DeAlloc(&ComputerMenu_tComputerMenuResource.tQSpriteArrow3_2);
  QSprite_DeAlloc(&ComputerMenu_tComputerMenuResource.tQSpriteArrow3_3);
  QSprite_DeAlloc(&ComputerMenu_tComputerMenuResource.tQSpriteArrow4_1);
  QSprite_DeAlloc(&ComputerMenu_tComputerMenuResource.tQSpriteArrow4_2);
  QSprite_DeAlloc(&ComputerMenu_tComputerMenuResource.tQSpriteArrow4_3);
  QSprite_DeAlloc(&ComputerMenu_tComputerMenuResource.tQSpriteArrowUp_1);
  QSprite_DeAlloc(&ComputerMenu_tComputerMenuResource.tQSpriteArrowUp_2);
  QSprite_DeAlloc(&ComputerMenu_tComputerMenuResource.tQSpriteArrowUp_3);
  QSprite_DeAlloc(&ComputerMenu_tComputerMenuResource.tQSpriteArrowDown_1);
  QSprite_DeAlloc(&ComputerMenu_tComputerMenuResource.tQSpriteArrowDown_2);
  QSprite_DeAlloc(&ComputerMenu_tComputerMenuResource.tQSpriteArrowDown_3);
  QSprite_DeAlloc(&ComputerMenu_tComputerMenuResource.tQSpritePlus_1);
  QSprite_DeAlloc(&ComputerMenu_tComputerMenuResource.tQSpritePlus_2);
  QSprite_DeAlloc(&ComputerMenu_tComputerMenuResource.tQSpritePlus_3);
  QSprite_DeAlloc(&ComputerMenu_tComputerMenuResource.tQSpriteMinus_1);
  QSprite_DeAlloc(&ComputerMenu_tComputerMenuResource.tQSpriteMinus_2);
  QSprite_DeAlloc(&ComputerMenu_tComputerMenuResource.tQSpriteMinus_3);
  QSprite_DeAlloc(&ComputerMenu_tComputerMenuResource.tQSpriteSphere_1);
  QSprite_DeAlloc(&ComputerMenu_tComputerMenuResource.tQSpriteSphere_2);
  QSprite_DeAlloc(&ComputerMenu_tComputerMenuResource.tQSpriteSphere_3);
  QSprite_DeAlloc(&ComputerMenu_tComputerMenuResource.tQSpriteObjective_1);
  QSprite_DeAlloc(&ComputerMenu_tComputerMenuResource.tQSpriteObjective_2);
  QSprite_DeAlloc(&ComputerMenu_tComputerMenuResource.tQSpriteHUD1);
  QSprite_DeAlloc(&ComputerMenu_tComputerMenuResource.tQSpriteHUD2);
  FontManager_DeleteFont(ComputerMenu_tComputerMenuResource.ptQSpriteFont1);
  FontManager_DeleteFont(ComputerMenu_tComputerMenuResource.ptQSpriteFont2);
  FontManager_DeleteFont(ComputerMenu_tComputerMenuResource.ptQSpriteFont3);
  FontManager_DeleteFont(ComputerMenu_tComputerMenuResource.ptQSpriteFont4);
  QSprite_DeAlloc(&ComputerMenu_tComputerMenuResource.tQSpriteOverlay);
  ptHead = Resource_tResourceList.ptHead;
  ptNext = Resource_tResourceList.ptHead->ptNext;
  v3 = Resource_tResourceList.ptHead;
  if ( Resource_tResourceList.ptHead->ptNext )
  {
    while ( v3->pxData != ComputerMenu_tComputerMenuResource.pxLanguageResource )
    {
      v3 = ptNext;
      ptNext = ptNext->ptNext;
      if ( !ptNext )
        goto LABEL_10;
    }
    nType = v3->nType;
    if ( nType != 3 && nType != 1 )
    {
      Resource_Remove(v3);
      ptHead = Resource_tResourceList.ptHead;
    }
  }
LABEL_10:
  v5 = ptHead->ptNext;
  v6 = ptHead;
  if ( ptHead->ptNext )
  {
    while ( v6->pxData != ComputerMenu_tComputerMenuResource.pxObjectivesResource )
    {
      v6 = v5;
      v5 = v5->ptNext;
      if ( !v5 )
        goto LABEL_17;
    }
    v7 = v6->nType;
    if ( v7 != 3 && v7 != 1 )
    {
      Resource_Remove(v6);
      ptHead = Resource_tResourceList.ptHead;
    }
  }
LABEL_17:
  v8 = ptHead->ptNext;
  v9 = ptHead;
  if ( ptHead->ptNext )
  {
    while ( v9->pxData != ComputerMenu_tComputerMenuResource.pxMenusResource )
    {
      v9 = v8;
      v8 = v8->ptNext;
      if ( !v8 )
        return;
    }
    v10 = v9->nType;
    if ( v10 != 3 && v10 != 1 )
      Resource_Remove(v9);
  }
}

// source: j/0/computer/computermenu.c:885  [size]
struct ComputerMenuResource_t *__cdecl ComputerMenu_GetComputerMenuResource()
{
  return &ComputerMenu_tComputerMenuResource;
}

// source: j/0/computer/computermenu.c:898  [size]
void __cdecl ComputerMenu_RequestMenu(enum ComputerMenu_e eComputerMenu)
{
  ComputerMenu_ptComputerMenuQTask[1].tQTaskRefList.ptTail = (struct QReference_s *)eComputerMenu;
}

// source: j/0/computer/computermenu.c:915  [size]
unsigned int __cdecl ComputerMenu_GetCurrentButton()
{
  return (unsigned int)ComputerMenu_ptComputerMenuQTask[1].tQTaskChildren.ptTail;
}

// source: j/0/computer/computermenu.c:931  [size]
unsigned int __cdecl ComputerMenu_GetEdgeButton()
{
  return (unsigned int)ComputerMenu_ptComputerMenuQTask[1].tQTaskRefList.ptHead;
}

// source: j/0/computer/computermenu.c:948  [size]
unsigned int __cdecl ComputerMenu_GetEdgeReleaseButton()
{
  return (unsigned int)ComputerMenu_ptComputerMenuQTask[1].tQTaskRefList.ptMiddle;
}

// source: j/0/computer/computermenu.c:964  [anchor-hash]
void __cdecl ComputerMenu_InvalidateButtons()
{
  struct QTask_s *v0; // eax

  v0 = ComputerMenu_ptComputerMenuQTask;
  ComputerMenu_ptComputerMenuQTask[1].tQTaskRefList.ptHead = nullptr;
  v0[1].tQTaskRefList.ptMiddle = nullptr;
}

// source: j/0/computer/computermenu.c:981  [anchor-strings]
struct QTask_s *__cdecl ComputerMenu_CreateScreenMenuItems(
        struct MenuItem_s **pptFirstMenuItem,
        struct MenuItem_s **pptLastMenuItem,
        struct QTask_s *ptParent,
        enum ComputerMenu_e eForWhichScreen)
{
  #pragma pack(push, 1)
  union
  {
    struct { float eLinkDown; };
    struct { float eLinkDowna; };
    struct { float eLinkDownb; };
    struct { float eLinkDownc; };
    struct { char igi2_o4[4]; float eLinkLeft; };
    struct { char igi2_o5[4]; float eLinkLefta; };
    struct { char igi2_o6[4]; float eLinkLeftb; };
    struct { char igi2_o7[4]; float eLinkLeftc; };
    struct { char igi2_o8[44]; float v43; };
    struct { char igi2_o9[48]; struct QTask_s *ptQTask; };
    struct { char igi2_o10[52]; float v45; };
    struct { char igi2_o11[56]; float nWidth; };
    struct { char igi2_o12[60]; char *isDisabled; };
    struct { char igi2_o13[60]; char *isDisableda; };
    struct { char igi2_o14[64]; _DWORD v49[7]; };
    char igi2_extent[92];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *v4; // eax
  struct QTask_s *v5; // ebx
  double nHeight; // st7
  struct QTask_s *ptNext; // eax
  struct QTask_s *ptHead; // eax
  struct QTask_s *v9; // esi
  struct QTask_s *v10; // eax
  struct MenuItem_s *v11; // edx
  struct QTask_s *v12; // ebp
  int ptMiddle; // esi
  struct QTask_s *v14; // ecx
  char *LocalizedStringForLanguage; // esi
  struct QSprite_s *Font; // ebx
  struct QTask_s *v17; // edi
  struct QTask_s *v18; // ecx
  struct QTask_s *v19; // ebx
  struct QSprite_s *v20; // ebx
  struct QTask_s *v21; // edi
  struct QTask_s *v22; // ecx
  struct QTask_s *v23; // ebx
  struct QSprite_s *v24; // ebx
  struct QTask_s *v25; // edi
  struct QTask_s *v26; // ecx
  struct QTask_s *v27; // ebx
  struct QSprite_s *v28; // ebx
  struct QTask_s *v29; // edi
  int eMenuItem; // eax
  int v31; // eax
  int v32; // edx
  int eQTaskType; // ecx
  char *ptParenta = *(char * *)&eForWhichScreen; // [esp+68h] [ebp+Ch] ARGSLOT

  v4 = ComputerMenu_ptComputerMenuQTask;
  v5 = nullptr;
  igi2_frame.nWidth = (float)Display_tActiveMode.nWidth;
  nHeight = (double)Display_tActiveMode.nHeight;
  ComputerMenu_ptComputerMenuQTask[1].tQTaskRefList.ptHead = nullptr;
  v4[1].tQTaskRefList.ptMiddle = nullptr;
  ptNext = v4[1].ptNext;
  igi2_frame.v45 = nHeight;
  igi2_frame.v43 = 0.7583333253860474;
  if ( !ptNext || (ptHead = ptNext->tQTaskChildren.ptHead) == nullptr )
  {
    ptHead = QTask_NewFn(ptParent, MenuItemQTask_eQTaskType, nullptr);
    ptHead[1].tQTaskChildren.ptMiddle = nullptr;
    ptHead[1].tQTaskChildren.ptTail = nullptr;
    ptHead[1].tQTaskRefList.ptHead = nullptr;
    ptHead[1].tQTaskRefList.ptMiddle = nullptr;
    ptHead[1].tQTaskRefList.ptTail = nullptr;
    ptHead[1].ptParent = nullptr;
    *(_DWORD *)&ptHead[1].eQTaskType = 0;
  }
  v9 = ComputerMenu_ptComputerMenuQTask + 1;
  igi2_frame.ptQTask = ptHead;
  v10 = ComputerMenu_ptComputerMenuQTask[1].ptNext;
  if ( v10 )
  {
    QReference_Delete((struct QReference_s *)v10, &QTask_tQTaskRefPool);
    v9->ptNext = nullptr;
  }
  if ( igi2_frame.ptQTask )
    v9->ptNext = (struct QTask_s *)QTask_NewQTaskRef(igi2_frame.ptQTask);
  v11 = nullptr;
  v12 = nullptr;
  ptMiddle = 0;
  if ( eForWhichScreen != COMPUTERMENU_SAVE && Game_eGameMode == GAME_GAMEMODE_SINGLEPLAYER )
  {
    v14 = Game_ptGame->ptGameScreenQTask[1].tQTaskChildren.ptHead;
    if ( v14 )
      v5 = v14->tQTaskChildren.ptHead;
    LocalizedStringForLanguage = Config_GetLocalizedStringForLanguage(
                                   "computer/IGI HQ",
                                   Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eLanguage,
                                   true);
    Font = MenuManager_GetFont(v5, (char *)&g_zFontName_1);
    igi2_frame.eLinkLeft = igi2_frame.v45 * 0.7583333253860474;
    v17 = QTask_NewFn(igi2_frame.ptQTask, ComputerTextItem_eQTaskType, nullptr);
    igi2_frame.eLinkDown = igi2_frame.nWidth * 0.15625;
    ComputerTextItem_Init(
      v17,
      4,
      0,
      0,
      0,
      0,
      false,
      igi2_frame.eLinkDown,
      igi2_frame.eLinkLeft,
      Font,
      LocalizedStringForLanguage,
      COMPUTERMENU_COLOR_GREEN,
      COMPUTERMENU_COLOR_LIGHT_GREEN,
      ComputerMenu_TextItemActivateCB);
    ptMiddle = (int)v17[1].tQTaskRefList.ptMiddle;
    v11 = (struct MenuItem_s *)v17;
    igi2_frame.v43 = 0.7249999642372131;
    v12 = v17;
  }
  if ( eForWhichScreen != COMPUTERMENU_MAP && Computer_isEnabled )
  {
    if ( v11 )
    {
      v11->eLinkLeft = 1;
      v11->eLinkUp = 1;
    }
    v18 = Game_ptGame->ptGameScreenQTask[1].tQTaskChildren.ptHead;
    if ( v18 )
      v19 = v18->tQTaskChildren.ptHead;
    else
      v19 = nullptr;
    igi2_frame.isDisabled = Config_GetLocalizedStringForLanguage(
                   "computer/MAP",
                   Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eLanguage,
                   true);
    v20 = MenuManager_GetFont(v19, (char *)&g_zFontName_1);
    igi2_frame.eLinkLefta = igi2_frame.v43 * igi2_frame.v45;
    v21 = QTask_NewFn(igi2_frame.ptQTask, ComputerTextItem_eQTaskType, nullptr);
    igi2_frame.eLinkDowna = igi2_frame.nWidth * 0.15625;
    ComputerTextItem_Init(
      v21,
      1,
      0,
      ptMiddle,
      0,
      ptMiddle,
      false,
      igi2_frame.eLinkDowna,
      igi2_frame.eLinkLefta,
      v20,
      igi2_frame.isDisabled,
      COMPUTERMENU_COLOR_GREEN,
      COMPUTERMENU_COLOR_LIGHT_GREEN,
      ComputerMenu_TextItemActivateCB);
    ptMiddle = (int)v21[1].tQTaskRefList.ptMiddle;
    igi2_frame.v43 = igi2_frame.v43 - 0.03333333507180214;
    v11 = (struct MenuItem_s *)v21;
    if ( !v12 )
      v12 = v21;
  }
  if ( eForWhichScreen != COMPUTERMENU_OBJECTIVES )
  {
    if ( v11 )
    {
      v11->eLinkLeft = 2;
      v11->eLinkUp = 2;
    }
    v22 = Game_ptGame->ptGameScreenQTask[1].tQTaskChildren.ptHead;
    if ( v22 )
      v23 = v22->tQTaskChildren.ptHead;
    else
      v23 = nullptr;
    igi2_frame.isDisableda = Config_GetLocalizedStringForLanguage(
                    "computer/OBJECTIVES",
                    Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eLanguage,
                    true);
    v24 = MenuManager_GetFont(v23, (char *)&g_zFontName_1);
    igi2_frame.eLinkLeftb = igi2_frame.v43 * igi2_frame.v45;
    v25 = QTask_NewFn(igi2_frame.ptQTask, ComputerTextItem_eQTaskType, nullptr);
    igi2_frame.eLinkDownb = igi2_frame.nWidth * 0.15625;
    ComputerTextItem_Init(
      v25,
      2,
      0,
      ptMiddle,
      0,
      ptMiddle,
      false,
      igi2_frame.eLinkDownb,
      igi2_frame.eLinkLeftb,
      v24,
      igi2_frame.isDisableda,
      COMPUTERMENU_COLOR_GREEN,
      COMPUTERMENU_COLOR_LIGHT_GREEN,
      ComputerMenu_TextItemActivateCB);
    ptMiddle = (int)v25[1].tQTaskRefList.ptMiddle;
    igi2_frame.v43 = igi2_frame.v43 - 0.03333333507180214;
    v11 = (struct MenuItem_s *)v25;
    if ( !v12 )
      v12 = v25;
  }
  if ( eForWhichScreen == COMPUTERMENU_LOG )
  {
LABEL_38:
    if ( !v12 )
      goto LABEL_42;
    goto LABEL_39;
  }
  if ( v11 )
  {
    v11->eLinkLeft = 3;
    v11->eLinkUp = 3;
  }
  v26 = Game_ptGame->ptGameScreenQTask[1].tQTaskChildren.ptHead;
  if ( v26 )
    v27 = v26->tQTaskChildren.ptHead;
  else
    v27 = nullptr;
  ptParenta = Config_GetLocalizedStringForLanguage(
                (char *)&g_zFontName_1.tQTaskChildren.ptMiddle,
                Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eLanguage,
                true);
  v28 = MenuManager_GetFont(v27, (char *)&g_zFontName_1);
  igi2_frame.eLinkLeftc = igi2_frame.v43 * igi2_frame.v45;
  v29 = QTask_NewFn(igi2_frame.ptQTask, ComputerTextItem_eQTaskType, nullptr);
  igi2_frame.eLinkDownc = igi2_frame.nWidth * 0.15625;
  ComputerTextItem_Init(
    v29,
    3,
    0,
    ptMiddle,
    0,
    ptMiddle,
    false,
    igi2_frame.eLinkDownc,
    igi2_frame.eLinkLeftc,
    v28,
    ptParenta,
    COMPUTERMENU_COLOR_GREEN,
    COMPUTERMENU_COLOR_LIGHT_GREEN,
    ComputerMenu_TextItemActivateCB);
  v11 = (struct MenuItem_s *)v29;
  if ( !v12 )
  {
    v12 = v29;
    goto LABEL_38;
  }
LABEL_39:
  if ( v11 && v12 != (struct QTask_s *)v11 )
  {
    eMenuItem = v11->eMenuItem;
    v12[2].ptNext = (struct QTask_s *)eMenuItem;
    v12[1].ptParent = (struct QTask_s *)eMenuItem;
    v31 = (int)v12[1].tQTaskRefList.ptMiddle;
    v11->eLinkLeft = v31;
    v11->eLinkUp = v31;
  }
LABEL_42:
  if ( ComputerMenu_ptComputerMenuQTask )
    ComputerMenu_ptComputerMenuQTask[1].ptParent = (struct QTask_s *)v12[1].tQTaskRefList.ptMiddle;
  if ( pptFirstMenuItem )
    *pptFirstMenuItem = v11;
  if ( pptLastMenuItem )
    *pptLastMenuItem = (struct MenuItem_s *)v12;
  v32 = v11->eMenuItem;
  memset(igi2_frame.v49, 0, sizeof(igi2_frame.v49));
  eQTaskType = igi2_frame.ptQTask->eQTaskType;
  igi2_frame.v49[0] = v32;
  ((void (__cdecl *)(struct QTask_s *, _DWORD *))QTask_aatQTaskFinalEvent[MenuItem_eActivateQTaskEvent][eQTaskType].pfHandler)(
    igi2_frame.ptQTask,
    igi2_frame.v49);
  return igi2_frame.ptQTask;
}
