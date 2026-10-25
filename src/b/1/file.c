/* b/1/file.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: b/1/file.c:99  [anchor-callee]
struct FileLoaded_s *__cdecl File_NewLoadInfo(char *zFilename)
{
  _DWORD *v1; // esi

  v1 = Mem_AllocFn(strlen(zFilename) + 29, 4);
  memset(v1, 0, 0x1Cu);
  v1[1] = 0;
  *v1 = 0;
  List_AddTail(v1, (int)&File_tLoadInfoList);
  v1[2] = v1 + 7;
  strcpy((char *)v1 + 28, zFilename);
  return (struct FileLoaded_s *)v1;
}

// source: b/1/file.c:121  [anchor-callee]
void __cdecl File_DeleteLoadInfo(struct FileLoaded_s *ptLoadInfo)
{
  _DWORD **v1; // eax
  int v2; // esi

  v1 = Node_Remove(ptLoadInfo);
  if ( v1 )
  {
    v2 = *(_DWORD *)((unsigned int)(v1 - 1) & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v2);
    memset(*(void **)(v2 + 8), 0xCDu, *(_DWORD *)(v2 + 16));
    free((void *)v2);
  }
}

// source: b/1/file.c:135  [anchor-refs]
struct FileLoaded_s *__cdecl File_GetLoadInfo(void *pxMemory)
{
  struct FileLoaded_s *result; // eax
  struct FileLoaded_s *ptNext; // ecx

  result = File_tLoadInfoList.ptHead;
  ptNext = File_tLoadInfoList.ptHead->ptNext;
  if ( !File_tLoadInfoList.ptHead->ptNext )
  {
LABEL_4:
    LDebug_Error("No files loaded at address: %p", pxMemory);
    abort();
  }
  while ( result->pxData != pxMemory )
  {
    result = ptNext;
    ptNext = ptNext->ptNext;
    if ( !ptNext )
      goto LABEL_4;
  }
  return result;
}

// source: b/1/file.c:163  [anchor-callee]
int __cdecl File_GetCreationMode(char *zMode)
{
  char *v1; // esi
  int v2; // edi

  v1 = File_azAccessMode[0];
  v2 = 0;
  if ( !File_azAccessMode[0] )
    return 0;
  while ( strcmp(zMode, v1) )
  {
    v1 = File_azAccessMode[++v2];
    if ( !v1 )
      return 0;
  }
  return File_abAccessMode[v2];
}

// source: b/1/file.c:193  [anchor-strings]
int __cdecl File_SubstituteAlias(
        char *zFilename,
        char *zOrigFilename,
        int nAlias,
        enum bool isConvertToUpperCase)
{
  char *v4; // ebp
  int v6; // edi
  struct DevAlias_s *v7; // esi
  char *i; // esi
  char v9; // al
  char *zAliasPath; // edi
  char *j; // esi
  char *v12; // eax
  char k; // al
  char *v14; // esi
  char v15; // al
  int nNextAlias; // [esp+10h] [ebp-8h]
  int nNextAliasa; // [esp+10h] [ebp-8h]
  size_t nAliasLength; // [esp+14h] [ebp-4h]

  nNextAlias = nAlias;
  v4 = File_zLastSubstitutedPath;
  v6 = 0;
  v7 = File_atAlias;
  while ( 1 )
  {
    if ( !v7->eDeviceID )
    {
LABEL_5:
      for ( i = zOrigFilename; *i; ++v4 )
      {
        v9 = *i;
        if ( *i == 92 )
        {
          v9 = 47;
        }
        else if ( isConvertToUpperCase )
        {
          v9 = toupper(v9);
        }
        *zFilename++ = v9;
        ++i;
        *v4 = v9;
      }
      *zFilename = 0;
      *v4 = 0;
      return 0;
    }
    nAliasLength = strlen(v7->zAlias);
    if ( !strncmp(zOrigFilename, v7->zAlias, nAliasLength) )
      break;
    ++v7;
    ++v6;
    if ( (int)v7 >= 7356944 )
      goto LABEL_5;
  }
  zAliasPath = File_atAlias[v6].zAliasPath;
  for ( j = zAliasPath; nAlias; --nAlias )
  {
    v12 = strchr(j, 59);
    if ( !v12 )
    {
      LDebug_Error("Error in alias path: %s", zAliasPath);
      abort();
    }
    j = v12 + 1;
  }
  if ( strchr(j, 59) )
    nNextAliasa = nNextAlias + 1;
  else
    nNextAliasa = 0;
  for ( k = *j; *j != 59; ++v4 )
  {
    if ( !k )
      break;
    if ( k == 92 )
    {
      k = 47;
    }
    else if ( isConvertToUpperCase )
    {
      k = toupper(k);
    }
    *zFilename++ = k;
    ++j;
    *v4 = k;
    k = *j;
  }
  v14 = &zOrigFilename[nAliasLength];
  v15 = zOrigFilename[nAliasLength];
  if ( v15 )
  {
    do
    {
      if ( v15 == 92 )
      {
        v15 = 47;
      }
      else if ( isConvertToUpperCase )
      {
        v15 = toupper(v15);
      }
      *zFilename++ = v15;
      ++v14;
      *v4 = v15;
      v15 = *v14;
      ++v4;
    }
    while ( *v14 );
  }
  *zFilename = 0;
  *v4 = 0;
  return nNextAliasa;
}

// source: b/1/file.c:284  [anchor-hash]
int __cdecl File_AllocDeviceID()
{
  int result; // eax

  result = File_eFreeDeviceID;
  File_atDevice[File_eFreeDeviceID].eDeviceID = File_eFreeDeviceID;
  File_eFreeDeviceID = result + 1;
  return result;
}

// source: b/1/file.c:301  [anchor-hash]
int __cdecl File_DeAllocDeviceID(int eDeviceID)
{
  int result; // eax

  result = eDeviceID;
  File_atDevice[result].eDeviceID = 0;
  return result * 144;
}

// source: b/1/file.c:314  [anchor-callee]
int __cdecl File_IsValidDevicename(int *peDeviceID, char *zFilename)
{
  int v2; // edi
  char *zDevicename; // esi

  v2 = 1;
  zDevicename = File_atDevice[1].zDevicename;
  while ( !*((_DWORD *)zDevicename - 9) || strncmp(zDevicename, zFilename, strlen(zDevicename)) )
  {
    zDevicename += 144;
    ++v2;
    if ( (int)zDevicename >= 7359144 )
      return 0;
  }
  if ( peDeviceID )
    *peDeviceID = v2;
  return 1;
}

// source: b/1/file.c:350  [anchor-mhash]
int __cdecl File_GetDeviceID(char *zFilename)
{
  int v1; // ecx
  bool v2; // zf
  int result; // eax
  int eDeviceID; // [esp+0h] [ebp-4h] BYREF

  eDeviceID = v1;
  v2 = File_IsValidDevicename(&eDeviceID, zFilename) == 0;
  result = eDeviceID;
  if ( v2 )
    return File_eDefaultDevice;
  return result;
}

// source: b/1/file.c:373  [anchor-hash]
void __cdecl File_Open()
{
  int *p_eDeviceID; // eax

  p_eDeviceID = &File_atAlias[0].eDeviceID;
  do
  {
    *p_eDeviceID = 0;
    p_eDeviceID += 70;
  }
  while ( (int)p_eDeviceID < 7357220 );
  memset(File_atDevice, 0, sizeof(File_atDevice));
  File_eFreeDeviceID = 1;
  File_zLastSubstitutedPath[0] = 0;
  File_RegisterDevices();
  File_tDummyAsyncFile.isAsync = false;
  File_tLoadInfoList.ptHead = (struct FileLoaded_s *)&File_tLoadInfoList.ptMiddle;
  File_tLoadInfoList.ptTail = (struct FileLoaded_s *)&File_tLoadInfoList;
  File_tLoadInfoList.ptMiddle = nullptr;
}

// source: b/1/pc/pc_file.c:44  [layout]
void __cdecl File_Close()
{
  int v0; // ecx
  struct FileLoaded_s *ptHead; // eax
  struct FileLoaded_s *i; // ebx
  _DWORD **v3; // eax
  int v4; // esi
  bool v5; // zf
  int v6; // eax
  int v7; // eax
  int v8; // eax
  int peDeviceID; // [esp+0h] [ebp-4h] BYREF

  ptHead = File_tLoadInfoList.ptHead;
  for ( i = File_tLoadInfoList.ptHead->ptNext; i; i = i->ptNext )
  {
    v3 = Node_Remove(ptHead);
    if ( v3 )
    {
      v4 = *(_DWORD *)((unsigned int)(v3 - 1) & 0xFFFFFFFC);
      --Mem_nCurrentAllocations;
      Node_Remove((_DWORD **)v4);
      memset(*(void **)(v4 + 8), 0xCDu, *(_DWORD *)(v4 + 16));
      free((void *)v4);
    }
    ptHead = i;
  }
  peDeviceID = v0;
  v5 = File_IsValidDevicename(&peDeviceID, "RAM:") == 0;
  v6 = peDeviceID;
  if ( v5 )
    v6 = File_eDefaultDevice;
  File_atDevice[v6].pfDeleteDevice(v6);
  v5 = File_IsValidDevicename(&peDeviceID, (char *)&g_zFileName.atPictureResources[13].ptPicture) == 0;
  v7 = peDeviceID;
  if ( v5 )
    v7 = File_eDefaultDevice;
  File_atDevice[v7].pfDeleteDevice(v7);
  v5 = File_IsValidDevicename(&peDeviceID, "REMOTE:") == 0;
  v8 = peDeviceID;
  if ( v5 )
    v8 = File_eDefaultDevice;
  File_atDevice[v8].pfDeleteDevice(v8);
}

// source: b/1/file.c:430  [size]
char *__cdecl File_SetDevicePath(int eDevice, char *zPath)
{
  int v2; // edx
  char v3; // cl

  v2 = File_atDevice[eDevice].zDevicepath - zPath;
  do
  {
    v3 = *zPath;
    zPath[v2] = *zPath;
    ++zPath;
  }
  while ( v3 );
  return zPath;
}

// source: b/1/file.c:445  [size]
char *__cdecl File_SetDeviceName(int eDevice, char *zName)
{
  int v2; // edx
  char v3; // cl

  v2 = File_atDevice[eDevice].zDevicename - zName;
  do
  {
    v3 = *zName;
    zName[v2] = *zName;
    ++zName;
  }
  while ( v3 );
  return zName;
}

// source: b/1/file.c:460  [anchor-hash]
void __cdecl File_CleanAlias()
{
  int *p_eDeviceID; // eax

  p_eDeviceID = &File_atAlias[0].eDeviceID;
  do
  {
    *p_eDeviceID = 0;
    p_eDeviceID += 70;
  }
  while ( (int)p_eDeviceID < 7357220 );
}

// source: b/1/file.c:481  [anchor-strings]
char *__cdecl File_RegisterAlias(char *zAlias, char *zPath)
{
  int IsValidDevicename; // eax
  int v4; // ebp
  int v5; // edx
  int *p_eDeviceID; // eax
  int v7; // edx
  int v8; // eax
  char *result; // eax
  int peDeviceID; // [esp+8h] [ebp-4h] BYREF

  IsValidDevicename = File_IsValidDevicename(&peDeviceID, zPath);
  v4 = peDeviceID;
  if ( !IsValidDevicename )
    v4 = File_eDefaultDevice;
  if ( !v4 )
  {
LABEL_7:
    LDebug_Error("Failed to register alias: %s", zAlias);
    abort();
  }
  File_RemoveAlias(zAlias);
  v5 = 0;
  p_eDeviceID = &File_atAlias[0].eDeviceID;
  while ( *p_eDeviceID )
  {
    p_eDeviceID += 70;
    ++v5;
    if ( (int)p_eDeviceID >= 7357220 )
      goto LABEL_7;
  }
  v7 = v5;
  strcpy(File_atAlias[v7].zAlias, zAlias);
  strcpy(File_atAlias[v7].zAliasPath, zPath);
  v8 = File_nAliases;
  File_atAlias[v7].eDeviceID = v4;
  result = (char *)(v8 + 1);
  File_nAliases = (int)result;
  return result;
}

// source: b/1/file.c:517  [anchor-callee]
void __cdecl File_RemoveAlias(char *zAlias)
{
  int v1; // edx
  struct DevAlias_s *v2; // edi
  int v3; // ebx
  int v4; // ebp
  int v5; // ecx
  int v6; // esi
  char *v7; // eax
  int v8; // edi
  char v9; // dl
  char *v10; // eax
  int v11; // edx
  char v12; // cl

  v1 = 0;
  v2 = File_atAlias;
  while ( !v2->eDeviceID || strcmp(v2->zAlias, zAlias) )
  {
    ++v2;
    ++v1;
    if ( (int)v2 >= 7356944 )
      return;
  }
  v3 = File_nAliases;
  v4 = File_nAliases - 1;
  if ( v1 < File_nAliases - 1 )
  {
    v5 = 280 * File_nAliases;
    v6 = v1;
    File_atAlias[v1].eDeviceID = (int)(&File_tLoadInfoList.ptTail)[70 * File_nAliases];
    v7 = (char *)&QTask_atQTaskEventType[490] + 280 * v3;
    v8 = (char *)&File_atAlias[v1] - v7;
    do
    {
      v9 = *v7;
      v7[v8] = *v7;
      ++v7;
    }
    while ( v9 );
    v10 = &QTask_atQTaskEventType[491].isFixmeContextUsed + v5;
    v11 = File_atAlias[v6].zAliasPath - (&QTask_atQTaskEventType[491].isFixmeContextUsed + v5);
    do
    {
      v12 = *v10;
      v10[v11] = *v10;
      ++v10;
    }
    while ( v12 );
  }
  File_nAliases = v4;
  (&File_tLoadInfoList.ptTail)[70 * v3] = nullptr;
}

// source: b/1/file.c:554  [anchor-strings]
int __cdecl File_DirList(
        char *zPath,
        void (__cdecl *pfCallback)(struct FileDirListCallbackContext_s *, void *),
        void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { int nCount; };
    struct { char igi2_o1[4]; int peDeviceID; };
    struct { char igi2_o2[8]; char zSubstPath[260]; };
    char igi2_extent[268];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  char *v3; // ecx
  int v4; // ebp
  int IsValidDevicename; // eax
  int v6; // esi
  char v7; // al
  int v8; // ecx
  char *v9; // eax

  v4 = 0;
  igi2_frame.nCount = 0;
  do
  {
    Game_MPRunNetwork(v3);
    v4 = File_SubstituteAlias(igi2_frame.zSubstPath, zPath, v4, false);
    IsValidDevicename = File_IsValidDevicename(&igi2_frame.peDeviceID, igi2_frame.zSubstPath);
    v6 = igi2_frame.peDeviceID;
    if ( !IsValidDevicename )
      v6 = File_eDefaultDevice;
    if ( v6 <= 0 || v6 >= 5 )
    {
      LDebug_Error("Illegal device name in path: \"%s\".", zPath);
LABEL_16:
      abort();
    }
    if ( File_atDevice[v6].isInitialised == false )
    {
      LDebug_Error("Device not present: %s", (char *)(144 * v6 + 7358424));
      goto LABEL_16;
    }
    if ( File_IsValidDevicename(nullptr, igi2_frame.zSubstPath) && (v7 = igi2_frame.zSubstPath[0], v8 = 0, igi2_frame.zSubstPath[0]) )
    {
      while ( v7 != 58 )
      {
        v7 = igi2_frame.zSubstPath[++v8];
        if ( !v7 )
          goto LABEL_11;
      }
      v9 = &igi2_frame.zSubstPath[v8 + 1];
    }
    else
    {
LABEL_11:
      v9 = igi2_frame.zSubstPath;
    }
    v3 = (char *)(File_atDevice[v6].pfDirList(v6, v9, pfCallback, pxContext) + igi2_frame.nCount);
    igi2_frame.nCount = (int)v3;
  }
  while ( v4 );
  return (int)v3;
}

// source: b/1/file.c:620  [anchor-callee]
struct File_s *__cdecl File_New(char *zFile, char *zOpenMode)
{
  #pragma pack(push, 1)
  union
  {
    struct { int nAlias; };
    struct { char igi2_o1[4]; int peDeviceID; };
    struct { char igi2_o2[8]; int bCreationMode; };
    char igi2_extent[16];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v2; // esi
  int IsValidDevicename; // eax
  int v4; // esi
  char v5; // al
  int v6; // ecx
  char *v7; // edx
  struct File_s *result; // eax

  v2 = 0;
  igi2_frame.bCreationMode = File_GetCreationMode(zOpenMode);
  while ( 1 )
  {
    igi2_frame.nAlias = File_SubstituteAlias(&byte_704420, zFile, v2, false);
    IsValidDevicename = File_IsValidDevicename(&igi2_frame.peDeviceID, &byte_704420);
    v4 = igi2_frame.peDeviceID;
    if ( !IsValidDevicename )
      v4 = File_eDefaultDevice;
    if ( v4 <= 0 || v4 >= 5 )
    {
      LDebug_Error("Illegal device name in path: \"%s\".", zFile);
LABEL_18:
      abort();
    }
    if ( File_atDevice[v4].isInitialised == false )
    {
      LDebug_Error("Device not present: %s", (char *)(144 * v4 + 7358424));
      goto LABEL_18;
    }
    if ( File_IsValidDevicename(nullptr, &byte_704420) && (v5 = byte_704420, v6 = 0, byte_704420) )
    {
      while ( v5 != 58 )
      {
        v5 = byte_704421[v6++];
        if ( !v5 )
          goto LABEL_11;
      }
      v7 = &byte_704421[v6];
    }
    else
    {
LABEL_11:
      v7 = &byte_704420;
    }
    if ( strlen(v7) )
    {
      result = File_atDevice[v4].pfNew(v4, v7, igi2_frame.bCreationMode);
      if ( result )
      {
        result->eDeviceID = v4;
        strcpy(result->zFilename, zFile);
        return result;
      }
    }
    if ( !igi2_frame.nAlias )
      return nullptr;
    v2 = igi2_frame.nAlias;
  }
}

// source: b/1/file.c:707  [anchor-callee]
void __cdecl File_Delete(struct File_s *ptFile)
{
  if ( ptFile == &File_tDummyAsyncFile )
    File_tDummyAsyncFile.isAsync = false;
  else
    File_atDevice[ptFile->eDeviceID].pfDelete(ptFile->eDeviceID, ptFile);
}

// source: b/1/file.c:737  [size]
unsigned int __cdecl File_Read(struct File_s *ptFile, void *pxBuffer, unsigned int nBytes)
{
  return File_atDevice[ptFile->eDeviceID].pfRead(ptFile->eDeviceID, ptFile, pxBuffer, nBytes);
}

// source: b/1/file.c:760  [anchor-callee]
unsigned int __cdecl File_Write(struct File_s *ptFile, void *pxBuffer, unsigned int nBytes)
{
  return File_atDevice[ptFile->eDeviceID].pfWrite(ptFile->eDeviceID, ptFile, pxBuffer, nBytes);
}

// source: b/1/file.c:783  [size]
int __cdecl File_Seek(struct File_s *ptFile, int nOffset, enum FileSeekMode_e eOrigin)
{
  return File_atDevice[ptFile->eDeviceID].pfSeek(ptFile->eDeviceID, ptFile, nOffset, eOrigin);
}

// source: b/1/file.c:802  [size]
enum bool __cdecl File_IsEOF(struct File_s *ptFile)
{
  return File_atDevice[ptFile->eDeviceID].pfisEOF(ptFile->eDeviceID, ptFile);
}

// source: b/1/file.c:822  [size]
unsigned int __cdecl File_GetSize(struct File_s *ptFile)
{
  return File_atDevice[ptFile->eDeviceID].pfGetSize(ptFile->eDeviceID, ptFile);
}

// source: b/1/file.c:842  [size]
int __cdecl File_GetPos(struct File_s *ptFile)
{
  return File_atDevice[ptFile->eDeviceID].pfGetPos(ptFile->eDeviceID, ptFile);
}

// source: b/1/file.c:862  [size]
enum FileStatus_e __cdecl File_GetStatus(struct File_s *ptFile)
{
  return File_atDevice[ptFile->eDeviceID].pfGetStatus(ptFile->eDeviceID, ptFile);
}

// source: b/1/file.c:881  [size]
enum FileError_e __cdecl File_GetError(struct File_s *ptFile)
{
  return File_atDevice[ptFile->eDeviceID].pfGetError(ptFile->eDeviceID, ptFile);
}

// source: b/1/file.c:900  [size]
void __cdecl File_WaitIO(struct File_s *ptFile)
{
  File_atDevice[ptFile->eDeviceID].pfSync(ptFile->eDeviceID, ptFile, FILE_SYNC_WAIT);
}

// source: b/1/file.c:919  [size]
void __cdecl File_Sync(struct File_s *ptFile, enum FileSyncMode_e eMode)
{
  ((void (__cdecl *)(int, struct File_s *))File_atDevice[ptFile->eDeviceID].pfSync)(ptFile->eDeviceID, ptFile);
}

// source: b/1/file.c:936  [anchor-strings]
int __cdecl File_GetFileTime(struct FileTime_s *ptFileTime, char *zFilename)
{
  #pragma pack(push, 1)
  union
  {
    struct { int peDeviceID; };
    struct { char igi2_o1[4]; char zRealFilename[512]; };
    char igi2_extent[516];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v2; // edi
  int IsValidDevicename; // eax
  int v4; // esi
  char v5; // al
  int v6; // ecx
  char *v7; // eax

  v2 = 0;
  while ( 1 )
  {
    v2 = File_SubstituteAlias(igi2_frame.zRealFilename, zFilename, v2, false);
    IsValidDevicename = File_IsValidDevicename(&igi2_frame.peDeviceID, igi2_frame.zRealFilename);
    v4 = igi2_frame.peDeviceID;
    if ( !IsValidDevicename )
      v4 = File_eDefaultDevice;
    if ( v4 <= 0 || v4 >= 5 )
    {
      LDebug_Error("Illegal device name in path: \"%s\".", igi2_frame.zRealFilename);
      abort();
    }
    if ( File_IsValidDevicename(nullptr, igi2_frame.zRealFilename) && (v5 = igi2_frame.zRealFilename[0], v6 = 0, igi2_frame.zRealFilename[0]) )
    {
      while ( v5 != 58 )
      {
        v5 = igi2_frame.zRealFilename[++v6];
        if ( !v5 )
          goto LABEL_10;
      }
      v7 = &igi2_frame.zRealFilename[v6 + 1];
    }
    else
    {
LABEL_10:
      v7 = igi2_frame.zRealFilename;
    }
    if ( !File_atDevice[v4].pfGetFileTime(v4, ptFileTime, v7) )
      return 0;
    if ( !v2 )
      return -1;
  }
}

// source: b/1/file.c:996  [anchor-strings]
void *__cdecl File_Load(char *zFilename, unsigned int *pnLength)
{
  #pragma pack(push, 1)
  union
  {
    struct { int v15; };
    struct { char igi2_o1[32]; void *pxMem; };
    struct { char igi2_o2[36]; unsigned int nFilesize; };
    char igi2_extent[40];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct File_s *v3; // eax
  struct File_s *v4; // esi
  int eDeviceID; // ecx
  int v6; // eax
  struct FileLoaded_s *Info; // eax
  void *v8; // edi
  unsigned int v10; // ebp
  struct FileLoaded_s *v11; // eax
  void *v12; // ebx
  struct FileLoaded_s *v13; // edi
  int v14; // eax

  v3 = File_New(zFilename, "r");
  v4 = v3;
  if ( !v3 )
    return nullptr;
  eDeviceID = v3->eDeviceID;
  v6 = v3->eDeviceID;
  if ( File_atDevice[v6].pfLoad )
  {
    Info = File_NewLoadInfo(zFilename);
    Info->eDeviceID = v4->eDeviceID;
    v8 = File_atDevice[v4->eDeviceID].pfLoad(v4->eDeviceID, v4, &igi2_frame.nFilesize, Info);
    if ( v4 == &File_tDummyAsyncFile )
      File_tDummyAsyncFile.isAsync = false;
    else
      File_atDevice[v4->eDeviceID].pfDelete(v4->eDeviceID, v4);
    if ( pnLength )
      *pnLength = igi2_frame.nFilesize;
    return v8;
  }
  igi2_frame.nFilesize = 0;
  v10 = File_atDevice[v6].pfGetSize(eDeviceID, v4);
  igi2_frame.pxMem = Mem_AllocFn(v10, 4);
  v11 = File_NewLoadInfo(zFilename);
  v12 = igi2_frame.pxMem;
  v13 = v11;
  v11->eDeviceID = v4->eDeviceID;
  v11->pxData = igi2_frame.pxMem;
  v11->nSize = v10;
  do
  {
    if ( File_atDevice[v4->eDeviceID].pfRead(v4->eDeviceID, v4, v12, v10) )
      break;
    v14 = v4->eDeviceID;
    igi2_frame.v15 = v4->eDeviceID;
    ++igi2_frame.nFilesize;
    File_atDevice[v14].pfSeek(igi2_frame.v15, v4, 0, 0);
    v12 = igi2_frame.pxMem;
  }
  while ( (int)igi2_frame.nFilesize < 10 );
  if ( igi2_frame.nFilesize == 10 )
  {
    LDebug_Error("Error while reading from file %s", v4->zFilename);
    abort();
  }
  File_atDevice[v4->eDeviceID].pfSync(v4->eDeviceID, v4, FILE_SYNC_WAIT);
  if ( File_atDevice[v4->eDeviceID].pfGetError(v4->eDeviceID, v4) )
  {
    File_DeleteLoadInfo(v13);
    Mem_DeAllocFn(v12);
    File_Delete(v4);
    if ( pnLength )
      *pnLength = 0;
    return nullptr;
  }
  if ( pnLength )
    *pnLength = v10;
  File_Delete(v4);
  return v12;
}

// source: b/1/file.c:1114  [anchor-strings]
struct File_s *__cdecl File_LoadAsync(char *zFilename, unsigned int *pnLength)
{
  struct File_s *v3; // eax
  struct File_s *v4; // esi
  struct FileLoaded_s *Info; // eax
  void *v7; // eax
  unsigned int v8; // esi
  unsigned int nLength; // [esp+8h] [ebp-4h] BYREF

  v3 = File_New(zFilename, "r");
  v4 = v3;
  if ( !v3 )
    return nullptr;
  if ( File_atDevice[v3->eDeviceID].pfAsyncLoad )
  {
    v3->isAsync = true;
    Info = File_NewLoadInfo(zFilename);
    Info->eDeviceID = v4->eDeviceID;
    File_atDevice[v4->eDeviceID].pfAsyncLoad(v4->eDeviceID, v4, pnLength, Info);
    return v4;
  }
  if ( File_tDummyAsyncFile.isAsync )
  {
    LDebug_Error("Cannot load more than one file at a time asynchronously.");
    abort();
  }
  v7 = File_Load(zFilename, &nLength);
  if ( !v7 )
    return nullptr;
  v8 = nLength;
  File_tDummyAsyncFile.pxAsyncBuffer = v7;
  File_tDummyAsyncFile.eDeviceID = -1;
  File_tDummyAsyncFile.isAsync = true;
  File_tDummyAsyncFile.isAsyncReadComplete = true;
  File_tDummyAsyncFile.nAsyncBytesRead = nLength;
  File_tDummyAsyncFile.nAsyncError = 0;
  strcpy(File_tDummyAsyncFile.zFilename, zFilename);
  if ( pnLength )
    *pnLength = v8;
  return &File_tDummyAsyncFile;
}

// source: b/1/file.c:1182  [anchor-hash]
unsigned int __cdecl File_GetAsyncBytesRead(struct File_s *ptFile)
{
  if ( ptFile != &File_tDummyAsyncFile )
    File_atDevice[ptFile->eDeviceID].pfUpdateAsyncStatus(ptFile->eDeviceID, ptFile);
  return ptFile->nAsyncBytesRead;
}

// source: b/1/file.c:1202  [anchor-hash]
enum bool __cdecl File_IsAsyncReadComplete(struct File_s *ptFile)
{
  if ( ptFile != &File_tDummyAsyncFile )
    File_atDevice[ptFile->eDeviceID].pfUpdateAsyncStatus(ptFile->eDeviceID, ptFile);
  return ptFile->isAsyncReadComplete;
}

// source: b/1/file.c:1225  [anchor-callee]
void __cdecl File_Flush(void *pxMemory)
{
  struct FileLoaded_s *ptHead; // esi
  struct FileLoaded_s *ptNext; // eax
  int eDeviceID; // eax
  void (__cdecl *pfFlush)(int, struct FileLoaded_s *); // ecx
  int v5; // ebx

  ptHead = File_tLoadInfoList.ptHead;
  ptNext = File_tLoadInfoList.ptHead->ptNext;
  if ( !File_tLoadInfoList.ptHead->ptNext )
  {
LABEL_4:
    LDebug_Error("No files loaded at address: %p", pxMemory);
    abort();
  }
  while ( ptHead->pxData != pxMemory )
  {
    ptHead = ptNext;
    ptNext = ptNext->ptNext;
    if ( !ptNext )
      goto LABEL_4;
  }
  eDeviceID = ptHead->eDeviceID;
  pfFlush = File_atDevice[eDeviceID].pfFlush;
  if ( pfFlush )
  {
    pfFlush(eDeviceID, ptHead);
    File_DeleteLoadInfo(ptHead);
  }
  else
  {
    if ( pxMemory )
    {
      v5 = *(_DWORD *)(((int)pxMemory - 4) & 0xFFFFFFFC);
      --Mem_nCurrentAllocations;
      Node_Remove((_DWORD **)v5);
      memset(*(void **)(v5 + 8), 0xCDu, *(_DWORD *)(v5 + 16));
      free((void *)v5);
    }
    File_DeleteLoadInfo(ptHead);
  }
}

// source: b/1/file.c:1253  [anchor-callee]
void __cdecl File_Remove(char *zFilename)
{
  int v1; // ebp
  int IsValidDevicename; // eax
  int v3; // edi
  char v4; // al
  int v5; // ecx
  char *v6; // ecx
  void (__cdecl *pfRemove)(int, char *); // eax
  int peDeviceID; // [esp+10h] [ebp-4h] BYREF

  v1 = 0;
  do
  {
    v1 = File_SubstituteAlias(&byte_704318, zFilename, v1, false);
    IsValidDevicename = File_IsValidDevicename(&peDeviceID, &byte_704318);
    v3 = peDeviceID;
    if ( !IsValidDevicename )
      v3 = File_eDefaultDevice;
    if ( v3 <= 0 || v3 >= 5 )
    {
      LDebug_Error("Illegal device name in path: \"%s\".", &byte_704318);
LABEL_18:
      abort();
    }
    if ( File_atDevice[v3].isInitialised == false )
    {
      LDebug_Error("Device not present: %s", (char *)(144 * v3 + 7358424));
      goto LABEL_18;
    }
    if ( File_IsValidDevicename(nullptr, &byte_704318) && (v4 = byte_704318, v5 = 0, byte_704318) )
    {
      while ( v4 != 58 )
      {
        v4 = byte_704319[v5++];
        if ( !v4 )
          goto LABEL_11;
      }
      v6 = &byte_704319[v5];
    }
    else
    {
LABEL_11:
      v6 = &byte_704318;
    }
    pfRemove = File_atDevice[v3].pfRemove;
    if ( pfRemove )
      pfRemove(v3, v6);
  }
  while ( v1 );
}

// source: b/1/file.c:1308  [anchor-mhash]
int __cdecl File_NewDevice(char *zDevicename, int (__cdecl *pfNewDevice)(char *))
{
  int result; // eax

  result = pfNewDevice(zDevicename);
  if ( result )
  {
    File_atDevice[result].isInitialised = true;
    if ( !File_eDefaultDevice )
      File_eDefaultDevice = result;
  }
  return result;
}

// source: b/1/file.c:1338  [anchor-hash]
int __cdecl File_DeleteDevice(int eDeviceID)
{
  return ((int (__cdecl *)(int))File_atDevice[eDeviceID].pfDeleteDevice)(eDeviceID);
}

// source: b/1/file.c:1354  [size]
int __cdecl File_SetDeviceNewDeviceCallback(
        int eDeviceID,
        int (__cdecl *pfNewDevice)(char *))
{
  int result; // eax

  result = eDeviceID;
  File_atDevice[result].pfNewDevice = pfNewDevice;
  return result * 144;
}

// source: b/1/file.c:1367  [size]
int __cdecl File_SetDeviceDeleteDeviceCallback(
        int eDeviceID,
        void (__cdecl *pfDeleteDevice)(int))
{
  int result; // eax

  result = eDeviceID;
  File_atDevice[result].pfDeleteDevice = pfDeleteDevice;
  return result * 144;
}

// source: b/1/file.c:1380  [size]
int __cdecl File_SetDeviceNewCallback(
        int eDeviceID,
        struct File_s *(__cdecl *pfNew)(int, char *, int))
{
  int result; // eax

  result = eDeviceID;
  File_atDevice[result].pfNew = pfNew;
  return result * 144;
}

// source: b/1/file.c:1393  [size]
int __cdecl File_SetDeviceDeleteCallback(
        int eDeviceID,
        void (__cdecl *pfDelete)(int, struct File_s *))
{
  int result; // eax

  result = eDeviceID;
  File_atDevice[result].pfDelete = pfDelete;
  return result * 144;
}

// source: b/1/file.c:1406  [size]
int __cdecl File_SetDeviceReadCallback(
        int eDeviceID,
        unsigned int (__cdecl *pfRead)(int, struct File_s *, void *, unsigned int))
{
  int result; // eax

  result = eDeviceID;
  File_atDevice[result].pfRead = pfRead;
  return result * 144;
}

// source: b/1/file.c:1419  [size]
int __cdecl File_SetDeviceWriteCallback(
        int eDeviceID,
        unsigned int (__cdecl *pfWrite)(int, struct File_s *, void *, unsigned int))
{
  int result; // eax

  result = eDeviceID;
  File_atDevice[result].pfWrite = pfWrite;
  return result * 144;
}

// source: b/1/file.c:1432  [size]
int __cdecl File_SetDeviceSeekCallback(
        int eDeviceID,
        int (__cdecl *pfSeek)(int, struct File_s *, int, int))
{
  int result; // eax

  result = eDeviceID;
  File_atDevice[result].pfSeek = pfSeek;
  return result * 144;
}

// source: b/1/file.c:1445  [size]
int __cdecl File_SetDeviceGetPosCallback(
        int eDeviceID,
        int (__cdecl *pfGetPos)(int, struct File_s *))
{
  int result; // eax

  result = eDeviceID;
  File_atDevice[result].pfGetPos = pfGetPos;
  return result * 144;
}

// source: b/1/file.c:1458  [size]
int __cdecl File_SetDeviceGetSizeCallback(
        int eDeviceID,
        unsigned int (__cdecl *pfGetSize)(int, struct File_s *))
{
  int result; // eax

  result = eDeviceID;
  File_atDevice[result].pfGetSize = pfGetSize;
  return result * 144;
}

// source: b/1/file.c:1471  [size]
int __cdecl File_SetDeviceGetErrorCallback(
        int eDeviceID,
        enum FileError_e (__cdecl *pfGetError)(int, struct File_s *))
{
  int result; // eax

  result = eDeviceID;
  File_atDevice[result].pfGetError = pfGetError;
  return result * 144;
}

// source: b/1/file.c:1484  [size]
int __cdecl File_SetDeviceGetStatusCallback(
        int eDeviceID,
        enum FileStatus_e (__cdecl *pfGetStatus)(int, struct File_s *))
{
  int result; // eax

  result = eDeviceID;
  File_atDevice[result].pfGetStatus = pfGetStatus;
  return result * 144;
}

// source: b/1/file.c:1497  [size]
int __cdecl File_SetDeviceGetLineCallback(
        int eDeviceID,
        int (__cdecl *pfGetLine)(int, struct File_s *, void *, unsigned int))
{
  int result; // eax

  result = eDeviceID;
  File_atDevice[result].pfGetLine = pfGetLine;
  return result * 144;
}

// source: b/1/file.c:1510  [size]
int __cdecl File_SetDeviceisEOFCallback(
        int eDeviceID,
        enum bool (__cdecl *pfisEOF)(int, struct File_s *))
{
  int result; // eax

  result = eDeviceID;
  File_atDevice[result].pfisEOF = pfisEOF;
  return result * 144;
}

// source: b/1/file.c:1523  [size]
int __cdecl File_SetDeviceSyncCallback(
        int eDeviceID,
        int (__cdecl *pfSync)(int, struct File_s *, enum FileSyncMode_e))
{
  int result; // eax

  result = eDeviceID;
  File_atDevice[result].pfSync = pfSync;
  return result * 144;
}

// source: b/1/file.c:1536  [size]
int __cdecl File_SetDeviceRemoveCallback(
        int eDeviceID,
        void (__cdecl *pfRemove)(int, char *))
{
  int result; // eax

  result = eDeviceID;
  File_atDevice[result].pfRemove = pfRemove;
  return result * 144;
}

// source: b/1/file.c:1549  [size]
int __cdecl File_SetDeviceLoadCallback(
        int eDeviceID,
        void *(__cdecl *pfLoad)(int, struct File_s *, unsigned int *, struct FileLoaded_s *))
{
  int result; // eax

  result = eDeviceID;
  File_atDevice[result].pfLoad = pfLoad;
  return result * 144;
}

// source: b/1/file.c:1562  [size]
int __cdecl File_SetDeviceDirListCallback(
        int eDeviceID,
        int (__cdecl *pfDirList)(int, char *, void (__cdecl *)(struct FileDirListCallbackContext_s *, void *), void *))
{
  int result; // eax

  result = eDeviceID;
  File_atDevice[result].pfDirList = pfDirList;
  return result * 144;
}

// source: b/1/file.c:1575  [size]
int __cdecl File_SetDeviceFlushCallback(
        int eDeviceID,
        void (__cdecl *pfFlush)(int, struct FileLoaded_s *))
{
  int result; // eax

  result = eDeviceID;
  File_atDevice[result].pfFlush = pfFlush;
  return result * 144;
}

// source: b/1/file.c:1588  [size]
int __cdecl File_SetDeviceGetFileTimeCallback(
        int eDeviceID,
        int (__cdecl *pfGetFileTime)(int, struct FileTime_s *, char *))
{
  int result; // eax

  result = eDeviceID;
  File_atDevice[result].pfGetFileTime = pfGetFileTime;
  return result * 144;
}

// source: b/1/file.c:1601  [size]
int __cdecl File_SetDeviceAsyncLoadCallback(
        int eDeviceID,
        void (__cdecl *pfAsyncLoad)(int, struct File_s *, unsigned int *, struct FileLoaded_s *))
{
  int result; // eax

  result = eDeviceID;
  File_atDevice[result].pfAsyncLoad = pfAsyncLoad;
  return result * 144;
}

// source: b/1/file.c:1614  [size]
int __cdecl File_SetDeviceUpdateAsyncStatusCallback(
        int eDeviceID,
        void (__cdecl *pfUpdateAsyncStatus)(int, struct File_s *))
{
  int result; // eax

  result = eDeviceID;
  File_atDevice[result].pfUpdateAsyncStatus = pfUpdateAsyncStatus;
  return result * 144;
}

// source: b/1/file.c:1627  [size]
int __cdecl File_SetDevicePrintfCallback(
        int eDeviceID,
        int (__cdecl *pfPrintf)(int, struct File_s *, char *, char *))
{
  int result; // eax

  result = eDeviceID;
  File_atDevice[result].pfPrintf = pfPrintf;
  return result * 144;
}

// source: b/1/file.c:1640  [anchor-hash]
char *__cdecl File_GetDeviceName(int eDeviceID)
{
  return (char *)(144 * eDeviceID + 7358424);
}

// source: b/1/file.c:1653  [anchor-mhash]
char *__cdecl File_RemoveDeviceNameFromPath(
        char *zRealPath,
        unsigned int nRealPathSize,
        char *zPath)
{
  char v4; // al
  int v5; // esi

  if ( File_IsValidDevicename(nullptr, zPath) && (v4 = *zPath, v5 = 0, *zPath) )
  {
    while ( v4 != 58 )
    {
      v4 = zPath[++v5];
      if ( !v4 )
        goto LABEL_5;
    }
    if ( zRealPath )
    {
      strncpy(zRealPath, &zPath[v5 + 1], nRealPathSize);
      zRealPath[nRealPathSize - 1] = 0;
    }
    return (char *)&zPath[v5 + 1];
  }
  else
  {
LABEL_5:
    if ( zRealPath )
    {
      strncpy(zRealPath, zPath, nRealPathSize);
      zRealPath[nRealPathSize - 1] = 0;
    }
    return (char *)zPath;
  }
}

// source: b/1/file.c:1690  [anchor-hash]
char *__cdecl File_GetRealFilename(char *zFilename)
{
  char v2; // al
  int v3; // ecx

  if ( !File_IsValidDevicename(nullptr, zFilename) )
    return (char *)zFilename;
  v2 = *zFilename;
  v3 = 0;
  if ( !*zFilename )
    return (char *)zFilename;
  while ( v2 != 58 )
  {
    v2 = zFilename[++v3];
    if ( !v2 )
      return (char *)zFilename;
  }
  return (char *)&zFilename[v3 + 1];
}

// source: b/1/file.c:1703  [anchor-mhash]
char *__cdecl File_GetFilenameExtension(
        char *zExtension,
        unsigned int nExtensionSize,
        char *zFilename)
{
  unsigned int i; // eax
  char *v4; // esi

  for ( i = strlen(zFilename); i; --i )
  {
    if ( zFilename[i] == 46 )
      break;
  }
  v4 = &zFilename[i];
  if ( zExtension )
  {
    strncpy(zExtension, v4, nExtensionSize - 1);
    zExtension[nExtensionSize - 1] = 0;
  }
  return (char *)v4;
}

// source: b/1/file.c:1734  [anchor-mhash]
char *__cdecl File_GetFilenamePath(
        char *zPath,
        unsigned int nPathSize,
        char *zFilename)
{
  char *v3; // ebp
  unsigned int v4; // edi
  int v5; // esi
  char v6; // dl

  v3 = nullptr;
  v4 = 0;
  if ( !nPathSize )
    goto LABEL_10;
  v5 = zPath - zFilename;
  do
  {
    v6 = *zFilename;
    if ( !*zFilename )
      break;
    if ( v6 == 92 || v6 == 47 )
      v3 = &zFilename[v5];
    ++v4;
    (zFilename++)[v5] = v6;
  }
  while ( v4 < nPathSize );
  if ( v3 )
    *v3 = 0;
  else
LABEL_10:
    *zPath = 0;
  return zPath;
}

// source: b/1/file.c:1776  [anchor-mhash]
char *__cdecl File_GetFilenameNoExtension(
        char *zBuffer,
        unsigned int nBufferSize,
        char *zFilename)
{
  char *v3; // eax
  int v4; // edi

  v3 = strrchr(zFilename, 46);
  if ( v3 && (v4 = v3 - zFilename, nBufferSize > v3 - zFilename) )
  {
    strncpy(zBuffer, zFilename, v3 - zFilename);
    zBuffer[v4] = 0;
    return zBuffer;
  }
  else
  {
    strncpy(zBuffer, zFilename, nBufferSize);
    return zBuffer;
  }
}

// source: b/1/file.c:1813  [anchor-mhash]
char *__cdecl File_GetFilenameNoPath(
        char *zBuffer,
        unsigned int nBufferSize,
        char *zFilename)
{
  int i; // eax
  char v4; // cl

  for ( i = strlen(zFilename); i >= 0; --i )
  {
    v4 = zFilename[i];
    if ( v4 == 47 )
      break;
    if ( v4 == 92 )
      break;
    if ( v4 == 58 )
      break;
  }
  if ( !zBuffer )
    return (char *)&zFilename[i + 1];
  strncpy(zBuffer, &zFilename[i + 1], nBufferSize);
  return zBuffer;
}

// source: b/1/file.c:1848  [size]
char *__cdecl File_GetLastSubstitutedFilename()
{
  return File_zLastSubstitutedPath;
}

// source: b/1/file.c:1861  [size]
unsigned int __cdecl File_GetBytesRead()
{
  return File_nBytesRead;
}

// source: b/1/file.c:1874  [size]
void __cdecl File_ClearBytesRead()
{
  File_nBytesRead = 0;
}

// source: b/1/file.c:1887  [anchor-mhash]
int __cdecl File_EnumerateLoadedFiles(
        void (__cdecl *pfCallback)(struct FileLoaded_s *, void *),
        void *pxContext)
{
  struct FileLoaded_s *ptHead; // eax
  struct FileLoaded_s *ptNext; // esi
  int i; // edi

  ptHead = File_tLoadInfoList.ptHead;
  ptNext = File_tLoadInfoList.ptHead->ptNext;
  for ( i = 0; ptNext; ++i )
  {
    pfCallback(ptHead, pxContext);
    ptHead = ptNext;
    ptNext = ptNext->ptNext;
  }
  return i;
}

// source: b/1/file.c:1913  [anchor-hash]
enum bool __cdecl File_Exists(char *zFilename)
{
  struct File_s *v1; // eax

  v1 = File_New(zFilename, "r");
  if ( !v1 )
    return false;
  if ( v1 == &File_tDummyAsyncFile )
    File_tDummyAsyncFile.isAsync = false;
  else
    File_atDevice[v1->eDeviceID].pfDelete(v1->eDeviceID, v1);
  return true;
}

// source: b/1/file.c:1988  [anchor-mhash]
enum bool __cdecl File_IsFilenameValid(char *zFilename)
{
  int v1; // esi
  bool v2; // zf
  int v3; // eax
  int peDeviceID; // [esp+8h] [ebp-4h] BYREF

  v1 = 0;
  while ( 1 )
  {
    v1 = File_SubstituteAlias(byte_704210, zFilename, v1, false);
    v2 = File_IsValidDevicename(&peDeviceID, byte_704210) == 0;
    v3 = peDeviceID;
    if ( v2 )
      v3 = File_eDefaultDevice;
    if ( v3 <= 0 || v3 >= 5 )
      return false;
    if ( File_atDevice[v3].isInitialised )
      break;
    if ( !v1 )
      return false;
  }
  return true;
}

// source: b/1/file.c:2030  [size]
int __cdecl File_SetDefaultDeviceID(int eDeviceID)
{
  File_eDefaultDevice = eDeviceID;
  return eDeviceID;
}

// source: b/1/file.c:2045  [size]
int __cdecl File_GetDefaultDeviceID()
{
  return File_eDefaultDevice;
}

// source: b/1/file.c:2058  [anchor-callee]
int __cdecl File_printf(struct File_s *ptFile, char *zFormat)
{
  int (__cdecl *pfPrintf)(int, struct File_s *, char *, char *); // edx
  int result; // eax
  char *zFormata; // [esp+8h] [ebp+8h] BYREF ARGSLOT

  pfPrintf = File_atDevice[ptFile->eDeviceID].pfPrintf;
  result = 0;
  if ( pfPrintf )
    return pfPrintf(ptFile->eDeviceID, ptFile, zFormat, (char *)&zFormata);
  return result;
}
