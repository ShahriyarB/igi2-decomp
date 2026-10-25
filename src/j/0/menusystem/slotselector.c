/* j/0/menusystem/slotselector.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/menusystem/slotselector.c:49  [size]
struct SlotSelector_s *__cdecl SlotSelector_GetSlotSelector()
{
  return SlotSelector_ptActiveSelector;
}

// source: j/0/menusystem/slotselector.c:66  [size]
struct SlotSelector_s *__cdecl SlotSelector_SetActiveSlotSelector(
        struct SlotSelector_s *ptSlotSelector)
{
  SlotSelector_ptActiveSelector = ptSlotSelector;
  return ptSlotSelector;
}

// source: j/0/menusystem/slotselector.c:85  [anchor-mhash]
void __cdecl SlotSelector_AddToActive(struct SlotItem_s *ptSlotSelectorItem, int nSlot)
{
  struct SlotCategory_s *ptActiveCategory; // eax

  ptActiveCategory = SlotSelector_ptActiveSelector->ptActiveCategory;
  if ( ptActiveCategory )
    ptActiveCategory->aItems[nSlot] = (*(struct SlotItem_s *)&ptSlotSelectorItem->nItemID);
}

// source: j/0/menusystem/slotselector.c:111  [anchor-hash]
struct SlotCategory_s *__cdecl SlotSelector_GetCategory(int nCategory)
{
  unsigned __int16 v1; // dx
  struct SlotCategory_s *result; // eax

  v1 = SlotCategory_eQTaskType;
  result = (struct SlotCategory_s *)QTask_GetFirstChildOfType(
                                      &SlotSelector_ptActiveSelector->tQTask,
                                      SlotCategory_eQTaskType);
  if ( !result )
    return nullptr;
  while ( result->nCategory != nCategory )
  {
    result = (struct SlotCategory_s *)QTask_GetNextSiblingOfType(&result->tQTask, v1);
    if ( !result )
      return nullptr;
  }
  return result;
}

// source: j/0/menusystem/slotselector.c:149  [anchor-hash]
enum bool __cdecl SlotSelector_isCategory(int nCategory)
{
  unsigned __int16 v1; // dx
  struct QTask_s *FirstChildOfType; // eax

  v1 = SlotCategory_eQTaskType;
  FirstChildOfType = QTask_GetFirstChildOfType(&SlotSelector_ptActiveSelector->tQTask, SlotCategory_eQTaskType);
  if ( FirstChildOfType )
  {
    while ( FirstChildOfType[1].ptNext != (struct QTask_s *)nCategory )
    {
      FirstChildOfType = QTask_GetNextSiblingOfType(FirstChildOfType, v1);
      if ( !FirstChildOfType )
        goto LABEL_4;
    }
  }
  else
  {
LABEL_4:
    FirstChildOfType = nullptr;
  }
  return FirstChildOfType != nullptr;
}

// source: j/0/menusystem/slotselector.c:170  [size]
void __cdecl SlotSelector_SetCallbacks(
        void (__cdecl *pfItemClicked)(struct SlotSelector_s *, struct SlotCategory_s *, struct SlotItem_s *, int),
        enum bool (__cdecl *pfItemEnabled)(int),
        void (__cdecl *pfItemText)(int, char *))
{
  struct SlotSelector_s *v3; // eax

  v3 = SlotSelector_ptActiveSelector;
  SlotSelector_ptActiveSelector->pfItemClicked = pfItemClicked;
  v3->pfItemEnabled = pfItemEnabled;
  v3->pfItemText = pfItemText;
}

// source: j/0/menusystem/slotselector.c:200  [anchor-callee]
void __cdecl SlotSelector_CreateCategory(char *zName, int nCategory)
{
  unsigned __int16 v2; // dx
  struct SlotSelector_s *v3; // esi
  struct SlotSelector_s *v4; // edi
  struct QTask_s *FirstChildOfType; // eax
  enum bool (__cdecl *pfItemEnabled)(int); // ecx
  void (__cdecl *pfItemText)(int, char *); // edx
  struct SlotCategoryCreateContext_s tCreateContext; // [esp+8h] [ebp-30h] BYREF

  v2 = SlotCategory_eQTaskType;
  v3 = SlotSelector_ptActiveSelector;
  v4 = SlotSelector_ptActiveSelector;
  FirstChildOfType = QTask_GetFirstChildOfType(&SlotSelector_ptActiveSelector->tQTask, SlotCategory_eQTaskType);
  if ( FirstChildOfType )
  {
    while ( FirstChildOfType[1].ptNext != (struct QTask_s *)nCategory )
    {
      FirstChildOfType = QTask_GetNextSiblingOfType(FirstChildOfType, v2);
      if ( !FirstChildOfType )
        goto LABEL_4;
    }
  }
  else
  {
LABEL_4:
    pfItemEnabled = v3->pfItemEnabled;
    pfItemText = v3->pfItemText;
    tCreateContext.pfItemClicked = v3->pfItemClicked;
    tCreateContext.pfItemEnabled = pfItemEnabled;
    tCreateContext.nCategory = nCategory;
    tCreateContext.pfItemText = pfItemText;
    strncpy(tCreateContext.zName, zName, 0x20u);
    FirstChildOfType = QTask_NewFn(&v4->tQTask, SlotCategory_eQTaskType, &tCreateContext);
  }
  v4->ptActiveCategory = (struct SlotCategory_s *)FirstChildOfType;
}

// source: j/0/menusystem/slotselector.c:241  [anchor-callee]
void __cdecl SlotSelector_SetActiveCategory(int nCategory)
{
  struct SlotSelector_s *v1; // esi
  struct SlotCategory_s *ptActiveCategory; // eax
  unsigned __int16 v3; // dx
  struct QTask_s *FirstChildOfType; // eax

  v1 = SlotSelector_ptActiveSelector;
  ptActiveCategory = SlotSelector_ptActiveSelector->ptActiveCategory;
  if ( !ptActiveCategory || ptActiveCategory->nCategory != nCategory )
  {
    v3 = SlotCategory_eQTaskType;
    FirstChildOfType = QTask_GetFirstChildOfType(&SlotSelector_ptActiveSelector->tQTask, SlotCategory_eQTaskType);
    if ( FirstChildOfType )
    {
      while ( FirstChildOfType[1].ptNext != (struct QTask_s *)nCategory )
      {
        FirstChildOfType = QTask_GetNextSiblingOfType(FirstChildOfType, v3);
        if ( !FirstChildOfType )
          return;
      }
      v1->ptActiveCategory = (struct SlotCategory_s *)FirstChildOfType;
    }
  }
}

// source: j/0/menusystem/slotselector.c:278  [anchor-hash]
int __cdecl SlotSelector_GetActiveCategoryIfAny()
{
  struct SlotCategory_s *ptActiveCategory; // eax

  if ( SlotSelector_ptActiveSelector && (ptActiveCategory = SlotSelector_ptActiveSelector->ptActiveCategory) != nullptr )
    return ptActiveCategory->nCategory;
  else
    return -1;
}

// source: j/0/menusystem/slotselector.c:310  [anchor-caller]
struct Result_s *__cdecl SlotSelector_SetActiveCategoryCB(
        struct Result_s *retstr,
        void *pxUnUsed,
        struct ArgList_s *ptArgList)
{
  struct ArgList_s *v3; // edi
  struct ArgList_s *v4; // eax
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  v3 = ptArgList;
  if ( ptArgList->isQVM )
  {
    ptArgList = nullptr;
    QVM_EvalArg(&ptArgList, 4, v3, 1, 1);
    v4 = ptArgList;
  }
  else
  {
    v4 = (struct ArgList_s *)Expression_EvalInt(ptArgList->aptExpression[1]);
  }
  SlotSelector_SetActiveCategory((int)v4);
  Rs.nResult = 0;
  Rs.vResult = 0.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/menusystem/slotselector.c:331  [anchor-hash]
void __cdecl SlotSelector_DeactiveateCategory()
{
  SlotSelector_ptActiveSelector->ptActiveCategory = nullptr;
}

// source: j/0/menusystem/slotselector.c:352  [anchor-mhash]
struct Result_s *__cdecl SlotSelector_DeactiveateCategoryCB(
        struct Result_s *retstr,
        void *pxUnUsed,
        struct ArgList_s *ptArgList)
{
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  SlotSelector_ptActiveSelector->ptActiveCategory = nullptr;
  Rs.nResult = 0;
  Rs.vResult = 0.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/menusystem/slotselector.c:367  [anchor-strings]
struct Result_s *__cdecl SlotSelector_SetSlotCategoryNameCB(
        struct Result_s *retstr,
        void *pxUnUsed,
        struct ArgList_s *ptArgList)
{
  struct SlotCategory_s *ptActiveCategory; // eax
  char *LocalizedStringForLanguage; // eax
  struct Result_s Rs; // [esp+0h] [ebp-18h] BYREF

  ptActiveCategory = SlotSelector_ptActiveSelector->ptActiveCategory;
  if ( ptActiveCategory )
  {
    LocalizedStringForLanguage = Config_GetLocalizedStringForLanguage(
                                   ptActiveCategory->zName,
                                   Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eLanguage,
                                   true);
    MenuText_SetText(-1, LocalizedStringForLanguage);
  }
  else
  {
    MenuText_SetText(-1, "(No category selected)");
  }
  Rs.nResult = 0;
  Rs.vResult = 0.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/menusystem/slotselector.c:396  [anchor-strings]
struct Result_s *__cdecl SlotSelector_SetSlotTextCB(
        struct Result_s *retstr,
        void *pxUnUsed,
        struct ArgList_s *ptArgList)
{
  struct SlotSelector_s *v3; // esi
  struct ArgList_s *v4; // edi
  struct ArgList_s *v5; // edi
  struct SlotCategory_s *ptActiveCategory; // eax
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  v3 = SlotSelector_ptActiveSelector;
  v4 = ptArgList;
  if ( ptArgList->isQVM )
  {
    ptArgList = nullptr;
    QVM_EvalArg(&ptArgList, 4, v4, 1, 1);
    v5 = ptArgList;
  }
  else
  {
    v5 = (struct ArgList_s *)Expression_EvalInt(ptArgList->aptExpression[1]);
  }
  ptActiveCategory = v3->ptActiveCategory;
  if ( ptActiveCategory )
    SlotCategory_SetSlotText(ptActiveCategory, (int)v5);
  else
    MenuText_SetText(-1, "No active category");
  Rs.nResult = 0;
  Rs.vResult = 0.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/menusystem/slotselector.c:429  [anchor-mhash]
struct Result_s *__cdecl SlotSelector_isSlotEnabledCB(
        struct Result_s *retstr,
        void *pxUnUsed,
        struct ArgList_s *ptArgList)
{
  struct SlotSelector_s *v3; // esi
  struct ArgList_s *v4; // edi
  struct ArgList_s *v5; // eax
  struct SlotCategory_s *ptActiveCategory; // ecx
  int nItemID; // eax
  BOOL v8; // eax
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  v3 = SlotSelector_ptActiveSelector;
  v4 = ptArgList;
  if ( ptArgList->isQVM )
  {
    ptArgList = nullptr;
    QVM_EvalArg(&ptArgList, 4, v4, 1, 1);
    v5 = ptArgList;
  }
  else
  {
    v5 = (struct ArgList_s *)Expression_EvalInt(ptArgList->aptExpression[1]);
  }
  ptActiveCategory = v3->ptActiveCategory;
  if ( ptActiveCategory && (unsigned int)v5 <= 9 )
  {
    nItemID = ptActiveCategory->aItems[(_DWORD)v5].nItemID;
    v8 = nItemID != -1 && ptActiveCategory->pfItemEnabled(nItemID);
    ptArgList = (struct ArgList_s *)v8;
    Rs.nResult = (int)ptArgList;
    Rs.vResult = (double)(int)ptArgList;
  }
  else
  {
    Rs.vResult = 0.0;
    Rs.nResult = 0;
  }
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/menusystem/slotselector.c:466  [anchor-mhash]
struct Result_s *__cdecl SlotSelector_isSlotVisibleCB(
        struct Result_s *retstr,
        void *pxUnUsed,
        struct ArgList_s *ptArgList)
{
  struct SlotSelector_s *v3; // esi
  struct ArgList_s *v4; // edi
  struct ArgList_s *v5; // eax
  struct SlotCategory_s *ptActiveCategory; // ecx
  bool v7; // zf
  struct Result_s *result; // eax
  struct Result_s *v9; // edi
  struct Result_s Rs; // [esp+Ch] [ebp-18h] BYREF

  v3 = SlotSelector_ptActiveSelector;
  v4 = ptArgList;
  if ( ptArgList->isQVM )
  {
    ptArgList = nullptr;
    QVM_EvalArg(&ptArgList, 4, v4, 1, 1);
    v5 = ptArgList;
  }
  else
  {
    v5 = (struct ArgList_s *)Expression_EvalInt(ptArgList->aptExpression[1]);
  }
  ptActiveCategory = v3->ptActiveCategory;
  if ( ptActiveCategory && (unsigned int)v5 <= 9 )
  {
    v7 = ptActiveCategory->aItems[(_DWORD)v5].nItemID == -1;
    result = retstr;
    Rs.zResult = (char *)&g_zInitialValue;
    LODWORD(Rs.vResult) = 0;
    v9 = retstr;
    if ( !v7 )
    {
      Rs.nResult = 1;
      HIDWORD(Rs.vResult) = 1072693248;
      qmemcpy(retstr, &Rs, sizeof(struct Result_s));
      return result;
    }
  }
  else
  {
    result = retstr;
    v9 = retstr;
    Rs.zResult = (char *)&g_zInitialValue;
    LODWORD(Rs.vResult) = 0;
  }
  Rs.nResult = 0;
  HIDWORD(Rs.vResult) = 0;
  qmemcpy(v9, &Rs, sizeof(struct Result_s));
  return result;
}

// source: j/0/menusystem/slotselector.c:512  [anchor-mhash]
struct Result_s *__cdecl SlotSelector_isCategoryEmptyCB(
        struct Result_s *retstr,
        void *pxUnUsed,
        struct ArgList_s *ptArgList)
{
  struct ArgList_s *v3; // edi
  struct ArgList_s *v4; // esi
  unsigned __int16 v5; // dx
  struct QTask_s *FirstChildOfType; // eax
  int v7; // ecx
  unsigned __int16 *p_eQTaskType; // eax
  int v9; // eax
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  v3 = ptArgList;
  if ( ptArgList->isQVM )
  {
    ptArgList = nullptr;
    QVM_EvalArg(&ptArgList, 4, v3, 1, 1);
    v4 = ptArgList;
  }
  else
  {
    v4 = (struct ArgList_s *)Expression_EvalInt(ptArgList->aptExpression[1]);
  }
  v5 = SlotCategory_eQTaskType;
  FirstChildOfType = QTask_GetFirstChildOfType(&SlotSelector_ptActiveSelector->tQTask, SlotCategory_eQTaskType);
  if ( FirstChildOfType )
  {
    while ( (struct ArgList_s *)FirstChildOfType[1].ptNext != v4 )
    {
      FirstChildOfType = QTask_GetNextSiblingOfType(FirstChildOfType, v5);
      if ( !FirstChildOfType )
        goto LABEL_7;
    }
    v7 = 0;
    p_eQTaskType = &FirstChildOfType[1].eQTaskType;
    while ( *(_DWORD *)p_eQTaskType == -1 )
    {
      ++v7;
      p_eQTaskType += 2;
      if ( v7 >= 10 )
      {
        v9 = 1;
        goto LABEL_12;
      }
    }
    v9 = 0;
LABEL_12:
    ptArgList = (struct ArgList_s *)(v9 != 0);
    Rs.nResult = (int)ptArgList;
    Rs.vResult = (double)(int)ptArgList;
  }
  else
  {
LABEL_7:
    Rs.nResult = 1;
    Rs.vResult = 1.0;
  }
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/menusystem/slotselector.c:542  [anchor-mhash]
struct Result_s *__cdecl SlotSelector_isCategorySelectedCB(
        struct Result_s *retstr,
        void *pxUnUsed,
        struct ArgList_s *ptArgList)
{
  BOOL v3; // eax
  double v4; // st7
  struct Result_s Rs; // [esp+Ch] [ebp-18h] BYREF

  v3 = SlotSelector_ptActiveSelector->ptActiveCategory != nullptr;
  Rs.zResult = (char *)&g_zInitialValue;
  v4 = (double)v3;
  Rs.nResult = v3;
  Rs.vResult = v4;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/menusystem/slotselector.c:561  [anchor-mhash]
struct Result_s *__cdecl SlotSelector_isThisCategorySelectedCB(
        struct Result_s *retstr,
        void *pxUnUsed,
        struct ArgList_s *ptArgList)
{
  int v3; // eax
  struct SlotCategory_s *ptActiveCategory; // ecx
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  if ( !ptArgList || ptArgList->nArguments != 1 )
  {
    Rs.zResult = (char *)&g_zInitialValue;
    goto LABEL_6;
  }
  v3 = Script_EvalArgInt(ptArgList, 0);
  ptActiveCategory = SlotSelector_ptActiveSelector->ptActiveCategory;
  Rs.zResult = (char *)&g_zInitialValue;
  if ( !ptActiveCategory )
  {
LABEL_6:
    Rs.nResult = 0;
    Rs.vResult = 0.0;
    goto LABEL_7;
  }
  Rs.nResult = ptActiveCategory->nCategory == v3;
  Rs.vResult = (double)Rs.nResult;
LABEL_7:
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/menusystem/slotselector.c:599  [anchor-strings]
int __cdecl SlotSelector_BasicClickHandler(
        struct SlotSelector_s *ptSlotSelector,
        struct SlotCategory_s *ptSlotCategory,
        struct SlotItem_s *ptSlotSelectorItem,
        int nSlot)
{
  int result; // eax

  DebugConsole_printf("SlotSelector_BasicClickHandler(): cat=%d,slot=%d\n", ptSlotCategory->nCategory, nSlot);
  return result;
}

// source: j/0/menusystem/slotselector.c:620  [anchor-mhash]
void __cdecl SlotSelector_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *v2; // edx
  struct QTask_s *v3; // ecx

  v2 = *((struct QTask_s **)pxContext + 2);
  v3 = *(struct QTask_s **)pxContext;
  ptQTask[1].tQTaskChildren.ptHead = *((struct QTask_s **)pxContext + 1);
  ptQTask[1].ptPrev = v3;
  ptQTask[1].tQTaskChildren.ptMiddle = v2;
  SlotSelector_ptActiveSelector = (struct SlotSelector_s *)ptQTask;
  ptQTask[1].ptNext = nullptr;
}

// source: j/0/menusystem/slotselector.c:654  [anchor-mhash]
struct Result_s *__cdecl SlotSelector_ItemClicked(
        struct Result_s *retstr,
        void *pxUnUsed,
        struct ArgList_s *ptArgList)
{
  struct SlotSelector_s *v3; // esi
  struct ArgList_s *v4; // edi
  struct ArgList_s *v5; // eax
  struct SlotCategory_s *ptActiveCategory; // ecx
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  v3 = SlotSelector_ptActiveSelector;
  v4 = ptArgList;
  if ( ptArgList->isQVM )
  {
    ptArgList = nullptr;
    QVM_EvalArg(&ptArgList, 4, v4, 1, 1);
    v5 = ptArgList;
  }
  else
  {
    v5 = (struct ArgList_s *)Expression_EvalInt(ptArgList->aptExpression[1]);
  }
  if ( (unsigned int)v5 <= 9 )
  {
    ptActiveCategory = v3->ptActiveCategory;
    if ( ptActiveCategory )
    {
      if ( ptActiveCategory->aItems[(_DWORD)v5].nItemID != -1 )
        ptActiveCategory->pfItemClicked(v3, ptActiveCategory, &ptActiveCategory->aItems[(_DWORD)v5], (int)v5);
    }
  }
  SlotSelector_ptActiveSelector->ptActiveCategory = nullptr;
  Rs.nResult = 0;
  Rs.vResult = 0.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/menusystem/slotselector.c:704  [size]
void __cdecl SlotSelector_RunHandler(struct QTask_s *ptQTask)
{
  ;
}

// source: j/0/menusystem/slotselector.c:719  [size]
struct QTask_s *__cdecl SlotSelector_New(
        struct QTask_s *ptParentQTask,
        struct SlotCreateContext_s *ptCreateContext)
{
  return QTask_NewFn(ptParentQTask, SlotSelector_eQTaskType, ptCreateContext);
}

// source: j/0/menusystem/slotselector.c:733  [size]
unsigned __int16 __cdecl SlotSelector_GetQTaskType()
{
  return SlotSelector_eQTaskType;
}

// source: j/0/menusystem/slotselector.c:747  [anchor-hash]
void __cdecl SlotSelector_Close()
{
  QTask_DeleteQTaskType(SlotSelector_eQTaskType);
  Symbol_Remove("SlotSelector_SetSlotText");
  Symbol_Remove("SlotSelector_SetSlotCategoryName");
  Symbol_Remove("SlotSelector_isSlotEnabled");
  Symbol_Remove("SlotSelector_isSlotVisible");
  Symbol_Remove("SlotSelector_isCategorySelected");
  Symbol_Remove("SlotSelector_isThisCategorySelected");
  Symbol_Remove("SlotSelector_isCategoryEmpty");
  Symbol_Remove("SlotSelector_SetActiveCategory");
  Symbol_Remove("SlotSelector_ItemClicked");
  Symbol_Remove("SlotSelector_Deactivate");
}

// source: j/0/menusystem/slotselector.c:771  [anchor-hash]
void __cdecl SlotSelector_Open()
{
  unsigned __int16 BaseQTaskType; // ax
  unsigned __int16 v1; // si

  BaseQTaskType = QTask_GetBaseQTaskType();
  v1 = QTask_NewQTaskType("SlotSelector", 56, BaseQTaskType, 0, 0);
  SlotSelector_eQTaskType = v1;
  QTask_LinkQTaskEventHandlerFn(v1, 0, SlotSelector_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 1, (void (__cdecl *)(struct QTask_s *))SlotSelector_RunHandler);
  Symbol_Register(
    "SlotSelector_SetSlotText",
    SlotSelector_SetSlotTextCB,
    nullptr,
    2,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "SlotSelector_SetSlotCategoryName",
    SlotSelector_SetSlotCategoryNameCB,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "SlotSelector_isSlotEnabled",
    SlotSelector_isSlotEnabledCB,
    nullptr,
    2,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "SlotSelector_isSlotVisible",
    SlotSelector_isSlotVisibleCB,
    nullptr,
    2,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "SlotSelector_isCategorySelected",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))SlotSelector_isCategorySelectedCB,
    nullptr,
    2,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "SlotSelector_isThisCategorySelected",
    SlotSelector_isThisCategorySelectedCB,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "SlotSelector_isCategoryEmpty",
    SlotSelector_isCategoryEmptyCB,
    nullptr,
    2,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "SlotSelector_SetActiveCategory",
    SlotSelector_SetActiveCategoryCB,
    nullptr,
    2,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "SlotSelector_ItemClicked",
    SlotSelector_ItemClicked,
    nullptr,
    2,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "SlotSelector_Deactivate",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))SlotSelector_DeactiveateCategoryCB,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
}
