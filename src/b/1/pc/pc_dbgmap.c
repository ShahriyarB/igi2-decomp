/* b/1/pc/pc_dbgmap.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: b/1/pc/pc_dbgmap.c:66  [size]
enum bool __cdecl DbgMap_ReadMapFileLine(
        char *zBuffer,
        unsigned int nBufferSize,
        struct _iobuf *ptFile)
{
  return !feof(ptFile) && fgets(zBuffer, nBufferSize, ptFile);
}

// source: b/1/pc/pc_dbgmap.c:86  [size]
enum bool __cdecl DbgMap_MakeSymbolRecord(char *zBuffer)
{
  #pragma pack(push, 1)
  union
  {
    struct { char zDummy2[256]; };
    struct { char igi2_o1[256]; char zDummy1[256]; };
    char igi2_extent[512];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  enum bool result; // eax
  unsigned int *p_nAllocated; // edi
  struct QObjectVector_s *v3; // esi
  char *v4; // esi

  result = Wildcard_MatchSimple(" ????:???????? *", nullptr, nullptr, (void *)zBuffer, 0);
  if ( result )
  {
    p_nAllocated = &DbgMap_ptSymbolsVector->nAllocated;
    v3 = DbgMap_ptSymbolsVector;
    if ( DbgMap_ptSymbolsVector->nAllocated == DbgMap_ptSymbolsVector->nSize )
      QObjectVector_Realloc(DbgMap_ptSymbolsVector, DbgMap_ptSymbolsVector->nReallocSize);
    v4 = (char *)v3->papxElement[(*p_nAllocated)++];
    if ( scprintf(zBuffer, " %04X:%08X %s %s %s %s", v4 + 512, v4 + 516, v4, igi2_frame.zDummy1, igi2_frame.zDummy2, v4 + 256) != 6 )
      QObjectVector_RemoveElement(DbgMap_ptSymbolsVector, *(_DWORD *)&v4[DbgMap_ptSymbolsVector->nElementSize - 4]);
    return true;
  }
  return result;
}

// source: b/1/pc/pc_dbgmap.c:121  [size]
int __cdecl DbgMap_SymbolRecordQSortCallback(void *p1, void *p2)
{
  unsigned int v2; // edx
  unsigned int v3; // esi
  bool v4; // cf
  unsigned int v5; // ecx
  unsigned int v6; // eax

  v2 = *(_DWORD *)(*(_DWORD *)p1 + 512);
  v3 = *(_DWORD *)(*(_DWORD *)p2 + 512);
  v4 = v3 < v2;
  if ( v3 == v2
    && (v5 = *(_DWORD *)(*(_DWORD *)p1 + 516), v6 = *(_DWORD *)(*(_DWORD *)p2 + 516), v4 = v6 < v5, v6 == v5) )
  {
    return 0;
  }
  else
  {
    return v4 ? 1 : -1;
  }
}

// source: b/1/pc/pc_dbgmap.c:145  [size]
enum bool __cdecl DbgMap_ReadAndParseMapFile(char *zFilename)
{
  FILE *v1; // esi
  struct QObjectVector_s *v2; // eax
  unsigned int nAllocated; // eax
  char zLine[4096]; // [esp+8h] [ebp-1000h] BYREF

  v1 = fopen(zFilename, "r");
  if ( !v1 )
    return false;
  v2 = (struct QObjectVector_s *)Mem_AllocFn(52, 4);
  v2->isStrictOrder = true;
  v2->nSize = 0;
  v2->nAllocated = 0;
  v2->nReallocSize = 256;
  v2->papxElement = nullptr;
  v2->nElementSize = 524;
  v2->tMemPool.nBlocks = 0;
  v2->tMemPool.nAllocatedBlocks = 0;
  v2->tMemPool.nAlignment = 4;
  v2->tMemPool.nBlockSize = 524;
  v2->tMemPool.nReAllocBlocks = 256;
  v2->tMemPool.tMemPoolFreeList.ptHead = nullptr;
  v2->tMemPool.tMemPoolSegmentList.ptHead = nullptr;
  DbgMap_ptSymbolsVector = v2;
  while ( !feof(v1) )
  {
    if ( !fgets(zLine, 4096, v1) || Wildcard_MatchSimple("  Address*", nullptr, nullptr, zLine, 0) )
    {
      if ( !feof(v1) )
      {
        fgets(zLine, 4096, v1);
        while ( !feof(v1) )
        {
          if ( !fgets(zLine, 4096, v1) || DbgMap_MakeSymbolRecord(zLine) == false )
          {
            while ( !feof(v1) )
            {
              if ( !fgets(zLine, 4096, v1) || Wildcard_MatchSimple(" Static symbols*", nullptr, nullptr, zLine, 0) )
              {
                if ( !feof(v1) )
                {
                  fgets(zLine, 4096, v1);
                  while ( !feof(v1) && fgets(zLine, 4096, v1) && DbgMap_MakeSymbolRecord(zLine) )
                    ;
                }
                goto LABEL_19;
              }
            }
            goto LABEL_19;
          }
        }
      }
      break;
    }
  }
LABEL_19:
  nAllocated = DbgMap_ptSymbolsVector->nAllocated;
  if ( nAllocated )
    qsort(DbgMap_ptSymbolsVector->papxElement, nAllocated, 4, DbgMap_SymbolRecordQSortCallback);
  fclose(v1);
  return true;
}

// source: b/1/pc/pc_dbgmap.c:208  [size]
enum bool __cdecl DbgMap_GetSymbolInfo(
        char *zBuffer,
        unsigned int nBuffersize,
        unsigned int nSection,
        unsigned int nOffset,
        char *zModule)
{
  unsigned int nAllocated; // edi
  char *v7; // ecx
  unsigned int v8; // edx
  void **papxElement; // esi
  char *v10; // eax

  if ( !DbgMap_ptSymbolsVector )
    return false;
  if ( !zModule )
    return false;
  if ( !zBuffer )
    return false;
  if ( strcmp(zModule, DbgMap_zModuleName) )
    return false;
  nAllocated = DbgMap_ptSymbolsVector->nAllocated;
  v7 = nullptr;
  v8 = 0;
  if ( !nAllocated )
    return false;
  papxElement = DbgMap_ptSymbolsVector->papxElement;
  do
  {
    v10 = (char *)*papxElement;
    if ( *((_DWORD *)*papxElement + 128) >= nSection && *((_DWORD *)v10 + 129) > nOffset )
      break;
    ++v8;
    ++papxElement;
    v7 = v10;
  }
  while ( v8 < nAllocated );
  if ( !v7 )
    return false;
  _snprintf(zBuffer, nBuffersize, "%s + 0x%x (%s)", v7, nOffset - *((_DWORD *)v7 + 129), v7 + 256);
  return true;
}

// source: b/1/pc/pc_dbgmap.c:254  [size]
void __cdecl DbgMap_Open()
{
  int v0; // eax
  char v1; // cl
  char *v2; // eax
  _BYTE *v3; // esi
  char v4; // al
  char zModulename[260]; // [esp+0h] [ebp-104h] BYREF

  GetModuleFileNameA(nullptr, zModulename, 0x104u);
  v0 = 0;
  do
  {
    v1 = zModulename[v0];
    DbgMap_zModuleName[v0++] = v1;
  }
  while ( v1 );
  v2 = strrchr(zModulename, 46);
  if ( v2 )
  {
    v3 = v2 + 1;
    *(_DWORD *)(v2 + 1) = 5259597;
    if ( DbgMap_ReadAndParseMapFile(zModulename) == false )
    {
      if ( *v3 != 92 )
      {
        do
          v4 = *--v3;
        while ( v4 != 92 );
      }
      strcpy(v3 + 1, "pc\\pc.map");
      DbgMap_ReadAndParseMapFile(zModulename);
    }
  }
}

// source: b/1/pc/pc_dbgmap.c:294  [size]
void __cdecl DbgMap_Close()
{
  if ( DbgMap_ptSymbolsVector )
  {
    QObjectVector_Delete(DbgMap_ptSymbolsVector);
    DbgMap_ptSymbolsVector = nullptr;
  }
}
