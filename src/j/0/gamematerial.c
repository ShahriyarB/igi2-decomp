/* j/0/gamematerial.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/gamematerial.c:70  [size]
struct Result_s *__cdecl GameMaterial_SetActiveMaterialCB(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  struct ArgList_s *v3; // edi
  struct ArgList_s *v4; // eax
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  v3 = ptArgList;
  if ( ptArgList->isQVM )
  {
    ptArgList = nullptr;
    QVM_EvalArg(&ptArgList, 4, v3, 0, 1);
    v4 = ptArgList;
  }
  else
  {
    v4 = (struct ArgList_s *)Expression_EvalInt(*ptArgList->aptExpression);
  }
  GameMaterial_nActiveMaterial = (int)v4;
  Rs.nResult = 1;
  Rs.vResult = 1.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/gamematerial.c:91  [anchor-mhash]
struct Result_s *__cdecl GameMaterial_DefineQMaterialCB(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  #pragma pack(push, 1)
  union
  {
    struct { float pxDataa; };
    struct { char igi2_o1[4]; struct Result_s Rs; };
    char igi2_extent[28];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  double v3; // st7
  double v4; // st7
  double v5; // st7
  int v6; // eax

  if ( ptArgList->isQVM )
  {
    igi2_frame.pxDataa = 0.0;
    QVM_EvalArg(&igi2_frame.pxDataa, 4, ptArgList, 0, 2);
    v3 = igi2_frame.pxDataa;
  }
  else
  {
    v3 = Expression_EvalFloat(*ptArgList->aptExpression);
  }
  GameMaterial_atGameMaterial[GameMaterial_nActiveMaterial].tQMaterial.vTransparency = v3;
  if ( ptArgList->isQVM )
  {
    igi2_frame.pxDataa = 0.0;
    QVM_EvalArg(&igi2_frame.pxDataa, 4, ptArgList, 1, 2);
    v4 = igi2_frame.pxDataa;
  }
  else
  {
    v4 = Expression_EvalFloat((struct QExpression_s *)*((_DWORD *)ptArgList->aptExpression + 1));
  }
  *((float *)&unk_717D14 + 266 * GameMaterial_nActiveMaterial) = v4;
  if ( ptArgList->isQVM )
  {
    igi2_frame.pxDataa = 0.0;
    QVM_EvalArg(&igi2_frame.pxDataa, 4, ptArgList, 2, 2);
    v5 = igi2_frame.pxDataa;
  }
  else
  {
    v5 = Expression_EvalFloat((struct QExpression_s *)*((_DWORD *)ptArgList->aptExpression + 2));
  }
  *((float *)&unk_717D10 + 266 * GameMaterial_nActiveMaterial) = v5;
  if ( ptArgList->isQVM )
  {
    igi2_frame.pxDataa = 0.0;
    QVM_EvalArg(&igi2_frame.pxDataa, 4, ptArgList, 3, 1);
  }
  else
  {
    igi2_frame.pxDataa = COERCE_FLOAT(Expression_EvalInt(ptArgList->aptExpression[3]));
  }
  *((float *)&unk_717D1C + 266 * GameMaterial_nActiveMaterial) = (double)SLODWORD(igi2_frame.pxDataa) * 9.5367431640625e-07;
  if ( ptArgList->isQVM )
  {
    igi2_frame.pxDataa = 0.0;
    QVM_EvalArg(&igi2_frame.pxDataa, 4, ptArgList, 4, 1);
    v6 = LODWORD(igi2_frame.pxDataa);
  }
  else
  {
    v6 = Expression_EvalInt(ptArgList->aptExpression[4]);
  }
  igi2_frame.pxDataa = *(float *)&v6;
  *((float *)&unk_717D20 + 266 * GameMaterial_nActiveMaterial) = (double)v6 * 9.5367431640625e-07;
  if ( ptArgList->isQVM )
  {
    igi2_frame.pxDataa = 0.0;
    QVM_EvalArg(&igi2_frame.pxDataa, 4, ptArgList, 5, 1);
  }
  else
  {
    igi2_frame.pxDataa = COERCE_FLOAT(Expression_EvalInt(ptArgList->aptExpression[5]));
  }
  *((float *)&unk_717D24 + 266 * GameMaterial_nActiveMaterial) = (double)SLODWORD(igi2_frame.pxDataa) * 9.5367431640625e-07;
  igi2_frame.Rs.nResult = 1;
  igi2_frame.Rs.vResult = 1.0;
  igi2_frame.Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &igi2_frame.Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/gamematerial.c:117  [anchor-mhash]
struct Result_s *__cdecl GameMaterial_DefineGameMaterialCB(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct GetEffectParametersSizeContext_s tGetEffectParametersSizeContext; };
    struct { char igi2_o1[4]; _BYTE tParseEffectParametersContext[24]; };
    char igi2_extent[28];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v3; // eax
  int v4; // ebx
  _BYTE *v5; // eax
  double v6; // st7
  double v7; // st7
  double v8; // st7
  char nSize; // al
  double v10; // st7
  int v11; // eax
  int v12; // esi
  _BYTE *v13; // eax
  int i; // ebx
  _BYTE *v15; // eax
  void *v16; // eax
  int v17; // esi
  int j; // ebx
  _BYTE *v19; // eax
  void *v20; // eax
  int v21; // esi
  int k; // ebx
  _BYTE *v23; // eax
  int m; // ebx
  _BYTE *v25; // eax
  void *v26; // eax
  int v27; // esi
  __int16 v28; // ax
  unsigned int v29; // ecx
  int v30; // edx
  void (__cdecl *pfHandler)(_DWORD, struct GetEffectParametersSizeContext_s *); // eax
  int v32; // esi
  void *v33; // eax
  unsigned int v34; // ecx
  int v35; // eax
  __int16 v36; // ax
  unsigned int v37; // ecx
  int v38; // eax
  void (__cdecl *v39)(_DWORD, struct GetEffectParametersSizeContext_s *); // eax
  void *v40; // eax
  unsigned int v41; // ecx
  int v42; // edx
  int v43; // ecx

  v3 = 1064 * GameMaterial_nActiveMaterial;
  byte_71810C[v3] = 1;
  v4 = 0;
  v5 = (char *)&unk_717D28 + v3;
  if ( ptArgList->isQVM )
  {
    *v5 = 0;
    QVM_EvalArg(v5, 32, ptArgList, 0, 3);
  }
  else
  {
    Expression_EvalString(*ptArgList->aptExpression, v5, 32);
  }
  if ( ptArgList->isQVM )
  {
    *(float *)&igi2_frame.tGetEffectParametersSizeContext.nSize = 0.0;
    QVM_EvalArg(&igi2_frame.tGetEffectParametersSizeContext, 4, ptArgList, 1, 2);
    v6 = *(float *)&igi2_frame.tGetEffectParametersSizeContext.nSize;
  }
  else
  {
    v6 = Expression_EvalFloat((struct QExpression_s *)*((_DWORD *)ptArgList->aptExpression + 1));
  }
  *((float *)&unk_717D48 + 266 * GameMaterial_nActiveMaterial) = v6;
  if ( ptArgList->isQVM )
  {
    *(float *)&igi2_frame.tGetEffectParametersSizeContext.nSize = 0.0;
    QVM_EvalArg(&igi2_frame.tGetEffectParametersSizeContext, 4, ptArgList, 2, 2);
    v7 = *(float *)&igi2_frame.tGetEffectParametersSizeContext.nSize;
  }
  else
  {
    v7 = Expression_EvalFloat((struct QExpression_s *)*((_DWORD *)ptArgList->aptExpression + 2));
  }
  *((float *)&unk_717D4C + 266 * GameMaterial_nActiveMaterial) = v7;
  if ( ptArgList->isQVM )
  {
    *(float *)&igi2_frame.tGetEffectParametersSizeContext.nSize = 0.0;
    QVM_EvalArg(&igi2_frame.tGetEffectParametersSizeContext, 4, ptArgList, 3, 2);
    v8 = *(float *)&igi2_frame.tGetEffectParametersSizeContext.nSize;
  }
  else
  {
    v8 = Expression_EvalFloat((struct QExpression_s *)*((_DWORD *)ptArgList->aptExpression + 3));
  }
  *((float *)&unk_717D50 + 266 * GameMaterial_nActiveMaterial) = v8;
  if ( ptArgList->isQVM )
  {
    *(float *)&igi2_frame.tGetEffectParametersSizeContext.nSize = 0.0;
    QVM_EvalArg(&igi2_frame.tGetEffectParametersSizeContext, 4, ptArgList, 4, 1);
    nSize = igi2_frame.tGetEffectParametersSizeContext.nSize;
  }
  else
  {
    nSize = Expression_EvalInt(ptArgList->aptExpression[4]);
  }
  byte_717D54[1064 * GameMaterial_nActiveMaterial] = nSize;
  if ( ptArgList->isQVM )
  {
    *(float *)&igi2_frame.tGetEffectParametersSizeContext.nSize = 0.0;
    QVM_EvalArg(&igi2_frame.tGetEffectParametersSizeContext, 4, ptArgList, 5, 2);
    v10 = *(float *)&igi2_frame.tGetEffectParametersSizeContext.nSize;
  }
  else
  {
    v10 = Expression_EvalFloat((struct QExpression_s *)*((_DWORD *)ptArgList->aptExpression + 5));
  }
  v11 = GameMaterial_nActiveMaterial;
  v12 = 6;
  igi2_frame.tGetEffectParametersSizeContext.nSize = 8;
  *((float *)&unk_717D58 + 266 * GameMaterial_nActiveMaterial) = v10;
  while ( 1 )
  {
    v13 = (char *)&unk_717D5C + 1064 * v11 + v4;
    if ( ptArgList->isQVM )
    {
      *v13 = 0;
      QVM_EvalArg(v13, 32, ptArgList, v12, 3);
    }
    else
    {
      Expression_EvalString(ptArgList->aptExpression[v12], v13, 32);
    }
    ++v12;
    v4 += 32;
    --igi2_frame.tGetEffectParametersSizeContext.nSize;
    if ( *(float *)&igi2_frame.tGetEffectParametersSizeContext.nSize == 0.0 )
      break;
    v11 = GameMaterial_nActiveMaterial;
  }
  for ( i = 0; i < 256; i += 32 )
  {
    v15 = (char *)&unk_717E5C + 1064 * GameMaterial_nActiveMaterial + i;
    if ( ptArgList->isQVM )
    {
      *v15 = 0;
      QVM_EvalArg(v15, 32, ptArgList, v12, 3);
    }
    else
    {
      Expression_EvalString(
        ptArgList->aptExpression[v12],
        (char *)&unk_717E5C + 1064 * GameMaterial_nActiveMaterial + i,
        32);
    }
    ++v12;
  }
  v16 = (void *)(1064 * GameMaterial_nActiveMaterial + 7438172);
  if ( ptArgList->isQVM )
  {
    *((_BYTE *)&unk_717F5C + 1064 * GameMaterial_nActiveMaterial) = 0;
    QVM_EvalArg(v16, 32, ptArgList, v12, 3);
  }
  else
  {
    Expression_EvalString(ptArgList->aptExpression[v12], (char *)(1064 * GameMaterial_nActiveMaterial + 7438172), 32);
  }
  v17 = v12 + 1;
  for ( j = 0; j < 96; j += 32 )
  {
    v19 = (char *)&unk_717F7C + 1064 * GameMaterial_nActiveMaterial + j;
    if ( ptArgList->isQVM )
    {
      *v19 = 0;
      QVM_EvalArg(v19, 32, ptArgList, v17, 3);
    }
    else
    {
      Expression_EvalString(
        ptArgList->aptExpression[v17],
        (char *)&unk_717F7C + 1064 * GameMaterial_nActiveMaterial + j,
        32);
    }
    ++v17;
  }
  v20 = (void *)(1064 * GameMaterial_nActiveMaterial + 7438300);
  if ( ptArgList->isQVM )
  {
    *((_BYTE *)&unk_717FDC + 1064 * GameMaterial_nActiveMaterial) = 0;
    QVM_EvalArg(v20, 32, ptArgList, v17, 3);
  }
  else
  {
    Expression_EvalString(ptArgList->aptExpression[v17], (char *)(1064 * GameMaterial_nActiveMaterial + 7438300), 32);
  }
  v21 = v17 + 1;
  for ( k = 0; k < 192; k += 32 )
  {
    v23 = (char *)&unk_717FFC + 1064 * GameMaterial_nActiveMaterial + k;
    if ( ptArgList->isQVM )
    {
      *v23 = 0;
      QVM_EvalArg(v23, 32, ptArgList, v21, 3);
    }
    else
    {
      Expression_EvalString(
        ptArgList->aptExpression[v21],
        (char *)&unk_717FFC + 1064 * GameMaterial_nActiveMaterial + k,
        32);
    }
    ++v21;
  }
  for ( m = 0; m < 64; m += 32 )
  {
    v25 = (char *)&unk_7180BC + 1064 * GameMaterial_nActiveMaterial + m;
    if ( ptArgList->isQVM )
    {
      *v25 = 0;
      QVM_EvalArg(v25, 32, ptArgList, v21, 3);
    }
    else
    {
      Expression_EvalString(
        ptArgList->aptExpression[v21],
        (char *)&unk_7180BC + 1064 * GameMaterial_nActiveMaterial + m,
        32);
    }
    ++v21;
  }
  v26 = (void *)(1064 * GameMaterial_nActiveMaterial + 7438605);
  if ( ptArgList->isQVM )
  {
    byte_71810D[1064 * GameMaterial_nActiveMaterial] = 0;
    QVM_EvalArg(v26, 32, ptArgList, v21, 3);
  }
  else
  {
    Expression_EvalString(ptArgList->aptExpression[v21], (char *)(1064 * GameMaterial_nActiveMaterial + 7438605), 32);
  }
  v27 = v21 + 1;
  if ( ptArgList->isQVM )
  {
    *(float *)&igi2_frame.tGetEffectParametersSizeContext.nSize = 0.0;
    QVM_EvalArg(&igi2_frame.tGetEffectParametersSizeContext, 4, ptArgList, v27, 1);
    v28 = igi2_frame.tGetEffectParametersSizeContext.nSize;
  }
  else
  {
    v28 = Expression_EvalInt(ptArgList->aptExpression[v27]);
  }
  v29 = 1064 * GameMaterial_nActiveMaterial;
  v30 = 511 * GameMaterial_eGetEffectParametersSizeQTaskEvent;
  word_7180FC[v29 / 2] = v28;
  dword_718100[v29 / 4] = 0;
  pfHandler = (void (__cdecl *)(_DWORD, struct GetEffectParametersSizeContext_s *))QTask_aatQTaskFinalEvent[0][(unsigned __int16)word_7180FC[v29 / 2] + v30].pfHandler;
  v32 = v27 + 1;
  if ( pfHandler )
  {
    pfHandler(0, &igi2_frame.tGetEffectParametersSizeContext);
    v33 = Mem_AllocFn(igi2_frame.tGetEffectParametersSizeContext.nSize, 4);
    v34 = 532 * GameMaterial_nActiveMaterial;
    dword_718100[v34 / 2] = (int)v33;
    *(_DWORD *)igi2_frame.tParseEffectParametersContext = v33;
    v35 = 511 * GameMaterial_eParseEffectParametersQTaskEvent + (unsigned __int16)word_7180FC[v34];
    *(_DWORD *)&igi2_frame.tParseEffectParametersContext[4] = ptArgList;
    *(_DWORD *)&igi2_frame.tParseEffectParametersContext[8] = v32;
    ((void (__cdecl *)(_DWORD, _BYTE *))QTask_aatQTaskFinalEvent[0][v35].pfHandler)(0, igi2_frame.tParseEffectParametersContext);
    v32 += *(_DWORD *)&igi2_frame.tParseEffectParametersContext[12];
  }
  if ( ptArgList->isQVM )
  {
    *(float *)&igi2_frame.tGetEffectParametersSizeContext.nSize = 0.0;
    QVM_EvalArg(&igi2_frame.tGetEffectParametersSizeContext, 4, ptArgList, v32, 1);
    v36 = igi2_frame.tGetEffectParametersSizeContext.nSize;
  }
  else
  {
    v36 = Expression_EvalInt(ptArgList->aptExpression[v32]);
  }
  v37 = 1064 * GameMaterial_nActiveMaterial;
  word_718104[v37 / 2] = v36;
  v38 = 511 * GameMaterial_eGetEffectParametersSizeQTaskEvent;
  dword_718108[v37 / 4] = 0;
  v39 = (void (__cdecl *)(_DWORD, struct GetEffectParametersSizeContext_s *))QTask_aatQTaskFinalEvent[0][(unsigned __int16)word_718104[v37 / 2] + v38].pfHandler;
  if ( v39 )
  {
    v39(0, &igi2_frame.tGetEffectParametersSizeContext);
    v40 = Mem_AllocFn(igi2_frame.tGetEffectParametersSizeContext.nSize, 4);
    v41 = 532 * GameMaterial_nActiveMaterial;
    v42 = GameMaterial_eParseEffectParametersQTaskEvent;
    dword_718108[v41 / 2] = (int)v40;
    v43 = (unsigned __int16)word_718104[v41];
    *(_DWORD *)igi2_frame.tParseEffectParametersContext = v40;
    *(_DWORD *)&igi2_frame.tParseEffectParametersContext[4] = ptArgList;
    *(_DWORD *)&igi2_frame.tParseEffectParametersContext[8] = v32 + 1;
    ((void (__cdecl *)(_DWORD, _BYTE *))QTask_aatQTaskFinalEvent[v42][v43].pfHandler)(0, igi2_frame.tParseEffectParametersContext);
  }
  *(_DWORD *)igi2_frame.tParseEffectParametersContext = 1;
  *(_DWORD *)&igi2_frame.tParseEffectParametersContext[8] = 0;
  *(_DWORD *)&igi2_frame.tParseEffectParametersContext[12] = 1072693248;
  *(_DWORD *)&igi2_frame.tParseEffectParametersContext[16] = &g_zInitialValue;
  qmemcpy(retstr, igi2_frame.tParseEffectParametersContext, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/gamematerial.c:239  [anchor-strings]
void __cdecl GameMaterial_PrintGameMaterialInfo(struct GameMaterial_s *ptGameMaterial)
{
  unsigned int v1; // esi
  char *v2; // edi
  unsigned int v3; // esi
  char *v4; // edi
  char *v5; // esi
  int v6; // edi
  unsigned int v7; // esi
  char *v8; // edi
  unsigned int v9; // esi
  char *v10; // edi
  char *v11; // eax

  DebugConsole_printf("GameMaterial properties:\n");
  DebugConsole_printf("  Name: '%s' \n", ptGameMaterial->zName);
  v1 = 0;
  v2 = ptGameMaterial->azWalkSound[0];
  do
  {
    DebugConsole_printf("  Walk sound%d: '%s'\n", v1++, v2);
    v2 += 32;
  }
  while ( v1 < 8 );
  v3 = 0;
  v4 = ptGameMaterial->azRunSound[0];
  do
  {
    DebugConsole_printf("  Run sound%d: '%s'\n", v3++, v4);
    v4 += 32;
  }
  while ( v3 < 8 );
  DebugConsole_printf("  Land sound: '%s'\n", ptGameMaterial->zLandSound);
  v5 = ptGameMaterial->azDeadBodyLandSound[0];
  v6 = 3;
  do
  {
    DebugConsole_printf("  Dead Body Land sound: '%s'\n", v5);
    v5 += 32;
    --v6;
  }
  while ( v6 );
  v7 = 0;
  v8 = ptGameMaterial->azBulletHitSound[0];
  do
  {
    DebugConsole_printf("  Bullet hit sound%d: '%s'\n", v7++, v8);
    v8 += 32;
  }
  while ( v7 < 6 );
  v9 = 0;
  v10 = ptGameMaterial->azGrenadeHitSound[0];
  do
  {
    DebugConsole_printf("  Grenade hit sound%d: '%s'\n", v9++, v10);
    v10 += 32;
  }
  while ( v9 < 2 );
  DebugConsole_printf("  Rain sound '%s'\n", ptGameMaterial->zRainSound);
  DebugConsole_printf("  AI event range: %f\n", ptGameMaterial->vAIEventRange);
  DebugConsole_printf("  Max angle for riccochet: %f\n", ptGameMaterial->vMaxAngleForRiccochet);
  DebugConsole_printf("  Min thickness: %f\n", ptGameMaterial->vMinThickness);
  DebugConsole_printf("  Penetration power %f\n", ptGameMaterial->vPenetrationPower);
  v11 = "TRUE";
  if ( !ptGameMaterial->isWalkThrough )
    v11 = "FALSE";
  DebugConsole_printf("  Walk through? : %s\n", v11);
}

// source: j/0/gamematerial.c:286  [anchor-hash]
void __cdecl GameMaterial_Open()
{
  char *v0; // eax

  v0 = &byte_71810C;
  do
  {
    *v0 = 0;
    v0 += 1064;
  }
  while ( (int)v0 < 7506700 );
  GameMaterial_eGetEffectParametersSizeQTaskEvent = QTask_NewQTaskEventFn(0, "GetEffectParametersSize");
  GameMaterial_eParseEffectParametersQTaskEvent = QTask_NewQTaskEventFn(0, "ParseEffectParameters");
  GameMaterial_eCreateEffectQTaskEvent = QTask_NewQTaskEventFn(0, "CreateEffect");
  Symbol_Register(
    "SetActiveMaterial",
    GameMaterial_SetActiveMaterialCB,
    nullptr,
    -1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "DefineQMaterial",
    GameMaterial_DefineQMaterialCB,
    nullptr,
    -1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "DefineGameMaterial",
    GameMaterial_DefineGameMaterialCB,
    nullptr,
    -1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
}

// source: j/0/gamematerial.c:325  [anchor-hash]
void __cdecl GameMaterial_RemoveAll()
{
  int *v0; // ebp
  int v1; // eax
  int v2; // esi
  int v3; // esi

  v0 = &dword_718108;
  do
  {
    if ( *((_BYTE *)v0 + 4) )
    {
      v1 = *(v0 - 2);
      if ( v1 )
      {
        v2 = *(_DWORD *)((v1 - 4) & 0xFFFFFFFC);
        --Mem_nCurrentAllocations;
        Node_Remove((_DWORD **)v2);
        memset(*(void **)(v2 + 8), 0xCDu, *(_DWORD *)(v2 + 16));
        free((void *)v2);
        *(v0 - 2) = 0;
      }
      if ( *v0 )
      {
        v3 = *(_DWORD *)((*v0 - 4) & 0xFFFFFFFC);
        --Mem_nCurrentAllocations;
        Node_Remove((_DWORD **)v3);
        memset(*(void **)(v3 + 8), 0xCDu, *(_DWORD *)(v3 + 16));
        free((void *)v3);
        *v0 = 0;
      }
      *((_BYTE *)v0 + 4) = 0;
    }
    v0 += 266;
  }
  while ( (int)v0 < 7506696 );
}

// source: j/0/gamematerial.c:360  [anchor-hash]
void __cdecl GameMaterial_Close()
{
  GameMaterial_RemoveAll();
  QTask_DeleteQTaskEvent(GameMaterial_eGetEffectParametersSizeQTaskEvent);
  QTask_DeleteQTaskEvent(GameMaterial_eParseEffectParametersQTaskEvent);
  QTask_DeleteQTaskEvent(GameMaterial_eCreateEffectQTaskEvent);
}

// source: j/0/gamematerial.c:380  [size]
__int16 __cdecl GameMaterial_GetGetEffectParametersSizeQTaskEvent()
{
  return GameMaterial_eGetEffectParametersSizeQTaskEvent;
}

// source: j/0/gamematerial.c:394  [size]
__int16 __cdecl GameMaterial_GetParseEffectParametersQTaskEvent()
{
  return GameMaterial_eParseEffectParametersQTaskEvent;
}

// source: j/0/gamematerial.c:407  [size]
__int16 __cdecl GameMaterial_GetCreateEffectQTaskEvent()
{
  return GameMaterial_eCreateEffectQTaskEvent;
}

// source: j/0/gamematerial.c:420  [anchor-hash]
struct GameMaterial_s *__cdecl GameMaterial_Get(int iGameMaterial)
{
  return (struct GameMaterial_s *)(1064 * iGameMaterial + 7437576);
}

// source: j/0/gamematerial.c:436  [anchor-hash]
void __cdecl GameMaterial_LoadParameters()
{
  struct Script_s *v0; // eax
  struct Script_s *v1; // esi

  GameMaterial_RemoveAll();
  v0 = Script_New("LOCAL:material/material.qsc");
  v1 = v0;
  if ( !v0 )
  {
    LDebug_Error("GameMaterial_LoadParameters: Couldn't load script \"%s\"", "LOCAL:material/material.qsc");
    abort();
  }
  Script_Execute(v0);
  Script_Delete(v1);
}

// source: j/0/gamematerial.c:464  [anchor-mhash]
void __cdecl GameMaterial_RegisterParameters(struct World_s *ptWorld)
{
  struct GameMaterial_s *v1; // eax
  struct QMaterial_t **aptQMaterial; // ecx

  v1 = GameMaterial_atGameMaterial;
  aptQMaterial = ptWorld->aptQMaterial;
  do
  {
    *aptQMaterial = &v1->tQMaterial;
    ++v1;
    ++aptQMaterial;
  }
  while ( (int)v1 < 7505672 );
}

// source: j/0/gamematerial.c:491  [anchor-mhash]
struct real32x3_t *__cdecl GameMaterial_CreateEffect(
        unsigned __int16 eEffectQTaskType,
        void *pxData,
        struct QIntersection_s *ptIntersection,
        enum bool isPenetration,
        float vPenetrationPower,
        struct real32x3_t *ptParticleDirection,
        float vSmokeParticleSize)
{
  float vX; // ecx
  float vZ; // eax
  struct CreateEffectContext_s tCreateEffectContext; // [esp+0h] [ebp-20h] BYREF

  tCreateEffectContext.ptIntersection = ptIntersection;
  tCreateEffectContext.vPenetrationPower = vPenetrationPower;
  tCreateEffectContext.tParticleDirection.vY = ptParticleDirection->vY;
  tCreateEffectContext.pxData = pxData;
  tCreateEffectContext.isPenetration = isPenetration;
  vX = ptParticleDirection->vX;
  vZ = ptParticleDirection->vZ;
  tCreateEffectContext.tParticleDirection.vX = vX;
  tCreateEffectContext.tParticleDirection.vZ = vZ;
  tCreateEffectContext.vSmokeParticleSize = vSmokeParticleSize;
  return ((struct real32x3_t *(__cdecl *)(_DWORD, struct CreateEffectContext_s *))QTask_aatQTaskFinalEvent[GameMaterial_eCreateEffectQTaskEvent][eEffectQTaskType].pfHandler)(
           0,
           &tCreateEffectContext);
}
