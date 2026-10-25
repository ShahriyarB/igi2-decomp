/* b/2/pc/pc_transcontext.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: b/2/pc/pc_transcontext.c:91  [size]
void __cdecl TransContext_SetTransContextCB(void *pxData)
{
  if ( pxData )
    TransContext_SetActiveTransContext((struct TransContext_s *)((char *)pxData + 16));
}

// source: b/2/pc/pc_transcontext.c:112  [size]
void __cdecl Direct3D_SetActiveTransContext(struct SetActiveTransContextContext_t *ptContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct _D3DVIEWPORT8 tViewport; };
    struct { char igi2_o1[24]; int w; };
    struct { char igi2_o2[28]; float h; };
    struct { char igi2_o3[32]; struct _D3DMATRIX tView; };
    struct { char igi2_o4[96]; struct _D3DMATRIX tProjection; };
    struct { char igi2_o5[160]; char zString[1024]; };
    char igi2_extent[1184];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct TransContext_s *ptTransContext; // ecx
  struct TransContext_s *v2; // eax
  double v3; // st7
  enum TransContext_Layer_e eLayer; // eax
  unsigned int v5; // ecx
  int v6; // esi
  char *v7; // eax
  double v8; // st7
  double v9; // st6
  unsigned int nHeight; // eax
  int v11; // esi
  char *ErrorString; // eax
  unsigned int v13; // eax
  int v14; // esi
  char *v15; // eax
  unsigned int v16; // eax
  int v17; // esi
  char *v18; // eax
  struct TransContext_s *v19; // edx
  int v20; // esi
  char *v21; // eax
  struct TransContext_s *v22; // ebx
  int v23; // esi
  char *v24; // eax

  ptContext->ptTransContext->vFOVX = ptContext->ptTransContext->vFOVY
                                   * 4.0
                                   / ((double)Display_tActiveMode.nHeight
                                    * 4.0
                                    / ((double)Display_tActiveMode.nWidth
                                     * 3.0)
                                    * 3.0);
  ptTransContext = ptContext->ptTransContext;
  igi2_frame.w = ptContext->nWidth / 2;
  ptTransContext->vScreenFOVX = (double)igi2_frame.w / ptTransContext->vFOVX;
  v2 = ptContext->ptTransContext;
  *(float *)&igi2_frame.w = 1.0 / ptContext->ptTransContext->vFOVX;
  v3 = -1.0 / v2->vFOVY;
  eLayer = v2->eLayer;
  igi2_frame.h = v3;
  if ( eLayer )
  {
    switch ( eLayer )
    {
      case TRANSCONTEXT_LAYER_MIDDLE:
        nHeight = ptContext->nHeight;
        igi2_frame.tViewport.Width = ptContext->nWidth;
        igi2_frame.tViewport.MaxZ = Direct3D_vMaxZ;
        igi2_frame.tViewport.Height = nHeight;
        igi2_frame.tViewport.X = 0;
        igi2_frame.tViewport.Y = 0;
        igi2_frame.tViewport.MinZ = Direct3D_vMinZ;
        v11 = Direct3D_ptDevice->lpVtbl->SetViewport(Direct3D_ptDevice, &igi2_frame.tViewport);
        if ( v11 )
        {
          sprintf(igi2_frame.zString, "Couldn't set viewport");
          ErrorString = Direct3D_GetErrorString(v11);
          LDebug_Error(
            "%s\n\nDirectX error message: %s\nFile: %s Line: %d",
            igi2_frame.zString,
            ErrorString,
            "\\project\\igi2\\B\\2\\PC\\pc_transcontext.c",
            157);
          goto LABEL_4;
        }
        v8 = Direct3D_vD3DMinZ;
        v9 = Direct3D_vD3DMaxZ / (Direct3D_vD3DMaxZ - Direct3D_vD3DMinZ);
        break;
      case TRANSCONTEXT_LAYER_BACK:
        v13 = ptContext->nHeight;
        igi2_frame.tViewport.Width = ptContext->nWidth;
        igi2_frame.tViewport.MaxZ = Direct3D_vBackgroundMaxZ;
        igi2_frame.tViewport.Height = v13;
        igi2_frame.tViewport.X = 0;
        igi2_frame.tViewport.Y = 0;
        igi2_frame.tViewport.MinZ = Direct3D_vBackgroundMinZ;
        v14 = Direct3D_ptDevice->lpVtbl->SetViewport(Direct3D_ptDevice, &igi2_frame.tViewport);
        if ( v14 )
        {
          sprintf(igi2_frame.zString, "Couldn't set viewport");
          v15 = Direct3D_GetErrorString(v14);
          LDebug_Error(
            "%s\n\nDirectX error message: %s\nFile: %s Line: %d",
            igi2_frame.zString,
            v15,
            "\\project\\igi2\\B\\2\\PC\\pc_transcontext.c",
            169);
          goto LABEL_4;
        }
        v8 = Direct3D_vD3DBackgroundMinZ;
        v9 = Direct3D_vD3DBackgroundMaxZ / (Direct3D_vD3DBackgroundMaxZ - Direct3D_vD3DBackgroundMinZ);
        break;
      case TRANSCONTEXT_LAYER_HEMICUBE:
        v16 = ptContext->nHeight;
        igi2_frame.tViewport.Width = ptContext->nWidth;
        igi2_frame.tViewport.Height = v16;
        igi2_frame.tViewport.X = 0;
        igi2_frame.tViewport.Y = 0;
        igi2_frame.tViewport.MinZ = 0.0;
        igi2_frame.tViewport.MaxZ = 1.0;
        v17 = Direct3D_ptDevice->lpVtbl->SetViewport(Direct3D_ptDevice, &igi2_frame.tViewport);
        if ( v17 )
        {
          sprintf(igi2_frame.zString, "Couldn't set viewport");
          v18 = Direct3D_GetErrorString(v17);
          LDebug_Error(
            "%s\n\nDirectX error message: %s\nFile: %s Line: %d",
            igi2_frame.zString,
            v18,
            "\\project\\igi2\\B\\2\\PC\\pc_transcontext.c",
            181);
          goto LABEL_4;
        }
        v8 = Direct3D_vScale * 327.67999267578125;
        v9 = Direct3D_vScale * 4096000000.0 / (Direct3D_vScale * 4096000000.0 - v8);
        break;
      default:
        LDebug_Error("Invalid layer");
LABEL_4:
        abort();
    }
  }
  else
  {
    v5 = ptContext->nHeight;
    igi2_frame.tViewport.Width = ptContext->nWidth;
    igi2_frame.tViewport.MinZ = Direct3D_vOverlayMinZ;
    LODWORD(igi2_frame.tViewport.MaxZ) = dword_84B829C;
    igi2_frame.tViewport.X = 0;
    igi2_frame.tViewport.Y = 0;
    igi2_frame.tViewport.Height = v5;
    v6 = Direct3D_ptDevice->lpVtbl->SetViewport(Direct3D_ptDevice, &igi2_frame.tViewport);
    if ( v6 )
    {
      sprintf(igi2_frame.zString, "Couldn't set viewport");
      v7 = Direct3D_GetErrorString(v6);
      LDebug_Error(
        "%s\n\nDirectX error message: %s\nFile: %s Line: %d",
        igi2_frame.zString,
        v7,
        "\\project\\igi2\\B\\2\\PC\\pc_transcontext.c",
        145);
      goto LABEL_4;
    }
    v8 = Direct3D_vD3DOverlayMinZ;
    v9 = Direct3D_vD3DOverlayMaxZ / (Direct3D_vD3DOverlayMaxZ - Direct3D_vD3DOverlayMinZ);
  }
  v19 = ptContext->ptTransContext;
  if ( ptContext->ptTransContext->eLayer != TRANSCONTEXT_LAYER_HEMICUBE )
  {
    memset(&igi2_frame.tProjection, 0, sizeof(igi2_frame.tProjection));
    igi2_frame.tProjection._33 = v9;
    igi2_frame.tProjection._43 = -(v9 * v8);
    igi2_frame.tProjection._22 = igi2_frame.h;
    LODWORD(igi2_frame.tProjection._11) = igi2_frame.w;
    igi2_frame.tProjection._34 = 1.0;
    qmemcpy(&v19->tProjection, &igi2_frame.tProjection, sizeof(v19->tProjection));
  }
  v20 = Direct3D_ptDevice->lpVtbl->SetTransform(
          Direct3D_ptDevice,
          D3DTS_PROJECTION,
          &ptContext->ptTransContext->tProjection);
  if ( v20 )
  {
    sprintf(igi2_frame.zString, "Couldn't set projection matrix");
    v21 = Direct3D_GetErrorString(v20);
    LDebug_Error(
      "%s\n\nDirectX error message: %s\nFile: %s Line: %d",
      igi2_frame.zString,
      v21,
      "\\project\\igi2\\B\\2\\PC\\pc_transcontext.c",
      207);
    goto LABEL_4;
  }
  v22 = ptContext->ptTransContext;
  igi2_frame.tView._11 = ptContext->ptTransContext->tMatrix.tX.vX;
  igi2_frame.tView._12 = v22->tMatrix.tY.vX;
  *(_QWORD *)&igi2_frame.tView.m[0][2] = LODWORD(v22->tMatrix.tZ.vX);
  igi2_frame.tView._21 = v22->tMatrix.tX.vY;
  igi2_frame.tView._22 = v22->tMatrix.tY.vY;
  *(_QWORD *)&igi2_frame.tView.m[1][2] = LODWORD(v22->tMatrix.tZ.vY);
  igi2_frame.tView._31 = v22->tMatrix.tX.vZ;
  igi2_frame.tView._32 = v22->tMatrix.tY.vZ;
  *(_QWORD *)&igi2_frame.tView.m[2][2] = LODWORD(v22->tMatrix.tZ.vZ);
  *(_QWORD *)&igi2_frame.tView.m[3][0] = 0;
  *(_QWORD *)&igi2_frame.tView.m[3][2] = 0x3F80000000000000LL;
  v23 = Direct3D_ptDevice->lpVtbl->SetTransform(Direct3D_ptDevice, D3DTS_VIEW, &igi2_frame.tView);
  if ( v23 )
  {
    sprintf(igi2_frame.zString, "Couldn't set view matrix");
    v24 = Direct3D_GetErrorString(v23);
    LDebug_Error(
      "%s\n\nDirectX error message: %s\nFile: %s Line: %d",
      igi2_frame.zString,
      v24,
      "\\project\\igi2\\B\\2\\PC\\pc_transcontext.c",
      211);
    goto LABEL_4;
  }
}

// source: b/2/pc/pc_transcontext.c:223  [size]
void __cdecl Direct3D_SetNearClippingPlane(struct SetNearClippingPlaneContext_t *ptContext)
{
  struct SetActiveTransContextContext_t tSetActiveTransContextContext; // [esp+4h] [ebp-Ch] BYREF

  Direct3D_vWorldMinZ = ptContext->vNearClippingPlane;
  Direct3D_vD3DMinZ = Direct3D_vScale * Direct3D_vWorldMinZ;
  tSetActiveTransContextContext.ptTransContext = &TransContext_tActiveTransContext;
  tSetActiveTransContextContext.nWidth = Display_tActiveMode.nWidth;
  tSetActiveTransContextContext.nHeight = Display_tActiveMode.nHeight;
  Direct3D_SetActiveTransContext(&tSetActiveTransContextContext);
  ptContext->isLowresZBuffer = Direct3D_isLowresZBuffer;
}

// source: b/2/pc/pc_transcontext.c:253  [size]
int __cdecl TransContext_SetOptimizeZBuffer(int isOn)
{
  TransContext_isOptimizeZBuffer = isOn;
  return isOn;
}

// source: b/2/pc/pc_transcontext.c:292  [size]
void __cdecl TransContext_RenderModeEnumerateCallback(
        struct RenderModeEnumerateContext_s *ptRenderModeEnumerateContext,
        void *pxUnused)
{
  RenderMode_atRenderMode[ptRenderModeEnumerateContext->eRenderMode].apfRenderModeMethod[TransContext_ePrimType] = TransContext_SetTransContextCB;
}

// source: b/2/pc/pc_transcontext.c:305  [size]
void __cdecl TransContext_Open()
{
  int v0; // eax
  int v1; // ecx
  int v2; // eax
  __int32 v3; // edx

  TransContext_isValid = 0;
  v0 = 0;
  while ( RenderMode_atRenderModeMethod[v0].isAllocated )
  {
    if ( ++v0 >= 128 )
    {
      LDebug_Error("RenderMode: Failed to create new method '%s'", "TransContextPrimitive");
      goto LABEL_5;
    }
  }
  RenderMode_atRenderModeMethod[v0].zName = "TransContextPrimitive";
  RenderMode_atRenderModeMethod[v0].isAllocated = 1;
  TransContext_ePrimType = v0;
  RenderMode_EnumerateRenderModes(
    (void (__cdecl *)(struct RenderModeEnumerateContext_s *, void *))TransContext_RenderModeEnumerateCallback,
    nullptr);
  v1 = 0;
  while ( RenderMode_atRenderModeMethod[v1].isAllocated )
  {
    if ( ++v1 >= 128 )
    {
      LDebug_Error("RenderMode: Failed to create new method '%s'", "SetActiveTransContext");
      goto LABEL_5;
    }
  }
  RenderMode_atRenderModeMethod[v1].zName = "SetActiveTransContext";
  RenderMode_atRenderModeMethod[v1].isAllocated = 1;
  TransContext_eSetActiveTransContextRenderModeMethod = v1;
  v2 = 0;
  while ( RenderMode_atRenderModeMethod[v2].isAllocated )
  {
    if ( ++v2 >= 128 )
    {
      LDebug_Error("RenderMode: Failed to create new method '%s'", "SetNearClippingPlane");
LABEL_5:
      abort();
    }
  }
  RenderMode_atRenderModeMethod[v2].isAllocated = 1;
  TransContext_isOptimizeZBuffer = 1;
  v3 = v2 + 130 * Direct3D_eRenderMode;
  RenderMode_atRenderMode[Direct3D_eRenderMode].apfRenderModeMethod[v1] = (void (__cdecl *)(void *))Direct3D_SetActiveTransContext;
  RenderMode_atRenderModeMethod[v2].zName = "SetNearClippingPlane";
  TransContext_eSetNearClippingPlaneMethod = v2;
  RenderMode_atRenderMode[0].apfRenderModeMethod[v3] = (void (__cdecl *)(void *))Direct3D_SetNearClippingPlane;
}

// source: b/2/pc/pc_transcontext.c:331  [anchor-hash]
void __cdecl TransContext_Close()
{
  int v0; // edx

  v0 = TransContext_eSetActiveTransContextRenderModeMethod;
  RenderMode_atRenderModeMethod[TransContext_eSetNearClippingPlaneMethod].isAllocated = 0;
  RenderMode_atRenderModeMethod[v0].isAllocated = 0;
  TransContext_ePrimType = -1;
  TransContext_isValid = 0;
}

// source: b/2/pc/pc_transcontext.c:355  [anchor-callee]
struct TransContext_s *__cdecl TransContext_Create(
        struct TransContext_s *ptTransContext,
        struct real32x9_t *ptMatrix,
        struct real64x3_t *ptPos,
        float vFOVX)
{
  float vX; // edx
  float vY; // ecx
  float v6; // edx
  float vZ; // ecx
  float v8; // edx
  float v9; // ecx
  float v10; // edx
  double v11; // st7
  double v12; // st7
  struct real32x9_t Real32x9_Invert_tTemp; // [esp+8h] [ebp-28h] BYREF

  qmemcpy(ptTransContext, ptMatrix, 0x28u);
  vX = ptTransContext->tMatrix.tY.vX;
  Real32x9_Invert_tTemp.tX.vX = ptTransContext->tMatrix.tX.vX;
  Real32x9_Invert_tTemp.tX.vZ = ptTransContext->tMatrix.tZ.vX;
  vY = ptTransContext->tMatrix.tY.vY;
  Real32x9_Invert_tTemp.tX.vY = vX;
  v6 = ptTransContext->tMatrix.tX.vY;
  Real32x9_Invert_tTemp.tY.vY = vY;
  vZ = ptTransContext->tMatrix.tX.vZ;
  Real32x9_Invert_tTemp.tY.vX = v6;
  v8 = ptTransContext->tMatrix.tZ.vY;
  Real32x9_Invert_tTemp.tZ.vX = vZ;
  v9 = ptTransContext->tMatrix.tZ.vZ;
  Real32x9_Invert_tTemp.tY.vZ = v8;
  v10 = ptTransContext->tMatrix.tY.vZ;
  Real32x9_Invert_tTemp.tZ.vZ = v9;
  Real32x9_Invert_tTemp.tZ.vY = v10;
  Real32x9_Invert_tTemp.nOps = ptTransContext->tMatrix.nOps;
  qmemcpy(ptTransContext, &Real32x9_Invert_tTemp, 0x28u);
  qmemcpy(&ptTransContext->tPos, ptPos, sizeof(ptTransContext->tPos));
  ptTransContext->vFOVX = vFOVX;
  ptTransContext->vFOVY = RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vHeight
                        * vFOVX
                        / ((double)Display_tActiveMode.nHeight
                         * 4.0
                         / ((double)Display_tActiveMode.nWidth
                          * 3.0)
                         * RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vWidth);
  v11 = RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vHalfWidth / vFOVX;
  ptTransContext->vScreenFOVX = v11;
  ptTransContext->vScreenFOVY = (double)Display_tActiveMode.nHeight
                              * 4.0
                              / ((double)Display_tActiveMode.nWidth
                               * 3.0)
                              * v11;
  ptTransContext->vScreenOriginX = RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vX
                                 + RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vHalfWidth;
  v12 = RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vY
      + RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vHalfHeight;
  ptTransContext->isDraw = 1;
  ptTransContext->eLayer = TRANSCONTEXT_LAYER_MIDDLE;
  ptTransContext->vScreenOriginY = v12;
  return ptTransContext;
}

// source: b/2/pc/pc_transcontext.c:393  [size]
int __cdecl TransContext_SetDraw(struct TransContext_s *ptTransContext, int isDraw)
{
  ptTransContext->isDraw = isDraw;
  return isDraw;
}

// source: b/2/pc/pc_transcontext.c:405  [size]
void __cdecl TransContext_SetBackFaceSign(
        struct TransContext_s *ptTransContext,
        float vBackFaceSign)
{
  ptTransContext->vBackFaceSign = vBackFaceSign;
}

// source: b/2/pc/pc_transcontext.c:421  [anchor-callee]
struct TransContext_s *__cdecl TransContext_SetActiveTransContext(struct TransContext_s *ptTransContext)
{
  struct TransContext_s *result; // eax
  struct SetActiveTransContextContext_t tContext; // [esp+8h] [ebp-Ch] BYREF

  qmemcpy(&TransContext_tActiveTransContext, ptTransContext, sizeof(TransContext_tActiveTransContext));
  tContext.nWidth = Display_tActiveMode.nWidth;
  result = (struct TransContext_s *)RenderMode_tActiveRenderMode.apfRenderModeMethod[TransContext_eSetActiveTransContextRenderModeMethod];
  tContext.ptTransContext = &TransContext_tActiveTransContext;
  tContext.nHeight = Display_tActiveMode.nHeight;
  if ( result )
    result = (struct TransContext_s *)((int (__cdecl *)(struct SetActiveTransContextContext_t *))result)(&tContext);
  ++TransContext_nActiveTransContextTimeStamp;
  TransContext_isValid = 1;
  return result;
}

// source: b/2/pc/pc_transcontext.c:449  [anchor-mhash]
struct TransContext_s *__cdecl TransContext_SetHemicubeTransContext(
        struct TransContext_s *ptTransContext,
        int nWidth,
        int nHeight,
        float vAspectRatio)
{
  double v4; // st6
  double v5; // st5
  struct TransContext_s *result; // eax
  double v7; // st4
  struct SetActiveTransContextContext_t tContext; // [esp+8h] [ebp-Ch] BYREF

  v4 = Direct3D_vScale * 327.67999267578125;
  qmemcpy(&TransContext_tActiveTransContext, ptTransContext, sizeof(TransContext_tActiveTransContext));
  v5 = Direct3D_vScale * 4096000000.0 / (Direct3D_vScale * 4096000000.0 - v4);
  memset(&TransContext_tActiveTransContext.tProjection, 0, sizeof(TransContext_tActiveTransContext.tProjection));
  tContext.nWidth = nWidth;
  result = (struct TransContext_s *)RenderMode_tActiveRenderMode.apfRenderModeMethod[TransContext_eSetActiveTransContextRenderModeMethod];
  TransContext_tActiveTransContext.tProjection._11 = 1.0;
  TransContext_tActiveTransContext.tProjection._34 = 1.0;
  tContext.ptTransContext = &TransContext_tActiveTransContext;
  tContext.nHeight = nHeight;
  TransContext_tActiveTransContext.tProjection._31 = -1.0 / (double)nWidth;
  v7 = 1.0 / vAspectRatio;
  TransContext_tActiveTransContext.tProjection._22 = -1.0 * v7;
  TransContext_tActiveTransContext.tProjection._32 = 1.0 / (double)nHeight - (1.0 - vAspectRatio) * v7;
  TransContext_tActiveTransContext.tProjection._33 = v5;
  TransContext_tActiveTransContext.tProjection._43 = -(v4 * v5);
  if ( result )
    result = (struct TransContext_s *)((int (__cdecl *)(struct SetActiveTransContextContext_t *))result)(&tContext);
  ++TransContext_nActiveTransContextTimeStamp;
  TransContext_isValid = 1;
  return result;
}

// source: b/2/pc/pc_transcontext.c:487  [size]
int __cdecl TransContext_GetActiveTransContextTimeStamp()
{
  return TransContext_nActiveTransContextTimeStamp;
}

// source: b/2/pc/pc_transcontext.c:502  [size]
void __cdecl TransContext_InvalidateActiveTransContext()
{
  TransContext_isValid = 0;
}

// source: b/2/pc/pc_transcontext.c:515  [anchor-callee]
void __cdecl TransContext_RegisterTransContextInPrimitiveList(struct TransContext_s *ptTransContext)
{
  struct RenderPrimitive_s *v1; // eax
  struct RenderPrimitive_s *v2; // ecx

  v1 = (struct RenderPrimitive_s *)Primitive_ptNextFreePrimitive;
  Primitive_ptNextFreePrimitive = (char *)Primitive_ptNextFreePrimitive + 184;
  if ( (char *)Primitive_ptNextFreePrimitive - Primitive_asPrimitive[0] > (char *)Primitive_nMaxPrimitiveUsage )
  {
    Primitive_nMaxPrimitiveUsage = (unsigned int)Primitive_ptNextFreePrimitive - Primitive_asPrimitive[0];
    if ( (char *)Primitive_ptNextFreePrimitive - Primitive_asPrimitive[0] > (char *)dword_6B9E3C )
      v1 = nullptr;
  }
  v1->ePrimType = TransContext_ePrimType;
  qmemcpy(&v1[1].ePrimType, ptTransContext, 0xA8u);
  v2 = &RenderContext_tActiveRenderContext.ptRenderPrimitive_[RenderContext_tActiveRenderContext.nDepth - 1];
  v1->ptNext = v2->ptNext;
  v2->ptNext = v1;
}

// source: b/2/pc/pc_transcontext.c:542  [anchor-callee]
enum bool __cdecl TransContext_ProjectWorldPos2(
        struct TransContext_s *ptTransContext,
        struct real32x2_t *ptDest,
        float *pvDist,
        struct real64x3_t *ptPos)
{
  double v4; // st7
  double v5; // st6
  double v6; // st5
  double v7; // st7
  double v8; // st7
  float Real32x3_Rotate_tTemp; // [esp+4h] [ebp-Ch]
  float Real32x3_Rotate_tTemp_4; // [esp+8h] [ebp-8h]

  v4 = ptPos->vX - ptTransContext->tPos.vX;
  v5 = ptPos->vY - ptTransContext->tPos.vY;
  v6 = ptPos->vZ - ptTransContext->tPos.vZ;
  Real32x3_Rotate_tTemp = v6 * ptTransContext->tMatrix.tX.vZ
                        + v5 * ptTransContext->tMatrix.tX.vY
                        + v4 * ptTransContext->tMatrix.tX.vX;
  Real32x3_Rotate_tTemp_4 = v6 * ptTransContext->tMatrix.tY.vZ
                          + v5 * ptTransContext->tMatrix.tY.vY
                          + v4 * ptTransContext->tMatrix.tY.vX;
  v7 = v6 * ptTransContext->tMatrix.tZ.vZ + v5 * ptTransContext->tMatrix.tZ.vY + v4 * ptTransContext->tMatrix.tZ.vX;
  *pvDist = v7;
  if ( v7 <= 0.0 )
    return false;
  v8 = 1.0 / v7;
  ptDest->vX = ptTransContext->vScreenFOVX * Real32x3_Rotate_tTemp * v8 + ptTransContext->vScreenOriginX;
  ptDest->vY = ptTransContext->vScreenFOVY * Real32x3_Rotate_tTemp_4 * v8 + ptTransContext->vScreenOriginY;
  return true;
}

// source: b/2/pc/pc_transcontext.c:589  [anchor-caller]
enum bool __cdecl TransContext_ProjectWorldPos(
        struct real32x2_t *ptDest,
        float *pvDist,
        struct real64x3_t *ptPos)
{
  return TransContext_ProjectWorldPos2(&TransContext_tActiveTransContext, ptDest, pvDist, ptPos);
}

// source: b/2/pc/pc_transcontext.c:602  [size]
struct real32x3_t *__cdecl TransContext_ProjectRotatedPos(
        struct real32x2_t *ptDest,
        struct real32x3_t *ptPos)
{
  double v2; // st7

  v2 = 1.0 / ptPos->vZ;
  ptDest->vX = ptPos->vX * TransContext_tActiveTransContext.vScreenFOVX * v2
             + TransContext_tActiveTransContext.vScreenOriginX;
  ptDest->vY = ptPos->vY * TransContext_tActiveTransContext.vScreenFOVY * v2
             + TransContext_tActiveTransContext.vScreenOriginY;
  return ptPos;
}

// source: b/2/pc/pc_transcontext.c:629  [size]
void __cdecl TransContext_ProjectDir(
        struct real32x2_t *ptDest,
        float *pvDist,
        struct real32x3_t *ptDir)
{
  double v3; // st7
  double v4; // st6
  double v5; // st5
  double v6; // rt0

  v3 = TransContext_tActiveTransContext.tMatrix.tX.vX * ptDir->vX
     + TransContext_tActiveTransContext.tMatrix.tX.vZ * ptDir->vZ
     + TransContext_tActiveTransContext.tMatrix.tX.vY * ptDir->vY;
  v4 = TransContext_tActiveTransContext.tMatrix.tY.vX * ptDir->vX
     + TransContext_tActiveTransContext.tMatrix.tY.vZ * ptDir->vZ
     + TransContext_tActiveTransContext.tMatrix.tY.vY * ptDir->vY;
  v5 = TransContext_tActiveTransContext.tMatrix.tZ.vX * ptDir->vX
     + TransContext_tActiveTransContext.tMatrix.tZ.vZ * ptDir->vZ
     + TransContext_tActiveTransContext.tMatrix.tZ.vY * ptDir->vY;
  *pvDist = v5;
  if ( v5 > 0.0 )
  {
    v6 = 1.0 / v5;
    ptDest->vX = v3 * TransContext_tActiveTransContext.vScreenFOVX * v6
               + TransContext_tActiveTransContext.vScreenOriginX;
    ptDest->vY = v4 * TransContext_tActiveTransContext.vScreenFOVY * v6
               + TransContext_tActiveTransContext.vScreenOriginY;
  }
}

// source: b/2/pc/pc_transcontext.c:665  [size]
struct real32x2_t *__cdecl TransContext_ProjectSize(
        struct real32x2_t *ptDest,
        struct real32x2_t *ptSize,
        float vDist)
{
  double v3; // st7

  v3 = 1.0 / vDist;
  ptDest->vX = ptSize->vX * TransContext_tActiveTransContext.vScreenFOVX * v3;
  ptDest->vY = ptSize->vY * TransContext_tActiveTransContext.vScreenFOVY * v3;
  return ptSize;
}

// source: b/2/pc/pc_transcontext.c:686  [size]
int __cdecl TransContext_GetSetNearClippingPlaneMethod()
{
  return TransContext_eSetNearClippingPlaneMethod;
}
