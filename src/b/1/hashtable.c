/* b/1/hashtable.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: b/1/hashtable.c:81  [anchor-mhash]
void __cdecl QHashTable_CreateElementChained(
        struct QHashTable_s *ptHashTable,
        unsigned int nHashValue,
        void *pxKey,
        void *pxValue)
{
  char *v4; // ebx
  _DWORD *v5; // esi
  void *(__cdecl *pfDuplicateKey)(void *); // eax

  v4 = (char *)ptHashTable->tPrivate.papxElement + 12 * nHashValue;
  v5 = Mem_AllocFn(16, 4);
  v5[1] = 0;
  *v5 = 0;
  List_AddTail(v5, (int)v4);
  pfDuplicateKey = ptHashTable->tPrivate.pfDuplicateKey;
  if ( pfDuplicateKey )
    v5[2] = pfDuplicateKey(pxKey);
  else
    v5[2] = pxKey;
  v5[3] = pxValue;
  ++ptHashTable->tPrivate.nEntries;
}

// source: b/1/hashtable.c:109  [anchor-mhash]
void *__cdecl QHashTable_FindElementChained(
        struct QHashTable_s *ptHashTable,
        unsigned int nHashValue,
        void *pxKey)
{
  _DWORD *v3; // edi
  _DWORD *v4; // esi

  v3 = *((_DWORD **)ptHashTable->tPrivate.papxElement + 3 * nHashValue);
  v4 = (_DWORD *)*v3;
  if ( !*v3 )
    return nullptr;
  while ( ptHashTable->tPrivate.pfCompareKey((void *)v3[2], pxKey) )
  {
    v3 = v4;
    v4 = (_DWORD *)*v4;
    if ( !v4 )
      return nullptr;
  }
  return (void *)v3[3];
}

// source: b/1/hashtable.c:140  [anchor-mhash]
void __cdecl QHashTable_DeleteElementChained(
        struct QHashTable_s *ptHashTable,
        unsigned int nHashValue,
        void *pxKey)
{
  _DWORD *v3; // esi
  _DWORD *v4; // edi
  int v5; // eax
  int v6; // ebx
  int v7; // esi

  v3 = *((_DWORD **)ptHashTable->tPrivate.papxElement + 3 * nHashValue);
  v4 = (_DWORD *)*v3;
  if ( *v3 )
  {
    while ( ptHashTable->tPrivate.pfCompareKey((void *)v3[2], pxKey) )
    {
      v3 = v4;
      v4 = (_DWORD *)*v4;
      if ( !v4 )
        return;
    }
    Node_Remove((_DWORD **)v3);
    if ( ptHashTable->tPrivate.pfDuplicateKey )
    {
      v5 = v3[2];
      if ( v5 )
      {
        --Mem_nCurrentAllocations;
        v6 = *(_DWORD *)((v5 - 4) & 0xFFFFFFFC);
        Node_Remove((_DWORD **)v6);
        memset(*(void **)(v6 + 8), 0xCDu, *(_DWORD *)(v6 + 16));
        free((void *)v6);
      }
      v3[2] = 0;
    }
    v7 = *(_DWORD *)((unsigned int)(v3 - 1) & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v7);
    memset(*(void **)(v7 + 8), 0xCDu, *(_DWORD *)(v7 + 16));
    free((void *)v7);
    --ptHashTable->tPrivate.nEntries;
  }
}

// source: b/1/hashtable.c:174  [anchor-mhash]
void __cdecl QHashTable_MapChained(
        struct QHashTable_s *ptHashTable,
        void (__cdecl *pfElementCallback)(struct QHashTable_s *, void *, void *, void *),
        void *pxContext)
{
  _DWORD *v4; // eax
  _DWORD *v5; // esi
  bool v6; // cf
  unsigned int i; // [esp+4h] [ebp-4h]
  struct QHashTable_s *ptHashTablea = *(struct QHashTable_s * *)&ptHashTable; // [esp+Ch] [ebp+4h] ARGSLOT

  i = 0;
  if ( ptHashTable->tPrivate.nHashTableSize )
  {
    ptHashTablea = nullptr;
    do
    {
      v4 = *(_DWORD **)((char *)&ptHashTablea->tPrivate.nEntries + (unsigned int)ptHashTable->tPrivate.papxElement);
      v5 = (_DWORD *)*v4;
      if ( *v4 )
      {
        do
        {
          pfElementCallback(ptHashTable, (void *)v4[2], (void *)v4[3], pxContext);
          v4 = v5;
          v5 = (_DWORD *)*v5;
        }
        while ( v5 );
      }
      v6 = ++i < ptHashTable->tPrivate.nHashTableSize;
      ptHashTablea = (struct QHashTable_s *)((char *)ptHashTablea + 12);
    }
    while ( v6 );
  }
}

// source: b/1/hashtable.c:213  [anchor-mhash]
void __cdecl QHashTable_CreateElementClosed(
        struct QHashTable_s *ptHashTable,
        unsigned int nHashValue,
        void *pxKey,
        void *pxValue)
{
  unsigned int v4; // eax
  char *i; // esi
  void *(__cdecl *pfDuplicateKey)(void *); // eax

  v4 = nHashValue;
  for ( i = (char *)ptHashTable->tPrivate.papxElement + 8 * nHashValue;
        *(_DWORD *)i;
        i = (char *)ptHashTable->tPrivate.papxElement + 8 * v4 )
  {
    if ( *(_DWORD *)i == -1 )
      break;
    if ( ++v4 >= ptHashTable->tPrivate.nHashTableSize )
      v4 = 0;
  }
  pfDuplicateKey = ptHashTable->tPrivate.pfDuplicateKey;
  if ( pfDuplicateKey )
    *(_DWORD *)i = pfDuplicateKey(pxKey);
  else
    *(_DWORD *)i = pxKey;
  *((_DWORD *)i + 1) = pxValue;
  ++ptHashTable->tPrivate.nEntries;
}

// source: b/1/hashtable.c:254  [anchor-mhash]
void *__cdecl QHashTable_FindElementClosed(
        struct QHashTable_s *ptHashTable,
        unsigned int nHashValue,
        void *pxKey)
{
  unsigned int v3; // edi
  char *v4; // esi
  void *v5; // eax
  _DWORD *papxElement; // ecx

  v3 = nHashValue;
  v4 = (char *)ptHashTable->tPrivate.papxElement + 8 * nHashValue;
  v5 = *(void **)v4;
  if ( !*(_DWORD *)v4 )
    return nullptr;
  while ( v5 == (void *)-1 || ptHashTable->tPrivate.pfCompareKey(v5, pxKey) )
  {
    if ( ++v3 >= ptHashTable->tPrivate.nHashTableSize )
      v3 = 0;
    papxElement = ptHashTable->tPrivate.papxElement;
    v5 = (void *)papxElement[2 * v3];
    v4 = (char *)&papxElement[2 * v3];
    if ( !v5 )
      return nullptr;
  }
  return *((void **)v4 + 1);
}

// source: b/1/hashtable.c:301  [anchor-mhash]
void __cdecl QHashTable_DeleteElementClosed(
        struct QHashTable_s *ptHashTable,
        unsigned int nHashValue,
        void *pxKey)
{
  char *v4; // esi
  _DWORD ***v5; // eax
  int v6; // ebp

  while ( 1 )
  {
    v4 = (char *)ptHashTable->tPrivate.papxElement + 8 * nHashValue;
    if ( *(_DWORD *)v4 != -1 && !ptHashTable->tPrivate.pfCompareKey(*(void **)v4, pxKey) )
      break;
    if ( ++nHashValue >= ptHashTable->tPrivate.nHashTableSize )
      nHashValue = 0;
  }
  if ( ptHashTable->tPrivate.pfDuplicateKey )
  {
    if ( *(_DWORD *)v4 )
    {
      v5 = (_DWORD ***)((*(_DWORD *)v4 - 4) & 0xFFFFFFFC);
      --Mem_nCurrentAllocations;
      v6 = (int)*v5;
      Node_Remove(*v5);
      memset(*(void **)(v6 + 8), 0xCDu, *(_DWORD *)(v6 + 16));
      free((void *)v6);
    }
    *(_DWORD *)v4 = 0;
  }
  *(_DWORD *)v4 = -1;
  *((_DWORD *)v4 + 1) = 0;
  --ptHashTable->tPrivate.nEntries;
}

// source: b/1/hashtable.c:342  [anchor-mhash]
void __cdecl QHashTable_MapClosed(
        struct QHashTable_s *ptHashTable,
        void (__cdecl *pfElementCallback)(struct QHashTable_s *, void *, void *, void *),
        void *pxContext)
{
  unsigned int i; // edi
  _DWORD *papxElement; // eax
  void *v5; // ecx
  void **v6; // eax

  for ( i = 0; i < ptHashTable->tPrivate.nHashTableSize; ++i )
  {
    papxElement = ptHashTable->tPrivate.papxElement;
    v5 = (void *)papxElement[2 * i + 1];
    v6 = (void **)&papxElement[2 * i];
    if ( v5 )
      pfElementCallback(ptHashTable, *v6, v5, pxContext);
  }
}

// source: b/1/hashtable.c:373  [anchor-mhash]
void __cdecl QHashTable_DeleteElementCallback(
        struct QHashTable_s *ptHashTable,
        void *pxKey,
        void *pxValue,
        void *pxContext)
{
  unsigned int v4; // eax

  v4 = ptHashTable->tPrivate.pfHashFunction(ptHashTable->tPrivate.nHashTableSize, pxKey);
  ((void  (__cdecl *)(struct QHashTable_s *, unsigned int, const void *))ptHashTable->tPrivate.pfDeleteElement)(ptHashTable, v4, (const void *)(pxKey));
}

// source: b/1/hashtable.c:394  [anchor-mhash]
void __cdecl QHashTable_Alloc(
        struct QHashTable_s *ptHashTable,
        unsigned int (__cdecl *pfHashFunction)(unsigned int, void *),
        int (__cdecl *pfCompareKey)(void *, void *),
        void *(__cdecl *pfDuplicateKey)(void *),
        enum bool isChained,
        unsigned int nHashTableSize)
{
  void (__cdecl *v6)(struct QHashTable_s *, unsigned int, void *, void *); // eax
  void *(__cdecl *v7)(struct QHashTable_s *, unsigned int, void *); // eax
  void (__cdecl *v8)(struct QHashTable_s *, unsigned int, void *); // eax
  void (__cdecl *v9)(struct QHashTable_s *, void (__cdecl *)(struct QHashTable_s *, void *, void *, void *), void *); // eax
  unsigned int v10; // ebx
  void *v11; // eax
  unsigned int v12; // edx
  int v13; // eax

  ptHashTable->tPrivate.pfHashFunction = pfHashFunction;
  ptHashTable->tPrivate.pfDuplicateKey = pfDuplicateKey;
  ptHashTable->tPrivate.nHashTableSize = nHashTableSize;
  ptHashTable->tPrivate.pfCompareKey = pfCompareKey;
  v6 = QHashTable_CreateElementChained;
  if ( isChained == false )
    v6 = QHashTable_CreateElementClosed;
  ptHashTable->tPrivate.pfCreateElement = v6;
  v7 = QHashTable_FindElementChained;
  if ( isChained == false )
    v7 = QHashTable_FindElementClosed;
  ptHashTable->tPrivate.pfFindElement = v7;
  v8 = QHashTable_DeleteElementChained;
  if ( isChained == false )
    v8 = QHashTable_DeleteElementClosed;
  ptHashTable->tPrivate.pfDeleteElement = v8;
  v9 = QHashTable_MapChained;
  if ( isChained == false )
    v9 = QHashTable_MapClosed;
  v10 = nHashTableSize * (4 * (isChained != false) + 8);
  ptHashTable->tPrivate.pfMap = v9;
  ptHashTable->tPrivate.nEntries = 0;
  v11 = Mem_AllocFn(v10, 4);
  ptHashTable->tPrivate.papxElement = v11;
  memset(v11, 0, v10);
  if ( isChained )
  {
    v12 = nHashTableSize;
    if ( nHashTableSize )
    {
      v13 = 0;
      do
      {
        *(_DWORD *)((char *)ptHashTable->tPrivate.papxElement + v13) = (char *)ptHashTable->tPrivate.papxElement
                                                                     + v13
                                                                     + 4;
        *(_DWORD *)((char *)ptHashTable->tPrivate.papxElement + v13 + 8) = (char *)ptHashTable->tPrivate.papxElement
                                                                         + v13;
        *(_DWORD *)((char *)ptHashTable->tPrivate.papxElement + v13 + 4) = 0;
        v13 += 12;
        --v12;
      }
      while ( v12 );
    }
  }
}

// source: b/1/hashtable.c:436  [anchor-callee]
void __cdecl QHashTable_DeAlloc(struct QHashTable_s *ptHashTable)
{
  void *papxElement; // eax
  int v2; // esi

  if ( ptHashTable->tPrivate.nEntries )
    ptHashTable->tPrivate.pfMap(ptHashTable, QHashTable_DeleteElementCallback, nullptr);
  papxElement = ptHashTable->tPrivate.papxElement;
  if ( papxElement )
  {
    v2 = *(_DWORD *)(((int)papxElement - 4) & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v2);
    memset(*(void **)(v2 + 8), 0xCDu, *(_DWORD *)(v2 + 16));
    free((void *)v2);
  }
  ptHashTable->tPrivate.papxElement = nullptr;
}

// source: b/1/hashtable.c:456  [size]
unsigned int __cdecl QHashTable_CaseInsensitiveStringHashFunction(unsigned int nHashTableSize, void *pxKey)
{
  char *v2; // edi
  char v3; // al
  unsigned int i; // esi
  unsigned int v5; // et2

  v2 = (char *)pxKey;
  v3 = *(_BYTE *)pxKey;
  for ( i = 0; *v2; i = v5 )
  {
    ++v2;
    v5 = 26099587 * (i + tolower(v3)) % nHashTableSize;
    v3 = *v2;
  }
  return i;
}

// source: b/1/hashtable.c:484  [anchor-mhash]
unsigned int __cdecl QHashTable_StringHashFunction(unsigned int nHashTableSize, void *pxKey)
{
  char *v2; // esi
  char v3; // cl
  unsigned int result; // eax
  unsigned int v5; // edx

  v2 = (char *)pxKey;
  v3 = *(_BYTE *)pxKey;
  for ( result = 0; v3; result = v5 )
  {
    v5 = 26099587 * (v3 + result) % nHashTableSize;
    v3 = *++v2;
  }
  return result;
}

// source: b/1/hashtable.c:512  [anchor-mhash]
unsigned int __cdecl QHashTable_FastStringHashFunction(unsigned int nHashTableSize, void *pxKey)
{
  char v2; // cl
  unsigned int i; // eax
  unsigned int v4; // eax

  v2 = *(_BYTE *)pxKey;
  for ( i = 0; v2; pxKey = (char *)pxKey + 1 )
  {
    v4 = v2 + i;
    v2 = *((_BYTE *)pxKey + 1);
    i = 31 * v4;
  }
  return i % nHashTableSize;
}

// source: b/1/hashtable.c:537  [size]
// attributes: thunk
int __cdecl QHashTable_CaseInsensitiveStringCompareKeyFunction(void *pxKey1, void *pxKey2)
{
  return _stricmp((char *)pxKey1, (char *)pxKey2);
}

// source: b/1/hashtable.c:553  [anchor-mhash]
int __cdecl QHashTable_StringCompareKeyFunction(void *pxKey1, void *pxKey2)
{
  return strcmp((char *)pxKey1, (char *)pxKey2);
}

// source: b/1/hashtable.c:569  [anchor-mhash]
void *__cdecl QHashTable_StringDuplicateKeyFunction(void *pxKey)
{
  void *result; // eax

  result = Mem_AllocFn(strlen((char *)pxKey) + 1, 4);
  strcpy((char *)result, (char *)pxKey);
  return result;
}

// source: b/1/hashtable.c:592  [anchor-mhash]
struct QHashTable_s *__cdecl QHashTable_NewEx(
        unsigned int nHashTableSize,
        unsigned int (__cdecl *pfHashFunction)(unsigned int, void *),
        int (__cdecl *pfCompareKey)(void *, void *),
        void *(__cdecl *pfDuplicateKey)(void *),
        enum bool isChained)
{
  struct QHashTable_s *v5; // esi

  v5 = (struct QHashTable_s *)Mem_AllocFn(40, 4);
  QHashTable_Alloc(v5, pfHashFunction, pfCompareKey, pfDuplicateKey, isChained, nHashTableSize);
  return v5;
}

// source: b/1/hashtable.c:618  [anchor-mhash]
struct QHashTable_s *__cdecl QHashTable_New(
        unsigned int nHashTableSize,
        enum bool isDuplicateKeys,
        enum bool isChained)
{
  struct QHashTable_s *v4; // esi

  v4 = (struct QHashTable_s *)Mem_AllocFn(40, 4);
  QHashTable_Alloc(
    v4,
    QHashTable_StringHashFunction,
    QHashTable_StringCompareKeyFunction,
    isDuplicateKeys != false ? QHashTable_StringDuplicateKeyFunction : nullptr,
    isChained,
    nHashTableSize);
  return v4;
}

// source: b/1/hashtable.c:636  [anchor-callee]
void __cdecl QHashTable_Delete(struct QHashTable_s *ptHashTable)
{
  int v2; // esi

  QHashTable_DeAlloc(ptHashTable);
  if ( ptHashTable )
  {
    v2 = *(_DWORD *)((unsigned int)&ptHashTable[-1].tPrivate.pfMap & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v2);
    memset(*(void **)(v2 + 8), 0xCDu, *(_DWORD *)(v2 + 16));
    free((void *)v2);
  }
}

// source: b/1/hashtable.c:652  [anchor-hash]
void *__cdecl QHashTable_GetElement(struct QHashTable_s *ptHashTable, void *pxKey)
{
  unsigned int v2; // eax

  v2 = ptHashTable->tPrivate.pfHashFunction(ptHashTable->tPrivate.nHashTableSize, pxKey);
  return ((void * (__cdecl *)(struct QHashTable_s *, unsigned int, const void *))ptHashTable->tPrivate.pfFindElement)(ptHashTable, v2, (const void *)(pxKey));
}

// source: b/1/hashtable.c:672  [anchor-mhash]
void *__cdecl QHashTable_AddElement(
        struct QHashTable_s *ptHashTable,
        void *pxKey,
        void *pxValue)
{
  unsigned int v3; // eax

  v3 = ptHashTable->tPrivate.pfHashFunction(ptHashTable->tPrivate.nHashTableSize, pxKey);
  return ((void *(__cdecl *)(struct QHashTable_s *, unsigned int))ptHashTable->tPrivate.pfCreateElement)(
           ptHashTable,
           v3);
}

// source: b/1/hashtable.c:693  [anchor-hash]
void *__cdecl QHashTable_RemoveElement(struct QHashTable_s *ptHashTable, void *pxKey)
{
  unsigned int v2; // eax

  v2 = ptHashTable->tPrivate.pfHashFunction(ptHashTable->tPrivate.nHashTableSize, pxKey);
  return ((void * (__cdecl *)(struct QHashTable_s *, unsigned int, const void *))ptHashTable->tPrivate.pfDeleteElement)(ptHashTable, v2, (const void *)(pxKey));
}

// source: b/1/hashtable.c:716  [anchor-mhash]
struct QHashTable_s *__cdecl QHashTable_Map(
        struct QHashTable_s *ptHashTable,
        void (__cdecl *pfElementCallback)(struct QHashTable_s *, void *, void *, void *),
        void *pxContext)
{
  if ( ptHashTable->tPrivate.nEntries )
    return ((struct QHashTable_s *(__cdecl *)(struct QHashTable_s *, void (__cdecl *)(struct QHashTable_s *, void *, void *, void *), void *))ptHashTable->tPrivate.pfMap)(
             ptHashTable,
             pfElementCallback,
             pxContext);
  return ptHashTable;
}

// source: b/1/hashtable.c:736  [anchor-hash]
struct QHashTable_s *__cdecl QHashTable_Empty(struct QHashTable_s *ptHashTable)
{
  if ( ptHashTable->tPrivate.nEntries )
    return ((struct QHashTable_s *(__cdecl *)(struct QHashTable_s *, void (__cdecl *)(struct QHashTable_s *, void *, void *, void *), _DWORD))ptHashTable->tPrivate.pfMap)(
             ptHashTable,
             QHashTable_DeleteElementCallback,
             0);
  return ptHashTable;
}

int (*LDebug_Error(char *Format, ...))()
{
  int (*result)(); // eax
  va_list ArgList; // [esp+8h] [ebp+8h] BYREF ARGSLOT

  va_start(ArgList, Format);
  if ( dword_73D218 )
  {
    sprintf(byte_84B7C80, "Fatal error:\n\n");
    vsprintf(&byte_84B7C80[strlen(byte_84B7C80)], Format, ArgList);
    dword_73D218(byte_84B7C80);
  }
  result = (int (*)())dword_73D210;
  if ( dword_73D210 )
    return dword_73D210();
  return result;
}

int (__cdecl *LDebug_Warning(char *Format, ...))(_DWORD)
{
  int (__cdecl *result)(_DWORD); // eax
  va_list ArgList; // [esp+8h] [ebp+8h] BYREF ARGSLOT

  va_start(ArgList, Format);
  result = (int (__cdecl *)(_DWORD))dword_73D220;
  if ( dword_73D220 )
  {
    sprintf(byte_84B7C80, "Warning:\n\n");
    vsprintf(&byte_84B7C80[strlen(byte_84B7C80)], Format, ArgList);
    return dword_73D220(byte_84B7C80);
  }
  return result;
}

void __cdecl LDebug_SetPrint(void (__cdecl *pfPrint)(char *))
{
  dword_73D218 = (int)pfPrint;
}

void __cdecl LDebug_SetLog(void (__cdecl *pfLog)(char *))
{
  dword_73D208 = (int)pfLog;
}

void __cdecl LDebug_SetWarning(void (__cdecl *pfWarning)(char *))
{
  dword_73D220 = (int)pfWarning;
}

void __cdecl LDebug_SetMessage(void (__cdecl *pfMessage)(char *))
{
  dword_73D204 = (int)pfMessage;
}

void __cdecl LDebug_SetAbort(void (__cdecl *pfAbort)())
{
  dword_73D210 = (int)pfAbort;
}

int __cdecl LDebug_EnableLogging(int result)
{
  dword_73D21C = result;
  return result;
}

char *LDebug_GetTextBuffer()
{
  return byte_84B7C80;
}

int LDebug_GetAbort()
{
  return dword_73D210;
}

int LDebug_Open()
{
  dword_73D218 = 0;
  dword_73D210 = 0;
  dword_73D208 = 0;
  dword_73D220 = 0;
  dword_73D204 = 0;
  dword_73D21C = 0;
  return 0;
}

void nullsub_229()
{
  ;
}
