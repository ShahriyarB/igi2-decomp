/* h/2/breakpoint.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: h/2/breakpoint.c:88  [anchor-hash]
enum bool __cdecl BreakPoint_Enable(enum bool isEnabled)
{
  bool v1; // zf
  char *v2; // eax
  enum bool result; // eax

  BreakPoint_isBreakEnabled = isEnabled;
  v1 = isEnabled == false;
  v2 = (char *)&unk_683BE8;
  if ( v1 )
    v2 = (char *)&unk_683BE4;
  DebugConsole_printf("BreakPoints %sabled.\n", v2);
  return result;
}

// source: h/2/breakpoint.c:102  [anchor-mhash]
void __cdecl BreakPoint_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ptQTask[1].tQTaskRefList.ptMiddle = (struct QReference_s *)-1;
  ptQTask[1].tQTaskRefList.ptHead = (struct QReference_s *)-1;
  ptQTask[1].tQTaskChildren.ptMiddle = (struct QTask_s *)1;
  ptQTask[1].tQTaskChildren.ptTail = nullptr;
  LOBYTE(ptQTask[1].tQTaskRefList.ptTail) = 0;
  ptQTask[1].ptPrev = nullptr;
  ptQTask[1].tQTaskChildren.ptHead = ptQTask;
  ptQTask[1].ptNext = nullptr;
  List_AddTail(&ptQTask[1].ptNext, (int)&BreakPoint_tBreakPointLinkNodeList);
}

// source: h/2/breakpoint.c:125  [size]
void __cdecl BreakPoint_DeleteHandler(struct QTask_s *ptQTask)
{
  Node_Remove(&ptQTask[1]);
}

// source: h/2/breakpoint.c:141  [anchor-hash]
void __cdecl BreakPoint_RunHandler(struct QTask_s *ptQTask)
{
  bool v1; // zf

  v1 = (Keyboard_tKeyboard.anCurrentKey[60] & 0x80u) == 0;
  if ( (Keyboard_tKeyboard.anCurrentKey[60] & 0x80u) != 0 )
  {
    if ( (Keyboard_tKeyboard.anPreviousKey[60] & 0x80) == 0 && BreakPoint_isKeyDown == false )
    {
      BreakPoint_isKeyDown = true;
      if ( (Keyboard_tKeyboard.anCurrentKey[42] & 0x80) != 0 || (Keyboard_tKeyboard.anCurrentKey[54] & 0x80) != 0 )
        BreakPoint_Enable((enum bool)(BreakPoint_isBreakEnabled == false));
    }
    v1 = (Keyboard_tKeyboard.anCurrentKey[60] & 0x80u) == 0;
  }
  if ( v1 )
    BreakPoint_isKeyDown = false;
}

// source: h/2/breakpoint.c:165  [anchor-mhash]
void __cdecl BreakPoint_EnumQTaskEventsCallback(
        struct QTaskEnumerateQTaskEventContext_s *ptQTaskEnumerateQTaskEventContext,
        void *pxContext)
{
  if ( !strcmp((char *)pxContext + 68, ptQTaskEnumerateQTaskEventContext->zName) )
    *((_DWORD *)pxContext + 15) = ptQTaskEnumerateQTaskEventContext->eQTaskEvent;
}

// source: h/2/breakpoint.c:187  [anchor-mhash]
void __cdecl BreakPoint_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QReference_s *ptMiddle; // eax
  struct QReference_s *v3; // eax

  ptQTask[1].tQTaskRefList.ptHead = (struct QReference_s *)-1;
  if ( strlen((char *)&ptQTask[1].tQTaskRefList.ptTail) )
    QTask_EnumerateQTaskEvents(BreakPoint_EnumQTaskEventsCallback, ptQTask);
  if ( (int)ptQTask[1].tQTaskRefList.ptHead < 0 )
    strcpy((char *)&ptQTask[1].tQTaskRefList.ptTail, "(unknown)");
  ptMiddle = ptQTask[1].tQTaskRefList.ptMiddle;
  if ( (unsigned int)ptMiddle >= 0x1000 || (v3 = Level_atLevelQTaskID[(_DWORD)ptMiddle]) == nullptr || !v3->pxObject )
    ptQTask[1].tQTaskRefList.ptMiddle = (struct QReference_s *)-1;
}

// source: h/2/breakpoint.c:215  [size]
void __cdecl BreakPoint_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = BreakPoint_ptParameterList;
}

// source: h/2/breakpoint.c:231  [anchor-strings]
void __cdecl BreakPoint_QTaskEventCallback(struct QTask_s *ptQTask, int iQTaskEvent, void *pxContext)
{
  struct BreakPointLinkNode_s *ptHead; // eax
  struct BreakPointLinkNode_s *ptNext; // ecx
  struct BreakPoint_s *ptBreakPoint; // esi
  unsigned int nQTaskID; // eax
  struct QReference_s *v7; // eax
  struct QTask_s *pxObject; // eax

  if ( BreakPoint_isBreakEnabled )
  {
    ptHead = BreakPoint_tBreakPointLinkNodeList.ptHead;
    ptNext = BreakPoint_tBreakPointLinkNodeList.ptHead->ptNext;
    if ( BreakPoint_tBreakPointLinkNodeList.ptHead->ptNext )
    {
      while ( 1 )
      {
        ptBreakPoint = ptHead->ptBreakPoint;
        if ( ptBreakPoint->isEnabled )
        {
          nQTaskID = ptBreakPoint->nQTaskID;
          if ( nQTaskID < 0x1000 && (v7 = Level_atLevelQTaskID[nQTaskID]) != nullptr )
            pxObject = (struct QTask_s *)v7->pxObject;
          else
            pxObject = nullptr;
          if ( ptQTask == pxObject && ptBreakPoint->nEvent == iQTaskEvent )
            break;
        }
        ptHead = ptNext;
        ptNext = ptNext->ptNext;
        if ( !ptNext )
          return;
      }
      if ( MessageBoxA(nullptr, "BreakPoint reached, press cancel to disable all breakpoints.", "QTask breakpoint", 1u) == 2 )
      {
        BreakPoint_isBreakEnabled = false;
        DebugConsole_printf("BreakPoints %sabled.\n", "dis");
      }
      if ( ptBreakPoint->isOnceOnly )
        ptBreakPoint->isEnabled = 0;
    }
  }
}

// source: h/2/breakpoint.c:277  [size]
unsigned __int16 __cdecl BreakPoint_GetQTaskType()
{
  return BreakPoint_eQTaskType;
}

// source: h/2/breakpoint.c:290  [anchor-hash]
void __cdecl BreakPoint_Open()
{
  unsigned __int16 BaseQTaskType; // ax
  unsigned __int16 v1; // si
  struct ParameterList_s *v2; // eax
  int v3; // edx

  BaseQTaskType = QTask_GetBaseQTaskType();
  v1 = QTask_NewQTaskType("BreakPoint", 324, BaseQTaskType, 0, 0);
  BreakPoint_eQTaskType = v1;
  QTask_LinkQTaskEventHandlerFn(v1, 0, BreakPoint_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 2, BreakPoint_DeleteHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 1, BreakPoint_RunHandler);
  QTask_LinkQTaskEventHandlerFn(v1, ParameterList_eUpdateInternalDataQTaskEvent, BreakPoint_UpdateInternalDataHandler);
  QTask_LinkQTaskEventHandlerFn(
    v1,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))BreakPoint_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(
    v1,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveHandler);
  BreakPoint_tBreakPointLinkNodeList.ptHead = (struct BreakPointLinkNode_s *)&BreakPoint_tBreakPointLinkNodeList.ptMiddle;
  BreakPoint_tBreakPointLinkNodeList.ptTail = (struct BreakPointLinkNode_s *)&BreakPoint_tBreakPointLinkNodeList;
  BreakPoint_tBreakPointLinkNodeList.ptMiddle = nullptr;
  BreakPoint_isBreakEnabled = true;
  DebugConsole_printf("BreakPoints %sabled.\n", "en");
  v2 = (struct ParameterList_s *)Mem_AllocFn(92, 4);
  v2->ptParameterListItem = (struct ParameterListItem_s *)&v2[1];
  v3 = Level_eParameterTypebool8;
  v2->nParameters = 0;
  v2->nMaxParameters = 4;
  BreakPoint_ptParameterList = v2;
  ParameterList_AddParameter(v2, 0x34u, v3, "Enabled", 7u, nullptr);
  ParameterList_AddParameter(BreakPoint_ptParameterList, 0x38u, Level_eParameterTypebool8, "Once", 7u, nullptr);
  ParameterList_AddParameter(BreakPoint_ptParameterList, 0x40u, Level_eParameterTypeInt32, "TaskID", 7u, nullptr);
  ParameterList_AddParameter(BreakPoint_ptParameterList, 0x44u, Level_eParameterTypeString256, "Event", 7u, nullptr);
  BreakPoint_isKeyDown = false;
}

// source: h/2/breakpoint.c:332  [size]
void __cdecl BreakPoint_Close()
{
  int v0; // esi

  if ( BreakPoint_ptParameterList )
  {
    v0 = *(_DWORD *)((unsigned int)&BreakPoint_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
  QTask_DeleteQTaskType(BreakPoint_eQTaskType);
}
