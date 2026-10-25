/* b/2/rendermode.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: b/2/rendermode.c:65  [size]
void __cdecl RenderMode_Close()
{
  ;
}

// source: b/2/rendermode.c:77  [anchor-strings]
enum RenderMode_enum __cdecl RenderMode_New(char *zName)
{
  enum RenderMode_enum result; // eax
  char *p_isAllocated; // ecx
  enum RenderMode_enum v3; // ecx

  result = APPCONTEXT_RENDER_MODE_SOFTWARE;
  p_isAllocated = &RenderMode_atRenderMode[0].isAllocated;
  while ( *p_isAllocated )
  {
    p_isAllocated += 520;
    ++result;
    if ( (int)p_isAllocated >= 139172388 )
    {
      LDebug_Error("RenderMode: Failed to create new rendermode '%s'", zName);
      abort();
    }
  }
  v3 = result;
  RenderMode_atRenderMode[v3].zName = zName;
  RenderMode_atRenderMode[v3].isAllocated = 1;
  return result;
}

// source: b/2/rendermode.c:104  [anchor-hash]
enum RenderMode_enum __cdecl RenderMode_Delete(enum RenderMode_enum eRenderMode)
{
  enum RenderMode_enum result; // eax

  result = eRenderMode;
  RenderMode_atRenderMode[result].isAllocated = 0;
  return result * 520;
}

// source: b/2/rendermode.c:120  [anchor-callee]
int __cdecl RenderMode_NewMethod(char *zName)
{
  int result; // eax

  result = 0;
  while ( RenderMode_atRenderModeMethod[result].isAllocated )
  {
    if ( ++result >= 128 )
    {
      LDebug_Error("RenderMode: Failed to create new method '%s'", zName);
      abort();
    }
  }
  RenderMode_atRenderModeMethod[result].zName = zName;
  RenderMode_atRenderModeMethod[result].isAllocated = 1;
  return result;
}

// source: b/2/rendermode.c:148  [size]
int __cdecl RenderMode_DeleteMethod(int eRenderModeMethod)
{
  RenderMode_atRenderModeMethod[eRenderModeMethod].isAllocated = 0;
  return eRenderModeMethod;
}

// source: b/2/rendermode.c:168  [size]
enum RenderMode_enum __cdecl RenderMode_SetMethod(
        enum RenderMode_enum eRenderMode,
        int eRenderModeMethod,
        void (__cdecl *pfRenderModeMethod)(void *))
{
  enum RenderMode_enum result; // eax

  result = eRenderModeMethod + 130 * eRenderMode;
  RenderMode_atRenderMode[0].apfRenderModeMethod[result] = pfRenderModeMethod;
  return result;
}

// source: b/2/rendermode.c:191  [anchor-callee]
void __cdecl RenderMode_EnumerateRenderModes(
        void (__cdecl *pfRenderModeEnumerateCallback)(struct RenderModeEnumerateContext_s *, void *),
        void *pxContext)
{
  enum RenderMode_enum v2; // edi
  struct RenderMode_s *v3; // esi
  char *zName; // eax
  struct RenderModeEnumerateContext_s tRenderModeEnumerateContext; // [esp+Ch] [ebp-8h] BYREF

  v2 = APPCONTEXT_RENDER_MODE_SOFTWARE;
  v3 = RenderMode_atRenderMode;
  do
  {
    if ( v3->isAllocated )
    {
      zName = v3->zName;
      tRenderModeEnumerateContext.eRenderMode = v2;
      tRenderModeEnumerateContext.zRenderMode = zName;
      pfRenderModeEnumerateCallback(&tRenderModeEnumerateContext, pxContext);
    }
    ++v3;
    ++v2;
  }
  while ( (int)v3 < 139171872 );
}

// source: b/2/rendermode.c:219  [anchor-hash]
enum RenderMode_enum __cdecl RenderMode_SetActiveRenderMode(
        enum RenderMode_enum eRenderMode)
{
  if ( eRenderMode != RenderMode_eActiveRenderMode )
  {
    qmemcpy(
      &RenderMode_tActiveRenderMode,
      (void *)(520 * eRenderMode + 139167712),
      sizeof(RenderMode_tActiveRenderMode));
    RenderMode_eActiveRenderMode = eRenderMode;
  }
  return eRenderMode;
}

// source: b/2/rendermode.c:238  [size]
void __cdecl RenderMode_InvalidateActiveRenderMode()
{
  RenderMode_eActiveRenderMode = -1;
}

// source: b/2/rendermode.c:251  [size]
enum RenderMode_enum __cdecl RenderMode_GetActiveRenderMode()
{
  return RenderMode_eActiveRenderMode;
}

// source: b/2/rendermode.c:264  [anchor-hash]
enum RenderMode_enum __cdecl RenderMode_PopRenderMode()
{
  enum RenderMode_enum result; // eax

  result = RenderMode_aeRenderModeStack[RenderMode_nSP];
  if ( result == -1 )
  {
    RenderMode_eActiveRenderMode = -1;
    return -1;
  }
  else
  {
    ++RenderMode_nSP;
    if ( result != RenderMode_eActiveRenderMode )
    {
      qmemcpy(
        &RenderMode_tActiveRenderMode,
        (void *)(520 * result + 139167712),
        sizeof(RenderMode_tActiveRenderMode));
      RenderMode_eActiveRenderMode = result;
    }
  }
  return result;
}

// source: b/2/rendermode.c:291  [anchor-mhash]
void __cdecl RenderMode_PushRenderMode(enum RenderMode_enum eRenderMode)
{
  bool v1; // zf

  v1 = eRenderMode == RenderMode_eActiveRenderMode;
  RenderMode_aeRenderModeStack[--RenderMode_nSP] = RenderMode_eActiveRenderMode;
  if ( !v1 )
  {
    qmemcpy(
      &RenderMode_tActiveRenderMode,
      (void *)(520 * eRenderMode + 139167712),
      sizeof(RenderMode_tActiveRenderMode));
    RenderMode_eActiveRenderMode = eRenderMode;
  }
}

// source: b/2/rendermode.c:308  [size]
enum RenderMode_enum __cdecl RenderMode_RenderModeCall(
        enum RenderMode_enum eRenderMode,
        int eRenderModeMethod,
        void *pxContext)
{
  return ((enum RenderMode_enum (*)(void))RenderMode_atRenderMode[eRenderMode].apfRenderModeMethod[eRenderModeMethod])();
}

// source: b/2/rendermode.c:326  [anchor-mhash]
enum RenderMode_enum __cdecl RenderMode_RenderModeCallIfDefined(
        enum RenderMode_enum eRenderMode,
        int eRenderModeMethod,
        void *pxContext)
{
  enum RenderMode_enum result; // eax

  result = (enum RenderMode_enum)RenderMode_atRenderMode[eRenderMode].apfRenderModeMethod[eRenderModeMethod];
  if ( result )
    return ((int (__cdecl *)(void *))result)(pxContext);
  return result;
}
