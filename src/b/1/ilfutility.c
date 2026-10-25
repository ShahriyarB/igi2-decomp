/* b/1/ilfutility.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: b/1/ilfutility.c:29  [size]
int __cdecl ILF_IsContainer(void *pxChunk)
{
  return *(_DWORD *)pxChunk == 1179012169;
}

// source: b/1/ilfutility.c:57  [anchor-mhash]
void *__cdecl ILF_FindContainerType(void *pxChunk, int (__cdecl *pfIsContainer)(void *), unsigned int nType)
{
  int (__cdecl *v3)(void *); // ebx
  _DWORD *v4; // esi
  unsigned int v5; // edx
  int v6; // eax
  unsigned int v7; // eax
  char *v8; // eax
  void *result; // eax
  int v10; // eax

  v3 = pfIsContainer;
  if ( !pfIsContainer )
    v3 = ILF_IsContainer;
  v4 = pxChunk;
  if ( pxChunk )
  {
    while ( !v3(v4) )
    {
LABEL_13:
      v10 = v4[3];
      if ( v10 )
      {
        v4 = (_DWORD *)((char *)v4 + v10);
        if ( v4 )
          continue;
      }
      return nullptr;
    }
    if ( v4[4] == nType )
      return v4;
    v5 = v4[1];
    if ( v5 )
    {
      v6 = v4[2];
      if ( (v6 & ~(v6 - 1)) == v6 )
      {
        v7 = ~(v6 - 1) & (v6 + 19);
        if ( v7 < v5 )
        {
          v8 = (char *)v4 + v7;
          goto LABEL_12;
        }
      }
      else
      {
        ILF_nLastError = 1;
      }
    }
    v8 = nullptr;
LABEL_12:
    result = ILF_FindContainerType(v8, v3, nType);
    if ( result )
      return result;
    goto LABEL_13;
  }
  return nullptr;
}

// source: b/1/ilfutility.c:98  [anchor-mhash]
void *__cdecl ILF_FindChunk(void *pxChunk, unsigned int nId)
{
  int v2; // ecx

  if ( !pxChunk )
    return nullptr;
  while ( *(_DWORD *)pxChunk != nId )
  {
    v2 = *((_DWORD *)pxChunk + 3);
    if ( v2 )
    {
      pxChunk = (char *)pxChunk + v2;
      if ( pxChunk )
        continue;
    }
    return nullptr;
  }
  return pxChunk;
}
