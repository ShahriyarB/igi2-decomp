/* h/2/tagitem.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: h/2/tagitem.c:54  [size]
struct TagItem_s *__cdecl TagItem_Init(struct TagItem_s *ptTagItem, int eParameterType)
{
  ptTagItem->eParameterType = eParameterType;
  ptTagItem->zName[0] = 0;
  return ptTagItem;
}

// source: h/2/tagitem.c:72  [size]
void __cdecl TagItem_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ;
}

// source: h/2/tagitem.c:84  [size]
void __cdecl TagItem_DeleteHandler(struct QTask_s *ptQTask)
{
  ;
}

// source: h/2/tagitem.c:96  [size]
void __cdecl TagItem_RunHandler(struct QTask_s *ptQTask)
{
  ;
}

// source: h/2/tagitem.c:108  [anchor-mhash]
void __cdecl TagItem_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *ptParent; // eax
  void (__cdecl *pfHandler)(struct QTask_s *, struct QTask_s *); // ecx

  if ( !pxContext || !*(_DWORD *)pxContext )
  {
    ptParent = ptQTask->ptParent;
    if ( ptParent )
    {
      pfHandler = (void (__cdecl *)(struct QTask_s *, struct QTask_s *))QTask_aatQTaskFinalEvent[TagItem_eUpdateTagItemQTaskEvent][ptParent->eQTaskType].pfHandler;
      if ( pfHandler )
        pfHandler(ptParent, ptQTask);
    }
  }
}

// source: h/2/tagitem.c:137  [anchor-mhash]
void __cdecl TagItem_UpdateInternalDataAfterLoadHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptParent; // eax
  void (__cdecl *pfHandler)(struct QTask_s *, struct QTask_s *); // ecx

  ptParent = ptQTask->ptParent;
  if ( ptParent )
  {
    pfHandler = (void (__cdecl *)(struct QTask_s *, struct QTask_s *))QTask_aatQTaskFinalEvent[TagItem_eUpdateTagItemQTaskEvent][ptParent->eQTaskType].pfHandler;
    if ( pfHandler )
      pfHandler(ptParent, ptQTask);
  }
}

// source: h/2/tagitem.c:178  [size]
void __cdecl TagItem_Int32CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ptQTask[7].tQTaskChildren.ptTail = (struct QTask_s *)Level_eParameterTypeInt32;
  LOBYTE(ptQTask[1].ptNext) = 0;
  ptQTask[7].tQTaskRefList.ptHead = nullptr;
}

// source: h/2/tagitem.c:201  [size]
void __cdecl TagItem_Int32DeleteHandler(struct QTask_s *ptQTask)
{
  ;
}

// source: h/2/tagitem.c:224  [size]
void __cdecl TagItem_Int32GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = TagItem_ptInt32ParameterList;
}

// source: h/2/tagitem.c:252  [size]
void __cdecl TagItem_Real32CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ptQTask[7].tQTaskChildren.ptTail = (struct QTask_s *)Level_eParameterTypeReal32;
  LOBYTE(ptQTask[1].ptNext) = 0;
  ptQTask[7].tQTaskRefList.ptHead = nullptr;
}

// source: h/2/tagitem.c:274  [size]
void __cdecl TagItem_Real32DeleteHandler(struct QTask_s *ptQTask)
{
  ;
}

// source: h/2/tagitem.c:297  [size]
void __cdecl TagItem_Real32GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = TagItem_ptReal32ParameterList;
}

// source: h/2/tagitem.c:325  [size]
void __cdecl TagItem_String16CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ptQTask[7].tQTaskChildren.ptTail = (struct QTask_s *)Level_eParameterTypeString16;
  LOBYTE(ptQTask[1].ptNext) = 0;
  LOBYTE(ptQTask[7].tQTaskRefList.ptHead) = 0;
}

// source: h/2/tagitem.c:342  [size]
void __cdecl TagItem_String16GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = TagItem_ptString16ParameterList;
}

// source: h/2/tagitem.c:358  [size]
void __cdecl TagItem_String256CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ptQTask[7].tQTaskChildren.ptTail = (struct QTask_s *)Level_eParameterTypeString256;
  LOBYTE(ptQTask[1].ptNext) = 0;
  LOBYTE(ptQTask[7].tQTaskRefList.ptHead) = 0;
}

// source: h/2/tagitem.c:375  [size]
void __cdecl TagItem_String256GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = TagItem_ptString256ParameterList;
}

// source: h/2/tagitem.c:391  [size]
void __cdecl TagItem_Bool8CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ptQTask[7].tQTaskChildren.ptTail = (struct QTask_s *)Level_eParameterTypebool8;
  LOBYTE(ptQTask[1].ptNext) = 0;
  LOBYTE(ptQTask[7].tQTaskRefList.ptHead) = 0;
}

// source: h/2/tagitem.c:408  [size]
void __cdecl TagItem_Bool8GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = TagItem_ptBool8ParameterList;
}

// source: h/2/tagitem.c:424  [size]
void __cdecl TagItem_PushButtonCreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ptQTask[7].tQTaskChildren.ptTail = (struct QTask_s *)Level_eParameterTypePushButton;
  LOBYTE(ptQTask[1].ptNext) = 0;
  LOBYTE(ptQTask[7].tQTaskRefList.ptHead) = 0;
}

// source: h/2/tagitem.c:441  [size]
void __cdecl TagItem_PushButtonGetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = TagItem_ptPushButtonParameterList;
}

// source: h/2/tagitem.c:461  [anchor-callee]
struct QTask_s *__cdecl TagItem_NewInt32(
        struct QTask_s *ptParent,
        char *zName,
        int nInitialValue)
{
  struct QTask_s *result; // eax

  result = QTask_NewFn(ptParent, TagItem_eInt32QTaskType, nullptr);
  strcpy((char *)&result[1], zName);
  result[7].tQTaskRefList.ptHead = (struct QReference_s *)nInitialValue;
  return result;
}

// source: h/2/tagitem.c:489  [anchor-callee]
struct QTask_s *__cdecl TagItem_NewInt32MinMax(
        struct QTask_s *ptParent,
        char *zName,
        int nInitialValue,
        int nMin,
        int nMax)
{
  struct QTask_s *result; // eax

  result = QTask_NewFn(ptParent, TagItem_eInt32QTaskType, nullptr);
  strcpy((char *)&result[1], zName);
  result[7].tQTaskRefList.ptHead = (struct QReference_s *)nInitialValue;
  return result;
}

// source: h/2/tagitem.c:512  [anchor-callee]
struct QTask_s *__cdecl TagItem_NewInt32EnumList(
        struct QTask_s *ptParent,
        char *zName,
        int nInitialValue,
        void *pxContext)
{
  struct QTask_s *result; // eax

  result = QTask_NewFn(ptParent, TagItem_eInt32QTaskType, nullptr);
  strcpy((char *)&result[1], zName);
  result[7].tQTaskRefList.ptHead = (struct QReference_s *)nInitialValue;
  return result;
}

// source: h/2/tagitem.c:535  [anchor-callee]
struct QTask_s *__cdecl TagItem_NewReal32(
        struct QTask_s *ptParent,
        char *zName,
        float vInitialValue)
{
  struct QTask_s *result; // eax

  result = QTask_NewFn(ptParent, TagItem_eReal32QTaskType, nullptr);
  strcpy((char *)&result[1], zName);
  *(float *)&result[7].tQTaskRefList.ptHead = vInitialValue;
  return result;
}

// source: h/2/tagitem.c:563  [anchor-callee]
struct QTask_s *__cdecl TagItem_NewReal32MinMax(
        struct QTask_s *ptParent,
        char *zName,
        float vInitialValue,
        float vMin,
        float vMax)
{
  struct QTask_s *result; // eax

  result = QTask_NewFn(ptParent, TagItem_eReal32QTaskType, nullptr);
  strcpy((char *)&result[1], zName);
  *(float *)&result[7].tQTaskRefList.ptHead = vInitialValue;
  return result;
}

// source: h/2/tagitem.c:586  [anchor-callee]
struct QTask_s *__cdecl TagItem_NewReal32EnumList(
        struct QTask_s *ptParent,
        char *zName,
        float vInitialValue,
        void *pxContext)
{
  struct QTask_s *result; // eax

  result = QTask_NewFn(ptParent, TagItem_eReal32QTaskType, nullptr);
  strcpy((char *)&result[1], zName);
  *(float *)&result[7].tQTaskRefList.ptHead = vInitialValue;
  return result;
}

// source: h/2/tagitem.c:609  [anchor-callee]
struct QTask_s *__cdecl TagItem_NewString16(
        struct QTask_s *ptParent,
        char *zName,
        char *zInitialValue)
{
  struct QTask_s *result; // eax

  result = QTask_NewFn(ptParent, TagItem_eString16QTaskType, nullptr);
  strcpy((char *)&result[1], zName);
  strcpy((char *)&result[7].tQTaskRefList, zInitialValue);
  return result;
}

// source: h/2/tagitem.c:636  [anchor-callee]
struct QTask_s *__cdecl TagItem_NewString256(
        struct QTask_s *ptParent,
        char *zName,
        char *zInitialValue)
{
  struct QTask_s *result; // eax

  result = QTask_NewFn(ptParent, TagItem_eString256QTaskType, nullptr);
  strcpy((char *)&result[1], zName);
  strcpy((char *)&result[7].tQTaskRefList, zInitialValue);
  return result;
}

// source: h/2/tagitem.c:663  [anchor-callee]
struct QTask_s *__cdecl TagItem_NewBool8(
        struct QTask_s *ptParent,
        char *zName,
        enum bool isInitialValue)
{
  struct QTask_s *result; // eax

  result = QTask_NewFn(ptParent, TagItem_eBool8QTaskType, nullptr);
  LOBYTE(result[7].tQTaskRefList.ptHead) = isInitialValue;
  strcpy((char *)&result[1], zName);
  return result;
}

// source: h/2/tagitem.c:689  [anchor-mhash]
struct QTask_s *__cdecl TagItem_NewPushButton(struct QTask_s *ptParent, char *zName)
{
  struct QTask_s *result; // eax

  result = QTask_NewFn(ptParent, TagItem_ePushButtonQTaskType, nullptr);
  LOBYTE(result[7].tQTaskRefList.ptHead) = 0;
  strcpy((char *)&result[1], zName);
  return result;
}

// source: h/2/tagitem.c:727  [anchor-caller]
int __cdecl TagItem_FindInt32Value(
        struct QTask_s *ptParent,
        char *zName,
        enum bool isCreate,
        int nInitialValue,
        enum bool isMinMax,
        int nMin,
        int nMax)
{
  struct QTask_s *v9; // eax

  v9 = TagItem_Find(ptParent, zName);
  if ( v9 )
    return (int)v9[7].tQTaskRefList.ptHead;
  if ( isCreate
    && (isMinMax == false
      ? (v9 = TagItem_NewInt32(ptParent, zName, nInitialValue))
      : (v9 = TagItem_NewInt32MinMax(ptParent, zName, nInitialValue, nMin, nMax)),
        v9) )
  {
    return (int)v9[7].tQTaskRefList.ptHead;
  }
  else
  {
    return 0;
  }
}

// source: h/2/tagitem.c:764  [anchor-caller]
float __cdecl TagItem_FindReal32Value(
        struct QTask_s *ptParent,
        char *zName,
        enum bool isCreate,
        float vInitialValue,
        enum bool isMinMax,
        float vMin,
        float vMax)
{
  struct QTask_s *v9; // eax

  v9 = TagItem_Find(ptParent, zName);
  if ( v9 )
    return *(float *)&v9[7].tQTaskRefList.ptHead;
  if ( isCreate
    && (isMinMax == false
      ? (v9 = TagItem_NewReal32(ptParent, zName, vInitialValue))
      : (v9 = TagItem_NewReal32MinMax(ptParent, zName, vInitialValue, vMin, vMax)),
        v9) )
  {
    return *(float *)&v9[7].tQTaskRefList.ptHead;
  }
  else
  {
    return 0.0;
  }
}

// source: h/2/tagitem.c:798  [anchor-caller]
char *__cdecl TagItem_FindString16Value(
        struct QTask_s *ptParent,
        char *zName,
        enum bool isCreate,
        char *zInitialValue)
{
  struct QTask_s *v6; // eax

  v6 = TagItem_Find(ptParent, zName);
  if ( v6 )
    return (char *)&v6[7].tQTaskRefList;
  if ( isCreate && (v6 = TagItem_NewString16(ptParent, zName, zInitialValue)) != nullptr )
    return (char *)&v6[7].tQTaskRefList;
  else
    return (char *)&g_zInitialValue;
}

// source: h/2/tagitem.c:832  [anchor-caller]
char *__cdecl TagItem_FindString256Value(
        struct QTask_s *ptParent,
        char *zName,
        enum bool isCreate,
        char *zInitialValue)
{
  struct QTask_s *v6; // eax

  v6 = TagItem_Find(ptParent, zName);
  if ( v6 )
    return (char *)&v6[7].tQTaskRefList;
  if ( isCreate && (v6 = TagItem_NewString256(ptParent, zName, zInitialValue)) != nullptr )
    return (char *)&v6[7].tQTaskRefList;
  else
    return (char *)&g_zInitialValue;
}

// source: h/2/tagitem.c:862  [anchor-mhash]
int __cdecl TagItem_FindInt32EnumListValue(
        struct QTask_s *ptParent,
        char *zName,
        enum bool isCreate,
        int nInitialValue,
        void *pxContext)
{
  struct QTask_s *v7; // eax

  v7 = TagItem_Find(ptParent, zName);
  if ( v7 )
    return (int)v7[7].tQTaskRefList.ptHead;
  if ( isCreate && (v7 = TagItem_NewInt32EnumList(ptParent, zName, nInitialValue, pxContext)) != nullptr )
    return (int)v7[7].tQTaskRefList.ptHead;
  else
    return 0;
}

// source: h/2/tagitem.c:892  [anchor-mhash]
float __cdecl TagItem_FindReal32EnumListValue(
        struct QTask_s *ptParent,
        char *zName,
        enum bool isCreate,
        float vInitialValue,
        void *pxContext)
{
  struct QTask_s *v7; // eax

  v7 = TagItem_Find(ptParent, zName);
  if ( v7 )
    return *(float *)&v7[7].tQTaskRefList.ptHead;
  if ( isCreate && (v7 = TagItem_NewReal32EnumList(ptParent, zName, vInitialValue, pxContext)) != nullptr )
    return *(float *)&v7[7].tQTaskRefList.ptHead;
  else
    return 0.0;
}

// source: h/2/tagitem.c:922  [anchor-caller]
enum bool __cdecl TagItem_FindBool8Value(
        struct QTask_s *ptParent,
        char *zName,
        enum bool isCreate,
        enum bool isInitialValue)
{
  struct QTask_s *v6; // eax

  v6 = TagItem_Find(ptParent, zName);
  if ( v6 )
    return SLOBYTE(v6[7].tQTaskRefList.ptHead);
  if ( isCreate && (v6 = TagItem_NewBool8(ptParent, zName, isInitialValue)) != nullptr )
    return SLOBYTE(v6[7].tQTaskRefList.ptHead);
  else
    return false;
}

// source: h/2/tagitem.c:952  [anchor-mhash]
enum bool __cdecl TagItem_FindPushButtonValue(
        struct QTask_s *ptParent,
        char *zName,
        enum bool isCreate)
{
  if ( !TagItem_Find(ptParent, zName) && isCreate )
    TagItem_NewPushButton(ptParent, zName);
  return false;
}

// source: h/2/tagitem.c:975  [anchor-hash]
struct QTask_s *__cdecl TagItem_FindFirst(struct QTask_s *ptParent)
{
  struct QTask_s *ptHead; // edx
  unsigned __int16 v2; // cx

  ptHead = ptParent->tQTaskChildren.ptHead;
  if ( !ptHead->ptNext || !ptHead )
    return nullptr;
  v2 = TagItem_eQTaskType;
  while ( QTask_IsQTaskTypeDerived(ptHead->eQTaskType, v2) == false )
  {
    ptHead = ptHead->ptNext;
    if ( !ptHead || !ptHead->ptNext )
      return nullptr;
  }
  return ptHead;
}

// source: h/2/tagitem.c:1002  [anchor-mhash]
struct QTask_s *__cdecl TagItem_FindNext(struct QTask_s *ptQTask)
{
  unsigned __int16 v1; // cx

  if ( !ptQTask )
    return nullptr;
  v1 = TagItem_eQTaskType;
  while ( QTask_IsQTaskTypeDerived(ptQTask->eQTaskType, v1) == false )
  {
    ptQTask = ptQTask->ptNext;
    if ( !ptQTask || !ptQTask->ptNext )
      return nullptr;
  }
  return ptQTask;
}

// source: h/2/tagitem.c:1025  [anchor-callee]
struct QTask_s *__cdecl TagItem_Find(struct QTask_s *ptParent, char *zName)
{
  struct QTask_s *ptHead; // eax
  struct QTask_s *v3; // edi
  unsigned __int16 v4; // cx
  struct QTask_s *ptNext; // eax

  ptHead = ptParent->tQTaskChildren.ptHead;
  if ( !ptHead->ptNext )
    return nullptr;
  v3 = ptHead;
  if ( !ptHead )
    return nullptr;
  v4 = TagItem_eQTaskType;
  while ( QTask_IsQTaskTypeDerived(v3->eQTaskType, v4) == false || strcmp((char *)&v3[1], zName) )
  {
    ptNext = v3->ptNext;
    if ( v3->ptNext )
    {
      if ( ptNext->ptNext )
      {
        v3 = v3->ptNext;
        if ( ptNext )
          continue;
      }
    }
    return nullptr;
  }
  return v3;
}

// source: h/2/tagitem.c:1059  [anchor-hash]
struct QTask_s *__cdecl TagItem_DeleteAll(struct QTask_s *ptParent)
{
  struct QTask_s *ptHead; // edx
  struct QTask_s *v2; // esi

  ptHead = ptParent->tQTaskChildren.ptHead;
  if ( ptHead->ptNext && ptHead )
  {
    do
    {
      if ( ptHead->ptNext )
        v2 = ptHead->ptNext->ptNext != nullptr ? ptHead->ptNext : nullptr;
      else
        v2 = nullptr;
      ptParent = (struct QTask_s *)QTask_IsQTaskTypeDerived(ptHead->eQTaskType, TagItem_eQTaskType);
      if ( ptParent )
        QTask_Delete(ptHead);
      ptHead = v2;
    }
    while ( v2 );
  }
  return ptParent;
}

// source: h/2/tagitem.c:1088  [size]
__int16 __cdecl TagItem_GetUpdateTagItemQTaskEvent()
{
  return TagItem_eUpdateTagItemQTaskEvent;
}

// source: h/2/tagitem.c:1101  [anchor-hash]
void __cdecl TagItem_Open()
{
  unsigned __int16 BaseQTaskType; // ax
  unsigned __int16 v1; // si
  struct ParameterList_s *v2; // eax
  int v3; // edx
  unsigned __int16 v4; // si
  unsigned __int16 v5; // si
  unsigned __int16 v6; // si
  unsigned __int16 v7; // si
  unsigned __int16 v8; // si
  unsigned __int16 v9; // si

  TagItem_eUpdateTagItemQTaskEvent = QTask_NewQTaskEventFn(0, "UpdateTagItem");
  BaseQTaskType = QTask_GetBaseQTaskType();
  v1 = QTask_NewQTaskType("TagItem", 300, BaseQTaskType, 0, 0);
  TagItem_eQTaskType = v1;
  QTask_LinkQTaskEventHandlerFn(v1, 0, (void (__cdecl *)(struct QTask_s *, void *))TagItem_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 1, (void (__cdecl *)(struct QTask_s *))TagItem_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 2, (void (__cdecl *)(struct QTask_s *))TagItem_DeleteHandler);
  QTask_LinkQTaskEventHandlerFn(v1, ParameterList_eUpdateInternalDataQTaskEvent, TagItem_UpdateInternalDataHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(
    v1,
    Level_eUpdateInternalDataAfterLoadEvent,
    TagItem_UpdateInternalDataAfterLoadHandler);
  QTask_LinkQTaskEventHandlerFn(
    v1,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveHandler);
  v2 = (struct ParameterList_s *)Mem_AllocFn(32, 4);
  v2->ptParameterListItem = (struct ParameterListItem_s *)&v2[1];
  v3 = Level_eParameterTypeString256;
  v2->nParameters = 0;
  v2->nMaxParameters = 1;
  TagItem_ptParameterList = v2;
  ParameterList_AddParameter(v2, 0x28u, v3, "Name", 7u, nullptr);
  v4 = QTask_NewQTaskType("TagItemInt32", 304, TagItem_eQTaskType, 0, 0);
  TagItem_eInt32QTaskType = v4;
  QTask_LinkQTaskEventHandlerFn(v4, 0, (void (__cdecl *)(struct QTask_s *, void *))TagItem_Int32CreateHandler);
  QTask_LinkQTaskEventHandlerFn(
    v4,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))TagItem_Int32GetParameterListHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v4, 2, (void (__cdecl *)(struct QTask_s *))TagItem_Int32DeleteHandler);
  TagItem_ptInt32ParameterList = ParameterList_Derive(TagItem_ptParameterList, 2);
  ParameterList_AddParameter(TagItem_ptInt32ParameterList, 0x12Cu, Level_eParameterTypeInt32, "Value", 7u, nullptr);
  v5 = QTask_NewQTaskType("TagItemReal32", 304, TagItem_eQTaskType, 0, 0);
  TagItem_eReal32QTaskType = v5;
  QTask_LinkQTaskEventHandlerFn(v5, 0, (void (__cdecl *)(struct QTask_s *, void *))TagItem_Real32CreateHandler);
  QTask_LinkQTaskEventHandlerFn(
    v5,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))TagItem_Real32GetParameterListHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v5, 2, (void (__cdecl *)(struct QTask_s *))TagItem_Real32DeleteHandler);
  TagItem_ptReal32ParameterList = ParameterList_Derive(TagItem_ptParameterList, 2);
  ParameterList_AddParameter(TagItem_ptReal32ParameterList, 0x12Cu, Level_eParameterTypeReal32, "Value", 7u, nullptr);
  v6 = QTask_NewQTaskType("TagItemString16", 316, TagItem_eQTaskType, 0, 0);
  TagItem_eString16QTaskType = v6;
  QTask_LinkQTaskEventHandlerFn(v6, 0, (void (__cdecl *)(struct QTask_s *, void *))TagItem_String16CreateHandler);
  QTask_LinkQTaskEventHandlerFn(
    v6,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))TagItem_String16GetParameterListHandler);
  TagItem_ptString16ParameterList = ParameterList_Derive(TagItem_ptParameterList, 2);
  ParameterList_AddParameter(
    TagItem_ptString16ParameterList,
    0x12Cu,
    Level_eParameterTypeString16,
    "Value",
    7u,
    nullptr);
  v7 = QTask_NewQTaskType("TagItemString256", 556, TagItem_eQTaskType, 0, 0);
  TagItem_eString256QTaskType = v7;
  QTask_LinkQTaskEventHandlerFn(v7, 0, (void (__cdecl *)(struct QTask_s *, void *))TagItem_String256CreateHandler);
  QTask_LinkQTaskEventHandlerFn(
    v7,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))TagItem_String256GetParameterListHandler);
  TagItem_ptString256ParameterList = ParameterList_Derive(TagItem_ptParameterList, 2);
  ParameterList_AddParameter(
    TagItem_ptString256ParameterList,
    0x12Cu,
    Level_eParameterTypeString256,
    "Value",
    7u,
    nullptr);
  v8 = QTask_NewQTaskType("TagItemBool8", 304, TagItem_eQTaskType, 0, 0);
  TagItem_eBool8QTaskType = v8;
  QTask_LinkQTaskEventHandlerFn(v8, 0, (void (__cdecl *)(struct QTask_s *, void *))TagItem_Bool8CreateHandler);
  QTask_LinkQTaskEventHandlerFn(
    v8,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))TagItem_Bool8GetParameterListHandler);
  TagItem_ptBool8ParameterList = ParameterList_Derive(TagItem_ptParameterList, 2);
  ParameterList_AddParameter(TagItem_ptBool8ParameterList, 0x12Cu, Level_eParameterTypebool8, "Value", 7u, nullptr);
  v9 = QTask_NewQTaskType("TagItemPushButton", 304, TagItem_eQTaskType, 0, 0);
  TagItem_ePushButtonQTaskType = v9;
  QTask_LinkQTaskEventHandlerFn(v9, 0, (void (__cdecl *)(struct QTask_s *, void *))TagItem_PushButtonCreateHandler);
  QTask_LinkQTaskEventHandlerFn(
    v9,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))TagItem_PushButtonGetParameterListHandler);
  TagItem_ptPushButtonParameterList = ParameterList_Derive(TagItem_ptParameterList, 2);
  ParameterList_AddParameter(
    TagItem_ptPushButtonParameterList,
    0x12Cu,
    Level_eParameterTypePushButton,
    "Do it!",
    7u,
    nullptr);
}

// source: h/2/tagitem.c:1172  [anchor-hash]
void __cdecl TagItem_Close()
{
  int v0; // esi
  int v1; // esi
  int v2; // esi
  int v3; // esi
  int v4; // esi
  int v5; // esi
  int v6; // esi

  if ( TagItem_ptPushButtonParameterList )
  {
    v0 = *(_DWORD *)((unsigned int)&TagItem_ptPushButtonParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
  if ( TagItem_ptBool8ParameterList )
  {
    v1 = *(_DWORD *)((unsigned int)&TagItem_ptBool8ParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v1);
    memset(*(void **)(v1 + 8), 0xCDu, *(_DWORD *)(v1 + 16));
    free((void *)v1);
  }
  if ( TagItem_ptString256ParameterList )
  {
    v2 = *(_DWORD *)((unsigned int)&TagItem_ptString256ParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v2);
    memset(*(void **)(v2 + 8), 0xCDu, *(_DWORD *)(v2 + 16));
    free((void *)v2);
  }
  if ( TagItem_ptString16ParameterList )
  {
    v3 = *(_DWORD *)((unsigned int)&TagItem_ptString16ParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v3);
    memset(*(void **)(v3 + 8), 0xCDu, *(_DWORD *)(v3 + 16));
    free((void *)v3);
  }
  if ( TagItem_ptReal32ParameterList )
  {
    v4 = *(_DWORD *)((unsigned int)&TagItem_ptReal32ParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v4);
    memset(*(void **)(v4 + 8), 0xCDu, *(_DWORD *)(v4 + 16));
    free((void *)v4);
  }
  if ( TagItem_ptInt32ParameterList )
  {
    v5 = *(_DWORD *)((unsigned int)&TagItem_ptInt32ParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v5);
    memset(*(void **)(v5 + 8), 0xCDu, *(_DWORD *)(v5 + 16));
    free((void *)v5);
  }
  if ( TagItem_ptParameterList )
  {
    v6 = *(_DWORD *)((unsigned int)&TagItem_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v6);
    memset(*(void **)(v6 + 8), 0xCDu, *(_DWORD *)(v6 + 16));
    free((void *)v6);
  }
  QTask_DeleteQTaskType(TagItem_eQTaskType);
  QTask_DeleteQTaskType(TagItem_eInt32QTaskType);
  QTask_DeleteQTaskType(TagItem_eReal32QTaskType);
  QTask_DeleteQTaskType(TagItem_eString16QTaskType);
  QTask_DeleteQTaskType(TagItem_eString256QTaskType);
  QTask_DeleteQTaskType(TagItem_eBool8QTaskType);
  QTask_DeleteQTaskType(TagItem_ePushButtonQTaskType);
  QTask_DeleteQTaskEvent(TagItem_eUpdateTagItemQTaskEvent);
}
