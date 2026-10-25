/* h/0/menuitem.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: h/0/menuitem.c:59  [size]
void __cdecl MenuItem_FindFirstMenuItemCallback(
        struct MenuItem_s *ptMenuItem,
        struct FindMenuItemContext_s *ptContext)
{
  if ( !ptContext->ptMenuItem )
    ptContext->ptMenuItem = ptMenuItem;
}

// source: h/0/menuitem.c:77  [size]
void __cdecl MenuItem_FindMenuItemCallback(struct MenuItem_s *ptMenuItem, struct FindMenuItemContext_s *ptContext)
{
  if ( ptMenuItem->eMenuItem == ptContext->eMenuItem )
    ptContext->ptMenuItem = ptMenuItem;
}

// source: h/0/menuitem.c:96  [size]
void __cdecl MenuItem_ActiveMenuItemCallback(
        struct MenuItem_s *ptMenuItem,
        struct FindMenuItemContext_s *ptContext)
{
  if ( ptMenuItem->isActive )
    ptContext->ptMenuItem = ptMenuItem;
}

// source: h/0/menuitem.c:114  [anchor-mhash]
void __cdecl MenuItem_DisableMenuItemCallback(struct MenuItem_s *ptMenuItem, struct FindMenuItemContext_s *ptContext)
{
  if ( ptMenuItem->eMenuItem == ptContext->eMenuItem )
    ptMenuItem->isDisabled = ptContext->isSomething;
}

// source: h/0/menuitem.c:135  [size]
void __cdecl MenuItem_RunHandler(struct QTask_s *ptQTask)
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

// source: h/0/menuitem.c:148  [anchor-mhash]
void __cdecl MenuItem_UpdateActiveHandler(struct QTask_s *ptQTask, void *pxContext)
{
  char v2; // al
  struct QTask_s *ptHead; // eax
  int v4; // edx
  struct QTask_s *v5; // ecx
  void (__cdecl *pfHandler)(struct QTask_s *, void *); // ecx
  int v7; // edx

  v2 = 1;
  if ( !BYTE1(ptQTask[2].ptPrev) )
    v2 = BYTE2(ptQTask[2].ptPrev);
  BYTE2(ptQTask[2].ptPrev) = v2;
  ptHead = ptQTask->tQTaskChildren.ptHead;
  if ( ptHead->ptNext && ptHead )
  {
    v4 = QTask_nProtectedQTaskStackOffset;
    do
    {
      if ( ptHead->ptNext )
        v5 = ptHead->ptNext->ptNext != nullptr ? ptHead->ptNext : nullptr;
      else
        v5 = nullptr;
      QTask_atProtectedQTaskStack[v4].ptQTask = v5;
      pfHandler = (void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[MenuItem_eUpdateActiveQTaskEvent][ptHead->eQTaskType].pfHandler;
      v7 = v4 + 1;
      QTask_nProtectedQTaskStackOffset = v7;
      if ( pfHandler )
      {
        pfHandler(ptHead, pxContext);
        v7 = QTask_nProtectedQTaskStackOffset;
      }
      ptHead = (struct QTask_s *)dword_849C7DC[v7];
      v4 = v7 - 1;
      QTask_nProtectedQTaskStackOffset = v4;
    }
    while ( ptHead );
  }
  BYTE1(ptQTask[2].ptPrev) = 0;
}

// source: h/0/menuitem.c:166  [size]
void __cdecl MenuItem_DrawHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptHead; // ecx
  int v2; // edx
  struct QTask_s *v3; // eax
  int v4; // esi
  void (__cdecl *pfHandler)(struct QTask_s *); // eax
  int v6; // edx

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

// source: h/0/menuitem.c:179  [anchor-caller]
void __cdecl MenuItem_ActivateMenuItemHandler(struct QTask_s *ptQTask, void *pxContext)
{
  int v2; // eax
  struct QTask_s *ptHead; // eax

  if ( *(struct QReference_s **)pxContext != ptQTask[1].tQTaskRefList.ptMiddle || LOBYTE(ptQTask[2].ptPrev) )
  {
    BYTE2(ptQTask[2].ptPrev) = 0;
  }
  else
  {
    v2 = *((_DWORD *)pxContext + 6);
    if ( (v2 & 1) != 0 )
    {
      MenuItem_Move(ptQTask->ptParent, -3);
      return;
    }
    if ( (v2 & 2) != 0 )
    {
      MenuItem_Move(ptQTask->ptParent, -4);
      return;
    }
    if ( (v2 & 4) != 0 )
    {
      MenuItem_Move(ptQTask->ptParent, -1);
      return;
    }
    if ( (v2 & 8) != 0 )
    {
      MenuItem_Move(ptQTask->ptParent, -2);
      return;
    }
    BYTE1(ptQTask[2].ptPrev) = 1;
  }
  ptHead = ptQTask[2].tQTaskChildren.ptHead;
  if ( ptHead )
    ((void (__cdecl *)(struct QTask_s *, void *))ptHead)(ptQTask, pxContext);
}

// source: h/0/menuitem.c:232  [size]
void __cdecl MenuItem_GetMenuItemHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = ptQTask;
}

// source: h/0/menuitem.c:251  [size]
void __cdecl MenuItem_MenuItemInputHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *ptHead; // esi
  __int16 v3; // ax
  struct QTask_s *v4; // ecx
  int v5; // edx
  void (__cdecl *pfHandler)(struct QTask_s *, void *); // ecx

  ptHead = ptQTask->tQTaskChildren.ptHead;
  if ( ptHead->ptNext && ptHead )
  {
    v3 = MenuItemQTask_eMenuItemInputQTaskEvent;
    do
    {
      if ( ptHead->ptNext )
        v4 = ptHead->ptNext->ptNext != nullptr ? ptHead->ptNext : nullptr;
      else
        v4 = nullptr;
      v5 = QTask_nProtectedQTaskStackOffset;
      QTask_atProtectedQTaskStack[QTask_nProtectedQTaskStackOffset].ptQTask = v4;
      QTask_nProtectedQTaskStackOffset = v5 + 1;
      if ( v3 == 512 )
      {
        v3 = QTask_NewQTaskEventFn(0, "MenuItem Input");
        MenuItemQTask_eMenuItemInputQTaskEvent = v3;
      }
      pfHandler = (void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[v3][ptHead->eQTaskType].pfHandler;
      if ( pfHandler )
      {
        pfHandler(ptHead, pxContext);
        v3 = MenuItemQTask_eMenuItemInputQTaskEvent;
      }
      ptHead = (struct QTask_s *)dword_849C7DC[QTask_nProtectedQTaskStackOffset--];
    }
    while ( ptHead );
  }
}

// source: h/0/menuitem.c:266  [anchor-hash]
void __cdecl MenuItem_Open()
{
  unsigned __int16 BaseQTaskType; // ax
  unsigned __int16 v1; // si
  __int16 v2; // ax

  MenuItem_eGetMenuItemQTaskEvent = QTask_NewQTaskEventFn(0, "GetMenuItem");
  MenuItem_eActivateQTaskEvent = QTask_NewQTaskEventFn(0, "ActivateMenuItem");
  MenuItem_eUpdateActiveQTaskEvent = QTask_NewQTaskEventFn(0, "UpdateActiveMenuItem");
  BaseQTaskType = QTask_GetBaseQTaskType();
  v1 = QTask_NewQTaskType("MenuItem", 92, BaseQTaskType, 0, 0);
  MenuItem_eQTaskType = v1;
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 1, MenuItem_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, Screen_eDrawQTaskEvent, MenuItem_DrawHandler);
  QTask_LinkQTaskEventHandlerFn(
    v1,
    MenuItem_eGetMenuItemQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))MenuItem_GetMenuItemHandler);
  QTask_LinkQTaskEventHandlerFn(v1, MenuItem_eActivateQTaskEvent, MenuItem_ActivateMenuItemHandler);
  v2 = MenuItemQTask_eMenuItemInputQTaskEvent;
  if ( MenuItemQTask_eMenuItemInputQTaskEvent == 512 )
  {
    v2 = QTask_NewQTaskEventFn(0, "MenuItem Input");
    v1 = MenuItem_eQTaskType;
    MenuItemQTask_eMenuItemInputQTaskEvent = v2;
  }
  QTask_LinkQTaskEventHandlerFn(v1, v2, MenuItem_MenuItemInputHandler);
  QTask_LinkQTaskEventHandlerFn(v1, MenuItem_eUpdateActiveQTaskEvent, MenuItem_UpdateActiveHandler);
}

// source: h/0/menuitem.c:295  [size]
void __cdecl MenuItem_Close()
{
  QTask_DeleteQTaskEvent(MenuItem_eGetMenuItemQTaskEvent);
  QTask_DeleteQTaskEvent(MenuItem_eActivateQTaskEvent);
  QTask_DeleteQTaskEvent(MenuItem_eUpdateActiveQTaskEvent);
  QTask_DeleteQTaskType(MenuItem_eQTaskType);
  MenuItem_eQTaskType = 512;
}

// source: h/0/menuitem.c:319  [anchor-callee]
struct QTask_s *__cdecl MenuItem_Enumerate(
        struct QTask_s *ptParent,
        void (__cdecl *pfCallback)(struct MenuItem_s *, void *),
        void *pxContext)
{
  struct QTask_s *result; // eax
  struct QTask_s *v4; // esi
  void (__cdecl *pfHandler)(struct QTask_s *, struct MenuItem_s **); // ecx
  struct MenuItem_s *ptMenuItem; // [esp+4h] [ebp-4h] BYREF

  result = ptParent->tQTaskChildren.ptHead;
  ptMenuItem = nullptr;
  if ( result->ptNext && result )
  {
    do
    {
      if ( result->ptNext )
        v4 = result->ptNext->ptNext != nullptr ? result->ptNext : nullptr;
      else
        v4 = nullptr;
      pfHandler = (void (__cdecl *)(struct QTask_s *, struct MenuItem_s **))QTask_aatQTaskFinalEvent[MenuItem_eGetMenuItemQTaskEvent][result->eQTaskType].pfHandler;
      if ( pfHandler )
      {
        pfHandler(result, &ptMenuItem);
        if ( ptMenuItem )
        {
          pfCallback(ptMenuItem, pxContext);
          ptMenuItem = nullptr;
        }
      }
      result = v4;
    }
    while ( v4 );
  }
  return result;
}

// source: h/0/menuitem.c:360  [anchor-mhash]
struct MenuItem_s *__cdecl MenuItem_GetMenuItem(struct QTask_s *ptParent, int eMenuItem)
{
  struct FindMenuItemContext_s tFindMenuItemContext; // [esp+4h] [ebp-Ch] BYREF

  tFindMenuItemContext.eMenuItem = eMenuItem;
  tFindMenuItemContext.ptMenuItem = nullptr;
  tFindMenuItemContext.isSomething = 0;
  MenuItem_Enumerate(
    ptParent,
    (void (__cdecl *)(struct MenuItem_s *, void *))MenuItem_FindMenuItemCallback,
    &tFindMenuItemContext);
  return tFindMenuItemContext.ptMenuItem;
}

// source: h/0/menuitem.c:380  [anchor-callee]
struct MenuItem_s *__cdecl MenuItem_GetActiveMenuItem(struct QTask_s *ptParent)
{
  struct FindMenuItemContext_s tFindMenuItemContext; // [esp+4h] [ebp-Ch] BYREF

  memset(&tFindMenuItemContext, 0, sizeof(tFindMenuItemContext));
  MenuItem_Enumerate(
    ptParent,
    (void (__cdecl *)(struct MenuItem_s *, void *))MenuItem_ActiveMenuItemCallback,
    &tFindMenuItemContext);
  return tFindMenuItemContext.ptMenuItem;
}

// source: h/0/menuitem.c:398  [anchor-mhash]
int __cdecl MenuItem_Disable(struct QTask_s *ptParent, int eMenuItem, enum bool isDisabled)
{
  struct FindMenuItemContext_s tFindMenuItemContext; // [esp+4h] [ebp-Ch] BYREF

  tFindMenuItemContext.eMenuItem = eMenuItem;
  tFindMenuItemContext.ptMenuItem = nullptr;
  tFindMenuItemContext.isSomething = isDisabled;
  return (int)MenuItem_Enumerate(
                ptParent,
                (void (__cdecl *)(struct MenuItem_s *, void *))MenuItem_DisableMenuItemCallback,
                &tFindMenuItemContext);
}

// source: h/0/menuitem.c:415  [anchor-mhash]
struct MenuItem_s *__cdecl MenuItem_GetFirstMenuItem(struct QTask_s *ptParent)
{
  struct FindMenuItemContext_s tFindMenuItemContext; // [esp+4h] [ebp-Ch] BYREF

  memset(&tFindMenuItemContext, 0, sizeof(tFindMenuItemContext));
  MenuItem_Enumerate(
    ptParent,
    (void (__cdecl *)(struct MenuItem_s *, void *))MenuItem_FindFirstMenuItemCallback,
    &tFindMenuItemContext);
  return tFindMenuItemContext.ptMenuItem;
}

// source: h/0/menuitem.c:438  [anchor-strings]
enum bool __cdecl MenuItem_Move(struct QTask_s *ptParent, int eItem)
{
  #pragma pack(push, 1)
  union
  {
    struct { int v7; };
    struct { char igi2_o1[4]; int v8; };
    struct { char igi2_o2[8]; int v9; };
    struct { char igi2_o3[12]; int v10; };
    struct { char igi2_o4[16]; int v11; };
    struct { char igi2_o5[20]; int v12; };
    struct { char igi2_o6[24]; int pxContext; };
    struct { char igi2_o7[28]; int v14; };
    struct { char igi2_o8[32]; int v15; };
    struct { char igi2_o9[36]; _DWORD v16[7]; };
    char igi2_extent[64];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v3; // edx
  int v5; // edi
  int v6; // edx

  igi2_frame.pxContext = 0;
  igi2_frame.v14 = 0;
  igi2_frame.v15 = 0;
  MenuItem_Enumerate(
    ptParent,
    (void (__cdecl *)(struct MenuItem_s *, void *))MenuItem_ActiveMenuItemCallback,
    &igi2_frame.pxContext);
  igi2_frame.v9 = 0;
  igi2_frame.v8 = 0;
  if ( eItem <= 0 )
  {
    igi2_frame.v7 = 0;
    MenuItem_Enumerate(ptParent, (void (__cdecl *)(struct MenuItem_s *, void *))MenuItem_ActiveMenuItemCallback, &igi2_frame.v7);
    v3 = igi2_frame.v8;
    if ( igi2_frame.v8 )
    {
      v5 = eItem + 4;
      while ( 1 )
      {
        switch ( v5 )
        {
          case 0:
            v6 = *(_DWORD *)(v3 + 72);
            break;
          case 1:
            v6 = *(_DWORD *)(v3 + 68);
            break;
          case 2:
            v6 = *(_DWORD *)(v3 + 80);
            break;
          case 3:
            v6 = *(_DWORD *)(v3 + 76);
            break;
          default:
            LDebug_Error("MenuItem_Move() called with illegal direction parameter.");
            abort();
        }
        if ( !v6 )
          return false;
        igi2_frame.v11 = 0;
        igi2_frame.v12 = 0;
        igi2_frame.v10 = v6;
        MenuItem_Enumerate(ptParent, (void (__cdecl *)(struct MenuItem_s *, void *))MenuItem_FindMenuItemCallback, &igi2_frame.v10);
        v3 = igi2_frame.v11;
        if ( !*(_BYTE *)(igi2_frame.v11 + 84) )
          goto LABEL_16;
      }
    }
    igi2_frame.v10 = 0;
    igi2_frame.v11 = 0;
    igi2_frame.v12 = 0;
    MenuItem_Enumerate(
      ptParent,
      (void (__cdecl *)(struct MenuItem_s *, void *))MenuItem_FindFirstMenuItemCallback,
      &igi2_frame.v10);
    v3 = igi2_frame.v11;
  }
  else
  {
    igi2_frame.v7 = eItem;
    MenuItem_Enumerate(ptParent, (void (__cdecl *)(struct MenuItem_s *, void *))MenuItem_FindMenuItemCallback, &igi2_frame.v7);
    v3 = igi2_frame.v8;
    if ( *(_BYTE *)(igi2_frame.v8 + 84) )
      return false;
  }
LABEL_16:
  if ( !v3 )
    return false;
  memset(igi2_frame.v16, 0, sizeof(igi2_frame.v16));
  igi2_frame.v16[0] = *(_DWORD *)(v3 + 64);
  ((void (__cdecl *)(int, _DWORD *))QTask_aatQTaskFinalEvent[MenuItem_eActivateQTaskEvent][*(unsigned __int16 *)(v3 + 36)].pfHandler)(
    v3,
    igi2_frame.v16);
  if ( igi2_frame.v14 )
    ((void (__cdecl *)(int, _DWORD *))QTask_aatQTaskFinalEvent[MenuItem_eActivateQTaskEvent][*(unsigned __int16 *)(igi2_frame.v14 + 36)].pfHandler)(
      igi2_frame.v14,
      igi2_frame.v16);
  return true;
}

// source: h/0/menuitem.c:541  [anchor-mhash]
struct MenuItem_s *__cdecl MenuItem_Init(
        struct MenuItem_s *ptMenuItem,
        int eMenuItem,
        int eLinkUp,
        int eLinkDown,
        int eLinkLeft,
        int eLinkRight,
        enum bool isDisabled,
        void (__cdecl *pfActivateCallback)(struct MenuItem_s *, struct MenuItemActivateContext_s *))
{
  ptMenuItem->eMenuItem = eMenuItem;
  ptMenuItem->eLinkDown = eLinkDown;
  ptMenuItem->eLinkUp = eLinkUp;
  ptMenuItem->eLinkRight = eLinkRight;
  ptMenuItem->eLinkLeft = eLinkLeft;
  ptMenuItem->isActive = 0;
  ptMenuItem->isActivated = 0;
  ptMenuItem->isDisabled = isDisabled;
  ptMenuItem->pfActivateCallback = (void (__cdecl *)(struct MenuItem_s *, void *))pfActivateCallback;
  return ptMenuItem;
}

// source: h/0/menuitem.c:566  [anchor-callee]
void __cdecl MenuItem_Activate(struct QTask_s *ptParent, int eMenuItem)
{
  struct MenuItemActivateContext_s tContext; // [esp+4h] [ebp-1Ch] BYREF

  memset(&tContext, 0, sizeof(tContext));
  tContext.eMenuItem = eMenuItem;
  ((void (__cdecl *)(struct QTask_s *, struct MenuItemActivateContext_s *))QTask_aatQTaskFinalEvent[MenuItem_eActivateQTaskEvent][ptParent->eQTaskType].pfHandler)(
    ptParent,
    &tContext);
}

// source: h/0/menuitem.c:586  [size]
__int16 __cdecl MenuItem_GetGetMenuItemQTaskEvent()
{
  return MenuItem_eGetMenuItemQTaskEvent;
}

// source: h/0/menuitem.c:600  [size]
__int16 __cdecl MenuItem_GetActivateMenuItemQTaskEvent()
{
  return MenuItem_eActivateQTaskEvent;
}

// source: h/0/menuitem.c:614  [size]
__int16 __cdecl MenuItem_GetUpdateActiveMenuItemQTaskEvent()
{
  return MenuItem_eUpdateActiveQTaskEvent;
}

// source: h/0/menuitem.c:628  [size]
unsigned __int16 __cdecl MenuItem_GetQTaskType()
{
  return MenuItem_eQTaskType;
}
