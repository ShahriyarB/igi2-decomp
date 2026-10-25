/* j/0/weapons/laserdot.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/weapons/laserdot.c:78  [anchor-mhash]
void __cdecl LaserDot_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct World_s *ptWorld; // eax
  struct DynCubeObj_s *ptManualRedrawList; // ecx
  struct DynCubeObj_s *ptPrev; // ecx
  struct QTask_s **p_ptParent; // edx
  struct GameTexture_s *v7; // ebp
  struct TexInfo_s *p_tTexInfo; // ebp
  struct QReference_s **p_ptTail; // eax
  int v10; // edi
  struct Game_s *v11; // eax
  struct QTask_s *v12; // ebp
  struct QTask_s *ptQTaska = *(struct QTask_s * *)&ptQTask; // [esp+14h] [ebp+4h] ARGSLOT

  ptWorld = Game_ptGame->ptWorld;
  ptManualRedrawList = ptWorld->ptManualRedrawList;
  if ( ptManualRedrawList )
  {
    ptManualRedrawList->ptPrev = (struct DynCubeObj_s *)ptQTask;
    ptWorld->ptManualRedrawList->ptPrev->ptNext = ptWorld->ptManualRedrawList;
    ptPrev = ptWorld->ptManualRedrawList->ptPrev;
    ptWorld->ptManualRedrawList = ptPrev;
    ptPrev->ptPrev = nullptr;
  }
  else
  {
    ptWorld->ptManualRedrawList = (struct DynCubeObj_s *)ptQTask;
    ptQTask[2].tQTaskChildren.ptTail = nullptr;
    ptWorld->ptManualRedrawList->ptPrev = nullptr;
  }
  p_ptParent = &ptQTask[3].ptParent;
  ptQTask[3].ptParent = (struct QTask_s *)1124073472;
  *(_DWORD *)&ptQTask[3].eQTaskType = 1124073472;
  ptQTask[4].ptNext = (struct QTask_s *)1124073472;
  ptQTask[5].ptPrev = (struct QTask_s *)-1018377011;
  ptQTask[5].tQTaskChildren.ptTail = (struct QTask_s *)-1018377011;
  ptQTask[5].tQTaskRefList.ptHead = (struct QReference_s *)-1018377011;
  ptQTask[5].ptParent = (struct QTask_s *)-1018377011;
  ptQTask[6].tQTaskChildren.ptMiddle = (struct QTask_s *)((char *)ptQTask + 204);
  ptQTask[8].tQTaskChildren.ptMiddle = (struct QTask_s *)((char *)ptQTask + 204);
  ptQTask[6].tQTaskChildren.ptTail = (struct QTask_s *)((char *)ptQTask + 216);
  v7 = LaserDot_ptGameTexture;
  ptQTask[5].tQTaskRefList.ptTail = (struct QReference_s *)1129106637;
  ptQTask[6].tQTaskRefList.ptHead = (struct QReference_s *)&ptQTask[5].tQTaskRefList.ptTail;
  ptQTask[8].tQTaskChildren.ptTail = (struct QTask_s *)((char *)ptQTask + 228);
  ptQTask[8].tQTaskRefList.ptHead = (struct QReference_s *)&ptQTask[6];
  *(_DWORD *)&ptQTask[2].eQTaskType = 0;
  ptQTask[2].ptParent = (struct QTask_s *)1;
  ptQTask[3].tQTaskChildren.ptHead = nullptr;
  ptQTask[3].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[3].tQTaskChildren.ptTail = nullptr;
  ptQTask[3].tQTaskRefList.ptHead = nullptr;
  ptQTask[3].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[3].tQTaskRefList.ptTail = nullptr;
  ptQTask[5].tQTaskChildren.ptHead = (struct QTask_s *)1129106637;
  ptQTask[5].tQTaskChildren.ptMiddle = (struct QTask_s *)1065353216;
  ptQTask[5].tQTaskRefList.ptMiddle = (struct QReference_s *)1065353216;
  *(_DWORD *)&ptQTask[5].eQTaskType = 1065353216;
  ptQTask[6].ptNext = (struct QTask_s *)1129106637;
  ptQTask[6].ptPrev = (struct QTask_s *)1129106637;
  ptQTask[6].tQTaskChildren.ptHead = (struct QTask_s *)1065353216;
  *(_DWORD *)&ptQTask[6].eQTaskType = 0;
  ptQTask[7].ptNext = (struct QTask_s *)1065353216;
  ptQTask[7].ptPrev = nullptr;
  ptQTask[7].tQTaskChildren.ptHead = nullptr;
  ptQTask[7].tQTaskChildren.ptMiddle = (struct QTask_s *)1065353216;
  ptQTask[7].tQTaskChildren.ptTail = nullptr;
  *(_DWORD *)&ptQTask[8].eQTaskType = 0;
  ptQTask[9].ptNext = (struct QTask_s *)1065353216;
  ptQTask[9].ptPrev = (struct QTask_s *)1065353216;
  ptQTask[9].tQTaskChildren.ptHead = nullptr;
  ptQTask[9].tQTaskChildren.ptMiddle = (struct QTask_s *)1065353216;
  ptQTask[9].tQTaskChildren.ptTail = (struct QTask_s *)1065353216;
  p_tTexInfo = &v7->tTexInfo;
  p_ptTail = &ptQTask[6].tQTaskRefList.ptTail;
  v10 = 2;
  do
  {
    *(p_ptTail - 1) = (struct QReference_s *)p_ptParent;
    *p_ptTail = (struct QReference_s *)p_ptParent;
    p_ptTail[1] = (struct QReference_s *)p_ptParent;
    p_ptTail[8] = (struct QReference_s *)1065353216;
    p_ptTail[9] = (struct QReference_s *)1065353216;
    p_ptTail[10] = (struct QReference_s *)1065353216;
    p_ptTail[15] = nullptr;
    p_ptTail[14] = (struct QReference_s *)p_tTexInfo;
    p_ptTail[11] = nullptr;
    p_ptTail[12] = nullptr;
    p_ptTail[13] = (struct QReference_s *)1065353216;
    p_ptTail += 20;
    --v10;
  }
  while ( v10 );
  v11 = Game_ptGame;
  ptQTask[4].ptPrev = (struct QTask_s *)1065353216;
  ptQTask[4].tQTaskChildren.ptHead = nullptr;
  ptQTask[4].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[4].tQTaskChildren.ptTail = nullptr;
  ptQTask[4].tQTaskRefList.ptHead = (struct QReference_s *)1065353216;
  ptQTask[4].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[4].tQTaskRefList.ptTail = nullptr;
  ptQTask[4].ptParent = nullptr;
  *(_DWORD *)&ptQTask[4].eQTaskType = 1065353216;
  ptQTask[5].ptNext = nullptr;
  ptQTaska = (struct QTask_s *)v11->ptWorld;
  v12 = QTask_NewFn(ptQTask, PolyListDynCubeObj_eQTaskType, nullptr);
  *(_DWORD *)&v12[2].eQTaskType = (char *)ptQTask + 252;
  v12[2].ptParent = ptQTaska;
  v12[4].ptPrev = (struct QTask_s *)2;
  v12[4].tQTaskChildren.ptHead = (struct QTask_s *)8;
  v12[4].tQTaskChildren.ptTail = nullptr;
  v12[4].tQTaskChildren.ptMiddle = nullptr;
  v12[4].tQTaskRefList.ptHead = nullptr;
  v12[4].tQTaskRefList.ptTail = nullptr;
  v12[4].tQTaskRefList.ptMiddle = nullptr;
  v12[4].ptNext = nullptr;
  v12[4].ptParent = (struct QTask_s *)1;
  *(_DWORD *)&v12[4].eQTaskType = QTask_NewQTaskRef(ptQTask);
  qmemcpy(&v12[1], &ptQTask[3].tQTaskChildren, 0x18u);
  qmemcpy(&v12[3], &ptQTask[4].ptPrev, sizeof(struct QTask_s));
  ptQTask[3].ptNext = v12;
}

// source: j/0/weapons/laserdot.c:166  [size]
void __cdecl LaserDot_DeleteHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptMiddle; // ecx
  struct QTask_s *ptTail; // ecx

  ptMiddle = ptQTask[2].tQTaskChildren.ptMiddle;
  if ( ptMiddle )
    ptMiddle[2].tQTaskChildren.ptTail = ptQTask[2].tQTaskChildren.ptTail;
  else
    Game_ptGame->ptWorld->ptManualRedrawList = (struct DynCubeObj_s *)ptQTask[2].tQTaskChildren.ptTail;
  ptTail = ptQTask[2].tQTaskChildren.ptTail;
  if ( ptTail )
    ptTail[2].tQTaskChildren.ptMiddle = ptQTask[2].tQTaskChildren.ptMiddle;
}

// source: j/0/weapons/laserdot.c:182  [anchor-mhash]
void __cdecl LaserDot_EnterHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *v2; // ebx
  struct QTaskNodeList_s *p_tQTaskChildren; // esi
  struct real32x2_t tScreenPos; // [esp+4h] [ebp-8h] BYREF

  v2 = ptQTask;
  if ( *(_DWORD *)&ptQTask[2].eQTaskType && ptQTask[2].ptParent )
  {
    p_tQTaskChildren = &ptQTask[3].tQTaskChildren;
    TransContext_ProjectWorldPos2(
      &TransContext_tActiveTransContext,
      &tScreenPos,
      (float *)&ptQTask,
      (struct real64x3_t *)&ptQTask[3].tQTaskChildren);
    if ( *(float *)&ptQTask > 0.0 )
    {
      qmemcpy(&v2[3].ptNext[1], p_tQTaskChildren, 0x18u);
      qmemcpy(&v2[3].ptNext[3], &v2[4].ptPrev, sizeof(v2[3].ptNext[3]));
      ((void (__cdecl *)(struct QTask_s *, _DWORD))QTask_aatQTaskFinalEvent[5][v2[3].ptNext->eQTaskType].pfHandler)(
        v2[3].ptNext,
        0);
    }
  }
}

// source: j/0/weapons/laserdot.c:215  [anchor-mhash]
void __cdecl LaserDot_SetPosAndNormal(
        struct QTask_s *ptQTask,
        struct real64x3_t *ptPos,
        struct real32x3_t *ptNormal)
{
  Real32x9_FromReal32x3((struct real32x9_t *)&ptQTask[4].ptPrev, ptNormal);
  qmemcpy(&ptQTask[3].tQTaskChildren, ptPos, 0x18u);
  *(struct real32x3_t *)&ptQTask[7].ptParent = *ptNormal;
  *(struct real32x3_t *)&ptQTask[9].ptParent = *ptNormal;
}

// source: j/0/weapons/laserdot.c:238  [size]
enum bool __cdecl LaserDot_EnableDrawing(
        struct QTask_s *ptQTask,
        enum bool isEnabled)
{
  *(_DWORD *)&ptQTask[2].eQTaskType = isEnabled;
  return isEnabled;
}

// source: j/0/weapons/laserdot.c:256  [size]
enum bool __cdecl LaserDot_OverrideDraw(
        struct QTask_s *ptQTask,
        enum bool isEnabled)
{
  ptQTask[2].ptParent = (struct QTask_s *)isEnabled;
  return isEnabled;
}

// source: j/0/weapons/laserdot.c:274  [size]
unsigned __int16 __cdecl LaserDot_GetQTaskType()
{
  return LaserDot_eQTaskType;
}

// source: j/0/weapons/laserdot.c:287  [anchor-hash]
void __cdecl LaserDot_Open()
{
  unsigned __int16 v0; // si

  v0 = QTask_NewQTaskType("LaserDot", 416, DynCubeObj_eQTaskType, 0, 0);
  LaserDot_eQTaskType = v0;
  QTask_LinkQTaskEventHandlerFn(v0, 0, LaserDot_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 2, LaserDot_DeleteHandler);
  QTask_LinkQTaskEventHandlerFn(v0, 5, LaserDot_EnterHandler);
  LaserDot_ptGameTexture = GameFunctions_RegisterGameTexture("laserdot.tga");
}

// source: j/0/weapons/laserdot.c:307  [size]
void __cdecl LaserDot_Close()
{
  QTask_DeleteQTaskType(LaserDot_eQTaskType);
}
