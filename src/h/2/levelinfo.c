/* h/2/levelinfo.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: h/2/levelinfo.c:436  [anchor-hash]
void __cdecl LevelInfo_Open()
{
  unsigned __int16 BaseQTaskType; // ax

  BaseQTaskType = QTask_GetBaseQTaskType();
  LevelInfo_eQTaskType = QTask_NewQTaskType("LevelInfo", 40, BaseQTaskType, 0, 0);
}

// source: h/2/levelinfo.c:482  [size]
void __cdecl LevelInfo_Close()
{
  QTask_DeleteQTaskType(LevelInfo_eQTaskType);
}
