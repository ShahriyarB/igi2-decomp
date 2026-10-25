/* b/1/pc/pc_devmem.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: b/1/pc/pc_devmem.c:105  [anchor-mhash]
void __cdecl DevMem_InitFile(
        struct MemFile_s *ptMemFile,
        struct DirNode_s *ptDirNode,
        char *zName)
{
  memset(ptMemFile, 0, sizeof(struct MemFile_s));
  ptMemFile->ptDir = ptDirNode;
  strcpy(ptMemFile->zName, zName);
  ptMemFile->ptPrev = nullptr;
  ptMemFile->ptNext = nullptr;
  List_AddTail(ptMemFile, (int)&ptDirNode->tFileList);
}

// source: b/1/pc/pc_devmem.c:127  [anchor-callee]
struct DirNode_s *__cdecl DevMem_InitDir(
        struct DirNode_s *ptDirNode,
        char *zName)
{
  int v2; // esi
  char v3; // dl

  v2 = ptDirNode->zName - zName;
  do
  {
    v3 = *zName;
    zName[v2] = *zName;
    ++zName;
  }
  while ( v3 );
  ptDirNode->tChildList.ptHead = (struct DirNode_s *)&ptDirNode->tChildList.ptMiddle;
  ptDirNode->tChildList.ptTail = (struct DirNode_s *)&ptDirNode->tChildList;
  ptDirNode->tChildList.ptMiddle = nullptr;
  ptDirNode->ptPrev = nullptr;
  ptDirNode->ptNext = nullptr;
  ptDirNode->tFileList.ptHead = (struct MemFile_s *)&ptDirNode->tFileList.ptMiddle;
  ptDirNode->tFileList.ptTail = (struct MemFile_s *)&ptDirNode->tFileList;
  ptDirNode->tFileList.ptMiddle = nullptr;
  return ptDirNode;
}

// source: b/1/pc/pc_devmem.c:146  [anchor-callee]
struct MemFile_s *__cdecl DevMem_FindFileInDir(
        struct DirNode_s *ptDirNode,
        char *zName,
        enum bool isCreate)
{
  struct MemFile_s *ptHead; // edi
  struct MemFile_s *ptNext; // esi
  struct MemFile_s *v5; // ebp
  char *v6; // esi

  ptHead = ptDirNode->tFileList.ptHead;
  ptNext = ptHead->ptNext;
  v5 = nullptr;
  if ( !ptHead->ptNext )
    goto LABEL_6;
  while ( _stricmp(zName, ptHead->zName) )
  {
    ptHead = ptNext;
    ptNext = ptNext->ptNext;
    if ( !ptNext )
      goto LABEL_6;
  }
  v5 = ptHead;
  if ( !ptHead )
  {
LABEL_6:
    if ( isCreate )
    {
      v6 = (char *)Mem_AllocFn(300, 4);
      memset(v6, 0, 0x12Cu);
      *((_DWORD *)v6 + 73) = ptDirNode;
      strcpy(v6 + 32, zName);
      *((_DWORD *)v6 + 1) = 0;
      *(_DWORD *)v6 = 0;
      return (struct MemFile_s *)List_AddTail(v6, (int)&ptDirNode->tFileList);
    }
  }
  return v5;
}

// source: b/1/pc/pc_devmem.c:179  [anchor-caller]
struct DirNode_s *__cdecl DevMem_TraversePath(
        struct DirNode_s *ptDirNode,
        char *zPath,
        enum bool isCreateNode)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct DirNode_s *ptFound; };
    struct { char igi2_o1[8]; char zWorkPath[260]; };
    char igi2_extent[268];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  char *v4; // ecx
  char i; // al
  struct DirNode_s *ptHead; // edi
  struct DirNode_s *ptNext; // esi
  struct DirNode_s *inited; // eax

  igi2_frame.ptFound = nullptr;
  v4 = igi2_frame.zWorkPath;
  while ( *zPath == 47 || *zPath == 92 )
    ++zPath;
  for ( i = *zPath; i; ++zPath )
  {
    if ( i == 47 )
      break;
    if ( i == 92 )
      break;
    *v4 = i;
    i = zPath[1];
    ++v4;
  }
  *v4 = 0;
  if ( !strlen(igi2_frame.zWorkPath) )
    return ptDirNode;
  ptHead = ptDirNode->tChildList.ptHead;
  ptNext = ptHead->ptNext;
  if ( ptHead->ptNext )
  {
    while ( _stricmp(igi2_frame.zWorkPath, ptHead->zName) )
    {
      ptHead = ptNext;
      ptNext = ptNext->ptNext;
      if ( !ptNext )
        goto LABEL_15;
    }
    igi2_frame.ptFound = ptHead;
    if ( ptHead )
      return DevMem_TraversePath(igi2_frame.ptFound, zPath, isCreateNode);
  }
LABEL_15:
  if ( isCreateNode )
  {
    igi2_frame.ptFound = (struct DirNode_s *)Mem_AllocFn(292, 4);
    inited = DevMem_InitDir(igi2_frame.ptFound, igi2_frame.zWorkPath);
    if ( List_AddTail(inited, (int)&ptDirNode->tChildList) )
      return DevMem_TraversePath(igi2_frame.ptFound, zPath, isCreateNode);
  }
  return igi2_frame.ptFound;
}

// source: b/1/pc/pc_devmem.c:241  [anchor-callee]
char *__cdecl DevMem_SplitPath(char *zPathBuffer, char *zFilenameBuffer, char *zFullpath)
{
  #pragma pack(push, 1)
  union
  {
    struct { char zName[260]; };
    struct { char igi2_o1[260]; char zPath[260]; };
    struct { char igi2_o2[520]; char zExtension[260]; };
    struct { char igi2_o3[780]; char zDrive[260]; };
    char igi2_extent[1040];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  char *result; // eax

  splitpath(zFullpath, igi2_frame.zDrive, igi2_frame.zPath, igi2_frame.zName, igi2_frame.zExtension);
  strcpy(zPathBuffer, igi2_frame.zPath);
  strcpy(zFilenameBuffer, igi2_frame.zName);
  result = (char *)(strlen(igi2_frame.zExtension) + 1);
  qmemcpy(&zFilenameBuffer[strlen(zFilenameBuffer)], igi2_frame.zExtension, (unsigned int)result);
  return result;
}

// source: b/1/pc/pc_devmem.c:263  [anchor-caller]
struct MemFile_s *__cdecl DevMem_FindFile(char *zName, enum bool isCreate)
{
  #pragma pack(push, 1)
  union
  {
    struct { char zPath[260]; };
    struct { char igi2_o1[260]; char zFilename[260]; };
    char igi2_extent[520];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct DirNode_s *v2; // eax

  DevMem_SplitPath(igi2_frame.zPath, igi2_frame.zFilename, zName);
  v2 = DevMem_TraversePath(&DevMem_tRootDir, igi2_frame.zPath, isCreate);
  if ( v2 )
    return DevMem_FindFileInDir(v2, igi2_frame.zFilename, isCreate);
  else
    return nullptr;
}

// source: b/1/pc/pc_devmem.c:289  [size]
void __cdecl DevMem_RemoveFile(struct MemFile_s *ptMemFile)
{
  _DWORD **v1; // eax
  int v2; // esi

  v1 = Node_Remove(ptMemFile);
  if ( v1 )
  {
    v2 = *(_DWORD *)((unsigned int)(v1 - 1) & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v2);
    memset(*(void **)(v2 + 8), 0xCDu, *(_DWORD *)(v2 + 16));
    free((void *)v2);
  }
}

// source: b/1/pc/pc_devmem.c:305  [anchor-mhash]
struct DevMemFile_s *__cdecl DevMem_NewHandle(struct MemFile_s *ptMemFile, enum bool isWrite)
{
  struct DevMemFile_s *v2; // esi
  struct QVector_s *v3; // eax

  v2 = (struct DevMemFile_s *)Mem_AllocFn(296, 4);
  memset(v2, 0, sizeof(struct DevMemFile_s));
  v2->ptMemFile = ptMemFile;
  v3 = DevMem_ptFileHandleVector;
  v2->isWrite = isWrite;
  QVector_AddElement(v3, v2);
  return v2;
}

// source: b/1/pc/pc_devmem.c:328  [anchor-hash]
struct DevMemFile_s *__cdecl DevMem_DeleteHandle(struct DevMemFile_s *ptDevMemFile)
{
  struct QVector_s *v1; // edx
  struct DevMemFile_s *result; // eax
  void **i; // esi
  unsigned int v5; // edi
  enum bool isStrictOrder; // esi
  void **papxElement; // edx

  v1 = DevMem_ptFileHandleVector;
  result = nullptr;
  if ( DevMem_ptFileHandleVector->tPrivate.nElements )
  {
    for ( i = DevMem_ptFileHandleVector->tPrivate.papxElement; *i != ptDevMemFile; ++i )
    {
      result = (struct DevMemFile_s *)((char *)result + 1);
      if ( (unsigned int)result >= DevMem_ptFileHandleVector->tPrivate.nElements )
        return result;
    }
    v5 = DevMem_ptFileHandleVector->tPrivate.nElements - 1;
    DevMem_ptFileHandleVector->tPrivate.nElements = v5;
    if ( (unsigned int)result < v5 )
    {
      isStrictOrder = v1->tPrivate.isStrictOrder;
      papxElement = v1->tPrivate.papxElement;
      if ( isStrictOrder )
        return (struct DevMemFile_s *)memmove(
                                        &papxElement[(_DWORD)result],
                                        &papxElement[(_DWORD)result + 1],
                                        4 * (v5 - (_DWORD)result));
      else
        papxElement[(_DWORD)result] = papxElement[v5];
    }
  }
  return result;
}

// source: b/1/pc/pc_devmem.c:354  [anchor-mhash]
void __cdecl DevMem_Remove(int eDevice, char *zFilename)
{
  struct MemFile_s *File; // eax

  File = DevMem_FindFile(zFilename, false);
  if ( File )
    DevMem_RemoveFile(File);
}

// source: b/1/pc/pc_devmem.c:381  [size]
int __cdecl DevMem_DirList(
        int eDeviceID,
        char *zPath,
        void (__cdecl *pfCallback)(struct FileDirListCallbackContext_s *, void *),
        void *pxContext)
{
  return 0;
}

// source: b/1/pc/pc_devmem.c:394  [size]
struct File_s *__cdecl DevMem_New(int eDeviceID, char *zFilename, int bOpenMode)
{
  struct MemFile_s *v3; // esi
  struct MemFile_s *File; // eax
  struct _SYSTEMTIME tSystemTime; // [esp+4h] [ebp-10h] BYREF

  if ( bOpenMode == 1 )
  {
    File = DevMem_FindFile(zFilename, false);
    if ( File )
      return (struct File_s *)DevMem_NewHandle(File, false);
  }
  else
  {
    if ( bOpenMode <= 1 || bOpenMode > 3 )
    {
      LDebug_Error("Illegal openmode (%X) for file %s.", bOpenMode, zFilename);
      abort();
    }
    v3 = DevMem_FindFile(zFilename, true);
    if ( v3 )
    {
      GetSystemTime(&tSystemTime);
      SystemTimeToFileTime(&tSystemTime, &v3->tFileTime.tFileTime);
      return (struct File_s *)DevMem_NewHandle(v3, true);
    }
  }
  return nullptr;
}

// source: b/1/pc/pc_devmem.c:438  [size]
void __cdecl DevMem_Delete(int eDeviceID, struct File_s *ptFile)
{
  DevMem_DeleteHandle((struct DevMemFile_s *)ptFile);
}

// source: b/1/pc/pc_devmem.c:456  [anchor-mhash]
unsigned int __cdecl DevMem_Read(int eDeviceID, struct File_s *ptFile, void *pxBuffer, unsigned int nBytes)
{
  enum bool isAsyncReadComplete; // ecx
  int v5; // esi
  unsigned int result; // eax
  unsigned int v7; // ecx

  isAsyncReadComplete = ptFile[1].isAsyncReadComplete;
  v5 = ptFile[1].eDeviceID;
  result = *(_DWORD *)(v5 + 28) - isAsyncReadComplete;
  v7 = nBytes + isAsyncReadComplete;
  if ( v7 < result )
    result = v7;
  if ( result )
  {
    qmemcpy(pxBuffer, *(void **)(v5 + 8), result);
    ptFile[1].isAsyncReadComplete += result;
  }
  return result;
}

// source: b/1/pc/pc_devmem.c:490  [anchor-mhash]
unsigned int __cdecl DevMem_Write(int eDeviceID, struct File_s *ptFile, void *pxBuffer, unsigned int nBytes)
{
  unsigned int result; // eax
  int v6; // ebx
  unsigned __int32 v7; // ecx
  unsigned __int8 *v8; // eax
  int v9; // ecx
  enum bool v10; // esi
  enum bool v11; // ecx
  unsigned __int8 *pnNewData; // [esp+4h] [ebp-4h]
  unsigned int ptFilea = *(unsigned int *)&ptFile; // [esp+10h] [ebp+8h] ARGSLOT

  if ( ptFile[1].isAsync == false )
    return 0;
  result = nBytes;
  if ( !nBytes )
    return 0;
  v6 = ptFile[1].eDeviceID;
  v7 = *(_DWORD *)(v6 + 20);
  if ( nBytes + ptFile[1].isAsyncReadComplete >= v7 )
  {
    if ( nBytes > 0x400 )
      ptFilea = (nBytes + 2046) & 0xFFFFFC00;
    else
      ptFilea = 1024;
    v8 = (unsigned __int8 *)Mem_AllocFn(ptFilea + v7, 4);
    pnNewData = v8;
    if ( *(_DWORD *)(v6 + 20) )
    {
      qmemcpy(v8, *(void **)(v6 + 8), *(_DWORD *)(v6 + 28));
      Mem_DeAllocFn(*(void **)(v6 + 8));
      v8 = pnNewData;
      *(_DWORD *)(v6 + 8) = 0;
    }
    v9 = *(_DWORD *)(v6 + 20);
    *(_DWORD *)(v6 + 8) = v8;
    result = nBytes;
    *(_DWORD *)(v6 + 20) = ptFilea + v9;
  }
  qmemcpy((void *)(ptFile[1].isAsyncReadComplete + *(_DWORD *)(v6 + 8)), pxBuffer, result);
  v10 = result + ptFile[1].isAsyncReadComplete;
  ptFile[1].isAsyncReadComplete = v10;
  v11 = *(_DWORD *)(v6 + 28);
  if ( v11 <= (unsigned int)v10 )
    v11 = v10;
  *(_DWORD *)(v6 + 28) = v11;
  return result;
}

// source: b/1/pc/pc_devmem.c:548  [anchor-mhash]
int __cdecl DevMem_Seek(int eDeviceID, struct File_s *ptFile, int nOffset, int eOrigin)
{
  int v4; // ecx
  enum bool v5; // eax
  enum bool v7; // ecx
  enum bool v8; // ecx

  v4 = ptFile[1].eDeviceID;
  v5 = nOffset < 0 ? false : nOffset;
  if ( eOrigin )
  {
    if ( eOrigin != 1 )
    {
      if ( eOrigin == 2 )
      {
        ptFile[1].isAsyncReadComplete = *(_DWORD *)(v4 + 28) - v5;
        return 0;
      }
      return 0;
    }
    v7 = *(_DWORD *)(v4 + 28);
    v5 += ptFile[1].isAsyncReadComplete;
    if ( v5 >= (unsigned int)v7 )
    {
      ptFile[1].isAsyncReadComplete = v7;
      return 0;
    }
  }
  else
  {
    v8 = *(_DWORD *)(v4 + 28);
    if ( v5 >= v8 )
      v5 = v8;
  }
  ptFile[1].isAsyncReadComplete = v5;
  return 0;
}

// source: b/1/pc/pc_devmem.c:585  [size]
int __cdecl DevMem_GetSize(int eDeviceID, struct File_s *ptFile)
{
  return *(_DWORD *)(ptFile[1].eDeviceID + 28);
}

// source: b/1/pc/pc_devmem.c:607  [size]
int __cdecl DevMem_GetPos(int eDeviceID, struct File_s *ptFile)
{
  return ptFile[1].isAsyncReadComplete;
}

// source: b/1/pc/pc_devmem.c:623  [size]
enum bool __cdecl DevMem_isEOF(int eDeviceID, struct File_s *ptFile)
{
  return ptFile[1].isAsyncReadComplete >= *(_DWORD *)(ptFile[1].eDeviceID + 28);
}

// source: b/1/pc/pc_devmem.c:643  [size]
enum FileStatus_e __cdecl DevMem_GetStatus(int eDeviceID, struct File_s *ptFile)
{
  return FILE_STATUS_READY;
}

// source: b/1/pc/pc_devmem.c:659  [size]
enum FileError_e __cdecl DevMem_GetError(int eDeviceID, struct File_s *ptFile)
{
  return FILE_ERROR_NONE;
}

// source: b/1/pc/pc_devmem.c:675  [size]
int __cdecl DevMem_Sync(int eDeviceID, struct File_s *ptFile, enum FileSyncMode_e eSyncMode)
{
  return 0;
}

// source: b/1/pc/pc_devmem.c:691  [anchor-mhash]
int __cdecl DevMem_printf(int eDeviceID, struct File_s *ptFile, char *zFormat, char *arg)
{
  char *v4; // edi
  signed int v5; // eax
  int v6; // esi
  size_t v7; // ebx
  char *v8; // esi
  int i; // ebp
  int v10; // esi
  int v11; // esi
  char zTemp[1024]; // [esp+Ch] [ebp-400h] BYREF

  v4 = arg;
  v5 = vsnprintf(zTemp, 0x400u, zFormat, arg);
  v6 = v5;
  if ( v5 >= 0 )
  {
    DevMem_Write(eDeviceID, ptFile, zTemp, v5);
    return v6;
  }
  else
  {
    v7 = 2048;
    v8 = (char *)Mem_AllocFn(2048, 4);
    for ( i = vsnprintf(v8, 0x800u, zFormat, arg); i <= 0; i = vsnprintf(v8, v7, zFormat, v4) )
    {
      if ( v8 )
      {
        v10 = *(_DWORD *)((unsigned int)(v8 - 4) & 0xFFFFFFFC);
        --Mem_nCurrentAllocations;
        Node_Remove((_DWORD **)v10);
        memset(*(void **)(v10 + 8), 0xCDu, *(_DWORD *)(v10 + 16));
        free((void *)v10);
        v4 = arg;
      }
      v7 *= 2;
      v8 = (char *)Mem_AllocFn(v7, 4);
    }
    DevMem_Write(eDeviceID, ptFile, v8, i);
    if ( v8 )
    {
      v11 = *(_DWORD *)((unsigned int)(v8 - 4) & 0xFFFFFFFC);
      --Mem_nCurrentAllocations;
      Node_Remove((_DWORD **)v11);
      memset(*(void **)(v11 + 8), 0xCDu, *(_DWORD *)(v11 + 16));
      free((void *)v11);
    }
    return i;
  }
}

// source: b/1/pc/pc_devmem.c:742  [size]
int __cdecl DevMem_GetFileTime(int eDeviceID, struct FileTime_s *ptFileTime, char *zFilename)
{
  struct MemFile_s *File; // eax

  ptFileTime->tFileTime.dwLowDateTime = 0;
  ptFileTime->tFileTime.dwHighDateTime = 0;
  File = DevMem_FindFile(zFilename, false);
  if ( !File )
    return -1;
  *ptFileTime = File->tFileTime;
  return 0;
}

// source: b/1/pc/pc_devmem.c:771  [anchor-callee]
int __cdecl DevMem_NewDevice(char *zDevicename)
{
  void **v1; // esi
  struct QVector_s *v2; // eax
  int result; // eax
  int v4; // ecx

  DevMem_InitDir(&DevMem_tRootDir, (char *)&g_zInitialValue);
  v1 = (void **)Mem_AllocFn(64, 4);
  v2 = (struct QVector_s *)Mem_AllocFn(24, 4);
  v2->tPrivate.papxElement = v1;
  v2->tPrivate.nElements = 0;
  v2->tPrivate.isPrivateMem = false;
  v2->tPrivate.isStrictOrder = true;
  v2->tPrivate.nArraySize = 16;
  v2->tPrivate.nReallocSize = 16;
  DevMem_ptFileHandleVector = v2;
  result = File_eFreeDeviceID;
  File_atDevice[File_eFreeDeviceID].eDeviceID = File_eFreeDeviceID;
  File_eFreeDeviceID = result + 1;
  v4 = result;
  File_atDevice[v4].pfNewDevice = DevMem_NewDevice;
  File_atDevice[v4].pfDeleteDevice = DevMem_DeleteDevice;
  File_atDevice[v4].pfNew = DevMem_New;
  File_atDevice[v4].pfDelete = DevMem_Delete;
  File_atDevice[v4].pfRead = DevMem_Read;
  File_atDevice[v4].pfWrite = DevMem_Write;
  File_atDevice[v4].pfSeek = DevMem_Seek;
  File_atDevice[v4].pfGetPos = (int (__cdecl *)(int, struct File_s *))DevMem_GetPos;
  File_atDevice[v4].pfGetSize = (unsigned int (__cdecl *)(int, struct File_s *))DevMem_GetSize;
  File_atDevice[v4].pfisEOF = DevMem_isEOF;
  File_atDevice[v4].pfGetStatus = (enum FileStatus_e (__cdecl *)(int, struct File_s *))DevMem_GetStatus;
  File_atDevice[v4].pfGetError = (enum FileError_e (__cdecl *)(int, struct File_s *))DevMem_GetError;
  File_atDevice[v4].pfSync = (int (__cdecl *)(int, struct File_s *, enum FileSyncMode_e))DevMem_Sync;
  File_atDevice[v4].pfDirList = (int (__cdecl *)(int, char *, void (__cdecl *)(struct FileDirListCallbackContext_s *, void *), void *))DevMem_DirList;
  File_atDevice[v4].pfGetFileTime = DevMem_GetFileTime;
  File_atDevice[v4].pfRemove = DevMem_Remove;
  File_atDevice[v4].pfPrintf = DevMem_printf;
  strcpy(File_atDevice[result].zDevicename, zDevicename);
  return result;
}

// source: b/1/pc/pc_devmem.c:817  [anchor-hash]
void __cdecl DevMem_DeleteDevice(int eDeviceID)
{
  struct QVector_s *v1; // eax
  bool v2; // zf
  int v3; // ecx

  v1 = DevMem_ptFileHandleVector;
  while ( v1->tPrivate.nElements )
  {
    v3 = v1->tPrivate.nElements - 1;
    v2 = v1->tPrivate.nElements == 1;
    v1->tPrivate.nElements = v3;
    if ( !v2 )
    {
      if ( v1->tPrivate.isStrictOrder )
      {
        memmove(v1->tPrivate.papxElement, v1->tPrivate.papxElement + 1, 4 * v3);
        v1 = DevMem_ptFileHandleVector;
      }
      else
      {
        *v1->tPrivate.papxElement = v1->tPrivate.papxElement[v3];
      }
    }
  }
  QVector_Delete(v1);
}
