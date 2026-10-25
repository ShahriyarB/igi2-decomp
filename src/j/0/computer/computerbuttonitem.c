/* j/0/computer/computerbuttonitem.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/computer/computerbuttonitem.c:40  [size]
void __cdecl ComputerButtonItem_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ;
}

// source: j/0/computer/computerbuttonitem.c:56  [size]
void __cdecl ComputerButtonItem_RunHandler(struct QTask_s *ptQTask)
{
  ;
}

// source: j/0/computer/computerbuttonitem.c:70  [size]
void __cdecl ComputerButtonItem_DeleteHandler(struct QTask_s *ptQTask)
{
  struct QReference_s *ptHead; // eax

  ptHead = ptQTask[3].tQTaskRefList.ptHead;
  if ( ptHead )
    Text_Delete((struct StaticTilemap_s *)ptHead);
}

// source: j/0/computer/computerbuttonitem.c:90  [anchor-mhash]
void __cdecl ComputerButtonItem_DrawHandler(struct QTask_s *ptQTask)
{
  struct QSprite_s *ptParent; // ecx
  struct QReference_s *ptHead; // eax
  struct QReference_s *v3; // eax

  if ( BYTE2(ptQTask[2].ptPrev) )
  {
    if ( LOBYTE(ptQTask[3].tQTaskChildren.ptTail) )
      ptParent = (struct QSprite_s *)ptQTask[3].ptParent;
    else
      ptParent = (struct QSprite_s *)ptQTask[3].tQTaskRefList.ptTail;
  }
  else
  {
    ptParent = (struct QSprite_s *)ptQTask[3].tQTaskRefList.ptMiddle;
  }
  QSprite_RegisterAZ(
    ptParent,
    *(float *)&ptQTask[3].tQTaskChildren.ptHead,
    *(float *)&ptQTask[3].tQTaskChildren.ptMiddle,
    128.0,
    128.0,
    128.0,
    1.0,
    522.47998046875,
    0,
    0x400C0000u,
    -1);
  ptHead = ptQTask[3].tQTaskRefList.ptHead;
  if ( ptHead )
  {
    ptHead[2].pxObject = (void *)-1;
    v3 = ptQTask[3].tQTaskRefList.ptHead;
    QTilemap_Register(
      (struct QTilemap_s *)v3->ptNext,
      *(float *)&v3->ptPrev,
      *(float *)&v3->pxObject,
      *(float *)&v3[1].pxObject,
      *(float *)&v3[2].ptNext,
      *(float *)&v3[2].ptPrev,
      *(float *)&v3[1].ptPrev,
      *(float *)&v3[1].ptNext,
      (int)v3[3].ptNext | 0x40000000,
      (int)v3[2].pxObject);
  }
}

// source: j/0/computer/computerbuttonitem.c:144  [size]
void __cdecl ComputerButtonItem_RegisterHitboxHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ptQTask[2].tQTaskChildren.ptTail = nullptr;
  ptQTask[2].tQTaskChildren.ptMiddle = nullptr;
  List_AddTail(&ptQTask[2].tQTaskChildren.ptMiddle, *(_DWORD *)pxContext);
}

// source: j/0/computer/computerbuttonitem.c:163  [anchor-strings]
void __cdecl ComputerButtonItem_Open()
{
  unsigned __int16 v0; // si
  __int16 v1; // ax

  v0 = QTask_NewQTaskType("ComputerButtonItem", 156, MenuItem_eQTaskType, 0, 0);
  ComputerButtonItem_eQTaskType = v0;
  QTask_LinkQTaskEventHandlerFn(v0, 0, (void (__cdecl *)(struct QTask_s *, void *))ComputerButtonItem_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 1, (void (__cdecl *)(struct QTask_s *))ComputerButtonItem_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 2, ComputerButtonItem_DeleteHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, Screen_eDrawQTaskEvent, ComputerButtonItem_DrawHandler);
  v1 = MenuItemQTask_eRegisterHitboxQTaskEvent;
  if ( MenuItemQTask_eRegisterHitboxQTaskEvent == 512 )
  {
    v1 = QTask_NewQTaskEventFn(0, "Register Hitbox");
    v0 = ComputerButtonItem_eQTaskType;
    MenuItemQTask_eRegisterHitboxQTaskEvent = v1;
  }
  QTask_LinkQTaskEventHandlerFn(v0, v1, ComputerButtonItem_RegisterHitboxHandler);
}

// source: j/0/computer/computerbuttonitem.c:184  [size]
void __cdecl ComputerButtonItem_Close()
{
  QTask_DeleteQTaskType(ComputerButtonItem_eQTaskType);
}

// source: j/0/computer/computerbuttonitem.c:214  [anchor-callee]
struct QTask_s *__cdecl ComputerButtonItem_New(
        struct QTask_s *ptParent,
        int eMenuItem,
        int eLinkUp,
        int eLinkDown,
        int eLinkLeft,
        int eLinkRight,
        char isDisabled,
        float vX,
        float vY,
        char isActive,
        struct QSprite_s *ptQSprite,
        char *zText,
        struct QSprite_s *ptQSprite1,
        struct QSprite_s *ptQSprite2,
        struct QSprite_s *ptQSprite3,
        void (__cdecl *pfMenuItemActivateCallback)(struct MenuItem_s *, struct MenuItemActivateContext_s *))
{
  struct QTask_s *v16; // esi
  struct QAnimframe_s *v17; // eax
  struct StaticTilemap_s *v18; // eax
  struct QReference_s *ptNext; // ecx
  int ptPrev_high; // eax
  int ptNext_low; // ebx
  struct QReference_s *v22; // edi
  double v23; // st7
  float nX; // [esp+0h] [ebp-1Ch]
  int eLinkRighta = *(int *)&isDisabled; // [esp+34h] [ebp+18h] ARGSLOT
  float eLinkRightb = *(float *)&isDisabled; // [esp+34h] [ebp+18h] ARGSLOT
  float vYa = *(float *)&isActive; // [esp+40h] [ebp+24h] ARGSLOT
  float zTexta = *(float *)&ptQSprite1; // [esp+4Ch] [ebp+30h] ARGSLOT

  v16 = QTask_NewFn(ptParent, ComputerButtonItem_eQTaskType, nullptr);
  v16[1].tQTaskRefList.ptMiddle = (struct QReference_s *)eMenuItem;
  *(_DWORD *)&v16[1].eQTaskType = eLinkLeft;
  v16[1].tQTaskRefList.ptTail = (struct QReference_s *)eLinkUp;
  v16[1].ptParent = (struct QTask_s *)eLinkDown;
  v16[2].tQTaskChildren.ptHead = (struct QTask_s *)pfMenuItemActivateCallback;
  v16[2].ptNext = (struct QTask_s *)eLinkRight;
  LOBYTE(v16[2].ptPrev) = isDisabled;
  v16[3].ptParent = (struct QTask_s *)ptQSprite3;
  LOBYTE(v16[3].tQTaskChildren.ptTail) = isActive;
  BYTE2(v16[2].ptPrev) = 0;
  BYTE1(v16[2].ptPrev) = 0;
  v16[3].tQTaskRefList.ptMiddle = (struct QReference_s *)ptQSprite1;
  v16[3].tQTaskRefList.ptTail = (struct QReference_s *)ptQSprite2;
  v17 = &ptQSprite1->atQAnimframe[ptQSprite1->nQAnimframes];
  vYa = (float)v17->nWidth;
  zTexta = (float)v17->nHeight;
  if ( strlen(zText) )
  {
    nX = vYa + vX;
    v18 = Text_New(ptQSprite, nX, vY, zText);
    v16[3].tQTaskRefList.ptHead = (struct QReference_s *)v18;
    v18->bQGraphicFlags |= 0x40000u;
    v16[3].tQTaskRefList.ptHead[1].ptNext = (struct QReference_s *)1141022392;
    ptNext = v16[3].tQTaskRefList.ptHead->ptNext;
    ptPrev_high = SHIWORD(ptNext->ptPrev);
    ptNext_low = 0;
    eLinkRighta = 0;
    if ( ptPrev_high > 0 )
    {
      v22 = ptNext[1].ptNext;
      do
      {
        if ( SLOWORD(v22->ptNext) > ptNext_low )
          ptNext_low = SLOWORD(v22->ptNext);
        v22 = (struct QReference_s *)((char *)v22 + 2);
        --ptPrev_high;
      }
      while ( ptPrev_high );
      eLinkRighta = ptNext_low;
    }
    v23 = (double)eLinkRighta;
    eLinkRightb = (float)(SHIWORD(ptNext->ptPrev)
                        * *(__int16 *)(*((_DWORD *)ptNext->pxObject + 2)
                                     + 36 * *((unsigned __int16 *)ptNext->pxObject + 10)
                                     + 14));
  }
  else
  {
    v23 = 0.0;
    v16[3].tQTaskRefList.ptHead = nullptr;
    eLinkRightb = 0.0;
  }
  *(float *)&v16[2].tQTaskRefList.ptTail = v23 + vYa;
  *(float *)&v16[2].tQTaskRefList.ptHead = vX;
  *(float *)&v16[3].tQTaskChildren.ptHead = vX;
  *(float *)&v16[3].tQTaskChildren.ptMiddle = vY;
  v16[3].ptPrev = v16;
  *(float *)&v16[2].tQTaskRefList.ptMiddle = vY;
  if ( zTexta <= (double)eLinkRightb )
    *(float *)&v16[2].ptParent = eLinkRightb;
  else
    *(float *)&v16[2].ptParent = zTexta;
  return v16;
}

// source: j/0/computer/computerbuttonitem.c:303  [size]
struct QTask_s *__cdecl ComputerButtonItem_SetPos(
        struct QTask_s *ptQTask,
        float vX,
        float vY)
{
  *(float *)&ptQTask[3].tQTaskChildren.ptHead = vX;
  *(float *)&ptQTask[3].tQTaskChildren.ptMiddle = vY;
  *(float *)&ptQTask[2].tQTaskRefList.ptHead = vX;
  *(float *)&ptQTask[2].tQTaskRefList.ptMiddle = vY;
  return ptQTask;
}
