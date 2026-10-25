/* j/0/menusystem/menuwindow.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/menusystem/menuwindow.c:69  [anchor-mhash]
struct QTask_s *__cdecl MenuWindow_FindMenuManager(
        struct MenuWindow_t *ptMenuWindow,
        struct QTask_s *ptQTask)
{
  if ( ptQTask->eQTaskType == MenuManager_eQTaskType )
  {
LABEL_4:
    ptMenuWindow->ptMenuManager = ptQTask;
  }
  else
  {
    while ( 1 )
    {
      ptQTask = ptQTask->ptParent;
      if ( !ptQTask )
        break;
      if ( ptQTask->eQTaskType == MenuManager_eQTaskType )
        goto LABEL_4;
    }
    ptMenuWindow->ptMenuManager = nullptr;
  }
  return ptQTask;
}

// source: j/0/menusystem/menuwindow.c:105  [anchor-mhash]
void __cdecl MenuWindow_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *ptParent; // eax

  ptQTask[1].tQTaskChildren.ptTail = (struct QTask_s *)4;
  ptQTask[1].tQTaskRefList.ptHead = (struct QReference_s *)4;
  ptQTask[1].ptNext = nullptr;
  ptQTask[1].ptPrev = nullptr;
  ptQTask[1].tQTaskChildren.ptHead = nullptr;
  ptQTask[1].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[1].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[1].tQTaskRefList.ptTail = nullptr;
  ptQTask[1].ptParent = nullptr;
  BYTE2(ptQTask[2].ptNext) = 0;
  BYTE1(ptQTask[2].ptNext) = 0;
  HIBYTE(ptQTask[2].ptNext) = 0;
  LOBYTE(ptQTask[2].ptNext) = 0;
  ptQTask[2].tQTaskChildren.ptHead = nullptr;
  BYTE1(ptQTask[2].ptPrev) = 0;
  LOBYTE(ptQTask[2].ptPrev) = 0;
  BYTE2(ptQTask[2].ptPrev) = 0;
  HIBYTE(ptQTask[2].ptPrev) = 0;
  if ( pxContext )
  {
    *(_DWORD *)&ptQTask[1].eQTaskType = pxContext;
  }
  else if ( ptQTask->eQTaskType == MenuManager_eQTaskType )
  {
    *(_DWORD *)&ptQTask[1].eQTaskType = ptQTask;
  }
  else
  {
    ptParent = ptQTask->ptParent;
    if ( ptParent )
      MenuWindow_FindMenuManager((struct MenuWindow_t *)ptQTask, ptParent);
    else
      *(_DWORD *)&ptQTask[1].eQTaskType = 0;
  }
}

// source: j/0/menusystem/menuwindow.c:151  [size]
void __cdecl MenuWindow_DeleteHandler(struct QTask_s *ptQTask)
{
  ;
}

// source: j/0/menusystem/menuwindow.c:165  [anchor-mhash]
void __cdecl MenuWindow_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  int v2; // eax
  int v3; // eax

  if ( !pxContext || !*(_DWORD *)pxContext )
  {
    v2 = *(_DWORD *)&ptQTask[1].eQTaskType;
    if ( v2 )
    {
      v3 = *(_DWORD *)(v2 + 60);
      if ( v3 )
        ((void (__cdecl *)(int))QTask_aatQTaskFinalEvent[MenuWindow_eFormatEvent][*(unsigned __int16 *)(v3 + 36)].pfHandler)(v3);
    }
  }
}

// source: j/0/menusystem/menuwindow.c:191  [size]
void __cdecl MenuWindow_DrawHandler(struct QTask_s *ptQTask)
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

// source: j/0/menusystem/menuwindow.c:205  [size]
void __cdecl MenuWindow_RunHandler(struct QTask_s *ptQTask)
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

// source: j/0/menusystem/menuwindow.c:222  [size]
void __cdecl MenuWindow_ChangeDataHandler(struct QTask_s *ptQTask)
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
      v4 = MenuWindow_eChangeDataEvent;
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

// source: j/0/menusystem/menuwindow.c:236  [size]
void __cdecl MenuWindow_InitDataHandler(struct QTask_s *ptQTask)
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
      v4 = MenuWindow_eInitDataEvent;
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

// source: j/0/menusystem/menuwindow.c:250  [size]
void __cdecl MenuWindow_ChangeLanguageHandler(struct QTask_s *ptQTask)
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
      v4 = MenuWindow_eChangeLanguageEvent;
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

// source: j/0/menusystem/menuwindow.c:264  [size]
void __cdecl MenuWindow_GetSizeHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_BYTE *)pxContext = 1;
  *((_DWORD *)pxContext + 1) = ptQTask[1].tQTaskChildren.ptHead;
  *((_DWORD *)pxContext + 2) = ptQTask[1].tQTaskChildren.ptMiddle;
}

// source: j/0/menusystem/menuwindow.c:286  [anchor-mhash]
void __cdecl MenuWindow_SetPosHandler(struct QTask_s *ptQTask, void *pxContext)
{
  _DWORD *v2; // edx
  struct QReference_s *ptTail; // esi
  struct QTask_s *v4; // esi
  int v5; // edx
  char *v6; // ecx

  v2 = *((_DWORD **)pxContext + 5);
  if ( *(_BYTE *)pxContext )
  {
    ptQTask[1].ptNext = *((struct QTask_s **)pxContext + 1);
    *((_DWORD *)pxContext + 1) += (int)((char *)ptQTask[1].tQTaskChildren.ptHead + *((_DWORD *)pxContext + 3));
    goto LABEL_8;
  }
  ptTail = ptQTask[1].tQTaskRefList.ptTail;
  if ( ptTail == (struct QReference_s *)1 )
  {
    v4 = (struct QTask_s *)(v2[10] + ((signed int)(v2[12] - (unsigned int)ptQTask[1].tQTaskChildren.ptHead) >> 1));
  }
  else
  {
    if ( ptTail != (struct QReference_s *)2 )
      goto LABEL_8;
    v4 = (struct QTask_s *)v2[10];
  }
  ptQTask[1].ptNext = v4;
LABEL_8:
  if ( *((_BYTE *)pxContext + 1) )
  {
    ptQTask[1].ptPrev = *((struct QTask_s **)pxContext + 2);
    v5 = *((_DWORD *)pxContext + 2);
    v6 = (char *)ptQTask[1].tQTaskChildren.ptMiddle + *((_DWORD *)pxContext + 4);
    *((_BYTE *)pxContext + 2) = 1;
    *((_DWORD *)pxContext + 2) = &v6[v5];
  }
  else
  {
    if ( ptQTask[1].ptParent == (struct QTask_s *)1 )
      ptQTask[1].ptPrev = (struct QTask_s *)(v2[11]
                                           + ((signed int)(v2[13] - (unsigned int)ptQTask[1].tQTaskChildren.ptMiddle) >> 1));
    *((_BYTE *)pxContext + 2) = 1;
  }
}

// source: j/0/menusystem/menuwindow.c:346  [anchor-mhash]
void __cdecl MenuWindow_FormatHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { char v31[4]; };
    struct { char igi2_o1[4]; int v32; };
    struct { char igi2_o2[8]; int v33; };
    struct { char igi2_o3[12]; char v34; };
    struct { char igi2_o4[13]; char v35; };
    struct { char igi2_o5[16]; char *v36; };
    struct { char igi2_o6[20]; char *v37; };
    struct { char igi2_o7[24]; struct QTask_s *v38; };
    struct { char igi2_o8[28]; struct QReference_s *v39; };
    struct { char igi2_o9[32]; struct QTask_s *v40; };
    char igi2_extent[36];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QReference_s *ptMiddle; // eax
  struct QTask_s *ptHead; // esi
  struct QTask_s *v4; // ecx
  int v5; // ebx
  int v6; // ebp
  void (__cdecl *pfHandler)(struct QTask_s *, char *); // eax
  struct QTask_s *ptPrev; // ecx
  int v9; // eax
  struct QTask_s *v10; // edx
  struct QTask_s *v11; // edx
  struct QTask_s *v12; // esi
  struct QReference_s *v13; // eax
  int v14; // ecx
  int v15; // eax
  struct QTask_s *ptTail; // eax
  struct QTask_s *v17; // ecx
  struct QTask_s *ptNext; // edx
  struct QTask_s *v19; // eax
  int v20; // ecx
  struct QTask_s *v21; // edx
  int v22; // eax
  struct QTask_s *v23; // ecx
  void (__cdecl *v24)(struct QTask_s *, char *); // ecx
  int v25; // eax
  struct QTask_s *v26; // edx
  struct QTask_s *v27; // ecx
  int v28; // esi
  void (__cdecl *v29)(struct QTask_s *); // ecx
  int v30; // eax
  struct QTask_s *ptQTaska = *(struct QTask_s * *)&ptQTask; // [esp+30h] [ebp+4h] ARGSLOT

  ptMiddle = ptQTask[1].tQTaskRefList.ptMiddle;
  igi2_frame.v34 = 0;
  igi2_frame.v35 = 0;
  igi2_frame.v40 = ptQTask;
  if ( ptMiddle )
  {
    ptHead = ptQTask->tQTaskChildren.ptHead->ptNext != nullptr ? ptQTask->tQTaskChildren.ptHead : nullptr;
    v4 = nullptr;
    v5 = 0;
    v6 = 0;
    ptQTaska = nullptr;
    if ( ptHead )
    {
      if ( ptHead->eQTaskType != MenuTextSelection_eQTaskType
        || (ptHead = ptHead->tQTaskChildren.ptHead, ptHead->ptNext) )
      {
        if ( ptHead )
        {
          do
          {
            igi2_frame.v31[0] = 0;
            pfHandler = (void (__cdecl *)(struct QTask_s *, char *))QTask_aatQTaskFinalEvent[MenuWindow_eGetSizeEvent][ptHead->eQTaskType].pfHandler;
            if ( pfHandler )
            {
              pfHandler(ptHead, igi2_frame.v31);
              if ( igi2_frame.v31[0] )
              {
                v5 += igi2_frame.v32;
                ptQTaska = (struct QTask_s *)((char *)ptQTaska + igi2_frame.v33);
                ++v6;
              }
            }
            ptHead = ptHead->ptNext;
          }
          while ( ptHead && ptHead->ptNext );
          v4 = ptQTaska;
        }
      }
    }
    switch ( (unsigned int)ptQTask[1].tQTaskRefList.ptMiddle )
    {
      case 1u:
        ptPrev = ptQTask[1].ptPrev;
        igi2_frame.v39 = ptQTask[1].tQTaskRefList.ptHead;
        igi2_frame.v37 = (char *)ptPrev + (_DWORD)igi2_frame.v39;
        igi2_frame.v35 = 1;
        break;
      case 2u:
        v9 = ((char *)ptQTask[1].tQTaskChildren.ptMiddle - (char *)v4) / (v6 + 1);
        v10 = ptQTask[1].ptPrev;
        igi2_frame.v35 = 1;
        igi2_frame.v39 = (struct QReference_s *)v9;
        igi2_frame.v37 = (char *)v10 + v9;
        break;
      case 3u:
        v11 = ptQTask[1].tQTaskChildren.ptMiddle;
        v12 = ptQTask[1].ptPrev;
        igi2_frame.v39 = ptQTask[1].tQTaskRefList.ptHead;
        igi2_frame.v37 = (char *)((char *)v11 + (_DWORD)v12 - v6 * (_DWORD)igi2_frame.v39 - (char *)v4);
        igi2_frame.v35 = 1;
        break;
      case 4u:
        ptTail = ptQTask[1].tQTaskChildren.ptTail;
        igi2_frame.v36 = (char *)ptTail + (unsigned int)ptQTask[1].ptNext;
        goto LABEL_25;
      case 5u:
        ptTail = (struct QTask_s *)(((int)ptQTask[1].tQTaskChildren.ptHead - v5) / (v6 + 1));
        igi2_frame.v36 = (char *)ptTail + (unsigned int)ptQTask[1].ptNext;
        goto LABEL_25;
      case 6u:
        v17 = ptQTask[1].tQTaskChildren.ptHead;
        ptNext = ptQTask[1].ptNext;
        igi2_frame.v38 = ptQTask[1].tQTaskChildren.ptTail;
        igi2_frame.v36 = (char *)v17 + (_DWORD)ptNext - v6 * (_DWORD)igi2_frame.v38 - v5;
        goto LABEL_26;
      case 7u:
        v13 = ptQTask[1].tQTaskRefList.ptHead;
        igi2_frame.v37 = (char *)v13 + (unsigned int)ptQTask[1].ptPrev;
        v14 = v6 - 1;
        if ( v6 - 1 < 1 )
          v14 = 1;
        v15 = ((char *)ptQTask[1].tQTaskChildren.ptMiddle - 2 * (int)v13 - (char *)ptQTaska) / v14;
        igi2_frame.v35 = 1;
        igi2_frame.v39 = (struct QReference_s *)v15;
        break;
      case 8u:
        v19 = ptQTask[1].tQTaskChildren.ptTail;
        v20 = v6 - 1;
        igi2_frame.v36 = (char *)v19 + (unsigned int)ptQTask[1].ptNext;
        if ( v6 - 1 < 1 )
          v20 = 1;
        ptTail = (struct QTask_s *)(((int)ptQTask[1].tQTaskChildren.ptHead - v5 + -2 * (int)v19) / v20);
LABEL_25:
        igi2_frame.v38 = ptTail;
LABEL_26:
        igi2_frame.v34 = 1;
        break;
      default:
        break;
    }
  }
  v21 = ptQTask->tQTaskChildren.ptHead;
  if ( v21->ptNext && v21 )
  {
    v22 = QTask_nProtectedQTaskStackOffset;
    do
    {
      if ( v21->ptNext )
        v23 = v21->ptNext->ptNext != nullptr ? v21->ptNext : nullptr;
      else
        v23 = nullptr;
      QTask_atProtectedQTaskStack[v22].ptQTask = v23;
      v24 = (void (__cdecl *)(struct QTask_s *, char *))QTask_aatQTaskFinalEvent[MenuWindow_eSetPosEvent][v21->eQTaskType].pfHandler;
      v25 = v22 + 1;
      QTask_nProtectedQTaskStackOffset = v25;
      if ( v24 )
      {
        v24(v21, &igi2_frame.v34);
        v25 = QTask_nProtectedQTaskStackOffset;
      }
      v21 = (struct QTask_s *)dword_849C7DC[v25];
      v22 = v25 - 1;
      QTask_nProtectedQTaskStackOffset = v22;
    }
    while ( v21 );
  }
  else
  {
    v22 = QTask_nProtectedQTaskStackOffset;
  }
  v26 = ptQTask->tQTaskChildren.ptHead;
  if ( v26->ptNext && v26 )
  {
    do
    {
      if ( v26->ptNext )
        v27 = v26->ptNext->ptNext != nullptr ? v26->ptNext : nullptr;
      else
        v27 = nullptr;
      v28 = MenuWindow_eFormatEvent;
      QTask_atProtectedQTaskStack[v22].ptQTask = v27;
      v29 = (void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[v28][v26->eQTaskType].pfHandler;
      v30 = v22 + 1;
      QTask_nProtectedQTaskStackOffset = v30;
      if ( v29 )
      {
        v29(v26);
        v30 = QTask_nProtectedQTaskStackOffset;
      }
      v26 = (struct QTask_s *)dword_849C7DC[v30];
      v22 = v30 - 1;
      QTask_nProtectedQTaskStackOffset = v22;
    }
    while ( v26 );
  }
}

// source: j/0/menusystem/menuwindow.c:469  [size]
int __cdecl MenuWindow_GetFormatEvent()
{
  return MenuWindow_eFormatEvent;
}

// source: j/0/menusystem/menuwindow.c:482  [size]
int __cdecl MenuWindow_GetInitDataEvent()
{
  return MenuWindow_eInitDataEvent;
}

// source: j/0/menusystem/menuwindow.c:495  [size]
int __cdecl MenuWindow_GetChangeDataEvent()
{
  return MenuWindow_eChangeDataEvent;
}

// source: j/0/menusystem/menuwindow.c:508  [size]
int __cdecl MenuWindow_GetChangeLanguageEvent()
{
  return MenuWindow_eChangeLanguageEvent;
}

// source: j/0/menusystem/menuwindow.c:528  [anchor-callee]
void __cdecl MenuWindow_HitTest(
        struct MenuWindow_t *ptMenuWindow,
        int nXPos,
        int nYPos,
        int nWidth,
        int nHeight,
        int *pnHitXPos,
        int *pnHitYPos)
{
  struct QTask_s *ptMenuManager; // eax
  struct MenuWindow_t *p_tQTaskRefList; // edx
  int ptParent; // edx
  int v11; // eax
  char v12; // cl
  char v13; // bl
  char v14; // cl
  char v15; // al
  struct MenuWindow_t *ptMenuWindowa = *(struct MenuWindow_t * *)&ptMenuWindow; // [esp+8h] [ebp+4h] ARGSLOT
  char ptMenuWindowb = *(char *)&ptMenuWindow; // [esp+8h] [ebp+4h] ARGSLOT

  ptMenuManager = ptMenuWindow->ptMenuManager;
  if ( !ptMenuManager )
    return;
  p_tQTaskRefList = (struct MenuWindow_t *)&ptMenuManager[250].tQTaskRefList;
  ptMenuWindowa = (struct MenuWindow_t *)&ptMenuManager[250].tQTaskRefList;
  if ( ptMenuManager == (struct QTask_s *)-10020 )
    return;
  if ( !ptMenuManager[250].tQTaskChildren.ptTail[1].ptParent
    && !BYTE1(ptMenuManager[250].tQTaskRefList.ptHead)
    && !LOBYTE(p_tQTaskRefList->tQTask.ptNext)
    && !BYTE2(ptMenuManager[250].tQTaskRefList.ptHead) )
  {
    goto LABEL_13;
  }
  ptParent = (int)ptMenuManager[250].ptParent;
  if ( ptParent <= nXPos
    || (v11 = *(_DWORD *)&ptMenuManager[250].eQTaskType, v11 <= nYPos)
    || ptParent >= nXPos + nWidth
    || v11 >= nYPos + nHeight )
  {
    p_tQTaskRefList = ptMenuWindowa;
LABEL_13:
    v12 = 0;
    goto LABEL_14;
  }
  p_tQTaskRefList = ptMenuWindowa;
  v12 = 1;
LABEL_14:
  ptMenuWindowb = LOBYTE(p_tQTaskRefList->tQTask.ptNext) && ptMenuWindow->isPressed
               || BYTE1(p_tQTaskRefList->tQTask.ptNext) && v12;
  v13 = ptMenuWindow->isPressed && BYTE2(p_tQTaskRefList->tQTask.ptNext) && v12;
  v14 = (!LOBYTE(p_tQTaskRefList->tQTask.ptNext) || ptMenuWindowb) && v12;
  ptMenuWindow->isPressed = ptMenuWindowb;
  v15 = ptMenuWindow->isHilite || HIBYTE(p_tQTaskRefList->tQTask.ptNext);
  ptMenuWindow->isHilitePrevFrame = v15;
  ptMenuWindow->isClicked = v13;
  ptMenuWindow->isHilite = v14;
  if ( pnHitXPos )
    *pnHitXPos = (int)p_tQTaskRefList->tQTask.tQTaskChildren.ptMiddle;
  if ( pnHitYPos )
    *pnHitYPos = (int)p_tQTaskRefList->tQTask.tQTaskChildren.ptTail;
}

// source: j/0/menusystem/menuwindow.c:593  [anchor-mhash]
struct MenuWindow_t *__cdecl MenuWindow_DrawBorder(
        struct MenuWindow_t *ptMenuWindow,
        float vAlpha,
        float vFade,
        int isSelected)
{
  #pragma pack(push, 1)
  union
  {
    struct { float vX; };
    struct { char igi2_o1[4]; float vY; };
    struct { char igi2_o2[8]; float vWidth; };
    struct { char igi2_o3[12]; float vHeight; };
    struct { char igi2_o4[28]; float vA; };
    struct { char igi2_o5[60]; int nHeight; };
    struct { char igi2_o6[72]; float vBackgroundFade; };
    struct { char igi2_o7[80]; struct QVertexStripContext_s tContext; };
    struct { char igi2_o8[100]; struct QVertex_s atQVertex[5]; };
    char igi2_extent[280];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int nWidth; // ebp
  int v5; // esi
  int v6; // edi
  double v7; // st7
  double v8; // st7
  float *p_vG; // eax
  int v10; // edx
  struct MenuWindow_t *result; // eax

  nWidth = ptMenuWindow->nWidth;
  v5 = (Display_tActiveMode.nWidth >> 1) + ptMenuWindow->nXPos - 320;
  igi2_frame.nHeight = ptMenuWindow->nHeight;
  v6 = (Display_tActiveMode.nHeight >> 1) + ptMenuWindow->nYPos - 240;
  if ( isSelected )
    v7 = 1.0;
  else
    v7 = 0.4000000059604645;
  v8 = v7 * vFade;
  p_vG = &igi2_frame.atQVertex[0].vG;
  v10 = 4;
  do
  {
    p_vG[1] = 1.0;
    if ( isSelected )
    {
      *(p_vG - 1) = 0.8999999761581421;
      *p_vG = 0.8999999761581421;
    }
    else
    {
      *(p_vG - 1) = 0.4000000059604645;
      *p_vG = 0.6000000238418579;
    }
    *(p_vG - 2) = v8;
    *(p_vG - 4) = 0.0;
    *(p_vG - 3) = 0.0;
    *(p_vG - 5) = 1.0;
    p_vG += 9;
    --v10;
  }
  while ( v10 );
  igi2_frame.atQVertex[0].vX = (float)(v5 + 1);
  igi2_frame.atQVertex[0].vY = (float)(v6 + 1);
  igi2_frame.tContext.bFlags = 0;
  igi2_frame.atQVertex[1].vX = (float)(v5 + nWidth);
  igi2_frame.atQVertex[1].vY = igi2_frame.atQVertex[0].vY;
  igi2_frame.atQVertex[2].vX = igi2_frame.atQVertex[1].vX;
  igi2_frame.atQVertex[2].vY = (float)(v6 + igi2_frame.nHeight);
  igi2_frame.atQVertex[3].vX = igi2_frame.atQVertex[0].vX;
  igi2_frame.atQVertex[3].vY = igi2_frame.atQVertex[2].vY;
  qmemcpy(&igi2_frame.atQVertex[4], igi2_frame.atQVertex, sizeof(struct QVertex_s));
  if ( v8 <= 0.9900000095367432 )
    igi2_frame.tContext.bFlags = 0x80000;
  igi2_frame.tContext.isLine = 1;
  igi2_frame.tContext.nDepth = 0;
  igi2_frame.tContext.nStripLength = 5;
  igi2_frame.tContext.atQVertex = igi2_frame.atQVertex;
  QVertex_ptActiveTexture = nullptr;
  QVertex_ptActivePalette = nullptr;
  RenderMode_tActiveRenderMode.apfRenderModeMethod[QVertex_eRegisterQVertexStripMethod](&igi2_frame.tContext);
  igi2_frame.vBackgroundFade = vFade * 0.8999999761581421;
  igi2_frame.vA = igi2_frame.vBackgroundFade * vAlpha;
  igi2_frame.vHeight = (float)igi2_frame.nHeight;
  igi2_frame.vWidth = (float)nWidth;
  igi2_frame.vY = (float)v6;
  igi2_frame.vX = (float)v5;
  QSprite_RegisterBlankA(igi2_frame.vX, igi2_frame.vY, igi2_frame.vWidth, igi2_frame.vHeight, 0.0, 0.0, 0.0, igi2_frame.vA, 0x80000u, 0);
  return result;
}

// source: j/0/menusystem/menuwindow.c:676  [size]
struct MenuWindow_t *__cdecl MenuWindow_New(
        struct QTask_s *ptParent,
        struct QTask_s *ptMenuManager)
{
  return (struct MenuWindow_t *)QTask_NewFn(ptParent, MenuWindow_eQTaskType, ptMenuManager);
}

// source: j/0/menusystem/menuwindow.c:695  [size]
void __cdecl MenuWindow_Delete(struct MenuWindow_t *ptMenuWindow)
{
  QTask_Delete(&ptMenuWindow->tQTask);
}

// source: j/0/menusystem/menuwindow.c:709  [size]
__int16 __cdecl MenuWindow_GetSetPosEvent()
{
  return MenuWindow_eSetPosEvent;
}

// source: j/0/menusystem/menuwindow.c:723  [size]
unsigned __int16 __cdecl MenuWindow_GetQTaskType()
{
  return MenuWindow_eQTaskType;
}

// source: j/0/menusystem/menuwindow.c:736  [anchor-hash]
void __cdecl MenuWindow_Open()
{
  unsigned __int16 BaseQTaskType; // ax
  int v1; // eax
  unsigned __int16 v2; // si
  int v3; // edi

  BaseQTaskType = QTask_GetBaseQTaskType();
  MenuWindow_eQTaskType = QTask_NewQTaskType("MenuWindow", 92, BaseQTaskType, 0, 0);
  MenuWindow_eFormatEvent = QTask_NewQTaskEventNoContextFn(MenuWindow_eQTaskType, "GetSizeEvent");
  MenuWindow_eSetPosEvent = QTask_NewQTaskEventFn(MenuWindow_eQTaskType, "SetPosEvent");
  MenuWindow_eGetSizeEvent = QTask_NewQTaskEventFn(MenuWindow_eQTaskType, "FormatEvent");
  MenuWindow_eInitDataEvent = QTask_NewQTaskEventNoContextFn(MenuWindow_eQTaskType, "InitDataEvent");
  MenuWindow_eChangeDataEvent = QTask_NewQTaskEventNoContextFn(MenuWindow_eQTaskType, "ChangeDataEvent");
  v1 = QTask_NewQTaskEventNoContextFn(MenuWindow_eQTaskType, "ChangeLanguageEvent");
  v2 = MenuWindow_eQTaskType;
  v3 = v1;
  MenuWindow_eChangeLanguageEvent = v1;
  QTask_LinkQTaskEventHandlerFn(MenuWindow_eQTaskType, 0, MenuWindow_CreateHandler);
  QTask_LinkQTaskEventHandlerFn(v2, ParameterList_eUpdateInternalDataQTaskEvent, MenuWindow_UpdateInternalDataHandler);
  QTask_LinkQTaskEventHandlerFn(v2, MenuWindow_eSetPosEvent, MenuWindow_SetPosHandler);
  QTask_LinkQTaskEventHandlerFn(v2, MenuWindow_eGetSizeEvent, MenuWindow_GetSizeHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v2, 2, (void (__cdecl *)(struct QTask_s *))MenuWindow_DeleteHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v2, MenuWindow_eFormatEvent, MenuWindow_FormatHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v2, Screen_eDrawQTaskEvent, MenuWindow_DrawHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v2, 1, MenuWindow_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v2, MenuWindow_eInitDataEvent, MenuWindow_InitDataHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v2, MenuWindow_eChangeDataEvent, MenuWindow_ChangeDataHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v2, v3, MenuWindow_ChangeLanguageHandler);
  Symbol_Register(
    "LINEUPMODE_NONE",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    nullptr,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "LINEUPMODE_VERT_TOP",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)1,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "LINEUPMODE_VERT_CENTRE",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)2,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "LINEUPMODE_VERT_BOTTOM",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)3,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "LINEUPMODE_VERT_FILLOUT",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)7,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "LINEUPMODE_HOR_LEFT",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)4,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "LINEUPMODE_HOR_CENTRE",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)5,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "LINEUPMODE_HOR_RIGHT",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)6,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "LINEUPMODE_HOR_FILLOUT",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)8,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "ALIGNMODE_NONE",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    nullptr,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "ALIGNMODE_CENTRE",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)1,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "ALIGNMODE_LEFT",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)2,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
}

// source: j/0/menusystem/menuwindow.c:789  [anchor-hash]
void __cdecl MenuWindow_Close()
{
  Symbol_Remove("LINEUPMODE_NONE");
  Symbol_Remove("LINEUPMODE_VERT_TOP");
  Symbol_Remove("LINEUPMODE_VERT_CENTRE");
  Symbol_Remove("LINEUPMODE_VERT_BOTTOM");
  Symbol_Remove("LINEUPMODE_VERT_FILLOUT");
  Symbol_Remove("LINEUPMODE_HOR_LEFT");
  Symbol_Remove("LINEUPMODE_HOR_CENTRE");
  Symbol_Remove("LINEUPMODE_HOR_RIGHT");
  Symbol_Remove("LINEUPMODE_HOR_FILLOUT");
  Symbol_Remove("ALIGNMODE_NONE");
  Symbol_Remove("ALIGNMODE_CENTRE");
  Symbol_Remove("ALIGNMODE_LEFT");
  QTask_DeleteQTaskEventNoContext(MenuWindow_eFormatEvent);
  QTask_DeleteQTaskEventNoContext(MenuWindow_eInitDataEvent);
  QTask_DeleteQTaskEventNoContext(MenuWindow_eChangeDataEvent);
  QTask_DeleteQTaskEventNoContext(MenuWindow_eChangeLanguageEvent);
  QTask_DeleteQTaskEvent(MenuWindow_eSetPosEvent);
  QTask_DeleteQTaskEvent(MenuWindow_eGetSizeEvent);
  QTask_DeleteQTaskType(MenuWindow_eQTaskType);
  MenuWindow_eQTaskType = 512;
}
