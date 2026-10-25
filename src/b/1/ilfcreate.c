/* b/1/ilfcreate.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: b/1/ilfcreate.c:38  [anchor-hash]
__declspec(noreturn) void ILF_ParseError()
{
  LDebug_Error("Error in ILF file.");
  abort();
}

// source: b/1/ilfcreate.c:51  [anchor-callee]
unsigned int __cdecl ILF_UpdateAlignment(struct ILFContainerNode_s *ptContainer)
{
  struct ILFContainerNode_s *ptHead; // esi
  struct ILFContainerNode_s *ptNext; // ebx
  unsigned int updated; // edi
  unsigned int nAlignment; // esi

  ptHead = (struct ILFContainerNode_s *)ptContainer->tChunkNodeList.ptHead;
  ptNext = (struct ILFContainerNode_s *)ptHead->tChunk.ptNext;
  updated = 4;
  if ( ptHead->tChunk.ptNext )
  {
    do
    {
      if ( ptHead->tChunk.nAlignment < 4 )
        ptHead->tChunk.nAlignment = 4;
      if ( ptHead->tChunk.isContainer )
      {
        if ( updated <= ILF_UpdateAlignment(ptHead) )
          updated = ILF_UpdateAlignment(ptHead);
      }
      else
      {
        nAlignment = ptHead->tChunk.nAlignment;
        if ( updated <= nAlignment )
          updated = nAlignment;
      }
      ptHead = ptNext;
      ptNext = (struct ILFContainerNode_s *)ptNext->tChunk.ptNext;
    }
    while ( ptNext );
  }
  ptContainer->tChunk.nAlignment = updated;
  return updated;
}

// source: b/1/ilfcreate.c:89  [anchor-callee]
unsigned int __cdecl ILF_UpdateOffsets(struct ILFContainerNode_s *ptContainer, unsigned int nOffset)
{
  unsigned int nAlignment; // ecx
  struct ILFContainerNode_s *v3; // ebp
  struct ILFContainerNode_s *ptHead; // esi
  struct ILFContainerNode_s *ptNext; // edi
  unsigned int result; // eax
  unsigned int v7; // eax
  bool v8; // zf
  unsigned int v9; // ecx
  int v10; // eax
  unsigned int nSize; // ecx

  nAlignment = ptContainer->tChunk.nAlignment;
  ptContainer->tChunk.nChunkStart = nOffset;
  v3 = nullptr;
  ptHead = (struct ILFContainerNode_s *)ptContainer->tChunkNodeList.ptHead;
  ptContainer->tChunk.nDataOffset = 0;
  ptNext = (struct ILFContainerNode_s *)ptHead->tChunk.ptNext;
  result = ~(nAlignment - 1) & (nAlignment + nOffset + 19);
  if ( ptHead->tChunk.ptNext )
  {
    do
    {
      v7 = (result + 3) & 0xFFFFFFFC;
      v8 = ptHead->tChunk.isContainer == 0;
      v9 = ptHead->tChunk.nAlignment;
      ptHead->tChunk.nNext = 0;
      if ( v8 )
      {
        ptHead->tChunk.nChunkStart = v7;
        v10 = ~(v9 - 1) & (v9 + v7 + 15);
        nSize = ptHead->tChunk.nSize;
        ptHead->tChunk.nDataOffset = v10;
        result = nSize + v10;
      }
      else
      {
        result = ILF_UpdateOffsets(ptHead, ~(v9 - 1) & (v9 + v7 - 1));
      }
      if ( v3 )
        v3->tChunk.nNext = ptHead->tChunk.nChunkStart - v3->tChunk.nChunkStart;
      v3 = ptHead;
      ptHead = ptNext;
      ptNext = (struct ILFContainerNode_s *)ptNext->tChunk.ptNext;
    }
    while ( ptNext );
  }
  ptContainer->tChunk.nSize = result - nOffset;
  return result;
}

// source: b/1/ilfcreate.c:144  [anchor-callee]
unsigned int __cdecl ILF_WriteChunk(
        struct ILFChunkNode_s *ptChunk,
        unsigned int nOffset,
        struct File_s *ptFile)
{
  #pragma pack(push, 1)
  union
  {
    struct { unsigned __int8 nPad; };
    struct { char igi2_o1[1]; unsigned int nValue; };
    char igi2_extent[5];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  unsigned int v3; // ebx
  bool v5; // cf
  int eDeviceID; // eax
  int v7; // eax
  int v8; // eax
  int v9; // eax
  unsigned int v10; // ebx

  v3 = nOffset;
  if ( ptChunk->isContainer )
    return ILF_WriteContainer((struct ILFContainerNode_s *)ptChunk, nOffset, ptFile);
  v5 = nOffset < ptChunk->nChunkStart;
  igi2_frame.nPad = 0;
  if ( v5 )
  {
    do
    {
      File_atDevice[ptFile->eDeviceID].pfWrite(ptFile->eDeviceID, ptFile, &igi2_frame.nPad, 1u);
      File_atDevice[ptFile->eDeviceID].pfSync(ptFile->eDeviceID, ptFile, FILE_SYNC_WAIT);
      ++v3;
    }
    while ( v3 < ptChunk->nChunkStart );
  }
  eDeviceID = ptFile->eDeviceID;
  igi2_frame.nValue = ptChunk->nId;
  File_atDevice[eDeviceID].pfWrite(eDeviceID, ptFile, &igi2_frame.nValue, 4u);
  File_atDevice[ptFile->eDeviceID].pfSync(ptFile->eDeviceID, ptFile, FILE_SYNC_WAIT);
  v7 = ptFile->eDeviceID;
  igi2_frame.nValue = ptChunk->nSize;
  File_atDevice[v7].pfWrite(v7, ptFile, &igi2_frame.nValue, 4u);
  File_atDevice[ptFile->eDeviceID].pfSync(ptFile->eDeviceID, ptFile, FILE_SYNC_WAIT);
  v8 = ptFile->eDeviceID;
  igi2_frame.nValue = ptChunk->nAlignment;
  File_atDevice[v8].pfWrite(v8, ptFile, &igi2_frame.nValue, 4u);
  File_atDevice[ptFile->eDeviceID].pfSync(ptFile->eDeviceID, ptFile, FILE_SYNC_WAIT);
  v9 = ptFile->eDeviceID;
  igi2_frame.nValue = ptChunk->nNext;
  File_atDevice[v9].pfWrite(v9, ptFile, &igi2_frame.nValue, 4u);
  File_atDevice[ptFile->eDeviceID].pfSync(ptFile->eDeviceID, ptFile, FILE_SYNC_WAIT);
  v10 = v3 + 16;
  if ( ptChunk->nSize )
  {
    for ( ; v10 < ptChunk->nDataOffset; ++v10 )
    {
      File_atDevice[ptFile->eDeviceID].pfWrite(ptFile->eDeviceID, ptFile, &igi2_frame.nPad, 1u);
      File_atDevice[ptFile->eDeviceID].pfSync(ptFile->eDeviceID, ptFile, FILE_SYNC_WAIT);
    }
    File_atDevice[ptFile->eDeviceID].pfWrite(ptFile->eDeviceID, ptFile, ptChunk->pxData, ptChunk->nSize);
    v10 += ptChunk->nSize;
  }
  return v10;
}

// source: b/1/ilfcreate.c:204  [anchor-callee]
unsigned int __cdecl ILF_WriteContainer(
        struct ILFContainerNode_s *ptContainer,
        unsigned int nOffset,
        struct File_s *ptFile)
{
  unsigned int v3; // ebp
  struct File_s *v4; // esi
  struct ILFContainerNode_s *v5; // edi
  bool v6; // cf
  int eDeviceID; // eax
  int v8; // eax
  int v9; // eax
  int v10; // eax
  int v11; // eax
  struct ILFChunkNode_s *ptHead; // edi
  struct ILFChunkNode_s *ptNext; // ebx
  unsigned int i; // ebp
  unsigned int v15; // eax
  unsigned __int8 nPad; // [esp+13h] [ebp-1h] BYREF

  v3 = nOffset;
  v4 = ptFile;
  v5 = ptContainer;
  v6 = nOffset < ptContainer->tChunk.nChunkStart;
  nPad = 0;
  if ( v6 )
  {
    do
    {
      File_atDevice[v4->eDeviceID].pfWrite(v4->eDeviceID, v4, &nPad, 1u);
      File_atDevice[v4->eDeviceID].pfSync(v4->eDeviceID, v4, FILE_SYNC_WAIT);
      ++v3;
    }
    while ( v3 < v5->tChunk.nChunkStart );
  }
  eDeviceID = v4->eDeviceID;
  ptContainer = (struct ILFContainerNode_s *)v5->tChunk.nId;
  File_atDevice[eDeviceID].pfWrite(eDeviceID, v4, &ptContainer, 4u);
  File_atDevice[v4->eDeviceID].pfSync(v4->eDeviceID, v4, FILE_SYNC_WAIT);
  v8 = v4->eDeviceID;
  ptContainer = (struct ILFContainerNode_s *)v5->tChunk.nSize;
  File_atDevice[v8].pfWrite(v8, v4, &ptContainer, 4u);
  File_atDevice[v4->eDeviceID].pfSync(v4->eDeviceID, v4, FILE_SYNC_WAIT);
  v9 = v4->eDeviceID;
  ptContainer = (struct ILFContainerNode_s *)v5->tChunk.nAlignment;
  File_atDevice[v9].pfWrite(v9, v4, &ptContainer, 4u);
  File_atDevice[v4->eDeviceID].pfSync(v4->eDeviceID, v4, FILE_SYNC_WAIT);
  v10 = v4->eDeviceID;
  ptContainer = (struct ILFContainerNode_s *)v5->tChunk.nNext;
  File_atDevice[v10].pfWrite(v10, v4, &ptContainer, 4u);
  File_atDevice[v4->eDeviceID].pfSync(v4->eDeviceID, v4, FILE_SYNC_WAIT);
  v11 = v4->eDeviceID;
  ptContainer = (struct ILFContainerNode_s *)v5->nType;
  File_atDevice[v11].pfWrite(v11, v4, &ptContainer, 4u);
  File_atDevice[v4->eDeviceID].pfSync(v4->eDeviceID, v4, FILE_SYNC_WAIT);
  ptHead = v5->tChunkNodeList.ptHead;
  ptNext = ptHead->ptNext;
  for ( i = v3 + 20; ptNext; i = v15 )
  {
    v15 = ILF_WriteChunk(ptHead, i, v4);
    ptHead = ptNext;
    ptNext = ptNext->ptNext;
  }
  return i;
}

// source: b/1/ilfcreate.c:262  [anchor-callee]
struct ILFContainerNode_s *__cdecl ILF_NewContainterNode(unsigned int nId, unsigned int nType)
{
  struct ILFContainerNode_s *v2; // edx

  v2 = (struct ILFContainerNode_s *)Mem_AllocFn(56, 4);
  memset(v2, 0, sizeof(struct ILFContainerNode_s));
  v2->nType = nType;
  v2->tChunkNodeList.ptHead = (struct ILFChunkNode_s *)&v2->tChunkNodeList.ptMiddle;
  v2->tChunkNodeList.ptMiddle = nullptr;
  v2->tChunk.nId = 1179012169;
  v2->tChunk.isContainer = 1;
  v2->tChunkNodeList.ptTail = (struct ILFChunkNode_s *)&v2->tChunkNodeList;
  v2->tChunk.ptPrev = nullptr;
  v2->tChunk.ptNext = nullptr;
  return v2;
}

// source: b/1/ilfcreate.c:285  [anchor-mhash]
struct ILFChunkNode_s *__cdecl ILF_NewChunkNode(unsigned int nId)
{
  struct ILFChunkNode_s *v1; // edx

  v1 = (struct ILFChunkNode_s *)Mem_AllocFn(40, 4);
  memset(v1, 0, sizeof(struct ILFChunkNode_s));
  v1->nId = nId;
  v1->isContainer = 0;
  v1->ptPrev = nullptr;
  v1->ptNext = nullptr;
  return v1;
}

// source: b/1/ilfcreate.c:311  [size]
struct ILFChunkNode_s *__cdecl ILF_SetChunkData(
        struct ILFChunkNode_s *ptChunk,
        void *pxData,
        unsigned int nSize,
        unsigned int nAlignment)
{
  ptChunk->pxData = pxData;
  ptChunk->nSize = nSize;
  ptChunk->nAlignment = nAlignment;
  return ptChunk;
}

// source: b/1/ilfcreate.c:335  [size]
struct ILFChunkNode_s *__cdecl ILF_AddChunk(
        struct ILFContainerNode_s *ptContainer,
        struct ILFChunkNode_s *ptChunk)
{
  return (struct ILFChunkNode_s *)List_AddTail(ptChunk, (int)&ptContainer->tChunkNodeList);
}

// source: b/1/ilfcreate.c:350  [size]
// attributes: thunk
struct ILFChunkNode_s *__cdecl ILF_RemoveChunkNode(struct ILFChunkNode_s *ptChunk)
{
  return (struct ILFChunkNode_s *)Node_Remove(ptChunk);
}

// source: b/1/ilfcreate.c:364  [size]
// attributes: thunk
struct ILFContainerNode_s *__cdecl ILF_RemoveContainerNode(
        struct ILFContainerNode_s *ptContainer)
{
  return (struct ILFContainerNode_s *)Node_Remove(ptContainer);
}

// source: b/1/ilfcreate.c:381  [size]
struct ILFContainerNode_s *__cdecl ILF_AddContainer(
        struct ILFContainerNode_s *ptContainer,
        struct ILFContainerNode_s *ptContainerToAdd)
{
  return (struct ILFContainerNode_s *)List_AddTail(ptContainerToAdd, (int)&ptContainer->tChunkNodeList);
}

// source: b/1/ilfcreate.c:394  [anchor-caller]
struct ILFContainerNode_s *__cdecl ILF_Parse(void *pxBuffer)
{
  void *v1; // edi
  struct ILFContainerNode_s *v2; // eax
  unsigned int v3; // ecx
  struct ILFContainerNode_s *v4; // ebp
  int v5; // eax
  unsigned int v6; // eax
  int *v7; // esi
  int v8; // ebx
  struct ILFContainerNode_s *v9; // eax
  void *ChunkData; // ebp
  _DWORD *v11; // edx
  bool v12; // zf
  int v13; // eax
  int v14; // eax
  struct ILFContainerNode_s *ptNew; // [esp+10h] [ebp-4h]

  v1 = pxBuffer;
  if ( *(_DWORD *)pxBuffer != 1179012169 )
    return nullptr;
  v2 = ILF_NewContainterNode(0x46464C49u, *((_DWORD *)pxBuffer + 4));
  v3 = *((_DWORD *)pxBuffer + 1);
  v4 = v2;
  ptNew = v2;
  if ( !v3 )
    goto LABEL_7;
  v5 = *((_DWORD *)pxBuffer + 2);
  if ( (v5 & ~(v5 - 1)) != v5 )
  {
    ILF_nLastError = 1;
    goto LABEL_7;
  }
  v6 = ~(v5 - 1) & (v5 + 19);
  if ( v6 >= v3 )
  {
LABEL_7:
    v7 = nullptr;
    goto LABEL_8;
  }
  v7 = (int *)((char *)pxBuffer + v6);
LABEL_8:
  if ( ILF_nLastError )
  {
LABEL_9:
    LDebug_Error("Error in ILF file.");
    abort();
  }
  if ( v7 )
  {
    while ( 1 )
    {
      v8 = *v7;
      if ( *v7 == 1179012169 )
      {
        v9 = ILF_Parse(v7);
        if ( !v9 )
          goto LABEL_9;
        List_AddTail(v9, (int)&v4->tChunkNodeList);
      }
      else
      {
        ChunkData = ILF_GetChunkData(v7, v1);
        if ( ILF_nLastError )
          goto LABEL_9;
        v11 = Mem_AllocFn(40, 4);
        memset(v11, 0, 0x28u);
        v11[2] = v8;
        v12 = ILF_nLastError == 0;
        v11[8] = 0;
        v11[1] = 0;
        *v11 = 0;
        v13 = v7[1];
        if ( !v12 )
          goto LABEL_9;
        v11[5] = v7[2];
        v11[7] = v13;
        v11[9] = ChunkData;
        List_AddTail(v11, (int)&ptNew->tChunkNodeList);
        v1 = pxBuffer;
        v4 = ptNew;
      }
      v14 = v7[3];
      if ( v14 )
      {
        v7 = (int *)((char *)v7 + v14);
        if ( v7 )
          continue;
      }
      return v4;
    }
  }
  return v4;
}

// source: b/1/ilfcreate.c:480  [anchor-callee]
void __cdecl ILF_DeleteContainerNode(struct ILFContainerNode_s *ptContainer)
{
  struct ILFChunkNode_s *ptHead; // eax
  struct ILFChunkNode_s *i; // ebx
  struct ILFContainerNode_s *v3; // eax
  int v4; // esi
  int v5; // esi

  ptHead = ptContainer->tChunkNodeList.ptHead;
  for ( i = ptHead->ptNext; i; i = i->ptNext )
  {
    v3 = (struct ILFContainerNode_s *)Node_Remove(ptHead);
    if ( v3->tChunk.isContainer )
    {
      ILF_DeleteContainerNode(v3);
    }
    else
    {
      v4 = *(_DWORD *)((unsigned int)&v3[-1].tChunkNodeList.ptTail & 0xFFFFFFFC);
      --Mem_nCurrentAllocations;
      Node_Remove((_DWORD **)v4);
      memset(*(void **)(v4 + 8), 0xCDu, *(_DWORD *)(v4 + 16));
      free((void *)v4);
    }
    ptHead = i;
  }
  v5 = *(_DWORD *)((unsigned int)&ptContainer[-1].tChunkNodeList.ptTail & 0xFFFFFFFC);
  --Mem_nCurrentAllocations;
  Node_Remove((_DWORD **)v5);
  memset(*(void **)(v5 + 8), 0xCDu, *(_DWORD *)(v5 + 16));
  free((void *)v5);
}

// source: b/1/ilfcreate.c:510  [anchor-callee]
int __cdecl ILF_Write(struct ILFContainerNode_s *ptContainer, char *zFilename)
{
  struct File_s *v2; // eax
  struct File_s *v3; // esi

  ILF_UpdateAlignment(ptContainer);
  ILF_UpdateOffsets(ptContainer, 0);
  v2 = File_New(zFilename, "w");
  v3 = v2;
  if ( !v2 )
    return 0;
  ILF_WriteContainer(ptContainer, 0, v2);
  if ( v3 == &File_tDummyAsyncFile )
    File_tDummyAsyncFile.isAsync = false;
  else
    File_atDevice[v3->eDeviceID].pfDelete(v3->eDeviceID, v3);
  return 1;
}
