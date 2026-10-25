/* h/0/menuitemtask.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: h/0/menuitemtask.c:59  [anchor-mhash]
void __cdecl MenuItemQTask_ActivateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *ptHead; // ecx
  int v3; // eax
  struct QTask_s *v4; // edx
  void (__cdecl *pfHandler)(struct QTask_s *, _DWORD); // edx
  int v6; // eax
  struct QTask_s *v7; // ecx
  struct QTask_s *v8; // edx
  void (__cdecl *v9)(struct QTask_s *, void *); // edx
  int v10; // eax

  ptHead = ptQTask->tQTaskChildren.ptHead;
  if ( ptHead->ptNext && ptHead )
  {
    v3 = QTask_nProtectedQTaskStackOffset;
    do
    {
      if ( ptHead->ptNext )
        v4 = ptHead->ptNext->ptNext != nullptr ? ptHead->ptNext : nullptr;
      else
        v4 = nullptr;
      QTask_atProtectedQTaskStack[v3].ptQTask = v4;
      pfHandler = (void (__cdecl *)(struct QTask_s *, _DWORD))QTask_aatQTaskFinalEvent[MenuItem_eUpdateActiveQTaskEvent][ptHead->eQTaskType].pfHandler;
      v6 = v3 + 1;
      QTask_nProtectedQTaskStackOffset = v6;
      if ( pfHandler )
      {
        pfHandler(ptHead, 0);
        v6 = QTask_nProtectedQTaskStackOffset;
      }
      ptHead = (struct QTask_s *)dword_849C7DC[v6];
      v3 = v6 - 1;
      QTask_nProtectedQTaskStackOffset = v3;
    }
    while ( ptHead );
  }
  else
  {
    v3 = QTask_nProtectedQTaskStackOffset;
  }
  v7 = ptQTask->tQTaskChildren.ptHead;
  if ( v7->ptNext && v7 )
  {
    do
    {
      if ( v7->ptNext )
        v8 = v7->ptNext->ptNext != nullptr ? v7->ptNext : nullptr;
      else
        v8 = nullptr;
      QTask_atProtectedQTaskStack[v3].ptQTask = v8;
      v9 = (void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[MenuItem_eActivateQTaskEvent][v7->eQTaskType].pfHandler;
      v10 = v3 + 1;
      QTask_nProtectedQTaskStackOffset = v10;
      if ( v9 )
      {
        v9(v7, pxContext);
        v10 = QTask_nProtectedQTaskStackOffset;
      }
      v7 = (struct QTask_s *)dword_849C7DC[v10];
      v3 = v10 - 1;
      QTask_nProtectedQTaskStackOffset = v3;
    }
    while ( v7 );
  }
  *(_DWORD *)&ptQTask[1].eQTaskType = 1;
}

// source: h/0/menuitemtask.c:79  [anchor-mhash]
void __cdecl MenuItemQTask_RunHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct RegisterHitboxContext_s tRegisterHitboxContext; };
    struct { char igi2_o1[4]; __int64 pxContext; };
    struct { char igi2_o2[12]; int v55; };
    struct { char igi2_o3[16]; struct MenuItemActivateContext_s tMenuActivateContext; };
    char igi2_extent[44];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *v1; // edi
  struct QTask_s *ptHead; // eax
  int v3; // ecx
  struct QTask_s *v4; // edx
  void (__cdecl *pfHandler)(struct QTask_s *, _DWORD); // edx
  int v6; // ecx
  struct QTask_s *v7; // edx
  struct QTask_s *v8; // ebp
  struct QTask_s *v9; // eax
  void (__cdecl *v10)(struct QTask_s *); // eax
  int v11; // ecx
  struct QTask_s *v12; // esi
  __int16 v13; // ax
  struct QTask_s *v14; // edx
  int v15; // ecx
  void (__cdecl *v16)(struct QTask_s *, struct RegisterHitboxContext_s *); // edx
  unsigned int v17; // edx
  int ptMiddle; // eax
  struct QReference_s *v19; // ebx
  int ptTail; // ecx
  int v21; // eax
  struct QReference_s *v22; // ebx
  int v23; // ecx
  int v24; // ebx
  int v25; // ecx
  int v26; // edx
  struct QTask_s *v27; // eax
  void (__cdecl *v28)(int, struct MenuItemActivateContext_s *); // eax
  int v29; // edx
  struct QTask_s **p_ptNext; // eax
  int v31; // edx
  int nMouseY; // ebx
  int nMouseX; // ebp
  double v34; // st7
  int v35; // esi
  int v36; // ecx
  int v37; // eax
  struct QTask_s *v38; // ecx
  int v39; // esi
  void (__cdecl *v40)(int, struct MenuItemActivateContext_s *); // ecx
  int v41; // edx
  int v42; // eax
  struct QTask_s *v43; // ecx
  int v44; // esi
  void (__cdecl *v45)(int, struct MenuItemActivateContext_s *); // ecx
  int v46; // edx
  int v47; // ecx
  int v48; // edx
  struct QTask_s *v49; // eax
  int v50; // esi
  void (__cdecl *v51)(int, struct MenuItemActivateContext_s *); // eax
  int v52; // edx
  struct QTask_s *ptQTaska = *(struct QTask_s * *)&ptQTask; // [esp+40h] [ebp+4h] ARGSLOT

  v1 = ptQTask;
  ptHead = ptQTask->tQTaskChildren.ptHead;
  if ( ptHead->ptNext && ptHead )
  {
    v3 = QTask_nProtectedQTaskStackOffset;
    do
    {
      if ( ptHead->ptNext )
        v4 = ptHead->ptNext->ptNext != nullptr ? ptHead->ptNext : nullptr;
      else
        v4 = nullptr;
      QTask_atProtectedQTaskStack[v3].ptQTask = v4;
      pfHandler = (void (__cdecl *)(struct QTask_s *, _DWORD))QTask_aatQTaskFinalEvent[MenuItem_eUpdateActiveQTaskEvent][ptHead->eQTaskType].pfHandler;
      v6 = v3 + 1;
      QTask_nProtectedQTaskStackOffset = v6;
      if ( pfHandler )
      {
        pfHandler(ptHead, 0);
        v6 = QTask_nProtectedQTaskStackOffset;
      }
      ptHead = (struct QTask_s *)dword_849C7DC[v6];
      v3 = v6 - 1;
      QTask_nProtectedQTaskStackOffset = v3;
    }
    while ( ptHead );
  }
  else
  {
    v3 = QTask_nProtectedQTaskStackOffset;
  }
  v7 = ptQTask->tQTaskChildren.ptHead;
  v8 = ptQTask + 1;
  ptQTask[1].ptNext = (struct QTask_s *)((char *)ptQTask + 44);
  ptQTask[1].tQTaskChildren.ptHead = ptQTask + 1;
  ptQTask[1].ptPrev = nullptr;
  if ( v7->ptNext && v7 )
  {
    do
    {
      if ( v7->ptNext )
        v9 = v7->ptNext->ptNext != nullptr ? v7->ptNext : nullptr;
      else
        v9 = nullptr;
      QTask_atProtectedQTaskStack[v3].ptQTask = v9;
      v10 = (void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[1][v7->eQTaskType].pfHandler;
      v11 = v3 + 1;
      QTask_nProtectedQTaskStackOffset = v11;
      if ( v10 )
      {
        v10(v7);
        v11 = QTask_nProtectedQTaskStackOffset;
      }
      v7 = (struct QTask_s *)dword_849C7DC[v11];
      v3 = v11 - 1;
      QTask_nProtectedQTaskStackOffset = v3;
    }
    while ( v7 );
  }
  v12 = ptQTask->tQTaskChildren.ptHead;
  igi2_frame.tRegisterHitboxContext.ptHitboxList = (struct HitboxList_s *)&ptQTask[1];
  if ( v12->ptNext && v12 )
  {
    v13 = MenuItemQTask_eRegisterHitboxQTaskEvent;
    do
    {
      if ( v12->ptNext )
        v14 = v12->ptNext->ptNext != nullptr ? v12->ptNext : nullptr;
      else
        v14 = nullptr;
      QTask_atProtectedQTaskStack[v3].ptQTask = v14;
      v15 = v3 + 1;
      QTask_nProtectedQTaskStackOffset = v15;
      if ( v13 == 512 )
      {
        v13 = QTask_NewQTaskEventFn(0, "Register Hitbox");
        v15 = QTask_nProtectedQTaskStackOffset;
        MenuItemQTask_eRegisterHitboxQTaskEvent = v13;
      }
      v16 = (void (__cdecl *)(struct QTask_s *, struct RegisterHitboxContext_s *))QTask_aatQTaskFinalEvent[v13][v12->eQTaskType].pfHandler;
      if ( v16 )
      {
        v16(v12, &igi2_frame.tRegisterHitboxContext);
        v15 = QTask_nProtectedQTaskStackOffset;
        v13 = MenuItemQTask_eRegisterHitboxQTaskEvent;
      }
      v12 = (struct QTask_s *)dword_849C7DC[v15];
      v3 = v15 - 1;
      QTask_nProtectedQTaskStackOffset = v3;
    }
    while ( v12 );
    v1 = ptQTask;
  }
  v17 = (unsigned int)v1[1].tQTaskRefList.ptHead;
  ptMiddle = (int)v1[1].tQTaskChildren.ptMiddle;
  v19 = v1[1].tQTaskRefList.ptMiddle;
  igi2_frame.tMenuActivateContext.bEdgeButton = v17 & ~(int)v1[1].ptParent;
  ptTail = (int)v1[1].tQTaskChildren.ptTail;
  igi2_frame.tMenuActivateContext.nMouseX = ptMiddle;
  v21 = ptMiddle - (_DWORD)v19;
  v22 = v1[1].tQTaskRefList.ptTail;
  igi2_frame.tMenuActivateContext.nMouseY = ptTail;
  v23 = ptTail - (_DWORD)v22;
  v24 = *(_DWORD *)&v1[1].eQTaskType;
  igi2_frame.tMenuActivateContext.eMenuItem = 0;
  igi2_frame.tMenuActivateContext.bCurrentButton = v17;
  igi2_frame.tMenuActivateContext.nMouseDeltaX = v21;
  igi2_frame.tMenuActivateContext.nMouseDeltaY = v23;
  if ( !v24 && (v21 || v23 || (v17 & 0x70) != 0) )
  {
    igi2_frame.pxContext = 0;
    igi2_frame.v55 = 0;
    MenuItem_Enumerate(v1, (void (__cdecl *)(struct MenuItem_s *, void *))MenuItem_ActiveMenuItemCallback, &igi2_frame.pxContext);
    if ( igi2_frame.tMenuActivateContext.nMouseDeltaX || igi2_frame.tMenuActivateContext.nMouseDeltaY || !HIDWORD(igi2_frame.pxContext) )
    {
      p_ptNext = &v8->ptNext->ptNext;
      v31 = QTask_nProtectedQTaskStackOffset;
      ptQTaska = v8->ptNext->ptNext;
      if ( ptQTaska )
      {
        nMouseY = igi2_frame.tMenuActivateContext.nMouseY;
        nMouseX = igi2_frame.tMenuActivateContext.nMouseX;
        do
        {
          v34 = *((float *)p_ptNext + 2);
          igi2_frame.pxContext = (__int64)v34;
          if ( (int)(__int64)v34 <= nMouseX )
          {
            igi2_frame.pxContext = (__int64)(*((float *)p_ptNext + 4) + *((float *)p_ptNext + 2));
            v35 = igi2_frame.pxContext;
            if ( (int)igi2_frame.pxContext >= nMouseX )
              v35 = nMouseX;
          }
          else
          {
            v35 = (__int64)v34;
          }
          igi2_frame.pxContext = (__int64)*((float *)p_ptNext + 3);
          v36 = igi2_frame.pxContext;
          if ( (int)igi2_frame.pxContext <= nMouseY )
          {
            igi2_frame.pxContext = (__int64)(*((float *)p_ptNext + 5) + *((float *)p_ptNext + 3));
            v36 = igi2_frame.pxContext;
            if ( (int)igi2_frame.pxContext >= nMouseY )
              v36 = nMouseY;
          }
          if ( v35 == nMouseX && v36 == nMouseY )
          {
            igi2_frame.tMenuActivateContext.eMenuItem = (int)p_ptNext[8][1].tQTaskRefList.ptMiddle;
            v37 = (int)p_ptNext[8]->ptParent->tQTaskChildren.ptHead;
            if ( *(_DWORD *)v37 )
            {
              for ( ; v37; QTask_nProtectedQTaskStackOffset = v31 )
              {
                if ( *(_DWORD *)v37 )
                  v38 = **(_DWORD **)v37 != 0 ? *(struct QTask_s **)v37 : nullptr;
                else
                  v38 = nullptr;
                v39 = MenuItem_eActivateQTaskEvent;
                QTask_atProtectedQTaskStack[v31].ptQTask = v38;
                v40 = (void (__cdecl *)(int, struct MenuItemActivateContext_s *))QTask_aatQTaskFinalEvent[v39][*(unsigned __int16 *)(v37 + 36)].pfHandler;
                v41 = v31 + 1;
                QTask_nProtectedQTaskStackOffset = v41;
                if ( v40 )
                {
                  v40(v37, &igi2_frame.tMenuActivateContext);
                  nMouseY = igi2_frame.tMenuActivateContext.nMouseY;
                  nMouseX = igi2_frame.tMenuActivateContext.nMouseX;
                  v41 = QTask_nProtectedQTaskStackOffset;
                }
                v37 = dword_849C7DC[v41];
                v31 = v41 - 1;
              }
            }
          }
          p_ptNext = &ptQTaska->ptNext;
          ptQTaska = ptQTaska->ptNext;
        }
        while ( ptQTaska );
      }
      if ( !igi2_frame.tMenuActivateContext.eMenuItem )
      {
        v42 = (int)v1->tQTaskChildren.ptHead;
        if ( *(_DWORD *)v42 )
        {
          for ( ; v42; QTask_nProtectedQTaskStackOffset = v31 )
          {
            if ( *(_DWORD *)v42 )
              v43 = **(_DWORD **)v42 != 0 ? *(struct QTask_s **)v42 : nullptr;
            else
              v43 = nullptr;
            v44 = MenuItem_eActivateQTaskEvent;
            QTask_atProtectedQTaskStack[v31].ptQTask = v43;
            v45 = (void (__cdecl *)(int, struct MenuItemActivateContext_s *))QTask_aatQTaskFinalEvent[v44][*(unsigned __int16 *)(v42 + 36)].pfHandler;
            v46 = v31 + 1;
            QTask_nProtectedQTaskStackOffset = v46;
            if ( v45 )
            {
              v45(v42, &igi2_frame.tMenuActivateContext);
              v46 = QTask_nProtectedQTaskStackOffset;
            }
            v42 = dword_849C7DC[v46];
            v31 = v46 - 1;
          }
        }
      }
    }
    else
    {
      igi2_frame.tMenuActivateContext.eMenuItem = *(_DWORD *)(HIDWORD(igi2_frame.pxContext) + 64);
      v25 = *(_DWORD *)(*(_DWORD *)(HIDWORD(igi2_frame.pxContext) + 32) + 8);
      if ( *(_DWORD *)v25 && v25 )
      {
        v26 = QTask_nProtectedQTaskStackOffset;
        do
        {
          if ( *(_DWORD *)v25 )
            v27 = **(_DWORD **)v25 != 0 ? *(struct QTask_s **)v25 : nullptr;
          else
            v27 = nullptr;
          QTask_atProtectedQTaskStack[v26].ptQTask = v27;
          v28 = (void (__cdecl *)(int, struct MenuItemActivateContext_s *))QTask_aatQTaskFinalEvent[MenuItem_eActivateQTaskEvent][*(unsigned __int16 *)(v25 + 36)].pfHandler;
          v29 = v26 + 1;
          QTask_nProtectedQTaskStackOffset = v29;
          if ( v28 )
          {
            v28(v25, &igi2_frame.tMenuActivateContext);
            v29 = QTask_nProtectedQTaskStackOffset;
          }
          v25 = dword_849C7DC[v29];
          v26 = v29 - 1;
          QTask_nProtectedQTaskStackOffset = v26;
        }
        while ( v25 );
      }
    }
  }
  else
  {
    *(_DWORD *)&v1[1].eQTaskType = 0;
    igi2_frame.pxContext = 0;
    igi2_frame.v55 = 0;
    MenuItem_Enumerate(v1, (void (__cdecl *)(struct MenuItem_s *, void *))MenuItem_ActiveMenuItemCallback, &igi2_frame.pxContext);
    if ( HIDWORD(igi2_frame.pxContext) )
    {
      igi2_frame.tMenuActivateContext.eMenuItem = *(_DWORD *)(HIDWORD(igi2_frame.pxContext) + 64);
      v47 = *(_DWORD *)(*(_DWORD *)(HIDWORD(igi2_frame.pxContext) + 32) + 8);
      if ( *(_DWORD *)v47 )
      {
        if ( v47 )
        {
          v48 = QTask_nProtectedQTaskStackOffset;
          do
          {
            if ( *(_DWORD *)v47 )
              v49 = **(_DWORD **)v47 != 0 ? *(struct QTask_s **)v47 : nullptr;
            else
              v49 = nullptr;
            v50 = MenuItem_eActivateQTaskEvent;
            QTask_atProtectedQTaskStack[v48].ptQTask = v49;
            v51 = (void (__cdecl *)(int, struct MenuItemActivateContext_s *))QTask_aatQTaskFinalEvent[v50][*(unsigned __int16 *)(v47 + 36)].pfHandler;
            v52 = v48 + 1;
            QTask_nProtectedQTaskStackOffset = v52;
            if ( v51 )
            {
              v51(v47, &igi2_frame.tMenuActivateContext);
              v52 = QTask_nProtectedQTaskStackOffset;
            }
            v47 = dword_849C7DC[v52];
            v48 = v52 - 1;
            QTask_nProtectedQTaskStackOffset = v48;
          }
          while ( v47 );
        }
      }
    }
  }
}

// source: h/0/menuitemtask.c:198  [anchor-mhash]
void __cdecl MenuItemQTask_MenuItemInputHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *ptHead; // edx

  ptQTask[1].tQTaskRefList.ptMiddle = (struct QReference_s *)ptQTask[1].tQTaskChildren.ptMiddle;
  ptHead = (struct QTask_s *)ptQTask[1].tQTaskRefList.ptHead;
  ptQTask[1].tQTaskRefList.ptTail = (struct QReference_s *)ptQTask[1].tQTaskChildren.ptTail;
  ptQTask[1].ptParent = ptHead;
  ptQTask[1].tQTaskChildren.ptMiddle = *(struct QTask_s **)pxContext;
  ptQTask[1].tQTaskChildren.ptTail = *((struct QTask_s **)pxContext + 1);
  ptQTask[1].tQTaskRefList.ptHead = *((struct QReference_s **)pxContext + 2);
}

// source: h/0/menuitemtask.c:219  [size]
void __cdecl MenuItemQTask_DrawHandler(struct QTask_s *ptQTask)
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

// source: h/0/menuitemtask.c:232  [size]
void __cdecl MenuItemQTask_RedrawDirtyRectangleHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *ptHead; // eax
  int v3; // edx
  struct QTask_s *v4; // ecx
  void (__cdecl *pfHandler)(struct QTask_s *, void *); // ecx
  int v6; // edx

  ptHead = ptQTask->tQTaskChildren.ptHead;
  if ( ptHead->ptNext && ptHead )
  {
    v3 = QTask_nProtectedQTaskStackOffset;
    do
    {
      if ( ptHead->ptNext )
        v4 = ptHead->ptNext->ptNext != nullptr ? ptHead->ptNext : nullptr;
      else
        v4 = nullptr;
      QTask_atProtectedQTaskStack[v3].ptQTask = v4;
      pfHandler = (void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[Sync_eRedrawDirtyRectangleQTaskEvent][ptHead->eQTaskType].pfHandler;
      v6 = v3 + 1;
      QTask_nProtectedQTaskStackOffset = v6;
      if ( pfHandler )
      {
        pfHandler(ptHead, pxContext);
        v6 = QTask_nProtectedQTaskStackOffset;
      }
      ptHead = (struct QTask_s *)dword_849C7DC[v6];
      v3 = v6 - 1;
      QTask_nProtectedQTaskStackOffset = v3;
    }
    while ( ptHead );
  }
}

// source: h/0/menuitemtask.c:245  [size]
void __cdecl MenuItemQTask_RegisterDirtyRectangleHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *ptHead; // eax
  int v3; // edx
  struct QTask_s *v4; // ecx
  void (__cdecl *pfHandler)(struct QTask_s *, void *); // ecx
  int v6; // edx

  ptHead = ptQTask->tQTaskChildren.ptHead;
  if ( ptHead->ptNext && ptHead )
  {
    v3 = QTask_nProtectedQTaskStackOffset;
    do
    {
      if ( ptHead->ptNext )
        v4 = ptHead->ptNext->ptNext != nullptr ? ptHead->ptNext : nullptr;
      else
        v4 = nullptr;
      QTask_atProtectedQTaskStack[v3].ptQTask = v4;
      pfHandler = (void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[Sync_eRegisterDirtyRectangleQTaskEvent][ptHead->eQTaskType].pfHandler;
      v6 = v3 + 1;
      QTask_nProtectedQTaskStackOffset = v6;
      if ( pfHandler )
      {
        pfHandler(ptHead, pxContext);
        v6 = QTask_nProtectedQTaskStackOffset;
      }
      ptHead = (struct QTask_s *)dword_849C7DC[v6];
      v3 = v6 - 1;
      QTask_nProtectedQTaskStackOffset = v3;
    }
    while ( ptHead );
  }
}

// source: h/0/menuitemtask.c:258  [size]
void __cdecl MenuItemQTask_RegisterHitboxHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *ptHead; // esi
  __int16 v3; // ax
  struct QTask_s *v4; // ecx
  int v5; // edx
  void (__cdecl *pfHandler)(struct QTask_s *, void *); // ecx

  ptHead = ptQTask->tQTaskChildren.ptHead;
  if ( ptHead->ptNext && ptHead )
  {
    v3 = MenuItemQTask_eRegisterHitboxQTaskEvent;
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
        v3 = QTask_NewQTaskEventFn(0, "Register Hitbox");
        MenuItemQTask_eRegisterHitboxQTaskEvent = v3;
      }
      pfHandler = (void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[v3][ptHead->eQTaskType].pfHandler;
      if ( pfHandler )
      {
        pfHandler(ptHead, pxContext);
        v3 = MenuItemQTask_eRegisterHitboxQTaskEvent;
      }
      ptHead = (struct QTask_s *)dword_849C7DC[QTask_nProtectedQTaskStackOffset--];
    }
    while ( ptHead );
  }
}

// source: h/0/menuitemtask.c:275  [size]
struct Hitbox_s *__cdecl MenuItemQTask_RegisterHitbox(
        struct RegisterHitboxContext_s *ptRegisterHitboxContext,
        struct Hitbox_s *ptHitbox)
{
  ptHitbox->ptPrev = nullptr;
  ptHitbox->ptNext = nullptr;
  return (struct Hitbox_s *)List_AddTail(ptHitbox, (int)ptRegisterHitboxContext->ptHitboxList);
}

// source: h/0/menuitemtask.c:292  [size]
__int16 __cdecl MenuItemQTask_GetRegisterHitboxQTaskEvent()
{
  __int16 result; // ax

  result = MenuItemQTask_eRegisterHitboxQTaskEvent;
  if ( MenuItemQTask_eRegisterHitboxQTaskEvent == 512 )
  {
    result = QTask_NewQTaskEventFn(0, "Register Hitbox");
    MenuItemQTask_eRegisterHitboxQTaskEvent = result;
  }
  return result;
}

// source: h/0/menuitemtask.c:309  [size]
__int16 __cdecl MenuItemQTask_GetMenuItemInputQTaskEvent()
{
  __int16 result; // ax

  result = MenuItemQTask_eMenuItemInputQTaskEvent;
  if ( MenuItemQTask_eMenuItemInputQTaskEvent == 512 )
  {
    result = QTask_NewQTaskEventFn(0, "MenuItem Input");
    MenuItemQTask_eMenuItemInputQTaskEvent = result;
  }
  return result;
}

// source: h/0/menuitemtask.c:326  [anchor-hash]
void __cdecl MenuItemQTask_Open()
{
  unsigned __int16 BaseQTaskType; // ax
  unsigned __int16 v1; // si
  __int16 v2; // ax
  __int16 v3; // di
  __int16 v4; // ax
  __int16 v5; // ax
  __int16 v6; // ax

  BaseQTaskType = QTask_GetBaseQTaskType();
  v1 = QTask_NewQTaskType("MenuItemTask", 80, BaseQTaskType, 0, 0);
  MenuItemQTask_eQTaskType = v1;
  if ( MenuItemQTask_eMenuItemInputQTaskEvent == 512 )
  {
    v2 = QTask_NewQTaskEventFn(0, "MenuItem Input");
    v1 = MenuItemQTask_eQTaskType;
    MenuItemQTask_eMenuItemInputQTaskEvent = v2;
  }
  v3 = MenuItemQTask_eRegisterHitboxQTaskEvent;
  if ( MenuItemQTask_eRegisterHitboxQTaskEvent == 512 )
  {
    v4 = QTask_NewQTaskEventFn(0, "Register Hitbox");
    v1 = MenuItemQTask_eQTaskType;
    v3 = v4;
    MenuItemQTask_eRegisterHitboxQTaskEvent = v4;
  }
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 1, MenuItemQTask_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, Screen_eDrawQTaskEvent, MenuItemQTask_DrawHandler);
  QTask_LinkQTaskEventHandlerFn(v1, Sync_eRedrawDirtyRectangleQTaskEvent, MenuItemQTask_RedrawDirtyRectangleHandler);
  QTask_LinkQTaskEventHandlerFn(v1, Sync_eRegisterDirtyRectangleQTaskEvent, MenuItemQTask_RegisterDirtyRectangleHandler);
  if ( v3 == 512 )
  {
    v5 = QTask_NewQTaskEventFn(0, "Register Hitbox");
    v1 = MenuItemQTask_eQTaskType;
    v3 = v5;
    MenuItemQTask_eRegisterHitboxQTaskEvent = v5;
  }
  QTask_LinkQTaskEventHandlerFn(v1, v3, MenuItemQTask_RegisterHitboxHandler);
  v6 = MenuItemQTask_eMenuItemInputQTaskEvent;
  if ( MenuItemQTask_eMenuItemInputQTaskEvent == 512 )
  {
    v6 = QTask_NewQTaskEventFn(0, "MenuItem Input");
    v1 = MenuItemQTask_eQTaskType;
    MenuItemQTask_eMenuItemInputQTaskEvent = v6;
  }
  QTask_LinkQTaskEventHandlerFn(v1, v6, MenuItemQTask_MenuItemInputHandler);
  QTask_LinkQTaskEventHandlerFn(v1, MenuItem_eActivateQTaskEvent, MenuItemQTask_ActivateHandler);
}

// source: h/0/menuitemtask.c:352  [size]
void __cdecl MenuItemQTask_Close()
{
  QTask_DeleteQTaskEvent(MenuItemQTask_eMenuItemInputQTaskEvent);
  QTask_DeleteQTaskEvent(MenuItemQTask_eRegisterHitboxQTaskEvent);
  QTask_DeleteQTaskType(MenuItemQTask_eQTaskType);
}

// source: h/0/menuitemtask.c:369  [anchor-callee]
void __cdecl MenuItemQTask_SetMenuItemInput(
        struct QTask_s *ptQTask,
        struct MenuItemInputContext_s *ptMenuItemInputContext)
{
  __int16 v2; // ax

  v2 = MenuItemQTask_eMenuItemInputQTaskEvent;
  if ( MenuItemQTask_eMenuItemInputQTaskEvent == 512 )
  {
    v2 = QTask_NewQTaskEventFn(0, "MenuItem Input");
    MenuItemQTask_eMenuItemInputQTaskEvent = v2;
  }
  ((void (__cdecl *)(struct QTask_s *, struct MenuItemInputContext_s *))QTask_aatQTaskFinalEvent[v2][ptQTask->eQTaskType].pfHandler)(
    ptQTask,
    ptMenuItemInputContext);
}

// source: h/0/menuitemtask.c:382  [anchor-hash]
struct QTask_s *__cdecl MenuItemQTask_New(struct QTask_s *ptParent)
{
  struct QTask_s *result; // eax

  result = QTask_NewFn(ptParent, MenuItemQTask_eQTaskType, nullptr);
  result[1].tQTaskChildren.ptMiddle = nullptr;
  result[1].tQTaskChildren.ptTail = nullptr;
  result[1].tQTaskRefList.ptHead = nullptr;
  result[1].tQTaskRefList.ptMiddle = nullptr;
  result[1].tQTaskRefList.ptTail = nullptr;
  result[1].ptParent = nullptr;
  *(_DWORD *)&result[1].eQTaskType = 0;
  return result;
}
