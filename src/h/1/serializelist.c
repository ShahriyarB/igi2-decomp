/* h/1/serializelist.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: h/1/serializelist.c:47  [size]
void *__cdecl SerializeList_AllocListItem(struct SerializeListType_s *ptSerializeListType)
{
  return Mem_AllocFn(ptSerializeListType->nListItemSize, 4);
}

// source: h/1/serializelist.c:60  [anchor-mhash]
void __cdecl SerializeList_DeAllocListItem(struct SerializeListType_s *ptSerializeListType, void *pxItem)
{
  int v2; // esi

  if ( pxItem )
  {
    v2 = *(_DWORD *)(((int)pxItem - 4) & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v2);
    memset(*(void **)(v2 + 8), 0xCDu, *(_DWORD *)(v2 + 16));
    free((void *)v2);
  }
}

// source: h/1/serializelist.c:73  [anchor-caller]
void __cdecl SerializeList_ParameterPrintHandler(void *pxData, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct SerializeContext_s tSerializeContext; };
    struct { char igi2_o1[12]; char zParameterBuffer[1024]; };
    char igi2_extent[1036];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct ParameterList_s *v2; // ebx
  int v3; // eax
  _DWORD *v4; // eax
  _DWORD *i; // ebp

  v2 = **(struct ParameterList_s ***)(*(_DWORD *)pxContext + 8);
  igi2_frame.tSerializeContext.nParameterBufferSize = 1024;
  igi2_frame.tSerializeContext.ptFile = nullptr;
  igi2_frame.tSerializeContext.pzParameterBuffer = igi2_frame.zParameterBuffer;
  v3 = List_Length((_DWORD **)pxData);
  sprintf(igi2_frame.zParameterBuffer, (char *const)&g_ptNetManager.tReceiveCounters.tCounters[9].nBytes, v3);
  v4 = *(_DWORD **)pxData;
  for ( i = **(_DWORD ***)pxData; i; i = (_DWORD *)*i )
  {
    Serialize_WriteParameterList(v4, &igi2_frame.tSerializeContext, v2);
    strcat(*((char **)pxContext + 2), igi2_frame.zParameterBuffer);
    igi2_frame.zParameterBuffer[0] = 0;
    v4 = i;
  }
}

// source: h/1/serializelist.c:126  [anchor-mhash]
void __cdecl SerializeList_ParameterParseHandler(void *pxData, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct ParameterList_s *ptParameterList; };
    struct { char igi2_o1[4]; struct DeSerializeContext_s tDeSerializeContext; };
    char igi2_extent[12];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  void *v2; // ebp
  int v3; // ebx
  _DWORD **v4; // eax
  _DWORD *v5; // esi
  _DWORD **v6; // eax
  int v7; // eax
  struct ArgList_s *v8; // edi
  void *v9; // eax
  _DWORD *v10; // esi
  int v11; // ecx
  void (__cdecl *v12)(int, _DWORD *); // eax

  v2 = pxContext;
  v3 = *(_DWORD *)(*((_DWORD *)pxContext + 4) + 8);
  v4 = *(_DWORD ***)pxData;
  v5 = **(_DWORD ***)pxData;
  for ( igi2_frame.ptParameterList = *(struct ParameterList_s **)v3; v5; v5 = (_DWORD *)*v5 )
  {
    v6 = Node_Remove(v4);
    (*(void (__cdecl **)(int, _DWORD **))(v3 + 48))(v3, v6);
    v4 = (_DWORD **)v5;
  }
  v7 = *(_DWORD *)v2;
  v8 = *((struct ArgList_s **)v2 + 1);
  ++*(_DWORD *)v2;
  if ( v8->isQVM )
  {
    pxContext = nullptr;
    QVM_EvalArg(&pxContext, 4, v8, v7, 1);
    v9 = pxContext;
  }
  else
  {
    v9 = (void *)Expression_EvalInt(v8->aptExpression[v7]);
  }
  if ( (int)v9 > 0 )
  {
    pxContext = v9;
    do
    {
      v10 = (_DWORD *)(*(int (__cdecl **)(int))(v3 + 44))(v3);
      v10[1] = 0;
      *v10 = 0;
      List_AddTail(v10, (int)pxData);
      v11 = *(_DWORD *)v2;
      igi2_frame.tDeSerializeContext.ptArgList = *((struct ArgList_s **)v2 + 1);
      igi2_frame.tDeSerializeContext.tReturn.iArgOffset = v11;
      Serialize_ParseParameterList(v10, &igi2_frame.tDeSerializeContext, igi2_frame.ptParameterList);
      *(_DWORD *)v2 = igi2_frame.tDeSerializeContext.tReturn.iArgOffset;
      v12 = *(void (__cdecl **)(int, _DWORD *))(v3 + 52);
      if ( v12 )
        v12(v3, v10);
      pxContext = (char *)pxContext - 1;
    }
    while ( pxContext );
  }
}

// source: h/1/serializelist.c:213  [anchor-strings]
struct SerializeListType_s *__cdecl SerializeList_NewListType(
        char *zName,
        struct ParameterList_s *ptParameterList,
        unsigned int nListItemSize,
        void *(__cdecl *pfSerializeListAllocItem)(struct SerializeListType_s *),
        void (__cdecl *pfSerializeListDeAllocItem)(struct SerializeListType_s *, void *),
        void (__cdecl *pfSerializeListUpdateItem)(struct SerializeListType_s *, void *))
{
  int v8; // ecx
  unsigned int v9; // eax
  int v10; // ecx
  struct SerializeListType_s *result; // eax
  char *v12; // esi
  char v13; // cl

  v8 = 0;
  v9 = 0;
  while ( SerializeList_atSerializeListType[v9].isAllocated )
  {
    ++v9;
    ++v8;
    if ( v9 >= 32 )
    {
      LDebug_Error("Failed to create new SerializeList type.");
      abort();
    }
  }
  v10 = v8;
  SerializeList_atSerializeListType[v10].nListItemSize = nListItemSize;
  result = &SerializeList_atSerializeListType[v10];
  SerializeList_atSerializeListType[v10].isAllocated = true;
  SerializeList_atSerializeListType[v10].ptParameterList = ptParameterList;
  if ( !pfSerializeListAllocItem )
    pfSerializeListAllocItem = SerializeList_AllocListItem;
  SerializeList_atSerializeListType[v10].pfSerializeListAllocItem = pfSerializeListAllocItem;
  if ( !pfSerializeListDeAllocItem )
    pfSerializeListDeAllocItem = SerializeList_DeAllocListItem;
  SerializeList_atSerializeListType[v10].pfSerializeListDeAllocItem = pfSerializeListDeAllocItem;
  SerializeList_atSerializeListType[v10].pfSerializeListUpdateItem = pfSerializeListUpdateItem;
  v12 = &SerializeList_atSerializeListType[0].zName[v10 * 56 - (_DWORD)zName];
  do
  {
    v13 = *zName;
    zName[(_DWORD)v12] = *zName;
    ++zName;
  }
  while ( v13 );
  return result;
}

// source: h/1/serializelist.c:248  [size]
struct SerializeListType_s *__cdecl SerializeList_DeleteListType(
        struct SerializeListType_s *ptSerializeListType)
{
  ptSerializeListType->isAllocated = false;
  return ptSerializeListType;
}

// source: h/1/serializelist.c:263  [size]
int __cdecl SerializeList_GetParameterType()
{
  return SerializeList_eParameterType;
}

// source: h/1/serializelist.c:276  [anchor-strings]
void __cdecl SerializeList_Open()
{
  int v0; // esi

  v0 = ParameterList_NewParameterType("SerializeList", -1);
  SerializeList_eParameterType = v0;
  ParameterList_LinkParameterEventHandler(v0, ParameterList_eQParameterPrintEvent, SerializeList_ParameterPrintHandler);
  ParameterList_LinkParameterEventHandler(v0, ParameterList_eQParameterParseEvent, SerializeList_ParameterParseHandler);
}

// source: h/1/serializelist.c:291  [size]
void __cdecl SerializeList_Close()
{
  ParameterList_atParameterType[SerializeList_eParameterType].isUsed = false;
}
