/* b/b.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: b/b.c:42  [anchor-caller]
void __cdecl B_Open()
{
  LDebug_Open();
  Debug_InitCallbacks();
  LDebug_EnableLogging(1);
  GetLocaleInfoA(0x400u, 0x1002u, AppContext_tAppContext.zCountry, 256);
  AppContext_tAppContext.pfActivateCallback = nullptr;
  AppContext_tAppContext.pxActivateCallbackContext = nullptr;
  ExceptionHandler_Open();
  Real_Open();
  Mem_Open();
  WarningLog_Open();
  DbgMap_Open();
  DebugConsole_nAllocID = 1;
  DebugConsole_ptActiveDebugConsole = nullptr;
  DebugConsole_tConsoleList.ptHead = (struct DebugConsole_s *)&DebugConsole_tConsoleList.ptMiddle;
  DebugConsole_tConsoleList.ptTail = (struct DebugConsole_s *)&DebugConsole_tConsoleList;
  DebugConsole_tConsoleList.ptMiddle = nullptr;
  DebugConsole_tDefaultConsoleID = DebugConsole_Alloc("Default", 100);
  DebugConsole_PushActiveConsole(DebugConsole_tDefaultConsoleID);
  DebugConsoleCommand_tGlobalCommandList.ptHead = (struct ConsoleCommand_s *)&DebugConsoleCommand_tGlobalCommandList.ptMiddle;
  DebugConsoleCommand_tGlobalCommandList.ptTail = (struct ConsoleCommand_s *)&DebugConsoleCommand_tGlobalCommandList;
  DebugConsoleCommand_tGlobalCommandList.ptMiddle = nullptr;
  DebugConsoleCommand_tConsoleCommandListList.ptHead = (struct ConsoleCommandListNode_s *)&DebugConsoleCommand_tConsoleCommandListList.ptMiddle;
  DebugConsoleCommand_tConsoleCommandListList.ptTail = (struct ConsoleCommandListNode_s *)&DebugConsoleCommand_tConsoleCommandListList;
  DebugConsoleCommand_tConsoleCommandListList.ptMiddle = nullptr;
  RenderInfo_tLogConsoleID = DebugConsole_Alloc("RenderInfo Log", 100);
  RenderInfo_tFrameInfoConsoleID = DebugConsole_Alloc("RenderInfo", 100);
  SoundInfo_tLogConsoleID = DebugConsole_Alloc("SoundInfo Log", 100);
  SoundInfo_tFrameInfoConsoleID = DebugConsole_Alloc("SoundInfo", 100);
  NetworkInfo_Open();
  File_Open();
  memset(RenderMode_atRenderMode, 0, sizeof(RenderMode_atRenderMode));
  memset(&RenderMode_tActiveRenderMode, 0, sizeof(RenderMode_tActiveRenderMode));
  memset(RenderMode_atRenderModeMethod, 0, sizeof(RenderMode_atRenderModeMethod));
  RenderMode_nSP = 8;
  RenderMode_eActiveRenderMode = -1;
  Primitive_asPrimitive[0] = (unsigned int)Mem_AllocFn(0x80000, 4);
  Display_Open();
  Resource_Open();
  Palette_Open();
  Texture_Open();
  FontManager_Open();
  Network_Open();
  TelnetHost_tConsoleID = DebugConsole_Alloc("telnetd", 100);
  DebugConsole_PushActiveConsole(TelnetHost_tConsoleID);
  DebugConsoleCommand_Echo(false);
  DebugConsole_PopActiveConsole();
  Sound_Open();
  QVertex_Open();
  Keyboard_Open();
  KeyboardBuffer_Open();
  Mouse_Open();
  Joypad_Open();
  RenderContext_tDrawList.ptHead = (struct RenderContext_s *)&RenderContext_tDrawList.ptMiddle;
  RenderContext_tDrawList.ptTail = (struct RenderContext_s *)&RenderContext_tDrawList;
  RenderContext_tDrawList.ptMiddle = nullptr;
  TransContext_Open();
  if ( QueryPerformanceFrequency((LARGE_INTEGER *)&Timer_lpCount) )
  {
    Timer_isPerformanceCounter = 1;
    Timer_nStartTime = Timer_GetPerformanceCounter();
  }
  else
  {
    Timer_isPerformanceCounter = 0;
    Timer_nStartTime = GetTickCount();
  }
  SortRender_Open();
  Batch_Open();
}

LPTOP_LEVEL_EXCEPTION_FILTER B_Close()
{
  int PerformanceCounter; // eax
  int v1; // edx
  struct WinProcCBNode_s *ptHead; // eax
  struct WinProcCBNode_s *ptNext; // ecx
  int v4; // ecx
  int v5; // eax
  int v6; // ecx
  LPTOP_LEVEL_EXCEPTION_FILTER result; // eax

  Batch_Close();
  RenderMode_atRenderModeMethod[SortRender_ePrimType].isAllocated = 0;
  if ( QueryPerformanceFrequency((LARGE_INTEGER *)&Timer_lpCount) )
  {
    Timer_isPerformanceCounter = 1;
    PerformanceCounter = Timer_GetPerformanceCounter();
  }
  else
  {
    Timer_isPerformanceCounter = 0;
    PerformanceCounter = GetTickCount();
  }
  v1 = TransContext_eSetActiveTransContextRenderModeMethod;
  RenderMode_atRenderModeMethod[TransContext_eSetNearClippingPlaneMethod].isAllocated = 0;
  Timer_nStartTime = PerformanceCounter;
  RenderMode_atRenderModeMethod[v1].isAllocated = 0;
  TransContext_ePrimType = -1;
  TransContext_isValid = 0;
  Joypad_Close();
  Mouse_Close();
  ptHead = Main_tWinProcCBList.ptHead;
  ptNext = Main_tWinProcCBList.ptHead->ptNext;
  if ( Main_tWinProcCBList.ptHead->ptNext )
  {
    while ( ptHead->pfWinProcCB != KeyboardBuffer_WinProcHandler )
    {
      ptHead = ptNext;
      ptNext = ptNext->ptNext;
      if ( !ptNext )
        goto LABEL_9;
    }
    Node_Remove(ptHead)[2] = nullptr;
  }
LABEL_9:
  Keyboard_Close();
  v4 = QVertex_eRegisterQVertexStripMethod;
  RenderMode_atRenderModeMethod[QVertex_eStripPrimType].isAllocated = 0;
  RenderMode_atRenderModeMethod[v4].isAllocated = 0;
  Sound_Close();
  if ( tMyThreadContext.isRunning )
    TelnetHost_TerminateListenerThread(&tMyThreadContext);
  DebugConsole_DeAlloc(TelnetHost_tConsoleID);
  NetManager_LogMessage("Network_Close()\n");
  Network_pfExternalReceiveHandler = nullptr;
  Network_pfConsoleReceiveHandler = nullptr;
  Network_FreeAdapters();
  Network_FreeBannedList();
  WSACleanup();
  FontManager_Close();
  Texture_Close();
  v5 = Palette_eDeAllocPaletteMethod;
  v6 = Palette_eDownloadPaletteMethod;
  RenderMode_atRenderModeMethod[Palette_eAllocPaletteMethod].isAllocated = 0;
  RenderMode_atRenderModeMethod[v5].isAllocated = 0;
  RenderMode_atRenderModeMethod[v6].isAllocated = 0;
  while ( Resource_tResourceList.ptHead->ptNext )
    Resource_Remove(Resource_tResourceList.ptHead);
  QHashTable_Delete(Resource_ptHashTable);
  MemPool_DeInit(&Resource_tResourcePool);
  Display_Close();
  Primitive_Close();
  DebugConsole_DeAlloc(RenderInfo_tLogConsoleID);
  DebugConsole_DeAlloc(RenderInfo_tFrameInfoConsoleID);
  DebugConsole_DeAlloc(SoundInfo_tLogConsoleID);
  DebugConsole_DeAlloc(SoundInfo_tFrameInfoConsoleID);
  DebugConsole_DeAlloc(NetworkInfo_tLogConsoleID);
  DebugConsole_DeAlloc(NetworkInfo_tSendLogConsoleID);
  DebugConsole_DeAlloc(NetworkInfo_tReceiveLogConsoleID);
  DebugConsole_DeAlloc(NetworkInfo_tFrameInfoConsoleID);
  DebugConsoleCommand_Close();
  DebugConsole_PopActiveConsole();
  DebugConsole_DeAlloc(DebugConsole_tDefaultConsoleID);
  File_Close();
  if ( DbgMap_ptSymbolsVector )
  {
    QObjectVector_Delete(DbgMap_ptSymbolsVector);
    DbgMap_ptSymbolsVector = nullptr;
  }
  WarningLog_Close();
  Mem_Close();
  FreeLibrary(hImagehlpDll);
  result = SetUnhandledExceptionFilter(ExceptionHandler_tPreviousFilter);
  AppContext_tAppContext.pfActivateCallback = nullptr;
  AppContext_tAppContext.pxActivateCallbackContext = nullptr;
  return result;
}
