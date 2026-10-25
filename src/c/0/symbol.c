/* c/0/symbol.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: c/0/symbol.c:83  [anchor-hash]
void __cdecl Symbol_InvalidateSymbolReferences(struct ScriptSymbol_s *ptScriptSymbol)
{
  struct ScriptSymbolReference_s *ptHead; // ecx
  struct ScriptSymbolReference_s *i; // eax

  ptHead = Symbol_tAllocatedReferenceList.ptHead;
  for ( i = Symbol_tAllocatedReferenceList.ptHead->ptNext; i; i = i->ptNext )
  {
    if ( ptHead->ptScriptSymbol == ptScriptSymbol )
      ptHead->ptScriptSymbol = nullptr;
    ptHead = i;
  }
}

// source: c/0/symbol.c:154  [anchor-hash]
int __cdecl Symbol_AddReferenceBlock(int nReferences)
{
  int v1; // esi
  _DWORD *v2; // eax
  _DWORD *v3; // eax
  int result; // eax

  v1 = nReferences;
  v2 = Mem_AllocFn(4 * (3 * nReferences + 3), 4);
  v2[1] = 0;
  *v2 = 0;
  v3 = List_AddTail(v2, (int)&Symbol_tScriptSymbolReferenceBlockList);
  v3[2] = v3 + 3;
  result = (int)(v3 + 3);
  if ( v1 > 0 )
  {
    do
    {
      *(_DWORD *)(result + 4) = 0;
      *(_DWORD *)result = 0;
      result = (int)(List_AddTail((_DWORD *)result, (int)&Symbol_tFreeReferenceList) + 3);
      --v1;
    }
    while ( v1 );
  }
  return result;
}

// source: c/0/symbol.c:188  [size]
void __cdecl Symbol_RemoveReferenceBlock(struct ScriptSymbolReferenceBlock_s *ptBlock)
{
  _DWORD **v1; // eax
  int v2; // esi

  v1 = Node_Remove(ptBlock);
  if ( v1 )
  {
    v2 = *(_DWORD *)((unsigned int)(v1 - 1) & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v2);
    memset(*(void **)(v2 + 8), 0xCDu, *(_DWORD *)(v2 + 16));
    free((void *)v2);
  }
}

// source: c/0/symbol.c:213  [anchor-callee]
void __cdecl Symbol_Register(
        char *zName,
        struct Result_s *(__cdecl *pfSymbolParse__)(struct Result_s *retstr, void *, struct ArgList_s *),
        void *pxContext,
        int nSize,
        enum QScriptSymbolClass_e eClass,
        enum QScriptSymbolType_e eType,
        enum QScriptSymbolLifespan_e eLifespan)
{
  char *v7; // esi
  struct QHashTable_s *v8; // ecx
  struct QHashTable_s *v9; // edi
  int v10; // eax

  v7 = (char *)Mem_AllocFn(strlen(zName) + 29, 4);
  memset(v7, 0, 0x1Cu);
  strcpy(v7 + 28, zName);
  *((_DWORD *)v7 + 4) = pfSymbolParse__;
  *((_DWORD *)v7 + 6) = pxContext;
  *((_DWORD *)v7 + 3) = nSize;
  *(_DWORD *)v7 = eClass;
  *((_DWORD *)v7 + 1) = eType;
  v8 = Symbol_ptSymbolHashTable;
  *((_DWORD *)v7 + 5) = v7 + 28;
  *((_DWORD *)v7 + 2) = eLifespan;
  v9 = v8;
  v10 = v8->tPrivate.pfHashFunction(v8->tPrivate.nHashTableSize, v7 + 28);
  Symbol_ptSymbolHashTable->tPrivate.pfCreateElement(v9, v10, (const void *)(v7 + 28), (const void *)(v7));
  QVector_AddElement(Symbol_ptSymbolVector, v7);
}

// source: c/0/symbol.c:254  [size]
char *__cdecl Symbol_FindFunction(
        struct Result_s *(__cdecl *pfSymbolParse__)(struct Result_s *retstr, void *, struct ArgList_s *))
{
  char *result; // eax
  int v2; // ecx
  void **i; // edx

  result = nullptr;
  v2 = 0;
  if ( Symbol_ptSymbolVector->tPrivate.nElements )
  {
    for ( i = Symbol_ptSymbolVector->tPrivate.papxElement;
          *((struct Result_s *(__cdecl **)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))*i + 4) != pfSymbolParse__;
          ++i )
    {
      if ( ++v2 >= Symbol_ptSymbolVector->tPrivate.nElements )
        return result;
    }
    return *((char **)*i + 5);
  }
  return result;
}

// source: c/0/symbol.c:293  [size]
char *__cdecl Symbol_FindName(void *pxContext)
{
  char *result; // eax
  int v2; // ecx
  void **i; // edx

  result = nullptr;
  v2 = 0;
  if ( Symbol_ptSymbolVector->tPrivate.nElements )
  {
    for ( i = Symbol_ptSymbolVector->tPrivate.papxElement; *((void **)*i + 6) != pxContext; ++i )
    {
      if ( ++v2 >= Symbol_ptSymbolVector->tPrivate.nElements )
        return result;
    }
    return *((char **)*i + 5);
  }
  return result;
}

// source: c/0/symbol.c:331  [anchor-hash]
void __cdecl Symbol_Remove(char *zName)
{
  struct QHashTable_s *v2; // edi
  unsigned int v3; // eax
  int v4; // eax
  struct ScriptSymbol_s *v5; // ebx
  struct QHashTable_s *v6; // edi
  unsigned int v7; // eax
  struct QVector_s *v8; // edx
  unsigned int v9; // eax
  void **papxElement; // esi
  unsigned int v11; // edi
  enum bool isStrictOrder; // esi
  void **v13; // edx
  struct ScriptSymbolReference_s *ptHead; // ecx
  struct ScriptSymbolReference_s *i; // eax
  int v16; // esi

  v2 = Symbol_ptSymbolHashTable;
  v3 = Symbol_ptSymbolHashTable->tPrivate.pfHashFunction(Symbol_ptSymbolHashTable->tPrivate.nHashTableSize, zName);
  v4 = ((int  (__cdecl *)(struct QHashTable_s *, unsigned int, const void *))Symbol_ptSymbolHashTable->tPrivate.pfFindElement)(v2, v3, (const void *)(zName));
  v5 = (struct ScriptSymbol_s *)v4;
  if ( !v4 || !*(_DWORD *)(v4 + 20) )
  {
    LDebug_Error((char *)&stru_688EF4.isAsync, zName);
    abort();
  }
  v6 = Symbol_ptSymbolHashTable;
  v7 = Symbol_ptSymbolHashTable->tPrivate.pfHashFunction(Symbol_ptSymbolHashTable->tPrivate.nHashTableSize, zName);
  ((void  (__cdecl *)(struct QHashTable_s *, unsigned int, const void *))Symbol_ptSymbolHashTable->tPrivate.pfDeleteElement)(v6, v7, (const void *)(zName));
  v8 = Symbol_ptSymbolVector;
  v9 = 0;
  if ( Symbol_ptSymbolVector->tPrivate.nElements )
  {
    papxElement = Symbol_ptSymbolVector->tPrivate.papxElement;
    while ( *papxElement != v5 )
    {
      ++v9;
      ++papxElement;
      if ( v9 >= Symbol_ptSymbolVector->tPrivate.nElements )
        goto LABEL_12;
    }
    v11 = Symbol_ptSymbolVector->tPrivate.nElements - 1;
    Symbol_ptSymbolVector->tPrivate.nElements = v11;
    if ( v9 < v11 )
    {
      isStrictOrder = v8->tPrivate.isStrictOrder;
      v13 = v8->tPrivate.papxElement;
      if ( isStrictOrder )
        memmove(&v13[v9], &v13[v9 + 1], 4 * (v11 - v9));
      else
        v13[v9] = v13[v11];
    }
  }
LABEL_12:
  ptHead = Symbol_tAllocatedReferenceList.ptHead;
  for ( i = Symbol_tAllocatedReferenceList.ptHead->ptNext; i; i = i->ptNext )
  {
    if ( ptHead->ptScriptSymbol == v5 )
      ptHead->ptScriptSymbol = nullptr;
    ptHead = i;
  }
  v16 = *(_DWORD *)((unsigned int)&v5[-1].pxUserdata & 0xFFFFFFFC);
  --Mem_nCurrentAllocations;
  Node_Remove((_DWORD **)v16);
  memset(*(void **)(v16 + 8), 0xCDu, *(_DWORD *)(v16 + 16));
  free((void *)v16);
}

// source: c/0/symbol.c:371  [anchor-callee]
char *__cdecl Symbol_Find(char *zName, struct ScriptSymbol_s **pptScriptSymbol)
{
  char *zSymbolName; // edi
  struct QHashTable_s *v3; // esi
  int v4; // eax
  struct ScriptSymbol_s *v5; // eax

  zSymbolName = nullptr;
  v3 = Symbol_ptSymbolHashTable;
  v4 = Symbol_ptSymbolHashTable->tPrivate.pfHashFunction(Symbol_ptSymbolHashTable->tPrivate.nHashTableSize, zName);
  v5 = (struct ScriptSymbol_s *)((int  (__cdecl *)(struct QHashTable_s *, unsigned int, const void *))Symbol_ptSymbolHashTable->tPrivate.pfFindElement)(v3, v4, (const void *)(zName));
  if ( v5 )
    zSymbolName = v5->zSymbolName;
  if ( pptScriptSymbol )
    *pptScriptSymbol = v5;
  return zSymbolName;
}

// source: c/0/symbol.c:404  [anchor-mhash]
void __cdecl Script_EnumerateSymbols(
        void (__cdecl *pfCallback)(char *, void *, void *),
        void *pxContext)
{
  unsigned int nElements; // edi
  unsigned int i; // esi
  char **v4; // [esp-8h] [ebp-14h]

  nElements = Symbol_ptSymbolVector->tPrivate.nElements;
  for ( i = 0; i < nElements; ++i )
  {
    v4 = (char **)Symbol_ptSymbolVector->tPrivate.papxElement[i];
    pfCallback(v4[5], v4, pxContext);
  }
}

// source: c/0/symbol.c:435  [anchor-caller]
struct ScriptSymbolReference_s *__cdecl Symbol_NewReference(char *zSymbol)
{
  struct QHashTable_s *v1; // esi
  unsigned int v2; // eax
  int v3; // eax
  int v4; // ecx
  int v5; // esi
  _DWORD *v6; // eax
  struct ScriptSymbolReference_s *result; // eax
  unsigned int v8; // ecx

  v1 = Symbol_ptSymbolHashTable;
  v2 = Symbol_ptSymbolHashTable->tPrivate.pfHashFunction(Symbol_ptSymbolHashTable->tPrivate.nHashTableSize, zSymbol);
  v3 = ((int  (__cdecl *)(struct QHashTable_s *, unsigned int, const void *))Symbol_ptSymbolHashTable->tPrivate.pfFindElement)(v1, v2, (const void *)(zSymbol));
  v5 = v3;
  if ( !v3 || !*(_DWORD *)(v3 + 20) )
    return nullptr;
  if ( Symbol_tFreeReferenceList.ptHead == (struct ScriptSymbolReference_s *)&Symbol_tFreeReferenceList.ptMiddle )
    Symbol_AddReferenceBlock(1024);
  v6 = List_RemHead(v4, &Symbol_tFreeReferenceList);
  v6[2] = v5;
  result = (struct ScriptSymbolReference_s *)List_AddHead(v6, (int)&Symbol_tAllocatedReferenceList);
  v8 = ++Symbol_nReferencesUsed;
  if ( Symbol_nReferencesUsed > Symbol_nMaxReferencesUsed )
    Symbol_nMaxReferencesUsed = v8;
  return result;
}

// source: c/0/symbol.c:472  [anchor-callee]
struct ScriptSymbolReference_s *__cdecl Symbol_DeleteReference(
        struct ScriptSymbolReference_s *ptScriptSymbolReference)
{
  _DWORD *v1; // eax
  struct ScriptSymbolReference_s *result; // eax

  v1 = Node_Remove(ptScriptSymbolReference);
  result = (struct ScriptSymbolReference_s *)List_AddHead(v1, (int)&Symbol_tFreeReferenceList);
  --Symbol_nReferencesUsed;
  return result;
}

// source: c/0/symbol.c:490  [anchor-hash]
void __cdecl Symbol_Open()
{
  struct QHashTable_s *v0; // esi
  void *v1; // edi
  void **v2; // esi
  struct QVector_s *v3; // eax

  v0 = (struct QHashTable_s *)Mem_AllocFn(40, 4);
  v0->tPrivate.nHashTableSize = 4999;
  v0->tPrivate.pfHashFunction = QHashTable_StringHashFunction;
  v0->tPrivate.pfCompareKey = QHashTable_StringCompareKeyFunction;
  v0->tPrivate.pfDuplicateKey = nullptr;
  v0->tPrivate.pfCreateElement = QHashTable_CreateElementClosed;
  v0->tPrivate.pfFindElement = QHashTable_FindElementClosed;
  v0->tPrivate.pfDeleteElement = QHashTable_DeleteElementClosed;
  v0->tPrivate.pfMap = QHashTable_MapClosed;
  v0->tPrivate.nEntries = 0;
  v1 = Mem_AllocFn(39992, 4);
  v0->tPrivate.papxElement = v1;
  memset(v1, 0, 0x9C38u);
  Symbol_ptSymbolHashTable = v0;
  v2 = (void **)Mem_AllocFn(19996, 4);
  v3 = (struct QVector_s *)Mem_AllocFn(24, 4);
  v3->tPrivate.papxElement = v2;
  v3->tPrivate.nReallocSize = 0;
  v3->tPrivate.nElements = 0;
  v3->tPrivate.isPrivateMem = false;
  v3->tPrivate.isStrictOrder = false;
  v3->tPrivate.nArraySize = 4999;
  Symbol_nMaxReferencesUsed = 0;
  Symbol_nReferencesUsed = 0;
  Symbol_tScriptSymbolReferenceBlockList.ptMiddle = nullptr;
  Symbol_tFreeReferenceList.ptMiddle = nullptr;
  Symbol_tAllocatedReferenceList.ptMiddle = nullptr;
  Symbol_ptSymbolVector = v3;
  Symbol_tScriptSymbolReferenceBlockList.ptHead = (struct ScriptSymbolReferenceBlock_s *)&Symbol_tScriptSymbolReferenceBlockList.ptMiddle;
  Symbol_tScriptSymbolReferenceBlockList.ptTail = (struct ScriptSymbolReferenceBlock_s *)&Symbol_tScriptSymbolReferenceBlockList;
  Symbol_tFreeReferenceList.ptHead = (struct ScriptSymbolReference_s *)&Symbol_tFreeReferenceList.ptMiddle;
  Symbol_tFreeReferenceList.ptTail = (struct ScriptSymbolReference_s *)&Symbol_tFreeReferenceList;
  Symbol_tAllocatedReferenceList.ptHead = (struct ScriptSymbolReference_s *)&Symbol_tAllocatedReferenceList.ptMiddle;
  Symbol_tAllocatedReferenceList.ptTail = (struct ScriptSymbolReference_s *)&Symbol_tAllocatedReferenceList;
}

// source: c/0/symbol.c:513  [anchor-hash]
void __cdecl Symbol_Close()
{
  struct QHashTable_s *v0; // esi
  unsigned int nElements; // esi
  int v2; // esi
  struct ScriptSymbolReferenceBlock_s *ptHead; // eax
  struct ScriptSymbolReferenceBlock_s *i; // ebx
  _DWORD **v5; // eax
  int v6; // esi

  v0 = Symbol_ptSymbolHashTable;
  if ( Symbol_ptSymbolHashTable )
  {
    if ( (int)Symbol_ptSymbolVector->tPrivate.nElements > 0 )
    {
      nElements = Symbol_ptSymbolVector->tPrivate.nElements;
      do
      {
        Symbol_Remove(*((char **)*Symbol_ptSymbolVector->tPrivate.papxElement + 5));
        --nElements;
      }
      while ( nElements );
      v0 = Symbol_ptSymbolHashTable;
    }
    QHashTable_DeAlloc(v0);
    if ( v0 )
    {
      v2 = *(_DWORD *)((unsigned int)&v0[-1].tPrivate.pfMap & 0xFFFFFFFC);
      --Mem_nCurrentAllocations;
      Node_Remove((_DWORD **)v2);
      memset(*(void **)(v2 + 8), 0xCDu, *(_DWORD *)(v2 + 16));
      free((void *)v2);
    }
    QVector_Delete(Symbol_ptSymbolVector);
    Symbol_ptSymbolHashTable = nullptr;
    Symbol_ptSymbolVector = nullptr;
  }
  ptHead = Symbol_tScriptSymbolReferenceBlockList.ptHead;
  for ( i = Symbol_tScriptSymbolReferenceBlockList.ptHead->ptNext; i; i = i->ptNext )
  {
    v5 = Node_Remove(ptHead);
    if ( v5 )
    {
      v6 = *(_DWORD *)((unsigned int)(v5 - 1) & 0xFFFFFFFC);
      --Mem_nCurrentAllocations;
      Node_Remove((_DWORD **)v6);
      memset(*(void **)(v6 + 8), 0xCDu, *(_DWORD *)(v6 + 16));
      free((void *)v6);
    }
    ptHead = i;
  }
}
