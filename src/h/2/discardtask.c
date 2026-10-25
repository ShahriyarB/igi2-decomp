/* h/2/discardtask.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: h/2/discardtask.c:89  [anchor-mhash]
void __cdecl DiscardTask_UpdateCorners(struct DiscardTask_s *ptDiscardTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { float v16; };
    struct { char igi2_o1[4]; float v17; };
    struct { char igi2_o2[16]; double v18; };
    struct { char igi2_o3[32]; struct real64x3_t Real64x3_Rotate_tTemp; };
    char igi2_extent[60];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  double v1; // st7
  double v2; // st6
  double v3; // st5
  double vWidth; // st4
  double v5; // st4
  double v6; // st5
  double v7; // st4
  double v8; // st4
  double v9; // st4
  double v10; // st4
  double v11; // st4
  double v12; // st4
  double v13; // st4
  double v14; // st4
  double v15; // st7

  igi2_frame.v16 = sin(ptDiscardTask->vGamma);
  igi2_frame.v17 = cos(ptDiscardTask->vGamma);
  v1 = -igi2_frame.v16;
  v2 = ptDiscardTask->vWidth * 2048.0;
  v3 = ptDiscardTask->vHeight * 2048.0;
  if ( ptDiscardTask->vHeight <= (double)ptDiscardTask->vWidth )
    vWidth = ptDiscardTask->vWidth;
  else
    vWidth = ptDiscardTask->vHeight;
  v5 = vWidth * 2048.0;
  ptDiscardTask->atCorner[0].vX = v2;
  ptDiscardTask->atCorner[0].vY = v3;
  ptDiscardTask->atCorner[0].vZ = v5;
  ptDiscardTask->atCorner[1].vX = v2 * -1.0;
  ptDiscardTask->atCorner[1].vY = v3;
  ptDiscardTask->atCorner[7].vX = v2 * -1.0;
  ptDiscardTask->atCorner[1].vZ = v5;
  ptDiscardTask->atCorner[2].vX = v2;
  ptDiscardTask->atCorner[2].vY = v3 * -1.0;
  ptDiscardTask->atCorner[2].vZ = v5;
  ptDiscardTask->atCorner[3].vX = v2 * -1.0;
  ptDiscardTask->atCorner[3].vY = v3 * -1.0;
  ptDiscardTask->atCorner[3].vZ = v5;
  ptDiscardTask->atCorner[4].vX = v2;
  ptDiscardTask->atCorner[4].vY = v3;
  igi2_frame.v18 = v5 * -1.0;
  ptDiscardTask->atCorner[4].vZ = igi2_frame.v18;
  ptDiscardTask->atCorner[5].vX = v2 * -1.0;
  ptDiscardTask->atCorner[5].vY = v3;
  ptDiscardTask->atCorner[5].vZ = igi2_frame.v18;
  ptDiscardTask->atCorner[6].vX = v2;
  v6 = v3 * -1.0;
  ptDiscardTask->atCorner[6].vY = v6;
  ptDiscardTask->atCorner[6].vZ = igi2_frame.v18;
  ptDiscardTask->atCorner[7].vY = v6;
  ptDiscardTask->atCorner[7].vZ = igi2_frame.v18;
  v7 = ptDiscardTask->atCorner[0].vZ * 0.0;
  igi2_frame.Real64x3_Rotate_tTemp.vX = v1 * ptDiscardTask->atCorner[0].vY + igi2_frame.v17 * ptDiscardTask->atCorner[0].vX + v7;
  igi2_frame.Real64x3_Rotate_tTemp.vY = igi2_frame.v16 * ptDiscardTask->atCorner[0].vX + igi2_frame.v17 * ptDiscardTask->atCorner[0].vY + v7;
  igi2_frame.Real64x3_Rotate_tTemp.vZ = (ptDiscardTask->atCorner[0].vX + ptDiscardTask->atCorner[0].vY) * 0.0
                           + ptDiscardTask->atCorner[0].vZ;
  qmemcpy(ptDiscardTask->atCorner, &igi2_frame.Real64x3_Rotate_tTemp, 0x18u);
  ptDiscardTask->atCorner[0].vX = ptDiscardTask->atCorner[0].vX + ptDiscardTask->tPos.vX;
  ptDiscardTask->atCorner[0].vY = ptDiscardTask->atCorner[0].vY + ptDiscardTask->tPos.vY;
  ptDiscardTask->atCorner[0].vZ = ptDiscardTask->atCorner[0].vZ + ptDiscardTask->tPos.vZ;
  v8 = ptDiscardTask->atCorner[1].vZ * 0.0;
  igi2_frame.Real64x3_Rotate_tTemp.vX = v1 * ptDiscardTask->atCorner[1].vY + igi2_frame.v17 * ptDiscardTask->atCorner[1].vX + v8;
  igi2_frame.Real64x3_Rotate_tTemp.vY = igi2_frame.v17 * ptDiscardTask->atCorner[1].vY + igi2_frame.v16 * ptDiscardTask->atCorner[1].vX + v8;
  igi2_frame.Real64x3_Rotate_tTemp.vZ = (ptDiscardTask->atCorner[1].vX + ptDiscardTask->atCorner[1].vY) * 0.0
                           + ptDiscardTask->atCorner[1].vZ;
  qmemcpy(&ptDiscardTask->atCorner[1], &igi2_frame.Real64x3_Rotate_tTemp, sizeof(ptDiscardTask->atCorner[1]));
  ptDiscardTask->atCorner[1].vX = ptDiscardTask->atCorner[1].vX + ptDiscardTask->tPos.vX;
  ptDiscardTask->atCorner[1].vY = ptDiscardTask->atCorner[1].vY + ptDiscardTask->tPos.vY;
  ptDiscardTask->atCorner[1].vZ = ptDiscardTask->atCorner[1].vZ + ptDiscardTask->tPos.vZ;
  v9 = ptDiscardTask->atCorner[2].vZ * 0.0;
  igi2_frame.Real64x3_Rotate_tTemp.vX = v1 * ptDiscardTask->atCorner[2].vY + igi2_frame.v17 * ptDiscardTask->atCorner[2].vX + v9;
  igi2_frame.Real64x3_Rotate_tTemp.vY = igi2_frame.v16 * ptDiscardTask->atCorner[2].vX + igi2_frame.v17 * ptDiscardTask->atCorner[2].vY + v9;
  igi2_frame.Real64x3_Rotate_tTemp.vZ = (ptDiscardTask->atCorner[2].vX + ptDiscardTask->atCorner[2].vY) * 0.0
                           + ptDiscardTask->atCorner[2].vZ;
  qmemcpy(&ptDiscardTask->atCorner[2], &igi2_frame.Real64x3_Rotate_tTemp, sizeof(ptDiscardTask->atCorner[2]));
  ptDiscardTask->atCorner[2].vX = ptDiscardTask->atCorner[2].vX + ptDiscardTask->tPos.vX;
  ptDiscardTask->atCorner[2].vY = ptDiscardTask->atCorner[2].vY + ptDiscardTask->tPos.vY;
  ptDiscardTask->atCorner[2].vZ = ptDiscardTask->atCorner[2].vZ + ptDiscardTask->tPos.vZ;
  v10 = ptDiscardTask->atCorner[3].vZ * 0.0;
  igi2_frame.Real64x3_Rotate_tTemp.vX = v1 * ptDiscardTask->atCorner[3].vY + igi2_frame.v17 * ptDiscardTask->atCorner[3].vX + v10;
  igi2_frame.Real64x3_Rotate_tTemp.vY = igi2_frame.v17 * ptDiscardTask->atCorner[3].vY + igi2_frame.v16 * ptDiscardTask->atCorner[3].vX + v10;
  igi2_frame.Real64x3_Rotate_tTemp.vZ = (ptDiscardTask->atCorner[3].vX + ptDiscardTask->atCorner[3].vY) * 0.0
                           + ptDiscardTask->atCorner[3].vZ;
  qmemcpy(&ptDiscardTask->atCorner[3], &igi2_frame.Real64x3_Rotate_tTemp, sizeof(ptDiscardTask->atCorner[3]));
  ptDiscardTask->atCorner[3].vX = ptDiscardTask->atCorner[3].vX + ptDiscardTask->tPos.vX;
  ptDiscardTask->atCorner[3].vY = ptDiscardTask->atCorner[3].vY + ptDiscardTask->tPos.vY;
  ptDiscardTask->atCorner[3].vZ = ptDiscardTask->atCorner[3].vZ + ptDiscardTask->tPos.vZ;
  v11 = ptDiscardTask->atCorner[4].vZ * 0.0;
  igi2_frame.Real64x3_Rotate_tTemp.vX = v1 * ptDiscardTask->atCorner[4].vY + igi2_frame.v17 * ptDiscardTask->atCorner[4].vX + v11;
  igi2_frame.Real64x3_Rotate_tTemp.vY = igi2_frame.v16 * ptDiscardTask->atCorner[4].vX + igi2_frame.v17 * ptDiscardTask->atCorner[4].vY + v11;
  igi2_frame.Real64x3_Rotate_tTemp.vZ = (ptDiscardTask->atCorner[4].vX + ptDiscardTask->atCorner[4].vY) * 0.0
                           + ptDiscardTask->atCorner[4].vZ;
  qmemcpy(&ptDiscardTask->atCorner[4], &igi2_frame.Real64x3_Rotate_tTemp, sizeof(ptDiscardTask->atCorner[4]));
  ptDiscardTask->atCorner[4].vX = ptDiscardTask->atCorner[4].vX + ptDiscardTask->tPos.vX;
  ptDiscardTask->atCorner[4].vY = ptDiscardTask->atCorner[4].vY + ptDiscardTask->tPos.vY;
  ptDiscardTask->atCorner[4].vZ = ptDiscardTask->atCorner[4].vZ + ptDiscardTask->tPos.vZ;
  v12 = ptDiscardTask->atCorner[5].vZ * 0.0;
  igi2_frame.Real64x3_Rotate_tTemp.vX = v1 * ptDiscardTask->atCorner[5].vY + igi2_frame.v17 * ptDiscardTask->atCorner[5].vX + v12;
  igi2_frame.Real64x3_Rotate_tTemp.vY = igi2_frame.v17 * ptDiscardTask->atCorner[5].vY + igi2_frame.v16 * ptDiscardTask->atCorner[5].vX + v12;
  igi2_frame.Real64x3_Rotate_tTemp.vZ = (ptDiscardTask->atCorner[5].vX + ptDiscardTask->atCorner[5].vY) * 0.0
                           + ptDiscardTask->atCorner[5].vZ;
  qmemcpy(&ptDiscardTask->atCorner[5], &igi2_frame.Real64x3_Rotate_tTemp, sizeof(ptDiscardTask->atCorner[5]));
  ptDiscardTask->atCorner[5].vX = ptDiscardTask->atCorner[5].vX + ptDiscardTask->tPos.vX;
  ptDiscardTask->atCorner[5].vY = ptDiscardTask->atCorner[5].vY + ptDiscardTask->tPos.vY;
  ptDiscardTask->atCorner[5].vZ = ptDiscardTask->atCorner[5].vZ + ptDiscardTask->tPos.vZ;
  v13 = ptDiscardTask->atCorner[6].vZ * 0.0;
  igi2_frame.Real64x3_Rotate_tTemp.vX = v1 * ptDiscardTask->atCorner[6].vY + igi2_frame.v17 * ptDiscardTask->atCorner[6].vX + v13;
  igi2_frame.Real64x3_Rotate_tTemp.vY = igi2_frame.v16 * ptDiscardTask->atCorner[6].vX + igi2_frame.v17 * ptDiscardTask->atCorner[6].vY + v13;
  igi2_frame.Real64x3_Rotate_tTemp.vZ = (ptDiscardTask->atCorner[6].vX + ptDiscardTask->atCorner[6].vY) * 0.0
                           + ptDiscardTask->atCorner[6].vZ;
  qmemcpy(&ptDiscardTask->atCorner[6], &igi2_frame.Real64x3_Rotate_tTemp, sizeof(ptDiscardTask->atCorner[6]));
  ptDiscardTask->atCorner[6].vX = ptDiscardTask->atCorner[6].vX + ptDiscardTask->tPos.vX;
  ptDiscardTask->atCorner[6].vY = ptDiscardTask->atCorner[6].vY + ptDiscardTask->tPos.vY;
  ptDiscardTask->atCorner[6].vZ = ptDiscardTask->atCorner[6].vZ + ptDiscardTask->tPos.vZ;
  v14 = v1;
  v15 = ptDiscardTask->atCorner[7].vZ * 0.0;
  igi2_frame.Real64x3_Rotate_tTemp.vX = v14 * ptDiscardTask->atCorner[7].vY + igi2_frame.v17 * ptDiscardTask->atCorner[7].vX + v15;
  igi2_frame.Real64x3_Rotate_tTemp.vY = igi2_frame.v17 * ptDiscardTask->atCorner[7].vY + igi2_frame.v16 * ptDiscardTask->atCorner[7].vX + v15;
  igi2_frame.Real64x3_Rotate_tTemp.vZ = (ptDiscardTask->atCorner[7].vX + ptDiscardTask->atCorner[7].vY) * 0.0
                           + ptDiscardTask->atCorner[7].vZ;
  qmemcpy(&ptDiscardTask->atCorner[7], &igi2_frame.Real64x3_Rotate_tTemp, sizeof(ptDiscardTask->atCorner[7]));
  ptDiscardTask->atCorner[7].vX = ptDiscardTask->atCorner[7].vX + ptDiscardTask->tPos.vX;
  ptDiscardTask->atCorner[7].vY = ptDiscardTask->atCorner[7].vY + ptDiscardTask->tPos.vY;
  ptDiscardTask->atCorner[7].vZ = ptDiscardTask->atCorner[7].vZ + ptDiscardTask->tPos.vZ;
}

// source: h/2/discardtask.c:127  [anchor-mhash]
enum bool __cdecl DiscardTask_IsDiscardVertex(struct real32x3_t *ptPos)
{
  int v1; // esi
  struct QTask_s **i; // edi
  float *v3; // ecx

  v1 = 0;
  if ( DiscardTask_ptQTaskList->nTask <= 0 )
    return false;
  for ( i = DiscardTask_ptQTaskList->ptQTask; ; ++i )
  {
    v3 = (float *)*i;
    if ( ptPos->vX >= (double)*(float *)&(*i)[8].tQTaskChildren.ptHead
      && ptPos->vX <= (double)v3[83]
      && ptPos->vY >= (double)v3[85]
      && ptPos->vY <= (double)v3[84] )
    {
      break;
    }
    if ( ++v1 >= DiscardTask_ptQTaskList->nTask )
      return false;
  }
  return true;
}

// source: h/2/discardtask.c:159  [anchor-hash]
struct QTask_s *__cdecl DiscardTask_Update(struct QTask_s *ptQTask)
{
  struct QTask_s *result; // eax
  int (__cdecl *pfHandler)(struct QTask_s *); // ecx

  result = ptQTask->ptParent;
  if ( result )
  {
    pfHandler = (int (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[DiscardTask_eUpdateDiscardMeshQTaskEvent][result->eQTaskType].pfHandler;
    if ( pfHandler )
      return (struct QTask_s *)pfHandler(result);
  }
  return result;
}

// source: h/2/discardtask.c:181  [anchor-mhash]
void __cdecl DiscardTask_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ptQTask[7].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[7].tQTaskRefList.ptTail = nullptr;
  ptQTask[7].ptParent = nullptr;
  *(_DWORD *)&ptQTask[7].eQTaskType = 0;
  ptQTask[8].ptNext = nullptr;
  ptQTask[8].ptPrev = nullptr;
  ptQTask[8].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[9].ptPrev = (struct QTask_s *)1084227584;
  ptQTask[9].ptNext = (struct QTask_s *)1084227584;
  ptQTask[9].tQTaskChildren.ptHead = nullptr;
  LOBYTE(ptQTask[9].tQTaskChildren.ptMiddle) = 1;
  ptQTask[9].tQTaskChildren.ptTail = nullptr;
  DiscardTask_UpdateCorners((struct DiscardTask_s *)ptQTask);
  QTaskList_Register(DiscardTask_ptQTaskList, (struct QTaskList_s *)ptQTask);
}

// source: h/2/discardtask.c:205  [anchor-mhash]
void __cdecl DiscardTask_DeleteHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptParent; // eax
  void (__cdecl *pfHandler)(struct QTask_s *); // ecx
  struct QTask_s *ptMiddle; // eax
  struct QTask_s *ptTail; // eax

  QTaskList_Remove(DiscardTask_ptQTaskList, ptQTask);
  ptParent = ptQTask->ptParent;
  ptQTask[9].ptPrev = nullptr;
  ptQTask[9].ptNext = nullptr;
  if ( ptParent )
  {
    pfHandler = (void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[DiscardTask_eUpdateDiscardMeshQTaskEvent][ptParent->eQTaskType].pfHandler;
    if ( pfHandler )
      pfHandler(ptParent);
  }
  if ( ptQTask[9].tQTaskChildren.ptHead )
  {
    ptMiddle = ptQTask[2].tQTaskChildren.ptMiddle;
    if ( ptMiddle )
      ptMiddle[2].tQTaskChildren.ptTail = ptQTask[2].tQTaskChildren.ptTail;
    else
      World_ptActiveWorld->ptManualRedrawList = (struct DynCubeObj_s *)ptQTask[2].tQTaskChildren.ptTail;
    ptTail = ptQTask[2].tQTaskChildren.ptTail;
    if ( ptTail )
      ptTail[2].tQTaskChildren.ptMiddle = ptQTask[2].tQTaskChildren.ptMiddle;
  }
}

// source: h/2/discardtask.c:249  [size]
void __cdecl DiscardTask_EnterHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ;
}

// source: h/2/discardtask.c:284  [anchor-mhash]
void __cdecl DiscardTask_GetCameraTargetInfoHandler(struct QTask_s *ptQTask, void *pxContext)
{
  long double v3; // st7
  long double v4; // st6
  double v5; // st7
  struct QTask_s *ptQTaska = *(struct QTask_s * *)&ptQTask; // [esp+10h] [ebp+4h] ARGSLOT

  qmemcpy(pxContext, &ptQTask[7].tQTaskRefList.ptMiddle, 0x18u);
  ptQTaska = (struct QTask_s *)ptQTask[8].tQTaskRefList.ptMiddle;
  *((_DWORD *)pxContext + 11) = 0;
  *((_DWORD *)pxContext + 14) = 0;
  v3 = sin(*(float *)&ptQTaska);
  *((_DWORD *)pxContext + 15) = 0;
  *((_DWORD *)pxContext + 16) = 0;
  *((_DWORD *)pxContext + 17) = 1065353216;
  *((_DWORD *)pxContext + 18) = 0;
  v4 = cos(*(float *)&ptQTaska);
  *((float *)pxContext + 9) = v4;
  *((float *)pxContext + 10) = -v3;
  *((float *)pxContext + 12) = v3;
  *((float *)pxContext + 13) = v4;
  if ( *(float *)&ptQTask[9].ptNext <= (double)*(float *)&ptQTask[9].ptPrev )
    v5 = *(float *)&ptQTask[9].ptPrev * 4096.0;
  else
    v5 = *(float *)&ptQTask[9].ptNext * 4096.0;
  *((_DWORD *)pxContext + 20) = 0;
  *((float *)pxContext + 19) = v5;
}

// source: h/2/discardtask.c:316  [anchor-caller]
void __cdecl DiscardTask_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  bool v3; // zf
  DWORD TickCount; // eax
  struct QTask_s *ptParent; // eax
  void (__cdecl *pfHandler)(struct QTask_s *); // ecx
  struct QTask_s *v7; // edx
  double v8; // rt0
  double v9; // st6
  double v10; // st6
  double tRelative_16; // [esp+18h] [ebp-Ch]
  float ptQTaska = *(float *)&ptQTask; // [esp+28h] [ebp+4h] ARGSLOT

  DiscardTask_UpdateCorners((struct DiscardTask_s *)ptQTask);
  v3 = Timer_isPerformanceCounter == 0;
  ptQTask[9].tQTaskChildren.ptTail = (struct QTask_s *)1;
  if ( v3 )
    TickCount = GetTickCount();
  else
    TickCount = Timer_GetPerformanceCounter();
  ptQTask[9].tQTaskRefList.ptHead = (struct QReference_s *)(TickCount - Timer_nStartTime);
  if ( pxContext && *(_DWORD *)pxContext || LOBYTE(ptQTask[9].tQTaskChildren.ptMiddle) )
  {
    ptParent = ptQTask->ptParent;
    if ( ptParent )
    {
      pfHandler = (void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[DiscardTask_eUpdateDiscardMeshQTaskEvent][ptParent->eQTaskType].pfHandler;
      if ( pfHandler )
        pfHandler(ptQTask->ptParent);
    }
    ptQTask[9].tQTaskChildren.ptTail = nullptr;
    LOBYTE(ptQTask[9].tQTaskChildren.ptMiddle) = 0;
  }
  v7 = ptQTask->ptParent;
  if ( v7 )
  {
    if ( QTask_IsQTaskTypeDerived(v7->eQTaskType, DynCubeObj_eQTaskType) )
    {
      tRelative_16 = *(double *)&ptQTask[8].ptNext - *(double *)&v7[1].tQTaskChildren.ptTail;
      v8 = *(double *)&ptQTask[7].ptParent - *(double *)&v7[1].tQTaskChildren.ptHead;
      ptQTaska = *(double *)&ptQTask[7].tQTaskRefList.ptMiddle - *(double *)&v7[1].ptNext;
      *(float *)&ptQTask[8].tQTaskRefList.ptTail = ptQTaska;
      *(float *)&ptQTask[8].ptParent = v8;
      *(float *)&ptQTask[8].eQTaskType = tRelative_16;
      v9 = *(float *)&ptQTask[9].ptNext * 2048.0;
      *(float *)&ptQTask[8].tQTaskChildren.ptHead = ptQTaska - v9;
      *(float *)&ptQTask[8].tQTaskChildren.ptMiddle = v9 + ptQTaska;
      v10 = *(float *)&ptQTask[9].ptPrev * 2048.0;
      *(float *)&ptQTask[8].tQTaskRefList.ptHead = v8 - v10;
      *(float *)&ptQTask[8].tQTaskChildren.ptTail = v10 + v8;
    }
  }
}

// source: h/2/discardtask.c:384  [size]
void __cdecl DiscardTask_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = DiscardTask_ptParameterList;
}

// source: h/2/discardtask.c:400  [anchor-mhash]
void __cdecl DiscardTask_DiscardMeshHandler(struct QTask_s *ptQTask, void *pxContext)
{
  float ptDiscardMeshContext; // [esp+0h] [ebp-20h]
  float ptDiscardMeshContexta; // [esp+0h] [ebp-20h]
  float vX0; // [esp+4h] [ebp-1Ch]
  float vX0a; // [esp+4h] [ebp-1Ch]
  float vY0; // [esp+8h] [ebp-18h]
  float vY0a; // [esp+8h] [ebp-18h]
  float vX1; // [esp+Ch] [ebp-14h]
  float vX1a; // [esp+Ch] [ebp-14h]
  float vY1; // [esp+10h] [ebp-10h]
  float vY1a; // [esp+10h] [ebp-10h]
  float vX2; // [esp+14h] [ebp-Ch]
  float vX2a; // [esp+14h] [ebp-Ch]

  if ( *(float *)&ptQTask[9].ptPrev > 0.0 && *(float *)&ptQTask[9].ptNext > 0.0 )
  {
    vX2 = *(double *)&ptQTask[4].tQTaskChildren.ptHead;
    vY1 = *(double *)&ptQTask[4].ptNext;
    vX1 = *(double *)&ptQTask[3].tQTaskRefList.ptMiddle;
    vY0 = *(double *)&ptQTask[3].tQTaskChildren.ptTail;
    vX0 = *(double *)&ptQTask[3].ptNext;
    ptDiscardMeshContext = *(double *)&ptQTask[2].ptParent;
    Discard2D_RegisterDiscardTriangle(
      (struct DiscardMeshContext_s *)pxContext,
      ptDiscardMeshContext,
      vX0,
      vY0,
      vX1,
      vY1,
      vX2);
    vX2a = *(double *)&ptQTask[4].ptParent;
    vY1a = *(double *)&ptQTask[4].tQTaskRefList.ptMiddle;
    vX1a = *(double *)&ptQTask[4].tQTaskChildren.ptHead;
    vY0a = *(double *)&ptQTask[4].ptNext;
    vX0a = *(double *)&ptQTask[3].tQTaskRefList.ptMiddle;
    ptDiscardMeshContexta = *(double *)&ptQTask[3].tQTaskChildren.ptTail;
    Discard2D_RegisterDiscardTriangle(
      (struct DiscardMeshContext_s *)pxContext,
      ptDiscardMeshContexta,
      vX0a,
      vY0a,
      vX1a,
      vY1a,
      vX2a);
  }
}

// source: h/2/discardtask.c:435  [size]
unsigned __int16 __cdecl DiscardTask_GetQTaskType()
{
  return DiscardTask_eQTaskType;
}

// source: h/2/discardtask.c:448  [size]
__int16 __cdecl DiscardTask_GetDiscardMeshQTaskEvent()
{
  return DiscardTask_eDiscardMeshQTaskEvent;
}

// source: h/2/discardtask.c:461  [size]
int __cdecl DiscardTask_GetUpdateDiscardMeshQTaskEvent()
{
  return DiscardTask_eUpdateDiscardMeshQTaskEvent;
}

// source: h/2/discardtask.c:474  [anchor-hash]
void __cdecl DiscardTask_Open()
{
  unsigned __int16 BaseQTaskType; // ax
  int v1; // eax
  unsigned __int16 v2; // si
  struct ParameterList_s *v3; // eax
  int v4; // edx

  BaseQTaskType = QTask_GetBaseQTaskType();
  DiscardTask_eQTaskType = QTask_NewQTaskType("DiscardTask", 384, BaseQTaskType, 0, 0);
  DiscardTask_eDiscardMeshQTaskEvent = QTask_NewQTaskEventFn(0, "DiscardMesh");
  v1 = QTask_NewQTaskEventNoContextFn(0, "UpdateDiscardMesh");
  v2 = DiscardTask_eQTaskType;
  DiscardTask_eUpdateDiscardMeshQTaskEvent = v1;
  QTask_LinkQTaskEventHandlerFn(DiscardTask_eQTaskType, 0, DiscardTask_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v2, 2, DiscardTask_DeleteHandler);
  QTask_LinkQTaskEventHandlerFn(v2, 5, (void (__cdecl *)(struct QTask_s *, void *))DiscardTask_EnterHandler);
  QTask_LinkQTaskEventHandlerFn(v2, ParameterList_eUpdateInternalDataQTaskEvent, DiscardTask_UpdateInternalDataHandler);
  QTask_LinkQTaskEventHandlerFn(
    v2,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))DiscardTask_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(v2, 8, DiscardTask_GetCameraTargetInfoHandler);
  QTask_LinkQTaskEventHandlerFn(v2, DiscardTask_eDiscardMeshQTaskEvent, DiscardTask_DiscardMeshHandler);
  QTask_LinkQTaskEventHandlerFn(v2, DynCubeObj_eDynCubeObjRegisterQTaskEvent, nullptr);
  QTask_LinkQTaskEventHandlerFn(v2, DynCubeObj_eDynCubeObjRemoveQTaskEvent, nullptr);
  QTask_LinkQTaskEventHandlerFn(
    v2,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveHandler);
  v3 = (struct ParameterList_s *)Mem_AllocFn(112, 4);
  v4 = Level_eParameterTypeObjectPos;
  v3->ptParameterListItem = (struct ParameterListItem_s *)&v3[1];
  v3->nParameters = 0;
  v3->nMaxParameters = 5;
  DiscardTask_ptParameterList = v3;
  ParameterList_AddParameter(v3, 0x130u, v4, "Position", 7u, nullptr);
  ParameterList_AddParameterMinMax(
    DiscardTask_ptParameterList,
    0x168u,
    Level_eParameterTypeReal32,
    "Width",
    7u,
    0.0,
    10000.0);
  ParameterList_AddParameterMinMax(
    DiscardTask_ptParameterList,
    0x16Cu,
    Level_eParameterTypeReal32,
    "Height",
    7u,
    0.0,
    10000.0);
  ParameterList_AddParameter(DiscardTask_ptParameterList, 0x174u, Level_eParameterTypePushButton, "Update", 6u, nullptr);
  DiscardTask_ptQTaskList = QTaskList_New(256);
}

// source: h/2/discardtask.c:518  [anchor-hash]
void __cdecl DiscardTask_Close()
{
  int v0; // esi

  QTaskList_Delete(DiscardTask_ptQTaskList);
  if ( DiscardTask_ptParameterList )
  {
    v0 = *(_DWORD *)((unsigned int)&DiscardTask_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
  QTask_DeleteQTaskEventNoContext(DiscardTask_eUpdateDiscardMeshQTaskEvent);
  QTask_DeleteQTaskEvent(DiscardTask_eDiscardMeshQTaskEvent);
  QTask_DeleteQTaskType(DiscardTask_eQTaskType);
}
