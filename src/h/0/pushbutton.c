/* h/0/pushbutton.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: h/0/pushbutton.c:33  [anchor-mhash]
void __cdecl PushButton_DrawHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptHead; // eax

  ptHead = ptQTask[3].tQTaskChildren.ptHead;
  if ( ptHead )
    QTilemap_Register(
      (struct QTilemap_s *)ptHead->ptNext,
      *(float *)&ptHead->ptPrev,
      *(float *)&ptHead->tQTaskChildren.ptHead,
      *(float *)&ptHead->tQTaskRefList.ptHead,
      *(float *)&ptHead->tQTaskRefList.ptMiddle,
      *(float *)&ptHead->tQTaskRefList.ptTail,
      *(float *)&ptHead->tQTaskChildren.ptTail,
      *(float *)&ptHead->tQTaskChildren.ptMiddle,
      *(_DWORD *)&ptHead->eQTaskType | 0x40000000,
      (int)ptHead->ptParent);
}

// source: h/0/pushbutton.c:52  [anchor-mhash]
void __cdecl PushButton_RegisterHitboxHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *ptHead; // esi

  ptHead = ptQTask[3].tQTaskChildren.ptHead;
  if ( ptHead )
  {
    ptQTask[3].ptPrev = ptQTask;
    Text_GetClippingRect((struct StaticTilemap_s *)ptHead, (struct ClippingRect_s *)&ptQTask[2].tQTaskRefList);
    ptQTask[2].tQTaskChildren.ptTail = nullptr;
    ptQTask[2].tQTaskChildren.ptMiddle = nullptr;
    List_AddTail(&ptQTask[2].tQTaskChildren.ptMiddle, *(_DWORD *)pxContext);
  }
}

// source: h/0/pushbutton.c:77  [size]
unsigned __int16 __cdecl PushButton_GetQTaskType()
{
  return PushButton_eQTaskType;
}

// source: h/0/pushbutton.c:91  [anchor-hash]
void __cdecl PushButton_Open()
{
  unsigned __int16 v0; // si
  __int16 v1; // ax

  v0 = QTask_NewQTaskType("PushButton", 132, MenuItem_eQTaskType, 0, 0);
  PushButton_eQTaskType = v0;
  QTask_LinkQTaskEventHandlerNoContextFn(v0, Screen_eDrawQTaskEvent, PushButton_DrawHandler);
  v1 = MenuItemQTask_eRegisterHitboxQTaskEvent;
  if ( MenuItemQTask_eRegisterHitboxQTaskEvent == 512 )
  {
    v1 = QTask_NewQTaskEventFn(0, "Register Hitbox");
    v0 = PushButton_eQTaskType;
    MenuItemQTask_eRegisterHitboxQTaskEvent = v1;
  }
  QTask_LinkQTaskEventHandlerFn(v0, v1, PushButton_RegisterHitboxHandler);
}

// source: h/0/pushbutton.c:111  [size]
void __cdecl PushButton_Close()
{
  QTask_DeleteQTaskType(PushButton_eQTaskType);
}

// source: h/0/pushbutton.c:135  [anchor-mhash]
struct QTask_s *__cdecl PushButton_New(
        struct QTask_s *ptParent,
        int eMenuItem,
        int eLinkUp,
        int eLinkDown,
        int eLinkLeft,
        int eLinkRight,
        int isDisabled,
        void (__cdecl *pfActivateCallback)(struct MenuItem_s *, struct MenuItemActivateContext_s *),
        struct StaticTilemap_s *ptQText)
{
  struct QTask_s *result; // eax

  result = QTask_NewFn(ptParent, PushButton_eQTaskType, nullptr);
  result[1].tQTaskRefList.ptMiddle = (struct QReference_s *)eMenuItem;
  result[1].tQTaskRefList.ptTail = (struct QReference_s *)eLinkUp;
  result[1].ptParent = (struct QTask_s *)eLinkDown;
  *(_DWORD *)&result[1].eQTaskType = eLinkLeft;
  result[2].ptNext = (struct QTask_s *)eLinkRight;
  LOBYTE(result[2].ptPrev) = isDisabled;
  BYTE2(result[2].ptPrev) = 0;
  BYTE1(result[2].ptPrev) = 0;
  result[2].tQTaskChildren.ptHead = (struct QTask_s *)pfActivateCallback;
  result[3].tQTaskChildren.ptHead = (struct QTask_s *)ptQText;
  return result;
}
