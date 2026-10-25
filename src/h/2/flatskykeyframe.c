/* h/2/flatskykeyframe.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: h/2/flatskykeyframe.c:87  [anchor-mhash]
void __cdecl FlatSkyKeyframe_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ptQTask[1].ptNext = (struct QTask_s *)1065353216;
  ptQTask[1].ptPrev = (struct QTask_s *)1065353216;
  ptQTask[1].tQTaskChildren.ptHead = (struct QTask_s *)1065353216;
  ptQTask[1].tQTaskChildren.ptMiddle = (struct QTask_s *)1065353216;
  ptQTask[1].tQTaskChildren.ptTail = (struct QTask_s *)1065353216;
  ptQTask[1].tQTaskRefList.ptHead = (struct QReference_s *)1065353216;
  ptQTask[1].tQTaskRefList.ptMiddle = (struct QReference_s *)1065353216;
  ptQTask[1].tQTaskRefList.ptTail = (struct QReference_s *)1065353216;
  ptQTask[1].ptParent = (struct QTask_s *)1065353216;
  *(_DWORD *)&ptQTask[1].eQTaskType = 1065353216;
  ptQTask[2].ptNext = (struct QTask_s *)1065353216;
  ptQTask[2].ptPrev = (struct QTask_s *)1065353216;
  ptQTask[2].tQTaskChildren.ptHead = (struct QTask_s *)1065353216;
  ptQTask[2].tQTaskChildren.ptMiddle = (struct QTask_s *)1065353216;
  ptQTask[2].tQTaskChildren.ptTail = (struct QTask_s *)1065353216;
  ptQTask[2].tQTaskRefList.ptHead = nullptr;
}

// source: h/2/flatskykeyframe.c:108  [size]
void __cdecl FlatSkyKeyframe_DeleteHandler(struct QTask_s *ptQTask)
{
  ;
}

// source: h/2/flatskykeyframe.c:123  [size]
void __cdecl FlatSkyKeyframe_RunHandler(struct QTask_s *ptQTask)
{
  ;
}

// source: h/2/flatskykeyframe.c:138  [size]
void __cdecl FlatSkyKeyframe_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ;
}

// source: h/2/flatskykeyframe.c:153  [size]
void __cdecl FlatSkyKeyframe_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = FlatSkyKeyframe_ptParameterList;
}

// source: h/2/flatskykeyframe.c:171  [size]
unsigned __int16 __cdecl FlatSkyKeyframe_GetQTaskType()
{
  return FlatSkyKeyframe_eQTaskType;
}

// source: h/2/flatskykeyframe.c:184  [size]
float *__cdecl FlatSkyKeyframe_GetRequestedTime()
{
  return FlatSkyKeyframe_pvRequestedTime;
}

// source: h/2/flatskykeyframe.c:206  [anchor-callee]
struct QTask_s *__cdecl FlatSkyKeyframe_ApplyTime(
        struct QTask_s *ptParent,
        float vTime,
        struct real32x3_t *ptSkyColourTop,
        struct real32x3_t *ptSkyColourMiddleSouth,
        struct real32x3_t *ptSkyColourMiddleNorth,
        struct real32x3_t *ptSkyColourBottomSouth,
        struct real32x3_t *ptSkyColourBottomNorth)
{
  unsigned __int16 v7; // dx
  struct QTask_s *result; // eax
  float *v10; // esi
  float *v11; // edi
  struct QTask_s *FirstChildOfType; // ebx
  double v13; // st7

  v7 = FlatSkyKeyframe_eQTaskType;
  result = QTask_GetFirstChildOfType(ptParent, FlatSkyKeyframe_eQTaskType);
  if ( result )
  {
    v10 = nullptr;
    v11 = nullptr;
    FirstChildOfType = QTask_GetFirstChildOfType(ptParent, v7);
    if ( !FirstChildOfType )
      goto LABEL_16;
    while ( *(float *)&FirstChildOfType[2].tQTaskRefList.ptHead != vTime )
    {
      if ( *(float *)&FirstChildOfType[2].tQTaskRefList.ptHead < (double)vTime
        && (!v10 || *(float *)&FirstChildOfType[2].tQTaskRefList.ptHead > (double)v10[25]) )
      {
        v10 = (float *)FirstChildOfType;
      }
      if ( *(float *)&FirstChildOfType[2].tQTaskRefList.ptHead > (double)vTime
        && (!v11 || *(float *)&FirstChildOfType[2].tQTaskRefList.ptHead < (double)v11[25]) )
      {
        v11 = (float *)FirstChildOfType;
      }
      FirstChildOfType = QTask_GetNextSiblingOfType(FirstChildOfType, v7);
      if ( !FirstChildOfType )
        goto LABEL_15;
    }
    v10 = (float *)FirstChildOfType;
    v11 = (float *)FirstChildOfType;
LABEL_15:
    if ( v10 )
    {
      if ( v11 && v10 != v11 && v10[25] != v11[25] )
      {
        v13 = (vTime - v10[25]) / (v11[25] - v10[25]);
LABEL_23:
        ptSkyColourTop->vX = (v11[10] - v10[10]) * v13 + v10[10];
        ptSkyColourTop->vY = (v11[11] - v10[11]) * v13 + v10[11];
        ptSkyColourTop->vZ = (v11[12] - v10[12]) * v13 + v10[12];
        ptSkyColourBottomNorth->vX = (v11[22] - v10[22]) * v13 + v10[22];
        ptSkyColourBottomNorth->vY = (v11[23] - v10[23]) * v13 + v10[23];
        ptSkyColourBottomNorth->vZ = (v11[24] - v10[24]) * v13 + v10[24];
        ptSkyColourBottomSouth->vX = (v11[19] - v10[19]) * v13 + v10[19];
        ptSkyColourBottomSouth->vY = (v11[20] - v10[20]) * v13 + v10[20];
        ptSkyColourBottomSouth->vZ = (v11[21] - v10[21]) * v13 + v10[21];
        ptSkyColourMiddleNorth->vX = (v11[16] - v10[16]) * v13 + v10[16];
        ptSkyColourMiddleNorth->vY = (v11[17] - v10[17]) * v13 + v10[17];
        ptSkyColourMiddleNorth->vZ = (v11[18] - v10[18]) * v13 + v10[18];
        ptSkyColourMiddleSouth->vX = (v11[13] - v10[13]) * v13 + v10[13];
        ptSkyColourMiddleSouth->vY = (v11[14] - v10[14]) * v13 + v10[14];
        ptSkyColourMiddleSouth->vZ = (v11[15] - v10[15]) * v13 + v10[15];
        return (struct QTask_s *)ptSkyColourMiddleSouth;
      }
      v11 = v10;
    }
    else
    {
LABEL_16:
      v10 = v11;
    }
    v13 = 0.0;
    goto LABEL_23;
  }
  return result;
}

// source: h/2/flatskykeyframe.c:304  [anchor-hash]
void __cdecl FlatSkyKeyframe_Open()
{
  unsigned __int16 BaseQTaskType; // ax
  unsigned __int16 v1; // si
  struct ParameterList_s *v2; // eax
  int v3; // edx

  BaseQTaskType = QTask_GetBaseQTaskType();
  v1 = QTask_NewQTaskType("FlatSkyKeyframe", 104, BaseQTaskType, 0, 0);
  FlatSkyKeyframe_eQTaskType = v1;
  QTask_LinkQTaskEventHandlerFn(v1, 0, (void (__cdecl *)(struct QTask_s *, void *))FlatSkyKeyframe_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 2, (void (__cdecl *)(struct QTask_s *))FlatSkyKeyframe_DeleteHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 1, (void (__cdecl *)(struct QTask_s *))FlatSkyKeyframe_RunHandler);
  QTask_LinkQTaskEventHandlerFn(
    v1,
    ParameterList_eUpdateInternalDataQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))FlatSkyKeyframe_UpdateInternalDataHandler);
  QTask_LinkQTaskEventHandlerFn(
    v1,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))FlatSkyKeyframe_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(
    v1,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveHandler);
  v2 = (struct ParameterList_s *)Mem_AllocFn(132, 4);
  v2->ptParameterListItem = (struct ParameterListItem_s *)&v2[1];
  v3 = Level_eParameterTypeRGB;
  v2->nParameters = 0;
  v2->nMaxParameters = 6;
  FlatSkyKeyframe_ptParameterList = v2;
  ParameterList_AddParameter(v2, 0x28u, v3, "SkyDome Top Colour", 7u, nullptr);
  ParameterList_AddParameter(
    FlatSkyKeyframe_ptParameterList,
    0x40u,
    Level_eParameterTypeRGB,
    "SkyDome Middle Colour 1",
    7u,
    nullptr);
  ParameterList_AddParameter(
    FlatSkyKeyframe_ptParameterList,
    0x34u,
    Level_eParameterTypeRGB,
    "SkyDome Middle Colour 2",
    7u,
    nullptr);
  ParameterList_AddParameter(
    FlatSkyKeyframe_ptParameterList,
    0x58u,
    Level_eParameterTypeRGB,
    "SkyDome Bottom Colour 1",
    7u,
    nullptr);
  ParameterList_AddParameter(
    FlatSkyKeyframe_ptParameterList,
    0x4Cu,
    Level_eParameterTypeRGB,
    "SkyDome Bottom Colour 2",
    7u,
    nullptr);
  ParameterList_AddParameter(FlatSkyKeyframe_ptParameterList, 0x64u, Level_eParameterTypeReal32, "Time", 7u, nullptr);
}

// source: h/2/flatskykeyframe.c:338  [size]
void __cdecl FlatSkyKeyframe_Close()
{
  int v0; // esi

  if ( FlatSkyKeyframe_ptParameterList )
  {
    v0 = *(_DWORD *)((unsigned int)&FlatSkyKeyframe_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
  QTask_DeleteQTaskType(FlatSkyKeyframe_eQTaskType);
}
