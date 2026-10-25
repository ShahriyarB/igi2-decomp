/* b/2/pc/pc_primitive.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: b/2/pc/pc_primitive.c:62  [size]
void __cdecl Primitive_InitFreePointer()
{
  Primitive_ptNextFreePrimitive = (void *)Primitive_asPrimitive[0];
}

// source: b/2/pc/pc_primitive.c:108  [anchor-hash]
struct RenderPrimitive_s *__cdecl Primitive_DrawList(struct RenderPrimitive_s *ptRenderPrimitive)
{
  struct RenderPrimitive_s *i; // esi
  int ePrimType; // ecx
  int v3; // eax
  struct RenderPrimitive_s *result; // eax

  for ( i = ptRenderPrimitive; i; i = i->ptNext )
  {
    ePrimType = i->ePrimType;
    if ( ePrimType != -1 )
    {
      v3 = ptRenderPrimitive->ePrimType;
      if ( ePrimType != v3 && v3 != -1 )
        RenderMode_tActiveRenderMode.apfRenderModeMethod[v3](nullptr);
      RenderMode_tActiveRenderMode.apfRenderModeMethod[i->ePrimType](i);
      ptRenderPrimitive = i;
    }
  }
  result = (struct RenderPrimitive_s *)ptRenderPrimitive->ePrimType;
  if ( result != (struct RenderPrimitive_s *)-1 )
    return ((struct RenderPrimitive_s *(__cdecl *)(_DWORD))RenderMode_tActiveRenderMode.apfRenderModeMethod[(_DWORD)result])(0);
  return result;
}

// source: b/2/pc/pc_primitive.c:147  [anchor-callee]
void __cdecl Primitive_Draw(struct RenderPrimitive_s *ptRenderPrimitive)
{
  if ( ptRenderPrimitive )
  {
    RenderMode_tActiveRenderMode.apfRenderModeMethod[ptRenderPrimitive->ePrimType](ptRenderPrimitive);
    dword_834E068 = (int)ptRenderPrimitive;
  }
  else if ( dword_834E068 )
  {
    RenderMode_tActiveRenderMode.apfRenderModeMethod[*(_DWORD *)(dword_834E068 + 4)](nullptr);
  }
}

// source: b/2/pc/pc_primitive.c:179  [anchor-mhash]
struct RenderPrimitive_s *__cdecl Primitive_ClearList(
        struct RenderPrimitive_s *ptRenderPrimitive,
        int nSize)
{
  int v2; // ecx

  if ( nSize )
  {
    v2 = nSize - 1;
    ptRenderPrimitive->ptNext = nullptr;
    for ( ptRenderPrimitive->ePrimType = -1; v2; --v2 )
    {
      ptRenderPrimitive[1].ptNext = ptRenderPrimitive;
      ptRenderPrimitive[1].ePrimType = -1;
      ++ptRenderPrimitive;
    }
  }
  return ptRenderPrimitive;
}

// source: b/2/pc/pc_primitive.c:208  [size]
int __cdecl Primitive_AddToList(int nDepth, void *pxData)
{
  int result; // eax

  result = (int)&RenderContext_tActiveRenderContext.ptRenderPrimitive_[nDepth];
  *(_DWORD *)pxData = *(_DWORD *)result;
  *(_DWORD *)result = pxData;
  return result;
}

// source: b/2/pc/pc_primitive.c:247  [anchor-hash]
void __cdecl Primitive_Close()
{
  int v0; // esi

  if ( Primitive_asPrimitive[0] )
  {
    v0 = *(_DWORD *)((Primitive_asPrimitive[0] - 4) & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
  Primitive_asPrimitive[0] = 0;
}

// source: b/2/pc/pc_primitive.c:261  [anchor-callee]
int __cdecl Primitive_NewPrimType(char *zName)
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

// source: b/2/pc/pc_primitive.c:276  [size]
int __cdecl Primitive_DeletePrimType(int ePrimType)
{
  RenderMode_atRenderModeMethod[ePrimType].isAllocated = 0;
  return ePrimType;
}

// source: b/2/pc/pc_primitive.c:294  [anchor-mhash]
void __cdecl Primitive_SetPrimitiveDrawCallback(
        struct RenderModeEnumerateContext_s *ptRenderModeEnumerateContext,
        struct PrimitiveSetGeneralDrawContext_s *ptPrimitiveSetGeneralDrawContext)
{
  RenderMode_atRenderMode[ptRenderModeEnumerateContext->eRenderMode].apfRenderModeMethod[ptPrimitiveSetGeneralDrawContext->ePrimType] = ptPrimitiveSetGeneralDrawContext->pfPrimitiveDraw;
}

// source: b/2/pc/pc_primitive.c:316  [anchor-mhash]
void __cdecl Primitive_SetGeneralPrimitiveDraw(int ePrimType, void (__cdecl *pfPrimitiveDraw)(void *))
{
  struct PrimitiveSetGeneralDrawContext_s tPrimitiveSetGeneralDrawContext; // [esp+4h] [ebp-8h] BYREF

  tPrimitiveSetGeneralDrawContext.ePrimType = ePrimType;
  tPrimitiveSetGeneralDrawContext.pfPrimitiveDraw = pfPrimitiveDraw;
  RenderMode_EnumerateRenderModes(
    (void (__cdecl *)(struct RenderModeEnumerateContext_s *, void *))Primitive_SetPrimitiveDrawCallback,
    &tPrimitiveSetGeneralDrawContext);
}
