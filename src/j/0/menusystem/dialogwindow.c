/* j/0/menusystem/dialogwindow.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/menusystem/dialogwindow.c:62  [anchor-mhash]
struct DialogWindow_t *__cdecl DialogWindow_DrawFrame(
        struct DialogWindow_t *ptDialogWindow,
        float vFade)
{
  float v3; // edi
  struct DialogWindow_t *result; // eax
  float vAlphaTop; // [esp+0h] [ebp-38h]
  float vAlphaTopa; // [esp+0h] [ebp-38h]
  float vY0; // [esp+24h] [ebp-14h]
  float vX0; // [esp+28h] [ebp-10h]
  float vY2; // [esp+2Ch] [ebp-Ch]
  float vY2a; // [esp+2Ch] [ebp-Ch]
  float vY1; // [esp+30h] [ebp-8h]
  float vX1; // [esp+34h] [ebp-4h]
  float ptDialogWindowa = *(float *)&vFade; // [esp+3Ch] [ebp+4h] ARGSLOT

  vX0 = (double)((Display_tActiveMode.nWidth >> 1) - 320) + (double)ptDialogWindow->tMenuWindow.nXPos;
  vY0 = (double)((Display_tActiveMode.nHeight >> 1) - 240) + (double)ptDialogWindow->tMenuWindow.nYPos;
  vX1 = (double)ptDialogWindow->tMenuWindow.nWidth + vX0;
  vY1 = (double)ptDialogWindow->tMenuWindow.nHeight + vY0;
  vY2 = vY0 + 20.0;
  v3 = vY2;
  MenuScreen_DrawBorder(vX0, vY0, vX1, vY1, vY2, vFade, 0.20000000298023224, 0.05000000074505806, false, false);
  MenuScreen_DrawBackground(vX0, vY0, vX1, vY1, vY2, vFade, 0.20000000298023224, 0.05000000074505806, 1.0, 0.0, false);
  vY2a = vFade * 0.10000000149011612;
  vAlphaTop = vFade * 0.009999999776482582;
  MenuScreen_DrawBackground(vX0, vY0, vX1, vY1, v3, vFade, vAlphaTop, vY2a, 1.0, 1.0, false);
  vAlphaTopa = vFade * 0.8999999761581421;
  MenuScreen_DrawBackground(vX0, vY0, vX1, vY1, v3, vFade, vAlphaTopa, vY2a, 0.10000000149011612, 0.10000000149011612, true);
  ptDialogWindowa = vFade * 0.6000000238418579;
  MenuScreen_DrawBackground(vX0, vY0, vX1, vY1, v3, vFade, ptDialogWindowa, ptDialogWindowa, 0.0, 0.0, true);
  return result;
}

// source: j/0/menusystem/dialogwindow.c:93  [anchor-mhash]
void __cdecl DialogWindow_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ((void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[0][MenuWindow_eQTaskType].pfHandler)(
    ptQTask,
    pxContext);
  ptQTask[1].tQTaskRefList.ptTail = (struct QReference_s *)1;
  ptQTask[1].ptParent = (struct QTask_s *)1;
  LOBYTE(ptQTask[2].ptPrev) = 0;
  LOBYTE(ptQTask[2].tQTaskChildren.ptTail) = 0;
  ptQTask[2].tQTaskChildren.ptMiddle = nullptr;
  BYTE1(ptQTask[2].tQTaskChildren.ptTail) = 1;
}

// source: j/0/menusystem/dialogwindow.c:121  [size]
void __cdecl DialogWindow_DeleteHandler(struct QTask_s *ptQTask)
{
  ((void (__cdecl *)())QTask_aatQTaskFinalEvent[Level_eRemoveLevelScriptSymbolsEvent][ptQTask->eQTaskType].pfHandler)(ptQTask);
}

// source: j/0/menusystem/dialogwindow.c:139  [size]
void __cdecl DialogWindow_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ((void (__cdecl *)())QTask_aatQTaskFinalEvent[ParameterList_eUpdateInternalDataQTaskEvent][MenuWindow_eQTaskType].pfHandler)(ptQTask, pxContext);
}

// source: j/0/menusystem/dialogwindow.c:159  [size]
void __cdecl DialogWindow_RunHandler(struct QTask_s *ptQTask)
{
  ((void (__cdecl *)())QTask_aatQTaskFinalEvent[1][MenuWindow_eQTaskType].pfHandler)(ptQTask);
}

// source: j/0/menusystem/dialogwindow.c:181  [anchor-mhash]
void __cdecl DialogWindow_DrawHandler(struct QTask_s *ptQTask)
{
  double v2; // st7
  float ptQTaska = *(float *)&ptQTask; // [esp+8h] [ebp+4h] ARGSLOT

  v2 = (double)*(int *)(*(_DWORD *)&ptQTask[1].eQTaskType + 356) * 0.125;
  if ( v2 >= 1.0 )
    ptQTaska = 1.0;
  else
    ptQTaska = v2;
  ((void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[Screen_eDrawQTaskEvent][MenuWindow_eQTaskType].pfHandler)(ptQTask);
  DialogWindow_DrawFrame((struct DialogWindow_t *)ptQTask, ptQTaska);
}

// source: j/0/menusystem/dialogwindow.c:208  [size]
void __cdecl DialogWindow_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = DialogWindow_ptParameterList;
}

// source: j/0/menusystem/dialogwindow.c:224  [size]
void __cdecl DialogWindow_InitDataHandler(struct QTask_s *ptQTask)
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

// source: j/0/menusystem/dialogwindow.c:238  [size]
void __cdecl DialogWindow_ChangeDataHandler(struct QTask_s *ptQTask)
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

// source: j/0/menusystem/dialogwindow.c:252  [size]
void __cdecl DialogWindow_RegisterScriptSymbolsHandler(struct QTask_s *ptQTask)
{
  ;
}

// source: j/0/menusystem/dialogwindow.c:283  [size]
void __cdecl DialogWindow_RemoveScriptSymbolsHandler(struct QTask_s *ptQTask)
{
  ;
}

// source: j/0/menusystem/dialogwindow.c:316  [anchor-hash]
void __cdecl DialogWindow_Open()
{
  unsigned __int16 v0; // si
  struct ParameterList_s *v1; // eax
  int v2; // edx

  dword_79EF500 = 0;
  dword_79EF504 = 0;
  dword_79EF508 = 0;
  dword_79EF50C = 1082392576;
  v0 = QTask_NewQTaskType("DialogWindow", 100, MenuWindow_eQTaskType, 0, 0);
  DialogWindow_eQTaskType = v0;
  QTask_LinkQTaskEventHandlerFn(
    v0,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 1, (void (__cdecl *)(struct QTask_s *))DialogWindow_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, Screen_eDrawQTaskEvent, DialogWindow_DrawHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 2, DialogWindow_DeleteHandler);
  QTask_LinkQTaskEventHandlerFn(v0, 0, DialogWindow_CreateHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))DialogWindow_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    ParameterList_eUpdateInternalDataQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))DialogWindow_UpdateInternalDataHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, MenuWindow_eInitDataEvent, DialogWindow_InitDataHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, MenuWindow_eChangeDataEvent, DialogWindow_ChangeDataHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(
    v0,
    Level_eRegisterLevelScriptSymbolsEvent,
    (void (__cdecl *)(struct QTask_s *))DialogWindow_RegisterScriptSymbolsHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(
    v0,
    Level_eRemoveLevelScriptSymbolsEvent,
    (void (__cdecl *)(struct QTask_s *))DialogWindow_RemoveScriptSymbolsHandler);
  v1 = (struct ParameterList_s *)Mem_AllocFn(112, 4);
  v2 = Level_eParameterTypeInt32;
  v1->ptParameterListItem = (struct ParameterListItem_s *)&v1[1];
  v1->nParameters = 0;
  v1->nMaxParameters = 5;
  DialogWindow_ptParameterList = v1;
  ParameterList_AddParameter(v1, 0x28u, v2, "X-Pos", 7u, &dword_79EF500);
  ParameterList_AddParameter(
    DialogWindow_ptParameterList,
    0x2Cu,
    Level_eParameterTypeInt32,
    "Y-Pos",
    7u,
    &dword_79EF500);
  ParameterList_AddParameter(
    DialogWindow_ptParameterList,
    0x30u,
    Level_eParameterTypeInt32,
    "Width",
    7u,
    &dword_79EF500);
  ParameterList_AddParameter(
    DialogWindow_ptParameterList,
    0x34u,
    Level_eParameterTypeInt32,
    "Height",
    7u,
    &dword_79EF500);
  ParameterList_AddParameter(
    DialogWindow_ptParameterList,
    0x61u,
    Level_eParameterTypebool8,
    "SwapKeys",
    7u,
    &dword_79EF500);
}

// source: j/0/menusystem/dialogwindow.c:363  [size]
void __cdecl DialogWindow_Close()
{
  int v0; // esi

  if ( DialogWindow_ptParameterList )
  {
    v0 = *(_DWORD *)((unsigned int)&DialogWindow_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
  QTask_DeleteQTaskType(DialogWindow_eQTaskType);
  DialogWindow_eQTaskType = 512;
}

// source: j/0/menusystem/dialogwindow.c:383  [size]
int __cdecl DialogWindow_UseLeftRight(struct QTask_s *ptQTask)
{
  return SBYTE1(ptQTask[2].tQTaskChildren.ptTail);
}
