/* h/2/magicobjconfigcontainer.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: h/2/magicobjconfigcontainer.c:108  [size]
void __cdecl MagicObjConfigContainer_PrepareDeleteHandler(struct QTask_s *ptQTask)
{
  ;
}

// source: h/2/magicobjconfigcontainer.c:127  [anchor-mhash]
void __cdecl MagicObjConfigContainer_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *v2; // ebp
  bool v3; // cc
  struct MagicObjType_s *v4; // edx
  struct QTask_s *v5; // ebx
  char ptNext; // al

  v2 = (struct QTask_s *)MagicObj_nMagicObjType;
  v3 = MagicObj_nMagicObjType <= 0;
  ptQTask[1].tQTaskChildren.ptHead = nullptr;
  if ( !v3 )
  {
    v4 = MagicObj_atMagicObjType;
    v5 = v2;
    do
    {
      if ( strlen(v4->zName) )
        ++*(int *)&ptQTask[1].tQTaskChildren.ptHead;
      ++v4;
      v5 = (struct QTask_s *)((char *)v5 - 1);
    }
    while ( v5 );
  }
  ptNext = (char)ptQTask[1].ptNext;
  ptQTask[1].tQTaskChildren.ptMiddle = v2;
  if ( ptNext )
  {
    if ( strlen((char *)&ptQTask[1].tQTaskChildren.ptTail) )
      Level_SaveQTask((char *)&ptQTask[1].tQTaskChildren.ptTail, ptQTask, true, false);
  }
}

// source: h/2/magicobjconfigcontainer.c:159  [size]
void __cdecl MagicObjConfigContainer_GetParameterListHandler(
        struct QTask_s *ptQTask,
        void *pxContext)
{
  *(_DWORD *)pxContext = MagicObjConfigContainer_ptParameterList;
}

// source: h/2/magicobjconfigcontainer.c:179  [anchor-caller]
struct QTask_s *__cdecl MagicObjConfigContainer_Load(
        struct QTask_s *ptParent,
        char *zFilename)
{
  struct QTask_s *QTask; // esi

  MagicObjConfigContainer_zFilename = zFilename;
  QTask = Level_LoadQTask(ptParent, zFilename, false);
  if ( !QTask )
    QTask = QTask_NewFn(ptParent, MagicObjConfigContainer_eQTaskType, nullptr);
  Level_ClearQTaskIDRecursive(QTask);
  MagicObjConfigContainer_zFilename = nullptr;
  return QTask;
}

// source: h/2/magicobjconfigcontainer.c:205  [size]
struct QTask_s *__cdecl MagicObjConfigContainer_Save(struct QTask_s *ptQTask, char *zFilename)
{
  return (struct QTask_s *)Level_SaveQTask(zFilename, ptQTask, true, false);
}

// source: h/2/magicobjconfigcontainer.c:221  [size]
unsigned __int16 __cdecl MagicObjConfigContainer_GetQTaskType()
{
  return MagicObjConfigContainer_eQTaskType;
}

// source: h/2/magicobjconfigcontainer.c:234  [anchor-hash]
void __cdecl MagicObjConfigContainer_Open()
{
  unsigned __int16 BaseQTaskType; // ax
  unsigned __int16 v1; // si
  struct ParameterList_s *v2; // eax
  int v3; // edx

  BaseQTaskType = QTask_GetBaseQTaskType();
  v1 = QTask_NewQTaskType("MagicObjConfigContainer", 316, BaseQTaskType, 0, 0);
  MagicObjConfigContainer_eQTaskType = v1;
  QTask_LinkQTaskEventHandlerFn(v1, 0, (void (__cdecl *)(struct QTask_s *, void *))pfQTaskEvent__);
  QTask_LinkQTaskEventHandlerNoContextFn(
    v1,
    2,
    (void (__cdecl *)(struct QTask_s *))MagicObjConfigContainer_PrepareDeleteHandler);
  QTask_LinkQTaskEventHandlerFn(
    v1,
    ParameterList_eUpdateInternalDataQTaskEvent,
    MagicObjConfigContainer_UpdateInternalDataHandler);
  QTask_LinkQTaskEventHandlerFn(
    v1,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))MagicObjConfigContainer_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(
    v1,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveHandler);
  v2 = (struct ParameterList_s *)Mem_AllocFn(92, 4);
  v3 = Level_eParameterTypePushButton;
  v2->ptParameterListItem = (struct ParameterListItem_s *)&v2[1];
  v2->nParameters = 0;
  v2->nMaxParameters = 4;
  MagicObjConfigContainer_ptParameterList = v2;
  ParameterList_AddParameter(v2, 0x28u, v3, "Save", 6u, nullptr);
  ParameterList_AddParameter(
    MagicObjConfigContainer_ptParameterList,
    0x30u,
    Level_eParameterTypeInt32,
    "Current used magic object types.",
    2u,
    nullptr);
  ParameterList_AddParameter(
    MagicObjConfigContainer_ptParameterList,
    0x34u,
    Level_eParameterTypeInt32,
    "Current max magic object types.",
    2u,
    nullptr);
  ParameterList_AddParameter(
    MagicObjConfigContainer_ptParameterList,
    0x2Cu,
    Level_eParameterTypeInt32,
    "Max allowed magic object types.",
    2u,
    nullptr);
}

// source: h/2/magicobjconfigcontainer.c:266  [size]
void __cdecl MagicObjConfigContainer_Close()
{
  int v0; // esi

  if ( MagicObjConfigContainer_ptParameterList )
  {
    v0 = *(_DWORD *)((unsigned int)&MagicObjConfigContainer_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
  QTask_DeleteQTaskType(MagicObjConfigContainer_eQTaskType);
}
