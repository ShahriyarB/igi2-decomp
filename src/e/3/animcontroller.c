/* e/3/animcontroller.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: e/3/animcontroller.c:55  [anchor-callee]
void __cdecl AnimController_TriggerEvents(
        struct AnimController_t *ptAnimController,
        struct AnimEvent_s *ptEvent,
        struct AnimEvent_s *ptLast)
{
  #pragma pack(push, 1)
  union
  {
    struct { float v7; };
    struct { char igi2_o1[4]; struct QTask_s ptCreator; };
    struct { char igi2_o2[44]; float v9; };
    struct { char igi2_o3[48]; float v10; };
    struct { char igi2_o4[52]; float v11; };
    struct { char igi2_o5[56]; float v12; };
    struct { char igi2_o6[60]; float v13; };
    char igi2_extent[68];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct AnimEvent_s *v3; // ebp
  int v4; // ebx
  struct real32x3_t *ptBoneDynCubeObj; // eax
  double v6; // rt0
  struct AnimEvent_s *ptEventa = *(struct AnimEvent_s * *)&ptEvent; // [esp+68h] [ebp+8h] ARGSLOT

  v3 = ptEvent;
  if ( ptEvent != ptLast )
  {
    while ( 1 )
    {
      if ( v3->nType != 6 )
      {
        if ( v3->nType == 0xFF )
          return;
        goto LABEL_10;
      }
      v4 = *(_DWORD *)&v3[1].nType;
      ptBoneDynCubeObj = (struct real32x3_t *)ptAnimController->tBase.ptBoneDynCubeObj;
      ptEventa = (struct AnimEvent_s *)ptBoneDynCubeObj;
      if ( v4 == -1 )
        break;
      if ( ptAnimController->tBase.pisAnimated[v4] )
      {
        BoneDynCubeObj_GetBonePosition((struct BoneDynCubeObj_s *)&igi2_frame.ptCreator, ptBoneDynCubeObj, v4);
        BoneDynCubeObj_GetBoneWorldPositionFromName(
          (struct BoneDynCubeObj_s *)ptEventa,
          *(_DWORD *)&v3[1].nType,
          (float *)&igi2_frame.ptCreator.tQTaskRefList.ptMiddle);
        ptBoneDynCubeObj = (struct real32x3_t *)ptEventa;
        igi2_frame.v7 = igi2_frame.v13 * *(float *)&v3[2].nTime + igi2_frame.v11 * *(float *)&v3[1].ptNext + igi2_frame.v12 * *(float *)&v3[2].nType;
        v6 = igi2_frame.v10 * *(float *)&v3[2].nTime
           + *(float *)&igi2_frame.ptCreator.eQTaskType * *(float *)&v3[1].ptNext
           + igi2_frame.v9 * *(float *)&v3[2].nType;
        *(double *)&igi2_frame.ptCreator.ptNext = *(float *)&igi2_frame.ptCreator.ptParent * *(float *)&v3[2].nTime
                                     + *(float *)&igi2_frame.ptCreator.tQTaskRefList.ptMiddle * *(float *)&v3[1].ptNext
                                     + *(float *)&igi2_frame.ptCreator.tQTaskRefList.ptTail * *(float *)&v3[2].nType
                                     + *(double *)&igi2_frame.ptCreator.ptNext;
        *(double *)&igi2_frame.ptCreator.tQTaskChildren.ptHead = v6 + *(double *)&igi2_frame.ptCreator.tQTaskChildren.ptHead;
        *(double *)&igi2_frame.ptCreator.tQTaskChildren.ptTail = igi2_frame.v7 + *(double *)&igi2_frame.ptCreator.tQTaskChildren.ptTail;
LABEL_9:
        AnimTrigger_Trigger(SLOWORD(v3[1].nTime), (struct QTask_s *)ptBoneDynCubeObj, (struct real64x3_t *)&igi2_frame.ptCreator);
      }
LABEL_10:
      v3 = (struct AnimEvent_s *)((char *)v3 + 4 * v3->nLen);
      if ( v3 == ptLast )
        return;
    }
    qmemcpy(&igi2_frame.ptCreator, &ptBoneDynCubeObj[3].vY, 0x18u);
    goto LABEL_9;
  }
}

// source: e/3/animcontroller.c:128  [anchor-callee]
void __cdecl AnimController_CreateAttachObjects(struct AnimController_t *ptAnimController)
{
  struct BoneDynCubeObj_s *ptBoneDynCubeObj; // ebx
  int v2; // ebp
  struct Anim_AttachObject_t *ptFirstAttachObject; // esi
  int nBone; // eax
  struct Anim_AttachObject_t *v5; // esi
  enum bool v6; // eax
  struct QTask_s *AttachObject; // edx
  int nAttachObjects; // [esp+10h] [ebp-4h]

  ptBoneDynCubeObj = ptAnimController->tBase.ptBoneDynCubeObj;
  if ( ptBoneDynCubeObj->tModelObj.ptLODVirModel && ptAnimController->ptAnim->nAttachObjects > 0 )
  {
    v2 = 0;
    nAttachObjects = ptAnimController->ptAnim->nAttachObjects;
    do
    {
      ptFirstAttachObject = ptAnimController->ptAnim->ptFirstAttachObject;
      nBone = ptFirstAttachObject[v2].tAttachInfo.nBone;
      v5 = &ptFirstAttachObject[v2];
      if ( nBone == -1 || ptAnimController->tBase.pisAnimated[nBone] )
      {
        v6 = ptAnimController->isRegistered && SLOBYTE(ptAnimController->tBase.nFlags) >= 0;
        AttachObject = ModelObj_CreateAttachObject(
                         &ptBoneDynCubeObj->tModelObj,
                         &ptAnimController->tBase.tQTask,
                         &ptAnimController->tBase.tQTask,
                         &v5->tAttachInfo,
                         true,
                         v6);
        if ( QTask_IsQTaskTypeDerived(AttachObject->eQTaskType, ModelObj_eQTaskType) )
          AttachObject[6].ptNext = (struct QTask_s *)v5->ptFirstKey;
      }
      ++v2;
      --nAttachObjects;
    }
    while ( nAttachObjects );
  }
}

// source: e/3/animcontroller.c:196  [anchor-callee]
struct ModelObj_s *__cdecl AnimController_GetAttachObject(
        struct AnimController_t *ptAnimController,
        int nID)
{
  struct ModelObj_s *ptNext; // edx
  int v3; // esi
  unsigned __int16 v4; // cx
  int v5; // eax

  ptNext = ptAnimController->tBase.tQTask.tQTaskChildren.ptHead->ptNext != nullptr
         ? (struct ModelObj_s *)ptAnimController->tBase.tQTask.tQTaskChildren.ptHead
         : nullptr;
  v3 = 0;
  if ( !ptNext )
    return nullptr;
  v4 = ModelObj_eQTaskType;
  while ( 1 )
  {
    while ( QTask_IsQTaskTypeDerived(ptNext->tDynCubeObj.tQObj.tQTask.eQTaskType, v4) == false )
      ;
    v5 = v3++;
    if ( v5 == nID )
      break;
    ptNext = (struct ModelObj_s *)ptNext->tDynCubeObj.tQObj.tQTask.ptNext;
    if ( !ptNext || !ptNext->tDynCubeObj.tQObj.tQTask.ptNext )
      return nullptr;
  }
  return ptNext;
}

// source: e/3/animcontroller.c:231  [anchor-callee]
void __cdecl AnimController_Seek(struct AnimController_t *ptAnimController, int nTime)
{
  struct AnimHeader_s *ptAnim; // eax
  struct AnimEvent_s *ptFirstEvent; // ebx
  int i; // esi
  struct QTask_s *AttachObject; // eax
  int v6; // edx
  struct AnimEvent_s *ptNext; // ecx
  int v8; // edx
  struct AnimEvent_s *v9; // ecx
  struct AnimEvent_s *v10; // edx
  int v11; // ecx
  int v12; // edx
  int v13; // ecx
  int v14; // edx
  _DWORD v15[10]; // [esp+4h] [ebp-28h] BYREF

  ptAnim = ptAnimController->ptAnim;
  if ( ptAnim )
  {
    ptFirstEvent = ptAnim->ptFirstEvent;
    for ( i = nTime;
          ptFirstEvent->nTime < i;
          ptFirstEvent = (struct AnimEvent_s *)((char *)ptFirstEvent + 4 * ptFirstEvent->nLen) )
    {
      if ( ptFirstEvent->nType == 255 )
        break;
      switch ( ptFirstEvent->nType )
      {
        case 0u:
        case 2u:
        case 5u:
        case 6u:
        case 7u:
          continue;
        case 1u:
          AttachObject = (struct QTask_s *)AnimController_GetAttachObject(ptAnimController, ptFirstEvent->nArg);
          if ( AttachObject )
          {
            AttachObject[5].tQTaskRefList.ptHead = *(struct QReference_s **)&ptFirstEvent[1].nType;
            AttachObject[5].ptPrev = (struct QTask_s *)ptFirstEvent[4].ptNext;
            AttachObject[5].tQTaskChildren.ptHead = *(struct QTask_s **)&ptFirstEvent[5].nType;
            AttachObject[5].tQTaskChildren.ptMiddle = (struct QTask_s *)ptFirstEvent[5].nTime;
            v6 = ptFirstEvent[1].nTime;
            v15[1] = ptFirstEvent[2].nTime;
            ptNext = ptFirstEvent[1].ptNext;
            v15[0] = v6;
            v8 = ptFirstEvent[3].nTime;
            v15[3] = ptNext;
            v9 = ptFirstEvent[3].ptNext;
            v15[2] = v8;
            v10 = ptFirstEvent[2].ptNext;
            v15[5] = v9;
            v11 = *(_DWORD *)&ptFirstEvent[3].nType;
            v15[4] = v10;
            v12 = *(_DWORD *)&ptFirstEvent[2].nType;
            v15[7] = v11;
            v13 = ptFirstEvent[4].nTime;
            v15[6] = v12;
            v14 = *(_DWORD *)&ptFirstEvent[4].nType;
            v15[9] = v13;
            v15[8] = v14;
            qmemcpy(&AttachObject[4].ptPrev, v15, sizeof(struct QTask_s));
            QTask_TriggerQTaskEventParent(AttachObject, Attach_eAttachEvent, &AttachObject[5].tQTaskChildren.ptTail);
            i = nTime;
          }
          break;
        case 3u:
          ptAnimController->ptActiveTranslationKey = (struct AnimEvent_TranslationKey_t *)ptFirstEvent;
          break;
        case 4u:
          ptAnimController->pptActiveRotationKeys[ptFirstEvent->nArg] = (struct AnimEvent_RotationKey_t *)ptFirstEvent;
          break;
        default:
          LDebug_Error("Unknown animation event encountered");
          abort();
      }
    }
    ptAnimController->nTime = i - 1;
    ptAnimController->ptNextEvent = ptFirstEvent;
  }
}

// source: e/3/animcontroller.c:323  [anchor-mhash]
void __cdecl AnimController_RunHandler(struct QTask_s *ptQTask)
{
  if ( ((int)ptQTask[1].ptPrev & 2) != 0 )
    AnimController_Step(
      (struct AnimController_t *)ptQTask,
      (int)ptQTask[1].tQTaskRefList.ptMiddle + (unsigned int)ptQTask[1].tQTaskRefList.ptTail);
}

// source: e/3/animcontroller.c:346  [anchor-mhash]
void __cdecl AnimController_InterpolateHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { float ptDest; };
    struct { float ptDesta; };
    struct { char igi2_o2[20]; int i; };
    struct { char igi2_o3[24]; int v23; };
    struct { char igi2_o4[28]; struct Quat32_t *v24; };
    struct { char igi2_o5[32]; struct Quat32_t tTangent; };
    char igi2_extent[52];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *v2; // edi
  struct QTask_s *ptPrev; // eax
  struct QTask_s *ptHead; // ecx
  double v5; // st7
  int v6; // ebx
  int v7; // eax
  struct Quat32_t *v8; // edi
  int v9; // ecx
  int v10; // edx
  int v11; // eax
  int v12; // edi
  int v13; // ebx
  struct Quat32_t *v14; // eax
  struct QTask_s *v15; // esi
  bool v16; // zf
  int v17; // edi
  int v18; // edx
  void (__cdecl *pfHandler)(struct QTask_s *); // eax
  struct QTask_s *ptQTaska = *(struct QTask_s * *)&ptQTask; // [esp+38h] [ebp+4h] ARGSLOT
  float ptQTaskb = *(float *)&ptQTask; // [esp+38h] [ebp+4h] ARGSLOT

  v2 = nullptr;
  if ( ptQTask[1].ptParent )
  {
    ptPrev = ptQTask[2].ptPrev;
    if ( ((int)ptQTask[1].ptPrev & 0x40) != 0 )
    {
      ptQTask[1].tQTaskRefList.ptHead->ptNext = nullptr;
      ptQTask[1].tQTaskRefList.ptHead->ptPrev = nullptr;
      ptQTask[1].tQTaskRefList.ptHead->pxObject = nullptr;
    }
    else
    {
      ptHead = ptPrev->tQTaskChildren.ptHead;
      if ( ptHead )
      {
        v5 = (double)((char *)ptQTask[1].tQTaskRefList.ptMiddle - (char *)ptPrev->ptPrev)
           / (double)((char *)ptHead->ptPrev - (char *)ptPrev->ptPrev);
        *(float *)&ptQTask[1].tQTaskRefList.ptHead->ptNext = (*(float *)&ptHead->tQTaskChildren.ptMiddle
                                                            - *(float *)&ptPrev->tQTaskChildren.ptMiddle)
                                                           * v5
                                                           + *(float *)&ptPrev->tQTaskChildren.ptMiddle;
        *(float *)&ptQTask[1].tQTaskRefList.ptHead->ptPrev = (*(float *)&ptHead->tQTaskChildren.ptTail
                                                            - *(float *)&ptPrev->tQTaskChildren.ptTail)
                                                           * v5
                                                           + *(float *)&ptPrev->tQTaskChildren.ptTail;
        *(float *)&ptQTask[1].tQTaskRefList.ptHead->pxObject = (*(float *)&ptHead->tQTaskRefList.ptHead
                                                              - *(float *)&ptPrev->tQTaskRefList.ptHead)
                                                             * v5
                                                             + *(float *)&ptPrev->tQTaskRefList.ptHead;
      }
      else
      {
        *ptQTask[1].tQTaskRefList.ptHead = *(struct QReference_s *)&ptPrev->tQTaskChildren.ptMiddle;
      }
    }
    if ( ptQTask[1].tQTaskChildren.ptTail )
    {
      if ( ((int)ptQTask[1].ptPrev & 8) != 0 )
      {
        v10 = 0;
        igi2_frame.i = 0;
        if ( (int)ptQTask[1].ptParent->tQTaskRefList.ptHead > 0 )
        {
          v11 = 0;
          igi2_frame.v23 = 0;
          do
          {
            if ( *((_BYTE *)&ptQTask[1].tQTaskChildren.ptHead->ptNext + v10) )
            {
              v12 = *((_DWORD *)&ptQTask[2].ptNext->ptNext + v10);
              v13 = *(_DWORD *)(v12 + 8);
              v14 = (struct Quat32_t *)((char *)&ptQTask[1].tQTaskChildren.ptTail[1].tQTaskChildren.ptTail + v11);
              igi2_frame.v24 = v14;
              if ( v13 )
              {
                ptQTaskb = (double)((unsigned int)ptQTask[1].tQTaskRefList.ptMiddle - *(_DWORD *)(v12 + 4))
                         / (double)(*(_DWORD *)(v13 + 4) - *(_DWORD *)(v12 + 4));
                Quat32_SLERP(v14, (struct Quat32_t *)(v12 + 12), (struct Quat32_t *)(v13 + 12), ptQTaskb);
                Quat32_SLERP(&igi2_frame.tTangent, (struct Quat32_t *)(v12 + 52), (struct Quat32_t *)(v13 + 32), ptQTaskb);
                igi2_frame.ptDesta = (1.0 - ptQTaskb) * ptQTaskb + (1.0 - ptQTaskb) * ptQTaskb;
                Quat32_SLERP(igi2_frame.v24, igi2_frame.v24, &igi2_frame.tTangent, igi2_frame.ptDesta);
                v10 = igi2_frame.i;
              }
              else
              {
                qmemcpy(v14, (void *)(v12 + 12), sizeof(struct Quat32_t));
              }
            }
            ++v10;
            v11 = igi2_frame.v23 + 80;
            igi2_frame.i = v10;
            igi2_frame.v23 += 80;
          }
          while ( v10 < (int)ptQTask[1].ptParent->tQTaskRefList.ptHead );
        }
      }
      else
      {
        v6 = 0;
        if ( (int)ptQTask[1].ptParent->tQTaskRefList.ptHead > 0 )
        {
          ptQTaska = nullptr;
          do
          {
            if ( *((_BYTE *)&ptQTask[1].tQTaskChildren.ptHead->ptNext + v6) )
            {
              v7 = *((_DWORD *)&ptQTask[2].ptNext->ptNext + v6);
              v8 = (struct Quat32_t *)((char *)&v2[1].tQTaskChildren.ptTail
                                     + (unsigned int)ptQTask[1].tQTaskChildren.ptTail);
              v9 = *(_DWORD *)(v7 + 8);
              if ( v9 )
              {
                igi2_frame.ptDest = (double)((unsigned int)ptQTask[1].tQTaskRefList.ptMiddle - *(_DWORD *)(v7 + 4))
                       / (double)(*(_DWORD *)(v9 + 4) - *(_DWORD *)(v7 + 4));
                Quat32_SLERP(v8, (struct Quat32_t *)(v7 + 12), (struct Quat32_t *)(v9 + 12), igi2_frame.ptDest);
              }
              else
              {
                qmemcpy(v8, (void *)(v7 + 12), sizeof(struct Quat32_t));
              }
            }
            ++v6;
            v2 = ptQTaska + 2;
            ptQTaska += 2;
          }
          while ( v6 < (int)ptQTask[1].ptParent->tQTaskRefList.ptHead );
        }
      }
      v15 = ptQTask->tQTaskChildren.ptHead;
      v16 = v15->ptNext == nullptr;
      AnimController_nTime = (int)ptQTask[1].tQTaskRefList.ptMiddle;
      if ( !v16 && v15 )
      {
        v17 = 0;
        do
        {
          v18 = *(_DWORD *)&ptQTask[1].ptParent[1].ptNext[v17 + 1].eQTaskType;
          v17 += 2;
          if ( v18 )
          {
            pfHandler = (void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[BoneDynCubeObj_eInterpolateQTaskEvent][v15->eQTaskType].pfHandler;
            if ( pfHandler )
              pfHandler(v15);
          }
          v15 = v15->ptNext;
        }
        while ( v15 && v15->ptNext );
      }
    }
  }
}

// source: e/3/animcontroller.c:495  [anchor-mhash]
void __cdecl AnimController_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  unsigned __int8 *v2; // edi
  int v3; // eax
  int v4; // edx
  int v5; // ecx
  int v6; // ecx
  unsigned int v7; // ebx
  struct QTask_s *v8; // eax
  struct QTask_s *v9; // eax

  v2 = *((unsigned __int8 **)pxContext + 1);
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
  v7 = 4 * v4;
  v8 = (struct QTask_s *)Mem_AllocFn(4 * v4, 4);
  ptQTask[2].ptNext = v8;
  memset(v8, 0, v7);
  ptQTask[1].ptPrev = (struct QTask_s *)2;
  ptQTask[1].tQTaskChildren.ptTail = nullptr;
  ptQTask[1].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[2].ptPrev = nullptr;
  ptQTask[1].tQTaskChildren.ptHead = (struct QTask_s *)AnimController_aisAnimated;
  ptQTask[1].ptNext = *(struct QTask_s **)pxContext;
  ptQTask[1].tQTaskChildren.ptMiddle = (struct QTask_s *)(*(_DWORD *)pxContext + 288);
  ptQTask[1].tQTaskChildren.ptTail = *(struct QTask_s **)(*(_DWORD *)pxContext + 316);
  ptQTask[1].tQTaskRefList.ptHead = (struct QReference_s *)(*(_DWORD *)pxContext + 296);
  ptQTask[2].tQTaskChildren.ptHead = (struct QTask_s *)1;
  ++*(_DWORD *)(*(_DWORD *)pxContext + 388);
  v9 = (struct QTask_s *)((int)ptQTask[1].ptPrev | 0x10);
  ptQTask[1].ptParent = nullptr;
  ptQTask[1].ptPrev = v9;
  QTask_DeleteChildren(ptQTask);
}

// source: e/3/animcontroller.c:545  [anchor-mhash]
void __cdecl AnimController_DeleteHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *v1; // edi
  struct QTask_s *ptNext; // eax
  int v3; // ebx

  v1 = (struct QTask_s *)((int)ptQTask[1].ptPrev | 0x10);
  ptQTask[1].ptParent = nullptr;
  ptQTask[1].ptPrev = v1;
  QTask_DeleteChildren(ptQTask);
  --*(int *)&ptQTask[1].ptNext[9].tQTaskRefList.ptTail;
  ptNext = ptQTask[2].ptNext;
  if ( ptNext )
  {
    v3 = *(_DWORD *)((unsigned int)&ptNext[-1].eQTaskType & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v3);
    memset(*(void **)(v3 + 8), 0xCDu, *(_DWORD *)(v3 + 16));
    free((void *)v3);
  }
  ptQTask[2].ptNext = nullptr;
}

// source: e/3/animcontroller.c:571  [size]
void __cdecl AnimController_UpdateAttachmentHandler(struct QTask_s *ptQTask)
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

// source: e/3/animcontroller.c:587  [size]
void __cdecl AnimController_MagicObjEnterEventHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *ptHead; // eax
  int v3; // edx
  struct QTask_s *v4; // ecx
  void (__cdecl *pfHandler)(struct QTask_s *, void *); // ecx
  int v6; // edx

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
      pfHandler = (void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[MagicObj_eMagicObjEnterEvent][ptHead->eQTaskType].pfHandler;
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

// source: e/3/animcontroller.c:601  [size]
void __cdecl AnimController_RemoveHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *ptHead; // eax
  int v3; // edx
  struct QTask_s *v4; // ecx
  void (__cdecl *pfHandler)(struct QTask_s *, void *); // ecx
  int v6; // edx

  ptQTask[2].tQTaskChildren.ptHead = nullptr;
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

// source: e/3/animcontroller.c:620  [size]
void __cdecl AnimController_RegisterHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *ptHead; // eax
  int v3; // edx
  struct QTask_s *v4; // ecx
  void (__cdecl *pfHandler)(struct QTask_s *, void *); // ecx
  int v6; // edx

  ptQTask[2].tQTaskChildren.ptHead = (struct QTask_s *)1;
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
      pfHandler = (void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[DynCubeObj_eDynCubeObjRegisterQTaskEvent][ptHead->eQTaskType].pfHandler;
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

// source: e/3/animcontroller.c:643  [anchor-hash]
void __cdecl AnimController_Open()
{
  unsigned __int16 BaseQTaskType; // ax
  unsigned __int16 v1; // si

  memset(AnimController_aisAnimated, 1u, sizeof(AnimController_aisAnimated));
  BaseQTaskType = QTask_GetBaseQTaskType();
  v1 = QTask_NewQTaskType("AnimController", 92, BaseQTaskType, 0, 0);
  AnimController_eQTaskType = v1;
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 1, AnimController_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 2, AnimController_DeleteHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, Attach_eUpdateAttachmentEvent, AnimController_UpdateAttachmentHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, BoneDynCubeObj_eInterpolateQTaskEvent, AnimController_InterpolateHandler);
  QTask_LinkQTaskEventHandlerFn(v1, 0, AnimController_CreateHandler);
  QTask_LinkQTaskEventHandlerFn(v1, MagicObj_eMagicObjEnterEvent, AnimController_MagicObjEnterEventHandler);
  QTask_LinkQTaskEventHandlerFn(v1, DynCubeObj_eDynCubeObjRemoveQTaskEvent, AnimController_RemoveHandler);
  QTask_LinkQTaskEventHandlerFn(v1, DynCubeObj_eDynCubeObjRegisterQTaskEvent, AnimController_RegisterHandler);
}

// source: e/3/animcontroller.c:677  [size]
void __cdecl AnimController_Close()
{
  QTask_DeleteQTaskType(AnimController_eQTaskType);
}

// source: e/3/animcontroller.c:694  [anchor-mhash]
struct AnimController_t *__cdecl AnimController_New(
        struct QTask_s *ptParent,
        unsigned __int8 *ptHierarchy)
{
  struct AnimController_CreateContext_t tCreateContext; // [esp+4h] [ebp-8h] BYREF

  tCreateContext.ptHierarchy = ptHierarchy;
  tCreateContext.ptBoneDynCubeObj = (struct BoneDynCubeObj_s *)ptParent;
  return (struct AnimController_t *)QTask_NewFn(ptParent, AnimController_eQTaskType, &tCreateContext);
}

// source: e/3/animcontroller.c:722  [size]
void __cdecl AnimController_SetFPS(int nFPS)
{
  AnimController_nTicksPerFrame = 4800 / nFPS;
}

// source: e/3/animcontroller.c:737  [size]
char *__cdecl AnimController_SetAnimated(
        struct AnimController_t *ptAnimController,
        char *aisAnimated)
{
  ptAnimController->tBase.pisAnimated = aisAnimated;
  return aisAnimated;
}

// source: e/3/animcontroller.c:752  [anchor-hash]
struct AnimController_t *__cdecl AnimController_ClearAnimation(
        struct AnimController_t *ptAnimController)
{
  int v1; // ecx

  v1 = ptAnimController->tBase.nFlags | 0x10;
  ptAnimController->ptAnim = nullptr;
  ptAnimController->tBase.nFlags = v1;
  return (struct AnimController_t *)QTask_DeleteChildren(&ptAnimController->tBase.tQTask);
}

// source: e/3/animcontroller.c:774  [anchor-callee]
struct AnimHeader_s *__cdecl AnimController_SetAnimationAndTime(
        struct AnimController_t *ptAnimController,
        struct AnimHeader_s *ptAnim,
        int nTime)
{
  int v5; // ecx
  struct AnimHeader_s *result; // eax
  int nFlags; // eax
  int v8; // eax
  int v9; // eax
  int v10; // esi

  v5 = ptAnimController->tBase.nFlags | 0x10;
  ptAnimController->ptAnim = nullptr;
  ptAnimController->tBase.nFlags = v5;
  result = (struct AnimHeader_s *)QTask_DeleteChildren(&ptAnimController->tBase.tQTask);
  if ( ptAnim )
  {
    ptAnimController->ptAnim = ptAnim;
    nFlags = ptAnimController->tBase.nFlags;
    if ( ptAnim->isLoop )
      v8 = nFlags | 1;
    else
      v8 = nFlags & 0xFFFFFFFE;
    ptAnimController->tBase.nFlags = v8;
    ptAnimController->tBase.nFlags = v8 & 0xFFFFFFEF;
    v9 = AnimController_nTicksPerFrame;
    ptAnimController->nTime = -1;
    ptAnimController->nTimeStep = v9;
    ptAnimController->ptNextEvent = ptAnim->ptFirstEvent;
    ptAnimController->ptActiveTranslationKey = nullptr;
    AnimController_CreateAttachObjects(ptAnimController);
    v10 = nTime % (ptAnim->nTotalTime + 1);
    AnimController_Seek(ptAnimController, v10 - 1);
    AnimController_Step(ptAnimController, v10);
    result = (struct AnimHeader_s *)(ptAnimController->tBase.nFlags & 0xFFFFFFFB);
    ptAnimController->tBase.nFlags = (int)result;
  }
  return result;
}

// source: e/3/animcontroller.c:821  [size]
struct AnimController_t *__cdecl AnimController_SetLoop(
        struct AnimController_t *ptAnimController,
        int isLoop)
{
  bool v2; // zf
  int nFlags; // ecx

  v2 = isLoop == 0;
  nFlags = ptAnimController->tBase.nFlags;
  if ( v2 )
    ptAnimController->tBase.nFlags = nFlags & 0xFFFFFFFE;
  else
    ptAnimController->tBase.nFlags = nFlags | 1;
  return ptAnimController;
}

// source: e/3/animcontroller.c:845  [size]
struct AnimController_t *__cdecl AnimController_DisableAttachObjectRegistration(
        struct AnimController_t *ptAnimController,
        enum bool isDisable)
{
  bool v2; // zf
  int nFlags; // ecx

  v2 = isDisable == false;
  nFlags = ptAnimController->tBase.nFlags;
  if ( v2 )
    ptAnimController->tBase.nFlags = nFlags & 0xFFFFFF7F;
  else
    ptAnimController->tBase.nFlags = nFlags | 0x80;
  return ptAnimController;
}

// source: e/3/animcontroller.c:869  [size]
struct AnimController_t *__cdecl AnimController_SetSuppressTriggers(
        struct AnimController_t *ptAnimController,
        int isSuppressTriggers)
{
  bool v2; // zf
  int nFlags; // ecx

  v2 = isSuppressTriggers == 0;
  nFlags = ptAnimController->tBase.nFlags;
  if ( v2 )
    ptAnimController->tBase.nFlags = nFlags & 0xFFFFFFDF;
  else
    ptAnimController->tBase.nFlags = nFlags | 0x20;
  return ptAnimController;
}

// source: e/3/animcontroller.c:893  [size]
struct AnimController_t *__cdecl AnimController_SetSQUAD(
        struct AnimController_t *ptAnimController,
        int isSQUAD)
{
  bool v2; // zf
  int nFlags; // ecx

  v2 = isSQUAD == 0;
  nFlags = ptAnimController->tBase.nFlags;
  if ( v2 )
    ptAnimController->tBase.nFlags = nFlags & 0xFFFFFFF7;
  else
    ptAnimController->tBase.nFlags = nFlags | 8;
  return ptAnimController;
}

// source: e/3/animcontroller.c:917  [size]
struct AnimController_t *__cdecl AnimController_SetAutoStep(
        struct AnimController_t *ptAnimController,
        int isAutoStep)
{
  bool v2; // zf
  int nFlags; // ecx

  v2 = isAutoStep == 0;
  nFlags = ptAnimController->tBase.nFlags;
  if ( v2 )
    ptAnimController->tBase.nFlags = nFlags & 0xFFFFFFFD;
  else
    ptAnimController->tBase.nFlags = nFlags | 2;
  return ptAnimController;
}

// source: e/3/animcontroller.c:938  [size]
struct AnimController_t *__cdecl AnimController_SetIgnoreTranslation(
        struct AnimController_t *ptAnimController,
        int isIgnore)
{
  bool v2; // zf
  int nFlags; // ecx

  v2 = isIgnore == 0;
  nFlags = ptAnimController->tBase.nFlags;
  if ( v2 )
    ptAnimController->tBase.nFlags = nFlags & 0xFFFFFFBF;
  else
    ptAnimController->tBase.nFlags = nFlags | 0x40;
  return ptAnimController;
}

// source: e/3/animcontroller.c:965  [anchor-callee]
void __cdecl AnimController_Step(struct AnimController_t *ptAnimController, int nTime)
{
  #pragma pack(push, 1)
  union
  {
    struct { int v24; };
    struct { char igi2_o1[4]; struct AnimEvent_s *ptLast[2]; };
    struct { char igi2_o2[12]; struct AnimEvent_s *ptEvent[2]; };
    struct { char igi2_o3[20]; _DWORD v27[10]; };
    char igi2_extent[64];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct AnimHeader_s *ptAnim; // edi
  int v4; // esi
  char v5; // al
  int nTotalTime; // ebx
  char v7; // al
  int v8; // edx
  struct AnimEvent_s *ptNextEvent; // eax
  int v10; // eax
  struct AnimEvent_s *ptFirstEvent; // ebx
  int *pisTouched; // eax
  struct QTask_s *AttachObject; // eax
  int v14; // edx
  struct AnimEvent_s *ptNext; // ecx
  int v16; // edx
  struct AnimEvent_s *v17; // ecx
  struct AnimEvent_s *v18; // edx
  int v19; // ecx
  int v20; // edx
  int v21; // ecx
  int v22; // edx
  bool v23; // zf
  int ptAnimControllera = *(int *)&ptAnimController; // [esp+58h] [ebp+4h] ARGSLOT

  ptAnim = ptAnimController->ptAnim;
  ptAnimControllera = 0;
  if ( !ptAnim )
    return;
  v4 = nTime;
  if ( nTime >= 0 )
  {
    if ( nTime < ptAnim->nTotalTime )
      goto LABEL_11;
    v7 = LOBYTE(ptAnimController->tBase.nFlags) | 4;
    ptAnimController->tBase.nFlags |= 4u;
    if ( (v7 & 1) != 0 )
    {
      v8 = nTime % ptAnim->nTotalTime;
      ptNextEvent = ptAnimController->ptNextEvent;
      ptAnimController->nTime = -1;
      igi2_frame.ptEvent[0] = ptNextEvent;
      igi2_frame.ptLast[0] = nullptr;
      ptAnimControllera = 1;
      nTime = v8;
      ptAnimController->ptNextEvent = ptAnim->ptFirstEvent;
    }
    else
    {
      nTime = ptAnim->nTotalTime;
    }
  }
  else
  {
    v5 = LOBYTE(ptAnimController->tBase.nFlags) | 4;
    ptAnimController->tBase.nFlags |= 4u;
    if ( (v5 & 1) != 0 )
    {
      nTotalTime = ptAnim->nTotalTime;
      igi2_frame.ptEvent[0] = ptAnim->ptFirstEvent;
      ptAnimControllera = 1;
      nTime = nTotalTime + nTime % nTotalTime;
      igi2_frame.ptLast[0] = ptAnimController->ptNextEvent;
      ptAnimController->nTime = nTotalTime + 1;
      ptAnimController->ptNextEvent = nullptr;
    }
    else
    {
      nTime = 0;
    }
  }
  v4 = nTime;
LABEL_11:
  v10 = ptAnimController->nTime;
  if ( v4 != v10 )
  {
    if ( v4 >= v10 )
    {
      ptFirstEvent = ptAnimController->ptNextEvent;
      igi2_frame.ptEvent[ptAnimControllera] = ptFirstEvent;
      igi2_frame.v24 = 0;
    }
    else
    {
      ptFirstEvent = ptAnim->ptFirstEvent;
      igi2_frame.ptLast[ptAnimControllera] = ptAnimController->ptNextEvent;
      igi2_frame.v24 = 1;
    }
    pisTouched = ptAnimController->tBase.pisTouched;
    if ( pisTouched )
      *pisTouched = 1;
    for ( ; ptFirstEvent->nTime <= v4; ptFirstEvent = (struct AnimEvent_s *)((char *)ptFirstEvent
                                                                           + 4 * ptFirstEvent->nLen) )
    {
      if ( ptFirstEvent->nType == 255 )
        break;
      switch ( ptFirstEvent->nType )
      {
        case 0u:
        case 2u:
        case 5u:
        case 6u:
        case 7u:
          continue;
        case 1u:
          AttachObject = (struct QTask_s *)AnimController_GetAttachObject(ptAnimController, ptFirstEvent->nArg);
          if ( AttachObject )
          {
            AttachObject[5].tQTaskRefList.ptHead = *(struct QReference_s **)&ptFirstEvent[1].nType;
            AttachObject[5].ptPrev = (struct QTask_s *)ptFirstEvent[4].ptNext;
            AttachObject[5].tQTaskChildren.ptHead = *(struct QTask_s **)&ptFirstEvent[5].nType;
            AttachObject[5].tQTaskChildren.ptMiddle = (struct QTask_s *)ptFirstEvent[5].nTime;
            v14 = ptFirstEvent[1].nTime;
            igi2_frame.v27[1] = ptFirstEvent[2].nTime;
            ptNext = ptFirstEvent[1].ptNext;
            igi2_frame.v27[0] = v14;
            v16 = ptFirstEvent[3].nTime;
            igi2_frame.v27[3] = ptNext;
            v17 = ptFirstEvent[3].ptNext;
            igi2_frame.v27[2] = v16;
            v18 = ptFirstEvent[2].ptNext;
            igi2_frame.v27[5] = v17;
            v19 = *(_DWORD *)&ptFirstEvent[3].nType;
            igi2_frame.v27[4] = v18;
            v20 = *(_DWORD *)&ptFirstEvent[2].nType;
            igi2_frame.v27[7] = v19;
            v21 = ptFirstEvent[4].nTime;
            igi2_frame.v27[6] = v20;
            v22 = *(_DWORD *)&ptFirstEvent[4].nType;
            igi2_frame.v27[9] = v21;
            igi2_frame.v27[8] = v22;
            qmemcpy(&AttachObject[4].ptPrev, igi2_frame.v27, sizeof(struct QTask_s));
            QTask_TriggerQTaskEventParent(AttachObject, Attach_eAttachEvent, &AttachObject[5].tQTaskChildren.ptTail);
            v4 = nTime;
          }
          break;
        case 3u:
          ptAnimController->ptActiveTranslationKey = (struct AnimEvent_TranslationKey_t *)ptFirstEvent;
          break;
        case 4u:
          ptAnimController->pptActiveRotationKeys[ptFirstEvent->nArg] = (struct AnimEvent_RotationKey_t *)ptFirstEvent;
          break;
        default:
          LDebug_Error("Unknown animation event encountered");
          abort();
      }
    }
    v23 = (ptAnimController->tBase.nFlags & 0x20) == 0;
    ptAnimController->ptNextEvent = ptFirstEvent;
    ptAnimController->nTime = v4;
    if ( v23 )
    {
      if ( igi2_frame.v24 )
        igi2_frame.ptEvent[ptAnimControllera] = ptFirstEvent;
      else
        igi2_frame.ptLast[ptAnimControllera] = ptFirstEvent;
      AnimController_TriggerEvents(ptAnimController, igi2_frame.ptEvent[0], igi2_frame.ptLast[0]);
      if ( ptAnimControllera )
        AnimController_TriggerEvents(ptAnimController, igi2_frame.ptEvent[1], igi2_frame.ptLast[1]);
    }
  }
}

// source: e/3/animcontroller.c:1142  [anchor-mhash]
void __cdecl AnimController_StepParametric(struct AnimController_t *ptAnimController, float vParam)
{
  struct AnimHeader_s *ptAnim; // ecx

  ptAnim = ptAnimController->ptAnim;
  if ( ptAnim )
  {
    if ( vParam < 0.0 )
      vParam = 0.0;
    AnimController_Step(ptAnimController, (__int64)((double)ptAnim->nTotalTime * vParam));
  }
}

// source: e/3/animcontroller.c:1168  [size]
int __cdecl AnimController_GetFlags(struct AnimController_t *ptAnimController)
{
  return ptAnimController->tBase.nFlags;
}

// source: e/3/animcontroller.c:1183  [anchor-hash]
char *__cdecl AnimController_GetActiveAnimation(struct AnimController_t *ptAnimController)
{
  char *result; // eax

  result = (char *)ptAnimController->ptAnim;
  if ( result )
    result += 52;
  return result;
}

// source: e/3/animcontroller.c:1205  [size]
int __cdecl AnimController_GetAnimationTime(struct AnimController_t *ptAnimController)
{
  return ptAnimController->nTime;
}

// source: e/3/animcontroller.c:1220  [anchor-mhash]
void __cdecl AnimController_ScaleAnimationTimeStep(
        struct AnimController_t *ptAnimController,
        float vScale)
{
  ptAnimController->nTimeStep = (__int64)((double)AnimController_nTicksPerFrame * vScale);
}

// source: e/3/animcontroller.c:1235  [anchor-hash]
int __cdecl AnimController_GetAnimationTotalTime(
        struct AnimController_t *ptAnimController)
{
  struct AnimHeader_s *ptAnim; // eax

  ptAnim = ptAnimController->ptAnim;
  if ( ptAnim )
    return ptAnim->nTotalTime;
  else
    return 0;
}

// source: e/3/animcontroller.c:1257  [anchor-mhash]
float __cdecl AnimController_GetAnimationTimeFactor(
        struct AnimController_t *ptAnimController)
{
  struct AnimHeader_s *ptAnim; // eax

  ptAnim = ptAnimController->ptAnim;
  if ( ptAnim )
    return (double)ptAnimController->nTime / (double)ptAnim->nTotalTime;
  else
    return 0.0;
}
