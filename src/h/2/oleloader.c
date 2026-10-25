/* h/2/oleloader.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: h/2/oleloader.c:55  [anchor-callee]
void __cdecl OLELoader_DeleteHeightmapsAndLightmaps(struct QTask_s *ptQTask)
{
  unsigned __int16 eQTaskType; // si
  struct QTask_s *ptHead; // eax
  struct QTask_s *v3; // esi

  eQTaskType = ptQTask->eQTaskType;
  if ( QTask_IsQTaskTypeDerived(eQTaskType, HeightMap_eQTaskType)
    || QTask_IsQTaskTypeDerived(eQTaskType, TextureModifier_eQTaskType) )
  {
    QTask_Delete(ptQTask);
  }
  else
  {
    ptHead = ptQTask->tQTaskChildren.ptHead;
    if ( ptHead->ptNext && ptHead )
    {
      do
      {
        if ( ptHead->ptNext )
          v3 = ptHead->ptNext->ptNext != nullptr ? ptHead->ptNext : nullptr;
        else
          v3 = nullptr;
        OLELoader_DeleteHeightmapsAndLightmaps(ptHead);
        ptHead = v3;
      }
      while ( v3 );
    }
  }
}

// source: h/2/oleloader.c:88  [anchor-caller]
struct OLELoader_s *__cdecl OLELoader_LoadTerrain(struct OLELoader_s *ptOLELoader)
{
  #pragma pack(push, 1)
  union
  {
    struct { char v11; };
    struct { char igi2_o1[1]; char zTempname[256]; };
    struct { char igi2_o2[257]; char zFilename[256]; };
    char igi2_extent[513];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  char *zTerrain; // esi
  char *v2; // eax
  char v3; // cl
  int v4; // eax
  char v5; // cl
  char *v6; // edi
  int *p_nFrame; // eax
  int v9; // ecx
  struct OLELoader_s *result; // eax

  zTerrain = ptOLELoader->zTerrain;
  v2 = ptOLELoader->zTerrain;
  do
  {
    v3 = *v2;
    v2[igi2_frame.zFilename - zTerrain] = *v2;
    ++v2;
  }
  while ( v3 );
  v4 = 0;
  do
  {
    v5 = igi2_frame.zFilename[v4];
    igi2_frame.zTempname[v4++] = v5;
  }
  while ( v5 );
  v6 = &igi2_frame.v11;
  while ( *++v6 )
    ;
  strcpy(v6, ".tex");
  if ( Resource_IsLoadedInternal(igi2_frame.zTempname, nullptr) || File_Exists(igi2_frame.zTempname) )
  {
    p_nFrame = &QCube_atCubeHash[0].nFrame;
    v9 = 2048;
    do
    {
      *p_nFrame = -1;
      p_nFrame += 7;
      --v9;
    }
    while ( v9 );
    World_LoadTerrainTextureData(World_ptActiveWorld, igi2_frame.zFilename);
    World_LoadTerrain(World_ptActiveWorld, igi2_frame.zFilename);
  }
  else
  {
    strcpy(zTerrain, "file not found");
    result = (struct OLELoader_s *)unk_6842A0;
    LOBYTE(result) = unk_6842AA;
  }
  return result;
}

// source: h/2/oleloader.c:123  [anchor-caller]
void __cdecl OLELoader_UnloadTerrain(struct OLELoader_s *ptOLELoader)
{
  struct OLELoader_s *i; // eax
  int *p_nFrame; // eax
  int v3; // ecx

  for ( i = (struct OLELoader_s *)ptOLELoader->tQTask.ptParent; i; i = (struct OLELoader_s *)i->tQTask.ptParent )
    ptOLELoader = i;
  OLELoader_DeleteHeightmapsAndLightmaps(&ptOLELoader->tQTask);
  if ( World_ptActiveWorld->ptCubeTree )
  {
    World_UnloadTerrain(World_ptActiveWorld);
    p_nFrame = &QCube_atCubeHash[0].nFrame;
    v3 = 2048;
    do
    {
      *p_nFrame = -1;
      p_nFrame += 7;
      --v3;
    }
    while ( v3 );
  }
}

// source: h/2/oleloader.c:149  [size]
void __cdecl OLELoader_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  LOBYTE(ptQTask[1].ptNext) = 0;
  ptQTask[7].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[7].tQTaskRefList.ptTail = nullptr;
  ptQTask[7].tQTaskRefList.ptHead = (struct QReference_s *)1;
  ptQTask[7].tQTaskChildren.ptTail = (struct QTask_s *)1;
}

// source: h/2/oleloader.c:169  [anchor-caller]
void __cdecl OLELoader_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  OLELoader_UnloadTerrain((struct OLELoader_s *)ptQTask);
  OLELoader_LoadTerrain((struct OLELoader_s *)ptQTask);
}

// source: h/2/oleloader.c:209  [size]
void __cdecl OLELoader_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = OLELoader_ptParameterList;
}

// source: h/2/oleloader.c:225  [size]
void __cdecl OLELoader_DeleteHandler(struct QTask_s *ptQTask)
{
  OLELoader_UnloadTerrain((struct OLELoader_s *)ptQTask);
}

// source: h/2/oleloader.c:243  [anchor-hash]
void __cdecl OLELoader_Open()
{
  unsigned __int16 BaseQTaskType; // ax
  unsigned __int16 v1; // si
  struct ParameterList_s *v2; // eax
  int v3; // edx

  BaseQTaskType = QTask_GetBaseQTaskType();
  v1 = QTask_NewQTaskType("OLELoader", 312, BaseQTaskType, 0, 0);
  OLELoader_eQTaskType = v1;
  QTask_LinkQTaskEventHandlerFn(v1, 0, (void (__cdecl *)(struct QTask_s *, void *))OLELoader_CreateHandler);
  QTask_LinkQTaskEventHandlerFn(v1, ParameterList_eUpdateInternalDataQTaskEvent, OLELoader_UpdateInternalDataHandler);
  QTask_LinkQTaskEventHandlerFn(
    v1,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))OLELoader_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 2, OLELoader_DeleteHandler);
  QTask_LinkQTaskEventHandlerFn(
    v1,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveHandler);
  v2 = (struct ParameterList_s *)Mem_AllocFn(92, 4);
  v3 = Level_eParameterTypeString256;
  v2->ptParameterListItem = (struct ParameterListItem_s *)&v2[1];
  v2->nParameters = 0;
  v2->nMaxParameters = 4;
  OLELoader_ptParameterList = v2;
  ParameterList_AddParameter(v2, 0x28u, v3, "Terrain filename", 7u, nullptr);
  ParameterList_AddParameter(OLELoader_ptParameterList, 0x128u, Level_eParameterTypebool8, "AutoLoad", 7u, nullptr);
  ParameterList_AddParameter(OLELoader_ptParameterList, 0x130u, Level_eParameterTypePushButton, "Load", 6u, nullptr);
  ParameterList_AddParameter(OLELoader_ptParameterList, 0x134u, Level_eParameterTypePushButton, "Unload", 6u, nullptr);
}

// source: h/2/oleloader.c:273  [size]
void __cdecl OLELoader_Close()
{
  int v0; // esi

  if ( OLELoader_ptParameterList )
  {
    v0 = *(_DWORD *)((unsigned int)&OLELoader_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
  QTask_DeleteQTaskType(OLELoader_eQTaskType);
}
