/* e/3/pc/pc_polylistdyncubeobj.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: e/3/pc/pc_polylistdyncubeobj.c:104  [anchor-mhash]
void __cdecl PolyListDynCubeObj_DeleteHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptMiddle; // ecx
  struct QTask_s *ptTail; // ecx
  struct QReference_s *v3; // eax

  if ( ptQTask[4].tQTaskChildren.ptTail )
  {
    ptMiddle = ptQTask[2].tQTaskChildren.ptMiddle;
    if ( ptMiddle )
      ptMiddle[2].tQTaskChildren.ptTail = ptQTask[2].tQTaskChildren.ptTail;
    else
      ptQTask[2].ptParent[2].ptPrev = ptQTask[2].tQTaskChildren.ptTail;
    ptTail = ptQTask[2].tQTaskChildren.ptTail;
    if ( ptTail )
      ptTail[2].tQTaskChildren.ptMiddle = ptQTask[2].tQTaskChildren.ptMiddle;
  }
  v3 = *(struct QReference_s **)&ptQTask[4].eQTaskType;
  if ( v3 )
    QReference_Delete(v3, &QTask_tQTaskRefPool);
}

// source: e/3/pc/pc_polylistdyncubeobj.c:131  [anchor-hash]
void __cdecl PolyListDynCubeObj_SetTextureState(void *pxContext)
{
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_MINFILTER, 2u);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_MAGFILTER, 2u);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_ADDRESSU, 1u);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_ADDRESSV, 1u);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_MIPFILTER, 1u);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_TEXCOORDINDEX, 0);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_ALPHAOP, 3u);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_ALPHAARG1, 2u);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_ALPHAARG2, 0);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_COLOROP, 4u);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_COLORARG1, 2u);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_COLORARG2, 0);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_TEXTURETRANSFORMFLAGS, 0);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 1u, D3DTSS_COLOROP, 1u);
}

// source: e/3/pc/pc_polylistdyncubeobj.c:158  [size]
void __cdecl PolyListDynCubeObj_SetClippingState(void *pxContext)
{
  ;
}

// source: e/3/pc/pc_polylistdyncubeobj.c:170  [anchor-mhash]
void __cdecl PolyListDynCubeObj_SetGenericState(void *pxContext)
{
  struct _D3DMATERIAL8 tMaterial; // [esp+1Ch] [ebp-44h] BYREF

  memset(&tMaterial, 0, sizeof(tMaterial));
  tMaterial.Diffuse.r = 1.0;
  tMaterial.Diffuse.g = 1.0;
  tMaterial.Diffuse.b = 1.0;
  tMaterial.Ambient.r = 1.0;
  tMaterial.Ambient.g = 1.0;
  tMaterial.Ambient.b = 1.0;
  Direct3D_ptDevice->lpVtbl->SetMaterial(Direct3D_ptDevice, &tMaterial);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_CLIPPING, 1u);
  Direct3D_ptDevice->lpVtbl->SetRenderState(
    Direct3D_ptDevice,
    D3DRS_FOGCOLOR,
    (__int64)(Mesh3D_atFogColor[1].vZ * 255.0)
  - (((unsigned int)(__int64)(Mesh3D_atFogColor[1].vY * -255.0)
    + ((unsigned int)(__int64)(Mesh3D_atFogColor[1].vX * -255.0) << 8)) << 8));
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_FOGDENSITY, LODWORD(Mesh3D_avFogDensity[1]));
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_FOGTABLEMODE, 0);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_FOGVERTEXMODE, 3u);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_FOGENABLE, QVertex_isFog);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_SPECULARENABLE, 0);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ALPHABLENDENABLE, 0);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_CULLMODE, 1u);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_COLORVERTEX, 0);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_DITHERENABLE, 1u);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ALPHATESTENABLE, 1u);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ALPHAREF, 0);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ALPHAFUNC, 5u);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ZENABLE, Direct3D_bZBufferMode);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ZWRITEENABLE, 0);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ZFUNC, 4u);
}

// source: e/3/pc/pc_polylistdyncubeobj.c:224  [size]
void __cdecl PolyListDynCubeObj_SetBlendState(void *pxContext)
{
  ;
}

// source: e/3/pc/pc_polylistdyncubeobj.c:236  [size]
void __cdecl PolyListDynCubeObj_Direct3DDrawHandler(void *pxData)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct real32x3_t tDeltaPos; };
    struct { char igi2_o1[20]; struct real32x3_t tColorOffset; };
    struct { char igi2_o2[32]; struct PolyList_Direct3DVertex_t *ptWorkVertex; };
    struct { char igi2_o3[36]; float v47; };
    struct { char igi2_o4[40]; float v48; };
    struct { char igi2_o5[44]; float v49; };
    struct { char igi2_o6[48]; int iPoly; };
    struct { char igi2_o7[52]; int iStartVertex; };
    struct { char igi2_o8[56]; struct real32x9_t tTempMatrix; };
    struct { char igi2_o9[96]; struct PolyListDynCubeObj_t *ptPolyListDynCubeObj; };
    struct { char igi2_o10[100]; float vTempWorldMinZ; };
    struct { char igi2_o11[104]; struct SetNearClippingPlaneContext_t tContext; };
    struct { char igi2_o12[112]; struct TransContext_s tNewTransContext; };
    struct { char igi2_o13[280]; struct _D3DMATRIX tLocalMatrix; };
    struct { char igi2_o14[344]; struct TransContext_s tOldTransContext; };
    char igi2_extent[512];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct PolyListDynCubeObj_t *v1; // ebx
  int isFlatShaded; // eax
  struct RenderStateBlock_t *v3; // eax
  int v4; // ecx
  struct RenderStateBlock_t *v5; // eax
  int v6; // ecx
  struct RenderStateBlock_t *v7; // eax
  int v8; // ecx
  struct RandomPoly_t *ptPolyList; // eax
  double vZ; // st7
  struct QReference_s *ptParentQTaskRef; // eax
  unsigned __int16 *pxObject; // eax
  void (__cdecl *pfHandler)(unsigned __int16 *, struct real32x9_t *); // ecx
  double v14; // st7
  double v15; // st7
  double v16; // st6
  unsigned int bFlags; // eax
  struct PolyList_Direct3DVertex_t *v18; // ecx
  int v19; // eax
  int nNumPolys; // edx
  signed int v21; // esi
  double v22; // st7
  char *v23; // eax
  float *v24; // edx
  float *v25; // edx
  float vX; // edi
  int v27; // edi
  int v28; // edi
  double v29; // st7
  float *v30; // edi
  float *v31; // edx
  float v32; // edi
  int v33; // edi
  int v34; // edi
  double v35; // st7
  float *v36; // edi
  float *v37; // edx
  float v38; // edi
  int v39; // edi
  int v40; // edi
  int v41; // edx
  struct IDirect3DBaseTexture8 *v42; // edx
  bool v43; // cc

  igi2_frame.v47 = 1.0;
  igi2_frame.v48 = 1.0;
  igi2_frame.v49 = 1.0;
  memset(&igi2_frame.tColorOffset, 0, sizeof(igi2_frame.tColorOffset));
  if ( pxData )
  {
    v1 = *((struct PolyListDynCubeObj_t **)pxData + 3);
    isFlatShaded = v1->isFlatShaded;
    igi2_frame.ptPolyListDynCubeObj = v1;
    if ( isFlatShaded )
    {
      igi2_frame.tColorOffset = Mesh3D_atAmbientColor[1];
      igi2_frame.v47 = 0.0;
      igi2_frame.v48 = 0.0;
      igi2_frame.v49 = 0.0;
      if ( Mesh3D_atAmbientColor[1].vX > 1.0 )
        igi2_frame.v47 = 1.0 - igi2_frame.tColorOffset.vX;
      if ( igi2_frame.tColorOffset.vY > 1.0 )
        igi2_frame.v48 = 1.0 - igi2_frame.tColorOffset.vY;
      if ( igi2_frame.tColorOffset.vZ > 1.0 )
        igi2_frame.v49 = 1.0 - igi2_frame.tColorOffset.vZ;
    }
    v3 = Direct3D_ptTextureStateBlock;
    v4 = PolyListDynCubeObj_eTextureState;
    if ( Direct3D_ptTextureStateBlock->eCurrentState != PolyListDynCubeObj_eTextureState )
    {
      Direct3D_ptTextureStateBlock->eCurrentState = PolyListDynCubeObj_eTextureState;
      v3->atRenderState[v4].pfCallback(nullptr);
    }
    v5 = Direct3D_ptBlendStateBlock;
    v6 = PolyListDynCubeObj_eBlendState;
    if ( Direct3D_ptBlendStateBlock->eCurrentState != PolyListDynCubeObj_eBlendState )
    {
      Direct3D_ptBlendStateBlock->eCurrentState = PolyListDynCubeObj_eBlendState;
      v5->atRenderState[v6].pfCallback(nullptr);
    }
    v7 = Direct3D_ptGenericStateBlock;
    v8 = PolyListDynCubeObj_eGenericState;
    if ( Direct3D_ptGenericStateBlock->eCurrentState != PolyListDynCubeObj_eGenericState )
    {
      Direct3D_ptGenericStateBlock->eCurrentState = PolyListDynCubeObj_eGenericState;
      v7->atRenderState[v8].pfCallback(v1);
    }
    Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_CULLMODE, 2 * (v1->isBackFaceCull != 0) + 1);
    ptPolyList = v1->ptPolyList;
    qmemcpy(&igi2_frame.tTempMatrix, &v1->tDynCubeObj.tQObj.tPos, 0x18u);
    *(double *)&igi2_frame.tTempMatrix.tX.vX = ptPolyList->aptPos[0]->vX + *(double *)&igi2_frame.tTempMatrix.tX.vX;
    *(double *)&igi2_frame.tTempMatrix.tX.vZ = ptPolyList->aptPos[0]->vY + *(double *)&igi2_frame.tTempMatrix.tX.vZ;
    vZ = ptPolyList->aptPos[0]->vZ;
    ptParentQTaskRef = v1->ptParentQTaskRef;
    igi2_frame.tTempMatrix.tZ.vX = 4096.0;
    *(double *)&igi2_frame.tTempMatrix.tY.vY = vZ + *(double *)&igi2_frame.tTempMatrix.tY.vY;
    if ( ptParentQTaskRef )
    {
      pxObject = (unsigned __int16 *)ptParentQTaskRef->pxObject;
      if ( pxObject )
      {
        pfHandler = (void (__cdecl *)(unsigned __int16 *, struct real32x9_t *))QTask_aatQTaskFinalEvent[SLOWORD(ShadowVolume_vIntensity)][pxObject[18]].pfHandler;
        if ( pfHandler )
          pfHandler(pxObject, &igi2_frame.tTempMatrix);
      }
    }
    Direct3DRender_SetFogParameters((struct real64x3_t *)&igi2_frame.tTempMatrix, igi2_frame.tTempMatrix.tZ.vX);
    Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_LIGHTING, 0);
    if ( v1->eLayer == TRANSCONTEXT_LAYER_FRONT )
    {
      qmemcpy(&igi2_frame.tOldTransContext, &TransContext_tActiveTransContext, sizeof(igi2_frame.tOldTransContext));
      v14 = (double)Display_tActiveMode.nHeight * 4.0 / ((double)Display_tActiveMode.nWidth * 3.0);
      qmemcpy(&igi2_frame.tNewTransContext, &igi2_frame.tOldTransContext, sizeof(igi2_frame.tNewTransContext));
      igi2_frame.tNewTransContext.vFOVX = Mesh3D_avOverrideFOV[0];
      igi2_frame.tNewTransContext.eLayer = TRANSCONTEXT_LAYER_FRONT;
      igi2_frame.tNewTransContext.vFOVY = Mesh3D_avOverrideFOV[0]
                             * RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vHeight
                             / (v14
                              * RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vWidth);
      igi2_frame.tNewTransContext.vScreenFOVX = RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vHalfWidth
                                   / Mesh3D_avOverrideFOV[0];
      igi2_frame.tNewTransContext.vScreenFOVY = v14 * igi2_frame.tNewTransContext.vScreenFOVX;
      TransContext_SetActiveTransContext(&igi2_frame.tNewTransContext);
    }
    v15 = v1->tDynCubeObj.tQObj.tPos.vX - TransContext_tActiveTransContext.tPos.vX;
    v16 = v1->tDynCubeObj.tQObj.tPos.vY - TransContext_tActiveTransContext.tPos.vY;
    qmemcpy(&igi2_frame.tTempMatrix, &v1->tOrientation, sizeof(igi2_frame.tTempMatrix));
    igi2_frame.tDeltaPos.vZ = v1->tDynCubeObj.tQObj.tPos.vZ - TransContext_tActiveTransContext.tPos.vZ;
    igi2_frame.tDeltaPos.vX = v15 * Direct3D_vScale;
    igi2_frame.tDeltaPos.vY = v16 * Direct3D_vScale;
    igi2_frame.tDeltaPos.vZ = igi2_frame.tDeltaPos.vZ * Direct3D_vScale;
    igi2_frame.tTempMatrix.tX.vX = igi2_frame.tTempMatrix.tX.vX * Direct3D_vScale;
    igi2_frame.tTempMatrix.tX.vY = igi2_frame.tTempMatrix.tX.vY * Direct3D_vScale;
    igi2_frame.tTempMatrix.tX.vZ = igi2_frame.tTempMatrix.tX.vZ * Direct3D_vScale;
    igi2_frame.tTempMatrix.tY.vX = igi2_frame.tTempMatrix.tY.vX * Direct3D_vScale;
    igi2_frame.tTempMatrix.tY.vY = igi2_frame.tTempMatrix.tY.vY * Direct3D_vScale;
    igi2_frame.tTempMatrix.tY.vZ = igi2_frame.tTempMatrix.tY.vZ * Direct3D_vScale;
    igi2_frame.tTempMatrix.tZ.vX = igi2_frame.tTempMatrix.tZ.vX * Direct3D_vScale;
    igi2_frame.tTempMatrix.tZ.vY = igi2_frame.tTempMatrix.tZ.vY * Direct3D_vScale;
    igi2_frame.tTempMatrix.tZ.vZ = igi2_frame.tTempMatrix.tZ.vZ * Direct3D_vScale;
    Direct3D_D3DMATRIXFromReal32x9(&igi2_frame.tLocalMatrix, &igi2_frame.tTempMatrix, &igi2_frame.tDeltaPos);
    Direct3D_ptDevice->lpVtbl->SetTransform(Direct3D_ptDevice, (enum _D3DTRANSFORMSTATETYPE)256, &igi2_frame.tLocalMatrix);
    bFlags = v1->bFlags;
    if ( (bFlags & 8) != 0 )
    {
      Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ALPHABLENDENABLE, 1u);
      Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_SRCBLEND, 5u);
      Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_DESTBLEND, 2u);
    }
    else if ( (bFlags & 0x10) != 0 )
    {
      Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ALPHABLENDENABLE, 1u);
      Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_SRCBLEND, 1u);
      Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_DESTBLEND, 4u);
    }
    else
    {
      Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ALPHABLENDENABLE, 1u);
      Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_SRCBLEND, 5u);
      Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_DESTBLEND, 6u);
    }
    PolyListDynCubeObj_tRandomState.anRandom[0] = -923067897;
    PolyListDynCubeObj_tRandomState.anRandom[1] = 971667286;
    PolyListDynCubeObj_tRandomState.anRandom[2] = 2146516173;
    if ( !ComputerMap_ptComputerMap )
    {
      igi2_frame.vTempWorldMinZ = Direct3D_vWorldMinZ;
      igi2_frame.tContext.vNearClippingPlane = Direct3D_vWorldMinZ * 1.0099999904632568;
      RenderMode_tActiveRenderMode.apfRenderModeMethod[TransContext_eSetNearClippingPlaneMethod](&igi2_frame.tContext);
    }
    Direct3D_tState.aptStreamData[0] = Direct3D_atDynamicVertexBuffer[1].ptVertexBuffer;
    Direct3D_tState.anStride[0] = Direct3D_atDynamicVertexBuffer[1].nStride;
    Direct3D_ptDevice->lpVtbl->SetStreamSource(
      Direct3D_ptDevice,
      0,
      Direct3D_atDynamicVertexBuffer[1].ptVertexBuffer,
      Direct3D_atDynamicVertexBuffer[1].nStride);
    Direct3D_tState.nHandle = Direct3D_atDynamicVertexBuffer[1].nFVF;
    Direct3D_ptDevice->lpVtbl->SetVertexShader(Direct3D_ptDevice, Direct3D_atDynamicVertexBuffer[1].nFVF);
    Direct3D_LockDynamicVertexBuffer(&Direct3D_atDynamicVertexBuffer[1], (void **)&igi2_frame.ptWorkVertex, &igi2_frame.iStartVertex, 192);
    v18 = igi2_frame.ptWorkVertex;
    v19 = 0;
    if ( igi2_frame.ptWorkVertex )
    {
      nNumPolys = v1->nNumPolys;
      v21 = 0;
      igi2_frame.iPoly = 0;
      if ( nNumPolys > 0 )
      {
        igi2_frame.tContext.vNearClippingPlane = 0.0;
        do
        {
          v22 = igi2_frame.v47;
          v23 = (char *)v1->ptPolyList + v19;
          v24 = *(float **)v23;
          v18->tPos.vX = **(float **)v23;
          v18->tPos.vY = v24[1];
          v18->tPos.vZ = v24[2];
          v25 = *((float **)v23 + 3);
          *(_QWORD *)&igi2_frame.tDeltaPos.vX = (__int64)((v22 * *v25 + igi2_frame.tColorOffset.vX) * 255.0);
          vX = igi2_frame.tDeltaPos.vX;
          *(_QWORD *)&igi2_frame.tDeltaPos.vX = (__int64)(*((float *)v23 + 12) * 255.0);
          v27 = ((LODWORD(igi2_frame.tDeltaPos.vX) << 8) | LODWORD(vX)) << 8;
          *(_QWORD *)&igi2_frame.tDeltaPos.vX = (__int64)((igi2_frame.v48 * v25[1] + igi2_frame.tColorOffset.vY) * 255.0);
          v28 = (LODWORD(igi2_frame.tDeltaPos.vX) | v27) << 8;
          *(_QWORD *)&igi2_frame.tDeltaPos.vX = (__int64)((igi2_frame.v49 * v25[2] + igi2_frame.tColorOffset.vZ) * 255.0);
          v18->bDiffuseRGBA = LODWORD(igi2_frame.tDeltaPos.vX) | v28;
          v29 = igi2_frame.v47;
          v18->tUV.vX = *((float *)v23 + 6);
          v18->tUV.vY = *((float *)v23 + 7);
          v30 = *((float **)v23 + 1);
          v18[1].tPos.vX = *v30;
          v18[1].tPos.vY = v30[1];
          v18[1].tPos.vZ = v30[2];
          v31 = *((float **)v23 + 4);
          *(_QWORD *)&igi2_frame.tDeltaPos.vX = (__int64)((v29 * *v31 + igi2_frame.tColorOffset.vX) * 255.0);
          v32 = igi2_frame.tDeltaPos.vX;
          *(_QWORD *)&igi2_frame.tDeltaPos.vX = (__int64)(*((float *)v23 + 13) * 255.0);
          v33 = ((LODWORD(igi2_frame.tDeltaPos.vX) << 8) | LODWORD(v32)) << 8;
          *(_QWORD *)&igi2_frame.tDeltaPos.vX = (__int64)((igi2_frame.v48 * v31[1] + igi2_frame.tColorOffset.vY) * 255.0);
          v34 = (LODWORD(igi2_frame.tDeltaPos.vX) | v33) << 8;
          *(_QWORD *)&igi2_frame.tDeltaPos.vX = (__int64)((igi2_frame.v49 * v31[2] + igi2_frame.tColorOffset.vZ) * 255.0);
          v18[1].bDiffuseRGBA = LODWORD(igi2_frame.tDeltaPos.vX) | v34;
          v35 = igi2_frame.v47;
          v18[1].tUV.vX = *((float *)v23 + 8);
          v18[1].tUV.vY = *((float *)v23 + 9);
          v36 = *((float **)v23 + 2);
          v18[2].tPos.vX = *v36;
          v18[2].tPos.vY = v36[1];
          v18[2].tPos.vZ = v36[2];
          v37 = *((float **)v23 + 5);
          *(_QWORD *)&igi2_frame.tDeltaPos.vX = (__int64)((v35 * *v37 + igi2_frame.tColorOffset.vX) * 255.0);
          v38 = igi2_frame.tDeltaPos.vX;
          *(_QWORD *)&igi2_frame.tDeltaPos.vX = (__int64)(*((float *)v23 + 14) * 255.0);
          v39 = ((LODWORD(igi2_frame.tDeltaPos.vX) << 8) | LODWORD(v38)) << 8;
          *(_QWORD *)&igi2_frame.tDeltaPos.vX = (__int64)((igi2_frame.v48 * v37[1] + igi2_frame.tColorOffset.vY) * 255.0);
          v1 = igi2_frame.ptPolyListDynCubeObj;
          v40 = (LODWORD(igi2_frame.tDeltaPos.vX) | v39) << 8;
          *(_QWORD *)&igi2_frame.tDeltaPos.vX = (__int64)((igi2_frame.v49 * v37[2] + igi2_frame.tColorOffset.vZ) * 255.0);
          v18[2].bDiffuseRGBA = LODWORD(igi2_frame.tDeltaPos.vX) | v40;
          v18[2].tUV.vX = *((float *)v23 + 10);
          v18[2].tUV.vY = *((float *)v23 + 11);
          v41 = *((_DWORD *)v23 + 18);
          ++v21;
          if ( v41 )
          {
            if ( igi2_frame.iPoly >= v1->nNumPolys - 1 || *((_DWORD *)v23 + 38) != v41 || v21 >= 63 )
            {
              v42 = *(struct IDirect3DBaseTexture8 **)(v41 + 36);
              if ( v42 != Direct3D_tState.aptTexture[0] )
              {
                Direct3D_tState.aptTexture[0] = v42;
                Direct3D_ptDevice->lpVtbl->SetTexture(Direct3D_ptDevice, 0, v42);
              }
              Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_ALPHAOP, 4u);
              if ( (v1->bFlags & 0x200000) != 0 )
                Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_COLOROP, 5u);
              else
                Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_COLOROP, 4u);
              Direct3D_atDynamicVertexBuffer[1].ptVertexBuffer->lpVtbl->Unlock(Direct3D_atDynamicVertexBuffer[1].ptVertexBuffer);
              Direct3D_ptDevice->lpVtbl->DrawPrimitive(Direct3D_ptDevice, D3DPT_TRIANGLELIST, igi2_frame.iStartVertex, v21);
LABEL_49:
              Direct3D_LockDynamicVertexBuffer(
                &Direct3D_atDynamicVertexBuffer[1],
                (void **)&igi2_frame.ptWorkVertex,
                &igi2_frame.iStartVertex,
                192);
              v18 = igi2_frame.ptWorkVertex;
              if ( !igi2_frame.ptWorkVertex )
                goto LABEL_53;
              v21 = 0;
              goto LABEL_51;
            }
            v18 += 3;
          }
          else
          {
            if ( igi2_frame.iPoly >= v1->nNumPolys - 1 || *((_DWORD *)v23 + 38) || v21 >= 63 )
            {
              if ( Direct3D_tState.aptTexture[0] )
              {
                Direct3D_tState.aptTexture[0] = nullptr;
                Direct3D_ptDevice->lpVtbl->SetTexture(Direct3D_ptDevice, 0, nullptr);
              }
              Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_ALPHAOP, 3u);
              Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_COLOROP, 3u);
              Direct3D_atDynamicVertexBuffer[1].ptVertexBuffer->lpVtbl->Unlock(Direct3D_atDynamicVertexBuffer[1].ptVertexBuffer);
              Direct3D_ptDevice->lpVtbl->DrawPrimitive(Direct3D_ptDevice, D3DPT_TRIANGLELIST, igi2_frame.iStartVertex, v21);
              goto LABEL_49;
            }
            v18 += 3;
          }
LABEL_51:
          v19 = LODWORD(igi2_frame.tContext.vNearClippingPlane) + 80;
          v43 = ++igi2_frame.iPoly < v1->nNumPolys;
          LODWORD(igi2_frame.tContext.vNearClippingPlane) += 80;
        }
        while ( v43 );
      }
      Direct3D_atDynamicVertexBuffer[1].ptVertexBuffer->lpVtbl->Unlock(Direct3D_atDynamicVertexBuffer[1].ptVertexBuffer);
    }
LABEL_53:
    if ( v1->eLayer == TRANSCONTEXT_LAYER_FRONT )
      TransContext_SetActiveTransContext(&igi2_frame.tOldTransContext);
    if ( !ComputerMap_ptComputerMap )
    {
      igi2_frame.tDeltaPos.vX = igi2_frame.vTempWorldMinZ;
      RenderMode_tActiveRenderMode.apfRenderModeMethod[TransContext_eSetNearClippingPlaneMethod](&igi2_frame.tDeltaPos);
    }
  }
}

_BYTE *__cdecl PolyListDynCubeObj_DrawSorted(int *a1)
{
  #pragma pack(push, 1)
  union
  {
    struct { _BYTE v3[4]; };
    struct { char igi2_o1[4]; int v4; };
    struct { char igi2_o2[12]; int v5; };
    char igi2_extent[16];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v1; // ecx
  _BYTE *result; // eax

  if ( a1 )
  {
    v1 = *a1;
    igi2_frame.v4 = PolyListDynCubeObj_ePrimType;
    igi2_frame.v5 = v1;
    RenderMode_tActiveRenderMode.apfRenderModeMethod[PolyListDynCubeObj_ePrimType](igi2_frame.v3);
    dword_834E068 = (int)igi2_frame.v3;
    return igi2_frame.v3;
  }
  return result;
}

void __cdecl PolyListDynCubeObj_EnterHandler(struct QTask_s *a1)
{
  double v1; // st7
  struct SortRenderItem_t *v2; // eax
  double v3; // st4
  double vX; // st3
  unsigned __int8 *v5; // esi

  if ( a1[4].ptPrev )
  {
    v1 = *(double *)&a1[1].ptNext - TransContext_tActiveTransContext.tPos.vX;
    v2 = &SortRender_ptActiveList->atItem[SortRender_ptActiveList->nNumItems];
    v3 = TransContext_tActiveTransContext.tMatrix.tZ.vZ
       * (*(double *)&a1[1].tQTaskChildren.ptTail - TransContext_tActiveTransContext.tPos.vZ)
       + TransContext_tActiveTransContext.tMatrix.tZ.vY
       * (*(double *)&a1[1].tQTaskChildren.ptHead - TransContext_tActiveTransContext.tPos.vY);
    vX = TransContext_tActiveTransContext.tMatrix.tZ.vX;
    ++SortRender_ptActiveList->nNumItems;
    v5 = &SortRender_anSortBuffer[SortRender_nBufferPos];
    SortRender_nBufferPos += 4;
    v2->pxData = v5;
    v2->pfCallback = (void (__cdecl *)(void *))PolyListDynCubeObj_DrawSorted;
    v2->vZ = v3 + vX * v1;
    *(_DWORD *)v5 = a1;
  }
}

// source: e/3/pc/pc_polylistdyncubeobj.c:760  [anchor-mhash]
struct PolyListDynCubeObj_t *__cdecl PolyListDynCubeObj_New(
        struct World_s *ptWorld,
        struct QTask_s *ptParent,
        struct real64x3_t *ptPos,
        struct real32x9_t *ptOrientation,
        struct RandomPoly_t *ptPolyList,
        int nNumPolys,
        unsigned int bFlags,
        int isAutomatic,
        int isFlatShaded,
        int isBackFaceCull,
        void (__cdecl *pfDrawInit)(void *),
        void *pxDrawInitData)
{
  struct QTask_s *v13; // ebx
  struct DynCubeObj_s *ptManualRedrawList; // eax
  struct DynCubeObj_s *ptPrev; // eax

  v13 = QTask_NewFn(ptParent, PolyListDynCubeObj_eQTaskType, nullptr);
  *(_DWORD *)&v13[2].eQTaskType = ptPolyList;
  v13[4].ptPrev = (struct QTask_s *)nNumPolys;
  v13[4].tQTaskChildren.ptHead = (struct QTask_s *)bFlags;
  v13[4].tQTaskChildren.ptTail = (struct QTask_s *)isAutomatic;
  v13[4].tQTaskChildren.ptMiddle = (struct QTask_s *)isFlatShaded;
  v13[2].ptParent = (struct QTask_s *)ptWorld;
  v13[4].tQTaskRefList.ptHead = (struct QReference_s *)isBackFaceCull;
  v13[4].tQTaskRefList.ptTail = (struct QReference_s *)pfDrawInit;
  v13[4].tQTaskRefList.ptMiddle = (struct QReference_s *)pxDrawInitData;
  v13[4].ptNext = nullptr;
  v13[4].ptParent = (struct QTask_s *)1;
  if ( ptParent )
    *(_DWORD *)&v13[4].eQTaskType = QTask_NewQTaskRef(ptParent);
  else
    *(_DWORD *)&v13[4].eQTaskType = 0;
  qmemcpy(&v13[1], ptPos, 0x18u);
  qmemcpy(&v13[3], ptOrientation, sizeof(struct QTask_s));
  if ( isAutomatic )
  {
    ptManualRedrawList = ptWorld->ptManualRedrawList;
    if ( ptManualRedrawList )
    {
      ptManualRedrawList->ptPrev = (struct DynCubeObj_s *)v13;
      ptWorld->ptManualRedrawList->ptPrev->ptNext = ptWorld->ptManualRedrawList;
      ptPrev = ptWorld->ptManualRedrawList->ptPrev;
      ptWorld->ptManualRedrawList = ptPrev;
      ptPrev->ptPrev = nullptr;
      return (struct PolyListDynCubeObj_t *)v13;
    }
    ptWorld->ptManualRedrawList = (struct DynCubeObj_s *)v13;
    v13[2].tQTaskChildren.ptTail = nullptr;
    ptWorld->ptManualRedrawList->ptPrev = nullptr;
  }
  return (struct PolyListDynCubeObj_t *)v13;
}

// source: e/3/pc/pc_polylistdyncubeobj.c:819  [size]
int __cdecl PolyListDynCubeObj_SetNumPolysPerItem(
        struct PolyListDynCubeObj_t *ptPolyListDynCubeObj,
        int nNumPolysPerItem)
{
  ptPolyListDynCubeObj->nNumPolysPerItem = nNumPolysPerItem;
  return nNumPolysPerItem;
}

// source: e/3/pc/pc_polylistdyncubeobj.c:834  [anchor-strings]
void __cdecl PolyListDynCubeObj_Open()
{
  unsigned __int16 v0; // si
  int v1; // eax
  struct RenderStateBlock_t *v2; // ecx
  __int32 v3; // edx
  int nNumStates; // eax
  struct RenderStateBlock_t *v5; // ecx
  int v6; // eax
  struct RenderStateBlock_t *v7; // ecx
  int v8; // eax
  struct RenderStateBlock_t *v9; // ecx
  int v10; // eax

  v0 = QTask_NewQTaskType("PolyListDynCubeObj", 200, DynCubeObj_eQTaskType, 0, 0);
  PolyListDynCubeObj_eQTaskType = v0;
  QTask_LinkQTaskEventHandlerFn(v0, 5, (void (__cdecl *)(struct QTask_s *, void *))PolyListDynCubeObj_EnterHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 2, PolyListDynCubeObj_DeleteHandler);
  v1 = 0;
  while ( RenderMode_atRenderModeMethod[v1].isAllocated )
  {
    if ( ++v1 >= 128 )
    {
      LDebug_Error("RenderMode: Failed to create new method '%s'", "PolyListDynCubeObjPrimitive");
      abort();
    }
  }
  v2 = Direct3D_ptTextureStateBlock;
  v3 = 130 * Direct3D_eRenderMode;
  RenderMode_atRenderModeMethod[v1].zName = "PolyListDynCubeObjPrimitive";
  RenderMode_atRenderModeMethod[v1].isAllocated = 1;
  *((_DWORD *)&RenderMode_atRenderMode[0].apfRenderModeMethod[v1] + v3) = PolyListDynCubeObj_Direct3DDrawHandler;
  PolyListDynCubeObj_ePrimType = v1;
  nNumStates = v2->nNumStates;
  v2->nNumStates = nNumStates + 1;
  v2->atRenderState[nNumStates].pfCallback = PolyListDynCubeObj_SetTextureState;
  v5 = Direct3D_ptBlendStateBlock;
  PolyListDynCubeObj_eTextureState = nNumStates;
  v6 = Direct3D_ptBlendStateBlock->nNumStates;
  Direct3D_ptBlendStateBlock->nNumStates = v6 + 1;
  v5->atRenderState[v6].pfCallback = (void (__cdecl *)(void *))PolyListDynCubeObj_SetBlendState;
  v7 = Direct3D_ptGenericStateBlock;
  PolyListDynCubeObj_eBlendState = v6;
  v8 = Direct3D_ptGenericStateBlock->nNumStates;
  Direct3D_ptGenericStateBlock->nNumStates = v8 + 1;
  v7->atRenderState[v8].pfCallback = PolyListDynCubeObj_SetGenericState;
  v9 = Direct3D_ptClippingStateBlock;
  PolyListDynCubeObj_eGenericState = v8;
  v10 = Direct3D_ptClippingStateBlock->nNumStates;
  Direct3D_ptClippingStateBlock->nNumStates = v10 + 1;
  v9->atRenderState[v10].pfCallback = (void (__cdecl *)(void *))PolyListDynCubeObj_SetClippingState;
  PolyListDynCubeObj_eClippingState = v10;
}

// source: e/3/pc/pc_polylistdyncubeobj.c:861  [anchor-hash]
void __cdecl PolyListDynCubeObj_Close()
{
  int v0; // edx
  int v1; // ecx
  int v2; // eax

  v0 = PolyListDynCubeObj_eBlendState;
  Direct3D_ptTextureStateBlock->atRenderState[PolyListDynCubeObj_eTextureState].pfCallback = nullptr;
  v1 = PolyListDynCubeObj_eGenericState;
  Direct3D_ptBlendStateBlock->atRenderState[v0].pfCallback = nullptr;
  v2 = PolyListDynCubeObj_eClippingState;
  Direct3D_ptGenericStateBlock->atRenderState[v1].pfCallback = nullptr;
  Direct3D_ptClippingStateBlock->atRenderState[v2].pfCallback = nullptr;
  QTask_DeleteQTaskType(PolyListDynCubeObj_eQTaskType);
  RenderMode_atRenderModeMethod[PolyListDynCubeObj_ePrimType].isAllocated = 0;
}
