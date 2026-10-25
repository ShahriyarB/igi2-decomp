/* j/0/menusystem/inputbox.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/menusystem/inputbox.c:99  [size]
void __cdecl InputBox_DeleteLetter(struct InputBox_t *ptInputBox, int nPos)
{
  char v3; // dl
  char *v4; // eax
  bool v6; // zf
  struct QHashTable_s *v7; // esi
  unsigned int v8; // eax
  struct Sample_s *v9; // edx
  unsigned int v10; // ecx
  struct SoundModify_t ptModify; // [esp+8h] [ebp-64h] BYREF

  v3 = ptInputBox->zInputString[nPos];
  v4 = &ptInputBox->zInputString[nPos];
  if ( v3 )
  {
    do
      *v4 = v4[1];
    while ( *++v4 );
  }
  v6 = SoundSys_isSoundDisabled == 0;
  ptInputBox->nCarretPos = nPos;
  if ( v6 )
  {
    v7 = Sound_ptSampleHashTable;
    v8 = Sound_ptSampleHashTable->tPrivate.pfHashFunction(Sound_ptSampleHashTable->tPrivate.nHashTableSize, "menu_k01");
    v9 = (struct Sample_s *)((int  (__cdecl *)(struct QHashTable_s *, unsigned int, const void *))Sound_ptSampleHashTable->tPrivate.pfFindElement)(v7, v8, (const void *)("menu_k01"));
    Sound_DefaultSoundModify(&ptModify);
    v10 = SoundSys_nCurrentID++;
    SoundSys_AddSoundToRequestlist(v10, v9, 1u, &ptModify);
  }
}

// source: j/0/menusystem/inputbox.c:127  [anchor-strings]
void __cdecl InputBox_InsertLetter(struct InputBox_t *ptInputBox, int nPos, char nChar)
{
  #pragma pack(push, 1)
  union
  {
    struct { char zSoundRes[64]; };
    struct { char igi2_o1[64]; struct SoundModify_t ptModify; };
    char igi2_extent[164];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int i; // eax
  struct QHashTable_s *v5; // esi
  unsigned int v6; // eax
  struct Sample_s *v7; // edx
  unsigned int v8; // ecx

  for ( i = strlen(ptInputBox->zInputString); i >= nPos; --i )
    ptInputBox->zInputString[i + 1] = ptInputBox->zInputString[i];
  ptInputBox->zInputString[nPos] = nChar;
  ptInputBox->nCarretPos = nPos + 1;
  sprintf(igi2_frame.zSoundRes, "menu_k0%.1d", abs8(nChar) % 7 + 1);
  if ( !SoundSys_isSoundDisabled )
  {
    v5 = Sound_ptSampleHashTable;
    v6 = Sound_ptSampleHashTable->tPrivate.pfHashFunction(Sound_ptSampleHashTable->tPrivate.nHashTableSize, igi2_frame.zSoundRes);
    v7 = (struct Sample_s *)((int  (__cdecl *)(struct QHashTable_s *, unsigned int, const void *))Sound_ptSampleHashTable->tPrivate.pfFindElement)(v5, v6, (const void *)(igi2_frame.zSoundRes));
    Sound_DefaultSoundModify(&igi2_frame.ptModify);
    v8 = SoundSys_nCurrentID++;
    SoundSys_AddSoundToRequestlist(v8, v7, 1u, &igi2_frame.ptModify);
  }
}

// source: j/0/menusystem/inputbox.c:164  [size]
void __cdecl InputBox_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ((void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[0][MenuWindow_eQTaskType].pfHandler)(
    ptQTask,
    pxContext);
  ptQTask[1].tQTaskChildren.ptMiddle = (struct QTask_s *)15;
  LOBYTE(ptQTask[2].tQTaskChildren.ptMiddle) = 0;
  ptQTask[21].tQTaskChildren.ptTail = (struct QTask_s *)4;
  ptQTask[21].tQTaskRefList.ptHead = (struct QReference_s *)20;
  ptQTask[1].tQTaskRefList.ptTail = (struct QReference_s *)1;
  ptQTask[1].ptParent = (struct QTask_s *)1;
  ptQTask[15].ptPrev = nullptr;
  ptQTask[15].tQTaskChildren.ptHead = nullptr;
  ptQTask[15].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[17].ptNext = nullptr;
  ptQTask[17].ptPrev = nullptr;
  ptQTask[17].tQTaskChildren.ptHead = nullptr;
  ptQTask[17].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[19].ptNext = nullptr;
  ptQTask[19].ptPrev = nullptr;
  ptQTask[19].tQTaskChildren.ptHead = nullptr;
  ptQTask[19].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[21].ptNext = nullptr;
  LOBYTE(ptQTask[21].ptPrev) = 0;
  BYTE1(ptQTask[21].ptPrev) = 0;
  BYTE2(ptQTask[21].ptPrev) = 0;
  HIBYTE(ptQTask[21].ptPrev) = 0;
  ptQTask[21].tQTaskChildren.ptMiddle = nullptr;
  LOBYTE(ptQTask[2].ptPrev) = 1;
}

// source: j/0/menusystem/inputbox.c:203  [anchor-mhash]
void __cdecl InputBox_DeleteHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptMiddle; // eax

  ptMiddle = ptQTask[21].tQTaskChildren.ptMiddle;
  if ( ptMiddle )
  {
    Text_Delete((struct StaticTilemap_s *)ptMiddle);
    ptQTask[21].tQTaskChildren.ptMiddle = nullptr;
  }
  Level_DeinitLevelExpression((struct LevelExpression_s *)&ptQTask[15].ptPrev);
  Level_DeinitLevelExpression((struct LevelExpression_s *)&ptQTask[17].ptPrev);
  Level_DeinitLevelExpression((struct LevelExpression_s *)&ptQTask[19].ptPrev);
  ((void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[Level_eRemoveLevelScriptSymbolsEvent][ptQTask->eQTaskType].pfHandler)(ptQTask);
}

// source: j/0/menusystem/inputbox.c:232  [anchor-mhash]
void __cdecl InputBox_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *ptMiddle; // eax
  struct QTask_s *Font; // eax

  Level_CompileLevelExpression((struct LevelExpression_s *)&ptQTask[15].ptPrev, ptQTask);
  Level_CompileLevelExpression((struct LevelExpression_s *)&ptQTask[17].ptPrev, ptQTask);
  Level_CompileLevelExpression((struct LevelExpression_s *)&ptQTask[19].ptPrev, ptQTask);
  ptMiddle = ptQTask[21].tQTaskChildren.ptMiddle;
  if ( ptMiddle )
  {
    Text_Delete((struct StaticTilemap_s *)ptMiddle);
    ptQTask[21].tQTaskChildren.ptMiddle = nullptr;
  }
  ((void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[ParameterList_eUpdateInternalDataQTaskEvent][MenuWindow_eQTaskType].pfHandler)(
    ptQTask,
    pxContext);
  Font = (struct QTask_s *)MenuManager_GetFont(*(struct QTask_s **)&ptQTask[1].eQTaskType, (char *)&g_zFontName_0);
  ptQTask[21].tQTaskChildren.ptHead = Font;
  if ( Font )
    ptQTask[21].tQTaskChildren.ptMiddle = (struct QTask_s *)Text_New(
                                                              (struct QSprite_s *)Font,
                                                              0.0,
                                                              0.0,
                                                              (char *)&g_zInitialValue);
}

// source: j/0/menusystem/inputbox.c:272  [anchor-caller]
void __cdecl InputBox_RunHandler(struct QTask_s *ptQTask)
{
  int v1; // ebx
  struct QTask_s *v2; // eax
  struct QTask_s *ptTail; // ecx
  struct QTask_s *v4; // eax
  int v5; // eax
  int v6; // eax

  if ( *(_BYTE *)(*(_DWORD *)&ptQTask[1].eQTaskType + 10023) )
  {
    BYTE1(ptQTask[21].ptPrev) = 0;
    ptQTask[2].tQTaskChildren.ptHead = nullptr;
  }
  else if ( BYTE1(ptQTask[21].ptPrev) )
  {
    if ( tKeyboardBuffer.nBuffer )
    {
      while ( 1 )
      {
        v1 = 0;
        if ( tKeyboardBuffer.nBuffer )
        {
          v1 = tKeyboardBuffer.anBuffer[tKeyboardBuffer.iBufferIndex++];
          if ( tKeyboardBuffer.iBufferIndex == 32 )
            tKeyboardBuffer.iBufferIndex = 0;
          --tKeyboardBuffer.nBuffer;
        }
        v2 = (struct QTask_s *)strlen((char *)&ptQTask[2].tQTaskChildren.ptMiddle);
        switch ( v1 )
        {
          case -10:
            goto LABEL_14;
          case -9:
            ptQTask[21].tQTaskChildren.ptTail = nullptr;
            goto LABEL_43;
          case -8:
            *(_DWORD *)(*(_DWORD *)&ptQTask[1].eQTaskType + 52) = 3;
            BYTE1(ptQTask[21].ptPrev) = 0;
            ptQTask[2].tQTaskChildren.ptHead = nullptr;
            goto LABEL_43;
          case -7:
            *(_DWORD *)(*(_DWORD *)&ptQTask[1].eQTaskType + 52) = 3;
            BYTE1(ptQTask[21].ptPrev) = 0;
            ptQTask[2].tQTaskChildren.ptHead = nullptr;
            if ( ptQTask[19].ptPrev && ptQTask[19].tQTaskChildren.ptHead->ptNext && ptQTask[19].tQTaskChildren.ptMiddle )
              Level_RunLevelExpression((struct LevelExpression_s *)&ptQTask[19].ptPrev, ptQTask);
            goto LABEL_43;
          case -6:
            ptTail = ptQTask[21].tQTaskChildren.ptTail;
            if ( (int)ptTail < (int)v2 )
              InputBox_DeleteLetter((struct InputBox_t *)ptQTask, (int)ptTail);
            goto LABEL_43;
          case -5:
            v4 = ptQTask[21].tQTaskChildren.ptTail;
            if ( (int)v4 > 0 )
              InputBox_DeleteLetter((struct InputBox_t *)ptQTask, (int)(&v4[-1].isInMemPool + 1));
            goto LABEL_43;
          case -4:
          case -3:
            goto LABEL_43;
          case -2:
            if ( (int)v2 >= (int)&ptQTask[21].tQTaskChildren.ptTail->ptNext + 1 )
              v2 = (struct QTask_s *)((char *)&ptQTask[21].tQTaskChildren.ptTail->ptNext + 1);
            ptQTask[21].tQTaskChildren.ptTail = v2;
            goto LABEL_43;
          case -1:
            v2 = (int)(&ptQTask[21].tQTaskChildren.ptTail[-1].isInMemPool + 1) < 0
               ? nullptr
               : (struct QTask_s *)(&ptQTask[21].tQTaskChildren.ptTail[-1].isInMemPool + 1);
LABEL_14:
            ptQTask[21].tQTaskChildren.ptTail = v2;
            goto LABEL_43;
          default:
            if ( (int)v2 >= (int)&ptQTask[21].tQTaskRefList.ptHead[-1].pxObject + 3 || v1 <= 0 || (_BYTE)v1 == 34 )
              goto LABEL_43;
            if ( HIBYTE(ptQTask[21].ptPrev) )
            {
              if ( _mb_cur_max_6aece0 <= 1 )
                v5 = pctype_6aecec[v1] & 4;
              else
                v5 = isctype(v1, 4);
              if ( v5 || v1 == 46 )
                goto LABEL_42;
            }
            else
            {
              if ( _mb_cur_max_6aece0 <= 1 )
                v6 = pctype_6aecec[v1] & 0x157;
              else
                v6 = isctype(v1, 343);
              if ( v6 )
LABEL_42:
                InputBox_InsertLetter((struct InputBox_t *)ptQTask, (int)ptQTask[21].tQTaskChildren.ptTail, v1);
            }
LABEL_43:
            if ( !tKeyboardBuffer.nBuffer )
              goto LABEL_44;
            break;
        }
      }
    }
  }
  else
  {
    MenuWindow_HitTest(
      (struct MenuWindow_t *)ptQTask,
      (int)ptQTask[1].ptNext,
      (int)ptQTask[1].ptPrev,
      (int)ptQTask[1].tQTaskChildren.ptHead,
      (int)ptQTask[1].tQTaskChildren.ptMiddle,
      nullptr,
      nullptr);
    if ( HIBYTE(ptQTask[2].ptNext) || ptQTask[2].tQTaskChildren.ptHead == (struct QTask_s *)-7 )
    {
      *(_DWORD *)(*(_DWORD *)&ptQTask[1].eQTaskType + 52) = 4;
      BYTE1(ptQTask[21].ptPrev) = 1;
      ptQTask[21].tQTaskChildren.ptTail = (struct QTask_s *)strlen((char *)&ptQTask[2].tQTaskChildren.ptMiddle);
      SoundSys_PlaySimpleSoundFn("menu_k01", 0, nullptr);
    }
  }
LABEL_44:
  ((void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[1][MenuWindow_eQTaskType].pfHandler)(ptQTask);
}

// source: j/0/menusystem/inputbox.c:421  [size]
void __cdecl InputBox_DrawHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { char *nYPos; };
    struct { char igi2_o1[4]; char *zInputString; };
    struct { char igi2_o2[8]; char *nXPos; };
    struct { char igi2_o3[12]; float vFade; };
    struct { char igi2_o4[16]; struct QTask_s *v23; };
    struct { char igi2_o5[20]; struct QVertexStripContext_s tContext; };
    struct { char igi2_o6[40]; struct QVertex_s atQVertex[2]; };
    struct { char igi2_o7[112]; char zString[264]; };
    struct { char igi2_o8[376]; char zTemp[256]; };
    char igi2_extent[632];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct MenuWindow_t *v1; // esi
  double v2; // st7
  struct QTask_s *ptMiddle; // edi
  signed int v4; // edx
  signed int v5; // eax
  __int16 *ptNext; // edx
  struct QTilemap_s *v7; // edi
  char *v8; // eax
  unsigned __int8 v9; // dl
  int p_ptTail; // ecx
  int v11; // ebx
  struct QTask_s *v12; // eax
  struct QTask_s *ptTail; // eax
  struct QTask_s *v14; // esi
  struct QTask_s *v15; // ecx
  int ptPrev_high; // edx
  int ptNext_low; // eax
  struct QTask_s *v18; // ecx

  v1 = (struct MenuWindow_t *)ptQTask;
  v2 = (double)(*(_DWORD *)(*(_DWORD *)&ptQTask[1].eQTaskType + 356) - 8) * 0.125;
  if ( v2 <= 0.0 )
    igi2_frame.vFade = 0.0;
  else
    igi2_frame.vFade = v2;
  ((void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[Screen_eDrawQTaskEvent][MenuWindow_eQTaskType].pfHandler)(ptQTask);
  ptMiddle = ptQTask[21].tQTaskChildren.ptMiddle;
  igi2_frame.v23 = ptMiddle;
  if ( ptMiddle )
  {
    igi2_frame.nXPos = (char *)&ptQTask[1].ptNext->ptNext + 2;
    igi2_frame.nYPos = (char *)&ptQTask[1].ptPrev->ptNext + 2;
    if ( BYTE2(ptQTask[21].ptPrev) )
    {
      v4 = strlen((char *)&ptQTask[2].tQTaskChildren.ptMiddle);
      v5 = 0;
      if ( v4 > 0 )
      {
        memset(igi2_frame.zTemp, 0x2Au, v4);
        v5 = v4;
      }
      igi2_frame.zTemp[v5] = 0;
      igi2_frame.zInputString = igi2_frame.zTemp;
    }
    else
    {
      igi2_frame.zInputString = (char *)&ptQTask[2].tQTaskChildren.ptMiddle;
    }
    ptNext = (__int16 *)ptMiddle->ptNext;
    memset(ptMiddle->ptNext->tQTaskChildren.ptMiddle, 0, 2 * SHIWORD(ptMiddle->ptNext->ptPrev));
    memset(ptNext + 8, 0, ptNext[3] * ptNext[2]);
    v7 = (struct QTilemap_s *)ptMiddle->ptNext;
    v8 = igi2_frame.zInputString;
    v9 = *igi2_frame.zInputString;
    p_ptTail = (int)&igi2_frame.v23->ptNext->tQTaskChildren.ptHead->tQTaskChildren.ptMiddle->tQTaskChildren.ptTail;
    if ( *igi2_frame.zInputString )
    {
      v11 = (char *)&igi2_frame.v23->ptNext->tQTaskChildren.ptTail - igi2_frame.zInputString;
      do
      {
        v8[v11] = *(_BYTE *)(v9 + p_ptTail);
        v9 = *++v8;
      }
      while ( v9 );
    }
    QTilemap_UpdateGraphicWidth(v7, 0);
    *(float *)&ptQTask[21].tQTaskChildren.ptMiddle->ptPrev = (float)(int)igi2_frame.nXPos;
    *(float *)&ptQTask[21].tQTaskChildren.ptMiddle->tQTaskChildren.ptHead = (float)(int)igi2_frame.nYPos;
    *(_DWORD *)&ptQTask[21].tQTaskChildren.ptMiddle->eQTaskType |= 0x80000u;
    *(float *)&ptQTask[21].tQTaskChildren.ptMiddle->tQTaskChildren.ptTail = igi2_frame.vFade;
    v12 = ptQTask[21].tQTaskChildren.ptMiddle;
    QTilemap_Register(
      (struct QTilemap_s *)v12->ptNext,
      *(float *)&v12->ptPrev,
      *(float *)&v12->tQTaskChildren.ptHead,
      *(float *)&v12->tQTaskRefList.ptHead,
      *(float *)&v12->tQTaskRefList.ptMiddle,
      *(float *)&v12->tQTaskRefList.ptTail,
      *(float *)&v12->tQTaskChildren.ptTail,
      *(float *)&v12->tQTaskChildren.ptMiddle,
      *(_DWORD *)&v12->eQTaskType | 0x40000000,
      (int)v12->ptParent);
    if ( BYTE1(ptQTask[21].ptPrev) && ((2 * Flow_ptFlow->nTicks / Flow_ptFlow->nFrequency) & 1) != 0 )
    {
      strncpy(igi2_frame.zString, igi2_frame.zInputString, (size_t)ptQTask[21].tQTaskChildren.ptTail);
      ptTail = ptQTask[21].tQTaskChildren.ptTail;
      v14 = ptQTask[21].tQTaskChildren.ptMiddle;
      igi2_frame.zString[(_DWORD)ptTail] = 97;
      igi2_frame.zString[(_DWORD)ptTail + 1] = 0;
      Text_SetString((struct StaticTilemap_s *)v14, igi2_frame.zString);
      v15 = ptQTask[21].tQTaskChildren.ptMiddle->ptNext;
      ptPrev_high = SHIWORD(v15->ptPrev);
      ptNext_low = 0;
      if ( ptPrev_high > 0 )
      {
        v18 = v15->tQTaskChildren.ptMiddle;
        do
        {
          if ( SLOWORD(v18->ptNext) > ptNext_low )
            ptNext_low = SLOWORD(v18->ptNext);
          v18 = (struct QTask_s *)((char *)v18 + 2);
          --ptPrev_high;
        }
        while ( ptPrev_high );
      }
      igi2_frame.atQVertex[0].vR = 1.0;
      igi2_frame.atQVertex[0].vX = (float)(int)&igi2_frame.nXPos[ptNext_low - 6];
      igi2_frame.atQVertex[0].vG = 1.0;
      igi2_frame.atQVertex[0].vB = 1.0;
      igi2_frame.atQVertex[0].vA = 0.0;
      igi2_frame.atQVertex[0].vU = 0.0;
      igi2_frame.atQVertex[0].vY = (float)(int)(igi2_frame.nYPos + 10);
      igi2_frame.atQVertex[0].vV = 0.0;
      igi2_frame.atQVertex[0].vZ = 1.0;
      qmemcpy(&igi2_frame.atQVertex[1], igi2_frame.atQVertex, sizeof(struct QVertex_s));
      igi2_frame.atQVertex[1].vX = igi2_frame.atQVertex[0].vX + 6.0;
      igi2_frame.tContext.bFlags = 0;
      igi2_frame.tContext.isLine = 1;
      igi2_frame.tContext.nDepth = 0;
      igi2_frame.tContext.nStripLength = 2;
      igi2_frame.tContext.atQVertex = igi2_frame.atQVertex;
      QVertex_ptActiveTexture = nullptr;
      QVertex_ptActivePalette = nullptr;
      RenderMode_tActiveRenderMode.apfRenderModeMethod[QVertex_eRegisterQVertexStripMethod](&igi2_frame.tContext);
      v1 = (struct MenuWindow_t *)ptQTask;
    }
  }
  MenuWindow_DrawBorder(v1, 0.5, igi2_frame.vFade, v1->isSelectedByKeyboard);
}

// source: j/0/menusystem/inputbox.c:535  [size]
void __cdecl InputBox_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = InputBox_ptParameterList;
}

// source: j/0/menusystem/inputbox.c:552  [anchor-mhash]
void __cdecl InputBox_InitDataHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptHead; // ecx
  int v2; // edx
  struct QTask_s *v3; // eax
  int v4; // esi
  void (__cdecl *pfHandler)(struct QTask_s *); // eax
  int v6; // edx

  LOBYTE(ptQTask[2].tQTaskChildren.ptMiddle) = 0;
  if ( ptQTask[15].ptPrev && ptQTask[15].tQTaskChildren.ptHead->ptNext && ptQTask[15].tQTaskChildren.ptMiddle )
  {
    InputBox_ptActiveInputBox = (struct InputBox_t *)ptQTask;
    Level_RunLevelExpression((struct LevelExpression_s *)&ptQTask[15].ptPrev, ptQTask);
    InputBox_ptActiveInputBox = nullptr;
  }
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
      v4 = MenuWindow_eInitDataEvent;
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

// source: j/0/menusystem/inputbox.c:579  [size]
void __cdecl InputBox_ChangeDataHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptHead; // ecx
  int v2; // edx
  struct QTask_s *v3; // eax
  int v4; // esi
  void (__cdecl *pfHandler)(struct QTask_s *); // eax
  int v6; // edx

  if ( ptQTask[17].ptPrev && ptQTask[17].tQTaskChildren.ptHead->ptNext && ptQTask[17].tQTaskChildren.ptMiddle )
    Level_RunLevelExpression((struct LevelExpression_s *)&ptQTask[17].ptPrev, ptQTask);
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
      v4 = MenuWindow_eChangeDataEvent;
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

// source: j/0/menusystem/inputbox.c:602  [size]
void __cdecl InputBox_RegisterScriptSymbolsHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { char zName[64]; };
    struct { char igi2_o1[64]; char zTemp[128]; };
    char igi2_extent[192];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)

  if ( !LOBYTE(ptQTask[21].ptPrev) )
  {
    Level_GetUniqueQTaskNameFromTask(igi2_frame.zName, ptQTask);
    sprintf(igi2_frame.zTemp, "%s.zData", igi2_frame.zName);
    Symbol_Register(
      igi2_frame.zTemp,
      (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_String,
      &ptQTask[2].tQTaskChildren.ptMiddle,
      256,
      QSCRIPT_SYMBOLCLASS_VARIABLE,
      QSCRIPT_SYMBOLTYPE_STRING,
      QSCRIPT_SYMBOLLIFESPAN_FINITE);
    LOBYTE(ptQTask[21].ptPrev) = 1;
  }
}

// source: j/0/menusystem/inputbox.c:631  [size]
void __cdecl InputBox_RemoveScriptSymbolsHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { char zName[64]; };
    struct { char igi2_o1[64]; char zTemp[128]; };
    char igi2_extent[192];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)

  if ( LOBYTE(ptQTask[21].ptPrev) )
  {
    Level_GetUniqueQTaskNameFromTask(igi2_frame.zName, ptQTask);
    sprintf(igi2_frame.zTemp, "%s.zData", igi2_frame.zName);
    Symbol_Remove(igi2_frame.zTemp);
    LOBYTE(ptQTask[21].ptPrev) = 0;
  }
}

// source: j/0/menusystem/inputbox.c:662  [anchor-strings]
void __cdecl InputBox_Open()
{
  unsigned __int16 v0; // si
  struct ParameterList_s *v1; // eax
  int v2; // edx

  v0 = QTask_NewQTaskType("InputBox", 864, MenuWindow_eQTaskType, 0, 0);
  InputBox_eQTaskType = v0;
  QTask_LinkQTaskEventHandlerFn(
    v0,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 1, InputBox_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, Screen_eDrawQTaskEvent, InputBox_DrawHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 2, InputBox_DeleteHandler);
  QTask_LinkQTaskEventHandlerFn(v0, 0, InputBox_CreateHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))InputBox_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(v0, ParameterList_eUpdateInternalDataQTaskEvent, InputBox_UpdateInternalDataHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, MenuWindow_eInitDataEvent, InputBox_InitDataHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, MenuWindow_eChangeDataEvent, InputBox_ChangeDataHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(
    v0,
    Level_eRegisterLevelScriptSymbolsEvent,
    InputBox_RegisterScriptSymbolsHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, Level_eRemoveLevelScriptSymbolsEvent, InputBox_RemoveScriptSymbolsHandler);
  v1 = (struct ParameterList_s *)Mem_AllocFn(152, 4);
  v2 = Level_eParameterTypeInt32;
  v1->ptParameterListItem = (struct ParameterListItem_s *)&v1[1];
  v1->nParameters = 0;
  v1->nMaxParameters = 7;
  InputBox_ptParameterList = v1;
  ParameterList_AddParameter(v1, 0x30u, v2, "Width", 7u, nullptr);
  ParameterList_AddParameter(InputBox_ptParameterList, 0x35Cu, Level_eParameterTypeInt32, "String Length", 7u, nullptr);
  ParameterList_AddParameter(
    InputBox_ptParameterList,
    0x25Cu,
    Level_eParameterTypeVarString,
    "Get Data Script",
    7u,
    nullptr);
  ParameterList_AddParameter(
    InputBox_ptParameterList,
    0x2ACu,
    Level_eParameterTypeVarString,
    "Set Data Script",
    7u,
    nullptr);
  ParameterList_AddParameter(
    InputBox_ptParameterList,
    0x2FCu,
    Level_eParameterTypeVarString,
    "On Modify Script",
    7u,
    nullptr);
  ParameterList_AddParameter(InputBox_ptParameterList, 0x34Eu, Level_eParameterTypebool8, "Hide Input", 7u, nullptr);
  ParameterList_AddParameter(InputBox_ptParameterList, 0x34Fu, Level_eParameterTypebool8, "Numeric Input", 7u, nullptr);
}

// source: j/0/menusystem/inputbox.c:705  [size]
void __cdecl InputBox_Close()
{
  int v0; // esi

  if ( InputBox_ptParameterList )
  {
    v0 = *(_DWORD *)((unsigned int)&InputBox_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
  QTask_DeleteQTaskType(InputBox_eQTaskType);
  InputBox_eQTaskType = 512;
}

// source: j/0/menusystem/inputbox.c:726  [anchor-hash]
char *__cdecl InputBox_SetString(char *zString)
{
  int v1; // edx
  char v2; // cl

  v1 = InputBox_ptActiveInputBox->zInputString - zString;
  do
  {
    v2 = *zString;
    zString[v1] = *zString;
    ++zString;
  }
  while ( v2 );
  return zString;
}
