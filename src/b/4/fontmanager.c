/* b/4/fontmanager.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: b/4/fontmanager.c:96  [anchor-mhash]
void __cdecl FontManager_EnumerateMapFunction(
        struct ManagedFont_s *ptManagedFont,
        struct EnumFontsMyContext_s *ptEnumFontsMyContext)
{
  struct QSprite_s *ptFont; // ecx
  void (__cdecl *pfEnumFontsCallback)(struct EnumFontsContext_s *, void *); // eax
  bool v4; // zf
  struct EnumFontsContext_s tEnumFontsContext; // [esp+4h] [ebp-8h] BYREF

  ptFont = ptManagedFont->ptFont;
  tEnumFontsContext.pzFilename = ptManagedFont->zFilename;
  pfEnumFontsCallback = ptEnumFontsMyContext->pfEnumFontsCallback;
  v4 = ptEnumFontsMyContext->pfEnumFontsCallback == nullptr;
  tEnumFontsContext.ptFont = ptFont;
  if ( !v4 )
    pfEnumFontsCallback(&tEnumFontsContext, ptEnumFontsMyContext->pxContext);
  ++ptEnumFontsMyContext->nCount;
}

// source: b/4/fontmanager.c:118  [anchor-mhash]
void __cdecl FontManager_ModeChangeMapFunction(struct ManagedFont_s *ptManagedFont, void *pxUnused)
{
  if ( ptManagedFont->ptFont )
  {
    Font_ForceDelete(ptManagedFont->ptFont);
    ptManagedFont->ptFont = nullptr;
  }
}

// source: b/4/fontmanager.c:136  [size]
void __cdecl FontManager_ModeChangeCallback()
{
  unsigned int nAllocated; // edi
  unsigned int v1; // esi
  struct QSprite_s **v2; // ebp
  struct QSprite_s *v3; // ebx
  int v4; // esi
  unsigned int v5; // [esp+8h] [ebp-Ch]
  void ***p_papxElement; // [esp+Ch] [ebp-8h]
  unsigned int v7; // [esp+10h] [ebp-4h]

  nAllocated = FontManager_ptQObjectVector->nAllocated;
  v1 = 0;
  v7 = nAllocated;
  v5 = 0;
  if ( nAllocated )
  {
    p_papxElement = &FontManager_ptQObjectVector->papxElement;
    do
    {
      v2 = (struct QSprite_s **)(*p_papxElement)[v1];
      v3 = *v2;
      if ( *v2 )
      {
        QSprite_DeAlloc(v3);
        v4 = *(_DWORD *)((unsigned int)&v3[-1].nQAnimframes & 0xFFFFFFFC);
        --Mem_nCurrentAllocations;
        Node_Remove((_DWORD **)v4);
        memset(*(void **)(v4 + 8), 0xCDu, *(_DWORD *)(v4 + 16));
        free((void *)v4);
        v1 = v5;
        nAllocated = v7;
        *v2 = nullptr;
      }
      v5 = ++v1;
    }
    while ( v1 < nAllocated );
  }
}

// source: b/4/fontmanager.c:149  [anchor-mhash]
void __cdecl FontManager_NameMapFunction(
        struct ManagedFont_s *ptManagedFont,
        struct FontManagerMapContext_s *ptFontManagerMapContext)
{
  if ( !_stricmp(ptManagedFont->zFilename, ptFontManagerMapContext->zFilename) )
    ptFontManagerMapContext->ptManagedFont = ptManagedFont;
}

// source: b/4/fontmanager.c:168  [size]
void __cdecl FontManager_SpriteMapFunction(
        struct ManagedFont_s *ptManagedFont,
        struct FontManagerMapContext_s *ptFontManagerMapContext)
{
  if ( ptManagedFont->ptFont == ptFontManagerMapContext->ptFont )
    ptFontManagerMapContext->ptManagedFont = ptManagedFont;
}

// source: b/4/fontmanager.c:187  [anchor-callee]
struct ManagedFont_s *__cdecl FontManager_FindFontByName(char *zFilename)
{
  unsigned int nAllocated; // ebx
  unsigned int v2; // edi
  void ***p_papxElement; // ebp
  struct ManagedFont_s *v4; // esi
  struct ManagedFont_s *tFontManagerMapContext; // [esp+8h] [ebp-Ch]

  nAllocated = FontManager_ptQObjectVector->nAllocated;
  v2 = 0;
  tFontManagerMapContext = nullptr;
  if ( !nAllocated )
    return nullptr;
  p_papxElement = &FontManager_ptQObjectVector->papxElement;
  do
  {
    v4 = (struct ManagedFont_s *)(*p_papxElement)[v2];
    if ( !_stricmp(v4->zFilename, zFilename) )
      tFontManagerMapContext = v4;
    ++v2;
  }
  while ( v2 < nAllocated );
  return tFontManagerMapContext;
}

// source: b/4/fontmanager.c:207  [anchor-mhash]
struct ManagedFont_s *__cdecl FontManager_FindFontBySprite(struct QSprite_s *ptQSprite)
{
  struct ManagedFont_s *result; // eax
  void **papxElement; // edx
  unsigned int nAllocated; // esi

  result = nullptr;
  if ( FontManager_ptQObjectVector->nAllocated )
  {
    papxElement = FontManager_ptQObjectVector->papxElement;
    nAllocated = FontManager_ptQObjectVector->nAllocated;
    do
    {
      if ( *(struct QSprite_s **)*papxElement == ptQSprite )
        result = (struct ManagedFont_s *)*papxElement;
      ++papxElement;
      --nAllocated;
    }
    while ( nAllocated );
  }
  return result;
}

// source: b/4/fontmanager.c:230  [size]
struct QSprite_s *__cdecl FontManager_GetUpdatedFont(struct ManagedFont_s *ptManagedFont)
{
  struct QSprite_s *result; // eax

  result = ptManagedFont->ptFont;
  if ( !ptManagedFont->ptFont )
  {
    if ( RenderMode_eActiveRenderMode == -1 )
    {
      return nullptr;
    }
    else
    {
      result = Font_ForceLoad(ptManagedFont->zFilename);
      ptManagedFont->ptFont = result;
    }
  }
  return result;
}

// source: b/4/fontmanager.c:255  [anchor-mhash]
struct ManagedFont_s *__cdecl FontManager_RegisterFont(char *zFilename)
{
  unsigned int *p_nAllocated; // esi
  struct QObjectVector_s *v2; // edi
  struct ManagedFont_s *v3; // ebx

  p_nAllocated = &FontManager_ptQObjectVector->nAllocated;
  v2 = FontManager_ptQObjectVector;
  if ( FontManager_ptQObjectVector->nAllocated == FontManager_ptQObjectVector->nSize )
    QObjectVector_Realloc(FontManager_ptQObjectVector, FontManager_ptQObjectVector->nReallocSize);
  v3 = (struct ManagedFont_s *)v2->papxElement[(*p_nAllocated)++];
  memset(v3, 0, sizeof(struct ManagedFont_s));
  strcpy(v3->zFilename, zFilename);
  return v3;
}

// source: b/4/fontmanager.c:277  [anchor-hash]
void __cdecl FontManager_RemoveFont(struct ManagedFont_s *ptManagedFont)
{
  if ( ptManagedFont->ptFont )
    Font_ForceDelete(ptManagedFont->ptFont);
  QObjectVector_RemoveElement(
    FontManager_ptQObjectVector,
    *(_DWORD *)((char *)ptManagedFont + FontManager_ptQObjectVector->nElementSize - 4));
}

// source: b/4/fontmanager.c:298  [size]
struct ManagedFont_s *__cdecl FontManager_AddRef(struct ManagedFont_s *ptManagedFont)
{
  ++ptManagedFont->nRefCount;
  return ptManagedFont;
}

// source: b/4/fontmanager.c:316  [anchor-hash]
int __cdecl FontManager_Release(struct ManagedFont_s *ptManagedFont)
{
  int result; // eax

  result = ptManagedFont->nRefCount - 1;
  ptManagedFont->nRefCount = result;
  if ( !result )
  {
    if ( ptManagedFont->ptFont )
      Font_ForceDelete(ptManagedFont->ptFont);
    QObjectVector_RemoveElement(
      FontManager_ptQObjectVector,
      *(_DWORD *)((char *)ptManagedFont + FontManager_ptQObjectVector->nElementSize - 4));
    return 0;
  }
  return result;
}

// source: b/4/fontmanager.c:339  [size]
struct QSprite_s *__cdecl FontManager_LoadFont(char *zFilename)
{
  struct ManagedFont_s *FontByName; // esi
  struct QSprite_s *result; // eax
  bool v3; // zf

  FontByName = FontManager_FindFontByName(zFilename);
  if ( !FontByName )
    FontByName = FontManager_RegisterFont(zFilename);
  result = FontByName->ptFont;
  v3 = FontByName->ptFont == nullptr;
  ++FontByName->nRefCount;
  if ( v3 )
  {
    if ( RenderMode_eActiveRenderMode == -1 )
    {
      return nullptr;
    }
    else
    {
      result = Font_ForceLoad(FontByName->zFilename);
      FontByName->ptFont = result;
    }
  }
  return result;
}

// source: b/4/fontmanager.c:361  [anchor-callee]
int __cdecl FontManager_DeleteFont(struct QSprite_s *ptFont)
{
  struct QObjectVector_s *v1; // edi
  struct QSprite_s **v2; // esi
  void **papxElement; // edx
  unsigned int nAllocated; // eax
  int result; // eax

  v1 = FontManager_ptQObjectVector;
  v2 = nullptr;
  if ( FontManager_ptQObjectVector->nAllocated )
  {
    papxElement = FontManager_ptQObjectVector->papxElement;
    nAllocated = FontManager_ptQObjectVector->nAllocated;
    do
    {
      if ( *(struct QSprite_s **)*papxElement == ptFont )
        v2 = (struct QSprite_s **)*papxElement;
      ++papxElement;
      --nAllocated;
    }
    while ( nAllocated );
    if ( v2 )
    {
      result = (int)&v2[66][-1].nPad0;
      v2[66] = (struct QSprite_s *)result;
      if ( result )
        return result;
      if ( *v2 )
      {
        Font_ForceDelete(*v2);
        v1 = FontManager_ptQObjectVector;
      }
      QObjectVector_RemoveElement(v1, *(unsigned int *)((char *)v2 + v1->nElementSize - 4));
    }
  }
  return 0;
}

// source: b/4/fontmanager.c:382  [anchor-hash]
int __cdecl FontManager_DeleteFontByName(char *zFilename)
{
  struct ManagedFont_s *FontByName; // eax
  struct ManagedFont_s *v2; // esi
  int result; // eax

  FontByName = FontManager_FindFontByName(zFilename);
  v2 = FontByName;
  if ( FontByName )
  {
    result = FontByName->nRefCount - 1;
    v2->nRefCount = result;
    if ( result )
      return result;
    if ( v2->ptFont )
      Font_ForceDelete(v2->ptFont);
    QObjectVector_RemoveElement(
      FontManager_ptQObjectVector,
      *(_DWORD *)((char *)v2 + FontManager_ptQObjectVector->nElementSize - 4));
  }
  return 0;
}

// source: b/4/fontmanager.c:403  [anchor-callee]
int __cdecl FontManager_EnumerateFonts(
        void (__cdecl *pfEnumFontsCallback)(struct EnumFontsContext_s *, void *),
        void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { void ***p_papxElement; };
    struct { char igi2_o1[4]; _DWORD v8[2]; };
    char igi2_extent[12];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  unsigned int nAllocated; // edi
  int v3; // ebp
  unsigned int v4; // esi
  _DWORD *v5; // eax

  nAllocated = FontManager_ptQObjectVector->nAllocated;
  v3 = 0;
  v4 = 0;
  if ( nAllocated )
  {
    igi2_frame.p_papxElement = &FontManager_ptQObjectVector->papxElement;
    do
    {
      v5 = (*igi2_frame.p_papxElement)[v4];
      igi2_frame.v8[1] = *v5;
      igi2_frame.v8[0] = v5 + 1;
      if ( pfEnumFontsCallback )
        pfEnumFontsCallback((struct EnumFontsContext_s *)igi2_frame.v8, pxContext);
      ++v3;
      ++v4;
    }
    while ( v4 < nAllocated );
  }
  return v3;
}

// source: b/4/fontmanager.c:422  [anchor-hash]
void __cdecl FontManager_Open()
{
  struct QObjectVector_s *v0; // esi

  Display_RegisterCallback(FontManager_ModeChangeCallback, &Display_ptSetModeCallback);
  v0 = (struct QObjectVector_s *)Mem_AllocFn(52, 4);
  v0->isStrictOrder = true;
  v0->nSize = 0;
  v0->nAllocated = 0;
  v0->nReallocSize = 16;
  v0->papxElement = nullptr;
  v0->nElementSize = 272;
  v0->tMemPool.nBlocks = 0;
  v0->tMemPool.nAllocatedBlocks = 0;
  v0->tMemPool.nAlignment = 4;
  v0->tMemPool.nBlockSize = 272;
  v0->tMemPool.nReAllocBlocks = 16;
  v0->tMemPool.tMemPoolFreeList.ptHead = nullptr;
  v0->tMemPool.tMemPoolSegmentList.ptHead = nullptr;
  MemPool_ReAlloc(&v0->tMemPool, 0x10u);
  QObjectVector_Realloc(v0, 0x10u);
  FontManager_ptQObjectVector = v0;
}

// source: b/4/fontmanager.c:436  [anchor-hash]
void __cdecl FontManager_Close()
{
  struct DisplayCallbackChain_s *v0; // eax
  struct DisplayCallbackChain_s *v1; // ecx

  QObjectVector_Delete(FontManager_ptQObjectVector);
  v0 = Display_ptSetModeCallback;
  v1 = nullptr;
  if ( Display_ptSetModeCallback )
  {
    while ( v0->pfCallback != FontManager_ModeChangeCallback )
    {
      v1 = v0;
      v0 = v0->ptNext;
      if ( !v0 )
        return;
    }
    if ( v1 )
      v1->ptNext = v0->ptNext;
    else
      Display_ptSetModeCallback = v0->ptNext;
  }
}
