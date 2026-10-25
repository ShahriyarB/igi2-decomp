/* b/2/renderstate.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: b/2/renderstate.c:28  [anchor-hash]
struct RenderStateBlock_t *__cdecl RenderState_NewBlock(int nNumMaxStates)
{
  struct RenderStateBlock_t *result; // eax

  result = (struct RenderStateBlock_t *)Mem_AllocFn(4 * nNumMaxStates + 20, 4);
  result->eCurrentState = -1;
  result->nNumMaxStates = nNumMaxStates;
  result->nNumStates = 0;
  result->nSafety0 = -1412584499;
  result->nSafety1 = -591733574;
  return result;
}

// source: b/2/renderstate.c:58  [size]
void __cdecl RenderState_DeleteBlock(struct RenderStateBlock_t *ptBlock)
{
  int v1; // esi

  if ( ptBlock )
  {
    v1 = *(_DWORD *)((unsigned int)ptBlock[-1].atRenderState & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v1);
    memset(*(void **)(v1 + 8), 0xCDu, *(_DWORD *)(v1 + 16));
    free((void *)v1);
  }
}

// source: b/2/renderstate.c:77  [size]
int __cdecl RenderState_NewState(
        struct RenderStateBlock_t *ptBlock,
        void (__cdecl *pfCallback)(void *))
{
  int result; // eax

  result = ptBlock->nNumStates;
  ptBlock->nNumStates = result + 1;
  ptBlock->atRenderState[result].pfCallback = pfCallback;
  return result;
}

// source: b/2/renderstate.c:107  [size]
int __cdecl RenderState_DeleteState(struct RenderStateBlock_t *ptBlock, int eState)
{
  ptBlock->atRenderState[eState].pfCallback = nullptr;
  return eState;
}

// source: b/2/renderstate.c:126  [size]
void __cdecl RenderState_Open()
{
  ;
}

// source: b/2/renderstate.c:138  [size]
void __cdecl RenderState_Close()
{
  ;
}
