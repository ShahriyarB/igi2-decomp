/* j/0/menusystem/slidebar.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/menusystem/slidebar.c:115  [anchor-mhash]
void __cdecl SlideBar_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  unsigned __int16 v2; // ax
  struct QTask_s *v3; // eax
  struct QTask_s *ptNext; // ecx
  int v5; // edx

  ((void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[0][MenuWindow_eQTaskType].pfHandler)(
    ptQTask,
    pxContext);
  if ( pxContext )
    *(_DWORD *)&ptQTask[1].eQTaskType = pxContext;
  v2 = MenuButton_eQTaskType;
  LOBYTE(ptQTask[2].tQTaskChildren.ptMiddle) = 0;
  *(_DWORD *)&ptQTask[3].eQTaskType = 0;
  ptQTask[4].tQTaskRefList.ptHead = (struct QReference_s *)50;
  LOBYTE(ptQTask[4].tQTaskRefList.ptTail) = 1;
  ptQTask[4].ptNext = QTask_NewFn(nullptr, v2, nullptr);
  v3 = QTask_NewFn(nullptr, MenuButton_eQTaskType, nullptr);
  ptNext = ptQTask[4].ptNext;
  v5 = *(_DWORD *)&ptQTask[1].eQTaskType;
  ptQTask[4].ptPrev = v3;
  *(_DWORD *)&ptNext[1].eQTaskType = v5;
  *(_DWORD *)&ptQTask[4].ptPrev[1].eQTaskType = *(_DWORD *)&ptQTask[1].eQTaskType;
  ptQTask[4].ptPrev[1].ptParent = (struct QTask_s *)1;
  ptQTask[4].ptNext[1].ptParent = (struct QTask_s *)1;
  ptQTask[4].ptPrev[1].tQTaskRefList.ptTail = (struct QReference_s *)1;
  ptQTask[4].ptNext[1].tQTaskRefList.ptTail = (struct QReference_s *)1;
  ptQTask[1].ptNext = (struct QTask_s *)300;
  ptQTask[1].ptPrev = (struct QTask_s *)230;
  ptQTask[1].tQTaskRefList.ptTail = (struct QReference_s *)1;
  ptQTask[1].ptParent = (struct QTask_s *)1;
  ptQTask[6].ptParent = nullptr;
  *(_DWORD *)&ptQTask[6].eQTaskType = 0;
  ptQTask[7].ptNext = nullptr;
  ptQTask[8].tQTaskRefList.ptTail = nullptr;
  ptQTask[8].ptParent = nullptr;
  *(_DWORD *)&ptQTask[8].eQTaskType = 0;
  ptQTask[9].ptNext = nullptr;
  ptQTask[10].tQTaskRefList.ptTail = nullptr;
  ptQTask[10].ptParent = nullptr;
  *(_DWORD *)&ptQTask[10].eQTaskType = 0;
  ptQTask[11].ptNext = nullptr;
  ptQTask[12].tQTaskRefList.ptTail = nullptr;
  ptQTask[12].ptParent = nullptr;
  *(_DWORD *)&ptQTask[12].eQTaskType = 0;
  ptQTask[13].ptNext = nullptr;
  ptQTask[14].tQTaskRefList.ptTail = nullptr;
  ptQTask[14].ptParent = nullptr;
  *(_DWORD *)&ptQTask[14].eQTaskType = 0;
  ptQTask[15].ptNext = nullptr;
  ptQTask[16].tQTaskRefList.ptTail = nullptr;
  ptQTask[4].ptParent = nullptr;
  *(_DWORD *)&ptQTask[4].eQTaskType = 0;
  ptQTask[5].ptNext = nullptr;
  ptQTask[6].tQTaskRefList.ptTail = nullptr;
  BYTE1(ptQTask[4].tQTaskRefList.ptTail) = 0;
  ptQTask[16].ptParent = nullptr;
  ptQTask[4].tQTaskChildren.ptHead = nullptr;
  ptQTask[4].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[17].ptNext = nullptr;
  *(_DWORD *)&ptQTask[16].eQTaskType = 0;
  ptQTask[4].tQTaskChildren.ptTail = (struct QTask_s *)1028443341;
  BYTE2(ptQTask[4].tQTaskRefList.ptTail) = 1;
}

// source: j/0/menusystem/slidebar.c:176  [anchor-mhash]
void __cdecl SlideBar_DeleteHandler(struct QTask_s *ptQTask)
{
  Level_DeinitLevelExpression((struct LevelExpression_s *)&ptQTask[4].ptParent);
  Level_DeinitLevelExpression((struct LevelExpression_s *)&ptQTask[6].ptParent);
  Level_DeinitLevelExpression((struct LevelExpression_s *)&ptQTask[8].ptParent);
  Level_DeinitLevelExpression((struct LevelExpression_s *)&ptQTask[10].ptParent);
  Level_DeinitLevelExpression((struct LevelExpression_s *)&ptQTask[12].ptParent);
  Level_DeinitLevelExpression((struct LevelExpression_s *)&ptQTask[14].ptParent);
  QTask_Delete(ptQTask[4].ptNext);
  QTask_Delete(ptQTask[4].ptPrev);
  ((void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[Level_eRemoveLevelScriptSymbolsEvent][ptQTask->eQTaskType].pfHandler)(ptQTask);
}

// source: j/0/menusystem/slidebar.c:206  [anchor-strings]
void __cdecl SlideBar_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct MenuButton_t *ptArrowButton2; };
    struct { struct MenuButton_t *ptArrowButton2a; };
    struct { struct MenuButton_t *ptArrowButton2b; };
    struct { char igi2_o3[4]; int nHeight; };
    struct { char igi2_o4[4]; int nHeighta; };
    struct { char igi2_o5[8]; char zResourceName[64]; };
    char igi2_extent[72];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *ptNext; // edi
  int p_ptPrev; // ecx
  int v5; // edx
  int v6; // eax
  struct MenuButton_t *ptMiddle; // ecx
  struct MenuButton_t *v8; // edx
  struct MenuButton_t *v9; // ecx
  int v10; // eax
  struct MenuButton_t *ptHead; // ecx
  struct MenuButton_t *nWidth; // edx
  int v13; // ecx

  ptNext = ptQTask[4].ptNext;
  igi2_frame.ptArrowButton2 = (struct MenuButton_t *)ptQTask[4].ptPrev;
  Level_CompileLevelExpression((struct LevelExpression_s *)&ptQTask[6].ptParent, ptQTask);
  Level_CompileLevelExpression((struct LevelExpression_s *)&ptQTask[8].ptParent, ptQTask);
  Level_CompileLevelExpression((struct LevelExpression_s *)&ptQTask[10].ptParent, ptQTask);
  Level_CompileLevelExpression((struct LevelExpression_s *)&ptQTask[12].ptParent, ptQTask);
  Level_CompileLevelExpression((struct LevelExpression_s *)&ptQTask[14].ptParent, ptQTask);
  Level_CompileLevelExpression((struct LevelExpression_s *)&ptQTask[4].ptParent, ptQTask);
  if ( ptQTask[12].ptParent && **(_BYTE **)&ptQTask[12].eQTaskType && ptQTask[13].ptNext )
    *(float *)&ptQTask[4].tQTaskChildren.ptTail = Level_RunLevelExpression(
                                                    (struct LevelExpression_s *)&ptQTask[12].ptParent,
                                                    ptQTask);
  else
    ptQTask[4].tQTaskChildren.ptTail = (struct QTask_s *)1028443341;
  if ( *(_DWORD *)&ptQTask[1].eQTaskType )
  {
    sprintf(igi2_frame.zResourceName, "%s_1.spr", (char *)&ptQTask[2].tQTaskChildren.ptMiddle);
    strcpy((char *)&ptQTask[4].ptNext[2].tQTaskChildren.ptMiddle, igi2_frame.zResourceName);
    sprintf(igi2_frame.zResourceName, "%s_2.spr", (char *)&ptQTask[2].tQTaskChildren.ptMiddle);
    strcpy((char *)&ptQTask[4].ptPrev[2].tQTaskChildren.ptMiddle, igi2_frame.zResourceName);
    sprintf(igi2_frame.zResourceName, "%s_3.spr", (char *)&ptQTask[2].tQTaskChildren.ptMiddle);
    *(_DWORD *)&ptQTask[3].eQTaskType = MenuManager_GetSprite(*(struct QTask_s **)&ptQTask[1].eQTaskType, igi2_frame.zResourceName);
  }
  ((void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[ParameterList_eUpdateInternalDataQTaskEvent][ptQTask[4].ptNext->eQTaskType].pfHandler)(
    ptQTask[4].ptNext,
    pxContext);
  ((void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[ParameterList_eUpdateInternalDataQTaskEvent][ptQTask[4].ptPrev->eQTaskType].pfHandler)(
    ptQTask[4].ptPrev,
    pxContext);
  p_ptPrev = 4;
  v5 = 4;
  if ( LOBYTE(ptQTask[4].tQTaskRefList.ptTail) )
  {
    v5 = (int)&ptQTask[4].tQTaskRefList.ptHead->ptPrev
       + igi2_frame.ptArrowButton2->tMenuWindow.nWidth
       + (unsigned int)ptNext[1].tQTaskChildren.ptHead
       + 2;
    v6 = *(_DWORD *)&ptQTask[3].eQTaskType;
    igi2_frame.nHeight = v5;
    if ( v6 )
    {
      ptMiddle = (struct MenuButton_t *)ptNext[1].tQTaskChildren.ptMiddle;
      v8 = (struct MenuButton_t *)igi2_frame.ptArrowButton2->tMenuWindow.nHeight;
      igi2_frame.ptArrowButton2a = ptMiddle;
      if ( (int)ptMiddle <= (int)v8 )
        igi2_frame.ptArrowButton2a = v8;
      if ( (int)igi2_frame.ptArrowButton2a <= *(__int16 *)(*(_DWORD *)(v6 + 8) + 36 * *(unsigned __int16 *)(v6 + 20) + 14) )
      {
        ptMiddle = (struct MenuButton_t *)*(__int16 *)(*(_DWORD *)(v6 + 8) + 36 * *(unsigned __int16 *)(v6 + 20) + 14);
      }
      else if ( (int)ptMiddle <= (int)v8 )
      {
        v9 = v8;
        v5 = igi2_frame.nHeight;
        p_ptPrev = (int)&v9->tMenuWindow.tQTask.ptPrev;
        goto LABEL_25;
      }
      v5 = igi2_frame.nHeight;
      p_ptPrev = (int)&ptMiddle->tMenuWindow.tQTask.ptPrev;
    }
  }
  else
  {
    p_ptPrev = (int)&ptQTask[4].tQTaskRefList.ptHead->ptPrev
             + igi2_frame.ptArrowButton2->tMenuWindow.nHeight
             + (unsigned int)ptNext[1].tQTaskChildren.ptMiddle
             + 2;
    v10 = *(_DWORD *)&ptQTask[3].eQTaskType;
    igi2_frame.nHeighta = p_ptPrev;
    if ( v10 )
    {
      ptHead = (struct MenuButton_t *)ptNext[1].tQTaskChildren.ptHead;
      nWidth = (struct MenuButton_t *)igi2_frame.ptArrowButton2->tMenuWindow.nWidth;
      igi2_frame.ptArrowButton2b = ptHead;
      if ( (int)ptHead <= (int)nWidth )
        igi2_frame.ptArrowButton2b = nWidth;
      if ( (int)igi2_frame.ptArrowButton2b <= *(__int16 *)(*(_DWORD *)(v10 + 8) + 36 * *(unsigned __int16 *)(v10 + 20) + 12) )
      {
        ptHead = (struct MenuButton_t *)*(__int16 *)(*(_DWORD *)(v10 + 8) + 36 * *(unsigned __int16 *)(v10 + 20) + 12);
      }
      else if ( (int)ptHead <= (int)nWidth )
      {
        ptHead = nWidth;
      }
      v5 = (int)&ptHead->tMenuWindow.tQTask.ptPrev;
      p_ptPrev = igi2_frame.nHeighta;
    }
  }
LABEL_25:
  ptQTask[1].tQTaskChildren.ptMiddle = (struct QTask_s *)p_ptPrev;
  v13 = 511 * ParameterList_eUpdateInternalDataQTaskEvent;
  ptQTask[1].tQTaskChildren.ptHead = (struct QTask_s *)v5;
  ((void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[0][MenuWindow_eQTaskType + v13].pfHandler)(
    ptQTask,
    pxContext);
}

// source: j/0/menusystem/slidebar.c:311  [size]
void __cdecl SlideBar_RunHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { char isHorizontal; };
    struct { char igi2_o1[1]; float vValue; };
    struct { char igi2_o2[5]; int isModified; };
    struct { char igi2_o3[9]; float vCarretSpeed; };
    struct { char igi2_o4[9]; char *vCarretSpeeda; };
    struct { char igi2_o5[13]; struct MenuButton_t *ptArrowButton2; };
    struct { char igi2_o6[17]; struct MenuButton_t *ptArrowButton1; };
    struct { char igi2_o7[21]; __int64 ptInputContext; };
    char igi2_extent[29];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct MenuButton_t *ptNext; // ebx
  bool v2; // zf
  struct QTask_s *ptParent; // eax
  char isPressed; // al
  struct QTask_s *ptHead; // esi
  int v6; // ebx
  BOOL v7; // ecx
  struct QReference_s *v8; // eax
  int v9; // eax
  struct QTask_s *v10; // eax
  int v11; // eax
  double v12; // st7
  int v13; // eax
  char *v14; // ecx
  char *v15; // ebx
  int v16; // edx
  int v17; // eax
  int v18; // eax
  double v19; // st7
  struct QTask_s *v20; // esi
  double v21; // st7
  double v22; // st7
  struct QReference_s *v23; // eax

  ptNext = (struct MenuButton_t *)ptQTask[4].ptNext;
  igi2_frame.vValue = *(double *)&ptQTask[4].tQTaskChildren.ptHead;
  igi2_frame.ptArrowButton2 = (struct MenuButton_t *)ptQTask[4].ptPrev;
  LODWORD(igi2_frame.ptInputContext) = *(_DWORD *)&ptQTask[1].eQTaskType + 10020;
  v2 = ptQTask[4].ptParent == nullptr;
  igi2_frame.ptArrowButton1 = ptNext;
  igi2_frame.isModified = 0;
  if ( !v2 && **(_BYTE **)&ptQTask[4].eQTaskType && ptQTask[5].ptNext )
    BYTE2(ptQTask[4].tQTaskRefList.ptTail) = Expression_EvalInt((struct QExpression_s *)ptQTask[5].ptNext) != 0;
  ptParent = ptQTask[16].ptParent;
  if ( ptParent )
    igi2_frame.vCarretSpeed = 1.0 / (double)(int)(&ptParent[-1].isInMemPool + 1);
  else
    igi2_frame.vCarretSpeed = *(float *)&ptQTask[4].tQTaskChildren.ptTail;
  if ( BYTE2(ptQTask[4].tQTaskRefList.ptTail) )
  {
    ((void (__cdecl *)(struct MenuButton_t *))QTask_aatQTaskFinalEvent[1][ptNext->tMenuWindow.tQTask.eQTaskType].pfHandler)(ptNext);
    ((void (__cdecl *)(struct MenuButton_t *))QTask_aatQTaskFinalEvent[1][igi2_frame.ptArrowButton2->tMenuWindow.tQTask.eQTaskType].pfHandler)(igi2_frame.ptArrowButton2);
  }
  else
  {
    ptQTask[2].tQTaskChildren.ptHead = nullptr;
  }
  isPressed = ptNext->tMenuWindow.isPressed;
  ptHead = ptQTask[2].tQTaskChildren.ptHead;
  if ( isPressed || igi2_frame.ptArrowButton2->tMenuWindow.isPressed )
  {
    if ( *(_DWORD *)&ptQTask[16].eQTaskType )
    {
      if ( !ptQTask[17].ptNext )
      {
        ptQTask[17].ptNext = (struct QTask_s *)4;
        ptHead = (struct QTask_s *)((ptNext->tMenuWindow.isPressed != 0) - 2);
      }
    }
    else
    {
      v6 = *(_DWORD *)&ptQTask[1].eQTaskType;
      v7 = isPressed != 0;
      ptQTask[17].ptNext = (struct QTask_s *)30;
      v8 = *(struct QReference_s **)(v6 + 10236);
      ptHead = (struct QTask_s *)(v7 - 2);
      if ( v8 )
      {
        QReference_Delete(v8, &QTask_tQTaskRefPool);
        *(_DWORD *)(v6 + 10236) = 0;
      }
      *(_DWORD *)(v6 + 10236) = QTask_NewQTaskRef(ptQTask);
    }
    --*(int *)&ptQTask[17].ptNext;
    *(_DWORD *)&ptQTask[16].eQTaskType = 1;
  }
  else
  {
    *(_DWORD *)&ptQTask[16].eQTaskType = 0;
  }
  v9 = *(_DWORD *)(*(_DWORD *)&ptQTask[1].eQTaskType + 10236);
  if ( v9 )
    v10 = *(struct QTask_s **)(v9 + 8);
  else
    v10 = nullptr;
  if ( v10 == ptQTask )
  {
    v11 = *(_DWORD *)(igi2_frame.ptInputContext + 8);
    if ( v11 < 0 )
    {
LABEL_28:
      if ( *(double *)&ptQTask[4].tQTaskChildren.ptHead <= 0.0 )
        goto LABEL_45;
      SoundSys_PlaySimpleSoundFn((char *)&g_zFileName.aptSelectableItems[22], 0, nullptr);
      v12 = igi2_frame.vValue - igi2_frame.vCarretSpeed;
      igi2_frame.isModified = 1;
      goto LABEL_44;
    }
    if ( v11 > 0 )
      goto LABEL_31;
  }
  if ( ptHead == (struct QTask_s *)-1 )
    goto LABEL_28;
  if ( ptHead == (struct QTask_s *)-2 )
  {
LABEL_31:
    if ( *(double *)&ptQTask[4].tQTaskChildren.ptHead >= 1.0 )
      goto LABEL_45;
    igi2_frame.isModified = 1;
    SoundSys_PlaySimpleSoundFn((char *)&g_zFileName.aptSelectableItems[22], 0, nullptr);
    v12 = igi2_frame.vCarretSpeed + igi2_frame.vValue;
    goto LABEL_44;
  }
  v13 = *(_DWORD *)&ptQTask[3].eQTaskType;
  if ( v13 )
  {
    v14 = (char *)&ptQTask[1].ptNext->ptNext + 2;
    v15 = (char *)&ptQTask[1].ptPrev->ptNext + 2;
    igi2_frame.isHorizontal = (char)ptQTask[4].tQTaskRefList.ptTail;
    igi2_frame.vCarretSpeeda = v14;
    if ( igi2_frame.isHorizontal )
    {
      v14 += igi2_frame.ptArrowButton1->tMenuWindow.nWidth + 1;
      v16 = (int)ptQTask[4].tQTaskRefList.ptHead;
      igi2_frame.vCarretSpeeda = v14;
      v17 = *(__int16 *)(*(_DWORD *)(v13 + 8) + 36 * *(unsigned __int16 *)(v13 + 20) + 14);
    }
    else
    {
      v15 += igi2_frame.ptArrowButton1->tMenuWindow.nHeight + 1;
      v16 = *(__int16 *)(*(_DWORD *)(v13 + 8) + 36 * *(unsigned __int16 *)(v13 + 20) + 12);
      v17 = (int)ptQTask[4].tQTaskRefList.ptHead;
    }
    if ( BYTE2(ptQTask[4].tQTaskRefList.ptTail) )
      MenuWindow_HitTest(
        (struct MenuWindow_t *)ptQTask,
        (int)v14,
        (int)v15,
        v16,
        v17,
        (int *)&igi2_frame.ptInputContext,
        (int *)&igi2_frame.ptArrowButton1);
    if ( BYTE2(ptQTask[2].ptNext) )
    {
      MenuManager_SetCaptureMouseWheelQTask(*(struct QTask_s **)&ptQTask[1].eQTaskType, ptQTask);
      v18 = *(_DWORD *)&ptQTask[3].eQTaskType;
      if ( igi2_frame.isHorizontal )
      {
        LODWORD(igi2_frame.ptInputContext) = igi2_frame.ptInputContext - (_DWORD)igi2_frame.vCarretSpeeda;
        v19 = (double)(int)igi2_frame.ptInputContext;
        LODWORD(igi2_frame.ptInputContext) = (char *)ptQTask[4].tQTaskRefList.ptHead
                                - *(__int16 *)(*(_DWORD *)(v18 + 8) + 36 * *(unsigned __int16 *)(v18 + 20) + 12);
        v12 = v19 / (double)(int)igi2_frame.ptInputContext;
      }
      else
      {
        LODWORD(igi2_frame.ptInputContext) = (char *)igi2_frame.ptArrowButton1 - v15;
        LODWORD(igi2_frame.ptInputContext) = (char *)ptQTask[4].tQTaskRefList.ptHead
                                - *(__int16 *)(*(_DWORD *)(v18 + 8) + 36 * *(unsigned __int16 *)(v18 + 20) + 14);
        v12 = (double)((char *)igi2_frame.ptArrowButton1 - v15) / (double)(int)igi2_frame.ptInputContext;
      }
      igi2_frame.isModified = 1;
LABEL_44:
      igi2_frame.vValue = v12;
    }
  }
LABEL_45:
  v20 = ptQTask[16].ptParent;
  if ( v20 )
  {
    LODWORD(igi2_frame.ptInputContext) = (char *)v20 - 1;
    v21 = floor((double)(int)(&v20[-1].isInMemPool + 1) * igi2_frame.vValue + 0.5);
    LODWORD(igi2_frame.ptInputContext) = (char *)v20 - 1;
    igi2_frame.vValue = v21 / (double)(int)(&v20[-1].isInMemPool + 1);
  }
  if ( igi2_frame.vValue >= 0.0 )
  {
    if ( igi2_frame.vValue <= 1.0 )
      v22 = igi2_frame.vValue;
    else
      v22 = 1.0;
  }
  else
  {
    v22 = 0.0;
  }
  *(double *)&ptQTask[4].tQTaskChildren.ptHead = v22;
  if ( v20 )
  {
    igi2_frame.ptInputContext = (__int64)((double)(int)(&v20[-1].isInMemPool + 1) * v22 + 0.5);
    v23 = (struct QReference_s *)igi2_frame.ptInputContext;
  }
  else
  {
    v23 = nullptr;
  }
  ptQTask[4].tQTaskRefList.ptMiddle = v23;
  if ( igi2_frame.isModified && ptQTask[10].ptParent && **(_BYTE **)&ptQTask[10].eQTaskType && ptQTask[11].ptNext )
  {
    Level_RunLevelExpression((struct LevelExpression_s *)&ptQTask[10].ptParent, ptQTask);
    *(_BYTE *)(*(_DWORD *)&ptQTask[1].eQTaskType + 9755) = 1;
  }
  ((void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[1][MenuWindow_eQTaskType].pfHandler)(ptQTask);
}

// source: j/0/menusystem/slidebar.c:503  [anchor-mhash]
void __cdecl SlideBar_DrawHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptNext; // ebx
  double v3; // st7
  struct QTask_s *v4; // ebp
  struct QTask_s *v5; // edi
  int v6; // eax
  struct QTask_s *ptMiddle; // edx
  struct QSprite_s *v8; // ecx
  struct QAnimframe_s *atQAnimframe; // ebx
  float ptQSprite; // [esp+0h] [ebp-48h]
  float vX; // [esp+4h] [ebp-44h]
  float vAlpha; // [esp+1Ch] [ebp-2Ch]
  float vFade; // [esp+34h] [ebp-14h]
  struct MenuButton_t *ptArrowButton2; // [esp+38h] [ebp-10h]
  struct MenuButton_t *ptArrowButton2a; // [esp+38h] [ebp-10h]
  int vColourScalea; // [esp+3Ch] [ebp-Ch]
  float vColourScale; // [esp+3Ch] [ebp-Ch]
  char ptQTaska = *(char *)&ptQTask; // [esp+4Ch] [ebp+4h] ARGSLOT
  struct QTask_s *ptQTaskb = *(struct QTask_s * *)&ptQTask; // [esp+4Ch] [ebp+4h] ARGSLOT

  ptNext = ptQTask[4].ptNext;
  ptArrowButton2 = (struct MenuButton_t *)ptQTask[4].ptPrev;
  vColourScalea = *(_DWORD *)(*(_DWORD *)&ptQTask[1].eQTaskType + 356) - 8;
  ptQTaska = (char)ptQTask[4].tQTaskRefList.ptTail;
  v3 = (double)vColourScalea * 0.125;
  if ( v3 <= 0.0 )
    vFade = 0.0;
  else
    vFade = v3;
  vColourScale = 1.0;
  if ( !BYTE2(ptQTask[4].tQTaskRefList.ptTail) )
    vColourScale = 0.5;
  v4 = (struct QTask_s *)((char *)&ptQTask[1].ptNext->ptNext + 2);
  v5 = (struct QTask_s *)((char *)&ptQTask[1].ptPrev->ptNext + 2);
  v6 = MenuWindow_eQTaskType + 511 * Screen_eDrawQTaskEvent;
  ptNext[1].ptNext = v4;
  ptNext[1].ptPrev = v5;
  ((void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[0][v6].pfHandler)(ptQTask);
  if ( ptQTaska )
  {
    v4 = (struct QTask_s *)((char *)v4 + (unsigned int)&ptNext[1].tQTaskChildren.ptHead->ptNext + 1);
    ptArrowButton2->tMenuWindow.nXPos = (int)&ptQTask[4].tQTaskRefList.ptHead->ptNext + (unsigned int)v4 + 1;
    ptArrowButton2->tMenuWindow.nYPos = (int)v5;
  }
  else
  {
    ptMiddle = ptNext[1].tQTaskChildren.ptMiddle;
    ptArrowButton2->tMenuWindow.nXPos = (int)v4;
    v5 = (struct QTask_s *)((char *)&ptMiddle->ptNext + (_DWORD)v5 + 1);
    ptArrowButton2->tMenuWindow.nYPos = (int)&ptQTask[4].tQTaskRefList.ptHead->ptNext + (unsigned int)v5 + 1;
  }
  ((void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[Screen_eDrawQTaskEvent][ptQTask[4].ptNext->eQTaskType].pfHandler)(ptQTask[4].ptNext);
  ((void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[Screen_eDrawQTaskEvent][ptQTask[4].ptPrev->eQTaskType].pfHandler)(ptQTask[4].ptPrev);
  v8 = *(struct QSprite_s **)&ptQTask[3].eQTaskType;
  if ( v8 )
  {
    atQAnimframe = v8->atQAnimframe;
    if ( ptQTaska )
    {
      ptQTaskb = nullptr;
      ptArrowButton2a = (struct MenuButton_t *)(__int64)((double)((unsigned int)ptQTask[4].tQTaskRefList.ptHead
                                                                - atQAnimframe[v8->nQAnimframes].nWidth)
                                                       * *(double *)&ptQTask[4].tQTaskChildren.ptHead);
    }
    else
    {
      ptArrowButton2a = nullptr;
      ptQTaskb = (struct QTask_s *)(__int64)((double)((unsigned int)ptQTask[4].tQTaskRefList.ptHead
                                                    - atQAnimframe[v8->nQAnimframes].nHeight)
                                           * *(double *)&ptQTask[4].tQTaskChildren.ptHead);
    }
    vX = (double)((int)&v5[-6] + (Display_tActiveMode.nHeight >> 1)) + (double)(int)ptQTaskb;
    ptQSprite = (double)((int)&v4[-8] + (Display_tActiveMode.nWidth >> 1)) + (double)(int)ptArrowButton2a;
    QSprite_RegisterAZ(v8, ptQSprite, vX, 128.0, 128.0, 128.0, vFade, 1.0, 0, 0x80000u, 0);
  }
  vAlpha = vColourScale * vFade;
  MenuWindow_DrawBorder((struct MenuWindow_t *)ptQTask, 0.5, vAlpha, SBYTE1(ptQTask[2].ptPrev));
}

// source: j/0/menusystem/slidebar.c:604  [size]
void __cdecl SlideBar_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = SlideBar_ptParameterList;
}

// source: j/0/menusystem/slidebar.c:621  [anchor-mhash]
void __cdecl SlideBar_InitDataHandler(struct QTask_s *ptQTask)
{
  struct LevelExpression_s *p_ptParent; // eax
  struct QTask_s *ptHead; // ecx
  int v4; // edx
  struct QTask_s *v5; // eax
  int v6; // esi
  void (__cdecl *pfHandler)(struct QTask_s *); // eax
  int v8; // edx
  struct QTask_s *ptQTaska = *(struct QTask_s * *)&ptQTask; // [esp+10h] [ebp+4h] ARGSLOT

  if ( ptQTask[14].ptParent && **(_BYTE **)&ptQTask[14].eQTaskType && ptQTask[15].ptNext )
    ptQTask[16].ptParent = (struct QTask_s *)(__int64)Level_RunLevelExpression(
                                                        (struct LevelExpression_s *)&ptQTask[14].ptParent,
                                                        ptQTask);
  p_ptParent = (struct LevelExpression_s *)&ptQTask[6].ptParent;
  if ( ptQTask[6].ptParent && **(_BYTE **)&ptQTask[6].eQTaskType && ptQTask[7].ptNext )
  {
    if ( ptQTask[16].ptParent )
    {
      ptQTaska = (struct QTask_s *)(__int64)Level_RunLevelExpression(p_ptParent, ptQTask);
      if ( ptQTask[16].ptParent )
        *(double *)&ptQTask[4].tQTaskChildren.ptHead = ((double)(int)ptQTaska + 0.5) / (double)(int)ptQTask[16].ptParent;
    }
    else
    {
      *(double *)&ptQTask[4].tQTaskChildren.ptHead = Level_RunLevelExpression(p_ptParent, ptQTask);
    }
  }
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
      v6 = MenuWindow_eInitDataEvent;
      QTask_atProtectedQTaskStack[v4].ptQTask = v5;
      pfHandler = (void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[v6][ptHead->eQTaskType].pfHandler;
      v8 = v4 + 1;
      QTask_nProtectedQTaskStackOffset = v8;
      if ( pfHandler )
      {
        pfHandler(ptHead);
        v8 = QTask_nProtectedQTaskStackOffset;
      }
      ptHead = (struct QTask_s *)dword_849C7DC[v8];
      v4 = v8 - 1;
      QTask_nProtectedQTaskStackOffset = v4;
    }
    while ( ptHead );
  }
}

// source: j/0/menusystem/slidebar.c:661  [size]
void __cdecl SlideBar_ChangeDataHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptHead; // ecx
  int v2; // edx
  struct QTask_s *v3; // eax
  int v4; // esi
  void (__cdecl *pfHandler)(struct QTask_s *); // eax
  int v6; // edx

  if ( ptQTask[8].ptParent && **(_BYTE **)&ptQTask[8].eQTaskType && ptQTask[9].ptNext )
    Level_RunLevelExpression((struct LevelExpression_s *)&ptQTask[8].ptParent, ptQTask);
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

// source: j/0/menusystem/slidebar.c:684  [size]
void __cdecl SlideBar_RegisterScriptSymbolsHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { char zName[64]; };
    struct { char igi2_o1[64]; char zTemp[128]; };
    char igi2_extent[192];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)

  if ( !BYTE1(ptQTask[4].tQTaskRefList.ptTail) )
  {
    BYTE1(ptQTask[4].tQTaskRefList.ptTail) = 1;
    Level_GetUniqueQTaskNameFromTask(igi2_frame.zName, ptQTask);
    sprintf(igi2_frame.zTemp, "%s.vValue", igi2_frame.zName);
    Symbol_Register(
      igi2_frame.zTemp,
      Script_Float,
      &ptQTask[4].tQTaskChildren,
      8,
      QSCRIPT_SYMBOLCLASS_VARIABLE,
      QSCRIPT_SYMBOLTYPE_FLOAT,
      QSCRIPT_SYMBOLLIFESPAN_FINITE);
    sprintf(igi2_frame.zTemp, "%s.nValue", igi2_frame.zName);
    Symbol_Register(
      igi2_frame.zTemp,
      (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_Int,
      &ptQTask[4].tQTaskRefList.ptMiddle,
      4,
      QSCRIPT_SYMBOLCLASS_VARIABLE,
      QSCRIPT_SYMBOLTYPE_INT,
      QSCRIPT_SYMBOLLIFESPAN_FINITE);
  }
}

// source: j/0/menusystem/slidebar.c:716  [size]
void __cdecl SlideBar_RemoveScriptSymbolsHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { char zName[64]; };
    struct { char igi2_o1[64]; char zTemp[128]; };
    char igi2_extent[192];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)

  if ( BYTE1(ptQTask[4].tQTaskRefList.ptTail) )
  {
    BYTE1(ptQTask[4].tQTaskRefList.ptTail) = 0;
    Level_GetUniqueQTaskNameFromTask(igi2_frame.zName, ptQTask);
    sprintf(igi2_frame.zTemp, "%s.vValue", igi2_frame.zName);
    Symbol_Remove(igi2_frame.zTemp);
    sprintf(igi2_frame.zTemp, "%s.nValue", igi2_frame.zName);
    Symbol_Remove(igi2_frame.zTemp);
  }
}

// source: j/0/menusystem/slidebar.c:751  [anchor-hash]
struct MenuWindow_t *__cdecl SlideBar_New(
        struct QTask_s *ptParentQTask,
        struct QTask_s *ptMenuManager)
{
  struct MenuWindow_t *result; // eax

  result = (struct MenuWindow_t *)QTask_NewFn(ptParentQTask, SlideBar_eQTaskType, ptMenuManager);
  strcpy((char *)&result[1], "slidevert");
  LOBYTE(result[2].tQTask.ptPrev) = 0;
  result[1].nKeyPress = 50;
  result[7].tQTask.tQTaskRefList.ptTail = (struct QReference_s *)3;
  return result;
}

// source: j/0/menusystem/slidebar.c:776  [size]
void __cdecl SlideBar_Delete(struct MenuWindow_t *ptQTask)
{
  QTask_Delete(&ptQTask->tQTask);
}

// source: j/0/menusystem/slidebar.c:790  [anchor-mhash]
int __cdecl SlideBar_SetProperties(
        struct MenuWindow_t *ptQTask,
        int nX,
        int nY,
        int nWidth,
        int nHeight,
        int nSteps)
{
  enum MenuWindowAlignmentMode_e eVertAlignmentMode; // edx

  ptQTask->nXPos = nX;
  ptQTask->nYPos = nY;
  eVertAlignmentMode = ptQTask[1].eVertAlignmentMode;
  ptQTask->nHeight = nHeight;
  ptQTask[1].nKeyPress = nHeight
                       - *(_DWORD *)(eVertAlignmentMode + 52)
                       - *(_DWORD *)(ptQTask[1].eHorAlignmentMode + 52)
                       - 6;
  ptQTask[7].tQTask.tQTaskRefList.ptTail = (struct QReference_s *)nSteps;
  return nSteps;
}

// source: j/0/menusystem/slidebar.c:814  [anchor-mhash]
int __cdecl SlideBar_GetIntValue(struct MenuWindow_t *ptQTask)
{
  struct QReference_s *ptTail; // eax

  ptTail = ptQTask[7].tQTask.tQTaskRefList.ptTail;
  if ( ptTail )
    return (__int64)((double)((int)&ptTail[-1].pxObject + 3) * *(double *)&ptQTask[1].ptMenuManager + 0.5);
  else
    return 0;
}

// source: j/0/menusystem/slidebar.c:831  [anchor-callee]
void __cdecl SlideBar_SetIntValue(struct MenuWindow_t *ptQTask, int nValue)
{
  if ( ptQTask[7].tQTask.tQTaskRefList.ptTail )
    *(double *)&ptQTask[1].ptMenuManager = ((double)nValue + 0.5) / (double)(int)ptQTask[7].tQTask.tQTaskRefList.ptTail;
}

// source: j/0/menusystem/slidebar.c:850  [size]
unsigned __int16 __cdecl SlideBar_GetQTaskType()
{
  return SlideBar_eQTaskType;
}

// source: j/0/menusystem/slidebar.c:863  [anchor-hash]
void __cdecl SlideBar_Open()
{
  unsigned __int16 v0; // si
  struct ParameterList_s *v1; // eax
  int v2; // edx

  v0 = QTask_NewQTaskType("SlideBar", 688, MenuWindow_eQTaskType, 0, 0);
  SlideBar_eQTaskType = v0;
  QTask_LinkQTaskEventHandlerFn(
    v0,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 1, SlideBar_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, Screen_eDrawQTaskEvent, SlideBar_DrawHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 2, SlideBar_DeleteHandler);
  QTask_LinkQTaskEventHandlerFn(v0, 0, SlideBar_CreateHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))SlideBar_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(v0, ParameterList_eUpdateInternalDataQTaskEvent, SlideBar_UpdateInternalDataHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, MenuWindow_eInitDataEvent, SlideBar_InitDataHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, MenuWindow_eChangeDataEvent, SlideBar_ChangeDataHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(
    v0,
    Level_eRegisterLevelScriptSymbolsEvent,
    SlideBar_RegisterScriptSymbolsHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, Level_eRemoveLevelScriptSymbolsEvent, SlideBar_RemoveScriptSymbolsHandler);
  v1 = (struct ParameterList_s *)Mem_AllocFn(192, 4);
  v2 = Level_eParameterTypeString32;
  v1->ptParameterListItem = (struct ParameterListItem_s *)&v1[1];
  v1->nParameters = 0;
  v1->nMaxParameters = 9;
  SlideBar_ptParameterList = v1;
  ParameterList_AddParameter(v1, 0x5Cu, v2, "Sprite Resource", 7u, nullptr);
  ParameterList_AddParameter(SlideBar_ptParameterList, 0xBCu, Level_eParameterTypebool8, "Horizontal", 7u, nullptr);
  ParameterList_AddParameter(SlideBar_ptParameterList, 0xB4u, Level_eParameterTypeInt32, "Size", 7u, nullptr);
  ParameterList_AddParameter(
    SlideBar_ptParameterList,
    0x110u,
    Level_eParameterTypeVarString,
    "Get Data Script",
    7u,
    nullptr);
  ParameterList_AddParameter(
    SlideBar_ptParameterList,
    0x160u,
    Level_eParameterTypeVarString,
    "Set Data Script",
    7u,
    nullptr);
  ParameterList_AddParameter(
    SlideBar_ptParameterList,
    0x1B0u,
    Level_eParameterTypeVarString,
    "Modify Data Script",
    7u,
    nullptr);
  ParameterList_AddParameter(
    SlideBar_ptParameterList,
    0x200u,
    Level_eParameterTypeVarString,
    "Carret Speed",
    7u,
    nullptr);
  ParameterList_AddParameter(
    SlideBar_ptParameterList,
    0x250u,
    Level_eParameterTypeVarString,
    "Set Num Options",
    7u,
    nullptr);
  ParameterList_AddParameter(
    SlideBar_ptParameterList,
    0xC0u,
    Level_eParameterTypeVarString,
    "isEnabled Expression",
    7u,
    nullptr);
}

// source: j/0/menusystem/slidebar.c:908  [size]
void __cdecl SlideBar_Close()
{
  int v0; // esi

  if ( SlideBar_ptParameterList )
  {
    v0 = *(_DWORD *)((unsigned int)&SlideBar_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
  QTask_DeleteQTaskType(SlideBar_eQTaskType);
  SlideBar_eQTaskType = 512;
}
