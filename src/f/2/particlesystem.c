/* f/2/particlesystem.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: f/2/particlesystem.c:290  [anchor-mhash]
int __cdecl ParticleSystem_isObjectVisible(struct real64x3_t *ptCenter, float vRadius)
{
  double v2; // rt0
  double v3; // st6
  double v4; // st7
  double v5; // st7
  double v6; // st6
  double v7; // st6
  float tV1; // [esp+0h] [ebp-24h]
  float tV1_4; // [esp+4h] [ebp-20h]
  float tV1_8; // [esp+8h] [ebp-1Ch]
  float tV; // [esp+Ch] [ebp-18h]
  float tV_4; // [esp+10h] [ebp-14h]
  float tV_8; // [esp+14h] [ebp-10h]

  v2 = ptCenter->vY - TransContext_tActiveTransContext.tPos.vY;
  tV1 = ptCenter->vX - TransContext_tActiveTransContext.tPos.vX;
  v3 = ptCenter->vZ - TransContext_tActiveTransContext.tPos.vZ;
  tV = TransContext_tActiveTransContext.tMatrix.tX.vZ * v3
     + TransContext_tActiveTransContext.tMatrix.tX.vY * v2
     + TransContext_tActiveTransContext.tMatrix.tX.vX * tV1;
  tV_4 = TransContext_tActiveTransContext.tMatrix.tY.vZ * v3
       + TransContext_tActiveTransContext.tMatrix.tY.vY * v2
       + TransContext_tActiveTransContext.tMatrix.tY.vX * tV1;
  tV_8 = TransContext_tActiveTransContext.tMatrix.tZ.vZ * v3
       + TransContext_tActiveTransContext.tMatrix.tZ.vY * v2
       + TransContext_tActiveTransContext.tMatrix.tZ.vX * tV1;
  v4 = tV;
  if ( tV < 0.0 )
    v4 = -v4;
  v5 = v4 - vRadius;
  v6 = tV_4;
  if ( tV_4 < 0.0 )
    v6 = -v6;
  tV1_4 = v6 - vRadius;
  v7 = tV_8 + vRadius;
  tV1_8 = v7;
  if ( v7 < 0.0 )
    return 0;
  return (v5 < 0.0 || v5 <= TransContext_tActiveTransContext.vFOVX * tV1_8)
      && (tV1_4 < 0.0 || TransContext_tActiveTransContext.vFOVY * tV1_8 >= tV1_4);
}

// source: f/2/particlesystem.c:339  [anchor-mhash]
void __cdecl ParticleSystem_EnterHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { int nIterate; };
    struct { char igi2_o1[4]; int v12; };
    struct { char igi2_o2[8]; int v13; };
    struct { char igi2_o3[12]; int v14; };
    struct { char igi2_o4[16]; int v15; };
    struct { char igi2_o5[20]; int v16; };
    struct { char igi2_o6[24]; int v17; };
    struct { char igi2_o7[28]; int v18; };
    struct { char igi2_o8[64]; struct real64x3_t tPos; };
    struct { char igi2_o9[88]; struct real64x3_t tRealPos; };
    char igi2_extent[112];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QReference_s *ptHead; // eax
  struct QTask_s *v3; // esi
  int v4; // eax
  int v5; // ecx
  int v6; // ecx
  int v7; // esi
  int v8; // edi
  struct QReference_s *v9; // edx
  bool v10; // zf

  if ( LOBYTE(ptQTask[4].tQTaskRefList.ptTail) )
  {
    qmemcpy(&ptQTask[3].tQTaskRefList.ptMiddle, &TransContext_tActiveTransContext.tPos, 0x18u);
    LOBYTE(ptQTask[4].tQTaskRefList.ptTail) = 0;
  }
  ptHead = ptQTask[4].tQTaskRefList.ptHead;
  *(float *)&ptQTask[4].tQTaskChildren.ptHead = TransContext_tActiveTransContext.tPos.vX
                                              - *(double *)&ptQTask[3].tQTaskRefList.ptMiddle;
  *(float *)&ptQTask[4].tQTaskChildren.ptMiddle = TransContext_tActiveTransContext.tPos.vY
                                                - *(double *)&ptQTask[3].ptParent;
  *(float *)&ptQTask[4].tQTaskChildren.ptTail = TransContext_tActiveTransContext.tPos.vZ - *(double *)&ptQTask[4].ptNext;
  qmemcpy(&ptQTask[3].tQTaskRefList.ptMiddle, &TransContext_tActiveTransContext.tPos, 0x18u);
  if ( ptHead )
    ((void (__cdecl *)(struct QTask_s *))ptHead)(ptQTask);
  v3 = ptQTask[3].tQTaskChildren.ptHead;
  v4 = ~(int)ptQTask[3].ptNext;
  v5 = *(_DWORD *)&ptQTask[2].eQTaskType;
  igi2_frame.nIterate = 2 * v5 - 1;
  if ( igi2_frame.nIterate > 0 )
  {
    v6 = (_DWORD)v3 * v5;
    igi2_frame.v18 = (v4 & (__int64)TransContext_tActiveTransContext.tPos.vZ) + v6 + (int)v3 / 2;
    v7 = -(int)v3;
    igi2_frame.v17 = v6 + (v4 & (__int64)TransContext_tActiveTransContext.tPos.vY);
    igi2_frame.v14 = (v4 & (__int64)TransContext_tActiveTransContext.tPos.vX) + v6;
    igi2_frame.v16 = igi2_frame.nIterate;
    do
    {
      igi2_frame.v13 = igi2_frame.v17;
      igi2_frame.v15 = igi2_frame.nIterate;
      do
      {
        v8 = igi2_frame.nIterate;
        igi2_frame.v12 = igi2_frame.v18;
        do
        {
          v9 = ptQTask[3].tQTaskRefList.ptHead;
          igi2_frame.tRealPos.vZ = (double)igi2_frame.v12;
          igi2_frame.tRealPos.vX = (double)igi2_frame.v14;
          igi2_frame.tRealPos.vY = (double)igi2_frame.v13;
          if ( ParticleSystem_isObjectVisible(&igi2_frame.tRealPos, *(float *)&v9) )
          {
            igi2_frame.tPos.vX = (double)igi2_frame.v14;
            igi2_frame.tPos.vY = (double)igi2_frame.v13;
            igi2_frame.tPos.vZ = (double)igi2_frame.v12;
            ((void (__cdecl *)(struct QTask_s *, struct real64x3_t *))ptQTask[4].tQTaskRefList.ptMiddle)(ptQTask, &igi2_frame.tPos);
          }
          --v8;
          igi2_frame.v12 += v7;
        }
        while ( v8 );
        v10 = igi2_frame.v15 == 1;
        igi2_frame.v13 += v7;
        --igi2_frame.v15;
      }
      while ( !v10 );
      v10 = igi2_frame.v16 == 1;
      igi2_frame.v14 += v7;
      --igi2_frame.v16;
    }
    while ( !v10 );
  }
}

// source: f/2/particlesystem.c:465  [anchor-mhash]
void __cdecl ParticleSystem_DeleteHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptMiddle; // eax
  struct QTask_s *ptTail; // eax
  struct QTask_s *v3; // eax
  int v4; // ebx

  ptMiddle = ptQTask[2].tQTaskChildren.ptMiddle;
  if ( ptMiddle )
    ptMiddle[2].tQTaskChildren.ptTail = ptQTask[2].tQTaskChildren.ptTail;
  else
    ptQTask[3].tQTaskChildren.ptTail[2].ptPrev = ptQTask[2].tQTaskChildren.ptTail;
  ptTail = ptQTask[2].tQTaskChildren.ptTail;
  if ( ptTail )
    ptTail[2].tQTaskChildren.ptMiddle = ptQTask[2].tQTaskChildren.ptMiddle;
  v3 = ptQTask[3].tQTaskChildren.ptMiddle;
  if ( v3 )
  {
    v4 = *(_DWORD *)((unsigned int)&v3[-1].eQTaskType & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v4);
    memset(*(void **)(v4 + 8), 0xCDu, *(_DWORD *)(v4 + 16));
    free((void *)v4);
  }
  ptQTask[3].tQTaskChildren.ptMiddle = nullptr;
}

// source: f/2/particlesystem.c:486  [anchor-hash]
void __cdecl ParticleSystem_Open()
{
  unsigned __int16 v0; // si

  v0 = QTask_NewQTaskType("ParticleSystemDynCubeObj", 192, DynCubeObj_eQTaskType, 0, 0);
  ParticleSystem_eQTaskType = v0;
  QTask_LinkQTaskEventHandlerFn(v0, 5, ParticleSystem_EnterHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 2, ParticleSystem_DeleteHandler);
  QTask_LinkQTaskEventHandlerFn(v0, DynCubeObj_eDynCubeObjRegisterQTaskEvent, nullptr);
  QTask_LinkQTaskEventHandlerFn(v0, DynCubeObj_eDynCubeObjRemoveQTaskEvent, nullptr);
  ParticleSystem_tRandomState.anRandom[0] = -923067897;
  ParticleSystem_tRandomState.anRandom[1] = 971667286;
  ParticleSystem_tRandomState.anRandom[2] = 2146516173;
}

// source: f/2/particlesystem.c:532  [size]
void __cdecl ParticleSystem_Close()
{
  QTask_DeleteQTaskType(ParticleSystem_eQTaskType);
}

// source: f/2/particlesystem.c:560  [anchor-mhash]
struct QParticleSystem_s *__cdecl ParticleSystem_New(
        struct QTask_s *ptParent,
        int nParticles,
        int nBoxSize,
        int nStructSize,
        int nDepth,
        void (__cdecl *pfUpdate)(struct QParticleSystem_s *),
        void (__cdecl *pfDraw)(struct QParticleSystem_s *, struct real64x3_t *),
        struct World_s *ptWorld,
        unsigned __int16 eQTaskType)
{
  int v9; // ebx
  struct QTask_s *v10; // esi
  struct World_s *v11; // edi
  struct QTask_s *v12; // eax
  double *v13; // ecx
  unsigned int v14; // edi
  unsigned int v15; // edi
  unsigned int v16; // edi
  struct DynCubeObj_s *ptManualRedrawList; // eax
  struct DynCubeObj_s *ptPrev; // eax
  int nParticlesa = *(int *)&nBoxSize; // [esp+18h] [ebp+8h] ARGSLOT

  v9 = nBoxSize - 1;
  v10 = QTask_NewFn(ptParent, eQTaskType, nullptr);
  memset(&v10[1], 0, 0x48u);
  *(float *)&v10[3].tQTaskRefList.ptHead = (double)nBoxSize * 1.7319999933242798;
  v11 = ptWorld;
  v10[3].ptPrev = (struct QTask_s *)nParticles;
  v10[3].tQTaskChildren.ptHead = (struct QTask_s *)nBoxSize;
  *(_DWORD *)&v10[2].eQTaskType = nDepth;
  BYTE1(v10[4].tQTaskRefList.ptTail) = 1;
  LOBYTE(v10[4].tQTaskRefList.ptTail) = 1;
  v10[2].tQTaskRefList.ptTail = (struct QReference_s *)5;
  v10[3].ptNext = (struct QTask_s *)(nBoxSize - 1);
  v10[2].ptParent = (struct QTask_s *)nStructSize;
  v10[3].tQTaskChildren.ptTail = (struct QTask_s *)ptWorld;
  v10[4].tQTaskRefList.ptHead = (struct QReference_s *)pfUpdate;
  v10[4].tQTaskRefList.ptMiddle = (struct QReference_s *)pfDraw;
  v12 = (struct QTask_s *)Mem_AllocFn(nStructSize * nParticles, 4);
  v10[3].tQTaskChildren.ptMiddle = v12;
  v13 = (double *)v12;
  if ( nParticles > 0 )
  {
    nParticlesa = nParticles;
    do
    {
      v14 = (ParticleSystem_tRandomState.anRandom[0] >> 7) ^ ParticleSystem_tRandomState.anRandom[2];
      ParticleSystem_tRandomState.anRandom[0] += v14 ^ ParticleSystem_tRandomState.anRandom[1];
      ParticleSystem_tRandomState.anRandom[2] = v14;
      ParticleSystem_tRandomState.anRandom[1] ^= v14;
      *v13 = (double)(v9 & ParticleSystem_tRandomState.anRandom[0]);
      v15 = (ParticleSystem_tRandomState.anRandom[0] >> 7) ^ ParticleSystem_tRandomState.anRandom[2];
      ParticleSystem_tRandomState.anRandom[0] += v15 ^ ParticleSystem_tRandomState.anRandom[1];
      ParticleSystem_tRandomState.anRandom[2] = v15;
      ParticleSystem_tRandomState.anRandom[1] ^= v15;
      v13[1] = (double)(v9 & ParticleSystem_tRandomState.anRandom[0]);
      v16 = (ParticleSystem_tRandomState.anRandom[0] >> 7) ^ ParticleSystem_tRandomState.anRandom[2];
      ParticleSystem_tRandomState.anRandom[0] += v16 ^ ParticleSystem_tRandomState.anRandom[1];
      ParticleSystem_tRandomState.anRandom[2] = v16;
      ParticleSystem_tRandomState.anRandom[1] ^= v16;
      v13[2] = (double)(v9 & ParticleSystem_tRandomState.anRandom[0]);
      v13 = (double *)((char *)v13 + nStructSize);
      --nParticlesa;
    }
    while ( nParticlesa );
    v11 = ptWorld;
  }
  ptManualRedrawList = v11->ptManualRedrawList;
  if ( ptManualRedrawList )
  {
    ptManualRedrawList->ptPrev = (struct DynCubeObj_s *)v10;
    v11->ptManualRedrawList->ptPrev->ptNext = v11->ptManualRedrawList;
    ptPrev = v11->ptManualRedrawList->ptPrev;
    v11->ptManualRedrawList = ptPrev;
    ptPrev->ptPrev = nullptr;
  }
  else
  {
    v11->ptManualRedrawList = (struct DynCubeObj_s *)v10;
    v10[2].tQTaskChildren.ptTail = nullptr;
    v11->ptManualRedrawList->ptPrev = nullptr;
  }
  return (struct QParticleSystem_s *)v10;
}

// source: f/2/particlesystem.c:623  [size]
void __cdecl ParticleSystem_Delete(struct QParticleSystem_s *ptSystem)
{
  QTask_Delete(&ptSystem->tDynCubeObj.tQObj.tQTask);
}

// source: f/2/particlesystem.c:636  [size]
unsigned __int16 __cdecl ParticleSystem_GetQTaskType()
{
  return ParticleSystem_eQTaskType;
}
