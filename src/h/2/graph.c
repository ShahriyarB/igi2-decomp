/* h/2/graph.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: h/2/graph.c:164  [anchor-mhash]
void __cdecl Graph_AddLinkToNode(struct GraphNode_s *ptNode, struct GraphLink_s *ptLink)
{
  int v2; // eax
  struct GraphLink_s **i; // ecx

  v2 = 0;
  for ( i = ptNode->aptLinks; *i; ++i )
  {
    if ( ++v2 >= 64 )
      return;
  }
  ptNode->aptLinks[v2] = ptLink;
}

// source: h/2/graph.c:189  [anchor-mhash]
void __cdecl Graph_RemoveLinkFromNode(
        struct GraphNode_s *ptNode,
        struct GraphLink_s *ptLink)
{
  int v2; // eax
  struct GraphLink_s **i; // ecx

  v2 = 0;
  for ( i = ptNode->aptLinks; *i != ptLink; ++i )
  {
    if ( ++v2 >= 64 )
      return;
  }
  ptNode->aptLinks[v2] = nullptr;
}

// source: h/2/graph.c:241  [anchor-mhash]
int __cdecl Graph_ClearNodeList(struct Graph_s *ptGraph, int nEntries)
{
  int result; // eax
  int v4; // ecx
  int v5; // edx

  result = (int)ptGraph->pxGraphNodeList;
  if ( result )
  {
    result = Graph_GetGraphNodeDataSize((int)ptGraph);
    if ( nEntries > 0 )
    {
      v4 = 0;
      v5 = nEntries;
      do
      {
        *(_DWORD *)((char *)ptGraph->pxGraphNodeList + v4) = -1;
        v4 += result;
        --v5;
      }
      while ( v5 );
    }
  }
  return result;
}

// source: h/2/graph.c:271  [anchor-callee]
int __cdecl Graph_ExpandNodeList(struct Graph_s *ptGraph, int nID)
{
  void *pxGraphNodeList; // esi
  int v3; // ebp
  int v4; // eax
  int nDataSize; // edi
  void *v6; // eax
  int GraphNodeDataSize; // eax
  int v8; // ecx
  int v9; // edx
  int v10; // esi
  int v11; // eax
  int result; // eax

  pxGraphNodeList = ptGraph->pxGraphNodeList;
  v3 = ptGraph->nMaxNodes + 100 * ((nID - ptGraph->nMaxNodes) / 100 + 1);
  v4 = 0;
  while ( ptGraph->tQTask.eQTaskType != Graph_atGraphNodeDataSize[v4].eGraphQTaskType )
  {
    if ( ++v4 >= 4 )
    {
      LDebug_Error("Undefined GraphNodeDataSize");
      abort();
    }
  }
  nDataSize = Graph_atGraphNodeDataSize[v4].nDataSize;
  v6 = Mem_AllocFn(v3 * nDataSize, 4);
  ptGraph->pxGraphNodeList = v6;
  if ( v6 )
  {
    GraphNodeDataSize = Graph_GetGraphNodeDataSize((int)ptGraph);
    if ( v3 > 0 )
    {
      v8 = 0;
      v9 = v3;
      do
      {
        *(_DWORD *)((char *)ptGraph->pxGraphNodeList + v8) = -1;
        v8 += GraphNodeDataSize;
        --v9;
      }
      while ( v9 );
    }
  }
  if ( pxGraphNodeList )
  {
    qmemcpy(ptGraph->pxGraphNodeList, pxGraphNodeList, nDataSize * ptGraph->nMaxNodes);
    v10 = *(_DWORD *)(((int)pxGraphNodeList - 4) & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v10);
    memset(*(void **)(v10 + 8), 0xCDu, *(_DWORD *)(v10 + 16));
    free((void *)v10);
  }
  v11 = ptGraph->tQTask.eQTaskType + 511 * Graph_eInitDataQTaskEvent;
  ptGraph->nMaxNodes = v3;
  result = (int)QTask_aatQTaskFinalEvent[0][v11].pfHandler;
  if ( result )
    return ((int (__cdecl *)(struct Graph_s *, _DWORD))result)(ptGraph, 0);
  return result;
}

// source: h/2/graph.c:490  [anchor-mhash]
void __cdecl Graph_PrepareDeleteHandler(struct QTask_s *ptQTask)
{
  struct GraphEntry_s *ptHead; // esi
  struct GraphEntry_s *ptNext; // eax
  struct QReference_s *ptGraphQTaskRef; // ecx
  struct QTask_s *v4; // ebx
  struct QReference_s *ptMiddle; // eax
  int i; // ebp
  struct QTask_s *v7; // edx
  int j; // eax
  int v9; // esi
  int v10; // eax
  int v11; // ecx
  char *v12; // eax
  struct GraphLink_s **v13; // esi
  int v14; // edi

  ptHead = Graph_tGraphList.ptHead;
  ptNext = Graph_tGraphList.ptHead->ptNext;
  if ( Graph_tGraphList.ptHead->ptNext )
  {
    while ( 1 )
    {
      ptGraphQTaskRef = ptHead->ptGraphQTaskRef;
      if ( ptGraphQTaskRef )
      {
        v4 = ptQTask;
        if ( ptGraphQTaskRef->pxObject == ptQTask )
          break;
      }
      ptHead = ptNext;
      ptNext = ptNext->ptNext;
      if ( !ptNext )
        goto LABEL_5;
    }
    QReference_Delete(ptHead->ptGraphQTaskRef, &QTask_tQTaskRefPool);
    Node_Remove(ptHead);
    v9 = *(_DWORD *)((unsigned int)&ptHead[-1].ptGraphQTaskRef & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v9);
    memset(*(void **)(v9 + 8), 0xCDu, *(_DWORD *)(v9 + 16));
    free((void *)v9);
  }
  else
  {
LABEL_5:
    v4 = ptQTask;
  }
  ptMiddle = v4[2].tQTaskRefList.ptMiddle;
  for ( i = 0; i < (int)ptMiddle; ++i )
  {
    v7 = v4[3].tQTaskChildren.ptMiddle;
    if ( v7 && i < (int)ptMiddle && i >= 0 )
    {
      for ( j = 0; ; ++j )
      {
        if ( j >= 4 )
        {
          LDebug_Error("Undefined GraphNodeDataSize");
          abort();
        }
        if ( v4->eQTaskType == Graph_atGraphNodeDataSize[j].eGraphQTaskType )
          break;
      }
      v10 = i * Graph_atGraphNodeDataSize[j].nDataSize;
      v11 = *(int *)((char *)&v7->ptNext + v10);
      v12 = (char *)v7 + v10;
      if ( v11 != -1 )
      {
        v13 = (struct GraphLink_s **)(v12 + 324);
        v14 = 64;
        do
        {
          if ( *v13 )
            Graph_DeleteLink(*v13);
          ++v13;
          --v14;
        }
        while ( v14 );
        v4 = ptQTask;
      }
    }
    ptMiddle = v4[2].tQTaskRefList.ptMiddle;
  }
}

// source: h/2/graph.c:602  [size]
void __cdecl Graph_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = Graph_ptParameterList;
}

// source: h/2/graph.c:618  [anchor-strings]
void __cdecl Graph_ParseGraphHandler(void *pxData, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { int v12; };
    struct { char igi2_o1[4]; char zGraphName[1024]; };
    char igi2_extent[1028];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v2; // esi
  struct ArgList_s *v3; // edi
  struct ArgList_s *v4; // edi
  int v5; // esi
  int v6; // eax
  struct ArgList_s *v7; // edi
  int v8; // esi
  int v9; // esi
  int v10; // eax
  struct QReference_s *v11; // ecx

  v2 = *(_DWORD *)pxContext;
  *((_BYTE *)pxData + 123) = 0;
  *((_BYTE *)pxData + 124) = 0;
  v3 = *((struct ArgList_s **)pxContext + 1);
  if ( v3->isQVM )
  {
    igi2_frame.v12 = 0;
    QVM_EvalArg(&igi2_frame.v12, 4, v3, v2, 1);
  }
  else
  {
    Expression_EvalInt(v3->aptExpression[v2]);
  }
  v4 = *((struct ArgList_s **)pxContext + 1);
  v5 = v2 + 1;
  if ( v4->isQVM )
  {
    igi2_frame.v12 = 0;
    QVM_EvalArg(&igi2_frame.v12, 4, v4, v5, 1);
    v6 = igi2_frame.v12;
  }
  else
  {
    v6 = Expression_EvalInt(v4->aptExpression[v5]);
  }
  *((_DWORD *)pxData + 26) = v6;
  v7 = *((struct ArgList_s **)pxContext + 1);
  v8 = v5 + 1;
  if ( v7->isQVM )
  {
    igi2_frame.v12 = 0;
    QVM_EvalArg(&igi2_frame.v12, 4, v7, v8, 1);
  }
  else
  {
    Expression_EvalInt(v7->aptExpression[v8]);
  }
  v9 = v8 + 1;
  *((_DWORD *)pxData + 27) = 0;
  *((_DWORD *)pxData + 28) = 0;
  v10 = 0;
  while ( 1 )
  {
    v11 = Level_atLevelQTaskID[v10];
    if ( v11 )
    {
      if ( v11->pxObject == pxData )
        break;
    }
    if ( ++v10 >= 4096 )
    {
      v10 = -1;
      break;
    }
  }
  sprintf(igi2_frame.zGraphName, "MISSION:graphs/graph%d.dat", v10);
  Graph_ParseGraphStream((struct Graph_s *)pxData, igi2_frame.zGraphName);
  *(_DWORD *)pxContext = v9;
}

// source: h/2/graph.c:672  [anchor-strings]
void __cdecl Graph_PrintGraphHandler(void *pxData, void *pxContext)
{
  int v2; // eax
  struct QReference_s *v3; // ecx
  char zGraphName[1024]; // [esp+4h] [ebp-400h] BYREF

  sprintf(
    *((char **)pxContext + 2),
    "%d, %d, %d",
    *((_DWORD *)pxData + 27),
    *((_DWORD *)pxData + 26),
    *((_DWORD *)pxData + 28));
  v2 = 0;
  while ( 1 )
  {
    v3 = Level_atLevelQTaskID[v2];
    if ( v3 )
    {
      if ( v3->pxObject == pxData )
        break;
    }
    if ( ++v2 >= 4096 )
    {
      v2 = -1;
      break;
    }
  }
  sprintf(zGraphName, "MISSION:graphs/graph%d.dat", v2);
  Graph_SaveGraphStream((struct Graph_s *)pxData, zGraphName);
}

// source: h/2/graph.c:721  [size]
void __cdecl Graph_GetNumberOfArgumentsGraphHandler(void *pxData, void *pxContext)
{
  *(_DWORD *)pxContext = 3;
}

// source: h/2/graph.c:783  [anchor-mhash]
void __cdecl Graph_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  _DWORD *v2; // edi

  ptQTask[2].tQTaskChildren.ptTail = (struct QTask_s *)-1;
  ptQTask[2].tQTaskRefList.ptHead = nullptr;
  ptQTask[2].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[2].tQTaskRefList.ptTail = nullptr;
  ptQTask[2].ptParent = nullptr;
  LOBYTE(ptQTask[1].ptNext) = 0;
  LOBYTE(ptQTask[3].ptNext) = 0;
  HIBYTE(ptQTask[3].ptNext) = 0;
  LOBYTE(ptQTask[3].ptPrev) = 0;
  BYTE1(ptQTask[3].ptNext) = 0;
  BYTE2(ptQTask[3].ptNext) = 0;
  *(_DWORD *)&ptQTask[2].eQTaskType = 1;
  ptQTask[3].tQTaskChildren.ptHead = (struct QTask_s *)1082130432;
  ptQTask[1].ptParent = nullptr;
  *(_DWORD *)&ptQTask[1].eQTaskType = 0;
  ptQTask[2].ptNext = nullptr;
  ptQTask[2].ptPrev = nullptr;
  ptQTask[2].tQTaskChildren.ptHead = nullptr;
  ptQTask[2].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[3].tQTaskChildren.ptMiddle = nullptr;
  v2 = Mem_AllocFn(12, 4);
  v2[2] = QTask_NewQTaskRef(ptQTask);
  v2[1] = 0;
  *v2 = 0;
  List_AddTail(v2, (int)&Graph_tGraphList);
  ptQTask[3].tQTaskChildren.ptTail = (struct QTask_s *)((char *)ptQTask + 140);
  ptQTask[3].tQTaskRefList.ptMiddle = (struct QReference_s *)&ptQTask[3].tQTaskChildren.ptTail;
  ptQTask[3].tQTaskRefList.ptHead = nullptr;
  ptQTask[1].ptParent = nullptr;
  *(_DWORD *)&ptQTask[1].eQTaskType = 0;
  ptQTask[2].ptNext = nullptr;
  ptQTask[2].ptPrev = nullptr;
  ptQTask[2].tQTaskChildren.ptHead = nullptr;
  ptQTask[2].tQTaskChildren.ptMiddle = nullptr;
  memset(&ptQTask[1].ptPrev, 0, 0x1Cu);
  QTask_TriggerQTaskEventParent(ptQTask, Attach_eAttachEvent, &ptQTask[1].ptPrev);
}

// source: h/2/graph.c:853  [anchor-mhash]
void __cdecl Graph_ParentChangedHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { float v25; };
    struct { char igi2_o1[32]; float vAlpha; };
    struct { char igi2_o2[36]; struct real32x3_t v29; };
    struct { char igi2_o3[48]; struct real32x9_t tOrientation; };
    struct { char igi2_o4[88]; float *vBeta; };
    struct { char igi2_o5[92]; struct real32x9_t Real32x9_Multiply_tTemp; };
    struct { char igi2_o6[132]; struct real32x9_t Real32x9_Normalize_tTemp; };
    struct { char igi2_o7[172]; float v34; };
    struct { char igi2_o8[176]; struct real32x9_t Real32x9_Invert_tTemp; };
    struct { char igi2_o9[216]; struct AttachContext_t tOldAttachContext; };
    struct { char igi2_o10[244]; struct real64x3_t Real64x3_Rotate_tTemp; };
    struct { char igi2_o11[268]; struct real64x3_t Real64x3_RotateInverse_tTemp; };
    char igi2_extent[292];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *v2; // ebx
  struct QReference_s *ptMiddle; // eax
  float v4; // esi
  double *v5; // ebx
  struct real32x9_t *ptParentOrientation; // eax
  struct real64x3_t *ptParentPos; // ecx
  double v8; // st7
  long double v9; // st7
  struct QTask_s *v10; // eax
  double v11; // st7
  float *ptTail; // eax
  struct QTask_s *v13; // eax
  float v14; // edx
  double v15; // st7
  double v16; // st6
  double v17; // st5
  double v18; // st4
  float v19; // edx
  int v20; // eax
  bool v21; // sf
  long double v22; // st7
  long double v23; // st7
  long double v24; // st7
  struct real32x3_t tTemp_; // 0:^1C.12

  v2 = ptQTask;
  qmemcpy(&igi2_frame.tOldAttachContext, &ptQTask[1].ptPrev, sizeof(igi2_frame.tOldAttachContext));
  memset(&ptQTask[1].ptPrev, 0, 0x1Cu);
  QTask_TriggerQTaskEventParent(ptQTask, Attach_eAttachEvent, &ptQTask[1].ptPrev);
  if ( igi2_frame.tOldAttachContext.ptParentPos != (struct real64x3_t *)ptQTask[1].tQTaskChildren.ptMiddle )
  {
    ptMiddle = ptQTask[2].tQTaskRefList.ptMiddle;
    v4 = 0.0;
    igi2_frame.vAlpha = 0.0;
    if ( (int)ptMiddle > 0 )
    {
      do
      {
        if ( v2[3].tQTaskChildren.ptMiddle && SLODWORD(v4) < (int)ptMiddle && v4 >= 0.0 )
        {
          v5 = (double *)((char *)v2[3].tQTaskChildren.ptMiddle + LODWORD(v4) * Graph_GetGraphNodeDataSize((int)v2));
          if ( *(_DWORD *)v5 != -1 )
          {
            if ( igi2_frame.tOldAttachContext.ptParentPos )
            {
              ptParentOrientation = igi2_frame.tOldAttachContext.ptParentOrientation;
              igi2_frame.Real64x3_Rotate_tTemp.vX = igi2_frame.tOldAttachContext.ptParentOrientation->tX.vY * v5[2]
                                       + igi2_frame.tOldAttachContext.ptParentOrientation->tX.vZ * v5[3]
                                       + igi2_frame.tOldAttachContext.ptParentOrientation->tX.vX * v5[1];
              igi2_frame.Real64x3_Rotate_tTemp.vY = igi2_frame.tOldAttachContext.ptParentOrientation->tY.vY * v5[2]
                                       + igi2_frame.tOldAttachContext.ptParentOrientation->tY.vZ * v5[3]
                                       + igi2_frame.tOldAttachContext.ptParentOrientation->tY.vX * v5[1];
              igi2_frame.Real64x3_Rotate_tTemp.vZ = igi2_frame.tOldAttachContext.ptParentOrientation->tZ.vY * v5[2]
                                       + igi2_frame.tOldAttachContext.ptParentOrientation->tZ.vZ * v5[3]
                                       + igi2_frame.tOldAttachContext.ptParentOrientation->tZ.vX * v5[1];
              qmemcpy(v5 + 1, &igi2_frame.Real64x3_Rotate_tTemp, 0x18u);
              ptParentPos = igi2_frame.tOldAttachContext.ptParentPos;
              v5[1] = igi2_frame.tOldAttachContext.ptParentPos->vX + v5[1];
              v5[2] = ptParentPos->vY + v5[2];
              v8 = ptParentPos->vZ + v5[3];
              igi2_frame.vBeta = (float *)(v5 + 4);
              igi2_frame.v25 = *((float *)v5 + 8);
              v5[3] = v8;
              Real32x9_RotateGamma(&igi2_frame.tOrientation, ptParentOrientation, igi2_frame.v25);
              v4 = igi2_frame.vAlpha;
            }
            else
            {
              igi2_frame.v34 = *((float *)v5 + 8);
              igi2_frame.vBeta = (float *)(v5 + 4);
              v9 = sin(igi2_frame.v34);
              igi2_frame.tOrientation.tX.vZ = 0.0;
              memset(&igi2_frame.tOrientation.tY.vZ, 0, 12);
              igi2_frame.tOrientation.tZ.vZ = 1.0;
              igi2_frame.tOrientation.nOps = 0;
              igi2_frame.tOrientation.tX.vX = cos(igi2_frame.v34);
              igi2_frame.tOrientation.tX.vY = -v9;
              igi2_frame.tOrientation.tY.vX = v9;
              igi2_frame.tOrientation.tY.vY = igi2_frame.tOrientation.tX.vX;
            }
            v10 = ptQTask[1].tQTaskChildren.ptMiddle;
            if ( v10 )
            {
              v5[1] = v5[1] - *(double *)&v10->ptNext;
              v5[2] = v5[2] - *(double *)&ptQTask[1].tQTaskChildren.ptMiddle->tQTaskChildren.ptHead;
              v11 = v5[3] - *(double *)&ptQTask[1].tQTaskChildren.ptMiddle->tQTaskChildren.ptTail;
              v5[3] = v11;
              ptTail = (float *)ptQTask[1].tQTaskChildren.ptTail;
              igi2_frame.Real64x3_RotateInverse_tTemp.vX = ptTail[6] * v11 + ptTail[3] * v5[2] + *ptTail * v5[1];
              igi2_frame.Real64x3_RotateInverse_tTemp.vY = ptTail[7] * v11 + ptTail[4] * v5[2] + ptTail[1] * v5[1];
              igi2_frame.Real64x3_RotateInverse_tTemp.vZ = ptTail[8] * v11 + ptTail[5] * v5[2] + ptTail[2] * v5[1];
              qmemcpy(v5 + 1, &igi2_frame.Real64x3_RotateInverse_tTemp, 0x18u);
              v13 = ptQTask[1].tQTaskChildren.ptTail;
              v14 = *(float *)&v13->tQTaskRefList.ptMiddle;
              v15 = *(float *)&v13->ptNext;
              LODWORD(igi2_frame.Real32x9_Invert_tTemp.tY.vY) = v13->tQTaskChildren.ptTail;
              v16 = *(float *)&v13->tQTaskChildren.ptMiddle;
              v17 = *(float *)&v13->ptPrev;
              LODWORD(igi2_frame.Real32x9_Invert_tTemp.tZ.vY) = v13->tQTaskRefList.ptHead;
              v18 = *(float *)&v13->tQTaskChildren.ptHead;
              igi2_frame.Real32x9_Invert_tTemp.tX.vZ = v14;
              LODWORD(igi2_frame.Real32x9_Invert_tTemp.tY.vZ) = v13->tQTaskRefList.ptTail;
              v19 = *(float *)&v13->ptParent;
              v20 = *(_DWORD *)&v13->eQTaskType;
              igi2_frame.Real32x9_Invert_tTemp.tZ.vZ = v19;
              igi2_frame.Real32x9_Multiply_tTemp.tX.vX = igi2_frame.tOrientation.tX.vZ * v18
                                            + igi2_frame.tOrientation.tX.vY * v17
                                            + igi2_frame.tOrientation.tX.vX * v15;
              igi2_frame.Real32x9_Multiply_tTemp.tX.vY = igi2_frame.tOrientation.tX.vZ * igi2_frame.Real32x9_Invert_tTemp.tZ.vY
                                            + igi2_frame.tOrientation.tX.vY * igi2_frame.Real32x9_Invert_tTemp.tY.vY
                                            + igi2_frame.tOrientation.tX.vX * v16;
              igi2_frame.Real32x9_Multiply_tTemp.nOps = igi2_frame.tOrientation.nOps + v20 + 1;
              v21 = igi2_frame.tOrientation.nOps + v20 - 999 < 0;
              igi2_frame.Real32x9_Multiply_tTemp.tX.vZ = igi2_frame.tOrientation.tX.vZ * v19
                                            + igi2_frame.tOrientation.tX.vY * igi2_frame.Real32x9_Invert_tTemp.tY.vZ
                                            + igi2_frame.tOrientation.tX.vX * igi2_frame.Real32x9_Invert_tTemp.tX.vZ;
              igi2_frame.Real32x9_Multiply_tTemp.tY.vX = igi2_frame.tOrientation.tY.vZ * v18
                                            + igi2_frame.tOrientation.tY.vY * v17
                                            + igi2_frame.tOrientation.tY.vX * v15;
              igi2_frame.Real32x9_Multiply_tTemp.tY.vY = igi2_frame.tOrientation.tY.vZ * igi2_frame.Real32x9_Invert_tTemp.tZ.vY
                                            + igi2_frame.tOrientation.tY.vY * igi2_frame.Real32x9_Invert_tTemp.tY.vY
                                            + igi2_frame.tOrientation.tY.vX * v16;
              igi2_frame.Real32x9_Multiply_tTemp.tY.vZ = igi2_frame.tOrientation.tY.vZ * v19
                                            + igi2_frame.tOrientation.tY.vY * igi2_frame.Real32x9_Invert_tTemp.tY.vZ
                                            + igi2_frame.tOrientation.tY.vX * igi2_frame.Real32x9_Invert_tTemp.tX.vZ;
              igi2_frame.Real32x9_Multiply_tTemp.tZ.vX = igi2_frame.tOrientation.tZ.vZ * v18
                                            + igi2_frame.tOrientation.tZ.vY * v17
                                            + igi2_frame.tOrientation.tZ.vX * v15;
              igi2_frame.Real32x9_Multiply_tTemp.tZ.vY = igi2_frame.tOrientation.tZ.vZ * igi2_frame.Real32x9_Invert_tTemp.tZ.vY
                                            + igi2_frame.tOrientation.tZ.vY * igi2_frame.Real32x9_Invert_tTemp.tY.vY
                                            + igi2_frame.tOrientation.tZ.vX * v16;
              igi2_frame.Real32x9_Multiply_tTemp.tZ.vZ = igi2_frame.tOrientation.tZ.vZ * v19
                                            + igi2_frame.tOrientation.tZ.vY * igi2_frame.Real32x9_Invert_tTemp.tY.vZ
                                            + igi2_frame.tOrientation.tZ.vX * igi2_frame.Real32x9_Invert_tTemp.tX.vZ;
              qmemcpy(&igi2_frame.tOrientation, &igi2_frame.Real32x9_Multiply_tTemp, sizeof(igi2_frame.tOrientation));
              if ( !(v21 ^ __OFSUB__(igi2_frame.Real32x9_Multiply_tTemp.nOps, 1000) | (igi2_frame.Real32x9_Multiply_tTemp.nOps == 1000)) )
              {
                igi2_frame.Real32x9_Normalize_tTemp.tX = igi2_frame.Real32x9_Multiply_tTemp.tX;
                if ( igi2_frame.Real32x9_Multiply_tTemp.tX.vX != 0.0
                  || igi2_frame.Real32x9_Multiply_tTemp.tX.vY != 0.0
                  || igi2_frame.Real32x9_Multiply_tTemp.tX.vZ != 0.0 )
                {
                  v22 = 1.0
                      / sqrt(
                          igi2_frame.Real32x9_Multiply_tTemp.tX.vX * igi2_frame.Real32x9_Multiply_tTemp.tX.vX
                        + igi2_frame.Real32x9_Multiply_tTemp.tX.vY * igi2_frame.Real32x9_Multiply_tTemp.tX.vY
                        + igi2_frame.Real32x9_Multiply_tTemp.tX.vZ * igi2_frame.Real32x9_Multiply_tTemp.tX.vZ);
                  igi2_frame.Real32x9_Normalize_tTemp.tX.vX = igi2_frame.Real32x9_Multiply_tTemp.tX.vX * v22;
                  igi2_frame.Real32x9_Normalize_tTemp.tX.vY = igi2_frame.Real32x9_Normalize_tTemp.tX.vY * v22;
                  igi2_frame.Real32x9_Normalize_tTemp.tX.vZ = igi2_frame.Real32x9_Normalize_tTemp.tX.vZ * v22;
                }
                tTemp_.vX = igi2_frame.Real32x9_Multiply_tTemp.tZ.vY * igi2_frame.Real32x9_Multiply_tTemp.tX.vZ
                          - igi2_frame.Real32x9_Multiply_tTemp.tZ.vZ * igi2_frame.Real32x9_Multiply_tTemp.tX.vY;
                tTemp_.vY = -(igi2_frame.Real32x9_Multiply_tTemp.tZ.vX * igi2_frame.Real32x9_Multiply_tTemp.tX.vZ
                            - igi2_frame.Real32x9_Multiply_tTemp.tZ.vZ * igi2_frame.Real32x9_Multiply_tTemp.tX.vX);
                tTemp_.vZ = igi2_frame.Real32x9_Multiply_tTemp.tZ.vX * igi2_frame.Real32x9_Multiply_tTemp.tX.vY
                          - igi2_frame.Real32x9_Multiply_tTemp.tZ.vY * igi2_frame.Real32x9_Multiply_tTemp.tX.vX;
                igi2_frame.Real32x9_Normalize_tTemp.tY = tTemp_;
                igi2_frame.v29.vX = tTemp_.vZ * igi2_frame.Real32x9_Normalize_tTemp.tX.vY - tTemp_.vY * igi2_frame.Real32x9_Normalize_tTemp.tX.vZ;
                igi2_frame.v29.vY = -(tTemp_.vZ * igi2_frame.Real32x9_Normalize_tTemp.tX.vX - tTemp_.vX * igi2_frame.Real32x9_Normalize_tTemp.tX.vZ);
                igi2_frame.v29.vZ = tTemp_.vY * igi2_frame.Real32x9_Normalize_tTemp.tX.vX - tTemp_.vX * igi2_frame.Real32x9_Normalize_tTemp.tX.vY;
                igi2_frame.Real32x9_Normalize_tTemp.tZ = igi2_frame.v29;
                if ( tTemp_.vX != 0.0 || tTemp_.vY != 0.0 || tTemp_.vZ != 0.0 )
                {
                  v23 = 1.0 / sqrt(tTemp_.vZ * tTemp_.vZ + tTemp_.vY * tTemp_.vY + tTemp_.vX * tTemp_.vX);
                  igi2_frame.Real32x9_Normalize_tTemp.tY.vX = tTemp_.vX * v23;
                  igi2_frame.Real32x9_Normalize_tTemp.tY.vY = igi2_frame.Real32x9_Normalize_tTemp.tY.vY * v23;
                  igi2_frame.Real32x9_Normalize_tTemp.tY.vZ = igi2_frame.Real32x9_Normalize_tTemp.tY.vZ * v23;
                }
                if ( igi2_frame.v29.vX != 0.0 || igi2_frame.v29.vY != 0.0 || igi2_frame.v29.vZ != 0.0 )
                {
                  v24 = 1.0 / sqrt(igi2_frame.v29.vX * igi2_frame.v29.vX + igi2_frame.v29.vY * igi2_frame.v29.vY + igi2_frame.v29.vZ * igi2_frame.v29.vZ);
                  igi2_frame.Real32x9_Normalize_tTemp.tZ.vX = igi2_frame.v29.vX * v24;
                  igi2_frame.Real32x9_Normalize_tTemp.tZ.vY = igi2_frame.Real32x9_Normalize_tTemp.tZ.vY * v24;
                  igi2_frame.Real32x9_Normalize_tTemp.tZ.vZ = igi2_frame.Real32x9_Normalize_tTemp.tZ.vZ * v24;
                }
                qmemcpy(&igi2_frame.Real32x9_Multiply_tTemp, &igi2_frame.Real32x9_Normalize_tTemp, sizeof(igi2_frame.Real32x9_Multiply_tTemp));
                igi2_frame.Real32x9_Multiply_tTemp.nOps = 0;
              }
              v4 = igi2_frame.vAlpha;
            }
            Real32x9_GetAngles(&igi2_frame.tOrientation, &igi2_frame.vAlpha, (float *)&igi2_frame.vBeta, igi2_frame.vBeta);
          }
          v2 = ptQTask;
        }
        ptMiddle = v2[2].tQTaskRefList.ptMiddle;
        ++LODWORD(v4);
        igi2_frame.vAlpha = v4;
      }
      while ( SLODWORD(v4) < (int)ptMiddle );
    }
  }
}

// source: h/2/graph.c:929  [anchor-mhash]
void __cdecl Graph_UpdateInternalDataAfterLoadHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct real64x3_t tWorldPos; };
    struct { char igi2_o1[24]; struct GetSectorContext_t tSectorContext; };
    char igi2_extent[80];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QReference_s *ptMiddle; // ecx
  int v2; // ebx
  struct GraphNode_s *v3; // esi

  ptMiddle = ptQTask[2].tQTaskRefList.ptMiddle;
  v2 = 0;
  LOBYTE(ptQTask[1].ptNext) = 1;
  ptQTask[1].ptParent = nullptr;
  *(_DWORD *)&ptQTask[1].eQTaskType = 0;
  ptQTask[2].ptNext = nullptr;
  ptQTask[2].ptPrev = nullptr;
  ptQTask[2].tQTaskChildren.ptHead = nullptr;
  ptQTask[2].tQTaskChildren.ptMiddle = nullptr;
  if ( (int)ptMiddle > 0 )
  {
    do
    {
      if ( ptQTask[3].tQTaskChildren.ptMiddle )
      {
        if ( v2 < (int)ptQTask[2].tQTaskRefList.ptMiddle && v2 >= 0 )
        {
          v3 = (struct GraphNode_s *)((char *)ptQTask[3].tQTaskChildren.ptMiddle
                                    + v2 * Graph_GetGraphNodeDataSize((int)ptQTask));
          if ( v3->nID != -1 )
          {
            if ( v3->isTerrainNode )
            {
              v3->ptSectorQTask = nullptr;
            }
            else
            {
              Graph_GetNodePos(&igi2_frame.tWorldPos, v3);
              igi2_frame.tSectorContext.ptPos = &igi2_frame.tWorldPos;
              igi2_frame.tSectorContext.ptInsideSector = nullptr;
              igi2_frame.tSectorContext.ptInsideSectorObject = nullptr;
              igi2_frame.tSectorContext.isTolerance = 1;
              World_TriggerQTaskEventXyzSpecificTree(
                World_ptActiveWorld,
                QCube_eGetSectorQTaskEvent,
                &igi2_frame.tSectorContext,
                &igi2_frame.tWorldPos,
                0xFFFFFFFF,
                WORLD_DYNCUBETREE_STATIONARY);
              v3->ptSectorQTask = &igi2_frame.tSectorContext.ptInsideSector->tQObj.tQTask;
            }
          }
        }
      }
      ++v2;
    }
    while ( v2 < (int)ptQTask[2].tQTaskRefList.ptMiddle );
  }
}

// source: h/2/graph.c:989  [size]
void __cdecl Graph_UpdateAttachmentHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptHead; // ecx
  int v2; // edx
  struct QTask_s *v3; // eax
  int v4; // esi
  void (__cdecl *pfHandler)(struct QTask_s *); // eax
  int v6; // edx

  ptHead = ptQTask->tQTaskChildren.ptHead;
  if ( ptHead->ptNext && ptHead )
  {
    v2 = QTask_nProtectedQTaskStackOffset;
    do
    {
      if ( ptHead->ptNext )
        v3 = ptHead->ptNext->ptNext != nullptr ? ptHead->ptNext : nullptr;
      else
        v3 = nullptr;
      v4 = Attach_eUpdateAttachmentEvent;
      QTask_atProtectedQTaskStack[v2].ptQTask = v3;
      pfHandler = (void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[v4][ptHead->eQTaskType].pfHandler;
      v6 = v2 + 1;
      QTask_nProtectedQTaskStackOffset = v6;
      if ( pfHandler )
      {
        pfHandler(ptHead);
        v6 = QTask_nProtectedQTaskStackOffset;
      }
      ptHead = (struct QTask_s *)dword_849C7DC[v6];
      v2 = v6 - 1;
      QTask_nProtectedQTaskStackOffset = v2;
    }
    while ( ptHead );
  }
}

// source: h/2/graph.c:1002  [size]
void __cdecl Graph_RunHandler(struct QTask_s *ptQTask)
{
  ;
}

// source: h/2/graph.c:1022  [size]
void __cdecl Graph_DeleteHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptMiddle; // eax
  int v2; // esi

  ptMiddle = ptQTask[3].tQTaskChildren.ptMiddle;
  if ( ptMiddle )
  {
    v2 = *(_DWORD *)((unsigned int)&ptMiddle[-1].eQTaskType & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v2);
    memset(*(void **)(v2 + 8), 0xCDu, *(_DWORD *)(v2 + 16));
    free((void *)v2);
    ptQTask[3].tQTaskChildren.ptMiddle = nullptr;
  }
}

// source: h/2/graph.c:1041  [anchor-callee]
void __cdecl Graph_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  int v2; // ecx
  struct QReference_s *v3; // eax

  v2 = 0;
  while ( 1 )
  {
    v3 = Level_atLevelQTaskID[v2];
    if ( v3 )
    {
      if ( v3->pxObject == ptQTask )
        break;
    }
    if ( ++v2 >= 4096 )
    {
      ptQTask[2].tQTaskChildren.ptTail = (struct QTask_s *)-1;
      return;
    }
  }
  ptQTask[2].tQTaskChildren.ptTail = (struct QTask_s *)v2;
}

// source: h/2/graph.c:1131  [size]
struct ParameterList_s *__cdecl Graph_GetParameterList()
{
  return Graph_ptParameterList;
}

// source: h/2/graph.c:1144  [size]
unsigned __int16 __cdecl Graph_GetQTaskType()
{
  return Graph_eQTaskType;
}

// source: h/2/graph.c:1158  [size]
__int16 __cdecl Graph_GetDisplayRouteQTaskEvent()
{
  return Graph_eDisplayRouteQTaskEvent;
}

// source: h/2/graph.c:1172  [size]
__int16 __cdecl Graph_GetLoadGraphQTaskEvent()
{
  return Graph_eLoadGraphQTaskEvent;
}

// source: h/2/graph.c:1186  [size]
__int16 __cdecl Graph_GetSaveGraphQTaskEvent()
{
  return Graph_eSaveGraphQTaskEvent;
}

// source: h/2/graph.c:1200  [size]
__int16 __cdecl Graph_GetLoadNodeQTaskEvent()
{
  return Graph_eLoadNodeQTaskEvent;
}

// source: h/2/graph.c:1214  [size]
__int16 __cdecl Graph_GetSaveNodeQTaskEvent()
{
  return Graph_eSaveNodeQTaskEvent;
}

// source: h/2/graph.c:1228  [size]
__int16 __cdecl Graph_GetPrintNodeQTaskEvent()
{
  return Graph_ePrintNodeQTaskEvent;
}

// source: h/2/graph.c:1242  [size]
__int16 __cdecl Graph_GetCreateNodeQTaskEvent()
{
  return Graph_eCreateNodeQTaskEvent;
}

// source: h/2/graph.c:1256  [size]
__int16 __cdecl Graph_GetUpdateNodeQTaskEvent()
{
  return Graph_eUpdateNodeQTaskEvent;
}

// source: h/2/graph.c:1270  [size]
__int16 __cdecl Graph_GetUpdateDataQTaskEvent()
{
  return Graph_eUpdateDataQTaskEvent;
}

// source: h/2/graph.c:1284  [size]
__int16 __cdecl Graph_GetInitDataQTaskEvent()
{
  return Graph_eInitDataQTaskEvent;
}

// source: h/2/graph.c:1304  [anchor-callee]
struct Graph_s *__cdecl Graph_GetGraph(int nGraphID)
{
  struct Graph_s *result; // eax
  struct GraphEntry_s *ptHead; // eax
  struct GraphEntry_s *ptNext; // esi
  struct QReference_s *ptGraphQTaskRef; // eax
  int v5; // ecx
  struct QReference_s *v6; // edx

  if ( nGraphID == -1 )
    return nullptr;
  ptHead = Graph_tGraphList.ptHead;
  ptNext = Graph_tGraphList.ptHead->ptNext;
  if ( !Graph_tGraphList.ptHead->ptNext )
    return nullptr;
  while ( 1 )
  {
    ptGraphQTaskRef = ptHead->ptGraphQTaskRef;
    if ( ptGraphQTaskRef )
    {
      result = (struct Graph_s *)ptGraphQTaskRef->pxObject;
      if ( result->nGraphID == -1 )
      {
        v5 = 0;
        while ( 1 )
        {
          v6 = Level_atLevelQTaskID[v5];
          if ( v6 )
          {
            if ( v6->pxObject == result )
              break;
          }
          if ( ++v5 >= 4096 )
          {
            v5 = -1;
            break;
          }
        }
        result->nGraphID = v5;
      }
      if ( nGraphID == result->nGraphID )
        return result;
    }
    ptHead = ptNext;
    ptNext = ptNext->ptNext;
    if ( !ptNext )
      return nullptr;
  }
}

// source: h/2/graph.c:1349  [anchor-mhash]
struct Graph_s *__cdecl Graph_GetGraphFromParent(struct QTask_s *ptParentQTask)
{
  struct GraphEntry_s *ptHead; // eax
  struct GraphEntry_s *ptNext; // ecx
  struct QReference_s *ptGraphQTaskRef; // eax
  struct Graph_s *result; // eax

  ptHead = Graph_tGraphList.ptHead;
  ptNext = Graph_tGraphList.ptHead->ptNext;
  if ( !Graph_tGraphList.ptHead->ptNext )
    return nullptr;
  while ( 1 )
  {
    ptGraphQTaskRef = ptHead->ptGraphQTaskRef;
    if ( ptGraphQTaskRef )
    {
      result = (struct Graph_s *)ptGraphQTaskRef->pxObject;
      if ( ptParentQTask == result->tQTask.ptParent )
        break;
    }
    ptHead = ptNext;
    ptNext = ptNext->ptNext;
    if ( !ptNext )
      return nullptr;
  }
  return result;
}

// source: h/2/graph.c:1388  [anchor-mhash]
struct Graph_s *__cdecl Graph_TranslateWorldPosToRelativePos(
        struct Graph_s *ptGraph,
        struct real64x3_t *ptDest,
        struct real64x3_t *ptSource)
{
  struct real64x3_t *ptParentPos; // ecx
  double vZ; // st7
  double v6; // st7
  struct real64x3_t Real64x3_RotateInverse_tTemp; // [esp+8h] [ebp-1Ch] BYREF

  ptParentPos = ptGraph->tAttachContext.ptParentPos;
  if ( ptParentPos )
  {
    ptDest->vX = ptSource->vX - ptParentPos->vX;
    ptDest->vY = ptSource->vY - ptGraph->tAttachContext.ptParentPos->vY;
    vZ = ptSource->vZ;
    ptSource = &Real64x3_RotateInverse_tTemp;
    v6 = vZ - ptGraph->tAttachContext.ptParentPos->vZ;
    ptDest->vZ = v6;
    ptGraph = (struct Graph_s *)ptGraph->tAttachContext.ptParentOrientation;
    Real64x3_RotateInverse_tTemp.vX = *(float *)&ptGraph->tQTask.tQTaskChildren.ptMiddle * ptDest->vY
                                    + *(float *)&ptGraph->tQTask.tQTaskRefList.ptMiddle * v6
                                    + *(float *)&ptGraph->tQTask.ptNext * ptDest->vX;
    Real64x3_RotateInverse_tTemp.vY = *(float *)&ptGraph->tQTask.tQTaskChildren.ptTail * ptDest->vY
                                    + *(float *)&ptGraph->tQTask.ptPrev * ptDest->vX
                                    + *(float *)&ptGraph->tQTask.tQTaskRefList.ptTail * v6;
    Real64x3_RotateInverse_tTemp.vZ = *(float *)&ptGraph->tQTask.tQTaskRefList.ptHead * ptDest->vY
                                    + *(float *)&ptGraph->tQTask.tQTaskChildren.ptHead * ptDest->vX
                                    + *(float *)&ptGraph->tQTask.ptParent * v6;
  }
  qmemcpy(ptDest, ptSource, sizeof(struct real64x3_t));
  return ptGraph;
}

// source: h/2/graph.c:1416  [anchor-mhash]
struct real64x3_t *__cdecl Graph_TranslateRelativePosToWorldPos(
        struct Graph_s *ptGraph,
        struct real64x3_t *ptDest,
        struct real64x3_t *ptSource)
{
  struct real64x3_t *result; // eax
  struct real32x9_t *ptParentOrientation; // eax
  struct real64x3_t Real64x3_Rotate_tTemp; // [esp+8h] [ebp-18h] BYREF

  result = ptGraph->tAttachContext.ptParentPos;
  if ( result )
  {
    ptParentOrientation = ptGraph->tAttachContext.ptParentOrientation;
    Real64x3_Rotate_tTemp.vX = ptParentOrientation->tX.vZ * ptSource->vZ
                             + ptParentOrientation->tX.vY * ptSource->vY
                             + ptParentOrientation->tX.vX * ptSource->vX;
    Real64x3_Rotate_tTemp.vY = ptParentOrientation->tY.vZ * ptSource->vZ
                             + ptParentOrientation->tY.vY * ptSource->vY
                             + ptParentOrientation->tY.vX * ptSource->vX;
    Real64x3_Rotate_tTemp.vZ = ptParentOrientation->tZ.vZ * ptSource->vZ
                             + ptParentOrientation->tZ.vY * ptSource->vY
                             + ptParentOrientation->tZ.vX * ptSource->vX;
    qmemcpy(ptDest, &Real64x3_Rotate_tTemp, sizeof(struct real64x3_t));
    ptDest->vX = ptGraph->tAttachContext.ptParentPos->vX + ptDest->vX;
    ptDest->vY = ptGraph->tAttachContext.ptParentPos->vY + ptDest->vY;
    result = ptGraph->tAttachContext.ptParentPos;
    ptDest->vZ = result->vZ + ptDest->vZ;
  }
  else
  {
    qmemcpy(ptDest, ptSource, sizeof(struct real64x3_t));
  }
  return result;
}

// source: h/2/graph.c:1443  [anchor-callee]
void __cdecl Graph_AddWeightToNode(struct Graph_s *ptGraph, int nNodeId, float vWeight)
{
  float *v3; // ecx
  double v4; // st7

  if ( ptGraph )
  {
    if ( ptGraph->pxGraphNodeList )
    {
      if ( nNodeId < ptGraph->nMaxNodes && nNodeId >= 0 )
      {
        v3 = (float *)((char *)ptGraph->pxGraphNodeList + nNodeId * Graph_GetGraphNodeDataSize((int)ptGraph));
        if ( *(_DWORD *)v3 != -1 )
        {
          v4 = vWeight + v3[146];
          v3[146] = v4;
          if ( v4 <= 0.0 )
            v4 = 0.0;
          v3[146] = v4;
        }
      }
    }
  }
}

// source: h/2/graph.c:1468  [anchor-hash]
int __cdecl Graph_SetGraphNodeDataSize(unsigned __int16 a1, int a2)
{
  int v2; // ecx
  int result; // eax

  v2 = -1;
  for ( result = 0; result < 4; ++result )
  {
    if ( v2 == -1 && Graph_atGraphNodeDataSize[result].eGraphQTaskType == 512 )
      v2 = result;
    if ( Graph_atGraphNodeDataSize[result].eGraphQTaskType == a1 )
    {
      Graph_atGraphNodeDataSize[result].nDataSize = a2;
      return result;
    }
  }
  if ( v2 == -1 )
  {
    LDebug_Error("NO FREE NODESIZE ELEMENTS");
    abort();
  }
  Graph_atGraphNodeDataSize[v2].eGraphQTaskType = a1;
  Graph_atGraphNodeDataSize[v2].nDataSize = a2;
  return result;
}

// source: h/2/graph.c:1511  [anchor-hash]
int __cdecl Graph_GetGraphNodeDataSize(int a1)
{
  __int16 v1; // cx
  int v2; // eax

  v1 = *(_WORD *)(a1 + 36);
  v2 = 0;
  while ( v1 != Graph_atGraphNodeDataSize[v2].eGraphQTaskType )
  {
    if ( ++v2 >= 4 )
    {
      LDebug_Error("Undefined GraphNodeDataSize");
      abort();
    }
  }
  return Graph_atGraphNodeDataSize[v2].nDataSize;
}

// source: h/2/graph.c:1557  [anchor-strings]
struct GraphNode_s *__cdecl Graph_CreateNode(
        struct Graph_s *ptGraph,
        int nID,
        struct real64x3_t *ptPos,
        float vGamma,
        float vRadius,
        struct QMaterial_t *ptGroundMaterial,
        char *zCriteria,
        float vLight,
        int isTerrain,
        struct QTask_s *ptNodeQTask)
{
  int GraphNodeDataSize; // eax
  char *pxGraphNodeList; // edx
  struct GraphNode_s *v16; // ebp
  void (__cdecl *pfHandler)(struct Graph_s *, struct GraphNode_s *); // eax

  if ( nID >= 2000 )
    return nullptr;
  if ( nID >= ptGraph->nMaxNodes )
    Graph_ExpandNodeList(ptGraph, nID);
  if ( ptGraph->pxGraphNodeList
    && nID < ptGraph->nMaxNodes
    && nID >= 0
    && *(_DWORD *)((char *)ptGraph->pxGraphNodeList + nID * Graph_GetGraphNodeDataSize((int)ptGraph)) != -1 )
  {
    LDebug_Error("GRAPHNODE ID ALREADY USED");
    abort();
  }
  GraphNodeDataSize = Graph_GetGraphNodeDataSize((int)ptGraph);
  pxGraphNodeList = (char *)ptGraph->pxGraphNodeList;
  *(float *)&pxGraphNodeList[nID * GraphNodeDataSize + 40] = vRadius + vRadius;
  v16 = (struct GraphNode_s *)&pxGraphNodeList[nID * GraphNodeDataSize];
  v16->nID = nID;
  v16->vGamma = vGamma;
  v16->vRadius = vRadius;
  v16->nOccupiedByID = -1;
  strcpy(v16->zCriteria, zCriteria);
  qmemcpy(&v16->tPos, ptPos, sizeof(v16->tPos));
  v16->vLightValue = vLight;
  v16->isTerrainNode = isTerrain;
  v16->ptSectorQTask = nullptr;
  v16->ptGraph = ptGraph;
  v16->bCriteria = Script_ParseLineInt32(v16->zCriteria);
  v16->ptGroundMaterial = ptGroundMaterial;
  memset(v16->aptLinks, 0, sizeof(v16->aptLinks));
  pfHandler = (void (__cdecl *)(struct Graph_s *, struct GraphNode_s *))QTask_aatQTaskFinalEvent[Graph_eCreateNodeQTaskEvent][ptGraph->tQTask.eQTaskType].pfHandler;
  if ( pfHandler )
    pfHandler(ptGraph, v16);
  v16->vNodeWeight = 0.0;
  ++ptGraph->nNumNodes;
  return v16;
}

// source: h/2/graph.c:1645  [anchor-mhash]
void __cdecl Graph_DeleteNode(struct GraphNode_s *ptNode)
{
  struct GraphLink_s **aptLinks; // esi
  int v2; // edi
  struct Graph_s *ptGraph; // eax
  struct Graph_s *v4; // eax

  aptLinks = ptNode->aptLinks;
  v2 = 64;
  do
  {
    if ( *aptLinks )
      Graph_DeleteLink(*aptLinks);
    ++aptLinks;
    --v2;
  }
  while ( v2 );
  ptGraph = ptNode->ptGraph;
  if ( ptNode->nID < ptGraph->nFirstFreeNode )
    ptGraph->nFirstFreeNode = ptNode->nID;
  v4 = ptNode->ptGraph;
  ptNode->nID = -1;
  --v4->nNumNodes;
}

// source: h/2/graph.c:1697  [size]
void __cdecl Graph_UpdateNode(struct Graph_s *ptGraph, struct GraphNode_s *ptNode)
{
  ;
}

// source: h/2/graph.c:1777  [anchor-callee]
void __cdecl Graph_UpdateNodePos(struct Graph_s *ptGraph, int nNodeID, struct real64x3_t *ptPos)
{
  int GraphNodeDataSize; // eax

  if ( ptGraph->pxGraphNodeList && nNodeID < ptGraph->nMaxNodes && nNodeID >= 0 )
  {
    GraphNodeDataSize = Graph_GetGraphNodeDataSize((int)ptGraph);
    Graph_TranslateWorldPosToRelativePos(
      ptGraph,
      *(_DWORD *)((char *)ptGraph->pxGraphNodeList + nNodeID * GraphNodeDataSize) == -1
    ? (struct real64x3_t *)8
    : (struct real64x3_t *)((char *)ptGraph->pxGraphNodeList + nNodeID * GraphNodeDataSize + 8),
      ptPos);
  }
  else
  {
    Graph_TranslateWorldPosToRelativePos(ptGraph, (struct real64x3_t *)8, ptPos);
  }
}

// source: h/2/graph.c:1801  [anchor-callee]
struct GraphNode_s *__cdecl Graph_GetNode(struct Graph_s *ptGraph, int nID)
{
  int GraphNodeDataSize; // eax

  if ( !ptGraph->pxGraphNodeList || nID >= ptGraph->nMaxNodes || nID < 0 )
    return nullptr;
  GraphNodeDataSize = Graph_GetGraphNodeDataSize((int)ptGraph);
  return *(_DWORD *)((char *)ptGraph->pxGraphNodeList + nID * GraphNodeDataSize) == -1
       ? nullptr
       : (struct GraphNode_s *)((char *)ptGraph->pxGraphNodeList + nID * GraphNodeDataSize);
}

// source: h/2/graph.c:1843  [anchor-callee]
struct GraphNode_s *__cdecl Graph_GetNodePos(
        struct real64x3_t *ptPosition,
        struct GraphNode_s *ptNode)
{
  struct Graph_s *ptGraph; // ecx
  float *p_vX; // ecx
  struct real64x3_t Real64x3_Rotate_tTemp; // [esp+8h] [ebp-1Ch] BYREF

  ptGraph = ptNode->ptGraph;
  if ( ptGraph->tAttachContext.ptParentPos )
  {
    p_vX = &ptGraph->tAttachContext.ptParentOrientation->tX.vX;
    Real64x3_Rotate_tTemp.vX = p_vX[2] * ptNode->tPos.vZ + p_vX[1] * ptNode->tPos.vY + *p_vX * ptNode->tPos.vX;
    Real64x3_Rotate_tTemp.vY = p_vX[5] * ptNode->tPos.vZ + p_vX[4] * ptNode->tPos.vY + p_vX[3] * ptNode->tPos.vX;
    Real64x3_Rotate_tTemp.vZ = p_vX[8] * ptNode->tPos.vZ + p_vX[7] * ptNode->tPos.vY + p_vX[6] * ptNode->tPos.vX;
    qmemcpy(ptPosition, &Real64x3_Rotate_tTemp, sizeof(struct real64x3_t));
    ptPosition->vX = ptNode->ptGraph->tAttachContext.ptParentPos->vX + ptPosition->vX;
    ptPosition->vY = ptNode->ptGraph->tAttachContext.ptParentPos->vY + ptPosition->vY;
    ptNode = (struct GraphNode_s *)ptNode->ptGraph;
    ptPosition->vZ = *(double *)(ptNode->isTerrainNode + 16) + ptPosition->vZ;
  }
  else
  {
    qmemcpy(ptPosition, &ptNode->tPos, sizeof(struct real64x3_t));
  }
  return ptNode;
}

// source: h/2/graph.c:1869  [anchor-mhash]
struct GraphNode_s *__cdecl Graph_GetNodeOrientation(
        struct real32x9_t *ptOrientation,
        struct GraphNode_s *ptNode,
        char isIncludeNodeGamma)
{
  struct GraphNode_s *result; // eax

  result = (struct GraphNode_s *)ptNode->ptGraph->tAttachContext.ptParentOrientation;
  if ( result )
  {
    if ( isIncludeNodeGamma )
      return (struct GraphNode_s *)Real32x9_RotateGamma(ptOrientation, (struct real32x9_t *)result, ptNode->vGamma);
    else
      qmemcpy(ptOrientation, result, sizeof(struct real32x9_t));
  }
  else
  {
    ptOrientation->tX.vX = 1.0;
    ptOrientation->tX.vY = 0.0;
    ptOrientation->tX.vZ = 0.0;
    ptOrientation->tY.vX = 0.0;
    ptOrientation->tY.vY = 1.0;
    ptOrientation->tY.vZ = 0.0;
    ptOrientation->tZ.vX = 0.0;
    ptOrientation->tZ.vY = 0.0;
    ptOrientation->tZ.vZ = 1.0;
    ptOrientation->nOps = 0;
    return (struct GraphNode_s *)1065353216;
  }
  return result;
}

// source: h/2/graph.c:1900  [size]
int __cdecl Graph_SetNodeOccupiedStatus(struct GraphNode_s *ptNode, int nOccupiedID)
{
  ptNode->nOccupiedByID = nOccupiedID;
  return nOccupiedID;
}

// source: h/2/graph.c:1916  [size]
int __cdecl Graph_GetNodeOccupiedStatus(struct GraphNode_s *ptNode)
{
  return ptNode->nOccupiedByID;
}

// source: h/2/graph.c:1931  [size]
struct GraphNode_s *__cdecl Graph_ClearNodeOccupiedStatus(struct GraphNode_s *ptNode)
{
  ptNode->nOccupiedByID = -1;
  return ptNode;
}

// source: h/2/graph.c:1946  [anchor-mhash]
void __cdecl Graph_SetNodeIDOccupiedStatus(struct Graph_s *ptGraph, int nNodeID, int nOccupiedID)
{
  _DWORD *v3; // ecx

  if ( ptGraph->pxGraphNodeList && nNodeID < ptGraph->nMaxNodes && nNodeID >= 0 )
  {
    v3 = (char *)ptGraph->pxGraphNodeList + nNodeID * Graph_GetGraphNodeDataSize((int)ptGraph);
    if ( *v3 != -1 )
      v3[12] = nOccupiedID;
  }
}

// source: h/2/graph.c:1971  [anchor-mhash]
int __cdecl Graph_GetNodeIDOccupiedStatus(struct Graph_s *ptGraph, int nNodeID)
{
  _DWORD *v2; // ecx

  if ( !ptGraph->pxGraphNodeList )
    return -1;
  if ( nNodeID >= ptGraph->nMaxNodes )
    return -1;
  if ( nNodeID < 0 )
    return -1;
  v2 = (char *)ptGraph->pxGraphNodeList + nNodeID * Graph_GetGraphNodeDataSize((int)ptGraph);
  if ( *v2 == -1 )
    return -1;
  else
    return v2[12];
}

// source: h/2/graph.c:1998  [anchor-mhash]
void __cdecl Graph_ClearNodeIDOccupiedStatus(struct Graph_s *ptGraph, int nNodeID)
{
  _DWORD *v2; // ecx

  if ( ptGraph->pxGraphNodeList && nNodeID < ptGraph->nMaxNodes && nNodeID >= 0 )
  {
    v2 = (char *)ptGraph->pxGraphNodeList + nNodeID * Graph_GetGraphNodeDataSize((int)ptGraph);
    if ( *v2 != -1 )
      v2[12] = -1;
  }
}

// source: h/2/graph.c:2023  [anchor-mhash]
char __cdecl Graph_IsPositionOnNode(
        struct real64x3_t *ptPosition,
        struct GraphNode_s *ptNode,
        double vDeviance,
        char isCheckHeight)
{
  #pragma pack(push, 1)
  union
  {
    struct { double v12; };
    struct { char igi2_o1[8]; double v13; };
    struct { char igi2_o2[16]; double tRelativePosFromNode; };
    struct { char igi2_o3[24]; double tRelativePosFromNode_8; };
    struct { char igi2_o4[40]; struct real32x9_t tNodePos; };
    char igi2_extent[80];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  double v4; // st7
  struct real32x9_t *ptParentOrientation; // eax
  double vX; // st7
  double v8; // st6
  double v9; // st5
  double v10; // st7
  double v11; // st6

  Graph_GetNodePos((struct real64x3_t *)&igi2_frame.tNodePos, ptNode);
  igi2_frame.tRelativePosFromNode = ptPosition->vX - *(double *)&igi2_frame.tNodePos.tX.vX;
  igi2_frame.tRelativePosFromNode_8 = ptPosition->vY - *(double *)&igi2_frame.tNodePos.tX.vZ;
  v4 = ptPosition->vZ - *(double *)&igi2_frame.tNodePos.tY.vY;
  if ( isCheckHeight )
  {
    if ( v4 < 0.0 )
      v4 = -v4;
    if ( v4 > 4096.0 )
      return 0;
  }
  if ( igi2_frame.tRelativePosFromNode == 0.0 && igi2_frame.tRelativePosFromNode_8 == 0.0 )
    return 0;
  ptParentOrientation = ptNode->ptGraph->tAttachContext.ptParentOrientation;
  if ( ptParentOrientation )
  {
    Real32x9_RotateGamma(&igi2_frame.tNodePos, ptParentOrientation, ptNode->vGamma);
    vX = igi2_frame.tNodePos.tX.vX;
    v8 = igi2_frame.tNodePos.tY.vX;
    v9 = igi2_frame.tNodePos.tZ.vX;
  }
  else
  {
    vX = 1.0;
    igi2_frame.tNodePos.tX.vY = 0.0;
    v8 = 0.0;
    igi2_frame.tNodePos.tY.vY = 1.0;
    v9 = 0.0;
    igi2_frame.tNodePos.tZ.vY = 0.0;
  }
  v10 = v8 * igi2_frame.tRelativePosFromNode_8 + vX * igi2_frame.tRelativePosFromNode + v9 * 0.0;
  *(double *)&igi2_frame.tNodePos.tX.vZ = igi2_frame.tNodePos.tY.vY * igi2_frame.tRelativePosFromNode_8
                             + igi2_frame.tNodePos.tX.vY * igi2_frame.tRelativePosFromNode
                             + igi2_frame.tNodePos.tZ.vY * 0.0;
  v11 = ptNode->vRadius + vDeviance;
  igi2_frame.v12 = -4096.0 * v11;
  if ( v10 < igi2_frame.v12 )
    return 0;
  igi2_frame.v13 = v11 * 4096.0;
  return v10 <= igi2_frame.v13 && *(double *)&igi2_frame.tNodePos.tX.vZ >= igi2_frame.v12 && *(double *)&igi2_frame.tNodePos.tX.vZ <= igi2_frame.v13;
}

// source: h/2/graph.c:2081  [anchor-callee]
struct GraphLink_s *__cdecl Graph_CreateLink(struct Graph_s *ptGraph, int nID1, int nID2, int eType)
{
  #pragma pack(push, 1)
  union
  {
    struct { float tReal32x3; };
    struct { char igi2_o1[4]; float tReal32x3_4; };
    struct { char igi2_o2[12]; struct real64x3_t tP1; };
    struct { char igi2_o3[36]; struct real64x3_t tP2; };
    char igi2_extent[60];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct GraphLink_s *ptHead; // esi
  int v5; // ebx
  int GraphNodeDataSize; // eax
  char *v7; // edx
  int v8; // eax
  _DWORD *v9; // ecx
  int v10; // ebx
  int v11; // eax
  char *v12; // edx
  int v13; // eax
  _DWORD *v14; // ecx
  char *pxGraphNodeList; // ebx
  int v16; // ebp
  int v17; // eax
  struct GraphNode_s *v18; // eax
  int v19; // ebp
  int v20; // eax
  struct GraphNode_s *v21; // eax

  if ( Graph_tLinkPool.nAllocatedBlocks == Graph_tLinkPool.nBlocks )
    MemPool_ReAlloc(&Graph_tLinkPool, Graph_tLinkPool.nReAllocBlocks);
  ptHead = (struct GraphLink_s *)Graph_tLinkPool.tMemPoolFreeList.ptHead;
  ++Graph_tLinkPool.nAllocatedBlocks;
  Graph_tLinkPool.tMemPoolFreeList.ptHead = Graph_tLinkPool.tMemPoolFreeList.ptHead->ptNext;
  ptHead->nID2 = nID2;
  ptHead->eType = eType;
  ptHead->nID1 = nID1;
  ptHead->ptGraph = ptGraph;
  ptHead->ptPrev = nullptr;
  ptHead->ptNext = nullptr;
  List_AddTail(ptHead, (int)&ptGraph->tGraphLinkList);
  v5 = ptHead->nID1;
  if ( ptGraph->pxGraphNodeList && v5 < ptGraph->nMaxNodes && v5 >= 0 )
  {
    GraphNodeDataSize = Graph_GetGraphNodeDataSize((int)ptGraph);
    v7 = *(_DWORD *)((char *)ptGraph->pxGraphNodeList + v5 * GraphNodeDataSize) == -1
       ? nullptr
       : (char *)ptGraph->pxGraphNodeList + v5 * GraphNodeDataSize;
  }
  else
  {
    v7 = nullptr;
  }
  v8 = 0;
  v9 = v7 + 324;
  while ( *v9 )
  {
    ++v8;
    ++v9;
    if ( v8 >= 64 )
      goto LABEL_13;
  }
  *(_DWORD *)&v7[4 * v8 + 324] = ptHead;
LABEL_13:
  v10 = ptHead->nID2;
  if ( ptGraph->pxGraphNodeList && v10 < ptGraph->nMaxNodes && v10 >= 0 )
  {
    v11 = Graph_GetGraphNodeDataSize((int)ptGraph);
    v12 = *(_DWORD *)((char *)ptGraph->pxGraphNodeList + v10 * v11) == -1
        ? nullptr
        : (char *)ptGraph->pxGraphNodeList + v10 * v11;
  }
  else
  {
    v12 = nullptr;
  }
  v13 = 0;
  v14 = v12 + 324;
  while ( *v14 )
  {
    ++v13;
    ++v14;
    if ( v13 >= 64 )
      goto LABEL_23;
  }
  *(_DWORD *)&v12[4 * v13 + 324] = ptHead;
LABEL_23:
  pxGraphNodeList = (char *)ptGraph->pxGraphNodeList;
  v16 = ptHead->nID1;
  if ( pxGraphNodeList && v16 < ptGraph->nMaxNodes && v16 >= 0 )
  {
    v17 = Graph_GetGraphNodeDataSize((int)ptGraph);
    pxGraphNodeList = (char *)ptGraph->pxGraphNodeList;
    v18 = *(_DWORD *)&pxGraphNodeList[v16 * v17] == -1 ? nullptr : (struct GraphNode_s *)&pxGraphNodeList[v16 * v17];
  }
  else
  {
    v18 = nullptr;
  }
  Graph_GetNodePos(&igi2_frame.tP1, v18);
  v19 = ptHead->nID2;
  if ( pxGraphNodeList && v19 < ptGraph->nMaxNodes && v19 >= 0 )
  {
    v20 = Graph_GetGraphNodeDataSize((int)ptGraph);
    v21 = *(_DWORD *)((char *)ptGraph->pxGraphNodeList + v19 * v20) == -1
        ? nullptr
        : (struct GraphNode_s *)((char *)ptGraph->pxGraphNodeList + v19 * v20);
  }
  else
  {
    v21 = nullptr;
  }
  Graph_GetNodePos(&igi2_frame.tP2, v21);
  igi2_frame.tReal32x3 = igi2_frame.tP1.vX - igi2_frame.tP2.vX;
  igi2_frame.tReal32x3_4 = igi2_frame.tP1.vY - igi2_frame.tP2.vY;
  ptHead->vLength = sqrt(igi2_frame.tReal32x3 * igi2_frame.tReal32x3 + igi2_frame.tReal32x3_4 * igi2_frame.tReal32x3_4 + (igi2_frame.tP1.vZ - igi2_frame.tP2.vZ) * (igi2_frame.tP1.vZ - igi2_frame.tP2.vZ));
  ++ptGraph->nNumLinks;
  return ptHead;
}

// source: h/2/graph.c:2175  [anchor-mhash]
void __cdecl Graph_DeleteLink(struct GraphLink_s *ptLink)
{
  struct Graph_s *ptGraph; // esi
  int nID1; // edi
  int GraphNodeDataSize; // eax
  int v4; // edx
  int v5; // eax
  struct GraphLink_s **v6; // ecx
  struct Graph_s *v7; // esi
  int nID2; // edi
  int v9; // eax
  int v10; // edx
  int v11; // eax
  struct GraphLink_s **v12; // ecx

  ptGraph = ptLink->ptGraph;
  nID1 = ptLink->nID1;
  if ( ptGraph->pxGraphNodeList && nID1 < ptGraph->nMaxNodes && nID1 >= 0 )
  {
    GraphNodeDataSize = Graph_GetGraphNodeDataSize((int)ptLink->ptGraph);
    v4 = *(_DWORD *)((char *)ptGraph->pxGraphNodeList + nID1 * GraphNodeDataSize) == -1
       ? 0
       : (int)ptGraph->pxGraphNodeList + nID1 * GraphNodeDataSize;
  }
  else
  {
    v4 = 0;
  }
  v5 = 0;
  v6 = (struct GraphLink_s **)(v4 + 324);
  while ( *v6 != ptLink )
  {
    ++v5;
    ++v6;
    if ( v5 >= 64 )
      goto LABEL_11;
  }
  *(_DWORD *)(v4 + 4 * v5 + 324) = 0;
LABEL_11:
  v7 = ptLink->ptGraph;
  nID2 = ptLink->nID2;
  if ( v7->pxGraphNodeList && nID2 < v7->nMaxNodes && nID2 >= 0 )
  {
    v9 = Graph_GetGraphNodeDataSize((int)ptLink->ptGraph);
    v10 = *(_DWORD *)((char *)v7->pxGraphNodeList + nID2 * v9) == -1 ? 0 : (int)v7->pxGraphNodeList + nID2 * v9;
  }
  else
  {
    v10 = 0;
  }
  v11 = 0;
  v12 = (struct GraphLink_s **)(v10 + 324);
  while ( *v12 != ptLink )
  {
    ++v11;
    ++v12;
    if ( v11 >= 64 )
      goto LABEL_21;
  }
  *(_DWORD *)(v10 + 4 * v11 + 324) = 0;
LABEL_21:
  --ptLink->ptGraph->nNumLinks;
  Node_Remove(ptLink);
  --Graph_tLinkPool.nAllocatedBlocks;
  ptLink->ptNext = (struct GraphLink_s *)Graph_tLinkPool.tMemPoolFreeList.ptHead;
  Graph_tLinkPool.tMemPoolFreeList.ptHead = (struct MemPoolFreeItem_s *)ptLink;
}

// source: h/2/graph.c:2309  [anchor-mhash]
void __cdecl Graph_MaxNodesCallback(struct GraphStreamCallbackContext_s *ptCallbackContext)
{
  struct GraphStreamCallbackContext_s *v1; // ebp
  struct Graph_s *ptGraph; // esi
  void *pxGraphNodeList; // eax
  int v4; // ebx
  int v5; // eax
  void *v6; // eax
  struct GraphStreamCallbackContext_s *v7; // edi
  int GraphNodeDataSize; // eax
  int v9; // ecx

  v1 = ptCallbackContext;
  ptGraph = ptCallbackContext->ptGraph;
  ptCallbackContext = (struct GraphStreamCallbackContext_s *)ptGraph->nMaxNodes;
  pxGraphNodeList = ptGraph->pxGraphNodeList;
  if ( pxGraphNodeList )
  {
    --Mem_nCurrentAllocations;
    v4 = *(_DWORD *)(((int)pxGraphNodeList - 4) & 0xFFFFFFFC);
    Node_Remove((_DWORD **)v4);
    memset(*(void **)(v4 + 8), 0xCDu, *(_DWORD *)(v4 + 16));
    free((void *)v4);
    ptGraph->pxGraphNodeList = nullptr;
  }
  GraphStream_LoadParameter(v1, &ptCallbackContext, 0);
  v5 = 0;
  while ( ptGraph->tQTask.eQTaskType != Graph_atGraphNodeDataSize[v5].eGraphQTaskType )
  {
    if ( ++v5 >= 4 )
    {
      LDebug_Error("Undefined GraphNodeDataSize");
      abort();
    }
  }
  v6 = Mem_AllocFn((_DWORD)ptCallbackContext * Graph_atGraphNodeDataSize[v5].nDataSize, 4);
  ptGraph->pxGraphNodeList = v6;
  v7 = ptCallbackContext;
  if ( v6 )
  {
    GraphNodeDataSize = Graph_GetGraphNodeDataSize((int)ptGraph);
    if ( (int)v7 > 0 )
    {
      v9 = 0;
      do
      {
        *(_DWORD *)((char *)ptGraph->pxGraphNodeList + v9) = -1;
        v9 += GraphNodeDataSize;
        v7 = (struct GraphStreamCallbackContext_s *)((char *)v7 - 1);
      }
      while ( v7 );
    }
  }
  ptGraph->nMaxNodes = (int)ptCallbackContext;
}

// source: h/2/graph.c:2342  [anchor-mhash]
void __cdecl Graph_NodeIDCallback(struct GraphStreamCallbackContext_s *ptCallbackContext)
{
  memset(&Graph_tNode, 0, sizeof(Graph_tNode));
  ptCallbackContext->ptCurrentGraphNode = nullptr;
  GraphStream_LoadParameter(ptCallbackContext, &Graph_tNode, 0);
}

// source: h/2/graph.c:2359  [anchor-mhash]
void __cdecl Graph_NodePositionCallback(struct GraphStreamCallbackContext_s *ptCallbackContext)
{
  struct Graph_s *ptGraph; // eax
  struct real64x3_t *ptParentPos; // eax
  struct real32x9_t *ptParentOrientation; // eax
  struct real64x3_t Real64x3_RotateInverse_tTemp; // [esp+4h] [ebp-18h] BYREF

  GraphStream_LoadParameter(ptCallbackContext, &Graph_tNode.tPos, 0);
  ptGraph = ptCallbackContext->ptGraph;
  if ( !ptGraph->isRelative )
  {
    Graph_tNode.tPos.vX = Graph_tNode.tPos.vX + ptGraph->tPosition.vX;
    Graph_tNode.tPos.vY = Graph_tNode.tPos.vY + ptCallbackContext->ptGraph->tPosition.vY;
    Graph_tNode.tPos.vZ = Graph_tNode.tPos.vZ + ptCallbackContext->ptGraph->tPosition.vZ;
    ptParentPos = ptCallbackContext->ptGraph->tAttachContext.ptParentPos;
    if ( ptParentPos )
    {
      Graph_tNode.tPos.vX = Graph_tNode.tPos.vX - ptParentPos->vX;
      Graph_tNode.tPos.vY = Graph_tNode.tPos.vY - ptCallbackContext->ptGraph->tAttachContext.ptParentPos->vY;
      Graph_tNode.tPos.vZ = Graph_tNode.tPos.vZ - ptCallbackContext->ptGraph->tAttachContext.ptParentPos->vZ;
      ptParentOrientation = ptCallbackContext->ptGraph->tAttachContext.ptParentOrientation;
      Real64x3_RotateInverse_tTemp.vX = ptParentOrientation->tZ.vX * Graph_tNode.tPos.vZ
                                      + ptParentOrientation->tY.vX * Graph_tNode.tPos.vY
                                      + ptParentOrientation->tX.vX * Graph_tNode.tPos.vX;
      Real64x3_RotateInverse_tTemp.vY = ptParentOrientation->tZ.vY * Graph_tNode.tPos.vZ
                                      + ptParentOrientation->tY.vY * Graph_tNode.tPos.vY
                                      + ptParentOrientation->tX.vY * Graph_tNode.tPos.vX;
      Real64x3_RotateInverse_tTemp.vZ = ptParentOrientation->tZ.vZ * Graph_tNode.tPos.vZ
                                      + ptParentOrientation->tY.vZ * Graph_tNode.tPos.vY
                                      + ptParentOrientation->tX.vZ * Graph_tNode.tPos.vX;
      qmemcpy(&Graph_tNode.tPos, &Real64x3_RotateInverse_tTemp, sizeof(Graph_tNode.tPos));
    }
  }
}

// source: h/2/graph.c:2388  [size]
void __cdecl Graph_NodeGammaCallback(struct GraphStreamCallbackContext_s *ptCallbackContext)
{
  GraphStream_LoadParameter(ptCallbackContext, &Graph_tNode.vGamma, 0);
}

// source: h/2/graph.c:2401  [size]
void __cdecl Graph_NodeRadiusCallback(struct GraphStreamCallbackContext_s *ptCallbackContext)
{
  GraphStream_LoadParameter(ptCallbackContext, &Graph_tNode.vRadius, 0);
}

// source: h/2/graph.c:2414  [anchor-mhash]
void __cdecl Graph_NodeMaterialCallback(struct GraphStreamCallbackContext_s *ptCallbackContext)
{
  int nMaterialID; // [esp+0h] [ebp-4h] BYREF

  nMaterialID = -1;
  GraphStream_LoadParameter(ptCallbackContext, &nMaterialID, 0);
  if ( nMaterialID == -1 )
    Graph_tNode.ptGroundMaterial = nullptr;
  else
    Graph_tNode.ptGroundMaterial = World_ptActiveWorld->aptQMaterial[nMaterialID];
}

// source: h/2/graph.c:2440  [anchor-mhash]
void __cdecl Graph_NodeLightValueCallback(struct GraphStreamCallbackContext_s *ptCallbackContext)
{
  float vLightValue; // [esp+0h] [ebp-4h] BYREF

  vLightValue = -1.0;
  GraphStream_LoadParameter(ptCallbackContext, &vLightValue, 0);
  if ( vLightValue <= 0.0 )
    Graph_tNode.vLightValue = 0.0;
  else
    Graph_tNode.vLightValue = vLightValue;
}

// source: h/2/graph.c:2459  [anchor-mhash]
void __cdecl Graph_NodeTerrainCallback(struct GraphStreamCallbackContext_s *ptCallbackContext)
{
  int nTerrain; // [esp+0h] [ebp-4h] BYREF

  nTerrain = -1;
  GraphStream_LoadParameter(ptCallbackContext, &nTerrain, 0);
  Graph_tNode.isTerrainNode = nTerrain == -1 ? 0 : nTerrain;
}

// source: h/2/graph.c:2479  [anchor-caller]
void __cdecl Graph_NodeCriteriaCallback(struct GraphStreamCallbackContext_s *ptCallbackContext)
{
  GraphStream_LoadParameter(ptCallbackContext, Graph_tNode.zCriteria, 0x100u);
  ptCallbackContext->ptCurrentGraphNode = Graph_CreateNode(
                                            ptCallbackContext->ptGraph,
                                            Graph_tNode.nID,
                                            &Graph_tNode.tPos,
                                            Graph_tNode.vGamma,
                                            Graph_tNode.vRadius,
                                            Graph_tNode.ptGroundMaterial,
                                            Graph_tNode.zCriteria,
                                            Graph_tNode.vLightValue,
                                            Graph_tNode.isTerrainNode,
                                            nullptr);
}

// source: h/2/graph.c:2503  [anchor-mhash]
void __cdecl Graph_LinkID1Callback(struct GraphStreamCallbackContext_s *ptCallbackContext)
{
  Graph_nLinkID1 = -1;
  Graph_nLinkID2 = -1;
  ptCallbackContext->ptCurrentGraphLink = nullptr;
  GraphStream_LoadParameter(ptCallbackContext, &Graph_nLinkID1, 0);
}

// source: h/2/graph.c:2521  [size]
void __cdecl Graph_LinkID2Callback(struct GraphStreamCallbackContext_s *ptCallbackContext)
{
  GraphStream_LoadParameter(ptCallbackContext, &Graph_nLinkID2, 0);
}

// source: h/2/graph.c:2536  [anchor-caller]
void __cdecl Graph_LinkTypeCallback(struct GraphStreamCallbackContext_s *ptCallbackContext)
{
  GraphStream_LoadParameter(ptCallbackContext, &Graph_nLinkType, 0);
  ptCallbackContext->ptCurrentGraphLink = Graph_CreateLink(
                                            ptCallbackContext->ptGraph,
                                            Graph_nLinkID1,
                                            Graph_nLinkID2,
                                            Graph_nLinkType);
}

// source: h/2/graph.c:2551  [anchor-hash]
unsigned int __cdecl Graph_CalculateHash(char *zStringToHash)
{
  char *v1; // esi
  char v2; // cl
  unsigned int result; // eax
  int v4; // edx

  v1 = zStringToHash;
  v2 = *zStringToHash;
  result = 0;
  v4 = 1;
  if ( v2 )
  {
    do
    {
      ++v1;
      if ( v2 >= 97 && v2 <= 122 )
        v2 -= 32;
      result += v4 * v2;
      v2 = *v1;
      v4 = (unsigned __int16)(v4 + 317);
    }
    while ( *v1 );
  }
  return result;
}

// source: h/2/graph.c:2584  [size]
struct GraphStreamCallbackItem_t *__cdecl Graph_GetCallbackFromList(
        unsigned int nHash)
{
  struct GraphStreamCallbackItem_t *result; // eax
  struct GraphStreamCallbackItem_t *ptNext; // ecx

  result = (struct GraphStreamCallbackItem_t *)Graph_tGraphStreamCallbackList.ptHead;
  ptNext = (struct GraphStreamCallbackItem_t *)Graph_tGraphStreamCallbackList.ptHead->ptNext;
  if ( !Graph_tGraphStreamCallbackList.ptHead->ptNext )
    return nullptr;
  while ( result->nHash != nHash )
  {
    result = ptNext;
    ptNext = (struct GraphStreamCallbackItem_t *)ptNext->tNode.ptNext;
    if ( !ptNext )
      return nullptr;
  }
  return result;
}

// source: h/2/graph.c:2612  [anchor-callee]
void __cdecl Graph_LoadOldGraph(struct Graph_s *ptGraph, struct GraphStream_s *ptGraphStream)
{
  #pragma pack(push, 1)
  union
  {
    struct { char v20; };
    struct { char igi2_o1[1]; char v21; };
    struct { char igi2_o2[2]; char v22; };
    struct { char igi2_o3[3]; int v23; };
    struct { char igi2_o4[10]; char v24; };
    struct { char igi2_o5[11]; struct Graph_s *v25; };
    struct { char igi2_o6[18]; char v26; };
    struct { char igi2_o7[19]; int nID2; };
    struct { char igi2_o8[26]; char v28; };
    struct { char igi2_o9[27]; int nID1; };
    struct { char igi2_o10[34]; int v30; };
    struct { char igi2_o11[38]; char v31; };
    struct { char igi2_o12[39]; int v32; };
    struct { char igi2_o13[46]; struct GraphLoadSaveContext_s tGraphLoadContext; };
    struct { char igi2_o14[50]; char v34; };
    struct { char igi2_o15[51]; int v35; };
    struct { char igi2_o16[58]; struct GraphNodeLoadSaveContext_S tLoadContext; };
    struct { char igi2_o17[66]; _BYTE v37[8]; };
    struct { char igi2_o18[74]; char v38; };
    struct { char igi2_o19[75]; _BYTE v39[24]; };
    struct { char igi2_o20[102]; struct GraphNode_s tNew; };
    struct { char igi2_o21[694]; char v41; };
    struct { char igi2_o22[695]; unsigned __int8 v42; };
    struct { char igi2_o23[696]; _BYTE v43[262]; };
    char igi2_extent[958];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  void *pxGraphNodeList; // eax
  int v4; // esi
  int v5; // eax
  void *v6; // eax
  int nMaxNodes; // esi
  int GraphNodeDataSize; // eax
  int v9; // ecx
  void (__cdecl *pfHandler)(struct Graph_s *, _DWORD); // eax
  struct File_s *ptGraphFile; // ecx
  struct File_s *v12; // ecx
  struct File_s *v13; // ecx
  unsigned int v14; // esi
  struct GraphNode_s *Node; // eax
  void (__cdecl *v16)(struct Graph_s *, struct GraphNodeLoadSaveContext_S *); // eax
  int v17; // esi
  int v18; // ecx
  void (__cdecl *v19)(struct Graph_s *, struct GraphLoadSaveContext_s *); // eax

  File_atDevice[ptGraphStream->ptGraphFile->eDeviceID].pfRead(
    ptGraphStream->ptGraphFile->eDeviceID,
    ptGraphStream->ptGraphFile,
    &igi2_frame.v31,
    5u);
  File_atDevice[ptGraphStream->ptGraphFile->eDeviceID].pfRead(
    ptGraphStream->ptGraphFile->eDeviceID,
    ptGraphStream->ptGraphFile,
    &igi2_frame.v22,
    5u);
  ptGraph->nMaxNodes = igi2_frame.v23;
  File_atDevice[ptGraphStream->ptGraphFile->eDeviceID].pfRead(
    ptGraphStream->ptGraphFile->eDeviceID,
    ptGraphStream->ptGraphFile,
    &igi2_frame.v22,
    5u);
  pxGraphNodeList = ptGraph->pxGraphNodeList;
  if ( pxGraphNodeList )
  {
    v4 = *(_DWORD *)(((int)pxGraphNodeList - 4) & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v4);
    memset(*(void **)(v4 + 8), 0xCDu, *(_DWORD *)(v4 + 16));
    free((void *)v4);
    ptGraph->pxGraphNodeList = nullptr;
  }
  v5 = 0;
  while ( ptGraph->tQTask.eQTaskType != Graph_atGraphNodeDataSize[v5].eGraphQTaskType )
  {
    if ( ++v5 >= 4 )
    {
      LDebug_Error("Undefined GraphNodeDataSize");
      abort();
    }
  }
  v6 = Mem_AllocFn(Graph_atGraphNodeDataSize[v5].nDataSize * ptGraph->nMaxNodes, 4);
  nMaxNodes = ptGraph->nMaxNodes;
  ptGraph->pxGraphNodeList = v6;
  if ( v6 )
  {
    GraphNodeDataSize = Graph_GetGraphNodeDataSize((int)ptGraph);
    if ( nMaxNodes > 0 )
    {
      v9 = 0;
      do
      {
        *(_DWORD *)((char *)ptGraph->pxGraphNodeList + v9) = -1;
        v9 += GraphNodeDataSize;
        --nMaxNodes;
      }
      while ( nMaxNodes );
    }
  }
  pfHandler = (void (__cdecl *)(struct Graph_s *, _DWORD))QTask_aatQTaskFinalEvent[Graph_eInitDataQTaskEvent][ptGraph->tQTask.eQTaskType].pfHandler;
  if ( pfHandler )
    pfHandler(ptGraph, 0);
  if ( igi2_frame.v32 > 0 )
  {
    igi2_frame.v30 = igi2_frame.v32;
    do
    {
      File_atDevice[ptGraphStream->ptGraphFile->eDeviceID].pfRead(
        ptGraphStream->ptGraphFile->eDeviceID,
        ptGraphStream->ptGraphFile,
        &igi2_frame.v34,
        5u);
      ptGraphFile = ptGraphStream->ptGraphFile;
      igi2_frame.tNew.nID = igi2_frame.v35;
      File_atDevice[ptGraphFile->eDeviceID].pfRead(ptGraphFile->eDeviceID, ptGraphFile, &igi2_frame.v38, 25u);
      qmemcpy(&igi2_frame.tNew.tPos, igi2_frame.v39, sizeof(igi2_frame.tNew.tPos));
      File_atDevice[ptGraphStream->ptGraphFile->eDeviceID].pfRead(
        ptGraphStream->ptGraphFile->eDeviceID,
        ptGraphStream->ptGraphFile,
        &igi2_frame.v24,
        5u);
      v12 = ptGraphStream->ptGraphFile;
      LODWORD(igi2_frame.tNew.vGamma) = igi2_frame.v25;
      File_atDevice[v12->eDeviceID].pfRead(v12->eDeviceID, v12, &igi2_frame.v28, 5u);
      v13 = ptGraphStream->ptGraphFile;
      LODWORD(igi2_frame.tNew.vRadius) = igi2_frame.nID1;
      File_atDevice[v13->eDeviceID].pfRead(v13->eDeviceID, v13, &igi2_frame.v21, 1u);
      File_atDevice[ptGraphStream->ptGraphFile->eDeviceID].pfSeek(
        ptGraphStream->ptGraphFile->eDeviceID,
        ptGraphStream->ptGraphFile,
        -1,
        1);
      if ( igi2_frame.v21 == 6 )
        File_atDevice[ptGraphStream->ptGraphFile->eDeviceID].pfRead(
          ptGraphStream->ptGraphFile->eDeviceID,
          ptGraphStream->ptGraphFile,
          igi2_frame.v37,
          5u);
      File_atDevice[ptGraphStream->ptGraphFile->eDeviceID].pfRead(
        ptGraphStream->ptGraphFile->eDeviceID,
        ptGraphStream->ptGraphFile,
        &igi2_frame.v20,
        1u);
      File_atDevice[ptGraphStream->ptGraphFile->eDeviceID].pfSeek(
        ptGraphStream->ptGraphFile->eDeviceID,
        ptGraphStream->ptGraphFile,
        -1,
        1);
      if ( igi2_frame.v20 == 5 )
      {
        File_atDevice[ptGraphStream->ptGraphFile->eDeviceID].pfRead(
          ptGraphStream->ptGraphFile->eDeviceID,
          ptGraphStream->ptGraphFile,
          &igi2_frame.v26,
          5u);
        if ( igi2_frame.nID2 != -1 )
          igi2_frame.tNew.ptGroundMaterial = World_ptActiveWorld->aptQMaterial[igi2_frame.nID2];
      }
      File_atDevice[ptGraphStream->ptGraphFile->eDeviceID].pfRead(
        ptGraphStream->ptGraphFile->eDeviceID,
        ptGraphStream->ptGraphFile,
        &igi2_frame.v41,
        2u);
      v14 = igi2_frame.v42;
      File_atDevice[ptGraphStream->ptGraphFile->eDeviceID].pfRead(
        ptGraphStream->ptGraphFile->eDeviceID,
        ptGraphStream->ptGraphFile,
        igi2_frame.v43,
        igi2_frame.v42);
      qmemcpy(igi2_frame.tNew.zCriteria, igi2_frame.v43, v14);
      Node = Graph_CreateNode(
               ptGraph,
               igi2_frame.tNew.nID,
               &igi2_frame.tNew.tPos,
               igi2_frame.tNew.vGamma,
               igi2_frame.tNew.vRadius,
               igi2_frame.tNew.ptGroundMaterial,
               igi2_frame.tNew.zCriteria,
               0.0,
               0,
               nullptr);
      if ( Node )
      {
        igi2_frame.tLoadContext.ptNode = Node;
        v16 = (void (__cdecl *)(struct Graph_s *, struct GraphNodeLoadSaveContext_S *))QTask_aatQTaskFinalEvent[Graph_eLoadNodeQTaskEvent][ptGraph->tQTask.eQTaskType].pfHandler;
        igi2_frame.tLoadContext.ptGraphStream = ptGraphStream;
        if ( v16 )
          v16(ptGraph, &igi2_frame.tLoadContext);
      }
      --igi2_frame.v30;
    }
    while ( igi2_frame.v30 );
  }
  v17 = igi2_frame.v23;
  if ( igi2_frame.v23 > 0 )
  {
    do
    {
      File_atDevice[ptGraphStream->ptGraphFile->eDeviceID].pfRead(
        ptGraphStream->ptGraphFile->eDeviceID,
        ptGraphStream->ptGraphFile,
        &igi2_frame.v24,
        5u);
      File_atDevice[ptGraphStream->ptGraphFile->eDeviceID].pfRead(
        ptGraphStream->ptGraphFile->eDeviceID,
        ptGraphStream->ptGraphFile,
        &igi2_frame.v28,
        5u);
      File_atDevice[ptGraphStream->ptGraphFile->eDeviceID].pfRead(
        ptGraphStream->ptGraphFile->eDeviceID,
        ptGraphStream->ptGraphFile,
        &igi2_frame.v26,
        5u);
      Graph_CreateLink(ptGraph, (int)igi2_frame.v25, igi2_frame.nID1, igi2_frame.nID2);
      --v17;
    }
    while ( v17 );
    v17 = igi2_frame.v23;
  }
  v18 = ptGraph->tQTask.eQTaskType + 511 * Graph_eLoadGraphQTaskEvent;
  ptGraph->nNumNodes = igi2_frame.v32;
  ptGraph->nNumLinks = v17;
  v19 = (void (__cdecl *)(struct Graph_s *, struct GraphLoadSaveContext_s *))QTask_aatQTaskFinalEvent[0][v18].pfHandler;
  igi2_frame.tGraphLoadContext.ptGraphStream = ptGraphStream;
  if ( v19 )
    v19(ptGraph, &igi2_frame.tGraphLoadContext);
}

// source: h/2/graph.c:2737  [anchor-strings]
struct GraphStreamCallbackContext_s *__cdecl GraphStream_LoadParameter(
        struct GraphStreamCallbackContext_s *ptCallbackContext,
        void *pxData,
        unsigned int nDataSize)
{
  struct GraphStreamCallbackContext_s *result; // eax

  switch ( ptCallbackContext->eParameterType )
  {
    case GRAPHSTREAM_PARAMETERTYPE_UINT8:
      LOBYTE(result) = GraphStream_Getuint8(ptCallbackContext->ptGraphStream, (unsigned __int8 *)pxData);
      break;
    case GRAPHSTREAM_PARAMETERTYPE_INT8:
      LOBYTE(result) = GraphStream_Getint8(ptCallbackContext->ptGraphStream, (char *)pxData);
      break;
    case GRAPHSTREAM_PARAMETERTYPE_UINT16:
      LOBYTE(result) = GraphStream_Getuint16(ptCallbackContext->ptGraphStream, (unsigned __int16 *)pxData);
      break;
    case GRAPHSTREAM_PARAMETERTYPE_INT16:
      LOBYTE(result) = GraphStream_Getint16(ptCallbackContext->ptGraphStream, (__int16 *)pxData);
      break;
    case GRAPHSTREAM_PARAMETERTYPE_UINT32:
      LOBYTE(result) = GraphStream_Getuint32(ptCallbackContext->ptGraphStream, (unsigned int *)pxData);
      break;
    case GRAPHSTREAM_PARAMETERTYPE_INT32:
      LOBYTE(result) = GraphStream_Getint32(ptCallbackContext->ptGraphStream, (int *)pxData);
      break;
    case GRAPHSTREAM_PARAMETERTYPE_REAL32:
      LOBYTE(result) = GraphStream_Getreal32(ptCallbackContext->ptGraphStream, (float *)pxData);
      break;
    case GRAPHSTREAM_PARAMETERTYPE_REAL64:
      LOBYTE(result) = GraphStream_Getreal64(ptCallbackContext->ptGraphStream, (double *)pxData);
      break;
    case GRAPHSTREAM_PARAMETERTYPE_REAL64X3:
      LOBYTE(result) = GraphStream_Getreal64x3(ptCallbackContext->ptGraphStream, (struct real64x3_t *)pxData);
      break;
    case GRAPHSTREAM_PARAMETERTYPE_STRING:
      LOBYTE(result) = GraphStream_GetString(ptCallbackContext->ptGraphStream, (char *)pxData, nDataSize);
      break;
    case GRAPHSTREAM_PARAMETERTYPE_BUFFER:
      LOBYTE(result) = GraphStream_GetBuffer(ptCallbackContext->ptGraphStream, pxData, nDataSize);
      break;
    default:
      LDebug_Error("Unknown GRAPHSTREAM_PARAMETERTYPE");
      abort();
  }
  return result;
}

// source: h/2/graph.c:2790  [anchor-caller]
char *__cdecl Graph_AddGraphStreamCallback(
        char *zCallbackName,
        enum GraphStreamParameterType_e eParameterType,
        void (__cdecl *pfCallback)(struct GraphStreamCallbackContext_s *))
{
  struct Node_s *v3; // edx
  char *result; // eax
  char *ptNext; // ecx
  _DWORD **v6; // eax

  v3 = (struct Node_s *)Graph_CalculateHash(zCallbackName);
  result = (char *)Graph_tGraphStreamCallbackList.ptHead;
  ptNext = (char *)Graph_tGraphStreamCallbackList.ptHead->ptNext;
  if ( Graph_tGraphStreamCallbackList.ptHead->ptNext )
  {
    while ( *((struct Node_s **)result + 2) != v3 )
    {
      result = ptNext;
      ptNext = *(char **)ptNext;
      if ( !ptNext )
        goto LABEL_4;
    }
  }
  else
  {
LABEL_4:
    result = (char *)Graph_tGraphStreamCallbackFreeList.ptHead;
    if ( Graph_tGraphStreamCallbackFreeList.ptHead->ptNext )
    {
      Graph_tGraphStreamCallbackFreeList.ptHead[1].ptNext = v3;
      *((_DWORD *)result + 3) = eParameterType;
      *((_DWORD *)result + 4) = pfCallback;
      v6 = Node_Remove((_DWORD **)result);
      v6[1] = nullptr;
      *v6 = nullptr;
      return (char *)List_AddTail(v6, (int)&Graph_tGraphStreamCallbackList);
    }
  }
  return result;
}

// source: h/2/graph.c:2842  [anchor-caller]
char *__cdecl Graph_SaveGraphStreamItem(
        struct GraphStream_s *ptStream,
        char *zCallbackName,
        enum GraphStreamParameterType_e eParameterType,
        void *pxData,
        int nDataSize)
{
  #pragma pack(push, 1)
  union
  {
    struct { _BYTE v10[4]; };
    struct { char igi2_o1[4]; char v11; };
    struct { char igi2_o2[5]; unsigned int v12; };
    char igi2_extent[12];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  unsigned int v6; // eax
  struct File_s *ptGraphFile; // ecx
  struct File_s *v8; // ecx
  char *result; // eax

  igi2_frame.v11 = 4;
  v6 = Graph_CalculateHash(zCallbackName);
  ptGraphFile = ptStream->ptGraphFile;
  igi2_frame.v12 = v6;
  File_atDevice[ptGraphFile->eDeviceID].pfWrite(ptGraphFile->eDeviceID, ptGraphFile, &igi2_frame.v11, 5u);
  v8 = ptStream->ptGraphFile;
  igi2_frame.v10[0] = 0;
  igi2_frame.v10[1] = eParameterType;
  result = (char *)File_atDevice[v8->eDeviceID].pfWrite(v8->eDeviceID, v8, igi2_frame.v10, 2u);
  switch ( eParameterType )
  {
    case GRAPHSTREAM_PARAMETERTYPE_UINT8:
      LOBYTE(result) = GraphStream_Adduint8(ptStream, *(_BYTE *)pxData);
      break;
    case GRAPHSTREAM_PARAMETERTYPE_INT8:
      LOBYTE(result) = GraphStream_Addint8(ptStream, *(_BYTE *)pxData);
      break;
    case GRAPHSTREAM_PARAMETERTYPE_UINT16:
      LOBYTE(result) = GraphStream_Adduint16(ptStream, *(_WORD *)pxData);
      break;
    case GRAPHSTREAM_PARAMETERTYPE_INT16:
      LOBYTE(result) = GraphStream_Addint16(ptStream, *(_WORD *)pxData);
      break;
    case GRAPHSTREAM_PARAMETERTYPE_UINT32:
      LOBYTE(result) = GraphStream_Adduint32(ptStream, *(_DWORD *)pxData);
      break;
    case GRAPHSTREAM_PARAMETERTYPE_INT32:
      LOBYTE(result) = GraphStream_Addint32(ptStream, *(_DWORD *)pxData);
      break;
    case GRAPHSTREAM_PARAMETERTYPE_REAL32:
      LOBYTE(result) = GraphStream_Addreal32(ptStream, *(float *)pxData);
      break;
    case GRAPHSTREAM_PARAMETERTYPE_REAL64:
      LOBYTE(result) = GraphStream_Addreal64(ptStream, *(double *)pxData);
      break;
    case GRAPHSTREAM_PARAMETERTYPE_REAL64X3:
      LOBYTE(result) = GraphStream_Addreal64x3(ptStream, (struct real64x3_t *)pxData);
      break;
    case GRAPHSTREAM_PARAMETERTYPE_STRING:
      LOBYTE(result) = GraphStream_AddString(ptStream, (char *)pxData);
      break;
    case GRAPHSTREAM_PARAMETERTYPE_BUFFER:
      LOBYTE(result) = GraphStream_AddBuffer(ptStream, pxData, nDataSize);
      break;
    default:
      return result;
  }
  return result;
}

// source: h/2/graph.c:2904  [anchor-strings]
char *__cdecl Graph_ParseGraphStream(struct Graph_s *ptGraph, char *zGraphStreamName)
{
  #pragma pack(push, 1)
  union
  {
    struct { _BYTE v8[4]; };
    struct { char igi2_o1[4]; unsigned int nHeader; };
    struct { char igi2_o2[8]; char v10; };
    struct { char igi2_o3[9]; struct Node_s *v11; };
    struct { char igi2_o4[16]; struct GraphStream_s tGraphStream; };
    struct { char igi2_o5[24]; struct GraphStreamCallbackContext_s tCallbackContext; };
    char igi2_extent[48];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct File_s *v4; // eax
  char *result; // eax
  struct Node_s *ptHead; // esi
  struct Node_s *ptNext; // eax

  v4 = File_New(zGraphStreamName, "r");
  igi2_frame.tGraphStream.ptGraphFile = v4;
  if ( !v4 )
  {
    LDebug_Error("Unable to open %s for reading", zGraphStreamName);
    abort();
  }
  igi2_frame.tCallbackContext.ptGraphStream = &igi2_frame.tGraphStream;
  File_atDevice[v4->eDeviceID].pfRead(v4->eDeviceID, v4, &igi2_frame.nHeader, 4u);
  if ( igi2_frame.nHeader == -1122868 )
  {
    igi2_frame.tCallbackContext.ptGraph = ptGraph;
    igi2_frame.tCallbackContext.ptCurrentGraphNode = nullptr;
    igi2_frame.tCallbackContext.ptCurrentGraphLink = nullptr;
    for ( result = (char *)File_atDevice[igi2_frame.tGraphStream.ptGraphFile->eDeviceID].pfisEOF(
                             igi2_frame.tGraphStream.ptGraphFile->eDeviceID,
                             igi2_frame.tGraphStream.ptGraphFile);
          !result;
          result = (char *)File_atDevice[igi2_frame.tGraphStream.ptGraphFile->eDeviceID].pfisEOF(
                             igi2_frame.tGraphStream.ptGraphFile->eDeviceID,
                             igi2_frame.tGraphStream.ptGraphFile) )
    {
      File_atDevice[igi2_frame.tGraphStream.ptGraphFile->eDeviceID].pfRead(
        igi2_frame.tGraphStream.ptGraphFile->eDeviceID,
        igi2_frame.tGraphStream.ptGraphFile,
        &igi2_frame.v10,
        5u);
      if ( File_atDevice[igi2_frame.tGraphStream.ptGraphFile->eDeviceID].pfisEOF(
             igi2_frame.tGraphStream.ptGraphFile->eDeviceID,
             igi2_frame.tGraphStream.ptGraphFile) == false )
      {
        ptHead = Graph_tGraphStreamCallbackList.ptHead;
        ptNext = Graph_tGraphStreamCallbackList.ptHead->ptNext;
        if ( Graph_tGraphStreamCallbackList.ptHead->ptNext )
        {
          while ( ptHead[1].ptNext != igi2_frame.v11 )
          {
            ptHead = ptNext;
            ptNext = ptNext->ptNext;
            if ( !ptNext )
              goto LABEL_9;
          }
          File_atDevice[igi2_frame.tGraphStream.ptGraphFile->eDeviceID].pfRead(
            igi2_frame.tGraphStream.ptGraphFile->eDeviceID,
            igi2_frame.tGraphStream.ptGraphFile,
            igi2_frame.v8,
            2u);
          igi2_frame.tCallbackContext.eParameterType = igi2_frame.v8[1];
          ((void (__cdecl *)(struct GraphStreamCallbackContext_s *))ptHead[2].ptNext)(&igi2_frame.tCallbackContext);
        }
        else
        {
LABEL_9:
          GraphStream_SkipStreamItems(&igi2_frame.tGraphStream, 2);
        }
      }
    }
  }
  else
  {
    File_atDevice[igi2_frame.tGraphStream.ptGraphFile->eDeviceID].pfSeek(
      igi2_frame.tGraphStream.ptGraphFile->eDeviceID,
      igi2_frame.tGraphStream.ptGraphFile,
      0,
      0);
    Graph_LoadOldGraph(ptGraph, &igi2_frame.tGraphStream);
  }
  if ( igi2_frame.tGraphStream.ptGraphFile != &File_tDummyAsyncFile )
    return ((char *(__cdecl *)(int, struct File_s *))File_atDevice[igi2_frame.tGraphStream.ptGraphFile->eDeviceID].pfDelete)(
             igi2_frame.tGraphStream.ptGraphFile->eDeviceID,
             igi2_frame.tGraphStream.ptGraphFile);
  File_tDummyAsyncFile.isAsync = false;
  return result;
}

// source: h/2/graph.c:2992  [anchor-strings]
char *__cdecl Graph_SaveGraphStream(struct Graph_s *ptGraph, char *zGraphStreamName)
{
  #pragma pack(push, 1)
  union
  {
    struct { char v29; };
    struct { char igi2_o1[1]; char v30; };
    struct { char igi2_o2[4]; _BYTE v31[4]; };
    struct { char igi2_o3[8]; _BYTE v32[4]; };
    struct { char igi2_o4[12]; _BYTE v33[4]; };
    struct { char igi2_o5[16]; _BYTE v34[4]; };
    struct { char igi2_o6[20]; char v35; };
    struct { char igi2_o7[21]; char v36; };
    struct { char igi2_o8[24]; char v37; };
    struct { char igi2_o9[25]; char v38; };
    struct { char igi2_o10[28]; char v39; };
    struct { char igi2_o11[29]; char v40; };
    struct { char igi2_o12[32]; struct GraphLoadSaveContext_s tLoadSaveContext; };
    struct { char igi2_o13[36]; _DWORD ptTempLink[2]; };
    struct { char igi2_o14[44]; unsigned int nHeader; };
    struct { char igi2_o15[48]; char v44; };
    struct { char igi2_o16[49]; unsigned int v45; };
    struct { char igi2_o17[56]; char v46; };
    struct { char igi2_o18[57]; unsigned int v47; };
    struct { char igi2_o19[64]; char v48; };
    struct { char igi2_o20[65]; unsigned int v49; };
    struct { char igi2_o21[72]; char v50; };
    struct { char igi2_o22[73]; unsigned int v51; };
    struct { char igi2_o23[80]; char v52; };
    struct { char igi2_o24[81]; unsigned int v53; };
    struct { char igi2_o25[88]; char v54; };
    struct { char igi2_o26[89]; unsigned int v55; };
    struct { char igi2_o27[96]; char v56; };
    struct { char igi2_o28[97]; unsigned int v57; };
    struct { char igi2_o29[104]; char v58; };
    struct { char igi2_o30[105]; unsigned int v59; };
    struct { char igi2_o31[112]; struct GraphStream_s tGraphStream; };
    struct { char igi2_o32[120]; int nMaterial; };
    struct { char igi2_o33[128]; struct GraphNodeLoadSaveContext_S tSaveContext; };
    char igi2_extent[136];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct Graph_s *v2; // edi
  char *result; // eax
  int eQTaskType; // edx
  void (__cdecl *pfHandler)(struct Graph_s *, struct GraphLoadSaveContext_s *); // eax
  int nMaxNodes; // eax
  int v7; // ebp
  struct GraphNode_s *v8; // esi
  struct QMaterial_t *ptGroundMaterial; // eax
  int v10; // ecx
  struct QMaterial_t **i; // edx
  void (__cdecl *v12)(struct Graph_s *, struct GraphNodeLoadSaveContext_S *); // eax
  struct GraphLink_s *ptHead; // edi
  char *v14; // esi
  unsigned int v15; // edx
  int v16; // eax
  char v17; // cl
  unsigned int nID1; // eax
  char *v19; // ebp
  unsigned int v20; // esi
  int v21; // eax
  char v22; // cl
  unsigned int nID2; // eax
  char *v24; // esi
  unsigned int v25; // ebp
  int v26; // eax
  char v27; // cl
  unsigned int eType; // eax

  v2 = ptGraph;
  igi2_frame.nHeader = -1122868;
  result = (char *)File_New(zGraphStreamName, "w");
  igi2_frame.tGraphStream.ptGraphFile = (struct File_s *)result;
  if ( result )
  {
    igi2_frame.tLoadSaveContext.ptGraphStream = &igi2_frame.tGraphStream;
    File_atDevice[*(_DWORD *)result].pfWrite(*(_DWORD *)result, (struct File_s *)result, &igi2_frame.nHeader, 4u);
    LOBYTE(igi2_frame.ptTempLink[0]) = 4;
    *(_DWORD *)((char *)igi2_frame.ptTempLink + 1) = Graph_CalculateHash("nMaxNodes");
    File_atDevice[igi2_frame.tGraphStream.ptGraphFile->eDeviceID].pfWrite(
      igi2_frame.tGraphStream.ptGraphFile->eDeviceID,
      igi2_frame.tGraphStream.ptGraphFile,
      igi2_frame.ptTempLink,
      5u);
    igi2_frame.v29 = 0;
    igi2_frame.v30 = 5;
    File_atDevice[igi2_frame.tGraphStream.ptGraphFile->eDeviceID].pfWrite(
      igi2_frame.tGraphStream.ptGraphFile->eDeviceID,
      igi2_frame.tGraphStream.ptGraphFile,
      &igi2_frame.v29,
      2u);
    GraphStream_Addint32(&igi2_frame.tGraphStream, ptGraph->nMaxNodes);
    eQTaskType = ptGraph->tQTask.eQTaskType;
    igi2_frame.tLoadSaveContext.ptGraphStream = &igi2_frame.tGraphStream;
    pfHandler = (void (__cdecl *)(struct Graph_s *, struct GraphLoadSaveContext_s *))QTask_aatQTaskFinalEvent[Graph_eSaveGraphQTaskEvent][eQTaskType].pfHandler;
    if ( pfHandler )
      pfHandler(ptGraph, &igi2_frame.tLoadSaveContext);
    nMaxNodes = ptGraph->nMaxNodes;
    v7 = 0;
    for ( igi2_frame.ptTempLink[0] = 0; v7 < nMaxNodes; igi2_frame.ptTempLink[0] = v7 )
    {
      if ( v2->pxGraphNodeList )
      {
        if ( v7 < nMaxNodes && v7 >= 0 )
        {
          v8 = (struct GraphNode_s *)((char *)v2->pxGraphNodeList + v7 * Graph_GetGraphNodeDataSize((int)v2));
          if ( v8->nID != -1 )
          {
            igi2_frame.nMaterial = -1;
            igi2_frame.v44 = 4;
            igi2_frame.v45 = Graph_CalculateHash("nNodeID");
            File_atDevice[igi2_frame.tGraphStream.ptGraphFile->eDeviceID].pfWrite(
              igi2_frame.tGraphStream.ptGraphFile->eDeviceID,
              igi2_frame.tGraphStream.ptGraphFile,
              &igi2_frame.v44,
              5u);
            igi2_frame.v29 = 0;
            igi2_frame.v30 = 5;
            File_atDevice[igi2_frame.tGraphStream.ptGraphFile->eDeviceID].pfWrite(
              igi2_frame.tGraphStream.ptGraphFile->eDeviceID,
              igi2_frame.tGraphStream.ptGraphFile,
              &igi2_frame.v29,
              2u);
            GraphStream_Addint32(&igi2_frame.tGraphStream, v8->nID);
            igi2_frame.v46 = 4;
            igi2_frame.v47 = Graph_CalculateHash("tNodePosition");
            File_atDevice[igi2_frame.tGraphStream.ptGraphFile->eDeviceID].pfWrite(
              igi2_frame.tGraphStream.ptGraphFile->eDeviceID,
              igi2_frame.tGraphStream.ptGraphFile,
              &igi2_frame.v46,
              5u);
            igi2_frame.v31[0] = 0;
            igi2_frame.v31[1] = 8;
            File_atDevice[igi2_frame.tGraphStream.ptGraphFile->eDeviceID].pfWrite(
              igi2_frame.tGraphStream.ptGraphFile->eDeviceID,
              igi2_frame.tGraphStream.ptGraphFile,
              igi2_frame.v31,
              2u);
            GraphStream_Addreal64x3(&igi2_frame.tGraphStream, &v8->tPos);
            igi2_frame.v48 = 4;
            igi2_frame.v49 = Graph_CalculateHash("vNodeGamma");
            File_atDevice[igi2_frame.tGraphStream.ptGraphFile->eDeviceID].pfWrite(
              igi2_frame.tGraphStream.ptGraphFile->eDeviceID,
              igi2_frame.tGraphStream.ptGraphFile,
              &igi2_frame.v48,
              5u);
            igi2_frame.v32[0] = 0;
            igi2_frame.v32[1] = 6;
            File_atDevice[igi2_frame.tGraphStream.ptGraphFile->eDeviceID].pfWrite(
              igi2_frame.tGraphStream.ptGraphFile->eDeviceID,
              igi2_frame.tGraphStream.ptGraphFile,
              igi2_frame.v32,
              2u);
            GraphStream_Addreal32(&igi2_frame.tGraphStream, v8->vGamma);
            igi2_frame.v50 = 4;
            igi2_frame.v51 = Graph_CalculateHash("vNodeRadius");
            File_atDevice[igi2_frame.tGraphStream.ptGraphFile->eDeviceID].pfWrite(
              igi2_frame.tGraphStream.ptGraphFile->eDeviceID,
              igi2_frame.tGraphStream.ptGraphFile,
              &igi2_frame.v50,
              5u);
            igi2_frame.v33[0] = 0;
            igi2_frame.v33[1] = 6;
            File_atDevice[igi2_frame.tGraphStream.ptGraphFile->eDeviceID].pfWrite(
              igi2_frame.tGraphStream.ptGraphFile->eDeviceID,
              igi2_frame.tGraphStream.ptGraphFile,
              igi2_frame.v33,
              2u);
            GraphStream_Addreal32(&igi2_frame.tGraphStream, v8->vRadius);
            ptGroundMaterial = v8->ptGroundMaterial;
            if ( ptGroundMaterial )
            {
              v10 = 0;
              for ( i = World_ptActiveWorld->aptQMaterial; ; ++i )
              {
                if ( v10 >= 64 )
                {
                  LDebug_Error((char *)&stru_6A4CDC.tWorkQString.tPrivate.patQStringChar);
                  abort();
                }
                if ( *i == ptGroundMaterial )
                  break;
                ++v10;
              }
              igi2_frame.nMaterial = v10;
            }
            igi2_frame.v52 = 4;
            igi2_frame.v53 = Graph_CalculateHash("nNodeMaterial");
            File_atDevice[igi2_frame.tGraphStream.ptGraphFile->eDeviceID].pfWrite(
              igi2_frame.tGraphStream.ptGraphFile->eDeviceID,
              igi2_frame.tGraphStream.ptGraphFile,
              &igi2_frame.v52,
              5u);
            igi2_frame.v34[0] = 0;
            igi2_frame.v34[1] = 5;
            File_atDevice[igi2_frame.tGraphStream.ptGraphFile->eDeviceID].pfWrite(
              igi2_frame.tGraphStream.ptGraphFile->eDeviceID,
              igi2_frame.tGraphStream.ptGraphFile,
              igi2_frame.v34,
              2u);
            GraphStream_Addint32(&igi2_frame.tGraphStream, igi2_frame.nMaterial);
            igi2_frame.v54 = 4;
            igi2_frame.v55 = Graph_CalculateHash("vNodeLightValue");
            File_atDevice[igi2_frame.tGraphStream.ptGraphFile->eDeviceID].pfWrite(
              igi2_frame.tGraphStream.ptGraphFile->eDeviceID,
              igi2_frame.tGraphStream.ptGraphFile,
              &igi2_frame.v54,
              5u);
            igi2_frame.v35 = 0;
            igi2_frame.v36 = 6;
            File_atDevice[igi2_frame.tGraphStream.ptGraphFile->eDeviceID].pfWrite(
              igi2_frame.tGraphStream.ptGraphFile->eDeviceID,
              igi2_frame.tGraphStream.ptGraphFile,
              &igi2_frame.v35,
              2u);
            GraphStream_Addreal32(&igi2_frame.tGraphStream, v8->vLightValue);
            igi2_frame.v56 = 4;
            igi2_frame.v57 = Graph_CalculateHash("nNodeOnTerrain");
            File_atDevice[igi2_frame.tGraphStream.ptGraphFile->eDeviceID].pfWrite(
              igi2_frame.tGraphStream.ptGraphFile->eDeviceID,
              igi2_frame.tGraphStream.ptGraphFile,
              &igi2_frame.v56,
              5u);
            igi2_frame.v37 = 0;
            igi2_frame.v38 = 5;
            File_atDevice[igi2_frame.tGraphStream.ptGraphFile->eDeviceID].pfWrite(
              igi2_frame.tGraphStream.ptGraphFile->eDeviceID,
              igi2_frame.tGraphStream.ptGraphFile,
              &igi2_frame.v37,
              2u);
            GraphStream_Addint32(&igi2_frame.tGraphStream, v8->isTerrainNode);
            igi2_frame.v58 = 4;
            igi2_frame.v59 = Graph_CalculateHash("nNodeCriteria");
            File_atDevice[igi2_frame.tGraphStream.ptGraphFile->eDeviceID].pfWrite(
              igi2_frame.tGraphStream.ptGraphFile->eDeviceID,
              igi2_frame.tGraphStream.ptGraphFile,
              &igi2_frame.v58,
              5u);
            igi2_frame.v39 = 0;
            igi2_frame.v40 = 9;
            File_atDevice[igi2_frame.tGraphStream.ptGraphFile->eDeviceID].pfWrite(
              igi2_frame.tGraphStream.ptGraphFile->eDeviceID,
              igi2_frame.tGraphStream.ptGraphFile,
              &igi2_frame.v39,
              2u);
            GraphStream_AddString(&igi2_frame.tGraphStream, v8->zCriteria);
            v2 = ptGraph;
            v12 = (void (__cdecl *)(struct Graph_s *, struct GraphNodeLoadSaveContext_S *))QTask_aatQTaskFinalEvent[Graph_eSaveNodeQTaskEvent][ptGraph->tQTask.eQTaskType].pfHandler;
            igi2_frame.tSaveContext.ptNode = v8;
            igi2_frame.tSaveContext.ptGraphStream = &igi2_frame.tGraphStream;
            if ( v12 )
              v12(ptGraph, &igi2_frame.tSaveContext);
            v7 = igi2_frame.ptTempLink[0];
          }
        }
      }
      nMaxNodes = v2->nMaxNodes;
      ++v7;
    }
    ptHead = v2->tGraphLinkList.ptHead;
    result = (char *)ptHead->ptNext;
    for ( igi2_frame.ptTempLink[0] = ptHead->ptNext; igi2_frame.ptTempLink[0]; igi2_frame.ptTempLink[0] = *(_DWORD *)igi2_frame.ptTempLink[0] )
    {
      v14 = (char *)&unk_6863E8;
      v15 = 0;
      v16 = 1;
      do
      {
        v17 = *v14++;
        if ( v17 >= 97 && v17 <= 122 )
          v17 -= 32;
        v15 += v16 * v17;
        v16 = (unsigned __int16)(v16 + 317);
      }
      while ( *v14 );
      igi2_frame.v59 = v15;
      igi2_frame.v58 = 4;
      File_atDevice[igi2_frame.tGraphStream.ptGraphFile->eDeviceID].pfWrite(
        igi2_frame.tGraphStream.ptGraphFile->eDeviceID,
        igi2_frame.tGraphStream.ptGraphFile,
        &igi2_frame.v58,
        5u);
      igi2_frame.v39 = 0;
      igi2_frame.v40 = 5;
      File_atDevice[igi2_frame.tGraphStream.ptGraphFile->eDeviceID].pfWrite(
        igi2_frame.tGraphStream.ptGraphFile->eDeviceID,
        igi2_frame.tGraphStream.ptGraphFile,
        &igi2_frame.v39,
        2u);
      nID1 = ptHead->nID1;
      igi2_frame.v56 = 5;
      igi2_frame.v57 = nID1;
      File_atDevice[igi2_frame.tGraphStream.ptGraphFile->eDeviceID].pfWrite(
        igi2_frame.tGraphStream.ptGraphFile->eDeviceID,
        igi2_frame.tGraphStream.ptGraphFile,
        &igi2_frame.v56,
        5u);
      v19 = (char *)&unk_6863DC;
      v20 = 0;
      v21 = 1;
      do
      {
        v22 = *v19++;
        if ( v22 >= 97 && v22 <= 122 )
          v22 -= 32;
        v20 += v21 * v22;
        v21 = (unsigned __int16)(v21 + 317);
      }
      while ( *v19 );
      igi2_frame.v55 = v20;
      igi2_frame.v54 = 4;
      File_atDevice[igi2_frame.tGraphStream.ptGraphFile->eDeviceID].pfWrite(
        igi2_frame.tGraphStream.ptGraphFile->eDeviceID,
        igi2_frame.tGraphStream.ptGraphFile,
        &igi2_frame.v54,
        5u);
      igi2_frame.v37 = 0;
      igi2_frame.v38 = 5;
      File_atDevice[igi2_frame.tGraphStream.ptGraphFile->eDeviceID].pfWrite(
        igi2_frame.tGraphStream.ptGraphFile->eDeviceID,
        igi2_frame.tGraphStream.ptGraphFile,
        &igi2_frame.v37,
        2u);
      nID2 = ptHead->nID2;
      igi2_frame.v52 = 5;
      igi2_frame.v53 = nID2;
      File_atDevice[igi2_frame.tGraphStream.ptGraphFile->eDeviceID].pfWrite(
        igi2_frame.tGraphStream.ptGraphFile->eDeviceID,
        igi2_frame.tGraphStream.ptGraphFile,
        &igi2_frame.v52,
        5u);
      v24 = (char *)&unk_6863D0;
      v25 = 0;
      v26 = 1;
      do
      {
        v27 = *v24++;
        if ( v27 >= 97 && v27 <= 122 )
          v27 -= 32;
        v25 += v26 * v27;
        v26 = (unsigned __int16)(v26 + 317);
      }
      while ( *v24 );
      igi2_frame.v50 = 4;
      igi2_frame.v51 = v25;
      File_atDevice[igi2_frame.tGraphStream.ptGraphFile->eDeviceID].pfWrite(
        igi2_frame.tGraphStream.ptGraphFile->eDeviceID,
        igi2_frame.tGraphStream.ptGraphFile,
        &igi2_frame.v50,
        5u);
      igi2_frame.v35 = 0;
      igi2_frame.v36 = 5;
      File_atDevice[igi2_frame.tGraphStream.ptGraphFile->eDeviceID].pfWrite(
        igi2_frame.tGraphStream.ptGraphFile->eDeviceID,
        igi2_frame.tGraphStream.ptGraphFile,
        &igi2_frame.v35,
        2u);
      eType = ptHead->eType;
      igi2_frame.v48 = 5;
      igi2_frame.v49 = eType;
      File_atDevice[igi2_frame.tGraphStream.ptGraphFile->eDeviceID].pfWrite(
        igi2_frame.tGraphStream.ptGraphFile->eDeviceID,
        igi2_frame.tGraphStream.ptGraphFile,
        &igi2_frame.v48,
        5u);
      ptHead = (struct GraphLink_s *)igi2_frame.ptTempLink[0];
      result = *(char **)igi2_frame.ptTempLink[0];
    }
    if ( igi2_frame.tGraphStream.ptGraphFile == &File_tDummyAsyncFile )
      File_tDummyAsyncFile.isAsync = false;
    else
      return (char *)((int (__cdecl *)(int, struct File_s *))File_atDevice[igi2_frame.tGraphStream.ptGraphFile->eDeviceID].pfDelete)(
                       igi2_frame.tGraphStream.ptGraphFile->eDeviceID,
                       igi2_frame.tGraphStream.ptGraphFile);
  }
  return result;
}

// source: h/2/graph.c:3094  [anchor-callee]
int __cdecl GraphStream_SkipStreamItems(struct GraphStream_s *ptGraphStream, int nItemsToSkip)
{
  #pragma pack(push, 1)
  union
  {
    struct { unsigned __int8 v3; };
    struct { char igi2_o1[1]; unsigned __int8 v4; };
    struct { char igi2_o2[2]; int v5; };
    char igi2_extent[6];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v2; // edi

  v2 = nItemsToSkip;
  while ( v2 )
  {
    --v2;
    nItemsToSkip = File_atDevice[ptGraphStream->ptGraphFile->eDeviceID].pfisEOF(
                     ptGraphStream->ptGraphFile->eDeviceID,
                     ptGraphStream->ptGraphFile);
    if ( nItemsToSkip )
      break;
    File_atDevice[ptGraphStream->ptGraphFile->eDeviceID].pfRead(
      ptGraphStream->ptGraphFile->eDeviceID,
      ptGraphStream->ptGraphFile,
      &igi2_frame.v3,
      1u);
    nItemsToSkip = File_atDevice[ptGraphStream->ptGraphFile->eDeviceID].pfisEOF(
                     ptGraphStream->ptGraphFile->eDeviceID,
                     ptGraphStream->ptGraphFile);
    if ( !nItemsToSkip )
    {
      nItemsToSkip = igi2_frame.v3;
      switch ( igi2_frame.v3 )
      {
        case 0u:
        case 1u:
          nItemsToSkip = 1;
          goto LABEL_13;
        case 2u:
        case 3u:
          nItemsToSkip = 2;
          goto LABEL_13;
        case 4u:
        case 5u:
        case 6u:
          nItemsToSkip = 4;
          goto LABEL_13;
        case 7u:
          nItemsToSkip = 8;
          goto LABEL_13;
        case 8u:
          nItemsToSkip = 24;
          goto LABEL_13;
        case 9u:
          File_atDevice[ptGraphStream->ptGraphFile->eDeviceID].pfRead(
            ptGraphStream->ptGraphFile->eDeviceID,
            ptGraphStream->ptGraphFile,
            &igi2_frame.v4,
            1u);
          nItemsToSkip = igi2_frame.v4;
          goto LABEL_12;
        case 0xAu:
          File_atDevice[ptGraphStream->ptGraphFile->eDeviceID].pfRead(
            ptGraphStream->ptGraphFile->eDeviceID,
            ptGraphStream->ptGraphFile,
            &igi2_frame.v5,
            4u);
          nItemsToSkip = igi2_frame.v5;
LABEL_12:
          if ( nItemsToSkip )
LABEL_13:
            nItemsToSkip = File_atDevice[ptGraphStream->ptGraphFile->eDeviceID].pfSeek(
                             ptGraphStream->ptGraphFile->eDeviceID,
                             ptGraphStream->ptGraphFile,
                             nItemsToSkip,
                             1);
          break;
        default:
          break;
      }
    }
  }
  return nItemsToSkip;
}

// source: h/2/graph.c:3166  [anchor-callee]
char __cdecl GraphStream_Adduint8(struct GraphStream_s *ptGraphStream, unsigned __int8 nValue)
{
  struct File_s *ptGraphFile; // ecx
  struct GraphStream_s *anData; // [esp+0h] [ebp-4h] BYREF

  anData = ptGraphStream;
  ptGraphFile = ptGraphStream->ptGraphFile;
  LOBYTE(anData) = 0;
  BYTE1(anData) = nValue;
  File_atDevice[ptGraphFile->eDeviceID].pfWrite(ptGraphFile->eDeviceID, ptGraphFile, &anData, 2u);
  return 1;
}

// source: h/2/graph.c:3190  [anchor-callee]
char __cdecl GraphStream_Addint8(struct GraphStream_s *ptGraphStream, char nValue)
{
  struct File_s *ptGraphFile; // ecx
  struct GraphStream_s *anData; // [esp+0h] [ebp-4h] BYREF

  anData = ptGraphStream;
  ptGraphFile = ptGraphStream->ptGraphFile;
  LOBYTE(anData) = 1;
  BYTE1(anData) = nValue;
  File_atDevice[ptGraphFile->eDeviceID].pfWrite(ptGraphFile->eDeviceID, ptGraphFile, &anData, 2u);
  return 1;
}

// source: h/2/graph.c:3214  [anchor-callee]
char __cdecl GraphStream_Adduint16(struct GraphStream_s *ptGraphStream, unsigned __int16 nValue)
{
  struct File_s *ptGraphFile; // ecx
  struct GraphStream_s *anData; // [esp+0h] [ebp-4h] BYREF

  anData = ptGraphStream;
  ptGraphFile = ptGraphStream->ptGraphFile;
  LOBYTE(anData) = 2;
  *(_WORD *)((char *)&anData + 1) = nValue;
  File_atDevice[ptGraphFile->eDeviceID].pfWrite(ptGraphFile->eDeviceID, ptGraphFile, &anData, 3u);
  return 1;
}

// source: h/2/graph.c:3241  [anchor-callee]
char __cdecl GraphStream_Addint16(struct GraphStream_s *ptGraphStream, __int16 nValue)
{
  struct File_s *ptGraphFile; // ecx
  struct GraphStream_s *anData; // [esp+0h] [ebp-4h] BYREF

  anData = ptGraphStream;
  ptGraphFile = ptGraphStream->ptGraphFile;
  LOBYTE(anData) = 3;
  *(_WORD *)((char *)&anData + 1) = nValue;
  File_atDevice[ptGraphFile->eDeviceID].pfWrite(ptGraphFile->eDeviceID, ptGraphFile, &anData, 3u);
  return 1;
}

// source: h/2/graph.c:3268  [anchor-callee]
char __cdecl GraphStream_Adduint32(struct GraphStream_s *ptGraphStream, unsigned int nValue)
{
  struct File_s *ptGraphFile; // ecx
  unsigned __int8 anData[8]; // [esp+4h] [ebp-8h] BYREF

  ptGraphFile = ptGraphStream->ptGraphFile;
  anData[0] = 4;
  *(_DWORD *)&anData[1] = nValue;
  File_atDevice[ptGraphFile->eDeviceID].pfWrite(ptGraphFile->eDeviceID, ptGraphFile, anData, 5u);
  return 1;
}

// source: h/2/graph.c:3295  [anchor-callee]
char __cdecl GraphStream_Addint32(struct GraphStream_s *ptGraphStream, int nValue)
{
  struct File_s *ptGraphFile; // ecx
  unsigned __int8 anData[8]; // [esp+4h] [ebp-8h] BYREF

  ptGraphFile = ptGraphStream->ptGraphFile;
  anData[0] = 5;
  *(_DWORD *)&anData[1] = nValue;
  File_atDevice[ptGraphFile->eDeviceID].pfWrite(ptGraphFile->eDeviceID, ptGraphFile, anData, 5u);
  return 1;
}

// source: h/2/graph.c:3322  [anchor-callee]
char __cdecl GraphStream_Addreal32(struct GraphStream_s *ptGraphStream, float vValue)
{
  struct File_s *ptGraphFile; // ecx
  unsigned __int8 anData[8]; // [esp+4h] [ebp-8h] BYREF

  ptGraphFile = ptGraphStream->ptGraphFile;
  anData[0] = 6;
  *(float *)&anData[1] = vValue;
  File_atDevice[ptGraphFile->eDeviceID].pfWrite(ptGraphFile->eDeviceID, ptGraphFile, anData, 5u);
  return 1;
}

// source: h/2/graph.c:3349  [anchor-callee]
char __cdecl GraphStream_Addreal64(struct GraphStream_s *ptGraphStream, double vValue)
{
  struct File_s *ptGraphFile; // ecx
  unsigned __int8 anData[12]; // [esp+4h] [ebp-Ch] BYREF

  ptGraphFile = ptGraphStream->ptGraphFile;
  anData[0] = 7;
  *(double *)&anData[1] = vValue;
  File_atDevice[ptGraphFile->eDeviceID].pfWrite(ptGraphFile->eDeviceID, ptGraphFile, anData, 9u);
  return 1;
}

// source: h/2/graph.c:3376  [anchor-callee]
char __cdecl GraphStream_Addreal64x3(
        struct GraphStream_s *ptGraphStream,
        struct real64x3_t *ptValue)
{
  unsigned __int8 anData[28]; // [esp+8h] [ebp-1Ch] BYREF

  anData[0] = 8;
  qmemcpy(&anData[1], ptValue, 0x18u);
  File_atDevice[ptGraphStream->ptGraphFile->eDeviceID].pfWrite(
    ptGraphStream->ptGraphFile->eDeviceID,
    ptGraphStream->ptGraphFile,
    anData,
    25u);
  return 1;
}

// source: h/2/graph.c:3405  [anchor-callee]
char __cdecl GraphStream_AddString(struct GraphStream_s *ptGraphStream, char *pzString)
{
  unsigned int v3; // kr00_4
  unsigned __int8 anData[264]; // [esp+8h] [ebp-108h] BYREF

  v3 = strlen(pzString);
  anData[1] = v3 + 1;
  anData[0] = 9;
  qmemcpy(&anData[2], pzString, v3 + 1);
  File_atDevice[ptGraphStream->ptGraphFile->eDeviceID].pfWrite(
    ptGraphStream->ptGraphFile->eDeviceID,
    ptGraphStream->ptGraphFile,
    anData,
    v3 + 3);
  return 1;
}

// source: h/2/graph.c:3440  [anchor-callee]
char __cdecl GraphStream_AddBuffer(struct GraphStream_s *ptGraphStream, void *pxBuffer, int nSize)
{
  #pragma pack(push, 1)
  union
  {
    struct { _BYTE v7[4]; };
    struct { char igi2_o1[4]; char v8; };
    struct { char igi2_o2[5]; int v9; };
    char igi2_extent[12];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct File_s *ptGraphFile; // ecx
  struct File_s *v5; // ecx

  ptGraphFile = ptGraphStream->ptGraphFile;
  igi2_frame.v7[0] = 0;
  igi2_frame.v7[1] = 10;
  File_atDevice[ptGraphFile->eDeviceID].pfWrite(ptGraphFile->eDeviceID, ptGraphFile, igi2_frame.v7, 2u);
  v5 = ptGraphStream->ptGraphFile;
  igi2_frame.v8 = 5;
  igi2_frame.v9 = nSize;
  File_atDevice[v5->eDeviceID].pfWrite(v5->eDeviceID, v5, &igi2_frame.v8, 5u);
  File_atDevice[ptGraphStream->ptGraphFile->eDeviceID].pfWrite(
    ptGraphStream->ptGraphFile->eDeviceID,
    ptGraphStream->ptGraphFile,
    pxBuffer,
    nSize);
  return 1;
}

// source: h/2/graph.c:3463  [anchor-callee]
char __cdecl GraphStream_Getuint8(struct GraphStream_s *ptGraphStream, unsigned __int8 *pnValue)
{
  int v2; // ecx
  int anData; // [esp+0h] [ebp-4h] BYREF

  anData = v2;
  File_atDevice[ptGraphStream->ptGraphFile->eDeviceID].pfRead(
    ptGraphStream->ptGraphFile->eDeviceID,
    ptGraphStream->ptGraphFile,
    &anData,
    2u);
  *pnValue = BYTE1(anData);
  return 1;
}

// source: h/2/graph.c:3489  [anchor-callee]
char __cdecl GraphStream_Getint8(struct GraphStream_s *ptGraphStream, char *pnValue)
{
  int v2; // ecx
  int anData; // [esp+0h] [ebp-4h] BYREF

  anData = v2;
  File_atDevice[ptGraphStream->ptGraphFile->eDeviceID].pfRead(
    ptGraphStream->ptGraphFile->eDeviceID,
    ptGraphStream->ptGraphFile,
    &anData,
    2u);
  *pnValue = BYTE1(anData);
  return 1;
}

// source: h/2/graph.c:3515  [anchor-callee]
char __cdecl GraphStream_Getuint16(struct GraphStream_s *ptGraphStream, unsigned __int16 *pnValue)
{
  int v2; // ecx
  int anData; // [esp+0h] [ebp-4h] BYREF

  anData = v2;
  File_atDevice[ptGraphStream->ptGraphFile->eDeviceID].pfRead(
    ptGraphStream->ptGraphFile->eDeviceID,
    ptGraphStream->ptGraphFile,
    &anData,
    3u);
  *pnValue = *(_WORD *)((char *)&anData + 1);
  return 1;
}

// source: h/2/graph.c:3544  [anchor-callee]
char __cdecl GraphStream_Getint16(struct GraphStream_s *ptGraphStream, __int16 *pnValue)
{
  int v2; // ecx
  int anData; // [esp+0h] [ebp-4h] BYREF

  anData = v2;
  File_atDevice[ptGraphStream->ptGraphFile->eDeviceID].pfRead(
    ptGraphStream->ptGraphFile->eDeviceID,
    ptGraphStream->ptGraphFile,
    &anData,
    3u);
  *pnValue = *(_WORD *)((char *)&anData + 1);
  return 1;
}

// source: h/2/graph.c:3573  [anchor-callee]
char __cdecl GraphStream_Getuint32(struct GraphStream_s *ptGraphStream, unsigned int *pnValue)
{
  unsigned __int8 anData[5]; // [esp+4h] [ebp-8h] BYREF

  File_atDevice[ptGraphStream->ptGraphFile->eDeviceID].pfRead(
    ptGraphStream->ptGraphFile->eDeviceID,
    ptGraphStream->ptGraphFile,
    anData,
    5u);
  if ( File_atDevice[ptGraphStream->ptGraphFile->eDeviceID].pfisEOF(
         ptGraphStream->ptGraphFile->eDeviceID,
         ptGraphStream->ptGraphFile) )
  {
    return 0;
  }
  *pnValue = *(_DWORD *)&anData[1];
  return 1;
}

// source: h/2/graph.c:3604  [anchor-callee]
char __cdecl GraphStream_Getint32(struct GraphStream_s *ptGraphStream, int *pnValue)
{
  unsigned __int8 anData[5]; // [esp+4h] [ebp-8h] BYREF

  File_atDevice[ptGraphStream->ptGraphFile->eDeviceID].pfRead(
    ptGraphStream->ptGraphFile->eDeviceID,
    ptGraphStream->ptGraphFile,
    anData,
    5u);
  *pnValue = *(_DWORD *)&anData[1];
  return 1;
}

// source: h/2/graph.c:3633  [anchor-callee]
char __cdecl GraphStream_Getreal32(struct GraphStream_s *ptGraphStream, float *pvValue)
{
  unsigned __int8 anData[5]; // [esp+4h] [ebp-8h] BYREF

  File_atDevice[ptGraphStream->ptGraphFile->eDeviceID].pfRead(
    ptGraphStream->ptGraphFile->eDeviceID,
    ptGraphStream->ptGraphFile,
    anData,
    5u);
  *pvValue = *(float *)&anData[1];
  return 1;
}

// source: h/2/graph.c:3662  [anchor-callee]
char __cdecl GraphStream_Getreal64(struct GraphStream_s *ptGraphStream, double *pvValue)
{
  int v2; // ecx
  unsigned __int8 anData[9]; // [esp+4h] [ebp-Ch] BYREF

  File_atDevice[ptGraphStream->ptGraphFile->eDeviceID].pfRead(
    ptGraphStream->ptGraphFile->eDeviceID,
    ptGraphStream->ptGraphFile,
    anData,
    9u);
  v2 = *(_DWORD *)&anData[5];
  *(_DWORD *)pvValue = *(_DWORD *)&anData[1];
  *((_DWORD *)pvValue + 1) = v2;
  return 1;
}

// source: h/2/graph.c:3691  [anchor-callee]
char __cdecl GraphStream_Getreal64x3(struct GraphStream_s *ptGraphStream, struct real64x3_t *ptValue)
{
  unsigned __int8 anData[25]; // [esp+8h] [ebp-1Ch] BYREF

  File_atDevice[ptGraphStream->ptGraphFile->eDeviceID].pfRead(
    ptGraphStream->ptGraphFile->eDeviceID,
    ptGraphStream->ptGraphFile,
    anData,
    25u);
  qmemcpy(ptValue, &anData[1], sizeof(struct real64x3_t));
  return 1;
}

// source: h/2/graph.c:3720  [anchor-callee]
char __cdecl GraphStream_GetString(
        struct GraphStream_s *ptGraphStream,
        char *pzString,
        int nMaxStringLength)
{
  unsigned int v4; // esi
  unsigned __int8 anData[260]; // [esp+8h] [ebp-104h] BYREF

  File_atDevice[ptGraphStream->ptGraphFile->eDeviceID].pfRead(
    ptGraphStream->ptGraphFile->eDeviceID,
    ptGraphStream->ptGraphFile,
    anData,
    2u);
  v4 = anData[1];
  File_atDevice[ptGraphStream->ptGraphFile->eDeviceID].pfRead(
    ptGraphStream->ptGraphFile->eDeviceID,
    ptGraphStream->ptGraphFile,
    &anData[2],
    anData[1]);
  qmemcpy(pzString, &anData[2], v4);
  return 1;
}

// source: h/2/graph.c:3758  [anchor-callee]
char __cdecl GraphStream_GetBuffer(struct GraphStream_s *ptGraphStream, void *pxBuffer, int nSize)
{
  #pragma pack(push, 1)
  union
  {
    struct { _BYTE v5[4]; };
    struct { char igi2_o1[4]; _BYTE v6[8]; };
    char igi2_extent[12];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)

  File_atDevice[ptGraphStream->ptGraphFile->eDeviceID].pfRead(
    ptGraphStream->ptGraphFile->eDeviceID,
    ptGraphStream->ptGraphFile,
    igi2_frame.v5,
    2u);
  File_atDevice[ptGraphStream->ptGraphFile->eDeviceID].pfRead(
    ptGraphStream->ptGraphFile->eDeviceID,
    ptGraphStream->ptGraphFile,
    igi2_frame.v6,
    5u);
  File_atDevice[ptGraphStream->ptGraphFile->eDeviceID].pfRead(
    ptGraphStream->ptGraphFile->eDeviceID,
    ptGraphStream->ptGraphFile,
    pxBuffer,
    nSize);
  return 1;
}

// source: h/2/graph.c:3790  [anchor-mhash]
enum GraphStreamParameterType_e __cdecl GraphStream_GetNextItemType(struct GraphStream_s *ptGraphStream)
{
  int v1; // ecx
  unsigned __int8 eType; // [esp+1h] [ebp-1h] BYREF

  eType = HIBYTE(v1);
  File_atDevice[ptGraphStream->ptGraphFile->eDeviceID].pfRead(
    ptGraphStream->ptGraphFile->eDeviceID,
    ptGraphStream->ptGraphFile,
    &eType,
    1u);
  File_atDevice[ptGraphStream->ptGraphFile->eDeviceID].pfSeek(
    ptGraphStream->ptGraphFile->eDeviceID,
    ptGraphStream->ptGraphFile,
    -1,
    1);
  return eType;
}

// source: h/2/graph.c:3813  [anchor-strings]
void __cdecl Graph_Open()
{
  struct MemPoolSegment_s *v0; // esi
  int v1; // eax
  struct MemPoolFreeItem_s *ptHead; // edx
  unsigned int i; // ecx
  struct MemPoolFreeItem_s *v4; // eax
  unsigned __int16 BaseQTaskType; // ax
  __int16 v6; // ax
  unsigned __int16 v7; // si
  int v8; // esi
  struct ParameterList_s *v9; // eax
  int v10; // edx
  int *p_nDataSize; // eax
  struct GraphStreamCallbackItem_t *v12; // eax
  char *v13; // edx
  struct Node_s *v14; // esi
  int v15; // eax
  char v16; // cl
  struct Node_s *v17; // ecx
  struct Node_s *ptNext; // eax
  struct Node_s *v19; // eax
  _DWORD **v20; // eax
  char *v21; // esi
  struct Node_s *v22; // edi
  int v23; // ecx
  char v24; // dl
  struct Node_s *v25; // edx
  struct Node_s *v26; // ecx
  _DWORD **v27; // eax
  char *v28; // esi
  struct Node_s *v29; // edi
  int v30; // ecx
  char v31; // dl
  struct Node_s *v32; // edx
  struct Node_s *v33; // ecx
  _DWORD **v34; // eax
  char *v35; // esi
  struct Node_s *v36; // edi
  int v37; // ecx
  char v38; // dl
  struct Node_s *v39; // edx
  struct Node_s *v40; // ecx
  _DWORD **v41; // eax
  char *v42; // esi
  struct Node_s *v43; // edi
  int v44; // ecx
  char v45; // dl
  struct Node_s *v46; // edx
  struct Node_s *v47; // ecx
  _DWORD **v48; // eax
  char *v49; // esi
  struct Node_s *v50; // edi
  int v51; // ecx
  char v52; // dl
  struct Node_s *v53; // edx
  struct Node_s *v54; // ecx
  _DWORD **v55; // eax
  char *v56; // esi
  struct Node_s *v57; // edi
  int v58; // ecx
  char v59; // dl
  struct Node_s *v60; // edx
  struct Node_s *v61; // ecx
  _DWORD **v62; // eax
  char *v63; // esi
  struct Node_s *v64; // edi
  int v65; // ecx
  char v66; // dl
  struct Node_s *v67; // ebp
  struct Node_s *v68; // ecx
  struct Node_s *v69; // edx
  _DWORD **v70; // eax
  char *v71; // esi
  struct Node_s *v72; // edi
  int v73; // ecx
  char v74; // dl
  struct Node_s *v75; // ecx
  struct Node_s *v76; // edx
  _DWORD **v77; // eax
  char *v78; // esi
  struct Node_s *v79; // edi
  int v80; // ecx
  char v81; // dl
  struct Node_s *v82; // ecx
  struct Node_s *v83; // edx
  _DWORD **v84; // eax
  char *v85; // esi
  struct Node_s *v86; // edi
  int v87; // ecx
  char v88; // dl
  struct Node_s *v89; // ecx
  struct Node_s *v90; // edx
  _DWORD **v91; // eax
  char *v92; // esi
  struct Node_s *v93; // edi
  int v94; // ecx
  char v95; // dl
  struct Node_s *v96; // ecx
  struct Node_s *v97; // edx
  _DWORD **v98; // eax

  Graph_tLinkPool.nBlocks = 0;
  Graph_tLinkPool.nAllocatedBlocks = 0;
  Graph_tLinkPool.nAlignment = 4;
  Graph_tLinkPool.nBlockSize = 28;
  Graph_tLinkPool.nReAllocBlocks = 1024;
  Graph_tLinkPool.tMemPoolFreeList.ptHead = nullptr;
  Graph_tLinkPool.tMemPoolSegmentList.ptHead = nullptr;
  v0 = (struct MemPoolSegment_s *)Mem_AllocFn(12, 4);
  v1 = Graph_tLinkPool.nBlockSize << 10;
  v0->nByteSize = Graph_tLinkPool.nBlockSize << 10;
  v0->pxData = Mem_AllocFn(v1, Graph_tLinkPool.nAlignment);
  v0->ptNext = Graph_tLinkPool.tMemPoolSegmentList.ptHead;
  ptHead = Graph_tLinkPool.tMemPoolFreeList.ptHead;
  Graph_tLinkPool.tMemPoolSegmentList.ptHead = v0;
  Graph_tLinkPool.nBlocks += 1024;
  for ( i = 0; i < 0x400; ++i )
  {
    v4 = (struct MemPoolFreeItem_s *)((char *)v0->pxData + i * Graph_tLinkPool.nBlockSize);
    v4->ptNext = ptHead;
    ptHead = v4;
    Graph_tLinkPool.tMemPoolFreeList.ptHead = v4;
  }
  BaseQTaskType = QTask_GetBaseQTaskType();
  Graph_eQTaskType = QTask_NewQTaskType("Graph", 152, BaseQTaskType, 0, 0);
  Graph_eUpdateDataQTaskEvent = QTask_NewQTaskEventFn(0, "Graph-UpdateData");
  Graph_eInitDataQTaskEvent = QTask_NewQTaskEventFn(0, "Graph-InitData");
  Graph_eDisplayRouteQTaskEvent = QTask_NewQTaskEventFn(0, "Graph-DisplayRoute");
  Graph_eLoadGraphQTaskEvent = QTask_NewQTaskEventFn(0, "Graph-LoadGraph");
  Graph_eSaveGraphQTaskEvent = QTask_NewQTaskEventFn(0, "Graph-SaveGraph");
  Graph_eCreateNodeQTaskEvent = QTask_NewQTaskEventFn(0, "Graph-CreateNode");
  Graph_eUpdateNodeQTaskEvent = QTask_NewQTaskEventFn(0, "Graph-UpdateNode");
  Graph_ePrintNodeQTaskEvent = QTask_NewQTaskEventFn(0, "Graph-PrintNode");
  Graph_eLoadNodeQTaskEvent = QTask_NewQTaskEventFn(0, "Graph-LoadNode");
  v6 = QTask_NewQTaskEventFn(0, "Graph-SaveNode");
  v7 = Graph_eQTaskType;
  Graph_eSaveNodeQTaskEvent = v6;
  QTask_LinkQTaskEventHandlerFn(Graph_eQTaskType, 0, Graph_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v7, 1, (void (__cdecl *)(struct QTask_s *))Graph_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v7, 2, Graph_DeleteHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v7, 3, Graph_PrepareDeleteHandler);
  QTask_LinkQTaskEventHandlerFn(v7, ParameterList_eUpdateInternalDataQTaskEvent, Graph_UpdateInternalDataHandler);
  QTask_LinkQTaskEventHandlerFn(
    v7,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Graph_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v7, Attach_eUpdateAttachmentEvent, Graph_UpdateAttachmentHandler);
  QTask_LinkQTaskEventHandlerFn(v7, 4, Graph_ParentChangedHandler);
  QTask_LinkQTaskEventHandlerFn(v7, Attach_eAttachEvent, nullptr);
  QTask_LinkQTaskEventHandlerNoContextFn(
    v7,
    Level_eUpdateInternalDataAfterLoadEvent,
    Graph_UpdateInternalDataAfterLoadHandler);
  v8 = Level_eParameterTypeGraph;
  ParameterList_LinkParameterEventHandler(
    Level_eParameterTypeGraph,
    ParameterList_eQParameterPrintEvent,
    Graph_PrintGraphHandler);
  ParameterList_LinkParameterEventHandler(v8, ParameterList_eQParameterParseEvent, Graph_ParseGraphHandler);
  ParameterList_LinkParameterEventHandler(
    v8,
    ParameterList_eQParameterGetNumberOfArgumentsEvent,
    (void (__cdecl *)(void *, void *))Graph_GetNumberOfArgumentsGraphHandler);
  v9 = (struct ParameterList_s *)Mem_AllocFn(172, 4);
  v10 = Level_eParameterTypeObjectPos;
  v9->ptParameterListItem = (struct ParameterListItem_s *)&v9[1];
  v9->nParameters = 0;
  v9->nMaxParameters = 8;
  Graph_ptParameterList = v9;
  ParameterList_AddParameter(v9, 0x48u, v10, "Graph position", 1u, nullptr);
  ParameterList_AddParameter(Graph_ptParameterList, 0x28u, Level_eParameterTypebool8, "Relative", 1u, nullptr);
  ParameterList_AddParameter(Graph_ptParameterList, 0x78u, Level_eParameterTypePushButton, "Update", 7u, nullptr);
  ParameterList_AddParameter(Graph_ptParameterList, 0x7Bu, Level_eParameterTypebool8, "Register Nodes", 6u, nullptr);
  ParameterList_AddParameter(Graph_ptParameterList, 0x7Cu, Level_eParameterTypebool8, "Show Node Links", 6u, nullptr);
  ParameterList_AddParameter(Graph_ptParameterList, 0, Level_eParameterTypeGraph, "Graphdata", 7u, nullptr);
  ParameterList_AddParameter(Graph_ptParameterList, 0x74u, Level_eParameterTypeInt32, "NodesToAdd", 6u, nullptr);
  ParameterList_AddParameter(Graph_ptParameterList, 0x80u, Level_eParameterTypeReal32, "AddDistance", 6u, nullptr);
  Graph_tGraphList.ptHead = (struct GraphEntry_s *)&Graph_tGraphList.ptMiddle;
  Graph_tGraphList.ptTail = (struct GraphEntry_s *)&Graph_tGraphList;
  Graph_tGraphList.ptMiddle = nullptr;
  p_nDataSize = &Graph_atGraphNodeDataSize[0].nDataSize;
  do
  {
    *((_WORD *)p_nDataSize - 2) = 512;
    *p_nDataSize = 0;
    p_nDataSize += 2;
  }
  while ( (int)p_nDataSize < 129476832 );
  Graph_SetGraphNodeDataSize(Graph_eQTaskType, 592);
  Graph_tGraphStreamCallbackList.ptHead = (struct Node_s *)&Graph_tGraphStreamCallbackList.ptMiddle;
  Graph_tGraphStreamCallbackList.ptTail = (struct Node_s *)&Graph_tGraphStreamCallbackList;
  Graph_tGraphStreamCallbackList.ptMiddle = nullptr;
  Graph_tGraphStreamCallbackFreeList.ptHead = (struct Node_s *)&Graph_tGraphStreamCallbackFreeList.ptMiddle;
  Graph_tGraphStreamCallbackFreeList.ptTail = (struct Node_s *)&Graph_tGraphStreamCallbackFreeList;
  Graph_tGraphStreamCallbackFreeList.ptMiddle = nullptr;
  v12 = Graph_atGraphStreamCallbackItems;
  do
  {
    v12->tNode.ptPrev = nullptr;
    v12->tNode.ptNext = nullptr;
    v12 = (struct GraphStreamCallbackItem_t *)(List_AddTail(v12, (int)&Graph_tGraphStreamCallbackFreeList) + 5);
  }
  while ( (int)v12 < 129478760 );
  v13 = "nMaxNodes";
  v14 = nullptr;
  v15 = 1;
  do
  {
    v16 = *v13++;
    if ( v16 >= 97 && v16 <= 122 )
      v16 -= 32;
    v14 = (struct Node_s *)((char *)v14 + v15 * v16);
    v15 = (unsigned __int16)(v15 + 317);
  }
  while ( *v13 );
  v17 = Graph_tGraphStreamCallbackList.ptHead;
  ptNext = Graph_tGraphStreamCallbackList.ptHead->ptNext;
  if ( Graph_tGraphStreamCallbackList.ptHead->ptNext )
  {
    while ( v17[1].ptNext != v14 )
    {
      v17 = ptNext;
      ptNext = ptNext->ptNext;
      if ( !ptNext )
        goto LABEL_15;
    }
    goto LABEL_17;
  }
LABEL_15:
  v19 = Graph_tGraphStreamCallbackFreeList.ptHead;
  if ( Graph_tGraphStreamCallbackFreeList.ptHead->ptNext )
  {
    Graph_tGraphStreamCallbackFreeList.ptHead[1].ptNext = v14;
    v19[1].ptPrev = (struct Node_s *)5;
    v19[2].ptNext = (struct Node_s *)Graph_MaxNodesCallback;
    v20 = Node_Remove(v19);
    v20[1] = nullptr;
    *v20 = nullptr;
    List_AddTail(v20, (int)&Graph_tGraphStreamCallbackList);
LABEL_17:
    v19 = Graph_tGraphStreamCallbackFreeList.ptHead;
  }
  v21 = "nNodeID";
  v22 = nullptr;
  v23 = 1;
  do
  {
    v24 = *v21++;
    if ( v24 >= 97 && v24 <= 122 )
      v24 -= 32;
    v22 = (struct Node_s *)((char *)v22 + v23 * v24);
    v23 = (unsigned __int16)(v23 + 317);
  }
  while ( *v21 );
  v25 = Graph_tGraphStreamCallbackList.ptHead;
  v26 = Graph_tGraphStreamCallbackList.ptHead->ptNext;
  if ( Graph_tGraphStreamCallbackList.ptHead->ptNext )
  {
    while ( v25[1].ptNext != v22 )
    {
      v25 = v26;
      v26 = v26->ptNext;
      if ( !v26 )
        goto LABEL_26;
    }
  }
  else
  {
LABEL_26:
    if ( v19->ptNext )
    {
      v19[1].ptNext = v22;
      v19[1].ptPrev = (struct Node_s *)5;
      v19[2].ptNext = (struct Node_s *)Graph_NodeIDCallback;
      v27 = Node_Remove(v19);
      v27[1] = nullptr;
      *v27 = nullptr;
      List_AddTail(v27, (int)&Graph_tGraphStreamCallbackList);
      v19 = Graph_tGraphStreamCallbackFreeList.ptHead;
    }
  }
  v28 = "tNodePosition";
  v29 = nullptr;
  v30 = 1;
  do
  {
    v31 = *v28++;
    if ( v31 >= 97 && v31 <= 122 )
      v31 -= 32;
    v29 = (struct Node_s *)((char *)v29 + v30 * v31);
    v30 = (unsigned __int16)(v30 + 317);
  }
  while ( *v28 );
  v32 = Graph_tGraphStreamCallbackList.ptHead;
  v33 = Graph_tGraphStreamCallbackList.ptHead->ptNext;
  if ( Graph_tGraphStreamCallbackList.ptHead->ptNext )
  {
    while ( v32[1].ptNext != v29 )
    {
      v32 = v33;
      v33 = v33->ptNext;
      if ( !v33 )
        goto LABEL_36;
    }
  }
  else
  {
LABEL_36:
    if ( v19->ptNext )
    {
      v19[1].ptNext = v29;
      v19[1].ptPrev = (struct Node_s *)8;
      v19[2].ptNext = (struct Node_s *)Graph_NodePositionCallback;
      v34 = Node_Remove(v19);
      v34[1] = nullptr;
      *v34 = nullptr;
      List_AddTail(v34, (int)&Graph_tGraphStreamCallbackList);
      v19 = Graph_tGraphStreamCallbackFreeList.ptHead;
    }
  }
  v35 = "vNodeGamma";
  v36 = nullptr;
  v37 = 1;
  do
  {
    v38 = *v35++;
    if ( v38 >= 97 && v38 <= 122 )
      v38 -= 32;
    v36 = (struct Node_s *)((char *)v36 + v37 * v38);
    v37 = (unsigned __int16)(v37 + 317);
  }
  while ( *v35 );
  v39 = Graph_tGraphStreamCallbackList.ptHead;
  v40 = Graph_tGraphStreamCallbackList.ptHead->ptNext;
  if ( Graph_tGraphStreamCallbackList.ptHead->ptNext )
  {
    while ( v39[1].ptNext != v36 )
    {
      v39 = v40;
      v40 = v40->ptNext;
      if ( !v40 )
        goto LABEL_46;
    }
  }
  else
  {
LABEL_46:
    if ( v19->ptNext )
    {
      v19[1].ptNext = v36;
      v19[1].ptPrev = (struct Node_s *)6;
      v19[2].ptNext = (struct Node_s *)Graph_NodeGammaCallback;
      v41 = Node_Remove(v19);
      v41[1] = nullptr;
      *v41 = nullptr;
      List_AddTail(v41, (int)&Graph_tGraphStreamCallbackList);
      v19 = Graph_tGraphStreamCallbackFreeList.ptHead;
    }
  }
  v42 = "vNodeRadius";
  v43 = nullptr;
  v44 = 1;
  do
  {
    v45 = *v42++;
    if ( v45 >= 97 && v45 <= 122 )
      v45 -= 32;
    v43 = (struct Node_s *)((char *)v43 + v44 * v45);
    v44 = (unsigned __int16)(v44 + 317);
  }
  while ( *v42 );
  v46 = Graph_tGraphStreamCallbackList.ptHead;
  v47 = Graph_tGraphStreamCallbackList.ptHead->ptNext;
  if ( Graph_tGraphStreamCallbackList.ptHead->ptNext )
  {
    while ( v46[1].ptNext != v43 )
    {
      v46 = v47;
      v47 = v47->ptNext;
      if ( !v47 )
        goto LABEL_56;
    }
  }
  else
  {
LABEL_56:
    if ( v19->ptNext )
    {
      v19[1].ptNext = v43;
      v19[1].ptPrev = (struct Node_s *)6;
      v19[2].ptNext = (struct Node_s *)Graph_NodeRadiusCallback;
      v48 = Node_Remove(v19);
      v48[1] = nullptr;
      *v48 = nullptr;
      List_AddTail(v48, (int)&Graph_tGraphStreamCallbackList);
      v19 = Graph_tGraphStreamCallbackFreeList.ptHead;
    }
  }
  v49 = "nNodeMaterial";
  v50 = nullptr;
  v51 = 1;
  do
  {
    v52 = *v49++;
    if ( v52 >= 97 && v52 <= 122 )
      v52 -= 32;
    v50 = (struct Node_s *)((char *)v50 + v51 * v52);
    v51 = (unsigned __int16)(v51 + 317);
  }
  while ( *v49 );
  v53 = Graph_tGraphStreamCallbackList.ptHead;
  v54 = Graph_tGraphStreamCallbackList.ptHead->ptNext;
  if ( Graph_tGraphStreamCallbackList.ptHead->ptNext )
  {
    while ( v53[1].ptNext != v50 )
    {
      v53 = v54;
      v54 = v54->ptNext;
      if ( !v54 )
        goto LABEL_66;
    }
  }
  else
  {
LABEL_66:
    if ( v19->ptNext )
    {
      v19[1].ptNext = v50;
      v19[1].ptPrev = (struct Node_s *)5;
      v19[2].ptNext = (struct Node_s *)Graph_NodeMaterialCallback;
      v55 = Node_Remove(v19);
      v55[1] = nullptr;
      *v55 = nullptr;
      List_AddTail(v55, (int)&Graph_tGraphStreamCallbackList);
      v19 = Graph_tGraphStreamCallbackFreeList.ptHead;
    }
  }
  v56 = "vNodeLightValue";
  v57 = nullptr;
  v58 = 1;
  do
  {
    v59 = *v56++;
    if ( v59 >= 97 && v59 <= 122 )
      v59 -= 32;
    v57 = (struct Node_s *)((char *)v57 + v58 * v59);
    v58 = (unsigned __int16)(v58 + 317);
  }
  while ( *v56 );
  v60 = Graph_tGraphStreamCallbackList.ptHead;
  v61 = Graph_tGraphStreamCallbackList.ptHead->ptNext;
  if ( Graph_tGraphStreamCallbackList.ptHead->ptNext )
  {
    while ( v60[1].ptNext != v57 )
    {
      v60 = v61;
      v61 = v61->ptNext;
      if ( !v61 )
        goto LABEL_76;
    }
  }
  else
  {
LABEL_76:
    if ( v19->ptNext )
    {
      v19[1].ptNext = v57;
      v19[1].ptPrev = (struct Node_s *)6;
      v19[2].ptNext = (struct Node_s *)Graph_NodeLightValueCallback;
      v62 = Node_Remove(v19);
      v62[1] = nullptr;
      *v62 = nullptr;
      List_AddTail(v62, (int)&Graph_tGraphStreamCallbackList);
      v19 = Graph_tGraphStreamCallbackFreeList.ptHead;
    }
  }
  v63 = "nNodeOnTerrain";
  v64 = nullptr;
  v65 = 1;
  do
  {
    v66 = *v63++;
    if ( v66 >= 97 && v66 <= 122 )
      v66 -= 32;
    v64 = (struct Node_s *)((char *)v64 + v65 * v66);
    v65 = (unsigned __int16)(v65 + 317);
  }
  while ( *v63 );
  v67 = Graph_tGraphStreamCallbackList.ptHead;
  v68 = Graph_tGraphStreamCallbackList.ptHead->ptNext;
  v69 = Graph_tGraphStreamCallbackList.ptHead;
  if ( Graph_tGraphStreamCallbackList.ptHead->ptNext )
  {
    while ( v69[1].ptNext != v64 )
    {
      v69 = v68;
      v68 = v68->ptNext;
      if ( !v68 )
        goto LABEL_86;
    }
  }
  else
  {
LABEL_86:
    if ( v19->ptNext )
    {
      v19[1].ptNext = v64;
      v19[1].ptPrev = (struct Node_s *)5;
      v19[2].ptNext = (struct Node_s *)Graph_NodeTerrainCallback;
      v70 = Node_Remove(v19);
      v70[1] = nullptr;
      *v70 = nullptr;
      List_AddTail(v70, (int)&Graph_tGraphStreamCallbackList);
      v67 = Graph_tGraphStreamCallbackList.ptHead;
      v19 = Graph_tGraphStreamCallbackFreeList.ptHead;
    }
  }
  v71 = "nNodeCriteria";
  v72 = nullptr;
  v73 = 1;
  do
  {
    v74 = *v71++;
    if ( v74 >= 97 && v74 <= 122 )
      v74 -= 32;
    v72 = (struct Node_s *)((char *)v72 + v73 * v74);
    v73 = (unsigned __int16)(v73 + 317);
  }
  while ( *v71 );
  v75 = v67->ptNext;
  v76 = v67;
  if ( v67->ptNext )
  {
    while ( v76[1].ptNext != v72 )
    {
      v76 = v75;
      v75 = v75->ptNext;
      if ( !v75 )
        goto LABEL_96;
    }
  }
  else
  {
LABEL_96:
    if ( v19->ptNext )
    {
      v19[1].ptNext = v72;
      v19[1].ptPrev = (struct Node_s *)9;
      v19[2].ptNext = (struct Node_s *)Graph_NodeCriteriaCallback;
      v77 = Node_Remove(v19);
      v77[1] = nullptr;
      *v77 = nullptr;
      List_AddTail(v77, (int)&Graph_tGraphStreamCallbackList);
      v67 = Graph_tGraphStreamCallbackList.ptHead;
      v19 = Graph_tGraphStreamCallbackFreeList.ptHead;
    }
  }
  v78 = (char *)&unk_6863E8;
  v79 = nullptr;
  v80 = 1;
  do
  {
    v81 = *v78++;
    if ( v81 >= 97 && v81 <= 122 )
      v81 -= 32;
    v79 = (struct Node_s *)((char *)v79 + v80 * v81);
    v80 = (unsigned __int16)(v80 + 317);
  }
  while ( *v78 );
  v82 = v67->ptNext;
  v83 = v67;
  if ( v67->ptNext )
  {
    while ( v83[1].ptNext != v79 )
    {
      v83 = v82;
      v82 = v82->ptNext;
      if ( !v82 )
        goto LABEL_106;
    }
  }
  else
  {
LABEL_106:
    if ( v19->ptNext )
    {
      v19[1].ptNext = v79;
      v19[1].ptPrev = (struct Node_s *)5;
      v19[2].ptNext = (struct Node_s *)Graph_LinkID1Callback;
      v84 = Node_Remove(v19);
      v84[1] = nullptr;
      *v84 = nullptr;
      List_AddTail(v84, (int)&Graph_tGraphStreamCallbackList);
      v67 = Graph_tGraphStreamCallbackList.ptHead;
      v19 = Graph_tGraphStreamCallbackFreeList.ptHead;
    }
  }
  v85 = (char *)&unk_6863DC;
  v86 = nullptr;
  v87 = 1;
  do
  {
    v88 = *v85++;
    if ( v88 >= 97 && v88 <= 122 )
      v88 -= 32;
    v86 = (struct Node_s *)((char *)v86 + v87 * v88);
    v87 = (unsigned __int16)(v87 + 317);
  }
  while ( *v85 );
  v89 = v67->ptNext;
  v90 = v67;
  if ( v67->ptNext )
  {
    while ( v90[1].ptNext != v86 )
    {
      v90 = v89;
      v89 = v89->ptNext;
      if ( !v89 )
        goto LABEL_116;
    }
  }
  else
  {
LABEL_116:
    if ( v19->ptNext )
    {
      v19[1].ptNext = v86;
      v19[1].ptPrev = (struct Node_s *)5;
      v19[2].ptNext = (struct Node_s *)Graph_LinkID2Callback;
      v91 = Node_Remove(v19);
      v91[1] = nullptr;
      *v91 = nullptr;
      List_AddTail(v91, (int)&Graph_tGraphStreamCallbackList);
      v67 = Graph_tGraphStreamCallbackList.ptHead;
      v19 = Graph_tGraphStreamCallbackFreeList.ptHead;
    }
  }
  v92 = (char *)&unk_6863D0;
  v93 = nullptr;
  v94 = 1;
  do
  {
    v95 = *v92++;
    if ( v95 >= 97 && v95 <= 122 )
      v95 -= 32;
    v93 = (struct Node_s *)((char *)v93 + v94 * v95);
    v94 = (unsigned __int16)(v94 + 317);
  }
  while ( *v92 );
  v96 = v67->ptNext;
  v97 = v67;
  if ( v67->ptNext )
  {
    while ( v97[1].ptNext != v93 )
    {
      v97 = v96;
      v96 = v96->ptNext;
      if ( !v96 )
        goto LABEL_126;
    }
  }
  else
  {
LABEL_126:
    if ( v19->ptNext )
    {
      v19[1].ptNext = v93;
      v19[1].ptPrev = (struct Node_s *)5;
      v19[2].ptNext = (struct Node_s *)Graph_LinkTypeCallback;
      v98 = Node_Remove(v19);
      v98[1] = nullptr;
      *v98 = nullptr;
      List_AddTail(v98, (int)&Graph_tGraphStreamCallbackList);
    }
  }
}

// source: h/2/graph.c:3921  [anchor-hash]
void __cdecl Graph_Close()
{
  int v0; // esi

  MemPool_DeInit(&Graph_tLinkPool);
  if ( Graph_ptParameterList )
  {
    v0 = *(_DWORD *)((unsigned int)&Graph_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
  QTask_DeleteQTaskEvent(Graph_eUpdateDataQTaskEvent);
  QTask_DeleteQTaskEvent(Graph_eInitDataQTaskEvent);
  QTask_DeleteQTaskEvent(Graph_eDisplayRouteQTaskEvent);
  QTask_DeleteQTaskEvent(Graph_eLoadGraphQTaskEvent);
  QTask_DeleteQTaskEvent(Graph_eSaveGraphQTaskEvent);
  QTask_DeleteQTaskEvent(Graph_eLoadNodeQTaskEvent);
  QTask_DeleteQTaskEvent(Graph_eSaveNodeQTaskEvent);
  QTask_DeleteQTaskEvent(Graph_ePrintNodeQTaskEvent);
  QTask_DeleteQTaskEvent(Graph_eCreateNodeQTaskEvent);
  QTask_DeleteQTaskEvent(Graph_eUpdateNodeQTaskEvent);
  QTask_DeleteQTaskType(Graph_eQTaskType);
}
