/* b/1/warninglog.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: b/1/warninglog.c:49  [anchor-caller]
char *__cdecl WarningLog_RegisterWarning(
        char *zWarning,
        enum bool isDisplayWarning)
{
  char *result; // eax
  struct QHashTable_s *v4; // esi
  unsigned int v5; // eax
  char *v6; // esi
  struct QHashTable_s *v7; // edi
  unsigned int v8; // eax
  bool v9; // zf

  result = (char *)WarningLog_ptHashTable;
  if ( WarningLog_ptHashTable && WarningLog_ptVector )
  {
    v4 = WarningLog_ptHashTable;
    v5 = WarningLog_ptHashTable->tPrivate.pfHashFunction(WarningLog_ptHashTable->tPrivate.nHashTableSize, zWarning);
    if ( !((int  (__cdecl *)(struct QHashTable_s *, unsigned int, const void *))WarningLog_ptHashTable->tPrivate.pfFindElement)(v4, v5, (const void *)(zWarning)) )
    {
      v6 = (char *)Mem_AllocFn(strlen(zWarning) + 1, 4);
      strcpy(v6, zWarning);
      QVector_AddElement(WarningLog_ptVector, v6);
      v7 = WarningLog_ptHashTable;
      v8 = WarningLog_ptHashTable->tPrivate.pfHashFunction(WarningLog_ptHashTable->tPrivate.nHashTableSize, v6);
      result = (char *)((int  (__cdecl *)(struct QHashTable_s *, unsigned int, const void *, const void *))WarningLog_ptHashTable->tPrivate.pfCreateElement)(v7, v8, (const void *)(v6), (const void *)(v6));
      if ( isDisplayWarning )
        return (char *)LDebug_Warning((char *)&stru_6A4CDC.tDebugConsoleLineList.ptMiddle, v6);
      return result;
    }
    result = (char *)WarningLog_isDisplayDuplicateWarnings;
    v9 = WarningLog_isDisplayDuplicateWarnings == false;
  }
  else
  {
    v9 = isDisplayWarning == false;
  }
  if ( !v9 )
    return (char *)LDebug_Warning((char *)&stru_6A4CDC.tDebugConsoleLineList.ptMiddle, zWarning);
  return result;
}

// source: b/1/warninglog.c:88  [anchor-caller]
void WarningLog_Warning(char *zFormat, ...)
{
  char Buffer[1024]; // [esp+4h] [ebp-400h] BYREF
  va_list ArgList; // [esp+40Ch] [ebp+8h] BYREF ARGSLOT

  va_start(ArgList, zFormat);
  vsprintf(Buffer, zFormat, ArgList);
  WarningLog_RegisterWarning(Buffer, true);
}

// source: b/1/warninglog.c:112  [size]
enum bool __cdecl WarningLog_DisplayDuplicateWarnings(
        enum bool isDisplayDuplicateWarnings)
{
  WarningLog_isDisplayDuplicateWarnings = isDisplayDuplicateWarnings;
  return isDisplayDuplicateWarnings;
}

// source: b/1/warninglog.c:125  [anchor-hash]
void __cdecl WarningLog_Open()
{
  struct QHashTable_s *v0; // esi
  void *v1; // edi
  unsigned int v2; // eax
  struct QVector_s *v3; // eax

  v0 = (struct QHashTable_s *)Mem_AllocFn(40, 4);
  v0->tPrivate.nHashTableSize = 1023;
  v0->tPrivate.pfHashFunction = QHashTable_StringHashFunction;
  v0->tPrivate.pfCompareKey = QHashTable_StringCompareKeyFunction;
  v0->tPrivate.pfDuplicateKey = nullptr;
  v0->tPrivate.pfCreateElement = QHashTable_CreateElementChained;
  v0->tPrivate.pfFindElement = QHashTable_FindElementChained;
  v0->tPrivate.pfDeleteElement = QHashTable_DeleteElementChained;
  v0->tPrivate.pfMap = QHashTable_MapChained;
  v0->tPrivate.nEntries = 0;
  v1 = Mem_AllocFn(12276, 4);
  v2 = 0;
  v0->tPrivate.papxElement = v1;
  memset(v1, 0, 0x2FF4u);
  do
  {
    *(_DWORD *)((char *)v0->tPrivate.papxElement + v2) = (char *)v0->tPrivate.papxElement + v2 + 4;
    *(_DWORD *)((char *)v0->tPrivate.papxElement + v2 + 8) = (char *)v0->tPrivate.papxElement + v2;
    *(_DWORD *)((char *)v0->tPrivate.papxElement + v2 + 4) = 0;
    *(_DWORD *)((char *)v0->tPrivate.papxElement + v2 + 12) = (char *)v0->tPrivate.papxElement + v2 + 16;
    *(_DWORD *)((char *)v0->tPrivate.papxElement + v2 + 20) = (char *)v0->tPrivate.papxElement + v2 + 12;
    *(_DWORD *)((char *)v0->tPrivate.papxElement + v2 + 16) = 0;
    *(_DWORD *)((char *)v0->tPrivate.papxElement + v2 + 24) = (char *)v0->tPrivate.papxElement + v2 + 28;
    *(_DWORD *)((char *)v0->tPrivate.papxElement + v2 + 32) = (char *)v0->tPrivate.papxElement + v2 + 24;
    *(_DWORD *)((char *)v0->tPrivate.papxElement + v2 + 28) = 0;
    v2 += 36;
  }
  while ( v2 < 0x2FF4 );
  WarningLog_ptHashTable = v0;
  v3 = (struct QVector_s *)Mem_AllocFn(24, 4);
  v3->tPrivate.nArraySize = 0;
  v3->tPrivate.nElements = 0;
  v3->tPrivate.isPrivateMem = false;
  v3->tPrivate.papxElement = nullptr;
  v3->tPrivate.nReallocSize = 32;
  v3->tPrivate.isStrictOrder = true;
  WarningLog_ptVector = v3;
}

// source: b/1/warninglog.c:139  [anchor-hash]
void __cdecl WarningLog_Close()
{
  struct File_s *v0; // esi
  struct QVector_s *v1; // eax
  unsigned int i; // ebp
  void **papxElement; // eax
  void *v4; // edi
  struct QHashTable_s *v5; // ebx
  unsigned int v6; // eax
  int v7; // ebx
  struct QHashTable_s *v8; // esi
  int v9; // esi

  v0 = File_New("warninglog.txt", "w");
  v1 = WarningLog_ptVector;
  for ( i = 0; i < WarningLog_ptVector->tPrivate.nElements; ++i )
  {
    papxElement = v1->tPrivate.papxElement;
    v4 = papxElement[i];
    if ( v0 )
    {
      File_atDevice[v0->eDeviceID].pfWrite(v0->eDeviceID, v0, papxElement[i], strlen((char *)papxElement[i]));
      File_atDevice[v0->eDeviceID].pfWrite(v0->eDeviceID, v0, "\r\n", 2u);
    }
    v5 = WarningLog_ptHashTable;
    v6 = WarningLog_ptHashTable->tPrivate.pfHashFunction(WarningLog_ptHashTable->tPrivate.nHashTableSize, v4);
    ((void  (__cdecl *)(struct QHashTable_s *, unsigned int, const void *))WarningLog_ptHashTable->tPrivate.pfDeleteElement)(v5, v6, (const void *)(v4));
    if ( v4 )
    {
      v7 = *(_DWORD *)(((int)v4 - 4) & 0xFFFFFFFC);
      --Mem_nCurrentAllocations;
      Node_Remove((_DWORD **)v7);
      memset(*(void **)(v7 + 8), 0xCDu, *(_DWORD *)(v7 + 16));
      free((void *)v7);
    }
    v1 = WarningLog_ptVector;
  }
  if ( v0 )
  {
    if ( v0 == &File_tDummyAsyncFile )
      File_tDummyAsyncFile.isAsync = false;
    else
      File_atDevice[v0->eDeviceID].pfDelete(v0->eDeviceID, v0);
  }
  v8 = WarningLog_ptHashTable;
  QHashTable_DeAlloc(WarningLog_ptHashTable);
  if ( v8 )
  {
    v9 = *(_DWORD *)((unsigned int)&v8[-1].tPrivate.pfMap & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v9);
    memset(*(void **)(v9 + 8), 0xCDu, *(_DWORD *)(v9 + 16));
    free((void *)v9);
  }
  QVector_Delete(WarningLog_ptVector);
  WarningLog_ptHashTable = nullptr;
  WarningLog_ptVector = nullptr;
}
