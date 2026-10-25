/* j/0/screens/statusscreen/statusmessagescreen.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/screens/statusscreen/statusmessagescreen.c:80  [size]
struct StatusMessage_s *__cdecl StatusMessageScreen_GetStatusMessage(
        struct StatusMessageScreen_s *ptStatusMessageScreen,
        int iMessage)
{
  return (struct StatusMessage_s *)ptStatusMessageScreen->atRegisteredMessage[iMessage].ptQTaskRef->pxObject;
}

// source: j/0/screens/statusscreen/statusmessagescreen.c:95  [anchor-strings]
struct QSprite_s *__cdecl StatusMessageScreen_GetFont(
        struct StatusMessageScreen_s *ptStatusMessageScreen,
        int iMessage)
{
  _BYTE *pxObject; // eax
  struct QTask_s *ptHead; // eax
  struct QTask_s *v5; // eax

  pxObject = ptStatusMessageScreen->atRegisteredMessage[iMessage].ptQTaskRef->pxObject;
  if ( !pxObject )
    return nullptr;
  if ( pxObject[710] )
  {
    ptHead = Game_ptGame->ptGameScreenQTask[1].tQTaskChildren.ptHead;
    if ( ptHead )
      return MenuManager_GetFont(ptHead->tQTaskChildren.ptHead, (char *)&g_zFontName_0.tQTaskChildren.ptMiddle);
    else
      return MenuManager_GetFont(nullptr, (char *)&g_zFontName_0.tQTaskChildren.ptMiddle);
  }
  else
  {
    v5 = Game_ptGame->ptGameScreenQTask[1].tQTaskChildren.ptHead;
    if ( v5 )
      return MenuManager_GetFont(v5->tQTaskChildren.ptHead, (char *)&g_zFontName_0);
    else
      return MenuManager_GetFont(nullptr, (char *)&g_zFontName_0);
  }
}

// source: j/0/screens/statusscreen/statusmessagescreen.c:125  [anchor-mhash]
struct Result_s *__cdecl StatusMessageScreen_ClearMessagesCB(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  struct StatusMessageScreen_s *ptTail; // ebx
  int v4; // esi
  char *p_isUsed; // edi
  struct Result_s Rs; // [esp+Ch] [ebp-18h] BYREF

  ptTail = (struct StatusMessageScreen_s *)StatusScreen_ptStatusScreenQTask[52].tQTaskChildren.ptTail;
  v4 = 0;
  p_isUsed = &ptTail->atRegisteredMessage[0].isUsed;
  do
  {
    if ( *p_isUsed )
      StatusMessageScreen_RemoveMessage(ptTail, v4);
    ++v4;
    p_isUsed += 4148;
  }
  while ( v4 < 24 );
  Rs.nResult = 1;
  Rs.vResult = 1.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/screens/statusscreen/statusmessagescreen.c:144  [anchor-caller]
void __cdecl StatusMessageScreen_FormatMessageText(
        struct StatusMessageScreen_s *ptStatusMessageScreen,
        int iMessage,
        float vTextWidth)
{
  #pragma pack(push, 1)
  union
  {
    struct { char zCurrentToken; };
    struct { char igi2_o1[1]; int v32; };
    struct { char igi2_o2[1]; char *v33; };
    struct { char igi2_o3[1]; struct QTilemap_s ***v34; };
    struct { char igi2_o4[5]; int nLine; };
    struct { char igi2_o5[9]; char *pzStart; };
    struct { char igi2_o6[17]; struct StatusMessageScreenRegisteredMessage_s *ptRegisteredMessage; };
    struct { char igi2_o7[21]; struct QSprite_s *ptQSprite; };
    struct { char igi2_o8[25]; struct StaticTilemap_s **v39; };
    struct { char igi2_o9[29]; char *pzPos; };
    struct { char igi2_o10[33]; char zLineBuffer[10][1024]; };
    char igi2_extent[10273];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct StatusMessageScreenRegisteredMessage_s *v5; // esi
  char *zCurrentTextPos; // eax
  struct QTilemap_s ***aptText; // ebp
  struct QTilemap_s **v8; // ebx
  struct QTilemap_s *v9; // edx
  char *zText; // ebp
  char *v11; // esi
  char *v12; // edi
  int v13; // ebx
  char v14; // bl
  BOOL v15; // eax
  char v16; // bl
  int v18; // eax
  char *v19; // ebp
  struct QTilemap_s **v20; // esi
  struct QTilemap_s *v21; // edx
  char *anID; // edi
  unsigned int v23; // edx
  char *v24; // edi
  char v25; // cl
  unsigned __int8 v26; // dl
  struct QTilemap_s *v27; // esi
  int v28; // eax
  char *i; // ecx
  bool v30; // zf

  igi2_frame.ptQSprite = StatusMessageScreen_GetFont(ptStatusMessageScreen, iMessage);
  v5 = &ptStatusMessageScreen->atRegisteredMessage[iMessage];
  igi2_frame.nLine = 0;
  zCurrentTextPos = v5->zCurrentTextPos;
  igi2_frame.zCurrentToken = *zCurrentTextPos;
  aptText = (struct QTilemap_s ***)v5->aptText;
  igi2_frame.ptRegisteredMessage = v5;
  igi2_frame.pzPos = v5->zText;
  *zCurrentTextPos = 0;
  igi2_frame.v39 = v5->aptText;
  igi2_frame.v32 = 3;
  do
  {
    v8 = *aptText;
    v9 = **aptText;
    memset(v9->anGraphicWidth, 0, 2 * v9->nHeight);
    memset(v9->anID, 0, v9->nHeight * v9->nWidth);
    QTilemap_UpdateGraphicWidth(*v8, 0);
    ++aptText;
    --igi2_frame.v32;
  }
  while ( igi2_frame.v32 );
  zText = v5->zText;
  v11 = v5->zText;
  if ( *igi2_frame.pzPos )
  {
    v12 = nullptr;
    igi2_frame.v33 = igi2_frame.zLineBuffer[0];
    while ( 1 )
    {
      v13 = igi2_frame.nLine;
      if ( igi2_frame.nLine >= 9 )
        break;
      v14 = *zText;
      *zText = 0;
      v15 = (double)Font_GetStringWidth(igi2_frame.ptQSprite, v11) >= vTextWidth || v14 == 10;
      *zText = v14;
      if ( v15 )
      {
        if ( !v12 )
          v12 = zText - 1;
        v16 = *v12;
        *v12 = 0;
        strcpy(igi2_frame.v33, v11);
        *v12 = v16;
        v11 = v12 + 1;
        ++igi2_frame.nLine;
        igi2_frame.v33 += 1024;
      }
      if ( *zText == 32 )
        v12 = zText;
      if ( !*++zText )
        goto LABEL_17;
    }
  }
  else
  {
LABEL_17:
    v13 = igi2_frame.nLine;
  }
  if ( zText != v11 )
  {
    strcpy(igi2_frame.zLineBuffer[v13++], v11);
    igi2_frame.nLine = v13;
  }
  if ( v13 <= 3 )
    v18 = 0;
  else
    v18 = v13 - 3;
  if ( v18 < v13 )
  {
    igi2_frame.v34 = (struct QTilemap_s ***)igi2_frame.v39;
    v19 = igi2_frame.zLineBuffer[v18];
    igi2_frame.pzStart = (char *)(igi2_frame.nLine - v18);
    do
    {
      v20 = *igi2_frame.v34;
      v21 = **igi2_frame.v34;
      memset(v21->anGraphicWidth, 0, 2 * v21->nHeight);
      anID = (char *)v21->anID;
      v23 = v21->nHeight * v21->nWidth;
      memset(anID, 0, 4 * (v23 >> 2));
      v24 = &anID[4 * (v23 >> 2)];
      v25 = v23;
      v26 = *v19;
      memset(v24, 0, v25 & 3);
      v27 = *v20;
      v28 = (int)v27->ptQSprite->ptQTilemap->anID;
      for ( i = v19; v26; ++i )
      {
        i[v27->anID - (unsigned __int8 *)v19] = *(_BYTE *)(v26 + v28);
        v26 = i[1];
      }
      QTilemap_UpdateGraphicWidth(v27, 0);
      v19 += 1024;
      v30 = igi2_frame.pzStart == (char *)1;
      ++igi2_frame.v34;
      --igi2_frame.pzStart;
    }
    while ( !v30 );
  }
  *igi2_frame.ptRegisteredMessage->zCurrentTextPos = igi2_frame.zCurrentToken;
}

// source: j/0/screens/statusscreen/statusmessagescreen.c:250  [anchor-mhash]
int __cdecl StatusMessageScreen_DrawBox(
        struct StatusMessageScreen_s *ptStatusMessageScreen,
        int iMessage,
        float vX,
        float vY,
        int nDepth)
{
  #pragma pack(push, 1)
  union
  {
    struct { float vA; };
    struct { char igi2_o1[28]; float vCenterX; };
    struct { char igi2_o2[32]; float vY1; };
    struct { char igi2_o3[32]; float vY1a; };
    struct { char igi2_o4[36]; float v18; };
    struct { char igi2_o5[40]; float vScaleX; };
    struct { char igi2_o6[44]; float vScaleY; };
    struct { char igi2_o7[48]; struct real32x2_t atMesh[5]; };
    char igi2_extent[88];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v5; // eax
  float vBoxSizeScaleX; // edx
  char *v7; // ecx
  double v8; // st7
  double v9; // st6
  double v10; // st7
  double v11; // st6
  double v12; // st5
  float ptStatusMessageScreena = *(float *)&vX; // [esp+5Ch] [ebp+4h] ARGSLOT
  float iMessagea = *(float *)&vY; // [esp+60h] [ebp+8h] ARGSLOT
  struct real32x2_t struct_real32x2_t; // 0:^6C.8

  v5 = iMessage;
  vBoxSizeScaleX = ptStatusMessageScreen->atRegisteredMessage[v5].vBoxSizeScaleX;
  v7 = (char *)ptStatusMessageScreen + v5 * 4148;
  v8 = (double)((9 - *((_DWORD *)v7 + 11)) / 9);
  if ( v8 <= 0.0 )
    igi2_frame.v18 = 0.0;
  else
    igi2_frame.v18 = v8;
  v9 = *((float *)v7 + 22) * 0.5;
  igi2_frame.vY1 = v9;
  igi2_frame.vCenterX = v9 + vX;
  v10 = *((float *)v7 + 21) * 0.5;
  v11 = vY + v10;
  v12 = igi2_frame.vY1 * vBoxSizeScaleX;
  ptStatusMessageScreena = igi2_frame.vCenterX - v12;
  igi2_frame.vY1a = v10 * *((float *)v7 + 20);
  iMessagea = v11 - igi2_frame.vY1a;
  struct_real32x2_t.vX = v12 + igi2_frame.vCenterX;
  struct_real32x2_t.vY = igi2_frame.vY1a + v11;
  igi2_frame.vScaleY = struct_real32x2_t.vY - iMessagea;
  igi2_frame.vScaleX = struct_real32x2_t.vX - ptStatusMessageScreena;
  QSprite_RegisterBlankAZ(
    ptStatusMessageScreena,
    iMessagea,
    igi2_frame.vScaleX,
    igi2_frame.vScaleY,
    0.0,
    0.0,
    0.0,
    0.33000001311302185,
    1.0,
    0x80000u,
    nDepth);
  igi2_frame.vA = igi2_frame.v18 * 0.6000000238418579 + 0.15000000596046448;
  QSprite_RegisterBlankAZ(
    ptStatusMessageScreena,
    iMessagea,
    igi2_frame.vScaleX,
    igi2_frame.vScaleY,
    51.20000076293945,
    51.20000076293945,
    51.20000076293945,
    igi2_frame.vA,
    1.0,
    0x80000u,
    nDepth);
  igi2_frame.atMesh[0].vX = ptStatusMessageScreena;
  igi2_frame.atMesh[0].vY = iMessagea;
  igi2_frame.atMesh[1].vX = struct_real32x2_t.vX;
  igi2_frame.atMesh[1].vY = iMessagea;
  igi2_frame.atMesh[2] = struct_real32x2_t;
  igi2_frame.atMesh[3].vX = ptStatusMessageScreena;
  igi2_frame.atMesh[3].vY = struct_real32x2_t.vY;
  igi2_frame.atMesh[4].vY = iMessagea;
  igi2_frame.atMesh[4].vX = ptStatusMessageScreena;
  return QSprite_RegisterLineMesh(
           igi2_frame.atMesh,
           5,
           0.0,
           0.0,
           1.0,
           65.27999877929688,
           80.63999938964844,
           125.44000244140625,
           1.0,
           1.0,
           0.0,
           1.0,
           1.0,
           0,
           nDepth);
}

// source: j/0/screens/statusscreen/statusmessagescreen.c:356  [anchor-mhash]
void __cdecl StatusMessageScreen_DrawMessage(
        struct StatusMessageScreen_s *ptStatusMessageScreen,
        int iMessage,
        float vX,
        float vY)
{
  char *v4; // esi
  struct QSprite_s *v5; // ecx
  int v6; // eax
  struct QTilemap_s ***v7; // esi
  int v8; // edi
  int v9; // [esp+Ch] [ebp-10h]
  float vWindowX; // [esp+18h] [ebp-4h]
  float vXa = *(float *)&vX; // [esp+28h] [ebp+Ch] ARGSLOT
  float vYa = *(float *)&vY; // [esp+2Ch] [ebp+10h] ARGSLOT

  vWindowX = vX;
  v4 = (char *)ptStatusMessageScreen + 4148 * iMessage;
  v5 = *((struct QSprite_s **)v4 + 17);
  if ( v5 && *((int *)v4 + 11) > 9 )
    QSprite_Register(v5, vX, vY, 128.0, 128.0, 128.0, 0, 0, 0);
  v6 = *((_DWORD *)v4 + 17);
  if ( v6 )
    vX = (double)*(__int16 *)(*(_DWORD *)(v6 + 8) + 36 * *(unsigned __int16 *)(v6 + 20) + 12) + vX;
  v7 = (struct QTilemap_s ***)(v4 + 56);
  v8 = 3;
  vYa = vY + 2.0;
  vXa = (float)(int)(__int64)(vX + 3.0);
  do
  {
    (*v7)[5] = (struct QTilemap_s *)1112329421;
    (*v7)[6] = (struct QTilemap_s *)1117362586;
    (*v7)[7] = (struct QTilemap_s *)1124073472;
    *((float *)*v7 + 1) = vXa;
    *((float *)*v7 + 2) = (float)(__int64)vYa;
    QTilemap_Register(
      **v7,
      *((float *)*v7 + 1),
      *((float *)*v7 + 2),
      *((float *)*v7 + 5),
      *((float *)*v7 + 6),
      *((float *)*v7 + 7),
      *((float *)*v7 + 4),
      *((float *)*v7 + 3),
      (unsigned int)(*v7)[9] | 0x40000000,
      (int)(*v7)[8]);
    v9 = (**v7)->nHeight * (**v7)->ptQSprite->atQAnimframe[(**v7)->ptQSprite->nQAnimframes].nHeight;
    ++v7;
    --v8;
    vYa = (double)v9 + vYa;
  }
  while ( v8 );
  StatusMessageScreen_DrawBox(ptStatusMessageScreen, iMessage, vWindowX, vY, 0);
}

// source: j/0/screens/statusscreen/statusmessagescreen.c:417  [anchor-mhash]
int __cdecl StatusMessageScreen_DrawCutSceneMessage(
        struct StatusMessageScreen_s *ptStatusMessageScreen,
        int iMessage,
        float vX,
        float vY)
{
  struct QTilemap_s ***aptText; // esi
  int v5; // edi
  struct QTilemap_s *v6; // eax
  struct QSprite_s *ptQSprite; // ecx
  int result; // eax
  float v9; // [esp+0h] [ebp-Ch]

  aptText = (struct QTilemap_s ***)ptStatusMessageScreen->atRegisteredMessage[iMessage].aptText;
  v5 = 3;
  do
  {
    v9 = (float)(__int64)vX;
    *((float *)*aptText + 1) = v9;
    *((float *)*aptText + 2) = (float)(__int64)vY;
    QTilemap_Register(
      **aptText,
      *((float *)*aptText + 1),
      *((float *)*aptText + 2),
      *((float *)*aptText + 5),
      *((float *)*aptText + 6),
      *((float *)*aptText + 7),
      *((float *)*aptText + 4),
      *((float *)*aptText + 3),
      (unsigned int)(*aptText)[9] | 0x40000000,
      (int)(*aptText)[8]);
    v6 = **aptText;
    ptQSprite = v6->ptQSprite;
    result = v6->nHeight;
    ++aptText;
    --v5;
    vY = (double)(result * ptQSprite->atQAnimframe[ptQSprite->nQAnimframes].nHeight) + vY;
  }
  while ( v5 );
  return result;
}

// source: j/0/screens/statusscreen/statusmessagescreen.c:440  [anchor-caller]
void __cdecl StatusMessageScreen_UpdateMessage(
        struct StatusMessageScreen_s *ptStatusMessageScreen,
        int iMessage)
{
  char *v2; // esi
  int v3; // ebx
  int v4; // edi
  _BYTE *v5; // eax
  bool v6; // zf
  signed int v7; // edi
  double v8; // st7
  float v9; // [esp+0h] [ebp-10h]
  float v10; // [esp+0h] [ebp-10h]

  v2 = (char *)ptStatusMessageScreen + 4148 * iMessage;
  v3 = *(_DWORD *)(*((_DWORD *)v2 + 10) + 8);
  if ( !v3 )
    return;
  if ( *(_BYTE *)(v3 + 710) )
  {
    if ( !*((_DWORD *)v2 + 12) )
    {
      v10 = (double)Display_tActiveMode.nWidth * 0.96875;
      StatusMessageScreen_FormatMessageText(ptStatusMessageScreen, iMessage, v10);
    }
LABEL_14:
    ++*((_DWORD *)v2 + 12);
    goto LABEL_15;
  }
  v4 = *((_DWORD *)v2 + 11);
  if ( v4 >= 9 )
  {
    v5 = *((_BYTE **)v2 + 13);
    if ( *v5 )
    {
      v7 = (v4 - 9) & 0x80000001;
      v6 = v7 == 0;
      if ( v7 < 0 )
        v6 = (((_BYTE)v7 - 1) | 0xFFFFFFFE) == -1;
      if ( v6 )
      {
        v8 = *((float *)v2 + 22) - 6.0;
        *((_DWORD *)v2 + 13) = v5 + 1;
        v9 = v8;
        StatusMessageScreen_FormatMessageText(ptStatusMessageScreen, iMessage, v9);
      }
      goto LABEL_15;
    }
    goto LABEL_14;
  }
  if ( v4 >= 2 )
    *((float *)v2 + 19) = *((float *)v2 + 19) + 0.1428571492433548;
  else
    *((float *)v2 + 20) = *((float *)v2 + 20) + 0.5;
LABEL_15:
  if ( *((int *)v2 + 12) > 30 )
    *(_BYTE *)(v3 + 988) = 1;
  ++*((_DWORD *)v2 + 11);
}

// source: j/0/screens/statusscreen/statusmessagescreen.c:509  [anchor-mhash]
void __cdecl StatusMessageScreen_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s **p_ptParent; // eax
  int v3; // ecx

  p_ptParent = &ptQTask[1].ptParent;
  v3 = 24;
  do
  {
    *(_BYTE *)p_ptParent = 0;
    p_ptParent += 1037;
    --v3;
  }
  while ( v3 );
  ComputerLog_ClearLog();
}

// source: j/0/screens/statusscreen/statusmessagescreen.c:535  [anchor-caller]
void __cdecl StatusMessageScreen_RunHandler(struct QTask_s *ptQTask)
{
  int v1; // esi
  struct QTask_s **p_ptParent; // edi

  if ( !Game_ptGame || !LOBYTE(Game_ptGame->pxSpritesResource) )
  {
    v1 = 0;
    p_ptParent = &ptQTask[1].ptParent;
    do
    {
      if ( *(_BYTE *)p_ptParent )
        StatusMessageScreen_UpdateMessage((struct StatusMessageScreen_s *)ptQTask, v1);
      ++v1;
      p_ptParent += 1037;
    }
    while ( v1 < 24 );
  }
}

// source: j/0/screens/statusscreen/statusmessagescreen.c:565  [anchor-mhash]
void __cdecl StatusMessageScreen_DeleteHandler(struct QTask_s *ptQTask)
{
  int v1; // esi
  struct QTask_s **p_ptParent; // edi

  v1 = 0;
  p_ptParent = &ptQTask[1].ptParent;
  do
  {
    if ( *(_BYTE *)p_ptParent )
      StatusMessageScreen_RemoveMessage((struct StatusMessageScreen_s *)ptQTask, v1);
    ++v1;
    p_ptParent += 1037;
  }
  while ( v1 < 24 );
}

// source: j/0/screens/statusscreen/statusmessagescreen.c:581  [anchor-mhash]
void __cdecl StatusMessageScreen_DrawHandler(struct QTask_s *ptQTask)
{
  struct StatusMessageScreen_s *v1; // ebp
  struct QTask_s *v2; // ebx
  int v3; // esi
  struct QTask_s *v4; // edi
  struct QTask_s *ptHead; // eax
  float ptStatusMessageScreen; // [esp+0h] [ebp-24h]
  float iMessage; // [esp+4h] [ebp-20h]
  float vY; // [esp+18h] [ebp-Ch]
  int nHeight; // [esp+1Ch] [ebp-8h]
  int nWidth; // [esp+20h] [ebp-4h]

  nWidth = Display_tActiveMode.nWidth;
  nHeight = Display_tActiveMode.nHeight;
  v1 = (struct StatusMessageScreen_s *)ptQTask;
  v2 = nullptr;
  v3 = 0;
  vY = (double)(3
              * SHIWORD(StatusScreen_ptStatusScreenQTask[27].ptParent->ptNext->ptPrev)
              * *((__int16 *)&StatusScreen_ptStatusScreenQTask[27].ptParent->ptNext->tQTaskChildren.ptHead->tQTaskChildren.ptHead->tQTaskChildren.ptMiddle
                + 18
                * LOWORD(StatusScreen_ptStatusScreenQTask[27].ptParent->ptNext->tQTaskChildren.ptHead->tQTaskRefList.ptHead)
                + 1))
     + 76.0;
  v4 = ptQTask + 1;
  do
  {
    if ( LOBYTE(v4->ptParent) )
    {
      ptHead = v4->ptNext->tQTaskChildren.ptHead;
      if ( BYTE2(ptHead[17].tQTaskRefList.ptTail) )
      {
        if ( !v2 || (int)(*(_DWORD *)&v2[24].eQTaskType) < (int)(*(_DWORD *)&ptHead[24].eQTaskType) )
        {
          v2 = v4->ptNext->tQTaskChildren.ptHead;
          ptQTask = (struct QTask_s *)v3;
        }
      }
      else
      {
        StatusMessageScreen_DrawMessage(v1, v3, 5.0, vY);
      }
      vY = vY + *(float *)&v4[1].ptPrev + 5.0;
    }
    ++v3;
    v4 = (struct QTask_s *)((char *)v4 + 4148);
  }
  while ( v3 < 24 );
  if ( v2 )
  {
    iMessage = (double)nHeight * 0.8645833134651184;
    ptStatusMessageScreen = (double)nWidth * 0.015625;
    StatusMessageScreen_DrawCutSceneMessage(v1, (int)ptQTask, ptStatusMessageScreen, iMessage);
  }
}

// source: j/0/screens/statusscreen/statusmessagescreen.c:663  [anchor-hash]
void __cdecl StatusMessageScreen_Open()
{
  unsigned __int16 BaseQTaskType; // ax
  unsigned __int16 v1; // si

  BaseQTaskType = QTask_GetBaseQTaskType();
  v1 = QTask_NewQTaskType("StatusMessageScreen", 99592, BaseQTaskType, 0, 0);
  StatusMessageScreen_eQTaskType = v1;
  QTask_LinkQTaskEventHandlerFn(v1, 0, StatusMessageScreen_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 1, StatusMessageScreen_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 2, StatusMessageScreen_DeleteHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, Screen_eDrawQTaskEvent, StatusMessageScreen_DrawHandler);
  Symbol_Register(
    (char *)&g_ptQSprite.atTexInfo,
    StatusMessageScreen_ClearMessagesCB,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
}

// source: j/0/screens/statusscreen/statusmessagescreen.c:688  [size]
void __cdecl StatusMessageScreen_Close()
{
  QTask_DeleteQTaskType(StatusMessageScreen_eQTaskType);
}

// source: j/0/screens/statusscreen/statusmessagescreen.c:702  [size]
struct StatusMessageScreen_s *__cdecl StatusMessageScreen_New(struct QTask_s *ptParent)
{
  return (struct StatusMessageScreen_s *)QTask_NewFn(ptParent, StatusMessageScreen_eQTaskType, nullptr);
}

// source: j/0/screens/statusscreen/statusmessagescreen.c:731  [anchor-caller]
int __cdecl StatusMessageScreen_GetBoxWidth()
{
  struct QTask_s *ptHead; // eax
  struct QTask_s *v1; // eax
  struct QSprite_s *Font; // eax

  ptHead = Game_ptGame->ptGameScreenQTask[1].tQTaskChildren.ptHead;
  if ( ptHead )
    v1 = ptHead->tQTaskChildren.ptHead;
  else
    v1 = nullptr;
  Font = MenuManager_GetFont(v1, (char *)&g_zFontName_0);
  return (__int64)((double)Font_GetStringWidth(Font, (char *)&g_ptQSprite) * 40.0 + 5.0);
}

// source: j/0/screens/statusscreen/statusmessagescreen.c:755  [anchor-callee]
int __cdecl StatusMessageScreen_RegisterMessage(
        struct StatusMessageScreen_s *ptStatusMessageScreen,
        struct StatusMessage_s *ptStatusMessage)
{
  int v2; // ebp
  char *p_isUsed; // eax
  int v5; // edi
  char *zSprite; // eax
  struct StaticTilemap_s **aptText; // esi
  struct QSprite_s *Font; // ebp
  int v9; // ebx
  struct StatusMessageScreen_s *v10; // esi
  struct QSprite_s *ptSprite; // eax
  double vBoxHeight; // st7
  struct StatusMessage_s *v13; // ebx
  char *pzText; // eax
  char *v15; // esi
  unsigned int nElements; // ebp
  struct QVector_s *v17; // ebx
  void **papxElement; // edx
  int iFreeMessage; // [esp+8h] [ebp-Ch]
  int iMessageIcon; // [esp+Ch] [ebp-8h]
  char *v21; // [esp+10h] [ebp-4h]

  v2 = 0;
  p_isUsed = &ptStatusMessageScreen->atRegisteredMessage[1].isUsed;
  while ( *(p_isUsed - 4148) )
  {
    if ( !*p_isUsed )
    {
      ++v2;
      break;
    }
    if ( !p_isUsed[4148] )
    {
      v2 += 2;
      break;
    }
    if ( !p_isUsed[8296] )
    {
      v2 += 3;
      break;
    }
    if ( !p_isUsed[12444] )
    {
      v2 += 4;
      break;
    }
    if ( !p_isUsed[16592] )
    {
      v2 += 5;
      break;
    }
    if ( !p_isUsed[20740] )
    {
      v2 += 6;
      break;
    }
    if ( !p_isUsed[24888] )
    {
      v2 += 7;
      break;
    }
    v2 += 8;
    p_isUsed += 33184;
    if ( v2 >= 24 )
      break;
  }
  iFreeMessage = v2;
  if ( v2 == 24 )
    return -1;
  v5 = v2;
  ptStatusMessageScreen->atRegisteredMessage[v2].isUsed = 1;
  ptStatusMessageScreen->atRegisteredMessage[v5].ptQTaskRef = QTask_NewQTaskRef(&ptStatusMessage->tEditorRigidObj.tQTask);
  ptStatusMessageScreen->atRegisteredMessage[v5].nDisplayTime = 0;
  ptStatusMessageScreen->atRegisteredMessage[v5].nTextPrintedTime = 0;
  ptStatusMessageScreen->atRegisteredMessage[v5].vBoxSizeScaleX = 0.0;
  ptStatusMessageScreen->atRegisteredMessage[v5].vBoxSizeScaleY = 0.0;
  zSprite = ptStatusMessage->zSprite;
  ptStatusMessage->isFinishedPrinting = 0;
  ptStatusMessageScreen->atRegisteredMessage[v5].ptSprite = nullptr;
  if ( ptStatusMessage->zSprite[0] )
  {
    iMessageIcon = 0;
    while ( strcmp(zSprite, StatusScreen_azQSpriteMessageIcon[iMessageIcon]) )
    {
      if ( ++iMessageIcon >= 4 )
        goto LABEL_28;
      zSprite = ptStatusMessage->zSprite;
    }
    ptStatusMessageScreen->atRegisteredMessage[v5].ptSprite = (struct QSprite_s *)&(&StatusScreen_ptStatusScreenQTask[12].tQTaskRefList.ptTail)[6 * iMessageIcon];
  }
LABEL_28:
  aptText = ptStatusMessageScreen->atRegisteredMessage[v5].aptText;
  Font = StatusMessageScreen_GetFont(ptStatusMessageScreen, v2);
  v9 = 3;
  do
  {
    *aptText++ = Text_New(Font, 0.0, 0.0, (char *)&g_zInitialValue);
    --v9;
  }
  while ( v9 );
  v10 = ptStatusMessageScreen;
  ptSprite = ptStatusMessageScreen->atRegisteredMessage[v5].ptSprite;
  ptStatusMessageScreen->atRegisteredMessage[v5].vBoxHeight = 0.0;
  if ( ptSprite )
    ptStatusMessageScreen->atRegisteredMessage[v5].vBoxHeight = (float)ptSprite->atQAnimframe[ptSprite->nQAnimframes].nHeight;
  vBoxHeight = (double)(3 * Font->atQAnimframe[Font->nQAnimframes].nHeight) + 4.0;
  if ( vBoxHeight < ptStatusMessageScreen->atRegisteredMessage[v5].vBoxHeight )
    vBoxHeight = ptStatusMessageScreen->atRegisteredMessage[v5].vBoxHeight;
  ptStatusMessageScreen->atRegisteredMessage[v5].vBoxHeight = vBoxHeight;
  v13 = ptStatusMessage;
  ptStatusMessageScreen->atRegisteredMessage[v5].vBoxWidth = (double)Font_GetStringWidth(
                                                                       Font,
                                                                       (char *)&g_ptQSprite)
                                                           * 40.0;
  pzText = ptStatusMessage->pzText;
  if ( pzText )
  {
    strncpy(ptStatusMessageScreen->atRegisteredMessage[v5].zText, pzText, 0x1000u);
    if ( ptStatusMessage->isCutSceneMessage )
    {
LABEL_42:
      v10->atRegisteredMessage[v5].zCurrentTextPos = &v10->atRegisteredMessage[v5].zText[strlen(v10->atRegisteredMessage[v5].zText)];
      return iFreeMessage;
    }
    v15 = ptStatusMessage->pzText;
    v21 = (char *)Mem_AllocFn(strlen(v15) + 1, 4);
    strcpy(v21, v15);
    nElements = ComputerLog_ptQVector->tPrivate.nElements;
    v17 = ComputerLog_ptQVector;
    if ( ComputerLog_ptQVector->tPrivate.nElements == ComputerLog_ptQVector->tPrivate.nArraySize )
      QVector_Realloc(ComputerLog_ptQVector, 1u);
    if ( nElements < v17->tPrivate.nElements - 1 )
      memmove(
        &v17->tPrivate.papxElement[nElements + 1],
        &v17->tPrivate.papxElement[nElements],
        4 * (v17->tPrivate.nElements - nElements));
    papxElement = v17->tPrivate.papxElement;
    v10 = ptStatusMessageScreen;
    ++v17->tPrivate.nElements;
    v13 = ptStatusMessage;
    papxElement[nElements] = v21;
  }
  if ( v13->isCutSceneMessage )
    goto LABEL_42;
  v10->atRegisteredMessage[v5].zCurrentTextPos = v10->atRegisteredMessage[v5].zText;
  return iFreeMessage;
}

// source: j/0/screens/statusscreen/statusmessagescreen.c:876  [anchor-callee]
void __cdecl StatusMessageScreen_RemoveMessage(
        struct StatusMessageScreen_s *ptStatusMessageScreen,
        int iMessage)
{
  char *v2; // esi
  struct QTilemap_s ***v3; // ebp
  int v4; // ebx
  struct QTilemap_s **v5; // esi
  int v6; // esi

  v2 = (char *)ptStatusMessageScreen + 4148 * iMessage;
  QReference_Delete(*((struct QReference_s **)v2 + 10), &QTask_tQTaskRefPool);
  *((_DWORD *)v2 + 10) = 0;
  v2[72] = 0;
  v3 = (struct QTilemap_s ***)(v2 + 56);
  v4 = 3;
  do
  {
    v5 = *v3;
    QTilemap_Delete(**v3);
    v6 = *(_DWORD *)((unsigned int)(v5 - 1) & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v6);
    memset(*(void **)(v6 + 8), 0xCDu, *(_DWORD *)(v6 + 16));
    free((void *)v6);
    *v3++ = nullptr;
    --v4;
  }
  while ( v4 );
}

// source: j/0/screens/statusscreen/statusmessagescreen.c:910  [anchor-strings]
void __cdecl StatusMessageScreen_LoadResource()
{
  char *v0; // ecx
  int v1; // eax
  void *v2; // eax
  char zFilename[4]; // [esp+4h] [ebp-4h] BYREF

  if ( Resource_IsLoadedInternal("LANGUAGE:messages.res", (struct Resource_s **)zFilename) )
  {
    v1 = *(_DWORD *)zFilename;
    *(_DWORD *)(*(_DWORD *)zFilename + 44) = 1;
    StatusMessageScreen_tResource.pxLanguageResource = *(void **)(v1 + 52);
  }
  else
  {
    Game_MPRunNetwork(v0);
    v2 = File_Load("LANGUAGE:messages.res", (unsigned int *)zFilename);
    if ( !v2 )
    {
      LDebug_Error("Failed to load resource: '%s'", "LANGUAGE:messages.res");
      abort();
    }
    StatusMessageScreen_tResource.pxLanguageResource = Resource_ParseFile(
                                                         File_zLastSubstitutedPath,
                                                         v2,
                                                         *(unsigned int *)zFilename);
  }
}

// source: j/0/screens/statusscreen/statusmessagescreen.c:924  [anchor-hash]
void __cdecl StatusMessageScreen_FreeResource()
{
  struct Resource_s *ptHead; // ecx
  struct Resource_s *ptNext; // eax
  unsigned int nType; // eax

  ptHead = Resource_tResourceList.ptHead;
  ptNext = Resource_tResourceList.ptHead->ptNext;
  if ( Resource_tResourceList.ptHead->ptNext )
  {
    while ( ptHead->pxData != StatusMessageScreen_tResource.pxLanguageResource )
    {
      ptHead = ptNext;
      ptNext = ptNext->ptNext;
      if ( !ptNext )
        return;
    }
    nType = ptHead->nType;
    if ( nType != 3 && nType != 1 )
      Resource_Remove(ptHead);
  }
}

// source: j/0/screens/statusscreen/statusmessagescreen.c:938  [anchor-hash]
void __cdecl StatusMessageScreen_RemoveAllMessages(struct StatusMessageScreen_s *ptStatusMessageScreen)
{
  int v1; // esi
  char *p_isUsed; // edi

  v1 = 0;
  p_isUsed = &ptStatusMessageScreen->atRegisteredMessage[0].isUsed;
  do
  {
    if ( *p_isUsed )
      StatusMessageScreen_RemoveMessage(ptStatusMessageScreen, v1);
    ++v1;
    p_isUsed += 4148;
  }
  while ( v1 < 24 );
}
