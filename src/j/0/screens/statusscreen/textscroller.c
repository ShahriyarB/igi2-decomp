/* j/0/screens/statusscreen/textscroller.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/screens/statusscreen/textscroller.c:45  [size]
unsigned __int16 __cdecl TextScroller_GetQTaskType()
{
  return TextScroller_eQTaskType;
}

// source: j/0/screens/statusscreen/textscroller.c:59  [size]
struct QTask_s *__cdecl TextScroller_New(
        struct QTask_s *ptParentQTask,
        struct TextScrollerCreateContext_s *ptCreateContext)
{
  return QTask_NewFn(ptParentQTask, TextScroller_eQTaskType, ptCreateContext);
}

// source: j/0/screens/statusscreen/textscroller.c:74  [anchor-mhash]
struct TextScroller_s *__cdecl TextScroller_SetFade(
        struct TextScroller_s *ptScroller,
        struct TextScrollerLine_s *ptLine,
        int nTick)
{
  bool v3; // sf
  double v4; // st7
  double v5; // st7
  struct TextScroller_s *result; // eax
  int nDisplayTicks; // [esp+0h] [ebp-4h]
  struct TextScroller_s *ptScrollera = *(struct TextScroller_s * *)&nTick; // [esp+8h] [ebp+4h] ARGSLOT

  v3 = nTick - ptLine->nEndTick < 0;
  nDisplayTicks = ptScroller->nDisplayTicks;
  ptScrollera = (struct TextScroller_s *)(nTick + nDisplayTicks - ptLine->nEndTick);
  if ( v3 ^ __OFSUB__(ptScrollera, nDisplayTicks) | (ptScrollera == (struct TextScroller_s *)nDisplayTicks) )
  {
    v5 = (double)(int)ptScrollera / (double)nDisplayTicks;
    if ( v5 >= 0.05000000074505806 )
    {
      if ( v5 <= 0.800000011920929 )
        v4 = 1.0;
      else
        v4 = 1.0 - (v5 - 0.800000011920929) * 5.0;
    }
    else
    {
      v4 = v5 * 20.0;
    }
  }
  else
  {
    v4 = 0.0;
  }
  result = (struct TextScroller_s *)ptLine->ptQText;
  ptLine->ptQText->bQGraphicFlags |= 0x80000u;
  ptLine->ptQText->vA = v4;
  return result;
}

// source: j/0/screens/statusscreen/textscroller.c:133  [anchor-mhash]
void __cdecl TextScroller_DrawHandler(struct QTask_s *ptQTask)
{
  struct TextScroller_s *v1; // ebx
  struct QTask_s *ptHead; // edi
  signed int v3; // eax
  struct QTilemap_s ***v4; // esi
  bool v5; // zf
  int nSkipLines; // [esp+Ch] [ebp-1Ch]
  float vPosY; // [esp+10h] [ebp-18h]
  int v8; // [esp+14h] [ebp-14h]
  int nTick; // [esp+18h] [ebp-10h]
  struct QTask_s *vPosX; // [esp+1Ch] [ebp-Ch]

  v1 = (struct TextScroller_s *)ptQTask;
  vPosY = *(float *)&ptQTask[4].ptPrev;
  vPosX = ptQTask[4].ptNext;
  nTick = Flow_ptFlow->nTicks;
  ptHead = ptQTask[4].tQTaskChildren.ptHead;
  v3 = 10 - (unsigned int)ptQTask[4].tQTaskChildren.ptTail;
  nSkipLines = v3;
  if ( (InputPort_atInputPort[0].tInput.bCurrentButton & 0x1000000000000LL) != 0 )
  {
    nSkipLines = 0;
    v3 = 0;
  }
  v8 = 10;
  while ( 1 )
  {
    v4 = (struct QTilemap_s ***)&v1->atLine[(_DWORD)ptHead];
    if ( v1->atLine[(_DWORD)ptHead].isShowing )
    {
      if ( v3 <= 0 )
      {
        TextScroller_SetFade(v1, &v1->atLine[(_DWORD)ptHead], nTick);
        *((float *)*v4 + 1) = (float)(__int64)*(float *)&vPosX;
        *((float *)*v4 + 2) = (float)(__int64)vPosY;
        QTilemap_Register(
          **v4,
          *((float *)*v4 + 1),
          *((float *)*v4 + 2),
          *((float *)*v4 + 5),
          *((float *)*v4 + 6),
          *((float *)*v4 + 7),
          *((float *)*v4 + 4),
          *((float *)*v4 + 3),
          (unsigned int)(*v4)[9] | 0x40000000,
          (int)(*v4)[8]);
        v1 = (struct TextScroller_s *)ptQTask;
      }
    }
    vPosY = (double)((**v4)->nHeight * (**v4)->ptQSprite->atQAnimframe[(**v4)->ptQSprite->nQAnimframes].nHeight) * 1.100000023841858
          + vPosY;
    v5 = v8 == 1;
    --nSkipLines;
    --v8;
    ptHead = (struct QTask_s *)(((int)&ptHead->ptNext + 1) % 10);
    if ( v5 )
      break;
    v3 = nSkipLines;
  }
}

// source: j/0/screens/statusscreen/textscroller.c:198  [anchor-strings]
_DWORD *__cdecl TextScroller_SetColour(_DWORD *result, int a2)
{
  switch ( a2 )
  {
    case 0:
      result[4] = 1036831949;
      result[5] = 1124073472;
      result[6] = 1115684864;
      result[7] = 1108973978;
      break;
    case 1:
      result[4] = 1036831949;
      result[5] = 1124073472;
      result[6] = 1117362586;
      result[7] = 1117362586;
      break;
    case 2:
      result[4] = 1036831949;
      result[5] = 0;
      result[6] = 1124073472;
      result[7] = 0;
      break;
    case 3:
      result[4] = 1036831949;
      result[5] = 1117362586;
      result[6] = 1124073472;
      result[7] = 1117362586;
      break;
    case 4:
      result[4] = 1036831949;
      result[5] = 0;
      result[6] = 1117362586;
      result[7] = 1124073472;
      break;
    case 5:
      result[4] = 1036831949;
      result[5] = 1124073472;
      result[6] = 1124073472;
      result[7] = 1124073472;
      break;
    case 6:
      result[4] = 1036831949;
      result[5] = 1124073472;
      result[6] = 1112329421;
      result[7] = 1124073472;
      break;
    case 7:
      result[4] = 1036831949;
      result[5] = 1124073472;
      result[6] = 1124073472;
      result[7] = 0;
      break;
    default:
      LDebug_Error((char *)&g_zMessage.nMomentOfDeath);
      abort();
  }
  return result;
}

// source: j/0/screens/statusscreen/textscroller.c:258  [anchor-caller]
void __cdecl TextScroller_AddLine(
        struct TextScroller_s *ptScroller,
        char *zText,
        enum TextScrollerColour_e eColour)
{
  int nNextSlot; // eax
  struct TextScrollerLine_s *v4; // edi
  struct Flow_t *v5; // edx
  char zTemp[256]; // [esp+0h] [ebp-100h] BYREF

  if ( Game_eGameMode != GAME_GAMEMODE_MULTIPLAYER || NetManager_eMode != NETMANAGER_MODE_WELCOME )
  {
    nNextSlot = ptScroller->nNextSlot;
    v4 = &ptScroller->atLine[nNextSlot];
    ptScroller->nNextSlot = (nNextSlot + 1) % 10;
    strncpy(zTemp, zText, 0xFFu);
    Text_SetString(v4->ptQText, zTemp);
    TextScroller_SetColour(&v4->ptQText->ptQTilemap, eColour);
    v5 = Flow_ptFlow;
    v4->isShowing = true;
    v4->nEndTick = ptScroller->nDisplayTicks + v5->nTicks;
  }
}

// source: j/0/screens/statusscreen/textscroller.c:306  [anchor-strings]
char *__cdecl TextScroller_Add(
        struct TextScroller_s *ptScroller,
        char *zText,
        enum TextScrollerColour_e eColour)
{
  #pragma pack(push, 1)
  union
  {
    struct { char *zWord; };
    struct { char igi2_o1[4]; char zTemp[1032]; };
    struct { char igi2_o2[1036]; char zCopy[1024]; };
    char igi2_extent[2060];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  char *result; // eax
  char *v5; // esi
  int v6; // ebx
  unsigned int v7; // eax
  char *v8; // edi
  _WORD *v10; // edi
  char v11; // al
  char *v12; // eax

  if ( strlen(zText) <= 0x400 )
  {
    strcpy(igi2_frame.zCopy, zText);
    result = strtok(igi2_frame.zCopy, (char *)&Delimiter);
    v5 = (char *)result;
    igi2_frame.zWord = (char *)result;
    if ( result )
    {
      do
      {
        v6 = 0;
        memset(igi2_frame.zTemp, 0, 1025);
        if ( v5 )
        {
          do
          {
            if ( v6 >= 70 )
              break;
            v7 = strlen(v5) + 1;
            v8 = (char *)&igi2_frame.zWord + 3;
            while ( *++v8 )
              ;
            qmemcpy(v8, v5, v7);
            v10 = (_WORD *)((char *)&igi2_frame.zWord + 3);
            do
            {
              v11 = *((_BYTE *)v10 + 1);
              v10 = (_WORD *)((char *)v10 + 1);
            }
            while ( v11 );
            v12 = igi2_frame.zWord;
            *v10 = 32;
            v6 += strlen(v12) + 1;
            igi2_frame.zWord = strtok(nullptr, (char *)&Delimiter);
            v5 = igi2_frame.zWord;
          }
          while ( igi2_frame.zWord );
        }
        igi2_frame.zTemp[254] = 0;
        TextScroller_AddLine(ptScroller, igi2_frame.zTemp, eColour);
      }
      while ( v5 );
    }
  }
  else
  {
    NetManager_LogMessage(&g_zMessage.zTalkString[228]);
  }
  return result;
}

// source: j/0/screens/statusscreen/textscroller.c:365  [anchor-mhash]
void __cdecl TextScroller_RunHandler(struct QTask_s *ptQTask)
{
  int nTicks; // ecx

  nTicks = Flow_ptFlow->nTicks;
  if ( ptQTask[1].tQTaskChildren.ptHead && (int)ptQTask[1].ptPrev < nTicks )
    ptQTask[1].tQTaskChildren.ptHead = nullptr;
  if ( ptQTask[1].tQTaskRefList.ptHead && (int)ptQTask[1].tQTaskChildren.ptTail < nTicks )
    ptQTask[1].tQTaskRefList.ptHead = nullptr;
  if ( ptQTask[1].ptParent && (int)ptQTask[1].tQTaskRefList.ptTail < nTicks )
    ptQTask[1].ptParent = nullptr;
  if ( ptQTask[2].ptPrev && (int)ptQTask[2].ptNext < nTicks )
    ptQTask[2].ptPrev = nullptr;
  if ( ptQTask[2].tQTaskChildren.ptTail && (int)ptQTask[2].tQTaskChildren.ptMiddle < nTicks )
    ptQTask[2].tQTaskChildren.ptTail = nullptr;
  if ( ptQTask[2].tQTaskRefList.ptTail && (int)ptQTask[2].tQTaskRefList.ptMiddle < nTicks )
    ptQTask[2].tQTaskRefList.ptTail = nullptr;
  if ( ptQTask[3].ptNext && (int)(*(_DWORD *)&ptQTask[2].eQTaskType) < nTicks )
    ptQTask[3].ptNext = nullptr;
  if ( ptQTask[3].tQTaskChildren.ptMiddle && (int)ptQTask[3].tQTaskChildren.ptHead < nTicks )
    ptQTask[3].tQTaskChildren.ptMiddle = nullptr;
  if ( ptQTask[3].tQTaskRefList.ptMiddle && (int)ptQTask[3].tQTaskRefList.ptHead < nTicks )
    ptQTask[3].tQTaskRefList.ptMiddle = nullptr;
  if ( *(_DWORD *)&ptQTask[3].eQTaskType )
  {
    if ( (int)ptQTask[3].ptParent < nTicks )
      *(_DWORD *)&ptQTask[3].eQTaskType = 0;
  }
}

// source: j/0/screens/statusscreen/textscroller.c:396  [anchor-strings]
void __cdecl TextScroller_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QSprite_s *v2; // ebp
  int v3; // edi
  struct QTask_s *v4; // esi
  struct StaticTilemap_s *v5; // eax
  struct QTask_s *ptNext; // eax
  char zTemp[256]; // [esp+10h] [ebp-100h] BYREF

  v2 = *((struct QSprite_s **)pxContext + 4);
  ptQTask[4].ptNext = *(struct QTask_s **)pxContext;
  ptQTask[4].ptPrev = *((struct QTask_s **)pxContext + 1);
  ptQTask[4].tQTaskChildren.ptMiddle = *((struct QTask_s **)pxContext + 2);
  ptQTask[4].tQTaskChildren.ptTail = *((struct QTask_s **)pxContext + 3);
  v3 = 0;
  v4 = ptQTask + 1;
  do
  {
    _snprintf(zTemp, 0xFFu, &g_zMessage.zTalkString[216], v3);
    v5 = Text_New(v2, 0.0, 0.0, zTemp);
    v4->ptNext = (struct QTask_s *)v5;
    v5->nPri = 0;
    ptNext = v4->ptNext;
    v4->tQTaskChildren.ptHead = nullptr;
    ++v3;
    v4 = (struct QTask_s *)((char *)v4 + 12);
    ptNext->tQTaskChildren.ptTail = (struct QTask_s *)1065353216;
    ptNext->tQTaskRefList.ptHead = nullptr;
    ptNext->tQTaskRefList.ptMiddle = nullptr;
    ptNext->tQTaskRefList.ptTail = nullptr;
  }
  while ( v3 < 10 );
  ptQTask[4].tQTaskChildren.ptHead = nullptr;
}

// source: j/0/screens/statusscreen/textscroller.c:452  [anchor-strings]
void __cdecl TextScroller_DeleteHandler(struct QTask_s *ptQTask)
{
  int v1; // ebp
  struct QTilemap_s ***v2; // ebx
  struct QTilemap_s **v3; // esi
  int v4; // esi

  v1 = 0;
  v2 = (struct QTilemap_s ***)&ptQTask[1];
  do
  {
    v3 = *v2;
    if ( !*v2 )
    {
      LDebug_Error(&g_zMessage.zTalkString[184]);
      abort();
    }
    QTilemap_Delete(*v3);
    v4 = *(_DWORD *)((unsigned int)(v3 - 1) & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v4);
    memset(*(void **)(v4 + 8), 0xCDu, *(_DWORD *)(v4 + 16));
    free((void *)v4);
    *v2 = nullptr;
    ++v1;
    v2 += 3;
  }
  while ( v1 < 10 );
}

// source: j/0/screens/statusscreen/textscroller.c:486  [size]
void __cdecl TextScroller_Close()
{
  QTask_DeleteQTaskType(TextScroller_eQTaskType);
}

// source: j/0/screens/statusscreen/textscroller.c:500  [anchor-hash]
void __cdecl TextScroller_Open()
{
  unsigned __int16 BaseQTaskType; // ax
  unsigned __int16 v1; // si

  BaseQTaskType = QTask_GetBaseQTaskType();
  v1 = QTask_NewQTaskType(&g_zMessage.zTalkString[168], 180, BaseQTaskType, 0, 0);
  TextScroller_eQTaskType = v1;
  QTask_LinkQTaskEventHandlerFn(v1, 0, TextScroller_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 1, TextScroller_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 2, TextScroller_DeleteHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, Screen_eDrawQTaskEvent, TextScroller_DrawHandler);
}
