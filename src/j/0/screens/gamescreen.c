/* j/0/screens/gamescreen.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/screens/gamescreen.c:61  [anchor-mhash]
void __cdecl GameScreen_CameraInAreaCB(struct AreaActivateContext_s *ptContext)
{
  if ( AreaActivateQTask_IsInsideArea(
         ptContext->ptAreaActivateQTask,
         (struct real64x3_t *)&Game_ptGame->ptGameScreenQTask[1].ptPrev[2].tQTaskChildren.ptHead[1]) )
  {
    ++ptContext->nHitCount;
  }
}

// source: j/0/screens/gamescreen.c:85  [anchor-strings]
void __cdecl GameScreen_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *v2; // esi
  struct QTask_s *v3; // eax
  unsigned __int16 v4; // ax
  struct QTask_s *v5; // eax
  float vMaxX; // [esp+0h] [ebp-10h]
  float vMinY; // [esp+4h] [ebp-Ch]
  float vMinX; // [esp+8h] [ebp-8h]
  float ptParent; // [esp+Ch] [ebp-4h]

  if ( AppContext_isFixmeSmall )
  {
    vMaxX = 0.699999988079071;
    vMinY = 0.699999988079071;
    vMinX = 0.30000001192092896;
    ptParent = 0.30000001192092896;
  }
  else
  {
    vMaxX = 1.0;
    vMinY = 1.0;
    vMinX = 0.0;
    ptParent = 0.0;
  }
  v2 = ViewportQTask_New(
         ptQTask,
         ptParent,
         vMinX,
         vMinY,
         vMaxX,
         Game_ptGame->ptWorld,
         &Game_ptGame->tQCamera,
         0,
         0.0,
         0.0,
         0.0,
         1.0);
  ptQTask[1].ptNext = QTask_NewFn(ptQTask, StatusScreen_eQTaskType, nullptr);
  v3 = MenuManager_New(ptQTask, "LOCAL:menusystem/ingamemenu.qsc", false, false, false);
  ptQTask[1].tQTaskChildren.ptHead = (struct QTask_s *)QTask_NewQTaskRef(v3);
  v4 = FadeOut_eFadeOutStartQTaskType;
  ptQTask[1].ptPrev = v2;
  v5 = QTask_NewFn(v2, v4, nullptr);
  v5[1].ptNext = nullptr;
  v5[1].ptPrev = nullptr;
  v5[1].tQTaskChildren.ptHead = nullptr;
  v5[1].tQTaskChildren.ptMiddle = (struct QTask_s *)255;
  RenderContext_Alloc((struct RenderContext_s *)&v5[1].tQTaskChildren.ptTail, 1);
  QTask_NewFn(v2, FadeOut_eFadeOutEndQTaskType, nullptr);
}

void __cdecl sub_45B160(struct QTask_s *a1)
{
  struct QTask_s *ptHead; // ecx
  int v2; // edx
  struct QTask_s *v3; // eax
  void (__cdecl *pfHandler)(struct QTask_s *); // eax
  int v5; // edx

  ptHead = a1->tQTaskChildren.ptHead;
  if ( ptHead->ptNext && ptHead )
  {
    v2 = QTask_nProtectedQTaskStackOffset;
    do
    {
      if ( ptHead->ptNext )
        v3 = ptHead->ptNext->ptNext != nullptr ? ptHead->ptNext : nullptr;
      else
        v3 = nullptr;
      QTask_atProtectedQTaskStack[v2].ptQTask = v3;
      pfHandler = (void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[1][ptHead->eQTaskType].pfHandler;
      v5 = v2 + 1;
      QTask_nProtectedQTaskStackOffset = v5;
      if ( pfHandler )
      {
        pfHandler(ptHead);
        v5 = QTask_nProtectedQTaskStackOffset;
      }
      ptHead = (struct QTask_s *)dword_849C7DC[v5];
      v2 = v5 - 1;
      QTask_nProtectedQTaskStackOffset = v2;
    }
    while ( ptHead );
  }
}

void __cdecl sub_45B1D0(struct QTask_s *a1)
{
  struct QTask_s *ptHead; // ecx
  int v2; // edx
  struct QTask_s *v3; // eax
  int v4; // esi
  void (__cdecl *pfHandler)(struct QTask_s *); // eax
  int v6; // edx

  ptHead = a1->tQTaskChildren.ptHead;
  if ( ptHead->ptNext && ptHead )
  {
    v2 = QTask_nProtectedQTaskStackOffset;
    do
    {
      if ( ptHead->ptNext )
        v3 = ptHead->ptNext->ptNext != nullptr ? ptHead->ptNext : nullptr;
      else
        v3 = nullptr;
      v4 = Screen_eDrawQTaskEvent;
      QTask_atProtectedQTaskStack[v2].ptQTask = v3;
      pfHandler = (void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[v4][ptHead->eQTaskType].pfHandler;
      v6 = v2 + 1;
      QTask_nProtectedQTaskStackOffset = v6;
      if ( pfHandler )
      {
        pfHandler(ptHead);
        v6 = QTask_nProtectedQTaskStackOffset;
      }
      ptHead = (struct QTask_s *)dword_849C7DC[v6];
      v2 = v6 - 1;
      QTask_nProtectedQTaskStackOffset = v2;
    }
    while ( ptHead );
  }
}

void __cdecl sub_45B250(struct QTask_s *a1)
{
  QTask_DeleteQTaskAndQTaskRefSafe((struct QReference_s **)&a1[1].tQTaskChildren);
}

// source: j/0/screens/gamescreen.c:172  [anchor-hash]
void __cdecl GameScreen_Open()
{
  unsigned __int16 BaseQTaskType; // ax
  unsigned __int16 v1; // si

  BaseQTaskType = QTask_GetBaseQTaskType();
  v1 = QTask_NewQTaskType("GameScreen", 52, BaseQTaskType, 0, 0);
  GameScreen_eQTaskType = v1;
  QTask_LinkQTaskEventHandlerFn(v1, 0, GameScreen_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 1, sub_45B160);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 2, sub_45B250);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, Screen_eDrawQTaskEvent, sub_45B1D0);
  GameScreen_bAreaActivateCriteriaCamera = AreaActivateQTask_RegisterCriteria(
                                             "CRITERIA_CAMERA",
                                             GameScreen_CameraInAreaCB);
}

// source: j/0/screens/gamescreen.c:199  [anchor-hash]
void __cdecl GameScreen_Close()
{
  int v0; // ecx
  int i; // eax
  int v2; // eax

  v0 = GameScreen_bAreaActivateCriteriaCamera;
  for ( i = 0; (v0 & 1) == 0; ++i )
    v0 >>= 1;
  v2 = i;
  AreaActivate_atCriteria[v2].isUsed = 0;
  Symbol_Remove(AreaActivate_atCriteria[v2].zName);
  QTask_DeleteQTaskType(GameScreen_eQTaskType);
}

// source: j/0/screens/gamescreen.c:216  [size]
struct QTask_s *__cdecl GameScreen_New(struct QTask_s *ptParent)
{
  return QTask_NewFn(ptParent, GameScreen_eQTaskType, nullptr);
}

// source: j/0/screens/gamescreen.c:229  [size]
struct QTask_s *__cdecl GameScreen_GetViewportQTask(struct QTask_s *ptGameScreenQTask)
{
  return ptGameScreenQTask[1].ptPrev;
}

void __cdecl sub_45B360(struct QTask_s *ptParent, void *pxContext)
{
  Serialize_SerializeChild(ptParent, *(struct QTask_s **)&ptParent[14].eQTaskType, pxContext);
}
