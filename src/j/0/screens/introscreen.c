/* j/0/screens/introscreen.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/screens/introscreen.c:103  [anchor-mhash]
int __cdecl Introscreen_WinProcCB(
        struct HWND__ *hWnd,
        unsigned int nMessage,
        unsigned int wParam,
        int lParam)
{
  if ( nMessage == 6 && HIWORD(wParam) && IntroScreen_ptIntroScreen )
    IntroScreen_ptIntroScreen->isBreak = true;
  return 1;
}

// source: j/0/screens/introscreen.c:132  [size]
void __cdecl IntroScreen_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct ClippingRect_s tClippingRect; };
    struct { char igi2_o1[24]; struct DisplayMode_s tDisplayMode; };
    char igi2_extent[320];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QReference_s *v2; // eax
  int v3; // edx
  char *v4; // ecx
  char *v5; // ecx

  ptQTask[1].ptPrev = nullptr;
  ptQTask[1].ptNext = *(struct QTask_s **)pxContext;
  ptQTask[1].tQTaskChildren.ptHead = *((struct QTask_s **)pxContext + 1);
  ptQTask[3].tQTaskRefList.ptHead = nullptr;
  ptQTask[3].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[1].tQTaskChildren.ptMiddle = nullptr;
  v2 = *((struct QReference_s **)pxContext + 2);
  IntroScreen_ptIntroScreen = (struct IntroScreen_s *)ptQTask;
  ptQTask[3].tQTaskRefList.ptTail = v2;
  if ( v2 != (struct QReference_s *)1 )
  {
    v3 = 2752 * Config_tConfig.iActiveProfile + 7392072;
    memset(&igi2_frame.tDisplayMode, 0, sizeof(igi2_frame.tDisplayMode));
    v4 = (char *)(2752 * Config_tConfig.iActiveProfile + 7392400);
    igi2_frame.tDisplayMode.nWidth = 640;
    igi2_frame.tDisplayMode.nHeight = 480;
    igi2_frame.tDisplayMode.nBitsPerPixel = 16;
    igi2_frame.tDisplayMode.nBackBuffers = 1;
    igi2_frame.tDisplayMode.eRenderMode = Direct3D_eRenderMode;
    igi2_frame.tDisplayMode.isZBuffer = 1;
    igi2_frame.tDisplayMode.isCleared = 1;
    if ( 2752 * Config_tConfig.iActiveProfile == -7392400 )
      v4 = (char *)&g_zInitialValue;
    strcpy(igi2_frame.tDisplayMode.zDeviceDescription, v4);
    v5 = (char *)(v3 + 72);
    if ( v3 == -72 )
      v5 = (char *)&g_zInitialValue;
    strcpy(igi2_frame.tDisplayMode.zDeviceIdentifier, v5);
    Display_SetMode(&igi2_frame.tDisplayMode);
  }
  igi2_frame.tClippingRect.vWidth = (float)Display_tActiveMode.nWidth;
  igi2_frame.tClippingRect.vX = 0.0;
  igi2_frame.tClippingRect.vY = 0.0;
  igi2_frame.tClippingRect.vHeight = (float)Display_tActiveMode.nHeight;
  RenderContext_Alloc((struct RenderContext_s *)&ptQTask[1].tQTaskRefList, 1);
  RenderContext_SetClippingRect((struct RenderContext_s *)&ptQTask[1].tQTaskRefList, &igi2_frame.tClippingRect);
  Main_RegisterWinProcCallback((int (__cdecl *)(struct HWND__ *, unsigned int, unsigned int, int))Introscreen_WinProcCB);
}

// source: j/0/screens/introscreen.c:199  [anchor-strings]
void __cdecl IntroScreen_RunHandler(struct QTask_s *ptQTask)
{
  int v1; // ebp
  int v2; // eax
  struct QTask_s *ptPrev; // eax
  struct QTask_s *ptTail; // edi
  struct QReference_s *ptMiddle; // ecx
  int v6; // edx
  struct StaticTilemap_s *v7; // eax
  char zPath[256]; // [esp+14h] [ebp-100h] BYREF

  v1 = 0;
  v2 = ptQTask[3].tQTaskRefList.ptTail != nullptr ? 1230 : 90;
  if ( ptQTask[1].tQTaskChildren.ptTail )
  {
    PlayLoop();
    Real_nTempCW = igi2_fpu_or(0xC00u);
    if ( g_bContinue )
      goto LABEL_4;
    goto LABEL_3;
  }
  ptTail = ptQTask[3].tQTaskChildren.ptTail;
  if ( ptTail )
  {
    ptMiddle = ptQTask[3].tQTaskRefList.ptMiddle;
    if ( (int)ptMiddle >= 30 )
    {
      if ( (int)ptMiddle < v2 )
      {
        ptQTask[3].tQTaskRefList.ptHead = (struct QReference_s *)128;
LABEL_23:
        if ( (int)ptQTask[3].tQTaskRefList.ptHead < 0 )
        {
          v1 = 1;
        }
        else
        {
          *(float *)&ptTail->tQTaskRefList.ptHead = (float)(int)ptQTask[3].tQTaskRefList.ptHead;
          *(float *)&ptQTask[3].tQTaskChildren.ptTail->tQTaskRefList.ptMiddle = (float)(int)ptQTask[3].tQTaskRefList.ptHead;
          *(float *)&ptQTask[3].tQTaskChildren.ptTail->tQTaskRefList.ptTail = (float)(int)ptQTask[3].tQTaskRefList.ptHead;
        }
        ++*(int *)&ptQTask[3].tQTaskRefList.ptMiddle;
        goto LABEL_4;
      }
      v6 = ((v2 - (int)ptMiddle + 30) << 7) / 30;
    }
    else
    {
      v6 = ((_DWORD)ptMiddle << 7) / 30;
    }
    ptQTask[3].tQTaskRefList.ptHead = (struct QReference_s *)v6;
    goto LABEL_23;
  }
LABEL_3:
  v1 = 1;
LABEL_4:
  if ( (Keyboard_tKeyboard.anCurrentKey[1] & 0x80u) != 0 || ptQTask[1].tQTaskChildren.ptMiddle )
    goto LABEL_32;
  if ( v1 )
  {
    if ( ptQTask[3].tQTaskChildren.ptTail )
    {
      Picture_Delete((struct StaticTilemap_s *)ptQTask[3].tQTaskChildren.ptTail);
      ptQTask[3].tQTaskChildren.ptTail = nullptr;
    }
    if ( ptQTask[1].tQTaskChildren.ptTail )
    {
      Movie_End();
      ptQTask[1].tQTaskChildren.ptTail = nullptr;
    }
    ptPrev = ptQTask[1].ptPrev;
    if ( (int)ptPrev < (int)ptQTask[1].ptNext )
    {
      sprintf(
        zPath,
        "%s%s/%s",
        "LOCAL:screens/intro/",
        (char *)(16 * Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eLanguage
                     + 6828784),
        *((char **)&ptQTask[1].tQTaskChildren.ptHead->ptNext + (_DWORD)ptPrev));
      if ( !Resource_Exists(zPath) )
        sprintf(
          zPath,
          (char *const)&g_zFileName.aptSelectableItems[28],
          "LOCAL:screens/intro/",
          *((_DWORD *)&ptQTask[1].tQTaskChildren.ptHead->ptNext + (int)ptQTask[1].ptPrev));
      Resource_Exists(zPath);
      if ( strstr(zPath, ".avi") )
      {
        ptQTask[1].tQTaskChildren.ptTail = (struct QTask_s *)Movie_Begin(zPath);
      }
      else
      {
        ptQTask[3].tQTaskRefList.ptMiddle = nullptr;
        ptQTask[3].tQTaskRefList.ptHead = nullptr;
        v7 = Picture_Load(zPath);
        ptQTask[3].tQTaskChildren.ptTail = (struct QTask_s *)v7;
        if ( v7 )
        {
          v7->vR = (float)(int)ptQTask[3].tQTaskRefList.ptHead;
          *(float *)&ptQTask[3].tQTaskChildren.ptTail->tQTaskRefList.ptMiddle = (float)(int)ptQTask[3].tQTaskRefList.ptHead;
          *(float *)&ptQTask[3].tQTaskChildren.ptTail->tQTaskRefList.ptTail = (float)(int)ptQTask[3].tQTaskRefList.ptHead;
        }
      }
      ++*(int *)&ptQTask[1].ptPrev;
    }
  }
  if ( !ptQTask[1].tQTaskChildren.ptTail && !ptQTask[3].tQTaskChildren.ptTail )
  {
LABEL_32:
    Flow_ptFlow->eRequestedEvent = 8 * (ptQTask[3].tQTaskRefList.ptTail == (struct QReference_s *)2) + 3;
    QTask_Delete(ptQTask);
  }
}

// source: j/0/screens/introscreen.c:334  [anchor-mhash]
void __cdecl IntroScreen_DrawHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptTail; // esi
  unsigned __int16 *pxObject; // eax
  float vY; // [esp+0h] [ebp-18h]
  float vWidth; // [esp+4h] [ebp-14h]

  qmemcpy(&RenderContext_tActiveRenderContext, &ptQTask[1].tQTaskRefList, sizeof(RenderContext_tActiveRenderContext));
  ++RenderContext_nActiveRenderContextTimeStamp;
  ptQTask[1].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[1].tQTaskRefList.ptHead = nullptr;
  List_AddTail(&ptQTask[1].tQTaskRefList.ptHead, (int)&RenderContext_tDrawList);
  ptTail = ptQTask[3].tQTaskChildren.ptTail;
  if ( ptTail )
  {
    vWidth = (float)Display_tActiveMode.nHeight;
    vY = (float)Display_tActiveMode.nWidth;
    Q3DPicture_RegisterSize((struct StaticTilemap_s *)ptTail, 0.0, 0.0, vY, vWidth, -1);
  }
  if ( Game_ptMissionScoreScreenQTaskRef )
  {
    pxObject = (unsigned __int16 *)Game_ptMissionScoreScreenQTaskRef->pxObject;
    if ( pxObject )
      ((void (__cdecl *)(unsigned __int16 *))QTask_aatQTaskFinalEvent[Screen_eDrawQTaskEvent][pxObject[18]].pfHandler)(pxObject);
  }
}

// source: j/0/screens/introscreen.c:364  [size]
void __cdecl IntroScreen_DeleteHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *pxObject; // eax
  struct WinProcCBNode_s *ptHead; // eax
  struct WinProcCBNode_s *ptNext; // ecx

  if ( Game_ptMissionScoreScreenQTaskRef )
  {
    pxObject = (struct QTask_s *)Game_ptMissionScoreScreenQTaskRef->pxObject;
    if ( pxObject )
      QTask_Delete(pxObject);
  }
  RenderContext_DeAlloc((struct RenderContext_s *)&ptQTask[1].tQTaskRefList);
  if ( ptQTask[3].tQTaskChildren.ptTail )
    Picture_Delete((struct StaticTilemap_s *)ptQTask[3].tQTaskChildren.ptTail);
  if ( ptQTask[1].tQTaskChildren.ptTail )
  {
    if ( pMC )
      pMC->lpVtbl->Stop(pMC);
    g_bContinue = 0;
    CleanupInterfaces();
    Real_nTempCW = igi2_fpu_or(0xC00u);
  }
  ptHead = Main_tWinProcCBList.ptHead;
  ptNext = Main_tWinProcCBList.ptHead->ptNext;
  if ( Main_tWinProcCBList.ptHead->ptNext )
  {
    while ( (int (__cdecl *)(struct HWND__ *, unsigned int, unsigned int, int))ptHead->pfWinProcCB != Introscreen_WinProcCB )
    {
      ptHead = ptNext;
      ptNext = ptNext->ptNext;
      if ( !ptNext )
      {
        IntroScreen_ptIntroScreen = nullptr;
        return;
      }
    }
    Node_Remove(ptHead)[2] = nullptr;
  }
  IntroScreen_ptIntroScreen = nullptr;
}

// source: j/0/screens/introscreen.c:400  [anchor-hash]
void __cdecl IntroScreen_Open()
{
  unsigned __int16 BaseQTaskType; // ax
  unsigned __int16 v1; // si

  BaseQTaskType = QTask_GetBaseQTaskType();
  v1 = QTask_NewQTaskType("IntroScreen", 152, BaseQTaskType, 0, 0);
  IntroScreen_eQTaskType = v1;
  QTask_LinkQTaskEventHandlerFn(v1, 0, IntroScreen_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 1, IntroScreen_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 2, IntroScreen_DeleteHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, Screen_eDrawQTaskEvent, IntroScreen_DrawHandler);
}

// source: j/0/screens/introscreen.c:424  [size]
void __cdecl IntroScreen_Close()
{
  QTask_DeleteQTaskType(IntroScreen_eQTaskType);
}

// source: j/0/screens/introscreen.c:438  [size]
unsigned __int16 __cdecl IntroScreen_GetQTaskType()
{
  return IntroScreen_eQTaskType;
}

// source: j/0/screens/introscreen.c:452  [anchor-strings]
struct QTask_s *__cdecl IntroScreen_New(
        struct QTask_s *ptParent,
        enum IntroScreenMode_e eShowMode,
        char isLoop)
{
  struct IntroScreenCreateContext_s tIntroScreenCreateContext; // [esp+0h] [ebp-Ch] BYREF

  if ( eShowMode )
  {
    if ( eShowMode == INTROSCREENMODE_OUTRO )
    {
      tIntroScreenCreateContext.ppzMovieSequence = IntroScreen_azOutroMoviesToPlay;
      tIntroScreenCreateContext.nMovies = 1;
    }
    else
    {
      if ( eShowMode != INTROSCREENMODE_QUIT )
      {
        LDebug_Error("Invalid introscreen mode");
        abort();
      }
      tIntroScreenCreateContext.ppzMovieSequence = IntroScreen_azQuitMoviesToPlay;
      tIntroScreenCreateContext.nMovies = 1;
    }
  }
  else
  {
    tIntroScreenCreateContext.ppzMovieSequence = IntroScreen_azIntroMoviesToPlay;
    tIntroScreenCreateContext.nMovies = 2;
  }
  tIntroScreenCreateContext.eShowMode = eShowMode;
  return QTask_NewFn(ptParent, IntroScreen_eQTaskType, &tIntroScreenCreateContext);
}
