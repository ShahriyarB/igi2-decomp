/* h/2/bsptreeedit.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: h/2/bsptreeedit.c:59  [anchor-mhash]
void __cdecl BspTreeEdit_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  ptQTask[2].ptParent = nullptr;
  ptQTask[3].ptPrev = nullptr;
  *(_DWORD *)&ptQTask[2].eQTaskType = 0;
  ptQTask[3].ptNext = nullptr;
  ptQTask[3].ptParent = nullptr;
  *(_DWORD *)&ptQTask[3].eQTaskType = 0;
  strcpy((char *)&ptQTask[5].ptPrev, "ChangeThis.bsp");
  BspTreeDynCubeObj_ptTree = (struct BspTreeDynCubeObj_s *)ptQTask;
  ptQTask[4].ptNext = nullptr;
  ptQTask[4].ptPrev = nullptr;
  ptQTask[4].tQTaskChildren.ptHead = nullptr;
  ptQTask[4].tQTaskChildren.ptMiddle = nullptr;
  ptQTask[4].tQTaskChildren.ptTail = nullptr;
  ptQTask[4].tQTaskRefList.ptHead = nullptr;
  ptQTask[4].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[4].tQTaskRefList.ptTail = nullptr;
  ptQTask[4].ptParent = nullptr;
  LOBYTE(ptQTask[4].eQTaskType) = 0;
  ptQTask[5].ptNext = nullptr;
}

// source: h/2/bsptreeedit.c:93  [size]
void __cdecl BspTreeEdit_DeleteHandler(struct QTask_s *ptQTask)
{
  ((void (__cdecl *)())QTask_aatQTaskFinalEvent[2][BspTreeDynCubeObj_eQTaskType].pfHandler)(ptQTask);
}

// source: h/2/bsptreeedit.c:120  [size]
void __cdecl BspTreeEdit_GetParameterListHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *(_DWORD *)pxContext = BspTreeEdit_ptParameterList;
}

// source: h/2/bsptreeedit.c:140  [anchor-caller]
void __cdecl BspTreeEdit_UpdateInternalDataHandler(struct QTask_s *ptQTask, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { char v5; };
    struct { char igi2_o1[1]; char zString[104]; };
    char igi2_extent[105];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  unsigned int v2; // eax
  char *v3; // edi

  strcpy(igi2_frame.zString, "LOCAL:");
  memset(&igi2_frame.zString[7], 0, 93);
  v2 = strlen((char *)&ptQTask[5].ptPrev) + 1;
  v3 = &igi2_frame.v5;
  while ( *++v3 )
    ;
  qmemcpy(v3, &ptQTask[5].ptPrev, v2);
  BspTreeDynCubeObj_Load((struct BspTreeDynCubeObj_s *)ptQTask, igi2_frame.zString);
}

// source: h/2/bsptreeedit.c:333  [anchor-hash]
void __cdecl BspTreeEdit_Open()
{
  unsigned __int16 v0; // si
  struct ParameterList_s *v1; // eax
  int v2; // edx

  v0 = QTask_NewQTaskType("BspTreeEdit", 240, BspTreeDynCubeObj_eQTaskType, 0, 0);
  BspTreeEdit_eQTaskType = v0;
  QTask_LinkQTaskEventHandlerFn(v0, 0, BspTreeEdit_CreateHandler);
  QTask_LinkQTaskEventHandlerFn(v0, ParameterList_eUpdateInternalDataQTaskEvent, BspTreeEdit_UpdateInternalDataHandler);
  QTask_LinkQTaskEventHandlerFn(
    v0,
    ParameterList_eGetParameterListQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))BspTreeEdit_GetParameterListHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v0, 2, (void (__cdecl *)(struct QTask_s *))BspTreeEdit_DeleteHandler);
  v1 = (struct ParameterList_s *)Mem_AllocFn(92, 4);
  v2 = Level_eParameterTypeObjectPos;
  v1->ptParameterListItem = (struct ParameterListItem_s *)&v1[1];
  v1->nParameters = 0;
  v1->nMaxParameters = 4;
  BspTreeEdit_ptParameterList = v1;
  ParameterList_AddParameter(v1, 0xA0u, v2, off_68D890, 7u, nullptr);
  ParameterList_AddParameter(BspTreeEdit_ptParameterList, 0xB8u, Level_eParameterTypeReal32x3, "Size", 7u, nullptr);
  ParameterList_AddParameter(
    BspTreeEdit_ptParameterList,
    0xC4u,
    Level_eParameterTypePushButton,
    "Generate",
    7u,
    nullptr);
  ParameterList_AddParameter(BspTreeEdit_ptParameterList, 0xCCu, Level_eParameterTypeString32, "FileName", 7u, nullptr);
  QTask_LinkQTaskEventHandlerFn(
    BspTreeEdit_eQTaskType,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveNoChildrenHandler);
}

// source: h/2/bsptreeedit.c:370  [size]
void __cdecl BspTreeEdit_Close()
{
  int v0; // esi

  if ( BspTreeEdit_ptParameterList )
  {
    v0 = *(_DWORD *)((unsigned int)&BspTreeEdit_ptParameterList[-1].ptParameterListItem & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v0);
    memset(*(void **)(v0 + 8), 0xCDu, *(_DWORD *)(v0 + 16));
    free((void *)v0);
  }
  QTask_DeleteQTaskType(BspTreeEdit_eQTaskType);
  BspTreeEdit_eQTaskType = 512;
}

// source: h/2/bsptreeedit.c:390  [size]
struct BspTreeEdit_s *__cdecl BspTreeEdit_New(struct QTask_s *ptParent)
{
  return (struct BspTreeEdit_s *)QTask_NewFn(ptParent, BspTreeEdit_eQTaskType, nullptr);
}

// source: h/2/bsptreeedit.c:410  [size]
unsigned __int16 __cdecl BspTreeEdit_GetQTaskType()
{
  return BspTreeEdit_eQTaskType;
}

// source: h/2/bsptreeedit.c:430  [anchor-caller]
void __cdecl BspTreeEdit_Test()
{
  #pragma pack(push, 1)
  union
  {
    struct { unsigned __int8 aunMaterialIndex[8]; };
    struct { char igi2_o1[8]; float avScoreList[4]; };
    struct { char igi2_o2[24]; struct real32x3_t atEdge[2]; };
    struct { char igi2_o3[48]; struct real32x3_t atNormals[4]; };
    struct { char igi2_o4[96]; unsigned int aunTriangleVertIndex[12]; };
    struct { char igi2_o5[144]; struct real64x3_t atVertex[12]; };
    char igi2_extent[432];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  double *p_vY; // esi
  int v1; // edi
  int v2; // ebx
  unsigned int v3; // esi
  int v4; // ebp
  int v5; // edi
  int v6; // edx
  int v7; // eax
  int v8; // ecx
  double v9; // st7
  struct real64x3_t *v10; // edi
  double *v11; // ebp
  double v12; // st6
  double *p_vZ; // ecx
  double v14; // st5
  double vX; // st4
  double v16; // st4
  double v17; // st4
  struct real32x3_t *v18; // ecx
  long double v19; // st4
  struct QTask_s *v20; // esi

  srand(0);
  p_vY = &igi2_frame.atVertex[0].vY;
  v1 = 12;
  do
  {
    *(p_vY - 1) = (double)rand() * 3.0518509447574615e-05 * 100.0;
    *p_vY = (double)rand() * 3.0518509447574615e-05 * 100.0;
    *(_DWORD *)igi2_frame.aunMaterialIndex = rand();
    p_vY += 3;
    --v1;
    *(p_vY - 2) = (double)*(int *)igi2_frame.aunMaterialIndex * 3.0518509447574615e-05 * 100.0;
  }
  while ( v1 );
  v2 = 0;
  v3 = 0;
  while ( 1 )
  {
    *(_QWORD *)igi2_frame.aunMaterialIndex = (__int64)((double)rand() * 3.0518509447574615e-05 * 12.0);
    v4 = *(_DWORD *)igi2_frame.aunMaterialIndex;
    igi2_frame.aunTriangleVertIndex[v3 / 4] = *(_DWORD *)igi2_frame.aunMaterialIndex;
    do
    {
      *(_QWORD *)igi2_frame.aunMaterialIndex = (__int64)((double)rand() * 3.0518509447574615e-05 * 12.0);
      v5 = *(_DWORD *)igi2_frame.aunMaterialIndex;
    }
    while ( *(_DWORD *)igi2_frame.aunMaterialIndex == v4 );
    igi2_frame.aunTriangleVertIndex[v3 / 4 + 1] = *(_DWORD *)igi2_frame.aunMaterialIndex;
    do
    {
      do
      {
        *(_QWORD *)igi2_frame.aunMaterialIndex = (__int64)((double)rand() * 3.0518509447574615e-05 * 12.0);
        v6 = *(_DWORD *)igi2_frame.aunMaterialIndex;
      }
      while ( *(_DWORD *)igi2_frame.aunMaterialIndex == v5 );
    }
    while ( *(_DWORD *)igi2_frame.aunMaterialIndex == v4 );
    v7 = v5;
    v8 = v4;
    v9 = igi2_frame.atVertex[v5].vX - igi2_frame.atVertex[v4].vX;
    v10 = &igi2_frame.atVertex[v4];
    v11 = &igi2_frame.atVertex[v4].vY;
    v12 = igi2_frame.atVertex[v7].vY - *v11;
    p_vZ = &igi2_frame.atVertex[v8].vZ;
    v14 = igi2_frame.atVertex[v7].vZ - *p_vZ;
    vX = igi2_frame.atVertex[*(_DWORD *)igi2_frame.aunMaterialIndex].vX;
    igi2_frame.aunTriangleVertIndex[v3 / 4 + 2] = *(_DWORD *)igi2_frame.aunMaterialIndex;
    v16 = vX - v10->vX;
    igi2_frame.aunMaterialIndex[v2] = 0;
    igi2_frame.atEdge[1].vX = v16;
    igi2_frame.atEdge[1].vY = igi2_frame.atVertex[v6].vY - *v11;
    v17 = igi2_frame.atVertex[v6].vZ - *p_vZ;
    v18 = &igi2_frame.atNormals[v3 / 0xC];
    igi2_frame.avScoreList[0] = v17 * v12 - igi2_frame.atEdge[1].vY * v14;
    v18->vX = igi2_frame.avScoreList[0];
    igi2_frame.avScoreList[1] = -(v17 * v9 - igi2_frame.atEdge[1].vX * v14);
    v18->vY = igi2_frame.avScoreList[1];
    igi2_frame.avScoreList[2] = igi2_frame.atEdge[1].vY * v9 - igi2_frame.atEdge[1].vX * v12;
    v18->vZ = igi2_frame.avScoreList[2];
    v19 = sqrt(
            igi2_frame.atNormals[v3 / 0xC].vX * igi2_frame.atNormals[v3 / 0xC].vX
          + igi2_frame.atNormals[v3 / 0xC].vY * igi2_frame.atNormals[v3 / 0xC].vY
          + igi2_frame.atNormals[v3 / 0xC].vZ * igi2_frame.atNormals[v3 / 0xC].vZ);
    if ( v19 != 0.0 )
    {
      v3 += 12;
      ++v2;
      v18->vX = 1.0 / v19 * v18->vX;
      igi2_frame.atEdge[v3 / 0xC + 1].vY = 1.0 / v19 * igi2_frame.atEdge[v3 / 0xC + 1].vY;
      igi2_frame.atEdge[v3 / 0xC + 1].vZ = 1.0 / v19 * igi2_frame.atEdge[v3 / 0xC + 1].vZ;
      if ( v3 >= 0x30 )
        break;
    }
  }
  BspTreeDynCubeObj_ptTree = nullptr;
  v20 = QTask_NewFn(nullptr, BspTreeEdit_eQTaskType, nullptr);
  BspTreeDynCubeObj_GenerateScoreList2(
    0xCu,
    igi2_frame.atVertex,
    0xCu,
    igi2_frame.aunTriangleVertIndex,
    igi2_frame.aunMaterialIndex,
    igi2_frame.atNormals,
    igi2_frame.avScoreList);
  QTask_Delete(v20);
}
