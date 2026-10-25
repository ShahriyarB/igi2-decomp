/* j/0/computer/computer.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/computer/computer.c:71  [anchor-strings]
void __cdecl Computer_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { float ptOrientation; };
    struct { char igi2_o1[16]; float nFrameNumber; };
    struct { char igi2_o2[36]; struct real64x3_t tNull; };
    struct { char igi2_o3[60]; struct real32x9_t tOrientation; };
    char igi2_extent[100];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *ptPrev; // esi
  double nTimeOfDayTick; // st7
  double nFrequency; // st6
  struct QTask_s *v5; // eax
  int v6; // edx
  struct QTask_s *ptParent; // ecx

  ptPrev = Game_ptGame->ptGameScreenQTask[1].ptPrev;
  memset(&igi2_frame.tNull, 0, sizeof(igi2_frame.tNull));
  if ( Computer_ptComputerQTask )
    QTask_Delete(Computer_ptComputerQTask);
  Computer_ptComputerQTask = ptQTask;
  if ( Computer_isEnabled )
    MTP_GetLODVirModelExistsFn("mapcomputer");
  nTimeOfDayTick = (double)LevelFlow_ptLevelFlow->nTimeOfDayTick;
  nFrequency = (double)Flow_ptFlow->nFrequency;
  igi2_frame.tOrientation.tX.vX = 1.0;
  memset(&igi2_frame.tOrientation.tX.vY, 0, 12);
  igi2_frame.tOrientation.tY.vY = 1.0;
  memset(&igi2_frame.tOrientation.tY.vZ, 0, 12);
  igi2_frame.tOrientation.tZ.vZ = 1.0;
  igi2_frame.tOrientation.nOps = 0;
  igi2_frame.nFrameNumber = nTimeOfDayTick / (nFrequency * 3600.0) + LevelFlow_ptLevelFlow->vStartTime;
  igi2_frame.ptOrientation = tan(0.7853981852531433);
  QCamera_Set(
    &Game_ptGame->tQCamera,
    &igi2_frame.tNull,
    &igi2_frame.tOrientation,
    igi2_frame.ptOrientation,
    1.0,
    2000.0,
    Screen_nFrameNumber,
    ptQTask,
    igi2_frame.nFrameNumber,
    0);
  v5 = Computer_ptComputerQTask;
  v6 = Rain_isEnabled;
  ptPrev[10].tQTaskChildren.ptHead = nullptr;
  ptPrev[10].tQTaskChildren.ptMiddle = nullptr;
  ptParent = v5->ptParent;
  isDrawInfra = false;
  Computer_isRain = v6;
  Rain_isEnabled = 0;
  ComputerMap_ptPositionQTask = ptParent;
  if ( Computer_eStartupMode >= 2 && Computer_eStartupMode <= 4 || Computer_isEnabled )
  {
    ComputerMenu_New((enum ComputerMenu_e)Computer_eStartupMode);
  }
  else
  {
    ComputerMenu_eActiveMenu = COMPUTERMENU_OBJECTIVES;
    if ( !ComputerMenu_ptComputerMenuQTask )
      QTask_NewFn(Game_ptGame->ptGameScreenQTask[1].ptPrev, ComputerMenu_eQTaskType, nullptr);
    QTask_NewFn(ComputerMenu_ptComputerMenuQTask, ComputerObjectives_eQTaskType, nullptr);
  }
}

// source: j/0/computer/computer.c:172  [anchor-mhash]
void __cdecl Computer_RunHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptParent; // edx

  ptParent = ptQTask->ptParent;
  qmemcpy(&ptQTask[1], &ptParent[33].tQTaskChildren.ptTail[10].tQTaskChildren, 0x18u);
  qmemcpy(&ptQTask[1].tQTaskRefList.ptMiddle, &ptParent[33].tQTaskChildren.ptTail[10].ptParent, sizeof(struct QTask_s));
}

// source: j/0/computer/computer.c:198  [anchor-hash]
void __cdecl Computer_DeleteHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptPrev; // esi
  int v2; // edx

  ptPrev = Game_ptGame->ptGameScreenQTask[1].ptPrev;
  Computer_ptComputerQTask = nullptr;
  if ( ComputerMenu_ptComputerMenuQTask )
    QTask_Delete(ComputerMenu_ptComputerMenuQTask);
  v2 = Computer_isRain;
  ptPrev[10].tQTaskChildren.ptMiddle = (struct QTask_s *)1;
  ptPrev[10].tQTaskChildren.ptHead = (struct QTask_s *)1;
  Rain_isEnabled = v2;
}

// source: j/0/computer/computer.c:298  [anchor-hash]
void __cdecl Computer_Open()
{
  unsigned __int16 BaseQTaskType; // ax
  unsigned __int16 v1; // si

  BaseQTaskType = QTask_GetBaseQTaskType();
  v1 = QTask_NewQTaskType("Computer", 104, BaseQTaskType, 0, 0);
  Computer_eQTaskType = v1;
  QTask_LinkQTaskEventHandlerFn(v1, 0, Computer_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 1, Computer_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 2, Computer_DeleteHandler);
}

// source: j/0/computer/computer.c:317  [size]
void __cdecl Computer_Close()
{
  QTask_DeleteQTaskType(Computer_eQTaskType);
}

// source: j/0/computer/computer.c:331  [size]
struct QTask_s *__cdecl Computer_New(struct QTask_s *ptParent)
{
  return QTask_NewFn(ptParent, Computer_eQTaskType, nullptr);
}

// source: j/0/computer/computer.c:364  [anchor-hash]
void __cdecl Computer_Delete()
{
  QTask_Delete(Computer_ptComputerQTask);
  Computer_ptComputerQTask = nullptr;
}

// source: j/0/computer/computer.c:379  [size]
struct QTask_s *__cdecl Computer_GetComputerQTask()
{
  return Computer_ptComputerQTask;
}

// source: j/0/computer/computer.c:392  [anchor-hash]
struct QTask_s *__cdecl Computer_GetViewportQTask()
{
  return Game_ptGame->ptGameScreenQTask[1].ptPrev;
}

// source: j/0/computer/computer.c:405  [anchor-hash]
struct QCamera_s *__cdecl Computer_GetQCamera()
{
  return &Game_ptGame->tQCamera;
}

// source: j/0/computer/computer.c:418  [size]
enum bool __cdecl Computer_SetEnabled(enum bool isEnabled)
{
  Computer_isEnabled = isEnabled;
  return isEnabled;
}

// source: j/0/computer/computer.c:431  [size]
enum bool __cdecl Computer_GetEnabled()
{
  return Computer_isEnabled;
}

// source: j/0/computer/computer.c:444  [size]
int __cdecl Computer_SetStartupMode(int eStartupMode)
{
  Computer_eStartupMode = eStartupMode;
  return eStartupMode;
}

void *sub_52B6B0()
{
  void *result; // eax
  struct QTask_s *v1; // eax

  if ( !g_pptQTaskRef || (result = g_pptQTaskRef->pxObject) == nullptr )
  {
    QTask_DeleteQTaskAndQTaskRefSafe(&g_pptQTaskRef);
    v1 = QTask_NewFn(Level_ptDynamicQTask, Container_eQTaskType, nullptr);
    g_pptQTaskRef = QTask_NewQTaskRef(v1);
    return g_pptQTaskRef->pxObject;
  }
  return result;
}
