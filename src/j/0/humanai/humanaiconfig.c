/* j/0/humanai/humanaiconfig.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/humanai/humanaiconfig.c:78  [size]
void __cdecl HumanAIConfig_SetConfigItemTaskNode(struct HumanAIConfigItem_t *ptHumanAIConfigItem)
{
  ;
}

// source: j/0/humanai/humanaiconfig.c:98  [anchor-mhash]
void __cdecl HumanAIConfig_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  LOBYTE(ptQTask[1].ptNext) = 0;
  memset(&ptQTask[1].ptPrev, 0, 0x18u);
  ptQTask[1].tQTaskRefList.ptTail = nullptr;
  ptQTask[1].ptParent = nullptr;
  *(_DWORD *)&ptQTask[1].eQTaskType = 0;
}

// source: j/0/humanai/humanaiconfig.c:116  [size]
void __cdecl HumanAIConfig_DeleteHandler(struct QTask_s *ptQTask)
{
  ;
}

// source: j/0/humanai/humanaiconfig.c:128  [size]
void __cdecl HumanAIConfig_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = HumanAIConfig_ptParameterList;
}

// source: j/0/humanai/humanaiconfig.c:144  [size]
void __cdecl HumanAIConfig_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ;
}

// source: j/0/humanai/humanaiconfig.c:165  [anchor-mhash]
void __cdecl HumanAIConfigItem_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  char ptPrev; // cl
  double v3; // st7
  double v4; // st7
  double v5; // st7
  double v6; // st7
  double v7; // st7
  double v8; // st7
  double v9; // st7
  double v10; // st7
  double v11; // st7
  double v12; // st7
  double v13; // st7
  double v14; // st7
  double v15; // st7
  double v16; // st7
  double v17; // st7
  double v18; // st7
  double v19; // st7
  double v20; // st7
  double v21; // st7
  double v22; // st7
  double v23; // st7
  double v24; // st7
  double v25; // st7
  double v26; // st7
  double v27; // st7
  double v28; // st7
  double v29; // st7
  double v30; // st7
  double v31; // st7
  double v32; // st7
  double v33; // st7
  double v34; // st7
  double v35; // st7

  if ( pxContext )
  {
    strcpy((char *)&ptQTask[1].ptPrev + 1, *(char **)pxContext);
    LOBYTE(ptQTask[1].ptPrev) = *((_BYTE *)pxContext + 4);
  }
  else
  {
    BYTE1(ptQTask[1].ptPrev) = 0;
    LOBYTE(ptQTask[1].ptPrev) = 0;
  }
  ptPrev = (char)ptQTask[1].ptPrev;
  ptQTask[1].ptNext = nullptr;
  if ( ptPrev )
    v3 = 5.0;
  else
    v3 = 1.0;
  *(float *)&ptQTask[14].ptNext = v3;
  if ( ptPrev )
    v4 = 5.0;
  else
    v4 = 1.0;
  *(float *)&ptQTask[14].ptPrev = v4;
  if ( ptPrev )
    v5 = 0.10000000149011612;
  else
    v5 = 1.0;
  *(float *)&ptQTask[14].tQTaskChildren.ptHead = v5;
  if ( ptPrev )
    v6 = 50.0;
  else
    v6 = 1.0;
  *(float *)&ptQTask[14].tQTaskRefList.ptHead = v6;
  if ( ptPrev )
    v7 = 10.0;
  else
    v7 = 1.0;
  *(float *)&ptQTask[14].tQTaskRefList.ptMiddle = v7;
  if ( ptPrev )
    v8 = 5.0;
  else
    v8 = 1.0;
  *(float *)&ptQTask[14].tQTaskRefList.ptTail = v8;
  if ( ptPrev )
    v9 = 50.0;
  else
    v9 = 1.0;
  *(float *)&ptQTask[14].ptParent = v9;
  if ( ptPrev )
    v10 = 100.0;
  else
    v10 = 1.0;
  *(float *)&ptQTask[14].eQTaskType = v10;
  ptQTask[15].ptNext = nullptr;
  ptQTask[15].ptPrev = nullptr;
  ptQTask[17].tQTaskRefList.ptHead = (struct QReference_s *)1065353216;
  ptQTask[15].ptParent = (struct QTask_s *)1065353216;
  if ( ptPrev )
    v11 = 30.0;
  else
    v11 = 1.0;
  *(float *)&ptQTask[16].ptPrev = v11;
  if ( ptPrev )
    v12 = 100.0;
  else
    v12 = 1.0;
  *(float *)&ptQTask[16].tQTaskChildren.ptHead = v12;
  if ( ptPrev )
    v13 = 90.0;
  else
    v13 = 1.0;
  *(float *)&ptQTask[16].tQTaskChildren.ptMiddle = v13;
  if ( ptPrev )
    v14 = 10.0;
  else
    v14 = 1.0;
  *(float *)&ptQTask[16].tQTaskChildren.ptTail = v14;
  if ( ptPrev )
    v15 = 30.0;
  else
    v15 = 1.0;
  *(float *)&ptQTask[14].tQTaskChildren.ptTail = v15;
  if ( ptPrev )
    v16 = 4.0;
  else
    v16 = 1.0;
  *(float *)&ptQTask[15].tQTaskRefList.ptMiddle = v16;
  if ( ptPrev )
    v17 = 50.0;
  else
    v17 = 1.0;
  *(float *)&ptQTask[15].tQTaskRefList.ptTail = v17;
  if ( ptPrev )
    v18 = 50.0;
  else
    v18 = 1.0;
  *(float *)&ptQTask[15].tQTaskRefList.ptHead = v18;
  if ( ptPrev )
    v19 = 100.0;
  else
    v19 = 1.0;
  *(float *)&ptQTask[15].eQTaskType = v19;
  if ( ptPrev )
    v20 = 10.0;
  else
    v20 = 1.0;
  *(float *)&ptQTask[16].ptNext = v20;
  if ( ptPrev )
    v21 = 30.0;
  else
    v21 = 1.0;
  *(float *)&ptQTask[16].eQTaskType = v21;
  if ( ptPrev )
    v22 = 20.0;
  else
    v22 = 1.0;
  *(float *)&ptQTask[16].tQTaskRefList.ptHead = v22;
  if ( ptPrev )
    v23 = 40.0;
  else
    v23 = 1.0;
  *(float *)&ptQTask[16].tQTaskRefList.ptMiddle = v23;
  if ( ptPrev )
    v24 = 90.0;
  else
    v24 = 1.0;
  *(float *)&ptQTask[16].tQTaskRefList.ptTail = v24;
  if ( ptPrev )
    v25 = 5.0;
  else
    v25 = 1.0;
  *(float *)&ptQTask[16].ptParent = v25;
  if ( ptPrev )
    v26 = 10.0;
  else
    v26 = 1.0;
  *(float *)&ptQTask[17].tQTaskChildren.ptTail = v26;
  if ( ptPrev )
    v27 = 40.0;
  else
    v27 = 1.0;
  *(float *)&ptQTask[17].ptNext = v27;
  if ( ptPrev )
    v28 = 60.0;
  else
    v28 = 1.0;
  *(float *)&ptQTask[17].ptPrev = v28;
  if ( ptPrev )
    v29 = 90.0;
  else
    v29 = 1.0;
  *(float *)&ptQTask[17].tQTaskChildren.ptHead = v29;
  if ( ptPrev )
    v30 = 10.0;
  else
    v30 = 1.0;
  *(float *)&ptQTask[17].tQTaskChildren.ptMiddle = v30;
  if ( ptPrev )
    v31 = 0.30000001192092896;
  else
    v31 = 1.0;
  *(float *)&ptQTask[15].tQTaskChildren.ptHead = v31;
  if ( ptPrev )
    v32 = 10.0;
  else
    v32 = 1.0;
  *(float *)&ptQTask[14].tQTaskChildren.ptMiddle = v32;
  if ( ptPrev )
    v33 = 100.0;
  else
    v33 = 1.0;
  *(float *)&ptQTask[15].tQTaskChildren.ptTail = v33;
  if ( ptPrev )
    v34 = 30.0;
  else
    v34 = 1.0;
  *(float *)&ptQTask[15].tQTaskChildren.ptMiddle = v34;
  if ( ptPrev )
    v35 = 2.0;
  else
    v35 = 0.5;
  *(float *)&ptQTask[17].tQTaskRefList.ptMiddle = v35;
  memset32(&ptQTask[17].tQTaskRefList.ptTail, 1065353216, 0x11u);
  BYTE1(ptQTask[7].tQTaskRefList.ptHead) = 0;
}

// source: j/0/humanai/humanaiconfig.c:250  [size]
void __cdecl HumanAIConfigItem_RunHandler(struct QTask_s *ptQTask)
{
  ;
}

// source: j/0/humanai/humanaiconfig.c:262  [size]
void __cdecl HumanAIConfigItem_DeleteHandler(struct QTask_s *ptQTask)
{
  ;
}

// source: j/0/humanai/humanaiconfig.c:274  [size]
void __cdecl HumanAIConfigItem_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = HumanAIConfigItem_ptParameterList;
}

// source: j/0/humanai/humanaiconfig.c:295  [anchor-caller]
void __cdecl HumanAIConfigItem_UpdateAccuracyDisplay(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { float vAccuracyMedRange; };
    struct { char igi2_o1[4]; float vAccuracyMaxRange; };
    struct { char igi2_o2[16]; float vDistanceToCalcFor; };
    struct { char igi2_o3[32]; int iI; };
    struct { char igi2_o4[32]; float iIa; };
    struct { char igi2_o5[32]; __int64 iIb; };
    struct { char igi2_o6[40]; float vMaxAccuracyFactor; };
    struct { char igi2_o7[44]; float vMedAccuracyFactor; };
    struct { char igi2_o8[48]; char zText[256]; };
    char igi2_extent[304];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v1; // esi
  int v2; // ebp
  char *v3; // edi
  unsigned int v5; // eax
  struct QReferenceList_s *p_tQTaskRefList; // edi
  char v7; // cl

  if ( LOBYTE(ptQTask[1].ptPrev) )
  {
    igi2_frame.iIa = *(float *)&ptQTask[14].ptParent * 4096.0;
    igi2_frame.vMedAccuracyFactor = pow(
                           *(float *)&ptQTask[14].tQTaskRefList.ptMiddle / *(float *)&ptQTask[14].tQTaskRefList.ptHead,
                           1.0 / (igi2_frame.iIa - 1.0));
    igi2_frame.vMaxAccuracyFactor = pow(
                           *(float *)&ptQTask[14].tQTaskRefList.ptTail / *(float *)&ptQTask[14].tQTaskRefList.ptMiddle,
                           1.0 / (*(float *)&ptQTask[14].eQTaskType * 4096.0 - igi2_frame.iIa));
    v1 = 0;
    BYTE1(ptQTask[7].tQTaskRefList.ptHead) = 0;
    igi2_frame.iI = 0;
    do
    {
      igi2_frame.vDistanceToCalcFor = (double)igi2_frame.iI * 4096.0;
      igi2_frame.vAccuracyMaxRange = *(float *)&ptQTask[14].eQTaskType * 4096.0;
      igi2_frame.vAccuracyMedRange = *(float *)&ptQTask[14].ptParent * 4096.0;
      igi2_frame.iIb = (__int64)(HumanAIConfig_CalculateAccuracy(
                        *(float *)&ptQTask[14].tQTaskRefList.ptHead,
                        *(float *)&ptQTask[14].tQTaskRefList.ptMiddle,
                        igi2_frame.vAccuracyMedRange,
                        igi2_frame.vAccuracyMaxRange,
                        igi2_frame.vMedAccuracyFactor,
                        igi2_frame.vMaxAccuracyFactor,
                        igi2_frame.vDistanceToCalcFor)
                    + 0.5);
      sprintf(igi2_frame.zText, "%i%%", (_DWORD)igi2_frame.iIb);
      v2 = v1 + 20;
      if ( v1 + 20 <= 100 )
      {
        v3 = (char *)&igi2_frame.vMedAccuracyFactor + 3;
        while ( *++v3 )
          ;
        strcpy(v3, ", ");
      }
      v5 = strlen(igi2_frame.zText) + 1;
      p_tQTaskRefList = &ptQTask[7].tQTaskRefList;
      do
      {
        v7 = BYTE1(p_tQTaskRefList->ptHead);
        p_tQTaskRefList = (struct QReferenceList_s *)((char *)p_tQTaskRefList + 1);
      }
      while ( v7 );
      qmemcpy(p_tQTaskRefList, igi2_frame.zText, v5);
      v1 += 20;
      igi2_frame.iI = v2;
    }
    while ( v2 <= 100 );
  }
}

// source: j/0/humanai/humanaiconfig.c:355  [anchor-caller]
void __cdecl HumanAIConfigItem_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ptQTask[1].ptNext = (struct QTask_s *)Script_ParseLineInt32((char *)&ptQTask[1].ptPrev + 1);
  HumanAIConfigItem_UpdateAccuracyDisplay(ptQTask);
  HumanSoldier_InitDamagePartTable();
}

// source: j/0/humanai/humanaiconfig.c:386  [anchor-hash]
void __cdecl HumanAIConfig_Open()
{
  unsigned __int16 BaseQTaskType; // ax
  unsigned __int16 v1; // ax
  unsigned __int16 v2; // ax
  unsigned __int16 v3; // si
  struct ParameterList_s *v4; // eax
  int v5; // edx
  unsigned __int16 v6; // si
  struct ParameterList_s *v7; // eax
  int v8; // edx

  BaseQTaskType = QTask_GetBaseQTaskType();
  HumanAIConfig_eQTaskType = QTask_NewQTaskType("HumanAIConfig", 80, BaseQTaskType, 0, 0);
  v1 = QTask_GetBaseQTaskType();
  v2 = QTask_NewQTaskType("HumanAIConfigItem", 776, v1, 0, 0);
  v3 = HumanAIConfig_eQTaskType;
  HumanAIConfigItem_eQTaskType = v2;
  QTask_LinkQTaskEventHandlerFn(HumanAIConfig_eQTaskType, 0, HumanAIConfig_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v3, 2, (void (__cdecl *)(struct QTask_s *))HumanAIConfig_DeleteHandler);
  QTask_LinkQTaskEventHandlerFn(
    v3,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))HumanAIConfig_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(
    v3,
    ParameterList_eUpdateInternalDataQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))HumanAIConfig_UpdateInternalDataHandler);
  QTask_LinkQTaskEventHandlerFn(
    v3,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveHandler);
  v4 = (struct ParameterList_s *)Mem_AllocFn(32, 4);
  v5 = Level_eParameterTypePushButton;
  v4->ptParameterListItem = (struct ParameterListItem_s *)&v4[1];
  v4->nParameters = 0;
  v4->nMaxParameters = 1;
  HumanAIConfig_ptParameterList = v4;
  ParameterList_AddParameter(v4, 0x28u, v5, "Save all settings", 7u, nullptr);
  v6 = HumanAIConfigItem_eQTaskType;
  QTask_LinkQTaskEventHandlerFn(HumanAIConfigItem_eQTaskType, 0, HumanAIConfigItem_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v6, 1, (void (__cdecl *)(struct QTask_s *))HumanAIConfigItem_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v6, 2, (void (__cdecl *)(struct QTask_s *))HumanAIConfigItem_DeleteHandler);
  QTask_LinkQTaskEventHandlerFn(
    v6,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))HumanAIConfigItem_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(
    v6,
    ParameterList_eUpdateInternalDataQTaskEvent,
    HumanAIConfigItem_UpdateInternalDataHandler);
  QTask_LinkQTaskEventHandlerFn(
    v6,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveNoChildrenHandler);
  HumanAIConfig_DamageScaleLimitContext.vMin = 0.0;
  HumanAIConfig_DamageScaleLimitContext.vMax = 1.0;
  HumanAIConfig_ViewAngleLimitContext.vMin = 0.0;
  HumanAIConfig_ViewAngleLimitContext.vMax = 90.0;
  HumanAIConfig_ViewLengthLimitContext.vMin = 0.0;
  HumanAIConfig_ViewLengthLimitContext.vMax = 500.0;
  v7 = (struct ParameterList_s *)Mem_AllocFn(1112, 4);
  v8 = Level_eParameterTypeString256;
  v7->ptParameterListItem = (struct ParameterListItem_s *)&v7[1];
  v7->nParameters = 0;
  v7->nMaxParameters = 55;
  HumanAIConfigItem_ptParameterList = v7;
  ParameterList_AddParameter(v7, 0x2Du, v8, "AI Type", 3u, nullptr);
  ParameterList_AddParameter(
    HumanAIConfigItem_ptParameterList,
    0x2Cu,
    Level_eParameterTypebool8,
    "isBaseData",
    3u,
    nullptr);
  ParameterList_AddParameter(
    HumanAIConfigItem_ptParameterList,
    0x230u,
    Level_eParameterTypeReal32,
    "DangerTimeout[0..100]",
    7u,
    &unk_6B09F8);
  ParameterList_AddParameter(
    HumanAIConfigItem_ptParameterList,
    0x234u,
    Level_eParameterTypeReal32,
    "InquireTimeout[0..100]",
    7u,
    &unk_6B09F8);
  ParameterList_AddParameter(
    HumanAIConfigItem_ptParameterList,
    0x238u,
    Level_eParameterTypeReal32,
    "DetectionTimeDistanceFactor[0..100]",
    7u,
    &unk_6B09F8);
  ParameterList_AddParameter(
    HumanAIConfigItem_ptParameterList,
    0x244u,
    Level_eParameterTypeReal32,
    "MinRangeAccuracy[0..100]",
    7u,
    &unk_6B09F8);
  ParameterList_AddParameter(
    HumanAIConfigItem_ptParameterList,
    0x248u,
    Level_eParameterTypeReal32,
    "MedRangeAccuracy[0..100]",
    7u,
    &unk_6B09F8);
  ParameterList_AddParameter(
    HumanAIConfigItem_ptParameterList,
    0x24Cu,
    Level_eParameterTypeReal32,
    "MaxRangeAccuracy[0..100]",
    7u,
    &unk_6B09F8);
  ParameterList_AddParameter(
    HumanAIConfigItem_ptParameterList,
    0x250u,
    Level_eParameterTypeReal32,
    "AccuracyMedRange[0..]",
    7u,
    nullptr);
  ParameterList_AddParameter(
    HumanAIConfigItem_ptParameterList,
    0x254u,
    Level_eParameterTypeReal32,
    "AccuracyMaxRange[0..]",
    7u,
    nullptr);
  ParameterList_AddParameter(
    HumanAIConfigItem_ptParameterList,
    0x12Du,
    Level_eParameterTypeString256,
    "Accuracy values",
    2u,
    nullptr);
  ParameterList_AddParameter(
    HumanAIConfigItem_ptParameterList,
    0x2BCu,
    Level_eParameterTypeReal32,
    "AnimSpeed[0..1]",
    7u,
    &unk_6B09D8);
  ParameterList_AddParameter(
    HumanAIConfigItem_ptParameterList,
    0x278u,
    Level_eParameterTypeReal32,
    "CloseCombatDamage[0..10]",
    7u,
    &HumanAIConfig_DamageScaleLimitContext);
  ParameterList_AddParameter(
    HumanAIConfigItem_ptParameterList,
    0x284u,
    Level_eParameterTypeReal32,
    "CombatView1Alpha[0..180]",
    7u,
    &HumanAIConfig_ViewAngleLimitContext);
  ParameterList_AddParameter(
    HumanAIConfigItem_ptParameterList,
    0x288u,
    Level_eParameterTypeReal32,
    "CombatView1Length[0..500]",
    7u,
    &HumanAIConfig_ViewLengthLimitContext);
  ParameterList_AddParameter(
    HumanAIConfigItem_ptParameterList,
    0x28Cu,
    Level_eParameterTypeReal32,
    "CombatView2Alpha[0..180]",
    7u,
    &HumanAIConfig_ViewAngleLimitContext);
  ParameterList_AddParameter(
    HumanAIConfigItem_ptParameterList,
    0x290u,
    Level_eParameterTypeReal32,
    "CombatView2Length[0..500]",
    7u,
    &HumanAIConfig_ViewLengthLimitContext);
  ParameterList_AddParameter(
    HumanAIConfigItem_ptParameterList,
    0x240u,
    Level_eParameterTypeReal32,
    "EvasiveActionProb[0..100]",
    7u,
    &unk_6B09F8);
  ParameterList_AddParameter(
    HumanAIConfigItem_ptParameterList,
    0x270u,
    Level_eParameterTypeReal32,
    "GrenadeTimer[0..100]",
    7u,
    &unk_6B09F8);
  ParameterList_AddParameter(
    HumanAIConfigItem_ptParameterList,
    0x274u,
    Level_eParameterTypeReal32,
    "GrenadeReactionProb[0..100]",
    7u,
    &unk_6B09F8);
  ParameterList_AddParameter(
    HumanAIConfigItem_ptParameterList,
    0x26Cu,
    Level_eParameterTypeReal32,
    "GrenadeThrowProb[0..100]",
    7u,
    &unk_6B09F8);
  ParameterList_AddParameter(
    HumanAIConfigItem_ptParameterList,
    0x27Cu,
    Level_eParameterTypeReal32,
    "HitPoints[0..100]",
    7u,
    &unk_6B09F8);
  ParameterList_AddParameter(
    HumanAIConfigItem_ptParameterList,
    0x280u,
    Level_eParameterTypeReal32,
    "HitAnimThreshold[0..100]",
    7u,
    &unk_6B09F8);
  ParameterList_AddParameter(
    HumanAIConfigItem_ptParameterList,
    0x2A4u,
    Level_eParameterTypeReal32,
    "IdleAnimFreq[0..100]",
    7u,
    &unk_6B09F8);
  ParameterList_AddParameter(
    HumanAIConfigItem_ptParameterList,
    0x294u,
    Level_eParameterTypeReal32,
    "IdleView1Alpha[0..180]",
    7u,
    &HumanAIConfig_ViewAngleLimitContext);
  ParameterList_AddParameter(
    HumanAIConfigItem_ptParameterList,
    0x298u,
    Level_eParameterTypeReal32,
    "IdleView1Length[0..500]",
    7u,
    &HumanAIConfig_ViewLengthLimitContext);
  ParameterList_AddParameter(
    HumanAIConfigItem_ptParameterList,
    0x29Cu,
    Level_eParameterTypeReal32,
    "IdleView2Alpha[0..180]",
    7u,
    &HumanAIConfig_ViewAngleLimitContext);
  ParameterList_AddParameter(
    HumanAIConfigItem_ptParameterList,
    0x2A0u,
    Level_eParameterTypeReal32,
    "IdleView2Length[0..500]",
    7u,
    &HumanAIConfig_ViewLengthLimitContext);
  ParameterList_AddParameter(
    HumanAIConfigItem_ptParameterList,
    0x2B8u,
    Level_eParameterTypeReal32,
    "InvShoutFreq[0..100]",
    7u,
    &unk_6B09F8);
  ParameterList_AddParameter(
    HumanAIConfigItem_ptParameterList,
    0x2A8u,
    Level_eParameterTypeReal32,
    "InvView1Alpha[0..180]",
    7u,
    &HumanAIConfig_ViewAngleLimitContext);
  ParameterList_AddParameter(
    HumanAIConfigItem_ptParameterList,
    0x2ACu,
    Level_eParameterTypeReal32,
    "InvView1Length[0..500]",
    7u,
    &HumanAIConfig_ViewLengthLimitContext);
  ParameterList_AddParameter(
    HumanAIConfigItem_ptParameterList,
    0x2B0u,
    Level_eParameterTypeReal32,
    "InvView2Alpha[0..180]",
    7u,
    &HumanAIConfig_ViewAngleLimitContext);
  ParameterList_AddParameter(
    HumanAIConfigItem_ptParameterList,
    0x2B4u,
    Level_eParameterTypeReal32,
    "InvView2Length[0..500]",
    7u,
    &HumanAIConfig_ViewLengthLimitContext);
  ParameterList_AddParameter(
    HumanAIConfigItem_ptParameterList,
    0x260u,
    Level_eParameterTypeReal32,
    "MinFireInterval[0..1]",
    7u,
    &unk_6B09D8);
  ParameterList_AddParameter(
    HumanAIConfigItem_ptParameterList,
    0x23Cu,
    Level_eParameterTypeReal32,
    "PercentFirecPerBurst[0..100]",
    7u,
    &unk_6B09F8);
  ParameterList_AddParameter(
    HumanAIConfigItem_ptParameterList,
    0x268u,
    Level_eParameterTypeReal32,
    "MaxTrackingDist[0..500]",
    7u,
    &HumanAIConfig_ViewLengthLimitContext);
  ParameterList_AddParameter(
    HumanAIConfigItem_ptParameterList,
    0x264u,
    Level_eParameterTypeReal32,
    "MaxTrackingTime[0..500]",
    7u,
    &HumanAIConfig_ViewLengthLimitContext);
  ParameterList_AddParameter(
    HumanAIConfigItem_ptParameterList,
    0x2C0u,
    Level_eParameterTypeReal32,
    "DetectionToAttackTime[0..100]",
    7u,
    &unk_6B09F8);
  ParameterList_AddParameter(
    HumanAIConfigItem_ptParameterList,
    0x2C4u,
    Level_eParameterTypeReal32,
    "Damagemultiplier Right Foot [0..100]",
    7u,
    &unk_6B09F8);
  ParameterList_AddParameter(
    HumanAIConfigItem_ptParameterList,
    0x2C8u,
    Level_eParameterTypeReal32,
    "Damagemultiplier Right Lower Leg [0..100]",
    7u,
    &unk_6B09F8);
  ParameterList_AddParameter(
    HumanAIConfigItem_ptParameterList,
    0x2CCu,
    Level_eParameterTypeReal32,
    "Damagemultiplier Right Upper Leg [0..100]",
    7u,
    &unk_6B09F8);
  ParameterList_AddParameter(
    HumanAIConfigItem_ptParameterList,
    0x2D0u,
    Level_eParameterTypeReal32,
    "Damagemultiplier Right Hand [0..100]",
    7u,
    &unk_6B09F8);
  ParameterList_AddParameter(
    HumanAIConfigItem_ptParameterList,
    0x2D4u,
    Level_eParameterTypeReal32,
    "Damagemultiplier Right Lower Arm [0..100]",
    7u,
    &unk_6B09F8);
  ParameterList_AddParameter(
    HumanAIConfigItem_ptParameterList,
    0x2D8u,
    Level_eParameterTypeReal32,
    "Damagemultiplier Right Upper Arm [0..100]",
    7u,
    &unk_6B09F8);
  ParameterList_AddParameter(
    HumanAIConfigItem_ptParameterList,
    0x2DCu,
    Level_eParameterTypeReal32,
    "Damagemultiplier Left Foot [0..100]",
    7u,
    &unk_6B09F8);
  ParameterList_AddParameter(
    HumanAIConfigItem_ptParameterList,
    0x2E0u,
    Level_eParameterTypeReal32,
    "Damagemultiplier Left Lower Leg [0..100]",
    7u,
    &unk_6B09F8);
  ParameterList_AddParameter(
    HumanAIConfigItem_ptParameterList,
    0x2E4u,
    Level_eParameterTypeReal32,
    "Damagemultiplier Left Upper Leg [0..100]",
    7u,
    &unk_6B09F8);
  ParameterList_AddParameter(
    HumanAIConfigItem_ptParameterList,
    0x2E8u,
    Level_eParameterTypeReal32,
    "Damagemultiplier Left Hand [0..100]",
    7u,
    &unk_6B09F8);
  ParameterList_AddParameter(
    HumanAIConfigItem_ptParameterList,
    0x2ECu,
    Level_eParameterTypeReal32,
    "Damagemultiplier Left Lower Arm [0..100]",
    7u,
    &unk_6B09F8);
  ParameterList_AddParameter(
    HumanAIConfigItem_ptParameterList,
    0x2F0u,
    Level_eParameterTypeReal32,
    "Damagemultiplier Left Upper Arm [0..100]",
    7u,
    &unk_6B09F8);
  ParameterList_AddParameter(
    HumanAIConfigItem_ptParameterList,
    0x2F4u,
    Level_eParameterTypeReal32,
    "Damagemultiplier Upper Body [0..100]",
    7u,
    &unk_6B09F8);
  ParameterList_AddParameter(
    HumanAIConfigItem_ptParameterList,
    0x2F8u,
    Level_eParameterTypeReal32,
    "Damagemultiplier Chest [0..100]",
    7u,
    &unk_6B09F8);
  ParameterList_AddParameter(
    HumanAIConfigItem_ptParameterList,
    0x2FCu,
    Level_eParameterTypeReal32,
    "Damagemultiplier Back [0..100]",
    7u,
    &unk_6B09F8);
  ParameterList_AddParameter(
    HumanAIConfigItem_ptParameterList,
    0x300u,
    Level_eParameterTypeReal32,
    "Damagemultiplier Groin [0..100]",
    7u,
    &unk_6B09F8);
  ParameterList_AddParameter(
    HumanAIConfigItem_ptParameterList,
    0x304u,
    Level_eParameterTypeReal32,
    "Damagemultiplier Head [0..100]",
    7u,
    &unk_6B09F8);
}

// source: j/0/humanai/humanaiconfig.c:492  [anchor-hash]
void __cdecl HumanAIConfig_Close()
{
  char *v0; // esi
  int v1; // esi
  int v2; // esi

  v0 = HumanAIConfig_azDifficultyScaleName;
  do
  {
    Symbol_Remove(v0);
    v0 += 80;
  }
  while ( (int)v0 < 7375216 );
  if ( HumanAIConfig_ptParameterList )
  {
    v1 = *(_DWORD *)((unsigned int)&HumanAIConfig_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v1);
    memset(*(void **)(v1 + 8), 0xCDu, *(_DWORD *)(v1 + 16));
    free((void *)v1);
  }
  if ( HumanAIConfigItem_ptParameterList )
  {
    v2 = *(_DWORD *)((unsigned int)&HumanAIConfigItem_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v2);
    memset(*(void **)(v2 + 8), 0xCDu, *(_DWORD *)(v2 + 16));
    free((void *)v2);
  }
  QTask_DeleteQTaskType(HumanAIConfig_eQTaskType);
  QTask_DeleteQTaskType(HumanAIConfigItem_eQTaskType);
}

// source: j/0/humanai/humanaiconfig.c:519  [size]
unsigned __int16 __cdecl HumanAIConfig_GetQTaskType()
{
  return HumanAIConfig_eQTaskType;
}

// source: j/0/humanai/humanaiconfig.c:534  [size]
unsigned __int16 __cdecl HumanAIConfigItem_GetQTaskType()
{
  return HumanAIConfigItem_eQTaskType;
}

// source: j/0/humanai/humanaiconfig.c:549  [anchor-strings]
void __cdecl HumanAIConfig_LoadSettings(struct QTask_s *ptParentQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { char *iI; };
    struct { char igi2_o1[4]; struct QTask_s *ptHumanAIConfigQTask; };
    struct { char igi2_o2[8]; char v19; };
    char igi2_extent[16];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  char *v1; // ebx
  char *v2; // ebp
  struct QTask_s *v3; // ebp
  char **v4; // esi
  struct QTask_s **v5; // ebx
  char *v6; // esi
  _DWORD *v7; // ebx
  struct QTask_s *ptHead; // eax
  char **v9; // esi
  struct QTask_s **p_ptPrev; // ebx
  struct QTask_s *v11; // eax
  int v12; // ecx
  char *v13; // esi
  _DWORD *p_ptTail; // ebx
  struct QTask_s *v15; // eax
  int v16; // edx

  igi2_frame.ptHumanAIConfigQTask = QTask_NewFn(ptParentQTask, HumanAIConfig_eQTaskType, nullptr);
  igi2_frame.iI = nullptr;
  v1 = HumanAIConfig_azDifficultyScaleName;
  v2 = Config_azGameDifficulty;
  do
  {
    strcpy(v1, "DIFF_SCALE_");
    strcat(v1, v2);
    Symbol_Register(
      v1,
      (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
      igi2_frame.iI,
      4,
      QSCRIPT_SYMBOLCLASS_CONSTANT,
      QSCRIPT_SYMBOLTYPE_INT,
      QSCRIPT_SYMBOLLIFESPAN_INFINITE);
    v2 += 16;
    v1 += 80;
    ++igi2_frame.iI;
  }
  while ( (int)v2 < 6828928 );
  v3 = igi2_frame.ptHumanAIConfigQTask;
  if ( igi2_frame.ptHumanAIConfigQTask )
  {
    HumanAIConfig_ptHumanAIConfigQTask = igi2_frame.ptHumanAIConfigQTask;
    if ( Level_LoadQTask(igi2_frame.ptHumanAIConfigQTask, "LOCAL:common/ai/settings.qsc", false) )
    {
      ptHead = igi2_frame.ptHumanAIConfigQTask->tQTaskChildren.ptHead;
      if ( ptHead->ptNext && ptHead )
      {
        do
        {
          if ( LOBYTE(ptHead[1].ptPrev) )
            *((_DWORD *)&v3[1].ptPrev + (int)ptHead[1].ptNext) = ptHead;
          else
            *((_DWORD *)&v3[1].tQTaskRefList.ptTail + (int)ptHead[1].ptNext) = ptHead;
          ptHead = ptHead->ptNext;
        }
        while ( ptHead && ptHead->ptNext );
      }
      v9 = HumanAI_azAITypeStrings;
      p_ptPrev = &v3[1].ptPrev;
      do
      {
        if ( !*p_ptPrev )
        {
          igi2_frame.ptHumanAIConfigQTask = (struct QTask_s *)*v9;
          igi2_frame.v19 = 1;
          v11 = QTask_NewFn(v3, HumanAIConfigItem_eQTaskType, &igi2_frame.ptHumanAIConfigQTask);
          v12 = ParameterList_eUpdateInternalDataQTaskEvent;
          *p_ptPrev = v11;
          ((void (__cdecl *)(struct QTask_s *, _DWORD))QTask_aatQTaskFinalEvent[v12][v11->eQTaskType].pfHandler)(v11, 0);
        }
        ++v9;
        ++p_ptPrev;
      }
      while ( (int)v9 < 7050968 );
      v13 = HumanAIConfig_azDifficultyScaleName;
      p_ptTail = &v3[1].tQTaskRefList.ptTail;
      do
      {
        if ( !*p_ptTail )
        {
          igi2_frame.ptHumanAIConfigQTask = (struct QTask_s *)v13;
          igi2_frame.v19 = 0;
          v15 = QTask_NewFn(v3, HumanAIConfigItem_eQTaskType, &igi2_frame.ptHumanAIConfigQTask);
          v16 = ParameterList_eUpdateInternalDataQTaskEvent;
          *p_ptTail = v15;
          ((void (__cdecl *)(struct QTask_s *, _DWORD))QTask_aatQTaskFinalEvent[v16][v15->eQTaskType].pfHandler)(v15, 0);
        }
        v13 += 80;
        ++p_ptTail;
      }
      while ( (int)v13 < 7375216 );
    }
    else
    {
      v4 = HumanAI_azAITypeStrings;
      v5 = &igi2_frame.ptHumanAIConfigQTask[1].ptPrev;
      do
      {
        igi2_frame.ptHumanAIConfigQTask = (struct QTask_s *)*v4;
        igi2_frame.v19 = 1;
        *v5 = QTask_NewFn(v3, HumanAIConfigItem_eQTaskType, &igi2_frame.ptHumanAIConfigQTask);
        ++v4;
        ++v5;
      }
      while ( (int)v4 < 7050968 );
      v6 = HumanAIConfig_azDifficultyScaleName;
      v7 = &v3[1].tQTaskRefList.ptTail;
      do
      {
        igi2_frame.ptHumanAIConfigQTask = (struct QTask_s *)v6;
        igi2_frame.v19 = 0;
        *v7 = QTask_NewFn(v3, HumanAIConfigItem_eQTaskType, &igi2_frame.ptHumanAIConfigQTask);
        v6 += 80;
        ++v7;
      }
      while ( (int)v6 < 7375216 );
      QTask_TriggerQTaskEventChildrenRecursively(v3, ParameterList_eUpdateInternalDataQTaskEvent, nullptr);
    }
  }
}

// source: j/0/humanai/humanaiconfig.c:676  [size]
float __cdecl HumanAIConfig_CalculateAccuracyFactor(
        float vMinRangeAccuracy,
        float vMaxRangeAccuracy,
        float vAccuracyMinRange,
        float vAccuracyMaxRange)
{
  return pow(vMaxRangeAccuracy / vMinRangeAccuracy, 1.0 / (vAccuracyMaxRange - vAccuracyMinRange));
}

// source: j/0/humanai/humanaiconfig.c:696  [anchor-callee]
float __cdecl HumanAIConfig_CalculateAccuracy(
        float vMinRangeAccuracy,
        float vMedRangeAccuracy,
        float vAccuracyMedRange,
        float vAccuracyMaxRange,
        float vMedRangeAccuracyFactor,
        float vMaxRangeAccuracyFactor,
        float vDistanceToCalcFor)
{
  if ( vDistanceToCalcFor >= (double)vAccuracyMedRange )
  {
    if ( vDistanceToCalcFor >= 1.0 )
    {
      if ( vAccuracyMaxRange < (double)vDistanceToCalcFor )
        vDistanceToCalcFor = vAccuracyMaxRange;
    }
    else
    {
      vDistanceToCalcFor = 1.0;
    }
    return pow(vMaxRangeAccuracyFactor, vDistanceToCalcFor - vAccuracyMedRange) * vMedRangeAccuracy;
  }
  else
  {
    return pow(vMedRangeAccuracyFactor, vDistanceToCalcFor) * vMinRangeAccuracy;
  }
}

// source: j/0/humanai/humanaiconfig.c:723  [anchor-callee]
void __cdecl HumanAIConfig_SetAISettingsFromConfig(struct HumanAI_s *ptHumanAI)
{
  struct QTask_s *ptParent; // ebp
  float *v2; // edi
  float *v3; // ebx
  double v4; // st7
  double v5; // st7
  double v6; // st7
  double v7; // st7
  double v8; // st7
  double v9; // st7
  double v10; // st7
  float vIdleAnimationFrequency; // edx

  ptParent = ptHumanAI->tQTask.ptParent;
  if ( HumanAIConfig_ptHumanAIConfigQTask )
  {
    if ( 2752 * Config_tConfig.iActiveProfile != -7392072 )
    {
      v2 = *((float **)&HumanAIConfig_ptHumanAIConfigQTask[1].ptPrev + LODWORD(ptHumanAI->vHearingRangeFactor));
      if ( v2 )
      {
        if ( LevelFlow_ptLevelFlow )
        {
          v3 = *((float **)&HumanAIConfig_ptHumanAIConfigQTask[1].tQTaskRefList.ptTail
               + LevelFlow_ptLevelFlow->eDifficultySetting);
          ptHumanAI->tTweakParameters.vMedRangeAccuracyFactor = v3[140] * v2[140];
          ptHumanAI->tTweakParameters.vMaxRangeAccuracyFactor = v3[141] * v2[141];
          v4 = v3[142] * v2[142];
          ptHumanAI->tTweakParameters.vMinDelayBetweenFiring = v4;
          if ( v4 >= 0.0 )
          {
            if ( v4 > 1.0 )
              v4 = 1.0;
          }
          else
          {
            v4 = 0.0;
          }
          ptHumanAI->tTweakParameters.vMinDelayBetweenFiring = v4;
          v5 = v3[145] * v2[145] * 0.009999999776482582;
          ptHumanAI->tTweakParameters.vGrenadeThrowProb = v5;
          if ( v5 <= 0.009999999776482582 )
            v5 = 0.009999999776482582;
          ptHumanAI->tTweakParameters.vGrenadeThrowProb = v5;
          v6 = v3[146] * v2[146] * 0.009999999776482582;
          ptHumanAI->tTweakParameters.vGrenadeDetonationTimer = v6;
          if ( v6 <= 0.009999999776482582 )
            v6 = 0.009999999776482582;
          ptHumanAI->tTweakParameters.vGrenadeDetonationTimer = v6;
          v7 = v3[147] * v2[147] * 0.009999999776482582;
          ptHumanAI->tTweakParameters.vGrenadeLandingReactionProb = v7;
          if ( v7 <= 0.0 )
            v7 = 0.0;
          ptHumanAI->tTweakParameters.vGrenadeLandingReactionProb = v7;
          v8 = v3[148] * v2[148] * 4096.0;
          ptHumanAI->tTweakParameters.vCloseCombatDamage = v8;
          if ( v8 <= 1.0 )
            v8 = 1.0;
          ptHumanAI->tTweakParameters.vCloseCombatDamage = v8;
          v9 = v3[149] * v2[149] * 4096.0;
          ptHumanAI->tTweakParameters.vHitPoints = v9;
          if ( v9 <= 1.0 )
            v9 = 1.0;
          ptHumanAI->tTweakParameters.vHitPoints = v9;
          ptHumanAI->tTweakParameters.vHitRecoilThreshold = pow(
                                                              ptHumanAI->tTweakParameters.vGrenadeDetonationTimer
                                                            / ptHumanAI->tTweakParameters.vGrenadeThrowProb,
                                                              1.0 / ptHumanAI->tTweakParameters.vCloseCombatDamage);
          ptHumanAI->tTweakParameters.vCombatViewCone1Alpha = pow(
                                                                ptHumanAI->tTweakParameters.vGrenadeLandingReactionProb
                                                              / ptHumanAI->tTweakParameters.vGrenadeDetonationTimer,
                                                                1.0
                                                              / (ptHumanAI->tTweakParameters.vHitPoints
                                                               - ptHumanAI->tTweakParameters.vCloseCombatDamage));
          v10 = v3[175] * v2[175];
          if ( v10 >= 0.800000011920929 )
          {
            if ( v10 > 1.2000000476837158 )
              v10 = 1.2000000476837158;
          }
          else
          {
            v10 = 0.800000011920929;
          }
          ptHumanAI->tTweakParameters.avDamageMultiplier[8] = v10;
          ptHumanAI->tTweakParameters.vIdleViewCone2Length = v3[158] * v2[158];
          ptHumanAI->tTweakParameters.vInvestigateViewCone1Length = v2[161] * 0.01745329238474369 * v3[161];
          ptHumanAI->tTweakParameters.vInvestigateViewCone2Alpha = v3[162] * v2[162] * 4096.0;
          ptHumanAI->tTweakParameters.vInvestigateViewCone2Length = v2[163] * 0.01745329238474369 * v3[163];
          ptHumanAI->tTweakParameters.vInvestigateShoutFrequency = v3[164] * v2[164] * 4096.0;
          ptHumanAI->tTweakParameters.vTrackingMaxDistance = v2[144] * 0.009999999776482582 * v3[144];
          ptHumanAI->tTweakParameters.vIdleViewCone1Length = v2[156] * 30.0;
          ptHumanAI->tTweakParameters.vIdleViewCone2Alpha = v2[157] * 0.009999999776482582 * v3[157];
          ptHumanAI->tTweakParameters.vIdleViewCone1Alpha = v2[155] * 0.009999999776482582 * v3[155];
          ptHumanAI->tTweakParameters.vIdleAnimationFrequency = v2[159] * 0.009999999776482582 * v3[159];
          ptHumanAI->tTweakParameters.vInvestigateViewCone1Alpha = v2[160] * 0.009999999776482582 * v3[160];
          ptHumanAI->tTweakParameters.avDamageMultiplier[2] = v2[169] * 30.0 * v3[169];
          ptHumanAI->tTweakParameters.vAnimSpeedFactor = v2[165] * 0.01745329238474369 * v3[165];
          ptHumanAI->tTweakParameters.vDetectionToAttackTime = v3[166] * v2[166] * 4096.0;
          ptHumanAI->tTweakParameters.avDamageMultiplier[0] = v2[167] * 0.01745329238474369 * v3[167];
          ptHumanAI->tTweakParameters.avDamageMultiplier[1] = v3[168] * v2[168] * 4096.0;
          ptHumanAI->tTweakParameters.avDamageMultiplier[7] = v3[174] * v2[174] * 30.0;
          vIdleAnimationFrequency = ptHumanAI->tTweakParameters.vIdleAnimationFrequency;
          ptHumanAI->tTweakParameters.avDamageMultiplier[3] = v2[170] * 0.01745329238474369 * v3[170];
          ptHumanAI->tTweakParameters.avDamageMultiplier[4] = v3[171] * v2[171] * 4096.0;
          ptHumanAI->tTweakParameters.avDamageMultiplier[5] = v2[172] * 0.01745329238474369 * v3[172];
          ptHumanAI->tTweakParameters.avDamageMultiplier[6] = v3[173] * v2[173] * 4096.0;
          ptHumanAI->tTweakParameters.vCombatViewCone1Length = v3[152] * v2[152] * 30.0;
          ptHumanAI->tTweakParameters.vTrackingTimeout = v2[143] * 0.009999999776482582 * v3[143];
          ptHumanAI->tTweakParameters.vCombatViewCone2Length = v3[154] * v2[154] * 4096.0;
          ptHumanAI->tTweakParameters.vCombatViewCone2Alpha = v3[153] * v2[153] * 30.0;
          ptHumanAI->tTweakParameters.avDamageMultiplier[9] = v3[176] * v2[176] * 30.0;
          *(float *)&ptParent[25].tQTaskRefList.ptMiddle = vIdleAnimationFrequency;
        }
      }
    }
  }
}

// source: j/0/humanai/humanaiconfig.c:840  [size]
struct HumanAIConfig_t *__cdecl HumanAIConfig_GetHumanAIConfigQTask()
{
  return (struct HumanAIConfig_t *)HumanAIConfig_ptHumanAIConfigQTask;
}
