/* j/0/vehicles/cartype.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/vehicles/cartype.c:31  [anchor-mhash]
void __cdecl CarType_ParsePhysicsObjTypeHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { int pxData; };
    struct { char igi2_o1[4]; int v36; };
    struct { char igi2_o2[8]; float v37; };
    struct { char igi2_o3[12]; int v38; };
    struct { char igi2_o4[16]; float v39; };
    struct { char igi2_o5[20]; float v40; };
    struct { char igi2_o6[24]; int iExplodeVertex; };
    struct { char igi2_o7[28]; struct CarType_s *ptCarType; };
    char igi2_extent[32];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct CarType_s *v2; // ebx
  struct ArgList_s *v3; // edi
  int v4; // eax
  int v5; // eax
  char *p_isEngineWheel; // ebx
  int v7; // eax
  char v8; // al
  int v9; // eax
  char v10; // al
  int v11; // eax
  double v12; // st7
  int v13; // eax
  int v14; // eax
  int v15; // eax
  double v16; // st7
  int v17; // eax
  double v18; // st7
  int v19; // eax
  int nWheel; // edx
  int v21; // eax
  double v22; // st7
  int v23; // eax
  char v24; // al
  int v25; // eax
  char v26; // al
  int v27; // eax
  int v28; // eax
  struct CarType_s *v29; // eax
  int v30; // eax
  struct CarType_s *v31; // eax
  float v32; // ecx
  int v34; // eax

  v2 = *(struct CarType_s **)pxContext;
  v3 = *((struct ArgList_s **)pxContext + 1);
  igi2_frame.ptCarType = *(struct CarType_s **)pxContext;
  ((void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[PhysicsObjType_eParsePhysicsObjTypeEvent][Vehicle_eQTaskType].pfHandler)(
    ptQTask,
    pxContext);
  v4 = *((_DWORD *)pxContext + 2);
  *((_DWORD *)pxContext + 2) = v4 + 1;
  if ( v3->isQVM )
  {
    igi2_frame.pxData = 0;
    QVM_EvalArg(&igi2_frame.pxData, 4, v3, v4, 1);
    v5 = igi2_frame.pxData;
  }
  else
  {
    v5 = Expression_EvalInt(v3->aptExpression[v4]);
  }
  v2->nWheel = v5;
  igi2_frame.iExplodeVertex = 0;
  if ( v5 > 0 )
  {
    p_isEngineWheel = &v2->atCarWheelType[0].isEngineWheel;
    do
    {
      v7 = *((_DWORD *)pxContext + 2);
      *((_DWORD *)pxContext + 2) = v7 + 1;
      if ( v3->isQVM )
      {
        igi2_frame.pxData = 0;
        QVM_EvalArg(&igi2_frame.pxData, 4, v3, v7, 1);
        v8 = igi2_frame.pxData;
      }
      else
      {
        v8 = Expression_EvalInt(v3->aptExpression[v7]);
      }
      *(p_isEngineWheel - 1) = v8;
      v9 = *((_DWORD *)pxContext + 2);
      *((_DWORD *)pxContext + 2) = v9 + 1;
      if ( v3->isQVM )
      {
        igi2_frame.v36 = 0;
        QVM_EvalArg(&igi2_frame.v36, 4, v3, v9, 1);
        v10 = igi2_frame.v36;
      }
      else
      {
        v10 = Expression_EvalInt(v3->aptExpression[v9]);
      }
      *p_isEngineWheel = v10;
      v11 = *((_DWORD *)pxContext + 2);
      *((_DWORD *)pxContext + 2) = v11 + 1;
      if ( v3->isQVM )
      {
        igi2_frame.v37 = 0.0;
        QVM_EvalArg(&igi2_frame.v37, 4, v3, v11, 2);
        v12 = igi2_frame.v37;
      }
      else
      {
        v12 = Expression_EvalFloat(v3->aptExpression[v11]);
      }
      *(float *)(p_isEngineWheel + 3) = v12;
      v13 = *((_DWORD *)pxContext + 2);
      *((_DWORD *)pxContext + 2) = v13 + 1;
      if ( v3->isQVM )
      {
        igi2_frame.v38 = 0;
        QVM_EvalArg(&igi2_frame.v38, 4, v3, v13, 1);
        v14 = igi2_frame.v38;
      }
      else
      {
        v14 = Expression_EvalInt(v3->aptExpression[v13]);
      }
      *(_DWORD *)(p_isEngineWheel + 7) = v14;
      v15 = *((_DWORD *)pxContext + 2);
      *((_DWORD *)pxContext + 2) = v15 + 1;
      if ( v3->isQVM )
      {
        igi2_frame.v39 = 0.0;
        QVM_EvalArg(&igi2_frame.v39, 4, v3, v15, 2);
        v16 = igi2_frame.v39;
      }
      else
      {
        v16 = Expression_EvalFloat(v3->aptExpression[v15]);
      }
      *(float *)(p_isEngineWheel + 11) = v16 * 4096.0;
      v17 = *((_DWORD *)pxContext + 2);
      *((_DWORD *)pxContext + 2) = v17 + 1;
      if ( v3->isQVM )
      {
        igi2_frame.v40 = 0.0;
        QVM_EvalArg(&igi2_frame.v40, 4, v3, v17, 2);
        v18 = igi2_frame.v40;
      }
      else
      {
        v18 = Expression_EvalFloat(v3->aptExpression[v17]);
      }
      v19 = igi2_frame.iExplodeVertex;
      *(float *)(p_isEngineWheel + 15) = v18;
      nWheel = igi2_frame.ptCarType->nWheel;
      p_isEngineWheel += 20;
      igi2_frame.iExplodeVertex = v19 + 1;
    }
    while ( v19 + 1 < nWheel );
    v2 = igi2_frame.ptCarType;
  }
  v21 = *((_DWORD *)pxContext + 2);
  *((_DWORD *)pxContext + 2) = v21 + 1;
  if ( v3->isQVM )
  {
    *(float *)&igi2_frame.ptCarType = 0.0;
    QVM_EvalArg(&igi2_frame.ptCarType, 4, v3, v21, 2);
    v22 = *(float *)&igi2_frame.ptCarType;
  }
  else
  {
    v22 = Expression_EvalFloat(v3->aptExpression[v21]);
  }
  v2->vWheelCollPointZAdjustment = v22 * 4096.0;
  v23 = *((_DWORD *)pxContext + 2);
  *((_DWORD *)pxContext + 2) = v23 + 1;
  if ( v3->isQVM )
  {
    *(float *)&igi2_frame.ptCarType = 0.0;
    QVM_EvalArg(&igi2_frame.ptCarType, 4, v3, v23, 1);
    v24 = (char)igi2_frame.ptCarType;
  }
  else
  {
    v24 = Expression_EvalInt(v3->aptExpression[v23]);
  }
  v2->isWheelsAttachObj = v24;
  v25 = *((_DWORD *)pxContext + 2);
  *((_DWORD *)pxContext + 2) = v25 + 1;
  if ( v3->isQVM )
  {
    *(float *)&igi2_frame.ptCarType = 0.0;
    QVM_EvalArg(&igi2_frame.ptCarType, 4, v3, v25, 1);
    v26 = (char)igi2_frame.ptCarType;
  }
  else
  {
    v26 = Expression_EvalInt(v3->aptExpression[v25]);
  }
  v2->isCrawler = v26;
  v27 = *((_DWORD *)pxContext + 2);
  *((_DWORD *)pxContext + 2) = v27 + 1;
  if ( v3->isQVM )
  {
    v2->zEngineSound[0] = 0;
    QVM_EvalArg(v2->zEngineSound, 32, v3, v27, 3);
  }
  else
  {
    Expression_EvalString(v3->aptExpression[v27], v2->zEngineSound, 32);
  }
  v28 = *((_DWORD *)pxContext + 2);
  *((_DWORD *)pxContext + 2) = v28 + 1;
  if ( v3->isQVM )
  {
    *(float *)&igi2_frame.ptCarType = 0.0;
    QVM_EvalArg(&igi2_frame.ptCarType, 4, v3, v28, 1);
    v29 = igi2_frame.ptCarType;
  }
  else
  {
    v29 = (struct CarType_s *)Expression_EvalInt(v3->aptExpression[v28]);
  }
  v2->nExplodeMagicVertex = (int)v29;
  igi2_frame.iExplodeVertex = 0;
  if ( (int)v29 > 0 )
  {
    LODWORD(igi2_frame.v40) = v2->anExplodeMagicVertex;
    do
    {
      v30 = *((_DWORD *)pxContext + 2);
      *((_DWORD *)pxContext + 2) = v30 + 1;
      if ( v3->isQVM )
      {
        *(float *)&igi2_frame.ptCarType = 0.0;
        QVM_EvalArg(&igi2_frame.ptCarType, 4, v3, v30, 1);
        v31 = igi2_frame.ptCarType;
      }
      else
      {
        v31 = (struct CarType_s *)Expression_EvalInt(v3->aptExpression[v30]);
      }
      v32 = igi2_frame.v40;
      *(_DWORD *)LODWORD(igi2_frame.v40) = v31;
      LODWORD(igi2_frame.v40) = LODWORD(v32) + 4;
    }
    while ( ++igi2_frame.iExplodeVertex < v2->nExplodeMagicVertex );
  }
  v34 = *((_DWORD *)pxContext + 2);
  *((_DWORD *)pxContext + 2) = v34 + 1;
  if ( v3->isQVM )
  {
    v2->zDestroyedModel[0] = 0;
    QVM_EvalArg(v2->zDestroyedModel, 16, v3, v34, 3);
  }
  else
  {
    Expression_EvalString(v3->aptExpression[v34], v2->zDestroyedModel, 16);
  }
}

// source: j/0/vehicles/cartype.c:93  [size]
void __cdecl CarType_GetGetPhysicsObjTypeSizeHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = 704;
}

// source: j/0/vehicles/cartype.c:111  [size]
void __cdecl CarType_Open()
{
  unsigned __int16 v0; // si

  v0 = Car_eQTaskType;
  QTask_LinkQTaskEventHandlerFn(
    Car_eQTaskType,
    PhysicsObjType_eParsePhysicsObjTypeEvent,
    CarType_ParsePhysicsObjTypeHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    PhysicsObjType_eGetPhysicsObjTypeSizeEvent,
    (void (__cdecl *)(struct QTask_s *, void *))CarType_GetGetPhysicsObjTypeSizeHandler);
}

// source: j/0/vehicles/cartype.c:125  [size]
void __cdecl CarType_Close()
{
  ;
}
