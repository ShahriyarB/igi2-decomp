/* f/1/soundsys.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: f/1/soundsys.c:198  [size]
struct PlayingSound_s *__cdecl SoundSys_LinkIn(
        struct PlayingSound_s *ptLink,
        struct PlayingSound_s **pptFirst)
{
  ptLink->ptNext = *pptFirst;
  ptLink->ptPrev = nullptr;
  if ( *pptFirst )
    (*pptFirst)->ptPrev = ptLink;
  *pptFirst = ptLink;
  return ptLink;
}

// source: f/1/soundsys.c:224  [size]
struct PlayingSound_s *__cdecl SoundSys_LinkOut(
        struct PlayingSound_s *ptLink,
        struct PlayingSound_s **pptFirst)
{
  struct PlayingSound_s *ptNext; // ecx

  ptNext = ptLink->ptNext;
  if ( ptNext )
    ptNext->ptPrev = ptLink->ptPrev;
  if ( ptLink->ptPrev )
    ptLink->ptPrev->ptNext = ptLink->ptNext;
  if ( *pptFirst == ptLink )
  {
    ptLink = ptLink->ptNext;
    *pptFirst = ptLink;
  }
  return ptLink;
}

// source: f/1/soundsys.c:292  [size]
char *__cdecl SoundSys_RegisterLipsync(char *pzFilename, int nSize)
{
  #pragma pack(push, 1)
  union
  {
    struct { char zFilename[4]; };
    struct { char igi2_o1[4]; char zNameNoExt[256]; };
    struct { char igi2_o2[260]; char zName[256]; };
    char igi2_extent[516];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  void *v3; // eax
  unsigned int v4; // edi
  void *v5; // esi
  _DWORD *v6; // ebp
  int v7; // eax
  char *v8; // eax
  int v9; // esi
  struct QHashTable_s *v10; // esi
  unsigned int v11; // eax

  v3 = Resource_Load(pzFilename, (unsigned int *)&nSize);
  v4 = nSize;
  v5 = v3;
  v6 = Mem_AllocFn(nSize + 4, 4);
  *v6 = v4 >> 2;
  qmemcpy(v6 + 1, v5, v4);
  if ( Resource_IsLoadedInternal(pzFilename, (struct Resource_s **)igi2_frame.zFilename) )
  {
    v7 = *(_DWORD *)(*(_DWORD *)igi2_frame.zFilename + 36);
    if ( v7 != 3 && v7 != 1 )
      Resource_Remove(*(struct Resource_s **)igi2_frame.zFilename);
  }
  File_GetFilenameNoPath(igi2_frame.zName, 0x100u, pzFilename);
  v8 = strrchr(igi2_frame.zName, 46);
  if ( v8 && (v9 = v8 - igi2_frame.zName, (unsigned int)(v8 - igi2_frame.zName) < 0x100) )
  {
    strncpy(igi2_frame.zNameNoExt, igi2_frame.zName, v8 - igi2_frame.zName);
    igi2_frame.zNameNoExt[v9] = 0;
  }
  else
  {
    strncpy(igi2_frame.zNameNoExt, igi2_frame.zName, 0x100u);
  }
  String_UpperInPlace(igi2_frame.zNameNoExt);
  v10 = SoundSys_ptLipsyncHashTable;
  v11 = SoundSys_ptLipsyncHashTable->tPrivate.pfHashFunction(
          SoundSys_ptLipsyncHashTable->tPrivate.nHashTableSize,
          igi2_frame.zNameNoExt);
  return ((char * (__cdecl *)(struct QHashTable_s *, unsigned int, const void *, const void *))SoundSys_ptLipsyncHashTable->tPrivate.pfCreateElement)(v10, v11, (const void *)(igi2_frame.zNameNoExt), (const void *)(v6));
}

// source: f/1/soundsys.c:326  [anchor-mhash]
void __cdecl SoundSys_RemoveLipsync(char *pzFilename, int nSize)
{
  #pragma pack(push, 1)
  union
  {
    struct { char zNameNoExt[256]; };
    struct { char igi2_o1[256]; char zName[256]; };
    char igi2_extent[512];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  char *v2; // eax
  int v3; // esi
  struct QHashTable_s *v4; // esi
  unsigned int v5; // eax
  int v6; // eax
  int v7; // esi
  struct QHashTable_s *v8; // esi
  unsigned int v9; // eax

  File_GetFilenameNoPath(igi2_frame.zName, 0x100u, pzFilename);
  v2 = strrchr(igi2_frame.zName, 46);
  if ( v2 && (v3 = v2 - igi2_frame.zName, (unsigned int)(v2 - igi2_frame.zName) < 0x100) )
  {
    strncpy(igi2_frame.zNameNoExt, igi2_frame.zName, v2 - igi2_frame.zName);
    igi2_frame.zNameNoExt[v3] = 0;
  }
  else
  {
    strncpy(igi2_frame.zNameNoExt, igi2_frame.zName, 0x100u);
  }
  String_UpperInPlace(igi2_frame.zNameNoExt);
  v4 = SoundSys_ptLipsyncHashTable;
  v5 = SoundSys_ptLipsyncHashTable->tPrivate.pfHashFunction(
         SoundSys_ptLipsyncHashTable->tPrivate.nHashTableSize,
         igi2_frame.zNameNoExt);
  v6 = ((int  (__cdecl *)(struct QHashTable_s *, unsigned int, const void *))SoundSys_ptLipsyncHashTable->tPrivate.pfFindElement)(v4, v5, (const void *)(igi2_frame.zNameNoExt));
  if ( v6 )
  {
    v7 = *(_DWORD *)((v6 - 4) & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v7);
    memset(*(void **)(v7 + 8), 0xCDu, *(_DWORD *)(v7 + 16));
    free((void *)v7);
  }
  v8 = SoundSys_ptLipsyncHashTable;
  v9 = SoundSys_ptLipsyncHashTable->tPrivate.pfHashFunction(
         SoundSys_ptLipsyncHashTable->tPrivate.nHashTableSize,
         igi2_frame.zNameNoExt);
  ((void  (__cdecl *)(struct QHashTable_s *, unsigned int, const void *))SoundSys_ptLipsyncHashTable->tPrivate.pfDeleteElement)(v8, v9, (const void *)(igi2_frame.zNameNoExt));
}

// source: f/1/soundsys.c:351  [size]
void __cdecl SoundSys_RegisterSampleCallback(
        struct FileDirListCallbackContext_s *ptDirListCallbackContext,
        void *pxContext)
{
  char *zFilename; // edx
  unsigned int i; // eax
  char zExtension[32]; // [esp+Ch] [ebp-20h] BYREF

  zFilename = ptDirListCallbackContext->zFilename;
  for ( i = strlen(ptDirListCallbackContext->zFilename); i; --i )
  {
    if ( zFilename[i] == 46 )
      break;
  }
  strncpy(zExtension, &zFilename[i], 0x1Fu);
  zExtension[31] = 0;
  String_UpperInPlace(zExtension);
  if ( !strcmp(zExtension, &g_zFileName.zMenuResourcePath[192])
    || !strcmp(zExtension, &g_zFileName.zMenuResourcePath[184]) )
  {
    Sound_RegisterSample(ptDirListCallbackContext->zFilename, ptDirListCallbackContext->nSize, true);
  }
  else if ( !strcmp(zExtension, &g_zFileName.zMenuResourcePath[176]) )
  {
    SoundSys_RegisterLipsync(ptDirListCallbackContext->zFilename, ptDirListCallbackContext->nSize);
  }
}

// source: f/1/soundsys.c:378  [size]
void __cdecl SoundSys_RemoveSampleCallback(
        struct FileDirListCallbackContext_s *ptDirListCallbackContext,
        void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { char zExtension[32]; };
    struct { char igi2_o1[32]; char zSampleName[1024]; };
    char igi2_extent[1056];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct PlayingSound_s *v2; // ebx
  char *zFilename; // esi
  unsigned int i; // eax
  char *v5; // edi
  char *v6; // esi
  int v7; // ecx
  bool v8; // zf
  struct QHashTable_s *v9; // esi
  unsigned int v10; // eax
  int v11; // ebp
  struct PlayingSound_s *ptNext; // edi
  struct Sound_s *ptSound; // esi
  struct PlayingSound_s *v14; // eax

  v2 = SoundSys_atPlaylist;
  zFilename = ptDirListCallbackContext->zFilename;
  for ( i = strlen(ptDirListCallbackContext->zFilename); i; --i )
  {
    if ( zFilename[i] == 46 )
      break;
  }
  strncpy(igi2_frame.zExtension, &zFilename[i], 0x1Fu);
  igi2_frame.zExtension[31] = 0;
  String_UpperInPlace(igi2_frame.zExtension);
  if ( !strcmp(igi2_frame.zExtension, &g_zFileName.zMenuResourcePath[192])
    || !strcmp(igi2_frame.zExtension, &g_zFileName.zMenuResourcePath[184]) )
  {
    Sound_CropFilenameToSamplename(igi2_frame.zSampleName, ptDirListCallbackContext->zFilename);
    v9 = Sound_ptSampleHashTable;
    v10 = Sound_ptSampleHashTable->tPrivate.pfHashFunction(
            Sound_ptSampleHashTable->tPrivate.nHashTableSize,
            igi2_frame.zSampleName);
    v11 = ((int  (__cdecl *)(struct QHashTable_s *, unsigned int, const void *))Sound_ptSampleHashTable->tPrivate.pfFindElement)(v9, v10, (const void *)(igi2_frame.zSampleName));
    if ( v2 )
    {
      do
      {
        ptNext = v2->ptNext;
        if ( v2->ptSample == (struct Sample_s *)v11 )
        {
          ptSound = v2->ptSound;
          if ( ptSound )
            Sound_FreeSound(ptSound);
          v14 = v2->ptNext;
          if ( v14 )
            v14->ptPrev = v2->ptPrev;
          if ( v2->ptPrev )
            v2->ptPrev->ptNext = v2->ptNext;
          if ( SoundSys_atPlaylist == v2 )
            SoundSys_atPlaylist = v2->ptNext;
          v2->ptNext = SoundSys_ptFirstFree;
          v2->ptPrev = nullptr;
          if ( SoundSys_ptFirstFree )
            SoundSys_ptFirstFree->ptPrev = v2;
          SoundSys_ptFirstFree = v2;
        }
        v2 = ptNext;
      }
      while ( ptNext );
    }
    Sound_RemoveSample(ptDirListCallbackContext->zFilename);
  }
  else
  {
    v5 = &g_zFileName.zMenuResourcePath[176];
    v6 = igi2_frame.zExtension;
    v7 = 5;
    v8 = 1;
    do
    {
      if ( !v7 )
        break;
      v8 = *v6++ == *v5++;
      --v7;
    }
    while ( v8 );
    if ( v8 )
      SoundSys_RemoveLipsync(ptDirListCallbackContext->zFilename, v7);
  }
}

// source: f/1/soundsys.c:442  [size]
void __cdecl SoundSys_ScanDirectoryDirListRegisterCallback(
        struct FileDirListCallbackContext_s *ptContext,
        void *pxContext)
{
  char *zFilename; // edx
  unsigned int i; // eax
  char zExtension[12]; // [esp+4h] [ebp-Ch] BYREF

  if ( ptContext->isDirectory == false )
  {
    zFilename = ptContext->zFilename;
    for ( i = strlen(ptContext->zFilename); i; --i )
    {
      if ( zFilename[i] == 46 )
        break;
    }
    strncpy(zExtension, &zFilename[i], 9u);
    zExtension[9] = 0;
    String_UpperInPlace(zExtension);
    if ( !strcmp(zExtension, &g_zFileName.zMenuResourcePath[168]) )
    {
      SoundSys_LoadSoundResource(ptContext->zFilename);
    }
    else if ( !strcmp(zExtension, &g_zFileName.zMenuResourcePath[192])
           || !strcmp(zExtension, &g_zFileName.zMenuResourcePath[184]) )
    {
      Sound_RegisterSample(ptContext->zFilename, ptContext->nSize, false);
    }
  }
}

// source: f/1/soundsys.c:478  [size]
void __cdecl SoundSys_ScanDirectoryDirListRemoveCallback(
        struct FileDirListCallbackContext_s *ptContext,
        void *pxContext)
{
  char *zFilename; // edx
  unsigned int i; // eax
  char zExtension[12]; // [esp+4h] [ebp-Ch] BYREF

  if ( ptContext->isDirectory == false )
  {
    zFilename = ptContext->zFilename;
    for ( i = strlen(ptContext->zFilename); i; --i )
    {
      if ( zFilename[i] == 46 )
        break;
    }
    strncpy(zExtension, &zFilename[i], 9u);
    zExtension[9] = 0;
    String_UpperInPlace(zExtension);
    if ( !strcmp(zExtension, &g_zFileName.zMenuResourcePath[168]) )
    {
      SoundSys_UnloadSoundResource(ptContext->zFilename);
    }
    else if ( !strcmp(zExtension, &g_zFileName.zMenuResourcePath[192])
           || !strcmp(zExtension, &g_zFileName.zMenuResourcePath[184]) )
    {
      Sound_RemoveSample(ptContext->zFilename);
    }
  }
}

// source: f/1/soundsys.c:523  [size]
void __cdecl SoundSys_AddSoundToRequestlist(
        unsigned int nCurrentID,
        struct Sample_s *ptSample,
        unsigned int bFlags,
        struct SoundModify_t *ptModify)
{
  struct Sample_s *v4; // eax
  struct PlayingSound_s *v5; // ebp
  struct PlayingSound_s *v6; // ebp
  struct Sound_s *v7; // edx
  struct SoundModify_t *p_tModify; // ebx
  struct SoundModify_t *v9; // edx
  float *p_vVolume; // ebx
  struct Sound_s *ptSound; // esi
  struct Sound_s *v12; // esi
  struct Sound_s *v13; // esi
  struct PlayingSound_s *ptNext; // eax

  v4 = ptSample;
  v5 = SoundSys_atPlaylist;
  if ( !ptSample )
    return;
  if ( SoundSys_atPlaylist )
  {
    while ( v5->ptSample != ptSample || v5->nOwner != nCurrentID )
    {
      v5 = v5->ptNext;
      if ( !v5 )
        goto LABEL_6;
    }
    v9 = ptModify;
    v5->nAge = 0;
    p_vVolume = &v5->tModify.tAttr.vVolume;
    if ( ptModify )
    {
      qmemcpy(p_vVolume, ptModify, 0x60u);
    }
    else
    {
      Sound_DefaultSoundModify(&v5->tModify);
      v4 = ptSample;
    }
    ptSound = v5->ptSound;
    if ( ptSound )
    {
      Sound_ModifySound(ptSound, &v5->tModify);
    }
    else
    {
      if ( SoundSys_isDontAddSoundToPlayList )
      {
LABEL_21:
        if ( v9 )
          v9->vPlayPos = v5->tModify.vPlayPos;
        if ( *p_vVolume == 0.0 )
        {
          v13 = v5->ptSound;
          if ( v13 )
            Sound_FreeSound(v13);
          ptNext = v5->ptNext;
          if ( ptNext )
            ptNext->ptPrev = v5->ptPrev;
          if ( v5->ptPrev )
            v5->ptPrev->ptNext = v5->ptNext;
          if ( SoundSys_atPlaylist == v5 )
            SoundSys_atPlaylist = v5->ptNext;
          v5->ptNext = SoundSys_ptFirstFree;
          v5->ptPrev = nullptr;
          if ( SoundSys_ptFirstFree )
            SoundSys_ptFirstFree->ptPrev = v5;
          SoundSys_ptFirstFree = v5;
        }
        return;
      }
      v12 = Sound_PlaySample(v4, bFlags, &v5->tModify);
      if ( !v12 )
      {
LABEL_17:
        SoundSys_LinkOut(v5, &SoundSys_atPlaylist);
        SoundSys_LinkIn(v5, &SoundSys_ptFirstFree);
        return;
      }
      if ( *p_vVolume == 0.0 )
      {
        Sound_FreeSound(v12);
        goto LABEL_17;
      }
      v5->ptSound = v12;
    }
    v9 = ptModify;
    goto LABEL_21;
  }
LABEL_6:
  if ( !SoundSys_ptFirstFree )
    return;
  v6 = SoundSys_ptFirstFree;
  v7 = nullptr;
  p_tModify = &SoundSys_ptFirstFree->tModify;
  if ( ptModify )
  {
    qmemcpy(p_tModify, ptModify, sizeof(struct SoundModify_t));
  }
  else
  {
    Sound_DefaultSoundModify(&SoundSys_ptFirstFree->tModify);
    v4 = ptSample;
  }
  if ( !SoundSys_isDontAddSoundToPlayList )
  {
    v7 = Sound_PlaySample(v4, bFlags, p_tModify);
    if ( v7 )
    {
      if ( p_tModify->tAttr.vVolume == 0.0 )
      {
        Sound_FreeSound(v7);
        return;
      }
    }
    else if ( !SoundSys_isDontAddSoundToPlayList )
    {
      return;
    }
    v4 = ptSample;
  }
  v6->ptSample = v4;
  v6->ptSound = v7;
  v6->bFlags = bFlags;
  v6->nOwner = nCurrentID;
  v6->nAge = 0;
  SoundSys_LinkOut(v6, &SoundSys_ptFirstFree);
  v6->ptNext = SoundSys_atPlaylist;
  v6->ptPrev = nullptr;
  if ( SoundSys_atPlaylist )
    SoundSys_atPlaylist->ptPrev = v6;
  SoundSys_atPlaylist = v6;
}

// source: f/1/soundsys.c:694  [size]
void __cdecl SoundSys_UpdatePlaylist()
{
  struct PlayingSound_s *v0; // ebp
  struct PlayingSound_s *ptNext; // edi
  struct Sound_s *ptSound; // eax
  int v3; // eax
  struct h3DPOBJECT *h3DSample; // eax
  struct PlayingSound_s *v5; // eax
  struct Sound_s *v6; // esi
  struct Sound_s *v7; // esi
  struct PlayingSound_s *v8; // eax
  struct Sound_s *v9; // esi

  v0 = SoundSys_atPlaylist;
  if ( SoundSys_atPlaylist )
  {
    while ( 1 )
    {
      ptNext = v0->ptNext;
      if ( (v0->bFlags & 1) == 0 )
        break;
      ptSound = v0->ptSound;
      if ( ptSound )
      {
        if ( Sound_isSSInitialized == false )
          goto LABEL_12;
        if ( ptSound->hStream )
        {
          v3 = AIL_stream_status(ptSound->hStream);
        }
        else if ( ptSound->hSample )
        {
          v3 = AIL_sample_status(ptSound->hSample);
        }
        else
        {
          h3DSample = ptSound->h3DSample;
          if ( !h3DSample )
            goto LABEL_12;
          v3 = AIL_3D_sample_status(h3DSample);
        }
        if ( v3 != 4 )
        {
LABEL_12:
          Sound_FreeSound(v0->ptSound);
LABEL_13:
          v5 = v0->ptNext;
          if ( v5 )
            v5->ptPrev = v0->ptPrev;
          if ( v0->ptPrev )
            v0->ptPrev->ptNext = v0->ptNext;
          if ( SoundSys_atPlaylist == v0 )
            SoundSys_atPlaylist = v0->ptNext;
          v0->ptNext = SoundSys_ptFirstFree;
          v0->ptPrev = nullptr;
          if ( SoundSys_ptFirstFree )
            SoundSys_ptFirstFree->ptPrev = v0;
          goto LABEL_21;
        }
      }
      v6 = v0->ptSound;
      if ( v6 )
        Sound_ModifySound(v6, &v0->tModify);
      if ( v0->tModify.tAttr.vVolume != 0.0 )
        goto LABEL_39;
      v7 = v0->ptSound;
      if ( v7 )
        Sound_FreeSound(v7);
      v8 = v0->ptNext;
      if ( v8 )
        v8->ptPrev = v0->ptPrev;
      if ( v0->ptPrev )
        v0->ptPrev->ptNext = v0->ptNext;
      if ( SoundSys_atPlaylist == v0 )
        SoundSys_atPlaylist = v0->ptNext;
      v0->ptNext = SoundSys_ptFirstFree;
      v0->ptPrev = nullptr;
      if ( SoundSys_ptFirstFree )
      {
        SoundSys_ptFirstFree->ptPrev = v0;
        SoundSys_ptFirstFree = v0;
        goto LABEL_39;
      }
LABEL_21:
      SoundSys_ptFirstFree = v0;
LABEL_39:
      v0 = ptNext;
      if ( !ptNext )
        return;
    }
    if ( !v0->nAge )
    {
      v0->nAge = 1;
      goto LABEL_39;
    }
    v9 = v0->ptSound;
    if ( v9 )
    {
      Sound_FreeSound(v9);
      v0->ptSound = nullptr;
    }
    goto LABEL_13;
  }
}

// source: f/1/soundsys.c:784  [size]
void __cdecl SoundSys_ControlCreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ;
}

// source: f/1/soundsys.c:803  [size]
// attributes: thunk
void __cdecl SoundSys_ControlRunHandler(struct QTask_s *ptQTask)
{
  SoundSys_UpdatePlaylist();
}

// source: f/1/soundsys.c:846  [size]
void __cdecl SoundSys_ControlDeleteHandler(struct QTask_s *ptQTask)
{
  ;
}

// source: f/1/soundsys.c:864  [anchor-callee]
int __cdecl SoundSys_GetLipsync(char *pzFilename, float **ppvData)
{
  struct QHashTable_s *v2; // esi
  unsigned int v3; // eax
  int v4; // eax
  char zUpper[256]; // [esp+4h] [ebp-100h] BYREF

  strncpy(zUpper, pzFilename, 0x100u);
  String_UpperInPlace(zUpper);
  v2 = SoundSys_ptLipsyncHashTable;
  v3 = SoundSys_ptLipsyncHashTable->tPrivate.pfHashFunction(
         SoundSys_ptLipsyncHashTable->tPrivate.nHashTableSize,
         zUpper);
  v4 = ((int  (__cdecl *)(struct QHashTable_s *, unsigned int, const void *))SoundSys_ptLipsyncHashTable->tPrivate.pfFindElement)(v2, v3, (const void *)(zUpper));
  if ( v4 )
  {
    *ppvData = (float *)(v4 + 4);
    return *(_DWORD *)v4;
  }
  else
  {
    *ppvData = nullptr;
    return 0;
  }
}

// source: f/1/soundsys.c:896  [anchor-strings]
void __cdecl SoundSys_SoundDefCreateHandler(struct QTask_s *ptQTask, void *pxData)
{
  struct QHashTable_s *v2; // edi
  unsigned int v3; // eax
  int v4; // eax
  struct QHashTable_s *v5; // edi
  unsigned int v6; // eax
  int v7; // eax
  struct QHashTable_s *v8; // edi
  unsigned int v9; // eax
  int v10; // eax
  struct QHashTable_s *v11; // edi
  unsigned int v12; // eax
  int v13; // eax
  struct Script_s *v14; // eax
  struct Script_s *v15; // esi

  strcpy((char *)&ptQTask[1], (char *)pxData);
  QTaskList_Register(SoundSys_ptSoundDefQTaskList, (struct QTaskList_s *)ptQTask);
  v2 = Symbol_ptSymbolHashTable;
  v3 = Symbol_ptSymbolHashTable->tPrivate.pfHashFunction(
         Symbol_ptSymbolHashTable->tPrivate.nHashTableSize,
         &g_zFileName.zMenuResourcePath[156]);
  v4 = ((int  (__cdecl *)(struct QHashTable_s *, unsigned int, const void *))Symbol_ptSymbolHashTable->tPrivate.pfFindElement)(v2, v3, (const void *)(&g_zFileName.zMenuResourcePath[156]));
  if ( !v4 || !*(_DWORD *)(v4 + 20) )
  {
    LDebug_Error("Script_SetSymbolContext(): Symbol not found: %s", &g_zFileName.zMenuResourcePath[156]);
LABEL_12:
    abort();
  }
  *(_DWORD *)(v4 + 24) = ptQTask;
  v5 = Symbol_ptSymbolHashTable;
  v6 = Symbol_ptSymbolHashTable->tPrivate.pfHashFunction(
         Symbol_ptSymbolHashTable->tPrivate.nHashTableSize,
         &g_zFileName.zMenuResourcePath[144]);
  v7 = ((int  (__cdecl *)(struct QHashTable_s *, unsigned int, const void *))Symbol_ptSymbolHashTable->tPrivate.pfFindElement)(v5, v6, (const void *)(&g_zFileName.zMenuResourcePath[144]));
  if ( !v7 || !*(_DWORD *)(v7 + 20) )
  {
    LDebug_Error("Script_SetSymbolContext(): Symbol not found: %s", &g_zFileName.zMenuResourcePath[144]);
    goto LABEL_12;
  }
  *(_DWORD *)(v7 + 24) = ptQTask;
  v8 = Symbol_ptSymbolHashTable;
  v9 = Symbol_ptSymbolHashTable->tPrivate.pfHashFunction(
         Symbol_ptSymbolHashTable->tPrivate.nHashTableSize,
         &g_zFileName.zMenuResourcePath[132]);
  v10 = ((int  (__cdecl *)(struct QHashTable_s *, unsigned int, const void *))Symbol_ptSymbolHashTable->tPrivate.pfFindElement)(v8, v9, (const void *)(&g_zFileName.zMenuResourcePath[132]));
  if ( !v10 || !*(_DWORD *)(v10 + 20) )
  {
    LDebug_Error("Script_SetSymbolContext(): Symbol not found: %s", &g_zFileName.zMenuResourcePath[132]);
    goto LABEL_12;
  }
  *(_DWORD *)(v10 + 24) = ptQTask;
  v11 = Symbol_ptSymbolHashTable;
  v12 = Symbol_ptSymbolHashTable->tPrivate.pfHashFunction(
          Symbol_ptSymbolHashTable->tPrivate.nHashTableSize,
          &g_zFileName.zMenuResourcePath[112]);
  v13 = ((int  (__cdecl *)(struct QHashTable_s *, unsigned int, const void *))Symbol_ptSymbolHashTable->tPrivate.pfFindElement)(v11, v12, (const void *)(&g_zFileName.zMenuResourcePath[112]));
  if ( !v13 || !*(_DWORD *)(v13 + 20) )
  {
    LDebug_Error("Script_SetSymbolContext(): Symbol not found: %s", &g_zFileName.zMenuResourcePath[112]);
    goto LABEL_12;
  }
  *(_DWORD *)(v13 + 24) = ptQTask;
  v14 = Script_New((char *)pxData);
  v15 = v14;
  if ( v14 )
  {
    Script_Execute(v14);
    Script_Delete(v15);
  }
}

// source: f/1/soundsys.c:938  [size]
void __cdecl SoundSys_SoundDefDeleteHandler(struct QTask_s *ptQTask)
{
  QTaskList_Remove(SoundSys_ptSoundDefQTaskList, ptQTask);
}

// source: f/1/soundsys.c:953  [size]
void __cdecl SoundSys_SoundDefFindSoundDefHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *ptHead; // esi
  __int16 v3; // ax
  struct QTask_s *v4; // ecx
  int v5; // edx
  void (__cdecl *pfHandler)(struct QTask_s *, void *); // ecx

  ptHead = ptQTask->tQTaskChildren.ptHead;
  if ( ptHead->ptNext && ptHead )
  {
    v3 = SoundSys_eFindSoundDefQTaskEvent;
    do
    {
      if ( ptHead->ptNext )
        v4 = ptHead->ptNext->ptNext != nullptr ? ptHead->ptNext : nullptr;
      else
        v4 = nullptr;
      v5 = QTask_nProtectedQTaskStackOffset;
      QTask_atProtectedQTaskStack[QTask_nProtectedQTaskStackOffset].ptQTask = v4;
      QTask_nProtectedQTaskStackOffset = v5 + 1;
      if ( v3 == 512 )
      {
        v3 = QTask_NewQTaskEventFn(0, (char *)&g_zFileName.iActiveTABItem);
        SoundSys_eFindSoundDefQTaskEvent = v3;
      }
      pfHandler = (void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[v3][ptHead->eQTaskType].pfHandler;
      if ( pfHandler )
      {
        pfHandler(ptHead, pxContext);
        v3 = SoundSys_eFindSoundDefQTaskEvent;
      }
      ptHead = (struct QTask_s *)dword_849C7DC[QTask_nProtectedQTaskStackOffset--];
    }
    while ( ptHead );
  }
}

// source: f/1/soundsys.c:966  [anchor-mhash]
void __cdecl SoundSys_SoundDefParentCreateHandler(struct QTask_s *ptQTask, void *pxData)
{
  strcpy((char *)&ptQTask[1], (char *)pxData);
}

// source: f/1/soundsys.c:988  [size]
int __cdecl SoundSys_SetFrequency(int nFrequency)
{
  SoundSys_nFrequency = nFrequency;
  Sound_nFrequency = nFrequency;
  return nFrequency;
}

// source: f/1/soundsys.c:1003  [size]
int __cdecl SoundSys_GetFrequency()
{
  return SoundSys_nFrequency;
}

// source: f/1/soundsys.c:1016  [size]
void __cdecl SoundSys_EditorEnabled(int isEditor)
{
  SoundSys_isEditorEnabled = isEditor;
}

// source: f/1/soundsys.c:1029  [size]
char __cdecl SoundSys_IsEditorEnabled()
{
  return SoundSys_isEditorEnabled;
}

// source: f/1/soundsys.c:1042  [size]
char __cdecl SoundSys_DisplaySpheres()
{
  return SoundSys_isSpheres;
}

// source: f/1/soundsys.c:1055  [anchor-strings]
void __cdecl SoundSys_Open()
{
  unsigned __int16 BaseQTaskType; // ax
  unsigned __int16 v1; // ax
  unsigned __int16 v2; // ax
  unsigned __int16 v3; // ax
  unsigned __int16 v4; // bx
  unsigned __int16 v5; // si
  unsigned __int16 v6; // di
  __int16 v7; // ax
  struct PlayingSound_s *v8; // eax
  int v9; // esi
  struct PlayingSound_s *v10; // ecx
  struct QHashTable_s *v11; // esi
  void *v12; // edi
  unsigned int v13; // eax

  SoundSys_isMusicFileBased = 1;
  SoundSys_ptSoundQTaskList = QTaskList_New(1024);
  SoundSys_ptSoundDefQTaskList = QTaskList_New(8);
  BaseQTaskType = QTask_GetBaseQTaskType();
  SoundSys_eSystemControlQTaskType = QTask_NewQTaskType(&g_zFileName.zMenuResourcePath[92], 40, BaseQTaskType, 0, 0);
  v1 = QTask_GetBaseQTaskType();
  SoundSys_eSystemSoundDefQTaskType = QTask_NewQTaskType(&g_zFileName.zMenuResourcePath[80], 300, v1, 0, 0);
  v2 = QTask_GetBaseQTaskType();
  v3 = QTask_NewQTaskType(&g_zFileName.zMenuResourcePath[60], 300, v2, 0, 0);
  v4 = SoundSys_eSystemControlQTaskType;
  v5 = SoundSys_eSystemSoundDefQTaskType;
  v6 = v3;
  SoundSys_eSystemSoundDefParentQTaskType = v3;
  SoundSys_eSystemSoundDefCreateQTaskType = SoundSys_eSystemSoundDefQTaskType;
  SoundSys_eSystemSoundDefParentCreateQTaskType = v3;
  QTask_LinkQTaskEventHandlerFn(
    SoundSys_eSystemControlQTaskType,
    0,
    (void (__cdecl *)(struct QTask_s *, void *))SoundSys_ControlCreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v4, 1, SoundSys_ControlRunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v4, 2, (void (__cdecl *)(struct QTask_s *))SoundSys_ControlDeleteHandler);
  QTask_LinkQTaskEventHandlerFn(v5, 0, SoundSys_SoundDefCreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v5, 2, SoundSys_SoundDefDeleteHandler);
  v7 = SoundSys_eFindSoundDefQTaskEvent;
  if ( SoundSys_eFindSoundDefQTaskEvent == 512 )
  {
    v7 = QTask_NewQTaskEventFn(0, (char *)&g_zFileName.iActiveTABItem);
    v6 = SoundSys_eSystemSoundDefParentQTaskType;
    v5 = SoundSys_eSystemSoundDefQTaskType;
    SoundSys_eFindSoundDefQTaskEvent = v7;
  }
  QTask_LinkQTaskEventHandlerFn(v5, v7, SoundSys_SoundDefFindSoundDefHandler);
  QTask_LinkQTaskEventHandlerFn(v6, 0, SoundSys_SoundDefParentCreateHandler);
  SoundSys_nMaxVoices = Sound_nSSMaxPlayBuffers;
  SoundSys_nCurrentID = 1;
  SoundSys_nFrequency = 0;
  v8 = (struct PlayingSound_s *)Mem_AllocFn(Sound_nSSMaxPlayBuffers << 7, 4);
  v9 = SoundSys_nMaxVoices;
  memset(v8, 0, SoundSys_nMaxVoices << 7);
  SoundSys_atPlayingSoundList = v8;
  if ( v9 > 0 )
  {
    v10 = SoundSys_ptFirstFree;
    do
    {
      v8->ptNext = v10;
      v8->ptPrev = nullptr;
      if ( SoundSys_ptFirstFree )
        SoundSys_ptFirstFree->ptPrev = v8;
      v10 = v8++;
      --v9;
      SoundSys_ptFirstFree = v10;
    }
    while ( v9 );
  }
  Symbol_Register(
    &g_zFileName.zMenuResourcePath[156],
    SoundDefGroup_ScriptParseCB,
    nullptr,
    -1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &g_zFileName.zMenuResourcePath[144],
    SoundDefSound_ScriptParseCB,
    nullptr,
    -1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &g_zFileName.zMenuResourcePath[132],
    SoundDefGraph_ScriptParseCB,
    nullptr,
    -1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    &g_zFileName.zMenuResourcePath[112],
    SoundDefTriggerOnce_ScriptParseCB,
    nullptr,
    -1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  v11 = (struct QHashTable_s *)Mem_AllocFn(40, 4);
  v11->tPrivate.nHashTableSize = 32;
  v11->tPrivate.pfHashFunction = QHashTable_StringHashFunction;
  v11->tPrivate.pfCompareKey = QHashTable_StringCompareKeyFunction;
  v11->tPrivate.pfDuplicateKey = QHashTable_StringDuplicateKeyFunction;
  v11->tPrivate.pfCreateElement = QHashTable_CreateElementChained;
  v11->tPrivate.pfFindElement = QHashTable_FindElementChained;
  v11->tPrivate.pfDeleteElement = QHashTable_DeleteElementChained;
  v11->tPrivate.pfMap = QHashTable_MapChained;
  v11->tPrivate.nEntries = 0;
  v12 = Mem_AllocFn(384, 4);
  v13 = 0;
  v11->tPrivate.papxElement = v12;
  memset(v12, 0, 0x180u);
  do
  {
    *(_DWORD *)((char *)v11->tPrivate.papxElement + v13) = (char *)v11->tPrivate.papxElement + v13 + 4;
    *(_DWORD *)((char *)v11->tPrivate.papxElement + v13 + 8) = (char *)v11->tPrivate.papxElement + v13;
    *(_DWORD *)((char *)v11->tPrivate.papxElement + v13 + 4) = 0;
    *(_DWORD *)((char *)v11->tPrivate.papxElement + v13 + 12) = (char *)v11->tPrivate.papxElement + v13 + 16;
    *(_DWORD *)((char *)v11->tPrivate.papxElement + v13 + 20) = (char *)v11->tPrivate.papxElement + v13 + 12;
    *(_DWORD *)((char *)v11->tPrivate.papxElement + v13 + 16) = 0;
    *(_DWORD *)((char *)v11->tPrivate.papxElement + v13 + 24) = (char *)v11->tPrivate.papxElement + v13 + 28;
    *(_DWORD *)((char *)v11->tPrivate.papxElement + v13 + 32) = (char *)v11->tPrivate.papxElement + v13 + 24;
    *(_DWORD *)((char *)v11->tPrivate.papxElement + v13 + 28) = 0;
    *(_DWORD *)((char *)v11->tPrivate.papxElement + v13 + 36) = (char *)v11->tPrivate.papxElement + v13 + 40;
    *(_DWORD *)((char *)v11->tPrivate.papxElement + v13 + 44) = (char *)v11->tPrivate.papxElement + v13 + 36;
    *(_DWORD *)((char *)v11->tPrivate.papxElement + v13 + 40) = 0;
    *(_DWORD *)((char *)v11->tPrivate.papxElement + v13 + 48) = (char *)v11->tPrivate.papxElement + v13 + 52;
    *(_DWORD *)((char *)v11->tPrivate.papxElement + v13 + 56) = (char *)v11->tPrivate.papxElement + v13 + 48;
    *(_DWORD *)((char *)v11->tPrivate.papxElement + v13 + 52) = 0;
    *(_DWORD *)((char *)v11->tPrivate.papxElement + v13 + 60) = (char *)v11->tPrivate.papxElement + v13 + 64;
    *(_DWORD *)((char *)v11->tPrivate.papxElement + v13 + 68) = (char *)v11->tPrivate.papxElement + v13 + 60;
    *(_DWORD *)((char *)v11->tPrivate.papxElement + v13 + 64) = 0;
    *(_DWORD *)((char *)v11->tPrivate.papxElement + v13 + 72) = (char *)v11->tPrivate.papxElement + v13 + 76;
    *(_DWORD *)((char *)v11->tPrivate.papxElement + v13 + 80) = (char *)v11->tPrivate.papxElement + v13 + 72;
    *(_DWORD *)((char *)v11->tPrivate.papxElement + v13 + 76) = 0;
    *(_DWORD *)((char *)v11->tPrivate.papxElement + v13 + 84) = (char *)v11->tPrivate.papxElement + v13 + 88;
    *(_DWORD *)((char *)v11->tPrivate.papxElement + v13 + 92) = (char *)v11->tPrivate.papxElement + v13 + 84;
    *(_DWORD *)((char *)v11->tPrivate.papxElement + v13 + 88) = 0;
    v13 += 96;
  }
  while ( v13 < 0x180 );
  SoundSys_ptLipsyncHashTable = v11;
  SoundSys_isSoundDisabled = Sound_isSSInitialized == false;
}

// source: f/1/soundsys.c:1142  [anchor-hash]
void __cdecl SoundSys_Close()
{
  int v0; // esi

  QHashTable_Delete(SoundSys_ptLipsyncHashTable);
  QTaskList_Delete(SoundSys_ptSoundQTaskList);
  QTaskList_Delete(SoundSys_ptSoundDefQTaskList);
  if ( SoundSys_atPlayingSoundList )
  {
    v0 = *(_DWORD *)((unsigned int)(&SoundSys_atPlayingSoundList[-1].tModify.vPlayPos + 1) & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
  SoundSys_atPlayingSoundList = nullptr;
  if ( SoundSys_eSaveQTaskEvent != 512 )
    QTask_DeleteQTaskEvent(SoundSys_eSaveQTaskEvent);
  if ( SoundSys_eUpdateParameterListQTaskEvent != 512 )
    QTask_DeleteQTaskEvent(SoundSys_eUpdateParameterListQTaskEvent);
  if ( SoundSys_eFindSoundDefQTaskEvent != 512 )
    QTask_DeleteQTaskEvent(SoundSys_eFindSoundDefQTaskEvent);
  if ( SoundSys_eRequestSoundDefQTaskEvent != 512 )
    QTask_DeleteQTaskEvent(SoundSys_eRequestSoundDefQTaskEvent);
  if ( SoundSys_eSetPositionQTaskEvent != 512 )
    QTask_DeleteQTaskEvent(SoundSys_eSetPositionQTaskEvent);
  if ( SoundSys_eSetSectorQTaskEvent != 512 )
    QTask_DeleteQTaskEvent(SoundSys_eSetSectorQTaskEvent);
  if ( SoundSys_eSetVolumeQTaskEvent != 512 )
    QTask_DeleteQTaskEvent(SoundSys_eSetVolumeQTaskEvent);
  if ( SoundSys_eSetPitchQTaskEvent != 512 )
    QTask_DeleteQTaskEvent(SoundSys_eSetPitchQTaskEvent);
  if ( SoundSys_eSetRelativeToMicrophoneQTaskEvent != 512 )
    QTask_DeleteQTaskEvent(SoundSys_eSetRelativeToMicrophoneQTaskEvent);
  if ( SoundSys_eGetSoundRadiusQTaskEvent != 512 )
    QTask_DeleteQTaskEvent(SoundSys_eGetSoundRadiusQTaskEvent);
  if ( SoundSys_eGetSoundLengthQTaskEvent != 512 )
    QTask_DeleteQTaskEvent(SoundSys_eGetSoundLengthQTaskEvent);
  QTask_DeleteQTaskType(SoundSys_eSystemControlQTaskType);
  QTask_DeleteQTaskType(SoundSys_eSystemSoundDefParentQTaskType);
  QTask_DeleteQTaskType(SoundSys_eSystemSoundDefQTaskType);
  Symbol_Remove(&g_zFileName.zMenuResourcePath[156]);
  Symbol_Remove(&g_zFileName.zMenuResourcePath[144]);
  Symbol_Remove(&g_zFileName.zMenuResourcePath[132]);
  Symbol_Remove(&g_zFileName.zMenuResourcePath[112]);
}

// source: f/1/soundsys.c:1232  [size]
struct QTask_s *__cdecl SoundSys_NewControlQTask(struct QTask_s *ptParent)
{
  return QTask_NewFn(ptParent, SoundSys_eSystemControlQTaskType, nullptr);
}

// source: f/1/soundsys.c:1250  [anchor-strings]
struct QTask_s *__cdecl SoundSys_NewSoundDefParentQTask(
        struct QTask_s *ptParent,
        char *pzDirectory)
{
  struct QTask_s *v2; // edi
  char v3; // al
  char zFileString[1024]; // [esp+8h] [ebp-400h] BYREF

  v2 = QTask_NewFn(ptParent, SoundSys_eSystemSoundDefParentQTaskType, pzDirectory);
  v3 = pzDirectory[strlen(pzDirectory) - 1];
  if ( v3 == 47 || v3 == 92 )
    sprintf(zFileString, &g_zFileName.zMenuResourcePath[44], pzDirectory);
  else
    sprintf(zFileString, &g_zFileName.zMenuResourcePath[28], pzDirectory);
  QTask_NewFn(v2, SoundSys_eSystemSoundDefCreateQTaskType, zFileString);
  return v2;
}

// source: f/1/soundsys.c:1294  [size]
struct QTask_s *__cdecl SoundSys_NewSoundDefQTask(
        struct QTask_s *ptParent,
        char *pzSoundDefFile)
{
  return QTask_NewFn(ptParent, SoundSys_eSystemSoundDefCreateQTaskType, (void *)pzSoundDefFile);
}

// source: f/1/soundsys.c:1312  [size]
void __cdecl SoundSys_SetSoundDefCreateQTask(unsigned __int16 eQTaskType)
{
  SoundSys_eSystemSoundDefCreateQTaskType = eQTaskType;
}

// source: f/1/soundsys.c:1327  [size]
void __cdecl SoundSys_SetSoundDefParentCreateQTask(unsigned __int16 eQTaskType)
{
  SoundSys_eSystemSoundDefParentCreateQTaskType = eQTaskType;
}

// source: f/1/soundsys.c:1342  [size]
unsigned __int16 __cdecl SoundSys_GetSoundDefQTaskType()
{
  return SoundSys_eSystemSoundDefQTaskType;
}

// source: f/1/soundsys.c:1357  [size]
unsigned __int16 __cdecl SoundSys_GetSoundDefParentQTaskType()
{
  return SoundSys_eSystemSoundDefParentQTaskType;
}

// source: f/1/soundsys.c:1372  [anchor-refs]
__int16 __cdecl SoundSys_GetSaveQTaskEvent()
{
  __int16 result; // ax

  result = SoundSys_eSaveQTaskEvent;
  if ( SoundSys_eSaveQTaskEvent == 512 )
  {
    result = QTask_NewQTaskEventFn(0, &g_zFileName.zMenuResourcePath[16]);
    SoundSys_eSaveQTaskEvent = result;
  }
  return result;
}

// source: f/1/soundsys.c:1392  [size]
__int16 __cdecl SoundSys_GetUpdateParameterListQTaskEvent()
{
  __int16 result; // ax

  result = SoundSys_eUpdateParameterListQTaskEvent;
  if ( SoundSys_eUpdateParameterListQTaskEvent == 512 )
  {
    result = QTask_NewQTaskEventFn(0, (char *)&g_zFileName.nRealFadeCount);
    SoundSys_eUpdateParameterListQTaskEvent = result;
  }
  return result;
}

// source: f/1/soundsys.c:1412  [size]
__int16 __cdecl SoundSys_GetFindSoundDefQTaskEvent()
{
  __int16 result; // ax

  result = SoundSys_eFindSoundDefQTaskEvent;
  if ( SoundSys_eFindSoundDefQTaskEvent == 512 )
  {
    result = QTask_NewQTaskEventFn(0, (char *)&g_zFileName.iActiveTABItem);
    SoundSys_eFindSoundDefQTaskEvent = result;
  }
  return result;
}

// source: f/1/soundsys.c:1432  [anchor-refs]
__int16 __cdecl SoundSys_GetRequestSoundDefQTaskEvent()
{
  __int16 result; // ax

  result = SoundSys_eRequestSoundDefQTaskEvent;
  if ( SoundSys_eRequestSoundDefQTaskEvent == 512 )
  {
    result = QTask_NewQTaskEventFn(0, (char *)&g_zFileName.aptSelectableTABItems[31]);
    SoundSys_eRequestSoundDefQTaskEvent = result;
  }
  return result;
}

// source: f/1/soundsys.c:1452  [anchor-strings]
__int16 __cdecl SoundSys_GetSetPositionQTaskEvent()
{
  __int16 result; // ax

  result = SoundSys_eSetPositionQTaskEvent;
  if ( SoundSys_eSetPositionQTaskEvent == 512 )
  {
    result = QTask_NewQTaskEventFn(0, (char *)&g_zFileName.aptSelectableTABItems[26]);
    SoundSys_eSetPositionQTaskEvent = result;
  }
  return result;
}

// source: f/1/soundsys.c:1473  [anchor-strings]
__int16 __cdecl SoundSys_GetSetSectorQTaskEvent()
{
  __int16 result; // ax

  result = SoundSys_eSetSectorQTaskEvent;
  if ( SoundSys_eSetSectorQTaskEvent == 512 )
  {
    result = QTask_NewQTaskEventFn(0, (char *)&g_zFileName.aptSelectableTABItems[22]);
    SoundSys_eSetSectorQTaskEvent = result;
  }
  return result;
}

// source: f/1/soundsys.c:1494  [size]
__int16 __cdecl SoundSys_GetSetVolumeQTaskEvent()
{
  __int16 result; // ax

  result = SoundSys_eSetVolumeQTaskEvent;
  if ( SoundSys_eSetVolumeQTaskEvent == 512 )
  {
    result = QTask_NewQTaskEventFn(0, (char *)&g_zFileName.aptSelectableTABItems[18]);
    SoundSys_eSetVolumeQTaskEvent = result;
  }
  return result;
}

// source: f/1/soundsys.c:1514  [size]
__int16 __cdecl SoundSys_GetSetPitchQTaskEvent()
{
  __int16 result; // ax

  result = SoundSys_eSetPitchQTaskEvent;
  if ( SoundSys_eSetPitchQTaskEvent == 512 )
  {
    result = QTask_NewQTaskEventFn(0, (char *)&g_zFileName.aptSelectableTABItems[14]);
    SoundSys_eSetPitchQTaskEvent = result;
  }
  return result;
}

// source: f/1/soundsys.c:1534  [size]
__int16 __cdecl SoundSys_GetSetRelativeToMicrophoneQTaskEvent()
{
  __int16 result; // ax

  result = SoundSys_eSetRelativeToMicrophoneQTaskEvent;
  if ( SoundSys_eSetRelativeToMicrophoneQTaskEvent == 512 )
  {
    result = QTask_NewQTaskEventFn(0, (char *)&g_zFileName.aptSelectableTABItems[6]);
    SoundSys_eSetRelativeToMicrophoneQTaskEvent = result;
  }
  return result;
}

// source: f/1/soundsys.c:1554  [size]
__int16 __cdecl SoundSys_GetGetSoundRadiusQTaskEvent()
{
  __int16 result; // ax

  result = SoundSys_eGetSoundRadiusQTaskEvent;
  if ( SoundSys_eGetSoundRadiusQTaskEvent == 512 )
  {
    result = QTask_NewQTaskEventFn(0, (char *)&g_zFileName.aptSelectableTABItems[2]);
    SoundSys_eGetSoundRadiusQTaskEvent = result;
  }
  return result;
}

// source: f/1/soundsys.c:1574  [size]
__int16 __cdecl SoundSys_GetGetSoundLengthQTaskEvent()
{
  __int16 result; // ax

  result = SoundSys_eGetSoundLengthQTaskEvent;
  if ( SoundSys_eGetSoundLengthQTaskEvent == 512 )
  {
    result = QTask_NewQTaskEventFn(0, (char *)&g_zFileName.aptSelectableItems[30]);
    SoundSys_eGetSoundLengthQTaskEvent = result;
  }
  return result;
}

// source: f/1/soundsys.c:1596  [anchor-callee]
void __cdecl SoundSys_LoadSoundResource(char *pzFilename)
{
  #pragma pack(push, 1)
  union
  {
    struct { char zFilename[4]; };
    struct { char igi2_o1[4]; int v18; };
    struct { char igi2_o2[8]; int v19; };
    struct { char igi2_o3[12]; int v20; };
    struct { char igi2_o4[16]; int v21; };
    struct { char igi2_o5[20]; int v22; };
    struct { char igi2_o6[24]; int v23; };
    struct { char igi2_o7[28]; char zPath[128]; };
    char igi2_extent[29];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v2; // ebp
  char *v3; // edx
  unsigned int v4; // esi
  int v5; // edi
  char v6; // cl
  char *v7; // eax
  char v8; // cl
  char v9; // cl
  char v10; // cl
  char v11; // cl
  char v12; // cl
  char v13; // cl
  char v14; // cl
  char *v15; // ecx
  void *v16; // eax

  igi2_frame.v21 = &igi2_frame.zPath[2] - pzFilename;
  igi2_frame.v22 = &igi2_frame.zPath[3] - pzFilename;
  igi2_frame.v23 = &igi2_frame.zPath[4] - pzFilename;
  igi2_frame.v18 = &igi2_frame.zPath[5] - pzFilename;
  igi2_frame.v19 = &igi2_frame.zPath[6] - pzFilename;
  v2 = &igi2_frame.zPath[1] - pzFilename;
  v3 = nullptr;
  v4 = 0;
  v5 = igi2_frame.zPath - pzFilename;
  *(_DWORD *)igi2_frame.zFilename = &igi2_frame.zPath[1] - pzFilename;
  igi2_frame.v20 = &igi2_frame.zPath[7] - pzFilename;
  while ( 1 )
  {
    v6 = pzFilename[v4];
    v7 = &pzFilename[v4];
    if ( !v6 )
      break;
    if ( v6 == 92 || v6 == 47 )
      v3 = &v7[v5];
    v7[v5] = v6;
    v8 = pzFilename[v4 + 1];
    if ( !v8 )
      break;
    if ( v8 == 92 || v8 == 47 )
      v3 = &v7[v2];
    v7[v2] = v8;
    v9 = pzFilename[v4 + 2];
    if ( !v9 )
      break;
    if ( v9 == 92 || v9 == 47 )
      v3 = &v7[igi2_frame.v21];
    v7[igi2_frame.v21] = v9;
    v10 = pzFilename[v4 + 3];
    if ( !v10 )
      break;
    if ( v10 == 92 || v10 == 47 )
      v3 = &v7[igi2_frame.v22];
    v7[igi2_frame.v22] = v10;
    v11 = pzFilename[v4 + 4];
    if ( !v11 )
      break;
    if ( v11 == 92 || v11 == 47 )
      v3 = &v7[igi2_frame.v23];
    v7[igi2_frame.v23] = v11;
    v12 = pzFilename[v4 + 5];
    if ( !v12 )
      break;
    if ( v12 == 92 || v12 == 47 )
      v3 = &v7[igi2_frame.v18];
    v7[igi2_frame.v18] = v12;
    v13 = pzFilename[v4 + 6];
    if ( !v13 )
      break;
    if ( v13 == 92 || v13 == 47 )
      v3 = &v7[igi2_frame.v19];
    v7[igi2_frame.v19] = v13;
    v14 = pzFilename[v4 + 7];
    if ( !v14 )
      break;
    if ( v14 == 92 || v14 == 47 )
      v3 = &v7[igi2_frame.v20];
    v4 += 8;
    v7[igi2_frame.v20] = v14;
    if ( v4 >= 0x80 )
      break;
    v2 = *(_DWORD *)igi2_frame.zFilename;
  }
  if ( v3 )
    *v3 = 0;
  else
    igi2_frame.zPath[0] = 0;
  if ( Resource_IsLoadedInternal(pzFilename, nullptr) || File_Exists(pzFilename) )
  {
    if ( Resource_IsLoadedInternal(pzFilename, (struct Resource_s **)igi2_frame.zFilename) )
    {
      *(_DWORD *)(*(_DWORD *)igi2_frame.zFilename + 44) = 1;
    }
    else
    {
      Game_MPRunNetwork(v15);
      v16 = File_Load(pzFilename, (unsigned int *)igi2_frame.zFilename);
      if ( !v16 )
      {
        LDebug_Error("Failed to load resource: '%s'", pzFilename);
        abort();
      }
      Resource_ParseFile(File_zLastSubstitutedPath, v16, *(unsigned int *)igi2_frame.zFilename);
    }
    Resource_DirList(igi2_frame.zPath, SoundSys_RegisterSampleCallback, nullptr);
  }
}

// source: f/1/soundsys.c:1643  [anchor-callee]
char *__cdecl SoundSys_UnloadSoundResource(char *pzFilename)
{
  #pragma pack(push, 1)
  union
  {
    struct { char zFilename[4]; };
    struct { char igi2_o1[4]; int v17; };
    struct { char igi2_o2[8]; int v18; };
    struct { char igi2_o3[12]; int v19; };
    struct { char igi2_o4[16]; int v20; };
    struct { char igi2_o5[20]; int v21; };
    struct { char igi2_o6[24]; int v22; };
    struct { char igi2_o7[28]; char zPath[128]; };
    char igi2_extent[29];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v2; // ebp
  char *v3; // edx
  unsigned int v4; // esi
  int v5; // edi
  char v6; // cl
  char *v7; // eax
  char v8; // cl
  char v9; // cl
  char v10; // cl
  char v11; // cl
  char v12; // cl
  char v13; // cl
  char v14; // cl
  char *result; // eax

  igi2_frame.v20 = &igi2_frame.zPath[2] - pzFilename;
  igi2_frame.v21 = &igi2_frame.zPath[3] - pzFilename;
  igi2_frame.v22 = &igi2_frame.zPath[4] - pzFilename;
  igi2_frame.v17 = &igi2_frame.zPath[5] - pzFilename;
  igi2_frame.v18 = &igi2_frame.zPath[6] - pzFilename;
  v2 = &igi2_frame.zPath[1] - pzFilename;
  v3 = nullptr;
  v4 = 0;
  v5 = igi2_frame.zPath - pzFilename;
  *(_DWORD *)igi2_frame.zFilename = &igi2_frame.zPath[1] - pzFilename;
  igi2_frame.v19 = &igi2_frame.zPath[7] - pzFilename;
  while ( 1 )
  {
    v6 = pzFilename[v4];
    v7 = &pzFilename[v4];
    if ( !v6 )
      break;
    if ( v6 == 92 || v6 == 47 )
      v3 = &v7[v5];
    v7[v5] = v6;
    v8 = pzFilename[v4 + 1];
    if ( !v8 )
      break;
    if ( v8 == 92 || v8 == 47 )
      v3 = &v7[v2];
    v7[v2] = v8;
    v9 = pzFilename[v4 + 2];
    if ( !v9 )
      break;
    if ( v9 == 92 || v9 == 47 )
      v3 = &v7[igi2_frame.v20];
    v7[igi2_frame.v20] = v9;
    v10 = pzFilename[v4 + 3];
    if ( !v10 )
      break;
    if ( v10 == 92 || v10 == 47 )
      v3 = &v7[igi2_frame.v21];
    v7[igi2_frame.v21] = v10;
    v11 = pzFilename[v4 + 4];
    if ( !v11 )
      break;
    if ( v11 == 92 || v11 == 47 )
      v3 = &v7[igi2_frame.v22];
    v7[igi2_frame.v22] = v11;
    v12 = pzFilename[v4 + 5];
    if ( !v12 )
      break;
    if ( v12 == 92 || v12 == 47 )
      v3 = &v7[igi2_frame.v17];
    v7[igi2_frame.v17] = v12;
    v13 = pzFilename[v4 + 6];
    if ( !v13 )
      break;
    if ( v13 == 92 || v13 == 47 )
      v3 = &v7[igi2_frame.v18];
    v7[igi2_frame.v18] = v13;
    v14 = pzFilename[v4 + 7];
    if ( !v14 )
      break;
    if ( v14 == 92 || v14 == 47 )
      v3 = &v7[igi2_frame.v19];
    v4 += 8;
    v7[igi2_frame.v19] = v14;
    if ( v4 >= 0x80 )
      break;
    v2 = *(_DWORD *)igi2_frame.zFilename;
  }
  if ( v3 )
    *v3 = 0;
  else
    igi2_frame.zPath[0] = 0;
  if ( Resource_IsLoadedInternal(pzFilename, nullptr) || (result = (char *)File_Exists(pzFilename)) != nullptr )
  {
    Resource_DirList(igi2_frame.zPath, SoundSys_RemoveSampleCallback, nullptr);
    result = (char *)Resource_IsLoadedInternal(pzFilename, (struct Resource_s **)igi2_frame.zFilename);
    if ( result )
    {
      result = *(char **)(*(_DWORD *)igi2_frame.zFilename + 36);
      if ( result != (char *)3 && result != (char *)1 )
        Resource_Remove(*(struct Resource_s **)igi2_frame.zFilename);
    }
  }
  return result;
}

// source: f/1/soundsys.c:1682  [size]
char *__cdecl SoundSys_ScanDirectoryForSoundResourcesToAdd(char *pzDirectory)
{
  return (char *)File_DirList(pzDirectory, SoundSys_ScanDirectoryDirListRegisterCallback, nullptr);
}

// source: f/1/soundsys.c:1695  [size]
char *__cdecl SoundSys_ScanDirectoryForSoundResourcesToRemove(char *pzDirectory)
{
  return (char *)File_DirList(pzDirectory, SoundSys_ScanDirectoryDirListRemoveCallback, nullptr);
}

// source: f/1/soundsys.c:1708  [anchor-hash]
struct SoundSysChannelList_t *__cdecl SoundSys_CreateChannelList(int nChannels)
{
  struct SoundSysChannelList_t *result; // eax

  result = (struct SoundSysChannelList_t *)Mem_AllocFn(4 * nChannels + 4, 4);
  if ( result )
  {
    result->nChannels = nChannels;
    if ( nChannels > 0 )
      memset(result->auData, 0, 4 * nChannels);
  }
  return result;
}

// source: f/1/soundsys.c:1745  [anchor-callee]
void __cdecl SoundSys_DeleteChannelList(struct SoundSysChannelList_t *ptChannelList)
{
  int v1; // esi

  if ( ptChannelList )
  {
    v1 = *(_DWORD *)((unsigned int)(ptChannelList - 1) & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v1);
    memset(*(void **)(v1 + 8), 0xCDu, *(_DWORD *)(v1 + 16));
    free((void *)v1);
  }
}

// source: f/1/soundsys.c:1763  [anchor-callee]
struct QTask_s *__cdecl SoundSys_GetSoundDef(char *zFile)
{
  struct QTaskList_s *v1; // ecx
  int v2; // esi
  int v3; // edi
  __int16 v4; // ax
  struct SoundSysFindSoundDefContext_t tFindContext; // [esp+0h] [ebp-8h] BYREF

  v1 = SoundSys_ptSoundDefQTaskList;
  if ( !SoundSys_ptSoundDefQTaskList->nTask || !*zFile )
    return nullptr;
  tFindContext.pzSoundDef = zFile;
  tFindContext.ptSoundDef = nullptr;
  v2 = 0;
  if ( SoundSys_ptSoundDefQTaskList->nTask > 0 )
  {
    v3 = 8;
    do
    {
      v4 = SoundSys_eFindSoundDefQTaskEvent;
      if ( SoundSys_eFindSoundDefQTaskEvent == 512 )
      {
        v4 = QTask_NewQTaskEventFn(0, (char *)&g_zFileName.iActiveTABItem);
        v1 = SoundSys_ptSoundDefQTaskList;
        SoundSys_eFindSoundDefQTaskEvent = v4;
      }
      ((void (__cdecl *)(_DWORD, struct SoundSysFindSoundDefContext_t *))QTask_aatQTaskFinalEvent[v4][*(unsigned __int16 *)(*(int *)((char *)&v1->nTask + v3) + 36)].pfHandler)(
        *(int *)((char *)&v1->nTask + v3),
        &tFindContext);
      v1 = SoundSys_ptSoundDefQTaskList;
      ++v2;
      v3 += 4;
    }
    while ( v2 < SoundSys_ptSoundDefQTaskList->nTask );
  }
  return tFindContext.ptSoundDef;
}

// source: f/1/soundsys.c:1804  [anchor-callee]
struct QTask_s *__cdecl SoundSys_NewSoundFn(struct QTask_s *ptParent, char *pzSoundDef)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct SoundSysFindSoundDefContext_t tFindContext; };
    struct { char igi2_o1[8]; struct SoundSysCreateSoundContext_t tCreateContext; };
    char igi2_extent[16];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTaskList_s *v2; // ecx
  int v3; // esi
  int v4; // edi
  __int16 v5; // ax
  int eQTaskType; // eax
  struct QTask_s *v7; // eax
  struct QTask_s *ptHead; // esi
  struct QTask_s *v9; // edi
  int v10; // eax

  if ( SoundSys_isSoundDisabled )
    return nullptr;
  v2 = SoundSys_ptSoundDefQTaskList;
  if ( !SoundSys_ptSoundDefQTaskList->nTask )
    return nullptr;
  if ( !*pzSoundDef )
    return nullptr;
  igi2_frame.tFindContext.pzSoundDef = pzSoundDef;
  igi2_frame.tFindContext.ptSoundDef = nullptr;
  v3 = 0;
  if ( SoundSys_ptSoundDefQTaskList->nTask <= 0 )
    return nullptr;
  v4 = 8;
  do
  {
    v5 = SoundSys_eFindSoundDefQTaskEvent;
    if ( SoundSys_eFindSoundDefQTaskEvent == 512 )
    {
      v5 = QTask_NewQTaskEventFn(0, (char *)&g_zFileName.iActiveTABItem);
      v2 = SoundSys_ptSoundDefQTaskList;
      SoundSys_eFindSoundDefQTaskEvent = v5;
    }
    ((void (__cdecl *)(_DWORD, struct SoundSysFindSoundDefContext_t *))QTask_aatQTaskFinalEvent[v5][*(unsigned __int16 *)(*(int *)((char *)&v2->nTask + v4) + 36)].pfHandler)(
      *(int *)((char *)&v2->nTask + v4),
      &igi2_frame.tFindContext);
    v2 = SoundSys_ptSoundDefQTaskList;
    ++v3;
    v4 += 4;
  }
  while ( v3 < SoundSys_ptSoundDefQTaskList->nTask );
  if ( !igi2_frame.tFindContext.ptSoundDef )
    return nullptr;
  eQTaskType = igi2_frame.tFindContext.ptSoundDef->eQTaskType;
  igi2_frame.tCreateContext.ptSoundDef = igi2_frame.tFindContext.ptSoundDef;
  igi2_frame.tCreateContext.isDefinition = 0;
  v7 = QTask_NewFn(ptParent, eQTaskType, &igi2_frame.tCreateContext);
  ptHead = igi2_frame.tFindContext.ptSoundDef->tQTaskChildren.ptHead;
  v9 = v7;
  if ( ptHead->ptNext && ptHead )
  {
    do
    {
      v10 = ptHead->eQTaskType;
      igi2_frame.tCreateContext.ptSoundDef = ptHead;
      QTask_NewFn(v9, v10, &igi2_frame.tCreateContext);
      ptHead = ptHead->ptNext;
    }
    while ( ptHead && ptHead->ptNext );
  }
  return v9;
}

// source: f/1/soundsys.c:1885  [anchor-mhash]
float __cdecl SoundSys_GetSoundRadius(struct QTask_s *ptSoundQTask)
{
  __int16 v1; // ax
  void (__cdecl *pfHandler)(struct QTask_s *, struct SoundSysGetSoundRadiusContext_t *); // eax
  struct SoundSysGetSoundRadiusContext_t tContext; // [esp+0h] [ebp-4h] BYREF

  v1 = SoundSys_eGetSoundRadiusQTaskEvent;
  tContext.vRadius = -1.0;
  if ( SoundSys_eGetSoundRadiusQTaskEvent == 512 )
  {
    v1 = QTask_NewQTaskEventFn(0, (char *)&g_zFileName.aptSelectableTABItems[2]);
    SoundSys_eGetSoundRadiusQTaskEvent = v1;
  }
  pfHandler = (void (__cdecl *)(struct QTask_s *, struct SoundSysGetSoundRadiusContext_t *))QTask_aatQTaskFinalEvent[v1][ptSoundQTask->eQTaskType].pfHandler;
  if ( pfHandler )
    pfHandler(ptSoundQTask, &tContext);
  return tContext.vRadius * 4096.0;
}

// source: f/1/soundsys.c:1907  [anchor-callee]
int __cdecl SoundSys_GetSoundLength(struct QTask_s *ptSoundQTask)
{
  __int16 v1; // ax
  void (__cdecl *pfHandler)(struct QTask_s *, struct SoundSysGetSoundLengthContext_t *); // eax
  struct SoundSysGetSoundLengthContext_t tContext; // [esp+0h] [ebp-4h] BYREF

  v1 = SoundSys_eGetSoundLengthQTaskEvent;
  tContext.nLength = 0;
  if ( SoundSys_eGetSoundLengthQTaskEvent == 512 )
  {
    v1 = QTask_NewQTaskEventFn(0, (char *)&g_zFileName.aptSelectableItems[30]);
    SoundSys_eGetSoundLengthQTaskEvent = v1;
  }
  pfHandler = (void (__cdecl *)(struct QTask_s *, struct SoundSysGetSoundLengthContext_t *))QTask_aatQTaskFinalEvent[v1][ptSoundQTask->eQTaskType].pfHandler;
  if ( pfHandler )
    pfHandler(ptSoundQTask, &tContext);
  return tContext.nLength;
}

// source: f/1/soundsys.c:1929  [anchor-callee]
struct QTask_s *__cdecl SoundSys_SetSoundPosition(struct QTask_s *ptQTask, struct real64x3_t *ptPos)
{
  return ((struct QTask_s *(__cdecl *)(struct QTask_s *, struct real64x3_t *))QTask_aatQTaskFinalEvent[SoundSys_eSetPositionQTaskEvent][ptQTask->eQTaskType].pfHandler)(
           ptQTask,
           ptPos);
}

// source: f/1/soundsys.c:1947  [anchor-callee]
struct QTask_s *__cdecl SoundSys_SetSoundSector(struct QTask_s *ptQTask, struct QTask_s *ptSectorQTask)
{
  return ((struct QTask_s *(__cdecl *)(struct QTask_s *, struct QTask_s *))QTask_aatQTaskFinalEvent[SoundSys_eSetSectorQTaskEvent][ptQTask->eQTaskType].pfHandler)(
           ptQTask,
           ptSectorQTask);
}

// source: f/1/soundsys.c:1965  [anchor-callee]
struct QTask_s *__cdecl SoundSys_SetSoundVolumes(
        struct QTask_s *ptQTask,
        float vBaseVolume,
        float vRelativeVolume)
{
  struct SoundSysSetVolumeContext_t tContext; // [esp+0h] [ebp-8h] BYREF

  tContext.vBaseVolume = vBaseVolume;
  tContext.vRelativeVolume = vRelativeVolume;
  return ((struct QTask_s *(__cdecl *)(struct QTask_s *, struct SoundSysSetVolumeContext_t *))QTask_aatQTaskFinalEvent[SoundSys_eSetVolumeQTaskEvent][ptQTask->eQTaskType].pfHandler)(
           ptQTask,
           &tContext);
}

// source: f/1/soundsys.c:1987  [anchor-mhash]
struct QTask_s *__cdecl SoundSys_SetSoundPitch(struct QTask_s *ptQTask, float vPitch)
{
  return ((struct QTask_s *(__cdecl *)(struct QTask_s *, float *))QTask_aatQTaskFinalEvent[SoundSys_eSetPitchQTaskEvent][ptQTask->eQTaskType].pfHandler)(
           ptQTask,
           &vPitch);
}

// source: f/1/soundsys.c:2008  [anchor-mhash]
struct QTask_s *__cdecl SoundSys_SetSoundRelativeToMicrophone(
        struct QTask_s *ptQTask,
        char isRelativeStatus)
{
  struct SoundSysSetRelativeToMicrophoneContext_t tContext; // [esp+3h] [ebp-1h] BYREF

  tContext.isRelative = isRelativeStatus;
  return ((struct QTask_s *(__cdecl *)(struct QTask_s *, struct SoundSysSetRelativeToMicrophoneContext_t *))QTask_aatQTaskFinalEvent[SoundSys_eSetRelativeToMicrophoneQTaskEvent][ptQTask->eQTaskType].pfHandler)(
           ptQTask,
           &tContext);
}

// source: f/1/soundsys.c:2029  [size]
struct QTask_s *__cdecl SoundSys_RegisterSoundQTask(struct QTask_s *ptQTask)
{
  return (struct QTask_s *)QTaskList_Register(SoundSys_ptSoundQTaskList, (struct QTaskList_s *)ptQTask);
}

// source: f/1/soundsys.c:2044  [size]
void __cdecl SoundSys_RemoveSoundQTask(struct QTask_s *ptQTask)
{
  QTaskList_Remove(SoundSys_ptSoundQTaskList, ptQTask);
}

// source: f/1/soundsys.c:2071  [anchor-callee]
void __cdecl SoundSys_RequestSoundFn(struct SoundSysRequest_s *ptRequest)
{
  unsigned int v1; // ecx

  if ( !SoundSys_isSoundDisabled )
  {
    if ( !ptRequest->nSoundID )
    {
      v1 = SoundSys_nCurrentID;
      ptRequest->nSoundID = SoundSys_nCurrentID;
      SoundSys_nCurrentID = v1 + 1;
    }
    SoundSys_AddSoundToRequestlist(ptRequest->nSoundID, ptRequest->ptSample, ptRequest->bFlags, &ptRequest->tModify);
  }
}

// source: f/1/soundsys.c:2106  [anchor-callee]
char __cdecl SoundSys_SoundPlaying(struct SoundSysRequest_s *ptRequest)
{
  struct PlayingSound_s *v1; // eax
  struct Sound_s *ptSound; // eax
  struct h3DPOBJECT *h3DSample; // eax

  v1 = SoundSys_atPlaylist;
  if ( !SoundSys_atPlaylist )
    return 0;
  while ( v1->ptSample != ptRequest->ptSample || v1->nOwner != ptRequest->nSoundID )
  {
    v1 = v1->ptNext;
    if ( !v1 )
      return 0;
  }
  ptSound = v1->ptSound;
  if ( !ptSound )
    return 1;
  if ( Sound_isSSInitialized == false )
    return 0;
  if ( ptSound->hStream )
    return AIL_stream_status(ptSound->hStream) == 4;
  if ( ptSound->hSample )
    return AIL_sample_status(ptSound->hSample) == 4;
  h3DSample = ptSound->h3DSample;
  return h3DSample && AIL_3D_sample_status(h3DSample) == 4;
}

// source: f/1/soundsys.c:2140  [size]
void __cdecl SoundSys_SoundStop(struct SoundSysRequest_s *ptRequest)
{
  struct PlayingSound_s *v1; // edi
  struct Sound_s *ptSound; // esi
  struct PlayingSound_s *ptNext; // eax

  v1 = SoundSys_atPlaylist;
  if ( SoundSys_atPlaylist )
  {
    while ( v1->ptSample != ptRequest->ptSample || v1->nOwner != ptRequest->nSoundID )
    {
      v1 = v1->ptNext;
      if ( !v1 )
        return;
    }
    ptSound = v1->ptSound;
    if ( ptSound )
      Sound_FreeSound(ptSound);
    ptNext = v1->ptNext;
    if ( ptNext )
      ptNext->ptPrev = v1->ptPrev;
    if ( v1->ptPrev )
      v1->ptPrev->ptNext = v1->ptNext;
    if ( SoundSys_atPlaylist == v1 )
      SoundSys_atPlaylist = v1->ptNext;
    v1->ptNext = SoundSys_ptFirstFree;
    v1->ptPrev = nullptr;
    if ( SoundSys_ptFirstFree )
      SoundSys_ptFirstFree->ptPrev = v1;
    SoundSys_ptFirstFree = v1;
  }
}

// source: f/1/soundsys.c:2178  [anchor-hash]
float __cdecl SoundSys_CalculateRadius(struct SoundAttr_t *ptSourceAttr)
{
  double vFalloffEnd; // st7

  if ( ptSourceAttr->vVolume >= 0.0 )
  {
    if ( ptSourceAttr->vVolume > 1.0 )
      ptSourceAttr->vVolume = 1.0;
    return ptSourceAttr->vFalloffEnd;
  }
  else
  {
    vFalloffEnd = ptSourceAttr->vFalloffEnd;
    ptSourceAttr->vVolume = 0.0;
  }
  return vFalloffEnd;
}

// source: f/1/soundsys.c:2201  [anchor-mhash]
void __cdecl SoundSys_CalculateParameterFromEnvelope(
        float *pvParameter,
        float *avEnvelope,
        float vOffset)
{
  int v3; // ecx
  float *v4; // edi
  float vFromOffset; // [esp+0h] [ebp-14h]
  float vToOffset; // [esp+4h] [ebp-10h]

  if ( vOffset < 1.0 )
  {
    if ( vOffset > 0.0 )
    {
      v3 = (__int64)(vOffset * 10.0);
      v4 = &avEnvelope[v3 + 1];
      vFromOffset = (double)v3 * 0.10000000149011612;
      vToOffset = (double)(v3 + 1) * 0.10000000149011612;
      if ( vFromOffset == vOffset )
      {
        *pvParameter = avEnvelope[v3];
      }
      else if ( vToOffset == vOffset )
      {
        *pvParameter = *v4;
      }
      else
      {
        *pvParameter = (*v4 - avEnvelope[v3]) / (vToOffset - vFromOffset) * (vOffset - vFromOffset) + avEnvelope[v3];
      }
    }
    else
    {
      *pvParameter = *avEnvelope;
    }
  }
  else
  {
    *pvParameter = avEnvelope[10];
  }
}

// source: f/1/soundsys.c:2256  [anchor-callee]
void __cdecl SoundSys_ClearPlayList()
{
  struct PlayingSound_s *v0; // edi
  struct Sound_s *ptSound; // esi
  struct PlayingSound_s *ptNext; // ebx
  struct PlayingSound_s *v3; // eax

  v0 = SoundSys_atPlaylist;
  if ( SoundSys_atPlaylist )
  {
    do
    {
      ptSound = v0->ptSound;
      ptNext = v0->ptNext;
      if ( ptSound )
        Sound_FreeSound(ptSound);
      v3 = v0->ptNext;
      if ( v3 )
        v3->ptPrev = v0->ptPrev;
      if ( v0->ptPrev )
        v0->ptPrev->ptNext = v0->ptNext;
      if ( SoundSys_atPlaylist == v0 )
        SoundSys_atPlaylist = v0->ptNext;
      v0->ptNext = SoundSys_ptFirstFree;
      v0->ptPrev = nullptr;
      if ( SoundSys_ptFirstFree )
        SoundSys_ptFirstFree->ptPrev = v0;
      SoundSys_ptFirstFree = v0;
      v0 = ptNext;
    }
    while ( ptNext );
  }
}

// source: f/1/soundsys.c:2304  [size]
void __cdecl SoundSys_PlaySimpleSoundFn(
        char *pzSound,
        unsigned int bFlags,
        struct SoundAttr_t *ptAttr)
{
  struct QHashTable_s *v5; // edi
  unsigned int v6; // eax
  struct Sample_s *v7; // edx
  unsigned int v8; // ecx
  struct SoundModify_t tModify; // [esp+10h] [ebp-64h] BYREF

  if ( !SoundSys_isSoundDisabled )
  {
    v5 = Sound_ptSampleHashTable;
    v6 = Sound_ptSampleHashTable->tPrivate.pfHashFunction(Sound_ptSampleHashTable->tPrivate.nHashTableSize, pzSound);
    v7 = (struct Sample_s *)((int  (__cdecl *)(struct QHashTable_s *, unsigned int, const void *))Sound_ptSampleHashTable->tPrivate.pfFindElement)(v5, v6, (const void *)(pzSound));
    if ( ptAttr )
      qmemcpy(&tModify, ptAttr, 0x28u);
    else
      Sound_DefaultSoundModify(&tModify);
    v8 = SoundSys_nCurrentID++;
    SoundSys_AddSoundToRequestlist(v8, v7, bFlags | 1, &tModify);
  }
}

// source: f/1/soundsys.c:2364  [anchor-callee]
void __cdecl SoundSys_PlaySimpleSoundDefFn(
        char *pzSoundDef,
        unsigned int bFlags,
        struct SoundAttr_t *ptAttr)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct SoundSysFindSoundDefContext_t tFindContext; };
    struct { char igi2_o1[8]; struct SoundModify_t tModify; };
    char igi2_extent[104];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTaskList_s *v4; // ecx
  int v5; // edi
  int v6; // ebx
  __int16 v7; // ax
  unsigned __int16 eQTaskType; // cx
  struct QHashTable_s *v9; // edi
  unsigned int v10; // eax
  struct Sample_s *v11; // edx
  unsigned int v12; // ecx

  if ( !SoundSys_isSoundDisabled )
  {
    v4 = SoundSys_ptSoundDefQTaskList;
    v5 = 0;
    if ( SoundSys_ptSoundDefQTaskList->nTask )
    {
      if ( *pzSoundDef )
      {
        igi2_frame.tFindContext.pzSoundDef = pzSoundDef;
        igi2_frame.tFindContext.ptSoundDef = nullptr;
        if ( SoundSys_ptSoundDefQTaskList->nTask > 0 )
        {
          v6 = 8;
          do
          {
            v7 = SoundSys_eFindSoundDefQTaskEvent;
            if ( SoundSys_eFindSoundDefQTaskEvent == 512 )
            {
              v7 = QTask_NewQTaskEventFn(0, (char *)&g_zFileName.iActiveTABItem);
              v4 = SoundSys_ptSoundDefQTaskList;
              SoundSys_eFindSoundDefQTaskEvent = v7;
            }
            ((void (__cdecl *)(_DWORD, struct SoundSysFindSoundDefContext_t *))QTask_aatQTaskFinalEvent[v7][*(unsigned __int16 *)(*(int *)((char *)&v4->nTask + v6) + 36)].pfHandler)(
              *(int *)((char *)&v4->nTask + v6),
              &igi2_frame.tFindContext);
            v4 = SoundSys_ptSoundDefQTaskList;
            ++v5;
            v6 += 4;
          }
          while ( v5 < SoundSys_ptSoundDefQTaskList->nTask );
          if ( igi2_frame.tFindContext.ptSoundDef )
          {
            eQTaskType = igi2_frame.tFindContext.ptSoundDef->eQTaskType;
            if ( eQTaskType != SoundDefGroup_eCreateQTaskType
              && eQTaskType != SoundDefGraph_eCreateQTaskType
              && eQTaskType != SoundDefTriggerOnce_eCreateQTaskType )
            {
              v9 = Sound_ptSampleHashTable;
              v10 = Sound_ptSampleHashTable->tPrivate.pfHashFunction(
                      Sound_ptSampleHashTable->tPrivate.nHashTableSize,
                      (char *)&igi2_frame.tFindContext.ptSoundDef[7].tQTaskRefList.ptTail + 2);
              v11 = (struct Sample_s *)((int  (__cdecl *)(struct QHashTable_s *, unsigned int, const void *))Sound_ptSampleHashTable->tPrivate.pfFindElement)(v9, v10, (const void *)((char *)&igi2_frame.tFindContext.ptSoundDef[7].tQTaskRefList.ptTail + 2));
              if ( ptAttr )
                qmemcpy(&igi2_frame.tModify, ptAttr, 0x28u);
              else
                Sound_DefaultSoundModify(&igi2_frame.tModify);
              v12 = SoundSys_nCurrentID++;
              SoundSys_AddSoundToRequestlist(v12, v11, bFlags | 1, &igi2_frame.tModify);
            }
          }
        }
      }
    }
  }
}

// source: f/1/soundsys.c:2522  [size]
void __cdecl SoundSys_SetActiveWorld(struct World_s *ptWorld)
{
  ;
}

// source: f/1/soundsys.c:2539  [size]
struct QTaskList_s *__cdecl SoundSys_GetSoundQTaskList()
{
  return SoundSys_ptSoundQTaskList;
}

// source: f/1/soundsys.c:2554  [size]
void __cdecl SoundSys_DisableSound()
{
  SoundSys_isSoundDisabled = 1;
}

// source: f/1/soundsys.c:2567  [size]
void __cdecl SoundSys_EnableSound()
{
  if ( Sound_isSSInitialized )
    SoundSys_isSoundDisabled = 0;
}

// source: f/1/soundsys.c:2583  [size]
void __cdecl SoundSys_SetDontAddSoundToPlayListStatus(char isStatus)
{
  SoundSys_isDontAddSoundToPlayList = isStatus;
}

// source: f/1/soundsys.c:2596  [size]
char __cdecl SoundSys_GetDontAddSoundToPlayListStatus()
{
  return SoundSys_isDontAddSoundToPlayList;
}

// source: f/1/soundsys.c:2609  [size]
struct MusicInfo_t *__cdecl SoundSys_MusicPlay(struct MusicInfo_t *ptMusicInfo, int isRepeat)
{
  struct MusicInfo_t *result; // eax
  char zFilename[64]; // [esp+0h] [ebp-40h] BYREF

  if ( SoundSys_isMusicFileBased )
    return (struct MusicInfo_t *)sprintf(
                                   zFilename,
                                   (char *const)&g_zFileName.aptSelectableItems[28],
                                   SoundSys_pzMusicPath,
                                   ptMusicInfo->pzWavName);
  Sound_CDPlay(ptMusicInfo->nTrack, (enum bool)(char)isRepeat);
  return result;
}

// source: f/1/soundsys.c:2633  [size]
void __cdecl SoundSys_MusicPause()
{
  if ( !SoundSys_isMusicFileBased )
    Sound_CDPause();
}

// source: f/1/soundsys.c:2653  [size]
void __cdecl SoundSys_MusicUnPause()
{
  if ( !SoundSys_isMusicFileBased )
    Sound_CDUnPause();
}

// source: f/1/soundsys.c:2673  [size]
void __cdecl SoundSys_MusicStop()
{
  DWORD_PTR v0; // ecx
  DWORD_PTR dwParam2; // [esp+0h] [ebp-4h] BYREF

  dwParam2 = v0;
  if ( !SoundSys_isMusicFileBased )
  {
    dwParam2 = 0;
    mciSendCommandA(Sound_DeviceID, 0x808u, 0, (DWORD_PTR)&dwParam2);
    Sound_nCDPlayedTrack = -1;
  }
}

// source: f/1/soundsys.c:2693  [size]
void __cdecl SoundSys_MusicSetVolumeCurrent(float vVolume)
{
  if ( vVolume >= 0.0 )
  {
    if ( vVolume <= 1.0 )
      g_vPlayedVol = vVolume;
    else
      g_vPlayedVol = 1.0;
  }
  else
  {
    g_vPlayedVol = 0.0;
  }
  if ( !SoundSys_isMusicFileBased )
    Sound_SetVolumeCD(Soundsys_vMusicVolumeMaster, g_vPlayedVol);
}

// source: f/1/soundsys.c:2715  [size]
void __cdecl SoundSys_MusicSetVolumeMaster(float vVolume)
{
  if ( vVolume >= 0.0 )
  {
    if ( vVolume <= 1.0 )
      Soundsys_vMusicVolumeMaster = vVolume;
    else
      Soundsys_vMusicVolumeMaster = 1.0;
  }
  else
  {
    Soundsys_vMusicVolumeMaster = 0.0;
  }
  if ( !SoundSys_isMusicFileBased )
    Sound_SetVolumeCD(Soundsys_vMusicVolumeMaster, g_vPlayedVol);
}

// source: f/1/soundsys.c:2737  [size]
float __cdecl SoundSys_MusicGetVolumeCurrent()
{
  return g_vPlayedVol;
}

// source: f/1/soundsys.c:2750  [size]
float __cdecl SoundSys_MusicGetVolumeMaster()
{
  return Soundsys_vMusicVolumeMaster;
}

// source: f/1/soundsys.c:2765  [size]
char *__cdecl SoundSys_MusicSetPath(char *pzPath)
{
  SoundSys_pzMusicPath = pzPath;
  return pzPath;
}

// source: f/1/soundsys.c:2778  [size]
void __cdecl SoundSys_MusicSetType(int eType)
{
  SoundSys_isMusicFileBased = eType == 0;
}

// source: f/1/soundsys.c:2798  [size]
char *__cdecl SoundSys_InitRequest(
        struct SoundSysRequest_s *ptRequest,
        char *pzSample,
        unsigned int bFlags)
{
  struct QHashTable_s *v3; // edi
  unsigned int v4; // eax
  unsigned int v5; // eax

  if ( pzSample && *pzSample )
  {
    v3 = Sound_ptSampleHashTable;
    v4 = Sound_ptSampleHashTable->tPrivate.pfHashFunction(Sound_ptSampleHashTable->tPrivate.nHashTableSize, pzSample);
    ptRequest->ptSample = (struct Sample_s *)((int  (__cdecl *)(struct QHashTable_s *, unsigned int, const void *))Sound_ptSampleHashTable->tPrivate.pfFindElement)(v3, v4, (const void *)(pzSample));
  }
  else
  {
    ptRequest->ptSample = nullptr;
  }
  v5 = SoundSys_nCurrentID;
  ptRequest->nSoundID = SoundSys_nCurrentID;
  ptRequest->bFlags = bFlags;
  SoundSys_nCurrentID = v5 + 1;
  ptRequest->tModify.tAttr.vPan = 0.0;
  ptRequest->tModify.tAttr.vFalloffBegin = 0.0;
  LODWORD(ptRequest->tModify.tAttr.vFalloffEnd) = 0;
  ptRequest->tModify.tAttr.vOcclusion = 0.0;
  ptRequest->tModify.tPos.vX = 0.0;
  ptRequest->tModify.tPos.vY = 0.0;
  ptRequest->tModify.tPos.vZ = 0.0;
  ptRequest->tModify.tSpeed.vX = 0.0;
  ptRequest->tModify.tSpeed.vY = 0.0;
  ptRequest->tModify.tSpeed.vZ = 0.0;
  ptRequest->tModify.vPlayPos = 0.0;
  ptRequest->tModify.tAttr.vVolume = 1.0;
  ptRequest->tModify.tAttr.vPitch = 1.0;
  HIDWORD(ptRequest->tModify.tAttr.vFalloffEnd) = 1072693248;
  return (char *)1065353216;
}
