/* h/2/sound/sounddefgroupedit.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: h/2/sound/sounddefgroupedit.c:44  [size]
void __cdecl SoundDefGroupEdit_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ((void (__cdecl *)())QTask_aatQTaskFinalEvent[0][SoundDefGroup_eQTaskType].pfHandler)(ptQTask, pxContext);
}

// source: h/2/sound/sounddefgroupedit.c:63  [size]
void __cdecl SoundDefGroupEdit_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ;
}

// source: h/2/sound/sounddefgroupedit.c:80  [size]
void __cdecl SoundDefGroupEdit_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = SoundDefGroupEdit_ptParameterList;
}

// source: h/2/sound/sounddefgroupedit.c:96  [size]
void __cdecl SoundDefGroupEdit_GetCameraTargetInfoHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ;
}

// source: h/2/sound/sounddefgroupedit.c:118  [anchor-hash]
void __cdecl SoundDefGroupEdit_Open()
{
  unsigned __int16 v0; // si
  struct ParameterList_s *v1; // eax
  int v2; // edx

  v0 = QTask_NewQTaskType("SoundDefGroupEdit", 104, SoundDefGroup_eQTaskType, 512, 0);
  SoundDefGroupEdit_eQTaskType = v0;
  QTask_LinkQTaskEventHandlerFn(
    v0,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskDontSaveCreateableHandler);
  QTask_LinkQTaskEventHandlerFn(v0, 0, (void (__cdecl *)(struct QTask_s *, void *))SoundDefGroupEdit_CreateHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    ParameterList_eUpdateInternalDataQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))SoundDefGroupEdit_UpdateInternalDataHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))SoundDefGroupEdit_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    8,
    (void (__cdecl *)(struct QTask_s *, void *))SoundDefGroupEdit_GetCameraTargetInfoHandler);
  v1 = (struct ParameterList_s *)Mem_AllocFn(32, 4);
  v1->ptParameterListItem = (struct ParameterListItem_s *)&v1[1];
  v2 = Level_eParameterTypeString32;
  v1->nParameters = 0;
  v1->nMaxParameters = 1;
  SoundDefGroupEdit_ptParameterList = v1;
  ParameterList_AddParameter(v1, 0x29u, v2, "SoundDef", 7u, nullptr);
  SoundDefGroup_eCreateQTaskType = SoundDefGroupEdit_eQTaskType;
}

// source: h/2/sound/sounddefgroupedit.c:148  [size]
void __cdecl SoundDefGroupEdit_Close()
{
  int v0; // esi

  QTask_DeleteQTaskType(SoundDefGroupEdit_eQTaskType);
  if ( SoundDefGroupEdit_ptParameterList )
  {
    v0 = *(_DWORD *)((unsigned int)&SoundDefGroupEdit_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
}

// source: h/2/sound/sounddefgroupedit.c:165  [size]
unsigned __int16 __cdecl SoundDefGroupEdit_GetQTaskType()
{
  return SoundDefGroupEdit_eQTaskType;
}
