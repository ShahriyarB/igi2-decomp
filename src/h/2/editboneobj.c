/* h/2/editboneobj.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: h/2/editboneobj.c:96  [anchor-callee]
void __cdecl EditBoneObj_UpdateAnimation(struct EditBoneObj_s *ptEditBoneObj)
{
  struct AnimBlender_t *ptAnimBlender; // esi
  struct AnimController_t *v2; // eax
  double v3; // st7
  struct AnimController_t *v4; // edi
  size_t v5; // esi
  char zAnimName[256]; // [esp+18h] [ebp-100h] BYREF

  if ( ptEditBoneObj->pzCurrentAnimation )
  {
    ptAnimBlender = ptEditBoneObj->ptAnimBlender;
    if ( ptAnimBlender )
    {
      v2 = ptEditBoneObj->aptAnimController[0];
      v3 = ptEditBoneObj->vTransitionTime * 4800.0;
      ptEditBoneObj->aptAnimController[0] = ptEditBoneObj->aptAnimController[1];
      v4 = ptEditBoneObj->aptAnimController[0];
      ptEditBoneObj->ptAnimController = v2;
      ptEditBoneObj->aptAnimController[1] = v2;
      AnimBlender_Blend(ptAnimBlender, &v4->tBase, &v2->tBase, (__int64)v3);
    }
    v5 = strcspn(ptEditBoneObj->pzCurrentAnimation, ", \t\n");
    if ( v5 >= 0x100 )
      v5 = 255;
    strncpy(zAnimName, ptEditBoneObj->pzCurrentAnimation, v5);
    zAnimName[v5] = 0;
    EditBoneObj_SetAnimation(ptEditBoneObj, zAnimName);
  }
}

// source: h/2/editboneobj.c:140  [anchor-mhash]
void __cdecl EditBoneObj_UpdateAttachmentHandler(struct QTask_s *ptQTask)
{
  ModelObj_UpdateAttachment((struct ModelObj_s *)ptQTask);
  qmemcpy(&ptQTask[10].tQTaskRefList.ptMiddle, &ptQTask[3].ptPrev, sizeof(struct QTask_s));
  qmemcpy(&ptQTask[10], &ptQTask[1], 0x18u);
  ModelObj_UpdateAttachments((struct ModelObj_s *)ptQTask);
}

// source: h/2/editboneobj.c:170  [anchor-mhash]
void __cdecl EditBoneObj_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  double v3; // st6
  double v4; // st5
  unsigned int v5; // edx
  struct World_s *v6; // eax
  double v7; // st3
  __int16 v8; // cx
  float ptDynCubeObj; // [esp+0h] [ebp-18h]

  BoneDynCubeObj_Init((struct BoneDynCubeObj_s *)ptQTask, World_ptActiveWorld);
  ptQTask[10].tQTaskRefList.ptMiddle = (struct QReference_s *)1065353216;
  ptQTask[11].ptNext = (struct QTask_s *)1065353216;
  ptQTask[11].tQTaskChildren.ptTail = (struct QTask_s *)1065353216;
  ptQTask[13].tQTaskChildren.ptMiddle = (struct QTask_s *)1065353216;
  ptQTask[10].tQTaskRefList.ptTail = nullptr;
  ptQTask[10].ptParent = nullptr;
  *(_DWORD *)&ptQTask[10].eQTaskType = 0;
  ptQTask[11].ptPrev = nullptr;
  ptQTask[11].tQTaskChildren.ptHead = nullptr;
  ptQTask[11].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[11].tQTaskRefList.ptHead = nullptr;
  ptQTask[10].ptNext = nullptr;
  ptQTask[10].ptPrev = nullptr;
  ptQTask[10].tQTaskChildren.ptHead = nullptr;
  ptQTask[10].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[10].tQTaskChildren.ptTail = nullptr;
  ptQTask[10].tQTaskRefList.ptHead = nullptr;
  ptQTask[13].ptPrev = nullptr;
  ptQTask[13].tQTaskChildren.ptHead = nullptr;
  BYTE1(ptQTask[12].ptParent) = 0;
  ptQTask[13].ptNext = nullptr;
  LOBYTE(ptQTask[11].tQTaskRefList.ptMiddle) = 0;
  ptQTask[12].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[12].tQTaskChildren.ptTail = nullptr;
  ptQTask[12].tQTaskRefList.ptHead = nullptr;
  ptQTask[12].tQTaskRefList.ptTail = nullptr;
  BYTE2(ptQTask[12].ptParent) = 1;
  EditBoneObj_tBlinkRandomState.anRandom[2] ^= EditBoneObj_tBlinkRandomState.anRandom[0] >> 7;
  EditBoneObj_tBlinkRandomState.anRandom[1] ^= EditBoneObj_tBlinkRandomState.anRandom[2];
  EditBoneObj_tBlinkRandomState.anRandom[0] += EditBoneObj_tBlinkRandomState.anRandom[1];
  v3 = *(float *)&ptQTask[7].tQTaskRefList.ptHead;
  v4 = *(float *)&ptQTask[7].tQTaskChildren.ptTail;
  v5 = EditBoneObj_tBlinkRandomState.anRandom[0] % 0x96;
  v6 = World_ptActiveWorld;
  v7 = *(float *)&ptQTask[7].tQTaskRefList.ptMiddle * *(float *)&ptQTask[7].tQTaskRefList.ptMiddle;
  LOBYTE(ptQTask[12].ptParent) = 1;
  ptQTask[13].tQTaskChildren.ptTail = nullptr;
  LOBYTE(ptQTask[12].ptNext) = 0;
  *(_DWORD *)&ptQTask[12].eQTaskType = v5;
  ptDynCubeObj = sqrt(v4 * v4 + v3 * v3 + v7) + *(float *)&ptQTask[8].ptNext;
  World_RegisterDynCubeObjFirstTimeRadius(
    v6,
    (struct DynCubeObj_s *)ptQTask,
    (struct real64x3_t *)&ptQTask[10],
    ptDynCubeObj,
    WORLD_DYNCUBETREE_CATEGORY_MOBILE);
  v8 = Attach_eAttachEvent;
  ptQTask[5].tQTaskChildren.ptTail = (struct QTask_s *)-1;
  ptQTask[5].tQTaskRefList.ptHead = nullptr;
  QTask_TriggerQTaskEventParent(ptQTask, v8, &ptQTask[5].tQTaskChildren.ptTail);
  ModelObj_CalcRelativePosAndOrientation((struct ModelObj_s *)ptQTask);
}

// source: h/2/editboneobj.c:217  [anchor-mhash]
void __cdecl EditBoneObj_DeleteHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptPrev; // eax
  int v2; // ebx
  struct QTask_s *ptTail; // eax
  int v4; // ebx

  BoneDynCubeObj_SetLODVirModel((struct BoneDynCubeObj_s *)ptQTask, nullptr);
  World_RemoveDynCubeObj((struct World_s *)ptQTask[2].ptParent, (struct DynCubeObj_s *)ptQTask);
  ptPrev = ptQTask[13].ptPrev;
  if ( ptPrev )
  {
    --Mem_nCurrentAllocations;
    v2 = *(_DWORD *)((unsigned int)&ptPrev[-1].eQTaskType & 0xFFFFFFFC);
    Node_Remove((_DWORD **)v2);
    memset(*(void **)(v2 + 8), 0xCDu, *(_DWORD *)(v2 + 16));
    free((void *)v2);
  }
  ptTail = ptQTask[13].tQTaskChildren.ptTail;
  ptQTask[13].ptPrev = nullptr;
  if ( ptTail )
  {
    v4 = *(_DWORD *)((unsigned int)&ptTail[-1].eQTaskType & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v4);
    memset(*(void **)(v4 + 8), 0xCDu, *(_DWORD *)(v4 + 16));
    free((void *)v4);
  }
  ptQTask[13].tQTaskChildren.ptTail = nullptr;
}

// source: h/2/editboneobj.c:256  [anchor-caller]
void __cdecl EditBoneObj_RunHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptHead; // ecx
  int v2; // edx
  struct QTask_s *v3; // eax
  void (__cdecl *pfHandler)(struct QTask_s *); // eax
  int v5; // edx
  struct QReference_s *ptMiddle; // eax
  struct QTask_s *v7; // eax
  char *v8; // eax
  struct QTask_s *v9; // eax
  int v10; // eax
  unsigned int v11; // eax

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
      QTask_atProtectedQTaskStack[v2].ptQTask = v3;
      pfHandler = (void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[1][ptHead->eQTaskType].pfHandler;
      v5 = v2 + 1;
      QTask_nProtectedQTaskStackOffset = v5;
      if ( pfHandler )
      {
        pfHandler(ptHead);
        v5 = QTask_nProtectedQTaskStackOffset;
      }
      ptHead = (struct QTask_s *)dword_849C7DC[v5];
      v2 = v5 - 1;
      QTask_nProtectedQTaskStackOffset = v2;
    }
    while ( ptHead );
  }
  ptMiddle = ptQTask[12].tQTaskRefList.ptMiddle;
  if ( ptMiddle )
  {
    if ( ((int)ptMiddle[3].pxObject & 4) != 0 )
    {
      v7 = ptQTask[13].tQTaskChildren.ptHead;
      if ( v7 )
      {
        v8 = strpbrk((char *)v7, ", \t\n");
        ptQTask[13].tQTaskChildren.ptHead = (struct QTask_s *)v8;
        if ( v8 )
        {
          v9 = (struct QTask_s *)((char *)ptQTask[13].tQTaskChildren.ptHead + strspn(v8, ", \t\n"));
          ptQTask[13].tQTaskChildren.ptHead = v9;
          if ( !LOBYTE(v9->ptNext) )
            ptQTask[13].tQTaskChildren.ptHead = nullptr;
        }
        if ( !ptQTask[13].tQTaskChildren.ptHead && BYTE1(ptQTask[12].ptParent) )
          ptQTask[13].tQTaskChildren.ptHead = ptQTask[13].ptPrev;
        EditBoneObj_UpdateAnimation((struct EditBoneObj_s *)ptQTask);
      }
    }
  }
  if ( LOBYTE(ptQTask[12].ptParent) )
  {
    v10 = *(_DWORD *)&ptQTask[12].eQTaskType - 1;
    *(_DWORD *)&ptQTask[12].eQTaskType = v10;
    if ( v10 < 0 )
    {
      v11 = -v10;
      if ( v11 >= 4 )
      {
        ptQTask[8].tQTaskChildren.ptHead = nullptr;
        EditBoneObj_tBlinkRandomState.anRandom[1] ^= (EditBoneObj_tBlinkRandomState.anRandom[0] >> 7)
                                                   ^ EditBoneObj_tBlinkRandomState.anRandom[2];
        EditBoneObj_tBlinkRandomState.anRandom[2] ^= EditBoneObj_tBlinkRandomState.anRandom[0] >> 7;
        EditBoneObj_tBlinkRandomState.anRandom[0] += EditBoneObj_tBlinkRandomState.anRandom[1];
        *(_DWORD *)&ptQTask[12].eQTaskType = EditBoneObj_tBlinkRandomState.anRandom[0] % 0x96;
      }
      else
      {
        ptQTask[8].tQTaskChildren.ptHead = (struct QTask_s *)dword_6B0734[v11];
      }
    }
  }
}

// source: h/2/editboneobj.c:317  [anchor-caller]
void __cdecl EditBoneObj_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { float ptDynCubeObj; };
    struct { char igi2_o1[20]; struct QTask_s *v21; };
    struct { char igi2_o2[24]; struct QReference_s *v22; };
    char igi2_extent[32];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *ptTail; // eax
  struct LODVirModel_s *LODVirModelExistsFn; // eax
  struct Model_s *ptModel; // ecx
  struct Mesh3D_Mesh_t *ptMesh; // ecx
  struct LODVirModel_s *v6; // esi
  struct QReference_s *v7; // eax
  char v8; // cl
  bool v9; // zf
  unsigned int pxObject; // ecx
  unsigned int v11; // ecx
  double v12; // st7
  struct QReference_s *v13; // eax
  char v14; // cl
  unsigned int v15; // ecx
  unsigned int v16; // ecx
  struct AnimControllerBase_t *v17; // ecx
  struct QReference_s *ptMiddle; // ebx
  __int16 v19; // cx

  ptTail = ptQTask[12].tQTaskChildren.ptTail;
  qmemcpy(&ptQTask[3].ptPrev, &ptQTask[10].tQTaskRefList.ptMiddle, sizeof(struct QTask_s));
  if ( ptTail )
  {
    if ( ptTail != (struct QTask_s *)ptQTask[12].tQTaskRefList.ptHead )
      QTask_Delete((struct QTask_s *)ptQTask[12].tQTaskRefList.ptHead);
    QTask_Delete(ptQTask[12].tQTaskChildren.ptTail);
    ptQTask[12].tQTaskRefList.ptMiddle = nullptr;
    ptQTask[12].tQTaskChildren.ptTail = nullptr;
    ptQTask[12].tQTaskRefList.ptHead = nullptr;
  }
  if ( ptQTask[12].tQTaskRefList.ptTail )
  {
    QTask_Delete((struct QTask_s *)ptQTask[12].tQTaskRefList.ptTail);
    ptQTask[12].tQTaskRefList.ptTail = nullptr;
  }
  Human_MakeRandomFaceModel((char *)&ptQTask[11].tQTaskRefList.ptMiddle);
  LODVirModelExistsFn = MTP_GetLODVirModelExistsFn((char *)&ptQTask[11].tQTaskRefList.ptMiddle);
  if ( LODVirModelExistsFn
    && LODVirModelExistsFn->nLOD > 0
    && LODVirModelExistsFn->aptVirModel[0]
    && (ptModel = LODVirModelExistsFn->aptVirModel[0]->ptModel) != nullptr
    && (ptMesh = ptModel->ptMesh) != nullptr
    && ptMesh->eRenderMeshType == MESH3D_RENDERMESHTYPE_DIRECT3D_BONE )
  {
    v6 = LODVirModelExistsFn;
  }
  else
  {
    v6 = nullptr;
  }
  BoneDynCubeObj_SetLODVirModel((struct BoneDynCubeObj_s *)ptQTask, v6);
  if ( v6 )
  {
    if ( ptQTask[7].tQTaskRefList.ptTail )
    {
      igi2_frame.v22 = ptQTask[7].tQTaskRefList.ptTail;
      igi2_frame.v21 = ptQTask;
      v7 = (struct QReference_s *)QTask_NewFn(ptQTask, AnimController_eQTaskType, &igi2_frame.v21);
      v8 = BYTE2(ptQTask[12].ptParent);
      ptQTask[12].tQTaskRefList.ptMiddle = v7;
      v9 = v8 == 0;
      pxObject = (unsigned int)v7[3].pxObject;
      if ( v9 )
        v11 = pxObject & 0xFFFFFFF7;
      else
        v11 = pxObject | 8;
      v7[3].pxObject = (void *)v11;
      ptQTask[13].tQTaskChildren.ptHead = ptQTask[13].ptPrev;
    }
    v12 = *(float *)&ptQTask[13].ptNext;
    ptQTask[12].tQTaskChildren.ptTail = (struct QTask_s *)ptQTask[12].tQTaskRefList.ptMiddle;
    if ( v12 > 0.0 )
    {
      igi2_frame.v22 = ptQTask[7].tQTaskRefList.ptTail;
      igi2_frame.v21 = ptQTask;
      v13 = (struct QReference_s *)QTask_NewFn(ptQTask, AnimController_eQTaskType, &igi2_frame.v21);
      v14 = BYTE2(ptQTask[12].ptParent);
      ptQTask[12].tQTaskRefList.ptMiddle = v13;
      v9 = v14 == 0;
      v15 = (unsigned int)v13[3].pxObject;
      if ( v9 )
        v16 = v15 & 0xFFFFFFF7;
      else
        v16 = v15 | 8;
      v13[3].pxObject = (void *)v16;
      v17 = (struct AnimControllerBase_t *)ptQTask[12].tQTaskChildren.ptTail;
      ptMiddle = ptQTask[12].tQTaskRefList.ptMiddle;
      ptQTask[13].tQTaskChildren.ptHead = ptQTask[13].ptPrev;
      ptQTask[12].tQTaskRefList.ptTail = (struct QReference_s *)AnimBlender_New(
                                                                  ptQTask,
                                                                  v17,
                                                                  (struct AnimControllerBase_t *)ptMiddle);
    }
    ptQTask[12].tQTaskRefList.ptHead = ptQTask[12].tQTaskRefList.ptMiddle;
    EditBoneObj_UpdateAnimation((struct EditBoneObj_s *)ptQTask);
  }
  igi2_frame.ptDynCubeObj = sqrt(
                   *(float *)&ptQTask[7].tQTaskChildren.ptTail * *(float *)&ptQTask[7].tQTaskChildren.ptTail
                 + *(float *)&ptQTask[7].tQTaskRefList.ptHead * *(float *)&ptQTask[7].tQTaskRefList.ptHead
                 + *(float *)&ptQTask[7].tQTaskRefList.ptMiddle * *(float *)&ptQTask[7].tQTaskRefList.ptMiddle)
               + *(float *)&ptQTask[8].ptNext;
  World_MoveDynCubeObjRadius(
    (struct World_s *)ptQTask[2].ptParent,
    (struct DynCubeObj_s *)ptQTask,
    (struct real64x3_t *)&ptQTask[10],
    igi2_frame.ptDynCubeObj);
  ModelObj_UpdateAttachments((struct ModelObj_s *)ptQTask);
  v19 = Attach_eAttachEvent;
  ptQTask[5].tQTaskChildren.ptTail = (struct QTask_s *)-1;
  ptQTask[5].tQTaskRefList.ptHead = nullptr;
  QTask_TriggerQTaskEventParent(ptQTask, v19, &ptQTask[5].tQTaskChildren.ptTail);
  ModelObj_CalcRelativePosAndOrientation((struct ModelObj_s *)ptQTask);
}

// source: h/2/editboneobj.c:402  [anchor-caller]
void __cdecl EditBoneObj_UpdateInternalDataAfterLoadHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptTail; // edx
  struct QExpression_s *v2; // eax
  struct QExpression_s *v3; // esi

  ptTail = ptQTask[13].tQTaskChildren.ptTail;
  if ( ptTail && LOBYTE(ptTail->ptNext) )
  {
    v2 = Script_ParseLine((char *)ptTail);
    v3 = v2;
    if ( v2 )
    {
      Expression_EvalString(v2, (char *)&ptQTask[12], 16);
      Expression_Delete(v3);
    }
    Script_isError = false;
  }
}

// source: h/2/editboneobj.c:444  [size]
void __cdecl EditBoneObj_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = EditBoneObj_ptParameterList;
}

// source: h/2/editboneobj.c:460  [anchor-mhash]
void __cdecl EditBoneObj_GetShadowInfoHandler(struct QTask_s *ptQTask, void *pxData)
{
  long double v2; // st7
  long double v3; // st6

  if ( *((_DWORD *)pxData + 2) )
  {
    v2 = sub_5C5840((struct real64x3_t *)&ptQTask[1], (struct World_s *)ptQTask[2].ptParent, 204800.0);
    *((float *)pxData + 1) = v2;
    v3 = sqrt(
           *(float *)&ptQTask[7].tQTaskChildren.ptTail * *(float *)&ptQTask[7].tQTaskChildren.ptTail
         + *(float *)&ptQTask[7].tQTaskRefList.ptHead * *(float *)&ptQTask[7].tQTaskRefList.ptHead
         + *(float *)&ptQTask[7].tQTaskRefList.ptMiddle * *(float *)&ptQTask[7].tQTaskRefList.ptMiddle)
       + *(float *)&ptQTask[8].ptNext;
    *((_DWORD *)pxData + 4) = ptQTask;
    *((float *)pxData + 1) = v3 + v2;
  }
  else
  {
    *((_DWORD *)pxData + 4) = ptQTask;
  }
}

// source: h/2/editboneobj.c:524  [anchor-caller]
void __cdecl EditBoneObj_DeSerializeDoneHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct QTask_s *v15; };
    struct { char igi2_o1[4]; struct QReference_s *v16; };
    char igi2_extent[12];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *ptTail; // eax
  struct QReference_s *v3; // eax
  char v4; // cl
  bool v5; // zf
  unsigned int pxObject; // ecx
  unsigned int v7; // ecx
  double v8; // st7
  struct QReference_s *v9; // eax
  char v10; // cl
  unsigned int v11; // ecx
  unsigned int v12; // ecx
  struct AnimControllerBase_t *v13; // ecx
  struct QReference_s *ptMiddle; // ebx

  ptTail = ptQTask[12].tQTaskChildren.ptTail;
  if ( ptTail )
  {
    if ( ptTail != (struct QTask_s *)ptQTask[12].tQTaskRefList.ptHead )
      QTask_Delete((struct QTask_s *)ptQTask[12].tQTaskRefList.ptHead);
    QTask_Delete(ptQTask[12].tQTaskChildren.ptTail);
    ptQTask[12].tQTaskRefList.ptMiddle = nullptr;
    ptQTask[12].tQTaskChildren.ptTail = nullptr;
    ptQTask[12].tQTaskRefList.ptHead = nullptr;
  }
  if ( ptQTask[12].tQTaskRefList.ptTail )
  {
    QTask_Delete((struct QTask_s *)ptQTask[12].tQTaskRefList.ptTail);
    ptQTask[12].tQTaskRefList.ptTail = nullptr;
  }
  if ( ptQTask[7].tQTaskRefList.ptTail )
  {
    igi2_frame.v16 = ptQTask[7].tQTaskRefList.ptTail;
    igi2_frame.v15 = ptQTask;
    v3 = (struct QReference_s *)QTask_NewFn(ptQTask, AnimController_eQTaskType, &igi2_frame.v15);
    v4 = BYTE2(ptQTask[12].ptParent);
    ptQTask[12].tQTaskRefList.ptMiddle = v3;
    v5 = v4 == 0;
    pxObject = (unsigned int)v3[3].pxObject;
    if ( v5 )
      v7 = pxObject & 0xFFFFFFF7;
    else
      v7 = pxObject | 8;
    v3[3].pxObject = (void *)v7;
    ptQTask[13].tQTaskChildren.ptHead = ptQTask[13].ptPrev;
  }
  v8 = *(float *)&ptQTask[13].ptNext;
  ptQTask[12].tQTaskChildren.ptTail = (struct QTask_s *)ptQTask[12].tQTaskRefList.ptMiddle;
  if ( v8 > 0.0 )
  {
    igi2_frame.v16 = ptQTask[7].tQTaskRefList.ptTail;
    igi2_frame.v15 = ptQTask;
    v9 = (struct QReference_s *)QTask_NewFn(ptQTask, AnimController_eQTaskType, &igi2_frame.v15);
    v10 = BYTE2(ptQTask[12].ptParent);
    ptQTask[12].tQTaskRefList.ptMiddle = v9;
    v5 = v10 == 0;
    v11 = (unsigned int)v9[3].pxObject;
    if ( v5 )
      v12 = v11 & 0xFFFFFFF7;
    else
      v12 = v11 | 8;
    v9[3].pxObject = (void *)v12;
    v13 = (struct AnimControllerBase_t *)ptQTask[12].tQTaskChildren.ptTail;
    ptMiddle = ptQTask[12].tQTaskRefList.ptMiddle;
    ptQTask[13].tQTaskChildren.ptHead = ptQTask[13].ptPrev;
    ptQTask[12].tQTaskRefList.ptTail = (struct QReference_s *)AnimBlender_New(
                                                                ptQTask,
                                                                v13,
                                                                (struct AnimControllerBase_t *)ptMiddle);
  }
  ptQTask[12].tQTaskRefList.ptHead = ptQTask[12].tQTaskRefList.ptMiddle;
  EditBoneObj_UpdateAnimation((struct EditBoneObj_s *)ptQTask);
}

// source: h/2/editboneobj.c:586  [anchor-callee]
void __cdecl EditBoneObj_SetAnimation(struct EditBoneObj_s *ptEditBoneObj, char *zAnimName)
{
  unsigned __int8 *pcHierarchy; // ecx
  struct QHashTable_s *v3; // esi
  unsigned int v4; // eax
  int v5; // eax
  int v6; // esi
  int v7; // eax
  struct AnimHeader_s *v8; // eax

  pcHierarchy = ptEditBoneObj->tBoneDynCubeObj.pcHierarchy;
  if ( pcHierarchy )
  {
    v3 = Hierarchy_ptHashTable;
    v4 = Hierarchy_ptHashTable->tPrivate.pfHashFunction(Hierarchy_ptHashTable->tPrivate.nHashTableSize, pcHierarchy);
    v5 = ((int  (__cdecl *)(struct QHashTable_s *, unsigned int, const void *))Hierarchy_ptHashTable->tPrivate.pfFindElement)(v3, v4, (const void *)(pcHierarchy));
    v6 = *(_DWORD *)v5;
    v7 = (*(int (__cdecl **)(_DWORD, char *))(*(_DWORD *)v5 + 12))(*(_DWORD *)(*(_DWORD *)v5 + 4), zAnimName);
    v8 = (struct AnimHeader_s *)(*(int (__cdecl **)(int, int, const void *))(v6 + 28))(v6, v7, (const void *)(zAnimName));
    if ( v8 )
    {
      ptEditBoneObj->ptAnimController->tBase.nFlags |= 0x20u;
      AnimController_SetAnimationAndTime(ptEditBoneObj->ptAnimController, v8, 0);
      ptEditBoneObj->ptAnimController->nTimeStep = (__int64)(ptEditBoneObj->vAnimSpeedFactor
                                                           * (double)AnimController_nTicksPerFrame);
    }
  }
}

// source: h/2/editboneobj.c:612  [size]
unsigned __int16 __cdecl EditBoneObj_GetQTaskType()
{
  return EditBoneObj_eQTaskType;
}

// source: h/2/editboneobj.c:625  [anchor-strings]
void __cdecl EditBoneObj_Open()
{
  unsigned __int16 v0; // si
  struct ParameterList_s *v1; // eax
  int v2; // edx

  v0 = QTask_NewQTaskType("EditBoneObj", 544, BoneDynCubeObj_eQTaskType, 0, 0);
  EditBoneObj_eQTaskType = v0;
  QTask_LinkQTaskEventHandlerFn(v0, 0, EditBoneObj_CreateHandler);
  QTask_LinkQTaskEventHandlerFn(v0, ParameterList_eUpdateInternalDataQTaskEvent, EditBoneObj_UpdateInternalDataHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))EditBoneObj_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerFn(v0, ShadowVolume_eGetShadowInfoEvent, EditBoneObj_GetShadowInfoHandler);
  QTask_LinkQTaskEventHandlerFn(v0, Serialize_eDeSerializeDoneQTaskEvent, EditBoneObj_DeSerializeDoneHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 2, EditBoneObj_DeleteHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 1, EditBoneObj_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(
    v0,
    Level_eUpdateInternalDataAfterLoadEvent,
    EditBoneObj_UpdateInternalDataAfterLoadHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, Attach_eUpdateAttachmentEvent, EditBoneObj_UpdateAttachmentHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveHandler);
  v1 = (struct ParameterList_s *)Mem_AllocFn(232, 4);
  v1->ptParameterListItem = (struct ParameterListItem_s *)&v1[1];
  v2 = Level_eParameterTypeObjectPos;
  v1->nParameters = 0;
  v1->nMaxParameters = 11;
  EditBoneObj_ptParameterList = v1;
  ParameterList_AddParameter(v1, 0x190u, v2, "Position", 7u, nullptr);
  ParameterList_AddParameter(
    EditBoneObj_ptParameterList,
    0x1A8u,
    Level_eParameterTypeReal32x9,
    "Orientation",
    7u,
    nullptr);
  ParameterList_AddParameter(
    EditBoneObj_ptParameterList,
    0x201u,
    Level_eParameterTypebool8,
    "Loop animation list",
    7u,
    nullptr);
  ParameterList_AddParameter(
    EditBoneObj_ptParameterList,
    0x202u,
    Level_eParameterTypebool8,
    "Use spline interpolation",
    7u,
    nullptr);
  ParameterList_AddParameter(EditBoneObj_ptParameterList, 0x1D0u, Level_eParameterTypeString16, "Model", 7u, nullptr);
  ParameterList_AddParameter(EditBoneObj_ptParameterList, 0x200u, Level_eParameterTypebool8, "Blinking", 7u, nullptr);
  ParameterList_AddParameter(
    EditBoneObj_ptParameterList,
    0x1E0u,
    Level_eParameterTypeString16,
    "WeaponModel",
    7u,
    nullptr);
  ParameterList_AddParameter(
    EditBoneObj_ptParameterList,
    0x218u,
    Level_eParameterTypeVarString,
    "WeaponModel Expression",
    7u,
    nullptr);
  ParameterList_AddParameter(
    EditBoneObj_ptParameterList,
    0x20Cu,
    Level_eParameterTypeVarString,
    "Animation list",
    7u,
    nullptr);
  ParameterList_AddParameterMinMax(
    EditBoneObj_ptParameterList,
    0x214u,
    Level_eParameterTypeReal32,
    "Time factor",
    7u,
    0.1,
    2.0);
  ParameterList_AddParameterMinMax(
    EditBoneObj_ptParameterList,
    0x208u,
    Level_eParameterTypeReal32,
    "Transition time",
    7u,
    0.0,
    1.0);
  EditBoneObj_tBlinkRandomState.anRandom[0] = -912896271;
  EditBoneObj_tBlinkRandomState.anRandom[1] = -463112362;
  EditBoneObj_tBlinkRandomState.anRandom[2] = -1522052915;
}

// source: h/2/editboneobj.c:678  [size]
void __cdecl EditBoneObj_Close()
{
  int v0; // esi

  if ( EditBoneObj_ptParameterList )
  {
    v0 = *(_DWORD *)((unsigned int)&EditBoneObj_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
  QTask_DeleteQTaskType(EditBoneObj_eQTaskType);
}

int sub_5C3B70()
{
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_FOGENABLE, 0);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_SPECULARENABLE, 0);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_CULLMODE, 1u);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_LIGHTING, 0);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_DITHERENABLE, 1u);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_COLORVERTEX, 1u);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ALPHATESTENABLE, 0);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ZBIAS, 0);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ZFUNC, 4u);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ZENABLE, Direct3D_bZBufferMode);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ZWRITEENABLE, 0);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_ALPHAOP, 3u);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_ALPHAARG1, 2u);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_ALPHAARG2, 0);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_COLOROP, 3u);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_COLORARG1, 2u);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 0, D3DTSS_COLORARG2, 0);
  Direct3D_ptDevice->lpVtbl->SetTextureStageState(Direct3D_ptDevice, 1u, D3DTSS_COLOROP, 1u);
  if ( Direct3D_tState.aptTexture[0] )
  {
    Direct3D_tState.aptTexture[0] = nullptr;
    Direct3D_ptDevice->lpVtbl->SetTexture(Direct3D_ptDevice, 0, nullptr);
  }
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_ALPHABLENDENABLE, 1u);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_SRCBLEND, 1u);
  return Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_DESTBLEND, 2u);
}

int sub_5C3D30()
{
  int result; // eax
  struct RenderStateBlock_t *v1; // edx
  struct RenderStateBlock_t *v2; // ecx
  struct RenderStateBlock_t *v3; // eax
  int v4; // ecx
  _DWORD v5[16]; // [esp+4h] [ebp-40h] BYREF

  result = ShadowVolume_iStartIndex;
  if ( ShadowVolume_iStartIndex )
  {
    v1 = Direct3D_ptBlendStateBlock;
    Direct3D_ptTextureStateBlock->eCurrentState = -1;
    v2 = Direct3D_ptGenericStateBlock;
    v1->eCurrentState = -1;
    v2->eCurrentState = -1;
    v3 = Direct3D_ptClippingStateBlock;
    v4 = Direct3D_eClippingStateOn;
    if ( Direct3D_ptClippingStateBlock->eCurrentState != Direct3D_eClippingStateOn )
    {
      Direct3D_ptClippingStateBlock->eCurrentState = Direct3D_eClippingStateOn;
      v3->atRenderState[v4].pfCallback(nullptr);
    }
    sub_5C3B70();
    memset(v5, 0, sizeof(v5));
    v5[15] = 1065353216;
    v5[10] = 1065353216;
    v5[5] = 1065353216;
    v5[0] = 1065353216;
    Direct3D_ptDevice->lpVtbl->SetTransform(
      Direct3D_ptDevice,
      (enum _D3DTRANSFORMSTATETYPE)256,
      (struct _D3DMATRIX *)v5);
    ShadowVolume_ptIndexBuffer->lpVtbl->Unlock(ShadowVolume_ptIndexBuffer);
    ShadowVolume_ptLockedIndex = nullptr;
    ShadowVolume_ptVertexBuffer->lpVtbl->Unlock(ShadowVolume_ptVertexBuffer);
    ShadowVolume_ptLockedVertex = nullptr;
    Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_STENCILENABLE, 1u);
    Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_STENCILFUNC, 8u);
    Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_STENCILPASS, 1u);
    Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_STENCILZFAIL, 4u);
    Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_CULLMODE, 2u);
    Direct3D_tState.ptIndexData = ShadowVolume_ptIndexBuffer;
    Direct3D_tState.nBaseVertexIndex = 0;
    Direct3D_ptDevice->lpVtbl->SetIndices(Direct3D_ptDevice, ShadowVolume_ptIndexBuffer, 0);
    Direct3D_tState.aptStreamData[0] = ShadowVolume_ptVertexBuffer;
    Direct3D_tState.anStride[0] = 12;
    Direct3D_ptDevice->lpVtbl->SetStreamSource(Direct3D_ptDevice, 0, ShadowVolume_ptVertexBuffer, 12u);
    Direct3D_tState.nHandle = 2;
    Direct3D_ptDevice->lpVtbl->SetVertexShader(Direct3D_ptDevice, 2u);
    Direct3D_ptDevice->lpVtbl->DrawIndexedPrimitive(
      Direct3D_ptDevice,
      D3DPT_TRIANGLELIST,
      0,
      ShadowVolume_iStartVertex,
      0,
      ShadowVolume_iStartIndex / 3);
    Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_STENCILZFAIL, 5u);
    Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_CULLMODE, 3u);
    Direct3D_ptDevice->lpVtbl->DrawIndexedPrimitive(
      Direct3D_ptDevice,
      D3DPT_TRIANGLELIST,
      0,
      ShadowVolume_iStartVertex,
      0,
      ShadowVolume_iStartIndex / 3);
    Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_STENCILZFAIL, 1u);
    Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_STENCILPASS, 3u);
    result = Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_STENCILREF, 0);
    ShadowVolume_iStartVertex = 0;
    ShadowVolume_iStartIndex = 0;
  }
  return result;
}

float *__cdecl sub_5C3F70(float *a1, float *a2, double *a3)
{
  double v3; // st7
  float v5; // [esp+8h] [ebp-Ch]
  float v6; // [esp+Ch] [ebp-8h]
  float v7; // [esp+10h] [ebp-4h]

  ShadowVolume_tDeltaPos.vX = *a3 - TransContext_tActiveTransContext.tPos.vX;
  ShadowVolume_tDeltaPos.vY = a3[1] - TransContext_tActiveTransContext.tPos.vY;
  v3 = a3[2];
  ShadowVolume_tDeltaPos.vX = Direct3D_vScale * ShadowVolume_tDeltaPos.vX;
  ShadowVolume_tDeltaPos.vY = Direct3D_vScale * ShadowVolume_tDeltaPos.vY;
  ShadowVolume_tDeltaPos.vZ = Direct3D_vScale * (v3 - TransContext_tActiveTransContext.tPos.vZ);
  qmemcpy(&ShadowVolume_tMatrix, a1, sizeof(ShadowVolume_tMatrix));
  ShadowVolume_tMatrix.tX.vX = ShadowVolume_tMatrix.tX.vX * Direct3D_vScale;
  ShadowVolume_tMatrix.tX.vY = ShadowVolume_tMatrix.tX.vY * Direct3D_vScale;
  ShadowVolume_tMatrix.tX.vZ = ShadowVolume_tMatrix.tX.vZ * Direct3D_vScale;
  ShadowVolume_tMatrix.tY.vX = ShadowVolume_tMatrix.tY.vX * Direct3D_vScale;
  ShadowVolume_tMatrix.tY.vY = ShadowVolume_tMatrix.tY.vY * Direct3D_vScale;
  ShadowVolume_tMatrix.tY.vZ = ShadowVolume_tMatrix.tY.vZ * Direct3D_vScale;
  ShadowVolume_tMatrix.tZ.vX = ShadowVolume_tMatrix.tZ.vX * Direct3D_vScale;
  ShadowVolume_tMatrix.tZ.vY = ShadowVolume_tMatrix.tZ.vY * Direct3D_vScale;
  ShadowVolume_tMatrix.tZ.vZ = ShadowVolume_tMatrix.tZ.vZ * Direct3D_vScale;
  v5 = a1[3] * SkyDome_ptDirlight->tDir.vY + a1[6] * SkyDome_ptDirlight->tDir.vZ + *a1 * SkyDome_ptDirlight->tDir.vX;
  v6 = a1[4] * SkyDome_ptDirlight->tDir.vY + a1[7] * SkyDome_ptDirlight->tDir.vZ + a1[1] * SkyDome_ptDirlight->tDir.vX;
  v7 = a1[5] * SkyDome_ptDirlight->tDir.vY + a1[8] * SkyDome_ptDirlight->tDir.vZ + a1[2] * SkyDome_ptDirlight->tDir.vX;
  *a2 = v5;
  a2[1] = v6;
  a2[2] = v7;
  *a2 = -*a2;
  a2[1] = -a2[1];
  a2[2] = -a2[2];
  return a2;
}

int __cdecl sub_5C4110(int a1, float *a2, int a3, _WORD *a4)
{
  _DWORD *v4; // ebx
  _WORD *v5; // ebp
  double v7; // st7
  double v8; // st6
  unsigned __int16 *v9; // ecx
  int v10; // edx
  int v11; // eax
  double v12; // st7
  int v13; // esi
  int v14; // eax
  double v15; // st7
  double v16; // st6
  double v17; // st5
  float *v18; // eax
  int v19; // esi
  double v20; // st4
  int v21; // [esp+8h] [ebp-28h]
  float v22; // [esp+Ch] [ebp-24h]
  float v23; // [esp+10h] [ebp-20h]
  float v24; // [esp+18h] [ebp-18h]
  float v25; // [esp+1Ch] [ebp-14h]
  float i; // [esp+20h] [ebp-10h]
  float v27; // [esp+24h] [ebp-Ch]
  float v28; // [esp+28h] [ebp-8h]

  v4 = *(_DWORD **)(a1 + 36);
  v5 = a4;
  if ( *(_DWORD *)(a1 + 32) != 3 )
    return 0;
  v21 = 0;
  v24 = a2[6] * SkyDome_ptDirlight->tDir.vZ + a2[3] * SkyDome_ptDirlight->tDir.vY + *a2 * SkyDome_ptDirlight->tDir.vX;
  v25 = a2[7] * SkyDome_ptDirlight->tDir.vZ + a2[4] * SkyDome_ptDirlight->tDir.vY + a2[1] * SkyDome_ptDirlight->tDir.vX;
  v7 = a2[8] * SkyDome_ptDirlight->tDir.vZ + a2[5] * SkyDome_ptDirlight->tDir.vY;
  v8 = a2[2];
  v9 = (unsigned __int16 *)v4[7];
  for ( i = v7 + v8 * SkyDome_ptDirlight->tDir.vX; v21 < (int)(v4[2]); ++v21 )
  {
    v10 = v4[5];
    v11 = 28 * v9[1];
    v12 = *(float *)(v11 + v10);
    v13 = v11 + v10;
    v14 = 28 * *v9;
    v15 = v12 - *(float *)(v14 + v10);
    v16 = *(float *)(v13 + 4) - *(float *)(v14 + v10 + 4);
    v17 = *(float *)(v13 + 8) - *(float *)(v14 + v10 + 8);
    v18 = (float *)(v10 + v14);
    v19 = 28 * v9[2];
    v22 = *(float *)(v10 + v19) - *v18;
    v23 = *(float *)(v10 + v19 + 4) - v18[1];
    v20 = *(float *)(v19 + v10 + 8) - v18[2];
    v27 = v20 * v16 - v23 * v17;
    v28 = -(v20 * v15 - v22 * v17);
    if ( i * (v15 * v23 - v22 * v16) + v28 * v25 + v27 * v24 >= 0.0 )
    {
      if ( a4 )
      {
        *v5 = *v9;
        v5[1] = v9[1];
        v5[2] = v9[2];
      }
      v5 += 3;
    }
    v9 += 3;
  }
  return v5 - a4;
}

struct QObjectVector_s *sub_5C4290()
{
  #pragma pack(push, 1)
  union
  {
    struct { unsigned int v15; };
    struct { char igi2_o1[20]; float v16; };
    struct { char igi2_o2[24]; float v17; };
    struct { char igi2_o3[28]; float i; };
    struct { char igi2_o4[32]; struct real32x3_t ptPos; };
    struct { char igi2_o5[44]; struct real32x9_t ptSource; };
    struct { char igi2_o6[84]; struct _D3DMATRIX ptDest; };
    char igi2_extent[148];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QObjectVector_s *result; // eax
  unsigned int v1; // ebp
  _DWORD *v2; // edi
  int v3; // esi
  struct IDirect3DIndexBuffer8 **v4; // ebx
  struct RenderStateBlock_t *v5; // edx
  struct RenderStateBlock_t *v6; // ecx
  struct RenderStateBlock_t *v7; // eax
  int v8; // ecx
  double *v9; // eax
  double v10; // st7
  double v11; // st6
  double v12; // st5
  int v13; // eax
  struct IDirect3DIndexBuffer8 *v14; // ecx

  igi2_frame.v16 = Direct3D_vScale;
  result = ShadowVolume_ptProtectRequestVector;
  igi2_frame.v17 = Direct3D_vScale;
  v1 = 0;
  for ( igi2_frame.i = Direct3D_vScale; v1 < ShadowVolume_ptProtectRequestVector->nAllocated; ++v1 )
  {
    v2 = result->papxElement[v1];
    v3 = *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(*(_DWORD *)(*v2 + 4 * v2[4]) + 12) + 12) + 36);
    v4 = (struct IDirect3DIndexBuffer8 **)v2[1];
    v5 = Direct3D_ptBlendStateBlock;
    Direct3D_ptTextureStateBlock->eCurrentState = -1;
    v6 = Direct3D_ptGenericStateBlock;
    v5->eCurrentState = -1;
    v6->eCurrentState = -1;
    v7 = Direct3D_ptClippingStateBlock;
    v8 = Direct3D_eClippingStateOn;
    if ( Direct3D_ptClippingStateBlock->eCurrentState != Direct3D_eClippingStateOn )
    {
      Direct3D_ptClippingStateBlock->eCurrentState = Direct3D_eClippingStateOn;
      v7->atRenderState[v8].pfCallback(nullptr);
    }
    sub_5C3B70();
    Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_STENCILENABLE, 1u);
    Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_STENCILFUNC, 8u);
    Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_STENCILPASS, 3u);
    Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_STENCILZFAIL, 1u);
    Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_CULLMODE, 3u);
    v9 = (double *)v2[2];
    v10 = *v9 - TransContext_tActiveTransContext.tPos.vX;
    v11 = v9[1] - TransContext_tActiveTransContext.tPos.vY;
    v12 = v9[2];
    v13 = v2[3];
    igi2_frame.ptPos.vZ = v12 - TransContext_tActiveTransContext.tPos.vZ;
    igi2_frame.ptPos.vX = Direct3D_vScale * v10;
    igi2_frame.ptPos.vY = Direct3D_vScale * v11;
    igi2_frame.ptPos.vZ = Direct3D_vScale * igi2_frame.ptPos.vZ;
    igi2_frame.ptSource.tX.vX = igi2_frame.v16 * *(float *)v13;
    igi2_frame.ptSource.tX.vY = igi2_frame.v17 * *(float *)(v13 + 4);
    igi2_frame.ptSource.tX.vZ = igi2_frame.i * *(float *)(v13 + 8);
    igi2_frame.ptSource.tY.vX = igi2_frame.v16 * *(float *)(v13 + 12);
    igi2_frame.ptSource.tY.vY = igi2_frame.v17 * *(float *)(v13 + 16);
    igi2_frame.ptSource.tY.vZ = igi2_frame.i * *(float *)(v13 + 20);
    igi2_frame.ptSource.tZ.vX = igi2_frame.v16 * *(float *)(v13 + 24);
    igi2_frame.ptSource.tZ.vY = igi2_frame.v17 * *(float *)(v13 + 28);
    igi2_frame.ptSource.tZ.vZ = igi2_frame.i * *(float *)(v13 + 32);
    igi2_frame.ptSource.nOps = *(_DWORD *)(v13 + 36) + 1;
    Direct3D_D3DMATRIXFromReal32x9(&igi2_frame.ptDest, &igi2_frame.ptSource, &igi2_frame.ptPos);
    Direct3D_ptDevice->lpVtbl->SetTransform(Direct3D_ptDevice, (enum _D3DTRANSFORMSTATETYPE)256, &igi2_frame.ptDest);
    v14 = *v4;
    igi2_frame.v15 = *(unsigned __int16 *)(*(_DWORD *)(v3 + 36) + 12);
    Direct3D_tState.nBaseVertexIndex = igi2_frame.v15;
    Direct3D_tState.ptIndexData = v14;
    Direct3D_ptDevice->lpVtbl->SetIndices(Direct3D_ptDevice, v14, igi2_frame.v15);
    Direct3D_tState.aptStreamData[0] = **(struct IDirect3DVertexBuffer8 ***)(*(_DWORD *)(v3 + 36) + 16);
    Direct3D_tState.anStride[0] = 28;
    Direct3D_ptDevice->lpVtbl->SetStreamSource(Direct3D_ptDevice, 0, Direct3D_tState.aptStreamData[0], 28u);
    Direct3D_tState.nHandle = *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(v3 + 36) + 16) + 24);
    Direct3D_ptDevice->lpVtbl->SetVertexShader(Direct3D_ptDevice, Direct3D_tState.nHandle);
    Direct3D_ptDevice->lpVtbl->DrawIndexedPrimitive(
      Direct3D_ptDevice,
      D3DPT_TRIANGLELIST,
      0,
      *(_DWORD *)(v3 + 16),
      (unsigned int)v4[v2[4] + 1],
      (unsigned int)v4[v2[4] + 6]);
    result = ShadowVolume_ptProtectRequestVector;
  }
  return result;
}

int __cdecl sub_5C4510(int a1, int *a2, float *a3)
{
  double v3; // st7
  int v4; // ebp
  int *v5; // esi
  int v6; // ebx
  unsigned __int16 *v7; // edx
  int v8; // edi
  struct ShadowVolume_Direct3DVertex_t *v9; // ecx
  float *v10; // eax
  int v11; // esi
  double vX; // st7
  double v13; // st7
  double vZ; // st7
  float *p_vX; // esi
  int v16; // ecx
  int v17; // esi
  int v18; // eax
  unsigned int v19; // ebx
  float *v20; // edi
  __int16 v21; // si
  __int16 v22; // ax
  int v23; // ecx
  __int16 v24; // si
  __int16 v25; // ax
  int v26; // ecx
  __int16 v27; // si
  __int16 v28; // ax
  int v29; // ecx
  __int16 v30; // si
  __int16 v31; // ax
  __int16 v32; // si
  __int16 v33; // ax
  unsigned __int16 *v34; // eax
  unsigned __int16 v35; // di
  int v36; // ecx
  int result; // eax
  int v38; // esi
  int v39; // ebp
  _DWORD *v40; // esi
  int v41; // eax
  unsigned __int16 v42; // ax
  bool v43; // zf
  unsigned __int16 v44; // si
  unsigned __int16 v45; // ax
  unsigned __int16 *v46; // edx
  int v47; // eax
  int v48; // edx
  int v49; // [esp+28h] [ebp-30h]
  int i; // [esp+28h] [ebp-30h]
  int v51; // [esp+2Ch] [ebp-2Ch]
  unsigned __int16 *v52; // [esp+30h] [ebp-28h]
  float v53; // [esp+34h] [ebp-24h]
  float v54; // [esp+34h] [ebp-24h]
  float v55; // [esp+38h] [ebp-20h]
  float v56; // [esp+38h] [ebp-20h]
  float v57; // [esp+3Ch] [ebp-1Ch]
  float v58; // [esp+3Ch] [ebp-1Ch]
  float v59; // [esp+40h] [ebp-18h]
  float v60; // [esp+44h] [ebp-14h]
  float v61; // [esp+48h] [ebp-10h]
  float v62; // [esp+4Ch] [ebp-Ch]
  float v63; // [esp+50h] [ebp-8h]
  float v64; // [esp+54h] [ebp-4h]
  int a1a = *(int *)&a1; // [esp+5Ch] [ebp+4h] ARGSLOT
  int a1b = *(int *)&a1; // [esp+5Ch] [ebp+4h] ARGSLOT
  int a1c = *(int *)&a1; // [esp+5Ch] [ebp+4h] ARGSLOT
  int a1d = *(int *)&a1; // [esp+5Ch] [ebp+4h] ARGSLOT

  v3 = Direct3D_vScale * *(float *)(a1 + 240);
  v4 = ShadowVolume_iStartVertex;
  v5 = a2;
  v59 = -(SkyDome_ptDirlight->tDir.vX * v3);
  v60 = -(SkyDome_ptDirlight->tDir.vY * v3);
  v61 = -(v3 * SkyDome_ptDirlight->tDir.vZ);
  if ( ShadowVolume_iStartVertex + 2 * a2[4] > ShadowVolume_nVertexBufferSize
    || ShadowVolume_iStartIndex + 300 > ShadowVolume_nIndexBufferSize )
  {
    sub_5C3D30();
    v4 = ShadowVolume_iStartVertex;
  }
  if ( !ShadowVolume_ptLockedVertex )
  {
    ShadowVolume_ptVertexBuffer->lpVtbl->Lock(
      ShadowVolume_ptVertexBuffer,
      0,
      0,
      (unsigned __int8 **)&ShadowVolume_ptLockedVertex,
      0x2000u);
    v4 = ShadowVolume_iStartVertex;
  }
  if ( !ShadowVolume_ptLockedIndex )
  {
    ShadowVolume_ptIndexBuffer->lpVtbl->Lock(
      ShadowVolume_ptIndexBuffer,
      0,
      0,
      (unsigned __int8 **)&ShadowVolume_ptLockedIndex,
      0x2000u);
    v4 = ShadowVolume_iStartVertex;
  }
  v6 = a2[4];
  v7 = &ShadowVolume_ptLockedIndex[ShadowVolume_iStartIndex];
  v8 = 0;
  v9 = &ShadowVolume_ptLockedVertex[v4];
  v10 = (float *)a2[1];
  v52 = v7;
  if ( v6 > 0 )
  {
    v11 = 0;
    do
    {
      vX = ShadowVolume_tMatrix.tX.vX;
      ShadowVolume_anVertexLeft[v11] = -1;
      ShadowVolume_anVertexRight[v11] = -1;
      v13 = vX * *v10;
      v10 += 3;
      v62 = v13 + ShadowVolume_tMatrix.tX.vZ * *(v10 - 1) + ShadowVolume_tMatrix.tX.vY * *(v10 - 2);
      v63 = ShadowVolume_tMatrix.tY.vX * *(v10 - 3)
          + ShadowVolume_tMatrix.tY.vZ * *(v10 - 1)
          + ShadowVolume_tMatrix.tY.vY * *(v10 - 2);
      v64 = ShadowVolume_tMatrix.tZ.vX * *(v10 - 3)
          + ShadowVolume_tMatrix.tZ.vZ * *(v10 - 1)
          + ShadowVolume_tMatrix.tZ.vY * *(v10 - 2);
      v53 = ShadowVolume_tDeltaPos.vX + v62;
      v55 = ShadowVolume_tDeltaPos.vY + v63;
      vZ = ShadowVolume_tDeltaPos.vZ;
      v9->tPos.vX = v53;
      v9->tPos.vY = v55;
      v57 = vZ + v64;
      v9->tPos.vZ = v57;
      p_vX = &v9[1].tPos.vX;
      v9 += 2;
      ++v8;
      v54 = v53 + v59;
      *p_vX = v54;
      v56 = v55 + v60;
      p_vX[1] = v56;
      v58 = v57 + v61;
      p_vX[2] = v58;
      v11 = (unsigned __int16)v8;
    }
    while ( (unsigned __int16)v8 < v6 );
    v4 = ShadowVolume_iStartVertex;
    v5 = a2;
  }
  v16 = *v5;
  v17 = v5[3];
  ShadowVolume_nPolygons += 2 * v17;
  v18 = 0;
  v19 = 0;
  v51 = v17;
  a1a = 0;
  if ( v17 < 4 )
  {
    v20 = a3;
  }
  else
  {
    v49 = 3;
    do
    {
      v20 = a3;
      if ( *(float *)(v16 + 24) * a3[2] + *(float *)(v16 + 16) * *a3 + *(float *)(v16 + 20) * a3[1] < 0.0 )
      {
        v21 = v4 + 1;
      }
      else
      {
        v21 = v4;
        v19 ^= *(_DWORD *)(v16 + 12);
      }
      v22 = 2 * *(_WORD *)v16;
      v23 = v16 + 28;
      *v7 = v21 + v22;
      v7[1] = v21 + 2 * *(_WORD *)(v23 - 20);
      v7[2] = v21 + 2 * *(_WORD *)(v23 - 24);
      if ( *(float *)(v23 + 24) * a3[2] + *(float *)(v23 + 16) * *a3 + *(float *)(v23 + 20) * a3[1] < 0.0 )
      {
        v24 = v4 + 1;
      }
      else
      {
        v24 = v4;
        v19 ^= *(_DWORD *)(v23 + 12);
      }
      v25 = 2 * *(_WORD *)v23;
      v26 = v23 + 28;
      v7[3] = v24 + v25;
      v7[4] = v24 + 2 * *(_WORD *)(v26 - 20);
      v7[5] = v24 + 2 * *(_WORD *)(v26 - 24);
      if ( *(float *)(v26 + 24) * a3[2] + *(float *)(v26 + 16) * *a3 + *(float *)(v26 + 20) * a3[1] < 0.0 )
      {
        v27 = v4 + 1;
      }
      else
      {
        v27 = v4;
        v19 ^= *(_DWORD *)(v26 + 12);
      }
      v28 = 2 * *(_WORD *)v26;
      v29 = v26 + 28;
      v7[6] = v27 + v28;
      v7[7] = v27 + 2 * *(_WORD *)(v29 - 20);
      v7[8] = v27 + 2 * *(_WORD *)(v29 - 24);
      if ( *(float *)(v29 + 24) * a3[2] + *(float *)(v29 + 16) * *a3 + *(float *)(v29 + 20) * a3[1] < 0.0 )
      {
        v30 = v4 + 1;
      }
      else
      {
        v30 = v4;
        v19 ^= *(_DWORD *)(v29 + 12);
      }
      v31 = 2 * *(_WORD *)v29;
      v16 = v29 + 28;
      v7 += 12;
      *(v7 - 3) = v30 + v31;
      *(v7 - 2) = v30 + 2 * *(_WORD *)(v16 - 20);
      *(v7 - 1) = v30 + 2 * *(_WORD *)(v16 - 24);
      a1a += 4;
      v49 += 4;
    }
    while ( v49 < v51 );
    v18 = a1a;
  }
  if ( v18 < v51 )
  {
    a1b = v51 - v18;
    do
    {
      if ( *(float *)(v16 + 24) * v20[2] + *(float *)(v16 + 16) * *v20 + *(float *)(v16 + 20) * v20[1] < 0.0 )
      {
        v32 = v4 + 1;
      }
      else
      {
        v32 = v4;
        v19 ^= *(_DWORD *)(v16 + 12);
      }
      v33 = 2 * *(_WORD *)v16;
      v16 += 28;
      v7 += 3;
      *(v7 - 3) = v32 + v33;
      *(v7 - 2) = v32 + 2 * *(_WORD *)(v16 - 20);
      *(v7 - 1) = v32 + 2 * *(_WORD *)(v16 - 24);
      --a1b;
    }
    while ( a1b );
  }
  v34 = (unsigned __int16 *)a2[2];
  v35 = (unsigned __int16)a2;
  LOWORD(v36) = (_WORD)a2;
  a1c = (int)v34;
  for ( i = 0; v19; a1c += 8 )
  {
    if ( (v19 & 1) != 0 )
    {
      v35 = *v34;
      ShadowVolume_nPolygons += 2;
      LOWORD(v36) = v34[2];
      result = v35;
      ++i;
      if ( ShadowVolume_anVertexLeft[v35] < 0 )
      {
        v38 = (unsigned __int16)v36;
        ShadowVolume_anVertexLeft[v35] = (unsigned __int16)v36;
      }
      else
      {
        if ( ShadowVolume_anVertexRight[v35] != -1 )
          return result;
        v38 = (unsigned __int16)v36;
        ShadowVolume_anVertexRight[v35] = (unsigned __int16)v36;
      }
      if ( ShadowVolume_anVertexLeft[v38] < 0 )
      {
        ShadowVolume_anVertexLeft[v38] = v35;
      }
      else
      {
        v39 = ShadowVolume_anVertexRight[v38];
        v40 = (_DWORD *)(4 * v38 + 129827464);
        if ( v39 != -1 )
          return result;
        *v40 = v35;
      }
      v4 = ShadowVolume_iStartVertex;
    }
    v19 >>= 1;
    v34 = (unsigned __int16 *)(a1c + 8);
  }
  v41 = *a2;
  a1d = 0;
  if ( v51 > 0 )
  {
    while ( (*(_DWORD *)v41 != v35 || *(_DWORD *)(v41 + 4) != (unsigned __int16)v36)
         && (*(_DWORD *)(v41 + 4) != v35 || *(_DWORD *)(v41 + 8) != (unsigned __int16)v36)
         && (*(_DWORD *)(v41 + 8) != v35 || *(_DWORD *)v41 != (unsigned __int16)v36) )
    {
      v41 += 28;
      if ( ++a1d >= v51 )
        goto LABEL_58;
    }
    if ( *(float *)(v41 + 24) * a3[2] + *(float *)(v41 + 20) * a3[1] + *(float *)(v41 + 16) * *a3 < 0.0 )
    {
      v42 = v36;
      LOWORD(v36) = v35;
      v35 = v42;
    }
  }
LABEL_58:
  while ( i > 0 )
  {
    --i;
    result = 4 * (unsigned __int16)v36;
    v43 = *(int *)((char *)ShadowVolume_anVertexLeft + result) == v35;
    v35 = v36;
    if ( v43 )
    {
      if ( ShadowVolume_anVertexRight[(unsigned __int16)v36] == -1 )
        return result;
      v36 = LOWORD(ShadowVolume_anVertexRight[(unsigned __int16)v36]);
    }
    else
    {
      v36 = ShadowVolume_anVertexLeft[(unsigned __int16)v36];
      if ( v36 == -1 )
        return result;
    }
    v44 = v4 + 2 * v35;
    *v7 = v44++;
    v45 = v4 + 2 * v36;
    v7[1] = v45;
    v7[2] = v44;
    v46 = v7 + 3;
    *v46 = v45;
    v46[1] = v45 + 1;
    v46[2] = v44;
    v7 = v46 + 3;
  }
  v47 = v7 - v52 + ShadowVolume_iStartIndex;
  v48 = a2[4];
  ShadowVolume_iStartIndex = v47;
  result = v4 + 2 * v48;
  ShadowVolume_iStartVertex = result;
  return result;
}

void __cdecl sub_5C4B80(int a1, int a2)
{
  #pragma pack(push, 1)
  union
  {
    struct { float v11; };
    struct { char igi2_o1[4]; _BYTE ptPos[40]; };
    char igi2_extent[44];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  bool v2; // zf
  int v3; // eax
  double v4; // st7
  double v5; // st6
  int v6; // ecx
  int v7; // edx
  double v8; // st5
  double v9; // st4
  double *v10; // eax

  if ( ShadowVolume_isEnabled && *(_DWORD *)(a1 + 256) )
  {
    v2 = SkyDome_ptDirlight == nullptr;
    *(_DWORD *)(a1 + 252) = 0;
    *(_DWORD *)(a1 + 248) = 0;
    if ( !v2 )
    {
      QTask_TriggerQTaskEventParent((struct QTask_s *)a1, ShadowVolume_eGetShadowInfoEvent, (void *)(a1 + 236));
      *(_DWORD *)(a1 + 244) = 0;
    }
    if ( *(_DWORD *)(a1 + 248) || a2 )
    {
      v3 = *(_DWORD *)(a1 + 220);
      v4 = *(float *)(v3 + 8) * *(float *)(a1 + 204)
         + *(float *)(a1 + 200) * *(float *)(v3 + 4)
         + *(float *)v3 * *(float *)(a1 + 196);
      v5 = *(float *)(v3 + 12) * *(float *)(a1 + 196)
         + *(float *)(a1 + 200) * *(float *)(v3 + 16)
         + *(float *)(v3 + 20) * *(float *)(a1 + 204);
      igi2_frame.v11 = *(float *)(v3 + 32) * *(float *)(a1 + 204)
          + *(float *)(a1 + 196) * *(float *)(v3 + 24)
          + *(float *)(v3 + 28) * *(float *)(a1 + 200);
      *(float *)igi2_frame.ptPos = *(float *)v3 * *(float *)(a1 + 156)
                      + *(float *)(v3 + 8) * *(float *)(a1 + 180)
                      + *(float *)(v3 + 4) * *(float *)(a1 + 168);
      *(float *)&igi2_frame.ptPos[4] = *(float *)(v3 + 8) * *(float *)(a1 + 184)
                          + *(float *)(v3 + 4) * *(float *)(a1 + 172)
                          + *(float *)v3 * *(float *)(a1 + 160);
      *(float *)&igi2_frame.ptPos[8] = *(float *)(a1 + 176) * *(float *)(v3 + 4)
                          + *(float *)v3 * *(float *)(a1 + 164)
                          + *(float *)(v3 + 8) * *(float *)(a1 + 188);
      *(float *)&igi2_frame.ptPos[12] = *(float *)(v3 + 20) * *(float *)(a1 + 180)
                           + *(float *)(v3 + 16) * *(float *)(a1 + 168)
                           + *(float *)(v3 + 12) * *(float *)(a1 + 156);
      *(float *)&igi2_frame.ptPos[16] = *(float *)(v3 + 20) * *(float *)(a1 + 184)
                           + *(float *)(v3 + 16) * *(float *)(a1 + 172)
                           + *(float *)(v3 + 12) * *(float *)(a1 + 160);
      v6 = *(_DWORD *)(v3 + 36);
      v7 = *(_DWORD *)(a1 + 192);
      *(float *)&igi2_frame.ptPos[20] = *(float *)(v3 + 12) * *(float *)(a1 + 164)
                           + *(float *)(a1 + 188) * *(float *)(v3 + 20)
                           + *(float *)(a1 + 176) * *(float *)(v3 + 16);
      *(float *)&igi2_frame.ptPos[24] = *(float *)(a1 + 156) * *(float *)(v3 + 24)
                           + *(float *)(v3 + 32) * *(float *)(a1 + 180)
                           + *(float *)(v3 + 28) * *(float *)(a1 + 168);
      *(float *)&igi2_frame.ptPos[28] = *(float *)(v3 + 32) * *(float *)(a1 + 184)
                           + *(float *)(v3 + 28) * *(float *)(a1 + 172)
                           + *(float *)(a1 + 160) * *(float *)(v3 + 24);
      v8 = *(float *)(v3 + 32) * *(float *)(a1 + 188) + *(float *)(v3 + 28) * *(float *)(a1 + 176);
      v9 = *(float *)(v3 + 24) * *(float *)(a1 + 164);
      *(_DWORD *)&igi2_frame.ptPos[36] = v6 + v7 + 1;
      v10 = *(double **)(a1 + 216);
      *(float *)&igi2_frame.ptPos[32] = v8 + v9;
      qmemcpy((void *)(a1 + 116), igi2_frame.ptPos, 0x28u);
      *(double *)igi2_frame.ptPos = v4 + *v10;
      *(double *)&igi2_frame.ptPos[8] = v5 + v10[1];
      *(double *)&igi2_frame.ptPos[16] = igi2_frame.v11 + v10[2];
      if ( a2 )
        World_RegisterDynCubeObjFirstTimeRadius(
          *(struct World_s **)(a1 + 112),
          (struct DynCubeObj_s *)a1,
          (struct real64x3_t *)igi2_frame.ptPos,
          *(float *)(a1 + 240),
          WORLD_DYNCUBETREE_CATEGORY_MOBILE);
      else
        World_MoveDynCubeObjRadius(
          *(struct World_s **)(a1 + 112),
          (struct DynCubeObj_s *)a1,
          (struct real64x3_t *)igi2_frame.ptPos,
          *(float *)(a1 + 240));
    }
  }
}

void __cdecl sub_5C4E10()
{
  float vR; // [esp+0h] [ebp-4h]

  if ( ShadowVolume_isEnabled )
  {
    vR = (1.0 - *(float *)&ShadowVolume_nUseAsm) * 128.0;
    sub_5C4290();
    QSprite_RegisterBlank(
      RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vX,
      RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vY,
      RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vWidth,
      RenderContext_tActiveRenderContext.tClippingWindow.tClippingRect.vHeight,
      vR,
      vR,
      vR,
      0x80100000,
      -1);
  }
}

void __cdecl sub_5C4E70(struct QTask_s *a1)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct QTask_s *ptNext; };
    struct { char igi2_o1[20]; int v12; };
    struct { char igi2_o2[24]; float a2; };
    struct { char igi2_o3[28]; float v14; };
    struct { char igi2_o4[32]; float v15; };
    struct { char igi2_o5[36]; struct real32x3_t ptRotatedPos; };
    struct { char igi2_o6[60]; float a3[10]; };
    char igi2_extent[100];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  double v2; // st7
  double v3; // st7
  double v4; // st6
  double v5; // st5
  struct real32x3_t *ptMiddle; // esi
  int v7; // edi
  struct QTask_s *v8; // edi
  int v9; // ebx
  bool v10; // cc
  struct QTask_s *a1a = *(struct QTask_s * *)&a1; // [esp+54h] [ebp+4h] ARGSLOT

  if ( ShadowVolume_isEnabled )
  {
    if ( a1[6].tQTaskChildren.ptHead )
    {
      igi2_frame.a2 = *(double *)&a1[1].ptNext - TransContext_tActiveTransContext.tPos.vX;
      igi2_frame.v14 = *(double *)&a1[1].tQTaskChildren.ptHead - TransContext_tActiveTransContext.tPos.vY;
      if ( igi2_frame.a2 * igi2_frame.a2
         + igi2_frame.v14 * igi2_frame.v14
         + (*(double *)&a1[1].tQTaskChildren.ptTail - TransContext_tActiveTransContext.tPos.vZ)
         * (*(double *)&a1[1].tQTaskChildren.ptTail - TransContext_tActiveTransContext.tPos.vZ) < 9.437184e10 )
      {
        v2 = *(double *)&a1[1].ptNext;
        a1[6].ptPrev = (struct QTask_s *)1;
        v3 = v2 - TransContext_tActiveTransContext.tPos.vX;
        v4 = *(double *)&a1[1].tQTaskChildren.ptHead - TransContext_tActiveTransContext.tPos.vY;
        v5 = *(double *)&a1[1].tQTaskChildren.ptTail - TransContext_tActiveTransContext.tPos.vZ;
        igi2_frame.a2 = TransContext_tActiveTransContext.tMatrix.tX.vZ * v5
           + TransContext_tActiveTransContext.tMatrix.tX.vY * v4
           + TransContext_tActiveTransContext.tMatrix.tX.vX * v3;
        igi2_frame.ptRotatedPos.vX = igi2_frame.a2;
        igi2_frame.ptNext = a1[6].ptNext;
        igi2_frame.v14 = TransContext_tActiveTransContext.tMatrix.tY.vZ * v5
            + TransContext_tActiveTransContext.tMatrix.tY.vY * v4
            + TransContext_tActiveTransContext.tMatrix.tY.vX * v3;
        igi2_frame.ptRotatedPos.vY = igi2_frame.v14;
        igi2_frame.v15 = TransContext_tActiveTransContext.tMatrix.tZ.vZ * v5
            + TransContext_tActiveTransContext.tMatrix.tZ.vY * v4
            + TransContext_tActiveTransContext.tMatrix.tZ.vX * v3;
        igi2_frame.ptRotatedPos.vZ = igi2_frame.v15;
        if ( Mesh3D_ExcludeObject(&igi2_frame.ptRotatedPos, *(float *)&igi2_frame.ptNext, nullptr) == false )
        {
          if ( ShadowVolume_isShadowLayerRegistered == false )
          {
            World_DrawManualDynCubeObj(&ShadowVolume_tShadowLayerDynCubeObj);
            ShadowVolume_isShadowLayerRegistered = true;
          }
          ptMiddle = (struct real32x3_t *)a1[6].tQTaskChildren.ptMiddle;
          if ( ptMiddle )
          {
            igi2_frame.v12 = 0;
            if ( (int)a1[6].tQTaskChildren.ptTail->tQTaskChildren.ptHead > 0 )
            {
              v8 = nullptr;
              a1a = nullptr;
              do
              {
                v9 = *(int *)((char *)&a1[6].tQTaskChildren.ptTail->tQTaskChildren.ptMiddle->tQTaskRefList.ptMiddle
                            + (unsigned int)v8);
                if ( v9 == -1 )
                {
                  sub_5C3F70((float *)&a1[2].eQTaskType, &igi2_frame.a2, (double *)&a1[1]);
                  sub_5C4510(
                    (int)a1,
                    (int *)((char *)v8 + (unsigned int)a1[6].tQTaskChildren.ptTail->tQTaskChildren.ptMiddle),
                    &igi2_frame.a2);
                }
                else
                {
                  BoneDynCubeObj_GetBonePosition((struct BoneDynCubeObj_s *)&igi2_frame.ptRotatedPos, ptMiddle, v9);
                  BoneDynCubeObj_GetBoneWorldPositionFromName((struct BoneDynCubeObj_s *)ptMiddle, v9, igi2_frame.a3);
                  sub_5C3F70(igi2_frame.a3, &igi2_frame.a2, (double *)&igi2_frame.ptRotatedPos.vX);
                  v8 = a1a;
                  sub_5C4510(
                    (int)a1,
                    (int *)((char *)a1a + (unsigned int)a1[6].tQTaskChildren.ptTail->tQTaskChildren.ptMiddle),
                    &igi2_frame.a2);
                }
                v8 = (struct QTask_s *)((char *)v8 + 28);
                v10 = ++igi2_frame.v12 < (int)a1[6].tQTaskChildren.ptTail->tQTaskChildren.ptHead;
                a1a = v8;
              }
              while ( v10 );
            }
            ShadowVolume_nBonePolygons = ShadowVolume_nPolygons;
          }
          else
          {
            sub_5C3F70((float *)&a1[2].eQTaskType, &igi2_frame.a2, (double *)&a1[1]);
            if ( (int)a1[6].tQTaskChildren.ptTail->tQTaskChildren.ptHead > 0 )
            {
              v7 = 0;
              do
              {
                sub_5C4510((int)a1, (int *)((char *)a1[6].tQTaskChildren.ptTail->tQTaskChildren.ptMiddle + v7), &igi2_frame.a2);
                ptMiddle = (struct real32x3_t *)((char *)ptMiddle + 1);
                v7 += 28;
              }
              while ( (int)ptMiddle < (int)a1[6].tQTaskChildren.ptTail->tQTaskChildren.ptHead );
            }
          }
        }
      }
    }
  }
}

void __cdecl sub_5C5100(struct QTask_s *ptQTask, char *a2)
{
  struct QTask_s *ShadowVolumePtrByName; // eax
  struct QReference_s *v3; // eax

  memset(&ptQTask[1], 0, 0x48u);
  ptQTask[2].tQTaskRefList.ptTail = (struct QReference_s *)5;
  ptQTask[6].ptPrev = (struct QTask_s *)1;
  ptQTask[6].tQTaskChildren.ptHead = (struct QTask_s *)1;
  ptQTask[6].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[6].ptNext = (struct QTask_s *)1201668096;
  *(_DWORD *)&ptQTask[5].eQTaskType = 1178599424;
  if ( *((_DWORD *)a2 + 35) == 1 )
  {
    ptQTask[2].ptParent = *((struct QTask_s **)a2 + 1);
    qmemcpy(&ptQTask[3].eQTaskType, a2 + 84, sizeof(struct QTask_s));
    *(_DWORD *)&ptQTask[4].eQTaskType = *((_DWORD *)a2 + 8);
    ptQTask[5].ptNext = *((struct QTask_s **)a2 + 9);
    ptQTask[5].ptPrev = *((struct QTask_s **)a2 + 10);
    qmemcpy(&ptQTask[2].eQTaskType, a2 + 44, sizeof(struct QTask_s));
    memset(&ptQTask[5].tQTaskChildren, 0, 0x1Cu);
    QTask_TriggerQTaskEventParent(ptQTask, Attach_eAttachEvent, &ptQTask[5].tQTaskChildren);
    ShadowVolumePtrByName = (struct QTask_s *)MTP_GetShadowVolumePtrByName(*(char **)a2);
    ptQTask[6].tQTaskChildren.ptTail = ShadowVolumePtrByName;
    if ( ShadowVolumePtrByName )
    {
      v3 = (struct QReference_s *)(*(_DWORD *)(*((_DWORD *)a2 + 31) + 108) - 1);
      ptQTask[2].tQTaskRefList.ptTail = v3;
      if ( (int)v3 >= 0 )
        sub_5C4B80((int)ptQTask, *((_DWORD *)a2 + 36));
      else
        ptQTask[6].tQTaskChildren.ptTail = nullptr;
    }
  }
  else
  {
    ptQTask[6].tQTaskChildren.ptTail = nullptr;
  }
}

void __cdecl sub_5C5200(struct DynCubeObj_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct QTask_s *ptTail; };
    struct { char igi2_o1[24]; float v14; };
    struct { char igi2_o2[28]; _BYTE ptNewPos[40]; };
    char igi2_extent[68];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  bool v1; // zf
  enum DynCubeRenderGroup_e iRenderGroup; // eax
  double v3; // st7
  double v4; // st6
  int v5; // ecx
  void *pxQData; // edx
  double v7; // st5
  double v8; // st4
  int v9; // eax
  double v10; // st4
  struct QTask_s *ptNext; // edx
  double *ptSector; // eax

  if ( ShadowVolume_isEnabled && ptQTask[2].tQObj.tQTask.ptParent )
  {
    v1 = SkyDome_ptDirlight == nullptr;
    ptQTask[2].tQObj.tQTask.tQTaskRefList.ptTail = nullptr;
    ptQTask[2].tQObj.tQTask.tQTaskRefList.ptMiddle = nullptr;
    if ( !v1 )
    {
      QTask_TriggerQTaskEventParent(
        &ptQTask->tQObj.tQTask,
        ShadowVolume_eGetShadowInfoEvent,
        &ptQTask[2].tQObj.tQTask.tQTaskChildren.ptMiddle);
      ptQTask[2].tQObj.tQTask.tQTaskRefList.ptHead = nullptr;
    }
    if ( ptQTask[2].tQObj.tQTask.tQTaskRefList.ptMiddle )
    {
      iRenderGroup = ptQTask[1].iRenderGroup;
      v3 = *(float *)iRenderGroup * *((float *)&ptQTask[1].tQObj.pxQData + 1)
         + *(float *)(iRenderGroup + 8) * *(float *)&ptQTask[1].ptPrev
         + *(float *)(iRenderGroup + 4) * *(float *)&ptQTask[1].ptDynCubeObjTreeItem;
      v4 = *(float *)(iRenderGroup + 16) * *(float *)&ptQTask[1].ptDynCubeObjTreeItem
         + *(float *)(iRenderGroup + 20) * *(float *)&ptQTask[1].ptPrev
         + *(float *)(iRenderGroup + 12) * *((float *)&ptQTask[1].tQObj.pxQData + 1);
      igi2_frame.v14 = *(float *)&ptQTask[1].ptPrev * *(float *)(iRenderGroup + 32)
          + *((float *)&ptQTask[1].tQObj.pxQData + 1) * *(float *)(iRenderGroup + 24)
          + *(float *)(iRenderGroup + 28) * *(float *)&ptQTask[1].ptDynCubeObjTreeItem;
      *(float *)igi2_frame.ptNewPos = *(float *)(iRenderGroup + 8) * ptQTask[1].tQObj.vRangeY
                         + *(float *)(iRenderGroup + 4) * *(float *)&ptQTask[1].tQObj.tPos.vZ
                         + *((float *)&ptQTask[1].tQObj.tPos.vX + 1) * *(float *)iRenderGroup;
      *(float *)&igi2_frame.ptNewPos[4] = *(float *)(iRenderGroup + 8) * ptQTask[1].tQObj.vRangeZ
                             + *(float *)(iRenderGroup + 4) * *((float *)&ptQTask[1].tQObj.tPos.vZ + 1)
                             + *(float *)&ptQTask[1].tQObj.tPos.vY * *(float *)iRenderGroup;
      *(float *)&igi2_frame.ptNewPos[8] = *(float *)(iRenderGroup + 8) * ptQTask[1].tQObj.vRealRadius
                             + *(float *)(iRenderGroup + 4) * ptQTask[1].tQObj.vRangeX
                             + *((float *)&ptQTask[1].tQObj.tPos.vY + 1) * *(float *)iRenderGroup;
      *(float *)&igi2_frame.ptNewPos[12] = *(float *)(iRenderGroup + 16) * *(float *)&ptQTask[1].tQObj.tPos.vZ
                              + *(float *)(iRenderGroup + 20) * ptQTask[1].tQObj.vRangeY
                              + *(float *)(iRenderGroup + 12) * *((float *)&ptQTask[1].tQObj.tPos.vX + 1);
      *(float *)&igi2_frame.ptNewPos[16] = *(float *)(iRenderGroup + 16) * *((float *)&ptQTask[1].tQObj.tPos.vZ + 1)
                              + *(float *)(iRenderGroup + 20) * ptQTask[1].tQObj.vRangeZ
                              + *(float *)(iRenderGroup + 12) * *(float *)&ptQTask[1].tQObj.tPos.vY;
      v5 = *(_DWORD *)(iRenderGroup + 36);
      pxQData = ptQTask[1].tQObj.pxQData;
      *(float *)&igi2_frame.ptNewPos[20] = *(float *)(iRenderGroup + 16) * ptQTask[1].tQObj.vRangeX
                              + *(float *)(iRenderGroup + 20) * ptQTask[1].tQObj.vRealRadius
                              + *(float *)(iRenderGroup + 12) * *((float *)&ptQTask[1].tQObj.tPos.vY + 1);
      *(float *)&igi2_frame.ptNewPos[24] = ptQTask[1].tQObj.vRangeY * *(float *)(iRenderGroup + 32)
                              + *((float *)&ptQTask[1].tQObj.tPos.vX + 1) * *(float *)(iRenderGroup + 24)
                              + *(float *)(iRenderGroup + 28) * *(float *)&ptQTask[1].tQObj.tPos.vZ;
      *(float *)&igi2_frame.ptNewPos[28] = ptQTask[1].tQObj.vRangeZ * *(float *)(iRenderGroup + 32)
                              + *(float *)&ptQTask[1].tQObj.tPos.vY * *(float *)(iRenderGroup + 24)
                              + *(float *)(iRenderGroup + 28) * *((float *)&ptQTask[1].tQObj.tPos.vZ + 1);
      v7 = ptQTask[1].tQObj.vRealRadius * *(float *)(iRenderGroup + 32)
         + *((float *)&ptQTask[1].tQObj.tPos.vY + 1) * *(float *)(iRenderGroup + 24);
      v8 = *(float *)(iRenderGroup + 28);
      v9 = (int)pxQData + v5 + 1;
      v10 = v8 * ptQTask[1].tQObj.vRangeX;
      ptNext = ptQTask[1].tQObj.tQTask.ptNext;
      *(_DWORD *)&igi2_frame.ptNewPos[36] = v9;
      ptSector = (double *)ptQTask[1].ptSector;
      *(float *)&igi2_frame.ptNewPos[32] = v7 + v10;
      qmemcpy(&ptQTask[1].tQObj.tQTask.ptPrev, igi2_frame.ptNewPos, 0x28u);
      *(double *)igi2_frame.ptNewPos = v3 + *ptSector;
      *(double *)&igi2_frame.ptNewPos[8] = v4 + ptSector[1];
      igi2_frame.ptTail = ptQTask[2].tQObj.tQTask.tQTaskChildren.ptTail;
      *(double *)&igi2_frame.ptNewPos[16] = igi2_frame.v14 + ptSector[2];
      World_MoveDynCubeObjRadius((struct World_s *)ptNext, ptQTask, (struct real64x3_t *)igi2_frame.ptNewPos, *(float *)&igi2_frame.ptTail);
    }
  }
}

void __cdecl sub_5C5460(struct DynCubeObj_s *a1)
{
  World_RemoveDynCubeObj((struct World_s *)a1[1].tQObj.tQTask.ptNext, a1);
}

void __cdecl sub_5C5470(struct QTask_s *a1)
{
  sub_5C4B80((int)a1, 1);
}

void __cdecl sub_5C5490(struct DynCubeObj_s *a1)
{
  World_RemoveDynCubeObj((struct World_s *)a1[1].tQObj.tQTask.ptNext, a1);
}

void __cdecl sub_5C54A0()
{
  ShadowVolume_iStartIndex = 0;
  ShadowVolume_nActiveVolumes = 0;
  ShadowVolume_isShadowLayerRegistered = false;
}

void __cdecl sub_5C54C0()
{
  ShadowVolume_ptProtectRequestVector->nAllocated = 0;
}

void __cdecl sub_5C54D0()
{
  struct IDirect3DDevice8Vtbl *lpVtbl; // ecx

  ShadowVolume_ptIndexBuffer = nullptr;
  ShadowVolume_ptVertexBuffer = nullptr;
  Direct3D_ptDevice->lpVtbl->CreateIndexBuffer(
    Direct3D_ptDevice,
    2 * ShadowVolume_nIndexBufferSize,
    520u,
    D3DFMT_INDEX16,
    D3DPOOL_DEFAULT,
    &ShadowVolume_ptIndexBuffer);
  Direct3D_ptDevice->lpVtbl->CreateVertexBuffer(
    Direct3D_ptDevice,
    12 * ShadowVolume_nVertexBufferSize,
    520u,
    2u,
    D3DPOOL_DEFAULT,
    &ShadowVolume_ptVertexBuffer);
  lpVtbl = Direct3D_ptDevice->lpVtbl;
  ShadowVolume_iStartIndex = 0;
  ShadowVolume_iStartVertex = 0;
  lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_STENCILPASS, 3u);
  Direct3D_ptDevice->lpVtbl->SetRenderState(Direct3D_ptDevice, D3DRS_STENCILREF, 0);
}

void __cdecl sub_5C5560()
{
  if ( ShadowVolume_ptIndexBuffer )
  {
    ShadowVolume_ptIndexBuffer->lpVtbl->Release(ShadowVolume_ptIndexBuffer);
    ShadowVolume_ptIndexBuffer = nullptr;
    ShadowVolume_iStartIndex = 0;
  }
  if ( ShadowVolume_ptVertexBuffer )
  {
    ShadowVolume_ptVertexBuffer->lpVtbl->Release(ShadowVolume_ptVertexBuffer);
    ShadowVolume_ptVertexBuffer = nullptr;
    ShadowVolume_iStartVertex = 0;
  }
}

void __cdecl sub_5C55A0()
{
  if ( ShadowVolume_ptIndexBuffer )
  {
    ShadowVolume_ptIndexBuffer->lpVtbl->Release(ShadowVolume_ptIndexBuffer);
    ShadowVolume_ptIndexBuffer = nullptr;
    ShadowVolume_iStartIndex = 0;
  }
  if ( ShadowVolume_ptVertexBuffer )
  {
    ShadowVolume_ptVertexBuffer->lpVtbl->Release(ShadowVolume_ptVertexBuffer);
    ShadowVolume_ptVertexBuffer = nullptr;
    ShadowVolume_iStartVertex = 0;
  }
}

// attributes: thunk
void __cdecl sub_5C55E0()
{
  sub_5C54D0();
}

int __cdecl sub_5C5600(int a2, int *a3, int a4, float *a5)
{
  int result; // eax
  int v5; // ebx
  int v6; // edi
  int *v7; // ebp
  int v8; // edi
  _WORD *v9; // eax
  int *v10; // ebx
  int v11; // eax
  int v12; // ecx
  char v13[4]; // [esp+30h] [ebp-4h] BYREF

  result = ShadowVolume_isEnabled;
  v5 = 0;
  if ( ShadowVolume_isEnabled )
  {
    result = (int)SkyDome_ptDirlight;
    if ( SkyDome_ptDirlight )
    {
      result = *a3;
      if ( *a3 )
      {
        (*(void (__stdcall **)(int))(*(_DWORD *)result + 8))(result);
        result = 0;
        memset(a3, 0, 0x2Cu);
      }
      if ( a2 )
      {
        v6 = 0;
        if ( *(__int16 *)(a2 + 60) > 0 )
        {
          v7 = a3 + 1;
          do
          {
            *v7 = v5;
            v5 += sub_5C4110(*(_DWORD *)(*(_DWORD *)(*(_DWORD *)(a2 + 4 * v6) + 12) + 12), a5, a4, nullptr);
            result = *(__int16 *)(a2 + 60);
            ++v6;
            ++v7;
          }
          while ( v6 < result );
          if ( v5 > 0 )
          {
            result = Direct3D_ptDevice->lpVtbl->CreateIndexBuffer(
                       Direct3D_ptDevice,
                       2 * v5,
                       8u,
                       D3DFMT_INDEX16,
                       D3DPOOL_MANAGED,
                       (struct IDirect3DIndexBuffer8 **)a3);
            if ( !result )
            {
              (*(void (__stdcall **)(int, _DWORD, _DWORD, char *, _DWORD))(*(_DWORD *)*a3 + 44))(*a3, 0, 0, v13, 0);
              v8 = 0;
              if ( *(__int16 *)(a2 + 60) > 0 )
              {
                v9 = *(_WORD **)v13;
                v10 = a3 + 6;
                do
                {
                  v11 = sub_5C4110(*(_DWORD *)(*(_DWORD *)(*(_DWORD *)(a2 + 4 * v8) + 12) + 12), a5, a4, v9);
                  *v10 = v11 / 3;
                  v9 = (_WORD *)(*(_DWORD *)v13 + 2 * v11);
                  v12 = *(__int16 *)(a2 + 60);
                  ++v8;
                  ++v10;
                  *(_DWORD *)v13 = v9;
                }
                while ( v8 < v12 );
              }
              return (*(int (__stdcall **)(int))(*(_DWORD *)*a3 + 48))(*a3);
            }
          }
        }
      }
    }
  }
  return result;
}
