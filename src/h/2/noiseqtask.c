/* h/2/noiseqtask.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: h/2/noiseqtask.c:102  [anchor-mhash]
void __cdecl NoiseQTask_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ptQTask[5].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[5].tQTaskRefList.ptTail = nullptr;
  ptQTask[5].ptParent = nullptr;
  ptQTask[7].tQTaskRefList.ptHead = nullptr;
  ptQTask[1].tQTaskRefList.ptMiddle = (struct QReference_s *)1065353216;
  ptQTask[2].ptNext = (struct QTask_s *)1065353216;
  ptQTask[2].tQTaskChildren.ptTail = (struct QTask_s *)1065353216;
  ptQTask[1].ptNext = nullptr;
  ptQTask[1].ptPrev = nullptr;
  ptQTask[1].tQTaskChildren.ptHead = nullptr;
  ptQTask[1].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[1].tQTaskChildren.ptTail = nullptr;
  ptQTask[1].tQTaskRefList.ptHead = nullptr;
  ptQTask[1].tQTaskRefList.ptTail = nullptr;
  ptQTask[1].ptParent = nullptr;
  *(_DWORD *)&ptQTask[1].eQTaskType = 0;
  ptQTask[2].ptPrev = nullptr;
  ptQTask[2].tQTaskChildren.ptHead = nullptr;
  ptQTask[2].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[2].tQTaskRefList.ptHead = nullptr;
  LOBYTE(ptQTask[7].tQTaskRefList.ptMiddle) = 0;
  *(_DWORD *)&ptQTask[4].eQTaskType = 0;
  ptQTask[4].ptParent = nullptr;
  ptQTask[2].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[2].tQTaskRefList.ptTail = nullptr;
  ptQTask[3].ptNext = nullptr;
  ptQTask[3].ptPrev = nullptr;
  ptQTask[2].ptParent = nullptr;
  *(_DWORD *)&ptQTask[2].eQTaskType = 0;
  ptQTask[3].tQTaskChildren.ptHead = nullptr;
  ptQTask[3].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[4].tQTaskChildren.ptHead = nullptr;
  ptQTask[4].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[4].ptNext = nullptr;
  ptQTask[4].ptPrev = nullptr;
  ptQTask[3].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[3].tQTaskRefList.ptTail = nullptr;
  ptQTask[3].ptParent = nullptr;
  *(_DWORD *)&ptQTask[3].eQTaskType = 0;
  ptQTask[4].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[4].tQTaskRefList.ptTail = nullptr;
  ptQTask[4].tQTaskChildren.ptTail = nullptr;
  ptQTask[4].tQTaskRefList.ptHead = nullptr;
  ptQTask[3].tQTaskChildren.ptTail = nullptr;
  ptQTask[5].ptNext = nullptr;
  ptQTask[5].ptPrev = nullptr;
  ptQTask[5].tQTaskChildren.ptHead = nullptr;
  ptQTask[5].tQTaskChildren.ptMiddle = (struct QTask_s *)1072693248;
  ptQTask[5].tQTaskChildren.ptTail = nullptr;
  ptQTask[5].tQTaskRefList.ptHead = (struct QReference_s *)1072693248;
}

// source: h/2/noiseqtask.c:168  [size]
void __cdecl NoiseQTask_RegisterScriptSymbolsHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { char zName[64]; };
    struct { char igi2_o1[64]; char zTemp[128]; };
    char igi2_extent[192];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)

  if ( !LOBYTE(ptQTask[7].tQTaskRefList.ptMiddle) )
  {
    LOBYTE(ptQTask[7].tQTaskRefList.ptMiddle) = 1;
    Level_GetUniqueQTaskNameFromTask(igi2_frame.zName, ptQTask);
    sprintf(igi2_frame.zTemp, "%s.vValue", igi2_frame.zName);
    Symbol_Register(
      igi2_frame.zTemp,
      Script_Float,
      &ptQTask[2].ptParent,
      8,
      QSCRIPT_SYMBOLCLASS_VARIABLE,
      QSCRIPT_SYMBOLTYPE_FLOAT,
      QSCRIPT_SYMBOLLIFESPAN_FINITE);
  }
}

// source: h/2/noiseqtask.c:198  [size]
void __cdecl NoiseQTask_RemoveScriptSymbolsHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { char zName[64]; };
    struct { char igi2_o1[64]; char zTemp[128]; };
    char igi2_extent[192];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)

  Level_GetUniqueQTaskNameFromTask(igi2_frame.zName, ptQTask);
  LOBYTE(ptQTask[7].tQTaskRefList.ptMiddle) = 0;
  sprintf(igi2_frame.zTemp, "%s.vValue", igi2_frame.zName);
  Symbol_Remove(igi2_frame.zTemp);
  LOBYTE(ptQTask[7].tQTaskRefList.ptMiddle) = 0;
}

// source: h/2/noiseqtask.c:228  [size]
void __cdecl NoiseQTask_DeleteHandler(struct QTask_s *ptQTask)
{
  int v1; // ecx
  struct QReference_s *v2; // eax
  void (__cdecl *pfHandler)(struct QTask_s *); // eax

  v1 = 0;
  while ( 1 )
  {
    v2 = Level_atLevelQTaskID[v1];
    if ( v2 )
    {
      if ( v2->pxObject == ptQTask )
        break;
    }
    if ( ++v1 >= 4096 )
      goto LABEL_9;
  }
  if ( v1 >= 0 )
  {
    pfHandler = (void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[Level_eRemoveLevelScriptSymbolsEvent][ptQTask->eQTaskType].pfHandler;
    if ( pfHandler )
      pfHandler(ptQTask);
  }
LABEL_9:
  Level_DeinitLevelExpression((struct LevelExpression_s *)&ptQTask[5].tQTaskRefList.ptMiddle);
}

// source: h/2/noiseqtask.c:261  [size]
void __cdecl NoiseQTask_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = NoiseQTask_ptParameterList;
}

// source: h/2/noiseqtask.c:277  [anchor-mhash]
void __cdecl NoiseQTask_RunHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptHead; // ecx
  int v2; // edx
  struct QTask_s *v3; // eax
  void (__cdecl *pfHandler)(struct QTask_s *); // eax
  int v5; // edx
  struct QReference_s *ptTail; // eax
  double v7; // st7
  struct QTask_s *v8; // edx
  double v9; // st7
  struct QTask_s *v10; // ecx
  struct QTask_s *v11; // eax
  struct QTask_s *ptParent; // eax
  double v13; // st7
  int v14; // ecx
  unsigned int v15; // edi
  struct QTask_s *v16; // edx
  double v17; // st7
  bool v18; // zf
  struct QTask_s *ptPrev; // eax
  struct QTask_s *ptMiddle; // edx

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
  if ( ptQTask[5].tQTaskRefList.ptMiddle && ptQTask[5].tQTaskRefList.ptTail->ptNext && ptQTask[5].ptParent )
  {
    *(double *)&ptQTask[2].tQTaskRefList.ptMiddle = Level_RunLevelExpression(
                                                      (struct LevelExpression_s *)&ptQTask[5].tQTaskRefList.ptMiddle,
                                                      ptQTask);
  }
  else
  {
    ptTail = ptQTask[3].tQTaskRefList.ptTail;
    ptQTask[2].tQTaskRefList.ptMiddle = ptQTask[3].tQTaskRefList.ptMiddle;
    ptQTask[2].tQTaskRefList.ptTail = ptTail;
  }
  if ( *(double *)&ptQTask[3].ptNext >= *(double *)&ptQTask[2].tQTaskRefList.ptMiddle )
  {
    if ( *(double *)&ptQTask[3].ptNext > *(double *)&ptQTask[2].tQTaskRefList.ptMiddle )
    {
      v9 = *(double *)&ptQTask[3].ptNext - *(double *)&ptQTask[4].tQTaskChildren.ptHead;
      *(double *)&ptQTask[3].ptNext = v9;
      if ( v9 < *(double *)&ptQTask[2].tQTaskRefList.ptMiddle )
      {
        v10 = (struct QTask_s *)ptQTask[2].tQTaskRefList.ptTail;
        ptQTask[3].ptNext = (struct QTask_s *)ptQTask[2].tQTaskRefList.ptMiddle;
        ptQTask[3].ptPrev = v10;
      }
    }
  }
  else
  {
    v7 = *(double *)&ptQTask[4].ptNext + *(double *)&ptQTask[3].ptNext;
    *(double *)&ptQTask[3].ptNext = v7;
    if ( v7 > *(double *)&ptQTask[2].tQTaskRefList.ptMiddle )
    {
      v8 = (struct QTask_s *)ptQTask[2].tQTaskRefList.ptTail;
      ptQTask[3].ptNext = (struct QTask_s *)ptQTask[2].tQTaskRefList.ptMiddle;
      ptQTask[3].ptPrev = v8;
    }
  }
  v11 = ptQTask[3].tQTaskChildren.ptTail;
  if ( (int)v11 > 0 )
  {
    ptQTask[3].tQTaskChildren.ptTail = (struct QTask_s *)((char *)v11 - 1);
  }
  else
  {
    ptParent = ptQTask[4].ptParent;
    v13 = *(double *)&ptQTask[4].tQTaskRefList.ptMiddle - *(double *)&ptQTask[4].tQTaskChildren.ptTail;
    v14 = *(_DWORD *)&ptQTask[4].eQTaskType - (_DWORD)ptParent;
    ptQTask[3].tQTaskChildren.ptTail = ptParent;
    if ( v14 )
    {
      v15 = (NoiseQTask_tRandomState.anRandom[0] >> 7)
          ^ NoiseQTask_tRandomState.anRandom[2]
          ^ NoiseQTask_tRandomState.anRandom[1];
      NoiseQTask_tRandomState.anRandom[2] ^= NoiseQTask_tRandomState.anRandom[0] >> 7;
      NoiseQTask_tRandomState.anRandom[0] += v15;
      NoiseQTask_tRandomState.anRandom[1] = v15;
      ptQTask[3].tQTaskChildren.ptTail = (struct QTask_s *)((char *)ptQTask[3].tQTaskChildren.ptTail
                                                          + NoiseQTask_tRandomState.anRandom[0] % (v14 + 1));
    }
    v16 = ptQTask[4].tQTaskChildren.ptTail;
    ptQTask[3].tQTaskChildren.ptMiddle = (struct QTask_s *)ptQTask[4].tQTaskRefList.ptHead;
    ptQTask[3].tQTaskChildren.ptHead = v16;
    if ( v13 > 0.0 )
      *(double *)&ptQTask[3].tQTaskChildren.ptHead = Random_GetRandomNumberReal32(&NoiseQTask_tRandomState) * v13
                                                   + *(double *)&ptQTask[3].tQTaskChildren.ptHead;
  }
  v17 = *(double *)&ptQTask[3].ptNext;
  v18 = ScreenGrab_isRecord[0] == 0;
  *(double *)&ptQTask[2].ptParent = v17;
  if ( !v18 || ScreenGrab_isGrabSingle[0] )
    *(double *)&ptQTask[2].ptParent = v17 + *(double *)&ptQTask[3].tQTaskChildren.ptHead;
  if ( *(double *)&ptQTask[5].tQTaskChildren.ptTail != 0.0 )
    *(double *)&ptQTask[2].ptParent = (double)(int)(__int64)(*(double *)&ptQTask[2].ptParent
                                                           / *(double *)&ptQTask[5].tQTaskChildren.ptTail)
                                    * *(double *)&ptQTask[5].tQTaskChildren.ptTail;
  if ( *(double *)&ptQTask[2].ptParent >= *(double *)&ptQTask[5].ptNext )
  {
    if ( *(double *)&ptQTask[2].ptParent > *(double *)&ptQTask[5].tQTaskChildren.ptHead )
    {
      ptMiddle = ptQTask[5].tQTaskChildren.ptMiddle;
      ptQTask[2].ptParent = ptQTask[5].tQTaskChildren.ptHead;
      *(_DWORD *)&ptQTask[2].eQTaskType = ptMiddle;
    }
  }
  else
  {
    ptPrev = ptQTask[5].ptPrev;
    ptQTask[2].ptParent = ptQTask[5].ptNext;
    *(_DWORD *)&ptQTask[2].eQTaskType = ptPrev;
  }
}

// source: h/2/noiseqtask.c:376  [anchor-mhash]
void __cdecl NoiseQTask_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *ptHead; // eax
  int v3; // edx
  struct QTask_s *v4; // ecx
  void (__cdecl *pfHandler)(struct QTask_s *, _DWORD); // ecx
  int v6; // edx
  struct QReference_s *v7; // ecx
  struct QTask_s *v8; // eax

  if ( !pxContext || !*(_DWORD *)pxContext )
  {
    ptHead = ptQTask->tQTaskChildren.ptHead;
    if ( ptHead->ptNext )
    {
      if ( ptHead )
      {
        v3 = QTask_nProtectedQTaskStackOffset;
        do
        {
          if ( ptHead->ptNext )
            v4 = ptHead->ptNext->ptNext != nullptr ? ptHead->ptNext : nullptr;
          else
            v4 = nullptr;
          QTask_atProtectedQTaskStack[v3].ptQTask = v4;
          pfHandler = (void (__cdecl *)(struct QTask_s *, _DWORD))QTask_aatQTaskFinalEvent[ParameterList_eUpdateInternalDataQTaskEvent][ptHead->eQTaskType].pfHandler;
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
    }
  }
  Level_CompileLevelExpression((struct LevelExpression_s *)&ptQTask[5].tQTaskRefList.ptMiddle, ptQTask);
  if ( *(double *)&ptQTask[4].tQTaskRefList.ptMiddle < *(double *)&ptQTask[4].tQTaskChildren.ptTail )
  {
    v7 = ptQTask[4].tQTaskRefList.ptHead;
    ptQTask[4].tQTaskRefList.ptMiddle = (struct QReference_s *)ptQTask[4].tQTaskChildren.ptTail;
    ptQTask[4].tQTaskRefList.ptTail = v7;
  }
  v8 = *(struct QTask_s **)&ptQTask[3].eQTaskType;
  ptQTask[3].ptNext = ptQTask[3].ptParent;
  ptQTask[3].ptPrev = v8;
}

// source: h/2/noiseqtask.c:437  [anchor-hash]
void __cdecl NoiseQTask_Open()
{
  unsigned __int16 v0; // si
  struct ParameterList_s *v1; // eax
  int v2; // edx

  v0 = QTask_NewQTaskType("NoiseQTask", 312, EditorRigidObj_eQTaskType, 0, 0);
  NoiseQTask_eQTaskType = v0;
  QTask_LinkQTaskEventHandlerFn(
    v0,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveHandler);
  QTask_LinkQTaskEventHandlerFn(v0, 0, NoiseQTask_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 1, NoiseQTask_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 2, NoiseQTask_DeleteHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))NoiseQTask_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(v0, ParameterList_eUpdateInternalDataQTaskEvent, NoiseQTask_UpdateInternalDataHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(
    v0,
    Level_eRegisterLevelScriptSymbolsEvent,
    NoiseQTask_RegisterScriptSymbolsHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(
    v0,
    Level_eRemoveLevelScriptSymbolsEvent,
    NoiseQTask_RemoveScriptSymbolsHandler);
  v1 = (struct ParameterList_s *)Mem_AllocFn(412, 4);
  v2 = Level_eParameterTypeObjectPos;
  v1->ptParameterListItem = (struct ParameterListItem_s *)&v1[1];
  v1->nParameters = 0;
  v1->nMaxParameters = 20;
  NoiseQTask_ptParameterList = v1;
  ParameterList_AddParameter(v1, 0x28u, v2, "Position", 7u, nullptr);
  ParameterList_AddParameter(
    NoiseQTask_ptParameterList,
    0x40u,
    Level_eParameterTypeReal32x9,
    "Orientation",
    7u,
    nullptr);
  ParameterList_AddParameter(NoiseQTask_ptParameterList, 0xE0u, Level_eParameterTypeVarString, "Value", 7u, nullptr);
  ParameterList_AddParameter(
    NoiseQTask_ptParameterList,
    0x90u,
    Level_eParameterTypeReal64,
    "Initial ideal value",
    7u,
    nullptr);
  ParameterList_AddParameter(
    NoiseQTask_ptParameterList,
    0x98u,
    Level_eParameterTypeReal64,
    "Initial real value",
    7u,
    nullptr);
  ParameterList_AddParameter(
    NoiseQTask_ptParameterList,
    0xA0u,
    Level_eParameterTypeReal64,
    "Increment value",
    7u,
    nullptr);
  ParameterList_AddParameter(
    NoiseQTask_ptParameterList,
    0xA8u,
    Level_eParameterTypeReal64,
    "Decrement value",
    7u,
    nullptr);
  ParameterList_AddParameter(
    NoiseQTask_ptParameterList,
    0xB0u,
    Level_eParameterTypeReal64,
    "Minimum random value",
    7u,
    nullptr);
  ParameterList_AddParameter(
    NoiseQTask_ptParameterList,
    0xB8u,
    Level_eParameterTypeReal64,
    "Maximum random value",
    7u,
    nullptr);
  ParameterList_AddParameter(
    NoiseQTask_ptParameterList,
    0xC0u,
    Level_eParameterTypeInt32,
    "Minimum time between random switches",
    7u,
    nullptr);
  ParameterList_AddParameter(
    NoiseQTask_ptParameterList,
    0xC4u,
    Level_eParameterTypeInt32,
    "Maximum time between random switches",
    7u,
    nullptr);
  ParameterList_AddParameter(
    NoiseQTask_ptParameterList,
    0xC8u,
    Level_eParameterTypeReal64,
    "Minimum final value",
    7u,
    nullptr);
  ParameterList_AddParameter(
    NoiseQTask_ptParameterList,
    0xD0u,
    Level_eParameterTypeReal64,
    "Maximum final value",
    7u,
    nullptr);
  ParameterList_AddParameter(NoiseQTask_ptParameterList, 0xD8u, Level_eParameterTypeReal64, "Step value", 7u, nullptr);
  Symbol_Register(
    "TASKTYPE_NOISEQTASK",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)NoiseQTask_eQTaskType,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  NoiseQTask_tRandomState.anRandom[0] = -923067897;
  NoiseQTask_tRandomState.anRandom[1] = 971667286;
  NoiseQTask_tRandomState.anRandom[2] = 2146516173;
}

// source: h/2/noiseqtask.c:490  [size]
void __cdecl NoiseQTask_Close()
{
  int v0; // esi

  if ( NoiseQTask_ptParameterList )
  {
    v0 = *(_DWORD *)((unsigned int)&NoiseQTask_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
  QTask_DeleteQTaskType(NoiseQTask_eQTaskType);
}

// source: h/2/noiseqtask.c:507  [size]
unsigned __int16 __cdecl NoiseQTask_GetQTaskType()
{
  return NoiseQTask_eQTaskType;
}
