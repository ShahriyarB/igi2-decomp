/* h/2/globallighttask.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: h/2/globallighttask.c:107  [anchor-mhash]
void __cdecl GlobalLightQTask_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QReferenceList_s *p_tQTaskRefList; // eax
  int v3; // edi

  ptQTask[1].ptNext = (struct QTask_s *)World_ptActiveWorld;
  ptQTask[2].ptNext = (struct QTask_s *)1148846080;
  ptQTask[2].ptPrev = (struct QTask_s *)1061997773;
  ptQTask[2].tQTaskChildren.ptHead = (struct QTask_s *)1101004800;
  ptQTask[2].tQTaskChildren.ptMiddle = (struct QTask_s *)1043878380;
  LOBYTE(ptQTask[11].tQTaskChildren.ptTail) = 0;
  p_tQTaskRefList = &ptQTask[2].tQTaskRefList;
  v3 = 5;
  do
  {
    p_tQTaskRefList[-1].ptTail = nullptr;
    p_tQTaskRefList->ptHead = nullptr;
    p_tQTaskRefList->ptMiddle = nullptr;
    p_tQTaskRefList->ptTail = (struct QReference_s *)1065353216;
    p_tQTaskRefList[1].ptHead = (struct QReference_s *)1065353216;
    p_tQTaskRefList[1].ptMiddle = (struct QReference_s *)1065353216;
    p_tQTaskRefList[1].ptTail = nullptr;
    p_tQTaskRefList[2].ptHead = (struct QReference_s *)1065353216;
    p_tQTaskRefList[2].ptMiddle = nullptr;
    p_tQTaskRefList[2].ptTail = nullptr;
    p_tQTaskRefList[3].ptHead = nullptr;
    p_tQTaskRefList[3].ptMiddle = (struct QReference_s *)1065353216;
    p_tQTaskRefList[3].ptTail = nullptr;
    p_tQTaskRefList[4].ptHead = nullptr;
    p_tQTaskRefList[4].ptMiddle = nullptr;
    p_tQTaskRefList[4].ptTail = (struct QReference_s *)1065353216;
    p_tQTaskRefList = (struct QReferenceList_s *)((char *)p_tQTaskRefList + 64);
    --v3;
  }
  while ( v3 );
  ptQTask[11].ptNext = (struct QTask_s *)1065353216;
  ptQTask[11].ptPrev = (struct QTask_s *)1065353216;
  ptQTask[11].tQTaskChildren.ptHead = (struct QTask_s *)1065353216;
  ptQTask[11].tQTaskChildren.ptMiddle = (struct QTask_s *)1065353216;
  ptQTask[10].tQTaskRefList.ptTail = nullptr;
  ptQTask[10].ptParent = nullptr;
  *(_DWORD *)&ptQTask[10].eQTaskType = 0;
  BYTE2(ptQTask[11].tQTaskChildren.ptTail) = 1;
  BYTE1(ptQTask[11].tQTaskChildren.ptTail) = 0;
  GlobalLightQTask_ptGlobalLight = (struct GlobalLightQTask_t *)ptQTask;
}

// source: h/2/globallighttask.c:153  [size]
void __cdecl GlobalLightQTask_RunHandler(struct QTask_s *ptQTask)
{
  ;
}

// source: h/2/globallighttask.c:168  [size]
void __cdecl GlobalLightQTask_DeleteHandler(struct QTask_s *ptQTask)
{
  GlobalLightQTask_ptGlobalLight = nullptr;
}

// source: h/2/globallighttask.c:186  [size]
void __cdecl GlobalLightQTask_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = GlobalLightQTask_ptParameterList;
}

// source: h/2/globallighttask.c:203  [anchor-mhash]
void __cdecl GlobalLightQTask_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  void (__cdecl *v2)(void *); // eax
  unsigned __int16 v3; // dx
  struct QTask_s *i; // esi
  struct GlobalLightQTask_t *v5; // ecx

  if ( BYTE1(ptQTask[11].tQTaskChildren.ptTail) )
  {
    ptQTask[10].tQTaskRefList.ptTail = nullptr;
    ptQTask[10].ptParent = nullptr;
    *(_DWORD *)&ptQTask[10].eQTaskType = 0;
    ptQTask[11].ptNext = (struct QTask_s *)1065353216;
    ptQTask[11].ptPrev = (struct QTask_s *)1065353216;
    ptQTask[11].tQTaskChildren.ptHead = (struct QTask_s *)1065353216;
    ptQTask[11].tQTaskChildren.ptMiddle = (struct QTask_s *)1065353216;
    BYTE2(ptQTask[11].tQTaskChildren.ptTail) = 1;
    BYTE1(ptQTask[11].tQTaskChildren.ptTail) = 0;
  }
  if ( BYTE2(ptQTask[11].tQTaskChildren.ptTail) )
  {
    v2 = RenderMode_tActiveRenderMode.apfRenderModeMethod[Texture_eReloadTextureMethod];
    qmemcpy(
      &Texture_tActiveTextureFilterContext,
      &ptQTask[10].tQTaskRefList.ptTail,
      sizeof(Texture_tActiveTextureFilterContext));
    if ( v2 )
      v2(nullptr);
    BYTE2(ptQTask[11].tQTaskChildren.ptTail) = 0;
  }
  v3 = GlobalLightKeyframeQTask_eQTaskType;
  ptQTask[10].tQTaskRefList.ptMiddle = (struct QReference_s *)-8388609;
  ptQTask[10].tQTaskRefList.ptHead = (struct QReference_s *)-8388609;
  ptQTask[10].tQTaskChildren.ptTail = (struct QTask_s *)2139095039;
  for ( i = QTask_GetFirstChildOfType(ptQTask, v3); i; i = QTask_GetNextSiblingOfType(i, v3) )
  {
    if ( *(float *)&i[2].ptNext > (double)*(float *)&ptQTask[10].tQTaskRefList.ptHead )
      ptQTask[10].tQTaskRefList.ptHead = (struct QReference_s *)i[2].ptNext;
    if ( *(float *)&i[2].ptNext < (double)*(float *)&ptQTask[10].tQTaskChildren.ptTail )
      ptQTask[10].tQTaskChildren.ptTail = i[2].ptNext;
  }
  v5 = GlobalLightQTask_ptGlobalLight;
  if ( GlobalLightQTask_ptGlobalLight )
  {
    if ( 0.0 != GlobalLightQTask_ptGlobalLight->vCurrentTime )
    {
      GlobalLightQTask_ptGlobalLight->vCurrentTime = 0.0;
      GlobalLightQTask_Update(v5);
    }
  }
}

// source: h/2/globallighttask.c:256  [anchor-mhash]
void __cdecl GlobalLightKeyframeQTask_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTaskNodeList_s *p_tQTaskChildren; // eax
  int v3; // esi

  p_tQTaskChildren = &ptQTask[2].tQTaskChildren;
  v3 = 5;
  do
  {
    p_tQTaskChildren[-1].ptTail = nullptr;
    p_tQTaskChildren->ptHead = nullptr;
    p_tQTaskChildren->ptMiddle = nullptr;
    p_tQTaskChildren->ptTail = (struct QTask_s *)1065353216;
    p_tQTaskChildren[1].ptHead = (struct QTask_s *)1065353216;
    p_tQTaskChildren[1].ptMiddle = (struct QTask_s *)1065353216;
    p_tQTaskChildren[1].ptTail = nullptr;
    p_tQTaskChildren[5].ptHead = (struct QTask_s *)-1;
    p_tQTaskChildren = (struct QTaskNodeList_s *)((char *)p_tQTaskChildren + 68);
    --v3;
  }
  while ( v3 );
  ptQTask[1].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[1].tQTaskChildren.ptTail = nullptr;
  ptQTask[1].tQTaskRefList.ptHead = nullptr;
  ptQTask[2].ptNext = nullptr;
  *(_DWORD *)&ptQTask[1].eQTaskType = 0;
  LOBYTE(ptQTask[10].tQTaskRefList.ptMiddle) = 0;
  ptQTask[1].ptNext = (struct QTask_s *)1065353216;
  ptQTask[1].ptPrev = (struct QTask_s *)1065353216;
  ptQTask[1].tQTaskChildren.ptHead = (struct QTask_s *)1065353216;
  ptQTask[1].tQTaskRefList.ptMiddle = (struct QReference_s *)1065353216;
  ptQTask[1].tQTaskRefList.ptTail = (struct QReference_s *)1065353216;
  ptQTask[1].ptParent = (struct QTask_s *)1065353216;
}

// source: h/2/globallighttask.c:292  [anchor-mhash]
void __cdecl GlobalLightKeyframeQTask_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QReference_s **p_ptTail; // eax
  int v4; // ecx
  double v5; // st7
  struct QTask_s *ptParent; // eax
  unsigned __int16 eQTaskType; // cx
  struct QReference_s *ptTail; // ecx
  struct QTask_s *v9; // edx
  char *v10; // eax
  char *v11; // eax
  struct QTask_s *ptPrev; // eax
  char *v13; // eax
  struct QTask_s *v14; // eax
  char *v15; // eax
  struct QReference_s *ptHead; // eax
  char *v17; // eax
  int ptQTaska = *(int *)&ptQTask; // [esp+14h] [ebp+4h] ARGSLOT

  if ( LOBYTE(ptQTask[10].tQTaskRefList.ptMiddle) )
  {
    if ( ptQTask[5].tQTaskChildren.ptTail )
    {
      ptQTask[3].tQTaskRefList.ptTail = (struct QReference_s *)-1;
      ptQTask[5].tQTaskChildren.ptTail = nullptr;
      ptQTask[7].ptPrev = (struct QTask_s *)1;
      ptQTask[8].ptParent = (struct QTask_s *)2;
      ptQTask[10].tQTaskRefList.ptHead = (struct QReference_s *)3;
    }
    else
    {
      p_ptTail = &ptQTask[3].tQTaskRefList.ptTail;
      v4 = 5;
      do
      {
        *p_ptTail = (struct QReference_s *)-1;
        p_ptTail += 17;
        --v4;
      }
      while ( v4 );
    }
    LOBYTE(ptQTask[10].tQTaskRefList.ptMiddle) = 0;
  }
  if ( !GlobalLightQTask_ptActiveKeyframe )
    GlobalLightQTask_ptActiveKeyframe = (struct GlobalLightKeyframeQTask_t *)ptQTask;
  v5 = *(float *)&ptQTask[1].eQTaskType;
  ptParent = ptQTask->ptParent;
  ptQTask[2].ptNext = *(struct QTask_s **)&ptQTask[1].eQTaskType;
  GlobalLightQTask_vRequestedTime = v5;
  if ( ptParent )
  {
    eQTaskType = ptParent->eQTaskType;
    if ( eQTaskType == GlobalLightQTask_eQTaskType )
      ((void (__cdecl *)(struct QTask_s *, struct QTask_s *))QTask_aatQTaskFinalEvent[ParameterList_eUpdateInternalDataQTaskEvent][eQTaskType].pfHandler)(
        ptParent,
        ptQTask);
  }
  ptTail = ptQTask[3].tQTaskRefList.ptTail;
  v9 = ptQTask[5].tQTaskChildren.ptTail;
  ptQTaska = 5;
  do
  {
    if ( (unsigned int)ptTail <= 4 )
    {
      v10 = (char *)ptQTask + 68 * (_DWORD)ptTail;
      ptQTask[2].ptPrev = *((struct QTask_s **)v10 + 21);
      ptQTask[2].tQTaskChildren.ptHead = *((struct QTask_s **)v10 + 22);
      ptQTask[2].tQTaskChildren.ptMiddle = *((struct QTask_s **)v10 + 23);
      ptQTask[2].tQTaskChildren.ptTail = *((struct QTask_s **)v10 + 24);
      ptQTask[2].tQTaskRefList.ptHead = *((struct QReference_s **)v10 + 25);
      ptQTask[2].tQTaskRefList.ptMiddle = *((struct QReference_s **)v10 + 26);
      ptQTask[2].tQTaskRefList.ptTail = *((struct QReference_s **)v10 + 27);
    }
    if ( (unsigned int)v9 <= 4 )
    {
      v11 = (char *)ptQTask + 68 * (_DWORD)v9;
      ptQTask[3].ptParent = *((struct QTask_s **)v11 + 21);
      *(_DWORD *)&ptQTask[3].eQTaskType = *((_DWORD *)v11 + 22);
      ptQTask[4].ptNext = *((struct QTask_s **)v11 + 23);
      ptQTask[4].ptPrev = *((struct QTask_s **)v11 + 24);
      ptQTask[4].tQTaskChildren.ptHead = *((struct QTask_s **)v11 + 25);
      ptQTask[4].tQTaskChildren.ptMiddle = *((struct QTask_s **)v11 + 26);
      ptQTask[4].tQTaskChildren.ptTail = *((struct QTask_s **)v11 + 27);
    }
    ptPrev = ptQTask[7].ptPrev;
    if ( (unsigned int)ptPrev <= 4 )
    {
      v13 = (char *)ptQTask + 68 * (_DWORD)ptPrev;
      ptQTask[5].tQTaskRefList.ptHead = *((struct QReference_s **)v13 + 21);
      ptQTask[5].tQTaskRefList.ptMiddle = *((struct QReference_s **)v13 + 22);
      ptQTask[5].tQTaskRefList.ptTail = *((struct QReference_s **)v13 + 23);
      ptQTask[5].ptParent = *((struct QTask_s **)v13 + 24);
      *(_DWORD *)&ptQTask[5].eQTaskType = *((_DWORD *)v13 + 25);
      ptQTask[6].ptNext = *((struct QTask_s **)v13 + 26);
      ptQTask[6].ptPrev = *((struct QTask_s **)v13 + 27);
    }
    v14 = ptQTask[8].ptParent;
    if ( (unsigned int)v14 <= 4 )
    {
      v15 = (char *)ptQTask + 68 * (_DWORD)v14;
      ptQTask[7].tQTaskChildren.ptHead = *((struct QTask_s **)v15 + 21);
      ptQTask[7].tQTaskChildren.ptMiddle = *((struct QTask_s **)v15 + 22);
      ptQTask[7].tQTaskChildren.ptTail = *((struct QTask_s **)v15 + 23);
      ptQTask[7].tQTaskRefList.ptHead = *((struct QReference_s **)v15 + 24);
      ptQTask[7].tQTaskRefList.ptMiddle = *((struct QReference_s **)v15 + 25);
      ptQTask[7].tQTaskRefList.ptTail = *((struct QReference_s **)v15 + 26);
      ptQTask[7].ptParent = *((struct QTask_s **)v15 + 27);
    }
    ptHead = ptQTask[10].tQTaskRefList.ptHead;
    if ( (unsigned int)ptHead <= 4 )
    {
      v17 = (char *)ptQTask + 68 * (_DWORD)ptHead;
      *(_DWORD *)&ptQTask[8].eQTaskType = *((_DWORD *)v17 + 21);
      ptQTask[9].ptNext = *((struct QTask_s **)v17 + 22);
      ptQTask[9].ptPrev = *((struct QTask_s **)v17 + 23);
      ptQTask[9].tQTaskChildren.ptHead = *((struct QTask_s **)v17 + 24);
      ptQTask[9].tQTaskChildren.ptMiddle = *((struct QTask_s **)v17 + 25);
      ptQTask[9].tQTaskChildren.ptTail = *((struct QTask_s **)v17 + 26);
      ptQTask[9].tQTaskRefList.ptHead = *((struct QReference_s **)v17 + 27);
    }
    --ptQTaska;
  }
  while ( ptQTaska );
  if ( GlobalLightQTask_ptActiveKeyframe == (struct GlobalLightKeyframeQTask_t *)ptQTask )
    GlobalLightQTask_ptActiveKeyframe = nullptr;
}

// source: h/2/globallighttask.c:380  [size]
void __cdecl GlobalLightKeyframeQTask_GetParameterListHandler(
        struct QTask_s *ptQTask,
        void *pxContext)
{
  *(_DWORD *)pxContext = GlobalLightKeyframeQTask_ptParameterList;
}

// source: h/2/globallighttask.c:396  [size]
void __cdecl GlobalLightKeyframeQTask_DeleteHandler(struct QTask_s *ptQTask)
{
  ptQTask->ptParent[10].tQTaskRefList.ptMiddle = (struct QReference_s *)-8388609;
}

// source: h/2/globallighttask.c:453  [anchor-hash]
void __cdecl GlobalLightQTask_Update(struct GlobalLightQTask_t *ptGlobalLightQTask)
{
  unsigned __int16 v1; // dx
  struct QTask_s *v3; // esi
  float *v4; // ebx
  struct QTask_s *NextSiblingOfType; // edx
  struct real32x3_t *p_tObjectFogColor; // ecx
  float *v7; // eax
  _DWORD *p_vX; // esi
  float v9; // ecx
  float *v10; // ebx
  struct real32x3_t *v11; // edi
  double v12; // st7
  float v13; // eax
  float *p_ptMiddle; // esi
  struct real32x3_t *v15; // edi
  struct QTask_s *FirstChildOfType; // eax
  float v17; // ecx
  struct real32x3_t *p_tWaterColor; // edi
  float *p_vY; // eax
  int v20; // ecx
  int v21; // [esp+10h] [ebp-4h]

  v1 = GlobalLightKeyframeQTask_eQTaskType;
  ptGlobalLightQTask->ptWorld->isLightingTablesValid = 0;
  if ( QTask_GetFirstChildOfType(&ptGlobalLightQTask->tQTask, v1) )
  {
    if ( ptGlobalLightQTask->vMaxTime == ptGlobalLightQTask->vMinTime )
    {
      FirstChildOfType = QTask_GetFirstChildOfType(&ptGlobalLightQTask->tQTask, v1);
      LODWORD(ptGlobalLightQTask->atGlobalLightCategory[0].tObjectAmbientColor.vX) = FirstChildOfType[2].ptPrev;
      *(struct QTaskNodeList_s *)&ptGlobalLightQTask->atGlobalLightCategory[0].tObjectAmbientColor.vY = FirstChildOfType[2].tQTaskChildren;
      *(struct QReferenceList_s *)&ptGlobalLightQTask->atGlobalLightCategory[0].tObjectFogColor.vY = FirstChildOfType[2].tQTaskRefList;
      LODWORD(ptGlobalLightQTask->atGlobalLightCategory[1].tObjectAmbientColor.vX) = FirstChildOfType[3].ptParent;
      ptGlobalLightQTask->atGlobalLightCategory[1].tObjectAmbientColor.vY = *(float *)&FirstChildOfType[3].eQTaskType;
      LODWORD(ptGlobalLightQTask->atGlobalLightCategory[1].tObjectAmbientColor.vZ) = FirstChildOfType[4].ptNext;
      LODWORD(ptGlobalLightQTask->atGlobalLightCategory[1].tObjectFogColor.vX) = FirstChildOfType[4].ptPrev;
      *(struct QTaskNodeList_s *)&ptGlobalLightQTask->atGlobalLightCategory[1].tObjectFogColor.vY = FirstChildOfType[4].tQTaskChildren;
      ptGlobalLightQTask->atGlobalLightCategory[2].tObjectAmbientColor = (*(struct real32x3_t *)&FirstChildOfType[5].tQTaskRefList);
      LODWORD(ptGlobalLightQTask->atGlobalLightCategory[2].tObjectFogColor.vX) = FirstChildOfType[5].ptParent;
      ptGlobalLightQTask->atGlobalLightCategory[2].tObjectFogColor.vY = *(float *)&FirstChildOfType[5].eQTaskType;
      LODWORD(ptGlobalLightQTask->atGlobalLightCategory[2].tObjectFogColor.vZ) = FirstChildOfType[6].ptNext;
      LODWORD(ptGlobalLightQTask->atGlobalLightCategory[2].vObjectFogDensity) = FirstChildOfType[6].ptPrev;
      ptGlobalLightQTask->atGlobalLightCategory[3].tObjectAmbientColor = (*(struct real32x3_t *)&FirstChildOfType[7].tQTaskChildren);
      ptGlobalLightQTask->atGlobalLightCategory[3].tObjectFogColor = (*(struct real32x3_t *)&FirstChildOfType[7].tQTaskRefList);
      LODWORD(ptGlobalLightQTask->atGlobalLightCategory[3].vObjectFogDensity) = FirstChildOfType[7].ptParent;
      ptGlobalLightQTask->atGlobalLightCategory[4].tObjectAmbientColor.vX = *(float *)&FirstChildOfType[8].eQTaskType;
      LODWORD(ptGlobalLightQTask->atGlobalLightCategory[4].tObjectAmbientColor.vY) = FirstChildOfType[9].ptNext;
      LODWORD(ptGlobalLightQTask->atGlobalLightCategory[4].tObjectAmbientColor.vZ) = FirstChildOfType[9].ptPrev;
      ptGlobalLightQTask->atGlobalLightCategory[4].tObjectFogColor = (*(struct real32x3_t *)&FirstChildOfType[9].tQTaskChildren);
      LODWORD(ptGlobalLightQTask->atGlobalLightCategory[4].vObjectFogDensity) = FirstChildOfType[9].tQTaskRefList.ptHead;
      LODWORD(ptGlobalLightQTask->tSkyColor.vX) = FirstChildOfType[1].ptNext;
      LODWORD(ptGlobalLightQTask->tSkyColor.vY) = FirstChildOfType[1].ptPrev;
      *(struct QTaskNodeList_s *)&ptGlobalLightQTask->tSkyColor.vZ = FirstChildOfType[1].tQTaskChildren;
      v17 = *(float *)&FirstChildOfType[1].tQTaskRefList.ptHead;
      FirstChildOfType = (struct QTask_s *)((char *)FirstChildOfType + 64);
      ptGlobalLightQTask->tWaterAmbient.vZ = v17;
      p_tWaterColor = &ptGlobalLightQTask->tWaterColor;
      LODWORD(p_tWaterColor->vX) = FirstChildOfType->ptNext;
      LODWORD(p_tWaterColor->vY) = FirstChildOfType->ptPrev;
      LODWORD(p_tWaterColor->vZ) = FirstChildOfType->tQTaskChildren.ptHead;
    }
    else
    {
      v3 = nullptr;
      v4 = nullptr;
      NextSiblingOfType = QTask_GetFirstChildOfType(&ptGlobalLightQTask->tQTask, v1);
      if ( !NextSiblingOfType )
        goto LABEL_17;
      while ( *(float *)&NextSiblingOfType[2].ptNext != ptGlobalLightQTask->vCurrentTime )
      {
        if ( *(float *)&NextSiblingOfType[2].ptNext < (double)ptGlobalLightQTask->vCurrentTime
          && (!v3 || *(float *)&NextSiblingOfType[2].ptNext > (double)*(float *)&v3[2].ptNext) )
        {
          v3 = NextSiblingOfType;
        }
        if ( *(float *)&NextSiblingOfType[2].ptNext > (double)ptGlobalLightQTask->vCurrentTime
          && (!v4 || *(float *)&NextSiblingOfType[2].ptNext < (double)v4[20]) )
        {
          v4 = (float *)NextSiblingOfType;
        }
        NextSiblingOfType = QTask_GetNextSiblingOfType(NextSiblingOfType, GlobalLightKeyframeQTask_eQTaskType);
        if ( !NextSiblingOfType )
          goto LABEL_16;
      }
      v3 = NextSiblingOfType;
      v4 = (float *)NextSiblingOfType;
LABEL_16:
      if ( v3 )
      {
        if ( !v4 || v3 == (struct QTask_s *)v4 || *(float *)&v3[2].ptNext == v4[20] )
        {
          LODWORD(ptGlobalLightQTask->atGlobalLightCategory[0].tObjectAmbientColor.vX) = v3[2].ptPrev;
          LODWORD(ptGlobalLightQTask->atGlobalLightCategory[0].tObjectAmbientColor.vY) = v3[2].tQTaskChildren.ptHead;
          LODWORD(ptGlobalLightQTask->atGlobalLightCategory[0].tObjectAmbientColor.vZ) = v3[2].tQTaskChildren.ptMiddle;
          LODWORD(ptGlobalLightQTask->atGlobalLightCategory[0].tObjectFogColor.vX) = v3[2].tQTaskChildren.ptTail;
          LODWORD(ptGlobalLightQTask->atGlobalLightCategory[0].tObjectFogColor.vY) = v3[2].tQTaskRefList.ptHead;
          LODWORD(ptGlobalLightQTask->atGlobalLightCategory[0].tObjectFogColor.vZ) = v3[2].tQTaskRefList.ptMiddle;
          LODWORD(ptGlobalLightQTask->atGlobalLightCategory[0].vObjectFogDensity) = v3[2].tQTaskRefList.ptTail;
          LODWORD(ptGlobalLightQTask->atGlobalLightCategory[1].tObjectAmbientColor.vX) = v3[3].ptParent;
          ptGlobalLightQTask->atGlobalLightCategory[1].tObjectAmbientColor.vY = *(float *)&v3[3].eQTaskType;
          LODWORD(ptGlobalLightQTask->atGlobalLightCategory[1].tObjectAmbientColor.vZ) = v3[4].ptNext;
          LODWORD(ptGlobalLightQTask->atGlobalLightCategory[1].tObjectFogColor.vX) = v3[4].ptPrev;
          LODWORD(ptGlobalLightQTask->atGlobalLightCategory[1].tObjectFogColor.vY) = v3[4].tQTaskChildren.ptHead;
          LODWORD(ptGlobalLightQTask->atGlobalLightCategory[1].tObjectFogColor.vZ) = v3[4].tQTaskChildren.ptMiddle;
          LODWORD(ptGlobalLightQTask->atGlobalLightCategory[1].vObjectFogDensity) = v3[4].tQTaskChildren.ptTail;
          LODWORD(ptGlobalLightQTask->atGlobalLightCategory[2].tObjectAmbientColor.vX) = v3[5].tQTaskRefList.ptHead;
          LODWORD(ptGlobalLightQTask->atGlobalLightCategory[2].tObjectAmbientColor.vY) = v3[5].tQTaskRefList.ptMiddle;
          LODWORD(ptGlobalLightQTask->atGlobalLightCategory[2].tObjectAmbientColor.vZ) = v3[5].tQTaskRefList.ptTail;
          LODWORD(ptGlobalLightQTask->atGlobalLightCategory[2].tObjectFogColor.vX) = v3[5].ptParent;
          ptGlobalLightQTask->atGlobalLightCategory[2].tObjectFogColor.vY = *(float *)&v3[5].eQTaskType;
          LODWORD(ptGlobalLightQTask->atGlobalLightCategory[2].tObjectFogColor.vZ) = v3[6].ptNext;
          LODWORD(ptGlobalLightQTask->atGlobalLightCategory[2].vObjectFogDensity) = v3[6].ptPrev;
          LODWORD(ptGlobalLightQTask->atGlobalLightCategory[3].tObjectAmbientColor.vX) = v3[7].tQTaskChildren.ptHead;
          LODWORD(ptGlobalLightQTask->atGlobalLightCategory[3].tObjectAmbientColor.vY) = v3[7].tQTaskChildren.ptMiddle;
          LODWORD(ptGlobalLightQTask->atGlobalLightCategory[3].tObjectAmbientColor.vZ) = v3[7].tQTaskChildren.ptTail;
          LODWORD(ptGlobalLightQTask->atGlobalLightCategory[3].tObjectFogColor.vX) = v3[7].tQTaskRefList.ptHead;
          LODWORD(ptGlobalLightQTask->atGlobalLightCategory[3].tObjectFogColor.vY) = v3[7].tQTaskRefList.ptMiddle;
          LODWORD(ptGlobalLightQTask->atGlobalLightCategory[3].tObjectFogColor.vZ) = v3[7].tQTaskRefList.ptTail;
          LODWORD(ptGlobalLightQTask->atGlobalLightCategory[3].vObjectFogDensity) = v3[7].ptParent;
          ptGlobalLightQTask->atGlobalLightCategory[4].tObjectAmbientColor.vX = *(float *)&v3[8].eQTaskType;
          LODWORD(ptGlobalLightQTask->atGlobalLightCategory[4].tObjectAmbientColor.vY) = v3[9].ptNext;
          LODWORD(ptGlobalLightQTask->atGlobalLightCategory[4].tObjectAmbientColor.vZ) = v3[9].ptPrev;
          LODWORD(ptGlobalLightQTask->atGlobalLightCategory[4].tObjectFogColor.vX) = v3[9].tQTaskChildren.ptHead;
          LODWORD(ptGlobalLightQTask->atGlobalLightCategory[4].tObjectFogColor.vY) = v3[9].tQTaskChildren.ptMiddle;
          LODWORD(ptGlobalLightQTask->atGlobalLightCategory[4].tObjectFogColor.vZ) = v3[9].tQTaskChildren.ptTail;
          LODWORD(ptGlobalLightQTask->atGlobalLightCategory[4].vObjectFogDensity) = v3[9].tQTaskRefList.ptHead;
          LODWORD(ptGlobalLightQTask->tSkyColor.vX) = v3[1].ptNext;
          LODWORD(ptGlobalLightQTask->tSkyColor.vY) = v3[1].ptPrev;
          LODWORD(ptGlobalLightQTask->tSkyColor.vZ) = v3[1].tQTaskChildren.ptHead;
          LODWORD(ptGlobalLightQTask->tWaterAmbient.vX) = v3[1].tQTaskChildren.ptMiddle;
          LODWORD(ptGlobalLightQTask->tWaterAmbient.vY) = v3[1].tQTaskChildren.ptTail;
          v13 = *(float *)&v3[1].tQTaskRefList.ptHead;
          p_ptMiddle = (float *)&v3[1].tQTaskRefList.ptMiddle;
          ptGlobalLightQTask->tWaterAmbient.vZ = v13;
          v15 = &ptGlobalLightQTask->tWaterColor;
          v15->vX = *p_ptMiddle;
          v15->vY = p_ptMiddle[1];
          v15->vZ = p_ptMiddle[2];
        }
        else
        {
          v12 = (ptGlobalLightQTask->vCurrentTime - *(float *)&v3[2].ptNext) / (v4[20] - *(float *)&v3[2].ptNext);
          ptGlobalLightQTask->atGlobalLightCategory[0].tObjectAmbientColor.vX = (v4[21] - *(float *)&v3[2].ptPrev) * v12
                                                                              + *(float *)&v3[2].ptPrev;
          ptGlobalLightQTask->atGlobalLightCategory[0].tObjectAmbientColor.vY = (v4[22]
                                                                               - *(float *)&v3[2].tQTaskChildren.ptHead)
                                                                              * v12
                                                                              + *(float *)&v3[2].tQTaskChildren.ptHead;
          ptGlobalLightQTask->atGlobalLightCategory[0].tObjectAmbientColor.vZ = (v4[23]
                                                                               - *(float *)&v3[2].tQTaskChildren.ptMiddle)
                                                                              * v12
                                                                              + *(float *)&v3[2].tQTaskChildren.ptMiddle;
          ptGlobalLightQTask->atGlobalLightCategory[0].tObjectFogColor.vX = (v4[24]
                                                                           - *(float *)&v3[2].tQTaskChildren.ptTail)
                                                                          * v12
                                                                          + *(float *)&v3[2].tQTaskChildren.ptTail;
          ptGlobalLightQTask->atGlobalLightCategory[0].tObjectFogColor.vY = (v4[25]
                                                                           - *(float *)&v3[2].tQTaskRefList.ptHead)
                                                                          * v12
                                                                          + *(float *)&v3[2].tQTaskRefList.ptHead;
          ptGlobalLightQTask->atGlobalLightCategory[0].tObjectFogColor.vZ = (v4[26]
                                                                           - *(float *)&v3[2].tQTaskRefList.ptMiddle)
                                                                          * v12
                                                                          + *(float *)&v3[2].tQTaskRefList.ptMiddle;
          ptGlobalLightQTask->atGlobalLightCategory[0].vObjectFogDensity = (v4[27]
                                                                          - *(float *)&v3[2].tQTaskRefList.ptTail)
                                                                         * v12
                                                                         + *(float *)&v3[2].tQTaskRefList.ptTail;
          ptGlobalLightQTask->atGlobalLightCategory[1].tObjectAmbientColor.vX = (v4[38] - *(float *)&v3[3].ptParent)
                                                                              * v12
                                                                              + *(float *)&v3[3].ptParent;
          ptGlobalLightQTask->atGlobalLightCategory[1].tObjectAmbientColor.vY = (v4[39] - *(float *)&v3[3].eQTaskType)
                                                                              * v12
                                                                              + *(float *)&v3[3].eQTaskType;
          ptGlobalLightQTask->atGlobalLightCategory[1].tObjectAmbientColor.vZ = (v4[40] - *(float *)&v3[4].ptNext) * v12
                                                                              + *(float *)&v3[4].ptNext;
          ptGlobalLightQTask->atGlobalLightCategory[1].tObjectFogColor.vX = (v4[41] - *(float *)&v3[4].ptPrev) * v12
                                                                          + *(float *)&v3[4].ptPrev;
          ptGlobalLightQTask->atGlobalLightCategory[1].tObjectFogColor.vY = (v4[42]
                                                                           - *(float *)&v3[4].tQTaskChildren.ptHead)
                                                                          * v12
                                                                          + *(float *)&v3[4].tQTaskChildren.ptHead;
          ptGlobalLightQTask->atGlobalLightCategory[1].tObjectFogColor.vZ = (v4[43]
                                                                           - *(float *)&v3[4].tQTaskChildren.ptMiddle)
                                                                          * v12
                                                                          + *(float *)&v3[4].tQTaskChildren.ptMiddle;
          ptGlobalLightQTask->atGlobalLightCategory[1].vObjectFogDensity = (v4[44]
                                                                          - *(float *)&v3[4].tQTaskChildren.ptTail)
                                                                         * v12
                                                                         + *(float *)&v3[4].tQTaskChildren.ptTail;
          ptGlobalLightQTask->atGlobalLightCategory[2].tObjectAmbientColor.vX = (v4[55]
                                                                               - *(float *)&v3[5].tQTaskRefList.ptHead)
                                                                              * v12
                                                                              + *(float *)&v3[5].tQTaskRefList.ptHead;
          ptGlobalLightQTask->atGlobalLightCategory[2].tObjectAmbientColor.vY = (v4[56]
                                                                               - *(float *)&v3[5].tQTaskRefList.ptMiddle)
                                                                              * v12
                                                                              + *(float *)&v3[5].tQTaskRefList.ptMiddle;
          ptGlobalLightQTask->atGlobalLightCategory[2].tObjectAmbientColor.vZ = (v4[57]
                                                                               - *(float *)&v3[5].tQTaskRefList.ptTail)
                                                                              * v12
                                                                              + *(float *)&v3[5].tQTaskRefList.ptTail;
          ptGlobalLightQTask->atGlobalLightCategory[2].tObjectFogColor.vX = (v4[58] - *(float *)&v3[5].ptParent) * v12
                                                                          + *(float *)&v3[5].ptParent;
          ptGlobalLightQTask->atGlobalLightCategory[2].tObjectFogColor.vY = (v4[59] - *(float *)&v3[5].eQTaskType) * v12
                                                                          + *(float *)&v3[5].eQTaskType;
          ptGlobalLightQTask->atGlobalLightCategory[2].tObjectFogColor.vZ = (v4[60] - *(float *)&v3[6].ptNext) * v12
                                                                          + *(float *)&v3[6].ptNext;
          ptGlobalLightQTask->atGlobalLightCategory[2].vObjectFogDensity = (v4[61] - *(float *)&v3[6].ptPrev) * v12
                                                                         + *(float *)&v3[6].ptPrev;
          ptGlobalLightQTask->atGlobalLightCategory[3].tObjectAmbientColor.vX = (v4[72]
                                                                               - *(float *)&v3[7].tQTaskChildren.ptHead)
                                                                              * v12
                                                                              + *(float *)&v3[7].tQTaskChildren.ptHead;
          ptGlobalLightQTask->atGlobalLightCategory[3].tObjectAmbientColor.vY = (v4[73]
                                                                               - *(float *)&v3[7].tQTaskChildren.ptMiddle)
                                                                              * v12
                                                                              + *(float *)&v3[7].tQTaskChildren.ptMiddle;
          ptGlobalLightQTask->atGlobalLightCategory[3].tObjectAmbientColor.vZ = (v4[74]
                                                                               - *(float *)&v3[7].tQTaskChildren.ptTail)
                                                                              * v12
                                                                              + *(float *)&v3[7].tQTaskChildren.ptTail;
          ptGlobalLightQTask->atGlobalLightCategory[3].tObjectFogColor.vX = (v4[75]
                                                                           - *(float *)&v3[7].tQTaskRefList.ptHead)
                                                                          * v12
                                                                          + *(float *)&v3[7].tQTaskRefList.ptHead;
          ptGlobalLightQTask->atGlobalLightCategory[3].tObjectFogColor.vY = (v4[76]
                                                                           - *(float *)&v3[7].tQTaskRefList.ptMiddle)
                                                                          * v12
                                                                          + *(float *)&v3[7].tQTaskRefList.ptMiddle;
          ptGlobalLightQTask->atGlobalLightCategory[3].tObjectFogColor.vZ = (v4[77]
                                                                           - *(float *)&v3[7].tQTaskRefList.ptTail)
                                                                          * v12
                                                                          + *(float *)&v3[7].tQTaskRefList.ptTail;
          ptGlobalLightQTask->atGlobalLightCategory[3].vObjectFogDensity = (v4[78] - *(float *)&v3[7].ptParent) * v12
                                                                         + *(float *)&v3[7].ptParent;
          ptGlobalLightQTask->atGlobalLightCategory[4].tObjectAmbientColor.vX = (v4[89] - *(float *)&v3[8].eQTaskType)
                                                                              * v12
                                                                              + *(float *)&v3[8].eQTaskType;
          ptGlobalLightQTask->atGlobalLightCategory[4].tObjectAmbientColor.vY = (v4[90] - *(float *)&v3[9].ptNext) * v12
                                                                              + *(float *)&v3[9].ptNext;
          ptGlobalLightQTask->atGlobalLightCategory[4].tObjectAmbientColor.vZ = (v4[91] - *(float *)&v3[9].ptPrev) * v12
                                                                              + *(float *)&v3[9].ptPrev;
          ptGlobalLightQTask->atGlobalLightCategory[4].tObjectFogColor.vX = (v4[92]
                                                                           - *(float *)&v3[9].tQTaskChildren.ptHead)
                                                                          * v12
                                                                          + *(float *)&v3[9].tQTaskChildren.ptHead;
          ptGlobalLightQTask->atGlobalLightCategory[4].tObjectFogColor.vY = (v4[93]
                                                                           - *(float *)&v3[9].tQTaskChildren.ptMiddle)
                                                                          * v12
                                                                          + *(float *)&v3[9].tQTaskChildren.ptMiddle;
          ptGlobalLightQTask->atGlobalLightCategory[4].tObjectFogColor.vZ = (v4[94]
                                                                           - *(float *)&v3[9].tQTaskChildren.ptTail)
                                                                          * v12
                                                                          + *(float *)&v3[9].tQTaskChildren.ptTail;
          ptGlobalLightQTask->atGlobalLightCategory[4].vObjectFogDensity = (v4[95]
                                                                          - *(float *)&v3[9].tQTaskRefList.ptHead)
                                                                         * v12
                                                                         + *(float *)&v3[9].tQTaskRefList.ptHead;
          ptGlobalLightQTask->tSkyColor.vX = (v4[10] - *(float *)&v3[1].ptNext) * v12 + *(float *)&v3[1].ptNext;
          ptGlobalLightQTask->tSkyColor.vY = (v4[11] - *(float *)&v3[1].ptPrev) * v12 + *(float *)&v3[1].ptPrev;
          ptGlobalLightQTask->tSkyColor.vZ = (v4[12] - *(float *)&v3[1].tQTaskChildren.ptHead) * v12
                                           + *(float *)&v3[1].tQTaskChildren.ptHead;
          ptGlobalLightQTask->tWaterAmbient.vX = (v4[13] - *(float *)&v3[1].tQTaskChildren.ptMiddle) * v12
                                               + *(float *)&v3[1].tQTaskChildren.ptMiddle;
          ptGlobalLightQTask->tWaterAmbient.vY = (v4[14] - *(float *)&v3[1].tQTaskChildren.ptTail) * v12
                                               + *(float *)&v3[1].tQTaskChildren.ptTail;
          ptGlobalLightQTask->tWaterAmbient.vZ = (v4[15] - *(float *)&v3[1].tQTaskRefList.ptHead) * v12
                                               + *(float *)&v3[1].tQTaskRefList.ptHead;
          ptGlobalLightQTask->tWaterColor.vX = (v4[16] - *(float *)&v3[1].tQTaskRefList.ptMiddle) * v12
                                             + *(float *)&v3[1].tQTaskRefList.ptMiddle;
          ptGlobalLightQTask->tWaterColor.vY = (v4[17] - *(float *)&v3[1].tQTaskRefList.ptTail) * v12
                                             + *(float *)&v3[1].tQTaskRefList.ptTail;
          ptGlobalLightQTask->tWaterColor.vZ = (v4[18] - *(float *)&v3[1].ptParent) * v12 + *(float *)&v3[1].ptParent;
        }
      }
      else
      {
LABEL_17:
        p_tObjectFogColor = &ptGlobalLightQTask->atGlobalLightCategory[0].tObjectFogColor;
        v7 = v4 + 24;
        v21 = 5;
        do
        {
          p_vX = (_DWORD *)&p_tObjectFogColor[-1].vX;
          *p_vX = *((_DWORD *)v7 - 3);
          p_vX[1] = *((_DWORD *)v7 - 2);
          p_vX[2] = *((_DWORD *)v7 - 1);
          p_tObjectFogColor->vX = *v7;
          p_tObjectFogColor->vY = v7[1];
          p_tObjectFogColor->vZ = v7[2];
          p_tObjectFogColor[1].vY = v7[4];
          p_tObjectFogColor[1].vZ = v7[5];
          p_tObjectFogColor[2].vX = v7[6];
          p_tObjectFogColor[2].vY = v7[7];
          p_tObjectFogColor[2].vZ = v7[8];
          p_tObjectFogColor[3].vX = v7[9];
          p_tObjectFogColor[3].vY = v7[10];
          p_tObjectFogColor[3].vZ = v7[11];
          p_tObjectFogColor[4].vX = v7[12];
          p_tObjectFogColor[1].vX = v7[3];
          v7 += 17;
          p_tObjectFogColor = (struct real32x3_t *)((char *)p_tObjectFogColor + 64);
          --v21;
        }
        while ( v21 );
        ptGlobalLightQTask->tSkyColor.vX = v4[10];
        ptGlobalLightQTask->tSkyColor.vY = v4[11];
        ptGlobalLightQTask->tSkyColor.vZ = v4[12];
        ptGlobalLightQTask->tWaterAmbient.vX = v4[13];
        ptGlobalLightQTask->tWaterAmbient.vY = v4[14];
        v9 = v4[15];
        v10 = v4 + 16;
        ptGlobalLightQTask->tWaterAmbient.vZ = v9;
        v11 = &ptGlobalLightQTask->tWaterColor;
        v11->vX = *v10;
        v11->vY = v10[1];
        v11->vZ = v10[2];
      }
    }
  }
  else
  {
    p_vY = &ptGlobalLightQTask->atGlobalLightCategory[0].tObjectAmbientColor.vY;
    v20 = 5;
    do
    {
      *(p_vY - 1) = 0.0;
      *p_vY = 0.0;
      p_vY[1] = 0.0;
      p_vY[2] = 0.0;
      p_vY[3] = 0.0;
      p_vY[4] = 0.0;
      p_vY[5] = 0.0;
      p_vY += 16;
      --v20;
    }
    while ( v20 );
    ptGlobalLightQTask->tSkyColor.vX = 0.0;
    ptGlobalLightQTask->tSkyColor.vY = 0.0;
    ptGlobalLightQTask->tSkyColor.vZ = 0.0;
    ptGlobalLightQTask->tWaterAmbient.vX = 0.0;
    ptGlobalLightQTask->tWaterAmbient.vY = 0.0;
    ptGlobalLightQTask->tWaterAmbient.vZ = 0.0;
    ptGlobalLightQTask->tWaterColor.vX = 0.0;
    ptGlobalLightQTask->tWaterColor.vY = 0.0;
    ptGlobalLightQTask->tWaterColor.vZ = 0.0;
  }
}

// source: h/2/globallighttask.c:642  [anchor-caller]
void __cdecl GlobalLightQTask_DrawCallback(struct QCamera_s *ptQCamera)
{
  #pragma pack(push, 1)
  union
  {
    struct { float ptColor; };
    struct { char igi2_o1[16]; struct Ambientlight_t tAmbientlight; };
    struct { char igi2_o2[28]; _DWORD v12[3]; };
    char igi2_extent[40];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct GlobalLightQTask_t *v1; // esi
  struct GlobalLightQTask_t *v2; // eax
  float vX; // edx
  float vZ; // ecx
  double v5; // st7
  double v6; // st7
  float vY; // ebx
  void (__cdecl *v8)(void *); // eax
  struct World_s *ptWorld; // esi

  v1 = GlobalLightQTask_ptGlobalLight;
  if ( GlobalLightQTask_ptGlobalLight )
  {
    if ( *(float *)&ptQCamera->isFirstPerson != GlobalLightQTask_ptGlobalLight->vCurrentTime )
    {
      v2 = GlobalLightQTask_ptGlobalLight;
      GlobalLightQTask_ptGlobalLight->vCurrentTime = *(float *)&ptQCamera->isFirstPerson;
      GlobalLightQTask_Update(v2);
    }
    FlatSky_SetTime(*(float *)&ptQCamera->isFirstPerson);
    vX = v1->atGlobalLightCategory[0].tObjectAmbientColor.vX;
    igi2_frame.ptColor = v1->atGlobalLightCategory[0].vObjectFogDensity * 0.0005000000237487257;
    vZ = v1->atGlobalLightCategory[0].tObjectAmbientColor.vZ;
    DrawTerrainMesh_tAmbientColor.vY = v1->atGlobalLightCategory[0].tObjectAmbientColor.vY;
    DrawTerrainMesh_tAmbientColor.vX = vX;
    DrawTerrainMesh_tAmbientColor.vZ = vZ;
    DrawTerrainMesh_SetFog(&v1->atGlobalLightCategory[0].tObjectFogColor, igi2_frame.ptColor);
    Mesh3D_atAmbientColor[0] = v1->atGlobalLightCategory[0].tObjectAmbientColor;
    Mesh3D_atFogColor[0] = v1->atGlobalLightCategory[0].tObjectFogColor;
    Mesh3D_avFogDensity[0] = v1->atGlobalLightCategory[0].vObjectFogDensity * 0.0005000000237487257;
    Mesh3D_atAmbientColor[1] = v1->atGlobalLightCategory[1].tObjectAmbientColor;
    Mesh3D_atFogColor[1] = v1->atGlobalLightCategory[1].tObjectFogColor;
    Mesh3D_avFogDensity[1] = v1->atGlobalLightCategory[1].vObjectFogDensity * 0.0005000000237487257;
    Mesh3D_atAmbientColor[2] = v1->atGlobalLightCategory[2].tObjectAmbientColor;
    Mesh3D_atFogColor[2] = v1->atGlobalLightCategory[2].tObjectFogColor;
    Mesh3D_avFogDensity[2] = v1->atGlobalLightCategory[2].vObjectFogDensity * 0.0005000000237487257;
    Mesh3D_atAmbientColor[3] = v1->atGlobalLightCategory[3].tObjectAmbientColor;
    Mesh3D_atFogColor[3] = v1->atGlobalLightCategory[3].tObjectFogColor;
    v5 = v1->atGlobalLightCategory[3].vObjectFogDensity * 0.0005000000237487257;
    *(_QWORD *)&igi2_frame.tAmbientlight.tColor.vX = *(_QWORD *)&Mesh3D_atAmbientColor[1].vX;
    Mesh3D_avFogDensity[3] = v5;
    Mesh3D_atAmbientColor[4] = v1->atGlobalLightCategory[4].tObjectAmbientColor;
    Mesh3D_atFogColor[4] = v1->atGlobalLightCategory[4].tObjectFogColor;
    v6 = v1->atGlobalLightCategory[4].vObjectFogDensity * 0.0005000000237487257;
    igi2_frame.tAmbientlight.tColor.vZ = Mesh3D_atAmbientColor[1].vZ;
    Mesh3D_avFogDensity[4] = v6;
    Sky_tColor.vX = v1->tSkyColor.vX;
    vY = v1->tSkyColor.vY;
    Sky_tColor.vZ = v1->tSkyColor.vZ;
    Sky_tColor.vY = vY;
    if ( AppContext_tAppContext.isMainMenu == false )
    {
      igi2_frame.v12[1] = &igi2_frame.tAmbientlight;
      v8 = RenderMode_tActiveRenderMode.apfRenderModeMethod[Lightsource_eAddLightsourceRenderModeMethod];
      igi2_frame.v12[0] = 0x40000;
      igi2_frame.v12[2] = 0;
      if ( v8 )
        v8(igi2_frame.v12);
    }
    ptWorld = v1->ptWorld;
    if ( !ptWorld->isLightingTablesValid )
    {
      if ( ptWorld->ptCubeTree )
        ptWorld->isLightingTablesValid = 1;
    }
  }
}

// source: h/2/globallighttask.c:692  [anchor-strings]
void __cdecl GlobalLightQTask_Open()
{
  unsigned __int16 BaseQTaskType; // ax
  unsigned __int16 v1; // ax
  unsigned __int16 v2; // ax
  unsigned __int16 v3; // di
  unsigned __int16 v4; // si
  __int16 v5; // bx
  __int16 v6; // bp
  struct ParameterList_s *v7; // eax
  int v8; // edx
  struct ParameterList_s *v9; // eax
  int v10; // edx
  int i; // edi
  int v12; // eax
  char zCategory[36]; // [esp+18h] [ebp-24h] BYREF

  BaseQTaskType = QTask_GetBaseQTaskType();
  GlobalLightQTask_eQTaskType = QTask_NewQTaskType("GlobalLight", 460, BaseQTaskType, 0, 0);
  v1 = QTask_GetBaseQTaskType();
  v2 = QTask_NewQTaskType("GlobalLightKeyframe", 428, v1, 0, 0);
  v3 = GlobalLightQTask_eQTaskType;
  v4 = v2;
  GlobalLightKeyframeQTask_eQTaskType = v2;
  QTask_LinkQTaskEventHandlerFn(GlobalLightQTask_eQTaskType, 0, GlobalLightQTask_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v3, 1, (void (__cdecl *)(struct QTask_s *))GlobalLightQTask_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v3, 2, (void (__cdecl *)(struct QTask_s *))GlobalLightQTask_DeleteHandler);
  v5 = ParameterList_eGetParameterListQTaskEvent;
  QTask_LinkQTaskEventHandlerFn(
    v3,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))GlobalLightQTask_GetParameterListHandler);
  v6 = ParameterList_eUpdateInternalDataQTaskEvent;
  QTask_LinkQTaskEventHandlerFn(
    v3,
    ParameterList_eUpdateInternalDataQTaskEvent,
    GlobalLightQTask_UpdateInternalDataHandler);
  QTask_LinkQTaskEventHandlerFn(v4, 0, GlobalLightKeyframeQTask_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(
    v4,
    2,
    (void (__cdecl *)(struct QTask_s *))GlobalLightKeyframeQTask_DeleteHandler);
  QTask_LinkQTaskEventHandlerFn(
    v4,
    v5,
    (void (__cdecl *)(struct QTask_s *, void *))GlobalLightKeyframeQTask_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(v4, v6, GlobalLightKeyframeQTask_UpdateInternalDataHandler);
  v7 = (struct ParameterList_s *)Mem_AllocFn(212, 4);
  v8 = Level_eParameterTypeReal32;
  v7->ptParameterListItem = (struct ParameterListItem_s *)&v7[1];
  v7->nParameters = 0;
  v7->nMaxParameters = 10;
  GlobalLightQTask_ptParameterList = v7;
  ParameterList_AddParameter(v7, 0x50u, v8, "Radiosity intensity ", 7u, nullptr);
  ParameterList_AddParameter(
    GlobalLightQTask_ptParameterList,
    0x54u,
    Level_eParameterTypeReal32,
    "Radiosity gamma",
    7u,
    nullptr);
  ParameterList_AddParameter(
    GlobalLightQTask_ptParameterList,
    0x58u,
    Level_eParameterTypeReal32,
    "Radiosity fadeout",
    7u,
    nullptr);
  ParameterList_AddParameterMinMax(
    GlobalLightQTask_ptParameterList,
    0x5Cu,
    Level_eParameterTypeReal32,
    "Radiosity dirlight softness",
    7u,
    0.019999999552965164,
    0.30000001192092896);
  ParameterList_AddParameter(
    GlobalLightQTask_ptParameterList,
    0x1C8u,
    Level_eParameterTypebool8,
    "Radiosity terrain shadows",
    7u,
    nullptr);
  ParameterList_AddParameter(
    GlobalLightQTask_ptParameterList,
    0x1ACu,
    Level_eParameterTypeRGB,
    "Texture filter ambient colour",
    7u,
    nullptr);
  ParameterList_AddParameter(
    GlobalLightQTask_ptParameterList,
    0x1B8u,
    Level_eParameterTypeRGB,
    "Texture filter scale",
    7u,
    nullptr);
  ParameterList_AddParameter(
    GlobalLightQTask_ptParameterList,
    0x1C4u,
    Level_eParameterTypeReal32,
    "Texture filter gamma",
    7u,
    &GlobalLightQTask_tGammaContext);
  ParameterList_AddParameter(
    GlobalLightQTask_ptParameterList,
    0x1CAu,
    Level_eParameterTypePushButton,
    "Update textures",
    6u,
    nullptr);
  ParameterList_AddParameter(
    GlobalLightQTask_ptParameterList,
    0x1C9u,
    Level_eParameterTypePushButton,
    "Reset texture filter",
    6u,
    nullptr);
  v9 = (struct ParameterList_s *)Mem_AllocFn(812, 4);
  v10 = Level_eParameterTypePushButton;
  v9->ptParameterListItem = (struct ParameterListItem_s *)&v9[1];
  v9->nParameters = 0;
  v9->nMaxParameters = 40;
  GlobalLightKeyframeQTask_ptParameterList = v9;
  ParameterList_AddParameter(v9, 0x1A8u, v10, "Link All Sliders", 7u, nullptr);
  for ( i = 0; i < 5; ++i )
  {
    if ( i )
      sprintf(zCategory, "object category %d", i);
    else
      strcpy(zCategory, "terrain");
    sprintf(&byte_7BDCF00[32 * i], "Ambient color %s", zCategory);
    sprintf(&byte_7BDCFA0[32 * i], "Fog color %s", zCategory);
    sprintf(&byte_7BDCDB8[32 * i], "Fog density %s", zCategory);
    sprintf(&byte_7BDCE58[32 * i], "Scale R %s", zCategory);
    sprintf(&byte_7BDD0E0[32 * i], "Scale G %s", zCategory);
    sprintf(&byte_7BDD040[32 * i], "Scale B %s", zCategory);
    sprintf(&byte_7BDD188[32 * i], "Link setting %s", zCategory);
    ParameterList_AddParameter(
      GlobalLightKeyframeQTask_ptParameterList,
      68 * i + 84,
      Level_eParameterTypeRGB,
      &byte_7BDCF00[32 * i],
      7u,
      nullptr);
    ParameterList_AddParameter(
      GlobalLightKeyframeQTask_ptParameterList,
      68 * i + 96,
      Level_eParameterTypeRGB,
      &byte_7BDCFA0[32 * i],
      7u,
      nullptr);
    ParameterList_AddParameter(
      GlobalLightKeyframeQTask_ptParameterList,
      68 * i + 108,
      Level_eParameterTypeReal32,
      &byte_7BDCDB8[32 * i],
      7u,
      nullptr);
    ParameterList_AddParameter(
      GlobalLightKeyframeQTask_ptParameterList,
      68 * i + 148,
      Level_eParameterTypeInt32,
      &byte_7BDD188[32 * i],
      7u,
      nullptr);
  }
  ParameterList_AddParameter(
    GlobalLightKeyframeQTask_ptParameterList,
    0x28u,
    Level_eParameterTypeRGB,
    "Sky color",
    7u,
    nullptr);
  ParameterList_AddParameter(
    GlobalLightKeyframeQTask_ptParameterList,
    0x34u,
    Level_eParameterTypeRGB,
    "Water ambient",
    7u,
    nullptr);
  ParameterList_AddParameter(
    GlobalLightKeyframeQTask_ptParameterList,
    0x40u,
    Level_eParameterTypeRGB,
    "Water color",
    7u,
    nullptr);
  ParameterList_AddParameter(
    GlobalLightKeyframeQTask_ptParameterList,
    0x4Cu,
    Level_eParameterTypeReal32,
    "Time",
    7u,
    nullptr);
  v12 = 0;
  while ( ViewportQTask_apfDrawCallback[v12] )
  {
    if ( ++v12 >= 15 )
      return;
  }
  ViewportQTask_apfDrawCallback[v12] = GlobalLightQTask_DrawCallback;
}

// source: h/2/globallighttask.c:797  [size]
void __cdecl GlobalLightQTask_Close()
{
  int v0; // esi
  int v1; // esi

  if ( GlobalLightKeyframeQTask_ptParameterList )
  {
    v0 = *(_DWORD *)((unsigned int)&GlobalLightKeyframeQTask_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
  if ( GlobalLightQTask_ptParameterList )
  {
    v1 = *(_DWORD *)((unsigned int)&GlobalLightQTask_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v1);
    memset(*(void **)(v1 + 8), 0xCDu, *(_DWORD *)(v1 + 16));
    free((void *)v1);
  }
  QTask_DeleteQTaskType(GlobalLightKeyframeQTask_eQTaskType);
  QTask_DeleteQTaskType(GlobalLightQTask_eQTaskType);
}

// source: h/2/globallighttask.c:816  [size]
unsigned __int16 __cdecl GlobalLightQTask_GetQTaskType()
{
  return GlobalLightQTask_eQTaskType;
}

// source: h/2/globallighttask.c:829  [size]
unsigned __int16 __cdecl GlobalLightKeyframeQTask_GetQTaskType()
{
  return GlobalLightKeyframeQTask_eQTaskType;
}

// source: h/2/globallighttask.c:842  [anchor-mhash]
void __cdecl GlobalLightQTask_SetTime(float vTime)
{
  struct GlobalLightQTask_t *v1; // ecx

  v1 = GlobalLightQTask_ptGlobalLight;
  if ( GlobalLightQTask_ptGlobalLight )
  {
    if ( vTime != GlobalLightQTask_ptGlobalLight->vCurrentTime )
    {
      GlobalLightQTask_ptGlobalLight->vCurrentTime = vTime;
      GlobalLightQTask_Update(v1);
    }
  }
}

// source: h/2/globallighttask.c:863  [size]
struct GlobalLightQTask_t *__cdecl GlobalLightQTask_GetGlobalLight()
{
  return GlobalLightQTask_ptGlobalLight;
}

// source: h/2/globallighttask.c:876  [size]
float *__cdecl GlobalLightQTask_GetRequestedTime()
{
  return GlobalLightQTask_pvRequestedTime;
}
