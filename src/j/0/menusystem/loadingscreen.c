/* j/0/menusystem/loadingscreen.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/menusystem/loadingscreen.c:84  [anchor-callee]
void __cdecl LoadingScreen_ClearScreen()
{
  unsigned __int8 nX; // bl
  unsigned __int8 tOldBackgroundColor_4; // [esp+8h] [ebp-8h]
  unsigned __int8 tOldBackgroundColor_8; // [esp+Ch] [ebp-4h]

  tOldBackgroundColor_4 = Display_tBackgroundColor.nY;
  tOldBackgroundColor_8 = Display_tBackgroundColor.nZ;
  nX = Display_tBackgroundColor.nX;
  Display_tBackgroundColor.nX = 0;
  Display_tBackgroundColor.nY = 0;
  Display_tBackgroundColor.nZ = 0;
  if ( Display_isModeSet )
    RenderMode_tActiveRenderMode.apfRenderModeMethod[Display_eClearMethod](nullptr);
  Display_tBackgroundColor.nX = nX;
  Display_tBackgroundColor.nY = tOldBackgroundColor_4;
  Display_tBackgroundColor.nZ = tOldBackgroundColor_8;
}

// source: j/0/menusystem/loadingscreen.c:108  [anchor-mhash]
void *__cdecl LoadingScreen_SetTextColour(void *pxLoadingScreen, float vR, float vG, float vB)
{
  void *result; // eax

  *(float *)(*((_DWORD *)pxLoadingScreen + 7) + 20) = vR * 128.0;
  *(float *)(*((_DWORD *)pxLoadingScreen + 7) + 24) = vG * 128.0;
  result = *((void **)pxLoadingScreen + 7);
  *((float *)result + 7) = vB * 128.0;
  return result;
}

// source: j/0/menusystem/loadingscreen.c:134  [anchor-caller]
void *__cdecl LoadingScreen_New(int nItems, int iMissionID, enum bool isDisplayHint)
{
  #pragma pack(push, 1)
  union
  {
    struct { float vX; };
    struct { float vXa; };
    struct { char igi2_o2[4]; float vY; };
    struct { char igi2_o3[4]; float vYa; };
    struct { char igi2_o4[4]; float vYb; };
    struct { char igi2_o5[28]; char zFilename[4]; };
    struct { char igi2_o6[32]; struct Node_s *v29; };
    struct { char igi2_o7[36]; struct ClippingRect_s ptClippingRect; };
    struct { char igi2_o8[60]; char zName[260]; };
    struct { char igi2_o9[320]; char Buffer[260]; };
    struct { char igi2_o10[580]; char zString[256]; };
    char igi2_extent[836];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct LoadingScreen_s *v3; // eax
  struct Node_s *ptHead; // ecx
  struct LoadingScreen_s *v5; // esi
  struct Node_s *ptNext; // eax
  char *v7; // ecx
  int v8; // eax
  void *v9; // edi
  void *v10; // eax
  struct StaticTilemap_s *v11; // eax
  enum bool v12; // edi
  char *v13; // ecx
  void *v14; // eax
  struct Node_s *v15; // ebx
  int v16; // edi
  struct QSprite_s *Font; // eax
  struct StaticTilemap_s *v19; // eax
  struct QSprite_s *v20; // eax
  struct StaticTilemap_s *v21; // eax

  v3 = (struct LoadingScreen_s *)Mem_AllocFn(116, 4);
  ptHead = Mission_tMissions.ptHead;
  v5 = v3;
  ptNext = Mission_tMissions.ptHead->ptNext;
  if ( Mission_tMissions.ptHead->ptNext )
  {
    while ( ptHead[1].ptNext != (struct Node_s *)iMissionID )
    {
      ptHead = ptNext;
      ptNext = ptNext->ptNext;
      if ( !ptNext )
        goto LABEL_4;
    }
    igi2_frame.v29 = ptHead;
  }
  else
  {
LABEL_4:
    igi2_frame.v29 = nullptr;
  }
  igi2_frame.ptClippingRect.vWidth = (float)Display_tActiveMode.nWidth;
  igi2_frame.ptClippingRect.vX = 0.0;
  igi2_frame.ptClippingRect.vY = 0.0;
  igi2_frame.ptClippingRect.vHeight = (float)Display_tActiveMode.nHeight;
  RenderContext_Alloc(&v5->tRenderContext, 1);
  RenderContext_SetClippingRect(&v5->tRenderContext, &igi2_frame.ptClippingRect);
  v5->nMaxProgress = nItems;
  v5->nActiveProgress = 0;
  if ( !iMissionID )
  {
    v5->ptQPicture = nullptr;
    v5->ptHintScreen = nullptr;
    v5->ptMapText = nullptr;
    v5->ptMapFont = nullptr;
    goto LABEL_32;
  }
  if ( Resource_IsLoadedInternal(
         &g_zFileName.atSpriteResources[43].zResourceFilename[12],
         (struct Resource_s **)igi2_frame.zFilename) )
  {
    v8 = *(_DWORD *)igi2_frame.zFilename;
    *(_DWORD *)(*(_DWORD *)igi2_frame.zFilename + 44) = 1;
    v9 = *(void **)(v8 + 52);
  }
  else
  {
    Game_MPRunNetwork(v7);
    v10 = File_Load(&g_zFileName.atSpriteResources[43].zResourceFilename[12], (unsigned int *)igi2_frame.zFilename);
    if ( !v10 )
    {
      LDebug_Error("Failed to load resource: '%s'", &g_zFileName.atSpriteResources[43].zResourceFilename[12]);
      goto LABEL_11;
    }
    v9 = Resource_ParseFile(File_zLastSubstitutedPath, v10, *(unsigned int *)igi2_frame.zFilename);
  }
  sprintf(igi2_frame.Buffer, (char *const)&g_zFileName.atSpriteResources[42].tSprite, iMissionID);
  if ( Resource_IsLoadedInternal(igi2_frame.Buffer, nullptr) || File_Exists(igi2_frame.Buffer) )
    v11 = Picture_Load(igi2_frame.Buffer);
  else
    v11 = Picture_Load(&g_zFileName.atSpriteResources[42].zResourceFilename[32]);
  v5->ptQPicture = v11;
  Resource_Flush(v9);
  if ( isDisplayHint )
  {
    v12 = Resource_IsLoadedInternal(&g_zFileName.atSpriteResources[42].zResourceFilename[8], nullptr);
    if ( Resource_IsLoadedInternal(
           &g_zFileName.atSpriteResources[42].zResourceFilename[8],
           (struct Resource_s **)igi2_frame.zFilename) )
    {
      *(_DWORD *)(*(_DWORD *)igi2_frame.zFilename + 44) = 1;
      goto LABEL_23;
    }
    Game_MPRunNetwork(v13);
    v14 = File_Load(&g_zFileName.atSpriteResources[42].zResourceFilename[8], (unsigned int *)igi2_frame.zFilename);
    if ( v14 )
    {
      Resource_ParseFile(File_zLastSubstitutedPath, v14, *(unsigned int *)igi2_frame.zFilename);
LABEL_23:
      Game_GetLoadFont(igi2_frame.zName, g_zFileName.atSpriteResources[42].zResourceFilename);
      igi2_frame.vY = (double)Display_tActiveMode.nHeight * 0.75;
      igi2_frame.vX = (double)Display_tActiveMode.nWidth * 0.05000000074505806;
      v5->ptHintScreen = HintsScreen_New(nullptr, igi2_frame.vX, igi2_frame.vY, iMissionID, igi2_frame.zName);
      if ( v12 == false )
        Resource_Unload(&g_zFileName.atSpriteResources[42].zResourceFilename[8]);
      goto LABEL_26;
    }
    LDebug_Error("Failed to load resource: '%s'", &g_zFileName.atSpriteResources[42].zResourceFilename[8]);
LABEL_11:
    abort();
  }
  v5->ptHintScreen = nullptr;
LABEL_26:
  if ( Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER )
  {
    v15 = igi2_frame.v29;
    v16 = 0;
    if ( LOBYTE(igi2_frame.v29[2].ptNext) )
    {
      do
      {
        if ( v16 >= 255 )
          break;
        igi2_frame.zString[v16] = toupper(*((char *)&v15[2].ptNext + v16));
      }
      while ( *((_BYTE *)&v15[2].ptNext + ++v16) );
    }
    igi2_frame.zString[v16] = 0;
    Game_GetLoadFont(igi2_frame.zName, off_6A5454);
    Font = FontManager_LoadFont(igi2_frame.zName);
    v5->ptMapFont = Font;
    igi2_frame.vYa = (double)Display_tActiveMode.nHeight * 0.20000000298023224;
    igi2_frame.vXa = (double)Display_tActiveMode.nWidth * 0.5;
    v19 = Text_New(Font, igi2_frame.vXa, igi2_frame.vYa, igi2_frame.zString);
    v5->ptMapText = v19;
    v19->bQGraphicFlags |= 0x80u;
  }
LABEL_32:
  Game_GetLoadFont(igi2_frame.zName, g_zFileName.atSpriteResources[42].zResourceFilename);
  v20 = FontManager_LoadFont(igi2_frame.zName);
  v5->ptStateFont = v20;
  igi2_frame.vYb = (double)Display_tActiveMode.nHeight * 0.9200000166893005;
  v21 = Text_New(v20, 20.0, igi2_frame.vYb, (char *)&g_zInitialValue);
  v5->ptStateText = v21;
  v21->vR = 128.0;
  v5->ptStateText->vG = 128.0;
  v5->ptStateText->vB = 128.0;
  LoadingScreen_UpdateScreen(v5);
  LoadingScreen_UpdateScreen(v5);
  LoadingScreen_UpdateScreen(v5);
  return v5;
}

// source: j/0/menusystem/loadingscreen.c:252  [anchor-callee]
void __cdecl LoadingScreen_Delete(void *pxLoadingScreen)
{
  struct StaticTilemap_s *v2; // eax
  int v3; // esi

  RenderContext_DeAlloc((struct RenderContext_s *)((char *)pxLoadingScreen + 36));
  if ( *((_DWORD *)pxLoadingScreen + 4) )
    Picture_Delete(*((struct StaticTilemap_s **)pxLoadingScreen + 4));
  Text_Delete(*((struct StaticTilemap_s **)pxLoadingScreen + 7));
  FontManager_DeleteFont(*((struct QSprite_s **)pxLoadingScreen + 5));
  if ( Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER )
  {
    v2 = *((struct StaticTilemap_s **)pxLoadingScreen + 8);
    if ( v2 )
    {
      Text_Delete(v2);
      FontManager_DeleteFont(*((struct QSprite_s **)pxLoadingScreen + 6));
    }
  }
  if ( *((_DWORD *)pxLoadingScreen + 28) )
    QTask_Delete(*((struct QTask_s **)pxLoadingScreen + 28));
  v3 = *(_DWORD *)(((int)pxLoadingScreen - 4) & 0xFFFFFFFC);
  --Mem_nCurrentAllocations;
  Node_Remove((_DWORD **)v3);
  memset(*(void **)(v3 + 8), 0xCDu, *(_DWORD *)(v3 + 16));
  free((void *)v3);
}

// source: j/0/menusystem/loadingscreen.c:285  [anchor-callee]
void __cdecl LoadingScreen_UpdateScreen(struct LoadingScreen_s *ptLoadingScreen)
{
  struct StaticTilemap_s *ptQPicture; // eax
  struct StaticTilemap_s *v3; // edi
  int v4; // edx
  int v5; // ecx
  __int16 *anGraphicWidth; // eax
  struct StaticTilemap_s *v7; // ecx
  double nWidth; // st7
  double v9; // st7
  double v10; // st6
  struct StaticTilemap_s *v11; // esi
  struct StaticTilemap_s *ptStateText; // eax
  struct QTilemap_s *ptQTilemap; // eax
  int v14; // ecx
  int v15; // edx
  __int16 *v16; // edi
  int v17; // esi
  __int16 *v18; // edx
  int v19; // ebx
  double v20; // st7
  struct StaticTilemap_s *ptMapText; // edi
  struct QTilemap_s *v22; // esi
  struct QSprite_s *ptQSprite; // ebx
  double v24; // st7
  struct QReference_s *v25; // ecx
  float *v26; // eax
  struct QTask_s *v27; // esi
  double v28; // st7
  double v29; // st6
  unsigned __int16 *pxObject; // eax
  float vX; // [esp+0h] [ebp-48h]
  float vXa; // [esp+0h] [ebp-48h]
  float v33; // [esp+4h] [ebp-44h]
  float v34; // [esp+4h] [ebp-44h]
  float v35; // [esp+8h] [ebp-40h]
  float v36; // [esp+8h] [ebp-40h]
  float v37; // [esp+8h] [ebp-40h]
  float ptQText; // [esp+Ch] [ebp-3Ch]
  float ptQTexta; // [esp+Ch] [ebp-3Ch]
  float ptQTextb; // [esp+Ch] [ebp-3Ch]
  float ptQTextc; // [esp+Ch] [ebp-3Ch]
  float vHeight; // [esp+10h] [ebp-38h]
  float vY; // [esp+20h] [ebp-28h]
  float vWidth; // [esp+24h] [ebp-24h]
  float vWidtha; // [esp+24h] [ebp-24h]
  float v46; // [esp+28h] [ebp-20h]
  float nY; // [esp+38h] [ebp-10h]
  float nYa; // [esp+38h] [ebp-10h]
  float nYb; // [esp+38h] [ebp-10h]
  float nHeight; // [esp+3Ch] [ebp-Ch]
  int nHeighta; // [esp+3Ch] [ebp-Ch]
  float nHeightb; // [esp+3Ch] [ebp-Ch]
  float nX; // [esp+40h] [ebp-8h]
  float nXa; // [esp+40h] [ebp-8h]
  float ptLoadingScreenc = *(float *)&ptLoadingScreen; // [esp+4Ch] [ebp+4h] ARGSLOT
  float ptLoadingScreena = *(float *)&ptLoadingScreen; // [esp+4Ch] [ebp+4h] ARGSLOT
  float ptLoadingScreend = *(float *)&ptLoadingScreen; // [esp+4Ch] [ebp+4h] ARGSLOT
  float ptLoadingScreenb = *(float *)&ptLoadingScreen; // [esp+4Ch] [ebp+4h] ARGSLOT

  ptQPicture = ptLoadingScreen->ptQPicture;
  if ( ptQPicture )
  {
    ptQPicture->nPri = -1;
    v3 = ptLoadingScreen->ptQPicture;
    v4 = v3->ptQTilemap->nHeight;
    v5 = 0;
    if ( v4 > 0 )
    {
      anGraphicWidth = v3->ptQTilemap->anGraphicWidth;
      do
      {
        if ( *anGraphicWidth > v5 )
          v5 = *anGraphicWidth;
        ++anGraphicWidth;
        --v4;
      }
      while ( v4 );
    }
    v3->vX = (float)((Display_tActiveMode.nWidth - v5) / 2);
    v7 = ptLoadingScreen->ptQPicture;
    v7->vY = (float)((Display_tActiveMode.nHeight
                    - v7->ptQTilemap->nHeight
                    * v7->ptQTilemap->ptQSprite->atQAnimframe[v7->ptQTilemap->ptQSprite->nQAnimframes].nHeight)
                   / 2);
  }
  nWidth = (double)Display_tActiveMode.nWidth;
  ptLoadingScreenc = nWidth;
  v9 = nWidth * 0.800000011920929;
  nX = (ptLoadingScreenc - v9) * 0.5;
  v10 = (double)Display_tActiveMode.nHeight;
  nY = 0.9200000166893005 * v10 + v10 * 0.03500000014901161;
  ptLoadingScreena = v9;
  nHeight = v10 * 0.019999999552965164;
  if ( AppContext_tAppContext.isMainMenu == false )
  {
    Display_StartFrame();
    LoadingScreen_ClearScreen();
    qmemcpy(
      &RenderContext_tActiveRenderContext,
      &ptLoadingScreen->tRenderContext,
      sizeof(RenderContext_tActiveRenderContext));
    ++RenderContext_nActiveRenderContextTimeStamp;
    ptLoadingScreen->tRenderContext.ptPrev = nullptr;
    ptLoadingScreen->tRenderContext.ptNext = nullptr;
    List_AddTail(&ptLoadingScreen->tRenderContext.ptNext, (int)&RenderContext_tDrawList);
    v11 = ptLoadingScreen->ptQPicture;
    if ( v11 )
    {
      vWidth = (float)Display_tActiveMode.nHeight;
      vY = (float)Display_tActiveMode.nWidth;
      Q3DPicture_RegisterSize(v11, 0.0, 0.0, vY, vWidth, -1);
    }
    QSprite_RegisterBlank(nX, nY, ptLoadingScreena, nHeight, 38.400001525878906, 12.800000190734863, 12.800000190734863, 0, -1);
    ptQText = (double)ptLoadingScreen->nActiveProgress * ptLoadingScreena / (double)ptLoadingScreen->nMaxProgress;
    QSprite_RegisterBlank(nX, nY, ptQText, nHeight, 128.0, 0.0, 0.0, 0, -1);
    ptLoadingScreen->ptStateText->vX = (float)(int)(__int64)(((double)Display_tActiveMode.nWidth
                                                            - 0.800000011920929 * (double)Display_tActiveMode.nWidth)
                                                           * 0.5
                                                           + (double)Display_tActiveMode.nWidth * 0.009999999776482582);
    ptLoadingScreen->ptStateText->vY = (float)(int)(__int64)((double)Display_tActiveMode.nHeight * 0.9200000166893005);
    ptStateText = ptLoadingScreen->ptStateText;
    QTilemap_Register(
      ptStateText->ptQTilemap,
      ptStateText->vX,
      ptStateText->vY,
      ptStateText->vR,
      ptStateText->vG,
      ptStateText->vB,
      ptStateText->vA,
      ptStateText->vZ,
      ptStateText->bQGraphicFlags | 0x40000000,
      ptStateText->nPri);
    ptQTilemap = ptLoadingScreen->ptStateText->ptQTilemap;
    v14 = ptQTilemap->nHeight;
    v15 = 0;
    if ( v14 > 0 )
    {
      v16 = ptQTilemap->anGraphicWidth;
      do
      {
        if ( *v16 > v15 )
          v15 = *v16;
        ++v16;
        --v14;
      }
      while ( v14 );
      if ( v15 )
      {
        v17 = 0;
        nHeighta = 0;
        if ( ptQTilemap->nHeight > 0 )
        {
          v18 = ptQTilemap->anGraphicWidth;
          v19 = ptQTilemap->nHeight;
          do
          {
            if ( *v18 > v17 )
              v17 = *v18;
            ++v18;
            --v19;
          }
          while ( v19 );
          nHeighta = v17;
        }
        v20 = (double)Display_tActiveMode.nHeight;
        ptLoadingScreend = (float)Display_tActiveMode.nWidth;
        ptQTexta = (double)(ptQTilemap->nHeight
                          * ptQTilemap->ptQSprite->atQAnimframe[ptQTilemap->ptQSprite->nQAnimframes].nHeight)
                 + 0.004999999888241291 * v20
                 + 0.004999999888241291 * v20;
        v35 = ptLoadingScreend * 0.009999999776482582 + ptLoadingScreend * 0.009999999776482582 + (double)nHeighta;
        v33 = v20 * 0.9200000166893005 - 0.004999999888241291 * v20;
        vX = (ptLoadingScreend - ptLoadingScreend * 0.800000011920929) * 0.5;
        QSprite_RegisterBlankA(vX, v33, v35, ptQTexta, 0.0, 0.0, 0.0, 0.5, 0x80000u, 0);
      }
    }
    if ( Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER )
    {
      ptMapText = ptLoadingScreen->ptMapText;
      if ( ptMapText )
      {
        v22 = ptMapText->ptQTilemap;
        ptQSprite = ptMapText->ptQTilemap->ptQSprite;
        ptQTextb = (double)(ptMapText->ptQTilemap->nHeight * ptQSprite->atQAnimframe[ptQSprite->nQAnimframes].nHeight)
                 * 1.399999976158142;
        v36 = (double)Text_GetWidth(ptMapText) * 1.2000000476837158;
        v34 = (double)Display_tActiveMode.nHeight * 0.20000000298023224
            - (double)(v22->nHeight * ptQSprite->atQAnimframe[ptQSprite->nQAnimframes].nHeight) * 0.15000000596046448;
        v24 = (double)Display_tActiveMode.nWidth * 0.5;
        vXa = v24 - (double)Text_GetWidth(ptMapText) * 0.6000000238418579;
        QSprite_RegisterBlankA(vXa, v34, v36, ptQTextb, 0.0, 0.0, 0.0, 0.5, 0x80000u, -1);
        Text_Register(ptLoadingScreen->ptMapText);
      }
    }
    v25 = Game_ptMissionScoreScreenQTaskRef;
    ptLoadingScreenb = 0.0;
    nYa = 0.0;
    if ( Game_ptMissionScoreScreenQTaskRef && (v26 = (float *)Game_ptMissionScoreScreenQTaskRef->pxObject) != nullptr )
    {
      v27 = HintsScreen_ptQTask;
      nHeightb = v26[45];
      ptLoadingScreenb = v26[47];
      nYa = (double)Display_tActiveMode.nHeight * 0.05000000074505806;
      if ( !HintsScreen_ptQTask )
        goto LABEL_34;
    }
    else
    {
      v27 = HintsScreen_ptQTask;
      if ( !HintsScreen_ptQTask )
      {
LABEL_36:
        if ( v25 )
        {
          pxObject = (unsigned __int16 *)v25->pxObject;
          if ( pxObject )
            ((void (__cdecl *)(unsigned __int16 *))QTask_aatQTaskFinalEvent[Screen_eDrawQTaskEvent][pxObject[18]].pfHandler)(pxObject);
        }
        Display_EndFrame();
        return;
      }
      nHeightb = *(float *)&HintsScreen_ptQTask[1].tQTaskRefList.ptMiddle;
    }
    nXa = *(float *)&v27[1].ptParent;
    v46 = nHeightb + nYa + ptLoadingScreenb;
    vWidtha = (double)Display_tActiveMode.nWidth * 0.5 - *(float *)&v27[1].tQTaskRefList.ptTail * 0.5;
    HintsScreen_SetPos(vWidtha, v46);
    ptLoadingScreenb = nXa + ptLoadingScreenb + nYa;
    ((void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[Screen_eDrawQTaskEvent][v27->eQTaskType].pfHandler)(v27);
    v25 = Game_ptMissionScoreScreenQTaskRef;
LABEL_34:
    if ( ptLoadingScreenb != 0.0 )
    {
      v28 = (double)Display_tActiveMode.nHeight * 0.05000000074505806;
      v29 = (double)Display_tActiveMode.nWidth;
      nYb = 0.02500000037252903 * v29;
      vHeight = v28 + v28 + ptLoadingScreenb;
      ptQTextc = v29 - (nYb + nYb);
      v37 = nHeightb - v28;
      QSprite_RegisterBlankA(nYb, v37, ptQTextc, vHeight, 0.0, 0.0, 0.0, 0.5, 0x80000u, 0);
      v25 = Game_ptMissionScoreScreenQTaskRef;
    }
    goto LABEL_36;
  }
}

// source: j/0/menusystem/loadingscreen.c:430  [anchor-caller]
void *__cdecl LoadingScreen_UpdateProgress(void *pxLoadingScreen, int nItem)
{
  void *result; // eax

  *((_DWORD *)pxLoadingScreen + 1) += (int)(nItem);
  LoadingScreen_UpdateScreen((struct LoadingScreen_s *)pxLoadingScreen);
  return result;
}

// source: j/0/menusystem/loadingscreen.c:451  [anchor-mhash]
void __cdecl LoadingScreen_UpdateText(void *pxLoadingScreen, char *zText)
{
  if ( Game_eGameMode == GAME_GAMEMODE_MULTIPLAYER )
  {
    Text_SetString(*((struct StaticTilemap_s **)pxLoadingScreen + 7), zText);
    LoadingScreen_UpdateScreen((struct LoadingScreen_s *)pxLoadingScreen);
    LoadingScreen_UpdateScreen((struct LoadingScreen_s *)pxLoadingScreen);
    LoadingScreen_UpdateScreen((struct LoadingScreen_s *)pxLoadingScreen);
  }
}
