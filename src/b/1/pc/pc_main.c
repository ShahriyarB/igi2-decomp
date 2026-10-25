/* b/1/pc/pc_main.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: b/1/pc/pc_main.c:93  [size]
void __cdecl Main_ParsePasswordCB(char *zArg)
{
  Main_isRun[0] = 1;
}

// source: b/1/pc/pc_main.c:106  [size]
void __cdecl Main_ParseFullScreenCB(char *zArg)
{
  AppContext_tAppContext.isActive = true;
}

// source: b/1/pc/pc_main.c:119  [size]
void __cdecl Main_ParseWindowCB(char *zArg)
{
  AppContext_tAppContext.isActive = false;
}

// source: b/1/pc/pc_main.c:132  [size]
void __cdecl Main_ParseSmallCB(char *zArg)
{
  AppContext_isFixmeSmall = 1;
}

// source: b/1/pc/pc_main.c:145  [size]
void __cdecl Main_ParseDebugCB(char *zArg)
{
  AppContext_tAppContext.isDebugtext = true;
}

// source: b/1/pc/pc_main.c:210  [size]
void __cdecl Main_ParseWinInputCB(char *zArg)
{
  AppContext_tAppContext.isGermany = true;
}

// source: b/1/pc/pc_main.c:236  [size]
void __cdecl Main_ParseEditorCB(char *zArg)
{
  AppContext_tAppContext.isFullscreen = true;
}

// source: b/1/pc/pc_main.c:275  [size]
void __cdecl Main_ParseServerCB(char *zArg)
{
  AppContext_tAppContext.isDrawingDisabled = true;
}

// source: b/1/pc/pc_main.c:289  [anchor-hash]
void __cdecl Main_ParseServerDedicatedCB(char *zArg)
{
  AppContext_tAppContext.isServer = true;
  AppContext_tAppContext.isMainMenu = true;
  AppContext_tAppContext.isFullscreen = false;
}

void __cdecl sub_404120(char *String)
{
  AppContext_tAppContext.nPort = atoi(String);
}

void __cdecl sub_404140(char *Source)
{
  strncpy(AppContext_tAppContext.zIP, Source, 0x10u);
}

void __cdecl sub_404160(char *Source)
{
  strncpy(AppContext_tAppContext.zPlayer, Source, 0x40u);
}

void __cdecl sub_404180(char *Source)
{
  strncpy(AppContext_tAppContext.zPassword, Source, 0x40u);
}

void __cdecl pfParseCmdLineArg__(char *String)
{
  AppContext_tAppContext.nTrack = atoi(String);
}

void __cdecl sub_4041C0(char *String)
{
  AppContext_tAppContext.isClient = (atoi(String) == 2) + 1;
}

// source: b/1/pc/pc_main.c:437  [anchor-refs]
int __stdcall Main_WindowProc(struct HWND__ *tHwnd, unsigned int nMessage, unsigned int wParam, int lParam)
{
  struct WinProcCBNode_s *ptHead; // eax
  struct WinProcCBNode_s *ptNext; // esi

  if ( Main_isContinue )
  {
    ptHead = Main_tWinProcCBList.ptHead;
    ptNext = Main_tWinProcCBList.ptHead->ptNext;
    if ( Main_tWinProcCBList.ptHead->ptNext )
    {
      while ( ptHead->pfWinProcCB(tHwnd, nMessage, wParam, lParam) )
      {
        ptHead = ptNext;
        ptNext = ptNext->ptNext;
        if ( !ptNext )
          goto LABEL_5;
      }
      return 0;
    }
  }
LABEL_5:
  if ( nMessage <= 0x104 )
  {
    if ( nMessage == 260 )
    {
      if ( wParam == 115 )
      {
        if ( dword_834E22C )
        {
          PostMessageA(AppContext_tAppContext.hWnd, 2u, 0, 0);
          return 0;
        }
      }
      else if ( wParam == 18 )
      {
        dword_834E22C = 1;
        return 0;
      }
      return 0;
    }
    if ( nMessage != 1 )
    {
      if ( nMessage == 2 )
      {
        Main_isContinue = 0;
        return 0;
      }
      if ( nMessage == 28 )
      {
        Real_nTempCW = igi2_fpu_or(0xC00u);
        return 0;
      }
      return DefWindowProcA(tHwnd, nMessage, wParam, lParam);
    }
    return 0;
  }
  if ( nMessage == 261 )
  {
    if ( wParam == 18 )
      dword_834E22C = 0;
    return 0;
  }
  if ( nMessage != 274 )
    return DefWindowProcA(tHwnd, nMessage, wParam, lParam);
  if ( (wParam & 0xFFF0) == 0xF140 )
    return 1;
  else
    return DefWindowProcA(tHwnd, 0x112u, wParam, lParam);
}

// source: b/1/pc/pc_main.c:516  [size]
void __cdecl Main_SetContinueStatus(char isContinue)
{
  Main_isContinue = isContinue;
}

// source: b/1/pc/pc_main.c:529  [anchor-strings]
void __cdecl Main_RegisterWinProcCallback(int (__cdecl *pfCB_)(struct HWND__ *, unsigned int, unsigned int, int))
{
  int v1; // ecx
  int (__cdecl **p_pfWinProcCB)(struct HWND__ *, unsigned int, unsigned int, int); // eax
  int v3; // eax
  struct WinProcCBNode_s *v4; // eax

  v1 = 0;
  p_pfWinProcCB = &Main_atWinProcCB[0].pfWinProcCB;
  while ( *p_pfWinProcCB )
  {
    p_pfWinProcCB += 3;
    ++v1;
    if ( (int)p_pfWinProcCB >= 7079720 )
    {
      LDebug_Error("Failed to register WinProc callback.");
      abort();
    }
  }
  v3 = v1;
  Main_atWinProcCB[v3].pfWinProcCB = pfCB_;
  Main_atWinProcCB[v3].ptPrev = nullptr;
  v4 = &Main_atWinProcCB[v1];
  v4->ptNext = nullptr;
  List_AddTail(v4, (int)&Main_tWinProcCBList);
}

// source: b/1/pc/pc_main.c:556  [anchor-mhash]
void __cdecl Main_RemoveWinProcCallback(
        int (__cdecl *pfCB_)(struct HWND__ *, unsigned int, unsigned int, int))
{
  struct WinProcCBNode_s *ptHead; // eax
  struct WinProcCBNode_s *ptNext; // ecx

  ptHead = Main_tWinProcCBList.ptHead;
  ptNext = Main_tWinProcCBList.ptHead->ptNext;
  if ( Main_tWinProcCBList.ptHead->ptNext )
  {
    while ( ptHead->pfWinProcCB != pfCB_ )
    {
      ptHead = ptNext;
      ptNext = ptNext->ptNext;
      if ( !ptNext )
        return;
    }
    Node_Remove(ptHead)[2] = nullptr;
  }
}

// source: b/1/pc/pc_main.c:589  [anchor-caller]
int __stdcall WinMain(struct HINSTANCE__ *hInstance, struct HINSTANCE__ *hPrevInstance, char *lpCmdLine, int nCmdShow)
{
  #pragma pack(push, 1)
  union
  {
    struct { int v10; };
    struct { char igi2_o1[44]; HWND hMutex; };
    struct { char igi2_o2[48]; HANDLE hObject; };
    struct { char igi2_o3[64]; WNDCLASSA WndClass; };
    struct { char igi2_o4[104]; struct tagMSG Msg; };
    struct { char igi2_o5[132]; CHAR Text[1024]; };
    char igi2_extent[1156];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  DWORD v5; // esi
  int SystemMetrics; // eax
  struct HWND__ *Window; // esi
  WPARAM wParam; // edi
  char *v9; // ecx

  AppContext_tAppContext.zCmdLine = lpCmdLine;
  AppContext_tAppContext.isServer = false;
  AppMain_FindPrefix(lpCmdLine, "ServerDedicated", (void (__cdecl *)(char *))Main_ParseServerDedicatedCB);
  if ( AppContext_tAppContext.isServer
    || (igi2_frame.hObject = CreateMutexA(nullptr, 1, "InnerloopGameMUTEX")) != nullptr
    && GetLastError() != 183
    && GetLastError() != 6 )
  {
    CoInitialize(nullptr);
    igi2_frame.hMutex = GetForegroundWindow();
    igi2_frame.WndClass.style = 3;
    igi2_frame.WndClass.lpfnWndProc = Main_WindowProc;
    igi2_frame.WndClass.cbClsExtra = 0;
    igi2_frame.WndClass.cbWndExtra = 0;
    igi2_frame.WndClass.hInstance = hInstance;
    igi2_frame.WndClass.hIcon = LoadIconA(hInstance, (LPCSTR)0x7F00);
    igi2_frame.WndClass.hCursor = LoadCursorA(nullptr, (LPCSTR)0x7F00);
    igi2_frame.WndClass.lpszMenuName = lpClassName_6bc190;
    igi2_frame.WndClass.lpszClassName = lpClassName_6bc190;
    igi2_frame.WndClass.hbrBackground = (HBRUSH)7;
    RegisterClassA(&igi2_frame.WndClass);
    AppContext_tAppContext.hInstance = hInstance;
    AppContext_tAppContext.zCfgFileName = "filesys.cfg";
    AppContext_tAppContext.zApplicationName = "Innerloop";
    if ( AppContext_tAppContext.hWnd )
      SetWindowTextA(AppContext_tAppContext.hWnd, "Innerloop");
    AppContext_tAppContext.isDebugged = true;
    if ( AppContext_tAppContext.pfActivateCallback )
      AppContext_tAppContext.pfActivateCallback(true, AppContext_tAppContext.pxActivateCallbackContext);
    AppContext_tAppContext.isActive = true;
    AppContext_tAppContext.isDebugtext = false;
    AppContext_tAppContext.isTerrainLightmapsDisabled = true;
    AppContext_tAppContext.isQVMOnly = false;
    AppContext_tAppContext.isWinMessageInput = true;
    AppContext_tAppContext.isLightmapsDisabled = true;
    AppContext_tAppContext.isClient = false;
    AppContext_tAppContext.isGermany = false;
    AppContext_tAppContext.isDrawingDisabled = false;
    AppContext_tAppContext.isEditorState = true;
    AppContext_tAppContext.nPort = -1;
    strncpy(AppContext_tAppContext.zIP, (char *)&g_zInitialValue, 0x10u);
    strncpy(AppContext_tAppContext.zPlayer, "MR_NOT_NAMED", 0x40u);
    AppContext_tAppContext.isFullscreen = false;
    memset(Main_atWinProcCB, 0, sizeof(Main_atWinProcCB));
    Main_tWinProcCBList.ptHead = (struct WinProcCBNode_s *)&Main_tWinProcCBList.ptMiddle;
    Main_tWinProcCBList.ptTail = (struct WinProcCBNode_s *)&Main_tWinProcCBList;
    Main_tWinProcCBList.ptMiddle = nullptr;
    AppMain_FindPrefix(AppContext_tAppContext.zCmdLine, "Window", (void (__cdecl *)(char *))Main_ParseWindowCB);
    AppMain_FindPrefix(
      AppContext_tAppContext.zCmdLine,
      "WinInput",
      (void (__cdecl *)(char *))Main_ParseWinInputCB);
    AppMain_FindPrefix(AppContext_tAppContext.zCmdLine, "Track", (void (__cdecl *)(char *))pfParseCmdLineArg__);
    AppMain_FindPrefix(AppContext_tAppContext.zCmdLine, "Editor", (void (__cdecl *)(char *))Main_ParseEditorCB);
    AppMain_FindPrefix(AppContext_tAppContext.zCmdLine, "Server", (void (__cdecl *)(char *))Main_ParseServerCB);
    AppMain_FindPrefix(AppContext_tAppContext.zCmdLine, "Port", (void (__cdecl *)(char *))sub_404120);
    AppMain_FindPrefix(AppContext_tAppContext.zCmdLine, "IP", (void (__cdecl *)(char *))sub_404140);
    AppMain_FindPrefix(AppContext_tAppContext.zCmdLine, "Player", (void (__cdecl *)(char *))sub_404160);
    AppMain_FindPrefix(AppContext_tAppContext.zCmdLine, "Password", (void (__cdecl *)(char *))sub_404180);
    AppMain_FindPrefix(AppContext_tAppContext.zCmdLine, "Zbias", (void (__cdecl *)(char *))sub_4041C0);
    if ( AppContext_tAppContext.isServer == false && GetDXVersion() < 0x801 )
    {
      sprintf(igi2_frame.Text, "This application requires DirectX version %d.%d or greater to run.", 8, 1);
      MessageBoxA(nullptr, igi2_frame.Text, "Error", 0x10u);
      exit__crt0dat(1);
    }
    Main_dwWindowStyle = 281935872;
    Main_dwFullscreenWindowStyle = -1777860608;
    v5 = AppContext_tAppContext.isActive != false ? -1777860608 : 281935872;
    igi2_frame.v10 = (GetSystemMetrics(1) - 1080) / 2;
    SystemMetrics = GetSystemMetrics(0);
    Window = CreateWindowExA(
               0,
               lpClassName_6bc190,
               lpClassName_6bc190,
               v5,
               (SystemMetrics - 1920) / 2,
               igi2_frame.v10,
               1920,
               1080,
               nullptr,
               nullptr,
               hInstance,
               nullptr);
    if ( Window )
    {
      ShowCursor(0);
      ShowWindow(Window, 10);
      AppContext_tAppContext.hWnd = Window;
      Real_nTempCW = igi2_fpu_or(0xC00u);
      Main_isContinue = App_Open();
      CPU_TestCPU();
      if ( Main_isContinue )
      {
        while ( 1 )
        {
          Real_nTempCW = igi2_fpu_or(0xC00u);
          App_Run();
          if ( AppContext_tAppContext.isServer )
          {
            Sleep(0);
          }
          else if ( AppContext_tAppContext.isDebugged == false )
          {
            Sleep(2u);
          }
          if ( !Main_isContinue )
            DestroyWindow(Window);
          if ( PeekMessageA(&igi2_frame.Msg, nullptr, 0, 0, 0) )
            break;
LABEL_25:
          if ( !Main_isContinue )
            goto LABEL_26;
        }
        while ( GetMessageA(&igi2_frame.Msg, nullptr, 0, 0) )
        {
          TranslateMessage(&igi2_frame.Msg);
          DispatchMessageA(&igi2_frame.Msg);
          if ( !PeekMessageA(&igi2_frame.Msg, nullptr, 0, 0, 0) )
            goto LABEL_25;
        }
        wParam = igi2_frame.Msg.wParam;
        Main_isContinue = 0;
      }
      else
      {
LABEL_26:
        wParam = 0;
      }
      ShowCursor(1);
      App_Close(v9);
      SetForegroundWindow(igi2_frame.hMutex);
      UnregisterClassA(lpClassName_6bc190, hInstance);
      CoUninitialize();
      if ( AppContext_tAppContext.isServer == false )
      {
        ReleaseMutex(igi2_frame.hObject);
        CloseHandle(igi2_frame.hObject);
      }
      return wParam;
    }
    else
    {
      MessageBoxA(nullptr, "Couldn't open window", "Innerloop", 0);
      return 0;
    }
  }
  else
  {
    MessageBoxA(nullptr, "InnerloopGame is already running.", "Error", 0x10u);
    return 0;
  }
}
