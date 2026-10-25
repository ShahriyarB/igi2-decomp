/* f/1/vptask.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: f/1/vptask.c:60  [size]
void __cdecl ViewportQTask_ClearList()
{
  ViewportQTask_nList = 0;
}

// source: f/1/vptask.c:79  [anchor-callee]
void __cdecl ViewPortQTask_FindSector(struct QViewportQTask_s *ptViewPort)
{
  int isEnableCubeTree; // edx
  struct real64x3_t *p_tPos; // eax

  isEnableCubeTree = ptViewPort->isEnableCubeTree;
  p_tPos = &ptViewPort->ptQCamera->tPos;
  ptViewPort->tSectorContext.ptInsideSector = nullptr;
  ptViewPort->tSectorContext.ptInsideSectorObject = nullptr;
  ptViewPort->tSectorContext.ptPos = p_tPos;
  ptViewPort->tSectorContext.isTolerance = 0;
  if ( isEnableCubeTree )
  {
    World_TriggerQTaskEventXyzSpecificTree(
      ptViewPort->ptWorld,
      QCube_eGetSectorQTaskEvent,
      &ptViewPort->tSectorContext,
      p_tPos,
      0xFFFFFFFF,
      WORLD_DYNCUBETREE_STATIONARY);
    if ( ptViewPort->tSectorContext.ptInsideSector )
    {
      DebugConsole_PushActiveConsole(RenderInfo_tFrameInfoConsoleID);
      DebugConsole_printf(
        "Camera sector: %s\n\n",
        (char *)&ptViewPort->tSectorContext.ptInsideSector[1].tQObj.tQTask.ptPrev->tQTaskRefList);
      DebugConsole_PopActiveConsole();
    }
  }
}

// source: f/1/vptask.c:113  [size]
void __cdecl ViewportQTask_RunHandler(struct QTask_s *ptQTask)
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

// source: f/1/vptask.c:142  [anchor-caller]
void __cdecl ViewportQTask_DrawHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { float ptMatrix; };
    struct { char igi2_o1[20]; float v19; };
    struct { char igi2_o2[32]; struct QTask_s *ptMiddle; };
    struct { char igi2_o3[32]; float v21; };
    struct { char igi2_o4[36]; float v22; };
    struct { char igi2_o5[44]; __int64 ptTail; };
    struct { char igi2_o6[52]; struct real64x3_t ptPos; };
    struct { char igi2_o7[76]; struct real32x9_t v25; };
    char igi2_extent[116];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  double nWidth; // st7
  double nHeight; // st6
  double v3; // st5
  struct QTask_s *ptHead; // eax
  struct RenderContext_s *v5; // eax
  float *v6; // esi
  double v7; // st7
  struct TransContext_s *v8; // eax
  void (__cdecl *v9)(void *); // eax
  void (__cdecl **v10)(struct QCamera_s *); // esi
  struct QTask_s *v11; // ecx
  int v12; // edx
  struct QTask_s *v13; // eax
  int v14; // esi
  void (__cdecl *pfHandler)(struct QTask_s *); // eax
  int v16; // edx
  int v17; // eax

  nWidth = (double)Display_tActiveMode.nWidth;
  nHeight = (double)Display_tActiveMode.nHeight;
  v3 = *(float *)&ptQTask[1].ptPrev;
  igi2_frame.ptMiddle = ptQTask[1].tQTaskChildren.ptMiddle;
  ptHead = ptQTask[2].tQTaskChildren.ptHead;
  Viewport_nActiveID = (int)ptQTask[10].ptPrev;
  igi2_frame.v19 = (*(float *)&igi2_frame.ptMiddle + v3) * 0.5;
  ViewportQTask_ptActiveViewportQTask = ptQTask;
  igi2_frame.v22 = *(float *)&ptQTask[1].ptNext * nWidth;
  *(float *)&igi2_frame.ptTail = ((v3 - igi2_frame.v19) * *(float *)&ptHead[1].ptParent + igi2_frame.v19) * nHeight;
  igi2_frame.v21 = ((*(float *)&igi2_frame.ptMiddle - igi2_frame.v19) * *(float *)&ptHead[1].ptParent + igi2_frame.v19) * nHeight;
  *(float *)&ptQTask[1].tQTaskRefList.ptHead = (float)(__int64)igi2_frame.v22;
  *(float *)&ptQTask[1].tQTaskRefList.ptMiddle = (float)(__int64)*(float *)&igi2_frame.ptTail;
  *(float *)&ptQTask[1].tQTaskRefList.ptTail = (float)(int)(__int64)(*(float *)&ptQTask[1].tQTaskChildren.ptHead
                                                                   * nWidth
                                                                   - igi2_frame.v22);
  igi2_frame.ptTail = (__int64)(igi2_frame.v21 - *(float *)&igi2_frame.ptTail);
  *(float *)&ptQTask[1].ptParent = (float)(int)igi2_frame.ptTail;
  v5 = RenderContext_SetClippingRect(
         (struct RenderContext_s *)&ptQTask[2].tQTaskChildren.ptMiddle,
         (struct ClippingRect_s *)&ptQTask[1].tQTaskRefList);
  qmemcpy(&RenderContext_tActiveRenderContext, v5, sizeof(RenderContext_tActiveRenderContext));
  ++RenderContext_nActiveRenderContextTimeStamp;
  v5->ptPrev = nullptr;
  v5->ptNext = nullptr;
  List_AddTail(v5, (int)&RenderContext_tDrawList);
  v6 = (float *)ptQTask[2].tQTaskChildren.ptHead;
  v7 = v6[16] * *(float *)&ptQTask[1].tQTaskChildren.ptTail;
  qmemcpy(&igi2_frame.v25, v6, sizeof(igi2_frame.v25));
  qmemcpy(&igi2_frame.ptPos, v6 + 10, sizeof(igi2_frame.ptPos));
  igi2_frame.ptMatrix = v7;
  v8 = TransContext_Create((struct TransContext_s *)&ptQTask[4].tQTaskChildren, &igi2_frame.v25, &igi2_frame.ptPos, igi2_frame.ptMatrix);
  ptQTask[6].tQTaskRefList.ptHead = (struct QReference_s *)1065353216;
  TransContext_SetActiveTransContext(v8);
  igi2_frame.ptTail = (unsigned int)ptQTask[2].tQTaskChildren.ptHead[1].tQTaskRefList.ptTail;
  v9 = RenderMode_tActiveRenderMode.apfRenderModeMethod[TransContext_eSetNearClippingPlaneMethod];
  if ( v9 )
    v9(&igi2_frame.ptTail);
  QVertex_isFog = (int)ptQTask[10].tQTaskChildren.ptHead;
  v10 = ViewportQTask_apfDrawCallback;
  do
  {
    if ( *v10 )
      (*v10)((struct QCamera_s *)ptQTask[2].tQTaskChildren.ptHead);
    ++v10;
  }
  while ( (int)v10 < 127904924 );
  SortRender_ptActiveList = (struct SortRenderList_t *)ptQTask[10].tQTaskChildren.ptTail;
  SortRender_isActive = 1;
  ViewPortQTask_FindSector((struct QViewportQTask_s *)ptQTask);
  World_Draw(
    (struct World_s *)ptQTask[2].ptPrev,
    (enum bool)ptQTask[10].tQTaskChildren.ptMiddle,
    (struct GetSectorContext_t *)&ptQTask[8].tQTaskChildren.ptTail);
  SortRender_DrawList(ptQTask[10].tQTaskChildren.ptTail);
  v11 = ptQTask->tQTaskChildren.ptHead;
  if ( v11->ptNext && v11 )
  {
    v12 = QTask_nProtectedQTaskStackOffset;
    do
    {
      if ( v11->ptNext )
        v13 = v11->ptNext->ptNext != nullptr ? v11->ptNext : nullptr;
      else
        v13 = nullptr;
      v14 = Screen_eDrawQTaskEvent;
      QTask_atProtectedQTaskStack[v12].ptQTask = v13;
      pfHandler = (void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[v14][v11->eQTaskType].pfHandler;
      v16 = v12 + 1;
      QTask_nProtectedQTaskStackOffset = v16;
      if ( pfHandler )
      {
        pfHandler(v11);
        v16 = QTask_nProtectedQTaskStackOffset;
      }
      v11 = (struct QTask_s *)dword_849C7DC[v16];
      v12 = v16 - 1;
      QTask_nProtectedQTaskStackOffset = v12;
    }
    while ( v11 );
  }
  TransContext_RegisterTransContextInPrimitiveList((struct TransContext_s *)&ptQTask[4].tQTaskChildren);
  v17 = ViewportQTask_nList;
  ViewportQTask_atList[ViewportQTask_nList] = (struct QViewportQTask_s *)ptQTask;
  ViewportQTask_ptActiveViewportQTask = nullptr;
  ViewportQTask_nList = v17 + 1;
  RenderContext_RenderAll();
}

// source: f/1/vptask.c:299  [anchor-mhash]
void __cdecl ViewportQTask_DeleteHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptTail; // eax
  int v2; // esi

  ptTail = ptQTask[10].tQTaskChildren.ptTail;
  if ( ptTail )
  {
    v2 = *(_DWORD *)((unsigned int)&ptTail[-1].eQTaskType & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v2);
    memset(*(void **)(v2 + 8), 0xCDu, *(_DWORD *)(v2 + 16));
    free((void *)v2);
  }
  --ViewportQTask_nQTaskNum;
  RenderContext_DeAlloc((struct RenderContext_s *)&ptQTask[2].tQTaskChildren.ptMiddle);
  Viewport_aisIDUsed[(unsigned int)ptQTask[10].ptPrev] = 0;
}

// source: f/1/vptask.c:331  [anchor-hash]
void __cdecl ViewportQTask_Open()
{
  unsigned __int16 BaseQTaskType; // ax
  unsigned __int16 v1; // si

  BaseQTaskType = QTask_GetBaseQTaskType();
  v1 = QTask_NewQTaskType("ViewportQTask", 424, BaseQTaskType, 0, 0);
  ViewportQTask_eQTaskType = v1;
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 1, ViewportQTask_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 2, ViewportQTask_DeleteHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, Screen_eDrawQTaskEvent, ViewportQTask_DrawHandler);
  ViewportQTask_isInitialised = 1;
  Display_RegisterCallback((void (__cdecl *)())ViewportQTask_ClearList, &Display_ptStartFrameCallback);
  memset(ViewportQTask_apfDrawCallback, 0, sizeof(ViewportQTask_apfDrawCallback));
  ViewportQTask_nList = 0;
}

// source: f/1/vptask.c:372  [anchor-hash]
void __cdecl ViewportQTask_Close()
{
  struct DisplayCallbackChain_s *v0; // eax
  struct DisplayCallbackChain_s *v1; // ecx

  v0 = Display_ptStartFrameCallback;
  v1 = nullptr;
  if ( Display_ptStartFrameCallback )
  {
    while ( (void (__cdecl *)())v0->pfCallback != ViewportQTask_ClearList )
    {
      v1 = v0;
      v0 = v0->ptNext;
      if ( !v0 )
        goto LABEL_8;
    }
    if ( v1 )
    {
      v1->ptNext = v0->ptNext;
      QTask_DeleteQTaskType(ViewportQTask_eQTaskType);
      ViewportQTask_isInitialised = 0;
      return;
    }
    Display_ptStartFrameCallback = v0->ptNext;
  }
LABEL_8:
  QTask_DeleteQTaskType(ViewportQTask_eQTaskType);
  ViewportQTask_isInitialised = 0;
}

// source: f/1/vptask.c:391  [size]
unsigned __int16 __cdecl ViewportQTask_GetQTaskType()
{
  return ViewportQTask_eQTaskType;
}

// source: f/1/vptask.c:416  [anchor-callee]
struct QTask_s *__cdecl ViewportQTask_New(
        struct QTask_s *ptParent,
        float vMinX,
        float vMinY,
        float vMaxX,
        float vMaxY,
        struct World_s *ptWorld,
        struct QCamera_s *ptQCamera,
        int isMirror,
        float vBackgroundR,
        float vBackgroundG,
        float vBackgroundB,
        float vAspect)
{
  struct QTask_s *v12; // esi
  struct QTask_s *v13; // eax
  char v14; // dl
  int v15; // edi
  struct QTask_s *v16; // eax

  v12 = QTask_NewFn(ptParent, ViewportQTask_eQTaskType, nullptr);
  v12[2].tQTaskChildren.ptHead = (struct QTask_s *)ptQCamera;
  v12[2].ptPrev = (struct QTask_s *)ptWorld;
  v12[10].tQTaskChildren.ptMiddle = (struct QTask_s *)1;
  v12[10].tQTaskChildren.ptHead = (struct QTask_s *)1;
  v12[8].tQTaskRefList.ptMiddle = nullptr;
  v12[8].tQTaskRefList.ptTail = nullptr;
  v12[8].tQTaskChildren.ptTail = (struct QTask_s *)&ptQCamera->tPos;
  v12[8].tQTaskRefList.ptHead = nullptr;
  v13 = nullptr;
  if ( Viewport_aisIDUsed[0] )
  {
    do
    {
      v14 = Viewport_aisIDUsed[(_DWORD)v13 + 1];
      v13 = (struct QTask_s *)((char *)v13 + 1);
    }
    while ( v14 );
  }
  v15 = ViewportQTask_nQTaskNum;
  Viewport_aisIDUsed[(_DWORD)v13] = 1;
  v12[10].ptPrev = v13;
  *(float *)&v12[1].ptNext = vMinX;
  *(float *)&v12[1].ptPrev = vMinY;
  *(float *)&v12[1].tQTaskChildren.ptHead = vMaxX;
  *(float *)&v12[1].tQTaskChildren.ptMiddle = vMaxY;
  *(float *)&v12[9].ptParent = vBackgroundR;
  ViewportQTask_nQTaskNum = v15 + 1;
  *(float *)&v12[9].eQTaskType = vBackgroundG;
  *(float *)&v12[10].ptNext = vBackgroundB;
  *(float *)&v12[1].tQTaskChildren.ptTail = vAspect;
  RenderContext_Alloc((struct RenderContext_s *)&v12[2].tQTaskChildren.ptMiddle, 256);
  v16 = (struct QTask_s *)Mem_AllocFn(210008, 4);
  v16->ptNext = nullptr;
  v16->ptPrev = (struct QTask_s *)17500;
  v12[10].tQTaskChildren.ptTail = v16;
  return v12;
}

// source: f/1/vptask.c:480  [anchor-mhash]
struct QTask_s *__cdecl ViewportQTask_AttachMicrophone(
        struct QTask_s *ptQTask,
        struct QTask_s *ptViewportQTask,
        struct World_s *ptWorld)
{
  struct QTask_s *result; // eax

  result = Microphone_New(
             ptQTask,
             ptWorld,
             (struct real64x3_t *)&ptViewportQTask[2].tQTaskChildren.ptHead[1],
             (struct real32x9_t *)ptViewportQTask[2].tQTaskChildren.ptHead,
             (int *)&ptViewportQTask[8].tQTaskRefList.ptMiddle);
  ptViewportQTask[10].tQTaskRefList.ptHead = (struct QReference_s *)result;
  return result;
}

// source: f/1/vptask.c:500  [anchor-hash]
struct World_s *__cdecl ViewportQTask_GetActiveWorld()
{
  return (struct World_s *)ViewportQTask_ptActiveViewportQTask[2].ptPrev;
}

// source: f/1/vptask.c:525  [anchor-hash]
struct QCamera_s *__cdecl ViewportQTask_GetActiveQCamera()
{
  return (struct QCamera_s *)ViewportQTask_ptActiveViewportQTask[2].tQTaskChildren.ptHead;
}

// source: f/1/vptask.c:552  [size]
struct ClippingRect_s *__cdecl ViewportQTask_GetActiveClippingRect()
{
  return (struct ClippingRect_s *)&ViewportQTask_ptActiveViewportQTask[1].tQTaskRefList;
}

// source: f/1/vptask.c:574  [size]
int __cdecl ViewportQTask_GetNumberOfViewports()
{
  return ViewportQTask_nList;
}

// source: f/1/vptask.c:587  [size]
struct ClippingRect_s *__cdecl ViewportQTask_GetClippingRectFromID(int iViewportQTask)
{
  return &ViewportQTask_atList[iViewportQTask]->tClippingRect;
}

// source: f/1/vptask.c:602  [size]
struct ClippingRect_s *__cdecl ViewportQTask_GetClippingRect(struct QTask_s *ptQTask)
{
  return (struct ClippingRect_s *)&ptQTask[1].tQTaskRefList;
}

// source: f/1/vptask.c:620  [anchor-hash]
struct QCamera_s *__cdecl ViewportQTask_GetQCameraFromID(int iViewportQTask)
{
  return ViewportQTask_atList[iViewportQTask]->ptQCamera;
}

// source: f/1/vptask.c:635  [size]
struct QCamera_s *__cdecl ViewportQTask_GetQCamera(struct QTask_s *ptQTask)
{
  return (struct QCamera_s *)ptQTask[2].tQTaskChildren.ptHead;
}

// source: f/1/vptask.c:653  [size]
void __cdecl ViewportQTask_SetEnableCubeTree(struct QTask_s *ptQTask, char isEnable)
{
  ptQTask[10].tQTaskChildren.ptMiddle = (struct QTask_s *)isEnable;
}

// source: f/1/vptask.c:666  [size]
int __cdecl ViewportQTask_GetEnableCubeTree(struct QTask_s *ptQTask)
{
  return (int)ptQTask[10].tQTaskChildren.ptMiddle;
}

// source: f/1/vptask.c:679  [size]
int __cdecl ViewportQTask_SetEnableFog(struct QTask_s *ptQTask, int isEnable)
{
  ptQTask[10].tQTaskChildren.ptHead = (struct QTask_s *)isEnable;
  return isEnable;
}

// source: f/1/vptask.c:692  [size]
int __cdecl ViewportQTask_GetEnableFog(struct QTask_s *ptQTask)
{
  return (int)ptQTask[10].tQTaskChildren.ptHead;
}

// source: f/1/vptask.c:705  [size]
struct QTask_s *__cdecl ViewportQTask_GetActiveViewport()
{
  return ViewportQTask_ptActiveViewportQTask;
}

// source: f/1/vptask.c:718  [anchor-mhash]
void __cdecl ViewportQTask_RegisterDrawCallback(void (__cdecl *pfCallback)(struct QCamera_s *))
{
  int v1; // eax

  v1 = 0;
  while ( ViewportQTask_apfDrawCallback[v1] )
  {
    if ( ++v1 >= 15 )
      return;
  }
  ViewportQTask_apfDrawCallback[v1] = pfCallback;
}

// source: f/1/vptask.c:742  [size]
int __cdecl ViewportQTask_GetID(struct QViewportQTask_s *ptQViewportQTask)
{
  return ptQViewportQTask->nID;
}
