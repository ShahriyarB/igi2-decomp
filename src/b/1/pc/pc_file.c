/* b/1/pc/pc_file.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: b/1/pc/pc_file.c:29  [anchor-hash]
void __cdecl File_RegisterDevices()
{
  int v0; // eax
  int v1; // eax
  bool v2; // zf
  int v3; // eax

  v0 = devSTD_NewDevice((char *)&g_zFileName.atPictureResources[13].ptPicture);
  if ( v0 )
    File_atDevice[v0].isInitialised = true;
  File_eDefaultDevice = v0;
  v1 = devNET_NewDevice("REMOTE:");
  if ( v1 )
  {
    v2 = File_eDefaultDevice == 0;
    File_atDevice[v1].isInitialised = true;
    if ( v2 )
      File_eDefaultDevice = v1;
  }
  v3 = DevMem_NewDevice("RAM:");
  if ( v3 )
  {
    File_atDevice[v3].isInitialised = true;
    if ( !File_eDefaultDevice )
      File_eDefaultDevice = v3;
  }
}

// source: b/1/pc/pc_file.c:59  [size]
int __cdecl File_CompareFileTime(struct FileTime_s *ptFileTime1, struct FileTime_s *ptFileTime2)
{
  return CompareFileTime(&ptFileTime1->tFileTime, &ptFileTime2->tFileTime);
}
