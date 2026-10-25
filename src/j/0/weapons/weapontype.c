/* j/0/weapons/weapontype.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/weapons/weapontype.c:203  [anchor-mhash]
void __cdecl WeaponType_UnloadInternalSprites(struct WeaponType_s *ptWeaponType)
{
  if ( ptWeaponType->isWeaponSpriteLoaded )
  {
    QSprite_DeAlloc(&ptWeaponType->tWeaponSprite);
    ptWeaponType->isWeaponSpriteLoaded = false;
  }
  if ( ptWeaponType->isWeaponPickupSpriteLoaded )
  {
    QSprite_DeAlloc(&ptWeaponType->tWeaponPickupSprite);
    ptWeaponType->isWeaponPickupSpriteLoaded = false;
  }
}

// source: j/0/weapons/weapontype.c:225  [anchor-hash]
struct WeaponTypeFireType_s *__cdecl WeaponType_InitFireType(
        struct WeaponTypeFireType_s *ptFireType)
{
  ptFireType->eQTaskType = 512;
  ptFireType->eOldQTaskType = 512;
  ptFireType->ptParametersQTaskRef = nullptr;
  ptFireType->ptContainer = nullptr;
  ptFireType->isForceReload = 1;
  ptFireType->isReloadRoundsIndividually = 0;
  return ptFireType;
}

// source: j/0/weapons/weapontype.c:244  [anchor-hash]
void __cdecl WeaponType_DeInitFireType(struct WeaponTypeFireType_s *ptFireType)
{
  struct QReference_s *ptParametersQTaskRef; // eax
  struct QTask_s *pxObject; // eax
  struct QReference_s *v3; // eax

  ptParametersQTaskRef = ptFireType->ptParametersQTaskRef;
  if ( ptParametersQTaskRef )
  {
    pxObject = (struct QTask_s *)ptParametersQTaskRef->pxObject;
    if ( pxObject )
      QTask_Delete(pxObject);
  }
  v3 = ptFireType->ptParametersQTaskRef;
  if ( v3 )
  {
    QReference_Delete(v3, &QTask_tQTaskRefPool);
    ptFireType->ptParametersQTaskRef = nullptr;
  }
}

// source: j/0/weapons/weapontype.c:263  [anchor-mhash]
void __cdecl WeaponType_UpdateFireType(
        struct WeaponTypeFireType_s *ptFireType,
        struct WeaponType_s *ptWeaponType,
        int nParameterID)
{
  int v3; // ecx
  struct WeaponTypeParameterContainerCreateContext_s tContext; // [esp+0h] [ebp-4h] BYREF

  tContext.nParameterID = v3;
  if ( ptFireType->eQTaskType != ptFireType->eOldQTaskType )
  {
    WeaponType_DeleteParameters(&ptFireType->ptParametersQTaskRef);
    if ( !ptFireType->ptContainer )
    {
      tContext.nParameterID = nParameterID;
      ptFireType->ptContainer = QTask_NewFn(&ptWeaponType->tQTask, WeaponTypeParameterContainer_eQTaskType, &tContext);
    }
    ptFireType->ptParametersQTaskRef = WeaponType_CreateParameters(ptFireType->eQTaskType, ptFireType->ptContainer);
    ptFireType->eOldQTaskType = ptFireType->eQTaskType;
  }
}

// source: j/0/weapons/weapontype.c:297  [anchor-mhash]
void __cdecl WeaponType_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QReference_s *v2; // eax
  struct QReferenceList_s *p_tQTaskRefList; // eax
  struct QTask_s **p_ptPrev; // ecx
  int v5; // edx

  v2 = (struct QReference_s *)WeaponType_nWeaponType;
  strcpy((char *)&ptQTask[2].ptPrev, "WEAPON_ID_UNDEFINED");
  ptQTask[3].tQTaskRefList.ptTail = v2;
  LOBYTE(ptQTask[2].eQTaskType) = 0;
  ptQTask[3].ptParent = nullptr;
  LOBYTE(ptQTask[3].eQTaskType) = 0;
  LOBYTE(ptQTask[10].tQTaskChildren.ptMiddle) = 0;
  LOBYTE(ptQTask[33].tQTaskRefList.ptHead) = 0;
  ptQTask[40].tQTaskRefList.ptHead = nullptr;
  ptQTask[16].tQTaskRefList.ptTail = nullptr;
  ptQTask[21].ptNext = nullptr;
  ptQTask[21].ptPrev = nullptr;
  ptQTask[21].tQTaskChildren.ptHead = nullptr;
  ptQTask[21].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[21].tQTaskChildren.ptTail = nullptr;
  ptQTask[21].tQTaskRefList.ptHead = nullptr;
  ptQTask[21].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[21].tQTaskRefList.ptTail = nullptr;
  ptQTask[21].ptParent = nullptr;
  *(_DWORD *)&ptQTask[21].eQTaskType = 0;
  ptQTask[22].ptNext = (struct QTask_s *)1056964608;
  LOBYTE(ptQTask[22].ptPrev) = 0;
  LOBYTE(ptQTask[22].eQTaskType) = 0;
  LOBYTE(ptQTask[23].tQTaskRefList.ptTail) = 0;
  LOBYTE(ptQTask[24].tQTaskRefList.ptHead) = 0;
  LOBYTE(ptQTask[25].tQTaskChildren.ptMiddle) = 0;
  LOBYTE(ptQTask[26].ptPrev) = 0;
  LOBYTE(ptQTask[26].eQTaskType) = 0;
  LOBYTE(ptQTask[27].tQTaskRefList.ptTail) = 0;
  LOBYTE(ptQTask[28].tQTaskRefList.ptHead) = 0;
  LOBYTE(ptQTask[29].tQTaskChildren.ptMiddle) = 0;
  LOBYTE(ptQTask[30].ptPrev) = 0;
  LOBYTE(ptQTask[30].eQTaskType) = 0;
  LOBYTE(ptQTask[31].tQTaskRefList.ptTail) = 0;
  WeaponType_nWeaponType = (int)&v2->ptNext + 1;
  ptQTask[17].tQTaskRefList.ptTail = (struct QReference_s *)1;
  ptQTask[32].tQTaskRefList.ptHead = (struct QReference_s *)512;
  ptQTask[32].tQTaskRefList.ptMiddle = (struct QReference_s *)512;
  ptQTask[32].ptParent = nullptr;
  *(_DWORD *)&ptQTask[32].eQTaskType = 0;
  LOBYTE(ptQTask[32].tQTaskRefList.ptTail) = 1;
  BYTE1(ptQTask[32].tQTaskRefList.ptTail) = 0;
  ptQTask[33].ptNext = (struct QTask_s *)512;
  ptQTask[33].ptPrev = (struct QTask_s *)512;
  LOWORD(v2) = WeaponTypeAnim_eQTaskType;
  ptQTask[33].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[33].tQTaskChildren.ptTail = nullptr;
  LOBYTE(ptQTask[33].tQTaskChildren.ptHead) = 1;
  BYTE1(ptQTask[33].tQTaskChildren.ptHead) = 0;
  LOBYTE(ptQTask[20].eQTaskType) = 0;
  ptQTask[48].ptPrev = nullptr;
  LOBYTE(ptQTask[40].tQTaskRefList.ptMiddle) = 0;
  ptQTask[48].tQTaskChildren.ptHead = QTask_NewFn(ptQTask, (unsigned __int16)v2, nullptr);
  ptQTask[48].tQTaskChildren.ptMiddle = QTask_NewFn(ptQTask, WeaponTypeAnim_eQTaskType, nullptr);
  LOBYTE(ptQTask[1].ptNext) = 0;
  ptQTask[1].ptParent = (struct QTask_s *)1117126656;
  *(_DWORD *)&ptQTask[1].eQTaskType = 0;
  ptQTask[2].ptNext = nullptr;
  ptQTask[47].tQTaskRefList.ptMiddle = (struct QReference_s *)90;
  ptQTask[47].ptParent = (struct QTask_s *)-1;
  *(_DWORD *)&ptQTask[47].eQTaskType = -1;
  BYTE1(ptQTask[47].tQTaskRefList.ptTail) = 0;
  LOBYTE(ptQTask[47].tQTaskRefList.ptTail) = 0;
  ptQTask[16].ptParent = (struct QTask_s *)1;
  p_tQTaskRefList = &ptQTask[20].tQTaskRefList;
  p_ptPrev = &ptQTask[18].ptPrev;
  v5 = 3;
  do
  {
    p_tQTaskRefList[-9].ptHead = (struct QReference_s *)1;
    *(_BYTE *)p_ptPrev = 0;
    p_tQTaskRefList->ptHead = nullptr;
    p_tQTaskRefList = (struct QReferenceList_s *)((char *)p_tQTaskRefList + 4);
    p_ptPrev += 8;
    --v5;
  }
  while ( v5 );
  ptQTask[20].ptParent = (struct QTask_s *)1;
  LOBYTE(ptQTask[48].ptNext) = 0;
  LOBYTE(ptQTask[48].tQTaskChildren.ptTail) = 0;
  BYTE1(ptQTask[48].tQTaskChildren.ptTail) = 0;
  ptQTask[48].tQTaskRefList.ptHead = (struct QReference_s *)1025758986;
  LOBYTE(ptQTask[48].tQTaskRefList.ptMiddle) = 1;
}

// source: j/0/weapons/weapontype.c:410  [anchor-mhash]
void __cdecl WeaponType_DeleteHandler(struct QTask_s *ptQTask)
{
  struct QReference_s **p_ptParent; // esi
  int v2; // ebx

  WeaponType_aptWeaponTypeByIDCache[(int)ptQTask[3].tQTaskRefList.ptTail] = nullptr;
  p_ptParent = (struct QReference_s **)&ptQTask[32].ptParent;
  v2 = 2;
  do
  {
    if ( *p_ptParent && (*p_ptParent)->pxObject )
      QTask_Delete((struct QTask_s *)(*p_ptParent)->pxObject);
    if ( *p_ptParent )
    {
      QReference_Delete(*p_ptParent, &QTask_tQTaskRefPool);
      *p_ptParent = nullptr;
    }
    p_ptParent += 5;
    --v2;
  }
  while ( v2 );
  if ( ptQTask[40].tQTaskRefList.ptHead )
  {
    QSprite_DeAlloc((struct QSprite_s *)&ptQTask[39].eQTaskType);
    ptQTask[40].tQTaskRefList.ptHead = nullptr;
  }
  if ( ptQTask[48].ptPrev )
  {
    QSprite_DeAlloc((struct QSprite_s *)&ptQTask[47]);
    ptQTask[48].ptPrev = nullptr;
  }
  if ( ptQTask[3].ptParent )
    Symbol_Remove((char *)&ptQTask[2].ptPrev);
}

// source: j/0/weapons/weapontype.c:444  [size]
void __cdecl WeaponType_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = WeaponType_ptParameterList;
}

// source: j/0/weapons/weapontype.c:462  [anchor-mhash]
void __cdecl WeaponType_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s **p_ptPrev; // eax
  char v4; // cl
  int v5; // edi
  struct QTask_s **p_eQTaskType; // ebx
  struct QReference_s *Parameters; // eax
  struct QTask_s *v8; // ecx
  int v9; // [esp+10h] [ebp-4h] BYREF
  struct QTask_s *ptQTaska = *(struct QTask_s * *)&ptQTask; // [esp+18h] [ebp+4h] ARGSLOT

  if ( ptQTask[3].ptParent )
  {
    Symbol_Remove((char *)&ptQTask[2].eQTaskType);
    ptQTask[3].ptParent = nullptr;
  }
  if ( strcmp((char *)&ptQTask[2].ptPrev, "WEAPON_ID_UNDEFINED") )
  {
    Symbol_Register(
      (char *)&ptQTask[2].ptPrev,
      (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
      ptQTask[3].tQTaskRefList.ptTail,
      4,
      QSCRIPT_SYMBOLCLASS_CONSTANT,
      QSCRIPT_SYMBOLTYPE_INT,
      QSCRIPT_SYMBOLLIFESPAN_INFINITE);
    p_ptPrev = &ptQTask[2].ptPrev;
    do
    {
      v4 = *(_BYTE *)p_ptPrev;
      *((_BYTE *)p_ptPrev + 32) = *(_BYTE *)p_ptPrev;
      p_ptPrev = (struct QTask_s **)((char *)p_ptPrev + 1);
    }
    while ( v4 );
    ptQTask[3].ptParent = (struct QTask_s *)1;
  }
  if ( LOBYTE(ptQTask[48].ptNext) )
  {
    v5 = 0;
    ptQTaska = nullptr;
    p_eQTaskType = (struct QTask_s **)&ptQTask[32].eQTaskType;
    do
    {
      if ( *(p_eQTaskType - 4) != *(p_eQTaskType - 3) )
      {
        WeaponType_DeleteParameters((struct QReference_s **)p_eQTaskType - 1);
        if ( !*p_eQTaskType )
        {
          v9 = v5;
          v5 = (int)ptQTaska;
          *p_eQTaskType = QTask_NewFn(ptQTask, WeaponTypeParameterContainer_eQTaskType, &v9);
        }
        Parameters = WeaponType_CreateParameters(*((_WORD *)p_eQTaskType - 8), *p_eQTaskType);
        v8 = *(p_eQTaskType - 4);
        *(p_eQTaskType - 1) = (struct QTask_s *)Parameters;
        *(p_eQTaskType - 3) = v8;
      }
      ++v5;
      p_eQTaskType += 5;
      ptQTaska = (struct QTask_s *)v5;
    }
    while ( v5 < 2 );
  }
}

// source: j/0/weapons/weapontype.c:507  [anchor-strings]
void __cdecl WeaponType_UpdateInternalDataAfterLoadHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { int pxContext; };
    struct { char igi2_o1[4]; void *v8; };
    struct { char igi2_o2[8]; char zFileName[256]; };
    char igi2_extent[264];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v1; // ebx
  struct QTask_s **p_ptParent; // esi
  struct QReference_s *v3; // ecx
  unsigned __int16 *pxObject; // eax
  void (__cdecl *pfHandler)(unsigned __int16 *, void **); // edx
  char ptNext; // cl

  QTask_TriggerQTaskEventChildrenRecursivelyNoContext(ptQTask, WeaponType_eFindChildrenQTaskEvent);
  v1 = 0;
  p_ptParent = &ptQTask[32].ptParent;
  do
  {
    if ( *(p_ptParent - 3) != *(p_ptParent - 2) )
    {
      v3 = (struct QReference_s *)*p_ptParent;
      if ( *p_ptParent )
      {
        pxObject = (unsigned __int16 *)v3->pxObject;
        if ( pxObject )
        {
          pfHandler = (void (__cdecl *)(unsigned __int16 *, void **))QTask_aatQTaskFinalEvent[WeaponType_eDeleteParametersQTaskEvent][pxObject[18]].pfHandler;
          if ( pfHandler )
          {
            igi2_frame.v8 = v3->pxObject;
            pfHandler(pxObject, &igi2_frame.v8);
            if ( *p_ptParent )
            {
              QReference_Delete((struct QReference_s *)*p_ptParent, &QTask_tQTaskRefPool);
              *p_ptParent = nullptr;
            }
          }
        }
      }
      if ( !p_ptParent[1] )
      {
        igi2_frame.pxContext = v1;
        p_ptParent[1] = QTask_NewFn(ptQTask, WeaponTypeParameterContainer_eQTaskType, &igi2_frame.pxContext);
      }
      *p_ptParent = (struct QTask_s *)WeaponType_CreateParameters(*((_WORD *)p_ptParent - 6), p_ptParent[1]);
      *(p_ptParent - 2) = *(p_ptParent - 3);
    }
    ++v1;
    p_ptParent += 5;
  }
  while ( v1 < 2 );
  ptNext = (char)ptQTask[1].ptNext;
  LOBYTE(ptQTask[48].ptNext) = 1;
  if ( ptNext )
  {
    sprintf(igi2_frame.zFileName, "%s.tex", (char *)&ptQTask[1]);
    ptQTask[2].ptNext = (struct QTask_s *)GameFunctions_RegisterGameTexture(igi2_frame.zFileName);
    *(_DWORD *)&ptQTask[1].eQTaskType = 1;
  }
}

// source: j/0/weapons/weapontype.c:544  [anchor-strings]
void __cdecl WeaponType_DrawIconHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { float ptQSprite; };
    struct { char igi2_o1[4]; float vX; };
    struct { char igi2_o2[44]; char *nHeight; };
    struct { char igi2_o3[44]; int nHeighta; };
    struct { char igi2_o4[44]; int nHeightb; };
    struct { char igi2_o5[44]; float nHeightc; };
    struct { char igi2_o6[48]; float v23; };
    struct { char igi2_o7[64]; float vGunSpriteWidth; };
    struct { char igi2_o8[68]; int v25; };
    struct { char igi2_o9[72]; float v26; };
    struct { char igi2_o10[80]; struct QVertexStripContext_s tContext; };
    struct { char igi2_o11[100]; struct QVertex_s atQVertex[2]; };
    struct { char igi2_o12[172]; char zResourcename[260]; };
    struct { char igi2_o13[432]; char zTemp[256]; };
    char igi2_extent[688];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v2; // edi
  double v3; // st7
  char *LocalizedStringForLanguage; // eax
  float *v5; // esi
  int v6; // edx
  int v7; // eax
  int v8; // ebp
  __int16 *v9; // ebx
  int v10; // eax
  int v11; // eax
  int v12; // ecx
  int v13; // edx
  __int16 *v14; // edi
  struct QTask_s *ptPrev; // edi
  double v16; // st6

  igi2_frame.v26 = (double)Display_tActiveMode.nWidth * 0.984375;
  v2 = **((_DWORD **)pxContext + 1);
  v3 = (double)Display_tActiveMode.nHeight * 0.9583333134651184;
  igi2_frame.vGunSpriteWidth = 0.0;
  igi2_frame.v23 = v3 - 2.0;
  sprintf(igi2_frame.zResourcename, "weapons/strings/%s", (char *)&ptQTask[3].eQTaskType);
  igi2_frame.nHeight = Config_GetLocalizedStringForLanguage(
              igi2_frame.zResourcename,
              Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eLanguage,
              false);
  if ( !igi2_frame.nHeight )
    igi2_frame.nHeight = (char *)&ptQTask[3].eQTaskType;
  sprintf(igi2_frame.zResourcename, "weapons/strings/%s", (char *)&ptQTask[18].ptPrev + 32 * *((_DWORD *)pxContext + 3));
  LocalizedStringForLanguage = Config_GetLocalizedStringForLanguage(
                                 igi2_frame.zResourcename,
                                 Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eLanguage,
                                 false);
  if ( !LocalizedStringForLanguage )
    LocalizedStringForLanguage = (char *)(&ptQTask[18].ptPrev + 8 * *((_DWORD *)pxContext + 3));
  if ( strlen(LocalizedStringForLanguage) )
    sprintf(igi2_frame.zTemp, "%s : %s", igi2_frame.nHeight, LocalizedStringForLanguage);
  else
    sprintf(igi2_frame.zTemp, (char *const)&stru_6A4CDC.tDebugConsoleLineList.ptMiddle, igi2_frame.nHeight);
  Text_SetString(*(struct StaticTilemap_s **)(v2 + 1136), igi2_frame.zTemp);
  v5 = *(float **)(v2 + 1136);
  v6 = *(_DWORD *)v5;
  v7 = *(__int16 *)(*(_DWORD *)v5 + 6);
  v8 = 0;
  igi2_frame.nHeighta = 0;
  if ( v7 > 0 )
  {
    v9 = *(__int16 **)(v6 + 12);
    do
    {
      if ( *v9 > v8 )
        v8 = *v9;
      ++v9;
      --v7;
    }
    while ( v7 );
    igi2_frame.nHeighta = v8;
  }
  igi2_frame.v25 = *(__int16 *)(v6 + 6)
      * *(__int16 *)(*(_DWORD *)(*(_DWORD *)(v6 + 8) + 8) + 36 * *(unsigned __int16 *)(*(_DWORD *)(v6 + 8) + 20) + 14);
  v5[1] = (float)(int)(__int64)(igi2_frame.v26 - (double)igi2_frame.nHeighta);
  *(float *)(*(_DWORD *)(v2 + 1136) + 8) = (float)(int)(__int64)(igi2_frame.v23 - (double)igi2_frame.v25);
  *(_DWORD *)(*(_DWORD *)(v2 + 1136) + 20) = 1112329421;
  *(_DWORD *)(*(_DWORD *)(v2 + 1136) + 24) = 1117362586;
  *(_DWORD *)(*(_DWORD *)(v2 + 1136) + 28) = 1124073472;
  *(_DWORD *)(*(_DWORD *)(v2 + 1136) + 32) = 1;
  v10 = *(_DWORD *)(v2 + 1136);
  QTilemap_Register(
    *(struct QTilemap_s **)v10,
    *(float *)(v10 + 4),
    *(float *)(v10 + 8),
    *(float *)(v10 + 20),
    *(float *)(v10 + 24),
    *(float *)(v10 + 28),
    *(float *)(v10 + 16),
    *(float *)(v10 + 12),
    *(_DWORD *)(v10 + 36) | 0x40000000,
    *(_DWORD *)(v10 + 32));
  v11 = **(_DWORD **)(v2 + 1136);
  v12 = *(__int16 *)(v11 + 6);
  v13 = 0;
  igi2_frame.nHeightb = 0;
  if ( v12 > 0 )
  {
    v14 = *(__int16 **)(v11 + 12);
    do
    {
      if ( *v14 > v13 )
        v13 = *v14;
      ++v14;
      --v12;
    }
    while ( v12 );
    igi2_frame.nHeightb = v13;
  }
  igi2_frame.nHeightc = (float)igi2_frame.nHeightb;
  if ( ptQTask[40].tQTaskRefList.ptHead )
  {
    ptPrev = ptQTask[40].ptPrev;
    igi2_frame.vX = igi2_frame.v23
       - 2.0
       - (double)*((__int16 *)&ptPrev->tQTaskChildren.ptMiddle + 18 * LOWORD(ptQTask[40].tQTaskChildren.ptTail) + 1)
       - (double)(*(__int16 *)(v11 + 6)
                * *(__int16 *)(*(_DWORD *)(*(_DWORD *)(v11 + 8) + 8)
                             + 36 * *(unsigned __int16 *)(*(_DWORD *)(v11 + 8) + 20)
                             + 14));
    igi2_frame.ptQSprite = igi2_frame.v26
              - (double)*((__int16 *)&ptPrev->tQTaskChildren.ptMiddle + 18 * LOWORD(ptQTask[40].tQTaskChildren.ptTail));
    QSprite_Register((struct QSprite_s *)&ptQTask[39].eQTaskType, igi2_frame.ptQSprite, igi2_frame.vX, 128.0, 128.0, 128.0, 0, 0, 1);
    igi2_frame.vGunSpriteWidth = (float)*((__int16 *)&ptQTask[40].ptPrev->tQTaskChildren.ptMiddle
                             + 18 * LOWORD(ptQTask[40].tQTaskChildren.ptTail));
  }
  igi2_frame.atQVertex[0].vY = v3;
  igi2_frame.tContext.isLine = 1;
  igi2_frame.tContext.nDepth = 1;
  QVertex_ptActiveTexture = nullptr;
  QVertex_ptActivePalette = nullptr;
  igi2_frame.atQVertex[0].vR = 0.4000000059604645;
  igi2_frame.atQVertex[0].vG = 0.6000000238418579;
  igi2_frame.atQVertex[0].vB = 1.0;
  igi2_frame.atQVertex[0].vA = 0.5;
  igi2_frame.atQVertex[0].vU = 0.0;
  igi2_frame.atQVertex[0].vV = 0.0;
  igi2_frame.atQVertex[0].vZ = 1.0;
  igi2_frame.atQVertex[1].vR = 0.4000000059604645;
  igi2_frame.atQVertex[1].vG = 0.6000000238418579;
  igi2_frame.atQVertex[1].vB = 1.0;
  igi2_frame.atQVertex[1].vA = 0.5;
  igi2_frame.atQVertex[1].vU = 0.0;
  igi2_frame.atQVertex[1].vV = 0.0;
  igi2_frame.atQVertex[1].vZ = 1.0;
  igi2_frame.tContext.nStripLength = 2;
  igi2_frame.tContext.atQVertex = igi2_frame.atQVertex;
  igi2_frame.tContext.bFlags = 0x80000;
  igi2_frame.atQVertex[0].vX = igi2_frame.v26;
  if ( igi2_frame.nHeightc <= (double)igi2_frame.vGunSpriteWidth )
    v16 = igi2_frame.vGunSpriteWidth;
  else
    v16 = igi2_frame.nHeightc + 3.0;
  igi2_frame.atQVertex[1].vX = igi2_frame.atQVertex[0].vX - v16;
  igi2_frame.atQVertex[1].vY = v3;
  RenderMode_tActiveRenderMode.apfRenderModeMethod[QVertex_eRegisterQVertexStripMethod](&igi2_frame.tContext);
}

// source: j/0/weapons/weapontype.c:676  [anchor-mhash]
void __cdecl WeaponType_StatusDisplayHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { float vX1; };
    struct { char igi2_o1[4]; float vY1; };
    struct { char igi2_o2[12]; float vX2; };
    struct { char igi2_o3[16]; float vY2; };
    struct { char igi2_o4[24]; float vY; };
    struct { char igi2_o5[24]; float vYa; };
    struct { char igi2_o6[24]; float vYb; };
    struct { char igi2_o7[24]; float vYc; };
    struct { char igi2_o8[24]; float vYd; };
    struct { char igi2_o9[28]; float vZ; };
    struct { char igi2_o10[28]; float vZa; };
    struct { char igi2_o11[28]; float vZb; };
    struct { char igi2_o12[28]; float vZc; };
    struct { char igi2_o13[28]; float vZd; };
    struct { char igi2_o14[32]; float vR; };
    struct { char igi2_o15[32]; float vRa; };
    struct { char igi2_o16[32]; float vRb; };
    struct { char igi2_o17[32]; float vRc; };
    struct { char igi2_o18[32]; float vRd; };
    struct { char igi2_o19[36]; float vG; };
    struct { char igi2_o20[36]; float vGa; };
    struct { char igi2_o21[36]; float vGb; };
    struct { char igi2_o22[36]; float vGc; };
    struct { char igi2_o23[36]; float vGd; };
    struct { char igi2_o24[48]; float vAlpha; };
    struct { char igi2_o25[56]; float vStartAngle; };
    struct { char igi2_o26[80]; int vCenterX; };
    struct { char igi2_o27[80]; float vCenterXa; };
    struct { char igi2_o28[80]; float vCenterXb; };
    struct { char igi2_o29[80]; float vCenterXc; };
    struct { char igi2_o30[80]; float vCenterXd; };
    struct { char igi2_o31[80]; float vCenterXe; };
    struct { char igi2_o32[80]; float vCenterXf; };
    struct { char igi2_o33[84]; int nDots; };
    struct { char igi2_o34[84]; float nDotsa; };
    struct { char igi2_o35[84]; float nDotsb; };
    struct { char igi2_o36[84]; int nDotsc; };
    struct { char igi2_o37[84]; float nDotsd; };
    struct { char igi2_o38[88]; float vRadius; };
    struct { char igi2_o39[92]; int nHeight; };
    struct { char igi2_o40[92]; float nHeighta; };
    struct { char igi2_o41[96]; __int64 vStep; };
    struct { char igi2_o42[104]; float v73; };
    struct { char igi2_o43[108]; float v74; };
    struct { char igi2_o44[112]; float v75; };
    struct { char igi2_o45[116]; float v76; };
    struct { char igi2_o46[120]; struct GetWeaponPrecisionContext_s tGetWeaponPrecisionContext; };
    struct { char igi2_o47[128]; float vB1; };
    struct { char igi2_o48[132]; float vAngleSize; };
    struct { char igi2_o49[136]; float vG1; };
    struct { char igi2_o50[140]; float vR1; };
    struct { char igi2_o51[144]; struct real32x2_t atMesh[16]; };
    char igi2_extent[272];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  _DWORD *v2; // ebp
  int v3; // eax
  int v4; // eax
  void (__cdecl *pfHandler)(int, struct GetWeaponPrecisionContext_s *); // ecx
  double v6; // st6
  double v7; // st7
  double v8; // st7
  struct QReference_s *ptTail; // eax
  float v10; // esi
  double v11; // st7
  int v12; // ebx
  long double v13; // st7
  double v14; // st7
  int v15; // ebx
  int v16; // ebx
  double v17; // st7
  double v18; // st6
  int v19; // ebx
  int v20; // ebx
  struct QReference_s *v21; // eax
  int v22; // ebx
  int v23; // ebx
  int v24; // esi
  struct QTask_s **p_ptParent; // edi
  int v26; // ecx
  int v27; // eax
  void *v28; // ecx
  void (__cdecl **v29)(_DWORD, _DWORD *); // eax
  int v30; // ecx

  igi2_frame.vCenterX = Display_tActiveMode.nHeight;
  v2 = pxContext;
  igi2_frame.nDots = Display_tActiveMode.nWidth;
  v3 = *(_DWORD *)pxContext;
  igi2_frame.tGetWeaponPrecisionContext.vPrecision = 0.0;
  igi2_frame.tGetWeaponPrecisionContext.vSightFOV = 1.0;
  v4 = *(_DWORD *)(v3 + 32);
  pfHandler = (void (__cdecl *)(int, struct GetWeaponPrecisionContext_s *))QTask_aatQTaskFinalEvent[Weapon_eGetWeaponPrecisionQTaskEvent][*(unsigned __int16 *)(v4 + 36)].pfHandler;
  if ( pfHandler )
    pfHandler(v4, &igi2_frame.tGetWeaponPrecisionContext);
  v6 = (double)igi2_frame.vCenterX;
  v7 = 1.0 / igi2_frame.tGetWeaponPrecisionContext.vSightFOV * v6 * igi2_frame.tGetWeaponPrecisionContext.vPrecision * 0.013089969754219055;
  if ( v7 >= 1.0 )
    igi2_frame.vRadius = v7;
  else
    igi2_frame.vRadius = 1.0;
  igi2_frame.nDotsa = (float)igi2_frame.nDots;
  igi2_frame.vStep = (__int64)(Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGraphicOptions.vCrossHairThickness
                  * 0.5);
  v8 = (double)(int)igi2_frame.vStep;
  igi2_frame.vCenterXa = igi2_frame.nDotsa * 0.5 + 1.0 - v8;
  igi2_frame.nHeighta = v6;
  *(float *)&igi2_frame.nHeight = igi2_frame.nHeighta * 0.5 + 1.0 - v8;
  if ( *(_DWORD *)(*(_DWORD *)pxContext + 44) == *(_DWORD *)(*(_DWORD *)pxContext + 40) )
  {
    ptTail = ptQTask[17].tQTaskRefList.ptTail;
    v10 = igi2_frame.nDotsa * 0.5 + 1.0 - v8;
    if ( ptTail == (struct QReference_s *)2 )
    {
      v11 = igi2_frame.vRadius * 6.2831854820251465;
      igi2_frame.vStep = (__int64)(0.1666666716337204 * v11);
      v12 = igi2_frame.vStep;
      if ( (int)igi2_frame.vStep < 1 )
        v12 = 1;
      igi2_frame.nDotsb = 0.0;
      *(float *)&igi2_frame.vStep = 6.2831854820251465 / (double)v12;
      igi2_frame.vAngleSize = 12.566370964050293 / v11;
      do
      {
        igi2_frame.vB1 = Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGraphicOptions.vCrossHairB * 128.0;
        igi2_frame.vG1 = Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGraphicOptions.vCrossHairG * 128.0;
        igi2_frame.vR1 = Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGraphicOptions.vCrossHairR * 128.0;
        v13 = igi2_frame.vAngleSize + igi2_frame.nDotsb;
        igi2_frame.vAlpha = Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGraphicOptions.vCrossHairAlpha * 0.5;
        igi2_frame.vY2 = sin(v13) * igi2_frame.vRadius + *(float *)&igi2_frame.nHeight;
        igi2_frame.vX2 = cos(v13) * igi2_frame.vRadius + igi2_frame.vCenterXa;
        igi2_frame.vY1 = sin(igi2_frame.nDotsb) * igi2_frame.vRadius + *(float *)&igi2_frame.nHeight;
        igi2_frame.vX1 = cos(igi2_frame.nDotsb) * igi2_frame.vRadius + igi2_frame.vCenterXa;
        QSprite_RegisterLine(
          igi2_frame.vX1,
          igi2_frame.vY1,
          1.0,
          igi2_frame.vX2,
          igi2_frame.vY2,
          1.0,
          igi2_frame.vR1,
          igi2_frame.vG1,
          igi2_frame.vB1,
          igi2_frame.vR1,
          igi2_frame.vG1,
          igi2_frame.vB1,
          igi2_frame.vAlpha,
          2.0,
          (unsigned int)&MTP_atLODVirModel[6].atBoneVertexRefs[7].atVertexRefs[366],
          0);
        --v12;
        igi2_frame.nDotsb = igi2_frame.nDotsb + *(float *)&igi2_frame.vStep;
      }
      while ( v12 );
    }
    else if ( ptTail == (struct QReference_s *)3 )
    {
      v14 = igi2_frame.nDotsa * 0.01718750037252903 / igi2_frame.vRadius;
      if ( v14 <= 0.7853981852531433 )
        igi2_frame.vCenterXb = v14;
      else
        igi2_frame.vCenterXb = 0.7853981852531433;
      v15 = 4;
      *(float *)&igi2_frame.nDotsc = igi2_frame.vCenterXb * -0.5;
      do
      {
        igi2_frame.vStartAngle = *(float *)&igi2_frame.nDotsc + igi2_frame.vCenterXb;
        QSprite_CreateCircleSegment(igi2_frame.atMesh, *(float *)&igi2_frame.nDotsc, igi2_frame.vStartAngle, igi2_frame.vRadius, 16);
        igi2_frame.vG = Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGraphicOptions.vCrossHairAlpha * 0.20000000298023224;
        igi2_frame.vR = Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGraphicOptions.vCrossHairB * 128.0;
        igi2_frame.vZ = Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGraphicOptions.vCrossHairG * 128.0;
        igi2_frame.vY = Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGraphicOptions.vCrossHairR * 128.0;
        QSprite_RegisterLineMesh(
          igi2_frame.atMesh,
          16,
          v10,
          *(float *)&igi2_frame.nHeight,
          1.0,
          igi2_frame.vY,
          igi2_frame.vZ,
          igi2_frame.vR,
          igi2_frame.vG,
          Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGraphicOptions.vCrossHairThickness,
          0.0,
          1.0,
          1.0,
          (unsigned int)&MTP_atLODVirModel[6].atBoneVertexRefs[7].atVertexRefs[366],
          0);
        --v15;
        *(float *)&igi2_frame.nDotsc = *(float *)&igi2_frame.nDotsc + 1.5707963705062866;
      }
      while ( v15 );
      v2 = pxContext;
    }
    else if ( ptTail == (struct QReference_s *)6 )
    {
      v16 = 4;
      v17 = igi2_frame.vRadius * 0.7071059942245483;
      igi2_frame.vCenterXf = v17;
      *(float *)&igi2_frame.vStep = v17 - 4.0;
      v18 = igi2_frame.vCenterXf;
      igi2_frame.vCenterXc = 0.0;
      *((float *)&igi2_frame.vStep + 1) = v18 + 4.0;
      igi2_frame.v73 = *((float *)&igi2_frame.vStep + 1);
      igi2_frame.v74 = *(float *)&igi2_frame.vStep;
      do
      {
        igi2_frame.vGa = Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGraphicOptions.vCrossHairAlpha * 0.800000011920929;
        igi2_frame.vRa = Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGraphicOptions.vCrossHairB * 128.0;
        igi2_frame.vZa = Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGraphicOptions.vCrossHairG * 128.0;
        igi2_frame.vYa = Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGraphicOptions.vCrossHairR * 128.0;
        QSprite_RegisterLineMesh(
          (struct real32x2_t *)&igi2_frame.vStep,
          2,
          v10,
          *(float *)&igi2_frame.nHeight,
          1.0,
          igi2_frame.vYa,
          igi2_frame.vZa,
          igi2_frame.vRa,
          igi2_frame.vGa,
          Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGraphicOptions.vCrossHairThickness,
          igi2_frame.vCenterXc,
          1.0,
          1.0,
          (unsigned int)&MTP_atLODVirModel[6].atBoneVertexRefs[7].atVertexRefs[366],
          0);
        --v16;
        igi2_frame.vCenterXc = igi2_frame.vCenterXc + 1.5707963705062866;
      }
      while ( v16 );
    }
    else if ( ptTail == (struct QReference_s *)7 )
    {
      igi2_frame.vStep = 0;
      igi2_frame.v73 = 0.0;
      igi2_frame.v74 = 0.0;
      igi2_frame.vCenterXd = 0.0;
      v19 = 4;
      do
      {
        igi2_frame.vGb = Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGraphicOptions.vCrossHairAlpha * 0.800000011920929;
        igi2_frame.vRb = Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGraphicOptions.vCrossHairB * 128.0;
        igi2_frame.vZb = Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGraphicOptions.vCrossHairG * 128.0;
        igi2_frame.vYb = Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGraphicOptions.vCrossHairR * 128.0;
        QSprite_RegisterLineMesh(
          (struct real32x2_t *)&igi2_frame.vStep,
          2,
          v10,
          *(float *)&igi2_frame.nHeight,
          1.0,
          igi2_frame.vYb,
          igi2_frame.vZb,
          igi2_frame.vRb,
          igi2_frame.vGb,
          2.0,
          igi2_frame.vCenterXd,
          1.0,
          1.0,
          (unsigned int)&MTP_atLODVirModel[6].atBoneVertexRefs[7].atVertexRefs[366],
          0);
        --v19;
        igi2_frame.vCenterXd = igi2_frame.vCenterXd + 1.5707963705062866;
      }
      while ( v19 );
    }
    else if ( ptTail == (struct QReference_s *)5 )
    {
      *(float *)&igi2_frame.vStep = igi2_frame.vRadius;
      igi2_frame.v76 = igi2_frame.vRadius;
      *((float *)&igi2_frame.vStep + 1) = igi2_frame.vRadius + 8.0;
      igi2_frame.vCenterXe = 0.0;
      igi2_frame.v73 = *((float *)&igi2_frame.vStep + 1);
      v20 = 4;
      igi2_frame.v74 = *((float *)&igi2_frame.vStep + 1);
      igi2_frame.v75 = *((float *)&igi2_frame.vStep + 1);
      do
      {
        igi2_frame.vGc = Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGraphicOptions.vCrossHairAlpha * 0.800000011920929;
        igi2_frame.vRc = Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGraphicOptions.vCrossHairB * 128.0;
        igi2_frame.vZc = Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGraphicOptions.vCrossHairG * 128.0;
        igi2_frame.vYc = Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGraphicOptions.vCrossHairR * 128.0;
        QSprite_RegisterLineMesh(
          (struct real32x2_t *)&igi2_frame.vStep,
          3,
          v10,
          *(float *)&igi2_frame.nHeight,
          1.0,
          igi2_frame.vYc,
          igi2_frame.vZc,
          igi2_frame.vRc,
          igi2_frame.vGc,
          Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGraphicOptions.vCrossHairThickness,
          igi2_frame.vCenterXe,
          1.0,
          1.0,
          (unsigned int)&MTP_atLODVirModel[6].atBoneVertexRefs[7].atVertexRefs[366],
          0);
        --v20;
        igi2_frame.vCenterXe = igi2_frame.vCenterXe + 1.5707963705062866;
      }
      while ( v20 );
    }
    v21 = ptQTask[17].tQTaskRefList.ptTail;
    if ( v21 == (struct QReference_s *)1
      || v21 == (struct QReference_s *)3
      || v21 == (struct QReference_s *)4
      || v21 == (struct QReference_s *)8 && v2[4] )
    {
      LODWORD(igi2_frame.vStep) = 0;
      igi2_frame.v73 = 0.0;
      *((float *)&igi2_frame.vStep + 1) = igi2_frame.vRadius + 8.0;
      igi2_frame.v74 = igi2_frame.vRadius;
      igi2_frame.nDotsd = 0.7853981852531433;
      if ( v21 != (struct QReference_s *)4 )
        igi2_frame.nDotsd = 0.0;
      v22 = 4;
      do
      {
        igi2_frame.vGd = Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGraphicOptions.vCrossHairAlpha * 0.800000011920929;
        igi2_frame.vRd = Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGraphicOptions.vCrossHairB * 128.0;
        igi2_frame.vZd = Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGraphicOptions.vCrossHairG * 128.0;
        igi2_frame.vYd = Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGraphicOptions.vCrossHairR * 128.0;
        QSprite_RegisterLineMesh(
          (struct real32x2_t *)&igi2_frame.vStep,
          2,
          v10,
          *(float *)&igi2_frame.nHeight,
          1.0,
          igi2_frame.vYd,
          igi2_frame.vZd,
          igi2_frame.vRd,
          igi2_frame.vGd,
          Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGraphicOptions.vCrossHairThickness,
          igi2_frame.nDotsd,
          1.0,
          1.0,
          (unsigned int)&MTP_atLODVirModel[6].atBoneVertexRefs[7].atVertexRefs[366],
          0);
        --v22;
        igi2_frame.nDotsd = igi2_frame.nDotsd + 1.5707963705062866;
      }
      while ( v22 );
    }
  }
  v23 = 0;
  v24 = 0;
  p_ptParent = &ptQTask[32].ptParent;
  do
  {
    v26 = *((unsigned __int16 *)p_ptParent - 6);
    if ( QTask_IsQTaskTypeValid(v26) )
    {
      v27 = v26 + 511 * StatusScreen_eStatusDisplayQTaskEvent;
      v28 = QTask_aatQTaskFinalEvent[0][v27].pfHandler;
      v29 = (void (__cdecl **)(_DWORD, _DWORD *))(4 * v27 + 137981376);
      if ( v28 )
      {
        v30 = *v2 + v24 + 104;
        v2[2] = v23;
        v2[5] = v30;
        v2[6] = (*p_ptParent)->tQTaskChildren.ptHead;
        (*v29)(0, v2);
      }
    }
    v24 += 28;
    ++v23;
    p_ptParent += 5;
  }
  while ( v24 < 56 );
}

// source: j/0/weapons/weapontype.c:1028  [anchor-mhash]
void __cdecl WeaponType_GetWeaponTypeHandler(struct QTask_s *ptQTask, void *pxContext)
{
  char *v2; // eax

  if ( !*((_DWORD *)pxContext + 1) )
  {
    if ( *(_DWORD *)pxContext != -1 && *(struct QReference_s **)pxContext == ptQTask[3].tQTaskRefList.ptTail )
      *((_DWORD *)pxContext + 1) = ptQTask;
    v2 = *((char **)pxContext + 2);
    if ( v2 )
    {
      if ( !strcmp(v2, (char *)&ptQTask[16].eQTaskType) )
        *((_DWORD *)pxContext + 1) = ptQTask;
    }
  }
}

// source: j/0/weapons/weapontype.c:1068  [anchor-mhash]
void __cdecl WeaponType_GetAnimHandler(struct QTask_s *ptQTask, void *pxContext)
{
  int v2; // eax
  char *p_ptTail; // edi
  struct AnimHeader_s *Anim; // eax
  double nTotalTime; // st7
  double v6; // st7
  enum WeaponTypeAnim_e v7; // esi
  struct AnimHeader_s *AnimHeaderFromWeaponTypeAnim; // ecx
  int v9; // eax
  unsigned __int16 *v10; // ecx
  int v11; // edx
  int v12; // eax
  void *pfHandler; // edx
  void (__cdecl **v14)(_DWORD, void *); // eax

  v2 = *((_DWORD *)pxContext + 3);
  *((_DWORD *)pxContext + 6) = 0;
  *((_DWORD *)pxContext + 7) = 1065353216;
  switch ( v2 )
  {
    case 0:
      *((_DWORD *)pxContext + 6) = Hierarchy_GetAnim(*(unsigned __int8 **)pxContext, (char *)&ptQTask[22].ptPrev);
      break;
    case 1:
      *((_DWORD *)pxContext + 6) = Hierarchy_GetAnim(
                                     *(unsigned __int8 **)pxContext,
                                     (char *)&ptQTask[22].eQTaskType);
      break;
    case 2:
    case 3:
      p_ptTail = (char *)&ptQTask[23].tQTaskRefList.ptTail;
      if ( v2 != 2 )
        p_ptTail = (char *)&ptQTask[24].tQTaskRefList;
      if ( p_ptTail )
      {
        Anim = Hierarchy_GetAnim(*(unsigned __int8 **)pxContext, p_ptTail);
        if ( Anim )
        {
          nTotalTime = (double)Anim->nTotalTime;
          *((_DWORD *)pxContext + 6) = Anim;
          v6 = nTotalTime * 0.00020833333837799728;
          goto LABEL_21;
        }
      }
      break;
    case 10:
      *((_DWORD *)pxContext + 6) = Hierarchy_GetAnim(
                                     *(unsigned __int8 **)pxContext,
                                     (char *)&ptQTask[25].tQTaskChildren.ptMiddle);
      break;
    case 11:
      *((_DWORD *)pxContext + 6) = Hierarchy_GetAnim(*(unsigned __int8 **)pxContext, (char *)&ptQTask[26].ptPrev);
      break;
    case 12:
      *((_DWORD *)pxContext + 6) = Hierarchy_GetAnim(
                                     *(unsigned __int8 **)pxContext,
                                     (char *)&ptQTask[26].eQTaskType);
      break;
    case 13:
      *((_DWORD *)pxContext + 6) = Hierarchy_GetAnim(
                                     *(unsigned __int8 **)pxContext,
                                     (char *)&ptQTask[27].tQTaskRefList.ptTail);
      break;
    case 14:
      *((_DWORD *)pxContext + 6) = Hierarchy_GetAnim(
                                     *(unsigned __int8 **)pxContext,
                                     (char *)&ptQTask[28].tQTaskRefList);
      break;
    case 15:
      v7 = WEAPONTYPEANIM_RAISEWEAPON;
      goto LABEL_18;
    case 16:
      v7 = WEAPONTYPEANIM_LOWERWEAPON;
      goto LABEL_18;
    case 26:
      v7 = WEAPONTYPEANIM_FLAT_RAISEWEAPON;
      goto LABEL_18;
    case 27:
      v7 = WEAPONTYPEANIM_FLAT_LOWERWEAPON;
LABEL_18:
      AnimHeaderFromWeaponTypeAnim = WeaponType_GetAnimHeaderFromWeaponTypeAnim(
                                       (struct WeaponType_s *)ptQTask,
                                       *(unsigned __int8 **)pxContext,
                                       v7);
      *((_DWORD *)pxContext + 6) = AnimHeaderFromWeaponTypeAnim;
      if ( AnimHeaderFromWeaponTypeAnim && *(float *)&ptQTask[22].ptNext != 0.0 )
      {
        v6 = (double)AnimHeaderFromWeaponTypeAnim->nTotalTime * 0.00020833333837799728;
LABEL_21:
        *((float *)pxContext + 7) = v6 / *(float *)&ptQTask[22].ptNext;
      }
      break;
    default:
      break;
  }
  if ( !*((_DWORD *)pxContext + 6) )
  {
    v9 = *((_DWORD *)pxContext + 4);
    if ( v9 != -1 )
    {
      v10 = (unsigned __int16 *)((char *)&ptQTask[32].tQTaskRefList + 20 * v9);
      v11 = *v10;
      if ( QTask_IsQTaskTypeValid(v11) )
      {
        v12 = v11 + 511 * WeaponType_eGetAnimQTaskEvent;
        pfHandler = QTask_aatQTaskFinalEvent[0][v12].pfHandler;
        v14 = (void (__cdecl **)(_DWORD, void *))(4 * v12 + 137981376);
        if ( pfHandler )
        {
          *((_DWORD *)pxContext + 2) = ptQTask;
          *((_DWORD *)pxContext + 5) = *(_DWORD *)(*((_DWORD *)v10 + 3) + 8);
          (*v14)(0, pxContext);
        }
      }
    }
  }
}

// source: j/0/weapons/weapontype.c:1234  [anchor-callee]
struct AmmoType_s *__cdecl WeaponType_GetAmmoTypeForWeaponFire(
        struct WeaponType_s *ptWeaponType,
        int nFireType)
{
  struct WeaponTypeGetAmmoInfoContext_s tAmmoInfoContext; // [esp+0h] [ebp-28h] BYREF

  if ( (unsigned int)nFireType > 1 )
    return nullptr;
  memset(&tAmmoInfoContext, 0, sizeof(tAmmoInfoContext));
  ((void (__cdecl *)(struct WeaponType_s *, struct WeaponTypeGetAmmoInfoContext_s *))QTask_aatQTaskFinalEvent[WeaponType_eGetAmmoInfoQTaskEvent][ptWeaponType->tQTask.eQTaskType].pfHandler)(
    ptWeaponType,
    &tAmmoInfoContext);
  return tAmmoInfoContext.atAmmoItem[nFireType].tOut.ptAmmoType;
}

// source: j/0/weapons/weapontype.c:1263  [anchor-mhash]
void __cdecl WeaponType_GetAmmoInfoHandler(struct QTask_s *ptQTask, void *pxContext)
{
  _DWORD *v2; // esi
  struct QTask_s **p_ptParent; // ebx
  int v4; // ebp
  unsigned __int16 v5; // cx
  struct QTask_s *ptHead; // eax
  void *pfHandler; // eax

  v2 = (char *)pxContext + 8;
  p_ptParent = &ptQTask[32].ptParent;
  v4 = 2;
  do
  {
    v5 = *((_WORD *)p_ptParent - 6);
    if ( *p_ptParent )
      ptHead = (*p_ptParent)->tQTaskChildren.ptHead;
    else
      ptHead = nullptr;
    *(v2 - 2) = ptHead;
    *(v2 - 1) = 0;
    *v2 = 0;
    v2[1] = 0;
    v2[2] = 0;
    if ( QTask_IsQTaskTypeValid(v5) )
    {
      pfHandler = QTask_aatQTaskFinalEvent[WeaponType_eGetAmmoInfoQTaskEvent][v5].pfHandler;
      if ( pfHandler )
        ((void (__cdecl *)(_DWORD, _DWORD *))pfHandler)(0, v2 - 2);
    }
    p_ptParent += 5;
    v2 += 5;
    --v4;
  }
  while ( v4 );
}

// source: j/0/weapons/weapontype.c:1302  [size]
void __cdecl WeaponType_LoadSpriteHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s **p_ptParent; // esi
  int v3; // edi
  int v4; // ecx
  void (__cdecl *pfHandler)(_DWORD, struct QTask_s *); // eax

  if ( ptQTask[40].tQTaskRefList.ptHead )
  {
    QSprite_DeAlloc((struct QSprite_s *)&ptQTask[39].eQTaskType);
    ptQTask[40].tQTaskRefList.ptHead = nullptr;
  }
  if ( ptQTask[48].ptPrev )
  {
    QSprite_DeAlloc((struct QSprite_s *)&ptQTask[47]);
    ptQTask[48].ptPrev = nullptr;
  }
  if ( LOBYTE(ptQTask[33].tQTaskRefList.ptHead)
    && (Resource_IsLoadedInternal((char *)&ptQTask[33].tQTaskRefList, nullptr)
     || File_Exists((char *)&ptQTask[33].tQTaskRefList)) )
  {
    QSprite_Load((struct QSprite_s *)&ptQTask[39].eQTaskType, (char *)&ptQTask[33].tQTaskRefList);
    ptQTask[40].tQTaskRefList.ptHead = (struct QReference_s *)1;
  }
  if ( LOBYTE(ptQTask[40].tQTaskRefList.ptMiddle)
    && (Resource_IsLoadedInternal((char *)&ptQTask[40].tQTaskRefList.ptMiddle, nullptr)
     || File_Exists((char *)&ptQTask[40].tQTaskRefList.ptMiddle)) )
  {
    QSprite_Load((struct QSprite_s *)&ptQTask[47], (char *)&ptQTask[40].tQTaskRefList.ptMiddle);
    ptQTask[48].ptPrev = (struct QTask_s *)1;
  }
  p_ptParent = &ptQTask[32].ptParent;
  v3 = 2;
  do
  {
    v4 = *((unsigned __int16 *)p_ptParent - 6);
    if ( QTask_IsQTaskTypeValid(v4) )
    {
      pfHandler = (void (__cdecl *)(_DWORD, struct QTask_s *))QTask_aatQTaskFinalEvent[WeaponType_eLoadSpriteQTaskEvent][v4].pfHandler;
      if ( pfHandler )
        pfHandler(0, (*p_ptParent)->tQTaskChildren.ptHead);
    }
    p_ptParent += 5;
    --v3;
  }
  while ( v3 );
}

// source: j/0/weapons/weapontype.c:1346  [size]
void __cdecl WeaponType_UnLoadSpriteHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s **p_ptParent; // esi
  int v3; // edi
  int v4; // ecx
  void (__cdecl *pfHandler)(_DWORD, struct QTask_s *); // eax

  if ( ptQTask[40].tQTaskRefList.ptHead )
  {
    QSprite_DeAlloc((struct QSprite_s *)&ptQTask[39].eQTaskType);
    ptQTask[40].tQTaskRefList.ptHead = nullptr;
  }
  if ( ptQTask[48].ptPrev )
  {
    QSprite_DeAlloc((struct QSprite_s *)&ptQTask[47]);
    ptQTask[48].ptPrev = nullptr;
  }
  p_ptParent = &ptQTask[32].ptParent;
  v3 = 2;
  do
  {
    v4 = *((unsigned __int16 *)p_ptParent - 6);
    if ( QTask_IsQTaskTypeValid(v4) )
    {
      pfHandler = (void (__cdecl *)(_DWORD, struct QTask_s *))QTask_aatQTaskFinalEvent[WeaponType_eUnLoadSpriteQTaskEvent][v4].pfHandler;
      if ( pfHandler )
        pfHandler(0, *p_ptParent);
    }
    p_ptParent += 5;
    --v3;
  }
  while ( v3 );
}

// source: j/0/weapons/weapontype.c:1378  [size]
void __cdecl WeaponType_EnumWeaponTypesHandler(struct QTask_s *ptQTask, void *pxContext)
{
  (*(void (__cdecl **)(struct QTask_s *, _DWORD))pxContext)(ptQTask, *((_DWORD *)pxContext + 1));
}

// source: j/0/weapons/weapontype.c:1400  [size]
void __cdecl WeaponTypeContainer_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  LOBYTE(ptQTask[1].ptNext) = 0;
}

// source: j/0/weapons/weapontype.c:1416  [size]
void __cdecl WeaponTypeContainer_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = WeaponTypeContainer_ptParameterList;
}

// source: j/0/weapons/weapontype.c:1434  [size]
void __cdecl WeaponTypeContainer_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ;
}

// source: j/0/weapons/weapontype.c:1493  [anchor-mhash]
void __cdecl WeaponTypeParameterContainer_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  if ( pxContext )
    ptQTask[1].ptNext = *(struct QTask_s **)pxContext;
  else
    ptQTask[1].ptNext = (struct QTask_s *)-1;
}

// source: j/0/weapons/weapontype.c:1519  [size]
void __cdecl WeaponTypeParameterContainer_GetParameterListHandler(
        struct QTask_s *ptQTask,
        void *pxContext)
{
  *(_DWORD *)pxContext = WeaponTypeParameterContainer_ptParameterList;
}

// source: j/0/weapons/weapontype.c:1537  [size]
void __cdecl WeaponTypeParameterContainer_UpdateInternalDataHandler(
        struct QTask_s *ptQTask,
        void *pxContext)
{
  ;
}

// source: j/0/weapons/weapontype.c:1551  [size]
void __cdecl WeaponTypeParameterContainer_FindChildrenHandler(struct QTask_s *ptQTask)
{
  *((_DWORD *)&ptQTask->ptParent[32].eQTaskType + 5 * (int)ptQTask[1].ptNext) = ptQTask;
}

// source: j/0/weapons/weapontype.c:1607  [anchor-strings]
void __cdecl WeaponType_LoadConfig()
{
  WeaponType_ptContainer = QTask_NewFn(&Flow_ptFlow->tQTask, WeaponTypeContainer_eQTaskType, nullptr);
  Level_LoadQTask(WeaponType_ptContainer, "weapons/weapon.qsc", false);
}

// source: j/0/weapons/weapontype.c:1627  [size]
__int16 __cdecl WeaponType_GetCreateParametersQTaskEvent()
{
  return WeaponType_eCreateParametersQTaskEvent;
}

// source: j/0/weapons/weapontype.c:1641  [size]
__int16 __cdecl WeaponType_GetDeleteParametersQTaskEvent()
{
  return WeaponType_eDeleteParametersQTaskEvent;
}

// source: j/0/weapons/weapontype.c:1656  [size]
__int16 __cdecl WeaponType_GetGetAnimQTaskEvent()
{
  return WeaponType_eGetAnimQTaskEvent;
}

// source: j/0/weapons/weapontype.c:1671  [size]
__int16 __cdecl WeaponType_GetGetAmmoInfoQTaskEvent()
{
  return WeaponType_eGetAmmoInfoQTaskEvent;
}

// source: j/0/weapons/weapontype.c:1686  [size]
int __cdecl WeaponType_GetFindChildrenQTaskEvent()
{
  return WeaponType_eFindChildrenQTaskEvent;
}

// source: j/0/weapons/weapontype.c:1701  [size]
struct ParameterEnumItemList_s *__cdecl WeaponType_GetWeaponTypeEnumList()
{
  return &WeaponType_tWeaponTypeEnumList;
}

// source: j/0/weapons/weapontype.c:1714  [size]
struct ParameterEnumItemList_s *__cdecl WeaponType_GetSightDisplayTypeEnumList()
{
  return &WeaponType_tSightDisplayTypeEnumList;
}

// source: j/0/weapons/weapontype.c:1727  [size]
struct ParameterEnumItemList_s *__cdecl WeaponType_GetAmmoDisplayTypeEnumList()
{
  return &WeaponType_tAmmoDisplayTypeEnumList;
}

// source: j/0/weapons/weapontype.c:1740  [size]
struct ParameterEnumItemList_s *__cdecl WeaponType_GetWeaponIDEnumList()
{
  return &WeaponType_tWeaponIDEnumList;
}

// source: j/0/weapons/weapontype.c:1753  [size]
struct ParameterEnumItemList_s *__cdecl WeaponType_GetTaskTypeEnumList()
{
  return &WeaponType_tTaskTypeEnumList;
}

// source: j/0/weapons/weapontype.c:1766  [size]
struct ParameterEnumItemList_s *__cdecl WeaponType_GetAIDetectionRangeEnumList()
{
  return &WeaponType_tAIDetectionRangeEnumList;
}

// source: j/0/weapons/weapontype.c:1779  [size]
struct WeaponType_s *__cdecl WeaponType_GetWeaponTypeScriptID(char *pzScriptID)
{
  int v1; // eax

  v1 = Script_ParseLineInt32(pzScriptID);
  return WeaponType_GetWeaponTypeFromID(v1);
}

// source: j/0/weapons/weapontype.c:1799  [anchor-callee]
struct WeaponType_s *__cdecl WeaponType_GetWeaponTypeFromID(int eWeaponTypeID)
{
  struct WeaponType_s *result; // eax
  struct QTask_s *ptHead; // ecx
  int v3; // edx
  struct QTask_s *v4; // eax
  int eQTaskType; // eax
  struct WeaponTypeGetWeaponTypeContext_s tContext; // [esp+0h] [ebp-Ch] BYREF

  if ( eWeaponTypeID == -1 )
    return nullptr;
  result = WeaponType_aptWeaponTypeByIDCache[eWeaponTypeID];
  if ( !result )
  {
    tContext.eWeaponTypeID = eWeaponTypeID;
    tContext.pzModel = nullptr;
    tContext.ptWeaponType = nullptr;
    ptHead = WeaponType_ptContainer->tQTaskChildren.ptHead;
    if ( ptHead->ptNext && ptHead )
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
        ((void (__cdecl *)(struct QTask_s *, struct WeaponTypeGetWeaponTypeContext_s *))QTask_aatQTaskFinalEvent[WeaponType_eGetWeaponTypeQTaskEvent][eQTaskType].pfHandler)(
          ptHead,
          &tContext);
        ptHead = (struct QTask_s *)dword_849C7DC[QTask_nProtectedQTaskStackOffset];
        v3 = --QTask_nProtectedQTaskStackOffset;
      }
      while ( ptHead );
      result = tContext.ptWeaponType;
    }
    WeaponType_aptWeaponTypeByIDCache[eWeaponTypeID] = result;
  }
  return result;
}

// source: j/0/weapons/weapontype.c:1837  [anchor-mhash]
struct WeaponType_s *__cdecl WeaponType_GetWeaponTypeFromModel(char *pzModel)
{
  struct WeaponType_s *result; // eax
  struct QTask_s *ptHead; // ecx
  int v3; // edx
  struct QTask_s *v4; // eax
  int eQTaskType; // eax
  struct WeaponTypeGetWeaponTypeContext_s tContext; // [esp+0h] [ebp-Ch] BYREF

  tContext.pzModel = pzModel;
  result = nullptr;
  tContext.eWeaponTypeID = -1;
  tContext.ptWeaponType = nullptr;
  ptHead = WeaponType_ptContainer->tQTaskChildren.ptHead;
  if ( ptHead->ptNext && ptHead )
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
      ((void (__cdecl *)(struct QTask_s *, struct WeaponTypeGetWeaponTypeContext_s *))QTask_aatQTaskFinalEvent[WeaponType_eGetWeaponTypeQTaskEvent][eQTaskType].pfHandler)(
        ptHead,
        &tContext);
      ptHead = (struct QTask_s *)dword_849C7DC[QTask_nProtectedQTaskStackOffset];
      v3 = --QTask_nProtectedQTaskStackOffset;
    }
    while ( ptHead );
    return tContext.ptWeaponType;
  }
  return result;
}

// source: j/0/weapons/weapontype.c:1865  [size]
int __cdecl WeaponType_GetIDFromScriptID(char *zScriptID)
{
  return Script_ParseLineInt32(zScriptID);
}

// source: j/0/weapons/weapontype.c:1890  [anchor-mhash]
void __cdecl WeaponType_RegisterChild(struct QTask_s *ptQTask, struct QTask_s *ptParametersQTask)
{
  struct QTask_s **v2; // esi
  struct QTask_s *eQTaskType; // eax

  v2 = &ptQTask->ptParent->ptParent->ptNext + 5 * ((int)&ptQTask->ptParent[1].ptNext[1].tQTaskRefList.ptMiddle + 1);
  eQTaskType = (struct QTask_s *)ptQTask->eQTaskType;
  *v2 = eQTaskType;
  v2[1] = eQTaskType;
  v2[3] = (struct QTask_s *)QTask_NewQTaskRef(ptParametersQTask);
}

// source: j/0/weapons/weapontype.c:1922  [anchor-callee]
void __cdecl WeaponType_EnumerateWeaponTypes(
        void (__cdecl *pfCallback)(struct WeaponType_s *, void *),
        void *pxContext)
{
  struct QTask_s *ptHead; // eax
  int v3; // edx
  struct QTask_s *v4; // ecx
  struct WeaponTypeEnumerateWeaponTypesContext_s tContext; // [esp+0h] [ebp-8h] BYREF

  tContext.pfCallback = pfCallback;
  tContext.pxContext = pxContext;
  ptHead = WeaponType_ptContainer->tQTaskChildren.ptHead;
  if ( ptHead->ptNext && ptHead )
  {
    v3 = QTask_nProtectedQTaskStackOffset;
    do
    {
      if ( ptHead->ptNext )
        v4 = ptHead->ptNext->ptNext != nullptr ? ptHead->ptNext : nullptr;
      else
        v4 = nullptr;
      QTask_atProtectedQTaskStack[v3].ptQTask = v4;
      QTask_nProtectedQTaskStackOffset = v3 + 1;
      ((void (__cdecl *)(struct QTask_s *, struct WeaponTypeEnumerateWeaponTypesContext_s *))QTask_aatQTaskFinalEvent[WeaponType_eEnumerateWeaponTypesQTaskEvent][ptHead->eQTaskType].pfHandler)(
        ptHead,
        &tContext);
      ptHead = (struct QTask_s *)dword_849C7DC[QTask_nProtectedQTaskStackOffset];
      v3 = --QTask_nProtectedQTaskStackOffset;
    }
    while ( ptHead );
  }
}

// source: j/0/weapons/weapontype.c:1944  [anchor-callee]
void __cdecl WeaponType_GetAmmoInfo(
        struct WeaponType_s *ptWeaponType,
        struct WeaponTypeGetAmmoInfoContext_s *ptContext)
{
  memset(ptContext, 0, sizeof(struct WeaponTypeGetAmmoInfoContext_s));
  ((void (__cdecl *)(struct WeaponType_s *, struct WeaponTypeGetAmmoInfoContext_s *))QTask_aatQTaskFinalEvent[WeaponType_eGetAmmoInfoQTaskEvent][ptWeaponType->tQTask.eQTaskType].pfHandler)(
    ptWeaponType,
    ptContext);
}

// source: j/0/weapons/weapontype.c:1962  [anchor-callee]
struct WeaponTypeGetFireTypeScreenPositionContext_s *__cdecl WeaponType_GetFireTypeScreenPosition(
        struct WeaponTypeGetFireTypeScreenPositionContext_s *ptContext)
{
  double v1; // st7
  double v2; // st6
  float vYPos; // [esp+0h] [ebp-4h]

  v1 = (double)Display_tActiveMode.nWidth * 0.984375 - 10.0;
  v2 = (double)Display_tActiveMode.nHeight * 0.9583333134651184 + 4.0;
  if ( ptContext->tIn.nFireType )
  {
    if ( ptContext->tIn.nFireType != 1 )
      return ptContext;
    ptContext->tOut.vTextXPos = v1;
    ptContext->tOut.vTextYPos = v2;
  }
  else
  {
    ptContext->tOut.vTextXPos = v1 - ptContext->tIn.vTextWidth;
    ptContext->tOut.vTextYPos = v2;
    v1 = v1 - ptContext->tIn.vIconWidth;
  }
  ptContext->tOut.vIconXPos = v1;
  vYPos = v2;
  ptContext->tOut.vIconYPos = vYPos + 10.0;
  return ptContext;
}

// source: j/0/weapons/weapontype.c:2004  [size]
void __cdecl WeaponType_LoadSprites()
{
  struct QTask_s *ptHead; // eax
  int v1; // edx
  struct QTask_s *v2; // ecx
  void (__cdecl *pfHandler)(struct QTask_s *, _DWORD); // ecx
  int v4; // edx

  ptHead = WeaponType_ptContainer->tQTaskChildren.ptHead;
  if ( ptHead->ptNext && ptHead )
  {
    v1 = QTask_nProtectedQTaskStackOffset;
    do
    {
      if ( ptHead->ptNext )
        v2 = ptHead->ptNext->ptNext != nullptr ? ptHead->ptNext : nullptr;
      else
        v2 = nullptr;
      QTask_atProtectedQTaskStack[v1].ptQTask = v2;
      pfHandler = (void (__cdecl *)(struct QTask_s *, _DWORD))QTask_aatQTaskFinalEvent[WeaponType_eLoadSpriteQTaskEvent][ptHead->eQTaskType].pfHandler;
      v4 = v1 + 1;
      QTask_nProtectedQTaskStackOffset = v4;
      if ( pfHandler )
      {
        pfHandler(ptHead, 0);
        v4 = QTask_nProtectedQTaskStackOffset;
      }
      ptHead = (struct QTask_s *)dword_849C7DC[v4];
      v1 = v4 - 1;
      QTask_nProtectedQTaskStackOffset = v1;
    }
    while ( ptHead );
  }
}

// source: j/0/weapons/weapontype.c:2019  [size]
void __cdecl WeaponType_UnLoadSprites()
{
  struct QTask_s *ptHead; // eax
  int v1; // edx
  struct QTask_s *v2; // ecx
  void (__cdecl *pfHandler)(struct QTask_s *, _DWORD); // ecx
  int v4; // edx

  ptHead = WeaponType_ptContainer->tQTaskChildren.ptHead;
  if ( ptHead->ptNext && ptHead )
  {
    v1 = QTask_nProtectedQTaskStackOffset;
    do
    {
      if ( ptHead->ptNext )
        v2 = ptHead->ptNext->ptNext != nullptr ? ptHead->ptNext : nullptr;
      else
        v2 = nullptr;
      QTask_atProtectedQTaskStack[v1].ptQTask = v2;
      pfHandler = (void (__cdecl *)(struct QTask_s *, _DWORD))QTask_aatQTaskFinalEvent[WeaponType_eUnLoadSpriteQTaskEvent][ptHead->eQTaskType].pfHandler;
      v4 = v1 + 1;
      QTask_nProtectedQTaskStackOffset = v4;
      if ( pfHandler )
      {
        pfHandler(ptHead, 0);
        v4 = QTask_nProtectedQTaskStackOffset;
      }
      ptHead = (struct QTask_s *)dword_849C7DC[v4];
      v1 = v4 - 1;
      QTask_nProtectedQTaskStackOffset = v1;
    }
    while ( ptHead );
  }
}

// source: j/0/weapons/weapontype.c:2034  [anchor-mhash]
void __cdecl WeaponType_RegisterSprite(char *pzSpriteFilename)
{
  struct QSprite_s *Sprite; // eax
  _DWORD *v3; // esi
  int v4; // esi

  Sprite = WeaponType_GetSprite(pzSpriteFilename);
  if ( Sprite )
  {
    ++Sprite[1].ptPalInfo;
  }
  else
  {
    v3 = Mem_AllocFn(292, 4);
    if ( QSprite_Load((struct QSprite_s *)v3 + 11, pzSpriteFilename) )
    {
      v3[1] = 0;
      *v3 = 0;
      List_AddTail(v3, (int)&WeaponType_tSpriteList);
      strcpy((char *)v3 + 8, pzSpriteFilename);
      v3[72] = 1;
    }
    else if ( v3 )
    {
      v4 = *(_DWORD *)((unsigned int)(v3 - 1) & 0xFFFFFFFC);
      --Mem_nCurrentAllocations;
      Node_Remove((_DWORD **)v4);
      memset(*(void **)(v4 + 8), 0xCDu, *(_DWORD *)(v4 + 16));
      free((void *)v4);
    }
  }
}

// source: j/0/weapons/weapontype.c:2090  [anchor-caller]
void __cdecl WeaponType_UnRegisterSprite(char *pzSpriteFilename)
{
  struct QSprite_s *Sprite; // eax
  struct PalInfo *ptPalInfo; // ecx
  struct QSprite_s *v3; // esi
  int v4; // esi

  Sprite = WeaponType_GetSprite(pzSpriteFilename);
  if ( Sprite )
  {
    ptPalInfo = Sprite[1].ptPalInfo;
    v3 = Sprite - 11;
    Sprite[1].ptPalInfo = (struct PalInfo *)((char *)ptPalInfo - 1);
    if ( (int)&ptPalInfo[-1].pxPalette + 3 <= 0 )
    {
      QSprite_DeAlloc(Sprite);
      Node_Remove(v3);
      v4 = *(_DWORD *)((unsigned int)&v3[-1].nQAnimframes & 0xFFFFFFFC);
      --Mem_nCurrentAllocations;
      Node_Remove((_DWORD **)v4);
      memset(*(void **)(v4 + 8), 0xCDu, *(_DWORD *)(v4 + 16));
      free((void *)v4);
    }
  }
}

// source: j/0/weapons/weapontype.c:2142  [anchor-hash]
struct QSprite_s *__cdecl WeaponType_GetSprite(char *pzSpriteFilename)
{
  struct Node_s *ptHead; // edi
  struct Node_s *ptNext; // esi

  ptHead = WeaponType_tSpriteList.ptHead;
  ptNext = WeaponType_tSpriteList.ptHead->ptNext;
  if ( !WeaponType_tSpriteList.ptHead->ptNext )
    return nullptr;
  while ( _stricmp((char *)&ptHead[1], pzSpriteFilename) )
  {
    ptHead = ptNext;
    ptNext = ptNext->ptNext;
    if ( !ptNext )
      return nullptr;
  }
  return (struct QSprite_s *)&ptHead[33];
}

// source: j/0/weapons/weapontype.c:2172  [size]
__int16 __cdecl WeaponType_GetDrawIconEvent()
{
  return WeaponType_eDrawIconQTaskEvent;
}

// source: j/0/weapons/weapontype.c:2185  [anchor-strings]
void __cdecl WeaponType_Open()
{
  unsigned __int16 BaseQTaskType; // ax
  unsigned __int16 v1; // ax
  unsigned __int16 v2; // ax
  unsigned __int16 v3; // ax
  __int16 v4; // si
  unsigned __int16 v5; // di
  __int16 v6; // ax
  unsigned __int16 v7; // si
  __int16 v8; // di
  __int16 v9; // di
  __int16 v10; // bx
  unsigned __int16 v11; // si
  unsigned __int16 v12; // si
  _DWORD *v13; // esi
  _DWORD *v14; // esi
  _DWORD *v15; // esi
  _DWORD *v16; // esi
  _DWORD *v17; // esi
  _DWORD *v18; // esi
  _DWORD *v19; // esi
  struct ParameterList_s *v20; // eax
  int v21; // edx
  int v22; // edi
  struct ParameterList_s *v23; // ebx
  _DWORD *v24; // eax
  void *v25; // esi
  unsigned int v26; // edi
  char **v27; // esi
  int v28; // edi
  struct ParameterList_s *v29; // ebx
  _DWORD *v30; // eax
  void *v31; // esi
  struct ParameterList_s *v32; // eax
  int v33; // edx
  struct ParameterList_s *v34; // eax
  int v35; // edx
  char *v36; // ecx
  int v37; // eax
  void *v38; // eax
  void *v39; // eax
  char zFilename[4]; // [esp+10h] [ebp-4h] BYREF

  BaseQTaskType = QTask_GetBaseQTaskType();
  WeaponType_eQTaskType = QTask_NewQTaskType("WeaponType", 1948, BaseQTaskType, 0, 0);
  v1 = QTask_GetBaseQTaskType();
  WeaponTypeContainer_eQTaskType = QTask_NewQTaskType("WeaponTypeContainer", 44, v1, 0, 0);
  v2 = QTask_GetBaseQTaskType();
  v3 = QTask_NewQTaskType("WeaponTypeParameterContainer", 44, v2, 0, 0);
  v4 = Level_eAllowSaveQTaskEvent;
  v5 = v3;
  WeaponTypeParameterContainer_eQTaskType = v3;
  QTask_LinkQTaskEventHandlerFn(
    WeaponType_eQTaskType,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveHandler);
  QTask_LinkQTaskEventHandlerFn(
    WeaponTypeContainer_eQTaskType,
    v4,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskDontSaveHandler);
  QTask_LinkQTaskEventHandlerFn(v5, v4, (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveHandler);
  WeaponType_eCreateParametersQTaskEvent = QTask_NewQTaskEventFn(0, "WeaponType-CreateParameters");
  WeaponType_eDeleteParametersQTaskEvent = QTask_NewQTaskEventFn(0, "WeaponType-DeleteParameters");
  WeaponType_eGetWeaponTypeQTaskEvent = QTask_NewQTaskEventFn(0, "WeaponType-Get");
  WeaponType_eCheckForDuplicateQTaskEvent = QTask_NewQTaskEventFn(0, "WeaponType-CheckForDuplicate");
  WeaponType_eEnumerateWeaponTypesQTaskEvent = QTask_NewQTaskEventFn(0, "WeaponType-EnumTypes");
  WeaponType_eLoadSpriteQTaskEvent = QTask_NewQTaskEventFn(0, "WeaponType-LoadSprite");
  WeaponType_eUnLoadSpriteQTaskEvent = QTask_NewQTaskEventFn(0, "WeaponType-UnLoadSprite");
  WeaponType_eDrawIconQTaskEvent = QTask_NewQTaskEventFn(0, "WeaponType-DrawIcon");
  WeaponType_eFindChildrenQTaskEvent = QTask_NewQTaskEventNoContextFn(0, "WeaponType-FindChildren");
  WeaponType_eGetAnimQTaskEvent = QTask_NewQTaskEventFn(0, "WeaponType_GetAnim");
  v6 = QTask_NewQTaskEventFn(0, "WeaponType_GetAmmoInfo");
  v7 = WeaponType_eQTaskType;
  v8 = v6;
  WeaponType_eGetAmmoInfoQTaskEvent = v6;
  QTask_LinkQTaskEventHandlerFn(WeaponType_eQTaskType, 0, WeaponType_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v7, 2, WeaponType_DeleteHandler);
  QTask_LinkQTaskEventHandlerFn(
    v7,
    WeaponType_eEnumerateWeaponTypesQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))WeaponType_EnumWeaponTypesHandler);
  QTask_LinkQTaskEventHandlerFn(v7, WeaponType_eGetWeaponTypeQTaskEvent, WeaponType_GetWeaponTypeHandler);
  QTask_LinkQTaskEventHandlerFn(v7, WeaponType_eGetAnimQTaskEvent, WeaponType_GetAnimHandler);
  QTask_LinkQTaskEventHandlerFn(v7, v8, WeaponType_GetAmmoInfoHandler);
  QTask_LinkQTaskEventHandlerFn(v7, WeaponType_eLoadSpriteQTaskEvent, WeaponType_LoadSpriteHandler);
  QTask_LinkQTaskEventHandlerFn(v7, WeaponType_eUnLoadSpriteQTaskEvent, WeaponType_UnLoadSpriteHandler);
  v9 = ParameterList_eGetParameterListQTaskEvent;
  QTask_LinkQTaskEventHandlerFn(
    v7,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))WeaponType_GetParameterListHandler);
  v10 = ParameterList_eUpdateInternalDataQTaskEvent;
  QTask_LinkQTaskEventHandlerFn(v7, ParameterList_eUpdateInternalDataQTaskEvent, WeaponType_UpdateInternalDataHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(
    v7,
    Level_eUpdateInternalDataAfterLoadEvent,
    WeaponType_UpdateInternalDataAfterLoadHandler);
  QTask_LinkQTaskEventHandlerFn(v7, StatusScreen_eStatusDisplayQTaskEvent, WeaponType_StatusDisplayHandler);
  QTask_LinkQTaskEventHandlerFn(v7, WeaponType_eDrawIconQTaskEvent, WeaponType_DrawIconHandler);
  v11 = WeaponTypeContainer_eQTaskType;
  QTask_LinkQTaskEventHandlerFn(
    WeaponTypeContainer_eQTaskType,
    0,
    (void (__cdecl *)(struct QTask_s *, void *))WeaponTypeContainer_CreateHandler);
  QTask_LinkQTaskEventHandlerFn(
    v11,
    v9,
    (void (__cdecl *)(struct QTask_s *, void *))WeaponTypeContainer_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(
    v11,
    v10,
    (void (__cdecl *)(struct QTask_s *, void *))WeaponTypeContainer_UpdateInternalDataHandler);
  v12 = WeaponTypeParameterContainer_eQTaskType;
  QTask_LinkQTaskEventHandlerFn(WeaponTypeParameterContainer_eQTaskType, 0, WeaponTypeParameterContainer_CreateHandler);
  QTask_LinkQTaskEventHandlerFn(
    v12,
    v9,
    (void (__cdecl *)(struct QTask_s *, void *))WeaponTypeParameterContainer_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(
    v12,
    v10,
    (void (__cdecl *)(struct QTask_s *, void *))WeaponTypeParameterContainer_UpdateInternalDataHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(
    v12,
    WeaponType_eFindChildrenQTaskEvent,
    WeaponTypeParameterContainer_FindChildrenHandler);
  WeaponType_tWeaponCategoryEnumList.pfEnumItemsCallback = ParameterEnumList_EnumerateItemsCallback;
  WeaponType_tWeaponCategoryEnumList.ptHead = (struct ParameterEnumItem_s *)&WeaponType_tWeaponCategoryEnumList.ptMiddle;
  WeaponType_tWeaponCategoryEnumList.ptTail = (struct ParameterEnumItem_s *)&WeaponType_tWeaponCategoryEnumList;
  WeaponType_tWeaponCategoryEnumList.ptMiddle = nullptr;
  v13 = Mem_AllocFn(18444, 4);
  v13[1] = 0;
  *v13 = 0;
  v13[4610] = "WEAPONCATEGORY_.*";
  Wildcard_CreateNFA("WEAPONCATEGORY_.*", v13 + 2, (char *)v13 + 10248);
  List_AddTail(v13, (int)&WeaponType_tWeaponCategoryEnumList);
  WeaponType_tWeaponTypeEnumList.pfEnumItemsCallback = ParameterEnumList_EnumerateItemsCallback;
  WeaponType_tWeaponTypeEnumList.ptHead = (struct ParameterEnumItem_s *)&WeaponType_tWeaponTypeEnumList.ptMiddle;
  WeaponType_tWeaponTypeEnumList.ptTail = (struct ParameterEnumItem_s *)&WeaponType_tWeaponTypeEnumList;
  WeaponType_tWeaponTypeEnumList.ptMiddle = nullptr;
  v14 = Mem_AllocFn(18444, 4);
  v14[1] = 0;
  *v14 = 0;
  v14[4610] = "WEAPONTYPE_.*";
  Wildcard_CreateNFA("WEAPONTYPE_.*", v14 + 2, (char *)v14 + 10248);
  List_AddTail(v14, (int)&WeaponType_tWeaponTypeEnumList);
  WeaponType_tSightDisplayTypeEnumList.pfEnumItemsCallback = ParameterEnumList_EnumerateItemsCallback;
  WeaponType_tSightDisplayTypeEnumList.ptHead = (struct ParameterEnumItem_s *)&WeaponType_tSightDisplayTypeEnumList.ptMiddle;
  WeaponType_tSightDisplayTypeEnumList.ptTail = (struct ParameterEnumItem_s *)&WeaponType_tSightDisplayTypeEnumList;
  WeaponType_tSightDisplayTypeEnumList.ptMiddle = nullptr;
  v15 = Mem_AllocFn(18444, 4);
  v15[1] = 0;
  *v15 = 0;
  v15[4610] = "SIGHTDISPLAYTYPE_.*";
  Wildcard_CreateNFA("SIGHTDISPLAYTYPE_.*", v15 + 2, (char *)v15 + 10248);
  List_AddTail(v15, (int)&WeaponType_tSightDisplayTypeEnumList);
  WeaponType_tAmmoDisplayTypeEnumList.pfEnumItemsCallback = ParameterEnumList_EnumerateItemsCallback;
  WeaponType_tAmmoDisplayTypeEnumList.ptHead = (struct ParameterEnumItem_s *)&WeaponType_tAmmoDisplayTypeEnumList.ptMiddle;
  WeaponType_tAmmoDisplayTypeEnumList.ptTail = (struct ParameterEnumItem_s *)&WeaponType_tAmmoDisplayTypeEnumList;
  WeaponType_tAmmoDisplayTypeEnumList.ptMiddle = nullptr;
  v16 = Mem_AllocFn(18444, 4);
  v16[1] = 0;
  *v16 = 0;
  v16[4610] = "AMMODISPLAYTYPE_.*";
  Wildcard_CreateNFA("AMMODISPLAYTYPE_.*", v16 + 2, (char *)v16 + 10248);
  List_AddTail(v16, (int)&WeaponType_tAmmoDisplayTypeEnumList);
  WeaponType_tWeaponIDEnumList.pfEnumItemsCallback = ParameterEnumList_EnumerateItemsCallback;
  WeaponType_tWeaponIDEnumList.ptHead = (struct ParameterEnumItem_s *)&WeaponType_tWeaponIDEnumList.ptMiddle;
  WeaponType_tWeaponIDEnumList.ptTail = (struct ParameterEnumItem_s *)&WeaponType_tWeaponIDEnumList;
  WeaponType_tWeaponIDEnumList.ptMiddle = nullptr;
  v17 = Mem_AllocFn(18444, 4);
  v17[1] = 0;
  *v17 = 0;
  v17[4610] = "WEAPON_ID_.*";
  Wildcard_CreateNFA("WEAPON_ID_.*", v17 + 2, (char *)v17 + 10248);
  List_AddTail(v17, (int)&WeaponType_tWeaponIDEnumList);
  WeaponType_tTaskTypeEnumList.pfEnumItemsCallback = ParameterEnumList_EnumerateItemsCallback;
  WeaponType_tTaskTypeEnumList.ptHead = (struct ParameterEnumItem_s *)&WeaponType_tTaskTypeEnumList.ptMiddle;
  WeaponType_tTaskTypeEnumList.ptTail = (struct ParameterEnumItem_s *)&WeaponType_tTaskTypeEnumList;
  WeaponType_tTaskTypeEnumList.ptMiddle = nullptr;
  v18 = Mem_AllocFn(18444, 4);
  v18[1] = 0;
  *v18 = 0;
  v18[4610] = "TASKTYPE_.*";
  Wildcard_CreateNFA("TASKTYPE_.*", v18 + 2, (char *)v18 + 10248);
  List_AddTail(v18, (int)&WeaponType_tTaskTypeEnumList);
  WeaponType_tAIDetectionRangeEnumList.pfEnumItemsCallback = ParameterEnumList_EnumerateItemsCallback;
  WeaponType_tAIDetectionRangeEnumList.ptHead = (struct ParameterEnumItem_s *)&WeaponType_tAIDetectionRangeEnumList.ptMiddle;
  WeaponType_tAIDetectionRangeEnumList.ptTail = (struct ParameterEnumItem_s *)&WeaponType_tAIDetectionRangeEnumList;
  WeaponType_tAIDetectionRangeEnumList.ptMiddle = nullptr;
  v19 = Mem_AllocFn(18444, 4);
  v19[1] = 0;
  *v19 = 0;
  v19[4610] = "HUMANAI_DETECTIONEVENT_.*_RANGE";
  Wildcard_CreateNFA("HUMANAI_DETECTIONEVENT_.*_RANGE", v19 + 2, (char *)v19 + 10248);
  List_AddTail(v19, (int)&WeaponType_tAIDetectionRangeEnumList);
  v20 = (struct ParameterList_s *)Mem_AllocFn(1252, 4);
  v21 = Level_eParameterTypeString32;
  v20->ptParameterListItem = (struct ParameterListItem_s *)&v20[1];
  v20->nParameters = 0;
  v20->nMaxParameters = 62;
  WeaponType_ptParameterList = v20;
  ParameterList_AddParameter(v20, 0x54u, v21, "Weapon ID", 7u, nullptr);
  ParameterList_AddParameter(
    WeaponType_ptParameterList,
    0x9Cu,
    Level_eParameterTypeString256,
    "Weapon Name",
    7u,
    nullptr);
  ParameterList_AddParameter(
    WeaponType_ptParameterList,
    0x19Cu,
    Level_eParameterTypeString256,
    "Weapon Animation Name",
    7u,
    nullptr);
  ParameterList_AddParameter(
    WeaponType_ptParameterList,
    0x53Cu,
    Level_eParameterTypeString256,
    "Weapon Sprite",
    7u,
    nullptr);
  ParameterList_AddParameter(
    WeaponType_ptParameterList,
    0x29Cu,
    ParameterEnumList_eParameterTypeInt32,
    "Weapon Type",
    7u,
    &WeaponType_tWeaponTypeEnumList);
  ParameterList_AddParameter(
    WeaponType_ptParameterList,
    0x2A0u,
    ParameterEnumList_eParameterTypeInt32,
    "Weapon Category",
    7u,
    &WeaponType_tWeaponCategoryEnumList);
  ParameterList_AddParameter(
    WeaponType_ptParameterList,
    0x2C4u,
    ParameterEnumList_eParameterTypeInt32,
    "Sight Display Type",
    7u,
    &WeaponType_tSightDisplayTypeEnumList);
  ParameterList_AddParameter(
    WeaponType_ptParameterList,
    0x2A4u,
    Level_eParameterTypeString32,
    "Fixed Model (Used by GunPickup)",
    7u,
    nullptr);
  ParameterList_AddParameterMinMax(
    WeaponType_ptParameterList,
    0x340u,
    Level_eParameterTypeInt32,
    "Available FireModes",
    7u,
    0.0,
    3.0);
  v22 = Level_eParameterTypeInt32;
  v23 = WeaponType_ptParameterList;
  v24 = Mem_AllocFn(24, 4);
  v25 = v24 + 2;
  v24[1] = 0;
  *v24 = 0;
  v24[2] = 0;
  v24[3] = 0;
  v24[4] = 0;
  v24[5] = 1090021888;
  List_AddTail(v24, (int)&ParameterList_tParameterScalarContextList);
  ParameterList_AddParameterArray(v23, 0x2C8u, v22, "Firemode Rounds In Succession", 7u, v25, 4u, 3u);
  ParameterList_AddParameterArray(
    WeaponType_ptParameterList,
    0x2D4u,
    Level_eParameterTypeString32,
    "Firemode Name",
    7u,
    nullptr,
    0x20u,
    3u);
  ParameterList_AddParameterArray(
    WeaponType_ptParameterList,
    0x334u,
    Level_eParameterTypeReal32,
    "Firemode Firesound Stop Time",
    7u,
    nullptr,
    4u,
    3u);
  ParameterList_AddParameter(
    WeaponType_ptParameterList,
    0x348u,
    Level_eParameterTypeDegrees,
    "Standing Precision (Degrees)",
    7u,
    nullptr);
  ParameterList_AddParameter(
    WeaponType_ptParameterList,
    0x34Cu,
    Level_eParameterTypeDegrees,
    "Running Precision (Degrees)",
    7u,
    nullptr);
  ParameterList_AddParameter(
    WeaponType_ptParameterList,
    0x350u,
    Level_eParameterTypeDegrees,
    "Walking Precision (Degrees)",
    7u,
    nullptr);
  ParameterList_AddParameter(
    WeaponType_ptParameterList,
    0x354u,
    Level_eParameterTypeDegrees,
    "Crouching Precision (Degrees)",
    7u,
    nullptr);
  ParameterList_AddParameter(
    WeaponType_ptParameterList,
    0x358u,
    Level_eParameterTypeDegrees,
    "Crouch Walking Precision (Degrees)",
    7u,
    nullptr);
  ParameterList_AddParameter(
    WeaponType_ptParameterList,
    0x35Cu,
    Level_eParameterTypeDegrees,
    "Lying Flat Precision (Degrees)",
    7u,
    nullptr);
  ParameterList_AddParameter(
    WeaponType_ptParameterList,
    0x360u,
    Level_eParameterTypeDegrees,
    "Crawling Precision (Degrees)",
    7u,
    nullptr);
  ParameterList_AddParameterMinMax(
    WeaponType_ptParameterList,
    0x364u,
    Level_eParameterTypeReal32,
    "Jumping Precision Modifier",
    7u,
    0.0,
    5.0);
  ParameterList_AddParameterMinMax(
    WeaponType_ptParameterList,
    0x368u,
    Level_eParameterTypeReal32,
    "Turning Precision Modifier",
    7u,
    0.0,
    5.0);
  ParameterList_AddParameterMinMax(
    WeaponType_ptParameterList,
    0x36Cu,
    Level_eParameterTypeReal32,
    "Movement Speed Modifier",
    7u,
    0.0,
    1.0);
  ParameterList_AddParameterMinMax(
    WeaponType_ptParameterList,
    0x370u,
    Level_eParameterTypeReal32,
    "(De)Activate Time",
    7u,
    0.0,
    30.0);
  ParameterList_AddParameter(
    WeaponType_ptParameterList,
    0x374u,
    Level_eParameterTypeString32,
    "1st Person Stand Anim",
    7u,
    nullptr);
  ParameterList_AddParameter(
    WeaponType_ptParameterList,
    0x394u,
    Level_eParameterTypeString32,
    "1st Person Move Anim",
    7u,
    nullptr);
  ParameterList_AddParameter(
    WeaponType_ptParameterList,
    0x3B4u,
    Level_eParameterTypeString32,
    "1st Person Activate Anim",
    7u,
    nullptr);
  ParameterList_AddParameter(
    WeaponType_ptParameterList,
    0x3D4u,
    Level_eParameterTypeString32,
    "1st Person DeActivate Anim",
    7u,
    nullptr);
  ParameterList_AddParameter(
    WeaponType_ptParameterList,
    0x3F4u,
    Level_eParameterTypeString32,
    "3rd Person Stand Anim",
    7u,
    nullptr);
  ParameterList_AddParameter(
    WeaponType_ptParameterList,
    0x414u,
    Level_eParameterTypeString32,
    "3rd Person Walk Anim",
    7u,
    nullptr);
  ParameterList_AddParameter(
    WeaponType_ptParameterList,
    0x434u,
    Level_eParameterTypeString32,
    "3rd Person Run Anim",
    7u,
    nullptr);
  ParameterList_AddParameter(
    WeaponType_ptParameterList,
    0x454u,
    Level_eParameterTypeString32,
    "3rd Person Crouch Stand Anim",
    7u,
    nullptr);
  ParameterList_AddParameter(
    WeaponType_ptParameterList,
    0x474u,
    Level_eParameterTypeString32,
    "3rd Person Crouch Walk Anim",
    7u,
    nullptr);
  ParameterList_AddParameter(
    WeaponType_ptParameterList,
    0x494u,
    Level_eParameterTypeString32,
    "3rd Person Activate Anim",
    7u,
    nullptr);
  ParameterList_AddParameter(
    WeaponType_ptParameterList,
    0x4B4u,
    Level_eParameterTypeString32,
    "3rd Person DeActivate Anim",
    7u,
    nullptr);
  ParameterList_AddParameter(
    WeaponType_ptParameterList,
    0x4D4u,
    Level_eParameterTypeString32,
    "Activate Sound",
    7u,
    nullptr);
  ParameterList_AddParameter(
    WeaponType_ptParameterList,
    0x4F4u,
    Level_eParameterTypeString32,
    "DeActivate Sound",
    7u,
    nullptr);
  ParameterList_AddParameter(
    WeaponType_ptParameterList,
    0x28u,
    Level_eParameterTypeString16,
    "TracerTexture",
    7u,
    nullptr);
  ParameterList_AddParameter(
    WeaponType_ptParameterList,
    0x48u,
    Level_eParameterTypeReal32,
    "TracerVelocity(m/s)",
    7u,
    nullptr);
  v26 = 1308;
  v27 = (char **)&WeaponType_apzFireTypeParameterNames[0][1];
  do
  {
    ParameterList_AddParameter(
      WeaponType_ptParameterList,
      v26 - 8,
      ParameterEnumList_eParameterTypeInt32,
      *(v27 - 1),
      7u,
      &WeaponType_tTaskTypeEnumList);
    ParameterList_AddParameter(WeaponType_ptParameterList, v26, Level_eParameterTypebool8, *v27, 7u, nullptr);
    ParameterList_AddParameter(WeaponType_ptParameterList, v26 + 1, Level_eParameterTypebool8, v27[1], 7u, nullptr);
    v27 += 3;
    v26 += 20;
  }
  while ( (int)v27 < 7053128 );
  ParameterList_AddParameter(
    WeaponType_ptParameterList,
    0x344u,
    Level_eParameterTypebool8,
    "Selectable When Empty",
    7u,
    nullptr);
  ParameterList_AddParameter(
    WeaponType_ptParameterList,
    0x658u,
    Level_eParameterTypeString256,
    "Pickup sprite",
    7u,
    nullptr);
  ParameterList_AddParameter(WeaponType_ptParameterList, 0x790u, Level_eParameterTypebool8, "Laser Dot", 7u, nullptr);
  ParameterList_AddParameter(
    WeaponType_ptParameterList,
    0x791u,
    Level_eParameterTypebool8,
    "Laser Dot Always On",
    7u,
    nullptr);
  ParameterList_AddParameter(
    WeaponType_ptParameterList,
    0x770u,
    Level_eParameterTypeInt32,
    "Netshop price",
    7u,
    nullptr);
  ParameterList_AddParameter(
    WeaponType_ptParameterList,
    0x775u,
    Level_eParameterTypebool8,
    "Bad Guys can buy",
    7u,
    nullptr);
  ParameterList_AddParameter(
    WeaponType_ptParameterList,
    0x774u,
    Level_eParameterTypebool8,
    "Good Guys can buy",
    7u,
    nullptr);
  ParameterList_AddParameter(
    WeaponType_ptParameterList,
    0x778u,
    Level_eParameterTypeInt32,
    "Netshop category",
    7u,
    nullptr);
  ParameterList_AddParameter(
    WeaponType_ptParameterList,
    0x77Cu,
    Level_eParameterTypeInt32,
    "Netshop slot position",
    7u,
    nullptr);
  v28 = Level_eParameterTypeReal32;
  v29 = WeaponType_ptParameterList;
  v30 = Mem_AllocFn(24, 4);
  v30[1] = 0;
  *v30 = 0;
  v31 = v30 + 2;
  v30[2] = 0x40000000;
  v30[3] = 1067743969;
  v30[4] = 0;
  v30[5] = 1076101120;
  List_AddTail(v30, (int)&ParameterList_tParameterScalarContextList);
  ParameterList_AddParameter(v29, 0x794u, v28, "Smoke Particle Size", 7u, v31);
  ParameterList_AddParameter(
    WeaponType_ptParameterList,
    0x798u,
    Level_eParameterTypebool8,
    "Can weapon be dropped in 1P game",
    7u,
    nullptr);
  v32 = (struct ParameterList_s *)Mem_AllocFn(32, 4);
  v33 = Level_eParameterTypePushButton;
  v32->ptParameterListItem = (struct ParameterListItem_s *)&v32[1];
  v32->nParameters = 0;
  v32->nMaxParameters = 1;
  WeaponTypeContainer_ptParameterList = v32;
  ParameterList_AddParameter(v32, 0x28u, v33, "Save", 6u, nullptr);
  v34 = (struct ParameterList_s *)Mem_AllocFn(32, 4);
  v34->ptParameterListItem = (struct ParameterListItem_s *)&v34[1];
  v35 = Level_eParameterTypeInt32;
  v34->nParameters = 0;
  v34->nMaxParameters = 1;
  WeaponTypeParameterContainer_ptParameterList = v34;
  ParameterList_AddParameter(v34, 0x28u, v35, "Parameter ID", 5u, nullptr);
  Symbol_Register(
    "WEAPON_ID_UNDEFINED",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)0xFFFFFFFF,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "TASKTYPE_NONE",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)0x200,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "WEAPONCATEGORY_NONE",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    nullptr,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "WEAPONCATEGORY_KNIFE",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)1,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "WEAPONCATEGORY_SIDEARM",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)2,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "WEAPONCATEGORY_PRIMARY",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)3,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "WEAPONCATEGORY_MEDIPACK",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)8,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "WEAPONCATEGORY_GRENADE",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)4,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "WEAPONCATEGORY_PROXIMITYMINE",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)5,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "WEAPONCATEGORY_FLASHBANG",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)6,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "WEAPONCATEGORY_SMOKEGRENADE",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)7,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "WEAPONCATEGORY_BINOCULARS",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)0xC,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "WEAPONCATEGORY_C4",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)9,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "WEAPONCATEGORY_LASERDESIGNATOR",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)0xA,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "WEAPONCATEGORY_THERMOCHEMICAL",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)0xB,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "WEAPONCATEGORY_EXPLOSIVE",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    nullptr,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "WEAPONCATEGORY_RPG",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    nullptr,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "WEAPONCATEGORY_OTHER",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    nullptr,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "WEAPONTYPE_GUN",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    nullptr,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "WEAPONTYPE_PISTOL",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)1,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "WEAPONTYPE_SHOTGUN",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)2,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "WEAPONTYPE_KNIFE",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)3,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "WEAPONTYPE_GRENADE",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)4,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "WEAPONTYPE_BINOCULAR",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)5,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "WEAPONTYPE_MEDIPACK",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)6,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "WEAPONTYPE_PROXIMITYMINE",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)7,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "WEAPONTYPE_C4BOMB",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)8,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "WEAPONTYPE_SPECIAL",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)9,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "SIGHTDISPLAYTYPE_NONE",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    nullptr,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "SIGHTDISPLAYTYPE_PISTOL",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)1,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "SIGHTDISPLAYTYPE_SNIPERRIFLE",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)8,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "SIGHTDISPLAYTYPE_SHOTGUN",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)2,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "SIGHTDISPLAYTYPE_SMG",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)3,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "SIGHTDISPLAYTYPE_ASSAULTRIFLE",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)4,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "SIGHTDISPLAYTYPE_MINIMI",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)5,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "SIGHTDISPLAYTYPE_RPG",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)6,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "SIGHTDISPLAYTYPE_GRENADE",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)7,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "SIGHTDISPLAYTYPE_CROSSHAIR",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    nullptr,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "SIGHTDISPLAYTYPE_CIRCLE",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    nullptr,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AMMODISPLAYTYPE_NONE",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    nullptr,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AMMODISPLAYTYPE_NORMAL",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)1,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AMMODISPLAYTYPE_CLIP",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)2,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AMMODISPLAYTYPE_BARREL",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)3,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AMMODISPLAYTYPE_SHELL",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)4,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "AMMODISPLAYTYPE_GRENADE",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)5,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  File_RegisterAlias("WEAPONS:", "LOCAL:weapons/");
  if ( Resource_IsLoadedInternal("LOCAL:weapons/weapons.res", (struct Resource_s **)zFilename) )
  {
    v37 = *(_DWORD *)zFilename;
    *(_DWORD *)(*(_DWORD *)zFilename + 44) = 1;
    v38 = *(void **)(v37 + 52);
  }
  else
  {
    Game_MPRunNetwork(v36);
    v39 = File_Load("LOCAL:weapons/weapons.res", (unsigned int *)zFilename);
    if ( !v39 )
    {
      LDebug_Error("Failed to load resource: '%s'", "LOCAL:weapons/weapons.res");
      abort();
    }
    v38 = Resource_ParseFile(File_zLastSubstitutedPath, v39, *(unsigned int *)zFilename);
  }
  WeaponType_pxWeaponResource = v38;
  memset(WeaponType_aptWeaponTypeByIDCache, 0, sizeof(WeaponType_aptWeaponTypeByIDCache));
  WeaponType_tSpriteList.ptMiddle = nullptr;
  WeaponType_tSpriteList.ptHead = (struct Node_s *)&WeaponType_tSpriteList.ptMiddle;
  WeaponType_tSpriteList.ptTail = (struct Node_s *)&WeaponType_tSpriteList;
}

// source: j/0/weapons/weapontype.c:2426  [anchor-hash]
void __cdecl WeaponType_Close()
{
  struct Resource_s *ptHead; // ecx
  struct Resource_s *ptNext; // eax
  unsigned int nType; // eax
  int v3; // esi
  int v4; // esi
  int v5; // esi

  ptHead = Resource_tResourceList.ptHead;
  ptNext = Resource_tResourceList.ptHead->ptNext;
  if ( Resource_tResourceList.ptHead->ptNext )
  {
    while ( ptHead->pxData != WeaponType_pxWeaponResource )
    {
      ptHead = ptNext;
      ptNext = ptNext->ptNext;
      if ( !ptNext )
        goto LABEL_8;
    }
    nType = ptHead->nType;
    if ( nType != 3 && nType != 1 )
      Resource_Remove(ptHead);
  }
LABEL_8:
  File_RemoveAlias("WEAPONS:");
  Symbol_Remove("WEAPON_ID_UNDEFINED");
  ParameterEnumList_DeAlloc(&WeaponType_tWeaponCategoryEnumList);
  ParameterEnumList_DeAlloc(&WeaponType_tWeaponTypeEnumList);
  ParameterEnumList_DeAlloc(&WeaponType_tSightDisplayTypeEnumList);
  ParameterEnumList_DeAlloc(&WeaponType_tAmmoDisplayTypeEnumList);
  ParameterEnumList_DeAlloc(&WeaponType_tWeaponIDEnumList);
  ParameterEnumList_DeAlloc(&WeaponType_tTaskTypeEnumList);
  ParameterEnumList_DeAlloc(&WeaponType_tAIDetectionRangeEnumList);
  if ( WeaponTypeParameterContainer_ptParameterList )
  {
    v3 = *(_DWORD *)((unsigned int)&WeaponTypeParameterContainer_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v3);
    memset(*(void **)(v3 + 8), 0xCDu, *(_DWORD *)(v3 + 16));
    free((void *)v3);
  }
  if ( WeaponTypeContainer_ptParameterList )
  {
    v4 = *(_DWORD *)((unsigned int)&WeaponTypeContainer_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v4);
    memset(*(void **)(v4 + 8), 0xCDu, *(_DWORD *)(v4 + 16));
    free((void *)v4);
  }
  if ( WeaponType_ptParameterList )
  {
    v5 = *(_DWORD *)((unsigned int)&WeaponType_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v5);
    memset(*(void **)(v5 + 8), 0xCDu, *(_DWORD *)(v5 + 16));
    free((void *)v5);
  }
  QTask_DeleteQTaskEvent(WeaponType_eCreateParametersQTaskEvent);
  QTask_DeleteQTaskEvent(WeaponType_eDeleteParametersQTaskEvent);
  QTask_DeleteQTaskEvent(WeaponType_eGetWeaponTypeQTaskEvent);
  QTask_DeleteQTaskEvent(WeaponType_eCheckForDuplicateQTaskEvent);
  QTask_DeleteQTaskEvent(WeaponType_eEnumerateWeaponTypesQTaskEvent);
  QTask_DeleteQTaskEvent(WeaponType_eGetAnimQTaskEvent);
  QTask_DeleteQTaskEvent(WeaponType_eGetAmmoInfoQTaskEvent);
  QTask_DeleteQTaskEvent(WeaponType_eLoadSpriteQTaskEvent);
  QTask_DeleteQTaskEvent(WeaponType_eUnLoadSpriteQTaskEvent);
  QTask_DeleteQTaskEvent(WeaponType_eDrawIconQTaskEvent);
  QTask_DeleteQTaskEventNoContext(WeaponType_eFindChildrenQTaskEvent);
  QTask_DeleteQTaskType(WeaponTypeParameterContainer_eQTaskType);
  QTask_DeleteQTaskType(WeaponTypeContainer_eQTaskType);
  QTask_DeleteQTaskType(WeaponType_eQTaskType);
}

// source: j/0/weapons/weapontype.c:2480  [size]
unsigned __int16 __cdecl WeaponType_GetQTaskType()
{
  return WeaponType_eQTaskType;
}

// source: j/0/weapons/weapontype.c:2494  [anchor-strings]
void __cdecl WeaponType_MakeWeaponTypeAnimTables()
{
  struct LODVirModel_s *LODVirModelExistsFn; // eax
  struct QTask_s *ptHead; // esi
  unsigned __int8 *pcHierarchy; // ebx
  struct LODVirModel_s *v3; // eax
  struct QTask_s *v4; // esi
  unsigned __int8 *v5; // ebx

  LODVirModelExistsFn = MTP_GetLODVirModelExistsFn("000_01_1");
  if ( LODVirModelExistsFn )
  {
    ptHead = WeaponType_ptContainer->tQTaskChildren.ptHead;
    pcHierarchy = LODVirModelExistsFn->aptVirModel[0]->ptModel->ptMesh->pcHierarchy;
    if ( ptHead->ptNext )
    {
      if ( ptHead )
      {
        do
        {
          if ( QTask_IsQTaskTypeDerived(ptHead->eQTaskType, WeaponType_eQTaskType) )
            WeaponTypeAnim_MakeAnimTable(ptHead[48].tQTaskChildren.ptHead, pcHierarchy);
          ptHead = ptHead->ptNext;
        }
        while ( ptHead && ptHead->ptNext );
      }
    }
  }
  v3 = MTP_GetLODVirModelExistsFn("jones_1");
  if ( !v3 )
  {
    LDebug_Error("No jones_1 model found");
    abort();
  }
  v4 = WeaponType_ptContainer->tQTaskChildren.ptHead;
  v5 = v3->aptVirModel[0]->ptModel->ptMesh->pcHierarchy;
  if ( v4->ptNext && v4 )
  {
    do
    {
      if ( QTask_IsQTaskTypeDerived(v4->eQTaskType, WeaponType_eQTaskType) )
        WeaponTypeAnim_MakeAnimTable(v4[48].tQTaskChildren.ptMiddle, v5);
      v4 = v4->ptNext;
    }
    while ( v4 && v4->ptNext );
  }
}

// source: j/0/weapons/weapontype.c:2562  [anchor-mhash]
void __cdecl WeaponType_DeleteParameters(struct QReference_s **pptQTaskRef)
{
  struct QTask_s *v1; // ecx
  unsigned __int16 *pxObject; // eax
  void (__cdecl *pfHandler)(unsigned __int16 *, struct WeaponTypeDeleteParameterContext_s *); // edx
  struct WeaponTypeDeleteParameterContext_s tDeleteParameterContext; // [esp+0h] [ebp-4h] BYREF

  tDeleteParameterContext.ptParametersQTask = v1;
  if ( *pptQTaskRef )
  {
    pxObject = (unsigned __int16 *)(*pptQTaskRef)->pxObject;
    if ( pxObject )
    {
      pfHandler = (void (__cdecl *)(unsigned __int16 *, struct WeaponTypeDeleteParameterContext_s *))QTask_aatQTaskFinalEvent[WeaponType_eDeleteParametersQTaskEvent][pxObject[18]].pfHandler;
      if ( pfHandler )
      {
        tDeleteParameterContext.ptParametersQTask = (struct QTask_s *)(*pptQTaskRef)->pxObject;
        pfHandler(pxObject, &tDeleteParameterContext);
        if ( *pptQTaskRef )
        {
          QReference_Delete(*pptQTaskRef, &QTask_tQTaskRefPool);
          *pptQTaskRef = nullptr;
        }
      }
    }
  }
}

// source: j/0/weapons/weapontype.c:2589  [anchor-callee]
struct QReference_s *__cdecl WeaponType_CreateParameters(
        unsigned __int16 eQTaskType,
        struct QTask_s *ptParent)
{
  void (__cdecl *pfHandler)(_DWORD, struct WeaponTypeCreateParameterContext_s *); // eax
  struct WeaponTypeCreateParameterContext_s tCreateParameterContext; // [esp+0h] [ebp-Ch] BYREF

  tCreateParameterContext.ptParent = ptParent;
  tCreateParameterContext.nParameterID = -1;
  tCreateParameterContext.ptParametersQTask = nullptr;
  if ( QTask_IsQTaskTypeValid(eQTaskType)
    && (pfHandler = (void (__cdecl *)(_DWORD, struct WeaponTypeCreateParameterContext_s *))QTask_aatQTaskFinalEvent[WeaponType_eCreateParametersQTaskEvent][eQTaskType].pfHandler) != nullptr
    && (pfHandler(0, &tCreateParameterContext), tCreateParameterContext.ptParametersQTask) )
  {
    return QTask_NewQTaskRef(tCreateParameterContext.ptParametersQTask);
  }
  else
  {
    return nullptr;
  }
}

// source: j/0/weapons/weapontype.c:2619  [anchor-callee]
void __cdecl WeaponType_CalcGunPickupAmmo(
        int *anAmmoCount,
        struct WeaponType_s *ptWeaponType,
        float vClipFraction)
{
  int v3; // eax
  double nRoundsPerClip; // st7
  int v5; // eax
  struct WeaponTypeGetAmmoInfoContext_s tGetAmmoInfoContext; // [esp+Ch] [ebp-28h] BYREF

  memset(&tGetAmmoInfoContext, 0, sizeof(tGetAmmoInfoContext));
  ((void (__cdecl *)(struct WeaponType_s *, struct WeaponTypeGetAmmoInfoContext_s *))QTask_aatQTaskFinalEvent[WeaponType_eGetAmmoInfoQTaskEvent][ptWeaponType->tQTask.eQTaskType].pfHandler)(
    ptWeaponType,
    &tGetAmmoInfoContext);
  v3 = (__int64)((double)tGetAmmoInfoContext.atAmmoItem[0].tOut.nRoundsPerClip * vClipFraction);
  if ( v3 < 1 )
    v3 = 1;
  nRoundsPerClip = (double)tGetAmmoInfoContext.atAmmoItem[1].tOut.nRoundsPerClip;
  *anAmmoCount = v3;
  v5 = (__int64)(nRoundsPerClip * vClipFraction);
  if ( v5 < 1 )
    v5 = 1;
  anAmmoCount[1] = v5;
}

// source: j/0/weapons/weapontype.c:2648  [anchor-callee]
struct AnimHeader_s *__cdecl WeaponType_GetAnimHeaderFromWeaponTypeAnim(
        struct WeaponType_s *ptWeaponType,
        unsigned __int8 *ptHierachy,
        enum WeaponTypeAnim_e eWeaponTypeAnim)
{
  struct QTask_s *ptWeaponTypeAnim1; // eax

  ptWeaponTypeAnim1 = ptWeaponType->ptWeaponTypeAnim1;
  if ( *(unsigned __int8 **)&ptWeaponTypeAnim1[24].eQTaskType == ptHierachy )
    return *((struct AnimHeader_s **)&ptWeaponTypeAnim1[1].ptNext + eWeaponTypeAnim);
  ptWeaponTypeAnim1 = ptWeaponType->ptWeaponTypeAnim2;
  if ( *(unsigned __int8 **)&ptWeaponTypeAnim1[24].eQTaskType == ptHierachy )
    return *((struct AnimHeader_s **)&ptWeaponTypeAnim1[1].ptNext + eWeaponTypeAnim);
  else
    return nullptr;
}

// source: j/0/weapons/weapontype.c:2674  [anchor-callee]
enum WeaponTypeAnim_e __cdecl WeaponType_GetWeaponTypeAnimFromName(
        struct WeaponType_s *ptWeaponType,
        unsigned __int8 *ptHierachy,
        char *zAnimName)
{
  struct QTask_s *ptWeaponTypeAnim1; // ecx

  ptWeaponTypeAnim1 = ptWeaponType->ptWeaponTypeAnim1;
  if ( *(unsigned __int8 **)&ptWeaponTypeAnim1[24].eQTaskType == ptHierachy )
    return WeaponTypeAnim_GetWeaponTypeAnimFromName(ptWeaponTypeAnim1, zAnimName);
  ptWeaponTypeAnim1 = ptWeaponType->ptWeaponTypeAnim2;
  if ( *(unsigned __int8 **)&ptWeaponTypeAnim1[24].eQTaskType == ptHierachy )
    return WeaponTypeAnim_GetWeaponTypeAnimFromName(ptWeaponTypeAnim1, zAnimName);
  else
    return WEAPONTYPEANIM_STAND;
}
