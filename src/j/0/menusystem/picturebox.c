/* j/0/menusystem/picturebox.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/menusystem/picturebox.c:151  [anchor-mhash]
void __cdecl PictureBox_DeleteHandler(struct QTask_s *ptQTask)
{
  Level_DeinitLevelExpression((struct LevelExpression_s *)&ptQTask[60].tQTaskRefList.ptMiddle);
  Level_DeinitLevelExpression((struct LevelExpression_s *)&ptQTask[62].tQTaskRefList.ptMiddle);
  Level_DeinitLevelExpression((struct LevelExpression_s *)&ptQTask[64].tQTaskRefList.ptMiddle);
  Level_DeinitLevelExpression((struct LevelExpression_s *)&ptQTask[66].tQTaskRefList.ptMiddle);
}

// source: j/0/menusystem/picturebox.c:171  [anchor-mhash]
void __cdecl PictureBox_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  Level_CompileLevelExpression((struct LevelExpression_s *)&ptQTask[60].tQTaskRefList.ptMiddle, ptQTask);
  Level_CompileLevelExpression((struct LevelExpression_s *)&ptQTask[62].tQTaskRefList.ptMiddle, ptQTask);
  Level_CompileLevelExpression((struct LevelExpression_s *)&ptQTask[64].tQTaskRefList.ptMiddle, ptQTask);
  Level_CompileLevelExpression((struct LevelExpression_s *)&ptQTask[66].tQTaskRefList.ptMiddle, ptQTask);
  ((void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[ParameterList_eUpdateInternalDataQTaskEvent][MenuWindow_eQTaskType].pfHandler)(
    ptQTask,
    pxContext);
}

// source: j/0/menusystem/picturebox.c:210  [size]
void __cdecl PictureBox_RunHandler(struct QTask_s *ptQTask)
{
  struct LevelExpression_s *p_ptMiddle; // ebx
  bool v2; // sf
  char *v3; // ecx
  struct QTask_s *ptNext; // ecx
  int v5; // eax
  unsigned __int16 *p_eQTaskType; // ecx
  struct QReference_s *ptMiddle; // ecx
  __int64 v8; // [esp+10h] [ebp-8h]

  p_ptMiddle = (struct LevelExpression_s *)&ptQTask[60].tQTaskRefList.ptMiddle;
  if ( ptQTask[60].tQTaskRefList.ptMiddle )
  {
    v2 = *(int *)&ptQTask[59].eQTaskType < 0;
    LOBYTE(ptQTask[2].ptPrev) = 1;
    if ( !v2 )
    {
      MenuWindow_HitTest(
        (struct MenuWindow_t *)ptQTask,
        (int)ptQTask[1].ptNext,
        (int)ptQTask[1].ptPrev,
        (int)ptQTask[1].tQTaskChildren.ptHead,
        (int)ptQTask[1].tQTaskChildren.ptMiddle,
        nullptr,
        nullptr);
      if ( BYTE1(ptQTask[2].ptNext) )
        MenuManager_SetSelectedWindow(*(struct QTask_s **)&ptQTask[1].eQTaskType, ptQTask);
      if ( HIBYTE(ptQTask[2].ptNext)
        || ptQTask[2].tQTaskChildren.ptHead == (struct QTask_s *)-7
        || ptQTask[60].tQTaskRefList.ptHead )
      {
        ptQTask[60].tQTaskRefList.ptHead = nullptr;
        if ( p_ptMiddle->zExpression )
        {
          if ( ptQTask[60].tQTaskRefList.ptTail->ptNext && ptQTask[60].ptParent )
          {
            Level_RunLevelExpression(p_ptMiddle, ptQTask);
            v3 = (char *)&ptQTask[68].tQTaskRefList.ptMiddle;
            if ( !LOBYTE(ptQTask[68].tQTaskRefList.ptMiddle) )
              v3 = "menu_sel";
            SoundSys_PlaySimpleSoundFn(v3, 0, nullptr);
          }
        }
      }
    }
  }
  ptQTask[2].tQTaskChildren.ptHead = nullptr;
  if ( ptQTask[64].tQTaskRefList.ptMiddle )
  {
    if ( ptQTask[64].tQTaskRefList.ptTail->ptNext )
    {
      if ( ptQTask[64].ptParent )
      {
        v8 = (__int64)Level_RunLevelExpression((struct LevelExpression_s *)&ptQTask[64].tQTaskRefList.ptMiddle, ptQTask);
        ptNext = ptQTask[60].ptNext;
        v5 = 0;
        *(_DWORD *)&ptQTask[59].eQTaskType = -1;
        if ( (int)ptNext > 0 )
        {
          p_eQTaskType = &ptQTask[3].eQTaskType;
          while ( (_DWORD)v8 != *(_DWORD *)p_eQTaskType )
          {
            ++v5;
            p_eQTaskType += 36;
            if ( v5 >= (int)ptQTask[60].ptNext )
              goto LABEL_23;
          }
          *(_DWORD *)&ptQTask[59].eQTaskType = v5;
        }
      }
    }
  }
LABEL_23:
  ptMiddle = ptQTask[66].tQTaskRefList.ptMiddle;
  PictureBox_ptActivePictureBox = (struct PictureBox_s *)ptQTask;
  if ( ptMiddle && ptQTask[66].tQTaskRefList.ptTail->ptNext && ptQTask[66].ptParent )
    Level_RunLevelExpression((struct LevelExpression_s *)&ptQTask[66].tQTaskRefList.ptMiddle, ptQTask);
  PictureBox_ptActivePictureBox = nullptr;
}

// source: j/0/menusystem/picturebox.c:304  [anchor-mhash]
void __cdecl PictureBox_DrawHandler(struct QTask_s *ptQTask)
{
  double v2; // st7
  struct QSprite_s *v3; // ecx
  char *v4; // edx
  float vY4; // [esp+0h] [ebp-38h]
  float vR1; // [esp+4h] [ebp-34h]
  float vG1; // [esp+8h] [ebp-30h]
  float vB1; // [esp+Ch] [ebp-2Ch]
  float nY1; // [esp+28h] [ebp-10h]
  float nX1; // [esp+2Ch] [ebp-Ch]
  char *nX0; // [esp+30h] [ebp-8h]
  float nX0a; // [esp+30h] [ebp-8h]
  float nY0; // [esp+34h] [ebp-4h]
  float ptQTaska = *(float *)&ptQTask; // [esp+3Ch] [ebp+4h] ARGSLOT

  v2 = (double)(*(_DWORD *)(*(_DWORD *)&ptQTask[1].eQTaskType + 356) - 8) * 0.125;
  if ( v2 <= 0.0 )
    ptQTaska = 0.0;
  else
    ptQTaska = v2;
  ((void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[Screen_eDrawQTaskEvent][MenuWindow_eQTaskType].pfHandler)(ptQTask);
  if ( ptQTask[60].ptNext )
  {
    v3 = *((struct QSprite_s **)&ptQTask[4].ptNext + 18 * *(_DWORD *)&ptQTask[59].eQTaskType);
    if ( v3 )
    {
      v4 = (char *)&ptQTask[1].ptPrev[-5] + (Display_tActiveMode.nHeight >> 1) - 38;
      nX0 = (char *)&ptQTask[1].ptNext[-7] + (Display_tActiveMode.nWidth >> 1) - 38;
      nY1 = (float)(int)((int)ptQTask[1].tQTaskChildren.ptMiddle + (unsigned int)v4 - 4);
      nX1 = (float)(int)((int)ptQTask[1].tQTaskChildren.ptHead + (unsigned int)nX0 - 4);
      nX0a = (float)(int)nX0;
      nY0 = (float)(int)v4;
      vB1 = ptQTaska * *(float *)&ptQTask[60].tQTaskChildren.ptTail;
      vG1 = *(float *)&ptQTask[60].tQTaskChildren.ptMiddle * 128.0;
      vR1 = *(float *)&ptQTask[60].tQTaskChildren.ptHead * 128.0;
      vY4 = *(float *)&ptQTask[60].ptPrev * 128.0;
      QSprite_Register4AZ(v3, nX0a, nY0, nX1, nY0, nX0a, nY1, nX1, nY1, vY4, vR1, vG1, vB1, 1.0, 0, 0x80000u, 0);
    }
  }
  if ( ptQTask[60].tQTaskRefList.ptMiddle && BYTE1(ptQTask[2].ptPrev) && *(int *)&ptQTask[59].eQTaskType >= 0 )
    MenuWindow_DrawBorder((struct MenuWindow_t *)ptQTask, 0.5, ptQTaska, 1);
  else
    MenuWindow_DrawBorder((struct MenuWindow_t *)ptQTask, 0.5, ptQTaska, 0);
}

// source: j/0/menusystem/picturebox.c:380  [anchor-mhash]
void __cdecl PictureBox_InitDataHandler(struct QTask_s *ptQTask)
{
  bool v1; // zf
  struct QTask_s *ptNext; // eax
  int v3; // ebp
  struct QTask_s **p_ptMiddle; // edi
  struct QTask_s *ptHead; // ecx
  int v6; // edx
  struct QTask_s *v7; // eax
  int v8; // esi
  void (__cdecl *pfHandler)(struct QTask_s *); // eax
  int v10; // edx

  *(_DWORD *)&ptQTask[59].eQTaskType = 0;
  v1 = ptQTask[62].tQTaskRefList.ptMiddle == nullptr;
  PictureBox_ptActivePictureBox = (struct PictureBox_s *)ptQTask;
  if ( !v1 && ptQTask[62].tQTaskRefList.ptTail->ptNext && ptQTask[62].ptParent )
    Level_RunLevelExpression((struct LevelExpression_s *)&ptQTask[62].tQTaskRefList.ptMiddle, ptQTask);
  ptNext = ptQTask[60].ptNext;
  v3 = 0;
  PictureBox_ptActivePictureBox = nullptr;
  p_ptMiddle = &ptQTask[2].tQTaskChildren.ptMiddle;
  if ( (int)ptNext > 0 )
  {
    do
    {
      p_ptMiddle[17] = (struct QTask_s *)MenuManager_GetSprite(
                                           *(struct QTask_s **)&ptQTask[1].eQTaskType,
                                           (char *)p_ptMiddle);
      p_ptMiddle += 18;
      ++v3;
    }
    while ( v3 < (int)ptQTask[60].ptNext );
  }
  ptHead = ptQTask->tQTaskChildren.ptHead;
  if ( ptHead->ptNext && ptHead )
  {
    v6 = QTask_nProtectedQTaskStackOffset;
    do
    {
      if ( ptHead->ptNext )
        v7 = ptHead->ptNext->ptNext != nullptr ? ptHead->ptNext : nullptr;
      else
        v7 = nullptr;
      v8 = MenuWindow_eInitDataEvent;
      QTask_atProtectedQTaskStack[v6].ptQTask = v7;
      pfHandler = (void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[v8][ptHead->eQTaskType].pfHandler;
      v10 = v6 + 1;
      QTask_nProtectedQTaskStackOffset = v10;
      if ( pfHandler )
      {
        pfHandler(ptHead);
        v10 = QTask_nProtectedQTaskStackOffset;
      }
      ptHead = (struct QTask_s *)dword_849C7DC[v10];
      v6 = v10 - 1;
      QTask_nProtectedQTaskStackOffset = v6;
    }
    while ( ptHead );
  }
}

// source: j/0/menusystem/picturebox.c:424  [size]
void __cdecl PictureBox_ChangeDataHandler(struct QTask_s *ptQTask)
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

// source: j/0/menusystem/picturebox.c:438  [size]
void __cdecl PictureBox_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = PictureBox_ptParameterList;
}

// source: j/0/menusystem/picturebox.c:457  [anchor-hash]
void __cdecl PictureBox_Open()
{
  unsigned __int16 v0; // si
  struct ParameterList_s *v1; // eax

  v0 = QTask_NewQTaskType("PictureBox", 2808, MenuWindow_eQTaskType, 0, 0);
  PictureBox_eQTaskType = v0;
  QTask_LinkQTaskEventHandlerFn(
    v0,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 1, PictureBox_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, Screen_eDrawQTaskEvent, PictureBox_DrawHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 2, PictureBox_DeleteHandler);
  QTask_LinkQTaskEventHandlerFn(v0, 0, sub_533810);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))PictureBox_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(v0, ParameterList_eUpdateInternalDataQTaskEvent, PictureBox_UpdateInternalDataHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, MenuWindow_eInitDataEvent, PictureBox_InitDataHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, MenuWindow_eChangeDataEvent, PictureBox_ChangeDataHandler);
  v1 = (struct ParameterList_s *)Mem_AllocFn(152, 4);
  v1->nParameters = 0;
  v1->nMaxParameters = 7;
  v1->ptParameterListItem = (struct ParameterListItem_s *)&v1[1];
  PictureBox_ptParameterList = v1;
  ParameterList_AddParameter(v1, 0x30u, Level_eParameterTypeInt32, "Width", 7u, nullptr);
  ParameterList_AddParameter(PictureBox_ptParameterList, 0x34u, Level_eParameterTypeInt32, "Height", 7u, nullptr);
  ParameterList_AddParameter(
    PictureBox_ptParameterList,
    0x9C8u,
    Level_eParameterTypeVarString,
    "Collect Items",
    7u,
    nullptr);
  ParameterList_AddParameter(
    PictureBox_ptParameterList,
    0xA18u,
    Level_eParameterTypeVarString,
    "Get Active Picture",
    7u,
    nullptr);
  ParameterList_AddParameter(PictureBox_ptParameterList, 0xA68u, Level_eParameterTypeVarString, "Get RGBA", 7u, nullptr);
  ParameterList_AddParameter(
    PictureBox_ptParameterList,
    0x978u,
    Level_eParameterTypeVarString,
    "On Click Script",
    7u,
    nullptr);
  ParameterList_AddParameter(
    PictureBox_ptParameterList,
    0xAB8u,
    Level_eParameterTypeString32,
    "Click Sound Resource",
    7u,
    nullptr);
}

// source: j/0/menusystem/picturebox.c:498  [size]
void __cdecl PictureBox_Close()
{
  int v0; // esi

  if ( PictureBox_ptParameterList )
  {
    v0 = *(_DWORD *)((unsigned int)&PictureBox_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
  QTask_DeleteQTaskType(PictureBox_eQTaskType);
  PictureBox_eQTaskType = 512;
}

// source: j/0/menusystem/picturebox.c:519  [anchor-callee]
char *__cdecl PictureBox_AddItem(char *zItemName, int nItemID)
{
  struct PictureBox_s *v2; // esi
  int nPicture; // ecx
  struct PictureBoxItem_s *v4; // edi
  int v5; // edx
  int *p_nItemID; // ecx
  int v7; // edx
  char v8; // cl

  v2 = PictureBox_ptActivePictureBox;
  nPicture = PictureBox_ptActivePictureBox->nPicture;
  v4 = &PictureBox_ptActivePictureBox->atPictureBoxItem[nPicture];
  v5 = 0;
  if ( nPicture <= 0 )
  {
LABEL_5:
    v4->nItemID = nItemID;
    v7 = (char *)v4 - zItemName;
    do
    {
      v8 = *zItemName;
      zItemName[v7] = *zItemName;
      ++zItemName;
    }
    while ( v8 );
    ++v2->nPicture;
  }
  else
  {
    p_nItemID = &PictureBox_ptActivePictureBox->atPictureBoxItem[0].nItemID;
    while ( *p_nItemID != nItemID )
    {
      ++v5;
      p_nItemID += 18;
      if ( v5 >= PictureBox_ptActivePictureBox->nPicture )
        goto LABEL_5;
    }
  }
  return zItemName;
}

// source: j/0/menusystem/picturebox.c:562  [anchor-mhash]
void __cdecl PictureBox_SetRGBA(float vR, float vG, float vB, float vA)
{
  struct PictureBox_s *v4; // eax

  v4 = PictureBox_ptActivePictureBox;
  PictureBox_ptActivePictureBox->vR = vR;
  v4->vG = vG;
  v4->vB = vB;
  v4->vA = vA;
}
