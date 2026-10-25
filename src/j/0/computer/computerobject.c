/* j/0/computer/computerobject.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/computer/computerobject.c:134  [size]
void __cdecl ComputerObject_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ;
}

// source: j/0/computer/computerobject.c:146  [size]
void __cdecl ComputerObject_DeleteHandler(struct QTask_s *ptQTask)
{
  ;
}

// source: j/0/computer/computerobject.c:158  [anchor-strings]
void __cdecl ComputerObject_DrawHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { int iCount; };
    struct { char igi2_o1[4]; struct ComputerMap_s *ptComputerMap; };
    struct { char igi2_o2[8]; struct DrawComputerObjectContext_s tDrawComputerObjectContext; };
    char igi2_extent[52];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *v1; // ebx
  float vX; // edx
  char ptNext; // al
  int v4; // edi
  __int16 v5; // ax
  int v6; // esi
  int v7; // ecx
  void (__cdecl *pfHandler)(int, struct DrawComputerObjectContext_s *); // edx
  int v9; // edi
  int v10; // esi
  int v11; // ecx
  void (__cdecl *v12)(int, struct DrawComputerObjectContext_s *); // edx
  int v13; // edi
  int v14; // esi
  int v15; // ecx
  void (__cdecl *v16)(int, struct DrawComputerObjectContext_s *); // edx
  struct Client_s *ClientFromHumanQTask; // eax
  struct QTask_s *v18; // edx
  void (__cdecl *v19)(struct QTask_s *, struct DrawComputerObjectContext_s *); // ecx
  struct QTaskList_s *v20; // ecx
  int v21; // ebp
  int v22; // edi
  int v23; // edx
  void (__cdecl *v24)(int, struct DrawComputerObjectContext_s *); // esi
  __int16 v25; // di
  int v26; // ebp
  __int16 v27; // ax
  int v28; // edx
  void (__cdecl *v29)(int, struct DrawComputerObjectContext_s *); // esi
  struct QTask_s *ptSCameraLensQTask; // ecx
  int v31; // edi
  int v32; // esi
  int v33; // ecx
  void (__cdecl *v34)(int, struct DrawComputerObjectContext_s *); // edx
  int v35; // edi
  int v36; // esi
  int v37; // ecx
  void (__cdecl *v38)(int, struct DrawComputerObjectContext_s *); // edx

  v1 = ptQTask;
  igi2_frame.tDrawComputerObjectContext.ptCameraOrientation = (struct real32x9_t *)Game_ptGame->ptGameScreenQTask[1].ptPrev[2].tQTaskChildren.ptHead;
  igi2_frame.tDrawComputerObjectContext.ptCameraPos = (struct real64x3_t *)&igi2_frame.tDrawComputerObjectContext.ptCameraOrientation[1];
  vX = igi2_frame.tDrawComputerObjectContext.ptCameraOrientation[1].tZ.vX;
  igi2_frame.tDrawComputerObjectContext.eComputerObjectMarker = COMPUTEROBJECTMARKER_NONE;
  igi2_frame.tDrawComputerObjectContext.eComputerObjectMarkerColor = COMPUTEROBJECTMARKER_COLOR_NONE;
  ptNext = (char)ptQTask[1].ptNext;
  v4 = 0;
  igi2_frame.tDrawComputerObjectContext.vCameraFOV = vX;
  igi2_frame.tDrawComputerObjectContext.ptQSprite = nullptr;
  igi2_frame.tDrawComputerObjectContext.ptPos = nullptr;
  igi2_frame.tDrawComputerObjectContext.vRadius = 0.0;
  igi2_frame.tDrawComputerObjectContext.zTitle = nullptr;
  igi2_frame.tDrawComputerObjectContext.zInfo = nullptr;
  if ( (ptNext & 1) != 0 )
  {
    v5 = ComputerObject_eDrawComputerObjectQTaskEvent;
    if ( Human_ptQTaskList->nTask > 0 )
    {
      v6 = 8;
      do
      {
        if ( v5 == 512 )
        {
          v5 = QTask_NewQTaskEventFn(0x200u, "DrawComputerObject");
          ComputerObject_eDrawComputerObjectQTaskEvent = v5;
        }
        v7 = *(int *)((char *)&Human_ptQTaskList->nTask + v6);
        pfHandler = (void (__cdecl *)(int, struct DrawComputerObjectContext_s *))QTask_aatQTaskFinalEvent[v5][*(unsigned __int16 *)(v7 + 36)].pfHandler;
        if ( pfHandler )
        {
          pfHandler(v7, &igi2_frame.tDrawComputerObjectContext);
          v5 = ComputerObject_eDrawComputerObjectQTaskEvent;
        }
        ++v4;
        v6 += 4;
      }
      while ( v4 < Human_ptQTaskList->nTask );
    }
  }
  else
  {
    v5 = ComputerObject_eDrawComputerObjectQTaskEvent;
  }
  if ( ((int)ptQTask[1].ptNext & 2) != 0 )
  {
    v9 = 0;
    if ( GameFunctions_ptVehicleQTaskList->nTask > 0 )
    {
      v10 = 8;
      do
      {
        if ( v5 == 512 )
        {
          v5 = QTask_NewQTaskEventFn(0x200u, "DrawComputerObject");
          ComputerObject_eDrawComputerObjectQTaskEvent = v5;
        }
        v11 = *(int *)((char *)&GameFunctions_ptVehicleQTaskList->nTask + v10);
        v12 = (void (__cdecl *)(int, struct DrawComputerObjectContext_s *))QTask_aatQTaskFinalEvent[v5][*(unsigned __int16 *)(v11 + 36)].pfHandler;
        if ( v12 )
        {
          v12(v11, &igi2_frame.tDrawComputerObjectContext);
          v5 = ComputerObject_eDrawComputerObjectQTaskEvent;
        }
        ++v9;
        v10 += 4;
      }
      while ( v9 < GameFunctions_ptVehicleQTaskList->nTask );
    }
  }
  if ( ((int)ptQTask[1].ptNext & 4) != 0 )
  {
    v13 = 0;
    if ( ComputerHilight_ptQTaskList->nTask > 0 )
    {
      v14 = 8;
      do
      {
        if ( v5 == 512 )
        {
          v5 = QTask_NewQTaskEventFn(0x200u, "DrawComputerObject");
          ComputerObject_eDrawComputerObjectQTaskEvent = v5;
        }
        v15 = *(int *)((char *)&ComputerHilight_ptQTaskList->nTask + v14);
        v16 = (void (__cdecl *)(int, struct DrawComputerObjectContext_s *))QTask_aatQTaskFinalEvent[v5][*(unsigned __int16 *)(v15 + 36)].pfHandler;
        if ( v16 )
        {
          v16(v15, &igi2_frame.tDrawComputerObjectContext);
          v5 = ComputerObject_eDrawComputerObjectQTaskEvent;
        }
        ++v13;
        v14 += 4;
      }
      while ( v13 < ComputerHilight_ptQTaskList->nTask );
    }
  }
  if ( Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER )
  {
    ClientFromHumanQTask = NetManager_GetClientFromHumanQTask(HumanPlayer_ptQTask);
    SpawnArea_DrawAllActiveComputerObjects(&igi2_frame.tDrawComputerObjectContext, ClientFromHumanQTask->eTeam);
    v18 = C4Bomb_ptQTask;
    v5 = ComputerObject_eDrawComputerObjectQTaskEvent;
    if ( C4Bomb_ptQTask )
    {
      if ( ComputerObject_eDrawComputerObjectQTaskEvent == 512 )
      {
        v5 = QTask_NewQTaskEventFn(0x200u, "DrawComputerObject");
        v18 = C4Bomb_ptQTask;
        ComputerObject_eDrawComputerObjectQTaskEvent = v5;
      }
      v19 = (void (__cdecl *)(struct QTask_s *, struct DrawComputerObjectContext_s *))QTask_aatQTaskFinalEvent[v5][v18->eQTaskType].pfHandler;
      if ( v19 )
      {
        v19(v18, &igi2_frame.tDrawComputerObjectContext);
        v5 = ComputerObject_eDrawComputerObjectQTaskEvent;
      }
    }
  }
  if ( ((int)ptQTask[1].ptNext & 8) != 0 && ComputerMap_nZoomLevel >= 1 && Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER )
  {
    if ( NetManager_GetClientFromHumanQTask(HumanPlayer_ptQTask)->eTeam == NetMission_eDefendingTeam )
    {
      v20 = SCamera_ptSCameraLensQTaskList;
      v21 = 0;
      v5 = ComputerObject_eDrawComputerObjectQTaskEvent;
      igi2_frame.ptComputerMap = ComputerMap_ptComputerMap;
      if ( SCamera_ptSCameraLensQTaskList->nTask > 0 )
      {
        v22 = 8;
        do
        {
          if ( v5 == 512 )
          {
            v5 = QTask_NewQTaskEventFn(0x200u, "DrawComputerObject");
            v20 = SCamera_ptSCameraLensQTaskList;
            ComputerObject_eDrawComputerObjectQTaskEvent = v5;
          }
          v23 = *(int *)((char *)&v20->nTask + v22);
          v24 = (void (__cdecl *)(int, struct DrawComputerObjectContext_s *))QTask_aatQTaskFinalEvent[v5][*(unsigned __int16 *)(v23 + 36)].pfHandler;
          if ( v24 )
          {
            v24(v23, &igi2_frame.tDrawComputerObjectContext);
            v5 = ComputerObject_eDrawComputerObjectQTaskEvent;
            v20 = SCamera_ptSCameraLensQTaskList;
          }
          ++v21;
          v22 += 4;
        }
        while ( v21 < v20->nTask );
        v1 = ptQTask;
      }
      igi2_frame.iCount = 0;
      if ( v20->nTask > 0 )
      {
        v25 = ComputerObject_eDrawCameraConeQTaskEvent;
        v26 = 8;
        do
        {
          if ( v25 == 512 )
          {
            v27 = QTask_NewQTaskEventFn(0x200u, "DrawCameraCone");
            v20 = SCamera_ptSCameraLensQTaskList;
            v25 = v27;
            v5 = ComputerObject_eDrawComputerObjectQTaskEvent;
            ComputerObject_eDrawCameraConeQTaskEvent = v25;
          }
          v28 = *(int *)((char *)&v20->nTask + v26);
          v29 = (void (__cdecl *)(int, struct DrawComputerObjectContext_s *))QTask_aatQTaskFinalEvent[v25][*(unsigned __int16 *)(v28 + 36)].pfHandler;
          if ( v29 )
          {
            v29(v28, &igi2_frame.tDrawComputerObjectContext);
            v5 = ComputerObject_eDrawComputerObjectQTaskEvent;
            v20 = SCamera_ptSCameraLensQTaskList;
            v25 = ComputerObject_eDrawCameraConeQTaskEvent;
          }
          v26 += 4;
          ++igi2_frame.iCount;
        }
        while ( igi2_frame.iCount < v20->nTask );
        v1 = ptQTask;
      }
      ptSCameraLensQTask = igi2_frame.ptComputerMap->ptSCameraLensQTask;
      if ( ptSCameraLensQTask )
        BYTE1(ptSCameraLensQTask[513].tQTaskChildren.ptTail) = 1;
    }
    else
    {
      v5 = ComputerObject_eDrawComputerObjectQTaskEvent;
    }
  }
  if ( ((int)v1[1].ptNext & 0x10) != 0 )
  {
    v31 = 0;
    if ( GameFunctions_ptNotifyQTaskList->nTask > 0 )
    {
      v32 = 8;
      do
      {
        if ( v5 == 512 )
        {
          v5 = QTask_NewQTaskEventFn(0x200u, "DrawComputerObject");
          ComputerObject_eDrawComputerObjectQTaskEvent = v5;
        }
        v33 = *(int *)((char *)&GameFunctions_ptNotifyQTaskList->nTask + v32);
        v34 = (void (__cdecl *)(int, struct DrawComputerObjectContext_s *))QTask_aatQTaskFinalEvent[v5][*(unsigned __int16 *)(v33 + 36)].pfHandler;
        if ( v34 )
        {
          v34(v33, &igi2_frame.tDrawComputerObjectContext);
          v5 = ComputerObject_eDrawComputerObjectQTaskEvent;
        }
        ++v31;
        v32 += 4;
      }
      while ( v31 < GameFunctions_ptNotifyQTaskList->nTask );
    }
    v35 = 0;
    if ( AIStationaryGunHolder_ptQTaskList->nTask > 0 )
    {
      v36 = 8;
      do
      {
        if ( v5 == 512 )
        {
          v5 = QTask_NewQTaskEventFn(0x200u, "DrawComputerObject");
          ComputerObject_eDrawComputerObjectQTaskEvent = v5;
        }
        v37 = *(int *)((char *)&AIStationaryGunHolder_ptQTaskList->nTask + v36);
        v38 = (void (__cdecl *)(int, struct DrawComputerObjectContext_s *))QTask_aatQTaskFinalEvent[v5][*(unsigned __int16 *)(v37 + 36)].pfHandler;
        if ( v38 )
        {
          v38(v37, &igi2_frame.tDrawComputerObjectContext);
          v5 = ComputerObject_eDrawComputerObjectQTaskEvent;
        }
        ++v35;
        v36 += 4;
      }
      while ( v35 < AIStationaryGunHolder_ptQTaskList->nTask );
    }
  }
}

// source: j/0/computer/computerobject.c:318  [anchor-mhash]
void __cdecl ComputerObject_VehicleDrawComputerObjectHandler(struct QTask_s *ptQTask, void *pxContext)
{
  double v2; // st7
  double v3; // st7
  int *v4; // ecx
  int v5; // ecx
  double v6; // st6

  if ( ComputerMap_nZoomLevel && ComputerMap_nZoomLevel != 3 && ptQTask[2].tQTaskChildren.ptHead )
  {
    *((_DWORD *)pxContext + 3) = ptQTask + 1;
    *((_DWORD *)pxContext + 4) = (char *)ptQTask + 124;
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
    *((_DWORD *)pxContext + 7) = 0;
    *((_DWORD *)pxContext + 8) = 1;
    *((float *)pxContext + 5) = v3 * v6;
    ComputerObject_DrawMarker((struct DrawComputerObjectContext_s *)pxContext);
  }
}

// source: j/0/computer/computerobject.c:355  [anchor-caller]
void __cdecl RigidDynCubeObj_DrawComputerObjectHandler(struct QTask_s *ptQTask, void *pxContext)
{
  double v2; // st7
  double v3; // st7
  int *v4; // ecx
  int v5; // ecx
  double v6; // st6

  *((_DWORD *)pxContext + 3) = ptQTask + 1;
  *((_DWORD *)pxContext + 4) = (char *)ptQTask + 124;
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
  *((float *)pxContext + 5) = v3 * v6;
  ComputerObject_DrawSprite((struct DrawComputerObjectContext_s *)pxContext);
  ComputerObject_DrawMarker((struct DrawComputerObjectContext_s *)pxContext);
  ComputerObject_DrawText((struct DrawComputerObjectContext_s *)pxContext);
}

// source: j/0/computer/computerobject.c:388  [anchor-callee]
void __cdecl ComputerObject_ProjectRotatedPos(
        struct real32x2_t *ptDest,
        struct real32x3_t *ptSource,
        struct DrawComputerObjectContext_s *ptContext,
        enum bool isLimitToInsideScreen)
{
  double vZ; // st7
  double v5; // st6
  double v6; // st7
  double v7; // st6
  double nWidth; // st7
  double vX; // st7
  double nHeight; // st7
  double vY; // st7
  float ptDestc = *(float *)&ptContext; // [esp+4h] [ebp+4h] ARGSLOT
  float ptDesta = *(float *)&ptContext; // [esp+4h] [ebp+4h] ARGSLOT
  float ptDestb = *(float *)&ptContext; // [esp+4h] [ebp+4h] ARGSLOT

  if ( ptSource->vZ <= 1.0 )
    vZ = 1.0;
  else
    vZ = ptSource->vZ;
  v5 = vZ;
  v6 = (double)Display_tActiveMode.nWidth * 0.5;
  v7 = v6 / (v5 * ptContext->vCameraFOV);
  ptDestc = v7;
  ptDest->vX = v7 * ptSource->vX + v6;
  ptDest->vY = 4.0
             * (double)Display_tActiveMode.nHeight
             / ((double)Display_tActiveMode.nWidth
              * 3.0)
             * ptSource->vY
             * ptDestc
             + (double)Display_tActiveMode.nHeight * 0.5;
  if ( isLimitToInsideScreen )
  {
    nWidth = (double)Display_tActiveMode.nWidth;
    ptDesta = nWidth;
    vX = nWidth * 0.15000000596046448;
    if ( vX <= ptDest->vX )
    {
      vX = ptDesta * 0.8500000238418579;
      if ( vX >= ptDest->vX )
        vX = ptDest->vX;
    }
    ptDest->vX = vX;
    nHeight = (double)Display_tActiveMode.nHeight;
    ptDestb = nHeight;
    vY = nHeight * 0.10000000149011612;
    if ( vY <= ptDest->vY )
    {
      vY = ptDestb * 0.800000011920929;
      if ( vY >= ptDest->vY )
        vY = ptDest->vY;
    }
    ptDest->vY = vY;
  }
}

// source: j/0/computer/computerobject.c:420  [anchor-mhash]
void __cdecl ComputerObject_ProjectWorldPos(
        struct real32x2_t *ptDest,
        float *pvZ,
        struct real64x3_t *ptSource,
        struct DrawComputerObjectContext_s *ptContext)
{
  double v4; // st7
  double v5; // st6
  double v6; // st5
  struct real32x9_t *ptCameraOrientation; // eax
  double v8; // st7
  double v9; // st6
  double v10; // st5
  float Real32x3_Rotate_tTemp; // [esp+0h] [ebp-Ch]
  float Real32x3_Rotate_tTemp_4; // [esp+4h] [ebp-8h]

  v4 = ptSource->vX - ptContext->ptCameraPos->vX;
  v5 = ptSource->vY - ptContext->ptCameraPos->vY;
  v6 = ptSource->vZ - ptContext->ptCameraPos->vZ;
  ptCameraOrientation = ptContext->ptCameraOrientation;
  Real32x3_Rotate_tTemp = v6 * ptCameraOrientation->tX.vZ
                        + v5 * ptCameraOrientation->tX.vY
                        + v4 * ptCameraOrientation->tX.vX;
  Real32x3_Rotate_tTemp_4 = v6 * ptCameraOrientation->tY.vZ
                          + v5 * ptCameraOrientation->tY.vY
                          + v4 * ptCameraOrientation->tY.vX;
  v8 = v6 * ptCameraOrientation->tZ.vZ + v5 * ptCameraOrientation->tZ.vY + v4 * ptCameraOrientation->tZ.vX;
  v9 = (double)Display_tActiveMode.nWidth * 0.5;
  v10 = v9 / (v8 * ptContext->vCameraFOV);
  ptDest->vX = Real32x3_Rotate_tTemp * v10 + v9;
  ptDest->vY = 4.0
             * (double)Display_tActiveMode.nHeight
             / ((double)Display_tActiveMode.nWidth
              * 3.0)
             * v10
             * Real32x3_Rotate_tTemp_4
             + (double)Display_tActiveMode.nHeight * 0.5;
  if ( pvZ )
    *pvZ = v8;
}

// source: j/0/computer/computerobject.c:453  [anchor-hash]
void __cdecl ComputerObject_Open()
{
  unsigned __int16 BaseQTaskType; // ax
  unsigned __int16 v1; // si
  __int16 v2; // si
  __int16 v3; // ax

  BaseQTaskType = QTask_GetBaseQTaskType();
  v1 = QTask_NewQTaskType("ComputerObject", 44, BaseQTaskType, 0, 0);
  ComputerObject_eQTaskType = v1;
  QTask_LinkQTaskEventHandlerFn(v1, 0, (void (__cdecl *)(struct QTask_s *, void *))ComputerObject_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 2, (void (__cdecl *)(struct QTask_s *))ComputerObject_DeleteHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, Screen_eDrawQTaskEvent, ComputerObject_DrawHandler);
  v2 = ComputerObject_eDrawComputerObjectQTaskEvent;
  if ( ComputerObject_eDrawComputerObjectQTaskEvent == 512 )
  {
    v2 = QTask_NewQTaskEventFn(0x200u, "DrawComputerObject");
    ComputerObject_eDrawComputerObjectQTaskEvent = v2;
  }
  if ( ComputerObject_eDrawCameraConeQTaskEvent == 512 )
  {
    v3 = QTask_NewQTaskEventFn(0x200u, "DrawCameraCone");
    v2 = ComputerObject_eDrawComputerObjectQTaskEvent;
    ComputerObject_eDrawCameraConeQTaskEvent = v3;
  }
  if ( v2 == 512 )
  {
    v2 = QTask_NewQTaskEventFn(0x200u, "DrawComputerObject");
    ComputerObject_eDrawComputerObjectQTaskEvent = v2;
  }
  QTask_LinkQTaskEventHandlerFn(RigidDynCubeObj_eQTaskType, v2, RigidDynCubeObj_DrawComputerObjectHandler);
  if ( v2 == 512 )
  {
    v2 = QTask_NewQTaskEventFn(0x200u, "DrawComputerObject");
    ComputerObject_eDrawComputerObjectQTaskEvent = v2;
  }
  QTask_LinkQTaskEventHandlerFn(Vehicle_eQTaskType, v2, ComputerObject_VehicleDrawComputerObjectHandler);
  ComputerObject_ptTriangleGameSprite = GameFunctions_RegisterGameSprite("triangle.spr");
  ComputerObject_ptDiamondGameSprite = GameFunctions_RegisterGameSprite("diamond.spr");
  Symbol_Register(
    "MARKER_NONE",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)0xFFFFFFFF,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "MARKER_BOX",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    nullptr,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "MARKER_COLOR_NONE",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)0xFFFFFFFF,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "MARKER_COLOR_RED",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    nullptr,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "MARKER_COLOR_YELLOW",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)1,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "MARKER_COLOR_GREEN",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)2,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "MARKER_COLOR_BLUE",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)4,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
}

// source: j/0/computer/computerobject.c:495  [size]
void __cdecl ComputerObject_Close()
{
  QTask_DeleteQTaskEvent(ComputerObject_eDrawComputerObjectQTaskEvent);
  QTask_DeleteQTaskEvent(ComputerObject_eDrawCameraConeQTaskEvent);
  QTask_DeleteQTaskType(ComputerObject_eQTaskType);
}

// source: j/0/computer/computerobject.c:513  [anchor-hash]
struct QTask_s *__cdecl ComputerObject_New(struct QTask_s *ptParent)
{
  struct QTask_s *result; // eax

  result = QTask_NewFn(ptParent, ComputerObject_eQTaskType, nullptr);
  result[1].ptNext = nullptr;
  return result;
}

// source: j/0/computer/computerobject.c:538  [anchor-hash]
__int16 __cdecl ComputerObject_GetDrawComputerObjectQTaskEvent()
{
  __int16 result; // ax

  result = ComputerObject_eDrawComputerObjectQTaskEvent;
  if ( ComputerObject_eDrawComputerObjectQTaskEvent == 512 )
  {
    result = QTask_NewQTaskEventFn(0x200u, "DrawComputerObject");
    ComputerObject_eDrawComputerObjectQTaskEvent = result;
  }
  return result;
}

// source: j/0/computer/computerobject.c:558  [anchor-strings]
__int16 __cdecl ComputerObject_GetDrawCameraConeQTaskEvent()
{
  __int16 result; // ax

  result = ComputerObject_eDrawCameraConeQTaskEvent;
  if ( ComputerObject_eDrawCameraConeQTaskEvent == 512 )
  {
    result = QTask_NewQTaskEventFn(0x200u, "DrawCameraCone");
    ComputerObject_eDrawCameraConeQTaskEvent = result;
  }
  return result;
}

// source: j/0/computer/computerobject.c:578  [anchor-callee]
struct real64x3_t *__cdecl ComputerObject_SnapToObject(
        struct DrawComputerObjectContext_s *ptDrawComputerObjectContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct real64x3_t tStop; };
    struct { char igi2_o1[24]; struct real64x3_t tStart; };
    struct { char igi2_o2[48]; struct QIntersection_s tIntersection; };
    char igi2_extent[168];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct real64x3_t *ptPos; // eax

  ptPos = ptDrawComputerObjectContext->ptPos;
  qmemcpy(&igi2_frame.tStart, ptPos, sizeof(igi2_frame.tStart));
  qmemcpy(&igi2_frame.tStop, ptPos, sizeof(igi2_frame.tStop));
  igi2_frame.tStart.vZ = igi2_frame.tStart.vZ + 2048000.0;
  igi2_frame.tStop.vZ = igi2_frame.tStop.vZ - 409600.0;
  World_TraceLines(Game_ptGame->ptWorld, &igi2_frame.tIntersection, &igi2_frame.tStart, &igi2_frame.tStop, 1, 512, nullptr, 0xFFFFFFFF);
  return &igi2_frame.tIntersection.tPos;
}

// source: j/0/computer/computerobject.c:622  [anchor-caller]
void __cdecl ComputerObject_DrawSprite(struct DrawComputerObjectContext_s *ptDrawComputerObjectContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { float vY; };
    struct { char igi2_o1[4]; float vR; };
    struct { char igi2_o2[8]; float vG; };
    struct { char igi2_o3[32]; int nDepth; };
    struct { char igi2_o4[36]; struct real32x2_t tPos; };
    struct { char igi2_o5[44]; float v14; };
    struct { char igi2_o6[48]; struct real32x3_t tRelativePos; };
    char igi2_extent[64];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QSprite_s *ptQSprite; // edi
  double vZ; // st7
  struct real32x9_t *ptCameraOrientation; // eax
  double v4; // st7
  double v5; // st7
  double vX; // st6
  double v7; // st6
  struct QAnimframe_s *atQAnimframe; // eax

  ptQSprite = ptDrawComputerObjectContext->ptQSprite;
  if ( ptQSprite )
  {
    igi2_frame.tRelativePos.vX = ComputerObject_SnapToObject(ptDrawComputerObjectContext)->vX
                    - ptDrawComputerObjectContext->ptCameraPos->vX;
    igi2_frame.tRelativePos.vY = ComputerObject_SnapToObject(ptDrawComputerObjectContext)->vY
                    - ptDrawComputerObjectContext->ptCameraPos->vY;
    vZ = ComputerObject_SnapToObject(ptDrawComputerObjectContext)->vZ;
    ptCameraOrientation = ptDrawComputerObjectContext->ptCameraOrientation;
    v4 = vZ - ptDrawComputerObjectContext->ptCameraPos->vZ;
    igi2_frame.tPos.vX = v4 * ptCameraOrientation->tZ.vX
            + igi2_frame.tRelativePos.vY * ptCameraOrientation->tY.vX
            + igi2_frame.tRelativePos.vX * ptCameraOrientation->tX.vX;
    igi2_frame.tPos.vY = v4 * ptCameraOrientation->tZ.vY
            + igi2_frame.tRelativePos.vY * ptCameraOrientation->tY.vY
            + igi2_frame.tRelativePos.vX * ptCameraOrientation->tX.vY;
    v5 = v4 * ptCameraOrientation->tZ.vZ + igi2_frame.tRelativePos.vY * ptCameraOrientation->tY.vZ;
    vX = igi2_frame.tRelativePos.vX;
    igi2_frame.tRelativePos.vX = igi2_frame.tPos.vX;
    v7 = vX * ptCameraOrientation->tX.vZ;
    igi2_frame.tRelativePos.vY = igi2_frame.tPos.vY;
    igi2_frame.v14 = v5 + v7;
    igi2_frame.tRelativePos.vZ = igi2_frame.v14;
    ComputerObject_ProjectRotatedPos(&igi2_frame.tPos, &igi2_frame.tRelativePos, ptDrawComputerObjectContext, true);
    atQAnimframe = ptQSprite->atQAnimframe;
    igi2_frame.nDepth = atQAnimframe[ptQSprite->nQAnimframes].nHeight;
    igi2_frame.tPos.vX = igi2_frame.tPos.vX - (double)atQAnimframe[ptQSprite->nQAnimframes].nWidth * 0.5;
    igi2_frame.tPos.vY = igi2_frame.tPos.vY - (double)igi2_frame.nDepth * 0.5;
    igi2_frame.vG = ComputerObject_atMarkerColor[5].vZ * 0.5;
    igi2_frame.vR = ComputerObject_atMarkerColor[5].vY * 0.5;
    igi2_frame.vY = ComputerObject_atMarkerColor[5].vX * 0.5;
    QSprite_RegisterAZ(ptQSprite, igi2_frame.tPos.vX, igi2_frame.tPos.vY, igi2_frame.vY, igi2_frame.vR, igi2_frame.vG, 1.0, 532.47998046875, 0, 0x400C0000u, -1);
  }
}

// source: j/0/computer/computerobject.c:683  [anchor-callee]
struct DrawComputerObjectContext_s *__cdecl ComputerObject_DrawMarker(
        struct DrawComputerObjectContext_s *ptDrawComputerObjectContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { float vY4; };
    struct { char igi2_o1[4]; float vR1; };
    struct { char igi2_o2[8]; float vG1; };
    struct { char igi2_o3[12]; float vAlpha; };
    struct { char igi2_o4[12]; float vAlphaa; };
    struct { char igi2_o5[44]; float vRadius; };
    struct { char igi2_o6[44]; float vRadiusa; };
    struct { char igi2_o7[48]; float vGamma; };
    struct { char igi2_o8[52]; float vBeta; };
    struct { char igi2_o9[56]; struct real32x2_t tPos; };
    struct { char igi2_o10[64]; float v37; };
    struct { char igi2_o11[68]; struct real32x3_t tRelativePos; };
    struct { char igi2_o12[80]; struct real32x3_t Real32x3_RotateInverse_tTemp; };
    struct { char igi2_o13[96]; struct real32x2_t atPos[4]; };
    char igi2_extent[132];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct DrawComputerObjectContext_s *v1; // esi
  enum ComputerObjectMarker_e eComputerObjectMarker; // edx
  struct real64x3_t *ptPos; // eax
  double v4; // st7
  int v5; // ebx
  double v6; // st6
  double vZ; // st5
  float *p_vX; // eax
  double v9; // st5
  double v10; // rt0
  double v11; // st5
  double v12; // st6
  float *v13; // edi
  double v14; // st7
  struct real32x9_t *ptOrientation; // ecx
  enum ComputerObjectMarker_e v16; // esi
  double v17; // st7
  double v18; // st6
  long double v19; // st5
  long double v20; // st5
  long double v21; // st5
  long double v22; // st6
  long double v23; // st5
  double v24; // st4
  double v25; // st3
  struct GameSprite_t *v26; // ecx

  v1 = ptDrawComputerObjectContext;
  eComputerObjectMarker = ptDrawComputerObjectContext->eComputerObjectMarker;
  if ( eComputerObjectMarker != COMPUTEROBJECTMARKER_NONE )
  {
    igi2_frame.vRadius = ptDrawComputerObjectContext->vRadius;
    if ( igi2_frame.vRadius < 3072.0 )
      igi2_frame.vRadius = 3072.0;
    ptPos = ptDrawComputerObjectContext->ptPos;
    v4 = ptPos->vX - v1->ptCameraPos->vX;
    v5 = 8 * eComputerObjectMarker + 7044796;
    v6 = ptPos->vY - v1->ptCameraPos->vY;
    vZ = ptPos->vZ;
    p_vX = &v1->ptCameraOrientation->tX.vX;
    v9 = vZ - v1->ptCameraPos->vZ;
    igi2_frame.Real32x3_RotateInverse_tTemp.vX = v9 * p_vX[6] + v6 * p_vX[3] + v4 * *p_vX;
    igi2_frame.Real32x3_RotateInverse_tTemp.vY = v9 * p_vX[7] + v6 * p_vX[4] + v4 * p_vX[1];
    igi2_frame.tRelativePos.vY = igi2_frame.Real32x3_RotateInverse_tTemp.vY;
    v10 = v9 * p_vX[8];
    v11 = v6 * p_vX[5];
    v12 = v4 * p_vX[2];
    igi2_frame.tRelativePos.vX = igi2_frame.Real32x3_RotateInverse_tTemp.vX;
    igi2_frame.Real32x3_RotateInverse_tTemp.vZ = v10 + v11 + v12;
    igi2_frame.tRelativePos.vZ = igi2_frame.Real32x3_RotateInverse_tTemp.vZ;
    v13 = (float *)(12 * v1->eComputerObjectMarkerColor + 7044824);
    ComputerObject_ProjectRotatedPos((struct real32x2_t *)&igi2_frame.tPos.vY, &igi2_frame.tRelativePos, v1, false);
    if ( igi2_frame.Real32x3_RotateInverse_tTemp.vZ > 1.0 )
      v14 = igi2_frame.tRelativePos.vZ;
    else
      v14 = 1.0;
    ptOrientation = v1->ptOrientation;
    *(double *)&igi2_frame.Real32x3_RotateInverse_tTemp.vX = 1.0 / v14;
    igi2_frame.tRelativePos.vX = TransContext_tActiveTransContext.vScreenFOVX
                    * igi2_frame.vRadius
                    * *(double *)&igi2_frame.Real32x3_RotateInverse_tTemp.vX;
    igi2_frame.tRelativePos.vY = TransContext_tActiveTransContext.vScreenFOVY
                    * igi2_frame.vRadius
                    * *(double *)&igi2_frame.Real32x3_RotateInverse_tTemp.vX;
    Real32x9_GetAngles(ptOrientation, &igi2_frame.tPos.vX, &igi2_frame.vBeta, &igi2_frame.vGamma);
    v16 = v1->eComputerObjectMarker;
    if ( v16 == COMPUTEROBJECTMARKER_TRIANGLE
      || v16 == COMPUTEROBJECTMARKER_LARGETRIANGLE
      || v16 == COMPUTEROBJECTMARKER_DIAMOND )
    {
      igi2_frame.tRelativePos.vX = TransContext_tActiveTransContext.vScreenFOVX
                      * igi2_frame.vRadius
                      * *(double *)&igi2_frame.Real32x3_RotateInverse_tTemp.vX;
      igi2_frame.tRelativePos.vY = TransContext_tActiveTransContext.vScreenFOVY
                      * igi2_frame.vRadius
                      * *(double *)&igi2_frame.Real32x3_RotateInverse_tTemp.vX;
      v17 = (igi2_frame.tRelativePos.vX - 128.0) * 0.8999999761581421 + 128.0;
      v18 = (igi2_frame.tRelativePos.vY - 128.0) * 0.8999999761581421 + 128.0;
      if ( v16 == COMPUTEROBJECTMARKER_LARGETRIANGLE )
      {
        v17 = v17 * 1.5;
        v18 = v18 * 1.5;
      }
      v19 = sin(igi2_frame.vGamma);
      igi2_frame.vBeta = v19;
      v20 = v19 * v18;
      igi2_frame.vRadiusa = v20;
      igi2_frame.tPos.vY = igi2_frame.tPos.vY - v20 * 0.3333333432674408;
      v21 = cos(igi2_frame.vGamma);
      igi2_frame.vGamma = v21 * v18;
      igi2_frame.v37 = igi2_frame.v37 - v21 * v18 * 0.3333333432674408;
      v22 = v21 * v17;
      v23 = igi2_frame.tPos.vY - v22;
      igi2_frame.atPos[0].vX = v23 - igi2_frame.vRadiusa;
      v24 = igi2_frame.vBeta * v17;
      igi2_frame.atPos[0].vY = igi2_frame.v37 + v24 - igi2_frame.vGamma;
      igi2_frame.atPos[1].vX = v22 + igi2_frame.tPos.vY - igi2_frame.vRadiusa;
      v25 = igi2_frame.v37 - v24;
      igi2_frame.vBeta = v25;
      igi2_frame.atPos[1].vY = v25 - igi2_frame.vGamma;
      igi2_frame.atPos[2].vX = v23 + igi2_frame.vRadiusa;
      igi2_frame.atPos[2].vY = v24 + igi2_frame.vGamma + igi2_frame.v37;
      igi2_frame.atPos[3].vX = v22 + igi2_frame.vRadiusa + igi2_frame.tPos.vY;
      igi2_frame.atPos[3].vY = igi2_frame.vBeta + igi2_frame.vGamma;
      igi2_frame.vAlpha = sin((double)Flow_ptFlow->nTicks * 0.10000000149011612) * 0.20000000298023224 + 0.5;
      v26 = ComputerObject_ptDiamondGameSprite;
      if ( v16 != COMPUTEROBJECTMARKER_DIAMOND )
        v26 = ComputerObject_ptTriangleGameSprite;
      igi2_frame.vY4 = *v13 * 0.5;
      igi2_frame.vR1 = v13[1] * 0.5;
      igi2_frame.vG1 = v13[2] * 0.5;
      QSprite_Register4AZ(
        &v26->tQSprite,
        igi2_frame.atPos[0].vX,
        igi2_frame.atPos[0].vY,
        igi2_frame.atPos[1].vX,
        igi2_frame.atPos[1].vY,
        igi2_frame.atPos[2].vX,
        igi2_frame.atPos[2].vY,
        igi2_frame.atPos[3].vX,
        igi2_frame.atPos[3].vY,
        igi2_frame.vY4,
        igi2_frame.vR1,
        igi2_frame.vG1,
        igi2_frame.vAlpha,
        532.47998046875,
        0,
        0x400C0008u,
        -1);
    }
    else
    {
      igi2_frame.vAlphaa = -igi2_frame.vGamma;
      return (struct DrawComputerObjectContext_s *)QSprite_RegisterLineMesh(
                                                     *(struct real32x2_t **)v5,
                                                     *(_DWORD *)(v5 + 4),
                                                     igi2_frame.tPos.vY,
                                                     igi2_frame.v37,
                                                     532.47998046875,
                                                     *v13,
                                                     v13[1],
                                                     v13[2],
                                                     0.75,
                                                     1.0,
                                                     igi2_frame.vAlphaa,
                                                     igi2_frame.tRelativePos.vX,
                                                     igi2_frame.tRelativePos.vY,
                                                     0x400C0000u,
                                                     -1);
    }
  }
  return ptDrawComputerObjectContext;
}

// source: j/0/computer/computerobject.c:844  [anchor-strings]
void __cdecl ComputerObject_DrawText(struct DrawComputerObjectContext_s *ptDrawComputerObjectContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct real32x3_t tRelativePos; };
    struct { char igi2_o1[16]; struct real32x3_t Real32x3_RotateInverse_tTemp; };
    char igi2_extent[36];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  double vZ; // st7
  struct real32x9_t *ptCameraOrientation; // eax
  double v4; // st7
  double v5; // st7
  double vX; // st6
  double v7; // st6
  char *zTitle; // esi
  char *LocalizedStringForLanguage; // esi
  struct QTask_s *ptHead; // eax
  struct QTask_s *v11; // eax
  char *zInfo; // esi
  struct QTask_s *v13; // eax
  struct QSprite_s *Font; // eax

  igi2_frame.tRelativePos.vX = ComputerObject_SnapToObject(ptDrawComputerObjectContext)->vX
                  - ptDrawComputerObjectContext->ptCameraPos->vX;
  igi2_frame.tRelativePos.vY = ComputerObject_SnapToObject(ptDrawComputerObjectContext)->vY
                  - ptDrawComputerObjectContext->ptCameraPos->vY;
  vZ = ComputerObject_SnapToObject(ptDrawComputerObjectContext)->vZ;
  ptCameraOrientation = ptDrawComputerObjectContext->ptCameraOrientation;
  v4 = vZ - ptDrawComputerObjectContext->ptCameraPos->vZ;
  igi2_frame.Real32x3_RotateInverse_tTemp.vX = v4 * ptCameraOrientation->tZ.vX
                                  + igi2_frame.tRelativePos.vY * ptCameraOrientation->tY.vX
                                  + igi2_frame.tRelativePos.vX * ptCameraOrientation->tX.vX;
  igi2_frame.Real32x3_RotateInverse_tTemp.vY = v4 * ptCameraOrientation->tZ.vY
                                  + igi2_frame.tRelativePos.vY * ptCameraOrientation->tY.vY
                                  + igi2_frame.tRelativePos.vX * ptCameraOrientation->tX.vY;
  v5 = v4 * ptCameraOrientation->tZ.vZ + igi2_frame.tRelativePos.vY * ptCameraOrientation->tY.vZ;
  vX = igi2_frame.tRelativePos.vX;
  igi2_frame.tRelativePos.vX = igi2_frame.Real32x3_RotateInverse_tTemp.vX;
  v7 = vX * ptCameraOrientation->tX.vZ;
  igi2_frame.tRelativePos.vY = igi2_frame.Real32x3_RotateInverse_tTemp.vY;
  igi2_frame.Real32x3_RotateInverse_tTemp.vZ = v5 + v7;
  igi2_frame.tRelativePos.vZ = igi2_frame.Real32x3_RotateInverse_tTemp.vZ;
  ComputerObject_ProjectRotatedPos(
    (struct real32x2_t *)&igi2_frame.Real32x3_RotateInverse_tTemp,
    &igi2_frame.tRelativePos,
    ptDrawComputerObjectContext,
    true);
  if ( ComputerMap_nZoomLevel == 1 )
  {
    zTitle = ptDrawComputerObjectContext->zTitle;
    LODWORD(igi2_frame.tRelativePos.vX) = strlen(zTitle);
    if ( !LODWORD(igi2_frame.tRelativePos.vX) )
      return;
    LocalizedStringForLanguage = Config_GetLocalizedStringForLanguage(
                                   zTitle,
                                   Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eLanguage,
                                   true);
    ptHead = Game_ptGame->ptGameScreenQTask[1].tQTaskChildren.ptHead;
    if ( ptHead )
      v11 = ptHead->tQTaskChildren.ptHead;
    else
      v11 = nullptr;
    goto LABEL_11;
  }
  if ( ComputerMap_nZoomLevel > 1 )
  {
    zInfo = ptDrawComputerObjectContext->zInfo;
    LODWORD(igi2_frame.tRelativePos.vX) = strlen(zInfo);
    if ( LODWORD(igi2_frame.tRelativePos.vX) )
    {
      LocalizedStringForLanguage = Config_GetLocalizedStringForLanguage(
                                     zInfo,
                                     Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eLanguage,
                                     true);
      v13 = Game_ptGame->ptGameScreenQTask[1].tQTaskChildren.ptHead;
      if ( v13 )
        v11 = v13->tQTaskChildren.ptHead;
      else
        v11 = nullptr;
LABEL_11:
      Font = MenuManager_GetFont(v11, (char *)&g_zFontName_0.tQTaskChildren.ptMiddle);
      ComputerObjectives_Print(
        (__int64)igi2_frame.Real32x3_RotateInverse_tTemp.vX + 10,
        (__int64)igi2_frame.Real32x3_RotateInverse_tTemp.vY,
        532.47998046875,
        128,
        128,
        LocalizedStringForLanguage,
        Font,
        COMPUTERMENU_COLOR_DARK_RED);
    }
  }
}

// source: j/0/computer/computerobject.c:924  [size]
int __cdecl ComputerObject_GetDrawFlags(struct QTask_s *ptQTask)
{
  return (int)ptQTask[1].ptNext;
}

// source: j/0/computer/computerobject.c:942  [size]
int __cdecl ComputerObject_SetDrawFlags(struct QTask_s *ptQTask, int bDrawFlags)
{
  ptQTask[1].ptNext = (struct QTask_s *)bDrawFlags;
  return bDrawFlags;
}
