/* app.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: app.c:80  [anchor-hash]
char *__cdecl GetFilenameFromCommandLine(char *a1)
{
  char *v1; // eax

  if ( *a1 == 34 )
  {
    v1 = a1 + 1;
    if ( a1[1] )
    {
      do
      {
        if ( *v1 == 34 )
          break;
        *(v1 - 1) = *v1;
      }
      while ( *++v1 );
    }
    *(v1 - 1) = 0;
    return a1;
  }
  else
  {
    strtok(a1, (char *)&Delimiter);
    return a1;
  }
}

// source: app.c:115  [anchor-strings]
char *CheckForSaveGame()
{
  #pragma pack(push, 1)
  union
  {
    struct { int v10; };
    struct { char igi2_o1[4]; int v11; };
    struct { char igi2_o2[8]; int v12; };
    struct { char igi2_o3[12]; _BYTE v13[3]; };
    struct { char igi2_o4[15]; char v14; };
    struct { char igi2_o5[16]; CHAR PathName[260]; };
    struct { char igi2_o6[276]; char Dir[256]; };
    struct { char igi2_o7[532]; CHAR Filename[260]; };
    char igi2_extent[792];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  char *result; // eax
  char *zCmdLine; // eax
  int v2; // edx
  char v3; // cl
  char *FilenameFromCommandLine; // eax
  int i; // ecx
  char v6; // dl
  unsigned int v7; // eax
  char *v8; // edi

  result = strstr(AppContext_tAppContext.zCmdLine, ".igi2save");
  if ( result )
  {
    zCmdLine = AppContext_tAppContext.zCmdLine;
    v2 = g_a1_0 - AppContext_tAppContext.zCmdLine;
    do
    {
      v3 = *zCmdLine;
      zCmdLine[v2] = *zCmdLine;
      ++zCmdLine;
    }
    while ( v3 );
    FilenameFromCommandLine = GetFilenameFromCommandLine(g_a1_0);
    for ( i = strlen(FilenameFromCommandLine); i >= 0; --i )
    {
      v6 = FilenameFromCommandLine[i];
      if ( v6 == 47 )
        break;
      if ( v6 == 92 )
        break;
      if ( v6 == 58 )
        break;
    }
    result = (char *)scprintf(&FilenameFromCommandLine[i + 1], &g_ptParentQTask.tQTaskChildren, &igi2_frame.v11, igi2_frame.v13, &igi2_frame.v12, &igi2_frame.v10);
    if ( result == (char *)4 )
    {
      GetModuleFileNameA(nullptr, igi2_frame.Filename, 0x104u);
      splitpath(igi2_frame.Filename, igi2_frame.PathName, igi2_frame.Dir, nullptr, nullptr);
      v7 = strlen(igi2_frame.Dir) + 1;
      v8 = &igi2_frame.v14;
      while ( *++v8 )
        ;
      qmemcpy(v8, igi2_frame.Dir, v7);
      if ( !SetCurrentDirectoryA(igi2_frame.PathName) )
      {
        MessageBoxA(nullptr, igi2_frame.PathName, "Failed to set directory.", 0);
        exit__crt0dat(1);
      }
      Flow_iOverrideActivePlayerProfile = igi2_frame.v11;
      Game_nMenuLoadFromSlot = igi2_frame.v10;
      result = (char *)sprintf(g_a1_0, "level%d", igi2_frame.v12);
      AppContext_tAppContext.zCmdLine = g_a1_0;
    }
  }
  return result;
}

// source: app.c:165  [anchor-mhash]
struct Result_s *__cdecl App_IsClientScriptFunction(struct Result_s *retstr)
{
  #pragma pack(push, 1)
  union
  {
    struct { int v2; };
    struct { char igi2_o1[4]; double v3[3]; };
    char igi2_extent[28];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)

  if ( AppContext_tAppContext.nPort <= 0 || (LODWORD(igi2_frame.v3[0]) = 1, !AppContext_tAppContext.zIP[0]) )
    LODWORD(igi2_frame.v3[0]) = 0;
  if ( AppContext_tAppContext.nPort <= 0 || (igi2_frame.v2 = 1, !AppContext_tAppContext.zIP[0]) )
    igi2_frame.v2 = 0;
  igi2_frame.v3[1] = (double)igi2_frame.v2;
  LODWORD(igi2_frame.v3[2]) = &g_zInitialValue;
  qmemcpy(retstr, igi2_frame.v3, sizeof(struct Result_s));
  return retstr;
}

// source: app.c:182  [anchor-caller]
int App_Open()
{
  #pragma pack(push, 1)
  union
  {
    struct { DWORD dwHandle; };
    struct { char igi2_o1[4]; int v5; };
    struct { char igi2_o2[8]; int v6; };
    struct { char igi2_o3[12]; char *Buffer; };
    struct { char igi2_o4[16]; LPVOID lpBuffer; };
    struct { char igi2_o5[20]; unsigned int puLen; };
    struct { char igi2_o6[24]; unsigned int v10; };
    struct { char igi2_o7[28]; CHAR Filename[264]; };
    struct { char igi2_o8[292]; CHAR SubBlock_[260]; };
    char igi2_extent[552];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  size_t FileVersionInfoSizeA; // eax
  DWORD v1; // esi
  void *v2; // edi

  igi2_frame.dwHandle = 0;
  GetModuleFileNameA(nullptr, igi2_frame.Filename, 0x104u);
  FileVersionInfoSizeA = GetFileVersionInfoSizeA(igi2_frame.Filename, &igi2_frame.dwHandle);
  v1 = FileVersionInfoSizeA;
  if ( FileVersionInfoSizeA )
  {
    v2 = malloc(FileVersionInfoSizeA);
    if ( GetFileVersionInfoA(igi2_frame.Filename, igi2_frame.dwHandle, v1, v2) )
    {
      if ( VerQueryValueA(v2, "\\VarFileInfo\\Translation", &igi2_frame.lpBuffer, &igi2_frame.puLen) )
      {
        _snprintf(
          igi2_frame.SubBlock_,
          0x100u,
          "\\StringFileInfo\\%04x%04x\\FileVersion",
          *(unsigned __int16 *)igi2_frame.lpBuffer,
          *((unsigned __int16 *)igi2_frame.lpBuffer + 1));
        if ( VerQueryValueA(v2, igi2_frame.SubBlock_, (LPVOID *)&igi2_frame.Buffer, &igi2_frame.v10) )
        {
          if ( scprintf(igi2_frame.Buffer, "%d, %d", &igi2_frame.v5, &igi2_frame.v6) == 2 )
            sprintf(g_zPlayer1, "%d.%d", igi2_frame.v5, igi2_frame.v6);
        }
      }
    }
    free(v2);
  }
  CheckForSaveGame();
  AppContext_tAppContext.zApplicationName = "IGI2 - Covert Strike";
  if ( AppContext_tAppContext.hWnd )
    SetWindowTextA(AppContext_tAppContext.hWnd, "IGI2 - Covert Strike");
  AppContext_tAppContext.isQVMUsed = true;
  J_Open();
  Symbol_Register(
    "App_IsClient",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))App_IsClientScriptFunction,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Resource_Register("GLOBAL:version", nullptr, g_zPlayer1, strlen(g_zPlayer1) + 1, 3u, nullptr);
  QTask_NewFn(nullptr, Flow_eQTaskType, nullptr);
  NetworkConfig_Load("networkconfig.cfg");
  if ( AppContext_tAppContext.isEditorState )
  {
    Flow_ptFlow->eRequestedEvent = 2;
    return 1;
  }
  else if ( AppContext_tAppContext.nPort > 0 && AppContext_tAppContext.zIP[0] )
  {
    Flow_ptFlow->eRequestedEvent = 10;
    return 1;
  }
  else
  {
    Flow_ptFlow->eRequestedEvent = 4;
    return 1;
  }
}

// source: app.c:282  [override: the decompiler cannot analyse the _setjmp3 call]
// One frame: run the Flow task's run handler (final-event row 1, indexed by task type) under a
// setjmp guard; a longjmp back here (a fatal error) ends the main loop. The replay driver
// (support/replay.c) feeds the frame's scripted input before it and logs the player after it;
// support/menu_extras.c adds what the menus get from C.
void __cdecl Igi2_ReplayBeforeFrame(void);
void __cdecl Igi2_ReplayAfterFrame(void);
void __cdecl Igi2_MenuExtras(void);

void __cdecl App_Run()
{
  Igi2_ReplayBeforeFrame();
  if ( setjmp(*(jmp_buf *)&App_tLongJumpEnv) )
    Main_isContinue = 0;
  else
    ((void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[1][Flow_ptFlow->tQTask.eQTaskType].pfHandler)(
      (struct QTask_s *)Flow_ptFlow);
  Igi2_MenuExtras();
  Igi2_ReplayAfterFrame();
}

// source: app.c:306  [anchor-hash]
__declspec(noreturn) void App_Quit()
{
  longjmp(App_tLongJumpEnv, 1);
}

// source: app.c:323  [anchor-hash]
void __cdecl App_Close(char *zNetworkConfigFileName)
{
  if ( QTask_GetNumberOfQTasks() )
  {
    if ( Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER )
    {
      NetworkConfig_Save("networkconfig.cfg");
      if ( Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER )
        NetManager_LeaveGame();
    }
    QTask_Delete(&Flow_ptFlow->tQTask);
  }
  if ( Display_isModeSet )
  {
    RenderMode_tActiveRenderMode.apfRenderModeMethod[Display_eUnsetModeMethod](nullptr);
    Display_tActiveMode.eRenderMode = -1;
    RenderMode_eActiveRenderMode = -1;
    Display_isModeSet = 0;
  }
  J_Close();
}

// source: app.c:351  [size]
char *App_GetVersionNumberString()
{
  return g_zPlayer1;
}

struct Result_s *__cdecl pfSymbolParse__(struct Result_s *retstr)
{
  struct Result_s *result; // eax
  _DWORD v2[6]; // [esp+8h] [ebp-18h] BYREF

  v2[4] = &g_zInitialValue;
  v2[2] = 0;
  if ( dword_6C02F8 )
  {
    dword_6C02F8 = 0;
    result = retstr;
    v2[0] = 1;
    v2[3] = 1072693248;
  }
  else
  {
    v2[0] = 0;
    result = retstr;
    v2[3] = 0;
  }
  qmemcpy(retstr, v2, sizeof(struct Result_s));
  return result;
}
