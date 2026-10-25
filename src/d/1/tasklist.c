/* d/1/tasklist.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: d/1/tasklist.c:28  [size]
void __cdecl QTaskList_Open()
{
  ;
}

// source: d/1/tasklist.c:41  [size]
void __cdecl QTaskList_Close()
{
  ;
}

// source: d/1/tasklist.c:54  [anchor-strings]
_DWORD *__cdecl QTaskList_Register(_DWORD *result, struct QTaskList_s *ptQTaskList)
{
  if ( (int)(*result) >= (int)(result[1]) )
  {
    LDebug_Error("QTaskList is full");
    abort();
  }
  result[(*result)++ + 2] = ptQTaskList;
  return result;
}

// source: d/1/tasklist.c:87  [anchor-callee]
struct QTaskList_s *__cdecl QTaskList_Remove(
        struct QTaskList_s *ptQTaskList,
        struct QTask_s *ptQTask)
{
  int nTask; // esi
  int v3; // ecx
  struct QTask_s **i; // edx

  nTask = ptQTaskList->nTask;
  v3 = 0;
  if ( ptQTaskList->nTask > 0 )
  {
    for ( i = ptQTaskList->ptQTask; *i != ptQTask; ++i )
    {
      if ( ++v3 >= ptQTaskList->nTask )
        return ptQTaskList;
    }
    ptQTaskList->nTask = nTask - 1;
    ptQTaskList->ptQTask[v3] = ptQTaskList->ptQTask[nTask - 1];
  }
  return ptQTaskList;
}

// source: d/1/tasklist.c:115  [anchor-callee]
enum bool __cdecl QTaskList_IsQTaskRegistered(
        struct QTaskList_s *ptQTaskList,
        int *piTask,
        struct QTask_s *ptQTask)
{
  int nTask; // ecx
  int v4; // eax
  struct QTask_s **i; // edx

  nTask = ptQTaskList->nTask;
  v4 = 0;
  if ( ptQTaskList->nTask <= 0 )
    return false;
  for ( i = ptQTaskList->ptQTask; *i != ptQTask; ++i )
  {
    if ( ++v4 >= nTask )
      return false;
  }
  if ( piTask )
    *piTask = v4;
  return true;
}

// source: d/1/tasklist.c:146  [anchor-mhash]
struct QTask_s *__cdecl QTaskList_RegisterSafe(
        struct QTaskList_s *ptQTaskList,
        struct QTask_s *ptQTask)
{
  struct QTask_s *result; // eax

  result = (struct QTask_s *)QTaskList_IsQTaskRegistered(ptQTaskList, nullptr, ptQTask);
  if ( !result )
    return (struct QTask_s *)QTaskList_Register(ptQTaskList, (struct QTaskList_s *)ptQTask);
  return result;
}

// source: d/1/tasklist.c:164  [anchor-callee]
struct QTask_s *__cdecl QTaskList_RemoveSafe(
        struct QTaskList_s *ptQTaskList,
        struct QTask_s *ptQTask)
{
  struct QTask_s *result; // eax

  result = (struct QTask_s *)QTaskList_IsQTaskRegistered(ptQTaskList, nullptr, ptQTask);
  if ( result )
    return (struct QTask_s *)QTaskList_Remove(ptQTaskList, ptQTask);
  return result;
}

// source: d/1/tasklist.c:180  [anchor-hash]
struct QTaskList_s *__cdecl QTaskList_New(int nMaxTask)
{
  struct QTaskList_s *result; // eax

  result = (struct QTaskList_s *)Mem_AllocFn(4 * nMaxTask + 8, 4);
  result->nTask = 0;
  result->nMaxTask = nMaxTask;
  return result;
}

// source: d/1/tasklist.c:199  [anchor-callee]
void __cdecl QTaskList_Delete(struct QTaskList_s *ptQTaskList)
{
  int v1; // esi

  if ( ptQTaskList )
  {
    v1 = *(_DWORD *)((unsigned int)ptQTaskList[-1].ptQTask & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v1);
    memset(*(void **)(v1 + 8), 0xCDu, *(_DWORD *)(v1 + 16));
    free((void *)v1);
  }
}
