/* b/1/pc/pc_devstd.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: b/1/pc/pc_devstd.c:66  [size]
int __cdecl devSTD_CheckAndCreateDir(char *zDrive, char *zDir)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct _SECURITY_ATTRIBUTES tSecurityAttributes; };
    struct { char igi2_o1[12]; char zPath[260]; };
    struct { char igi2_o2[272]; char zTempPath[260]; };
    struct { char igi2_o3[532]; struct _WIN32_FIND_DATAA tFindData; };
    char igi2_extent[12];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  char *v2; // eax
  char v3; // cl
  unsigned int v4; // eax
  char *v5; // edi
  int v7; // eax
  char v8; // al
  _WORD *v9; // edi
  char v10; // al
  _DWORD *v11; // edi
  char v12; // al
  HANDLE FirstFileA; // edi
  unsigned int v14; // eax
  unsigned int v16; // ecx
  char v17; // al
  char *v18; // eax
  char v19; // cl
  unsigned int v20; // eax
  char *v21; // edi

  v2 = (char *)zDrive;
  do
  {
    v3 = *v2;
    igi2_frame.zPath[v2 - (char *)zDrive] = *v2;
    ++v2;
  }
  while ( v3 );
  v4 = strlen(zDir) + 1;
  v5 = (char *)&igi2_frame.tSecurityAttributes.bInheritHandle + 3;
  while ( *++v5 )
    ;
  qmemcpy(v5, zDir, v4);
  v7 = &igi2_frame.zPath[strlen(igi2_frame.zPath) + 1] - &igi2_frame.zPath[1];
  if ( v7 > 1 )
  {
    v8 = *((_BYTE *)&igi2_frame.tSecurityAttributes.bInheritHandle + v7 + 3);
    if ( v8 != 47 && v8 != 92 )
    {
      v9 = (_WORD *)((char *)&igi2_frame.tSecurityAttributes.bInheritHandle + 3);
      do
      {
        v10 = *((_BYTE *)v9 + 1);
        v9 = (_WORD *)((char *)v9 + 1);
      }
      while ( v10 );
      *v9 = *(_WORD *)&g_zFileName.atPictureResources[13].zResourceFilename[60];
    }
  }
  v11 = (BOOL *)((char *)&igi2_frame.tSecurityAttributes.bInheritHandle + 3);
  do
  {
    v12 = *((_BYTE *)v11 + 1);
    v11 = (_DWORD *)((char *)v11 + 1);
  }
  while ( v12 );
  *v11 = 2764330;
  FirstFileA = FindFirstFileA(igi2_frame.zPath, &igi2_frame.tFindData);
  if ( FirstFileA != (HANDLE)-1 )
    goto LABEL_28;
  v14 = strlen(zDir);
  if ( (int)(v14 - 1) < 0 )
    return 0;
  v16 = v14 - 2;
  if ( (int)(v14 - 2) > 0 )
  {
    while ( 1 )
    {
      v17 = zDir[v16];
      if ( v17 == 47 || v17 == 92 )
        break;
      if ( (int)--v16 <= 0 )
        goto LABEL_22;
    }
    ++v16;
  }
LABEL_22:
  strcpy(igi2_frame.zTempPath, zDir);
  igi2_frame.zTempPath[v16] = 0;
  if ( devSTD_CheckAndCreateDir(zDrive, igi2_frame.zTempPath) )
  {
    v18 = (char *)zDrive;
    do
    {
      v19 = *v18;
      igi2_frame.zPath[v18 - (char *)zDrive] = *v18;
      ++v18;
    }
    while ( v19 );
    v20 = strlen(zDir) + 1;
    v21 = (char *)&igi2_frame.tSecurityAttributes.bInheritHandle + 3;
    while ( *++v21 )
      ;
    qmemcpy(v21, zDir, v20);
    igi2_frame.tSecurityAttributes.lpSecurityDescriptor = nullptr;
    igi2_frame.tSecurityAttributes.bInheritHandle = 0;
    igi2_frame.tSecurityAttributes.nLength = 12;
    return CreateDirectoryA(igi2_frame.zPath, &igi2_frame.tSecurityAttributes);
  }
  else
  {
LABEL_28:
    FindClose(FirstFileA);
    return 1;
  }
}

// source: b/1/pc/pc_devstd.c:141  [anchor-mhash]
void __cdecl devSTD_CreateDir(char *zFilename)
{
  #pragma pack(push, 1)
  union
  {
    struct { char zDrive[4]; };
    struct { char igi2_o1[4]; char zDir[256]; };
    char igi2_extent[260];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)

  splitpath(zFilename, igi2_frame.zDrive, igi2_frame.zDir, nullptr, nullptr);
  devSTD_CheckAndCreateDir(igi2_frame.zDrive, igi2_frame.zDir);
}

// source: b/1/pc/pc_devstd.c:159  [anchor-caller]
void __cdecl devSTD_Remove(int eDevice, char *zFilename)
{
  remove(zFilename);
}

// source: b/1/pc/pc_devstd.c:180  [size]
int __cdecl devSTD_DirList(
        int eDeviceID,
        char *zPath,
        void (__cdecl *pfCallback)(struct FileDirListCallbackContext_s *, void *),
        void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { int nCount; };
    struct { char igi2_o1[4]; char *zAppend; };
    struct { char igi2_o2[8]; HANDLE hSearch; };
    struct { char igi2_o3[12]; struct FileDirListCallbackContext_s tContext; };
    struct { char igi2_o4[24]; char *v41; };
    struct { char igi2_o5[28]; char *v42; };
    struct { char igi2_o6[32]; struct _WIN32_FIND_DATAA tFindData; };
    struct { char igi2_o7[352]; char zFilename[260]; };
    struct { char igi2_o8[612]; char zSearchPath[260]; };
    char igi2_extent[872];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  char *v4; // edi
  char *v6; // edi
  char *zDevicename; // eax
  char *v9; // edx
  char v10; // cl
  unsigned int v11; // eax
  CHAR *v12; // edi
  unsigned int v14; // eax
  CHAR *v15; // edi
  unsigned int v17; // eax
  CHAR *v18; // edi
  DWORD nFileSizeLow; // edx
  char *v21; // eax
  char v22; // cl
  unsigned int v23; // eax
  CHAR *v24; // edi
  unsigned int v26; // eax
  CHAR *v27; // edi
  unsigned int v29; // eax
  CHAR *v30; // edi
  CHAR *v32; // edi
  CHAR *v33; // esi
  char v34; // cl
  DWORD v35; // eax

  igi2_frame.nCount = 0;
  strcpy(igi2_frame.zSearchPath, zPath);
  if ( zPath[strlen(zPath) - 1] == 47 )
  {
    igi2_frame.zAppend = (char *)&g_zInitialValue;
  }
  else
  {
    v4 = &igi2_frame.zFilename[259];
    while ( *++v4 )
      ;
    *(_WORD *)v4 = *(_WORD *)&g_zFileName.atPictureResources[13].zResourceFilename[60];
    igi2_frame.zAppend = &g_zFileName.atPictureResources[13].zResourceFilename[60];
  }
  v6 = &igi2_frame.zFilename[259];
  while ( *++v6 )
    ;
  *(_DWORD *)v6 = 2764330;
  igi2_frame.hSearch = FindFirstFileA(igi2_frame.zSearchPath, &igi2_frame.tFindData);
  igi2_frame.tContext.zFilename = igi2_frame.zFilename;
  if ( igi2_frame.hSearch == (HANDLE)-1 )
    return 0;
  zDevicename = File_atDevice[eDeviceID].zDevicename;
  v9 = (char *)(igi2_frame.zFilename - zDevicename);
  igi2_frame.v42 = zDevicename;
  igi2_frame.v41 = (char *)(igi2_frame.zFilename - zDevicename);
  do
  {
    v10 = *zDevicename;
    zDevicename[(_DWORD)v9] = *zDevicename;
    ++zDevicename;
  }
  while ( v10 );
  v11 = strlen(zPath) + 1;
  v12 = &igi2_frame.tFindData.cAlternateFileName[15];
  while ( *++v12 )
    ;
  qmemcpy(v12, zPath, v11);
  v14 = strlen(igi2_frame.zAppend) + 1;
  v15 = &igi2_frame.tFindData.cAlternateFileName[15];
  while ( *++v15 )
    ;
  qmemcpy(v15, igi2_frame.zAppend, v14);
  v17 = strlen(igi2_frame.tFindData.cFileName) + 1;
  v18 = &igi2_frame.tFindData.cAlternateFileName[15];
  while ( *++v18 )
    ;
  nFileSizeLow = igi2_frame.tFindData.nFileSizeLow;
  qmemcpy(v18, igi2_frame.tFindData.cFileName, v17);
  igi2_frame.tContext.isDirectory = (igi2_frame.tFindData.dwFileAttributes >> 4) & 1;
  igi2_frame.tContext.nSize = nFileSizeLow;
  if ( igi2_frame.tFindData.cFileName[0] != 46 )
  {
    if ( pfCallback )
      pfCallback(&igi2_frame.tContext, pxContext);
    igi2_frame.nCount = 1;
  }
  while ( FindNextFileA(igi2_frame.hSearch, &igi2_frame.tFindData) )
  {
    v21 = igi2_frame.v42;
    do
    {
      v22 = *v21;
      v21[(_DWORD)igi2_frame.v41] = *v21;
      ++v21;
    }
    while ( v22 );
    v23 = strlen(zPath) + 1;
    v24 = &igi2_frame.tFindData.cAlternateFileName[15];
    while ( *++v24 )
      ;
    qmemcpy(v24, zPath, v23);
    v26 = strlen(igi2_frame.zAppend) + 1;
    v27 = &igi2_frame.tFindData.cAlternateFileName[15];
    while ( *++v27 )
      ;
    qmemcpy(v27, igi2_frame.zAppend, v26);
    v29 = strlen(igi2_frame.tFindData.cFileName) + 1;
    v30 = &igi2_frame.tFindData.cAlternateFileName[15];
    while ( *++v30 )
      ;
    qmemcpy(v30, igi2_frame.tFindData.cFileName, 4 * (v29 >> 2));
    v33 = &igi2_frame.tFindData.cFileName[4 * (v29 >> 2)];
    v32 = &v30[4 * (v29 >> 2)];
    v34 = v29;
    v35 = igi2_frame.tFindData.nFileSizeLow;
    qmemcpy(v32, v33, v34 & 3);
    igi2_frame.tContext.nSize = v35;
    igi2_frame.tContext.isDirectory = (igi2_frame.tFindData.dwFileAttributes >> 4) & 1;
    if ( igi2_frame.tFindData.cFileName[0] != 46 )
    {
      if ( pfCallback )
        pfCallback(&igi2_frame.tContext, pxContext);
      ++igi2_frame.nCount;
    }
  }
  FindClose(igi2_frame.hSearch);
  return igi2_frame.nCount;
}

// source: b/1/pc/pc_devstd.c:256  [anchor-caller]
struct File_s *__cdecl devSTD_New(int eDeviceID, char *zFilename, int bOpenMode)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct devSTDfile *ptSTDfile; };
    struct { char igi2_o1[4]; char Dir[256]; };
    char igi2_extent[260];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v3; // esi
  int *p_isUsed; // eax
  struct devSTDfile *v5; // esi
  char *v7; // edi
  FILE *v8; // eax

  v3 = 0;
  p_isUsed = &devSTD_atFile[0].isUsed;
  while ( *p_isUsed )
  {
    p_isUsed += 76;
    ++v3;
    if ( (int)p_isUsed >= 129476084 )
    {
      v5 = igi2_frame.ptSTDfile;
      goto LABEL_6;
    }
  }
  v5 = (struct devSTDfile *)(304 * v3 + 129470920);
LABEL_6:
  if ( !v5 )
    return nullptr;
  if ( bOpenMode == 1 )
  {
    v7 = (char *)&unk_68700C;
  }
  else
  {
    if ( bOpenMode == 2 )
    {
      v7 = "wb";
    }
    else
    {
      if ( bOpenMode != 3 )
      {
        LDebug_Error("Illegal openmode (%X) for file %s.", bOpenMode, zFilename);
        abort();
      }
      v7 = dword_687008;
    }
    splitpath(zFilename, (char *)&igi2_frame.ptSTDfile, igi2_frame.Dir, nullptr, nullptr);
    devSTD_CheckAndCreateDir((char *)&igi2_frame.ptSTDfile, igi2_frame.Dir);
  }
  v8 = fopen(zFilename, v7);
  if ( !v8 )
    return nullptr;
  v5->bOpenMode = bOpenMode;
  v5->ptFILE = v8;
  v5->isUsed = 1;
  v5->eError = FILE_ERROR_NONE;
  v5->eStatus = FILE_STATUS_READY;
  return &v5->tFile;
}

// source: b/1/pc/pc_devstd.c:326  [size]
void __cdecl devSTD_Delete(int eDeviceID, struct File_s *ptFile)
{
  ptFile[1].nAsyncBytesRead = 0;
  fclose((FILE *)ptFile[1].eDeviceID);
}

// source: b/1/pc/pc_devstd.c:346  [anchor-mhash]
unsigned int __cdecl devSTD_Read(int eDeviceID, struct File_s *ptFile, void *pxBuffer, unsigned int nBytes)
{
  unsigned int result; // eax
  int i; // ebx

  result = 0;
  for ( i = 0; i < 10; ++i )
  {
    result = fread(pxBuffer, nBytes, 1u, (FILE *)ptFile[1].eDeviceID);
    if ( !result && (feof((FILE *)ptFile[1].eDeviceID)) != 0 )
      return 0;
    if ( result )
      return result;
  }
  return result;
}

// source: b/1/pc/pc_devstd.c:385  [anchor-mhash]
unsigned int __cdecl devSTD_Write(int eDeviceID, struct File_s *ptFile, void *pxBuffer, unsigned int nBytes)
{
  return fwrite(pxBuffer, nBytes, 1u, (FILE *)ptFile[1].eDeviceID);
}

// source: b/1/pc/pc_devstd.c:403  [anchor-strings]
int __cdecl devSTD_Seek(int eDeviceID, struct File_s *ptFile, int nOffset, int eOrigin)
{
  int v5; // [esp-4h] [ebp-4h]

  if ( eOrigin )
  {
    if ( eOrigin == 1 )
    {
      v5 = 1;
    }
    else
    {
      if ( eOrigin != 2 )
      {
        LDebug_Error("Unkown seek origin");
        abort();
      }
      v5 = 2;
    }
  }
  else
  {
    v5 = 0;
  }
  fseek((FILE *)ptFile[1].eDeviceID, nOffset, v5);
  return 0;
}

// source: b/1/pc/pc_devstd.c:441  [anchor-caller]
unsigned int __cdecl devSTD_GetSize(int eDeviceID, struct File_s *ptFile)
{
  FILE *v2; // esi
  int v3; // edi
  unsigned int v4; // ebx

  v2 = (FILE *)ptFile[1].eDeviceID;
  v3 = ftell(v2);
  fseek(v2, 0, 2);
  v4 = ftell(v2);
  fseek(v2, v3, 0);
  return v4;
}

// source: b/1/pc/pc_devstd.c:471  [anchor-caller]
int __cdecl devSTD_GetPos(int eDeviceID, struct File_s *ptFile)
{
  return ftell((FILE *)ptFile[1].eDeviceID);
}

// source: b/1/pc/pc_devstd.c:487  [size]
enum bool __cdecl devSTD_isEOF(int eDeviceID, struct File_s *ptFile)
{
  return feof((FILE *)ptFile[1].eDeviceID);
}

// source: b/1/pc/pc_devstd.c:503  [size]
enum FileStatus_e __cdecl devSTD_GetStatus(int eDeviceID, struct File_s *ptFile)
{
  return ptFile[1].isAsync;
}

// source: b/1/pc/pc_devstd.c:519  [size]
enum FileError_e __cdecl devSTD_GetError(int eDeviceID, struct File_s *ptFile)
{
  return ptFile[1].isAsyncReadComplete;
}

// source: b/1/pc/pc_devstd.c:535  [anchor-mhash]
int __cdecl devSTD_Sync(int eDeviceID, struct File_s *ptFile, enum FileSyncMode_e eSyncMode)
{
  if ( eSyncMode == FILE_SYNC_FLUSH )
    return fflush((FILE *)ptFile[1].eDeviceID);
  else
    return 0;
}

// source: b/1/pc/pc_devstd.c:565  [anchor-mhash]
int __cdecl devSTD_printf(int eDeviceID, struct File_s *ptFile, char *zFormat, char *arg)
{
  return vfprintf((FILE *)ptFile[1].eDeviceID, (int)zFormat, (int)arg);
}

// source: b/1/pc/pc_devstd.c:587  [size]
int __cdecl devSTD_GetFileTime(int eDeviceID, struct FileTime_s *ptFileTime, char *zFilename)
{
  HANDLE FileA; // eax
  void *v4; // esi

  ptFileTime->tFileTime.dwLowDateTime = 0;
  ptFileTime->tFileTime.dwHighDateTime = 0;
  FileA = CreateFileA(zFilename, 0, 0, nullptr, 3u, 0x80u, nullptr);
  v4 = FileA;
  if ( FileA == (HANDLE)-1 )
    return -1;
  GetFileTime(FileA, nullptr, nullptr, &ptFileTime->tFileTime);
  CloseHandle(v4);
  return 0;
}

// source: b/1/pc/pc_devstd.c:617  [anchor-callee]
int __cdecl devSTD_NewDevice(char *zDevicename)
{
  int result; // eax
  char *v2; // edx
  int v3; // ecx
  char v4; // cl
  int *p_isUsed; // ecx

  result = File_eFreeDeviceID;
  v2 = (char *)zDevicename;
  File_atDevice[File_eFreeDeviceID].eDeviceID = File_eFreeDeviceID;
  File_eFreeDeviceID = result + 1;
  v3 = result;
  File_atDevice[v3].pfNewDevice = devSTD_NewDevice;
  File_atDevice[v3].pfDeleteDevice = (void (__cdecl *)(int))devSTD_DeleteDevice;
  File_atDevice[v3].pfNew = devSTD_New;
  File_atDevice[v3].pfDelete = devSTD_Delete;
  File_atDevice[v3].pfRead = devSTD_Read;
  File_atDevice[v3].pfWrite = devSTD_Write;
  File_atDevice[v3].pfSeek = devSTD_Seek;
  File_atDevice[v3].pfGetPos = devSTD_GetPos;
  File_atDevice[v3].pfGetSize = devSTD_GetSize;
  File_atDevice[v3].pfisEOF = (enum bool (__cdecl *)(int, struct File_s *))devSTD_isEOF;
  File_atDevice[v3].pfGetStatus = (enum FileStatus_e (__cdecl *)(int, struct File_s *))devSTD_GetStatus;
  File_atDevice[v3].pfGetError = (enum FileError_e (__cdecl *)(int, struct File_s *))devSTD_GetError;
  File_atDevice[v3].pfSync = devSTD_Sync;
  File_atDevice[v3].pfDirList = devSTD_DirList;
  File_atDevice[v3].pfGetFileTime = devSTD_GetFileTime;
  File_atDevice[v3].pfRemove = devSTD_Remove;
  File_atDevice[v3].pfPrintf = devSTD_printf;
  do
  {
    v4 = *v2;
    File_atDevice[0].zDevicename[144 * result - (_DWORD)zDevicename + (_DWORD)v2] = *v2;
    ++v2;
  }
  while ( v4 );
  p_isUsed = &devSTD_atFile[0].isUsed;
  do
  {
    *p_isUsed = 0;
    p_isUsed += 76;
  }
  while ( (int)p_isUsed < 129476084 );
  return result;
}

// source: b/1/pc/pc_devstd.c:667  [size]
void __cdecl devSTD_DeleteDevice(int eDeviceID)
{
  ;
}
