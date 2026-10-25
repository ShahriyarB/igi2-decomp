/* h/2/rotateattachment.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: h/2/rotateattachment.c:74  [anchor-mhash]
struct Result_s *__cdecl RotateAttachment_SetRotationSpeedTarget(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  #pragma pack(push, 1)
  union
  {
    struct { float vTargetSpeed; };
    struct { char igi2_o1[4]; int nTicks; };
    struct { char igi2_o2[8]; struct Result_s Rs; };
    char igi2_extent[32];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct RotateAttachment_s *v3; // ebp
  unsigned int v4; // edi
  int v5; // ebx

  v3 = RotateAttachment_ptRotateAttachment;
  if ( RotateAttachment_ptRotateAttachment )
  {
    if ( ptArgList->nArguments == 3 )
    {
      v4 = Script_EvalArgInt(ptArgList, 0);
      v5 = Script_EvalArgInt(ptArgList, 1);
      igi2_frame.nTicks = v5;
      igi2_frame.vTargetSpeed = Script_EvalArgFloat(ptArgList, 2);
      if ( v4 <= 2 )
      {
        if ( v5 < 1 )
          igi2_frame.nTicks = 1;
        v3->avRotation[v4] = igi2_frame.vTargetSpeed;
        v3->avAcceleration[v4] = (igi2_frame.vTargetSpeed - v3->avActualRotation[v4]) / (double)igi2_frame.nTicks;
      }
    }
  }
  igi2_frame.Rs.nResult = 0;
  igi2_frame.Rs.vResult = 0.0;
  igi2_frame.Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &igi2_frame.Rs, sizeof(struct Result_s));
  return retstr;
}

// source: h/2/rotateattachment.c:111  [size]
void __cdecl RotateAttachment_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ptQTask[1].tQTaskChildren.ptHead = nullptr;
  ptQTask[1].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[1].tQTaskChildren.ptTail = nullptr;
  ptQTask[1].ptParent = nullptr;
  *(_DWORD *)&ptQTask[1].eQTaskType = 0;
  ptQTask[2].ptNext = nullptr;
  ptQTask[1].tQTaskRefList.ptHead = nullptr;
  ptQTask[1].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[1].tQTaskRefList.ptTail = nullptr;
  ptQTask[1].ptNext = nullptr;
  ptQTask[1].ptPrev = nullptr;
  LOBYTE(ptQTask[2].tQTaskChildren.ptHead) = 0;
  ptQTask[2].ptPrev = nullptr;
}

// source: h/2/rotateattachment.c:139  [size]
void __cdecl RotateAttachment_DeleteHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptNext; // eax
  struct QTask_s *ptPrev; // eax

  ptNext = ptQTask[1].ptNext;
  if ( ptNext )
  {
    QReference_Delete((struct QReference_s *)ptNext, &QTask_tQTaskRefPool);
    ptQTask[1].ptNext = nullptr;
  }
  ptPrev = ptQTask[1].ptPrev;
  if ( ptPrev )
  {
    QReference_Delete((struct QReference_s *)ptPrev, &QTask_tQTaskRefPool);
    ptQTask[1].ptPrev = nullptr;
  }
}

// source: h/2/rotateattachment.c:156  [anchor-mhash]
void __cdecl RotateAttachment_RunHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct real32x9_t Real32x9_Normalize_tTemp; };
    struct { char igi2_o1[40]; struct real32x9_t tOrientation; };
    struct { char igi2_o2[80]; struct real32x9_t Real32x9_Multiply_tTemp; };
    char igi2_extent[120];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *ptHead; // eax
  bool v2; // zf
  int v3; // edx
  struct QTask_s *v4; // ecx
  int eQTaskType; // ecx
  struct QTask_s *ptNext; // eax
  float *v7; // ebx
  double v8; // st7
  double v9; // st7
  float *v10; // ecx
  double v11; // st7
  double v12; // st7
  double v13; // st7
  double v14; // st7
  double v15; // st7
  double v16; // st6
  double v17; // st5
  long double v18; // st1
  long double v19; // st6
  long double v20; // st7
  int v21; // edx
  void (__cdecl *pfHandler)(float *); // eax
  struct real32x3_t tTemp_; // 0:^1C.12
  struct real32x3_t v31; // 0:^30.12

  ptHead = ptQTask->tQTaskChildren.ptHead;
  v2 = ptHead->ptNext == nullptr;
  RotateAttachment_ptRotateAttachment = (struct RotateAttachment_s *)ptQTask;
  if ( !v2 && ptHead )
  {
    v3 = QTask_nProtectedQTaskStackOffset;
    do
    {
      if ( ptHead->ptNext )
        v4 = ptHead->ptNext->ptNext != nullptr ? ptHead->ptNext : nullptr;
      else
        v4 = nullptr;
      QTask_atProtectedQTaskStack[v3].ptQTask = v4;
      eQTaskType = ptHead->eQTaskType;
      QTask_nProtectedQTaskStackOffset = v3 + 1;
      ((void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[1][eQTaskType].pfHandler)(ptHead);
      ptHead = (struct QTask_s *)dword_849C7DC[QTask_nProtectedQTaskStackOffset];
      v3 = --QTask_nProtectedQTaskStackOffset;
    }
    while ( ptHead );
  }
  ptNext = ptQTask[1].ptNext;
  RotateAttachment_ptRotateAttachment = nullptr;
  if ( ptNext )
  {
    v7 = (float *)ptNext->tQTaskChildren.ptHead;
    if ( v7 )
    {
      v8 = *(float *)&ptQTask[1].tQTaskChildren.ptHead + *(float *)&ptQTask[1].ptParent;
      if ( *(float *)&ptQTask[1].tQTaskChildren.ptHead >= 0.0 )
      {
        if ( v8 <= *(float *)&ptQTask[1].tQTaskRefList.ptHead )
          goto LABEL_15;
      }
      else if ( v8 >= *(float *)&ptQTask[1].tQTaskRefList.ptHead )
      {
        goto LABEL_15;
      }
      v8 = *(float *)&ptQTask[1].tQTaskRefList.ptHead;
LABEL_15:
      *(float *)&ptQTask[1].ptParent = v8;
      v9 = *(float *)&ptQTask[1].tQTaskChildren.ptMiddle + *(float *)&ptQTask[1].eQTaskType;
      if ( *(float *)&ptQTask[1].tQTaskChildren.ptMiddle >= 0.0 )
      {
        if ( v9 <= *(float *)&ptQTask[1].tQTaskRefList.ptMiddle )
          goto LABEL_20;
      }
      else if ( v9 >= *(float *)&ptQTask[1].tQTaskRefList.ptMiddle )
      {
        goto LABEL_20;
      }
      v9 = *(float *)&ptQTask[1].tQTaskRefList.ptMiddle;
LABEL_20:
      *(float *)&ptQTask[1].eQTaskType = v9;
      v10 = (float *)&ptQTask[2];
      v11 = *(float *)&ptQTask[1].tQTaskChildren.ptTail + *(float *)&ptQTask[2].ptNext;
      if ( *(float *)&ptQTask[1].tQTaskChildren.ptTail >= 0.0 )
      {
        if ( v11 <= *(float *)&ptQTask[1].tQTaskRefList.ptTail )
          goto LABEL_25;
      }
      else if ( v11 >= *(float *)&ptQTask[1].tQTaskRefList.ptTail )
      {
        goto LABEL_25;
      }
      v11 = *(float *)&ptQTask[1].tQTaskRefList.ptTail;
LABEL_25:
      *v10 = v11;
      Real32x9_Create(&igi2_frame.tOrientation, *(float *)&ptQTask[1].ptParent, *(float *)&ptQTask[1].eQTaskType, *v10);
      igi2_frame.Real32x9_Multiply_tTemp.tX.vX = igi2_frame.tOrientation.tX.vX * v7[41]
                                    + igi2_frame.tOrientation.tZ.vX * v7[43]
                                    + igi2_frame.tOrientation.tY.vX * v7[42];
      v12 = igi2_frame.tOrientation.tX.vY * v7[41];
      igi2_frame.Real32x9_Normalize_tTemp.tX.vX = igi2_frame.Real32x9_Multiply_tTemp.tX.vX;
      igi2_frame.Real32x9_Multiply_tTemp.tX.vY = v12 + igi2_frame.tOrientation.tZ.vY * v7[43] + igi2_frame.tOrientation.tY.vY * v7[42];
      v13 = igi2_frame.tOrientation.tX.vZ * v7[41];
      igi2_frame.Real32x9_Normalize_tTemp.tX.vY = igi2_frame.Real32x9_Multiply_tTemp.tX.vY;
      igi2_frame.Real32x9_Multiply_tTemp.tX.vZ = v13 + igi2_frame.tOrientation.tZ.vZ * v7[43] + igi2_frame.tOrientation.tY.vZ * v7[42];
      v14 = igi2_frame.tOrientation.tX.vX * v7[47];
      igi2_frame.Real32x9_Normalize_tTemp.tX.vZ = igi2_frame.Real32x9_Multiply_tTemp.tX.vZ;
      v15 = v14 + igi2_frame.tOrientation.tZ.vX * v7[49] + igi2_frame.tOrientation.tY.vX * v7[48];
      v16 = igi2_frame.tOrientation.tX.vY * v7[47] + igi2_frame.tOrientation.tZ.vY * v7[49] + igi2_frame.tOrientation.tY.vY * v7[48];
      v17 = igi2_frame.tOrientation.tX.vZ * v7[47] + igi2_frame.tOrientation.tZ.vZ * v7[49] + igi2_frame.tOrientation.tY.vZ * v7[48];
      if ( igi2_frame.Real32x9_Multiply_tTemp.tX.vX != 0.0
        || igi2_frame.Real32x9_Multiply_tTemp.tX.vY != 0.0
        || igi2_frame.Real32x9_Multiply_tTemp.tX.vZ != 0.0 )
      {
        v18 = sqrt(
                igi2_frame.Real32x9_Multiply_tTemp.tX.vX * igi2_frame.Real32x9_Multiply_tTemp.tX.vX
              + igi2_frame.Real32x9_Multiply_tTemp.tX.vY * igi2_frame.Real32x9_Multiply_tTemp.tX.vY
              + igi2_frame.Real32x9_Multiply_tTemp.tX.vZ * igi2_frame.Real32x9_Multiply_tTemp.tX.vZ);
        igi2_frame.Real32x9_Normalize_tTemp.tX.vX = igi2_frame.Real32x9_Multiply_tTemp.tX.vX * (1.0 / v18);
        igi2_frame.Real32x9_Normalize_tTemp.tX.vY = igi2_frame.Real32x9_Normalize_tTemp.tX.vY * (1.0 / v18);
        igi2_frame.Real32x9_Normalize_tTemp.tX.vZ = igi2_frame.Real32x9_Normalize_tTemp.tX.vZ * (1.0 / v18);
      }
      tTemp_.vX = v16 * igi2_frame.Real32x9_Multiply_tTemp.tX.vZ - v17 * igi2_frame.Real32x9_Multiply_tTemp.tX.vY;
      tTemp_.vY = -(v15 * igi2_frame.Real32x9_Multiply_tTemp.tX.vZ - v17 * igi2_frame.Real32x9_Multiply_tTemp.tX.vX);
      tTemp_.vZ = v15 * igi2_frame.Real32x9_Multiply_tTemp.tX.vY - v16 * igi2_frame.Real32x9_Multiply_tTemp.tX.vX;
      igi2_frame.Real32x9_Normalize_tTemp.tY = tTemp_;
      v31.vX = tTemp_.vZ * igi2_frame.Real32x9_Normalize_tTemp.tX.vY - tTemp_.vY * igi2_frame.Real32x9_Normalize_tTemp.tX.vZ;
      v31.vY = -(tTemp_.vZ * igi2_frame.Real32x9_Normalize_tTemp.tX.vX - tTemp_.vX * igi2_frame.Real32x9_Normalize_tTemp.tX.vZ);
      v31.vZ = tTemp_.vY * igi2_frame.Real32x9_Normalize_tTemp.tX.vX - tTemp_.vX * igi2_frame.Real32x9_Normalize_tTemp.tX.vY;
      igi2_frame.Real32x9_Normalize_tTemp.tZ = v31;
      if ( tTemp_.vX != 0.0 || tTemp_.vY != 0.0 || tTemp_.vZ != 0.0 )
      {
        v19 = 1.0 / sqrt(tTemp_.vZ * tTemp_.vZ + tTemp_.vY * tTemp_.vY + tTemp_.vX * tTemp_.vX);
        igi2_frame.Real32x9_Normalize_tTemp.tY.vX = v19 * tTemp_.vX;
        igi2_frame.Real32x9_Normalize_tTemp.tY.vY = igi2_frame.Real32x9_Normalize_tTemp.tY.vY * v19;
        igi2_frame.Real32x9_Normalize_tTemp.tY.vZ = igi2_frame.Real32x9_Normalize_tTemp.tY.vZ * v19;
      }
      if ( v31.vX != 0.0 || v31.vY != 0.0 || v31.vZ != 0.0 )
      {
        v20 = 1.0 / sqrt(v31.vX * v31.vX + v31.vY * v31.vY + v31.vZ * v31.vZ);
        igi2_frame.Real32x9_Normalize_tTemp.tZ.vX = v31.vX * v20;
        igi2_frame.Real32x9_Normalize_tTemp.tZ.vY = igi2_frame.Real32x9_Normalize_tTemp.tZ.vY * v20;
        igi2_frame.Real32x9_Normalize_tTemp.tZ.vZ = igi2_frame.Real32x9_Normalize_tTemp.tZ.vZ * v20;
      }
      qmemcpy(&igi2_frame.tOrientation, &igi2_frame.Real32x9_Normalize_tTemp, sizeof(igi2_frame.tOrientation));
      v21 = Attach_eUpdateAttachmentEvent;
      igi2_frame.tOrientation.nOps = 0;
      qmemcpy(v7 + 41, &igi2_frame.tOrientation, 0x28u);
      pfHandler = (void (__cdecl *)(float *))QTask_aatQTaskFinalEvent[v21][*((unsigned __int16 *)v7 + 18)].pfHandler;
      if ( pfHandler )
        pfHandler(v7);
    }
  }
}

// source: h/2/rotateattachment.c:197  [anchor-mhash]
void __cdecl RotateAttachment_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *ptNext; // eax
  struct QTask_s *ptPrev; // eax
  struct QTask_s *ptTail; // edx
  struct QReference_s *ptMiddle; // ecx
  struct QTask_s *v7; // edx
  unsigned __int16 v8; // cx
  struct QTask_s *v9; // eax
  struct QTask_s *ptHead; // eax
  struct QTask_s *v11; // ebp
  int v12; // eax
  struct QTask_s *v13; // eax
  struct QTask_s *ptParent; // [esp+4h] [ebp-4h]
  struct QTask_s *ptQTaska = *(struct QTask_s * *)&ptQTask; // [esp+Ch] [ebp+4h] ARGSLOT

  ptNext = ptQTask[1].ptNext;
  if ( ptNext )
  {
    QReference_Delete((struct QReference_s *)ptNext, &QTask_tQTaskRefPool);
    ptQTask[1].ptNext = nullptr;
  }
  ptPrev = ptQTask[1].ptPrev;
  if ( ptPrev )
  {
    QReference_Delete((struct QReference_s *)ptPrev, &QTask_tQTaskRefPool);
    ptQTask[1].ptPrev = nullptr;
  }
  ptTail = (struct QTask_s *)ptQTask[1].tQTaskRefList.ptTail;
  ptMiddle = ptQTask[1].tQTaskRefList.ptMiddle;
  ptQTask[1].ptParent = (struct QTask_s *)ptQTask[1].tQTaskRefList.ptHead;
  *(_DWORD *)&ptQTask[1].eQTaskType = ptMiddle;
  ptQTask[2].ptNext = ptTail;
  v7 = ptQTask->ptParent;
  ptParent = v7;
  if ( v7 )
  {
    v8 = RigidDynCubeObj_eQTaskType;
    while ( QTask_IsQTaskTypeDerived(v7->eQTaskType, v8) == false )
    {
      ptParent = v7->ptParent;
      if ( !ptParent )
        return;
      v7 = v7->ptParent;
    }
    v9 = v7[3].ptNext;
    if ( v9 )
    {
      ptHead = v9->tQTaskChildren.ptHead;
      ptQTaska = ptQTask[2].ptPrev;
      if ( ptHead->ptNext )
      {
        v11 = ptHead;
        if ( ptHead )
        {
          while ( 1 )
          {
            if ( QTask_IsQTaskTypeDerived(v11->eQTaskType, RigidMagicObj_eQTaskType) )
            {
              v12 = *(_DWORD *)&v11[2].eQTaskType;
              if ( v12 )
              {
                if ( !strcmp((char *)(v12 + 20), (char *)&ptQTask[2].tQTaskChildren) )
                {
                  if ( !ptQTaska )
                  {
                    ptQTask[1].ptNext = (struct QTask_s *)QTask_NewQTaskRef(v11);
                    ptQTask[1].ptPrev = (struct QTask_s *)QTask_NewQTaskRef(ptParent);
                    return;
                  }
                  ptQTaska = (struct QTask_s *)((char *)ptQTaska - 1);
                }
              }
            }
            v13 = v11->ptNext;
            if ( v11->ptNext )
            {
              if ( v13->ptNext )
              {
                v11 = v11->ptNext;
                if ( v13 )
                  continue;
              }
            }
            return;
          }
        }
      }
    }
  }
}

// source: h/2/rotateattachment.c:267  [size]
void __cdecl RotateAttachment_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = RotateAttachment_ptParameterList;
}

// source: h/2/rotateattachment.c:285  [size]
unsigned __int16 __cdecl RotateAttachment_GetQTaskType()
{
  return RotateAttachment_eQTaskType;
}

// source: h/2/rotateattachment.c:298  [anchor-hash]
void __cdecl RotateAttachment_Open()
{
  unsigned __int16 BaseQTaskType; // ax
  unsigned __int16 v1; // si
  struct ParameterList_s *v2; // eax
  int v3; // [esp-1Ch] [ebp-28h]

  BaseQTaskType = QTask_GetBaseQTaskType();
  v1 = QTask_NewQTaskType("RotateAttachment", 104, BaseQTaskType, 0, 0);
  RotateAttachment_eQTaskType = v1;
  QTask_LinkQTaskEventHandlerFn(v1, 0, (void (__cdecl *)(struct QTask_s *, void *))RotateAttachment_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 2, RotateAttachment_DeleteHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 1, RotateAttachment_RunHandler);
  QTask_LinkQTaskEventHandlerFn(
    v1,
    ParameterList_eUpdateInternalDataQTaskEvent,
    RotateAttachment_UpdateInternalDataHandler);
  QTask_LinkQTaskEventHandlerFn(
    v1,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))RotateAttachment_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(
    v1,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveHandler);
  v2 = (struct ParameterList_s *)Mem_AllocFn(112, 4);
  v3 = Level_eParameterTypeReal32;
  v2->nParameters = 0;
  v2->nMaxParameters = 5;
  v2->ptParameterListItem = (struct ParameterListItem_s *)&v2[1];
  RotateAttachment_ptParameterList = v2;
  ParameterList_AddParameterMinMax(v2, 0x3Cu, v3, "AlphaRotationSpeed", 7u, -0.7853981852531433, 0.7853981852531433);
  ParameterList_AddParameterMinMax(
    RotateAttachment_ptParameterList,
    0x40u,
    Level_eParameterTypeReal32,
    "BetaRotationSpeed",
    7u,
    -0.7853981852531433,
    0.7853981852531433);
  ParameterList_AddParameterMinMax(
    RotateAttachment_ptParameterList,
    0x44u,
    Level_eParameterTypeReal32,
    "GammaRotationSpeed",
    7u,
    -0.7853981852531433,
    0.7853981852531433);
  ParameterList_AddParameter(
    RotateAttachment_ptParameterList,
    0x58u,
    Level_eParameterTypeString16,
    "Attachment model",
    7u,
    nullptr);
  ParameterList_AddParameterMinMax(
    RotateAttachment_ptParameterList,
    0x54u,
    Level_eParameterTypeInt32,
    "Attachment model instance",
    7u,
    0.0,
    10.0);
  Symbol_Register(
    "RotateAttachment_SetTargetSpeed",
    RotateAttachment_SetRotationSpeedTarget,
    nullptr,
    -1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
}

// source: h/2/rotateattachment.c:333  [anchor-strings]
void __cdecl RotateAttachment_Close()
{
  int v0; // esi

  Symbol_Remove("RotateAttachment_SetTargetSpeed");
  if ( RotateAttachment_ptParameterList )
  {
    v0 = *(_DWORD *)((unsigned int)&RotateAttachment_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
  QTask_DeleteQTaskType(RotateAttachment_eQTaskType);
}
