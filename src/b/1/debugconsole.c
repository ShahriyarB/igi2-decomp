/* b/1/debugconsole.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: b/1/debugconsole.c:135  [anchor-hash]
struct DebugConsoleLine_s *__cdecl DebugConsoleLine_New()
{
  struct DebugConsoleLine_s *result; // eax

  result = (struct DebugConsoleLine_s *)Mem_AllocFn(28, 4);
  result->ptPrev = nullptr;
  result->ptNext = nullptr;
  result->tQString.nLength = 0;
  result->tQString.tPrivate.nAllocated = 0;
  result->tQString.tPrivate.nReallocSize = 64;
  result->tQString.tPrivate.patQStringChar = nullptr;
  result->tQString.tPrivate.pxAllocatedMem = nullptr;
  return result;
}

// source: b/1/debugconsole.c:154  [anchor-hash]
void __cdecl DebugConsoleLine_Delete(struct DebugConsoleLine_s *ptLine)
{
  int v2; // esi

  QString_DeAlloc(&ptLine->tQString);
  if ( ptLine )
  {
    v2 = *(_DWORD *)((unsigned int)&ptLine[-1].tQString.nLength & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v2);
    memset(*(void **)(v2 + 8), 0xCDu, *(_DWORD *)(v2 + 16));
    free((void *)v2);
  }
}

// source: b/1/debugconsole.c:170  [size]
unsigned int __cdecl DebugConsoleLine_Trim(
        struct DebugConsoleLine_s *ptLine,
        unsigned int nOffset)
{
  if ( ptLine->tQString.nLength > nOffset )
    ptLine->tQString.nLength = nOffset;
  return nOffset;
}

// source: b/1/debugconsole.c:185  [anchor-callee]
void __cdecl DebugConsoleLine_DeleteSubstring(
        struct DebugConsoleLine_s *ptLine,
        unsigned int nOffset,
        unsigned int nLength)
{
  unsigned int v3; // ecx
  unsigned int v4; // eax

  v3 = ptLine->tQString.nLength;
  if ( nOffset < v3 )
  {
    v4 = 0;
    if ( v3 - nOffset != nLength )
    {
      do
      {
        ptLine->tQString.tPrivate.patQStringChar[v4 + nOffset] = ptLine->tQString.tPrivate.patQStringChar[v4 + nOffset + nLength];
        ++v4;
      }
      while ( v4 < ptLine->tQString.nLength - nOffset - nLength );
    }
    ptLine->tQString.nLength -= nLength;
  }
}

// source: b/1/debugconsole.c:200  [anchor-caller]
struct DebugConsoleLine_s *__cdecl DebugConsole_ScrollUp(struct DebugConsole_s *ptConsole)
{
  struct DebugConsoleLineList_s *p_tDebugConsoleLineList; // edx
  struct DebugConsoleLine_s *ptHead; // esi
  struct DebugConsoleLine_s **p_ptMiddle; // ecx
  struct DebugConsoleLine_s *result; // eax
  _DWORD *v5; // eax

  p_tDebugConsoleLineList = &ptConsole->tDebugConsoleLineList;
  ptHead = ptConsole->tDebugConsoleLineList.ptHead;
  p_ptMiddle = &ptConsole->tDebugConsoleLineList.ptMiddle;
  result = nullptr;
  if ( ptHead != (struct DebugConsoleLine_s *)p_ptMiddle )
  {
    v5 = List_RemHead((int)p_ptMiddle, p_tDebugConsoleLineList);
    result = (struct DebugConsoleLine_s *)List_AddTail(v5, (int)p_tDebugConsoleLineList);
    if ( result->tQString.nLength )
      result->tQString.nLength = 0;
  }
  return result;
}

// source: b/1/debugconsole.c:223  [size]
struct DebugConsole_s *__cdecl DebugConsole_Find(int tConsoleID)
{
  struct DebugConsole_s *result; // eax
  struct DebugConsole_s *ptNext; // ecx

  result = DebugConsole_tConsoleList.ptHead;
  ptNext = DebugConsole_tConsoleList.ptHead->ptNext;
  if ( !DebugConsole_tConsoleList.ptHead->ptNext )
    return nullptr;
  while ( result->tConsoleID != tConsoleID )
  {
    result = ptNext;
    ptNext = ptNext->ptNext;
    if ( !ptNext )
      return nullptr;
  }
  return result;
}

// source: b/1/debugconsole.c:247  [anchor-mhash]
enum bool __cdecl DebugConsole_IsOnStack(int tConsoleID)
{
  int v1; // eax

  v1 = DebugConsole_nStackPointer;
  if ( DebugConsole_nStackPointer <= 0 )
    return false;
  while ( tConsoleID != DebugConsole_atActiveConsoleStack[v1] )
  {
    if ( --v1 <= 0 )
      return false;
  }
  return true;
}

// source: b/1/debugconsole.c:272  [anchor-callee]
void __cdecl DebugConsole_ClearAll(struct DebugConsole_s *ptConsole, enum bool isDeleteLines)
{
  struct DebugConsole_s *v2; // edi
  struct DebugConsoleLine_s *ptHead; // esi
  struct DebugConsoleLine_s *i; // ebp
  int v5; // esi

  v2 = ptConsole;
  ptHead = ptConsole->tDebugConsoleLineList.ptHead;
  for ( i = ptHead->ptNext; i; i = i->ptNext )
  {
    if ( isDeleteLines )
    {
      Node_Remove(ptHead);
      QString_DeAlloc(&ptHead->tQString);
      if ( ptHead )
      {
        v5 = *(_DWORD *)((unsigned int)&ptHead[-1].tQString.nLength & 0xFFFFFFFC);
        --Mem_nCurrentAllocations;
        Node_Remove((_DWORD **)v5);
        memset(*(void **)(v5 + 8), 0xCDu, *(_DWORD *)(v5 + 16));
        free((void *)v5);
        v2 = ptConsole;
      }
      --v2->nLines;
    }
    else if ( ptHead->tQString.nLength )
    {
      ptHead->tQString.nLength = 0;
    }
    ptHead = i;
  }
  v2->nCursorY = 0;
  v2->nCursorX = 0;
}

// source: b/1/debugconsole.c:302  [anchor-mhash]
enum bool __cdecl DebugConsole_IsLineAllowed(
        struct DebugConsole_s *ptConsole,
        int nY)
{
  int nMaxLines; // eax

  nMaxLines = ptConsole->nMaxLines;
  return nMaxLines == -1 || nMaxLines > nY;
}

// source: b/1/debugconsole.c:318  [anchor-callee]
struct DebugConsoleLine_s *__cdecl DebugConsole_InsertNewLineAfterLine(
        struct DebugConsole_s *ptConsole,
        struct DebugConsoleLine_s *ptInsertAfter)
{
  _DWORD *v2; // eax
  struct DebugConsoleLine_s *result; // eax

  v2 = Mem_AllocFn(28, 4);
  v2[1] = 0;
  *v2 = 0;
  v2[6] = 0;
  v2[3] = 0;
  v2[2] = 64;
  v2[4] = 0;
  v2[5] = 0;
  if ( ptInsertAfter )
    result = (struct DebugConsoleLine_s *)Node_InsertAfter(v2, (int)ptInsertAfter);
  else
    result = (struct DebugConsoleLine_s *)List_AddTail(v2, (int)&ptConsole->tDebugConsoleLineList);
  ++ptConsole->nLines;
  return result;
}

// source: b/1/debugconsole.c:344  [anchor-callee]
struct DebugConsoleLine_s *__cdecl DebugConsole_GetLine(
        struct DebugConsole_s *ptConsole,
        int nLine,
        enum bool isCreate)
{
  struct DebugConsoleLine_s *result; // eax
  struct DebugConsoleLine_s *ptNext; // ecx
  int v5; // esi
  struct DebugConsoleLine_s *v6; // edi
  int nMaxLines; // eax
  _DWORD *v8; // eax
  struct DebugConsoleLine_s *v9; // eax

  result = ptConsole->tDebugConsoleLineList.ptHead;
  ptNext = result->ptNext;
  v5 = 0;
  v6 = nullptr;
  if ( result->ptNext )
  {
    while ( v5 != nLine )
    {
      v6 = result;
      result = ptNext;
      ptNext = ptNext->ptNext;
      ++v5;
      if ( !ptNext )
        goto LABEL_4;
    }
  }
  else
  {
LABEL_4:
    if ( isCreate )
    {
      if ( v5 > nLine )
        return v6;
      while ( 1 )
      {
        nMaxLines = ptConsole->nMaxLines;
        if ( nMaxLines != -1 && nMaxLines <= v5 )
          break;
        v8 = Mem_AllocFn(28, 4);
        v8[1] = 0;
        *v8 = 0;
        v8[6] = 0;
        v8[3] = 0;
        v8[2] = 64;
        v8[4] = 0;
        v8[5] = 0;
        if ( v6 )
          v9 = (struct DebugConsoleLine_s *)Node_InsertAfter(v8, (int)v6);
        else
          v9 = (struct DebugConsoleLine_s *)List_AddTail(v8, (int)&ptConsole->tDebugConsoleLineList);
        v6 = v9;
        ++v5;
        ++ptConsole->nLines;
        if ( v5 > nLine )
          return v6;
      }
    }
    return nullptr;
  }
  return result;
}

// source: b/1/debugconsole.c:394  [anchor-callee]
struct DebugConsoleLine_s *__cdecl DebugConsole_SplitLine(
        struct DebugConsole_s *ptConsole,
        struct DebugConsoleLine_s *ptCurrentLine,
        int nOffset)
{
  int nMaxLines; // eax
  struct DebugConsoleLine_s *inserted; // ebx
  struct DebugConsoleLine_s *ptHead; // ecx
  struct DebugConsoleLineList_s *p_tDebugConsoleLineList; // edx
  struct DebugConsoleLine_s *v9; // eax
  _DWORD *v10; // eax
  struct QString_s *p_tQString; // esi
  struct DebugConsoleLine_s *result; // eax

  nMaxLines = ptConsole->nMaxLines;
  if ( nMaxLines == -1 || nMaxLines > ptConsole->nCursorY + 1 )
  {
    inserted = DebugConsole_InsertNewLineAfterLine(ptConsole, ptCurrentLine);
    ++ptConsole->nCursorY;
  }
  else
  {
    ptHead = ptConsole->tDebugConsoleLineList.ptHead;
    p_tDebugConsoleLineList = &ptConsole->tDebugConsoleLineList;
    v9 = nullptr;
    if ( ptHead != (struct DebugConsoleLine_s *)&ptConsole->tDebugConsoleLineList.ptMiddle )
    {
      v10 = List_RemHead((int)ptHead, p_tDebugConsoleLineList);
      v9 = (struct DebugConsoleLine_s *)List_AddTail(v10, (int)p_tDebugConsoleLineList);
      if ( v9->tQString.nLength )
        v9->tQString.nLength = 0;
    }
    inserted = v9;
  }
  p_tQString = &ptCurrentLine->tQString;
  if ( inserted->tQString.nLength )
    inserted->tQString.nLength = 0;
  QString_InsertSubString(&inserted->tQString, 0, p_tQString, nOffset, p_tQString->nLength - nOffset);
  result = inserted;
  if ( p_tQString->nLength > nOffset )
    p_tQString->nLength = nOffset;
  return result;
}

// source: b/1/debugconsole.c:423  [anchor-callee]
struct DebugConsole_s *__cdecl DebugConsole_InsertCStringInLine(
        struct DebugConsole_s *ptConsole,
        struct DebugConsoleLine_s *ptLine,
        unsigned int nOffset,
        char *zString,
        unsigned int nLength,
        enum bool isInsert)
{
  struct QString_s *p_tWorkQString; // ebx
  unsigned int i; // eax

  if ( nLength )
  {
    p_tWorkQString = &ptConsole->tWorkQString;
    QString_ReAlloc(&ptConsole->tWorkQString, nLength);
    for ( i = 0; i < nLength; ++i )
    {
      if ( i >= p_tWorkQString->tPrivate.nAllocated )
        break;
      p_tWorkQString->tPrivate.patQStringChar[i] = zString[i];
    }
    p_tWorkQString->nLength = i;
    if ( ptLine->tQString.nLength > __PAIR64__(isInsert, nOffset) )
      ptLine->tQString.nLength = nOffset;
    return (struct DebugConsole_s *)QString_InsertSubString(&ptLine->tQString, nOffset, p_tWorkQString, 0, nLength);
  }
  return ptConsole;
}

// source: b/1/debugconsole.c:447  [anchor-callee]
void __cdecl DebugConsole_ParseCString(struct DebugConsole_s *ptConsole, char *zString)
{
  enum bool isInsert; // esi
  struct DebugConsoleLine_s *Line; // eax
  unsigned int v4; // ebp
  int nCursorX; // eax
  struct DebugConsoleLine_s *ptHead; // edi
  struct DebugConsoleLine_s *v7; // eax
  _DWORD *v8; // eax
  int v9; // [esp-8h] [ebp-1Ch]
  struct DebugConsoleLine_s *ptLine; // [esp+Ch] [ebp-8h]
  enum bool v11; // [esp+10h] [ebp-4h]

  isInsert = ptConsole->isInsert;
  v11 = isInsert;
  Line = DebugConsole_GetLine(ptConsole, ptConsole->nCursorY, true);
  ptLine = Line;
  while ( 2 )
  {
    v4 = 0;
LABEL_3:
    switch ( zString[v4] )
    {
      case 0:
        DebugConsole_InsertCStringInLine(ptConsole, Line, ptConsole->nCursorX, zString, v4, isInsert);
        ptConsole->nCursorX += v4;
        return;
      case 8:
        DebugConsole_InsertCStringInLine(ptConsole, Line, ptConsole->nCursorX, zString, v4, isInsert);
        nCursorX = ptConsole->nCursorX;
        if ( nCursorX > 0 )
        {
          ptConsole->nCursorX = nCursorX - 1;
          DebugConsoleLine_DeleteSubstring(ptLine, nCursorX - 1, 1u);
        }
        Line = ptLine;
        isInsert = v11;
        zString += v4 + 1;
        continue;
      case 0xA:
        DebugConsole_InsertCStringInLine(ptConsole, Line, ptConsole->nCursorX, zString, v4, isInsert);
        if ( v11 )
        {
          ptLine = DebugConsole_SplitLine(ptConsole, ptLine, v4 + ptConsole->nCursorX);
          ptConsole->nCursorX = 0;
        }
        else
        {
          v9 = ptConsole->nCursorY + 1;
          ptConsole->nCursorY = v9;
          ptLine = DebugConsole_GetLine(ptConsole, v9, true);
          if ( !ptLine )
          {
            ptHead = ptConsole->tDebugConsoleLineList.ptHead;
            --ptConsole->nCursorY;
            v7 = nullptr;
            if ( ptHead != (struct DebugConsoleLine_s *)&ptConsole->tDebugConsoleLineList.ptMiddle )
            {
              v8 = List_RemHead((int)&ptConsole->tDebugConsoleLineList.ptMiddle, &ptConsole->tDebugConsoleLineList);
              v7 = (struct DebugConsoleLine_s *)List_AddTail(v8, (int)&ptConsole->tDebugConsoleLineList);
              if ( v7->tQString.nLength )
                v7->tQString.nLength = 0;
            }
            ptLine = v7;
          }
          ptConsole->nCursorX = 0;
        }
        goto LABEL_8;
      case 0xD:
        DebugConsole_InsertCStringInLine(ptConsole, Line, ptConsole->nCursorX, zString, v4, isInsert);
        ptConsole->nCursorX = 0;
LABEL_8:
        isInsert = v11;
        zString += v4 + 1;
        Line = ptLine;
        continue;
      default:
        ++v4;
        goto LABEL_3;
    }
  }
}

// source: b/1/debugconsole.c:535  [anchor-callee]
int __cdecl DebugConsole_Alloc(char *zName, int nMaxLines)
{
  char *v3; // esi
  int v4; // ecx
  int v5; // eax

  v3 = (char *)Mem_AllocFn(136, 4);
  memset(v3, 0, 0x88u);
  v4 = DebugConsole_nAllocID;
  *((_DWORD *)v3 + 14) = nMaxLines;
  *((_DWORD *)v3 + 10) = v4;
  strcpy(v3 + 72, zName);
  *((_DWORD *)v3 + 2) = v3 + 12;
  *((_DWORD *)v3 + 4) = v3 + 8;
  *((_DWORD *)v3 + 3) = 0;
  *((_DWORD *)v3 + 1) = 0;
  *(_DWORD *)v3 = 0;
  List_AddTail(v3, (int)&DebugConsole_tConsoleList);
  v5 = DebugConsole_nAllocID + 1;
  *((_DWORD *)v3 + 9) = 0;
  *((_DWORD *)v3 + 6) = 0;
  *((_DWORD *)v3 + 7) = 0;
  *((_DWORD *)v3 + 8) = 0;
  *((_DWORD *)v3 + 5) = 64;
  DebugConsole_nAllocID = v5;
  return *((_DWORD *)v3 + 10);
}

// source: b/1/debugconsole.c:561  [anchor-strings]
void __cdecl DebugConsole_DeAlloc(int tConsoleID)
{
  struct DebugConsole_s *ptHead; // edi
  struct DebugConsole_s *ptNext; // eax
  int v3; // eax
  struct DebugConsoleLine_s *v4; // eax
  struct DebugConsoleLine_s *i; // esi
  struct DebugConsoleLine_s *v6; // eax
  int v7; // esi

  ptHead = DebugConsole_tConsoleList.ptHead;
  ptNext = DebugConsole_tConsoleList.ptHead->ptNext;
  if ( !DebugConsole_tConsoleList.ptHead->ptNext )
  {
LABEL_4:
    LDebug_Error("DebugConsole_DeAlloc() : Cannot find console ID: %d", tConsoleID);
    goto LABEL_5;
  }
  while ( ptHead->tConsoleID != tConsoleID )
  {
    ptHead = ptNext;
    ptNext = ptNext->ptNext;
    if ( !ptNext )
      goto LABEL_4;
  }
  v3 = DebugConsole_nStackPointer;
  if ( DebugConsole_nStackPointer > 0 )
  {
    while ( tConsoleID != DebugConsole_atActiveConsoleStack[v3] )
    {
      if ( --v3 <= 0 )
        goto LABEL_9;
    }
    LDebug_Error("DebugConsole_DeAlloc() : Cannot deallocate active console.");
LABEL_5:
    abort();
  }
LABEL_9:
  v4 = ptHead->tDebugConsoleLineList.ptHead;
  for ( i = v4->ptNext; i; i = i->ptNext )
  {
    v6 = (struct DebugConsoleLine_s *)Node_Remove(v4);
    DebugConsoleLine_Delete(v6);
    --ptHead->nLines;
    v4 = i;
  }
  QString_DeAlloc(&ptHead->tWorkQString);
  Node_Remove(ptHead);
  v7 = *(_DWORD *)((unsigned int)&ptHead[-1].zName[60] & 0xFFFFFFFC);
  --Mem_nCurrentAllocations;
  Node_Remove((_DWORD **)v7);
  memset(*(void **)(v7 + 8), 0xCDu, *(_DWORD *)(v7 + 16));
  free((void *)v7);
}

// source: b/1/debugconsole.c:605  [anchor-callee]
void __cdecl DebugConsole_PushActiveConsole(int tConsoleID)
{
  struct DebugConsole_s *ptHead; // ecx
  struct DebugConsole_s *ptNext; // eax

  ptHead = DebugConsole_tConsoleList.ptHead;
  ptNext = DebugConsole_tConsoleList.ptHead->ptNext;
  if ( DebugConsole_tConsoleList.ptHead->ptNext )
  {
    while ( ptHead->tConsoleID != tConsoleID )
    {
      ptHead = ptNext;
      ptNext = ptNext->ptNext;
      if ( !ptNext )
        goto LABEL_4;
    }
  }
  else
  {
LABEL_4:
    ptHead = nullptr;
  }
  DebugConsole_atActiveConsoleStack[++DebugConsole_nStackPointer] = tConsoleID;
  DebugConsole_ptActiveDebugConsole = ptHead;
}

// source: b/1/debugconsole.c:627  [anchor-hash]
void __cdecl DebugConsole_PopActiveConsole()
{
  int v0; // edx
  struct DebugConsole_s *ptHead; // ecx
  struct DebugConsole_s *ptNext; // eax
  int v3; // edx

  v0 = --DebugConsole_nStackPointer;
  if ( DebugConsole_nStackPointer <= 0 )
  {
    DebugConsole_ptActiveDebugConsole = nullptr;
  }
  else
  {
    ptHead = DebugConsole_tConsoleList.ptHead;
    ptNext = DebugConsole_tConsoleList.ptHead->ptNext;
    if ( DebugConsole_tConsoleList.ptHead->ptNext )
    {
      v3 = DebugConsole_atActiveConsoleStack[v0];
      while ( ptHead->tConsoleID != v3 )
      {
        ptHead = ptNext;
        ptNext = ptNext->ptNext;
        if ( !ptNext )
          goto LABEL_6;
      }
    }
    else
    {
LABEL_6:
      ptHead = nullptr;
    }
    DebugConsole_ptActiveDebugConsole = ptHead;
  }
}

// source: b/1/debugconsole.c:651  [anchor-hash]
int __cdecl DebugConsole_GetActiveConsole()
{
  return DebugConsole_atActiveConsoleStack[DebugConsole_nStackPointer];
}

// source: b/1/debugconsole.c:664  [anchor-hash]
int __cdecl DebugConsole_SetCursor(int nX, int nY)
{
  struct DebugConsole_s *v2; // ecx
  int result; // eax

  v2 = DebugConsole_ptActiveDebugConsole;
  DebugConsole_ptActiveDebugConsole->nCursorX = nX;
  result = v2->nMaxLines;
  if ( result == -1 || result > nY )
    v2->nCursorY = nY;
  else
    v2->nCursorY = result;
  return result;
}

// source: b/1/debugconsole.c:690  [size]
int __cdecl DebugConsole_GetCursorX()
{
  return DebugConsole_ptActiveDebugConsole->nCursorX;
}

// source: b/1/debugconsole.c:708  [size]
int __cdecl DebugConsole_GetCursorY()
{
  return DebugConsole_ptActiveDebugConsole->nCursorY;
}

// source: b/1/debugconsole.c:726  [anchor-hash]
void __cdecl DebugConsole_Clear(enum bool isSetCursorHome)
{

  DebugConsole_ClearAll(DebugConsole_ptActiveDebugConsole, isSetCursorHome);
}

// source: b/1/debugconsole.c:744  [anchor-hash]
void __cdecl DebugConsole_ClearLine()
{
  struct DebugConsoleLine_s *Line; // eax
  unsigned int nLength; // ecx
  struct QString_s *p_tQString; // eax

  Line = DebugConsole_GetLine(DebugConsole_ptActiveDebugConsole, DebugConsole_ptActiveDebugConsole->nCursorY, true);
  nLength = Line->tQString.nLength;
  p_tQString = &Line->tQString;
  if ( nLength )
    p_tQString->nLength = 0;
}

// source: b/1/debugconsole.c:766  [anchor-hash]
void __cdecl DebugConsole_ClearLineFromCursor()
{
  struct DebugConsole_s *v0; // esi
  struct DebugConsoleLine_s *Line; // eax
  unsigned int nCursorX; // ecx

  v0 = DebugConsole_ptActiveDebugConsole;
  Line = DebugConsole_GetLine(DebugConsole_ptActiveDebugConsole, DebugConsole_ptActiveDebugConsole->nCursorY, true);
  nCursorX = v0->nCursorX;
  if ( Line->tQString.nLength > nCursorX )
    Line->tQString.nLength = nCursorX;
}

// source: b/1/debugconsole.c:788  [anchor-hash]
void __cdecl DebugConsole_PrintCString(char *zString)
{
  void (__cdecl *pfDebugConsolePrintCallback)(char *, void *); // ecx
  struct DebugConsole_s *v2; // ebx

  pfDebugConsolePrintCallback = DebugConsole_ptActiveDebugConsole->pfDebugConsolePrintCallback;
  v2 = DebugConsole_ptActiveDebugConsole;
  if ( pfDebugConsolePrintCallback )
    pfDebugConsolePrintCallback(zString, DebugConsole_ptActiveDebugConsole->pxPrintCallbackContext);
  if ( v2->nMaxLines )
    DebugConsole_ParseCString(v2, zString);
}

// source: b/1/debugconsole.c:817  [anchor-hash]
int __cdecl DebugConsole_FindFirst()
{
  if ( DebugConsole_tConsoleList.ptHead == (struct DebugConsole_s *)&DebugConsole_tConsoleList.ptMiddle )
    return -1;
  else
    return DebugConsole_tConsoleList.ptHead->tConsoleID;
}

// source: b/1/debugconsole.c:834  [anchor-mhash]
int __cdecl DebugConsole_FindNext(int tCurrentID)
{
  struct DebugConsole_s *ptHead; // ecx
  struct DebugConsole_s *ptNext; // eax

  ptHead = DebugConsole_tConsoleList.ptHead;
  ptNext = DebugConsole_tConsoleList.ptHead->ptNext;
  if ( DebugConsole_tConsoleList.ptHead->ptNext )
  {
    while ( ptHead->tConsoleID != tCurrentID )
    {
      ptHead = ptNext;
      ptNext = ptNext->ptNext;
      if ( !ptNext )
        goto LABEL_4;
    }
  }
  else
  {
LABEL_4:
    ptHead = nullptr;
  }
  if ( ptHead->ptNext->ptNext )
    return ptHead->ptNext->tConsoleID;
  else
    return -1;
}

// source: b/1/debugconsole.c:857  [size]
char *__cdecl DebugConsole_GetName()
{
  return DebugConsole_ptActiveDebugConsole->zName;
}

// source: b/1/debugconsole.c:875  [anchor-hash]
char *__cdecl DebugConsole_SetName(char *zName)
{
  int v1; // edx
  char v2; // cl

  v1 = DebugConsole_ptActiveDebugConsole->zName - zName;
  do
  {
    v2 = *zName;
    zName[v1] = *zName;
    ++zName;
  }
  while ( v2 );
  return zName;
}

// source: b/1/debugconsole.c:893  [size]
int __cdecl DebugConsole_GetLines()
{
  return DebugConsole_ptActiveDebugConsole->nLines;
}

// source: b/1/debugconsole.c:913  [anchor-caller]
int __cdecl DebugConsole_GetLineCString(char *zBuffer, unsigned int nBufferSize, int nLine)
{
  struct DebugConsoleLine_s *Line; // eax
  unsigned int i; // ecx

  Line = DebugConsole_GetLine(DebugConsole_ptActiveDebugConsole, nLine, false);
  if ( !Line || !nBufferSize )
    return 0;
  for ( i = 0; i < Line->tQString.nLength; ++i )
  {
    if ( i >= nBufferSize )
      break;
    zBuffer[i] = Line->tQString.tPrivate.patQStringChar[i];
  }
  return i;
}

// source: b/1/debugconsole.c:940  [anchor-callee]
enum bool __cdecl DebugConsole_IsConsoleIDValid(int tConsoleID)
{
  int v1; // edx
  struct DebugConsole_s *ptNext; // eax
  struct DebugConsole_s *ptHead; // ecx

  if ( DebugConsole_tConsoleList.ptHead == (struct DebugConsole_s *)&DebugConsole_tConsoleList.ptMiddle )
    return false;
  v1 = DebugConsole_tConsoleList.ptHead->tConsoleID;
  if ( v1 == -1 )
    return false;
  while ( v1 != tConsoleID )
  {
    ptNext = DebugConsole_tConsoleList.ptHead->ptNext;
    ptHead = DebugConsole_tConsoleList.ptHead;
    if ( DebugConsole_tConsoleList.ptHead->ptNext )
    {
      while ( ptHead->tConsoleID != v1 )
      {
        ptHead = ptNext;
        ptNext = ptNext->ptNext;
        if ( !ptNext )
          goto LABEL_7;
      }
    }
    else
    {
LABEL_7:
      ptHead = nullptr;
    }
    if ( ptHead->ptNext->ptNext )
    {
      v1 = ptHead->ptNext->tConsoleID;
      if ( v1 != -1 )
        continue;
    }
    return false;
  }
  return true;
}

// source: b/1/debugconsole.c:965  [anchor-mhash]
char *__cdecl DebugConsole_vprintf(char *zFormat, char *arg)
{
  void (__cdecl *pfDebugConsolePrintCallback)(char *, void *); // ecx
  struct DebugConsole_s *v3; // ebx
  char *result; // eax
  char zTemp[1024]; // [esp+4h] [ebp-400h] BYREF

  vsnprintf(zTemp, 0x400u, zFormat, arg);
  pfDebugConsolePrintCallback = DebugConsole_ptActiveDebugConsole->pfDebugConsolePrintCallback;
  v3 = DebugConsole_ptActiveDebugConsole;
  if ( pfDebugConsolePrintCallback )
    pfDebugConsolePrintCallback(zTemp, DebugConsole_ptActiveDebugConsole->pxPrintCallbackContext);
  result = (char *)v3->nMaxLines;
  if ( result )
    DebugConsole_ParseCString(v3, zTemp);
  return result;
}

// source: b/1/debugconsole.c:985  [anchor-callee]
void DebugConsole_printf(char *zFormat, ...)
{
  va_list arg; // [esp+8h] [ebp+8h] BYREF ARGSLOT

  va_start(arg, zFormat);
  DebugConsole_vprintf(zFormat, arg);
}

// source: b/1/debugconsole.c:1006  [size]
void __cdecl DebugConsole_RegisterPrintCallback(
        void (__cdecl *pfDebugConsolePrintCallback)(char *, void *),
        void *pxContext)
{
  struct DebugConsole_s *v2; // eax

  v2 = DebugConsole_ptActiveDebugConsole;
  DebugConsole_ptActiveDebugConsole->pfDebugConsolePrintCallback = pfDebugConsolePrintCallback;
  v2->pxPrintCallbackContext = pxContext;
}

// source: b/1/debugconsole.c:1024  [anchor-hash]
void __cdecl DebugConsole_RemovePrintCallback(
        void (__cdecl *pfDebugConsolePrintCallback)(char *, void *))
{
  DebugConsole_ptActiveDebugConsole->pfDebugConsolePrintCallback = nullptr;
}

// source: b/1/debugconsole.c:1041  [size]
int __cdecl DebugConsole_GetDefaultConsoleID()
{
  return DebugConsole_tDefaultConsoleID;
}

// source: b/1/debugconsole.c:1054  [anchor-hash]
void __cdecl DebugConsole_Open()
{
  DebugConsole_ptActiveDebugConsole = nullptr;
  DebugConsole_tConsoleList.ptMiddle = nullptr;
  DebugConsole_nAllocID = 1;
  DebugConsole_tConsoleList.ptHead = (struct DebugConsole_s *)&DebugConsole_tConsoleList.ptMiddle;
  DebugConsole_tConsoleList.ptTail = (struct DebugConsole_s *)&DebugConsole_tConsoleList;
  DebugConsole_tDefaultConsoleID = DebugConsole_Alloc("Default", 100);
  DebugConsole_PushActiveConsole(DebugConsole_tDefaultConsoleID);
}

// source: b/1/debugconsole.c:1072  [anchor-hash]
void __cdecl DebugConsole_Close()
{
  DebugConsole_PopActiveConsole();
  DebugConsole_DeAlloc(DebugConsole_tDefaultConsoleID);
}
