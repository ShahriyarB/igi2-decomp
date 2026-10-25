/* b/2/pc/pc_display.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: b/2/pc/pc_display.c:122  [size]
void __cdecl Display_ParseQuietCmd(char *zUnused)
{
  Display_isQuiet = true;
}

// source: b/2/pc/pc_display.c:135  [anchor-hash]
void __cdecl Display_InitCallback()
{
  void (__cdecl **p_pfCallback)(); // eax

  Display_ptSetModeCallback = nullptr;
  Display_ptStartFrameCallback = nullptr;
  Display_ptEndFrameCallback = nullptr;
  p_pfCallback = &Display_atCallback[0].pfCallback;
  do
  {
    *p_pfCallback = nullptr;
    p_pfCallback += 2;
  }
  while ( (int)p_pfCallback < 137688964 );
}

// source: b/2/pc/pc_display.c:157  [size]
struct DisplayCallbackChain_s *__cdecl Display_CallChain(struct DisplayCallbackChain_s *ptChain)
{
  struct DisplayCallbackChain_s *i; // esi

  for ( i = ptChain; i; i = i->ptNext )
    ptChain = (struct DisplayCallbackChain_s *)((int (*)(void))i->pfCallback)();
  return ptChain;
}

// source: b/2/pc/pc_display.c:174  [anchor-strings]
void __cdecl Display_RegisterCallback(void (__cdecl *pfCB_)(), struct DisplayCallbackChain_s **pptFirst)
{
  int v2; // eax
  struct DisplayCallbackChain_s *v3; // ecx

  v2 = 0;
  while ( Display_atCallback[v2].pfCallback )
  {
    if ( ++v2 >= 32 )
    {
      LDebug_Error("No more Display callbacks available.");
      abort();
    }
  }
  v3 = (struct DisplayCallbackChain_s *)(8 * v2 + 137688704);
  v3->ptNext = *pptFirst;
  Display_atCallback[v2].pfCallback = pfCB_;
  *pptFirst = v3;
}

// source: b/2/pc/pc_display.c:202  [size]
char __cdecl Display_RemoveCallback(
        void (__cdecl *pfCB_)(),
        struct DisplayCallbackChain_s **pptFirst)
{
  struct DisplayCallbackChain_s *v2; // eax
  struct DisplayCallbackChain_s *v3; // ecx

  v2 = *pptFirst;
  v3 = nullptr;
  if ( !*pptFirst )
    return 0;
  while ( v2->pfCallback != pfCB_ )
  {
    v3 = v2;
    v2 = v2->ptNext;
    if ( !v2 )
      return 0;
  }
  if ( v3 )
    v3->ptNext = v2->ptNext;
  else
    *pptFirst = v2->ptNext;
  return 1;
}

// source: b/2/pc/pc_display.c:243  [size]
void __cdecl Display_MsgWinRestore(char *zString)
{
  ShowCursor(1);
  MessageBoxA(nullptr, zString, AppContext_tAppContext.zApplicationName, 0x10u);
  ShowCursor(0);
}

// source: b/2/pc/pc_display.c:258  [size]
void __cdecl Display_MsgWinFatal(char *zString)
{
  ShowCursor(1);
  MessageBoxA(nullptr, zString, AppContext_tAppContext.zApplicationName, 0x10u);
  ShowCursor(0);
}

// source: b/2/pc/pc_display.c:271  [anchor-mhash]
void __cdecl Display_RenderModeEnumerateCallback(
        struct RenderModeEnumerateContext_s *ptRenderModeEnumerateContext,
        struct DisplayEnumerateContext_s *ptDisplayEnumerateContext)
{
  RenderMode_atRenderMode[ptRenderModeEnumerateContext->eRenderMode].apfRenderModeMethod[ptDisplayEnumerateContext->eRenderModeMethod](ptDisplayEnumerateContext->pxContext);
}

// source: b/2/pc/pc_display.c:289  [size]
void __cdecl Display_CheckMode(struct DisplayMode_s *ptMode)
{
  int v1; // ebp
  int v2; // esi
  int v3; // edi
  int *p_nHeight; // ecx
  __int64 v5; // rax
  int v6; // eax

  v1 = 0;
  v2 = 0;
  v3 = 0x7FFFFFFF;
  if ( Display_nModes > 0 )
  {
    p_nHeight = &Display_atMode[0].nHeight;
    do
    {
      if ( p_nHeight[2] == ptMode->nBitsPerPixel )
      {
        v5 = *p_nHeight * *(p_nHeight - 1) - ptMode->nWidth * ptMode->nHeight;
        v6 = (HIDWORD(v5) ^ v5) - HIDWORD(v5);
        if ( v6 < v3 )
        {
          v1 = v2;
          v3 = v6;
        }
      }
      ++v2;
      p_nHeight += 73;
    }
    while ( v2 < Display_nModes );
  }
  ptMode->nWidth = Display_atMode[v1].nWidth;
  ptMode->nHeight = Display_atMode[v1].nHeight;
}

// source: b/2/pc/pc_display.c:332  [size]
void __cdecl Display_RegisterSetModeCallback(void (__cdecl *pfCB_)())
{
  Display_RegisterCallback(pfCB_, &Display_ptSetModeCallback);
}

// source: b/2/pc/pc_display.c:345  [size]
void __cdecl Display_RemoveSetModeCallback(void (__cdecl *pfCB_)())
{
  struct DisplayCallbackChain_s *v1; // eax
  struct DisplayCallbackChain_s *v2; // ecx

  v1 = Display_ptSetModeCallback;
  v2 = nullptr;
  if ( Display_ptSetModeCallback )
  {
    while ( v1->pfCallback != pfCB_ )
    {
      v2 = v1;
      v1 = v1->ptNext;
      if ( !v1 )
        return;
    }
    if ( v2 )
      v2->ptNext = v1->ptNext;
    else
      Display_ptSetModeCallback = v1->ptNext;
  }
}

// source: b/2/pc/pc_display.c:361  [size]
void __cdecl Display_RegisterStartFrameCallback(void (__cdecl *pfCB_)())
{
  Display_RegisterCallback(pfCB_, &Display_ptStartFrameCallback);
}

// source: b/2/pc/pc_display.c:374  [size]
void __cdecl Display_RemoveStartFrameCallback(void (__cdecl *pfCB_)())
{
  struct DisplayCallbackChain_s *v1; // eax
  struct DisplayCallbackChain_s *v2; // ecx

  v1 = Display_ptStartFrameCallback;
  v2 = nullptr;
  if ( Display_ptStartFrameCallback )
  {
    while ( v1->pfCallback != pfCB_ )
    {
      v2 = v1;
      v1 = v1->ptNext;
      if ( !v1 )
        return;
    }
    if ( v2 )
      v2->ptNext = v1->ptNext;
    else
      Display_ptStartFrameCallback = v1->ptNext;
  }
}

// source: b/2/pc/pc_display.c:389  [size]
void __cdecl Display_RegisterEndFrameCallback(void (__cdecl *pfCB_)())
{
  Display_RegisterCallback(pfCB_, &Display_ptEndFrameCallback);
}

// source: b/2/pc/pc_display.c:402  [size]
void __cdecl Display_RemoveEndFrameCallback(void (__cdecl *pfCB_)())
{
  struct DisplayCallbackChain_s *v1; // eax
  struct DisplayCallbackChain_s *v2; // ecx

  v1 = Display_ptEndFrameCallback;
  v2 = nullptr;
  if ( Display_ptEndFrameCallback )
  {
    while ( v1->pfCallback != pfCB_ )
    {
      v2 = v1;
      v1 = v1->ptNext;
      if ( !v1 )
        return;
    }
    if ( v2 )
      v2->ptNext = v1->ptNext;
    else
      Display_ptEndFrameCallback = v1->ptNext;
  }
}

// source: b/2/pc/pc_display.c:415  [anchor-strings]
void __cdecl Display_Open()
{
  struct DisplayEnumerateContext_s tDisplayEnumerateContext; // [esp+4h] [ebp-8h] BYREF

  if ( Display_isOpen )
  {
    LDebug_Error("Display can only be opened once!");
    abort();
  }
  Display_zCurrentDriverIdentifier[0] = 0;
  Display_eOpenMethod = RenderMode_NewMethod("DisplayOpen");
  Display_eCloseMethod = RenderMode_NewMethod("DisplayClose");
  Display_eSetModeMethod = RenderMode_NewMethod("DisplaySetMode");
  Display_eUnsetModeMethod = RenderMode_NewMethod("DisplayUnsetMode");
  Display_eRestoreMethod = RenderMode_NewMethod("DisplayRestore");
  Display_eWaitVBMethod = RenderMode_NewMethod("DisplayVSync");
  Display_eSwapBuffersMethod = RenderMode_NewMethod("DisplaySwapBuffers");
  Display_eClearMethod = RenderMode_NewMethod("DisplayClear");
  Display_eEnumDevicesMethod = RenderMode_NewMethod("Enum");
  Display_eGetGFXCapsMethod = RenderMode_NewMethod("GetGFXCaps");
  Display_isModeSet = 0;
  Display_nModes = 0;
  Display_InitCallback();
  Display_eClipWindowPrim = Primitive_NewPrimType("ClipWindowPrimitive");
  Display_eBlitPrim = Primitive_NewPrimType("BlitPrimitive");
  Display_eSnapshotPrim = Primitive_NewPrimType("SnapshotPrimitive");
  Direct3D_New();
  OffscreenBuffer_New();
  tDisplayEnumerateContext.pxContext = nullptr;
  tDisplayEnumerateContext.eRenderModeMethod = Display_eOpenMethod;
  RenderMode_EnumerateRenderModes(
    (void (__cdecl *)(struct RenderModeEnumerateContext_s *, void *))Display_RenderModeEnumerateCallback,
    &tDisplayEnumerateContext);
  LDebug_SetPrint(Display_MsgWinFatal);
  AppMain_FindPrefix(AppContext_tAppContext.zCmdLine, "quiet", (void (__cdecl *)(char *))Display_ParseQuietCmd);
  if ( Display_isQuiet == false )
  {
    LDebug_SetWarning(Display_MsgWinRestore);
    LDebug_SetMessage(Display_MsgWinRestore);
  }
  Display_isOpen = 1;
}

// source: b/2/pc/pc_display.c:487  [anchor-caller]
void __cdecl Display_Close()
{
  struct DisplayEnumerateContext_s tDisplayEnumerateContext; // [esp+4h] [ebp-8h] BYREF

  tDisplayEnumerateContext.eRenderModeMethod = Display_eCloseMethod;
  tDisplayEnumerateContext.pxContext = nullptr;
  RenderMode_EnumerateRenderModes(
    (void (__cdecl *)(struct RenderModeEnumerateContext_s *, void *))Display_RenderModeEnumerateCallback,
    &tDisplayEnumerateContext);
  Direct3D_Delete();
  RenderMode_atRenderMode[dword_73D31C].isAllocated = 0;
  OffscreenBuffer_isInitialised[0] = 0;
  Display_isOpen = 0;
}

// source: b/2/pc/pc_display.c:528  [anchor-mhash]
int __cdecl Display_EnumerateModes(
        struct DisplayMode_s *ptDisplayMode,
        unsigned int bMask,
        void (__cdecl *pfEnumCallback)(struct DisplayMode_s *))
{
  int v3; // ebp
  int *p_nHeight; // esi
  BOOL v5; // eax
  int nModes; // [esp+8h] [ebp-4h]

  v3 = 0;
  nModes = 0;
  if ( Display_nModes > 0 )
  {
    p_nHeight = &Display_atMode[0].nHeight;
    do
    {
      v5 = 1;
      if ( !ptDisplayMode )
        goto LABEL_15;
      if ( (bMask & 1) != 0 )
        v5 = ptDisplayMode->nWidth == *(p_nHeight - 1);
      if ( (bMask & 2) != 0 && ptDisplayMode->nHeight != *p_nHeight )
        v5 = 0;
      if ( (bMask & 4) != 0 && ptDisplayMode->nBitsPerPixel != p_nHeight[2] )
        v5 = 0;
      if ( ((bMask & 8) == 0 || ptDisplayMode->eRenderMode == p_nHeight[4]) && v5 )
      {
LABEL_15:
        if ( pfEnumCallback )
          pfEnumCallback((struct DisplayMode_s *)(p_nHeight - 2));
        ++nModes;
      }
      ++v3;
      p_nHeight += 73;
    }
    while ( v3 < Display_nModes );
  }
  return nModes;
}

// source: b/2/pc/pc_display.c:599  [size]
void __cdecl Display_Clear()
{
  if ( Display_isModeSet )
    RenderMode_tActiveRenderMode.apfRenderModeMethod[Display_eClearMethod](nullptr);
}

// source: b/2/pc/pc_display.c:616  [anchor-mhash]
void __cdecl Display_UnsetMode(struct DisplayMode_s *ptDisplayMode)
{
  if ( Display_isModeSet )
  {
    RenderMode_tActiveRenderMode.apfRenderModeMethod[Display_eUnsetModeMethod](ptDisplayMode);
    Display_tActiveMode.eRenderMode = -1;
    RenderMode_eActiveRenderMode = -1;
    Display_isModeSet = 0;
  }
}

// source: b/2/pc/pc_display.c:638  [size]
void __cdecl Display_SetMode(struct DisplayMode_s *ptMode)
{
  struct DisplayCallbackChain_s *i; // esi
  int SystemMetrics; // eax
  int nHeight; // esi
  int v4; // eax
  LONG v5; // ecx
  LONG WindowLongA; // eax
  enum RenderMode_enum eRenderMode; // eax
  int v8; // eax
  char v9; // cl
  struct tagRECT rect; // [esp+14h] [ebp-10h] BYREF

  Display_CheckMode(ptMode);
  if ( !Display_isModeSet )
    goto LABEL_10;
  if ( !strlen(ptMode->zDeviceIdentifier) )
    strcpy(ptMode->zDeviceIdentifier, Display_zCurrentDriverIdentifier);
  if ( ptMode->nWidth != Display_tActiveMode.nWidth
    || ptMode->nHeight != Display_tActiveMode.nHeight
    || ptMode->nBitsPerPixel != Display_tActiveMode.nBitsPerPixel
    || ptMode->eRenderMode != Display_tActiveMode.eRenderMode
    || ptMode->isZBuffer != Display_tActiveMode.isZBuffer
    || strcmp(ptMode->zDeviceIdentifier, Display_tActiveMode.zDeviceIdentifier) )
  {
LABEL_10:
    for ( i = Display_ptSetModeCallback; i; i = i->ptNext )
      i->pfCallback();
    if ( Display_isModeSet )
    {
      RenderMode_tActiveRenderMode.apfRenderModeMethod[Display_eUnsetModeMethod](ptMode);
      Display_tActiveMode.eRenderMode = -1;
      RenderMode_eActiveRenderMode = -1;
      Display_isModeSet = 0;
    }
    if ( AppContext_tAppContext.isActive )
    {
      rect.left = 0;
      rect.top = 0;
      rect.right = GetSystemMetrics(0);
      rect.bottom = GetSystemMetrics(1);
    }
    else
    {
      SystemMetrics = GetSystemMetrics(0);
      nHeight = ptMode->nHeight;
      rect.left = (SystemMetrics - ptMode->nWidth) / 2;
      v4 = GetSystemMetrics(1);
      v5 = rect.left + ptMode->nWidth;
      rect.top = (v4 - nHeight) / 2;
      rect.right = v5;
      rect.bottom = rect.top + nHeight;
    }
    WindowLongA = GetWindowLongA(AppContext_tAppContext.hWnd, -16);
    AdjustWindowRect(&rect, WindowLongA, 0);
    SetWindowPos(
      AppContext_tAppContext.hWnd,
      nullptr,
      rect.left,
      rect.top,
      rect.right - rect.left,
      rect.bottom - rect.top,
      0x44u);
    UpdateWindow(AppContext_tAppContext.hWnd);
    SetFocus(AppContext_tAppContext.hWnd);
    eRenderMode = ptMode->eRenderMode;
    if ( eRenderMode != RenderMode_eActiveRenderMode )
    {
      qmemcpy(
        &RenderMode_tActiveRenderMode,
        (void *)(520 * eRenderMode + 139167712),
        sizeof(RenderMode_tActiveRenderMode));
      RenderMode_eActiveRenderMode = eRenderMode;
    }
    RenderMode_tActiveRenderMode.apfRenderModeMethod[Display_eSetModeMethod](ptMode);
    Display_isModeSet = 1;
    v8 = 0;
    do
    {
      v9 = Display_tActiveMode.zDeviceIdentifier[v8];
      Display_zCurrentDriverIdentifier[v8++] = v9;
    }
    while ( v9 );
  }
}

// source: b/2/pc/pc_display.c:722  [size]
void __cdecl Display_WaitForVBlank()
{
  if ( Display_isModeSet )
    RenderMode_tActiveRenderMode.apfRenderModeMethod[Display_eWaitVBMethod](nullptr);
}

// source: b/2/pc/pc_display.c:739  [anchor-hash]
void __cdecl Display_SwapBuffers()
{
  if ( Display_isModeSet )
    RenderMode_tActiveRenderMode.apfRenderModeMethod[Display_eSwapBuffersMethod](nullptr);
  ++Display_nFrame;
}

// source: b/2/pc/pc_display.c:758  [size]
struct DisplayMode_s *__cdecl Display_GetActiveMode()
{
  return &Display_tActiveMode;
}

// source: b/2/pc/pc_display.c:774  [anchor-hash]
void __cdecl Display_StartFrame()
{
  struct DisplayCallbackChain_s *v0; // esi

  if ( Display_isModeSet )
    RenderMode_tActiveRenderMode.apfRenderModeMethod[Display_eSwapBuffersMethod](nullptr);
  ++Display_nFrame;
  if ( Display_isModeSet )
    RenderMode_tActiveRenderMode.apfRenderModeMethod[Display_eClearMethod](nullptr);
  v0 = Display_ptStartFrameCallback;
  for ( Primitive_ptNextFreePrimitive = (void *)Primitive_asPrimitive[0]; v0; v0 = v0->ptNext )
    v0->pfCallback();
}

// source: b/2/pc/pc_display.c:799  [anchor-hash]
void __cdecl Display_EndFrame()
{
  struct DisplayCallbackChain_s *i; // esi

  RenderContext_RenderAll();
  for ( i = Display_ptEndFrameCallback; i; i = i->ptNext )
    i->pfCallback();
  DebugConsole_PushActiveConsole(RenderInfo_tFrameInfoConsoleID);
  DebugConsole_ClearAll(DebugConsole_ptActiveDebugConsole, false);
  DebugConsole_PopActiveConsole();
}

// source: b/2/pc/pc_display.c:823  [anchor-hash]
float __cdecl Display_GetAspectRatio()
{
  return (double)Display_tActiveMode.nHeight * 4.0 / ((double)Display_tActiveMode.nWidth * 3.0);
}

// source: b/2/pc/pc_display.c:841  [size]
void __cdecl Display_Blit(struct DisplayBlitContext_s *ptDisplayBlitContext)
{
  if ( ptDisplayBlitContext )
  {
    RenderMode_tActiveRenderMode.apfRenderModeMethod[ptDisplayBlitContext->tRenderPrimitive.ePrimType](ptDisplayBlitContext);
    dword_834E068 = (int)ptDisplayBlitContext;
  }
  else if ( dword_834E068 )
  {
    RenderMode_tActiveRenderMode.apfRenderModeMethod[*(_DWORD *)(dword_834E068 + 4)](nullptr);
  }
}

// source: b/2/pc/pc_display.c:859  [anchor-callee]
void __cdecl Display_Snapshot(unsigned __int8 *anRGBBuffer)
{
  struct DisplaySnapshotContext_s tSnapshot; // [esp+0h] [ebp-10h] BYREF

  tSnapshot.tRenderPrimitive.ePrimType = Display_eSnapshotPrim;
  tSnapshot.anRGBBuffer = anRGBBuffer;
  RenderMode_tActiveRenderMode.apfRenderModeMethod[Display_eSnapshotPrim](&tSnapshot);
  dword_834E068 = (int)&tSnapshot;
}

// source: b/2/pc/pc_display.c:1049  [size]
int __cdecl Display_GetEnumDevicesMethod()
{
  return Display_eClipWindowPrim;
}
