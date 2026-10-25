/* h/2/sound/sounddeftriggeronceedit.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: h/2/sound/sounddeftriggeronceedit.c:50  [size]
void __cdecl SoundDefTriggerOnceEdit_MicTriggerHandler(struct QTask_s *ptQTask, void *pxContext)
{
  bool v2; // al

  v2 = Level_isDynamicQTaskActive || !Level_isDynamicQTaskPaused;
  *((_BYTE *)pxContext + 4) = v2;
  if ( v2 && !BYTE2(ptQTask[6].tQTaskChildren.ptTail) )
    ((void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[Microphone_eTriggerEvent][SoundDefTriggerOnce_eQTaskType].pfHandler)(
      ptQTask,
      pxContext);
}

// source: h/2/sound/sounddeftriggeronceedit.c:83  [size]
void __cdecl SoundDefTriggerOnceEdit_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ((void (__cdecl *)())QTask_aatQTaskFinalEvent[0][SoundDefTriggerOnce_eQTaskType].pfHandler)(ptQTask, pxContext);
}

// source: h/2/sound/sounddeftriggeronceedit.c:114  [size]
void __cdecl SoundDefTriggerOnceEdit_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QHashTable_s *v2; // edi
  unsigned int v3; // eax

  SoundDefTriggerOnce_Move(ptQTask);
  v2 = Sound_ptSampleHashTable;
  v3 = Sound_ptSampleHashTable->tPrivate.pfHashFunction(
         Sound_ptSampleHashTable->tPrivate.nHashTableSize,
         (char *)&ptQTask[7].tQTaskChildren.ptHead + 3);
  ptQTask[1].tQTaskChildren.ptTail = (struct QTask_s *)((int  (__cdecl *)(struct QHashTable_s *, unsigned int, const void *))Sound_ptSampleHashTable->tPrivate.pfFindElement)(v2, v3, (const void *)((char *)&ptQTask[7].tQTaskChildren.ptHead + 3));
}

// source: h/2/sound/sounddeftriggeronceedit.c:142  [size]
void __cdecl SoundDefTriggerOnceEdit_GetParameterListHandler(
        struct QTask_s *ptQTask,
        void *pxContext)
{
  *(_DWORD *)pxContext = SoundDefTriggerOnceEdit_ptParameterList;
}

// source: h/2/sound/sounddeftriggeronceedit.c:158  [size]
void __cdecl SoundDefTriggerOnceEdit_GetCameraTargetInfoHandler(struct QTask_s *ptQTask, void *pxContext)
{
  qmemcpy(pxContext, &ptQTask[4].tQTaskChildren, 0x18u);
  *((_DWORD *)pxContext + 9) = 1065353216;
  *((_DWORD *)pxContext + 13) = 1065353216;
  *((_DWORD *)pxContext + 17) = 1065353216;
  *((_DWORD *)pxContext + 6) = 0;
  *((_DWORD *)pxContext + 7) = 0;
  *((_DWORD *)pxContext + 8) = 0;
  *((_DWORD *)pxContext + 10) = 0;
  *((_DWORD *)pxContext + 11) = 0;
  *((_DWORD *)pxContext + 12) = 0;
  *((_DWORD *)pxContext + 14) = 0;
  *((_DWORD *)pxContext + 15) = 0;
  *((_DWORD *)pxContext + 16) = 0;
  *((_DWORD *)pxContext + 18) = 0;
  *((_DWORD *)pxContext + 19) = *(_DWORD *)&ptQTask[5].eQTaskType;
}

// source: h/2/sound/sounddeftriggeronceedit.c:246  [anchor-hash]
void __cdecl SoundDefTriggerOnceEdit_Open()
{
  unsigned __int16 v0; // si
  struct ParameterList_s *v1; // eax
  int v2; // edx

  v0 = QTask_NewQTaskType("SoundDefTriggerOnceEdit", 336, SoundDefTriggerOnce_eQTaskType, 512, 0);
  SoundDefTriggerOnceEdit_eQTaskType = v0;
  QTask_LinkQTaskEventHandlerFn(
    v0,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskDontSaveCreateableHandler);
  QTask_LinkQTaskEventHandlerFn(v0, Microphone_eTriggerEvent, SoundDefTriggerOnceEdit_MicTriggerHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    0,
    (void (__cdecl *)(struct QTask_s *, void *))SoundDefTriggerOnceEdit_CreateHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    ParameterList_eUpdateInternalDataQTaskEvent,
    SoundDefTriggerOnceEdit_UpdateInternalDataHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))SoundDefTriggerOnceEdit_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(v0, 8, SoundDefTriggerOnceEdit_GetCameraTargetInfoHandler);
  v1 = (struct ParameterList_s *)Mem_AllocFn(332, 4);
  v2 = Level_eParameterTypeString32;
  v1->ptParameterListItem = (struct ParameterListItem_s *)&v1[1];
  v1->nParameters = 0;
  v1->nMaxParameters = 16;
  SoundDefTriggerOnceEdit_ptParameterList = v1;
  ParameterList_AddParameter(v1, 0x103u, v2, "SoundDef", 7u, nullptr);
  ParameterList_AddParameter(
    SoundDefTriggerOnceEdit_ptParameterList,
    0x123u,
    Level_eParameterTypeString32,
    "Sound",
    7u,
    nullptr);
  ParameterList_AddParameter(
    SoundDefTriggerOnceEdit_ptParameterList,
    0xC0u,
    Level_eParameterTypeObjectPos,
    "Position",
    7u,
    nullptr);
  ParameterList_AddParameter(
    SoundDefTriggerOnceEdit_ptParameterList,
    0xD8u,
    Level_eParameterTypeReal32,
    "Volume",
    7u,
    nullptr);
  ParameterList_AddParameterMinMax(
    SoundDefTriggerOnceEdit_ptParameterList,
    0xE4u,
    Level_eParameterTypeReal32,
    "Falloff Begin",
    7u,
    0.01,
    1000.0);
  ParameterList_AddParameterMinMax(
    SoundDefTriggerOnceEdit_ptParameterList,
    0xE8u,
    Level_eParameterTypeReal32,
    "Falloff End",
    7u,
    1.0,
    10000.0);
  ParameterList_AddParameter(
    SoundDefTriggerOnceEdit_ptParameterList,
    0x148u,
    Level_eParameterTypeReal32,
    "MinPlayLength",
    7u,
    nullptr);
  ParameterList_AddParameter(
    SoundDefTriggerOnceEdit_ptParameterList,
    0xF0u,
    Level_eParameterTypeInt32,
    "TriggerChannel",
    7u,
    nullptr);
  ParameterList_AddParameter(
    SoundDefTriggerOnceEdit_ptParameterList,
    0xF4u,
    Level_eParameterTypeInt32,
    "VolumeChannel",
    7u,
    nullptr);
  ParameterList_AddParameter(
    SoundDefTriggerOnceEdit_ptParameterList,
    0xF8u,
    Level_eParameterTypeInt32,
    "PitchChannel",
    7u,
    nullptr);
  ParameterList_AddParameter(
    SoundDefTriggerOnceEdit_ptParameterList,
    0xFCu,
    Level_eParameterTypeInt32,
    "SoundChannel",
    7u,
    nullptr);
  ParameterList_AddParameter(
    SoundDefTriggerOnceEdit_ptParameterList,
    0x100u,
    Level_eParameterTypebool8,
    "Looped",
    7u,
    nullptr);
  ParameterList_AddParameter(
    SoundDefTriggerOnceEdit_ptParameterList,
    0x101u,
    Level_eParameterTypebool8,
    "Reversed",
    7u,
    nullptr);
  SoundDefTriggerOnce_eCreateQTaskType = SoundDefTriggerOnceEdit_eQTaskType;
}

// source: h/2/sound/sounddeftriggeronceedit.c:300  [size]
void __cdecl SoundDefTriggerOnceEdit_Close()
{
  int v0; // esi

  QTask_DeleteQTaskType(SoundDefTriggerOnceEdit_eQTaskType);
  if ( SoundDefTriggerOnceEdit_ptParameterList )
  {
    v0 = *(_DWORD *)((unsigned int)&SoundDefTriggerOnceEdit_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
}

// source: h/2/sound/sounddeftriggeronceedit.c:317  [size]
unsigned __int16 __cdecl SoundDefTriggerOnceEdit_GetQTaskType()
{
  return SoundDefTriggerOnceEdit_eQTaskType;
}
