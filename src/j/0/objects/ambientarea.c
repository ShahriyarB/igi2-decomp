/* j/0/objects/ambientarea.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/objects/ambientarea.c:107  [anchor-mhash]
void __cdecl AmbientArea_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  _BYTE *v2; // edx
  int v3; // esi

  ptQTask[1].tQTaskRefList.ptTail = (struct QReference_s *)1072693248;
  *(_DWORD *)&ptQTask[1].eQTaskType = 1072693248;
  ptQTask[2].ptPrev = (struct QTask_s *)1072693248;
  ptQTask[2].tQTaskChildren.ptHead = (struct QTask_s *)1065353216;
  ptQTask[2].tQTaskRefList.ptMiddle = (struct QReference_s *)1065353216;
  ptQTask[3].ptNext = (struct QTask_s *)1065353216;
  BYTE1(ptQTask[4].tQTaskRefList.ptMiddle) = 1;
  BYTE2(ptQTask[4].tQTaskRefList.ptMiddle) = 1;
  ptQTask[1].ptNext = nullptr;
  ptQTask[1].ptPrev = nullptr;
  ptQTask[1].tQTaskChildren.ptHead = nullptr;
  ptQTask[1].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[1].tQTaskChildren.ptTail = nullptr;
  ptQTask[1].tQTaskRefList.ptHead = nullptr;
  ptQTask[1].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[1].ptParent = nullptr;
  ptQTask[2].ptNext = nullptr;
  ptQTask[2].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[2].tQTaskChildren.ptTail = nullptr;
  ptQTask[2].tQTaskRefList.ptHead = nullptr;
  ptQTask[2].tQTaskRefList.ptTail = nullptr;
  ptQTask[2].ptParent = nullptr;
  *(_DWORD *)&ptQTask[2].eQTaskType = 0;
  ptQTask[3].ptPrev = nullptr;
  ptQTask[3].tQTaskChildren.ptHead = nullptr;
  ptQTask[3].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[3].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[3].tQTaskRefList.ptTail = nullptr;
  ptQTask[3].ptParent = nullptr;
  *(_DWORD *)&ptQTask[3].eQTaskType = 0;
  ptQTask[4].ptNext = nullptr;
  ptQTask[4].ptPrev = (struct QTask_s *)1076101120;
  ptQTask[4].tQTaskChildren.ptHead = (struct QTask_s *)1431655765;
  ptQTask[4].tQTaskChildren.ptMiddle = (struct QTask_s *)1071994197;
  ptQTask[4].tQTaskChildren.ptTail = nullptr;
  ptQTask[4].tQTaskRefList.ptHead = nullptr;
  LOBYTE(ptQTask[4].tQTaskRefList.ptMiddle) = 0;
  *(_DWORD *)&ptQTask[11].eQTaskType = 0;
  HIBYTE(ptQTask[4].tQTaskRefList.ptMiddle) = 0;
  v2 = (char *)&ptQTask[5].tQTaskChildren.ptTail + 3;
  v3 = 8;
  do
  {
    *v2 = 0;
    v2 += 32;
    --v3;
  }
  while ( v3 );
  ptQTask[12].ptNext = nullptr;
  ptQTask[12].ptPrev = nullptr;
  ptQTask[12].tQTaskChildren.ptHead = nullptr;
  ptQTask[12].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[14].ptNext = nullptr;
}

// source: j/0/objects/ambientarea.c:179  [anchor-caller]
void __cdecl AmbientArea_RunHandler(struct QTask_s *ptQTask)
{
  struct Game_s *v1; // ecx
  long double v2; // st7
  struct QReference_s *ptMicrophoneQTaskRef; // eax
  double *pxObject; // esi
  struct QTask_s *v5; // edi
  struct LevelExpression_s *p_ptPrev; // eax
  int v7; // ebp
  double v8; // st6
  double v9; // st6
  double v10; // st6
  long double v11; // st7
  char v12; // al
  double v13; // st7
  double v14; // st7
  struct QTask_s *ptNext; // eax
  struct QReference_s **v16; // esi
  struct QTask_s *ptHead; // eax
  unsigned int v18; // edx
  int v19; // eax
  int v20; // eax
  unsigned int v21; // ebp
  int v22; // ebp
  struct QTask_s *v23; // eax
  struct QTask_s *v24; // ebp
  int v25; // ecx
  struct QReference_s *v26; // eax
  double v27; // st7
  int v28; // eax
  unsigned int v29; // edx
  struct QReference_s *v30; // eax
  int v31; // ecx
  int v32; // edx
  struct QTask_s *v33; // eax
  void (__cdecl *pfHandler)(int); // eax
  int v35; // edx
  float vBaseVolume; // [esp+0h] [ebp-54h]
  float vBaseVolumea; // [esp+0h] [ebp-54h]
  __int64 v38; // [esp+14h] [ebp-40h]
  double tMicrophoneAbsPosa; // [esp+24h] [ebp-30h]
  double tMicrophoneAbsPos; // [esp+24h] [ebp-30h]
  double tMicrophoneAbsPos_8a; // [esp+2Ch] [ebp-28h]
  double tMicrophoneAbsPos_8; // [esp+2Ch] [ebp-28h]
  double tMicrophoneAbsPos_16a; // [esp+34h] [ebp-20h]
  double tMicrophoneAbsPos_16; // [esp+34h] [ebp-20h]
  double Real64x3_RotateInverse_tTemp_8; // [esp+44h] [ebp-10h]
  double Real64x3_RotateInverse_tTemp_16; // [esp+4Ch] [ebp-8h]

  v1 = Game_ptGame;
  v2 = 0.0;
  ptMicrophoneQTaskRef = Game_ptGame->ptMicrophoneQTaskRef;
  if ( ptMicrophoneQTaskRef )
    pxObject = (double *)ptMicrophoneQTaskRef->pxObject;
  else
    pxObject = nullptr;
  v5 = ptQTask;
  p_ptPrev = (struct LevelExpression_s *)&ptQTask[12].ptPrev;
  ptQTask[3].tQTaskChildren.ptTail = nullptr;
  v5[3].tQTaskRefList.ptHead = nullptr;
  v7 = 0;
  if ( p_ptPrev->zExpression && *p_ptPrev->zCompiledExpression && p_ptPrev->ptExpression )
  {
    v38 = (__int64)Level_RunLevelExpression(p_ptPrev, v5);
    v1 = Game_ptGame;
    if ( !(_BYTE)v38 )
      goto LABEL_33;
    v2 = 0.0;
  }
  tMicrophoneAbsPosa = pxObject[10] - *(double *)&v5[1].ptNext;
  tMicrophoneAbsPos_8a = pxObject[11] - *(double *)&v5[1].tQTaskChildren.ptHead;
  tMicrophoneAbsPos_16a = pxObject[12] - *(double *)&v5[1].tQTaskChildren.ptTail;
  v8 = *(float *)&v5[2].ptParent * tMicrophoneAbsPos_16a
     + *(float *)&v5[2].tQTaskRefList.ptHead * tMicrophoneAbsPos_8a
     + *(float *)&v5[2].tQTaskChildren.ptHead * tMicrophoneAbsPosa;
  Real64x3_RotateInverse_tTemp_8 = *(float *)&v5[2].eQTaskType * tMicrophoneAbsPos_16a
                                 + *(float *)&v5[2].tQTaskRefList.ptMiddle * tMicrophoneAbsPos_8a
                                 + *(float *)&v5[2].tQTaskChildren.ptMiddle * tMicrophoneAbsPosa;
  Real64x3_RotateInverse_tTemp_16 = *(float *)&v5[3].ptNext * tMicrophoneAbsPos_16a
                                  + *(float *)&v5[2].tQTaskRefList.ptTail * tMicrophoneAbsPos_8a
                                  + *(float *)&v5[2].tQTaskChildren.ptTail * tMicrophoneAbsPosa;
  if ( v8 < 0.0 )
    v8 = -v8;
  tMicrophoneAbsPos = v8 * 0.000244140625;
  v9 = Real64x3_RotateInverse_tTemp_8;
  if ( Real64x3_RotateInverse_tTemp_8 < 0.0 )
    v9 = -Real64x3_RotateInverse_tTemp_8;
  tMicrophoneAbsPos_8 = v9 * 0.000244140625;
  v10 = Real64x3_RotateInverse_tTemp_16;
  if ( Real64x3_RotateInverse_tTemp_16 < 0.0 )
    v10 = -Real64x3_RotateInverse_tTemp_16;
  tMicrophoneAbsPos_16 = v10 * 0.000244140625;
  if ( *(double *)&v5[1].tQTaskRefList.ptMiddle + *(double *)&v5[4].ptNext < tMicrophoneAbsPos
    || *(double *)&v5[4].ptNext + *(double *)&v5[1].ptParent < tMicrophoneAbsPos_8
    || *(double *)&v5[2].ptNext + *(double *)&v5[4].ptNext < tMicrophoneAbsPos_16 )
  {
    v5[3].tQTaskRefList.ptHead = nullptr;
    v7 = 0;
    goto LABEL_32;
  }
  v7 = 1;
  if ( tMicrophoneAbsPos <= *(double *)&v5[1].tQTaskRefList.ptMiddle
    && tMicrophoneAbsPos_8 <= *(double *)&v5[1].ptParent
    && tMicrophoneAbsPos_16 <= *(double *)&v5[2].ptNext )
  {
    v5[3].tQTaskRefList.ptHead = (struct QReference_s *)1072693248;
LABEL_32:
    v5[3].tQTaskChildren.ptTail = nullptr;
    goto LABEL_33;
  }
  if ( tMicrophoneAbsPos > *(double *)&v5[1].tQTaskRefList.ptMiddle )
    v2 = (tMicrophoneAbsPos - *(double *)&v5[1].tQTaskRefList.ptMiddle)
       * (tMicrophoneAbsPos - *(double *)&v5[1].tQTaskRefList.ptMiddle);
  if ( tMicrophoneAbsPos_8 > *(double *)&v5[1].ptParent )
    v2 = v2 + (tMicrophoneAbsPos_8 - *(double *)&v5[1].ptParent) * (tMicrophoneAbsPos_8 - *(double *)&v5[1].ptParent);
  if ( tMicrophoneAbsPos_16 > *(double *)&v5[2].ptNext )
    v2 = v2 + (tMicrophoneAbsPos_16 - *(double *)&v5[2].ptNext) * (tMicrophoneAbsPos_16 - *(double *)&v5[2].ptNext);
  v11 = 1.0 - sqrt(v2) / *(double *)&v5[4].ptNext;
  if ( v11 < 0.0 )
    v11 = 0.0;
  *(long double *)&v5[3].tQTaskChildren.ptTail = v11;
LABEL_33:
  if ( *((_DWORD *)pxObject + 33) )
    v12 = BYTE1(v5[4].tQTaskRefList.ptMiddle);
  else
    v12 = BYTE2(v5[4].tQTaskRefList.ptMiddle);
  if ( !v12 )
  {
    v7 = 0;
LABEL_37:
    v13 = *(double *)&v5[3].tQTaskChildren.ptHead
        - 1.0 / ((double)Flow_ptFlow->nFrequency * *(double *)&v5[4].tQTaskChildren.ptHead + 1.0);
    goto LABEL_38;
  }
  if ( !v7 )
    goto LABEL_37;
  v13 = 1.0 / ((double)Flow_ptFlow->nFrequency * *(double *)&v5[4].tQTaskChildren.ptHead + 1.0)
      + *(double *)&v5[3].tQTaskChildren.ptHead;
LABEL_38:
  *(double *)&v5[3].tQTaskChildren.ptHead = v13;
  if ( *(double *)&v5[3].tQTaskChildren.ptHead >= 0.0 )
  {
    if ( *(double *)&v5[3].tQTaskChildren.ptTail >= *(double *)&v5[3].tQTaskChildren.ptHead )
      v14 = *(double *)&v5[3].tQTaskChildren.ptHead;
    else
      v14 = *(double *)&v5[3].tQTaskChildren.ptTail;
  }
  else
  {
    v14 = 0.0;
  }
  *(double *)&v5[3].tQTaskChildren.ptHead = v14;
  if ( v14 == 0.0 )
  {
LABEL_56:
    v28 = (v1->tRunRandomState.anRandom[0] >> 7) ^ v1->tRunRandomState.anRandom[2] ^ v1->tRunRandomState.anRandom[1];
    v29 = v28 + v1->tRunRandomState.anRandom[0];
    v1->tRunRandomState.anRandom[2] ^= v1->tRunRandomState.anRandom[0] >> 7;
    v1->tRunRandomState.anRandom[1] = v28;
    v1->tRunRandomState.anRandom[0] = v29;
    ptQTask = (struct QTask_s *)(unsigned __int16)v29;
    v5[4].tQTaskRefList.ptHead = (struct QReference_s *)(__int64)(((double)(unsigned __int16)v29
                                                                 * 0.0000152587890625
                                                                 * *(double *)&v5[3].ptParent
                                                                 + *(double *)&v5[3].tQTaskRefList.ptMiddle)
                                                                * 30.0);
    QTask_DeleteQTaskAndQTaskRefSafe((struct QReference_s **)&v5[12]);
    goto LABEL_57;
  }
  ptNext = v5[12].ptNext;
  v16 = (struct QReference_s **)&v5[12];
  if ( ptNext )
  {
    ptHead = ptNext->tQTaskChildren.ptHead;
    if ( ptHead )
    {
      vBaseVolume = v14;
      SoundSys_SetSoundVolumes(ptHead, -1.0, vBaseVolume);
      goto LABEL_57;
    }
    goto LABEL_56;
  }
  if ( v7 )
  {
    v18 = v1->tRunRandomState.anRandom[1];
    v19 = (v1->tRunRandomState.anRandom[0] >> 7) ^ v1->tRunRandomState.anRandom[2];
    v1->tRunRandomState.anRandom[2] = v19;
    v20 = v19 ^ v18;
    v21 = v20 + v1->tRunRandomState.anRandom[0];
    v1->tRunRandomState.anRandom[1] = v20;
    v1->tRunRandomState.anRandom[0] = v21;
    ptQTask = (struct QTask_s *)(unsigned __int16)v21;
    v22 = (__int64)((double)(unsigned __int16)v21 * 0.0000152587890625 * (double)*(int *)&v5[11].eQTaskType);
    QTask_DeleteQTaskAndQTaskRefSafe(v16);
    if ( !v5[4].tQTaskRefList.ptHead )
    {
      v23 = SoundSys_NewSoundFn(v5, (char *)&v5[5].tQTaskChildren.ptTail + 32 * v22 + 3);
      v24 = v23;
      if ( v23 )
      {
        v25 = v23->eQTaskType + 511 * SoundSys_eSetRelativeToMicrophoneQTaskEvent;
        LOBYTE(ptQTask) = 1;
        ((void (__cdecl *)(struct QTask_s *, struct QTask_s **))QTask_aatQTaskFinalEvent[0][v25].pfHandler)(
          v23,
          &ptQTask);
        if ( LOBYTE(v5[4].tQTaskRefList.ptMiddle) )
          v24[1].tQTaskRefList.ptMiddle = (struct QReference_s *)((int)v24[1].tQTaskRefList.ptMiddle | 0x20);
        v26 = QTask_NewQTaskRef(v24);
        v27 = *(double *)&v5[3].tQTaskChildren.ptHead;
        *v16 = v26;
        vBaseVolumea = v27;
        SoundSys_SetSoundVolumes((struct QTask_s *)v26->pxObject, -1.0, vBaseVolumea);
      }
    }
  }
LABEL_57:
  v30 = v5[4].tQTaskRefList.ptHead;
  if ( v30 )
    v5[4].tQTaskRefList.ptHead = (struct QReference_s *)((char *)v30 - 1);
  v31 = (int)v5->tQTaskChildren.ptHead;
  if ( *(_DWORD *)v31 && v31 )
  {
    v32 = QTask_nProtectedQTaskStackOffset;
    do
    {
      if ( *(_DWORD *)v31 )
        v33 = **(_DWORD **)v31 != 0 ? *(struct QTask_s **)v31 : nullptr;
      else
        v33 = nullptr;
      QTask_atProtectedQTaskStack[v32].ptQTask = v33;
      pfHandler = (void (__cdecl *)(int))QTask_aatQTaskFinalEvent[1][*(unsigned __int16 *)(v31 + 36)].pfHandler;
      v35 = v32 + 1;
      QTask_nProtectedQTaskStackOffset = v35;
      if ( pfHandler )
      {
        pfHandler(v31);
        v35 = QTask_nProtectedQTaskStackOffset;
      }
      v31 = dword_849C7DC[v35];
      v32 = v35 - 1;
      QTask_nProtectedQTaskStackOffset = v32;
    }
    while ( v31 );
  }
}

// source: j/0/objects/ambientarea.c:354  [anchor-mhash]
void __cdecl AmbientArea_DeleteHandler(struct QTask_s *ptQTask)
{
  struct QTaskList_s *v1; // ebx
  struct QTask_s *ptNext; // eax

  v1 = AmbientArea_ptNoiseQTaskList;
  if ( QTaskList_IsQTaskRegistered(AmbientArea_ptNoiseQTaskList, nullptr, ptQTask) )
    QTaskList_Remove(v1, ptQTask);
  ptNext = ptQTask[12].ptNext;
  if ( ptNext )
    QReference_Delete((struct QReference_s *)ptNext, &QTask_tQTaskRefPool);
  Level_DeinitLevelExpression((struct LevelExpression_s *)&ptQTask[12].ptPrev);
}

// source: j/0/objects/ambientarea.c:392  [size]
void __cdecl AmbientArea_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = AmbientArea_ptParameterList;
}

// source: j/0/objects/ambientarea.c:408  [anchor-mhash]
void __cdecl AmbientArea_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  char *v2; // edi
  char *v3; // ebp
  char v4; // cl
  char v5; // al
  struct Game_s *v6; // eax
  unsigned int v7; // ecx
  unsigned int v8; // edx
  struct QTaskList_s *v9; // ebx

  v2 = (char *)&ptQTask[4].tQTaskRefList.ptMiddle + 3;
  v3 = (char *)&ptQTask[4].tQTaskRefList.ptMiddle + 3;
  v4 = 0;
  *(_DWORD *)&ptQTask[11].eQTaskType = 0;
  while ( 1 )
  {
    v5 = *v2;
    if ( *v2 == 32 || v5 == 59 || v5 == 44 || !v5 )
    {
      if ( v4 )
      {
        strncpy((char *)&ptQTask[5].tQTaskChildren.ptTail + 32 * *(_DWORD *)&ptQTask[11].eQTaskType + 3, v3, v2 - v3);
        v2[32 * (*(_DWORD *)&ptQTask[11].eQTaskType)++ - (_DWORD)v3 + 219 + (_DWORD)ptQTask] = 0;
        v4 = 0;
      }
    }
    else
    {
      if ( !v4 )
        v3 = v2;
      v4 = 1;
    }
    if ( !*v2 )
      break;
    ++v2;
  }
  v6 = Game_ptGame;
  v7 = (Game_ptGame->tRunRandomState.anRandom[0] >> 7)
     ^ Game_ptGame->tRunRandomState.anRandom[2]
     ^ Game_ptGame->tRunRandomState.anRandom[1];
  v8 = v7 + Game_ptGame->tRunRandomState.anRandom[0];
  Game_ptGame->tRunRandomState.anRandom[2] ^= Game_ptGame->tRunRandomState.anRandom[0] >> 7;
  v6->tRunRandomState.anRandom[1] = v7;
  v6->tRunRandomState.anRandom[0] = v8;
  ptQTask[4].tQTaskRefList.ptHead = (struct QReference_s *)(__int64)(((double)(unsigned __int16)v8
                                                                    * 0.0000152587890625
                                                                    * *(double *)&ptQTask[3].ptParent
                                                                    + *(double *)&ptQTask[3].tQTaskRefList.ptMiddle)
                                                                   * 30.0);
  Level_CompileLevelExpression((struct LevelExpression_s *)&ptQTask[12].ptPrev, ptQTask);
  v9 = AmbientArea_ptNoiseQTaskList;
  if ( QTaskList_IsQTaskRegistered(AmbientArea_ptNoiseQTaskList, nullptr, ptQTask)
    || *(float *)&ptQTask[4].tQTaskChildren.ptTail <= 0.0 )
  {
    if ( QTaskList_IsQTaskRegistered(v9, nullptr, ptQTask) )
    {
      if ( *(float *)&ptQTask[4].tQTaskChildren.ptTail == 0.0 )
        QTaskList_Remove(v9, ptQTask);
    }
  }
  else
  {
    QTaskList_Register(v9, (struct QTaskList_s *)ptQTask);
  }
}

// source: j/0/objects/ambientarea.c:499  [size]
void __cdecl AmbientArea_RegisterHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ;
}

// source: j/0/objects/ambientarea.c:511  [anchor-mhash]
void __cdecl AmbientArea_RemoveHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct Game_s *v2; // eax
  unsigned int v3; // ecx
  unsigned int v4; // esi
  int v5; // ecx
  unsigned int v6; // edx

  v2 = Game_ptGame;
  v3 = (Game_ptGame->tRunRandomState.anRandom[0] >> 7) ^ Game_ptGame->tRunRandomState.anRandom[2];
  v4 = Game_ptGame->tRunRandomState.anRandom[1];
  Game_ptGame->tRunRandomState.anRandom[2] = v3;
  v5 = v3 ^ v4;
  v6 = v5 + v2->tRunRandomState.anRandom[0];
  v2->tRunRandomState.anRandom[1] = v5;
  v2->tRunRandomState.anRandom[0] = v6;
  ptQTask[4].tQTaskRefList.ptHead = (struct QReference_s *)(__int64)(((double)(unsigned __int16)v6
                                                                    * 0.0000152587890625
                                                                    * *(double *)&ptQTask[3].ptParent
                                                                    + *(double *)&ptQTask[3].tQTaskRefList.ptMiddle)
                                                                   * 30.0);
  QTask_DeleteQTaskAndQTaskRefSafe((struct QReference_s **)&ptQTask[12]);
}

// source: j/0/objects/ambientarea.c:534  [anchor-hash]
void __cdecl AmbientArea_Open()
{
  unsigned __int16 v0; // si
  struct ParameterList_s *v1; // eax
  int v2; // edx

  AmbientArea_ptNoiseQTaskList = QTaskList_New(200);
  AmbientArea_ptLODVirModel = MTP_GetLODVirModel("johan");
  v0 = QTask_NewQTaskType("AmbientArea", 568, EditorRigidObj_eQTaskType, 0, 0);
  AmbientArea_eQTaskType = v0;
  QTask_LinkQTaskEventHandlerFn(
    v0,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveNoChildrenHandler);
  QTask_LinkQTaskEventHandlerFn(v0, 0, AmbientArea_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 1, AmbientArea_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 2, AmbientArea_DeleteHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))AmbientArea_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(v0, ParameterList_eUpdateInternalDataQTaskEvent, AmbientArea_UpdateInternalDataHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    DynCubeObj_eDynCubeObjRegisterQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))AmbientArea_RegisterHandler);
  QTask_LinkQTaskEventHandlerFn(v0, DynCubeObj_eDynCubeObjRemoveQTaskEvent, AmbientArea_RemoveHandler);
  v1 = (struct ParameterList_s *)Mem_AllocFn(272, 4);
  v2 = Level_eParameterTypeObjectPos;
  v1->ptParameterListItem = (struct ParameterListItem_s *)&v1[1];
  v1->nParameters = 0;
  v1->nMaxParameters = 13;
  AmbientArea_ptParameterList = v1;
  ParameterList_AddParameter(v1, 0x28u, v2, "Position", 7u, nullptr);
  ParameterList_AddParameter(
    AmbientArea_ptParameterList,
    0x58u,
    Level_eParameterTypeReal32x9,
    "Orientation",
    7u,
    nullptr);
  ParameterList_AddParameter(AmbientArea_ptParameterList, 0x40u, Level_eParameterTypeReal64x3, "Size", 7u, nullptr);
  ParameterList_AddParameter(AmbientArea_ptParameterList, 0xA0u, Level_eParameterTypeReal64, "Falloff", 7u, nullptr);
  ParameterList_AddParameter(AmbientArea_ptParameterList, 0x90u, Level_eParameterTypeReal64, "Min delay", 7u, nullptr);
  ParameterList_AddParameter(AmbientArea_ptParameterList, 0x98u, Level_eParameterTypeReal64, "Random wait", 7u, nullptr);
  ParameterList_AddParameter(AmbientArea_ptParameterList, 0xBBu, Level_eParameterTypeString256, "SoundDef", 7u, nullptr);
  ParameterList_AddParameter(
    AmbientArea_ptParameterList,
    0xB9u,
    Level_eParameterTypebool8,
    "Inside Buildings",
    7u,
    nullptr);
  ParameterList_AddParameter(
    AmbientArea_ptParameterList,
    0xBAu,
    Level_eParameterTypebool8,
    "Outside Buildings",
    7u,
    nullptr);
  ParameterList_AddParameter(
    AmbientArea_ptParameterList,
    0x1E4u,
    Level_eParameterTypeVarString,
    "On expression",
    7u,
    nullptr);
  ParameterList_AddParameterMinMax(
    AmbientArea_ptParameterList,
    0xA8u,
    Level_eParameterTypeReal64,
    "Fade time",
    7u,
    0.0,
    10.0);
  ParameterList_AddParameter(
    AmbientArea_ptParameterList,
    0xB8u,
    Level_eParameterTypebool8,
    "Controlled By Music Volume Setting",
    7u,
    nullptr);
  ParameterList_AddParameter(
    AmbientArea_ptParameterList,
    0xB0u,
    Level_eParameterTypeReal32,
    (char *)&stru_68BC20.tQTaskRefList.ptTail,
    7u,
    nullptr);
}

// source: j/0/objects/ambientarea.c:583  [size]
void __cdecl AmbientArea_Close()
{
  int v0; // esi

  QTaskList_Delete(AmbientArea_ptNoiseQTaskList);
  if ( AmbientArea_ptParameterList )
  {
    v0 = *(_DWORD *)((unsigned int)&AmbientArea_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
  QTask_DeleteQTaskType(AmbientArea_eQTaskType);
}

// source: j/0/objects/ambientarea.c:604  [size]
struct QTask_s *__cdecl AmbientArea_New(struct QTask_s *ptParent)
{
  return QTask_NewFn(ptParent, AmbientArea_eQTaskType, nullptr);
}

// source: j/0/objects/ambientarea.c:635  [anchor-callee]
void __cdecl AmbientArea_SetParameters(
        struct QTask_s *ptQTask,
        struct real64x3_t *ptPos,
        struct real32x9_t *ptOrientation,
        struct real64x3_t *ptSize,
        double vFalloff,
        char *zSoundDefString)
{
  char *v6; // ecx
  int v7; // edx
  char v8; // al

  qmemcpy(&ptQTask[1], ptPos, 0x18u);
  qmemcpy(&ptQTask[1].tQTaskRefList.ptMiddle, ptSize, 0x18u);
  qmemcpy(&ptQTask[2].tQTaskChildren, ptOrientation, sizeof(struct QTask_s));
  *(double *)&ptQTask[4].ptNext = vFalloff;
  v6 = zSoundDefString;
  v7 = (char *)&ptQTask[4].tQTaskRefList.ptMiddle + 3 - zSoundDefString;
  do
  {
    v8 = *v6;
    v6[v7] = *v6;
    ++v6;
  }
  while ( v8 );
}

// source: j/0/objects/ambientarea.c:656  [anchor-callee]
float __cdecl AmbientArea_GetNoiseLevelAtPosition(struct real64x3_t *ptPosition)
{
  double v1; // st7
  struct QTask_s **ptQTask; // edx
  int nTask; // esi
  struct QTask_s *v4; // ecx
  double v5; // st6
  double v6; // st5
  double v7; // st4
  double v8; // st6
  double v9; // st6
  double v10; // st5
  double v11; // st5
  float tReal32x3_4; // [esp+Ch] [ebp-14h]
  float tReal32x3_8; // [esp+10h] [ebp-10h]
  float Real32x3_RotateInverse_tTemp; // [esp+14h] [ebp-Ch]
  float Real32x3_RotateInverse_tTemp_4; // [esp+18h] [ebp-8h]
  float Real32x3_RotateInverse_tTemp_8; // [esp+1Ch] [ebp-4h]

  v1 = 0.0;
  if ( AmbientArea_ptNoiseQTaskList->nTask > 0 )
  {
    ptQTask = AmbientArea_ptNoiseQTaskList->ptQTask;
    nTask = AmbientArea_ptNoiseQTaskList->nTask;
    do
    {
      v4 = *ptQTask;
      if ( *(float *)&(*ptQTask)[4].tQTaskChildren.ptTail > 0.0 )
      {
        v5 = ptPosition->vX - *(double *)&v4[1].ptNext;
        v6 = ptPosition->vY - *(double *)&v4[1].tQTaskChildren.ptHead;
        v7 = ptPosition->vZ - *(double *)&v4[1].tQTaskChildren.ptTail;
        Real32x3_RotateInverse_tTemp = v7 * *(float *)&v4[2].ptParent
                                     + v6 * *(float *)&v4[2].tQTaskRefList.ptHead
                                     + v5 * *(float *)&v4[2].tQTaskChildren.ptHead;
        Real32x3_RotateInverse_tTemp_4 = v7 * *(float *)&v4[2].eQTaskType
                                       + v6 * *(float *)&v4[2].tQTaskRefList.ptMiddle
                                       + v5 * *(float *)&v4[2].tQTaskChildren.ptMiddle;
        Real32x3_RotateInverse_tTemp_8 = v7 * *(float *)&v4[3].ptNext
                                       + v6 * *(float *)&v4[2].tQTaskRefList.ptTail
                                       + v5 * *(float *)&v4[2].tQTaskChildren.ptTail;
        v8 = Real32x3_RotateInverse_tTemp;
        if ( Real32x3_RotateInverse_tTemp < 0.0 )
          v8 = -v8;
        v9 = v8 * 0.000244140625;
        v10 = Real32x3_RotateInverse_tTemp_4;
        if ( Real32x3_RotateInverse_tTemp_4 < 0.0 )
          v10 = -v10;
        tReal32x3_4 = v10 * 0.000244140625;
        v11 = Real32x3_RotateInverse_tTemp_8;
        if ( Real32x3_RotateInverse_tTemp_8 < 0.0 )
          v11 = -v11;
        if ( *(double *)&v4[1].tQTaskRefList.ptMiddle + *(double *)&v4[4].ptNext > v9
          && *(double *)&v4[1].ptParent + *(double *)&v4[4].ptNext > tReal32x3_4 )
        {
          tReal32x3_8 = v11 * 0.000244140625;
          if ( *(double *)&v4[2].ptNext + *(double *)&v4[4].ptNext > tReal32x3_8
            && v1 < *(float *)&v4[4].tQTaskChildren.ptTail )
          {
            v1 = *(float *)&v4[4].tQTaskChildren.ptTail;
            if ( v1 >= 1.0 )
              v1 = 1.0;
          }
        }
      }
      ++ptQTask;
      --nTask;
    }
    while ( nTask );
  }
  return v1;
}
