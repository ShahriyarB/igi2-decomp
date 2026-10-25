/* h/2/scriptdebugger.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: h/2/scriptdebugger.c:76  [anchor-strings]
void __cdecl ScriptDebugger_EnumerateScriptSymbolsCallback(char *zSymbol, void *pxScriptSymbol, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { int v11; };
    struct { char igi2_o1[20]; char zTemp[1024]; };
    struct { char igi2_o2[1044]; char zBuffer[256]; };
    char igi2_extent[1300];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v3; // eax
  int v4; // eax
  int v5; // ecx
  int v6; // eax
  double v7; // st7
  char *v8; // eax
  double v9; // st7
  int v10; // eax

  v3 = *(_DWORD *)pxScriptSymbol;
  if ( (!*(_DWORD *)pxScriptSymbol || v3 == 2 || v3 == 1)
    && Wildcard_MatchSimple(*(void **)pxContext, nullptr, nullptr, (void *)zSymbol, 1) )
  {
    if ( *((_DWORD *)pxContext + 2) )
    {
      if ( *(_DWORD *)pxScriptSymbol )
      {
        DebugConsole_printf("ERROR: Can't assign to function or constant.\n");
        goto LABEL_20;
      }
      v4 = *((_DWORD *)pxContext + 3);
      v5 = *((_DWORD *)pxContext + 4);
      if ( v4 > 2 )
      {
        if ( **(_BYTE **)(v5 + 8) == 61 )
        {
          if ( v4 <= 3 )
            goto LABEL_20;
          v6 = 3;
        }
        else
        {
          v6 = 2;
        }
        switch ( *((_DWORD *)pxScriptSymbol + 1) )
        {
          case 1:
            igi2_frame.v11 = atoi(*(char **)(v5 + 4 * v6));
            sprintf(igi2_frame.zTemp, "%s = %d", zSymbol, igi2_frame.v11);
            goto LABEL_16;
          case 2:
            v7 = atof((char *)*(_DWORD *)(v5 + 4 * v6));
            sprintf(igi2_frame.zTemp, "%s = %f", zSymbol, v7);
            Script_ParseLineInt32(igi2_frame.zTemp);
            break;
          case 3:
            sprintf(igi2_frame.zTemp, "%s = \"%s\"", zSymbol, *(_DWORD *)(v5 + 4 * v6));
LABEL_16:
            Script_ParseLineInt32(igi2_frame.zTemp);
            break;
        }
      }
    }
LABEL_20:
    if ( *((_DWORD *)pxContext + 1) && (!*(_DWORD *)pxScriptSymbol || *(_DWORD *)pxScriptSymbol == 2) )
    {
      switch ( *((_DWORD *)pxScriptSymbol + 1) )
      {
        case 1:
          v10 = Script_ParseLineInt32(zSymbol);
          DebugConsole_printf("%s = %d\n", zSymbol, v10);
          break;
        case 2:
          v9 = Script_ParseLineFloat(zSymbol);
          DebugConsole_printf("%s = %f\n", zSymbol, v9);
          break;
        case 3:
          v8 = Script_ParseLineString(igi2_frame.zBuffer, 0x100u, zSymbol);
          DebugConsole_printf("%s = \"%s\"\n", zSymbol, v8);
          break;
      }
    }
    else
    {
      DebugConsole_printf((char *)&g_zMessage_0.nCreateTime, zSymbol);
    }
  }
}

// source: h/2/scriptdebugger.c:187  [anchor-mhash]
enum bool __cdecl ScriptDebugger_InspectScriptSymbols(
        char *zPattern,
        enum bool isEvaluate,
        enum bool isAssign,
        int argc,
        char **argv)
{
  enum bool result; // eax
  struct ScriptSymbolEnumFilter_s tScriptSymbolEnumFilter; // [esp+4h] [ebp-14h] BYREF

  tScriptSymbolEnumFilter.isEvaluate = isEvaluate;
  tScriptSymbolEnumFilter.isAssign = isAssign;
  tScriptSymbolEnumFilter.zPattern = zPattern;
  tScriptSymbolEnumFilter.argc = argc;
  tScriptSymbolEnumFilter.argv = argv;
  Script_EnumerateSymbols(ScriptDebugger_EnumerateScriptSymbolsCallback, &tScriptSymbolEnumFilter);
  return result;
}

// source: h/2/scriptdebugger.c:210  [size]
void __cdecl ScriptDebugger_ParseListScriptSymbols(int argc, char **argv, void *pxCommandContext)
{
  char *v3; // eax
  _DWORD pxContext[5]; // [esp+0h] [ebp-14h] BYREF

  DebugConsole_printf((char *)&stru_6A4CDC);
  if ( argc <= 1 )
    v3 = "*";
  else
    v3 = argv[1];
  pxContext[1] = 0;
  pxContext[2] = 0;
  pxContext[0] = v3;
  pxContext[3] = argc;
  pxContext[4] = argv;
  Script_EnumerateSymbols(ScriptDebugger_EnumerateScriptSymbolsCallback, pxContext);
}

// source: h/2/scriptdebugger.c:224  [anchor-caller]
void __cdecl ScriptDebugger_ParseEvaluateExpression(int argc, char **argv, void *pxCommandContext)
{
  int v3; // ecx
  int v4; // edi
  char *v5; // ebp
  int i; // ebx
  int v7; // esi
  double v; // [esp+8h] [ebp-8h] BYREF

  DebugConsole_printf((char *)&stru_6A4CDC);
  v3 = 1;
  v4 = 0;
  if ( argc > 1 )
  {
    do
      v4 += strlen(argv[v3++]);
    while ( v3 < argc );
    if ( v4 )
    {
      v5 = (char *)Mem_AllocFn(v4 + 1, 4);
      *v5 = 0;
      for ( i = 1; i < argc; ++i )
        qmemcpy(&v5[strlen(v5)], argv[i], &argv[i][strlen(argv[i]) + 1] - argv[i]);
      ScriptDebugger_EvaluateExpression(v5, &v);
      DebugConsole_printf("%f\n", v);
      v7 = *(_DWORD *)((unsigned int)(v5 - 4) & 0xFFFFFFFC);
      --Mem_nCurrentAllocations;
      Node_Remove((_DWORD **)v7);
      memset(*(void **)(v7 + 8), 0xCDu, *(_DWORD *)(v7 + 16));
      free((void *)v7);
    }
  }
}

// source: h/2/scriptdebugger.c:270  [size]
void __cdecl ScriptDebugger_ParseInspectScriptSymbols(int argc, char **argv, void *pxCommandContext)
{
  char *v3; // eax
  _DWORD pxContext[5]; // [esp+0h] [ebp-14h] BYREF

  DebugConsole_printf((char *)&stru_6A4CDC);
  if ( argc <= 1 )
    v3 = "*";
  else
    v3 = argv[1];
  pxContext[1] = 1;
  pxContext[2] = 0;
  pxContext[0] = v3;
  pxContext[3] = argc;
  pxContext[4] = argv;
  Script_EnumerateSymbols(ScriptDebugger_EnumerateScriptSymbolsCallback, pxContext);
}

// source: h/2/scriptdebugger.c:284  [size]
void __cdecl ScriptDebugger_ParseSetScriptSymbols(int argc, char **argv, void *pxCommandContext)
{
  char *v3; // eax
  _DWORD pxContext[5]; // [esp+0h] [ebp-14h] BYREF

  DebugConsole_printf((char *)&stru_6A4CDC);
  if ( argc <= 1 )
    v3 = "*";
  else
    v3 = argv[1];
  pxContext[1] = 1;
  pxContext[2] = 1;
  pxContext[0] = v3;
  pxContext[3] = argc;
  pxContext[4] = argv;
  Script_EnumerateSymbols(ScriptDebugger_EnumerateScriptSymbolsCallback, pxContext);
}

// source: h/2/scriptdebugger.c:298  [anchor-mhash]
void __cdecl ScriptDebugger_ParseWatch(int argc, char **argv, void *pxCommandContext)
{
  char **v3; // esi
  unsigned int v4; // ebp
  char **v5; // edi
  char *v6; // ebp
  unsigned int v7; // edi
  float vZ; // ebx
  int v9; // edx

  if ( argc > 1 )
  {
    v3 = argv;
    v4 = 0;
    if ( *(_DWORD *)LODWORD(g_ptRotationMatrix.tZ.vZ) )
    {
      v5 = *(char ***)(LODWORD(g_ptRotationMatrix.tZ.vZ) + 16);
      while ( strcmp(argv[1], *v5) )
      {
        ++v4;
        ++v5;
        if ( v4 >= *(_DWORD *)LODWORD(g_ptRotationMatrix.tZ.vZ) )
        {
          v3 = argv;
          goto LABEL_7;
        }
      }
    }
    else
    {
LABEL_7:
      v6 = (char *)Mem_AllocFn(strlen(v3[1]) + 1, 4);
      strcpy(v6, v3[1]);
      v7 = *(_DWORD *)LODWORD(g_ptRotationMatrix.tZ.vZ);
      vZ = g_ptRotationMatrix.tZ.vZ;
      if ( *(_DWORD *)LODWORD(g_ptRotationMatrix.tZ.vZ) == *(_DWORD *)(LODWORD(g_ptRotationMatrix.tZ.vZ) + 4) )
        QVector_Realloc((struct QVector_s *)LODWORD(g_ptRotationMatrix.tZ.vZ), 1u);
      if ( v7 < *(_DWORD *)LODWORD(vZ) - 1 )
        memmove(
          (void *)(*(_DWORD *)(LODWORD(vZ) + 16) + 4 * v7 + 4),
          (void *)(*(_DWORD *)(LODWORD(vZ) + 16) + 4 * v7),
          4 * (*(_DWORD *)LODWORD(vZ) - v7));
      v9 = *(_DWORD *)(LODWORD(vZ) + 16);
      ++*(_DWORD *)LODWORD(vZ);
      *(_DWORD *)(v9 + 4 * v7) = v6;
    }
  }
}

// source: h/2/scriptdebugger.c:332  [anchor-callee]
void __cdecl ScriptDebugger_ParseUnwatch(int argc, char **argv, void *pxCommandContext)
{
  float vZ; // edi
  unsigned int i; // ebp
  int v5; // eax
  int v6; // esi
  unsigned int v7; // edx
  int v8; // ecx

  vZ = g_ptRotationMatrix.tZ.vZ;
  for ( i = 0; i < *(_DWORD *)LODWORD(vZ); ++i )
  {
    if ( argc < 2 || !strcmp(argv[1], *(char **)(*(_DWORD *)(LODWORD(vZ) + 16) + 4 * i)) )
    {
      v5 = *(_DWORD *)(*(_DWORD *)(LODWORD(vZ) + 16) + 4 * i);
      if ( v5 )
      {
        v6 = *(_DWORD *)((v5 - 4) & 0xFFFFFFFC);
        --Mem_nCurrentAllocations;
        Node_Remove((_DWORD **)v6);
        memset(*(void **)(v6 + 8), 0xCDu, *(_DWORD *)(v6 + 16));
        free((void *)v6);
        vZ = g_ptRotationMatrix.tZ.vZ;
      }
      v7 = *(_DWORD *)LODWORD(vZ) - 1;
      *(_DWORD *)LODWORD(vZ) = v7;
      if ( i < v7 )
      {
        v8 = *(_DWORD *)(LODWORD(vZ) + 16);
        if ( *(_DWORD *)(LODWORD(vZ) + 20) )
        {
          memmove((void *)(v8 + 4 * i), (void *)(v8 + 4 * i + 4), 4 * (v7 - i));
          vZ = g_ptRotationMatrix.tZ.vZ;
        }
        else
        {
          *(_DWORD *)(v8 + 4 * i) = *(_DWORD *)(v8 + 4 * v7);
        }
      }
      --i;
    }
  }
}

// source: h/2/scriptdebugger.c:369  [anchor-strings]
void __cdecl ScriptDebugger_EvaluateExpression(char *zEval, double *ptv)
{
  struct QExpression_s *v2; // eax
  struct QExpression_s *v3; // esi

  if ( !Script_nSP )
  {
    LDebug_Error("Script: Stack underflow.");
LABEL_7:
    abort();
  }
  Script_anWarningLevelStack[--Script_nSP] = Script_nWarningLevel;
  Script_nWarningLevel = 0;
  v2 = Script_ParseLine(zEval);
  v3 = v2;
  if ( v2 )
  {
    *ptv = Expression_EvalFloat(v2);
    Expression_Delete(v3);
  }
  if ( Script_nSP >= 256 )
  {
    LDebug_Error("Script: Stack overflow.");
    goto LABEL_7;
  }
  Script_nWarningLevel = Script_anWarningLevelStack[Script_nSP++];
}

// source: h/2/scriptdebugger.c:399  [size]
int __cdecl ScriptDebugger_GetConsoleID()
{
  return LODWORD(g_ptRotationMatrix.tZ.vY);
}

// source: h/2/scriptdebugger.c:412  [size]
int __cdecl ScriptDebugger_GetWatchConsoleID()
{
  return g_ptRotationMatrix.nOps;
}

// source: h/2/scriptdebugger.c:425  [anchor-caller]
void __cdecl ScriptDebugger_UpdateWatchConsole()
{
  float vZ; // eax
  unsigned int i; // ebx
  int v2; // edx
  unsigned int nElements; // edi
  unsigned int v4; // esi
  bool v5; // zf
  int v6; // edx
  struct DebugConsole_s *ptHead; // ecx
  struct DebugConsole_s *ptNext; // eax
  int v9; // edx
  _DWORD pxContext[5]; // [esp+Ch] [ebp-14h] BYREF

  DebugConsole_PushActiveConsole(g_ptRotationMatrix.nOps);
  DebugConsole_ClearAll(DebugConsole_ptActiveDebugConsole, true);
  vZ = g_ptRotationMatrix.tZ.vZ;
  for ( i = 0; i < *(_DWORD *)LODWORD(vZ); ++i )
  {
    v2 = *(_DWORD *)(*(_DWORD *)(LODWORD(vZ) + 16) + 4 * i);
    nElements = Symbol_ptSymbolVector->tPrivate.nElements;
    v4 = 0;
    v5 = Symbol_ptSymbolVector->tPrivate.nElements == 0;
    pxContext[1] = 1;
    memset(&pxContext[2], 0, 12);
    pxContext[0] = v2;
    if ( !v5 )
    {
      do
      {
        ScriptDebugger_EnumerateScriptSymbolsCallback(
          *((char **)Symbol_ptSymbolVector->tPrivate.papxElement[v4] + 5),
          Symbol_ptSymbolVector->tPrivate.papxElement[v4],
          pxContext);
        ++v4;
      }
      while ( v4 < nElements );
      vZ = g_ptRotationMatrix.tZ.vZ;
    }
  }
  v6 = --DebugConsole_nStackPointer;
  if ( DebugConsole_nStackPointer <= 0 )
  {
    DebugConsole_ptActiveDebugConsole = nullptr;
  }
  else
  {
    ptHead = DebugConsole_tConsoleList.ptHead;
    ptNext = DebugConsole_tConsoleList.ptHead->ptNext;
    if ( DebugConsole_tConsoleList.ptHead->ptNext )
    {
      v9 = DebugConsole_atActiveConsoleStack[v6];
      while ( ptHead->tConsoleID != v9 )
      {
        ptHead = ptNext;
        ptNext = ptNext->ptNext;
        if ( !ptNext )
          goto LABEL_11;
      }
    }
    else
    {
LABEL_11:
      ptHead = nullptr;
    }
    DebugConsole_ptActiveDebugConsole = ptHead;
  }
}

// source: h/2/scriptdebugger.c:447  [anchor-hash]
void __cdecl ScriptDebugger_Open()
{
  void *v0; // esi
  _DWORD *v1; // eax

  LODWORD(g_ptRotationMatrix.tZ.vY) = DebugConsole_Alloc("ScriptDebugger", 100);
  g_ptRotationMatrix.nOps = DebugConsole_Alloc("Watch Window", 100);
  DebugConsole_PushActiveConsole(SLODWORD(g_ptRotationMatrix.tZ.vY));
  DebugConsoleCommand_Register(
    "ls",
    "[pattern]",
    "Display a list of script symbols matching [pattern]. Use * as wildcard.",
    ScriptDebugger_ParseListScriptSymbols,
    nullptr);
  DebugConsoleCommand_Register(
    "inspect",
    "[pattern]",
    "Inspect script symbols matching [pattern]. Use * as wildcard.",
    ScriptDebugger_ParseInspectScriptSymbols,
    nullptr);
  DebugConsoleCommand_Register(
    off_6876BC,
    "[pattern] = [value]",
    "Set script symbols matching [pattern]. Use * as wildcard.",
    ScriptDebugger_ParseSetScriptSymbols,
    nullptr);
  DebugConsoleCommand_Register(
    "eval",
    "[expression]",
    "Evaluate expression.",
    ScriptDebugger_ParseEvaluateExpression,
    nullptr);
  DebugConsoleCommand_Register(
    "watch",
    "[pattern]",
    "Watch script symbols matching [pattern]. Use * as wildcard.",
    ScriptDebugger_ParseWatch,
    nullptr);
  DebugConsoleCommand_Register(
    "unwatch",
    "[pattern]",
    "Remove [pattern] from watch list. No [pattern] will remove all.",
    ScriptDebugger_ParseUnwatch,
    nullptr);
  DebugConsole_PopActiveConsole();
  DebugConsole_PushActiveConsole(g_ptRotationMatrix.nOps);
  DebugConsoleCommand_Register(
    "watch",
    "[pattern]",
    "Watch script symbols matching [pattern]. Use * as wildcard.",
    ScriptDebugger_ParseWatch,
    nullptr);
  DebugConsoleCommand_Register(
    "unwatch",
    "[pattern]",
    "Remove [pattern] from watch list. No [pattern] will remove all.",
    ScriptDebugger_ParseUnwatch,
    nullptr);
  DebugConsole_PopActiveConsole();
  v0 = Mem_AllocFn(128, 4);
  v1 = Mem_AllocFn(24, 4);
  v1[1] = 32;
  v1[2] = 32;
  *v1 = 0;
  v1[3] = 0;
  v1[4] = v0;
  v1[5] = 1;
  LODWORD(g_ptRotationMatrix.tZ.vZ) = v1;
}

// source: h/2/scriptdebugger.c:474  [anchor-hash]
void __cdecl ScriptDebugger_Close()
{
  ScriptDebugger_ParseUnwatch(0, nullptr, nullptr);
  QVector_Delete((struct QVector_s *)LODWORD(g_ptRotationMatrix.tZ.vZ));
  DebugConsole_PushActiveConsole(SLODWORD(g_ptRotationMatrix.tZ.vY));
  DebugConsoleCommand_Remove("ls");
  DebugConsoleCommand_Remove("inspect");
  DebugConsoleCommand_Remove(off_6876BC);
  DebugConsoleCommand_Remove("eval");
  DebugConsoleCommand_Remove("watch");
  DebugConsoleCommand_Remove("unwatch");
  DebugConsole_PopActiveConsole();
  DebugConsole_PushActiveConsole(g_ptRotationMatrix.nOps);
  DebugConsoleCommand_Remove("watch");
  DebugConsoleCommand_Remove("unwatch");
  DebugConsole_PopActiveConsole();
  DebugConsole_DeAlloc(SLODWORD(g_ptRotationMatrix.tZ.vY));
  DebugConsole_DeAlloc(g_ptRotationMatrix.nOps);
}
