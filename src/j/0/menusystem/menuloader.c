/* j/0/menusystem/menuloader.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/menusystem/menuloader.c:66  [size]
void __cdecl MenuLoader_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  LOBYTE(ptQTask[1].ptNext) = 0;
  BYTE1(ptQTask[7].tQTaskChildren.ptTail) = 0;
  LOBYTE(ptQTask[7].tQTaskChildren.ptTail) = 0;
}

// source: j/0/menusystem/menuloader.c:84  [size]
void __cdecl MenuLoader_DeleteHandler(struct QTask_s *ptQTask)
{
  ;
}

// source: j/0/menusystem/menuloader.c:98  [anchor-caller]
void __cdecl MenuLoader_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct Game_s *v2; // edi
  struct QTask_s *FirstChildOfType; // eax
  struct QTask_s *v4; // esi
  char *v5; // ebx

  v2 = Game_ptGame;
  if ( BYTE1(ptQTask[7].tQTaskChildren.ptTail) || LOBYTE(ptQTask[7].tQTaskChildren.ptTail) )
  {
    FirstChildOfType = QTask_GetFirstChildOfType(Game_ptGame->ptGameScreenQTask, MenuManager_eQTaskType);
    v4 = FirstChildOfType;
    if ( FirstChildOfType )
    {
      Level_ClearQTaskIDRecursive(FirstChildOfType);
      QTask_Delete(v4);
    }
  }
  if ( LOBYTE(ptQTask[7].tQTaskChildren.ptTail) )
  {
    LOBYTE(ptQTask[7].tQTaskChildren.ptTail) = 0;
    v5 = (char *)&ptQTask[1];
    if ( Resource_IsLoadedInternal((char *)&ptQTask[1], nullptr) || File_Exists(v5) )
      MenuManager_New(v2->ptGameScreenQTask, v5, false, true, false);
  }
}

// source: j/0/menusystem/menuloader.c:149  [size]
void __cdecl MenuLoader_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = MenuLoader_ptParameterList;
}

// source: j/0/menusystem/menuloader.c:166  [size]
void __cdecl MenuLoader_RunHandler(struct QTask_s *ptQTask)
{
  ;
}

// source: j/0/menusystem/menuloader.c:183  [anchor-hash]
void __cdecl MenuLoader_Open()
{
  unsigned __int16 BaseQTaskType; // ax
  unsigned __int16 v1; // si
  struct ParameterList_s *v2; // eax
  int v3; // edx

  BaseQTaskType = QTask_GetBaseQTaskType();
  v1 = QTask_NewQTaskType("MenuLoader", 300, BaseQTaskType, 0, 0);
  MenuLoader_eQTaskType = v1;
  QTask_LinkQTaskEventHandlerFn(
    v1,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveHandler);
  QTask_LinkQTaskEventHandlerFn(v1, 0, (void (__cdecl *)(struct QTask_s *, void *))MenuLoader_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 2, (void (__cdecl *)(struct QTask_s *))MenuLoader_DeleteHandler);
  QTask_LinkQTaskEventHandlerFn(
    v1,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))MenuLoader_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(v1, ParameterList_eUpdateInternalDataQTaskEvent, MenuLoader_UpdateInternalDataHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 1, (void (__cdecl *)(struct QTask_s *))MenuLoader_RunHandler);
  v2 = (struct ParameterList_s *)Mem_AllocFn(72, 4);
  v2->ptParameterListItem = (struct ParameterListItem_s *)&v2[1];
  v3 = Level_eParameterTypeString256;
  v2->nParameters = 0;
  v2->nMaxParameters = 3;
  MenuLoader_ptParameterList = v2;
  ParameterList_AddParameter(v2, 0x28u, v3, "Menu task path", 7u, nullptr);
  ParameterList_AddParameter(MenuLoader_ptParameterList, 0x128u, Level_eParameterTypePushButton, "Load", 6u, nullptr);
  ParameterList_AddParameter(MenuLoader_ptParameterList, 0x129u, Level_eParameterTypePushButton, "Delete", 6u, nullptr);
}

// source: j/0/menusystem/menuloader.c:216  [size]
void __cdecl MenuLoader_Close()
{
  int v0; // esi

  if ( MenuLoader_ptParameterList )
  {
    v0 = *(_DWORD *)((unsigned int)&MenuLoader_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
  QTask_DeleteQTaskType(MenuLoader_eQTaskType);
  MenuLoader_eQTaskType = 512;
}
