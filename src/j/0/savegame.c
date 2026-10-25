/* j/0/savegame.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/savegame.c:37  [anchor-mhash]
struct Result_s *__cdecl SaveGame_SaveInfoScriptFunction(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  int *v3; // ebx
  struct ArgList_s *v4; // edi
  void *v5; // eax
  void *v6; // eax
  void *v7; // eax
  int v8; // ecx
  struct Result_s Rs; // [esp+Ch] [ebp-18h] BYREF

  v3 = (int *)pxContext;
  v4 = ptArgList;
  *((_DWORD *)pxContext + 3) = 0;
  if ( v4->nArguments >= 3 )
  {
    if ( v4->isQVM )
    {
      pxContext = nullptr;
      QVM_EvalArg(&pxContext, 4, v4, 0, 1);
      v5 = pxContext;
    }
    else
    {
      v5 = (void *)Expression_EvalInt(*v4->aptExpression);
    }
    *v3 = (int)v5;
    if ( v4->isQVM )
    {
      pxContext = nullptr;
      QVM_EvalArg(&pxContext, 4, v4, 1, 1);
      v6 = pxContext;
    }
    else
    {
      v6 = (void *)Expression_EvalInt(v4->aptExpression[1]);
    }
    v3[1] = (int)v6;
    if ( v4->isQVM )
    {
      pxContext = nullptr;
      QVM_EvalArg(&pxContext, 4, v4, 2, 1);
      v7 = pxContext;
    }
    else
    {
      v7 = (void *)Expression_EvalInt(v4->aptExpression[2]);
    }
    v8 = *v3;
    v3[2] = (int)v7;
    v3[3] = v8 >= 63;
  }
  Rs.nResult = 0;
  Rs.vResult = 0.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/savegame.c:66  [anchor-strings]
enum bool __cdecl SaveGame_LoadFile(
        struct SaveGame_s *ptSaveGame,
        char *zFilename,
        enum bool isGetInfoOnly,
        struct QTask_s *ptParentQTask)
{
  struct QHashTable_s *v4; // esi
  unsigned int v5; // eax
  int v6; // eax
  struct Script_s *v7; // eax
  struct Script_s *v8; // esi
  struct QHashTable_s *v9; // esi
  unsigned int v10; // eax
  int v11; // eax

  ptSaveGame->nVersion = 0;
  ptSaveGame->nMissionID = 0;
  ptSaveGame->nTicks = 0;
  ptSaveGame->isValid = 0;
  v4 = Symbol_ptSymbolHashTable;
  v5 = Symbol_ptSymbolHashTable->tPrivate.pfHashFunction(
         Symbol_ptSymbolHashTable->tPrivate.nHashTableSize,
         "SaveGameInfo");
  v6 = ((int  (__cdecl *)(struct QHashTable_s *, unsigned int, const void *))Symbol_ptSymbolHashTable->tPrivate.pfFindElement)(v4, v5, (const void *)("SaveGameInfo"));
  if ( !v6 || !*(_DWORD *)(v6 + 20) )
    goto LABEL_10;
  *(_DWORD *)(v6 + 24) = ptSaveGame;
  v7 = Script_New(zFilename);
  v8 = v7;
  if ( v7 )
  {
    Script_isBreakEnabled = isGetInfoOnly;
    Script_Execute(v7);
    if ( isGetInfoOnly == false )
      Serialize_TriggerQTaskEventRecursivelyChildrenFirst(ptParentQTask, Serialize_eDeSerializeDoneQTaskEvent, nullptr);
    Script_isBreakEnabled = false;
    Script_Delete(v8);
  }
  v9 = Symbol_ptSymbolHashTable;
  v10 = Symbol_ptSymbolHashTable->tPrivate.pfHashFunction(
          Symbol_ptSymbolHashTable->tPrivate.nHashTableSize,
          "SaveGameInfo");
  v11 = ((int  (__cdecl *)(struct QHashTable_s *, unsigned int, const void *))Symbol_ptSymbolHashTable->tPrivate.pfFindElement)(v9, v10, (const void *)("SaveGameInfo"));
  if ( !v11 || !*(_DWORD *)(v11 + 20) )
  {
LABEL_10:
    LDebug_Error("Script_SetSymbolContext(): Symbol not found: %s", "SaveGameInfo");
    abort();
  }
  *(_DWORD *)(v11 + 24) = 0;
  return ptSaveGame->isValid;
}

// source: j/0/savegame.c:109  [anchor-caller]
enum bool __cdecl SaveGame_Create(
        char *zFilename,
        struct QTask_s *ptParentQTask,
        struct SaveGame_s *ptSaveGame,
        char *zFileInfo)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct Resource_s *ptResource; };
    struct { char igi2_o1[4]; char zCompiledFilename[264]; };
    struct { char igi2_o2[268]; char zBuffer[1028]; };
    char igi2_extent[1296];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct File_s *v5; // ebx
  unsigned int i; // eax
  unsigned int nType; // eax

  if ( !ptSaveGame->isValid )
    return false;
  v5 = File_New(zFilename, "w");
  if ( !v5 )
    return false;
  sprintf(
    igi2_frame.zBuffer,
    "%s(%d, %d, %d);\r\nBreakScript();\r\n",
    "SaveGameInfo",
    ptSaveGame->nVersion,
    ptSaveGame->nMissionID,
    ptSaveGame->nTicks);
  File_atDevice[v5->eDeviceID].pfWrite(v5->eDeviceID, v5, igi2_frame.zBuffer, strlen(igi2_frame.zBuffer));
  Serialize_SerializeToFile(v5, ptParentQTask);
  if ( v5 == &File_tDummyAsyncFile )
    File_tDummyAsyncFile.isAsync = false;
  else
    File_atDevice[v5->eDeviceID].pfDelete(v5->eDeviceID, v5);
  strcpy(igi2_frame.zCompiledFilename, zFilename);
  for ( i = strlen(igi2_frame.zCompiledFilename); i; --i )
  {
    if ( igi2_frame.zCompiledFilename[i] == 46 )
      break;
  }
  strcpy(&igi2_frame.zCompiledFilename[i], ".qvm");
  Resource_Load(zFilename, nullptr);
  Script_CompileEx(zFilename, zFilename, zFileInfo);
  if ( Resource_IsLoadedInternal(zFilename, &igi2_frame.ptResource) )
  {
    nType = igi2_frame.ptResource->nType;
    if ( nType != 3 && nType != 1 )
      Resource_Remove(igi2_frame.ptResource);
  }
  return true;
}

// source: j/0/savegame.c:163  [anchor-mhash]
enum bool __cdecl SaveGame_Load(
        struct SaveGame_s *ptSaveGame,
        char *zFilename,
        struct QTask_s *ptParentQTask)
{
  return SaveGame_LoadFile(ptSaveGame, zFilename, false, ptParentQTask);
}

// source: j/0/savegame.c:179  [anchor-hash]
enum bool __cdecl SaveGame_Check(struct SaveGame_s *ptSaveGame, char *zFilename)
{
  return SaveGame_LoadFile(ptSaveGame, zFilename, true, nullptr);
}

// source: j/0/savegame.c:192  [anchor-hash]
void __cdecl SaveGame_Open()
{
  Symbol_Register(
    "SaveGameInfo",
    SaveGame_SaveInfoScriptFunction,
    nullptr,
    -1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
}

// source: j/0/savegame.c:205  [anchor-strings]
void __cdecl SaveGame_Close()
{
  Symbol_Remove("SaveGameInfo");
}
