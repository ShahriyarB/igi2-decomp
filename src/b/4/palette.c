/* b/4/palette.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: b/4/palette.c:35  [anchor-hash]
void __cdecl Palette_Open()
{
  int v0; // eax
  int v1; // eax
  int v2; // eax

  v0 = 0;
  while ( RenderMode_atRenderModeMethod[v0].isAllocated )
  {
    if ( ++v0 >= 128 )
    {
      LDebug_Error("RenderMode: Failed to create new method '%s'", "AllocPalette");
      goto LABEL_5;
    }
  }
  RenderMode_atRenderModeMethod[v0].zName = "AllocPalette";
  RenderMode_atRenderModeMethod[v0].isAllocated = 1;
  Palette_eAllocPaletteMethod = v0;
  v1 = 0;
  while ( RenderMode_atRenderModeMethod[v1].isAllocated )
  {
    if ( ++v1 >= 128 )
    {
      LDebug_Error("RenderMode: Failed to create new method '%s'", "DeAllocPalette");
      goto LABEL_5;
    }
  }
  RenderMode_atRenderModeMethod[v1].zName = "DeAllocPalette";
  RenderMode_atRenderModeMethod[v1].isAllocated = 1;
  Palette_eDeAllocPaletteMethod = v1;
  v2 = 0;
  while ( RenderMode_atRenderModeMethod[v2].isAllocated )
  {
    if ( ++v2 >= 128 )
    {
      LDebug_Error("RenderMode: Failed to create new method '%s'", "DownloadPalette");
LABEL_5:
      abort();
    }
  }
  RenderMode_atRenderModeMethod[v2].zName = "DownloadPalette";
  RenderMode_atRenderModeMethod[v2].isAllocated = 1;
  Palette_eDownloadPaletteMethod = v2;
}

// source: b/4/palette.c:50  [anchor-hash]
void __cdecl Palette_Close()
{
  int v0; // edx
  int v1; // ecx

  v0 = Palette_eDeAllocPaletteMethod;
  RenderMode_atRenderModeMethod[Palette_eAllocPaletteMethod].isAllocated = 0;
  v1 = Palette_eDownloadPaletteMethod;
  RenderMode_atRenderModeMethod[v0].isAllocated = 0;
  RenderMode_atRenderModeMethod[v1].isAllocated = 0;
}

// source: b/4/palette.c:72  [anchor-mhash]
struct PalInfo *__cdecl Palette_Alloc(struct PalInfo *ptPalInfo, void *pxData, int nType)
{
  struct AllocPaletteContext_s tAllocPaletteContext; // [esp+0h] [ebp-Ch] BYREF

  ptPalInfo->eRenderMode = RenderMode_eActiveRenderMode;
  tAllocPaletteContext.nType = nType;
  tAllocPaletteContext.ptPalInfo = ptPalInfo;
  tAllocPaletteContext.pxData = pxData;
  return ((struct PalInfo *(__cdecl *)(struct AllocPaletteContext_s *))RenderMode_tActiveRenderMode.apfRenderModeMethod[Palette_eAllocPaletteMethod])(&tAllocPaletteContext);
}

// source: b/4/palette.c:94  [anchor-mhash]
void __cdecl Palette_DeAlloc(struct PalInfo *ptPalInfo)
{
  if ( ptPalInfo->eRenderMode != -1 )
    RenderMode_atRenderMode[ptPalInfo->eRenderMode].apfRenderModeMethod[Palette_eDeAllocPaletteMethod](ptPalInfo);
}

// source: b/4/palette.c:113  [anchor-strings]
char *__cdecl Palette_Load(struct PalInfo *ptPalInfo, char *zFilename)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct Resource_s *ptResource; };
    struct { char igi2_o1[4]; struct Resource_s *pptResource[3]; };
    char igi2_extent[16];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  char *v3; // ecx
  struct Resource_s *v4; // eax
  char *pxData; // eax
  void *v6; // eax
  struct Resource_s *v7; // ecx
  int v8; // ecx
  char *result; // eax

  if ( Resource_IsLoadedInternal(zFilename, &igi2_frame.ptResource) )
  {
    v4 = igi2_frame.ptResource;
    igi2_frame.ptResource->isReferenced = 1;
    pxData = (char *)v4->pxData;
  }
  else
  {
    Game_MPRunNetwork(v3);
    v6 = File_Load(zFilename, (unsigned int *)&igi2_frame.ptResource);
    if ( !v6 )
    {
      LDebug_Error("Failed to load resource: '%s'", zFilename);
      goto LABEL_5;
    }
    pxData = (char *)Resource_ParseFile(File_zLastSubstitutedPath, v6, (unsigned int)igi2_frame.ptResource);
  }
  if ( *pxData != 76 || pxData[1] != 79 || pxData[2] != 79 || pxData[3] != 80 || *((_DWORD *)pxData + 1) != 3 )
  {
    LDebug_Error("'%s' is not a valid palette file.", zFilename);
LABEL_5:
    abort();
  }
  v7 = *((struct Resource_s **)pxData + 3);
  igi2_frame.pptResource[2] = (struct Resource_s *)(pxData + 16);
  igi2_frame.pptResource[1] = v7;
  v8 = Palette_eAllocPaletteMethod;
  ptPalInfo->eRenderMode = RenderMode_eActiveRenderMode;
  igi2_frame.pptResource[0] = (struct Resource_s *)ptPalInfo;
  RenderMode_tActiveRenderMode.apfRenderModeMethod[v8](igi2_frame.pptResource);
  result = (char *)Resource_IsLoadedInternal(zFilename, &igi2_frame.ptResource);
  if ( result )
  {
    result = (char *)igi2_frame.ptResource->nType;
    if ( result != (char *)3 && result != (char *)1 )
      Resource_Remove(igi2_frame.ptResource);
  }
  return result;
}

// source: b/4/palette.c:141  [anchor-hash]
struct PalInfo *__cdecl Palette_Download(struct PalInfo *ptPalInfo)
{
  return (struct PalInfo *)((int (__cdecl *)(struct PalInfo *))RenderMode_tActiveRenderMode.apfRenderModeMethod[Palette_eDownloadPaletteMethod])(ptPalInfo);
}
