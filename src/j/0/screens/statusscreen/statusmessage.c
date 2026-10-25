/* j/0/screens/statusscreen/statusmessage.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/screens/statusscreen/statusmessage.c:60  [anchor-callee]
void __cdecl StatusMessage_UpdateMorph(struct StatusMessage_s *ptStatusMessage)
{
  char *v1; // esi
  char i; // al
  int v3; // eax
  unsigned int v4; // eax
  struct QReference_s *v5; // eax
  void *pxObject; // ebp
  int Lipsync; // eax
  int nTicks; // ecx
  char *v9; // esi
  float *pvLipsync; // [esp+4h] [ebp-4h] BYREF

  v1 = &ptStatusMessage->zMorphQTasks[strspn(ptStatusMessage->zMorphQTasks, ",\t\n ")];
  for ( i = *v1; *v1; i = *v1 )
  {
    if ( _mb_cur_max_6aece0 <= 1 )
      v3 = pctype_6aecec[i] & 4;
    else
      v3 = isctype(i, 4);
    if ( v3 )
    {
      v4 = atoi(v1);
      if ( v4 < 0x1000 )
      {
        v5 = Level_atLevelQTaskID[v4];
        if ( v5 )
        {
          pxObject = v5->pxObject;
          if ( pxObject )
          {
            if ( QTask_IsQTaskTypeDerived(*((_WORD *)pxObject + 18), BoneDynCubeObj_eQTaskType) )
            {
              Lipsync = SoundSys_GetLipsync(ptStatusMessage->zSound, &pvLipsync);
              nTicks = ptStatusMessage->nTicks;
              if ( nTicks >= Lipsync )
                *((_DWORD *)pxObject + 81) = 0;
              else
                *((float *)pxObject + 81) = pvLipsync[nTicks];
            }
          }
        }
      }
    }
    v9 = &v1[strcspn(v1, ",\t\n ")];
    v1 = (char *)&v9[strspn(v9, ",\t\n ")];
  }
}

// source: j/0/screens/statusscreen/statusmessage.c:136  [anchor-callee]
void __cdecl StatusMessage_PlaySound(struct StatusMessage_s *ptStatusMessage)
{
  #pragma pack(push, 1)
  union
  {
    struct { char v4; };
    struct { char igi2_o1[1]; int SoundLength; };
    struct { char igi2_o2[5]; int nFrequency; };
    char igi2_extent[9];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *v1; // eax
  struct QTask_s *v2; // esi
  int v3; // edx

  if ( ptStatusMessage->zSound[0] && !ptStatusMessage->ptSoundQTaskRef )
  {
    v1 = SoundSys_NewSoundFn(&ptStatusMessage->tEditorRigidObj.tQTask, ptStatusMessage->zSound);
    v2 = v1;
    if ( v1 )
    {
      ptStatusMessage->ptSoundQTaskRef = QTask_NewQTaskRef(v1);
      igi2_frame.nFrequency = Flow_ptFlow->nFrequency;
      igi2_frame.SoundLength = SoundSys_GetSoundLength(v2);
      v3 = 511 * SoundSys_eSetRelativeToMicrophoneQTaskEvent;
      igi2_frame.v4 = 1;
      ptStatusMessage->vDuration = (double)igi2_frame.SoundLength / (double)igi2_frame.nFrequency;
      ((void (__cdecl *)(struct QTask_s *, char *))QTask_aatQTaskFinalEvent[0][v2->eQTaskType + v3].pfHandler)(v2, &igi2_frame.v4);
      SoundSys_GetSoundDef(ptStatusMessage->zSound);
    }
  }
}

// source: j/0/screens/statusscreen/statusmessage.c:167  [anchor-hash]
void __cdecl StatusMessage_KillSound(struct StatusMessage_s *ptStatusMessage)
{
  struct QReference_s *ptSoundQTaskRef; // eax
  struct QTask_s *pxObject; // eax

  ptSoundQTaskRef = ptStatusMessage->ptSoundQTaskRef;
  if ( ptSoundQTaskRef )
  {
    pxObject = (struct QTask_s *)ptSoundQTaskRef->pxObject;
    if ( pxObject )
      QTask_Delete(pxObject);
    QReference_Delete(ptStatusMessage->ptSoundQTaskRef, &QTask_tQTaskRefPool);
    ptStatusMessage->ptSoundQTaskRef = nullptr;
  }
}

// source: j/0/screens/statusscreen/statusmessage.c:192  [anchor-callee]
void __cdecl StatusMessage_UpdateText(struct StatusMessage_s *ptStatusMessage)
{
  #pragma pack(push, 1)
  union
  {
    struct { enum GameLanguage_e eLanguage; };
    struct { char *v7; };
    struct { char igi2_o2[24]; char zResourceName[256]; };
    char igi2_extent[280];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  char *pzCurrentResource; // eax
  unsigned int v2; // edi
  char *v3; // eax
  char *v4; // eax
  char *v5; // eax

  pzCurrentResource = ptStatusMessage->pzCurrentResource;
  if ( pzCurrentResource )
  {
    if ( ptStatusMessage->isLocalize )
    {
      v2 = strcspn(pzCurrentResource, ",\t\n");
      if ( strstr(ptStatusMessage->pzCurrentResource, "//") )
        v2 = strstr(ptStatusMessage->pzCurrentResource, "//") - ptStatusMessage->pzCurrentResource;
      if ( v2 >= 0x100 )
        v2 = 255;
      strncpy(igi2_frame.zResourceName, ptStatusMessage->pzCurrentResource, v2);
      igi2_frame.eLanguage = Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eLanguage;
      igi2_frame.zResourceName[v2] = 0;
      ptStatusMessage->pzText = Config_GetLocalizedStringForLanguage(igi2_frame.zResourceName, igi2_frame.eLanguage, true);
      v3 = strpbrk(ptStatusMessage->pzCurrentResource, ",\t\n");
      ptStatusMessage->pzCurrentResource = v3;
      if ( v3 )
      {
        while ( 1 )
        {
          igi2_frame.v7 = &ptStatusMessage->pzCurrentResource[strspn(ptStatusMessage->pzCurrentResource, ",\t\n ")];
          ptStatusMessage->pzCurrentResource = igi2_frame.v7;
          if ( strncmp(igi2_frame.v7, "//", 2u) )
            break;
          v4 = strpbrk(ptStatusMessage->pzCurrentResource, (char *)&stru_6A4CDC);
          ptStatusMessage->pzCurrentResource = v4;
          v5 = strpbrk(v4, ",\t\n");
          ptStatusMessage->pzCurrentResource = v5;
          if ( !v5 )
            return;
        }
        if ( !*ptStatusMessage->pzCurrentResource )
          ptStatusMessage->pzCurrentResource = nullptr;
      }
    }
    else
    {
      ptStatusMessage->pzText = pzCurrentResource;
      ptStatusMessage->pzCurrentResource = nullptr;
    }
  }
}

// source: j/0/screens/statusscreen/statusmessage.c:266  [anchor-hash]
struct StatusMessage_s *__cdecl StatusMessage_InitText(struct StatusMessage_s *ptStatusMessage)
{
  struct StatusMessage_s *result; // eax
  char *pzText; // eax

  result = (struct StatusMessage_s *)ptStatusMessage->pzResourceNames;
  ptStatusMessage->pzCurrentResource = (char *)result;
  ptStatusMessage->nResources = 0;
  ptStatusMessage->nTotalStringLength = 0;
  if ( result )
  {
    do
    {
      ++ptStatusMessage->nResources;
      StatusMessage_UpdateText(ptStatusMessage);
      pzText = ptStatusMessage->pzText;
      if ( pzText )
        ptStatusMessage->nTotalStringLength += strlen(pzText);
    }
    while ( ptStatusMessage->pzCurrentResource );
    result = (struct StatusMessage_s *)ptStatusMessage->pzResourceNames;
    ptStatusMessage->pzCurrentResource = (char *)result;
  }
  else
  {
    ptStatusMessage->pzCurrentResource = ptStatusMessage->pzResourceNames;
  }
  return result;
}

// source: j/0/screens/statusscreen/statusmessage.c:294  [size]
void __cdecl StatusMessage_GetSerializeParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = StatusMessage_ptSerializeParameterList;
}

// source: j/0/screens/statusscreen/statusmessage.c:328  [size]
void __cdecl StatusMessage_DeSerializeHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ptQTask[17].tQTaskRefList.ptHead = ptQTask[17].tQTaskRefList.ptMiddle;
  ptQTask[18].ptNext = (struct QTask_s *)-1;
  Serialize_DeSerializeHandler(ptQTask, pxContext);
}

// source: j/0/screens/statusscreen/statusmessage.c:346  [anchor-mhash]
void __cdecl StatusMessage_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  LOBYTE(ptQTask[4].tQTaskRefList.ptTail) = 0;
  LOBYTE(ptQTask[11].ptPrev) = 0;
  BYTE1(ptQTask[17].tQTaskRefList.ptTail) = 0;
  LOBYTE(ptQTask[25].tQTaskChildren.ptHead) = 0;
  BYTE2(ptQTask[17].tQTaskRefList.ptTail) = 0;
  ptQTask[2].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[2].tQTaskRefList.ptTail = nullptr;
  ptQTask[2].ptParent = nullptr;
  ptQTask[4].tQTaskRefList.ptHead = nullptr;
  *(_DWORD *)&ptQTask[24].eQTaskType = 0;
  BYTE2(ptQTask[25].tQTaskChildren.ptHead) = 0;
  BYTE1(ptQTask[25].tQTaskChildren.ptHead) = 0;
  LOBYTE(ptQTask[17].tQTaskRefList.ptTail) = 0;
  ptQTask[25].ptNext = (struct QTask_s *)-1;
  ptQTask[25].ptPrev = nullptr;
  HIBYTE(ptQTask[25].tQTaskChildren.ptHead) = 0;
  HIBYTE(ptQTask[17].tQTaskRefList.ptTail) = 1;
  ptQTask[17].tQTaskRefList.ptHead = nullptr;
  ptQTask[4].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[17].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[18].ptPrev = nullptr;
  LOBYTE(ptQTask[18].tQTaskChildren.ptHead) = 0;
  ptQTask[24].tQTaskRefList.ptMiddle = (struct QReference_s *)1084227584;
  ptQTask[18].ptNext = (struct QTask_s *)-1;
  ptQTask[17].ptParent = (struct QTask_s *)1;
  ptQTask[24].ptParent = nullptr;
  QVector_AddElement(StatusMessage_ptQVector, ptQTask);
}

// source: j/0/screens/statusscreen/statusmessage.c:421  [anchor-caller]
void __cdecl StatusMessage_RunHandler(struct QTask_s *ptQTask)
{
  char v1; // al
  struct QReference_s *ptMiddle; // eax
  int v3; // eax
  int v4; // ecx
  struct QTask_s *ptNext; // eax
  struct QTask_s *v6; // eax
  struct QReference_s *v7; // edx
  struct QTask_s *v8; // eax
  struct QTask_s *ptHead; // ecx
  int v10; // edx
  struct QTask_s *v11; // eax
  void (__cdecl *pfHandler)(struct QTask_s *); // eax
  int v13; // edx
  int nWait; // [esp+10h] [ebp-8h]

  if ( !HIBYTE(ptQTask[25].tQTaskChildren.ptHead)
    || (v1 = BYTE1(ptQTask[17].tQTaskRefList.ptTail), ++*(int *)&ptQTask[25].ptPrev, !v1) )
  {
    if ( !BYTE1(ptQTask[25].tQTaskChildren.ptHead) )
    {
      if ( LOBYTE(ptQTask[25].tQTaskChildren.ptHead)
        || ptQTask[2].tQTaskRefList.ptMiddle
        && ptQTask[2].tQTaskRefList.ptTail->ptNext
        && ptQTask[2].ptParent
        && Level_RunLevelExpression((struct LevelExpression_s *)&ptQTask[2].tQTaskRefList.ptMiddle, ptQTask) != 0.0 )
      {
        if ( Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER )
        {
          StatusScreen_ShowCritical((char *)ptQTask[4].tQTaskRefList.ptMiddle, TEXTSCROLLER_COLOUR_RED);
          LOBYTE(ptQTask[24].tQTaskRefList.ptTail) = 1;
          ptQTask[25].ptNext = nullptr;
        }
        else
        {
          *(_DWORD *)&ptQTask[24].eQTaskType = -10000000;
          BYTE1(ptQTask[25].tQTaskChildren.ptHead) = 1;
          HIBYTE(ptQTask[25].tQTaskChildren.ptHead) = 0;
          StatusMessage_PlaySound((struct StatusMessage_s *)ptQTask);
        }
        BYTE2(ptQTask[25].tQTaskChildren.ptHead) = 1;
      }
      else
      {
        BYTE1(ptQTask[25].tQTaskChildren.ptHead) = 0;
      }
    }
    if ( Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER )
    {
      if ( BYTE2(ptQTask[25].tQTaskChildren.ptHead) )
        ++*(int *)&ptQTask[25].ptNext;
    }
    else
    {
      if ( BYTE1(ptQTask[25].tQTaskChildren.ptHead) )
      {
        StatusMessage_UpdateMorph((struct StatusMessage_s *)ptQTask);
        ptMiddle = ptQTask[4].tQTaskRefList.ptMiddle;
        ++*(int *)&ptQTask[24].ptParent;
        if ( ptMiddle )
          v3 = (__int64)((double)Flow_ptFlow->nFrequency
                       * *(float *)&ptQTask[24].tQTaskRefList.ptMiddle
                       * (double)strlen((char *)ptMiddle)
                       / (double)*(int *)&ptQTask[17].eQTaskType);
        else
          v3 = (__int64)((double)Flow_ptFlow->nFrequency * *(float *)&ptQTask[24].tQTaskRefList.ptMiddle);
      }
      else
      {
        v3 = nWait;
      }
      if ( BYTE1(ptQTask[25].tQTaskChildren.ptHead) )
      {
        v4 = *(_DWORD *)&ptQTask[24].eQTaskType;
        if ( LevelFlow_ptLevelFlow->nTick > v4 + v3 )
        {
          if ( ptQTask[17].tQTaskRefList.ptHead )
          {
            StatusMessage_UpdateText((struct StatusMessage_s *)ptQTask);
            ptNext = ptQTask[18].ptNext;
            if ( ptNext != (struct QTask_s *)-1 )
              StatusMessageScreen_RemoveMessage(
                (struct StatusMessageScreen_s *)StatusScreen_ptStatusScreenQTask[52].tQTaskChildren.ptTail,
                (int)ptNext);
            ptQTask[18].ptNext = (struct QTask_s *)StatusMessageScreen_RegisterMessage(
                                                     (struct StatusMessageScreen_s *)StatusScreen_ptStatusScreenQTask[52].tQTaskChildren.ptTail,
                                                     (struct StatusMessage_s *)ptQTask);
            *(_DWORD *)&ptQTask[24].eQTaskType = LevelFlow_ptLevelFlow->nTick;
          }
          else
          {
            if ( v4 != -10000000 && LOBYTE(ptQTask[24].tQTaskRefList.ptTail) )
            {
              v6 = ptQTask[18].ptNext;
              if ( v6 != (struct QTask_s *)-1 )
              {
                StatusMessageScreen_RemoveMessage(
                  (struct StatusMessageScreen_s *)StatusScreen_ptStatusScreenQTask[52].tQTaskChildren.ptTail,
                  (int)v6);
                ptQTask[18].ptNext = (struct QTask_s *)-1;
              }
              StatusMessage_KillSound((struct StatusMessage_s *)ptQTask);
              if ( LOBYTE(ptQTask[25].tQTaskChildren.ptHead) )
              {
                QTask_Delete(ptQTask);
                return;
              }
              v7 = ptQTask[17].tQTaskRefList.ptMiddle;
              v8 = (struct QTask_s *)((char *)&ptQTask[25].ptNext->ptNext + 1);
              ptQTask[24].ptParent = nullptr;
              BYTE1(ptQTask[25].tQTaskChildren.ptHead) = 0;
              HIBYTE(ptQTask[25].tQTaskChildren.ptHead) = 1;
              ptQTask[25].ptNext = v8;
              ptQTask[17].tQTaskRefList.ptHead = v7;
            }
            *(_DWORD *)&ptQTask[24].eQTaskType = LevelFlow_ptLevelFlow->nTick;
          }
        }
      }
    }
    ptHead = ptQTask->tQTaskChildren.ptHead;
    if ( ptHead->ptNext && ptHead )
    {
      v10 = QTask_nProtectedQTaskStackOffset;
      do
      {
        if ( ptHead->ptNext )
          v11 = ptHead->ptNext->ptNext != nullptr ? ptHead->ptNext : nullptr;
        else
          v11 = nullptr;
        QTask_atProtectedQTaskStack[v10].ptQTask = v11;
        pfHandler = (void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[1][ptHead->eQTaskType].pfHandler;
        v13 = v10 + 1;
        QTask_nProtectedQTaskStackOffset = v13;
        if ( pfHandler )
        {
          pfHandler(ptHead);
          v13 = QTask_nProtectedQTaskStackOffset;
        }
        ptHead = (struct QTask_s *)dword_849C7DC[v13];
        v10 = v13 - 1;
        QTask_nProtectedQTaskStackOffset = v10;
      }
      while ( ptHead );
    }
  }
}

// source: j/0/screens/statusscreen/statusmessage.c:546  [anchor-mhash]
void __cdecl StatusMessage_DeleteHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptPrev; // eax
  struct QTask_s *ptHead; // eax
  int v3; // ecx
  struct QReference_s *v4; // eax
  void (__cdecl *pfHandler)(struct QTask_s *); // eax
  struct QReference_s *ptMiddle; // eax
  int v7; // esi

  QVector_RemoveElementByPointer(StatusMessage_ptQVector, ptQTask);
  ptPrev = ptQTask[18].ptPrev;
  if ( ptPrev )
  {
    ptHead = ptPrev->tQTaskChildren.ptHead;
    if ( ptHead )
      QTask_Delete(ptHead);
    QReference_Delete((struct QReference_s *)ptQTask[18].ptPrev, &QTask_tQTaskRefPool);
    ptQTask[18].ptPrev = nullptr;
  }
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
  Level_DeinitLevelExpression((struct LevelExpression_s *)&ptQTask[2].tQTaskRefList.ptMiddle);
  ptMiddle = ptQTask[17].tQTaskRefList.ptMiddle;
  if ( ptMiddle )
  {
    v7 = *(_DWORD *)((unsigned int)&ptMiddle[-1].pxObject & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v7);
    memset(*(void **)(v7 + 8), 0xCDu, *(_DWORD *)(v7 + 16));
    free((void *)v7);
    ptQTask[17].tQTaskRefList.ptMiddle = nullptr;
  }
}

// source: j/0/screens/statusscreen/statusmessage.c:587  [size]
void __cdecl StatusMessage_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = StatusMessage_ptParameterList;
}

// source: j/0/screens/statusscreen/statusmessage.c:603  [anchor-mhash]
void __cdecl StatusMessage_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  Level_CompileLevelExpression((struct LevelExpression_s *)&ptQTask[2].tQTaskRefList.ptMiddle, ptQTask);
  StatusMessage_InitText((struct StatusMessage_s *)ptQTask);
}

// source: j/0/screens/statusscreen/statusmessage.c:640  [anchor-refs]
void __cdecl StatusMessage_RegisterScriptSymbolsHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { char zName[64]; };
    struct { char igi2_o1[64]; char zTemp[128]; };
    char igi2_extent[192];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)

  if ( !LOBYTE(ptQTask[17].tQTaskRefList.ptTail) )
  {
    LOBYTE(ptQTask[17].tQTaskRefList.ptTail) = 1;
    Level_GetUniqueQTaskNameFromTask(igi2_frame.zName, ptQTask);
    sprintf(igi2_frame.zTemp, "%s.isSendt", igi2_frame.zName);
    Symbol_Register(
      igi2_frame.zTemp,
      (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_Int8,
      (char *)&ptQTask[25].tQTaskChildren.ptHead + 2,
      1,
      QSCRIPT_SYMBOLCLASS_VARIABLE,
      QSCRIPT_SYMBOLTYPE_INT,
      QSCRIPT_SYMBOLLIFESPAN_FINITE);
    sprintf(igi2_frame.zTemp, "%s.nTickSendt", igi2_frame.zName);
    Symbol_Register(
      igi2_frame.zTemp,
      (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_Int,
      &ptQTask[24].eQTaskType,
      4,
      QSCRIPT_SYMBOLCLASS_VARIABLE,
      QSCRIPT_SYMBOLTYPE_INT,
      QSCRIPT_SYMBOLLIFESPAN_FINITE);
    sprintf(igi2_frame.zTemp, "%s.isFinishedDisplay", igi2_frame.zName);
    Symbol_Register(
      igi2_frame.zTemp,
      (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_Int8,
      (char *)&ptQTask[25].tQTaskChildren.ptHead + 3,
      1,
      QSCRIPT_SYMBOLCLASS_VARIABLE,
      QSCRIPT_SYMBOLTYPE_INT,
      QSCRIPT_SYMBOLLIFESPAN_FINITE);
    sprintf(igi2_frame.zTemp, "%s.nFinishedDisplay", igi2_frame.zName);
    Symbol_Register(
      igi2_frame.zTemp,
      (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_Int,
      &ptQTask[25],
      4,
      QSCRIPT_SYMBOLCLASS_VARIABLE,
      QSCRIPT_SYMBOLTYPE_INT,
      QSCRIPT_SYMBOLLIFESPAN_FINITE);
    sprintf(igi2_frame.zTemp, "%s.nTicksSinceFinishedDisplay", igi2_frame.zName);
    Symbol_Register(
      igi2_frame.zTemp,
      (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_Int,
      &ptQTask[25].ptPrev,
      4,
      QSCRIPT_SYMBOLCLASS_VARIABLE,
      QSCRIPT_SYMBOLTYPE_INT,
      QSCRIPT_SYMBOLLIFESPAN_FINITE);
  }
}

// source: j/0/screens/statusscreen/statusmessage.c:684  [anchor-mhash]
void __cdecl StatusMessage_RemoveScriptSymbolsHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { char zName[64]; };
    struct { char igi2_o1[64]; char zTemp[128]; };
    char igi2_extent[192];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)

  if ( LOBYTE(ptQTask[17].tQTaskRefList.ptTail) )
  {
    Level_GetUniqueQTaskNameFromTask(igi2_frame.zName, ptQTask);
    sprintf(igi2_frame.zTemp, "%s.isSendt", igi2_frame.zName);
    Symbol_Remove(igi2_frame.zTemp);
    sprintf(igi2_frame.zTemp, "%s.nTickSendt", igi2_frame.zName);
    Symbol_Remove(igi2_frame.zTemp);
    sprintf(igi2_frame.zTemp, "%s.isFinishedDisplay", igi2_frame.zName);
    Symbol_Remove(igi2_frame.zTemp);
    sprintf(igi2_frame.zTemp, "%s.nFinishedDisplay", igi2_frame.zName);
    Symbol_Remove(igi2_frame.zTemp);
    sprintf(igi2_frame.zTemp, "%s.nTicksSinceFinishedDisplay", igi2_frame.zName);
    Symbol_Remove(igi2_frame.zTemp);
    LOBYTE(ptQTask[17].tQTaskRefList.ptTail) = 0;
  }
}

// source: j/0/screens/statusscreen/statusmessage.c:730  [anchor-mhash]
int __cdecl StatusMessage_RemoveHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *ptPrev; // eax
  struct QTask_s *ptHead; // eax
  int result; // eax

  ptPrev = ptQTask[18].ptPrev;
  if ( ptPrev )
  {
    ptHead = ptPrev->tQTaskChildren.ptHead;
    if ( ptHead )
      QTask_Delete(ptHead);
    QReference_Delete((struct QReference_s *)ptQTask[18].ptPrev, &QTask_tQTaskRefPool);
    ptQTask[18].ptPrev = nullptr;
  }
  result = (int)ptQTask[18].ptNext;
  if ( result != -1 )
  {
    StatusMessageScreen_RemoveMessage(
      (struct StatusMessageScreen_s *)StatusScreen_ptStatusScreenQTask[52].tQTaskChildren.ptTail,
      result);
    ptQTask[18].ptNext = (struct QTask_s *)-1;
  }
  return result;
}

// source: j/0/screens/statusscreen/statusmessage.c:808  [anchor-caller]
struct QTask_s *__cdecl StatusMessage_New(
        struct QTask_s *ptParent,
        char *pzText,
        char *zSprite,
        char *zSound,
        enum bool isLocalize)
{
  struct StatusMessage_s *v6; // esi
  char *v7; // eax

  if ( Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER )
  {
    StatusScreen_ShowCritical(pzText, TEXTSCROLLER_COLOUR_RED);
    return nullptr;
  }
  else
  {
    v6 = (struct StatusMessage_s *)QTask_NewFn(ptParent, StatusMessage_eQTaskType, nullptr);
    v6->isLocalize = isLocalize;
    v7 = (char *)Mem_AllocFn(strlen(pzText) + 1, 4);
    v6->pzResourceNames = v7;
    strcpy(v7, pzText);
    strncpy(v6->zSprite, zSprite, 0x100u);
    strncpy(v6->zSound, zSound, 0x100u);
    v6->isSendOnce = 1;
    v6->isForceSend = 1;
    Level_CompileLevelExpression(&v6->tLevelExpressionSend, &v6->tEditorRigidObj.tQTask);
    StatusMessage_InitText(v6);
    return &v6->tEditorRigidObj.tQTask;
  }
}

// source: j/0/screens/statusscreen/statusmessage.c:869  [anchor-hash]
void __cdecl StatusMessage_CleanUp()
{
  unsigned int i; // edx
  int v1; // ecx
  struct QReference_s *v2; // eax

LABEL_1:
  for ( i = 0; i < StatusMessage_ptQVector->tPrivate.nElements; ++i )
  {
    v1 = 0;
    while ( 1 )
    {
      v2 = Level_atLevelQTaskID[v1];
      if ( v2 )
      {
        if ( v2->pxObject == StatusMessage_ptQVector->tPrivate.papxElement[i] )
          break;
      }
      if ( ++v1 >= 4096 )
        goto LABEL_6;
    }
    if ( v1 == -1 )
    {
LABEL_6:
      QTask_Delete((struct QTask_s *)StatusMessage_ptQVector->tPrivate.papxElement[i]);
      goto LABEL_1;
    }
  }
}

// source: j/0/screens/statusscreen/statusmessage.c:900  [anchor-hash]
void __cdecl StatusMessage_Open()
{
  unsigned __int16 v0; // si
  void **v1; // esi
  struct QVector_s *v2; // eax
  struct ParameterList_s *v3; // eax
  int v4; // edx
  struct ParameterList_s *v5; // eax
  int v6; // edx

  v0 = QTask_NewQTaskType("StatusMessage", 1016, EditorRigidObj_eQTaskType, 0, 0);
  StatusMessage_eQTaskType = v0;
  QTask_LinkQTaskEventHandlerFn(
    v0,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveNoChildrenHandler);
  QTask_LinkQTaskEventHandlerFn(v0, 0, StatusMessage_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 1, StatusMessage_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 2, StatusMessage_DeleteHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))StatusMessage_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    ParameterList_eUpdateInternalDataQTaskEvent,
    StatusMessage_UpdateInternalDataHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(
    v0,
    Level_eRegisterLevelScriptSymbolsEvent,
    StatusMessage_RegisterScriptSymbolsHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(
    v0,
    Level_eRemoveLevelScriptSymbolsEvent,
    StatusMessage_RemoveScriptSymbolsHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    DynCubeObj_eDynCubeObjRemoveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))StatusMessage_RemoveHandler);
  v1 = (void **)Mem_AllocFn(512, 4);
  v2 = (struct QVector_s *)Mem_AllocFn(24, 4);
  v2->tPrivate.nArraySize = 128;
  v2->tPrivate.nReallocSize = 32;
  v2->tPrivate.nElements = 0;
  v2->tPrivate.isPrivateMem = false;
  v2->tPrivate.papxElement = v1;
  v2->tPrivate.isStrictOrder = false;
  StatusMessage_ptQVector = v2;
  dword_79EE4E0 = 0;
  dword_79EE4E4 = 1079574528;
  dword_79EE4D8 = 0;
  dword_79EE4DC = 0;
  v3 = (struct ParameterList_s *)Mem_AllocFn(212, 4);
  v4 = Level_eParameterTypeObjectPos;
  v3->ptParameterListItem = (struct ParameterListItem_s *)&v3[1];
  v3->nParameters = 0;
  v3->nMaxParameters = 10;
  StatusMessage_ptParameterList = v3;
  ParameterList_AddParameter(v3, 0x28u, v4, "Position", 7u, nullptr);
  ParameterList_AddParameter(
    StatusMessage_ptParameterList,
    0x40u,
    Level_eParameterTypeReal32x9,
    "Orientation",
    7u,
    nullptr);
  ParameterList_AddParameter(StatusMessage_ptParameterList, 0x68u, Level_eParameterTypeVarString, "Send", 7u, nullptr);
  ParameterList_AddParameter(StatusMessage_ptParameterList, 0x2C0u, Level_eParameterTypeVarString, "Text", 7u, nullptr);
  ParameterList_AddParameter(StatusMessage_ptParameterList, 0xBCu, Level_eParameterTypeString256, "Sprite", 7u, nullptr);
  ParameterList_AddParameter(StatusMessage_ptParameterList, 0x1BCu, Level_eParameterTypeString256, "Sound", 7u, nullptr);
  ParameterList_AddParameter(
    StatusMessage_ptParameterList,
    0x2C5u,
    Level_eParameterTypebool8,
    "Is send once",
    7u,
    nullptr);
  ParameterList_AddParameter(
    StatusMessage_ptParameterList,
    0x2C6u,
    Level_eParameterTypebool8,
    "Cutscene message",
    7u,
    nullptr);
  ParameterList_AddParameter(
    StatusMessage_ptParameterList,
    0x3D8u,
    Level_eParameterTypeReal32,
    "Duration",
    7u,
    &dword_79EE4D8);
  ParameterList_AddParameter(
    StatusMessage_ptParameterList,
    0x2D8u,
    Level_eParameterTypeString256,
    "Morph QTask IDs",
    7u,
    nullptr);
  LOWORD(v1) = StatusMessage_eQTaskType;
  QTask_LinkQTaskEventHandlerFn(
    StatusMessage_eQTaskType,
    Serialize_eDeSerializeQTaskEvent,
    StatusMessage_DeSerializeHandler);
  QTask_LinkQTaskEventHandlerFn(
    (unsigned __int16)v1,
    Serialize_eGetSerializeParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))StatusMessage_GetSerializeParameterListHandler);
  v5 = (struct ParameterList_s *)Mem_AllocFn(192, 4);
  v5->ptParameterListItem = (struct ParameterListItem_s *)&v5[1];
  v6 = Level_eParameterTypeInt32;
  v5->nParameters = 0;
  v5->nMaxParameters = 9;
  StatusMessage_ptSerializeParameterList = v5;
  ParameterList_AddParameter(v5, 0x3E4u, v6, "TickSent", 7u, nullptr);
  ParameterList_AddParameter(
    StatusMessage_ptSerializeParameterList,
    0x3E8u,
    Level_eParameterTypeInt32,
    "FinishedDisplay",
    7u,
    nullptr);
  ParameterList_AddParameter(
    StatusMessage_ptSerializeParameterList,
    0x3ECu,
    Level_eParameterTypeInt32,
    "TicksSinceFinishedDisplay",
    7u,
    nullptr);
  ParameterList_AddParameter(
    StatusMessage_ptSerializeParameterList,
    0x3F0u,
    Level_eParameterTypebool8,
    "isForceSend",
    7u,
    nullptr);
  ParameterList_AddParameter(
    StatusMessage_ptSerializeParameterList,
    0x3F1u,
    Level_eParameterTypebool8,
    "isDisplay",
    7u,
    nullptr);
  ParameterList_AddParameter(
    StatusMessage_ptSerializeParameterList,
    0x3F2u,
    Level_eParameterTypebool8,
    "isSent",
    7u,
    nullptr);
  ParameterList_AddParameter(
    StatusMessage_ptSerializeParameterList,
    0x3F3u,
    Level_eParameterTypebool8,
    "isFinishedDisplay",
    7u,
    nullptr);
  ParameterList_AddParameter(
    StatusMessage_ptSerializeParameterList,
    0x3DCu,
    Level_eParameterTypebool8,
    "isFinishedPrinting",
    7u,
    nullptr);
  ParameterList_AddParameter(
    StatusMessage_ptSerializeParameterList,
    0x3E0u,
    Level_eParameterTypeInt32,
    "nTicks",
    7u,
    nullptr);
}

// source: j/0/screens/statusscreen/statusmessage.c:968  [anchor-hash]
void __cdecl StatusMessage_Close()
{
  int v0; // esi
  int v1; // esi

  QVector_Delete(StatusMessage_ptQVector);
  if ( StatusMessage_ptParameterList )
  {
    v0 = *(_DWORD *)((unsigned int)&StatusMessage_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
  if ( StatusMessage_ptSerializeParameterList )
  {
    v1 = *(_DWORD *)((unsigned int)&StatusMessage_ptSerializeParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v1);
    memset(*(void **)(v1 + 8), 0xCDu, *(_DWORD *)(v1 + 16));
    free((void *)v1);
  }
  QTask_DeleteQTaskType(StatusMessage_eQTaskType);
}
