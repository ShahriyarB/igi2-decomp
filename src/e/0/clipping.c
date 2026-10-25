/* e/0/clipping.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: e/0/clipping.c:53  [size]
void __cdecl Clipping_StartFrameCallback()
{
  Clipping_tClipData.tClipWindows.ptClipWindowsList = nullptr;
  Clipping_tClipData.tClipFrustumList.nNumClipPlanes = 0;
  Clipping_tClipData.tClipFrustumList.nNumClipWindows = 0;
}

// source: e/0/clipping.c:74  [size]
void __cdecl Clipping_BuildClippingFrustum(
        struct real32x4_t *ptClipWindow,
        struct Clipping_ClipPlane_s *atClipPlanes,
        struct _D3DMATRIX *ptInversedProjection)
{
  #pragma pack(push, 1)
  union
  {
    struct { float v24; };
    struct { float v25; };
    struct { float v26; };
    struct { float v27; };
    struct { float v28; };
    struct { char igi2_o5[4]; float v29; };
    struct { char igi2_o6[4]; float v30; };
    struct { char igi2_o7[4]; float v31; };
    struct { char igi2_o8[8]; float v32; };
    struct { char igi2_o9[8]; float v33; };
    struct { char igi2_o10[8]; float v34; };
    struct { char igi2_o11[12]; float v35; };
    struct { char igi2_o12[16]; float v36; };
    struct { char igi2_o13[20]; int v37; };
    struct { char igi2_o14[24]; float v38; };
    struct { char igi2_o15[28]; int v39; };
    struct { char igi2_o16[32]; float v40; };
    struct { char igi2_o17[36]; float v41; };
    struct { char igi2_o18[40]; float v42; };
    struct { char igi2_o19[44]; float v43; };
    struct { char igi2_o20[48]; float v44; };
    struct { char igi2_o21[52]; int v45; };
    struct { char igi2_o22[56]; float v46; };
    struct { char igi2_o23[60]; float v47; };
    struct { char igi2_o24[64]; float v48; };
    struct { char igi2_o25[68]; float v49; };
    struct { char igi2_o26[72]; float v50; };
    struct { char igi2_o27[76]; float v51; };
    struct { char igi2_o28[80]; float v52; };
    struct { char igi2_o29[84]; float v53; };
    struct { char igi2_o30[88]; float v54; };
    struct { char igi2_o31[92]; float v55; };
    struct { char igi2_o32[96]; float v56; };
    struct { char igi2_o33[100]; float v57; };
    struct { char igi2_o34[104]; float v58; };
    struct { char igi2_o35[108]; float v59; };
    struct { char igi2_o36[112]; float v60; };
    struct { char igi2_o37[120]; float v61; };
    struct { char igi2_o38[124]; float v62; };
    struct { char igi2_o39[128]; float v63; };
    struct { char igi2_o40[132]; int v64; };
    struct { char igi2_o41[136]; float v65; };
    struct { char igi2_o42[140]; float v66; };
    struct { char igi2_o43[148]; float v67; };
    struct { char igi2_o44[152]; float v68; };
    struct { char igi2_o45[156]; float v69; };
    struct { char igi2_o46[164]; float v70; };
    struct { char igi2_o47[168]; float v71; };
    struct { char igi2_o48[172]; float v72; };
    struct { char igi2_o49[180]; float v73; };
    struct { char igi2_o50[184]; float v74; };
    struct { char igi2_o51[188]; float v75; };
    struct { char igi2_o52[196]; float v76; };
    struct { char igi2_o53[200]; float v77; };
    struct { char igi2_o54[204]; float v78; };
    struct { char igi2_o55[212]; float v79; };
    struct { char igi2_o56[216]; float v80; };
    struct { char igi2_o57[220]; float v81; };
    char igi2_extent[228];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  double v3; // st7
  double v4; // st6
  int v5; // esi
  double v6; // st5
  double v7; // st4
  double v8; // st2
  double v9; // st5
  double v10; // st7
  double v11; // st6
  double v12; // st5
  double v13; // st4
  double v14; // st7
  double v15; // st7
  double v16; // st7
  double v17; // st7
  double v18; // st7
  double v19; // st7
  double v20; // st7
  float *p_vY; // ecx
  int v22; // edx
  long double v23; // st7
  struct real32x3_t v82; // 0:^18.12

  if ( TransContext_tActiveTransContext.eLayer )
  {
    if ( TransContext_tActiveTransContext.eLayer == TRANSCONTEXT_LAYER_BACK )
    {
      v3 = Direct3D_vD3DBackgroundMinZ;
      v4 = Direct3D_vD3DBackgroundMaxZ;
    }
    else
    {
      v3 = Direct3D_vD3DMinZ;
      v4 = Direct3D_vD3DMaxZ;
    }
  }
  else
  {
    v3 = Direct3D_vD3DOverlayMinZ;
    v4 = Direct3D_vD3DOverlayMaxZ;
  }
  igi2_frame.v39 = 0;
  igi2_frame.v43 = 0.0;
  igi2_frame.v47 = 0.0;
  igi2_frame.v51 = 0.0;
  igi2_frame.v24 = RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vX
      + RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vHalfWidth;
  v5 = 0;
  v6 = RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vY
     + RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vHalfHeight;
  igi2_frame.v63 = ptClipWindow->tX.vX - igi2_frame.v24;
  v7 = 1.0 / igi2_frame.v24;
  igi2_frame.v36 = v7;
  *(float *)&igi2_frame.v37 = v7 * igi2_frame.v63 * v3;
  igi2_frame.v61 = ptClipWindow->tX.vY - v6;
  igi2_frame.v35 = 1.0 / v6;
  igi2_frame.v38 = -(1.0 / v6 * igi2_frame.v61 * v3);
  igi2_frame.v40 = v3;
  v8 = ptClipWindow->tY.vX - igi2_frame.v24;
  igi2_frame.v62 = v8;
  igi2_frame.v25 = v8 * igi2_frame.v36 * v3;
  igi2_frame.v41 = igi2_frame.v25;
  igi2_frame.v49 = igi2_frame.v25;
  igi2_frame.v42 = igi2_frame.v38;
  igi2_frame.v44 = v3;
  igi2_frame.v45 = igi2_frame.v37;
  v9 = ptClipWindow->tY.vY - v6;
  igi2_frame.v46 = -(igi2_frame.v35 * v9 * v3);
  igi2_frame.v48 = v3;
  igi2_frame.v50 = igi2_frame.v46;
  igi2_frame.v52 = v3;
  igi2_frame.v53 = igi2_frame.v36 * igi2_frame.v63 * v4;
  igi2_frame.v54 = -(igi2_frame.v35 * igi2_frame.v61 * v4);
  igi2_frame.v55 = v4;
  igi2_frame.v56 = v4;
  igi2_frame.v57 = igi2_frame.v62 * igi2_frame.v36 * v4;
  igi2_frame.v58 = -(v9 * igi2_frame.v35 * v4);
  igi2_frame.v59 = v4;
  igi2_frame.v60 = igi2_frame.v59;
  do
  {
    D3DXVec4Transform((int)&igi2_frame.v64 + v5, (int)&igi2_frame.v37 + v5, (int)ptInversedProjection);
    v5 += 16;
  }
  while ( v5 < 96 );
  v10 = igi2_frame.v70 - *(float *)&igi2_frame.v64;
  v11 = igi2_frame.v71 - igi2_frame.v65;
  v12 = igi2_frame.v72 - igi2_frame.v66;
  igi2_frame.v41 = *(float *)&igi2_frame.v64 - igi2_frame.v67;
  igi2_frame.v42 = igi2_frame.v65 - igi2_frame.v68;
  igi2_frame.v43 = igi2_frame.v66 - igi2_frame.v69;
  *(float *)&igi2_frame.v45 = igi2_frame.v70 - igi2_frame.v73;
  igi2_frame.v46 = igi2_frame.v71 - igi2_frame.v74;
  igi2_frame.v47 = igi2_frame.v72 - igi2_frame.v75;
  igi2_frame.v49 = igi2_frame.v73 - igi2_frame.v67;
  igi2_frame.v50 = igi2_frame.v74 - igi2_frame.v68;
  igi2_frame.v51 = igi2_frame.v75 - igi2_frame.v69;
  igi2_frame.v53 = igi2_frame.v76 - *(float *)&igi2_frame.v64;
  igi2_frame.v54 = igi2_frame.v77 - igi2_frame.v65;
  igi2_frame.v55 = igi2_frame.v78 - igi2_frame.v66;
  igi2_frame.v57 = igi2_frame.v79 - igi2_frame.v73;
  igi2_frame.v58 = igi2_frame.v80 - igi2_frame.v74;
  igi2_frame.v59 = igi2_frame.v81 - igi2_frame.v75;
  igi2_frame.v26 = igi2_frame.v54 * v12 - v11 * igi2_frame.v55;
  v13 = igi2_frame.v53 * v12;
  atClipPlanes->tNormal.vX = igi2_frame.v26;
  igi2_frame.v29 = -(v13 - v10 * igi2_frame.v55);
  atClipPlanes->tNormal.vY = igi2_frame.v29;
  igi2_frame.v32 = igi2_frame.v53 * v11 - v10 * igi2_frame.v54;
  v14 = igi2_frame.v43 * igi2_frame.v54;
  atClipPlanes->tNormal.vZ = igi2_frame.v32;
  igi2_frame.v27 = v14 - igi2_frame.v42 * igi2_frame.v55;
  v15 = igi2_frame.v43 * igi2_frame.v53;
  atClipPlanes[1].tNormal.vX = igi2_frame.v27;
  igi2_frame.v30 = -(v15 - igi2_frame.v41 * igi2_frame.v55);
  v16 = igi2_frame.v42;
  atClipPlanes[1].tNormal.vY = igi2_frame.v30;
  igi2_frame.v33 = v16 * igi2_frame.v53 - igi2_frame.v41 * igi2_frame.v54;
  v17 = igi2_frame.v59 * igi2_frame.v50;
  atClipPlanes[1].tNormal.vZ = igi2_frame.v33;
  igi2_frame.v28 = v17 - igi2_frame.v58 * igi2_frame.v51;
  v18 = igi2_frame.v49 * igi2_frame.v59;
  atClipPlanes[2].tNormal.vX = igi2_frame.v28;
  igi2_frame.v31 = -(v18 - igi2_frame.v57 * igi2_frame.v51);
  v19 = igi2_frame.v49;
  atClipPlanes[2].tNormal.vY = igi2_frame.v31;
  igi2_frame.v34 = v19 * igi2_frame.v58 - igi2_frame.v57 * igi2_frame.v50;
  v20 = igi2_frame.v46 * igi2_frame.v59;
  atClipPlanes[2].tNormal.vZ = igi2_frame.v34;
  v82.vX = v20 - igi2_frame.v47 * igi2_frame.v58;
  v82.vY = -(*(float *)&igi2_frame.v45 * igi2_frame.v59 - igi2_frame.v47 * igi2_frame.v57);
  v82.vZ = *(float *)&igi2_frame.v45 * igi2_frame.v58 - igi2_frame.v46 * igi2_frame.v57;
  atClipPlanes[3].tNormal = v82;
  p_vY = &atClipPlanes->tNormal.vY;
  v22 = 4;
  do
  {
    if ( *(p_vY - 1) != 0.0 || *p_vY != 0.0 || p_vY[1] != 0.0 )
    {
      v23 = 1.0 / sqrt(*(p_vY - 1) * *(p_vY - 1) + p_vY[1] * p_vY[1] + *p_vY * *p_vY);
      *(p_vY - 1) = *(p_vY - 1) * v23;
      *p_vY = *p_vY * v23;
      p_vY[1] = p_vY[1] * v23;
    }
    *(p_vY - 4) = 0.0;
    *(p_vY - 3) = 0.0;
    *(p_vY - 2) = 0.0;
    p_vY += 6;
    --v22;
  }
  while ( v22 );
}

// source: e/0/clipping.c:176  [size]
void __cdecl Clipping_SetupClippingPlanes(struct QObjectVector_s *ptClipList)
{
  int v1; // esi
  struct Clipping_ClipFrustumList_s *p_tClipFrustumList; // edi
  struct _D3DMATRIX ptClipWindow; // [esp+10h] [ebp-40h] BYREF

  Clipping_tClipData.tClipFrustumList.nNumClipPlanes = 4;
  Clipping_tClipData.tClipFrustumList.nNumClipWindows = ptClipList->nAllocated;
  D3DXMatrixInverse((int)&ptClipWindow, 0, (int)&TransContext_tActiveTransContext.tProjection);
  v1 = 0;
  if ( Clipping_tClipData.tClipFrustumList.nNumClipWindows > 0 )
  {
    p_tClipFrustumList = &Clipping_tClipData.tClipFrustumList;
    do
    {
      Clipping_BuildClippingFrustum(
        (struct real32x4_t *)ptClipList->papxElement[v1++],
        (struct Clipping_ClipPlane_s *)p_tClipFrustumList,
        &ptClipWindow);
      p_tClipFrustumList = (struct Clipping_ClipFrustumList_s *)((char *)p_tClipFrustumList + 192);
    }
    while ( v1 < Clipping_tClipData.tClipFrustumList.nNumClipWindows );
  }
  Clipping_BuildClippingFrustum(
    &Clipping_tClipData.tClipWindows.tEnclosingWindow,
    Clipping_tClipData.tClipFrustumList.atEnclosingFrustum,
    &ptClipWindow);
}

// source: e/0/clipping.c:321  [size]
struct QObjectVector_s *__cdecl Clipping_GetClipWindows()
{
  return Clipping_tClipData.tClipWindows.ptClipWindowsList;
}

// source: e/0/clipping.c:334  [size]
struct Clipping_ClipFrustumList_s *__cdecl Clipping_GetClipPlanes()
{
  return &Clipping_tClipData.tClipFrustumList;
}

// source: e/0/clipping.c:348  [size]
struct real32x2_t *__cdecl Clipping_SetClipWindows(
        struct QObjectVector_s *ptClipList,
        struct real32x2_t *ptMin,
        struct real32x2_t *ptMax)
{
  struct real32x2_t *result; // eax

  Clipping_tClipData.tClipWindows.ptClipWindowsList = ptClipList;
  Clipping_tClipData.tClipWindows.tEnclosingWindow.tX = *ptMin;
  Clipping_tClipData.tClipWindows.tEnclosingWindow.tY = *ptMax;
  Clipping_SetupClippingPlanes(ptClipList);
  return result;
}

// source: e/0/clipping.c:381  [anchor-hash]
void __cdecl Clipping_Open()
{
  Display_RegisterCallback((void (__cdecl *)())Clipping_StartFrameCallback, &Display_ptStartFrameCallback);
}

// source: e/0/clipping.c:395  [anchor-hash]
void __cdecl Clipping_Close()
{
  struct DisplayCallbackChain_s *v0; // eax
  struct DisplayCallbackChain_s *v1; // ecx

  v0 = Display_ptStartFrameCallback;
  v1 = nullptr;
  if ( Display_ptStartFrameCallback )
  {
    while ( (void (__cdecl *)())v0->pfCallback != Clipping_StartFrameCallback )
    {
      v1 = v0;
      v0 = v0->ptNext;
      if ( !v0 )
        return;
    }
    if ( v1 )
      v1->ptNext = v0->ptNext;
    else
      Display_ptStartFrameCallback = v0->ptNext;
  }
}
