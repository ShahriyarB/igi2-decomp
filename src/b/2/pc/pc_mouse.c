/* b/2/pc/pc_mouse.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: b/2/pc/pc_mouse.c:69  [size~]
char *__cdecl Mouse_GetErrorString(int nDIError)
{
  char *result; // eax

  if ( nDIError > -2147220983 )
  {
    if ( nDIError <= -2147024866 )
    {
      if ( nDIError == -2147024866 )
        return &g_zFileName.zMenuTaskPath[158];
      if ( nDIError > -2147024884 )
      {
        if ( nDIError == -2147024882 )
          return (char *)&g_zFileName.iMenuStack;
        if ( nDIError == -2147024875 )
          return &g_zFileName.zMenuTaskPath[246];
      }
      else
      {
        switch ( nDIError )
        {
          case -2147024884:
            return &g_zFileName.zMenuTaskPath[122];
          case -2147220982:
            return &g_zFileName.atPictureResources[31].zResourceFilename[60];
          case -2147024894:
            return (char *)&g_zFileName.tSoundSysRequest.nSoundID;
          case -2147024891:
            return &g_zFileName.zMenuTaskPath[174];
        }
      }
      return &g_zFileName.atPictureResources[31].zResourceFilename[44];
    }
    if ( nDIError <= -2147023746 )
    {
      switch ( nDIError )
      {
        case -2147023746:
          return (char *)&g_zFileName.tSoundSysRequest.tModify.tSpeed.vY + 4;
        case -2147024809:
          return (char *)&g_zFileName.anMenuStack[13];
        case -2147024777:
          return (char *)&g_zFileName.tSoundSysRequest.tModify.tAttr.vFalloffEnd;
        case -2147024726:
          return &g_zFileName.zMenuTaskPath[142];
      }
      return &g_zFileName.atPictureResources[31].zResourceFilename[44];
    }
    if ( nDIError == -2147023743 )
    {
      return (char *)&g_zFileName.tSoundSysRequest.tModify.tPos.vX + 4;
    }
    else
    {
      if ( nDIError != -2147023649 )
        return &g_zFileName.atPictureResources[31].zResourceFilename[44];
      return &g_zFileName.zMenuTaskPath[218];
    }
  }
  else
  {
    if ( nDIError == -2147220983 )
      return (char *)&g_zFileName.tRenderContext.ptPrev;
    if ( nDIError <= -2147220990 )
    {
      if ( nDIError == -2147220990 )
        return &g_zFileName.zMenuTaskPath[62];
      if ( nDIError > -2147221232 )
      {
        switch ( nDIError )
        {
          case -2147221164:
            return (char *)&g_zFileName.tSoundSysRequest.tModify.tAttr.vPitch;
          case -2147220992:
            return &g_zFileName.zMenuTaskPath[98];
          case -2147220991:
            return &g_zFileName.zMenuTaskPath[78];
        }
      }
      else
      {
        switch ( nDIError )
        {
          case -2147221232:
            return &g_zFileName.zMenuTaskPath[198];
          case -2147467263:
            return (char *)&g_zFileName.tMenuInputContext.nWheelMouseStatus;
          case -2147467262:
            return (char *)&g_zFileName.anMenuStack[8];
          case -2147467259:
            return (char *)&g_zFileName.anMenuStack[4];
        }
      }
      return &g_zFileName.atPictureResources[31].zResourceFilename[44];
    }
    switch ( nDIError )
    {
      case -2147220989:
        result = &g_zFileName.zMenuTaskPath[42];
        break;
      case -2147220988:
        result = &g_zFileName.zMenuTaskPath[22];
        break;
      case -2147220987:
        result = &g_zFileName.isPlaySounds;
        break;
      case -2147220986:
        result = (char *)&g_zFileName.tRenderContext.tDisplayAreaMax.vY;
        break;
      case -2147220985:
        result = (char *)&g_zFileName.tRenderContext.tClippingWindow.tClippingRect.vHalfWidth;
        break;
      case -2147220984:
        result = (char *)&g_zFileName.tRenderContext.tClippingWindow.tRenderPrimitive.vZ;
        break;
    }
  }
  return result;
}

// source: b/2/pc/pc_mouse.c:176  [size~]
int __cdecl Mouse_WinProcCB(struct HWND__ *hWnd, unsigned int message, unsigned int wParam, int lParam)
{
  int v4; // edx
  int result; // eax

  if ( AppContext_tAppContext.isGermany == false )
    return 1;
  switch ( message )
  {
    case 0x201u:
      ++Mouse_nWheel;
      result = 1;
      break;
    case 0x202u:
      ++dword_7089C4;
      result = 1;
      break;
    case 0x204u:
      ++Mouse_isButton1;
      result = 1;
      break;
    case 0x205u:
      ++dword_7089C8;
      result = 1;
      break;
    case 0x207u:
      ++Mouse_isButton2;
      result = 1;
      break;
    case 0x208u:
      ++dword_7089CC;
      return 1;
    case 0x20Au:
      v4 = SHIWORD(wParam) / 120;
      if ( v4 <= 0 )
        dword_7089AC -= v4;
      else
        dword_7089A8 += v4;
      result = 1;
      break;
    default:
      return 1;
  }
  return result;
}

char sub_4274B0()
{
  #pragma pack(push, 1)
  union
  {
    struct { _DWORD v12[2]; };
    struct { char igi2_o1[8]; int v13; };
    struct { char igi2_o2[12]; char v14; };
    struct { char igi2_o3[13]; char v15; };
    struct { char igi2_o4[14]; char v16; };
    struct { char igi2_o5[15]; char v17; };
    struct { char igi2_o6[16]; char v18; };
    struct { char igi2_o7[17]; char v19; };
    struct { char igi2_o8[18]; char v20; };
    struct { char igi2_o9[19]; char v21; };
    char igi2_extent[20];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v0; // eax
  int v1; // eax
  char *ErrorString; // eax
  char v3; // cl
  char v4; // cl
  char v5; // cl
  char v6; // cl
  char v7; // cl
  char v8; // cl
  char v9; // cl
  char v10; // cl

  LOBYTE(v0) = Mouse_tMouse.isConnected;
  if ( Mouse_tMouse.isConnected )
  {
    if ( (*(int (__stdcall **)(int, int, _DWORD *))(*(_DWORD *)dword_7089C0 + 36))(dword_7089C0, 20, igi2_frame.v12) )
    {
      v0 = (*(int (__stdcall **)(int))(*(_DWORD *)dword_7089C0 + 28))(dword_7089C0);
      if ( v0 )
        return v0;
      v1 = (*(int (__stdcall **)(int, int, _DWORD *))(*(_DWORD *)dword_7089C0 + 36))(dword_7089C0, 20, igi2_frame.v12);
      if ( v1 )
      {
        ErrorString = Mouse_GetErrorString(v1);
        LDebug_Error(&g_zFileName.atPictureResources[31].zResourceFilename[16], ErrorString);
        abort();
      }
    }
    LOBYTE(v0) = AppContext_tAppContext.isGermany;
    Mouse_tMouse.vAnalogX = (double)(int)igi2_frame.v12[0] * 0.00392156862745098;
    Mouse_tMouse.vAnalogY = (double)(int)igi2_frame.v12[1] * 0.00392156862745098;
    if ( AppContext_tAppContext.isGermany == false )
    {
      v3 = byte_7089B8;
      byte_7089B0 = byte_7089B8;
      byte_7089B8 = igi2_frame.v14 != 0;
      if ( igi2_frame.v14 )
      {
        if ( !v3 )
          ++Mouse_nWheel;
      }
      else if ( v3 )
      {
        ++dword_7089C4;
      }
      v4 = byte_7089B9;
      byte_7089B1 = byte_7089B9;
      byte_7089B9 = igi2_frame.v15 != 0;
      if ( igi2_frame.v15 )
      {
        if ( !v4 )
          ++Mouse_isButton1;
      }
      else if ( v4 )
      {
        ++dword_7089C8;
      }
      v5 = byte_7089BA;
      byte_7089B2 = byte_7089BA;
      byte_7089BA = igi2_frame.v16 != 0;
      if ( igi2_frame.v16 )
      {
        if ( !v5 )
          ++Mouse_isButton2;
      }
      else if ( v5 )
      {
        ++dword_7089CC;
      }
      v6 = byte_7089BB;
      byte_7089B3 = byte_7089BB;
      byte_7089BB = igi2_frame.v17 != 0;
      if ( igi2_frame.v17 )
      {
        if ( !v6 )
          ++Mouse_nWheelUp;
      }
      else if ( v6 )
      {
        ++dword_7089D0;
      }
      v7 = byte_7089BC;
      byte_7089B4 = byte_7089BC;
      byte_7089BC = igi2_frame.v18 != 0;
      if ( igi2_frame.v18 )
      {
        if ( !v7 )
          ++dword_708998;
      }
      else if ( v7 )
      {
        ++dword_7089D4;
      }
      v8 = byte_7089BD;
      byte_7089B5 = byte_7089BD;
      byte_7089BD = igi2_frame.v19 != 0;
      if ( igi2_frame.v19 )
      {
        if ( !v8 )
          ++dword_70899C;
      }
      else if ( v8 )
      {
        ++Mouse_isButton3;
      }
      v9 = byte_7089BE;
      byte_7089B6 = byte_7089BE;
      byte_7089BE = igi2_frame.v20 != 0;
      if ( igi2_frame.v20 )
      {
        if ( !v9 )
          ++dword_7089A0;
      }
      else if ( v9 )
      {
        ++Mouse_nWheelDown;
      }
      v10 = byte_7089BF;
      byte_7089B7 = byte_7089BF;
      byte_7089BF = igi2_frame.v21 != 0;
      if ( igi2_frame.v21 )
      {
        if ( !v10 )
          ++dword_7089A4;
      }
      else if ( v10 )
      {
        Mouse_lpDIDMouse = (struct IDirectInputDevice8A *)((char *)Mouse_lpDIDMouse + 1);
      }
      LOBYTE(v0) = igi2_frame.v13;
      if ( igi2_frame.v13 <= 0 )
      {
        if ( igi2_frame.v13 < 0 )
          ++dword_7089AC;
      }
      else
      {
        ++dword_7089A8;
      }
    }
  }
  return v0;
}

// source: b/2/pc/pc_mouse.c:235  [size~]
void __cdecl Mouse_Update(enum bool isUpdateButtons)
{
  #pragma pack(push, 1)
  union
  {
    struct { int v16; };
    struct { char igi2_o1[4]; int v17; };
    struct { char igi2_o2[8]; int v18; };
    struct { char igi2_o3[12]; _DWORD v19[5]; };
    char igi2_extent[32];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  unsigned int bButton; // edi
  unsigned int v2; // ebx
  int i; // eax
  int v4; // esi
  int v5; // edx
  int v6; // ecx
  int v7; // esi
  int v8; // edx
  int v9; // ecx
  int v10; // esi
  int v11; // edx
  int v12; // ecx
  int v13; // esi
  int v14; // edx
  int v15; // ecx

  bButton = Mouse_tMouse.bButton;
  v2 = 0;
  igi2_frame.v16 = 1;
  igi2_frame.v17 = 2;
  igi2_frame.v18 = 4;
  igi2_frame.v19[0] = 8;
  igi2_frame.v19[1] = 16;
  igi2_frame.v19[2] = 32;
  igi2_frame.v19[3] = 64;
  igi2_frame.v19[4] = 128;
  for ( i = 0; i < 8; i += 4 )
  {
    v4 = *(int *)((char *)&Mouse_nWheel + i * 4);
    if ( v4 )
    {
      v5 = *(int *)((char *)&igi2_frame.v16 + i * 4);
      if ( (v5 & bButton) == 0 || (v6 = (&dword_7089C4)[i]) == 0 )
      {
        v2 |= v5;
        goto LABEL_9;
      }
      *(int *)((char *)&Mouse_nWheel + i * 4) = v4 - 1;
    }
    else
    {
      v6 = (&dword_7089C4)[i];
      if ( !v6 )
        goto LABEL_9;
    }
    (&dword_7089C4)[i] = v6 - 1;
LABEL_9:
    v7 = *(int *)((char *)&Mouse_isButton1 + i * 4);
    if ( v7 )
    {
      v8 = *(int *)((char *)&igi2_frame.v17 + i * 4);
      if ( (v8 & bButton) == 0 || (v9 = (&dword_7089C8)[i]) == 0 )
      {
        v2 |= v8;
        goto LABEL_16;
      }
      *(int *)((char *)&Mouse_isButton1 + i * 4) = v7 - 1;
    }
    else
    {
      v9 = (&dword_7089C8)[i];
      if ( !v9 )
        goto LABEL_16;
    }
    (&dword_7089C8)[i] = v9 - 1;
LABEL_16:
    v10 = *(int *)((char *)&Mouse_isButton2 + i * 4);
    if ( v10 )
    {
      v11 = igi2_frame.v19[i - 1];
      if ( (v11 & bButton) == 0 || (v12 = (&dword_7089CC)[i]) == 0 )
      {
        v2 |= v11;
        goto LABEL_23;
      }
      *(int *)((char *)&Mouse_isButton2 + i * 4) = v10 - 1;
    }
    else
    {
      v12 = (&dword_7089CC)[i];
      if ( !v12 )
        goto LABEL_23;
    }
    (&dword_7089CC)[i] = v12 - 1;
LABEL_23:
    v13 = *(int *)((char *)&Mouse_nWheelUp + i * 4);
    if ( v13 )
    {
      v14 = igi2_frame.v19[i];
      if ( (v14 & bButton) == 0 || (v15 = (&dword_7089D0)[i]) == 0 )
      {
        v2 |= v14;
        continue;
      }
      *(int *)((char *)&Mouse_nWheelUp + i * 4) = v13 - 1;
    }
    else
    {
      v15 = (&dword_7089D0)[i];
      if ( !v15 )
        continue;
    }
    (&dword_7089D0)[i] = v15 - 1;
  }
  if ( dword_7089A8 )
    v2 |= 0x100u;
  if ( dword_7089AC )
    v2 |= 0x200u;
  if ( dword_7089A8 )
    --dword_7089A8;
  Mouse_tMouse.bButton = v2;
  if ( dword_7089AC )
    --dword_7089AC;
}

// source: b/2/pc/pc_mouse.c:402  [size]
void __cdecl Mouse_UpdateCapabilities()
{
  struct DIDEVCAPS sMouseCaps; // [esp+0h] [ebp-2Ch] BYREF

  sMouseCaps.dwSize = 44;
  if ( (*(int (__stdcall **)(int, struct DIDEVCAPS *))(*(_DWORD *)dword_7089C0 + 12))(dword_7089C0, &sMouseCaps) )
  {
    LDebug_Error(&g_zFileName.atPictureResources[30].zResourceFilename[56]);
    abort();
  }
  Mouse_tMouse.isConnected = 1;
  Mouse_tMouse.nButton = sMouseCaps.dwButtons;
}

// source: b/2/pc/pc_mouse.c:430  [size~]
void __cdecl Mouse_Open()
{
  dword_7089C0 = 0;
  if ( AppContext_tAppContext.isServer )
  {
    Mouse_tMouse.isConnected = 0;
    Mouse_tMouse.nButton = 0;
  }
  else
  {
    if ( Keyboard_lpDIObject->lpVtbl->CreateDevice(
           Keyboard_lpDIObject,
           &CLSID_GUID_SysMouse,
           (LPDIRECTINPUTDEVICE8A *)&dword_7089C0,
           nullptr) )
    {
      LDebug_Error(&g_zFileName.atPictureResources[29].zResourceFilename[56]);
      goto LABEL_4;
    }
    if ( (*(int (__stdcall **)(int, struct _DIDATAFORMAT *))(*(_DWORD *)dword_7089C0 + 44))(
           dword_7089C0,
           &c_dfDIMouse2_67598c) )
    {
      LDebug_Error(&g_zFileName.atPictureResources[29].zResourceFilename[16]);
      goto LABEL_4;
    }
    if ( (*(int (__stdcall **)(int, struct HWND__ *, int))(*(_DWORD *)dword_7089C0 + 52))(
           dword_7089C0,
           AppContext_tAppContext.hWnd,
           ((AppContext_tAppContext.isGermany != false) + 1) | 4) )
    {
      LDebug_Error(&g_zFileName.atPictureResources[28].zResourceFilename[40]);
LABEL_4:
      abort();
    }
    Mouse_UpdateCapabilities();
  }
  if ( AppContext_tAppContext.isServer == false )
    Main_RegisterWinProcCallback(Mouse_WinProcCB);
}

// source: b/2/pc/pc_mouse.c:497  [size]
void __cdecl Mouse_Close()
{
  struct WinProcCBNode_s *ptHead; // eax
  struct WinProcCBNode_s *ptNext; // ecx

  if ( Keyboard_lpDIObject )
  {
    if ( dword_7089C0 )
    {
      (*(void (__stdcall **)(int))(*(_DWORD *)dword_7089C0 + 32))(dword_7089C0);
      (*(void (__stdcall **)(int))(*(_DWORD *)dword_7089C0 + 8))(dword_7089C0);
      dword_7089C0 = 0;
    }
  }
  ptHead = Main_tWinProcCBList.ptHead;
  ptNext = Main_tWinProcCBList.ptHead->ptNext;
  if ( Main_tWinProcCBList.ptHead->ptNext )
  {
    while ( ptHead->pfWinProcCB != Mouse_WinProcCB )
    {
      ptHead = ptNext;
      ptNext = ptNext->ptNext;
      if ( !ptNext )
        return;
    }
    Node_Remove(ptHead)[2] = nullptr;
  }
}
