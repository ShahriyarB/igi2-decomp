/* j/0/menusystem/backgroundfx.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/menusystem/backgroundfx.c:198  [anchor-mhash]
int __cdecl BackgroundFX_CreateMatrix(
        struct Matrix2d_t *ptMatrix,
        float vAngle,
        float vScale,
        float vPivotX,
        float vPivotY)
{
  long double v5; // st7
  long double v6; // st6

  ptMatrix->vTX = vPivotX;
  ptMatrix->vTY = vPivotY;
  ptMatrix->vScale = vScale;
  v5 = cos(vAngle) * vScale;
  ptMatrix->vM00 = v5;
  v6 = sin(vAngle);
  ptMatrix->vM01 = vScale * v6;
  ptMatrix->vM10 = -v6 * vScale;
  ptMatrix->vM11 = v5;
  return (int)ptMatrix;
}

// source: j/0/menusystem/backgroundfx.c:222  [anchor-mhash]
int __cdecl BackgroundFX_DrawGrid(struct GridFX_t *ptGridFX, struct Matrix2d_t *ptMatrix)
{
  #pragma pack(push, 1)
  union
  {
    struct { float vX0; };
    struct { float vX0a; };
    struct { char igi2_o2[4]; float vY0; };
    struct { char igi2_o3[4]; float vY0a; };
    struct { char igi2_o4[8]; float vHeightY; };
    struct { char igi2_o5[12]; float vStepY; };
    struct { char igi2_o6[12]; float vStepYa; };
    struct { char igi2_o7[16]; float vWidthY; };
    struct { char igi2_o8[20]; float vStepX; };
    struct { char igi2_o9[20]; float vStepXa; };
    struct { char igi2_o10[24]; float vWidthX; };
    struct { char igi2_o11[28]; float vHeightX; };
    struct { char igi2_o12[32]; float v24; };
    struct { char igi2_o13[36]; float v25; };
    struct { char igi2_o14[40]; struct QVertexStripContext_s tContext; };
    struct { char igi2_o15[60]; struct QVertex_s atQVertex[2]; };
    char igi2_extent[132];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  float *p_vG; // eax
  int v3; // edx
  int v4; // edi
  double v5; // st7
  double v6; // st6
  int v7; // ebx
  bool v8; // sf
  double v9; // st7
  double v10; // st6
  int result; // eax

  p_vG = &igi2_frame.atQVertex[0].vG;
  v3 = 2;
  v4 = 0;
  do
  {
    *(p_vG - 1) = 0.4000000059604645;
    *p_vG = 0.6000000238418579;
    p_vG[1] = 1.0;
    *(p_vG - 2) = 0.07500000298023224;
    *(p_vG - 4) = 0.0;
    *(p_vG - 3) = 0.0;
    *(p_vG - 5) = 1.0;
    p_vG += 9;
    --v3;
  }
  while ( v3 );
  v5 = ptGridFX->vCentreX * ptMatrix->vM00;
  igi2_frame.tContext.atQVertex = igi2_frame.atQVertex;
  v6 = ptGridFX->vCentreY * ptMatrix->vM10;
  v7 = 0;
  v8 = ptGridFX->nXLines < 0;
  igi2_frame.tContext.bFlags = 0x80000;
  igi2_frame.tContext.isLine = 1;
  igi2_frame.tContext.nDepth = 0;
  igi2_frame.tContext.nStripLength = 2;
  v9 = v5 + v6 + ptMatrix->vTX;
  v10 = ptMatrix->vM11 * ptGridFX->vCentreY + ptMatrix->vM01 * ptGridFX->vCentreX + ptMatrix->vTY;
  igi2_frame.vWidthX = ptGridFX->vWidth * ptMatrix->vM00 + ptMatrix->vM10 * 0.0;
  igi2_frame.vWidthY = ptMatrix->vM01 * ptGridFX->vWidth + ptMatrix->vM11 * 0.0;
  igi2_frame.vHeightX = ptMatrix->vM10 * ptGridFX->vHeight + ptMatrix->vM00 * 0.0;
  igi2_frame.vHeightY = ptMatrix->vM11 * ptGridFX->vHeight + ptMatrix->vM01 * 0.0;
  igi2_frame.v24 = v9 - (igi2_frame.vHeightX + igi2_frame.vWidthX) * 0.5;
  igi2_frame.vX0 = igi2_frame.v24;
  igi2_frame.v25 = v10 - (igi2_frame.vHeightY + igi2_frame.vWidthY) * 0.5;
  igi2_frame.vY0 = igi2_frame.v25;
  if ( !v8 )
  {
    do
    {
      igi2_frame.atQVertex[0].vX = igi2_frame.vX0;
      igi2_frame.atQVertex[1].vX = igi2_frame.vX0 + igi2_frame.vWidthX;
      igi2_frame.atQVertex[0].vY = igi2_frame.vY0;
      igi2_frame.atQVertex[1].vY = igi2_frame.vY0 + igi2_frame.vWidthY;
      igi2_frame.vStepX = igi2_frame.vHeightX * 0.05000000074505806;
      igi2_frame.vX0 = igi2_frame.vStepX + igi2_frame.vX0;
      igi2_frame.vStepY = igi2_frame.vHeightY * 0.05000000074505806;
      igi2_frame.vY0 = igi2_frame.vStepY + igi2_frame.vY0;
      RenderMode_tActiveRenderMode.apfRenderModeMethod[QVertex_eRegisterQVertexStripMethod](&igi2_frame.tContext);
      ++v7;
    }
    while ( v7 <= ptGridFX->nXLines );
  }
  result = ptGridFX->nYLines;
  igi2_frame.vX0a = v9 - (igi2_frame.vHeightX + igi2_frame.vWidthX) * 0.5;
  igi2_frame.vY0a = v10 - (igi2_frame.vHeightY + igi2_frame.vWidthY) * 0.5;
  if ( result >= 0 )
  {
    do
    {
      igi2_frame.atQVertex[0].vX = igi2_frame.vX0a;
      igi2_frame.atQVertex[1].vX = igi2_frame.vX0a + igi2_frame.vHeightX;
      igi2_frame.atQVertex[0].vY = igi2_frame.vY0a;
      igi2_frame.atQVertex[1].vY = igi2_frame.vY0a + igi2_frame.vHeightY;
      igi2_frame.vStepXa = igi2_frame.vWidthX * 0.05000000074505806;
      igi2_frame.vX0a = igi2_frame.vStepXa + igi2_frame.vX0a;
      igi2_frame.vStepYa = igi2_frame.vWidthY * 0.05000000074505806;
      igi2_frame.vY0a = igi2_frame.vStepYa + igi2_frame.vY0a;
      RenderMode_tActiveRenderMode.apfRenderModeMethod[QVertex_eRegisterQVertexStripMethod](&igi2_frame.tContext);
      result = ptGridFX->nYLines;
      ++v4;
    }
    while ( v4 <= result );
  }
  return result;
}

// source: j/0/menusystem/backgroundfx.c:313  [anchor-mhash]
int __cdecl BackgroundFX_DrawLineFX(struct LineFX_t *ptLineFX, struct Matrix2d_t *ptMatrix)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct QVertexStripContext_s tContext; };
    struct { char igi2_o1[20]; struct QVertex_s atQVertex[2]; };
    char igi2_extent[92];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  float *p_vG; // eax
  int v3; // ecx
  int v4; // ebx
  int result; // eax
  bool v6; // cc
  float *avPoints; // edi

  p_vG = &igi2_frame.atQVertex[0].vG;
  v3 = 2;
  v4 = 0;
  do
  {
    *(p_vG - 1) = 0.4000000059604645;
    *p_vG = 0.6000000238418579;
    p_vG[1] = 1.0;
    *(p_vG - 2) = 0.07500000298023224;
    *(p_vG - 4) = 0.0;
    *(p_vG - 3) = 0.0;
    *(p_vG - 5) = 1.0;
    p_vG += 9;
    --v3;
  }
  while ( v3 );
  result = (int)igi2_frame.atQVertex;
  igi2_frame.tContext.atQVertex = igi2_frame.atQVertex;
  v6 = ptLineFX->nPoint <= 0;
  igi2_frame.tContext.bFlags = 0x80000;
  igi2_frame.tContext.isLine = 1;
  igi2_frame.tContext.nDepth = 0;
  igi2_frame.tContext.nStripLength = 2;
  avPoints = ptLineFX->avPoints;
  if ( !v6 )
  {
    do
    {
      igi2_frame.atQVertex[0].vX = avPoints[1] * ptMatrix->vM10 + *avPoints * ptMatrix->vM00 + ptMatrix->vTX;
      igi2_frame.atQVertex[0].vY = avPoints[1] * ptMatrix->vM11 + *avPoints * ptMatrix->vM01 + ptMatrix->vTY;
      igi2_frame.atQVertex[1].vX = avPoints[2] * ptMatrix->vM00 + avPoints[3] * ptMatrix->vM10 + ptMatrix->vTX;
      igi2_frame.atQVertex[1].vY = avPoints[2] * ptMatrix->vM01 + avPoints[3] * ptMatrix->vM11 + ptMatrix->vTY;
      RenderMode_tActiveRenderMode.apfRenderModeMethod[QVertex_eRegisterQVertexStripMethod](&igi2_frame.tContext);
      result = ptLineFX->nPoint;
      ++v4;
      avPoints += 4;
    }
    while ( v4 < ptLineFX->nPoint );
  }
  return result;
}

// source: j/0/menusystem/backgroundfx.c:365  [anchor-mhash]
int __cdecl BackgroundFX_DrawCircle(struct CircleFX_t *ptCircleFX, struct Matrix2d_t *ptMatrix)
{
  #pragma pack(push, 1)
  union
  {
    struct { float vRadius; };
    struct { char igi2_o1[12]; float vCentreX; };
    struct { char igi2_o2[16]; float vCentreY; };
    struct { char igi2_o3[20]; struct QVertexStripContext_s tContext; };
    struct { char igi2_o4[40]; struct QVertex_s atQVertex[41]; };
    char igi2_extent[1516];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  long double v2; // st7
  double v3; // st6
  int v4; // ebp
  int v5; // eax
  float *p_vG; // eax
  int v7; // ecx
  int v8; // edx

  v2 = 0.0;
  igi2_frame.vCentreX = ptMatrix->vM10 * ptCircleFX->vCentreY + ptCircleFX->vCentreX * ptMatrix->vM00 + ptMatrix->vTX;
  igi2_frame.vCentreY = ptMatrix->vM01 * ptCircleFX->vCentreX + ptMatrix->vM11 * ptCircleFX->vCentreY + ptMatrix->vTY;
  v3 = ptCircleFX->vRadius * ptMatrix->vScale;
  igi2_frame.vRadius = v3;
  v4 = (__int64)(v3 * 0.3141592741012573);
  if ( v4 >= 40 )
    v4 = 40;
  v5 = 0;
  if ( v4 > 0 )
  {
    p_vG = &igi2_frame.atQVertex[0].vG;
    v7 = v4;
    do
    {
      *(p_vG - 1) = 0.4000000059604645;
      *p_vG = 0.6000000238418579;
      p_vG[1] = 1.0;
      *(p_vG - 2) = 0.07500000298023224;
      *(p_vG - 4) = 0.0;
      *(p_vG - 3) = 0.0;
      *(p_vG - 5) = 1.0;
      p_vG += 9;
      --v7;
      *(p_vG - 16) = cos(v2) * igi2_frame.vRadius + igi2_frame.vCentreX;
      *(p_vG - 15) = sin(v2) * igi2_frame.vRadius + igi2_frame.vCentreY;
      v2 = v2 + 6.2831854820251465 / (double)v4;
    }
    while ( v7 );
    v5 = v4;
  }
  v8 = QVertex_eRegisterQVertexStripMethod;
  qmemcpy(&igi2_frame.atQVertex[v5], igi2_frame.atQVertex, sizeof(struct QVertex_s));
  igi2_frame.tContext.bFlags = 0x80000;
  igi2_frame.tContext.isLine = 1;
  igi2_frame.tContext.nDepth = 0;
  igi2_frame.tContext.nStripLength = v4 + 1;
  igi2_frame.tContext.atQVertex = igi2_frame.atQVertex;
  return ((int (__cdecl *)(struct QVertexStripContext_s *))RenderMode_tActiveRenderMode.apfRenderModeMethod[v8])(&igi2_frame.tContext);
}

// source: j/0/menusystem/backgroundfx.c:427  [anchor-mhash]
struct Matrix2d_t *__cdecl BackgroundFX_DrawSingleObject(
        struct ObjectFX_t *ptObjectFX,
        struct Matrix2d_t *ptMatrix)
{
  struct Matrix2d_t *result; // eax
  int v5; // ebx
  int v6; // ebp
  struct GridFX_t *ptGrid; // edi

  if ( ptObjectFX->ptLine )
    BackgroundFX_DrawLineFX(ptObjectFX->ptLine, ptMatrix);
  result = (struct Matrix2d_t *)ptObjectFX->nCircleEffect;
  v5 = 0;
  if ( (int)result > 0 )
  {
    v6 = 0;
    do
    {
      BackgroundFX_DrawCircle(&ptObjectFX->ptCircle[v6], ptMatrix);
      result = (struct Matrix2d_t *)ptObjectFX->nCircleEffect;
      ++v5;
      ++v6;
    }
    while ( v5 < (int)result );
  }
  ptGrid = ptObjectFX->ptGrid;
  if ( ptGrid )
    return (struct Matrix2d_t *)BackgroundFX_DrawGrid(ptGrid, ptMatrix);
  return result;
}

// source: j/0/menusystem/backgroundfx.c:455  [anchor-mhash]
void __cdecl BackgroundFX_DrawAllObjects(struct BackgroundFX_t *ptBackgroundFX, float vTime)
{
  #pragma pack(push, 1)
  union
  {
    struct { float ptObjectFX; };
    struct { float ptObjectFXa; };
    struct { char igi2_o2[4]; struct Matrix2d_t tMatrix; };
    char igi2_extent[32];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  long double v2; // st7
  long double v3; // st6
  long double v4; // st5
  long double v5; // st7
  long double v6; // st6
  long double v7; // st5
  long double v8; // st7
  long double v9; // st6
  long double v10; // st5
  float vTimea = *(float *)&vTime; // [esp+28h] [ebp+8h] ARGSLOT

  igi2_frame.tMatrix.vTX = 200.0;
  igi2_frame.tMatrix.vTY = 300.0;
  v2 = cos(vTime * 0.004999999888241291) * 0.25 + 1.25;
  v3 = vTime * 0.0020000000949949026;
  igi2_frame.ptObjectFX = v3;
  igi2_frame.tMatrix.vM00 = cos(v3) * v2;
  v4 = sin(igi2_frame.ptObjectFX);
  igi2_frame.tMatrix.vM01 = v4 * v2;
  igi2_frame.tMatrix.vM10 = -v4 * v2;
  igi2_frame.tMatrix.vM11 = igi2_frame.tMatrix.vM00;
  igi2_frame.tMatrix.vScale = v2;
  BackgroundFX_DrawSingleObject(BackgroundFX_atObjects, &igi2_frame.tMatrix);
  igi2_frame.tMatrix.vTX = 400.0;
  igi2_frame.tMatrix.vTY = 250.0;
  v5 = cos(vTime * 0.0024999999441206455) * 0.15000000596046448 + 1.149999976158142;
  v6 = vTime * -0.0014285714132711291;
  igi2_frame.ptObjectFXa = v6;
  igi2_frame.tMatrix.vM00 = cos(v6) * v5;
  v7 = sin(igi2_frame.ptObjectFXa);
  igi2_frame.tMatrix.vM01 = v7 * v5;
  igi2_frame.tMatrix.vM10 = -v7 * v5;
  igi2_frame.tMatrix.vM11 = igi2_frame.tMatrix.vM00;
  igi2_frame.tMatrix.vScale = v5;
  BackgroundFX_DrawSingleObject(&BackgroundFX_atObjects[1], &igi2_frame.tMatrix);
  igi2_frame.tMatrix.vTX = 150.0;
  igi2_frame.tMatrix.vTY = 250.0;
  v8 = sin(vTime * 0.0033333334140479565) + 2.0;
  v9 = vTime * 0.0011111111380159855;
  vTimea = v9;
  igi2_frame.tMatrix.vM00 = cos(v9) * v8;
  v10 = sin(vTimea);
  igi2_frame.tMatrix.vM01 = v10 * v8;
  igi2_frame.tMatrix.vM10 = -v10 * v8;
  igi2_frame.tMatrix.vM11 = igi2_frame.tMatrix.vM00;
  igi2_frame.tMatrix.vScale = v8;
  BackgroundFX_DrawSingleObject(&BackgroundFX_atObjects[2], &igi2_frame.tMatrix);
}

// source: j/0/menusystem/backgroundfx.c:482  [size]
void __cdecl BackgroundFX_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ptQTask[1].ptNext = nullptr;
}

// source: j/0/menusystem/backgroundfx.c:516  [size]
void __cdecl BackgroundFX_DeleteHandler(struct QTask_s *ptQTask)
{
  ;
}

// source: j/0/menusystem/backgroundfx.c:529  [size]
void __cdecl BackgroundFX_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ;
}

// source: j/0/menusystem/backgroundfx.c:541  [size]
void __cdecl BackgroundFX_RunHandler(struct QTask_s *ptQTask)
{
  *(float *)&ptQTask[1].ptNext = *(float *)&ptQTask[1].ptNext + 1.0;
}

// source: j/0/menusystem/backgroundfx.c:558  [anchor-mhash]
void __cdecl BackgroundFX_DrawHandler(struct QTask_s *ptQTask)
{
  float vTime; // [esp+0h] [ebp-8h]
  struct QTask_s *ptQTaska = *(struct QTask_s * *)&ptQTask; // [esp+Ch] [ebp+4h] ARGSLOT

  ptQTaska = ptQTask[1].ptNext;
  QVertex_ptActiveTexture = nullptr;
  QVertex_ptActivePalette = nullptr;
  BackgroundFX_DrawAllObjects((struct BackgroundFX_t *)ptQTask, *(float *)&ptQTaska);
  vTime = *(float *)&ptQTaska + 1.0;
  BackgroundFX_DrawAllObjects((struct BackgroundFX_t *)ptQTask, vTime);
}

// source: j/0/menusystem/backgroundfx.c:586  [anchor-hash]
void __cdecl BackgroundFX_Open()
{
  unsigned __int16 BaseQTaskType; // ax
  unsigned __int16 v1; // si

  BaseQTaskType = QTask_GetBaseQTaskType();
  v1 = QTask_NewQTaskType("BackgroundFX", 44, BaseQTaskType, 0, 0);
  BackgroundFX_eQTaskType = v1;
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 1, (void (__cdecl *)(struct QTask_s *))BackgroundFX_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, Screen_eDrawQTaskEvent, BackgroundFX_DrawHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 2, (void (__cdecl *)(struct QTask_s *))BackgroundFX_DeleteHandler);
  QTask_LinkQTaskEventHandlerFn(v1, 0, (void (__cdecl *)(struct QTask_s *, void *))BackgroundFX_CreateHandler);
  QTask_LinkQTaskEventHandlerFn(
    v1,
    ParameterList_eUpdateInternalDataQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))BackgroundFX_UpdateInternalDataHandler);
}

// source: j/0/menusystem/backgroundfx.c:612  [size]
void __cdecl BackgroundFX_Close()
{
  QTask_DeleteQTaskType(BackgroundFX_eQTaskType);
  BackgroundFX_eQTaskType = 512;
}

// source: j/0/menusystem/backgroundfx.c:631  [size]
struct QTask_s *__cdecl BackgroundFX_New(struct QTask_s *ptParent)
{
  return QTask_NewFn(ptParent, BackgroundFX_eQTaskType, nullptr);
}

// source: j/0/menusystem/backgroundfx.c:650  [size]
void __cdecl BackgroundFX_Delete()
{
  struct QTask_s *v0; // eax

  QTask_Delete(v0);
}
