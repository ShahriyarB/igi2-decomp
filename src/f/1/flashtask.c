/* f/1/flashtask.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: f/1/flashtask.c:92  [anchor-mhash]
void __cdecl FlashQTask_RunHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptNext; // edx
  char *v3; // ecx
  struct QTask_s *ptPrev; // esi
  struct QTask_s *v5; // ecx
  double v6; // st7
  double v7; // st6
  struct QTask_s *ptMiddle; // edx
  struct QTask_s *v9; // edx
  struct QTask_s *v10; // esi
  struct QTask_s *v11; // ecx
  struct QTask_s *v12; // edx
  struct QTask_s *v13; // ecx
  struct QTask_s *ptQTaska = *(struct QTask_s * *)&ptQTask; // [esp+10h] [ebp+4h] ARGSLOT
  struct QTask_s *ptQTaskb = *(struct QTask_s * *)&ptQTask; // [esp+10h] [ebp+4h] ARGSLOT

  ptNext = ptQTask[2].ptNext;
  v3 = (char *)ptQTask[1].ptParent + 20 * (_DWORD)ptNext;
  ptPrev = ptQTask[2].ptPrev;
  if ( (int)ptPrev < (int)(*((_DWORD *)v3 - 2)) && !LOBYTE(ptQTask[2].tQTaskChildren.ptHead) )
  {
    v5 = ptQTask[1].ptNext;
    v6 = *(float *)&ptQTask[2].tQTaskRefList.ptMiddle + *(float *)&ptQTask[2].eQTaskType;
    ptQTask[2].ptPrev = (struct QTask_s *)((char *)&ptPrev->ptNext + 1);
    v5 = (struct QTask_s *)((char *)v5 + 112);
    *(float *)&ptQTask[2].eQTaskType = v6;
    v7 = *(float *)&ptQTask[2].tQTaskRefList.ptTail + *(float *)&ptQTask[3].ptNext;
    *(float *)&ptQTask[3].ptNext = v7;
    *(float *)&ptQTaska = *(float *)&ptQTask[2].ptParent + *(float *)&ptQTask[3].ptPrev;
    ptQTask[3].ptPrev = ptQTaska;
    ptQTask[2].tQTaskRefList.ptHead = (struct QReference_s *)ptQTaska;
    *(float *)&ptQTask[2].tQTaskChildren.ptMiddle = v6;
    *(float *)&ptQTask[2].tQTaskChildren.ptTail = v7;
    ptMiddle = ptQTask[2].tQTaskChildren.ptMiddle;
    *(float *)&ptQTask[3].tQTaskChildren.ptMiddle = *(float *)&ptQTask[3].tQTaskChildren.ptHead
                                                  + *(float *)&ptQTask[3].tQTaskChildren.ptMiddle;
    v5->ptNext = ptMiddle;
    v5->ptPrev = ptQTask[2].tQTaskChildren.ptTail;
    v5->tQTaskChildren.ptHead = (struct QTask_s *)ptQTask[2].tQTaskRefList.ptHead;
LABEL_4:
    v9 = ptQTask[1].ptPrev;
    v10 = ptQTask[1].ptNext;
    ptQTaskb = ptQTask[3].tQTaskChildren.ptMiddle;
    v10[3].ptPrev = ptQTaskb;
    World_MoveDynCubeObjRadius(
      (struct World_s *)v9,
      (struct DynCubeObj_s *)v10,
      (struct real64x3_t *)&ptQTask[1].tQTaskChildren,
      *(float *)&ptQTaskb);
    return;
  }
  if ( (int)ptNext < (int)(*(_DWORD *)&ptQTask[1].eQTaskType - 1) )
  {
    *(float *)&ptQTask[2].tQTaskRefList.ptMiddle = (*((float *)v3 + 5) - *(float *)v3) / (double)*((int *)v3 + 3);
    *(float *)&ptQTask[2].tQTaskRefList.ptTail = (*((float *)v3 + 6) - *((float *)v3 + 1)) / (double)*((int *)v3 + 3);
    *(float *)&ptQTask[2].ptParent = (*((float *)v3 + 7) - *((float *)v3 + 2)) / (double)*((int *)v3 + 3);
    *(float *)&ptQTask[3].tQTaskChildren.ptHead = (*((float *)v3 + 9) - *((float *)v3 + 4)) / (double)*((int *)v3 + 3);
    *(_DWORD *)&ptQTask[2].eQTaskType = *(_DWORD *)v3;
    ptQTask[3].ptNext = *((struct QTask_s **)v3 + 1);
    ptQTask[3].ptPrev = *((struct QTask_s **)v3 + 2);
    ptQTask[2].tQTaskChildren.ptMiddle = *(struct QTask_s **)v3;
    ptQTask[2].tQTaskChildren.ptTail = *((struct QTask_s **)v3 + 1);
    ptQTask[2].tQTaskRefList.ptHead = *((struct QReference_s **)v3 + 2);
    v11 = *((struct QTask_s **)v3 + 4);
    ptQTask[2].ptNext = (struct QTask_s *)((char *)&ptNext->ptNext + 1);
    v12 = ptQTask[1].ptNext;
    ptQTask[3].tQTaskChildren.ptMiddle = v11;
    v13 = ptQTask[2].tQTaskChildren.ptMiddle;
    ptQTask[2].ptPrev = nullptr;
    LOBYTE(ptQTask[2].tQTaskChildren.ptHead) = 0;
    v12 = (struct QTask_s *)((char *)v12 + 112);
    v12->ptNext = v13;
    v12->ptPrev = ptQTask[2].tQTaskChildren.ptTail;
    v12->tQTaskChildren.ptHead = (struct QTask_s *)ptQTask[2].tQTaskRefList.ptHead;
    goto LABEL_4;
  }
  if ( *((_DWORD *)v3 + 3) == -1 )
  {
    ptQTask[2].ptNext = nullptr;
    ptQTask[2].ptPrev = nullptr;
    LOBYTE(ptQTask[2].tQTaskChildren.ptHead) = 1;
  }
  else
  {
    QTask_Delete(ptQTask[3].tQTaskChildren.ptTail);
  }
}

// source: f/1/flashtask.c:183  [anchor-mhash]
void __cdecl FlashQTask_DeleteHandler(struct QTask_s *ptQTask)
{
  struct DynCubeObj_s *ptNext; // esi

  ptNext = (struct DynCubeObj_s *)ptQTask[1].ptNext;
  World_RemoveDynCubeObj((struct World_s *)ptQTask[1].ptPrev, ptNext);
  QObjectVector_RemoveElement(
    DynCubeLight_ptPointlightCollection,
    *(_DWORD *)((char *)ptNext[1].tQObj.tQTask.tQTaskChildren.ptTail
              + DynCubeLight_ptPointlightCollection->nElementSize
              - 4));
  QTask_Delete(&ptNext->tQObj.tQTask);
}

// source: f/1/flashtask.c:205  [anchor-hash]
void __cdecl FlashQTask_Open()
{
  unsigned __int16 BaseQTaskType; // ax
  unsigned __int16 v1; // si

  BaseQTaskType = QTask_GetBaseQTaskType();
  v1 = QTask_NewQTaskType("FlashTask", 144, BaseQTaskType, 2, 0);
  FlashQTask_eQTaskType = v1;
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 2, FlashQTask_DeleteHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 1, FlashQTask_RunHandler);
  FlashQTask_isInitialised[0] = 1;
}

// source: f/1/flashtask.c:232  [size]
void __cdecl FlashQTask_Close()
{
  QTask_DeleteQTaskType(FlashQTask_eQTaskType);
  FlashQTask_isInitialised[0] = 0;
}

// source: f/1/flashtask.c:251  [size]
unsigned __int16 __cdecl FlashQTask_GetQTaskType()
{
  return FlashQTask_eQTaskType;
}

// source: f/1/flashtask.c:270  [anchor-mhash]
struct QTask_s *__cdecl FlashQTask_New(
        struct QTask_s *ptParent,
        struct World_s *ptWorld,
        struct real64x3_t *ptPos,
        struct ColorKeyframe_s *atColorKeyframe,
        int nMaxKeyframe)
{
  struct QTask_s *v5; // ebx

  v5 = QTask_NewFn(ptParent, FlashQTask_eQTaskType, nullptr);
  *(_DWORD *)&v5[1].eQTaskType = nMaxKeyframe;
  v5[1].ptPrev = (struct QTask_s *)ptWorld;
  v5[3].tQTaskChildren.ptTail = v5;
  v5[1].ptParent = (struct QTask_s *)atColorKeyframe;
  qmemcpy(&v5[1].tQTaskChildren, ptPos, 0x18u);
  v5[2].ptNext = nullptr;
  v5[2].ptPrev = nullptr;
  LOBYTE(v5[2].tQTaskChildren.ptHead) = 1;
  *(struct real32x3_t *)&v5[2].tQTaskChildren.ptMiddle = atColorKeyframe->tColor;
  v5[1].ptNext = (struct QTask_s *)DynCubeLight_NewPointlight(
                                     ptWorld,
                                     ptPos,
                                     (struct real32x3_t *)&v5[2].tQTaskChildren.ptMiddle,
                                     atColorKeyframe->vRadius);
  return v5;
}

// source: f/1/flashtask.c:308  [size]
struct QTask_s *__cdecl FlashQTask_SetPos(
        struct QTask_s *ptQTask,
        struct real64x3_t *ptPos)
{
  qmemcpy(&ptQTask[1].tQTaskChildren, ptPos, 0x18u);
  return ptQTask;
}
