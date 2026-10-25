/* j/0/computer/computerhilight.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/computer/computerhilight.c:110  [anchor-hash]
void __cdecl ComputerHilight_ExtractTaskID(struct ComputerHilight_s *ptComputerHilight)
{
  int v1; // ebx
  char *zQTaskID; // edi
  int v3; // edx
  int nQTaskID; // eax
  int i; // eax
  int v6; // ecx

  v1 = 0;
  zQTaskID = ptComputerHilight->zQTaskID;
  ptComputerHilight->nQTaskID = 0;
  while ( 2 )
  {
    if ( *zQTaskID )
    {
      switch ( *zQTaskID )
      {
        case ' ':
          goto LABEL_15;
        case '-':
          v1 = 1;
          goto LABEL_15;
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
          v3 = atoi(zQTaskID);
          if ( v1 )
          {
            nQTaskID = ptComputerHilight->nQTaskID;
            if ( nQTaskID )
            {
              for ( i = *(_DWORD *)&ptComputerHilight->zQTaskID[4 * nQTaskID + 256] + 1;
                    i < v3;
                    ++ptComputerHilight->nQTaskID )
              {
                v6 = ptComputerHilight->nQTaskID;
                if ( v6 >= 64 )
                  break;
                ptComputerHilight->anQTaskID[v6] = i++;
              }
              v1 = 0;
            }
          }
          for ( ptComputerHilight->anQTaskID[ptComputerHilight->nQTaskID++] = v3; v3; v3 /= 10 )
            ++zQTaskID;
          goto LABEL_16;
        default:
          v1 = 0;
LABEL_15:
          ++zQTaskID;
LABEL_16:
          if ( ptComputerHilight->nQTaskID >= 64 )
            return;
          continue;
      }
    }
    break;
  }
}

// source: j/0/computer/computerhilight.c:195  [anchor-strings]
void __cdecl ComputerHilight_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTaskList_s *v2; // eax

  ptQTask[1].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[1].tQTaskRefList.ptTail = nullptr;
  ptQTask[1].ptParent = nullptr;
  ptQTask[3].tQTaskRefList.ptHead = nullptr;
  LOBYTE(ptQTask[3].tQTaskRefList.ptTail) = 0;
  ptQTask[3].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[10].ptPrev = nullptr;
  ptQTask[16].tQTaskRefList.ptMiddle = nullptr;
  sprintf((char *const)&ptQTask[16].tQTaskRefList.ptTail, "MARKER_NONE");
  ptQTask[17].tQTaskRefList.ptHead = (struct QReference_s *)-1;
  sprintf((char *const)&ptQTask[17].tQTaskRefList.ptMiddle, "MARKER_COLOR_NONE");
  v2 = ComputerHilight_ptQTaskList;
  ptQTask[18].tQTaskChildren.ptTail = (struct QTask_s *)-1;
  LOBYTE(ptQTask[18].tQTaskRefList.ptHead) = 0;
  LOBYTE(ptQTask[24].eQTaskType) = 0;
  ptQTask[31].tQTaskChildren.ptMiddle = (struct QTask_s *)-1;
  ptQTask[31].tQTaskChildren.ptTail = nullptr;
  QTaskList_Register(v2, (struct QTaskList_s *)ptQTask);
}

// source: j/0/computer/computerhilight.c:259  [anchor-mhash]
void __cdecl ComputerHilight_RunHandler(struct QTask_s *ptQTask)
{
  if ( ptQTask[1].tQTaskRefList.ptMiddle && ptQTask[1].tQTaskRefList.ptTail->ptNext )
  {
    if ( ptQTask[1].ptParent )
      ptQTask[31].tQTaskChildren.ptTail = (struct QTask_s *)(__int64)Level_RunLevelExpression(
                                                                       (struct LevelExpression_s *)&ptQTask[1].tQTaskRefList.ptMiddle,
                                                                       ptQTask);
  }
}

// source: j/0/computer/computerhilight.c:278  [anchor-mhash]
void __cdecl ComputerHilight_DeleteHandler(struct QTask_s *ptQTask)
{
  struct QReference_s *ptMiddle; // eax
  int v2; // esi

  Level_DeinitLevelExpression((struct LevelExpression_s *)&ptQTask[1].tQTaskRefList.ptMiddle);
  QTaskList_Remove(ComputerHilight_ptQTaskList, ptQTask);
  ptMiddle = ptQTask[3].tQTaskRefList.ptMiddle;
  if ( ptMiddle )
  {
    v2 = *(_DWORD *)((unsigned int)&ptMiddle[-1].pxObject & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v2);
    memset(*(void **)(v2 + 8), 0xCDu, *(_DWORD *)(v2 + 16));
    free((void *)v2);
    ptQTask[3].tQTaskRefList.ptMiddle = nullptr;
  }
}

// source: j/0/computer/computerhilight.c:308  [size]
void __cdecl ComputerHilight_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = ComputerHilight_ptParameterList;
}

// source: j/0/computer/computerhilight.c:324  [anchor-caller]
void __cdecl ComputerHilight_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QReference_s *ptMiddle; // esi
  int v3; // ebp

  ComputerHilight_ExtractTaskID((struct ComputerHilight_s *)ptQTask);
  ptMiddle = ptQTask[3].tQTaskRefList.ptMiddle;
  v3 = 0;
  ptQTask[16].tQTaskRefList.ptMiddle = nullptr;
  if ( ptMiddle )
  {
    while ( strcmp((char *)ptMiddle, ComputerMenu_tComputerMenuResource.azQSpriteHilight[v3]) )
    {
      if ( ++v3 >= 20 )
        goto LABEL_6;
    }
    ptQTask[16].tQTaskRefList.ptMiddle = (struct QReference_s *)(24 * v3 + 127857332);
  }
LABEL_6:
  ptQTask[17].tQTaskRefList.ptHead = (struct QReference_s *)Script_ParseLineInt32((char *)&ptQTask[16].tQTaskRefList.ptTail);
  ptQTask[18].tQTaskChildren.ptTail = (struct QTask_s *)Script_ParseLineInt32((char *)&ptQTask[17].tQTaskRefList.ptMiddle);
  Level_CompileLevelExpression((struct LevelExpression_s *)&ptQTask[1].tQTaskRefList.ptMiddle, ptQTask);
}

// source: j/0/computer/computerhilight.c:389  [anchor-mhash]
void __cdecl ComputerHilight_DrawComputerObjectHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *ptPrev; // eax
  int v4; // ebp
  bool v5; // zf
  __int16 v6; // ax
  int ptNext; // ecx
  struct QReference_s *v8; // ecx
  unsigned __int16 *pxObject; // edi
  void (__cdecl *pfHandler)(unsigned __int16 *, void *); // ecx
  struct QTask_s *v11; // ecx
  struct QTask_s *ptQTaska = *(struct QTask_s * *)&ptQTask; // [esp+8h] [ebp+4h] ARGSLOT

  if ( ptQTask[31].tQTaskChildren.ptTail )
  {
    *((_DWORD *)pxContext + 6) = ptQTask[16].tQTaskRefList.ptMiddle;
    *((_DWORD *)pxContext + 7) = ptQTask[17].tQTaskRefList.ptHead;
    *((_DWORD *)pxContext + 8) = ptQTask[18].tQTaskChildren.ptTail;
    *((_DWORD *)pxContext + 9) = (char *)ptQTask + 740;
    *((_DWORD *)pxContext + 10) = (char *)ptQTask + 996;
    ptPrev = ptQTask[10].ptPrev;
    v4 = 0;
    v5 = ptPrev == nullptr;
    if ( (int)ptPrev > 0 )
    {
      v6 = ComputerObject_eDrawComputerObjectQTaskEvent;
      ptQTaska = (struct QTask_s *)((char *)ptQTask + 408);
      do
      {
        ptNext = (int)ptQTaska->ptNext;
        if ( (int)ptQTaska->ptNext >= 0 && ptNext < 4096 )
        {
          v8 = Level_atLevelQTaskID[ptNext];
          if ( v8 )
          {
            pxObject = (unsigned __int16 *)v8->pxObject;
            if ( pxObject )
            {
              if ( v6 == 512 )
              {
                v6 = QTask_NewQTaskEventFn(0x200u, "DrawComputerObject");
                ComputerObject_eDrawComputerObjectQTaskEvent = v6;
              }
              pfHandler = (void (__cdecl *)(unsigned __int16 *, void *))QTask_aatQTaskFinalEvent[v6][pxObject[18]].pfHandler;
              if ( pfHandler )
              {
                pfHandler(pxObject, pxContext);
                v6 = ComputerObject_eDrawComputerObjectQTaskEvent;
              }
            }
          }
        }
        v11 = ptQTask[10].ptPrev;
        ++v4;
        ptQTaska = (struct QTask_s *)((char *)ptQTaska + 4);
      }
      while ( v4 < (int)v11 );
      v5 = v11 == nullptr;
    }
    if ( v5 )
    {
      if ( ptQTask[16].tQTaskRefList.ptMiddle )
      {
        *((_DWORD *)pxContext + 3) = ptQTask + 1;
        ComputerObject_DrawSprite((struct DrawComputerObjectContext_s *)pxContext);
      }
    }
  }
}

// source: j/0/computer/computerhilight.c:445  [anchor-hash]
void __cdecl ComputerHilight_Open()
{
  unsigned __int16 v0; // si
  __int16 v1; // ax
  struct ParameterList_s *v2; // eax
  int v3; // edx

  dword_79EE340 = 20;
  dword_79EE344 = (int)ComputerMenu_tComputerMenuResource.azQSpriteHilight;
  v0 = QTask_NewQTaskType("ComputerHilight", 1264, EditorRigidObj_eQTaskType, 0, 0);
  ComputerHilight_eQTaskType = v0;
  QTask_LinkQTaskEventHandlerFn(
    v0,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveHandler);
  QTask_LinkQTaskEventHandlerFn(v0, 0, ComputerHilight_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 1, ComputerHilight_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 2, ComputerHilight_DeleteHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))ComputerHilight_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    ParameterList_eUpdateInternalDataQTaskEvent,
    ComputerHilight_UpdateInternalDataHandler);
  v1 = ComputerObject_eDrawComputerObjectQTaskEvent;
  if ( ComputerObject_eDrawComputerObjectQTaskEvent == 512 )
  {
    v1 = QTask_NewQTaskEventFn(0x200u, "DrawComputerObject");
    v0 = ComputerHilight_eQTaskType;
    ComputerObject_eDrawComputerObjectQTaskEvent = v1;
  }
  QTask_LinkQTaskEventHandlerFn(v0, v1, ComputerHilight_DrawComputerObjectHandler);
  v2 = (struct ParameterList_s *)Mem_AllocFn(192, 4);
  v3 = Level_eParameterTypeObjectPos;
  v2->ptParameterListItem = (struct ParameterListItem_s *)&v2[1];
  v2->nParameters = 0;
  v2->nMaxParameters = 9;
  ComputerHilight_ptParameterList = v2;
  ParameterList_AddParameter(v2, 0x28u, v3, "Position", 7u, nullptr);
  ParameterList_AddParameter(
    ComputerHilight_ptParameterList,
    0x40u,
    Level_eParameterTypeVarString,
    "Hilight",
    7u,
    nullptr);
  ParameterList_AddParameter(
    ComputerHilight_ptParameterList,
    0x94u,
    Level_eParameterTypeString256,
    "TaskID",
    7u,
    nullptr);
  ParameterList_AddParameter(
    ComputerHilight_ptParameterList,
    0x90u,
    Level_eParameterTypeDropDownCombo,
    "Click to select sprite",
    7u,
    &dword_79EE340);
  ParameterList_AddParameter(
    ComputerHilight_ptParameterList,
    0x29Cu,
    Level_eParameterTypeString32,
    "Marker mesh",
    7u,
    nullptr);
  ParameterList_AddParameter(
    ComputerHilight_ptParameterList,
    0x2C0u,
    Level_eParameterTypeString32,
    "Marker color",
    7u,
    nullptr);
  ParameterList_AddParameter(
    ComputerHilight_ptParameterList,
    0x2E4u,
    Level_eParameterTypeString256,
    "Title text resource",
    7u,
    nullptr);
  ParameterList_AddParameter(
    ComputerHilight_ptParameterList,
    0x3E4u,
    Level_eParameterTypeString256,
    "Info text resource",
    7u,
    nullptr);
  ParameterList_AddParameter(
    ComputerHilight_ptParameterList,
    0x4E4u,
    Level_eParameterTypeInt32,
    "Objective",
    7u,
    nullptr);
  ComputerHilight_ptQTaskList = QTaskList_New(32);
}

// source: j/0/computer/computerhilight.c:494  [size]
void __cdecl ComputerHilight_Close()
{
  int v0; // esi

  if ( ComputerHilight_ptParameterList )
  {
    v0 = *(_DWORD *)((unsigned int)&ComputerHilight_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
  QTask_DeleteQTaskType(ComputerHilight_eQTaskType);
  QTaskList_Delete(ComputerHilight_ptQTaskList);
}

// source: j/0/computer/computerhilight.c:514  [size]
struct QTaskList_s *__cdecl ComputerHilight_GetQTaskList()
{
  return ComputerHilight_ptQTaskList;
}

// source: j/0/computer/computerhilight.c:529  [anchor-callee]
int __cdecl ComputerHilight_GetEnumObjectivePos(
        struct real64x3_t *ptPriPos,
        struct real64x3_t *ptSecPos,
        int nObjective)
{
  int v3; // ebx
  struct QTask_s **ptQTask; // edx
  int nTask; // ebp
  unsigned int ptHead; // ecx
  struct QReference_s *v7; // ecx
  char *pxObject; // ecx
  struct real64x3_t *v9; // edi
  int nCount; // [esp+0h] [ebp-4h]

  v3 = 0;
  nCount = 0;
  if ( ComputerHilight_ptQTaskList->nTask <= 0 )
    return 0;
  ptQTask = ComputerHilight_ptQTaskList->ptQTask;
  nTask = ComputerHilight_ptQTaskList->nTask;
  do
  {
    if ( (*ptQTask)[31].tQTaskChildren.ptMiddle == (struct QTask_s *)nObjective )
    {
      ptHead = (unsigned int)(*ptQTask)[10].tQTaskChildren.ptHead;
      if ( ptHead < 0x1000 && (v7 = Level_atLevelQTaskID[ptHead]) != nullptr )
        pxObject = (char *)v7->pxObject;
      else
        pxObject = nullptr;
      if ( v3 )
      {
        v9 = ptSecPos;
      }
      else
      {
        v3 = 1;
        v9 = ptPriPos;
      }
      qmemcpy(v9, pxObject + 40, sizeof(struct real64x3_t));
      ++nCount;
    }
    ++ptQTask;
    --nTask;
  }
  while ( nTask );
  return nCount;
}

// source: j/0/computer/computerhilight.c:590  [anchor-mhash]
struct QTask_s *__cdecl ComputerHilight_SetObjectivePos(
        struct QTask_s *ptQTask,
        struct real64x3_t *ptPos)
{
  qmemcpy(&ptQTask[1], ptPos, 0x18u);
  *(double *)&ptQTask[1].tQTaskChildren.ptTail = *(double *)&ptQTask[1].tQTaskChildren.ptTail + 8192.0;
  return ptQTask;
}

// source: j/0/computer/computerhilight.c:607  [size]
struct real64x3_t *__cdecl ComputerHilight_GetObjectivePos(struct QTask_s *ptQTask)
{
  return (struct real64x3_t *)&ptQTask[1];
}

// source: j/0/computer/computerhilight.c:623  [size]
void __cdecl ComputerHilight_SetSprite(struct QTask_s *ptQTask, char *pzSprite)
{
  int v2; // edi

  v2 = 0;
  ptQTask[31].tQTaskChildren.ptTail = (struct QTask_s *)1;
  ptQTask[3].tQTaskRefList.ptMiddle = (struct QReference_s *)pzSprite;
  ptQTask[16].tQTaskRefList.ptMiddle = nullptr;
  if ( pzSprite )
  {
    while ( strcmp(pzSprite, ComputerMenu_tComputerMenuResource.azQSpriteHilight[v2]) )
    {
      if ( ++v2 >= 20 )
        return;
    }
    ptQTask[16].tQTaskRefList.ptMiddle = (struct QReference_s *)(24 * v2 + 127857332);
  }
}

// source: j/0/computer/computerhilight.c:660  [size]
unsigned __int16 __cdecl ComputerHilight_GetQTaskType()
{
  return ComputerHilight_eQTaskType;
}
