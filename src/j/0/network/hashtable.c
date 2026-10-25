/* j/0/network/hashtable.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/network/hashtable.c:50  [anchor-caller]
struct HashImplementation *__cdecl TableNew(
        int elemSize,
        int nBuckets,
        int (__cdecl *hashFn)(void *, int),
        int (__cdecl *compFn)(void *, void *),
        void (__cdecl *freeFn)(void *))
{
  return TableNew2(elemSize, nBuckets, 4, hashFn, compFn, freeFn);
}

// source: j/0/network/hashtable.c:56  [anchor-callee]
struct HashImplementation *__cdecl TableNew2(
        int elemSize,
        int nBuckets,
        int nChains,
        int (__cdecl *hashFn)(void *, int),
        int (__cdecl *compFn)(void *, void *),
        void (__cdecl *freeFn)(void *))
{
  int v6; // esi
  struct HashImplementation *v7; // ebx
  int v8; // ebp
  int v9; // edi
  struct DArrayImplementation *v10; // esi

  v6 = nBuckets;
  v7 = (struct HashImplementation *)malloc(0x14u);
  v8 = 0;
  v7->buckets = (struct DArrayImplementation **)malloc(4 * nBuckets);
  if ( nBuckets > 0 )
  {
    do
    {
      v9 = nChains;
      v10 = (struct DArrayImplementation *)malloc(0x18u);
      if ( !nChains )
        v9 = 8;
      v10->capacity = v9;
      v10->growby = v9;
      v10->count = 0;
      v10->elemsize = elemSize;
      v10->elemfreefn = freeFn;
      v10->list = malloc(elemSize * v9);
      v7->buckets[v8++] = v10;
    }
    while ( v8 < nBuckets );
    v6 = nBuckets;
  }
  v7->nbuckets = v6;
  v7->freefn = freeFn;
  v7->compfn = compFn;
  v7->hashfn = hashFn;
  return v7;
}

// source: j/0/network/hashtable.c:82  [anchor-hash]
void __cdecl TableFree(struct HashImplementation *table)
{
  int i; // edi

  for ( i = 0; i < table->nbuckets; ++i )
    ArrayFree(table->buckets[i]);
  free(table->buckets);
  free(table);
}

// source: j/0/network/hashtable.c:95  [anchor-mhash]
int __cdecl TableCount(struct HashImplementation *table)
{
  int nbuckets; // edx
  int result; // eax
  struct DArrayImplementation **buckets; // ecx

  nbuckets = table->nbuckets;
  result = 0;
  if ( nbuckets > 0 )
  {
    buckets = table->buckets;
    do
    {
      result += (*buckets++)->count;
      --nbuckets;
    }
    while ( nbuckets );
  }
  return result;
}

// source: j/0/network/hashtable.c:106  [anchor-callee]
void __cdecl TableEnter(struct HashImplementation *table, void *newElem)
{
  void *v2; // ebx
  int v3; // esi
  struct DArrayImplementation *v4; // edi
  void *v5; // eax
  int v6; // ebx
  struct DArrayImplementation *v7; // ebp
  void (__cdecl *elemfreefn)(void *); // eax

  v2 = newElem;
  v3 = table->hashfn(newElem, table->nbuckets);
  v4 = table->buckets[v3];
  if ( !v4 || !v4->count )
    goto LABEL_6;
  v5 = mylsearch(newElem, v4->list, v4->count, v4->elemsize, table->compfn);
  if ( !v5 || (v6 = (signed int)((int)v5 - (unsigned int)v4->list) / v4->elemsize, v6 == -1) )
  {
    v2 = newElem;
LABEL_6:
    ArrayInsertAt(table->buckets[v3], v2, table->buckets[v3]->count);
    return;
  }
  v7 = table->buckets[v3];
  elemfreefn = v7->elemfreefn;
  if ( elemfreefn )
    elemfreefn((char *)v7->list + v6 * v7->elemsize);
  qmemcpy((char *)v7->list + v6 * v7->elemsize, newElem, v7->elemsize);
}

// source: j/0/network/hashtable.c:118  [anchor-caller]
int __cdecl TableRemove(struct HashImplementation *table, void *delElem)
{
  int v3; // eax
  struct DArrayImplementation *v4; // esi
  void *v5; // eax
  int v6; // eax
  int hash; // [esp+10h] [ebp-4h]

  v3 = table->hashfn(delElem, table->nbuckets);
  v4 = table->buckets[v3];
  hash = v3;
  if ( !v4 )
    return 0;
  if ( !v4->count )
    return 0;
  v5 = mylsearch(delElem, v4->list, v4->count, v4->elemsize, table->compfn);
  if ( !v5 )
    return 0;
  v6 = (signed int)((int)v5 - (unsigned int)v4->list) / v4->elemsize;
  if ( v6 == -1 )
    return 0;
  ArrayDeleteAt(table->buckets[hash], v6);
  return 1;
}

// source: j/0/network/hashtable.c:131  [anchor-callee]
void *__cdecl TableLookup(struct HashImplementation *table, void *elemKey)
{
  int v2; // eax
  struct DArrayImplementation *v3; // esi
  void *v4; // eax
  int v5; // eax
  int hash; // [esp+Ch] [ebp-4h]

  v2 = table->hashfn(elemKey, table->nbuckets);
  v3 = table->buckets[v2];
  hash = v2;
  if ( v3
    && v3->count
    && (v4 = mylsearch(elemKey, v3->list, v3->count, v3->elemsize, table->compfn)) != nullptr
    && (v5 = (signed int)((int)v4 - (unsigned int)v3->list) / v3->elemsize, v5 != -1) )
  {
    return (char *)table->buckets[hash]->list + v5 * table->buckets[hash]->elemsize;
  }
  else
  {
    return nullptr;
  }
}

// source: j/0/network/hashtable.c:145  [anchor-mhash]
void __cdecl TableMap(struct HashImplementation *table, void (__cdecl *fn)(void *, void *), void *clientData)
{
  int i; // ebx
  struct DArrayImplementation *v4; // esi
  int j; // edi

  for ( i = 0; i < table->nbuckets; ++i )
  {
    v4 = table->buckets[i];
    for ( j = 0; j < v4->count; ++j )
      fn((char *)v4->list + j * v4->elemsize, clientData);
  }
}

// source: j/0/network/hashtable.c:156  [anchor-mhash]
void __cdecl TableMapSafe(struct HashImplementation *table, void (__cdecl *fn)(void *, void *), void *clientData)
{
  struct HashImplementation *v3; // eax
  int i; // ebx
  struct DArrayImplementation *v5; // edi
  int v6; // esi

  v3 = table;
  for ( i = 0; i < v3->nbuckets; ++i )
  {
    v5 = v3->buckets[i];
    v6 = v5->count - 1;
    if ( v6 >= 0 )
    {
      do
      {
        fn((char *)v5->list + v6 * v5->elemsize, clientData);
        --v6;
      }
      while ( v6 >= 0 );
      v3 = table;
    }
  }
}

// source: j/0/network/hashtable.c:167  [anchor-mhash]
void *__cdecl TableMap2(struct HashImplementation *table, int (__cdecl *fn)(void *, void *), void *clientData)
{
  struct HashImplementation *v3; // eax
  int v4; // ebp
  struct DArrayImplementation *v5; // edi
  int v6; // ebx
  char *v7; // esi

  v3 = table;
  v4 = 0;
  if ( table->nbuckets <= 0 )
    return nullptr;
  while ( 1 )
  {
    v5 = v3->buckets[v4];
    v6 = 0;
    if ( v5->count > 0 )
    {
      while ( 1 )
      {
        v7 = (char *)v5->list + v6 * v5->elemsize;
        if ( !fn(v7, clientData) )
          break;
        if ( ++v6 >= v5->count )
          goto LABEL_7;
      }
      if ( v7 )
        return v7;
    }
LABEL_7:
    v3 = table;
    if ( ++v4 >= table->nbuckets )
      return nullptr;
  }
}

// source: j/0/network/hashtable.c:184  [anchor-hash]
void __cdecl TableClear(struct HashImplementation *table)
{
  int i; // edi

  for ( i = 0; i < table->nbuckets; ++i )
    ArrayClear(table->buckets[i]);
}
