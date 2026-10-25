/* j/0/objects/placeexplosivetba.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/objects/placeexplosivetba.c:60  [anchor-mhash]
void __cdecl PlaceExplosiveTBA_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ((void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[0][GenericTBA_eQTaskType].pfHandler)(
    ptQTask,
    pxContext);
  ptQTask[20].ptParent = (struct QTask_s *)1061158912;
  *(_DWORD *)&ptQTask[20].eQTaskType = -1;
}

// source: j/0/objects/placeexplosivetba.c:79  [anchor-mhash]
void __cdecl PlaceExplosiveTBA_EvaluateActivateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct real64x3_t v5; };
    struct { char igi2_o1[36]; float vAlpha; };
    struct { char igi2_o2[40]; struct real64x3_t tDelta; };
    struct { char igi2_o3[64]; struct real64x3_t tPos; };
    char igi2_extent[88];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  double v2; // st7
  double v3; // st7
  float v4; // eax

  if ( LOBYTE(ptQTask[20].tQTaskRefList.ptHead) )
  {
    GameFunctions_GetMagicVertex(&igi2_frame.tPos, ptQTask, 1);
    igi2_frame.tDelta.vX = igi2_frame.tPos.vX - *((double *)pxContext + 1);
    igi2_frame.tDelta.vY = igi2_frame.tPos.vY - *((double *)pxContext + 2);
    igi2_frame.tDelta.vZ = igi2_frame.tPos.vZ - *((double *)pxContext + 3);
    if ( *(float *)&ptQTask[20].ptParent * 4096.0 > sqrt(
                                                      igi2_frame.tDelta.vY * igi2_frame.tDelta.vY
                                                    + igi2_frame.tDelta.vZ * igi2_frame.tDelta.vZ
                                                    + igi2_frame.tDelta.vX * igi2_frame.tDelta.vX)
      && !*((_DWORD *)pxContext + 32) )
    {
      igi2_frame.tPos.vX = *((float *)pxContext + 14) * igi2_frame.tDelta.vZ
              + *((float *)pxContext + 11) * igi2_frame.tDelta.vY
              + *((float *)pxContext + 8) * igi2_frame.tDelta.vX;
      igi2_frame.tPos.vY = *((float *)pxContext + 15) * igi2_frame.tDelta.vZ
              + *((float *)pxContext + 12) * igi2_frame.tDelta.vY
              + *((float *)pxContext + 9) * igi2_frame.tDelta.vX;
      igi2_frame.tPos.vZ = *((float *)pxContext + 16) * igi2_frame.tDelta.vZ
              + *((float *)pxContext + 13) * igi2_frame.tDelta.vY
              + *((float *)pxContext + 10) * igi2_frame.tDelta.vX;
      if ( igi2_frame.tPos.vY > 0.0 )
      {
        qmemcpy(&igi2_frame.v5, &igi2_frame.tPos, sizeof(igi2_frame.v5));
        v2 = GameFunctions_CalcAlpha(igi2_frame.v5);
        if ( v2 < 0.0 )
          v2 = -v2;
        igi2_frame.vAlpha = v2;
        qmemcpy(&igi2_frame.v5, &igi2_frame.tPos, sizeof(igi2_frame.v5));
        v3 = GameFunctions_CalcGamma(igi2_frame.v5);
        if ( v3 < 0.0 )
          v3 = -v3;
        if ( igi2_frame.vAlpha < (double)*((float *)pxContext + 28) && v3 < *((float *)pxContext + 29) )
        {
          v4 = igi2_frame.vAlpha;
          *((float *)pxContext + 29) = v3;
          *((float *)pxContext + 28) = v4;
          *((_DWORD *)pxContext + 32) = ptQTask;
        }
      }
    }
  }
}

// source: j/0/objects/placeexplosivetba.c:167  [size]
void __cdecl PlaceExplosiveTBA_GetActivateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = 12;
}

// source: j/0/objects/placeexplosivetba.c:184  [size]
void __cdecl PlaceExplosiveTBA_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = PlaceExplosiveTBA_ptParameterList;
}

// source: j/0/objects/placeexplosivetba.c:202  [size]
int __cdecl PlaceExplosiveTBA_GetQTaskIDToPlace(struct QTask_s *ptQTask)
{
  return *(_DWORD *)&ptQTask[20].eQTaskType;
}

// source: j/0/objects/placeexplosivetba.c:221  [anchor-mhash]
void __cdecl PlaceExplosiveTBA_Open()
{
  unsigned __int16 v0; // si

  v0 = QTask_NewQTaskType("PlaceExplosiveTBA", 840, GenericTBA_eQTaskType, 0, 0);
  PlaceExplosiveTBA_eQTaskType = v0;
  QTask_LinkQTaskEventHandlerFn(
    v0,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveHandler);
  QTask_LinkQTaskEventHandlerFn(v0, 0, PlaceExplosiveTBA_CreateHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))PlaceExplosiveTBA_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    GameFunctions_eEvaluateActivateQTaskEvent,
    PlaceExplosiveTBA_EvaluateActivateHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    GameFunctions_eGetActivateQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))PlaceExplosiveTBA_GetActivateHandler);
  PlaceExplosiveTBA_ptParameterList = ParameterList_Derive(GenericTBA_ptParameterList, 2);
  ParameterList_AddParameter(
    PlaceExplosiveTBA_ptParameterList,
    0x340u,
    Level_eParameterTypeReal32,
    "Activate radius (meters)",
    7u,
    nullptr);
  ParameterList_AddParameter(
    PlaceExplosiveTBA_ptParameterList,
    0x344u,
    Level_eParameterTypeInt32,
    "Task ID to place",
    7u,
    nullptr);
}

// source: j/0/objects/placeexplosivetba.c:252  [size]
void __cdecl PlaceExplosiveTBA_Close()
{
  int v0; // esi

  if ( PlaceExplosiveTBA_ptParameterList )
  {
    v0 = *(_DWORD *)((unsigned int)&PlaceExplosiveTBA_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
  QTask_DeleteQTaskType(PlaceExplosiveTBA_eQTaskType);
}
