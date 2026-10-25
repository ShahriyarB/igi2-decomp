/* j/0/computer/computerplanmenu.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/computer/computerplanmenu.c:79  [anchor-mhash]
void __cdecl ComputerLog_ButtonItemActivateCB(
        struct MenuItem_s *ptMenuItem,
        struct MenuItemActivateContext_s *ptMenuItemActivateContext)
{
  struct QTask_s *v2; // edi
  char v3; // al
  unsigned int v4; // eax
  struct QTask_s *ptNext; // eax

  v2 = ComputerPlanMenu_ptQTask;
  if ( ptMenuItem->isActivated && !ptMenuItem->isActive )
    SoundSys_PlaySimpleSoundDefFn("mapcomp_05", 1u, nullptr);
  if ( ptMenuItem->eMenuItem == ptMenuItemActivateContext->eMenuItem )
  {
    v3 = (int)ComputerMenu_ptComputerMenuQTask[1].tQTaskChildren.ptTail & 0x10;
    BYTE1(ptMenuItem[1].tClientRect.vY) = LOBYTE(ptMenuItem[1].tClientRect.vY);
    LOBYTE(ptMenuItem[1].tClientRect.vY) = v3;
    if ( v3 )
    {
      SoundSys_PlaySimpleSoundDefFn("mapcomp_01", 1u, nullptr);
      if ( ptMenuItem->eMenuItem == 5 )
      {
        if ( !BYTE1(ptMenuItem[1].tClientRect.vY) )
        {
          ptNext = v2[1].ptNext;
          if ( ptNext )
            v2[1].ptNext = (struct QTask_s *)((char *)ptNext - 1);
        }
      }
      else if ( ptMenuItem->eMenuItem == 6 && !BYTE1(ptMenuItem[1].tClientRect.vY) )
      {
        v4 = (unsigned int)v2[1].ptNext;
        if ( v4 < ComputerPlan_ptComputerPlanVector->tPrivate.nElements - 1 )
          v2[1].ptNext = (struct QTask_s *)(v4 + 1);
      }
    }
  }
}

// source: j/0/computer/computerplanmenu.c:135  [anchor-caller]
void __cdecl ComputerPlanMenu_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *ScreenMenuItems; // esi
  float vX; // [esp+0h] [ebp-30h]
  float vDisplayWidth; // [esp+28h] [ebp-8h]
  float vDisplayWidtha; // [esp+28h] [ebp-8h]
  float vDisplayHeight; // [esp+2Ch] [ebp-4h]
  float ptQTaska = *(float *)&ptQTask; // [esp+34h] [ebp+4h] ARGSLOT

  vDisplayWidth = (float)Display_tActiveMode.nWidth;
  ComputerPlanMenu_ptQTask = ptQTask;
  vDisplayHeight = (float)Display_tActiveMode.nHeight;
  vDisplayWidtha = vDisplayWidth * 0.14687499403953552;
  ScreenMenuItems = ComputerMenu_CreateScreenMenuItems(nullptr, nullptr, ptQTask, COMPUTERMENU_MAP);
  ptQTaska = vDisplayHeight * 0.14166666567325592;
  ComputerButtonItem_New(
    ScreenMenuItems,
    5,
    0,
    0,
    0,
    0,
    0,
    vDisplayWidtha,
    ptQTaska,
    0,
    nullptr,
    (char *)&g_zInitialValue,
    &ComputerMenu_tComputerMenuResource.tQSpriteArrowUp_1,
    &ComputerMenu_tComputerMenuResource.tQSpriteArrowUp_2,
    &ComputerMenu_tComputerMenuResource.tQSpriteArrowUp_3,
    ComputerLog_ButtonItemActivateCB);
  vX = ptQTaska + 36.0;
  ComputerButtonItem_New(
    ScreenMenuItems,
    6,
    0,
    0,
    0,
    0,
    0,
    vDisplayWidtha,
    vX,
    0,
    nullptr,
    (char *)&g_zInitialValue,
    &ComputerMenu_tComputerMenuResource.tQSpriteArrowDown_1,
    &ComputerMenu_tComputerMenuResource.tQSpriteArrowDown_2,
    &ComputerMenu_tComputerMenuResource.tQSpriteArrowDown_3,
    ComputerLog_ButtonItemActivateCB);
}

// source: j/0/computer/computerplanmenu.c:208  [size]
void __cdecl ComputerPlanMenu_DeleteHandler(struct QTask_s *ptQTask)
{
  ComputerPlanMenu_ptQTask = nullptr;
}

// source: j/0/computer/computerplanmenu.c:224  [size]
void __cdecl ComputerPlanMenu_RunHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptHead; // ecx
  int v2; // edx
  struct QTask_s *v3; // eax
  void (__cdecl *pfHandler)(struct QTask_s *); // eax
  int v5; // edx

  ptHead = ptQTask->tQTaskChildren.ptHead;
  if ( ptHead->ptNext && ptHead )
  {
    v2 = QTask_nProtectedQTaskStackOffset;
    do
    {
      if ( ptHead->ptNext )
        v3 = ptHead->ptNext->ptNext != nullptr ? ptHead->ptNext : nullptr;
      else
        v3 = nullptr;
      QTask_atProtectedQTaskStack[v2].ptQTask = v3;
      pfHandler = (void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[1][ptHead->eQTaskType].pfHandler;
      v5 = v2 + 1;
      QTask_nProtectedQTaskStackOffset = v5;
      if ( pfHandler )
      {
        pfHandler(ptHead);
        v5 = QTask_nProtectedQTaskStackOffset;
      }
      ptHead = (struct QTask_s *)dword_849C7DC[v5];
      v2 = v5 - 1;
      QTask_nProtectedQTaskStackOffset = v2;
    }
    while ( ptHead );
  }
}

// source: j/0/computer/computerplanmenu.c:240  [anchor-mhash]
void __cdecl ComputerPlanMenu_DrawHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptHead; // ecx
  int v2; // edx
  struct QTask_s *v3; // eax
  int v4; // esi
  void (__cdecl *pfHandler)(struct QTask_s *); // eax
  int v6; // edx

  if ( ComputerPlan_ptComputerPlanVector->tPrivate.nElements )
    ((void (__cdecl *)(void *))QTask_aatQTaskFinalEvent[Screen_eDrawQTaskEvent][*((unsigned __int16 *)ComputerPlan_ptComputerPlanVector->tPrivate.papxElement[(int)ptQTask[1].ptNext]
                                                                                + 18)].pfHandler)(ComputerPlan_ptComputerPlanVector->tPrivate.papxElement[(int)ptQTask[1].ptNext]);
  ptHead = ptQTask->tQTaskChildren.ptHead;
  if ( ptHead->ptNext && ptHead )
  {
    v2 = QTask_nProtectedQTaskStackOffset;
    do
    {
      if ( ptHead->ptNext )
        v3 = ptHead->ptNext->ptNext != nullptr ? ptHead->ptNext : nullptr;
      else
        v3 = nullptr;
      v4 = Screen_eDrawQTaskEvent;
      QTask_atProtectedQTaskStack[v2].ptQTask = v3;
      pfHandler = (void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[v4][ptHead->eQTaskType].pfHandler;
      v6 = v2 + 1;
      QTask_nProtectedQTaskStackOffset = v6;
      if ( pfHandler )
      {
        pfHandler(ptHead);
        v6 = QTask_nProtectedQTaskStackOffset;
      }
      ptHead = (struct QTask_s *)dword_849C7DC[v6];
      v2 = v6 - 1;
      QTask_nProtectedQTaskStackOffset = v2;
    }
    while ( ptHead );
  }
}

// source: j/0/computer/computerplanmenu.c:263  [size]
unsigned __int16 __cdecl ComputerPlanMenu_GetQTaskType()
{
  return ComputerPlanMenu_eQTaskType;
}

// source: j/0/computer/computerplanmenu.c:276  [size]
struct QTask_s *__cdecl ComputerPlanMenu_New(struct QTask_s *ptParent)
{
  return QTask_NewFn(ptParent, ComputerPlanMenu_eQTaskType, nullptr);
}

// source: j/0/computer/computerplanmenu.c:289  [anchor-hash]
void __cdecl ComputerPlanMenu_Open()
{
  unsigned __int16 BaseQTaskType; // ax
  unsigned __int16 v1; // si

  BaseQTaskType = QTask_GetBaseQTaskType();
  v1 = QTask_NewQTaskType("ComputerPlanMenu", 44, BaseQTaskType, 0, 0);
  ComputerPlanMenu_eQTaskType = v1;
  QTask_LinkQTaskEventHandlerFn(v1, 0, ComputerPlanMenu_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 2, (void (__cdecl *)(struct QTask_s *))ComputerPlanMenu_DeleteHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 1, ComputerPlanMenu_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, Screen_eDrawQTaskEvent, ComputerPlanMenu_DrawHandler);
}

// source: j/0/computer/computerplanmenu.c:309  [size]
void __cdecl ComputerPlanMenu_Close()
{
  QTask_DeleteQTaskType(ComputerPlanMenu_eQTaskType);
}
