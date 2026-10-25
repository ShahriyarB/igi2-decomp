/* j/0/menusystem/asciibox.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/menusystem/asciibox.c:95  [anchor-callee]
int __cdecl AsciiBox_FormatText(struct StaticTilemap_s *ptQText, struct QSprite_s *ptFont, char *zText, int nWidth)
{
  char *v4; // esi
  char v6; // al
  char v8; // al
  struct QTilemap_s *ptQTilemap; // edx
  char *v10; // ebp
  struct QTilemap_s *v11; // edi
  unsigned __int8 v12; // dl
  unsigned __int8 *anID; // eax
  char *v14; // ecx
  unsigned __int8 *v15; // ebx
  int nHeight; // ecx
  int v17; // edi
  __int16 *anGraphicWidth; // eax
  int v19; // eax
  char v20; // [esp+7h] [ebp-9h]
  int v21; // [esp+8h] [ebp-8h]
  char *v22; // [esp+Ch] [ebp-4h]

  v4 = zText;
  v21 = 0;
  v22 = zText;
  if ( !zText )
    return 0;
  if ( *zText )
  {
    while ( 1 )
    {
      if ( *v4 )
      {
        do
        {
          v6 = *v4;
          if ( *v4 == 32 )
            break;
          if ( v6 == 9 )
            break;
          if ( v6 == 10 )
            break;
        }
        while ( *++v4 );
      }
      v8 = *v4;
      *v4 = 0;
      ptQTilemap = ptQText->ptQTilemap;
      v20 = v8;
      memset(ptQText->ptQTilemap->anGraphicWidth, 0, 2 * ptQText->ptQTilemap->nHeight);
      v10 = v22;
      memset(ptQTilemap->anID, 0, ptQTilemap->nHeight * ptQTilemap->nWidth);
      v11 = ptQText->ptQTilemap;
      v12 = *v22;
      anID = ptQText->ptQTilemap->ptQSprite->ptQTilemap->anID;
      v14 = v22;
      v15 = ptQText->ptQTilemap->anID;
      if ( *v22 )
      {
        do
        {
          v14[v15 - (unsigned __int8 *)v22] = anID[v12];
          v12 = *++v14;
        }
        while ( v12 );
        v10 = v22;
      }
      QTilemap_UpdateGraphicWidth(v11, 0);
      *v4 = v20;
      nHeight = ptQText->ptQTilemap->nHeight;
      v17 = 0;
      if ( nHeight > 0 )
      {
        anGraphicWidth = ptQText->ptQTilemap->anGraphicWidth;
        do
        {
          if ( *anGraphicWidth > v17 )
            v17 = *anGraphicWidth;
          ++anGraphicWidth;
          --nHeight;
        }
        while ( nHeight );
      }
      if ( v17 > nWidth && zText != v10 )
      {
        *(zText - 1) = 0;
        v22 = zText;
        ++v21;
      }
      switch ( *v4 )
      {
        case 0:
          v19 = v21 + 1;
          goto LABEL_26;
        case 9:
        case 32:
          ++v4;
          goto LABEL_27;
        case 10:
          *v4 = 0;
          v19 = v21 + 1;
          v22 = ++v4;
LABEL_26:
          v21 = v19;
LABEL_27:
          zText = v4;
          break;
        default:
          break;
      }
      if ( !*zText )
        break;
      v4 = zText;
    }
  }
  return v21;
}

// source: j/0/menusystem/asciibox.c:182  [anchor-mhash]
void __cdecl AsciiBox_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  unsigned __int16 v2; // ax
  struct QTask_s *v3; // eax
  void *v4; // [esp-Ch] [ebp-18h]

  ((void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[0][MenuWindow_eQTaskType].pfHandler)(
    ptQTask,
    pxContext);
  ptQTask[1].tQTaskChildren.ptHead = (struct QTask_s *)100;
  ptQTask[1].tQTaskChildren.ptMiddle = (struct QTask_s *)100;
  ptQTask[1].tQTaskRefList.ptTail = (struct QReference_s *)1;
  ptQTask[1].ptParent = (struct QTask_s *)1;
  v4 = *(void **)&ptQTask[1].eQTaskType;
  v2 = SlideBar_eQTaskType;
  ptQTask[6].tQTaskChildren.ptHead = nullptr;
  ptQTask[5].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[5].tQTaskRefList.ptHead = nullptr;
  ptQTask[5].tQTaskRefList.ptTail = nullptr;
  LOBYTE(ptQTask[2].tQTaskChildren.ptMiddle) = 0;
  LOBYTE(ptQTask[3].eQTaskType) = 0;
  v3 = QTask_NewFn(nullptr, v2, v4);
  strcpy((char *)&v3[2].tQTaskChildren.ptMiddle, "slidevert");
  LOBYTE(v3[4].tQTaskRefList.ptTail) = 0;
  v3[4].tQTaskRefList.ptHead = (struct QReference_s *)50;
  v3[16].ptParent = (struct QTask_s *)3;
  ptQTask[6].tQTaskChildren.ptMiddle = v3;
}

// source: j/0/menusystem/asciibox.c:216  [anchor-mhash]
void __cdecl AsciiBox_DeleteHandler(struct QTask_s *ptQTask)
{
  struct QReference_s *ptMiddle; // eax
  struct QReference_s *ptTail; // eax
  int v3; // esi

  QTask_Delete(ptQTask[6].tQTaskChildren.ptMiddle);
  ptMiddle = ptQTask[5].tQTaskRefList.ptMiddle;
  if ( ptMiddle )
  {
    Text_Delete((struct StaticTilemap_s *)ptMiddle);
    ptQTask[5].tQTaskRefList.ptMiddle = nullptr;
  }
  ptTail = ptQTask[5].tQTaskRefList.ptTail;
  if ( ptTail )
  {
    v3 = *(_DWORD *)((unsigned int)&ptTail[-1].pxObject & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v3);
    memset(*(void **)(v3 + 8), 0xCDu, *(_DWORD *)(v3 + 16));
    free((void *)v3);
    ptQTask[5].tQTaskRefList.ptTail = nullptr;
  }
  ((void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[Level_eRemoveLevelScriptSymbolsEvent][ptQTask->eQTaskType].pfHandler)(ptQTask);
}

// source: j/0/menusystem/asciibox.c:252  [anchor-callee]
void __cdecl AsciiBox_ChangeLanguageHandler(struct QTask_s *ptQTask)
{
  struct QReference_s *ptTail; // eax
  int v2; // ebp
  bool v3; // zf
  struct File_s *v4; // eax
  struct File_s *v5; // edi
  unsigned int v6; // ebp
  struct QReference_s *v7; // eax
  struct QTask_s *ptHead; // ecx
  int v9; // edx
  struct QTask_s *v10; // eax
  int v11; // esi
  void (__cdecl *pfHandler)(struct QTask_s *); // eax
  int v13; // edx

  ptTail = ptQTask[5].tQTaskRefList.ptTail;
  if ( ptTail )
  {
    --Mem_nCurrentAllocations;
    v2 = *(_DWORD *)((unsigned int)&ptTail[-1].pxObject & 0xFFFFFFFC);
    Node_Remove((_DWORD **)v2);
    memset(*(void **)(v2 + 8), 0xCDu, *(_DWORD *)(v2 + 16));
    free((void *)v2);
    ptQTask[5].tQTaskRefList.ptTail = nullptr;
  }
  v3 = *(_DWORD *)&ptQTask[1].eQTaskType == 0;
  ptQTask[5].tQTaskRefList.ptTail = nullptr;
  *(_DWORD *)&ptQTask[5].eQTaskType = 0;
  if ( !v3 )
  {
    if ( ptQTask[5].tQTaskRefList.ptHead )
    {
      v4 = File_New((char *)&ptQTask[3].eQTaskType, "r");
      v5 = v4;
      if ( v4 )
      {
        v6 = File_atDevice[v4->eDeviceID].pfGetSize(v4->eDeviceID, v4);
        v7 = (struct QReference_s *)Mem_AllocFn(v6 + 2, 4);
        ptQTask[5].tQTaskRefList.ptTail = v7;
        File_atDevice[v5->eDeviceID].pfRead(v5->eDeviceID, v5, (char *)&v7->ptNext + 1, v6);
        File_Delete(v5);
        *((_BYTE *)&ptQTask[5].tQTaskRefList.ptTail->ptNext + v6 + 1) = 0;
        LOBYTE(ptQTask[5].tQTaskRefList.ptTail->ptNext) = 0;
        *(_DWORD *)&ptQTask[5].eQTaskType = AsciiBox_FormatText(
                                              (struct StaticTilemap_s *)ptQTask[5].tQTaskRefList.ptMiddle,
                                              (struct QSprite_s *)ptQTask[5].tQTaskRefList.ptHead,
                                              (char *)&ptQTask[5].tQTaskRefList.ptTail->ptNext + 1,
                                              (int)&ptQTask[1].tQTaskChildren.ptHead[-1].tQTaskChildren.ptMiddle);
      }
    }
  }
  ptHead = ptQTask->tQTaskChildren.ptHead;
  ptQTask[5].ptParent = (struct QTask_s *)((char *)&ptQTask[5].tQTaskRefList.ptTail->ptNext + 1);
  ptQTask[6].ptNext = nullptr;
  if ( ptHead->ptNext && ptHead )
  {
    v9 = QTask_nProtectedQTaskStackOffset;
    do
    {
      if ( ptHead->ptNext )
        v10 = ptHead->ptNext->ptNext != nullptr ? ptHead->ptNext : nullptr;
      else
        v10 = nullptr;
      v11 = MenuWindow_eChangeLanguageEvent;
      QTask_atProtectedQTaskStack[v9].ptQTask = v10;
      pfHandler = (void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[v11][ptHead->eQTaskType].pfHandler;
      v13 = v9 + 1;
      QTask_nProtectedQTaskStackOffset = v13;
      if ( pfHandler )
      {
        pfHandler(ptHead);
        v13 = QTask_nProtectedQTaskStackOffset;
      }
      ptHead = (struct QTask_s *)dword_849C7DC[v13];
      v9 = v13 - 1;
      QTask_nProtectedQTaskStackOffset = v9;
    }
    while ( ptHead );
  }
}

// source: j/0/menusystem/asciibox.c:327  [anchor-strings]
void __cdecl AsciiBox_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QReference_s *ptMiddle; // eax
  struct QTask_s *v3; // ebx
  struct QReference_s *Font; // eax
  struct QReference_s *v5; // eax

  ptMiddle = ptQTask[5].tQTaskRefList.ptMiddle;
  if ( ptMiddle )
  {
    Text_Delete((struct StaticTilemap_s *)ptMiddle);
    ptQTask[5].tQTaskRefList.ptMiddle = nullptr;
  }
  v3 = *(struct QTask_s **)&ptQTask[1].eQTaskType;
  if ( v3 )
  {
    Font = (struct QReference_s *)MenuManager_GetFont(v3, (char *)&ptQTask[2].tQTaskChildren.ptMiddle);
    ptQTask[5].tQTaskRefList.ptHead = Font;
    if ( Font )
    {
      v5 = (struct QReference_s *)Text_New((struct QSprite_s *)Font, 0.0, 0.0, (char *)&g_zInitialValue);
      ptQTask[5].tQTaskRefList.ptMiddle = v5;
      v5[2].pxObject = nullptr;
      Text_SetString((struct StaticTilemap_s *)ptQTask[5].tQTaskRefList.ptMiddle, (char *)&stru_68DAFC);
      ptQTask[6].ptPrev = (struct QTask_s *)(SHIWORD(ptQTask[5].tQTaskRefList.ptMiddle->ptNext->ptPrev)
                                           * *(__int16 *)(*((_DWORD *)ptQTask[5].tQTaskRefList.ptMiddle->ptNext->pxObject
                                                          + 2)
                                                        + 36
                                                        * *((unsigned __int16 *)ptQTask[5].tQTaskRefList.ptMiddle->ptNext->pxObject
                                                          + 10)
                                                        + 14)
                                           + 2);
    }
  }
  AsciiBox_ChangeLanguageHandler(ptQTask);
  ((void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[ParameterList_eUpdateInternalDataQTaskEvent][ptQTask[6].tQTaskChildren.ptMiddle->eQTaskType].pfHandler)(
    ptQTask[6].tQTaskChildren.ptMiddle,
    pxContext);
  ((void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[ParameterList_eUpdateInternalDataQTaskEvent][MenuWindow_eQTaskType].pfHandler)(
    ptQTask,
    pxContext);
}

// source: j/0/menusystem/asciibox.c:383  [anchor-mhash]
void __cdecl AsciiBox_RunHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptMiddle; // eax
  struct QTask_s *ptParent; // ecx
  int v3; // ecx
  bool v4; // cc
  struct QTask_s *v5; // eax
  struct QTask_s *v6; // edx
  struct QTask_s *v7; // eax
  struct QTask_s *v8; // edx

  if ( ptQTask[5].tQTaskRefList.ptTail )
  {
    ptMiddle = ptQTask[6].tQTaskChildren.ptMiddle;
    ptParent = ptMiddle[16].ptParent;
    if ( ptParent )
      v3 = (__int64)((double)(int)(&ptParent[-1].isInMemPool + 1) * *(double *)&ptMiddle[4].tQTaskChildren.ptHead + 0.5);
    else
      v3 = 0;
    v4 = v3 <= (int)ptQTask[6].ptNext;
    if ( v3 < (int)ptQTask[6].ptNext )
    {
      do
      {
        v5 = (struct QTask_s *)((char *)ptQTask[5].ptParent - 1);
        for ( ptQTask[5].ptParent = v5; *(&v5[-1].isInMemPool + 1); ptQTask[5].ptParent = v5 )
          v5 = (struct QTask_s *)((char *)v5 - 1);
        v6 = (struct QTask_s *)((char *)ptQTask[6].ptNext - 1);
        ptQTask[6].ptNext = v6;
      }
      while ( v3 < (int)v6 );
      v4 = v3 <= (int)v6;
    }
    if ( !v4 )
    {
      do
      {
        v7 = (struct QTask_s *)((char *)&ptQTask[5].ptParent->ptNext + 1);
        for ( ptQTask[5].ptParent = v7; *(&v7[-1].isInMemPool + 1); ptQTask[5].ptParent = v7 )
          v7 = (struct QTask_s *)((char *)v7 + 1);
        v8 = (struct QTask_s *)((char *)&ptQTask[6].ptNext->ptNext + 1);
        ptQTask[6].ptNext = v8;
      }
      while ( v3 > (int)v8 );
    }
  }
  ((void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[1][ptQTask[6].tQTaskChildren.ptMiddle->eQTaskType].pfHandler)(ptQTask[6].tQTaskChildren.ptMiddle);
  ((void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[1][MenuWindow_eQTaskType].pfHandler)(ptQTask);
}

// source: j/0/menusystem/asciibox.c:437  [anchor-mhash]
void __cdecl AsciiBox_DrawHandler(struct QTask_s *ptQTask)
{
  double v2; // st7
  struct QTask_s *ptMiddle; // ecx
  struct QTask_s *ptNext; // ebp
  struct QTask_s *ptHead; // ebx
  struct QTask_s *v6; // edx
  struct QTask_s *v7; // eax
  struct QTask_s *ptPrev; // esi
  struct QTask_s *v9; // ebp
  struct QTask_s *v10; // ebx
  int v11; // edx
  struct QTask_s *ptParent; // ebp
  signed int v13; // ecx
  double v14; // st7
  struct QReference_s *v15; // eax
  char v16; // al
  bool v17; // zf
  float vFade; // [esp+10h] [ebp-Ch]
  int nX; // [esp+14h] [ebp-8h]
  float v20; // [esp+18h] [ebp-4h]
  struct QTask_s *ptQTaska = *(struct QTask_s * *)&ptQTask; // [esp+20h] [ebp+4h] ARGSLOT

  v2 = (double)(*(_DWORD *)(*(_DWORD *)&ptQTask[1].eQTaskType + 356) - 8) * 0.125;
  if ( v2 <= 0.0 )
    vFade = 0.0;
  else
    vFade = v2;
  ptMiddle = ptQTask[6].tQTaskChildren.ptMiddle;
  ptNext = ptQTask[1].ptNext;
  ptHead = ptQTask[1].tQTaskChildren.ptHead;
  v6 = *(struct QTask_s **)&ptQTask[5].eQTaskType;
  v7 = ptQTask[1].tQTaskChildren.ptMiddle;
  ptMiddle[1].ptPrev = ptQTask[1].ptPrev;
  ptPrev = ptMiddle[4].ptPrev;
  ptMiddle[1].tQTaskChildren.ptMiddle = v7;
  ptMiddle[1].ptNext = (struct QTask_s *)((char *)ptNext + (_DWORD)ptHead - 19);
  v9 = ptPrev[1].tQTaskChildren.ptMiddle;
  v10 = ptMiddle[4].ptNext[1].tQTaskChildren.ptMiddle;
  ptMiddle[16].ptParent = v6;
  v11 = MenuWindow_eQTaskType;
  ptMiddle[4].tQTaskRefList.ptHead = (struct QReference_s *)((char *)v7 - (char *)v9 - (_DWORD)v10 - 6);
  ((void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[Screen_eDrawQTaskEvent][v11].pfHandler)(ptQTask);
  ((void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[Screen_eDrawQTaskEvent][ptQTask[6].tQTaskChildren.ptMiddle->eQTaskType].pfHandler)(ptQTask[6].tQTaskChildren.ptMiddle);
  if ( ptQTask[5].tQTaskRefList.ptHead && ptQTask[5].tQTaskRefList.ptTail )
  {
    ptParent = ptQTask[5].ptParent;
    v13 = *(_DWORD *)&ptQTask[5].eQTaskType - (unsigned int)ptQTask[6].ptNext;
    if ( (int)&ptQTask[1].tQTaskChildren.ptMiddle[-1].eQTaskType / (int)ptQTask[6].ptPrev < v13 )
      v13 = (int)&ptQTask[1].tQTaskChildren.ptMiddle[-1].eQTaskType / (int)ptQTask[6].ptPrev;
    ptQTaska = (struct QTask_s *)((char *)ptQTask[1].ptPrev + (Display_tActiveMode.nHeight >> 1) - 236);
    if ( v13 > 0 )
    {
      v14 = (double)((unsigned int)&ptQTask[1].ptNext[-7] + (Display_tActiveMode.nWidth >> 1) - 36);
      nX = v13;
      do
      {
        Text_SetString((struct StaticTilemap_s *)ptQTask[5].tQTaskRefList.ptMiddle, (char *)ptParent);
        v20 = v14;
        *(float *)&ptQTask[5].tQTaskRefList.ptMiddle->ptPrev = v20;
        *(float *)&ptQTask[5].tQTaskRefList.ptMiddle->pxObject = (float)(int)ptQTaska;
        ptQTask[5].tQTaskRefList.ptMiddle[1].pxObject = (void *)1124073472;
        ptQTask[5].tQTaskRefList.ptMiddle[2].ptNext = (struct QReference_s *)1124073472;
        ptQTask[5].tQTaskRefList.ptMiddle[2].ptPrev = (struct QReference_s *)1124073472;
        ptQTask[5].tQTaskRefList.ptMiddle[3].ptNext = (struct QReference_s *)((int)ptQTask[5].tQTaskRefList.ptMiddle[3].ptNext
                                                                            | 0x80000);
        *(float *)&ptQTask[5].tQTaskRefList.ptMiddle[1].ptPrev = vFade;
        v15 = ptQTask[5].tQTaskRefList.ptMiddle;
        QTilemap_Register(
          (struct QTilemap_s *)v15->ptNext,
          *(float *)&v15->ptPrev,
          *(float *)&v15->pxObject,
          *(float *)&v15[1].pxObject,
          *(float *)&v15[2].ptNext,
          *(float *)&v15[2].ptPrev,
          *(float *)&v15[1].ptPrev,
          *(float *)&v15[1].ptNext,
          (int)v15[3].ptNext | 0x40000000,
          (int)v15[2].pxObject);
        if ( LOBYTE(ptParent->ptNext) )
        {
          do
          {
            v16 = BYTE1(ptParent->ptNext);
            ptParent = (struct QTask_s *)((char *)ptParent + 1);
          }
          while ( v16 );
        }
        ptParent = (struct QTask_s *)((char *)ptParent + 1);
        v17 = nX == 1;
        ptQTaska = (struct QTask_s *)((char *)ptQTaska + (unsigned int)ptQTask[6].ptPrev);
        --nX;
      }
      while ( !v17 );
    }
  }
  ptQTask[1].tQTaskChildren.ptHead = (struct QTask_s *)((char *)ptQTask[1].tQTaskChildren.ptHead - 20);
  MenuWindow_DrawBorder((struct MenuWindow_t *)ptQTask, 0.5, vFade, 0);
  ptQTask[1].tQTaskChildren.ptHead = (struct QTask_s *)((char *)ptQTask[1].tQTaskChildren.ptHead + 20);
}

// source: j/0/menusystem/asciibox.c:522  [size]
void __cdecl AsciiBox_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = AsciiBox_ptParameterList;
}

// source: j/0/menusystem/asciibox.c:538  [size]
void __cdecl AsciiBox_InitDataHandler(struct QTask_s *ptQTask)
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
}

// source: j/0/menusystem/asciibox.c:552  [size]
void __cdecl AsciiBox_ChangeDataHandler(struct QTask_s *ptQTask)
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

// source: j/0/menusystem/asciibox.c:570  [size]
void __cdecl AsciiBox_RegisterScriptSymbolsHandler(struct QTask_s *ptQTask)
{
  if ( !ptQTask[6].tQTaskChildren.ptHead )
    ptQTask[6].tQTaskChildren.ptHead = (struct QTask_s *)1;
}

// source: j/0/menusystem/asciibox.c:602  [size]
void __cdecl AsciiBox_RemoveScriptSymbolsHandler(struct QTask_s *ptQTask)
{
  if ( ptQTask[6].tQTaskChildren.ptHead )
    ptQTask[6].tQTaskChildren.ptHead = nullptr;
}

// source: j/0/menusystem/asciibox.c:638  [anchor-hash]
void __cdecl AsciiBox_Open()
{
  unsigned __int16 v0; // si
  struct ParameterList_s *v1; // eax
  int v2; // edx

  v0 = QTask_NewQTaskType("AsciiBox", 256, MenuWindow_eQTaskType, 0, 0);
  AsciiBox_eQTaskType = v0;
  QTask_LinkQTaskEventHandlerFn(
    v0,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 1, AsciiBox_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, Screen_eDrawQTaskEvent, AsciiBox_DrawHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 2, AsciiBox_DeleteHandler);
  QTask_LinkQTaskEventHandlerFn(v0, 0, AsciiBox_CreateHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))AsciiBox_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(v0, ParameterList_eUpdateInternalDataQTaskEvent, AsciiBox_UpdateInternalDataHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, MenuWindow_eInitDataEvent, AsciiBox_InitDataHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, MenuWindow_eChangeDataEvent, AsciiBox_ChangeDataHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(
    v0,
    Level_eRegisterLevelScriptSymbolsEvent,
    (void (__cdecl *)(struct QTask_s *))AsciiBox_RegisterScriptSymbolsHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(
    v0,
    Level_eRemoveLevelScriptSymbolsEvent,
    (void (__cdecl *)(struct QTask_s *))AsciiBox_RemoveScriptSymbolsHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, MenuWindow_eChangeLanguageEvent, AsciiBox_ChangeLanguageHandler);
  v1 = (struct ParameterList_s *)Mem_AllocFn(92, 4);
  v2 = Level_eParameterTypeString32;
  v1->ptParameterListItem = (struct ParameterListItem_s *)&v1[1];
  v1->nParameters = 0;
  v1->nMaxParameters = 4;
  AsciiBox_ptParameterList = v1;
  ParameterList_AddParameter(v1, 0x5Cu, v2, "Font Resource", 7u, nullptr);
  ParameterList_AddParameter(AsciiBox_ptParameterList, 0x9Cu, Level_eParameterTypeString32, "Text File", 7u, nullptr);
  ParameterList_AddParameter(AsciiBox_ptParameterList, 0x30u, Level_eParameterTypeInt32, "Width", 7u, nullptr);
  ParameterList_AddParameter(AsciiBox_ptParameterList, 0x34u, Level_eParameterTypeInt32, "Height", 7u, nullptr);
}

// source: j/0/menusystem/asciibox.c:679  [size]
void __cdecl AsciiBox_Close()
{
  int v0; // esi

  if ( AsciiBox_ptParameterList )
  {
    v0 = *(_DWORD *)((unsigned int)&AsciiBox_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
  QTask_DeleteQTaskType(AsciiBox_eQTaskType);
  AsciiBox_eQTaskType = 512;
}
