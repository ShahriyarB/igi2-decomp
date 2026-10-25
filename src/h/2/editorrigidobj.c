/* h/2/editorrigidobj.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: h/2/editorrigidobj.c:202  [anchor-strings]
void __cdecl EditorRigidObj_Open()
{
  unsigned __int16 BaseQTaskType; // ax
  unsigned __int16 v1; // si

  BaseQTaskType = QTask_GetBaseQTaskType();
  v1 = QTask_NewQTaskType("EditorRigidObj", 40, BaseQTaskType, 0, 0);
  EditorRigidObj_eQTaskType = v1;
  QTask_LinkQTaskEventHandlerFn(v1, 5, nullptr);
  QTask_LinkQTaskEventHandlerFn(v1, 10, nullptr);
  QTask_LinkQTaskEventHandlerFn(v1, 11, nullptr);
  QTask_LinkQTaskEventHandlerFn(v1, 12, nullptr);
  QTask_LinkQTaskEventHandlerFn(v1, Envmap_eEnumerateQTaskEvent, nullptr);
  QTask_LinkQTaskEventHandlerFn(v1, QCube_eGetClosestVertexQTaskEvent, nullptr);
  QTask_LinkQTaskEventHandlerFn(v1, 8, nullptr);
  QTask_LinkQTaskEventHandlerFn(v1, DynCubeObj_eDynCubeObjRemoveQTaskEvent, nullptr);
  QTask_LinkQTaskEventHandlerFn(v1, DynCubeObj_eDynCubeObjRegisterQTaskEvent, nullptr);
  QTask_LinkQTaskEventHandlerFn(v1, 9, nullptr);
}

// source: h/2/editorrigidobj.c:257  [size]
void __cdecl EditorRigidObj_Close()
{
  QTask_DeleteQTaskType(EditorRigidObj_eQTaskType);
}

// source: h/2/editorrigidobj.c:271  [size]
unsigned __int16 __cdecl EditorRigidObj_GetQTaskType()
{
  return EditorRigidObj_eQTaskType;
}
