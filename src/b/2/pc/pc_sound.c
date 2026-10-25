/* b/2/pc/pc_sound.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: b/2/pc/pc_sound.c:307  [size]
unsigned int __cdecl mpgsize(unsigned __int8 *szBuffer, unsigned int len)
{
  unsigned __int16 v2; // cx
  unsigned int v3; // eax
  unsigned int v4; // ecx
  unsigned __int16 v5; // dx
  int v6; // eax
  int v7; // ecx
  int v8; // edx
  int v9; // eax

  HIBYTE(v2) = *szBuffer;
  LOBYTE(v2) = szBuffer[1];
  v3 = ((szBuffer[2] | (v2 << 8)) << 8) | szBuffer[3];
  v4 = v3 >> 17;
  v5 = v3;
  v6 = (v3 >> 19) & 3;
  v7 = -v4 & 3;
  v8 = v5 >> 12;
  if ( v6 == 2 )
  {
    v9 = 0;
  }
  else
  {
    if ( !v6 )
      v8 = 8;
    v9 = 1;
  }
  return (__int64)((double)len * 8000.0 / (double)(int)iFreqTable[1][32 * v9 + 1 + 16 * v7 + 16 * v9 + v8]);
}

// source: b/2/pc/pc_sound.c:375  [size]
void *__cdecl Sound_LinkIn(void *pxLink, void **pxFirst)
{
  *(_DWORD *)pxLink = *pxFirst;
  *((_DWORD *)pxLink + 1) = 0;
  if ( *pxFirst )
    *((_DWORD *)*pxFirst + 1) = pxLink;
  *pxFirst = pxLink;
  return pxLink;
}

// source: b/2/pc/pc_sound.c:403  [size]
void *__cdecl Sound_LinkOut(void *pxLink, void **pxFirst)
{
  _DWORD *v2; // ecx

  if ( *(_DWORD *)pxLink )
    *(_DWORD *)(*(_DWORD *)pxLink + 4) = *((_DWORD *)pxLink + 1);
  v2 = *((_DWORD **)pxLink + 1);
  if ( v2 )
    *v2 = *(_DWORD *)pxLink;
  if ( *pxFirst == pxLink )
  {
    pxLink = *(void **)pxLink;
    *pxFirst = pxLink;
  }
  return pxLink;
}

// source: b/2/pc/pc_sound.c:465  [size~]
struct Sound_s *__cdecl Sound_CreateSound(
        struct Sample_s *ptSample,
        int bFlags,
        struct SoundModify_t *ptModify)
{
  int v4; // ebp
  struct Sound_s *v6; // eax
  struct Sound_s *v7; // esi
  struct Sound_s *v8; // ecx
  struct Sound_s *ptPrev; // edx
  struct _STREAM *v10; // eax
  struct _SAMPLE *v12; // eax
  struct h3DPOBJECT *_3D_sample_handle; // eax
  struct _SAMPLE *sample_handle; // eax
  __int16 nBitRate; // cx
  unsigned int v16; // eax

  v4 = 0;
  if ( Sound_isSSInitialized )
  {
    if ( ptSample )
    {
      v6 = Sound_ptFirstFreeSound;
      v7 = Sound_ptFirstFreeSound;
      if ( Sound_ptFirstFreeSound )
      {
        v8 = Sound_ptFirstFreeSound;
        if ( Sound_ptFirstFreeSound->ptNext )
        {
          Sound_ptFirstFreeSound->ptNext->ptPrev = Sound_ptFirstFreeSound->ptPrev;
          v6 = Sound_ptFirstFreeSound;
        }
        ptPrev = v8->ptPrev;
        if ( ptPrev )
        {
          ptPrev->ptNext = v8->ptNext;
          v6 = Sound_ptFirstFreeSound;
        }
        if ( v6 == v8 )
          Sound_ptFirstFreeSound = v8->ptNext;
        v7->ptSample = ptSample;
        v7->bFlags = bFlags;
        v7->isMP3 = false;
        v7->hStream = nullptr;
        switch ( ptSample->tSoundFileHeader.eMethod )
        {
          case 0:
          case 4:
            v10 = (struct _STREAM *)AIL_open_stream(Sound_hMilesDigitalDriver, ptSample->zWaveFilename, 0);
            v7->hStream = v10;
            if ( !v10 )
              goto LABEL_42;
            if ( (v7->bFlags & 1) != 0 )
              return (struct Sound_s *)Sound_LinkIn(v7, (void **)&Sound_ptFirstTakenSound);
            AIL_set_stream_loop_count(v10, (v7->bFlags & 0x10) == 0);
            return (struct Sound_s *)Sound_LinkIn(v7, (void **)&Sound_ptFirstTakenSound);
          case 1:
          case 3:
            if ( (bFlags & 2) != 0 && ptSample->tSoundFileHeader.nStreams == 1 )
            {
              _3D_sample_handle = (struct h3DPOBJECT *)AIL_allocate_3D_sample_handle(Sound_hMiles3DProvider);
              v7->h3DSample = _3D_sample_handle;
              if ( _3D_sample_handle )
              {
                AIL_set_3D_sample_info(_3D_sample_handle, &ptSample->tSoundInfo);
                AIL_set_3D_sample_offset(
                  v7->h3DSample,
                  2 * (__int64)((double)ptSample->tSoundFileHeader.nFrequency * ptModify->vPlayPos));
                AIL_set_3D_sample_loop_count(v7->h3DSample, ((v7->bFlags >> 4) & 1) == 0);
                if ( ptModify->tAttr.vOcclusion != 0.0 )
                {
                  AIL_set_3D_sample_occlusion(v7->h3DSample, LODWORD(ptModify->tAttr.vOcclusion));
                  return (struct Sound_s *)Sound_LinkIn(v7, (void **)&Sound_ptFirstTakenSound);
                }
                return (struct Sound_s *)Sound_LinkIn(v7, (void **)&Sound_ptFirstTakenSound);
              }
              goto LABEL_42;
            }
            sample_handle = (struct _SAMPLE *)AIL_allocate_sample_handle(Sound_hMilesDigitalDriver);
            v7->hSample = sample_handle;
            if ( !sample_handle )
            {
LABEL_42:
              Sound_LinkIn(v7, (void **)&Sound_ptFirstFreeSound);
              return nullptr;
            }
            nBitRate = ptSample->tSoundFileHeader.nBitRate;
            if ( ptSample->tSoundFileHeader.eMethod == 1 )
            {
              if ( nBitRate == 16 )
              {
                if ( ptSample->tSoundFileHeader.nStreams == 1 )
                {
                  v4 = 1;
                  goto LABEL_39;
                }
                if ( ptSample->tSoundFileHeader.nStreams == 2 )
                {
                  v4 = 3;
                  goto LABEL_39;
                }
              }
              if ( nBitRate == 8 )
              {
                if ( ptSample->tSoundFileHeader.nStreams == 1 )
                  goto LABEL_39;
                v4 = 2;
                if ( ptSample->tSoundFileHeader.nStreams == 2 )
                  goto LABEL_39;
              }
LABEL_33:
              LDebug_Error("Unsupported sound format");
              abort();
            }
            if ( nBitRate != 16 )
              goto LABEL_33;
            if ( ptSample->tSoundFileHeader.nStreams == 1 )
            {
              v4 = 5;
            }
            else
            {
              if ( ptSample->tSoundFileHeader.nStreams != 2 )
                goto LABEL_33;
              v4 = 7;
            }
LABEL_39:
            AIL_init_sample(sample_handle);
            AIL_set_sample_address(
              v7->hSample,
              ptSample->pnWaveData,
              (ptSample->tSoundFileHeader.nStreams
             * ptSample->tSoundFileHeader.nBitRate
             * ptSample->tSoundFileHeader.nSamples) >> 3);
            AIL_set_sample_type(v7->hSample, v4, 0);
            AIL_set_sample_playback_rate(v7->hSample, ptSample->tSoundFileHeader.nFrequency);
            AIL_set_sample_ms_position(v7->hSample, (__int64)(ptModify->vPlayPos * 1000.0));
            v16 = v7->bFlags;
            if ( (v16 & 1) == 0 )
              AIL_set_sample_loop_count(v7->hSample, ((v16 >> 4) & 1) == 0);
            return (struct Sound_s *)Sound_LinkIn(v7, (void **)&Sound_ptFirstTakenSound);
          case 5:
            v12 = (struct _SAMPLE *)AIL_allocate_sample_handle(Sound_hMilesDigitalDriver);
            v7->hSample = v12;
            if ( !v12 )
              goto LABEL_42;
            AIL_init_sample(v12);
            AIL_set_named_sample_file(
              v7->hSample,
              v7->ptSample->zWaveFilename,
              v7->ptSample->pnWaveData,
              v7->ptSample->tSoundFileHeader.nSamples,
              0);
            AIL_set_sample_ms_position(v7->hSample, (__int64)(ptModify->vPlayPos * 1000.0));
            if ( (v7->bFlags & 1) == 0 )
              AIL_set_sample_loop_count(v7->hSample, (v7->bFlags & 0x10) == 0);
            v7->isMP3 = true;
            return (struct Sound_s *)Sound_LinkIn(v7, (void **)&Sound_ptFirstTakenSound);
          default:
            v7->ptNext = Sound_ptFirstFreeSound;
            v7->ptPrev = nullptr;
            if ( Sound_ptFirstFreeSound )
              Sound_ptFirstFreeSound->ptPrev = v7;
            Sound_ptFirstFreeSound = v7;
            return nullptr;
        }
      }
    }
  }
  return nullptr;
}

// source: b/2/pc/pc_sound.c:682  [size]
void __cdecl Sound_SetDeviceVolume(
        struct HMIXER__ *hMixer,
        struct tagMIXERLINEA *psLine,
        struct tagMIXERCONTROLA *psControl,
        unsigned int nLeft,
        unsigned int nRight)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct tMIXERCONTROLDETAILS_UNSIGNED anValues[2]; };
    struct { char igi2_o1[8]; struct tMIXERCONTROLDETAILS sDetails; };
    char igi2_extent[32];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  DWORD dwControlID; // eax
  DWORD cMultipleItems; // ecx
  DWORD cChannels; // eax

  dwControlID = psControl->dwControlID;
  cMultipleItems = psControl->cMultipleItems;
  igi2_frame.sDetails.dwControlID = dwControlID;
  cChannels = psLine->cChannels;
  igi2_frame.sDetails.cbStruct = 24;
  igi2_frame.sDetails.cChannels = cChannels;
  igi2_frame.sDetails.cMultipleItems = cMultipleItems;
  igi2_frame.sDetails.cbDetails = 4;
  igi2_frame.sDetails.paDetails = igi2_frame.anValues;
  if ( cChannels )
    igi2_frame.anValues[0].dwValue = nLeft;
  if ( cChannels > 1 )
    igi2_frame.anValues[1].dwValue = nRight;
  mixerSetControlDetails((HMIXEROBJ)hMixer, &igi2_frame.sDetails, 0x80000000);
}

// source: b/2/pc/pc_sound.c:793  [size]
struct Sample_s *__cdecl Sound_GetSample(char *pzSample)
{
  struct QHashTable_s *v1; // esi
  int v2; // eax

  v1 = Sound_ptSampleHashTable;
  v2 = Sound_ptSampleHashTable->tPrivate.pfHashFunction(Sound_ptSampleHashTable->tPrivate.nHashTableSize, pzSample);
  return ((struct Sample_s * (__cdecl *)(struct QHashTable_s *, unsigned int, const void *))Sound_ptSampleHashTable->tPrivate.pfFindElement)(v1, v2, (const void *)(pzSample));
}

// source: b/2/pc/pc_sound.c:806  [size]
enum bool __cdecl Sound_IsInitialized()
{
  return Sound_isSSInitialized;
}

// source: b/2/pc/pc_sound.c:819  [size]
int __cdecl Sound_SetFrequency(int nFrequency)
{
  Sound_nFrequency = nFrequency;
  return nFrequency;
}

// source: b/2/pc/pc_sound.c:833  [size]
void __cdecl Sound_StartStream(char *pzFilename, int isRepeat)
{
  ;
}

// source: b/2/pc/pc_sound.c:845  [size]
void __cdecl Sound_StopStream()
{
  ;
}

// source: b/2/pc/pc_sound.c:857  [size]
void __cdecl Sound_MaintainStream()
{
  ;
}

// source: b/2/pc/pc_sound.c:875  [size]
void __cdecl Sound_SetVolumeCD(float vMasterVol, float vPlayedVol)
{
  int v2; // edi
  unsigned int *p_nCDVolumeR; // esi
  struct HMIXER__ *v4; // eax

  Sound_vCDMasterVolume = vMasterVol;
  v2 = 0;
  Sound_vCDPlayedVolume = vPlayedVol;
  if ( Sound_nMixerDevices > 0 )
  {
    p_nCDVolumeR = &Sound_atMixerDevices[0].nCDVolumeR;
    do
    {
      v4 = (struct HMIXER__ *)*(p_nCDVolumeR - 216);
      if ( v4 && *(p_nCDVolumeR - 203) )
      {
        if ( *(p_nCDVolumeR - 119) )
          Sound_SetDeviceVolume(
            v4,
            (struct tagMIXERLINEA *)(p_nCDVolumeR - 119),
            (struct tagMIXERCONTROLA *)(p_nCDVolumeR - 40),
            (__int64)((double)*(p_nCDVolumeR - 1) * (vMasterVol * vPlayedVol)),
            (__int64)((double)*p_nCDVolumeR * (vMasterVol * vPlayedVol)));
      }
      ++v2;
      p_nCDVolumeR += 217;
    }
    while ( v2 < Sound_nMixerDevices );
  }
}

// source: b/2/pc/pc_sound.c:928  [size]
void __cdecl Sound_SetMasterVolumeSFX(float vVol)
{
  Sound_vSSMasterVolume = vVol;
}

// source: b/2/pc/pc_sound.c:939  [size]
float __cdecl Sound_GetMasterVolumeCD()
{
  return Sound_vCDMasterVolume;
}

// source: b/2/pc/pc_sound.c:954  [size]
float __cdecl Sound_GetPlayedVolumeCD()
{
  return Sound_vCDPlayedVolume;
}

// source: b/2/pc/pc_sound.c:969  [size]
float __cdecl Sound_GetMasterVolumeSFX()
{
  return Sound_vSSMasterVolume;
}

// source: b/2/pc/pc_sound.c:985  [size]
void __cdecl Sound_StopAll()
{
  DWORD_PTR dwParam2; // [esp+0h] [ebp-4h] BYREF

  dwParam2 = 0;
  mciSendCommandA(Sound_DeviceID, 0x808u, 0, (DWORD_PTR)&dwParam2);
  Sound_nCDPlayedTrack = -1;
}

// source: b/2/pc/pc_sound.c:1009  [size]
void __cdecl Sound_CDPlay(int nTrackNum, enum bool isRepeat)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct tagMCI_PLAY_PARMS mciPlayParms; };
    struct { char igi2_o1[12]; struct tagMCI_SET_PARMS mciSetParms; };
    struct { char igi2_o2[24]; struct tagMCI_STATUS_PARMS mciStatusParms; };
    char igi2_extent[40];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  DWORD_PTR dwReturn; // edi

  if ( Sound_isCDInitialized )
  {
    igi2_frame.mciStatusParms.dwItem = 5;
    if ( !mciSendCommandA(Sound_DeviceID, 0x814u, 0x100u, (DWORD_PTR)&igi2_frame.mciStatusParms) )
    {
      if ( igi2_frame.mciStatusParms.dwReturn )
      {
        igi2_frame.mciStatusParms.dwItem = 3;
        if ( !mciSendCommandA(Sound_DeviceID, 0x814u, 0x100u, (DWORD_PTR)&igi2_frame.mciStatusParms)
          && nTrackNum >= 0
          && nTrackNum <= (int)igi2_frame.mciStatusParms.dwReturn )
        {
          igi2_frame.mciStatusParms.dwTrack = nTrackNum;
          igi2_frame.mciStatusParms.dwItem = 16385;
          if ( !mciSendCommandA(Sound_DeviceID, 0x814u, 0x110u, (DWORD_PTR)&igi2_frame.mciStatusParms)
            && igi2_frame.mciStatusParms.dwReturn != 1089 )
          {
            igi2_frame.mciSetParms.dwTimeFormat = 0;
            if ( !mciSendCommandA(Sound_DeviceID, 0x80Du, 0x400u, (DWORD_PTR)&igi2_frame.mciSetParms) )
            {
              igi2_frame.mciStatusParms.dwTrack = nTrackNum;
              igi2_frame.mciStatusParms.dwItem = 1;
              if ( !mciSendCommandA(Sound_DeviceID, 0x814u, 0x110u, (DWORD_PTR)&igi2_frame.mciStatusParms) )
              {
                dwReturn = igi2_frame.mciStatusParms.dwReturn;
                igi2_frame.mciStatusParms.dwItem = 2;
                if ( !mciSendCommandA(Sound_DeviceID, 0x814u, 0x110u, (DWORD_PTR)&igi2_frame.mciStatusParms) )
                {
                  igi2_frame.mciPlayParms.dwFrom = igi2_frame.mciStatusParms.dwReturn;
                  igi2_frame.mciPlayParms.dwCallback = isRepeat != false ? (DWORD_PTR)AppContext_tAppContext.hWnd : 0;
                  igi2_frame.mciPlayParms.dwTo = igi2_frame.mciStatusParms.dwReturn + dwReturn;
                  if ( !mciSendCommandA(Sound_DeviceID, 0x806u, (isRepeat != false) | 0xC, (DWORD_PTR)&igi2_frame.mciPlayParms) )
                  {
                    Sound_nCDPlayedTrack = nTrackNum;
                    Sound_isCDPaused = false;
                    Sound_isCDRepeat = isRepeat;
                  }
                }
              }
            }
          }
        }
      }
    }
  }
}

// source: b/2/pc/pc_sound.c:1099  [size]
void __cdecl Sound_CDPause()
{
  #pragma pack(push, 1)
  union
  {
    struct { struct tagMCI_GENERIC_PARMS mciGenParms; };
    struct { char igi2_o1[4]; struct tagMCI_SET_PARMS mciSetParms; };
    struct { char igi2_o2[16]; struct tagMCI_STATUS_PARMS mciStatusParms; };
    char igi2_extent[32];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)

  igi2_frame.mciGenParms.dwCallback = 0;
  igi2_frame.mciSetParms.dwTimeFormat = 0;
  if ( !mciSendCommandA(Sound_DeviceID, 0x80Du, 0x400u, (DWORD_PTR)&igi2_frame.mciSetParms) )
  {
    igi2_frame.mciStatusParms.dwItem = 2;
    if ( !mciSendCommandA(Sound_DeviceID, 0x814u, 0x100u, (DWORD_PTR)&igi2_frame.mciStatusParms) )
    {
      Sound_nCDPausedPosition = igi2_frame.mciStatusParms.dwReturn;
      if ( !mciSendCommandA(Sound_DeviceID, 0x809u, 0, (DWORD_PTR)&igi2_frame.mciGenParms) )
        Sound_isCDPaused = true;
    }
  }
}

// source: b/2/pc/pc_sound.c:1138  [size]
void __cdecl Sound_CDUnPause()
{
  #pragma pack(push, 1)
  union
  {
    struct { struct tagMCI_PLAY_PARMS mciPlayParms; };
    struct { char igi2_o1[12]; struct tagMCI_SET_PARMS mciSetParms; };
    struct { char igi2_o2[24]; struct tagMCI_STATUS_PARMS mciStatusParms; };
    char igi2_extent[40];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  DWORD_PTR dwReturn; // edi

  if ( Sound_isCDPaused )
  {
    if ( Sound_nCDPlayedTrack != -1 )
    {
      igi2_frame.mciSetParms.dwTimeFormat = 0;
      if ( !mciSendCommandA(Sound_DeviceID, 0x80Du, 0x400u, (DWORD_PTR)&igi2_frame.mciSetParms) )
      {
        igi2_frame.mciStatusParms.dwTrack = Sound_nCDPlayedTrack;
        igi2_frame.mciStatusParms.dwItem = 1;
        if ( !mciSendCommandA(Sound_DeviceID, 0x814u, 0x110u, (DWORD_PTR)&igi2_frame.mciStatusParms) )
        {
          dwReturn = igi2_frame.mciStatusParms.dwReturn;
          igi2_frame.mciStatusParms.dwItem = 2;
          if ( !mciSendCommandA(Sound_DeviceID, 0x814u, 0x110u, (DWORD_PTR)&igi2_frame.mciStatusParms) )
          {
            igi2_frame.mciPlayParms.dwFrom = Sound_nCDPausedPosition;
            igi2_frame.mciPlayParms.dwTo = dwReturn + igi2_frame.mciStatusParms.dwReturn;
            igi2_frame.mciPlayParms.dwCallback = Sound_isCDRepeat != false ? (DWORD_PTR)AppContext_tAppContext.hWnd : 0;
            if ( !mciSendCommandA(
                    Sound_DeviceID,
                    0x806u,
                    (Sound_isCDRepeat != false) | 0xC,
                    (DWORD_PTR)&igi2_frame.mciPlayParms) )
              Sound_isCDPaused = false;
          }
        }
      }
    }
  }
}

// source: b/2/pc/pc_sound.c:1193  [size]
void __cdecl Sound_CDStop()
{
  struct tagMCI_GENERIC_PARMS mciGenParms; // [esp+0h] [ebp-4h] BYREF

  mciGenParms.dwCallback = 0;
  mciSendCommandA(Sound_DeviceID, 0x808u, 0, (DWORD_PTR)&mciGenParms);
  Sound_nCDPlayedTrack = -1;
}

// source: b/2/pc/pc_sound.c:1216  [size]
int __cdecl Sound_CDGetTrackStart(int nCDTrack)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct tagMCI_SET_PARMS mciSetParms; };
    struct { char igi2_o1[12]; struct tagMCI_STATUS_PARMS mciStatusParms; };
    char igi2_extent[28];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)

  if ( nCDTrack < 0 )
    return -1;
  igi2_frame.mciSetParms.dwTimeFormat = 0;
  if ( mciSendCommandA(Sound_DeviceID, 0x80Du, 0x400u, (DWORD_PTR)&igi2_frame.mciSetParms) )
    return -1;
  igi2_frame.mciStatusParms.dwTrack = nCDTrack;
  igi2_frame.mciStatusParms.dwItem = 2;
  if ( mciSendCommandA(Sound_DeviceID, 0x814u, 0x110u, (DWORD_PTR)&igi2_frame.mciStatusParms) )
    return -1;
  else
    return igi2_frame.mciStatusParms.dwReturn;
}

// source: b/2/pc/pc_sound.c:1254  [size]
int __cdecl Sound_CDGetCurrentPos()
{
  #pragma pack(push, 1)
  union
  {
    struct { struct tagMCI_SET_PARMS mciSetParms; };
    struct { char igi2_o1[12]; struct tagMCI_STATUS_PARMS mciStatusParms; };
    char igi2_extent[28];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)

  if ( Sound_nCDPlayedTrack == -1 )
    return -1;
  igi2_frame.mciSetParms.dwTimeFormat = 0;
  if ( mciSendCommandA(Sound_DeviceID, 0x80Du, 0x400u, (DWORD_PTR)&igi2_frame.mciSetParms) )
    return -1;
  igi2_frame.mciStatusParms.dwItem = 2;
  if ( mciSendCommandA(Sound_DeviceID, 0x814u, 0x100u, (DWORD_PTR)&igi2_frame.mciStatusParms) )
    return -1;
  else
    return igi2_frame.mciStatusParms.dwReturn;
}

// source: b/2/pc/pc_sound.c:1289  [size]
int __cdecl Sound_CDGetCurrentTrack()
{
  return Sound_nCDPlayedTrack;
}

// source: b/2/pc/pc_sound.c:1305  [size~]
char *__cdecl Sound_RegisterSample(
        char *pzFilename,
        unsigned int nSize,
        enum bool isInResource)
{
  #pragma pack(push, 1)
  union
  {
    struct { unsigned int pnSize; };
    struct { char igi2_o1[4]; int v20; };
    struct { char igi2_o2[8]; _DWORD v21[5]; };
    struct { char igi2_o3[28]; char pzSamplename[32]; };
    char igi2_extent[60];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  char *result; // eax
  unsigned int v5; // esi
  int matched; // eax
  struct QHashTable_s *v7; // edi
  unsigned int v8; // eax
  char **v9; // ebp
  unsigned int v10; // kr00_4
  char *v11; // eax
  char *v12; // eax
  char *v13; // edx
  char *v14; // ecx
  char *v15; // edx
  unsigned int v16; // kr08_4
  struct QHashTable_s *v17; // esi
  unsigned int v18; // eax

  result = (char *)Sound_isSSInitialized;
  v5 = 0;
  igi2_frame.pnSize = 0;
  if ( Sound_isSSInitialized )
  {
    matched = Wildcard_MatchSimple("*.MP3", nullptr, nullptr, (void *)pzFilename, 1);
    igi2_frame.v20 = matched;
    if ( isInResource )
    {
      if ( matched )
      {
        igi2_frame.pnSize = (unsigned int)Resource_Load(pzFilename, &igi2_frame.pnSize);
      }
      else
      {
        igi2_frame.pnSize = (unsigned int)Resource_Load(pzFilename, &igi2_frame.pnSize);
        qmemcpy(igi2_frame.v21, (void *)igi2_frame.pnSize, sizeof(igi2_frame.v21));
        if ( igi2_frame.v21[0] != 1179864137 || !LOWORD(igi2_frame.v21[1]) || SLOWORD(igi2_frame.v21[1]) == 2 )
        {
LABEL_11:
          Resource_Unload(pzFilename);
          return result;
        }
      }
      v5 = igi2_frame.pnSize;
    }
    Sound_CropFilenameToSamplename(igi2_frame.pzSamplename, pzFilename);
    v7 = Sound_ptSampleHashTable;
    v8 = Sound_ptSampleHashTable->tPrivate.pfHashFunction(
           Sound_ptSampleHashTable->tPrivate.nHashTableSize,
           igi2_frame.pzSamplename);
    result = (char *)((int  (__cdecl *)(struct QHashTable_s *, unsigned int, const void *))v7->tPrivate.pfFindElement)(v7, v8, (const void *)(igi2_frame.pzSamplename));
    if ( result )
    {
      if ( !v5 )
        return result;
      goto LABEL_11;
    }
    v9 = (char **)Mem_AllocFn(64, 4);
    memset(v9, 0, 0x40u);
    if ( igi2_frame.v20 )
    {
      v9[4] = (char *)nSize;
      v9[6] = (char *)v5;
      *((_WORD *)v9 + 2) = (isInResource != false) + 4;
      v10 = strlen(File_GetRealFilename(pzFilename));
      v9[5] = (char *)Mem_AllocFn(v10 + 1, 4);
      strcpy(v9[5], File_GetRealFilename(pzFilename));
    }
    else
    {
      if ( isInResource )
      {
        qmemcpy(v9, igi2_frame.v21, 0x14u);
        switch ( *((_WORD *)v9 + 2) )
        {
          case 0:
          case 2:
            v11 = (char *)Mem_AllocFn(strlen(pzFilename) + 1, 4);
            v9[5] = v11;
            if ( v11 )
            {
              strcpy(v11, pzFilename);
              goto LABEL_21;
            }
            Mem_DeAllocFn(v9);
            return result;
          case 1:
            v9[6] = (char *)(igi2_frame.pnSize + 20);
            goto LABEL_21;
          case 3:
            Mem_DeAllocFn(v9);
            Resource_Unload(pzFilename);
            return result;
          default:
LABEL_21:
            v12 = v9[4];
            v13 = v9[6];
            v9[9] = (char *)(2 * (_DWORD)v12);
            v14 = (char *)*((__int16 *)v9 + 4);
            v9[8] = v13;
            v15 = v9[3];
            v9[7] = (char *)1;
            v9[10] = v15;
            v9[11] = (char *)16;
            v9[12] = v14;
            v9[13] = v12;
            v9[14] = nullptr;
            goto LABEL_23;
        }
      }
      *((_WORD *)v9 + 2) = 0;
      v9[4] = (char *)nSize;
      v9[6] = (char *)v5;
      v16 = strlen(File_GetRealFilename(pzFilename));
      v9[5] = (char *)Mem_AllocFn(v16 + 1, 4);
      strcpy(v9[5], File_GetRealFilename(pzFilename));
    }
LABEL_23:
    v17 = Sound_ptSampleHashTable;
    v18 = Sound_ptSampleHashTable->tPrivate.pfHashFunction(
            Sound_ptSampleHashTable->tPrivate.nHashTableSize,
            igi2_frame.pzSamplename);
    return (char *)((int  (__cdecl *)(struct QHashTable_s *, unsigned int, const void *, const void *))Sound_ptSampleHashTable->tPrivate.pfCreateElement)(v17, v18, (const void *)(igi2_frame.pzSamplename), (const void *)(v9));
  }
  return result;
}

// source: b/2/pc/pc_sound.c:1494  [size]
char *__cdecl Sound_RemoveSample(char *pzFilename)
{
  char *result; // eax
  struct QHashTable_s *v3; // esi
  unsigned int v4; // eax
  char *v5; // ebp
  int v6; // eax
  int v7; // esi
  struct QHashTable_s *v8; // esi
  unsigned int v9; // eax
  int v10; // esi
  char zName[32]; // [esp+4h] [ebp-20h] BYREF

  result = (char *)Sound_isSSInitialized;
  if ( Sound_isSSInitialized )
  {
    Sound_CropFilenameToSamplename(zName, pzFilename);
    v3 = Sound_ptSampleHashTable;
    v4 = Sound_ptSampleHashTable->tPrivate.pfHashFunction(Sound_ptSampleHashTable->tPrivate.nHashTableSize, zName);
    result = (char *)((int  (__cdecl *)(struct QHashTable_s *, unsigned int, const void *))Sound_ptSampleHashTable->tPrivate.pfFindElement)(v3, v4, (const void *)(zName));
    v5 = result;
    if ( result )
    {
      v6 = *((_DWORD *)result + 5);
      if ( v6 )
      {
        v7 = *(_DWORD *)((v6 - 4) & 0xFFFFFFFC);
        --Mem_nCurrentAllocations;
        Node_Remove((_DWORD **)v7);
        memset(*(void **)(v7 + 8), 0xCDu, *(_DWORD *)(v7 + 16));
        free((void *)v7);
        *((_DWORD *)v5 + 5) = 0;
      }
      v8 = Sound_ptSampleHashTable;
      v9 = Sound_ptSampleHashTable->tPrivate.pfHashFunction(Sound_ptSampleHashTable->tPrivate.nHashTableSize, zName);
      ((void  (__cdecl *)(struct QHashTable_s *, unsigned int, const void *))Sound_ptSampleHashTable->tPrivate.pfDeleteElement)(v8, v9, (const void *)(zName));
      v10 = *(_DWORD *)((unsigned int)(v5 - 4) & 0xFFFFFFFC);
      --Mem_nCurrentAllocations;
      Node_Remove((_DWORD **)v10);
      memset(*(void **)(v10 + 8), 0xCDu, *(_DWORD *)(v10 + 16));
      free((void *)v10);
      result = (char *)Resource_IsLoadedInternal(pzFilename, nullptr);
      if ( result )
        Resource_Unload(pzFilename);
    }
  }
  return result;
}

// source: b/2/pc/pc_sound.c:1542  [size]
void __cdecl Sound_FreeSound(struct Sound_s *ptSound)
{
  struct Sound_s *ptPrev; // eax

  if ( Sound_isSSInitialized )
  {
    if ( ptSound->hStream )
    {
      AIL_close_stream(ptSound->hStream);
      ptSound->hStream = nullptr;
    }
    else if ( ptSound->hSample )
    {
      AIL_release_sample_handle(ptSound->hSample);
      ptSound->hSample = nullptr;
    }
    else if ( ptSound->h3DSample )
    {
      AIL_end_3D_sample(ptSound->h3DSample);
      AIL_release_3D_sample_handle(ptSound->h3DSample);
      ptSound->h3DSample = nullptr;
    }
    if ( ptSound->ptNext )
      ptSound->ptNext->ptPrev = ptSound->ptPrev;
    ptPrev = ptSound->ptPrev;
    if ( ptPrev )
      ptPrev->ptNext = ptSound->ptNext;
    if ( Sound_ptFirstTakenSound == ptSound )
      Sound_ptFirstTakenSound = ptSound->ptNext;
    ptSound->ptNext = Sound_ptFirstFreeSound;
    ptSound->ptPrev = nullptr;
    if ( Sound_ptFirstFreeSound )
      Sound_ptFirstFreeSound->ptPrev = ptSound;
    Sound_ptFirstFreeSound = ptSound;
  }
}

// source: b/2/pc/pc_sound.c:1632  [size]
struct Sound_s *__cdecl Sound_PlaySample(
        struct Sample_s *ptSample,
        int bFlags,
        struct SoundModify_t *ptModify)
{
  struct SoundModify_t *p_tDefaultModify; // edi
  struct Sound_s *Sound; // esi
  __int16 eMethod; // ax
  struct SoundModify_t tDefaultModify; // [esp+8h] [ebp-64h] BYREF

  p_tDefaultModify = ptModify;
  if ( Sound_isSSInitialized == false )
    return nullptr;
  if ( !ptModify )
  {
    Sound_DefaultSoundModify(&tDefaultModify);
    p_tDefaultModify = &tDefaultModify;
  }
  Sound = Sound_CreateSound(ptSample, bFlags, p_tDefaultModify);
  if ( !Sound )
    return nullptr;
  Sound_ModifySound(Sound, p_tDefaultModify);
  eMethod = Sound->ptSample->tSoundFileHeader.eMethod;
  if ( eMethod == 4 || !eMethod )
  {
    if ( Sound->hStream )
      AIL_start_stream(Sound->hStream);
  }
  else
  {
    if ( Sound->h3DSample )
    {
      AIL_resume_3D_sample(Sound->h3DSample);
      return Sound;
    }
    if ( Sound->hSample )
    {
      AIL_resume_sample(Sound->hSample);
      return Sound;
    }
  }
  return Sound;
}

// source: b/2/pc/pc_sound.c:1693  [size]
float __cdecl Sound_GetSampleDuration(struct Sample_s *ptSample)
{
  if ( ptSample )
  {
    if ( ptSample->tSoundFileHeader.eMethod == 5 )
      return (double)mpgsize(ptSample->pnWaveData, ptSample->tSoundFileHeader.nSamples) * 0.0010000000474974513;
    else
      return (double)ptSample->tSoundFileHeader.nSamples / (double)ptSample->tSoundFileHeader.nFrequency;
  }
  else
  {
    return 0.0;
  }
}

// source: b/2/pc/pc_sound.c:1724  [size]
struct real32x9_t *__cdecl Sound_SoundUpdateMicrophone(
        struct real32x9_t *ptMOrientation,
        struct real64x3_t *ptPos,
        struct real64x3_t *ptSpeed)
{
  qmemcpy(&Sound_tMMicrophoneOrientation, ptMOrientation, sizeof(Sound_tMMicrophoneOrientation));
  qmemcpy(&Sound_tMicrophonePos, ptPos, sizeof(Sound_tMicrophonePos));
  qmemcpy(&Sound_tMicrophoneSpeed, ptSpeed, sizeof(Sound_tMicrophoneSpeed));
  return ptMOrientation;
}

// source: b/2/pc/pc_sound.c:1744  [size]
struct real32x9_t *__cdecl Sound_SoundGetCurrentMicrophone(
        struct real32x9_t *ptMOrientation,
        struct real64x3_t *ptPos,
        struct real64x3_t *ptSpeed)
{
  qmemcpy(ptMOrientation, &Sound_tMMicrophoneOrientation, sizeof(struct real32x9_t));
  qmemcpy(ptPos, &Sound_tMicrophonePos, sizeof(struct real64x3_t));
  qmemcpy(ptSpeed, &Sound_tMicrophoneSpeed, sizeof(struct real64x3_t));
  return ptMOrientation;
}

// source: b/2/pc/pc_sound.c:1766  [size]
struct Sound_s *__cdecl Sound_StopSound(struct Sound_s *ptSound)
{
  struct _STREAM *hStream; // ecx

  if ( Sound_isSSInitialized )
  {
    hStream = ptSound->hStream;
    if ( hStream )
    {
      AIL_pause_stream(hStream, 1);
      return 0;
    }
    else if ( ptSound->hSample )
    {
      AIL_stop_sample(ptSound->hSample);
      return 0;
    }
    else
    {
      ptSound = (struct Sound_s *)ptSound->h3DSample;
      if ( ptSound )
        AIL_stop_3D_sample(ptSound);
        return 0;
    }
  }
  return ptSound;
}

// source: b/2/pc/pc_sound.c:1800  [size]
void __cdecl Sound_ModifySound(struct Sound_s *ptSound, struct SoundModify_t *ptModify)
{
  #pragma pack(push, 1)
  union
  {
    struct { float vFalloffEnd; };
    struct { char igi2_o1[4]; float v17; };
    struct { char igi2_o2[4]; float v19; };
    struct { char igi2_o3[4]; float vFalloffBegin; };
    struct { char igi2_o4[8]; float vSpeed; };
    struct { char igi2_o5[12]; float vVolume; };
    struct { char igi2_o6[16]; float vPitch; };
    struct { char igi2_o7[24]; int nMilliseconds; };
    struct { char igi2_o8[28]; struct real32x3_t tSpeed; };
    struct { char igi2_o9[40]; struct real32x3_t tPos; };
    struct { char igi2_o10[52]; struct real32x3_t Real32x3_RotateInverse_tTemp; };
    struct { char igi2_o11[64]; float v27; };
    struct { char igi2_o12[68]; float v28; };
    struct { char igi2_o13[72]; float v29; };
    char igi2_extent[76];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  double v2; // st7
  struct _STREAM *hStream; // eax
  struct h3DPOBJECT *h3DSample; // ecx
  double v5; // st7
  double v6; // st6
  double v7; // st5
  double v8; // st7
  double v9; // st6
  double v10; // st5
  double v11; // st7
  double v12; // st7
  long double v13; // st7
  double v14; // st7
  struct _SAMPLE *hSample; // eax

  if ( ptModify->tAttr.vPitch >= 0.5 )
  {
    if ( ptModify->tAttr.vPitch <= 2.0 )
      igi2_frame.vPitch = ptModify->tAttr.vPitch;
    else
      igi2_frame.vPitch = 2.0;
  }
  else
  {
    igi2_frame.vPitch = 0.5;
  }
  if ( (ptSound->bFlags & 0x20) != 0 )
    v2 = Sound_vCDPlayedVolume * ptModify->tAttr.vVolume * Sound_vCDMasterVolume;
  else
    v2 = Sound_vSSMasterVolume * ptModify->tAttr.vVolume;
  hStream = ptSound->hStream;
  igi2_frame.vVolume = v2;
  if ( hStream )
  {
    igi2_frame.v17 = (ptModify->tAttr.vPan + 1.0) * 0.5;
    AIL_set_stream_volume_pan(hStream, LODWORD(igi2_frame.vVolume), LODWORD(igi2_frame.v17));
  }
  else
  {
    h3DSample = ptSound->h3DSample;
    if ( h3DSample )
    {
      v5 = ptModify->tPos.vX - Sound_tMicrophonePos.vX;
      v6 = ptModify->tPos.vY - Sound_tMicrophonePos.vY;
      v7 = ptModify->tPos.vZ - Sound_tMicrophonePos.vZ;
      igi2_frame.Real32x3_RotateInverse_tTemp.vX = Sound_tMMicrophoneOrientation.tZ.vX * v7
                                      + Sound_tMMicrophoneOrientation.tY.vX * v6
                                      + Sound_tMMicrophoneOrientation.tX.vX * v5;
      igi2_frame.Real32x3_RotateInverse_tTemp.vY = Sound_tMMicrophoneOrientation.tZ.vY * v7
                                      + Sound_tMMicrophoneOrientation.tY.vY * v6
                                      + Sound_tMMicrophoneOrientation.tX.vY * v5;
      igi2_frame.Real32x3_RotateInverse_tTemp.vZ = Sound_tMMicrophoneOrientation.tZ.vZ * v7
                                      + Sound_tMMicrophoneOrientation.tY.vZ * v6
                                      + Sound_tMMicrophoneOrientation.tX.vZ * v5;
      igi2_frame.tPos = igi2_frame.Real32x3_RotateInverse_tTemp;
      v8 = ptModify->tSpeed.vX - Sound_tMicrophoneSpeed.vX;
      v9 = ptModify->tSpeed.vY - Sound_tMicrophoneSpeed.vY;
      v10 = ptModify->tSpeed.vZ - Sound_tMicrophoneSpeed.vZ;
      igi2_frame.v27 = Sound_tMMicrophoneOrientation.tZ.vX * v10
          + Sound_tMMicrophoneOrientation.tY.vX * v9
          + Sound_tMMicrophoneOrientation.tX.vX * v8;
      igi2_frame.v28 = Sound_tMMicrophoneOrientation.tZ.vY * v10
          + Sound_tMMicrophoneOrientation.tY.vY * v9
          + Sound_tMMicrophoneOrientation.tX.vY * v8;
      igi2_frame.v29 = Sound_tMMicrophoneOrientation.tZ.vZ * v10
          + Sound_tMMicrophoneOrientation.tY.vZ * v9
          + Sound_tMMicrophoneOrientation.tX.vZ * v8;
      igi2_frame.tPos.vX = igi2_frame.Real32x3_RotateInverse_tTemp.vX * 0.000244140625;
      igi2_frame.tPos.vY = igi2_frame.Real32x3_RotateInverse_tTemp.vY * 0.000244140625;
      igi2_frame.tPos.vZ = igi2_frame.Real32x3_RotateInverse_tTemp.vZ * 0.000244140625;
      v11 = (double)Sound_nFrequency;
      igi2_frame.tSpeed.vX = igi2_frame.v27 * v11 * 2.4414063659605745e-07;
      igi2_frame.tSpeed.vY = igi2_frame.v28 * v11 * 2.4414063659605745e-07;
      v12 = v11 * igi2_frame.v29 * 2.4414063659605745e-07;
      igi2_frame.tSpeed.vZ = v12;
      v13 = sqrt(igi2_frame.tSpeed.vX * igi2_frame.tSpeed.vX + igi2_frame.tSpeed.vY * igi2_frame.tSpeed.vY + v12 * v12);
      igi2_frame.vSpeed = v13;
      if ( v13 > 0.16500000655651093 )
      {
        v14 = 0.16500000655651093 / igi2_frame.vSpeed;
        igi2_frame.vSpeed = 0.16500000655651093;
        igi2_frame.tSpeed.vX = igi2_frame.tSpeed.vX * v14;
        igi2_frame.tSpeed.vY = igi2_frame.tSpeed.vY * v14;
        igi2_frame.tSpeed.vZ = v14 * igi2_frame.tSpeed.vZ;
      }
      igi2_frame.vFalloffBegin = ptModify->tAttr.vFalloffBegin;
      igi2_frame.vFalloffEnd = ptModify->tAttr.vFalloffEnd;
      AIL_set_3D_sample_distances(h3DSample, LODWORD(igi2_frame.vFalloffEnd), LODWORD(igi2_frame.vFalloffBegin));
      AIL_set_3D_position(ptSound->h3DSample, LODWORD(igi2_frame.tPos.vX), LODWORD(igi2_frame.tPos.vZ), LODWORD(igi2_frame.tPos.vY));
      AIL_set_3D_velocity(
        ptSound->h3DSample,
        LODWORD(igi2_frame.tSpeed.vX),
        LODWORD(igi2_frame.tSpeed.vZ),
        LODWORD(igi2_frame.tSpeed.vY),
        LODWORD(igi2_frame.vSpeed));
      AIL_set_3D_sample_volume(ptSound->h3DSample, LODWORD(igi2_frame.vVolume));
      if ( ptSound->isMP3 == false )
        AIL_set_3D_sample_playback_rate(
          ptSound->h3DSample,
          (__int64)((double)ptSound->ptSample->tSoundFileHeader.nFrequency * igi2_frame.vPitch));
      if ( (ptSound->bFlags & 0x40) != 0 )
        AIL_set_3D_sample_offset(
          ptSound->h3DSample,
          2 * (__int64)((double)ptSound->ptSample->tSoundFileHeader.nFrequency * ptModify->vPlayPos));
      else
        ptModify->vPlayPos = (double)(unsigned int)AIL_3D_sample_offset(ptSound->h3DSample)
                           / (double)(2 * ptSound->ptSample->tSoundFileHeader.nFrequency);
    }
    else
    {
      hSample = ptSound->hSample;
      if ( hSample )
      {
        igi2_frame.v19 = (ptModify->tAttr.vPan + 1.0) * 0.5;
        AIL_set_sample_volume_pan(hSample, LODWORD(igi2_frame.vVolume), LODWORD(igi2_frame.v19));
        if ( ptSound->isMP3 == false )
          AIL_set_sample_playback_rate(
            ptSound->hSample,
            (__int64)((double)ptSound->ptSample->tSoundFileHeader.nFrequency * igi2_frame.vPitch));
        if ( (ptSound->bFlags & 0x40) != 0 )
        {
          AIL_set_sample_ms_position(ptSound->hSample, (__int64)(ptModify->vPlayPos * 1000.0));
        }
        else
        {
          AIL_sample_ms_position(ptSound->hSample, 0, &igi2_frame.nMilliseconds);
          ptModify->vPlayPos = (double)igi2_frame.nMilliseconds * 0.0010000000474974513;
        }
      }
    }
  }
}

// source: b/2/pc/pc_sound.c:1895  [size]
void __cdecl Sound_CropFilenameToSamplename(char *pzSamplename, char *pzFilename)
{
  char v2; // cl
  char *v3; // eax
  char *v4; // esi
  char v5; // cl
  char *v6; // eax
  size_t v7; // esi

  *pzSamplename = 0;
  v2 = *pzFilename;
  v3 = pzFilename;
  if ( *pzFilename )
  {
    while ( v2 != 46 )
    {
      v2 = *++v3;
      if ( !v2 )
        return;
    }
    v4 = v3;
    if ( v3 >= pzFilename )
    {
      while ( 1 )
      {
        v5 = *v3;
        if ( *v3 == 47 || v5 == 92 || v5 == 58 )
          break;
        if ( --v3 < pzFilename )
          return;
      }
      v6 = v3 + 1;
      v7 = v4 - v6;
      strncpy(pzSamplename, v6, v7);
      pzSamplename[v7] = 0;
    }
  }
}

// source: b/2/pc/pc_sound.c:1952  [size]
struct SoundModify_t *__cdecl Sound_DefaultSoundModify(struct SoundModify_t *ptModify)
{
  ptModify->tAttr.vVolume = 1.0;
  ptModify->tAttr.vPitch = 1.0;
  ptModify->tAttr.vPan = 0.0;
  ptModify->tAttr.vFalloffBegin = 0.0;
  ptModify->tAttr.vFalloffEnd = 1.0;
  ptModify->tAttr.vOcclusion = 0.0;
  ptModify->tPos.vX = 0.0;
  ptModify->tPos.vY = 0.0;
  ptModify->tPos.vZ = 0.0;
  ptModify->tSpeed.vX = 0.0;
  ptModify->tSpeed.vY = 0.0;
  ptModify->tSpeed.vZ = 0.0;
  ptModify->vPlayPos = 0.0;
  return ptModify;
}

// source: b/2/pc/pc_sound.c:1980  [size]
struct SoundAttr_t *__cdecl Sound_DefaultSoundAttr(struct SoundAttr_t *ptAttr)
{
  ptAttr->vVolume = 1.0;
  ptAttr->vPitch = 1.0;
  ptAttr->vPan = 0.0;
  ptAttr->vFalloffBegin = 0.0;
  ptAttr->vFalloffEnd = 1.0;
  ptAttr->vOcclusion = 0.0;
  return ptAttr;
}

// source: b/2/pc/pc_sound.c:2004  [size]
int __cdecl Sound_GetNumVoices()
{
  return Sound_nSSMaxPlayBuffers;
}

// source: b/2/pc/pc_sound.c:2017  [size]
float __cdecl Sound_GetStreamMasterVolume()
{
  return Sound_vSStreamMasterVolume;
}

// source: b/2/pc/pc_sound.c:2030  [size]
void __cdecl Sound_SetStreamMasterVolume(float vVol)
{
  ;
}

// source: b/2/pc/pc_sound.c:2042  [size]
float __cdecl Sound_GetStreamVolume()
{
  return Sound_vSStreamVolume;
}

// source: b/2/pc/pc_sound.c:2055  [size]
void __cdecl Sound_SetStreamVolume(float vVol)
{
  ;
}

// source: b/2/pc/pc_sound.c:2067  [size]
enum bool __cdecl Sound_Get3DProviderName(int iProvider, char **pzProvider)
{
  if ( iProvider >= provider_count )
    return false;
  *pzProvider = provider_names[iProvider];
  return true;
}

// source: b/2/pc/pc_sound.c:2087  [size]
int __cdecl Sound_Set3DProvider(int iProvider)
{
  unsigned int v1; // esi

  v1 = iProvider;
  if ( iProvider >= provider_count )
    return 0;
  if ( iProvider == provider_activeindex )
    return 0;
  iProvider = 0;
  mciSendCommandA(Sound_DeviceID, 0x808u, 0, (DWORD_PTR)&iProvider);
  Sound_nCDPlayedTrack = -1;
  AIL_close_3D_provider(Sound_hMiles3DProvider);
  Sound_hMiles3DProvider = provider_handles[v1];
  provider_activeindex = v1;
  if ( !AIL_open_3D_provider(Sound_hMiles3DProvider) )
    return 0;
  Sound_Set3DProvider(provider_defaultindex);
  return 1;
}

// source: b/2/pc/pc_sound.c:2117  [size]
int __cdecl Sound_Get3DProvider()
{
  return provider_activeindex;
}

// source: b/2/pc/pc_sound.c:2135  [size]
void __cdecl Sound_Open()
{
  #pragma pack(push, 1)
  union
  {
    struct { unsigned int enum3D; };
    struct { char igi2_o1[4]; enum bool isFound; };
    char igi2_extent[8];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QHashTable_s *v0; // esi
  void *v1; // edi
  unsigned int v2; // eax
  struct Sound_s *v3; // eax
  int v4; // edx
  struct Sound_s *v5; // ecx

  igi2_frame.enum3D = 0;
  igi2_frame.isFound = false;
  if ( AppContext_tAppContext.isServer == false )
  {
    v0 = (struct QHashTable_s *)Mem_AllocFn(40, 4);
    v0->tPrivate.nHashTableSize = 256;
    v0->tPrivate.pfHashFunction = QHashTable_CaseInsensitiveStringHashFunction;
    v0->tPrivate.pfCompareKey = QHashTable_CaseInsensitiveStringCompareKeyFunction;
    v0->tPrivate.pfDuplicateKey = QHashTable_StringDuplicateKeyFunction;
    v0->tPrivate.pfCreateElement = QHashTable_CreateElementChained;
    v0->tPrivate.pfFindElement = QHashTable_FindElementChained;
    v0->tPrivate.pfDeleteElement = QHashTable_DeleteElementChained;
    v0->tPrivate.pfMap = QHashTable_MapChained;
    v0->tPrivate.nEntries = 0;
    v1 = Mem_AllocFn(3072, 4);
    v2 = 0;
    v0->tPrivate.papxElement = v1;
    memset(v1, 0, 0xC00u);
    do
    {
      *(_DWORD *)((char *)v0->tPrivate.papxElement + v2) = (char *)v0->tPrivate.papxElement + v2 + 4;
      *(_DWORD *)((char *)v0->tPrivate.papxElement + v2 + 8) = (char *)v0->tPrivate.papxElement + v2;
      *(_DWORD *)((char *)v0->tPrivate.papxElement + v2 + 4) = 0;
      *(_DWORD *)((char *)v0->tPrivate.papxElement + v2 + 12) = (char *)v0->tPrivate.papxElement + v2 + 16;
      *(_DWORD *)((char *)v0->tPrivate.papxElement + v2 + 20) = (char *)v0->tPrivate.papxElement + v2 + 12;
      *(_DWORD *)((char *)v0->tPrivate.papxElement + v2 + 16) = 0;
      *(_DWORD *)((char *)v0->tPrivate.papxElement + v2 + 24) = (char *)v0->tPrivate.papxElement + v2 + 28;
      *(_DWORD *)((char *)v0->tPrivate.papxElement + v2 + 32) = (char *)v0->tPrivate.papxElement + v2 + 24;
      *(_DWORD *)((char *)v0->tPrivate.papxElement + v2 + 28) = 0;
      *(_DWORD *)((char *)v0->tPrivate.papxElement + v2 + 36) = (char *)v0->tPrivate.papxElement + v2 + 40;
      *(_DWORD *)((char *)v0->tPrivate.papxElement + v2 + 44) = (char *)v0->tPrivate.papxElement + v2 + 36;
      *(_DWORD *)((char *)v0->tPrivate.papxElement + v2 + 40) = 0;
      *(_DWORD *)((char *)v0->tPrivate.papxElement + v2 + 48) = (char *)v0->tPrivate.papxElement + v2 + 52;
      *(_DWORD *)((char *)v0->tPrivate.papxElement + v2 + 56) = (char *)v0->tPrivate.papxElement + v2 + 48;
      *(_DWORD *)((char *)v0->tPrivate.papxElement + v2 + 52) = 0;
      *(_DWORD *)((char *)v0->tPrivate.papxElement + v2 + 60) = (char *)v0->tPrivate.papxElement + v2 + 64;
      *(_DWORD *)((char *)v0->tPrivate.papxElement + v2 + 68) = (char *)v0->tPrivate.papxElement + v2 + 60;
      *(_DWORD *)((char *)v0->tPrivate.papxElement + v2 + 64) = 0;
      *(_DWORD *)((char *)v0->tPrivate.papxElement + v2 + 72) = (char *)v0->tPrivate.papxElement + v2 + 76;
      *(_DWORD *)((char *)v0->tPrivate.papxElement + v2 + 80) = (char *)v0->tPrivate.papxElement + v2 + 72;
      *(_DWORD *)((char *)v0->tPrivate.papxElement + v2 + 76) = 0;
      *(_DWORD *)((char *)v0->tPrivate.papxElement + v2 + 84) = (char *)v0->tPrivate.papxElement + v2 + 88;
      *(_DWORD *)((char *)v0->tPrivate.papxElement + v2 + 92) = (char *)v0->tPrivate.papxElement + v2 + 84;
      *(_DWORD *)((char *)v0->tPrivate.papxElement + v2 + 88) = 0;
      v2 += 96;
    }
    while ( v2 < 0xC00 );
    Sound_ptSampleHashTable = v0;
    AIL_set_redist_directory("miles");
    MSS_auto_cleanup();
    AIL_startup();
    Sound_hMilesDigitalDriver = (struct _DIG_DRIVER *)AIL_open_digital_driver(44100, 16, 2, 0);
    if ( Sound_hMilesDigitalDriver )
    {
      if ( !AIL_enumerate_3D_providers(&igi2_frame.enum3D, 4 * provider_count + 127859416, 4 * provider_count + 127859104) )
        goto LABEL_10;
      do
      {
        if ( !strcmp(provider_names[provider_count], "Miles Fast 2D Positional Audio") )
        {
          Sound_hMiles3DProvider = provider_handles[provider_count];
          provider_activeindex = provider_count;
          provider_defaultindex = provider_count;
          igi2_frame.isFound = true;
        }
        ++provider_count;
      }
      while ( AIL_enumerate_3D_providers(&igi2_frame.enum3D, 4 * provider_count + 127859416, 4 * provider_count + 127859104) );
      if ( igi2_frame.isFound == false )
      {
LABEL_10:
        LDebug_Error("Could not find 3D sound provider");
        abort();
      }
      AIL_open_3D_provider(Sound_hMiles3DProvider);
      Sound_nSSMaxPlayBuffers = 32;
      v3 = (struct Sound_s *)Mem_AllocFn(1152, 4);
      v4 = Sound_nSSMaxPlayBuffers;
      memset(v3, 0, 36 * Sound_nSSMaxPlayBuffers);
      Sound_aptSounds = v3;
      if ( v4 > 0 )
      {
        v5 = Sound_ptFirstFreeSound;
        do
        {
          v3->ptNext = v5;
          v3->ptPrev = nullptr;
          if ( Sound_ptFirstFreeSound )
            Sound_ptFirstFreeSound->ptPrev = v3;
          v5 = v3++;
          --v4;
          Sound_ptFirstFreeSound = v5;
        }
        while ( v4 );
      }
      Sound_ptFirstTakenSound = nullptr;
      Sound_isSSInitialized = true;
    }
  }
}

// source: b/2/pc/pc_sound.c:2231  [size]
void __cdecl Sound_Close()
{
  int v0; // esi

  if ( AppContext_tAppContext.isServer == false )
  {
    QHashTable_Delete(Sound_ptSampleHashTable);
    AIL_close_3D_provider(Sound_hMiles3DProvider);
    AIL_shutdown();
    if ( Sound_aptSounds )
    {
      v0 = *(_DWORD *)((unsigned int)&Sound_aptSounds[-1].isMP3 & 0xFFFFFFFC);
      --Mem_nCurrentAllocations;
      Node_Remove((_DWORD **)v0);
      memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
      free((void *)v0);
    }
    Sound_aptSounds = nullptr;
  }
}
