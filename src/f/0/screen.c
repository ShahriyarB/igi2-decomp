/* f/0/screen.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: f/0/screen.c:79  [anchor-mhash]
int __cdecl Screen_SortManualRedrawListCallback(void **ppx1, void **ppx2)
{
  return *((_DWORD *)*ppx1 + 1) - *((_DWORD *)*ppx2 + 1);
}

// source: f/0/screen.c:96  [anchor-hash]
void __cdecl Screen_SortManualRedrawList()
{
  qsort(
    Screen_aptScreenManualRedrawQTaskSortVector,
    Screen_nScreenManualRedrawQTask,
    4,
    Screen_SortManualRedrawListCallback);
}

// source: f/0/screen.c:114  [size]
void __cdecl Screen_CreateHandler(struct QTask_s *ptQTask, void *pxData)
{
  ;
}

// source: f/0/screen.c:130  [size]
void __cdecl Screen_RunHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptHead; // ecx
  int v2; // edx
  struct QTask_s *v3; // eax
  void (__cdecl *pfHandler)(struct QTask_s *); // eax
  int v5; // edx

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
}

// source: f/0/screen.c:150  [size]
void __cdecl Screen_DrawHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptHead; // ecx
  int v2; // edx
  int v3; // edi
  struct QTask_s *v4; // eax
  void (__cdecl *pfHandler)(struct QTask_s *); // eax
  int v6; // edx
  int v7; // esi
  struct DisplayCallbackChain_s *i; // esi
  struct DebugConsole_s *v9; // ecx
  struct DebugConsole_s *ptNext; // eax
  int v11; // edx
  struct DebugConsole_s *v12; // ecx
  struct DebugConsole_s *v13; // eax
  int v14; // edx

  if ( Screen_isDisplayModeRequested )
  {
    Display_SetMode(&Screen_tRequestedDisplayMode);
    qmemcpy(&Screen_tCurrentDisplayMode, &Screen_tRequestedDisplayMode, sizeof(Screen_tCurrentDisplayMode));
    Screen_isDisplayModeRequested = 0;
  }
  Display_StartFrame();
  if ( AppContext_tAppContext.isMainMenu == false )
  {
    ptHead = ptQTask->tQTaskChildren.ptHead;
    if ( ptHead->ptNext && ptHead )
    {
      v2 = QTask_nProtectedQTaskStackOffset;
      v3 = Screen_eDrawQTaskEvent;
      do
      {
        if ( ptHead->ptNext )
          v4 = ptHead->ptNext->ptNext != nullptr ? ptHead->ptNext : nullptr;
        else
          v4 = nullptr;
        QTask_atProtectedQTaskStack[v2].ptQTask = v4;
        pfHandler = (void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[v3][ptHead->eQTaskType].pfHandler;
        v6 = v2 + 1;
        QTask_nProtectedQTaskStackOffset = v6;
        if ( pfHandler )
        {
          pfHandler(ptHead);
          v6 = QTask_nProtectedQTaskStackOffset;
          v3 = Screen_eDrawQTaskEvent;
        }
        ptHead = (struct QTask_s *)dword_849C7DC[v6];
        v2 = v6 - 1;
        QTask_nProtectedQTaskStackOffset = v2;
      }
      while ( ptHead );
    }
    else
    {
      v3 = Screen_eDrawQTaskEvent;
    }
    v7 = 0;
    if ( Screen_nScreenManualRedrawQTask > 0 )
    {
      while ( 1 )
      {
        ((void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[v3][Screen_aptScreenManualRedrawQTaskSortVector[v7]->ptQTask->eQTaskType].pfHandler)(Screen_aptScreenManualRedrawQTaskSortVector[v7]->ptQTask);
        if ( ++v7 >= Screen_nScreenManualRedrawQTask )
          break;
        v3 = Screen_eDrawQTaskEvent;
      }
    }
  }
  RenderContext_RenderAll();
  for ( i = Display_ptEndFrameCallback; i; i = i->ptNext )
    i->pfCallback();
  v9 = DebugConsole_tConsoleList.ptHead;
  ptNext = DebugConsole_tConsoleList.ptHead->ptNext;
  if ( DebugConsole_tConsoleList.ptHead->ptNext )
  {
    while ( v9->tConsoleID != RenderInfo_tFrameInfoConsoleID )
    {
      v9 = ptNext;
      ptNext = ptNext->ptNext;
      if ( !ptNext )
        goto LABEL_24;
    }
  }
  else
  {
LABEL_24:
    v9 = nullptr;
  }
  DebugConsole_atActiveConsoleStack[++DebugConsole_nStackPointer] = RenderInfo_tFrameInfoConsoleID;
  DebugConsole_ptActiveDebugConsole = v9;
  DebugConsole_ClearAll(v9, false);
  v11 = --DebugConsole_nStackPointer;
  if ( DebugConsole_nStackPointer <= 0 )
  {
    DebugConsole_ptActiveDebugConsole = nullptr;
    ++Screen_nFrameNumber;
  }
  else
  {
    v12 = DebugConsole_tConsoleList.ptHead;
    v13 = DebugConsole_tConsoleList.ptHead->ptNext;
    if ( DebugConsole_tConsoleList.ptHead->ptNext )
    {
      v14 = DebugConsole_atActiveConsoleStack[v11];
      while ( v12->tConsoleID != v14 )
      {
        v12 = v13;
        v13 = v13->ptNext;
        if ( !v13 )
          goto LABEL_30;
      }
    }
    else
    {
LABEL_30:
      v12 = nullptr;
    }
    DebugConsole_ptActiveDebugConsole = v12;
    ++Screen_nFrameNumber;
  }
}

// source: f/0/screen.c:223  [anchor-hash]
void __cdecl Screen_Open()
{
  unsigned __int16 BaseQTaskType; // ax
  unsigned __int16 v1; // si

  Screen_eDrawQTaskEvent = QTask_NewQTaskEventNoContextFn(0, "Draw");
  BaseQTaskType = QTask_GetBaseQTaskType();
  v1 = QTask_NewQTaskType((char *)&g_zFileName.atSpriteResources[41].tSprite.nTextures, 40, BaseQTaskType, 0, 0);
  Screen_eQTaskType = v1;
  QTask_LinkQTaskEventHandlerFn(v1, 0, (void (__cdecl *)(struct QTask_s *, void *))Screen_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 1, Screen_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, Screen_eDrawQTaskEvent, Screen_DrawHandler);
  memset(&Screen_tCurrentDisplayMode, 0, sizeof(Screen_tCurrentDisplayMode));
  Screen_isDisplayModeRequested = 0;
  Screen_isInitialised = 1;
}

// source: f/0/screen.c:258  [anchor-hash]
void __cdecl Screen_Close()
{
  QTask_DeleteQTaskEventNoContext(Screen_eDrawQTaskEvent);
  Screen_eDrawQTaskEvent = 512;
  QTask_DeleteQTaskType(Screen_eQTaskType);
  Screen_isInitialised = 0;
}

// source: f/0/screen.c:282  [size]
int __cdecl Screen_GetDrawQTaskEvent()
{
  return Screen_eDrawQTaskEvent;
}

// source: f/0/screen.c:300  [anchor-mhash]
int __cdecl Screen_RequestDisplayMode(
        struct DisplayMode_s *ptDisplayMode,
        int isFullscreen)
{
  if ( Screen_isDisplayModeRequested )
    return 0;
  qmemcpy(&Screen_tRequestedDisplayMode, ptDisplayMode, sizeof(Screen_tRequestedDisplayMode));
  Screen_isFullscreen = isFullscreen;
  Screen_isDisplayModeRequested = 1;
  return 1;
}

// source: f/0/screen.c:326  [size]
struct QTask_s *__cdecl Screen_New(struct QTask_s *ptParent)
{
  return QTask_NewFn(ptParent, Screen_eQTaskType, nullptr);
}

// source: f/0/screen.c:344  [size]
void __cdecl Screen_EnableRendering()
{
  Screen_isEnableRendering = 1;
}

// source: f/0/screen.c:357  [size]
void __cdecl Screen_DisableRendering()
{
  Screen_isEnableRendering = 0;
}

// source: f/0/screen.c:370  [size]
int __cdecl Screen_GetFrameNumber()
{
  return Screen_nFrameNumber;
}

// source: f/0/screen.c:385  [anchor-mhash]
void __cdecl Screen_RegisterRedrawQTask(struct QTask_s *ptQTask, int nPriority)
{
  int v2; // eax
  struct ScreenManualRedrawQTask_s *v3; // ecx

  v2 = Screen_nScreenManualRedrawQTask;
  v3 = (struct ScreenManualRedrawQTask_s *)(8 * Screen_nScreenManualRedrawQTask + 7436400);
  v3->ptQTask = ptQTask;
  Screen_atScreenManualRedrawQTask[v2].nPriority = nPriority;
  Screen_aptScreenManualRedrawQTaskSortVector[v2] = v3;
  Screen_nScreenManualRedrawQTask = v2 + 1;
  qsort(Screen_aptScreenManualRedrawQTaskSortVector, v2 + 1, 4, Screen_SortManualRedrawListCallback);
}

// source: f/0/screen.c:420  [anchor-strings]
int __cdecl Screen_RemoveRedrawQTask(int a1, struct QTask_s *a2)
{
  int v2; // ecx
  int v3; // eax

  v2 = Screen_nScreenManualRedrawQTask;
  v3 = 0;
  if ( Screen_nScreenManualRedrawQTask <= 0 )
  {
LABEL_4:
    LDebug_Error(&g_zFileName.atSpriteResources[41].zResourceFilename[16]);
    abort();
  }
  while ( Screen_atScreenManualRedrawQTask[v3].ptQTask != a2 )
  {
    if ( ++v3 >= Screen_nScreenManualRedrawQTask )
      goto LABEL_4;
  }
  Screen_atScreenManualRedrawQTask[v3].ptQTask = (struct QTask_s *)Screen_aptScreenManualRedrawQTaskSortVector[2 * Screen_nScreenManualRedrawQTask + 62];
  Screen_atScreenManualRedrawQTask[v3].nPriority = (int)Screen_aptScreenManualRedrawQTaskSortVector[2 * v2 + 63];
  Screen_nScreenManualRedrawQTask = v2 - 1;
  qsort(Screen_aptScreenManualRedrawQTaskSortVector, v2 - 1, 4, Screen_SortManualRedrawListCallback);
  return 0;
}

// source: f/0/screen.c:454  [size]
unsigned __int16 __cdecl Screen_GetQTaskType()
{
  return Screen_eQTaskType;
}
