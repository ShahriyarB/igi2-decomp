/* j/0/effects/mosquitoswarm.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/effects/mosquitoswarm.c:88  [anchor-mhash]
void __cdecl MosquitoSwarm_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct World_s *ptWorld; // ecx
  struct DynCubeObj_s *ptManualRedrawList; // edx
  struct DynCubeObj_s *ptPrev; // edx

  ptWorld = Game_ptGame->ptWorld;
  ptManualRedrawList = ptWorld->ptManualRedrawList;
  if ( ptManualRedrawList )
  {
    ptManualRedrawList->ptPrev = (struct DynCubeObj_s *)ptQTask;
    ptWorld->ptManualRedrawList->ptPrev->ptNext = ptWorld->ptManualRedrawList;
    ptPrev = ptWorld->ptManualRedrawList->ptPrev;
    ptWorld->ptManualRedrawList = ptPrev;
    ptPrev->ptPrev = nullptr;
  }
  else
  {
    ptWorld->ptManualRedrawList = (struct DynCubeObj_s *)ptQTask;
    ptQTask[2].tQTaskChildren.ptTail = nullptr;
    ptWorld->ptManualRedrawList->ptPrev = nullptr;
  }
  ptQTask[2].ptParent = nullptr;
  *(_DWORD *)&ptQTask[2].eQTaskType = 0;
  ptQTask[3].ptNext = nullptr;
  ptQTask[3].ptPrev = nullptr;
  ptQTask[3].tQTaskChildren.ptHead = nullptr;
  ptQTask[3].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[93].ptParent = nullptr;
  ptQTask[3].tQTaskChildren.ptTail = (struct QTask_s *)1069547520;
  ptQTask[3].tQTaskRefList.ptHead = (struct QReference_s *)1103626240;
  ptQTask[3].tQTaskRefList.ptMiddle = (struct QReference_s *)30;
}

// source: j/0/effects/mosquitoswarm.c:114  [size]
void __cdecl MosquitoSwarm_DeleteHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptMiddle; // ecx
  struct QTask_s *ptTail; // ecx

  ptMiddle = ptQTask[2].tQTaskChildren.ptMiddle;
  if ( ptMiddle )
    ptMiddle[2].tQTaskChildren.ptTail = ptQTask[2].tQTaskChildren.ptTail;
  else
    Game_ptGame->ptWorld->ptManualRedrawList = (struct DynCubeObj_s *)ptQTask[2].tQTaskChildren.ptTail;
  ptTail = ptQTask[2].tQTaskChildren.ptTail;
  if ( ptTail )
    ptTail[2].tQTaskChildren.ptMiddle = ptQTask[2].tQTaskChildren.ptMiddle;
}

// source: j/0/effects/mosquitoswarm.c:131  [anchor-mhash]
void __cdecl MosquitoSwarm_RunHandler(struct QTask_s *ptQTask)
{
  int v1; // edi
  float *p_ptPrev; // eax
  int v3; // edx
  int v4; // ecx
  unsigned int v5; // edx
  int v6; // edx
  int v7; // ecx
  unsigned int v8; // edx
  int v9; // edx
  int v10; // ecx
  unsigned int v11; // edx
  double v12; // st7
  double v13; // st3
  double v14; // st6
  double v15; // st3
  float vRadius; // [esp+Ch] [ebp-1Ch]
  int v17; // [esp+10h] [ebp-18h]
  float vAngle2; // [esp+18h] [ebp-10h]
  int vAngle2a; // [esp+18h] [ebp-10h]
  float vAngle3; // [esp+20h] [ebp-8h]

  vRadius = *(float *)&ptQTask[3].tQTaskChildren.ptTail * 4096.0;
  if ( ptQTask[3].tQTaskRefList.ptTail )
  {
    v1 = 0;
    if ( (int)ptQTask[3].tQTaskRefList.ptMiddle > 0 )
    {
      p_ptPrev = (float *)&ptQTask[4].ptPrev;
      do
      {
        v3 = *((_DWORD *)p_ptPrev + 1);
        v4 = *(_DWORD *)p_ptPrev + 1;
        *(_DWORD *)p_ptPrev = v4;
        if ( v4 > v3 )
        {
          *p_ptPrev = 0.0;
          v5 = (MosquitoSwarm_tRandomState.anRandom[0] >> 7) ^ MosquitoSwarm_tRandomState.anRandom[2];
          MosquitoSwarm_tRandomState.anRandom[0] += v5 ^ MosquitoSwarm_tRandomState.anRandom[1];
          MosquitoSwarm_tRandomState.anRandom[2] = v5;
          MosquitoSwarm_tRandomState.anRandom[1] ^= v5;
          *((_DWORD *)p_ptPrev + 1) = (__int64)((double)LOWORD(MosquitoSwarm_tRandomState.anRandom[0])
                                              * 0.0000152587890625
                                              * 120.0
                                              + 5.0);
        }
        v6 = *((_DWORD *)p_ptPrev + 3);
        v7 = *((_DWORD *)p_ptPrev + 2) + 1;
        *((_DWORD *)p_ptPrev + 2) = v7;
        if ( v7 > v6 )
        {
          p_ptPrev[2] = 0.0;
          v8 = (MosquitoSwarm_tRandomState.anRandom[0] >> 7) ^ MosquitoSwarm_tRandomState.anRandom[2];
          MosquitoSwarm_tRandomState.anRandom[0] += v8 ^ MosquitoSwarm_tRandomState.anRandom[1];
          MosquitoSwarm_tRandomState.anRandom[2] = v8;
          MosquitoSwarm_tRandomState.anRandom[1] ^= v8;
          *((_DWORD *)p_ptPrev + 3) = (__int64)((double)LOWORD(MosquitoSwarm_tRandomState.anRandom[0])
                                              * 0.0000152587890625
                                              * 120.0
                                              + 5.0);
        }
        v9 = *((_DWORD *)p_ptPrev + 5);
        v10 = *((_DWORD *)p_ptPrev + 4) + 1;
        *((_DWORD *)p_ptPrev + 4) = v10;
        if ( v10 > v9 )
        {
          p_ptPrev[4] = 0.0;
          v11 = (MosquitoSwarm_tRandomState.anRandom[0] >> 7) ^ MosquitoSwarm_tRandomState.anRandom[2];
          MosquitoSwarm_tRandomState.anRandom[0] += v11 ^ MosquitoSwarm_tRandomState.anRandom[1];
          MosquitoSwarm_tRandomState.anRandom[2] = v11;
          MosquitoSwarm_tRandomState.anRandom[1] ^= v11;
          *((_DWORD *)p_ptPrev + 5) = (__int64)((double)LOWORD(MosquitoSwarm_tRandomState.anRandom[0])
                                              * 0.0000152587890625
                                              * 120.0
                                              + 5.0);
        }
        vAngle2 = (double)*((int *)p_ptPrev + 2) / (double)*((int *)p_ptPrev + 3);
        vAngle3 = (double)*((int *)p_ptPrev + 4) / (double)*((int *)p_ptPrev + 5);
        v12 = (double)*(int *)p_ptPrev / (double)*((int *)p_ptPrev + 1) * 4096.0;
        v17 = (__int64)v12;
        v13 = vAngle2 * 4096.0;
        *(p_ptPrev - 3) = ((v12 - (double)v17) * Real32_avSin[v17 & 0xFFF].vY
                         + (v13 - (double)(int)(__int64)v13) * Real32_avSin[(__int64)v13 & 0xFFF].vY
                         + Real32_avSin[v17 & 0xFFF].vX
                         + Real32_avSin[(__int64)v13 & 0xFFF].vX)
                        * vRadius;
        vAngle2a = (__int64)v13;
        v14 = v13 - (double)vAngle2a;
        v15 = vAngle3 * 4096.0;
        *(p_ptPrev - 2) = (v14 * Real32_avSin[vAngle2a & 0xFFF].vY
                         + (v15 - (double)(int)(__int64)v15) * Real32_avSin[(__int64)v15 & 0xFFF].vY
                         + Real32_avSin[vAngle2a & 0xFFF].vX
                         + Real32_avSin[(__int64)v15 & 0xFFF].vX)
                        * vRadius;
        ++v1;
        p_ptPrev += 9;
        *(p_ptPrev - 10) = ((v15 - (double)(int)(__int64)v15) * Real32_avSin[(__int64)v15 & 0xFFF].vY
                          + (v12 - (double)v17) * Real32_avSin[v17 & 0xFFF].vY
                          + Real32_avSin[(__int64)v15 & 0xFFF].vX
                          + Real32_avSin[v17 & 0xFFF].vX)
                         * vRadius;
      }
      while ( v1 < (int)ptQTask[3].tQTaskRefList.ptMiddle );
    }
  }
}

// source: j/0/effects/mosquitoswarm.c:191  [anchor-mhash]
void __cdecl MosquitoSwarm_EnterHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct QTask_s *v23; };
    struct { char igi2_o1[4]; float vDepth; };
    struct { char igi2_o2[8]; double *v25; };
    struct { char igi2_o3[12]; struct real32x2_t tScreenPos; };
    struct { char igi2_o4[20]; struct real32x3_t tRGB; };
    struct { char igi2_o5[32]; struct real64x3_t tPos1; };
    struct { char igi2_o6[56]; struct real64x3_t tPos2; };
    struct { char igi2_o7[80]; struct real64x3_t tPos3; };
    char igi2_extent[104];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *v2; // esi
  double *p_ptParent; // edi
  struct QReference_s *ptMiddle; // eax
  float *v5; // eax
  unsigned int v6; // ecx
  unsigned int v7; // edx
  unsigned int v8; // eax
  double v9; // st7
  int v10; // ecx
  int v11; // edx
  unsigned int v12; // eax
  double v13; // st7
  int v14; // ecx
  int v15; // edx
  unsigned int v16; // eax
  int v17; // ecx
  int v18; // edx
  unsigned int v19; // eax
  int v20; // ecx
  int v21; // edx
  bool v22; // cc

  v2 = ptQTask;
  p_ptParent = (double *)&ptQTask[2].ptParent;
  igi2_frame.v25 = (double *)&ptQTask[2].ptParent;
  TransContext_ProjectWorldPos2(
    &TransContext_tActiveTransContext,
    &igi2_frame.tScreenPos,
    &igi2_frame.vDepth,
    (struct real64x3_t *)&ptQTask[2].ptParent);
  if ( *(float *)&ptQTask[3].tQTaskRefList.ptHead * 4096.0 >= igi2_frame.vDepth )
  {
    ptMiddle = ptQTask[3].tQTaskRefList.ptMiddle;
    ptQTask[3].tQTaskRefList.ptTail = (struct QReference_s *)1;
    memset(&igi2_frame.tRGB, 0, sizeof(igi2_frame.tRGB));
    igi2_frame.vDepth = 0.0;
    if ( (int)ptMiddle > 0 )
    {
      v5 = (float *)&ptQTask[4];
      igi2_frame.v23 = ptQTask + 4;
      while ( 1 )
      {
        igi2_frame.tPos1.vX = *(v5 - 2) + *p_ptParent;
        igi2_frame.tPos1.vY = *(v5 - 1) + *(double *)&v2[3].ptNext;
        igi2_frame.tPos1.vZ = *v5 + *(double *)&v2[3].tQTaskChildren.ptHead;
        qmemcpy(&igi2_frame.tPos2, &igi2_frame.tPos1, sizeof(igi2_frame.tPos2));
        qmemcpy(&igi2_frame.tPos3, &igi2_frame.tPos1, sizeof(igi2_frame.tPos3));
        v6 = (MosquitoSwarm_tRandomState.anRandom[0] >> 7) ^ MosquitoSwarm_tRandomState.anRandom[2];
        v7 = v6 ^ MosquitoSwarm_tRandomState.anRandom[1];
        v8 = (v6 ^ MosquitoSwarm_tRandomState.anRandom[1]) + MosquitoSwarm_tRandomState.anRandom[0];
        v9 = (double)(unsigned __int16)v8;
        v10 = (v8 >> 7) ^ v6;
        v11 = v10 ^ v7;
        v12 = v11 + v8;
        igi2_frame.tPos2.vX = (v9 * 0.0000152587890625 - 0.5) * 409.6000061035156 + igi2_frame.tPos1.vX;
        v13 = (double)(unsigned __int16)v12;
        v14 = (v12 >> 7) ^ v10;
        v15 = v14 ^ v11;
        v16 = v15 + v12;
        LODWORD(igi2_frame.tScreenPos.vX) = v16 & 1;
        igi2_frame.tPos2.vY = (v13 * 0.0000152587890625 - 0.5) * 409.6000061035156 + igi2_frame.tPos2.vY;
        v17 = (v16 >> 7) ^ v14;
        v18 = v17 ^ v15;
        v19 = v18 + v16;
        igi2_frame.tPos2.vZ = (double)SLODWORD(igi2_frame.tScreenPos.vX) * 204.8000030517578 + igi2_frame.tPos2.vZ - 102.4000015258789;
        v20 = (v19 >> 7) ^ v17;
        v21 = v20 ^ v18;
        MosquitoSwarm_tRandomState.anRandom[0] = v21 + v19;
        LODWORD(igi2_frame.tScreenPos.vX) = (unsigned __int16)(v21 + v19);
        MosquitoSwarm_tRandomState.anRandom[2] = v20;
        igi2_frame.tPos3.vX = ((double)(unsigned __int16)v19 * 0.0000152587890625 - 0.5) * 409.6000061035156 + igi2_frame.tPos1.vX;
        MosquitoSwarm_tRandomState.anRandom[1] = v21;
        igi2_frame.tPos3.vY = ((double)SLODWORD(igi2_frame.tScreenPos.vX) * 0.0000152587890625 - 0.5) * 409.6000061035156 + igi2_frame.tPos3.vY;
        igi2_frame.tPos3.vZ = igi2_frame.tPos2.vZ;
        Line_DrawLine3D(&igi2_frame.tPos1, &igi2_frame.tPos2, &igi2_frame.tRGB, 1.0, &igi2_frame.tRGB, 0.0);
        Line_DrawLine3D(&igi2_frame.tPos1, &igi2_frame.tPos3, &igi2_frame.tRGB, 1.0, &igi2_frame.tRGB, 0.0);
        v22 = (int)(++LODWORD(igi2_frame.vDepth)) < (int)ptQTask[3].tQTaskRefList.ptMiddle;
        igi2_frame.v23 = (struct QTask_s *)((char *)igi2_frame.v23 + 36);
        if ( !v22 )
          break;
        v2 = ptQTask;
        v5 = (float *)igi2_frame.v23;
        p_ptParent = igi2_frame.v25;
      }
    }
  }
  else
  {
    ptQTask[3].tQTaskRefList.ptTail = nullptr;
  }
}

// source: j/0/effects/mosquitoswarm.c:257  [size]
void __cdecl MosquitoSwarm_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  int ptMiddle; // eax
  int v3; // edx
  struct QTask_s **p_ptMiddle; // eax
  unsigned int v5; // esi
  unsigned int v6; // esi
  unsigned int v7; // esi

  ptMiddle = (int)ptQTask[3].tQTaskRefList.ptMiddle;
  if ( ptMiddle >= 100 )
    ptMiddle = 100;
  v3 = 0;
  ptQTask[3].tQTaskRefList.ptMiddle = (struct QReference_s *)ptMiddle;
  if ( ptMiddle > 0 )
  {
    p_ptMiddle = &ptQTask[4].tQTaskChildren.ptMiddle;
    do
    {
      *(p_ptMiddle - 2) = nullptr;
      *p_ptMiddle = nullptr;
      p_ptMiddle[2] = nullptr;
      v5 = (MosquitoSwarm_tRandomState.anRandom[0] >> 7) ^ MosquitoSwarm_tRandomState.anRandom[2];
      MosquitoSwarm_tRandomState.anRandom[0] += v5 ^ MosquitoSwarm_tRandomState.anRandom[1];
      MosquitoSwarm_tRandomState.anRandom[2] = v5;
      MosquitoSwarm_tRandomState.anRandom[1] ^= v5;
      *(p_ptMiddle - 1) = (struct QTask_s *)(__int64)((double)LOWORD(MosquitoSwarm_tRandomState.anRandom[0])
                                                    * 0.0000152587890625
                                                    * 120.0
                                                    + 5.0);
      v6 = (MosquitoSwarm_tRandomState.anRandom[0] >> 7) ^ MosquitoSwarm_tRandomState.anRandom[2];
      MosquitoSwarm_tRandomState.anRandom[0] += v6 ^ MosquitoSwarm_tRandomState.anRandom[1];
      MosquitoSwarm_tRandomState.anRandom[2] = v6;
      MosquitoSwarm_tRandomState.anRandom[1] ^= v6;
      p_ptMiddle[1] = (struct QTask_s *)(__int64)((double)LOWORD(MosquitoSwarm_tRandomState.anRandom[0])
                                                * 0.0000152587890625
                                                * 120.0
                                                + 5.0);
      v7 = (MosquitoSwarm_tRandomState.anRandom[0] >> 7) ^ MosquitoSwarm_tRandomState.anRandom[2];
      MosquitoSwarm_tRandomState.anRandom[0] += v7 ^ MosquitoSwarm_tRandomState.anRandom[1];
      MosquitoSwarm_tRandomState.anRandom[2] = v7;
      MosquitoSwarm_tRandomState.anRandom[1] ^= v7;
      ++v3;
      p_ptMiddle += 9;
      *(p_ptMiddle - 6) = (struct QTask_s *)(__int64)((double)LOWORD(MosquitoSwarm_tRandomState.anRandom[0])
                                                    * 0.0000152587890625
                                                    * 120.0
                                                    + 5.0);
    }
    while ( v3 < (int)ptQTask[3].tQTaskRefList.ptMiddle );
  }
}

// source: j/0/effects/mosquitoswarm.c:292  [size]
void __cdecl MosquitoSwarm_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = MosquitoSwarm_ptParameterList;
}

// source: j/0/effects/mosquitoswarm.c:310  [size]
unsigned __int16 __cdecl MosquitoSwarm_GetQTaskType()
{
  return MosquitoSwarm_eQTaskType;
}

// source: j/0/effects/mosquitoswarm.c:323  [anchor-hash]
void __cdecl MosquitoSwarm_Open()
{
  unsigned __int16 v0; // si
  struct ParameterList_s *v1; // eax

  v0 = QTask_NewQTaskType("MosquitoSwarm", 3760, DynCubeObj_eQTaskType, 0, 0);
  MosquitoSwarm_eQTaskType = v0;
  QTask_LinkQTaskEventHandlerFn(v0, 0, MosquitoSwarm_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 2, MosquitoSwarm_DeleteHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 1, MosquitoSwarm_RunHandler);
  QTask_LinkQTaskEventHandlerFn(v0, 5, MosquitoSwarm_EnterHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    ParameterList_eUpdateInternalDataQTaskEvent,
    MosquitoSwarm_UpdateInternalDataHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))MosquitoSwarm_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(v0, DynCubeObj_eDynCubeObjRegisterQTaskEvent, nullptr);
  QTask_LinkQTaskEventHandlerFn(v0, DynCubeObj_eDynCubeObjRemoveQTaskEvent, nullptr);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveHandler);
  v1 = (struct ParameterList_s *)Mem_AllocFn(212, 4);
  v1->nParameters = 0;
  v1->nMaxParameters = 10;
  v1->ptParameterListItem = (struct ParameterListItem_s *)&v1[1];
  MosquitoSwarm_ptParameterList = v1;
  ParameterList_AddParameter(v1, 0x70u, Level_eParameterTypeObjectPos, "Position", 7u, nullptr);
  ParameterList_AddParameter(
    MosquitoSwarm_ptParameterList,
    0x88u,
    Level_eParameterTypeReal32,
    "Radius (meter)",
    7u,
    nullptr);
  ParameterList_AddParameter(
    MosquitoSwarm_ptParameterList,
    0x8Cu,
    Level_eParameterTypeReal32,
    "Cutoff Distance (meter)",
    7u,
    nullptr);
  ParameterList_AddParameter(
    MosquitoSwarm_ptParameterList,
    0x90u,
    Level_eParameterTypeInt32,
    "Individuals (max 100)",
    7u,
    nullptr);
  MosquitoSwarm_tRandomState.anRandom[0] = -227095208;
  MosquitoSwarm_tRandomState.anRandom[1] = 630847318;
  MosquitoSwarm_tRandomState.anRandom[2] = 1682079437;
}

// source: j/0/effects/mosquitoswarm.c:363  [size]
void __cdecl MosquitoSwarm_Close()
{
  int v0; // esi

  if ( MosquitoSwarm_ptParameterList )
  {
    v0 = *(_DWORD *)((unsigned int)&MosquitoSwarm_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
  QTask_DeleteQTaskType(MosquitoSwarm_eQTaskType);
}
