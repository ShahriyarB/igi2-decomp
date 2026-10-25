/* j/0/menusystem/keyinterface.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/menusystem/keyinterface.c:61  [anchor-mhash]
void __cdecl KeyInterface_AddKeyToBuffer(int nKey)
{
  if ( tKeyboardBuffer.nBuffer < 31 )
  {
    tKeyboardBuffer.anBuffer[(tKeyboardBuffer.nBuffer + tKeyboardBuffer.iBufferIndex) % 32] = nKey;
    ++tKeyboardBuffer.nBuffer;
  }
}

// source: j/0/menusystem/keyinterface.c:87  [anchor-caller]
int __cdecl KeyInterface_WinProcHandler(struct HWND__ *hWnd, unsigned int iMsg, unsigned int wParam, int lParam)
{
  _DWORD *pxObject; // eax
  int result; // eax

  if ( DebugConsoleTask_ptQTaskRef )
  {
    pxObject = DebugConsoleTask_ptQTaskRef->pxObject;
    if ( pxObject )
    {
      if ( pxObject[81] )
        return 0;
    }
  }
  if ( iMsg == 256 )
  {
    switch ( wParam )
    {
      case 8u:
        KeyInterface_AddKeyToBuffer(-5);
        result = 1;
        break;
      case 9u:
        KeyInterface_AddKeyToBuffer(-11);
        return 1;
      case 0x23u:
        KeyInterface_AddKeyToBuffer(-10);
        result = 1;
        break;
      case 0x24u:
        KeyInterface_AddKeyToBuffer(-9);
        result = 1;
        break;
      case 0x25u:
        KeyInterface_AddKeyToBuffer(-1);
        result = 1;
        break;
      case 0x26u:
        KeyInterface_AddKeyToBuffer(-3);
        result = 1;
        break;
      case 0x27u:
        KeyInterface_AddKeyToBuffer(-2);
        result = 1;
        break;
      case 0x28u:
        KeyInterface_AddKeyToBuffer(-4);
        result = 1;
        break;
      case 0x2Eu:
        KeyInterface_AddKeyToBuffer(-6);
        result = 1;
        break;
      default:
        return 1;
    }
  }
  else
  {
    if ( iMsg != 257 )
    {
      if ( iMsg == 258 && wParam != 8 && wParam != 13 && wParam != 27 )
      {
        KeyInterface_AddKeyToBuffer(wParam);
        return 1;
      }
      return 1;
    }
    if ( wParam == 13 )
    {
      KeyInterface_AddKeyToBuffer(-7);
      return 1;
    }
    if ( wParam != 27 )
      return 1;
    if ( !tKeyboardBuffer.isFreezeEscape )
      KeyInterface_AddKeyToBuffer(-8);
    tKeyboardBuffer.isFreezeEscape = 0;
    return 1;
  }
  return result;
}

// source: j/0/menusystem/keyinterface.c:181  [anchor-hash]
void __cdecl KeyInterface_Open()
{
  tKeyboardBuffer.iBufferIndex = 0;
  tKeyboardBuffer.nBuffer = 0;
  tKeyboardBuffer.isKeyboardActive = 1;
  tKeyboardBuffer.isFreezeEscape = 0;
  Main_RegisterWinProcCallback(KeyInterface_WinProcHandler);
}

// source: j/0/menusystem/keyinterface.c:202  [anchor-hash]
void __cdecl KeyInterface_Close()
{
  struct WinProcCBNode_s *ptHead; // eax
  struct WinProcCBNode_s *ptNext; // ecx

  ptHead = Main_tWinProcCBList.ptHead;
  ptNext = Main_tWinProcCBList.ptHead->ptNext;
  if ( Main_tWinProcCBList.ptHead->ptNext )
  {
    while ( ptHead->pfWinProcCB != KeyInterface_WinProcHandler )
    {
      ptHead = ptNext;
      ptNext = ptNext->ptNext;
      if ( !ptNext )
      {
        tKeyboardBuffer.isKeyboardActive = 0;
        return;
      }
    }
    Node_Remove(ptHead)[2] = nullptr;
  }
  tKeyboardBuffer.isKeyboardActive = 0;
}

// source: j/0/menusystem/keyinterface.c:218  [size]
void __cdecl KeyInterface_FlushBuffer()
{
  tKeyboardBuffer.iBufferIndex = 0;
  tKeyboardBuffer.nBuffer = 0;
}

// source: j/0/menusystem/keyinterface.c:233  [anchor-hash]
int __cdecl KeyInterface_GetAsciiCode()
{
  int result; // eax

  result = 0;
  if ( tKeyboardBuffer.nBuffer )
  {
    result = tKeyboardBuffer.anBuffer[tKeyboardBuffer.iBufferIndex++];
    if ( tKeyboardBuffer.iBufferIndex == 32 )
      tKeyboardBuffer.iBufferIndex = 0;
    --tKeyboardBuffer.nBuffer;
  }
  return result;
}

// source: j/0/menusystem/keyinterface.c:267  [size]
int __cdecl KeyInterface_IsCharacterInBuffer()
{
  return tKeyboardBuffer.nBuffer != 0;
}

// source: j/0/menusystem/keyinterface.c:283  [size]
void __cdecl KeyInterface_FreezeEscape()
{
  tKeyboardBuffer.isFreezeEscape = 1;
}
