/* j/0/menusystem/menubutton.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/menusystem/menubutton.c:41  [anchor-mhash]
void __cdecl MenuButton_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ((void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[0][MenuWindow_eQTaskType].pfHandler)(
    ptQTask,
    pxContext);
  *(_DWORD *)&ptQTask[3].eQTaskType = 0;
  LOBYTE(ptQTask[2].tQTaskChildren.ptMiddle) = 0;
  ptQTask[1].ptNext = (struct QTask_s *)320;
  ptQTask[1].ptPrev = (struct QTask_s *)240;
}

// source: j/0/menusystem/menubutton.c:64  [size]
void __cdecl MenuButton_DeleteHandler(struct QTask_s *ptQTask)
{
  ;
}

// source: j/0/menusystem/menubutton.c:79  [anchor-mhash]
void __cdecl MenuButton_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *v2; // ebx
  struct QSprite_s *Sprite; // eax

  v2 = *(struct QTask_s **)&ptQTask[1].eQTaskType;
  if ( v2 )
  {
    Sprite = MenuManager_GetSprite(v2, (char *)&ptQTask[2].tQTaskChildren.ptMiddle);
    *(_DWORD *)&ptQTask[3].eQTaskType = Sprite;
    if ( Sprite )
    {
      ptQTask[1].tQTaskChildren.ptHead = (struct QTask_s *)Sprite->atQAnimframe[Sprite->nQAnimframes].nWidth;
      ptQTask[1].tQTaskChildren.ptMiddle = (struct QTask_s *)Sprite->atQAnimframe[Sprite->nQAnimframes].nHeight;
    }
    else
    {
      ptQTask[1].tQTaskChildren.ptHead = nullptr;
      ptQTask[1].tQTaskChildren.ptMiddle = nullptr;
    }
  }
  ((void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[ParameterList_eUpdateInternalDataQTaskEvent][MenuWindow_eQTaskType].pfHandler)(
    ptQTask,
    pxContext);
}

// source: j/0/menusystem/menubutton.c:123  [anchor-mhash]
void __cdecl MenuButton_RunHandler(struct QTask_s *ptQTask)
{
  MenuWindow_HitTest(
    (struct MenuWindow_t *)ptQTask,
    (int)ptQTask[1].ptNext,
    (int)ptQTask[1].ptPrev,
    (int)ptQTask[1].tQTaskChildren.ptHead,
    (int)ptQTask[1].tQTaskChildren.ptMiddle,
    nullptr,
    nullptr);
}

// source: j/0/menusystem/menubutton.c:150  [anchor-mhash]
void __cdecl MenuButton_DrawHandler(struct QTask_s *ptQTask)
{
  double v2; // st7
  struct QSprite_s *v3; // ecx
  float ptQSprite; // [esp+0h] [ebp-28h]
  float vX; // [esp+4h] [ebp-24h]
  float ptQTaska = *(float *)&ptQTask; // [esp+2Ch] [ebp+4h] ARGSLOT

  v2 = (double)(*(_DWORD *)(*(_DWORD *)&ptQTask[1].eQTaskType + 356) - 8) * 0.125;
  if ( v2 <= 0.0 )
    ptQTaska = 0.0;
  else
    ptQTaska = v2;
  ((void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[Screen_eDrawQTaskEvent][MenuWindow_eQTaskType].pfHandler)(ptQTask);
  v3 = *(struct QSprite_s **)&ptQTask[3].eQTaskType;
  if ( v3 )
  {
    vX = (float)((unsigned int)&ptQTask[1].ptPrev[-6] + (Display_tActiveMode.nHeight >> 1));
    ptQSprite = (float)((unsigned int)&ptQTask[1].ptNext[-8] + (Display_tActiveMode.nWidth >> 1));
    QSprite_RegisterAZ(v3, ptQSprite, vX, 128.0, 128.0, 128.0, ptQTaska, 1.0, 0, 0x80000u, 0);
  }
}

// source: j/0/menusystem/menubutton.c:193  [size]
void __cdecl MenuButton_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = MenuButton_ptParameterList;
}

// source: j/0/menusystem/menubutton.c:212  [anchor-hash]
void __cdecl MenuButton_Open()
{
  unsigned __int16 v0; // si
  struct ParameterList_s *v1; // eax
  int v2; // edx

  v0 = QTask_NewQTaskType("MenuButton", 160, MenuWindow_eQTaskType, 0, 0);
  MenuButton_eQTaskType = v0;
  QTask_LinkQTaskEventHandlerFn(
    v0,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 1, MenuButton_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, Screen_eDrawQTaskEvent, MenuButton_DrawHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 2, (void (__cdecl *)(struct QTask_s *))MenuButton_DeleteHandler);
  QTask_LinkQTaskEventHandlerFn(v0, 0, MenuButton_CreateHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))MenuButton_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(v0, ParameterList_eUpdateInternalDataQTaskEvent, MenuButton_UpdateInternalDataHandler);
  v1 = (struct ParameterList_s *)Mem_AllocFn(32, 4);
  v1->ptParameterListItem = (struct ParameterListItem_s *)&v1[1];
  v2 = Level_eParameterTypeString32;
  v1->nParameters = 0;
  v1->nMaxParameters = 1;
  MenuButton_ptParameterList = v1;
  ParameterList_AddParameter(v1, 0x5Cu, v2, "Sprite Resource", 7u, nullptr);
}

// source: j/0/menusystem/menubutton.c:243  [size]
void __cdecl MenuButton_Close()
{
  int v0; // esi

  if ( MenuButton_ptParameterList )
  {
    v0 = *(_DWORD *)((unsigned int)&MenuButton_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
  QTask_DeleteQTaskType(MenuButton_eQTaskType);
  MenuButton_eQTaskType = 512;
}

// source: j/0/menusystem/menubutton.c:264  [anchor-hash]
struct MenuButton_t *__cdecl MenuButton_New(struct QTask_s *ptParentTask)
{
  return (struct MenuButton_t *)QTask_NewFn(ptParentTask, MenuButton_eQTaskType, ptParentTask);
}

// source: j/0/menusystem/menubutton.c:279  [size]
void __cdecl MenuButton_Delete(struct MenuButton_t *ptMenuButton)
{
  QTask_Delete(&ptMenuButton->tMenuWindow.tQTask);
}
