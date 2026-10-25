/* j/0/menusystem/cursor.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/menusystem/cursor.c:76  [anchor-mhash]
void __cdecl Cursor_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ptQTask[1].ptNext = (struct QTask_s *)pxContext;
  ptQTask[1].tQTaskRefList.ptHead = nullptr;
  ptQTask[1].ptPrev = (struct QTask_s *)320;
  ptQTask[1].tQTaskChildren.ptHead = (struct QTask_s *)240;
  ptQTask[1].tQTaskChildren.ptMiddle = (struct QTask_s *)-2;
  ptQTask[1].tQTaskChildren.ptTail = nullptr;
  ptQTask[1].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[1].tQTaskRefList.ptTail = nullptr;
  ptQTask[1].ptParent = nullptr;
  QTaskList_Register(Flow_ptDrawInterpolateQTaskList, (struct QTaskList_s *)ptQTask);
}

// source: j/0/menusystem/cursor.c:105  [size]
void __cdecl Cursor_DeleteHandler(struct QTask_s *ptQTask)
{
  QTaskList_Remove(Flow_ptDrawInterpolateQTaskList, ptQTask);
}

// source: j/0/menusystem/cursor.c:122  [anchor-mhash]
void __cdecl Cursor_DrawHandler(struct QTask_s *ptQTask)
{
  struct QReference_s *ptHead; // ecx
  float ptQSprite; // [esp+0h] [ebp-20h]
  float vX; // [esp+4h] [ebp-1Ch]

  ptHead = ptQTask[1].tQTaskRefList.ptHead;
  if ( ptHead )
  {
    vX = (float)((unsigned int)ptQTask[1].tQTaskChildren.ptHead + (unsigned int)ptQTask[1].tQTaskChildren.ptTail);
    ptQSprite = (float)((unsigned int)ptQTask[1].ptPrev + (unsigned int)ptQTask[1].tQTaskChildren.ptMiddle);
    QSprite_Register((struct QSprite_s *)ptHead, ptQSprite, vX, 128.0, 128.0, 128.0, 0, 0, 0);
  }
}

// source: j/0/menusystem/cursor.c:149  [anchor-mhash]
int __cdecl Cursor_WinProcHandler(struct HWND__ *hWnd, unsigned int iMsg, unsigned int wParam, int lParam)
{
  if ( iMsg == 512 && AppContext_tAppContext.isActive == false )
  {
    Cursor_nMouseX = (__int16)lParam;
    Cursor_nMouseY = SHIWORD(lParam);
  }
  return 1;
}

// source: j/0/menusystem/cursor.c:173  [anchor-mhash]
void __cdecl Cursor_UpdatePosition(struct Cursor_t *ptCursor)
{
  int v1; // eax
  int v2; // edx
  BOOL v3; // esi
  double v4; // st7
  BOOL v5; // eax
  int nY; // edi
  enum bool v7; // esi
  int v8; // eax
  int v9; // edi
  float vDeltaY; // [esp+8h] [ebp-Ch]

  if ( AppContext_tAppContext.isActive )
  {
    v4 = InputPort_atInputPort[0].tInput.vAnalogX * 320.0;
    vDeltaY = InputPort_atInputPort[0].tInput.vAnalogY * 240.0;
    v5 = v4 != 0.0 || vDeltaY != 0.0;
    nY = ptCursor->nY;
    v7 = v5 | ptCursor->isMoved;
    v8 = (__int64)v4 + ptCursor->nX;
    ptCursor->nX = v8;
    v9 = (__int64)vDeltaY + nY;
    ptCursor->isMoved = v7;
    ptCursor->nY = v9;
    v2 = v9;
    if ( v8 >= 0 )
    {
      if ( Display_tActiveMode.nWidth - 1 < v8 )
        v8 = Display_tActiveMode.nWidth - 1;
    }
    else
    {
      v8 = 0;
    }
    ptCursor->nX = v8;
    if ( v9 < 0 )
      goto LABEL_11;
  }
  else
  {
    v1 = Cursor_nMouseX;
    v2 = Cursor_nMouseY;
    v3 = Cursor_nMouseX != ptCursor->nX || Cursor_nMouseY != ptCursor->nY;
    ptCursor->isMoved |= v3;
    ptCursor->nX = v1;
    ptCursor->nY = v2;
    if ( v1 >= 0 )
    {
      if ( Display_tActiveMode.nWidth - 1 < v1 )
        v1 = Display_tActiveMode.nWidth - 1;
    }
    else
    {
      v1 = 0;
    }
    ptCursor->nX = v1;
    if ( v2 < 0 )
    {
LABEL_11:
      ptCursor->nY = 0;
      return;
    }
  }
  if ( Display_tActiveMode.nHeight - 1 < v2 )
    v2 = Display_tActiveMode.nHeight - 1;
  ptCursor->nY = v2;
}

// source: j/0/menusystem/cursor.c:207  [anchor-caller]
void __cdecl Cursor_RunHandler(struct QTask_s *ptQTask)
{
  Cursor_UpdatePosition((struct Cursor_t *)ptQTask);
  ptQTask[1].tQTaskRefList.ptMiddle = ptQTask[1].tQTaskRefList.ptTail;
  ptQTask[1].tQTaskRefList.ptTail = (struct QReference_s *)(Mouse_tMouse.bButton & 1);
}

// source: j/0/menusystem/cursor.c:228  [size]
void __cdecl Cursor_DrawInterpolateHandler(struct QTask_s *ptQTask)
{
  Cursor_UpdatePosition((struct Cursor_t *)ptQTask);
}

// source: j/0/menusystem/cursor.c:248  [anchor-hash]
void __cdecl Cursor_Open()
{
  unsigned __int16 BaseQTaskType; // ax
  unsigned __int16 v1; // si

  BaseQTaskType = QTask_GetBaseQTaskType();
  v1 = QTask_NewQTaskType("Cursor", 76, BaseQTaskType, 0, 0);
  Cursor_eQTaskType = v1;
  QTask_LinkQTaskEventHandlerFn(v1, 0, Cursor_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 1, Cursor_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 2, Cursor_DeleteHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, Screen_eDrawQTaskEvent, Cursor_DrawHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, Flow_eDrawInterpolateQTaskEvent, Cursor_DrawInterpolateHandler);
  Main_RegisterWinProcCallback(Cursor_WinProcHandler);
}

// source: j/0/menusystem/cursor.c:273  [size]
void __cdecl Cursor_Close()
{
  QTask_DeleteQTaskType(Cursor_eQTaskType);
}

// source: j/0/menusystem/cursor.c:288  [anchor-hash]
struct QTask_s *__cdecl Cursor_New(struct QTask_s *ptMenuManagerTask)
{
  return QTask_NewFn(nullptr, Cursor_eQTaskType, ptMenuManagerTask);
}

// source: j/0/menusystem/cursor.c:309  [size]
void __cdecl Cursor_Delete(struct QTask_s *ptQTask)
{
  QTask_Delete(ptQTask);
}

// source: j/0/menusystem/cursor.c:324  [size]
struct QSprite_s *__cdecl Cursor_SetSprite(
        struct QTask_s *ptQTask,
        struct QSprite_s *ptQSprite)
{
  ptQTask[1].tQTaskRefList.ptHead = (struct QReference_s *)ptQSprite;
  return ptQSprite;
}

// source: j/0/menusystem/cursor.c:340  [size]
struct QTask_s *__cdecl Cursor_GetPos(
        struct QTask_s *ptQTask,
        int *pnX,
        int *pnY,
        int *isButtonDown,
        int *isPrevButtonDown)
{
  struct QTask_s *result; // eax

  *pnX = (int)ptQTask[1].ptPrev;
  *pnY = (int)ptQTask[1].tQTaskChildren.ptHead;
  *isButtonDown = (int)ptQTask[1].tQTaskRefList.ptTail;
  result = (struct QTask_s *)ptQTask[1].tQTaskRefList.ptMiddle;
  *isPrevButtonDown = (int)result;
  return result;
}

// source: j/0/menusystem/cursor.c:359  [size]
enum bool __cdecl Cursor_IsMoved(struct QTask_s *ptQTask)
{
  return (enum bool)ptQTask[1].ptParent;
}

// source: j/0/menusystem/cursor.c:378  [size]
struct QTask_s *__cdecl Cursor_ResetMoved(struct QTask_s *ptQTask)
{
  ptQTask[1].ptParent = nullptr;
  return ptQTask;
}
