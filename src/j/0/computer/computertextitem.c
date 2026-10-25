/* j/0/computer/computertextitem.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/computer/computertextitem.c:41  [size]
void __cdecl ComputerTextItem_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ;
}

// source: j/0/computer/computertextitem.c:55  [size]
void __cdecl ComputerTextItem_RunHandler(struct QTask_s *ptQTask)
{
  ;
}

// source: j/0/computer/computertextitem.c:69  [size]
void __cdecl ComputerTextItem_DeleteHandler(struct QTask_s *ptQTask)
{
  Text_Delete((struct StaticTilemap_s *)ptQTask[3].tQTaskChildren.ptHead);
}

// source: j/0/computer/computertextitem.c:86  [anchor-mhash]
void __cdecl ComputerTextItem_DrawHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptTail; // ecx
  struct QTask_s *ptHead; // eax

  if ( BYTE2(ptQTask[2].ptPrev) )
    ptTail = ptQTask[3].tQTaskChildren.ptTail;
  else
    ptTail = ptQTask[3].tQTaskChildren.ptMiddle;
  memcpy(&ptQTask[3].tQTaskChildren.ptHead->tQTaskRefList, &ComputerMenu_atColor[(_DWORD)ptTail], sizeof(struct real32x3_t));
  ptQTask[3].tQTaskChildren.ptHead->ptParent = (struct QTask_s *)-1;
  ptHead = ptQTask[3].tQTaskChildren.ptHead;
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

// source: j/0/computer/computertextitem.c:111  [size]
void __cdecl ComputerTextItem_RegisterHitboxHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ptQTask[2].tQTaskChildren.ptTail = nullptr;
  ptQTask[2].tQTaskChildren.ptMiddle = nullptr;
  List_AddTail(&ptQTask[2].tQTaskChildren.ptMiddle, *(_DWORD *)pxContext);
}

// source: j/0/computer/computertextitem.c:144  [anchor-callee]
int __cdecl ComputerTextItem_Init(
        struct QTask_s *ptQTask,
        int eMenuItem,
        int eLinkUp,
        int eLinkDown,
        int eLinkLeft,
        int eLinkRight,
        enum bool isDisabled,
        float vX,
        float vY,
        struct QSprite_s *ptQSprite,
        char *zText,
        enum ComputerMenuColor_e eComputerMenuColor,
        enum ComputerMenuColor_e eHighlightComputerMenuColor,
        void (__cdecl *pfMenuItemActivateCallback)(struct MenuItem_s *, struct MenuItemActivateContext_s *))
{
  struct StaticTilemap_s *v14; // eax
  struct QTask_s *ptHead; // edx
  int ptPrev_high; // ecx
  struct QTask_s *ptNext_low; // edi
  struct QTask_s *ptMiddle; // eax
  double v19; // st7
  struct QTask_s *ptQTaska = *(struct QTask_s * *)&eLinkLeft; // [esp+Ch] [ebp+4h] ARGSLOT
  int ptQTaskb = *(int *)&eLinkLeft; // [esp+Ch] [ebp+4h] ARGSLOT

  ptQTask[1].tQTaskRefList.ptTail = (struct QReference_s *)eLinkUp;
  ptQTask[1].tQTaskRefList.ptMiddle = (struct QReference_s *)eMenuItem;
  ptQTask[1].ptParent = (struct QTask_s *)eLinkDown;
  ptQTask[2].ptNext = (struct QTask_s *)eLinkRight;
  *(_DWORD *)&ptQTask[1].eQTaskType = eLinkLeft;
  LOBYTE(ptQTask[2].ptPrev) = isDisabled;
  ptQTask[2].tQTaskChildren.ptHead = (struct QTask_s *)pfMenuItemActivateCallback;
  BYTE2(ptQTask[2].ptPrev) = 0;
  BYTE1(ptQTask[2].ptPrev) = 0;
  v14 = Text_New(ptQSprite, vX, vY, zText);
  ptQTask[3].tQTaskChildren.ptHead = (struct QTask_s *)v14;
  v14->bQGraphicFlags |= 0x40000u;
  ptQTask[3].tQTaskChildren.ptHead->tQTaskChildren.ptMiddle = (struct QTask_s *)1141022392;
  ptQTask[3].tQTaskChildren.ptMiddle = (struct QTask_s *)eComputerMenuColor;
  *(float *)&ptQTask[3].tQTaskRefList.ptHead = vX;
  ptHead = ptQTask[3].tQTaskChildren.ptHead;
  ptQTask[3].tQTaskChildren.ptTail = (struct QTask_s *)eHighlightComputerMenuColor;
  *(float *)&ptQTask[3].tQTaskRefList.ptMiddle = vY;
  ptPrev_high = SHIWORD(ptHead->ptNext->ptPrev);
  ptNext_low = nullptr;
  ptQTaska = nullptr;
  if ( ptPrev_high > 0 )
  {
    ptMiddle = ptHead->ptNext->tQTaskChildren.ptMiddle;
    do
    {
      if ( SLOWORD(ptMiddle->ptNext) > (int)ptNext_low )
        ptNext_low = (struct QTask_s *)SLOWORD(ptMiddle->ptNext);
      ptMiddle = (struct QTask_s *)((char *)ptMiddle + 2);
      --ptPrev_high;
    }
    while ( ptPrev_high );
    ptQTaska = ptNext_low;
  }
  v19 = (double)(int)ptQTaska;
  *(float *)&ptQTask[3].tQTaskRefList.ptTail = v19;
  ptQTaskb = SHIWORD(ptHead->ptNext->ptPrev)
           * *((__int16 *)&ptHead->ptNext->tQTaskChildren.ptHead->tQTaskChildren.ptHead->tQTaskChildren.ptMiddle
             + 18 * LOWORD(ptHead->ptNext->tQTaskChildren.ptHead->tQTaskRefList.ptHead)
             + 1);
  ptQTask[3].ptPrev = ptQTask;
  *(float *)&ptQTask[2].tQTaskRefList.ptHead = vX;
  *(float *)&ptQTask[2].tQTaskRefList.ptMiddle = vY;
  *(float *)&ptQTask[3].ptParent = (float)ptQTaskb;
  ptQTask[2].ptParent = ptQTask[3].ptParent;
  *(float *)&ptQTask[2].tQTaskRefList.ptTail = v19;
  return LODWORD(vX);
}

// source: j/0/computer/computertextitem.c:208  [anchor-callee]
struct QTask_s *__cdecl ComputerTextItem_New(
        struct QTask_s *ptParent,
        int eMenuItem,
        int eLinkUp,
        int eLinkDown,
        int eLinkLeft,
        int eLinkRight,
        enum bool isDisabled,
        float vX,
        float vY,
        struct QSprite_s *ptQSprite,
        char *zText,
        enum ComputerMenuColor_e eComputerMenuColor,
        enum ComputerMenuColor_e eHighlightComputerMenuColor,
        void (__cdecl *pfMenuItemActivateCallback)(struct MenuItem_s *, struct MenuItemActivateContext_s *))
{
  struct QTask_s *v14; // esi

  v14 = QTask_NewFn(ptParent, ComputerTextItem_eQTaskType, nullptr);
  ComputerTextItem_Init(
    v14,
    eMenuItem,
    eLinkUp,
    eLinkDown,
    eLinkLeft,
    eLinkRight,
    isDisabled,
    vX,
    vY,
    ptQSprite,
    zText,
    eComputerMenuColor,
    eHighlightComputerMenuColor,
    pfMenuItemActivateCallback);
  return v14;
}

// source: j/0/computer/computertextitem.c:241  [size]
unsigned __int16 __cdecl ComputerTextItem_GetQTaskType()
{
  return ComputerTextItem_eQTaskType;
}

// source: j/0/computer/computertextitem.c:254  [anchor-strings]
void __cdecl ComputerTextItem_Open()
{
  unsigned __int16 v0; // si
  __int16 v1; // ax

  v0 = QTask_NewQTaskType("ComputerTextItem", 156, MenuItem_eQTaskType, 0, 0);
  ComputerTextItem_eQTaskType = v0;
  QTask_LinkQTaskEventHandlerFn(v0, 0, (void (__cdecl *)(struct QTask_s *, void *))ComputerTextItem_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 1, (void (__cdecl *)(struct QTask_s *))ComputerTextItem_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 2, ComputerTextItem_DeleteHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, Screen_eDrawQTaskEvent, ComputerTextItem_DrawHandler);
  v1 = MenuItemQTask_eRegisterHitboxQTaskEvent;
  if ( MenuItemQTask_eRegisterHitboxQTaskEvent == 512 )
  {
    v1 = QTask_NewQTaskEventFn(0, "Register Hitbox");
    v0 = ComputerTextItem_eQTaskType;
    MenuItemQTask_eRegisterHitboxQTaskEvent = v1;
  }
  QTask_LinkQTaskEventHandlerFn(v0, v1, ComputerTextItem_RegisterHitboxHandler);
}

// source: j/0/computer/computertextitem.c:275  [size]
void __cdecl ComputerTextItem_Close()
{
  QTask_DeleteQTaskType(ComputerTextItem_eQTaskType);
}
