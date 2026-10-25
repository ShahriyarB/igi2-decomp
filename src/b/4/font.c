/* b/4/font.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: b/4/font.c:29  [size]
// attributes: thunk
struct QSprite_s *__cdecl Font_Load(char *zFilename)
{
  return FontManager_LoadFont(zFilename);
}

// source: b/4/font.c:35  [anchor-mhash]
struct QSprite_s *__cdecl Font_ForceLoad(char *zFilename)
{
  struct QSprite_s *v1; // esi
  int v3; // esi

  v1 = (struct QSprite_s *)Mem_AllocFn(24, 4);
  if ( QSprite_Load(v1, zFilename) )
    return v1;
  if ( v1 )
  {
    v3 = *(_DWORD *)((unsigned int)&v1[-1].nQAnimframes & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v3);
    memset(*(void **)(v3 + 8), 0xCDu, *(_DWORD *)(v3 + 16));
    free((void *)v3);
  }
  return nullptr;
}

// source: b/4/font.c:57  [size]
// attributes: thunk
void __cdecl Font_Delete(struct QSprite_s *ptQSprite)
{
  FontManager_DeleteFont(ptQSprite);
}

// source: b/4/font.c:64  [anchor-callee]
void __cdecl Font_ForceDelete(struct QSprite_s *ptQSprite)
{
  int v2; // esi

  QSprite_DeAlloc(ptQSprite);
  if ( ptQSprite )
  {
    v2 = *(_DWORD *)((unsigned int)&ptQSprite[-1].nQAnimframes & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v2);
    memset(*(void **)(v2 + 8), 0xCDu, *(_DWORD *)(v2 + 16));
    free((void *)v2);
  }
}

// source: b/4/font.c:78  [size]
int __cdecl Font_GetStringWidth(struct QSprite_s *ptQSprite, char *zString)
{
  int v2; // esi
  struct QAnimframe_s *atQAnimframe; // edi
  int nSpace; // ebp
  int result; // eax
  int v6; // ecx
  struct QTilemap_s *ptQTilemap; // ebx
  unsigned __int8 v8; // dl
  int v9; // edx

  v2 = strlen(zString);
  atQAnimframe = ptQSprite->atQAnimframe;
  nSpace = atQAnimframe[ptQSprite->nQAnimframes].nSpace;
  result = 0;
  v6 = 0;
  if ( v2 > 0 )
  {
    ptQTilemap = ptQSprite->ptQTilemap;
    do
    {
      v8 = ptQTilemap->anID[(unsigned __int8)zString[v6]];
      if ( v8 )
        v9 = atQAnimframe[v8 - 1].nSpace;
      else
        v9 = nSpace;
      result += v9;
      ++v6;
    }
    while ( v6 < v2 );
  }
  return result;
}

// source: b/4/font.c:109  [size]
int __cdecl Font_GetStringHeight(struct QSprite_s *ptQSprite, char *zString)
{
  return ptQSprite->atQAnimframe[ptQSprite->nQAnimframes].nHeight;
}
