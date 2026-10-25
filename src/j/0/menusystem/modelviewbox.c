/* j/0/menusystem/modelviewbox.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/menusystem/modelviewbox.c:78  [anchor-caller]
void __cdecl ModelViewBox_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { float ptOrientation; };
    struct { char igi2_o1[36]; struct real64x3_t vAspect; };
    struct { char igi2_o2[60]; struct real32x9_t ptPos; };
    char igi2_extent[100];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QReference_s *v3; // eax

  memset(&igi2_frame.vAspect, 0, sizeof(igi2_frame.vAspect));
  ((void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[0][MenuWindow_eQTaskType].pfHandler)(
    ptQTask,
    pxContext);
  ptQTask[1].tQTaskRefList.ptTail = (struct QReference_s *)1;
  ptQTask[1].ptParent = (struct QTask_s *)1;
  ptQTask[1].tQTaskChildren.ptHead = (struct QTask_s *)300;
  ptQTask[1].tQTaskChildren.ptMiddle = (struct QTask_s *)200;
  LOBYTE(ptQTask[2].tQTaskChildren.ptMiddle) = 0;
  ptQTask[2].tQTaskChildren.ptTail = (struct QTask_s *)World_New(4096);
  ptQTask[2].tQTaskRefList.ptMiddle = (struct QReference_s *)1065353216;
  ptQTask[3].ptNext = (struct QTask_s *)1065353216;
  ptQTask[3].tQTaskChildren.ptTail = (struct QTask_s *)1065353216;
  igi2_frame.ptPos.tX.vX = 1.0;
  igi2_frame.ptPos.tY.vY = 1.0;
  igi2_frame.ptPos.tZ.vZ = 1.0;
  ptQTask[4].tQTaskRefList.ptTail = nullptr;
  ptQTask[4].tQTaskRefList.ptHead = (struct QReference_s *)-1082130432;
  ptQTask[3].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[3].tQTaskRefList.ptTail = nullptr;
  ptQTask[3].ptParent = nullptr;
  *(_DWORD *)&ptQTask[3].eQTaskType = 0;
  ptQTask[4].ptNext = nullptr;
  ptQTask[4].ptPrev = nullptr;
  ptQTask[2].tQTaskRefList.ptTail = nullptr;
  ptQTask[2].ptParent = nullptr;
  *(_DWORD *)&ptQTask[2].eQTaskType = 0;
  ptQTask[3].ptPrev = nullptr;
  ptQTask[3].tQTaskChildren.ptHead = nullptr;
  ptQTask[3].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[3].tQTaskRefList.ptHead = nullptr;
  ptQTask[4].tQTaskChildren.ptMiddle = (struct QTask_s *)1137495245;
  memset(&igi2_frame.ptPos.tX.vY, 0, 12);
  memset(&igi2_frame.ptPos.tY.vZ, 0, 12);
  igi2_frame.ptPos.nOps = 0;
  igi2_frame.ptOrientation = tan(0.7853981852531433);
  QCamera_Set(
    (struct QCamera_s *)&ptQTask[2].tQTaskRefList.ptMiddle,
    &igi2_frame.vAspect,
    &igi2_frame.ptPos,
    igi2_frame.ptOrientation,
    1.0,
    300.0,
    Screen_nFrameNumber,
    ptQTask,
    0.0,
    0);
  v3 = (struct QReference_s *)ViewportQTask_New(
                                *(struct QTask_s **)(*(_DWORD *)&ptQTask[1].eQTaskType + 32),
                                0.0,
                                0.0,
                                1.0,
                                1.0,
                                (struct World_s *)ptQTask[2].tQTaskChildren.ptTail,
                                (struct QCamera_s *)&ptQTask[2].tQTaskRefList.ptMiddle,
                                0,
                                0.0,
                                0.0,
                                0.0,
                                1.0);
  ptQTask[2].tQTaskRefList.ptHead = v3;
  v3[34].ptPrev = nullptr;
}

void __cdecl sub_53BAA0(struct QTask_s *a1)
{
  QTask_Delete(a1[5].tQTaskChildren.ptMiddle);
  QTask_Delete((struct QTask_s *)a1[2].tQTaskRefList.ptHead);
  World_Delete((struct World_s *)a1[2].tQTaskChildren.ptTail);
  ((void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[Level_eRemoveLevelScriptSymbolsEvent][a1->eQTaskType].pfHandler)(a1);
}

// source: j/0/menusystem/modelviewbox.c:176  [anchor-strings]
void __cdecl ModelViewBox_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct ModelObj_s *v2; // edx
  struct QTask_s *ptTail; // eax
  struct QTask_s *ptPrev; // ecx
  struct QTask_s *ptMiddle; // ecx

  Mesh3D_atAmbientColor[1].vX = 0.5;
  Mesh3D_atAmbientColor[1].vY = 0.5;
  Mesh3D_atAmbientColor[1].vZ = 0.5;
  ((void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[ParameterList_eUpdateInternalDataQTaskEvent][MenuWindow_eQTaskType].pfHandler)(
    ptQTask,
    pxContext);
  ptQTask[5].tQTaskChildren.ptHead = (struct QTask_s *)MTP_GetLODVirModelExistsFn("minefield");
  v2 = (struct ModelObj_s *)QTask_NewFn(ptQTask, RigidDynCubeObj_eQTaskType, nullptr);
  LODWORD(v2->tDynCubeObj.tQObj.tPos.vX) = 0;
  HIDWORD(v2->tDynCubeObj.tQObj.tPos.vX) = 0;
  LODWORD(v2->tDynCubeObj.tQObj.tPos.vY) = 0;
  HIDWORD(v2->tDynCubeObj.tQObj.tPos.vY) = 0;
  LODWORD(v2->tDynCubeObj.tQObj.tPos.vZ) = 0;
  HIDWORD(v2->tDynCubeObj.tQObj.tPos.vZ) = 0;
  ModelObj_Init(
    v2,
    (struct World_s *)ptQTask[2].tQTaskChildren.ptTail,
    (struct LODVirModel_s *)ptQTask[5].tQTaskChildren.ptHead);
  v2[1].tDynCubeObj.tQObj.tQTask.ptNext = nullptr;
  v2[1].tDynCubeObj.tQObj.tQTask.ptPrev = (struct QTask_s *)2;
  v2[1].tDynCubeObj.tQObj.tQTask.tQTaskChildren.ptMiddle = nullptr;
  v2[1].tDynCubeObj.tQObj.tQTask.tQTaskChildren.ptTail = nullptr;
  v2[1].tDynCubeObj.tQObj.tQTask.tQTaskRefList.ptHead = nullptr;
  v2[1].tDynCubeObj.tQObj.tQTask.tQTaskRefList.ptMiddle = nullptr;
  v2[1].tDynCubeObj.tQObj.tQTask.tQTaskRefList.ptTail = nullptr;
  ptTail = ptQTask[2].tQTaskChildren.ptTail;
  ptPrev = ptTail[2].ptPrev;
  if ( ptPrev )
  {
    ptPrev[2].tQTaskChildren.ptMiddle = &v2->tDynCubeObj.tQObj.tQTask;
    ptTail[2].ptPrev[2].tQTaskChildren.ptMiddle[2].tQTaskChildren.ptTail = ptTail[2].ptPrev;
    ptMiddle = ptTail[2].ptPrev[2].tQTaskChildren.ptMiddle;
    ptTail[2].ptPrev = ptMiddle;
    ptMiddle[2].tQTaskChildren.ptMiddle = nullptr;
  }
  else
  {
    ptTail[2].ptPrev = &v2->tDynCubeObj.tQObj.tQTask;
    v2->tDynCubeObj.ptNext = nullptr;
    ptTail[2].ptPrev[2].tQTaskChildren.ptMiddle = nullptr;
  }
  ptQTask[5].tQTaskChildren.ptMiddle = &v2->tDynCubeObj.tQObj.tQTask;
}

// source: j/0/menusystem/modelviewbox.c:220  [size]
void __cdecl ModelViewBox_RunHandler(struct QTask_s *ptQTask)
{
  ((void (__cdecl *)())QTask_aatQTaskFinalEvent[1][MenuWindow_eQTaskType].pfHandler)(ptQTask);
}

// source: j/0/menusystem/modelviewbox.c:247  [anchor-mhash]
void __cdecl ModelViewBox_DrawHandler(struct QTask_s *ptQTask)
{
  double v2; // st7
  float ptQTaska = *(float *)&ptQTask; // [esp+8h] [ebp+4h] ARGSLOT

  v2 = (double)(*(_DWORD *)(*(_DWORD *)&ptQTask[1].eQTaskType + 356) - 8) * 0.125;
  if ( v2 <= 0.0 )
    ptQTaska = 0.0;
  else
    ptQTaska = v2;
  MenuWindow_DrawBorder((struct MenuWindow_t *)ptQTask, 0.0, ptQTaska, 0);
  ((void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[Screen_eDrawQTaskEvent][MenuWindow_eQTaskType].pfHandler)(ptQTask);
}

// source: j/0/menusystem/modelviewbox.c:273  [size]
void __cdecl ModelViewBox_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = ModelViewBox_ptParameterList;
}

// source: j/0/menusystem/modelviewbox.c:290  [anchor-mhash]
void __cdecl ModelViewBox_RegisterScriptSymbolsHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { char zName[64]; };
    struct { char igi2_o1[64]; char zTemp[128]; };
    char igi2_extent[192];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)

  if ( !LOBYTE(ptQTask[2].tQTaskChildren.ptMiddle) )
  {
    LOBYTE(ptQTask[2].tQTaskChildren.ptMiddle) = 1;
    Level_GetUniqueQTaskNameFromTask(igi2_frame.zName, ptQTask);
    sprintf(igi2_frame.zTemp, "%s.isOn", igi2_frame.zName);
  }
}

// source: j/0/menusystem/modelviewbox.c:319  [anchor-mhash]
void __cdecl ModelViewBox_RemoveScriptSymbolsHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { char zName[64]; };
    struct { char igi2_o1[64]; char zTemp[128]; };
    char igi2_extent[192];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)

  if ( LOBYTE(ptQTask[2].tQTaskChildren.ptMiddle) )
  {
    Level_GetUniqueQTaskNameFromTask(igi2_frame.zName, ptQTask);
    sprintf(igi2_frame.zTemp, "%s.isOn", igi2_frame.zName);
    LOBYTE(ptQTask[2].tQTaskChildren.ptMiddle) = 0;
  }
}

// source: j/0/menusystem/modelviewbox.c:352  [anchor-strings]
void __cdecl ModelViewBox_Open()
{
  unsigned __int16 v0; // si
  struct ParameterList_s *v1; // eax
  int v2; // edx

  v0 = QTask_NewQTaskType("ModelViewBox", 216, MenuWindow_eQTaskType, 0, 0);
  ModelViewBox_eQTaskType = v0;
  QTask_LinkQTaskEventHandlerFn(
    v0,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 1, (void (__cdecl *)(struct QTask_s *))ModelViewBox_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, Screen_eDrawQTaskEvent, ModelViewBox_DrawHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 2, sub_53BAA0);
  QTask_LinkQTaskEventHandlerFn(v0, 0, ModelViewBox_CreateHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))ModelViewBox_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(v0, ParameterList_eUpdateInternalDataQTaskEvent, ModelViewBox_UpdateInternalDataHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(
    v0,
    Level_eRegisterLevelScriptSymbolsEvent,
    ModelViewBox_RegisterScriptSymbolsHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(
    v0,
    Level_eRemoveLevelScriptSymbolsEvent,
    ModelViewBox_RemoveScriptSymbolsHandler);
  dword_79EEEE8 = 0;
  dword_79EEEEC = 0;
  dword_79EEEF0 = 0;
  dword_79EEEF4 = 1082392576;
  v1 = (struct ParameterList_s *)Mem_AllocFn(52, 4);
  v1->nParameters = 0;
  v2 = Level_eParameterTypeInt32;
  v1->ptParameterListItem = (struct ParameterListItem_s *)&v1[1];
  v1->nMaxParameters = 2;
  ModelViewBox_ptParameterList = v1;
  ParameterList_AddParameter(v1, 0x30u, v2, "X-Pos", 7u, &dword_79EEEE8);
  ParameterList_AddParameter(
    ModelViewBox_ptParameterList,
    0x34u,
    Level_eParameterTypeInt32,
    "Y-Pos",
    7u,
    &dword_79EEEE8);
}

// source: j/0/menusystem/modelviewbox.c:393  [size]
void __cdecl ModelViewBox_Close()
{
  int v0; // esi

  if ( ModelViewBox_ptParameterList )
  {
    v0 = *(_DWORD *)((unsigned int)&ModelViewBox_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
  QTask_DeleteQTaskType(ModelViewBox_eQTaskType);
  ModelViewBox_eQTaskType = 512;
}
