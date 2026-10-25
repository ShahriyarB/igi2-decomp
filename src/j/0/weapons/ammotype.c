/* j/0/weapons/ammotype.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/weapons/ammotype.c:137  [anchor-mhash]
void __cdecl AmmoType_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  int v2; // ecx

  v2 = AmmoType_eID;
  ptQTask[2].tQTaskRefList.ptMiddle = (struct QReference_s *)AmmoType_eID;
  AmmoType_eID = v2 + 1;
  ptQTask[2].tQTaskRefList.ptTail = nullptr;
  strcpy((char *)&ptQTask[1], "AMMO_ID_UNDEFINED");
  LOBYTE(ptQTask[1].ptParent) = 0;
  LOBYTE(ptQTask[3].tQTaskRefList.ptMiddle) = 0;
  LOBYTE(ptQTask[2].ptParent) = 0;
  LOBYTE(ptQTask[4].tQTaskChildren.ptTail) = 0;
  BYTE1(ptQTask[4].tQTaskChildren.ptTail) = 1;
  ptQTask[4].tQTaskRefList.ptTail = (struct QReference_s *)255;
  ptQTask[4].ptParent = (struct QTask_s *)128;
  *(_DWORD *)&ptQTask[4].eQTaskType = 0;
  ptQTask[5].ptNext = (struct QTask_s *)255;
  ptQTask[5].ptPrev = (struct QTask_s *)255;
  ptQTask[5].tQTaskChildren.ptHead = nullptr;
  ptQTask[4].tQTaskRefList.ptHead = (struct QReference_s *)40;
  ptQTask[4].tQTaskRefList.ptMiddle = (struct QReference_s *)10;
  LOBYTE(ptQTask[5].tQTaskChildren.ptMiddle) = 0;
}

// source: j/0/weapons/ammotype.c:185  [size]
void __cdecl AmmoType_RunHandler(struct QTask_s *ptQTask)
{
  ;
}

// source: j/0/weapons/ammotype.c:198  [anchor-mhash]
void __cdecl AmmoType_DeleteHandler(struct QTask_s *ptQTask)
{
  AmmoType_aptAmmoTypeFromIDTable[(int)ptQTask[2].tQTaskRefList.ptMiddle] = nullptr;
  if ( ptQTask[2].tQTaskRefList.ptTail )
    Symbol_Remove((char *)&ptQTask[1].ptParent);
}

// source: j/0/weapons/ammotype.c:221  [anchor-mhash]
void __cdecl AmmoType_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *v2; // eax
  char ptNext; // cl

  if ( ptQTask[2].tQTaskRefList.ptTail )
  {
    Symbol_Remove((char *)&ptQTask[1].ptParent);
    ptQTask[2].tQTaskRefList.ptTail = nullptr;
  }
  if ( strcmp((char *)&ptQTask[1], "AMMO_ID_UNDEFINED") )
  {
    Symbol_Register(
      (char *)&ptQTask[1],
      (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
      ptQTask[2].tQTaskRefList.ptMiddle,
      4,
      QSCRIPT_SYMBOLCLASS_CONSTANT,
      QSCRIPT_SYMBOLTYPE_INT,
      QSCRIPT_SYMBOLLIFESPAN_INFINITE);
    v2 = ptQTask + 1;
    do
    {
      ptNext = (char)v2->ptNext;
      LOBYTE(v2->ptParent) = v2->ptNext;
      v2 = (struct QTask_s *)((char *)v2 + 1);
    }
    while ( ptNext );
    ptQTask[2].tQTaskRefList.ptTail = (struct QReference_s *)1;
  }
}

// source: j/0/weapons/ammotype.c:261  [size]
void __cdecl AmmoType_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = AmmoType_ptParameterList;
}

// source: j/0/weapons/ammotype.c:279  [anchor-mhash]
void __cdecl AmmoType_GetAmmoTypeFromIDHandler(struct QTask_s *ptQTask, void *pxContext)
{
  if ( !*((_DWORD *)pxContext + 1) && *(struct QReference_s **)pxContext == ptQTask[2].tQTaskRefList.ptMiddle )
    *((_DWORD *)pxContext + 1) = ptQTask;
}

// source: j/0/weapons/ammotype.c:314  [anchor-mhash]
void __cdecl AmmoType_CheckForDuplicateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  if ( *(struct QTask_s **)pxContext != ptQTask
    && !*((_DWORD *)pxContext + 1)
    && !strcmp((char *)&ptQTask[1], (char *)(*(_DWORD *)pxContext + 40)) )
  {
    *((_DWORD *)pxContext + 1) = 1;
  }
}

// source: j/0/weapons/ammotype.c:344  [size]
void __cdecl AmmoType_EnumerateAmmoTypesHandler(struct QTask_s *ptQTask, void *pxContext)
{
  (*(void (__cdecl **)(struct QTask_s *, _DWORD))pxContext)(ptQTask, *((_DWORD *)pxContext + 1));
}

// source: j/0/weapons/ammotype.c:366  [size]
void __cdecl AmmoTypeContainer_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ptQTask[1].ptNext = nullptr;
}

// source: j/0/weapons/ammotype.c:382  [size]
void __cdecl AmmoTypeContainer_RunHandler(struct QTask_s *ptQTask)
{
  ;
}

// source: j/0/weapons/ammotype.c:395  [anchor-hash]
void __cdecl AmmoTypeContainer_DeleteHandler(struct QTask_s *ptQTask)
{
  memset(AmmoType_aptAmmoTypeFromIDTable, 0, sizeof(AmmoType_aptAmmoTypeFromIDTable));
}

// source: j/0/weapons/ammotype.c:408  [size]
void __cdecl AmmoTypeContainer_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ;
}

// source: j/0/weapons/ammotype.c:434  [size]
void __cdecl AmmoTypeContainer_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = AmmoTypeContainer_ptParameterList;
}

// source: j/0/weapons/ammotype.c:486  [anchor-hash]
void __cdecl AmmoType_Open()
{
  unsigned __int16 BaseQTaskType; // ax
  unsigned __int16 v1; // ax
  __int16 v2; // ax
  unsigned __int16 v3; // si
  __int16 v4; // di
  __int16 v5; // bx
  __int16 v6; // bp
  unsigned __int16 v7; // si
  struct ParameterList_s *v8; // eax
  int v9; // edx
  struct ParameterList_s *v10; // eax
  int v11; // edx
  _DWORD *v12; // esi

  BaseQTaskType = QTask_GetBaseQTaskType();
  AmmoType_eQTaskType = QTask_NewQTaskType("AmmoType", 244, BaseQTaskType, 0, 0);
  v1 = QTask_GetBaseQTaskType();
  AmmoTypeContainer_eQTaskType = QTask_NewQTaskType("AmmoTypeContainer", 44, v1, 0, 0);
  AmmoType_eGetAmmoTypeFromIDQTaskEvent = QTask_NewQTaskEventFn(0, "GetAmmoTypeFromID");
  AmmoType_eCheckForDuplicateQTaskEvent = QTask_NewQTaskEventFn(0, "CheckForDuplicate");
  v2 = QTask_NewQTaskEventFn(0, "EnumerateAmmoTypes");
  v3 = AmmoType_eQTaskType;
  v4 = v2;
  AmmoType_eEnumerateAmmoTypesQTaskEvent = v2;
  QTask_LinkQTaskEventHandlerFn(
    AmmoType_eQTaskType,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveNoChildrenHandler);
  QTask_LinkQTaskEventHandlerFn(v3, 0, AmmoType_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v3, 1, (void (__cdecl *)(struct QTask_s *))AmmoType_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v3, 2, AmmoType_DeleteHandler);
  v5 = ParameterList_eUpdateInternalDataQTaskEvent;
  QTask_LinkQTaskEventHandlerFn(v3, ParameterList_eUpdateInternalDataQTaskEvent, AmmoType_UpdateInternalDataHandler);
  v6 = ParameterList_eGetParameterListQTaskEvent;
  QTask_LinkQTaskEventHandlerFn(
    v3,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))AmmoType_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(v3, AmmoType_eGetAmmoTypeFromIDQTaskEvent, AmmoType_GetAmmoTypeFromIDHandler);
  QTask_LinkQTaskEventHandlerFn(v3, AmmoType_eCheckForDuplicateQTaskEvent, AmmoType_CheckForDuplicateHandler);
  QTask_LinkQTaskEventHandlerFn(v3, v4, (void (__cdecl *)(struct QTask_s *, void *))AmmoType_EnumerateAmmoTypesHandler);
  v7 = AmmoTypeContainer_eQTaskType;
  QTask_LinkQTaskEventHandlerFn(
    AmmoTypeContainer_eQTaskType,
    0,
    (void (__cdecl *)(struct QTask_s *, void *))AmmoTypeContainer_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v7, 1, (void (__cdecl *)(struct QTask_s *))AmmoTypeContainer_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v7, 2, (void (__cdecl *)(struct QTask_s *))AmmoTypeContainer_DeleteHandler);
  QTask_LinkQTaskEventHandlerFn(
    v7,
    v5,
    (void (__cdecl *)(struct QTask_s *, void *))AmmoTypeContainer_UpdateInternalDataHandler);
  QTask_LinkQTaskEventHandlerFn(
    v7,
    v6,
    (void (__cdecl *)(struct QTask_s *, void *))AmmoTypeContainer_GetParameterListHandler);
  v8 = (struct ParameterList_s *)Mem_AllocFn(292, 4);
  v8->ptParameterListItem = (struct ParameterListItem_s *)&v8[1];
  v9 = Level_eParameterTypeString32;
  v8->nParameters = 0;
  v8->nMaxParameters = 14;
  AmmoType_ptParameterList = v8;
  ParameterList_AddParameter(v8, 0x28u, v9, "Ammo ID", 7u, nullptr);
  ParameterList_AddParameter(AmmoType_ptParameterList, 0x70u, Level_eParameterTypeString32, "Casing Model", 7u, nullptr);
  ParameterList_AddParameter(
    AmmoType_ptParameterList,
    0x90u,
    Level_eParameterTypeString32,
    "Model (Used for ammopickup)",
    7u,
    nullptr);
  ParameterList_AddParameter(AmmoType_ptParameterList, 0xB0u, Level_eParameterTypebool8, "Enable Tracer", 7u, nullptr);
  ParameterList_AddParameter(
    AmmoType_ptParameterList,
    0xB1u,
    Level_eParameterTypebool8,
    "Used for Accuracy-Score",
    7u,
    nullptr);
  ParameterList_AddParameter(AmmoType_ptParameterList, 0xBCu, Level_eParameterTypeInt32, "Tracer Start R", 7u, nullptr);
  ParameterList_AddParameter(AmmoType_ptParameterList, 0xC0u, Level_eParameterTypeInt32, "Tracer Start G", 7u, nullptr);
  ParameterList_AddParameter(AmmoType_ptParameterList, 0xC4u, Level_eParameterTypeInt32, "Tracer Start B", 7u, nullptr);
  ParameterList_AddParameter(AmmoType_ptParameterList, 0xC8u, Level_eParameterTypeInt32, "Tracer End R", 7u, nullptr);
  ParameterList_AddParameter(AmmoType_ptParameterList, 0xCCu, Level_eParameterTypeInt32, "Tracer End G", 7u, nullptr);
  ParameterList_AddParameter(AmmoType_ptParameterList, 0xD0u, Level_eParameterTypeInt32, "Tracer End B", 7u, nullptr);
  ParameterList_AddParameter(AmmoType_ptParameterList, 0xB4u, Level_eParameterTypeInt32, "Shop price", 7u, nullptr);
  ParameterList_AddParameter(AmmoType_ptParameterList, 0xB8u, Level_eParameterTypeInt32, "Shop amount", 7u, nullptr);
  ParameterList_AddParameter(
    AmmoType_ptParameterList,
    0xD4u,
    Level_eParameterTypeString32,
    "Shop Name Resource",
    7u,
    nullptr);
  v10 = (struct ParameterList_s *)Mem_AllocFn(32, 4);
  v10->nParameters = 0;
  v11 = Level_eParameterTypePushButton;
  v10->ptParameterListItem = (struct ParameterListItem_s *)&v10[1];
  v10->nMaxParameters = 1;
  AmmoTypeContainer_ptParameterList = v10;
  ParameterList_AddParameter(v10, 0x28u, v11, "Save", 6u, nullptr);
  AmmoType_tEnumList.pfEnumItemsCallback = ParameterEnumList_EnumerateItemsCallback;
  AmmoType_tEnumList.ptHead = (struct ParameterEnumItem_s *)&AmmoType_tEnumList.ptMiddle;
  AmmoType_tEnumList.ptTail = (struct ParameterEnumItem_s *)&AmmoType_tEnumList;
  AmmoType_tEnumList.ptMiddle = nullptr;
  v12 = Mem_AllocFn(18444, 4);
  v12[1] = 0;
  *v12 = 0;
  v12[4610] = "AMMO_ID_.*";
  Wildcard_CreateNFA("AMMO_ID_.*", v12 + 2, (char *)v12 + 10248);
  List_AddTail(v12, (int)&AmmoType_tEnumList);
  Symbol_Register(
    "AMMO_ID_UNDEFINED",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)0xFFFFFFFF,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
}

// source: j/0/weapons/ammotype.c:568  [anchor-hash]
void __cdecl AmmoType_Close()
{
  int v0; // esi
  int v1; // esi

  Symbol_Remove("AMMO_ID_UNDEFINED");
  ParameterEnumList_DeAlloc(&AmmoType_tEnumList);
  if ( AmmoTypeContainer_ptParameterList )
  {
    v0 = *(_DWORD *)((unsigned int)&AmmoTypeContainer_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
  if ( AmmoType_ptParameterList )
  {
    v1 = *(_DWORD *)((unsigned int)&AmmoType_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v1);
    memset(*(void **)(v1 + 8), 0xCDu, *(_DWORD *)(v1 + 16));
    free((void *)v1);
  }
  QTask_DeleteQTaskEvent(AmmoType_eGetAmmoTypeFromIDQTaskEvent);
  QTask_DeleteQTaskEvent(AmmoType_eCheckForDuplicateQTaskEvent);
  QTask_DeleteQTaskEvent(AmmoType_eEnumerateAmmoTypesQTaskEvent);
  QTask_DeleteQTaskType(AmmoTypeContainer_eQTaskType);
  QTask_DeleteQTaskType(AmmoType_eQTaskType);
}

// source: j/0/weapons/ammotype.c:599  [size]
unsigned __int16 __cdecl AmmoType_GetQTaskType()
{
  return AmmoType_eQTaskType;
}

// source: j/0/weapons/ammotype.c:613  [size]
struct ParameterEnumItemList_s *__cdecl AmmoType_GetAmmoEnumList()
{
  return &AmmoType_tEnumList;
}

// source: j/0/weapons/ammotype.c:626  [anchor-strings]
void __cdecl AmmoType_LoadConfig()
{
  AmmoType_ptContainer = QTask_NewFn(&Flow_ptFlow->tQTask, AmmoTypeContainer_eQTaskType, nullptr);
  Level_LoadQTask(AmmoType_ptContainer, "LOCAL:weapons/ammo.qsc", false);
}

// source: j/0/weapons/ammotype.c:646  [size]
// attributes: thunk
int __cdecl AmmoType_GetIDFromScriptID(char *pzScriptID)
{
  return Script_ParseLineInt32(pzScriptID);
}

// source: j/0/weapons/ammotype.c:670  [anchor-callee]
struct AmmoType_s *__cdecl AmmoType_GetAmmoTypeFromID(int eAmmoTypeID)
{
  struct AmmoType_s *result; // eax
  struct QTask_s *ptHead; // ecx
  int v3; // edx
  struct QTask_s *v4; // eax
  int eQTaskType; // eax
  struct AmmoTypeGetAmmoTypeFromIDContext_s tContext; // [esp+0h] [ebp-8h] BYREF

  result = AmmoType_aptAmmoTypeFromIDTable[eAmmoTypeID];
  if ( !result )
  {
    tContext.eAmmoTypeID = eAmmoTypeID;
    tContext.ptAmmoType = nullptr;
    ptHead = AmmoType_ptContainer->tQTaskChildren.ptHead;
    if ( ptHead->ptNext && ptHead )
    {
      v3 = QTask_nProtectedQTaskStackOffset;
      do
      {
        if ( ptHead->ptNext )
          v4 = ptHead->ptNext->ptNext != nullptr ? ptHead->ptNext : nullptr;
        else
          v4 = nullptr;
        QTask_atProtectedQTaskStack[v3].ptQTask = v4;
        eQTaskType = ptHead->eQTaskType;
        QTask_nProtectedQTaskStackOffset = v3 + 1;
        ((void (__cdecl *)(struct QTask_s *, struct AmmoTypeGetAmmoTypeFromIDContext_s *))QTask_aatQTaskFinalEvent[AmmoType_eGetAmmoTypeFromIDQTaskEvent][eQTaskType].pfHandler)(
          ptHead,
          &tContext);
        ptHead = (struct QTask_s *)dword_849C7DC[QTask_nProtectedQTaskStackOffset];
        v3 = --QTask_nProtectedQTaskStackOffset;
      }
      while ( ptHead );
      result = tContext.ptAmmoType;
    }
    AmmoType_aptAmmoTypeFromIDTable[eAmmoTypeID] = result;
  }
  return result;
}

// source: j/0/weapons/ammotype.c:700  [size]
struct AmmoType_s *__cdecl AmmoType_GetAmmoTypeFromScriptID(char *pzScriptID)
{
  int v1; // eax

  v1 = Script_ParseLineInt32(pzScriptID);
  return AmmoType_GetAmmoTypeFromID(v1);
}

// source: j/0/weapons/ammotype.c:720  [anchor-callee]
void __cdecl AmmoType_EnumerateAmmoTypes(
        void (__cdecl *pfCallback)(struct AmmoType_s *, void *),
        void *pxContext)
{
  struct QTask_s *ptHead; // eax
  int v3; // edx
  struct QTask_s *v4; // ecx
  struct AmmoTypeEnumerateAmmoTypesContext_s tContext; // [esp+0h] [ebp-8h] BYREF

  tContext.pfCallback = pfCallback;
  tContext.pxContext = pxContext;
  ptHead = AmmoType_ptContainer->tQTaskChildren.ptHead;
  if ( ptHead->ptNext && ptHead )
  {
    v3 = QTask_nProtectedQTaskStackOffset;
    do
    {
      if ( ptHead->ptNext )
        v4 = ptHead->ptNext->ptNext != nullptr ? ptHead->ptNext : nullptr;
      else
        v4 = nullptr;
      QTask_atProtectedQTaskStack[v3].ptQTask = v4;
      QTask_nProtectedQTaskStackOffset = v3 + 1;
      ((void (__cdecl *)(struct QTask_s *, struct AmmoTypeEnumerateAmmoTypesContext_s *))QTask_aatQTaskFinalEvent[AmmoType_eEnumerateAmmoTypesQTaskEvent][ptHead->eQTaskType].pfHandler)(
        ptHead,
        &tContext);
      ptHead = (struct QTask_s *)dword_849C7DC[QTask_nProtectedQTaskStackOffset];
      v3 = --QTask_nProtectedQTaskStackOffset;
    }
    while ( ptHead );
  }
}
