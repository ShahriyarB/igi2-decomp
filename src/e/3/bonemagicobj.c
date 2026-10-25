/* e/3/bonemagicobj.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: e/3/bonemagicobj.c:32  [anchor-mhash]
void __cdecl BoneMagicObj_CreateHandler(struct QTask_s *ptQTask, void *pxData)
{
  struct LODVirModel_s *LODVirModelExistsFn; // eax

  LODVirModelExistsFn = MTP_GetLODVirModelExistsFn(*(char **)pxData);
  if ( !LODVirModelExistsFn )
  {
    LDebug_Error("VirModel \"%s\" not available", *(char **)pxData);
    abort();
  }
  qmemcpy(&ptQTask[3].ptPrev, (char *)pxData + 44, sizeof(struct QTask_s));
  ptQTask[10].ptNext = *((struct QTask_s **)pxData + 31);
  ptQTask[7].ptPrev = *((struct QTask_s **)pxData + 35);
  ptQTask[2].tQTaskRefList.ptTail = *((struct QReference_s **)pxData + 34);
  BoneDynCubeObj_SetLODVirModel((struct BoneDynCubeObj_s *)ptQTask, LODVirModelExistsFn);
  ModelObj_AttachToParent((struct ModelObj_s *)ptQTask, (struct MagicObjCreateContext_s *)pxData);
}

// source: e/3/bonemagicobj.c:83  [size]
// attributes: thunk
void __cdecl BoneMagicObj_BoneMagicObjEnterHandler(struct QTask_s *ptQTask, void *pxContext)
{
  BoneDynCubeObj_EnterHandler(ptQTask, pxContext);
}

// source: e/3/bonemagicobj.c:108  [size]
void __cdecl BoneMagicObj_UpdateMagicObjHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *ptHead; // ecx
  int v3; // edx
  struct QTask_s *v4; // eax
  void (__cdecl *pfHandler)(struct QTask_s *, struct UpdateMagicObjContext_t *); // eax
  int v6; // edx
  struct UpdateMagicObjContext_t tUpdateMagicObjContext; // [esp+4h] [ebp-Ch] BYREF

  ptQTask[5].tQTaskRefList.ptTail = *((struct QReference_s **)pxContext + 1);
  ptQTask[5].tQTaskRefList.ptMiddle = *(struct QReference_s **)pxContext;
  *(_DWORD *)&ptQTask[5].eQTaskType = 0;
  ptQTask[5].ptParent = nullptr;
  ModelObj_UpdateAttachment((struct ModelObj_s *)ptQTask);
  tUpdateMagicObjContext.ptParentPos = (struct real64x3_t *)&ptQTask[1];
  ptHead = ptQTask->tQTaskChildren.ptHead;
  tUpdateMagicObjContext.ptParentOrientation = (struct real32x9_t *)&ptQTask[3].ptPrev;
  tUpdateMagicObjContext.ptTriggeredBy = ptQTask;
  if ( ptHead->ptNext && ptHead )
  {
    v3 = QTask_nProtectedQTaskStackOffset;
    do
    {
      if ( ptHead->ptNext )
        v4 = ptHead->ptNext->ptNext != nullptr ? ptHead->ptNext : nullptr;
      else
        v4 = nullptr;
      QTask_atProtectedQTaskStack[v3].ptQTask = v4;
      pfHandler = (void (__cdecl *)(struct QTask_s *, struct UpdateMagicObjContext_t *))QTask_aatQTaskFinalEvent[MagicObj_eUpdateMagicObjEvent][ptHead->eQTaskType].pfHandler;
      v6 = v3 + 1;
      QTask_nProtectedQTaskStackOffset = v6;
      if ( pfHandler )
      {
        pfHandler(ptHead, &tUpdateMagicObjContext);
        v6 = QTask_nProtectedQTaskStackOffset;
      }
      ptHead = (struct QTask_s *)dword_849C7DC[v6];
      v3 = v6 - 1;
      QTask_nProtectedQTaskStackOffset = v3;
    }
    while ( ptHead );
  }
}

// source: e/3/bonemagicobj.c:148  [size]
void __cdecl BoneMagicObj_CollisionEvaluateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *v2; // eax

  v2 = *((struct QTask_s **)pxContext + 1);
  *(_BYTE *)pxContext = ptQTask != v2 && ptQTask[10].ptNext != v2;
}

// source: e/3/bonemagicobj.c:168  [size]
void __cdecl BoneMagicObj_DeleteHandler(struct QTask_s *ptQTask)
{
  BoneDynCubeObj_SetLODVirModel((struct BoneDynCubeObj_s *)ptQTask, nullptr);
}

// source: e/3/bonemagicobj.c:187  [anchor-strings]
void __cdecl BoneMagicObj_Open()
{
  unsigned __int16 v0; // si

  v0 = QTask_NewQTaskType("BoneMagicObj", 408, BoneDynCubeObj_eQTaskType, 0, 0);
  LOWORD(CubeOcclusion_vScreenSizeX) = v0;
  QTask_LinkQTaskEventHandlerFn(v0, 5, nullptr);
  QTask_LinkQTaskEventHandlerFn(v0, MagicObj_eMagicObjEnterEvent, BoneMagicObj_BoneMagicObjEnterHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 1, nullptr);
  QTask_LinkQTaskEventHandlerFn(v0, 0, BoneMagicObj_CreateHandler);
  QTask_LinkQTaskEventHandlerFn(v0, MagicObj_eUpdateMagicObjEvent, BoneMagicObj_UpdateMagicObjHandler);
  QTask_LinkQTaskEventHandlerFn(v0, 13, BoneMagicObj_CollisionEvaluateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 2, BoneMagicObj_DeleteHandler);
  Symbol_Register(
    "TASKTYPE_BONEMAGICOBJ",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)v0,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
}

// source: e/3/bonemagicobj.c:213  [size]
void __cdecl BoneMagicObj_Close()
{
  QTask_DeleteQTaskType(LOWORD(CubeOcclusion_vScreenSizeX));
  LOWORD(CubeOcclusion_vScreenSizeX) = 512;
}

// source: e/3/bonemagicobj.c:231  [size]
unsigned __int16 __cdecl BoneMagicObj_GetQTaskType()
{
  return LOWORD(CubeOcclusion_vScreenSizeX);
}
