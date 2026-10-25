/* h/0/input.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: h/0/input.c:33  [size]
__int16 __cdecl Input_GetGetInputQTaskEvent()
{
  return Input_eGetInputQTaskEvent;
}

// source: h/0/input.c:47  [anchor-mhash]
void __cdecl Input_Init(
        struct Input_s *ptInput,
        void (__cdecl *pfInputHandler)(struct Input_s *, struct QTask_s *))
{
  ptInput->pfInputHandler = pfInputHandler;
  ptInput->vAnalogX = 0.0;
  ptInput->vAnalogY = 0.0;
  ptInput->vAnalogButton0 = 0.0;
  ptInput->vAnalogButton1 = 0.0;
  ptInput->bPreviousButton = 0;
  ptInput->bCurrentButton = 0;
  ptInput->bEdgeButton = 0;
  memset(ptInput->anButtonRepeat, 0, sizeof(ptInput->anButtonRepeat));
}

// source: h/0/input.c:75  [anchor-mhash]
struct Input_s *__cdecl Input_Run(struct Input_s *ptInput, struct QTask_s *ptQTask)
{
  int bCurrentButton_high; // ecx
  void (__cdecl *pfInputHandler)(struct Input_s *, struct QTask_s *); // eax
  int v5; // ebx
  int bCurrentButton; // edi
  int v7; // eax
  int v8; // ecx
  unsigned __int16 *anButtonRepeat; // esi
  struct Input_s *result; // eax

  bCurrentButton_high = HIDWORD(ptInput->bCurrentButton);
  LODWORD(ptInput->bPreviousButton) = ptInput->bCurrentButton;
  pfInputHandler = ptInput->pfInputHandler;
  HIDWORD(ptInput->bPreviousButton) = bCurrentButton_high;
  if ( pfInputHandler )
    pfInputHandler(ptInput, ptQTask);
  v5 = HIDWORD(ptInput->bCurrentButton);
  bCurrentButton = ptInput->bCurrentButton;
  v7 = bCurrentButton & ~LODWORD(ptInput->bPreviousButton);
  HIDWORD(ptInput->bEdgeButton) = v5 & ~HIDWORD(ptInput->bPreviousButton);
  LODWORD(ptInput->bEdgeButton) = v7;
  v8 = 0;
  anButtonRepeat = ptInput->anButtonRepeat;
  do
  {
    result = (struct Input_s *)(v5 & (1 << v8 >> 31) | bCurrentButton & (1 << v8));
    if ( result )
      ++*anButtonRepeat;
    else
      *anButtonRepeat = 0;
    ++v8;
    ++anButtonRepeat;
  }
  while ( v8 < 64 );
  return result;
}

// source: h/0/input.c:122  [anchor-hash]
struct Input_s *__cdecl Input_InputHandlerPort0(
        struct Input_s *ptInput,
        struct QTask_s *ptQTask)
{
  ptInput->vAnalogX = InputPort_atInputPort[0].tInput.vAnalogX;
  ptInput->vAnalogY = InputPort_atInputPort[0].tInput.vAnalogY;
  ptInput->vAnalogButton0 = InputPort_atInputPort[0].tInput.vAnalogButton0;
  ptInput->vAnalogButton1 = InputPort_atInputPort[0].tInput.vAnalogButton1;
  ptInput->bCurrentButton = InputPort_atInputPort[0].tInput.bCurrentButton;
  return ptInput;
}

// source: h/0/input.c:144  [anchor-mhash]
unsigned __int64 __cdecl Input_GetButtonFromButtonID(int nButton)
{
  unsigned int v1; // ecx

  if ( v1 >= 0x40 )
    return 0;
  else
    return 1LL << v1;
}

// source: h/0/input.c:163  [anchor-mhash]
int __cdecl Input_GetButtonIDFromButton(unsigned __int64 bButton)
{
  unsigned __int64 v1; // kr00_8
  int result; // eax

  v1 = bButton;
  if ( !bButton )
    return -1;
  result = 0;
  while ( (v1 & 1) == 0 )
  {
    ++result;
    v1 >>= 1;
    if ( result >= 64 )
      return -1;
  }
  return result;
}

// source: h/0/input.c:190  [anchor-hash]
void __cdecl Input_Open()
{
  Input_eGetInputQTaskEvent = QTask_NewQTaskEventFn(0, "GetInput");
}

// source: h/0/input.c:206  [size]
void __cdecl Input_Close()
{
  QTask_DeleteQTaskEvent(Input_eGetInputQTaskEvent);
}
