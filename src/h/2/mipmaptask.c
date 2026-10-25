/* h/2/mipmaptask.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: h/2/mipmaptask.c:59  [anchor-strings]
void __cdecl MipMapTask_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxUnused)
{
  int v2; // esi
  char *ErrorString; // eax
  char zString[1024]; // [esp+10h] [ebp-400h] BYREF

  if ( RenderMode_eActiveRenderMode == Direct3D_eRenderMode )
  {
    v2 = Direct3D_ptDevice->lpVtbl->SetTextureStageState(
           Direct3D_ptDevice,
           0,
           D3DTSS_MIPMAPLODBIAS,
           (unsigned int)ptQTask[1].ptNext);
    if ( v2 )
    {
      sprintf(zString, "Couldn't set texturestagestate");
      ErrorString = Direct3D_GetErrorString(v2);
      LDebug_Error("%s\n\nDirectX error message: %s\nFile: %s Line: %d", zString, ErrorString, "2\\mipmaptask.c", 98);
      abort();
    }
  }
}

// source: h/2/mipmaptask.c:112  [size]
void __cdecl MipMapTask_CreateHandler(struct QTask_s *ptQTask, void *pxUnused)
{
  ptQTask[1].ptNext = (struct QTask_s *)1063675494;
  ptQTask[1].ptPrev = (struct QTask_s *)1045220557;
  ptQTask[1].tQTaskChildren.ptHead = nullptr;
  LOBYTE(ptQTask[1].tQTaskChildren.ptMiddle) = 1;
}

// source: h/2/mipmaptask.c:134  [size]
void __cdecl MipMapTask_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = MipMapTask_ptParameterList;
}

// source: h/2/mipmaptask.c:151  [anchor-callee]
void __cdecl MipMapTask_Open()
{
  unsigned __int16 BaseQTaskType; // ax
  unsigned __int16 v1; // si
  struct ParameterList_s *v2; // eax
  int v3; // edx

  BaseQTaskType = QTask_GetBaseQTaskType();
  v1 = QTask_NewQTaskType("MipMapControl", 56, BaseQTaskType, 0, 0);
  MipMapTask_eQTaskType = v1;
  QTask_LinkQTaskEventHandlerFn(v1, 0, (void (__cdecl *)(struct QTask_s *, void *))MipMapTask_CreateHandler);
  QTask_LinkQTaskEventHandlerFn(v1, ParameterList_eUpdateInternalDataQTaskEvent, MipMapTask_UpdateInternalDataHandler);
  QTask_LinkQTaskEventHandlerFn(
    v1,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))MipMapTask_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(
    v1,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveNoChildrenHandler);
  v2 = (struct ParameterList_s *)Mem_AllocFn(92, 4);
  v3 = Level_eParameterTypebool8;
  v2->ptParameterListItem = (struct ParameterListItem_s *)&v2[1];
  v2->nParameters = 0;
  v2->nMaxParameters = 4;
  MipMapTask_ptParameterList = v2;
  ParameterList_AddParameter(v2, 0x34u, v3, "LOD blend", 7u, nullptr);
  dword_83415F0 = 0;
  dword_83415F4 = 0x40000000;
  dword_83415E8 = 0;
  dword_83415EC = 0;
  Symbol_Register(
    "GR_MIPMAP_DISABLE",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    nullptr,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "GR_MIPMAP_NEAREST",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)1,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "GR_MIPMAP_NEAREST_DITHER",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)2,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  ParameterList_AddParameter(
    MipMapTask_ptParameterList,
    0x30u,
    Level_eParameterTypeInt32,
    "MipMap mode",
    7u,
    &dword_83415E8);
  dword_8341600 = 0;
  dword_8341604 = 1075773440;
  dword_83415F8 = 0;
  dword_83415FC = -1071644672;
  ParameterList_AddParameter(
    MipMapTask_ptParameterList,
    0x28u,
    Level_eParameterTypeReal32,
    "LOD bias (Standard MipMapping)",
    7u,
    &dword_83415F8);
  ParameterList_AddParameter(
    MipMapTask_ptParameterList,
    0x2Cu,
    Level_eParameterTypeReal32,
    "LOD bias (Trilinear MipMapping)",
    7u,
    &dword_83415F8);
}

// source: h/2/mipmaptask.c:197  [size]
void __cdecl MipMapTask_Close()
{
  int v0; // esi

  if ( MipMapTask_ptParameterList )
  {
    v0 = *(_DWORD *)((unsigned int)&MipMapTask_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
  QTask_DeleteQTaskType(MipMapTask_eQTaskType);
}
