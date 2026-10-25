/* h/0/inputport.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: h/0/inputport.c:44  [anchor-mhash]
void __cdecl InputPort_InputHandler(struct Input_s *ptInput, struct QTask_s *ptQTask)
{
  double v2; // st7
  float *v3; // ecx
  struct RemapButton_t *patRemapButton; // eax
  int v5; // edi
  bool v6; // zf
  enum InputPortDevice_e eAnalogInputPortDevice; // eax
  double v8; // st6
  double v9; // st6
  double v10; // st6
  double vX; // st6
  double v12; // st6
  double v13; // st6
  double v14; // st6
  double v15; // st6
  double v16; // st6
  double v17; // st6
  double v18; // st6
  double v19; // st6
  double v20; // st6
  double v21; // st6
  double v22; // st6
  double v23; // st6
  double v24; // st7
  unsigned int vAnalogX; // [esp+10h] [ebp-18h]
  float vAnalogXa; // [esp+10h] [ebp-18h]
  float vAnalogXb; // [esp+10h] [ebp-18h]
  float vAnalogXc; // [esp+10h] [ebp-18h]
  float vAnalogXd; // [esp+10h] [ebp-18h]
  float vAnalogXe; // [esp+10h] [ebp-18h]
  float vAnalogY; // [esp+14h] [ebp-14h]
  float vAnalogYa; // [esp+14h] [ebp-14h]
  float vAnalogButton1; // [esp+18h] [ebp-10h]
  float vAnalogButton1a; // [esp+18h] [ebp-10h]
  float vAnalogButton0; // [esp+1Ch] [ebp-Ch]
  int bCurrentButton_4; // [esp+24h] [ebp-4h]

  v2 = 0.0;
  v3 = (float *)(InputPort_eCurrentPort << 8);
  patRemapButton = InputPort_atInputPort[InputPort_eCurrentPort].patRemapButton;
  v5 = 0;
  bCurrentButton_4 = 0;
  vAnalogY = 0.0;
  vAnalogButton0 = 0.0;
  vAnalogButton1 = 0.0;
  if ( (int)InputPort_atInputPort[InputPort_eCurrentPort].nRemapButtons > 0 )
  {
    vAnalogX = InputPort_atInputPort[InputPort_eCurrentPort].nRemapButtons;
    while ( patRemapButton->eInputPortDevice != INPUTPORT_DEVICE_KEYBOARD )
    {
      if ( patRemapButton->eInputPortDevice == INPUTPORT_DEVICE_JOYPAD )
      {
        v6 = (Joypad_atJoypad[InputPort_eCurrentPort].bButton & patRemapButton->nDeviceSource) == 0;
        goto LABEL_9;
      }
      if ( patRemapButton->eInputPortDevice == INPUTPORT_DEVICE_MOUSE )
      {
        v6 = (Mouse_tMouse.bButton & patRemapButton->nDeviceSource) == 0;
        goto LABEL_9;
      }
LABEL_11:
      ++patRemapButton;
      if ( !--vAnalogX )
        goto LABEL_12;
    }
    v6 = (Keyboard_tKeyboard.anCurrentKey[patRemapButton->nDeviceSource] & 0x80u) == 0;
LABEL_9:
    if ( !v6 )
    {
      v5 |= LODWORD(patRemapButton->bInputButton);
      bCurrentButton_4 |= HIDWORD(patRemapButton->bInputButton);
    }
    goto LABEL_11;
  }
LABEL_12:
  eAnalogInputPortDevice = InputPort_atInputPort[InputPort_eCurrentPort].eAnalogInputPortDevice;
  if ( eAnalogInputPortDevice == INPUTPORT_DEVICE_JOYPAD )
  {
    v2 = Joypad_atJoypad[InputPort_eCurrentPort].vAnalogX;
    vAnalogY = Joypad_atJoypad[InputPort_eCurrentPort].vAnalogY;
    vAnalogButton0 = Joypad_atJoypad[InputPort_eCurrentPort].vAnalogButton0;
    vAnalogButton1 = Joypad_atJoypad[InputPort_eCurrentPort].vAnalogButton1;
  }
  else if ( eAnalogInputPortDevice == INPUTPORT_DEVICE_MOUSE )
  {
    v2 = Mouse_tMouse.vAnalogX;
    vAnalogY = Mouse_tMouse.vAnalogY;
  }
  if ( (v5 & 0x10) != 0 )
  {
    v8 = -InputPort_atInputPort[InputPort_eCurrentPort].vMaxX;
    if ( v8 <= InputPort_atInputPort[InputPort_eCurrentPort].vX )
    {
      if ( v8 < InputPort_atInputPort[InputPort_eCurrentPort].vX )
      {
        v10 = InputPort_atInputPort[InputPort_eCurrentPort].vX - InputPort_atInputPort[InputPort_eCurrentPort].vActiveX;
        InputPort_atInputPort[InputPort_eCurrentPort].vX = v10;
        vAnalogXb = -v3[34790688];
        if ( v10 < vAnalogXb )
          *(float *)((char *)&InputPort_atInputPort[0].vX + (_DWORD)v3) = vAnalogXb;
      }
    }
    else
    {
      v9 = InputPort_atInputPort[InputPort_eCurrentPort].vActiveX + InputPort_atInputPort[InputPort_eCurrentPort].vX;
      InputPort_atInputPort[InputPort_eCurrentPort].vX = v9;
      vAnalogXa = -v3[34790688];
      if ( v9 > vAnalogXa )
        *(float *)((char *)&InputPort_atInputPort[0].vX + (_DWORD)v3) = vAnalogXa;
    }
  }
  else
  {
    vX = InputPort_atInputPort[InputPort_eCurrentPort].vX;
    if ( (v5 & 0x20) == 0 )
    {
      if ( vX >= 0.0 )
      {
        if ( InputPort_atInputPort[InputPort_eCurrentPort].vX <= 0.0 )
          goto LABEL_36;
        v15 = InputPort_atInputPort[InputPort_eCurrentPort].vX - InputPort_atInputPort[InputPort_eCurrentPort].vPassiveX;
        InputPort_atInputPort[InputPort_eCurrentPort].vX = v15;
        if ( v15 >= 0.0 )
          goto LABEL_36;
      }
      else
      {
        v14 = InputPort_atInputPort[InputPort_eCurrentPort].vPassiveX + InputPort_atInputPort[InputPort_eCurrentPort].vX;
        InputPort_atInputPort[InputPort_eCurrentPort].vX = v14;
        if ( v14 <= 0.0 )
          goto LABEL_36;
      }
      *(float *)((char *)&InputPort_atInputPort[0].vX + (_DWORD)v3) = 0.0;
      goto LABEL_36;
    }
    if ( vX >= InputPort_atInputPort[InputPort_eCurrentPort].vMaxX )
    {
      if ( InputPort_atInputPort[InputPort_eCurrentPort].vX > (double)InputPort_atInputPort[InputPort_eCurrentPort].vMaxX )
      {
        v13 = InputPort_atInputPort[InputPort_eCurrentPort].vX - InputPort_atInputPort[InputPort_eCurrentPort].vActiveX;
        InputPort_atInputPort[InputPort_eCurrentPort].vX = v13;
        if ( v13 < v3[34790688] )
          *(float *)((char *)&InputPort_atInputPort[0].vX + (_DWORD)v3) = *(float *)((char *)&InputPort_atInputPort[0].vMaxX
                                                                                   + (_DWORD)v3);
      }
    }
    else
    {
      v12 = InputPort_atInputPort[InputPort_eCurrentPort].vActiveX + InputPort_atInputPort[InputPort_eCurrentPort].vX;
      InputPort_atInputPort[InputPort_eCurrentPort].vX = v12;
      if ( v12 > v3[34790688] )
        *(float *)((char *)&InputPort_atInputPort[0].vX + (_DWORD)v3) = *(float *)((char *)&InputPort_atInputPort[0].vMaxX
                                                                                 + (_DWORD)v3);
    }
  }
LABEL_36:
  if ( (v5 & 0x40) != 0 )
  {
    v16 = -v3[34790688];
    if ( v16 <= v3[34790685] )
    {
      if ( v16 < v3[34790685] )
      {
        v18 = v3[34790685] - v3[34790693];
        v3[34790685] = v18;
        vAnalogXd = -v3[34790688];
        if ( v18 < vAnalogXd )
          *(float *)((char *)&InputPort_atInputPort[0].vY + (_DWORD)v3) = vAnalogXd;
      }
    }
    else
    {
      v17 = v3[34790693] + v3[34790685];
      v3[34790685] = v17;
      vAnalogXc = -v3[34790688];
      if ( v17 > vAnalogXc )
        *(float *)((char *)&InputPort_atInputPort[0].vY + (_DWORD)v3) = vAnalogXc;
    }
  }
  else
  {
    v19 = v3[34790685];
    if ( (v5 & 0x80) == 0 )
    {
      if ( v19 >= 0.0 )
      {
        if ( v3[34790685] <= 0.0 )
          goto LABEL_56;
        v23 = v3[34790685] - v3[34790697];
        v3[34790685] = v23;
        if ( v23 >= 0.0 )
          goto LABEL_56;
      }
      else
      {
        v22 = v3[34790697] + v3[34790685];
        v3[34790685] = v22;
        if ( v22 <= 0.0 )
          goto LABEL_56;
      }
      *(float *)((char *)&InputPort_atInputPort[0].vY + (_DWORD)v3) = 0.0;
      goto LABEL_56;
    }
    if ( v19 >= v3[34790688] )
    {
      if ( v3[34790685] > (double)v3[34790688] )
      {
        v21 = v3[34790685] - v3[34790693];
        v3[34790685] = v21;
        if ( v21 < v3[34790688] )
          *(float *)((char *)&InputPort_atInputPort[0].vY + (_DWORD)v3) = *(float *)((char *)&InputPort_atInputPort[0].vMaxX
                                                                                   + (_DWORD)v3);
      }
    }
    else
    {
      v20 = v3[34790693] + v3[34790685];
      v3[34790685] = v20;
      if ( v20 > v3[34790688] )
        *(float *)((char *)&InputPort_atInputPort[0].vY + (_DWORD)v3) = *(float *)((char *)&InputPort_atInputPort[0].vMaxX
                                                                                 + (_DWORD)v3);
    }
  }
LABEL_56:
  vAnalogXe = v2 + v3[34790684];
  vAnalogYa = vAnalogY + v3[34790685];
  if ( vAnalogXe >= -1.0 )
  {
    if ( vAnalogXe > 1.0 )
      vAnalogXe = 1.0;
  }
  else
  {
    vAnalogXe = -1.0;
  }
  if ( vAnalogYa >= -1.0 )
  {
    if ( vAnalogYa > 1.0 )
      vAnalogYa = 1.0;
  }
  else
  {
    vAnalogYa = -1.0;
  }
  v24 = vAnalogButton0 + v3[34790686];
  vAnalogButton1a = vAnalogButton1 + v3[34790687];
  if ( v24 >= 0.0 )
  {
    if ( v24 > 1.0 )
      v24 = 1.0;
  }
  else
  {
    v24 = 0.0;
  }
  ptInput->vAnalogX = vAnalogXe;
  LODWORD(ptInput->bCurrentButton) = v5;
  ptInput->vAnalogButton0 = v24;
  ptInput->vAnalogY = vAnalogYa;
  ptInput->vAnalogButton1 = vAnalogButton1a;
  HIDWORD(ptInput->bCurrentButton) = bCurrentButton_4;
}

// source: h/0/inputport.c:199  [size~]
void __cdecl InputPort_RunHandler(struct QTask_s *ptQTask)
{
  enum InputPort_e v1; // edi
  struct Input_s *p_tInput; // esi
  enum bool v3; // [esp+0h] [ebp-Ch]

  Keyboard_Update();
  sub_4274B0();
  Mouse_Update(v3);
  Joypad_Update();
  v1 = INPUTPORT_0;
  p_tInput = &InputPort_atInputPort[0].tInput;
  do
  {
    if ( *(_DWORD *)&p_tInput[-1].anButtonRepeat[24] )
    {
      InputPort_eCurrentPort = v1;
      Input_Run(p_tInput, ptQTask);
    }
    p_tInput = (struct Input_s *)((char *)p_tInput + 256);
    ++v1;
  }
  while ( (int)p_tInput < 139163824 );
}

// source: h/0/inputport.c:241  [anchor-mhash]
void __cdecl InputPort_Update(struct QTask_s *ptQTask)
{
  enum InputPort_e v1; // edi
  struct Input_s *p_tInput; // esi

  v1 = INPUTPORT_0;
  p_tInput = &InputPort_atInputPort[0].tInput;
  do
  {
    if ( *(_DWORD *)&p_tInput[-1].anButtonRepeat[24] )
    {
      InputPort_eCurrentPort = v1;
      Input_Run(p_tInput, ptQTask);
    }
    p_tInput = (struct Input_s *)((char *)p_tInput + 256);
    ++v1;
  }
  while ( (int)p_tInput < 139163824 );
}

// source: h/0/inputport.c:269  [anchor-hash]
void __cdecl InputPort_Open()
{
  unsigned __int16 BaseQTaskType; // ax

  BaseQTaskType = QTask_GetBaseQTaskType();
  InputPort_eQTaskType = QTask_NewQTaskType("InputPort", 40, BaseQTaskType, 0, 0);
  QTask_LinkQTaskEventHandlerNoContextFn(InputPort_eQTaskType, 1, InputPort_RunHandler);
  InputPort_atInputPort[0].isActive = false;
  InputPort_atInputPort[1].isActive = false;
  InputPort_atInputPort[2].isActive = false;
  InputPort_atInputPort[3].isActive = false;
}

// source: h/0/inputport.c:294  [size]
void __cdecl InputPort_Close()
{
  QTask_DeleteQTaskType(InputPort_eQTaskType);
}

// source: h/0/inputport.c:308  [size]
struct QTask_s *__cdecl InputPort_New(struct QTask_s *ptParent)
{
  return QTask_NewFn(ptParent, InputPort_eQTaskType, nullptr);
}

// source: h/0/inputport.c:343  [anchor-callee]
unsigned int __cdecl InputPort_Init(
        enum InputPort_e eInputPort,
        unsigned int nRemapButtons,
        struct RemapButton_t *patRemapButton,
        enum InputPortDevice_e eAnalogInputPortDevice,
        float vMaxX,
        float vActiveX,
        float vPassiveX,
        float vMaxY,
        float vActiveY,
        float vPassiveY,
        float vMax0,
        float vActive0,
        float vPassive0,
        float vMax1,
        float vActive1,
        float vPassive1)
{
  enum InputPort_e v16; // edx

  v16 = eInputPort << 8;
  *(struct RemapButton_t **)((char *)&InputPort_atInputPort[0].patRemapButton + v16) = patRemapButton;
  *(float *)((char *)&InputPort_atInputPort[0].vMaxX + v16) = vMaxX;
  *(float *)((char *)&InputPort_atInputPort[0].vMaxY + v16) = vMaxX;
  *(float *)((char *)&InputPort_atInputPort[0].vMax0 + v16) = vMax0;
  *(float *)((char *)&InputPort_atInputPort[0].vMax1 + v16) = vMax1;
  *(float *)((char *)&InputPort_atInputPort[0].vActiveX + v16) = vActiveX;
  *(float *)((char *)&InputPort_atInputPort[0].vActiveY + v16) = vActiveY;
  *(float *)((char *)&InputPort_atInputPort[0].vActive0 + v16) = vActive0;
  *(float *)((char *)&InputPort_atInputPort[0].vActive1 + v16) = vActive1;
  *(float *)((char *)&InputPort_atInputPort[0].vPassiveX + v16) = vPassiveX;
  *(float *)((char *)&InputPort_atInputPort[0].vPassiveY + v16) = vPassiveY;
  *(unsigned int *)((char *)&InputPort_atInputPort[0].nRemapButtons + v16) = nRemapButtons;
  *(float *)((char *)&InputPort_atInputPort[0].vPassive0 + v16) = vPassive0;
  *(enum InputPortDevice_e *)((char *)&InputPort_atInputPort[0].eAnalogInputPortDevice + v16) = eAnalogInputPortDevice;
  *(float *)((char *)&InputPort_atInputPort[0].vPassive1 + v16) = vPassive1;
  *(float *)((char *)&InputPort_atInputPort[0].vX + v16) = 0.0;
  *(float *)((char *)&InputPort_atInputPort[0].vY + v16) = 0.0;
  *(float *)((char *)&InputPort_atInputPort[0].v0 + v16) = 0.0;
  *(void (__cdecl **)(struct Input_s *, struct QTask_s *))((char *)&InputPort_atInputPort[0].tInput.pfInputHandler + v16) = InputPort_InputHandler;
  *(float *)((char *)&InputPort_atInputPort[0].tInput.vAnalogX + v16) = 0.0;
  *(float *)((char *)&InputPort_atInputPort[0].tInput.vAnalogY + v16) = 0.0;
  *(float *)((char *)&InputPort_atInputPort[0].tInput.vAnalogButton0 + v16) = 0.0;
  *(float *)((char *)&InputPort_atInputPort[0].tInput.vAnalogButton1 + v16) = 0.0;
  *(_DWORD *)((char *)&InputPort_atInputPort[0].tInput.bPreviousButton + v16) = 0;
  *(_DWORD *)((char *)&InputPort_atInputPort[0].tInput.bPreviousButton + v16 + 4) = 0;
  *(_DWORD *)((char *)&InputPort_atInputPort[0].tInput.bCurrentButton + v16) = 0;
  *(_DWORD *)((char *)&InputPort_atInputPort[0].tInput.bCurrentButton + v16 + 4) = 0;
  *(_DWORD *)((char *)&InputPort_atInputPort[0].tInput.bEdgeButton + v16) = 0;
  *(_DWORD *)((char *)&InputPort_atInputPort[0].tInput.bEdgeButton + v16 + 4) = 0;
  memset((char *)InputPort_atInputPort[0].tInput.anButtonRepeat + v16, 0, 0x80u);
  return 0;
}
