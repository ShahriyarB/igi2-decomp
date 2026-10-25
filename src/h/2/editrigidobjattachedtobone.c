/* h/2/editrigidobjattachedtobone.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: h/2/editrigidobjattachedtobone.c:36  [anchor-mhash]
void __cdecl EditRigidObjAttachedToBone_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct World_s *v5; };
    struct { char igi2_o1[12]; struct real64x3_t tPos; };
    char igi2_extent[36];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int *v3; // eax
  int v4; // eax
  float ptQTaska = *(float *)&ptQTask; // [esp+20h] [ebp+4h] ARGSLOT

  ptQTask[8].tQTaskChildren.ptMiddle = (struct QTask_s *)1065353216;
  ptQTask[8].tQTaskRefList.ptTail = (struct QReference_s *)1065353216;
  ptQTask[9].ptPrev = (struct QTask_s *)1065353216;
  igi2_frame.v5 = World_ptActiveWorld;
  memset(&igi2_frame.tPos, 0, sizeof(igi2_frame.tPos));
  ptQTask[8].ptNext = nullptr;
  ptQTask[8].ptPrev = nullptr;
  ptQTask[8].tQTaskChildren.ptHead = nullptr;
  ptQTask[8].tQTaskChildren.ptTail = nullptr;
  ptQTask[8].tQTaskRefList.ptHead = nullptr;
  ptQTask[8].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[8].ptParent = nullptr;
  *(_DWORD *)&ptQTask[8].eQTaskType = 0;
  ptQTask[9].ptNext = nullptr;
  ptQTask[9].tQTaskChildren.ptHead = nullptr;
  ptQTask[9].tQTaskChildren.ptMiddle = nullptr;
  LOWORD(ptQTask[9].tQTaskChildren.ptTail) = 42;
  ModelObj_Init((struct ModelObj_s *)ptQTask, igi2_frame.v5, nullptr);
  ptQTask[7].tQTaskChildren.ptHead = nullptr;
  ptQTask[7].tQTaskChildren.ptMiddle = (struct QTask_s *)2;
  ptQTask[7].tQTaskRefList.ptHead = nullptr;
  ptQTask[7].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[7].tQTaskRefList.ptTail = nullptr;
  ptQTask[7].ptParent = nullptr;
  *(_DWORD *)&ptQTask[7].eQTaskType = 0;
  v3 = *(int **)&ptQTask[2].eQTaskType;
  if ( v3 && (v4 = *v3) != 0 )
    ptQTaska = *(float *)(*(_DWORD *)(*(_DWORD *)(v4 + 12) + 12) + 120);
  else
    ptQTaska = 1.0;
  World_RegisterDynCubeObjFirstTimeRadius(
    (struct World_s *)ptQTask[2].ptParent,
    (struct DynCubeObj_s *)ptQTask,
    &igi2_frame.tPos,
    ptQTaska,
    WORLD_DYNCUBETREE_CATEGORY_MOBILE);
}

// source: h/2/editrigidobjattachedtobone.c:67  [size]
void __cdecl EditRigidObjAttachedToBone_DeleteHandler(struct QTask_s *ptQTask)
{
  World_RemoveDynCubeObj((struct World_s *)ptQTask[2].ptParent, (struct DynCubeObj_s *)ptQTask);
}

// source: h/2/editrigidobjattachedtobone.c:83  [size]
void __cdecl EditRigidObjAttachedToBone_RunHandler(struct QTask_s *ptQTask)
{
  ;
}

// source: h/2/editrigidobjattachedtobone.c:129  [anchor-mhash]
void __cdecl EditRigidObjAttachedToBone_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  char ptTail; // al
  char *p_ptTail; // esi
  struct LODVirModel_s *LODVirModelExistsFn; // eax
  char *v5; // eax
  char v6; // cl
  char zTemp[16]; // [esp+8h] [ebp-10h] BYREF

  ptTail = (char)ptQTask[9].tQTaskChildren.ptTail;
  p_ptTail = (char *)&ptQTask[9].tQTaskChildren.ptTail;
  if ( ptTail != 42 && ptTail )
  {
    LODVirModelExistsFn = MTP_GetLODVirModelExistsFn((char *)&ptQTask[9].tQTaskChildren.ptTail);
    if ( LODVirModelExistsFn )
    {
      *(_DWORD *)&ptQTask[2].eQTaskType = LODVirModelExistsFn;
    }
    else
    {
      v5 = (char *)&ptQTask[9].tQTaskChildren.ptTail;
      do
      {
        v6 = *v5;
        v5[zTemp - p_ptTail] = *v5;
        ++v5;
      }
      while ( v6 );
      sprintf(p_ptTail, "*%s", zTemp);
    }
  }
}

// source: h/2/editrigidobjattachedtobone.c:166  [size]
void __cdecl EditRigidObjAttachedToBone_GetParameterListHandler(
        struct QTask_s *ptQTask,
        void *pxContext)
{
  *(_DWORD *)pxContext = EditRigidObjAttachedToBone_ptParameterList;
}

// source: h/2/editrigidobjattachedtobone.c:212  [anchor-strings]
void __cdecl EditRigidObjAttachedToBone_Open()
{
  unsigned __int16 v0; // si
  struct ParameterList_s *v1; // eax
  int v2; // edx

  v0 = QTask_NewQTaskType("EditRigidObjAttachedToBone", 392, RigidDynCubeObj_eQTaskType, 0, 0);
  EditRigidObjAttachedToBone_eQTaskType = v0;
  QTask_LinkQTaskEventHandlerFn(v0, 0, EditRigidObjAttachedToBone_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 2, EditRigidObjAttachedToBone_DeleteHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(
    v0,
    1,
    (void (__cdecl *)(struct QTask_s *))EditRigidObjAttachedToBone_RunHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    ParameterList_eUpdateInternalDataQTaskEvent,
    EditRigidObjAttachedToBone_UpdateInternalDataHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))EditRigidObjAttachedToBone_GetParameterListHandler);
  v1 = (struct ParameterList_s *)Mem_AllocFn(92, 4);
  v2 = Level_eParameterTypeReal32x3;
  v1->ptParameterListItem = (struct ParameterListItem_s *)&v1[1];
  v1->nParameters = 0;
  v1->nMaxParameters = 4;
  EditRigidObjAttachedToBone_ptParameterList = v1;
  ParameterList_AddParameter(v1, 0x140u, v2, "Relative Position", 7u, nullptr);
  ParameterList_AddParameter(
    EditRigidObjAttachedToBone_ptParameterList,
    0x14Cu,
    Level_eParameterTypeReal32x9,
    "Relative Orientation",
    7u,
    nullptr);
  ParameterList_AddParameter(
    EditRigidObjAttachedToBone_ptParameterList,
    0x174u,
    Level_eParameterTypeInt32,
    "Magic Vertex",
    7u,
    nullptr);
  ParameterList_AddParameter(
    EditRigidObjAttachedToBone_ptParameterList,
    0x178u,
    Level_eParameterTypeString16,
    "Model Name",
    7u,
    nullptr);
}

// source: h/2/editrigidobjattachedtobone.c:244  [anchor-hash]
void __cdecl EditRigidObjAttachedToBone_Close()
{
  int v0; // esi

  QTask_DeleteQTaskType(EditRigidObjAttachedToBone_eQTaskType);
  if ( EditRigidObjAttachedToBone_ptParameterList )
  {
    v0 = *(_DWORD *)((unsigned int)&EditRigidObjAttachedToBone_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
}

// source: h/2/editrigidobjattachedtobone.c:261  [size]
unsigned __int16 __cdecl EditRigidObjAttachedToBone_GetQTaskType()
{
  return EditRigidObjAttachedToBone_eQTaskType;
}
