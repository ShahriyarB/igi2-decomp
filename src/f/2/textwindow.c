/* f/2/textwindow.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: f/2/textwindow.c:35  [size]
struct TextWindow_s *__cdecl TextWindow_Scroll(struct TextWindow_s *ptWindow)
{
  struct TextWindow_s *result; // eax

  QTilemap_ScrollUp(ptWindow->ptQTilemap, 1);
  return result;
}

// source: f/2/textwindow.c:52  [size]
int __cdecl TextWindow_MoveDown(struct TextWindow_s *ptWindow, int nMoves)
{
  int v2; // ebx
  struct QTilemap_s *ptQTilemap; // ecx

  if ( nMoves )
  {
    v2 = nMoves;
    do
    {
      ptQTilemap = ptWindow->ptQTilemap;
      nMoves = ptWindow->nCursorY + 1;
      ptWindow->nCursorX = 0;
      ptWindow->nCursorY = nMoves;
      if ( nMoves >= ptQTilemap->nHeight )
      {
        ptWindow->nCursorY = nMoves - 1;
        QTilemap_ScrollUp(ptQTilemap, 1);
      }
      --v2;
    }
    while ( v2 );
  }
  return nMoves;
}

// source: f/2/textwindow.c:79  [size]
int __cdecl TextWindow_MoveRight(struct TextWindow_s *ptWindow, int nMoves)
{
  int v2; // ebx
  int nWidth; // ecx
  struct QTilemap_s *ptQTilemap; // ecx

  if ( nMoves )
  {
    v2 = nMoves;
    do
    {
      nWidth = ptWindow->nWidth;
      nMoves = ptWindow->nCursorX + 1;
      ptWindow->nCursorX = nMoves;
      if ( nMoves >= nWidth )
      {
        ptQTilemap = ptWindow->ptQTilemap;
        nMoves = ptWindow->nCursorY + 1;
        ptWindow->nCursorX = 0;
        ptWindow->nCursorY = nMoves;
        if ( nMoves >= ptQTilemap->nHeight )
        {
          ptWindow->nCursorY = nMoves - 1;
          QTilemap_ScrollUp(ptQTilemap, 1);
        }
      }
      --v2;
    }
    while ( v2 );
  }
  return nMoves;
}

// source: f/2/textwindow.c:103  [size]
char *__cdecl TextWindow_PrintText(struct TextWindow_s *ptWindow, char *zText)
{
  #pragma pack(push, 1)
  union
  {
    struct { char *i; };
    struct { char igi2_o1[4]; enum bool isNewline; };
    struct { char igi2_o2[8]; struct QTilemap_s *ptQTilemap; };
    struct { char igi2_o3[12]; char zBuffer[512]; };
    char igi2_extent[524];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  char *v3; // edi
  int v4; // edx
  char v5; // cl
  char *v6; // eax
  struct QTilemap_s *v8; // ebp
  unsigned __int8 v9; // dl
  unsigned __int8 *anID; // ecx
  char *v11; // ebx
  unsigned __int8 *v12; // eax
  struct QTilemap_s *v13; // ecx
  int v14; // ebp

  v3 = igi2_frame.zBuffer;
  v4 = igi2_frame.zBuffer - zText;
  do
  {
    v5 = *zText;
    zText[v4] = *zText;
    ++zText;
  }
  while ( v5 );
  if ( ptWindow->ptQTilemap )
  {
    while ( 1 )
    {
      v6 = nullptr;
      igi2_frame.isNewline = false;
      igi2_frame.i = nullptr;
      if ( *v3 )
      {
        while ( v3[(_DWORD)v6] != 10 )
        {
          if ( !v3[(_DWORD)v6++ + 1] )
            goto LABEL_9;
        }
        v3[(_DWORD)v6] = 0;
        igi2_frame.isNewline = true;
LABEL_9:
        igi2_frame.i = v6;
      }
      v8 = ptWindow->ptQTilemap;
      v9 = *v3;
      igi2_frame.ptQTilemap = (struct QTilemap_s *)ptWindow->nCursorY;
      anID = ptWindow->ptQTilemap->ptQSprite->ptQTilemap->anID;
      v11 = v3;
      if ( *v3 )
      {
        v12 = &v8->anID[ptWindow->nCursorX + ptWindow->nCursorY * ptWindow->ptQTilemap->nWidth];
        do
        {
          *v12 = anID[v9];
          v9 = v11[1];
          ++v12;
          ++v11;
        }
        while ( v9 );
      }
      QTilemap_UpdateGraphicWidth(v8, (int)igi2_frame.ptQTilemap);
      if ( igi2_frame.isNewline == false )
        return (char *)TextWindow_MoveRight(ptWindow, strlen(v3));
      v13 = ptWindow->ptQTilemap;
      v14 = ptWindow->nCursorY + 1;
      ptWindow->nCursorX = 0;
      ptWindow->nCursorY = v14;
      if ( v14 >= v13->nHeight )
      {
        ptWindow->nCursorY = v14 - 1;
        QTilemap_ScrollUp(v13, 1);
      }
      zText = igi2_frame.i;
      v3 = (char *)&igi2_frame.i[(_DWORD)v3 + 1];
      if ( !v3 )
        return zText;
    }
  }
  return zText;
}

// source: f/2/textwindow.c:160  [size]
struct TextWindow_s *__cdecl TextWindow_SetCursor(
        struct TextWindow_s *ptWindow,
        int nX,
        int nY)
{
  ptWindow->nCursorX = nX;
  ptWindow->nCursorY = nY;
  return ptWindow;
}

// source: f/2/textwindow.c:174  [anchor-callee]
void __cdecl TextWindow_Clear(struct TextWindow_s *ptWindow)
{
  struct QTilemap_s *ptQTilemap; // edx

  ptQTilemap = ptWindow->ptQTilemap;
  if ( ptWindow->ptQTilemap )
  {
    memset(ptQTilemap->anGraphicWidth, 0, 2 * ptQTilemap->nHeight);
    memset(ptQTilemap->anID, 0, ptQTilemap->nHeight * ptQTilemap->nWidth);
    ptWindow->nCursorX = 0;
    ptWindow->nCursorY = 0;
  }
}

// source: f/2/textwindow.c:192  [anchor-mhash]
struct TextWindow_s *__cdecl TextWindow_New(struct QSprite_s *ptFont, int nWidth, int nHeight)
{
  struct TextWindow_s *v4; // esi
  struct QTilemap_s *v5; // eax

  v4 = (struct TextWindow_s *)Mem_AllocFn(36, 4);
  if ( ptFont )
    v5 = QTilemap_New(nWidth, nHeight, ptFont);
  else
    v5 = nullptr;
  v4->nCursorX = 0;
  v4->nCursorY = 0;
  v4->nX = 0;
  v4->nY = 0;
  v4->isDisplayed = false;
  v4->ptQTilemap = v5;
  v4->nHeight = nHeight;
  v4->nWidth = nWidth;
  return v4;
}

// source: f/2/textwindow.c:218  [anchor-hash]
void __cdecl TextWindow_Delete(struct TextWindow_s *ptWindow)
{
  struct QTilemap_s *ptQTilemap; // eax
  int v3; // esi

  ptQTilemap = ptWindow->ptQTilemap;
  if ( ptQTilemap )
  {
    QTilemap_Delete(ptQTilemap);
    ptWindow->ptQTilemap = nullptr;
  }
  v3 = *(_DWORD *)((unsigned int)&ptWindow[-1].nPri & 0xFFFFFFFC);
  --Mem_nCurrentAllocations;
  Node_Remove((_DWORD **)v3);
  memset(*(void **)(v3 + 8), 0xCDu, *(_DWORD *)(v3 + 16));
  free((void *)v3);
}

// source: f/2/textwindow.c:237  [size]
struct TextWindow_s *__cdecl TextWindow_SetPos(
        struct TextWindow_s *ptWindow,
        int nX,
        int nY)
{
  ptWindow->nX = nX;
  ptWindow->nY = nY;
  return ptWindow;
}

// source: f/2/textwindow.c:254  [size]
int __cdecl TextWindow_SetPri(struct TextWindow_s *ptWindow, int nPri)
{
  ptWindow->nPri = nPri;
  return nPri;
}

// source: f/2/textwindow.c:268  [anchor-mhash]
struct TextWindow_s *__cdecl TextWindow_Register(struct TextWindow_s *ptWindow)
{
  float ptQTilemap; // [esp+0h] [ebp-28h]
  float vX; // [esp+4h] [ebp-24h]

  if ( ptWindow->isDisplayed )
  {
    if ( ptWindow->ptQTilemap )
    {
      vX = (float)ptWindow->nY;
      ptQTilemap = (float)ptWindow->nX;
      QTilemap_Register(ptWindow->ptQTilemap, ptQTilemap, vX, 128.0, 128.0, 128.0, 1.0, 1.0, 0, ptWindow->nPri);
    }
  }
  return ptWindow;
}

// source: f/2/textwindow.c:284  [size]
char *__cdecl TextWindow_vprintf(
        struct TextWindow_s *ptWindow,
        char *zFormat,
        char *pArgList)
{
  char zBuffer[512]; // [esp+0h] [ebp-200h] BYREF

  vsprintf(zBuffer, zFormat, pArgList);
  return (char *)TextWindow_PrintText(ptWindow, zBuffer);
}

// source: f/2/textwindow.c:303  [anchor-callee]
void TextWindow_printf(struct TextWindow_s *ptWindow, char *zFormat, ...)
{
  char Buffer[512]; // [esp+0h] [ebp-200h] BYREF
  va_list ArgList; // [esp+20Ch] [ebp+Ch] BYREF ARGSLOT

  va_start(ArgList, zFormat);
  vsprintf(Buffer, zFormat, ArgList);
  TextWindow_PrintText(ptWindow, Buffer);
}

// source: f/2/textwindow.c:321  [size]
enum bool __cdecl TextWindow_Show(
        struct TextWindow_s *ptWindow,
        enum bool isDisplayed)
{
  ptWindow->isDisplayed = isDisplayed;
  return isDisplayed;
}
