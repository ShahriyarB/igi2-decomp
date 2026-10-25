/* j/0/objects/conveyorbelt.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/objects/conveyorbelt.c:64  [size]
void __cdecl ConveyorBelt_GetSerializeParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = ConveyorBelt_ptSerializeParameterList;
}

// source: j/0/objects/conveyorbelt.c:88  [anchor-mhash]
struct Result_s *__cdecl ConveyorBelt_SetSpeed(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  struct ArgList_s *v3; // edi
  struct ArgList_s *v4; // eax
  struct QReference_s *v5; // eax
  void *pxObject; // esi
  double v7; // st7
  double v8; // st7
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  v3 = ptArgList;
  if ( ptArgList->nArguments >= 3 )
  {
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
        pxObject = v5->pxObject;
        if ( pxObject )
        {
          if ( QTask_IsQTaskTypeDerived(*((_WORD *)pxObject + 18), ConveyorBelt_eQTaskType) )
          {
            if ( Script_EvalArgFloat(v3, 1) >= -20.0 )
            {
              if ( Script_EvalArgFloat(v3, 1) <= 20.0 )
                v7 = Script_EvalArgFloat(v3, 1);
              else
                v7 = 20.0;
            }
            else
            {
              v7 = -20.0;
            }
            *((float *)pxObject + 128) = v7;
            if ( Script_EvalArgFloat(v3, 2) >= -20.0 )
            {
              if ( Script_EvalArgFloat(v3, 2) <= 20.0 )
                v8 = Script_EvalArgFloat(v3, 2);
              else
                v8 = 20.0;
            }
            else
            {
              v8 = -20.0;
            }
            *((float *)pxObject + 129) = v8;
          }
        }
      }
    }
  }
  Rs.nResult = 0;
  Rs.vResult = 0.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/objects/conveyorbelt.c:120  [anchor-mhash]
void __cdecl ConveyorBelt_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ((void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[0][EditRigidObj_eQTaskType].pfHandler)(
    ptQTask,
    pxContext);
  ptQTask[12].ptParent = nullptr;
  *(_DWORD *)&ptQTask[12].eQTaskType = 0;
}

// source: j/0/objects/conveyorbelt.c:138  [size]
void __cdecl ConveyorBelt_RunHandler(struct QTask_s *ptQTask)
{
  ((void (__cdecl *)())QTask_aatQTaskFinalEvent[1][EditRigidObj_eQTaskType].pfHandler)(ptQTask);
}

// source: j/0/objects/conveyorbelt.c:154  [size]
void __cdecl ConveyorBelt_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ((void (__cdecl *)())QTask_aatQTaskFinalEvent[ParameterList_eUpdateInternalDataQTaskEvent][EditRigidObj_eQTaskType].pfHandler)(ptQTask, pxContext);
}

// source: j/0/objects/conveyorbelt.c:170  [size]
void __cdecl ConveyorBelt_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = ConveyorBelt_ptParameterList;
}

// source: j/0/objects/conveyorbelt.c:186  [anchor-strings]
void __cdecl ConveyorBelt_PushObjectHandler(struct QTask_s *ptQTask, void *pxContext)
{
  int v2; // ecx
  double v4; // st7
  double v5; // st7
  double v6; // st6
  float Real32x3_Rotate_tTemp; // [esp+0h] [ebp-Ch]
  float Real32x3_Rotate_tTemp_4; // [esp+4h] [ebp-8h]
  float Real32x3_Rotate_tTemp_8; // [esp+8h] [ebp-4h]

  v2 = *((_DWORD *)pxContext + 24);
  *(_DWORD *)pxContext = 0;
  *((_DWORD *)pxContext + 1) = 0;
  *((_DWORD *)pxContext + 2) = 0;
  if ( v2 )
  {
    if ( !strcmp((char *)(v2 + 32), "ConveyorBelt") )
    {
      *(float *)pxContext = *(float *)&ptQTask[12].ptParent * 136.53334045410156;
      v4 = *(float *)&ptQTask[12].eQTaskType;
      *((_DWORD *)pxContext + 2) = 0;
      *((float *)pxContext + 1) = v4 * 136.53334045410156;
      Real32x3_Rotate_tTemp = *(float *)&ptQTask[3].tQTaskChildren.ptHead * *((float *)pxContext + 1)
                            + *(float *)&ptQTask[3].ptPrev * *(float *)pxContext
                            + *(float *)&ptQTask[3].tQTaskChildren.ptMiddle * 0.0;
      Real32x3_Rotate_tTemp_4 = *(float *)&ptQTask[3].tQTaskRefList.ptHead * *((float *)pxContext + 1)
                              + *(float *)&ptQTask[3].tQTaskChildren.ptTail * *(float *)pxContext
                              + *(float *)&ptQTask[3].tQTaskRefList.ptMiddle * 0.0;
      v5 = *(float *)&ptQTask[3].ptParent * *((float *)pxContext + 1)
         + *(float *)&ptQTask[3].tQTaskRefList.ptTail * *(float *)pxContext;
      v6 = *(float *)&ptQTask[3].eQTaskType * 0.0;
      *(float *)pxContext = Real32x3_Rotate_tTemp;
      *((float *)pxContext + 1) = Real32x3_Rotate_tTemp_4;
      Real32x3_Rotate_tTemp_8 = v5 + v6;
      *((float *)pxContext + 2) = Real32x3_Rotate_tTemp_8;
    }
  }
}

// source: j/0/objects/conveyorbelt.c:217  [size]
__int16 __cdecl ConveyorBelt_GetPushObjectQTaskEvent()
{
  return ConveyorBelt_ePushObjectQTaskEvent;
}

// source: j/0/objects/conveyorbelt.c:232  [size]
unsigned __int16 __cdecl ConveyorBelt_GetQTaskType()
{
  return ConveyorBelt_eQTaskType;
}

// source: j/0/objects/conveyorbelt.c:247  [anchor-strings]
void __cdecl ConveyorBelt_Open()
{
  __int16 v0; // ax
  unsigned __int16 v1; // si
  __int16 v2; // di
  __int16 v3; // bx
  struct ParameterList_s *v4; // eax
  int v5; // edx
  int nMaxParameters; // [esp+10h] [ebp-4h] BYREF

  ConveyorBelt_eQTaskType = QTask_NewQTaskType("ConveyorBelt", 520, EditRigidObj_eQTaskType, 0, 0);
  v0 = QTask_NewQTaskEventFn(0, "PushObject");
  v1 = ConveyorBelt_eQTaskType;
  v2 = v0;
  ConveyorBelt_ePushObjectQTaskEvent = v0;
  QTask_LinkQTaskEventHandlerFn(ConveyorBelt_eQTaskType, 0, ConveyorBelt_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 1, (void (__cdecl *)(struct QTask_s *))ConveyorBelt_RunHandler);
  QTask_LinkQTaskEventHandlerFn(
    v1,
    ParameterList_eUpdateInternalDataQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))ConveyorBelt_UpdateInternalDataHandler);
  v3 = ParameterList_eGetParameterListQTaskEvent;
  QTask_LinkQTaskEventHandlerFn(
    v1,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))ConveyorBelt_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(v1, v2, ConveyorBelt_PushObjectHandler);
  QTask_LinkQTaskEventHandlerFn(
    v1,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveHandler);
  nMaxParameters = 0;
  ((void (__cdecl *)(_DWORD, int *))QTask_aatQTaskFinalEvent[v3][EditRigidObj_eQTaskType].pfHandler)(0, &nMaxParameters);
  ConveyorBelt_ptParameterList = ParameterList_Derive((struct ParameterList_s *)nMaxParameters, 2);
  ParameterList_AddParameterMinMax(
    ConveyorBelt_ptParameterList,
    0x200u,
    Level_eParameterTypeReal32,
    "X Speed",
    7u,
    -20.0,
    20.0);
  ParameterList_AddParameterMinMax(
    ConveyorBelt_ptParameterList,
    0x204u,
    Level_eParameterTypeReal32,
    "Y Speed",
    7u,
    -20.0,
    20.0);
  Symbol_Register(
    "ConveyorBelt_SetSpeed",
    ConveyorBelt_SetSpeed,
    nullptr,
    3,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  QTask_LinkQTaskEventHandlerFn(
    ConveyorBelt_eQTaskType,
    Serialize_eGetSerializeParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))ConveyorBelt_GetSerializeParameterListHandler);
  v4 = (struct ParameterList_s *)Mem_AllocFn(52, 4);
  v5 = Level_eParameterTypeReal32;
  v4->ptParameterListItem = (struct ParameterListItem_s *)&v4[1];
  v4->nParameters = 0;
  v4->nMaxParameters = 2;
  ConveyorBelt_ptSerializeParameterList = v4;
  ParameterList_AddParameter(v4, 0x200u, v5, "XSpeed", 7u, nullptr);
  ParameterList_AddParameter(
    ConveyorBelt_ptSerializeParameterList,
    0x204u,
    Level_eParameterTypeReal32,
    "YSpeed",
    7u,
    nullptr);
}

// source: j/0/objects/conveyorbelt.c:289  [anchor-strings]
void __cdecl ConveyorBelt_Close()
{
  int v0; // esi
  int v1; // esi

  Symbol_Remove("ConveyorBelt_SetSpeed");
  if ( ConveyorBelt_ptParameterList )
  {
    v0 = *(_DWORD *)((unsigned int)&ConveyorBelt_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
  if ( ConveyorBelt_ptSerializeParameterList )
  {
    v1 = *(_DWORD *)((unsigned int)&ConveyorBelt_ptSerializeParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v1);
    memset(*(void **)(v1 + 8), 0xCDu, *(_DWORD *)(v1 + 16));
    free((void *)v1);
  }
  QTask_DeleteQTaskType(ConveyorBelt_eQTaskType);
  QTask_DeleteQTaskEvent(ConveyorBelt_ePushObjectQTaskEvent);
}
