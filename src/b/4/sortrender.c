/* b/4/sortrender.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: b/4/sortrender.c:107  [anchor-hash]
void __cdecl SortRender_BucketSort(struct SortRenderItem_t *ptItemList, int nItem)
{
  #pragma pack(push, 1)
  union
  {
    struct { _BYTE v20[12]; };
    struct { char igi2_o1[12]; int anBucket[1024]; };
    struct { char igi2_o2[4108]; struct SortRenderItem_t *ptTempList; };
    struct { char igi2_o3[4112]; int v23; };
    struct { char igi2_o4[4116]; struct SortRenderItem_t *ptDestList; };
    struct { char igi2_o5[4120]; struct SortRenderItem_t *ptSourceList; };
    struct { char igi2_o6[4124]; unsigned int nKey; };
    char igi2_extent[4128];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  signed int v2; // ebx
  unsigned int *p_vZ; // edx
  int v4; // edi
  unsigned int v5; // eax
  int v6; // esi
  int *v7; // ecx
  int *v8; // edx
  int v9; // esi
  int v10; // ecx
  int v11; // edi
  int v12; // eax
  void *v13; // esp
  struct SortRenderItem_t *v14; // esi
  struct SortRenderItem_t *v15; // edi
  int *v16; // edx
  int v17; // eax
  struct SortRenderItem_t *v18; // ecx
  bool v19; // zf
  char ptItemLista = *(char *)&ptItemList; // [esp+1028h] [ebp+8h] ARGSLOT

  v2 = nItem;
  memset(igi2_frame.anBucket, 0, sizeof(igi2_frame.anBucket));
  if ( nItem > 0 )
  {
    p_vZ = (unsigned int *)&ptItemList->vZ;
    v4 = nItem;
    do
    {
      v5 = *p_vZ;
      igi2_frame.nKey = *p_vZ;
      if ( (igi2_frame.nKey & 0x80000000) == 0 )
      {
        v5 ^= 0x7FFFFFFFu;
        igi2_frame.nKey = v5;
      }
      ++igi2_frame.anBucket[(unsigned __int8)v5];
      ++igi2_frame.anBucket[BYTE1(v5) + 256];
      v6 = igi2_frame.anBucket[BYTE2(igi2_frame.nKey) + 512];
      v7 = &igi2_frame.anBucket[BYTE2(igi2_frame.nKey) + 512];
      *p_vZ = v5;
      *v7 = v6 + 1;
      p_vZ += 3;
      --v4;
      ++igi2_frame.anBucket[HIBYTE(v5) + 768];
    }
    while ( v4 );
  }
  v8 = igi2_frame.anBucket;
  v9 = 4;
  do
  {
    v10 = 0;
    v11 = 256;
    do
    {
      v12 = *v8;
      *v8++ = v10;
      --v11;
      v10 += v12;
    }
    while ( v11 );
    --v9;
  }
  while ( v9 );
  v13 = alloca(12 * nItem);
  v14 = ptItemList;
  v15 = (struct SortRenderItem_t *)v13;
  igi2_frame.ptTempList = (struct SortRenderItem_t *)v13;
  igi2_frame.ptSourceList = ptItemList;
  igi2_frame.ptDestList = (struct SortRenderItem_t *)v13;
  v16 = igi2_frame.anBucket;
  ptItemLista = 0;
  igi2_frame.v23 = 4;
  do
  {
    if ( v2 > 0 )
    {
      igi2_frame.nKey = v2;
      while ( 1 )
      {
        v17 = (unsigned __int8)(SLODWORD(v14->vZ) >> ptItemLista);
        v18 = &v15[v16[v17]];
        v18->pfCallback = v14->pfCallback;
        v18->pxData = v14->pxData;
        v18->vZ = v14->vZ;
        ++v16[v17];
        ++v14;
        if ( !--igi2_frame.nKey )
          break;
        v15 = igi2_frame.ptTempList;
      }
      v2 = nItem;
      v14 = igi2_frame.ptSourceList;
    }
    v15 = v14;
    v14 = igi2_frame.ptDestList;
    v16 += 256;
    v19 = igi2_frame.v23 == 1;
    igi2_frame.ptTempList = v15;
    igi2_frame.ptSourceList = igi2_frame.ptDestList;
    igi2_frame.ptDestList = v15;
    ptItemLista += 8;
    --igi2_frame.v23;
  }
  while ( !v19 );
}

// source: b/4/sortrender.c:231  [anchor-caller]
void __cdecl SortRender_DrawListPrimitive(struct SortRenderPrimitive_t *ptPrimitive)
{
  struct SortRenderList_t *ptSortRenderList; // edi
  struct SortRenderItem_t *atItem; // esi
  void (__cdecl *pfCallback)(void *); // eax
  int i; // ebx

  if ( ptPrimitive )
  {
    ptSortRenderList = ptPrimitive->ptSortRenderList;
    if ( ptSortRenderList->nNumItems )
    {
      atItem = ptSortRenderList->atItem;
      SortRender_BucketSort(ptSortRenderList->atItem, ptSortRenderList->nNumItems);
      pfCallback = ptSortRenderList->atItem[0].pfCallback;
      for ( i = 0; i < ptSortRenderList->nNumItems; ++atItem )
      {
        if ( atItem->pfCallback != pfCallback )
          pfCallback(nullptr);
        atItem->pfCallback(atItem->pxData);
        pfCallback = atItem->pfCallback;
        ++i;
      }
      pfCallback(nullptr);
      ptSortRenderList->nNumItems = 0;
    }
    SortRender_nBufferPos = 0;
  }
}

// source: b/4/sortrender.c:288  [anchor-mhash]
void *__cdecl SortRender_AllocItem(void (__cdecl *pfCallback)(void *), int nSize, float vZ)
{
  struct SortRenderList_t *v3; // edx
  int v4; // eax
  int v5; // ecx
  int v6; // eax

  v3 = SortRender_ptActiveList;
  v4 = SortRender_ptActiveList->nNumItems++;
  v5 = SortRender_nBufferPos;
  v6 = (int)&v3->atItem[v4];
  *(_DWORD *)(v6 + 4) = &SortRender_anSortBuffer[SortRender_nBufferPos];
  SortRender_nBufferPos = nSize + v5;
  *(_DWORD *)v6 = pfCallback;
  *(float *)(v6 + 8) = vZ;
  return *(void **)(v6 + 4);
}

// source: b/4/sortrender.c:385  [anchor-callee]
void __cdecl SortRender_DrawList(void *pxSortRenderList)
{
  _DWORD *v1; // esi
  int v2; // eax

  v1 = Primitive_ptNextFreePrimitive;
  Primitive_ptNextFreePrimitive = (char *)Primitive_ptNextFreePrimitive + 16;
  if ( (char *)Primitive_ptNextFreePrimitive - Primitive_asPrimitive[0] > (char *)Primitive_nMaxPrimitiveUsage )
  {
    Primitive_nMaxPrimitiveUsage = (unsigned int)Primitive_ptNextFreePrimitive - Primitive_asPrimitive[0];
    if ( (char *)Primitive_ptNextFreePrimitive - Primitive_asPrimitive[0] > (char *)dword_6B9E3C )
      v1 = nullptr;
  }
  v2 = SortRender_ePrimType;
  v1[1] = SortRender_ePrimType;
  v1[3] = pxSortRenderList;
  RenderMode_tActiveRenderMode.apfRenderModeMethod[v2](v1);
  dword_834E068 = (int)v1;
  SortRender_ptActiveList = nullptr;
  SortRender_isActive = 0;
}

// source: b/4/sortrender.c:407  [anchor-hash]
void *__cdecl SortRender_SetActiveList(void *pxSortRenderList)
{
  SortRender_ptActiveList = (struct SortRenderList_t *)pxSortRenderList;
  SortRender_isActive = 1;
  return pxSortRenderList;
}

// source: b/4/sortrender.c:422  [anchor-hash]
void __cdecl SortRender_Open()
{
  int v0; // eax
  _DWORD pxContext[2]; // [esp+0h] [ebp-8h] BYREF

  v0 = 0;
  while ( RenderMode_atRenderModeMethod[v0].isAllocated )
  {
    if ( ++v0 >= 128 )
    {
      LDebug_Error("RenderMode: Failed to create new method '%s'", "SortRender");
      abort();
    }
  }
  RenderMode_atRenderModeMethod[v0].zName = "SortRender";
  RenderMode_atRenderModeMethod[v0].isAllocated = 1;
  SortRender_ePrimType = v0;
  pxContext[0] = v0;
  pxContext[1] = SortRender_DrawListPrimitive;
  RenderMode_EnumerateRenderModes(
    (void (__cdecl *)(struct RenderModeEnumerateContext_s *, void *))Primitive_SetPrimitiveDrawCallback,
    pxContext);
}

// source: b/4/sortrender.c:437  [size]
void __cdecl SortRender_Close()
{
  RenderMode_atRenderModeMethod[SortRender_ePrimType].isAllocated = 0;
}
