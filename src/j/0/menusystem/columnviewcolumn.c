/* j/0/menusystem/columnviewcolumn.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/menusystem/columnviewcolumn.c:94  [anchor-mhash]
void __cdecl ColumnViewColumn_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *v2; // eax

  ptQTask[1].ptPrev = (struct QTask_s *)1;
  ptQTask[1].tQTaskChildren.ptHead = (struct QTask_s *)100;
  ptQTask[1].tQTaskChildren.ptMiddle = nullptr;
  v2 = (struct QTask_s *)Mem_AllocFn(52, 4);
  v2[1].ptNext = nullptr;
  *(_DWORD *)&v2->eQTaskType = 0;
  v2[1].tQTaskChildren.ptHead = nullptr;
  v2->tQTaskChildren.ptHead = nullptr;
  v2->ptPrev = nullptr;
  v2->tQTaskRefList.ptHead = nullptr;
  v2->tQTaskRefList.ptMiddle = nullptr;
  v2->tQTaskRefList.ptTail = (struct QReference_s *)1;
  v2[1].ptPrev = (struct QTask_s *)64;
  v2->ptParent = (struct QTask_s *)76;
  v2->ptNext = (struct QTask_s *)4;
  v2->tQTaskChildren.ptTail = (struct QTask_s *)76;
  v2->tQTaskChildren.ptMiddle = (struct QTask_s *)64;
  ptQTask[1].ptNext = v2;
}

// source: j/0/menusystem/columnviewcolumn.c:113  [size]
void __cdecl ColumnViewColumn_DeleteHandler(struct QTask_s *ptQTask)
{
  QObjectVector_Delete((struct QObjectVector_s *)ptQTask[1].ptNext);
}

// source: j/0/menusystem/columnviewcolumn.c:129  [size]
void __cdecl ColumnViewColumn_RunHandler(struct QTask_s *ptQTask)
{
  ;
}

// source: j/0/menusystem/columnviewcolumn.c:144  [anchor-mhash]
void __cdecl ColumnViewColumn_DrawHandler(struct QTask_s *ptQTask, void *pxContext)
{
  int v3; // eax
  int v4; // ebp
  int v5; // ecx
  float b; // eax
  int v7; // eax
  int nX; // [esp+8h] [ebp-8h]
  float nXa; // [esp+8h] [ebp-8h]
  int nEntry; // [esp+Ch] [ebp-4h]
  char *pxContexta = *(char * *)&pxContext; // [esp+18h] [ebp+8h] ARGSLOT

  nX = *((_DWORD *)pxContext + 1);
  v3 = *((_DWORD *)pxContext + 7);
  pxContexta = *((char **)pxContext + 2);
  if ( v3 )
  {
    v4 = 0;
    nEntry = *((_DWORD *)pxContext + 3);
    if ( nEntry <= 0 )
    {
      *((_DWORD *)pxContext + 1) += (int)(ptQTask[1].tQTaskChildren.ptHead);
    }
    else
    {
      nXa = (float)nX;
      do
      {
        Text_SetString(
          *((struct StaticTilemap_s **)pxContext + 7),
          *(char **)(*((_DWORD *)&ptQTask[1].ptNext[1].tQTaskChildren.ptHead->ptNext
                           + **(_DWORD **)(*(_DWORD *)(*((_DWORD *)pxContext + 5) + 48)
                                         + 4 * (v4 + *((_DWORD *)pxContext + 4))))
                         + 64));
        *(float *)(*((_DWORD *)pxContext + 7) + 4) = nXa;
        *(float *)(*((_DWORD *)pxContext + 7) + 8) = (float)(int)pxContexta;
        v5 = *((_DWORD *)pxContext + 7);
        if ( v4 == *(_DWORD *)pxContext )
        {
          *(float *)(v5 + 20) = MenuText_atTextColour[4].r;
          *(float *)(*((_DWORD *)pxContext + 7) + 24) = MenuText_atTextColour[4].g;
          b = MenuText_atTextColour[4].b;
        }
        else
        {
          *(float *)(v5 + 20) = MenuText_atTextColour[2].r;
          *(float *)(*((_DWORD *)pxContext + 7) + 24) = MenuText_atTextColour[2].g;
          b = MenuText_atTextColour[2].b;
        }
        *(float *)(*((_DWORD *)pxContext + 7) + 28) = b;
        *(_DWORD *)(*((_DWORD *)pxContext + 7) + 36) |= 0x80000u;
        *(_DWORD *)(*((_DWORD *)pxContext + 7) + 16) = *((_DWORD *)pxContext + 6);
        v7 = *((_DWORD *)pxContext + 7);
        QTilemap_Register(
          *(struct QTilemap_s **)v7,
          *(float *)(v7 + 4),
          *(float *)(v7 + 8),
          *(float *)(v7 + 20),
          *(float *)(v7 + 24),
          *(float *)(v7 + 28),
          *(float *)(v7 + 16),
          *(float *)(v7 + 12),
          *(_DWORD *)(v7 + 36) | 0x40000000,
          *(_DWORD *)(v7 + 32));
        ++v4;
        pxContexta += *((_DWORD *)pxContext + 8);
      }
      while ( v4 < nEntry );
      *((_DWORD *)pxContext + 1) += (int)(ptQTask[1].tQTaskChildren.ptHead);
    }
  }
  else
  {
    *((_DWORD *)pxContext + 1) += (int)(ptQTask[1].tQTaskChildren.ptHead);
  }
}

// source: j/0/menusystem/columnviewcolumn.c:214  [size]
void __cdecl ColumnViewColumn_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ;
}

// source: j/0/menusystem/columnviewcolumn.c:229  [size]
void __cdecl ColumnViewColumn_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = ColumnViewColumn_ptParameterList;
}

// source: j/0/menusystem/columnviewcolumn.c:245  [size]
void __cdecl ColumnViewColumn_AddEntryHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *ptNext; // ebx
  int v3; // eax
  int v4; // edi

  if ( *((_DWORD *)pxContext + 2) == *((_DWORD *)pxContext + 1) )
  {
    ptNext = ptQTask[1].ptNext;
    if ( *(struct QTask_s **)&ptNext->eQTaskType == ptNext[1].ptNext )
      QObjectVector_Realloc((struct QObjectVector_s *)ptQTask[1].ptNext, (unsigned int)ptNext[1].ptPrev);
    v3 = *(_DWORD *)&ptNext->eQTaskType;
    v4 = *((_DWORD *)&ptNext[1].tQTaskChildren.ptHead->ptNext + v3);
    *(_DWORD *)&ptNext->eQTaskType = v3 + 1;
    strncpy((char *)v4, *((char **)pxContext + 5), 0x40u);
    *(_DWORD *)(v4 + 68) = *((_DWORD *)pxContext + 4);
    if ( *((_DWORD *)pxContext + 4) )
    {
      *(_DWORD *)(v4 + 64) = Config_GetLocalizedStringForLanguage(
                               (char *)v4,
                               Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eLanguage,
                               true);
      ++*((_DWORD *)pxContext + 1);
      return;
    }
    *(_DWORD *)(v4 + 64) = v4;
  }
  ++*((_DWORD *)pxContext + 1);
}

// source: j/0/menusystem/columnviewcolumn.c:282  [anchor-mhash]
void __cdecl ColumnViewColumn_DeleteEntryHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QObjectVector_s *ptNext; // eax

  ptNext = (struct QObjectVector_s *)ptQTask[1].ptNext;
  if ( (int)(*(_DWORD *)pxContext) < (signed int)ptNext->nAllocated )
    QObjectVector_RemoveElement(ptNext, *(_DWORD *)pxContext);
}

// source: j/0/menusystem/columnviewcolumn.c:304  [anchor-caller]
int __cdecl ColumnViewColumn_SortCallbackBasicString(void *pxItem1, void *pxItem2)
{
  return ColumnViewColumn_nSortOrder
       * String_Compare(
           *((_BYTE **)ColumnViewColumn_ptColumnViewColumn->ptColumnViewItemVector->papxElement[**(_DWORD **)pxItem2]
           + 16),
           *((char **)ColumnViewColumn_ptColumnViewColumn->ptColumnViewItemVector->papxElement[**(_DWORD **)pxItem1] + 16),
           1);
}

// source: j/0/menusystem/columnviewcolumn.c:332  [anchor-mhash]
int __cdecl ColumnViewColumn_SortCallbackNumericString(void *pxItem1, void *pxItem2)
{
  void **papxElement; // eax
  _DWORD *v3; // esi
  double v4; // st7
  double vItem1; // [esp+4h] [ebp-8h]

  papxElement = ColumnViewColumn_ptColumnViewColumn->ptColumnViewItemVector->papxElement;
  v3 = papxElement[**(_DWORD **)pxItem2];
  vItem1 = atof((char *)*((_DWORD *)papxElement[**(_DWORD **)pxItem1] + 16));
  v4 = atof((char *)v3[16]);
  if ( vItem1 > v4 )
    return ColumnViewColumn_nSortOrder;
  if ( vItem1 >= v4 )
    return 0;
  return -ColumnViewColumn_nSortOrder;
}

// source: j/0/menusystem/columnviewcolumn.c:377  [anchor-mhash]
void __cdecl ColumnViewColumn_SortEntriesHandler(struct QTask_s *ptQTask, void *pxContext)
{
  bool v2; // zf
  int v3; // ecx
  int v4; // edx
  int v5; // ecx
  int v6; // edx
  int (__cdecl *apfSortCallback[2])(void *, void *); // [esp+4h] [ebp-8h]

  v2 = *((_DWORD *)pxContext + 1) == *(_DWORD *)pxContext;
  apfSortCallback[0] = ColumnViewColumn_SortCallbackBasicString;
  apfSortCallback[1] = ColumnViewColumn_SortCallbackNumericString;
  if ( v2 )
  {
    v3 = *((_DWORD *)pxContext + 2);
    if ( !v3 )
      v3 = -(int)ptQTask[1].ptPrev;
    v4 = v3;
    ptQTask[1].ptPrev = (struct QTask_s *)v3;
    v5 = *((_DWORD *)pxContext + 3);
    ColumnViewColumn_nSortOrder = v4;
    v6 = *(_DWORD *)(v5 + 36);
    ColumnViewColumn_ptColumnViewColumn = (struct ColumnViewColumn_s *)ptQTask;
    if ( v6 )
    {
      qsort(*(_DWORD *)(v5 + 48), v6, 4, apfSortCallback[(int)ptQTask[1].tQTaskChildren.ptMiddle]);
      ++*(_DWORD *)pxContext;
      return;
    }
  }
  else
  {
    ptQTask[1].ptPrev = (struct QTask_s *)-1;
  }
  ++*(_DWORD *)pxContext;
}

// source: j/0/menusystem/columnviewcolumn.c:425  [size]
unsigned __int16 __cdecl ColumnViewColumn_GetQTaskType()
{
  return ColumnViewColumn_eQTaskType;
}

// source: j/0/menusystem/columnviewcolumn.c:438  [anchor-hash]
void __cdecl ColumnViewColumn_Open()
{
  unsigned __int16 BaseQTaskType; // ax
  unsigned __int16 v1; // si
  _DWORD *v2; // esi
  _DWORD *v3; // esi
  struct ParameterList_s *v4; // eax

  BaseQTaskType = QTask_GetBaseQTaskType();
  v1 = QTask_NewQTaskType("ColumnViewColumn", 56, BaseQTaskType, 0, 0);
  ColumnViewColumn_eQTaskType = v1;
  QTask_LinkQTaskEventHandlerFn(v1, 0, ColumnViewColumn_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 2, ColumnViewColumn_DeleteHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 1, (void (__cdecl *)(struct QTask_s *))ColumnViewColumn_RunHandler);
  QTask_LinkQTaskEventHandlerFn(v1, ColumnView_eDrawEntriesQTaskEvent, ColumnViewColumn_DrawHandler);
  QTask_LinkQTaskEventHandlerFn(
    v1,
    ParameterList_eUpdateInternalDataQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))ColumnViewColumn_UpdateInternalDataHandler);
  QTask_LinkQTaskEventHandlerFn(
    v1,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))ColumnViewColumn_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(v1, ColumnView_eAddEntryQTaskEvent, ColumnViewColumn_AddEntryHandler);
  QTask_LinkQTaskEventHandlerFn(v1, ColumnView_eDeleteEntryQTaskEvent, ColumnViewColumn_DeleteEntryHandler);
  QTask_LinkQTaskEventHandlerFn(v1, ColumnView_eSortEntriesQTaskEvent, ColumnViewColumn_SortEntriesHandler);
  QTask_LinkQTaskEventHandlerFn(
    v1,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveHandler);
  ColumnViewColumn_tDataTypeEnumList.pfEnumItemsCallback = ParameterEnumList_EnumerateItemsCallback;
  ColumnViewColumn_tDataTypeEnumList.ptHead = (struct ParameterEnumItem_s *)&ColumnViewColumn_tDataTypeEnumList.ptMiddle;
  ColumnViewColumn_tDataTypeEnumList.ptTail = (struct ParameterEnumItem_s *)&ColumnViewColumn_tDataTypeEnumList;
  ColumnViewColumn_tDataTypeEnumList.ptMiddle = nullptr;
  v2 = Mem_AllocFn(18444, 4);
  v2[1] = 0;
  *v2 = 0;
  v2[4610] = "COLUMNVIEW_DATATYPE_BASICSTRING";
  Wildcard_CreateNFA("COLUMNVIEW_DATATYPE_BASICSTRING", v2 + 2, (char *)v2 + 10248);
  List_AddTail(v2, (int)&ColumnViewColumn_tDataTypeEnumList);
  v3 = Mem_AllocFn(18444, 4);
  v3[1] = 0;
  *v3 = 0;
  v3[4610] = "COLUMNVIEW_DATATYPE_NUMERICSTRING";
  Wildcard_CreateNFA("COLUMNVIEW_DATATYPE_NUMERICSTRING", v3 + 2, (char *)v3 + 10248);
  List_AddTail(v3, (int)&ColumnViewColumn_tDataTypeEnumList);
  Symbol_Register(
    "COLUMNVIEW_DATATYPE_BASICSTRING",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    nullptr,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "COLUMNVIEW_DATATYPE_NUMERICSTRING",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)1,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  v4 = (struct ParameterList_s *)Mem_AllocFn(52, 4);
  v4->nParameters = 0;
  v4->nMaxParameters = 2;
  v4->ptParameterListItem = (struct ParameterListItem_s *)&v4[1];
  ColumnViewColumn_ptParameterList = v4;
  ParameterList_AddParameterMinMax(v4, 0x30u, Level_eParameterTypeInt32, "Width", 7u, 0.0, 640.0);
  ParameterList_AddParameter(
    ColumnViewColumn_ptParameterList,
    0x34u,
    ParameterEnumList_eParameterTypeInt32,
    "Column data type",
    7u,
    &ColumnViewColumn_tDataTypeEnumList);
}

// source: j/0/menusystem/columnviewcolumn.c:478  [anchor-hash]
void __cdecl ColumnViewColumn_Close()
{
  int v0; // esi

  ParameterEnumList_DeAlloc(&ColumnViewColumn_tDataTypeEnumList);
  Symbol_Remove("COLUMNVIEW_DATATYPE_NUMERICSTRING");
  Symbol_Remove("COLUMNVIEW_DATATYPE_BASICSTRING");
  if ( ColumnViewColumn_ptParameterList )
  {
    v0 = *(_DWORD *)((unsigned int)&ColumnViewColumn_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
  QTask_DeleteQTaskType(ColumnViewColumn_eQTaskType);
}
