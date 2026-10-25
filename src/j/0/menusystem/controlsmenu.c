/* j/0/menusystem/controlsmenu.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/menusystem/controlsmenu.c:107  [anchor-mhash]
struct Result_s *__cdecl ControlsMenu_ConvertFloatFromOffsetCB(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  struct ArgList_s *v3; // edi
  double v5; // st6
  struct Result_s Rs; // [esp+10h] [ebp-18h] BYREF

  v3 = ptArgList;
  if ( ptArgList->isQVM )
  {
    ptArgList = nullptr;
    QVM_EvalArg(&ptArgList, 4, v3, 0, 1);
  }
  else
  {
    ptArgList = (struct ArgList_s *)Expression_EvalInt(*ptArgList->aptExpression);
  }
  Rs.zResult = (char *)&g_zInitialValue;
  v5 = (double)(int)ptArgList * 0.023255813866853714;
  Rs.nResult = (__int64)v5;
  Rs.vResult = v5;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/menusystem/controlsmenu.c:126  [anchor-mhash]
struct Result_s *__cdecl ControlsMenu_ConvertOffsetFromFloatCB(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  struct ArgList_s *v3; // edi
  double v4; // st7
  double v5; // st6
  struct Result_s Rs; // [esp+10h] [ebp-18h] BYREF

  v3 = ptArgList;
  if ( ptArgList->isQVM )
  {
    *(float *)&ptArgList = 0.0;
    QVM_EvalArg(&ptArgList, 4, v3, 0, 2);
    v4 = *(float *)&ptArgList;
  }
  else
  {
    v4 = Expression_EvalFloat(*ptArgList->aptExpression);
  }
  Rs.zResult = (char *)&g_zInitialValue;
  v5 = v4 * 43.0 + 0.5;
  Rs.nResult = (__int64)v5;
  Rs.vResult = v5;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/menusystem/controlsmenu.c:145  [anchor-callee]
void __cdecl ControlsMenu_SetInputCodeIndex(
        struct ControlsMenu_t *ptControlsMenu,
        int iAction,
        int iIndex,
        enum bool isSecondaryInput)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct StaticTilemap_s *ptQText; };
    struct { char igi2_o1[4]; char *string[64]; };
    char igi2_extent[260];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  enum bool v4; // edi
  struct StaticTilemap_s *v5; // esi
  char *InputNameAndCode; // eax
  char *v7; // eax

  if ( iAction )
  {
    v4 = isSecondaryInput;
    igi2_frame.ptQText = *(struct StaticTilemap_s **)(iIndex + 4 * (_DWORD)ptControlsMenu + 1116);
    *(_DWORD *)(iIndex + 4 * (_DWORD)ptControlsMenu + 2140) = isSecondaryInput;
  }
  else
  {
    igi2_frame.ptQText = *(struct StaticTilemap_s **)(iIndex + 4 * (_DWORD)ptControlsMenu + 604);
    *(_DWORD *)(iIndex + 4 * (_DWORD)ptControlsMenu + 1628) = isSecondaryInput;
    v4 = isSecondaryInput;
  }
  if ( *(_DWORD *)(iIndex + 4 * (_DWORD)ptControlsMenu + 1628) == *(_DWORD *)(iIndex + 4 * (_DWORD)ptControlsMenu + 2140) )
  {
    v5 = *(struct StaticTilemap_s **)(iIndex + 4 * (_DWORD)ptControlsMenu + 1116);
    if ( v5 )
      Text_SetString(v5, (char *)&g_zInitialValue);
    if ( *(_DWORD *)(iIndex + 4 * (_DWORD)ptControlsMenu + 604) )
    {
      if ( v4 < false )
      {
        Text_SetString(
          *(struct StaticTilemap_s **)(iIndex + 4 * (_DWORD)ptControlsMenu + 604),
          (char *)&g_zInitialValue);
      }
      else
      {
        InputNameAndCode = (char *)Config_GetInputNameAndCode(
                                           isSecondaryInput,
                                           (int *)0x100,
                                           (char **)igi2_frame.string);
        Text_SetString(*(struct StaticTilemap_s **)(iIndex + 4 * (_DWORD)ptControlsMenu + 604), InputNameAndCode);
      }
    }
  }
  else if ( igi2_frame.ptQText )
  {
    if ( v4 < false )
      v7 = (char *)&g_zInitialValue;
    else
      v7 = (char *)Config_GetInputNameAndCode(isSecondaryInput, (int *)0x100, (char **)igi2_frame.string);
    Text_SetString(igi2_frame.ptQText, v7);
  }
}

// source: j/0/menusystem/controlsmenu.c:198  [anchor-callee]
enum bool __cdecl ControlsMenu_IsInputIndexFree(
        struct ControlsMenu_t *ptControlsMenu,
        unsigned int *piAction,
        int iInputIndex)
{
  unsigned int v4; // ecx
  int *i; // eax

  if ( ((dword_6BAEE8[9 * iInputIndex] >> 30) & 3) == 1 && (dword_6BAEE8[9 * iInputIndex] & 0x3FFFFFFF) == 1 )
    return false;
  v4 = 0;
  for ( i = ptControlsMenu->aiSecondaryInputCodeIndex; *(i - 128) != iInputIndex && *i != iInputIndex; ++i )
  {
    if ( (int)++v4 >= 53 )
      return true;
  }
  if ( piAction )
    *piAction = v4;
  return false;
}

// source: j/0/menusystem/controlsmenu.c:236  [anchor-callee]
int *__cdecl ControlsMenu_GetRemapIndexFromActionIndex(
        int iActionIndex,
        int *pnPrimary,
        int *pnSecondary)
{
  int *v3; // edi
  int nRemapButton; // esi
  struct InputOptions_s *p_tInputOptions; // edx
  int *result; // eax
  int bInputButton; // [esp+8h] [ebp-8h]
  int bInputButton_4; // [esp+Ch] [ebp-4h]

  v3 = pnPrimary;
  nRemapButton = Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tInputOptions.nRemapButton;
  p_tInputOptions = &Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tInputOptions;
  *pnPrimary = -1;
  *pnSecondary = -1;
  bInputButton_4 = HIDWORD(Config_atInputButton[iActionIndex].bInputButton);
  result = nullptr;
  for ( bInputButton = Config_atInputButton[iActionIndex].bInputButton;
        (int)result < nRemapButton;
        result = (int *)((char *)result + 1) )
  {
    if ( LODWORD(p_tInputOptions->atRemapButtonTable[0].bInputButton) == bInputButton
      && HIDWORD(p_tInputOptions->atRemapButtonTable[0].bInputButton) == bInputButton_4 )
    {
      if ( v3 )
      {
        *v3 = (int)result;
        v3 = nullptr;
      }
      *pnSecondary = (int)result;
    }
    p_tInputOptions = (struct InputOptions_s *)((char *)p_tInputOptions + 16);
  }
  return result;
}

// source: j/0/menusystem/controlsmenu.c:281  [anchor-mhash]
struct MenuWindow_t *__cdecl ControlsMenu_DrawBorder(
        struct MenuWindow_t *ptMenuWindow,
        float vAlpha,
        enum bool isBox)
{
  #pragma pack(push, 1)
  union
  {
    struct { float v7; };
    struct { char igi2_o1[4]; int nY; };
    struct { char igi2_o2[8]; int nHeight; };
    struct { char igi2_o3[8]; float nHeighta; };
    struct { char igi2_o4[12]; int nX; };
    struct { char igi2_o5[16]; float v12; };
    struct { char igi2_o6[20]; struct QVertexStripContext_s tContext; };
    struct { char igi2_o7[40]; struct QVertex_s atQVertex[5]; };
    char igi2_extent[220];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int nWidth; // ebx
  float *p_vG; // eax
  int v5; // ecx

  igi2_frame.nHeight = ptMenuWindow->nHeight;
  nWidth = ptMenuWindow->nWidth;
  igi2_frame.nX = (Display_tActiveMode.nWidth >> 1) + ptMenuWindow->nXPos - 319;
  igi2_frame.nY = (Display_tActiveMode.nHeight >> 1) + ptMenuWindow->nYPos - 239;
  QVertex_ptActiveTexture = nullptr;
  QVertex_ptActivePalette = nullptr;
  p_vG = &igi2_frame.atQVertex[0].vG;
  v5 = 4;
  do
  {
    *(p_vG - 1) = 0.4000000059604645;
    *p_vG = 0.6000000238418579;
    p_vG[1] = 1.0;
    *(p_vG - 2) = vAlpha;
    *(p_vG - 4) = 0.0;
    *(p_vG - 3) = 0.0;
    *(p_vG - 5) = 1.0;
    p_vG += 9;
    --v5;
  }
  while ( v5 );
  igi2_frame.tContext.nDepth = 0;
  igi2_frame.v12 = (float)igi2_frame.nX;
  igi2_frame.tContext.bFlags = 0x80000;
  igi2_frame.atQVertex[0].vX = igi2_frame.v12;
  igi2_frame.v7 = (float)igi2_frame.nY;
  igi2_frame.tContext.isLine = 1;
  igi2_frame.atQVertex[0].vY = igi2_frame.v7;
  igi2_frame.atQVertex[1].vY = igi2_frame.v7;
  igi2_frame.atQVertex[1].vX = (float)(nWidth + igi2_frame.nX - 1);
  igi2_frame.atQVertex[2].vX = igi2_frame.atQVertex[1].vX;
  igi2_frame.atQVertex[3].vX = igi2_frame.v12;
  igi2_frame.atQVertex[2].vY = (float)(igi2_frame.nHeight + igi2_frame.nY - 1);
  igi2_frame.atQVertex[3].vY = igi2_frame.atQVertex[2].vY;
  qmemcpy(&igi2_frame.atQVertex[4], igi2_frame.atQVertex, sizeof(struct QVertex_s));
  igi2_frame.tContext.nStripLength = 5;
  igi2_frame.tContext.atQVertex = igi2_frame.atQVertex;
  if ( isBox )
    return ((struct MenuWindow_t *(__cdecl *)(struct QVertexStripContext_s *))RenderMode_tActiveRenderMode.apfRenderModeMethod[QVertex_eRegisterQVertexStripMethod])(&igi2_frame.tContext);
  igi2_frame.atQVertex[0].vY = (float)igi2_frame.nY;
  igi2_frame.tContext.nStripLength = 2;
  igi2_frame.atQVertex[0].vX = igi2_frame.v12 + 194.0;
  igi2_frame.atQVertex[1].vX = igi2_frame.atQVertex[0].vX;
  igi2_frame.nHeighta = (double)igi2_frame.nHeight + igi2_frame.v7 - 1.0;
  igi2_frame.atQVertex[1].vY = igi2_frame.nHeighta;
  RenderMode_tActiveRenderMode.apfRenderModeMethod[QVertex_eRegisterQVertexStripMethod](&igi2_frame.tContext);
  igi2_frame.atQVertex[0].vY = (float)igi2_frame.nY;
  igi2_frame.atQVertex[0].vX = igi2_frame.v12 + 364.0;
  igi2_frame.atQVertex[1].vX = igi2_frame.atQVertex[0].vX;
  igi2_frame.atQVertex[1].vY = igi2_frame.nHeighta;
  return ((struct MenuWindow_t *(__cdecl *)(struct QVertexStripContext_s *))RenderMode_tActiveRenderMode.apfRenderModeMethod[QVertex_eRegisterQVertexStripMethod])(&igi2_frame.tContext);
}

// source: j/0/menusystem/controlsmenu.c:368  [anchor-mhash]
void __cdecl ControlsMenu_DrawActionsAndKeys(struct ControlsMenu_t *ptControlsMenu, float vFade)
{
  struct ControlsMenu_t *v2; // esi
  int nItemOffset; // ecx
  int v4; // edi
  int v5; // eax
  double v6; // st7
  char v7; // bl
  double v8; // st7
  int v9; // ebx
  float v10; // esi
  struct QTilemap_s *v11; // ebx
  int v12; // ecx
  int i; // edi
  struct StaticTilemap_s *v14; // eax
  unsigned int bQGraphicFlags; // ecx
  struct QTilemap_s *v16; // ebx
  double v17; // st7
  double v18; // st6
  double v19; // st7
  double v20; // st6
  double v21; // st7
  double v22; // st6
  float v23; // [esp+0h] [ebp-68h]
  float v24; // [esp+0h] [ebp-68h]
  float vR; // [esp+10h] [ebp-58h]
  float vRa; // [esp+10h] [ebp-58h]
  float vRb; // [esp+10h] [ebp-58h]
  float vG; // [esp+14h] [ebp-54h]
  float vGa; // [esp+14h] [ebp-54h]
  float vGb; // [esp+14h] [ebp-54h]
  float v31; // [esp+1Ch] [ebp-4Ch]
  float v32; // [esp+1Ch] [ebp-4Ch]
  float vZ; // [esp+1Ch] [ebp-4Ch]
  int v34; // [esp+24h] [ebp-44h]
  int v35; // [esp+24h] [ebp-44h]
  int nPri; // [esp+24h] [ebp-44h]
  float v37; // [esp+38h] [ebp-30h]
  float vY; // [esp+3Ch] [ebp-2Ch]
  struct StaticTilemap_s **v39; // [esp+40h] [ebp-28h]
  float vX; // [esp+44h] [ebp-24h]
  int nY; // [esp+48h] [ebp-20h]
  float ptQTilemap; // [esp+4Ch] [ebp-1Ch]
  float ptQTilemapb; // [esp+4Ch] [ebp-1Ch]
  float ptQTilemapa; // [esp+4Ch] [ebp-1Ch]
  int iAction; // [esp+50h] [ebp-18h]
  int nX; // [esp+54h] [ebp-14h]
  float vB; // [esp+58h] [ebp-10h]
  float v48; // [esp+5Ch] [ebp-Ch]
  float v49; // [esp+60h] [ebp-8h]
  int v50; // [esp+64h] [ebp-4h]

  v2 = ptControlsMenu;
  nX = (Display_tActiveMode.nWidth >> 1) + ptControlsMenu->tMenuWindow.nXPos - 320;
  nItemOffset = ptControlsMenu->nItemOffset;
  v4 = nItemOffset + 10;
  nY = (Display_tActiveMode.nHeight >> 1) + ptControlsMenu->tMenuWindow.nYPos - 240;
  iAction = nItemOffset;
  v50 = nItemOffset + 10;
  if ( !__OFSUB__(nItemOffset, nItemOffset + 10) )
  {
    v39 = &ptControlsMenu->aptQTextKeyConfig[nItemOffset];
    do
    {
      v5 = (int)*(v39 - 128);
      if ( v5 )
      {
        v6 = (double)nX;
        v7 = v2->aisTab[nItemOffset];
        v37 = v6;
        ptQTilemap = v6 + 4.0;
        *(float *)(v5 + 4) = ptQTilemap;
        v8 = (double)nY;
        vY = v8;
        vX = v8 + 5.0;
        *(float *)(v5 + 8) = vX;
        if ( v7 )
        {
          v9 = *(_DWORD *)(v5 + 36) | 0x80000;
          *(float *)(v5 + 16) = vFade;
          v34 = *(_DWORD *)(v5 + 32);
          v10 = v8 + 5.0;
          v31 = *(float *)(v5 + 12);
          *(_DWORD *)(v5 + 20) = 0;
          *(_DWORD *)(v5 + 24) = 0;
          *(_DWORD *)(v5 + 28) = 0;
          *(_DWORD *)(v5 + 36) = v9;
          QTilemap_Register(*(struct QTilemap_s **)v5, ptQTilemap, vX, 0.0, 0.0, 0.0, vFade, v31, v9 | 0x40000000, v34);
          QSprite_RegisterBlankA(v37, vY, 534.0, 20.0, 15.359999656677246, 35.84000015258789, 98.55999755859375, vFade, 0x80000u, 0);
        }
        else
        {
          v10 = v8 + 5.0;
          v11 = *(struct QTilemap_s **)v5;
          v12 = *(_DWORD *)(v5 + 36) | 0x80000;
          *(float *)(v5 + 16) = vFade;
          v35 = *(_DWORD *)(v5 + 32);
          *(_DWORD *)(v5 + 36) = v12;
          v32 = *(float *)(v5 + 12);
          *(_DWORD *)(v5 + 20) = 1112329421;
          *(_DWORD *)(v5 + 24) = 1117362586;
          *(_DWORD *)(v5 + 28) = 1124073472;
          QTilemap_Register(v11, ptQTilemap, vX, 51.20000076293945, 76.80000305175781, 128.0, vFade, v32, v12 | 0x40000000, v35);
        }
        for ( i = 0; i < 2; ++i )
        {
          if ( i )
            v14 = v39[128];
          else
            v14 = *v39;
          if ( v14 )
          {
            bQGraphicFlags = v14->bQGraphicFlags;
            v14->vA = vFade;
            v16 = v14->ptQTilemap;
            bQGraphicFlags |= 0x80000u;
            v14->vY = vX;
            nPri = v14->nPri;
            v14->bQGraphicFlags = bQGraphicFlags;
            vZ = v14->vZ;
            ptQTilemapb = (double)(170 * i) + v37 + 198.0;
            v14->vX = ptQTilemapb;
            v14->vR = 128.0;
            v14->vG = 96.0;
            v14->vB = 0.0;
            QTilemap_Register(v16, ptQTilemapb, v10, 128.0, 96.0, 0.0, vFade, vZ, bQGraphicFlags | 0x40000000, nPri);
          }
        }
        vB = 16.0;
        if ( (iAction & 1) != 0 )
        {
          v17 = 16.0;
        }
        else
        {
          vB = 32.0;
          v17 = 32.0;
        }
        if ( (iAction & 1) != 0 )
          v18 = 16.0;
        else
          v18 = 32.0;
        ptQTilemapa = vFade * 0.5;
        vG = v17 * 0.5;
        vR = v18 * 0.20000000298023224;
        QSprite_RegisterBlankA(v37, vY, 194.0, 20.0, vR, vG, vB, ptQTilemapa, 0x80000u, 0);
        v48 = 32.0;
        if ( (iAction & 1) != 0 )
        {
          v19 = 32.0;
        }
        else
        {
          v19 = 48.0;
          v48 = 48.0;
        }
        if ( (iAction & 1) != 0 )
          v20 = 32.0;
        else
          v20 = 48.0;
        vGa = v19 * 0.5;
        vRa = v20 * 0.20000000298023224;
        v23 = v37 + 194.0;
        QSprite_RegisterBlankA(v23, vY, 170.0, 20.0, vRa, vGa, v48, ptQTilemapa, 0x80000u, 0);
        v49 = 32.0;
        if ( (iAction & 1) != 0 )
        {
          v21 = 32.0;
        }
        else
        {
          v21 = 48.0;
          v49 = 48.0;
        }
        if ( (iAction & 1) != 0 )
          v22 = 32.0;
        else
          v22 = 48.0;
        vGb = v21 * 0.5;
        vRb = v22 * 0.20000000298023224;
        v24 = v37 + 364.0;
        QSprite_RegisterBlankA(v24, vY, 170.0, 20.0, vRb, vGb, v49, ptQTilemapa, 0x80000u, 0);
        v4 = v50;
        nItemOffset = iAction;
        v2 = ptControlsMenu;
      }
      ++nItemOffset;
      nY += 20;
      iAction = nItemOffset;
      ++v39;
    }
    while ( nItemOffset < v4 );
  }
}

// source: j/0/menusystem/controlsmenu.c:495  [anchor-mhash]
int __cdecl ControlsMenu_CalculateIndexFromInput(
        enum InputPortDevice_e eInputPortDevice,
        int nDeviceSource)
{
  __int32 v2; // edx
  int result; // eax
  int *v4; // ecx

  v2 = nDeviceSource | (eInputPortDevice << 30);
  result = 0;
  v4 = &dword_6BAEE8;
  while ( *v4 != v2 )
  {
    v4 += 9;
    ++result;
    if ( (int)v4 >= 7061196 )
      return -1;
  }
  return result;
}

// source: j/0/menusystem/controlsmenu.c:526  [size]
int __cdecl ControlsMenu_CalculateInputFromIndex(int iIndex)
{
  return dword_6BAEE8[9 * iIndex];
}

// source: j/0/menusystem/controlsmenu.c:543  [anchor-strings]
void __cdecl ControlsMenu_InitData(struct ControlsMenu_t *ptControlsMenu)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct StaticTilemap_s **aptQTextAction; };
    struct { char igi2_o1[4]; struct ControlsMenu_t *iActionIndex; };
    struct { char igi2_o2[8]; struct ConfigInputButton_s *v18; };
    struct { char igi2_o3[12]; int pnPrimary; };
    struct { char igi2_o4[16]; int v20; };
    struct { char igi2_o5[20]; int pnSecondary; };
    char igi2_extent[24];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct ControlsMenu_t *v1; // edi
  char *v2; // ebp
  struct ConfigInputButton_s *v3; // esi
  char *LocalizedStringForLanguage; // esi
  struct QTilemap_s **v5; // ebx
  struct QTilemap_s *ptQTilemap; // edx
  struct QTilemap_s *v7; // ebx
  int v8; // ecx
  int anID; // eax
  int v10; // edi
  enum bool v11; // edx
  int *v12; // ecx
  enum bool v13; // esi
  int *v14; // ecx
  bool v15; // cc

  v1 = ptControlsMenu;
  igi2_frame.v20 = 2752 * Config_tConfig.iActiveProfile + 7392712;
  v2 = nullptr;
  v3 = Config_atInputButton;
  igi2_frame.iActionIndex = nullptr;
  igi2_frame.v18 = Config_atInputButton;
  igi2_frame.aptQTextAction = ptControlsMenu->aptQTextAction;
  do
  {
    v2[(_DWORD)v1 + 2656] = strstr(v3->zButton, (char *)&stru_6908E0.tQTaskChildren.ptMiddle) != nullptr;
    LocalizedStringForLanguage = Config_GetLocalizedStringForLanguage(
                                   v3->zButton,
                                   Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eLanguage,
                                   true);
    v5 = (struct QTilemap_s **)*igi2_frame.aptQTextAction;
    ptQTilemap = (*igi2_frame.aptQTextAction)->ptQTilemap;
    memset(ptQTilemap->anGraphicWidth, 0, 2 * ptQTilemap->nHeight);
    memset(ptQTilemap->anID, 0, ptQTilemap->nHeight * ptQTilemap->nWidth);
    v7 = *v5;
    v8 = *(unsigned __int8 *)LocalizedStringForLanguage;
    anID = (int)v7->ptQSprite->ptQTilemap->anID;
    if ( *LocalizedStringForLanguage )
    {
      v10 = v7->anID - (unsigned __int8 *)LocalizedStringForLanguage;
      do
      {
        LocalizedStringForLanguage[v10] = *(_BYTE *)((unsigned __int8)v8 + anID);
        LOBYTE(v8) = *++LocalizedStringForLanguage;
      }
      while ( (_BYTE)v8 );
    }
    QTilemap_UpdateGraphicWidth(v7, 0);
    ControlsMenu_GetRemapIndexFromActionIndex((int)igi2_frame.iActionIndex, &igi2_frame.pnPrimary, &igi2_frame.pnSecondary);
    v11 = false;
    v12 = &dword_6BAEE8;
    while ( *v12 != (*(_DWORD *)(16 * igi2_frame.pnPrimary + igi2_frame.v20 + 12) | (*(_DWORD *)(16 * igi2_frame.pnPrimary + igi2_frame.v20 + 8) << 30)) )
    {
      v12 += 9;
      ++v11;
      if ( (int)v12 >= 7061196 )
      {
        v11 = -1;
        break;
      }
    }
    v13 = false;
    v14 = &dword_6BAEE8;
    while ( *v14 != (*(_DWORD *)(igi2_frame.v20 + 16 * igi2_frame.pnSecondary + 12) | (*(_DWORD *)(16 * igi2_frame.pnSecondary + igi2_frame.v20 + 8) << 30)) )
    {
      v14 += 9;
      ++v13;
      if ( (int)v14 >= 7061196 )
      {
        v13 = -1;
        break;
      }
    }
    v1 = ptControlsMenu;
    ControlsMenu_SetInputCodeIndex(igi2_frame.iActionIndex, 0, (int)ptControlsMenu, v11);
    ControlsMenu_SetInputCodeIndex(igi2_frame.iActionIndex, 1, (int)ptControlsMenu, v13);
    v3 = igi2_frame.v18 + 1;
    v2 = (char *)&igi2_frame.iActionIndex->tMenuWindow.tQTask.ptNext + 1;
    v15 = (int)igi2_frame.v18[1].zButton < 7055656;
    igi2_frame.iActionIndex = (struct ControlsMenu_t *)((char *)igi2_frame.iActionIndex + 1);
    ++igi2_frame.aptQTextAction;
    ++igi2_frame.v18;
  }
  while ( v15 );
}

// source: j/0/menusystem/controlsmenu.c:600  [anchor-mhash]
void __cdecl ControlsMenu_ChangeData(struct ControlsMenu_t *ptControlsMenu)
{
  _DWORD *v1; // eax
  int v2; // esi
  char *aisTab; // ebx
  unsigned __int64 *p_bInputButton; // ecx
  int *aiSecondaryInputCodeIndex; // edi
  int v6; // edx
  int v7; // edx
  int v8; // edx
  int v9; // edx

  v1 = (_DWORD *)(2752 * Config_tConfig.iActiveProfile + 7392712);
  v2 = 0;
  aisTab = ptControlsMenu->aisTab;
  p_bInputButton = &Config_atInputButton[0].bInputButton;
  aiSecondaryInputCodeIndex = ptControlsMenu->aiSecondaryInputCodeIndex;
  do
  {
    if ( !*aisTab )
    {
      v6 = *(aiSecondaryInputCodeIndex - 128);
      if ( v6 >= 0 )
      {
        *v1 = *(_DWORD *)p_bInputButton;
        v7 = dword_6BAEE8[9 * v6];
        v1[1] = *((_DWORD *)p_bInputButton + 1);
        v1[2] = (v7 >> 30) & 3;
        v1[3] = v7 & 0x3FFFFFFF;
        ++v2;
        v1 += 4;
      }
      v8 = *aiSecondaryInputCodeIndex;
      if ( *(aiSecondaryInputCodeIndex - 128) != *aiSecondaryInputCodeIndex && v8 >= 0 )
      {
        *v1 = *(_DWORD *)p_bInputButton;
        v9 = dword_6BAEE8[9 * v8];
        v1[1] = *((_DWORD *)p_bInputButton + 1);
        v1[2] = (v9 >> 30) & 3;
        v1[3] = v9 & 0x3FFFFFFF;
        ++v2;
        v1 += 4;
      }
    }
    ++aiSecondaryInputCodeIndex;
    p_bInputButton += 5;
    ++aisTab;
  }
  while ( (int)p_bInputButton < 7055688 );
  Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tInputOptions.nRemapButton = v2;
}

// source: j/0/menusystem/controlsmenu.c:645  [anchor-callee]
void __cdecl ControlsMenu_ResetToDefaultSettings(struct ControlsMenu_t *ptControlsMenu)
{
  int iActiveProfile; // eax

  iActiveProfile = Config_tConfig.iActiveProfile;
  qmemcpy(
    &Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tInputOptions,
    Config_atDefaultRemapButtonTable,
    0x530u);
  Config_tConfig.atPlayerProfile[iActiveProfile].tInputOptions.nRemapButton = 83;
  Config_tConfig.atPlayerProfile[iActiveProfile].tInputOptions.isInvertMouse = 1;
  Config_tConfig.atPlayerProfile[iActiveProfile].tInputOptions.vMouseSensitivity = 0.4000000059604645;
  ControlsMenu_InitData(ptControlsMenu);
}

// source: j/0/menusystem/controlsmenu.c:662  [anchor-mhash]
void __cdecl ControlsMenu_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  int v2; // ecx
  struct QTask_s **p_ptPrev; // eax

  ((void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[0][MenuWindow_eQTaskType].pfHandler)(
    ptQTask,
    pxContext);
  ptQTask[1].tQTaskRefList.ptTail = (struct QReference_s *)1;
  ptQTask[1].ptParent = (struct QTask_s *)1;
  ptQTask[1].ptNext = (struct QTask_s *)300;
  ptQTask[1].ptPrev = (struct QTask_s *)230;
  ptQTask[1].tQTaskChildren.ptHead = (struct QTask_s *)534;
  ptQTask[1].tQTaskChildren.ptMiddle = (struct QTask_s *)200;
  v2 = 0;
  p_ptPrev = &ptQTask[15].ptPrev;
  do
  {
    *(p_ptPrev - 128) = nullptr;
    *p_ptPrev = nullptr;
    p_ptPrev[128] = nullptr;
    *((_BYTE *)&ptQTask[66].tQTaskChildren.ptTail + v2++) = 0;
    ++p_ptPrev;
  }
  while ( v2 < 53 );
  ptQTask[66].tQTaskChildren.ptMiddle = nullptr;
  LOBYTE(ptQTask[69].tQTaskRefList.ptMiddle) = 0;
  ptQTask[69].tQTaskRefList.ptTail = (struct QReference_s *)-1;
  BYTE1(ptQTask[69].tQTaskRefList.ptMiddle) = 0;
  BYTE2(ptQTask[69].tQTaskRefList.ptMiddle) = 0;
  *(_DWORD *)&ptQTask[69].eQTaskType = 0;
  ControlsMenu_tRandomState.anRandom[0] = -923067897;
  ControlsMenu_tRandomState.anRandom[1] = 971667286;
  ControlsMenu_tRandomState.anRandom[2] = 2146516173;
}

// source: j/0/menusystem/controlsmenu.c:716  [anchor-mhash]
void __cdecl ControlsMenu_DeleteHandler(struct QTask_s *ptQTask)
{
  struct QTask_s **p_ptPrev; // ebx
  struct QTilemap_s **v2; // esi
  int v3; // esi
  struct QTilemap_s **v4; // esi
  int v5; // esi
  struct QTilemap_s **v6; // esi
  int v7; // esi
  int v8; // [esp+10h] [ebp-4h]

  p_ptPrev = &ptQTask[15].ptPrev;
  v8 = 53;
  do
  {
    v2 = (struct QTilemap_s **)*(p_ptPrev - 128);
    if ( v2 )
    {
      QTilemap_Delete(*v2);
      v3 = *(_DWORD *)((unsigned int)(v2 - 1) & 0xFFFFFFFC);
      --Mem_nCurrentAllocations;
      Node_Remove((_DWORD **)v3);
      memset(*(void **)(v3 + 8), 0xCDu, *(_DWORD *)(v3 + 16));
      free((void *)v3);
      *(p_ptPrev - 128) = nullptr;
    }
    v4 = (struct QTilemap_s **)*p_ptPrev;
    if ( *p_ptPrev )
    {
      QTilemap_Delete(*v4);
      v5 = *(_DWORD *)((unsigned int)(v4 - 1) & 0xFFFFFFFC);
      --Mem_nCurrentAllocations;
      Node_Remove((_DWORD **)v5);
      memset(*(void **)(v5 + 8), 0xCDu, *(_DWORD *)(v5 + 16));
      free((void *)v5);
      *p_ptPrev = nullptr;
    }
    v6 = (struct QTilemap_s **)p_ptPrev[128];
    if ( v6 )
    {
      QTilemap_Delete(*v6);
      v7 = *(_DWORD *)((unsigned int)(v6 - 1) & 0xFFFFFFFC);
      --Mem_nCurrentAllocations;
      Node_Remove((_DWORD **)v7);
      memset(*(void **)(v7 + 8), 0xCDu, *(_DWORD *)(v7 + 16));
      free((void *)v7);
      p_ptPrev[128] = nullptr;
    }
    ++p_ptPrev;
    --v8;
  }
  while ( v8 );
  ((void (__cdecl *)())QTask_aatQTaskFinalEvent[Level_eRemoveLevelScriptSymbolsEvent][ptQTask->eQTaskType].pfHandler)(ptQTask);
}

// source: j/0/menusystem/controlsmenu.c:761  [anchor-strings]
void __cdecl ControlsMenu_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s **p_ptPrev; // esi
  struct QTilemap_s **v3; // edi
  int v4; // ebx
  struct QTilemap_s **v5; // edi
  int v6; // ebx
  struct QTilemap_s **v7; // edi
  int v8; // ebx
  struct QTask_s *v9; // ebx
  struct QSprite_s *Font; // ebx
  struct ConfigInputButton_s *v11; // edi
  _DWORD *v12; // esi
  char *LocalizedStringForLanguage; // eax
  struct StaticTilemap_s *v14; // eax
  struct StaticTilemap_s *v15; // eax
  struct StaticTilemap_s *v16; // eax
  int v17; // [esp+10h] [ebp-4h]

  p_ptPrev = &ptQTask[15].ptPrev;
  v17 = 53;
  do
  {
    v3 = (struct QTilemap_s **)*(p_ptPrev - 128);
    if ( v3 )
    {
      QTilemap_Delete(*v3);
      v4 = *(_DWORD *)((unsigned int)(v3 - 1) & 0xFFFFFFFC);
      --Mem_nCurrentAllocations;
      Node_Remove((_DWORD **)v4);
      memset(*(void **)(v4 + 8), 0xCDu, *(_DWORD *)(v4 + 16));
      free((void *)v4);
      *(p_ptPrev - 128) = nullptr;
    }
    v5 = (struct QTilemap_s **)*p_ptPrev;
    if ( *p_ptPrev )
    {
      QTilemap_Delete(*v5);
      v6 = *(_DWORD *)((unsigned int)(v5 - 1) & 0xFFFFFFFC);
      --Mem_nCurrentAllocations;
      Node_Remove((_DWORD **)v6);
      memset(*(void **)(v6 + 8), 0xCDu, *(_DWORD *)(v6 + 16));
      free((void *)v6);
      *p_ptPrev = nullptr;
    }
    v7 = (struct QTilemap_s **)p_ptPrev[128];
    if ( v7 )
    {
      QTilemap_Delete(*v7);
      v8 = *(_DWORD *)((unsigned int)(v7 - 1) & 0xFFFFFFFC);
      --Mem_nCurrentAllocations;
      Node_Remove((_DWORD **)v8);
      memset(*(void **)(v8 + 8), 0xCDu, *(_DWORD *)(v8 + 16));
      free((void *)v8);
      p_ptPrev[128] = nullptr;
    }
    ++p_ptPrev;
    --v17;
  }
  while ( v17 );
  v9 = *(struct QTask_s **)&ptQTask[1].eQTaskType;
  if ( v9 )
    Font = MenuManager_GetFont(v9, (char *)&stru_6908E0);
  else
    Font = (struct QSprite_s *)ptQTask;
  if ( Font )
  {
    v11 = Config_atInputButton;
    v12 = &ptQTask[15].ptPrev;
    do
    {
      LocalizedStringForLanguage = Config_GetLocalizedStringForLanguage(
                                     v11->zButton,
                                     Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eLanguage,
                                     true);
      v14 = Text_New(Font, 0.0, 0.0, LocalizedStringForLanguage);
      *(v12 - 128) = v14;
      v14->nPri = 0;
      v15 = Text_New(Font, 0.0, 0.0, (char *)&g_zInitialValue);
      *v12 = v15;
      v15->nPri = 0;
      v16 = Text_New(Font, 0.0, 0.0, (char *)&g_zInitialValue);
      v12[128] = v16;
      ++v11;
      ++v12;
      v16->nPri = 0;
    }
    while ( (int)v11 < 7055656 );
  }
  ((void (__cdecl *)())QTask_aatQTaskFinalEvent[ParameterList_eUpdateInternalDataQTaskEvent][MenuWindow_eQTaskType].pfHandler)(ptQTask, pxContext);
}

// source: j/0/menusystem/controlsmenu.c:851  [anchor-caller]
void __cdecl ControlsMenu_RunHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { int nWidth; };
    struct { char igi2_o1[4]; char Buffer[32]; };
    char igi2_extent[36];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *v1; // edi
  unsigned int bButton; // esi
  struct ControlsMenu_t *ptTail; // ebx
  enum bool v4; // ebp
  BOOL v5; // esi
  int v6; // eax
  int *v7; // edx
  int v8; // ecx
  unsigned int v9; // ecx
  int v10; // eax
  struct ControlsMenu_t *v11; // esi
  int v12; // eax
  int p_ptPrev; // edx
  bool v14; // zf
  struct StaticTilemap_s *v15; // esi
  char *LocalizedString; // eax

  v1 = ptQTask;
  if ( BYTE2(ptQTask[69].tQTaskRefList.ptMiddle) )
  {
    ControlsMenu_ResetToDefaultSettings((struct ControlsMenu_t *)ptQTask);
    BYTE2(v1[69].tQTaskRefList.ptMiddle) = 0;
  }
  if ( !BYTE1(v1[69].tQTaskRefList.ptMiddle) )
  {
    MenuWindow_HitTest(
      (struct MenuWindow_t *)v1,
      (int)v1[1].ptNext,
      (int)v1[1].ptPrev,
      (int)v1[1].tQTaskChildren.ptHead,
      (int)v1[1].tQTaskChildren.ptMiddle,
      &igi2_frame.nWidth,
      (int *)&ptQTask);
    if ( HIBYTE(v1[2].ptNext) )
    {
      v12 = (int)v1[66].tQTaskChildren.ptMiddle + ((char *)ptQTask - (char *)v1[1].ptPrev) / 20;
      v1[69].tQTaskRefList.ptTail = (struct QReference_s *)v12;
      if ( !*((_BYTE *)&v1[66].tQTaskChildren.ptTail + v12) )
      {
        p_ptPrev = (int)&v1[1].ptNext[9].ptPrev;
        v14 = igi2_frame.nWidth <= p_ptPrev;
        *(_DWORD *)&v1[69].eQTaskType = igi2_frame.nWidth > p_ptPrev;
        if ( v14 )
          v15 = *((struct StaticTilemap_s **)&v1[15].ptPrev + v12);
        else
          v15 = *((struct StaticTilemap_s **)&v1[27].eQTaskType + v12);
        if ( v15 )
        {
          LocalizedString = Config_GetLocalizedString("Select a key or button");
          Text_SetString(v15, LocalizedString);
        }
        *(_DWORD *)(*(_DWORD *)&v1[1].eQTaskType + 52) = 4;
        BYTE1(v1[69].tQTaskRefList.ptMiddle) = 1;
        SoundSys_PlaySimpleSoundFn("menu_sel2", 0, nullptr);
      }
    }
    goto LABEL_44;
  }
  bButton = Mouse_tMouse.bButton;
  ptTail = (struct ControlsMenu_t *)v1[69].tQTaskRefList.ptTail;
  if ( (Keyboard_tKeyboard.anCurrentKey[1] & 0x80u) != 0 )
    goto LABEL_44;
  if ( KeyInterface_GetAsciiCode() == -8 )
  {
    v4 = -1;
    SoundSys_PlaySimpleSoundFn("menu_cancel", 0, nullptr);
LABEL_7:
    v5 = 0;
    goto LABEL_8;
  }
  v4 = false;
  v7 = &dword_6BAEE8;
  while ( 1 )
  {
    v8 = *v7;
    if ( ((*v7 >> 30) & 3) != 1 )
      break;
    if ( (Keyboard_tKeyboard.anCurrentKey[v8 & 0x3FFFFFFF] & 0x80u) != 0 )
      goto LABEL_14;
LABEL_17:
    v7 += 9;
    ++v4;
    if ( (int)v7 >= 7061196 )
      goto LABEL_44;
  }
  if ( ((*v7 >> 30) & 3) != 3 || bButton != (v8 & 0x3FFFFFFF) )
    goto LABEL_17;
LABEL_14:
  v9 = (ControlsMenu_tRandomState.anRandom[0] >> 7) ^ ControlsMenu_tRandomState.anRandom[2];
  v10 = (v9 ^ ControlsMenu_tRandomState.anRandom[1]) + ControlsMenu_tRandomState.anRandom[0];
  ControlsMenu_tRandomState.anRandom[1] ^= v9;
  ControlsMenu_tRandomState.anRandom[0] = v10;
  ControlsMenu_tRandomState.anRandom[2] = v9;
  sprintf(igi2_frame.Buffer, "menu_k0%.1d", (int)abs32(v10) % 7 + 1);
  SoundSys_PlaySimpleSoundFn(igi2_frame.Buffer, 0, nullptr);
  if ( v4 < false )
    goto LABEL_7;
  v5 = ControlsMenu_IsInputIndexFree((struct ControlsMenu_t *)v1, (unsigned int *)&ptQTask, v4) == false;
LABEL_8:
  if ( *(_DWORD *)&v1[69].eQTaskType )
  {
    v6 = 1;
    goto LABEL_22;
  }
  if ( *((_DWORD *)&v1[53].tQTaskRefList.ptHead + (_DWORD)ptTail) == *((_DWORD *)&v1[40].tQTaskRefList.ptTail
                                                                     + (_DWORD)ptTail) )
  {
    ControlsMenu_SetInputCodeIndex(ptTail, 0, (int)v1, v4);
    ControlsMenu_SetInputCodeIndex(ptTail, 1, (int)v1, v4);
  }
  else
  {
    v6 = 0;
LABEL_22:
    ControlsMenu_SetInputCodeIndex(ptTail, v6, (int)v1, v4);
  }
  if ( *((int *)&v1[40].tQTaskRefList.ptTail + (_DWORD)ptTail) < 0
    && *((int *)&v1[53].tQTaskRefList.ptHead + (_DWORD)ptTail) >= 0 )
  {
    ControlsMenu_SetInputCodeIndex(
      ptTail,
      0,
      (int)v1,
      *((enum bool *)&v1[53].tQTaskRefList.ptHead + (_DWORD)ptTail));
  }
  if ( v5 )
  {
    v11 = (struct ControlsMenu_t *)ptQTask;
    if ( ptQTask != (struct QTask_s *)ptTail )
    {
      if ( *((_DWORD *)&v1[40].tQTaskRefList.ptTail + (_DWORD)ptQTask) == v4 )
        ControlsMenu_SetInputCodeIndex((struct ControlsMenu_t *)ptQTask, 0, (int)v1, (enum bool)-1);
      if ( *((_DWORD *)&v1[53].tQTaskRefList.ptHead + (_DWORD)v11) == v4 )
        ControlsMenu_SetInputCodeIndex(v11, 1, (int)v1, (enum bool)-1);
      if ( *((int *)&v1[40].tQTaskRefList.ptTail + (_DWORD)v11) < 0
        && *((int *)&v1[53].tQTaskRefList.ptHead + (_DWORD)v11) >= 0 )
      {
        ControlsMenu_SetInputCodeIndex(v11, 0, (int)v1, *((enum bool *)&v1[53].tQTaskRefList.ptHead + (_DWORD)v11));
      }
    }
  }
  tKeyboardBuffer.iBufferIndex = 0;
  tKeyboardBuffer.nBuffer = 0;
  *(_DWORD *)(*(_DWORD *)&v1[1].eQTaskType + 52) = 3;
  BYTE1(v1[69].tQTaskRefList.ptMiddle) = 0;
  v1[69].tQTaskRefList.ptTail = (struct QReference_s *)-1;
LABEL_44:
  ((void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[1][MenuWindow_eQTaskType].pfHandler)(v1);
}

// source: j/0/menusystem/controlsmenu.c:1045  [anchor-mhash]
void __cdecl ControlsMenu_DrawHandler(struct QTask_s *ptQTask)
{
  double v2; // st7
  float ptQTaska = *(float *)&ptQTask; // [esp+8h] [ebp+4h] ARGSLOT

  v2 = (double)(*(_DWORD *)(*(_DWORD *)&ptQTask[1].eQTaskType + 356) - 8) * 0.125;
  if ( v2 <= 0.0 )
    ptQTaska = 0.0;
  else
    ptQTaska = v2;
  ((void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[Screen_eDrawQTaskEvent][MenuWindow_eQTaskType].pfHandler)(ptQTask);
  ControlsMenu_DrawBorder((struct MenuWindow_t *)ptQTask, ptQTaska, true);
  ControlsMenu_DrawActionsAndKeys((struct ControlsMenu_t *)ptQTask, ptQTaska);
  ControlsMenu_DrawBorder((struct MenuWindow_t *)ptQTask, ptQTaska, false);
}

// source: j/0/menusystem/controlsmenu.c:1072  [size]
void __cdecl ControlsMenu_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = ControlsMenu_ptParameterList;
}

// source: j/0/menusystem/controlsmenu.c:1088  [anchor-mhash]
void __cdecl ControlsMenu_RegisterScriptSymbolsHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { char zName[64]; };
    struct { char igi2_o1[64]; char zTemp[128]; };
    char igi2_extent[192];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)

  if ( !LOBYTE(ptQTask[69].tQTaskRefList.ptMiddle) )
  {
    Level_GetUniqueQTaskNameFromTask(igi2_frame.zName, ptQTask);
    sprintf(igi2_frame.zTemp, "%s.nOffset", igi2_frame.zName);
    Symbol_Register(
      igi2_frame.zTemp,
      (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_Int,
      &ptQTask[66].tQTaskChildren.ptMiddle,
      4,
      QSCRIPT_SYMBOLCLASS_VARIABLE,
      QSCRIPT_SYMBOLTYPE_INT,
      QSCRIPT_SYMBOLLIFESPAN_FINITE);
    sprintf(igi2_frame.zTemp, "%s.isReset", igi2_frame.zName);
    Symbol_Register(
      igi2_frame.zTemp,
      (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_Int8,
      (char *)&ptQTask[69].tQTaskRefList.ptMiddle + 2,
      1,
      QSCRIPT_SYMBOLCLASS_VARIABLE,
      QSCRIPT_SYMBOLTYPE_INT,
      QSCRIPT_SYMBOLLIFESPAN_FINITE);
    LOBYTE(ptQTask[69].tQTaskRefList.ptMiddle) = 1;
  }
}

// source: j/0/menusystem/controlsmenu.c:1121  [anchor-refs]
void __cdecl ControlsMenu_RemoveScriptSymbolsHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { char zName[64]; };
    struct { char igi2_o1[64]; char zTemp[128]; };
    char igi2_extent[192];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)

  if ( LOBYTE(ptQTask[69].tQTaskRefList.ptMiddle) )
  {
    Level_GetUniqueQTaskNameFromTask(igi2_frame.zName, ptQTask);
    sprintf(igi2_frame.zTemp, "%s.nOffset", igi2_frame.zName);
    Symbol_Remove(igi2_frame.zTemp);
    sprintf(igi2_frame.zTemp, "%s.isReset", igi2_frame.zName);
    Symbol_Remove(igi2_frame.zTemp);
    LOBYTE(ptQTask[69].tQTaskRefList.ptMiddle) = 0;
  }
}

// source: j/0/menusystem/controlsmenu.c:1151  [anchor-caller]
void __cdecl ControlsMenu_InitDataHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *NextSiblingOfType; // ebx
  int v2; // esi
  struct QReference_s *v3; // eax
  struct QTask_s *ptHead; // ecx
  int v5; // edx
  struct QTask_s *v6; // eax
  int v7; // esi
  void (__cdecl *pfHandler)(struct QTask_s *); // eax
  int v9; // edx

  NextSiblingOfType = QTask_GetNextSiblingOfType(ptQTask, SlideBar_eQTaskType);
  if ( NextSiblingOfType )
  {
    v2 = *(_DWORD *)&ptQTask[1].eQTaskType;
    v3 = *(struct QReference_s **)(v2 + 10236);
    if ( v3 )
    {
      QReference_Delete(v3, &QTask_tQTaskRefPool);
      *(_DWORD *)(v2 + 10236) = 0;
    }
    *(_DWORD *)(v2 + 10236) = QTask_NewQTaskRef(NextSiblingOfType);
  }
  ControlsMenu_InitData((struct ControlsMenu_t *)ptQTask);
  ptHead = ptQTask->tQTaskChildren.ptHead;
  if ( ptHead->ptNext && ptHead )
  {
    v5 = QTask_nProtectedQTaskStackOffset;
    do
    {
      if ( ptHead->ptNext )
        v6 = ptHead->ptNext->ptNext != nullptr ? ptHead->ptNext : nullptr;
      else
        v6 = nullptr;
      v7 = MenuWindow_eInitDataEvent;
      QTask_atProtectedQTaskStack[v5].ptQTask = v6;
      pfHandler = (void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[v7][ptHead->eQTaskType].pfHandler;
      v9 = v5 + 1;
      QTask_nProtectedQTaskStackOffset = v9;
      if ( pfHandler )
      {
        pfHandler(ptHead);
        v9 = QTask_nProtectedQTaskStackOffset;
      }
      ptHead = (struct QTask_s *)dword_849C7DC[v9];
      v5 = v9 - 1;
      QTask_nProtectedQTaskStackOffset = v5;
    }
    while ( ptHead );
  }
}

// source: j/0/menusystem/controlsmenu.c:1178  [anchor-mhash]
void __cdecl ControlsMenu_ChangeDataHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptHead; // ecx
  int v2; // edx
  struct QTask_s *v3; // eax
  int v4; // esi
  void (__cdecl *pfHandler)(struct QTask_s *); // eax
  int v6; // edx

  ControlsMenu_ChangeData((struct ControlsMenu_t *)ptQTask);
  ptHead = ptQTask->tQTaskChildren.ptHead;
  if ( ptHead->ptNext && ptHead )
  {
    v2 = QTask_nProtectedQTaskStackOffset;
    do
    {
      if ( ptHead->ptNext )
        v3 = ptHead->ptNext->ptNext != nullptr ? ptHead->ptNext : nullptr;
      else
        v3 = nullptr;
      v4 = MenuWindow_eChangeDataEvent;
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

// source: j/0/menusystem/controlsmenu.c:1199  [anchor-hash]
void __cdecl ControlsMenu_Open()
{
  unsigned __int16 v0; // si

  v0 = QTask_NewQTaskType("ControlsMenu", 2800, MenuWindow_eQTaskType, 0, 0);
  ControlsMenu_eQTaskType = v0;
  QTask_LinkQTaskEventHandlerFn(
    v0,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 1, ControlsMenu_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, Screen_eDrawQTaskEvent, ControlsMenu_DrawHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 2, ControlsMenu_DeleteHandler);
  QTask_LinkQTaskEventHandlerFn(v0, 0, ControlsMenu_CreateHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))ControlsMenu_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(v0, ParameterList_eUpdateInternalDataQTaskEvent, ControlsMenu_UpdateInternalDataHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(
    v0,
    Level_eRegisterLevelScriptSymbolsEvent,
    ControlsMenu_RegisterScriptSymbolsHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(
    v0,
    Level_eRemoveLevelScriptSymbolsEvent,
    ControlsMenu_RemoveScriptSymbolsHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, MenuWindow_eInitDataEvent, ControlsMenu_InitDataHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, MenuWindow_eChangeDataEvent, ControlsMenu_ChangeDataHandler);
  Symbol_Register(
    "ControlsMenu_ConvertFloatFromOffset",
    ControlsMenu_ConvertFloatFromOffsetCB,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    (char *)&stru_690824.tQTaskRefList.ptTail,
    ControlsMenu_ConvertOffsetFromFloatCB,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
}

// source: j/0/menusystem/controlsmenu.c:1240  [anchor-hash]
void __cdecl ControlsMenu_Close()
{
  Symbol_Remove("ControlsMenu_ConvertFloatFromOffset");
  Symbol_Remove((char *)&stru_690824.tQTaskRefList.ptTail);
  QTask_DeleteQTaskType(ControlsMenu_eQTaskType);
  ControlsMenu_eQTaskType = 512;
}
