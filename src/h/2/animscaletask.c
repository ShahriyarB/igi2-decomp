/* h/2/animscaletask.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: h/2/animscaletask.c:41  [anchor-mhash]
void __cdecl AnimScaleQTask_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ptQTask[3285].tQTaskChildren.ptHead = (struct QTask_s *)-1;
  ptQTask[3285].ptNext = (struct QTask_s *)-1;
  ptQTask[1].ptNext = nullptr;
  ptQTask[1].ptPrev = nullptr;
  ptQTask[1].tQTaskChildren.ptHead = nullptr;
  ptQTask[1].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[1].tQTaskChildren.ptTail = nullptr;
  ptQTask[1].tQTaskRefList.ptHead = nullptr;
  ptQTask[1].tQTaskRefList.ptTail = nullptr;
  ptQTask[1].ptParent = nullptr;
  *(_DWORD *)&ptQTask[1].eQTaskType = 0;
  ptQTask[2].ptPrev = nullptr;
  ptQTask[2].tQTaskChildren.ptHead = nullptr;
  ptQTask[2].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[2].tQTaskRefList.ptHead = nullptr;
  ptQTask[3285].ptPrev = (struct QTask_s *)1;
  LOBYTE(ptQTask[3282].ptParent) = 1;
  LOBYTE(ptQTask[6].ptNext) = 32;
  ptQTask[6].ptPrev = nullptr;
  BYTE1(ptQTask[3282].ptParent) = 0;
  *(_DWORD *)&ptQTask[3284].eQTaskType = 0;
  ptQTask[1].tQTaskRefList.ptMiddle = (struct QReference_s *)1065353216;
  ptQTask[2].ptNext = (struct QTask_s *)1065353216;
  ptQTask[2].tQTaskChildren.ptTail = (struct QTask_s *)1065353216;
  *(_DWORD *)&ptQTask[3282].eQTaskType = 0;
  ptQTask[3283].ptNext = nullptr;
  ptQTask[3283].ptPrev = nullptr;
  ptQTask[3284].ptParent = nullptr;
  memset(&ptQTask[2].tQTaskRefList.ptMiddle, 0, 0x88u);
  QTaskList_Register(AnimQTask_ptQTaskList, (struct QTaskList_s *)ptQTask);
  ptQTask[3285].tQTaskChildren.ptTail = (struct QTask_s *)1065353216;
  ptQTask[3285].tQTaskRefList.ptHead = nullptr;
}

// source: h/2/animscaletask.c:112  [anchor-mhash]
void __cdecl AnimScaleQTask_RunHandler(struct QTask_s *ptQTask)
{
  int v1; // edi
  double v2; // st7
  double v3; // st7

  v1 = 0;
  if ( *(_DWORD *)&ptQTask[3282].eQTaskType && ptQTask[3283].ptNext->ptNext && ptQTask[3283].ptPrev )
    LOBYTE(ptQTask[3282].ptParent) = (__int64)Level_RunLevelExpression(
                                                (struct LevelExpression_s *)&ptQTask[3282].eQTaskType,
                                                ptQTask);
  if ( LOBYTE(ptQTask[3282].ptParent) )
  {
    v2 = *(float *)&ptQTask[3285].tQTaskChildren.ptTail + *(float *)&ptQTask[3285].tQTaskRefList.ptHead;
    *(float *)&ptQTask[3285].tQTaskRefList.ptHead = v2;
    if ( v2 >= 0.10000000149011612 )
    {
      v3 = *(float *)&ptQTask[3285].tQTaskRefList.ptHead;
      do
      {
        v3 = v3 - 0.10000000149011612;
        ++v1;
      }
      while ( v3 >= 0.10000000149011612 );
      *(float *)&ptQTask[3285].tQTaskRefList.ptHead = v3;
    }
    AnimQTask_SetIdealTime(ptQTask, (int)ptQTask[3285].tQTaskChildren.ptHead + v1);
  }
}

// source: h/2/animscaletask.c:155  [anchor-hash]
void __cdecl AnimScaleQTask_Open()
{
  unsigned __int16 v0; // si
  struct ParameterList_s *v1; // eax
  int v2; // edx

  v0 = QTask_NewQTaskType("AnimScaleTask", 131424, AnimQTask_eQTaskType, 0, 0);
  AnimScaleQTask_eQTaskType = v0;
  QTask_LinkQTaskEventHandlerFn(v0, 0, AnimScaleQTask_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 1, AnimScaleQTask_RunHandler);
  v1 = (struct ParameterList_s *)Mem_AllocFn(212, 4);
  v1->ptParameterListItem = (struct ParameterListItem_s *)&v1[1];
  v2 = Level_eParameterTypeObjectPos;
  v1->nParameters = 0;
  v1->nMaxParameters = 10;
  AnimScaleQTask_ptParameterList = v1;
  ParameterList_AddParameter(v1, 0x28u, v2, "Position", 7u, nullptr);
  ParameterList_AddParameter(
    AnimScaleQTask_ptParameterList,
    0x40u,
    Level_eParameterTypeReal32x9,
    "Orientation",
    7u,
    nullptr);
  ParameterList_AddParameter(
    AnimScaleQTask_ptParameterList,
    0x20148u,
    Level_eParameterTypeInt32,
    "TargetID",
    7u,
    nullptr);
  ParameterList_AddParameter(
    AnimScaleQTask_ptParameterList,
    0x200F4u,
    Level_eParameterTypeString256,
    off_6A50D8,
    7u,
    nullptr);
  ParameterList_AddParameter(
    AnimScaleQTask_ptParameterList,
    0x200F0u,
    Level_eParameterTypebool8,
    "Initial run",
    7u,
    nullptr);
  ParameterList_AddParameter(AnimScaleQTask_ptParameterList, 0, AnimQTask_eParameterType, "AnimData", 7u, nullptr);
}

// source: h/2/animscaletask.c:186  [size]
void __cdecl AnimScaleQTask_Close()
{
  int v0; // esi

  if ( AnimScaleQTask_ptParameterList )
  {
    v0 = *(_DWORD *)((unsigned int)&AnimScaleQTask_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
  QTask_DeleteQTaskType(AnimScaleQTask_eQTaskType);
  AnimScaleQTask_eQTaskType = 512;
}

// source: h/2/animscaletask.c:207  [anchor-hash]
float __cdecl AnimScaleQTask_GetScale(int nID)
{
  struct QReference_s *v1; // eax

  if ( (unsigned int)nID < 0x1000 && (v1 = Level_atLevelQTaskID[nID]) != nullptr )
    return *((float *)v1->pxObject + 32854);
  else
    return MEMORY[0x20158];
}

// source: h/2/animscaletask.c:227  [anchor-mhash]
int __cdecl AnimScaleQTask_SetScale(int nID, float vScale)
{
  struct QReference_s *v2; // eax
  int result; // eax

  if ( (unsigned int)nID < 0x1000 && (v2 = Level_atLevelQTaskID[nID]) != nullptr )
  {
    result = (int)v2->pxObject;
    *(float *)(result + 131416) = vScale;
  }
  else
  {
    MEMORY[0x20158] = LODWORD(vScale);
    return 0;
  }
  return result;
}
