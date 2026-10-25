/* h/2/graphnode.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: h/2/graphnode.c:355  [size]
void __cdecl GraphNode_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct World_s *v2; // edx

  v2 = World_ptActiveWorld;
  ptQTask[1].tQTaskRefList.ptMiddle = *(struct QReference_s **)pxContext;
  *(_DWORD *)&ptQTask[1].eQTaskType = v2;
  LOBYTE(ptQTask[1].tQTaskRefList.ptTail) = 0;
}

// source: h/2/graphnode.c:409  [size]
void __cdecl GraphNode_UpdateNodeHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ;
}

// source: h/2/graphnode.c:448  [size]
void __cdecl GraphNode_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QReference_s *ptMiddle; // ecx
  struct QTask_s *ptParent; // eax

  ptMiddle = ptQTask[1].tQTaskRefList.ptMiddle;
  ptParent = ptQTask->ptParent;
  if ( ptParent[3].tQTaskChildren.ptMiddle
    && (int)ptMiddle < (int)ptParent[2].tQTaskRefList.ptMiddle
    && (int)ptMiddle >= 0 )
  {
    Graph_GetGraphNodeDataSize((int)ptParent);
  }
}

// source: h/2/graphnode.c:470  [size]
void __cdecl GraphNode_UpdateAttachmentHandler(struct QTask_s *ptQTask)
{
  struct QReference_s *ptMiddle; // ecx
  struct QTask_s *ptParent; // eax

  ptMiddle = ptQTask[1].tQTaskRefList.ptMiddle;
  ptParent = ptQTask->ptParent;
  if ( ptParent[3].tQTaskChildren.ptMiddle
    && (int)ptMiddle < (int)ptParent[2].tQTaskRefList.ptMiddle
    && (int)ptMiddle >= 0 )
  {
    Graph_GetGraphNodeDataSize((int)ptParent);
  }
}

// source: h/2/graphnode.c:489  [size]
void __cdecl GraphNode_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = GraphNode_ptParameterList;
}

// source: h/2/graphnode.c:505  [size]
// attributes: thunk
void __cdecl GraphNode_RunHandler(struct QTask_s *ptQTask)
{
  QTask_Delete(ptQTask);
}

// source: h/2/graphnode.c:521  [anchor-mhash]
void __cdecl GraphNode_DeleteHandler(struct QTask_s *ptQTask)
{
  struct QTilemap_s ***p_ptPrev; // ebx
  int v2; // ebp
  struct QTilemap_s **v3; // esi
  int v4; // esi

  if ( LOBYTE(ptQTask[1].tQTaskRefList.ptTail) )
  {
    p_ptPrev = (struct QTilemap_s ***)&ptQTask[2].ptPrev;
    v2 = 3;
    do
    {
      v3 = *p_ptPrev;
      if ( *p_ptPrev )
      {
        QTilemap_Delete(*v3);
        v4 = *(_DWORD *)((unsigned int)(v3 - 1) & 0xFFFFFFFC);
        --Mem_nCurrentAllocations;
        Node_Remove((_DWORD **)v4);
        memset(*(void **)(v4 + 8), 0xCDu, *(_DWORD *)(v4 + 16));
        free((void *)v4);
      }
      ++p_ptPrev;
      --v2;
    }
    while ( v2 );
  }
}

// source: h/2/graphnode.c:638  [size]
void __cdecl GraphNode_GetMaterialCollisionEvalHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_BYTE *)pxContext = 0;
}

// source: h/2/graphnode.c:1003  [size]
void GraphNode_PrintText(struct QTask_s *ptQTask, int nLine, char *zFormat, ...)
{
  ;
}

// source: h/2/graphnode.c:1040  [anchor-mhash]
struct GraphNode_s *__cdecl GraphNode_GetData(struct QTask_s *ptQTask)
{
  struct QTask_s *ptParent; // esi
  struct QReference_s *ptMiddle; // edi
  int GraphNodeDataSize; // eax

  ptParent = ptQTask->ptParent;
  ptMiddle = ptQTask[1].tQTaskRefList.ptMiddle;
  if ( !ptParent[3].tQTaskChildren.ptMiddle
    || (int)ptMiddle >= (int)ptParent[2].tQTaskRefList.ptMiddle
    || (int)ptMiddle < 0 )
  {
    return nullptr;
  }
  GraphNodeDataSize = Graph_GetGraphNodeDataSize((int)ptParent);
  return *(struct QTask_s **)((char *)&ptParent[3].tQTaskChildren.ptMiddle->ptNext + (_DWORD)ptMiddle
                                                                                   * GraphNodeDataSize) == (struct QTask_s *)-1
       ? nullptr
       : (struct GraphNode_s *)((char *)ptParent[3].tQTaskChildren.ptMiddle + (_DWORD)ptMiddle * GraphNodeDataSize);
}

// source: h/2/graphnode.c:1069  [anchor-hash]
unsigned int __cdecl GraphNode_RegisterCriteria(char *zName)
{
  int v1; // ecx
  unsigned int v2; // esi

  v1 = 0;
  while ( GraphNode_atCriterias[v1].isUsed )
  {
    if ( ++v1 >= 32 )
    {
      LDebug_Error("Unable to register NodeCriteria %s", zName);
      abort();
    }
  }
  v2 = 1 << v1;
  GraphNode_atCriterias[v1].isUsed = 1;
  *((_DWORD *)&flt_83414CC + 2 * v1) = zName;
  Symbol_Register(
    zName,
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)(1 << v1),
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  return v2;
}

// source: h/2/graphnode.c:1102  [anchor-callee]
void __cdecl GraphNode_RemoveCriteria(unsigned int bCriteriaMask)
{
  int i; // esi

  for ( i = 0; i < 32; ++i )
  {
    if ( ((1 << i) & bCriteriaMask) != 0 )
    {
      Symbol_Remove(*((char **)&flt_83414CC + 2 * i));
      GraphNode_atCriterias[i].isUsed = 0;
      *(&flt_83414CC + 2 * i) = 0.0;
    }
  }
}

// source: h/2/graphnode.c:1132  [anchor-strings]
int __cdecl GraphNode_GetCriteriaBitPosition(char a1)
{
  int result; // eax
  int v2; // ecx

  result = 0;
  v2 = a1 & 1;
  while ( !v2 )
  {
    if ( ++result >= 32 )
    {
      LDebug_Error("No criteria matching bit position found");
      abort();
    }
  }
  return result;
}

// source: h/2/graphnode.c:1156  [size]
unsigned __int16 __cdecl GraphNode_GetQTaskType()
{
  return GraphNode_eQTaskType;
}

// source: h/2/graphnode.c:1170  [anchor-hash]
void __cdecl GraphNode_Open()
{
  __int16 v0; // ax
  unsigned __int16 v1; // si
  float *v2; // eax
  struct ParameterList_s *v3; // eax
  int v4; // edx

  GraphNode_eQTaskType = QTask_NewQTaskType("GraphNode", 288, EditorRigidObj_eQTaskType, 0, 0);
  v0 = QTask_NewQTaskEventFn(0, "GraphNode_StartsEnterHandlerEvent");
  v1 = GraphNode_eQTaskType;
  GraphNode_eNodeStartsEnterHandlerEvent = v0;
  QTask_LinkQTaskEventHandlerFn(GraphNode_eQTaskType, 0, GraphNode_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 1, GraphNode_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 2, GraphNode_DeleteHandler);
  QTask_LinkQTaskEventHandlerFn(v1, ParameterList_eUpdateInternalDataQTaskEvent, GraphNode_UpdateInternalDataHandler);
  QTask_LinkQTaskEventHandlerFn(
    v1,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))GraphNode_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(
    v1,
    Graph_eUpdateNodeQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))GraphNode_UpdateNodeHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, Attach_eUpdateAttachmentEvent, GraphNode_UpdateAttachmentHandler);
  QTask_LinkQTaskEventHandlerFn(v1, Attach_eAttachEvent, nullptr);
  GraphNode_ptVirModel = MTP_GetLODVirModel("ai-box");
  v2 = &flt_83414CC;
  do
  {
    *((_BYTE *)v2 - 4) = 0;
    *v2 = 0.0;
    v2 += 2;
  }
  while ( (int)v2 < 137631180 );
  v3 = (struct ParameterList_s *)Mem_AllocFn(32, 4);
  v4 = Level_eParameterTypeInt32;
  v3->ptParameterListItem = (struct ParameterListItem_s *)&v3[1];
  v3->nParameters = 0;
  v3->nMaxParameters = 1;
  GraphNode_ptParameterList = v3;
  ParameterList_AddParameter(v3, 0x40u, v4, "Node ID", 2u, nullptr);
  QTask_SetQTaskTypeGroup(
    GraphNode_eQTaskType,
    (unsigned int)&MTP_atLODVirModel[296].atBoneVertexRefs[36].atVertexRefs[609]);
}

// source: h/2/graphnode.c:1236  [anchor-hash]
void __cdecl GraphNode_Close()
{
  int v0; // esi

  if ( GraphNode_ptParameterList )
  {
    v0 = *(_DWORD *)((unsigned int)&GraphNode_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
  GraphNode_ptParameterList = nullptr;
  QTask_DeleteQTaskEvent(GraphNode_eNodeStartsEnterHandlerEvent);
  QTask_DeleteQTaskType(GraphNode_eQTaskType);
}

// source: h/2/graphnode.c:1283  [anchor-mhash]
struct QMaterial_t *__cdecl GraphNode_GetMaterialUnderNode(struct GraphNode_s *ptGraphNode)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct CollisionEvaluateContext_s tCollisionEvaluateContext; };
    struct { char igi2_o1[8]; struct real64x3_t tNodeStartPos; };
    struct { char igi2_o2[32]; struct real64x3_t tNodeEndPos; };
    struct { char igi2_o3[56]; struct QIntersection_s tIntersection; };
    char igi2_extent[176];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  void (__cdecl *pfHandler)(struct QTask_s *, void *); // esi

  igi2_frame.tCollisionEvaluateContext.isEvaluate = 1;
  igi2_frame.tCollisionEvaluateContext.ptQTask = nullptr;
  Graph_GetNodePos(&igi2_frame.tNodeStartPos, ptGraphNode);
  qmemcpy(&igi2_frame.tNodeEndPos, &igi2_frame.tNodeStartPos, sizeof(igi2_frame.tNodeEndPos));
  igi2_frame.tNodeStartPos.vZ = igi2_frame.tNodeStartPos.vZ + 4096.0;
  igi2_frame.tNodeEndPos.vZ = igi2_frame.tNodeEndPos.vZ - 12288.0;
  pfHandler = (void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[13][GraphNode_eQTaskType].pfHandler;
  QTask_LinkQTaskEventHandlerFn(
    GraphNode_eQTaskType,
    13,
    (void (__cdecl *)(struct QTask_s *, void *))GraphNode_GetMaterialCollisionEvalHandler);
  World_TraceLines(
    World_ptActiveWorld,
    &igi2_frame.tIntersection,
    &igi2_frame.tNodeStartPos,
    &igi2_frame.tNodeEndPos,
    1,
    13,
    &igi2_frame.tCollisionEvaluateContext,
    0xFFFFFFFF);
  QTask_LinkQTaskEventHandlerFn(GraphNode_eQTaskType, 13, pfHandler);
  return igi2_frame.tIntersection.isHit != 0 ? igi2_frame.tIntersection.ptEnterMaterial : nullptr;
}

// source: h/2/graphnode.c:1340  [anchor-mhash]
void __cdecl GraphNode_UpdateNodeGroundInfo(struct GraphNode_s *ptGraphNode)
{
  #pragma pack(push, 1)
  union
  {
    struct { double vDistance; };
    struct { char igi2_o1[8]; struct CollisionEvaluateContext_s tCollisionEvaluateContext; };
    struct { char igi2_o2[16]; struct real64x3_t tNodeStartPos; };
    struct { char igi2_o3[40]; struct QIntersection_s tIntersection; };
    char igi2_extent[160];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  float vLight; // ecx
  struct QObj_s *ptHitObj; // eax
  bool v3; // zf

  igi2_frame.tCollisionEvaluateContext.isEvaluate = 1;
  igi2_frame.tCollisionEvaluateContext.ptQTask = nullptr;
  Graph_GetNodePos(&igi2_frame.tNodeStartPos, ptGraphNode);
  igi2_frame.tNodeStartPos.vZ = igi2_frame.tNodeStartPos.vZ + 4096.0;
  igi2_frame.vDistance = -12288.0;
  QTask_LinkQTaskEventHandlerFn(
    GraphNode_eQTaskType,
    13,
    (void (__cdecl *)(struct QTask_s *, void *))GraphNode_GetMaterialCollisionEvalHandler);
  igi2_frame.tIntersection.vLight = 0.0;
  World_GetNextZ(
    World_ptActiveWorld,
    &igi2_frame.tIntersection,
    &igi2_frame.tNodeStartPos,
    1,
    &igi2_frame.vDistance,
    13,
    &igi2_frame.tCollisionEvaluateContext,
    0x98000000);
  if ( igi2_frame.tIntersection.isHit )
  {
    vLight = igi2_frame.tIntersection.vLight;
    ptGraphNode->ptGroundMaterial = igi2_frame.tIntersection.ptEnterMaterial;
    ptHitObj = igi2_frame.tIntersection.ptHitObj;
    v3 = igi2_frame.tIntersection.ptHitObj == nullptr;
    ptGraphNode->vLightValue = vLight;
    if ( v3 )
      ptGraphNode->isTerrainNode = 0;
    else
      ptGraphNode->isTerrainNode = QTask_IsQTaskTypeDerived(ptHitObj->tQTask.eQTaskType, Terrain_eQTaskType);
  }
  else
  {
    ptGraphNode->ptGroundMaterial = nullptr;
    ptGraphNode->vLightValue = 0.0;
    ptGraphNode->isTerrainNode = 1;
  }
}

// source: h/2/graphnode.c:1405  [size]
__int16 __cdecl GraphNode_GetNodeStartsEnterHandlerEvent()
{
  return GraphNode_eNodeStartsEnterHandlerEvent;
}
