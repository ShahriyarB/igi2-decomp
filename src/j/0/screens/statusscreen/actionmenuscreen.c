/* j/0/screens/statusscreen/actionmenuscreen.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/screens/statusscreen/actionmenuscreen.c:88  [anchor-callee]
int __cdecl ActionMenuScreen_DoScroll(struct QTask_s *ptQTask, int nScroll)
{
  struct QTask_s *v2; // edx
  int v3; // ecx
  struct QTask_s *ptHead; // esi
  int *p_tQTaskChildren; // ecx
  unsigned int v6; // edx
  struct QTask_s **p_ptTail; // eax
  struct QTask_s *ptTail; // ebx

  if ( nScroll )
  {
    while ( nScroll != -1 )
    {
      if ( nScroll == 1 )
      {
        ptHead = ptQTask[4].tQTaskChildren.ptHead;
        p_tQTaskChildren = (int *)&ptQTask[4].tQTaskChildren;
        if ( ptHead )
        {
          v6 = 0;
          p_ptTail = &ptQTask[4].tQTaskChildren.ptTail;
          ptTail = ptQTask[4].tQTaskChildren.ptTail;
          if ( ptHead != (struct QTask_s *)1 )
          {
            do
            {
              *p_ptTail = p_ptTail[1];
              ++v6;
              ++p_ptTail;
            }
            while ( v6 < *p_tQTaskChildren - 1 );
          }
          nScroll = *p_tQTaskChildren;
          *((_DWORD *)&ptQTask[4].tQTaskChildren.ptMiddle + *p_tQTaskChildren) = ptTail;
        }
        return nScroll;
      }
      if ( nScroll >= 0 )
        --nScroll;
      else
        ++nScroll;
      if ( !nScroll )
        return nScroll;
    }
    nScroll = (int)ptQTask[4].tQTaskChildren.ptHead;
    if ( nScroll )
    {
      v2 = *(&ptQTask[4].tQTaskChildren.ptMiddle + nScroll);
      v3 = nScroll - 1;
      if ( nScroll != 1 )
      {
        nScroll = (int)(&ptQTask[4].tQTaskChildren.ptTail + v3);
        do
        {
          *(_DWORD *)nScroll = *(_DWORD *)(nScroll - 4);
          nScroll -= 4;
          --v3;
        }
        while ( v3 );
      }
      ptQTask[4].tQTaskChildren.ptTail = v2;
    }
  }
  return nScroll;
}

// source: j/0/screens/statusscreen/actionmenuscreen.c:152  [size]
void __cdecl ActionMenuScreen_DrawActionItemHandler(struct QTask_s *ptQTask, void *pxContext)
{
  int v2; // eax
  int v3; // esi
  unsigned __int16 v4; // dx
  int v5; // eax
  void (__cdecl *pfHandler)(int, void *); // eax

  v2 = *(_DWORD *)(*(_DWORD *)pxContext + 4);
  if ( v2 )
  {
    v3 = *(_DWORD *)(v2 + 8);
    if ( v3 )
    {
      v4 = *(_WORD *)(v3 + 36);
      if ( QTask_IsQTaskTypeDerived(v4, Cabinet_eQTaskType) )
      {
        v5 = 0;
LABEL_15:
        ActionMenuScreen_DrawActionItem(
          ptQTask,
          (struct QSprite_s *)&StatusScreen_ptStatusScreenQTask[15].ptPrev + v5,
          pxContext);
        return;
      }
      if ( QTask_IsQTaskTypeDerived(v4, Fence_eQTaskType) )
      {
        v5 = 6;
        goto LABEL_15;
      }
      if ( QTask_IsQTaskTypeDerived(v4, Ladder_eQTaskType) )
      {
        v5 = 7;
        goto LABEL_15;
      }
      if ( QTask_IsQTaskTypeDerived(v4, Terminal_eQTaskType) )
      {
        v5 = 1;
        goto LABEL_15;
      }
      if ( QTask_IsQTaskTypeDerived(v4, Wire_eQTaskType) )
      {
        v5 = 8;
        goto LABEL_15;
      }
      if ( QTask_IsQTaskTypeDerived(v4, StationaryGun_eQTaskType) )
      {
        v5 = 3;
        goto LABEL_15;
      }
      pfHandler = (void (__cdecl *)(int, void *))QTask_aatQTaskFinalEvent[ActionMenuScreen_eDrawActionItemQTaskEvent][v4].pfHandler;
      if ( pfHandler )
        pfHandler(v3, pxContext);
    }
  }
}

// source: j/0/screens/statusscreen/actionmenuscreen.c:226  [anchor-mhash]
void __cdecl ActionMenuScreen_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  memset(&ptQTask[1], 0, 0x78u);
  ActionMenuScreen_ptQTask = ptQTask;
  ActionMenuScreen_ClearHistory(ptQTask);
}

// source: j/0/screens/statusscreen/actionmenuscreen.c:245  [anchor-caller]
void __cdecl ActionMenuScreen_DeleteHandler(struct QTask_s *ptQTask)
{
  ActionMenuScreen_ClearHistory(ptQTask);
  ActionMenuScreen_ptQTask = nullptr;
}

// source: j/0/screens/statusscreen/actionmenuscreen.c:262  [anchor-hash]
void __cdecl ActionMenuScreen_RunHandler(struct QTask_s *ptQTask)
{
  if ( ++f_79eeb64 > 8 )
    f_79eeb64 = -8;
}

// source: j/0/screens/statusscreen/actionmenuscreen.c:286  [anchor-callee]
void __cdecl ActionMenuScreen_Draw(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { float vX; };
    struct { char igi2_o1[4]; float vY; };
    struct { char igi2_o2[12]; float vHeight; };
    struct { char igi2_o3[16]; float vR; };
    struct { char igi2_o4[20]; float vG; };
    struct { char igi2_o5[24]; float vB; };
    struct { char igi2_o6[48]; float vScale; };
    struct { char igi2_o7[52]; float v13; };
    struct { char igi2_o8[56]; float i; };
    struct { char igi2_o9[60]; struct ActionMenuDrawContext_s tActionMenuDrawContext; };
    char igi2_extent[84];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *v1; // edi
  int v2; // eax
  int v3; // eax
  int v4; // eax
  int v5; // eax

  if ( !ptQTask[4].ptNext )
  {
    v1 = nullptr;
    igi2_frame.v13 = 175.0;
    for ( igi2_frame.i = (double)Display_tActiveMode.nHeight - 90.0;
          v1 < ptQTask[4].tQTaskChildren.ptMiddle;
          v1 = (struct QTask_s *)((char *)v1 + 1) )
    {
      v2 = *((_DWORD *)&ptQTask[5].ptNext + (_DWORD)v1);
      igi2_frame.tActionMenuDrawContext.ptActionMenuItem = (struct ActionMenuItem_s *)((char *)&ptQTask[1] + 20 * v2);
      igi2_frame.tActionMenuDrawContext.vX = igi2_frame.v13;
      igi2_frame.tActionMenuDrawContext.vY = igi2_frame.i;
      memset(&igi2_frame.tActionMenuDrawContext.ptOverlaySprite, 0, 12);
      v3 = *((_DWORD *)&ptQTask[1].tQTaskChildren.ptHead + 5 * v2);
      if ( v3 )
      {
        v4 = *(_DWORD *)(v3 + 8);
        if ( v4 )
        {
          ((void (__cdecl *)(int, struct ActionMenuDrawContext_s *))QTask_aatQTaskFinalEvent[ActionMenuScreen_eDrawActionItemQTaskEvent][*(unsigned __int16 *)(v4 + 36)].pfHandler)(
            v4,
            &igi2_frame.tActionMenuDrawContext);
          if ( !v1 )
          {
            v5 = f_79eeb64;
            if ( f_79eeb64 < 0 )
              v5 = -f_79eeb64;
            igi2_frame.vScale = (double)v5 * 0.125;
            igi2_frame.vB = igi2_frame.vScale * 98.55999755859375;
            igi2_frame.vG = igi2_frame.vScale * 35.84000015258789;
            igi2_frame.vR = igi2_frame.vScale * 15.359999656677246;
            igi2_frame.vHeight = (double)igi2_frame.tActionMenuDrawContext.tReturn.nHeight + 4.0;
            igi2_frame.vY = igi2_frame.i - 2.0;
            igi2_frame.vX = igi2_frame.v13 - 2.0 - 32.0;
            QSprite_RegisterBlankA(igi2_frame.vX, igi2_frame.vY, 68.0, igi2_frame.vHeight, igi2_frame.vR, igi2_frame.vG, igi2_frame.vB, igi2_frame.vScale, 0, 0);
          }
          igi2_frame.v13 = igi2_frame.v13 + 64.0;
        }
      }
    }
  }
}

// source: j/0/screens/statusscreen/actionmenuscreen.c:367  [anchor-callee]
void __cdecl ActionMenuScreen_RegisterActionItem(
        struct QTask_s *ptQTask,
        struct QTask_s *ptActionItem,
        struct QTask_s *ptDrawQTask,
        void *pxContext)
{
  struct QTask_s **p_ptPrev; // eax
  unsigned int v5; // edx
  void **v6; // ecx
  struct QTask_s *v7; // esi
  unsigned int v8; // edi
  char *v9; // esi
  struct QReference_s *v10; // eax
  struct QReference_s *v11; // eax
  struct MemPoolFreeItem_s *v12; // eax
  char *v13; // esi
  struct MemPoolFreeItem_s *v14; // eax
  struct QReference_s *v15; // eax

  if ( !ptDrawQTask )
    ptDrawQTask = ptQTask;
  p_ptPrev = &ptQTask[1].ptPrev;
  v5 = 0;
  v6 = (void **)&ptQTask[1].ptPrev;
  do
  {
    if ( *((_BYTE *)v6 + 14) )
    {
      v7 = *v6 ? *((struct QTask_s **)*v6 + 2) : nullptr;
      if ( v7 == ptActionItem && v6[2] == pxContext )
      {
        v9 = (char *)ptQTask + 20 * v5;
        v10 = *((struct QReference_s **)v9 + 12);
        if ( v10 )
        {
          QReference_Delete(v10, &QTask_tQTaskRefPool);
          *((_DWORD *)v9 + 12) = 0;
        }
        v9[57] = 1;
        if ( ptDrawQTask )
        {
          v11 = QTask_NewQTaskRef(ptDrawQTask);
          *((_DWORD *)v9 + 13) = pxContext;
          *((_DWORD *)v9 + 12) = v11;
        }
        else
        {
          *((_DWORD *)v9 + 13) = pxContext;
          *((_DWORD *)v9 + 12) = 0;
        }
        return;
      }
    }
    ++v5;
    v6 += 5;
  }
  while ( v5 < 6 );
  v8 = 0;
  while ( *((_BYTE *)p_ptPrev + 14) && *p_ptPrev && (*p_ptPrev)->tQTaskChildren.ptHead )
  {
    ++v8;
    p_ptPrev += 5;
    if ( v8 >= 6 )
      return;
  }
  v12 = *((struct MemPoolFreeItem_s **)&ptQTask[1].ptPrev + 5 * v8);
  v13 = (char *)ptQTask + 20 * v8;
  if ( v12 )
  {
    if ( v12->ptNext )
      v12 = (struct MemPoolFreeItem_s *)Node_Remove(v12);
    --QTask_tQTaskRefPool.nAllocatedBlocks;
    v12->ptNext = QTask_tQTaskRefPool.tMemPoolFreeList.ptHead;
    QTask_tQTaskRefPool.tMemPoolFreeList.ptHead = v12;
    *((_DWORD *)v13 + 11) = 0;
  }
  v14 = *((struct MemPoolFreeItem_s **)v13 + 12);
  if ( v14 )
  {
    if ( v14->ptNext )
      v14 = (struct MemPoolFreeItem_s *)Node_Remove(v14);
    --QTask_tQTaskRefPool.nAllocatedBlocks;
    v14->ptNext = QTask_tQTaskRefPool.tMemPoolFreeList.ptHead;
    QTask_tQTaskRefPool.tMemPoolFreeList.ptHead = v14;
    *((_DWORD *)v13 + 12) = 0;
  }
  v13[58] = 1;
  v13[57] = 1;
  *((_DWORD *)v13 + 11) = QTask_NewQTaskRef(ptActionItem);
  if ( ptDrawQTask )
    v15 = QTask_NewQTaskRef(ptDrawQTask);
  else
    v15 = nullptr;
  *((_DWORD *)v13 + 12) = v15;
  *((_DWORD *)&ptQTask[1].ptNext + 5 * v8) = Flow_ptFlow->nTicks;
  *((_DWORD *)v13 + 13) = pxContext;
}

// source: j/0/screens/statusscreen/actionmenuscreen.c:426  [anchor-mhash]
enum bool __cdecl ActionMenuScreen_GetCurrentItem(
        struct QTask_s *ptQTask,
        int i,
        struct QTask_s **pptActionItem,
        struct QTask_s **pptDrawQTask,
        void **ppxContext)
{
  char *v5; // eax
  int v6; // ecx
  struct QTask_s *v7; // ecx
  int v8; // ecx
  struct QTask_s *v9; // ecx

  if ( (unsigned int)i > 5 )
    return false;
  v5 = (char *)ptQTask + 20 * i;
  if ( !v5[58] || !v5[57] )
    return false;
  if ( pptActionItem )
  {
    v6 = *((_DWORD *)v5 + 11);
    if ( v6 )
      v7 = *(struct QTask_s **)(v6 + 8);
    else
      v7 = nullptr;
    *pptActionItem = v7;
  }
  if ( pptDrawQTask )
  {
    v8 = *((_DWORD *)v5 + 12);
    if ( v8 )
      v9 = *(struct QTask_s **)(v8 + 8);
    else
      v9 = nullptr;
    *pptDrawQTask = v9;
  }
  if ( ppxContext )
    *ppxContext = *((void **)v5 + 13);
  return true;
}

// source: j/0/screens/statusscreen/actionmenuscreen.c:462  [anchor-hash]
struct QTask_s *__cdecl ActionMenuScreen_Update(struct QTask_s *ptQTask)
{
  struct QTask_s *v2; // ecx
  struct QTask_s **p_ptTail; // eax
  struct QTask_s *ptPrev; // eax
  struct QTask_s *ptHead; // eax
  struct QTask_s *v6; // edx
  _DWORD *v7; // ecx
  unsigned int v8; // ecx
  char *v9; // eax
  struct QTask_s **v10; // eax
  int v11; // ecx
  struct QTask_s *result; // eax

  v2 = nullptr;
  if ( ptQTask[4].tQTaskChildren.ptMiddle )
  {
    p_ptTail = &ptQTask[4].tQTaskChildren.ptTail;
    do
    {
      *p_ptTail = p_ptTail[6];
      v2 = (struct QTask_s *)((char *)v2 + 1);
      ++p_ptTail;
    }
    while ( v2 < ptQTask[4].tQTaskChildren.ptMiddle );
  }
  ptQTask[4].tQTaskChildren.ptHead = ptQTask[4].tQTaskChildren.ptMiddle;
  ptPrev = ptQTask[4].ptPrev;
  ptQTask[4].tQTaskChildren.ptMiddle = nullptr;
  if ( ptPrev )
    ActionMenuScreen_DoScroll(ptQTask, (int)ptPrev);
  ptHead = ptQTask[4].tQTaskChildren.ptHead;
  v6 = nullptr;
  ptQTask[4].ptPrev = nullptr;
  ptQTask[4].tQTaskChildren.ptMiddle = nullptr;
  if ( ptHead )
  {
    v7 = &ptQTask[4].tQTaskChildren.ptTail;
    do
    {
      if ( *((_BYTE *)&ptQTask[1].tQTaskChildren.ptTail + 20 * *v7 + 1) )
      {
        *((_DWORD *)&ptQTask[5].ptNext + (int)(*(int *)&ptQTask[4].tQTaskChildren.ptMiddle)++) = *v7;
        *((_BYTE *)&ptQTask[1].tQTaskChildren.ptTail + 20 * *v7) = 1;
      }
      v6 = (struct QTask_s *)((char *)v6 + 1);
      ++v7;
    }
    while ( v6 < ptQTask[4].tQTaskChildren.ptHead );
  }
  v8 = 0;
  v9 = (char *)&ptQTask[1].tQTaskChildren.ptTail;
  do
  {
    if ( v9[1] )
    {
      if ( !*v9 )
      {
        *((_DWORD *)&ptQTask[5].ptNext + (int)(*(int *)&ptQTask[4].tQTaskChildren.ptMiddle)++) = v8;
        *v9 = 1;
      }
    }
    else
    {
      v9[2] = 0;
    }
    ++v8;
    v9 += 20;
  }
  while ( v8 < 6 );
  v10 = &ptQTask[1].tQTaskChildren.ptTail;
  v11 = 6;
  do
  {
    *((_BYTE *)v10 + 1) = 0;
    *(_BYTE *)v10 = 0;
    v10 += 5;
    --v11;
  }
  while ( v11 );
  result = (int)(&ptQTask[4].ptNext[-1].isInMemPool + 1) < 0
         ? nullptr
         : (struct QTask_s *)(&ptQTask[4].ptNext[-1].isInMemPool + 1);
  ptQTask[4].ptNext = result;
  return result;
}

// source: j/0/screens/statusscreen/actionmenuscreen.c:533  [anchor-callee]
enum bool __cdecl ActionMenuScreen_IsFirstActionItem(
        struct QTask_s *ptQTask,
        struct QTask_s *ptActionItem,
        void *pxContext)
{
  char *v3; // ecx
  int v4; // eax
  struct QTask_s *v5; // eax
  enum bool result; // eax

  result = false;
  if ( ptQTask[4].tQTaskChildren.ptHead && !ptQTask[4].ptNext )
  {
    v3 = (char *)ptQTask + 20 * (int)ptQTask[4].tQTaskChildren.ptTail;
    v4 = *((_DWORD *)v3 + 11);
    v5 = v4 ? *(struct QTask_s **)(v4 + 8) : nullptr;
    if ( ptActionItem == v5 && pxContext == *((void **)v3 + 13) )
      return true;
  }
  return result;
}

// source: j/0/screens/statusscreen/actionmenuscreen.c:560  [size]
unsigned __int16 __cdecl ActionMenuScreen_GetQTaskType()
{
  return ActionMenuScreen_eQTaskType;
}

// source: j/0/screens/statusscreen/actionmenuscreen.c:573  [size]
__int16 __cdecl ActionMenuScreen_GetDrawActionItemQTaskEvent()
{
  return ActionMenuScreen_eDrawActionItemQTaskEvent;
}

// source: j/0/screens/statusscreen/actionmenuscreen.c:589  [anchor-mhash]
void __cdecl ActionMenuScreen_DrawActionItem(
        struct QTask_s *ptQTask,
        struct QSprite_s *ptQSprite,
        void *pxContext)
{
  struct QSprite_s *v3; // ecx
  float v4; // ebp
  float v5; // [esp+0h] [ebp-8h]

  if ( ptQSprite )
  {
    v3 = *((struct QSprite_s **)pxContext + 3);
    v4 = *((float *)pxContext + 2);
    v5 = *((float *)pxContext + 1) - (double)(ptQSprite->atQAnimframe[ptQSprite->nQAnimframes].nWidth / 2);
    if ( v3 )
      QSprite_RegisterAZ(v3, v5, *((float *)pxContext + 2), 128.0, 128.0, 128.0, 1.0, 0.0, 0, 0x80000u, 0);
    QSprite_RegisterAZ(ptQSprite, v5, v4, 128.0, 128.0, 128.0, 1.0, 0.0, 0, 0x80000u, 0);
    *((_DWORD *)pxContext + 4) = ptQSprite->atQAnimframe[ptQSprite->nQAnimframes].nWidth;
    *((_DWORD *)pxContext + 5) = ptQSprite->atQAnimframe[ptQSprite->nQAnimframes].nHeight;
  }
}

// source: j/0/screens/statusscreen/actionmenuscreen.c:657  [size]
struct QTask_s *__cdecl ActionMenuScreen_GetQTask()
{
  return ActionMenuScreen_ptQTask;
}

// source: j/0/screens/statusscreen/actionmenuscreen.c:674  [size]
int __cdecl ActionMenuScreen_Scroll(struct QTask_s *ptQTask, int nScroll)
{
  ptQTask[4].ptPrev = (struct QTask_s *)nScroll;
  return nScroll;
}

// source: j/0/screens/statusscreen/actionmenuscreen.c:692  [size]
int __cdecl ActionMenuScreen_SetNoDrawTimeout(struct QTask_s *ptQTask, int nTicks)
{
  ptQTask[4].ptNext = (struct QTask_s *)nTicks;
  return nTicks;
}

// source: j/0/screens/statusscreen/actionmenuscreen.c:713  [anchor-hash]
struct QTask_s *__cdecl ActionMenuScreen_ClearHistory(struct QTask_s *ptQTask)
{
  struct QReference_s **p_tQTaskChildren; // esi
  int v2; // ebp
  struct QReference_s *v3; // eax
  struct QTask_s *result; // eax

  ptQTask[4].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[4].tQTaskChildren.ptHead = nullptr;
  ptQTask[4].ptPrev = nullptr;
  ptQTask[4].ptNext = nullptr;
  p_tQTaskChildren = (struct QReference_s **)&ptQTask[1].tQTaskChildren;
  v2 = 6;
  do
  {
    v3 = *(p_tQTaskChildren - 1);
    if ( v3 )
    {
      QReference_Delete(v3, &QTask_tQTaskRefPool);
      *(p_tQTaskChildren - 1) = nullptr;
    }
    if ( *p_tQTaskChildren )
    {
      QReference_Delete(*p_tQTaskChildren, &QTask_tQTaskRefPool);
      *p_tQTaskChildren = nullptr;
    }
    result = (struct QTask_s *)20;
    p_tQTaskChildren += 5;
    --v2;
  }
  while ( v2 );
  return result;
}

// source: j/0/screens/statusscreen/actionmenuscreen.c:743  [anchor-hash]
void __cdecl ActionMenuScreen_Open()
{
  unsigned __int16 BaseQTaskType; // ax
  __int16 v1; // ax
  unsigned __int16 v2; // si
  __int16 v3; // di

  BaseQTaskType = QTask_GetBaseQTaskType();
  ActionMenuScreen_eQTaskType = QTask_NewQTaskType(&stru_68C1E0.zFilename[36], 224, BaseQTaskType, 0, 0);
  v1 = QTask_NewQTaskEventFn(0, &stru_68C1E0.zFilename[20]);
  v2 = ActionMenuScreen_eQTaskType;
  v3 = v1;
  ActionMenuScreen_eDrawActionItemQTaskEvent = v1;
  QTask_LinkQTaskEventHandlerFn(ActionMenuScreen_eQTaskType, 0, ActionMenuScreen_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v2, 2, ActionMenuScreen_DeleteHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v2, 1, (void (__cdecl *)(struct QTask_s *))ActionMenuScreen_RunHandler);
  QTask_LinkQTaskEventHandlerFn(v2, v3, ActionMenuScreen_DrawActionItemHandler);
}

// source: j/0/screens/statusscreen/actionmenuscreen.c:766  [size]
void __cdecl ActionMenuScreen_Close()
{
  QTask_DeleteQTaskEvent(ActionMenuScreen_eDrawActionItemQTaskEvent);
  QTask_DeleteQTaskType(ActionMenuScreen_eQTaskType);
}
