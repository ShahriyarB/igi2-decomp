/* j/0/human/humananim.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/human/humananim.c:65  [anchor-hash]
int __cdecl HumanAnim_FindAnimatedInfo(unsigned __int8 *a1)
{
  int v1; // eax
  struct AnimatedInfo_t *v2; // ecx

  v1 = 0;
  v2 = HumanAnim_atAnimatedInfo;
  while ( v2->ptHierarchy != a1 && v2->ptHierarchy )
  {
    ++v2;
    ++v1;
    if ( (int)v2 >= 140666776 )
    {
      LDebug_Error("No more AnimatedInfo slots free in HumanAnim module");
      abort();
    }
  }
  return 2056 * v1 + 140660608;
}

// source: j/0/human/humananim.c:90  [anchor-callee]
unsigned __int8 *__cdecl HumanAnim_SetDamagePart(
        unsigned __int8 *ptHierarchy,
        char *zName,
        int nDamagePart)
{
  int AnimatedInfo; // ebx
  int Bone; // eax
  unsigned __int8 *result; // eax
  int *v7; // ecx
  char aisMarked[256]; // [esp+10h] [ebp-100h] BYREF

  AnimatedInfo = HumanAnim_FindAnimatedInfo(ptHierarchy);
  memset(aisMarked, 0, sizeof(aisMarked));
  Bone = Hierarchy_GetBone(ptHierarchy, zName);
  Hierarchy_MarkSubHierarchy((char *)ptHierarchy, Bone, aisMarked);
  result = nullptr;
  v7 = (int *)(AnimatedInfo + 1028);
  do
  {
    if ( aisMarked[(_DWORD)result] )
      *v7 = nDamagePart;
    ++result;
    ++v7;
  }
  while ( (int)result < 256 );
  return result;
}

// source: j/0/human/humananim.c:128  [anchor-strings]
struct AnimHeader_s *__cdecl HumanAnim_SetAnimation(
        struct QTask_s *ptHumanQTask,
        struct AnimHeader_s *ptAnim,
        int nTime,
        float vTransitionTime)
{
  struct QTask_s *ptTail; // edx
  struct QReference_s *ptMiddle; // ecx
  struct QTask_s *v7; // ebp
  struct AnimHeader_s *result; // eax

  ptHumanQTask[34].tQTaskChildren.ptTail[1].ptPrev = (struct QTask_s *)((int)ptHumanQTask[34].tQTaskChildren.ptTail[1].ptPrev
                                                                      | 2);
  ptHumanQTask[34].tQTaskChildren.ptTail[1].ptPrev = (struct QTask_s *)((int)ptHumanQTask[34].tQTaskChildren.ptTail[1].ptPrev
                                                                      | 0x20);
  ptTail = ptHumanQTask[34].tQTaskChildren.ptTail;
  ptMiddle = ptHumanQTask[34].tQTaskRefList.ptMiddle;
  if ( ptTail == (struct QTask_s *)ptMiddle )
  {
    ptHumanQTask[34].tQTaskRefList.ptTail[3].pxObject = (void *)((int)ptHumanQTask[34].tQTaskRefList.ptTail[3].pxObject
                                                               & ~0x20u);
    AnimController_SetAnimationAndTime((struct AnimController_t *)ptHumanQTask[34].tQTaskRefList.ptTail, ptAnim, nTime);
    AnimBlender_Blend(
      (struct AnimBlender_t *)ptHumanQTask[35].ptNext,
      (struct AnimControllerBase_t *)ptHumanQTask[34].tQTaskRefList.ptMiddle,
      (struct AnimControllerBase_t *)ptHumanQTask[34].tQTaskRefList.ptTail,
      (__int64)(vTransitionTime * 4800.0));
    ptHumanQTask[34].tQTaskChildren.ptTail = (struct QTask_s *)ptHumanQTask[34].tQTaskRefList.ptTail;
  }
  else
  {
    if ( ptTail != (struct QTask_s *)ptHumanQTask[34].tQTaskRefList.ptTail )
    {
      LDebug_Error("Human animcontroller is invalid");
      abort();
    }
    ptMiddle[3].pxObject = (void *)((int)ptMiddle[3].pxObject & ~0x20u);
    AnimController_SetAnimationAndTime(
      (struct AnimController_t *)ptHumanQTask[34].tQTaskRefList.ptMiddle,
      ptAnim,
      nTime);
    AnimBlender_Blend(
      (struct AnimBlender_t *)ptHumanQTask[35].ptNext,
      (struct AnimControllerBase_t *)ptHumanQTask[34].tQTaskRefList.ptTail,
      (struct AnimControllerBase_t *)ptHumanQTask[34].tQTaskRefList.ptMiddle,
      (__int64)(vTransitionTime * 4800.0));
    ptHumanQTask[34].tQTaskChildren.ptTail = (struct QTask_s *)ptHumanQTask[34].tQTaskRefList.ptMiddle;
  }
  v7 = ptHumanQTask[34].tQTaskChildren.ptTail;
  result = (struct AnimHeader_s *)((int)v7[1].ptPrev & 0xFFFFFFFD);
  v7[1].ptPrev = (struct QTask_s *)result;
  return result;
}

// source: j/0/human/humananim.c:178  [size]
char *__cdecl HumanAnim_GetActiveAnimation(struct QTask_s *ptQTask)
{
  char *result; // eax

  result = (char *)ptQTask[34].tQTaskChildren.ptTail[1].ptParent;
  if ( result )
    result += 52;
  return result;
}

// source: j/0/human/humananim.c:198  [anchor-callee]
void __cdecl HumanAnim_ScaleAnimationTimeStep(struct QTask_s *ptQTask, float vScale)
{
  ptQTask[34].tQTaskChildren.ptTail[1].tQTaskRefList.ptTail = (struct QReference_s *)(__int64)((double)AnimController_nTicksPerFrame
                                                                                             * vScale);
}

// source: j/0/human/humananim.c:218  [anchor-mhash]
int __cdecl HumanAnim_GetAnimationTotalTime(struct QTask_s *ptQTask)
{
  struct QTask_s *ptParent; // eax

  ptParent = ptQTask[34].tQTaskChildren.ptTail[1].ptParent;
  if ( ptParent )
    return (int)ptParent->tQTaskChildren.ptTail;
  else
    return 0;
}

// source: j/0/human/humananim.c:238  [anchor-mhash]
float __cdecl HumanAnim_GetAnimationTimeFactor(struct QTask_s *ptQTask)
{
  struct QTask_s *ptTail; // eax
  struct QTask_s *ptParent; // ecx

  ptTail = ptQTask[34].tQTaskChildren.ptTail;
  ptParent = ptTail[1].ptParent;
  if ( ptParent )
    return (double)(int)ptTail[1].tQTaskRefList.ptMiddle / (double)(int)ptParent->tQTaskChildren.ptTail;
  else
    return 0.0;
}

// source: j/0/human/humananim.c:258  [size]
char *__cdecl HumanAnim_GetActiveUpperBodyAnimation(struct QTask_s *ptQTask)
{
  char *result; // eax

  result = (char *)ptQTask[34].tQTaskRefList.ptHead[6].ptNext;
  if ( result )
    result += 52;
  return result;
}

// source: j/0/human/humananim.c:279  [anchor-mhash]
void __cdecl HumanAnim_UpdateAnim(struct QTask_s *ptQTask)
{
  AnimController_Step(
    (struct AnimController_t *)ptQTask[34].tQTaskChildren.ptTail,
    (int)ptQTask[34].tQTaskChildren.ptTail[1].tQTaskRefList.ptMiddle
  + (unsigned int)ptQTask[34].tQTaskChildren.ptTail[1].tQTaskRefList.ptTail);
}

// source: j/0/human/humananim.c:304  [size]
int __cdecl HumanAnim_GetFlags(struct QTask_s *ptQTask)
{
  return (int)ptQTask[34].tQTaskChildren.ptTail[1].ptPrev;
}

// source: j/0/human/humananim.c:326  [size]
int __cdecl HumanAnim_GetUpperBodyFlags(struct QTask_s *ptQTask)
{
  return (int)ptQTask[34].tQTaskRefList.ptHead[3].pxObject;
}

// source: j/0/human/humananim.c:349  [anchor-callee]
void __cdecl HumanAnim_SetUpperBodyAnimationFromHeader(
        struct QTask_s *ptQTask,
        struct AnimHeader_s *ptAnim,
        int nTime,
        float vTransitionTime)
{
  struct QReference_s *ptHead; // eax
  struct AnimController_t *ptParent; // ecx
  struct AnimControllerBase_t *ptPrev; // ebx
  struct AnimControllerBase_t *ptNext; // edi
  struct AnimBlender_t *v8; // esi
  struct QReference_s *v9; // ebp
  unsigned int pxObject; // eax

  ptHead = ptQTask[34].tQTaskRefList.ptHead;
  ptParent = (struct AnimController_t *)ptQTask[34].ptParent;
  if ( ptHead == (struct QReference_s *)ptParent )
  {
    ptHead[3].pxObject = (void *)((int)ptHead[3].pxObject | 0x20);
    AnimController_SetAnimationAndTime(*(struct AnimController_t **)&ptQTask[34].eQTaskType, ptAnim, nTime);
    AnimBlender_Blend(
      (struct AnimBlender_t *)ptQTask[35].ptPrev,
      (struct AnimControllerBase_t *)ptQTask[34].ptParent,
      *(struct AnimControllerBase_t **)&ptQTask[34].eQTaskType,
      (__int64)(vTransitionTime * 4800.0));
    ptQTask[34].tQTaskRefList.ptHead = *(struct QReference_s **)&ptQTask[34].eQTaskType;
  }
  else if ( ptHead == *(struct QReference_s **)&ptQTask[34].eQTaskType )
  {
    ptHead[3].pxObject = (void *)((int)ptHead[3].pxObject | 0x20);
    AnimController_SetAnimationAndTime((struct AnimController_t *)ptQTask[34].ptParent, ptAnim, nTime);
    AnimBlender_Blend(
      (struct AnimBlender_t *)ptQTask[35].ptPrev,
      *(struct AnimControllerBase_t **)&ptQTask[34].eQTaskType,
      (struct AnimControllerBase_t *)ptQTask[34].ptParent,
      (__int64)(vTransitionTime * 4800.0));
    ptQTask[34].tQTaskRefList.ptHead = (struct QReference_s *)ptQTask[34].ptParent;
  }
  else
  {
    AnimController_SetAnimationAndTime(ptParent, ptAnim, nTime);
    AnimBlender_Blend(
      (struct AnimBlender_t *)ptQTask[35].ptPrev,
      *(struct AnimControllerBase_t **)&ptQTask[34].eQTaskType,
      (struct AnimControllerBase_t *)ptQTask[34].ptParent,
      0);
    ptPrev = (struct AnimControllerBase_t *)ptQTask[35].ptPrev;
    ptNext = (struct AnimControllerBase_t *)ptQTask[35].ptNext;
    v8 = (struct AnimBlender_t *)ptQTask[35].tQTaskChildren.ptHead;
    ptQTask[34].tQTaskRefList.ptHead = (struct QReference_s *)ptQTask[34].ptParent;
    AnimBlender_Blend(v8, ptNext, ptPrev, (__int64)(vTransitionTime * 4800.0));
  }
  v9 = ptQTask[34].tQTaskRefList.ptHead;
  pxObject = (unsigned int)v9[3].pxObject;
  if ( (struct AnimHeader_s *)ptQTask[34].tQTaskChildren.ptTail[1].ptParent == ptAnim )
    v9[3].pxObject = (void *)(pxObject | 0x20);
  else
    v9[3].pxObject = (void *)(pxObject & 0xFFFFFFDF);
}

// source: j/0/human/humananim.c:407  [anchor-callee]
void __cdecl HumanAnim_SetUpperBodyAnimationAndTimeFromState(
        struct QTask_s *ptQTask,
        int eState,
        int nTime,
        float vTransitionTime)
{
  struct QTask_s *ptNext; // eax
  struct QTask_s *ptPrev; // eax
  struct QTask_s *ptTail; // eax
  struct QTask_s *ptHead; // edx
  int v8; // ecx
  struct AnimHeader_s *v9; // eax
  struct QHashTable_s *v10; // esi
  unsigned int v11; // eax
  int v12; // eax
  int v13; // esi
  int v14; // eax

  ptNext = ptQTask[33].ptNext;
  if ( !ptNext )
    goto LABEL_10;
  ptPrev = ptNext[1].ptPrev;
  if ( !ptPrev )
    goto LABEL_10;
  ptTail = ptPrev->tQTaskChildren.ptTail;
  if ( !ptTail )
    goto LABEL_10;
  ptHead = ptTail[48].tQTaskChildren.ptHead;
  if ( ptQTask[7].tQTaskRefList.ptTail != *(struct QReference_s **)&ptHead[24].eQTaskType )
    ptHead = ptTail[48].tQTaskChildren.ptMiddle;
  if ( ptHead )
  {
    v8 = *((_DWORD *)&ptQTask[32].tQTaskRefList.ptMiddle->ptNext + eState);
    v9 = *((struct AnimHeader_s **)&ptHead[1].ptNext + v8);
    if ( v8 == 233 || v8 == 235 )
    {
      HumanAnim_SetUpperBodyAnimationFromHeader(ptQTask, v9, v9->nTotalTime - nTime, vTransitionTime);
      ptQTask[34].tQTaskRefList.ptHead[5].pxObject = (void *)(__int64)((double)AnimController_nTicksPerFrame * -1.0);
      ptQTask[35].tQTaskRefList.ptHead = (struct QReference_s *)eState;
      return;
    }
  }
  else
  {
LABEL_10:
    v10 = Hierarchy_ptHashTable;
    v11 = Hierarchy_ptHashTable->tPrivate.pfHashFunction(
            Hierarchy_ptHashTable->tPrivate.nHashTableSize,
            *(void **)(*(_DWORD *)(*(_DWORD *)(**(_DWORD **)&ptQTask[2].eQTaskType + 12) + 12) + 160));
    v12 = ((int  (__cdecl *)(struct QHashTable_s *, unsigned int, const void *))Hierarchy_ptHashTable->tPrivate.pfFindElement)(v10, v11, (const void *)(*(void **)(*(_DWORD *)(*(_DWORD *)(**(_DWORD **)&ptQTask[2].eQTaskType + 12) + 12) + 160)));
    v13 = *(_DWORD *)v12;
    v14 = (*(int (__cdecl **)(_DWORD, int *))(*(_DWORD *)v12 + 12))(*(_DWORD *)(*(_DWORD *)v12 + 4), &dword_697578);
    v9 = (struct AnimHeader_s *)(*(int (__cdecl **)(int, int, const void *))(v13 + 28))(v13, v14, (const void *)(&dword_697578));
  }
  HumanAnim_SetUpperBodyAnimationFromHeader(ptQTask, v9, nTime, vTransitionTime);
  ptQTask[35].tQTaskRefList.ptHead = (struct QReference_s *)eState;
}

// source: j/0/human/humananim.c:482  [anchor-callee]
void __cdecl HumanAnim_SetUpperBodyAnimationAndTime(
        struct QTask_s *ptQTask,
        char *zAnim,
        int nTime,
        float vTransitionTime)
{
  struct QHashTable_s *v4; // esi
  unsigned int v5; // eax
  int v6; // eax
  int v7; // esi
  int v8; // eax
  struct AnimHeader_s *v9; // eax

  v4 = Hierarchy_ptHashTable;
  v5 = Hierarchy_ptHashTable->tPrivate.pfHashFunction(
         Hierarchy_ptHashTable->tPrivate.nHashTableSize,
         ptQTask[7].tQTaskRefList.ptTail);
  v6 = ((int  (__cdecl *)(struct QHashTable_s *, unsigned int, const void *))Hierarchy_ptHashTable->tPrivate.pfFindElement)(v4, v5, (const void *)(ptQTask[7].tQTaskRefList.ptTail));
  v7 = *(_DWORD *)v6;
  v8 = (*(int (__cdecl **)(_DWORD, char *))(*(_DWORD *)v6 + 12))(*(_DWORD *)(*(_DWORD *)v6 + 4), zAnim);
  v9 = (struct AnimHeader_s *)(*(int (__cdecl **)(int, int, const void *))(v7 + 28))(v7, v8, (const void *)(zAnim));
  if ( v9 )
    HumanAnim_SetUpperBodyAnimationFromHeader(ptQTask, v9, nTime, vTransitionTime);
}

// source: j/0/human/humananim.c:515  [anchor-callee]
void __cdecl HumanAnim_ClearUpperBodyAnimation(struct QTask_s *ptQTask, float vTransitionTime)
{
  if ( ptQTask[34].tQTaskRefList.ptHead )
  {
    AnimBlender_Blend(
      (struct AnimBlender_t *)ptQTask[35].tQTaskChildren.ptHead,
      (struct AnimControllerBase_t *)ptQTask[35].ptPrev,
      (struct AnimControllerBase_t *)ptQTask[35].ptNext,
      (__int64)(vTransitionTime * 4800.0));
    ptQTask[34].tQTaskRefList.ptHead = nullptr;
  }
}

// source: j/0/human/humananim.c:540  [anchor-caller]
int __cdecl HumanAnim_GetDamagePart(unsigned __int8 *ptHierarchy, int nBone)
{
  return *(_DWORD *)(HumanAnim_FindAnimatedInfo(ptHierarchy) + 4 * nBone + 1028);
}

// source: j/0/human/humananim.c:557  [anchor-strings]
struct QTask_s *__cdecl HumanAnim_Init(struct QTask_s *ptQTask, enum bool isAnimatedUpperBody)
{
  #pragma pack(push, 1)
  union
  {
    struct { unsigned __int16 eQTaskType[2]; };
    struct { char igi2_o1[4]; struct QReference_s *ptTail; };
    char igi2_extent[8];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int AnimatedInfo; // esi
  int v4; // eax
  struct QTask_s *v5; // eax
  struct QReference_s *ptMiddle; // ecx
  struct QTask_s *v7; // eax
  struct QTask_s *v8; // ebp
  struct QTask_s *v9; // eax
  struct QTask_s *ptParent; // ecx
  struct QTask_s *v11; // esi
  struct AnimBlender_t *v12; // eax
  struct AnimControllerBase_t *ptNext; // ebx

  ptQTask[35].tQTaskRefList.ptTail = (struct QReference_s *)Hierarchy_GetBone(
                                                              (unsigned __int8 *)ptQTask[7].tQTaskRefList.ptTail,
                                                              "center");
  ptQTask[35].ptParent = (struct QTask_s *)Hierarchy_GetBone(
                                             (unsigned __int8 *)ptQTask[7].tQTaskRefList.ptTail,
                                             "lower body");
  *(_DWORD *)&ptQTask[35].eQTaskType = Hierarchy_GetBone(
                                         (unsigned __int8 *)ptQTask[7].tQTaskRefList.ptTail,
                                         "upper body");
  ptQTask[36].ptNext = (struct QTask_s *)Hierarchy_GetBone(
                                           (unsigned __int8 *)ptQTask[7].tQTaskRefList.ptTail,
                                           "shoulders");
  ptQTask[35].tQTaskRefList.ptMiddle = (struct QReference_s *)Hierarchy_GetBone(
                                                                (unsigned __int8 *)ptQTask[7].tQTaskRefList.ptTail,
                                                                "head");
  AnimatedInfo = HumanAnim_FindAnimatedInfo((unsigned __int8 *)ptQTask[7].tQTaskRefList.ptTail);
  v4 = *(_DWORD *)AnimatedInfo;
  ++*(_DWORD *)(AnimatedInfo + 2052);
  if ( !v4 )
  {
    *(_DWORD *)AnimatedInfo = ptQTask[7].tQTaskRefList.ptTail;
    Hierarchy_MarkSubHierarchy(
      (char *)ptQTask[7].tQTaskRefList.ptTail,
      (int)ptQTask[35].tQTaskRefList.ptTail,
      (char *)(AnimatedInfo + 4));
    Hierarchy_MarkSubHierarchy(
      (char *)ptQTask[7].tQTaskRefList.ptTail,
      (int)ptQTask[35].ptParent,
      (char *)(AnimatedInfo + 516));
    Hierarchy_MarkSubHierarchy(
      (char *)ptQTask[7].tQTaskRefList.ptTail,
      -(int)ptQTask[35].ptParent,
      (char *)(AnimatedInfo + 772));
    HumanAnim_SetDamagePart((unsigned __int8 *)ptQTask[7].tQTaskRefList.ptTail, "center", 12);
    HumanAnim_SetDamagePart((unsigned __int8 *)ptQTask[7].tQTaskRefList.ptTail, "head", 16);
    HumanAnim_SetDamagePart((unsigned __int8 *)ptQTask[7].tQTaskRefList.ptTail, "upper left arm", 11);
    HumanAnim_SetDamagePart((unsigned __int8 *)ptQTask[7].tQTaskRefList.ptTail, "lower left arm", 10);
    HumanAnim_SetDamagePart((unsigned __int8 *)ptQTask[7].tQTaskRefList.ptTail, "left hand", 9);
    HumanAnim_SetDamagePart((unsigned __int8 *)ptQTask[7].tQTaskRefList.ptTail, "upper right arm", 5);
    HumanAnim_SetDamagePart((unsigned __int8 *)ptQTask[7].tQTaskRefList.ptTail, "lower right arm", 4);
    HumanAnim_SetDamagePart((unsigned __int8 *)ptQTask[7].tQTaskRefList.ptTail, "right hand", 3);
    HumanAnim_SetDamagePart((unsigned __int8 *)ptQTask[7].tQTaskRefList.ptTail, "upper left leg", 8);
    HumanAnim_SetDamagePart((unsigned __int8 *)ptQTask[7].tQTaskRefList.ptTail, "lower left leg", 7);
    HumanAnim_SetDamagePart((unsigned __int8 *)ptQTask[7].tQTaskRefList.ptTail, "left foot", 6);
    HumanAnim_SetDamagePart((unsigned __int8 *)ptQTask[7].tQTaskRefList.ptTail, "upper right leg", 2);
    HumanAnim_SetDamagePart((unsigned __int8 *)ptQTask[7].tQTaskRefList.ptTail, "lower right leg", 1);
    HumanAnim_SetDamagePart((unsigned __int8 *)ptQTask[7].tQTaskRefList.ptTail, "right foot", 0);
  }
  igi2_frame.ptTail = ptQTask[7].tQTaskRefList.ptTail;
  *(_DWORD *)igi2_frame.eQTaskType = ptQTask;
  ptQTask[34].tQTaskRefList.ptMiddle = (struct QReference_s *)QTask_NewFn(
                                                                ptQTask,
                                                                AnimController_eQTaskType,
                                                                igi2_frame.eQTaskType);
  igi2_frame.ptTail = ptQTask[7].tQTaskRefList.ptTail;
  *(_DWORD *)igi2_frame.eQTaskType = ptQTask;
  v5 = QTask_NewFn(ptQTask, AnimController_eQTaskType, igi2_frame.eQTaskType);
  ptMiddle = ptQTask[34].tQTaskRefList.ptMiddle;
  ptQTask[34].tQTaskRefList.ptTail = (struct QReference_s *)v5;
  ptQTask[35].ptNext = (struct QTask_s *)AnimBlender_New(
                                           ptQTask,
                                           (struct AnimControllerBase_t *)ptMiddle,
                                           (struct AnimControllerBase_t *)v5);
  v7 = (struct QTask_s *)ptQTask[34].tQTaskRefList.ptTail;
  ptQTask[34].tQTaskChildren.ptTail = v7;
  v7[1].ptPrev = (struct QTask_s *)((int)v7[1].ptPrev & ~2u);
  v8 = (struct QTask_s *)(AnimatedInfo + 4);
  ptQTask[35].ptNext[1].tQTaskChildren.ptHead = (struct QTask_s *)(AnimatedInfo + 4);
  ptQTask[35].ptNext[1].ptPrev = (struct QTask_s *)((int)ptQTask[35].ptNext[1].ptPrev | 1);
  ptQTask[35].tQTaskChildren.ptMiddle = (struct QTask_s *)isAnimatedUpperBody;
  if ( isAnimatedUpperBody )
  {
    igi2_frame.ptTail = ptQTask[7].tQTaskRefList.ptTail;
    *(_DWORD *)igi2_frame.eQTaskType = ptQTask;
    ptQTask[34].ptParent = QTask_NewFn(ptQTask, AnimController_eQTaskType, igi2_frame.eQTaskType);
    igi2_frame.ptTail = ptQTask[7].tQTaskRefList.ptTail;
    *(_DWORD *)igi2_frame.eQTaskType = ptQTask;
    v9 = QTask_NewFn(ptQTask, AnimController_eQTaskType, igi2_frame.eQTaskType);
    ptParent = ptQTask[34].ptParent;
    *(_DWORD *)&ptQTask[34].eQTaskType = v9;
    ptQTask[34].tQTaskRefList.ptHead = nullptr;
    v11 = (struct QTask_s *)(AnimatedInfo + 516);
    ptParent[1].tQTaskChildren.ptHead = v11;
    *(_DWORD *)(*(_DWORD *)&ptQTask[34].eQTaskType + 48) = v11;
    v12 = AnimBlender_New(
            ptQTask,
            (struct AnimControllerBase_t *)ptQTask[34].ptParent,
            *(struct AnimControllerBase_t **)&ptQTask[34].eQTaskType);
    ptNext = (struct AnimControllerBase_t *)ptQTask[35].ptNext;
    ptQTask[35].ptPrev = &v12->tBase.tQTask;
    ptQTask[35].tQTaskChildren.ptHead = (struct QTask_s *)AnimBlender_New(ptQTask, &v12->tBase, ptNext);
    ptQTask[35].ptPrev[1].ptPrev = (struct QTask_s *)((int)ptQTask[35].ptPrev[1].ptPrev | 1);
    ptQTask[35].ptPrev[1].tQTaskChildren.ptHead = v11;
    ptQTask[35].tQTaskChildren.ptHead[1].tQTaskChildren.ptHead = v8;
  }
  else
  {
    ptQTask[34].ptParent = nullptr;
    *(_DWORD *)&ptQTask[34].eQTaskType = 0;
    ptQTask[35].ptPrev = nullptr;
    ptQTask[35].tQTaskChildren.ptHead = nullptr;
    ptQTask[34].tQTaskRefList.ptHead = nullptr;
  }
  ptQTask[34].tQTaskChildren.ptTail = (struct QTask_s *)ptQTask[34].tQTaskRefList.ptMiddle;
  ptQTask[35].tQTaskChildren.ptTail = (struct QTask_s *)-1;
  ptQTask[35].tQTaskRefList.ptHead = (struct QReference_s *)-1;
  return (struct QTask_s *)-1;
}

// source: j/0/human/humananim.c:666  [anchor-callee]
void __cdecl HumanAnim_DeInit(struct QTask_s *ptQTask)
{
  unsigned __int8 *ptTail; // esi
  _DWORD *AnimatedInfo; // eax

  ptTail = (unsigned __int8 *)ptQTask[7].tQTaskRefList.ptTail;
  if ( ptTail )
  {
    AnimatedInfo = (_DWORD *)HumanAnim_FindAnimatedInfo(ptTail);
    if ( AnimatedInfo[513]-- == 1 )
      *AnimatedInfo = 0;
  }
  if ( ptQTask[34].tQTaskRefList.ptMiddle )
    QTask_Delete((struct QTask_s *)ptQTask[34].tQTaskRefList.ptMiddle);
  if ( ptQTask[34].tQTaskRefList.ptTail )
    QTask_Delete((struct QTask_s *)ptQTask[34].tQTaskRefList.ptTail);
  if ( ptQTask[34].ptParent )
    QTask_Delete(ptQTask[34].ptParent);
  if ( *(_DWORD *)&ptQTask[34].eQTaskType )
    QTask_Delete(*(struct QTask_s **)&ptQTask[34].eQTaskType);
  if ( ptQTask[35].ptNext )
    QTask_Delete(ptQTask[35].ptNext);
  if ( ptQTask[35].ptPrev )
    QTask_Delete(ptQTask[35].ptPrev);
  if ( ptQTask[35].tQTaskChildren.ptHead )
    QTask_Delete(ptQTask[35].tQTaskChildren.ptHead);
  ptQTask[35].tQTaskRefList.ptTail = (struct QReference_s *)-1;
  ptQTask[35].ptParent = (struct QTask_s *)-1;
  ptQTask[35].tQTaskRefList.ptMiddle = (struct QReference_s *)-1;
  ptQTask[36].ptNext = (struct QTask_s *)-1;
}

// source: j/0/human/humananim.c:718  [anchor-callee]
void __cdecl HumanAnim_SetAnimationAndTimeFromState(
        struct QTask_s *ptQTask,
        int eState,
        int nTime,
        float vTransitionTime)
{
  struct QTask_s *ptNext; // eax
  struct QTask_s *ptPrev; // eax
  struct QTask_s *ptTail; // eax
  struct QTask_s *ptHead; // edx
  int v8; // ecx
  struct AnimHeader_s *v9; // eax
  struct QHashTable_s *v10; // esi
  unsigned int v11; // eax
  int v12; // eax
  int v13; // esi
  int v14; // eax

  ptNext = ptQTask[33].ptNext;
  if ( !ptNext )
    goto LABEL_10;
  ptPrev = ptNext[1].ptPrev;
  if ( !ptPrev )
    goto LABEL_10;
  ptTail = ptPrev->tQTaskChildren.ptTail;
  if ( !ptTail )
    goto LABEL_10;
  ptHead = ptTail[48].tQTaskChildren.ptHead;
  if ( ptQTask[7].tQTaskRefList.ptTail != *(struct QReference_s **)&ptHead[24].eQTaskType )
    ptHead = ptTail[48].tQTaskChildren.ptMiddle;
  if ( ptHead )
  {
    v8 = *((_DWORD *)&ptQTask[32].tQTaskRefList.ptMiddle->ptNext + eState);
    v9 = *((struct AnimHeader_s **)&ptHead[1].ptNext + v8);
    if ( v8 == 233 || v8 == 235 )
    {
      HumanAnim_SetAnimation(ptQTask, v9, v9->nTotalTime - nTime, vTransitionTime);
      ptQTask[34].tQTaskChildren.ptTail[1].tQTaskRefList.ptTail = (struct QReference_s *)(__int64)((double)AnimController_nTicksPerFrame
                                                                                                 * -1.0);
      ptQTask[35].tQTaskChildren.ptTail = (struct QTask_s *)eState;
      return;
    }
  }
  else
  {
LABEL_10:
    v10 = Hierarchy_ptHashTable;
    v11 = Hierarchy_ptHashTable->tPrivate.pfHashFunction(
            Hierarchy_ptHashTable->tPrivate.nHashTableSize,
            *(void **)(*(_DWORD *)(*(_DWORD *)(**(_DWORD **)&ptQTask[2].eQTaskType + 12) + 12) + 160));
    v12 = ((int  (__cdecl *)(struct QHashTable_s *, unsigned int, const void *))Hierarchy_ptHashTable->tPrivate.pfFindElement)(v10, v11, (const void *)(*(void **)(*(_DWORD *)(*(_DWORD *)(**(_DWORD **)&ptQTask[2].eQTaskType + 12) + 12) + 160)));
    v13 = *(_DWORD *)v12;
    v14 = (*(int (__cdecl **)(_DWORD, int *))(*(_DWORD *)v12 + 12))(*(_DWORD *)(*(_DWORD *)v12 + 4), &dword_697578);
    v9 = (struct AnimHeader_s *)(*(int (__cdecl **)(int, int, const void *))(v13 + 28))(v13, v14, (const void *)(&dword_697578));
  }
  HumanAnim_SetAnimation(ptQTask, v9, nTime, vTransitionTime);
  ptQTask[35].tQTaskChildren.ptTail = (struct QTask_s *)eState;
}

// source: j/0/human/humananim.c:797  [anchor-mhash]
void __cdecl HumanAnim_SetAnimationAtEndFromState(
        struct QTask_s *ptQTask,
        int eState,
        float vTransitionTime)
{
  struct QTask_s *ptNext; // eax
  struct QTask_s *ptPrev; // eax
  struct QTask_s *ptTail; // eax
  struct QTask_s *ptMiddle; // eax
  struct AnimHeader_s *v7; // eax
  struct QHashTable_s *v8; // esi
  unsigned int v9; // eax
  int v10; // eax
  int v11; // esi
  int v12; // eax

  ptNext = ptQTask[33].ptNext;
  if ( ptNext
    && (ptPrev = ptNext[1].ptPrev) != nullptr
    && (ptTail = ptPrev->tQTaskChildren.ptTail) != nullptr
    && (ptQTask[7].tQTaskRefList.ptTail != *(struct QReference_s **)&ptTail[48].tQTaskChildren.ptHead[24].eQTaskType
      ? (ptMiddle = ptTail[48].tQTaskChildren.ptMiddle)
      : (ptMiddle = ptTail[48].tQTaskChildren.ptHead),
        ptMiddle) )
  {
    v7 = *((struct AnimHeader_s **)&ptMiddle[1].ptNext
         + *((_DWORD *)&ptQTask[32].tQTaskRefList.ptMiddle->ptNext + eState));
  }
  else
  {
    v8 = Hierarchy_ptHashTable;
    v9 = Hierarchy_ptHashTable->tPrivate.pfHashFunction(
           Hierarchy_ptHashTable->tPrivate.nHashTableSize,
           *(void **)(*(_DWORD *)(*(_DWORD *)(**(_DWORD **)&ptQTask[2].eQTaskType + 12) + 12) + 160));
    v10 = ((int  (__cdecl *)(struct QHashTable_s *, unsigned int, const void *))Hierarchy_ptHashTable->tPrivate.pfFindElement)(v8, v9, (const void *)(*(void **)(*(_DWORD *)(*(_DWORD *)(**(_DWORD **)&ptQTask[2].eQTaskType + 12) + 12) + 160)));
    v11 = *(_DWORD *)v10;
    v12 = (*(int (__cdecl **)(_DWORD, int *))(*(_DWORD *)v10 + 12))(*(_DWORD *)(*(_DWORD *)v10 + 4), &dword_697578);
    v7 = (struct AnimHeader_s *)(*(int (__cdecl **)(int, int, const void *))(v11 + 28))(v11, v12, (const void *)(&dword_697578));
  }
  ptQTask[35].tQTaskChildren.ptTail = (struct QTask_s *)eState;
  HumanAnim_SetAnimation(ptQTask, v7, v7->nTotalTime, vTransitionTime);
}

// source: j/0/human/humananim.c:848  [size]
enum bool __cdecl HumanAnim_IsAnimationFinished(struct QTask_s *ptQTask)
{
  return ((int)ptQTask[34].tQTaskChildren.ptTail[1].ptPrev & 4) != 0;
}

// source: j/0/human/humananim.c:882  [size]
void __cdecl HumanAnim_RotateUpperBody(struct QTask_s *ptQTask)
{
  ;
}

// source: j/0/human/humananim.c:1060  [layout]
struct QTask_s *__cdecl HumanAnim_EnableUpperBodyRotation(struct QTask_s *ptQTask)
{
  LOBYTE(ptQTask[36].tQTaskRefList.ptMiddle) = 1;
  return ptQTask;
}

// source: j/0/human/humananim.c:1099  [anchor-callee]
void __cdecl HumanAnim_GetWeaponPositionAndOrientation(
        struct QTask_s *ptHumanQTask,
        struct real64x3_t *ptPos,
        struct real32x9_t *ptOrientation)
{
  struct QTask_s *ptHead; // eax
  struct QTask_s *FirstChildOfType; // eax

  BoneDynCubeObj_UpdateHierarchy(ptHumanQTask);
  ptHead = (struct QTask_s *)ptHumanQTask[34].tQTaskRefList.ptHead;
  if ( !ptHead )
    ptHead = ptHumanQTask[34].tQTaskChildren.ptTail;
  FirstChildOfType = QTask_GetFirstChildOfType(ptHead, WeaponMagicObj_eQTaskType);
  if ( FirstChildOfType )
  {
    qmemcpy(ptPos, &FirstChildOfType[1], sizeof(struct real64x3_t));
    qmemcpy(ptOrientation, &FirstChildOfType[3].ptPrev, sizeof(struct real32x9_t));
  }
  else
  {
    qmemcpy(ptPos, &ptHumanQTask[1], sizeof(struct real64x3_t));
    ptPos->vZ = ptPos->vZ + 4096.0;
    qmemcpy(ptOrientation, &ptHumanQTask[3].ptPrev, sizeof(struct real32x9_t));
  }
}

// source: j/0/human/humananim.c:1155  [anchor-callee]
enum bool __cdecl HumanAnim_IsBlendFinished(struct QTask_s *ptHumanQTask)
{
  struct QTask_s *ptNext; // eax
  struct QTask_s *ptPrev; // edx
  struct QTask_s *v3; // eax
  struct QTask_s *v4; // eax
  unsigned __int8 v5; // dl
  struct QTask_s *ptHead; // eax

  ptNext = ptHumanQTask[35].ptNext;
  if ( ptNext )
    ptPrev = ptNext[1].ptPrev;
  else
    LOBYTE(ptPrev) = 4;
  v3 = ptHumanQTask[35].ptPrev;
  if ( v3 )
    v4 = v3[1].ptPrev;
  else
    LOBYTE(v4) = 4;
  v5 = (unsigned __int8)v4 & (unsigned __int8)ptPrev;
  ptHead = ptHumanQTask[35].tQTaskChildren.ptHead;
  if ( ptHead )
    return v5 & (unsigned __int8)ptHead[1].ptPrev & 4;
  else
    return v5 & 4;
}
