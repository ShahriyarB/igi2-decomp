/* g/0/lz77.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: g/0/lz77.c:160  [anchor-mhash]
void __cdecl LZ77_InitTree(struct Tree_t *ptTree, __int16 nNode)
{
  struct Tree_t *v2; // eax

  memset(ptTree, 0, 0x3004u);
  ptTree[2048].nLargerChild = 0;
  v2 = &ptTree[nNode];
  ptTree[2048].nLargerChild = nNode;
  v2->nParent = 2048;
  v2->nLargerChild = 0;
  v2->nSmallerChild = 0;
}

// source: g/0/lz77.c:185  [anchor-mhash]
void __cdecl LZ77_ContractNode(struct Tree_t *ptTree, __int16 nOldNode, __int16 nNewNode)
{
  struct Tree_t *v3; // eax
  bool v4; // zf
  struct Tree_t *v5; // ecx

  v3 = &ptTree[nOldNode];
  ptTree[nNewNode].nParent = v3->nParent;
  v4 = ptTree[v3->nParent].nLargerChild == (unsigned __int16)nOldNode;
  v5 = &ptTree[v3->nParent];
  if ( v4 )
    v5->nLargerChild = nNewNode;
  else
    v5->nSmallerChild = nNewNode;
  v3->nParent = 0;
}

// source: g/0/lz77.c:215  [anchor-mhash]
struct Tree_t *__cdecl LZ77_ReplaceNode(
        struct Tree_t *ptTree,
        __int16 nOldNode,
        __int16 nNewNode)
{
  struct Tree_t *v4; // edx
  struct Tree_t *v5; // ecx
  struct Tree_t *v6; // ebx

  v4 = &ptTree[nOldNode];
  v5 = &ptTree[v4->nParent];
  if ( v5->nSmallerChild == nOldNode )
    v5->nSmallerChild = nNewNode;
  else
    v5->nLargerChild = nNewNode;
  v6 = &ptTree[nNewNode];
  *(_DWORD *)&v6->nParent = *(_DWORD *)&v4->nParent;
  v6->nLargerChild = v4->nLargerChild;
  ptTree[v6->nSmallerChild].nParent = nNewNode;
  ptTree[v6->nLargerChild].nParent = nNewNode;
  v4->nParent = 0;
  return ptTree;
}

// source: g/0/lz77.c:251  [anchor-mhash]
int __cdecl LZ77_FindNextNode(struct Tree_t *ptTree, __int16 nNode)
{
  __int16 nSmallerChild; // dx
  __int16 i; // ax

  nSmallerChild = ptTree[nNode].nSmallerChild;
  for ( i = ptTree[nSmallerChild].nLargerChild; i; i = ptTree[i].nLargerChild )
    nSmallerChild = i;
  return nSmallerChild;
}

// source: g/0/lz77.c:282  [anchor-mhash]
void __cdecl LZ77_DeleteString(struct Tree_t *ptTree, __int16 nDelNode)
{
  struct Tree_t *v2; // eax
  __int16 nLargerChild; // di
  __int16 NextNode; // si

  v2 = &ptTree[nDelNode];
  if ( v2->nParent )
  {
    nLargerChild = v2->nLargerChild;
    if ( !nLargerChild )
    {
      nLargerChild = v2->nSmallerChild;
LABEL_4:
      LZ77_ContractNode(ptTree, nDelNode, nLargerChild);
      return;
    }
    if ( !v2->nSmallerChild )
      goto LABEL_4;
    NextNode = LZ77_FindNextNode(ptTree, nDelNode);
    LZ77_DeleteString(ptTree, NextNode);
    LZ77_ReplaceNode(ptTree, nDelNode, NextNode);
  }
}

// source: g/0/lz77.c:328  [anchor-mhash]
int __cdecl LZ77_AddString(
        struct Tree_t *ptTree,
        unsigned __int8 *paxWindow,
        __int16 nNewNode,
        __int16 *pnMatchPosition)
{
  int result; // eax
  __int16 nLargerChild; // cx
  int v6; // esi
  __int16 v7; // bx
  int v8; // ecx
  __int16 *p_nSmallerChild; // eax
  struct Tree_t *v10; // eax
  struct Tree_t *v11; // esi
  struct Tree_t *v12; // ecx
  struct Tree_t *v13; // ecx
  __int16 v14; // [esp+0h] [ebp-Ch]
  __int16 nTestNode; // [esp+4h] [ebp-8h]
  int nMatchLength; // [esp+8h] [ebp-4h]

  if ( !nNewNode )
    return 0;
  nLargerChild = ptTree[2048].nLargerChild;
  nMatchLength = 0;
  while ( 1 )
  {
    v6 = nLargerChild;
    nTestNode = nLargerChild;
    result = 0;
    v14 = nNewNode;
    v7 = nLargerChild;
    do
    {
      v8 = paxWindow[v14 & 0x7FF] - paxWindow[v7 & 0x7FF];
      if ( v8 )
        break;
      v8 = paxWindow[(nNewNode + (_WORD)result + 1) & 0x7FF] - paxWindow[((_WORD)v6 + (_WORD)result + 1) & 0x7FF];
      if ( v8 )
      {
        ++result;
        break;
      }
      v8 = paxWindow[(nNewNode + (_WORD)result + 2) & 0x7FF] - paxWindow[((_WORD)v6 + (_WORD)result + 2) & 0x7FF];
      if ( v8 )
      {
        result += 2;
        break;
      }
      v8 = paxWindow[(nNewNode + (_WORD)result + 3) & 0x7FF] - paxWindow[((_WORD)v6 + (_WORD)result + 3) & 0x7FF];
      if ( v8 )
      {
        result += 3;
        break;
      }
      v8 = paxWindow[(nNewNode + (_WORD)result + 4) & 0x7FF] - paxWindow[((_WORD)v6 + (_WORD)result + 4) & 0x7FF];
      if ( v8 )
      {
        result += 4;
        break;
      }
      v8 = paxWindow[(nNewNode + (_WORD)result + 5) & 0x7FF] - paxWindow[((_WORD)v6 + (_WORD)result + 5) & 0x7FF];
      if ( v8 )
      {
        result += 5;
        break;
      }
      v8 = paxWindow[(nNewNode + (_WORD)result + 6) & 0x7FF] - paxWindow[((_WORD)v6 + (_WORD)result + 6) & 0x7FF];
      if ( v8 )
      {
        result += 6;
        break;
      }
      v8 = paxWindow[(nNewNode + (_WORD)result + 7) & 0x7FF] - paxWindow[((_WORD)v6 + (_WORD)result + 7) & 0x7FF];
      if ( v8 )
      {
        result += 7;
        break;
      }
      v8 = paxWindow[(nNewNode + (_WORD)result + 8) & 0x7FF] - paxWindow[((_WORD)v6 + (_WORD)result + 8) & 0x7FF];
      if ( v8 )
      {
        result += 8;
        break;
      }
      v8 = paxWindow[(nNewNode + (_WORD)result + 9) & 0x7FF] - paxWindow[((_WORD)v6 + (_WORD)result + 9) & 0x7FF];
      if ( v8 )
      {
        result += 9;
        break;
      }
      result += 10;
      v7 += 10;
      v14 += 10;
    }
    while ( result < 130 );
    if ( result >= nMatchLength )
    {
      nMatchLength = result;
      *pnMatchPosition = nTestNode;
      if ( result >= 130 )
        break;
    }
    if ( v8 < 0 )
      p_nSmallerChild = &ptTree[v6].nSmallerChild;
    else
      p_nSmallerChild = &ptTree[v6].nLargerChild;
    nLargerChild = *p_nSmallerChild;
    if ( !*p_nSmallerChild )
    {
      *p_nSmallerChild = nNewNode;
      v10 = &ptTree[nNewNode];
      v10->nParent = nTestNode;
      v10->nLargerChild = 0;
      v10->nSmallerChild = 0;
      return nMatchLength;
    }
  }
  v11 = &ptTree[nTestNode];
  v12 = &ptTree[v11->nParent];
  if ( v12->nSmallerChild == nTestNode )
    v12->nSmallerChild = nNewNode;
  else
    v12->nLargerChild = nNewNode;
  v13 = &ptTree[nNewNode];
  *(_DWORD *)&v13->nParent = *(_DWORD *)&v11->nParent;
  v13->nLargerChild = v11->nLargerChild;
  ptTree[v13->nSmallerChild].nParent = nNewNode;
  ptTree[v13->nLargerChild].nParent = nNewNode;
  v11->nParent = 0;
  return result;
}

// source: g/0/lz77.c:409  [anchor-mhash]
void __cdecl LZ77_Encode(
        void *pxSession,
        int nBytes,
        struct CompressBitStream_t *ptInput,
        struct CompressBitStream_t *ptOutputStream)
{
  #pragma pack(push, 1)
  union
  {
    struct { unsigned __int8 *pnInput; };
    struct { char igi2_o1[4]; int nLookAheadBytes; };
    struct { char igi2_o2[8]; int nMatchLength; };
    struct { char igi2_o3[12]; unsigned __int8 *paxWindow; };
    struct { char igi2_o4[16]; int nMatchPosition; };
    struct { char igi2_o5[20]; int v34; };
    char igi2_extent[24];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  unsigned __int8 *pxCurrent; // edi
  struct Tree_t *v5; // esi
  unsigned __int8 *v6; // ebp
  int i; // edx
  unsigned __int8 v8; // cl
  int v9; // edi
  int v10; // ebx
  int bMask; // ecx
  int v12; // edx
  int v13; // ecx
  struct CompressBitStream_t *v14; // eax
  __int16 v15; // bp
  __int16 nParent; // ax
  struct Tree_t *v17; // ebx
  __int16 nLargerChild; // dx
  __int16 nSmallerChild; // di
  struct Tree_t *v20; // eax
  __int16 j; // ax
  struct Tree_t *v22; // eax
  struct Tree_t *v23; // eax
  unsigned __int8 v24; // cl
  __int16 v25; // ax
  int v26; // ecx
  int v27; // esi
  int v28; // esi
  __int16 ptInputa = *(__int16 *)&ptInput; // [esp+30h] [ebp+Ch] ARGSLOT

  pxCurrent = ptInput->pxCurrent;
  v5 = (struct Tree_t *)Mem_AllocFn(12294, 4);
  v6 = (unsigned __int8 *)Mem_AllocFn(2048, 4);
  igi2_frame.paxWindow = v6;
  ptInputa = 1;
  for ( i = 0; i < 130; ++i )
  {
    if ( !nBytes )
      break;
    v8 = *pxCurrent++;
    v6[i + 1] = v8;
    --nBytes;
  }
  igi2_frame.pnInput = pxCurrent;
  memset(v5, 0, 0x3004u);
  v5[2048].nLargerChild = 0;
  v9 = 0;
  v5[2048].nLargerChild = 1;
  v10 = i;
  igi2_frame.nLookAheadBytes = i;
  v5[1].nParent = 2048;
  v5[1].nLargerChild = 0;
  v5[1].nSmallerChild = 0;
  igi2_frame.nMatchLength = 0;
  igi2_frame.nMatchPosition = 0;
  while ( igi2_frame.nLookAheadBytes > 0 )
  {
    if ( v9 > v10 )
    {
      igi2_frame.nMatchLength = v10;
      v9 = v10;
    }
    if ( v9 > 2 )
    {
      v13 = ptOutputStream->bMask >> 1;
      ptOutputStream->bMask = v13;
      if ( !v13 )
      {
        *ptOutputStream->pxCurrent++ = ptOutputStream->nRack;
        ptOutputStream->nRack = 0;
        ptOutputStream->bMask = 128;
      }
      v14 = Compress_OutputBits(ptOutputStream, (__int16)igi2_frame.nMatchPosition, 11);
      Compress_OutputBits(v14, v9 - 3, 7);
    }
    else
    {
      bMask = ptOutputStream->bMask;
      v12 = bMask | ptOutputStream->nRack;
      bMask >>= 1;
      v9 = 1;
      ptOutputStream->nRack = v12;
      ptOutputStream->bMask = bMask;
      if ( !bMask )
      {
        *ptOutputStream->pxCurrent++ = ptOutputStream->nRack;
        ptOutputStream->nRack = 0;
        ptOutputStream->bMask = 128;
      }
      Compress_OutputBits(ptOutputStream, v6[ptInputa], 8);
    }
    igi2_frame.v34 = v9;
    do
    {
      v15 = (ptInputa + 130) & 0x7FF;
      nParent = v5[v15].nParent;
      v17 = &v5[v15];
      if ( !nParent )
        goto LABEL_29;
      nLargerChild = v17->nLargerChild;
      if ( nLargerChild )
      {
        nSmallerChild = v17->nSmallerChild;
        if ( nSmallerChild )
        {
          for ( j = v5[nSmallerChild].nLargerChild; j; j = v5[j].nLargerChild )
            nSmallerChild = j;
          LZ77_DeleteString(v5, nSmallerChild);
          v22 = &v5[v17->nParent];
          if ( v22->nSmallerChild == v15 )
            v22->nSmallerChild = nSmallerChild;
          else
            v22->nLargerChild = nSmallerChild;
          v23 = &v5[nSmallerChild];
          *(_DWORD *)&v23->nParent = *(_DWORD *)&v17->nParent;
          v23->nLargerChild = v17->nLargerChild;
          v5[v23->nSmallerChild].nParent = nSmallerChild;
          v5[v23->nLargerChild].nParent = nSmallerChild;
          goto LABEL_28;
        }
      }
      else
      {
        nLargerChild = v17->nSmallerChild;
      }
      v5[nLargerChild].nParent = nParent;
      v20 = &v5[v17->nParent];
      if ( v20->nLargerChild == v15 )
        v20->nLargerChild = nLargerChild;
      else
        v20->nSmallerChild = nLargerChild;
LABEL_28:
      v17->nParent = 0;
LABEL_29:
      if ( nBytes )
      {
        v24 = *igi2_frame.pnInput++;
        --nBytes;
        igi2_frame.paxWindow[(ptInputa + 130) & 0x7FF] = v24;
      }
      else
      {
        --igi2_frame.nLookAheadBytes;
      }
      v25 = (ptInputa + 1) & 0x7FF;
      ptInputa = v25;
      if ( igi2_frame.nLookAheadBytes )
        igi2_frame.nMatchLength = LZ77_AddString(v5, igi2_frame.paxWindow, v25, (__int16 *)&igi2_frame.nMatchPosition);
      --igi2_frame.v34;
    }
    while ( igi2_frame.v34 );
    v10 = igi2_frame.nLookAheadBytes;
    v6 = igi2_frame.paxWindow;
    v9 = igi2_frame.nMatchLength;
  }
  v26 = ptOutputStream->bMask >> 1;
  ptOutputStream->bMask = v26;
  if ( !v26 )
  {
    *ptOutputStream->pxCurrent++ = ptOutputStream->nRack;
    ptOutputStream->nRack = 0;
    ptOutputStream->bMask = 128;
  }
  Compress_OutputBits(ptOutputStream, 0, 11);
  v27 = *(_DWORD *)((unsigned int)&v5[-1].nSmallerChild & 0xFFFFFFFC);
  --Mem_nCurrentAllocations;
  Node_Remove((_DWORD **)v27);
  memset(*(void **)(v27 + 8), 0xCDu, *(_DWORD *)(v27 + 16));
  free((void *)v27);
  if ( v6 )
  {
    v28 = *(_DWORD *)((unsigned int)(v6 - 4) & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v28);
    memset(*(void **)(v28 + 8), 0xCDu, *(_DWORD *)(v28 + 16));
    free((void *)v28);
  }
}

// source: g/0/lz77.c:517  [anchor-mhash]
void __cdecl LZ77_Decode(
        void *pxSession,
        struct CompressBitStream_t *ptInputStream,
        struct CompressBitStream_t *ptOutputStream)
{
  unsigned __int8 *pxCurrent; // edi
  _BYTE *v4; // eax
  _BYTE *v6; // ebp
  int v7; // esi
  int bMask; // eax
  unsigned __int8 *v9; // ecx
  int v10; // ecx
  int v11; // eax
  unsigned __int8 v12; // al
  unsigned int v13; // eax
  __int16 v14; // bx
  unsigned int v15; // eax
  bool v16; // sf
  signed int v17; // eax
  int v18; // ecx
  unsigned __int8 v19; // bl
  int v20; // esi
  __int16 ptInputStreama = *(__int16 *)&ptInputStream; // [esp+18h] [ebp+8h] ARGSLOT

  pxCurrent = ptOutputStream->pxCurrent;
  v4 = Mem_AllocFn(2048, 4);
  v6 = v4;
  v7 = 1;
  while ( 1 )
  {
    while ( 1 )
    {
      bMask = ptInputStream->bMask;
      if ( bMask == 128 )
      {
        v9 = ptInputStream->pxCurrent + 1;
        ptInputStream->nRack = *ptInputStream->pxCurrent;
        ptInputStream->pxCurrent = v9;
      }
      v10 = bMask & ptInputStream->nRack;
      v11 = bMask >> 1;
      ptInputStream->bMask = v11;
      if ( !v11 )
        ptInputStream->bMask = 128;
      if ( !v10 )
        break;
      v12 = Compress_InputBits(ptInputStream, 8);
      *pxCurrent++ = v12;
      v6[v7] = v12;
      v7 = ((_WORD)v7 + 1) & 0x7FF;
    }
    v13 = Compress_InputBits(ptInputStream, 11);
    v14 = v13;
    ptInputStreama = v13;
    if ( !v13 )
      break;
    v15 = Compress_InputBits(ptInputStream, 7);
    v16 = (int)(v15 + 2) < 0;
    v17 = v15 + 2;
    v18 = 0;
    if ( !v16 )
    {
      while ( 1 )
      {
        v19 = v6[((_WORD)v18 + v14) & 0x7FF];
        *pxCurrent++ = v19;
        v6[v7] = v19;
        v7 = ((_WORD)v7 + 1) & 0x7FF;
        if ( ++v18 > v17 )
          break;
        v14 = ptInputStreama;
      }
    }
  }
  ptOutputStream->pxCurrent = pxCurrent;
  if ( v6 )
  {
    v20 = *(_DWORD *)((unsigned int)(v6 - 4) & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v20);
    memset(*(void **)(v20 + 8), 0xCDu, *(_DWORD *)(v20 + 16));
    free((void *)v20);
  }
}

// source: g/0/lz77.c:583  [size]
void __cdecl LZ77_Open()
{
  Compress_aptAlgorithm[0] = &LZ77_tAlgorithm;
}

// source: g/0/lz77.c:597  [size]
void __cdecl LZ77_Close()
{
  ;
}
