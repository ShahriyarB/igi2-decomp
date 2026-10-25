/* h/1/serializestruct.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: h/1/serializestruct.c:36  [anchor-mhash]
void __cdecl SerializeStruct_ParameterPrintHandler(void *pxData, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { int v7; };
    struct { char igi2_o1[4]; struct ParameterPrintContext_s tParameterPrintContext; };
    char igi2_extent[24];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  char *v2; // edx
  int *v3; // ebx
  char *v4; // esi
  int v5; // ebp
  int v6; // edi
  char *pxContexta = *(char * *)&pxContext; // [esp+30h] [ebp+8h] ARGSLOT

  v2 = *((char **)pxContext + 3);
  v3 = *(int **)(*(_DWORD *)pxContext + 8);
  qmemcpy(&igi2_frame.tParameterPrintContext, pxContext, sizeof(igi2_frame.tParameterPrintContext));
  v4 = *((char **)pxContext + 2);
  v5 = 0;
  pxContexta = v2;
  if ( *v3 > 0 )
  {
    v6 = 0;
    igi2_frame.v7 = 0;
    do
    {
      igi2_frame.tParameterPrintContext.nBufferSize = (unsigned int)pxContexta;
      igi2_frame.tParameterPrintContext.zBuffer = v4;
      igi2_frame.tParameterPrintContext.ptParameterListItem = (struct ParameterListItem_s *)(v6 + v3[2]);
      ParameterList_atParameterType[*(_DWORD *)(v6 + v3[2] + 4)].apfQParameterEvent[ParameterList_eQParameterPrintEvent](
        (char *)pxData + *(_DWORD *)(v6 + v3[2]),
        &igi2_frame.tParameterPrintContext);
      if ( v5 < *v3 - 1 )
      {
        strcat(v4, ", ");
        v6 = igi2_frame.v7;
      }
      pxContexta -= strlen(v4);
      v4 += strlen(v4);
      ++v5;
      v6 += 20;
      igi2_frame.v7 = v6;
    }
    while ( v5 < *v3 );
  }
}

// source: h/1/serializestruct.c:84  [anchor-mhash]
void __cdecl SerializeStruct_ParameterParseHandler(void *pxData, void *pxContext)
{
  int *v2; // ebx
  int v3; // edi
  int v4; // esi
  struct ParameterParseContext_s tParameterParseContext; // [esp+Ch] [ebp-14h] BYREF

  v2 = *(int **)(*((_DWORD *)pxContext + 4) + 8);
  qmemcpy(&tParameterParseContext, pxContext, sizeof(tParameterParseContext));
  v3 = 0;
  if ( *v2 <= 0 )
  {
    *(_DWORD *)pxContext = tParameterParseContext.iArg;
  }
  else
  {
    v4 = 0;
    do
    {
      tParameterParseContext.ptParameterListItem = (struct ParameterListItem_s *)(v4 + v2[2]);
      ParameterList_atParameterType[*(_DWORD *)(v2[2] + v4 + 4)].apfQParameterEvent[ParameterList_eQParameterParseEvent](
        (char *)pxData + *(_DWORD *)(v4 + v2[2]),
        &tParameterParseContext);
      ++v3;
      v4 += 20;
    }
    while ( v3 < *v2 );
    *(_DWORD *)pxContext = tParameterParseContext.iArg;
  }
}

// source: h/1/serializestruct.c:121  [anchor-mhash]
struct ParameterList_s *__cdecl SerializeStruct_AddParameter(
        struct ParameterList_s *ptParameterList,
        unsigned int nOffset,
        char *zName,
        unsigned __int8 bParameterProperties,
        struct ParameterList_s *ptStructParameterList)
{
  return ParameterList_AddParameter(
           ptParameterList,
           nOffset,
           SerializeStruct_eParameterType,
           zName,
           bParameterProperties,
           ptStructParameterList);
}

// source: h/1/serializestruct.c:134  [anchor-strings]
void __cdecl SerializeStruct_Open()
{
  int v0; // esi

  v0 = ParameterList_NewParameterType("SerializeStruct", -1);
  SerializeStruct_eParameterType = v0;
  ParameterList_LinkParameterEventHandler(
    v0,
    ParameterList_eQParameterPrintEvent,
    SerializeStruct_ParameterPrintHandler);
  ParameterList_LinkParameterEventHandler(
    v0,
    ParameterList_eQParameterParseEvent,
    SerializeStruct_ParameterParseHandler);
}

// source: h/1/serializestruct.c:149  [size]
void __cdecl SerializeStruct_Close()
{
  ParameterList_atParameterType[SerializeStruct_eParameterType].isUsed = false;
}
