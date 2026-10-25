/* b/4/pc/pc_batch.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: b/4/pc/pc_batch.c:150  [size~]
struct Batch_VertexBuffer_t *__cdecl Batch_GetVertexBuffer(
        struct Batch_VBChain_t *ptListItem,
        void (__cdecl *pfCallback)(struct Batch_SetStatesContext_s *))
{
  struct QObjectVector_s *ptChain; // esi
  int nAllocated; // ebp
  int v4; // edx
  void **papxElement; // ebx
  struct Batch_VertexBuffer_t *result; // eax
  void (__cdecl *v7)(struct Batch_SetStatesContext_s *); // ecx
  unsigned int v8; // eax
  struct IDirect3DVertexBuffer8 **v9; // ebp
  unsigned int v10; // esi
  int nMaxVertices; // ecx
  int v12; // ecx
  unsigned int v13; // esi
  struct Batch_VertexBuffer_t *v14; // esi
  struct IDirect3DVertexBuffer8 *ptVertexBuffer; // eax
  struct IDirect3DVertexBuffer8Vtbl *lpVtbl; // ecx
  int v17; // [esp+50h] [ebp-8h]
  int v18; // [esp+54h] [ebp-4h]

  ptChain = ptListItem->ptChain;
  nAllocated = ptChain->nAllocated;
  v4 = 0;
  v17 = -1;
  v18 = 0;
  if ( nAllocated <= 0 )
    goto LABEL_9;
  papxElement = ptChain->papxElement;
  do
  {
    result = (struct Batch_VertexBuffer_t *)*papxElement;
    v7 = *((void (__cdecl **)(struct Batch_SetStatesContext_s *))*papxElement + 8);
    if ( v7 == pfCallback )
      return result;
    if ( !v7 && result->ptVertexBuffer )
      v17 = v4;
    ++v4;
    ++papxElement;
  }
  while ( v4 < nAllocated );
  v18 = v4;
  if ( v17 == -1 )
  {
LABEL_9:
    if ( ptChain->nAllocated == ptChain->nSize )
      QObjectVector_Realloc(ptChain, ptChain->nReallocSize);
    v8 = ptChain->nAllocated;
    v9 = (struct IDirect3DVertexBuffer8 **)ptChain->papxElement[v8];
    ptChain->nAllocated = v8 + 1;
    v10 = ptListItem->ptDesc->nMaxVertices * ptListItem->ptDesc->nStride;
    if ( Direct3D_ptDevice->lpVtbl->ResourceManagerDiscardBytes(Direct3D_ptDevice, v10) )
    {
      while ( 1 )
      {
        ptListItem->ptDesc->nMaxVertices /= 2;
        nMaxVertices = ptListItem->ptDesc->nMaxVertices;
        v10 = nMaxVertices * ptListItem->ptDesc->nStride;
        if ( nMaxVertices < 256 )
          break;
        if ( !Direct3D_ptDevice->lpVtbl->ResourceManagerDiscardBytes(Direct3D_ptDevice, v10) )
          goto LABEL_14;
      }
      LDebug_Error("Dynamic Geometry: Out of agp memory");
LABEL_22:
      abort();
    }
LABEL_14:
    if ( Direct3D_ptDevice->lpVtbl->CreateVertexBuffer(
           Direct3D_ptDevice,
           v10,
           ptListItem->ptDesc->bUsage | (Direct3D_isHWTnL != 0 ? 0 : 0x10),
           ptListItem->ptDesc->bFVF,
           ptListItem->ptDesc->ePool,
           v9) )
    {
      while ( 1 )
      {
        ptListItem->ptDesc->nMaxVertices /= 2;
        v12 = ptListItem->ptDesc->nMaxVertices;
        if ( v12 < 256 )
          break;
        v13 = v12 * ptListItem->ptDesc->nStride;
        Direct3D_ptDevice->lpVtbl->ResourceManagerDiscardBytes(Direct3D_ptDevice, v13);
        if ( !Direct3D_ptDevice->lpVtbl->CreateVertexBuffer(
                Direct3D_ptDevice,
                v13,
                ptListItem->ptDesc->bUsage | (Direct3D_isHWTnL != 0 ? 0 : 0x10),
                ptListItem->ptDesc->bFVF,
                ptListItem->ptDesc->ePool,
                v9) )
          goto LABEL_17;
      }
      LDebug_Error("Dynamic Geometry: Can not create vertex buffer");
      goto LABEL_22;
    }
LABEL_17:
    v9[4] = nullptr;
    v17 = v18;
  }
  v14 = (struct Batch_VertexBuffer_t *)ptListItem->ptChain->papxElement[v17];
  ptVertexBuffer = v14->ptVertexBuffer;
  lpVtbl = v14->ptVertexBuffer->lpVtbl;
  if ( v14->pfSetStates )
    lpVtbl->Lock(ptVertexBuffer, 0, 0, &v14->pxLockedVertices, 0x2000u);
  else
    lpVtbl->Lock(ptVertexBuffer, 0, 0, &v14->pxLockedVertices, 4096u);
  v14->pfSetStates = nullptr;
  v14->nBatchedObjects = 0;
  v14->nBatchedVertices = 0;
  v14->pfUnsetStates = pfCallback;
  return v14;
}

// source: b/4/pc/pc_batch.c:253  [size~]
struct Batch_IndexBuffer_t *__cdecl Batch_GetIndexBuffer(
        struct Batch_IBChain_t *ptListItem,
        void (__cdecl *pfCallback)(struct Batch_SetStatesContext_s *))
{
  struct QObjectVector_s *ptChain; // esi
  int nAllocated; // edx
  int v4; // ebp
  int v5; // ebx
  void **papxElement; // edi
  struct Batch_IndexBuffer_t *result; // eax
  void (__cdecl *v8)(struct Batch_SetStatesContext_s *); // ecx
  unsigned int v9; // eax
  struct IDirect3DIndexBuffer8 **v10; // edi
  int v11; // ebp
  struct Batch_IndexBuffer_t *v12; // esi
  struct IDirect3DIndexBuffer8 *ptIndexBuffer; // eax
  struct IDirect3DIndexBuffer8Vtbl *lpVtbl; // ecx

  ptChain = ptListItem->ptChain;
  nAllocated = ptChain->nAllocated;
  v4 = -1;
  v5 = 0;
  if ( nAllocated <= 0 )
  {
LABEL_9:
    if ( ptChain->nAllocated == ptChain->nSize )
      QObjectVector_Realloc(ptListItem->ptChain, ptChain->nReallocSize);
    v9 = ptChain->nAllocated;
    v10 = (struct IDirect3DIndexBuffer8 **)ptChain->papxElement[v9];
    v11 = Direct3D_isHWTnL;
    ptChain->nAllocated = v9 + 1;
    if ( Direct3D_ptDevice->lpVtbl->CreateIndexBuffer(
           Direct3D_ptDevice,
           ptListItem->ptDesc->nMaxIndices * ptListItem->ptDesc->nStride,
           ptListItem->ptDesc->bUsage | (v11 != 0 ? 0 : 0x10),
           ptListItem->ptDesc->eFormat,
           ptListItem->ptDesc->ePool,
           v10) )
    {
      LDebug_Error("Dynamic Geometry: Can not create vertex buffer");
      abort();
    }
    v10[3] = nullptr;
    v4 = v5;
LABEL_14:
    v12 = (struct Batch_IndexBuffer_t *)ptListItem->ptChain->papxElement[v4];
    ptIndexBuffer = v12->ptIndexBuffer;
    lpVtbl = v12->ptIndexBuffer->lpVtbl;
    if ( v12->pfSetStates )
      lpVtbl->Lock(ptIndexBuffer, 0, 0, &v12->pxLockedIndices, 0x2000u);
    else
      lpVtbl->Lock(ptIndexBuffer, 0, 0, &v12->pxLockedIndices, 4096u);
    v12->pfSetStates = nullptr;
    v12->nBatchedIndices = 0;
    v12->pfUnsetStates = pfCallback;
    return v12;
  }
  else
  {
    papxElement = ptChain->papxElement;
    while ( 1 )
    {
      result = (struct Batch_IndexBuffer_t *)*papxElement;
      v8 = *((void (__cdecl **)(struct Batch_SetStatesContext_s *))*papxElement + 7);
      if ( v8 == pfCallback )
        break;
      if ( !v8 && result->ptIndexBuffer )
        v4 = v5;
      ++v5;
      ++papxElement;
      if ( v5 >= nAllocated )
      {
        if ( v4 != -1 )
          goto LABEL_14;
        goto LABEL_9;
      }
    }
  }
  return result;
}

// source: b/4/pc/pc_batch.c:333  [size]
void __cdecl Batch_UnsetModeCallback()
{
  struct QObjectVector_s *v0; // edx
  signed int v1; // ecx
  _DWORD *v2; // ebp
  int v3; // eax
  int v4; // edi
  _DWORD *v5; // esi
  struct QObjectVector_s *v6; // edx
  signed int v7; // ecx
  _DWORD *v8; // ebp
  int v9; // eax
  int v10; // edi
  _DWORD *v11; // esi
  int iChain; // [esp+10h] [ebp-4h]
  int iChaina; // [esp+10h] [ebp-4h]

  v0 = Batch_ptVBList;
  v1 = 0;
  for ( iChain = 0; v1 < (signed int)v0->nAllocated; iChain = v1 )
  {
    v2 = v0->papxElement[v1];
    v3 = v2[1];
    v4 = 0;
    if ( *(int *)(v3 + 36) > 0 )
    {
      do
      {
        v5 = *(_DWORD **)(*(_DWORD *)(v3 + 48) + 4 * v4);
        if ( *v5 )
        {
          (*(void (__stdcall **)(_DWORD))(*(_DWORD *)*v5 + 8))(*v5);
          *v5 = 0;
          v5[4] = 0;
          v5[5] = 0;
          v5[8] = 0;
        }
        v3 = v2[1];
        ++v4;
      }
      while ( v4 < (int)(*(_DWORD *)(v3 + 36)) );
      v1 = iChain;
      v0 = Batch_ptVBList;
    }
    ++v1;
  }
  v6 = Batch_ptIBList;
  v7 = 0;
  for ( iChaina = 0; v7 < (signed int)v6->nAllocated; iChaina = v7 )
  {
    v8 = v6->papxElement[v7];
    v9 = v8[1];
    v10 = 0;
    if ( *(int *)(v9 + 36) > 0 )
    {
      do
      {
        v11 = *(_DWORD **)(*(_DWORD *)(v9 + 48) + 4 * v10);
        if ( *v11 )
        {
          (*(void (__stdcall **)(_DWORD))(*(_DWORD *)*v11 + 8))(*v11);
          *v11 = 0;
          v11[3] = 0;
          v11[5] = 0;
          v11[7] = 0;
        }
        v9 = v8[1];
        ++v10;
      }
      while ( v10 < (int)(*(_DWORD *)(v9 + 36)) );
      v6 = Batch_ptIBList;
      v7 = iChaina;
    }
    ++v7;
  }
}

// source: b/4/pc/pc_batch.c:395  [size]
// attributes: thunk
void __cdecl Batch_DestroyCallback()
{
  Batch_UnsetModeCallback();
}

// source: b/4/pc/pc_batch.c:408  [size~]
void __cdecl Batch_SetModeCallback()
{
  struct QObjectVector_s *v0; // esi
  signed int v1; // edx
  _DWORD *v2; // edi
  int v3; // eax
  int v4; // ebp
  int v5; // edx
  _DWORD *v6; // esi
  struct QObjectVector_s *v7; // esi
  signed int v8; // edx
  enum _D3DFORMAT **v9; // edi
  enum _D3DFORMAT *v10; // eax
  int v11; // ebp
  int v12; // edx
  _DWORD *v13; // esi
  signed int i; // [esp+30h] [ebp-4h]
  signed int j; // [esp+30h] [ebp-4h]

  v0 = Batch_ptVBList;
  v1 = 0;
  for ( i = 0; v1 < (signed int)v0->nAllocated; i = v1 )
  {
    v2 = v0->papxElement[v1];
    v3 = v2[1];
    v4 = 0;
    if ( *(int *)(v3 + 36) > 0 )
    {
      do
      {
        v5 = *(_DWORD *)(v3 + 48);
        v6 = *(_DWORD **)(v5 + 4 * v4);
        if ( !*v6 )
        {
          if ( Direct3D_ptDevice->lpVtbl->CreateVertexBuffer(
                 Direct3D_ptDevice,
                 *(_DWORD *)(*v2 + 16) * *(_DWORD *)(*v2 + 20),
                 *(_DWORD *)(*v2 + 8) | (Direct3D_isHWTnL != 0 ? 0 : 0x10),
                 *(_DWORD *)(*v2 + 24),
                 *(enum _D3DPOOL *)(*v2 + 12),
                 *(struct IDirect3DVertexBuffer8 ***)(v5 + 4 * v4)) )
          {
LABEL_18:
            LDebug_Error("Dynamic Geometry: Can not create vertex buffer in SetModeCallback");
            abort();
          }
          v6[4] = 0;
          v6[5] = 0;
          v6[8] = 0;
          v6[7] = 1;
        }
        v3 = v2[1];
        ++v4;
      }
      while ( v4 < (int)(*(_DWORD *)(v3 + 36)) );
      v1 = i;
      v0 = Batch_ptVBList;
    }
    ++v1;
  }
  v7 = Batch_ptIBList;
  v8 = 0;
  for ( j = 0; v8 < (signed int)v7->nAllocated; j = v8 )
  {
    v9 = (enum _D3DFORMAT **)v7->papxElement[v8];
    v10 = v9[1];
    v11 = 0;
    if ( *((int *)v10 + 9) > 0 )
    {
      do
      {
        v12 = *((_DWORD *)v10 + 12);
        v13 = *(_DWORD **)(v12 + 4 * v11);
        if ( !*v13 )
        {
          if ( Direct3D_ptDevice->lpVtbl->CreateIndexBuffer(
                 Direct3D_ptDevice,
                 *((_DWORD *)*v9 + 4) * *((_DWORD *)*v9 + 5),
                 *((_DWORD *)*v9 + 2) | (Direct3D_isHWTnL != 0 ? 0 : 0x10),
                 **v9,
                 *((enum _D3DPOOL *)*v9 + 3),
                 *(struct IDirect3DIndexBuffer8 ***)(v12 + 4 * v11)) )
          {
            goto LABEL_18;
          }
          v13[3] = 0;
          v13[5] = 0;
          v13[7] = 0;
          v13[6] = 1;
        }
        v10 = v9[1];
        ++v11;
      }
      while ( v11 < (int)(*((_DWORD *)v10 + 9)) );
      v8 = j;
      v7 = Batch_ptIBList;
    }
    ++v8;
  }
}

// source: b/4/pc/pc_batch.c:483  [size]
// attributes: thunk
void __cdecl Batch_RestoreCallback()
{
  Batch_SetModeCallback();
}

signed int Batch_GetVertexBufferDescription()
{
  struct QObjectVector_s *v0; // edi
  signed int i; // esi
  _DWORD *v2; // edx
  int v3; // eax
  int j; // ecx
  int v5; // eax
  struct QObjectVector_s *v6; // edi
  signed int result; // eax
  signed int k; // esi
  _DWORD *v9; // edx
  int v10; // eax
  int m; // ecx
  int v12; // eax

  v0 = Batch_ptVBList;
  for ( i = 0; i < (signed int)v0->nAllocated; ++i )
  {
    v2 = v0->papxElement[i];
    if ( v2 )
    {
      v3 = v2[1];
      for ( j = 0; j < (int)(*(_DWORD *)(v3 + 36)); ++j )
      {
        v5 = *(_DWORD *)(*(_DWORD *)(v3 + 48) + 4 * j);
        if ( v5 )
          *(_DWORD *)(v5 + 28) = 1;
        v3 = v2[1];
      }
    }
  }
  v6 = Batch_ptIBList;
  result = Batch_ptIBList->nAllocated;
  for ( k = 0; k < result; ++k )
  {
    v9 = v6->papxElement[k];
    if ( v9 )
    {
      v10 = v9[1];
      for ( m = 0; m < (int)(*(_DWORD *)(v10 + 36)); ++m )
      {
        v12 = *(_DWORD *)(*(_DWORD *)(v10 + 48) + 4 * m);
        if ( v12 )
          *(_DWORD *)(v12 + 24) = 1;
        v10 = v9[1];
      }
    }
    result = v6->nAllocated;
  }
  return result;
}

// source: b/4/pc/pc_batch.c:541  [size]
unsigned int *__cdecl Batch_Flush(unsigned int *pnHandler, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { unsigned int v7; };
    struct { char igi2_o1[20]; struct Batch_SetStatesContext_s tContext; };
    struct { char igi2_o2[36]; struct _D3DMATRIX tIdentity; };
    char igi2_extent[100];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  _DWORD *v2; // esi
  void (__cdecl *v3)(struct Batch_SetStatesContext_s *); // eax
  void (__cdecl *v4)(struct Batch_SetStatesContext_s *); // eax
  int v5; // eax
  int v6; // ecx

  v2 = (_DWORD *)*pnHandler;
  if ( *pnHandler )
  {
    *pnHandler = 0;
    (*(void (__stdcall **)(_DWORD))(*(_DWORD *)*v2 + 48))(*v2);
    (*(void (__stdcall **)(_DWORD))(**(_DWORD **)v2[2] + 48))(*(_DWORD *)v2[2]);
    if ( v2[5] && *(_DWORD *)(v2[2] + 20) )
    {
      igi2_frame.tContext.nNumVertices = v2[5];
      igi2_frame.tContext.nNumFaces = (int)(*(_DWORD *)(v2[2] + 20)) / 3;
      igi2_frame.tContext.nNumObjects = v2[6];
      igi2_frame.tContext.pxUserContext = pxContext;
      v3 = (void (__cdecl *)(struct Batch_SetStatesContext_s *))v2[8];
      if ( v3 )
        v3(&igi2_frame.tContext);
      Direct3D_tState.nHandle = *(_DWORD *)(*(_DWORD *)v2[1] + 24);
      Direct3D_ptDevice->lpVtbl->SetVertexShader(Direct3D_ptDevice, Direct3D_tState.nHandle);
      igi2_frame.v7 = *(_DWORD *)(*(_DWORD *)v2[1] + 20);
      Direct3D_tState.aptStreamData[0] = (struct IDirect3DVertexBuffer8 *)*v2;
      Direct3D_tState.anStride[0] = igi2_frame.v7;
      Direct3D_ptDevice->lpVtbl->SetStreamSource(Direct3D_ptDevice, 0, Direct3D_tState.aptStreamData[0], igi2_frame.v7);
      Direct3D_tState.ptIndexData = *(struct IDirect3DIndexBuffer8 **)v2[2];
      Direct3D_tState.nBaseVertexIndex = 0;
      Direct3D_ptDevice->lpVtbl->SetIndices(Direct3D_ptDevice, Direct3D_tState.ptIndexData, 0);
      memset(&igi2_frame.tIdentity.m[2][3], 0, 16);
      memset(&igi2_frame.tIdentity.m[1][2], 0, 16);
      memset(&igi2_frame.tIdentity.m[0][1], 0, 16);
      igi2_frame.tIdentity._44 = 1.0;
      igi2_frame.tIdentity._33 = 1.0;
      igi2_frame.tIdentity._22 = 1.0;
      igi2_frame.tIdentity._11 = 1.0;
      Direct3D_ptDevice->lpVtbl->SetTransform(Direct3D_ptDevice, (enum _D3DTRANSFORMSTATETYPE)256, &igi2_frame.tIdentity);
      Direct3D_ptDevice->lpVtbl->DrawIndexedPrimitive(
        Direct3D_ptDevice,
        D3DPT_TRIANGLELIST,
        v2[4],
        v2[5],
        *(_DWORD *)(v2[2] + 12),
        (int)(*(_DWORD *)(v2[2] + 20)) / 3);
      v4 = (void (__cdecl *)(struct Batch_SetStatesContext_s *))v2[9];
      if ( v4 )
        v4(&igi2_frame.tContext);
      v5 = v2[2];
      v2[4] += v2[5];
      *(_DWORD *)(v5 + 12) += (int)(*(_DWORD *)(v5 + 20));
      *(_DWORD *)(v2[2] + 28) = 0;
      pnHandler = (unsigned int *)v2[2];
      v2[8] = 0;
      pnHandler[8] = 0;
      v6 = v2[2];
      v2[9] = 0;
      *(_DWORD *)(v6 + 20) = 0;
      v2[5] = 0;
      v2[6] = 0;
    }
    else
    {
      *(_DWORD *)(v2[2] + 28) = 0;
      pnHandler = (unsigned int *)v2[2];
      v2[8] = 0;
      pnHandler[8] = 0;
      v2[9] = 0;
    }
  }
  return pnHandler;
}

// source: b/4/pc/pc_batch.c:634  [size~]
int __cdecl Batch_GetLockedVertex(
        enum Batch_DynamicVertexBuffer_e iVertexFormat,
        enum Batch_DynamicIndexBuffer_e iIndexFormat,
        int nVerticesToAdd,
        int nFacesToAdd,
        int nObjectsToAdd,
        void *pxSourceIndex,
        int iStartVertex,
        void (__cdecl *pfCallback)(struct Batch_SetStatesContext_s *),
        void (__cdecl *pfUnsetCallback)(struct Batch_SetStatesContext_s *),
        void *pxContext,
        unsigned __int8 **ppxLockedVertex,
        int *pnOffset,
        unsigned int *pnHandler)
{
  struct Batch_VBChain_t *v14; // edi
  struct Batch_IBChain_t *v15; // ebp
  struct Batch_VertexBuffer_t *VertexBuffer; // esi
  struct Batch_IndexBuffer_t *IndexBuffer; // eax
  int iPosition; // edx
  struct Batch_IndexBuffer_t *v19; // ebp
  int v20; // ecx
  int v21; // ecx
  void (__cdecl *v22)(struct Batch_SetStatesContext_s *); // eax
  __int16 *v23; // edi
  bool v24; // zf
  enum _D3DFORMAT eFormat; // eax
  int v26; // eax
  char *v27; // edx
  int v28; // edi
  int v29; // ebx
  int v30; // ebx
  int v31; // eax
  __int16 *v32; // ecx
  __int16 v33; // di
  int v34; // edx
  int nBatchedIndices; // eax
  int v36; // eax
  unsigned __int8 **v37; // ecx
  unsigned int *v38; // ecx
  int v39; // edx
  int v40; // eax
  int v41; // edi
  int v42; // ecx
  int result; // eax
  struct Batch_IndexBuffer_t *ptIndexBuffer; // ecx
  int v45; // [esp+28h] [ebp-8h]
  struct Batch_IBChain_t *iVertexFormata = *(struct Batch_IBChain_t * *)&iVertexFormat; // [esp+34h] [ebp+4h] ARGSLOT
  enum Batch_DynamicVertexBuffer_e iVertexFormatb = *(enum Batch_DynamicVertexBuffer_e *)&iVertexFormat; // [esp+34h] [ebp+4h] ARGSLOT

  v45 = 3 * nFacesToAdd;
  v14 = (struct Batch_VBChain_t *)Batch_ptVBList->papxElement[iVertexFormat];
  v15 = (struct Batch_IBChain_t *)Batch_ptIBList->papxElement[iIndexFormat];
  iVertexFormata = v15;
  VertexBuffer = Batch_GetVertexBuffer(v14, pfCallback);
  IndexBuffer = Batch_GetIndexBuffer(v15, pfCallback);
  iPosition = VertexBuffer->iPosition;
  v19 = IndexBuffer;
  v20 = nVerticesToAdd + VertexBuffer->nBatchedVertices;
  VertexBuffer->ptIndexBuffer = IndexBuffer;
  if ( iPosition + v20 > v14->ptDesc->nMaxVertices
    || (v21 = v45, v45 + IndexBuffer->iPosition + IndexBuffer->nBatchedIndices > iVertexFormata->ptDesc->nMaxIndices) )
  {
    iIndexFormat = (enum Batch_DynamicIndexBuffer_e)VertexBuffer;
    Batch_Flush((unsigned int *)&iIndexFormat, pxContext);
    v22 = pfUnsetCallback;
    VertexBuffer->iPosition = 0;
    v19->iPosition = 0;
    VertexBuffer->pfUnsetStates = pfCallback;
    v19->pfUnsetStates = pfCallback;
    VertexBuffer[1].ptVertexBuffer = (struct IDirect3DVertexBuffer8 *)v22;
    v19[1].ptIndexBuffer = (struct IDirect3DIndexBuffer8 *)v22;
    VertexBuffer->ptVertexBuffer->lpVtbl->Lock(
      VertexBuffer->ptVertexBuffer,
      0,
      0,
      &VertexBuffer->pxLockedVertices,
      0x2000u);
    v19->ptIndexBuffer->lpVtbl->Lock(v19->ptIndexBuffer, 0, 0, &v19->pxLockedIndices, 0x2000u);
    v21 = v45;
  }
  VertexBuffer->ptChainHead = v14;
  v23 = (__int16 *)pxSourceIndex;
  v24 = pxSourceIndex == nullptr;
  VertexBuffer->ptIndexBuffer = v19;
  v19->ptChainHead = iVertexFormata;
  if ( !v24 )
  {
    eFormat = iVertexFormata->ptDesc->eFormat;
    if ( eFormat == D3DFMT_INDEX32 )
    {
      v26 = (int)&v19->pxLockedIndices[4 * v19->iPosition + 4 * v19->nBatchedIndices];
      if ( v21 > 0 )
      {
        v27 = (char *)v23 - v26;
        v28 = v21;
        do
        {
          v29 = *(_DWORD *)&v27[v26] - iStartVertex;
          v26 += 4;
          --v28;
          *(_DWORD *)(v26 - 4) = VertexBuffer->iPosition + VertexBuffer->nBatchedVertices + v29;
        }
        while ( v28 );
      }
    }
    else if ( eFormat == D3DFMT_INDEX16 )
    {
      v30 = (int)&v19->pxLockedIndices[2 * v19->iPosition + 2 * v19->nBatchedIndices];
      v31 = v21 / 2;
      if ( v21 / 2 > 0 )
      {
        v32 = v23;
        iIndexFormat = v30 - (_DWORD)v23;
        iVertexFormatb = v31;
        do
        {
          v33 = *v32;
          v34 = ((unsigned __int16)v32[1] + VertexBuffer->nBatchedVertices + VertexBuffer->iPosition - iStartVertex) << 16;
          v32 += 2;
          *(_DWORD *)((char *)v32 + iIndexFormat - 4) = (unsigned __int16)(VertexBuffer->nBatchedVertices
                                                                         + LOWORD(VertexBuffer->iPosition)
                                                                         + v33
                                                                         - iStartVertex)
                                                      ^ v34;
          --iVertexFormatb;
        }
        while ( iVertexFormatb );
        v21 = v45;
        v23 = (__int16 *)pxSourceIndex;
      }
      if ( (v21 & 1) != 0 )
        *(_WORD *)(v30 + 2 * v21 - 2) = LOWORD(VertexBuffer->iPosition)
                                      + LOWORD(VertexBuffer->nBatchedVertices)
                                      - iStartVertex
                                      + v23[v21 - 1];
    }
  }
  nBatchedIndices = v19->nBatchedIndices;
  v19->nOffset = nBatchedIndices + v19->iPosition;
  v36 = v21 + nBatchedIndices;
  v37 = ppxLockedVertex;
  v19->nBatchedIndices = v36;
  *v37 = VertexBuffer->pxLockedVertices;
  v38 = pnHandler;
  *pnOffset = VertexBuffer->iPosition + VertexBuffer->nBatchedVertices;
  v39 = nVerticesToAdd;
  v40 = nObjectsToAdd;
  *v38 = (unsigned int)VertexBuffer;
  v41 = v39 + VertexBuffer->nBatchedVertices;
  v42 = v40 + VertexBuffer->nBatchedObjects;
  result = (int)pfUnsetCallback;
  VertexBuffer->nBatchedObjects = v42;
  ptIndexBuffer = VertexBuffer->ptIndexBuffer;
  VertexBuffer->nBatchedVertices = v41;
  ptIndexBuffer[1].ptIndexBuffer = (struct IDirect3DIndexBuffer8 *)result;
  VertexBuffer[1].ptVertexBuffer = (struct IDirect3DVertexBuffer8 *)result;
  return result;
}

// source: b/4/pc/pc_batch.c:782  [size]
void __cdecl Batch_Open()
{
  struct QObjectVector_s *v0; // esi
  struct QObjectVector_s *v1; // esi
  struct Batch_VBDescription_t *v2; // esi
  struct QObjectVector_s *v3; // ebx
  unsigned int *p_nAllocated; // ebp
  struct Batch_VBDescription_t **v5; // ebx
  struct Batch_VBDescription_t *v6; // eax
  struct QObjectVector_s *v7; // esi
  unsigned int *v8; // ebx
  struct Batch_IBDescription_t **v9; // esi
  struct Batch_IBDescription_t *v10; // eax
  int v11; // eax
  struct DisplayCallbackChain_s *v12; // edx
  int v13; // eax
  struct DisplayCallbackChain_s *v14; // edx
  int v15; // eax
  struct DisplayCallbackChain_s *v16; // edx
  int v17; // eax
  struct DisplayCallbackChain_s *v18; // edx
  int v19; // eax

  v0 = (struct QObjectVector_s *)Mem_AllocFn(52, 4);
  v0->isStrictOrder = false;
  v0->nSize = 0;
  v0->nAllocated = 0;
  v0->nReallocSize = 1;
  v0->papxElement = nullptr;
  v0->nElementSize = 12;
  v0->tMemPool.nBlocks = 0;
  v0->tMemPool.nAllocatedBlocks = 0;
  v0->tMemPool.nAlignment = 4;
  v0->tMemPool.nBlockSize = 12;
  v0->tMemPool.nReAllocBlocks = 1;
  v0->tMemPool.tMemPoolFreeList.ptHead = nullptr;
  v0->tMemPool.tMemPoolSegmentList.ptHead = nullptr;
  MemPool_ReAlloc(&v0->tMemPool, 5u);
  QObjectVector_Realloc(v0, 5u);
  Batch_ptVBList = v0;
  v1 = (struct QObjectVector_s *)Mem_AllocFn(52, 4);
  v1->isStrictOrder = false;
  v1->nSize = 0;
  v1->nAllocated = 0;
  v1->nReallocSize = 1;
  v1->papxElement = nullptr;
  v1->nElementSize = 12;
  v1->tMemPool.nBlocks = 0;
  v1->tMemPool.nAllocatedBlocks = 0;
  v1->tMemPool.nAlignment = 4;
  v1->tMemPool.nBlockSize = 12;
  v1->tMemPool.nReAllocBlocks = 1;
  v1->tMemPool.tMemPoolFreeList.ptHead = nullptr;
  v1->tMemPool.tMemPoolSegmentList.ptHead = nullptr;
  MemPool_ReAlloc(&v1->tMemPool, 1u);
  QObjectVector_Realloc(v1, 1u);
  Batch_ptIBList = v1;
  v2 = Batch_atPredefinedVBFormats;
  do
  {
    v3 = Batch_ptVBList;
    p_nAllocated = &Batch_ptVBList->nAllocated;
    if ( Batch_ptVBList->nAllocated == Batch_ptVBList->nSize )
      QObjectVector_Realloc(Batch_ptVBList, Batch_ptVBList->nReallocSize);
    v5 = (struct Batch_VBDescription_t **)v3->papxElement[(*p_nAllocated)++];
    *v5 = v2;
    v6 = (struct Batch_VBDescription_t *)Mem_AllocFn(52, 4);
    ++v2;
    v6[1].eFormat = D3DFMT_UNKNOWN;
    v6[1].ePool = D3DPOOL_DEFAULT;
    v6[1].bUsage = 0;
    v6[1].nMaxVertices = 1;
    v6[1].nStride = 0;
    v6[1].eType = 44;
    v6->bUsage = 0;
    v6->eType = 0;
    v6->eFormat = 4;
    v6->nMaxVertices = 44;
    v6->ePool = D3DPOOL_MANAGED;
    v6->nStride = 0;
    v6->bFVF = 0;
    v5[1] = v6;
  }
  while ( (int)v2 < 7013556 );
  v7 = Batch_ptIBList;
  v8 = &Batch_ptIBList->nAllocated;
  if ( Batch_ptIBList->nAllocated == Batch_ptIBList->nSize )
    QObjectVector_Realloc(Batch_ptIBList, Batch_ptIBList->nReallocSize);
  v9 = (struct Batch_IBDescription_t **)v7->papxElement[(*v8)++];
  *v9 = Batch_atPredefinedIBFormats;
  v10 = (struct Batch_IBDescription_t *)Mem_AllocFn(52, 4);
  v10[1].eType = 0;
  v10[1].nMaxIndices = 0;
  v10[1].ePool = D3DPOOL_DEFAULT;
  v10[1].nStride = 1;
  v10[2].eFormat = D3DFMT_UNKNOWN;
  v10[1].bUsage = 40;
  v10->bUsage = 0;
  v10->eType = 0;
  v10->eFormat = 4;
  v10->nMaxIndices = 40;
  v10->ePool = D3DPOOL_MANAGED;
  v10->nStride = 0;
  v10[1].eFormat = D3DFMT_UNKNOWN;
  v9[1] = v10;
  v11 = 0;
  while ( Direct3D_atCallback[v11].pfCallback )
  {
    if ( ++v11 >= 32 )
    {
LABEL_10:
      LDebug_Error("No more Direct3D callbacks available.");
      goto LABEL_11;
    }
  }
  v12 = Direct3D_ptSetModeCallback;
  Direct3D_atCallback[v11].pfCallback = Batch_SetModeCallback;
  Direct3D_atCallback[v11].ptNext = v12;
  Direct3D_ptSetModeCallback = (struct DisplayCallbackChain_s *)(8 * v11 + 139166048);
  v13 = 0;
  while ( Direct3D_atCallback[v13].pfCallback )
  {
    if ( ++v13 >= 32 )
      goto LABEL_10;
  }
  v14 = Direct3D_ptUnsetModeCallback;
  Direct3D_atCallback[v13].pfCallback = Batch_UnsetModeCallback;
  Direct3D_atCallback[v13].ptNext = v14;
  Direct3D_ptUnsetModeCallback = (struct DisplayCallbackChain_s *)(8 * v13 + 139166048);
  v15 = 0;
  while ( Direct3D_atCallback[v15].pfCallback )
  {
    if ( ++v15 >= 32 )
      goto LABEL_10;
  }
  v16 = Direct3D_ptRestoreCallback;
  Direct3D_atCallback[v15].pfCallback = Batch_RestoreCallback;
  Direct3D_atCallback[v15].ptNext = v16;
  Direct3D_ptRestoreCallback = (struct DisplayCallbackChain_s *)(8 * v15 + 139166048);
  v17 = 0;
  while ( Direct3D_atCallback[v17].pfCallback )
  {
    if ( ++v17 >= 32 )
      goto LABEL_10;
  }
  v18 = Direct3D_ptDestroyCallback;
  Direct3D_atCallback[v17].pfCallback = Batch_DestroyCallback;
  Direct3D_atCallback[v17].ptNext = v18;
  Direct3D_ptDestroyCallback = (struct DisplayCallbackChain_s *)(8 * v17 + 139166048);
  v19 = 0;
  while ( Display_atCallback[v19].pfCallback )
  {
    if ( ++v19 >= 32 )
    {
      LDebug_Error("No more Display callbacks available.");
LABEL_11:
      abort();
    }
  }
  Display_atCallback[v19].ptNext = Display_ptStartFrameCallback;
  Display_atCallback[v19].pfCallback = (void (__cdecl *)())Batch_GetVertexBufferDescription;
  Display_ptStartFrameCallback = (struct DisplayCallbackChain_s *)(8 * v19 + 137688704);
}

// source: b/4/pc/pc_batch.c:820  [size]
void __cdecl Batch_Close()
{
  signed int i; // esi
  signed int j; // esi
  struct DisplayCallbackChain_s *v2; // eax
  struct DisplayCallbackChain_s *v3; // ecx
  struct DisplayCallbackChain_s *v4; // eax
  struct DisplayCallbackChain_s *v5; // ecx
  struct DisplayCallbackChain_s *v6; // eax
  struct DisplayCallbackChain_s *v7; // ecx
  struct DisplayCallbackChain_s *v8; // eax
  struct DisplayCallbackChain_s *v9; // ecx
  struct DisplayCallbackChain_s *v10; // eax
  struct DisplayCallbackChain_s *v11; // ecx

  for ( i = Batch_ptVBList->nAllocated - 1; i >= 0; --i )
    QObjectVector_Delete(*((struct QObjectVector_s **)Batch_ptVBList->papxElement[i] + 1));
  QObjectVector_Delete(Batch_ptVBList);
  for ( j = Batch_ptIBList->nAllocated - 1; j >= 0; --j )
    QObjectVector_Delete(*((struct QObjectVector_s **)Batch_ptIBList->papxElement[j] + 1));
  QObjectVector_Delete(Batch_ptIBList);
  v2 = Display_ptStartFrameCallback;
  v3 = nullptr;
  if ( Display_ptStartFrameCallback )
  {
    while ( (signed int (*)())v2->pfCallback != Batch_GetVertexBufferDescription )
    {
      v3 = v2;
      v2 = v2->ptNext;
      if ( !v2 )
        goto LABEL_12;
    }
    if ( v3 )
      v3->ptNext = v2->ptNext;
    else
      Display_ptStartFrameCallback = v2->ptNext;
  }
LABEL_12:
  v4 = Direct3D_ptSetModeCallback;
  v5 = nullptr;
  if ( Direct3D_ptSetModeCallback )
  {
    while ( v4->pfCallback != Batch_SetModeCallback )
    {
      v5 = v4;
      v4 = v4->ptNext;
      if ( !v4 )
        goto LABEL_19;
    }
    if ( v5 )
      v5->ptNext = v4->ptNext;
    else
      Direct3D_ptSetModeCallback = v4->ptNext;
  }
LABEL_19:
  v6 = Direct3D_ptUnsetModeCallback;
  v7 = nullptr;
  if ( Direct3D_ptUnsetModeCallback )
  {
    while ( v6->pfCallback != Batch_UnsetModeCallback )
    {
      v7 = v6;
      v6 = v6->ptNext;
      if ( !v6 )
        goto LABEL_26;
    }
    if ( v7 )
      v7->ptNext = v6->ptNext;
    else
      Direct3D_ptUnsetModeCallback = v6->ptNext;
  }
LABEL_26:
  v8 = Direct3D_ptRestoreCallback;
  v9 = nullptr;
  if ( Direct3D_ptRestoreCallback )
  {
    while ( v8->pfCallback != Batch_RestoreCallback )
    {
      v9 = v8;
      v8 = v8->ptNext;
      if ( !v8 )
        goto LABEL_33;
    }
    if ( v9 )
      v9->ptNext = v8->ptNext;
    else
      Direct3D_ptRestoreCallback = v8->ptNext;
  }
LABEL_33:
  v10 = Direct3D_ptDestroyCallback;
  v11 = nullptr;
  if ( Direct3D_ptDestroyCallback )
  {
    while ( v10->pfCallback != Batch_DestroyCallback )
    {
      v11 = v10;
      v10 = v10->ptNext;
      if ( !v10 )
        return;
    }
    if ( v11 )
      v11->ptNext = v10->ptNext;
    else
      Direct3D_ptDestroyCallback = v10->ptNext;
  }
}
