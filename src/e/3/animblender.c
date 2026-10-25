/* e/3/animblender.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: e/3/animblender.c:68  [anchor-mhash]
void __cdecl AnimBlender_RunHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptNext; // eax
  bool v2; // zf
  struct QTask_s *ptParent; // eax
  int v4; // ecx
  struct QTask_s *v5; // ecx
  struct QTask_s *ptMiddle; // eax
  struct QTask_s *ptHead; // ecx
  int v8; // edx
  struct QTask_s *v9; // eax
  void (__cdecl *pfHandler)(struct QTask_s *); // eax
  int v11; // edx

  ptNext = ptQTask[2].ptNext;
  if ( (int)ptNext < (int)ptQTask[2].ptPrev )
  {
    v5 = (struct QTask_s *)((char *)ptNext + (unsigned int)ptQTask[2].tQTaskChildren.ptHead);
    ptMiddle = ptQTask[1].tQTaskChildren.ptMiddle;
    ptQTask[2].ptNext = v5;
    if ( ptMiddle )
      ptMiddle->ptNext = (struct QTask_s *)1;
  }
  else
  {
    v2 = ((int)ptQTask[1].ptPrev & 1) == 0;
    ptQTask[1].ptPrev = (struct QTask_s *)((int)ptQTask[1].ptPrev | 4);
    if ( !v2 )
    {
      ptParent = ptQTask[1].ptParent;
      if ( ptParent )
      {
        v4 = (int)ptParent[1].ptPrev | 0x10;
        ptParent[1].ptParent = nullptr;
        ptParent[1].ptPrev = (struct QTask_s *)v4;
        QTask_DeleteChildren(ptParent);
      }
    }
  }
  ptHead = ptQTask->tQTaskChildren.ptHead;
  if ( ptHead->ptNext && ptHead )
  {
    v8 = QTask_nProtectedQTaskStackOffset;
    do
    {
      if ( ptHead->ptNext )
        v9 = ptHead->ptNext->ptNext != nullptr ? ptHead->ptNext : nullptr;
      else
        v9 = nullptr;
      QTask_atProtectedQTaskStack[v8].ptQTask = v9;
      pfHandler = (void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[1][ptHead->eQTaskType].pfHandler;
      v11 = v8 + 1;
      QTask_nProtectedQTaskStackOffset = v11;
      if ( pfHandler )
      {
        pfHandler(ptHead);
        v11 = QTask_nProtectedQTaskStackOffset;
      }
      ptHead = (struct QTask_s *)dword_849C7DC[v11];
      v8 = v11 - 1;
      QTask_nProtectedQTaskStackOffset = v8;
    }
    while ( ptHead );
  }
}

// source: e/3/animblender.c:105  [anchor-caller]
void __cdecl AnimBlender_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  unsigned __int8 *v2; // edi
  int v3; // ecx
  int v4; // ebx
  int v5; // edx
  int v6; // edx

  ptQTask[1].ptNext = *(struct QTask_s **)pxContext;
  ptQTask[1].ptPrev = nullptr;
  ptQTask[1].tQTaskChildren.ptHead = (struct QTask_s *)AnimBlender_aisAnimated;
  ptQTask[1].tQTaskChildren.ptTail = *(struct QTask_s **)(*(_DWORD *)pxContext + 316);
  ptQTask[1].tQTaskChildren.ptMiddle = (struct QTask_s *)(*(_DWORD *)pxContext + 288);
  ptQTask[1].tQTaskRefList.ptHead = (struct QReference_s *)(*(_DWORD *)pxContext + 296);
  ++*(_DWORD *)(*(_DWORD *)pxContext + 388);
  v2 = *(unsigned __int8 **)(*(_DWORD *)pxContext + 308);
  v3 = 0;
  v4 = 1;
  do
  {
    v5 = *v2;
    v4 += v5;
    ++v2;
    v6 = v5 + v3;
    v3 = v6 - 1;
  }
  while ( v6 > 0 );
  ptQTask[1].tQTaskRefList.ptMiddle = (struct QReference_s *)v4;
  ptQTask[2].tQTaskChildren.ptMiddle = (struct QTask_s *)1;
  AnimBlender_Blend(
    (struct AnimBlender_t *)ptQTask,
    *((struct AnimControllerBase_t **)pxContext + 1),
    *((struct AnimControllerBase_t **)pxContext + 2),
    *((_DWORD *)pxContext + 3));
}

// source: e/3/animblender.c:146  [size]
void __cdecl AnimBlender_DeleteHandler(struct QTask_s *ptQTask)
{
  --*(int *)&ptQTask[1].ptNext[9].tQTaskRefList.ptTail;
}

// source: e/3/animblender.c:164  [anchor-mhash]
void __cdecl AnimBlender_InterpolateHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { float vParam; };
    struct { char igi2_o1[4]; struct real32x3_t tSource0Translation; };
    struct { char igi2_o2[16]; struct Quat32_t *v33; };
    struct { char igi2_o3[20]; struct QTask_s *ptNext; };
    struct { char igi2_o4[24]; struct real32x3_t tSource1Translation; };
    struct { char igi2_o5[36]; struct Quat32_t *v36; };
    struct { char igi2_o6[40]; int nBones; };
    struct { char igi2_o7[44]; char aisAnimated[256]; };
    struct { char igi2_o8[300]; struct Bone_s AnimBlender_atSource0Buffer[256]; };
    struct { char igi2_o9[20780]; struct Bone_s AnimBlender_atSource1Buffer[256]; };
    char igi2_extent[41260];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct real32x3_t *ptHead; // eax
  int v2; // ebx
  int v3; // ecx
  int v4; // eax
  struct QTask_s *ptPrev; // ecx
  struct QTask_s *v6; // ecx
  double v7; // st7
  int v8; // eax
  void (__cdecl *v9)(struct QTask_s *); // edx
  void (__cdecl *v10)(_DWORD); // eax
  struct QTask_s *ptTail; // eax
  int v12; // ebx
  struct Quat32_t *p_ptTail; // eax
  struct Quat32_t *p_tOrientation; // esi
  struct Quat32_t *v15; // edx
  struct QTask_s *ptParent; // edi
  struct QReference_s *ptMiddle; // esi
  int v18; // edx
  int v19; // eax
  bool v20; // cl
  struct QTask_s *v21; // esi
  int v22; // edx
  void (__cdecl *pfHandler)(struct QTask_s *); // ecx
  struct QReference_s *v24; // esi
  int v25; // eax
  int v26; // edi
  bool v27; // cl
  int v28; // eax
  int v29; // esi
  void (__cdecl *v30)(_DWORD); // ecx

  ptHead = (struct real32x3_t *)ptQTask[1].tQTaskRefList.ptHead;
  v2 = *(_DWORD *)&ptQTask[1].eQTaskType;
  igi2_frame.tSource0Translation = *ptHead;
  igi2_frame.tSource1Translation = *ptHead;
  if ( (*(_BYTE *)(v2 + 44) & 0x10) != 0 )
  {
    v3 = 0;
    if ( (int)ptQTask[1].tQTaskRefList.ptMiddle > 0 )
    {
      v4 = 0;
      do
      {
        if ( *((_BYTE *)&ptQTask[1].tQTaskChildren.ptHead->ptNext + v3) )
        {
          ptQTask[1].tQTaskChildren.ptTail[v4 + 1].tQTaskChildren.ptTail = nullptr;
          ptQTask[1].tQTaskChildren.ptTail[v4 + 1].tQTaskRefList.ptHead = nullptr;
          ptQTask[1].tQTaskChildren.ptTail[v4 + 1].tQTaskRefList.ptMiddle = nullptr;
          ptQTask[1].tQTaskChildren.ptTail[v4 + 1].tQTaskRefList.ptTail = (struct QReference_s *)1065353216;
          ptQTask[1].tQTaskChildren.ptTail[v4 + 1].ptParent = nullptr;
        }
        ++v3;
        v4 += 2;
      }
      while ( v3 < (int)ptQTask[1].tQTaskRefList.ptMiddle );
    }
  }
  else
  {
    ptPrev = ptQTask[2].ptPrev;
    igi2_frame.ptNext = ptQTask[2].ptNext;
    igi2_frame.v33 = (struct Quat32_t *)ptPrev;
    if ( (int)igi2_frame.ptNext >= (int)ptPrev || (v6 = ptQTask[1].ptParent, ((int)v6[1].ptPrev & 0x10) != 0) )
    {
      ptParent = ptQTask[1].ptParent;
      if ( ptParent[1].tQTaskChildren.ptHead == *(struct QTask_s **)(v2 + 48) )
        goto LABEL_51;
      if ( ((int)ptParent[1].ptPrev & 0x10) != 0 )
        goto LABEL_51;
      ptMiddle = ptQTask[1].tQTaskRefList.ptMiddle;
      v18 = 0;
      v19 = 0;
      if ( (int)ptMiddle <= 0 )
        goto LABEL_51;
      do
      {
        v20 = *((_BYTE *)&ptParent[1].tQTaskChildren.ptHead->ptNext + v19)
           && !*(_BYTE *)(v19 + *(_DWORD *)(v2 + 48))
           && *((_BYTE *)&ptQTask[1].tQTaskChildren.ptHead->ptNext + v19);
        igi2_frame.aisAnimated[v19] = v20;
        if ( v18 || v20 )
          v18 = 1;
        ++v19;
      }
      while ( v19 < (int)ptMiddle );
      if ( !v18 )
      {
LABEL_51:
        v22 = BoneDynCubeObj_eInterpolateQTaskEvent;
      }
      else
      {
        v21 = ptParent[1].tQTaskChildren.ptHead;
        ptParent[1].tQTaskChildren.ptHead = (struct QTask_s *)igi2_frame.aisAnimated;
        ptQTask[1].ptParent[1].tQTaskChildren.ptTail = ptQTask[1].tQTaskChildren.ptTail;
        ptQTask[1].ptParent[1].tQTaskRefList.ptHead = (struct QReference_s *)&igi2_frame.tSource0Translation;
        v22 = BoneDynCubeObj_eInterpolateQTaskEvent;
        pfHandler = (void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[BoneDynCubeObj_eInterpolateQTaskEvent][ptQTask[1].ptParent->eQTaskType].pfHandler;
        if ( pfHandler )
        {
          pfHandler(ptQTask[1].ptParent);
          v22 = BoneDynCubeObj_eInterpolateQTaskEvent;
        }
        ptQTask[1].ptParent[1].tQTaskChildren.ptHead = v21;
      }
      v24 = ptQTask[1].tQTaskRefList.ptMiddle;
      v25 = 0;
      if ( (int)v24 > 0 )
      {
        v26 = *(_DWORD *)&ptQTask[1].eQTaskType;
        do
        {
          v27 = *(_BYTE *)(v25 + *(_DWORD *)(v26 + 48)) && *((_BYTE *)&ptQTask[1].tQTaskChildren.ptHead->ptNext + v25);
          igi2_frame.aisAnimated[v25++] = v27;
        }
        while ( v25 < (int)v24 );
      }
      v28 = *(_DWORD *)&ptQTask[1].eQTaskType;
      v29 = *(_DWORD *)(v28 + 48);
      *(_DWORD *)(v28 + 48) = igi2_frame.aisAnimated;
      *(_DWORD *)(*(_DWORD *)&ptQTask[1].eQTaskType + 56) = ptQTask[1].tQTaskChildren.ptTail;
      *(_DWORD *)(*(_DWORD *)&ptQTask[1].eQTaskType + 60) = &igi2_frame.tSource1Translation;
      v30 = (void (__cdecl *)(_DWORD))QTask_aatQTaskFinalEvent[v22][*(unsigned __int16 *)(*(_DWORD *)&ptQTask[1].eQTaskType
                                                                                        + 36)].pfHandler;
      if ( v30 )
        v30(*(_DWORD *)&ptQTask[1].eQTaskType);
      *(_DWORD *)(*(_DWORD *)&ptQTask[1].eQTaskType + 48) = v29;
      if ( ptQTask[1].tQTaskChildren.ptHead->ptNext )
      {
        if ( **(_BYTE **)(*(_DWORD *)&ptQTask[1].eQTaskType + 48) )
          *(struct real32x3_t *)ptQTask[1].tQTaskRefList.ptHead = igi2_frame.tSource1Translation;
        else
          *(struct real32x3_t *)ptQTask[1].tQTaskRefList.ptHead = igi2_frame.tSource0Translation;
      }
    }
    else
    {
      v7 = (double)(int)igi2_frame.ptNext / (double)(int)igi2_frame.v33;
      if ( v7 >= 0.0 )
      {
        if ( v7 <= 1.0 )
          igi2_frame.vParam = v7;
        else
          igi2_frame.vParam = 1.0;
      }
      else
      {
        igi2_frame.vParam = 0.0;
      }
      v6[1].tQTaskChildren.ptTail = (struct QTask_s *)igi2_frame.AnimBlender_atSource0Buffer;
      *(_DWORD *)(*(_DWORD *)&ptQTask[1].eQTaskType + 56) = igi2_frame.AnimBlender_atSource1Buffer;
      ptQTask[1].ptParent[1].tQTaskRefList.ptHead = (struct QReference_s *)&igi2_frame.tSource0Translation;
      *(_DWORD *)(*(_DWORD *)&ptQTask[1].eQTaskType + 60) = &igi2_frame.tSource1Translation;
      v8 = BoneDynCubeObj_eInterpolateQTaskEvent;
      v9 = (void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[BoneDynCubeObj_eInterpolateQTaskEvent][ptQTask[1].ptParent->eQTaskType].pfHandler;
      if ( v9 )
      {
        v9(ptQTask[1].ptParent);
        v8 = BoneDynCubeObj_eInterpolateQTaskEvent;
      }
      v10 = (void (__cdecl *)(_DWORD))QTask_aatQTaskFinalEvent[v8][*(unsigned __int16 *)(*(_DWORD *)&ptQTask[1].eQTaskType
                                                                                       + 36)].pfHandler;
      if ( v10 )
        v10(*(_DWORD *)&ptQTask[1].eQTaskType);
      if ( ptQTask[1].tQTaskChildren.ptHead->ptNext )
      {
        if ( ptQTask[1].ptParent[1].tQTaskChildren.ptHead->ptNext )
        {
          if ( **(_BYTE **)(*(_DWORD *)&ptQTask[1].eQTaskType + 48) )
          {
            *(float *)&ptQTask[1].tQTaskRefList.ptHead->ptNext = (igi2_frame.tSource1Translation.vX - igi2_frame.tSource0Translation.vX)
                                                               * igi2_frame.vParam
                                                               + igi2_frame.tSource0Translation.vX;
            *(float *)&ptQTask[1].tQTaskRefList.ptHead->ptPrev = (igi2_frame.tSource1Translation.vY - igi2_frame.tSource0Translation.vY)
                                                               * igi2_frame.vParam
                                                               + igi2_frame.tSource0Translation.vY;
            *(float *)&ptQTask[1].tQTaskRefList.ptHead->pxObject = (igi2_frame.tSource1Translation.vZ - igi2_frame.tSource0Translation.vZ)
                                                                 * igi2_frame.vParam
                                                                 + igi2_frame.tSource0Translation.vZ;
          }
          else
          {
            *(struct real32x3_t *)ptQTask[1].tQTaskRefList.ptHead = igi2_frame.tSource0Translation;
          }
        }
        else
        {
          *(struct real32x3_t *)ptQTask[1].tQTaskRefList.ptHead = igi2_frame.tSource1Translation;
        }
      }
      ptTail = ptQTask[1].tQTaskChildren.ptTail;
      v12 = 0;
      igi2_frame.nBones = (int)ptQTask[1].tQTaskRefList.ptMiddle;
      if ( igi2_frame.nBones > 0 )
      {
        p_ptTail = (struct Quat32_t *)&ptTail[1].tQTaskChildren.ptTail;
        p_tOrientation = &igi2_frame.AnimBlender_atSource0Buffer[0].tOrientation;
        v15 = &igi2_frame.AnimBlender_atSource1Buffer[0].tOrientation;
        igi2_frame.ptNext = (struct QTask_s *)p_ptTail;
        igi2_frame.v33 = &igi2_frame.AnimBlender_atSource0Buffer[0].tOrientation;
        igi2_frame.v36 = &igi2_frame.AnimBlender_atSource1Buffer[0].tOrientation;
        do
        {
          if ( *((_BYTE *)&ptQTask[1].tQTaskChildren.ptHead->ptNext + v12) )
          {
            if ( *(_BYTE *)(v12 + *(_DWORD *)(*(_DWORD *)&ptQTask[1].eQTaskType + 48)) )
            {
              if ( *((_BYTE *)&ptQTask[1].ptParent[1].tQTaskChildren.ptHead->ptNext + v12) )
              {
                Quat32_SLERP(p_ptTail, p_tOrientation, v15, igi2_frame.vParam);
                v15 = igi2_frame.v36;
                p_ptTail = (struct Quat32_t *)igi2_frame.ptNext;
              }
              else
              {
                qmemcpy(p_ptTail, v15, sizeof(struct Quat32_t));
              }
            }
            else
            {
              qmemcpy(p_ptTail, p_tOrientation, sizeof(struct Quat32_t));
            }
          }
          v15 += 4;
          p_tOrientation = igi2_frame.v33 + 4;
          p_ptTail += 4;
          ++v12;
          igi2_frame.v36 = v15;
          igi2_frame.v33 += 4;
          igi2_frame.ptNext = (struct QTask_s *)p_ptTail;
        }
        while ( v12 < igi2_frame.nBones );
      }
    }
  }
}

// source: e/3/animblender.c:334  [anchor-mhash]
void __cdecl AnimBlender_UpdateAttachmentHandler(struct QTask_s *ptQTask)
{
  int v1; // eax
  void (__cdecl *pfHandler)(int); // ecx
  struct QTask_s *ptHead; // ecx
  int v4; // edx
  struct QTask_s *v5; // eax
  int v6; // esi
  void (__cdecl *v7)(struct QTask_s *); // eax
  int v8; // edx

  if ( ((int)ptQTask[1].ptPrev & 1) != 0 )
  {
    v1 = *(_DWORD *)&ptQTask[1].eQTaskType;
    pfHandler = (void (__cdecl *)(int))QTask_aatQTaskFinalEvent[Attach_eUpdateAttachmentEvent][*(unsigned __int16 *)(v1 + 36)].pfHandler;
    if ( pfHandler )
      pfHandler(v1);
  }
  else
  {
    ptHead = ptQTask->tQTaskChildren.ptHead;
    if ( ptHead->ptNext && ptHead )
    {
      v4 = QTask_nProtectedQTaskStackOffset;
      do
      {
        if ( ptHead->ptNext )
          v5 = ptHead->ptNext->ptNext != nullptr ? ptHead->ptNext : nullptr;
        else
          v5 = nullptr;
        v6 = Attach_eUpdateAttachmentEvent;
        QTask_atProtectedQTaskStack[v4].ptQTask = v5;
        v7 = (void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[v6][ptHead->eQTaskType].pfHandler;
        v8 = v4 + 1;
        QTask_nProtectedQTaskStackOffset = v8;
        if ( v7 )
        {
          v7(ptHead);
          v8 = QTask_nProtectedQTaskStackOffset;
        }
        ptHead = (struct QTask_s *)dword_849C7DC[v8];
        v4 = v8 - 1;
        QTask_nProtectedQTaskStackOffset = v4;
      }
      while ( ptHead );
    }
  }
}

// source: e/3/animblender.c:361  [size]
void __cdecl AnimBlender_MagicObjEnterEventHandler(struct QTask_s *ptQTask, void *pxContext)
{
  void (__cdecl *pfHandler)(_DWORD, ...); // ecx

  pfHandler = (void (__cdecl *)(_DWORD, ...))QTask_aatQTaskFinalEvent[MagicObj_eMagicObjEnterEvent][*(unsigned __int16 *)(*(_DWORD *)&ptQTask[1].eQTaskType + 36)].pfHandler;
  if ( pfHandler )
    pfHandler(*(_DWORD *)&ptQTask[1].eQTaskType);
}

// source: e/3/animblender.c:378  [size]
void __cdecl AnimBlender_RemoveHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *ptHead; // eax
  int v3; // edx
  struct QTask_s *v4; // ecx
  void (__cdecl *pfHandler)(struct QTask_s *, void *); // ecx
  int v6; // edx

  ptQTask[2].tQTaskChildren.ptMiddle = nullptr;
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
      pfHandler = (void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[DynCubeObj_eDynCubeObjRemoveQTaskEvent][ptHead->eQTaskType].pfHandler;
      v6 = v3 + 1;
      QTask_nProtectedQTaskStackOffset = v6;
      if ( pfHandler )
      {
        pfHandler(ptHead, pxContext);
        v6 = QTask_nProtectedQTaskStackOffset;
      }
      ptHead = (struct QTask_s *)dword_849C7DC[v6];
      v3 = v6 - 1;
      QTask_nProtectedQTaskStackOffset = v3;
    }
    while ( ptHead );
  }
}

// source: e/3/animblender.c:397  [anchor-mhash]
void __cdecl AnimBlender_RegisterHandler(struct QTask_s *ptQTask, void *pxContext)
{
  int v2; // edx
  int v3; // eax
  void (__cdecl *pfHandler)(int, ...); // ecx

  v2 = DynCubeObj_eDynCubeObjRegisterQTaskEvent;
  ptQTask[2].tQTaskChildren.ptMiddle = (struct QTask_s *)1;
  v3 = *(_DWORD *)&ptQTask[1].eQTaskType;
  pfHandler = (void (__cdecl *)(int, ...))QTask_aatQTaskFinalEvent[v2][*(unsigned __int16 *)(v3 + 36)].pfHandler;
  if ( pfHandler )
    pfHandler(v3, pxContext);
}

// source: e/3/animblender.c:420  [size]
struct AnimBlender_t *__cdecl AnimBlender_SetClearWhenFinished(
        struct AnimBlender_t *ptAnimBlender,
        int isClearWhenFinished)
{
  bool v2; // zf
  int nFlags; // ecx

  v2 = isClearWhenFinished == 0;
  nFlags = ptAnimBlender->tBase.nFlags;
  if ( v2 )
    ptAnimBlender->tBase.nFlags = nFlags & 0xFFFFFFFE;
  else
    ptAnimBlender->tBase.nFlags = nFlags | 1;
  return ptAnimBlender;
}

// source: e/3/animblender.c:444  [size]
char *__cdecl AnimBlender_SetAnimated(
        struct AnimBlender_t *ptAnimBlender,
        char *aisAnimated)
{
  ptAnimBlender->tBase.pisAnimated = aisAnimated;
  return aisAnimated;
}

// source: e/3/animblender.c:459  [anchor-callee]
void __cdecl AnimBlender_Blend(
        struct AnimBlender_t *ptAnimBlender,
        struct AnimControllerBase_t *ptSource0,
        struct AnimControllerBase_t *ptSource1,
        int nTransitionTime)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct DynCubeObjRemoveObjContext_s tRemoveContext; };
    struct { char igi2_o1[4]; struct DynCubeObjRegisterObjContext_s tRegisterContext; };
    char igi2_extent[16];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  unsigned int v4; // eax
  int v5; // eax
  void (__cdecl *pfHandler)(struct AnimControllerBase_t *, struct DynCubeObjRemoveObjContext_s *); // eax
  void (__cdecl *v7)(struct AnimControllerBase_t *, struct DynCubeObjRegisterObjContext_s *); // eax

  ptAnimBlender->nTimeStep = AnimBlender_nTicksPerFrame;
  v4 = ptAnimBlender->tBase.nFlags & 0xFFFFFFFB;
  ptAnimBlender->ptSource0 = ptSource0;
  ptAnimBlender->ptSource1 = ptSource1;
  ptAnimBlender->nTime = 0;
  ptAnimBlender->nTotalTime = nTransitionTime;
  ptAnimBlender->tBase.nFlags = v4;
  if ( !nTransitionTime )
  {
    v5 = v4 | 4;
    ptAnimBlender->tBase.nFlags = v5;
    if ( (v5 & 1) != 0 )
    {
      if ( ptSource0 )
      {
        ptSource0->nFlags |= 0x10u;
        ptSource0[1].tQTask.tQTaskChildren.ptHead = nullptr;
        QTask_DeleteChildren(&ptSource0->tQTask);
      }
    }
  }
  pfHandler = (void (__cdecl *)(struct AnimControllerBase_t *, struct DynCubeObjRemoveObjContext_s *))QTask_aatQTaskFinalEvent[DynCubeObj_eDynCubeObjRemoveQTaskEvent][ptSource0->tQTask.eQTaskType].pfHandler;
  igi2_frame.tRemoveContext.ptWorld = World_ptActiveWorld;
  if ( pfHandler )
    pfHandler(ptSource0, &igi2_frame.tRemoveContext);
  if ( ptAnimBlender->isRegistered )
  {
    v7 = (void (__cdecl *)(struct AnimControllerBase_t *, struct DynCubeObjRegisterObjContext_s *))QTask_aatQTaskFinalEvent[DynCubeObj_eDynCubeObjRegisterQTaskEvent][ptSource1->tQTask.eQTaskType].pfHandler;
    igi2_frame.tRegisterContext.ptWorld = World_ptActiveWorld;
    igi2_frame.tRegisterContext.eDynCubeObjRegisterMethod = DYNCUBEOBJREGISTERMETHOD_RADIUS;
    igi2_frame.tRegisterContext.eDynCubeTreeCategory = 2;
    if ( v7 )
      v7(ptSource1, &igi2_frame.tRegisterContext);
  }
}

// source: e/3/animblender.c:520  [anchor-callee]
struct AnimBlender_t *__cdecl AnimBlender_New(
        struct QTask_s *ptParent,
        struct AnimControllerBase_t *ptSource0,
        struct AnimControllerBase_t *ptSource1)
{
  struct AnimBlender_t *v3; // esi
  struct AnimBlender_CreateContext_t tCreateContext; // [esp+Ch] [ebp-10h] BYREF

  tCreateContext.ptSource0 = ptSource0;
  tCreateContext.ptSource1 = ptSource1;
  tCreateContext.ptBoneDynCubeObj = (struct BoneDynCubeObj_s *)ptParent;
  tCreateContext.nTransitionTime = 0;
  v3 = (struct AnimBlender_t *)QTask_NewFn(ptParent, AnimBlender_eQTaskType, &tCreateContext);
  QTask_ChangeParent(&ptSource0->tQTask, &v3->tBase.tQTask);
  QTask_ChangeParent(&ptSource1->tQTask, &v3->tBase.tQTask);
  return v3;
}

// source: e/3/animblender.c:552  [anchor-hash]
void __cdecl AnimBlender_Open()
{
  unsigned __int16 BaseQTaskType; // ax
  unsigned __int16 v1; // si

  BaseQTaskType = QTask_GetBaseQTaskType();
  v1 = QTask_NewQTaskType("AnimBlender", 96, BaseQTaskType, 0, 0);
  AnimBlender_eQTaskType = v1;
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 1, AnimBlender_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 2, (void (__cdecl *)(struct QTask_s *))AnimBlender_DeleteHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, BoneDynCubeObj_eInterpolateQTaskEvent, AnimBlender_InterpolateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, Attach_eUpdateAttachmentEvent, AnimBlender_UpdateAttachmentHandler);
  QTask_LinkQTaskEventHandlerFn(v1, 0, AnimBlender_CreateHandler);
  QTask_LinkQTaskEventHandlerFn(v1, MagicObj_eMagicObjEnterEvent, AnimBlender_MagicObjEnterEventHandler);
  QTask_LinkQTaskEventHandlerFn(v1, DynCubeObj_eDynCubeObjRemoveQTaskEvent, AnimBlender_RemoveHandler);
  QTask_LinkQTaskEventHandlerFn(v1, DynCubeObj_eDynCubeObjRegisterQTaskEvent, AnimBlender_RegisterHandler);
  memset(AnimBlender_aisAnimated, 1u, sizeof(AnimBlender_aisAnimated));
}

// source: e/3/animblender.c:586  [size]
void __cdecl AnimBlender_Close()
{
  QTask_DeleteQTaskType(AnimBlender_eQTaskType);
}
