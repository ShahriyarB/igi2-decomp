/* h/2/animsound.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: h/2/animsound.c:68  [size]
void __cdecl AnimSound_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ;
}

// source: h/2/animsound.c:82  [size]
void __cdecl AnimSound_DeleteHandler(struct QTask_s *ptQTask)
{
  ;
}

// source: h/2/animsound.c:96  [anchor-mhash]
void __cdecl AnimSound_ParseAnimTriggerParametersHandler(struct QTask_s *ptQTask, void *pxContext)
{
  void *v2; // ebp
  int v3; // ebx
  _BYTE *v4; // esi
  struct ArgList_s *v5; // edi
  struct ArgList_s *v6; // edi
  int v7; // ebx

  v2 = pxContext;
  v3 = *((_DWORD *)pxContext + 2);
  v4 = *(_BYTE **)pxContext;
  v5 = *((struct ArgList_s **)pxContext + 1);
  if ( v5->isQVM )
  {
    *v4 = 0;
    QVM_EvalArg(v4, 32, v5, v3, 3);
  }
  else
  {
    Expression_EvalString(v5->aptExpression[v3], v4, 32);
  }
  v6 = *((struct ArgList_s **)v2 + 1);
  v7 = v3 + 1;
  if ( v6->isQVM )
  {
    pxContext = nullptr;
    QVM_EvalArg(&pxContext, 4, v6, v7, 1);
    v4[32] = (_BYTE)pxContext;
  }
  else
  {
    v4[32] = Expression_EvalInt(v6->aptExpression[v7]);
  }
}

// source: h/2/animsound.c:119  [size]
void __cdecl AnimSound_GetAnimTriggerParameterSizeHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = 33;
}

// source: h/2/animsound.c:135  [anchor-mhash]
void __cdecl AnimSound_TriggerAnimTriggerHandler(struct QTask_s *ptQTask, void *pxContext)
{
  int v2; // eax
  struct QTask_s *v3; // eax

  v2 = *((_DWORD *)pxContext + 1);
  if ( *(_BYTE *)(v2 + 32) )
  {
    SoundSys_NewSoundFn(*(struct QTask_s **)pxContext, (char *)v2);
  }
  else
  {
    v3 = SoundSys_NewSoundFn(Level_ptDynamicQTask, (char *)v2);
    if ( v3 )
      ((void (__cdecl *)(struct QTask_s *, _DWORD))QTask_aatQTaskFinalEvent[SoundSys_eSetPositionQTaskEvent][v3->eQTaskType].pfHandler)(
        v3,
        *((_DWORD *)pxContext + 3));
  }
}

// source: h/2/animsound.c:176  [anchor-hash]
void __cdecl AnimSound_Open()
{
  unsigned __int16 BaseQTaskType; // ax
  unsigned __int16 v1; // si

  BaseQTaskType = QTask_GetBaseQTaskType();
  v1 = QTask_NewQTaskType("AnimSound", 44, BaseQTaskType, 0, 0);
  AnimSound_eQTaskType = v1;
  QTask_LinkQTaskEventHandlerFn(v1, 0, (void (__cdecl *)(struct QTask_s *, void *))AnimSound_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 2, (void (__cdecl *)(struct QTask_s *))AnimSound_DeleteHandler);
  QTask_LinkQTaskEventHandlerFn(
    v1,
    AnimTrigger_eGetParseAnimTriggerParametersEvent,
    AnimSound_ParseAnimTriggerParametersHandler);
  QTask_LinkQTaskEventHandlerFn(
    v1,
    AnimTrigger_eGetAnimTriggerParameterSizeQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))AnimSound_GetAnimTriggerParameterSizeHandler);
  QTask_LinkQTaskEventHandlerFn(v1, AnimTrigger_eTriggerAnimTriggerQTaskEvent, AnimSound_TriggerAnimTriggerHandler);
  Symbol_Register(
    "TASKTYPE_ANIMSOUND",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)v1,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
}

// source: h/2/animsound.c:203  [size]
void __cdecl AnimSound_Close()
{
  QTask_DeleteQTaskType(AnimSound_eQTaskType);
}

// source: h/2/animsound.c:217  [size]
unsigned __int16 __cdecl AnimSound_GetQTaskType()
{
  return AnimSound_eQTaskType;
}
