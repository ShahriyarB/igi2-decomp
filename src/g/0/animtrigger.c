/* g/0/animtrigger.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: g/0/animtrigger.c:49  [anchor-mhash]
struct Result_s *__cdecl AnimTrigger_DefineAnimTriggerCB(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  struct ArgList_s *v3; // edi
  struct ArgList_s *v4; // eax
  unsigned __int16 v5; // ax
  int v6; // edx
  int v7; // ecx
  void (__cdecl *pfHandler)(_DWORD, struct ArgList_s **); // eax
  void *v9; // eax
  int v10; // ecx
  int v11; // eax
  struct ParseAnimTriggerParametersContext_s tParseAnimTriggerParametersContext[2]; // [esp+8h] [ebp-18h] BYREF

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
  stru_728708[AnimTrigger_nAnimTriggerType].iID = (int)v4;
  if ( v3->isQVM )
  {
    ptArgList = nullptr;
    QVM_EvalArg(&ptArgList, 4, v3, 1, 1);
    v5 = (unsigned __int16)ptArgList;
  }
  else
  {
    v5 = Expression_EvalInt(v3->aptExpression[1]);
  }
  v6 = 511 * AnimTrigger_eGetAnimTriggerParameterSizeQTaskEvent;
  v7 = AnimTrigger_nAnimTriggerType;
  stru_728708[v7].eQTaskType = v5;
  stru_728708[v7].pxData = nullptr;
  pfHandler = (void (__cdecl *)(_DWORD, struct ArgList_s **))QTask_aatQTaskFinalEvent[0][stru_728708[v7].eQTaskType + v6].pfHandler;
  if ( pfHandler )
  {
    pfHandler(0, &ptArgList);
    v9 = Mem_AllocFn((int)ptArgList, 4);
    v10 = AnimTrigger_nAnimTriggerType;
    stru_728708[v10].pxData = v9;
    tParseAnimTriggerParametersContext[0].pxData = v9;
    v11 = 511 * AnimTrigger_eGetParseAnimTriggerParametersEvent + stru_728708[v10].eQTaskType;
    tParseAnimTriggerParametersContext[0].ptArgList = v3;
    tParseAnimTriggerParametersContext[0].iFirstArg = 2;
    ((void (__cdecl *)(_DWORD, struct ParseAnimTriggerParametersContext_s *))QTask_aatQTaskFinalEvent[0][v11].pfHandler)(
      0,
      tParseAnimTriggerParametersContext);
  }
  ++AnimTrigger_nAnimTriggerType;
  tParseAnimTriggerParametersContext[0].pxData = (void *)1;
  tParseAnimTriggerParametersContext[0].iFirstArg = 0;
  tParseAnimTriggerParametersContext[1].pxData = (void *)1072693248;
  tParseAnimTriggerParametersContext[1].ptArgList = (struct ArgList_s *)&g_zInitialValue;
  qmemcpy(retstr, tParseAnimTriggerParametersContext, sizeof(struct Result_s));
  return retstr;
}

// source: g/0/animtrigger.c:117  [anchor-mhash]
void __cdecl AnimTrigger_ProcessFileCB(
        struct FileDirListCallbackContext_s *tFileDirListCallbackContext,
        void *pxContext)
{
  char *zFilename; // edi
  struct Script_s *v3; // eax
  struct Script_s *v4; // esi

  if ( tFileDirListCallbackContext->isDirectory == false )
  {
    zFilename = tFileDirListCallbackContext->zFilename;
    v3 = Script_New(tFileDirListCallbackContext->zFilename);
    v4 = v3;
    if ( !v3 )
    {
      LDebug_Error("AnimTrigger_ParseConfigFile(): Couldn't load script: %s", zFilename);
      abort();
    }
    Script_Execute(v3);
    Script_Delete(v4);
  }
}

// source: g/0/animtrigger.c:135  [anchor-strings]
void __cdecl AnimTrigger_Open()
{
  AnimTrigger_eTriggerAnimTriggerQTaskEvent = QTask_NewQTaskEventFn(0, "TriggerAnimTrigger");
  AnimTrigger_eGetAnimTriggerParameterSizeQTaskEvent = QTask_NewQTaskEventFn(0, "GetAnimTriggerParameterSize");
  AnimTrigger_eGetParseAnimTriggerParametersEvent = QTask_NewQTaskEventFn(0, "ParseAnimTriggerParameters");
  Symbol_Register(
    "DefineAnimTrigger",
    AnimTrigger_DefineAnimTriggerCB,
    nullptr,
    -1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
}

// source: g/0/animtrigger.c:156  [anchor-hash]
void __cdecl AnimTrigger_Close()
{
  int v0; // ebp
  void **p_pxData; // ebx
  int v2; // esi

  v0 = 0;
  if ( AnimTrigger_nAnimTriggerType > 0 )
  {
    p_pxData = &stru_728708[0].pxData;
    do
    {
      if ( *p_pxData )
      {
        v2 = *(_DWORD *)(((int)*p_pxData - 4) & 0xFFFFFFFC);
        --Mem_nCurrentAllocations;
        Node_Remove((_DWORD **)v2);
        memset(*(void **)(v2 + 8), 0xCDu, *(_DWORD *)(v2 + 16));
        free((void *)v2);
        *p_pxData = nullptr;
      }
      ++v0;
      p_pxData += 3;
    }
    while ( v0 < AnimTrigger_nAnimTriggerType );
  }
  QTask_DeleteQTaskEvent(AnimTrigger_eTriggerAnimTriggerQTaskEvent);
  AnimTrigger_eTriggerAnimTriggerQTaskEvent = 512;
  QTask_DeleteQTaskEvent(AnimTrigger_eGetAnimTriggerParameterSizeQTaskEvent);
  AnimTrigger_eGetAnimTriggerParameterSizeQTaskEvent = 512;
  QTask_DeleteQTaskEvent(AnimTrigger_eGetParseAnimTriggerParametersEvent);
  AnimTrigger_eGetParseAnimTriggerParametersEvent = 512;
}

// source: g/0/animtrigger.c:192  [size]
__int16 __cdecl AnimTrigger_GetTriggerAnimTriggerQTaskEvent()
{
  return AnimTrigger_eTriggerAnimTriggerQTaskEvent;
}

// source: g/0/animtrigger.c:207  [size]
__int16 __cdecl AnimTrigger_GetGetAnimTriggerParameterSizeQTaskEvent()
{
  return AnimTrigger_eGetAnimTriggerParameterSizeQTaskEvent;
}

// source: g/0/animtrigger.c:222  [size]
__int16 __cdecl AnimTrigger_GetParseAnimTriggerParametersQTaskEvent()
{
  return AnimTrigger_eGetParseAnimTriggerParametersEvent;
}

// source: g/0/animtrigger.c:237  [anchor-refs]
void __cdecl AnimTrigger_ParseConfigFile(char *zFile)
{
  struct Script_s *v1; // eax
  struct Script_s *v2; // esi

  v1 = Script_New(zFile);
  v2 = v1;
  if ( !v1 )
  {
    LDebug_Error("AnimTrigger_ParseConfigFile(): Couldn't load script: %s", zFile);
    abort();
  }
  Script_Execute(v1);
  Script_Delete(v2);
}

// source: g/0/animtrigger.c:262  [size]
void __cdecl AnimTrigger_ParseConfigDirectory(char *zDirectory)
{
  int pxContext[2]; // [esp+0h] [ebp-8h] BYREF

  pxContext[0] = (int)AnimTrigger_ProcessFileCB;
  pxContext[1] = 0;
  File_DirList(
    zDirectory,
    (void (__cdecl *)(struct FileDirListCallbackContext_s *, void *))Script_DirListCallback,
    pxContext);
}

// source: g/0/animtrigger.c:276  [anchor-callee]
void __cdecl AnimTrigger_Trigger(int iAnimTrigger, struct QTask_s *ptCreator, struct real64x3_t *ptPos)
{
  int v3; // eax
  struct AnimTriggerType_s *i; // ecx
  int v5; // eax
  int eQTaskType; // edx
  struct TriggerAnimTriggerContext_s tTriggerAnimTriggerContext; // [esp+0h] [ebp-10h] BYREF

  v3 = 0;
  if ( AnimTrigger_nAnimTriggerType > 0 )
  {
    for ( i = stru_728708; i->iID != iAnimTrigger; ++i )
    {
      if ( ++v3 >= AnimTrigger_nAnimTriggerType )
        return;
    }
    v5 = v3;
    tTriggerAnimTriggerContext.pxData = stru_728708[v5].pxData;
    eQTaskType = stru_728708[v5].eQTaskType;
    tTriggerAnimTriggerContext.ptCreator = ptCreator;
    tTriggerAnimTriggerContext.ptPos = ptPos;
    tTriggerAnimTriggerContext.iID = iAnimTrigger;
    ((void (__cdecl *)(_DWORD, struct TriggerAnimTriggerContext_s *))QTask_aatQTaskFinalEvent[AnimTrigger_eTriggerAnimTriggerQTaskEvent][eQTaskType].pfHandler)(
      0,
      &tTriggerAnimTriggerContext);
  }
}
