/* h/2/sound/soundsysedit.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: h/2/sound/soundsysedit.c:63  [size]
void __cdecl SoundSysEdit_DefCreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ((void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[0][SoundSys_eSystemSoundDefQTaskType].pfHandler)(
    ptQTask,
    pxContext);
  LOBYTE(ptQTask[7].tQTaskRefList.ptHead) = 0;
}

// source: h/2/sound/soundsysedit.c:83  [anchor-mhash]
void __cdecl SoundSysEdit_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  char *v2; // edi
  struct QTask_s *ptHead; // esi
  __int16 v4; // ax
  struct QTask_s *v5; // ecx
  int v6; // edx
  void (__cdecl *pfHandler)(struct QTask_s *, struct SoundSysSaveContext_t *); // ecx
  struct File_s *v8; // esi
  int v9; // esi
  struct SoundSysSaveContext_t tSaveContext; // [esp+4h] [ebp-8h] BYREF

  if ( LOBYTE(ptQTask[7].tQTaskRefList.ptHead) )
  {
    v2 = (char *)Mem_AllocFn(0x80000, 4);
    *v2 = 0;
    ptHead = ptQTask->tQTaskChildren.ptHead;
    tSaveContext.zFile = v2;
    tSaveContext.nIndent = 0;
    if ( ptHead->ptNext && ptHead )
    {
      v4 = SoundSys_eSaveQTaskEvent;
      do
      {
        if ( ptHead->ptNext )
          v5 = ptHead->ptNext->ptNext != nullptr ? ptHead->ptNext : nullptr;
        else
          v5 = nullptr;
        v6 = QTask_nProtectedQTaskStackOffset;
        QTask_atProtectedQTaskStack[QTask_nProtectedQTaskStackOffset].ptQTask = v5;
        QTask_nProtectedQTaskStackOffset = v6 + 1;
        if ( v4 == 512 )
        {
          v4 = QTask_NewQTaskEventFn(0, &g_zFileName.zMenuResourcePath[16]);
          SoundSys_eSaveQTaskEvent = v4;
        }
        pfHandler = (void (__cdecl *)(struct QTask_s *, struct SoundSysSaveContext_t *))QTask_aatQTaskFinalEvent[v4][ptHead->eQTaskType].pfHandler;
        if ( pfHandler )
        {
          pfHandler(ptHead, &tSaveContext);
          v4 = SoundSys_eSaveQTaskEvent;
        }
        ptHead = (struct QTask_s *)dword_849C7DC[QTask_nProtectedQTaskStackOffset--];
      }
      while ( ptHead );
    }
    v8 = File_New((char *)&ptQTask[1], "w");
    if ( v8 )
    {
      File_atDevice[v8->eDeviceID].pfWrite(v8->eDeviceID, v8, v2, strlen(v2));
      if ( v8 == &File_tDummyAsyncFile )
        File_tDummyAsyncFile.isAsync = false;
      else
        File_atDevice[v8->eDeviceID].pfDelete(v8->eDeviceID, v8);
    }
    v9 = *(_DWORD *)((unsigned int)(v2 - 4) & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v9);
    memset(*(void **)(v9 + 8), 0xCDu, *(_DWORD *)(v9 + 16));
    free((void *)v9);
  }
}

// source: h/2/sound/soundsysedit.c:160  [size]
void __cdecl SoundSysEdit_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = SoundSysEdit_ptParameterList;
}

// source: h/2/sound/soundsysedit.c:216  [anchor-hash]
int __cdecl SoundSysEdit_IsSoundDefEditorInfoPlaySound(
        struct SoundDefEditorInfo_s *ptSoundDefEditorInfo,
        struct QTask_s *ptQTask,
        struct SoundSysRequest_s *ptSoundSysRequest)
{
  ptSoundDefEditorInfo->isPlay = 0;
  ptSoundDefEditorInfo->isPlaying = 0;
  ptSoundDefEditorInfo->isStop = 0;
  ptSoundDefEditorInfo->vDistanceToMicrophone = 0.0;
  return 1;
}

// source: h/2/sound/soundsysedit.c:257  [size]
int __cdecl SoundSysEdit_GetNumberOfParametersInSoundDefEditorInfo()
{
  return 3;
}

// source: h/2/sound/soundsysedit.c:270  [anchor-strings]
unsigned int __cdecl SoundSysEdit_AddSoundDefEditorInfoParameters(
        struct ParameterList_s *ptParameterList,
        unsigned int nSoundDefEditorInfoOffset)
{
  ParameterList_AddParameter(
    ptParameterList,
    nSoundDefEditorInfoOffset + 4,
    SoundSysEdit_eParameterTypeMeter,
    "Distance to microphone",
    6u,
    nullptr);
  ParameterList_AddParameter(
    ptParameterList,
    nSoundDefEditorInfoOffset,
    Level_eParameterTypePushButton,
    "Play",
    6u,
    nullptr);
  return (unsigned int)ParameterList_AddParameter(
                         ptParameterList,
                         nSoundDefEditorInfoOffset + 1,
                         Level_eParameterTypePushButton,
                         "Stop",
                         6u,
                         nullptr);
}

// source: h/2/sound/soundsysedit.c:287  [size]
struct SoundDefEditorInfo_s *__cdecl SoundSysEdit_InitSoundDefEditorInfo(
        struct SoundDefEditorInfo_s *ptSoundDefEditorInfo)
{
  *(_DWORD *)&ptSoundDefEditorInfo->isPlay = 0;
  ptSoundDefEditorInfo->vDistanceToMicrophone = 0.0;
  return ptSoundDefEditorInfo;
}

// source: h/2/sound/soundsysedit.c:302  [anchor-hash]
void __cdecl SoundSysEdit_Open()
{
  int v0; // eax
  unsigned __int16 v1; // si
  struct ParameterList_s *v2; // eax
  int v3; // edx

  SoundSysEdit_eParameterTypeMeter = ParameterList_NewParameterType("Meter", Level_eParameterTypeReal32);
  SoundSysEdit_eQTaskType = QTask_NewQTaskType("SoundSysEdit", 304, SoundSys_eSystemSoundDefQTaskType, 0, 0);
  v0 = QTask_NewQTaskEventNoContextFn(0, "SoundSysEdit-PlaySound");
  v1 = SoundSysEdit_eQTaskType;
  SoundSysEdit_ePlaySoundQTaskEvent = v0;
  QTask_LinkQTaskEventHandlerFn(
    SoundSysEdit_eQTaskType,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskDontSaveHandler);
  QTask_LinkQTaskEventHandlerFn(v1, 0, SoundSysEdit_DefCreateHandler);
  QTask_LinkQTaskEventHandlerFn(v1, ParameterList_eUpdateInternalDataQTaskEvent, SoundSysEdit_UpdateInternalDataHandler);
  QTask_LinkQTaskEventHandlerFn(
    v1,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))SoundSysEdit_GetParameterListHandler);
  v2 = (struct ParameterList_s *)Mem_AllocFn(32, 4);
  v3 = Level_eParameterTypePushButton;
  v2->ptParameterListItem = (struct ParameterListItem_s *)&v2[1];
  v2->nParameters = 0;
  v2->nMaxParameters = 1;
  SoundSysEdit_ptParameterList = v2;
  ParameterList_AddParameter(v2, 0x12Cu, v3, "Save SoundDef", 7u, nullptr);
  SoundSys_eSystemSoundDefCreateQTaskType = SoundSysEdit_eQTaskType;
}

// source: h/2/sound/soundsysedit.c:338  [anchor-mhash]
void __cdecl SoundSysEdit_Close()
{
  int v0; // esi

  QTask_DeleteQTaskType(SoundSysEdit_eQTaskType);
  QTask_DeleteQTaskEventNoContext(SoundSysEdit_ePlaySoundQTaskEvent);
  if ( SoundSysEdit_ptParameterList )
  {
    v0 = *(_DWORD *)((unsigned int)&SoundSysEdit_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
  ParameterList_atParameterType[SoundSysEdit_eParameterTypeMeter].isUsed = false;
}

// source: h/2/sound/soundsysedit.c:361  [size]
unsigned __int16 __cdecl SoundSysEdit_GetQTaskType()
{
  return SoundSysEdit_eQTaskType;
}

// source: h/2/sound/soundsysedit.c:376  [size]
int __cdecl SoundSysEdit_GetPlaySoundQTaskEvent()
{
  return SoundSysEdit_ePlaySoundQTaskEvent;
}
