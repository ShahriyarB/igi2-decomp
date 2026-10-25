/* j/0/vehicles/helitype.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/vehicles/helitype.c:31  [size]
void __cdecl HeliType_Open()
{
  ;
}

// source: j/0/vehicles/helitype.c:43  [size]
void __cdecl HeliType_Close()
{
  ;
}

// source: j/0/vehicles/helitype.c:55  [anchor-mhash]
struct ArgList_s *__cdecl HeliType_DefineHeliType(
        struct HeliType_s *ptHeliType,
        int *pnArg,
        struct ArgList_s *ptArgList)
{
  int v5; // eax
  int v6; // ebp
  int v7; // eax
  struct HeliRotor_s *atRotor; // ebx
  int v9; // eax
  int v10; // eax
  int v11; // eax
  int v12; // ebp
  struct ArgList_s *result; // eax
  int *anExplodeMagicVertex; // ebx
  int v15; // eax
  int v16; // eax
  struct ArgList_s *pxData; // [esp+14h] [ebp-4h] BYREF

  VehicleType_DefineVehicleType(&ptHeliType->tVehicleType, pnArg, ptArgList);
  v5 = (*pnArg)++;
  v6 = 0;
  if ( ptArgList->isQVM )
  {
    pxData = nullptr;
    QVM_EvalArg(&pxData, 4, ptArgList, v5, 1);
    v7 = (int)pxData;
  }
  else
  {
    v7 = Expression_EvalInt(ptArgList->aptExpression[v5]);
  }
  ptHeliType->nRotor = v7;
  if ( v7 > 0 )
  {
    atRotor = ptHeliType->atRotor;
    do
    {
      v9 = (*pnArg)++;
      if ( ptArgList->isQVM )
      {
        pxData = nullptr;
        QVM_EvalArg(&pxData, 4, ptArgList, v9, 1);
        v10 = (int)pxData;
      }
      else
      {
        v10 = Expression_EvalInt(ptArgList->aptExpression[v9]);
      }
      atRotor->iMagicObj = v10;
      ++v6;
      ++atRotor;
    }
    while ( v6 < ptHeliType->nRotor );
  }
  v11 = (*pnArg)++;
  v12 = 0;
  if ( ptArgList->isQVM )
  {
    pxData = nullptr;
    QVM_EvalArg(&pxData, 4, ptArgList, v11, 1);
    result = pxData;
  }
  else
  {
    result = (struct ArgList_s *)Expression_EvalInt(ptArgList->aptExpression[v11]);
  }
  ptHeliType->nExplodeMagicVertex = (int)result;
  if ( (int)result > 0 )
  {
    anExplodeMagicVertex = ptHeliType->anExplodeMagicVertex;
    do
    {
      v15 = (*pnArg)++;
      if ( ptArgList->isQVM )
      {
        pxData = nullptr;
        QVM_EvalArg(&pxData, 4, ptArgList, v15, 1);
        v16 = (int)pxData;
      }
      else
      {
        v16 = Expression_EvalInt(ptArgList->aptExpression[v15]);
      }
      *anExplodeMagicVertex = v16;
      result = (struct ArgList_s *)ptHeliType;
      ++v12;
      ++anExplodeMagicVertex;
    }
    while ( v12 < ptHeliType->nExplodeMagicVertex );
  }
  return result;
}
