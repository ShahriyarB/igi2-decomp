/* i/0/aigraph.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: i/0/aigraph.c:746  [size]
void __cdecl AIGraph_InitDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ;
}

// source: i/0/aigraph.c:904  [anchor-caller]
void __cdecl AIGraph_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  char ptNext; // bl
  int v3; // eax
  struct QReference_s *v4; // ecx
  int UniqueQTaskID; // eax

  ptNext = (char)ptQTask[3].ptNext;
  v3 = 0;
  while ( 1 )
  {
    v4 = Level_atLevelQTaskID[v3];
    if ( v4 )
    {
      if ( v4->pxObject == ptQTask )
        break;
    }
    if ( ++v3 >= 4096 )
      goto LABEL_7;
  }
  if ( v3 != -1 )
    goto LABEL_8;
LABEL_7:
  UniqueQTaskID = Level_GetUniqueQTaskID();
  Level_DefineQTaskID(UniqueQTaskID, ptQTask);
LABEL_8:
  if ( *(double *)&ptQTask[3].ptParent > 100.0 )
    *(double *)&ptQTask[3].ptParent = *(double *)&ptQTask[3].ptParent * 0.000244140625;
  if ( *(double *)&ptQTask[4].ptNext > 100.0 )
    *(double *)&ptQTask[4].ptNext = *(double *)&ptQTask[4].ptNext * 0.000244140625;
  Graph_UpdateInternalDataHandler(ptQTask, pxContext);
  if ( ptNext && BYTE1(ptQTask[5].tQTaskChildren.ptTail) )
  {
    AIGraph_UpdateNodeCover((struct AIGraph_t *)ptQTask);
    AIGraph_SaveNodeCoverData((struct AIGraph_t *)ptQTask);
  }
  if ( HIBYTE(ptQTask[5].tQTaskChildren.ptTail) )
    AIGraph_DropNodesToGround((struct AIGraph_t *)ptQTask);
}

// source: i/0/aigraph.c:963  [anchor-mhash]
void __cdecl AIGraph_UpdateInternalDataAfterLoadHandler(struct QTask_s *ptQTask)
{
  ((void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[Level_eUpdateInternalDataAfterLoadEvent][Graph_eQTaskType].pfHandler)(ptQTask);
  AIGraph_LoadNodeCoverData((struct AIGraph_t *)ptQTask);
}

// source: i/0/aigraph.c:1043  [size]
void __cdecl AIGraph_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = AIGraph_ptParameterList;
}

// source: i/0/aigraph.c:1061  [size]
void __cdecl AIGraph_CreateNodeHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ;
}

// source: i/0/aigraph.c:1114  [anchor-mhash]
void __cdecl AIGraph_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  Graph_CreateHandler(ptQTask, pxContext);
  *(_DWORD *)&ptQTask[3].eQTaskType = 1072693248;
  ptQTask[4].tQTaskRefList.ptTail = (struct QReference_s *)1072693248;
  ptQTask[5].tQTaskChildren.ptHead = (struct QTask_s *)-1;
  ptQTask[5].tQTaskChildren.ptMiddle = (struct QTask_s *)-1;
  ptQTask[3].ptParent = nullptr;
  ptQTask[4].ptNext = nullptr;
  ptQTask[4].ptPrev = (struct QTask_s *)0x40000000;
  ptQTask[4].tQTaskChildren.ptHead = nullptr;
  ptQTask[4].tQTaskChildren.ptMiddle = (struct QTask_s *)1074266112;
  ptQTask[4].tQTaskChildren.ptTail = (struct QTask_s *)858993459;
  ptQTask[4].tQTaskRefList.ptHead = (struct QReference_s *)1070805811;
  ptQTask[4].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[5].ptNext = nullptr;
  ptQTask[5].ptPrev = (struct QTask_s *)1077805056;
  ptQTask[4].ptParent = (struct QTask_s *)-1717986918;
  *(_DWORD *)&ptQTask[4].eQTaskType = 1068079513;
  LOBYTE(ptQTask[5].tQTaskChildren.ptTail) = 0;
  BYTE1(ptQTask[5].tQTaskChildren.ptTail) = 0;
  BYTE2(ptQTask[5].tQTaskChildren.ptTail) = 0;
  HIBYTE(ptQTask[5].tQTaskChildren.ptTail) = 0;
  ptQTask[5].tQTaskRefList.ptTail = (struct QReference_s *)&ptQTask[5].tQTaskRefList;
  ptQTask[5].tQTaskRefList.ptHead = (struct QReference_s *)&ptQTask[5].tQTaskRefList.ptMiddle;
  ptQTask[5].tQTaskRefList.ptMiddle = nullptr;
}

// source: i/0/aigraph.c:1152  [size]
void __cdecl AIGraph_RunHandler(struct QTask_s *ptQTask)
{
  ;
}

// source: i/0/aigraph.c:1173  [anchor-mhash]
void __cdecl AIGraph_DeleteHandler(struct QTask_s *ptQTask)
{
  struct QReference_s *i; // eax
  int v2; // esi

  ((void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[2][Graph_eQTaskType].pfHandler)(ptQTask);
  for ( i = ptQTask[5].tQTaskRefList.ptHead; i->ptNext && i; i = ptQTask[5].tQTaskRefList.ptHead )
  {
    v2 = *(_DWORD *)((unsigned int)(Node_Remove(i) - 1) & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v2);
    memset(*(void **)(v2 + 8), 0xCDu, *(_DWORD *)(v2 + 16));
    free((void *)v2);
  }
}

// source: i/0/aigraph.c:1205  [anchor-strings]
void __cdecl AIGraph_Open()
{
  unsigned __int16 v0; // si
  char *p_isTaken; // eax

  v0 = QTask_NewQTaskType("AIGraph", 232, Graph_eQTaskType, 0, 0);
  AIGraph_eQTaskType = v0;
  QTask_LinkQTaskEventHandlerFn(v0, 0, AIGraph_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 1, (void (__cdecl *)(struct QTask_s *))AIGraph_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 2, AIGraph_DeleteHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    Graph_eInitDataQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))AIGraph_InitDataHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    Graph_eCreateNodeQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))AIGraph_CreateNodeHandler);
  QTask_LinkQTaskEventHandlerFn(v0, ParameterList_eUpdateInternalDataQTaskEvent, AIGraph_UpdateInternalDataHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))AIGraph_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(
    v0,
    Level_eUpdateInternalDataAfterLoadEvent,
    AIGraph_UpdateInternalDataAfterLoadHandler);
  AIGraph_tParameterReal64Context.vMax = 20.0;
  AIGraph_tParameterReal64Context.vMin = 0.3;
  AIGraph_tPreciseLinkCheckStepParameterReal64Context.vMax = 1.0;
  AIGraph_tPreciseLinkCheckStepParameterReal64Context.vMin = 0.01;
  AIGraph_ptParameterList = ParameterList_Derive(Graph_ptParameterList, 11);
  ParameterList_AddParameter(
    AIGraph_ptParameterList,
    0x98u,
    Level_eParameterTypeReal64,
    "Node cover midoffset",
    7u,
    nullptr);
  ParameterList_AddParameter(
    AIGraph_ptParameterList,
    0xA0u,
    Level_eParameterTypeReal64,
    "Node cover topoffset",
    5u,
    nullptr);
  ParameterList_AddParameter(
    AIGraph_ptParameterList,
    0xA8u,
    Level_eParameterTypeReal64,
    "Max height difference between linked nodes",
    7u,
    nullptr);
  ParameterList_AddParameter(
    AIGraph_ptParameterList,
    0xB0u,
    Level_eParameterTypeReal64,
    "Width of node links",
    7u,
    &AIGraph_tParameterReal64Context);
  ParameterList_AddParameter(
    AIGraph_ptParameterList,
    0xB8u,
    Level_eParameterTypeReal64,
    "Link maximum distance to ground",
    7u,
    nullptr);
  ParameterList_AddParameter(AIGraph_ptParameterList, 0xC8u, Level_eParameterTypeReal64, "Max Link-length", 7u, nullptr);
  ParameterList_AddParameter(
    AIGraph_ptParameterList,
    0xD8u,
    Level_eParameterTypebool8,
    "Use precise link method (SLOW!)",
    7u,
    nullptr);
  ParameterList_AddParameter(
    AIGraph_ptParameterList,
    0xC0u,
    Level_eParameterTypeReal64,
    "Precise link method step value",
    7u,
    &AIGraph_tPreciseLinkCheckStepParameterReal64Context);
  ParameterList_AddParameter(
    AIGraph_ptParameterList,
    0xD9u,
    Level_eParameterTypebool8,
    "Update & Display CoverInfo",
    7u,
    nullptr);
  ParameterList_AddParameter(
    AIGraph_ptParameterList,
    0xDAu,
    Level_eParameterTypePushButton,
    "Floodfill from active node",
    6u,
    nullptr);
  ParameterList_AddParameter(
    AIGraph_ptParameterList,
    0xDBu,
    Level_eParameterTypePushButton,
    "Drop nodes to ground",
    6u,
    nullptr);
  QTask_LinkQTaskEventHandlerFn(
    AIGraph_eQTaskType,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveNoChildrenHandler);
  Graph_SetGraphNodeDataSize(AIGraph_eQTaskType, 592);
  AIGraph_bVehicleNodeCriteria = GraphNode_RegisterCriteria("NODECRITERIA_VEHICLE");
  AIGraph_bDoorNodeCriteria = GraphNode_RegisterCriteria("NODECRITERIA_DOOR");
  AIGraph_bViewNodeCriteria = GraphNode_RegisterCriteria("NODECRITERIA_VIEW");
  AIGraph_bStairNodeCriteria = GraphNode_RegisterCriteria("NODECRITERIA_STAIR");
  p_isTaken = &AIGraphAStarSearch_atTakenAStarSearchNodeBuffer[0].isTaken;
  do
  {
    *p_isTaken = 0;
    p_isTaken += 32;
  }
  while ( (int)p_isTaken < 129798804 );
  AIGraph_ptCreatePathProfileRegion = nullptr;
}

// source: i/0/aigraph.c:1300  [anchor-hash]
void __cdecl AIGraph_Close()
{
  int v0; // esi

  GraphNode_RemoveCriteria(AIGraph_bDoorNodeCriteria | AIGraph_bViewNodeCriteria
                                                     | AIGraph_bStairNodeCriteria
                                                     | AIGraph_bVehicleNodeCriteria);
  if ( AIGraph_ptParameterList )
  {
    v0 = *(_DWORD *)((unsigned int)&AIGraph_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
  if ( AIGraph_eNodeLinkCheckQTaskEvent != 512 )
    QTask_DeleteQTaskEvent(AIGraph_eNodeLinkCheckQTaskEvent);
  QTask_DeleteQTaskType(AIGraph_eQTaskType);
}

// source: i/0/aigraph.c:1343  [anchor-refs]
__int16 __cdecl AIGraph_GetNodeLinkCheckQTaskEvent()
{
  __int16 result; // ax

  result = AIGraph_eNodeLinkCheckQTaskEvent;
  if ( AIGraph_eNodeLinkCheckQTaskEvent == 512 )
  {
    result = QTask_NewQTaskEventFn(0, "AIGraph_NodeLinkCheck");
    AIGraph_eNodeLinkCheckQTaskEvent = result;
  }
  return result;
}

// source: i/0/aigraph.c:1363  [anchor-callee]
enum AIGraphGetClosestNode_e __cdecl AIGraph_GetClosestNode(
        struct AIGraphNode_s **pptAIGraphNode,
        struct AIGraph_t *ptAIGraph,
        struct real64x3_t *ptPosition,
        enum bool isAllowVehicleNodes)
{
  #pragma pack(push, 1)
  union
  {
    struct { double vBestDistanceSquared; };
    struct { char igi2_o1[8]; struct real64x3_t tNodePos; };
    char igi2_extent[32];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int nMaxNodes; // eax
  int v5; // edi
  struct AIGraphNode_s *v6; // esi
  unsigned int bCriteria; // eax
  double v8; // st4

  *pptAIGraphNode = nullptr;
  nMaxNodes = ptAIGraph->tGraph.nMaxNodes;
  v5 = 0;
  igi2_frame.vBestDistanceSquared = 0.0;
  if ( nMaxNodes <= 0 )
    return AIGRAPH_GETCLOSESTNODE_NONODE;
  do
  {
    if ( ptAIGraph->tGraph.pxGraphNodeList )
    {
      if ( v5 < nMaxNodes && v5 >= 0 )
      {
        v6 = (struct AIGraphNode_s *)((char *)ptAIGraph->tGraph.pxGraphNodeList
                                    + v5 * Graph_GetGraphNodeDataSize((int)ptAIGraph));
        if ( v6->tGraphNode.nID != -1 )
        {
          bCriteria = v6->tGraphNode.bCriteria;
          if ( (bCriteria & AIGraph_bViewNodeCriteria) == 0
            && (isAllowVehicleNodes || (bCriteria & AIGraph_bVehicleNodeCriteria) == 0) )
          {
            Graph_GetNodePos(&igi2_frame.tNodePos, &v6->tGraphNode);
            v8 = (igi2_frame.tNodePos.vZ - ptPosition->vZ) * (igi2_frame.tNodePos.vZ - ptPosition->vZ)
               + (igi2_frame.tNodePos.vY - ptPosition->vY) * (igi2_frame.tNodePos.vY - ptPosition->vY)
               + (igi2_frame.tNodePos.vX - ptPosition->vX) * (igi2_frame.tNodePos.vX - ptPosition->vX);
            if ( !*pptAIGraphNode || v8 < igi2_frame.vBestDistanceSquared )
            {
              igi2_frame.vBestDistanceSquared = v8;
              *pptAIGraphNode = v6;
            }
          }
        }
      }
    }
    nMaxNodes = ptAIGraph->tGraph.nMaxNodes;
    ++v5;
  }
  while ( v5 < nMaxNodes );
  if ( !*pptAIGraphNode )
    return AIGRAPH_GETCLOSESTNODE_NONODE;
  if ( (*pptAIGraphNode)->tGraphNode.vRadius * 4096.0 <= igi2_frame.vBestDistanceSquared * 0.000244140625 )
    return AIGRAPH_GETCLOSESTNODE_OUTSIDENODE;
  return AIGRAPH_GETCLOSESTNODE_INSIDENODE;
}

// source: i/0/aigraph.c:1439  [size]
unsigned int __cdecl AIGraph_GetDoorNodeCriteria()
{
  return AIGraph_bDoorNodeCriteria;
}

// source: i/0/aigraph.c:1454  [size]
unsigned int __cdecl AIGraph_GetViewNodeCriteria()
{
  return AIGraph_bViewNodeCriteria;
}

// source: i/0/aigraph.c:1469  [size]
unsigned int __cdecl AIGraph_GetStairNodeCriteria()
{
  return AIGraph_bStairNodeCriteria;
}

// source: i/0/aigraph.c:1485  [size]
unsigned int __cdecl AIGraph_GetVehicleNodeCriteria()
{
  return AIGraph_bVehicleNodeCriteria;
}

// source: i/0/aigraph.c:1500  [size]
char __cdecl AIGraph_CheckNodeCriteria(
        struct AIGraphNode_s *ptNode,
        unsigned int bCriteria)
{
  return (bCriteria & ptNode->tGraphNode.bCriteria) != 0;
}

// source: i/0/aigraph.c:1521  [size]
unsigned __int16 __cdecl AIGraph_GetQTaskType()
{
  return AIGraph_eQTaskType;
}

// source: i/0/aigraph.c:1538  [anchor-hash]
struct AIGraphAStarSearchData_s *__cdecl AIGraphAStarSearch_InitSearchData(
        struct AIGraphAStarSearchData_s *ptSearchData)
{
  ptSearchData->nDestNodeId = -1;
  ptSearchData->nGraphId = -1;
  ptSearchData->nSourceNodeId = -1;
  ptSearchData->tClosedList.ptHead = (struct AIGraphAStarSearchNode_s *)&ptSearchData->tClosedList.ptMiddle;
  ptSearchData->tClosedList.ptMiddle = nullptr;
  ptSearchData->tClosedList.ptTail = (struct AIGraphAStarSearchNode_s *)&ptSearchData->tClosedList;
  ptSearchData->tCurrentPath.ptHead = (struct AIGraphAStarSearchNode_s *)&ptSearchData->tCurrentPath.ptMiddle;
  ptSearchData->tCurrentPath.ptMiddle = nullptr;
  ptSearchData->bFlags = 0;
  ptSearchData->vPathCost = 0.0;
  ptSearchData->tCurrentPath.ptTail = (struct AIGraphAStarSearchNode_s *)&ptSearchData->tCurrentPath;
  ptSearchData->tOpenList.ptHead = (struct AIGraphAStarSearchNode_s *)&ptSearchData->tOpenList.ptMiddle;
  ptSearchData->tOpenList.ptTail = (struct AIGraphAStarSearchNode_s *)ptSearchData;
  ptSearchData->tOpenList.ptMiddle = nullptr;
  return ptSearchData;
}

// source: i/0/aigraph.c:1561  [size]
struct AIGraphAStarSearchNode_s *__cdecl AIGraphAStarSearch_ReleaseSearchNode(
        struct AIGraphAStarSearchNode_s *ptNode)
{
  LOBYTE(ptNode[1].ptNext) = 0;
  return ptNode;
}

// source: i/0/aigraph.c:1591  [anchor-callee]
struct AIGraphAStarSearchNode_s *__cdecl AIGraphAStarSearch_ClaimSearchNode()
{
  int v0; // ecx
  int v1; // eax
  int v2; // ecx

  v0 = AIGraphAStarSearch_nTakenAStarSearchNodeIndex;
  v1 = 0;
  if ( AIGraphAStarSearch_atTakenAStarSearchNodeBuffer[AIGraphAStarSearch_nTakenAStarSearchNodeIndex].isTaken )
  {
    do
    {
      if ( v1 >= 10000 )
        break;
      if ( v0 >= 9999 )
        v0 = 0;
      else
        ++v0;
      ++v1;
    }
    while ( AIGraphAStarSearch_atTakenAStarSearchNodeBuffer[v0].isTaken );
    AIGraphAStarSearch_nTakenAStarSearchNodeIndex = v0;
  }
  v2 = v0;
  if ( AIGraphAStarSearch_atTakenAStarSearchNodeBuffer[v2].isTaken )
    return nullptr;
  AIGraphAStarSearch_atTakenAStarSearchNodeBuffer[v2].tNode.ptPrev = nullptr;
  AIGraphAStarSearch_atTakenAStarSearchNodeBuffer[v2].tNode.ptNext = nullptr;
  AIGraphAStarSearch_atTakenAStarSearchNodeBuffer[v2].tNode.nNodeId = -1;
  AIGraphAStarSearch_atTakenAStarSearchNodeBuffer[v2].tNode.ptParentNode = nullptr;
  AIGraphAStarSearch_atTakenAStarSearchNodeBuffer[v2].tNode.vCostToNode = 0.0;
  AIGraphAStarSearch_atTakenAStarSearchNodeBuffer[v2].tNode.vEstimatedCostToDest = 0.0;
  AIGraphAStarSearch_atTakenAStarSearchNodeBuffer[v2].tNode.vEstimatedTotalCost = 0.0;
  AIGraphAStarSearch_atTakenAStarSearchNodeBuffer[v2].isTaken = 1;
  return &AIGraphAStarSearch_atTakenAStarSearchNodeBuffer[v2].tNode;
}

// source: i/0/aigraph.c:1646  [anchor-callee]
void __cdecl AIGraphAStarSearch_AddNodeToSearchPrioriyList(
        struct AIAStarSearchList_s *ptList,
        struct AIGraphAStarSearchNode_s *ptNode)
{
  struct AIGraphAStarSearchNode_s *ptHead; // ecx

  ptHead = ptList->ptHead;
  if ( ptList->ptHead->ptNext && ptHead )
  {
    while ( ptHead->vEstimatedTotalCost <= (double)ptNode->vEstimatedTotalCost )
    {
      ptHead = ptHead->ptNext;
      if ( !ptHead->ptNext || !ptHead )
        goto LABEL_6;
    }
    Node_InsertBefore(ptNode, (int)ptHead);
  }
  else
  {
LABEL_6:
    List_AddTail(ptNode, (int)ptList);
  }
}

// source: i/0/aigraph.c:1682  [anchor-callee]
struct AIGraphAStarSearchNode_s *__cdecl AIGraphAStarSearch_BuildPathFromClosedList(
        struct AIGraphAStarSearchData_s *ptSearchData,
        struct AIGraphAStarSearchNode_s *ptDestNode)
{
  struct AIGraphAStarSearchNode_s *v4; // eax
  struct AIGraphAStarSearchNode_s **p_ptParentNode; // eax
  struct AIGraphAStarSearchNode_s *v6; // edi
  struct AIGraphAStarSearchNode_s *v7; // eax
  struct AIGraphAStarSearchNode_s *i; // eax
  struct AIGraphAStarSearchNode_s *result; // eax

  v4 = AIGraphAStarSearch_ClaimSearchNode();
  if ( !v4 )
  {
LABEL_14:
    AIGraphAStarSearch_Clear(ptSearchData);
    return result;
  }
  ptSearchData->vPathCost = ptDestNode->vCostToNode;
  v4->nNodeId = ptDestNode->nNodeId;
  v4->ptParentNode = nullptr;
  v4->vCostToNode = ptDestNode->vCostToNode;
  v4->vEstimatedCostToDest = ptDestNode->vEstimatedCostToDest;
  v4->vEstimatedTotalCost = ptDestNode->vEstimatedTotalCost;
  List_AddHead(v4, (int)&ptSearchData->tCurrentPath);
  p_ptParentNode = &ptDestNode->ptParentNode;
  if ( ptDestNode->ptParentNode )
  {
    do
    {
      v6 = *p_ptParentNode;
      v7 = AIGraphAStarSearch_ClaimSearchNode();
      if ( !v7 )
        goto LABEL_14;
      v7->nNodeId = v6->nNodeId;
      v7->ptParentNode = nullptr;
      v7->vCostToNode = v6->vCostToNode;
      v7->vEstimatedCostToDest = v6->vEstimatedCostToDest;
      v7->vEstimatedTotalCost = v6->vEstimatedTotalCost;
      List_AddHead(v7, (int)&ptSearchData->tCurrentPath);
      p_ptParentNode = &v6->ptParentNode;
    }
    while ( v6->ptParentNode );
  }
  for ( i = ptSearchData->tOpenList.ptHead; ptSearchData->tOpenList.ptHead->ptNext && i; i = ptSearchData->tOpenList.ptHead )
    *((_BYTE *)Node_Remove(i) + 28) = 0;
  for ( result = ptSearchData->tClosedList.ptHead; result->ptNext && result; result = ptSearchData->tClosedList.ptHead )
    *((_BYTE *)Node_Remove(result) + 28) = 0;
  return result;
}

// source: i/0/aigraph.c:1777  [anchor-callee]
char __cdecl AIGraphAStarSearch_CreatePath(
        struct AIGraphAStarSearchData_s *ptSearchData,
        int nGraphId,
        int nSourceNodeId,
        int nDestNodeId,
        unsigned int unMaxNodesToCheckPerCall)
{
  struct Graph_s *Graph; // edi
  struct AIGraphAStarSearchData_s *v7; // ecx
  struct AIGraphAStarSearchNode_s *ptHead; // eax
  struct AIGraphAStarSearchNode_s *i; // eax
  struct GraphNode_s *Node; // esi
  struct AIGraphAStarSearchNode_s *v11; // edi
  double v12; // st7
  long double v13; // st7
  struct AIGraphAStarSearchNode_s *v14; // ebp
  int nNodeId; // esi
  int GraphNodeDataSize; // eax
  struct GraphLink_s *v17; // esi
  int nID1; // edi
  char *pxGraphNodeList; // edx
  int j; // eax
  int v21; // eax
  double v22; // st7
  struct AIGraphAStarSearchNode_s *v23; // esi
  double v24; // st3
  float v25; // eax
  struct AIGraphAStarSearchNode_s *v26; // ecx
  _DWORD *v27; // eax
  int v28; // eax
  float vCostToDest; // [esp+10h] [ebp-2Ch]
  float vCostToNode; // [esp+14h] [ebp-28h]
  float vCostToNodea; // [esp+14h] [ebp-28h]
  struct Graph_s *ptGraph; // [esp+18h] [ebp-24h]
  int iLink; // [esp+1Ch] [ebp-20h]
  struct GraphNode_s *ptGraphNode; // [esp+20h] [ebp-1Ch]
  unsigned int unNodesChecked; // [esp+28h] [ebp-14h]
  int v37; // [esp+2Ch] [ebp-10h]
  float tReal32x3; // [esp+30h] [ebp-Ch]
  float tReal32x3a; // [esp+30h] [ebp-Ch]
  float tReal32x3_4; // [esp+34h] [ebp-8h]

  memset(AIGraphAStarSearch_aptClosedTable, 0, sizeof(AIGraphAStarSearch_aptClosedTable));
  memset(AIGraphAStarSearch_aptOpenTable, 0, sizeof(AIGraphAStarSearch_aptOpenTable));
  unNodesChecked = 0;
  Graph = Graph_GetGraph(nGraphId);
  ptGraph = Graph;
  if ( !Graph->pxGraphNodeList )
    goto LABEL_66;
  if ( nDestNodeId >= Graph->nMaxNodes )
    goto LABEL_66;
  if ( nDestNodeId < 0 )
    goto LABEL_66;
  v37 = (int)Graph->pxGraphNodeList + nDestNodeId * Graph_GetGraphNodeDataSize((int)Graph);
  if ( *(_DWORD *)v37 == -1 )
    goto LABEL_66;
  v7 = ptSearchData;
  if ( nSourceNodeId == ptSearchData->nSourceNodeId
    && nDestNodeId == ptSearchData->nDestNodeId
    && nGraphId == ptSearchData->nGraphId )
  {
    ptHead = ptSearchData->tOpenList.ptHead;
    if ( ptSearchData->tOpenList.ptHead->ptNext && ptHead )
    {
      do
      {
        AIGraphAStarSearch_aptOpenTable[ptHead->nNodeId] = ptHead;
        ptHead = ptHead->ptNext;
      }
      while ( ptHead->ptNext && ptHead );
    }
    for ( i = ptSearchData->tClosedList.ptHead; i->ptNext && i; i = i->ptNext )
      AIGraphAStarSearch_aptClosedTable[i->nNodeId] = i;
    goto LABEL_19;
  }
  AIGraphAStarSearch_Clear(ptSearchData);
  Node = Graph_GetNode(Graph, nSourceNodeId);
  v11 = AIGraphAStarSearch_ClaimSearchNode();
  if ( !v11 )
  {
LABEL_65:
    AIGraphAStarSearch_Clear(ptSearchData);
LABEL_66:
    LOBYTE(v28) = 0;
    return v28;
  }
  v11->nNodeId = nSourceNodeId;
  v11->ptParentNode = nullptr;
  v11->vCostToNode = 0.0;
  tReal32x3 = Node->tPos.vX - *(double *)(v37 + 8);
  v12 = Node->tPos.vY - *(double *)(v37 + 16);
  v13 = sqrt(
          (Node->tPos.vZ - *(double *)(v37 + 24)) * (Node->tPos.vZ - *(double *)(v37 + 24))
        + v12 * v12
        + tReal32x3 * tReal32x3);
  v11->vEstimatedCostToDest = v13;
  v11->vEstimatedTotalCost = v13;
  ptSearchData->bFlags = 0;
  ptSearchData->nGraphId = nGraphId;
  ptSearchData->nDestNodeId = nDestNodeId;
  ptSearchData->nSourceNodeId = nSourceNodeId;
  AIGraphAStarSearch_AddNodeToSearchPrioriyList(&ptSearchData->tOpenList, v11);
  AIGraphAStarSearch_aptOpenTable[nSourceNodeId] = v11;
  Graph = ptGraph;
  v7 = ptSearchData;
LABEL_19:
  if ( !v7->tOpenList.ptHead->ptNext )
  {
    v14 = nullptr;
    goto LABEL_69;
  }
  v14 = v7->tOpenList.ptHead;
  if ( !v7->tOpenList.ptHead )
    goto LABEL_69;
  while ( unNodesChecked < unMaxNodesToCheckPerCall )
  {
    nNodeId = v14->nNodeId;
    if ( nNodeId == v7->nDestNodeId )
    {
      AIGraphAStarSearch_BuildPathFromClosedList(v7, v14);
      LOBYTE(v28) = 1;
      return v28;
    }
    if ( Graph->pxGraphNodeList && nNodeId < Graph->nMaxNodes && nNodeId >= 0 )
    {
      GraphNodeDataSize = Graph_GetGraphNodeDataSize((int)Graph);
      ptGraphNode = *(_DWORD *)((char *)Graph->pxGraphNodeList + nNodeId * GraphNodeDataSize) == -1
                  ? nullptr
                  : (struct GraphNode_s *)((char *)Graph->pxGraphNodeList + nNodeId * GraphNodeDataSize);
    }
    else
    {
      ptGraphNode = nullptr;
    }
    for ( iLink = 0; iLink < 64; ++iLink )
    {
      v17 = ptGraphNode->aptLinks[iLink];
      if ( v17 )
      {
        nID1 = v17->nID1;
        if ( nID1 == v14->nNodeId )
          nID1 = v17->nID2;
        pxGraphNodeList = (char *)ptGraph->pxGraphNodeList;
        if ( pxGraphNodeList && nID1 < ptGraph->nMaxNodes && nID1 >= 0 )
        {
          for ( j = 0; ; ++j )
          {
            if ( j >= 4 )
            {
              LDebug_Error("Undefined GraphNodeDataSize");
              abort();
            }
            if ( ptGraph->tQTask.eQTaskType == Graph_atGraphNodeDataSize[j].eGraphQTaskType )
              break;
          }
          v21 = *(_DWORD *)&pxGraphNodeList[nID1 * Graph_atGraphNodeDataSize[j].nDataSize] == -1
              ? 0
              : (unsigned int)&pxGraphNodeList[nID1 * Graph_atGraphNodeDataSize[j].nDataSize];
        }
        else
        {
          v21 = 0;
        }
        v22 = v17->vLength + v14->vCostToNode;
        if ( (AIGraph_bVehicleNodeCriteria & ptGraphNode->bCriteria) != (AIGraph_bVehicleNodeCriteria
                                                                       & *(_DWORD *)(v21 + 56)) )
          v22 = v22 + 81920.0;
        v23 = AIGraphAStarSearch_aptOpenTable[nID1];
        vCostToNode = v22 + *(float *)(v21 + 584);
        tReal32x3a = *(double *)(v37 + 8) - *(double *)(v21 + 8);
        tReal32x3_4 = *(double *)(v37 + 16) - *(double *)(v21 + 16);
        v24 = *(double *)(v37 + 24) - *(double *)(v21 + 24);
        vCostToDest = sqrt(tReal32x3a * tReal32x3a + tReal32x3_4 * tReal32x3_4 + v24 * v24);
        if ( v23 )
        {
          if ( vCostToDest + vCostToNode <= v23->vEstimatedTotalCost )
          {
            Node_Remove(v23);
            v23->ptPrev = nullptr;
            v23->ptNext = nullptr;
            AIGraphAStarSearch_aptOpenTable[nID1] = nullptr;
            goto LABEL_51;
          }
        }
        else
        {
          v23 = AIGraphAStarSearch_aptClosedTable[nID1];
          if ( v23 )
          {
            if ( vCostToDest + vCostToNode <= v23->vEstimatedTotalCost )
            {
              Node_Remove(AIGraphAStarSearch_aptClosedTable[nID1]);
              v23->ptPrev = nullptr;
              v23->ptNext = nullptr;
              AIGraphAStarSearch_aptClosedTable[nID1] = nullptr;
              goto LABEL_51;
            }
          }
          else
          {
            v23 = AIGraphAStarSearch_ClaimSearchNode();
            if ( !v23 )
              goto LABEL_65;
LABEL_51:
            v25 = vCostToNode;
            v23->nNodeId = nID1;
            v23->ptParentNode = v14;
            vCostToNodea = vCostToDest + vCostToNode;
            v23->vCostToNode = v25;
            v23->vEstimatedTotalCost = vCostToNodea;
            v23->vEstimatedCostToDest = vCostToDest;
            v26 = ptSearchData->tOpenList.ptHead;
            if ( ptSearchData->tOpenList.ptHead->ptNext && v26 )
            {
              while ( v26->vEstimatedTotalCost <= (double)vCostToNodea )
              {
                v26 = v26->ptNext;
                if ( !v26->ptNext || !v26 )
                  goto LABEL_56;
              }
              Node_InsertBefore(v23, (int)v26);
            }
            else
            {
LABEL_56:
              List_AddTail(v23, (int)ptSearchData);
            }
            AIGraphAStarSearch_aptOpenTable[nID1] = v23;
          }
        }
        Graph = ptGraph;
        continue;
      }
      iLink = 64;
    }
    v27 = Node_Remove(v14);
    v14->ptPrev = nullptr;
    v14->ptNext = nullptr;
    List_AddHead(v27, (int)&ptSearchData->tClosedList);
    AIGraphAStarSearch_aptClosedTable[v14->nNodeId] = v14;
    v14 = ptSearchData->tOpenList.ptHead->ptNext != nullptr ? ptSearchData->tOpenList.ptHead : nullptr;
    ++unNodesChecked;
    v7 = ptSearchData;
    if ( !v14 )
    {
LABEL_69:
      v7->bFlags |= 1u;
      AIGraphAStarSearch_Clear(v7);
      return v14 != nullptr;
    }
  }
  if ( !v14 )
    goto LABEL_69;
  return v14 != nullptr;
}

// source: i/0/aigraph.c:2048  [anchor-mhash]
struct AIAStarSearchList_s *__cdecl AIGraphAStarSearch_GetPath(
        struct AIGraphAStarSearchData_s *ptSearchData,
        int nGraphId,
        int nSourceNodeId,
        int nDestNodeId)
{
  struct AIGraphAStarSearchNode_s *ptHead; // ecx
  struct AIAStarSearchList_s *result; // eax

  if ( ptSearchData->nGraphId != nGraphId )
    return nullptr;
  if ( ptSearchData->nSourceNodeId != nSourceNodeId )
    return nullptr;
  if ( ptSearchData->nDestNodeId != nDestNodeId )
    return nullptr;
  ptHead = ptSearchData->tCurrentPath.ptHead;
  result = &ptSearchData->tCurrentPath;
  if ( !ptHead->ptNext || !ptHead )
    return nullptr;
  return result;
}

// source: i/0/aigraph.c:2076  [anchor-mhash]
char __cdecl AIGraph_GetLineNodeBorder2DCollision(
        struct real64x3_t *ptCollisionPoint,
        struct GraphNode_s *ptGraphNode,
        struct real64x3_t *ptLineStartPos,
        struct real64x3_t *ptLineEndPos)
{
  #pragma pack(push, 1)
  union
  {
    struct { char isHit; };
    struct { char igi2_o1[1]; double vXMin; };
    struct { char igi2_o2[9]; double vXMax; };
    struct { char igi2_o3[9]; double vXMaxa; };
    struct { char igi2_o4[17]; double vYMax; };
    struct { char igi2_o5[17]; double vYMaxa; };
    struct { char igi2_o6[25]; double vYMin; };
    struct { char igi2_o7[25]; double vYMina; };
    struct { char igi2_o8[33]; struct real64x3_t tPos; };
    char igi2_extent[57];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  double v4; // st7
  double v5; // st7
  double v6; // st6
  double v7; // st5
  double v8; // st4

  igi2_frame.isHit = 0;
  Graph_GetNodePos(&igi2_frame.tPos, ptGraphNode);
  v4 = ptGraphNode->vRadius * 4096.0;
  igi2_frame.vXMin = igi2_frame.tPos.vX - v4;
  igi2_frame.vXMax = igi2_frame.tPos.vX + v4;
  igi2_frame.vYMin = igi2_frame.tPos.vY - v4;
  igi2_frame.vYMax = v4 + igi2_frame.tPos.vY;
  v5 = 1.0;
  if ( ptLineStartPos->vX < igi2_frame.vXMin != ptLineEndPos->vX < igi2_frame.vXMin )
  {
    igi2_frame.isHit = 1;
    v5 = (igi2_frame.vXMin - ptLineStartPos->vX) / (ptLineEndPos->vX - ptLineStartPos->vX);
  }
  if ( ptLineStartPos->vX > igi2_frame.vXMax != ptLineEndPos->vX > igi2_frame.vXMax )
  {
    igi2_frame.vXMaxa = (igi2_frame.vXMax - ptLineStartPos->vX) / (ptLineEndPos->vX - ptLineStartPos->vX);
    if ( igi2_frame.vXMaxa < v5 )
      v5 = igi2_frame.vXMaxa;
    igi2_frame.isHit = 1;
  }
  if ( ptLineStartPos->vY > igi2_frame.vYMax != ptLineEndPos->vY > igi2_frame.vYMax )
  {
    igi2_frame.vYMaxa = (igi2_frame.vYMax - ptLineStartPos->vY) / (ptLineEndPos->vY - ptLineStartPos->vY);
    if ( igi2_frame.vYMaxa < v5 )
      v5 = igi2_frame.vYMaxa;
    igi2_frame.isHit = 1;
  }
  if ( ptLineStartPos->vY > igi2_frame.vYMin != ptLineEndPos->vY > igi2_frame.vYMin )
  {
    igi2_frame.vYMina = (igi2_frame.vYMin - ptLineStartPos->vY) / (ptLineEndPos->vY - ptLineStartPos->vY);
    if ( igi2_frame.vYMina < v5 )
      v5 = igi2_frame.vYMina;
    goto LABEL_15;
  }
  if ( igi2_frame.isHit )
  {
LABEL_15:
    v6 = ptLineEndPos->vX - ptLineStartPos->vX;
    v7 = ptLineEndPos->vY - ptLineStartPos->vY;
    v8 = ptLineEndPos->vZ - ptLineStartPos->vZ;
    igi2_frame.tPos.vZ = v8;
    igi2_frame.tPos.vX = v6 * v5;
    igi2_frame.tPos.vY = v7 * v5;
    ptCollisionPoint->vX = igi2_frame.tPos.vX + ptLineStartPos->vX;
    ptCollisionPoint->vY = igi2_frame.tPos.vY + ptLineStartPos->vY;
    ptCollisionPoint->vZ = v5 * v8 + ptLineStartPos->vZ;
    return 1;
  }
  return 0;
}

// source: i/0/aigraph.c:2161  [anchor-hash]
void __cdecl AIGraphAStarSearch_Clear(struct AIGraphAStarSearchData_s *ptSearchData)
{
  struct AIGraphAStarSearchNode_s *i; // eax
  struct AIGraphAStarSearchNode_s *j; // eax
  struct AIGraphAStarSearchNode_s *k; // eax

  for ( i = ptSearchData->tCurrentPath.ptHead; i->ptNext && i; i = ptSearchData->tCurrentPath.ptHead )
    *((_BYTE *)Node_Remove(i) + 28) = 0;
  for ( j = ptSearchData->tOpenList.ptHead; ptSearchData->tOpenList.ptHead->ptNext && j; j = ptSearchData->tOpenList.ptHead )
    *((_BYTE *)Node_Remove(j) + 28) = 0;
  for ( k = ptSearchData->tClosedList.ptHead; k->ptNext && k; k = ptSearchData->tClosedList.ptHead )
    *((_BYTE *)Node_Remove(k) + 28) = 0;
  ptSearchData->nSourceNodeId = -1;
  ptSearchData->nDestNodeId = -1;
  ptSearchData->nGraphId = -1;
}

// source: i/0/aigraph.c:2204  [anchor-hash]
struct AIGraphAStarSearchData_s *__cdecl AIGraphAStarSearch_RemoveHeadFromCurrentPath(
        struct AIGraphAStarSearchData_s *ptSearchData)
{
  struct AIGraphAStarSearchData_s *result; // eax

  result = (struct AIGraphAStarSearchData_s *)ptSearchData->tCurrentPath.ptHead;
  if ( result->tOpenList.ptHead )
  {
    if ( result )
    {
      result = (struct AIGraphAStarSearchData_s *)Node_Remove(result);
      LOBYTE(result->tCurrentPath.ptMiddle) = 0;
    }
  }
  return result;
}

// source: i/0/aigraph.c:2227  [anchor-callee]
void __cdecl AIGraph_DecideCoverItemForNode(struct AIGraph_t *ptAIGraph, struct GraphNode_s *ptGraphNode)
{
  #pragma pack(push, 1)
  union
  {
    struct { int iJ; };
    struct { char igi2_o1[4]; double v25; };
    struct { char igi2_o2[12]; int abCoverInfo[32]; };
    struct { char igi2_o3[140]; struct real64x3_t atEnd[128]; };
    struct { char igi2_o4[3212]; struct real64x3_t atStart[128]; };
    struct { char igi2_o5[6284]; struct QIntersection_s atQIntersection[128]; };
    char igi2_extent[21648];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v2; // ebx
  unsigned int v3; // esi
  float *v4; // ebp
  int v5; // edi
  struct real64x3_t *v6; // edx
  double v7; // st7
  double v8; // st6
  long double v9; // st6
  int v10; // ecx
  int *p_isHit; // edx
  int i; // eax
  int v13; // edx
  int j; // eax
  int v15; // ecx
  int v16; // ecx
  int v17; // ecx
  int v18; // ecx
  int v19; // ecx
  int v20; // ecx
  int v21; // ecx
  int v22; // ecx
  _DWORD *v23; // eax

  v2 = 0;
  memset(igi2_frame.abCoverInfo, 0, sizeof(igi2_frame.abCoverInfo));
  v3 = 0;
  v4 = AIGraph_avNodeCoverHeight;
  do
  {
    v5 = 0;
    igi2_frame.v25 = *v4;
    igi2_frame.iJ = 0;
    do
    {
      v6 = &igi2_frame.atStart[v3 / 0x18];
      Graph_GetNodePos(&igi2_frame.atStart[v3 / 0x18], ptGraphNode);
      v7 = igi2_frame.v25 + igi2_frame.atStart[v3 / 0x18].vZ;
      ++v5;
      v3 += 24;
      v6->vZ = v7;
      v8 = (double)igi2_frame.iJ;
      igi2_frame.iJ = v5;
      v9 = v8 * 6.2831854820251465 * 0.03125;
      *(long double *)&igi2_frame.abCoverInfo[v3 / 4 + 26] = cos(v9) * 8192.0 + v6->vX;
      *(long double *)&igi2_frame.abCoverInfo[v3 / 4 + 28] = sin(v9) * 8192.0 + igi2_frame.atEnd[v3 / 0x18 + 127].vY;
      *(double *)&igi2_frame.abCoverInfo[v3 / 4 + 30] = v7;
    }
    while ( v5 < 32 );
    ++v4;
  }
  while ( (int)v4 < 7014284 );
  World_TraceLines(
    World_ptActiveWorld,
    igi2_frame.atQIntersection,
    igi2_frame.atStart,
    igi2_frame.atEnd,
    128,
    512,
    nullptr,
    Forest_bQTaskGroup & 0x67FFFFFF | 0x18000000);
  v10 = 0;
  p_isHit = &igi2_frame.atQIntersection[1].isHit;
  do
  {
    for ( i = 0; i < 32; i += 8 )
    {
      if ( *(p_isHit - 30) )
      {
        v2 = 1;
        igi2_frame.abCoverInfo[i] |= 1 << v10;
      }
      if ( *p_isHit )
      {
        v2 = 1;
        igi2_frame.abCoverInfo[i + 1] |= 1 << v10;
      }
      if ( p_isHit[30] )
      {
        v2 = 1;
        igi2_frame.abCoverInfo[i + 2] |= 1 << v10;
      }
      if ( p_isHit[60] )
      {
        v2 = 1;
        igi2_frame.abCoverInfo[i + 3] |= 1 << v10;
      }
      if ( p_isHit[90] )
      {
        v2 = 1;
        igi2_frame.abCoverInfo[i + 4] |= 1 << v10;
      }
      if ( p_isHit[120] )
      {
        v2 = 1;
        igi2_frame.abCoverInfo[i + 5] |= 1 << v10;
      }
      if ( p_isHit[150] )
      {
        v2 = 1;
        igi2_frame.abCoverInfo[i + 6] |= 1 << v10;
      }
      if ( p_isHit[180] )
      {
        v2 = 1;
        igi2_frame.abCoverInfo[i + 7] |= 1 << v10;
      }
      p_isHit += 240;
    }
    ++v10;
  }
  while ( v10 < 4 );
  if ( v2 )
  {
    v13 = 0;
    for ( j = 0; j < 32; j += 8 )
    {
      v15 = igi2_frame.abCoverInfo[j];
      if ( (v15 & 7) != 0 && (v15 & 8) == 0 )
        ++v13;
      v16 = igi2_frame.abCoverInfo[j + 1];
      if ( (v16 & 7) != 0 && (v16 & 8) == 0 )
        ++v13;
      v17 = igi2_frame.abCoverInfo[j + 2];
      if ( (v17 & 7) != 0 && (v17 & 8) == 0 )
        ++v13;
      v18 = igi2_frame.abCoverInfo[j + 3];
      if ( (v18 & 7) != 0 && (v18 & 8) == 0 )
        ++v13;
      v19 = igi2_frame.abCoverInfo[j + 4];
      if ( (v19 & 7) != 0 && (v19 & 8) == 0 )
        ++v13;
      v20 = igi2_frame.abCoverInfo[j + 5];
      if ( (v20 & 7) != 0 && (v20 & 8) == 0 )
        ++v13;
      v21 = igi2_frame.abCoverInfo[j + 6];
      if ( (v21 & 7) != 0 && (v21 & 8) == 0 )
        ++v13;
      v22 = igi2_frame.abCoverInfo[j + 7];
      if ( (v22 & 7) != 0 && (v22 & 8) == 0 )
        ++v13;
    }
    if ( v13 > 2 )
    {
      v23 = Mem_AllocFn(144, 4);
      v23[1] = 0;
      *v23 = 0;
      qmemcpy(v23 + 3, igi2_frame.abCoverInfo, 0x80u);
      v23[35] = ptGraphNode->nID;
      List_AddTail(v23, (int)&ptAIGraph->tNodeCoverItemList);
    }
  }
}

// source: i/0/aigraph.c:2403  [anchor-callee]
void __cdecl AIGraph_UpdateNodeCover(struct AIGraph_t *ptAIGraph)
{
  struct AIGraphNodeCoverItem_s *i; // eax
  int v2; // esi
  int nMaxNodes; // eax
  int j; // esi
  int v5; // eax

  for ( i = ptAIGraph->tNodeCoverItemList.ptHead; i->ptNext && i; i = ptAIGraph->tNodeCoverItemList.ptHead )
  {
    v2 = *(_DWORD *)((unsigned int)(Node_Remove(i) - 1) & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v2);
    memset(*(void **)(v2 + 8), 0xCDu, *(_DWORD *)(v2 + 16));
    free((void *)v2);
  }
  nMaxNodes = ptAIGraph->tGraph.nMaxNodes;
  for ( j = 0; j < nMaxNodes; ++j )
  {
    if ( ptAIGraph->tGraph.pxGraphNodeList && j < nMaxNodes && j >= 0 )
    {
      v5 = j * Graph_GetGraphNodeDataSize((int)ptAIGraph);
      if ( *(_DWORD *)((char *)ptAIGraph->tGraph.pxGraphNodeList + v5) != -1 )
        AIGraph_DecideCoverItemForNode(
          ptAIGraph,
          (struct GraphNode_s *)((char *)ptAIGraph->tGraph.pxGraphNodeList + v5));
    }
    nMaxNodes = ptAIGraph->tGraph.nMaxNodes;
  }
}

// source: i/0/aigraph.c:2452  [anchor-callee]
void __cdecl AIGraph_SaveNodeCoverData(struct AIGraph_t *ptAIGraph)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct ILFContainerNode_s *ptContainerNode; };
    struct { char igi2_o1[4]; struct AIGraph_ILFCoverNodeHeader_s tILFHeader; };
    struct { char igi2_o2[12]; char zFileName[256]; };
    char igi2_extent[268];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct AIGraphNodeCoverItem_s *v1; // esi
  _DWORD *v2; // edx
  _DWORD *v3; // edx
  int v4; // ecx
  struct QReference_s *v5; // eax

  v1 = ptAIGraph->tNodeCoverItemList.ptHead->ptNext != nullptr ? ptAIGraph->tNodeCoverItemList.ptHead : nullptr;
  igi2_frame.ptContainerNode = ILF_NewContainterNode(0x46464C49u, 0x43434941u);
  igi2_frame.tILFHeader.nNumNodes = List_Length(&ptAIGraph->tNodeCoverItemList);
  igi2_frame.tILFHeader.nVersion = 1;
  v2 = Mem_AllocFn(40, 4);
  memset(v2, 0, 0x28u);
  v2[9] = &igi2_frame.tILFHeader;
  v2[2] = 1212369217;
  v2[8] = 0;
  v2[1] = 0;
  *v2 = 0;
  v2[7] = 8;
  v2[5] = 0;
  List_AddTail(v2, (int)&igi2_frame.ptContainerNode->tChunkNodeList);
  if ( v1 )
  {
    do
    {
      v3 = Mem_AllocFn(40, 4);
      memset(v3, 0, 0x28u);
      v3[2] = 1313032513;
      v3[8] = 0;
      v3[1] = 0;
      *v3 = 0;
      v3[9] = v1;
      v3[7] = 144;
      v3[5] = 0;
      List_AddTail(v3, (int)&igi2_frame.ptContainerNode->tChunkNodeList);
      v1 = v1->ptNext;
    }
    while ( v1->ptNext && v1 );
  }
  v4 = 0;
  while ( 1 )
  {
    v5 = Level_atLevelQTaskID[v4];
    if ( v5 )
    {
      if ( v5->pxObject == ptAIGraph )
        break;
    }
    if ( ++v4 >= 4096 )
    {
      v4 = -1;
      break;
    }
  }
  sprintf(igi2_frame.zFileName, "MISSION:graphs/graphcover%d.dat", v4);
  ILF_Write(igi2_frame.ptContainerNode, igi2_frame.zFileName);
  ILF_DeleteContainerNode(igi2_frame.ptContainerNode);
}

// source: i/0/aigraph.c:2512  [anchor-refs]
void __cdecl AIGraph_LoadNodeCoverData(struct AIGraph_t *ptAIGraph)
{
  #pragma pack(push, 1)
  union
  {
    struct { unsigned int unSize; };
    struct { char igi2_o1[4]; void *pxResource; };
    struct { char igi2_o2[8]; char zFileName[256]; };
    char igi2_extent[264];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v1; // eax
  struct QReference_s *v2; // ecx
  _DWORD *v3; // eax
  void *v4; // esi
  struct AIGraphNodeCoverItem_s *ptHead; // eax
  struct AIGraphNodeCoverItemList_s *p_tNodeCoverItemList; // ebp
  bool v7; // zf
  _DWORD **v8; // eax
  int v9; // ebx
  _DWORD *FirstChunk; // edi
  int v11; // eax
  _DWORD *v12; // edi
  _BYTE *ChunkData; // ebx
  _DWORD *v14; // eax
  _DWORD *v15; // ecx
  int v16; // esi
  unsigned int v17; // ecx
  int v18; // eax
  int v19; // eax

  v1 = 0;
  while ( 1 )
  {
    v2 = Level_atLevelQTaskID[v1];
    if ( v2 )
    {
      if ( v2->pxObject == ptAIGraph )
        break;
    }
    if ( ++v1 >= 4096 )
    {
      v1 = -1;
      break;
    }
  }
  sprintf(igi2_frame.zFileName, "MISSION:graphs/graphcover%d.dat", v1);
  if ( Resource_IsLoadedInternal(igi2_frame.zFileName, nullptr) || File_Exists(igi2_frame.zFileName) )
  {
    v3 = Resource_Load(igi2_frame.zFileName, &igi2_frame.unSize);
    v4 = v3;
    igi2_frame.pxResource = v3;
    if ( v3 && *v3 == 1179012169 && v3[4] == 1128483137 )
    {
      ptHead = ptAIGraph->tNodeCoverItemList.ptHead;
      p_tNodeCoverItemList = &ptAIGraph->tNodeCoverItemList;
      v7 = ptHead->ptNext == nullptr;
      igi2_frame.unSize = (unsigned int)&ptAIGraph->tNodeCoverItemList;
      if ( !v7 && ptHead )
      {
        do
        {
          v8 = Node_Remove(ptHead);
          --Mem_nCurrentAllocations;
          v9 = *(_DWORD *)((unsigned int)(v8 - 1) & 0xFFFFFFFC);
          Node_Remove((_DWORD **)v9);
          memset(*(void **)(v9 + 8), 0xCDu, *(_DWORD *)(v9 + 16));
          free((void *)v9);
          ptHead = p_tNodeCoverItemList->ptHead;
        }
        while ( p_tNodeCoverItemList->ptHead->ptNext && ptHead );
      }
      FirstChunk = ILF_GetFirstChunk(v4);
      if ( *((_DWORD *)ILF_GetChunkData(FirstChunk, v4) + 1) != 1 )
      {
        Resource_Unload(igi2_frame.zFileName);
        return;
      }
      if ( FirstChunk )
      {
        v11 = FirstChunk[3];
        if ( v11 )
        {
          v12 = (_DWORD *)((char *)FirstChunk + v11);
          if ( v12 )
          {
            while ( 1 )
            {
              ChunkData = ILF_GetChunkData(v12, v4);
              v14 = Mem_AllocFn(144, 4);
              v14[1] = 0;
              *v14 = 0;
              v15 = v14 + 3;
              v16 = 32;
              do
              {
                *v15 = *(_DWORD *)((char *)v15 + ((char *)(ChunkData) - (char *)(v14)));
                ++v15;
                --v16;
              }
              while ( v16 );
              v14[35] = *((_DWORD *)ChunkData + 35);
              v17 = igi2_frame.unSize;
              v14[2] = 0;
              List_AddTail(v14, v17);
              v18 = v12[3];
              if ( !v18 )
                break;
              v12 = (_DWORD *)((char *)v12 + v18);
              if ( !v12 )
                break;
              v4 = igi2_frame.pxResource;
            }
          }
        }
      }
    }
    if ( Resource_IsLoadedInternal(igi2_frame.zFileName, (struct Resource_s **)&igi2_frame.unSize) )
    {
      v19 = *(_DWORD *)(igi2_frame.unSize + 36);
      if ( v19 != 3 && v19 != 1 )
        Resource_Remove((struct Resource_s *)igi2_frame.unSize);
    }
  }
}

// source: i/0/aigraph.c:2610  [anchor-callee]
int __cdecl AIGraph_GetCoverSectorFromPosition(
        struct AIGraph_t *ptAIGraph,
        struct real64x3_t *ptNodePos,
        struct real64x3_t *ptPosToCheck)
{
  double v3; // st7
  double v4; // st6
  double v5; // st1
  long double v6; // st2
  double v7; // st7
  float tDelta; // [esp+0h] [ebp-Ch]
  float tDelta_4; // [esp+4h] [ebp-8h]

  v3 = ptPosToCheck->vX - ptNodePos->vX;
  v4 = ptPosToCheck->vY - ptNodePos->vY;
  v5 = ptPosToCheck->vZ - ptNodePos->vZ;
  v6 = sqrt(v3 * v3 + v4 * v4 + v5 * v5);
  if ( v6 == 0.0 )
    return 0;
  tDelta = 1.0 / v6 * v3;
  tDelta_4 = 1.0 / v6 * v4;
  v7 = Real32_Acos(tDelta);
  if ( tDelta_4 < 0.0 )
    v7 = 6.2831854820251465 - v7;
  return (__int64)(5.092957973480225 * v7);
}

// source: i/0/aigraph.c:2661  [anchor-callee]
char __cdecl AIGraph_CoverNodeProvidesCoverFromPosition(
        struct AIGraph_t *ptAIGraph,
        struct AIGraphNodeCoverItem_s *ptCoverNodeItem,
        struct real64x3_t *ptPosition)
{
  int nNodeId; // edi
  struct GraphNode_s *v4; // eax
  struct real64x3_t ptNodePos; // [esp+8h] [ebp-18h] BYREF

  nNodeId = ptCoverNodeItem->nNodeId;
  if ( !ptAIGraph->tGraph.pxGraphNodeList )
    return 0;
  if ( nNodeId >= ptAIGraph->tGraph.nMaxNodes )
    return 0;
  if ( nNodeId < 0 )
    return 0;
  v4 = (struct GraphNode_s *)((char *)ptAIGraph->tGraph.pxGraphNodeList
                            + nNodeId * Graph_GetGraphNodeDataSize((int)ptAIGraph));
  if ( v4->nID == -1 )
    return 0;
  Graph_GetNodePos(&ptNodePos, v4);
  return ptCoverNodeItem->abCoverCircle[AIGraph_GetCoverSectorFromPosition(ptAIGraph, &ptNodePos, ptPosition)] != 0;
}

// source: i/0/aigraph.c:2704  [size]
struct AIGraphNodeCoverItem_s *__cdecl AIGraph_LockCoverNode(
        struct AIGraphNodeCoverItem_s *ptCoverNode)
{
  ptCoverNode->bFlags |= 1u;
  return ptCoverNode;
}

// source: i/0/aigraph.c:2719  [anchor-callee]
struct AIGraph_t *__cdecl AIGraph_UnlockCoverNode(
        struct AIGraph_t *ptAIGraph,
        int nNodeId)
{
  struct AIGraph_t *result; // eax

  result = (struct AIGraph_t *)ptAIGraph->tNodeCoverItemList.ptHead;
  if ( result->tGraph.tQTask.ptNext && result )
  {
    while ( result->tGraph.tGraphLinkList.ptMiddle != (struct GraphLink_s *)nNodeId )
    {
      result = (struct AIGraph_t *)result->tGraph.tQTask.ptNext;
      if ( !result->tGraph.tQTask.ptNext || !result )
        return result;
    }
    result->tGraph.tQTask.tQTaskChildren.ptHead = (struct QTask_s *)((int)result->tGraph.tQTask.tQTaskChildren.ptHead
                                                                   & ~1u);
  }
  return result;
}

// source: i/0/aigraph.c:2750  [anchor-callee]
void __cdecl AIGraph_CheckNeighboursRecusivelyForClosestNode(
        struct AIGraph_t *ptAIGraph,
        struct AIGraphNode_s *ptNode,
        struct AIGraphNode_s **pptClosestNode,
        float *pvClosestDistance,
        struct real64x3_t *ptPosition,
        int nMaxNodesToCheck)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct GraphLink_s **aptLinks; };
    struct { char igi2_o1[4]; float vClosestNeighbourDistance; };
    struct { char igi2_o2[8]; int v16; };
    struct { char igi2_o3[12]; float tReal32x3; };
    struct { char igi2_o4[16]; float tReal32x3_4; };
    struct { char igi2_o5[24]; struct real64x3_t tReal64x3; };
    char igi2_extent[48];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct AIGraphNode_s *v7; // ebx
  struct GraphLink_s *v8; // eax
  int nID1; // esi
  int GraphNodeDataSize; // eax
  struct GraphNode_s *v11; // esi
  long double v12; // st4
  bool v13; // zf

  v7 = nullptr;
  if ( nMaxNodesToCheck )
  {
    do
    {
      igi2_frame.aptLinks = ptNode->tGraphNode.aptLinks;
      igi2_frame.v16 = 64;
      do
      {
        v8 = *igi2_frame.aptLinks;
        if ( *igi2_frame.aptLinks )
        {
          nID1 = v8->nID1;
          if ( nID1 == ptNode->tGraphNode.nID )
            nID1 = v8->nID2;
          if ( ptAIGraph->tGraph.pxGraphNodeList && nID1 < ptAIGraph->tGraph.nMaxNodes && nID1 >= 0 )
          {
            GraphNodeDataSize = Graph_GetGraphNodeDataSize((int)ptAIGraph);
            v11 = *(_DWORD *)((char *)ptAIGraph->tGraph.pxGraphNodeList + nID1 * GraphNodeDataSize) == -1
                ? nullptr
                : (struct GraphNode_s *)((char *)ptAIGraph->tGraph.pxGraphNodeList + nID1 * GraphNodeDataSize);
          }
          else
          {
            v11 = nullptr;
          }
          if ( (AIGraph_bVehicleNodeCriteria & ptNode->tGraphNode.bCriteria) != 0
            || (AIGraph_bVehicleNodeCriteria & v11->bCriteria) == 0 )
          {
            Graph_GetNodePos(&igi2_frame.tReal64x3, v11);
            igi2_frame.tReal32x3 = igi2_frame.tReal64x3.vX - ptPosition->vX;
            igi2_frame.tReal32x3_4 = igi2_frame.tReal64x3.vY - ptPosition->vY;
            v12 = sqrt(
                    igi2_frame.tReal32x3 * igi2_frame.tReal32x3
                  + igi2_frame.tReal32x3_4 * igi2_frame.tReal32x3_4
                  + (igi2_frame.tReal64x3.vZ - ptPosition->vZ) * (igi2_frame.tReal64x3.vZ - ptPosition->vZ));
            if ( !v7 || v12 < igi2_frame.vClosestNeighbourDistance )
            {
              igi2_frame.vClosestNeighbourDistance = v12;
              v7 = (struct AIGraphNode_s *)v11;
            }
          }
        }
        v13 = igi2_frame.v16 == 1;
        ++igi2_frame.aptLinks;
        --igi2_frame.v16;
      }
      while ( !v13 );
      if ( !v7 || *pptClosestNode && igi2_frame.vClosestNeighbourDistance >= (double)*pvClosestDistance )
        break;
      *pvClosestDistance = igi2_frame.vClosestNeighbourDistance;
      v13 = nMaxNodesToCheck == 1;
      *pptClosestNode = v7;
      ptNode = v7;
      --nMaxNodesToCheck;
      v7 = nullptr;
    }
    while ( !v13 );
  }
}

// source: i/0/aigraph.c:2833  [anchor-callee]
struct AIGraphNode_s *__cdecl AIGraph_GetClosestNodeFromStartingNode(
        struct AIGraph_t *ptAIGraph,
        struct AIGraphNode_s *ptStartingNode,
        struct real64x3_t *ptPosition,
        int nMaxNodesToCheck)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct AIGraphNode_s *ptClosestNode; };
    struct { char igi2_o1[4]; float vClosestDistance; };
    char igi2_extent[8];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct AIGraphNode_s *result; // eax

  igi2_frame.vClosestDistance = 0.0;
  igi2_frame.ptClosestNode = nullptr;
  AIGraph_CheckNeighboursRecusivelyForClosestNode(
    ptAIGraph,
    ptStartingNode,
    &igi2_frame.ptClosestNode,
    &igi2_frame.vClosestDistance,
    ptPosition,
    nMaxNodesToCheck);
  result = igi2_frame.ptClosestNode;
  if ( !igi2_frame.ptClosestNode )
    return ptStartingNode;
  return result;
}

// source: i/0/aigraph.c:2883  [anchor-strings]
void __cdecl AIGraph_ValidatePaths(struct AIGraph_t *ptAIGraph)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct _iobuf *fpFile; };
    struct { FILE *fpFilea; };
    struct { char igi2_o2[4]; int iI0; };
    struct { char igi2_o3[8]; struct AIGraphAStarSearchData_s tSearchData; };
    struct { char igi2_o4[64]; int aiLeastConnected[10]; };
    struct { char igi2_o5[104]; char acFileName[104]; };
    struct { char igi2_o6[208]; int aiPathCount[2000]; };
    char igi2_extent[8208];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int nMaxNodes; // ecx
  int v3; // esi
  FILE *v4; // eax
  int v5; // ebx
  int v6; // edx
  int v7; // esi
  int v8; // eax
  int v9; // ecx
  char *pxGraphNodeList; // edi
  int i; // eax
  int v12; // eax
  int v13; // edx
  char *v14; // eax
  int j; // edi
  char *v16; // edx
  int k; // eax
  int v18; // eax
  int v19; // ecx
  char *v20; // eax
  int m; // esi
  int v22; // eax

  memset(igi2_frame.aiPathCount, 0, sizeof(igi2_frame.aiPathCount));
  igi2_frame.tSearchData.tClosedList.ptTail = (struct AIGraphAStarSearchNode_s *)&igi2_frame.tSearchData.tClosedList;
  igi2_frame.tSearchData.vPathCost = 0.0;
  igi2_frame.tSearchData.tCurrentPath.ptTail = (struct AIGraphAStarSearchNode_s *)&igi2_frame.tSearchData.tCurrentPath;
  igi2_frame.tSearchData.tClosedList.ptHead = (struct AIGraphAStarSearchNode_s *)&igi2_frame.tSearchData.tClosedList.ptMiddle;
  igi2_frame.tSearchData.tOpenList.ptTail = (struct AIGraphAStarSearchNode_s *)&igi2_frame.tSearchData;
  nMaxNodes = ptAIGraph->tGraph.nMaxNodes;
  igi2_frame.tSearchData.tCurrentPath.ptHead = (struct AIGraphAStarSearchNode_s *)&igi2_frame.tSearchData.tCurrentPath.ptMiddle;
  v3 = 0;
  igi2_frame.fpFile = nullptr;
  igi2_frame.tSearchData.bFlags = 0;
  memset(&igi2_frame.tSearchData.nGraphId, 255, 12);
  igi2_frame.tSearchData.tClosedList.ptMiddle = nullptr;
  igi2_frame.tSearchData.tCurrentPath.ptMiddle = nullptr;
  igi2_frame.tSearchData.tOpenList.ptHead = (struct AIGraphAStarSearchNode_s *)&igi2_frame.tSearchData.tOpenList.ptMiddle;
  igi2_frame.tSearchData.tOpenList.ptMiddle = nullptr;
  igi2_frame.iI0 = 0;
  if ( nMaxNodes > 0 )
  {
    do
    {
      pxGraphNodeList = (char *)ptAIGraph->tGraph.pxGraphNodeList;
      if ( !pxGraphNodeList || v3 >= nMaxNodes || v3 < 0 )
        goto LABEL_18;
      for ( i = 0; ; ++i )
      {
        if ( i >= 4 )
        {
LABEL_39:
          LDebug_Error("Undefined GraphNodeDataSize");
          abort();
        }
        if ( ptAIGraph->tGraph.tQTask.eQTaskType == Graph_atGraphNodeDataSize[i].eGraphQTaskType )
          break;
      }
      v12 = v3 * Graph_atGraphNodeDataSize[i].nDataSize;
      v13 = *(_DWORD *)&pxGraphNodeList[v12];
      v14 = &pxGraphNodeList[v12];
      if ( v13 != -1 )
      {
        if ( (AIGraph_bViewNodeCriteria & *((_DWORD *)v14 + 14)) != 0 )
        {
          igi2_frame.aiPathCount[v3] = -1;
        }
        else
        {
          for ( j = v3 + 1; j < nMaxNodes; ++j )
          {
            v16 = (char *)ptAIGraph->tGraph.pxGraphNodeList;
            if ( !v16 || j >= nMaxNodes || j < 0 )
              goto LABEL_30;
            for ( k = 0; ; ++k )
            {
              if ( k >= 4 )
                goto LABEL_39;
              if ( ptAIGraph->tGraph.tQTask.eQTaskType == Graph_atGraphNodeDataSize[k].eGraphQTaskType )
                break;
            }
            v18 = j * Graph_atGraphNodeDataSize[k].nDataSize;
            v19 = *(_DWORD *)&v16[v18];
            v20 = &v16[v18];
            if ( v19 != -1 )
            {
              if ( (AIGraph_bViewNodeCriteria & *((_DWORD *)v20 + 14)) != 0 )
              {
                igi2_frame.aiPathCount[j] = -1;
              }
              else
              {
                AIGraphAStarSearch_Clear(&igi2_frame.tSearchData);
                igi2_frame.fpFile = (struct _iobuf *)((char *)igi2_frame.fpFile + 1);
                if ( AIGraphAStarSearch_CreatePath(&igi2_frame.tSearchData, ptAIGraph->tGraph.nGraphID, igi2_frame.iI0, j, 0xFFFFFFFF) )
                {
                  ++igi2_frame.aiPathCount[igi2_frame.iI0];
                  ++igi2_frame.aiPathCount[j];
                }
                v3 = igi2_frame.iI0;
              }
            }
            else
            {
LABEL_30:
              igi2_frame.aiPathCount[j] = -1;
            }
            nMaxNodes = ptAIGraph->tGraph.nMaxNodes;
          }
        }
      }
      else
      {
LABEL_18:
        igi2_frame.aiPathCount[v3] = -1;
      }
      nMaxNodes = ptAIGraph->tGraph.nMaxNodes;
      igi2_frame.iI0 = ++v3;
    }
    while ( v3 < nMaxNodes );
  }
  AIGraphAStarSearch_Clear(&igi2_frame.tSearchData);
  sprintf(igi2_frame.acFileName, "GraphConnectivity%i.txt", ptAIGraph->tGraph.nGraphID);
  v4 = fopen(igi2_frame.acFileName, "wt");
  igi2_frame.fpFilea = v4;
  if ( v4 )
  {
    fprintf(v4, (int)&unk_6860B0, ptAIGraph->tGraph.nGraphID);
    v5 = ptAIGraph->tGraph.nMaxNodes;
    v6 = 0;
    memset(igi2_frame.aiLeastConnected, 0xFFu, sizeof(igi2_frame.aiLeastConnected));
    if ( v5 > 0 )
    {
      do
      {
        v7 = igi2_frame.aiPathCount[v6];
        if ( v7 != -1 )
        {
          v8 = 0;
          while ( 1 )
          {
            v9 = igi2_frame.aiLeastConnected[v8];
            if ( v9 == -1 || igi2_frame.aiPathCount[v9] > v7 )
              break;
            if ( ++v8 >= 10 )
              goto LABEL_41;
          }
          igi2_frame.aiLeastConnected[v8] = v6;
        }
LABEL_41:
        ++v6;
      }
      while ( v6 < v5 );
    }
    for ( m = 0; m < 10; ++m )
    {
      v22 = igi2_frame.aiLeastConnected[m];
      if ( v22 != -1 )
        fprintf(igi2_frame.fpFilea, (int)&unk_6860A4, v22);
    }
    fclose(igi2_frame.fpFilea);
  }
}

// source: i/0/aigraph.c:3061  [anchor-callee]
void __cdecl AIGraph_DropNodesToGround(struct AIGraph_t *ptAIGraph)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct real64x3_t atStart[2]; };
    struct { char igi2_o1[52]; struct AIGraphCollisionEvaluateContext_t tContext; };
    struct { char igi2_o2[64]; struct real64x3_t atEnd[2]; };
    struct { char igi2_o3[112]; struct QIntersection_s atIntersection[2]; };
    char igi2_extent[352];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int nMaxNodes; // eax
  int v2; // ebx
  struct GraphNode_s *v3; // eax
  __int16 v4; // ax
  double v5; // st7
  double v6; // st6
  struct AIGraph_t *v7; // esi
  int v8; // edi
  struct real64x3_t *p_tPos; // ecx

  nMaxNodes = ptAIGraph->tGraph.nMaxNodes;
  v2 = 0;
  igi2_frame.tContext.tCollisionEvaluateContext.ptQTask = &ptAIGraph->tGraph.tQTask;
  for ( igi2_frame.tContext.isIgnoreDoor = 1; v2 < nMaxNodes; ++v2 )
  {
    if ( !ptAIGraph->tGraph.pxGraphNodeList )
      goto LABEL_21;
    if ( v2 >= nMaxNodes )
      goto LABEL_21;
    if ( v2 < 0 )
      goto LABEL_21;
    v3 = (struct GraphNode_s *)((char *)ptAIGraph->tGraph.pxGraphNodeList
                              + v2 * Graph_GetGraphNodeDataSize((int)ptAIGraph));
    if ( v3->nID == -1 )
      goto LABEL_21;
    Graph_GetNodePos(igi2_frame.atStart, v3);
    v4 = AIGraph_eNodeLinkCheckQTaskEvent;
    igi2_frame.atStart[0].vZ = igi2_frame.atStart[0].vZ + 409.6000061035156;
    qmemcpy(igi2_frame.atEnd, igi2_frame.atStart, 0x18u);
    igi2_frame.atEnd[0].vZ = igi2_frame.atStart[0].vZ - 409600.0;
    qmemcpy(&igi2_frame.atStart[1], igi2_frame.atStart, sizeof(struct real64x3_t));
    qmemcpy(&igi2_frame.atEnd[1], igi2_frame.atStart, sizeof(struct real64x3_t));
    igi2_frame.atEnd[1].vZ = igi2_frame.atStart[0].vZ + 409600.0;
    if ( AIGraph_eNodeLinkCheckQTaskEvent == 512 )
    {
      v4 = QTask_NewQTaskEventFn(0, "AIGraph_NodeLinkCheck");
      AIGraph_eNodeLinkCheckQTaskEvent = v4;
    }
    World_TraceLines(
      World_ptActiveWorld,
      igi2_frame.atIntersection,
      igi2_frame.atStart,
      igi2_frame.atEnd,
      2,
      v4,
      &igi2_frame.tContext.tCollisionEvaluateContext,
      0x98000000);
    if ( igi2_frame.atIntersection[0].isHit )
    {
      if ( igi2_frame.atIntersection[1].isHit )
      {
        v5 = igi2_frame.atIntersection[0].tPos.vZ - igi2_frame.atStart[0].vZ;
        if ( igi2_frame.atIntersection[0].tPos.vZ - igi2_frame.atStart[0].vZ < 0.0 )
          v5 = -v5;
        v6 = igi2_frame.atIntersection[1].tPos.vZ - igi2_frame.atStart[1].vZ;
        if ( igi2_frame.atIntersection[1].tPos.vZ - igi2_frame.atStart[1].vZ < 0.0 )
          v6 = -v6;
        v7 = ptAIGraph;
        v8 = v2;
        if ( v5 < v6 )
        {
          p_tPos = &igi2_frame.atIntersection[0].tPos;
LABEL_20:
          Graph_UpdateNodePos(&v7->tGraph, v8, p_tPos);
          goto LABEL_21;
        }
        Graph_UpdateNodePos(&ptAIGraph->tGraph, v2, &igi2_frame.atIntersection[1].tPos);
      }
      else
      {
        Graph_UpdateNodePos(&ptAIGraph->tGraph, v2, &igi2_frame.atIntersection[0].tPos);
      }
    }
    else if ( igi2_frame.atIntersection[1].isHit )
    {
      p_tPos = &igi2_frame.atIntersection[1].tPos;
      v8 = v2;
      v7 = ptAIGraph;
      goto LABEL_20;
    }
LABEL_21:
    nMaxNodes = ptAIGraph->tGraph.nMaxNodes;
  }
}
