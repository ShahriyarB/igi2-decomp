/* e/3/hierarchy.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: e/3/hierarchy.c:70  [anchor-mhash]
unsigned int __cdecl Hierarchy_HashFunction(unsigned int nHashTableSize, void *pxHierarchy)
{
  unsigned int v3; // edx
  int v4; // ecx
  int v5; // ecx
  int v6; // eax

  v3 = 0;
  v4 = 0;
  do
  {
    v5 = *(char *)pxHierarchy + v4;
    v3 = 26099587 * (v3 + *(char *)pxHierarchy) % nHashTableSize;
    pxHierarchy = (char *)pxHierarchy + 1;
    v6 = v5;
    v4 = v5 - 1;
  }
  while ( v6 > 0 );
  return v3;
}

// source: e/3/hierarchy.c:103  [anchor-mhash]
int __cdecl Hierarchy_Compare(void *px1, void *px2)
{
  char *v2; // ecx
  int v3; // esi
  char v4; // dl
  char v5; // al
  int v6; // edx

  v2 = (char *)px1;
  v3 = 0;
  while ( 1 )
  {
    v4 = v2[(_BYTE *)px2 - (_BYTE *)px1];
    if ( *v2 < v4 )
      return -1;
    if ( *v2 > v4 )
      break;
    v5 = *v2++;
    v6 = v5 + v3;
    v3 = v6 - 1;
    if ( v6 <= 0 )
      return 0;
  }
  return 1;
}

// source: e/3/hierarchy.c:133  [anchor-hash]
void __cdecl Hierarchy_Open()
{
  struct MemPoolSegment_s *v0; // esi
  int v1; // eax
  struct MemPoolFreeItem_s *ptHead; // edx
  unsigned int i; // ecx
  struct MemPoolFreeItem_s *v4; // eax
  struct QHashTable_s *v5; // esi
  void *v6; // edi

  Hierarchy_tRecordPool.nBlocks = 0;
  Hierarchy_tRecordPool.nAllocatedBlocks = 0;
  Hierarchy_tRecordPool.nAlignment = 4;
  Hierarchy_tRecordPool.nBlockSize = 272;
  Hierarchy_tRecordPool.nReAllocBlocks = 0;
  Hierarchy_tRecordPool.tMemPoolFreeList.ptHead = nullptr;
  Hierarchy_tRecordPool.tMemPoolSegmentList.ptHead = nullptr;
  v0 = (struct MemPoolSegment_s *)Mem_AllocFn(12, 4);
  v1 = 16 * Hierarchy_tRecordPool.nBlockSize;
  v0->nByteSize = 16 * Hierarchy_tRecordPool.nBlockSize;
  v0->pxData = Mem_AllocFn(v1, Hierarchy_tRecordPool.nAlignment);
  v0->ptNext = Hierarchy_tRecordPool.tMemPoolSegmentList.ptHead;
  ptHead = Hierarchy_tRecordPool.tMemPoolFreeList.ptHead;
  Hierarchy_tRecordPool.tMemPoolSegmentList.ptHead = v0;
  Hierarchy_tRecordPool.nBlocks += 16;
  for ( i = 0; i < 0x10; ++i )
  {
    v4 = (struct MemPoolFreeItem_s *)((char *)v0->pxData + i * Hierarchy_tRecordPool.nBlockSize);
    v4->ptNext = ptHead;
    ptHead = v4;
    Hierarchy_tRecordPool.tMemPoolFreeList.ptHead = v4;
  }
  v5 = (struct QHashTable_s *)Mem_AllocFn(40, 4);
  v5->tPrivate.nHashTableSize = 16;
  v5->tPrivate.pfHashFunction = Hierarchy_HashFunction;
  v5->tPrivate.pfCompareKey = Hierarchy_Compare;
  v5->tPrivate.pfDuplicateKey = nullptr;
  v5->tPrivate.pfCreateElement = QHashTable_CreateElementClosed;
  v5->tPrivate.pfFindElement = QHashTable_FindElementClosed;
  v5->tPrivate.pfDeleteElement = QHashTable_DeleteElementClosed;
  v5->tPrivate.pfMap = QHashTable_MapClosed;
  v5->tPrivate.nEntries = 0;
  v6 = Mem_AllocFn(128, 4);
  v5->tPrivate.papxElement = v6;
  memset(v6, 0, 0x80u);
  Hierarchy_ptHashTable = v5;
}

// source: e/3/hierarchy.c:147  [anchor-hash]
void __cdecl Hierarchy_Close()
{
  QHashTable_Delete(Hierarchy_ptHashTable);
  MemPool_DeInit(&Hierarchy_tRecordPool);
}

// source: e/3/hierarchy.c:164  [anchor-callee]
void __cdecl Hierarchy_UnRegisterAnim(struct AnimHeader_s *ptAnim)
{
  unsigned __int8 *ptHierarchy; // eax
  struct QHashTable_s *v2; // esi
  unsigned int v3; // eax
  int v4; // eax
  int v5; // esi
  int v6; // eax

  ptHierarchy = ptAnim->ptHierarchy;
  if ( ptHierarchy )
  {
    v2 = Hierarchy_ptHashTable;
    v3 = Hierarchy_ptHashTable->tPrivate.pfHashFunction(Hierarchy_ptHashTable->tPrivate.nHashTableSize, ptHierarchy);
    v4 = ((int  (__cdecl *)(struct QHashTable_s *, unsigned int, const void *))Hierarchy_ptHashTable->tPrivate.pfFindElement)(v2, v3, (const void *)(ptHierarchy));
    if ( v4 )
    {
      v5 = *(_DWORD *)v4;
      v6 = (*(int (__cdecl **)(_DWORD, char *))(*(_DWORD *)v4 + 12))(*(_DWORD *)(*(_DWORD *)v4 + 4), ptAnim->zName);
      (*(void (__cdecl **)(int, int, const void *))(v5 + 32))(v5, v6, (const void *)(ptAnim->zName));
    }
  }
}

// source: e/3/hierarchy.c:193  [anchor-callee]
void __cdecl Hierarchy_UnRegister(unsigned __int8 *ptHierarchy)
{
  struct QHashTable_s *v1; // esi
  int v2; // eax
  int v3; // esi
  int v4; // eax
  struct QHashTable_s *v5; // ebx
  unsigned int v6; // eax

  v1 = Hierarchy_ptHashTable;
  v2 = Hierarchy_ptHashTable->tPrivate.pfHashFunction(Hierarchy_ptHashTable->tPrivate.nHashTableSize, ptHierarchy);
  v3 = ((int  (__cdecl *)(struct QHashTable_s *, unsigned int, const void *))Hierarchy_ptHashTable->tPrivate.pfFindElement)(v1, v2, (const void *)(ptHierarchy));
  v4 = *(_DWORD *)(v3 + 12) - 1;
  *(_DWORD *)(v3 + 12) = v4;
  if ( !v4 )
  {
    QHashTable_Delete(*(struct QHashTable_s **)v3);
    v5 = Hierarchy_ptHashTable;
    v6 = Hierarchy_ptHashTable->tPrivate.pfHashFunction(Hierarchy_ptHashTable->tPrivate.nHashTableSize, ptHierarchy);
    ((void  (__cdecl *)(struct QHashTable_s *, unsigned int, const void *))Hierarchy_ptHashTable->tPrivate.pfDeleteElement)(v5, v6, (const void *)(ptHierarchy));
    --Hierarchy_tRecordPool.nAllocatedBlocks;
    *(_DWORD *)v3 = Hierarchy_tRecordPool.tMemPoolFreeList.ptHead;
    Hierarchy_tRecordPool.tMemPoolFreeList.ptHead = (struct MemPoolFreeItem_s *)v3;
    --Hierarchy_nHierarchies;
  }
}

// source: e/3/hierarchy.c:224  [anchor-caller]
unsigned __int8 *__cdecl Hierarchy_Register(
        unsigned __int8 *ptHierarchy,
        struct AnimHeader_s *ptAnim,
        char *pazNames)
{
  struct QHashTable_s *v4; // esi
  unsigned int v5; // eax
  _DWORD *v6; // eax
  _DWORD *v7; // esi
  struct MemPoolFreeItem_s *ptHead; // ebx
  struct MemPoolFreeItem_s *v10; // esi
  struct MemPoolFreeItem_s *v11; // edi
  unsigned int v12; // eax
  struct MemPoolFreeItem_s *ptNext; // eax
  struct MemPoolFreeItem_s *v14; // edi
  unsigned __int8 *v15; // esi
  char v16; // cl
  struct QHashTable_s *v17; // eax
  struct QHashTable_s *v18; // esi
  int v19; // eax
  int v20; // edi
  int v21; // eax

  v4 = Hierarchy_ptHashTable;
  v5 = Hierarchy_ptHashTable->tPrivate.pfHashFunction(Hierarchy_ptHashTable->tPrivate.nHashTableSize, ptHierarchy);
  v6 = (_DWORD *)((int  (__cdecl *)(struct QHashTable_s *, unsigned int, const void *))v4->tPrivate.pfFindElement)(v4, v5, (const void *)(ptHierarchy));
  v7 = v6;
  if ( v6 )
  {
    if ( ptAnim )
    {
      v20 = *v6;
      v21 = (*(int (__cdecl **)(_DWORD, char *))(*v6 + 12))(*(_DWORD *)(*v6 + 4), ptAnim->zName);
      (*(void (__cdecl **)(int, int, const void *, const void *))(v20 + 24))(v20, v21, ptAnim->zName, ptAnim);
    }
    else
    {
      ++v6[3];
    }
    if ( pazNames && !v7[2] )
      v7[2] = pazNames;
    return (unsigned __int8 *)(v7 + 4);
  }
  else if ( ptAnim )
  {
    return nullptr;
  }
  else
  {
    if ( Hierarchy_tRecordPool.nAllocatedBlocks == Hierarchy_tRecordPool.nBlocks )
      MemPool_ReAlloc(&Hierarchy_tRecordPool, Hierarchy_tRecordPool.nReAllocBlocks);
    ++Hierarchy_tRecordPool.nAllocatedBlocks;
    ptHead = Hierarchy_tRecordPool.tMemPoolFreeList.ptHead;
    Hierarchy_tRecordPool.tMemPoolFreeList.ptHead = Hierarchy_tRecordPool.tMemPoolFreeList.ptHead->ptNext;
    ptHead[3].ptNext = (struct MemPoolFreeItem_s *)1;
    ptHead[2].ptNext = (struct MemPoolFreeItem_s *)pazNames;
    ptHead[1].ptNext = (struct MemPoolFreeItem_s *)Hierarchy_GetNumBones(ptHierarchy);
    v10 = (struct MemPoolFreeItem_s *)Mem_AllocFn(40, 4);
    v10[1].ptNext = (struct MemPoolFreeItem_s *)256;
    v10[3].ptNext = (struct MemPoolFreeItem_s *)QHashTable_StringHashFunction;
    v10[4].ptNext = (struct MemPoolFreeItem_s *)QHashTable_StringCompareKeyFunction;
    v10[5].ptNext = nullptr;
    v10[6].ptNext = (struct MemPoolFreeItem_s *)QHashTable_CreateElementChained;
    v10[7].ptNext = (struct MemPoolFreeItem_s *)QHashTable_FindElementChained;
    v10[8].ptNext = (struct MemPoolFreeItem_s *)QHashTable_DeleteElementChained;
    v10[9].ptNext = (struct MemPoolFreeItem_s *)QHashTable_MapChained;
    v10->ptNext = nullptr;
    v11 = (struct MemPoolFreeItem_s *)Mem_AllocFn(3072, 4);
    v12 = 0;
    v10[2].ptNext = v11;
    memset(v11, 0, 0xC00u);
    do
    {
      v10[2].ptNext[v12].ptNext = &v10[2].ptNext[v12 + 1];
      v10[2].ptNext[v12 + 2].ptNext = &v10[2].ptNext[v12];
      v10[2].ptNext[v12 + 1].ptNext = nullptr;
      v10[2].ptNext[v12 + 3].ptNext = &v10[2].ptNext[v12 + 4];
      v10[2].ptNext[v12 + 5].ptNext = &v10[2].ptNext[v12 + 3];
      v10[2].ptNext[v12 + 4].ptNext = nullptr;
      v10[2].ptNext[v12 + 6].ptNext = &v10[2].ptNext[v12 + 7];
      v10[2].ptNext[v12 + 8].ptNext = &v10[2].ptNext[v12 + 6];
      v10[2].ptNext[v12 + 7].ptNext = nullptr;
      v10[2].ptNext[v12 + 9].ptNext = &v10[2].ptNext[v12 + 10];
      v10[2].ptNext[v12 + 11].ptNext = &v10[2].ptNext[v12 + 9];
      v10[2].ptNext[v12 + 10].ptNext = nullptr;
      v10[2].ptNext[v12 + 12].ptNext = &v10[2].ptNext[v12 + 13];
      v10[2].ptNext[v12 + 14].ptNext = &v10[2].ptNext[v12 + 12];
      v10[2].ptNext[v12 + 13].ptNext = nullptr;
      v10[2].ptNext[v12 + 15].ptNext = &v10[2].ptNext[v12 + 16];
      v10[2].ptNext[v12 + 17].ptNext = &v10[2].ptNext[v12 + 15];
      v10[2].ptNext[v12 + 16].ptNext = nullptr;
      v10[2].ptNext[v12 + 18].ptNext = &v10[2].ptNext[v12 + 19];
      v10[2].ptNext[v12 + 20].ptNext = &v10[2].ptNext[v12 + 18];
      v10[2].ptNext[v12 + 19].ptNext = nullptr;
      v10[2].ptNext[v12 + 21].ptNext = &v10[2].ptNext[v12 + 22];
      v10[2].ptNext[v12 + 23].ptNext = &v10[2].ptNext[v12 + 21];
      v10[2].ptNext[v12 + 22].ptNext = nullptr;
      v12 += 24;
    }
    while ( v12 < 768 );
    ptNext = ptHead[1].ptNext;
    ptHead->ptNext = v10;
    qmemcpy(&ptHead[4], ptHierarchy, 4 * ((unsigned int)ptNext >> 2));
    v15 = &ptHierarchy[4 * ((unsigned int)ptNext >> 2)];
    v14 = &ptHead[((unsigned int)ptNext >> 2) + 4];
    v16 = (char)ptNext;
    v17 = Hierarchy_ptHashTable;
    qmemcpy(v14, v15, v16 & 3);
    v18 = v17;
    v19 = v17->tPrivate.pfHashFunction(v17->tPrivate.nHashTableSize, ptHierarchy);
    v18->tPrivate.pfCreateElement(v18, v19, ptHierarchy, ptHead);
    ++Hierarchy_nHierarchies;
    return (unsigned __int8 *)&ptHead[4];
  }
}

// source: e/3/hierarchy.c:287  [anchor-callee]
struct AnimHeader_s *__cdecl Hierarchy_LoadAnim(char *zFileName)
{
  char *v2; // ecx
  int v3; // eax
  _DWORD *v4; // ebx
  void *v5; // eax
  unsigned int v6; // edx
  int v7; // eax
  unsigned int v8; // eax
  _DWORD *v9; // eax
  int v10; // ecx
  struct AnimHeader_s *ChunkData; // esi
  unsigned int v12; // edx
  int v13; // eax
  unsigned int v14; // eax
  _DWORD *v15; // eax
  int v16; // ecx
  unsigned int v17; // edx
  int v18; // eax
  unsigned int v19; // eax
  _DWORD *v20; // eax
  int v21; // ecx
  unsigned __int8 *v22; // eax
  unsigned __int8 *v23; // eax
  int nAttachObjects; // ebp
  unsigned int v25; // edx
  int v26; // eax
  unsigned int v27; // eax
  _DWORD *v28; // eax
  int v29; // ecx
  int v30; // edi
  int v31; // edx
  struct Anim_AttachObject_t *ptFirstAttachObject; // eax
  struct AnimEvent_AttachKey_t *ptFirstKey; // ecx
  struct AnimEvent_AttachKey_t **p_ptFirstKey; // eax
  struct AnimEvent_s *ptFirstEvent; // eax
  int i; // edx
  struct AnimEvent_s *ptNext; // ecx
  char zFilename[4]; // [esp+8h] [ebp-4h] BYREF

  if ( Resource_IsLoadedInternal(zFileName, (struct Resource_s **)zFilename) )
  {
    v3 = *(_DWORD *)zFilename;
    *(_DWORD *)(*(_DWORD *)zFilename + 44) = 1;
    v4 = *(_DWORD **)(v3 + 52);
  }
  else
  {
    Game_MPRunNetwork(v2);
    v5 = File_Load(zFileName, (unsigned int *)zFilename);
    if ( !v5 )
    {
      LDebug_Error("Failed to load resource: '%s'", zFileName);
      abort();
    }
    v4 = Resource_ParseFile(File_zLastSubstitutedPath, v5, *(unsigned int *)zFilename);
  }
  if ( v4 )
  {
    v6 = v4[1];
    if ( v6 )
    {
      v7 = v4[2];
      if ( (v7 & ~(v7 - 1)) == v7 )
      {
        v8 = ~(v7 - 1) & (v7 + 19);
        if ( v8 < v6 )
        {
          v9 = (_DWORD *)((char *)v4 + v8);
          goto LABEL_13;
        }
      }
      else
      {
        ILF_nLastError = 1;
      }
    }
  }
  v9 = nullptr;
LABEL_13:
  if ( v9 )
  {
    while ( *v9 != 1095649348 )
    {
      v10 = v9[3];
      if ( v10 )
      {
        v9 = (_DWORD *)((char *)v9 + v10);
        if ( v9 )
          continue;
      }
      goto LABEL_17;
    }
  }
  else
  {
LABEL_17:
    v9 = nullptr;
  }
  ChunkData = (struct AnimHeader_s *)ILF_GetChunkData(v9, v4);
  ChunkData->ptPrev = nullptr;
  ChunkData->ptNext = nullptr;
  ChunkData->pxRawFile = v4;
  if ( v4 )
  {
    v12 = v4[1];
    if ( v12 )
    {
      v13 = v4[2];
      if ( (v13 & ~(v13 - 1)) == v13 )
      {
        v14 = ~(v13 - 1) & (v13 + 19);
        if ( v14 < v12 )
        {
          v15 = (_DWORD *)((char *)v4 + v14);
          goto LABEL_25;
        }
      }
      else
      {
        ILF_nLastError = 1;
      }
    }
  }
  v15 = nullptr;
LABEL_25:
  if ( v15 )
  {
    while ( *v15 != 1163284052 )
    {
      v16 = v15[3];
      if ( v16 )
      {
        v15 = (_DWORD *)((char *)v15 + v16);
        if ( v15 )
          continue;
      }
      goto LABEL_29;
    }
  }
  else
  {
LABEL_29:
    v15 = nullptr;
  }
  ChunkData->ptFirstEvent = (struct AnimEvent_s *)ILF_GetChunkData(v15, v4);
  if ( v4 )
  {
    v17 = v4[1];
    if ( v17 )
    {
      v18 = v4[2];
      if ( (v18 & ~(v18 - 1)) == v18 )
      {
        v19 = ~(v18 - 1) & (v18 + 19);
        if ( v19 < v17 )
        {
          v20 = (_DWORD *)((char *)v4 + v19);
          goto LABEL_37;
        }
      }
      else
      {
        ILF_nLastError = 1;
      }
    }
  }
  v20 = nullptr;
LABEL_37:
  if ( v20 )
  {
    while ( *v20 != 1212761426 )
    {
      v21 = v20[3];
      if ( v21 )
      {
        v20 = (_DWORD *)((char *)v20 + v21);
        if ( v20 )
          continue;
      }
      goto LABEL_41;
    }
  }
  else
  {
LABEL_41:
    v20 = nullptr;
  }
  v22 = (unsigned __int8 *)ILF_GetChunkData(v20, v4);
  v23 = Hierarchy_Register(v22, ChunkData, nullptr);
  nAttachObjects = ChunkData->nAttachObjects;
  ChunkData->ptHierarchy = v23;
  if ( nAttachObjects )
  {
    if ( v4 )
    {
      v25 = v4[1];
      if ( v25 )
      {
        v26 = v4[2];
        if ( (v26 & ~(v26 - 1)) == v26 )
        {
          v27 = ~(v26 - 1) & (v26 + 19);
          if ( v27 < v25 )
          {
            v28 = (_DWORD *)((char *)v4 + v27);
LABEL_50:
            if ( v28 )
            {
              while ( *v28 != 1096045633 )
              {
                v29 = v28[3];
                if ( v29 )
                {
                  v28 = (_DWORD *)((char *)v28 + v29);
                  if ( v28 )
                    continue;
                }
                goto LABEL_54;
              }
            }
            else
            {
LABEL_54:
              v28 = nullptr;
            }
            ChunkData->ptFirstAttachObject = (struct Anim_AttachObject_t *)ILF_GetChunkData(v28, v4);
            goto LABEL_56;
          }
        }
        else
        {
          ILF_nLastError = 1;
        }
      }
    }
    v28 = nullptr;
    goto LABEL_50;
  }
LABEL_56:
  v30 = 0;
  if ( nAttachObjects > 0 )
  {
    v31 = 0;
    do
    {
      ptFirstAttachObject = ChunkData->ptFirstAttachObject;
      ptFirstKey = ptFirstAttachObject[v31].ptFirstKey;
      p_ptFirstKey = &ptFirstAttachObject[v31].ptFirstKey;
      if ( ptFirstKey )
        *p_ptFirstKey = (struct AnimEvent_AttachKey_t *)((char *)ChunkData->ptFirstEvent + 4 * (_DWORD)ptFirstKey);
      ++v30;
      ++v31;
    }
    while ( v30 < ChunkData->nAttachObjects );
  }
  ptFirstEvent = ChunkData->ptFirstEvent;
  for ( i = 0; i < ChunkData->nEvents; ++i )
  {
    ptNext = ptFirstEvent->ptNext;
    if ( ptNext )
      ptFirstEvent->ptNext = (struct AnimEvent_s *)((char *)ChunkData->ptFirstEvent + 4 * (_DWORD)ptNext);
    ptFirstEvent = (struct AnimEvent_s *)((char *)ptFirstEvent + 4 * ptFirstEvent->nLen);
  }
  return ChunkData;
}

// source: e/3/hierarchy.c:357  [anchor-hash]
int __cdecl Hierarchy_GetNumBones(unsigned __int8 *ptHierarchy)
{
  int v2; // ecx
  int result; // eax
  int v4; // edx
  int v5; // edx

  v2 = 0;
  result = 1;
  do
  {
    v4 = *ptHierarchy;
    result += v4;
    ++ptHierarchy;
    v5 = v4 + v2;
    v2 = v5 - 1;
  }
  while ( v5 > 0 );
  return result;
}

// source: e/3/hierarchy.c:384  [anchor-strings]
int __cdecl Hierarchy_GetBone(unsigned __int8 *ptHierarchy, char *zName)
{
  struct QHashTable_s *v2; // esi
  int v3; // eax
  int v4; // esi
  int v5; // edi
  int v6; // ebx

  v2 = Hierarchy_ptHashTable;
  v3 = Hierarchy_ptHashTable->tPrivate.pfHashFunction(Hierarchy_ptHashTable->tPrivate.nHashTableSize, ptHierarchy);
  v4 = ((int  (__cdecl *)(struct QHashTable_s *, unsigned int, const void *))Hierarchy_ptHashTable->tPrivate.pfFindElement)(v2, v3, (const void *)(ptHierarchy));
  v5 = 0;
  if ( *(int *)(v4 + 4) <= 0 )
  {
LABEL_5:
    LDebug_Error("Bone '%s' could not be located\n", zName);
    abort();
  }
  v6 = 0;
  while ( strncmp(zName, (char *)(v6 + *(_DWORD *)(v4 + 8)), 0x10u) )
  {
    ++v5;
    v6 += 16;
    if ( v5 >= (int)(*(_DWORD *)(v4 + 4)) )
      goto LABEL_5;
  }
  return v5;
}

// source: e/3/hierarchy.c:422  [anchor-callee]
struct AnimHeader_s *__cdecl Hierarchy_GetAnim(unsigned __int8 *ptHierarchy, char *zName)
{
  struct QHashTable_s *v2; // esi
  int v3; // eax
  int v4; // eax
  int v5; // esi
  int v6; // eax

  v2 = Hierarchy_ptHashTable;
  v3 = Hierarchy_ptHashTable->tPrivate.pfHashFunction(Hierarchy_ptHashTable->tPrivate.nHashTableSize, ptHierarchy);
  v4 = ((int  (__cdecl *)(struct QHashTable_s *, unsigned int, const void *))Hierarchy_ptHashTable->tPrivate.pfFindElement)(v2, v3, (const void *)(ptHierarchy));
  v5 = *(_DWORD *)v4;
  v6 = (*(int (__cdecl **)(_DWORD, char *))(*(_DWORD *)v4 + 12))(*(_DWORD *)(*(_DWORD *)v4 + 4), zName);
  return (*(struct AnimHeader_s * (__cdecl **)(int, int, const void *))(v5 + 28))(v5, v6, (const void *)(zName));
}

// source: e/3/hierarchy.c:448  [anchor-callee]
char *__cdecl Hierarchy_MarkSubHierarchy(char *ptHierarchy, int nRootID, char *aisActive)
{
  int v3; // ebp
  char *v5; // ecx
  char *result; // eax
  char v7; // dl
  int v8; // edi
  int v9; // esi

  v3 = nRootID;
  v5 = aisActive;
  result = aisActive + 1;
  if ( nRootID >= 0 )
  {
    v7 = 1;
  }
  else
  {
    v3 = -nRootID;
    v7 = 0;
  }
  v8 = 0;
  *aisActive = v7 == 0;
  if ( result != aisActive )
  {
    do
    {
      if ( v8 == v3 )
        *v5 = v7;
      v9 = *ptHierarchy++;
      if ( v9 > 0 )
      {
        do
        {
          *result++ = *v5;
          --v9;
        }
        while ( v9 );
      }
      ++v5;
      ++v8;
    }
    while ( result != v5 );
  }
  return result;
}

// source: e/3/hierarchy.c:504  [anchor-mhash]
int __cdecl Hierarchy_GetAnimTotalTime(unsigned __int8 *ptHierarchy, char *zName)
{
  struct QHashTable_s *v2; // esi
  int v3; // eax
  int v4; // eax
  int v5; // esi
  int v6; // eax
  int v7; // eax

  v2 = Hierarchy_ptHashTable;
  v3 = Hierarchy_ptHashTable->tPrivate.pfHashFunction(Hierarchy_ptHashTable->tPrivate.nHashTableSize, ptHierarchy);
  v4 = ((int  (__cdecl *)(struct QHashTable_s *, unsigned int, const void *))Hierarchy_ptHashTable->tPrivate.pfFindElement)(v2, v3, (const void *)(ptHierarchy));
  v5 = *(_DWORD *)v4;
  v6 = (*(int (__cdecl **)(_DWORD, char *))(*(_DWORD *)v4 + 12))(*(_DWORD *)(*(_DWORD *)v4 + 4), zName);
  v7 = (*(int (__cdecl **)(int, int, const void *))(v5 + 28))(v5, v6, (const void *)(zName));
  if ( v7 )
    return *(_DWORD *)(v7 + 16);
  else
    return 0;
}

// source: e/3/hierarchy.c:529  [anchor-mhash]
void __cdecl Hierarchy_GetAnimDeltaTranslation(
        struct real32x3_t *ptDeltaTranslation,
        unsigned __int8 *ptHierarchy,
        char *zName)
{
  struct QHashTable_s *v3; // esi
  int v4; // eax
  int v5; // eax
  int v6; // esi
  int v7; // eax
  int v8; // eax
  int v9; // edx
  char v10; // cl
  int v11; // eax
  int i; // ecx

  v3 = Hierarchy_ptHashTable;
  v4 = Hierarchy_ptHashTable->tPrivate.pfHashFunction(Hierarchy_ptHashTable->tPrivate.nHashTableSize, ptHierarchy);
  v5 = ((int  (__cdecl *)(struct QHashTable_s *, unsigned int, const void *))Hierarchy_ptHashTable->tPrivate.pfFindElement)(v3, v4, (const void *)(ptHierarchy));
  v6 = *(_DWORD *)v5;
  v7 = (*(int (__cdecl **)(_DWORD, char *))(*(_DWORD *)v5 + 12))(*(_DWORD *)(*(_DWORD *)v5 + 4), zName);
  v8 = (*(int (__cdecl **)(int, int, const void *))(v6 + 28))(v6, v7, (const void *)(zName));
  ptDeltaTranslation->vX = 0.0;
  ptDeltaTranslation->vY = 0.0;
  ptDeltaTranslation->vZ = 0.0;
  if ( v8 )
  {
    v9 = *(_DWORD *)(v8 + 32);
    v10 = 1;
    while ( *(_BYTE *)v9 != 3 )
    {
      if ( *(_BYTE *)v9 == 0xFF )
        goto LABEL_10;
LABEL_11:
      v9 += 4 * *(unsigned __int16 *)(v9 + 2);
      if ( !v10 )
        return;
    }
    v11 = *(_DWORD *)(v9 + 8);
    if ( v11 )
    {
      for ( i = *(_DWORD *)(v11 + 8); i; i = *(_DWORD *)(i + 8) )
        v11 = i;
      ptDeltaTranslation->vX = *(float *)(v11 + 12) - *(float *)(v9 + 12);
      ptDeltaTranslation->vY = *(float *)(v11 + 16) - *(float *)(v9 + 16);
      ptDeltaTranslation->vZ = *(float *)(v11 + 20) - *(float *)(v9 + 20);
    }
LABEL_10:
    v10 = 0;
    goto LABEL_11;
  }
}
