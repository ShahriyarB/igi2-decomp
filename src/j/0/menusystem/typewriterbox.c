/* j/0/menusystem/typewriterbox.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/menusystem/typewriterbox.c:250  [anchor-mhash]
void __cdecl TypeWriterBox_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ((void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[0][MenuWindow_eQTaskType].pfHandler)(
    ptQTask,
    pxContext);
  ptQTask[1].tQTaskChildren.ptHead = (struct QTask_s *)100;
  ptQTask[1].tQTaskChildren.ptMiddle = (struct QTask_s *)100;
  ptQTask[1].tQTaskRefList.ptTail = (struct QReference_s *)1;
  ptQTask[1].ptParent = (struct QTask_s *)1;
  ptQTask[3].tQTaskChildren.ptHead = nullptr;
  ptQTask[3].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[3].tQTaskChildren.ptTail = nullptr;
  ptQTask[3].tQTaskRefList.ptHead = nullptr;
  ptQTask[2].tQTaskChildren.ptMiddle = nullptr;
}

// source: j/0/menusystem/typewriterbox.c:285  [anchor-mhash]
void __cdecl TypeWriterBox_DeleteHandler(struct QTask_s *ptQTask)
{
  struct QTilemap_s ***p_tQTaskChildren; // ebx
  int v2; // ebp
  struct QTilemap_s **v3; // esi
  int v4; // esi

  p_tQTaskChildren = (struct QTilemap_s ***)&ptQTask[3].tQTaskChildren;
  v2 = 4;
  do
  {
    v3 = *p_tQTaskChildren;
    if ( *p_tQTaskChildren )
    {
      QTilemap_Delete(*v3);
      v4 = *(_DWORD *)((unsigned int)(v3 - 1) & 0xFFFFFFFC);
      --Mem_nCurrentAllocations;
      Node_Remove((_DWORD **)v4);
      memset(*(void **)(v4 + 8), 0xCDu, *(_DWORD *)(v4 + 16));
      free((void *)v4);
    }
    ++p_tQTaskChildren;
    --v2;
  }
  while ( v2 );
  ((void (__cdecl *)())QTask_aatQTaskFinalEvent[Level_eRemoveLevelScriptSymbolsEvent][ptQTask->eQTaskType].pfHandler)(ptQTask);
}

// source: j/0/menusystem/typewriterbox.c:314  [size]
void __cdecl TypeWriterBox_ChangeLanguageHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptHead; // ecx
  int v2; // edx
  struct QTask_s *v3; // eax
  int v4; // esi
  void (__cdecl *pfHandler)(struct QTask_s *); // eax
  int v6; // edx
  int v7; // ebx
  int v8; // edi
  struct QTask_s *ptTail; // esi
  struct QReference_s *v10; // eax
  char **v11; // esi
  char *LocalizedStringForLanguage; // eax

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
      v4 = MenuWindow_eChangeLanguageEvent;
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
  if ( *(_DWORD *)&ptQTask[1].eQTaskType )
  {
    v7 = 0;
    if ( (int)ptQTask[2].tQTaskRefList.ptHead > 0 )
    {
      v8 = 0;
      do
      {
        ptTail = ptQTask[2].tQTaskChildren.ptTail;
        v10 = (&ptTail->tQTaskRefList.ptMiddle)[v8];
        v11 = (char **)((char *)ptTail + v8 * 4);
        if ( v10 )
          LocalizedStringForLanguage = Config_GetLocalizedStringForLanguage(
                                         v11[7],
                                         *(enum GameLanguage_e *)(*(_DWORD *)&ptQTask[1].eQTaskType + 10044),
                                         true);
        else
          LocalizedStringForLanguage = v11[7];
        v11[8] = LocalizedStringForLanguage;
        ++v7;
        v8 += 9;
      }
      while ( v7 < (int)ptQTask[2].tQTaskRefList.ptHead );
    }
  }
}

// source: j/0/menusystem/typewriterbox.c:353  [anchor-strings]
void __cdecl TypeWriterBox_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct QTask_s *ptMenuManager; };
    struct { char igi2_o1[4]; char *azFonts[4]; };
    char igi2_extent[20];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTilemap_s ***p_tQTaskChildren; // ebx
  struct QTilemap_s **v4; // esi
  int v5; // esi
  unsigned int v6; // esi
  _DWORD *p_ptHead; // edi
  struct QSprite_s *Font; // eax
  struct StaticTilemap_s *v9; // eax
  int v10; // ebx
  int v11; // edi
  struct QTask_s *ptTail; // esi
  struct QReference_s *v13; // eax
  char *v14; // esi
  int ptQTaska = *(int *)&ptQTask; // [esp+28h] [ebp+4h] ARGSLOT

  igi2_frame.ptMenuManager = *(struct QTask_s **)&ptQTask[1].eQTaskType;
  ptQTask[2].tQTaskChildren.ptTail = (struct QTask_s *)TypeWriterBox_atLines;
  ptQTask[2].tQTaskRefList.ptHead = (struct QReference_s *)117;
  p_tQTaskChildren = (struct QTilemap_s ***)&ptQTask[3].tQTaskChildren;
  ptQTaska = 4;
  do
  {
    v4 = *p_tQTaskChildren;
    if ( *p_tQTaskChildren )
    {
      QTilemap_Delete(*v4);
      v5 = *(_DWORD *)((unsigned int)(v4 - 1) & 0xFFFFFFFC);
      --Mem_nCurrentAllocations;
      Node_Remove((_DWORD **)v5);
      memset(*(void **)(v5 + 8), 0xCDu, *(_DWORD *)(v5 + 16));
      free((void *)v5);
    }
    ++p_tQTaskChildren;
    --ptQTaska;
  }
  while ( ptQTaska );
  if ( igi2_frame.ptMenuManager )
  {
    igi2_frame.azFonts[0] = (char *)&g_zFontName_0;
    igi2_frame.azFonts[1] = (char *)&stru_6908E0;
    igi2_frame.azFonts[2] = (char *)&g_zFontName_1;
    igi2_frame.azFonts[3] = (char *)&g_zFontName_0.tQTaskChildren.ptMiddle;
    v6 = 0;
    p_ptHead = &ptQTask[3].tQTaskChildren.ptHead;
    do
    {
      Font = MenuManager_GetFont(igi2_frame.ptMenuManager, igi2_frame.azFonts[v6]);
      if ( Font )
      {
        v9 = Text_New(Font, 0.0, 0.0, (char *)&g_zInitialValue);
        *p_ptHead = v9;
        v9->nPri = 0;
      }
      ++v6;
      ++p_ptHead;
    }
    while ( v6 < 4 );
    v10 = 0;
    if ( (int)ptQTask[2].tQTaskRefList.ptHead > 0 )
    {
      v11 = 0;
      do
      {
        ptTail = ptQTask[2].tQTaskChildren.ptTail;
        v13 = (&ptTail->tQTaskRefList.ptMiddle)[v11];
        v14 = (char *)ptTail + v11 * 4;
        if ( v13 )
          *((_DWORD *)v14 + 8) = Config_GetLocalizedStringForLanguage(
                                   *((char **)v14 + 7),
                                   Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eLanguage,
                                   true);
        else
          *((_DWORD *)v14 + 8) = *((_DWORD *)v14 + 7);
        ++v10;
        v11 += 9;
      }
      while ( v10 < (int)ptQTask[2].tQTaskRefList.ptHead );
    }
  }
  ((void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[ParameterList_eUpdateInternalDataQTaskEvent][MenuWindow_eQTaskType].pfHandler)(
    ptQTask,
    pxContext);
}

// source: j/0/menusystem/typewriterbox.c:437  [anchor-mhash]
void __cdecl TypeWriterBox_RunHandler(struct QTask_s *ptQTask)
{
  int v1; // eax
  struct QReference_s *ptMiddle; // ecx
  struct QTask_s *ptTail; // ebp
  unsigned int v4; // kr00_4
  struct QTask_s *ptParent; // edx
  struct QReference_s *v6; // ecx
  char *v7; // eax
  int v8; // edx
  int v9; // eax

  v1 = *(_DWORD *)&ptQTask[2].eQTaskType;
  if ( v1 )
  {
    *(_DWORD *)&ptQTask[2].eQTaskType = v1 - 1;
  }
  else
  {
    ptMiddle = ptQTask[2].tQTaskRefList.ptMiddle;
    ptTail = ptQTask[2].tQTaskChildren.ptTail;
    v4 = strlen(*((char **)&ptTail->ptParent + 9 * (_DWORD)ptMiddle));
    ptParent = ptQTask[2].ptParent;
    *(_DWORD *)&ptQTask[2].eQTaskType = 3;
    ptQTask[3].ptPrev = nullptr;
    if ( (struct QTask_s *)v4 == ptParent )
    {
      v6 = (struct QReference_s *)((char *)&ptMiddle->ptNext + 1);
      if ( v6 == ptQTask[2].tQTaskRefList.ptHead )
        v6 = nullptr;
      v7 = (char *)ptTail + 36 * (_DWORD)v6;
      v8 = *((_DWORD *)v7 + 4);
      if ( v8 == -1 )
      {
        *(_DWORD *)&ptQTask[2].eQTaskType = 253;
        ptQTask[3].ptPrev = (struct QTask_s *)1;
      }
      else
      {
        *(_DWORD *)&ptQTask[2].eQTaskType = v8 + 3;
      }
      ptQTask[2].tQTaskRefList.ptMiddle = v6;
      ptQTask[2].ptParent = nullptr;
      if ( *((_DWORD *)v7 + 5) )
        ptQTask[2].tQTaskRefList.ptTail = v6;
    }
    else
    {
      ptQTask[2].ptParent = (struct QTask_s *)((char *)&ptParent->ptNext + 1);
    }
  }
  v9 = MenuWindow_eQTaskType;
  ++*(int *)&ptQTask[3].ptNext;
  ((void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[1][v9].pfHandler)(ptQTask);
  *(_BYTE *)(*(_DWORD *)&ptQTask[1].eQTaskType + 9755) = 1;
}

// source: j/0/menusystem/typewriterbox.c:519  [size]
void __cdecl TypeWriterBox_DrawHandler(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { float vX; };
    struct { char igi2_o1[4]; float vY; };
    struct { char igi2_o2[8]; float vWidth; };
    struct { char igi2_o3[12]; float vHeight; };
    struct { char igi2_o4[64]; float g; };
    struct { char igi2_o5[68]; float vR; };
    struct { char igi2_o6[72]; float b; };
    struct { char igi2_o7[76]; int nX; };
    struct { char igi2_o8[76]; int nXa; };
    struct { char igi2_o9[80]; float vA; };
    struct { char igi2_o10[84]; int v34; };
    struct { char igi2_o11[88]; float vFade; };
    struct { char igi2_o12[92]; struct QReference_s *iActiveLine; };
    struct { char igi2_o13[96]; char zTemp[256]; };
    char igi2_extent[352];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  double v1; // st7
  struct QReference_s *ptTail; // ebx
  struct QReference_s *ptHead; // ecx
  int v4; // ecx
  struct QTask_s *v5; // edx
  struct StaticTilemap_s *v6; // esi
  char *v7; // ebp
  int v8; // ebx
  int v9; // eax
  int v10; // eax
  double v11; // st7
  int v12; // edx
  __int16 *v13; // ecx
  int nHeight; // edx
  int v15; // ebx
  __int16 *anGraphicWidth; // ecx
  int v17; // ebx
  double v18; // st7
  struct QTilemap_s *ptQTilemap; // edx
  int v20; // ebx
  __int16 *v21; // ecx
  int v22; // ebp
  int v23; // eax

  v1 = (double)(*(_DWORD *)(*(_DWORD *)&ptQTask[1].eQTaskType + 356) - 8) * 0.125;
  if ( v1 <= 0.0 )
    igi2_frame.vFade = 0.0;
  else
    igi2_frame.vFade = v1;
  ptTail = ptQTask[2].tQTaskRefList.ptTail;
  ptHead = ptQTask[2].tQTaskRefList.ptHead;
  igi2_frame.iActiveLine = ptTail;
  if ( (struct QReference_s *)(((int)&ptTail[-1].pxObject + 3) % (int)ptHead) != ptQTask[2].tQTaskRefList.ptMiddle )
  {
    igi2_frame.v34 = (int)&ptTail[-1].pxObject + 3;
    do
    {
      v4 = 9 * ((int)ptTail % (int)ptHead);
      v5 = ptQTask[2].tQTaskChildren.ptTail;
      v6 = *((struct StaticTilemap_s **)&ptQTask[3].tQTaskChildren.ptHead
           + *((_DWORD *)&v5->tQTaskChildren.ptMiddle + v4));
      v7 = (char *)v5 + 4 * v4;
      if ( v6 )
      {
        v8 = *(_DWORD *)v7;
        v9 = *((_DWORD *)v7 + 2);
        igi2_frame.b = MenuText_atTextColour[v9].b;
        igi2_frame.vR = MenuText_atTextColour[v9].r;
        igi2_frame.nX = *(_DWORD *)v7;
        igi2_frame.g = MenuText_atTextColour[v9].g;
        igi2_frame.vA = igi2_frame.vFade;
        if ( *((_DWORD *)v7 + 1) != -1 )
        {
          if ( ptQTask[3].ptPrev )
          {
            v10 = *(_DWORD *)&ptQTask[2].eQTaskType;
            if ( v10 < 16 )
              igi2_frame.vA = (double)*(int *)&ptQTask[2].eQTaskType * igi2_frame.vFade * 0.0625;
            if ( v10 < 32 )
            {
              v11 = (double)((v10 - 16) & ((v10 - 16 < 0) - 1)) * 0.0625;
              igi2_frame.vR = (igi2_frame.vR - 128.0) * v11 + 128.0;
              igi2_frame.g = (igi2_frame.g - 128.0) * v11 + 128.0;
              igi2_frame.b = (igi2_frame.b - 128.0) * v11 + 128.0;
            }
          }
          Text_SetString(v6, *((char **)v7 + 8));
          if ( v8 )
          {
            if ( v8 >= 0 )
            {
              igi2_frame.nXa = v8 + 8;
            }
            else
            {
              nHeight = v6->ptQTilemap->nHeight;
              v15 = 0;
              if ( nHeight > 0 )
              {
                anGraphicWidth = v6->ptQTilemap->anGraphicWidth;
                do
                {
                  if ( *anGraphicWidth > v15 )
                    v15 = *anGraphicWidth;
                  ++anGraphicWidth;
                  --nHeight;
                }
                while ( nHeight );
              }
              igi2_frame.nXa = (int)ptQTask[1].tQTaskChildren.ptHead + igi2_frame.nX - v15 - 8;
            }
          }
          else
          {
            v12 = v6->ptQTilemap->nHeight;
            if ( v12 > 0 )
            {
              v13 = v6->ptQTilemap->anGraphicWidth;
              do
              {
                if ( *v13 > v8 )
                  v8 = *v13;
                ++v13;
                --v12;
              }
              while ( v12 );
            }
            igi2_frame.nXa = ((int)ptQTask[1].tQTaskChildren.ptHead - v8) >> 1;
          }
          v17 = v6->bQGraphicFlags | 0x80000;
          v6->vX = (float)(int)(__int64)((double)(int)ptQTask[1].ptNext + (double)igi2_frame.nXa);
          v18 = (double)(int)ptQTask[1].ptPrev + (double)*((int *)v7 + 1);
          v6->vA = igi2_frame.vA;
          v6->vR = igi2_frame.vR;
          v6->vG = igi2_frame.g;
          v6->bQGraphicFlags = v17;
          v6->vB = igi2_frame.b;
          v6->vY = (float)(int)(__int64)v18;
          if ( igi2_frame.iActiveLine == ptQTask[2].tQTaskRefList.ptMiddle )
          {
            strncpy(igi2_frame.zTemp, *((char **)v7 + 8), (size_t)ptQTask[2].ptParent);
            igi2_frame.zTemp[(unsigned int)ptQTask[2].ptParent] = 0;
            Text_SetString(v6, igi2_frame.zTemp);
            QTilemap_Register(
              v6->ptQTilemap,
              v6->vX,
              v6->vY,
              v6->vR,
              v6->vG,
              v6->vB,
              v6->vA,
              v6->vZ,
              v6->bQGraphicFlags | 0x40000000,
              v6->nPri);
            if ( ((int)ptQTask[3].ptNext & 8) != 0 )
            {
              ptQTilemap = v6->ptQTilemap;
              v20 = 0;
              if ( v6->ptQTilemap->nHeight > 0 )
              {
                v21 = ptQTilemap->anGraphicWidth;
                v22 = v6->ptQTilemap->nHeight;
                do
                {
                  if ( *v21 > v20 )
                    v20 = *v21;
                  ++v21;
                  --v22;
                }
                while ( v22 );
              }
              v23 = ptQTilemap->nHeight
                  * ptQTilemap->ptQSprite->atQAnimframe[ptQTilemap->ptQSprite->nQAnimframes].nHeight;
              igi2_frame.vHeight = (float)v23;
              igi2_frame.vWidth = (float)((3 * v23) >> 2);
              igi2_frame.vY = (float)(__int64)v6->vY;
              igi2_frame.vX = (float)(int)(v20 + (__int64)v6->vX);
              QSprite_RegisterBlankA(igi2_frame.vX, igi2_frame.vY, igi2_frame.vWidth, igi2_frame.vHeight, igi2_frame.vR, igi2_frame.g, igi2_frame.b, igi2_frame.vA, 0x80000u, 0);
            }
          }
          else
          {
            QTilemap_Register(v6->ptQTilemap, v6->vX, v6->vY, igi2_frame.vR, igi2_frame.g, igi2_frame.b, igi2_frame.vA, v6->vZ, v17 | 0x40000000, v6->nPri);
          }
        }
      }
      ptHead = ptQTask[2].tQTaskRefList.ptHead;
      ptTail = (struct QReference_s *)((char *)&igi2_frame.iActiveLine->ptNext + 1);
      ++igi2_frame.v34;
      igi2_frame.iActiveLine = (struct QReference_s *)((char *)igi2_frame.iActiveLine + 1);
    }
    while ( (struct QReference_s *)(igi2_frame.v34 % (int)ptHead) != ptQTask[2].tQTaskRefList.ptMiddle );
  }
  ((void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[Screen_eDrawQTaskEvent][MenuWindow_eQTaskType].pfHandler)(ptQTask);
  MenuWindow_DrawBorder((struct MenuWindow_t *)ptQTask, 0.5, igi2_frame.vFade, 0);
}

// source: j/0/menusystem/typewriterbox.c:667  [size]
void __cdecl TypeWriterBox_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = TypeWriterBox_ptParameterList;
}

// source: j/0/menusystem/typewriterbox.c:683  [anchor-mhash]
void __cdecl TypeWriterBox_InitDataHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptHead; // ecx
  int v2; // edx
  struct QTask_s *v3; // eax
  int v4; // esi
  void (__cdecl *pfHandler)(struct QTask_s *); // eax
  int v6; // edx

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
      v4 = MenuWindow_eInitDataEvent;
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
  ptQTask[2].ptParent = nullptr;
  ptQTask[2].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[2].tQTaskRefList.ptTail = nullptr;
  ptQTask[3].ptNext = nullptr;
  ptQTask[3].ptPrev = nullptr;
  *(_DWORD *)&ptQTask[2].eQTaskType = 16;
}

// source: j/0/menusystem/typewriterbox.c:708  [size]
void __cdecl TypeWriterBox_ChangeDataHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptHead; // ecx
  int v2; // edx
  struct QTask_s *v3; // eax
  int v4; // esi
  void (__cdecl *pfHandler)(struct QTask_s *); // eax
  int v6; // edx

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

// source: j/0/menusystem/typewriterbox.c:726  [size]
void __cdecl TypeWriterBox_RegisterScriptSymbolsHandler(struct QTask_s *ptQTask)
{
  if ( !ptQTask[2].tQTaskChildren.ptMiddle )
    ptQTask[2].tQTaskChildren.ptMiddle = (struct QTask_s *)1;
}

// source: j/0/menusystem/typewriterbox.c:747  [size]
void __cdecl TypeWriterBox_RemoveScriptSymbolsHandler(struct QTask_s *ptQTask)
{
  if ( ptQTask[2].tQTaskChildren.ptMiddle )
    ptQTask[2].tQTaskChildren.ptMiddle = nullptr;
}

// source: j/0/menusystem/typewriterbox.c:770  [anchor-hash]
void __cdecl TypeWriterBox_Open()
{
  unsigned __int16 v0; // si
  struct ParameterList_s *v1; // eax
  int v2; // edx

  v0 = QTask_NewQTaskType("TypeWriterBox", 144, MenuWindow_eQTaskType, 0, 0);
  TypeWriterBox_eQTaskType = v0;
  QTask_LinkQTaskEventHandlerFn(
    v0,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 1, TypeWriterBox_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, Screen_eDrawQTaskEvent, TypeWriterBox_DrawHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 2, TypeWriterBox_DeleteHandler);
  QTask_LinkQTaskEventHandlerFn(v0, 0, TypeWriterBox_CreateHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))TypeWriterBox_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    ParameterList_eUpdateInternalDataQTaskEvent,
    TypeWriterBox_UpdateInternalDataHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, MenuWindow_eInitDataEvent, TypeWriterBox_InitDataHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, MenuWindow_eChangeDataEvent, TypeWriterBox_ChangeDataHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(
    v0,
    Level_eRegisterLevelScriptSymbolsEvent,
    (void (__cdecl *)(struct QTask_s *))TypeWriterBox_RegisterScriptSymbolsHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(
    v0,
    Level_eRemoveLevelScriptSymbolsEvent,
    (void (__cdecl *)(struct QTask_s *))TypeWriterBox_RemoveScriptSymbolsHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, MenuWindow_eChangeLanguageEvent, TypeWriterBox_ChangeLanguageHandler);
  v1 = (struct ParameterList_s *)Mem_AllocFn(52, 4);
  v2 = Level_eParameterTypeInt32;
  v1->ptParameterListItem = (struct ParameterListItem_s *)&v1[1];
  v1->nParameters = 0;
  v1->nMaxParameters = 2;
  TypeWriterBox_ptParameterList = v1;
  ParameterList_AddParameter(v1, 0x30u, v2, "Width", 7u, nullptr);
  ParameterList_AddParameter(TypeWriterBox_ptParameterList, 0x34u, Level_eParameterTypeInt32, "Height", 7u, nullptr);
}

// source: j/0/menusystem/typewriterbox.c:809  [size]
void __cdecl TypeWriterBox_Close()
{
  int v0; // esi

  if ( TypeWriterBox_ptParameterList )
  {
    v0 = *(_DWORD *)((unsigned int)&TypeWriterBox_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
  QTask_DeleteQTaskType(TypeWriterBox_eQTaskType);
  TypeWriterBox_eQTaskType = 512;
}

// source: j/0/menusystem/typewriterbox.c:829  [size]
unsigned __int16 __cdecl TypeWriterBox_GetQTaskType()
{
  return TypeWriterBox_eQTaskType;
}
