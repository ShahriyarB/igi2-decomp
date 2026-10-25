/* j/0/vehicles/deathzone.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/vehicles/deathzone.c:42  [anchor-mhash]
void __cdecl DeathZone_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ((void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[0][RigidMagicObj_eQTaskType].pfHandler)(
    ptQTask,
    pxContext);
  ptQTask[8].tQTaskChildren.ptHead = nullptr;
  ptQTask[8].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[8].tQTaskChildren.ptTail = nullptr;
}

// source: j/0/vehicles/deathzone.c:74  [size]
void __cdecl DeathZone_DeleteHandler(struct QTask_s *ptQTask)
{
  World_RemoveDynCubeObj((struct World_s *)ptQTask[2].ptParent, (struct DynCubeObj_s *)ptQTask);
}

// source: j/0/vehicles/deathzone.c:94  [anchor-mhash]
void __cdecl DeathZone_RunHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct QTask_s *v12; };
    struct { char igi2_o1[4]; char *p_tCMVel; };
    char igi2_extent[8];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct PhysicsObj_s *ptNext; // esi
  unsigned __int16 eQTaskType; // dx
  struct QTaskList_s *v3; // eax
  int v4; // esi
  int v5; // edi
  struct QTaskList_s *v6; // eax
  int v7; // esi
  int v8; // edi
  struct QTaskList_s *v9; // eax
  int v10; // esi
  int v11; // edi

  if ( Game_eGameMode != GAME_GAMEMODE_MULTIPLAYER )
  {
    ptNext = (struct PhysicsObj_s *)ptQTask[8].ptNext;
    if ( ptNext )
    {
      eQTaskType = ptNext->tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask.eQTaskType;
      if ( QTask_IsQTaskTypeDerived(eQTaskType, Vehicle_eQTaskType) )
      {
        if ( eQTaskType == Train_eQTaskType )
        {
          if ( ptNext->tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask.ptParent->eQTaskType == Train_eQTaskType )
            ptNext = (struct PhysicsObj_s *)ptNext->tRigidDynCubeObj.tModelObj.tDynCubeObj.tQObj.tQTask.ptParent;
          if ( ptNext->tPhysics.tCMVel.vX != 0.0 )
          {
            v3 = Human_ptQTaskList;
            igi2_frame.v12 = ptQTask;
            igi2_frame.p_tCMVel = (char *)&ptNext->tPhysics.tCMVel;
            v4 = 0;
            if ( Human_ptQTaskList->nTask > 0 )
            {
              v5 = 8;
              do
              {
                ((void (__cdecl *)(_DWORD, struct QTask_s **))QTask_aatQTaskFinalEvent[DeathZone_eDeathZoneHitTestEvent][*(unsigned __int16 *)(*(int *)((char *)&v3->nTask + v5) + 36)].pfHandler)(
                  *(int *)((char *)&v3->nTask + v5),
                  &igi2_frame.v12);
                v3 = Human_ptQTaskList;
                ++v4;
                v5 += 4;
              }
              while ( v4 < Human_ptQTaskList->nTask );
            }
          }
        }
        else if ( !PhysicsObj_IsIdle(ptNext) )
        {
          v6 = Human_ptQTaskList;
          igi2_frame.p_tCMVel = (char *)&ptNext->tPhysics.tCMVel;
          igi2_frame.v12 = ptQTask;
          v7 = 0;
          if ( Human_ptQTaskList->nTask > 0 )
          {
            v8 = 8;
            do
            {
              ((void (__cdecl *)(_DWORD, struct QTask_s **))QTask_aatQTaskFinalEvent[DeathZone_eDeathZoneHitTestEvent][*(unsigned __int16 *)(*(int *)((char *)&v6->nTask + v8) + 36)].pfHandler)(
                *(int *)((char *)&v6->nTask + v8),
                &igi2_frame.v12);
              v6 = Human_ptQTaskList;
              ++v7;
              v8 += 4;
            }
            while ( v7 < Human_ptQTaskList->nTask );
          }
        }
      }
      else if ( QTask_IsQTaskTypeDerived(eQTaskType, ModelObj_eQTaskType) )
      {
        if ( sqrt(
               *(float *)&ptQTask[8].tQTaskChildren.ptHead * *(float *)&ptQTask[8].tQTaskChildren.ptHead
             + *(float *)&ptQTask[8].tQTaskChildren.ptMiddle * *(float *)&ptQTask[8].tQTaskChildren.ptMiddle
             + *(float *)&ptQTask[8].tQTaskChildren.ptTail * *(float *)&ptQTask[8].tQTaskChildren.ptTail) > 0.0 )
        {
          v9 = Human_ptQTaskList;
          igi2_frame.v12 = ptQTask;
          igi2_frame.p_tCMVel = (char *)&ptQTask[8].tQTaskChildren;
          v10 = 0;
          if ( Human_ptQTaskList->nTask > 0 )
          {
            v11 = 8;
            do
            {
              ((void (__cdecl *)(_DWORD, struct QTask_s **))QTask_aatQTaskFinalEvent[DeathZone_eDeathZoneHitTestEvent][*(unsigned __int16 *)(*(int *)((char *)&v9->nTask + v11) + 36)].pfHandler)(
                *(int *)((char *)&v9->nTask + v11),
                &igi2_frame.v12);
              v9 = Human_ptQTaskList;
              ++v10;
              v11 += 4;
            }
            while ( v10 < Human_ptQTaskList->nTask );
          }
        }
      }
    }
    ptQTask[8].tQTaskChildren.ptHead = nullptr;
    ptQTask[8].tQTaskChildren.ptMiddle = nullptr;
    ptQTask[8].tQTaskChildren.ptTail = nullptr;
  }
}

// source: j/0/vehicles/deathzone.c:180  [size]
void __cdecl DeathZone_UpdateMagicObjHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { float ptDynCubeObj; };
    struct { char igi2_o1[20]; struct real64x3_t tNewPos; };
    struct { char igi2_o2[44]; _BYTE Real64x3_Rotate_tTemp[40]; };
    char igi2_extent[88];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  double v2; // st7
  float *v3; // eax
  double v4; // st6
  double v5; // st5
  double v6; // st4
  double v7; // st3
  double *v8; // eax
  double v9; // st7
  double v10; // st7
  int *v11; // eax
  int v12; // eax
  double v13; // st6
  int v14; // eax
  int v15; // edx
  double v16; // st7
  double v17; // st6

  if ( QTask_IsQTaskTypeDerived(ptQTask[8].ptNext->eQTaskType, Vehicle_eQTaskType) )
  {
    v2 = *(float *)&ptQTask[5].ptPrev;
    v3 = *((float **)pxContext + 1);
    v4 = *(float *)&ptQTask[5].tQTaskChildren.ptHead;
    v5 = *(float *)&ptQTask[5].tQTaskChildren.ptMiddle;
    *(double *)igi2_frame.Real64x3_Rotate_tTemp = v3[2] * v5 + v3[1] * v4 + *v3 * v2;
    *(double *)&igi2_frame.Real64x3_Rotate_tTemp[8] = v3[5] * v5 + v3[4] * v4 + v3[3] * v2;
    v6 = v3[8] * v5 + v3[7] * v4;
    v7 = v3[6];
    v8 = *(double **)pxContext;
    *(double *)&igi2_frame.Real64x3_Rotate_tTemp[16] = v6 + v7 * v2;
    qmemcpy(&igi2_frame.tNewPos, igi2_frame.Real64x3_Rotate_tTemp, sizeof(igi2_frame.tNewPos));
    igi2_frame.tNewPos.vX = *(double *)igi2_frame.Real64x3_Rotate_tTemp + *v8;
    igi2_frame.tNewPos.vY = igi2_frame.tNewPos.vY + v8[1];
    igi2_frame.tNewPos.vZ = igi2_frame.tNewPos.vZ + v8[2];
    if ( *(float *)&ptQTask[6].tQTaskChildren.ptHead <= (double)*(float *)&ptQTask[6].tQTaskChildren.ptMiddle )
      v9 = *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
    else
      v9 = *(float *)&ptQTask[6].tQTaskChildren.ptHead;
    if ( v9 >= *(float *)&ptQTask[6].ptPrev )
    {
      if ( *(float *)&ptQTask[6].tQTaskChildren.ptHead <= (double)*(float *)&ptQTask[6].tQTaskChildren.ptMiddle )
        v10 = *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
      else
        v10 = *(float *)&ptQTask[6].tQTaskChildren.ptHead;
    }
    else
    {
      v10 = *(float *)&ptQTask[6].ptPrev;
    }
    v11 = *(int **)&ptQTask[2].eQTaskType;
    if ( v11 && (v12 = *v11) != 0 )
      v13 = *(float *)(*(_DWORD *)(*(_DWORD *)(v12 + 12) + 12) + 120);
    else
      v13 = 1.0;
    igi2_frame.ptDynCubeObj = v13 * v10;
    World_MoveDynCubeObjRadius(Game_ptGame->ptWorld, (struct DynCubeObj_s *)ptQTask, &igi2_frame.tNewPos, igi2_frame.ptDynCubeObj);
    v14 = *((_DWORD *)pxContext + 1);
    *(float *)igi2_frame.Real64x3_Rotate_tTemp = *(float *)(v14 + 4) * *(float *)&ptQTask[4].tQTaskChildren.ptTail
                                    + *(float *)&ptQTask[4].tQTaskRefList.ptTail * *(float *)(v14 + 8)
                                    + *(float *)&ptQTask[4].ptPrev * *(float *)v14;
    *(float *)&igi2_frame.Real64x3_Rotate_tTemp[4] = *(float *)(v14 + 4) * *(float *)&ptQTask[4].tQTaskRefList.ptHead
                                        + *(float *)&ptQTask[4].ptParent * *(float *)(v14 + 8)
                                        + *(float *)&ptQTask[4].tQTaskChildren.ptHead * *(float *)v14;
    *(float *)&igi2_frame.Real64x3_Rotate_tTemp[8] = *(float *)(v14 + 4) * *(float *)&ptQTask[4].tQTaskRefList.ptMiddle
                                        + *(float *)&ptQTask[4].eQTaskType * *(float *)(v14 + 8)
                                        + *(float *)&ptQTask[4].tQTaskChildren.ptMiddle * *(float *)v14;
    *(float *)&igi2_frame.Real64x3_Rotate_tTemp[12] = *(float *)&ptQTask[4].tQTaskRefList.ptTail * *(float *)(v14 + 20)
                                         + *(float *)&ptQTask[4].ptPrev * *(float *)(v14 + 12)
                                         + *(float *)&ptQTask[4].tQTaskChildren.ptTail * *(float *)(v14 + 16);
    *(float *)&igi2_frame.Real64x3_Rotate_tTemp[16] = *(float *)&ptQTask[4].ptParent * *(float *)(v14 + 20)
                                         + *(float *)&ptQTask[4].tQTaskChildren.ptHead * *(float *)(v14 + 12)
                                         + *(float *)&ptQTask[4].tQTaskRefList.ptHead * *(float *)(v14 + 16);
    *(float *)&igi2_frame.Real64x3_Rotate_tTemp[20] = *(float *)&ptQTask[4].eQTaskType * *(float *)(v14 + 20)
                                         + *(float *)&ptQTask[4].tQTaskChildren.ptMiddle * *(float *)(v14 + 12)
                                         + *(float *)&ptQTask[4].tQTaskRefList.ptMiddle * *(float *)(v14 + 16);
    *(float *)&igi2_frame.Real64x3_Rotate_tTemp[24] = *(float *)&ptQTask[4].tQTaskRefList.ptTail * *(float *)(v14 + 32)
                                         + *(float *)&ptQTask[4].ptPrev * *(float *)(v14 + 24)
                                         + *(float *)&ptQTask[4].tQTaskChildren.ptTail * *(float *)(v14 + 28);
    v15 = *(_DWORD *)(v14 + 36);
    *(float *)&igi2_frame.Real64x3_Rotate_tTemp[28] = *(float *)&ptQTask[4].ptParent * *(float *)(v14 + 32)
                                         + *(float *)&ptQTask[4].tQTaskChildren.ptHead * *(float *)(v14 + 24)
                                         + *(float *)&ptQTask[4].tQTaskRefList.ptHead * *(float *)(v14 + 28);
    v16 = *(float *)&ptQTask[4].eQTaskType * *(float *)(v14 + 32)
        + *(float *)&ptQTask[4].tQTaskChildren.ptMiddle * *(float *)(v14 + 24);
    v17 = *(float *)&ptQTask[4].tQTaskRefList.ptMiddle * *(float *)(v14 + 28);
    *(_DWORD *)&igi2_frame.Real64x3_Rotate_tTemp[36] = (char *)&ptQTask[5].ptNext->ptNext + v15 + 1;
    *(float *)&igi2_frame.Real64x3_Rotate_tTemp[32] = v16 + v17;
    qmemcpy(&ptQTask[3].ptPrev, igi2_frame.Real64x3_Rotate_tTemp, sizeof(struct QTask_s));
  }
}

// source: j/0/vehicles/deathzone.c:237  [size]
void __cdecl DeathZone_AILineOfSightHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_BYTE *)pxContext = 0;
}

// source: j/0/vehicles/deathzone.c:255  [anchor-mhash]
void __cdecl DeathZone_UpdateAttachmentHandler(struct QTask_s *ptQTask)
{
  double v1; // st7
  double v2; // st6
  struct real64x3_t tReal64x3; // [esp+10h] [ebp-18h] BYREF

  qmemcpy(&tReal64x3, &ptQTask[1], sizeof(tReal64x3));
  QTask_TriggerBaseHandlerNoContext(ptQTask, ptQTask->eQTaskType, Attach_eUpdateAttachmentEvent);
  v1 = *(double *)&ptQTask[1].ptNext - tReal64x3.vX;
  v2 = *(double *)&ptQTask[1].tQTaskChildren.ptHead - tReal64x3.vY;
  *(float *)&tReal64x3.vY = *(double *)&ptQTask[1].tQTaskChildren.ptTail - tReal64x3.vZ;
  *(float *)&ptQTask[8].tQTaskChildren.ptHead = v1 + *(float *)&ptQTask[8].tQTaskChildren.ptHead;
  *(float *)&ptQTask[8].tQTaskChildren.ptMiddle = v2 + *(float *)&ptQTask[8].tQTaskChildren.ptMiddle;
  *(float *)&ptQTask[8].tQTaskChildren.ptTail = *(float *)&tReal64x3.vY + *(float *)&ptQTask[8].tQTaskChildren.ptTail;
}

// source: j/0/vehicles/deathzone.c:285  [anchor-strings]
void __cdecl DeathZone_Open()
{
  unsigned __int16 v0; // si
  _DWORD *v1; // esi

  v0 = QTask_NewQTaskType(&g_zMessage_0.zTalkString[96], 344, RigidMagicObj_eQTaskType, 0, 0);
  DeathZone_eQTaskType = v0;
  QTask_LinkQTaskEventHandlerFn(v0, 0, DeathZone_CreateHandler);
  QTask_LinkQTaskEventHandlerFn(v0, MagicObj_eUpdateMagicObjEvent, DeathZone_UpdateMagicObjHandler);
  QTask_LinkQTaskEventHandlerFn(v0, GameFunctions_eWeaponHitQTaskEvent, nullptr);
  QTask_LinkQTaskEventHandlerFn(v0, GameFunctions_eExplosionHitQTaskEvent, nullptr);
  QTask_LinkQTaskEventHandlerFn(v0, QCube_eGetClosestVertexQTaskEvent, nullptr);
  QTask_LinkQTaskEventHandlerFn(v0, 10, nullptr);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    AIDetection_eLineOfSightQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))DeathZone_AILineOfSightHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 1, DeathZone_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 2, DeathZone_DeleteHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, Attach_eUpdateAttachmentEvent, DeathZone_UpdateAttachmentHandler);
  Symbol_Register(
    &g_zMessage_0.zTalkString[76],
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)v0,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  v1 = Mem_AllocFn(18444, 4);
  v1[1] = 0;
  *v1 = 0;
  v1[4610] = &g_zMessage_0.zTalkString[76];
  Wildcard_CreateNFA(&g_zMessage_0.zTalkString[76], v1 + 2, (char *)v1 + 10248);
  List_AddTail(v1, (int)&MagicObjConfig_tTaskTypeEnumList);
  DeathZone_eDeathZoneHitTestEvent = QTask_NewQTaskEventFn(0, &g_zMessage_0.zTalkString[52]);
}

// source: j/0/vehicles/deathzone.c:328  [size]
void __cdecl DeathZone_Close()
{
  QTask_DeleteQTaskType(DeathZone_eQTaskType);
  QTask_DeleteQTaskEvent(DeathZone_eDeathZoneHitTestEvent);
}

// source: j/0/vehicles/deathzone.c:345  [size]
unsigned __int16 __cdecl DeathZone_GetQTaskType()
{
  return DeathZone_eQTaskType;
}

// source: j/0/vehicles/deathzone.c:358  [size]
__int16 __cdecl DeathZone_GetDeathZoneHitTestEvent()
{
  return DeathZone_eDeathZoneHitTestEvent;
}
