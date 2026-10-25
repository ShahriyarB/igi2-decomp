/* j/0/weapons/zoom.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/weapons/zoom.c:52  [size]
void __cdecl Zoom_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ptQTask[1].tQTaskChildren.ptHead = (struct QTask_s *)1084227584;
  ptQTask[1].tQTaskChildren.ptMiddle = (struct QTask_s *)1119092736;
  ptQTask[1].tQTaskChildren.ptTail = (struct QTask_s *)0x40000000;
  LOBYTE(ptQTask[1].ptParent) = 0;
  BYTE1(ptQTask[1].ptParent) = 0;
  ptQTask[2].tQTaskRefList.ptTail = (struct QReference_s *)512;
  ptQTask[2].ptParent = (struct QTask_s *)512;
  *(_DWORD *)&ptQTask[2].eQTaskType = 0;
  ptQTask[1].tQTaskRefList.ptHead = nullptr;
  ptQTask[1].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[1].tQTaskRefList.ptTail = nullptr;
}

// source: j/0/weapons/zoom.c:78  [size]
void __cdecl Zoom_DeleteHandler(struct QTask_s *ptQTask)
{
  WeaponType_DeleteParameters((struct QReference_s **)&ptQTask[2].eQTaskType);
}

// source: j/0/weapons/zoom.c:94  [size]
void __cdecl Zoom_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = Zoom_ptParameterList;
}

// source: j/0/weapons/zoom.c:112  [anchor-mhash]
void __cdecl Zoom_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(float *)&ptQTask[1].ptNext = tan(*(float *)&ptQTask[1].tQTaskChildren.ptHead * 0.5 * 0.01745329238474369);
  *(float *)&ptQTask[1].ptPrev = tan(*(float *)&ptQTask[1].tQTaskChildren.ptMiddle * 0.5 * 0.01745329238474369);
}

// source: j/0/weapons/zoom.c:137  [size]
void __cdecl Zoom_UpdaterInternalDataAfterLoadHandler(struct QTask_s *ptQTask)
{
  *(_DWORD *)&ptQTask[2].eQTaskType = WeaponType_CreateParameters(
                                        (unsigned __int16)ptQTask[2].tQTaskRefList.ptTail,
                                        ptQTask);
  ptQTask[2].ptParent = (struct QTask_s *)ptQTask[2].tQTaskRefList.ptTail;
}

// source: j/0/weapons/zoom.c:154  [size]
void __cdecl Zoom_CreateWeaponTypeParametersHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *v2; // esi

  v2 = QTask_NewFn(*((struct QTask_s **)pxContext + 1), Zoom_eQTaskType, nullptr);
  *((_DWORD *)pxContext + 2) = v2;
  *(_DWORD *)&v2[2].eQTaskType = WeaponType_CreateParameters((unsigned __int16)v2[2].tQTaskRefList.ptTail, v2);
}

// source: j/0/weapons/zoom.c:178  [size]
void __cdecl Zoom_UpdateTagItemsHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ;
}

// source: j/0/weapons/zoom.c:198  [size]
void __cdecl Zoom_DeleteWeaponTypeParametersHandler(struct QTask_s *ptQTask, void *pxContext)
{
  WeaponType_DeleteParameters((struct QReference_s **)(*(_DWORD *)pxContext + 116));
  ((void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[WeaponType_eDeleteParametersQTaskEvent][FireType_eQTaskType].pfHandler)(
    ptQTask,
    pxContext);
}

// source: j/0/weapons/zoom.c:218  [anchor-mhash]
void __cdecl Zoom_WeaponFireHandler(struct QTask_s *ptQTask, void *pxContext)
{
  enum WeaponOverlayStatus_e v2; // esi
  int v3; // edx
  int v4; // ebx
  struct QTask_s *v5; // ecx
  int v6; // esi
  bool v7; // zf
  int v8; // eax
  void *v9; // eax
  double v10; // st7
  double v11; // st7
  enum WeaponOverlayStatus_e v12; // [esp-4h] [ebp-10h]

  v3 = *((_DWORD *)pxContext + 1);
  v4 = *((_DWORD *)pxContext + 25);
  if ( v3 )
  {
    HIWORD(v5) = unk_79EE2F6;
    if ( QTask_IsQTaskTypeDerived(*(_WORD *)(v3 + 36), Human_eQTaskType) )
    {
      LOWORD(v5) = *(_WORD *)(v4 + 108);
      v12 = v2;
      v6 = *(_DWORD *)(v3 + 1336);
      if ( *(_DWORD *)(v6 + 664) )
      {
        *(_DWORD *)(v6 + 664) = 0;
        *(float *)(v6 + 648) = tan(0.7853981852531433);
        *(float *)(v6 + 660) = tan(0.5235987901687622);
        *((_DWORD *)pxContext + 29) = 0;
        if ( QTask_IsQTaskTypeValid((unsigned __int16)v5) )
        {
          if ( *(_DWORD *)(*(_DWORD *)pxContext + 164) )
          {
            QTask_Delete(*(struct QTask_s **)(*(_DWORD *)pxContext + 164));
            v5 = *(struct QTask_s **)pxContext;
            *(_DWORD *)(*(_DWORD *)pxContext + 164) = 0;
          }
        }
        Weapon_SetOverlayStatus(v5, v12, 0, *(_DWORD *)pxContext);
      }
      else
      {
        if ( QTask_IsQTaskTypeValid((unsigned __int16)v5) )
        {
          v7 = Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER;
          *(_DWORD *)(v6 + 664) = 1;
          if ( !v7
            || *(struct QTask_s **)(*(_DWORD *)(v3 + 1324) + 40) == Flow_ptFlow->ptNetManagerQTask[6].tQTaskChildren.ptMiddle )
          {
            v8 = *(_DWORD *)(v4 + 116);
            if ( v8 )
              v9 = *(void **)(v8 + 8);
            else
              v9 = nullptr;
            *(_DWORD *)(*(_DWORD *)pxContext + 164) = QTask_NewFn(
                                                        *(struct QTask_s **)pxContext,
                                                        (unsigned __int16)v5,
                                                        v9);
          }
          *(_DWORD *)(*(_DWORD *)pxContext + 160) = 2;
        }
        else
        {
          *(_DWORD *)(*(_DWORD *)pxContext + 160) = 1;
        }
        *((_DWORD *)pxContext + 29) = 0;
        v10 = *(float *)(v4 + 44);
        *(float *)(v6 + 652) = *(float *)(v4 + 44);
        v11 = (*(float *)(v6 + 648) - v10) * 0.3333333432674408;
        if ( v11 < 0.0 )
          v11 = -v11;
        *(float *)(v6 + 656) = v11;
      }
    }
  }
}

void __cdecl sub_530D00(struct QTask_s *a1, _DWORD *a2)
{
  int v2; // edx
  int v3; // eax

  v2 = a2[1];
  if ( v2 )
  {
    if ( QTask_IsQTaskTypeDerived(*(_WORD *)(v2 + 36), Human_eQTaskType) )
    {
      v3 = *(_DWORD *)(v2 + 1336);
      *(_DWORD *)(v3 + 664) = 0;
      *(float *)(v3 + 648) = tan(0.7853981852531433);
      *(float *)(v3 + 660) = tan(0.5235987901687622);
    }
  }
}

// source: j/0/weapons/zoom.c:349  [anchor-mhash]
void __cdecl Zoom_WeaponZoomHandler(struct QTask_s *ptQTask, void *pxContext)
{
  int v2; // edx
  int v3; // esi
  int v4; // esi
  double v5; // st7
  double v6; // st7
  double v7; // st7
  struct QTask_s *v8; // eax

  v2 = *((_DWORD *)pxContext + 2);
  if ( *(_DWORD *)(*(_DWORD *)pxContext + 160) )
  {
    v3 = *((_DWORD *)pxContext + 1);
    if ( v3 )
    {
      if ( QTask_IsQTaskTypeDerived(*(_WORD *)(v3 + 36), Human_eQTaskType) )
      {
        v4 = *(_DWORD *)(v3 + 1336);
        v5 = *(float *)(v4 + 652);
        v6 = *((_DWORD *)pxContext + 3) ? v5 / *(float *)(v2 + 56) : v5 * *(float *)(v2 + 56);
        if ( v6 >= *(float *)(v2 + 40) && v6 <= *(float *)(v2 + 44) )
        {
          *(float *)(v4 + 652) = v6;
          v7 = (*(float *)(v4 + 648) - v6) * 0.3333333432674408;
          if ( v7 < 0.0 )
            v7 = -v7;
          *(float *)(v4 + 656) = v7;
          if ( *(_BYTE *)(v2 + 73) )
          {
            v8 = SoundSys_NewSoundFn((struct QTask_s *)v4, (char *)(v2 + 73));
            if ( v8 )
              SoundSys_SetSoundPosition(v8, (struct real64x3_t *)(v4 + 408));
          }
        }
      }
    }
  }
}

// source: j/0/weapons/zoom.c:464  [size]
unsigned __int16 __cdecl Zoom_GetQTaskType()
{
  return Zoom_eQTaskType;
}

// source: j/0/weapons/zoom.c:477  [anchor-hash]
void __cdecl Zoom_Open()
{
  unsigned __int16 v0; // si
  struct ParameterList_s *v1; // eax
  int v2; // [esp-1Ch] [ebp-28h]

  v0 = QTask_NewQTaskType("Zoom", 120, FireType_eQTaskType, 0, 0);
  Zoom_eQTaskType = v0;
  QTask_LinkQTaskEventHandlerFn(
    v0,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveHandler);
  QTask_LinkQTaskEventHandlerFn(v0, 0, Zoom_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 2, Zoom_DeleteHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(
    v0,
    Level_eUpdateInternalDataAfterLoadEvent,
    Zoom_UpdaterInternalDataAfterLoadHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Zoom_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    ParameterList_eUpdateInternalDataQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Zoom_UpdateInternalDataHandler);
  QTask_LinkQTaskEventHandlerFn(v0, WeaponType_eCreateParametersQTaskEvent, Zoom_CreateWeaponTypeParametersHandler);
  QTask_LinkQTaskEventHandlerFn(v0, WeaponType_eDeleteParametersQTaskEvent, Zoom_DeleteWeaponTypeParametersHandler);
  QTask_LinkQTaskEventHandlerFn(v0, Weapon_eFireQTaskEvent, Zoom_WeaponFireHandler);
  QTask_LinkQTaskEventHandlerFn(v0, Weapon_eReloadQTaskEvent, (void (__cdecl *)(struct QTask_s *, void *))sub_530D00);
  QTask_LinkQTaskEventHandlerFn(v0, Weapon_eZoomQTaskEvent, Zoom_WeaponZoomHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    TagItem_eUpdateTagItemQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Zoom_UpdateTagItemsHandler);
  v1 = (struct ParameterList_s *)Mem_AllocFn(212, 4);
  v2 = Level_eParameterTypeDegrees;
  v1->nParameters = 0;
  v1->nMaxParameters = 10;
  v1->ptParameterListItem = (struct ParameterListItem_s *)&v1[1];
  Zoom_ptParameterList = v1;
  ParameterList_AddParameterMinMax(v1, 0x30u, v2, "Minimum FOV", 7u, 1.0, 90.0);
  ParameterList_AddParameterMinMax(
    Zoom_ptParameterList,
    0x34u,
    Level_eParameterTypeDegrees,
    "Maximum FOV",
    7u,
    1.0,
    90.0);
  ParameterList_AddParameterMinMax(
    Zoom_ptParameterList,
    0x38u,
    Level_eParameterTypeReal32,
    "Zoom Step Factor",
    7u,
    0.0,
    10.0);
  ParameterList_AddParameter(
    Zoom_ptParameterList,
    0x6Cu,
    ParameterEnumList_eParameterTypeInt32,
    "Overlay QTaskType",
    7u,
    &WeaponType_tTaskTypeEnumList);
  ParameterList_AddParameter(Zoom_ptParameterList, 0x48u, Level_eParameterTypebool8, "Loop Sound", 7u, nullptr);
  ParameterList_AddParameter(Zoom_ptParameterList, 0x49u, Level_eParameterTypeString32, "Sound", 7u, nullptr);
  ParameterList_AddParameterMinMax(
    Zoom_ptParameterList,
    0x3Cu,
    Level_eParameterTypeReal32,
    "Stand Breath Offset (degrees)",
    7u,
    0.0,
    10.0);
  ParameterList_AddParameterMinMax(
    Zoom_ptParameterList,
    0x40u,
    Level_eParameterTypeReal32,
    "Crouch Breath Offset (degrees)",
    7u,
    0.0,
    10.0);
  ParameterList_AddParameterMinMax(
    Zoom_ptParameterList,
    0x44u,
    Level_eParameterTypeReal32,
    "Flat Breath Offset (degrees)",
    7u,
    0.0,
    10.0);
  Symbol_Register(
    "TASKTYPE_ZOOM",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)Zoom_eQTaskType,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
}

// source: j/0/weapons/zoom.c:580  [size]
void __cdecl Zoom_Close()
{
  int v0; // esi

  if ( Zoom_ptParameterList )
  {
    v0 = *(_DWORD *)((unsigned int)&Zoom_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
  QTask_DeleteQTaskType(Zoom_eQTaskType);
}
