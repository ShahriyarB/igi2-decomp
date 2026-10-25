/* h/2/screengrab.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: h/2/screengrab.c:103  [anchor-callee]
struct TargaHeader_s *__cdecl ScreenGrab_WriteTargaHeader(
        struct File_s *ptFile,
        struct TargaHeader_s *ptHeader,
        int nWidth,
        int nHeight)
{
  ptHeader->nImageWidth = nWidth;
  ptHeader->nImageIdentificationLength = 0;
  ptHeader->eColorMapType = 0;
  ptHeader->eImageType = 2;
  ptHeader->nColorMapOrigin[0] = 0;
  ptHeader->nColorMapOrigin[1] = 0;
  ptHeader->nColorMapLength[0] = 0;
  ptHeader->nColorMapLength[1] = 0;
  ptHeader->nColorMapEntrySize = 0;
  ptHeader->nXOffset = 0;
  ptHeader->nYOffset = 0;
  ptHeader->nImageHeight = nHeight;
  ptHeader->nBitsPerPixel = 24;
  ptHeader->bImageDescription = 32;
  if ( ptFile )
    return (struct TargaHeader_s *)File_atDevice[ptFile->eDeviceID].pfWrite(ptFile->eDeviceID, ptFile, ptHeader, 18u);
  return ptHeader;
}

// source: h/2/screengrab.c:142  [size]
void __cdecl ScreenGrab_CreateHandler(struct QTask_s *ptQTask, void *pxData)
{
  ptQTask[1].ptNext = nullptr;
  LOBYTE(ptQTask[1].ptPrev) = 0;
  BYTE1(ptQTask[1].ptPrev) = 0;
  BYTE2(ptQTask[1].ptPrev) = 0;
}

// source: h/2/screengrab.c:163  [anchor-hash]
void __cdecl ScreenGrab_RunHandler(struct QTask_s *ptQTask)
{
  if ( AppContext_tAppContext.isActive )
  {
    if ( (Keyboard_tKeyboard.anCurrentKey[29] & 0x80u) != 0
      && (Keyboard_tKeyboard.anCurrentKey[181] & 0x80) != 0
      && (Keyboard_tKeyboard.anPreviousKey[181] & 0x80) == 0
      || (Keyboard_tKeyboard.anCurrentKey[183] & 0x80) != 0 && (Keyboard_tKeyboard.anPreviousKey[183] & 0x80) == 0 )
    {
      ScreenGrab_nDeltaPictureNumber = 100000;
      ScreenGrab_isGrabSingle[0] = 1;
    }
    if ( (Keyboard_tKeyboard.anCurrentKey[56] & 0x80) != 0
      && (Keyboard_tKeyboard.anCurrentKey[181] & 0x80) != 0
      && (Keyboard_tKeyboard.anPreviousKey[181] & 0x80) == 0 )
    {
      if ( !ScreenGrab_isRecord[0] )
        ScreenGrab_nDeltaPictureNumber = 100000;
      ScreenGrab_isRecord[0] = 1;
    }
    if ( (Keyboard_tKeyboard.anCurrentKey[56] & 0x80) != 0
      && (Keyboard_tKeyboard.anCurrentKey[42] & 0x80) != 0
      && (Keyboard_tKeyboard.anCurrentKey[181] & 0x80) != 0
      && (Keyboard_tKeyboard.anPreviousKey[181] & 0x80) == 0 )
    {
      ScreenGrab_nDeltaPictureNumber = 100000;
      ScreenGrab_isRecord[0] = 0;
    }
  }
}

// source: h/2/screengrab.c:210  [anchor-mhash]
void __cdecl ScreenGrab_DrawHandler(struct QTask_s *ptQTask)
{
  if ( !ScreenGrab_isRecord[0] )
  {
    if ( !ScreenGrab_isGrabSingle[0] )
      return;
LABEL_7:
    ScreenGrab_Grab((char *)ptQTask[1].ptNext);
    return;
  }
  if ( Level_isDynamicQTaskActive || !Level_isDynamicQTaskPaused || BYTE1(ptQTask[1].ptPrev) )
    goto LABEL_7;
}

// source: h/2/screengrab.c:242  [size]
void __cdecl ScreenGrab_DeleteHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptNext; // eax
  int v2; // esi

  ptNext = ptQTask[1].ptNext;
  if ( ptNext )
  {
    v2 = *(_DWORD *)((unsigned int)&ptNext[-1].eQTaskType & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v2);
    memset(*(void **)(v2 + 8), 0xCDu, *(_DWORD *)(v2 + 16));
    free((void *)v2);
  }
  ptQTask[1].ptNext = nullptr;
}

// source: h/2/screengrab.c:260  [anchor-strings]
void __cdecl ScreenGrab_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxData)
{
  struct QTask_s *v2; // eax
  char ptPrev; // al

  if ( !ptQTask[1].ptNext )
  {
    v2 = (struct QTask_s *)Mem_AllocFn(11, 4);
    ptQTask[1].ptNext = v2;
    strcpy((char *)v2, "LOCAL:grab");
  }
  ptPrev = (char)ptQTask[1].ptPrev;
  if ( ptPrev )
  {
    if ( !BYTE2(ptQTask[1].ptPrev) )
    {
      ScreenGrab_nDeltaPictureNumber = 100000;
      ScreenGrab_isRecord[0] = 1;
    }
  }
  else
  {
    ScreenGrab_isRecord[0] = 0;
  }
  BYTE2(ptQTask[1].ptPrev) = ptPrev;
}

// source: h/2/screengrab.c:297  [size]
void __cdecl ScreenGrab_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = ScreenGrab_ptParameterList;
}

// source: h/2/screengrab.c:317  [anchor-hash]
void __cdecl ScreenGrab_Open()
{
  unsigned __int16 BaseQTaskType; // ax
  unsigned __int16 v1; // si
  struct ParameterList_s *v2; // eax
  int v3; // edx

  BaseQTaskType = QTask_GetBaseQTaskType();
  v1 = QTask_NewQTaskType("ScreenGrab", 48, BaseQTaskType, 0, 0);
  ScreenGrab_eQTaskType = v1;
  QTask_LinkQTaskEventHandlerFn(v1, 0, (void (__cdecl *)(struct QTask_s *, void *))ScreenGrab_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 1, ScreenGrab_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, Screen_eDrawQTaskEvent, ScreenGrab_DrawHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 2, ScreenGrab_DeleteHandler);
  QTask_LinkQTaskEventHandlerFn(v1, ParameterList_eUpdateInternalDataQTaskEvent, ScreenGrab_UpdateInternalDataHandler);
  QTask_LinkQTaskEventHandlerFn(
    v1,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))ScreenGrab_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(
    v1,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveHandler);
  v2 = (struct ParameterList_s *)Mem_AllocFn(72, 4);
  v3 = Level_eParameterTypeVarString;
  v2->ptParameterListItem = (struct ParameterListItem_s *)&v2[1];
  v2->nParameters = 0;
  v2->nMaxParameters = 3;
  ScreenGrab_ptParameterList = v2;
  ParameterList_AddParameter(v2, 0x28u, v3, "Destination Path", 7u, nullptr);
  ParameterList_AddParameter(
    ScreenGrab_ptParameterList,
    0x2Cu,
    Level_eParameterTypebool8,
    "Save sequence from start",
    7u,
    nullptr);
  ParameterList_AddParameter(
    ScreenGrab_ptParameterList,
    0x2Du,
    Level_eParameterTypebool8,
    "Allow sequence grabbing from editor",
    7u,
    nullptr);
  ScreenGrab_nPictureNumber = 0;
  ScreenGrab_isRecord[0] = 0;
  ScreenGrab_isGrabSingle[0] = 0;
}

// source: h/2/screengrab.c:360  [size]
void __cdecl ScreenGrab_Close()
{
  int v0; // esi

  if ( ScreenGrab_ptParameterList )
  {
    v0 = *(_DWORD *)((unsigned int)&ScreenGrab_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
  QTask_DeleteQTaskType(ScreenGrab_eQTaskType);
}

// source: h/2/screengrab.c:379  [size]
unsigned __int16 __cdecl ScreenGrab_GetQTaskType()
{
  return ScreenGrab_eQTaskType;
}

// source: h/2/screengrab.c:396  [anchor-strings]
void __cdecl ScreenGrab_Grab(char *zPath)
{
  #pragma pack(push, 1)
  union
  {
    struct { char zFileName[1024]; };
    struct { char igi2_o1[1024]; char zRealPath[1024]; };
    char igi2_extent[2048];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  unsigned int v2; // eax
  char v3; // cl
  struct File_s *v4; // eax
  struct File_s *v5; // eax
  struct File_s *v6; // esi
  unsigned __int8 *v7; // edi
  struct File_s *v8; // esi
  int v9; // esi

  if ( !ScreenGrab_isRecord[0] )
  {
    if ( !ScreenGrab_isGrabSingle[0] )
      return;
    goto LABEL_5;
  }
  if ( ScreenGrab_isGrabSingle[0] )
LABEL_5:
    ScreenGrab_isGrabSingle[0] = 0;
  if ( ScreenGrab_nDeltaPictureNumber == 100000 )
    ScreenGrab_nPictureNumber = 100000 * (ScreenGrab_nPictureNumber / 100000);
  if ( zPath )
  {
    v2 = strlen(zPath);
    v3 = zPath[v2];
    if ( v3 == 92 || v3 == 47 )
      zPath[v2] = 0;
    sprintf(igi2_frame.zRealPath, (char *const)&stru_6A4CDC.tDebugConsoleLineList.ptMiddle, zPath);
  }
  else
  {
    sprintf(igi2_frame.zRealPath, (char *const)&stru_6A4CDC.tDebugConsoleLineList.ptMiddle, "LOCAL:grab");
  }
  sprintf(igi2_frame.zFileName, "%s/empty.dat", igi2_frame.zRealPath);
  v4 = File_New(igi2_frame.zFileName, "w");
  if ( v4 )
  {
    if ( v4 == &File_tDummyAsyncFile )
      File_tDummyAsyncFile.isAsync = false;
    else
      File_atDevice[v4->eDeviceID].pfDelete(v4->eDeviceID, v4);
    do
    {
      sprintf(igi2_frame.zFileName, "%s/A%07d.tga", igi2_frame.zRealPath, ScreenGrab_nPictureNumber);
      v5 = File_New(igi2_frame.zFileName, "r");
      v6 = v5;
      if ( v5 )
      {
        if ( v5 == &File_tDummyAsyncFile )
          File_tDummyAsyncFile.isAsync = false;
        else
          File_atDevice[v5->eDeviceID].pfDelete(v5->eDeviceID, v5);
      }
      else
      {
        ScreenGrab_nDeltaPictureNumber = 1;
      }
      ScreenGrab_nPictureNumber += ScreenGrab_nDeltaPictureNumber;
    }
    while ( v6 );
    v7 = (unsigned __int8 *)Mem_AllocFn(3 * Display_tActiveMode.nWidth * Display_tActiveMode.nHeight, 4);
    if ( v7 )
    {
      v8 = File_New(igi2_frame.zFileName, "w");
      if ( v8 )
      {
        Display_Snapshot(v7);
        ScreenGrab_WriteTargaHeader(
          v8,
          &ScreenGrab_tTargaHeader,
          Display_tActiveMode.nWidth,
          Display_tActiveMode.nHeight);
        File_Write(v8, v7, 3 * Display_tActiveMode.nWidth * Display_tActiveMode.nHeight);
        File_atDevice[v8->eDeviceID].pfSync(v8->eDeviceID, v8, FILE_SYNC_WAIT);
        File_Delete(v8);
      }
      v9 = *(_DWORD *)((unsigned int)(v7 - 4) & 0xFFFFFFFC);
      --Mem_nCurrentAllocations;
      Node_Remove((_DWORD **)v9);
      memset(*(void **)(v9 + 8), 0xCDu, *(_DWORD *)(v9 + 16));
      free((void *)v9);
    }
  }
}

// source: h/2/screengrab.c:526  [anchor-hash]
char __cdecl ScreenGrab_InProgress()
{
  return ScreenGrab_isRecord[0] || ScreenGrab_isGrabSingle[0];
}
