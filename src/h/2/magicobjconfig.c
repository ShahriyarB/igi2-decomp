/* h/2/magicobjconfig.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: h/2/magicobjconfig.c:42  [anchor-caller]
struct MagicObjType_s *__cdecl MagicObjConfig_AllocMagicObj(
        char *zName,
        char *zModel,
        unsigned __int16 eQTaskType,
        void *pxData)
{
  struct MagicObjType_s *MagicObjType; // eax
  struct MagicObjType_s *v5; // esi

  if ( !strlen(zName) )
    return nullptr;
  MagicObjType = MagicObj_GetMagicObjType(zName);
  if ( MagicObjType )
    MagicObj_RemoveMagicObjType(MagicObjType);
  v5 = MagicObj_AllocMagicObjType();
  strncpy(v5->zName, zName, 0x10u);
  strncpy(v5->zModel, zModel, 0x10u);
  v5->pxData = pxData;
  v5->eQTaskType = eQTaskType;
  return v5;
}

// source: h/2/magicobjconfig.c:77  [anchor-mhash]
void __cdecl MagicObjConfig_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  int v2; // edx

  v2 = RigidMagicObj_eQTaskType;
  LOBYTE(ptQTask[1].ptNext) = 0;
  LOBYTE(ptQTask[1].tQTaskChildren.ptTail) = 0;
  ptQTask[2].ptNext = nullptr;
  *(_DWORD *)&ptQTask[1].eQTaskType = v2;
  ptQTask[1].ptParent = nullptr;
}

// source: h/2/magicobjconfig.c:97  [anchor-caller]
void __cdecl MagicObjConfig_DeleteHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptParent; // ebx
  struct QTask_s *ptNext; // eax
  int v3; // esi

  ptParent = ptQTask[1].ptParent;
  if ( ptParent )
    MagicObj_RemoveMagicObjType((struct MagicObjType_s *)ptParent);
  ptNext = ptQTask[2].ptNext;
  if ( ptNext )
  {
    v3 = *(_DWORD *)((unsigned int)&ptNext[-1].eQTaskType & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v3);
    memset(*(void **)(v3 + 8), 0xCDu, *(_DWORD *)(v3 + 16));
    free((void *)v3);
    ptQTask[2].ptNext = nullptr;
  }
}

// source: h/2/magicobjconfig.c:120  [anchor-caller]
void __cdecl MagicObjConfig_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ptQTask[1].ptParent = (struct QTask_s *)MagicObjConfig_AllocMagicObj(
                                            (char *)&ptQTask[1],
                                            (char *)&ptQTask[1].tQTaskChildren.ptTail,
                                            ptQTask[1].eQTaskType,
                                            ptQTask[2].ptNext);
}

// source: h/2/magicobjconfig.c:137  [anchor-mhash]
void __cdecl MagicObjConfig_UpdateInternalDataAfterLoadHandler(struct QTask_s *ptQTask)
{
  void (__cdecl *pfHandler)(struct QTask_s *, struct MagicObjConfigUpdateTagItemsContext_s *); // ecx
  struct MagicObjConfigUpdateTagItemsContext_s tMagicObjConfigUpdateTagItemsContext; // [esp+0h] [ebp-8h] BYREF

  pfHandler = (void (__cdecl *)(struct QTask_s *, struct MagicObjConfigUpdateTagItemsContext_s *))QTask_aatQTaskFinalEvent[MagicObjConfig_eUpdateTagItemsQTaskEvent][ptQTask[1].eQTaskType].pfHandler;
  if ( pfHandler )
  {
    tMagicObjConfigUpdateTagItemsContext.ptMagicObjConfig = (struct MagicObjConfig_s *)ptQTask;
    tMagicObjConfigUpdateTagItemsContext.ptParent = ptQTask;
    pfHandler(ptQTask, &tMagicObjConfigUpdateTagItemsContext);
  }
}

// source: h/2/magicobjconfig.c:163  [size]
void __cdecl MagicObjConfig_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = MagicObjConfig_ptParameterList;
}

// source: h/2/magicobjconfig.c:181  [size]
struct ParameterEnumItemList_s *__cdecl MagicObjConfig_GetTaskTypeEnumList()
{
  return &MagicObjConfig_tTaskTypeEnumList;
}

// source: h/2/magicobjconfig.c:194  [size]
unsigned __int16 __cdecl MagicObjConfig_GetQTaskType()
{
  return MagicObjConfig_eQTaskType;
}

// source: h/2/magicobjconfig.c:207  [size]
__int16 __cdecl MagicObjConfig_GetUpdateTagItemsQTaskEvent()
{
  return MagicObjConfig_eUpdateTagItemsQTaskEvent;
}

// source: h/2/magicobjconfig.c:220  [anchor-hash]
void __cdecl MagicObjConfig_Open()
{
  unsigned __int16 BaseQTaskType; // ax
  __int16 v1; // ax
  unsigned __int16 v2; // si
  _DWORD *v3; // esi
  _DWORD *v4; // esi
  _DWORD *v5; // esi
  _DWORD *v6; // esi
  struct ParameterList_s *v7; // eax
  int v8; // edx

  BaseQTaskType = QTask_GetBaseQTaskType();
  MagicObjConfig_eQTaskType = QTask_NewQTaskType("MagicObjConfig", 84, BaseQTaskType, 0, 0);
  v1 = QTask_NewQTaskEventFn(0, "MagicObjUpdateTagItems");
  v2 = MagicObjConfig_eQTaskType;
  MagicObjConfig_eUpdateTagItemsQTaskEvent = v1;
  QTask_LinkQTaskEventHandlerFn(MagicObjConfig_eQTaskType, 0, MagicObjConfig_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v2, 2, MagicObjConfig_DeleteHandler);
  QTask_LinkQTaskEventHandlerFn(
    v2,
    ParameterList_eUpdateInternalDataQTaskEvent,
    MagicObjConfig_UpdateInternalDataHandler);
  QTask_LinkQTaskEventHandlerFn(
    v2,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))MagicObjConfig_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(
    v2,
    Level_eUpdateInternalDataAfterLoadEvent,
    MagicObjConfig_UpdateInternalDataAfterLoadHandler);
  QTask_LinkQTaskEventHandlerFn(
    v2,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveHandler);
  MagicObjConfig_tTaskTypeEnumList.pfEnumItemsCallback = ParameterEnumList_EnumerateItemsCallback;
  MagicObjConfig_tTaskTypeEnumList.ptHead = (struct ParameterEnumItem_s *)&MagicObjConfig_tTaskTypeEnumList.ptMiddle;
  MagicObjConfig_tTaskTypeEnumList.ptTail = (struct ParameterEnumItem_s *)&MagicObjConfig_tTaskTypeEnumList;
  MagicObjConfig_tTaskTypeEnumList.ptMiddle = nullptr;
  v3 = Mem_AllocFn(18444, 4);
  v3[1] = 0;
  *v3 = 0;
  v3[4610] = "TASKTYPE_MAGICOBJ";
  Wildcard_CreateNFA("TASKTYPE_MAGICOBJ", v3 + 2, (char *)v3 + 10248);
  List_AddTail(v3, (int)&MagicObjConfig_tTaskTypeEnumList);
  v4 = Mem_AllocFn(18444, 4);
  v4[1] = 0;
  *v4 = 0;
  v4[4610] = "TASKTYPE_BONEMAGICOBJ";
  Wildcard_CreateNFA("TASKTYPE_BONEMAGICOBJ", v4 + 2, (char *)v4 + 10248);
  List_AddTail(v4, (int)&MagicObjConfig_tTaskTypeEnumList);
  v5 = Mem_AllocFn(18444, 4);
  v5[1] = 0;
  *v5 = 0;
  v5[4610] = "TASKTYPE_SHADOWVOLUME";
  Wildcard_CreateNFA("TASKTYPE_SHADOWVOLUME", v5 + 2, (char *)v5 + 10248);
  List_AddTail(v5, (int)&MagicObjConfig_tTaskTypeEnumList);
  v6 = Mem_AllocFn(18444, 4);
  v6[1] = 0;
  *v6 = 0;
  v6[4610] = "TASKTYPE_HUMANSHADOW";
  Wildcard_CreateNFA("TASKTYPE_HUMANSHADOW", v6 + 2, (char *)v6 + 10248);
  List_AddTail(v6, (int)&MagicObjConfig_tTaskTypeEnumList);
  v7 = (struct ParameterList_s *)Mem_AllocFn(72, 4);
  v8 = Level_eParameterTypeString16;
  v7->ptParameterListItem = (struct ParameterListItem_s *)&v7[1];
  v7->nParameters = 0;
  v7->nMaxParameters = 3;
  MagicObjConfig_ptParameterList = v7;
  ParameterList_AddParameter(v7, 0x28u, v8, "Name", 7u, nullptr);
  ParameterList_AddParameter(MagicObjConfig_ptParameterList, 0x38u, Level_eParameterTypeString16, "Model", 7u, nullptr);
  ParameterList_AddParameter(
    MagicObjConfig_ptParameterList,
    0x4Cu,
    ParameterEnumList_eParameterTypeInt32,
    "TaskType",
    7u,
    &MagicObjConfig_tTaskTypeEnumList);
}

// source: h/2/magicobjconfig.c:260  [anchor-hash]
void __cdecl MagicObjConfig_Close()
{
  int v0; // esi

  ParameterEnumList_DeAlloc(&MagicObjConfig_tTaskTypeEnumList);
  if ( MagicObjConfig_ptParameterList )
  {
    v0 = *(_DWORD *)((unsigned int)&MagicObjConfig_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
  QTask_DeleteQTaskEvent(MagicObjConfig_eUpdateTagItemsQTaskEvent);
  QTask_DeleteQTaskType(MagicObjConfig_eQTaskType);
}
