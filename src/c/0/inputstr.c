/* c/0/inputstr.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: c/0/inputstr.c:31  [size]
struct InputStream_s *__cdecl InputStream_Alloc(
        struct InputStream_s *ptStream,
        void *pxUserdata,
        int nSize,
        enum bool (__cdecl *pfGetInput)(struct InputStream_s *))
{
  char *v4; // eax
  unsigned int v5; // kr00_4

  v4 = (char *)Mem_AllocFn(Script_nInputBufferSize, 4);
  v5 = Script_nInputBufferSize;
  ptStream->zBuffer = v4;
  memset(v4, 0, v5);
  ptStream->zData = ptStream->zBuffer;
  ptStream->nSize = nSize;
  ptStream->nNextLine = 0;
  ptStream->nLine = 0;
  ptStream->nPos = 0;
  ptStream->pxUserdata = pxUserdata;
  ptStream->pfGetInput = pfGetInput;
  return ptStream;
}

// source: c/0/inputstr.c:53  [size]
void __cdecl InputStream_DeAlloc(struct InputStream_s *ptStream)
{
  char *zBuffer; // eax
  int v2; // esi

  zBuffer = ptStream->zBuffer;
  if ( zBuffer )
  {
    v2 = *(_DWORD *)((unsigned int)(zBuffer - 4) & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v2);
    memset(*(void **)(v2 + 8), 0xCDu, *(_DWORD *)(v2 + 16));
    free((void *)v2);
  }
  ptStream->zBuffer = nullptr;
}

// source: c/0/inputstr.c:70  [anchor-strings]
enum bool __cdecl SingleLine_GetInput(struct InputStream_s *ptStream)
{
  char v1; // al
  int v2; // ecx
  int i; // esi
  int nPos; // eax
  char v5; // al
  char *v6; // ecx
  char v7; // al
  int v8; // eax
  char *zBuffer; // ecx
  int v10; // eax
  char v12; // dl
  char *v15; // edx
  char v17; // dl

  v1 = *ptStream->zData;
  if ( v1 && v1 != 10 && v1 != 13 )
    return true;
  if ( ptStream->nPos < ptStream->nSize )
  {
    v2 = Script_nInputBufferSize - 2;
    for ( i = 0; i < v2; ++i )
    {
      nPos = ptStream->nPos;
      if ( nPos + i >= ptStream->nSize )
        break;
      v5 = *((_BYTE *)ptStream->pxUserdata + nPos + i);
      ptStream->zBuffer[i] = v5;
      ptStream->nLine = ptStream->nNextLine;
      if ( v5 == 13 || v5 == 10 || !v5 )
      {
        ptStream->zBuffer[i] = 0;
        while ( 1 )
        {
          if ( v5 != 13 )
          {
            if ( v5 == 10 )
            {
              ++ptStream->nNextLine;
            }
            else if ( v5 )
            {
              break;
            }
          }
          v8 = ptStream->nPos;
          ++i;
          if ( v8 + i >= ptStream->nSize )
            break;
          v5 = *((_BYTE *)ptStream->pxUserdata + v8 + i);
        }
        zBuffer = ptStream->zBuffer;
        ptStream->nPos += i;
        ptStream->zData = zBuffer;
        v10 = 0;
        if ( *zBuffer )
        {
          while ( 1 )
          {
            if ( zBuffer[v10] == 34 )
            {
              if ( zBuffer[++v10] )
              {
                do
                {
                  v12 = zBuffer[v10];
                  if ( v12 == 92 )
                  {
                    if ( !zBuffer[++v10] )
                    {
                      --v10;
                      break;
                    }
                  }
                  else if ( v12 == 34 )
                  {
                    break;
                  }
                  ++v10;
                }
                while ( ptStream->zBuffer[v10] );
              }
            }
            if ( zBuffer[v10] == 47 && zBuffer[v10 + 1] == 47 )
              goto LABEL_54;
            if ( !ptStream->zBuffer[++v10] )
              return true;
          }
        }
        return true;
      }
    }
    if ( i >= v2 )
    {
      if ( !i )
        goto LABEL_40;
      v6 = ptStream->zBuffer;
      while ( 1 )
      {
        v7 = v6[--i];
        if ( v7 == 32 || v7 == 9 )
          break;
        if ( !i )
          goto LABEL_40;
      }
      v6[i] = 0;
      if ( !i )
LABEL_40:
        Script_Error("Token too big in line %d '%s'.", ptStream->nLine, ptStream->zBuffer);
    }
    v15 = ptStream->zBuffer;
    ptStream->nPos += i;
    v15[i] = 0;
    zBuffer = ptStream->zBuffer;
    ptStream->zData = zBuffer;
    v10 = 0;
    if ( *zBuffer )
    {
      while ( 1 )
      {
        if ( zBuffer[v10] == 34 )
        {
          if ( zBuffer[++v10] )
          {
            do
            {
              v17 = zBuffer[v10];
              if ( v17 == 92 )
              {
                if ( !zBuffer[++v10] )
                {
                  --v10;
                  break;
                }
              }
              else if ( v17 == 34 )
              {
                break;
              }
              ++v10;
            }
            while ( ptStream->zBuffer[v10] );
          }
        }
        if ( zBuffer[v10] == 47 && zBuffer[v10 + 1] == 47 )
          break;
        if ( !ptStream->zBuffer[++v10] )
          return true;
      }
LABEL_54:
      zBuffer[v10] = 0;
    }
    return true;
  }
  return false;
}

// source: c/0/inputstr.c:216  [size]
struct InputStream_s *__cdecl InputStream_AllocLine(
        struct InputStream_s *ptStream,
        char *zLine,
        int nSize)
{
  return InputStream_Alloc(ptStream, (void *)zLine, nSize, SingleLine_GetInput);
}

// source: c/0/inputstr.c:229  [size]
int __cdecl InputStream_GetInput(struct InputStream_s *ptStream)
{
  return ptStream->pfGetInput(ptStream);
}
