/* j/0/weapons/gun.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/weapons/gun.c:115  [anchor-mhash]
void __cdecl Gun_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  int v2; // edx
  struct QReference_s **p_ptTail; // esi

  *(_DWORD *)&ptQTask[1].eQTaskType = 1065353216;
  ptQTask[2].ptNext = (struct QTask_s *)1065353216;
  ptQTask[2].tQTaskRefList.ptHead = (struct QReference_s *)1065353216;
  ptQTask[1].tQTaskRefList.ptMiddle = (struct QReference_s *)1045220557;
  ptQTask[1].tQTaskRefList.ptTail = (struct QReference_s *)1045220557;
  ptQTask[1].ptPrev = (struct QTask_s *)1;
  ptQTask[1].tQTaskChildren.ptHead = (struct QTask_s *)1;
  ptQTask[1].tQTaskChildren.ptMiddle = (struct QTask_s *)1;
  ptQTask[1].tQTaskChildren.ptTail = (struct QTask_s *)1;
  *(_DWORD *)&ptQTask[2].eQTaskType = 512;
  ptQTask[3].ptNext = (struct QTask_s *)512;
  ptQTask[1].ptNext = (struct QTask_s *)-1;
  ptQTask[1].ptParent = (struct QTask_s *)1120403456;
  ptQTask[2].ptPrev = nullptr;
  ptQTask[2].tQTaskChildren.ptHead = nullptr;
  ptQTask[2].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[2].tQTaskChildren.ptTail = nullptr;
  ptQTask[2].tQTaskRefList.ptMiddle = (struct QReference_s *)1084227584;
  ptQTask[2].tQTaskRefList.ptTail = (struct QReference_s *)0x40000000;
  ptQTask[3].ptPrev = nullptr;
  LOBYTE(ptQTask[14].eQTaskType) = 0;
  LOBYTE(ptQTask[5].tQTaskChildren.ptMiddle) = 0;
  LOBYTE(ptQTask[6].ptPrev) = 0;
  LOBYTE(ptQTask[6].eQTaskType) = 0;
  LOBYTE(ptQTask[7].tQTaskRefList.ptTail) = 0;
  LOBYTE(ptQTask[8].tQTaskRefList.ptHead) = 0;
  LOBYTE(ptQTask[9].tQTaskChildren.ptMiddle) = 0;
  LOBYTE(ptQTask[10].ptPrev) = 0;
  LOBYTE(ptQTask[10].eQTaskType) = 0;
  LOBYTE(ptQTask[11].tQTaskRefList.ptTail) = 0;
  LOBYTE(ptQTask[12].tQTaskRefList.ptHead) = 0;
  LOBYTE(ptQTask[13].tQTaskChildren.ptMiddle) = 0;
  LOBYTE(ptQTask[14].ptPrev) = 0;
  v2 = 0;
  p_ptTail = &ptQTask[15].tQTaskRefList.ptTail;
  do
  {
    *((_BYTE *)&ptQTask[19].ptNext + v2) = 0;
    *(_BYTE *)p_ptTail = 0;
    ++v2;
    p_ptTail += 8;
  }
  while ( v2 < 3 );
  LOBYTE(ptQTask[18].ptPrev) = 0;
  *(_DWORD *)&ptQTask[18].eQTaskType = 1221066752;
  ptQTask[4].ptParent = nullptr;
  *(_DWORD *)&ptQTask[4].eQTaskType = 0;
  ptQTask[5].ptNext = nullptr;
  ptQTask[5].ptPrev = nullptr;
  ptQTask[5].tQTaskChildren.ptHead = nullptr;
  LOBYTE(ptQTask[3].tQTaskChildren.ptHead) = 0;
  LOBYTE(ptQTask[4].ptNext) = 0;
  ptQTask[1].tQTaskRefList.ptHead = (struct QReference_s *)1048576000;
  ptQTask[2].ptParent = nullptr;
}

// source: j/0/weapons/gun.c:185  [size]
void __cdecl Gun_DeleteHandler(struct QTask_s *ptQTask)
{
  WeaponType_DeleteParameters((struct QReference_s **)&ptQTask[3].ptPrev);
}

// source: j/0/weapons/gun.c:201  [size]
void __cdecl Gun_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = Gun_ptParameterList;
}

// source: j/0/weapons/gun.c:219  [anchor-mhash]
void __cdecl Gun_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  if ( LOBYTE(ptQTask[3].tQTaskChildren.ptHead) )
    ptQTask[5].ptPrev = (struct QTask_s *)GameFunctions_RegisterGameTexture((char *)&ptQTask[3].tQTaskChildren);
  if ( LOBYTE(ptQTask[4].ptNext) )
    ptQTask[5].tQTaskChildren.ptHead = (struct QTask_s *)GameFunctions_RegisterGameTexture((char *)&ptQTask[4]);
}

// source: j/0/weapons/gun.c:252  [size]
void __cdecl Gun_UpdaterInternalDataAfterLoadHandler(struct QTask_s *ptQTask)
{
  ptQTask[3].ptPrev = (struct QTask_s *)WeaponType_CreateParameters(ptQTask[2].eQTaskType, ptQTask);
  ptQTask[3].ptNext = *(struct QTask_s **)&ptQTask[2].eQTaskType;
}

// source: j/0/weapons/gun.c:269  [size]
void __cdecl Gun_CreateWeaponTypeParametersHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *v2; // esi

  v2 = QTask_NewFn(*((struct QTask_s **)pxContext + 1), Gun_eQTaskType, nullptr);
  *((_DWORD *)pxContext + 2) = v2;
  v2[3].ptPrev = (struct QTask_s *)WeaponType_CreateParameters(v2[2].eQTaskType, v2);
}

// source: j/0/weapons/gun.c:293  [size]
void __cdecl Gun_UpdateTagItemsHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ;
}

// source: j/0/weapons/gun.c:313  [size]
void __cdecl Gun_DeleteWeaponTypeParametersHandler(struct QTask_s *ptQTask, void *pxContext)
{
  WeaponType_DeleteParameters((struct QReference_s **)(*(_DWORD *)pxContext + 124));
  ((void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[WeaponType_eDeleteParametersQTaskEvent][FireType_eQTaskType].pfHandler)(
    ptQTask,
    pxContext);
}

// source: j/0/weapons/gun.c:336  [anchor-mhash]
void __cdecl Gun_GetAnimHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct WeaponType_s *v2; // edx
  int v3; // ebp
  int v4; // esi
  double v5; // st7
  struct AnimHeader_s *Anim; // eax
  struct AnimHeader_s *v7; // eax
  char *v8; // edi
  struct AnimHeader_s *v9; // eax
  double v10; // st7
  struct AnimHeader_s *v11; // eax
  struct AnimHeader_s *v12; // eax
  struct AnimHeader_s *v13; // eax
  struct AnimHeader_s *v14; // eax
  struct AnimHeader_s *v15; // eax
  double v16; // st7
  unsigned __int8 *v17; // ecx
  struct AnimHeader_s *AnimHeaderFromWeaponTypeAnim; // eax
  struct AnimHeader_s *v19; // eax
  unsigned __int8 *v20; // ecx
  enum WeaponTypeAnim_e v21; // esi
  struct AnimHeader_s *v22; // eax
  unsigned __int8 *v23; // ecx
  struct AnimHeader_s *v24; // eax
  struct AnimHeader_s *v25; // eax
  double nTotalTime; // st6
  int v27; // edx
  unsigned __int8 *v28; // ecx
  struct AnimHeader_s *v29; // eax
  struct AnimHeader_s *v30; // eax

  v2 = *((struct WeaponType_s **)pxContext + 2);
  v3 = *((_DWORD *)pxContext + 5);
  v4 = *((_DWORD *)pxContext + 3);
  switch ( v4 )
  {
    case 4:
      *((_DWORD *)pxContext + 6) = Hierarchy_GetAnim(*(unsigned __int8 **)pxContext, (char *)(v3 + 212));
      return;
    case 5:
      *((_DWORD *)pxContext + 6) = Hierarchy_GetAnim(*(unsigned __int8 **)pxContext, (char *)(v3 + 244));
      return;
    case 6:
      *((_DWORD *)pxContext + 6) = Hierarchy_GetAnim(*(unsigned __int8 **)pxContext, (char *)(v3 + 276));
      return;
    case 7:
      v5 = 0.0;
      if ( *(_BYTE *)(v3 + 340) )
      {
        Anim = Hierarchy_GetAnim(*(unsigned __int8 **)pxContext, (char *)(v3 + 340));
        if ( Anim )
          v5 = (double)Anim->nTotalTime * 0.00020833333837799728 * (double)(*(_DWORD *)(v3 + 52) - 1);
        v7 = Hierarchy_GetAnim(*(unsigned __int8 **)pxContext, (char *)(v3 + 372));
        if ( v7 )
          v5 = v5 + (double)v7->nTotalTime * 0.00020833333837799728;
      }
      v8 = (char *)(v3 + 308);
      goto LABEL_11;
    case 8:
      v10 = 0.0;
      v11 = Hierarchy_GetAnim(*(unsigned __int8 **)pxContext, (char *)(v3 + 372));
      if ( v11 )
        v10 = (double)v11->nTotalTime * 0.00020833333837799728;
      v12 = Hierarchy_GetAnim(*(unsigned __int8 **)pxContext, (char *)(v3 + 308));
      if ( v12 )
        v10 = v10 + (double)v12->nTotalTime * 0.00020833333837799728;
      v13 = Hierarchy_GetAnim(*(unsigned __int8 **)pxContext, (char *)(v3 + 340));
      if ( v13 )
        v10 = v10 + (double)v13->nTotalTime * 0.00020833333837799728 * (double)(*(_DWORD *)(v3 + 52) - 1);
      *((_DWORD *)pxContext + 6) = v13;
      *((float *)pxContext + 7) = v10 / *(float *)(v3 + 76);
      return;
    case 9:
      v5 = 0.0;
      v14 = Hierarchy_GetAnim(*(unsigned __int8 **)pxContext, (char *)(v3 + 308));
      if ( v14 )
        v5 = (double)v14->nTotalTime * 0.00020833333837799728;
      v15 = Hierarchy_GetAnim(*(unsigned __int8 **)pxContext, (char *)(v3 + 340));
      if ( v15 )
        v5 = v5 + (double)v15->nTotalTime * 0.00020833333837799728 * (double)(*(_DWORD *)(v3 + 52) - 1);
      v8 = (char *)(v3 + 372);
LABEL_11:
      v9 = Hierarchy_GetAnim(*(unsigned __int8 **)pxContext, v8);
      goto LABEL_12;
    case 17:
      *((_DWORD *)pxContext + 6) = Hierarchy_GetAnim(*(unsigned __int8 **)pxContext, (char *)(v3 + 404));
      return;
    case 18:
      *((_DWORD *)pxContext + 6) = Hierarchy_GetAnim(*(unsigned __int8 **)pxContext, (char *)(v3 + 436));
      return;
    case 19:
      *((_DWORD *)pxContext + 6) = Hierarchy_GetAnim(*(unsigned __int8 **)pxContext, (char *)(v3 + 468));
      return;
    case 20:
    case 23:
      v16 = 0.0;
      if ( v2 )
      {
        if ( *(_BYTE *)(v3 + 340) )
        {
          v17 = *(unsigned __int8 **)pxContext;
          AnimHeaderFromWeaponTypeAnim = WeaponType_GetAnimHeaderFromWeaponTypeAnim(
                                           v2,
                                           *(unsigned __int8 **)pxContext,
                                           (enum WeaponTypeAnim_e)(v4 == 23
                                                                 ? WEAPONTYPEANIM_FLAT_RELOADLOOP
                                                                 : WEAPONTYPEANIM_TENSE_RELOADLOOP));
          if ( AnimHeaderFromWeaponTypeAnim )
            v16 = (double)AnimHeaderFromWeaponTypeAnim->nTotalTime * 0.00020833333837799728 * (double)(*(_DWORD *)(v3 + 52) - 1);
          v19 = WeaponType_GetAnimHeaderFromWeaponTypeAnim(
                  v2,
                  v17,
                  (enum WeaponTypeAnim_e)(v4 == 23 ? WEAPONTYPEANIM_FLAT_RELOADEND : WEAPONTYPEANIM_TENSE_RELOADEND));
          if ( v19 )
            v16 = v16 + (double)v19->nTotalTime * 0.00020833333837799728;
        }
        v20 = *(unsigned __int8 **)pxContext;
        v21 = v4 == 23 ? WEAPONTYPEANIM_FLAT_RELOAD : WEAPONTYPEANIM_TENSE_RELOAD;
        v22 = WeaponType_GetAnimHeaderFromWeaponTypeAnim(v2, *(unsigned __int8 **)pxContext, v21);
        if ( v22 )
          v16 = v16 + (double)v22->nTotalTime * 0.00020833333837799728;
        *((_DWORD *)pxContext + 6) = WeaponType_GetAnimHeaderFromWeaponTypeAnim(v2, v20, v21);
        *((float *)pxContext + 7) = v16 / *(float *)(v3 + 76);
      }
      else
      {
        *((_DWORD *)pxContext + 6) = Hierarchy_GetAnim(*(unsigned __int8 **)pxContext, (char *)(v3 + 500));
      }
      return;
    case 21:
    case 24:
      v5 = 0.0;
      v23 = *(unsigned __int8 **)pxContext;
      if ( !v2 )
      {
        *((_DWORD *)pxContext + 6) = Hierarchy_GetAnim(v23, (char *)(v3 + 532));
        return;
      }
      v24 = WeaponType_GetAnimHeaderFromWeaponTypeAnim(
              v2,
              v23,
              (enum WeaponTypeAnim_e)(v4 == 24 ? WEAPONTYPEANIM_FLAT_RELOADEND : WEAPONTYPEANIM_TENSE_RELOADEND));
      if ( v24 )
        v5 = (double)v24->nTotalTime * 0.00020833333837799728;
      v25 = WeaponType_GetAnimHeaderFromWeaponTypeAnim(
              v2,
              v23,
              (enum WeaponTypeAnim_e)(v4 == 24 ? WEAPONTYPEANIM_FLAT_RELOAD : WEAPONTYPEANIM_TENSE_RELOAD));
      if ( v25 )
        v5 = v5 + (double)v25->nTotalTime * 0.00020833333837799728;
      v9 = WeaponType_GetAnimHeaderFromWeaponTypeAnim(
             v2,
             v23,
             (enum WeaponTypeAnim_e)(v4 == 24 ? WEAPONTYPEANIM_FLAT_RELOADLOOP : WEAPONTYPEANIM_TENSE_RELOADLOOP));
      if ( v9 )
      {
        nTotalTime = (double)v9->nTotalTime;
        v27 = *(_DWORD *)(v3 + 52) - 1;
        *((_DWORD *)pxContext + 6) = v9;
        *((float *)pxContext + 7) = (v5 + nTotalTime * 0.00020833333837799728 * (double)v27) / *(float *)(v3 + 76);
        return;
      }
      goto LABEL_14;
    case 22:
    case 25:
      v5 = 0.0;
      if ( v2 )
      {
        v28 = *(unsigned __int8 **)pxContext;
        v29 = WeaponType_GetAnimHeaderFromWeaponTypeAnim(
                v2,
                *(unsigned __int8 **)pxContext,
                (enum WeaponTypeAnim_e)(v4 == 25 ? WEAPONTYPEANIM_FLAT_RELOAD : WEAPONTYPEANIM_TENSE_RELOAD));
        if ( v29 )
          v5 = (double)v29->nTotalTime * 0.00020833333837799728;
        v30 = WeaponType_GetAnimHeaderFromWeaponTypeAnim(
                v2,
                v28,
                (enum WeaponTypeAnim_e)(v4 == 25 ? WEAPONTYPEANIM_FLAT_RELOADLOOP : WEAPONTYPEANIM_TENSE_RELOADLOOP));
        if ( v30 )
          v5 = v5 + (double)v30->nTotalTime * 0.00020833333837799728 * (double)(*(_DWORD *)(v3 + 52) - 1);
        v9 = WeaponType_GetAnimHeaderFromWeaponTypeAnim(
               v2,
               v28,
               (enum WeaponTypeAnim_e)(v4 == 25 ? WEAPONTYPEANIM_FLAT_RELOADEND : WEAPONTYPEANIM_TENSE_RELOADEND));
LABEL_12:
        if ( v9 )
          v5 = v5 + (double)v9->nTotalTime * 0.00020833333837799728;
LABEL_14:
        *((_DWORD *)pxContext + 6) = v9;
        *((float *)pxContext + 7) = v5 / *(float *)(v3 + 76);
      }
      else
      {
        *((_DWORD *)pxContext + 6) = Hierarchy_GetAnim(*(unsigned __int8 **)pxContext, (char *)(v3 + 564));
      }
      return;
    default:
      return;
  }
}

// source: j/0/weapons/gun.c:551  [anchor-mhash]
void __cdecl Gun_GetAmmoInfoHandler(struct QTask_s *ptQTask, void *pxContext)
{
  int *v2; // eax

  v2 = *(int **)pxContext;
  *((_DWORD *)pxContext + 2) = 1;
  *((_DWORD *)pxContext + 3) = v2[12];
  *((_DWORD *)pxContext + 4) = v2[13];
  *((_DWORD *)pxContext + 1) = AmmoType_GetAmmoTypeFromID(v2[10]);
}

// source: j/0/weapons/gun.c:576  [anchor-caller]
void __cdecl Gun_WeaponFireHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct real32x9_t *p_tOrientation; };
    struct { char igi2_o1[32]; int v106; };
    struct { char igi2_o2[32]; float v107; };
    struct { char igi2_o3[32]; float v108; };
    struct { char igi2_o4[36]; float v109; };
    struct { char igi2_o5[40]; float v110; };
    struct { char igi2_o6[44]; float v111; };
    struct { char igi2_o7[48]; float v112; };
    struct { char igi2_o8[48]; float v113; };
    struct { char igi2_o9[48]; float v114; };
    struct { char igi2_o10[52]; float v115; };
    struct { char igi2_o11[52]; float v116; };
    struct { char igi2_o12[60]; int v117; };
    struct { char igi2_o13[60]; float v118; };
    struct { char igi2_o14[64]; struct real64x3_t ptPos; };
    struct { char igi2_o15[88]; unsigned int v120; };
    struct { char igi2_o16[92]; float v121; };
    struct { char igi2_o17[96]; double vZ; };
    struct { char igi2_o18[104]; float v123; };
    struct { char igi2_o19[108]; struct QTask_s ptParent; };
    struct { char igi2_o20[148]; __int64 v125; };
    struct { char igi2_o21[160]; struct RigidDynCubeObj_t *ptRigidDynCubeObj[3]; };
    struct { char igi2_o22[172]; struct HumanAIEventContext_t ptEventContext; };
    struct { char igi2_o23[240]; struct QTask_s *v128; };
    struct { char igi2_o24[244]; float v129[10]; };
    struct { char igi2_o25[284]; _DWORD v130[19]; };
    char igi2_extent[360];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *v2; // eax
  int v3; // edx
  int v4; // edx
  int v5; // ebp
  int v6; // esi
  struct QTask_s *ptPrev; // edx
  int v8; // eax
  float *v9; // ebx
  int v10; // edx
  int v11; // eax
  struct QTask_s *v12; // edi
  int v13; // eax
  int v14; // eax
  struct HumanAI_s *v15; // eax
  struct QTask_s *TargetQTask; // eax
  int v17; // edx
  int v18; // ecx
  int v19; // edx
  int v20; // eax
  int v21; // ecx
  int v22; // edi
  struct AmmoType_s *AmmoTypeFromID; // eax
  int v24; // edx
  struct Game_s *v25; // eax
  unsigned int v26; // ecx
  unsigned int v27; // edx
  unsigned int v28; // edi
  double v29; // st7
  long double v30; // st7
  int v31; // ecx
  unsigned int v32; // edx
  long double v33; // st6
  int v34; // edi
  unsigned int v35; // edx
  long double v36; // st6
  long double v37; // rt0
  long double v38; // st6
  long double v39; // st4
  long double v40; // st5
  long double v41; // st7
  double v42; // st6
  double v43; // st5
  long double v44; // st4
  long double v45; // st7
  long double v46; // st3
  long double v47; // st6
  long double v48; // st2
  long double v49; // st5
  float v50; // eax
  int v51; // ecx
  int vX_low; // ecx
  int vX_high; // edx
  int v54; // eax
  _DWORD *v55; // edi
  double v56; // st7
  double v57; // st6
  struct Game_s *v58; // ecx
  unsigned int v59; // eax
  unsigned int v60; // edx
  unsigned int v61; // esi
  double v62; // st5
  double v63; // st7
  int v64; // eax
  unsigned int v65; // edx
  int v66; // esi
  unsigned int v67; // edx
  double v68; // st7
  long double v69; // st7
  double v70; // st6
  double v71; // st6
  double v72; // st7
  struct QTask_s *v73; // edi
  struct QTask_s *ptTail; // edi
  struct QTask_s *ptHead; // edi
  struct real64x3_t *v76; // esi
  int v77; // edi
  int v78; // edi
  struct QTask_s *v79; // edi
  struct QTask_s *v80; // eax
  struct QTask_s *v81; // eax
  struct QTask_s *v82; // eax
  struct QTask_s *v83; // edi
  struct RigidDynCubeObj_t *v84; // ecx
  struct QTask_s *v85; // eax
  void (__cdecl *pfHandler)(struct QTask_s *, struct RigidDynCubeObj_t **); // edx
  struct QReference_s *v87; // esi
  struct QTask_s *v88; // eax
  int v89; // eax
  struct TexInfo_s *v90; // ecx
  int v91; // eax
  struct TexInfo_s *v92; // eax
  unsigned int v93; // eax
  long double v94; // st7
  long double v95; // st7
  double v96; // st6
  long double v97; // st7
  enum TransContext_Layer_e eLayer; // edi
  long double v99; // st5
  struct QTask_s *v100; // eax
  struct QTask_s *v101; // esi
  int v102; // eax
  int v103; // edi
  int v104; // eax

  v2 = *(struct QTask_s **)pxContext;
  v3 = *(_DWORD *)(*(_DWORD *)pxContext + 96);
  if ( !v3 )
  {
    igi2_frame.ptParent.ptParent = nullptr;
    goto LABEL_5;
  }
  v4 = *(_DWORD *)(v3 + 8);
  igi2_frame.ptParent.ptParent = (struct QTask_s *)v4;
  if ( !v4 )
  {
LABEL_5:
    igi2_frame.ptParent.tQTaskRefList.ptTail = nullptr;
    goto LABEL_6;
  }
  igi2_frame.ptParent.tQTaskRefList.ptTail = *(struct QReference_s **)(v4 + 1336);
LABEL_6:
  v5 = *((_DWORD *)pxContext + 25);
  v6 = *(unsigned __int16 *)(v5 + 116);
  ptPrev = v2[1].ptPrev;
  igi2_frame.v128 = v2;
  igi2_frame.v120 = (unsigned int)ptPrev;
  *(_DWORD *)&igi2_frame.ptParent.eQTaskType = v6;
  if ( QTask_IsQTaskTypeValid(v6) == false
    || !QTask_aatQTaskFinalEvent[Weapon_eCreateProjectileQTaskEvent][v6].pfHandler )
  {
    return;
  }
  v8 = *(_DWORD *)(v5 + 200);
  v9 = (float *)((char *)pxContext + 40);
  qmemcpy(igi2_frame.v129, (char *)pxContext + 40, sizeof(igi2_frame.v129));
  if ( v8 )
  {
    v10 = *((_DWORD *)&ptPrev->tQTaskChildren.ptHead + (int)ptPrev->tQTaskRefList.ptMiddle);
    v11 = *(_DWORD *)(v5 + 48);
    if ( v10 < v11 )
      v11 = v10;
    igi2_frame.v106 = v11;
  }
  else
  {
    igi2_frame.v106 = *(_DWORD *)(v5 + 48);
    v11 = igi2_frame.v106;
  }
  if ( v11 > 0 )
  {
    LODWORD(igi2_frame.v123) = (char *)pxContext + 16;
    igi2_frame.v117 = v11;
    do
    {
      v12 = *(struct QTask_s **)pxContext;
      v13 = *(_DWORD *)(*(_DWORD *)pxContext + 96);
      if ( v13 )
        v14 = *(_DWORD *)(v13 + 8);
      else
        v14 = 0;
      igi2_frame.v130[1] = v14;
      if ( v14 && (v15 = *(struct HumanAI_s **)(v14 + 1952)) != nullptr )
        TargetQTask = HumanAI_GetTargetQTask(v15, true);
      else
        TargetQTask = nullptr;
      v17 = *((_DWORD *)pxContext + 1);
      v18 = *(_DWORD *)(v5 + 80);
      igi2_frame.v130[0] = TargetQTask;
      igi2_frame.v130[3] = v17;
      v19 = *(_DWORD *)(v5 + 72);
      *(float *)&igi2_frame.v130[4] = igi2_frame.v123;
      v20 = *((_DWORD *)pxContext + 23);
      igi2_frame.v130[10] = v18;
      v21 = *((_DWORD *)pxContext + 26);
      igi2_frame.v130[2] = v12;
      v22 = *(_DWORD *)(v5 + 40);
      igi2_frame.v130[9] = (char *)pxContext + 40;
      igi2_frame.v130[8] = (char *)pxContext + 40;
      igi2_frame.v130[11] = v19;
      igi2_frame.v130[12] = v20;
      igi2_frame.v130[15] = v21;
      AmmoTypeFromID = AmmoType_GetAmmoTypeFromID(v22);
      v24 = *(_DWORD *)(v5 + 124);
      igi2_frame.v130[16] = AmmoTypeFromID;
      igi2_frame.v130[17] = *(_DWORD *)(v24 + 8);
      if ( igi2_frame.v106 > 1 )
      {
        v25 = Game_ptGame;
        v26 = (Game_ptGame->tRunRandomState.anRandom[0] >> 7) ^ Game_ptGame->tRunRandomState.anRandom[2];
        v27 = v26 ^ Game_ptGame->tRunRandomState.anRandom[1];
        Game_ptGame->tRunRandomState.anRandom[2] = v26;
        v28 = v27 + v25->tRunRandomState.anRandom[0];
        LODWORD(igi2_frame.v125) = (unsigned __int16)(v27 + LOWORD(v25->tRunRandomState.anRandom[0]));
        v29 = (double)(int)igi2_frame.v125;
        v25->tRunRandomState.anRandom[1] = v27;
        v25->tRunRandomState.anRandom[0] = v28;
        v30 = v29 * 0.0000152587890625 * 6.283185307179589;
        v31 = (v25->tRunRandomState.anRandom[0] >> 7) ^ v25->tRunRandomState.anRandom[2];
        v32 = v25->tRunRandomState.anRandom[0];
        v33 = tan(*(float *)(v5 + 112) * 0.01745329238474369);
        v34 = v31 ^ v25->tRunRandomState.anRandom[1];
        v25->tRunRandomState.anRandom[2] = v31;
        v35 = v34 + v32;
        v25->tRunRandomState.anRandom[1] = v34;
        v25->tRunRandomState.anRandom[0] = v35;
        LODWORD(igi2_frame.v125) = (unsigned __int16)v35;
        v36 = v33 * ((double)(unsigned __int16)v35 * 0.0000152587890625);
        igi2_frame.v112 = sin(v30) * v36;
        v37 = v36;
        v38 = cos(v30);
        v39 = sqrt(igi2_frame.v112 * igi2_frame.v112 + v37 * v38 * (v37 * v38) + 1.0);
        igi2_frame.v113 = igi2_frame.v112 * (1.0 / v39);
        v40 = 1.0 / v39;
        igi2_frame.v115 = v40;
        v41 = v37 * v38 * v40;
        igi2_frame.v109 = igi2_frame.v129[1] * igi2_frame.v115 + igi2_frame.v129[0] * igi2_frame.v113 + igi2_frame.v129[2] * v41;
        igi2_frame.v110 = igi2_frame.v129[4] * igi2_frame.v115 + igi2_frame.v129[3] * igi2_frame.v113 + igi2_frame.v129[5] * v41;
        v42 = igi2_frame.v129[7] * igi2_frame.v115;
        igi2_frame.v116 = igi2_frame.v110;
        v43 = igi2_frame.v129[6] * igi2_frame.v113;
        igi2_frame.v114 = igi2_frame.v109;
        igi2_frame.v111 = v42 + v43 + igi2_frame.v129[8] * v41;
        *((float *)&igi2_frame.ptPos.vY + 1) = igi2_frame.v110 * igi2_frame.v129[8] - igi2_frame.v111 * igi2_frame.v129[5];
        igi2_frame.v121 = *((float *)&igi2_frame.ptPos.vY + 1);
        *(float *)&igi2_frame.ptPos.vZ = -(igi2_frame.v109 * igi2_frame.v129[8] - igi2_frame.v111 * igi2_frame.v129[2]);
        *((float *)&igi2_frame.ptPos.vZ + 1) = igi2_frame.v109 * igi2_frame.v129[5] - igi2_frame.v110 * igi2_frame.v129[2];
        igi2_frame.vZ = igi2_frame.ptPos.vZ;
        *(float *)&igi2_frame.ptParent.ptNext = *(float *)&igi2_frame.ptPos.vZ * igi2_frame.v111 - *((float *)&igi2_frame.ptPos.vZ + 1) * igi2_frame.v110;
        LODWORD(igi2_frame.ptPos.vX) = igi2_frame.ptParent.ptNext;
        *(float *)&igi2_frame.ptParent.ptPrev = -(*((float *)&igi2_frame.ptPos.vY + 1) * igi2_frame.v111 - *((float *)&igi2_frame.ptPos.vZ + 1) * igi2_frame.v109);
        HIDWORD(igi2_frame.ptPos.vX) = igi2_frame.ptParent.ptPrev;
        *(float *)&igi2_frame.ptParent.tQTaskChildren.ptHead = *((float *)&igi2_frame.ptPos.vY + 1) * igi2_frame.v110 - *(float *)&igi2_frame.ptPos.vZ * igi2_frame.v109;
        LODWORD(igi2_frame.ptPos.vY) = igi2_frame.ptParent.tQTaskChildren.ptHead;
        if ( *((float *)&igi2_frame.ptPos.vY + 1) == 0.0 && *(float *)&igi2_frame.ptPos.vZ == 0.0 && *((float *)&igi2_frame.ptPos.vZ + 1) == 0.0 )
        {
          v45 = *((float *)&igi2_frame.vZ + 1);
        }
        else
        {
          v44 = sqrt(
                  *(float *)&igi2_frame.ptPos.vZ * *(float *)&igi2_frame.ptPos.vZ
                + *((float *)&igi2_frame.ptPos.vZ + 1) * *((float *)&igi2_frame.ptPos.vZ + 1)
                + *((float *)&igi2_frame.ptPos.vY + 1) * *((float *)&igi2_frame.ptPos.vY + 1));
          igi2_frame.v121 = *((float *)&igi2_frame.ptPos.vY + 1) * (1.0 / v44);
          *(float *)&igi2_frame.vZ = *(float *)&igi2_frame.vZ * (1.0 / v44);
          v45 = 1.0 / v44 * *((float *)&igi2_frame.vZ + 1);
        }
        if ( igi2_frame.v109 == 0.0 && igi2_frame.v110 == 0.0 && igi2_frame.v111 == 0.0 )
        {
          v47 = igi2_frame.v111;
        }
        else
        {
          v46 = sqrt(igi2_frame.v109 * igi2_frame.v109 + igi2_frame.v110 * igi2_frame.v110 + igi2_frame.v111 * igi2_frame.v111);
          igi2_frame.v114 = igi2_frame.v109 * (1.0 / v46);
          igi2_frame.v116 = igi2_frame.v110 * (1.0 / v46);
          v47 = 1.0 / v46 * igi2_frame.v111;
        }
        if ( *(float *)&igi2_frame.ptParent.ptNext == 0.0
          && *(float *)&igi2_frame.ptParent.ptPrev == 0.0
          && *(float *)&igi2_frame.ptParent.tQTaskChildren.ptHead == 0.0 )
        {
          v49 = *(float *)&igi2_frame.ptPos.vY;
        }
        else
        {
          v48 = sqrt(
                  *(float *)&igi2_frame.ptParent.ptNext * *(float *)&igi2_frame.ptParent.ptNext
                + *(float *)&igi2_frame.ptParent.ptPrev * *(float *)&igi2_frame.ptParent.ptPrev
                + *(float *)&igi2_frame.ptParent.tQTaskChildren.ptHead * *(float *)&igi2_frame.ptParent.tQTaskChildren.ptHead);
          *(float *)&igi2_frame.ptPos.vX = *(float *)&igi2_frame.ptParent.ptNext * (1.0 / v48);
          *((float *)&igi2_frame.ptPos.vX + 1) = *((float *)&igi2_frame.ptPos.vX + 1) * (1.0 / v48);
          v49 = 1.0 / v48 * *(float *)&igi2_frame.ptPos.vY;
        }
        v50 = igi2_frame.v121;
        v51 = LODWORD(igi2_frame.vZ);
        *((float *)pxContext + 16) = v45;
        *((float *)pxContext + 17) = v47;
        *v9 = v50;
        *((_DWORD *)pxContext + 13) = v51;
        *((float *)pxContext + 18) = v49;
        vX_low = LODWORD(igi2_frame.ptPos.vX);
        *((float *)pxContext + 11) = igi2_frame.v114;
        vX_high = HIDWORD(igi2_frame.ptPos.vX);
        *((float *)pxContext + 14) = igi2_frame.v116;
        *((_DWORD *)pxContext + 12) = vX_low;
        *((_DWORD *)pxContext + 15) = vX_high;
      }
      ((void (__cdecl *)(_DWORD, _DWORD *))QTask_aatQTaskFinalEvent[Weapon_eCreateProjectileQTaskEvent][*(_DWORD *)&igi2_frame.ptParent.eQTaskType].pfHandler)(
        0,
        igi2_frame.v130);
      --igi2_frame.v117;
    }
    while ( igi2_frame.v117 );
  }
  qmemcpy(v9, igi2_frame.v129, 0x28u);
  v54 = igi2_frame.v106;
  if ( !*(_DWORD *)(v5 + 200) )
    v54 = 1;
  v55 = pxContext;
  *((_DWORD *)pxContext + 28) = v54;
  igi2_frame.v125 = (__int64)(60.0 / (double)*(int *)(v5 + 56) * 30.0 + 0.5);
  *((_DWORD *)pxContext + 29) = igi2_frame.v125;
  v56 = *(float *)(v5 + 88) - *(float *)(v5 + 84);
  *(float *)&igi2_frame.ptParent.eQTaskType = *(float *)(v5 + 96) - *(float *)(v5 + 92);
  v57 = *(float *)(v5 + 84);
  if ( v57 < 0.0 )
    v57 = -v57;
  v58 = Game_ptGame;
  v59 = (Game_ptGame->tRunRandomState.anRandom[0] >> 7) ^ Game_ptGame->tRunRandomState.anRandom[2];
  v60 = v59 ^ Game_ptGame->tRunRandomState.anRandom[1];
  Game_ptGame->tRunRandomState.anRandom[2] = v59;
  v61 = v60 + v58->tRunRandomState.anRandom[0];
  LODWORD(igi2_frame.v125) = (unsigned __int16)(v60 + LOWORD(v58->tRunRandomState.anRandom[0]));
  v62 = (double)(int)igi2_frame.v125;
  v58->tRunRandomState.anRandom[1] = v60;
  v58->tRunRandomState.anRandom[0] = v61;
  igi2_frame.v107 = v62 * 0.0000152587890625 * v56 - v57;
  v63 = *(float *)(v5 + 92);
  if ( v63 < 0.0 )
    v63 = -v63;
  v64 = (v58->tRunRandomState.anRandom[0] >> 7) ^ v58->tRunRandomState.anRandom[2];
  v65 = v58->tRunRandomState.anRandom[0];
  v66 = v64 ^ v58->tRunRandomState.anRandom[1];
  v58->tRunRandomState.anRandom[2] = v64;
  v67 = v66 + v65;
  v58->tRunRandomState.anRandom[1] = v66;
  v58->tRunRandomState.anRandom[0] = v67;
  LODWORD(igi2_frame.v125) = (unsigned __int16)v67;
  igi2_frame.v118 = (double)(unsigned __int16)v67 * 0.0000152587890625 * *(float *)&igi2_frame.ptParent.eQTaskType - v63;
  v68 = (double)*((int *)pxContext + 27) / *(float *)(v5 + 104);
  if ( v68 <= 1.0 )
    igi2_frame.v123 = v68;
  else
    igi2_frame.v123 = 1.0;
  v69 = pow(igi2_frame.v123, *(float *)(v5 + 108)) + *(float *)(v5 + 100);
  if ( v69 >= 0.0 )
  {
    if ( v69 > 1.0 )
      v69 = 1.0;
  }
  else
  {
    v69 = 0.0;
  }
  if ( *(float *)(v5 + 84) <= (double)igi2_frame.v107 )
  {
    if ( *(float *)(v5 + 88) >= (double)igi2_frame.v107 )
      v70 = igi2_frame.v107;
    else
      v70 = *(float *)(v5 + 88);
  }
  else
  {
    v70 = *(float *)(v5 + 84);
  }
  *((float *)pxContext + 32) = v70 * v69;
  if ( *(float *)(v5 + 92) <= (double)igi2_frame.v118 )
  {
    if ( *(float *)(v5 + 96) >= (double)igi2_frame.v118 )
      v71 = igi2_frame.v118;
    else
      v71 = *(float *)(v5 + 96);
  }
  else
  {
    v71 = *(float *)(v5 + 92);
  }
  *((float *)pxContext + 33) = v71 * v69;
  *((_DWORD *)pxContext + 30) = *(_DWORD *)(v5 + 64);
  *((_DWORD *)pxContext + 31) = *(_DWORD *)(v5 + 68);
  v72 = *(float *)(v5 + 72) * 4096.0;
  *(float *)&igi2_frame.ptParent.ptNext = (*((float *)pxContext + 12) + *v9) * 0.0 + v72 * *((float *)pxContext + 11);
  *(float *)&igi2_frame.ptParent.ptPrev = (*((float *)pxContext + 15) + *((float *)pxContext + 13)) * 0.0
                             + v72 * *((float *)pxContext + 14);
  *(float *)&igi2_frame.ptParent.tQTaskChildren.ptHead = (*((float *)pxContext + 18) + *((float *)pxContext + 16)) * 0.0
                                            + v72 * *((float *)pxContext + 17);
  if ( *(float *)(v5 + 756) > 20480.0 )
  {
    v73 = *(struct QTask_s **)pxContext;
    igi2_frame.ptEventContext.ptPosition = (struct real64x3_t *)((char *)pxContext + 16);
    igi2_frame.ptEventContext.eEvent = 39;
    igi2_frame.ptEventContext.bFlags = 706;
    igi2_frame.ptEventContext.vRadius = 614400.0;
    LODWORD(igi2_frame.ptEventContext.tDirection.vX) = igi2_frame.ptParent.ptNext;
    LODWORD(igi2_frame.ptEventContext.tDirection.vY) = igi2_frame.ptParent.ptPrev;
    LODWORD(igi2_frame.ptEventContext.tDirection.vZ) = igi2_frame.ptParent.tQTaskChildren.ptHead;
    igi2_frame.ptEventContext.ptReferenceQTask = v73;
    igi2_frame.ptEventContext.eTeam = (int)v73[2].tQTaskChildren.ptMiddle;
    ptTail = v73[2].tQTaskChildren.ptTail;
    if ( ptTail )
      ptHead = ptTail->tQTaskChildren.ptHead;
    else
      ptHead = nullptr;
    igi2_frame.ptEventContext.ptHumanOriginatorQTask = ptHead;
    HumanAI_SendEvent(&igi2_frame.ptEventContext);
    v55 = pxContext;
  }
  igi2_frame.ptEventContext.eEvent = 15;
  igi2_frame.ptEventContext.bFlags = 1090;
  igi2_frame.ptEventContext.vRadius = *(float *)(v5 + 756);
  v76 = (struct real64x3_t *)(v55 + 4);
  v77 = *v55;
  igi2_frame.ptEventContext.ptPosition = v76;
  LODWORD(igi2_frame.ptEventContext.tDirection.vX) = igi2_frame.ptParent.ptNext;
  LODWORD(igi2_frame.ptEventContext.tDirection.vY) = igi2_frame.ptParent.ptPrev;
  LODWORD(igi2_frame.ptEventContext.tDirection.vZ) = igi2_frame.ptParent.tQTaskChildren.ptHead;
  igi2_frame.ptEventContext.ptReferenceQTask = (struct QTask_s *)v77;
  igi2_frame.ptEventContext.eTeam = *(_DWORD *)(v77 + 92);
  v78 = *(_DWORD *)(v77 + 96);
  if ( v78 )
    v79 = *(struct QTask_s **)(v78 + 8);
  else
    v79 = nullptr;
  igi2_frame.ptEventContext.ptHumanOriginatorQTask = v79;
  HumanAI_SendEvent(&igi2_frame.ptEventContext);
  igi2_frame.ptEventContext.eEvent = 23;
  igi2_frame.ptEventContext.bFlags = 1314;
  igi2_frame.ptEventContext.vRadius = *(float *)(v5 + 756);
  qmemcpy(&igi2_frame.ptEventContext.uEventSpecificData, v76, sizeof(igi2_frame.ptEventContext.uEventSpecificData));
  LODWORD(igi2_frame.ptEventContext.tDirection.vX) = igi2_frame.ptParent.ptNext;
  igi2_frame.ptEventContext.ptPosition = (struct real64x3_t *)&igi2_frame.ptEventContext.uEventSpecificData;
  LODWORD(igi2_frame.ptEventContext.tDirection.vY) = igi2_frame.ptParent.ptPrev;
  v80 = *(struct QTask_s **)pxContext;
  LODWORD(igi2_frame.ptEventContext.tDirection.vZ) = igi2_frame.ptParent.tQTaskChildren.ptHead;
  igi2_frame.ptEventContext.ptReferenceQTask = v80;
  igi2_frame.ptEventContext.eTeam = (int)v80[2].tQTaskChildren.ptMiddle;
  v81 = v80[2].tQTaskChildren.ptTail;
  if ( v81 )
    v82 = v81->tQTaskChildren.ptHead;
  else
    v82 = nullptr;
  igi2_frame.ptEventContext.ptHumanOriginatorQTask = v82;
  HumanAI_SendEvent(&igi2_frame.ptEventContext);
  if ( igi2_frame.ptEventContext.ptHumanOriginatorQTask && *(float *)(v5 + 756) > 20480.0 )
    igi2_frame.ptEventContext.ptHumanOriginatorQTask[49].tQTaskChildren.ptTail = (struct QTask_s *)15;
  v83 = igi2_frame.v128;
  v84 = nullptr;
  igi2_frame.ptRigidDynCubeObj[0] = nullptr;
  igi2_frame.ptRigidDynCubeObj[2] = nullptr;
  igi2_frame.ptRigidDynCubeObj[1] = (struct RigidDynCubeObj_t *)((int)igi2_frame.v128[1].tQTaskRefList.ptTail % 2);
  v85 = igi2_frame.v128->ptParent;
  pfHandler = (void (__cdecl *)(struct QTask_s *, struct RigidDynCubeObj_t **))QTask_aatQTaskFinalEvent[Weapon_eGetWeaponObjectEvent][v85->eQTaskType].pfHandler;
  if ( pfHandler )
  {
    pfHandler(v85, igi2_frame.ptRigidDynCubeObj);
    v84 = igi2_frame.ptRigidDynCubeObj[0];
  }
  if ( AppContext_tAppContext.isServer == false )
  {
    v87 = igi2_frame.ptParent.tQTaskRefList.ptTail;
    if ( v84 && (!igi2_frame.ptParent.tQTaskRefList.ptTail || !igi2_frame.ptParent.tQTaskRefList.ptTail[55].ptPrev) )
    {
      v88 = igi2_frame.ptParent.ptParent;
      if ( igi2_frame.ptParent.ptParent )
      {
        igi2_frame.ptParent.ptParent[51].ptPrev = (struct QTask_s *)1065353216;
        v88[51].tQTaskChildren.ptHead = (struct QTask_s *)1061997773;
        v88[51].tQTaskChildren.ptMiddle = (struct QTask_s *)1056964608;
      }
      v89 = *(_DWORD *)(v5 + 208);
      if ( v89 )
        v90 = (struct TexInfo_s *)(v89 + 24);
      else
        v90 = nullptr;
      v91 = *(_DWORD *)(v5 + 204);
      if ( v91 )
        v92 = (struct TexInfo_s *)(v91 + 24);
      else
        v92 = nullptr;
      MuzzleFlash_New(v83, v92, v90, *(float *)(v5 + 60), (int)v83[1].tQTaskRefList.ptTail % 2);
      if ( AppContext_tAppContext.isServer )
        goto LABEL_102;
      v84 = igi2_frame.ptRigidDynCubeObj[0];
    }
    if ( *(_BYTE *)(v5 + 596) && v84 && igi2_frame.ptParent.ptParent && (!v87 || !v87[55].ptPrev) )
    {
      RigidDynCubeObj_GetMagicVertexPos(v84, 3u, (struct real64x3_t *)&igi2_frame.ptParent);
      v93 = Random_GetRandomNumberBelowLimit(&Game_ptGame->tRunRandomState, 20) - 10;
      if ( *(_DWORD *)(*(_DWORD *)(igi2_frame.v120 + 16) + 668) )
      {
        igi2_frame.v120 = v93 + 60;
        v97 = (double)(int)(v93 + 60) * 0.01745329238474369;
        igi2_frame.v108 = v97;
        v95 = cos(v97) * 273.0666809082031;
        v96 = 0.0;
      }
      else
      {
        igi2_frame.v120 = v93 + 30;
        v94 = (double)(int)(v93 + 30) * 0.01745329238474369;
        igi2_frame.v108 = v94;
        v95 = cos(v94) * 273.0666809082031;
        v96 = 273.0666809082031;
      }
      eLayer = igi2_frame.ptRigidDynCubeObj[0]->tModelObj.eLayer;
      v99 = sin(igi2_frame.v108) * 273.0666809082031;
      igi2_frame.v121 = v99 * igi2_frame.ptRigidDynCubeObj[0]->tModelObj.tOrientation.tX.vZ
           + v96 * igi2_frame.ptRigidDynCubeObj[0]->tModelObj.tOrientation.tX.vY
           + v95 * igi2_frame.ptRigidDynCubeObj[0]->tModelObj.tOrientation.tX.vX;
      *(float *)&igi2_frame.ptPos.vX = igi2_frame.v121;
      *(float *)&igi2_frame.vZ = v99 * igi2_frame.ptRigidDynCubeObj[0]->tModelObj.tOrientation.tY.vZ
                    + v96 * igi2_frame.ptRigidDynCubeObj[0]->tModelObj.tOrientation.tY.vY
                    + v95 * igi2_frame.ptRigidDynCubeObj[0]->tModelObj.tOrientation.tY.vX;
      HIDWORD(igi2_frame.ptPos.vX) = LODWORD(igi2_frame.vZ);
      *((float *)&igi2_frame.vZ + 1) = v99 * igi2_frame.ptRigidDynCubeObj[0]->tModelObj.tOrientation.tZ.vZ
                          + v96 * igi2_frame.ptRigidDynCubeObj[0]->tModelObj.tOrientation.tZ.vY
                          + v95 * igi2_frame.ptRigidDynCubeObj[0]->tModelObj.tOrientation.tZ.vX;
      LODWORD(igi2_frame.ptPos.vY) = HIDWORD(igi2_frame.vZ);
      *(float *)&igi2_frame.ptPos.vX = igi2_frame.v121 + *(float *)&v87[63].ptPrev;
      *((float *)&igi2_frame.ptPos.vX + 1) = *(float *)&igi2_frame.vZ + *(float *)&v87[63].pxObject;
      igi2_frame.p_tOrientation = &igi2_frame.ptRigidDynCubeObj[0]->tModelObj.tOrientation;
      *(float *)&igi2_frame.ptPos.vY = *((float *)&igi2_frame.vZ + 1) + *(float *)&v87[64].ptNext;
      v100 = (struct QTask_s *)sub_52B6B0();
      GunCasing_New(
        v100,
        (struct real64x3_t *)&igi2_frame.ptParent,
        (struct real32x3_t *)&igi2_frame.ptPos,
        igi2_frame.p_tOrientation,
        (char *)(v5 + 596),
        eLayer == TRANSCONTEXT_LAYER_FRONT);
    }
  }
LABEL_102:
  v101 = *(struct QTask_s **)pxContext;
  v102 = *(_DWORD *)(*(_DWORD *)pxContext + 44);
  if ( v102 )
    v103 = *(_DWORD *)(v102 + 24);
  else
    v103 = 0;
  if ( *(_BYTE *)(v103 + v5 + 760) )
  {
    v104 = *((_DWORD *)pxContext + 23);
    if ( *(_DWORD *)(*((_DWORD *)pxContext + 26) + 4 * v103 + 712) == *(_DWORD *)(v5 + 52) )
    {
      if ( !v104 )
        Weapon_PlaySound(v101, 0, (char *)(32 * v103 + v5 + 628), true);
    }
    else if ( !v104 )
    {
      Weapon_ClearSoundSequence(v101);
      Weapon_AddSoundToSoundSequence(
        *(struct QTask_s **)pxContext,
        (char *)(32 * v103 + v5 + 628),
        *(float *)(*((_DWORD *)pxContext + 26) + 4 * v103 + 820));
      Weapon_AddSoundToSoundSequence(*(struct QTask_s **)pxContext, (char *)(v5 + 724), -1.0);
    }
  }
  else if ( !*((_DWORD *)pxContext + 23) )
  {
    Weapon_PlaySound(v101, 0, (char *)(32 * v103 + v5 + 628), false);
  }
}

void __cdecl sub_48CFD0(struct QTask_s *a1, _DWORD *a2)
{
  int v2; // eax
  int v3; // ecx
  int v4; // ecx

  v2 = a2[24];
  v3 = *(_DWORD *)(*a2 + 44);
  if ( v3 )
    v4 = *(_DWORD *)(v3 + 24);
  else
    v4 = 0;
  if ( *(_BYTE *)(v4 + v2 + 760) )
  {
    if ( *(_DWORD *)(a2[25] + 4 * v4 + 712) == *(_DWORD *)(v2 + 52) )
      Weapon_PlaySound((struct QTask_s *)*a2, 0, (char *)(v2 + 724), false);
  }
}

// source: j/0/weapons/gun.c:940  [anchor-strings]
void __cdecl Gun_StatusDisplayHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { char zText[16]; };
    struct { char igi2_o1[16]; struct WeaponTypeGetFireTypeScreenPositionContext_s tPositionContext; };
    char igi2_extent[44];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v2; // ebp
  struct AmmoType_s *AmmoTypeFromID; // eax
  struct AmmoTypeItem_s *AmmoTypeItemFromAmmoType; // eax
  float *v5; // edi
  int v6; // ecx
  int v7; // esi
  __int16 *v8; // eax
  void *pxContexta = *(void * *)&pxContext; // [esp+48h] [ebp+8h] ARGSLOT

  v2 = **((_DWORD **)pxContext + 1);
  AmmoTypeFromID = AmmoType_GetAmmoTypeFromID(*(_DWORD *)(*((_DWORD *)pxContext + 6) + 40));
  if ( AmmoTypeFromID )
  {
    AmmoTypeItemFromAmmoType = Weapon_GetAmmoTypeItemFromAmmoType(
                                 *(struct QTask_s **)pxContext,
                                 AmmoTypeFromID->zAmmoTypeScriptID);
    if ( AmmoTypeItemFromAmmoType )
    {
      sprintf(igi2_frame.zText, "%4d/%4d", *(_DWORD *)(*((_DWORD *)pxContext + 5) + 20), AmmoTypeItemFromAmmoType->nAmmoCount);
      Text_SetString(*(struct StaticTilemap_s **)(v2 + 1136), igi2_frame.zText);
      v5 = *(float **)(v2 + 1136);
      igi2_frame.tPositionContext.tIn.nFireType = *((_DWORD *)pxContext + 2);
      v6 = *(__int16 *)(*(_DWORD *)v5 + 6);
      v7 = 0;
      pxContexta = nullptr;
      if ( v6 > 0 )
      {
        v8 = *(__int16 **)(*(_DWORD *)v5 + 12);
        do
        {
          if ( *v8 > v7 )
            v7 = *v8;
          ++v8;
          --v6;
        }
        while ( v6 );
        pxContexta = (void *)v7;
      }
      igi2_frame.tPositionContext.tIn.vTextWidth = (float)(int)pxContexta;
      WeaponType_GetFireTypeScreenPosition(&igi2_frame.tPositionContext);
      v5[1] = (float)(__int64)igi2_frame.tPositionContext.tOut.vTextXPos;
      *(float *)(*(_DWORD *)(v2 + 1136) + 8) = (float)(__int64)igi2_frame.tPositionContext.tOut.vTextYPos;
      Text_Register(*(struct StaticTilemap_s **)(v2 + 1136));
    }
  }
}

// source: j/0/weapons/gun.c:1085  [size]
unsigned __int16 __cdecl Gun_GetQTaskType()
{
  return Gun_eQTaskType;
}

// source: j/0/weapons/gun.c:1099  [anchor-hash]
void __cdecl Gun_Open()
{
  unsigned __int16 v0; // si
  struct ParameterList_s *v1; // eax
  int v2; // edx

  v0 = QTask_NewQTaskType(off_695A10, 764, FireType_eQTaskType, 0, 0);
  Gun_eQTaskType = v0;
  QTask_LinkQTaskEventHandlerFn(
    v0,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveHandler);
  QTask_LinkQTaskEventHandlerFn(v0, 0, Gun_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 2, Gun_DeleteHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(
    v0,
    Level_eUpdateInternalDataAfterLoadEvent,
    Gun_UpdaterInternalDataAfterLoadHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Gun_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(v0, ParameterList_eUpdateInternalDataQTaskEvent, Gun_UpdateInternalDataHandler);
  QTask_LinkQTaskEventHandlerFn(v0, WeaponType_eCreateParametersQTaskEvent, Gun_CreateWeaponTypeParametersHandler);
  QTask_LinkQTaskEventHandlerFn(v0, WeaponType_eDeleteParametersQTaskEvent, Gun_DeleteWeaponTypeParametersHandler);
  QTask_LinkQTaskEventHandlerFn(v0, WeaponType_eGetAnimQTaskEvent, Gun_GetAnimHandler);
  QTask_LinkQTaskEventHandlerFn(v0, WeaponType_eGetAmmoInfoQTaskEvent, Gun_GetAmmoInfoHandler);
  QTask_LinkQTaskEventHandlerFn(v0, Weapon_eFireQTaskEvent, Gun_WeaponFireHandler);
  QTask_LinkQTaskEventHandlerFn(v0, Weapon_eReleaseQTaskEvent, (void (__cdecl *)(struct QTask_s *, void *))sub_48CFD0);
  QTask_LinkQTaskEventHandlerFn(v0, StatusScreen_eStatusDisplayQTaskEvent, Gun_StatusDisplayHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    TagItem_eUpdateTagItemQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Gun_UpdateTagItemsHandler);
  v1 = (struct ParameterList_s *)Mem_AllocFn(892, 4);
  v1->ptParameterListItem = (struct ParameterListItem_s *)&v1[1];
  v2 = ParameterEnumList_eParameterTypeInt32;
  v1->nParameters = 0;
  v1->nMaxParameters = 44;
  Gun_ptParameterList = v1;
  ParameterList_AddParameter(v1, 0x28u, v2, "AmmoType ID", 7u, &AmmoType_tEnumList);
  ParameterList_AddParameter(
    Gun_ptParameterList,
    0x2Cu,
    ParameterEnumList_eParameterTypeInt32,
    "Ammo Display Type",
    7u,
    &WeaponType_tAmmoDisplayTypeEnumList);
  ParameterList_AddParameter(Gun_ptParameterList, 0x30u, Level_eParameterTypeInt32, "Bullets Per Round", 7u, nullptr);
  ParameterList_AddParameter(Gun_ptParameterList, 0x34u, Level_eParameterTypeInt32, "Rounds Per Clip", 7u, nullptr);
  ParameterList_AddParameter(Gun_ptParameterList, 0x38u, Level_eParameterTypeInt32, "Rounds Per Minute", 7u, nullptr);
  ParameterList_AddParameter(
    Gun_ptParameterList,
    0x48u,
    Level_eParameterTypeReal32,
    "Effective Range (Meters)",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Gun_ptParameterList,
    0x4Cu,
    Level_eParameterTypeReal32,
    "Reload Time (In Seconds)",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Gun_ptParameterList,
    0x50u,
    Level_eParameterTypeReal32,
    "Muzzle Velocity (m/s)",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Gun_ptParameterList,
    0x80u,
    Level_eParameterTypeString32,
    "Muzzle flash front sprite",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Gun_ptParameterList,
    0xA0u,
    Level_eParameterTypeString32,
    "Muzzle flash side sprite",
    7u,
    nullptr);
  ParameterList_AddParameterMinMax(
    Gun_ptParameterList,
    0x3Cu,
    Level_eParameterTypeReal32,
    "Muzzle flash size",
    7u,
    0.1,
    1.0);
  ParameterList_AddParameter(
    Gun_ptParameterList,
    0x54u,
    Level_eParameterTypeReal32,
    "Min Alpha Kickback (In Degress)",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Gun_ptParameterList,
    0x58u,
    Level_eParameterTypeReal32,
    "Max Alpha Kickback (In Degress)",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Gun_ptParameterList,
    0x5Cu,
    Level_eParameterTypeReal32,
    "Min Gamma Kickback (In Degress)",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Gun_ptParameterList,
    0x60u,
    Level_eParameterTypeReal32,
    "Max Gamma Kickback (In Degress)",
    7u,
    nullptr);
  ParameterList_AddParameterMinMax(
    Gun_ptParameterList,
    0x64u,
    Level_eParameterTypeReal32,
    "Kickback factor floor",
    7u,
    0.0,
    1.0);
  ParameterList_AddParameterMinMax(
    Gun_ptParameterList,
    0x68u,
    Level_eParameterTypeReal32,
    "Kickback factor attack time",
    7u,
    1.0,
    100.0);
  ParameterList_AddParameterMinMax(
    Gun_ptParameterList,
    0x6Cu,
    Level_eParameterTypeReal32,
    "Kickback factor acceleration",
    7u,
    1.0,
    20.0);
  ParameterList_AddParameterMinMax(
    Gun_ptParameterList,
    0x40u,
    Level_eParameterTypeReal32,
    "Kickback damping factor",
    7u,
    0.0,
    1.0);
  ParameterList_AddParameterMinMax(
    Gun_ptParameterList,
    0x44u,
    Level_eParameterTypeReal32,
    "Crosshair damping factor",
    7u,
    0.0,
    1.0);
  ParameterList_AddParameter(
    Gun_ptParameterList,
    0x74u,
    ParameterEnumList_eParameterTypeInt32,
    "Projectile TaskType",
    7u,
    &WeaponType_tTaskTypeEnumList);
  ParameterList_AddParameter(
    Gun_ptParameterList,
    0x254u,
    Level_eParameterTypeString32,
    "Bullet casing model",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Gun_ptParameterList,
    0xD4u,
    Level_eParameterTypeString32,
    "1st Person Fire Anim",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Gun_ptParameterList,
    0xF4u,
    Level_eParameterTypeString32,
    "1st Person Fire Hold Anim",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Gun_ptParameterList,
    0x114u,
    Level_eParameterTypeString32,
    "1st Person Fire Release Anim",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Gun_ptParameterList,
    0x134u,
    Level_eParameterTypeString32,
    "1st Person Reload Start Anim",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Gun_ptParameterList,
    0x154u,
    Level_eParameterTypeString32,
    "1st Person Reload Hold Anim",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Gun_ptParameterList,
    0x174u,
    Level_eParameterTypeString32,
    "1st Person Reload End Anim",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Gun_ptParameterList,
    0x194u,
    Level_eParameterTypeString32,
    "3rd Person Fire Anim",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Gun_ptParameterList,
    0x1B4u,
    Level_eParameterTypeString32,
    "3rd Person Fire Hold Anim",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Gun_ptParameterList,
    0x1D4u,
    Level_eParameterTypeString32,
    "3rd Person Fire Release Anim",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Gun_ptParameterList,
    0x1F4u,
    Level_eParameterTypeString32,
    "3rd Person Reload Start Anim",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Gun_ptParameterList,
    0x214u,
    Level_eParameterTypeString32,
    "3rd Person Reload Hold Anim",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Gun_ptParameterList,
    0x234u,
    Level_eParameterTypeString32,
    "3rd Person Reload End Anim",
    7u,
    nullptr);
  ParameterList_AddParameterArray(
    Gun_ptParameterList,
    0x274u,
    Level_eParameterTypeString32,
    "Fire Sound 1",
    7u,
    nullptr,
    0x20u,
    3u);
  ParameterList_AddParameterArray(
    Gun_ptParameterList,
    0x2F8u,
    Level_eParameterTypebool8,
    "Play Fire Sound Looped",
    7u,
    nullptr,
    1u,
    3u);
  ParameterList_AddParameter(Gun_ptParameterList, 0x2D4u, Level_eParameterTypeString32, "Fire Sound 2", 7u, nullptr);
  ParameterList_AddParameter(
    Gun_ptParameterList,
    0x2F4u,
    ParameterEnumList_eParameterTypeReal32,
    "AI Detection Range",
    7u,
    &WeaponType_tAIDetectionRangeEnumList);
  ParameterList_AddParameter(
    Gun_ptParameterList,
    0xC8u,
    Level_eParameterTypebool8,
    "Count bullets per round as rounds",
    7u,
    nullptr);
  ParameterList_AddParameter(
    Gun_ptParameterList,
    0x70u,
    Level_eParameterTypeReal32,
    "Bullets per round Spread (In Degrees)",
    7u,
    nullptr);
  Symbol_Register(
    "TASKTYPE_GUN",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)Gun_eQTaskType,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
}

// source: j/0/weapons/gun.c:1182  [size]
void __cdecl Gun_Close()
{
  int v0; // esi

  if ( Gun_ptParameterList )
  {
    v0 = *(_DWORD *)((unsigned int)&Gun_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
  QTask_DeleteQTaskType(Gun_eQTaskType);
}
