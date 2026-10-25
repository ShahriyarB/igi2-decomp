/* b/2/pc/pc_joypad.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: b/2/pc/pc_joypad.c:110  [size~]
int __stdcall joypad_EnumerateDevices(struct DIDEVICEINSTANCEA *lpDDI, void *pvRef)
{
  #pragma pack(push, 1)
  union
  {
    struct { _DWORD v13[4]; };
    struct { char igi2_o1[16]; _DWORD v14[2]; };
    struct { char igi2_o2[24]; int nAxis; };
    struct { char igi2_o3[28]; int v16; };
    struct { char igi2_o4[32]; int v17; };
    struct { char igi2_o5[36]; _DWORD v18[6]; };
    char igi2_extent[60];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  unsigned int Data1; // ecx
  int v3; // ecx
  int v4; // esi
  struct IDirectInputDevice8A *v5; // eax
  int *p_isSupported; // esi
  HRESULT v8; // eax
  struct IDirectInputDevice8A *v9; // eax
  struct IDirectInputDevice8A *v10; // eax
  struct JoypadAxesInfo_t *v11; // esi
  struct IDirectInputDevice8A *v12; // eax

  Data1 = lpDDI->guidInstance.Data1;
  igi2_frame.v13[1] = *(_DWORD *)&lpDDI->guidInstance.Data2;
  igi2_frame.v13[0] = Data1;
  v3 = *(_DWORD *)lpDDI->guidInstance.Data4;
  igi2_frame.v13[3] = *(_DWORD *)&lpDDI->guidInstance.Data4[4];
  igi2_frame.v13[2] = v3;
  if ( Keyboard_lpDIObject->lpVtbl->CreateDevice(
         Keyboard_lpDIObject,
         (GUID *const)igi2_frame.v13,
         (LPDIRECTINPUTDEVICE8A *)(4 * joypad_nDeviceCount + 129465344),
         nullptr) < 0 )
  {
    LDebug_Error("Failed to create device.");
    abort();
  }
  v4 = joypad_alpDID[joypad_nDeviceCount]->lpVtbl->QueryInterface(
         joypad_alpDID[joypad_nDeviceCount],
         &CLSID_IDirectInputDevice8A,
         (LPVOID *)(4 * joypad_nDeviceCount + 129465536));
  joypad_alpDID[joypad_nDeviceCount]->lpVtbl->Release(joypad_alpDID[joypad_nDeviceCount]);
  if ( v4 < 0 )
  {
    LDebug_Error("Failed to obtain interface.");
    abort();
  }
  if ( joypad_alpDID2[joypad_nDeviceCount]->lpVtbl->SetDataFormat(
         joypad_alpDID2[joypad_nDeviceCount],
         &c_dfDIJoystick_675d9c) >= 0 )
  {
    if ( joypad_alpDID2[joypad_nDeviceCount]->lpVtbl->SetCooperativeLevel(
           joypad_alpDID2[joypad_nDeviceCount],
           AppContext_tAppContext.hWnd,
           5) >= 0 )
    {
      igi2_frame.v18[0] = 24;
      igi2_frame.v18[1] = 16;
      igi2_frame.v18[3] = 1;
      igi2_frame.v18[4] = -128;
      igi2_frame.v18[5] = 128;
      p_isSupported = &joypad_anAxisConstants[0].isSupported;
      do
      {
        igi2_frame.v18[2] = *(p_isSupported - 1);
        v8 = joypad_alpDID[joypad_nDeviceCount]->lpVtbl->SetProperty(
               joypad_alpDID[joypad_nDeviceCount],
               (GUID *const)4,
               (LPCDIPROPHEADER)igi2_frame.v18);
        if ( v8 )
        {
          if ( v8 != -2147024894 )
            goto LABEL_5;
          *p_isSupported = 0;
        }
        p_isSupported += 2;
      }
      while ( (int)p_isSupported < 7014668 );
      v9 = joypad_alpDID[joypad_nDeviceCount];
      igi2_frame.v14[0] = 20;
      igi2_frame.v14[1] = 16;
      igi2_frame.nAxis = 0;
      igi2_frame.v16 = 0;
      igi2_frame.v17 = 1;
      v9->lpVtbl->SetProperty(v9, (GUID *const)9, (LPCDIPROPHEADER)igi2_frame.v14);
      v10 = joypad_alpDID[joypad_nDeviceCount];
      igi2_frame.v16 = 0;
      igi2_frame.v17 = 10000;
      v10->lpVtbl->SetProperty(v10, (GUID *const)6, (LPCDIPROPHEADER)igi2_frame.v14);
      igi2_frame.v16 = 1;
      igi2_frame.v17 = joypad_nDeadZone;
      v11 = joypad_anAxisConstants;
      while ( 1 )
      {
        if ( v11->isSupported )
        {
          v12 = joypad_alpDID[joypad_nDeviceCount];
          igi2_frame.nAxis = v11->nAxis;
          if ( v12->lpVtbl->SetProperty(v12, (GUID *const)5, (LPCDIPROPHEADER)igi2_frame.v14) )
            break;
        }
        if ( (int)++v11 >= 7014664 )
        {
          ++joypad_nDeviceCount;
          return 1;
        }
      }
    }
    v5 = joypad_alpDID2[joypad_nDeviceCount];
  }
  else
  {
LABEL_5:
    v5 = joypad_alpDID2[joypad_nDeviceCount];
  }
  v5->lpVtbl->Release(v5);
  joypad_alpDID2[joypad_nDeviceCount] = nullptr;
  return 1;
}

// source: b/2/pc/pc_joypad.c:283  [size]
int __cdecl joypad_AcquireInput(int nDevice)
{
  return Joypad_atJoypad[0].isConnected
      && joypad_alpDID2[nDevice]
      && joypad_alpDID[nDevice]->lpVtbl->Acquire(joypad_alpDID[nDevice]) >= 0;
}

// source: b/2/pc/pc_joypad.c:350  [size]
void __cdecl Joypad_Update()
{
  int v0; // eax
  int v1; // ebx
  struct IDirectInputDevice8A *v2; // eax
  int v3; // eax
  unsigned int *p_bButton; // ebp
  char *v5; // edi
  int v6; // esi
  unsigned int v7; // eax
  int v8; // edx
  int v9; // ebx
  char v10; // cl
  int v11; // ecx
  int v12; // eax
  int v13; // eax
  int v14; // eax
  double v15; // st7
  bool v16; // c0
  bool v17; // c3
  double v18; // st7
  double v19; // st7
  int nI; // [esp+14h] [ebp-8h]
  int nIa; // [esp+14h] [ebp-8h]
  int nIb; // [esp+14h] [ebp-8h]
  int i; // [esp+18h] [ebp-4h]

  if ( Joypad_atJoypad[0].isConnected )
  {
    v0 = 0;
    nI = 0;
    if ( joypad_nDeviceCount > 0 )
    {
      v1 = 0;
      do
      {
        v2 = joypad_alpDID2[v0];
        if ( v2 )
        {
          qmemcpy(&joypad_asPrevDIJoyState[v1], &joypad_asDIJoyState[v1], sizeof(struct DIJOYSTATE));
          v2->lpVtbl->Poll(v2);
          v3 = joypad_alpDID2[nI]->lpVtbl->GetDeviceState(joypad_alpDID2[nI], 80, &joypad_asDIJoyState[v1]);
          if ( v3 < 0 )
          {
            if ( v3 == -2147024866 && Joypad_atJoypad[0].isConnected && joypad_alpDID2[nI] )
              joypad_alpDID[nI]->lpVtbl->Acquire(joypad_alpDID[nI]);
            memset(&joypad_asDIJoyState[v1], 0, sizeof(struct DIJOYSTATE));
          }
        }
        v0 = nI + 1;
        ++v1;
        ++nI;
      }
      while ( nI < joypad_nDeviceCount );
      if ( joypad_nDeviceCount > 0 )
      {
        p_bButton = &Joypad_atJoypad[0].bButton;
        v5 = (char *)&joypad_asDIJoyState[0].rgdwPOV[3] + 1;
        for ( i = joypad_nDeviceCount; i; --i )
        {
          v6 = 4;
          p_bButton[1] = *p_bButton;
          *p_bButton = 0;
          v7 = 0;
          nIa = 4;
          do
          {
            v8 = (((v5[v6 + 1] & 0x80) == 0x80) << (v6 + 2))
               | (((v5[v6 + 2] & 0x80) == 0x80) << (v6 + 3))
               | (((v5[v6 + 3] & 0x80) == 0x80) << (v6 + 4))
               | (((v5[v6 + 4] & 0x80) == 0x80) << (v6 + 5))
               | (((v5[v6 + 5] & 0x80) == 0x80) << (v6 + 6))
               | (((v5[v6 + 6] & 0x80) == 0x80) << (v6 + 7))
               | (((v5[v6] & 0x80) == 0x80) << (v6 + 1));
            v9 = ((v5[v6 - 1] & 0x80) == 0x80) << v6;
            v6 += 8;
            v7 |= v9 | v8;
            --nIa;
          }
          while ( nIa );
          v10 = *((_BYTE *)p_bButton - 28);
          *p_bButton = v7;
          if ( !v10 )
            goto LABEL_27;
          v11 = *(_DWORD *)(v5 - 45);
          if ( v11 >= 0 )
          {
            if ( v11 <= 0 )
              goto LABEL_22;
            v12 = v7 | 2;
          }
          else
          {
            v12 = v7 | 1;
          }
          *p_bButton = v12;
LABEL_22:
          v13 = *(_DWORD *)(v5 - 41);
          if ( v13 < 0 )
          {
            v14 = *p_bButton | 4;
LABEL_26:
            *p_bButton = v14;
            goto LABEL_27;
          }
          if ( v13 > 0 )
          {
            v14 = *p_bButton | 8;
            goto LABEL_26;
          }
LABEL_27:
          if ( *((_BYTE *)p_bButton - 27) )
          {
            if ( !*p_bButton )
              *((_BYTE *)p_bButton - 27) = 0;
            *p_bButton = 0;
          }
          nIb = *(_DWORD *)(v5 - 25);
          *((float *)p_bButton - 6) = (double)*(int *)(v5 - 45) * 0.0078125;
          *((float *)p_bButton - 5) = (double)*(int *)(v5 - 41) * 0.0078125;
          v15 = (double)nIb;
          v16 = v15 < 0.0;
          v17 = v15 == 0.0;
          v18 = v15 * 0.0078125;
          if ( v16 || v17 )
          {
            *((float *)p_bButton - 2) = -v18;
            *(p_bButton - 1) = 0;
          }
          else
          {
            *((float *)p_bButton - 1) = v18;
            *(p_bButton - 2) = 0;
          }
          v19 = (double)*(int *)(v5 - 21);
          v5 += 80;
          p_bButton += 10;
          *((float *)p_bButton - 14) = v19;
          *((float *)p_bButton - 13) = (float)*(int *)(v5 - 97);
        }
      }
    }
  }
}

// source: b/2/pc/pc_joypad.c:467  [size]
void __cdecl Joypad_Open()
{
  int v0; // edi
  char *p_isAnalog; // esi
  struct DIDEVCAPS *v2; // ebp
  struct IDirectInputDevice8A *v3; // eax
  bool v4; // dl
  int v5; // eax

  v0 = 0;
  joypad_nDeviceCount = 0;
  if ( AppContext_tAppContext.isServer )
  {
    Joypad_atJoypad[0].isConnected = 0;
  }
  else
  {
    Keyboard_lpDIObject->lpVtbl->EnumDevices(Keyboard_lpDIObject, 20, joypad_EnumerateDevices, nullptr, 1);
    if ( joypad_nDeviceCount > 0 )
    {
      p_isAnalog = &Joypad_atJoypad[0].isAnalog;
      v2 = joypad_asDIDevCaps;
      do
      {
        if ( Joypad_atJoypad[0].isConnected && joypad_alpDID2[v0] )
          joypad_alpDID[v0]->lpVtbl->Acquire(joypad_alpDID[v0]);
        v3 = joypad_alpDID2[v0];
        v2->dwSize = 44;
        if ( v3->lpVtbl->GetCapabilities(v3, v2) )
        {
          LDebug_Error("Could not get capabilities for one or more joysticks .");
          abort();
        }
        v4 = joypad_alpDID2[v0] != nullptr;
        p_isAnalog[6] = v2->dwButtons;
        v5 = joypad_nDeviceCount;
        *(p_isAnalog - 1) = v4;
        *p_isAnalog = 1;
        p_isAnalog[2] = 1;
        p_isAnalog[3] = 1;
        ++v0;
        ++v2;
        p_isAnalog += 40;
      }
      while ( v0 < v5 );
    }
  }
}

// source: b/2/pc/pc_joypad.c:530  [size]
void __cdecl Joypad_Close()
{
  int i; // esi
  struct IDirectInputDevice8A *v1; // eax

  if ( Keyboard_lpDIObject )
  {
    for ( i = 0; i < joypad_nDeviceCount; ++i )
    {
      v1 = joypad_alpDID2[i];
      if ( v1 )
      {
        v1->lpVtbl->Unacquire(joypad_alpDID2[i]);
        joypad_alpDID2[i]->lpVtbl->Release(joypad_alpDID2[i]);
        joypad_alpDID2[i] = nullptr;
      }
    }
  }
  joypad_nDeviceCount = 0;
}

// source: b/2/pc/pc_joypad.c:564  [size]
void __cdecl Joypad_UpdateCapabilities(int nDevice)
{
  struct IDirectInputDevice8A *v1; // edx
  int v2; // eax
  unsigned __int8 dwButtons; // cl

  v1 = joypad_alpDID2[nDevice];
  v2 = nDevice;
  dwButtons = joypad_asDIDevCaps[nDevice].dwButtons;
  Joypad_atJoypad[v2].isConnected = v1 != nullptr;
  Joypad_atJoypad[v2].isAnalog = 1;
  Joypad_atJoypad[v2].isDirectionPad = 1;
  Joypad_atJoypad[v2].isAnalogDirectionPad = 1;
  Joypad_atJoypad[v2].nButton = dwButtons;
}

// source: b/2/pc/pc_joypad.c:585  [size]
void __cdecl Joypad_EnableAnalogDirectionPad(int isEnable)
{
  int v1; // ecx
  char *p_isAnalogDirectionPad; // eax

  v1 = joypad_nDeviceCount;
  if ( joypad_nDeviceCount > 0 )
  {
    p_isAnalogDirectionPad = &Joypad_atJoypad[0].isAnalogDirectionPad;
    do
    {
      *p_isAnalogDirectionPad = isEnable;
      p_isAnalogDirectionPad += 40;
      --v1;
    }
    while ( v1 );
  }
}

// source: b/2/pc/pc_joypad.c:608  [size]
void __cdecl Joypad_SetDeadZonePercentage(int nDeadZonePercentage)
{
  int v1; // edi
  struct JoypadAxesInfo_t *v2; // esi
  struct DIPROPDWORD sDIPropertyWord; // [esp+8h] [ebp-14h] BYREF

  v1 = 0;
  sDIPropertyWord.diph.dwSize = 20;
  sDIPropertyWord.diph.dwHeaderSize = 16;
  sDIPropertyWord.diph.dwObj = 0;
  sDIPropertyWord.diph.dwHow = 1;
  joypad_nDeadZone = (__int64)((double)nDeadZonePercentage * 10000.0 * 0.009999999776482582);
  for ( sDIPropertyWord.dwData = joypad_nDeadZone; v1 < joypad_nDeviceCount; ++v1 )
  {
    v2 = joypad_anAxisConstants;
    do
    {
      if ( v2->isSupported )
      {
        sDIPropertyWord.diph.dwObj = v2->nAxis;
        if ( joypad_alpDID[v1]->lpVtbl->SetProperty(
               joypad_alpDID[v1],
               (GUID *const)5,
               (LPCDIPROPHEADER)&sDIPropertyWord) )
        {
          joypad_alpDID2[v1]->lpVtbl->Release(joypad_alpDID2[v1]);
          joypad_alpDID2[v1] = nullptr;
        }
      }
      ++v2;
    }
    while ( (int)v2 < 7014664 );
  }
}

// source: b/2/pc/pc_joypad.c:665  [size]
void __cdecl Joypad_ClearButtons()
{
  char *p_isClearButtonsUntilReleased; // eax

  p_isClearButtonsUntilReleased = &Joypad_atJoypad[0].isClearButtonsUntilReleased;
  do
  {
    *p_isClearButtonsUntilReleased = 1;
    p_isClearButtonsUntilReleased += 40;
  }
  while ( (int)p_isClearButtonsUntilReleased < 139759333 );
}

// source: b/2/pc/pc_joypad.c:686  [size]
void *__cdecl Joypad_GetStateInfo(int nDevice)
{
  return (void *)(80 * nDevice + 129464704);
}

// source: b/2/pc/pc_joypad.c:702  [size]
void *__cdecl Joypad_GetPrevStateInfo(int nDevice)
{
  return (void *)(80 * nDevice + 129465024);
}

// source: b/2/pc/pc_joypad.c:718  [size]
int __cdecl Joypad_GetDeviceCount()
{
  return joypad_nDeviceCount;
}
