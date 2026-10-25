/* j/0/mission/missiontimer.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/mission/missiontimer.c:101  [size]
void __cdecl MissionTimer_GetSerializeParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = MissionTimer_ptSerializeParameterList;
}

// source: j/0/mission/missiontimer.c:117  [anchor-mhash]
void __cdecl MissionTimer_DeSerializeHandler(struct QTask_s *ptQTask, void *pxContext)
{
  QTask_DeleteQTaskAndQTaskRefSafe((struct QReference_s **)&ptQTask[5].tQTaskChildren.ptMiddle);
  Serialize_DeSerializeHandler(ptQTask, pxContext);
}

// source: j/0/mission/missiontimer.c:134  [anchor-mhash]
void __cdecl MissionTimerDrawTask_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct ClippingRect_s tClippingRect; // [esp+4h] [ebp-18h] BYREF

  ptQTask[1].tQTaskChildren.ptHead = nullptr;
  ptQTask[1].ptPrev = nullptr;
  ptQTask[1].ptNext = nullptr;
  tClippingRect.vWidth = (float)Display_tActiveMode.nWidth;
  tClippingRect.vX = 0.0;
  tClippingRect.vHeight = (float)Display_tActiveMode.nHeight;
  tClippingRect.vY = 0.0;
  RenderContext_Alloc((struct RenderContext_s *)&ptQTask[1].tQTaskChildren.ptMiddle, 1);
  RenderContext_SetClippingRect((struct RenderContext_s *)&ptQTask[1].tQTaskChildren.ptMiddle, &tClippingRect);
}

// source: j/0/mission/missiontimer.c:164  [anchor-mhash]
void __cdecl MissionTimerDrawTask_DeleteHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptPrev; // ebx
  struct QTask_s *ptNext; // eax

  ptPrev = ptQTask[1].ptPrev;
  if ( ptPrev )
    FontManager_DeleteFont((struct QSprite_s *)ptPrev);
  ptNext = ptQTask[1].ptNext;
  if ( ptNext )
    Text_Delete((struct StaticTilemap_s *)ptNext);
  RenderContext_DeAlloc((struct RenderContext_s *)&ptQTask[1].tQTaskChildren.ptMiddle);
}

// source: j/0/mission/missiontimer.c:191  [anchor-refs]
void __cdecl MissionTimerDrawTask_DrawHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptNext; // eax
  char zText[256]; // [esp+14h] [ebp-100h] BYREF

  qmemcpy(
    &RenderContext_tActiveRenderContext,
    &ptQTask[1].tQTaskChildren.ptMiddle,
    sizeof(RenderContext_tActiveRenderContext));
  ++RenderContext_nActiveRenderContextTimeStamp;
  ptQTask[1].tQTaskChildren.ptTail = nullptr;
  ptQTask[1].tQTaskChildren.ptMiddle = nullptr;
  List_AddTail(&ptQTask[1].tQTaskChildren.ptMiddle, (int)&RenderContext_tDrawList);
  if ( !ptQTask[1].ptPrev )
    ptQTask[1].ptPrev = (struct QTask_s *)FontManager_LoadFont("LOCAL:common/fonts/font3.fnt");
  if ( !ptQTask[1].ptNext )
    ptQTask[1].ptNext = (struct QTask_s *)Text_New((struct QSprite_s *)ptQTask[1].ptPrev, 0.0, 0.0, "Test");
  sprintf(
    zText,
    "%02d : %02d",
    (int)ptQTask[1].tQTaskChildren.ptHead / 1800,
    (int)ptQTask[1].tQTaskChildren.ptHead % 1800 / 30);
  Text_SetString((struct StaticTilemap_s *)ptQTask[1].ptNext, zText);
  *(_DWORD *)&ptQTask[1].ptNext->eQTaskType |= 0x80u;
  *(float *)&ptQTask[1].ptNext->ptPrev = (float)(int)(__int64)((double)Display_tActiveMode.nWidth * 0.5);
  *(float *)&ptQTask[1].ptNext->tQTaskChildren.ptHead = (float)(int)(__int64)((double)Display_tActiveMode.nHeight
                                                                            * 0.8999999761581421);
  ptNext = ptQTask[1].ptNext;
  QTilemap_Register(
    (struct QTilemap_s *)ptNext->ptNext,
    *(float *)&ptNext->ptPrev,
    *(float *)&ptNext->tQTaskChildren.ptHead,
    *(float *)&ptNext->tQTaskRefList.ptHead,
    *(float *)&ptNext->tQTaskRefList.ptMiddle,
    *(float *)&ptNext->tQTaskRefList.ptTail,
    *(float *)&ptNext->tQTaskChildren.ptTail,
    *(float *)&ptNext->tQTaskChildren.ptMiddle,
    *(_DWORD *)&ptNext->eQTaskType | 0x40000000,
    (int)ptNext->ptParent);
}

// source: j/0/mission/missiontimer.c:240  [size]
void __cdecl MissionTimerDrawTask_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ;
}

// source: j/0/mission/missiontimer.c:257  [size]
void __cdecl MissionTimer_RemoveHandler(struct QTask_s *ptQTask, void *pxContext)
{
  QTask_DeleteQTaskAndQTaskRefSafe((struct QReference_s **)&ptQTask[5].tQTaskChildren.ptMiddle);
}

// source: j/0/mission/missiontimer.c:274  [size]
void __cdecl MissionTimer_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ptQTask[1].ptNext = nullptr;
  ptQTask[1].ptPrev = nullptr;
  ptQTask[1].tQTaskChildren.ptHead = nullptr;
  *(_DWORD *)&ptQTask[2].eQTaskType = 0;
  ptQTask[3].ptNext = nullptr;
  ptQTask[3].ptPrev = nullptr;
  ptQTask[3].tQTaskChildren.ptHead = nullptr;
  *(_DWORD *)&ptQTask[4].eQTaskType = 0;
  ptQTask[5].ptNext = nullptr;
  ptQTask[5].ptPrev = nullptr;
  ptQTask[5].tQTaskChildren.ptHead = nullptr;
  ptQTask[5].tQTaskChildren.ptMiddle = nullptr;
}

// source: j/0/mission/missiontimer.c:295  [anchor-mhash]
void __cdecl MissionTimer_DeleteHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptMiddle; // eax
  struct QTask_s *ptHead; // eax

  Level_DeinitLevelExpression((struct LevelExpression_s *)&ptQTask[1]);
  Level_DeinitLevelExpression((struct LevelExpression_s *)&ptQTask[3]);
  ptMiddle = ptQTask[5].tQTaskChildren.ptMiddle;
  if ( ptMiddle )
  {
    ptHead = ptMiddle->tQTaskChildren.ptHead;
    if ( ptHead )
      QTask_Delete(ptHead);
    QReference_Delete((struct QReference_s *)ptQTask[5].tQTaskChildren.ptMiddle, &QTask_tQTaskRefPool);
  }
}

// source: j/0/mission/missiontimer.c:325  [anchor-mhash]
void __cdecl MissionTimer_RunHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptNext; // eax
  struct QTask_s *v2; // eax
  struct QTask_s *ptHead; // eax
  struct Flow_t *v4; // eax
  struct QTask_s *v5; // eax
  struct QTask_s *ptMiddle; // eax
  struct QTask_s *v7; // eax

  ptNext = ptQTask[5].ptNext;
  if ( ptNext )
  {
    if ( ptNext == (struct QTask_s *)1 )
    {
      if ( !ptQTask[5].tQTaskChildren.ptMiddle )
      {
        v2 = QTask_NewFn(Flow_ptFlow->ptScreenQTask, MissionTimerDrawTask_eQTaskType, nullptr);
        ptQTask[5].tQTaskChildren.ptMiddle = (struct QTask_s *)QTask_NewQTaskRef(v2);
      }
      if ( !ptQTask[3].ptNext
        || !ptQTask[3].ptPrev->ptNext
        || !ptQTask[3].tQTaskChildren.ptHead
        || Level_RunLevelExpression((struct LevelExpression_s *)&ptQTask[3], ptQTask) == 0.0 )
      {
        ptHead = ptQTask[5].tQTaskChildren.ptHead;
        if ( ptHead )
          ptQTask[5].tQTaskChildren.ptHead = (struct QTask_s *)((char *)ptHead - 1);
        else
          ptQTask[5].ptNext = (struct QTask_s *)2;
      }
    }
  }
  else if ( ptQTask[1].ptNext
         && ptQTask[1].ptPrev->ptNext
         && ptQTask[1].tQTaskChildren.ptHead
         && Level_RunLevelExpression((struct LevelExpression_s *)&ptQTask[1], ptQTask) != 0.0 )
  {
    v4 = Flow_ptFlow;
    ptQTask[5].ptNext = (struct QTask_s *)1;
    v5 = QTask_NewFn(v4->ptScreenQTask, MissionTimerDrawTask_eQTaskType, nullptr);
    ptQTask[5].tQTaskChildren.ptMiddle = (struct QTask_s *)QTask_NewQTaskRef(v5);
  }
  ptMiddle = ptQTask[5].tQTaskChildren.ptMiddle;
  if ( ptMiddle )
  {
    v7 = ptMiddle->tQTaskChildren.ptHead;
    if ( v7 )
      v7[1].tQTaskChildren.ptHead = ptQTask[5].tQTaskChildren.ptHead;
    if ( ptQTask[5].ptNext == (struct QTask_s *)2 )
    {
      QTask_Delete(v7);
      QReference_Delete((struct QReference_s *)ptQTask[5].tQTaskChildren.ptMiddle, &QTask_tQTaskRefPool);
      ptQTask[5].tQTaskChildren.ptMiddle = nullptr;
    }
  }
}

// source: j/0/mission/missiontimer.c:415  [anchor-mhash]
void __cdecl MissionTimer_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  Level_CompileLevelExpression((struct LevelExpression_s *)&ptQTask[1], ptQTask);
  Level_CompileLevelExpression((struct LevelExpression_s *)&ptQTask[3], ptQTask);
  ptQTask[5].tQTaskChildren.ptHead = (struct QTask_s *)(__int64)(*(float *)&ptQTask[5].ptPrev * 30.0);
}

// source: j/0/mission/missiontimer.c:434  [size]
void __cdecl MissionTimer_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = MissionTimer_ptParameterList;
}

// source: j/0/mission/missiontimer.c:452  [size]
unsigned __int16 __cdecl MissionTimer_GetQTaskType()
{
  return MissionTimer_eQTaskType;
}

// source: j/0/mission/missiontimer.c:465  [anchor-hash]
void __cdecl MissionTimer_Open()
{
  unsigned __int16 BaseQTaskType; // ax
  unsigned __int16 v1; // ax
  unsigned __int16 v2; // ax
  unsigned __int16 v3; // si
  unsigned __int16 v4; // di
  __int16 v5; // bx
  struct ParameterList_s *v6; // eax
  int v7; // edx
  unsigned __int16 v8; // si
  struct ParameterList_s *v9; // eax
  int v10; // edx

  BaseQTaskType = QTask_GetBaseQTaskType();
  MissionTimer_eQTaskType = QTask_NewQTaskType("MissionTimer", 216, BaseQTaskType, 0, 0);
  v1 = QTask_GetBaseQTaskType();
  v2 = QTask_NewQTaskType("MissionTimerDrawTask", 128, v1, 0, 0);
  v3 = MissionTimer_eQTaskType;
  v4 = v2;
  MissionTimerDrawTask_eQTaskType = v2;
  QTask_LinkQTaskEventHandlerFn(
    MissionTimer_eQTaskType,
    0,
    (void (__cdecl *)(struct QTask_s *, void *))MissionTimer_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v3, 2, MissionTimer_DeleteHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v3, 1, MissionTimer_RunHandler);
  v5 = ParameterList_eUpdateInternalDataQTaskEvent;
  QTask_LinkQTaskEventHandlerFn(v3, ParameterList_eUpdateInternalDataQTaskEvent, MissionTimer_UpdateInternalDataHandler);
  QTask_LinkQTaskEventHandlerFn(
    v3,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))MissionTimer_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(v3, DynCubeObj_eDynCubeObjRemoveQTaskEvent, MissionTimer_RemoveHandler);
  QTask_LinkQTaskEventHandlerFn(v4, 0, MissionTimerDrawTask_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v4, 2, MissionTimerDrawTask_DeleteHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v4, Screen_eDrawQTaskEvent, MissionTimerDrawTask_DrawHandler);
  QTask_LinkQTaskEventHandlerFn(
    v4,
    v5,
    (void (__cdecl *)(struct QTask_s *, void *))MissionTimerDrawTask_UpdateInternalDataHandler);
  QTask_LinkQTaskEventHandlerFn(
    v3,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveHandler);
  v6 = (struct ParameterList_s *)Mem_AllocFn(72, 4);
  v6->ptParameterListItem = (struct ParameterListItem_s *)&v6[1];
  v7 = Level_eParameterTypeVarString;
  v6->nParameters = 0;
  v6->nMaxParameters = 3;
  MissionTimer_ptParameterList = v6;
  ParameterList_AddParameter(v6, 0x28u, v7, "Start Timer Expression", 7u, nullptr);
  ParameterList_AddParameter(
    MissionTimer_ptParameterList,
    0x78u,
    Level_eParameterTypeVarString,
    "Pause Timer Expression",
    7u,
    nullptr);
  ParameterList_AddParameter(
    MissionTimer_ptParameterList,
    0xCCu,
    Level_eParameterTypeReal32,
    "Time In Seconds",
    7u,
    nullptr);
  v8 = MissionTimer_eQTaskType;
  QTask_LinkQTaskEventHandlerFn(
    MissionTimer_eQTaskType,
    Serialize_eGetSerializeParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))MissionTimer_GetSerializeParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(v8, Serialize_eDeSerializeQTaskEvent, MissionTimer_DeSerializeHandler);
  v9 = (struct ParameterList_s *)Mem_AllocFn(52, 4);
  v10 = Level_eParameterTypeInt32;
  v9->ptParameterListItem = (struct ParameterListItem_s *)&v9[1];
  v9->nParameters = 0;
  v9->nMaxParameters = 2;
  MissionTimer_ptSerializeParameterList = v9;
  ParameterList_AddParameter(v9, 0xD0u, v10, "nTicksLeft", 7u, nullptr);
  ParameterList_AddParameter(
    MissionTimer_ptSerializeParameterList,
    0xC8u,
    Level_eParameterTypeInt32,
    "eStatus",
    7u,
    nullptr);
}

// source: j/0/mission/missiontimer.c:508  [size]
void __cdecl MissionTimer_Close()
{
  int v0; // esi
  int v1; // esi

  if ( MissionTimer_ptParameterList )
  {
    v0 = *(_DWORD *)((unsigned int)&MissionTimer_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
  if ( MissionTimer_ptSerializeParameterList )
  {
    v1 = *(_DWORD *)((unsigned int)&MissionTimer_ptSerializeParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v1);
    memset(*(void **)(v1 + 8), 0xCDu, *(_DWORD *)(v1 + 16));
    free((void *)v1);
  }
  QTask_DeleteQTaskType(MissionTimer_eQTaskType);
  QTask_DeleteQTaskType(MissionTimerDrawTask_eQTaskType);
}
