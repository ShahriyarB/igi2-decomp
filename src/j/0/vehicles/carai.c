/* j/0/vehicles/carai.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/vehicles/carai.c:178  [anchor-callee]
void __cdecl CarAI_FindWantedThrust(
        float *pvWantedThrust,
        float *pvWantedBreak,
        struct CarAI_s *ptCarAI)
{
  struct Car_s *ptCar; // eax
  double v4; // st7
  double v5; // st6

  ptCar = ptCarAI->ptCar;
  v4 = ptCarAI->vWantedSpeed
     - (ptCar->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tZ.vY
      * ptCar->tVehicle.tPhysicsObj.tPhysics.tCMVel.vZ
      + ptCar->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tY.vY
      * ptCar->tVehicle.tPhysicsObj.tPhysics.tCMVel.vY
      + ptCar->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tX.vY
      * ptCar->tVehicle.tPhysicsObj.tPhysics.tCMVel.vX)
     * 0.0263671875;
  v5 = ptCar->tVehicle.vRealThrust + v4 * 0.009999999776482582;
  *pvWantedThrust = v5;
  if ( v5 >= 0.0 )
  {
    if ( v5 > 1.0 )
      *pvWantedThrust = 1.0;
  }
  else
  {
    *pvWantedThrust = 0.0;
  }
  if ( ptCarAI->vTargetBreak == 0.0 && v4 >= -3.0 )
    *pvWantedBreak = 0.0;
  else
    *pvWantedBreak = 1.0;
}

// source: j/0/vehicles/carai.c:241  [anchor-hash]
int __cdecl CarAI_IsStopCommand(enum PatrolPath_Command_e eCommand)
{
  return eCommand == PATROLPATH_COMMAND_QUIT || eCommand == PATROLPATH_COMMAND_END;
}

// source: j/0/vehicles/carai.c:255  [anchor-caller]
enum bool __cdecl CarAI_MakePath(struct CarAI_s *ptCarAI, int nEndNode)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct real64x3_t ptAIGraphNode; };
    struct { char igi2_o1[24]; double v12; };
    struct { char igi2_o2[32]; struct real32x3_t tE0Dest; };
    struct { char igi2_o3[48]; struct real64x3_t tDestPos; };
    struct { char igi2_o4[72]; struct real64x3_t tE1Pos; };
    char igi2_extent[96];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int nCurrentEdgeNode0; // ebx
  struct AIGraph_t *ptAIGraph; // esi
  struct AIGraphAStarSearchNode_s *ptHead; // eax
  struct GraphNode_s *Node; // ebp
  struct GraphNode_s *v6; // ebx
  struct GraphNode_s *v7; // esi
  double vY; // st6
  double vX; // st5

  nCurrentEdgeNode0 = ptCarAI->tPathData.nCurrentEdgeNode0;
  if ( nCurrentEdgeNode0 == -1 )
  {
    AIGraph_GetClosestNode(
      (struct AIGraphNode_s **)&igi2_frame.ptAIGraphNode,
      ptCarAI->ptAIGraph,
      &ptCarAI->ptCar->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos,
      false);
    nCurrentEdgeNode0 = *(_DWORD *)LODWORD(igi2_frame.ptAIGraphNode.vX);
  }
  ptAIGraph = ptCarAI->ptAIGraph;
  if ( ptCarAI->tPathData.tSearchData.nGraphId == ptAIGraph->tGraph.nGraphID
    && ptCarAI->tPathData.tSearchData.nSourceNodeId == ptCarAI->tPathData.nCurrentStartNode
    && ptCarAI->tPathData.tSearchData.nDestNodeId == nEndNode )
  {
    ptHead = ptCarAI->tPathData.tSearchData.tCurrentPath.ptHead;
    if ( ptHead->ptNext )
    {
      if ( ptHead && ptCarAI != (struct CarAI_s *)-1044 )
        return true;
    }
  }
  if ( ptCarAI->tPathData.nCurrentEdgeNode0 != -1 )
  {
    Node = Graph_GetNode(&ptAIGraph->tGraph, nEndNode);
    v6 = Graph_GetNode(&ptCarAI->ptAIGraph->tGraph, ptCarAI->tPathData.nCurrentEdgeNode0);
    v7 = Graph_GetNode(&ptCarAI->ptAIGraph->tGraph, ptCarAI->tPathData.nCurrentEdgeNode1);
    Graph_GetNodePos(&igi2_frame.tDestPos, Node);
    Graph_GetNodePos(&igi2_frame.ptAIGraphNode, v6);
    Graph_GetNodePos(&igi2_frame.tE1Pos, v7);
    igi2_frame.tE0Dest.vX = igi2_frame.tDestPos.vX - igi2_frame.ptAIGraphNode.vX;
    igi2_frame.tE0Dest.vY = igi2_frame.tDestPos.vY - igi2_frame.ptAIGraphNode.vY;
    *(float *)&igi2_frame.ptAIGraphNode.vX = igi2_frame.tDestPos.vX - igi2_frame.tE1Pos.vX;
    *((float *)&igi2_frame.ptAIGraphNode.vX + 1) = igi2_frame.tDestPos.vY - igi2_frame.tE1Pos.vY;
    *(float *)&igi2_frame.ptAIGraphNode.vY = igi2_frame.tDestPos.vZ - igi2_frame.tE1Pos.vZ;
    vY = igi2_frame.tE0Dest.vY;
    vX = igi2_frame.tE0Dest.vX;
    *(double *)&igi2_frame.tE0Dest.vX = *(float *)&igi2_frame.ptAIGraphNode.vY;
    igi2_frame.v12 = *((float *)&igi2_frame.ptAIGraphNode.vX + 1);
    igi2_frame.ptAIGraphNode.vX = *(float *)&igi2_frame.ptAIGraphNode.vX;
    if ( sqrt(igi2_frame.ptAIGraphNode.vX * igi2_frame.ptAIGraphNode.vX + igi2_frame.v12 * igi2_frame.v12 + *(float *)&igi2_frame.ptAIGraphNode.vY
                                                              * *(float *)&igi2_frame.ptAIGraphNode.vY) <= sqrt(
                                                                                                  vX * vX
                                                                                                + vY * vY
                                                                                                + (igi2_frame.tDestPos.vZ
                                                                                                 - igi2_frame.ptAIGraphNode.vZ)
                                                                                                * (igi2_frame.tDestPos.vZ
                                                                                                 - igi2_frame.ptAIGraphNode.vZ)) )
      nCurrentEdgeNode0 = v7->nID;
    else
      nCurrentEdgeNode0 = v6->nID;
  }
  if ( AIGraphAStarSearch_CreatePath(
         &ptCarAI->tPathData.tSearchData,
         ptCarAI->ptAIGraph->tGraph.nGraphID,
         nCurrentEdgeNode0,
         nEndNode,
         0xFFFFFFFF) )
  {
    ptCarAI->tPathData.nCurrentStartNode = nCurrentEdgeNode0;
    ptCarAI->tPathData.nCurrentPathIndex = 0;
    ptCarAI->tPathData.nCurrentEdgeNode0 = nCurrentEdgeNode0;
    ptCarAI->tPathData.nCurrentEdgeNode1 = nCurrentEdgeNode0;
    ptCarAI->tPathData.nCurrentDestNode = nEndNode;
    return true;
  }
  return false;
}

// source: j/0/vehicles/carai.c:343  [anchor-caller]
struct real64x3_t *__cdecl CarAI_GetPosFromPath(
        struct real64x3_t *retstr,
        struct CarAI_s *ptCarAI,
        struct real64x3_t *ptCurrentPos)
{
  struct AIGraph_t *ptAIGraph; // ebp
  struct AIGraphAStarSearchNode_s *ptHead; // eax
  struct AIGraphAStarSearchNode_s *v7; // esi
  int i; // ecx
  int nNodeId; // ebx
  int GraphNodeDataSize; // eax
  struct GraphNode_s *v11; // eax
  int nCurrentPathIndex; // edx
  struct AIGraphAStarSearchNode_s *v13; // eax
  struct real64x3_t tNodePos; // [esp+10h] [ebp-1Ch] BYREF

  ptAIGraph = ptCarAI->ptAIGraph;
  if ( ptCarAI->tPathData.tSearchData.nGraphId == ptAIGraph->tGraph.nGraphID
    && ptCarAI->tPathData.tSearchData.nSourceNodeId == ptCarAI->tPathData.nCurrentStartNode
    && ptCarAI->tPathData.tSearchData.nDestNodeId == ptCarAI->tPathData.nCurrentDestNode )
  {
    ptHead = ptCarAI->tPathData.tSearchData.tCurrentPath.ptHead;
    if ( ptHead->ptNext )
    {
      if ( ptHead && ptCarAI != (struct CarAI_s *)-1044 )
      {
        v7 = ptCarAI->tPathData.tSearchData.tCurrentPath.ptHead->ptNext != nullptr
           ? ptCarAI->tPathData.tSearchData.tCurrentPath.ptHead
           : nullptr;
        for ( i = 0; i < ptCarAI->tPathData.nCurrentPathIndex; ++i )
        {
          if ( !v7->ptNext->ptNext )
            break;
          if ( !v7->ptNext )
            break;
          v7 = v7->ptNext;
        }
        nNodeId = v7->nNodeId;
        if ( ptAIGraph->tGraph.pxGraphNodeList && nNodeId < ptAIGraph->tGraph.nMaxNodes && nNodeId >= 0 )
        {
          GraphNodeDataSize = Graph_GetGraphNodeDataSize((int)ptAIGraph);
          v11 = *(_DWORD *)((char *)ptAIGraph->tGraph.pxGraphNodeList + nNodeId * GraphNodeDataSize) == -1
              ? nullptr
              : (struct GraphNode_s *)((char *)ptAIGraph->tGraph.pxGraphNodeList + nNodeId * GraphNodeDataSize);
        }
        else
        {
          v11 = nullptr;
        }
        Graph_GetNodePos(&tNodePos, v11);
        if ( CarAI_IsOnNode(ptCarAI, v7->nNodeId) )
        {
          nCurrentPathIndex = ptCarAI->tPathData.nCurrentPathIndex;
          if ( nCurrentPathIndex < List_Length(&ptCarAI->tPathData.tSearchData.tCurrentPath) )
          {
            v13 = v7->ptNext->ptNext != nullptr ? v7->ptNext : nullptr;
            ptCarAI->tPathData.nCurrentEdgeNode0 = v7->nNodeId;
            if ( v13 )
              ptCarAI->tPathData.nCurrentEdgeNode1 = v13->nNodeId;
            else
              ptCarAI->tPathData.nCurrentEdgeNode1 = v7->nNodeId;
            ptCarAI->tPathData.nCurrentPathIndex = nCurrentPathIndex + 1;
          }
        }
        ptCurrentPos = &tNodePos;
      }
    }
  }
  qmemcpy(retstr, ptCurrentPos, sizeof(struct real64x3_t));
  return retstr;
}

// source: j/0/vehicles/carai.c:431  [anchor-callee]
float __cdecl CarAI_FindWantedSpeedPatrol(struct CarAI_s *ptCarAI)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct real64x3_t v10; };
    struct { char igi2_o1[40]; struct real64x3_t tCarTargetPos; };
    struct { char igi2_o2[64]; struct real64x3_t tDeltaTargetNextNode; };
    struct { char igi2_o3[88]; struct real64x3_t tDeltaCarTarget; };
    char igi2_extent[112];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct real64x3_t *p_tPos; // ebx
  double v2; // st7
  double v3; // st6
  double v4; // st5
  float *ptCar; // eax
  double v6; // st4
  double v7; // st7

  p_tPos = &ptCarAI->ptCar->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos;
  qmemcpy(&igi2_frame.tCarTargetPos, CarAI_GetPosFromPath(&igi2_frame.tDeltaCarTarget, ptCarAI, p_tPos), sizeof(igi2_frame.tCarTargetPos));
  v2 = igi2_frame.tCarTargetPos.vX - p_tPos->vX;
  igi2_frame.tDeltaCarTarget.vX = v2;
  v3 = igi2_frame.tCarTargetPos.vY - p_tPos->vY;
  igi2_frame.tDeltaCarTarget.vY = v3;
  v4 = igi2_frame.tCarTargetPos.vZ - p_tPos->vZ;
  igi2_frame.tDeltaCarTarget.vZ = v4;
  if ( v3 * v3 + v4 * v4 + v2 * v2 <= 1677721600.0 )
  {
    qmemcpy(
      &igi2_frame.tCarTargetPos,
      CarAI_GetPosFromPath(
        &igi2_frame.tDeltaTargetNextNode,
        ptCarAI,
        &ptCarAI->ptCar->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos),
      sizeof(igi2_frame.tCarTargetPos));
    igi2_frame.tDeltaTargetNextNode.vX = igi2_frame.tCarTargetPos.vX - p_tPos->vX;
    igi2_frame.tDeltaTargetNextNode.vY = igi2_frame.tCarTargetPos.vY - p_tPos->vY;
    igi2_frame.tDeltaTargetNextNode.vZ = igi2_frame.tCarTargetPos.vZ - p_tPos->vZ;
    v7 = Real64x3_Angle(&igi2_frame.tDeltaCarTarget, &igi2_frame.tDeltaTargetNextNode);
    if ( ptCarAI->vTargetSpeed < 5.0 )
      return ptCarAI->vTargetSpeed;
  }
  else
  {
    ptCar = (float *)ptCarAI->ptCar;
    v6 = ptCar[37];
    ptCar += 31;
    igi2_frame.tCarTargetPos.vX = v6 * v4 + ptCar[3] * v3 + *ptCar * v2;
    igi2_frame.tCarTargetPos.vY = ptCar[7] * v4 + ptCar[4] * v3 + ptCar[1] * v2;
    igi2_frame.tCarTargetPos.vZ = ptCar[8] * v4 + ptCar[5] * v3 + ptCar[2] * v2;
    qmemcpy(&igi2_frame.v10, &igi2_frame.tCarTargetPos, sizeof(igi2_frame.v10));
    v7 = GameFunctions_CalcGamma(igi2_frame.v10);
    if ( v7 < 0.0 )
      v7 = -v7;
    if ( v7 >= 1.5707963705062866 )
      v7 = 1.5707963705062866;
  }
  return (1.5707963705062866 - v7) * 0.6366197546520227 * (ptCarAI->vTargetSpeed - 5.0) + 5.0;
}

// source: j/0/vehicles/carai.c:548  [anchor-callee]
float __cdecl CarAI_FindWantedSpeedCombat(struct CarAI_s *ptCarAI)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct real64x3_t v11; };
    struct { char igi2_o1[40]; struct real64x3_t tCarTargetPos; };
    struct { char igi2_o2[64]; struct real64x3_t tDeltaTargetNextNode; };
    struct { char igi2_o3[88]; struct real64x3_t tDeltaCarTarget; };
    char igi2_extent[112];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct real64x3_t *p_tPos; // ebx
  double v2; // st7
  double v3; // st6
  double v4; // st5
  float *ptCar; // eax
  double v6; // st4
  double v7; // st7
  double v9; // st7

  p_tPos = &ptCarAI->ptCar->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos;
  qmemcpy(&igi2_frame.tCarTargetPos, CarAI_GetPosFromPath(&igi2_frame.tDeltaCarTarget, ptCarAI, p_tPos), sizeof(igi2_frame.tCarTargetPos));
  v2 = igi2_frame.tCarTargetPos.vX - p_tPos->vX;
  igi2_frame.tDeltaCarTarget.vX = v2;
  v3 = igi2_frame.tCarTargetPos.vY - p_tPos->vY;
  igi2_frame.tDeltaCarTarget.vY = v3;
  v4 = igi2_frame.tCarTargetPos.vZ - p_tPos->vZ;
  igi2_frame.tDeltaCarTarget.vZ = v4;
  if ( v3 * v3 + v4 * v4 + v2 * v2 <= 6710886400.0 )
  {
    qmemcpy(
      &igi2_frame.tCarTargetPos,
      CarAI_GetPosFromPath(
        &igi2_frame.tDeltaTargetNextNode,
        ptCarAI,
        &ptCarAI->ptCar->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos),
      sizeof(igi2_frame.tCarTargetPos));
    igi2_frame.tDeltaTargetNextNode.vX = igi2_frame.tCarTargetPos.vX - p_tPos->vX;
    igi2_frame.tDeltaTargetNextNode.vY = igi2_frame.tCarTargetPos.vY - p_tPos->vY;
    igi2_frame.tDeltaTargetNextNode.vZ = igi2_frame.tCarTargetPos.vZ - p_tPos->vZ;
    v9 = Real64x3_Angle(&igi2_frame.tDeltaCarTarget, &igi2_frame.tDeltaTargetNextNode);
    if ( ptCarAI->vTargetSpeed >= 5.0 )
    {
      if ( v9 >= 0.17453293005625406 )
        return 5.0;
      else
        return (1.3962634354829788 - v9) * 0.7161972265313185 * (ptCarAI->vTargetSpeed - 5.0) + 5.0;
    }
    else
    {
      return ptCarAI->vTargetSpeed;
    }
  }
  else
  {
    ptCar = (float *)ptCarAI->ptCar;
    v6 = ptCar[37];
    ptCar += 31;
    igi2_frame.tCarTargetPos.vX = v6 * v4 + ptCar[3] * v3 + *ptCar * v2;
    igi2_frame.tCarTargetPos.vY = ptCar[7] * v4 + ptCar[4] * v3 + ptCar[1] * v2;
    igi2_frame.tCarTargetPos.vZ = ptCar[8] * v4 + ptCar[5] * v3 + ptCar[2] * v2;
    qmemcpy(&igi2_frame.v11, &igi2_frame.tCarTargetPos, sizeof(igi2_frame.v11));
    v7 = GameFunctions_CalcGamma(igi2_frame.v11);
    if ( v7 < 0.0 )
      v7 = -v7;
    if ( v7 >= 1.5707963705062866 )
      v7 = 1.5707963705062866;
    return (1.5707963705062866 - v7) * 0.6366197546520227 * (ptCarAI->vTargetSpeed - 5.0) + 5.0;
  }
}

// source: j/0/vehicles/carai.c:641  [size]
struct real64x3_t *__cdecl CarAI_GetCarPos(struct CarAI_s *ptCarAI)
{
  return &ptCarAI->ptCar->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos;
}

// source: j/0/vehicles/carai.c:655  [anchor-callee]
int __cdecl CarAI_IsCombat(struct CarAI_s *ptCarAI)
{
  struct Car_s *ptCar; // eax
  struct QTask_s *ptDetectedHuman; // ecx
  struct AIDetectionListItem_s *ptHead; // ecx
  struct AIDetectionListItem_s *ptNext; // edx
  int v6; // eax
  int nDetectionCountdown; // eax

  ptCar = ptCarAI->ptCar;
  if ( !ptCar )
    return 0;
  if ( !ptCar->isFire
    || (ptDetectedHuman = ptCarAI->ptDetectedHuman) != nullptr && LOBYTE(ptDetectedHuman[29].tQTaskRefList.ptHead) )
  {
    ptCarAI->ptDetectedHuman = nullptr;
    ptCarAI->nDetectionCountdown = 0;
    return 0;
  }
  if ( ptCar->ptWeaponHitTask )
  {
    ptCarAI->nDetectionCountdown = 600;
    ptCarAI->ptDetectedHuman = ptCar->ptWeaponHitTask;
    return 1;
  }
  else
  {
    ptHead = ptCar->tAIDetection.tEnemyList.ptHead;
    ptNext = ptHead->ptNext;
    if ( ptHead->ptNext )
    {
      while ( 2 )
      {
        v6 = 0;
        while ( !ptHead->aisFullVisible[v6] )
        {
          if ( ++v6 >= 3 )
            goto LABEL_15;
        }
        if ( ptHead->ptQTaskRef->pxObject )
        {
          ptCarAI->nDetectionCountdown = 600;
          ptCarAI->ptDetectedHuman = (struct QTask_s *)ptHead->ptQTaskRef->pxObject;
          return 1;
        }
LABEL_15:
        ptHead = ptNext;
        ptNext = ptNext->ptNext;
        if ( ptNext )
          continue;
        break;
      }
    }
    nDetectionCountdown = ptCarAI->nDetectionCountdown;
    if ( nDetectionCountdown )
    {
      ptCarAI->nDetectionCountdown = nDetectionCountdown - 1;
      return 1;
    }
    else
    {
      ptCarAI->ptDetectedHuman = nullptr;
      return 0;
    }
  }
}

// source: j/0/vehicles/carai.c:732  [anchor-callee]
int __cdecl CarAI_IsOnNode(struct CarAI_s *ptCarAI, int nNode)
{
  #pragma pack(push, 1)
  union
  {
    struct { float tDelta; };
    struct { char igi2_o1[4]; float tDelta_4; };
    struct { char igi2_o2[12]; struct real64x3_t tPos; };
    char igi2_extent[40];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct AIGraph_t *ptAIGraph; // edi
  struct GraphNode_s *v4; // eax
  double *ptCar; // eax
  double v6; // st7
  double v7; // st7
  float *v9; // eax
  double v10; // st6
  double v11; // st7

  ptAIGraph = ptCarAI->ptAIGraph;
  if ( ptAIGraph->tGraph.pxGraphNodeList )
  {
    if ( nNode < ptAIGraph->tGraph.nMaxNodes && nNode >= 0 )
    {
      v4 = (struct GraphNode_s *)((char *)ptAIGraph->tGraph.pxGraphNodeList
                                + nNode * Graph_GetGraphNodeDataSize((int)ptAIGraph));
      if ( v4->nID != -1 )
      {
        Graph_GetNodePos(&igi2_frame.tPos, v4);
        ptCar = (double *)ptCarAI->ptCar;
        v6 = igi2_frame.tPos.vX - ptCar[5];
        ptCar += 5;
        igi2_frame.tDelta = v6;
        igi2_frame.tDelta_4 = igi2_frame.tPos.vY - ptCar[1];
        v7 = igi2_frame.tPos.vZ - ptCar[2];
        if ( CarAI_IsCombat(ptCarAI) )
        {
          if ( sqrt(igi2_frame.tDelta * igi2_frame.tDelta + igi2_frame.tDelta_4 * igi2_frame.tDelta_4 + v7 * v7) < 12288.0 )
            return 1;
        }
        else
        {
          v9 = (float *)ptCarAI->ptCar;
          v10 = v7 * v9[37];
          v9 += 31;
          *(float *)&igi2_frame.tPos.vX = v10 + igi2_frame.tDelta_4 * v9[3] + igi2_frame.tDelta * *v9;
          v11 = v7 * v9[7] + igi2_frame.tDelta_4 * v9[4] + igi2_frame.tDelta * v9[1];
          if ( v11 < 12288.0 && v11 > -12288.0 && *(float *)&igi2_frame.tPos.vX < 32768.0 && *(float *)&igi2_frame.tPos.vX > -32768.0 )
            return 1;
        }
      }
    }
  }
  return 0;
}

// source: j/0/vehicles/carai.c:781  [anchor-callee]
void __cdecl CarAI_UpdateAIStatePatrol(struct CarAI_s *ptCarAI)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct real64x3_t v7; };
    struct { char igi2_o1[40]; struct real64x3_t tCarTargetPos; };
    struct { char igi2_o2[64]; struct real64x3_t v9; };
    char igi2_extent[88];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct Car_s *ptCar; // ebx
  double v3; // st7
  double v4; // st6
  double v5; // st5
  double v6; // st7
  float ptCarAIa = *(float *)&ptCarAI; // [esp+44h] [ebp+4h] ARGSLOT

  ptCarAI->vWantedSpeed = CarAI_FindWantedSpeedPatrol(ptCarAI);
  CarAI_FindWantedThrust(&ptCarAI->vWantedThrust, &ptCarAI->vWantedBreak, ptCarAI);
  ptCar = ptCarAI->ptCar;
  qmemcpy(
    &igi2_frame.tCarTargetPos,
    CarAI_GetPosFromPath(&igi2_frame.v9, ptCarAI, &ptCar->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos),
    sizeof(igi2_frame.tCarTargetPos));
  v3 = igi2_frame.tCarTargetPos.vX - ptCar->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos.vX;
  v4 = igi2_frame.tCarTargetPos.vY - ptCar->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos.vY;
  v5 = igi2_frame.tCarTargetPos.vZ - ptCar->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos.vZ;
  igi2_frame.tCarTargetPos.vX = ptCar->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tZ.vX * v5
                   + ptCar->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tY.vX * v4
                   + ptCar->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tX.vX * v3;
  igi2_frame.tCarTargetPos.vY = ptCar->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tZ.vY * v5
                   + ptCar->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tY.vY * v4
                   + ptCar->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tX.vY * v3;
  igi2_frame.tCarTargetPos.vZ = ptCar->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tZ.vZ * v5
                   + ptCar->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tY.vZ * v4
                   + ptCar->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tX.vZ * v3;
  qmemcpy(&igi2_frame.v7, &igi2_frame.tCarTargetPos, sizeof(igi2_frame.v7));
  v6 = GameFunctions_CalcGamma(igi2_frame.v7);
  ptCarAIa = v6;
  if ( v6 <= 0.1745329350233078 )
  {
    if ( ptCarAIa >= -0.1745329350233078 )
      ptCarAI->vWantedGamma = ptCarAIa * -1.909859299659729;
    else
      ptCarAI->vWantedGamma = 1.0;
  }
  else
  {
    ptCarAI->vWantedGamma = -1.0;
  }
  ptCarAI->vWantedGamma = ((1.0 - ptCarAI->vWantedThrust) * 0.800000011920929 + 0.20000000298023224) * ptCarAI->vWantedGamma;
}

// source: j/0/vehicles/carai.c:838  [anchor-callee]
void __cdecl CarAI_UpdateAIStateCombat(struct CarAI_s *ptCarAI)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct real64x3_t v14; };
    struct { char igi2_o1[44]; int isAimAtTarget; };
    struct { char igi2_o2[48]; struct real64x3_t tCarTargetPos; };
    struct { char igi2_o3[72]; struct real64x3_t v17; };
    char igi2_extent[96];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct real64x3_t *PosFromPath; // eax
  int v3; // edx
  double v4; // st7
  double v5; // st6
  double v6; // st5
  double *ptDetectedHuman; // eax
  double v8; // st7
  double v9; // st7
  double v10; // st7
  double WantedSpeedCombat; // st7
  float *p_vWantedBreak; // esi
  double v13; // st7
  struct Car_s *ptCarAIa = *(struct Car_s * *)&ptCarAI; // [esp+44h] [ebp+4h] ARGSLOT
  float ptCarAIb = *(float *)&ptCarAI; // [esp+44h] [ebp+4h] ARGSLOT

  igi2_frame.isAimAtTarget = ptCarAI->vTargetSpeed == 0.0;
  ptCarAIa = ptCarAI->ptCar;
  PosFromPath = CarAI_GetPosFromPath(
                  &igi2_frame.v17,
                  ptCarAI,
                  &ptCarAIa->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos);
  v3 = igi2_frame.isAimAtTarget;
  qmemcpy(&igi2_frame.tCarTargetPos, PosFromPath, sizeof(igi2_frame.tCarTargetPos));
  v4 = igi2_frame.tCarTargetPos.vX - ptCarAIa->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos.vX;
  v5 = igi2_frame.tCarTargetPos.vY - ptCarAIa->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos.vY;
  v6 = igi2_frame.tCarTargetPos.vZ - ptCarAIa->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos.vZ;
  if ( igi2_frame.isAimAtTarget )
  {
    ptDetectedHuman = (double *)ptCarAI->ptDetectedHuman;
    v4 = ptDetectedHuman[5] - ptCarAIa->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos.vX;
    v5 = ptDetectedHuman[6] - ptCarAIa->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos.vY;
    v6 = ptDetectedHuman[7] - ptCarAIa->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tPos.vZ;
  }
  igi2_frame.tCarTargetPos.vX = ptCarAIa->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tZ.vX * v6
                   + ptCarAIa->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tY.vX * v5
                   + ptCarAIa->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tX.vX * v4;
  igi2_frame.tCarTargetPos.vY = ptCarAIa->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tZ.vY * v6
                   + ptCarAIa->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tY.vY * v5
                   + ptCarAIa->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tX.vY * v4;
  igi2_frame.tCarTargetPos.vZ = ptCarAIa->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tZ.vZ * v6
                   + ptCarAIa->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tY.vZ * v5
                   + ptCarAIa->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tOrientation.tX.vZ * v4;
  qmemcpy(&igi2_frame.v14, &igi2_frame.tCarTargetPos, sizeof(igi2_frame.v14));
  v8 = GameFunctions_CalcGamma(igi2_frame.v14);
  ptCarAIb = v8;
  if ( v8 <= 0.1745329350233078 )
  {
    if ( ptCarAIb >= -0.1745329350233078 )
      ptCarAI->vWantedGamma = ptCarAIb * -1.909859299659729;
    else
      ptCarAI->vWantedGamma = 1.0;
  }
  else
  {
    ptCarAI->vWantedGamma = -1.0;
  }
  if ( !v3 )
  {
    WantedSpeedCombat = CarAI_FindWantedSpeedCombat(ptCarAI);
LABEL_17:
    ptCarAI->vWantedSpeed = WantedSpeedCombat;
    goto LABEL_18;
  }
  v9 = ptCarAIb;
  if ( ptCarAIb < 0.0 )
    v9 = -v9;
  if ( v9 <= 0.1745329350233078 )
  {
    v10 = ptCarAIb;
    if ( ptCarAIb < 0.0 )
      v10 = -v10;
    WantedSpeedCombat = v10 * 28.64788818359375;
    goto LABEL_17;
  }
  ptCarAI->vWantedSpeed = 5.0;
LABEL_18:
  p_vWantedBreak = &ptCarAI->vWantedBreak;
  CarAI_FindWantedThrust(&ptCarAI->vWantedThrust, &ptCarAI->vWantedBreak, ptCarAI);
  if ( !igi2_frame.isAimAtTarget )
    goto LABEL_23;
  v13 = ptCarAIb;
  if ( ptCarAIb < 0.0 )
    v13 = -v13;
  if ( v13 > 0.1745329350233078 )
    *p_vWantedBreak = 0.0;
  else
LABEL_23:
    *p_vWantedBreak = ptCarAI->vTargetBreak;
}

// source: j/0/vehicles/carai.c:931  [anchor-callee]
void __cdecl CarAI_UpdateCar(struct CarAI_s *ptCarAI, int nTime, float vThrust, float vGamma, float vBreak)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct UpdateAnimDataContext_s tUpdateAnimDataContext; };
    struct { char igi2_o1[8]; float avChannels[5]; };
    char igi2_extent[28];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  double v5; // st7

  igi2_frame.tUpdateAnimDataContext.pvChannel = igi2_frame.avChannels;
  igi2_frame.avChannels[0] = vGamma;
  igi2_frame.tUpdateAnimDataContext.nTime = nTime;
  igi2_frame.avChannels[1] = vThrust;
  if ( vBreak == 0.0 )
    v5 = -1.0;
  else
    v5 = vBreak;
  igi2_frame.avChannels[3] = v5;
  ((void (__cdecl *)(struct Car_s *, struct UpdateAnimDataContext_s *))QTask_aatQTaskFinalEvent[AnimQTask_eUpdateAnimDataEvent][ptCarAI->ptCar->tVehicle.tPhysicsObj.tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask.eQTaskType].pfHandler)(
    ptCarAI->ptCar,
    &igi2_frame.tUpdateAnimDataContext);
}

// source: j/0/vehicles/carai.c:968  [anchor-mhash]
void __cdecl CarAI_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  BYTE1(ptQTask[19].ptNext) = 1;
  ptQTask[17].ptParent = (struct QTask_s *)-1;
  ptQTask[17].tQTaskRefList.ptMiddle = (struct QReference_s *)-1;
  ptQTask[17].tQTaskRefList.ptTail = (struct QReference_s *)-1;
  ptQTask[18].tQTaskRefList.ptMiddle = (struct QReference_s *)-1;
  ptQTask[18].tQTaskRefList.ptTail = (struct QReference_s *)-1;
  *(_DWORD *)&ptQTask[17].eQTaskType = 0;
  ptQTask[18].ptParent = nullptr;
  *(_DWORD *)&ptQTask[18].eQTaskType = 0;
  ptQTask[18].ptNext = nullptr;
  HIBYTE(ptQTask[19].ptNext) = 0;
  LOBYTE(ptQTask[19].ptNext) = 0;
  BYTE2(ptQTask[19].ptNext) = 0;
  LOBYTE(ptQTask[19].ptPrev) = 0;
  LOBYTE(ptQTask[19].eQTaskType) = 0;
  LOBYTE(ptQTask[21].tQTaskRefList.ptHead) = 0;
  ptQTask[24].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[24].tQTaskChildren.ptTail = nullptr;
  ptQTask[24].tQTaskRefList.ptHead = nullptr;
  ptQTask[24].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[24].tQTaskRefList.ptTail = nullptr;
  *(_DWORD *)&ptQTask[24].eQTaskType = 0;
  ptQTask[25].ptPrev = nullptr;
  ptQTask[25].tQTaskChildren.ptHead = nullptr;
  ptQTask[25].ptNext = nullptr;
  ptQTask[25].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[25].tQTaskChildren.ptTail = nullptr;
  *(_DWORD *)&ptQTask[25].eQTaskType = 0;
  ptQTask[26].tQTaskChildren.ptHead = nullptr;
  ptQTask[25].ptParent = (struct QTask_s *)((char *)ptQTask + 1036);
  ptQTask[26].ptNext = (struct QTask_s *)((char *)ptQTask + 1032);
  ptQTask[25].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[26].tQTaskRefList.ptTail = (struct QReference_s *)-1;
  ptQTask[26].tQTaskRefList.ptHead = (struct QReference_s *)-1;
  ptQTask[26].tQTaskRefList.ptMiddle = (struct QReference_s *)-1;
  ptQTask[26].tQTaskChildren.ptTail = nullptr;
  ptQTask[26].ptParent = nullptr;
  ptQTask[26].ptPrev = (struct QTask_s *)((char *)ptQTask + 1048);
  ptQTask[26].tQTaskChildren.ptMiddle = (struct QTask_s *)((char *)ptQTask + 1044);
  ptQTask[25].tQTaskRefList.ptTail = (struct QReference_s *)&ptQTask[25].tQTaskRefList;
  ptQTask[25].tQTaskRefList.ptHead = (struct QReference_s *)&ptQTask[25].tQTaskRefList.ptMiddle;
  ptQTask[27].ptNext = (struct QTask_s *)-1;
  ptQTask[27].ptPrev = (struct QTask_s *)-1;
  ptQTask[27].tQTaskChildren.ptHead = (struct QTask_s *)-1;
  ptQTask[27].tQTaskChildren.ptMiddle = (struct QTask_s *)-1;
  *(_DWORD *)&ptQTask[26].eQTaskType = 0;
  ptQTask[22].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[22].tQTaskChildren.ptTail = nullptr;
  ptQTask[22].tQTaskRefList.ptHead = nullptr;
  ptQTask[24].tQTaskChildren.ptHead = nullptr;
  QTask_TriggerBaseHandler(ptQTask, CarAI_eQTaskType, 0, nullptr);
}

// source: j/0/vehicles/carai.c:1035  [anchor-mhash]
void __cdecl CarAI_DeleteHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptTail; // eax
  struct QReference_s *ptHead; // eax
  int v3; // eax
  struct QReference_s *v4; // ecx
  void (__cdecl *pfHandler)(struct QTask_s *); // eax

  AIGraphAStarSearch_Clear((struct AIGraphAStarSearchData_s *)&ptQTask[25].tQTaskRefList);
  ptTail = ptQTask[17].tQTaskChildren.ptTail;
  if ( ptTail )
    QReference_Delete((struct QReference_s *)ptTail, &QTask_tQTaskRefPool);
  ptHead = ptQTask[17].tQTaskRefList.ptHead;
  if ( ptHead )
    QReference_Delete(ptHead, &QTask_tQTaskRefPool);
  Level_DeinitLevelExpression((struct LevelExpression_s *)&ptQTask[22].tQTaskChildren.ptMiddle);
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
      goto LABEL_13;
  }
  if ( v3 >= 0 )
  {
    pfHandler = (void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[Level_eRemoveLevelScriptSymbolsEvent][ptQTask->eQTaskType].pfHandler;
    if ( pfHandler )
      pfHandler(ptQTask);
  }
LABEL_13:
  QTask_TriggerBaseHandlerNoContext(ptQTask, CarAI_eQTaskType, 2);
}

// source: j/0/vehicles/carai.c:1062  [anchor-caller]
void __cdecl CarAI_RunHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { enum bool isCombat; };
    struct { char igi2_o1[4]; __int64 v22; };
    char igi2_extent[12];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *v1; // esi
  struct QTask_s *ptHead; // ecx
  int v3; // edx
  struct QTask_s *v4; // eax
  void (__cdecl *pfHandler)(struct QTask_s *); // eax
  int v6; // edx
  struct QReference_s *ptTail; // edx
  enum bool v8; // eax
  bool v9; // zf
  struct QTask_s *ptMiddle; // ecx
  int *v11; // eax
  int *v12; // esi
  struct QTask_s *ptNext; // eax
  int v14; // ebx
  struct QTask_s *ptPrev; // edi
  struct QTask_s *v16; // eax
  struct QTask_s *v17; // eax
  int v18; // ecx
  double v19; // st7
  struct QReference_s *Node; // eax

  v1 = ptQTask;
  ptHead = ptQTask->tQTaskChildren.ptHead;
  if ( ptHead->ptNext && ptHead )
  {
    v3 = QTask_nProtectedQTaskStackOffset;
    do
    {
      if ( ptHead->ptNext )
        v4 = ptHead->ptNext->ptNext != nullptr ? ptHead->ptNext : nullptr;
      else
        v4 = nullptr;
      QTask_atProtectedQTaskStack[v3].ptQTask = v4;
      pfHandler = (void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[1][ptHead->eQTaskType].pfHandler;
      v6 = v3 + 1;
      QTask_nProtectedQTaskStackOffset = v6;
      if ( pfHandler )
      {
        pfHandler(ptHead);
        v6 = QTask_nProtectedQTaskStackOffset;
      }
      ptHead = (struct QTask_s *)dword_849C7DC[v6];
      v3 = v6 - 1;
      QTask_nProtectedQTaskStackOffset = v3;
    }
    while ( ptHead );
  }
  if ( !HIBYTE(ptQTask[19].ptNext) )
  {
    ptTail = ptQTask[17].tQTaskRefList.ptTail;
    if ( ptTail != (struct QReference_s *)-1 )
    {
      PatrolPath_InitPatrolPath((struct PatrolPathControl_t *)&ptQTask[18], (int)ptTail, 0);
      HIBYTE(ptQTask[19].ptNext) = 1;
    }
  }
  v8 = CarAI_IsCombat((struct CarAI_s *)ptQTask);
  v9 = ptQTask[18].ptParent == nullptr;
  igi2_frame.isCombat = v8;
  if ( !v9 && *(_DWORD *)&ptQTask[17].eQTaskType && (v8 || ptQTask[18].ptNext) )
  {
    if ( LOBYTE(ptQTask[19].ptNext) )
      goto LABEL_56;
    ptMiddle = ptQTask[22].tQTaskChildren.ptMiddle;
    if ( ptMiddle
      && (ptMiddle = ptQTask[22].tQTaskChildren.ptTail, LOBYTE(ptMiddle->ptNext))
      && ptQTask[22].tQTaskRefList.ptHead
      && (igi2_frame.v22 = (__int64)Level_RunLevelExpression(
                           (struct LevelExpression_s *)&ptQTask[22].tQTaskChildren.ptMiddle,
                           ptQTask),
          !(_DWORD)igi2_frame.v22) )
    {
      if ( BYTE1(ptQTask[19].ptNext) )
      {
        EditBoneObj_SetAnimation((struct EditBoneObj_s *)ptQTask, (char *)&ptQTask[20].tQTaskRefList.ptTail);
        BYTE1(ptQTask[19].ptNext) = 0;
        goto LABEL_26;
      }
    }
    else if ( !BYTE1(ptQTask[19].ptNext) )
    {
      EditBoneObj_SetAnimation((struct EditBoneObj_s *)ptQTask, (char *)&ptQTask[19].eQTaskType);
      BYTE1(ptQTask[19].ptNext) = 1;
LABEL_26:
      v1 = ptQTask;
    }
    if ( !LOBYTE(v1[19].ptNext) && BYTE1(v1[19].ptNext) )
    {
      if ( igi2_frame.isCombat )
      {
        v11 = (int *)v1[24].tQTaskRefList.ptTail;
        if ( v11 )
        {
          if ( !CarAI_IsOnNode((struct CarAI_s *)ptQTask, *v11) )
          {
            v12 = (int *)ptQTask[24].tQTaskRefList.ptTail;
LABEL_37:
            v14 = *v12;
            v1 = ptQTask;
            if ( CarAI_IsOnNode((struct CarAI_s *)ptQTask, v14) )
            {
              ptQTask[24].ptParent = nullptr;
              *(_DWORD *)&ptQTask[24].eQTaskType = 1065353216;
              CarAI_UpdateAIStateCombat((struct CarAI_s *)ptQTask);
              v1 = ptQTask;
            }
            else
            {
              ptQTask[24].ptParent = (struct QTask_s *)1097859072;
              *(_DWORD *)&ptQTask[24].eQTaskType = 0;
              CarAI_UpdateAIStateCombat((struct CarAI_s *)ptQTask);
            }
            goto LABEL_57;
          }
          v1 = ptQTask;
        }
        ptNext = v1[25].ptNext;
        if ( ptNext )
        {
          AIGraph_GetClosestNode(
            (struct AIGraphNode_s **)&igi2_frame.isCombat,
            *(struct AIGraph_t **)&v1[17].eQTaskType,
            (struct real64x3_t *)&ptNext[1],
            false);
          v12 = (int *)igi2_frame.isCombat;
          ptQTask[24].tQTaskRefList.ptTail = (struct QReference_s *)igi2_frame.isCombat;
          CarAI_MakePath((struct CarAI_s *)ptQTask, *v12);
        }
        else
        {
          v12 = (int *)v1[24].tQTaskRefList.ptTail;
        }
        goto LABEL_37;
      }
      ptPrev = v1[18].ptPrev;
      v16 = ptPrev[1].ptPrev;
      if ( v16 == (struct QTask_s *)2 || v16 == (struct QTask_s *)3 )
      {
        v1 = ptQTask;
        if ( !CarAI_IsOnNode((struct CarAI_s *)ptQTask, (int)ptPrev[1].tQTaskChildren.ptHead) )
        {
          Node = (struct QReference_s *)Graph_GetNode(
                                          *(struct Graph_s **)&ptQTask[17].eQTaskType,
                                          (int)ptPrev[1].tQTaskChildren.ptHead);
          ptQTask[24].tQTaskRefList.ptTail = Node;
          if ( !Node )
            return;
          CarAI_MakePath((struct CarAI_s *)ptQTask, (int)Node->ptNext);
          ptQTask[24].ptParent = ptQTask[25].tQTaskChildren.ptTail;
          *(_DWORD *)&ptQTask[24].eQTaskType = 0;
          CarAI_UpdateAIStatePatrol((struct CarAI_s *)ptQTask);
          v1 = ptQTask;
          goto LABEL_57;
        }
        goto LABEL_53;
      }
      if ( v16 == (struct QTask_s *)1 )
      {
        v17 = v1[25].tQTaskChildren.ptMiddle;
        v1[24].ptParent = nullptr;
        *(_DWORD *)&v1[24].eQTaskType = 1065353216;
        v18 = (int)ptPrev[1].tQTaskChildren.ptHead;
        v1[25].tQTaskChildren.ptMiddle = (struct QTask_s *)((char *)&v17->ptNext + 1);
        if ( (int)v17 > v18 )
        {
          PatrolPath_StepPatrolPathForward(v18, &v1[18]);
          v1[25].tQTaskChildren.ptMiddle = nullptr;
        }
        goto LABEL_57;
      }
      if ( v16 != (struct QTask_s *)6 && v16 != (struct QTask_s *)7 )
      {
        if ( v16 == (struct QTask_s *)8 )
        {
          v19 = (double)(int)ptPrev[1].tQTaskChildren.ptHead;
          *(_DWORD *)&v1[24].eQTaskType = 0;
          *(float *)&v1[25].tQTaskChildren.ptTail = v19;
          PatrolPath_StepPatrolPathForward((int)ptMiddle, &v1[18]);
LABEL_57:
          CarAI_UpdateCar(
            (struct CarAI_s *)v1,
            *(_DWORD *)&v1[18].eQTaskType,
            *(float *)&v1[24].tQTaskChildren.ptMiddle,
            *(float *)&v1[24].tQTaskChildren.ptTail,
            *(float *)&v1[24].tQTaskRefList.ptHead);
          ++*(_DWORD *)&v1[18].eQTaskType;
          return;
        }
        if ( v16 != (struct QTask_s *)10 || PatrolPathCommand_isExpression(v1[18].ptPrev) )
        {
LABEL_53:
          PatrolPath_StepPatrolPathForward((int)ptMiddle, &v1[18]);
          goto LABEL_57;
        }
      }
    }
LABEL_56:
    v1[24].ptParent = nullptr;
    *(_DWORD *)&v1[24].eQTaskType = 1065353216;
    v1[24].tQTaskRefList.ptHead = (struct QReference_s *)1065353216;
    v1[24].tQTaskRefList.ptMiddle = nullptr;
    v1[24].tQTaskChildren.ptTail = nullptr;
    goto LABEL_57;
  }
}

// source: j/0/vehicles/carai.c:1276  [size]
void __cdecl CarAI_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = CarAI_ptParameterList;
}

// source: j/0/vehicles/carai.c:1292  [anchor-mhash]
void __cdecl CarAI_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  int v2; // eax
  __int16 v3; // dx
  unsigned __int16 v4; // ax
  float ptDynCubeObj; // [esp+0h] [ebp-18h]

  v2 = Script_ParseLineInt32((char *)&ptQTask[19].ptPrev);
  ptQTask[13].tQTaskRefList.ptTail = (struct QReference_s *)1065353216;
  ptQTask[13].ptParent = (struct QTask_s *)(1020 * v2 + 139173824);
  HumanDamage_ClearDamage((struct HumanDamage_t *)&ptQTask[13].tQTaskRefList.ptMiddle);
  v3 = ParameterList_eUpdateInternalDataQTaskEvent;
  v4 = CarAI_eQTaskType;
  ptQTask[17].tQTaskChildren.ptMiddle = (struct QTask_s *)-1;
  ptQTask[17].tQTaskChildren.ptTail = nullptr;
  ptQTask[17].tQTaskRefList.ptHead = nullptr;
  QTask_TriggerBaseHandler(ptQTask, v4, v3, pxContext);
  Level_CompileLevelExpression((struct LevelExpression_s *)&ptQTask[22].tQTaskChildren.ptMiddle, ptQTask);
  if ( *(_DWORD *)&ptQTask[2].eQTaskType )
  {
    EditBoneObj_SetAnimation((struct EditBoneObj_s *)ptQTask, (char *)&ptQTask[19].eQTaskType);
    ptDynCubeObj = sqrt(
                     *(float *)&ptQTask[7].tQTaskChildren.ptTail * *(float *)&ptQTask[7].tQTaskChildren.ptTail
                   + *(float *)&ptQTask[7].tQTaskRefList.ptHead * *(float *)&ptQTask[7].tQTaskRefList.ptHead
                   + *(float *)&ptQTask[7].tQTaskRefList.ptMiddle * *(float *)&ptQTask[7].tQTaskRefList.ptMiddle)
                 + *(float *)&ptQTask[8].ptNext;
    World_RegisterDynCubeObjFirstTimeRadius(
      (struct World_s *)ptQTask[2].ptParent,
      (struct DynCubeObj_s *)ptQTask,
      (struct real64x3_t *)&ptQTask[1],
      ptDynCubeObj,
      (enum DynCubeTreeCategory_enum)0);
  }
  else
  {
    World_RemoveDynCubeObj((struct World_s *)ptQTask[2].ptParent, (struct DynCubeObj_s *)ptQTask);
  }
}

// source: j/0/vehicles/carai.c:1332  [anchor-caller]
void __cdecl CarAI_UpdateInternalDataAfterLoadHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptParent; // edx
  unsigned __int16 v2; // cx
  struct QReference_s *ptMiddle; // eax
  struct QReference_s *v4; // eax
  _WORD *pxObject; // eax

  ptParent = ptQTask->ptParent;
  ptQTask[18].ptParent = nullptr;
  if ( ptParent )
  {
    v2 = Car_eQTaskType;
    while ( QTask_IsQTaskTypeDerived(ptParent->eQTaskType, v2) == false )
    {
      ptParent = ptQTask->ptParent;
      if ( !ptParent )
        goto LABEL_7;
    }
    ptQTask[18].ptParent = ptParent;
  }
LABEL_7:
  ptMiddle = ptQTask[17].tQTaskRefList.ptMiddle;
  if ( (unsigned int)ptMiddle < 0x1000 && (v4 = Level_atLevelQTaskID[(_DWORD)ptMiddle]) != nullptr )
    pxObject = v4->pxObject;
  else
    pxObject = nullptr;
  *(_DWORD *)&ptQTask[17].eQTaskType = pxObject;
  if ( pxObject && pxObject[18] != AIGraph_eQTaskType )
    *(_DWORD *)&ptQTask[17].eQTaskType = 0;
  if ( ptQTask[18].ptParent )
    CarAI_UpdateCar((struct CarAI_s *)ptQTask, 0, 0.0, 0.0, 0.0);
}

// source: j/0/vehicles/carai.c:1380  [size]
void __cdecl CarAI_RegisterScriptSymbolsHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { char zName[64]; };
    struct { char igi2_o1[64]; char zTemp[128]; };
    char igi2_extent[192];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)

  if ( !BYTE2(ptQTask[19].ptNext) )
  {
    BYTE2(ptQTask[19].ptNext) = 1;
    Level_GetUniqueQTaskNameFromTask(igi2_frame.zName, ptQTask);
    sprintf(igi2_frame.zTemp, "%s.isDead", igi2_frame.zName);
    Symbol_Register(
      igi2_frame.zTemp,
      (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_Int8,
      &ptQTask[19],
      1,
      QSCRIPT_SYMBOLCLASS_VARIABLE,
      QSCRIPT_SYMBOLTYPE_INT,
      QSCRIPT_SYMBOLLIFESPAN_FINITE);
  }
}

// source: j/0/vehicles/carai.c:1410  [size]
void __cdecl CarAI_RemoveScriptSymbolsHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { char zName[64]; };
    struct { char igi2_o1[64]; char zTemp[128]; };
    char igi2_extent[192];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)

  if ( BYTE2(ptQTask[19].ptNext) )
  {
    Level_GetUniqueQTaskNameFromTask(igi2_frame.zName, ptQTask);
    sprintf(igi2_frame.zTemp, "%s.isDead", igi2_frame.zName);
    Symbol_Remove(igi2_frame.zTemp);
    BYTE2(ptQTask[19].ptNext) = 0;
  }
}

// source: j/0/vehicles/carai.c:1442  [anchor-mhash]
void __cdecl CarAI_WeaponCollisionEvaluateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  if ( ptQTask != *((struct QTask_s **)pxContext + 1)
    && ptQTask != *((struct QTask_s **)pxContext + 2)
    && ptQTask != *((struct QTask_s **)pxContext + 3) )
  {
    *(_BYTE *)pxContext = 1;
  }
}

// source: j/0/vehicles/carai.c:1466  [anchor-mhash]
void __cdecl CarAI_WeaponHitHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *v2; // edi
  struct HumanDamage_t *p_ptMiddle; // ebx
  enum DamagePart_e DamagePartFromWeaponHit; // eax
  double v5; // st7
  int v6; // ecx
  int v7; // esi
  void (__cdecl *pfHandler)(int, struct HumanHitByYouContext_s *); // eax
  struct HumanHitByYouContext_s tHitByYouContext; // [esp+Ch] [ebp-4h] BYREF

  v2 = ptQTask;
  p_ptMiddle = (struct HumanDamage_t *)&ptQTask[13].tQTaskRefList.ptMiddle;
  if ( !LOBYTE(ptQTask[19].ptNext) )
  {
    DamagePartFromWeaponHit = HumanDamage_GetDamagePartFromWeaponHit(
                                (struct HumanDamage_t *)&ptQTask[13].tQTaskRefList.ptMiddle,
                                (struct BoneDynCubeObj_s *)ptQTask,
                                (struct WeaponHitContext_t *)pxContext);
    ptQTask[17].tQTaskChildren.ptMiddle = (struct QTask_s *)DamagePartFromWeaponHit;
    v5 = p_ptMiddle->atDamagePart[DamagePartFromWeaponHit].vDamageMultiplier * *((float *)pxContext + 1);
    p_ptMiddle->atDamagePart[DamagePartFromWeaponHit].vDamage = v5
                                                              + p_ptMiddle->atDamagePart[DamagePartFromWeaponHit].vDamage;
    p_ptMiddle->vDamage = v5 + p_ptMiddle->vDamage;
    HumanDamage_CreateFleshEnterEffect(
      p_ptMiddle,
      (struct real32x3_t *)((char *)pxContext + 8),
      (struct real64x3_t *)(*(_DWORD *)pxContext + 8),
      ptQTask);
    if ( *(float *)&ptQTask[13].tQTaskRefList.ptMiddle >= (double)*(float *)&ptQTask[13].tQTaskRefList.ptTail )
    {
      LOBYTE(ptQTask[19].ptNext) = 1;
      EditBoneObj_SetAnimation((struct EditBoneObj_s *)ptQTask, (char *)&ptQTask[21].tQTaskRefList);
      v2 = ptQTask;
    }
    v6 = *((_DWORD *)pxContext + 5);
    if ( v6 )
    {
      v7 = *((_DWORD *)pxContext + 7);
      if ( v7 )
      {
        if ( *(_BYTE *)(v7 + 177) )
        {
          tHitByYouContext.ptSenderQTask = v2;
          pfHandler = (void (__cdecl *)(int, struct HumanHitByYouContext_s *))QTask_aatQTaskFinalEvent[Human_eHitByYouQTaskEvent][*(unsigned __int16 *)(v6 + 36)].pfHandler;
          if ( pfHandler )
            pfHandler(v6, &tHitByYouContext);
        }
      }
    }
  }
}

void __cdecl sub_489CD0(struct QTask_s *a1)
{
  if ( *(_DWORD *)&a1[2].eQTaskType )
    ((void (__cdecl *)())QTask_aatQTaskFinalEvent[DynCubeObj_eDynCubeObjRegisterQTaskEvent][BoneDynCubeObj_eQTaskType].pfHandler)(a1);
}

void __cdecl sub_489D00(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *ptPrev; // edx
  int v3; // ecx
  struct QReference_s *v4; // eax
  struct QTask_s *ptHead; // edx
  int v6; // eax
  struct QReference_s *v7; // ecx

  ptPrev = ptQTask[18].ptPrev;
  if ( ptPrev )
  {
    v3 = 0;
    while ( 1 )
    {
      v4 = Level_atLevelQTaskID[v3];
      if ( v4 )
      {
        if ( v4->pxObject == ptPrev )
          break;
      }
      if ( ++v3 >= 4096 )
      {
        v3 = -1;
        break;
      }
    }
    ptQTask[18].tQTaskRefList.ptMiddle = (struct QReference_s *)v3;
  }
  else
  {
    ptQTask[18].tQTaskRefList.ptMiddle = (struct QReference_s *)-1;
  }
  ptHead = ptQTask[18].tQTaskChildren.ptHead;
  if ( ptHead )
  {
    v6 = 0;
    while ( 1 )
    {
      v7 = Level_atLevelQTaskID[v6];
      if ( v7 )
      {
        if ( v7->pxObject == ptHead )
          break;
      }
      if ( ++v6 >= 4096 )
      {
        v6 = -1;
        break;
      }
    }
    ptQTask[18].tQTaskRefList.ptTail = (struct QReference_s *)v6;
    Serialize_SerializeHandler(ptQTask, pxContext);
  }
  else
  {
    ptQTask[18].tQTaskRefList.ptTail = (struct QReference_s *)-1;
    Serialize_SerializeHandler(ptQTask, pxContext);
  }
}

void __cdecl sub_489DA0(struct QTask_s *ptQTask, void *pxContext)
{
  struct QReference_s *ptTail; // edx
  struct QReference_s *ptMiddle; // eax
  struct QReference_s *v4; // eax
  struct QTask_s *pxObject; // eax
  struct QReference_s *v6; // eax
  struct QReference_s *v7; // eax

  ptTail = ptQTask[17].tQTaskRefList.ptTail;
  if ( ptTail != (struct QReference_s *)-1 )
  {
    PatrolPath_InitPatrolPath((struct PatrolPathControl_t *)&ptQTask[18], (int)ptTail, 0);
    HIBYTE(ptQTask[19].ptNext) = 1;
  }
  AIGraphAStarSearch_Clear((struct AIGraphAStarSearchData_s *)&ptQTask[25].tQTaskRefList);
  Serialize_DeSerializeHandler(ptQTask, pxContext);
  ptMiddle = ptQTask[18].tQTaskRefList.ptMiddle;
  ptQTask[25].ptNext = nullptr;
  ptQTask[25].ptPrev = nullptr;
  if ( ptMiddle != (struct QReference_s *)-1 )
  {
    if ( (unsigned int)ptMiddle < 0x1000 && (v4 = Level_atLevelQTaskID[(_DWORD)ptMiddle]) != nullptr )
      pxObject = (struct QTask_s *)v4->pxObject;
    else
      pxObject = nullptr;
    ptQTask[18].ptPrev = pxObject;
  }
  v6 = ptQTask[18].tQTaskRefList.ptTail;
  if ( v6 == (struct QReference_s *)-1 )
  {
    ptQTask[18].tQTaskChildren.ptHead = nullptr;
  }
  else if ( (unsigned int)v6 < 0x1000 && (v7 = Level_atLevelQTaskID[(_DWORD)v6]) != nullptr )
  {
    ptQTask[18].tQTaskChildren.ptHead = (struct QTask_s *)v7->pxObject;
  }
  else
  {
    ptQTask[18].tQTaskChildren.ptHead = nullptr;
  }
}

// source: j/0/vehicles/carai.c:1650  [size]
void __cdecl CarAI_GetSerializeParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = CarAI_ptSerializeParameterList;
}

// source: j/0/vehicles/carai.c:1670  [anchor-strings]
void __cdecl CarAI_Open()
{
  unsigned __int16 v0; // si
  struct ParameterList_s *v1; // eax
  int v2; // edx
  unsigned __int16 v3; // si
  struct ParameterList_s *v4; // eax
  int v5; // edx

  v0 = QTask_NewQTaskType("CarAI", 1096, EditBoneObj_eQTaskType, 0, 0);
  CarAI_eQTaskType = v0;
  QTask_SetQTaskTypeGroup(v0, 1u);
  QTask_LinkQTaskEventHandlerFn(v0, 0, CarAI_CreateHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))CarAI_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(v0, GameFunctions_eWeaponHitQTaskEvent, CarAI_WeaponHitHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    GameFunctions_eWeaponCollisionEvaluateQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))CarAI_WeaponCollisionEvaluateHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    DynCubeObj_eDynCubeObjRegisterQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))sub_489CD0);
  QTask_LinkQTaskEventHandlerFn(v0, ParameterList_eUpdateInternalDataQTaskEvent, CarAI_UpdateInternalDataHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 1, CarAI_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 2, CarAI_DeleteHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(
    v0,
    Level_eUpdateInternalDataAfterLoadEvent,
    CarAI_UpdateInternalDataAfterLoadHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, Level_eRegisterLevelScriptSymbolsEvent, CarAI_RegisterScriptSymbolsHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, Level_eRemoveLevelScriptSymbolsEvent, CarAI_RemoveScriptSymbolsHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveHandler);
  v1 = (struct ParameterList_s *)Mem_AllocFn(212, 4);
  v2 = Level_eParameterTypeObjectPos;
  v1->ptParameterListItem = (struct ParameterListItem_s *)&v1[1];
  v1->nParameters = 0;
  v1->nMaxParameters = 10;
  CarAI_ptParameterList = v1;
  ParameterList_AddParameter(v1, 0x190u, v2, "Position", 7u, nullptr);
  ParameterList_AddParameter(CarAI_ptParameterList, 0x1A8u, Level_eParameterTypeReal32x9, "Orientation", 7u, nullptr);
  ParameterList_AddParameter(CarAI_ptParameterList, 0x1D0u, Level_eParameterTypeString16, "Driver Model", 7u, nullptr);
  ParameterList_AddParameter(
    CarAI_ptParameterList,
    0x31Cu,
    Level_eParameterTypeString32,
    "Driving animation",
    7u,
    nullptr);
  ParameterList_AddParameter(CarAI_ptParameterList, 0x33Cu, Level_eParameterTypeString32, "Idle animation", 7u, nullptr);
  ParameterList_AddParameter(
    CarAI_ptParameterList,
    0x35Cu,
    Level_eParameterTypeString32,
    "Death animation",
    7u,
    nullptr);
  ParameterList_AddParameter(
    CarAI_ptParameterList,
    0x37Cu,
    Level_eParameterTypeVarString,
    "Driving expression",
    7u,
    nullptr);
  ParameterList_AddParameter(CarAI_ptParameterList, 0x2FCu, Level_eParameterTypeString32, "AI Type", 7u, nullptr);
  ParameterList_AddParameter(CarAI_ptParameterList, 0x2C0u, Level_eParameterTypeInt32, "Graph ID", 7u, nullptr);
  ParameterList_AddParameter(CarAI_ptParameterList, 0x2C4u, Level_eParameterTypeInt32, "Route ID", 7u, nullptr);
  v3 = CarAI_eQTaskType;
  QTask_LinkQTaskEventHandlerFn(
    CarAI_eQTaskType,
    Serialize_eGetSerializeParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))CarAI_GetSerializeParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(v3, Serialize_eSerializeQTaskEvent, sub_489D00);
  QTask_LinkQTaskEventHandlerFn(v3, Serialize_eDeSerializeQTaskEvent, sub_489DA0);
  v4 = (struct ParameterList_s *)Mem_AllocFn(232, 4);
  v5 = Level_eParameterTypeInt32;
  v4->ptParameterListItem = (struct ParameterListItem_s *)&v4[1];
  v4->nParameters = 0;
  v4->nMaxParameters = 11;
  CarAI_ptSerializeParameterList = v4;
  ParameterList_AddParameter(v4, 0x2E8u, v5, "nCurrentCommandQTaskID", 7u, nullptr);
  ParameterList_AddParameter(
    CarAI_ptSerializeParameterList,
    0x2ECu,
    Level_eParameterTypeInt32,
    "nLastEndCommandQTaskID",
    7u,
    nullptr);
  ParameterList_AddParameter(CarAI_ptSerializeParameterList, 0x2F8u, Level_eParameterTypebool8, "isDead", 7u, nullptr);
  ParameterList_AddParameter(CarAI_ptSerializeParameterList, 0x220u, Level_eParameterTypeReal32, "Damage", 7u, nullptr);
  ParameterList_AddParameter(CarAI_ptSerializeParameterList, 0x2F4u, Level_eParameterTypeInt32, "Time", 7u, nullptr);
  ParameterList_AddParameter(
    CarAI_ptSerializeParameterList,
    0x434u,
    Level_eParameterTypeInt32,
    "CurrentPathIndex",
    7u,
    nullptr);
  ParameterList_AddParameter(
    CarAI_ptSerializeParameterList,
    0x438u,
    Level_eParameterTypeInt32,
    "nCurrentStartNode",
    7u,
    nullptr);
  ParameterList_AddParameter(
    CarAI_ptSerializeParameterList,
    0x43Cu,
    Level_eParameterTypeInt32,
    "nCurrentEdgeNode0",
    7u,
    nullptr);
  ParameterList_AddParameter(
    CarAI_ptSerializeParameterList,
    0x440u,
    Level_eParameterTypeInt32,
    "nCurrentEdgeNode1",
    7u,
    nullptr);
  ParameterList_AddParameter(
    CarAI_ptSerializeParameterList,
    0x444u,
    Level_eParameterTypeInt32,
    "nCurrentDestNode",
    7u,
    nullptr);
  ParameterList_AddParameter(
    CarAI_ptSerializeParameterList,
    0x3F8u,
    Level_eParameterTypeReal32,
    "vCommandSetSpeed",
    7u,
    nullptr);
}

// source: j/0/vehicles/carai.c:1740  [size]
void __cdecl CarAI_Close()
{
  int v0; // esi
  int v1; // esi

  if ( CarAI_ptParameterList )
  {
    v0 = *(_DWORD *)((unsigned int)&CarAI_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
  if ( CarAI_ptSerializeParameterList )
  {
    v1 = *(_DWORD *)((unsigned int)&CarAI_ptSerializeParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v1);
    memset(*(void **)(v1 + 8), 0xCDu, *(_DWORD *)(v1 + 16));
    free((void *)v1);
  }
  QTask_DeleteQTaskType(CarAI_eQTaskType);
}

// source: j/0/vehicles/carai.c:1759  [size]
unsigned __int16 __cdecl CarAI_GetQTaskType()
{
  return CarAI_eQTaskType;
}
