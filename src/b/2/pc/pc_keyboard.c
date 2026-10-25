/* b/2/pc/pc_keyboard.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: b/2/pc/pc_keyboard.c:115  [size~]
int __cdecl Keyboard_WinProcCB(int a1, int a2)
{
  int result; // eax

  switch ( a1 )
  {
    case 17:
    case 18:
      result = (a2 & 0x7F0000 | (a2 >> 1) & 0x800000) >> 16;
      break;
    case 33:
      result = 201;
      break;
    case 34:
      result = 209;
      break;
    case 37:
      result = 203;
      break;
    case 38:
      result = 200;
      break;
    case 39:
      result = 205;
      break;
    case 40:
      result = 208;
      break;
    default:
      result = (a2 >> 16) & 0x7F;
      break;
  }
  return result;
}

int __cdecl pfCB(struct HWND__ *a1, unsigned int a2, unsigned int message, struct HWND__ *hWnd)
{
  int result; // eax

  switch ( a2 )
  {
    case 0x100u:
    case 0x104u:
      Keyboard_anWindowsCurrentKey[Keyboard_WinProcCB(message, (int)hWnd)] = 0x80;
      result = 1;
      break;
    case 0x101u:
    case 0x105u:
      Keyboard_anWindowsCurrentKey[Keyboard_WinProcCB(message, (int)hWnd)] = 0;
      goto LABEL_4;
    default:
LABEL_4:
      result = 1;
      break;
  }
  return result;
}

// source: b/2/pc/pc_keyboard.c:150  [size]
void __cdecl Keyboard_Update()
{
  if ( Keyboard_tKeyboard.isConnected )
  {
    if ( !Keyboard_isAcquired )
    {
      if ( Keyboard_lpDIDKeyboard->lpVtbl->Acquire(Keyboard_lpDIDKeyboard) )
        return;
      Keyboard_isAcquired = 1;
    }
    qmemcpy(Keyboard_tKeyboard.anPreviousKey, Keyboard_tKeyboard.anCurrentKey, sizeof(Keyboard_tKeyboard.anPreviousKey));
    if ( AppContext_tAppContext.isGermany )
    {
      qmemcpy(
        Keyboard_tKeyboard.anAlwaysCurrentKey,
        Keyboard_anWindowsCurrentKey,
        sizeof(Keyboard_tKeyboard.anAlwaysCurrentKey));
    }
    else if ( Keyboard_lpDIDKeyboard->lpVtbl->GetDeviceState(
                Keyboard_lpDIDKeyboard,
                256,
                Keyboard_tKeyboard.anAlwaysCurrentKey)
           && (Keyboard_lpDIDKeyboard->lpVtbl->Acquire(Keyboard_lpDIDKeyboard)
            || Keyboard_lpDIDKeyboard->lpVtbl->GetDeviceState(
                 Keyboard_lpDIDKeyboard,
                 256,
                 Keyboard_tKeyboard.anAlwaysCurrentKey)) )
    {
      memset(Keyboard_tKeyboard.anAlwaysCurrentKey, 0, sizeof(Keyboard_tKeyboard.anAlwaysCurrentKey));
    }
    if ( Keyboard_tKeyboard.isLocked )
      memset(Keyboard_tKeyboard.anCurrentKey, 0, sizeof(Keyboard_tKeyboard.anCurrentKey));
    else
      qmemcpy(
        Keyboard_tKeyboard.anCurrentKey,
        Keyboard_tKeyboard.anAlwaysCurrentKey,
        sizeof(Keyboard_tKeyboard.anCurrentKey));
  }
}

// source: b/2/pc/pc_keyboard.c:222  [size]
enum bool __cdecl Keyboard_IsNumberActive()
{
  return (Keyboard_tKeyboard.anCurrentKey[2] & 0x80u) != 0
      || (Keyboard_tKeyboard.anCurrentKey[79] & 0x80) != 0
      || (Keyboard_tKeyboard.anCurrentKey[3] & 0x80) != 0
      || (Keyboard_tKeyboard.anCurrentKey[80] & 0x80) != 0
      || (Keyboard_tKeyboard.anCurrentKey[4] & 0x80) != 0
      || (Keyboard_tKeyboard.anCurrentKey[81] & 0x80) != 0
      || (Keyboard_tKeyboard.anCurrentKey[5] & 0x80) != 0
      || (Keyboard_tKeyboard.anCurrentKey[75] & 0x80) != 0
      || (Keyboard_tKeyboard.anCurrentKey[6] & 0x80) != 0
      || (Keyboard_tKeyboard.anCurrentKey[76] & 0x80) != 0
      || (Keyboard_tKeyboard.anCurrentKey[7] & 0x80) != 0
      || (Keyboard_tKeyboard.anCurrentKey[77] & 0x80) != 0
      || (Keyboard_tKeyboard.anCurrentKey[8] & 0x80) != 0
      || (Keyboard_tKeyboard.anCurrentKey[71] & 0x80) != 0
      || (Keyboard_tKeyboard.anCurrentKey[9] & 0x80) != 0
      || (Keyboard_tKeyboard.anCurrentKey[72] & 0x80) != 0
      || (Keyboard_tKeyboard.anCurrentKey[10] & 0x80) != 0
      || (Keyboard_tKeyboard.anCurrentKey[73] & 0x80) != 0
      || (Keyboard_tKeyboard.anCurrentKey[11] & 0x80) != 0
      || (Keyboard_tKeyboard.anCurrentKey[82] & 0x80) != 0;
}

// source: b/2/pc/pc_keyboard.c:246  [size]
void __cdecl Keyboard_UpdateCapabilities()
{
  Keyboard_tKeyboard.isConnected = 1;
}

// source: b/2/pc/pc_keyboard.c:264  [size]
void __cdecl Keyboard_SetLock(int isLocked)
{
  Keyboard_tKeyboard.isLocked = isLocked;
}

char *__cdecl sub_44BFC0(int a1, char *a2, int a3, size_t Count)
{
  _DWORD v5[80]; // [esp+8h] [ebp-140h] BYREF

  memset(v5, 0, 0x13Cu);
  *a2 = 0;
  v5[0] = 316;
  if ( a1 && !(*(int (__stdcall **)(int, _DWORD *, int, int))(*(_DWORD *)a1 + 56))(a1, v5, a3, 1) )
    strncpy(a2, (char *)&v5[8], Count);
  return a2;
}

// source: b/2/pc/pc_keyboard.c:279  [size]
void __cdecl Keyboard_Open()
{
  struct HINSTANCE__ *LibraryA; // eax
  struct _GUID GUIDKeyboard; // [esp+14h] [ebp-10h] BYREF

  if ( AppContext_tAppContext.isServer )
  {
    memset(Keyboard_anWindowsCurrentKey, 0, sizeof(Keyboard_anWindowsCurrentKey));
    Keyboard_isAcquired = 0;
    Keyboard_tKeyboard.isConnected = 0;
    Keyboard_tKeyboard.isLocked = 1;
  }
  else
  {
    GUIDKeyboard = CLSID_GUID_SysKeyboard;
    LibraryA = LoadLibraryA("dinput8.dll");
    Keyboard_hDINPUT8DLL = LibraryA;
    if ( !LibraryA )
    {
      LDebug_Error("Failed to load dinput8.dll\nPlease reinstall Microsoft DirectX");
      goto LABEL_4;
    }
    Keyboard_pfDirectInput8Create = (int (__stdcall *)(struct HINSTANCE__ *, unsigned int, struct _GUID *const, void **, struct IUnknown *))GetProcAddress(LibraryA, "DirectInput8Create");
    if ( Keyboard_pfDirectInput8Create(
           AppContext_tAppContext.hInstance,
           2048u,
           &CLSID_IDirectInput8A,
           (void **)&Keyboard_lpDIObject,
           nullptr) )
    {
      LDebug_Error("Could not create DirectInput keyboard object!");
      goto LABEL_4;
    }
    if ( Keyboard_lpDIObject->lpVtbl->CreateDevice(Keyboard_lpDIObject, &GUIDKeyboard, &Keyboard_lpDIDKeyboard, nullptr) )
    {
      LDebug_Error("Could not create DirectInput device keyboard!");
      goto LABEL_4;
    }
    if ( Keyboard_lpDIDKeyboard->lpVtbl->SetDataFormat(Keyboard_lpDIDKeyboard, &c_dfDIKeyboard_675b94) )
    {
      LDebug_Error("Could not set data format for keyboard!");
      goto LABEL_4;
    }
    if ( Keyboard_lpDIDKeyboard->lpVtbl->SetCooperativeLevel(Keyboard_lpDIDKeyboard, AppContext_tAppContext.hWnd, 6) )
    {
      LDebug_Error("Could not set cooperative level for keyboard!");
LABEL_4:
      abort();
    }
    if ( !Keyboard_lpDIDKeyboard->lpVtbl->Acquire(Keyboard_lpDIDKeyboard) )
      Keyboard_isAcquired = 1;
    Keyboard_tKeyboard.isConnected = 1;
    Keyboard_tKeyboard.isLocked = 0;
    memset(Keyboard_anWindowsCurrentKey, 0, sizeof(Keyboard_anWindowsCurrentKey));
    Main_RegisterWinProcCallback((int (__cdecl *)(struct HWND__ *, unsigned int, unsigned int, int))pfCB);
  }
}

// source: b/2/pc/pc_keyboard.c:364  [size]
void __cdecl Keyboard_Close()
{
  struct IDirectInput8A *v0; // ecx
  struct WinProcCBNode_s *ptHead; // eax
  struct WinProcCBNode_s *ptNext; // ecx

  if ( AppContext_tAppContext.isServer == false )
  {
    v0 = Keyboard_lpDIObject;
    if ( Keyboard_lpDIObject )
    {
      if ( Keyboard_lpDIDKeyboard )
      {
        Keyboard_lpDIDKeyboard->lpVtbl->Unacquire(Keyboard_lpDIDKeyboard);
        Keyboard_lpDIDKeyboard->lpVtbl->Release(Keyboard_lpDIDKeyboard);
        v0 = Keyboard_lpDIObject;
        Keyboard_lpDIDKeyboard = nullptr;
      }
      v0->lpVtbl->Release(v0);
      Keyboard_lpDIObject = nullptr;
    }
    FreeLibrary(Keyboard_hDINPUT8DLL);
    ptHead = Main_tWinProcCBList.ptHead;
    ptNext = Main_tWinProcCBList.ptHead->ptNext;
    if ( Main_tWinProcCBList.ptHead->ptNext )
    {
      while ( (int (__cdecl *)(struct HWND__ *, unsigned int, unsigned int, struct HWND__ *))ptHead->pfWinProcCB != pfCB )
      {
        ptHead = ptNext;
        ptNext = ptNext->ptNext;
        if ( !ptNext )
          return;
      }
      Node_Remove(ptHead)[2] = nullptr;
    }
  }
}
