/* b/1/pc/pc_devnet.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: b/1/pc/pc_devnet.c:71  [anchor-mhash]
struct File_s *__cdecl devNET_New(int eDeviceID, char *zFilename, int bOpenMode)
{
  int v3; // esi
  int *p_isUsed; // eax
  int v5; // esi
  HINTERNET v6; // eax
  struct devNETfile *ptSTDfile; // [esp+4h] [ebp-4h]

  v3 = 0;
  p_isUsed = &devNET_atFile[0].isUsed;
  while ( *p_isUsed )
  {
    p_isUsed += 77;
    ++v3;
    if ( (int)p_isUsed >= 129471224 )
    {
      v5 = (int)ptSTDfile;
      goto LABEL_6;
    }
  }
  v5 = 308 * v3 + 129465992;
LABEL_6:
  if ( !v5 )
    return nullptr;
  v6 = InternetOpenUrlA(devNET_hInternetConnection, zFilename, nullptr, 0, 0x40000000u, 0);
  *(_DWORD *)(v5 + 284) = v6;
  if ( !v6 )
    return nullptr;
  *(_DWORD *)(v5 + 296) = bOpenMode;
  *(_DWORD *)(v5 + 304) = 1;
  *(_DWORD *)(v5 + 288) = 0;
  *(_DWORD *)(v5 + 292) = 0;
  *(_DWORD *)(v5 + 300) = 0;
  return (struct File_s *)v5;
}

// source: b/1/pc/pc_devnet.c:120  [anchor-mhash]
void __cdecl devNET_Delete(int eDeviceID, struct File_s *ptFile)
{
  InternetCloseHandle((HINTERNET)ptFile[1].eDeviceID);
  ptFile[1].pxAsyncBuffer = nullptr;
}

// source: b/1/pc/pc_devnet.c:138  [anchor-mhash]
unsigned int __cdecl devNET_Read(int eDeviceID, struct File_s *ptFile, void *pxBuffer, unsigned int nBytes)
{
  unsigned int v4; // edi
  unsigned int result; // eax

  v4 = nBytes;
  InternetReadFile((HINTERNET)ptFile[1].eDeviceID, pxBuffer, nBytes, &nBytes);
  result = nBytes;
  if ( nBytes < v4 )
    ptFile[1].isAsyncReadComplete = true;
  ptFile[1].nAsyncBytesRead += result;
  return result;
}

// source: b/1/pc/pc_devnet.c:165  [anchor-strings]
__declspec(noreturn) void devNET_Write()
{
  LDebug_Error("UNABLE TO WRITE TO FILE");
  abort();
}

// source: b/1/pc/pc_devnet.c:179  [anchor-mhash]
int __cdecl devNET_Seek(int eDeviceID, struct File_s *ptFile, int nOffset, int eOrigin)
{
  if ( eOrigin )
  {
    if ( eOrigin == 1 )
    {
      ptFile[1].nAsyncBytesRead = InternetSetFilePointer((HINTERNET)ptFile[1].eDeviceID, nOffset, nullptr, 1u, 0);
      return 0;
    }
    if ( eOrigin == 2 )
    {
      ptFile[1].nAsyncBytesRead = InternetSetFilePointer((HINTERNET)ptFile[1].eDeviceID, nOffset, nullptr, 2u, 0);
      return 0;
    }
  }
  else
  {
    ptFile[1].nAsyncBytesRead = InternetSetFilePointer((HINTERNET)ptFile[1].eDeviceID, nOffset, nullptr, 0, 0);
  }
  return 0;
}

// source: b/1/pc/pc_devnet.c:209  [anchor-mhash]
int __cdecl devNET_GetSize(int eDeviceID, struct File_s *ptFile)
{
  LONG nAsyncBytesRead; // ebx
  DWORD v3; // edi
  void *v5; // [esp-14h] [ebp-24h]

  nAsyncBytesRead = ptFile[1].nAsyncBytesRead;
  v3 = InternetSetFilePointer((HINTERNET)ptFile[1].eDeviceID, 0, nullptr, 2u, 0);
  v5 = (void *)ptFile[1].eDeviceID;
  ptFile[1].nAsyncBytesRead = v3;
  ptFile[1].nAsyncBytesRead = InternetSetFilePointer(v5, nAsyncBytesRead, nullptr, 0, 0);
  return v3;
}

// source: b/1/pc/pc_devnet.c:237  [size]
int __cdecl devNET_GetPos(int eDeviceID, struct File_s *ptFile)
{
  return ptFile[1].nAsyncBytesRead;
}

// source: b/1/pc/pc_devnet.c:253  [anchor-mhash]
enum bool __cdecl devNET_isEOF(int eDeviceID, struct File_s *ptFile)
{
  signed int nAsyncBytesRead; // esi

  nAsyncBytesRead = ptFile[1].nAsyncBytesRead;
  return nAsyncBytesRead >= devNET_GetSize(eDeviceID, ptFile);
}

// source: b/1/pc/pc_devnet.c:269  [size]
enum FileStatus_e __cdecl devNET_GetStatus(int eDeviceID, struct File_s *ptFile)
{
  return ptFile[1].isAsync;
}

// source: b/1/pc/pc_devnet.c:285  [size]
enum FileError_e __cdecl devNET_GetError(int eDeviceID, struct File_s *ptFile)
{
  return ptFile[1].isAsyncReadComplete;
}

// source: b/1/pc/pc_devnet.c:301  [size]
int __cdecl devNET_Sync(int eDeviceID, struct File_s *ptFile, enum FileSyncMode_e eSyncMode)
{
  return 0;
}

// source: b/1/pc/pc_devnet.c:329  [anchor-strings]
int __cdecl devNET_NewDevice(char *zDevicename)
{
  int v1; // eax
  int v2; // esi
  char *v4; // ecx
  int v5; // eax
  char v6; // al
  int *p_isUsed; // eax

  v1 = File_eFreeDeviceID;
  File_atDevice[File_eFreeDeviceID].eDeviceID = File_eFreeDeviceID;
  File_eFreeDeviceID = v1 + 1;
  v2 = v1;
  devNET_hInternetConnection = InternetOpenA("CONNECTION NAME", 0, nullptr, nullptr, 0);
  if ( !devNET_hInternetConnection )
    return -1;
  v4 = (char *)zDevicename;
  v5 = v2;
  File_atDevice[v5].pfNewDevice = devNET_NewDevice;
  File_atDevice[v5].pfDeleteDevice = devNET_DeleteDevice;
  File_atDevice[v5].pfNew = devNET_New;
  File_atDevice[v5].pfDelete = devNET_Delete;
  File_atDevice[v5].pfRead = devNET_Read;
  File_atDevice[v5].pfWrite = (unsigned int (__cdecl *)(int, struct File_s *, void *, unsigned int))devNET_Write;
  File_atDevice[v5].pfSeek = devNET_Seek;
  File_atDevice[v5].pfGetPos = (int (__cdecl *)(int, struct File_s *))devNET_GetPos;
  File_atDevice[v5].pfGetSize = (unsigned int (__cdecl *)(int, struct File_s *))devNET_GetSize;
  File_atDevice[v5].pfisEOF = devNET_isEOF;
  File_atDevice[v5].pfGetStatus = (enum FileStatus_e (__cdecl *)(int, struct File_s *))devNET_GetStatus;
  File_atDevice[v5].pfGetError = (enum FileError_e (__cdecl *)(int, struct File_s *))devNET_GetError;
  File_atDevice[v5].pfSync = (int (__cdecl *)(int, struct File_s *, enum FileSyncMode_e))devNET_Sync;
  do
  {
    v6 = *v4;
    File_atDevice[0].zDevicename[144 * v2 - (_DWORD)zDevicename + (_DWORD)v4] = *v4;
    ++v4;
  }
  while ( v6 );
  p_isUsed = &devNET_atFile[0].isUsed;
  do
  {
    *p_isUsed = 0;
    p_isUsed += 77;
  }
  while ( (int)p_isUsed < 129471224 );
  return v2;
}

// source: b/1/pc/pc_devnet.c:387  [anchor-hash]
void __cdecl devNET_DeleteDevice(int eDeviceID)
{
  int *p_isUsed; // esi

  if ( devNET_hInternetConnection )
  {
    p_isUsed = &devNET_atFile[0].isUsed;
    do
    {
      if ( *p_isUsed )
      {
        InternetCloseHandle((HINTERNET)*(p_isUsed - 5));
        *p_isUsed = 0;
      }
      p_isUsed += 77;
    }
    while ( (int)p_isUsed < 129471224 );
    InternetCloseHandle(devNET_hInternetConnection);
  }
}
