/* j/0/menusystem/menumanager.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/menusystem/menumanager.c:261  [size]
void __cdecl MenuManager_PlayMusic(struct QTask_s *ptQTask)
{
  struct QHashTable_s *v1; // edi
  unsigned int v2; // eax
  unsigned int v3; // eax

  if ( !ptQTask[253].ptPrev )
  {
    v1 = Sound_ptSampleHashTable;
    v2 = Sound_ptSampleHashTable->tPrivate.pfHashFunction(
           Sound_ptSampleHashTable->tPrivate.nHashTableSize,
           &g_zFileName.aptSelectableItems[25]);
    ptQTask[253].ptNext = (struct QTask_s *)((int  (__cdecl *)(struct QHashTable_s *, unsigned int, const void *))Sound_ptSampleHashTable->tPrivate.pfFindElement)(v1, v2, (const void *)(&g_zFileName.aptSelectableItems[25]));
    ptQTask[253].tQTaskChildren.ptHead = (struct QTask_s *)48;
    Sound_DefaultSoundModify((struct SoundModify_t *)&ptQTask[253].tQTaskChildren.ptTail);
  }
  if ( !SoundSys_isSoundDisabled )
  {
    if ( !ptQTask[253].ptPrev )
    {
      v3 = SoundSys_nCurrentID;
      ptQTask[253].ptPrev = (struct QTask_s *)SoundSys_nCurrentID;
      SoundSys_nCurrentID = v3 + 1;
    }
    SoundSys_AddSoundToRequestlist(
      (unsigned int)ptQTask[253].ptPrev,
      (struct Sample_s *)ptQTask[253].ptNext,
      (unsigned int)ptQTask[253].tQTaskChildren.ptHead,
      (struct SoundModify_t *)&ptQTask[253].tQTaskChildren.ptTail);
  }
}

// source: j/0/menusystem/menumanager.c:286  [anchor-mhash]
struct QTask_s *__cdecl MenuManager_FormatScreen(
        struct MenuManager_s *ptMenuManager,
        struct QTask_s *ptActiveMenuScreen)
{
  if ( ptActiveMenuScreen )
    return ((struct QTask_s *(__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[MenuWindow_eFormatEvent][ptActiveMenuScreen->eQTaskType].pfHandler)(ptActiveMenuScreen);
  return ptActiveMenuScreen;
}

// source: j/0/menusystem/menumanager.c:303  [anchor-callee]
int __cdecl MenuManager_UpdateLanguage(struct MenuManager_s *ptMenuManager, int isUpdateAll)
{
  struct QTask_s *ptHead; // ecx
  int v3; // edx
  struct QTask_s *v4; // eax
  int v5; // esi
  void (__cdecl *pfHandler)(struct QTask_s *); // eax
  int v7; // edx
  void (__cdecl *v8)(struct QTask_s *); // ecx
  int result; // eax

  if ( isUpdateAll )
  {
    ptHead = ptMenuManager->tQTask.tQTaskChildren.ptHead;
    if ( ptHead->ptNext && ptHead )
    {
      v3 = QTask_nProtectedQTaskStackOffset;
      do
      {
        if ( ptHead->ptNext )
          v4 = ptHead->ptNext->ptNext != nullptr ? ptHead->ptNext : nullptr;
        else
          v4 = nullptr;
        v5 = MenuWindow_eChangeLanguageEvent;
        QTask_atProtectedQTaskStack[v3].ptQTask = v4;
        pfHandler = (void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[v5][ptHead->eQTaskType].pfHandler;
        v7 = v3 + 1;
        QTask_nProtectedQTaskStackOffset = v7;
        if ( pfHandler )
        {
          pfHandler(ptHead);
          v7 = QTask_nProtectedQTaskStackOffset;
        }
        ptHead = (struct QTask_s *)dword_849C7DC[v7];
        v3 = v7 - 1;
        QTask_nProtectedQTaskStackOffset = v3;
      }
      while ( ptHead );
    }
  }
  else
  {
    v8 = (void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[MenuWindow_eChangeLanguageEvent][ptMenuManager->ptActiveMenuScreen->eQTaskType].pfHandler;
    if ( v8 )
      v8(ptMenuManager->ptActiveMenuScreen);
  }
  result = (int)ptMenuManager->ptActiveMenuScreen;
  if ( result )
    return ((int (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[MenuWindow_eFormatEvent][*(unsigned __int16 *)(result + 36)].pfHandler)(ptMenuManager->ptActiveMenuScreen);
  return result;
}

// source: j/0/menusystem/menumanager.c:328  [anchor-caller]
struct MenuManager_s *__cdecl MenuManager_ReadDataFromActiveWindow(struct MenuManager_s *ptMenuManager)
{
  int iActiveProfile; // ecx
  enum GameLanguage_e eLanguage; // esi
  struct QTask_s *ptActiveMenuScreen; // eax
  void (__cdecl *pfHandler)(struct QTask_s *); // edx
  struct MenuManager_s *result; // eax

  iActiveProfile = Config_tConfig.iActiveProfile;
  eLanguage = Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eLanguage;
  ptActiveMenuScreen = ptMenuManager->ptActiveMenuScreen;
  if ( ptActiveMenuScreen )
  {
    pfHandler = (void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[MenuWindow_eChangeDataEvent][ptActiveMenuScreen->eQTaskType].pfHandler;
    if ( pfHandler )
    {
      pfHandler(ptActiveMenuScreen);
      iActiveProfile = Config_tConfig.iActiveProfile;
    }
  }
  Config_tConfig.atPlayerProfile[iActiveProfile].tGameOptions.eLanguage = ptMenuManager->eGameLanguage;
  Config_SetConfig();
  if ( ptMenuManager->eGameLanguage != eLanguage )
    return (struct MenuManager_s *)MenuManager_UpdateLanguage(ptMenuManager, 1);
  return result;
}

// source: j/0/menusystem/menumanager.c:355  [anchor-callee]
struct MenuManager_s *__cdecl MenuManager_WriteDataToActiveWindow(struct MenuManager_s *ptMenuManager)
{
  struct QTask_s *ptActiveMenuScreen; // eax
  struct MenuManager_s *eGameLanguage; // esi
  void (__cdecl *pfHandler)(struct QTask_s *); // ecx
  struct MenuManager_s *result; // eax

  ptActiveMenuScreen = ptMenuManager->ptActiveMenuScreen;
  eGameLanguage = (struct MenuManager_s *)ptMenuManager->eGameLanguage;
  pfHandler = (void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[MenuWindow_eInitDataEvent][ptActiveMenuScreen->eQTaskType].pfHandler;
  if ( pfHandler )
    pfHandler(ptActiveMenuScreen);
  result = (struct MenuManager_s *)Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eLanguage;
  ptMenuManager->eGameLanguage = (enum GameLanguage_e)result;
  if ( result != eGameLanguage )
    return (struct MenuManager_s *)MenuManager_UpdateLanguage(ptMenuManager, 1);
  return result;
}

// source: j/0/menusystem/menumanager.c:379  [anchor-callee]
void __cdecl MenuManager_WalkTaskTree(struct MenuManager_s *ptMenuManager, struct QTask_s *ptQTask)
{
  struct QTask_s *ptHead; // esi

  if ( QTask_IsQTaskTypeDerived(ptQTask->eQTaskType, MenuWindow_eQTaskType) && LOBYTE(ptQTask[2].ptPrev) )
  {
    ptMenuManager->aptSelectableItems[ptMenuManager->nNumKeyboardItems++] = (struct MenuWindow_t *)ptQTask;
  }
  else
  {
    ptHead = ptQTask->tQTaskChildren.ptHead;
    if ( ptHead->ptNext && ptHead )
    {
      do
      {
        MenuManager_WalkTaskTree(ptMenuManager, ptHead);
        ptHead = ptHead->ptNext;
      }
      while ( ptHead && ptHead->ptNext );
    }
  }
}

// source: j/0/menusystem/menumanager.c:415  [anchor-callee]
void __cdecl MenuManager_WalkTaskTreeTAB(struct MenuManager_s *ptMenuManager, struct QTask_s *ptQTask)
{
  struct QTask_s *ptHead; // edx
  struct QTask_s *v3; // esi

  if ( QTask_IsQTaskTypeDerived(ptQTask->eQTaskType, MenuWindow_eQTaskType) && BYTE2(ptQTask[2].ptPrev) )
  {
    ptMenuManager->aptSelectableTABItems[ptMenuManager->nNumTABItems] = (struct MenuWindow_t *)ptQTask;
    HIBYTE(ptQTask[2].ptPrev) = 0;
    ++ptMenuManager->nNumTABItems;
  }
  ptHead = ptQTask->tQTaskChildren.ptHead;
  if ( ptHead->ptNext )
  {
    v3 = ptQTask->tQTaskChildren.ptHead;
    if ( ptHead )
    {
      do
      {
        MenuManager_WalkTaskTreeTAB(ptMenuManager, v3);
        v3 = v3->ptNext;
      }
      while ( v3 && v3->ptNext );
    }
  }
}

// source: j/0/menusystem/menumanager.c:451  [anchor-mhash]
struct MenuManager_s *__cdecl MenuManager_SelectMenuItem(
        struct MenuManager_s *ptMenuManager,
        int iItem)
{
  struct MenuWindow_t *ptActiveKeyboardItem; // ecx
  struct MenuWindow_t *v3; // ecx

  ptActiveKeyboardItem = ptMenuManager->ptActiveKeyboardItem;
  if ( ptActiveKeyboardItem )
    ptActiveKeyboardItem->isSelectedByKeyboard = 0;
  ptMenuManager->iActiveKeyboardItem = iItem;
  v3 = ptMenuManager->aptSelectableItems[iItem];
  ptMenuManager->ptActiveKeyboardItem = v3;
  if ( v3 )
    v3->isSelectedByKeyboard = 1;
  return ptMenuManager;
}

// source: j/0/menusystem/menumanager.c:476  [anchor-hash]
void __cdecl MenuManager_UpdateKeyboardHandling(struct MenuManager_s *ptMenuManager)
{
  struct QTask_s *ptActivePopupScreen; // eax
  struct MenuWindow_t *ptActiveKeyboardItem; // eax
  struct MenuWindow_t *v3; // eax

  ptActivePopupScreen = ptMenuManager->ptActivePopupScreen;
  ptMenuManager->aptSelectableItems[0] = nullptr;
  ptMenuManager->nNumKeyboardItems = 0;
  if ( ptActivePopupScreen || (ptActivePopupScreen = ptMenuManager->ptActiveMenuScreen) != nullptr )
    MenuManager_WalkTaskTree(ptMenuManager, ptActivePopupScreen);
  ptActiveKeyboardItem = ptMenuManager->ptActiveKeyboardItem;
  if ( ptActiveKeyboardItem && !ptActiveKeyboardItem->isSelectableByKeyboard )
  {
    ptActiveKeyboardItem->isSelectedByKeyboard = 0;
    ptMenuManager->iActiveKeyboardItem = 0;
    v3 = ptMenuManager->aptSelectableItems[0];
    ptMenuManager->ptActiveKeyboardItem = v3;
    if ( v3 )
      v3->isSelectedByKeyboard = 1;
  }
}

// source: j/0/menusystem/menumanager.c:508  [anchor-callee]
void __cdecl MenuManager_InitKeyboardHandling(
        struct MenuManager_s *ptMenuManager,
        struct QTask_s *ptActiveMenuScreen)
{
  struct QReference_s *ptCaptureKeyboardQTaskRef; // eax
  struct MenuWindow_t *ptActiveKeyboardItem; // eax
  struct MenuWindow_t *v4; // eax

  ptMenuManager->iActiveKeyboardItem = 0;
  ptMenuManager->iActiveTABItem = 0;
  ptMenuManager->aptSelectableItems[0] = nullptr;
  ptMenuManager->nNumKeyboardItems = 0;
  ptMenuManager->nNumTABItems = 0;
  ptCaptureKeyboardQTaskRef = ptMenuManager->ptCaptureKeyboardQTaskRef;
  if ( ptCaptureKeyboardQTaskRef )
  {
    QReference_Delete(ptCaptureKeyboardQTaskRef, &QTask_tQTaskRefPool);
    ptMenuManager->ptCaptureKeyboardQTaskRef = nullptr;
  }
  if ( ptMenuManager->ptActiveMenuScreen )
  {
    MenuManager_WalkTaskTree(ptMenuManager, ptActiveMenuScreen);
    MenuManager_WalkTaskTreeTAB(ptMenuManager, ptActiveMenuScreen);
  }
  ptActiveKeyboardItem = ptMenuManager->ptActiveKeyboardItem;
  if ( ptActiveKeyboardItem )
    ptActiveKeyboardItem->isSelectedByKeyboard = 0;
  ptMenuManager->iActiveKeyboardItem = 0;
  v4 = ptMenuManager->aptSelectableItems[0];
  ptMenuManager->ptActiveKeyboardItem = v4;
  if ( v4 )
    v4->isSelectedByKeyboard = 1;
}

// source: j/0/menusystem/menumanager.c:537  [size~]
void __cdecl MenuManager_HandleKeyboard(struct MenuManager_s *ptMenuManager)
{
  int iActiveKeyboardItem; // edi
  struct QReference_s *ptCaptureKeyboardQTaskRef; // eax
  int i; // edx
  int v4; // eax
  struct QTask_s *ptActivePopupScreen; // edx
  struct MenuWindow_t *v6; // eax
  struct MenuWindow_t *v7; // eax
  struct MenuWindow_t *ptActiveKeyboardItem; // ecx

  iActiveKeyboardItem = ptMenuManager->iActiveKeyboardItem;
  ptMenuManager->tMenuInputContext.isPressedEscape = 0;
  if ( (Mouse_tMouse.bButton & 0x100) != 0 )
    ptMenuManager->tMenuInputContext.nWheelMouseStatus = -1;
  else
    ptMenuManager->tMenuInputContext.nWheelMouseStatus = (Mouse_tMouse.bButton >> 9) & 1;
  ptCaptureKeyboardQTaskRef = ptMenuManager->ptCaptureKeyboardQTaskRef;
  if ( !ptCaptureKeyboardQTaskRef || !ptCaptureKeyboardQTaskRef->pxObject )
  {
    for ( i = tKeyboardBuffer.nBuffer; tKeyboardBuffer.nBuffer; i = tKeyboardBuffer.nBuffer )
    {
      v4 = 0;
      if ( i )
      {
        v4 = tKeyboardBuffer.anBuffer[tKeyboardBuffer.iBufferIndex++];
        if ( tKeyboardBuffer.iBufferIndex == 32 )
          tKeyboardBuffer.iBufferIndex = 0;
        tKeyboardBuffer.nBuffer = i - 1;
      }
      if ( ptMenuManager->isEnableNavigation || v4 == -8 )
      {
        ptActivePopupScreen = ptMenuManager->ptActivePopupScreen;
        if ( ptActivePopupScreen && BYTE1(ptActivePopupScreen[2].tQTaskChildren.ptTail) )
        {
          switch ( v4 )
          {
            case -4:
              v4 = -2;
              break;
            case -3:
              v4 = -1;
              break;
            case -2:
              v4 = -4;
              break;
            case -1:
              v4 = -3;
              break;
            default:
              break;
          }
        }
        switch ( v4 )
        {
          case -11:
            if ( !ptActivePopupScreen )
              MenuManager_GotoNextTAB(&ptMenuManager->tQTask);
            break;
          case -8:
            ptMenuManager->tMenuInputContext.isPressedEscape = 1;
            break;
          case -7:
          case -2:
          case -1:
            ptActiveKeyboardItem = ptMenuManager->ptActiveKeyboardItem;
            if ( ptActiveKeyboardItem )
              ptActiveKeyboardItem->nKeyPress = v4;
            break;
          case -4:
            if ( ++iActiveKeyboardItem >= ptMenuManager->nNumKeyboardItems )
              iActiveKeyboardItem = 0;
            goto LABEL_25;
          case -3:
            if ( --iActiveKeyboardItem < 0 )
              iActiveKeyboardItem = ptMenuManager->nNumKeyboardItems - 1;
LABEL_25:
            v6 = ptMenuManager->ptActiveKeyboardItem;
            if ( v6 )
              v6->isSelectedByKeyboard = 0;
            ptMenuManager->iActiveKeyboardItem = iActiveKeyboardItem;
            v7 = ptMenuManager->aptSelectableItems[iActiveKeyboardItem];
            ptMenuManager->ptActiveKeyboardItem = v7;
            if ( v7 )
              v7->isSelectedByKeyboard = 1;
            SoundSys_PlaySimpleSoundFn((char *)&g_zFileName.aptSelectableItems[22], 0, nullptr);
            break;
          default:
            continue;
        }
      }
    }
  }
}

// source: j/0/menusystem/menumanager.c:653  [anchor-callee]
int __cdecl MenuManager_ActivateScreen(
        struct QTask_s *ptQTask,
        int nActiveMenuScreenID,
        enum bool isDataExchange)
{
  struct QReference_s *v4; // eax
  int result; // eax
  struct QReference_s *ptHead; // eax

  ptQTask[1].ptNext = (struct QTask_s *)nActiveMenuScreenID;
  if ( (unsigned int)nActiveMenuScreenID < 0x1000 && (v4 = Level_atLevelQTaskID[nActiveMenuScreenID]) != nullptr )
    result = (int)v4->pxObject;
  else
    result = 0;
  ptQTask[1].tQTaskRefList.ptHead = (struct QReference_s *)result;
  if ( result )
  {
    ((void (__cdecl *)(int))QTask_aatQTaskFinalEvent[MenuWindow_eFormatEvent][*(unsigned __int16 *)(result + 36)].pfHandler)(result);
    if ( isDataExchange )
      MenuManager_WriteDataToActiveWindow((struct MenuManager_s *)ptQTask);
    MenuManager_InitKeyboardHandling((struct MenuManager_s *)ptQTask, (struct QTask_s *)ptQTask[1].tQTaskRefList.ptHead);
    ptHead = ptQTask[1].tQTaskRefList.ptHead;
    BYTE1(ptQTask[250].tQTaskRefList.ptHead) = 0;
    BYTE2(ptQTask[250].tQTaskRefList.ptHead) = 0;
    LOBYTE(ptQTask[250].tQTaskRefList.ptHead) = 0;
    HIBYTE(ptQTask[250].tQTaskRefList.ptHead) = 1;
    result = ((int (__cdecl *)(struct QReference_s *))QTask_aatQTaskFinalEvent[1][LOWORD(ptHead[3].ptNext)].pfHandler)(ptHead);
    HIBYTE(ptQTask[250].tQTaskRefList.ptHead) = 0;
  }
  return result;
}

// source: j/0/menusystem/menumanager.c:698  [anchor-callee]
struct MenuManager_s *__cdecl MenuManager_ActivatePopupScreen(struct MenuManager_s *ptMenuManager)
{
  unsigned int nActivePopupScreenID; // eax
  struct QReference_s *v3; // eax
  struct MenuManager_s *result; // eax
  void (__cdecl *pfHandler)(struct MenuManager_s *); // ecx
  struct QTask_s *ptActivePopupScreen; // eax
  int nNumKeyboardItems; // eax
  struct MenuWindow_t *ptActiveKeyboardItem; // ecx
  int v9; // eax
  struct MenuWindow_t *v10; // eax
  struct QTask_s *v11; // eax

  nActivePopupScreenID = ptMenuManager->nActivePopupScreenID;
  if ( nActivePopupScreenID < 0x1000 && (v3 = Level_atLevelQTaskID[nActivePopupScreenID]) != nullptr )
    result = (struct MenuManager_s *)v3->pxObject;
  else
    result = nullptr;
  ptMenuManager->ptActivePopupScreen = &result->tQTask;
  if ( result )
  {
    pfHandler = (void (__cdecl *)(struct MenuManager_s *))QTask_aatQTaskFinalEvent[MenuWindow_eInitDataEvent][result->tQTask.eQTaskType].pfHandler;
    if ( pfHandler )
      pfHandler(result);
    ptActivePopupScreen = ptMenuManager->ptActivePopupScreen;
    if ( ptActivePopupScreen )
      ((void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[MenuWindow_eFormatEvent][ptActivePopupScreen->eQTaskType].pfHandler)(ptMenuManager->ptActivePopupScreen);
    MenuManager_InitKeyboardHandling(ptMenuManager, ptMenuManager->ptActivePopupScreen);
    nNumKeyboardItems = ptMenuManager->nNumKeyboardItems;
    if ( nNumKeyboardItems )
    {
      ptActiveKeyboardItem = ptMenuManager->ptActiveKeyboardItem;
      v9 = nNumKeyboardItems - 1;
      if ( ptActiveKeyboardItem )
        ptActiveKeyboardItem->isSelectedByKeyboard = 0;
      ptMenuManager->iActiveKeyboardItem = v9;
      v10 = ptMenuManager->aptSelectableItems[v9];
      ptMenuManager->ptActiveKeyboardItem = v10;
      if ( v10 )
        v10->isSelectedByKeyboard = 1;
    }
    v11 = ptMenuManager->ptActivePopupScreen;
    ptMenuManager->tMenuInputContext.isPressed = 0;
    ptMenuManager->tMenuInputContext.isReleased = 0;
    ptMenuManager->tMenuInputContext.isButtonDown = 0;
    ptMenuManager->tMenuInputContext.isFirstFrame = 1;
    result = (struct MenuManager_s *)((int (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[1][v11->eQTaskType].pfHandler)(v11);
    ptMenuManager->tMenuInputContext.isFirstFrame = 0;
  }
  return result;
}

// source: j/0/menusystem/menumanager.c:733  [anchor-hash]
struct MenuManager_s *__cdecl MenuManager_DeactivatePopupScreen(struct MenuManager_s *ptMenuManager)
{
  struct MenuManager_s *result; // eax

  result = (struct MenuManager_s *)ptMenuManager->ptActivePopupScreen;
  if ( result )
  {
    result = (struct MenuManager_s *)ptMenuManager->ptActiveMenuScreen;
    ptMenuManager->ptActivePopupScreen = nullptr;
    if ( result )
    {
      ((void (__cdecl *)(struct MenuManager_s *))QTask_aatQTaskFinalEvent[MenuWindow_eFormatEvent][result->tQTask.eQTaskType].pfHandler)(result);
      MenuManager_InitKeyboardHandling(ptMenuManager, ptMenuManager->ptActiveMenuScreen);
    }
  }
  return result;
}

// source: j/0/menusystem/menumanager.c:760  [anchor-mhash]
struct Result_s *__cdecl MenuManager_RequestScreenCB(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  struct ArgList_s *v3; // edi
  struct ArgList_s *v4; // eax
  struct ArgList_s *v5; // eax
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  v3 = ptArgList;
  if ( ptArgList->isQVM )
  {
    ptArgList = nullptr;
    QVM_EvalArg(&ptArgList, 4, v3, 1, 1);
    v4 = ptArgList;
  }
  else
  {
    v4 = (struct ArgList_s *)Expression_EvalInt(ptArgList->aptExpression[1]);
  }
  if ( v4 )
    MenuManager_ReadDataFromActiveWindow((struct MenuManager_s *)pxData);
  if ( v3->isQVM )
  {
    ptArgList = nullptr;
    QVM_EvalArg(&ptArgList, 4, v3, 0, 1);
    v5 = ptArgList;
  }
  else
  {
    v5 = (struct ArgList_s *)Expression_EvalInt(*v3->aptExpression);
  }
  *((_DWORD *)pxData + 10) = v5;
  *((_DWORD *)pxData + 13) = 7;
  *((_DWORD *)pxData + 14) = 0;
  Rs.nResult = 1;
  Rs.vResult = 1.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/menusystem/menumanager.c:790  [anchor-mhash]
void __cdecl MenuManager_PushScreen(int nActiveMenuScreenID, int eStatus, int eNextStatus)
{
  struct QTask_s *v3; // eax

  v3 = MenuManager_ptQTask;
  *((_DWORD *)&MenuManager_ptQTask[251].tQTaskChildren.ptMiddle + (int)MenuManager_ptQTask[251].tQTaskChildren.ptHead) = MenuManager_ptQTask[1].ptNext;
  ++*(int *)&v3[251].tQTaskChildren.ptHead;
  v3[1].ptNext = (struct QTask_s *)nActiveMenuScreenID;
  v3[1].tQTaskChildren.ptMiddle = (struct QTask_s *)eStatus;
  v3[1].tQTaskChildren.ptTail = (struct QTask_s *)eNextStatus;
}

// source: j/0/menusystem/menumanager.c:816  [anchor-mhash]
struct Result_s *__cdecl MenuManager_PushScreenCB(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  struct ArgList_s *v3; // edi
  struct ArgList_s *v4; // eax
  struct QTask_s *v5; // ecx
  struct QTask_s *ptHead; // edx
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  v3 = ptArgList;
  if ( ptArgList->isQVM )
  {
    ptArgList = nullptr;
    QVM_EvalArg(&ptArgList, 4, v3, 0, 1);
    v4 = ptArgList;
  }
  else
  {
    v4 = (struct ArgList_s *)Expression_EvalInt(*ptArgList->aptExpression);
  }
  v5 = MenuManager_ptQTask;
  *((_DWORD *)&MenuManager_ptQTask[251].tQTaskChildren.ptMiddle + (int)MenuManager_ptQTask[251].tQTaskChildren.ptHead) = MenuManager_ptQTask[1].ptNext;
  ptHead = v5[251].tQTaskChildren.ptHead;
  v5[1].ptNext = (struct QTask_s *)v4;
  v5[1].tQTaskChildren.ptTail = nullptr;
  v5[251].tQTaskChildren.ptHead = (struct QTask_s *)((char *)&ptHead->ptNext + 1);
  v5[1].tQTaskChildren.ptMiddle = (struct QTask_s *)7;
  Rs.nResult = 1;
  Rs.vResult = 1.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/menusystem/menumanager.c:840  [anchor-mhash]
struct Result_s *__cdecl MenuManager_PopScreenCB(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  struct ArgList_s *v3; // edi
  struct ArgList_s *v4; // eax
  int v5; // eax
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  v3 = ptArgList;
  if ( ptArgList->isQVM )
  {
    ptArgList = nullptr;
    QVM_EvalArg(&ptArgList, 4, v3, 0, 1);
    v4 = ptArgList;
  }
  else
  {
    v4 = (struct ArgList_s *)Expression_EvalInt(*ptArgList->aptExpression);
  }
  if ( v4 )
    MenuManager_ReadDataFromActiveWindow((struct MenuManager_s *)pxData);
  v5 = *((_DWORD *)pxData + 2512) - 1;
  *((_DWORD *)pxData + 2512) = v5;
  *((_DWORD *)pxData + 10) = *((_DWORD *)pxData + v5 + 2513);
  *((_DWORD *)pxData + 13) = 7;
  *((_DWORD *)pxData + 14) = 1;
  Rs.nResult = 1;
  Rs.vResult = 1.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/menusystem/menumanager.c:871  [size]
struct Result_s *__cdecl MenuManager_ClearStackCB(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  *((_DWORD *)pxData + 2512) = 0;
  Rs.nResult = 1;
  Rs.vResult = 1.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/menusystem/menumanager.c:894  [anchor-callee]
enum bool __cdecl MenuManager_LeaveMenues(
        int nActiveMenuScreenID,
        int eNextStatus,
        enum bool isDoDataExchange)
{
  struct QTask_s *v3; // eax
  struct QTask_s *v4; // esi
  int ptHead; // ecx
  char eQTaskType_high; // cl

  v3 = MenuManager_ptQTask;
  v4 = MenuManager_ptQTask;
  if ( isDoDataExchange )
  {
    MenuManager_ReadDataFromActiveWindow((struct MenuManager_s *)MenuManager_ptQTask);
    v3 = MenuManager_ptQTask;
  }
  ptHead = (int)v4[251].tQTaskChildren.ptHead;
  if ( ptHead > 0 )
  {
    v4[251].tQTaskChildren.ptHead = (struct QTask_s *)(ptHead - 1);
    v4[1].ptNext = *(&v4[251].tQTaskChildren.ptHead + ptHead);
    v4[1].tQTaskChildren.ptMiddle = (struct QTask_s *)7;
    v4[1].tQTaskChildren.ptTail = (struct QTask_s *)1;
    return true;
  }
  if ( !LevelFlow_ptLevelFlow || !LevelFlow_ptLevelFlow->isFailed || eNextStatus != 10 || Game_eGameMode )
  {
    v4[1].ptNext = (struct QTask_s *)nActiveMenuScreenID;
    eQTaskType_high = HIBYTE(v4[243].eQTaskType);
    v4[1].tQTaskChildren.ptTail = (struct QTask_s *)eNextStatus;
    if ( eQTaskType_high )
    {
      v4[1].tQTaskChildren.ptMiddle = (struct QTask_s *)10;
      v4[8].ptParent = nullptr;
      HIBYTE(v4[243].eQTaskType) = 0;
      LOBYTE(v3[243].eQTaskType) = 0;
      return true;
    }
    v4[1].tQTaskChildren.ptMiddle = (struct QTask_s *)7;
    LOBYTE(v3[243].eQTaskType) = 0;
  }
  return true;
}

// source: j/0/menusystem/menumanager.c:954  [anchor-caller]
struct Result_s *__cdecl MenuManager_LeaveMenusCB(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  struct ArgList_s *v3; // edi
  struct ArgList_s *v4; // ebp
  struct ArgList_s *v5; // esi
  char v6; // al
  struct Result_s Rs; // [esp+Ch] [ebp-18h] BYREF

  v3 = ptArgList;
  if ( ptArgList->isQVM )
  {
    ptArgList = nullptr;
    QVM_EvalArg(&ptArgList, 4, v3, 0, 1);
    v4 = ptArgList;
  }
  else
  {
    v4 = (struct ArgList_s *)Expression_EvalInt(*ptArgList->aptExpression);
  }
  if ( v3->isQVM )
  {
    ptArgList = nullptr;
    QVM_EvalArg(&ptArgList, 4, v3, 1, 1);
    v5 = ptArgList;
  }
  else
  {
    v5 = (struct ArgList_s *)Expression_EvalInt(v3->aptExpression[1]);
  }
  if ( v3->isQVM )
  {
    ptArgList = nullptr;
    QVM_EvalArg(&ptArgList, 4, v3, 2, 1);
    v6 = (char)ptArgList;
  }
  else
  {
    v6 = Expression_EvalInt(v3->aptExpression[2]);
  }
  Rs.nResult = (char)MenuManager_LeaveMenues((int)v4, (int)v5, (enum bool)v6);
  Rs.vResult = (double)Rs.nResult;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/menusystem/menumanager.c:982  [anchor-mhash]
struct Result_s *__cdecl MenuManager_SetLanguageCB(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  _DWORD *v3; // esi
  struct ArgList_s *v4; // edi
  void *v5; // eax
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  v3 = pxData;
  v4 = ptArgList;
  *((_DWORD *)pxData + 13) = 7;
  v3[14] = 5;
  if ( v4->isQVM )
  {
    pxData = nullptr;
    QVM_EvalArg(&pxData, 4, v4, 0, 1);
    v5 = pxData;
  }
  else
  {
    v5 = (void *)Expression_EvalInt(*v4->aptExpression);
  }
  v3[2511] = v5;
  Rs.nResult = 1;
  Rs.vResult = 1.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/menusystem/menumanager.c:1004  [anchor-mhash]
struct Result_s *__cdecl MenuManager_ForceUpdateWindowCB(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  struct ArgList_s *v3; // edi
  struct ArgList_s *v4; // eax
  struct QReference_s *v5; // eax
  unsigned __int16 *pxObject; // eax
  void (__cdecl *pfHandler)(unsigned __int16 *); // ecx
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  v3 = ptArgList;
  if ( ptArgList->isQVM )
  {
    ptArgList = nullptr;
    QVM_EvalArg(&ptArgList, 4, v3, 0, 1);
    v4 = ptArgList;
  }
  else
  {
    v4 = (struct ArgList_s *)Expression_EvalInt(*ptArgList->aptExpression);
  }
  if ( (unsigned int)v4 < 0x1000 )
  {
    v5 = Level_atLevelQTaskID[(_DWORD)v4];
    if ( v5 )
    {
      pxObject = (unsigned __int16 *)v5->pxObject;
      if ( pxObject )
      {
        pfHandler = (void (__cdecl *)(unsigned __int16 *))QTask_aatQTaskFinalEvent[MenuWindow_eInitDataEvent][pxObject[18]].pfHandler;
        if ( pfHandler )
          pfHandler(pxObject);
      }
    }
  }
  Rs.nResult = 1;
  Rs.vResult = 1.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/menusystem/menumanager.c:1029  [anchor-mhash]
struct Result_s *__cdecl MenuManager_ActivatePopupScreenCB(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  struct ArgList_s *v3; // edi
  struct ArgList_s *v4; // eax
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  v3 = ptArgList;
  if ( ptArgList->isQVM )
  {
    ptArgList = nullptr;
    QVM_EvalArg(&ptArgList, 4, v3, 0, 1);
    v4 = ptArgList;
  }
  else
  {
    v4 = (struct ArgList_s *)Expression_EvalInt(*ptArgList->aptExpression);
  }
  *((_DWORD *)pxData + 11) = v4;
  *((_DWORD *)pxData + 13) = 16;
  Rs.nResult = 1;
  Rs.vResult = 1.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/menusystem/menumanager.c:1051  [anchor-mhash]
struct Result_s *__cdecl MenuManager_DeactivatePopupScreenCB(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  *((_DWORD *)pxData + 13) = 9;
  *((_DWORD *)pxData + 14) = 17;
  Rs.nResult = 1;
  Rs.vResult = 1.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/menusystem/menumanager.c:1073  [anchor-mhash]
struct Result_s *__cdecl MenuManager_EnableCB(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  struct ArgList_s *v3; // edi
  struct ArgList_s *v4; // eax
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  v3 = ptArgList;
  if ( ptArgList->isQVM )
  {
    ptArgList = nullptr;
    QVM_EvalArg(&ptArgList, 4, v3, 0, 1);
    v4 = ptArgList;
  }
  else
  {
    v4 = (struct ArgList_s *)Expression_EvalInt(*ptArgList->aptExpression);
  }
  *((_DWORD *)pxData + 13) = 19 - (v4 != (struct ArgList_s *)1);
  Rs.nResult = 1;
  Rs.vResult = 1.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/menusystem/menumanager.c:1102  [anchor-strings]
void __cdecl MenuManager_FreeResources(struct MenuManager_s *ptMenuManager)
{
  int v1; // edi
  struct QSprite_s *p_tSprite; // ebx
  int v3; // edi
  struct StaticTilemap_s **p_ptPicture; // ebp
  int v5; // edi
  struct QSprite_s **p_ptFont; // ebp
  bool v7; // zf
  void *pxMenusResource; // edx
  struct Resource_s *ptHead; // ecx
  struct Resource_s *ptNext; // eax
  unsigned int nType; // eax
  void *pxMenusResource2; // edx
  struct Resource_s *v13; // ecx
  struct Resource_s *v14; // eax
  unsigned int v15; // eax
  int v16; // ebp
  void **apxLanguageResource; // edi
  struct Resource_s *v18; // ecx
  struct Resource_s *v19; // eax
  unsigned int v20; // eax

  v1 = 0;
  if ( ptMenuManager->nSpriteResources > 0 )
  {
    p_tSprite = &ptMenuManager->atSpriteResources[0].tSprite;
    do
    {
      QSprite_DeAlloc(p_tSprite);
      ++v1;
      p_tSprite = (struct QSprite_s *)((char *)p_tSprite + 88);
    }
    while ( v1 < ptMenuManager->nSpriteResources );
  }
  v3 = 0;
  if ( ptMenuManager->nPictureResources > 0 )
  {
    p_ptPicture = &ptMenuManager->atPictureResources[0].ptPicture;
    do
    {
      Picture_Delete(*p_ptPicture);
      ++v3;
      p_ptPicture += 17;
    }
    while ( v3 < ptMenuManager->nPictureResources );
  }
  v5 = 0;
  if ( ptMenuManager->nFontResources > 0 )
  {
    p_ptFont = &ptMenuManager->atFontResources[0].ptFont;
    do
    {
      FontManager_DeleteFont(*p_ptFont);
      ++v5;
      p_ptFont += 17;
    }
    while ( v5 < ptMenuManager->nFontResources );
  }
  v7 = ptMenuManager->isSoundLoaded == 0;
  ptMenuManager->nSpriteResources = 0;
  ptMenuManager->nPictureResources = 0;
  ptMenuManager->nFontResources = 0;
  if ( !v7 )
  {
    SoundSys_UnloadSoundResource((char *)&g_zFileName.aptSelectableItems[13]);
    ptMenuManager->isSoundLoaded = 0;
  }
  pxMenusResource = ptMenuManager->pxMenusResource;
  if ( pxMenusResource )
  {
    ptHead = Resource_tResourceList.ptHead;
    ptNext = Resource_tResourceList.ptHead->ptNext;
    if ( Resource_tResourceList.ptHead->ptNext )
    {
      while ( ptHead->pxData != pxMenusResource )
      {
        ptHead = ptNext;
        ptNext = ptNext->ptNext;
        if ( !ptNext )
          goto LABEL_20;
      }
      nType = ptHead->nType;
      if ( nType != 3 && nType != 1 )
        Resource_Remove(ptHead);
    }
LABEL_20:
    ptMenuManager->pxMenusResource = nullptr;
  }
  pxMenusResource2 = ptMenuManager->pxMenusResource2;
  if ( pxMenusResource2 )
  {
    v13 = Resource_tResourceList.ptHead;
    v14 = Resource_tResourceList.ptHead->ptNext;
    if ( Resource_tResourceList.ptHead->ptNext )
    {
      while ( v13->pxData != pxMenusResource2 )
      {
        v13 = v14;
        v14 = v14->ptNext;
        if ( !v14 )
          goto LABEL_29;
      }
      v15 = v13->nType;
      if ( v15 != 3 && v15 != 1 )
        Resource_Remove(v13);
    }
LABEL_29:
    ptMenuManager->pxMenusResource2 = nullptr;
  }
  v16 = 0;
  if ( ptMenuManager->nLanguageResource > 0 )
  {
    apxLanguageResource = ptMenuManager->apxLanguageResource;
    do
    {
      v18 = Resource_tResourceList.ptHead;
      v19 = Resource_tResourceList.ptHead->ptNext;
      if ( Resource_tResourceList.ptHead->ptNext )
      {
        while ( v18->pxData != *apxLanguageResource )
        {
          v18 = v19;
          v19 = v19->ptNext;
          if ( !v19 )
            goto LABEL_39;
        }
        v20 = v18->nType;
        if ( v20 != 3 && v20 != 1 )
          Resource_Remove(v18);
      }
LABEL_39:
      *apxLanguageResource = nullptr;
      ++v16;
      ++apxLanguageResource;
    }
    while ( v16 < ptMenuManager->nLanguageResource );
  }
  ptMenuManager->nLanguageResource = 0;
}

// source: j/0/menusystem/menumanager.c:1173  [size]
void __cdecl MenuManager_EnumerateFontsCallback(
        struct EnumFontsContext_s *ptEnumFontsContext,
        struct MenuManager_s *ptMenuManager)
{
  struct FontResource_s *v2; // ebx

  v2 = &ptMenuManager->atFontResources[ptMenuManager->nFontResources];
  File_GetFilenameNoPath(v2->zResourceFilename, 0x40u, ptEnumFontsContext->pzFilename);
  v2->ptFont = FontManager_LoadFont(ptEnumFontsContext->pzFilename);
  ++ptMenuManager->nFontResources;
}

// source: j/0/menusystem/menumanager.c:1191  [anchor-mhash]
void __cdecl MenuManager_ResourceCallbackHandler(
        struct FileDirListCallbackContext_s *ptDirListCallbackContext,
        void *pxContext)
{
  char *zFilename; // edi
  char *v4; // ebp
  char *v5; // ebx
  int v6; // ebx
  signed int i; // eax
  char v8; // cl
  struct PictureResource_s *ptCurrentPictureResource; // [esp+10h] [ebp-4h]
  char *pxContexta = *(char * *)&pxContext; // [esp+1Ch] [ebp+8h] ARGSLOT

  zFilename = ptDirListCallbackContext->zFilename;
  v4 = (char *)pxContext + 88 * *((__int16 *)pxContext + 4830) + 1852;
  v5 = &ptDirListCallbackContext->zFilename[strlen(ptDirListCallbackContext->zFilename) - 3];
  ptCurrentPictureResource = (struct PictureResource_s *)((char *)pxContext + 68 * *((__int16 *)pxContext + 4832) + 7484);
  pxContexta = (char *)pxContext + 68 * *((__int16 *)pxContext + 4831) + 764;
  if ( !_stricmp(v5, (char *)&g_zFileName.aptSelectableItems[12]) )
  {
    v6 = 0;
  }
  else if ( !_stricmp(v5, (char *)&g_zFileName.aptSelectableItems[11])
         || !_stricmp(v5, (char *)&g_zFileName.aptSelectableItems[10]) )
  {
    v6 = 1;
  }
  else
  {
    if ( _stricmp(v5, (char *)&g_zFileName.aptSelectableItems[9]) )
      return;
    v6 = 2;
  }
  for ( i = strlen(zFilename) - 1; i > 0; --i )
  {
    v8 = zFilename[i - 1];
    if ( v8 == 47 )
      break;
    if ( v8 == 58 )
      break;
    if ( v8 == 92 )
      break;
  }
  if ( v6 )
  {
    if ( v6 == 1 )
    {
      strcpy(ptCurrentPictureResource->zResourceFilename, &ptDirListCallbackContext->zFilename[i]);
      ptCurrentPictureResource->ptPicture = Picture_Load(zFilename);
      ++*((_WORD *)pxContext + 4832);
    }
    else
    {
      strcpy(pxContexta, &ptDirListCallbackContext->zFilename[i]);
      *((_DWORD *)pxContexta + 16) = FontManager_LoadFont(zFilename);
      ++*((_WORD *)pxContext + 4831);
    }
  }
  else
  {
    strcpy(v4, &ptDirListCallbackContext->zFilename[i]);
    QSprite_Load((struct QSprite_s *)(v4 + 64), zFilename);
    ++*((_WORD *)pxContext + 4830);
  }
}

// source: j/0/menusystem/menumanager.c:1309  [anchor-strings]
void __cdecl MenuManager_LoadLanguageResourceFile(struct MenuManager_s *ptMenuManager, char *zFileName)
{
  #pragma pack(push, 1)
  union
  {
    struct { char v8[4]; };
    struct { char igi2_o1[4]; char zFilename[4]; };
    struct { char igi2_o2[8]; char zTemp[256]; };
    char igi2_extent[264];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  char *v2; // ebp
  unsigned int i; // edi
  char *v4; // ecx
  int v5; // eax
  void *v6; // eax
  void *v7; // eax

  v2 = Config_azGameLanguage;
  for ( i = 0; i < 0x60; i += 16 )
  {
    sprintf(igi2_frame.zTemp, (char *const)&g_zFileName.aptSelectableItems[3], v2, zFileName);
    if ( Resource_IsLoadedInternal(igi2_frame.zTemp, (struct Resource_s **)igi2_frame.zFilename) )
    {
      v5 = *(_DWORD *)igi2_frame.zFilename;
      *(_DWORD *)(*(_DWORD *)igi2_frame.zFilename + 44) = 1;
      v6 = *(void **)(v5 + 52);
    }
    else
    {
      Game_MPRunNetwork(v4);
      v7 = File_Load(igi2_frame.zTemp, (unsigned int *)igi2_frame.v8);
      if ( !v7 )
      {
        LDebug_Error("Failed to load resource: '%s'", igi2_frame.zTemp);
        abort();
      }
      v6 = Resource_ParseFile(File_zLastSubstitutedPath, v7, *(unsigned int *)igi2_frame.v8);
    }
    ptMenuManager->apxLanguageResource[ptMenuManager->nLanguageResource] = v6;
    v2 += 16;
    ++ptMenuManager->nLanguageResource;
  }
}

// source: j/0/menusystem/menumanager.c:1335  [anchor-strings]
struct MenuManager_s *__cdecl MenuManager_LoadResources(struct MenuManager_s *ptMenuManager)
{
  #pragma pack(push, 1)
  union
  {
    struct { char zFilename[4]; };
    struct { char igi2_o1[4]; char zMenuResourceDir[256]; };
    char igi2_extent[260];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  char *zMenuResourcePath; // ebx
  char *v3; // eax
  char v4; // cl
  char *v5; // eax
  char *v6; // ecx
  int v7; // eax
  void *v8; // eax
  void *v9; // eax
  char *v10; // ecx
  unsigned int v11; // eax
  void *v12; // eax
  void *v13; // eax
  char *v14; // edi
  struct MenuManager_s *result; // eax

  zMenuResourcePath = ptMenuManager->zMenuResourcePath;
  v3 = ptMenuManager->zMenuResourcePath;
  do
  {
    v4 = *v3;
    v3[igi2_frame.zMenuResourceDir - zMenuResourcePath] = *v3;
    ++v3;
  }
  while ( v4 );
  v5 = strrchr(igi2_frame.zMenuResourceDir, 47);
  if ( v5 )
    *v5 = 0;
  MenuManager_FreeResources(ptMenuManager);
  if ( AppContext_tAppContext.isServer == false )
  {
    SoundSys_LoadSoundResource((char *)&g_zFileName.aptSelectableItems[13]);
    ptMenuManager->isSoundLoaded = 1;
  }
  if ( Resource_IsLoadedInternal(zMenuResourcePath, (struct Resource_s **)igi2_frame.zFilename) )
  {
    v7 = *(_DWORD *)igi2_frame.zFilename;
    *(_DWORD *)(*(_DWORD *)igi2_frame.zFilename + 44) = 1;
    v8 = *(void **)(v7 + 52);
  }
  else
  {
    Game_MPRunNetwork(v6);
    v9 = File_Load(zMenuResourcePath, (unsigned int *)igi2_frame.zFilename);
    if ( !v9 )
    {
      LDebug_Error("Failed to load resource: '%s'", zMenuResourcePath);
      goto LABEL_11;
    }
    v8 = Resource_ParseFile(File_zLastSubstitutedPath, v9, *(unsigned int *)igi2_frame.zFilename);
  }
  ptMenuManager->pxMenusResource = v8;
  Resource_DirList(igi2_frame.zMenuResourceDir, MenuManager_ResourceCallbackHandler, ptMenuManager);
  FontManager_EnumerateFonts(
    (void (__cdecl *)(struct EnumFontsContext_s *, void *))MenuManager_EnumerateFontsCallback,
    ptMenuManager);
  if ( Resource_IsLoadedInternal((char *)&g_zFileName.eHideTempStatus, (struct Resource_s **)igi2_frame.zFilename) == false )
  {
    Game_MPRunNetwork(v10);
    v13 = File_Load((char *)&g_zFileName.eHideTempStatus, (unsigned int *)igi2_frame.zFilename);
    if ( v13 )
    {
      v12 = Resource_ParseFile(File_zLastSubstitutedPath, v13, *(unsigned int *)igi2_frame.zFilename);
      goto LABEL_18;
    }
    LDebug_Error("Failed to load resource: '%s'", (char *)&g_zFileName.eHideTempStatus);
LABEL_11:
    abort();
  }
  v11 = *(_DWORD *)igi2_frame.zFilename;
  *(_DWORD *)(*(_DWORD *)igi2_frame.zFilename + 44) = 1;
  v12 = *(void **)(v11 + 52);
LABEL_18:
  ptMenuManager->pxMenusResource2 = v12;
  v14 = &igi2_frame.zFilename[3];
  while ( *++v14 )
    ;
  strcpy(v14, "/missionsprites");
  Resource_DirList(igi2_frame.zMenuResourceDir, MenuManager_ResourceCallbackHandler, ptMenuManager);
  MenuManager_LoadLanguageResourceFile(ptMenuManager, (char *)&g_zFileName.tQTask.tQTaskChildren.ptTail);
  MenuManager_LoadLanguageResourceFile(ptMenuManager, (char *)&g_zFileName);
  return result;
}

// source: j/0/menusystem/menumanager.c:1403  [anchor-caller]
void __cdecl MenuManager_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  enum InputPortDevice_e v2; // ecx
  unsigned __int16 v3; // ax
  struct QTask_s *v4; // eax
  struct ClippingRect_s tClippingRect; // [esp+10h] [ebp-18h] BYREF

  MenuManager_ptQTask = ptQTask;
  Symbol_Register(
    "MenuManager_RequestScreen",
    MenuManager_RequestScreenCB,
    ptQTask,
    2,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "MenuManager_LeaveMenus",
    MenuManager_LeaveMenusCB,
    ptQTask,
    3,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "MenuManager_ClearStack",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))MenuManager_ClearStackCB,
    ptQTask,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "MenuManager_SetLanguage",
    MenuManager_SetLanguageCB,
    ptQTask,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "MenuManager_PushScreen",
    MenuManager_PushScreenCB,
    ptQTask,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "MenuManager_PopScreen",
    MenuManager_PopScreenCB,
    ptQTask,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "MenuManager_ForceUpdateWindow",
    MenuManager_ForceUpdateWindowCB,
    ptQTask,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "MenuManager_ActivatePopupScreen",
    MenuManager_ActivatePopupScreenCB,
    ptQTask,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "MenuManager_DeactivatePopuScreen",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))MenuManager_DeactivatePopupScreenCB,
    ptQTask,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "MenuManager_SetEnabled",
    MenuManager_EnableCB,
    ptQTask,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "MENUMANAGER_QUIT",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)0xB,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "MENUMANAGER_QUITTOMAINMENU",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)0xC,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "MENUMANAGER_STARTGAME",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)0xE,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "MENUMANAGER_JOINGAME",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)0xF,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "MENUMANAGER_IDLE",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)0xA,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    (char *)&g_zSpriteName.tQTaskChildren.ptMiddle,
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)0xD,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  BYTE2(ptQTask[243].tQTaskRefList.ptTail) = 0;
  if ( Keyboard_tKeyboard.isConnected )
  {
    v2 = INPUTPORT_DEVICE_NONE;
    if ( Mouse_tMouse.isConnected )
      v2 = INPUTPORT_DEVICE_MOUSE;
    InputPort_Init(
      INPUTPORT_0,
      Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tInputOptions.nRemapButton,
      Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tInputOptions.atRemapButtonTable,
      v2,
      0.05000000074505806,
      0.0033333334140479565,
      0.0033333334140479565,
      0.25,
      0.0033333334140479565,
      0.0033333334140479565,
      0.05000000074505806,
      0.0033333334140479565,
      0.0033333334140479565,
      0.25,
      0.0033333334140479565,
      0.0033333334140479565);
    InputPort_atInputPort[0].isActive = true;
  }
  tKeyboardBuffer.iBufferIndex = 0;
  tKeyboardBuffer.nBuffer = 0;
  tKeyboardBuffer.isKeyboardActive = 1;
  tKeyboardBuffer.isFreezeEscape = 0;
  Main_RegisterWinProcCallback(KeyInterface_WinProcHandler);
  BYTE2(ptQTask[243].tQTaskRefList.ptTail) = 1;
  tClippingRect.vWidth = (float)Display_tActiveMode.nWidth;
  tClippingRect.vX = 0.0;
  tClippingRect.vY = 0.0;
  tClippingRect.vHeight = (float)Display_tActiveMode.nHeight;
  RenderContext_Alloc((struct RenderContext_s *)&ptQTask[241].tQTaskRefList.ptTail, 1);
  RenderContext_SetClippingRect((struct RenderContext_s *)&ptQTask[241].tQTaskRefList.ptTail, &tClippingRect);
  v3 = Cursor_eQTaskType;
  ptQTask[1].ptNext = (struct QTask_s *)-1;
  ptQTask[1].ptPrev = (struct QTask_s *)-1;
  ptQTask[9].ptPrev = nullptr;
  ptQTask[1].tQTaskRefList.ptHead = nullptr;
  ptQTask[1].tQTaskRefList.ptMiddle = nullptr;
  LOBYTE(ptQTask[243].tQTaskRefList.ptTail) = 0;
  BYTE1(ptQTask[243].tQTaskRefList.ptTail) = 0;
  LOBYTE(ptQTask[250].tQTaskRefList.ptHead) = 0;
  LOBYTE(ptQTask[9].tQTaskChildren.ptHead) = 0;
  ptQTask[15].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[15].tQTaskRefList.ptTail = nullptr;
  ptQTask[19].ptNext = nullptr;
  LOWORD(ptQTask[241].tQTaskRefList.ptHead) = 0;
  HIWORD(ptQTask[241].tQTaskRefList.ptHead) = 0;
  HIBYTE(ptQTask[243].tQTaskRefList.ptTail) = 0;
  ptQTask[1].tQTaskRefList.ptTail = nullptr;
  LOWORD(ptQTask[241].tQTaskRefList.ptMiddle) = 0;
  v4 = QTask_NewFn(nullptr, v3, ptQTask);
  ptQTask[251].ptNext = nullptr;
  ptQTask[251].tQTaskChildren.ptHead = nullptr;
  ptQTask[9].ptNext = nullptr;
  *(_DWORD *)&ptQTask[255].eQTaskType = 0;
  ptQTask[255].ptParent = nullptr;
  ptQTask[1].tQTaskChildren.ptHead = (struct QTask_s *)-1;
  HIBYTE(ptQTask[243].eQTaskType) = 0;
  ptQTask[250].tQTaskChildren.ptTail = v4;
  LOBYTE(ptQTask[243].eQTaskType) = 1;
}

// source: j/0/menusystem/menumanager.c:1523  [anchor-caller]
void __cdecl MenuManager_DeleteHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptParent; // eax
  struct QReference_s *v2; // eax
  int v3; // ecx
  struct QReference_s *v4; // eax
  void (__cdecl *pfHandler)(struct QTask_s *); // eax
  struct QTask_s *ptPrev; // eax
  int v7; // esi
  struct QTask_s *ptNext; // eax
  int v9; // esi
  unsigned __int8 tOldBackgroundColor; // [esp+10h] [ebp-Ch]
  unsigned __int8 tOldBackgroundColor_4; // [esp+14h] [ebp-8h]
  unsigned __int8 tOldBackgroundColor_8; // [esp+18h] [ebp-4h]

  ptParent = ptQTask[255].ptParent;
  if ( ptParent )
  {
    QReference_Delete((struct QReference_s *)ptParent, &QTask_tQTaskRefPool);
    ptQTask[255].ptParent = nullptr;
  }
  v2 = *(struct QReference_s **)&ptQTask[255].eQTaskType;
  if ( v2 )
  {
    QReference_Delete(v2, &QTask_tQTaskRefPool);
    *(_DWORD *)&ptQTask[255].eQTaskType = 0;
  }
  if ( LOBYTE(ptQTask[252].eQTaskType) )
    SoundSys_ClearPlayList();
  if ( BYTE2(ptQTask[243].tQTaskRefList.ptTail) )
  {
    KeyInterface_Close();
    BYTE2(ptQTask[243].tQTaskRefList.ptTail) = 0;
  }
  QTask_Delete(ptQTask[250].tQTaskChildren.ptTail);
  MenuManager_FreeResources((struct MenuManager_s *)ptQTask);
  RenderContext_DeAlloc((struct RenderContext_s *)&ptQTask[241].tQTaskRefList.ptTail);
  if ( (int)ptQTask[243].tQTaskRefList.ptMiddle > -1 )
  {
    tOldBackgroundColor_8 = Display_tBackgroundColor.nZ;
    tOldBackgroundColor = Display_tBackgroundColor.nX;
    tOldBackgroundColor_4 = Display_tBackgroundColor.nY;
    Display_tBackgroundColor.nX = 0;
    Display_tBackgroundColor.nY = 0;
    Display_tBackgroundColor.nZ = 0;
    if ( Display_isModeSet )
      RenderMode_tActiveRenderMode.apfRenderModeMethod[Display_eClearMethod](nullptr);
    Display_tBackgroundColor.nX = tOldBackgroundColor;
    Display_tBackgroundColor.nY = tOldBackgroundColor_4;
    Display_tBackgroundColor.nZ = tOldBackgroundColor_8;
    Flow_SetFrequency((int)ptQTask[243].tQTaskRefList.ptMiddle);
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
      goto LABEL_21;
  }
  if ( v3 >= 0 )
  {
    pfHandler = (void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[Level_eRemoveLevelScriptSymbolsEvent][ptQTask->eQTaskType].pfHandler;
    if ( pfHandler )
      pfHandler(ptQTask);
  }
LABEL_21:
  ptPrev = ptQTask[9].ptPrev;
  if ( ptPrev )
  {
    v7 = *(_DWORD *)((unsigned int)&ptPrev[-1].eQTaskType & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v7);
    memset(*(void **)(v7 + 8), 0xCDu, *(_DWORD *)(v7 + 16));
    free((void *)v7);
    ptQTask[9].ptPrev = nullptr;
  }
  ptNext = ptQTask[9].ptNext;
  if ( ptNext )
  {
    v9 = *(_DWORD *)((unsigned int)&ptNext[-1].eQTaskType & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v9);
    memset(*(void **)(v9 + 8), 0xCDu, *(_DWORD *)(v9 + 16));
    free((void *)v9);
    ptQTask[9].ptNext = nullptr;
  }
  Symbol_Remove("MenuManager_RequestScreen");
  Symbol_Remove("MenuManager_LeaveMenus");
  Symbol_Remove("MenuManager_SetLanguage");
  Symbol_Remove("MenuManager_ClearStack");
  Symbol_Remove("MenuManager_PushScreen");
  Symbol_Remove("MenuManager_PopScreen");
  Symbol_Remove("MenuManager_ForceUpdateWindow");
  Symbol_Remove("MenuManager_ActivatePopupScreen");
  Symbol_Remove("MenuManager_DeactivatePopuScreen");
  Symbol_Remove("MenuManager_SetEnabled");
  Symbol_Remove("MENUMANAGER_QUIT");
  Symbol_Remove("MENUMANAGER_QUITTOMAINMENU");
  Symbol_Remove("MENUMANAGER_IDLE");
  Symbol_Remove((char *)&g_zSpriteName.tQTaskChildren.ptMiddle);
  Symbol_Remove("MENUMANAGER_STARTGAME");
  Symbol_Remove("MENUMANAGER_JOINGAME");
  MenuManager_ptQTask = nullptr;
}

// source: j/0/menusystem/menumanager.c:1617  [anchor-caller]
void __cdecl MenuManager_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *ptNext; // eax
  struct QReference_s *v3; // eax
  struct QReference_s *pxObject; // eax

  ptNext = ptQTask[1].ptNext;
  if ( (unsigned int)ptNext < 0x1000 && (v3 = Level_atLevelQTaskID[(_DWORD)ptNext]) != nullptr )
    pxObject = (struct QReference_s *)v3->pxObject;
  else
    pxObject = nullptr;
  ptQTask[1].tQTaskRefList.ptHead = pxObject;
  if ( pxContext && *(_DWORD *)pxContext )
  {
    MenuManager_LoadResources((struct MenuManager_s *)ptQTask);
  }
  else if ( pxObject )
  {
    ((void (__cdecl *)(struct QReference_s *))QTask_aatQTaskFinalEvent[MenuWindow_eFormatEvent][LOWORD(pxObject[3].ptNext)].pfHandler)(pxObject);
  }
  ptQTask[250].tQTaskChildren.ptTail[1].tQTaskRefList.ptHead = (struct QReference_s *)MenuManager_GetSprite(
                                                                                        ptQTask,
                                                                                        (char *)&g_zSpriteName);
  ptQTask[251].ptPrev = (struct QTask_s *)Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eLanguage;
}

// source: j/0/menusystem/menumanager.c:1666  [anchor-callee]
int __cdecl MenuManager_GetDefaultMenuID(struct QTask_s *ptQTask)
{
  struct QTask_s *ptPrev; // edx
  int result; // eax
  struct QReference_s *v3; // ecx

  ptPrev = ptQTask[9].ptPrev;
  if ( !ptPrev )
    return -1;
  if ( !strlen((char *)ptQTask[9].ptPrev) )
    return -1;
  result = Script_ParseLineInt32((char *)ptPrev);
  if ( (unsigned int)result >= 0x1000 )
    return -1;
  v3 = Level_atLevelQTaskID[result];
  if ( !v3 || !v3->pxObject )
    return -1;
  return result;
}

// source: j/0/menusystem/menumanager.c:1690  [anchor-caller]
void __cdecl MenuManager_UpdateInternalDataAfterLoadHandler(struct QTask_s *ptQTask)
{
  int DefaultMenuID; // eax
  struct QReference_s *v2; // eax

  DefaultMenuID = MenuManager_GetDefaultMenuID(ptQTask);
  if ( DefaultMenuID >= 0 )
  {
    ptQTask[1].ptNext = (struct QTask_s *)DefaultMenuID;
    if ( DefaultMenuID < 4096 && (v2 = Level_atLevelQTaskID[DefaultMenuID]) != nullptr )
      ptQTask[1].tQTaskRefList.ptHead = (struct QReference_s *)v2->pxObject;
    else
      ptQTask[1].tQTaskRefList.ptHead = nullptr;
  }
}

// source: j/0/menusystem/menumanager.c:1714  [size]
void __cdecl MenuManager_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = MenuManager_ptParameterList;
}

// source: j/0/menusystem/menumanager.c:1730  [anchor-mhash]
struct Result_s *__cdecl MenuManager_GetActiveMenuScreen(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  struct QReference_s *ptHead; // edx
  int v4; // ecx
  struct QReference_s *v5; // eax
  int v6; // ecx
  struct QReference_s *v7; // eax
  struct Result_s Rs; // [esp+Ch] [ebp-18h] BYREF

  if ( MenuManager_ptQTask && (ptHead = MenuManager_ptQTask[1].tQTaskRefList.ptHead) != nullptr )
  {
    v4 = 0;
    while ( 1 )
    {
      v5 = Level_atLevelQTaskID[v4];
      if ( v5 )
      {
        if ( v5->pxObject == ptHead )
          break;
      }
      if ( ++v4 >= 4096 )
      {
        Rs.nResult = -1;
        goto LABEL_8;
      }
    }
    Rs.nResult = v4;
LABEL_8:
    v6 = 0;
    while ( 1 )
    {
      v7 = Level_atLevelQTaskID[v6];
      if ( v7 )
      {
        if ( v7->pxObject == ptHead )
          break;
      }
      if ( ++v6 >= 4096 )
      {
        Rs.vResult = (double)-1;
        goto LABEL_16;
      }
    }
    Rs.vResult = (double)v6;
  }
  else
  {
    Rs.nResult = -1;
    Rs.vResult = -1.0;
  }
LABEL_16:
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/menusystem/menumanager.c:1750  [anchor-caller]
void __cdecl MenuManager_RunHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptNext; // eax
  struct QTask_s *v2; // edx
  struct QReference_s *ptHead; // edx
  struct QTask_s *ptMiddle; // eax
  BOOL v5; // edx
  struct QTask_s *v6; // eax
  struct QTask_s *DefaultMenuID; // eax
  struct QTask_s *v8; // ecx
  struct QTask_s *ptParent; // eax
  struct QTask_s *v10; // eax
  struct QTask_s *ptTail; // eax
  struct QReference_s *v12; // ecx
  int v13; // ecx
  struct QReference_s *v14; // eax
  struct QReference_s *v15; // eax

  if ( AppContext_tAppContext.isDebugged && ptQTask[1].tQTaskChildren.ptMiddle != (struct QTask_s *)20 )
  {
    if ( ptQTask[1].tQTaskRefList.ptHead )
      MenuManager_UpdateKeyboardHandling((struct MenuManager_s *)ptQTask);
    if ( LOBYTE(ptQTask[252].eQTaskType) && HIBYTE(ptQTask[243].tQTaskRefList.ptTail) )
      MenuManager_PlayMusic(ptQTask);
    ptNext = ptQTask[251].ptNext;
    if ( ptNext )
      ((void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[1][ptNext->eQTaskType].pfHandler)(ptQTask[251].ptNext);
    ((void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[1][ptQTask[250].tQTaskChildren.ptTail->eQTaskType].pfHandler)(ptQTask[250].tQTaskChildren.ptTail);
    if ( BYTE2(ptQTask[243].ptParent) )
    {
      if ( memcmp(&ptQTask[250].tQTaskRefList, &unk_717CEC, 0x14u)
        || ptQTask[1].tQTaskRefList.ptTail != (struct QReference_s *)dword_717CE8
        || ptQTask[1].tQTaskRefList.ptHead != (struct QReference_s *)dword_717CE0
        || tKeyboardBuffer.nBuffer
        || HIBYTE(ptQTask[243].ptParent)
        || ptQTask[251].tQTaskChildren.ptHead )
      {
        dword_717CDC = 0;
      }
      else
      {
        v2 = ptQTask[9].ptNext;
        if ( v2 && Script_ParseLineInt32((char *)v2) && dword_717CDC > 3600 )
        {
          QTask_Delete(ptQTask);
          Flow_ptFlow->eRequestedEvent = 9;
          dword_717CDC = 0;
          return;
        }
        ++dword_717CDC;
      }
      qmemcpy(&unk_717CEC, &ptQTask[250].tQTaskRefList, 0x14u);
      ptHead = ptQTask[1].tQTaskRefList.ptHead;
      dword_717CE8 = (int)ptQTask[1].tQTaskRefList.ptTail;
      dword_717CE0 = (int)ptHead;
      HIBYTE(ptQTask[243].ptParent) = 0;
    }
    ptMiddle = ptQTask[1].tQTaskChildren.ptMiddle;
    if ( ptMiddle != (struct QTask_s *)10 )
      dword_717D00 = 0;
    switch ( (unsigned int)ptMiddle )
    {
      case 0u:
      case 1u:
        MenuManager_ActivateScreen(ptQTask, (int)ptQTask[1].ptNext, (enum bool)(ptMiddle == nullptr));
        ptQTask[1].tQTaskChildren.ptMiddle = (struct QTask_s *)6;
        ptQTask[8].ptParent = nullptr;
        ptQTask[8].tQTaskRefList.ptMiddle = nullptr;
        ptQTask[8].tQTaskRefList.ptTail = nullptr;
        return;
      case 2u:
        MenuManager_ActivateScreen(ptQTask, (int)ptQTask[1].ptNext, true);
        ptQTask[1].tQTaskChildren.ptMiddle = (struct QTask_s *)6;
        ptQTask[8].ptParent = (struct QTask_s *)16;
        ptQTask[8].tQTaskRefList.ptMiddle = (struct QReference_s *)16;
        ptQTask[8].tQTaskRefList.ptTail = (struct QReference_s *)16;
        return;
      case 3u:
        MenuManager_HandleKeyboard((struct MenuManager_s *)ptQTask);
        if ( LOBYTE(ptQTask[243].eQTaskType) )
        {
          ptTail = ptQTask[250].tQTaskChildren.ptTail;
          ptQTask[250].ptParent = ptTail[1].ptPrev;
          *(_DWORD *)&ptQTask[250].eQTaskType = ptTail[1].tQTaskChildren.ptHead;
          v12 = ptTail[1].tQTaskRefList.ptTail;
          LOBYTE(ptTail) = v12 != ptTail[1].tQTaskRefList.ptMiddle;
          BYTE1(ptQTask[250].tQTaskRefList.ptHead) = (unsigned __int8)v12 & (unsigned __int8)ptTail;
          LOBYTE(ptQTask[250].tQTaskRefList.ptHead) = (_BYTE)v12;
          BYTE2(ptQTask[250].tQTaskRefList.ptHead) = (unsigned __int8)ptTail & (v12 == nullptr);
          v13 = *(_DWORD *)&ptQTask[250].eQTaskType;
          ptQTask[250].ptParent = (struct QTask_s *)((char *)ptQTask[250].ptParent
                                                   + 320
                                                   - (Display_tActiveMode.nWidth >> 1));
          *(_DWORD *)&ptQTask[250].eQTaskType = 240 - (Display_tActiveMode.nHeight >> 1) + v13;
        }
        goto LABEL_63;
      case 4u:
        BYTE1(ptQTask[250].tQTaskRefList.ptHead) = 0;
        BYTE2(ptQTask[250].tQTaskRefList.ptHead) = 0;
        LOBYTE(ptQTask[250].tQTaskRefList.ptHead) = 0;
        goto LABEL_63;
      case 5u:
        MenuManager_UpdateLanguage((struct MenuManager_s *)ptQTask, 0);
        ptQTask[1].tQTaskChildren.ptMiddle = (struct QTask_s *)6;
        ptQTask[8].ptParent = nullptr;
        ptQTask[8].tQTaskRefList.ptMiddle = nullptr;
        ptQTask[8].tQTaskRefList.ptTail = nullptr;
        return;
      case 6u:
      case 8u:
        ptParent = ptQTask[8].ptParent;
        if ( ptParent != (struct QTask_s *)16 )
          ptQTask[8].ptParent = (struct QTask_s *)((char *)&ptParent->ptNext + (BYTE1(ptQTask[243].ptParent) == 0) + 1);
        if ( ptQTask[8].tQTaskRefList.ptTail == (struct QReference_s *)16 )
        {
          ptQTask[1].tQTaskChildren.ptMiddle = (struct QTask_s *)3;
          tKeyboardBuffer.iBufferIndex = 0;
          tKeyboardBuffer.nBuffer = 0;
        }
        return;
      case 7u:
      case 9u:
        v10 = ptQTask[8].ptParent;
        if ( v10 )
          ptQTask[8].ptParent = (struct QTask_s *)((char *)v10 - (BYTE1(ptQTask[243].ptParent) == 0) - 1);
        if ( !ptQTask[8].tQTaskRefList.ptTail )
        {
          ptQTask[1].tQTaskChildren.ptMiddle = ptQTask[1].tQTaskChildren.ptTail;
          MenuManager_DeactivatePopupScreen((struct MenuManager_s *)ptQTask);
        }
        return;
      case 0xAu:
        v5 = (Keyboard_tKeyboard.anCurrentKey[1] & 0x80u) != 0 && (Keyboard_tKeyboard.anPreviousKey[1] & 0x80) == 0;
        if ( LevelFlow_LevelFailed() == false || LOBYTE(Game_GetPlayerQTask(0)[29].tQTaskRefList.ptHead) )
          goto LABEL_37;
        if ( dword_717D00 > 150 )
        {
          dword_717D00 = 0;
LABEL_38:
          v6 = MenuManager_ptQTask;
          ptQTask[1].tQTaskRefList.ptHead = nullptr;
          LOBYTE(v6[243].eQTaskType) = 1;
          DefaultMenuID = (struct QTask_s *)MenuManager_GetDefaultMenuID(ptQTask);
          v8 = MenuManager_ptQTask;
          MenuManager_ptQTask[1].ptNext = DefaultMenuID;
          v8[1].tQTaskChildren.ptMiddle = nullptr;
          if ( Game_IsPaused() == false )
            Game_SetPaused(true);
          return;
        }
        ++dword_717D00;
LABEL_37:
        if ( v5 )
          goto LABEL_38;
        if ( Game_IsPaused() )
          Game_SetPaused(false);
        break;
      case 0xBu:
        QTask_Delete(ptQTask);
        Flow_ptFlow->eRequestedEvent = 1;
        return;
      case 0xCu:
        NetManager_LeaveGame();
        NetManager_Quit();
        ptQTask[1].tQTaskChildren.ptMiddle = (struct QTask_s *)10;
        return;
      case 0xDu:
        Flow_ptFlow->eRequestedEvent = 5;
        ptQTask[1].tQTaskChildren.ptMiddle = (struct QTask_s *)10;
        return;
      case 0xEu:
        QTask_Delete(ptQTask);
        Flow_ptFlow->eRequestedEvent = 4;
        return;
      case 0xFu:
        QTask_Delete(ptQTask);
        Flow_ptFlow->eRequestedEvent = 10;
        return;
      case 0x10u:
        MenuManager_ActivatePopupScreen((struct MenuManager_s *)ptQTask);
        ptQTask[1].tQTaskChildren.ptMiddle = (struct QTask_s *)8;
        ptQTask[8].ptParent = nullptr;
        ptQTask[8].tQTaskRefList.ptTail = nullptr;
        ptQTask[8].tQTaskRefList.ptMiddle = nullptr;
        return;
      case 0x11u:
        ptQTask[1].tQTaskChildren.ptMiddle = (struct QTask_s *)3;
        ptQTask[8].ptParent = (struct QTask_s *)16;
        ptQTask[8].tQTaskRefList.ptTail = (struct QReference_s *)16;
        ptQTask[8].tQTaskRefList.ptMiddle = (struct QReference_s *)16;
        return;
      case 0x12u:
        return;
      case 0x13u:
        ptQTask[1].tQTaskChildren.ptMiddle = (struct QTask_s *)10;
        return;
      default:
LABEL_63:
        v14 = ptQTask[1].tQTaskRefList.ptMiddle;
        if ( v14 )
        {
          ((void (__cdecl *)(struct QReference_s *))QTask_aatQTaskFinalEvent[1][LOWORD(v14[3].ptNext)].pfHandler)(ptQTask[1].tQTaskRefList.ptMiddle);
          ptQTask[250].tQTaskChildren.ptTail[1].ptParent = nullptr;
        }
        else
        {
          v15 = ptQTask[1].tQTaskRefList.ptHead;
          if ( v15 )
            ((void (__cdecl *)(struct QReference_s *))QTask_aatQTaskFinalEvent[1][LOWORD(v15[3].ptNext)].pfHandler)(ptQTask[1].tQTaskRefList.ptHead);
          ptQTask[250].tQTaskChildren.ptTail[1].ptParent = nullptr;
        }
        return;
    }
  }
}

// source: j/0/menusystem/menumanager.c:2071  [anchor-mhash]
void __cdecl MenuManager_DrawHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptMiddle; // eax
  struct QReference_s *v2; // eax
  struct QReference_s *ptHead; // ecx
  struct QTask_s *v4; // eax
  struct QTask_s *ptParent; // ecx

  ptMiddle = ptQTask[1].tQTaskChildren.ptMiddle;
  if ( ptMiddle != (struct QTask_s *)20 )
  {
    if ( ptQTask[1].tQTaskRefList.ptHead && ptMiddle != (struct QTask_s *)10 )
    {
      qmemcpy(
        &RenderContext_tActiveRenderContext,
        &ptQTask[241].tQTaskRefList.ptTail,
        sizeof(RenderContext_tActiveRenderContext));
      ++RenderContext_nActiveRenderContextTimeStamp;
      ptQTask[241].ptParent = nullptr;
      ptQTask[241].tQTaskRefList.ptTail = nullptr;
      List_AddTail(&ptQTask[241].tQTaskRefList.ptTail, (int)&RenderContext_tDrawList);
      if ( ptQTask[1].tQTaskChildren.ptMiddle == (struct QTask_s *)3 && LOBYTE(ptQTask[243].eQTaskType) )
        ((void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[Screen_eDrawQTaskEvent][ptQTask[250].tQTaskChildren.ptTail->eQTaskType].pfHandler)(ptQTask[250].tQTaskChildren.ptTail);
      v2 = ptQTask[1].tQTaskRefList.ptMiddle;
      if ( v2 )
      {
        *(_DWORD *)&ptQTask[8].eQTaskType = ptQTask[8].ptParent;
        ((void (__cdecl *)(struct QReference_s *))QTask_aatQTaskFinalEvent[Screen_eDrawQTaskEvent][LOWORD(v2[3].ptNext)].pfHandler)(v2);
      }
      ptHead = ptQTask[1].tQTaskRefList.ptHead;
      if ( ptHead )
      {
        v4 = ptQTask[1].tQTaskChildren.ptMiddle;
        if ( v4 == (struct QTask_s *)8 || v4 == (struct QTask_s *)9 || v4 == (struct QTask_s *)17 )
          *(_DWORD *)&ptQTask[8].eQTaskType = 16;
        else
          *(_DWORD *)&ptQTask[8].eQTaskType = ptQTask[8].ptParent;
        ((void (__cdecl *)(struct QReference_s *))QTask_aatQTaskFinalEvent[Screen_eDrawQTaskEvent][LOWORD(ptHead[3].ptNext)].pfHandler)(ptHead);
      }
    }
    ptParent = ptQTask[8].ptParent;
    ptQTask[8].tQTaskRefList.ptTail = ptQTask[8].tQTaskRefList.ptMiddle;
    ptQTask[8].tQTaskRefList.ptMiddle = (struct QReference_s *)ptParent;
  }
}

// source: j/0/menusystem/menumanager.c:2133  [size]
void __cdecl MenuManager_RegisterScriptSymbolsHandler(struct QTask_s *ptQTask)
{
  if ( !BYTE1(ptQTask[243].tQTaskRefList.ptTail) )
    BYTE1(ptQTask[243].tQTaskRefList.ptTail) = 1;
}

// source: j/0/menusystem/menumanager.c:2152  [size]
void __cdecl MenuManager_RemoveScriptSymbolsHandler(struct QTask_s *ptQTask)
{
  if ( BYTE1(ptQTask[243].tQTaskRefList.ptTail) )
    BYTE1(ptQTask[243].tQTaskRefList.ptTail) = 0;
}

// source: j/0/menusystem/menumanager.c:2175  [size]
void __cdecl MenuManager_Delete(struct QTask_s *ptQTask)
{
  QTask_Delete(ptQTask);
}

// source: j/0/menusystem/menumanager.c:2189  [anchor-callee]
struct StaticTilemap_s *__cdecl MenuManager_GetPicture(
        struct QTask_s *ptQTask,
        char *zPictureName)
{
  int v2; // esi
  char *i; // edi

  v2 = 0;
  if ( SLOWORD(ptQTask[241].tQTaskRefList.ptMiddle) <= 0 )
    return nullptr;
  for ( i = (char *)&ptQTask[187].ptPrev; _stricmp(zPictureName, i); i += 68 )
  {
    if ( ++v2 >= SLOWORD(ptQTask[241].tQTaskRefList.ptMiddle) )
      return nullptr;
  }
  return *((struct StaticTilemap_s **)&ptQTask[188].tQTaskRefList.ptTail + 17 * v2);
}

// source: j/0/menusystem/menumanager.c:2221  [anchor-callee]
struct QSprite_s *__cdecl MenuManager_GetSprite(struct QTask_s *ptQTask, char *zSpriteName)
{
  int v2; // esi
  char *i; // edi

  v2 = 0;
  if ( SLOWORD(ptQTask[241].tQTaskRefList.ptHead) <= 0 )
    return nullptr;
  for ( i = (char *)&ptQTask[46].tQTaskChildren.ptMiddle; _stricmp(zSpriteName, i); i += 88 )
  {
    if ( ++v2 >= SLOWORD(ptQTask[241].tQTaskRefList.ptHead) )
      return nullptr;
  }
  return (struct QSprite_s *)(&ptQTask[47].eQTaskType + 44 * v2);
}

// source: j/0/menusystem/menumanager.c:2253  [anchor-callee]
struct QSprite_s *__cdecl MenuManager_GetFont(struct QTask_s *ptQTask, char *zFontName)
{
  int v2; // esi
  char *i; // edi

  v2 = 0;
  if ( SHIWORD(ptQTask[241].tQTaskRefList.ptHead) <= 0 )
    return nullptr;
  for ( i = (char *)&ptQTask[19].ptPrev; _stricmp(zFontName, i); i += 68 )
  {
    if ( ++v2 >= SHIWORD(ptQTask[241].tQTaskRefList.ptHead) )
      return nullptr;
  }
  return *((struct QSprite_s **)&ptQTask[20].tQTaskRefList.ptTail + 17 * v2);
}

// source: j/0/menusystem/menumanager.c:2285  [size]
struct MenuInputContext_t *__cdecl MenuManager_GetInputContext(struct QTask_s *ptQTask)
{
  return (struct MenuInputContext_t *)&ptQTask[250].tQTaskRefList;
}

// source: j/0/menusystem/menumanager.c:2301  [size]
struct QTask_s *__cdecl MenuManager_Pause(struct QTask_s *ptQTask)
{
  ptQTask[1].tQTaskChildren.ptMiddle = (struct QTask_s *)4;
  return ptQTask;
}

// source: j/0/menusystem/menumanager.c:2317  [size]
struct QTask_s *__cdecl MenuManager_Unpause(struct QTask_s *ptQTask)
{
  ptQTask[1].tQTaskChildren.ptMiddle = (struct QTask_s *)3;
  return ptQTask;
}

// source: j/0/menusystem/menumanager.c:2333  [size]
void __cdecl MenuManager_SetSelectedWindow(struct QTask_s *ptQTask, struct QTask_s *ptSelectedWindow)
{
  struct QTask_s *v3; // ecx
  struct QTask_s **i; // edx
  struct QReference_s *ptTail; // edx
  int v6; // ecx
  struct QHashTable_s *v7; // esi
  unsigned int v8; // eax
  struct Sample_s *v9; // edx
  unsigned int v10; // ecx
  struct SoundModify_t ptModify; // [esp+8h] [ebp-64h] BYREF

  v3 = nullptr;
  if ( (int)ptQTask[8].tQTaskChildren.ptHead > 0 )
  {
    for ( i = &ptQTask[1].ptParent; *i != ptSelectedWindow; ++i )
    {
      v3 = (struct QTask_s *)((char *)v3 + 1);
      if ( (int)v3 >= (int)ptQTask[8].tQTaskChildren.ptHead )
        return;
    }
    ptTail = ptQTask[1].tQTaskRefList.ptTail;
    if ( ptTail != (struct QReference_s *)ptSelectedWindow )
    {
      if ( ptTail )
        BYTE1(ptTail[7].ptNext) = 0;
      ptQTask[8].tQTaskChildren.ptTail = v3;
      v6 = *((_DWORD *)&ptQTask[1].ptParent + (_DWORD)v3);
      ptQTask[1].tQTaskRefList.ptTail = (struct QReference_s *)v6;
      if ( v6 )
        *(_BYTE *)(v6 + 85) = 1;
      if ( !SoundSys_isSoundDisabled )
      {
        v7 = Sound_ptSampleHashTable;
        v8 = Sound_ptSampleHashTable->tPrivate.pfHashFunction(
               Sound_ptSampleHashTable->tPrivate.nHashTableSize,
               &g_zFileName.aptSelectableItems[22]);
        v9 = (struct Sample_s *)((int  (__cdecl *)(struct QHashTable_s *, unsigned int, const void *))Sound_ptSampleHashTable->tPrivate.pfFindElement)(v7, v8, (const void *)(&g_zFileName.aptSelectableItems[22]));
        Sound_DefaultSoundModify(&ptModify);
        v10 = SoundSys_nCurrentID++;
        SoundSys_AddSoundToRequestlist(v10, v9, 1u, &ptModify);
      }
    }
  }
}

// source: j/0/menusystem/menumanager.c:2364  [size]
int __cdecl MenuManager_GetFadeCount(struct QTask_s *ptQTask)
{
  return *(_DWORD *)&ptQTask[8].eQTaskType;
}

// source: j/0/menusystem/menumanager.c:2377  [size]
struct QTask_s *__cdecl MenuManager_GetBackgroundFXTask(struct QTask_s *ptQTask)
{
  return ptQTask[251].ptNext;
}

// source: j/0/menusystem/menumanager.c:2392  [size]
void __cdecl MenuManager_SetActiveMenuAndState(
        int nMenuID,
        enum MenuManagerStatus_e eState)
{
  struct QTask_s *v2; // eax

  v2 = MenuManager_ptQTask;
  MenuManager_ptQTask[1].ptNext = (struct QTask_s *)nMenuID;
  v2[1].tQTaskChildren.ptMiddle = (struct QTask_s *)eState;
}

// source: j/0/menusystem/menumanager.c:2415  [size]
void __cdecl MenuManager_SetActiveMenu(int nMenuID)
{
  struct QTask_s *v1; // eax

  v1 = MenuManager_ptQTask;
  MenuManager_ptQTask[1].ptNext = (struct QTask_s *)nMenuID;
  v1[1].tQTaskChildren.ptMiddle = nullptr;
}

// source: j/0/menusystem/menumanager.c:2428  [size]
int __cdecl MenuManager_GetActiveMenu()
{
  return (int)MenuManager_ptQTask[1].ptNext;
}

// source: j/0/menusystem/menumanager.c:2446  [anchor-hash]
enum bool __cdecl MenuManager_IsInGameMenuEnabled()
{
  return MenuManager_ptQTask && MenuManager_ptQTask[1].tQTaskChildren.ptMiddle != (struct QTask_s *)10;
}

// source: j/0/menusystem/menumanager.c:2473  [size]
int __cdecl MenuManager_RunLevelExpressionInt(
        struct LevelExpression_s *ptLevelExpression,
        struct QTask_s *ptQTask)
{
  struct QExpression_s *ptExpression; // ecx
  int result; // eax

  ptExpression = ptLevelExpression->ptExpression;
  result = 0;
  if ( ptExpression )
    return Expression_EvalInt(ptExpression);
  return result;
}

// source: j/0/menusystem/menumanager.c:2496  [anchor-hash]
struct QTask_s *__cdecl MenuManager_FormatActiveScreen(struct QTask_s *ptQTask)
{
  struct QTask_s *result; // eax

  result = (struct QTask_s *)ptQTask[1].tQTaskRefList.ptHead;
  if ( result )
    return (struct QTask_s *)((int (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[MenuWindow_eFormatEvent][result->eQTaskType].pfHandler)(result);
  return result;
}

// source: j/0/menusystem/menumanager.c:2515  [size]
struct QTask_s *__cdecl MenuManager_GetCaptureKeyboardQTask(struct QTask_s *ptQTask)
{
  struct QTask_s *ptParent; // eax

  ptParent = ptQTask[255].ptParent;
  if ( ptParent )
    return ptParent->tQTaskChildren.ptHead;
  else
    return nullptr;
}

// source: j/0/menusystem/menumanager.c:2533  [size]
void __cdecl MenuManager_SetCaptureKeyboardQTask(
        struct QTask_s *ptQTask,
        struct QTask_s *ptCaptureQTask)
{
  struct QTask_s *ptParent; // eax

  ptParent = ptQTask[255].ptParent;
  if ( ptParent )
  {
    QReference_Delete((struct QReference_s *)ptParent, &QTask_tQTaskRefPool);
    ptQTask[255].ptParent = nullptr;
  }
  if ( ptCaptureQTask )
    ptQTask[255].ptParent = (struct QTask_s *)QTask_NewQTaskRef(ptCaptureQTask);
}

// source: j/0/menusystem/menumanager.c:2555  [size]
struct QTask_s *__cdecl MenuManager_ResetDemoModeTimer(struct QTask_s *ptQTask)
{
  HIBYTE(ptQTask[243].ptParent) = 1;
  return ptQTask;
}

// source: j/0/menusystem/menumanager.c:2571  [size]
void __cdecl MenuManager_EnableNavigation(enum bool isEnable)
{
  LOBYTE(MenuManager_ptQTask[243].eQTaskType) = isEnable;
}

// source: j/0/menusystem/menumanager.c:2587  [size]
unsigned __int16 __cdecl MenuManager_GetQTaskType()
{
  return MenuManager_eQTaskType;
}

// source: j/0/menusystem/menumanager.c:2600  [size]
struct QTask_s *__cdecl MenuManager_GetQTask()
{
  return MenuManager_ptQTask;
}

// source: j/0/menusystem/menumanager.c:2613  [anchor-callee]
struct QTask_s *__cdecl MenuManager_New(
        struct QTask_s *ptParent,
        char *zMenuTaskPath,
        enum bool isSetScreenResolution,
        enum bool isRunning,
        enum bool isDemoMode)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct UpdateInternalDataContext_s tUpdateInternalDataContext; };
    struct { char igi2_o1[4]; struct DisplayMode_s tDisplayMode; };
    char igi2_extent[300];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v5; // edx
  char *v6; // ecx
  char *v7; // ecx
  struct Script_s *v8; // esi
  struct QTask_s *FirstChildOfType; // edi

  if ( isSetScreenResolution )
  {
    v5 = 2752 * Config_tConfig.iActiveProfile + 7392072;
    memset(&igi2_frame.tDisplayMode, 0, sizeof(igi2_frame.tDisplayMode));
    v6 = (char *)(2752 * Config_tConfig.iActiveProfile + 7392400);
    igi2_frame.tDisplayMode.nWidth = 640;
    igi2_frame.tDisplayMode.nHeight = 480;
    igi2_frame.tDisplayMode.nBitsPerPixel = 16;
    igi2_frame.tDisplayMode.nBackBuffers = 1;
    igi2_frame.tDisplayMode.eRenderMode = Direct3D_eRenderMode;
    igi2_frame.tDisplayMode.isZBuffer = 1;
    igi2_frame.tDisplayMode.isCleared = 1;
    if ( 2752 * Config_tConfig.iActiveProfile == -7392400 )
      v6 = (char *)&g_zInitialValue;
    strcpy(igi2_frame.tDisplayMode.zDeviceDescription, v6);
    v7 = (char *)(v5 + 72);
    if ( v5 == -72 )
      v7 = (char *)&g_zInitialValue;
    strcpy(igi2_frame.tDisplayMode.zDeviceIdentifier, v7);
    if ( !Screen_isDisplayModeRequested )
    {
      qmemcpy(&Screen_tRequestedDisplayMode, &igi2_frame.tDisplayMode, sizeof(Screen_tRequestedDisplayMode));
      Screen_isFullscreen = 0;
      Screen_isDisplayModeRequested = 1;
    }
    Display_SetMode(&igi2_frame.tDisplayMode);
    Config_SetGameToCurrentPerformanceLevel();
  }
  v8 = Script_New(zMenuTaskPath);
  if ( !v8 )
  {
    LDebug_Error("Failed to load menumanager: '%s'", zMenuTaskPath);
    abort();
  }
  Level_zScriptfile = zMenuTaskPath;
  Level_isLegalTask = 1;
  Level_nLinenumber = 0;
  Level_isFirstChild = 0;
  Level_ptRootQTask = nullptr;
  Script_SetSymbolContext("Task_New", ptParent);
  Script_Execute(v8);
  Script_Delete(v8);
  FirstChildOfType = QTask_GetFirstChildOfType(ptParent, MenuManager_eQTaskType);
  strcpy(&FirstChildOfType[243].isInMemPool, zMenuTaskPath);
  igi2_frame.tUpdateInternalDataContext.isFirstFrame = true;
  QTask_TriggerQTaskEventRecursively(ptParent, ParameterList_eUpdateInternalDataQTaskEvent, &igi2_frame.tUpdateInternalDataContext);
  igi2_frame.tUpdateInternalDataContext.isFirstFrame = false;
  QTask_TriggerQTaskEventRecursivelyNoContext(FirstChildOfType, Level_eUpdateInternalDataAfterLoadEvent);
  FirstChildOfType[1].tQTaskChildren.ptMiddle = isRunning != false ? nullptr : (struct QTask_s *)0xA;
  if ( isSetScreenResolution )
  {
    FirstChildOfType[243].tQTaskRefList.ptMiddle = (struct QReference_s *)Flow_ptFlow->nFrequency;
    Flow_SetFrequency(60);
    LOBYTE(FirstChildOfType[252].eQTaskType) = 1;
  }
  else
  {
    FirstChildOfType[243].tQTaskRefList.ptMiddle = (struct QReference_s *)-1;
    LOBYTE(FirstChildOfType[252].eQTaskType) = 0;
  }
  BYTE2(FirstChildOfType[243].ptParent) = isDemoMode;
  FirstChildOfType[253].ptPrev = nullptr;
  return FirstChildOfType;
}

// source: j/0/menusystem/menumanager.c:2726  [size]
enum bool __cdecl MenuManager_IsCursorMoved(struct QTask_s *ptQTask)
{
  return (enum bool)ptQTask[250].tQTaskChildren.ptTail[1].ptParent;
}

// source: j/0/menusystem/menumanager.c:2744  [size]
struct QTask_s *__cdecl MenuManager_ResetCursorMoved(struct QTask_s *ptQTask)
{
  ptQTask[250].tQTaskChildren.ptTail[1].ptParent = nullptr;
  return ptQTask;
}

// source: j/0/menusystem/menumanager.c:2762  [size]
enum MenuManagerStatus_e __cdecl MenuManager_GetStatus()
{
  return (enum MenuManagerStatus_e)MenuManager_ptQTask[1].tQTaskChildren.ptMiddle;
}

// source: j/0/menusystem/menumanager.c:2779  [size]
enum bool __cdecl MenuManager_IsNavigationEnabled()
{
  return SLOBYTE(MenuManager_ptQTask[243].eQTaskType);
}

// source: j/0/menusystem/menumanager.c:2797  [size]
int __cdecl MenuManager_GetActiveGameLanguage(struct QTask_s *ptQTask)
{
  return (int)ptQTask[251].ptPrev;
}

// source: j/0/menusystem/menumanager.c:2815  [size]
struct QTask_s *__cdecl MenuManager_GetCaptureMouseWheelQTask(struct QTask_s *ptQTask)
{
  int v1; // eax

  v1 = *(_DWORD *)&ptQTask[255].eQTaskType;
  if ( v1 )
    return *(struct QTask_s **)(v1 + 8);
  else
    return nullptr;
}

// source: j/0/menusystem/menumanager.c:2833  [size]
void __cdecl MenuManager_SetCaptureMouseWheelQTask(
        struct QTask_s *ptQTask,
        struct QTask_s *ptCaptureQTask)
{
  struct QReference_s *v2; // eax

  v2 = *(struct QReference_s **)&ptQTask[255].eQTaskType;
  if ( v2 )
  {
    QReference_Delete(v2, &QTask_tQTaskRefPool);
    *(_DWORD *)&ptQTask[255].eQTaskType = 0;
  }
  if ( ptCaptureQTask )
    *(_DWORD *)&ptQTask[255].eQTaskType = QTask_NewQTaskRef(ptCaptureQTask);
}

// source: j/0/menusystem/menumanager.c:2855  [anchor-hash]
struct QTask_s *__cdecl MenuManager_GotoNextTAB(struct QTask_s *ptQTask)
{
  struct QReference_s *ptTail; // ecx
  struct QTask_s *ptMiddle; // edx
  struct QReference_s *v3; // ecx
  struct QReference_s *v4; // edx
  struct QTask_s *v5; // ecx
  int v6; // ecx

  if ( ptQTask[8].tQTaskChildren.ptMiddle )
  {
    ptTail = ptQTask[1].tQTaskRefList.ptTail;
    if ( ptTail )
    {
      BYTE1(ptTail[7].ptNext) = 0;
      ptQTask[1].tQTaskRefList.ptTail = nullptr;
      ptQTask[8].tQTaskRefList.ptHead = nullptr;
      ptQTask = ptQTask[5].ptNext;
      HIBYTE(ptQTask[2].ptPrev) = 1;
    }
    else
    {
      *(_BYTE *)(*((_DWORD *)&ptQTask[5].ptNext + (int)ptQTask[8].tQTaskRefList.ptHead) + 87) = 0;
      ptMiddle = ptQTask[8].tQTaskChildren.ptMiddle;
      v3 = (struct QReference_s *)((char *)&ptQTask[8].tQTaskRefList.ptHead->ptNext + 1);
      ptQTask[8].tQTaskRefList.ptHead = v3;
      if ( (int)v3 >= (int)ptMiddle )
      {
        v4 = ptQTask[1].tQTaskRefList.ptTail;
        v5 = ptQTask[8].tQTaskChildren.ptTail;
        if ( v4 )
          BYTE1(v4[7].ptNext) = 0;
        ptQTask[8].tQTaskChildren.ptTail = v5;
        v6 = *((_DWORD *)&ptQTask[1].ptParent + (_DWORD)v5);
        ptQTask[1].tQTaskRefList.ptTail = (struct QReference_s *)v6;
        if ( v6 )
          *(_BYTE *)(v6 + 85) = 1;
        ptQTask[8].tQTaskRefList.ptHead = nullptr;
      }
      else
      {
        ptQTask = *(&ptQTask[5].ptNext + (_DWORD)v3);
        HIBYTE(ptQTask[2].ptPrev) = 1;
      }
    }
  }
  return ptQTask;
}

// source: j/0/menusystem/menumanager.c:2896  [anchor-hash]
struct QTask_s *__cdecl MenuManager_ExitTAB(struct QTask_s *ptQTask)
{
  struct QReference_s *ptTail; // edx
  struct QTask_s *v2; // ecx
  int v3; // ecx

  if ( ptQTask[8].tQTaskChildren.ptMiddle )
  {
    *(_BYTE *)(*((_DWORD *)&ptQTask[5].ptNext + (int)ptQTask[8].tQTaskRefList.ptHead) + 87) = 0;
    ptTail = ptQTask[1].tQTaskRefList.ptTail;
    v2 = ptQTask[8].tQTaskChildren.ptTail;
    if ( ptTail )
      BYTE1(ptTail[7].ptNext) = 0;
    ptQTask[8].tQTaskChildren.ptTail = v2;
    v3 = *((_DWORD *)&ptQTask[1].ptParent + (_DWORD)v2);
    ptQTask[1].tQTaskRefList.ptTail = (struct QReference_s *)v3;
    if ( v3 )
      *(_BYTE *)(v3 + 85) = 1;
    ptQTask[8].tQTaskRefList.ptHead = nullptr;
  }
  return ptQTask;
}

// source: j/0/menusystem/menumanager.c:2919  [anchor-mhash]
void __cdecl MenuManager_Hide(enum bool isHide)
{
  struct QTask_s *v1; // eax
  struct QTask_s *ptMiddle; // ecx

  v1 = MenuManager_ptQTask;
  if ( MenuManager_ptQTask )
  {
    if ( isHide )
    {
      ptMiddle = MenuManager_ptQTask[1].tQTaskChildren.ptMiddle;
      if ( ptMiddle != (struct QTask_s *)20 )
      {
        MenuManager_ptQTask[1].tQTaskChildren.ptHead = ptMiddle;
        v1[1].tQTaskChildren.ptMiddle = (struct QTask_s *)20;
      }
    }
    else if ( MenuManager_ptQTask[1].tQTaskChildren.ptMiddle == (struct QTask_s *)20 )
    {
      MenuManager_ptQTask[1].tQTaskChildren.ptMiddle = MenuManager_ptQTask[1].tQTaskChildren.ptHead;
    }
  }
}

// source: j/0/menusystem/menumanager.c:2952  [size]
void __cdecl MenuManager_DisableFading(enum bool isDisable)
{
  if ( MenuManager_ptQTask )
    HIBYTE(MenuManager_ptQTask[243].eQTaskType) = isDisable;
}

// source: j/0/menusystem/menumanager.c:2971  [anchor-caller]
void __cdecl MenuManager_Open()
{
  unsigned __int16 BaseQTaskType; // ax
  unsigned __int16 v1; // si
  struct ParameterList_s *v2; // eax
  int v3; // edx

  File_RegisterAlias("MENUSYS:", "LOCAL:menusystem/");
  BaseQTaskType = QTask_GetBaseQTaskType();
  v1 = QTask_NewQTaskType("MenuManager", 10240, BaseQTaskType, 0, 0);
  MenuManager_eQTaskType = v1;
  QTask_LinkQTaskEventHandlerFn(
    v1,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveHandler);
  QTask_LinkQTaskEventHandlerFn(v1, 0, MenuManager_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 2, MenuManager_DeleteHandler);
  QTask_LinkQTaskEventHandlerFn(
    v1,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))MenuManager_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(v1, ParameterList_eUpdateInternalDataQTaskEvent, MenuManager_UpdateInternalDataHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 1, MenuManager_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, Screen_eDrawQTaskEvent, MenuManager_DrawHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(
    v1,
    Level_eUpdateInternalDataAfterLoadEvent,
    MenuManager_UpdateInternalDataAfterLoadHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(
    v1,
    Level_eRegisterLevelScriptSymbolsEvent,
    (void (__cdecl *)(struct QTask_s *))MenuManager_RegisterScriptSymbolsHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(
    v1,
    Level_eRemoveLevelScriptSymbolsEvent,
    (void (__cdecl *)(struct QTask_s *))MenuManager_RemoveScriptSymbolsHandler);
  v2 = (struct ParameterList_s *)Mem_AllocFn(152, 4);
  v3 = Level_eParameterTypePushButton;
  v2->ptParameterListItem = (struct ParameterListItem_s *)&v2[1];
  v2->nParameters = 0;
  v2->nMaxParameters = 7;
  MenuManager_ptParameterList = v2;
  ParameterList_AddParameter(v2, 0x2614u, v3, "Save", 6u, nullptr);
  ParameterList_AddParameter(
    MenuManager_ptParameterList,
    0x16Cu,
    Level_eParameterTypeVarString,
    "Default menuscreen expression",
    7u,
    nullptr);
  ParameterList_AddParameter(
    MenuManager_ptParameterList,
    0x28u,
    Level_eParameterTypeInt32,
    "Current menuscreen",
    7u,
    nullptr);
  ParameterList_AddParameter(
    MenuManager_ptParameterList,
    0x170u,
    Level_eParameterTypeString256,
    "Resource path",
    7u,
    nullptr);
  ParameterList_AddParameter(
    MenuManager_ptParameterList,
    0x261Eu,
    Level_eParameterTypeString256,
    "Task path",
    6u,
    nullptr);
  ParameterList_AddParameter(
    MenuManager_ptParameterList,
    0x2619u,
    Level_eParameterTypebool8,
    "isOwnDisplay",
    7u,
    nullptr);
  ParameterList_AddParameter(
    MenuManager_ptParameterList,
    0x168u,
    Level_eParameterTypeVarString,
    "Enable demo expression",
    7u,
    nullptr);
  Level_AllocQTaskRangeForQTaskType(MenuManager_eQTaskType, 900, 1000);
  Symbol_Register(
    "MenuManager_GetActiveMenuScreen",
    MenuManager_GetActiveMenuScreen,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
}

// source: j/0/menusystem/menumanager.c:3019  [anchor-hash]
void __cdecl MenuManager_Close()
{
  int v0; // esi

  Symbol_Remove("MenuManager_GetActiveMenuScreen");
  if ( MenuManager_ptParameterList )
  {
    v0 = *(_DWORD *)((unsigned int)&MenuManager_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
  QTask_DeleteQTaskType(MenuManager_eQTaskType);
  MenuManager_eQTaskType = 512;
}
