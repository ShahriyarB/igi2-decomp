/* j/0/computer/computerplan.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/computer/computerplan.c:63  [size]
struct ComputerPlan_s *__cdecl ComputerPlan_DeleteResources(struct ComputerPlan_s *ptComputerPlan)
{
  struct ComputerPlan_s *result; // eax

  result = (struct ComputerPlan_s *)ptComputerPlan->ptPicture;
  if ( result )
    Picture_Delete((struct StaticTilemap_s *)result);
  return result;
}

// source: j/0/computer/computerplan.c:80  [anchor-mhash]
void __cdecl ComputerPlan_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ptQTask[1].ptNext = nullptr;
  LOBYTE(ptQTask[1].ptPrev) = 0;
  QVector_AddElement(ComputerPlan_ptComputerPlanVector, ptQTask);
}

// source: j/0/computer/computerplan.c:98  [size]
void __cdecl ComputerPlan_DeleteHandler(struct QTask_s *ptQTask)
{
  struct QVector_s *v1; // ecx
  unsigned int v2; // eax
  void **papxElement; // edx
  unsigned int v4; // edx
  unsigned int v5; // edi
  enum bool isStrictOrder; // esi
  void **v7; // ecx

  if ( ptQTask[1].ptNext )
    Picture_Delete((struct StaticTilemap_s *)ptQTask[1].ptNext);
  v1 = ComputerPlan_ptComputerPlanVector;
  v2 = 0;
  if ( ComputerPlan_ptComputerPlanVector->tPrivate.nElements )
  {
    papxElement = ComputerPlan_ptComputerPlanVector->tPrivate.papxElement;
    while ( *papxElement != ptQTask )
    {
      ++v2;
      ++papxElement;
      if ( v2 >= ComputerPlan_ptComputerPlanVector->tPrivate.nElements )
        goto LABEL_7;
    }
    v4 = v2;
  }
  else
  {
LABEL_7:
    v4 = (unsigned int)ptQTask;
  }
  v5 = ComputerPlan_ptComputerPlanVector->tPrivate.nElements - 1;
  ComputerPlan_ptComputerPlanVector->tPrivate.nElements = v5;
  if ( v4 < v5 )
  {
    isStrictOrder = v1->tPrivate.isStrictOrder;
    v7 = v1->tPrivate.papxElement;
    if ( isStrictOrder )
      memmove(&v7[v4], &v7[v4 + 1], 4 * (v5 - v4));
    else
      v7[v4] = v7[v5];
  }
}

// source: j/0/computer/computerplan.c:115  [size]
void __cdecl ComputerPlan_RunHandler(struct QTask_s *ptQTask)
{
  ;
}

// source: j/0/computer/computerplan.c:130  [anchor-mhash]
void __cdecl ComputerPlan_DrawHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptNext; // esi
  float vY; // [esp+0h] [ebp-10h]
  float vWidth; // [esp+4h] [ebp-Ch]

  ptNext = ptQTask[1].ptNext;
  if ( ptNext )
  {
    vWidth = (float)Display_tActiveMode.nHeight;
    vY = (float)Display_tActiveMode.nWidth;
    Q3DPicture_RegisterSize((struct StaticTilemap_s *)ptNext, 0.0, 0.0, vY, vWidth, -1);
  }
}

// source: j/0/computer/computerplan.c:153  [anchor-caller]
void __cdecl ComputerPlan_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  if ( ptQTask[1].ptNext )
    Picture_Delete((struct StaticTilemap_s *)ptQTask[1].ptNext);
  if ( Resource_IsLoadedInternal((char *)&ptQTask[1].ptPrev, nullptr)
    || File_Exists((char *)&ptQTask[1].ptPrev) )
  {
    ptQTask[1].ptNext = (struct QTask_s *)Picture_Load((char *)&ptQTask[1].ptPrev);
  }
}

// source: j/0/computer/computerplan.c:173  [size]
void __cdecl ComputerPlan_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = ComputerPlan_ptParameterList;
}

// source: j/0/computer/computerplan.c:191  [size]
unsigned __int16 __cdecl ComputerPlan_GetQTaskType()
{
  return ComputerPlan_eQTaskType;
}

// source: j/0/computer/computerplan.c:204  [anchor-hash]
unsigned int __cdecl ComputerPlan_GetNumberOfQTasks()
{
  return ComputerPlan_ptComputerPlanVector->tPrivate.nElements;
}

// source: j/0/computer/computerplan.c:217  [size]
struct QTask_s *__cdecl ComputerPlan_GetQTask(unsigned int iQTask)
{
  return (struct QTask_s *)ComputerPlan_ptComputerPlanVector->tPrivate.papxElement[iQTask];
}

// source: j/0/computer/computerplan.c:230  [anchor-hash]
void __cdecl ComputerPlan_Open()
{
  unsigned __int16 BaseQTaskType; // ax
  unsigned __int16 v1; // si
  struct QVector_s *v2; // eax
  struct ParameterList_s *v3; // eax

  BaseQTaskType = QTask_GetBaseQTaskType();
  v1 = QTask_NewQTaskType("ComputerPlan", 300, BaseQTaskType, 0, 0);
  ComputerPlan_eQTaskType = v1;
  QTask_LinkQTaskEventHandlerFn(v1, 0, ComputerPlan_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 2, ComputerPlan_DeleteHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 1, (void (__cdecl *)(struct QTask_s *))ComputerPlan_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, Screen_eDrawQTaskEvent, ComputerPlan_DrawHandler);
  QTask_LinkQTaskEventHandlerFn(v1, ParameterList_eUpdateInternalDataQTaskEvent, ComputerPlan_UpdateInternalDataHandler);
  QTask_LinkQTaskEventHandlerFn(
    v1,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))ComputerPlan_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(
    v1,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveHandler);
  v2 = (struct QVector_s *)Mem_AllocFn(24, 4);
  v2->tPrivate.nArraySize = 0;
  v2->tPrivate.nReallocSize = 32;
  v2->tPrivate.nElements = 0;
  v2->tPrivate.isPrivateMem = false;
  v2->tPrivate.papxElement = nullptr;
  v2->tPrivate.isStrictOrder = false;
  ComputerPlan_ptComputerPlanVector = v2;
  v3 = (struct ParameterList_s *)Mem_AllocFn(32, 4);
  v3->nParameters = 0;
  v3->nMaxParameters = 1;
  v3->ptParameterListItem = (struct ParameterListItem_s *)&v3[1];
  ComputerPlan_ptParameterList = v3;
  ParameterList_AddParameter(v3, 0x2Cu, Level_eParameterTypeString256, "Picture filename", 7u, nullptr);
}

// source: j/0/computer/computerplan.c:261  [size]
void __cdecl ComputerPlan_Close()
{
  int v0; // esi

  if ( ComputerPlan_ptParameterList )
  {
    v0 = *(_DWORD *)((unsigned int)&ComputerPlan_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
  QTask_DeleteQTaskType(ComputerPlan_eQTaskType);
  QVector_Delete(ComputerPlan_ptComputerPlanVector);
}
