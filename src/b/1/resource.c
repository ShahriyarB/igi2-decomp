/* b/1/resource.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: b/1/resource.c:109  [size]
unsigned int __cdecl Resource_GetHashValue(char *zString)
{
  char *v1; // esi
  char v2; // cl
  unsigned int result; // eax
  unsigned int v4; // eax

  v1 = zString;
  v2 = *zString;
  for ( result = 0; v2; result = v4 % 0x2710 )
  {
    v4 = 26099587 * (v2 + result);
    v2 = *++v1;
  }
  return result;
}

// source: b/1/resource.c:125  [size]
enum bool __cdecl Resource_IsLoadedInternal(char *zFilename, struct Resource_s **pptResource)
{
  int v2; // esi
  struct QHashTable_s *v3; // edi
  unsigned int v4; // eax
  enum bool result; // eax
  char zTempFilename[260]; // [esp+Ch] [ebp-104h] BYREF

  v2 = 0;
  while ( 1 )
  {
    v2 = File_SubstituteAlias(zTempFilename, zFilename, v2, true);
    v3 = Resource_ptHashTable;
    v4 = Resource_ptHashTable->tPrivate.pfHashFunction(Resource_ptHashTable->tPrivate.nHashTableSize, zTempFilename);
    result = ((int  (__cdecl *)(struct QHashTable_s *, unsigned int, const void *))Resource_ptHashTable->tPrivate.pfFindElement)(v3, v4, (const void *)(zTempFilename));
    if ( result )
      break;
    if ( !v2 )
      return result;
  }
  if ( pptResource )
    *pptResource = (struct Resource_s *)result;
  return true;
}

// source: b/1/resource.c:200  [anchor-callee]
struct Resource_s *__cdecl Resource_Register(
        char *zFilename,
        char *zOriginalFilename,
        void *pxData,
        unsigned int nSize,
        unsigned int nType,
        struct FileTime_s *ptFileTime)
{
  void *v6; // ebp
  struct Resource_s *ptHead; // esi
  struct QHashTable_s *v9; // ebx
  unsigned int v10; // eax

  v6 = pxData;
  if ( Resource_IsLoadedInternal(zFilename, nullptr) )
    return nullptr;
  if ( Resource_tResourcePool.nAllocatedBlocks == Resource_tResourcePool.nBlocks )
    MemPool_ReAlloc(&Resource_tResourcePool, Resource_tResourcePool.nReAllocBlocks);
  ++Resource_tResourcePool.nAllocatedBlocks;
  ptHead = (struct Resource_s *)Resource_tResourcePool.tMemPoolFreeList.ptHead;
  Resource_tResourcePool.tMemPoolFreeList.ptHead = Resource_tResourcePool.tMemPoolFreeList.ptHead->ptNext;
  File_SubstituteAlias(ptHead->zFilename, zFilename, 0, true);
  if ( !pxData )
    v6 = ptHead;
  ptHead->nSize = nSize;
  ptHead->pxData = v6;
  ptHead->nType = nType;
  ptHead->isLoaded = 1;
  ptHead->isReferenced = 0;
  ptHead->zOriginalFilename = zOriginalFilename;
  ptHead->nHashValue = Resource_GetHashValue(ptHead->zFilename);
  ptHead->sResourceList.ptHead = (struct RefNode_s *)&ptHead->sResourceList.ptMiddle;
  ptHead->sResourceList.ptTail = (struct RefNode_s *)&ptHead->sResourceList;
  ptHead->sResourceList.ptMiddle = nullptr;
  ptHead->ptPrev = nullptr;
  ptHead->ptNext = nullptr;
  ptHead->tRefNode.ptPrev = nullptr;
  ptHead->tRefNode.ptNext = nullptr;
  List_AddTail(ptHead, (int)&Resource_tResourceList);
  ptHead->tRefNode.ptResource = ptHead;
  if ( ptFileTime )
  {
    ptHead->tFileTime = *ptFileTime;
  }
  else
  {
    ptHead->tFileTime.tFileTime.dwLowDateTime = 0;
    ptHead->tFileTime.tFileTime.dwHighDateTime = 0;
  }
  v9 = Resource_ptHashTable;
  v10 = Resource_ptHashTable->tPrivate.pfHashFunction(Resource_ptHashTable->tPrivate.nHashTableSize, ptHead->zFilename);
  Resource_ptHashTable->tPrivate.pfCreateElement(v9, v10, (const void *)(ptHead->zFilename), (const void *)(ptHead));
  return ptHead;
}

// source: b/1/resource.c:261  [anchor-hash]
void __cdecl Resource_Log()
{
  struct Resource_s *ptHead; // eax
  struct Resource_s *i; // edx
  struct RefNode_s *j; // eax

  ptHead = Resource_tResourceList.ptHead;
  for ( i = Resource_tResourceList.ptHead->ptNext; i; i = i->ptNext )
  {
    if ( !ptHead->nType )
    {
      for ( j = ptHead->sResourceList.ptHead->ptNext; j; j = j->ptNext )
        ;
    }
    ptHead = i;
  }
}

// source: b/1/resource.c:333  [size]
int __cdecl Resource_Exists(char *zFilename)
{
  if ( Resource_IsLoadedInternal(zFilename, nullptr) )
    return 1;
  else
    return File_Exists(zFilename);
}

// source: b/1/resource.c:352  [anchor-callee]
void __cdecl Resource_Remove(struct Resource_s *ptResource)
{
  struct QHashTable_s *v1; // edi
  unsigned int v2; // eax
  struct RefNode_s *ptHead; // eax
  struct RefNode_s *i; // edi

  v1 = Resource_ptHashTable;
  v2 = Resource_ptHashTable->tPrivate.pfHashFunction(
         Resource_ptHashTable->tPrivate.nHashTableSize,
         ptResource->zFilename);
  ((void  (__cdecl *)(struct QHashTable_s *, unsigned int, const void *))Resource_ptHashTable->tPrivate.pfDeleteElement)(v1, v2, (const void *)(ptResource->zFilename));
  switch ( ptResource->nType )
  {
    case 0u:
      ptHead = ptResource->sResourceList.ptHead;
      for ( i = ptHead->ptNext; i; i = i->ptNext )
      {
        Resource_Remove(ptHead->ptResource);
        ptHead = i;
      }
      Node_Remove(ptResource);
      File_Flush(ptResource->pxData);
      --Resource_tResourcePool.nAllocatedBlocks;
      ptResource->ptNext = (struct Resource_s *)Resource_tResourcePool.tMemPoolFreeList.ptHead;
      Resource_tResourcePool.tMemPoolFreeList.ptHead = (struct MemPoolFreeItem_s *)ptResource;
      return;
    case 1u:
    case 4u:
      Node_Remove(&ptResource->tRefNode);
      goto LABEL_7;
    case 2u:
      File_Flush(ptResource->pxData);
      goto LABEL_7;
    case 3u:
LABEL_7:
      Node_Remove(ptResource);
      --Resource_tResourcePool.nAllocatedBlocks;
      ptResource->ptNext = (struct Resource_s *)Resource_tResourcePool.tMemPoolFreeList.ptHead;
      Resource_tResourcePool.tMemPoolFreeList.ptHead = (struct MemPoolFreeItem_s *)ptResource;
      break;
    default:
      return;
  }
}

// source: b/1/resource.c:409  [anchor-strings]
int __cdecl Resource_ParseILFResource(
        char *zResource,
        struct Resource_s *ptParent,
        void *pxContainer,
        struct FileTime_s *ptFileTime)
{
  char *v4; // ebp
  unsigned int v5; // edx
  int v6; // eax
  unsigned int v7; // eax
  char *v8; // esi
  unsigned int v9; // edx
  unsigned int v10; // eax
  char *v11; // ebx
  int result; // eax
  int v13; // eax
  int v14; // eax
  char *v15; // edx
  unsigned int v16; // edi
  int v17; // eax
  unsigned int v18; // eax
  char *i; // edi
  int v20; // eax
  unsigned int v21; // edx
  unsigned int v22; // edi
  struct Resource_s *v23; // eax
  int v24; // eax
  unsigned int v25; // ecx
  struct Resource_s *v26; // eax
  void *ChunkData; // eax
  void *v28; // eax
  int v29; // eax
  unsigned int v30; // [esp-Ch] [ebp-20h]
  unsigned int v31; // [esp-Ch] [ebp-20h]
  char *zOriginalName; // [esp+10h] [ebp-4h]

  v4 = (char *)pxContainer;
  if ( !pxContainer )
    return 1;
  v5 = *((_DWORD *)pxContainer + 1);
  if ( !v5 )
    return 1;
  v6 = *((_DWORD *)pxContainer + 2);
  if ( (v6 & ~(v6 - 1)) != v6 )
  {
    ILF_nLastError = 1;
    return 1;
  }
  v7 = ~(v6 - 1) & (v6 + 19);
  if ( v7 >= v5 )
    return 1;
  v8 = (char *)pxContainer + v7;
  if ( !((char *)pxContainer + v7) )
    return 1;
  do
  {
    if ( *(_DWORD *)v8 != 1162690894 )
    {
      if ( *(_DWORD *)v8 != 1179012169 || *((_DWORD *)v8 + 4) != 1196769860 )
      {
LABEL_59:
        LDebug_Error("Error in resource file: '%s'", zResource);
        abort();
      }
      goto LABEL_56;
    }
    v9 = *((_DWORD *)v4 + 2);
    if ( (v9 & ~(v9 - 1)) != v9
      || (unsigned int)(v8 - v4) >= *((_DWORD *)v4 + 1)
      || (v10 = *((_DWORD *)v8 + 2), (v10 & ~(v10 - 1)) != v10)
      || v10 > v9 )
    {
      ILF_nLastError = 1;
LABEL_16:
      v11 = nullptr;
      goto LABEL_17;
    }
    if ( !*((_DWORD *)v8 + 1) )
      goto LABEL_16;
    v11 = &v4[~(v10 - 1) & (v10 + v8 - v4 + 15)];
LABEL_17:
    v13 = *((_DWORD *)v8 + 3);
    if ( !v13 )
      goto LABEL_59;
    v8 += v13;
    if ( !v8 )
      goto LABEL_59;
    v14 = *((_DWORD *)v8 + 3);
    zOriginalName = nullptr;
    if ( v14 )
    {
      v15 = &v8[v14];
      if ( &v8[v14] )
      {
        if ( *(_DWORD *)v15 == 1179012169 && *((_DWORD *)v15 + 4) == 1196769860 )
        {
          v16 = *((_DWORD *)v15 + 1);
          if ( v16 )
          {
            v17 = *((_DWORD *)v15 + 2);
            if ( (v17 & ~(v17 - 1)) == v17 )
            {
              v18 = ~(v17 - 1) & (v17 + 19);
              if ( v18 < v16 )
              {
                for ( i = &v15[v18]; i; i = (char *)ILF_GetNextChunk(i) )
                {
                  if ( *(_DWORD *)i == 1381258051 )
                    zOriginalName = (char *)ILF_GetChunkData(i, v15);
                }
              }
            }
            else
            {
              ILF_nLastError = 1;
            }
            v4 = (char *)pxContainer;
          }
        }
      }
    }
    v20 = *(_DWORD *)v8;
    if ( *(_DWORD *)v8 != 1497648962 )
    {
      if ( v20 == 1179012169 && *((_DWORD *)v8 + 4) == 1397051977 )
      {
        v26 = Resource_Register(v11, zOriginalName, v8, 0, 1u, ptFileTime);
        if ( v26 )
        {
          List_AddTail(&v26->tRefNode.ptNext, (int)&ptParent->sResourceList);
          result = Resource_ParseILFResource(zResource, ptParent, v8, ptFileTime);
          if ( !result )
            return result;
        }
        goto LABEL_56;
      }
      if ( v20 == 1381258051 )
      {
        v30 = *((_DWORD *)v8 + 1);
        ChunkData = ILF_GetChunkData(v8, v4);
        v23 = Resource_Register(v11, nullptr, ChunkData, v30, 1u, ptFileTime);
        if ( !v23 )
          goto LABEL_56;
LABEL_49:
        List_AddTail(&v23->tRefNode.ptNext, (int)&ptParent->sResourceList);
        goto LABEL_56;
      }
      if ( v20 != 1213481296 )
        goto LABEL_59;
      v31 = *((_DWORD *)v8 + 1);
      v28 = ILF_GetChunkData(v8, v4);
      v23 = Resource_Register(v11, zOriginalName, v28, v31, 4u, ptFileTime);
      goto LABEL_52;
    }
    v21 = *((_DWORD *)v4 + 2);
    v22 = *((_DWORD *)v8 + 1);
    if ( (v21 & ~(v21 - 1)) != v21 || (v24 = v8 - v4, (unsigned int)(v8 - v4) >= *((_DWORD *)v4 + 1)) )
    {
      ILF_nLastError = 1;
      v23 = Resource_Register(v11, zOriginalName, nullptr, v22, 1u, ptFileTime);
      goto LABEL_52;
    }
    v25 = *((_DWORD *)v8 + 2);
    if ( (v25 & ~(v25 - 1)) == v25 && v25 <= v21 )
    {
      if ( v22 )
      {
        v4 = (char *)pxContainer;
        v23 = Resource_Register(
                v11,
                zOriginalName,
                (char *)pxContainer + (~(v25 - 1) & (v25 + v24 + 15)),
                v22,
                1u,
                ptFileTime);
        goto LABEL_52;
      }
    }
    else
    {
      ILF_nLastError = 1;
    }
    v4 = (char *)pxContainer;
    v23 = Resource_Register(v11, zOriginalName, nullptr, v22, 1u, ptFileTime);
LABEL_52:
    if ( v23 )
      goto LABEL_49;
LABEL_56:
    v29 = *((_DWORD *)v8 + 3);
    if ( !v29 )
      return 1;
    v8 += v29;
  }
  while ( v8 );
  return 1;
}

// source: b/1/resource.c:522  [anchor-callee]
void __cdecl Resource_DirList(
        char *zPath,
        void (__cdecl *pfCallback)(struct FileDirListCallbackContext_s *, void *),
        void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct Resource_s *ptResource; };
    struct { char igi2_o1[4]; struct FileDirListCallbackContext_s tContext; };
    struct { char igi2_o2[16]; char zName[512]; };
    char igi2_extent[528];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  char *pxData; // ebp
  char i; // al
  int v6; // esi
  int v7; // edi
  char *v8; // ecx

  if ( Resource_IsLoadedInternal(zPath, &igi2_frame.ptResource) && igi2_frame.ptResource->nType == 4 )
  {
    pxData = (char *)igi2_frame.ptResource->pxData;
    igi2_frame.tContext.zFilename = igi2_frame.zName;
    igi2_frame.tContext.isDirectory = false;
    for ( i = *pxData; i; pxData += v6 )
    {
      v6 = 0;
      v7 = 0;
      if ( i )
      {
        v8 = pxData;
        do
        {
          ++v6;
          if ( i == 59 )
            break;
          v8[igi2_frame.zName - pxData] = i;
          i = *++v8;
          ++v7;
        }
        while ( i );
      }
      igi2_frame.zName[v7] = 0;
      if ( Resource_IsLoadedInternal(igi2_frame.zName, &igi2_frame.ptResource) )
      {
        igi2_frame.tContext.nSize = igi2_frame.ptResource->nSize;
        pfCallback(&igi2_frame.tContext, pxContext);
      }
      i = pxData[v6];
    }
  }
  else
  {
    File_DirList(zPath, pfCallback, pxContext);
  }
}

// source: b/1/resource.c:587  [anchor-strings]
void *__cdecl Resource_ParseFile(char *zFilename, void *pxBuffer, unsigned int nSize)
{
  #pragma pack(push, 1)
  union
  {
    struct { int v15; };
    struct { char igi2_o1[4]; int a2; };
    struct { char igi2_o2[8]; struct FileTime_s tFileTime; };
    char igi2_extent[16];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  void *v3; // esi
  struct Resource_s *v6; // eax
  struct Resource_s *v7; // ebx
  struct Resource_s *v9; // eax
  char *v10; // ebp
  unsigned int v11; // eax
  unsigned int v12; // edx
  char *v13; // eax
  struct Resource_s *v14; // eax

  v3 = pxBuffer;
  Game_MPRunNetwork(zFilename);
  File_GetFileTime(&igi2_frame.tFileTime, zFilename);
  if ( pxBuffer && *(_DWORD *)pxBuffer == 1179012169 && *((_DWORD *)pxBuffer + 4) == 1397051977 )
  {
    v6 = Resource_Register(zFilename, nullptr, pxBuffer, 0, 0, &igi2_frame.tFileTime);
    v7 = v6;
    if ( v6 )
    {
      Resource_ParseILFResource(zFilename, v6, pxBuffer, &igi2_frame.tFileTime);
      v7->isReferenced = 1;
      return pxBuffer;
    }
    return nullptr;
  }
  if ( nSize >= 8 && !strncmp((char *)pxBuffer, "RESOURCE", 8u) )
  {
    v9 = Resource_Register(zFilename, nullptr, pxBuffer, 0, 0, &igi2_frame.tFileTime);
    if ( !v9 )
      return nullptr;
    v9->isReferenced = 1;
    v10 = (char *)pxBuffer + 32;
    if ( *((_DWORD *)pxBuffer + 2) )
    {
      igi2_frame.a2 = (int)&v9->sResourceList;
      igi2_frame.v15 = *((_DWORD *)pxBuffer + 2);
      do
      {
        v11 = *((_DWORD *)v10 + 2);
        v12 = *((_DWORD *)v10 + 1);
        qmemcpy(byte_6C0330, v10 + 12, v11);
        (&byte_6C0330)[v11] = 0;
        v13 = &v10[(v11 + 43) & 0xFFFFFFE0];
        v10 = &v13[(v12 + 31) & 0xFFFFFFE0];
        v14 = Resource_Register(byte_6C0330, nullptr, v13, v12, 1u, &igi2_frame.tFileTime);
        List_AddTail(&v14->tRefNode.ptNext, igi2_frame.a2);
        --igi2_frame.v15;
      }
      while ( igi2_frame.v15 );
      return pxBuffer;
    }
    return v3;
  }
  else
  {
    Resource_Register(zFilename, nullptr, pxBuffer, nSize, 2u, &igi2_frame.tFileTime)->isReferenced = 1;
    return pxBuffer;
  }
}

// source: b/1/resource.c:707  [anchor-mhash]
void __cdecl Resource_Open()
{
  struct MemPoolSegment_s *v0; // esi
  int v1; // eax
  struct MemPoolFreeItem_s *ptHead; // edx
  unsigned int i; // ecx
  struct MemPoolFreeItem_s *v4; // eax
  struct QHashTable_s *v5; // esi
  void *v6; // edi
  unsigned int v7; // eax

  Resource_tResourceList.ptHead = (struct Resource_s *)&Resource_tResourceList.ptMiddle;
  Resource_tResourceList.ptTail = (struct Resource_s *)&Resource_tResourceList;
  Resource_tResourceList.ptMiddle = nullptr;
  Resource_tResourcePool.nBlocks = 0;
  Resource_tResourcePool.nAllocatedBlocks = 0;
  Resource_tResourcePool.nAlignment = 4;
  Resource_tResourcePool.nBlockSize = 580;
  Resource_tResourcePool.nReAllocBlocks = 1024;
  Resource_tResourcePool.tMemPoolFreeList.ptHead = nullptr;
  Resource_tResourcePool.tMemPoolSegmentList.ptHead = nullptr;
  v0 = (struct MemPoolSegment_s *)Mem_AllocFn(12, 4);
  v1 = Resource_tResourcePool.nBlockSize << 10;
  v0->nByteSize = Resource_tResourcePool.nBlockSize << 10;
  v0->pxData = Mem_AllocFn(v1, Resource_tResourcePool.nAlignment);
  v0->ptNext = Resource_tResourcePool.tMemPoolSegmentList.ptHead;
  ptHead = Resource_tResourcePool.tMemPoolFreeList.ptHead;
  Resource_tResourcePool.tMemPoolSegmentList.ptHead = v0;
  Resource_tResourcePool.nBlocks += 1024;
  for ( i = 0; i < 0x400; ++i )
  {
    v4 = (struct MemPoolFreeItem_s *)((char *)v0->pxData + i * Resource_tResourcePool.nBlockSize);
    v4->ptNext = ptHead;
    ptHead = v4;
    Resource_tResourcePool.tMemPoolFreeList.ptHead = v4;
  }
  Resource_tDummyAsyncFile.isAsync = false;
  v5 = (struct QHashTable_s *)Mem_AllocFn(40, 4);
  v5->tPrivate.nHashTableSize = 10000;
  v5->tPrivate.pfHashFunction = QHashTable_StringHashFunction;
  v5->tPrivate.pfCompareKey = QHashTable_StringCompareKeyFunction;
  v5->tPrivate.pfDuplicateKey = nullptr;
  v5->tPrivate.pfCreateElement = QHashTable_CreateElementChained;
  v5->tPrivate.pfFindElement = QHashTable_FindElementChained;
  v5->tPrivate.pfDeleteElement = QHashTable_DeleteElementChained;
  v5->tPrivate.pfMap = QHashTable_MapChained;
  v5->tPrivate.nEntries = 0;
  v6 = Mem_AllocFn(120000, 4);
  v7 = 0;
  v5->tPrivate.papxElement = v6;
  memset(v6, 0, 0x1D4C0u);
  do
  {
    *(_DWORD *)((char *)v5->tPrivate.papxElement + v7) = (char *)v5->tPrivate.papxElement + v7 + 4;
    *(_DWORD *)((char *)v5->tPrivate.papxElement + v7 + 8) = (char *)v5->tPrivate.papxElement + v7;
    *(_DWORD *)((char *)v5->tPrivate.papxElement + v7 + 4) = 0;
    *(_DWORD *)((char *)v5->tPrivate.papxElement + v7 + 12) = (char *)v5->tPrivate.papxElement + v7 + 16;
    *(_DWORD *)((char *)v5->tPrivate.papxElement + v7 + 20) = (char *)v5->tPrivate.papxElement + v7 + 12;
    *(_DWORD *)((char *)v5->tPrivate.papxElement + v7 + 16) = 0;
    *(_DWORD *)((char *)v5->tPrivate.papxElement + v7 + 24) = (char *)v5->tPrivate.papxElement + v7 + 28;
    *(_DWORD *)((char *)v5->tPrivate.papxElement + v7 + 32) = (char *)v5->tPrivate.papxElement + v7 + 24;
    *(_DWORD *)((char *)v5->tPrivate.papxElement + v7 + 28) = 0;
    *(_DWORD *)((char *)v5->tPrivate.papxElement + v7 + 36) = (char *)v5->tPrivate.papxElement + v7 + 40;
    *(_DWORD *)((char *)v5->tPrivate.papxElement + v7 + 44) = (char *)v5->tPrivate.papxElement + v7 + 36;
    *(_DWORD *)((char *)v5->tPrivate.papxElement + v7 + 40) = 0;
    *(_DWORD *)((char *)v5->tPrivate.papxElement + v7 + 48) = (char *)v5->tPrivate.papxElement + v7 + 52;
    *(_DWORD *)((char *)v5->tPrivate.papxElement + v7 + 56) = (char *)v5->tPrivate.papxElement + v7 + 48;
    *(_DWORD *)((char *)v5->tPrivate.papxElement + v7 + 52) = 0;
    *(_DWORD *)((char *)v5->tPrivate.papxElement + v7 + 60) = (char *)v5->tPrivate.papxElement + v7 + 64;
    *(_DWORD *)((char *)v5->tPrivate.papxElement + v7 + 68) = (char *)v5->tPrivate.papxElement + v7 + 60;
    *(_DWORD *)((char *)v5->tPrivate.papxElement + v7 + 64) = 0;
    *(_DWORD *)((char *)v5->tPrivate.papxElement + v7 + 72) = (char *)v5->tPrivate.papxElement + v7 + 76;
    *(_DWORD *)((char *)v5->tPrivate.papxElement + v7 + 80) = (char *)v5->tPrivate.papxElement + v7 + 72;
    *(_DWORD *)((char *)v5->tPrivate.papxElement + v7 + 76) = 0;
    *(_DWORD *)((char *)v5->tPrivate.papxElement + v7 + 84) = (char *)v5->tPrivate.papxElement + v7 + 88;
    *(_DWORD *)((char *)v5->tPrivate.papxElement + v7 + 92) = (char *)v5->tPrivate.papxElement + v7 + 84;
    *(_DWORD *)((char *)v5->tPrivate.papxElement + v7 + 88) = 0;
    *(_DWORD *)((char *)v5->tPrivate.papxElement + v7 + 96) = (char *)v5->tPrivate.papxElement + v7 + 100;
    *(_DWORD *)((char *)v5->tPrivate.papxElement + v7 + 104) = (char *)v5->tPrivate.papxElement + v7 + 96;
    *(_DWORD *)((char *)v5->tPrivate.papxElement + v7 + 100) = 0;
    *(_DWORD *)((char *)v5->tPrivate.papxElement + v7 + 108) = (char *)v5->tPrivate.papxElement + v7 + 112;
    *(_DWORD *)((char *)v5->tPrivate.papxElement + v7 + 116) = (char *)v5->tPrivate.papxElement + v7 + 108;
    *(_DWORD *)((char *)v5->tPrivate.papxElement + v7 + 112) = 0;
    v7 += 120;
  }
  while ( v7 < 0x1D4C0 );
  Resource_ptHashTable = v5;
}

// source: b/1/resource.c:730  [anchor-hash]
void __cdecl Resource_Close()
{
  while ( Resource_tResourceList.ptHead->ptNext )
    Resource_Remove(Resource_tResourceList.ptHead);
  QHashTable_Delete(Resource_ptHashTable);
  MemPool_DeInit(&Resource_tResourcePool);
}

// source: b/1/resource.c:747  [anchor-hash]
void __cdecl Resource_Clean()
{
  while ( Resource_tResourceList.ptHead->ptNext )
    Resource_Remove(Resource_tResourceList.ptHead);
}

// source: b/1/resource.c:780  [anchor-callee]
void *__cdecl Resource_Load(char *zFilename, unsigned int *pnSize)
{
  char *v3; // ecx
  struct Resource_s *v4; // eax
  void *v6; // eax
  struct Resource_s *v7; // ecx
  struct Resource_s *ptResource; // [esp+4h] [ebp-4h] BYREF

  if ( Resource_IsLoadedInternal(zFilename, &ptResource) )
  {
    v4 = ptResource;
    if ( pnSize )
      *pnSize = ptResource->nSize;
    v4->isReferenced = 1;
    return v4->pxData;
  }
  else
  {
    Game_MPRunNetwork(v3);
    v6 = File_Load(zFilename, (unsigned int *)&ptResource);
    if ( !v6 )
    {
      LDebug_Error("Failed to load resource: '%s'", zFilename);
      abort();
    }
    v7 = ptResource;
    if ( pnSize )
      *pnSize = (unsigned int)ptResource;
    return Resource_ParseFile(File_zLastSubstitutedPath, v6, (unsigned int)v7);
  }
}

// source: b/1/resource.c:824  [anchor-callee]
void __cdecl Resource_Unload(char *zFilename)
{
  struct Resource_s *v1; // ecx
  unsigned int nType; // eax
  struct Resource_s *ptResource; // [esp+0h] [ebp-4h] BYREF

  ptResource = v1;
  if ( Resource_IsLoadedInternal(zFilename, &ptResource) )
  {
    nType = ptResource->nType;
    if ( nType != 3 && nType != 1 )
      Resource_Remove(ptResource);
  }
}

// source: b/1/resource.c:848  [anchor-callee]
void __cdecl Resource_Flush(void *pxData)
{
  struct Resource_s *ptHead; // ecx
  struct Resource_s *ptNext; // eax
  unsigned int nType; // eax

  ptHead = Resource_tResourceList.ptHead;
  ptNext = Resource_tResourceList.ptHead->ptNext;
  if ( Resource_tResourceList.ptHead->ptNext )
  {
    while ( ptHead->pxData != pxData )
    {
      ptHead = ptNext;
      ptNext = ptNext->ptNext;
      if ( !ptNext )
        return;
    }
    nType = ptHead->nType;
    if ( nType != 3 && nType != 1 )
      Resource_Remove(ptHead);
  }
}

// source: b/1/resource.c:876  [anchor-strings]
char *__cdecl Resource_GetFilenameByPointer(void *pxData)
{
  struct Resource_s *ptHead; // ecx
  struct Resource_s *ptNext; // eax

  ptHead = Resource_tResourceList.ptHead;
  ptNext = Resource_tResourceList.ptHead->ptNext;
  if ( !Resource_tResourceList.ptHead->ptNext )
  {
LABEL_4:
    LDebug_Error("Resource_GetFilenameByPointer() : Couldn't locate resource at %p.", pxData);
    abort();
  }
  while ( ptHead->pxData != pxData )
  {
    ptHead = ptNext;
    ptNext = ptNext->ptNext;
    if ( !ptNext )
      goto LABEL_4;
  }
  return ptHead->zFilename;
}

// source: b/1/resource.c:903  [anchor-strings]
char *__cdecl Resource_GetOriginalFilename(char *zFilename)
{
  struct Resource_s *ptResource; // [esp+4h] [ebp-4h] BYREF

  if ( Resource_IsLoadedInternal(zFilename, &ptResource) == false )
  {
    LDebug_Error("Resource_GetOriginalFilename() : Resource %s is not loaded.", zFilename);
    abort();
  }
  return ptResource->zOriginalFilename;
}

// source: b/1/resource.c:926  [anchor-caller]
int __cdecl Resource_NewROMResource(char *zFilename, int nSize, void *pxData)
{
  return (int)Resource_Register(zFilename, nullptr, pxData, nSize, 3u, nullptr);
}

// source: b/1/resource.c:939  [size]
int __cdecl Resource_GetFileTime(struct FileTime_s *ptFileTime, char *zFilename)
{
  struct Resource_s *ptResource; // [esp+4h] [ebp-4h] BYREF

  if ( Resource_IsLoadedInternal(zFilename, &ptResource) == false )
    return File_GetFileTime(ptFileTime, zFilename);
  *ptFileTime = ptResource->tFileTime;
  return 0;
}

// source: b/1/resource.c:961  [size]
int __cdecl Resource_CompareFileTime(
        struct FileTime_s *ptFileTime1,
        struct FileTime_s *ptFileTime2)
{
  return CompareFileTime(&ptFileTime1->tFileTime, &ptFileTime2->tFileTime);
}

// source: b/1/resource.c:976  [size]
void __cdecl Resource_DeleteROMResource(char *zFilename)
{
  struct Resource_s *v1; // ecx
  struct Resource_s *ptResource; // [esp+0h] [ebp-4h] BYREF

  ptResource = v1;
  if ( Resource_IsLoadedInternal(zFilename, &ptResource) )
    Resource_Remove(ptResource);
}

// source: b/1/resource.c:999  [anchor-strings]
struct File_s *__cdecl Resource_LoadAsync(char *zFilename, unsigned int *pnSize)
{
  struct Resource_s *ptResource; // [esp+4h] [ebp-4h] BYREF

  if ( Resource_IsLoadedInternal(zFilename, &ptResource) == false )
    return File_LoadAsync(zFilename, pnSize);
  if ( Resource_tDummyAsyncFile.isAsync )
  {
    LDebug_Error("Too many simultaneous async resources.");
    abort();
  }
  Resource_tDummyAsyncFile.isAsync = true;
  Resource_tDummyAsyncFile.isAsyncReadComplete = true;
  Resource_tDummyAsyncFile.pxAsyncBuffer = ptResource->pxData;
  Resource_tDummyAsyncFile.nAsyncBytesRead = ptResource->nSize;
  strcpy(Resource_tDummyAsyncFile.zFilename, zFilename);
  return &Resource_tDummyAsyncFile;
}

// source: b/1/resource.c:1032  [anchor-hash]
int __cdecl Resource_IsAsyncReadComplete(struct File_s *hResource)
{
  if ( hResource == &Resource_tDummyAsyncFile )
    return 1;
  if ( hResource != &File_tDummyAsyncFile )
    File_atDevice[hResource->eDeviceID].pfUpdateAsyncStatus(hResource->eDeviceID, hResource);
  return hResource->isAsyncReadComplete;
}

// source: b/1/resource.c:1051  [anchor-hash]
int __cdecl Resource_GetAsyncBytesRead(struct File_s *hResource)
{
  if ( hResource != &Resource_tDummyAsyncFile && hResource != &File_tDummyAsyncFile )
    File_atDevice[hResource->eDeviceID].pfUpdateAsyncStatus(hResource->eDeviceID, hResource);
  return hResource->nAsyncBytesRead;
}

// source: b/1/resource.c:1073  [anchor-hash]
void *__cdecl Resource_FinishAsyncRead(struct File_s *hResource)
{
  int v1; // ebx
  void *pxAsyncBuffer; // edi

  v1 = 0;
  if ( hResource == &Resource_tDummyAsyncFile )
  {
    Resource_tDummyAsyncFile.isAsync = false;
    v1 = 1;
  }
  else
  {
    do
    {
      if ( hResource != &File_tDummyAsyncFile )
        File_atDevice[hResource->eDeviceID].pfUpdateAsyncStatus(hResource->eDeviceID, hResource);
    }
    while ( hResource->isAsyncReadComplete == false );
  }
  pxAsyncBuffer = hResource->pxAsyncBuffer;
  if ( !v1 )
  {
    Resource_ParseFile(File_zLastSubstitutedPath, hResource->pxAsyncBuffer, hResource->nAsyncBytesRead);
    if ( hResource == &File_tDummyAsyncFile )
    {
      File_tDummyAsyncFile.isAsync = false;
      return pxAsyncBuffer;
    }
    File_atDevice[hResource->eDeviceID].pfDelete(hResource->eDeviceID, hResource);
  }
  return pxAsyncBuffer;
}

// source: b/1/resource.c:1125  [anchor-hash]
int __cdecl Resource_IsLoaded(char *zFilename)
{
  return Resource_IsLoadedInternal(zFilename, nullptr);
}

// source: b/1/resource.c:1138  [anchor-mhash]
void __cdecl Resource_EnumerateLoadedResources(
        void (__cdecl *pfCallback)(struct ResourceFileCallbackContext_s *, void *),
        void *pxContext)
{
  struct Resource_s *ptHead; // eax
  struct Resource_s *i; // esi
  struct ResourceFileCallbackContext_s tContext; // [esp+4h] [ebp-18h] BYREF

  ptHead = Resource_tResourceList.ptHead;
  for ( i = Resource_tResourceList.ptHead->ptNext; i; i = i->ptNext )
  {
    tContext.zFilename = ptHead->zFilename;
    tContext.zOriginalFilename = ptHead->zOriginalFilename;
    tContext.isReferenced = ptHead->isReferenced;
    tContext.nSize = ptHead->nSize;
    tContext.eType = ptHead->nType;
    tContext.pxData = ptHead->pxData;
    pfCallback(&tContext, pxContext);
    ptHead = i;
  }
}
