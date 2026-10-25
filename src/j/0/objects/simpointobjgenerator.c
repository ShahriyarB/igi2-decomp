/* j/0/objects/simpointobjgenerator.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/objects/simpointobjgenerator.c:83  [anchor-mhash]
void __cdecl SimpointObjGenerator_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct World_s *ptDynCubeObj; };
    struct { float ptDynCubeObja; };
    struct { char igi2_o2[20]; struct real64x3_t tNull; };
    char igi2_extent[44];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  double v2; // st7
  double v3; // st7
  int *v4; // eax
  int v5; // eax
  double v6; // st6

  igi2_frame.ptDynCubeObj = Game_ptGame->ptWorld;
  memset(&igi2_frame.tNull, 0, sizeof(igi2_frame.tNull));
  ModelObj_Init((struct ModelObj_s *)ptQTask, igi2_frame.ptDynCubeObj, nullptr);
  ptQTask[7].tQTaskChildren.ptHead = nullptr;
  ptQTask[7].tQTaskChildren.ptMiddle = (struct QTask_s *)2;
  ptQTask[7].tQTaskRefList.ptHead = nullptr;
  ptQTask[7].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[7].tQTaskRefList.ptTail = nullptr;
  ptQTask[7].ptParent = nullptr;
  *(_DWORD *)&ptQTask[7].eQTaskType = 0;
  if ( *(float *)&ptQTask[6].tQTaskChildren.ptHead <= (double)*(float *)&ptQTask[6].tQTaskChildren.ptMiddle )
    v2 = *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
  else
    v2 = *(float *)&ptQTask[6].tQTaskChildren.ptHead;
  if ( v2 >= *(float *)&ptQTask[6].ptPrev )
  {
    if ( *(float *)&ptQTask[6].tQTaskChildren.ptHead <= (double)*(float *)&ptQTask[6].tQTaskChildren.ptMiddle )
      v3 = *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
    else
      v3 = *(float *)&ptQTask[6].tQTaskChildren.ptHead;
  }
  else
  {
    v3 = *(float *)&ptQTask[6].ptPrev;
  }
  v4 = *(int **)&ptQTask[2].eQTaskType;
  if ( v4 && (v5 = *v4) != 0 )
    v6 = *(float *)(*(_DWORD *)(*(_DWORD *)(v5 + 12) + 12) + 120);
  else
    v6 = 1.0;
  igi2_frame.ptDynCubeObja = v3 * v6;
  World_RegisterDynCubeObjFirstTimeRadius(
    Game_ptGame->ptWorld,
    (struct DynCubeObj_s *)ptQTask,
    &igi2_frame.tNull,
    igi2_frame.ptDynCubeObja,
    WORLD_DYNCUBETREE_CATEGORY_MOBILE);
  ptQTask[3].tQTaskChildren.ptHead = nullptr;
  ptQTask[3].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[3].tQTaskChildren.ptTail = nullptr;
  ptQTask[3].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[3].tQTaskRefList.ptTail = nullptr;
  ptQTask[3].ptParent = nullptr;
  ptQTask[4].ptNext = nullptr;
  ptQTask[8].ptNext = nullptr;
  LOBYTE(ptQTask[8].ptPrev) = 0;
  LOBYTE(ptQTask[8].tQTaskRefList.ptHead) = 0;
  LOBYTE(ptQTask[8].eQTaskType) = 0;
  ptQTask[9].ptParent = nullptr;
  *(_DWORD *)&ptQTask[9].eQTaskType = 0;
  ptQTask[10].ptNext = nullptr;
  ptQTask[10].tQTaskChildren.ptHead = nullptr;
  ptQTask[10].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[10].tQTaskChildren.ptTail = nullptr;
  ptQTask[3].ptPrev = (struct QTask_s *)1065353216;
  ptQTask[3].tQTaskRefList.ptHead = (struct QReference_s *)1065353216;
  *(_DWORD *)&ptQTask[3].eQTaskType = 1065353216;
  ptQTask[9].tQTaskChildren.ptMiddle = (struct QTask_s *)30;
  ptQTask[9].tQTaskChildren.ptTail = (struct QTask_s *)15;
  ptQTask[9].tQTaskRefList.ptHead = (struct QReference_s *)1065017672;
  ptQTask[9].tQTaskRefList.ptMiddle = (struct QReference_s *)1065353216;
  ptQTask[9].tQTaskRefList.ptTail = (struct QReference_s *)1092616192;
  ptQTask[10].ptPrev = (struct QTask_s *)1065353216;
}

// source: j/0/objects/simpointobjgenerator.c:137  [size]
void __cdecl SimpointObjGenerator_DeleteHandler(struct QTask_s *ptQTask)
{
  World_RemoveDynCubeObj((struct World_s *)ptQTask[2].ptParent, (struct DynCubeObj_s *)ptQTask);
}

// source: j/0/objects/simpointobjgenerator.c:157  [anchor-caller]
void __cdecl SimpointObjGenerator_RunHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptNext; // edx
  struct QTask_s *ptPrev; // eax
  struct SimpointObjContainer_s *ptParent; // ecx
  struct real32x3_t tVelocity; // [esp+4h] [ebp-Ch] BYREF

  if ( !ptQTask[9].ptParent )
    ptQTask[9].ptParent = (struct QTask_s *)SimpointObjContainer_New(
                                              30 * (int)ptQTask[9].tQTaskChildren.ptMiddle,
                                              (char *)&ptQTask[8].tQTaskRefList,
                                              (char *)&ptQTask[8].eQTaskType,
                                              *(float *)&ptQTask[9].tQTaskRefList.ptHead,
                                              *(float *)&ptQTask[9].tQTaskRefList.ptMiddle,
                                              44.600887298583984,
                                              *(float *)&ptQTask[9].tQTaskRefList.ptTail,
                                              (struct real32x3_t *)&ptQTask[10].tQTaskChildren,
                                              0);
  if ( (int)ptQTask[8].ptNext <= 0 )
  {
    ptNext = ptQTask[10].ptNext;
    ptPrev = ptQTask[10].ptPrev;
    tVelocity.vX = *(float *)&ptQTask[9].eQTaskType;
    LODWORD(tVelocity.vY) = ptNext;
    LODWORD(tVelocity.vZ) = ptPrev;
    tVelocity.vX = tVelocity.vX * 4096.0;
    ptParent = (struct SimpointObjContainer_s *)ptQTask[9].ptParent;
    tVelocity.vY = *(float *)&ptNext * 4096.0;
    tVelocity.vZ = *(float *)&ptPrev * 4096.0;
    SimpointObjContainer_Add(
      ptParent,
      SimpointObj_eQTaskType,
      (struct real64x3_t *)&ptQTask[1],
      (struct real32x9_t *)&ptQTask[3].ptPrev,
      &tVelocity);
    ptQTask[8].ptNext = (struct QTask_s *)(30 * (int)ptQTask[9].tQTaskChildren.ptTail);
  }
  --*(int *)&ptQTask[8].ptNext;
}

// source: j/0/objects/simpointobjgenerator.c:211  [anchor-mhash]
void __cdecl SimpointObjGenerator_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { char zTempModel[128]; };
    struct { char igi2_o1[128]; char zString[128]; };
    char igi2_extent[256];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  char *p_ptPrev; // edi
  struct LODVirModel_s *LODVirModelExistsFn; // eax
  struct LODVirModel_s *v4; // ebp
  char *v5; // eax
  char v6; // cl

  p_ptPrev = (char *)&ptQTask[8].ptPrev;
  LODVirModelExistsFn = MTP_GetLODVirModelExistsFn((char *)&ptQTask[8].ptPrev);
  if ( LODVirModelExistsFn )
  {
    v4 = LODVirModelExistsFn;
  }
  else
  {
    v4 = nullptr;
    if ( ptQTask != (struct QTask_s *)-324 && BYTE1(ptQTask[8].ptPrev) != 42 )
    {
      sprintf(igi2_frame.zString, "Model \"%s\" not available", p_ptPrev);
      v5 = (char *)&ptQTask[8].ptPrev;
      do
      {
        v6 = *v5;
        v5[igi2_frame.zTempModel - p_ptPrev] = *v5;
        ++v5;
      }
      while ( v6 );
      sprintf(p_ptPrev, "** %s **", igi2_frame.zTempModel);
    }
  }
  if ( v4 != *(struct LODVirModel_s **)&ptQTask[2].eQTaskType )
  {
    ModelObj_SetLODVirModel((struct ModelObj_s *)ptQTask, v4, false);
    ptQTask[7].tQTaskRefList.ptHead = nullptr;
    ptQTask[7].tQTaskRefList.ptMiddle = nullptr;
    ptQTask[7].tQTaskRefList.ptTail = nullptr;
    ptQTask[7].ptParent = nullptr;
    *(_DWORD *)&ptQTask[7].eQTaskType = 0;
  }
  ptQTask[8].ptNext = nullptr;
}

// source: j/0/objects/simpointobjgenerator.c:259  [size]
void __cdecl SimpointObjGenerator_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = SimpointObjGenerator_ptParameterList;
}

// source: j/0/objects/simpointobjgenerator.c:319  [anchor-strings]
void __cdecl SimpointObjGenerator_Open()
{
  unsigned __int16 v0; // si
  struct ParameterList_s *v1; // eax

  v0 = QTask_NewQTaskType((char *)&g_zMessage_0.tDownload.vViewLength, 424, RigidDynCubeObj_eQTaskType, 0, 0);
  SimpointObjGenerator_eQTaskType = v0;
  QTask_LinkQTaskEventHandlerFn(
    v0,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveHandler);
  QTask_LinkQTaskEventHandlerFn(v0, 0, SimpointObjGenerator_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 1, SimpointObjGenerator_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 2, SimpointObjGenerator_DeleteHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))SimpointObjGenerator_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    ParameterList_eUpdateInternalDataQTaskEvent,
    SimpointObjGenerator_UpdateInternalDataHandler);
  v1 = (struct ParameterList_s *)Mem_AllocFn(272, 4);
  v1->nParameters = 0;
  v1->nMaxParameters = 13;
  v1->ptParameterListItem = (struct ParameterListItem_s *)&v1[1];
  SimpointObjGenerator_ptParameterList = v1;
  dword_752930 = 0;
  unk_752934 = 0;
  unk_752938 = 0;
  unk_75293C = 1072693248;
  dword_752920 = 0;
  unk_752924 = 0;
  unk_752928 = 0;
  unk_75292C = 1072693248;
  dword_752968 = 0;
  unk_75296C = 0;
  unk_752970 = 0;
  unk_752974 = 1083129856;
  dword_752950 = 0;
  unk_752954 = 0;
  unk_752958 = 0;
  unk_75295C = 1082310656;
  dword_752940 = 0;
  unk_752944 = 0;
  unk_752948 = 0;
  unk_75294C = 1081262080;
  ParameterList_AddParameter(v1, 0x28u, Level_eParameterTypeObjectPos, "Position", 7u, nullptr);
  ParameterList_AddParameter(
    SimpointObjGenerator_ptParameterList,
    0x7Cu,
    Level_eParameterTypeReal32x9,
    "Orientation",
    7u,
    nullptr);
  ParameterList_AddParameter(
    SimpointObjGenerator_ptParameterList,
    0x144u,
    Level_eParameterTypeString16,
    (char *)&g_zMessage_0.ptHumanQTaskRef,
    7u,
    nullptr);
  ParameterList_AddParameter(
    SimpointObjGenerator_ptParameterList,
    0x154u,
    Level_eParameterTypeString16,
    (char *)&g_zMessage_0.nUpdateItemTime,
    7u,
    nullptr);
  ParameterList_AddParameter(
    SimpointObjGenerator_ptParameterList,
    0x164u,
    Level_eParameterTypeString16,
    (char *)&g_zMessage_0.nMoney,
    7u,
    nullptr);
  ParameterList_AddParameter(
    SimpointObjGenerator_ptParameterList,
    0x174u,
    Level_eParameterTypeInt32,
    &g_zMessage_0.zTalkString[240],
    7u,
    &dword_752950);
  ParameterList_AddParameter(
    SimpointObjGenerator_ptParameterList,
    0x178u,
    Level_eParameterTypeInt32,
    &g_zMessage_0.zTalkString[212],
    7u,
    &dword_752940);
  ParameterList_AddParameter(
    SimpointObjGenerator_ptParameterList,
    0x17Cu,
    Level_eParameterTypeReal32,
    &g_zMessage_0.zTalkString[196],
    7u,
    &dword_752930);
  ParameterList_AddParameter(
    SimpointObjGenerator_ptParameterList,
    0x180u,
    Level_eParameterTypeReal32,
    &g_zMessage_0.zTalkString[180],
    7u,
    &dword_752920);
  ParameterList_AddParameter(
    SimpointObjGenerator_ptParameterList,
    0x184u,
    Level_eParameterTypeReal32,
    &g_zMessage_0.zTalkString[172],
    7u,
    &dword_752968);
  ParameterList_AddParameter(
    SimpointObjGenerator_ptParameterList,
    0x18Cu,
    Level_eParameterTypeReal32x3,
    "Velocity",
    7u,
    nullptr);
  ParameterList_AddParameter(
    SimpointObjGenerator_ptParameterList,
    0x198u,
    Level_eParameterTypeReal32x3,
    &g_zMessage_0.zTalkString[152],
    7u,
    nullptr);
}

// source: j/0/objects/simpointobjgenerator.c:382  [size]
void __cdecl SimpointObjGenerator_Close()
{
  int v0; // esi

  if ( SimpointObjGenerator_ptParameterList )
  {
    v0 = *(_DWORD *)((unsigned int)&SimpointObjGenerator_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
  QTask_DeleteQTaskType(SimpointObjGenerator_eQTaskType);
}

// source: j/0/objects/simpointobjgenerator.c:399  [size]
unsigned __int16 __cdecl SimpointObjGenerator_GetQTaskType()
{
  return SimpointObjGenerator_eQTaskType;
}
