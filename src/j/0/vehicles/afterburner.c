/* j/0/vehicles/afterburner.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/vehicles/afterburner.c:73  [anchor-mhash]
void __cdecl Afterburner_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ((void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[0][RigidMagicObj_eQTaskType].pfHandler)(
    ptQTask,
    pxContext);
  Afterburner_tRandomState.anRandom[0] = -923067897;
  Afterburner_tRandomState.anRandom[1] = 971667286;
  Afterburner_tRandomState.anRandom[2] = 2146516173;
}

// source: j/0/vehicles/afterburner.c:108  [size]
void __cdecl Afterburner_DeleteHandler(struct QTask_s *ptQTask)
{
  World_RemoveDynCubeObj((struct World_s *)ptQTask[2].ptParent, (struct DynCubeObj_s *)ptQTask);
}

// source: j/0/vehicles/afterburner.c:125  [anchor-mhash]
void __cdecl Afterburner_RunHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptNext; // edx
  double v2; // st7
  double v3; // st7
  unsigned int v4; // edx
  struct QTask_s *ptHead; // ecx
  int v6; // edx
  struct QTask_s *v7; // eax
  void (__cdecl *pfHandler)(struct QTask_s *); // eax
  int v9; // edx

  ptNext = ptQTask[8].ptNext;
  if ( *(float *)&ptNext[47].tQTaskRefList.ptMiddle <= 0.8100000023841858 )
    v2 = 0.0;
  else
    v2 = (*(float *)&ptNext[47].tQTaskRefList.ptMiddle - 0.8100000023841858) * 2.2727272510528564;
  if ( v2 != *(float *)&ptQTask[8].tQTaskChildren.ptHead )
    *(float *)&ptQTask[8].tQTaskChildren.ptHead = *(float *)&ptQTask[8].tQTaskChildren.ptHead * 0.9800000190734863
                                                + v2 * 0.019999980926513672;
  v3 = *(float *)&ptQTask[8].tQTaskChildren.ptHead * 1.399999976158142;
  if ( v3 < 1.0 )
    v3 = 1.0;
  v4 = (Afterburner_tRandomState.anRandom[0] >> 7) ^ Afterburner_tRandomState.anRandom[2];
  Afterburner_tRandomState.anRandom[0] += v4 ^ Afterburner_tRandomState.anRandom[1];
  Afterburner_tRandomState.anRandom[2] = v4;
  Afterburner_tRandomState.anRandom[1] ^= v4;
  *(float *)&ptQTask[6].tQTaskChildren.ptHead = (double)LOWORD(Afterburner_tRandomState.anRandom[0])
                                              * 0.0000152587890625
                                              * 0.20000000298023224
                                              + v3;
  ptHead = ptQTask->tQTaskChildren.ptHead;
  if ( ptHead->ptNext && ptHead )
  {
    v6 = QTask_nProtectedQTaskStackOffset;
    do
    {
      if ( ptHead->ptNext )
        v7 = ptHead->ptNext->ptNext != nullptr ? ptHead->ptNext : nullptr;
      else
        v7 = nullptr;
      QTask_atProtectedQTaskStack[v6].ptQTask = v7;
      pfHandler = (void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[1][ptHead->eQTaskType].pfHandler;
      v9 = v6 + 1;
      QTask_nProtectedQTaskStackOffset = v9;
      if ( pfHandler )
      {
        pfHandler(ptHead);
        v9 = QTask_nProtectedQTaskStackOffset;
      }
      ptHead = (struct QTask_s *)dword_849C7DC[v9];
      v6 = v9 - 1;
      QTask_nProtectedQTaskStackOffset = v6;
    }
    while ( ptHead );
  }
}

// source: j/0/vehicles/afterburner.c:175  [size]
void __cdecl Afterburner_UpdateMagicObjHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { float ptDynCubeObj; };
    struct { char igi2_o1[24]; float Real32x3_Rotate_tTemp_8; };
    struct { char igi2_o2[28]; struct real64x3_t tNewPos; };
    struct { char igi2_o3[52]; float v28; };
    struct { char igi2_o4[56]; float v29; };
    struct { char igi2_o5[68]; struct real32x9_t Real32x9_Multiply_tTemp; };
    char igi2_extent[112];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  float *v3; // eax
  double v4; // st7
  double v5; // st6
  double v6; // st5
  double v7; // st4
  double *v8; // eax
  double v9; // st7
  double v10; // st7
  int *v11; // eax
  int v12; // eax
  double v13; // st6
  unsigned int v14; // ecx
  long double v15; // st7
  long double v16; // rt1
  long double v17; // st6
  double v18; // st4
  double v19; // st4
  long double v20; // st7
  int v21; // eax
  char *v22; // ecx
  long double v23; // st7
  double v24; // st6
  float pxContexta = *(float *)&pxContext; // [esp+78h] [ebp+8h] ARGSLOT

  v3 = *((float **)pxContext + 1);
  v4 = v3[2] * *(float *)&ptQTask[5].tQTaskChildren.ptMiddle
     + v3[1] * *(float *)&ptQTask[5].tQTaskChildren.ptHead
     + *v3 * *(float *)&ptQTask[5].ptPrev;
  v5 = v3[5] * *(float *)&ptQTask[5].tQTaskChildren.ptMiddle
     + v3[4] * *(float *)&ptQTask[5].tQTaskChildren.ptHead
     + v3[3] * *(float *)&ptQTask[5].ptPrev;
  v6 = v3[8] * *(float *)&ptQTask[5].tQTaskChildren.ptMiddle + v3[7] * *(float *)&ptQTask[5].tQTaskChildren.ptHead;
  v7 = v3[6];
  v8 = *(double **)pxContext;
  igi2_frame.Real32x3_Rotate_tTemp_8 = v6 + v7 * *(float *)&ptQTask[5].ptPrev;
  igi2_frame.tNewPos.vX = v4 + *(double *)*(_DWORD *)pxContext;
  igi2_frame.tNewPos.vY = v5 + v8[1];
  igi2_frame.tNewPos.vZ = igi2_frame.Real32x3_Rotate_tTemp_8 + v8[2];
  if ( *(float *)&ptQTask[6].tQTaskChildren.ptHead <= (double)*(float *)&ptQTask[6].tQTaskChildren.ptMiddle )
    v9 = *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
  else
    v9 = *(float *)&ptQTask[6].tQTaskChildren.ptHead;
  if ( v9 >= *(float *)&ptQTask[6].ptPrev )
  {
    if ( *(float *)&ptQTask[6].tQTaskChildren.ptHead <= (double)*(float *)&ptQTask[6].tQTaskChildren.ptMiddle )
      v10 = *(float *)&ptQTask[6].tQTaskChildren.ptMiddle;
    else
      v10 = *(float *)&ptQTask[6].tQTaskChildren.ptHead;
  }
  else
  {
    v10 = *(float *)&ptQTask[6].ptPrev;
  }
  v11 = *(int **)&ptQTask[2].eQTaskType;
  if ( v11 && (v12 = *v11) != 0 )
    v13 = *(float *)(*(_DWORD *)(*(_DWORD *)(v12 + 12) + 12) + 120);
  else
    v13 = 1.0;
  igi2_frame.ptDynCubeObj = v13 * v10;
  World_MoveDynCubeObjRadius(Game_ptGame->ptWorld, (struct DynCubeObj_s *)ptQTask, &igi2_frame.tNewPos, igi2_frame.ptDynCubeObj);
  v14 = (Afterburner_tRandomState.anRandom[0] >> 7) ^ Afterburner_tRandomState.anRandom[2];
  Afterburner_tRandomState.anRandom[0] += v14 ^ Afterburner_tRandomState.anRandom[1];
  Afterburner_tRandomState.anRandom[2] = v14;
  Afterburner_tRandomState.anRandom[1] ^= v14;
  v15 = (double)LOWORD(Afterburner_tRandomState.anRandom[0]) * 0.0000152587890625;
  v16 = sin(v15);
  v17 = cos(v15);
  v18 = *(float *)&ptQTask[4].tQTaskChildren.ptHead * 0.0;
  *(float *)&igi2_frame.tNewPos.vX = v17 * *(float *)&ptQTask[4].ptPrev
                        + -v16 * *(float *)&ptQTask[4].tQTaskChildren.ptMiddle
                        + v18;
  *((float *)&igi2_frame.tNewPos.vX + 1) = (*(float *)&ptQTask[4].tQTaskChildren.ptMiddle + *(float *)&ptQTask[4].ptPrev) * 0.0
                              + *(float *)&ptQTask[4].tQTaskChildren.ptHead;
  *(float *)&igi2_frame.tNewPos.vY = v17 * *(float *)&ptQTask[4].tQTaskChildren.ptMiddle + v16 * *(float *)&ptQTask[4].ptPrev + v18;
  v19 = *(float *)&ptQTask[4].tQTaskRefList.ptHead * 0.0;
  *((float *)&igi2_frame.tNewPos.vY + 1) = -v16 * *(float *)&ptQTask[4].tQTaskRefList.ptMiddle
                              + v17 * *(float *)&ptQTask[4].tQTaskChildren.ptTail
                              + v19;
  *(float *)&igi2_frame.tNewPos.vZ = (*(float *)&ptQTask[4].tQTaskRefList.ptMiddle + *(float *)&ptQTask[4].tQTaskChildren.ptTail)
                        * 0.0
                        + *(float *)&ptQTask[4].tQTaskRefList.ptHead;
  *((float *)&igi2_frame.tNewPos.vZ + 1) = v17 * *(float *)&ptQTask[4].tQTaskRefList.ptMiddle
                              + v16 * *(float *)&ptQTask[4].tQTaskChildren.ptTail
                              + v19;
  pxContexta = *(float *)&ptQTask[4].ptParent * 0.0;
  igi2_frame.v28 = -v16 * *(float *)&ptQTask[4].eQTaskType + v17 * *(float *)&ptQTask[4].tQTaskRefList.ptTail + pxContexta;
  igi2_frame.v29 = (*(float *)&ptQTask[4].eQTaskType + *(float *)&ptQTask[4].tQTaskRefList.ptTail) * 0.0
      + *(float *)&ptQTask[4].ptParent;
  v20 = v17 * *(float *)&ptQTask[4].eQTaskType + v16 * *(float *)&ptQTask[4].tQTaskRefList.ptTail + pxContexta;
  v21 = *((_DWORD *)pxContext + 1);
  v22 = (char *)&ptQTask[5].ptNext->ptNext + 1;
  igi2_frame.Real32x9_Multiply_tTemp.tX.vX = igi2_frame.v28 * *(float *)(v21 + 8)
                                + *(float *)&igi2_frame.tNewPos.vX * *(float *)v21
                                + *((float *)&igi2_frame.tNewPos.vY + 1) * *(float *)(v21 + 4);
  igi2_frame.Real32x9_Multiply_tTemp.tX.vY = igi2_frame.v29 * *(float *)(v21 + 8)
                                + *((float *)&igi2_frame.tNewPos.vX + 1) * *(float *)v21
                                + *(float *)&igi2_frame.tNewPos.vZ * *(float *)(v21 + 4);
  igi2_frame.Real32x9_Multiply_tTemp.tX.vZ = v20 * *(float *)(v21 + 8)
                                + *(float *)&igi2_frame.tNewPos.vY * *(float *)v21
                                + *((float *)&igi2_frame.tNewPos.vZ + 1) * *(float *)(v21 + 4);
  igi2_frame.Real32x9_Multiply_tTemp.tY.vX = *((float *)&igi2_frame.tNewPos.vY + 1) * *(float *)(v21 + 16)
                                + igi2_frame.v28 * *(float *)(v21 + 20)
                                + *(float *)&igi2_frame.tNewPos.vX * *(float *)(v21 + 12);
  igi2_frame.Real32x9_Multiply_tTemp.tY.vY = *(float *)&igi2_frame.tNewPos.vZ * *(float *)(v21 + 16)
                                + igi2_frame.v29 * *(float *)(v21 + 20)
                                + *((float *)&igi2_frame.tNewPos.vX + 1) * *(float *)(v21 + 12);
  igi2_frame.Real32x9_Multiply_tTemp.tY.vZ = *((float *)&igi2_frame.tNewPos.vZ + 1) * *(float *)(v21 + 16)
                                + v20 * *(float *)(v21 + 20)
                                + *(float *)&igi2_frame.tNewPos.vY * *(float *)(v21 + 12);
  igi2_frame.Real32x9_Multiply_tTemp.tZ.vX = igi2_frame.v28 * *(float *)(v21 + 32)
                                + *(float *)&igi2_frame.tNewPos.vX * *(float *)(v21 + 24)
                                + *((float *)&igi2_frame.tNewPos.vY + 1) * *(float *)(v21 + 28);
  igi2_frame.Real32x9_Multiply_tTemp.tZ.vY = igi2_frame.v29 * *(float *)(v21 + 32)
                                + *((float *)&igi2_frame.tNewPos.vX + 1) * *(float *)(v21 + 24)
                                + *(float *)&igi2_frame.tNewPos.vZ * *(float *)(v21 + 28);
  v23 = v20 * *(float *)(v21 + 32) + *(float *)&igi2_frame.tNewPos.vY * *(float *)(v21 + 24);
  v24 = *((float *)&igi2_frame.tNewPos.vZ + 1) * *(float *)(v21 + 28);
  igi2_frame.Real32x9_Multiply_tTemp.nOps = (int)&v22[*(_DWORD *)(v21 + 36) + 1];
  igi2_frame.Real32x9_Multiply_tTemp.tZ.vZ = v23 + v24;
  qmemcpy(&ptQTask[3].ptPrev, &igi2_frame.Real32x9_Multiply_tTemp, sizeof(struct QTask_s));
}

// source: j/0/vehicles/afterburner.c:283  [anchor-caller]
void __cdecl Afterburner_EnterHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { float vZ; };
    struct { char igi2_o1[4]; _BYTE v20[24]; };
    struct { char igi2_o2[28]; _BYTE v21[40]; };
    char igi2_extent[80];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct RenderPrimitive_s *v2; // edx
  int v3; // eax
  int v4; // ebp
  int *v5; // eax
  int v6; // esi
  int v7; // eax
  int v8; // esi
  int v9; // ebp
  struct HazingDynCubeObj_t **v10; // edi
  int LogZ; // eax
  struct RenderPrimitive_s *v12; // eax
  struct QTask_s *ptHead; // ebx
  int v14; // ecx
  int v15; // edx
  struct QTask_s *v16; // eax
  void (__cdecl *pfHandler)(int, _BYTE *); // eax
  int v18; // edx

  v2 = (struct RenderPrimitive_s *)Primitive_ptNextFreePrimitive;
  Primitive_ptNextFreePrimitive = (char *)Primitive_ptNextFreePrimitive + 48;
  if ( (char *)Primitive_ptNextFreePrimitive - Primitive_asPrimitive[0] > (char *)Primitive_nMaxPrimitiveUsage )
  {
    Primitive_nMaxPrimitiveUsage = (unsigned int)Primitive_ptNextFreePrimitive - Primitive_asPrimitive[0];
    if ( (char *)Primitive_ptNextFreePrimitive - Primitive_asPrimitive[0] > (char *)dword_6B9E3C )
      v2 = nullptr;
  }
  v2->ePrimType = Afterburner_nPrimType;
  v3 = Lightsource_nLightDataBufferPos;
  v4 = Lightsource_nLightDataStackPos;
  v2[1].ptNext = (struct RenderPrimitive_s *)ptQTask;
  v5 = (int *)(4 * v3 + 140666816);
  *(float *)&v2[3].ptNext = *(float *)&ptQTask[8].tQTaskChildren.ptHead * 255.0;
  *(float *)&v2[3].ePrimType = *(float *)&ptQTask[8].tQTaskChildren.ptHead * 255.0;
  v2[3].vZ = *(float *)&ptQTask[8].tQTaskChildren.ptHead * 255.0;
  qmemcpy(v5, Lightsource_anLightDataStack, 4 * v4);
  v6 = Lightsource_nLightDataBufferPos;
  v2[2].ptNext = (struct RenderPrimitive_s *)v4;
  LODWORD(v2[1].vZ) = v5;
  v7 = Hazinglayers_iHazingStack;
  v8 = v4 + v6;
  v9 = Hazinglayers_iHazingBuffer;
  Lightsource_nLightDataBufferPos = v8;
  v10 = (struct HazingDynCubeObj_t **)(4 * Hazinglayers_iHazingBuffer + 129834072);
  LODWORD(v2[2].vZ) = v10;
  qmemcpy(v10, Hazinglayers_aptHazingStack, 4 * v7);
  v2[2].ePrimType = v7;
  Hazinglayers_iHazingBuffer = v7 + v9;
  igi2_frame.vZ = TransContext_tActiveTransContext.tMatrix.tZ.vZ
     * (*(double *)&ptQTask[1].tQTaskChildren.ptTail - TransContext_tActiveTransContext.tPos.vZ)
     + TransContext_tActiveTransContext.tMatrix.tZ.vY
     * (*(double *)&ptQTask[1].tQTaskChildren.ptHead - TransContext_tActiveTransContext.tPos.vY)
     + TransContext_tActiveTransContext.tMatrix.tZ.vX
     * (*(double *)&ptQTask[1].ptNext - TransContext_tActiveTransContext.tPos.vX);
  if ( Viewport_GetLogZ(igi2_frame.vZ) >= 1 )
    LogZ = Viewport_GetLogZ(igi2_frame.vZ);
  else
    LogZ = 1;
  v12 = &RenderContext_tActiveRenderContext.ptRenderPrimitive_[LogZ];
  v2->ptNext = v12->ptNext;
  v12->ptNext = v2;
  qmemcpy(igi2_frame.v20, &ptQTask[1], sizeof(igi2_frame.v20));
  ptHead = ptQTask->tQTaskChildren.ptHead;
  qmemcpy(igi2_frame.v21, &ptQTask[3].ptPrev, sizeof(igi2_frame.v21));
  if ( ptHead->ptNext )
  {
    v14 = (int)ptHead;
    if ( ptHead )
    {
      v15 = QTask_nProtectedQTaskStackOffset;
      do
      {
        if ( *(_DWORD *)v14 )
          v16 = **(_DWORD **)v14 != 0 ? *(struct QTask_s **)v14 : nullptr;
        else
          v16 = nullptr;
        QTask_atProtectedQTaskStack[v15].ptQTask = v16;
        pfHandler = (void (__cdecl *)(int, _BYTE *))QTask_aatQTaskFinalEvent[MagicObj_eMagicObjEnterEvent][*(unsigned __int16 *)(v14 + 36)].pfHandler;
        v18 = v15 + 1;
        QTask_nProtectedQTaskStackOffset = v18;
        if ( pfHandler )
        {
          pfHandler(v14, igi2_frame.v20);
          v18 = QTask_nProtectedQTaskStackOffset;
        }
        v14 = dword_849C7DC[v18];
        v15 = v18 - 1;
        QTask_nProtectedQTaskStackOffset = v15;
      }
      while ( v14 );
    }
  }
}

// source: j/0/vehicles/afterburner.c:340  [size]
void __cdecl Afterburner_DrawHandler(void *pxPrimitive)
{
  ;
}

// source: j/0/vehicles/afterburner.c:373  [anchor-caller]
void __cdecl Afterburner_Open()
{
  int v0; // eax
  unsigned __int16 v1; // si
  _DWORD *v2; // esi
  _DWORD pxContext[3]; // [esp+8h] [ebp-Ch] BYREF

  Afterburner_eQTaskType = QTask_NewQTaskType("Afterburner", 336, RigidMagicObj_eQTaskType, 0, 0);
  v0 = 0;
  while ( RenderMode_atRenderModeMethod[v0].isAllocated )
  {
    if ( ++v0 >= 128 )
    {
      LDebug_Error("RenderMode: Failed to create new method '%s'", "AfterburnerPrimitive");
      abort();
    }
  }
  RenderMode_atRenderModeMethod[v0].zName = "AfterburnerPrimitive";
  RenderMode_atRenderModeMethod[v0].isAllocated = 1;
  Afterburner_nPrimType = v0;
  pxContext[0] = v0;
  pxContext[1] = Afterburner_DrawHandler;
  RenderMode_EnumerateRenderModes(
    (void (__cdecl *)(struct RenderModeEnumerateContext_s *, void *))Primitive_SetPrimitiveDrawCallback,
    pxContext);
  v1 = Afterburner_eQTaskType;
  QTask_LinkQTaskEventHandlerFn(Afterburner_eQTaskType, 0, Afterburner_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 1, Afterburner_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 2, Afterburner_DeleteHandler);
  QTask_LinkQTaskEventHandlerFn(v1, MagicObj_eUpdateMagicObjEvent, Afterburner_UpdateMagicObjHandler);
  QTask_LinkQTaskEventHandlerFn(v1, 5, Afterburner_EnterHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, Screen_eDrawQTaskEvent, nullptr);
  QTask_LinkQTaskEventHandlerFn(v1, MagicObj_eMagicObjEnterEvent, nullptr);
  Symbol_Register(
    "TASKTYPE_AFTERBURNER",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)v1,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  v2 = Mem_AllocFn(18444, 4);
  v2[1] = 0;
  *v2 = 0;
  v2[4610] = "TASKTYPE_AFTERBURNER";
  Wildcard_CreateNFA("TASKTYPE_AFTERBURNER", v2 + 2, (char *)v2 + 10248);
  List_AddTail(v2, (int)&MagicObjConfig_tTaskTypeEnumList);
}

// source: j/0/vehicles/afterburner.c:412  [size]
void __cdecl Afterburner_Close()
{
  QTask_DeleteQTaskType(Afterburner_eQTaskType);
  RenderMode_atRenderModeMethod[Afterburner_nPrimType].isAllocated = 0;
}

// source: j/0/vehicles/afterburner.c:429  [size]
unsigned __int16 __cdecl Afterburner_GetQTaskType()
{
  return Afterburner_eQTaskType;
}
