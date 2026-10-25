/* j/0/effects/raineffect.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/effects/raineffect.c:90  [anchor-mhash]
void __cdecl RainEffect_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  BYTE1(ptQTask[1].ptPrev) = 1;
  LOBYTE(ptQTask[1].ptPrev) = 1;
  ptQTask[1].ptParent = (struct QTask_s *)1;
  ptQTask[1].ptNext = nullptr;
  ptQTask[1].tQTaskChildren.ptHead = (struct QTask_s *)1112014848;
  ptQTask[1].tQTaskChildren.ptMiddle = (struct QTask_s *)1101004800;
  ptQTask[1].tQTaskChildren.ptTail = (struct QTask_s *)1050673152;
  ptQTask[1].tQTaskRefList.ptHead = (struct QReference_s *)1065353216;
  ptQTask[1].tQTaskRefList.ptMiddle = (struct QReference_s *)1065353216;
  ptQTask[1].tQTaskRefList.ptTail = (struct QReference_s *)1065353216;
  *(_DWORD *)&ptQTask[1].eQTaskType = 0;
  ptQTask[2].ptNext = nullptr;
  ptQTask[2].ptPrev = nullptr;
  ptQTask[3].ptParent = nullptr;
}

// source: j/0/effects/raineffect.c:117  [size]
void __cdecl RainEffect_RegisterScriptSymbolsHandler(struct QTask_s *ptQTask)
{
  ;
}

// source: j/0/effects/raineffect.c:146  [size]
void __cdecl RainEffect_RemoveScriptSymbolsHandler(struct QTask_s *ptQTask)
{
  ;
}

// source: j/0/effects/raineffect.c:178  [anchor-mhash]
void __cdecl RainEffect_RunHandler(struct QTask_s *ptQTask)
{
  int v1; // ecx

  LOBYTE(v1) = 1;
  if ( ptQTask[1].ptNext )
  {
    if ( *(_DWORD *)&ptQTask[1].eQTaskType && ptQTask[2].ptNext->ptNext )
    {
      if ( ptQTask[2].ptPrev )
        v1 = (__int64)Level_RunLevelExpression((struct LevelExpression_s *)&ptQTask[1].eQTaskType, ptQTask);
    }
    LOBYTE(ptQTask[1].ptNext[554].eQTaskType) = v1;
    Rain_UpdateParticles(ptQTask[1].ptNext);
  }
}

// source: j/0/effects/raineffect.c:208  [anchor-mhash]
void __cdecl RainEffect_DeSerializeDoneHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *ptNext; // eax

  ptNext = ptQTask[1].ptNext;
  if ( ptNext )
  {
    if ( !BYTE1(ptQTask[1].ptPrev) )
      ptNext[554].ptParent = nullptr;
  }
}

// source: j/0/effects/raineffect.c:227  [size]
void __cdecl RainEffect_RegisterHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *ptNext; // eax

  ptNext = ptQTask[1].ptNext;
  if ( ptNext )
    ((void (__cdecl *)(struct QTask_s *, ...))QTask_aatQTaskFinalEvent[DynCubeObj_eDynCubeObjRegisterQTaskEvent][ptNext->eQTaskType].pfHandler)(ptQTask[1].ptNext, pxContext);
}

// source: j/0/effects/raineffect.c:246  [size]
void __cdecl RainEffect_RemoveHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *ptNext; // eax

  ptNext = ptQTask[1].ptNext;
  if ( ptNext )
    ((void (__cdecl *)(struct QTask_s *, ...))QTask_aatQTaskFinalEvent[DynCubeObj_eDynCubeObjRemoveQTaskEvent][ptNext->eQTaskType].pfHandler)(ptQTask[1].ptNext, pxContext);
}

// source: j/0/effects/raineffect.c:265  [anchor-mhash]
void __cdecl RainEffect_DeleteHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptNext; // esi
  int v2; // ecx
  struct QReference_s *v3; // eax
  void (__cdecl *pfHandler)(struct QTask_s *); // eax

  ptNext = ptQTask[1].ptNext;
  if ( ptNext )
    Rain_Delete(ptNext, Game_ptGame->ptWorld);
  v2 = 0;
  while ( 1 )
  {
    v3 = Level_atLevelQTaskID[v2];
    if ( v3 )
    {
      if ( v3->pxObject == ptQTask )
        break;
    }
    if ( ++v2 >= 4096 )
      goto LABEL_11;
  }
  if ( v2 >= 0 )
  {
    pfHandler = (void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[Level_eRemoveLevelScriptSymbolsEvent][ptQTask->eQTaskType].pfHandler;
    if ( pfHandler )
      pfHandler(ptQTask);
  }
LABEL_11:
  Level_DeinitLevelExpression((struct LevelExpression_s *)&ptQTask[1].eQTaskType);
}

// source: j/0/effects/raineffect.c:296  [size]
void __cdecl RainEffect_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = RainEffect_ptParameterList;
}

// source: j/0/effects/raineffect.c:312  [anchor-mhash]
void __cdecl RainEffect_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *ptNext; // esi
  char v3; // dl
  struct GameTexture_s *v4; // ecx
  struct QTask_s *v5; // eax
  int ptParent; // eax
  float vTraceLineTop; // [esp+0h] [ebp-14h]
  float vTraceLineBottom; // [esp+4h] [ebp-10h]
  struct QTask_s *vTraceLineBottoma; // [esp+4h] [ebp-10h]

  if ( BYTE1(ptQTask[1].ptPrev) != LOBYTE(ptQTask[1].ptPrev) )
  {
    ptNext = ptQTask[1].ptNext;
    if ( ptNext )
    {
      Rain_Delete(ptNext, Game_ptGame->ptWorld);
      ptQTask[1].ptNext = nullptr;
    }
  }
  if ( !ptQTask[1].ptNext && AppContext_tAppContext.isMainMenu == false )
  {
    v3 = BYTE1(ptQTask[1].ptPrev);
    v4 = RainEffect_ptRainTexture;
    if ( !v3 )
      v4 = RainEffect_ptSnowTexture;
    vTraceLineBottom = *(float *)&ptQTask[1].tQTaskChildren.ptMiddle * 4096.0;
    vTraceLineTop = *(float *)&ptQTask[1].tQTaskChildren.ptHead * 4096.0;
    v5 = Rain_New(Game_ptGame->ptWorld, &v4->tTexInfo, (enum bool)v3, vTraceLineTop, vTraceLineBottom);
    vTraceLineBottoma = ptQTask[1].tQTaskChildren.ptTail;
    ptQTask[1].ptNext = v5;
    Rain_SetAlpha(v5, *(float *)&vTraceLineBottoma);
    Rain_SetRGB(
      ptQTask[1].ptNext,
      *(float *)&ptQTask[1].tQTaskRefList.ptHead,
      *(float *)&ptQTask[1].tQTaskRefList.ptMiddle,
      *(float *)&ptQTask[1].tQTaskRefList.ptTail);
    ptParent = (int)ptQTask[1].ptParent;
    if ( ptParent >= 1 )
    {
      if ( ptParent > 32 )
        ptParent = 32;
    }
    else
    {
      ptParent = 1;
    }
    ptQTask[1].ptNext[556].tQTaskChildren.ptMiddle = (struct QTask_s *)ptParent;
  }
  Level_CompileLevelExpression((struct LevelExpression_s *)&ptQTask[1].eQTaskType, ptQTask);
  LOBYTE(ptQTask[1].ptPrev) = BYTE1(ptQTask[1].ptPrev);
}

// source: j/0/effects/raineffect.c:361  [anchor-hash]
void __cdecl RainEffect_Open()
{
  unsigned __int16 BaseQTaskType; // ax
  unsigned __int16 v1; // si
  struct ParameterList_s *v2; // eax
  int v3; // edx

  BaseQTaskType = QTask_GetBaseQTaskType();
  v1 = QTask_NewQTaskType("RainEffect", 156, BaseQTaskType, 0, 0);
  RainEffect_eQTaskType = v1;
  QTask_LinkQTaskEventHandlerFn(
    v1,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveHandler);
  QTask_LinkQTaskEventHandlerFn(v1, 0, RainEffect_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 2, RainEffect_DeleteHandler);
  QTask_LinkQTaskEventHandlerFn(
    v1,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))RainEffect_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(v1, ParameterList_eUpdateInternalDataQTaskEvent, RainEffect_UpdateInternalDataHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 1, RainEffect_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(
    v1,
    Level_eRegisterLevelScriptSymbolsEvent,
    (void (__cdecl *)(struct QTask_s *))RainEffect_RegisterScriptSymbolsHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(
    v1,
    Level_eRemoveLevelScriptSymbolsEvent,
    (void (__cdecl *)(struct QTask_s *))RainEffect_RemoveScriptSymbolsHandler);
  QTask_LinkQTaskEventHandlerFn(v1, DynCubeObj_eDynCubeObjRegisterQTaskEvent, RainEffect_RegisterHandler);
  QTask_LinkQTaskEventHandlerFn(v1, DynCubeObj_eDynCubeObjRemoveQTaskEvent, RainEffect_RemoveHandler);
  QTask_LinkQTaskEventHandlerFn(v1, Serialize_eDeSerializeDoneQTaskEvent, RainEffect_DeSerializeDoneHandler);
  v2 = (struct ParameterList_s *)Mem_AllocFn(152, 4);
  v3 = Level_eParameterTypebool8;
  v2->ptParameterListItem = (struct ParameterListItem_s *)&v2[1];
  v2->nParameters = 0;
  v2->nMaxParameters = 7;
  RainEffect_ptParameterList = v2;
  ParameterList_AddParameter(v2, 0x2Du, v3, "Is Rain", 7u, nullptr);
  ParameterList_AddParameterMinMax(
    RainEffect_ptParameterList,
    0x30u,
    Level_eParameterTypeReal32,
    "Traceline start",
    7u,
    5.0,
    150.0);
  ParameterList_AddParameterMinMax(
    RainEffect_ptParameterList,
    0x34u,
    Level_eParameterTypeReal32,
    "Traceline end",
    7u,
    5.0,
    150.0);
  ParameterList_AddParameter(RainEffect_ptParameterList, 0x3Cu, Level_eParameterTypeRGB, "Rain Colour", 7u, nullptr);
  ParameterList_AddParameterMinMax(
    RainEffect_ptParameterList,
    0x38u,
    Level_eParameterTypeReal32,
    "Rain Alpha",
    7u,
    0.0,
    1.0);
  ParameterList_AddParameterMinMax(
    RainEffect_ptParameterList,
    0x48u,
    Level_eParameterTypeInt32,
    "Density",
    7u,
    0.0,
    32.0);
  ParameterList_AddParameter(RainEffect_ptParameterList, 0x4Cu, Level_eParameterTypeVarString, "Is Active", 7u, nullptr);
  RainEffect_ptSnowTexture = GameFunctions_RegisterGameTexture("snow.tex");
  RainEffect_ptRainTexture = GameFunctions_RegisterGameTexture("drop.tga");
}

// source: j/0/effects/raineffect.c:407  [size]
void __cdecl RainEffect_Close()
{
  int v0; // esi

  if ( RainEffect_ptParameterList )
  {
    v0 = *(_DWORD *)((unsigned int)&RainEffect_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
  QTask_DeleteQTaskType(RainEffect_eQTaskType);
}
