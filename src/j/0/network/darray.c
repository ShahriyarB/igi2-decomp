/* j/0/network/darray.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/network/darray.c:57  [anchor-mhash]
struct DArrayImplementation *__cdecl FreeElement(
        struct DArrayImplementation *array,
        int n)
{
  void (__cdecl *elemfreefn)(void *); // ecx

  elemfreefn = array->elemfreefn;
  if ( elemfreefn )
    return ((struct DArrayImplementation *(__cdecl *)(char *))elemfreefn)((char *)array->list + n * array->elemsize);
  return array;
}

// source: j/0/network/darray.c:66  [anchor-hash]
void __cdecl ArrayGrow(struct DArrayImplementation *array)
{
  void *list; // edx
  int v2; // ecx

  list = array->list;
  v2 = array->growby + array->capacity;
  array->capacity = v2;
  array->list = realloc(list, v2 * array->elemsize);
}

// source: j/0/network/darray.c:76  [anchor-mhash]
struct DArrayImplementation *__cdecl SetElement(
        struct DArrayImplementation *array,
        void *elem,
        int pos)
{
  int v3; // edi
  char *list; // edx
  struct DArrayImplementation *result; // eax

  v3 = pos * array->elemsize;
  list = (char *)array->list;
  result = (struct DArrayImplementation *)array->elemsize;
  qmemcpy(&list[v3], elem, (unsigned int)result);
  return result;
}

// source: j/0/network/darray.c:82  [anchor-mhash]
struct DArrayImplementation *__cdecl ArrayNew(
        int elemSize,
        int numElemsToAllocate,
        void (__cdecl *elemFreeFn)(void *))
{
  struct DArrayImplementation *v5; // esi

  v5 = (struct DArrayImplementation *)malloc(0x18u);
  if ( !numElemsToAllocate )
    numElemsToAllocate = 8;
  v5->elemsize = elemSize;
  v5->count = 0;
  v5->capacity = numElemsToAllocate;
  v5->growby = numElemsToAllocate;
  v5->elemfreefn = elemFreeFn;
  v5->list = malloc(numElemsToAllocate * elemSize);
  return v5;
}

// source: j/0/network/darray.c:102  [anchor-hash]
void __cdecl ArrayFree(struct DArrayImplementation *array)
{
  int i; // edi
  void (__cdecl *elemfreefn)(void *); // eax

  for ( i = 0; i < array->count; ++i )
  {
    elemfreefn = array->elemfreefn;
    if ( elemfreefn )
      elemfreefn((char *)array->list + i * array->elemsize);
  }
  free(array->list);
  free(array);
}

// source: j/0/network/darray.c:116  [size]
int __cdecl ArrayLength(struct DArrayImplementation *array)
{
  return array->count;
}

// source: j/0/network/darray.c:121  [size]
void *__cdecl ArrayNth(struct DArrayImplementation *array, int n)
{
  return (char *)array->list + n * array->elemsize;
}

// source: j/0/network/darray.c:131  [anchor-caller]
struct DArrayImplementation *__cdecl ArrayAppend(
        struct DArrayImplementation *array,
        void *newElem)
{
  struct DArrayImplementation *result; // eax

  ArrayInsertAt(array, newElem, array->count);
  return result;
}

// source: j/0/network/darray.c:136  [anchor-callee]
void __cdecl ArrayInsertAt(struct DArrayImplementation *array, void *newElem, int n)
{
  int capacity; // eax
  int v4; // eax
  size_t v5; // edx
  int v6; // esi
  bool v7; // cc

  capacity = array->capacity;
  if ( array->count == capacity )
  {
    v4 = array->growby + capacity;
    v5 = v4 * array->elemsize;
    array->capacity = v4;
    array->list = realloc(array->list, v5);
  }
  v6 = array->count + 1;
  v7 = n < array->count;
  array->count = v6;
  if ( v7 )
    memmove(
      (char *)array->list + array->elemsize * (n + 1),
      (char *)array->list + n * array->elemsize,
      array->elemsize * (v6 - n - 1));
  qmemcpy((char *)array->list + n * array->elemsize, newElem, array->elemsize);
}

// source: j/0/network/darray.c:149  [anchor-caller]
struct DArrayImplementation *__cdecl ArrayInsertSorted(
        struct DArrayImplementation *array,
        void *newElem,
        int (__cdecl *comparator)(void *, void *))
{
  void *v4; // eax
  struct DArrayImplementation *result; // eax
  int found; // [esp+4h] [ebp-4h] BYREF

  v4 = mybsearch(newElem, array->list, array->count, array->elemsize, comparator, &found);
  ArrayInsertAt(array, newElem, (signed int)((int)v4 - (unsigned int)array->list) / array->elemsize);
  return result;
}

// source: j/0/network/darray.c:161  [anchor-callee]
void __cdecl ArrayRemoveAt(struct DArrayImplementation *array, int n)
{
  if ( n < array->count - 1 )
    memmove(
      (char *)array->list + n * array->elemsize,
      (char *)array->list + array->elemsize * (n + 1),
      array->elemsize * (array->count - n - 1));
  --array->count;
}

// source: j/0/network/darray.c:171  [anchor-callee]
void __cdecl ArrayDeleteAt(struct DArrayImplementation *array, int n)
{
  void (__cdecl *elemfreefn)(void *); // eax

  elemfreefn = array->elemfreefn;
  if ( elemfreefn )
    elemfreefn((char *)array->list + n * array->elemsize);
  if ( n < array->count - 1 )
    memmove(
      (char *)array->list + n * array->elemsize,
      (char *)array->list + array->elemsize * (n + 1),
      array->elemsize * (array->count - n - 1));
  --array->count;
}

// source: j/0/network/darray.c:180  [anchor-mhash]
void __cdecl ArrayReplaceAt(struct DArrayImplementation *array, void *newElem, int n)
{
  void (__cdecl *elemfreefn)(void *); // eax

  elemfreefn = array->elemfreefn;
  if ( elemfreefn )
    elemfreefn((char *)array->list + n * array->elemsize);
  qmemcpy((char *)array->list + n * array->elemsize, newElem, array->elemsize);
}

// source: j/0/network/darray.c:189  [size]
struct DArrayImplementation *__cdecl ArraySort(
        struct DArrayImplementation *array,
        int (__cdecl *comparator)(void *, void *))
{
  qsort(array->list, array->count, array->elemsize, comparator);
  return 0;
}

// source: j/0/network/darray.c:196  [anchor-caller]
int __cdecl ArraySearch(
        struct DArrayImplementation *array,
        void *key,
        int (__cdecl *comparator)(void *, void *),
        int fromIndex,
        int isSorted)
{
  int count; // eax
  bool v6; // zf
  int elemsize; // ecx
  void *v8; // eax
  int found; // [esp+4h] [ebp-4h] BYREF

  found = 1;
  if ( array
    && (count = array->count) != 0
    && ((v6 = isSorted == 0, elemsize = array->elemsize, v6)
      ? (v8 = mylsearch(key, (char *)array->list + fromIndex * elemsize, count - fromIndex, elemsize, comparator))
      : (v8 = mybsearch(
                key,
                (char *)array->list + fromIndex * elemsize,
                count - fromIndex,
                elemsize,
                comparator,
                &found)),
        v8 && found) )
  {
    return (signed int)((int)v8 - (unsigned int)array->list) / array->elemsize;
  }
  else
  {
    return -1;
  }
}

// source: j/0/network/darray.c:216  [anchor-mhash]
void __cdecl ArrayMap(
        struct DArrayImplementation *array,
        void (__cdecl *fn)(void *, void *),
        void *clientData)
{
  int i; // esi

  for ( i = 0; i < array->count; ++i )
    fn((char *)array->list + i * array->elemsize, clientData);
}

// source: j/0/network/darray.c:227  [anchor-mhash]
void __cdecl ArrayMapBackwards(
        struct DArrayImplementation *array,
        void (__cdecl *fn)(void *, void *),
        void *clientData)
{
  int i; // esi

  for ( i = array->count - 1; i >= 0; --i )
    fn((char *)array->list + i * array->elemsize, clientData);
}

// source: j/0/network/darray.c:238  [anchor-mhash]
void *__cdecl ArrayMap2(
        struct DArrayImplementation *array,
        int (__cdecl *fn)(void *, void *),
        void *clientData)
{
  int v3; // ebx
  char *v4; // esi

  v3 = 0;
  if ( array->count <= 0 )
    return nullptr;
  while ( 1 )
  {
    v4 = (char *)array->list + v3 * array->elemsize;
    if ( !fn(v4, clientData) )
      break;
    if ( ++v3 >= array->count )
      return nullptr;
  }
  return v4;
}

// source: j/0/network/darray.c:255  [anchor-hash]
void __cdecl ArrayClear(struct DArrayImplementation *array)
{
  int v1; // edi
  int count; // ebx
  void (__cdecl *elemfreefn)(void *); // eax

  v1 = array->count - 1;
  if ( v1 >= 0 )
  {
    count = array->count;
    do
    {
      elemfreefn = array->elemfreefn;
      if ( elemfreefn )
        elemfreefn((char *)array->list + v1 * array->elemsize);
      if ( v1 < array->count - 1 )
        memmove(
          (char *)array->list + v1 * array->elemsize,
          (char *)array->list + array->elemsize * count,
          array->elemsize * (array->count - v1 - 1));
      --v1;
      --count;
      --array->count;
    }
    while ( v1 >= 0 );
  }
}

// source: j/0/network/darray.c:270  [anchor-callee]
void *__cdecl mylsearch(
        void *key,
        void *base,
        int count,
        int size,
        int (__cdecl *comparator)(void *, void *))
{
  int v5; // esi
  char *v6; // edi

  v5 = 0;
  if ( count <= 0 )
    return nullptr;
  v6 = (char *)base;
  while ( comparator(key, v6) )
  {
    ++v5;
    v6 += size;
    if ( v5 >= count )
      return nullptr;
  }
  return (char *)base + size * v5;
}

// source: j/0/network/darray.c:284  [anchor-callee]
void *__cdecl mybsearch(
        void *elem,
        void *base,
        int num,
        int elemsize,
        int (__cdecl *comparator)(void *, void *),
        int *found)
{
  int v6; // ebx
  int v7; // edi
  int v8; // esi
  int v9; // eax

  v6 = 0;
  v7 = num - 1;
  *found = 0;
  while ( v6 <= v7 )
  {
    v8 = (v7 + v6) >> 1;
    v9 = comparator((char *)base + elemsize * v8, elem);
    if ( v9 )
    {
      if ( v9 < 0 )
      {
        v6 = v8 + 1;
        continue;
      }
    }
    else
    {
      *found = 1;
    }
    v7 = v8 - 1;
  }
  return (char *)base + elemsize * v6;
}
