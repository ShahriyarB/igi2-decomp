/* b/2/pc/pc_keyboardbuffer.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: b/2/pc/pc_keyboardbuffer.c:40  [size~]
int __cdecl KeyboardBuffer_WinProcHandler(struct HWND__ *hWnd, unsigned int iMsg, unsigned int wParam, int lParam)
{
  BOOL v4; // ecx
  int result; // eax
  int v6; // edx
  int nKeysInBuffer; // esi

  v4 = !KeyboardBuffer_isCtrl
    && !KeyboardBuffer_isAlt
    && !KeyboardBuffer_isButton1
    && !KeyboardBuffer_isButton2
    && !KeyboardBuffer_isButton3;
  KeyboardBuffer_isCharLegal = v4;
  if ( iMsg > 0x201 )
  {
    switch ( iMsg )
    {
      case 0x202u:
        KeyboardBuffer_isButton1 = 0;
        result = 1;
        break;
      case 0x204u:
        KeyboardBuffer_isButton2 = 1;
        result = 1;
        break;
      case 0x205u:
        KeyboardBuffer_isButton2 = 0;
        result = 1;
        break;
      case 0x207u:
        KeyboardBuffer_isButton3 = 1;
        result = 1;
        break;
      case 0x208u:
        goto LABEL_17;
      default:
        return 1;
    }
    return result;
  }
  if ( iMsg == 513 )
  {
    KeyboardBuffer_isButton1 = 1;
    return 1;
  }
  if ( iMsg <= 0x102 )
  {
    if ( iMsg == 258 )
    {
      if ( v4 && KeyboardBuffer_tKeyboardBuffer.nKeysInBuffer < KeyboardBuffer_tKeyboardBuffer.nBufferSize )
      {
        KeyboardBuffer_tKeyboardBuffer.anKey[KeyboardBuffer_tKeyboardBuffer.nKeysInBuffer++] = wParam;
        return 1;
      }
      return 1;
    }
    if ( iMsg == 6 )
    {
      KeyboardBuffer_isRightCtrl = 0;
      KeyboardBuffer_isCtrl = 0;
      KeyboardBuffer_isAlt = 0;
      KeyboardBuffer_isButton1 = 0;
      KeyboardBuffer_isButton2 = 0;
      KeyboardBuffer_isCharLegal = 1;
LABEL_17:
      KeyboardBuffer_isButton3 = 0;
      return 1;
    }
    if ( iMsg != 256 )
    {
      if ( iMsg != 257 )
        return 1;
      goto LABEL_24;
    }
LABEL_31:
    switch ( wParam )
    {
      case 0x10u:
        KeyboardBuffer_isShift = 1;
        return 1;
      case 0x11u:
        KeyboardBuffer_isCtrl = 1;
        if ( (lParam & 0x1000000) == 0 )
          return 1;
        KeyboardBuffer_isRightCtrl = 1;
        return 1;
      case 0x12u:
        KeyboardBuffer_isAlt = 1;
        return 1;
      default:
        if ( wParam >= 0xFF )
          return 1;
        v6 = 0;
        if ( KeyboardBuffer_isAlt )
          v6 = 0x40000;
        if ( KeyboardBuffer_isCtrl )
          v6 |= 0x20000u;
        if ( KeyboardBuffer_isShift )
          v6 |= 0x10000u;
        nKeysInBuffer = KeyboardBuffer_tKeyboardBuffer.nKeysInBuffer;
        if ( KeyboardBuffer_tKeyboardBuffer.nKeysInBuffer >= KeyboardBuffer_tKeyboardBuffer.nBufferSize )
          return 1;
        KeyboardBuffer_tKeyboardBuffer.anKey[nKeysInBuffer] = v6 | (Keyboard_WinProcCB(wParam, lParam) << 8);
        ++KeyboardBuffer_tKeyboardBuffer.nKeysInBuffer;
        return 1;
    }
  }
  if ( iMsg == 260 )
    goto LABEL_31;
  if ( iMsg != 261 )
    return 1;
LABEL_24:
  switch ( wParam )
  {
    case 0x10u:
      KeyboardBuffer_isShift = 0;
      return 1;
    case 0x11u:
      KeyboardBuffer_isCtrl = 0;
      if ( (lParam & 0x1000000) == 0 )
        return 1;
      KeyboardBuffer_isRightCtrl = 0;
      return 1;
    case 0x12u:
      KeyboardBuffer_isAlt = 0;
      return 1;
    default:
      return 1;
  }
}

// source: b/2/pc/pc_keyboardbuffer.c:159  [size]
void __cdecl KeyboardBuffer_HardwareOpen()
{
  KeyboardBuffer_isCtrl = 0;
  KeyboardBuffer_isAlt = 0;
  KeyboardBuffer_isButton1 = 0;
  KeyboardBuffer_isButton2 = 0;
  KeyboardBuffer_isButton3 = 0;
  KeyboardBuffer_isCharLegal = 1;
  Main_RegisterWinProcCallback(KeyboardBuffer_WinProcHandler);
}

// source: b/2/pc/pc_keyboardbuffer.c:179  [size]
void __cdecl KeyboardBuffer_HardwareClose()
{
  struct WinProcCBNode_s *ptHead; // eax
  struct WinProcCBNode_s *ptNext; // ecx

  ptHead = Main_tWinProcCBList.ptHead;
  ptNext = Main_tWinProcCBList.ptHead->ptNext;
  if ( Main_tWinProcCBList.ptHead->ptNext )
  {
    while ( ptHead->pfWinProcCB != KeyboardBuffer_WinProcHandler )
    {
      ptHead = ptNext;
      ptNext = ptNext->ptNext;
      if ( !ptNext )
        return;
    }
    Node_Remove(ptHead)[2] = nullptr;
  }
}
