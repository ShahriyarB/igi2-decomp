/* b/2/pc/pc_direct3d.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: b/2/pc/pc_direct3d.c:257  [anchor-mhash]
void __cdecl Direct3D_SetGamma(float vGamma)
{
  #pragma pack(push, 1)
  union
  {
    struct { __int64 i; };
    struct { char igi2_o1[8]; struct _D3DGAMMARAMP tGammaRamp; };
    char igi2_extent[1544];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct IDirect3DDevice8 *v1; // edi
  int v2; // esi

  v1 = Direct3D_ptDevice;
  if ( Direct3D_ptDevice && AppContext_tAppContext.isActive )
  {
    v2 = 0;
    LODWORD(igi2_frame.i) = 0;
    do
    {
      ++v2;
      igi2_frame.i = (__int64)(pow((double)(int)igi2_frame.i * 0.00390625, vGamma) * 65535.0);
      *((_WORD *)&igi2_frame.i + v2 + 3) = igi2_frame.i;
      igi2_frame.tGammaRamp.green[v2 - 1] = igi2_frame.i;
      igi2_frame.tGammaRamp.green[v2 + 255] = igi2_frame.i;
      LODWORD(igi2_frame.i) = v2;
    }
    while ( v2 < 256 );
    v1->lpVtbl->SetGammaRamp(v1, 0, &igi2_frame.tGammaRamp);
  }
}

// source: b/2/pc/pc_direct3d.c:287  [anchor-hash]
void __cdecl Direct3D_InitState()
{
  memset(&Direct3D_tState, 0xFFu, sizeof(Direct3D_tState));
}

// source: b/2/pc/pc_direct3d.c:300  [anchor-hash]
void __cdecl Direct3D_CreateDynamicVertexBuffers()
{
  #pragma pack(push, 1)
  union
  {
    struct { int v10; };
    struct { char igi2_o1[36]; char zString[1024]; };
    char igi2_extent[1060];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int *p_nMaxVertices; // esi
  int v1; // edi
  unsigned int v2; // edx
  unsigned int v3; // eax
  unsigned int v4; // ecx
  struct IDirect3DDevice8 *v5; // ebx
  int v6; // ebp
  struct IDirect3DDevice8 *v7; // eax
  int v8; // ebx
  char *ErrorString; // eax

  p_nMaxVertices = &Direct3D_atDynamicVertexBuffer[0].nMaxVertices;
  v1 = 0;
  do
  {
    v2 = Direct3D_abDynamicVertexBufferFVF[v1];
    v3 = Direct3D_anDynamicVertexBufferSize[v1];
    v4 = Direct3D_anDynamicVertexBufferStride[v1];
    v5 = Direct3D_ptDevice;
    v6 = Direct3D_isHWTnL;
    p_nMaxVertices[3] = v2;
    *p_nMaxVertices = v3;
    igi2_frame.v10 = v4 * v3;
    v7 = Direct3D_ptDevice;
    p_nMaxVertices[2] = v4;
    p_nMaxVertices[1] = 0;
    v8 = v5->lpVtbl->CreateVertexBuffer(
           v7,
           igi2_frame.v10,
           (v6 != 0 ? 0 : 0x10) | 0x208,
           v2,
           D3DPOOL_DEFAULT,
           (struct IDirect3DVertexBuffer8 **)p_nMaxVertices - 1);
    if ( v8 )
    {
      sprintf(igi2_frame.zString, "Couldn't create dynamic vertex buffer");
      ErrorString = Direct3D_GetErrorString(v8);
      LDebug_Error(
        "%s\n\nDirectX error message: %s\nFile: %s Line: %d",
        igi2_frame.zString,
        ErrorString,
        "\\project\\igi2\\B\\2\\PC\\pc_direct3d.c",
        330);
      abort();
    }
    p_nMaxVertices += 5;
    ++v1;
  }
  while ( (int)p_nMaxVertices < 139166472 );
  Direct3D_tDynamicIndexBuffer.nMaxIndices = 500000;
  Direct3D_tDynamicIndexBuffer.bFormat = D3DFMT_INDEX16;
  Direct3D_ptDevice->lpVtbl->CreateIndexBuffer(
    Direct3D_ptDevice,
    1000000u,
    520u,
    D3DFMT_INDEX16,
    D3DPOOL_DEFAULT,
    (struct IDirect3DIndexBuffer8 **)&Direct3D_tDynamicIndexBuffer);
}

// source: b/2/pc/pc_direct3d.c:358  [anchor-hash]
void __cdecl Direct3D_DeleteDynamicVertexBuffers()
{
  struct DynamicVertexBuffer_t *v0; // esi

  v0 = Direct3D_atDynamicVertexBuffer;
  do
  {
    if ( v0->ptVertexBuffer )
    {
      v0->ptVertexBuffer->lpVtbl->Release(v0->ptVertexBuffer);
      v0->ptVertexBuffer = nullptr;
    }
    ++v0;
  }
  while ( (int)v0 < 139166468 );
  Direct3D_tDynamicIndexBuffer.ptIndexBuffer->lpVtbl->Release(Direct3D_tDynamicIndexBuffer.ptIndexBuffer);
  Direct3D_tDynamicIndexBuffer.ptIndexBuffer = nullptr;
}

// source: b/2/pc/pc_direct3d.c:386  [size]
// attributes: thunk
void __cdecl Direct3D_RestoreCallback()
{
  Direct3D_CreateDynamicVertexBuffers();
}

// source: b/2/pc/pc_direct3d.c:399  [size]
// attributes: thunk
void __cdecl Direct3D_DestroyCallback()
{
  Direct3D_DeleteDynamicVertexBuffers();
}

// source: b/2/pc/pc_direct3d.c:412  [anchor-hash]
void __cdecl Direct3D_SetClippingStateOn(void *pxContext)
{
  int v1; // esi
  char *ErrorString; // eax
  char zString[1024]; // [esp+Ch] [ebp-400h] BYREF

  v1 = Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_CLIPPING, 1u);
  if ( v1 )
  {
    sprintf(zString, "Couldn't set renderstate");
    ErrorString = Direct3D_GetErrorString(v1);
    LDebug_Error(
      "%s\n\nDirectX error message: %s\nFile: %s Line: %d",
      zString,
      ErrorString,
      "\\project\\igi2\\B\\2\\PC\\pc_direct3d.c",
      421);
    abort();
  }
}

// source: b/2/pc/pc_direct3d.c:429  [anchor-hash]
void __cdecl Direct3D_SetClippingStateOff(void *pxContext)
{
  int v1; // esi
  char *ErrorString; // eax
  char zString[1024]; // [esp+Ch] [ebp-400h] BYREF

  v1 = Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_CLIPPING, 0);
  if ( v1 )
  {
    sprintf(zString, "Couldn't set renderstate");
    ErrorString = Direct3D_GetErrorString(v1);
    LDebug_Error(
      "%s\n\nDirectX error message: %s\nFile: %s Line: %d",
      zString,
      ErrorString,
      "\\project\\igi2\\B\\2\\PC\\pc_direct3d.c",
      438);
    abort();
  }
}

// source: b/2/pc/pc_direct3d.c:446  [size]
struct DisplayCallbackChain_s *__cdecl Direct3D_CallChain(struct DisplayCallbackChain_s *ptChain)
{
  struct DisplayCallbackChain_s *i; // esi

  for ( i = ptChain; i; i = i->ptNext )
    ptChain = (struct DisplayCallbackChain_s *)((int (*)(void))i->pfCallback)();
  return ptChain;
}

// source: b/2/pc/pc_direct3d.c:463  [anchor-strings]
void __cdecl Direct3D_RegisterCallback(void (__cdecl *pfCB_)(), struct DisplayCallbackChain_s **pptFirst)
{
  int v2; // eax
  struct DisplayCallbackChain_s *v3; // ecx

  v2 = 0;
  while ( Direct3D_atCallback[v2].pfCallback )
  {
    if ( ++v2 >= 32 )
    {
      LDebug_Error("No more Direct3D callbacks available.");
      abort();
    }
  }
  v3 = (struct DisplayCallbackChain_s *)(8 * v2 + 139166048);
  v3->ptNext = *pptFirst;
  Direct3D_atCallback[v2].pfCallback = pfCB_;
  *pptFirst = v3;
}

// source: b/2/pc/pc_direct3d.c:491  [size]
char __cdecl Direct3D_RemoveCallback(
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

// source: b/2/pc/pc_direct3d.c:533  [size]
enum _D3DFORMAT __cdecl Direct3D_FindZBufferFormat(enum _D3DFORMAT nFormat, int iAdapter)
{
  if ( !Direct3D_ptObject->lpVtbl->CheckDeviceFormat(
          Direct3D_ptObject,
          iAdapter,
          D3DDEVTYPE_HAL,
          nFormat,
          2u,
          D3DRTYPE_SURFACE,
          D3DFMT_D24S8) )
    return D3DFMT_D24S8;
  if ( !Direct3D_ptObject->lpVtbl->CheckDeviceFormat(
          Direct3D_ptObject,
          iAdapter,
          D3DDEVTYPE_HAL,
          nFormat,
          2u,
          D3DRTYPE_SURFACE,
          D3DFMT_D24X4S4) )
    return D3DFMT_D24X4S4;
  if ( Direct3D_ptObject->lpVtbl->CheckDeviceFormat(
         Direct3D_ptObject,
         iAdapter,
         D3DDEVTYPE_HAL,
         nFormat,
         2u,
         D3DRTYPE_SURFACE,
         D3DFMT_D32) )
  {
    return Direct3D_ptObject->lpVtbl->CheckDeviceFormat(
             Direct3D_ptObject,
             iAdapter,
             D3DDEVTYPE_HAL,
             nFormat,
             2u,
             D3DRTYPE_SURFACE,
             D3DFMT_D24X8) != 0
         ? 80
         : 77;
  }
  return D3DFMT_D32;
}

// source: b/2/pc/pc_direct3d.c:597  [size]
int __cdecl Direct3D_GetAntialiasingLevel(enum _D3DFORMAT eFormat)
{
  enum _D3DFORMAT ZBufferFormat; // ebx
  enum _D3DMULTISAMPLE_TYPE i; // esi

  ZBufferFormat = Direct3D_FindZBufferFormat(eFormat, 0);
  for ( i = D3DMULTISAMPLE_2_SAMPLES; i < D3DMULTISAMPLE_16_SAMPLES; i += 2 )
  {
    if ( Direct3D_ptObject->lpVtbl->CheckDeviceMultiSampleType(Direct3D_ptObject, 0, D3DDEVTYPE_HAL, eFormat, 0, i) < 0 )
      break;
    if ( Direct3D_ptObject->lpVtbl->CheckDeviceMultiSampleType(
           Direct3D_ptObject,
           0,
           D3DDEVTYPE_HAL,
           ZBufferFormat,
           0,
           i) < 0 )
      break;
  }
  return i - 2;
}

// source: b/2/pc/pc_direct3d.c:626  [size]
void __cdecl Direct3D_CheckAntialiasingCaps()
{
  int v0; // esi

  v0 = 0;
  if ( AppContext_tAppContext.isServer == false )
  {
    if ( !Direct3D_ptObject )
    {
      Direct3D_ptObject = Direct3D_pfDirect3DCreate8(0xDCu);
      v0 = 1;
    }
    Direct3D_tAntialiasingCaps.nMaxAntialiasingLevel16 = Direct3D_GetAntialiasingLevel(D3DFMT_R5G6B5);
    Direct3D_tAntialiasingCaps.nMaxAntialiasingLevel32 = Direct3D_GetAntialiasingLevel(D3DFMT_X8R8G8B8);
    if ( v0 )
    {
      Direct3D_ptObject->lpVtbl->Release(Direct3D_ptObject);
      Direct3D_ptObject = nullptr;
    }
  }
}

// source: b/2/pc/pc_direct3d.c:666  [size]
int Direct3D_Open()
{
  struct HINSTANCE__ *LibraryA; // eax

  Direct3D_pfBlitCallback = nullptr;
  Direct3D_hD3D8DLL = nullptr;
  Direct3D_pfDirect3DCreate8 = nullptr;
  if ( AppContext_tAppContext.isMainMenu )
    return 0;
  LibraryA = LoadLibraryA("D3D8.DLL");
  Direct3D_hD3D8DLL = LibraryA;
  if ( !LibraryA )
  {
    LDebug_Error("Failed to load d3d8.dll\nPlease reinstall Microsoft DirectX");
    abort();
  }
  Direct3D_pfDirect3DCreate8 = (struct IDirect3D8 *(__stdcall *)(unsigned int))GetProcAddress(
                                                                                 LibraryA,
                                                                                 "Direct3DCreate8");
  Direct3D_CheckAntialiasingCaps();
  return 1;
}

// source: b/2/pc/pc_direct3d.c:698  [size]
void __cdecl Direct3D_UnsetMode(struct DisplayMode_s *ptDisplayMode)
{
  struct DisplayCallbackChain_s *i; // esi

  if ( AppContext_tAppContext.isMainMenu == false )
  {
    if ( Direct3D_ptDevice )
    {
      Direct3D_ptDevice->lpVtbl->EndScene(Direct3D_ptDevice);
      if ( Direct3D_ptDevice )
      {
        Direct3D_ptDevice->lpVtbl->SetTexture(Direct3D_ptDevice, 0, nullptr);
        Direct3D_ptDevice->lpVtbl->SetTexture(Direct3D_ptDevice, 1u, nullptr);
        Direct3D_ptDevice->lpVtbl->SetTexture(Direct3D_ptDevice, 2u, nullptr);
        Direct3D_ptDevice->lpVtbl->SetTexture(Direct3D_ptDevice, 3u, nullptr);
        Direct3D_ptDevice->lpVtbl->SetTexture(Direct3D_ptDevice, 4u, nullptr);
        Direct3D_ptDevice->lpVtbl->SetTexture(Direct3D_ptDevice, 5u, nullptr);
        Direct3D_ptDevice->lpVtbl->SetTexture(Direct3D_ptDevice, 6u, nullptr);
        Direct3D_ptDevice->lpVtbl->SetTexture(Direct3D_ptDevice, 7u, nullptr);
        Direct3D_ptDevice->lpVtbl->SetVertexShader(Direct3D_ptDevice, 2u);
        Direct3D_ptDevice->lpVtbl->SetStreamSource(Direct3D_ptDevice, 0, nullptr, 0);
        Direct3D_ptDevice->lpVtbl->SetStreamSource(Direct3D_ptDevice, 1u, nullptr, 0);
        Direct3D_ptDevice->lpVtbl->SetIndices(Direct3D_ptDevice, nullptr, 0);
        Direct3D_ptDevice->lpVtbl->SetRenderTarget(Direct3D_ptDevice, nullptr, nullptr);
      }
    }
    Direct3D_DeleteDynamicVertexBuffers();
    for ( i = Direct3D_ptUnsetModeCallback; i; i = i->ptNext )
      i->pfCallback();
    if ( Direct3D_ptDevice )
    {
      while ( Direct3D_ptDevice->lpVtbl->Release(Direct3D_ptDevice) )
        ;
      Direct3D_ptDevice = nullptr;
    }
    if ( Direct3D_ptObject )
    {
      while ( Direct3D_ptObject->lpVtbl->Release(Direct3D_ptObject) )
        ;
      Direct3D_ptObject = nullptr;
    }
  }
}

// source: b/2/pc/pc_direct3d.c:771  [size]
void __cdecl Direct3D_Close(void *pxUnused)
{
  if ( AppContext_tAppContext.isMainMenu == false )
    FreeLibrary(Direct3D_hD3D8DLL);
}

// source: b/2/pc/pc_direct3d.c:789  [size]
void __cdecl Direct3D_GUIDToString(char *zBuffer, struct _GUID tGUID)
{
  sprintf(
    zBuffer,
    "{%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X}",
    tGUID.Data1,
    tGUID.Data2,
    HIWORD(*(_DWORD *)&tGUID.Data2),
    tGUID.Data4[0],
    tGUID.Data4[1],
    tGUID.Data4[2],
    tGUID.Data4[3],
    tGUID.Data4[4],
    tGUID.Data4[5],
    tGUID.Data4[6],
    tGUID.Data4[7]);
}

// source: b/2/pc/pc_direct3d.c:813  [size~]
int __cdecl Direct3D_CreateDevice(
        int nFramebufferDepth,
        int nZBufferDepth,
        int nWidth,
        int nHeight,
        struct DisplayMode_s *ptMode,
        int iAdapter)
{
  int result; // eax

  if ( nWidth == -1 )
    nWidth = ptMode->nWidth;
  if ( nHeight == -1 )
    nHeight = ptMode->nHeight;
  Direct3D_tActiveParameters.BackBufferWidth = nWidth;
  Direct3D_tActiveParameters.BackBufferHeight = nHeight;
  Direct3D_tActiveParameters.hDeviceWindow = AppContext_tAppContext.hWnd;
  Direct3D_tActiveParameters.BackBufferFormat = (nFramebufferDepth == 16) + 22;
  Direct3D_tActiveParameters.BackBufferCount = 1;
  Direct3D_tActiveParameters.Windowed = AppContext_tAppContext.isActive == false;
  if ( AppContext_tAppContext.isActive == false || Direct3D_nAntialiasingLevel )
  {
    Direct3D_tActiveParameters.SwapEffect = D3DSWAPEFFECT_DISCARD;
    if ( AppContext_tAppContext.isActive == false )
    {
LABEL_17:
      Direct3D_tActiveParameters.MultiSampleType = D3DMULTISAMPLE_NONE;
      Direct3D_tActiveParameters.Flags = 1;
      goto LABEL_18;
    }
  }
  else
  {
    Direct3D_tActiveParameters.SwapEffect = D3DSWAPEFFECT_FLIP;
  }
  if ( ptMode->isLockableBackbuffer )
    goto LABEL_17;
  Direct3D_tActiveParameters.Flags = 0;
  if ( nFramebufferDepth == 16 )
  {
    if ( Direct3D_nAntialiasingLevel > Direct3D_tAntialiasingCaps.nMaxAntialiasingLevel16 )
    {
      Direct3D_tActiveParameters.MultiSampleType = Direct3D_tAntialiasingCaps.nMaxAntialiasingLevel16;
      goto LABEL_18;
    }
    goto LABEL_13;
  }
  if ( nFramebufferDepth != 16 )
  {
    if ( Direct3D_nAntialiasingLevel <= Direct3D_tAntialiasingCaps.nMaxAntialiasingLevel32 )
    {
LABEL_13:
      Direct3D_tActiveParameters.MultiSampleType = Direct3D_nAntialiasingLevel;
      goto LABEL_18;
    }
    Direct3D_tActiveParameters.MultiSampleType = Direct3D_tAntialiasingCaps.nMaxAntialiasingLevel32;
  }
LABEL_18:
  Direct3D_tActiveParameters.EnableAutoDepthStencil = 1;
  Direct3D_tActiveParameters.AutoDepthStencilFormat = Direct3D_FindZBufferFormat(
                                                        (enum _D3DFORMAT)((nFramebufferDepth == 16) + 22),
                                                        iAdapter);
  Direct3D_eAdapterFormat = Direct3D_tActiveParameters.BackBufferFormat;
  Direct3D_tActiveParameters.FullScreen_RefreshRateInHz = 0;
  Direct3D_tActiveParameters.FullScreen_PresentationInterval = AppContext_tAppContext.isActive != false
                                                             ? 0x80000000
                                                             : 0;
  if ( dword_73D248 )
    result = nFramebufferDepth;
  else
    result = Direct3D_ptObject->lpVtbl->CreateDevice(
               Direct3D_ptObject,
               iAdapter,
               D3DDEVTYPE_HAL,
               AppContext_tAppContext.hWnd,
               128u,
               &Direct3D_tActiveParameters,
               &Direct3D_ptDevice);
  if ( result || dword_73D248 )
  {
    result = Direct3D_ptObject->lpVtbl->CreateDevice(
               Direct3D_ptObject,
               iAdapter,
               D3DDEVTYPE_HAL,
               AppContext_tAppContext.hWnd,
               32u,
               &Direct3D_tActiveParameters,
               &Direct3D_ptDevice);
    Direct3D_isHWTnL = 0;
  }
  else
  {
    Direct3D_isHWTnL = 1;
  }
  return result;
}

// source: b/2/pc/pc_direct3d.c:938  [anchor-mhash]
void __cdecl Direct3D_SetClippingWindow(struct DisplaySetClippingWindowContext_s *ptClippingWindow)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct _D3DCLIPSTATUS8 tClipStatus; };
    struct { char igi2_o1[8]; char zString[1024]; };
    char igi2_extent[1032];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v1; // esi
  char *ErrorString; // eax

  igi2_frame.tClipStatus.ClipUnion = 31;
  igi2_frame.tClipStatus.ClipIntersection = 63;
  v1 = Direct3D_ptDevice->lpVtbl->SetClipStatus(Direct3D_ptDevice, &igi2_frame.tClipStatus);
  if ( v1 )
  {
    sprintf(igi2_frame.zString, "Couldn't set clipping window");
    ErrorString = Direct3D_GetErrorString(v1);
    LDebug_Error(
      "%s\n\nDirectX error message: %s\nFile: %s Line: %d",
      igi2_frame.zString,
      ErrorString,
      "\\project\\igi2\\B\\2\\PC\\pc_direct3d.c",
      956);
    abort();
  }
}

// source: b/2/pc/pc_direct3d.c:979  [size~]
void __cdecl Direct3D_SetMode(struct DisplayMode_s *ptMode)
{
  #pragma pack(push, 1)
  union
  {
    struct { int v21; };
    struct { char igi2_o1[4]; int v22[11]; };
    struct { char igi2_o2[52]; char v23[20]; };
    struct { char igi2_o3[72]; char zBuffer[40]; };
    struct { char igi2_o4[196]; char v25[984]; };
    struct { char igi2_o5[1180]; int v26; };
    struct { char igi2_o6[1248]; struct _GUID v27; };
    char igi2_extent[1268];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct RenderStateBlock_t *v1; // edx
  struct RenderStateBlock_t *v2; // ecx
  struct RenderStateBlock_t *v3; // edx
  struct DisplayMode_s *v4; // ebx
  int v5; // eax
  char v6; // cl
  struct IDirect3D8 *v7; // eax
  struct IDirect3D8 v8; // ecx
  unsigned int v9; // esi
  struct IDirect3D8Vtbl *lpVtbl; // ecx
  int Device; // esi
  char *ErrorString; // eax
  int v13; // esi
  char *v14; // eax
  struct IDirect3DDevice8Vtbl *v15; // ecx
  int v16; // esi
  char *v17; // eax
  struct DisplayCallbackChain_s *i; // esi
  int v19; // esi
  char *v20; // eax

  if ( AppContext_tAppContext.isMainMenu == false )
  {
    v4 = ptMode;
    qmemcpy(&Display_tActiveMode, ptMode, sizeof(Display_tActiveMode));
    *(_DWORD *)igi2_frame.v23 = strlen(Display_tActiveMode.zDeviceIdentifier);
    if ( !*(_DWORD *)igi2_frame.v23 )
    {
      Direct3D_GUIDToString(igi2_frame.zBuffer, (struct _GUID){0});
      v5 = 0;
      do
      {
        v6 = igi2_frame.zBuffer[v5];
        Display_tActiveMode.zDeviceIdentifier[v5++] = v6;
      }
      while ( v6 );
    }
    v7 = Direct3D_pfDirect3DCreate8(0xDCu);
    v8.lpVtbl = v7->lpVtbl;
    Direct3D_ptObject = v7;
    v9 = 0;
    if ( v8.lpVtbl->GetAdapterCount(v7) )
    {
      do
      {
        Direct3D_ptObject->lpVtbl->GetAdapterIdentifier(
          Direct3D_ptObject,
          v9,
          2u,
          (struct _D3DADAPTER_IDENTIFIER8 *)&igi2_frame.v25[4]);
        Direct3D_GUIDToString(igi2_frame.zBuffer, igi2_frame.v27);
        if ( strstr(igi2_frame.zBuffer, Display_tActiveMode.zDeviceIdentifier) )
          break;
        ++v9;
      }
      while ( v9 < Direct3D_ptObject->lpVtbl->GetAdapterCount(Direct3D_ptObject) );
    }
    if ( v9 == Direct3D_ptObject->lpVtbl->GetAdapterCount(Direct3D_ptObject) )
      v9 = 0;
    lpVtbl = Direct3D_ptObject->lpVtbl;
    Direct3D_iAdapterIndex = v9;
    lpVtbl->GetAdapterIdentifier(Direct3D_ptObject, v9, 2u, &Direct3D_tAdapterIdentifier);
    dword_73D248 = Direct3D_tAdapterIdentifier.VendorId == 4153;
    LODWORD(Direct3D_vOverlayMaxZ) = Direct3D_tAdapterIdentifier.VendorId == 4139
                                  && (Direct3D_tAdapterIdentifier.DeviceId == 1317
                                   || Direct3D_tAdapterIdentifier.DeviceId == 9511);
    if ( Direct3D_CreateDevice(-1, -1, -1, -1, ptMode, v9) )
    {
      if ( Direct3D_CreateDevice(16, -1, -1, -1, ptMode, v9) )
      {
        if ( Direct3D_CreateDevice(-1, 16, -1, -1, ptMode, v9) )
        {
          if ( Direct3D_CreateDevice(16, 16, -1, -1, ptMode, v9) )
          {
            Device = Direct3D_CreateDevice(16, 16, 640, 480, ptMode, v9);
            Display_tActiveMode.nWidth = 640;
            Display_tActiveMode.nHeight = 480;
            if ( Device )
            {
              sprintf(&igi2_frame.v25[4], Direct3D_tAdapterIdentifier.Description);
              ErrorString = Direct3D_GetErrorString(Device);
              LDebug_Error(
                "%s\n\nDirectX error message: %s\nFile: %s Line: %d",
                &igi2_frame.v25[4],
                ErrorString,
                "\\project\\igi2\\B\\2\\PC\\pc_direct3d.c",
                1082);
              goto LABEL_21;
            }
          }
        }
      }
    }
    v13 = Direct3D_ptDevice->lpVtbl->GetDeviceCaps(Direct3D_ptDevice, &Direct3D_tCaps);
    if ( v13 )
    {
      sprintf(&igi2_frame.v25[4], "Couldn't get device caps");
      v14 = Direct3D_GetErrorString(v13);
      LDebug_Error(
        "%s\n\nDirectX error message: %s\nFile: %s Line: %d",
        &igi2_frame.v25[4],
        v14,
        "\\project\\igi2\\B\\2\\PC\\pc_direct3d.c",
        1086);
      goto LABEL_21;
    }
    if ( (Direct3D_tCaps.TextureOpCaps & 0x10) == 0 || Direct3D_tCaps.MaxSimultaneousTextures < 2 )
    {
      LDebug_Error("The device on adapter %s is not capable of running IGI2", Direct3D_tAdapterIdentifier.Description);
LABEL_21:
      abort();
    }
    if ( !BYTE1(Direct3D_tCaps.VertexShaderVersion)
      || Direct3D_tCaps.MaxStreams < 2
      || Direct3D_isSoftwareVS
      || (Direct3D_isHWVertexShader = 1, !Direct3D_isHWTnL) )
    {
      Direct3D_isHWVertexShader = 0;
    }
    v15 = Direct3D_ptDevice->lpVtbl;
    Direct3D_isLowresZBuffer = Direct3D_tActiveParameters.AutoDepthStencilFormat == D3DFMT_D16;
    v15->GetDisplayMode(Direct3D_ptDevice, (struct _D3DDISPLAYMODE *)&igi2_frame.v23[4]);
    ptMode->nRefreshRate = *(_DWORD *)&igi2_frame.v23[12];
    igi2_frame.v22[5] = Display_tActiveMode.nWidth;
    *(float *)&igi2_frame.v22[8] = Direct3D_vMaxZ;
    *(float *)&igi2_frame.v22[7] = Direct3D_vMinZ;
    igi2_frame.v22[3] = 0;
    igi2_frame.v22[4] = 0;
    igi2_frame.v22[6] = Display_tActiveMode.nHeight;
    v16 = Direct3D_ptDevice->lpVtbl->SetViewport(Direct3D_ptDevice, (struct _D3DVIEWPORT8 *)&igi2_frame.v22[3]);
    if ( v16 )
    {
      sprintf(&igi2_frame.v25[4], "Couldn't set viewport");
      v17 = Direct3D_GetErrorString(v16);
      LDebug_Error(
        "%s\n\nDirectX error message: %s\nFile: %s Line: %d",
        &igi2_frame.v25[4],
        v17,
        "\\project\\igi2\\B\\2\\PC\\pc_direct3d.c",
        1109);
      goto LABEL_21;
    }
    Direct3D_SetClippingWindow((struct DisplaySetClippingWindowContext_s *)&igi2_frame.v22[3]);
    for ( i = Direct3D_ptSetModeCallback; i; i = i->ptNext )
      i->pfCallback();
    Direct3D_CreateDynamicVertexBuffers();
    if ( PeekMessageA((LPMSG)&igi2_frame.v22[3], nullptr, 0, 0, 0) )
    {
      do
      {
        if ( GetMessageA((LPMSG)&igi2_frame.v22[3], nullptr, 0, 0) )
        {
          TranslateMessage((MSG *)&igi2_frame.v22[3]);
          DispatchMessageA((MSG *)&igi2_frame.v22[3]);
        }
      }
      while ( PeekMessageA((LPMSG)&igi2_frame.v22[3], nullptr, 0, 0, 0) );
      v4 = ptMode;
    }
    if ( Direct3D_nAntialiasingLevel > D3DMULTISAMPLE_NONE
      && !v4->isLockableBackbuffer
      && Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_MULTISAMPLEANTIALIAS, 1u) < 0 )
    {
      LDebug_Error("Direct3D: Could not set antialiasing mode");
      goto LABEL_21;
    }
    if ( Direct3D_ptDevice )
    {
      v19 = Direct3D_ptDevice->lpVtbl->BeginScene(Direct3D_ptDevice);
      if ( v19 )
      {
        sprintf(&igi2_frame.v25[4], "BeginScene failed.");
        v20 = Direct3D_GetErrorString(v19);
        LDebug_Error(
          "%s\n\nDirectX error message: %s\nFile: %s Line: %d",
          &igi2_frame.v25[4],
          v20,
          "\\project\\igi2\\B\\2\\PC\\pc_direct3d.c",
          1168);
        goto LABEL_21;
      }
    }
    Real_nTempCW = igi2_fpu_or(0xC00u);
    v1 = Direct3D_ptBlendStateBlock;
    igi2_frame.v26 = igi2_frame.v21;
    memset(&Direct3D_tState, 0xFFu, sizeof(Direct3D_tState));
    Direct3D_ptTextureStateBlock->eCurrentState = -1;
    v2 = Direct3D_ptGenericStateBlock;
    v1->eCurrentState = -1;
    v3 = Direct3D_ptClippingStateBlock;
    v2->eCurrentState = -1;
    v3->eCurrentState = -1;
  }
}

// source: b/2/pc/pc_direct3d.c:1174  [anchor-callee]
void __cdecl Direct3D_InvalidateDevice()
{
  int v0; // esi
  char *ErrorString; // eax
  struct DisplayCallbackChain_s *i; // esi
  char zString[1024]; // [esp+8h] [ebp-400h] BYREF

  if ( !Direct3D_isDeviceLost )
  {
    v0 = Direct3D_ptDevice->lpVtbl->ResourceManagerDiscardBytes(Direct3D_ptDevice, 0);
    if ( v0 )
    {
      sprintf(zString, "Couldn't evict textures");
      ErrorString = Direct3D_GetErrorString(v0);
      LDebug_Error(
        "%s\n\nDirectX error message: %s\nFile: %s Line: %d",
        zString,
        ErrorString,
        "\\project\\igi2\\B\\2\\PC\\pc_direct3d.c",
        1194);
      abort();
    }
    Direct3D_ptDevice->lpVtbl->SetTexture(Direct3D_ptDevice, 0, nullptr);
    Direct3D_ptDevice->lpVtbl->SetTexture(Direct3D_ptDevice, 1u, nullptr);
    for ( i = Direct3D_ptDestroyCallback; i; i = i->ptNext )
      i->pfCallback();
    Direct3D_isDeviceLost = 1;
  }
}

// source: b/2/pc/pc_direct3d.c:1198  [anchor-hash]
enum bool __cdecl Direct3D_ResetDevice()
{
  struct DisplayCallbackChain_s *i; // esi
  struct RenderStateBlock_t *v1; // ecx
  struct RenderStateBlock_t *v2; // edx
  struct RenderStateBlock_t *v3; // ecx

  if ( Direct3D_ptDevice->lpVtbl->Reset(Direct3D_ptDevice, &Direct3D_tActiveParameters) )
  {
    AppContext_tAppContext.isMainMenu = true;
    return false;
  }
  else
  {
    for ( i = Direct3D_ptRestoreCallback; i; i = i->ptNext )
      i->pfCallback();
    memset(&Direct3D_tState, 0xFFu, sizeof(Direct3D_tState));
    v1 = Direct3D_ptBlendStateBlock;
    Direct3D_ptTextureStateBlock->eCurrentState = -1;
    v2 = Direct3D_ptGenericStateBlock;
    v1->eCurrentState = -1;
    v3 = Direct3D_ptClippingStateBlock;
    v2->eCurrentState = -1;
    v3->eCurrentState = -1;
    AppContext_tAppContext.isMainMenu = false;
    Real_nTempCW = igi2_fpu_or(0xC00u);
    Direct3D_isDeviceLost = 0;
    return true;
  }
}

// source: b/2/pc/pc_direct3d.c:1228  [anchor-caller]
void __cdecl Direct3D_SwapBuffers(void *pxUnused)
{
  int v1; // edi
  DWORD PerformanceCounter; // eax
  int v3; // esi
  enum bool v4; // eax
  int v5; // esi
  char *ErrorString; // eax
  struct RenderStateBlock_t *v7; // edx
  struct RenderStateBlock_t *v8; // ecx
  struct RenderStateBlock_t *v9; // edx
  char zString[1024]; // [esp+1Ch] [ebp-400h] BYREF

  if ( Direct3D_ptDevice )
  {
    Direct3D_ptDevice->lpVtbl->EndScene(Direct3D_ptDevice);
    v1 = Direct3D_ptDevice->lpVtbl->Present(Direct3D_ptDevice, nullptr, nullptr, nullptr, nullptr);
    if ( Timer_isPerformanceCounter )
      PerformanceCounter = Timer_GetPerformanceCounter();
    else
      PerformanceCounter = GetTickCount();
    v3 = PerformanceCounter - Timer_nStartTime;
    DebugConsole_PushActiveConsole(3);
    DebugConsole_printf("Present time %d ms\n", v3 - dword_73D268);
    DebugConsole_PopActiveConsole();
    dword_73D268 = v3;
    if ( v1 == -2005530520 )
    {
      Direct3D_InvalidateDevice();
      Direct3D_ResetDevice();
    }
    else if ( Direct3D_isToggleWindowed )
    {
      v4 = AppContext_tAppContext.isActive == false;
      AppContext_tAppContext.isActive = v4;
      if ( v4 )
      {
        GetWindowRect(AppContext_tAppContext.hWnd, &X_73d254);
        SetWindowLongA(AppContext_tAppContext.hWnd, -16, Main_dwFullscreenWindowStyle);
        dword_73D26C = 1;
      }
      else
      {
        SetWindowLongA(AppContext_tAppContext.hWnd, -16, Main_dwWindowStyle);
      }
      Direct3D_InvalidateDevice();
      Direct3D_tActiveParameters.Windowed = AppContext_tAppContext.isActive == false;
      Direct3D_tActiveParameters.FullScreen_PresentationInterval = AppContext_tAppContext.isActive != false;
      Direct3D_isToggleWindowed = Direct3D_ResetDevice() == false;
      if ( AppContext_tAppContext.isActive == false )
      {
        if ( !dword_73D26C )
        {
          X_73d254.left = 10;
          X_73d254.top = 30;
          X_73d254.right = Display_tActiveMode.nWidth + 10;
          X_73d254.bottom = Display_tActiveMode.nHeight + 30;
          AdjustWindowRect(&X_73d254, (DWORD)&MTP_atLODVirModel[29].atBoneVertexRefs[19].atVertexRefs[54], 0);
          dword_73D26C = 1;
        }
        SetWindowPos(
          AppContext_tAppContext.hWnd,
          (HWND)0xFFFFFFFE,
          X_73d254.left,
          X_73d254.top,
          X_73d254.right - X_73d254.left,
          X_73d254.bottom - X_73d254.top,
          0x40u);
      }
    }
    v5 = Direct3D_ptDevice->lpVtbl->BeginScene(Direct3D_ptDevice);
    if ( v5 )
    {
      sprintf(zString, "BeginScene failed");
      ErrorString = Direct3D_GetErrorString(v5);
      LDebug_Error(
        "%s\n\nDirectX error message: %s\nFile: %s Line: %d",
        zString,
        ErrorString,
        "\\project\\igi2\\B\\2\\PC\\pc_direct3d.c",
        1321);
      abort();
    }
  }
  v7 = Direct3D_ptBlendStateBlock;
  memset(&Direct3D_tState, 0xFFu, sizeof(Direct3D_tState));
  Direct3D_ptTextureStateBlock->eCurrentState = -1;
  v8 = Direct3D_ptGenericStateBlock;
  v7->eCurrentState = -1;
  v9 = Direct3D_ptClippingStateBlock;
  v8->eCurrentState = -1;
  v9->eCurrentState = -1;
}

// source: b/2/pc/pc_direct3d.c:1326  [size]
void __cdecl Direct3D_WaitVB(void *pxUnused)
{
  ;
}

// source: b/2/pc/pc_direct3d.c:1340  [anchor-mhash]
void __cdecl Direct3D_Clear(void *pxUnused)
{
  int v1; // eax
  int v2; // esi
  char *ErrorString; // eax
  char zString[1024]; // [esp+1Ch] [ebp-400h] BYREF

  if ( Direct3D_ptDevice )
  {
    if ( Direct3D_tActiveParameters.AutoDepthStencilFormat == D3DFMT_D24S8
      || Direct3D_tActiveParameters.AutoDepthStencilFormat == D3DFMT_D24X4S4 )
    {
      v1 = 4;
    }
    else
    {
      v1 = 0;
    }
    v2 = ((int (__stdcall *)(struct IDirect3DDevice8 *, _DWORD, _DWORD, int, int, int, _DWORD))Direct3D_ptDevice->lpVtbl->Clear)(
           Direct3D_ptDevice,
           0,
           0,
           v1 | 3,
           Display_tBackgroundColor.nZ + ((Display_tBackgroundColor.nY + (Display_tBackgroundColor.nX << 8)) << 8),
           1065353216,
           0);
    if ( v2 )
    {
      sprintf(zString, "Couldn't clear screen");
      ErrorString = Direct3D_GetErrorString(v2);
      LDebug_Error(
        "%s\n\nDirectX error message: %s\nFile: %s Line: %d",
        zString,
        ErrorString,
        "\\project\\igi2\\B\\2\\PC\\pc_direct3d.c",
        1367);
      abort();
    }
  }
}

// source: b/2/pc/pc_direct3d.c:1367  [anchor-mhash]
void __cdecl Direct3D_Snapshot(struct DisplaySnapshotContext_s *ptSnapshotContext, int ltcg_arg1)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct IDirect3DSurface8 *ptFrontBufferSurface; };
    struct { char igi2_o1[4]; int nY; };
    struct { char igi2_o2[8]; struct _D3DLOCKED_RECT tLockedRect; };
    struct { char igi2_o3[16]; unsigned int nBPos; };
    struct { char igi2_o4[20]; int v25; };
    struct { char igi2_o5[24]; int nRPos; };
    struct { char igi2_o6[28]; unsigned int nBSize; };
    struct { char igi2_o7[32]; unsigned int nASize; };
    struct { char igi2_o8[36]; unsigned int nGSize; };
    struct { char igi2_o9[40]; unsigned int nRSize; };
    struct { char igi2_o10[44]; char zString[1024]; };
    char igi2_extent[1068];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v2; // esi
  char *ErrorString; // eax
  int v4; // esi
  char *v5; // eax
  int v6; // esi
  char *v7; // eax
  unsigned int *pBits; // edi
  unsigned __int8 *anRGBBuffer; // eax
  char v10; // dl
  int nWidth; // ecx
  int v12; // ebp
  unsigned int v13; // esi
  unsigned int v14; // ebx
  char v15; // cl
  _BYTE *v16; // eax
  unsigned int v17; // ebx
  char v18; // cl
  int v19; // esi
  char *v20; // eax

  if ( Direct3D_ptDevice || AppContext_tAppContext.isActive == false )
  {
    v2 = Direct3D_ptDevice->lpVtbl->CreateImageSurface(
           Direct3D_ptDevice,
           Display_tActiveMode.nWidth,
           Display_tActiveMode.nHeight,
           D3DFMT_A8R8G8B8,
           &igi2_frame.ptFrontBufferSurface);
    if ( v2 )
    {
      sprintf(igi2_frame.zString, "Failed to create front buffer.");
      ErrorString = Direct3D_GetErrorString(v2);
      LDebug_Error(
        "%s\n\nDirectX error message: %s\nFile: %s Line: %d",
        igi2_frame.zString,
        ErrorString,
        "\\project\\igi2\\B\\2\\PC\\pc_direct3d.c",
        1418);
      goto LABEL_5;
    }
    v4 = Direct3D_ptDevice->lpVtbl->GetFrontBuffer(Direct3D_ptDevice, igi2_frame.ptFrontBufferSurface);
    if ( v4 )
    {
      sprintf(igi2_frame.zString, "Failed to acquire front buffer.");
      v5 = Direct3D_GetErrorString(v4);
      LDebug_Error(
        "%s\n\nDirectX error message: %s\nFile: %s Line: %d",
        igi2_frame.zString,
        v5,
        "\\project\\igi2\\B\\2\\PC\\pc_direct3d.c",
        1422);
      goto LABEL_5;
    }
    igi2_frame.tLockedRect.Pitch = 0;
    igi2_frame.tLockedRect.pBits = nullptr;
    v6 = igi2_frame.ptFrontBufferSurface->lpVtbl->LockRect(igi2_frame.ptFrontBufferSurface, &igi2_frame.tLockedRect, nullptr, 0x8000u);
    if ( v6 )
    {
      sprintf(igi2_frame.zString, "Failed to lock front buffer.");
      v7 = Direct3D_GetErrorString(v6);
      LDebug_Error(
        "%s\n\nDirectX error message: %s\nFile: %s Line: %d",
        igi2_frame.zString,
        v7,
        "\\project\\igi2\\B\\2\\PC\\pc_direct3d.c",
        1429);
      goto LABEL_5;
    }
    Direct3D_GetColorLayout(
      Direct3D_eAdapterFormat,
      &igi2_frame.nY,
      &igi2_frame.v25,
      &igi2_frame.nRPos,
      (int *)&igi2_frame.nBPos,
      (int *)&igi2_frame.nASize,
      (int *)&igi2_frame.nRSize,
      (int *)&igi2_frame.nGSize,
      (int *)&igi2_frame.nBSize);
    pBits = (unsigned int *)igi2_frame.tLockedRect.pBits;
    anRGBBuffer = ptSnapshotContext->anRGBBuffer;
    igi2_frame.nY = 0;
    if ( Display_tActiveMode.nHeight > 0 )
    {
      v10 = igi2_frame.nBPos;
      nWidth = Display_tActiveMode.nWidth;
      do
      {
        v12 = 0;
        if ( nWidth > 0 )
        {
          do
          {
            v13 = *pBits;
            v14 = *pBits >> v10;
            v15 = igi2_frame.nRPos;
            v16 = anRGBBuffer + 1;
            ++pBits;
            *(v16 - 1) = v14;
            v17 = v13 >> v15;
            v18 = igi2_frame.v25;
            *v16++ = v17;
            anRGBBuffer = v16 + 1;
            ++v12;
            *(anRGBBuffer - 1) = v13 >> v18;
            nWidth = Display_tActiveMode.nWidth;
          }
          while ( v12 < Display_tActiveMode.nWidth );
        }
        pBits = (unsigned int *)((char *)pBits + igi2_frame.tLockedRect.Pitch - 4 * nWidth);
        ++igi2_frame.nY;
      }
      while ( igi2_frame.nY < Display_tActiveMode.nHeight );
    }
    v19 = igi2_frame.ptFrontBufferSurface->lpVtbl->UnlockRect(igi2_frame.ptFrontBufferSurface);
    if ( v19 )
    {
      sprintf(igi2_frame.zString, "Failed to unlock front buffer.");
      v20 = Direct3D_GetErrorString(v19);
      LDebug_Error(
        "%s\n\nDirectX error message: %s\nFile: %s Line: %d",
        igi2_frame.zString,
        v20,
        "\\project\\igi2\\B\\2\\PC\\pc_direct3d.c",
        1453);
LABEL_5:
      abort();
    }
    igi2_frame.ptFrontBufferSurface->lpVtbl->Release(igi2_frame.ptFrontBufferSurface);
  }
}

// source: b/2/pc/pc_direct3d.c:1455  [anchor-hash]
void __cdecl Direct3D_Blit(struct DisplayBlitContext_s *ptDisplayBlitContext)
{
  if ( Direct3D_pfBlitCallback )
    Direct3D_pfBlitCallback(ptDisplayBlitContext);
}

// source: b/2/pc/pc_direct3d.c:1471  [anchor-hash]
int __cdecl Direct3D_GetDepth(enum _D3DFORMAT eFormat)
{
  int result; // eax
  bool v2; // zf

  if ( eFormat > D3DFMT_DXT1 )
  {
    if ( eFormat > D3DFMT_DXT4 )
    {
      v2 = eFormat == D3DFMT_DXT5;
    }
    else
    {
      if ( eFormat == D3DFMT_DXT4 || eFormat == D3DFMT_DXT2 )
        return 32;
      v2 = eFormat == D3DFMT_DXT3;
    }
    if ( !v2 )
      return 0;
    return 32;
  }
  if ( eFormat == D3DFMT_DXT1 )
    return 32;
  switch ( eFormat )
  {
    case D3DFMT_R8G8B8:
      result = 24;
      break;
    case D3DFMT_A8R8G8B8:
    case D3DFMT_X8R8G8B8:
      return 32;
    case D3DFMT_R5G6B5:
    case D3DFMT_X1R5G5B5:
    case D3DFMT_A1R5G5B5:
    case D3DFMT_A4R4G4B4:
    case D3DFMT_A8R3G3B2:
    case D3DFMT_X4R4G4B4:
      result = 16;
      break;
    case D3DFMT_R3G3B2:
    case D3DFMT_A8:
      result = 8;
      break;
    default:
      return 0;
  }
  return result;
}

// source: b/2/pc/pc_direct3d.c:1528  [anchor-strings]
int *__cdecl Direct3D_GetColorLayout(
        enum _D3DFORMAT eFormat,
        int *nAPos,
        int *nRPos,
        int *nGPos,
        int *nBPos,
        int *nASize,
        int *nRSize,
        int *nGSize,
        int *nBSize)
{
  switch ( eFormat )
  {
    case D3DFMT_R8G8B8:
    case D3DFMT_X8R8G8B8:
      *nAPos = 0;
      *nRPos = 16;
      *nGPos = 8;
      *nBPos = 0;
      *nASize = 0;
      goto LABEL_3;
    case D3DFMT_A8R8G8B8:
      *nAPos = 24;
      *nRPos = 16;
      *nGPos = 8;
      *nBPos = 0;
      *nASize = 8;
LABEL_3:
      *nRSize = 8;
      *nGSize = 8;
      *nBSize = 8;
      return nBSize;
    case D3DFMT_R5G6B5:
      *nAPos = 0;
      *nRPos = 11;
      *nGPos = 5;
      *nBPos = 0;
      *nASize = 0;
      *nRSize = 5;
      *nGSize = 6;
      *nBSize = 5;
      return nBSize;
    case D3DFMT_X1R5G5B5:
      *nAPos = 0;
      *nRPos = 10;
      *nGPos = 5;
      *nBPos = 0;
      *nASize = 0;
      goto LABEL_7;
    case D3DFMT_A1R5G5B5:
      *nAPos = 15;
      *nRPos = 10;
      *nGPos = 5;
      *nBPos = 0;
      *nASize = 1;
LABEL_7:
      *nRSize = 5;
      *nGSize = 5;
      *nBSize = 5;
      return nBSize;
    case D3DFMT_A4R4G4B4:
      *nAPos = 12;
      *nRPos = 8;
      *nGPos = 4;
      *nBPos = 0;
      *nASize = 4;
      goto LABEL_10;
    case D3DFMT_R3G3B2:
      *nAPos = 0;
      *nRPos = 5;
      *nGPos = 2;
      *nBPos = 0;
      *nASize = 0;
      goto LABEL_12;
    case D3DFMT_A8:
      *nAPos = 0;
      *nRPos = 0;
      *nGPos = 0;
      *nBPos = 0;
      *nASize = 8;
      *nRSize = 0;
      *nGSize = 0;
      *nBSize = 0;
      return nBSize;
    case D3DFMT_A8R3G3B2:
      *nAPos = 8;
      *nRPos = 5;
      *nGPos = 2;
      *nBPos = 0;
      *nASize = 8;
LABEL_12:
      *nRSize = 3;
      *nGSize = 3;
      *nBSize = 2;
      break;
    case D3DFMT_X4R4G4B4:
      *nAPos = 12;
      *nRPos = 8;
      *nGPos = 4;
      *nBPos = 0;
      *nASize = 0;
LABEL_10:
      *nRSize = 4;
      *nGSize = 4;
      *nBSize = 4;
      break;
    default:
      LDebug_Error("Format not supported");
      abort();
  }
  return nBSize;
}

// source: b/2/pc/pc_direct3d.c:1666  [size~]
void __cdecl Direct3D_EnumDevices(struct EnumDisplayDevicesContext_t *ptContext, int ltcg_arg1)
{
  #pragma pack(push, 1)
  union
  {
    struct { int v18; };
    struct { char igi2_o1[4]; int v19; };
    struct { char igi2_o2[8]; unsigned int v20; };
    struct { char igi2_o3[12]; char *v21; };
    struct { char igi2_o4[16]; signed int v22; };
    struct { char igi2_o5[20]; int v23; };
    struct { char igi2_o6[24]; int v24; };
    struct { char igi2_o7[32]; enum _D3DFORMAT v25; };
    struct { char igi2_o8[36]; int v26; };
    struct { char igi2_o9[48]; char v27[512]; };
    struct { char igi2_o10[560]; char v28[556]; };
    char igi2_extent[2128];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  signed int v2; // edi
  struct IDirect3D8 *v3; // eax
  struct EnumDisplayDevicesContext_t *v4; // ebx
  struct IDirect3D8 v5; // ecx
  unsigned int nMaxDisplayDevices; // esi
  char *zIdentifier; // esi
  unsigned int v8; // esi
  int v9; // esi
  int v10; // ebx
  int v11; // esi
  int v12; // ebp
  int v13; // edx
  enum _D3DFORMAT v14; // eax
  char *v15; // ecx
  char *v16; // ecx
  char *ErrorString; // eax

  v2 = 0;
  if ( AppContext_tAppContext.isMainMenu == false )
  {
    v3 = Direct3D_pfDirect3DCreate8(0xDCu);
    v4 = ptContext;
    v5.lpVtbl = v3->lpVtbl;
    nMaxDisplayDevices = ptContext->nMaxDisplayDevices;
    Direct3D_ptObject = v3;
    if ( nMaxDisplayDevices >= v5.lpVtbl->GetAdapterCount(v3) )
      igi2_frame.v19 = Direct3D_ptObject->lpVtbl->GetAdapterCount(Direct3D_ptObject);
    else
      igi2_frame.v19 = nMaxDisplayDevices;
    igi2_frame.v22 = 0;
    if ( igi2_frame.v19 > 0 )
    {
      igi2_frame.v18 = 0;
      do
      {
        zIdentifier = v4->ptDisplayDevice[igi2_frame.v18].zIdentifier;
        igi2_frame.v21 = zIdentifier;
        Direct3D_ptObject->lpVtbl->GetAdapterIdentifier(
          Direct3D_ptObject,
          v2,
          2u,
          (struct _D3DADAPTER_IDENTIFIER8 *)&igi2_frame.v26);
        strcpy(zIdentifier + 128, &igi2_frame.v27[500]);
        strcpy(zIdentifier, (char *)&igi2_frame.v26);
        v8 = 0;
        igi2_frame.v20 = 0;
        if ( Direct3D_ptObject->lpVtbl->GetAdapterModeCount(Direct3D_ptObject, v2) )
        {
          do
          {
            v9 = Direct3D_ptObject->lpVtbl->EnumAdapterModes(Direct3D_ptObject, v2, v8, (struct _D3DDISPLAYMODE *)&igi2_frame.v23);
            if ( v9 )
            {
              sprintf(&igi2_frame.v28[544], "Couldn't enumerate display modes.");
              ErrorString = Direct3D_GetErrorString(v9);
              LDebug_Error(
                "%s\n\nDirectX error message: %s\nFile: %s Line: %d",
                &igi2_frame.v28[544],
                ErrorString,
                "\\project\\igi2\\B\\2\\PC\\pc_direct3d.c",
                1730);
              abort();
            }
            v10 = igi2_frame.v23;
            if ( igi2_frame.v23 )
            {
              v11 = igi2_frame.v24;
              if ( igi2_frame.v24 )
              {
                v12 = Display_nModes;
                if ( Display_nModes < 1000 )
                {
                  v13 = Display_nModes;
                  memset(&Display_atMode[Display_nModes], 0, sizeof(struct DisplayMode_s));
                  v14 = igi2_frame.v25;
                  Display_atMode[v12].nWidth = v10;
                  Display_atMode[v12].nHeight = v11;
                  Display_atMode[v12].nBitsPerPixel = Direct3D_GetDepth(v14);
                  v15 = igi2_frame.v21 + 128;
                  Display_atMode[v12].eRenderMode = Direct3D_eRenderMode;
                  Display_atMode[v12].nBackBuffers = 1;
                  if ( igi2_frame.v21 == (char *)-128 )
                    v15 = (char *)&g_zInitialValue;
                  strcpy(Display_atMode[v13].zDeviceDescription, v15);
                  v16 = igi2_frame.v21;
                  if ( !igi2_frame.v21 )
                    v16 = (char *)&g_zInitialValue;
                  strcpy(Display_atMode[v13].zDeviceIdentifier, v16);
                  v2 = igi2_frame.v22;
                  Display_nModes = v12 + 1;
                }
              }
            }
            v8 = ++igi2_frame.v20;
          }
          while ( igi2_frame.v20 < Direct3D_ptObject->lpVtbl->GetAdapterModeCount(Direct3D_ptObject, v2) );
          v4 = ptContext;
        }
        ++*v4->pnNumDisplayDevices;
        igi2_frame.v22 = ++v2;
        ++igi2_frame.v18;
      }
      while ( v2 < igi2_frame.v19 );
    }
    Direct3D_ptObject->lpVtbl->Release(Direct3D_ptObject);
    Direct3D_ptObject = nullptr;
    Real_nTempCW = igi2_fpu_or(0xC00u);
  }
}

// source: b/2/pc/pc_direct3d.c:1753  [size]
void __cdecl Direct3D_GetGFXCaps(struct GetGFXCapsContext_t *ptContext)
{
  ;
}

// source: b/2/pc/pc_direct3d.c:1769  [anchor-caller]
int __cdecl Direct3D_WinProcCB(struct HWND__ *hWnd, unsigned int nMessage, unsigned int wParam, int lParam)
{
  LONG left; // edx
  int v6; // ecx
  LONG bottom; // edx
  struct tagRECT rect; // [esp+0h] [ebp-10h] BYREF

  if ( RenderMode_eActiveRenderMode != Direct3D_eRenderMode || !Direct3D_ptObject )
    return 1;
  if ( nMessage > 0x101 )
  {
    if ( nMessage == 260 )
    {
LABEL_8:
      if ( wParam == 18 )
      {
        dword_73D240 = 1;
        return 1;
      }
      if ( wParam == 13 )
      {
        if ( dword_73D240 )
          Direct3D_isToggleWindowed = 1;
      }
      return 1;
    }
    if ( nMessage != 261 )
      return 1;
LABEL_19:
    if ( wParam == 18 )
    {
      dword_73D240 = 0;
      return 1;
    }
    return 1;
  }
  if ( nMessage == 257 )
    goto LABEL_19;
  if ( nMessage != 6 )
  {
    if ( nMessage == 36 )
    {
      rect.left = 0;
      rect.top = 0;
      rect.right = Display_tActiveMode.nWidth;
      rect.bottom = Display_tActiveMode.nHeight;
      AdjustWindowRect(&rect, AppContext_tAppContext.isActive != false ? 0x80000000 : 13565952, 0);
      left = rect.left;
      *(_DWORD *)(lParam + 24) = 100;
      *(_DWORD *)(lParam + 28) = 100;
      v6 = rect.right - left;
      bottom = rect.bottom;
      *(_DWORD *)(lParam + 32) = v6;
      *(_DWORD *)(lParam + 36) = bottom - rect.top;
      return 1;
    }
    if ( nMessage != 256 )
      return 1;
    goto LABEL_8;
  }
  if ( !(_WORD)wParam || HIWORD(wParam) )
  {
    if ( AppContext_tAppContext.isDebugged )
    {
      InvalidateRect(hWnd, nullptr, 0);
      AppContext_SetActive(false);
      return 1;
    }
    goto LABEL_16;
  }
  if ( AppContext_tAppContext.isDebugged == false )
  {
LABEL_16:
    AppContext_SetActive(true);
    return 1;
  }
  return 1;
}

// source: b/2/pc/pc_direct3d.c:1859  [anchor-hash]
char *__cdecl Direct3D_GetErrorString(int nD3DError)
{
  char *result; // eax

  if ( nD3DError > -2005530593 )
  {
    switch ( nD3DError )
    {
      case -2005530591:
        result = "D3DERR_CONFLICTINGRENDERSTATE";
        break;
      case -2005530590:
        result = "D3DERR_UNSUPPORTEDTEXTUREFILTER";
        break;
      case -2005530586:
        result = "D3DERR_CONFLICTINGTEXTUREPALETTE";
        break;
      case -2005530585:
        result = "D3DERR_DRIVERINTERNALERROR";
        break;
      case -2005530522:
        result = "D3DERR_NOTFOUND";
        break;
      case -2005530521:
        result = "D3DERR_MOREDATA";
        break;
      case -2005530520:
        result = "D3DERR_DEVICELOST";
        break;
      case -2005530519:
        result = "D3DERR_DEVICENOTRESET";
        break;
      case -2005530518:
        result = "D3DERR_NOTAVAILABLE";
        break;
      case -2005530517:
        result = "D3DERR_INVALIDDEVICE";
        break;
      case -2005530516:
        result = "D3DERR_INVALIDCALL";
        break;
      default:
        return &g_zFileName.atPictureResources[31].zResourceFilename[44];
    }
  }
  else if ( nD3DError == -2005530593 )
  {
    return "D3DERR_UNSUPPORTEDFACTORVALUE";
  }
  else if ( nD3DError > -2005530599 )
  {
    switch ( nD3DError )
    {
      case -2005530598:
        result = "D3DERR_UNSUPPORTEDCOLORARG";
        break;
      case -2005530597:
        result = "D3DERR_UNSUPPORTEDALPHAOPERATION";
        break;
      case -2005530596:
        result = "D3DERR_UNSUPPORTEDALPHAARG";
        break;
      case -2005530595:
        result = "D3DERR_TOOMANYOPERATIONS";
        break;
      case -2005530594:
        result = "D3DERR_CONFLICTINGTEXTUREFILTER";
        break;
    }
  }
  else if ( nD3DError == -2005530599 )
  {
    return "D3DERR_UNSUPPORTEDCOLOROPERATION";
  }
  else
  {
    if ( nD3DError > -2147024809 )
    {
      if ( nD3DError == -2005532292 )
        return "D3DERR_OUTOFVIDEOMEMORY";
      if ( nD3DError == -2005530600 )
        return "D3DERR_WRONGTEXTUREFORMAT";
    }
    else
    {
      switch ( nD3DError )
      {
        case -2147024809:
          return "E_INVALIDARG";
        case -2147467259:
          return "E_FAIL";
        case -2147024882:
          return "E_OUTOFMEMORY";
      }
    }
    return &g_zFileName.atPictureResources[31].zResourceFilename[44];
  }
  return result;
}

// source: b/2/pc/pc_direct3d.c:1945  [anchor-strings]
void __cdecl Direct3D_New()
{
  unsigned __int32 v0; // eax
  int v1; // ecx
  unsigned __int32 v2; // edx
  int v3; // ecx
  unsigned __int32 v4; // edx
  int v5; // ecx
  unsigned __int32 v6; // edx
  int v7; // ecx
  unsigned __int32 v8; // edx
  int v9; // ecx
  unsigned __int32 v10; // edx
  int v11; // ecx
  unsigned __int32 v12; // edx
  int v13; // ecx
  unsigned __int32 v14; // edx
  int v15; // ecx
  unsigned __int32 v16; // edx
  int v17; // ecx
  unsigned __int32 v18; // edx
  int v19; // ecx
  unsigned __int32 v20; // edx
  unsigned __int32 v21; // eax
  struct RenderStateBlock_t *v22; // eax
  struct RenderStateBlock_t *v23; // eax
  struct RenderStateBlock_t *v24; // eax
  struct RenderStateBlock_t *v25; // eax
  int nNumStates; // ecx

  Direct3D_eRenderMode = RenderMode_New("Direct3D");
  v0 = 130 * Direct3D_eRenderMode;
  v1 = Display_eCloseMethod;
  RenderMode_atRenderMode[v0 / 0x82].apfRenderModeMethod[Display_eOpenMethod] = (void (__cdecl *)(void *))Direct3D_Open;
  v2 = v0 + v1;
  v3 = Display_eSetModeMethod;
  RenderMode_atRenderMode[0].apfRenderModeMethod[v2] = Direct3D_Close;
  v4 = v0 + v3;
  v5 = Display_eUnsetModeMethod;
  RenderMode_atRenderMode[0].apfRenderModeMethod[v4] = (void (__cdecl *)(void *))Direct3D_SetMode;
  v6 = v0 + v5;
  v7 = Display_eWaitVBMethod;
  RenderMode_atRenderMode[0].apfRenderModeMethod[v6] = (void (__cdecl *)(void *))Direct3D_UnsetMode;
  v8 = v0 + v7;
  v9 = Display_eSwapBuffersMethod;
  RenderMode_atRenderMode[0].apfRenderModeMethod[v8] = (void (__cdecl *)(void *))Direct3D_WaitVB;
  v10 = v0 + v9;
  v11 = Display_eClearMethod;
  RenderMode_atRenderMode[0].apfRenderModeMethod[v10] = Direct3D_SwapBuffers;
  v12 = v0 + v11;
  v13 = Display_eEnumDevicesMethod;
  RenderMode_atRenderMode[0].apfRenderModeMethod[v12] = Direct3D_Clear;
  v14 = v0 + v13;
  v15 = Display_eBlitPrim;
  RenderMode_atRenderMode[0].apfRenderModeMethod[v14] = (void (__cdecl *)(void *))Direct3D_EnumDevices;
  v16 = v0 + v15;
  v17 = Display_eClipWindowPrim;
  RenderMode_atRenderMode[0].apfRenderModeMethod[v16] = (void (__cdecl *)(void *))Direct3D_Blit;
  v18 = v0 + v17;
  v19 = Display_eSnapshotPrim;
  RenderMode_atRenderMode[0].apfRenderModeMethod[v18] = (void (__cdecl *)(void *))Direct3D_SetClippingWindow;
  v20 = v0 + v19;
  v21 = Display_eGetGFXCapsMethod + v0;
  RenderMode_atRenderMode[0].apfRenderModeMethod[v20] = (void (__cdecl *)(void *))Direct3D_Snapshot;
  RenderMode_atRenderMode[0].apfRenderModeMethod[v21] = (void (__cdecl *)(void *))Direct3D_GetGFXCaps;
  Direct3D_bZBufferMode = 1;
  Direct3D_isInitialized = 1;
  memset(Direct3D_atCallback, 0, sizeof(Direct3D_atCallback));
  Direct3D_vScale = 0.0010000000474974513;
  Direct3D_vInverseScale = 999.9999389648438;
  Direct3D_vWorldOverlayMinZ = 204.8000030517578;
  Direct3D_vWorldOverlayMaxZ = 6144.0;
  Direct3D_vWorldMinZ = 409.6000061035156;
  Direct3D_vWorldMaxZ = 409600000.0;
  Direct3D_vWorldBackgroundMinZ = 409600000.0;
  Direct3D_vWorldBackgroundMaxZ = 409600000.0;
  Direct3D_vD3DOverlayMinZ = 0.20480000972747803;
  Direct3D_vD3DOverlayMaxZ = 6.144000053405762;
  Direct3D_vD3DMinZ = 0.40960001945495605;
  Direct3D_vD3DMaxZ = 409600.03125;
  Direct3D_vD3DBackgroundMinZ = 409600.03125;
  Direct3D_vD3DBackgroundMaxZ = 409600.03125;
  Direct3D_vOverlayMinZ = 0.0;
  dword_84B829C = 1028443341;
  Direct3D_vMinZ = 0.06000000238418579;
  Direct3D_vMaxZ = 1.0;
  Direct3D_vBackgroundMinZ = 1.0;
  Direct3D_vBackgroundMaxZ = 1.0;
  v22 = (struct RenderStateBlock_t *)Mem_AllocFn(84, 4);
  v22->eCurrentState = -1;
  v22->nNumMaxStates = 16;
  v22->nNumStates = 0;
  v22->nSafety0 = -1412584499;
  v22->nSafety1 = -591733574;
  Direct3D_ptTextureStateBlock = v22;
  v23 = (struct RenderStateBlock_t *)Mem_AllocFn(84, 4);
  v23->eCurrentState = -1;
  v23->nNumMaxStates = 16;
  v23->nNumStates = 0;
  v23->nSafety0 = -1412584499;
  v23->nSafety1 = -591733574;
  Direct3D_ptBlendStateBlock = v23;
  v24 = (struct RenderStateBlock_t *)Mem_AllocFn(84, 4);
  v24->eCurrentState = -1;
  v24->nNumMaxStates = 16;
  v24->nNumStates = 0;
  v24->nSafety0 = -1412584499;
  v24->nSafety1 = -591733574;
  Direct3D_ptGenericStateBlock = v24;
  v25 = (struct RenderStateBlock_t *)Mem_AllocFn(84, 4);
  v25->eCurrentState = -1;
  v25->nNumMaxStates = 16;
  v25->nNumStates = 0;
  v25->nSafety0 = -1412584499;
  v25->nSafety1 = -591733574;
  v25->nNumStates = 1;
  v25->atRenderState[0].pfCallback = Direct3D_SetClippingStateOn;
  Direct3D_eClippingStateOn = 0;
  nNumStates = v25->nNumStates;
  v25->nNumStates = nNumStates + 1;
  Direct3D_ptClippingStateBlock = v25;
  v25->atRenderState[nNumStates].pfCallback = Direct3D_SetClippingStateOff;
  Direct3D_eClippingStateOff = nNumStates;
  Main_RegisterWinProcCallback(Direct3D_WinProcCB);
  Direct3D_RegisterCallback(Direct3D_RestoreCallback, &Direct3D_ptRestoreCallback);
  Direct3D_RegisterCallback(Direct3D_DestroyCallback, &Direct3D_ptDestroyCallback);
}

// source: b/2/pc/pc_direct3d.c:2019  [anchor-hash]
void __cdecl Direct3D_Delete()
{
  struct DisplayCallbackChain_s *v0; // eax
  struct DisplayCallbackChain_s *v1; // ecx
  struct WinProcCBNode_s *ptHead; // eax
  struct WinProcCBNode_s *ptNext; // ecx
  struct RenderStateBlock_t *v4; // eax
  int v5; // ecx
  int v6; // esi
  int v7; // esi
  int v8; // esi
  int v9; // esi

  v0 = Direct3D_ptRestoreCallback;
  v1 = nullptr;
  if ( Direct3D_ptRestoreCallback )
  {
    while ( v0->pfCallback != Direct3D_RestoreCallback )
    {
      v1 = v0;
      v0 = v0->ptNext;
      if ( !v0 )
        goto LABEL_8;
    }
    if ( v1 )
      v1->ptNext = v0->ptNext;
    else
      Direct3D_ptRestoreCallback = v0->ptNext;
  }
LABEL_8:
  ptHead = Main_tWinProcCBList.ptHead;
  ptNext = Main_tWinProcCBList.ptHead->ptNext;
  if ( Main_tWinProcCBList.ptHead->ptNext )
  {
    while ( ptHead->pfWinProcCB != Direct3D_WinProcCB )
    {
      ptHead = ptNext;
      ptNext = ptNext->ptNext;
      if ( !ptNext )
        goto LABEL_13;
    }
    Node_Remove(ptHead)[2] = nullptr;
  }
LABEL_13:
  v4 = Direct3D_ptClippingStateBlock;
  v5 = Direct3D_eClippingStateOff;
  Direct3D_ptClippingStateBlock->atRenderState[Direct3D_eClippingStateOn].pfCallback = nullptr;
  v4->atRenderState[v5].pfCallback = nullptr;
  if ( Direct3D_ptTextureStateBlock )
  {
    v6 = *(_DWORD *)((unsigned int)Direct3D_ptTextureStateBlock[-1].atRenderState & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v6);
    memset(*(void **)(v6 + 8), 0xCDu, *(_DWORD *)(v6 + 16));
    free((void *)v6);
  }
  if ( Direct3D_ptBlendStateBlock )
  {
    v7 = *(_DWORD *)((unsigned int)Direct3D_ptBlendStateBlock[-1].atRenderState & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v7);
    memset(*(void **)(v7 + 8), 0xCDu, *(_DWORD *)(v7 + 16));
    free((void *)v7);
  }
  if ( Direct3D_ptGenericStateBlock )
  {
    v8 = *(_DWORD *)((unsigned int)Direct3D_ptGenericStateBlock[-1].atRenderState & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v8);
    memset(*(void **)(v8 + 8), 0xCDu, *(_DWORD *)(v8 + 16));
    free((void *)v8);
  }
  if ( Direct3D_ptClippingStateBlock )
  {
    v9 = *(_DWORD *)((unsigned int)Direct3D_ptClippingStateBlock[-1].atRenderState & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v9);
    memset(*(void **)(v9 + 8), 0xCDu, *(_DWORD *)(v9 + 16));
    free((void *)v9);
  }
  RenderMode_atRenderMode[Direct3D_eRenderMode].isAllocated = 0;
}

// source: b/2/pc/pc_direct3d.c:2047  [size]
enum RenderMode_enum __cdecl Direct3D_GetRenderMode()
{
  return Direct3D_eRenderMode;
}

// source: b/2/pc/pc_direct3d.c:2061  [anchor-mhash]
struct _D3DMATRIX *__cdecl Direct3D_D3DMATRIXFromReal32x9(
        struct _D3DMATRIX *ptDest,
        struct real32x9_t *ptSource,
        struct real32x3_t *ptPos)
{
  ptDest->_11 = ptSource->tX.vX;
  ptDest->_12 = ptSource->tY.vX;
  *(_QWORD *)&ptDest->m[0][2] = LODWORD(ptSource->tZ.vX);
  ptDest->_21 = ptSource->tX.vY;
  ptDest->_22 = ptSource->tY.vY;
  *(_QWORD *)&ptDest->m[1][2] = LODWORD(ptSource->tZ.vY);
  ptDest->_31 = ptSource->tX.vZ;
  ptDest->_32 = ptSource->tY.vZ;
  *(_QWORD *)&ptDest->m[2][2] = LODWORD(ptSource->tZ.vZ);
  if ( ptPos )
  {
    *(struct real32x3_t *)&ptDest->m[3][0] = *ptPos;
  }
  else
  {
    *(_QWORD *)&ptDest->m[3][0] = 0;
    ptDest->_43 = 0.0;
  }
  ptDest->_44 = 1.0;
  return ptDest;
}

// source: b/2/pc/pc_direct3d.c:2100  [size]
void __cdecl Direct3D_RegisterSetModeCallback(void (__cdecl *pfCB_)())
{
  Direct3D_RegisterCallback(pfCB_, &Direct3D_ptSetModeCallback);
}

// source: b/2/pc/pc_direct3d.c:2113  [size]
void __cdecl Direct3D_RegisterUnsetModeCallback(void (__cdecl *pfCB_)())
{
  Direct3D_RegisterCallback(pfCB_, &Direct3D_ptUnsetModeCallback);
}

// source: b/2/pc/pc_direct3d.c:2126  [size]
void __cdecl Direct3D_RegisterRestoreCallback(void (__cdecl *pfCB_)())
{
  Direct3D_RegisterCallback(pfCB_, &Direct3D_ptRestoreCallback);
}

// source: b/2/pc/pc_direct3d.c:2139  [size]
void __cdecl Direct3D_RegisterDestroyCallback(void (__cdecl *pfCB_)())
{
  Direct3D_RegisterCallback(pfCB_, &Direct3D_ptDestroyCallback);
}

// source: b/2/pc/pc_direct3d.c:2152  [size]
void __cdecl Direct3D_RemoveSetModeCallback(void (__cdecl *pfCB_)())
{
  struct DisplayCallbackChain_s *v1; // eax
  struct DisplayCallbackChain_s *v2; // ecx

  v1 = Direct3D_ptSetModeCallback;
  v2 = nullptr;
  if ( Direct3D_ptSetModeCallback )
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
      Direct3D_ptSetModeCallback = v1->ptNext;
  }
}

// source: b/2/pc/pc_direct3d.c:2165  [size]
void __cdecl Direct3D_RemoveUnsetModeCallback(void (__cdecl *pfCB_)())
{
  struct DisplayCallbackChain_s *v1; // eax
  struct DisplayCallbackChain_s *v2; // ecx

  v1 = Direct3D_ptUnsetModeCallback;
  v2 = nullptr;
  if ( Direct3D_ptUnsetModeCallback )
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
      Direct3D_ptUnsetModeCallback = v1->ptNext;
  }
}

// source: b/2/pc/pc_direct3d.c:2178  [size]
void __cdecl Direct3D_RemoveRestoreCallback(void (__cdecl *pfCB_)())
{
  struct DisplayCallbackChain_s *v1; // eax
  struct DisplayCallbackChain_s *v2; // ecx

  v1 = Direct3D_ptRestoreCallback;
  v2 = nullptr;
  if ( Direct3D_ptRestoreCallback )
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
      Direct3D_ptRestoreCallback = v1->ptNext;
  }
}

// source: b/2/pc/pc_direct3d.c:2191  [size]
void __cdecl Direct3D_RemoveDestroyCallback(void (__cdecl *pfCB_)())
{
  struct DisplayCallbackChain_s *v1; // eax
  struct DisplayCallbackChain_s *v2; // ecx

  v1 = Direct3D_ptDestroyCallback;
  v2 = nullptr;
  if ( Direct3D_ptDestroyCallback )
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
      Direct3D_ptDestroyCallback = v1->ptNext;
  }
}

// source: b/2/pc/pc_direct3d.c:2207  [anchor-mhash]
void __cdecl Direct3D_SetRenderingDefaults()
{
  #pragma pack(push, 1)
  union
  {
    struct { float vLodBias; };
    struct { char igi2_o1[4]; float vFogStart; };
    struct { char igi2_o2[8]; float vFogEnd; };
    struct { char igi2_o3[12]; float vFogDensity; };
    char igi2_extent[16];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  signed int i; // esi

  igi2_frame.vLodBias = 0.0;
  igi2_frame.vFogStart = 0.0;
  igi2_frame.vFogEnd = 1.0;
  igi2_frame.vFogDensity = 1.0;
  for ( i = 0; i < 8; ++i )
  {
    Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, i, D3DTSS_COLOROP, i != 0 ? 1 : 4);
    Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, i, D3DTSS_COLORARG1, 2u);
    Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, i, D3DTSS_COLORARG2, 1u);
    Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, i, D3DTSS_ALPHAOP, (i == 0) + 1);
    Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, i, D3DTSS_ALPHAARG1, 2u);
    Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, i, D3DTSS_ALPHAARG2, 1u);
    Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, i, D3DTSS_BUMPENVMAT01, 0);
    Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, i, D3DTSS_BUMPENVMAT01, 0);
    Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, i, D3DTSS_BUMPENVMAT11, 0);
    Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, i, D3DTSS_BUMPENVMAT11, 0);
    Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, i, D3DTSS_TEXCOORDINDEX, i);
    Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, i, D3DTSS_ADDRESSU, 1u);
    Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, i, D3DTSS_ADDRESSV, 1u);
    Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, i, D3DTSS_BORDERCOLOR, 0);
    Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, i, D3DTSS_MAGFILTER, 1u);
    Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, i, D3DTSS_MINFILTER, 1u);
    Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, i, D3DTSS_MIPFILTER, 0);
    Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, i, D3DTSS_MIPMAPLODBIAS, (unsigned int)&igi2_frame.vLodBias);
    Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, i, D3DTSS_MAXMIPLEVEL, 0);
    Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, i, D3DTSS_MAXANISOTROPY, 1u);
    Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, i, D3DTSS_BUMPENVLSCALE, 0);
    Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, i, D3DTSS_BUMPENVLOFFSET, 0);
    Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, i, D3DTSS_TEXTURETRANSFORMFLAGS, 0);
  }
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_MULTISAMPLEANTIALIAS, 0);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ZENABLE, 0);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_FILLMODE, 3u);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_SHADEMODE, 2u);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_LINEPATTERN, 0);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ZWRITEENABLE, 1u);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ALPHATESTENABLE, 0);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_LASTPIXEL, 1u);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_SRCBLEND, 2u);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_DESTBLEND, 1u);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_CULLMODE, 3u);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ZFUNC, 4u);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ALPHAREF, 0);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ALPHAFUNC, 8u);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_DITHERENABLE, 0);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ALPHABLENDENABLE, 0);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_FOGENABLE, 0);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_SPECULARENABLE, 0);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_FOGCOLOR, 0);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_FOGTABLEMODE, 0);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_FOGSTART, (unsigned int)&igi2_frame.vFogStart);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_FOGEND, (unsigned int)&igi2_frame.vFogEnd);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_FOGDENSITY, (unsigned int)&igi2_frame.vFogDensity);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_EDGEANTIALIAS, 0);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ZBIAS, 0);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_RANGEFOGENABLE, 0);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_STENCILENABLE, 0);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_STENCILFAIL, 1u);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_STENCILZFAIL, 1u);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_STENCILPASS, 1u);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_STENCILFUNC, 8u);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_STENCILREF, 0);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_STENCILMASK, -1u);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_STENCILWRITEMASK, -1u);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_TEXTUREFACTOR, 0);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_WRAP0, 0);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_WRAP1, 0);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_WRAP2, 0);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_WRAP3, 0);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_WRAP4, 0);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_WRAP5, 0);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_WRAP6, 0);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_WRAP7, 0);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_CLIPPING, 1u);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_LIGHTING, 1u);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_AMBIENT, 0);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_FOGVERTEXMODE, 0);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_COLORVERTEX, 1u);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_LOCALVIEWER, 1u);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_NORMALIZENORMALS, 0);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_DIFFUSEMATERIALSOURCE, 1u);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_SPECULARMATERIALSOURCE, 2u);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_AMBIENTMATERIALSOURCE, 2u);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_EMISSIVEMATERIALSOURCE, 0);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_VERTEXBLEND, 0);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_CLIPPLANEENABLE, 0);
}

// source: b/2/pc/pc_direct3d.c:2314  [size]
void __cdecl Direct3D_SetBlitCallback(void (__cdecl *pfCallback)(struct DisplayBlitContext_s *))
{
  Direct3D_pfBlitCallback = pfCallback;
}

// source: b/2/pc/pc_direct3d.c:2329  [anchor-mhash]
void __cdecl Direct3D_LockDynamicVertexBuffer(
        struct DynamicVertexBuffer_t *ptVB,
        void **ppxLocked,
        int *piStartVertex,
        int nVerticesToLock)
{
  if ( nVerticesToLock + ptVB->nNumVertices > ptVB->nMaxVertices )
    ptVB->nNumVertices = 0;
  if ( ptVB->ptVertexBuffer->lpVtbl->Lock(
         ptVB->ptVertexBuffer,
         ptVB->nNumVertices * ptVB->nStride,
         nVerticesToLock * ptVB->nStride,
         (unsigned __int8 **)ppxLocked,
         ptVB->nNumVertices != 0 ? 4096 : 0x2000) )
  {
    *ppxLocked = nullptr;
    *piStartVertex = 0;
  }
  else
  {
    *piStartVertex = ptVB->nNumVertices;
    ptVB->nNumVertices += nVerticesToLock;
  }
}

// source: b/2/pc/pc_direct3d.c:2373  [anchor-mhash]
unsigned int __cdecl Direct3D_SetStreamSource(
        unsigned int iStreamNumber,
        struct IDirect3DVertexBuffer8 *ptStreamData,
        unsigned int nStride)
{
  struct IDirect3DDevice8 *v3; // esi

  v3 = Direct3D_ptDevice;
  Direct3D_tState.aptStreamData[iStreamNumber] = ptStreamData;
  Direct3D_tState.anStride[iStreamNumber] = nStride;
  return v3->lpVtbl->SetStreamSource(v3, iStreamNumber, ptStreamData, nStride);
}

// source: b/2/pc/pc_direct3d.c:2398  [anchor-mhash]
unsigned int __cdecl Direct3D_SetIndices(
        struct IDirect3DIndexBuffer8 *ptIndexData,
        unsigned int nBaseVertexIndex)
{
  Direct3D_tState.ptIndexData = ptIndexData;
  Direct3D_tState.nBaseVertexIndex = nBaseVertexIndex;
  return Direct3D_ptDevice->lpVtbl->SetIndices(Direct3D_ptDevice, ptIndexData, nBaseVertexIndex);
}

// source: b/2/pc/pc_direct3d.c:2419  [anchor-hash]
unsigned int __cdecl Direct3D_SetVertexShader(unsigned int nHandle)
{
  Direct3D_tState.nHandle = nHandle;
  return Direct3D_ptDevice->lpVtbl->SetVertexShader(Direct3D_ptDevice, nHandle);
}

// source: b/2/pc/pc_direct3d.c:2436  [anchor-mhash]
struct IDirect3DBaseTexture8 *__cdecl Direct3D_SetTexture(
        unsigned int iStage,
        struct IDirect3DBaseTexture8 *ptTexture)
{
  struct IDirect3DDevice8 *v2; // edx

  if ( ptTexture != Direct3D_tState.aptTexture[iStage] )
  {
    v2 = Direct3D_ptDevice;
    Direct3D_tState.aptTexture[iStage] = ptTexture;
    return (struct IDirect3DBaseTexture8 *)v2->lpVtbl->SetTexture(v2, iStage, ptTexture);
  }
  return ptTexture;
}

// source: b/2/pc/pc_direct3d.c:2457  [anchor-mhash]
void __cdecl Direct3D_DrawIndexedPrimitive(
        enum _D3DPRIMITIVETYPE Type,
        unsigned int MinIndex,
        unsigned int NumVertices,
        unsigned int StartIndex,
        unsigned int PrimitiveCount)
{
  Direct3D_ptDevice->lpVtbl->DrawIndexedPrimitive(
    Direct3D_ptDevice,
    Type,
    MinIndex,
    NumVertices,
    StartIndex,
    PrimitiveCount);
}

// source: b/2/pc/pc_direct3d.c:2477  [anchor-mhash]
void __cdecl Direct3D_DrawIndexedPrimitiveUP(
        enum _D3DPRIMITIVETYPE PrimitiveType,
        unsigned int MinIndex,
        unsigned int NumVertices,
        unsigned int PrimitiveCount,
        void *pIndexData,
        enum _D3DFORMAT IndexDataFormat,
        void *pVertexStreamZeroData,
        unsigned int VertexStreamZeroStride)
{
  Direct3D_tState.aptStreamData[0] = nullptr;
  Direct3D_tState.anStride[0] = 0;
  Direct3D_tState.ptIndexData = nullptr;
  Direct3D_tState.nBaseVertexIndex = 0;
  Direct3D_ptDevice->lpVtbl->DrawIndexedPrimitiveUP(
    Direct3D_ptDevice,
    PrimitiveType,
    MinIndex,
    NumVertices,
    PrimitiveCount,
    pIndexData,
    IndexDataFormat,
    pVertexStreamZeroData,
    VertexStreamZeroStride);
}

// source: b/2/pc/pc_direct3d.c:2496  [anchor-mhash]
void __cdecl Direct3D_DrawPrimitive(
        enum _D3DPRIMITIVETYPE PrimitiveType,
        unsigned int StartVertex,
        unsigned int PrimitiveCount)
{
  Direct3D_ptDevice->lpVtbl->DrawPrimitive(Direct3D_ptDevice, PrimitiveType, StartVertex, PrimitiveCount);
}

// source: b/2/pc/pc_direct3d.c:2512  [anchor-mhash]
void __cdecl Direct3D_DrawPrimitiveUP(
        enum _D3DPRIMITIVETYPE PrimitiveType,
        unsigned int PrimitiveCount,
        void *pVertexStreamZeroData,
        unsigned int VertexStreamZeroStride)
{
  Direct3D_tState.aptStreamData[0] = nullptr;
  Direct3D_tState.anStride[0] = 0;
  Direct3D_ptDevice->lpVtbl->DrawPrimitiveUP(
    Direct3D_ptDevice,
    PrimitiveType,
    PrimitiveCount,
    pVertexStreamZeroData,
    VertexStreamZeroStride);
}

// source: b/2/pc/pc_direct3d.c:2527  [size]
struct Direct3D_AntialiasingCaps_t *__cdecl Direct3D_GetAntialiasingCaps()
{
  return &Direct3D_tAntialiasingCaps;
}

// source: b/2/pc/pc_direct3d.c:2540  [anchor-hash]
int __cdecl Direct3D_SetAntialiasingLevel(int nAntialiasingLevel)
{
  int result; // eax

  result = 2 * (nAntialiasingLevel / 2);
  Direct3D_nAntialiasingLevel = result;
  return result;
}

// source: b/2/pc/pc_direct3d.c:2553  [size]
int __cdecl Direct3D_VertexShadersForceSoftwareProcessing(int isSoftware)
{
  Direct3D_isSoftwareVS = isSoftware;
  return isSoftware;
}

// source: b/2/pc/pc_direct3d.c:2566  [size~]
enum bool __cdecl Direct3D_IsSoftwareVertexShadersByDefault()
{
  #pragma pack(push, 1)
  union
  {
    struct { char Str[128]; };
    struct { char igi2_o1[128]; struct _D3DCAPS8 v9; };
    struct { char igi2_o2[340]; int v10[258]; };
    struct { char igi2_o3[1372]; int v11; };
    struct { char igi2_o4[1376]; unsigned int v12; };
    struct { char igi2_o5[1388]; struct _GUID v13; };
    struct { char igi2_o6[1408]; char Buffer[1024]; };
    char igi2_extent[2432];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v0; // ebp
  struct IDirect3D8 *v1; // esi
  unsigned int i; // edi
  int v3; // ebx
  char *ErrorString; // eax
  int v5; // edi
  char *v6; // eax

  v0 = 0;
  if ( AppContext_tAppContext.isServer == false )
  {
    v1 = Direct3D_ptObject;
    if ( !Direct3D_ptObject )
    {
      v1 = Direct3D_pfDirect3DCreate8(0xDCu);
      v0 = 1;
    }
    for ( i = 0; i < v1->lpVtbl->GetAdapterCount(v1); ++i )
    {
      v1->lpVtbl->GetAdapterIdentifier(v1, i, 2u, (struct _D3DADAPTER_IDENTIFIER8 *)igi2_frame.v10);
      Direct3D_GUIDToString(igi2_frame.Str, igi2_frame.v13);
      if ( strstr(igi2_frame.Str, Display_tActiveMode.zDeviceIdentifier) )
        break;
    }
    if ( i == v1->lpVtbl->GetAdapterCount(v1) )
      i = 0;
    v3 = v1->lpVtbl->GetAdapterIdentifier(v1, i, 2u, (struct _D3DADAPTER_IDENTIFIER8 *)igi2_frame.v10);
    if ( v3 )
    {
      sprintf(igi2_frame.Buffer, "Couldn't get adapter identifier");
      ErrorString = Direct3D_GetErrorString(v3);
      LDebug_Error(
        "%s\n\nDirectX error message: %s\nFile: %s Line: %d",
        igi2_frame.Buffer,
        ErrorString,
        "\\project\\igi2\\B\\2\\PC\\pc_direct3d.c",
        2631);
      goto LABEL_11;
    }
    v5 = v1->lpVtbl->GetDeviceCaps(v1, i, D3DDEVTYPE_HAL, &igi2_frame.v9);
    if ( v5 )
    {
      sprintf(igi2_frame.Buffer, "Couldn't get device caps");
      v6 = Direct3D_GetErrorString(v5);
      LDebug_Error(
        "%s\n\nDirectX error message: %s\nFile: %s Line: %d",
        igi2_frame.Buffer,
        v6,
        "\\project\\igi2\\B\\2\\PC\\pc_direct3d.c",
        2634);
LABEL_11:
      abort();
    }
    if ( v0 )
      v1->lpVtbl->Release(v1);
    Real_nTempCW = igi2_fpu_or(0xC00u);
    if ( igi2_frame.v11 == 4098 )
    {
      if ( igi2_frame.v12 >= 0x4144 && igi2_frame.v12 <= 0x4147 || igi2_frame.v12 >= 0x4E44 && igi2_frame.v12 <= 0x4E47 )
        return false;
    }
    else if ( igi2_frame.v11 != 4318 || igi2_frame.v12 < 0x170 || igi2_frame.v12 > 0x179 )
    {
      return false;
    }
  }
  return true;
}
