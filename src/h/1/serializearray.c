/* h/1/serializearray.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: h/1/serializearray.c:37  [anchor-strings]
void __cdecl SerializeArray_ParameterPrintHandler(void *pxData, void *pxContext)
{
  char *v3; // edi
  int v4; // ebx
  int v5; // ebp
  char *v6; // edi
  int v7; // edx
  int v8; // eax
  char *v9; // esi
  int v10; // ecx
  int v11; // eax
  int v12; // edx
  int v13; // ebx

  v3 = *((char **)pxContext + 2);
  v4 = *(_DWORD *)(*(_DWORD *)pxContext + 8) >> 2;
  v5 = *(_DWORD *)(*(_DWORD *)pxContext + 8) - 4 * v4;
  v6 = &v3[sprintf(v3, "%d, %d", v4, v5)];
  if ( v4 > 0 )
  {
    do
    {
      v7 = *((unsigned __int8 *)pxData + 1);
      v8 = *(unsigned __int8 *)pxData << 8;
      v9 = (char *)pxData + 1;
      v10 = (unsigned __int8)v9[1];
      v11 = v7 | v8;
      v12 = (unsigned __int8)(++v9)[1];
      pxData = v9 + 2;
      v6 += sprintf(v6, ", 0x%08x", v12 | ((v10 | (v11 << 8)) << 8));
      --v4;
    }
    while ( v4 );
  }
  if ( v5 > 0 )
  {
    v13 = v5;
    do
    {
      v6 += sprintf(v6, ", 0x%02X", *(unsigned __int8 *)pxData);
      pxData = (char *)pxData + 1;
      --v13;
    }
    while ( v13 );
  }
}

// source: h/1/serializearray.c:89  [anchor-mhash]
void __cdecl SerializeArray_ParameterParseHandler(void *pxData, void *pxContext)
{
  int *v2; // esi
  int v3; // eax
  struct ArgList_s *v4; // edi
  char *v5; // ebx
  int v6; // eax
  struct ArgList_s *v7; // edi
  void *v8; // eax
  int v10; // eax
  struct ArgList_s *v11; // edi
  unsigned int v12; // eax
  int i; // ecx
  int v14; // ebx
  int v15; // eax
  struct ArgList_s *v16; // edi
  char v17; // al
  int nBytes; // [esp+10h] [ebp-4h]

  v2 = (int *)pxContext;
  v3 = *(_DWORD *)pxContext;
  v4 = *((struct ArgList_s **)pxContext + 1);
  ++*(_DWORD *)pxContext;
  if ( v4->isQVM )
  {
    pxContext = nullptr;
    QVM_EvalArg(&pxContext, 4, v4, v3, 1);
    v5 = (char *)pxContext;
  }
  else
  {
    v5 = (char *)Expression_EvalInt(v4->aptExpression[v3]);
  }
  v6 = *v2;
  v7 = (struct ArgList_s *)v2[1];
  ++*v2;
  if ( v7->isQVM )
  {
    pxContext = nullptr;
    QVM_EvalArg(&pxContext, 4, v7, v6, 1);
    v8 = pxContext;
  }
  else
  {
    v8 = (void *)Expression_EvalInt(v7->aptExpression[v6]);
  }
  nBytes = (int)v8;
  if ( (int)v5 > 0 )
  {
    do
    {
      v10 = *v2;
      v11 = (struct ArgList_s *)v2[1];
      ++*v2;
      if ( v11->isQVM )
      {
        pxContext = nullptr;
        QVM_EvalArg(&pxContext, 4, v11, v10, 1);
        v12 = (unsigned int)pxContext;
      }
      else
      {
        v12 = Expression_EvalInt(v11->aptExpression[v10]);
      }
      for ( i = 3; i >= 0; --i )
      {
        *((_BYTE *)pxData + i) = v12;
        v12 >>= 8;
      }
      pxData = (char *)pxData + 4;
      --v5;
    }
    while ( v5 );
  }
  v14 = nBytes;
  if ( nBytes > 0 )
  {
    do
    {
      v15 = *v2;
      v16 = (struct ArgList_s *)v2[1];
      ++*v2;
      if ( v16->isQVM )
      {
        pxContext = nullptr;
        QVM_EvalArg(&pxContext, 4, v16, v15, 1);
        v17 = (char)pxContext;
      }
      else
      {
        v17 = Expression_EvalInt(v16->aptExpression[v15]);
      }
      *(_BYTE *)pxData = v17;
      pxData = (char *)pxData + 1;
      --v14;
    }
    while ( v14 );
  }
}

// source: h/1/serializearray.c:143  [anchor-mhash]
unsigned int __cdecl SerializeArray_AddParameter(
        struct ParameterList_s *ptParameterList,
        unsigned int nOffset,
        char *zName,
        unsigned __int8 bParameterProperties,
        unsigned int nElementSize,
        unsigned int nElements)
{
  return (unsigned int)ParameterList_AddParameter(
                         ptParameterList,
                         nOffset,
                         SerializeArray_eParameterType,
                         zName,
                         bParameterProperties,
                         (void *)(nElements * nElementSize));
}

// source: h/1/serializearray.c:156  [anchor-strings]
void __cdecl SerializeArray_Open()
{
  int v0; // esi

  v0 = ParameterList_NewParameterType("SerializeArray", -1);
  SerializeArray_eParameterType = v0;
  ParameterList_LinkParameterEventHandler(v0, ParameterList_eQParameterPrintEvent, SerializeArray_ParameterPrintHandler);
  ParameterList_LinkParameterEventHandler(v0, ParameterList_eQParameterParseEvent, SerializeArray_ParameterParseHandler);
}

// source: h/1/serializearray.c:171  [size]
void __cdecl SerializeArray_Close()
{
  ParameterList_atParameterType[SerializeArray_eParameterType].isUsed = false;
}
