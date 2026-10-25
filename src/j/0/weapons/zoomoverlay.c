/* j/0/weapons/zoomoverlay.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/weapons/zoomoverlay.c:56  [size]
void __cdecl ZoomOverlay_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  LOBYTE(ptQTask[1].ptNext) = 0;
}

// source: j/0/weapons/zoomoverlay.c:72  [anchor-strings]
void __cdecl ZoomOverlay_CreateParameterHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *v2; // esi
  struct QTask_s *v3; // edi
  struct QTask_s *v4; // eax
  char *p_tQTaskRefList; // ecx

  v2 = QTask_NewFn(nullptr, ZoomOverlay_eQTaskType, nullptr);
  v3 = *((struct QTask_s **)pxContext + 1);
  *((_DWORD *)pxContext + 2) = v2;
  v4 = TagItem_Find(v3, (char *)&stru_68FBBC);
  if ( v4 || (v4 = TagItem_NewString256(v3, (char *)&stru_68FBBC, (char *)&g_zInitialValue)) != nullptr )
    p_tQTaskRefList = (char *)&v4[7].tQTaskRefList;
  else
    p_tQTaskRefList = (char *)&g_zInitialValue;
  strcpy((char *)&v2[1], p_tQTaskRefList);
}

// source: j/0/weapons/zoomoverlay.c:95  [size]
void __cdecl ZoomOverlay_StatusDisplayHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ;
}

// source: j/0/weapons/zoomoverlay.c:112  [anchor-hash]
void __cdecl ZoomOverlay_Open()
{
  unsigned __int16 v0; // si

  v0 = QTask_NewQTaskType("ZoomOverlay", 296, WeaponTypeParameters_eQTaskType, 0, 0);
  ZoomOverlay_eQTaskType = v0;
  QTask_LinkQTaskEventHandlerFn(
    v0,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveNoChildrenHandler);
  QTask_LinkQTaskEventHandlerFn(v0, 0, (void (__cdecl *)(struct QTask_s *, void *))ZoomOverlay_CreateHandler);
  QTask_LinkQTaskEventHandlerFn(v0, WeaponType_eCreateParametersQTaskEvent, ZoomOverlay_CreateParameterHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    StatusScreen_eStatusDisplayQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))ZoomOverlay_StatusDisplayHandler);
  Symbol_Register(
    "TASKTYPE_ZOOMOVERLAY",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)v0,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
}

// source: j/0/weapons/zoomoverlay.c:141  [size]
void __cdecl ZoomOverlay_Close()
{
  QTask_DeleteQTaskType(ZoomOverlay_eQTaskType);
}

// source: j/0/weapons/zoomoverlay.c:155  [size]
unsigned __int16 __cdecl ZoomOverlay_GetQTaskType()
{
  return ZoomOverlay_eQTaskType;
}
