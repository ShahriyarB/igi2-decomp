/* h/0/sync.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: h/0/sync.c:50  [size]
void __cdecl Sync_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ptQTask[1].ptNext = nullptr;
  ptQTask[1].ptPrev = nullptr;
  ptQTask[21].tQTaskChildren.ptHead = nullptr;
  ptQTask[41].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[61].tQTaskChildren.ptTail = nullptr;
  Sync_ptSyncQTask = ptQTask;
}

// source: h/0/sync.c:78  [size]
void __cdecl Sync_RunHandler(struct QTask_s *ptQTask)
{
  ;
}

// source: h/0/sync.c:93  [size]
void __cdecl Sync_DeleteHandler(struct QTask_s *ptQTask)
{
  Sync_ptSyncQTask = nullptr;
}

// source: h/0/sync.c:111  [anchor-mhash]
void __cdecl Sync_DrawHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct DirtyRectangleList_t *ptDirtyRectangleList; };
    struct { char igi2_o1[4]; int iDirtyRectangle; };
    struct { char igi2_o2[8]; unsigned __int16 *pnSourceBuffer; };
    struct { char igi2_o3[12]; struct DisplayBlitContext_s tDisplayBlitContext; };
    char igi2_extent[52];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *v1; // eax
  struct QTask_s *ptNext; // ecx
  struct QTaskNodeList_s *p_tQTaskChildren; // esi
  int *p_ptTail; // esi
  struct QTask_s *ptTail; // edx
  int v6; // ebx
  int v7; // ebp
  int v8; // ecx
  int v9; // edx
  int v10; // edx

  v1 = ptQTask;
  ptNext = ptQTask[1].ptNext;
  if ( ptNext )
  {
    p_tQTaskChildren = &ptQTask[21].tQTaskChildren;
    igi2_frame.ptDirtyRectangleList = (struct DirtyRectangleList_t *)&ptQTask[21].tQTaskChildren;
  }
  else
  {
    igi2_frame.ptDirtyRectangleList = (struct DirtyRectangleList_t *)&ptQTask[41].tQTaskChildren.ptMiddle;
    p_tQTaskChildren = (struct QTaskNodeList_s *)&ptQTask[41].tQTaskChildren.ptMiddle;
  }
  ptQTask[1].ptNext = (struct QTask_s *)((unsigned int)ptNext ^ 1);
  igi2_frame.iDirtyRectangle = 0;
  if ( (int)p_tQTaskChildren->ptHead <= 0 )
  {
    p_tQTaskChildren->ptHead = nullptr;
  }
  else
  {
    p_ptTail = (int *)&p_tQTaskChildren->ptTail;
    while ( 1 )
    {
      ptTail = v1[61].tQTaskChildren.ptTail;
      v6 = *p_ptTail;
      v7 = *(p_ptTail - 1);
      igi2_frame.pnSourceBuffer = (unsigned __int16 *)((char *)ptTail->tQTaskChildren.ptHead
                                          + 2 * v7
                                          + 2 * *p_ptTail * (int)ptTail->ptNext);
      memset(&igi2_frame.tDisplayBlitContext, 0, sizeof(igi2_frame.tDisplayBlitContext));
      igi2_frame.tDisplayBlitContext.pxSourceBuffer = igi2_frame.pnSourceBuffer;
      v8 = p_ptTail[1];
      igi2_frame.tDisplayBlitContext.tRenderPrimitive.ePrimType = Display_eBlitPrim;
      igi2_frame.tDisplayBlitContext.isFrontBuffer = 0;
      v9 = 4 * (int)ptTail->ptNext;
      igi2_frame.tDisplayBlitContext.nDestinationWidth = v8;
      igi2_frame.tDisplayBlitContext.nSourceModulo = v9;
      v10 = p_ptTail[2];
      igi2_frame.tDisplayBlitContext.nDestinationX = v7;
      igi2_frame.tDisplayBlitContext.nDestinationY = v6;
      igi2_frame.tDisplayBlitContext.nDestinationHeight = v10;
      RenderMode_tActiveRenderMode.apfRenderModeMethod[Display_eBlitPrim](&igi2_frame.tDisplayBlitContext);
      dword_834E068 = (int)&igi2_frame.tDisplayBlitContext;
      p_ptTail += 4;
      if ( ++igi2_frame.iDirtyRectangle >= igi2_frame.ptDirtyRectangleList->nDirtyRectangle )
        break;
      v1 = ptQTask;
    }
    igi2_frame.ptDirtyRectangleList->nDirtyRectangle = 0;
  }
}

// source: h/0/sync.c:182  [anchor-hash]
void __cdecl Sync_Open()
{
  unsigned __int16 BaseQTaskType; // ax
  __int16 v1; // ax
  unsigned __int16 v2; // si

  BaseQTaskType = QTask_GetBaseQTaskType();
  Sync_eQTaskType = QTask_NewQTaskType("Sync", 2460, BaseQTaskType, 0, 0);
  Sync_eRegisterDirtyRectangleQTaskEvent = QTask_NewQTaskEventFn(0, "RegisterDirtyRectangle");
  v1 = QTask_NewQTaskEventFn(0, "RedrawDirtyRectangle");
  v2 = Sync_eQTaskType;
  Sync_eRedrawDirtyRectangleQTaskEvent = v1;
  QTask_LinkQTaskEventHandlerFn(Sync_eQTaskType, 0, (void (__cdecl *)(struct QTask_s *, void *))Sync_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v2, 1, (void (__cdecl *)(struct QTask_s *))Sync_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v2, 2, (void (__cdecl *)(struct QTask_s *))Sync_DeleteHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v2, Screen_eDrawQTaskEvent, Sync_DrawHandler);
}

// source: h/0/sync.c:207  [size]
void __cdecl Sync_Close()
{
  QTask_DeleteQTaskEvent(Sync_eRegisterDirtyRectangleQTaskEvent);
  QTask_DeleteQTaskEvent(Sync_eRedrawDirtyRectangleQTaskEvent);
  QTask_DeleteQTaskType(Sync_eQTaskType);
}

// source: h/0/sync.c:226  [size]
struct QTask_s *__cdecl Sync_New(struct QTask_s *ptParent, struct OffscreenBuffer_s *ptOffscreenBuffer)
{
  struct QTask_s *result; // eax

  result = QTask_NewFn(ptParent, Sync_eQTaskType, nullptr);
  result[61].tQTaskChildren.ptTail = (struct QTask_s *)ptOffscreenBuffer;
  return result;
}

// source: h/0/sync.c:256  [size]
struct QTask_s *__cdecl Sync_GetSyncQTask()
{
  return Sync_ptSyncQTask;
}

// source: h/0/sync.c:272  [size]
struct Sync_t *__cdecl Sync_GetSync()
{
  return (struct Sync_t *)Sync_ptSyncQTask;
}

// source: h/0/sync.c:290  [size]
__int16 __cdecl Sync_GetRegisterDirtyRectangleQTaskEvent()
{
  return Sync_eRegisterDirtyRectangleQTaskEvent;
}

// source: h/0/sync.c:307  [size]
__int16 __cdecl Sync_GetRedrawDirtyRectangleQTaskEvent()
{
  return Sync_eRedrawDirtyRectangleQTaskEvent;
}

// source: h/0/sync.c:322  [anchor-mhash]
int __cdecl Sync_RegisterDirtyRectangle(struct DirtyRectangle_t tDirtyRectangle, int isVRAMBufferOnly)
{
  bool v2; // zf
  int result; // eax

  v2 = isVRAMBufferOnly == 0;
  result = (int)Sync_ptSyncQTask;
  if ( v2 )
  {
    *((struct DirtyRectangle_t *)&Sync_ptSyncQTask[1].tQTaskChildren.ptHead + (int)Sync_ptSyncQTask[1].ptPrev) = tDirtyRectangle;
    ++*(_DWORD *)(result + 44);
  }
  *(struct DirtyRectangle_t *)(16 * (*(_DWORD *)(result + 848))++ + result + 852) = tDirtyRectangle;
  *(struct DirtyRectangle_t *)(16 * (*(_DWORD *)(result + 1652))++ + result + 1656) = tDirtyRectangle;
  return result;
}

// source: h/0/sync.c:370  [anchor-mhash]
int __cdecl Sync_InsideDirtyRectangle(
        int nX,
        int nY,
        int nWidth,
        int nHeight,
        struct DirtyRectangle_t *ptDirtyRectangle)
{
  int v5; // ebp
  int v6; // esi
  int v7; // edi
  int v8; // ebx
  int v9; // eax
  int v10; // ebx
  int v11; // edx
  int v12; // edi
  int v13; // edi
  int v14; // edx
  int v15; // ecx
  int v17; // [esp+10h] [ebp-8h]
  int v18; // [esp+14h] [ebp-4h]
  int nYa = *(int *)&nHeight; // [esp+20h] [ebp+8h] ARGSLOT

  v5 = nY;
  v6 = ptDirtyRectangle->nY;
  v7 = nX + nWidth;
  v8 = nHeight + nY;
  v9 = ptDirtyRectangle->nX;
  v17 = v7;
  nYa = nHeight + nY;
  if ( ptDirtyRectangle->nX >= nX && v9 <= v7 && v6 >= nY && v6 <= v8 )
    return 1;
  v18 = ptDirtyRectangle->nWidth;
  v10 = v9 + v18;
  if ( v9 + v18 >= nX && v10 <= v7 && v6 >= nY && v6 <= nYa )
    return 1;
  v11 = ptDirtyRectangle->nHeight;
  v12 = v11 + v6;
  if ( v9 >= nX )
  {
    v5 = nY;
    if ( v9 <= v17 && v12 >= nY )
    {
      if ( v12 <= nYa )
        return 1;
      v5 = nY;
    }
  }
  if ( v10 >= nX )
  {
    v5 = nY;
    if ( v10 <= v17 && v12 >= nY && v12 <= nYa )
      return 1;
  }
  v13 = v9 + v18;
  v14 = v6 + v11;
  if ( nX >= v9 && nX <= v13 && v5 >= v6 && v5 <= v14 )
    return 1;
  if ( v17 >= v9 && v17 <= v13 && v5 >= v6 && v5 <= v14 )
    return 1;
  if ( nX < v9 || nX > v13 )
  {
    v15 = nYa;
  }
  else
  {
    v15 = nYa;
    if ( nYa >= v6 && nYa <= v14 )
      return 1;
  }
  return v17 >= v9 && v17 <= v13 && v15 >= v6 && v15 <= v14;
}

// source: h/0/sync.c:500  [anchor-hash]
struct QTask_s *__cdecl Sync_RegisterDirtyRectangleChildren(struct QTask_s *ptQTask)
{
  struct QTask_s *result; // eax
  int v2; // edx
  struct QTask_s *v3; // ecx
  void (__cdecl *pfHandler)(struct QTask_s *, _DWORD); // ecx
  int v5; // edx

  result = ptQTask->tQTaskChildren.ptHead;
  if ( result->ptNext && result )
  {
    v2 = QTask_nProtectedQTaskStackOffset;
    do
    {
      if ( result->ptNext )
        v3 = result->ptNext->ptNext != nullptr ? result->ptNext : nullptr;
      else
        v3 = nullptr;
      QTask_atProtectedQTaskStack[v2].ptQTask = v3;
      pfHandler = (void (__cdecl *)(struct QTask_s *, _DWORD))QTask_aatQTaskFinalEvent[Sync_eRegisterDirtyRectangleQTaskEvent][result->eQTaskType].pfHandler;
      v5 = v2 + 1;
      QTask_nProtectedQTaskStackOffset = v5;
      if ( pfHandler )
      {
        pfHandler(result, 0);
        v5 = QTask_nProtectedQTaskStackOffset;
      }
      result = (struct QTask_s *)dword_849C7DC[v5];
      v2 = v5 - 1;
      QTask_nProtectedQTaskStackOffset = v2;
    }
    while ( result );
  }
  return result;
}

// source: h/0/sync.c:518  [anchor-mhash]
void __cdecl Sync_RedrawDirtyRectangleChildren(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct OffscreenBuffer_s **p_ptTail; };
    struct { char igi2_o1[4]; struct RedrawDirtyRectangleContext_t tRedrawDirtyRectangleContext; };
    char igi2_extent[24];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s **p_ptPrev; // ebx
  int v2; // ebp
  int v3; // edx
  int *p_tQTaskChildren; // edi
  int v5; // eax
  struct QTask_s *ptHead; // eax
  struct QTask_s *v7; // ecx
  void (__cdecl *pfHandler)(struct QTask_s *, struct RedrawDirtyRectangleContext_t *); // ecx
  int v9; // edx

  p_ptPrev = &Sync_ptSyncQTask[1].ptPrev;
  v2 = 0;
  if ( (int)Sync_ptSyncQTask[1].ptPrev > 0 )
  {
    v3 = QTask_nProtectedQTaskStackOffset;
    igi2_frame.p_ptTail = (struct OffscreenBuffer_s **)&Sync_ptSyncQTask[61].tQTaskChildren.ptTail;
    p_tQTaskChildren = (int *)&Sync_ptSyncQTask[1].tQTaskChildren;
    do
    {
      igi2_frame.tRedrawDirtyRectangleContext.tDirtyRectangle.nX = *p_tQTaskChildren;
      igi2_frame.tRedrawDirtyRectangleContext.tDirtyRectangle.nY = p_tQTaskChildren[1];
      v5 = p_tQTaskChildren[3];
      igi2_frame.tRedrawDirtyRectangleContext.tDirtyRectangle.nWidth = p_tQTaskChildren[2];
      igi2_frame.tRedrawDirtyRectangleContext.tDirtyRectangle.nHeight = v5;
      igi2_frame.tRedrawDirtyRectangleContext.ptOffscreenBuffer = *igi2_frame.p_ptTail;
      ptHead = ptQTask->tQTaskChildren.ptHead;
      if ( ptHead->ptNext && ptHead )
      {
        do
        {
          if ( ptHead->ptNext )
            v7 = ptHead->ptNext->ptNext != nullptr ? ptHead->ptNext : nullptr;
          else
            v7 = nullptr;
          QTask_atProtectedQTaskStack[v3].ptQTask = v7;
          pfHandler = (void (__cdecl *)(struct QTask_s *, struct RedrawDirtyRectangleContext_t *))QTask_aatQTaskFinalEvent[Sync_eRedrawDirtyRectangleQTaskEvent][ptHead->eQTaskType].pfHandler;
          v9 = v3 + 1;
          QTask_nProtectedQTaskStackOffset = v9;
          if ( pfHandler )
          {
            pfHandler(ptHead, &igi2_frame.tRedrawDirtyRectangleContext);
            v9 = QTask_nProtectedQTaskStackOffset;
          }
          ptHead = (struct QTask_s *)dword_849C7DC[v9];
          v3 = v9 - 1;
          QTask_nProtectedQTaskStackOffset = v3;
        }
        while ( ptHead );
      }
      ++v2;
      p_tQTaskChildren += 4;
    }
    while ( v2 < (int)*p_ptPrev );
  }
  *p_ptPrev = nullptr;
}
