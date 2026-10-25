/* e/3/pc/pc_sprite3d.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: e/3/pc/pc_sprite3d.c:42  [anchor-mhash]
void __cdecl Sprite3D_EnterHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { float vX3; };
    struct { char igi2_o1[4]; float vY1; };
    struct { char igi2_o2[8]; struct QTask_s *tSize3D; };
    struct { char igi2_o3[8]; float tSize3Da; };
    struct { char igi2_o4[12]; float tSize3D_4; };
    struct { char igi2_o5[16]; struct real32x2_t tScreenPos; };
    struct { char igi2_o6[24]; struct real32x2_t tSize2D; };
    char igi2_extent[32];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *v2; // esi
  double v3; // st7
  double v4; // st6
  double v5; // st5
  int LogZ; // eax

  v2 = ptQTask;
  igi2_frame.tSize3D = ptQTask[2].ptParent;
  igi2_frame.tSize3D_4 = *(float *)&ptQTask[2].eQTaskType;
  TransContext_ProjectWorldPos2(
    &TransContext_tActiveTransContext,
    &igi2_frame.tScreenPos,
    (float *)&ptQTask,
    (struct real64x3_t *)&ptQTask[1]);
  if ( *(float *)&ptQTask > 0.0 )
  {
    v3 = 1.0 / *(float *)&ptQTask;
    v4 = TransContext_tActiveTransContext.vScreenFOVX * *(float *)&igi2_frame.tSize3D * v3;
    v5 = TransContext_tActiveTransContext.vScreenFOVY * igi2_frame.tSize3D_4 * v3;
    igi2_frame.tSize2D.vY = v5;
    igi2_frame.vX3 = v5 + igi2_frame.tScreenPos.vY;
    igi2_frame.vY1 = igi2_frame.tScreenPos.vX + v4;
    igi2_frame.tSize3Da = igi2_frame.tScreenPos.vX - v4;
    igi2_frame.tScreenPos.vX = igi2_frame.tScreenPos.vY - igi2_frame.tSize2D.vY;
    LogZ = Viewport_GetLogZ(*(float *)&ptQTask);
    QSprite_Register4(
      (struct QSprite_s *)v2[3].tQTaskChildren.ptTail,
      igi2_frame.tSize3Da,
      igi2_frame.tScreenPos.vX,
      igi2_frame.vY1,
      igi2_frame.tScreenPos.vX,
      igi2_frame.tSize3Da,
      igi2_frame.vX3,
      igi2_frame.vY1,
      igi2_frame.vX3,
      255.0,
      255.0,
      255.0,
      (int)v2[3].tQTaskChildren.ptMiddle,
      (unsigned int)v2[3].tQTaskRefList.ptHead,
      LogZ);
  }
}

// source: e/3/pc/pc_sprite3d.c:104  [anchor-mhash]
struct Sprite3D_t *__cdecl Sprite3D_New(
        struct World_s *ptWorld,
        struct real64x3_t *ptPos,
        float vWidth,
        float vHeight,
        struct real32x3_t *ptColor,
        struct QSprite_s *ptSprite,
        unsigned int bQGraphicFlags)
{
  struct Sprite3D_t *ptHead; // ebx

  if ( Sprite3D_tUDPool.nAllocatedBlocks == Sprite3D_tUDPool.nBlocks )
    MemPool_ReAlloc(&Sprite3D_tUDPool, Sprite3D_tUDPool.nReAllocBlocks);
  ptHead = (struct Sprite3D_t *)Sprite3D_tUDPool.tMemPoolFreeList.ptHead;
  ++Sprite3D_tUDPool.nAllocatedBlocks;
  Sprite3D_tUDPool.tMemPoolFreeList.ptHead = Sprite3D_tUDPool.tMemPoolFreeList.ptHead->ptNext;
  ptHead->vHeight = vHeight;
  ptHead->vWidth = vWidth;
  ptHead->tColor.vX = ptColor->vX;
  ptHead->tColor.vY = ptColor->vY;
  ptHead->tColor.vZ = ptColor->vZ;
  ptHead->ptSprite = ptSprite;
  ptHead->bQGraphicFlags = bQGraphicFlags;
  ptHead->nAnimFrame = 0;
  qmemcpy(&ptHead->tDynCubeObj.tQObj.tPos, ptPos, sizeof(ptHead->tDynCubeObj.tQObj.tPos));
  if ( vWidth <= (double)vHeight )
    vWidth = vHeight;
  World_RegisterDynCubeObjFirstTimeRadius(
    ptWorld,
    &ptHead->tDynCubeObj,
    ptPos,
    vWidth,
    WORLD_DYNCUBETREE_CATEGORY_MOBILE);
  return ptHead;
}

// source: e/3/pc/pc_sprite3d.c:148  [anchor-mhash]
struct World_s *__cdecl Sprite3D_Delete(struct World_s *ptWorld, struct Sprite3D_t *ptSprite3D)
{
  struct World_s *result; // eax

  World_RemoveDynCubeObj(ptWorld, &ptSprite3D->tDynCubeObj);
  --Sprite3D_tUDPool.nAllocatedBlocks;
  result = (struct World_s *)Sprite3D_tUDPool.tMemPoolFreeList.ptHead;
  ptSprite3D->tDynCubeObj.tQObj.tQTask.ptNext = (struct QTask_s *)Sprite3D_tUDPool.tMemPoolFreeList.ptHead;
  Sprite3D_tUDPool.tMemPoolFreeList.ptHead = (struct MemPoolFreeItem_s *)ptSprite3D;
  return result;
}

// source: e/3/pc/pc_sprite3d.c:167  [anchor-hash]
void __cdecl Sprite3D_Open()
{
  struct MemPoolSegment_s *v0; // esi
  int v1; // eax
  struct MemPoolFreeItem_s *ptHead; // edx
  unsigned int i; // ecx
  struct MemPoolFreeItem_s *v4; // eax

  Sprite3D_eQTaskType = QTask_NewQTaskType("Sprite3D", 144, DynCubeObj_eQTaskType, 0, 0);
  QTask_LinkQTaskEventHandlerFn(Sprite3D_eQTaskType, 5, Sprite3D_EnterHandler);
  Sprite3D_tUDPool.nBlocks = 0;
  Sprite3D_tUDPool.nAllocatedBlocks = 0;
  Sprite3D_tUDPool.nAlignment = 4;
  Sprite3D_tUDPool.nBlockSize = 144;
  Sprite3D_tUDPool.nReAllocBlocks = 0;
  Sprite3D_tUDPool.tMemPoolFreeList.ptHead = nullptr;
  Sprite3D_tUDPool.tMemPoolSegmentList.ptHead = nullptr;
  v0 = (struct MemPoolSegment_s *)Mem_AllocFn(12, 4);
  v1 = 100 * Sprite3D_tUDPool.nBlockSize;
  v0->nByteSize = 100 * Sprite3D_tUDPool.nBlockSize;
  v0->pxData = Mem_AllocFn(v1, Sprite3D_tUDPool.nAlignment);
  v0->ptNext = Sprite3D_tUDPool.tMemPoolSegmentList.ptHead;
  ptHead = Sprite3D_tUDPool.tMemPoolFreeList.ptHead;
  Sprite3D_tUDPool.tMemPoolSegmentList.ptHead = v0;
  Sprite3D_tUDPool.nBlocks += 100;
  for ( i = 0; i < 0x64; ++i )
  {
    v4 = (struct MemPoolFreeItem_s *)((char *)v0->pxData + i * Sprite3D_tUDPool.nBlockSize);
    v4->ptNext = ptHead;
    ptHead = v4;
    Sprite3D_tUDPool.tMemPoolFreeList.ptHead = v4;
  }
}

// source: e/3/pc/pc_sprite3d.c:188  [anchor-hash]
void __cdecl Sprite3D_Close()
{
  MemPool_DeInit(&Sprite3D_tUDPool);
  QTask_DeleteQTaskType(Sprite3D_eQTaskType);
}
