/* j/0/screens/hintsscreen.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/screens/hintsscreen.c:63  [anchor-mhash]
void __cdecl HintsScreen_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ptQTask[1].ptNext = nullptr;
  ptQTask[1].ptPrev = nullptr;
  ptQTask[1].tQTaskChildren.ptHead = nullptr;
  ptQTask[1].tQTaskChildren.ptMiddle = nullptr;
  HintsScreen_ptQTask = ptQTask;
  ptQTask[1].tQTaskChildren.ptTail = nullptr;
}

// source: j/0/screens/hintsscreen.c:84  [anchor-mhash]
void __cdecl HintsScreen_DeleteHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptNext; // eax
  struct QTilemap_s ***p_ptPrev; // ebx
  int v3; // ebp
  struct QTilemap_s **v4; // esi
  int v5; // esi
  struct QTask_s *ptTail; // ebx

  ptNext = ptQTask[1].ptNext;
  if ( ptNext )
    Text_Delete((struct StaticTilemap_s *)ptNext);
  p_ptPrev = (struct QTilemap_s ***)&ptQTask[1].ptPrev;
  v3 = 3;
  do
  {
    v4 = *p_ptPrev;
    if ( *p_ptPrev )
    {
      QTilemap_Delete(*v4);
      v5 = *(_DWORD *)((unsigned int)(v4 - 1) & 0xFFFFFFFC);
      --Mem_nCurrentAllocations;
      Node_Remove((_DWORD **)v5);
      memset(*(void **)(v5 + 8), 0xCDu, *(_DWORD *)(v5 + 16));
      free((void *)v5);
    }
    ++p_ptPrev;
    --v3;
  }
  while ( v3 );
  ptTail = ptQTask[1].tQTaskChildren.ptTail;
  if ( ptTail )
    FontManager_DeleteFont((struct QSprite_s *)ptTail);
  HintsScreen_ptQTask = nullptr;
}

// source: j/0/screens/hintsscreen.c:118  [size]
void __cdecl HintsScreen_RunHandler(struct QTask_s *ptQTask)
{
  ;
}

// source: j/0/screens/hintsscreen.c:133  [anchor-mhash]
void __cdecl HintsScreen_DrawHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptNext; // eax
  struct QTask_s **p_ptPrev; // esi
  int v3; // edi
  struct QTask_s *v4; // eax

  ptNext = ptQTask[1].ptNext;
  if ( ptNext )
    QTilemap_Register(
      (struct QTilemap_s *)ptNext->ptNext,
      *(float *)&ptNext->ptPrev,
      *(float *)&ptNext->tQTaskChildren.ptHead,
      *(float *)&ptNext->tQTaskRefList.ptHead,
      *(float *)&ptNext->tQTaskRefList.ptMiddle,
      *(float *)&ptNext->tQTaskRefList.ptTail,
      *(float *)&ptNext->tQTaskChildren.ptTail,
      *(float *)&ptNext->tQTaskChildren.ptMiddle,
      *(_DWORD *)&ptNext->eQTaskType | 0x40000000,
      (int)ptNext->ptParent);
  p_ptPrev = &ptQTask[1].ptPrev;
  v3 = 3;
  do
  {
    if ( *p_ptPrev )
    {
      v4 = *p_ptPrev;
      QTilemap_Register(
        (struct QTilemap_s *)v4->ptNext,
        *(float *)&v4->ptPrev,
        *(float *)&v4->tQTaskChildren.ptHead,
        *(float *)&v4->tQTaskRefList.ptHead,
        *(float *)&v4->tQTaskRefList.ptMiddle,
        *(float *)&v4->tQTaskRefList.ptTail,
        *(float *)&v4->tQTaskChildren.ptTail,
        *(float *)&v4->tQTaskChildren.ptMiddle,
        *(_DWORD *)&v4->eQTaskType | 0x40000000,
        (int)v4->ptParent);
    }
    ++p_ptPrev;
    --v3;
  }
  while ( v3 );
}

// source: j/0/screens/hintsscreen.c:164  [size]
unsigned __int16 __cdecl HintsScreen_GetQTaskType()
{
  return HintsScreen_eQTaskType;
}

// source: j/0/screens/hintsscreen.c:177  [size]
enum bool __cdecl HintsScreen_GetSize(float *pvWidth, float *pvHeight)
{
  struct QTask_s *v2; // eax

  v2 = HintsScreen_ptQTask;
  if ( !HintsScreen_ptQTask )
    return false;
  *pvWidth = *(float *)&HintsScreen_ptQTask[1].tQTaskRefList.ptTail;
  *pvHeight = *(float *)&v2[1].ptParent;
  return true;
}

// source: j/0/screens/hintsscreen.c:198  [size]
enum bool __cdecl HintsScreen_GetPos(float *pvX, float *pvY)
{
  struct QTask_s *v2; // eax

  v2 = HintsScreen_ptQTask;
  if ( !HintsScreen_ptQTask )
    return false;
  *pvX = *(float *)&HintsScreen_ptQTask[1].tQTaskRefList.ptHead;
  *pvY = *(float *)&v2[1].tQTaskRefList.ptMiddle;
  return true;
}

// source: j/0/screens/hintsscreen.c:220  [anchor-callee]
void __cdecl HintsScreen_SetPos(float vX, float vY)
{
  struct QTask_s *v2; // eax
  double v3; // st7
  struct QTask_s *ptNext; // ecx
  struct QTask_s *ptPrev; // ecx
  struct QTask_s *ptHead; // ecx
  struct QTask_s *ptMiddle; // ecx
  int v8; // [esp+0h] [ebp-8h]

  v2 = HintsScreen_ptQTask;
  if ( HintsScreen_ptQTask )
  {
    v3 = vY;
    *(float *)&HintsScreen_ptQTask[1].tQTaskRefList.ptHead = vX;
    *(float *)&v2[1].tQTaskRefList.ptMiddle = vY;
    ptNext = v2[1].ptNext;
    if ( ptNext )
    {
      *(float *)&ptNext->ptPrev = (float)(__int64)vX;
      *(float *)&v2[1].ptNext->tQTaskChildren.ptHead = (float)(int)(__int64)v3;
      v8 = SHIWORD(v2[1].ptNext->ptNext->ptPrev)
         * *((__int16 *)&v2[1].ptNext->ptNext->tQTaskChildren.ptHead->tQTaskChildren.ptHead->tQTaskChildren.ptMiddle
           + 18 * LOWORD(v2[1].ptNext->ptNext->tQTaskChildren.ptHead->tQTaskRefList.ptHead)
           + 1);
      v3 = v3 + (double)v8 + (double)v8;
    }
    ptPrev = v2[1].ptPrev;
    if ( ptPrev )
    {
      *(float *)&ptPrev->ptPrev = (float)(__int64)vX;
      *(float *)&v2[1].ptPrev->tQTaskChildren.ptHead = (float)(int)(__int64)v3;
      v3 = v3
         + (double)(SHIWORD(v2[1].ptPrev->ptNext->ptPrev)
                  * *((__int16 *)&v2[1].ptPrev->ptNext->tQTaskChildren.ptHead->tQTaskChildren.ptHead->tQTaskChildren.ptMiddle
                    + 18 * LOWORD(v2[1].ptPrev->ptNext->tQTaskChildren.ptHead->tQTaskRefList.ptHead)
                    + 1));
    }
    ptHead = v2[1].tQTaskChildren.ptHead;
    if ( ptHead )
    {
      *(float *)&ptHead->ptPrev = (float)(__int64)vX;
      *(float *)&v2[1].tQTaskChildren.ptHead->tQTaskChildren.ptHead = (float)(int)(__int64)v3;
      v3 = v3
         + (double)(SHIWORD(v2[1].tQTaskChildren.ptHead->ptNext->ptPrev)
                  * *((__int16 *)&v2[1].tQTaskChildren.ptHead->ptNext->tQTaskChildren.ptHead->tQTaskChildren.ptHead->tQTaskChildren.ptMiddle
                    + 18 * LOWORD(v2[1].tQTaskChildren.ptHead->ptNext->tQTaskChildren.ptHead->tQTaskRefList.ptHead)
                    + 1));
    }
    ptMiddle = v2[1].tQTaskChildren.ptMiddle;
    if ( ptMiddle )
    {
      *(float *)&ptMiddle->ptPrev = (float)(__int64)vX;
      *(float *)&v2[1].tQTaskChildren.ptMiddle->tQTaskChildren.ptHead = (float)(int)(__int64)v3;
    }
  }
}

// source: j/0/screens/hintsscreen.c:261  [anchor-strings]
struct QTask_s *__cdecl HintsScreen_New(
        struct QTask_s *ptParent,
        float vX,
        float vY,
        int iMissionID,
        char *zFont)
{
  #pragma pack(push, 1)
  union
  {
    struct { int v28; };
    struct { int v29; };
    struct { int v30; };
    struct { int v31; };
    struct { char igi2_o4[4]; int vMaxWidth; };
    struct { char igi2_o5[4]; float vMaxWidtha; };
    struct { char igi2_o6[8]; struct QSprite_s *ptFont; };
    struct { char igi2_o7[16]; struct QTask_s *ptQTask; };
    struct { char igi2_o8[20]; char zTemp[1024]; };
    char igi2_extent[1044];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QSprite_s *Font; // ebx
  struct QTask_s *v6; // ebp
  struct StaticTilemap_s *v7; // eax
  struct QTilemap_s *ptQTilemap; // eax
  int nHeight; // ecx
  int v10; // edi
  __int16 *anGraphicWidth; // esi
  unsigned int v12; // eax
  _DWORD *p_ptPrev; // ebp
  unsigned int v14; // ebx
  char *LocalizedStringForLanguage; // eax
  struct StaticTilemap_s *v16; // eax
  struct QTilemap_s *v17; // ecx
  int v18; // edx
  int v19; // eax
  int v20; // edx
  double v21; // st7
  __int16 *v22; // edi
  int v23; // eax
  int v24; // edx
  __int16 *v25; // ecx
  int v26; // esi
  float vYa = *(float *)&vY; // [esp+42Ch] [ebp+Ch] ARGSLOT

  Font = FontManager_LoadFont(zFont);
  igi2_frame.ptFont = Font;
  if ( !Font )
    return nullptr;
  sprintf(igi2_frame.zTemp, "level%dtips/heading", iMissionID);
  if ( !Config_GetLocalizedStringForLanguage(
          igi2_frame.zTemp,
          Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eLanguage,
          false) )
  {
    FontManager_DeleteFont(Font);
    return nullptr;
  }
  v6 = QTask_NewFn(ptParent, HintsScreen_eQTaskType, nullptr);
  *(float *)&v6[1].tQTaskRefList.ptHead = vX;
  v6[1].tQTaskChildren.ptTail = (struct QTask_s *)Font;
  *(float *)&v6[1].tQTaskRefList.ptMiddle = vY;
  igi2_frame.ptQTask = v6;
  strcpy(
    igi2_frame.zTemp,
    Config_GetLocalizedStringForLanguage(
      igi2_frame.zTemp,
      Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eLanguage,
      true));
  strupr(igi2_frame.zTemp);
  v7 = Text_New(Font, vX, vY, igi2_frame.zTemp);
  v6[1].ptNext = (struct QTask_s *)v7;
  ptQTilemap = v7->ptQTilemap;
  nHeight = ptQTilemap->nHeight;
  v10 = 0;
  igi2_frame.vMaxWidth = 0;
  if ( nHeight > 0 )
  {
    anGraphicWidth = ptQTilemap->anGraphicWidth;
    do
    {
      if ( *anGraphicWidth > v10 )
        v10 = *anGraphicWidth;
      ++anGraphicWidth;
      --nHeight;
    }
    while ( nHeight );
    igi2_frame.vMaxWidth = v10;
  }
  igi2_frame.vMaxWidtha = (float)igi2_frame.vMaxWidth;
  igi2_frame.v28 = ptQTilemap->nHeight * ptQTilemap->ptQSprite->atQAnimframe[ptQTilemap->ptQSprite->nQAnimframes].nHeight;
  v12 = 0;
  p_ptPrev = &v6[1].ptPrev;
  vYa = (double)igi2_frame.v28 + (double)igi2_frame.v28 + vY;
  do
  {
    v14 = v12 + 1;
    sprintf(igi2_frame.zTemp, "level%dtips/tip%d", iMissionID, v12 + 1);
    LocalizedStringForLanguage = Config_GetLocalizedStringForLanguage(
                                   igi2_frame.zTemp,
                                   Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eLanguage,
                                   false);
    if ( LocalizedStringForLanguage )
    {
      sprintf(igi2_frame.zTemp, "- %s", LocalizedStringForLanguage);
      v16 = Text_New(igi2_frame.ptFont, vX, vYa, igi2_frame.zTemp);
      *p_ptPrev = v16;
      v17 = v16->ptQTilemap;
      v18 = v16->ptQTilemap->nHeight
          * v16->ptQTilemap->ptQSprite->atQAnimframe[v16->ptQTilemap->ptQSprite->nQAnimframes].nHeight;
      v19 = v16->ptQTilemap->nHeight;
      igi2_frame.v29 = v18;
      v20 = 0;
      v21 = (double)igi2_frame.v29;
      igi2_frame.v30 = 0;
      vYa = v21 + vYa;
      if ( v19 > 0 )
      {
        v22 = v17->anGraphicWidth;
        do
        {
          if ( *v22 > v20 )
            v20 = *v22;
          ++v22;
          --v19;
        }
        while ( v19 );
        igi2_frame.v30 = v20;
      }
      if ( (double)igi2_frame.v30 >= igi2_frame.vMaxWidtha )
      {
        v23 = v17->nHeight;
        v24 = 0;
        igi2_frame.v31 = 0;
        if ( v23 > 0 )
        {
          v25 = v17->anGraphicWidth;
          v26 = v23;
          do
          {
            if ( *v25 > v24 )
              v24 = *v25;
            ++v25;
            --v26;
          }
          while ( v26 );
          igi2_frame.v31 = v24;
        }
        igi2_frame.vMaxWidtha = (float)igi2_frame.v31;
      }
    }
    v12 = v14;
    ++p_ptPrev;
  }
  while ( v14 < 3 );
  *(float *)&igi2_frame.ptQTask[1].ptParent = vYa - vY;
  *(float *)&igi2_frame.ptQTask[1].tQTaskRefList.ptTail = igi2_frame.vMaxWidtha;
  return igi2_frame.ptQTask;
}

// source: j/0/screens/hintsscreen.c:334  [size]
struct QTask_s *__cdecl HintsScreen_GetQTask()
{
  return HintsScreen_ptQTask;
}

// source: j/0/screens/hintsscreen.c:347  [anchor-hash]
void __cdecl HintsScreen_Open()
{
  unsigned __int16 BaseQTaskType; // ax
  unsigned __int16 v1; // si

  BaseQTaskType = QTask_GetBaseQTaskType();
  v1 = QTask_NewQTaskType("HintsScreen", 76, BaseQTaskType, 0, 0);
  HintsScreen_eQTaskType = v1;
  QTask_LinkQTaskEventHandlerFn(v1, 0, HintsScreen_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 2, HintsScreen_DeleteHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 1, (void (__cdecl *)(struct QTask_s *))HintsScreen_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, Screen_eDrawQTaskEvent, HintsScreen_DrawHandler);
}

// source: j/0/screens/hintsscreen.c:367  [size]
void __cdecl HintsScreen_Close()
{
  QTask_DeleteQTaskType(HintsScreen_eQTaskType);
}
