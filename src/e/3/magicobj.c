/* e/3/magicobj.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: e/3/magicobj.c:44  [anchor-mhash]
struct Result_s *__cdecl MagicObj_DefineMagicObjCB(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  int v3; // eax
  struct ArgList_s *v4; // edi
  struct MagicObjType_s *v5; // eax
  void *v6; // eax
  unsigned __int16 v7; // ax
  int v8; // edx
  int v9; // ecx
  void (__cdecl *pfHandler)(_DWORD, struct ArgList_s **); // eax
  void *v11; // eax
  int v12; // ecx
  int v13; // eax
  struct ParseMagicObjParametersContext_s tParseMagicObjParametersContext[2]; // [esp+8h] [ebp-18h] BYREF

  v3 = MagicObj_nMagicObjType;
  v4 = ptArgList;
  MagicObj_atMagicObjType[v3].pxData = nullptr;
  v5 = &MagicObj_atMagicObjType[v3];
  if ( v4->isQVM )
  {
    v5->zName[0] = 0;
    QVM_EvalArg(v5, 16, v4, 0, 3);
  }
  else
  {
    Expression_EvalString(*v4->aptExpression, v5->zName, 16);
  }
  v6 = (void *)(40 * MagicObj_nMagicObjType + 139718192);
  if ( v4->isQVM )
  {
    MagicObj_atMagicObjType[MagicObj_nMagicObjType].zModel[0] = 0;
    QVM_EvalArg(v6, 16, v4, 1, 3);
  }
  else
  {
    Expression_EvalString(v4->aptExpression[1], (char *)(40 * MagicObj_nMagicObjType + 139718192), 16);
  }
  if ( v4->isQVM )
  {
    ptArgList = nullptr;
    QVM_EvalArg(&ptArgList, 4, v4, 2, 1);
    v7 = (unsigned __int16)ptArgList;
  }
  else
  {
    v7 = Expression_EvalInt(v4->aptExpression[2]);
  }
  v8 = 511 * MagicObj_eGetMagicObjParameterSizeEvent;
  v9 = MagicObj_nMagicObjType;
  MagicObj_atMagicObjType[v9].eQTaskType = v7;
  MagicObj_atMagicObjType[v9].pxData = nullptr;
  pfHandler = (void (__cdecl *)(_DWORD, struct ArgList_s **))QTask_aatQTaskFinalEvent[0][MagicObj_atMagicObjType[v9].eQTaskType
                                                                                       + v8].pfHandler;
  if ( pfHandler )
  {
    pfHandler(0, &ptArgList);
    v11 = Mem_AllocFn((int)ptArgList, 4);
    v12 = MagicObj_nMagicObjType;
    MagicObj_atMagicObjType[v12].pxData = v11;
    tParseMagicObjParametersContext[0].pxData = v11;
    v13 = 511 * MagicObj_eGetParseMagicObjParametersEvent + MagicObj_atMagicObjType[v12].eQTaskType;
    tParseMagicObjParametersContext[0].ptArgList = v4;
    tParseMagicObjParametersContext[0].iFirstArg = 3;
    ((void (__cdecl *)(_DWORD, struct ParseMagicObjParametersContext_s *))QTask_aatQTaskFinalEvent[0][v13].pfHandler)(
      0,
      tParseMagicObjParametersContext);
  }
  ++MagicObj_nMagicObjType;
  tParseMagicObjParametersContext[0].pxData = (void *)1;
  tParseMagicObjParametersContext[0].iFirstArg = 0;
  tParseMagicObjParametersContext[1].pxData = (void *)1072693248;
  tParseMagicObjParametersContext[1].ptArgList = (struct ArgList_s *)&g_zInitialValue;
  qmemcpy(retstr, tParseMagicObjParametersContext, sizeof(struct Result_s));
  return retstr;
}

// source: e/3/magicobj.c:115  [size]
__int16 __cdecl MagicObj_GetUpdateMagicObjEvent()
{
  return MagicObj_eUpdateMagicObjEvent;
}

// source: e/3/magicobj.c:130  [size]
__int16 __cdecl MagicObj_GetParseMagicObjParametersEvent()
{
  return MagicObj_eGetParseMagicObjParametersEvent;
}

// source: e/3/magicobj.c:145  [size]
__int16 __cdecl MagicObj_GetGetMagicObjParameterSizeEvent()
{
  return MagicObj_eGetMagicObjParameterSizeEvent;
}

// source: e/3/magicobj.c:160  [size]
__int16 __cdecl MagicObj_GetMagicObjEnterEvent()
{
  return MagicObj_eMagicObjEnterEvent;
}

// source: e/3/magicobj.c:175  [size]
__int16 __cdecl MagicObj_GetSetMagicObjParametersEvent()
{
  return MagicObj_eSetMagicObjParametersEvent;
}

// source: e/3/magicobj.c:192  [anchor-callee]
struct MagicObjType_s *__cdecl MagicObj_GetMagicObjType(char *pzName)
{
  int v1; // edi
  struct MagicObjType_s *i; // ebp

  v1 = 0;
  if ( MagicObj_nMagicObjType <= 0 )
    return nullptr;
  for ( i = MagicObj_atMagicObjType; strcmp(pzName, i->zName); ++i )
  {
    if ( ++v1 >= MagicObj_nMagicObjType )
      return nullptr;
  }
  return (struct MagicObjType_s *)(40 * v1 + 139718176);
}

// source: e/3/magicobj.c:216  [anchor-hash]
struct MagicObjType_s *__cdecl MagicObj_AllocMagicObjType()
{
  int v0; // eax
  struct MagicObjType_s *v1; // edx
  int v2; // eax

  v0 = 0;
  if ( MagicObj_nMagicObjType <= 0 )
  {
LABEL_5:
    v2 = 5 * MagicObj_nMagicObjType++;
    return (struct MagicObjType_s *)(8 * v2 + 139718176);
  }
  else
  {
    v1 = MagicObj_atMagicObjType;
    while ( v1->zName[0] )
    {
      ++v0;
      ++v1;
      if ( v0 >= MagicObj_nMagicObjType )
        goto LABEL_5;
    }
    return (struct MagicObjType_s *)(40 * v0 + 139718176);
  }
}

// source: e/3/magicobj.c:244  [anchor-callee]
void __cdecl MagicObj_RemoveMagicObjType(struct MagicObjType_s *ptMagicObjType)
{
  void *pxData; // eax
  int v2; // esi

  pxData = ptMagicObjType->pxData;
  if ( pxData )
  {
    v2 = *(_DWORD *)(((int)pxData - 4) & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v2);
    memset(*(void **)(v2 + 8), 0xCDu, *(_DWORD *)(v2 + 16));
    free((void *)v2);
    ptMagicObjType->pxData = nullptr;
  }
  *(_DWORD *)ptMagicObjType->zName = 0;
  *(_DWORD *)&ptMagicObjType->zName[4] = 0;
  *(_DWORD *)&ptMagicObjType->zName[8] = 0;
  *(_DWORD *)&ptMagicObjType->zName[12] = 0;
}

// source: e/3/magicobj.c:264  [size]
void __cdecl MagicObj_Open()
{
  MagicObj_eUpdateMagicObjEvent = QTask_NewQTaskEventFn(0, "UpdateMagicObj");
  MagicObj_eGetParseMagicObjParametersEvent = QTask_NewQTaskEventFn(0, "GetParseMagicObjParameters");
  MagicObj_eGetMagicObjParameterSizeEvent = QTask_NewQTaskEventFn(0, "GetMagicObjParameterSize");
  MagicObj_eMagicObjEnterEvent = QTask_NewQTaskEventFn(0, "MagicObjEnter");
  MagicObj_eSetMagicObjParametersEvent = QTask_NewQTaskEventFn(0, "SetMagicObjParameters");
  Symbol_Register(
    "DefineMagicObj",
    MagicObj_DefineMagicObjCB,
    nullptr,
    -1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
}

// source: e/3/magicobj.c:285  [size]
void __cdecl MagicObj_Close()
{
  int v0; // ebp
  void **p_pxData; // ebx
  int v2; // esi
  void **v3; // ecx

  QTask_DeleteQTaskEvent(MagicObj_eUpdateMagicObjEvent);
  QTask_DeleteQTaskEvent(MagicObj_eGetParseMagicObjParametersEvent);
  QTask_DeleteQTaskEvent(MagicObj_eGetMagicObjParameterSizeEvent);
  QTask_DeleteQTaskEvent(MagicObj_eMagicObjEnterEvent);
  QTask_DeleteQTaskEvent(MagicObj_eSetMagicObjParametersEvent);
  v0 = 0;
  if ( MagicObj_nMagicObjType > 0 )
  {
    p_pxData = &MagicObj_atMagicObjType[0].pxData;
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
      v3 = p_pxData - 9;
      *v3 = nullptr;
      v3[1] = nullptr;
      v3[2] = nullptr;
      v3[3] = nullptr;
      ++v0;
      p_pxData += 10;
    }
    while ( v0 < MagicObj_nMagicObjType );
  }
}
