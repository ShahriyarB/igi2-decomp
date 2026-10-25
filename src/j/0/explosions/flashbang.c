/* j/0/explosions/flashbang.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/explosions/flashbang.c:87  [anchor-mhash]
void __cdecl FlashBang_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct World_s *ptWorld; };
    struct { char igi2_o1[52]; struct real32x2_t tSize; };
    struct { char igi2_o2[60]; struct real32x3_t tRGB; };
    struct { char igi2_o3[72]; struct real32x3_t tAcceleration; };
    char igi2_extent[84];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct Game_s *v2; // eax
  struct QTask_s *v3; // ecx
  struct QSprite_s *p_tQSprite; // edx

  v2 = Game_ptGame;
  v3 = Level_ptDynamicQTask;
  p_tQSprite = &FlashBang_ptSmoke->tQSprite;
  *(_DWORD *)&ptQTask[1].eQTaskType = -1;
  igi2_frame.ptWorld = v2->ptWorld;
  memset(&igi2_frame.tAcceleration, 0, sizeof(igi2_frame.tAcceleration));
  igi2_frame.tRGB.vX = 127.0;
  igi2_frame.tRGB.vY = 127.0;
  igi2_frame.tRGB.vZ = 127.0;
  igi2_frame.tSize.vX = 2457.60009765625;
  igi2_frame.tSize.vY = 2457.60009765625;
  ptQTask[1].tQTaskRefList.ptMiddle = (struct QReference_s *)Particle2DDynCubeObj_New(
                                                               v3,
                                                               igi2_frame.ptWorld,
                                                               p_tQSprite,
                                                               &igi2_frame.tAcceleration,
                                                               &igi2_frame.tRGB,
                                                               &igi2_frame.tSize,
                                                               819200.0,
                                                               (int)&MTP_atLODVirModel[45].atBoneVertexRefs[20].atVertexRefs[783],
                                                               0,
                                                               0.014583333395421505,
                                                               0.0,
                                                               20,
                                                               nullptr);
}

// source: j/0/explosions/flashbang.c:138  [anchor-strings]
void __cdecl FlashBang_RunHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { float ptVel; };
    struct { char igi2_o1[36]; int v16; };
    struct { char igi2_o2[40]; float vIntensity; };
    struct { char igi2_o3[48]; struct real32x3_t tSpeed; };
    struct { char igi2_o4[60]; struct real64x3_t tPos; };
    char igi2_extent[84];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct Game_s *v1; // ebp
  unsigned int v2; // edx
  unsigned int v3; // eax
  int v4; // esi
  unsigned int v5; // edx
  double v6; // st7
  unsigned int v7; // ecx
  int v8; // edi
  int v9; // esi
  unsigned int v10; // edx
  int v11; // eax
  int v12; // esi
  unsigned int v13; // edx
  struct QTask_s *v14; // eax

  v1 = Game_ptGame;
  igi2_frame.tSpeed.vX = 0.0;
  igi2_frame.tSpeed.vY = 0.0;
  igi2_frame.v16 = 3;
  do
  {
    v2 = v1->tRunRandomState.anRandom[0];
    v3 = v2 >> 7;
    qmemcpy(&igi2_frame.tPos, &ptQTask[1], sizeof(igi2_frame.tPos));
    v4 = (v2 >> 7) ^ v1->tRunRandomState.anRandom[2] ^ v1->tRunRandomState.anRandom[1];
    v5 = v4 + v2;
    v1->tRunRandomState.anRandom[2] ^= v3;
    v1->tRunRandomState.anRandom[1] = v4;
    v6 = (double)(unsigned __int16)v5;
    v1->tRunRandomState.anRandom[0] = v5;
    v7 = v1->tRunRandomState.anRandom[0] >> 7;
    v8 = v7 ^ v1->tRunRandomState.anRandom[2];
    v9 = v8 ^ v1->tRunRandomState.anRandom[1];
    v10 = v9 + v1->tRunRandomState.anRandom[0];
    v11 = (unsigned __int16)((v7 ^ LOWORD(v1->tRunRandomState.anRandom[2]) ^ LOWORD(v1->tRunRandomState.anRandom[1]))
                           + LOWORD(v1->tRunRandomState.anRandom[0]));
    igi2_frame.tSpeed.vZ = (v6 * 0.0000152587890625 + 1.0) * 1.5 * 4096000.0 * 9.259259059035685e-06;
    v1->tRunRandomState.anRandom[2] = v8;
    v1->tRunRandomState.anRandom[1] = v9;
    v1->tRunRandomState.anRandom[0] = v10;
    v12 = (v1->tRunRandomState.anRandom[0] >> 7) ^ v1->tRunRandomState.anRandom[2] ^ v1->tRunRandomState.anRandom[1];
    v13 = v12 + v1->tRunRandomState.anRandom[0];
    igi2_frame.vIntensity = ((double)v11 * 0.0000152587890625 + 1.0) * 0.25;
    v1->tRunRandomState.anRandom[2] ^= v1->tRunRandomState.anRandom[0] >> 7;
    v1->tRunRandomState.anRandom[1] = v12;
    v1->tRunRandomState.anRandom[0] = v13;
    igi2_frame.ptVel = ((double)(unsigned __int16)v13 * 0.0000152587890625
           - 0.5
           + (double)(unsigned __int16)v13 * 0.0000152587890625
           - 0.5)
          * 0.04363323375582695
          + 0.02036217600107193;
    Particle2DDynCubeObj_AddParticle(
      (struct QTask_s *)ptQTask[1].tQTaskRefList.ptMiddle,
      &igi2_frame.tPos,
      &igi2_frame.tSpeed,
      igi2_frame.vIntensity,
      igi2_frame.ptVel,
      0.0,
      1.0,
      90,
      30);
    --igi2_frame.v16;
  }
  while ( igi2_frame.v16 );
  v14 = SoundSys_NewSoundFn(Level_ptDynamicQTask, "explo_flash");
  if ( v14 )
    ((void (__cdecl *)(struct QTask_s *, struct QTask_s *))QTask_aatQTaskFinalEvent[SoundSys_eSetPositionQTaskEvent][v14->eQTaskType].pfHandler)(
      v14,
      &ptQTask[1]);
  QTask_Delete(ptQTask);
}

// source: j/0/explosions/flashbang.c:223  [size]
void __cdecl FlashBang_DeleteHandler(struct QTask_s *ptQTask)
{
  ;
}

// source: j/0/explosions/flashbang.c:239  [anchor-hash]
void __cdecl FlashBang_Open()
{
  unsigned __int16 BaseQTaskType; // ax
  unsigned __int16 v1; // si

  FlashBang_eFlashBangQTaskEvent = QTask_NewQTaskEventFn(0, "FlashBang");
  BaseQTaskType = QTask_GetBaseQTaskType();
  v1 = QTask_NewQTaskType("FlashBang", 80, BaseQTaskType, 4, 0);
  FlashBang_eQTaskType = v1;
  QTask_LinkQTaskEventHandlerFn(v1, 0, FlashBang_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 1, FlashBang_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 2, (void (__cdecl *)(struct QTask_s *))FlashBang_DeleteHandler);
  FlashBang_ptBurnMark = GameFunctions_RegisterGameTexture("burn1.tex");
  FlashBang_ptSmoke = GameFunctions_RegisterGameSprite("smoke1.spr");
}

// source: j/0/explosions/flashbang.c:269  [size]
void __cdecl FlashBang_Close()
{
  QTask_DeleteQTaskEvent(FlashBang_eFlashBangQTaskEvent);
  QTask_DeleteQTaskType(FlashBang_eQTaskType);
}

// source: j/0/explosions/flashbang.c:286  [size]
__int16 __cdecl FlashBang_GetFlashBangQTaskEvent()
{
  return FlashBang_eFlashBangQTaskEvent;
}

// source: j/0/explosions/flashbang.c:300  [anchor-callee]
struct QTask_s *__cdecl FlashBang_New(
        struct real64x3_t *ptPos,
        struct QIntersection_s *ptIntersection,
        float vPlayerRange,
        float vAIRange,
        int eTeam)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct FlashBangContext_t tFlashBangContext; };
    struct { char igi2_o1[12]; int v13; };
    char igi2_extent[16];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *v5; // ebx
  struct QTaskList_s *v6; // eax
  int v7; // esi
  int v8; // edi
  struct QObj_s *ptHitObj; // eax
  int v10; // ecx

  v5 = QTask_NewFn(Level_ptDynamicQTask, FlashBang_eQTaskType, nullptr);
  *(float *)&v5[1].ptParent = vPlayerRange;
  *(float *)&v5[1].tQTaskRefList.ptTail = vAIRange;
  igi2_frame.tFlashBangContext.ptPos = ptPos;
  v6 = Human_ptQTaskList;
  *(_DWORD *)&v5[1].eQTaskType = eTeam;
  qmemcpy(&v5[1], ptPos, 0x18u);
  igi2_frame.tFlashBangContext.vRange = vPlayerRange;
  igi2_frame.tFlashBangContext.eTeam = eTeam;
  v7 = 0;
  if ( v6->nTask > 0 )
  {
    v8 = 8;
    do
    {
      ((void (__cdecl *)(_DWORD, struct FlashBangContext_t *))QTask_aatQTaskFinalEvent[FlashBang_eFlashBangQTaskEvent][*(unsigned __int16 *)(*(int *)((char *)&v6->nTask + v8) + 36)].pfHandler)(
        *(int *)((char *)&v6->nTask + v8),
        &igi2_frame.tFlashBangContext);
      v6 = Human_ptQTaskList;
      ++v7;
      v8 += 4;
    }
    while ( v7 < Human_ptQTaskList->nTask );
  }
  if ( ptIntersection )
  {
    ptHitObj = ptIntersection->ptHitObj;
    if ( ptIntersection->ptHitObj )
    {
      v10 = BulletHole_eCreateBulletHoleTaskEvent;
      if ( QTask_aatQTaskFinalEvent[v10][ptHitObj->tQTask.eQTaskType].pfHandler )
      {
        igi2_frame.tFlashBangContext.ptPos = (struct real64x3_t *)ptIntersection;
        igi2_frame.tFlashBangContext.eTeam = (int)&FlashBang_ptBurnMark->tTexInfo;
        igi2_frame.tFlashBangContext.vRange = 0.0;
        igi2_frame.v13 = 1157627904;
        ((void (__cdecl *)(struct QObj_s *, struct FlashBangContext_t *))QTask_aatQTaskFinalEvent[v10][ptHitObj->tQTask.eQTaskType].pfHandler)(
          ptHitObj,
          &igi2_frame.tFlashBangContext);
      }
    }
  }
  return v5;
}
