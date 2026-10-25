/* b/4/qvertex.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: b/4/pc/pc_qvertex.c:50  [layout]
void __cdecl QVertex_Open()
{
  int v0; // eax
  int v1; // eax
  __int32 v2; // ecx
  __int32 v3; // eax
  int v4; // ecx
  __int32 v5; // eax
  struct RenderStateBlock_t *v6; // ecx
  int nNumStates; // eax
  struct RenderStateBlock_t *v8; // ecx
  int v9; // eax
  struct RenderStateBlock_t *v10; // ecx
  int v11; // eax

  QVertex_ptActiveTexture = nullptr;
  QVertex_ptActivePalette = nullptr;
  v0 = 0;
  while ( RenderMode_atRenderModeMethod[v0].isAllocated )
  {
    if ( ++v0 >= 128 )
    {
      LDebug_Error("RenderMode: Failed to create new method '%s'", "QVertex:RegisterStrip");
      goto LABEL_5;
    }
  }
  RenderMode_atRenderModeMethod[v0].zName = "QVertex:RegisterStrip";
  RenderMode_atRenderModeMethod[v0].isAllocated = 1;
  QVertex_eRegisterQVertexStripMethod = v0;
  v1 = 0;
  while ( RenderMode_atRenderModeMethod[v1].isAllocated )
  {
    if ( ++v1 >= 128 )
    {
      LDebug_Error("RenderMode: Failed to create new method '%s'", "QVertex:DrawStrip");
LABEL_5:
      abort();
    }
  }
  v2 = v1 + 130 * dword_73D31C;
  RenderMode_atRenderMode[dword_73D31C].apfRenderModeMethod[QVertex_eRegisterQVertexStripMethod] = (void (__cdecl *)(void *))OffscreenBufferQVertex_RegisterStrip;
  RenderMode_atRenderModeMethod[v1].zName = "QVertex:DrawStrip";
  RenderMode_atRenderModeMethod[v1].isAllocated = 1;
  QVertex_eStripPrimType = v1;
  RenderMode_atRenderMode[0].apfRenderModeMethod[v2] = (void (__cdecl *)(void *))OffscreenBufferQVertex_DrawStrip;
  v3 = 130 * Direct3D_eRenderMode;
  v4 = QVertex_eStripPrimType;
  RenderMode_atRenderMode[Direct3D_eRenderMode].apfRenderModeMethod[QVertex_eRegisterQVertexStripMethod] = (void (__cdecl *)(void *))sub_616080;
  v5 = v4 + v3;
  v6 = Direct3D_ptTextureStateBlock;
  RenderMode_atRenderMode[0].apfRenderModeMethod[v5] = (void (__cdecl *)(void *))Direct3DQVertex_DrawStrip;
  Direct3DQVertex_tLastContext.bFlags = -1;
  Direct3DQVertex_tLastContext.ptTexInfo = nullptr;
  nNumStates = v6->nNumStates;
  v6->nNumStates = nNumStates + 1;
  v6->atRenderState[nNumStates].pfCallback = (void (__cdecl *)(void *))Direct3DQVertex_SetTextureState;
  v8 = Direct3D_ptBlendStateBlock;
  Direct3DQVertex_eTextureState = nNumStates;
  v9 = Direct3D_ptBlendStateBlock->nNumStates;
  Direct3D_ptBlendStateBlock->nNumStates = v9 + 1;
  v8->atRenderState[v9].pfCallback = (void (__cdecl *)(void *))Direct3DQVertex_SetAlphaState;
  v10 = Direct3D_ptGenericStateBlock;
  Direct3DQVertex_eBlendState = v9;
  v11 = Direct3D_ptGenericStateBlock->nNumStates;
  Direct3D_ptGenericStateBlock->nNumStates = v11 + 1;
  v10->atRenderState[v11].pfCallback = (void (__cdecl *)(void *))Direct3DQVertex_SetGenericState;
  Direct3DQVertex_eGenericState = v11;
}

// source: b/4/qvertex.c:153  [size]
void __cdecl QVertex_Close()
{
  int v0; // edx

  v0 = QVertex_eRegisterQVertexStripMethod;
  RenderMode_atRenderModeMethod[QVertex_eStripPrimType].isAllocated = 0;
  RenderMode_atRenderModeMethod[v0].isAllocated = 0;
}
