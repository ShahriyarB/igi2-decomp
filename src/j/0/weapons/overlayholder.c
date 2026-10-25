/* j/0/weapons/overlayholder.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/weapons/overlayholder.c:76  [size]
void __cdecl OverlayHolder_DisableOverlay(struct OverlayHolder_s *ptOverlayHolder)
{
  struct QReference_s *ptOverlayQTaskRef; // eax
  struct QTask_s *pxObject; // eax

  ptOverlayQTaskRef = ptOverlayHolder->ptOverlayQTaskRef;
  if ( ptOverlayQTaskRef )
  {
    pxObject = (struct QTask_s *)ptOverlayQTaskRef->pxObject;
    isInfraEnabled = 0;
    isDrawInfra = false;
    if ( pxObject )
    {
      QTask_Delete(pxObject);
      QReference_Delete(ptOverlayHolder->ptOverlayQTaskRef, &QTask_tQTaskRefPool);
      ptOverlayHolder->ptOverlayQTaskRef = nullptr;
    }
  }
}

// source: j/0/weapons/overlayholder.c:108  [size~]
void __cdecl OverlayHolder_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ptQTask[5].tQTaskChildren.ptHead = nullptr;
  ptQTask[1].ptPrev = nullptr;
  ptQTask[1].tQTaskChildren.ptHead = nullptr;
  ptQTask[1].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[3].ptNext = nullptr;
  ptQTask[3].ptPrev = nullptr;
  ptQTask[3].tQTaskChildren.ptHead = nullptr;
  ptQTask[3].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[5].ptNext = nullptr;
  ptQTask[1].ptNext = nullptr;
  ptQTask[5].tQTaskChildren.ptMiddle = nullptr;
  LOBYTE(ptQTask[5].ptPrev) = 1;
}

// source: j/0/weapons/overlayholder.c:134  [size~]
void __cdecl OverlayHolder_RunHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptPrev; // edi
  struct QTask_s *v2; // eax
  struct QTask_s *v3; // eax
  struct QTask_s *v4; // eax
  struct QTask_s *v5; // eax

  if ( ptQTask[1].ptPrev && ptQTask[1].tQTaskChildren.ptHead->ptNext && ptQTask[1].tQTaskChildren.ptMiddle )
    ptQTask[5].tQTaskChildren.ptHead = (struct QTask_s *)(__int64)Level_RunLevelExpression(
                                                                    (struct LevelExpression_s *)&ptQTask[1].ptPrev,
                                                                    ptQTask);
  if ( ptQTask[5].tQTaskChildren.ptHead )
  {
    if ( ptQTask[3].ptPrev && ptQTask[3].tQTaskChildren.ptHead->ptNext && ptQTask[3].tQTaskChildren.ptMiddle )
    {
      isInfraEnabled = (__int64)Level_RunLevelExpression((struct LevelExpression_s *)&ptQTask[3].ptPrev, ptQTask);
      isDrawInfra = isInfraEnabled;
    }
    if ( !ptQTask[1].ptNext )
    {
      ptPrev = Game_ptGame->ptGameScreenQTask[1].ptPrev;
      switch ( (unsigned int)ptQTask[5].tQTaskChildren.ptMiddle )
      {
        case 0u:
          v2 = QTask_NewFn(ptPrev, BinocularOverlay_eQTaskType, nullptr);
          v2[294].tQTaskRefList.ptHead = (struct QReference_s *)SLOBYTE(ptQTask[5].ptPrev);
          ptQTask[1].ptNext = (struct QTask_s *)QTask_NewQTaskRef(v2);
          break;
        case 1u:
          v4 = QTask_NewFn(ptPrev, ZoomOverlay_eQTaskType, nullptr);
          ptQTask[1].ptNext = (struct QTask_s *)QTask_NewQTaskRef(v4);
          break;
        case 2u:
          v3 = QTask_NewFn(ptPrev, SniperOverlay_eQTaskType, nullptr);
          ptQTask[1].ptNext = (struct QTask_s *)QTask_NewQTaskRef(v3);
          break;
        case 3u:
          v5 = QTask_NewFn(ptPrev, LaserDesignatorOverlay_eQTaskType, nullptr);
          ptQTask[1].ptNext = (struct QTask_s *)QTask_NewQTaskRef(v5);
          break;
        default:
          ptQTask[1].ptNext = (struct QTask_s *)QTask_NewQTaskRef(ptQTask);
          break;
      }
    }
  }
  else
  {
    OverlayHolder_DisableOverlay((struct OverlayHolder_s *)ptQTask);
  }
}

// source: j/0/weapons/overlayholder.c:198  [size]
void __cdecl OverlayHolder_DeleteHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptNext; // eax
  struct QTask_s *ptHead; // eax

  Level_DeinitLevelExpression((struct LevelExpression_s *)&ptQTask[1].ptPrev);
  Level_DeinitLevelExpression((struct LevelExpression_s *)&ptQTask[3].ptPrev);
  ptNext = ptQTask[1].ptNext;
  if ( ptNext )
  {
    ptHead = ptNext->tQTaskChildren.ptHead;
    isInfraEnabled = 0;
    isDrawInfra = false;
    if ( ptHead )
    {
      QTask_Delete(ptHead);
      QReference_Delete((struct QReference_s *)ptQTask[1].ptNext, &QTask_tQTaskRefPool);
      ptQTask[1].ptNext = nullptr;
    }
  }
}

// source: j/0/weapons/overlayholder.c:219  [size]
void __cdecl OverlayHolder_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = OverlayHolder_ptParameterList;
}

// source: j/0/weapons/overlayholder.c:235  [size]
void __cdecl OverlayHolder_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  Level_CompileLevelExpression((struct LevelExpression_s *)&ptQTask[1].ptPrev, ptQTask);
  Level_CompileLevelExpression((struct LevelExpression_s *)&ptQTask[3].ptPrev, ptQTask);
}

// source: j/0/weapons/overlayholder.c:256  [size]
void __cdecl OverlayHolder_RemoveHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *ptNext; // eax
  struct QTask_s *ptHead; // eax

  ptNext = ptQTask[1].ptNext;
  if ( ptNext )
  {
    ptHead = ptNext->tQTaskChildren.ptHead;
    isInfraEnabled = 0;
    isDrawInfra = false;
    if ( ptHead )
    {
      QTask_Delete(ptHead);
      QReference_Delete((struct QReference_s *)ptQTask[1].ptNext, &QTask_tQTaskRefPool);
      ptQTask[1].ptNext = nullptr;
    }
  }
}

// source: j/0/weapons/overlayholder.c:274  [size]
unsigned __int16 __cdecl OverlayHolder_GetQTaskType()
{
  return OverlayHolder_eQTaskType;
}

// source: j/0/weapons/overlayholder.c:287  [anchor-hash]
void __cdecl OverlayHolder_Open()
{
  unsigned __int16 BaseQTaskType; // ax
  unsigned __int16 v1; // si
  _DWORD *v2; // esi
  _DWORD *v3; // esi
  _DWORD *v4; // esi
  _DWORD *v5; // esi
  struct ParameterList_s *v6; // eax
  int v7; // edx

  BaseQTaskType = QTask_GetBaseQTaskType();
  v1 = QTask_NewQTaskType("OverlayHolder", 216, BaseQTaskType, 0, 0);
  OverlayHolder_eQTaskType = v1;
  QTask_LinkQTaskEventHandlerFn(
    v1,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveHandler);
  QTask_LinkQTaskEventHandlerFn(v1, 0, (void (__cdecl *)(struct QTask_s *, void *))OverlayHolder_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 1, OverlayHolder_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 2, OverlayHolder_DeleteHandler);
  QTask_LinkQTaskEventHandlerFn(
    v1,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))OverlayHolder_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(
    v1,
    ParameterList_eUpdateInternalDataQTaskEvent,
    OverlayHolder_UpdateInternalDataHandler);
  QTask_LinkQTaskEventHandlerFn(v1, DynCubeObj_eDynCubeObjRemoveQTaskEvent, OverlayHolder_RemoveHandler);
  Symbol_Register(
    "OVERLAY_BINOCULAR",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    nullptr,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "OVERLAY_ZOOM",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)1,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "OVERLAY_SNIPER",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)2,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "OVERLAY_LASERDESIGNATOR",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)3,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  OverlayHolder_tOverlayTypeEnumList.pfEnumItemsCallback = ParameterEnumList_EnumerateItemsCallback;
  OverlayHolder_tOverlayTypeEnumList.ptHead = (struct ParameterEnumItem_s *)&OverlayHolder_tOverlayTypeEnumList.ptMiddle;
  OverlayHolder_tOverlayTypeEnumList.ptTail = (struct ParameterEnumItem_s *)&OverlayHolder_tOverlayTypeEnumList;
  OverlayHolder_tOverlayTypeEnumList.ptMiddle = nullptr;
  v2 = Mem_AllocFn(18444, 4);
  v2[1] = 0;
  *v2 = 0;
  v2[4610] = "OVERLAY_BINOCULAR";
  Wildcard_CreateNFA("OVERLAY_BINOCULAR", v2 + 2, (char *)v2 + 10248);
  List_AddTail(v2, (int)&OverlayHolder_tOverlayTypeEnumList);
  v3 = Mem_AllocFn(18444, 4);
  v3[1] = 0;
  *v3 = 0;
  v3[4610] = "OVERLAY_ZOOM";
  Wildcard_CreateNFA("OVERLAY_ZOOM", v3 + 2, (char *)v3 + 10248);
  List_AddTail(v3, (int)&OverlayHolder_tOverlayTypeEnumList);
  v4 = Mem_AllocFn(18444, 4);
  v4[1] = 0;
  *v4 = 0;
  v4[4610] = "OVERLAY_SNIPER";
  Wildcard_CreateNFA("OVERLAY_SNIPER", v4 + 2, (char *)v4 + 10248);
  List_AddTail(v4, (int)&OverlayHolder_tOverlayTypeEnumList);
  v5 = Mem_AllocFn(18444, 4);
  v5[1] = 0;
  *v5 = 0;
  v5[4610] = "OVERLAY_LASERDESIGNATOR";
  Wildcard_CreateNFA("OVERLAY_LASERDESIGNATOR", v5 + 2, (char *)v5 + 10248);
  List_AddTail(v5, (int)&OverlayHolder_tOverlayTypeEnumList);
  v6 = (struct ParameterList_s *)Mem_AllocFn(92, 4);
  v7 = Level_eParameterTypeVarString;
  v6->ptParameterListItem = (struct ParameterListItem_s *)&v6[1];
  v6->nParameters = 0;
  v6->nMaxParameters = 4;
  OverlayHolder_ptParameterList = v6;
  ParameterList_AddParameter(v6, 0x2Cu, v7, "Visible expression", 7u, nullptr);
  ParameterList_AddParameter(
    OverlayHolder_ptParameterList,
    0x7Cu,
    Level_eParameterTypeVarString,
    "Infrared expression",
    7u,
    nullptr);
  ParameterList_AddParameter(
    OverlayHolder_ptParameterList,
    0xD4u,
    ParameterEnumList_eParameterTypeInt32,
    "Overlay type",
    7u,
    &OverlayHolder_tOverlayTypeEnumList);
  ParameterList_AddParameter(
    OverlayHolder_ptParameterList,
    0xCCu,
    Level_eParameterTypebool8,
    "Show Distance",
    7u,
    nullptr);
}

// source: j/0/weapons/overlayholder.c:330  [anchor-hash]
void __cdecl OverlayHolder_Close()
{
  int v0; // esi

  Symbol_Remove("OVERLAY_BINOCULAR");
  Symbol_Remove("OVERLAY_ZOOM");
  Symbol_Remove("OVERLAY_SNIPER");
  Symbol_Remove("OVERLAY_LASERDESIGNATOR");
  ParameterEnumList_DeAlloc(&OverlayHolder_tOverlayTypeEnumList);
  if ( OverlayHolder_ptParameterList )
  {
    v0 = *(_DWORD *)((unsigned int)&OverlayHolder_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
  QTask_DeleteQTaskType(OverlayHolder_eQTaskType);
}
