/* h/2/texturemodifier.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: h/2/texturemodifier.c:270  [anchor-strings]
struct World_s *__cdecl TextureModifier_SaveBitmap(struct World_s *ptWorld)
{
  #pragma pack(push, 1)
  union
  {
    struct { int v12; };
    struct { char igi2_o1[4]; char zFileName[256]; };
    struct { char igi2_o2[260]; char zWarning[1024]; };
    char igi2_extent[1284];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct Terrain_MaterialBitmap_t *ptMaterialBitmap; // ebx
  int v2; // eax
  char v3; // cl
  char *v4; // edi
  struct File_s *v6; // esi
  struct Terrain_MaterialBitmap_t *v7; // eax
  int v8; // ecx
  struct Terrain_MaterialBitmap_t *v9; // edi
  struct World_s *result; // eax
  char *RealFilename; // eax

  ptMaterialBitmap = ptWorld->ptMaterialBitmap;
  v2 = 0;
  do
  {
    v3 = World_zTerrainFileName[v2];
    igi2_frame.zFileName[v2++] = v3;
  }
  while ( v3 );
  v4 = (char *)&igi2_frame.v12 + 3;
  while ( *++v4 )
    ;
  strcpy(v4, ".bit");
  v6 = File_New(igi2_frame.zFileName, "w");
  if ( v6 )
  {
    v7 = ptMaterialBitmap;
    v8 = 256;
    do
    {
      if ( !v7->ptBitmap )
        v7->nSize = 0;
      ++v7;
      --v8;
    }
    while ( v8 );
    File_atDevice[v6->eDeviceID].pfWrite(v6->eDeviceID, v6, ptMaterialBitmap, 3072u);
    File_atDevice[v6->eDeviceID].pfSync(v6->eDeviceID, v6, FILE_SYNC_WAIT);
    v9 = ptMaterialBitmap;
    igi2_frame.v12 = 256;
    do
    {
      if ( v9->ptBitmap )
      {
        File_atDevice[v6->eDeviceID].pfWrite(v6->eDeviceID, v6, v9->ptBitmap, v9->nSize * v9->nSize / 8);
        File_atDevice[v6->eDeviceID].pfSync(v6->eDeviceID, v6, FILE_SYNC_WAIT);
      }
      ++v9;
      result = (struct World_s *)--igi2_frame.v12;
    }
    while ( igi2_frame.v12 );
    if ( v6 == &File_tDummyAsyncFile )
      File_tDummyAsyncFile.isAsync = false;
    else
      return ((struct World_s *(__cdecl *)(int, struct File_s *))File_atDevice[v6->eDeviceID].pfDelete)(
               v6->eDeviceID,
               v6);
  }
  else
  {
    RealFilename = File_GetRealFilename(igi2_frame.zFileName);
    return (struct World_s *)sprintf(igi2_frame.zWarning, "File '%s' could not be opened for writing.", RealFilename);
  }
  return result;
}

// source: h/2/texturemodifier.c:336  [anchor-mhash]
void __cdecl TextureModifier_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ptQTask[2].ptParent = (struct QTask_s *)World_ptActiveWorld;
  *(_DWORD *)&ptQTask[4].eQTaskType = -1;
  ptQTask[5].ptNext = (struct QTask_s *)-1;
  *(_DWORD *)&ptQTask[5].eQTaskType = -1;
  ptQTask[3].ptNext = nullptr;
  ptQTask[3].ptPrev = nullptr;
  ptQTask[3].tQTaskChildren.ptHead = nullptr;
  ptQTask[3].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[3].tQTaskChildren.ptTail = nullptr;
  ptQTask[3].tQTaskRefList.ptHead = nullptr;
  ptQTask[3].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[3].tQTaskRefList.ptTail = nullptr;
  ptQTask[3].ptParent = nullptr;
  *(_DWORD *)&ptQTask[3].eQTaskType = 0;
  ptQTask[4].ptNext = nullptr;
  ptQTask[4].ptPrev = nullptr;
  ptQTask[4].tQTaskChildren.ptHead = nullptr;
  ptQTask[4].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[4].tQTaskChildren.ptTail = nullptr;
  ptQTask[4].tQTaskRefList.ptHead = nullptr;
  ptQTask[4].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[4].tQTaskRefList.ptTail = nullptr;
  ptQTask[4].ptParent = (struct QTask_s *)10;
  ptQTask[5].ptPrev = nullptr;
  LOBYTE(ptQTask[5].tQTaskChildren.ptTail) = 0;
  ptQTask[5].tQTaskRefList.ptMiddle = (struct QReference_s *)32;
  BYTE1(ptQTask[5].tQTaskChildren.ptTail) = 0;
  LOBYTE(ptQTask[5].tQTaskRefList.ptHead) = 0;
  ptQTask[5].ptParent = nullptr;
  BYTE2(ptQTask[5].tQTaskChildren.ptTail) = 0;
  HIBYTE(ptQTask[5].tQTaskChildren.ptTail) = 1;
  ptQTask[6].ptNext = nullptr;
  BYTE1(ptQTask[5].tQTaskRefList.ptHead) = 1;
  TextureModifier_tRandomState.anRandom[0] = -773192938;
  TextureModifier_tRandomState.anRandom[1] = -965544106;
  TextureModifier_tRandomState.anRandom[2] = 1572805325;
}

// source: h/2/texturemodifier.c:684  [anchor-strings]
int __cdecl TextureModifier_EnterHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptParent; // edx
  int result; // eax
  int v3; // eax
  unsigned int v4; // edx

  ptParent = ptQTask[2].ptParent;
  result = (int)ptParent->tQTaskChildren.ptMiddle;
  if ( result )
  {
    result = *(_DWORD *)&ptQTask[4].eQTaskType;
    if ( result >= 0 && (result *= 3, *((_DWORD *)&ptParent[9].ptNext->ptNext + result)) )
    {
      v3 = TextureModifier_nStackItem;
      if ( TextureModifier_nStackItem >= 20 )
      {
        LDebug_Error("Too many items in texture modifier stack!");
        abort();
      }
      v4 = *(_DWORD *)&ptQTask[5].eQTaskType;
      ptQTask[5].tQTaskRefList.ptTail = (struct QReference_s *)1;
      TextureModifier_aiStackItem[v3] = v4;
      result = v3 + 1;
      TextureModifier_biTextureModifier = (TextureModifier_biTextureModifier << 8)
                                        | (*(_DWORD *)&ptQTask[5].eQTaskType + 1);
      TextureModifier_nStackItem = result;
    }
    else
    {
      ptQTask[5].tQTaskRefList.ptTail = nullptr;
    }
  }
  return result;
}

// source: h/2/texturemodifier.c:730  [anchor-mhash]
void __cdecl TextureModifier_LeaveHandler(struct QTask_s *ptQTask, void *pxContext)
{
  if ( ptQTask[2].ptParent->tQTaskChildren.ptMiddle && ptQTask[5].tQTaskRefList.ptTail )
  {
    --TextureModifier_nStackItem;
    TextureModifier_biTextureModifier >>= 8;
    if ( TextureModifier_nStackItem - 4 >= 0 )
      TextureModifier_biTextureModifier |= (TextureModifier_aiStackItem[TextureModifier_nStackItem - 4] << 24) + 1;
  }
}

// source: h/2/texturemodifier.c:802  [anchor-mhash]
void __cdecl TextureModifier_DeleteHandler(struct QTask_s *ptQTask)
{
  int v1; // eax
  int v2; // edx
  struct TextureModifier_t *v3; // ecx

  if ( World_ptActiveWorld->ptCubeTree )
  {
    if ( !LOBYTE(ptQTask[5].tQTaskRefList.ptHead) )
    {
      v1 = *(_DWORD *)&ptQTask[5].eQTaskType;
      if ( v1 != -1 )
      {
        v2 = TextureModifier_nTextureModifier - 1;
        if ( v1 != TextureModifier_nTextureModifier - 1 )
        {
          v3 = *((struct TextureModifier_t **)&TextureModifier_eQTaskType + TextureModifier_nTextureModifier);
          TextureModifier_aptTextureModifier[v1] = v3;
          v3->iGlobalList = v1;
        }
        TextureModifier_nTextureModifier = v2;
      }
    }
    World_RemoveDynCubeObj((struct World_s *)ptQTask[2].ptParent, (struct DynCubeObj_s *)ptQTask);
  }
}

// source: h/2/texturemodifier.c:844  [size]
void __cdecl TextureModifier_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = TextureModifier_ptParameterList;
}

// source: h/2/texturemodifier.c:1328  [anchor-callee]
int __cdecl TextureModifier_SnapSize(int nSize)
{
  if ( nSize >= 256 )
    return 256;
  if ( nSize >= 128 )
    return 128;
  if ( nSize >= 64 )
    return 64;
  if ( nSize < 32 )
    return 8 * (nSize >= 16) + 8;
  return 32;
}

// source: h/2/texturemodifier.c:1375  [anchor-mhash]
void __cdecl TextureModifier_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct QTask_s *v43; };
    struct { char igi2_o1[48]; int nCubeSize; };
    struct { char igi2_o2[48]; int nCubeSizea; };
    struct { char igi2_o3[48]; int nCubeSizeb; };
    struct { char igi2_o4[48]; int nCubeSizec; };
    struct { char igi2_o5[52]; struct QTask_s *ptMaterialBitmap; };
    struct { char igi2_o6[52]; int ptMaterialBitmapa; };
    struct { char igi2_o7[56]; double vHighestZ; };
    struct { char igi2_o8[56]; double vHighestZa; };
    struct { char igi2_o9[56]; double vHighestZb; };
    struct { char igi2_o10[64]; struct real64x3_t tNewPos; };
    struct { char igi2_o11[88]; double vLowestZ; };
    struct { char igi2_o12[96]; double vRadius; };
    struct { char igi2_o13[104]; double vNegDist; };
    struct { char igi2_o14[112]; struct real64x3_t tGetNextZPos; };
    struct { char igi2_o15[136]; struct real64x3_t tCenterPos; };
    struct { char igi2_o16[160]; struct QIntersection_s tIntersection; };
    char igi2_extent[280];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v2; // eax
  int v3; // eax
  int isHit; // eax
  int v5; // esi
  double vZ; // st7
  struct World_s *ptParent; // eax
  double v8; // st7
  double v9; // st6
  double v10; // st7
  int ptTail_high; // ecx
  int v12; // eax
  struct QTask_s *v13; // esi
  struct QReference_s *v14; // eax
  int v15; // esi
  struct QReference_s **p_ptMiddle; // eax
  void *v17; // eax
  char *v18; // edi
  void *v19; // eax
  char *v20; // eax
  int v21; // eax
  struct QTask_s *ptNext; // eax
  struct QTask_s *v23; // esi
  char ptTail; // cl
  struct QTask_s *v25; // eax
  struct QTask_s **p_ptPrev; // eax
  int v27; // ecx
  int v28; // eax
  char v29; // al
  unsigned int v30; // ecx
  unsigned int v31; // edx
  unsigned int v32; // eax
  int v33; // ecx
  int v34; // edx
  struct QTask_s *v35; // edx
  unsigned __int16 BaseQTaskType; // ax
  struct QTask_s *v37; // ecx
  unsigned __int16 v38; // ax
  struct QTask_s *v39; // ecx
  struct QTask_s *v40; // edx
  int v41; // eax
  double v42; // st7

  v2 = 0x40000000 >> (int)ptQTask[4].ptParent;
  igi2_frame.vNegDist = -536870912.0;
  igi2_frame.nCubeSize = 2 * v2;
  if ( World_ptActiveWorld->ptCubeTree )
  {
    if ( !LOBYTE(ptQTask[5].tQTaskRefList.ptHead) )
    {
      if ( ptQTask[6].ptNext )
      {
        QTask_Delete(ptQTask[6].ptNext);
        ptQTask[6].ptNext = nullptr;
      }
      igi2_frame.ptMaterialBitmap = ptQTask[2].ptParent[9].ptNext;
      if ( *(_DWORD *)&ptQTask[5].eQTaskType == -1 )
      {
        v3 = TextureModifier_nTextureModifier;
        TextureModifier_aptTextureModifier[TextureModifier_nTextureModifier] = (struct TextureModifier_t *)ptQTask;
        *(_DWORD *)&ptQTask[5].eQTaskType = v3;
        TextureModifier_nTextureModifier = v3 + 1;
        if ( v3 + 1 >= 256 )
        {
          LDebug_Error("Too many texturemodfiers");
          goto LABEL_8;
        }
      }
    }
    TextureModifier_atRenderItem[*(_DWORD *)&ptQTask[5].eQTaskType].ptBitmap = nullptr;
    qmemcpy(&igi2_frame.tNewPos, &ptQTask[3], sizeof(igi2_frame.tNewPos));
    if ( LOBYTE(ptQTask[5].tQTaskRefList.ptHead) || !BYTE1(ptQTask[5].tQTaskRefList.ptHead) )
      goto LABEL_17;
    qmemcpy(&igi2_frame.tGetNextZPos, &ptQTask[3], sizeof(igi2_frame.tGetNextZPos));
    igi2_frame.tGetNextZPos.vZ = igi2_frame.tGetNextZPos.vZ + 268435456.0;
    isHit = 0;
    igi2_frame.tIntersection.isHit = 0;
    v5 = 0;
    while ( v5 < 5 )
    {
      World_GetNextZNoMaterial(
        (struct World_s *)ptQTask[2].ptParent,
        &igi2_frame.tIntersection,
        &igi2_frame.tGetNextZPos,
        1,
        &igi2_frame.vNegDist,
        512,
        nullptr,
        0x80000000);
      isHit = igi2_frame.tIntersection.isHit;
      ++v5;
      if ( igi2_frame.tIntersection.isHit )
      {
        vZ = igi2_frame.tIntersection.tPos.vZ;
        goto LABEL_18;
      }
    }
    if ( isHit )
      vZ = igi2_frame.tIntersection.tPos.vZ;
    else
LABEL_17:
      vZ = igi2_frame.tNewPos.vZ;
LABEL_18:
    ptParent = (struct World_s *)ptQTask[2].ptParent;
    igi2_frame.tNewPos.vX = (double)ptParent->tOrigo.nX + igi2_frame.tNewPos.vX;
    igi2_frame.tNewPos.vY = (double)ptParent->tOrigo.nY + igi2_frame.tNewPos.vY;
    igi2_frame.tNewPos.vZ = (double)ptParent->tOrigo.nZ + vZ;
    v8 = (double)(int)(-igi2_frame.nCubeSize & (__int64)igi2_frame.tNewPos.vX);
    *(double *)&ptQTask[3].tQTaskRefList.ptMiddle = v8;
    v9 = (double)(int)(-igi2_frame.nCubeSize & (__int64)igi2_frame.tNewPos.vY);
    *(double *)&ptQTask[3].ptParent = v9;
    igi2_frame.vLowestZ = (double)(int)(-igi2_frame.nCubeSize & (__int64)igi2_frame.tNewPos.vZ);
    *(double *)&ptQTask[4].ptNext = igi2_frame.vLowestZ;
    qmemcpy(&igi2_frame.tNewPos, &ptQTask[3].tQTaskRefList.ptMiddle, sizeof(igi2_frame.tNewPos));
    igi2_frame.vHighestZa = (double)igi2_frame.nCubeSize;
    *(double *)&ptQTask[4].tQTaskChildren.ptHead = igi2_frame.vHighestZa + v8;
    *(double *)&ptQTask[4].tQTaskChildren.ptTail = igi2_frame.vHighestZa + v9;
    *(double *)&ptQTask[4].tQTaskRefList.ptMiddle = igi2_frame.vHighestZa + igi2_frame.vLowestZ;
    igi2_frame.tNewPos.vY = igi2_frame.vHighestZa * 0.5 + igi2_frame.tNewPos.vY;
    v10 = igi2_frame.tNewPos.vX + igi2_frame.vHighestZa * 0.5;
    igi2_frame.tNewPos.vZ = igi2_frame.vHighestZa * 0.5 + igi2_frame.tNewPos.vZ;
    igi2_frame.vHighestZb = (double)ptParent->tOrigo.nX;
    igi2_frame.tNewPos.vX = v10 - igi2_frame.vHighestZb;
    igi2_frame.tNewPos.vY = igi2_frame.tNewPos.vY - (double)ptParent->tOrigo.nY;
    igi2_frame.tNewPos.vZ = igi2_frame.tNewPos.vZ - (double)ptParent->tOrigo.nZ;
    *(double *)&ptQTask[3].tQTaskRefList.ptMiddle = *(double *)&ptQTask[3].tQTaskRefList.ptMiddle - igi2_frame.vHighestZb;
    *(double *)&ptQTask[3].ptParent = *(double *)&ptQTask[3].ptParent - (double)ptParent->tOrigo.nY;
    *(double *)&ptQTask[4].ptNext = *(double *)&ptQTask[4].ptNext - (double)ptParent->tOrigo.nZ;
    ptTail_high = HIBYTE(ptQTask[5].tQTaskChildren.ptTail);
    *(double *)&ptQTask[4].tQTaskChildren.ptHead = *(double *)&ptQTask[4].tQTaskChildren.ptHead
                                                 - (double)ptParent->tOrigo.nX;
    *(double *)&ptQTask[4].tQTaskChildren.ptTail = *(double *)&ptQTask[4].tQTaskChildren.ptTail
                                                 - (double)ptParent->tOrigo.nY;
    *(double *)&ptQTask[4].tQTaskRefList.ptMiddle = *(double *)&ptQTask[4].tQTaskRefList.ptMiddle
                                                  - (double)ptParent->tOrigo.nZ;
    if ( (_BYTE)ptTail_high )
      World_RegisterDynCubeObjFirstTimeMinMaxXYZ(
        ptParent,
        (struct DynCubeObj_s *)ptQTask,
        &igi2_frame.tNewPos,
        (struct real64x3_t *)&ptQTask[3].tQTaskRefList.ptMiddle,
        (struct real64x3_t *)&ptQTask[4].tQTaskChildren,
        WORLD_DYNCUBETREE_CATEGORY_TERRAINMODIFIERS);
    World_MoveDynCubeObjMinMaxXYZ(
      (struct World_s *)ptQTask[2].ptParent,
      (struct DynCubeObj_s *)ptQTask,
      &igi2_frame.tNewPos,
      (struct real64x3_t *)&ptQTask[3].tQTaskRefList.ptMiddle,
      (struct real64x3_t *)&ptQTask[4].tQTaskChildren);
    if ( !LOBYTE(ptQTask[5].tQTaskRefList.ptHead) )
    {
      v12 = *(_DWORD *)&ptQTask[4].eQTaskType;
      if ( v12 < 256 )
      {
        if ( v12 < -1 )
          *(_DWORD *)&ptQTask[4].eQTaskType = -1;
      }
      else
      {
        *(_DWORD *)&ptQTask[4].eQTaskType = 255;
      }
      v13 = *(struct QTask_s **)&ptQTask[4].eQTaskType;
      if ( v13 != (struct QTask_s *)-1 )
      {
        v14 = (struct QReference_s *)TextureModifier_SnapSize((int)ptQTask[5].tQTaskRefList.ptMiddle);
        ptQTask[5].tQTaskRefList.ptMiddle = v14;
        igi2_frame.nCubeSizea = (int)v14;
        if ( *((_DWORD *)&igi2_frame.ptMaterialBitmap->ptNext + 3 * (_DWORD)v13) )
        {
          if ( HIBYTE(ptQTask[5].tQTaskChildren.ptTail) )
            BYTE2(ptQTask[5].tQTaskChildren.ptTail) = 1;
          if ( v13 == ptQTask[5].ptNext )
          {
            v18 = (char *)igi2_frame.ptMaterialBitmap + 12 * (_DWORD)v13;
            if ( *((struct QReference_s **)v18 + 2) != v14 )
            {
              if ( World_aisMaterialBitmapResource[(_DWORD)v13] )
              {
                BYTE2(ptQTask[5].tQTaskChildren.ptTail) = 0;
              }
              else
              {
                Mem_DeAllocFn(*(void **)v18);
                *(_DWORD *)v18 = 0;
              }
              *((_DWORD *)v18 + 2) = igi2_frame.nCubeSizea;
              v19 = Mem_AllocFn(igi2_frame.nCubeSizea * igi2_frame.nCubeSizea / 8, 4);
              *((_DWORD *)&igi2_frame.ptMaterialBitmap->ptNext + 3 * (_DWORD)v13) = v19;
              memset(v19, 0, igi2_frame.nCubeSizea * igi2_frame.nCubeSizea / 8);
              World_aisMaterialBitmapResource[(_DWORD)v13] = 0;
            }
          }
          else
          {
            v20 = (char *)igi2_frame.ptMaterialBitmap + 12 * (_DWORD)v13;
            ptQTask[5].tQTaskRefList.ptMiddle = *((struct QReference_s **)v20 + 2);
            LOBYTE(ptQTask[5].tQTaskChildren.ptTail) = v20[4];
          }
        }
        else
        {
          v15 = 0;
          p_ptMiddle = &igi2_frame.ptMaterialBitmap->tQTaskRefList.ptMiddle;
          while ( *(p_ptMiddle - 6) )
          {
            if ( !*(p_ptMiddle - 3) )
            {
              ++v15;
              break;
            }
            if ( !*p_ptMiddle )
            {
              v15 += 2;
              break;
            }
            if ( !p_ptMiddle[3] )
            {
              v15 += 3;
              break;
            }
            if ( !p_ptMiddle[6] )
            {
              v15 += 4;
              break;
            }
            if ( !p_ptMiddle[9] )
            {
              v15 += 5;
              break;
            }
            if ( !p_ptMiddle[12] )
            {
              v15 += 6;
              break;
            }
            if ( !p_ptMiddle[15] )
            {
              v15 += 7;
              break;
            }
            v15 += 8;
            p_ptMiddle += 24;
            if ( v15 >= 256 )
              break;
          }
          if ( v15 == 256 )
            v15 = 255;
          *((_DWORD *)&igi2_frame.ptMaterialBitmap->tQTaskChildren.ptHead + 3 * v15) = igi2_frame.nCubeSizea;
          v17 = Mem_AllocFn(igi2_frame.nCubeSizea * igi2_frame.nCubeSizea / 8, 4);
          *((_DWORD *)&igi2_frame.ptMaterialBitmap->ptNext + 3 * v15) = v17;
          memset(v17, 0, igi2_frame.nCubeSizea * igi2_frame.nCubeSizea / 8);
          World_aisMaterialBitmapResource[v15] = 0;
          *(_DWORD *)&ptQTask[4].eQTaskType = v15;
        }
        switch ( igi2_frame.nCubeSizea )
        {
          case 256:
            v21 = 7;
            break;
          case 128:
            v21 = 6;
            break;
          case 64:
            v21 = 5;
            break;
          case 32:
            v21 = 4;
            break;
          case 16:
            v21 = 3;
            break;
          case 8:
            v21 = 2;
            break;
          default:
            LDebug_Error("Illegal shift size");
LABEL_8:
            abort();
        }
        ptQTask[5].tQTaskChildren.ptHead = (struct QTask_s *)(30 - (unsigned int)ptQTask[4].ptParent - v21);
        ptQTask[5].tQTaskChildren.ptMiddle = (struct QTask_s *)(v21 - 2);
      }
      if ( *(_DWORD *)&ptQTask[4].eQTaskType != -1 || (ptNext = ptQTask[5].ptNext, ptNext == (struct QTask_s *)-1) )
      {
        v23 = igi2_frame.ptMaterialBitmap;
      }
      else
      {
        v23 = igi2_frame.ptMaterialBitmap;
        if ( !World_aisMaterialBitmapResource[(_DWORD)ptNext] )
        {
          Mem_DeAllocFn(*((void **)&igi2_frame.ptMaterialBitmap->ptNext + 3 * (_DWORD)ptNext));
          *((_DWORD *)&igi2_frame.ptMaterialBitmap->ptNext + 3 * (int)ptQTask[5].ptNext) = 0;
        }
        *((_DWORD *)&igi2_frame.ptMaterialBitmap->ptNext + 3 * (int)ptQTask[5].ptNext) = 0;
      }
      ptTail = (char)ptQTask[5].tQTaskChildren.ptTail;
      v25 = *(struct QTask_s **)&ptQTask[4].eQTaskType;
      ptQTask[5].ptNext = v25;
      if ( ptTail )
      {
        p_ptPrev = &v23->ptPrev;
        v27 = 256;
        do
        {
          *(_BYTE *)p_ptPrev = 0;
          p_ptPrev += 3;
          --v27;
        }
        while ( v27 );
        v28 = *(_DWORD *)&ptQTask[4].eQTaskType;
        if ( v28 >= 0 )
          *((_BYTE *)&v23->ptPrev + 12 * v28) = 1;
      }
      else if ( (int)v25 >= 0 )
      {
        *((_BYTE *)&v23->ptPrev + 12 * (_DWORD)v25) = 0;
      }
      v29 = BYTE1(ptQTask[5].tQTaskRefList.ptHead);
      HIBYTE(ptQTask[5].tQTaskChildren.ptTail) = 0;
      if ( v29 )
      {
        qmemcpy(&igi2_frame.tCenterPos, &ptQTask[1], sizeof(igi2_frame.tCenterPos));
        igi2_frame.vLowestZ = igi2_frame.tCenterPos.vZ;
        igi2_frame.vHighestZ = igi2_frame.tCenterPos.vZ;
        igi2_frame.nCubeSizeb = 50;
        igi2_frame.vRadius = (double)(0x40000000 >> (int)ptQTask[4].ptParent);
        do
        {
          qmemcpy(&igi2_frame.tGetNextZPos, &igi2_frame.tCenterPos, sizeof(igi2_frame.tGetNextZPos));
          v30 = (TextureModifier_tRandomState.anRandom[0] >> 7) ^ TextureModifier_tRandomState.anRandom[2];
          v31 = v30 ^ TextureModifier_tRandomState.anRandom[1];
          v32 = (v30 ^ TextureModifier_tRandomState.anRandom[1]) + TextureModifier_tRandomState.anRandom[0];
          v33 = (v32 >> 7) ^ v30;
          v34 = v33 ^ v31;
          TextureModifier_tRandomState.anRandom[0] = v34 + v32;
          TextureModifier_tRandomState.anRandom[2] = v33;
          TextureModifier_tRandomState.anRandom[1] = v34;
          igi2_frame.tGetNextZPos.vX = ((double)(unsigned __int16)v32 * 0.0000152587890625
                           + (double)(unsigned __int16)v32 * 0.0000152587890625
                           - 1.0)
                          * igi2_frame.vRadius
                          + igi2_frame.tCenterPos.vX;
          igi2_frame.v43 = ptQTask[2].ptParent;
          igi2_frame.tGetNextZPos.vY = ((double)(unsigned __int16)(v34 + v32) * 0.0000152587890625
                           + (double)(unsigned __int16)(v34 + v32) * 0.0000152587890625
                           - 1.0)
                          * igi2_frame.vRadius
                          + igi2_frame.tGetNextZPos.vY;
          igi2_frame.tGetNextZPos.vZ = igi2_frame.tGetNextZPos.vZ + 268435456.0;
          World_GetNextZNoMaterial(
            (struct World_s *)igi2_frame.v43,
            &igi2_frame.tIntersection,
            &igi2_frame.tGetNextZPos,
            1,
            &igi2_frame.vNegDist,
            512,
            nullptr,
            0x80000000);
          while ( igi2_frame.tIntersection.isHit )
          {
            if ( igi2_frame.tIntersection.tPos.vZ < igi2_frame.vLowestZ )
              igi2_frame.vLowestZ = igi2_frame.tIntersection.tPos.vZ;
            if ( igi2_frame.tIntersection.tPos.vZ > igi2_frame.vHighestZ )
              igi2_frame.vHighestZ = igi2_frame.tIntersection.tPos.vZ;
            v35 = ptQTask[2].ptParent;
            qmemcpy(&igi2_frame.tGetNextZPos, &igi2_frame.tIntersection.tPos, sizeof(igi2_frame.tGetNextZPos));
            igi2_frame.tGetNextZPos.vZ = igi2_frame.tIntersection.tPos.vZ - 4096.0;
            World_GetNextZNoMaterial(
              (struct World_s *)v35,
              &igi2_frame.tIntersection,
              &igi2_frame.tGetNextZPos,
              1,
              &igi2_frame.vNegDist,
              512,
              nullptr,
              0x80000000);
          }
          --igi2_frame.nCubeSizeb;
        }
        while ( igi2_frame.nCubeSizeb );
        qmemcpy(&igi2_frame.tNewPos, &igi2_frame.tCenterPos, sizeof(igi2_frame.tNewPos));
        igi2_frame.tNewPos.vZ = igi2_frame.tCenterPos.vZ - igi2_frame.vRadius;
        for ( igi2_frame.ptMaterialBitmapa = 0; igi2_frame.vLowestZ < igi2_frame.tNewPos.vZ; igi2_frame.tNewPos.vZ = igi2_frame.tNewPos.vZ - igi2_frame.vRadius )
        {
          if ( !igi2_frame.ptMaterialBitmapa )
          {
            BaseQTaskType = QTask_GetBaseQTaskType();
            ptQTask[6].ptNext = QTask_NewFn(ptQTask, BaseQTaskType, nullptr);
            igi2_frame.ptMaterialBitmapa = 1;
          }
          v37 = ptQTask[6].ptNext;
          igi2_frame.tNewPos.vZ = igi2_frame.tNewPos.vZ - igi2_frame.vRadius;
          TextureModifier_NewCopy(v37, (struct TextureModifier_t *)ptQTask, &igi2_frame.tNewPos);
        }
        qmemcpy(&igi2_frame.tNewPos, &igi2_frame.tCenterPos, sizeof(igi2_frame.tNewPos));
        for ( igi2_frame.tNewPos.vZ = igi2_frame.vRadius + igi2_frame.tCenterPos.vZ; igi2_frame.vHighestZ > igi2_frame.tNewPos.vZ; igi2_frame.tNewPos.vZ = igi2_frame.tNewPos.vZ + igi2_frame.vRadius )
        {
          if ( !igi2_frame.ptMaterialBitmapa )
          {
            v38 = QTask_GetBaseQTaskType();
            ptQTask[6].ptNext = QTask_NewFn(ptQTask, v38, nullptr);
            igi2_frame.ptMaterialBitmapa = 1;
          }
          v39 = ptQTask[6].ptNext;
          igi2_frame.tNewPos.vZ = igi2_frame.tNewPos.vZ + igi2_frame.vRadius;
          TextureModifier_NewCopy(v39, (struct TextureModifier_t *)ptQTask, &igi2_frame.tNewPos);
        }
      }
    }
    v40 = ptQTask[2].ptParent[9].ptNext;
    v41 = *(_DWORD *)&ptQTask[5].eQTaskType;
    TextureModifier_atRenderItem[v41].nPitchShift = (int)ptQTask[5].tQTaskChildren.ptMiddle;
    igi2_frame.nCubeSizec = *((_DWORD *)&v40->tQTaskChildren.ptHead + 3 * *(_DWORD *)&ptQTask[4].eQTaskType);
    *(float *)(v41 * 48 + 139705872) = (double)(igi2_frame.nCubeSizec - 1) / (double)igi2_frame.nCubeSizec;
    TextureModifier_atRenderItem[v41].iMaterial = (int)ptQTask[5].ptPrev;
    TextureModifier_atRenderItem[v41].nShift = (int)ptQTask[5].tQTaskChildren.ptHead;
    TextureModifier_atRenderItem[v41].ptBitmap = *((unsigned __int8 **)&v40->ptNext
                                                 + 3 * *(_DWORD *)&ptQTask[4].eQTaskType);
    *(float *)(v41 * 48 + 139705872) = 1.0
                                     / (double)(1 << TextureModifier_atRenderItem[v41].nShift)
                                     * *(float *)(v41 * 48 + 139705872);
    v42 = (double)(0x40000000 >> (int)ptQTask[4].ptParent);
    *(double *)(v41 * 48 + 139705880) = *(double *)&ptQTask[1].ptNext - v42;
    *(double *)(v41 * 48 + 139705888) = *(double *)&ptQTask[1].tQTaskChildren.ptHead - v42;
    LOBYTE(ptQTask[5].tQTaskChildren.ptTail) = *((_BYTE *)&v40->ptPrev + 12 * *(_DWORD *)&ptQTask[4].eQTaskType);
    HIBYTE(ptQTask[5].tQTaskChildren.ptTail) = 0;
  }
}

// source: h/2/texturemodifier.c:1813  [size]
void __cdecl TextureModifier_ModifyGroundMaterialHandler(struct QTask_s *ptQTask, void *pxContext)
{
  unsigned int v2; // eax
  int v3; // ecx

  if ( *(int *)&ptQTask[4].eQTaskType >= 0 )
  {
    v2 = *(_DWORD *)&ptQTask[5].eQTaskType;
    if ( TextureModifier_atRenderItem[v2].ptBitmap )
    {
      v3 = TextureModifier_nStackItem;
      TextureModifier_aiStackItem[TextureModifier_nStackItem] = v2;
      TextureModifier_nStackItem = v3 + 1;
    }
  }
}

// source: h/2/texturemodifier.c:1837  [size]
void __cdecl TextureModifier_DynCubeObjInGameEvalHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = 0;
}

// source: h/2/texturemodifier.c:1882  [anchor-hash]
void __cdecl TextureModifier_Open()
{
  unsigned __int16 v0; // si
  struct ParameterList_s *v1; // eax
  int v2; // edx

  TextureModifier_tRandomState.anRandom[0] = -773192938;
  TextureModifier_tRandomState.anRandom[1] = -965544106;
  TextureModifier_tRandomState.anRandom[2] = 1572805325;
  v0 = QTask_NewQTaskType("TextureModifier", 248, DynCubeObj_eQTaskType, 0, 0);
  TextureModifier_eQTaskType = v0;
  QTask_LinkQTaskEventHandlerFn(v0, 14, TextureModifier_ModifyGroundMaterialHandler);
  QTask_LinkQTaskEventHandlerFn(v0, 0, TextureModifier_CreateHandler);
  QTask_LinkQTaskEventHandlerFn(v0, 16, TextureModifier_LeaveHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 2, TextureModifier_DeleteHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))TextureModifier_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    ParameterList_eUpdateInternalDataQTaskEvent,
    TextureModifier_UpdateInternalDataHandler);
  QTask_LinkQTaskEventHandlerFn(v0, 11, nullptr);
  QTask_LinkQTaskEventHandlerFn(v0, 12, nullptr);
  QTask_LinkQTaskEventHandlerFn(v0, QCube_eGetClosestVertexQTaskEvent, nullptr);
  QTask_LinkQTaskEventHandlerFn(v0, 13, nullptr);
  QTask_LinkQTaskEventHandlerFn(v0, 15, (void (__cdecl *)(struct QTask_s *, void *))TextureModifier_EnterHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    DynCube_eDynCubeObjInGameEvalQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))TextureModifier_DynCubeObjInGameEvalHandler);
  QTask_LinkQTaskEventHandlerFn(v0, 9, nullptr);
  QTask_LinkQTaskEventHandlerFn(v0, 5, nullptr);
  QTask_LinkQTaskEventHandlerFn(v0, 6, nullptr);
  v1 = (struct ParameterList_s *)Mem_AllocFn(192, 4);
  v2 = Level_eParameterTypeObjectPos;
  v1->ptParameterListItem = (struct ParameterListItem_s *)&v1[1];
  v1->nParameters = 0;
  v1->nMaxParameters = 9;
  TextureModifier_ptParameterList = v1;
  ParameterList_AddParameter(v1, 0x78u, v2, "Position", 7u, nullptr);
  ParameterList_AddParameter(TextureModifier_ptParameterList, 0xC0u, Level_eParameterTypeInt32, "Level", 7u, nullptr);
  ParameterList_AddParameter(
    TextureModifier_ptParameterList,
    0xCCu,
    Level_eParameterTypeInt32,
    "Material Index",
    7u,
    nullptr);
  ParameterList_AddParameter(
    TextureModifier_ptParameterList,
    0xC4u,
    Level_eParameterTypeInt32,
    "Bitmap ID",
    7u,
    nullptr);
  ParameterList_AddParameter(TextureModifier_ptParameterList, 0xE0u, Level_eParameterTypeInt32, "Size", 7u, nullptr);
  ParameterList_AddParameter(TextureModifier_ptParameterList, 0xD8u, Level_eParameterTypebool8, "isEdit", 7u, nullptr);
  ParameterList_AddParameter(
    TextureModifier_ptParameterList,
    0xD9u,
    Level_eParameterTypePushButton,
    "Save",
    6u,
    nullptr);
  ParameterList_AddParameter(
    TextureModifier_ptParameterList,
    0xE8u,
    Level_eParameterTypePushButton,
    "FIXUPALL",
    6u,
    nullptr);
  ParameterList_AddParameter(
    TextureModifier_ptParameterList,
    0xDDu,
    Level_eParameterTypebool8,
    "MULTIPLE HEIGHT",
    6u,
    nullptr);
  TextureModifier_nStackItem = 0;
}

// source: h/2/texturemodifier.c:1941  [size]
void __cdecl TextureModifier_Close()
{
  int v0; // esi

  if ( TextureModifier_ptParameterList )
  {
    v0 = *(_DWORD *)((unsigned int)&TextureModifier_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
  QTask_DeleteQTaskType(TextureModifier_eQTaskType);
}

// source: h/2/texturemodifier.c:1959  [size]
unsigned __int16 __cdecl TextureModifier_GetQTaskType()
{
  return TextureModifier_eQTaskType;
}

// source: h/2/texturemodifier.c:1991  [anchor-callee]
struct QTask_s *__cdecl TextureModifier_NewCopy(
        struct QTask_s *ptParent,
        struct TextureModifier_t *ptCopyOf,
        struct real64x3_t *ptPos)
{
  struct QTask_s *v3; // ebx
  int eQTaskType; // edx
  void (__cdecl *pfHandler)(struct QTask_s *, _DWORD); // eax

  v3 = QTask_NewFn(ptParent, TextureModifier_eQTaskType, nullptr);
  LOBYTE(v3[5].tQTaskRefList.ptHead) = 1;
  v3[4].ptParent = (struct QTask_s *)ptCopyOf->nLevel;
  v3[5].tQTaskRefList.ptMiddle = (struct QReference_s *)ptCopyOf->nEditSize;
  v3[5].tQTaskChildren.ptHead = (struct QTask_s *)ptCopyOf->nShift;
  v3[5].tQTaskChildren.ptMiddle = (struct QTask_s *)ptCopyOf->nPitchShift;
  v3[5].ptPrev = (struct QTask_s *)ptCopyOf->iMaterial;
  *(_DWORD *)&v3[5].eQTaskType = ptCopyOf->iGlobalList;
  eQTaskType = v3->eQTaskType;
  *(_DWORD *)&v3[4].eQTaskType = ptCopyOf->nBitmapID;
  qmemcpy(&v3[4].tQTaskChildren, &ptCopyOf->tMax, 0x18u);
  qmemcpy(&v3[3].tQTaskRefList.ptMiddle, &ptCopyOf->tMin, 0x18u);
  qmemcpy(&v3[3], ptPos, 0x18u);
  pfHandler = (void (__cdecl *)(struct QTask_s *, _DWORD))QTask_aatQTaskFinalEvent[ParameterList_eUpdateInternalDataQTaskEvent][eQTaskType].pfHandler;
  if ( pfHandler )
    pfHandler(v3, 0);
  return v3;
}
