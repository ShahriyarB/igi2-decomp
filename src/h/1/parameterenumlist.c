/* h/1/parameterenumlist.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: h/1/parameterenumlist.c:63  [anchor-mhash]
int __cdecl ParameterEnumList_IsString(int eParameterType)
{
  int eParentParameterType; // ecx
  int v2; // ecx
  int v3; // ecx
  int result; // eax

  eParentParameterType = eParameterType;
  while ( eParentParameterType != Level_eParameterTypeString16 )
  {
    eParentParameterType = ParameterList_atParameterType[eParentParameterType].eParentParameterType;
    if ( eParentParameterType == -1 )
    {
      v2 = eParameterType;
      while ( v2 != Level_eParameterTypeString32 )
      {
        v2 = ParameterList_atParameterType[v2].eParentParameterType;
        if ( v2 == -1 )
        {
          v3 = eParameterType;
          while ( v3 != Level_eParameterTypeString256 )
          {
            v3 = ParameterList_atParameterType[v3].eParentParameterType;
            if ( v3 == -1 )
            {
              result = ParameterList_IsParameterTypeDerived(eParameterType, Level_eParameterTypeVarString);
              if ( !result )
                return result;
              return 1;
            }
          }
          return 1;
        }
      }
      return 1;
    }
  }
  return 1;
}

// source: h/1/parameterenumlist.c:79  [anchor-mhash]
void __cdecl ParameterEnumList_EnumCallback(
        struct ParameterEnumListEnumItemsContext_s *ptEnumContext,
        struct ParameterEnumListParseItemsContext_s *ptParseItemContext)
{
  struct EnumListSymbolEnumContext_s *pxContext; // ebx
  int v3; // ebp
  int eParameterType; // edx
  int v5; // esi
  int eParentParameterType; // edx
  struct ParameterEnumListParseItemsContext_s *v7; // edi
  int v8; // edx
  int v9; // edx
  double v10; // st7
  int v11; // ecx
  bool v12; // zf
  struct EnumListSymbolEnumContext_s *ptContext; // [esp+4h] [ebp-Ch]

  pxContext = (struct EnumListSymbolEnumContext_s *)ptEnumContext->pxContext;
  ptContext = pxContext;
  if ( !pxContext->isMatch )
  {
    v3 = 0;
    eParameterType = pxContext->eParameterType;
    while ( eParameterType != Level_eParameterTypeInt32 )
    {
      eParameterType = ParameterList_atParameterType[eParameterType].eParentParameterType;
      if ( eParameterType == -1 )
      {
        v5 = Level_eParameterTypeReal32;
        eParentParameterType = pxContext->eParameterType;
        while ( eParentParameterType != Level_eParameterTypeReal32 )
        {
          eParentParameterType = ParameterList_atParameterType[eParentParameterType].eParentParameterType;
          if ( eParentParameterType == -1 )
          {
            if ( !ParameterEnumList_IsString(pxContext->eParameterType) )
              return;
            v7 = ptParseItemContext;
            v11 = 0;
            v12 = strcmp(ptParseItemContext->zName, pxContext->zValue) == 0;
            v3 = 1;
            goto LABEL_24;
          }
        }
        v7 = ptParseItemContext;
        v9 = ptParseItemContext->eParameterType;
        if ( ParameterList_IsParameterTypeDerived(ptParseItemContext->eParameterType, Level_eParameterTypeInt32) )
        {
          v10 = (double)*(int *)ptParseItemContext->pxData;
        }
        else if ( ParameterList_IsParameterTypeDerived(v9, v5) )
        {
          v10 = *(float *)ptParseItemContext->pxData;
        }
        else
        {
          v10 = *(float *)&ptEnumContext;
        }
        if ( v10 != pxContext->vValue )
          return;
LABEL_25:
        if ( ParameterEnumList_GetItem(ptEnumContext->ptParameterEnumItemList, v7->zName) )
        {
          if ( v3 )
            sprintf(
              ptContext->zBuffer,
              (char *const)&stru_6A4CDC.tDebugConsoleLineList.ptMiddle,
              ptContext->zValue);
          else
            sprintf(ptContext->zBuffer, (char *const)&stru_6A4CDC.tDebugConsoleLineList.ptMiddle, v7->zName);
          ptContext->isMatch = 1;
        }
        return;
      }
    }
    v7 = ptParseItemContext;
    v8 = ptParseItemContext->eParameterType;
    do
    {
      if ( v8 == Level_eParameterTypeInt32 )
      {
        v11 = 0;
        v12 = *(_DWORD *)ptParseItemContext->pxData == pxContext->nValue;
        goto LABEL_24;
      }
      v8 = ParameterList_atParameterType[v8].eParentParameterType;
    }
    while ( v8 != -1 );
    v11 = 0;
    if ( ParameterList_IsParameterTypeDerived(ptParseItemContext->eParameterType, Level_eParameterTypeReal32) )
      v12 = (__int64)*(float *)ptParseItemContext->pxData == pxContext->nValue;
    else
      v12 = ptEnumContext == (struct ParameterEnumListEnumItemsContext_s *)pxContext->nValue;
LABEL_24:
    LOBYTE(v11) = v12;
    if ( v11 )
      goto LABEL_25;
  }
}

// source: h/1/parameterenumlist.c:176  [anchor-callee]
struct ParameterEnumItemList_s *__cdecl ParameterEnumList_PrintValueInt(
        struct ParameterEnumItemList_s *ptParameterEnumList,
        int nValue,
        char *zBuffer)
{
  #pragma pack(push, 1)
  union
  {
    struct { _DWORD v5[3]; };
    struct { char igi2_o1[12]; struct EnumListSymbolEnumContext_s tContext; };
    char igi2_extent[40];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  void (__cdecl *pfEnumItemsCallback)(struct ParameterEnumListEnumItemsContext_s *); // ecx
  struct ParameterEnumItemList_s *result; // eax

  if ( !ptParameterEnumList )
    return (struct ParameterEnumItemList_s *)sprintf(
                                               zBuffer,
                                               (char *const)&g_ptNetManager.tReceiveCounters.tCounters[9].nBytes,
                                               nValue);
  igi2_frame.tContext.eParameterType = Level_eParameterTypeInt32;
  pfEnumItemsCallback = ptParameterEnumList->pfEnumItemsCallback;
  igi2_frame.tContext.isMatch = 0;
  igi2_frame.tContext.ptParameterEnumList = ptParameterEnumList;
  igi2_frame.tContext.zBuffer = zBuffer;
  igi2_frame.tContext.nValue = nValue;
  igi2_frame.tContext.vValue = 0.0;
  igi2_frame.tContext.zValue = (char *)&g_zInitialValue;
  if ( !pfEnumItemsCallback )
    return (struct ParameterEnumItemList_s *)sprintf(
                                               zBuffer,
                                               (char *const)&g_ptNetManager.tReceiveCounters.tCounters[9].nBytes,
                                               nValue);
  igi2_frame.v5[0] = ptParameterEnumList;
  igi2_frame.v5[1] = ParameterEnumList_EnumCallback;
  igi2_frame.v5[2] = &igi2_frame.tContext;
  pfEnumItemsCallback((struct ParameterEnumListEnumItemsContext_s *)igi2_frame.v5);
  result = (struct ParameterEnumItemList_s *)igi2_frame.tContext.isMatch;
  if ( !igi2_frame.tContext.isMatch )
    return (struct ParameterEnumItemList_s *)sprintf(
                                               zBuffer,
                                               (char *const)&g_ptNetManager.tReceiveCounters.tCounters[9].nBytes,
                                               nValue);
  return result;
}

// source: h/1/parameterenumlist.c:207  [anchor-mhash]
struct ParameterEnumItemList_s *__cdecl ParameterEnumList_PrintValueReal(
        struct ParameterEnumItemList_s *ptParameterEnumList,
        float vValue,
        char *zBuffer)
{
  #pragma pack(push, 1)
  union
  {
    struct { _DWORD v5[3]; };
    struct { char igi2_o1[12]; struct EnumListSymbolEnumContext_s tContext; };
    char igi2_extent[40];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  void (__cdecl *pfEnumItemsCallback)(struct ParameterEnumListEnumItemsContext_s *); // ecx
  struct ParameterEnumItemList_s *result; // eax

  if ( !ptParameterEnumList )
    return (struct ParameterEnumItemList_s *)sprintf(zBuffer, "%f", vValue);
  igi2_frame.tContext.vValue = vValue;
  pfEnumItemsCallback = ptParameterEnumList->pfEnumItemsCallback;
  igi2_frame.tContext.isMatch = 0;
  igi2_frame.tContext.ptParameterEnumList = ptParameterEnumList;
  igi2_frame.tContext.zBuffer = zBuffer;
  igi2_frame.tContext.nValue = 0;
  igi2_frame.tContext.zValue = (char *)&g_zInitialValue;
  igi2_frame.tContext.eParameterType = Level_eParameterTypeReal32;
  if ( !pfEnumItemsCallback )
    return (struct ParameterEnumItemList_s *)sprintf(zBuffer, "%f", vValue);
  igi2_frame.v5[0] = ptParameterEnumList;
  igi2_frame.v5[1] = ParameterEnumList_EnumCallback;
  igi2_frame.v5[2] = &igi2_frame.tContext;
  pfEnumItemsCallback((struct ParameterEnumListEnumItemsContext_s *)igi2_frame.v5);
  result = (struct ParameterEnumItemList_s *)igi2_frame.tContext.isMatch;
  if ( !igi2_frame.tContext.isMatch )
    return (struct ParameterEnumItemList_s *)sprintf(zBuffer, "%f", vValue);
  return result;
}

// source: h/1/parameterenumlist.c:238  [anchor-callee]
struct ParameterEnumItemList_s *__cdecl ParameterEnumList_PrintValueString(
        struct ParameterEnumItemList_s *ptParameterEnumList,
        char *zString,
        char *zBuffer)
{
  #pragma pack(push, 1)
  union
  {
    struct { _DWORD v5[3]; };
    struct { char igi2_o1[12]; struct EnumListSymbolEnumContext_s tContext; };
    char igi2_extent[40];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  void (__cdecl *pfEnumItemsCallback)(struct ParameterEnumListEnumItemsContext_s *); // ecx
  struct ParameterEnumItemList_s *result; // eax

  if ( !ptParameterEnumList )
    return (struct ParameterEnumItemList_s *)sprintf(
                                               zBuffer,
                                               (char *const)&stru_6A4CDC.tDebugConsoleLineList.ptMiddle,
                                               zString);
  igi2_frame.tContext.eParameterType = Level_eParameterTypeString16;
  pfEnumItemsCallback = ptParameterEnumList->pfEnumItemsCallback;
  memset(&igi2_frame.tContext.isMatch, 0, 12);
  igi2_frame.tContext.ptParameterEnumList = ptParameterEnumList;
  igi2_frame.tContext.zBuffer = zBuffer;
  igi2_frame.tContext.zValue = zString;
  if ( !pfEnumItemsCallback )
    return (struct ParameterEnumItemList_s *)sprintf(
                                               zBuffer,
                                               (char *const)&stru_6A4CDC.tDebugConsoleLineList.ptMiddle,
                                               zString);
  igi2_frame.v5[0] = ptParameterEnumList;
  igi2_frame.v5[1] = ParameterEnumList_EnumCallback;
  igi2_frame.v5[2] = &igi2_frame.tContext;
  pfEnumItemsCallback((struct ParameterEnumListEnumItemsContext_s *)igi2_frame.v5);
  result = (struct ParameterEnumItemList_s *)igi2_frame.tContext.isMatch;
  if ( !igi2_frame.tContext.isMatch )
    return (struct ParameterEnumItemList_s *)sprintf(
                                               zBuffer,
                                               (char *const)&stru_6A4CDC.tDebugConsoleLineList.ptMiddle,
                                               zString);
  return result;
}

// source: h/1/parameterenumlist.c:269  [anchor-mhash]
char *__cdecl ParameterEnumList_PrintValue(
        struct ParameterListItem_s *ptParameterListItem,
        void *pxData,
        char *zBuffer)
{
  struct ParameterEnumItemList_s *pxContext; // ebx
  int eParameterType; // eax
  int eParentParameterType; // ecx
  int v8; // ecx
  char *result; // eax

  pxContext = (struct ParameterEnumItemList_s *)ptParameterListItem->pxContext;
  eParameterType = ptParameterListItem->eParameterType;
  eParentParameterType = eParameterType;
  do
  {
    if ( eParentParameterType == Level_eParameterTypeInt32 )
      return (char *)ParameterEnumList_PrintValueInt(pxContext, *(_DWORD *)pxData, zBuffer);
    eParentParameterType = ParameterList_atParameterType[eParentParameterType].eParentParameterType;
  }
  while ( eParentParameterType != -1 );
  v8 = eParameterType;
  do
  {
    if ( v8 == Level_eParameterTypeReal32 )
      return (char *)ParameterEnumList_PrintValueReal(pxContext, *(float *)pxData, zBuffer);
    v8 = ParameterList_atParameterType[v8].eParentParameterType;
  }
  while ( v8 != -1 );
  result = (char *)ParameterEnumList_IsString(eParameterType);
  if ( result )
    return (char *)ParameterEnumList_PrintValueString(pxContext, (char *)pxData, zBuffer);
  return result;
}

// source: h/1/parameterenumlist.c:303  [anchor-mhash]
void __cdecl ParameterEnumList_EnumListParameterPrintHandler(void *pxData, void *pxContext)
{
  char *v2; // edi

  v2 = *((char **)pxContext + 2);
  if ( *((_DWORD *)pxContext + 1) && ParameterEnumList_IsString(*(_DWORD *)(*(_DWORD *)pxContext + 4)) )
    *v2++ = 34;
  ParameterEnumList_PrintValue(*(struct ParameterListItem_s **)pxContext, pxData, v2);
  if ( *((_DWORD *)pxContext + 1) )
  {
    if ( ParameterEnumList_IsString(*(_DWORD *)(*(_DWORD *)pxContext + 4)) )
      *(_WORD *)&v2[strlen(v2)] = 34;
  }
}

// source: h/1/parameterenumlist.c:338  [anchor-mhash]
void __cdecl ParameterEnumList_EnumerateSymbolsCallback(char *zSymbol, void *pxUserdata, void *pxContext)
{
  struct ParameterEnumListParseItemsContext_s tContext; // [esp+0h] [ebp-Ch] BYREF

  if ( *(_DWORD *)pxUserdata == 2 && *((_DWORD *)pxUserdata + 1) == 1 )
  {
    pxUserdata = *((void **)pxUserdata + 6);
    tContext.eParameterType = Level_eParameterTypeInt32;
    tContext.zName = zSymbol;
    tContext.pxData = &pxUserdata;
    (*((void (__cdecl **)(void *, struct ParameterEnumListParseItemsContext_s *))pxContext + 1))(pxContext, &tContext);
  }
}

// source: h/1/parameterenumlist.c:394  [size]
void __cdecl ParameterEnumList_EnumerateItemsCallback(struct ParameterEnumListEnumItemsContext_s *ptEnumContext)
{
  Script_EnumerateSymbols(ParameterEnumList_EnumerateSymbolsCallback, ptEnumContext);
}

// source: h/1/parameterenumlist.c:415  [anchor-hash]
struct ParameterEnumItemList_s *__cdecl ParameterEnumList_Alloc(
        struct ParameterEnumItemList_s *ptParameterEnumList)
{
  ptParameterEnumList->pfEnumItemsCallback = ParameterEnumList_EnumerateItemsCallback;
  ptParameterEnumList->ptHead = (struct ParameterEnumItem_s *)&ptParameterEnumList->ptMiddle;
  ptParameterEnumList->ptTail = (struct ParameterEnumItem_s *)ptParameterEnumList;
  ptParameterEnumList->ptMiddle = nullptr;
  return ptParameterEnumList;
}

// source: h/1/parameterenumlist.c:433  [size]
struct ParameterEnumItemList_s *__cdecl ParameterEnumList_AllocEx(
        struct ParameterEnumItemList_s *ptParameterEnumList,
        void (__cdecl *pfEnumItemsCallback)(struct ParameterEnumListEnumItemsContext_s *))
{
  ptParameterEnumList->pfEnumItemsCallback = pfEnumItemsCallback;
  ptParameterEnumList->ptHead = (struct ParameterEnumItem_s *)&ptParameterEnumList->ptMiddle;
  ptParameterEnumList->ptTail = (struct ParameterEnumItem_s *)ptParameterEnumList;
  ptParameterEnumList->ptMiddle = nullptr;
  return ptParameterEnumList;
}

// source: h/1/parameterenumlist.c:449  [anchor-callee]
struct ParameterEnumItemList_s *__cdecl ParameterEnumList_DeAlloc(
        struct ParameterEnumItemList_s *ptParameterEnumList)
{
  struct ParameterEnumItemList_s *result; // eax
  struct ParameterEnumItemList_s *ptHead; // ebx
  _DWORD **v3; // eax
  int v4; // esi

  result = (struct ParameterEnumItemList_s *)ptParameterEnumList->ptHead;
  ptHead = (struct ParameterEnumItemList_s *)result->ptHead;
  if ( result->ptHead )
  {
    do
    {
      v3 = Node_Remove(result);
      if ( v3 )
      {
        v4 = *(_DWORD *)((unsigned int)(v3 - 1) & 0xFFFFFFFC);
        --Mem_nCurrentAllocations;
        Node_Remove((_DWORD **)v4);
        memset(*(void **)(v4 + 8), 0xCDu, *(_DWORD *)(v4 + 16));
        free((void *)v4);
      }
      result = ptHead;
      ptHead = (struct ParameterEnumItemList_s *)ptHead->ptHead;
    }
    while ( ptHead );
  }
  return result;
}

// source: h/1/parameterenumlist.c:472  [anchor-mhash]
void __cdecl ParameterEnumList_EnumerateItems(
        struct ParameterEnumItemList_s *ptParameterEnumList,
        void (__cdecl *pfParseItemCallback)(struct ParameterEnumListEnumItemsContext_s *, struct ParameterEnumListParseItemsContext_s *),
        void *pxContext)
{
  void (__cdecl *pfEnumItemsCallback)(struct ParameterEnumListEnumItemsContext_s *); // eax
  struct ParameterEnumListEnumItemsContext_s tContext; // [esp+0h] [ebp-Ch] BYREF

  pfEnumItemsCallback = ptParameterEnumList->pfEnumItemsCallback;
  if ( pfEnumItemsCallback )
  {
    tContext.pfParseItems = pfParseItemCallback;
    tContext.ptParameterEnumItemList = ptParameterEnumList;
    tContext.pxContext = pxContext;
    pfEnumItemsCallback(&tContext);
  }
}

// source: h/1/parameterenumlist.c:497  [anchor-mhash]
void __cdecl ParameterEnumList_AddItem(
        struct ParameterEnumItemList_s *ptParameterEnumList,
        char *zPattern)
{
  _DWORD *v2; // esi

  v2 = Mem_AllocFn(18444, 4);
  v2[1] = 0;
  *v2 = 0;
  v2[4610] = zPattern;
  Wildcard_CreateNFA(zPattern, v2 + 2, (char *)v2 + 10248);
  List_AddTail(v2, (int)ptParameterEnumList);
}

// source: h/1/parameterenumlist.c:519  [anchor-mhash]
struct ParameterEnumItem_s *__cdecl ParameterEnumList_GetItem(
        struct ParameterEnumItemList_s *ptParameterEnumList,
        char *zName)
{
  struct ParameterEnumItem_s *ptHead; // edi
  struct ParameterEnumItem_s *ptNext; // esi

  ptHead = ptParameterEnumList->ptHead;
  ptNext = ptParameterEnumList->ptHead->ptNext;
  if ( !ptNext )
    return nullptr;
  while ( !Wildcard_MatchNFA(nullptr, nullptr, zName, (int)ptHead->atQMatchNFA, (int)ptHead->atQMatchCharClass, 0) )
  {
    ptHead = ptNext;
    ptNext = ptNext->ptNext;
    if ( !ptNext )
      return nullptr;
  }
  return ptHead;
}

// source: h/1/parameterenumlist.c:545  [size]
int __cdecl ParameterEnumList_GetParameterTypeEnumListInt32()
{
  return ParameterEnumList_eParameterTypeInt32;
}

// source: h/1/parameterenumlist.c:558  [size]
int __cdecl ParameterEnumList_GetParameterTypeEnumListReal32()
{
  return ParameterEnumList_eParameterTypeReal32;
}

// source: h/1/parameterenumlist.c:571  [size]
int __cdecl ParameterEnumList_GetParameterTypeEnumListString32()
{
  return ParameterEnumList_eParameterTypeString32;
}

// source: h/1/parameterenumlist.c:584  [size]
int __cdecl ParameterEnumList_GetParameterTypeEnumListString16()
{
  return ParameterEnumList_eParameterTypeString16;
}

// source: h/1/parameterenumlist.c:597  [size]
int __cdecl ParameterEnumList_GetParameterTypeEnumListString256()
{
  return ParameterEnumList_eParameterTypeString256;
}

// source: h/1/parameterenumlist.c:610  [anchor-hash]
void __cdecl ParameterEnumList_Open()
{
  int v0; // eax
  char v1; // bl
  int v2; // esi

  ParameterEnumList_eParameterTypeInt32 = ParameterList_NewParameterType("EnumInt32", Level_eParameterTypeInt32);
  ParameterEnumList_eParameterTypeReal32 = ParameterList_NewParameterType("EnumReal32", Level_eParameterTypeReal32);
  ParameterEnumList_eParameterTypeString16 = ParameterList_NewParameterType(
                                               "EnumString16",
                                               Level_eParameterTypeString16);
  ParameterEnumList_eParameterTypeString32 = ParameterList_NewParameterType(
                                               "EnumString32",
                                               Level_eParameterTypeString32);
  v0 = ParameterList_NewParameterType("EnumString256", Level_eParameterTypeString256);
  v1 = ParameterList_eQParameterPrintEvent;
  v2 = v0;
  ParameterEnumList_eParameterTypeString256 = v0;
  ParameterList_LinkParameterEventHandler(
    ParameterEnumList_eParameterTypeInt32,
    ParameterList_eQParameterPrintEvent,
    ParameterEnumList_EnumListParameterPrintHandler);
  ParameterList_LinkParameterEventHandler(
    ParameterEnumList_eParameterTypeReal32,
    v1,
    ParameterEnumList_EnumListParameterPrintHandler);
  ParameterList_LinkParameterEventHandler(
    ParameterEnumList_eParameterTypeString16,
    v1,
    ParameterEnumList_EnumListParameterPrintHandler);
  ParameterList_LinkParameterEventHandler(
    ParameterEnumList_eParameterTypeString32,
    v1,
    ParameterEnumList_EnumListParameterPrintHandler);
  ParameterList_LinkParameterEventHandler(v2, v1, ParameterEnumList_EnumListParameterPrintHandler);
}

// source: h/1/parameterenumlist.c:643  [anchor-mhash]
void __cdecl ParameterEnumList_Close()
{
  int v0; // edx
  int v1; // ecx
  int v2; // edx
  int v3; // ecx

  v0 = ParameterEnumList_eParameterTypeReal32;
  ParameterList_atParameterType[ParameterEnumList_eParameterTypeInt32].isUsed = false;
  v1 = ParameterEnumList_eParameterTypeString16;
  ParameterList_atParameterType[v0].isUsed = false;
  v2 = ParameterEnumList_eParameterTypeString32;
  ParameterList_atParameterType[v1].isUsed = false;
  v3 = ParameterEnumList_eParameterTypeString256;
  ParameterList_atParameterType[v2].isUsed = false;
  ParameterList_atParameterType[v3].isUsed = false;
}
