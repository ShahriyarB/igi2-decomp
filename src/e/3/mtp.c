/* e/3/mtp.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: e/3/mtp.c:115  [anchor-mhash]
struct VirModel_s *__cdecl MTP_VirModel_GetPtr(char *pzVirModelName)
{
  struct MTP_s *ptHead; // eax
  struct MTP_s *ptNext; // ebx
  struct VirModel_s *v3; // ebp
  struct VirModel_s *v4; // edi

  ptHead = MTP_tMTPList.ptHead;
  ptNext = MTP_tMTPList.ptHead->ptNext;
  if ( !MTP_tMTPList.ptHead->ptNext )
    return nullptr;
  while ( 1 )
  {
    v3 = ptHead->tVirModelList.ptHead;
    v4 = v3->ptNext;
    if ( v3->ptNext )
      break;
LABEL_5:
    ptHead = ptNext;
    ptNext = ptNext->ptNext;
    if ( !ptNext )
      return nullptr;
  }
  while ( strcmp(pzVirModelName, v3->pzName) )
  {
    v3 = v4;
    v4 = v4->ptNext;
    if ( !v4 )
      goto LABEL_5;
  }
  return v3;
}

// source: e/3/mtp.c:154  [anchor-callee]
struct LODVirModel_s *__cdecl MTP_CreateLODVirModel(struct LODVirModel_s *ptLODVirModel)
{
  int v2; // edi
  char *zFirstVirModelName; // eax
  char *v4; // edx
  char v5; // cl
  int v6; // esi
  __int16 *anDetail; // ebp
  struct LODVirModel_s *result; // eax
  char zName[32]; // [esp+8h] [ebp-20h] BYREF

  v2 = 0;
  zFirstVirModelName = ptLODVirModel->zFirstVirModelName;
  ptLODVirModel->isLODDistanceSpecified = 0;
  v4 = (char *)(zName - zFirstVirModelName);
  do
  {
    v5 = *zFirstVirModelName;
    zFirstVirModelName[(_DWORD)v4] = *zFirstVirModelName;
    ++zFirstVirModelName;
  }
  while ( v5 );
  v6 = 1;
  anDetail = ptLODVirModel->anDetail;
  while ( 1 )
  {
    *anDetail = 100 / (v6 * v6);
    result = (struct LODVirModel_s *)MTP_VirModel_GetPtr(zName);
    ptLODVirModel->aptVirModel[v2] = (struct VirModel_s *)result;
    if ( !result )
      break;
    result = (struct LODVirModel_s *)&zName[strlen(zName) - 1];
    ++v2;
    ++anDetail;
    ++v6;
    ++LOBYTE(result->aptVirModel[0]);
    if ( v6 >= 6 )
      goto LABEL_8;
  }
  ptLODVirModel->nLOD = v2;
LABEL_8:
  ptLODVirModel->nLOD = v2;
  if ( (__int16)v2 > 0 )
  {
    result = (struct LODVirModel_s *)ptLODVirModel->aptVirModel[0];
    if ( ptLODVirModel->aptVirModel[0] )
    {
      result = (struct LODVirModel_s *)result->aptVirModel[3];
      if ( result )
      {
        result = (struct LODVirModel_s *)result->aptVirModel[3];
        if ( result )
        {
          if ( *(_DWORD *)&result->zFirstVirModelName[12] == 1 )
            Direct3DRender_SetupBoneVertexRefs(ptLODVirModel);
        }
      }
    }
  }
  return result;
}

// source: e/3/mtp.c:204  [size]
void __cdecl MTP_ReloadLOD()
{
  struct LODVirModel_s *v0; // esi

  v0 = MTP_atLODVirModel;
  do
  {
    if ( v0 != (struct LODVirModel_s *)-20 )
      MTP_CreateLODVirModel(v0);
    ++v0;
  }
  while ( (int)v0 < 127844896 );
}

// source: e/3/mtp.c:250  [anchor-callee]
void *__cdecl MTP_GetChunkData(void *pxRawFile, unsigned int nID, unsigned int *pnChunkSize)
{
  unsigned __int16 v3; // dx
  char *v4; // ecx
  char *v5; // edx

  HIBYTE(v3) = BYTE2(*((_DWORD *)pxRawFile + 1));
  v4 = (char *)pxRawFile + 12;
  LOBYTE(v3) = *((_BYTE *)pxRawFile + 7);
  v5 = (char *)pxRawFile + (((*((_DWORD *)pxRawFile + 1) & 0xFF00 | (*((_DWORD *)pxRawFile + 1) << 16)) << 8) | v3) + 8;
  while ( nID != ((((*(_DWORD *)v4 << 16) | *(_DWORD *)v4 & 0xFF00) << 8)
                | ((HIWORD(*(_DWORD *)v4) | *(_DWORD *)v4 & 0xFF0000u) >> 8)) )
  {
    v4 += ((((((*((_DWORD *)v4 + 1) << 16) | *((_DWORD *)v4 + 1) & 0xFF00) << 8)
           | ((HIWORD(*((_DWORD *)v4 + 1)) | *((_DWORD *)v4 + 1) & 0xFF0000u) >> 8))
          + 3)
         & 0xFFFFFFFC)
        + 8;
    if ( v4 >= v5 )
      return nullptr;
  }
  if ( pnChunkSize )
    *pnChunkSize = (((*((_DWORD *)v4 + 1) << 16) | *((_DWORD *)v4 + 1) & 0xFF00) << 8)
                 | ((HIWORD(*((_DWORD *)v4 + 1)) | *((_DWORD *)v4 + 1) & 0xFF0000u) >> 8);
  return v4 + 8;
}

// source: e/3/mtp.c:322  [anchor-hash]
struct Model_s *__cdecl MTP_GetModelViaIdx(struct ModelList_s *ptList, int nIdx)
{
  struct Model_s *result; // eax
  struct Model_s *ptNext; // ecx
  int v4; // edx

  result = ptList->ptHead;
  ptNext = result->ptNext;
  v4 = 0;
  if ( !result->ptNext )
    return nullptr;
  while ( v4 != nIdx )
  {
    result = ptNext;
    ptNext = ptNext->ptNext;
    ++v4;
    if ( !ptNext )
      return nullptr;
  }
  return result;
}

// source: e/3/mtp.c:358  [anchor-hash]
struct AnimHeader_s *__cdecl MTP_AnimLoad(char *pzName)
{
  sprintf(MTP_zFileName, "LOCAL:anims/%s.iff", pzName);
  return Hierarchy_LoadAnim(MTP_zFileName);
}

// source: e/3/mtp.c:382  [anchor-callee]
struct Model_s *__cdecl MTP_ModelLoad(char *pzName)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct Model_s *ptModel; };
    struct { char igi2_o1[4]; float pxRawFile; };
    struct { char igi2_o2[8]; struct Mesh3D_Mesh_t *ptMesh; };
    struct { char igi2_o3[12]; struct LoadModelContext_t tContext; };
    char igi2_extent[24];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  char *v1; // ecx
  struct Mesh3D_Mesh_t *v2; // eax
  float vY; // ebp
  void *v4; // eax
  unsigned int v5; // edx
  int v6; // eax
  unsigned int v7; // eax
  _DWORD *v8; // eax
  int v9; // ecx
  struct Mesh3D_Mesh_t *ChunkData; // eax
  struct Mesh3D_Mesh_t *v11; // edi
  bool v12; // zf
  struct Model_s *v13; // eax
  _DWORD *FirstChunk; // eax
  int v15; // ecx
  unsigned __int8 *v16; // ebx
  _DWORD *v17; // eax
  int v18; // ecx
  char *v19; // eax
  unsigned __int8 *v20; // eax
  struct Mesh3D_Mesh_t *v21; // esi
  unsigned int v22; // edx
  int v23; // eax
  unsigned int v24; // eax
  _DWORD *v25; // edi
  int v26; // eax
  unsigned int v27; // edx
  int v28; // eax
  unsigned int v29; // eax
  _DWORD *v30; // edi
  int v31; // eax
  unsigned int v32; // edx
  int v33; // eax
  unsigned int v34; // eax
  _DWORD *v35; // eax
  int v36; // ecx
  char *v37; // eax
  int v38; // ecx
  char *v39; // ebx
  int i; // edi
  int v41; // ecx
  int v42; // ecx
  char *v43; // ecx
  int v44; // ebx
  int j; // esi
  unsigned int v46; // edi
  int v47; // eax
  unsigned int v48; // edx
  int *v49; // eax
  int v50; // eax
  char *v51; // eax
  int v52; // ecx
  _DWORD *v54; // eax
  int v55; // ecx
  struct Mesh3D_AttachObject_t *v56; // eax
  struct Mesh3D_Mesh_t *v57; // ebx
  _DWORD *v58; // eax
  int v59; // ecx
  _DWORD *v60; // eax
  int v61; // ecx
  _DWORD *v62; // eax
  int v63; // ecx
  _DWORD *v64; // eax
  int v65; // ecx
  struct Mesh3D_PortalVertex_t *v66; // eax
  enum RenderMode_enum v67; // edx
  void (__cdecl *v68)(void *); // eax

  sprintf(MTP_zFileName, "LOCAL:models/%s.mef", pzName);
  if ( Resource_IsLoadedInternal(MTP_zFileName, (struct Resource_s **)&igi2_frame.ptMesh) )
  {
    v2 = igi2_frame.ptMesh;
    igi2_frame.ptMesh->pxCollisionMesh = (void *)1;
    vY = v2->tRenderMeshSphere.tPos.vY;
  }
  else
  {
    Game_MPRunNetwork(v1);
    v4 = File_Load(MTP_zFileName, (unsigned int *)&igi2_frame.ptMesh);
    if ( !v4 )
    {
      LDebug_Error("Failed to load resource: '%s'", MTP_zFileName);
      goto LABEL_5;
    }
    vY = COERCE_FLOAT(Resource_ParseFile(File_zLastSubstitutedPath, v4, (unsigned int)igi2_frame.ptMesh));
  }
  igi2_frame.pxRawFile = vY;
  if ( vY != 0.0 )
  {
    v5 = *(_DWORD *)(LODWORD(vY) + 4);
    if ( v5 )
    {
      v6 = *(_DWORD *)(LODWORD(vY) + 8);
      if ( (v6 & ~(v6 - 1)) == v6 )
      {
        v7 = ~(v6 - 1) & (v6 + 19);
        if ( v7 < v5 )
        {
          v8 = (_DWORD *)(LODWORD(vY) + v7);
          goto LABEL_14;
        }
      }
      else
      {
        ILF_nLastError = 1;
      }
    }
  }
  v8 = nullptr;
LABEL_14:
  if ( v8 )
  {
    while ( *v8 != 1296388936 )
    {
      v9 = v8[3];
      if ( v9 )
      {
        v8 = (_DWORD *)((char *)v8 + v9);
        if ( v8 )
          continue;
      }
      goto LABEL_18;
    }
  }
  else
  {
LABEL_18:
    v8 = nullptr;
  }
  ChunkData = (struct Mesh3D_Mesh_t *)ILF_GetChunkData(v8, (void *)LODWORD(vY));
  v11 = ChunkData;
  v12 = LODWORD(ChunkData->vVersion) == 1042536202;
  igi2_frame.ptMesh = ChunkData;
  if ( !v12 )
  {
    LDebug_Error(
      "Mesh \"%s\" and source code are incompatible. (Mesh \"%s\" is version %0.2f, source code is version %0.2f.)",
      pzName,
      pzName,
      ChunkData->vVersion,
      0.1599999964237213);
LABEL_5:
    abort();
  }
  v13 = (struct Model_s *)Mem_AllocFn(24, 4);
  v13->ptPrev = nullptr;
  v13->ptNext = nullptr;
  v13->ptMesh = v11;
  *(float *)&v13->pxRawFile = vY;
  v13->nAnimTextures = 0;
  v13->atAnimTexInfo = nullptr;
  igi2_frame.ptModel = v13;
  if ( v11->nBones <= 0 )
  {
    v21 = igi2_frame.ptMesh;
    v11->pcHierarchy = nullptr;
    v11->ptBoneTranslations = nullptr;
  }
  else
  {
    FirstChunk = ILF_GetFirstChunk((void *)LODWORD(vY));
    if ( FirstChunk )
    {
      while ( *FirstChunk != 1212761426 )
      {
        v15 = FirstChunk[3];
        if ( v15 )
        {
          FirstChunk = (_DWORD *)((char *)FirstChunk + v15);
          if ( FirstChunk )
            continue;
        }
        goto LABEL_26;
      }
    }
    else
    {
LABEL_26:
      FirstChunk = nullptr;
    }
    v16 = (unsigned __int8 *)ILF_GetChunkData(FirstChunk, (void *)LODWORD(vY));
    v17 = ILF_GetFirstChunk((void *)LODWORD(vY));
    if ( v17 )
    {
      while ( *v17 != 1112424781 )
      {
        v18 = v17[3];
        if ( v18 )
        {
          v17 = (_DWORD *)((char *)v17 + v18);
          if ( v17 )
            continue;
        }
        goto LABEL_31;
      }
    }
    else
    {
LABEL_31:
      v17 = nullptr;
    }
    v19 = (char *)ILF_GetChunkData(v17, (void *)LODWORD(vY));
    v20 = Hierarchy_Register(v16, nullptr, v19);
    v21 = igi2_frame.ptMesh;
    igi2_frame.ptMesh->pcHierarchy = v20;
    v21->ptBoneTranslations = (struct real32x3_t *)&v16[(v21->nBones + 3) & 0xFFFFFFFC];
  }
  if ( vY != 0.0 )
  {
    v22 = *(_DWORD *)(LODWORD(vY) + 4);
    if ( v22 )
    {
      v23 = *(_DWORD *)(LODWORD(vY) + 8);
      if ( (v23 & ~(v23 - 1)) == v23 )
      {
        v24 = ~(v23 - 1) & (v23 + 19);
        if ( v24 < v22 )
        {
          v25 = (_DWORD *)(v24 + LODWORD(vY));
          goto LABEL_41;
        }
      }
      else
      {
        ILF_nLastError = 1;
      }
    }
  }
  v25 = nullptr;
LABEL_41:
  if ( v25 )
  {
    while ( *v25 != 1297240136 )
    {
      v26 = v25[3];
      if ( v26 )
      {
        v25 = (_DWORD *)((char *)v25 + v26);
        if ( v25 )
          continue;
      }
      goto LABEL_45;
    }
    v21->ptMorph = (struct Mesh3D_Morph_t *)ILF_GetChunkData(v25, (void *)LODWORD(vY));
  }
  else
  {
LABEL_45:
    v21->ptMorph = nullptr;
  }
  if ( vY != 0.0 )
  {
    v27 = *(_DWORD *)(LODWORD(vY) + 4);
    if ( v27 )
    {
      v28 = *(_DWORD *)(LODWORD(vY) + 8);
      if ( (v28 & ~(v28 - 1)) == v28 )
      {
        v29 = ~(v28 - 1) & (v28 + 19);
        if ( v29 < v27 )
        {
          v30 = (_DWORD *)(v29 + LODWORD(vY));
          goto LABEL_54;
        }
      }
      else
      {
        ILF_nLastError = 1;
      }
    }
  }
  v30 = nullptr;
LABEL_54:
  if ( v30 )
  {
    while ( *v30 != 1196183383 )
    {
      v31 = v30[3];
      if ( v31 )
      {
        v30 = (_DWORD *)((char *)v30 + v31);
        if ( v30 )
          continue;
      }
      goto LABEL_58;
    }
    v21->ptGlows = (struct Mesh3D_Glow_t *)ILF_GetChunkData(v30, (void *)LODWORD(vY));
  }
  else
  {
LABEL_58:
    v21->ptGlows = nullptr;
  }
  if ( vY == 0.0 )
    goto LABEL_66;
  v32 = *(_DWORD *)(LODWORD(vY) + 4);
  if ( !v32 )
    goto LABEL_66;
  v33 = *(_DWORD *)(LODWORD(vY) + 8);
  if ( (v33 & ~(v33 - 1)) != v33 )
  {
    ILF_nLastError = 1;
    goto LABEL_66;
  }
  v34 = ~(v33 - 1) & (v33 + 19);
  if ( v34 >= v32 )
  {
LABEL_66:
    v35 = nullptr;
    goto LABEL_67;
  }
  v35 = (_DWORD *)(LODWORD(vY) + v34);
LABEL_67:
  if ( v35 )
  {
    while ( *v35 != 1312905300 )
    {
      v36 = v35[3];
      if ( v36 )
      {
        v35 = (_DWORD *)((char *)v35 + v36);
        if ( v35 )
          continue;
      }
      goto LABEL_109;
    }
    v37 = (char *)ILF_GetFirstChunk((void *)LODWORD(vY));
    if ( v37 )
    {
      while ( *(_DWORD *)v37 != 1312905300 )
      {
        v38 = *((_DWORD *)v37 + 3);
        if ( v38 )
        {
          v37 += v38;
          if ( v37 )
            continue;
        }
        goto LABEL_76;
      }
    }
    else
    {
LABEL_76:
      v37 = nullptr;
    }
    v39 = v37;
    for ( i = 1; v37; ++i )
    {
      v41 = *((_DWORD *)v37 + 3);
      if ( !v41 )
        break;
      v37 += v41;
      if ( !v37 )
        break;
      while ( *(_DWORD *)v37 != 1312905300 )
      {
        v42 = *((_DWORD *)v37 + 3);
        if ( v42 )
        {
          v37 += v42;
          if ( v37 )
            continue;
        }
        goto LABEL_84;
      }
    }
LABEL_84:
    igi2_frame.ptModel->atAnimTexInfo = (struct ModelAnimTexInfo_s *)Mem_AllocFn(20 * i, 4);
    igi2_frame.ptModel->nAnimTextures = i;
    v43 = v39;
    if ( i )
    {
      v44 = 0;
      for ( j = i; j; --j )
      {
        if ( vY != 0.0 && v43 )
        {
          v46 = *(_DWORD *)(LODWORD(vY) + 8);
          if ( (v46 & ~(v46 - 1)) == v46 )
          {
            v47 = (int)&v43[-LODWORD(vY)];
            if ( (unsigned int)&v43[-LODWORD(vY)] < *(_DWORD *)(LODWORD(vY) + 4) )
            {
              v48 = *((_DWORD *)v43 + 2);
              if ( (v48 & ~(v48 - 1)) == v48 && v48 <= v46 )
              {
                if ( *((_DWORD *)v43 + 1) )
                {
                  vY = igi2_frame.pxRawFile;
                  v49 = (int *)(LODWORD(igi2_frame.pxRawFile) + (~(v48 - 1) & (v48 + v47 + 15)));
                  goto LABEL_100;
                }
              }
              else
              {
                ILF_nLastError = 1;
              }
              vY = igi2_frame.pxRawFile;
            }
            else
            {
              ILF_nLastError = 1;
            }
          }
          else
          {
            ILF_nLastError = 1;
          }
        }
        v49 = nullptr;
LABEL_100:
        igi2_frame.ptModel->atAnimTexInfo[v44].aiFrames = v49 + 2;
        igi2_frame.ptModel->atAnimTexInfo[v44].iTextureToAnimate = *v49;
        igi2_frame.ptModel->atAnimTexInfo[v44].nFrames = v49[1];
        igi2_frame.ptModel->atAnimTexInfo[v44].nActiveFrame = 0;
        if ( v43 && (v50 = *((_DWORD *)v43 + 3)) != 0 )
        {
          v43 += v50;
          if ( v43 )
          {
            v51 = v43;
            while ( *(_DWORD *)v51 != 1312905300 )
            {
              v52 = *((_DWORD *)v51 + 3);
              if ( v52 )
              {
                v51 += v52;
                if ( v51 )
                  continue;
              }
              goto LABEL_107;
            }
            v43 = v51;
          }
        }
        else
        {
LABEL_107:
          v43 = nullptr;
        }
        ++v44;
      }
    }
  }
LABEL_109:
  if ( igi2_frame.ptMesh->pxRenderMesh )
  {
    igi2_frame.ptModel->pxRawFile = nullptr;
    return igi2_frame.ptModel;
  }
  else
  {
    v54 = ILF_GetFirstChunk((void *)LODWORD(vY));
    if ( v54 )
    {
      while ( *v54 != 1096045633 )
      {
        v55 = v54[3];
        if ( v55 )
        {
          v54 = (_DWORD *)((char *)v54 + v55);
          if ( v54 )
            continue;
        }
        goto LABEL_116;
      }
    }
    else
    {
LABEL_116:
      v54 = nullptr;
    }
    v56 = (struct Mesh3D_AttachObject_t *)ILF_GetChunkData(v54, (void *)LODWORD(vY));
    v57 = igi2_frame.ptMesh;
    igi2_frame.ptMesh->ptAttachObject = v56;
    v58 = ILF_GetFirstChunk((void *)LODWORD(vY));
    if ( v58 )
    {
      while ( *v58 != 1297503320 )
      {
        v59 = v58[3];
        if ( v59 )
        {
          v58 = (_DWORD *)((char *)v58 + v59);
          if ( v58 )
            continue;
        }
        goto LABEL_121;
      }
    }
    else
    {
LABEL_121:
      v58 = nullptr;
    }
    v57->ptMagicVertex = (struct Mesh3D_MagicVertex_t *)ILF_GetChunkData(v58, (void *)LODWORD(vY));
    v60 = ILF_GetFirstChunk((void *)LODWORD(vY));
    if ( v60 )
    {
      while ( *v60 != 1347375700 )
      {
        v61 = v60[3];
        if ( v61 )
        {
          v60 = (_DWORD *)((char *)v60 + v61);
          if ( v60 )
            continue;
        }
        goto LABEL_126;
      }
    }
    else
    {
LABEL_126:
      v60 = nullptr;
    }
    v57->ptPortal = (struct Mesh3D_Portal_t *)ILF_GetChunkData(v60, (void *)LODWORD(vY));
    v62 = ILF_GetFirstChunk((void *)LODWORD(vY));
    if ( v62 )
    {
      while ( *v62 != 1347700291 )
      {
        v63 = v62[3];
        if ( v63 )
        {
          v62 = (_DWORD *)((char *)v62 + v63);
          if ( v62 )
            continue;
        }
        goto LABEL_131;
      }
    }
    else
    {
LABEL_131:
      v62 = nullptr;
    }
    v57->ptPortalFace = (struct Mesh3D_PortalFace_t *)ILF_GetChunkData(v62, (void *)LODWORD(vY));
    v64 = ILF_GetFirstChunk((void *)LODWORD(vY));
    if ( v64 )
    {
      while ( *v64 != 1347704408 )
      {
        v65 = v64[3];
        if ( v65 )
        {
          v64 = (_DWORD *)((char *)v64 + v65);
          if ( v64 )
            continue;
        }
        goto LABEL_136;
      }
    }
    else
    {
LABEL_136:
      v64 = nullptr;
    }
    v66 = (struct Mesh3D_PortalVertex_t *)ILF_GetChunkData(v64, (void *)LODWORD(vY));
    v67 = MTP_eLoadModelRenderModeMethod;
    v57->ptPortalVertex = v66;
    v68 = RenderMode_tActiveRenderMode.apfRenderModeMethod[v67];
    igi2_frame.tContext.ptMesh = v57;
    *(float *)&igi2_frame.tContext.pxRawFile = vY;
    igi2_frame.tContext.pzName = pzName;
    if ( v68 )
      v68(&igi2_frame.tContext);
    return igi2_frame.ptModel;
  }
}

// source: e/3/mtp.c:540  [anchor-strings]
struct Shadow_Volume_s *__cdecl MTP_ShadowVolumeLoad(char *pzName)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct Shadow_Volume_s *ptVolume; };
    struct { char igi2_o1[4]; unsigned int nSize; };
    char igi2_extent[8];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct Shadow_Volume_s *v1; // ebp
  char *v2; // ecx
  unsigned int v3; // eax
  _DWORD *v4; // esi
  void *v5; // eax
  unsigned int v6; // edx
  int v7; // eax
  unsigned int v8; // eax
  _DWORD *v9; // eax
  int v10; // ecx
  unsigned int v11; // edx
  int v12; // eax
  unsigned int v13; // eax
  _DWORD *v14; // eax
  int v15; // ecx
  unsigned int v16; // ecx
  signed int v17; // ebp
  unsigned int v18; // edx
  int v19; // eax
  unsigned int v20; // eax
  _DWORD *v21; // eax
  int v22; // ecx
  unsigned int v23; // edx
  int v24; // eax
  unsigned int v25; // eax
  _DWORD *v26; // eax
  int v27; // ecx
  char *ChunkData; // ebx
  unsigned int v29; // edx
  int v30; // eax
  unsigned int v31; // eax
  _DWORD *v32; // eax
  int v33; // ecx
  char *v34; // eax
  int v35; // esi
  int v36; // edi
  struct Shadow_Mesh_t *ptFirstMesh; // ecx
  struct Shadow_Face_t *patFace; // edx
  int *v39; // ecx

  v1 = (struct Shadow_Volume_s *)Mem_AllocFn(20, 4);
  igi2_frame.ptVolume = v1;
  v1->ptPrev = nullptr;
  v1->ptNext = nullptr;
  sprintf(MTP_zFileName, "LOCAL:models/%s.mef", pzName);
  if ( Resource_IsLoadedInternal(MTP_zFileName, (struct Resource_s **)&igi2_frame.nSize) )
  {
    v3 = igi2_frame.nSize;
    *(_DWORD *)(igi2_frame.nSize + 44) = 1;
    v4 = *(_DWORD **)(v3 + 52);
  }
  else
  {
    Game_MPRunNetwork(v2);
    v5 = File_Load(MTP_zFileName, &igi2_frame.nSize);
    if ( !v5 )
    {
      LDebug_Error("Failed to load resource: '%s'", MTP_zFileName);
      abort();
    }
    v4 = Resource_ParseFile(File_zLastSubstitutedPath, v5, igi2_frame.nSize);
  }
  v1->pxRawFile = v4;
  if ( v4 )
  {
    v6 = v4[1];
    if ( v6 )
    {
      v7 = v4[2];
      if ( (v7 & ~(v7 - 1)) == v7 )
      {
        v8 = ~(v7 - 1) & (v7 + 19);
        if ( v8 < v6 )
        {
          v9 = (_DWORD *)((char *)v4 + v8);
          goto LABEL_13;
        }
      }
      else
      {
        ILF_nLastError = 1;
      }
    }
  }
  v9 = nullptr;
LABEL_13:
  if ( v9 )
  {
    while ( *v9 != 1397572947 )
    {
      v10 = v9[3];
      if ( v10 )
      {
        v9 = (_DWORD *)((char *)v9 + v10);
        if ( v9 )
          continue;
      }
      goto LABEL_17;
    }
  }
  else
  {
LABEL_17:
    v9 = nullptr;
  }
  v1->ptFirstMesh = (struct Shadow_Mesh_t *)ILF_GetChunkData(v9, v4);
  if ( v4 )
  {
    v11 = v4[1];
    if ( v11 )
    {
      v12 = v4[2];
      if ( (v12 & ~(v12 - 1)) == v12 )
      {
        v13 = ~(v12 - 1) & (v12 + 19);
        if ( v13 < v11 )
        {
          v14 = (_DWORD *)((char *)v4 + v13);
          goto LABEL_25;
        }
      }
      else
      {
        ILF_nLastError = 1;
      }
    }
  }
  v14 = nullptr;
LABEL_25:
  if ( v14 )
  {
    while ( *v14 != 1397572947 )
    {
      v15 = v14[3];
      if ( v15 )
      {
        v14 = (_DWORD *)((char *)v14 + v15);
        if ( v14 )
          continue;
      }
      goto LABEL_29;
    }
    v16 = v14[1];
  }
  else
  {
LABEL_29:
    v16 = igi2_frame.nSize;
  }
  v17 = v16 / 0x1C;
  igi2_frame.ptVolume->nMesh = v16 / 0x1C;
  if ( v4 )
  {
    v18 = v4[1];
    if ( v18 )
    {
      v19 = v4[2];
      if ( (v19 & ~(v19 - 1)) == v19 )
      {
        v20 = ~(v19 - 1) & (v19 + 19);
        if ( v20 < v18 )
        {
          v21 = (_DWORD *)((char *)v4 + v20);
          goto LABEL_38;
        }
      }
      else
      {
        ILF_nLastError = 1;
      }
    }
  }
  v21 = nullptr;
LABEL_38:
  if ( v21 )
  {
    while ( *v21 != 1397113155 )
    {
      v22 = v21[3];
      if ( v22 )
      {
        v21 = (_DWORD *)((char *)v21 + v22);
        if ( v21 )
          continue;
      }
      goto LABEL_42;
    }
  }
  else
  {
LABEL_42:
    v21 = nullptr;
  }
  igi2_frame.nSize = (unsigned int)ILF_GetChunkData(v21, v4);
  if ( v4 )
  {
    v23 = v4[1];
    if ( v23 )
    {
      v24 = v4[2];
      if ( (v24 & ~(v24 - 1)) == v24 )
      {
        v25 = ~(v24 - 1) & (v24 + 19);
        if ( v25 < v23 )
        {
          v26 = (_DWORD *)((char *)v4 + v25);
          goto LABEL_50;
        }
      }
      else
      {
        ILF_nLastError = 1;
      }
    }
  }
  v26 = nullptr;
LABEL_50:
  if ( v26 )
  {
    while ( *v26 != 1398166616 )
    {
      v27 = v26[3];
      if ( v27 )
      {
        v26 = (_DWORD *)((char *)v26 + v27);
        if ( v26 )
          continue;
      }
      goto LABEL_54;
    }
  }
  else
  {
LABEL_54:
    v26 = nullptr;
  }
  ChunkData = (char *)ILF_GetChunkData(v26, v4);
  if ( v4 )
  {
    v29 = v4[1];
    if ( v29 )
    {
      v30 = v4[2];
      if ( (v30 & ~(v30 - 1)) == v30 )
      {
        v31 = ~(v30 - 1) & (v30 + 19);
        if ( v31 < v29 )
        {
          v32 = (_DWORD *)((char *)v4 + v31);
          goto LABEL_62;
        }
      }
      else
      {
        ILF_nLastError = 1;
      }
    }
  }
  v32 = nullptr;
LABEL_62:
  if ( v32 )
  {
    while ( *v32 != 1162102597 )
    {
      v33 = v32[3];
      if ( v33 )
      {
        v32 = (_DWORD *)((char *)v32 + v33);
        if ( v32 )
          continue;
      }
      goto LABEL_66;
    }
  }
  else
  {
LABEL_66:
    v32 = nullptr;
  }
  v34 = (char *)ILF_GetChunkData(v32, v4);
  v35 = 0;
  if ( v17 > 0 )
  {
    v36 = 0;
    do
    {
      ptFirstMesh = igi2_frame.ptVolume->ptFirstMesh;
      patFace = ptFirstMesh[v36].uStartFace.patFace;
      v39 = (int *)&ptFirstMesh[v36];
      ++v35;
      *v39 = igi2_frame.nSize + 28 * (_DWORD)patFace;
      v39[1] = (int)&ChunkData[12 * v39[1]];
      v39[2] = (int)&v34[8 * v39[2]];
      ++v36;
    }
    while ( v35 < igi2_frame.ptVolume->nMesh );
  }
  return igi2_frame.ptVolume;
}

// source: e/3/mtp.c:604  [anchor-callee]
void __cdecl MTP_ModelFree(struct Model_s *ptModel)
{
  unsigned __int8 *pcHierarchy; // edi
  struct ModelAnimTexInfo_s *atAnimTexInfo; // eax
  int v4; // esi
  struct Mesh3D_Mesh_t *ptMesh; // ecx
  void (__cdecl *v6)(void *); // eax
  int v7; // esi
  struct UnloadModelContext_t tContext; // [esp+Ch] [ebp-8h] BYREF

  pcHierarchy = ptModel->ptMesh->pcHierarchy;
  if ( pcHierarchy )
    Hierarchy_UnRegister(pcHierarchy);
  if ( ptModel->nAnimTextures )
  {
    atAnimTexInfo = ptModel->atAnimTexInfo;
    if ( atAnimTexInfo )
    {
      v4 = *(_DWORD *)((unsigned int)&atAnimTexInfo[-1].aiFrames & 0xFFFFFFFC);
      --Mem_nCurrentAllocations;
      Node_Remove((_DWORD **)v4);
      memset(*(void **)(v4 + 8), 0xCDu, *(_DWORD *)(v4 + 16));
      free((void *)v4);
    }
    ptModel->atAnimTexInfo = nullptr;
  }
  if ( ptModel->pxRawFile )
  {
    ptMesh = ptModel->ptMesh;
    tContext.pxRawFile = ptModel->pxRawFile;
    v6 = RenderMode_tActiveRenderMode.apfRenderModeMethod[MTP_eUnloadModelRenderModeMethod];
    tContext.ptMesh = ptMesh;
    if ( v6 )
      v6(&tContext);
    Resource_Flush(ptModel->pxRawFile);
  }
  Node_Remove(ptModel);
  v7 = *(_DWORD *)((unsigned int)&ptModel[-1].atAnimTexInfo & 0xFFFFFFFC);
  --Mem_nCurrentAllocations;
  Node_Remove((_DWORD **)v7);
  memset(*(void **)(v7 + 8), 0xCDu, *(_DWORD *)(v7 + 16));
  free((void *)v7);
}

// source: e/3/mtp.c:653  [anchor-hash]
struct AnimHeader_s *__cdecl MTP_AnimFree(struct AnimHeader_s *ptAnimHeader)
{
  struct Resource_s *ptHead; // ecx
  struct AnimHeader_s *result; // eax
  void *pxRawFile; // edi

  Hierarchy_UnRegisterAnim(ptAnimHeader);
  Node_Remove(ptAnimHeader);
  ptHead = Resource_tResourceList.ptHead;
  result = (struct AnimHeader_s *)Resource_tResourceList.ptHead->ptNext;
  pxRawFile = ptAnimHeader->pxRawFile;
  if ( Resource_tResourceList.ptHead->ptNext )
  {
    while ( ptHead->pxData != pxRawFile )
    {
      ptHead = (struct Resource_s *)result;
      result = result->ptNext;
      if ( !result )
        return result;
    }
    result = (struct AnimHeader_s *)ptHead->nType;
    if ( result != (struct AnimHeader_s *)3 && result != (struct AnimHeader_s *)1 )
      Resource_Remove(ptHead);
  }
  return result;
}

// source: e/3/mtp.c:677  [anchor-hash]
void __cdecl MTP_ShadowVolumeFree(struct Shadow_Volume_s *ptVolume)
{
  struct Resource_s *ptHead; // ecx
  struct Resource_s *ptNext; // eax
  unsigned int nType; // eax
  int v5; // esi

  ptHead = Resource_tResourceList.ptHead;
  ptNext = Resource_tResourceList.ptHead->ptNext;
  if ( Resource_tResourceList.ptHead->ptNext )
  {
    while ( ptHead->pxData != ptVolume->pxRawFile )
    {
      ptHead = ptNext;
      ptNext = ptNext->ptNext;
      if ( !ptNext )
        goto LABEL_8;
    }
    nType = ptHead->nType;
    if ( nType != 3 && nType != 1 )
      Resource_Remove(ptHead);
  }
LABEL_8:
  Node_Remove(ptVolume);
  v5 = *(_DWORD *)((unsigned int)&ptVolume[-1].pxRawFile & 0xFFFFFFFC);
  --Mem_nCurrentAllocations;
  Node_Remove((_DWORD **)v5);
  memset(*(void **)(v5 + 8), 0xCDu, *(_DWORD *)(v5 + 16));
  free((void *)v5);
}

// source: e/3/mtp.c:697  [anchor-hash]
struct MTP_s *__cdecl MTP_ParseChunkMODS(struct MTP_s *ptMTP)
{
  struct MTP_s **ChunkData; // esi
  struct MTP_s *result; // eax
  char *v4; // esi
  struct ModelList_s *p_tModelList; // ebx
  struct MTP_s *v6; // edi
  struct Model_s *v7; // eax

  ChunkData = (struct MTP_s **)MTP_GetChunkData(ptMTP->pxRawFile, 0x4D4F4453u, nullptr);
  result = *ChunkData;
  v4 = (char *)(ChunkData + 1);
  if ( (int)result > 0 )
  {
    p_tModelList = &ptMTP->tModelList;
    v6 = result;
    do
    {
      v7 = MTP_ModelLoad(v4);
      List_AddTail(v7, (int)p_tModelList);
      result = (struct MTP_s *)strlen(v4);
      v6 = (struct MTP_s *)((char *)v6 - 1);
      v4 = (char *)&result->ptNext + (_DWORD)v4 + 1;
    }
    while ( v6 );
  }
  return result;
}

// source: e/3/mtp.c:738  [anchor-hash]
struct MTP_s *__cdecl MTP_ParseChunkSVOL(struct MTP_s *ptMTP)
{
  struct MTP_s *result; // eax
  struct MTP_s *v3; // esi
  char *p_ptPrev; // esi
  struct ShadowVolumeList_s *p_tShadowVolumeList; // ebx
  struct MTP_s *v6; // edi
  struct Shadow_Volume_s *v7; // eax

  result = (struct MTP_s *)MTP_GetChunkData(ptMTP->pxRawFile, 0x53564F4Cu, nullptr);
  v3 = result;
  if ( result )
  {
    result = result->ptNext;
    p_ptPrev = (char *)&v3->ptPrev;
    if ( (int)result > 0 )
    {
      p_tShadowVolumeList = &ptMTP->tShadowVolumeList;
      v6 = result;
      do
      {
        v7 = MTP_ShadowVolumeLoad(p_ptPrev);
        List_AddTail(v7, (int)p_tShadowVolumeList);
        result = (struct MTP_s *)strlen(p_ptPrev);
        v6 = (struct MTP_s *)((char *)v6 - 1);
        p_ptPrev = (char *)&result->ptNext + (_DWORD)p_ptPrev + 1;
      }
      while ( v6 );
    }
  }
  return result;
}

// source: e/3/mtp.c:778  [anchor-strings]
void __cdecl MTP_ParseChunkTEXF(struct MTP_s *ptMTP)
{
  char *v1; // ecx
  int v3; // ebx
  int *ChunkData; // esi
  int v5; // edi
  bool v6; // cc
  char *v7; // esi
  char *v8; // ecx
  bool v9; // zf
  int v10; // [esp+10h] [ebp-4h]
  struct MTP_s *ptMTPa = *(struct MTP_s * *)&ptMTP; // [esp+18h] [ebp+4h] ARGSLOT

  Game_MPRunNetwork(v1);
  v3 = 0;
  ChunkData = (int *)MTP_GetChunkData(ptMTP->pxRawFile, 0x54455846u, nullptr);
  v5 = *ChunkData;
  v6 = *ChunkData <= 0;
  ptMTP->nNumTex = *ChunkData;
  if ( v6 )
  {
    ptMTP->paTexInfo = nullptr;
    ptMTP->paPalInfo = nullptr;
  }
  else
  {
    ptMTP->paTexInfo = (struct TexInfo_s *)Mem_AllocFn(44 * v5, 4);
    v7 = (char *)(ChunkData + 1);
    ptMTP->paPalInfo = (struct PalInfo *)Mem_AllocFn(12 * v5, 4);
    if ( v5 > 0 )
    {
      ptMTPa = nullptr;
      v10 = v5;
      do
      {
        ptMTP->paPalInfo[v3].nPalette = 0;
        sprintf(MTP_zFileName, "LOCAL:textures/%s.tex", v7);
        Game_MPRunNetwork(v8);
        Texture_Load(
          (struct TexInfo_s *)((char *)ptMTPa + (unsigned int)ptMTP->paTexInfo),
          &ptMTP->paPalInfo[v3],
          MTP_zFileName);
        v7 += strlen(v7) + 1;
        ++v3;
        v9 = v10 == 1;
        ptMTPa = (struct MTP_s *)((char *)ptMTPa + 44);
        --v10;
      }
      while ( !v9 );
    }
  }
}

// source: e/3/mtp.c:837  [anchor-strings]
void __cdecl MTP_ParseChunkPALF(struct MTP_s *ptMTP)
{
  int v2; // ebx
  int *ChunkData; // edi
  int v4; // esi
  bool v5; // cc
  char *v6; // edi
  struct MTP_s *ptMTPa = *(struct MTP_s * *)&ptMTP; // [esp+14h] [ebp+4h] ARGSLOT

  v2 = 0;
  ChunkData = (int *)MTP_GetChunkData(ptMTP->pxRawFile, 0x50414C46u, nullptr);
  v4 = *ChunkData;
  v5 = *ChunkData <= 0;
  ptMTP->nNumPal = *ChunkData;
  if ( v5 )
  {
    ptMTP->paPalInfoExtra = nullptr;
  }
  else
  {
    v6 = (char *)(ChunkData + 1);
    ptMTP->paPalInfoExtra = (struct PalInfo *)Mem_AllocFn(12 * v4, 4);
    if ( v4 > 0 )
    {
      ptMTPa = (struct MTP_s *)v4;
      do
      {
        sprintf(MTP_zFileName, "%spalettes/%s.pal", MTP_zRootDir, v6);
        Palette_Load(&ptMTP->paPalInfoExtra[v2], MTP_zFileName);
        v6 += strlen(v6) + 1;
        ++v2;
        ptMTPa = (struct MTP_s *)((char *)ptMTPa - 1);
      }
      while ( ptMTPa );
    }
  }
}

// source: e/3/mtp.c:885  [anchor-hash]
struct MTP_s *__cdecl MTP_ParseChunkBANM(struct MTP_s *ptMTP)
{
  struct MTP_s **ChunkData; // esi
  struct MTP_s *result; // eax
  char *v4; // esi
  struct AnimHeaderList_s *p_tAnimHeaderList; // edi
  struct MTP_s *v6; // ebx
  struct AnimHeader_s *Anim; // eax

  ChunkData = (struct MTP_s **)MTP_GetChunkData(ptMTP->pxRawFile, 0x42414E4Du, nullptr);
  result = *ChunkData;
  v4 = (char *)(ChunkData + 1);
  if ( (int)result > 0 )
  {
    p_tAnimHeaderList = &ptMTP->tAnimHeaderList;
    v6 = result;
    do
    {
      sprintf(MTP_zFileName, "LOCAL:anims/%s.iff", v4);
      Anim = Hierarchy_LoadAnim(MTP_zFileName);
      List_AddTail(Anim, (int)p_tAnimHeaderList);
      result = (struct MTP_s *)strlen(v4);
      v6 = (struct MTP_s *)((char *)v6 - 1);
      v4 = (char *)&result->ptNext + (_DWORD)v4 + 1;
    }
    while ( v6 );
  }
  return result;
}

// source: e/3/mtp.c:948  [anchor-strings]
char *__cdecl MTP_ParseMTP(
        struct MTP_s *ptMTP,
        char *pzBaseName,
        enum bool isLoadTextures)
{
  #pragma pack(push, 1)
  union
  {
    struct { int v44; };
    struct { char igi2_o1[20]; char zFilename[4]; };
    struct { char igi2_o2[24]; struct MTP_s *ptMTPCommon; };
    struct { char igi2_o3[28]; int nLookIdx; };
    struct { char igi2_o4[32]; char *pzName; };
    struct { char igi2_o5[36]; char *pzData; };
    struct { char igi2_o6[40]; char Buffer[256]; };
    char igi2_extent[296];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  char *v4; // ecx
  char *v5; // ecx
  void *v6; // eax
  struct MTP_s *v7; // ebp
  char *v8; // ecx
  char *v9; // ecx
  int v10; // eax
  char *v11; // ecx
  unsigned int v12; // eax
  void *v13; // eax
  void *v14; // eax
  int *ChunkData; // eax
  int v16; // esi
  char *v17; // edx
  void *pxRawFile; // eax
  char *result; // eax
  char *v20; // ebp
  int v21; // edx
  _DWORD *v22; // ebp
  int v23; // ecx
  struct Model_s *ptHead; // edi
  struct Model_s *v25; // eax
  int v26; // edx
  struct Model_s *ptNext; // eax
  int v28; // ebx
  _DWORD *v29; // esi
  char *v30; // edi
  char *v31; // eax
  unsigned int v32; // kr00_4
  void *v33; // eax
  int v34; // edi
  int v35; // ecx
  struct TexInfo_s *v36; // edx
  struct TexInfo_s *v37; // ecx
  struct TexInfo_s *paTexInfo; // edx
  int v39; // edx
  struct PalInfo *paPalInfo; // edi
  struct PalInfo *v41; // edi
  struct PalInfo *v42; // edx
  int v43; // edi

  igi2_frame.ptMTPCommon = MTP_tMTPList.ptHead;
  if ( isLoadTextures )
  {
    sprintf(igi2_frame.Buffer, "%stextures/%s.res", MTP_zRootDir, pzBaseName);
    Game_MPRunNetwork(v4);
    if ( Resource_IsLoadedInternal(igi2_frame.Buffer, (struct Resource_s **)igi2_frame.zFilename) )
    {
      *(_DWORD *)(*(_DWORD *)igi2_frame.zFilename + 44) = 1;
    }
    else
    {
      Game_MPRunNetwork(v5);
      v6 = File_Load(igi2_frame.Buffer, (unsigned int *)igi2_frame.zFilename);
      if ( !v6 )
        goto LABEL_5;
      Resource_ParseFile(File_zLastSubstitutedPath, v6, *(unsigned int *)igi2_frame.zFilename);
    }
    Game_MPRunNetwork(v5);
    v7 = ptMTP;
    MTP_ParseChunkTEXF(ptMTP);
    Game_MPRunNetwork(v8);
    MTP_ParseChunkPALF(ptMTP);
    Game_MPRunNetwork(v9);
    if ( Resource_IsLoadedInternal(igi2_frame.Buffer, (struct Resource_s **)igi2_frame.zFilename) )
    {
      v10 = *(_DWORD *)(*(_DWORD *)igi2_frame.zFilename + 36);
      if ( v10 != 3 && v10 != 1 )
        Resource_Remove(*(struct Resource_s **)igi2_frame.zFilename);
    }
  }
  else
  {
    ptMTP->nNumTex = 0;
    ptMTP->nNumPal = 0;
    ptMTP->paTexInfo = nullptr;
    ptMTP->paPalInfo = nullptr;
    ptMTP->paPalInfoExtra = nullptr;
    v7 = ptMTP;
  }
  sprintf(igi2_frame.Buffer, "%smodels/%s.res", MTP_zRootDir, pzBaseName);
  if ( Resource_IsLoadedInternal(igi2_frame.Buffer, (struct Resource_s **)igi2_frame.zFilename) )
  {
    v12 = *(_DWORD *)igi2_frame.zFilename;
    *(_DWORD *)(*(_DWORD *)igi2_frame.zFilename + 44) = 1;
    v13 = *(void **)(v12 + 52);
    goto LABEL_16;
  }
  Game_MPRunNetwork(v11);
  v14 = File_Load(igi2_frame.Buffer, (unsigned int *)igi2_frame.zFilename);
  if ( !v14 )
  {
LABEL_5:
    LDebug_Error("Failed to load resource: '%s'", igi2_frame.Buffer);
    abort();
  }
  v13 = Resource_ParseFile(File_zLastSubstitutedPath, v14, *(unsigned int *)igi2_frame.zFilename);
LABEL_16:
  v7->pxResourceModel = v13;
  MTP_ParseChunkMODS(v7);
  MTP_ParseChunkSVOL(v7);
  MTP_ParseChunkBANM(v7);
  ChunkData = (int *)MTP_GetChunkData(v7->pxRawFile, 0x564E414Du, nullptr);
  v16 = *ChunkData;
  v17 = (char *)&ChunkData[*ChunkData + 1];
  pxRawFile = v7->pxRawFile;
  igi2_frame.pzName = v17;
  result = (char *)MTP_GetChunkData(pxRawFile, 0x494E5354u, nullptr);
  v20 = (char *)result;
  if ( v16 > 0 )
  {
    *(_DWORD *)igi2_frame.zFilename = v16;
    do
    {
      v21 = *(_DWORD *)v20;
      v22 = v20 + 4;
      v23 = 0;
      if ( v21 < 0x2000 )
      {
        ptHead = ptMTP->tModelList.ptHead;
        ptNext = ptHead->ptNext;
        if ( ptHead->ptNext )
        {
          while ( v23 != v21 )
          {
            ptHead = ptNext;
            ptNext = ptNext->ptNext;
            ++v23;
            if ( !ptNext )
              goto LABEL_27;
          }
          goto LABEL_28;
        }
      }
      else
      {
        ptHead = igi2_frame.ptMTPCommon->tModelList.ptHead;
        v25 = ptHead->ptNext;
        if ( ptHead->ptNext )
        {
          v26 = v21 - 0x2000;
          while ( v23 != v26 )
          {
            ptHead = v25;
            v25 = v25->ptNext;
            ++v23;
            if ( !v25 )
              goto LABEL_27;
          }
          goto LABEL_28;
        }
      }
LABEL_27:
      ptHead = nullptr;
LABEL_28:
      v28 = *v22;
      igi2_frame.v44 = 8 * *v22 + 28;
      v20 = (char *)(v22 + 1);
      v29 = Mem_AllocFn(igi2_frame.v44, 4);
      v29[5] = &v29[v28 + 7];
      v29[4] = v29 + 7;
      v29[6] = v28;
      v29[1] = 0;
      *v29 = 0;
      List_AddTail(v29, (int)&ptMTP->tVirModelList);
      v29[3] = ptHead;
      v30 = igi2_frame.pzName;
      v31 = igi2_frame.pzName;
      v29[2] = igi2_frame.pzName;
      v32 = strlen(v31);
      v33 = ptMTP->pxRawFile;
      igi2_frame.pzName = &v30[v32 + 1];
      result = (char *)MTP_GetChunkData(v33, 0x47545420u, nullptr) + 4;
      igi2_frame.nLookIdx = 0;
      if ( v28 > 0 )
      {
        do
        {
          v34 = *(_DWORD *)v20;
          v35 = *(_DWORD *)&result[8 * *(_DWORD *)v20];
          igi2_frame.pzData = v20 + 4;
          if ( v35 < 0x2000 )
          {
            paTexInfo = ptMTP->paTexInfo;
            if ( paTexInfo )
            {
              v37 = &paTexInfo[v35];
              goto LABEL_35;
            }
          }
          else
          {
            v36 = igi2_frame.ptMTPCommon->paTexInfo;
            if ( v36 )
            {
              v37 = &v36[v35 - 0x2000];
              goto LABEL_35;
            }
          }
          v37 = nullptr;
LABEL_35:
          v39 = *(_DWORD *)&result[8 * v34 + 4];
          if ( v39 == -1 )
          {
            paPalInfo = ptMTP->paPalInfo;
          }
          else
          {
            if ( v39 >= 0x2000 )
            {
              v41 = igi2_frame.ptMTPCommon->paPalInfo;
              if ( !v41 )
                goto LABEL_43;
              v42 = &v41[v39 - 0x2000];
              goto LABEL_44;
            }
            paPalInfo = ptMTP->paPalInfoExtra;
          }
          if ( !paPalInfo )
          {
LABEL_43:
            v42 = nullptr;
            goto LABEL_44;
          }
          v42 = &paPalInfo[v39];
LABEL_44:
          v43 = igi2_frame.nLookIdx;
          *(_DWORD *)(v29[4] + 4 * igi2_frame.nLookIdx) = v37;
          v20 = igi2_frame.pzData;
          *(_DWORD *)(v29[5] + 4 * v43) = v42;
          igi2_frame.nLookIdx = v43 + 1;
        }
        while ( v43 + 1 < v28 );
      }
      --*(_DWORD *)igi2_frame.zFilename;
    }
    while ( *(_DWORD *)igi2_frame.zFilename );
  }
  return result;
}

// source: e/3/mtp.c:1176  [size]
int __cdecl MTP_GetInitModelsRenderModeMethod()
{
  return MTP_eInitModelsRenderModeMethod;
}

// source: e/3/mtp.c:1191  [size]
int __cdecl MTP_GetDeinitModelsRenderModeMethod()
{
  return MTP_eDeinitModelsRenderModeMethod;
}

// source: e/3/mtp.c:1206  [size]
int __cdecl MTP_GetLoadModelRenderModeMethod()
{
  return MTP_eLoadModelRenderModeMethod;
}

// source: e/3/mtp.c:1221  [size]
int __cdecl MTP_GetUnloadModelRenderModeMethod()
{
  return MTP_eUnloadModelRenderModeMethod;
}

// source: e/3/mtp.c:1239  [anchor-hash]
struct Model_s *__cdecl MTP_GetModelPtrByName(char *pzModelName)
{
  struct MTP_s *ptHead; // esi
  struct MTP_s *ptNext; // ebp
  char *ChunkData; // eax
  struct Model_s *v4; // ebx
  struct Model_s *v5; // esi
  char *v6; // edi

  ptHead = MTP_tMTPList.ptHead;
  ptNext = MTP_tMTPList.ptHead->ptNext;
  if ( !MTP_tMTPList.ptHead->ptNext )
    return nullptr;
  while ( 1 )
  {
    ChunkData = (char *)MTP_GetChunkData(ptHead->pxRawFile, 0x4D4F4453u, nullptr);
    v4 = ptHead->tModelList.ptHead;
    v5 = v4->ptNext;
    v6 = ChunkData + 4;
    if ( v4->ptNext )
      break;
LABEL_5:
    ptHead = ptNext;
    ptNext = ptNext->ptNext;
    if ( !ptNext )
      return nullptr;
  }
  while ( _stricmp(pzModelName, v6) )
  {
    v4 = v5;
    v5 = v5->ptNext;
    v6 += strlen(v6) + 1;
    if ( !v5 )
      goto LABEL_5;
  }
  return v4;
}

// source: e/3/mtp.c:1291  [anchor-caller]
struct Shadow_Volume_s *__cdecl MTP_GetShadowVolumePtrByName(char *pzVolumeName)
{
  struct MTP_s *ptHead; // esi
  struct MTP_s *ptNext; // ebp
  char *ChunkData; // eax
  struct Shadow_Volume_s *v4; // ebx
  struct Shadow_Volume_s *v5; // esi
  char *v6; // edi

  ptHead = MTP_tMTPList.ptHead;
  ptNext = MTP_tMTPList.ptHead->ptNext;
  if ( !MTP_tMTPList.ptHead->ptNext )
    return nullptr;
  while ( 1 )
  {
    ChunkData = (char *)MTP_GetChunkData(ptHead->pxRawFile, 0x53564F4Cu, nullptr);
    v4 = ptHead->tShadowVolumeList.ptHead;
    v5 = v4->ptNext;
    v6 = ChunkData + 4;
    if ( v4->ptNext )
      break;
LABEL_5:
    ptHead = ptNext;
    ptNext = ptNext->ptNext;
    if ( !ptNext )
      return nullptr;
  }
  while ( _stricmp(pzVolumeName, v6) )
  {
    v4 = v5;
    v5 = v5->ptNext;
    v6 += strlen(v6) + 1;
    if ( !v5 )
      goto LABEL_5;
  }
  return v4;
}

// source: e/3/mtp.c:1341  [anchor-callee]
struct LODVirModel_s *__cdecl MTP_GetLODVirModel(char *zName)
{
  struct LODVirModel_s *result; // eax
  int v2; // edi
  int v3; // esi
  char v4; // dl

  if ( !zName )
    return nullptr;
  v2 = MTP_nLODVirModel;
  if ( MTP_nLODVirModel >= 600 )
  {
    LDebug_Error("MTP_nLODVirModel >= %d", 600);
    abort();
  }
  result = (struct LODVirModel_s *)(200272 * MTP_nLODVirModel + 7681696);
  v3 = 200272 * MTP_nLODVirModel + 7681716 - (_DWORD)zName;
  do
  {
    v4 = *zName;
    zName[v3] = *zName;
    ++zName;
  }
  while ( v4 );
  MTP_nLODVirModel = v2 + 1;
  return result;
}

// source: e/3/mtp.c:1371  [anchor-callee]
struct LODVirModel_s *__cdecl MTP_GetLODVirModelExistsFn(char *zName)
{
  int v1; // edi
  int v2; // ebp
  char *zFirstVirModelName; // esi
  char *v4; // edx
  int v6; // edi
  char *v7; // eax
  char v8; // cl

  v1 = MTP_nLODVirModel;
  v2 = 0;
  if ( MTP_nLODVirModel > 0 )
  {
    zFirstVirModelName = MTP_atLODVirModel[0].zFirstVirModelName;
    while ( 1 )
    {
      v4 = zName;
      if ( !strcmp(zName, zFirstVirModelName) )
        break;
      ++v2;
      zFirstVirModelName += 200272;
      if ( v2 >= MTP_nLODVirModel )
      {
        v1 = MTP_nLODVirModel;
        goto LABEL_10;
      }
    }
    if ( MTP_atLODVirModel[v2].nLOD || !strcmp(zName, "none") )
      return &MTP_atLODVirModel[v2];
    return nullptr;
  }
  v4 = zName;
LABEL_10:
  if ( v1 >= 600 )
  {
    LDebug_Error("MTP_nLODVirModel >= %d", 600);
    abort();
  }
  v6 = v1;
  v7 = v4;
  do
  {
    v8 = *v7;
    v7[MTP_atLODVirModel[v6].zFirstVirModelName - zName] = *v7;
    ++v7;
  }
  while ( v8 );
  MTP_CreateLODVirModel(&MTP_atLODVirModel[v6]);
  if ( !MTP_atLODVirModel[v6].nLOD )
    return nullptr;
  ++MTP_nLODVirModel;
  return &MTP_atLODVirModel[v6];
}

// source: e/3/mtp.c:1422  [anchor-hash]
struct LODVirModel_s *__cdecl MTP_GetLODVirModelExists(char *zName)
{
  return MTP_GetLODVirModelExistsFn(zName);
}

// source: e/3/mtp.c:1453  [size]
void __cdecl MTP_InitLODVirModelSystem()
{
  MTP_nLODVirModel = MTP_nLODVirModelInOpen;
}

// source: e/3/mtp.c:1468  [anchor-hash]
void __cdecl MTP_Open()
{
  enum RenderMode_enum v0; // eax
  enum RenderMode_enum v1; // eax
  enum RenderMode_enum v2; // eax
  enum RenderMode_enum v3; // eax

  v0 = APPCONTEXT_RENDER_MODE_SOFTWARE;
  memset(MTP_atLODVirModel, 0, 4 * (_DWORD)&MTP_atLODVirModel[111].atBoneVertexRefs[32].atVertexRefs[177]);
  MTP_tMTPList.ptHead = (struct MTP_s *)&MTP_tMTPList.ptMiddle;
  MTP_tMTPList.ptTail = (struct MTP_s *)&MTP_tMTPList;
  MTP_tMTPList.ptMiddle = nullptr;
  MTP_zRootDir[0] = 0;
  MTP_nLODVirModel = 0;
  MTP_nLODVirModelInOpen = 0;
  while ( RenderMode_atRenderModeMethod[v0].isAllocated )
  {
    if ( ++v0 >= 128 )
    {
      LDebug_Error("RenderMode: Failed to create new method '%s'", "InitModels");
      goto LABEL_5;
    }
  }
  RenderMode_atRenderModeMethod[v0].zName = "InitModels";
  RenderMode_atRenderModeMethod[v0].isAllocated = 1;
  MTP_eInitModelsRenderModeMethod = v0;
  v1 = APPCONTEXT_RENDER_MODE_SOFTWARE;
  while ( RenderMode_atRenderModeMethod[v1].isAllocated )
  {
    if ( ++v1 >= 128 )
    {
      LDebug_Error("RenderMode: Failed to create new method '%s'", "DeinitModels");
      goto LABEL_5;
    }
  }
  RenderMode_atRenderModeMethod[v1].zName = "DeinitModels";
  RenderMode_atRenderModeMethod[v1].isAllocated = 1;
  MTP_eDeinitModelsRenderModeMethod = v1;
  v2 = APPCONTEXT_RENDER_MODE_SOFTWARE;
  while ( RenderMode_atRenderModeMethod[v2].isAllocated )
  {
    if ( ++v2 >= 128 )
    {
      LDebug_Error("RenderMode: Failed to create new method '%s'", "LoadModel");
      goto LABEL_5;
    }
  }
  RenderMode_atRenderModeMethod[v2].zName = "LoadModel";
  RenderMode_atRenderModeMethod[v2].isAllocated = 1;
  MTP_eLoadModelRenderModeMethod = v2;
  v3 = APPCONTEXT_RENDER_MODE_SOFTWARE;
  while ( RenderMode_atRenderModeMethod[v3].isAllocated )
  {
    if ( ++v3 >= 128 )
    {
      LDebug_Error("RenderMode: Failed to create new method '%s'", "UnloadModel");
LABEL_5:
      abort();
    }
  }
  RenderMode_atRenderModeMethod[v3].isAllocated = 1;
  RenderMode_atRenderModeMethod[v3].zName = "UnloadModel";
  MTP_eUnloadModelRenderModeMethod = v3;
  MTP_ptMissingModel = MTP_GetLODVirModel("missing");
}

// source: e/3/mtp.c:1497  [size]
void __cdecl MTP_SetOpenedLODVirModels()
{
  MTP_nLODVirModelInOpen = MTP_nLODVirModel;
}

// source: e/3/mtp.c:1513  [anchor-hash]
void __cdecl MTP_Close()
{
  struct MTP_s *ptTail; // eax
  struct MTP_s *i; // esi
  enum RenderMode_enum v2; // ecx
  enum RenderMode_enum v3; // edx
  enum RenderMode_enum v4; // eax

  ptTail = MTP_tMTPList.ptTail;
  for ( i = MTP_tMTPList.ptTail->ptPrev; i; i = i->ptPrev )
  {
    MTP_Free(ptTail);
    ptTail = i;
  }
  v2 = MTP_eLoadModelRenderModeMethod;
  v3 = MTP_eDeinitModelsRenderModeMethod;
  RenderMode_atRenderModeMethod[MTP_eUnloadModelRenderModeMethod].isAllocated = 0;
  v4 = MTP_eInitModelsRenderModeMethod;
  RenderMode_atRenderModeMethod[v2].isAllocated = 0;
  RenderMode_atRenderModeMethod[v3].isAllocated = 0;
  RenderMode_atRenderModeMethod[v4].isAllocated = 0;
}

// source: e/3/mtp.c:1542  [anchor-strings]
struct MTP_s *__cdecl MTP_Load(char *pzName)
{
  #pragma pack(push, 1)
  union
  {
    struct { char zFilename[4]; };
    struct { char igi2_o1[4]; char Buffer[64]; };
    char igi2_extent[68];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct MTP_s *v2; // esi
  char *v3; // ecx
  char *v4; // ecx
  int v5; // eax
  void *v6; // eax
  void *v7; // eax
  char *v8; // ecx
  struct LODVirModel_s *v9; // edi

  v2 = (struct MTP_s *)Mem_AllocFn(88, 4);
  v2->ptPrev = nullptr;
  v2->ptNext = nullptr;
  v2->isMTPFileEmbedded = 0;
  List_AddTail(v2, (int)&MTP_tMTPList);
  v2->tModelList.ptHead = (struct Model_s *)&v2->tModelList.ptMiddle;
  v2->tModelList.ptMiddle = nullptr;
  v2->tModelList.ptTail = (struct Model_s *)&v2->tModelList;
  v2->tVirModelList.ptHead = (struct VirModel_s *)&v2->tVirModelList.ptMiddle;
  v2->tVirModelList.ptMiddle = nullptr;
  v2->tVirModelList.ptTail = (struct VirModel_s *)&v2->tVirModelList;
  v2->tShadowVolumeList.ptHead = (struct Shadow_Volume_s *)&v2->tShadowVolumeList.ptMiddle;
  v2->tShadowVolumeList.ptMiddle = nullptr;
  v2->tShadowVolumeList.ptTail = (struct Shadow_Volume_s *)&v2->tShadowVolumeList;
  v2->tAnimHeaderList.ptHead = (struct AnimHeader_s *)&v2->tAnimHeaderList.ptMiddle;
  v2->tAnimHeaderList.ptMiddle = nullptr;
  v2->tAnimHeaderList.ptTail = (struct AnimHeader_s *)&v2->tAnimHeaderList;
  sprintf(igi2_frame.Buffer, "%s%s.mtp", MTP_zRootDir, pzName);
  Game_MPRunNetwork(v3);
  if ( Resource_IsLoadedInternal(igi2_frame.Buffer, (struct Resource_s **)igi2_frame.zFilename) )
  {
    v5 = *(_DWORD *)igi2_frame.zFilename;
    *(_DWORD *)(*(_DWORD *)igi2_frame.zFilename + 44) = 1;
    v6 = *(void **)(v5 + 52);
  }
  else
  {
    Game_MPRunNetwork(v4);
    v7 = File_Load(igi2_frame.Buffer, (unsigned int *)igi2_frame.zFilename);
    if ( !v7 )
    {
      LDebug_Error("Failed to load resource: '%s'", igi2_frame.Buffer);
      abort();
    }
    v6 = Resource_ParseFile(File_zLastSubstitutedPath, v7, *(unsigned int *)igi2_frame.zFilename);
  }
  v2->pxRawFile = v6;
  MTP_ParseMTP(v2, pzName, (enum bool)(AppContext_tAppContext.isServer == false));
  Game_MPRunNetwork(v8);
  v9 = MTP_atLODVirModel;
  do
  {
    if ( v9 != (struct LODVirModel_s *)-20 )
      MTP_CreateLODVirModel(v9);
    ++v9;
  }
  while ( (int)v9 < 127844896 );
  return v2;
}

// source: e/3/mtp.c:1593  [anchor-mhash]
struct MTP_s *__cdecl MTP_New(void *pxMTPFile, int nMTPFileSize)
{
  _DWORD *v3; // eax
  struct MTP_s *result; // eax

  v3 = Mem_AllocFn(nMTPFileSize + 88, 4);
  v3[1] = 0;
  *v3 = 0;
  v3[21] = 1;
  result = (struct MTP_s *)List_AddTail(v3, (int)&MTP_tMTPList);
  result->tModelList.ptMiddle = nullptr;
  result->tVirModelList.ptMiddle = nullptr;
  result->tModelList.ptHead = (struct Model_s *)&result->tModelList.ptMiddle;
  result->tModelList.ptTail = (struct Model_s *)&result->tModelList;
  result->tVirModelList.ptHead = (struct VirModel_s *)&result->tVirModelList.ptMiddle;
  result->tVirModelList.ptTail = (struct VirModel_s *)&result->tVirModelList;
  result->tShadowVolumeList.ptMiddle = nullptr;
  result->tShadowVolumeList.ptHead = (struct Shadow_Volume_s *)&result->tShadowVolumeList.ptMiddle;
  result->tShadowVolumeList.ptTail = (struct Shadow_Volume_s *)&result->tShadowVolumeList;
  result->tAnimHeaderList.ptMiddle = nullptr;
  result->tAnimHeaderList.ptHead = (struct AnimHeader_s *)&result->tAnimHeaderList.ptMiddle;
  result->tAnimHeaderList.ptTail = (struct AnimHeader_s *)&result->tAnimHeaderList;
  qmemcpy(&result[1], pxMTPFile, nMTPFileSize);
  result->pxRawFile = &result[1];
  return result;
}

// source: e/3/mtp.c:1634  [anchor-hash]
void __cdecl MTP_InstallTextures(struct MTP_s *ptMTP)
{

  MTP_ParseChunkTEXF(ptMTP);
  MTP_ParseChunkPALF(ptMTP);
}

// source: e/3/mtp.c:1652  [size]
struct MTP_s *__cdecl MTP_InstallRest(struct MTP_s *ptMTP, char *pzName)
{
  struct MTP_s *result; // eax
  struct LODVirModel_s *v3; // esi

  result = (struct MTP_s *)MTP_ParseMTP(ptMTP, pzName, false);
  v3 = MTP_atLODVirModel;
  do
  {
    if ( v3 != (struct LODVirModel_s *)-20 )
      result = (struct MTP_s *)MTP_CreateLODVirModel(v3);
    ++v3;
  }
  while ( (int)v3 < 127844896 );
  return result;
}

// source: e/3/mtp.c:1673  [anchor-caller]
struct MTP_s *__cdecl MTP_Free(struct MTP_s *ptMTP)
{
  __int32 eRenderMode; // ecx
  int v3; // edi
  int v4; // esi
  struct PalInfo *paPalInfoExtra; // eax
  struct PalInfo *v6; // eax
  struct PalInfo *v7; // eax
  int v8; // esi
  int v9; // edi
  int v10; // esi
  struct PalInfo *paPalInfo; // eax
  struct PalInfo *v12; // eax
  struct PalInfo *v13; // eax
  int v14; // esi
  int v15; // eax
  int v16; // esi
  int nNumTex; // ebp
  struct TexInfo_s *v18; // edi
  struct TexInfo_s *paTexInfo; // eax
  int v20; // esi
  struct Shadow_Volume_s *ptTail; // edi
  struct Shadow_Volume_s *i; // esi
  struct AnimHeader_s *v23; // esi
  struct AnimHeader_s *j; // ebp
  unsigned __int8 *ptHierarchy; // eax
  struct QHashTable_s *v26; // edi
  unsigned int v27; // eax
  int v28; // eax
  int v29; // edi
  int v30; // eax
  struct Resource_s *ptNext; // eax
  void *pxRawFile; // esi
  unsigned int v33; // eax
  struct Model_s *v34; // edi
  struct Model_s *k; // esi
  struct VirModel_s *v36; // eax
  struct VirModel_s *m; // ebp
  _DWORD **v38; // eax
  int v39; // esi
  struct Resource_s *ptHead; // ecx
  struct Resource_s *v41; // eax
  unsigned int nType; // eax
  struct Resource_s *v43; // ecx
  struct Resource_s *v44; // eax
  unsigned int v45; // eax
  int v46; // esi
  char *v47; // ecx
  struct LODVirModel_s *v48; // esi
  struct MTP_s *result; // eax

  Node_Remove(ptMTP);
  v3 = 0;
  if ( ptMTP->nNumPal > 0 )
  {
    v4 = 0;
    do
    {
      Game_MPRunNetwork((char *)eRenderMode);
      paPalInfoExtra = ptMTP->paPalInfoExtra;
      eRenderMode = paPalInfoExtra[v4].eRenderMode;
      v6 = &paPalInfoExtra[v4];
      if ( eRenderMode != -1 )
        RenderMode_atRenderMode[eRenderMode].apfRenderModeMethod[Palette_eDeAllocPaletteMethod](v6);
      ++v3;
      ++v4;
    }
    while ( v3 < ptMTP->nNumPal );
  }
  if ( ptMTP->paPalInfoExtra )
  {
    Game_MPRunNetwork((char *)eRenderMode);
    v7 = ptMTP->paPalInfoExtra;
    if ( v7 )
    {
      v8 = *(_DWORD *)((unsigned int)&v7[-1].pxPalette & 0xFFFFFFFC);
      --Mem_nCurrentAllocations;
      Node_Remove((_DWORD **)v8);
      memset(*(void **)(v8 + 8), 0xCDu, *(_DWORD *)(v8 + 16));
      free((void *)v8);
    }
    ptMTP->paPalInfoExtra = nullptr;
  }
  v9 = 0;
  if ( ptMTP->nNumTex > 0 )
  {
    v10 = 0;
    do
    {
      if ( ptMTP->paPalInfo[v10].nPalette )
      {
        Game_MPRunNetwork((char *)eRenderMode);
        paPalInfo = ptMTP->paPalInfo;
        eRenderMode = paPalInfo[v10].eRenderMode;
        v12 = &paPalInfo[v10];
        if ( eRenderMode != -1 )
          RenderMode_atRenderMode[eRenderMode].apfRenderModeMethod[Palette_eDeAllocPaletteMethod](v12);
      }
      ++v9;
      ++v10;
    }
    while ( v9 < ptMTP->nNumTex );
  }
  if ( ptMTP->paPalInfo )
  {
    Game_MPRunNetwork((char *)eRenderMode);
    v13 = ptMTP->paPalInfo;
    if ( v13 )
    {
      v14 = *(_DWORD *)((unsigned int)&v13[-1].pxPalette & 0xFFFFFFFC);
      --Mem_nCurrentAllocations;
      Node_Remove((_DWORD **)v14);
      memset(*(void **)(v14 + 8), 0xCDu, *(_DWORD *)(v14 + 16));
      free((void *)v14);
    }
    ptMTP->paPalInfo = nullptr;
  }
  v15 = ptMTP->nNumTex - 1;
  if ( v15 >= 0 )
  {
    v16 = v15;
    nNumTex = ptMTP->nNumTex;
    do
    {
      Game_MPRunNetwork((char *)eRenderMode);
      v18 = &ptMTP->paTexInfo[v16];
      if ( AppContext_tAppContext.isMainMenu == false )
        RenderMode_atRenderMode[v18->eRenderMode].apfRenderModeMethod[Texture_eDeAllocTextureMethod](v18);
      --v16;
      --nNumTex;
      memset(v18, 0, sizeof(struct TexInfo_s));
      eRenderMode = 0;
    }
    while ( nNumTex );
  }
  if ( ptMTP->paTexInfo )
  {
    Game_MPRunNetwork((char *)eRenderMode);
    paTexInfo = ptMTP->paTexInfo;
    if ( paTexInfo )
    {
      v20 = *(_DWORD *)((unsigned int)&paTexInfo[-1].eDirect3DFormat & 0xFFFFFFFC);
      --Mem_nCurrentAllocations;
      Node_Remove((_DWORD **)v20);
      memset(*(void **)(v20 + 8), 0xCDu, *(_DWORD *)(v20 + 16));
      free((void *)v20);
    }
    ptMTP->paTexInfo = nullptr;
  }
  ptTail = ptMTP->tShadowVolumeList.ptTail;
  for ( i = ptTail->ptPrev; i; i = i->ptPrev )
  {
    Game_MPRunNetwork((char *)eRenderMode);
    MTP_ShadowVolumeFree(ptTail);
    ptTail = i;
  }
  v23 = ptMTP->tAnimHeaderList.ptTail;
  for ( j = v23->ptPrev; j; j = j->ptPrev )
  {
    ptHierarchy = v23->ptHierarchy;
    if ( ptHierarchy )
    {
      v26 = Hierarchy_ptHashTable;
      v27 = Hierarchy_ptHashTable->tPrivate.pfHashFunction(Hierarchy_ptHashTable->tPrivate.nHashTableSize, ptHierarchy);
      v28 = ((int  (__cdecl *)(struct QHashTable_s *, unsigned int, const void *))Hierarchy_ptHashTable->tPrivate.pfFindElement)(v26, v27, (const void *)(ptHierarchy));
      if ( v28 )
      {
        v29 = *(_DWORD *)v28;
        v30 = (*(int (__cdecl **)(_DWORD, char *))(*(_DWORD *)v28 + 12))(*(_DWORD *)(*(_DWORD *)v28 + 4), v23->zName);
        (*(void (__cdecl **)(int, int, const void *))(v29 + 32))(v29, v30, (const void *)(v23->zName));
      }
    }
    Node_Remove(v23);
    eRenderMode = (__int32)Resource_tResourceList.ptHead;
    ptNext = Resource_tResourceList.ptHead->ptNext;
    pxRawFile = v23->pxRawFile;
    if ( Resource_tResourceList.ptHead->ptNext )
    {
      while ( *(void **)(eRenderMode + 52) != pxRawFile )
      {
        eRenderMode = (__int32)ptNext;
        ptNext = ptNext->ptNext;
        if ( !ptNext )
          goto LABEL_42;
      }
      v33 = *(_DWORD *)(eRenderMode + 36);
      if ( v33 != 3 && v33 != 1 )
        Resource_Remove((struct Resource_s *)eRenderMode);
    }
LABEL_42:
    v23 = j;
  }
  v34 = ptMTP->tModelList.ptTail;
  for ( k = v34->ptPrev; k; k = k->ptPrev )
  {
    Game_MPRunNetwork((char *)eRenderMode);
    MTP_ModelFree(v34);
    v34 = k;
  }
  v36 = ptMTP->tVirModelList.ptTail;
  for ( m = v36->ptPrev; m; m = m->ptPrev )
  {
    v38 = Node_Remove(v36);
    if ( v38 )
    {
      v39 = *(_DWORD *)((unsigned int)(v38 - 1) & 0xFFFFFFFC);
      --Mem_nCurrentAllocations;
      Node_Remove((_DWORD **)v39);
      memset(*(void **)(v39 + 8), 0xCDu, *(_DWORD *)(v39 + 16));
      free((void *)v39);
    }
    v36 = m;
  }
  Game_MPRunNetwork((char *)eRenderMode);
  ptHead = Resource_tResourceList.ptHead;
  v41 = Resource_tResourceList.ptHead->ptNext;
  if ( Resource_tResourceList.ptHead->ptNext )
  {
    while ( ptHead->pxData != ptMTP->pxResourceModel )
    {
      ptHead = v41;
      v41 = v41->ptNext;
      if ( !v41 )
        goto LABEL_56;
    }
    nType = ptHead->nType;
    if ( nType != 3 && nType != 1 )
      Resource_Remove(ptHead);
  }
LABEL_56:
  if ( !ptMTP->isMTPFileEmbedded )
  {
    Game_MPRunNetwork((char *)ptHead);
    v43 = Resource_tResourceList.ptHead;
    v44 = Resource_tResourceList.ptHead->ptNext;
    if ( Resource_tResourceList.ptHead->ptNext )
    {
      while ( v43->pxData != ptMTP->pxRawFile )
      {
        v43 = v44;
        v44 = v44->ptNext;
        if ( !v44 )
          goto LABEL_64;
      }
      v45 = v43->nType;
      if ( v45 != 3 && v45 != 1 )
        Resource_Remove(v43);
    }
  }
LABEL_64:
  v46 = *(_DWORD *)((unsigned int)&ptMTP[-1].isMTPFileEmbedded & 0xFFFFFFFC);
  --Mem_nCurrentAllocations;
  Node_Remove((_DWORD **)v46);
  memset(*(void **)(v46 + 8), 0xCDu, *(_DWORD *)(v46 + 16));
  free((void *)v46);
  Game_MPRunNetwork(v47);
  v48 = MTP_atLODVirModel;
  do
  {
    result = (struct MTP_s *)v48->zFirstVirModelName;
    if ( v48 != (struct LODVirModel_s *)-20 )
      result = (struct MTP_s *)MTP_CreateLODVirModel(v48);
    ++v48;
  }
  while ( (int)v48 < 127844896 );
  return result;
}

// source: e/3/mtp.c:1795  [size]
char *__cdecl MTP_SetRootDir(char *pzNewRootDir)
{
  int v1; // edx
  char v2; // cl

  v1 = MTP_zRootDir - pzNewRootDir;
  do
  {
    v2 = *pzNewRootDir;
    pzNewRootDir[v1] = *pzNewRootDir;
    ++pzNewRootDir;
  }
  while ( v2 );
  return pzNewRootDir;
}

// source: e/3/mtp.c:1813  [size]
char *__cdecl MTP_SetAnimationRootDir(char *pzNewAnimationRootDir)
{
  int v1; // edx
  char v2; // cl

  v1 = MTP_zAnimationRootDir - pzNewAnimationRootDir;
  do
  {
    v2 = *pzNewAnimationRootDir;
    pzNewAnimationRootDir[v1] = *pzNewAnimationRootDir;
    ++pzNewAnimationRootDir;
  }
  while ( v2 );
  return pzNewAnimationRootDir;
}

// source: e/3/mtp.c:1828  [size]
struct LODVirModel_s *__cdecl MTP_GetLODVirModelArray()
{
  return MTP_atLODVirModel;
}

// source: e/3/mtp.c:1843  [size]
int __cdecl MTP_GetLODVirModelCount()
{
  return MTP_nLODVirModel;
}

// source: e/3/mtp.c:1858  [size]
int __cdecl MTP_GetMTPCount()
{
  return List_Length(&MTP_tMTPList);
}

// source: e/3/mtp.c:1873  [anchor-hash]
struct MTP_s *__cdecl MTP_GetMTP(int iMTP)
{
  struct MTP_s *result; // eax
  struct MTP_s *ptNext; // ecx
  int v3; // edx

  result = MTP_tMTPList.ptHead;
  ptNext = MTP_tMTPList.ptHead->ptNext;
  v3 = 0;
  if ( !MTP_tMTPList.ptHead->ptNext )
    return nullptr;
  while ( v3 != iMTP )
  {
    result = ptNext;
    ptNext = ptNext->ptNext;
    ++v3;
    if ( !ptNext )
      return nullptr;
  }
  return result;
}

// source: e/3/mtp.c:1902  [anchor-hash]
struct LODVirModel_s *__cdecl MTP_GetBoneLODVirModel(char *zModel)
{
  struct LODVirModel_s *result; // eax
  struct Model_s *ptModel; // ecx
  struct Mesh3D_Mesh_t *ptMesh; // ecx

  result = MTP_GetLODVirModelExistsFn(zModel);
  if ( !result )
    return nullptr;
  if ( result->nLOD <= 0 )
    return nullptr;
  if ( !result->aptVirModel[0] )
    return nullptr;
  ptModel = result->aptVirModel[0]->ptModel;
  if ( !ptModel )
    return nullptr;
  ptMesh = ptModel->ptMesh;
  if ( !ptMesh || ptMesh->eRenderMeshType != MESH3D_RENDERMESHTYPE_DIRECT3D_BONE )
    return nullptr;
  return result;
}
