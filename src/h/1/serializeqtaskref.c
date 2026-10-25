/* h/1/serializeqtaskref.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: h/1/serializeqtaskref.c:39  [anchor-caller]
void __cdecl SerializeQTaskRef_ParameterPrintHandler(void *pxData, void *pxContext)
{
  struct QTask_s *v2; // edx
  int v3; // eax
  struct QReference_s *v4; // ecx

  if ( *(_DWORD *)pxData && *(_DWORD *)(*(_DWORD *)pxData + 8) )
  {
    v2 = *(struct QTask_s **)(*(_DWORD *)pxData + 8);
    while ( 2 )
    {
      v3 = 0;
      while ( 1 )
      {
        v4 = Level_atLevelQTaskID[v3];
        if ( v4 )
        {
          if ( v4->pxObject == v2 )
            break;
        }
        if ( ++v3 >= 4096 )
          goto LABEL_10;
      }
      if ( v3 < 0 )
      {
LABEL_10:
        v2 = v2->ptParent;
        if ( v2 )
          continue;
        goto LABEL_11;
      }
      break;
    }
    if ( !v2 )
      goto LABEL_11;
    Serialize_PrintQTaskHierarchy(
      *((char **)pxContext + 2),
      *((_DWORD *)pxContext + 3),
      v2,
      *(struct QTask_s **)(*(_DWORD *)pxData + 8));
  }
  else
  {
LABEL_11:
    strcat(*((char **)pxContext + 2), "-1");
  }
}

// source: h/1/serializeqtaskref.c:81  [anchor-mhash]
void __cdecl SerializeQTaskRef_ParameterParseHandler(void *pxData, void *pxContext)
{
  _DWORD *v2; // ebp
  int *v3; // esi
  struct ArgList_s *v4; // edi
  int v5; // eax
  void *v6; // eax
  struct ArgList_s *v7; // edi
  struct QTask_s *TaskFromArgList; // ebx
  int v9; // eax
  int v10; // eax
  struct QTask_s *ChildTaskFromArgList; // eax

  v2 = pxData;
  if ( *(_DWORD *)pxData )
  {
    QReference_Delete(*(struct QReference_s **)pxData, &QTask_tQTaskRefPool);
    *v2 = 0;
  }
  v3 = (int *)pxContext;
  v4 = *((struct ArgList_s **)pxContext + 1);
  v5 = *(_DWORD *)pxContext;
  if ( v4->isQVM )
  {
    pxData = nullptr;
    QVM_EvalArg(&pxData, 4, v4, v5, 1);
    v6 = pxData;
  }
  else
  {
    v6 = (void *)Expression_EvalInt(v4->aptExpression[v5]);
  }
  if ( (int)v6 < 0 )
  {
    ++*v3;
  }
  else
  {
    v7 = (struct ArgList_s *)v3[1];
    TaskFromArgList = Serialize_GetTaskFromArgList(v7, v3);
    if ( TaskFromArgList )
    {
      v9 = (*v3)++;
      v10 = Script_EvalArgInt(v7, v9);
      ChildTaskFromArgList = Serialize_GetChildTaskFromArgList(v7, TaskFromArgList, v10, v3);
      if ( ChildTaskFromArgList )
        *v2 = QTask_NewQTaskRef(ChildTaskFromArgList);
    }
  }
}

// source: h/1/serializeqtaskref.c:125  [size]
int __cdecl SerializeQTaskRef_GetParameterType()
{
  return SerializeQTaskRef_eParameterType;
}

// source: h/1/serializeqtaskref.c:138  [anchor-strings]
void __cdecl SerializeQTaskRef_Open()
{
  int v0; // esi

  v0 = ParameterList_NewParameterType("SerializeQTaskRef", -1);
  SerializeQTaskRef_eParameterType = v0;
  ParameterList_LinkParameterEventHandler(
    v0,
    ParameterList_eQParameterPrintEvent,
    SerializeQTaskRef_ParameterPrintHandler);
  ParameterList_LinkParameterEventHandler(
    v0,
    ParameterList_eQParameterParseEvent,
    SerializeQTaskRef_ParameterParseHandler);
}

// source: h/1/serializeqtaskref.c:153  [size]
void __cdecl SerializeQTaskRef_Close()
{
  ParameterList_atParameterType[SerializeQTaskRef_eParameterType].isUsed = false;
}
