/* b/1/ilfparse.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: b/1/ilfparse.c:46  [anchor-callee]
void *__cdecl ILF_GetNextChunk(void *pxChunk)
{
  int v1; // eax

  if ( pxChunk && (v1 = *((_DWORD *)pxChunk + 3)) != 0 )
    return (char *)pxChunk + v1;
  else
    return nullptr;
}

// source: b/1/ilfparse.c:76  [anchor-hash]
void *__cdecl ILF_GetFirstChunk(void *pxContainer)
{
  unsigned int v1; // edx
  int v2; // eax
  unsigned int v3; // eax

  if ( pxContainer )
  {
    v1 = *((_DWORD *)pxContainer + 1);
    if ( v1 )
    {
      v2 = *((_DWORD *)pxContainer + 2);
      if ( (v2 & ~(v2 - 1)) == v2 )
      {
        v3 = ~(v2 - 1) & (v2 + 19);
        if ( v3 < v1 )
          return (char *)pxContainer + v3;
      }
      else
      {
        ILF_nLastError = 1;
      }
    }
  }
  return nullptr;
}

// source: b/1/ilfparse.c:120  [anchor-callee]
void *__cdecl ILF_GetChunkData(void *pxChunk, void *pxContainer)
{
  unsigned int v2; // esi
  unsigned int v3; // ecx

  if ( !pxContainer || !pxChunk )
    return nullptr;
  v2 = *((_DWORD *)pxContainer + 2);
  if ( (v2 & ~(v2 - 1)) != v2
    || (unsigned int)((_BYTE *)pxChunk - (_BYTE *)pxContainer) >= *((_DWORD *)pxContainer + 1)
    || (v3 = *((_DWORD *)pxChunk + 2), (v3 & ~(v3 - 1)) != v3)
    || v3 > v2 )
  {
    ILF_nLastError = 1;
    return nullptr;
  }
  if ( !*((_DWORD *)pxChunk + 1) )
    return nullptr;
  return (char *)pxContainer + (~(v3 - 1) & (v3 + ((_BYTE *)pxChunk - (_BYTE *)pxContainer) + 15));
}

// source: b/1/ilfparse.c:186  [anchor-mhash]
void *__cdecl ILF_GetChunkAttributes(
        unsigned int *pnSize,
        unsigned int *pnAlignment,
        void *pxChunk)
{
  if ( pxChunk )
  {
    if ( pnSize )
      *pnSize = *((_DWORD *)pxChunk + 1);
    if ( pnAlignment )
    {
      pxChunk = *((void **)pxChunk + 2);
      *pnAlignment = (unsigned int)pxChunk;
    }
  }
  return pxChunk;
}

// source: b/1/ilfparse.c:213  [anchor-hash]
unsigned int __cdecl ILF_GetContainerType(void *pxContainer)
{
  if ( pxContainer )
    return *((_DWORD *)pxContainer + 4);
  else
    return 0;
}

// source: b/1/ilfparse.c:234  [anchor-hash]
unsigned int __cdecl ILF_GetChunkId(void *pxChunk)
{
  if ( pxChunk )
    return *(_DWORD *)pxChunk;
  else
    return 0;
}

// source: b/1/ilfparse.c:252  [size]
int __cdecl ILF_GetLastError()
{
  return ILF_nLastError;
}

// source: b/1/ilfparse.c:265  [size]
void __cdecl ILF_ResetError()
{
  ILF_nLastError = 0;
}
