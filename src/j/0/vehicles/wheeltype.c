/* j/0/vehicles/wheeltype.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/vehicles/wheeltype.c:31  [anchor-mhash]
void __cdecl WheelType_ParsePhysicsObjTypeHandler(struct QTask_s *ptQTask, void *pxContext)
{
  _DWORD *v2; // esi
  int v3; // eax
  float *v4; // ebx
  struct ArgList_s *v5; // edi
  int v6; // eax
  double v7; // st7
  int v8; // eax

  v2 = pxContext;
  v3 = *((_DWORD *)pxContext + 2);
  v4 = *(float **)pxContext;
  v5 = *((struct ArgList_s **)pxContext + 1);
  *((_DWORD *)pxContext + 2) = v3 + 1;
  if ( v5->isQVM )
  {
    *((_BYTE *)v4 + 728) = 0;
    QVM_EvalArg(v4 + 182, 16, v5, v3, 3);
  }
  else
  {
    Expression_EvalString(v5->aptExpression[v3], (char *)v4 + 728, 16);
  }
  v6 = v2[2];
  v2[2] = v6 + 1;
  if ( v5->isQVM )
  {
    *(float *)&pxContext = 0.0;
    QVM_EvalArg(&pxContext, 4, v5, v6, 2);
    v7 = *(float *)&pxContext;
  }
  else
  {
    v7 = Expression_EvalFloat(v5->aptExpression[v6]);
  }
  v4[186] = v7 * 4096.0;
  v8 = v2[2];
  v2[2] = v8 + 1;
  if ( v5->isQVM )
  {
    *(float *)&pxContext = 0.0;
    QVM_EvalArg(&pxContext, 4, v5, v8, 2);
    v4[187] = *(float *)&pxContext * 4096.0;
  }
  else
  {
    v4[187] = Expression_EvalFloat(v5->aptExpression[v8]) * 4096.0;
  }
}

// source: j/0/vehicles/wheeltype.c:59  [size]
void __cdecl WheelType_GetGetPhysicsObjTypeSizeHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = 752;
}

// source: j/0/vehicles/wheeltype.c:77  [size]
void __cdecl WheelType_Open()
{
  unsigned __int16 v0; // si

  v0 = Wheel_eQTaskType;
  QTask_LinkQTaskEventHandlerFn(
    Wheel_eQTaskType,
    PhysicsObjType_eParsePhysicsObjTypeEvent,
    WheelType_ParsePhysicsObjTypeHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    PhysicsObjType_eGetPhysicsObjTypeSizeEvent,
    (void (__cdecl *)(struct QTask_s *, void *))WheelType_GetGetPhysicsObjTypeSizeHandler);
}

// source: j/0/vehicles/wheeltype.c:92  [size]
void __cdecl WheelType_Close()
{
  ;
}
