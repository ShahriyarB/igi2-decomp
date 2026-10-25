/* b/4/pc/pc_direct3dtexture.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: b/4/pc/pc_direct3dtexture.c:72  [size~]
enum bool __cdecl Direct3DTexture_D3DXCheckFileFormat(
        struct AllocTextureContext_s *ptAllocTextureContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { int v5; };
    struct { char igi2_o1[4]; int v6; };
    struct { char igi2_o2[16]; int v7; };
    char igi2_extent[28];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v1; // ecx
  int v2; // eax
  int v3; // ecx
  enum bool result; // eax

  if ( D3DXGetImageInfoFromFileInMemory(
         (int)ptAllocTextureContext->pxFileInMemory,
         ptAllocTextureContext->nSizeOfFileInMemory,
         (int)&igi2_frame.v5) )
  {
    return false;
  }
  v1 = igi2_frame.v6;
  v2 = igi2_frame.v5;
  ptAllocTextureContext->nHeight = igi2_frame.v6;
  ptAllocTextureContext->nSourceHeight = v1;
  v3 = igi2_frame.v7 - 20;
  ptAllocTextureContext->nWidth = v2;
  ptAllocTextureContext->nSourceWidth = v2;
  switch ( v3 )
  {
    case 0:
      ptAllocTextureContext->nPitch = 4 * v2;
      ptAllocTextureContext->nType = 3;
      result = true;
      break;
    case 1:
      ptAllocTextureContext->nType = 3;
      ptAllocTextureContext->nPitch = 4 * v2;
      result = true;
      break;
    case 2:
      ptAllocTextureContext->nType = 3;
      ptAllocTextureContext->nPitch = 4 * v2;
      result = true;
      break;
    case 3:
      ptAllocTextureContext->nPitch = 2 * v2;
      ptAllocTextureContext->nType = 5;
      result = true;
      break;
    case 4:
      ptAllocTextureContext->nType = 2;
      ptAllocTextureContext->nPitch = 2 * v2;
      result = true;
      break;
    case 5:
      ptAllocTextureContext->nType = 2;
      ptAllocTextureContext->nPitch = 2 * v2;
      result = true;
      break;
    case 6:
      ptAllocTextureContext->nPitch = 2 * v2;
      ptAllocTextureContext->nType = 4;
      result = true;
      break;
    default:
      return false;
  }
  return result;
}

// source: b/4/pc/pc_direct3dtexture.c:184  [size~]
void __cdecl Direct3DTexture_Alloc(struct AllocTextureContext_s *ptAllocTextureContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { int v13; };
    struct { char igi2_o1[4]; int v14; };
    struct { char igi2_o2[8]; int v15; };
    char igi2_extent[12];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct AllocTextureContext_s *v1; // esi
  void *pxFileInMemory; // eax
  int v3; // edi
  unsigned int bFlags; // edx
  int nWidth; // eax
  int nHeight; // ecx
  int nType; // ebx
  int v8; // eax
  int v9; // ecx
  struct TexInfo_s *ptTexInfo; // ebp
  enum RenderMode_enum v11; // edx
  int Depth; // eax

  v1 = ptAllocTextureContext;
  pxFileInMemory = ptAllocTextureContext->pxFileInMemory;
  v3 = 1;
  igi2_frame.v13 = 1;
  if ( pxFileInMemory )
  {
    if ( Direct3DTexture_D3DXCheckFileFormat(ptAllocTextureContext) == false )
    {
      memset(v1->ptTexInfo, 0, sizeof(struct TexInfo_s));
      return;
    }
    v3 = igi2_frame.v13;
  }
  bFlags = v1->bFlags;
  nWidth = v1->nWidth;
  nHeight = v1->nHeight;
  nType = v1->nType;
  igi2_frame.v14 = nWidth;
  igi2_frame.v15 = nHeight;
  if ( (bFlags & 0x8000000) != 0 || (nType & 0x40) != 0 )
  {
    v8 = nWidth >> 1;
    v9 = nHeight >> 1;
    if ( v8 )
    {
      do
      {
        if ( !v9 )
          break;
        v8 >>= 1;
        ++v3;
        v9 >>= 1;
      }
      while ( v8 );
      igi2_frame.v13 = v3;
    }
  }
  if ( (bFlags & 1) != 0
    || (ptAllocTextureContext = (struct AllocTextureContext_s *)827611204,
        D3DXCheckTextureRequirements(
          (int)Direct3D_ptDevice,
          (int)&igi2_frame.v14,
          (int)&igi2_frame.v15,
          (int)&igi2_frame.v13,
          0,
          (int)&ptAllocTextureContext,
          1),
        ptAllocTextureContext != (struct AllocTextureContext_s *)827611204) )
  {
    switch ( nType & 0xFFFFFF3F )
    {
      case 2u:
        ptAllocTextureContext = (struct AllocTextureContext_s *)25;
        break;
      case 4u:
        ptAllocTextureContext = (struct AllocTextureContext_s *)26;
        break;
      case 5u:
        ptAllocTextureContext = (struct AllocTextureContext_s *)23;
        break;
      default:
        ptAllocTextureContext = (struct AllocTextureContext_s *)21;
        break;
    }
    D3DXCheckTextureRequirements(
      (int)Direct3D_ptDevice,
      (int)&igi2_frame.v14,
      (int)&igi2_frame.v15,
      (int)&igi2_frame.v13,
      0,
      (int)&ptAllocTextureContext,
      1);
  }
  ptTexInfo = v1->ptTexInfo;
  v11 = Direct3D_eRenderMode;
  memset(v1->ptTexInfo, 0, sizeof(struct TexInfo_s));
  ptTexInfo->eRenderMode = v11;
  ptTexInfo->ptDirect3DTexture = nullptr;
  ptTexInfo->ptDirect3DBaseTexture = nullptr;
  Depth = Direct3D_GetDepth((enum _D3DFORMAT)ptAllocTextureContext);
  LOWORD(Depth) = igi2_frame.v14 * (Depth / 8);
  ptTexInfo->tUVScale.vX = (double)v1->nWidth / (double)igi2_frame.v14;
  ptTexInfo->tUVScale.vY = (double)v1->nHeight / (double)igi2_frame.v15;
  ptTexInfo->nWidth = igi2_frame.v14;
  ptTexInfo->nHeight = igi2_frame.v15;
  ptTexInfo->nPitch = Depth;
  ptTexInfo->nType = nType;
  ptTexInfo->vTransparency = 0.0;
  ptTexInfo->bFlags = v1->bFlags;
  if ( v1->nType == 1 )
    QVector_AddElement(Direct3DTexture_ptPalettedTextureContainer, ptTexInfo);
}

// source: b/4/pc/pc_direct3dtexture.c:320  [size]
int __cdecl Direct3DTexture_GetFootPrint(struct IDirect3DTexture8 *ptTexture)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct _D3DSURFACE_DESC tSurfaceDesc; };
    struct { char igi2_o1[32]; char zString[1024]; };
    char igi2_extent[1056];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v1; // ebp
  unsigned int i; // edi
  int v3; // ebx
  char *ErrorString; // eax

  v1 = 0;
  for ( i = 0; i < ptTexture->lpVtbl->GetLevelCount(ptTexture); ++i )
  {
    v3 = ptTexture->lpVtbl->GetLevelDesc(ptTexture, i, &igi2_frame.tSurfaceDesc);
    if ( v3 )
    {
      sprintf(igi2_frame.zString, "Couldn't get surface description");
      ErrorString = Direct3D_GetErrorString(v3);
      LDebug_Error(
        "%s\n\nDirectX error message: %s\nFile: %s Line: %d",
        igi2_frame.zString,
        ErrorString,
        "\\project\\igi2\\B\\4\\PC\\pc_direct3dtexture.c",
        336);
      abort();
    }
    v1 += igi2_frame.tSurfaceDesc.Size;
  }
  return v1;
}

// source: b/4/pc/pc_direct3dtexture.c:353  [size]
void __cdecl Direct3DTexture_DeAlloc(struct TexInfo_s *ptTexInfo)
{
  #pragma pack(push, 1)
  union
  {
    struct { __int64 nTemp1; };
    struct { char igi2_o1[8]; __int64 nTemp0; };
    char igi2_extent[16];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QVector_s *v1; // edx
  unsigned int v2; // eax
  void **papxElement; // esi
  unsigned int v4; // edi
  enum bool isStrictOrder; // esi
  void **v6; // edx
  struct IDirect3DTexture8 *ptDirect3DTexture; // esi
  enum TextureCategory_e v8; // edi
  int FootPrint; // eax
  int v10; // esi
  int v11; // eax

  if ( Direct3D_tState.aptTexture[0] )
  {
    Direct3D_tState.aptTexture[0] = nullptr;
    Direct3D_ptDevice->lpVtbl->SetTexture(Direct3D_ptDevice, 0, nullptr);
  }
  if ( Direct3D_tState.aptTexture[1] )
  {
    Direct3D_tState.aptTexture[1] = nullptr;
    Direct3D_ptDevice->lpVtbl->SetTexture(Direct3D_ptDevice, 1u, nullptr);
  }
  v1 = Direct3DTexture_ptPalettedTextureContainer;
  v2 = 0;
  if ( Direct3DTexture_ptPalettedTextureContainer->tPrivate.nElements )
  {
    papxElement = Direct3DTexture_ptPalettedTextureContainer->tPrivate.papxElement;
    while ( *papxElement != ptTexInfo )
    {
      ++v2;
      ++papxElement;
      if ( v2 >= Direct3DTexture_ptPalettedTextureContainer->tPrivate.nElements )
        goto LABEL_14;
    }
    v4 = Direct3DTexture_ptPalettedTextureContainer->tPrivate.nElements - 1;
    Direct3DTexture_ptPalettedTextureContainer->tPrivate.nElements = v4;
    if ( v2 < v4 )
    {
      isStrictOrder = v1->tPrivate.isStrictOrder;
      v6 = v1->tPrivate.papxElement;
      if ( isStrictOrder )
        memmove(&v6[v2], &v6[v2 + 1], 4 * (v4 - v2));
      else
        v6[v2] = v6[v4];
    }
  }
LABEL_14:
  ptDirect3DTexture = ptTexInfo->ptDirect3DTexture;
  if ( ptDirect3DTexture )
  {
    v8 = Texture_eCategory;
    FootPrint = Direct3DTexture_GetFootPrint(ptDirect3DTexture);
    v10 = Texture_anTextureNum[v8];
    v11 = -FootPrint;
    Texture_anTextureFootprint[v8] += v11;
    Texture_anTextureNum[v8] = v10 - 1;
    --Texture_anTextureNum[2];
    Texture_anTextureFootprint[2] += v11;
    QueryPerformanceCounter((LARGE_INTEGER *)&igi2_frame.nTemp0);
    ptTexInfo->ptDirect3DTexture->lpVtbl->Release(ptTexInfo->ptDirect3DTexture);
    QueryPerformanceCounter((LARGE_INTEGER *)&igi2_frame.nTemp1);
    Direct3DTexture_nReleaseTime += igi2_frame.nTemp1 - igi2_frame.nTemp0;
    ptTexInfo->ptDirect3DTexture = nullptr;
  }
}

// source: b/4/pc/pc_direct3dtexture.c:403  [size]
float __cdecl Direct3DTexture_GetTransparencyARGB8888(
        unsigned int *pnTempTexture,
        int nWidth,
        int nHeight)
{
  int v3; // eax
  int v4; // edx
  int i; // ecx

  v3 = nHeight * nWidth;
  v4 = 255 * v3;
  for ( i = 0; i < v3; ++i )
    v4 -= HIBYTE(pnTempTexture[i]);
  return (double)(unsigned int)v4 / (double)(255 * v3);
}

// source: b/4/pc/pc_direct3dtexture.c:436  [size]
struct IDirect3DTexture8 *__cdecl Direct3DTexture_ConvertARGB8888ToRawDirectDrawSurface(
        struct IDirect3DTexture8 *ptDestTexture,
        int iLevel,
        enum _D3DFORMAT eFormat,
        int nDestWidth,
        int nDestHeight,
        int *pnSource,
        int nSourceWidth,
        int nSourceHeight)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct IDirect3DSurface8 *ptDestSurface; };
    struct { char igi2_o1[4]; struct tagRECT tSourceRect; };
    struct { char igi2_o2[20]; struct _D3DSURFACE_DESC tDesc; };
    char igi2_extent[52];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct IDirect3DTexture8Vtbl *lpVtbl; // edx
  struct IDirect3DTexture8 *result; // eax

  lpVtbl = ptDestTexture->lpVtbl;
  igi2_frame.tSourceRect.bottom = nSourceHeight;
  igi2_frame.tSourceRect.left = 0;
  igi2_frame.tSourceRect.top = 0;
  igi2_frame.tSourceRect.right = nSourceWidth;
  igi2_frame.ptDestSurface = nullptr;
  result = (struct IDirect3DTexture8 *)lpVtbl->GetSurfaceLevel(ptDestTexture, iLevel, &igi2_frame.ptDestSurface);
  if ( (int)result >= 0 )
  {
    igi2_frame.ptDestSurface->lpVtbl->GetDesc(igi2_frame.ptDestSurface, &igi2_frame.tDesc);
    if ( D3DXLoadSurfaceFromMemory(
           (int)igi2_frame.ptDestSurface,
           0,
           0,
           (int)pnSource,
           21,
           4 * nSourceWidth,
           0,
           (int)&igi2_frame.tSourceRect,
           1,
           0) < 0 )
    {
      LDebug_Error("Error occurred in texture module");
      abort();
    }
    return (struct IDirect3DTexture8 *)igi2_frame.ptDestSurface->lpVtbl->Release(igi2_frame.ptDestSurface);
  }
  return result;
}

// source: b/4/pc/pc_direct3dtexture.c:501  [size~]
void __cdecl Direct3DTexture_DownloadFromFile(struct AllocTextureContext_s *ptDownloadTextureContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { enum _D3DFORMAT eFormat; };
    struct { char igi2_o1[4]; int v23; };
    struct { char igi2_o2[8]; int v24; };
    struct { char igi2_o3[12]; int v25; };
    struct { char igi2_o4[16]; unsigned int v26; };
    struct { char igi2_o5[20]; int nHeight; };
    struct { char igi2_o6[24]; char Buffer[1024]; };
    char igi2_extent[1048];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  bool v1; // zf
  struct IDirect3DTexture8 *ptDirect3DTexture; // esi
  enum TextureCategory_e v3; // edi
  int FootPrint; // eax
  int v5; // edx
  _DWORD *v6; // ecx
  int v7; // eax
  int v8; // edi
  int nType; // esi
  int nWidth; // ebx
  char bFlags; // al
  unsigned int v12; // esi
  struct TexInfo_s *ptTexInfo; // esi
  enum RenderMode_enum v14; // edx
  int Depth; // eax
  int v16; // esi
  char *ErrorString; // eax
  enum TextureCategory_e v18; // edi
  int v19; // eax
  int v20; // esi
  int v21; // edx

  v1 = (ptDownloadTextureContext->bFlags & 0x8000000) == 0;
  igi2_frame.v25 = 1;
  if ( !v1
    && ((ptDownloadTextureContext->nWidth & ~(ptDownloadTextureContext->nWidth - 1)) != ptDownloadTextureContext->nWidth
     || (ptDownloadTextureContext->nHeight & ~(ptDownloadTextureContext->nHeight - 1)) != ptDownloadTextureContext->nHeight) )
  {
    LDebug_Error("Trying to download mipmap texture that is not power of 2 in width or height");
    goto LABEL_5;
  }
  if ( Direct3D_tState.aptTexture[0] )
  {
    Direct3D_tState.aptTexture[0] = nullptr;
    Direct3D_ptDevice->lpVtbl->SetTexture(Direct3D_ptDevice, 0, nullptr);
  }
  if ( Direct3D_tState.aptTexture[1] )
  {
    Direct3D_tState.aptTexture[1] = nullptr;
    Direct3D_ptDevice->lpVtbl->SetTexture(Direct3D_ptDevice, 1u, nullptr);
  }
  ptDownloadTextureContext->ptTexInfo->vTransparency = 0.0;
  ptDirect3DTexture = ptDownloadTextureContext->ptTexInfo->ptDirect3DTexture;
  if ( ptDirect3DTexture )
  {
    v3 = Texture_eCategory;
    FootPrint = Direct3DTexture_GetFootPrint(ptDirect3DTexture);
    v5 = Texture_anTextureFootprint[v3];
    v6 = (_DWORD *)(4 * v3 + 128714392);
    v7 = -FootPrint;
    --Texture_anTextureNum[v3];
    v8 = Texture_anTextureNum[2];
    *v6 = v7 + v5;
    Texture_anTextureNum[2] = v8 - 1;
    Texture_anTextureFootprint[2] += v7;
    ptDownloadTextureContext->ptTexInfo->ptDirect3DTexture->lpVtbl->Release(ptDownloadTextureContext->ptTexInfo->ptDirect3DTexture);
    ptDownloadTextureContext->ptTexInfo->ptDirect3DTexture = nullptr;
  }
  nType = ptDownloadTextureContext->nType;
  nWidth = ptDownloadTextureContext->nWidth;
  igi2_frame.nHeight = ptDownloadTextureContext->nHeight;
  igi2_frame.v23 = igi2_frame.nHeight;
  bFlags = ptDownloadTextureContext->bFlags;
  v12 = nType & 0xFFFFFFBF;
  igi2_frame.v26 = v12;
  igi2_frame.v24 = nWidth;
  if ( (bFlags & 1) != 0
    || ptDownloadTextureContext->ptTexInfo->vTransparency != 0.0
    || (igi2_frame.eFormat = D3DFMT_DXT1,
        D3DXCheckTextureRequirements((int)Direct3D_ptDevice, (int)&igi2_frame.v24, (int)&igi2_frame.v23, (int)&igi2_frame.v25, 0, (int)&igi2_frame.eFormat, 1),
        igi2_frame.eFormat != D3DFMT_DXT1) )
  {
    switch ( v12 )
    {
      case 2u:
        igi2_frame.eFormat = D3DFMT_A1R5G5B5;
        break;
      case 4u:
        igi2_frame.eFormat = D3DFMT_A4R4G4B4;
        break;
      case 5u:
        igi2_frame.eFormat = D3DFMT_R5G6B5;
        break;
      default:
        igi2_frame.eFormat = D3DFMT_A8R8G8B8;
        break;
    }
    D3DXCheckTextureRequirements((int)Direct3D_ptDevice, (int)&igi2_frame.v24, (int)&igi2_frame.v23, (int)&igi2_frame.v25, 0, (int)&igi2_frame.eFormat, 1);
  }
  ptTexInfo = ptDownloadTextureContext->ptTexInfo;
  v14 = Direct3D_eRenderMode;
  memset(ptDownloadTextureContext->ptTexInfo, 0, sizeof(struct TexInfo_s));
  ptTexInfo->eRenderMode = v14;
  ptTexInfo->ptDirect3DTexture = nullptr;
  ptTexInfo->ptDirect3DBaseTexture = nullptr;
  Depth = Direct3D_GetDepth(igi2_frame.eFormat);
  ptTexInfo->nType = igi2_frame.v26;
  ptTexInfo->nPitch = nWidth * (Depth / 8);
  ptTexInfo->nWidth = nWidth;
  ptTexInfo->vTransparency = 0.0;
  ptTexInfo->tUVScale.vX = 1.0;
  ptTexInfo->tUVScale.vY = 1.0;
  ptTexInfo->nHeight = igi2_frame.nHeight;
  ptTexInfo->bFlags = ptDownloadTextureContext->bFlags;
  ptTexInfo->pxData = nullptr;
  ptDownloadTextureContext->ptTexInfo->eDirect3DFormat = igi2_frame.eFormat;
  v16 = D3DXCreateTextureFromFileInMemoryEx(
          (int)Direct3D_ptDevice,
          (int)ptDownloadTextureContext->pxFileInMemory,
          ptDownloadTextureContext->nSizeOfFileInMemory,
          igi2_frame.v24,
          igi2_frame.v23,
          (ptDownloadTextureContext->bFlags & 0x8000000) != 0 ? -1 : 1,
          0,
          igi2_frame.eFormat,
          1,
          -1,
          -1,
          0,
          0,
          0,
          (int)&ptDownloadTextureContext->ptTexInfo->ptDirect3DTexture);
  if ( v16 )
  {
    sprintf(igi2_frame.Buffer, "Couldn't create texture");
    ErrorString = Direct3D_GetErrorString(v16);
    LDebug_Error(
      "%s\n\nDirectX error message: %s\nFile: %s Line: %d",
      igi2_frame.Buffer,
      ErrorString,
      "\\project\\igi2\\B\\4\\PC\\pc_direct3dtexture.c",
      653);
LABEL_5:
    abort();
  }
  v18 = Texture_eCategory;
  ptDownloadTextureContext->ptTexInfo->ptDirect3DBaseTexture = (struct IDirect3DBaseTexture8 *)ptDownloadTextureContext->ptTexInfo->ptDirect3DTexture;
  v19 = Direct3DTexture_GetFootPrint(ptDownloadTextureContext->ptTexInfo->ptDirect3DTexture);
  v20 = Texture_anTextureFootprint[v18];
  ++Texture_anTextureNum[v18];
  v21 = Texture_anTextureNum[2];
  Texture_anTextureFootprint[v18] = v19 + v20;
  Texture_anTextureNum[2] = v21 + 1;
  Texture_anTextureFootprint[2] += v19;
}

// source: b/4/pc/pc_direct3dtexture.c:672  [size~]
void __cdecl Direct3DTexture_Download(struct AllocTextureContext_s *ptDownloadTextureContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { int iLevel; };
    struct { char igi2_o1[4]; int v29; };
    struct { char igi2_o2[8]; int nDestWidth; };
    struct { char igi2_o3[12]; enum _D3DFORMAT eFormat; };
    struct { char igi2_o4[16]; int nSourceHeight; };
    struct { char igi2_o5[20]; int v33; };
    struct { char igi2_o6[24]; int v34; };
    struct { char igi2_o7[28]; int nDestHeight; };
    struct { char igi2_o8[32]; unsigned int v36; };
    struct { char igi2_o9[36]; char Buffer[1024]; };
    char igi2_extent[1060];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  void *pxFileInMemory; // ecx
  unsigned int v2; // eax
  void *v3; // edi
  struct IDirect3DTexture8 *ptDirect3DTexture; // esi
  enum TextureCategory_e v5; // ebp
  int FootPrint; // eax
  int v7; // edx
  _DWORD *v8; // ecx
  int v9; // eax
  int v10; // ebp
  bool v11; // zf
  int nWidth; // ebp
  int nHeight; // edx
  int v14; // eax
  int v15; // ecx
  int v16; // esi
  struct TexInfo_s *ptTexInfo; // esi
  int v18; // edi
  int Depth; // eax
  __int16 v20; // dx
  int v21; // esi
  char *ErrorString; // eax
  int v23; // esi
  enum TextureCategory_e v24; // edi
  int v25; // eax
  int v26; // esi
  int v27; // edx

  pxFileInMemory = ptDownloadTextureContext->pxFileInMemory;
  igi2_frame.v34 = Direct3DTexture_nLOD;
  v2 = (ptDownloadTextureContext->bFlags >> 27) & 1;
  igi2_frame.v29 = 1;
  if ( pxFileInMemory )
  {
    Direct3DTexture_DownloadFromFile(ptDownloadTextureContext);
    return;
  }
  if ( v2
    && ((ptDownloadTextureContext->nWidth & ~(ptDownloadTextureContext->nWidth - 1)) != ptDownloadTextureContext->nWidth
     || (ptDownloadTextureContext->nHeight & ~(ptDownloadTextureContext->nHeight - 1)) != ptDownloadTextureContext->nHeight) )
  {
    LDebug_Error("Trying to download mipmap texture that is not power of 2 in width or height");
    goto LABEL_7;
  }
  if ( Direct3D_tState.aptTexture[0] )
  {
    Direct3D_tState.aptTexture[0] = nullptr;
    Direct3D_ptDevice->lpVtbl->SetTexture(Direct3D_ptDevice, 0, nullptr);
  }
  if ( Direct3D_tState.aptTexture[1] )
  {
    Direct3D_tState.aptTexture[1] = nullptr;
    Direct3D_ptDevice->lpVtbl->SetTexture(Direct3D_ptDevice, 1u, nullptr);
  }
  v3 = Mem_AllocFn(4 * ptDownloadTextureContext->nHeight * ptDownloadTextureContext->nWidth, 4);
  igi2_frame.v36 = ptDownloadTextureContext->nType & 0xFFFFFFBF;
  igi2_frame.nDestHeight = (int)v3;
  switch ( igi2_frame.v36 )
  {
    case 1u:
      TextureUtility_ConvertARGB88ToARGB8888(
        v3,
        ptDownloadTextureContext->nWidth,
        ptDownloadTextureContext->nHeight,
        nullptr,
        ptDownloadTextureContext->pxData,
        ptDownloadTextureContext->ptPalInfo->pxPalette,
        ptDownloadTextureContext->nWidth,
        ptDownloadTextureContext->nHeight,
        nullptr);
      goto LABEL_17;
    case 2u:
      TextureUtility_ConvertARGB1555ToARGB8888(
        v3,
        ptDownloadTextureContext->nWidth,
        ptDownloadTextureContext->nHeight,
        ptDownloadTextureContext->pxData,
        ptDownloadTextureContext->nWidth,
        ptDownloadTextureContext->nHeight,
        nullptr);
      goto LABEL_17;
    case 3u:
      TextureUtility_Fit32bitTexture(
        v3,
        ptDownloadTextureContext->nWidth,
        ptDownloadTextureContext->nHeight,
        ptDownloadTextureContext->pxData,
        ptDownloadTextureContext->nWidth,
        ptDownloadTextureContext->nHeight,
        nullptr);
      goto LABEL_17;
    case 5u:
      TextureUtility_ConvertRGB565ToARGB8888(
        v3,
        ptDownloadTextureContext->nWidth,
        ptDownloadTextureContext->nHeight,
        ptDownloadTextureContext->pxData,
        ptDownloadTextureContext->nWidth,
        ptDownloadTextureContext->nHeight,
        nullptr);
LABEL_17:
      ptDownloadTextureContext->ptTexInfo->vTransparency = Direct3DTexture_GetTransparencyARGB8888(
                                                             (unsigned int *)v3,
                                                             ptDownloadTextureContext->nWidth,
                                                             ptDownloadTextureContext->nHeight);
      ptDirect3DTexture = ptDownloadTextureContext->ptTexInfo->ptDirect3DTexture;
      if ( ptDirect3DTexture )
      {
        v5 = Texture_eCategory;
        FootPrint = Direct3DTexture_GetFootPrint(ptDirect3DTexture);
        v7 = Texture_anTextureFootprint[v5];
        v8 = (_DWORD *)(4 * v5 + 128714392);
        v9 = -FootPrint;
        --Texture_anTextureNum[v5];
        v10 = Texture_anTextureNum[2];
        *v8 = v9 + v7;
        Texture_anTextureNum[2] = v10 - 1;
        Texture_anTextureFootprint[2] += v9;
        ptDownloadTextureContext->ptTexInfo->ptDirect3DTexture->lpVtbl->Release(ptDownloadTextureContext->ptTexInfo->ptDirect3DTexture);
        ptDownloadTextureContext->ptTexInfo->ptDirect3DTexture = nullptr;
      }
      v11 = (ptDownloadTextureContext->bFlags & 0x8000000) == 0;
      nWidth = ptDownloadTextureContext->nWidth;
      nHeight = ptDownloadTextureContext->nHeight;
      igi2_frame.v33 = nWidth;
      igi2_frame.nSourceHeight = nHeight;
      if ( !v11 )
      {
        if ( igi2_frame.v34 )
        {
          do
          {
            --igi2_frame.v34;
            if ( nWidth >> 1 < 1 )
              break;
            igi2_frame.v33 = nHeight >> 1;
            if ( nHeight >> 1 < 1 )
              break;
            TextureUtility_ShrinkToHalf32HighQuality(v3, v3, nWidth, nHeight);
            igi2_frame.nSourceHeight = igi2_frame.v33;
            nHeight = igi2_frame.v33;
            nWidth >>= 1;
          }
          while ( igi2_frame.v34 );
          igi2_frame.v33 = nWidth;
        }
        if ( (ptDownloadTextureContext->bFlags & 0x8000000) != 0 )
        {
          v14 = nWidth >> 1;
          v15 = nHeight >> 1;
          if ( nWidth >> 1 )
          {
            v16 = igi2_frame.v29;
            do
            {
              if ( !v15 )
                break;
              v14 >>= 1;
              ++v16;
              v15 >>= 1;
            }
            while ( v14 );
            igi2_frame.v29 = v16;
          }
        }
      }
      v11 = (ptDownloadTextureContext->bFlags & 1) == 0;
      igi2_frame.eFormat = nWidth;
      igi2_frame.nDestWidth = nHeight;
      if ( !v11
        || ptDownloadTextureContext->ptTexInfo->vTransparency != 0.0
        || (igi2_frame.iLevel = 827611204,
            D3DXCheckTextureRequirements(
              (int)Direct3D_ptDevice,
              (int)&igi2_frame.eFormat,
              (int)&igi2_frame.nDestWidth,
              (int)&igi2_frame.v29,
              0,
              (int)&igi2_frame.iLevel,
              1),
            igi2_frame.iLevel != 827611204) )
      {
        switch ( igi2_frame.v36 )
        {
          case 2u:
            igi2_frame.iLevel = 25;
            break;
          case 4u:
            igi2_frame.iLevel = 26;
            break;
          case 5u:
            igi2_frame.iLevel = 23;
            break;
          default:
            igi2_frame.iLevel = 21;
            break;
        }
        D3DXCheckTextureRequirements(
          (int)Direct3D_ptDevice,
          (int)&igi2_frame.eFormat,
          (int)&igi2_frame.nDestWidth,
          (int)&igi2_frame.v29,
          0,
          (int)&igi2_frame.iLevel,
          1);
      }
      ptTexInfo = ptDownloadTextureContext->ptTexInfo;
      memset(ptDownloadTextureContext->ptTexInfo, 0, sizeof(struct TexInfo_s));
      v18 = 0;
      ptTexInfo->eRenderMode = Direct3D_eRenderMode;
      ptTexInfo->ptDirect3DTexture = nullptr;
      ptTexInfo->ptDirect3DBaseTexture = nullptr;
      Depth = Direct3D_GetDepth((enum _D3DFORMAT)igi2_frame.iLevel);
      ptTexInfo->tUVScale.vX = (double)igi2_frame.v33 / (double)(int)igi2_frame.eFormat;
      ptTexInfo->tUVScale.vY = (double)igi2_frame.nSourceHeight / (double)igi2_frame.nDestWidth;
      ptTexInfo->nWidth = igi2_frame.eFormat;
      v20 = igi2_frame.nDestWidth;
      ptTexInfo->nPitch = nWidth * (Depth / 8);
      LOWORD(Depth) = igi2_frame.v36;
      ptTexInfo->nHeight = v20;
      ptTexInfo->nType = Depth;
      ptTexInfo->vTransparency = 0.0;
      ptTexInfo->bFlags = ptDownloadTextureContext->bFlags;
      ptDownloadTextureContext->ptTexInfo->eDirect3DFormat = igi2_frame.iLevel;
      v21 = Direct3D_ptDevice->lpVtbl->CreateTexture(
              Direct3D_ptDevice,
              igi2_frame.eFormat,
              igi2_frame.nDestWidth,
              igi2_frame.v29,
              0,
              (enum _D3DFORMAT)igi2_frame.iLevel,
              D3DPOOL_MANAGED,
              &ptDownloadTextureContext->ptTexInfo->ptDirect3DTexture);
      if ( v21 )
      {
        sprintf(igi2_frame.Buffer, "Couldn't create texture");
        ErrorString = Direct3D_GetErrorString(v21);
        LDebug_Error(
          "%s\n\nDirectX error message: %s\nFile: %s Line: %d",
          igi2_frame.Buffer,
          ErrorString,
          "\\project\\igi2\\B\\4\\PC\\pc_direct3dtexture.c",
          919);
LABEL_7:
        abort();
      }
      ptDownloadTextureContext->ptTexInfo->ptDirect3DBaseTexture = (struct IDirect3DBaseTexture8 *)ptDownloadTextureContext->ptTexInfo->ptDirect3DTexture;
      if ( igi2_frame.v29 > 0 )
      {
        do
        {
          Direct3DTexture_ConvertARGB8888ToRawDirectDrawSurface(
            ptDownloadTextureContext->ptTexInfo->ptDirect3DTexture,
            v18++,
            (enum _D3DFORMAT)igi2_frame.iLevel,
            igi2_frame.eFormat,
            igi2_frame.nDestWidth,
            (int *)igi2_frame.nDestHeight,
            nWidth,
            igi2_frame.nSourceHeight);
          if ( v18 < igi2_frame.v29 )
            TextureUtility_ShrinkToHalf32HighQuality((void *)igi2_frame.nDestHeight, (void *)igi2_frame.nDestHeight, nWidth, igi2_frame.nSourceHeight);
          nWidth >>= 1;
          igi2_frame.nSourceHeight >>= 1;
          igi2_frame.eFormat >>= 1;
          igi2_frame.nDestWidth >>= 1;
        }
        while ( v18 < igi2_frame.v29 );
      }
      if ( igi2_frame.nDestHeight )
      {
        v23 = *(_DWORD *)((igi2_frame.nDestHeight - 4) & 0xFFFFFFFC);
        --Mem_nCurrentAllocations;
        Node_Remove((_DWORD **)v23);
        memset(*(void **)(v23 + 8), 0xCDu, *(_DWORD *)(v23 + 16));
        free((void *)v23);
      }
      v24 = Texture_eCategory;
      v25 = Direct3DTexture_GetFootPrint(ptDownloadTextureContext->ptTexInfo->ptDirect3DTexture);
      v26 = Texture_anTextureFootprint[v24];
      ++Texture_anTextureNum[v24];
      v27 = Texture_anTextureNum[2];
      Texture_anTextureFootprint[v24] = v25 + v26;
      Texture_anTextureNum[2] = v27 + 1;
      Texture_anTextureFootprint[2] += v25;
      return;
    default:
      LDebug_Error("Unsupported texture format");
      goto LABEL_7;
  }
}

// source: b/4/pc/pc_direct3dtexture.c:968  [size]
void __cdecl Direct3DTexture_AllocPalette(struct AllocPaletteContext_s *ptAllocPaletteContext)
{
  struct PalInfo *ptPalInfo; // edi
  void *v2; // eax
  void *pxData; // esi

  ptPalInfo = ptAllocPaletteContext->ptPalInfo;
  v2 = Mem_AllocFn(1024, 4);
  ptPalInfo->pxPalette = v2;
  pxData = ptAllocPaletteContext->pxData;
  if ( pxData )
    qmemcpy(v2, pxData, 0x400u);
}

// source: b/4/pc/pc_direct3dtexture.c:994  [size]
void __cdecl Direct3DTexture_DeAllocPalette(struct PalInfo *ptPalInfo)
{
  void *pxPalette; // eax
  int v2; // esi

  pxPalette = ptPalInfo->pxPalette;
  if ( pxPalette )
  {
    v2 = *(_DWORD *)(((int)pxPalette - 4) & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v2);
    memset(*(void **)(v2 + 8), 0xCDu, *(_DWORD *)(v2 + 16));
    free((void *)v2);
    ptPalInfo->pxPalette = nullptr;
  }
}

// source: b/4/pc/pc_direct3dtexture.c:1015  [size]
void __cdecl Direct3DTexture_DownloadPalette(struct PalInfo *ptPalInfo)
{
  ;
}

// source: b/4/pc/pc_direct3dtexture.c:1029  [size]
void __cdecl Direct3DTexture_RefreshTextures(void *pxContext)
{
  ;
}

// source: b/4/pc/pc_direct3dtexture.c:1041  [size]
void __cdecl Direct3DTexture_ReloadTextures(void *pxContext)
{
  ;
}

// source: b/4/pc/pc_direct3dtexture.c:1053  [size]
void __cdecl Direct3DTexture_GetTMUs(struct GetTMUsContext_s *ptContext)
{
  if ( Direct3D_tCaps.MaxSimultaneousTextures >= Direct3D_tCaps.MaxTextureBlendStages )
    ptContext->nTMUs = Direct3D_tCaps.MaxTextureBlendStages;
  else
    ptContext->nTMUs = Direct3D_tCaps.MaxSimultaneousTextures;
}

// source: b/4/pc/pc_direct3dtexture.c:1067  [size]
void __cdecl Direct3DTexture_SetActiveTMU(struct SetActiveTMUContext_s *ptContext)
{
  Direct3DTexture_eActiveTMU = ptContext->eTMU;
}

// source: b/4/pc/pc_direct3dtexture.c:1082  [size]
void __cdecl Direct3DTexture_GetActiveTMU(struct GetActiveTMUContext_s *ptContext)
{
  ptContext->eTMU = Direct3DTexture_eActiveTMU;
}

// source: b/4/pc/pc_direct3dtexture.c:1096  [size]
void __cdecl Direct3DTexture_SetLOD(struct SetLODContext_t *ptContext)
{
  Direct3DTexture_nLOD = ptContext->nLOD;
}

// source: b/4/pc/pc_direct3dtexture.c:1141  [size]
void __cdecl Direct3DTexture_Close()
{
  QVector_Delete(Direct3DTexture_ptPalettedTextureContainer);
}
