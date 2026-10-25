/* h/2/physicsobjtype.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: h/2/physicsobjtype.c:46  [anchor-callee]
void __cdecl PhysicsObjType_GetSizeFromModel(struct PhysicsObjType_s *ptType)
{
  struct LODVirModel_s *LODVirModelExistsFn; // eax
  double v2; // st7
  struct Mesh3D_Mesh_t *ptMesh; // edx
  int nCollPoint; // edi
  struct PhysicsObjTypeCollPoint_s *atCollPoint; // ecx
  float *p_vX; // eax
  double v7; // st6
  double v8; // st6
  double v9; // st7
  float tPos; // [esp+Ch] [ebp-40h]
  float tPos_4; // [esp+10h] [ebp-3Ch]
  float tPos_8; // [esp+14h] [ebp-38h]
  double tMaxXYZ; // [esp+18h] [ebp-34h]
  double tMaxXYZ_8; // [esp+20h] [ebp-2Ch]
  double tMaxXYZ_16; // [esp+28h] [ebp-24h]
  double tMinXYZ; // [esp+30h] [ebp-1Ch]
  double tMinXYZ_8; // [esp+38h] [ebp-14h]

  tMinXYZ = 1.7976931348623157e+308;
  tMinXYZ_8 = 1.7976931348623157e+308;
  tMaxXYZ = -1.7976931348623157e+308;
  tMaxXYZ_8 = -1.7976931348623157e+308;
  tMaxXYZ_16 = -1.7976931348623157e+308;
  LODVirModelExistsFn = MTP_GetLODVirModelExistsFn(ptType->zModel);
  v2 = 1.7976931348623157e+308;
  if ( ptType->nCollPoint > 0 )
  {
    ptMesh = LODVirModelExistsFn->aptVirModel[0]->ptModel->ptMesh;
    nCollPoint = ptType->nCollPoint;
    atCollPoint = ptType->atCollPoint;
    do
    {
      if ( atCollPoint->iMagicVertex < (unsigned int)ptMesh->nMagicVertex
        && (p_vX = &ptMesh->ptMagicVertex[atCollPoint->iMagicVertex].tPos.vX) != nullptr )
      {
        tPos = *p_vX;
        tPos_4 = p_vX[1];
        tPos_8 = p_vX[2];
      }
      else
      {
        tPos = 0.0;
        tPos_4 = 0.0;
        tPos_8 = 0.0;
      }
      if ( tPos < tMinXYZ )
        tMinXYZ = tPos;
      if ( tPos_4 < tMinXYZ_8 )
        tMinXYZ_8 = tPos_4;
      if ( tPos_8 < v2 )
        v2 = tPos_8;
      if ( tPos > tMaxXYZ )
        tMaxXYZ = tPos;
      if ( tPos_4 > tMaxXYZ_8 )
        tMaxXYZ_8 = tPos_4;
      if ( tPos_8 > tMaxXYZ_16 )
        tMaxXYZ_16 = tPos_8;
      ++atCollPoint;
      --nCollPoint;
    }
    while ( nCollPoint );
  }
  v7 = tMaxXYZ - tMinXYZ;
  if ( tMaxXYZ - tMinXYZ < 0.0 )
    v7 = -v7;
  ptType->tSize.vX = v7;
  v8 = tMaxXYZ_8 - tMinXYZ_8;
  if ( tMaxXYZ_8 - tMinXYZ_8 < 0.0 )
    v8 = -v8;
  ptType->tSize.vY = v8;
  v9 = tMaxXYZ_16 - v2;
  if ( v9 < 0.0 )
    v9 = -v9;
  ptType->tSize.vZ = v9;
}

// source: h/2/physicsobjtype.c:95  [anchor-strings]
struct Result_s *__cdecl PhysicsObjType_DefinePhysicsObjTypeCB(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  #pragma pack(push, 1)
  union
  {
    struct { int iPhysicsObj; };
    struct { char igi2_o1[4]; char *pxDataa; };
    struct { char igi2_o2[8]; char ArgList[4]; };
    struct { char igi2_o3[12]; float v41; };
    struct { char igi2_o4[16]; float v42; };
    struct { char igi2_o5[20]; float v43; };
    struct { char igi2_o6[24]; int iCollPoint; };
    struct { char igi2_o7[28]; struct PhysicsObjType_s *ptType; };
    struct { char igi2_o8[32]; struct ParsePhysicsObjTypeContext_s tParsePhysicsObjTypeContext[2]; };
    char igi2_extent[56];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct PhysicsObjType_s *v3; // ebx
  bool v4; // zf
  unsigned __int16 v5; // ax
  int v6; // eax
  double v7; // st7
  double v8; // st7
  double v9; // st7
  double v10; // st7
  int isQVM; // ecx
  char *zModel; // esi
  bool v13; // cc
  char *v14; // eax
  int v15; // esi
  int *p_iType; // ebx
  char *v17; // eax
  int v18; // esi
  int v19; // eax
  int v20; // esi
  int v21; // eax
  int v22; // esi
  double v23; // st7
  int v24; // esi
  double v25; // st7
  int v26; // esi
  double v27; // st7
  int v28; // eax
  int nCollPoint; // edx
  double v30; // st7
  int v31; // esi
  double v32; // st7
  int v33; // edx
  void (__cdecl *pfHandler)(_DWORD, struct PhysicsObjType_s **); // eax
  void *v35; // eax
  int eQTaskType; // ecx

  v3 = (struct PhysicsObjType_s *)(728 * PhysicsObjType_nType + 7510696);
  v3->pxData = nullptr;
  v4 = ptArgList->isQVM == 0;
  igi2_frame.ptType = v3;
  if ( v4 )
  {
    v5 = Expression_EvalInt(*ptArgList->aptExpression);
  }
  else
  {
    *(float *)&igi2_frame.iPhysicsObj = 0.0;
    QVM_EvalArg(&igi2_frame.iPhysicsObj, 4, ptArgList, 0, 1);
    v5 = igi2_frame.iPhysicsObj;
  }
  v3->eQTaskType = v5;
  if ( ptArgList->isQVM )
  {
    *(float *)&igi2_frame.iPhysicsObj = 0.0;
    QVM_EvalArg(&igi2_frame.iPhysicsObj, 4, ptArgList, 1, 1);
    v6 = igi2_frame.iPhysicsObj;
  }
  else
  {
    v6 = Expression_EvalInt(ptArgList->aptExpression[1]);
  }
  v3->nID = v6;
  if ( ptArgList->isQVM )
  {
    *(float *)&igi2_frame.iPhysicsObj = 0.0;
    QVM_EvalArg(&igi2_frame.iPhysicsObj, 4, ptArgList, 2, 2);
    v7 = *(float *)&igi2_frame.iPhysicsObj;
  }
  else
  {
    v7 = Expression_EvalFloat((struct QExpression_s *)*((_DWORD *)ptArgList->aptExpression + 2));
  }
  v3->vMass = v7;
  if ( ptArgList->isQVM )
  {
    *(float *)&igi2_frame.iPhysicsObj = 0.0;
    QVM_EvalArg(&igi2_frame.iPhysicsObj, 4, ptArgList, 3, 2);
    v8 = *(float *)&igi2_frame.iPhysicsObj;
  }
  else
  {
    v8 = Expression_EvalFloat((struct QExpression_s *)*((_DWORD *)ptArgList->aptExpression + 3));
  }
  v3->tSize.vX = v8;
  if ( ptArgList->isQVM )
  {
    *(float *)&igi2_frame.iPhysicsObj = 0.0;
    QVM_EvalArg(&igi2_frame.iPhysicsObj, 4, ptArgList, 4, 2);
    v9 = *(float *)&igi2_frame.iPhysicsObj;
  }
  else
  {
    v9 = Expression_EvalFloat((struct QExpression_s *)*((_DWORD *)ptArgList->aptExpression + 4));
  }
  v3->tSize.vY = v9;
  if ( ptArgList->isQVM )
  {
    *(float *)&igi2_frame.iPhysicsObj = 0.0;
    QVM_EvalArg(&igi2_frame.iPhysicsObj, 4, ptArgList, 5, 2);
    v10 = *(float *)&igi2_frame.iPhysicsObj;
  }
  else
  {
    v10 = Expression_EvalFloat((struct QExpression_s *)*((_DWORD *)ptArgList->aptExpression + 5));
  }
  v3->tSize.vZ = v10;
  if ( ptArgList->isQVM )
  {
    v3->zName[0] = 0;
    QVM_EvalArg(v3->zName, 32, ptArgList, 6, 3);
  }
  else
  {
    Expression_EvalString(ptArgList->aptExpression[6], v3->zName, 32);
  }
  if ( ptArgList->isQVM )
  {
    v3->zDesc[0] = 0;
    QVM_EvalArg(v3->zDesc, 256, ptArgList, 7, 3);
  }
  else
  {
    Expression_EvalString(ptArgList->aptExpression[7], v3->zDesc, 256);
  }
  isQVM = ptArgList->isQVM;
  *(_DWORD *)igi2_frame.ArgList = v3->zModel;
  if ( isQVM )
  {
    v3->zModel[0] = 0;
    QVM_EvalArg(v3->zModel, 16, ptArgList, 8, 3);
  }
  else
  {
    Expression_EvalString(ptArgList->aptExpression[8], v3->zModel, 16);
  }
  *(float *)&igi2_frame.iPhysicsObj = 0.0;
  if ( PhysicsObjType_nType > 0 )
  {
    zModel = PhysicsObjType_atPhysicsObjType[0].zModel;
    igi2_frame.pxDataa = PhysicsObjType_atPhysicsObjType[0].zModel;
    do
    {
      if ( !strcmp(*(char **)igi2_frame.ArgList, zModel) )
      {
        LDebug_Error("Physics obj model %s is defined multiple times.", *(char **)igi2_frame.ArgList);
        abort();
      }
      zModel = igi2_frame.pxDataa + 728;
      v13 = ++igi2_frame.iPhysicsObj < PhysicsObjType_nType;
      igi2_frame.pxDataa += 728;
    }
    while ( v13 );
  }
  if ( ptArgList->isQVM )
  {
    *(_DWORD *)igi2_frame.ArgList = 0;
    QVM_EvalArg(igi2_frame.ArgList, 4, ptArgList, 9, 1);
    v14 = *(char **)igi2_frame.ArgList;
  }
  else
  {
    v14 = (char *)Expression_EvalInt(ptArgList->aptExpression[9]);
  }
  v3->nCollPoint = (int)v14;
  v15 = 10;
  igi2_frame.iCollPoint = 0;
  if ( (int)v14 > 0 )
  {
    p_iType = &v3->atCollPoint[0].iType;
    do
    {
      if ( ptArgList->isQVM )
      {
        *(_DWORD *)igi2_frame.ArgList = 0;
        QVM_EvalArg(igi2_frame.ArgList, 4, ptArgList, v15, 1);
        v17 = *(char **)igi2_frame.ArgList;
      }
      else
      {
        v17 = (char *)Expression_EvalInt(ptArgList->aptExpression[v15]);
      }
      *(p_iType - 1) = (int)v17;
      v18 = v15 + 1;
      if ( ptArgList->isQVM )
      {
        igi2_frame.pxDataa = nullptr;
        QVM_EvalArg(&igi2_frame.pxDataa, 4, ptArgList, v18, 1);
        v19 = (int)igi2_frame.pxDataa;
      }
      else
      {
        v19 = Expression_EvalInt(ptArgList->aptExpression[v18]);
      }
      *p_iType = v19;
      v20 = v18 + 1;
      if ( ptArgList->isQVM )
      {
        *(float *)&igi2_frame.iPhysicsObj = 0.0;
        QVM_EvalArg(&igi2_frame.iPhysicsObj, 4, ptArgList, v20, 1);
        v21 = igi2_frame.iPhysicsObj;
      }
      else
      {
        v21 = Expression_EvalInt(ptArgList->aptExpression[v20]);
      }
      p_iType[1] = v21;
      v22 = v20 + 1;
      if ( ptArgList->isQVM )
      {
        igi2_frame.v41 = 0.0;
        QVM_EvalArg(&igi2_frame.v41, 4, ptArgList, v22, 2);
        v23 = igi2_frame.v41;
      }
      else
      {
        v23 = Expression_EvalFloat(ptArgList->aptExpression[v22]);
      }
      *((float *)p_iType + 2) = v23;
      v24 = v22 + 1;
      if ( ptArgList->isQVM )
      {
        igi2_frame.v42 = 0.0;
        QVM_EvalArg(&igi2_frame.v42, 4, ptArgList, v24, 2);
        v25 = igi2_frame.v42;
      }
      else
      {
        v25 = Expression_EvalFloat(ptArgList->aptExpression[v24]);
      }
      *((float *)p_iType + 3) = v25;
      v26 = v24 + 1;
      if ( ptArgList->isQVM )
      {
        igi2_frame.v43 = 0.0;
        QVM_EvalArg(&igi2_frame.v43, 4, ptArgList, v26, 2);
        v27 = igi2_frame.v43;
      }
      else
      {
        v27 = Expression_EvalFloat(ptArgList->aptExpression[v26]);
      }
      v28 = igi2_frame.iCollPoint;
      *((float *)p_iType + 4) = v27;
      nCollPoint = igi2_frame.ptType->nCollPoint;
      v15 = v26 + 1;
      p_iType += 6;
      igi2_frame.iCollPoint = v28 + 1;
    }
    while ( v28 + 1 < nCollPoint );
    v3 = igi2_frame.ptType;
  }
  if ( ptArgList->isQVM )
  {
    *(float *)&igi2_frame.ptType = 0.0;
    QVM_EvalArg(&igi2_frame.ptType, 4, ptArgList, v15, 2);
    v30 = *(float *)&igi2_frame.ptType;
  }
  else
  {
    v30 = Expression_EvalFloat(ptArgList->aptExpression[v15]);
  }
  v3->vRestSpeed = v30;
  v31 = v15 + 1;
  if ( ptArgList->isQVM )
  {
    *(float *)&igi2_frame.ptType = 0.0;
    QVM_EvalArg(&igi2_frame.ptType, 4, ptArgList, v31, 2);
    v32 = *(float *)&igi2_frame.ptType;
  }
  else
  {
    v32 = Expression_EvalFloat(ptArgList->aptExpression[v31]);
  }
  v33 = PhysicsObjType_eGetPhysicsObjTypeSizeEvent;
  v3->vRestAngMomSquared = v32;
  pfHandler = (void (__cdecl *)(_DWORD, struct PhysicsObjType_s **))QTask_aatQTaskFinalEvent[v33][v3->eQTaskType].pfHandler;
  v3->pxData = nullptr;
  if ( pfHandler )
  {
    pfHandler(0, &igi2_frame.ptType);
    v35 = Mem_AllocFn((int)igi2_frame.ptType, 4);
    eQTaskType = v3->eQTaskType;
    v3->pxData = v35;
    igi2_frame.tParsePhysicsObjTypeContext[0].pxData = v35;
    igi2_frame.tParsePhysicsObjTypeContext[0].ptArgList = ptArgList;
    igi2_frame.tParsePhysicsObjTypeContext[0].iFirstArg = v31 + 1;
    ((void (__cdecl *)(_DWORD, struct ParsePhysicsObjTypeContext_s *))QTask_aatQTaskFinalEvent[PhysicsObjType_eParsePhysicsObjTypeEvent][eQTaskType].pfHandler)(
      0,
      igi2_frame.tParsePhysicsObjTypeContext);
  }
  ++PhysicsObjType_nType;
  igi2_frame.tParsePhysicsObjTypeContext[0].pxData = (void *)1;
  igi2_frame.tParsePhysicsObjTypeContext[0].iFirstArg = 0;
  igi2_frame.tParsePhysicsObjTypeContext[1].pxData = (void *)1072693248;
  igi2_frame.tParsePhysicsObjTypeContext[1].ptArgList = (struct ArgList_s *)&g_zInitialValue;
  qmemcpy(retstr, igi2_frame.tParsePhysicsObjTypeContext, sizeof(struct Result_s));
  return retstr;
}

// source: h/2/physicsobjtype.c:195  [anchor-mhash]
void __cdecl PhysicsObjType_ProcessFileCB(
        struct FileDirListCallbackContext_s *tFileDirListCallbackContext,
        void *pxContext)
{
  char *zFilename; // edi
  struct Script_s *v3; // eax
  struct Script_s *v4; // esi

  if ( tFileDirListCallbackContext->isDirectory )
  {
    Script_DirList(tFileDirListCallbackContext->zFilename, PhysicsObjType_ProcessFileCB, nullptr);
  }
  else
  {
    zFilename = tFileDirListCallbackContext->zFilename;
    v3 = Script_New(tFileDirListCallbackContext->zFilename);
    v4 = v3;
    if ( !v3 )
    {
      LDebug_Error("PhysicsObjType_ParseConfigFile(): Couldn't load script: %s", zFilename);
      abort();
    }
    Script_Execute(v3);
    Script_Delete(v4);
  }
}

// source: h/2/physicsobjtype.c:217  [anchor-strings]
void __cdecl PhysicsObjType_Open()
{
  PhysicsObjType_eParsePhysicsObjTypeEvent = QTask_NewQTaskEventFn(0, "ParsePhysicsObjType");
  PhysicsObjType_eGetPhysicsObjTypeSizeEvent = QTask_NewQTaskEventFn(0, "GetPhysicsObjTypeSize");
  PhysicsObjType_ePhysicsObjTypeDeleteEvent = QTask_NewQTaskEventFn(0, "PhysicsObjTypeDelete");
  Symbol_Register(
    "DefinePhysicsObjType",
    PhysicsObjType_DefinePhysicsObjTypeCB,
    nullptr,
    -1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
}

// source: h/2/physicsobjtype.c:236  [size]
void __cdecl PhysicsObjType_Close()
{
  QTask_DeleteQTaskEvent(PhysicsObjType_eParsePhysicsObjTypeEvent);
  QTask_DeleteQTaskEvent(PhysicsObjType_eGetPhysicsObjTypeSizeEvent);
  QTask_DeleteQTaskEvent(PhysicsObjType_ePhysicsObjTypeDeleteEvent);
}

// source: h/2/physicsobjtype.c:252  [anchor-refs]
void __cdecl PhysicsObjType_ParseConfigFile(char *zFile)
{
  struct Script_s *v1; // eax
  struct Script_s *v2; // esi

  v1 = Script_New(zFile);
  v2 = v1;
  if ( !v1 )
  {
    LDebug_Error("PhysicsObjType_ParseConfigFile(): Couldn't load script: %s", zFile);
    abort();
  }
  Script_Execute(v1);
  Script_Delete(v2);
}

// source: h/2/physicsobjtype.c:277  [size]
void __cdecl PhysicsObjType_ParseConfigDirectory(char *zDirectory)
{
  int pxContext[2]; // [esp+0h] [ebp-8h] BYREF

  pxContext[0] = (int)PhysicsObjType_ProcessFileCB;
  pxContext[1] = 0;
  File_DirList(
    zDirectory,
    (void (__cdecl *)(struct FileDirListCallbackContext_s *, void *))Script_DirListCallback,
    pxContext);
}

// source: h/2/physicsobjtype.c:291  [size]
__int16 __cdecl PhysicsObjType_GetParsePhysicsObjTypeEvent()
{
  return PhysicsObjType_eParsePhysicsObjTypeEvent;
}

// source: h/2/physicsobjtype.c:306  [size]
__int16 __cdecl PhysicsObjType_GetGetPhysicsObjTypeSizeEvent()
{
  return PhysicsObjType_eGetPhysicsObjTypeSizeEvent;
}

// source: h/2/physicsobjtype.c:321  [size]
__int16 __cdecl PhysicsObjType_GetPhysicsObjTypeDeleteEvent()
{
  return PhysicsObjType_ePhysicsObjTypeDeleteEvent;
}

// source: h/2/physicsobjtype.c:336  [size]
int __cdecl PhysicsObjType_GetNumberOfTypes()
{
  return PhysicsObjType_nType;
}

// source: h/2/physicsobjtype.c:349  [anchor-hash]
struct PhysicsObjType_s *__cdecl PhysicsObjType_GetType(int iType)
{
  return (struct PhysicsObjType_s *)(728 * iType + 7510696);
}

// source: h/2/physicsobjtype.c:364  [anchor-callee]
struct PhysicsObjType_s *__cdecl PhysicsObjType_FindType(char *zModel)
{
  int v1; // ebp
  struct PhysicsObjType_s *i; // edi

  v1 = 0;
  if ( PhysicsObjType_nType <= 0 )
    return nullptr;
  for ( i = PhysicsObjType_atPhysicsObjType; strcmp(i->zModel, zModel); ++i )
  {
    if ( ++v1 >= PhysicsObjType_nType )
      return nullptr;
  }
  return i;
}

// source: h/2/physicsobjtype.c:391  [anchor-hash]
struct real32x3_t *__cdecl PhysicsObjType_GetSize(struct PhysicsObjType_s *ptType)
{
  if ( ptType->tSize.vX == 0.0 || ptType->tSize.vY == 0.0 || ptType->tSize.vZ == 0.0 )
    PhysicsObjType_GetSizeFromModel(ptType);
  return &ptType->tSize;
}

// source: h/2/physicsobjtype.c:410  [anchor-mhash]
void __cdecl PhysicsObjType_Delete()
{
  int v0; // edi
  struct PhysicsObjType_s *v1; // esi
  struct PhysicsObjTypeDeleteContext_s tPhysicsObjTypeDeleteContext; // [esp+4h] [ebp-4h] BYREF

  v0 = PhysicsObjType_nType;
  if ( PhysicsObjType_nType > 0 )
  {
    v1 = PhysicsObjType_atPhysicsObjType;
    do
    {
      tPhysicsObjTypeDeleteContext.ptPhysicsObjType = v1;
      ((void (__cdecl *)(_DWORD, struct PhysicsObjTypeDeleteContext_s *))QTask_aatQTaskFinalEvent[PhysicsObjType_ePhysicsObjTypeDeleteEvent][v1->eQTaskType].pfHandler)(
        0,
        &tPhysicsObjTypeDeleteContext);
      ++v1;
      --v0;
    }
    while ( v0 );
  }
  PhysicsObjType_nType = 0;
}
