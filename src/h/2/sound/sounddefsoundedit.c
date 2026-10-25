/* h/2/sound/sounddefsoundedit.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: h/2/sound/sounddefsoundedit.c:50  [size]
void __cdecl SoundDefSoundEdit_MicTriggerHandler(struct QTask_s *ptQTask, void *pxContext)
{
  bool v2; // al

  v2 = Level_isDynamicQTaskActive || !Level_isDynamicQTaskPaused;
  *((_BYTE *)pxContext + 4) = v2;
  if ( v2 && !HIBYTE(ptQTask[6].eQTaskType) )
    ((void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[Microphone_eTriggerEvent][SoundDefSound_eQTaskType].pfHandler)(
      ptQTask,
      pxContext);
}

// source: h/2/sound/sounddefsoundedit.c:83  [size]
void __cdecl SoundDefSoundEdit_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ((void (__cdecl *)())QTask_aatQTaskFinalEvent[0][SoundDefSound_eQTaskType].pfHandler)(ptQTask, pxContext);
}

// source: h/2/sound/sounddefsoundedit.c:114  [size]
void __cdecl SoundDefSoundEdit_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QHashTable_s *v2; // esi
  unsigned int v3; // eax

  if ( *(float *)&ptQTask[6].tQTaskRefList.ptMiddle == 0.0 )
    *(float *)&ptQTask[6].tQTaskRefList.ptMiddle = *(float *)&ptQTask[6].tQTaskRefList.ptTail * 0.019999999552965164;
  SoundDefSound_Modify(ptQTask);
  v2 = Sound_ptSampleHashTable;
  v3 = Sound_ptSampleHashTable->tPrivate.pfHashFunction(
         Sound_ptSampleHashTable->tPrivate.nHashTableSize,
         (char *)&ptQTask[7].tQTaskRefList.ptTail + 2);
  ptQTask[1].tQTaskChildren.ptTail = (struct QTask_s *)((int  (__cdecl *)(struct QHashTable_s *, unsigned int, const void *))Sound_ptSampleHashTable->tPrivate.pfFindElement)(v2, v3, (const void *)((char *)&ptQTask[7].tQTaskRefList.ptTail + 2));
}

// source: h/2/sound/sounddefsoundedit.c:148  [size]
void __cdecl SoundDefSoundEdit_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = SoundDefSoundEdit_ptParameterList;
}

// source: h/2/sound/sounddefsoundedit.c:164  [size]
void __cdecl SoundDefSoundEdit_GetCameraTargetInfoHandler(struct QTask_s *ptQTask, void *pxContext)
{
  qmemcpy(pxContext, &ptQTask[4].ptParent, 0x18u);
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
  *((_DWORD *)pxContext + 19) = ptQTask[6].ptParent;
}

// source: h/2/sound/sounddefsoundedit.c:252  [anchor-callee]
void __cdecl SoundDefSoundEdit_Open()
{
  unsigned __int16 v0; // si
  struct ParameterList_s *v1; // eax
  int v2; // edx

  v0 = QTask_NewQTaskType("SoundDefSoundEdit", 384, SoundDefSound_eQTaskType, 512, 0);
  SoundDefSoundEdit_eQTaskType = v0;
  QTask_LinkQTaskEventHandlerFn(
    v0,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskDontSaveCreateableHandler);
  QTask_LinkQTaskEventHandlerFn(v0, Microphone_eTriggerEvent, SoundDefSoundEdit_MicTriggerHandler);
  QTask_LinkQTaskEventHandlerFn(v0, 0, (void (__cdecl *)(struct QTask_s *, void *))SoundDefSoundEdit_CreateHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    ParameterList_eUpdateInternalDataQTaskEvent,
    SoundDefSoundEdit_UpdateInternalDataHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))SoundDefSoundEdit_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(v0, 8, SoundDefSoundEdit_GetCameraTargetInfoHandler);
  v1 = (struct ParameterList_s *)Mem_AllocFn(292, 4);
  v2 = Level_eParameterTypeString32;
  v1->ptParameterListItem = (struct ParameterListItem_s *)&v1[1];
  v1->nParameters = 0;
  v1->nMaxParameters = 14;
  SoundDefSoundEdit_ptParameterList = v1;
  ParameterList_AddParameter(v1, 0x116u, v2, "SoundDef", 7u, nullptr);
  ParameterList_AddParameter(
    SoundDefSoundEdit_ptParameterList,
    0x136u,
    Level_eParameterTypeString32,
    "Sound",
    7u,
    nullptr);
  ParameterList_AddParameter(
    SoundDefSoundEdit_ptParameterList,
    0xD8u,
    Level_eParameterTypeObjectPos,
    "Position",
    7u,
    nullptr);
  ParameterList_AddParameter(
    SoundDefSoundEdit_ptParameterList,
    0xFCu,
    Level_eParameterTypeReal32,
    "Volume",
    7u,
    nullptr);
  ParameterList_AddParameterMinMax(
    SoundDefSoundEdit_ptParameterList,
    0x108u,
    Level_eParameterTypeReal32,
    "Falloff Begin",
    7u,
    0.01,
    1000.0);
  ParameterList_AddParameterMinMax(
    SoundDefSoundEdit_ptParameterList,
    0x10Cu,
    Level_eParameterTypeReal32,
    "Falloff End",
    7u,
    1.0,
    10000.0);
  ParameterList_AddParameter(
    SoundDefSoundEdit_ptParameterList,
    0xF0u,
    Level_eParameterTypeInt32,
    "VolumeChannel",
    7u,
    nullptr);
  ParameterList_AddParameter(
    SoundDefSoundEdit_ptParameterList,
    0xF4u,
    Level_eParameterTypeInt32,
    "PitchChannel",
    7u,
    nullptr);
  ParameterList_AddParameter(
    SoundDefSoundEdit_ptParameterList,
    0xF8u,
    Level_eParameterTypeInt32,
    "SoundChannel",
    7u,
    nullptr);
  ParameterList_AddParameter(
    SoundDefSoundEdit_ptParameterList,
    0x15Cu,
    Level_eParameterTypeReal32,
    "MinPlayLength",
    7u,
    nullptr);
  ParameterList_AddParameter(
    SoundDefSoundEdit_ptParameterList,
    0x114u,
    Level_eParameterTypebool8,
    "Looped",
    7u,
    nullptr);
  SoundDefSound_eCreateQTaskType = SoundDefSoundEdit_eQTaskType;
}

// source: h/2/sound/sounddefsoundedit.c:304  [size]
void __cdecl SoundDefSoundEdit_Close()
{
  int v0; // esi

  QTask_DeleteQTaskType(SoundDefSoundEdit_eQTaskType);
  if ( SoundDefSoundEdit_ptParameterList )
  {
    v0 = *(_DWORD *)((unsigned int)&SoundDefSoundEdit_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
}

// source: h/2/sound/sounddefsoundedit.c:321  [size]
unsigned __int16 __cdecl SoundDefSoundEdit_GetQTaskType()
{
  return SoundDefSoundEdit_eQTaskType;
}
