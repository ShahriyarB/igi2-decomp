/* b/2/keyboardbuffer.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: b/2/keyboardbuffer.c:64  [anchor-mhash]
void __cdecl KeyboardBuffer_Init(struct QKeyboardBuffer_s *ptKeyboardBuffer)
{
  memset(ptKeyboardBuffer, 0, sizeof(struct QKeyboardBuffer_s));
  ptKeyboardBuffer->nKeysInBuffer = 0;
  ptKeyboardBuffer->nBufferSize = 256;
}

// source: b/2/keyboardbuffer.c:85  [anchor-mhash]
int __cdecl KeyboardBuffer_PutChar(int hHandle, int nChar)
{
  if ( !hHandle || KeyboardBuffer_anStack[KeyboardBuffer_nSP] == hHandle )
  {
    hHandle = KeyboardBuffer_tKeyboardBuffer.nKeysInBuffer;
    if ( KeyboardBuffer_tKeyboardBuffer.nKeysInBuffer < KeyboardBuffer_tKeyboardBuffer.nBufferSize )
      KeyboardBuffer_tKeyboardBuffer.anKey[KeyboardBuffer_tKeyboardBuffer.nKeysInBuffer++] = nChar;
  }
  return hHandle;
}

// source: b/2/keyboardbuffer.c:112  [anchor-mhash]
int __cdecl KeyboardBuffer_GetChar(int hHandle)
{
  int nKeysInBuffer; // esi
  int result; // eax
  int v3; // edx
  int *anKey; // ecx

  if ( KeyboardBuffer_anStack[KeyboardBuffer_nSP] != hHandle )
    return 0;
  nKeysInBuffer = KeyboardBuffer_tKeyboardBuffer.nKeysInBuffer;
  if ( !KeyboardBuffer_tKeyboardBuffer.nKeysInBuffer )
    return 0;
  result = KeyboardBuffer_tKeyboardBuffer.anKey[0];
  v3 = 0;
  if ( KeyboardBuffer_tKeyboardBuffer.nKeysInBuffer - 1 > 0 )
  {
    anKey = KeyboardBuffer_tKeyboardBuffer.anKey;
    do
    {
      *anKey = anKey[1];
      nKeysInBuffer = KeyboardBuffer_tKeyboardBuffer.nKeysInBuffer;
      ++v3;
      ++anKey;
    }
    while ( v3 < KeyboardBuffer_tKeyboardBuffer.nKeysInBuffer - 1 );
  }
  KeyboardBuffer_tKeyboardBuffer.nKeysInBuffer = nKeysInBuffer - 1;
  return result;
}

// source: b/2/keyboardbuffer.c:147  [anchor-mhash]
void __cdecl KeyboardBuffer_UnGetChar(int hHandle, int nChar)
{
  int nKeysInBuffer; // ecx
  _DWORD *v3; // eax

  if ( KeyboardBuffer_anStack[KeyboardBuffer_nSP] == hHandle )
  {
    nKeysInBuffer = KeyboardBuffer_tKeyboardBuffer.nKeysInBuffer;
    if ( KeyboardBuffer_tKeyboardBuffer.nKeysInBuffer < KeyboardBuffer_tKeyboardBuffer.nBufferSize )
    {
      if ( KeyboardBuffer_tKeyboardBuffer.nKeysInBuffer )
      {
        v3 = (_DWORD *)(4 * KeyboardBuffer_tKeyboardBuffer.nKeysInBuffer + 129876648);
        do
        {
          *v3-- = KeyboardBuffer_tKeyboardBuffer.anKey[0];
          --nKeysInBuffer;
        }
        while ( nKeysInBuffer );
        nKeysInBuffer = KeyboardBuffer_tKeyboardBuffer.nKeysInBuffer;
      }
      KeyboardBuffer_tKeyboardBuffer.anKey[0] = nChar;
      KeyboardBuffer_tKeyboardBuffer.nKeysInBuffer = nKeysInBuffer + 1;
    }
  }
}

// source: b/2/keyboardbuffer.c:178  [size]
int __cdecl KeyboardBuffer_Acquire()
{
  int result; // eax

  result = KeyboardBuffer_nSP + 1;
  Keyboard_tKeyboard.isLocked = 1;
  KeyboardBuffer_nSP = result;
  KeyboardBuffer_anStack[result] = result;
  KeyboardBuffer_tKeyboardBuffer.nKeysInBuffer = 0;
  return result;
}

// source: b/2/keyboardbuffer.c:196  [anchor-callee]
void __cdecl KeyboardBuffer_Release(int hHandle)
{
  int v1; // eax
  int v2; // ecx
  int v3; // ecx

  v1 = KeyboardBuffer_nSP;
  if ( hHandle == KeyboardBuffer_nSP )
  {
    v2 = *(&KeyboardBuffer_nSP + KeyboardBuffer_nSP);
    v1 = --KeyboardBuffer_nSP;
    if ( v2 < 0 )
    {
      do
        v3 = *(&KeyboardBuffer_nSP + v1--);
      while ( v3 < 0 );
      KeyboardBuffer_nSP = v1;
    }
  }
  else
  {
    KeyboardBuffer_anStack[hHandle] = -1;
  }
  if ( v1 <= 0 )
    Keyboard_tKeyboard.isLocked = 0;
}

// source: b/2/keyboardbuffer.c:229  [anchor-hash]
enum bool __cdecl KeyboardBuffer_IsAcquired()
{
  return KeyboardBuffer_nSP > 0;
}

// source: b/2/keyboardbuffer.c:242  [size]
int __cdecl KeyboardBuffer_GetGlobalHandle()
{
  return 0;
}

// source: b/2/keyboardbuffer.c:255  [size]
void __cdecl KeyboardBuffer_Open()
{
  memset(&KeyboardBuffer_tKeyboardBuffer, 0, sizeof(KeyboardBuffer_tKeyboardBuffer));
  KeyboardBuffer_tKeyboardBuffer.nKeysInBuffer = 0;
  KeyboardBuffer_tKeyboardBuffer.nBufferSize = 256;
  KeyboardBuffer_isCtrl = 0;
  KeyboardBuffer_isAlt = 0;
  KeyboardBuffer_isButton1 = 0;
  KeyboardBuffer_isButton2 = 0;
  KeyboardBuffer_isButton3 = 0;
  KeyboardBuffer_isCharLegal = 1;
  Main_RegisterWinProcCallback(KeyboardBuffer_WinProcHandler);
  KeyboardBuffer_nSP = 0;
  KeyboardBuffer_anStack[0] = 0;
}

// source: b/2/keyboardbuffer.c:271  [size]
void __cdecl KeyboardBuffer_Close()
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
