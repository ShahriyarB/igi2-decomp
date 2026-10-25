/* c/0/scriptcompiler.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: c/0/scriptcompiler.c:53  [anchor-callee]
void ScriptCompiler_Error(char *zFormat, ...)
{
  char Buffer[1024]; // [esp+0h] [ebp-400h] BYREF
  va_list ArgList; // [esp+408h] [ebp+8h] BYREF ARGSLOT

  va_start(ArgList, zFormat);
  vsprintf(Buffer, zFormat, ArgList);
  ++ScriptCompiler_nErrors;
  if ( !ScriptCompiler_pfErrorCallback )
  {
    LDebug_Error(Buffer);
    abort();
  }
  ScriptCompiler_pfErrorCallback(Buffer, ScriptCompiler_pxErrorContext);
}

// source: c/0/scriptcompiler.c:109  [anchor-callee]
void ScriptCompiler_Message(char *zFormat, ...)
{
  char Buffer[1024]; // [esp+0h] [ebp-400h] BYREF
  va_list ArgList; // [esp+408h] [ebp+8h] BYREF ARGSLOT

  va_start(ArgList, zFormat);
  if ( ScriptCompiler_pfMessageCallback )
  {
    vsprintf(Buffer, zFormat, ArgList);
    ScriptCompiler_pfMessageCallback(Buffer, ScriptCompiler_pxMessageContext);
  }
}

// source: c/0/scriptcompiler.c:136  [size]
void *__cdecl ScriptCompiler_CreateLabel(char *zLabel, char *zPrefix, void *pxAddress)
{
  return (void *)sprintf(zLabel, (char *const)&stru_688EF4, zPrefix, pxAddress);
}

// source: c/0/scriptcompiler.c:151  [anchor-callee]
void __cdecl ScriptCompiler_EmitOpCode(int eOpCode, struct File_s *ptFile)
{
  File_atDevice[ptFile->eDeviceID].pfWrite(ptFile->eDeviceID, ptFile, (void *)(20 * eOpCode + 128664128), 19u);
}

// source: c/0/scriptcompiler.c:166  [anchor-callee]
void __cdecl ScriptCompiler_EmitLeadIn(struct File_s *ptFile)
{
  File_atDevice[ptFile->eDeviceID].pfWrite(ptFile->eDeviceID, ptFile, ScriptCompiler_zLeadIn, 20u);
}

// source: c/0/scriptcompiler.c:182  [anchor-callee]
void __cdecl ScriptCompiler_EmitEOL(struct File_s *ptFile)
{
  File_atDevice[ptFile->eDeviceID].pfWrite(ptFile->eDeviceID, ptFile, &stru_6A4CDC, 1u);
}

// source: c/0/scriptcompiler.c:200  [anchor-hash]
char *__cdecl ScriptCompiler_EmitString(struct File_s *ptFile, char *zString)
{
  File_atDevice[ptFile->eDeviceID].pfWrite(ptFile->eDeviceID, ptFile, &word_689EA8, 1u);
  if ( *zString )
  {
    do
    {
      switch ( *zString )
      {
        case 9:
        case 0xA:
        case 0xD:
          File_atDevice[ptFile->eDeviceID].pfWrite(ptFile->eDeviceID, ptFile, &unk_688EF0, 2u);
          break;
        case 0x22:
          File_atDevice[ptFile->eDeviceID].pfWrite(ptFile->eDeviceID, ptFile, &unk_688EEC, 2u);
          break;
        case 0x5C:
          File_atDevice[ptFile->eDeviceID].pfWrite(ptFile->eDeviceID, ptFile, &unk_688EE8, 2u);
          break;
        default:
          File_atDevice[ptFile->eDeviceID].pfWrite(ptFile->eDeviceID, ptFile, zString, 1u);
          break;
      }
    }
    while ( *++zString );
  }
  return (char *)File_atDevice[ptFile->eDeviceID].pfWrite(ptFile->eDeviceID, ptFile, &word_689EA8, 1u);
}

// source: c/0/scriptcompiler.c:250  [anchor-callee]
void __cdecl ScriptCompiler_EmitWord(struct File_s *ptFile, char *zString)
{
  File_atDevice[ptFile->eDeviceID].pfWrite(ptFile->eDeviceID, ptFile, zString, strlen(zString));
}

// source: c/0/scriptcompiler.c:265  [anchor-hash]
int __cdecl ScriptCompiler_EmitInteger(struct File_s *ptFile, int nValue)
{
  char zTemp[256]; // [esp+0h] [ebp-100h] BYREF

  sprintf(zTemp, (char *const)&g_ptNetManager.tReceiveCounters.tCounters[9].nBytes, nValue);
  return File_atDevice[ptFile->eDeviceID].pfWrite(ptFile->eDeviceID, ptFile, zTemp, strlen(zTemp));
}

// source: c/0/scriptcompiler.c:284  [anchor-callee]
void __cdecl ScriptCompiler_EmitReal(struct File_s *ptFile, double vValue)
{
  char zTemp[260]; // [esp+0h] [ebp-104h] BYREF

  sprintf(zTemp, "%f", vValue);
  File_atDevice[ptFile->eDeviceID].pfWrite(ptFile->eDeviceID, ptFile, zTemp, strlen(zTemp));
}

// source: c/0/scriptcompiler.c:304  [anchor-strings]
void __cdecl ScriptCompiler_ConvertExpressionRecursive(struct File_s *ptFile, struct QExpression_s *ptExpression)
{
  #pragma pack(push, 1)
  union
  {
    struct { int i; };
    struct { char igi2_o1[4]; char Buffer[68]; };
    char igi2_extent[72];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QExpression_s *v2; // ebx
  struct File_s *v3; // esi
  struct ArgList_s *ptArgList; // ebx
  int v5; // ebp
  int j; // esi
  struct QExpression_s *ptExpressiona = *(struct QExpression_s * *)&ptExpression; // [esp+64h] [ebp+8h] ARGSLOT

  v2 = ptExpression;
  if ( ptExpression )
  {
    while ( 2 )
    {
      switch ( v2->tExpressionHeader.eType )
      {
        case 1:
          v3 = ptFile;
          ScriptCompiler_EmitOpCode(8, ptFile);
          ScriptCompiler_EmitInteger(ptFile, v2->uValue.nValue);
LABEL_6:
          ScriptCompiler_EmitEOL(v3);
          return;
        case 2:
          ScriptCompiler_EmitOpCode(13, ptFile);
          ScriptCompiler_EmitString(ptFile, v2->uValue.zString);
          ScriptCompiler_EmitEOL(ptFile);
          return;
        case 3:
          ScriptCompiler_EmitOpCode(11, ptFile);
          ScriptCompiler_EmitReal(ptFile, v2->uValue.vValue);
          ScriptCompiler_EmitEOL(ptFile);
          return;
        case 4:
        case 5:
          ScriptCompiler_EmitOpCode(17, ptFile);
          ScriptCompiler_EmitWord(ptFile, v2->uValue.tExpressionSymbolContext.zSymbolname);
          ScriptCompiler_EmitEOL(ptFile);
          ptArgList = v2->uValue.tExpressionSymbolContext.ptArgList;
          if ( ptArgList )
          {
            ptExpressiona = (struct QExpression_s *)ptArgList->nArguments;
            ScriptCompiler_EmitOpCode(7, ptFile);
            ScriptCompiler_EmitWord(ptFile, word_692AD0);
            v5 = 0;
            for ( igi2_frame.i = 0; v5 < (int)ptExpressiona; ++igi2_frame.i )
            {
              if ( igi2_frame.i >= 5 )
              {
                igi2_frame.i = 0;
                ScriptCompiler_EmitEOL(ptFile);
                ScriptCompiler_EmitLeadIn(ptFile);
              }
              sprintf(igi2_frame.Buffer, (char *const)&stru_688EF4, &off_688EE4, ptArgList->aptExpression[v5]);
              ScriptCompiler_EmitWord(ptFile, igi2_frame.Buffer);
              if ( v5 < (int)&ptExpressiona[-1].nLinenumber + 3 )
                ScriptCompiler_EmitWord(ptFile, word_6A1DBC);
              ++v5;
            }
            ScriptCompiler_EmitWord(ptFile, (char *)&g_zSpriteName_0.tQTaskChildren.ptMiddle);
            File_atDevice[ptFile->eDeviceID].pfWrite(ptFile->eDeviceID, ptFile, &stru_6A4CDC, 1u);
            sprintf(igi2_frame.Buffer, (char *const)&stru_688EF4, &unk_688EE0, ptArgList);
            ScriptCompiler_EmitOpCode(3, ptFile);
            ScriptCompiler_EmitWord(ptFile, igi2_frame.Buffer);
            File_atDevice[ptFile->eDeviceID].pfWrite(ptFile->eDeviceID, ptFile, &stru_6A4CDC, 1u);
            for ( j = 0; j < (int)ptExpressiona; ++j )
            {
              sprintf(igi2_frame.Buffer, (char *const)&stru_688EF4, &off_688EE4, ptArgList->aptExpression[j]);
              File_atDevice[ptFile->eDeviceID].pfWrite(ptFile->eDeviceID, ptFile, igi2_frame.Buffer, strlen(igi2_frame.Buffer));
              File_atDevice[ptFile->eDeviceID].pfWrite(ptFile->eDeviceID, ptFile, ":", strlen(":"));
              File_atDevice[ptFile->eDeviceID].pfWrite(ptFile->eDeviceID, ptFile, &stru_6A4CDC, 1u);
              ScriptCompiler_ConvertExpressionRecursive(ptFile, ptArgList->aptExpression[j]);
              File_atDevice[ptFile->eDeviceID].pfWrite(ptFile->eDeviceID, ptFile, ScriptCompiler_azOpCode, 19u);
              File_atDevice[ptFile->eDeviceID].pfWrite(ptFile->eDeviceID, ptFile, &stru_6A4CDC, 1u);
            }
            sprintf(igi2_frame.Buffer, (char *const)&stru_688EF4, &unk_688EE0, ptArgList);
            File_atDevice[ptFile->eDeviceID].pfWrite(ptFile->eDeviceID, ptFile, igi2_frame.Buffer, strlen(igi2_frame.Buffer));
            File_atDevice[ptFile->eDeviceID].pfWrite(ptFile->eDeviceID, ptFile, ":", strlen(":"));
            File_atDevice[ptFile->eDeviceID].pfWrite(ptFile->eDeviceID, ptFile, &stru_6A4CDC, 1u);
          }
          return;
        case 6:
          v2 = v2->uValue.ptExpression;
          if ( !v2 )
            return;
          continue;
        case 7:
          ScriptCompiler_ConvertExpressionRecursive(ptFile, v2->uValue.ptExpression);
          ScriptCompiler_EmitOpCode(4, ptFile);
          sprintf(igi2_frame.Buffer, (char *const)&stru_688EF4, &dword_688ED8, v2->ptRight);
          ScriptCompiler_EmitWord(ptFile, igi2_frame.Buffer);
          ScriptCompiler_EmitEOL(ptFile);
          ScriptCompiler_ConvertExpressionRecursive(ptFile, v2->ptLeft);
          ScriptCompiler_EmitOpCode(3, ptFile);
          sprintf(igi2_frame.Buffer, (char *const)&stru_688EF4, "CON", v2);
          ScriptCompiler_EmitWord(ptFile, igi2_frame.Buffer);
          sprintf(igi2_frame.Buffer, (char *const)&stru_688EF4, &dword_688ED8, v2->ptRight);
          ScriptCompiler_EmitWord(ptFile, igi2_frame.Buffer);
          ScriptCompiler_EmitEOL(ptFile);
          ScriptCompiler_ConvertExpressionRecursive(ptFile, v2->ptRight);
          sprintf(igi2_frame.Buffer, (char *const)&stru_688EF4, "CON", v2);
          ScriptCompiler_EmitWord(ptFile, igi2_frame.Buffer);
          ScriptCompiler_EmitWord(ptFile, ":");
          ScriptCompiler_EmitEOL(ptFile);
          return;
        case 8:
          v3 = ptFile;
          if ( v2->ptLeft )
            ScriptCompiler_ConvertExpressionRecursive(ptFile, v2->ptLeft);
          if ( v2->tExpressionHeader.eOpType == 24 )
          {
            ScriptCompiler_EmitOpCode(24, ptFile);
            ScriptCompiler_EmitEOL(ptFile);
          }
          if ( v2->ptRight )
            ScriptCompiler_ConvertExpressionRecursive(ptFile, v2->ptRight);
          switch ( v2->tExpressionHeader.eOpType )
          {
            case 1:
              ScriptCompiler_EmitOpCode(25, ptFile);
              ScriptCompiler_EmitEOL(ptFile);
              return;
            case 2:
              ScriptCompiler_EmitOpCode(26, ptFile);
              ScriptCompiler_EmitEOL(ptFile);
              return;
            case 3:
              ScriptCompiler_EmitOpCode(43, ptFile);
              ScriptCompiler_EmitEOL(ptFile);
              return;
            case 4:
              ScriptCompiler_EmitOpCode(44, ptFile);
              ScriptCompiler_EmitEOL(ptFile);
              return;
            case 5:
              ScriptCompiler_EmitOpCode(27, ptFile);
              ScriptCompiler_EmitEOL(ptFile);
              return;
            case 6:
              ScriptCompiler_EmitOpCode(28, ptFile);
              ScriptCompiler_EmitEOL(ptFile);
              return;
            case 8:
              ScriptCompiler_EmitOpCode(32, ptFile);
              ScriptCompiler_EmitEOL(ptFile);
              return;
            case 9:
              ScriptCompiler_EmitOpCode(33, ptFile);
              ScriptCompiler_EmitEOL(ptFile);
              return;
            case 0xA:
              ScriptCompiler_EmitOpCode(31, ptFile);
              ScriptCompiler_EmitEOL(ptFile);
              return;
            case 0xB:
              ScriptCompiler_EmitOpCode(29, ptFile);
              ScriptCompiler_EmitEOL(ptFile);
              return;
            case 0xC:
              ScriptCompiler_EmitOpCode(30, ptFile);
              ScriptCompiler_EmitEOL(ptFile);
              return;
            case 0xD:
              ScriptCompiler_EmitOpCode(45, ptFile);
              ScriptCompiler_EmitEOL(ptFile);
              return;
            case 0xE:
              ScriptCompiler_EmitOpCode(36, ptFile);
              ScriptCompiler_EmitEOL(ptFile);
              return;
            case 0xF:
              ScriptCompiler_EmitOpCode(37, ptFile);
              ScriptCompiler_EmitEOL(ptFile);
              return;
            case 0x10:
              ScriptCompiler_EmitOpCode(38, ptFile);
              ScriptCompiler_EmitEOL(ptFile);
              return;
            case 0x11:
              ScriptCompiler_EmitOpCode(40, ptFile);
              ScriptCompiler_EmitEOL(ptFile);
              return;
            case 0x12:
              ScriptCompiler_EmitOpCode(39, ptFile);
              ScriptCompiler_EmitEOL(ptFile);
              return;
            case 0x13:
              ScriptCompiler_EmitOpCode(41, ptFile);
              ScriptCompiler_EmitEOL(ptFile);
              return;
            case 0x14:
              ScriptCompiler_EmitOpCode(46, ptFile);
              ScriptCompiler_EmitEOL(ptFile);
              return;
            case 0x18:
              goto LABEL_6;
            case 0x19:
              ScriptCompiler_EmitOpCode(42, ptFile);
              ScriptCompiler_EmitEOL(ptFile);
              return;
            case 0x1B:
              ScriptCompiler_EmitOpCode(35, ptFile);
              ScriptCompiler_EmitEOL(ptFile);
              return;
            case 0x1C:
              ScriptCompiler_EmitOpCode(34, ptFile);
              ScriptCompiler_EmitEOL(ptFile);
              return;
            default:
              LDebug_Error("Unknown operator in expression.");
              goto LABEL_51;
          }
        default:
          LDebug_Error("Unknown expression type");
LABEL_51:
          abort();
      }
    }
  }
}

// source: c/0/scriptcompiler.c:561  [anchor-strings]
void __cdecl ScriptCompiler_ConvertControlBlockRecursive(struct File_s *ptFile, struct ScriptControlBlock_s *ptBlock)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct ScriptControlBlock_s *v11; };
    struct { char igi2_o1[4]; char Buffer[68]; };
    char igi2_extent[72];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QExpression_s *v3; // ebx
  struct ScriptControlBlock_s *ptNext; // ebx
  struct ScriptControlBlock_s *i; // esi
  struct File_s *v6; // esi
  enum ScriptControlBlockType_e eBlockType; // edi
  struct ScriptControlBlock_s *v8; // eax
  char *v9; // ecx
  char *v10; // eax
  struct ScriptControlBlock_s *ptBlocka = *(struct ScriptControlBlock_s * *)&ptBlock; // [esp+64h] [ebp+8h] ARGSLOT

  switch ( ptBlock->eBlockType )
  {
    case SCRIPTCONTROLBLOCK_TYPE_BLOCK:
      ptNext = ptBlock[1].ptNext;
      for ( i = ptNext->ptNext; i; i = i->ptNext )
      {
        ScriptCompiler_ConvertControlBlockRecursive(ptFile, ptNext);
        ptNext = i;
      }
      return;
    case SCRIPTCONTROLBLOCK_TYPE_IF:
      v6 = ptFile;
      ScriptCompiler_ConvertExpressionRecursive(ptFile, (struct QExpression_s *)ptBlock[1].ptNext);
      File_atDevice[v6->eDeviceID].pfWrite(v6->eDeviceID, v6, &ScriptCompiler_azOpCode[80], 19u);
      sprintf(igi2_frame.Buffer, (char *const)&stru_688EF4, "EL", ptBlock);
      File_atDevice[ptFile->eDeviceID].pfWrite(ptFile->eDeviceID, ptFile, igi2_frame.Buffer, strlen(igi2_frame.Buffer));
      File_atDevice[ptFile->eDeviceID].pfWrite(ptFile->eDeviceID, ptFile, &stru_6A4CDC, 1u);
      ScriptCompiler_ConvertControlBlockRecursive(ptFile, ptBlock[1].ptPrev);
      File_atDevice[ptFile->eDeviceID].pfWrite(ptFile->eDeviceID, ptFile, &ScriptCompiler_azOpCode[60], 19u);
      sprintf(igi2_frame.Buffer, (char *const)&stru_688EF4, "IF", ptBlock);
      File_atDevice[ptFile->eDeviceID].pfWrite(ptFile->eDeviceID, ptFile, igi2_frame.Buffer, strlen(igi2_frame.Buffer));
      File_atDevice[ptFile->eDeviceID].pfWrite(ptFile->eDeviceID, ptFile, &stru_6A4CDC, 1u);
      eBlockType = ptBlock[1].eBlockType;
      v8 = ptBlock;
      ptBlocka = *(struct ScriptControlBlock_s **)eBlockType;
      if ( *(_DWORD *)eBlockType )
      {
        do
        {
          sprintf(igi2_frame.Buffer, (char *const)&stru_688EF4, "EL", v8);
          File_atDevice[ptFile->eDeviceID].pfWrite(ptFile->eDeviceID, ptFile, igi2_frame.Buffer, strlen(igi2_frame.Buffer));
          File_atDevice[ptFile->eDeviceID].pfWrite(ptFile->eDeviceID, ptFile, ":", strlen(":"));
          File_atDevice[ptFile->eDeviceID].pfWrite(ptFile->eDeviceID, ptFile, &stru_6A4CDC, 1u);
          igi2_frame.v11 = (struct ScriptControlBlock_s *)eBlockType;
          ScriptCompiler_ConvertExpressionRecursive(ptFile, *(struct QExpression_s **)(eBlockType + 12));
          File_atDevice[ptFile->eDeviceID].pfWrite(ptFile->eDeviceID, ptFile, &ScriptCompiler_azOpCode[80], 19u);
          sprintf(igi2_frame.Buffer, (char *const)&stru_688EF4, "EL", eBlockType);
          File_atDevice[ptFile->eDeviceID].pfWrite(ptFile->eDeviceID, ptFile, igi2_frame.Buffer, strlen(igi2_frame.Buffer));
          File_atDevice[ptFile->eDeviceID].pfWrite(ptFile->eDeviceID, ptFile, &stru_6A4CDC, 1u);
          ScriptCompiler_ConvertControlBlockRecursive(ptFile, *(struct ScriptControlBlock_s **)(eBlockType + 16));
          File_atDevice[ptFile->eDeviceID].pfWrite(ptFile->eDeviceID, ptFile, &ScriptCompiler_azOpCode[60], 19u);
          sprintf(igi2_frame.Buffer, (char *const)&stru_688EF4, "IF", ptBlock);
          File_atDevice[ptFile->eDeviceID].pfWrite(ptFile->eDeviceID, ptFile, igi2_frame.Buffer, strlen(igi2_frame.Buffer));
          File_atDevice[ptFile->eDeviceID].pfWrite(ptFile->eDeviceID, ptFile, &stru_6A4CDC, 1u);
          eBlockType = (enum ScriptControlBlockType_e)ptBlocka;
          ptBlocka = ptBlocka->ptNext;
          v8 = igi2_frame.v11;
        }
        while ( ptBlocka );
      }
      sprintf(igi2_frame.Buffer, (char *const)&stru_688EF4, "EL", v8);
      File_atDevice[ptFile->eDeviceID].pfWrite(ptFile->eDeviceID, ptFile, igi2_frame.Buffer, strlen(igi2_frame.Buffer));
      File_atDevice[ptFile->eDeviceID].pfWrite(ptFile->eDeviceID, ptFile, ":", strlen(":"));
      File_atDevice[ptFile->eDeviceID].pfWrite(ptFile->eDeviceID, ptFile, &stru_6A4CDC, 1u);
      if ( ptBlock[2].eBlockType )
        ScriptCompiler_ConvertControlBlockRecursive(ptFile, (struct ScriptControlBlock_s *)ptBlock[2].eBlockType);
      sprintf(igi2_frame.Buffer, (char *const)&stru_688EF4, "IF", ptBlock);
      File_atDevice[ptFile->eDeviceID].pfWrite(ptFile->eDeviceID, ptFile, igi2_frame.Buffer, strlen(igi2_frame.Buffer));
      v9 = "";
      v10 = &asc_688EDC[strlen(":") + 1];
      goto LABEL_13;
    case SCRIPTCONTROLBLOCK_TYPE_WHILE:
      sprintf(igi2_frame.Buffer, (char *const)&stru_688EF4, "WL", ptBlock);
      v6 = ptFile;
      File_atDevice[ptFile->eDeviceID].pfWrite(ptFile->eDeviceID, ptFile, igi2_frame.Buffer, strlen(igi2_frame.Buffer));
      File_atDevice[ptFile->eDeviceID].pfWrite(ptFile->eDeviceID, ptFile, ":", strlen(":"));
      File_atDevice[ptFile->eDeviceID].pfWrite(ptFile->eDeviceID, ptFile, &stru_6A4CDC, 1u);
      ScriptCompiler_ConvertExpressionRecursive(ptFile, (struct QExpression_s *)ptBlock[1].ptNext);
      File_atDevice[ptFile->eDeviceID].pfWrite(ptFile->eDeviceID, ptFile, &ScriptCompiler_azOpCode[80], 19u);
      sprintf(igi2_frame.Buffer, (char *const)&stru_688EF4, "WE", ptBlock);
      File_atDevice[ptFile->eDeviceID].pfWrite(ptFile->eDeviceID, ptFile, igi2_frame.Buffer, strlen(igi2_frame.Buffer));
      File_atDevice[ptFile->eDeviceID].pfWrite(ptFile->eDeviceID, ptFile, &stru_6A4CDC, 1u);
      ScriptCompiler_ConvertControlBlockRecursive(ptFile, ptBlock[1].ptPrev);
      File_atDevice[ptFile->eDeviceID].pfWrite(ptFile->eDeviceID, ptFile, &ScriptCompiler_azOpCode[60], 19u);
      sprintf(igi2_frame.Buffer, (char *const)&stru_688EF4, "WL", ptBlock);
      File_atDevice[ptFile->eDeviceID].pfWrite(ptFile->eDeviceID, ptFile, igi2_frame.Buffer, strlen(igi2_frame.Buffer));
      File_atDevice[ptFile->eDeviceID].pfWrite(ptFile->eDeviceID, ptFile, &stru_6A4CDC, 1u);
      sprintf(igi2_frame.Buffer, (char *const)&stru_688EF4, "WE", ptBlock);
      File_atDevice[ptFile->eDeviceID].pfWrite(ptFile->eDeviceID, ptFile, igi2_frame.Buffer, strlen(igi2_frame.Buffer));
      v9 = "";
      v10 = &asc_688EDC[strlen(":") + 1];
LABEL_13:
      File_atDevice[v6->eDeviceID].pfWrite(v6->eDeviceID, v6, ":", v10 - v9);
      File_atDevice[v6->eDeviceID].pfWrite(v6->eDeviceID, v6, &stru_6A4CDC, 1u);
      break;
    case SCRIPTCONTROLBLOCK_TYPE_STATEMENT:
      v3 = (struct QExpression_s *)ptBlock[1].ptNext;
      if ( v3 )
      {
        ScriptCompiler_ConvertExpressionRecursive(ptFile, v3);
        ScriptCompiler_EmitOpCode(24, ptFile);
        ScriptCompiler_EmitEOL(ptFile);
      }
      break;
    default:
      LDebug_Error("Internal error: Unknown statement block type.");
      abort();
  }
}

// source: c/0/scriptcompiler.c:715  [anchor-strings]
int __cdecl ScriptCompiler_CompileScript(char *zDestinationFile, struct Script_s *ptScript)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct QVMGetNameContext_s tGetNameContext; };
    struct { char igi2_o1[8]; struct __anon_2f08 tControlBlockList; };
    struct { char igi2_o2[20]; struct InputStream_s tInputStream; };
    struct { char igi2_o3[52]; struct ParseContext_s tParseContext; };
    struct { char igi2_o4[100]; char zTokenBuffer[2048]; };
    char igi2_extent[2152];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v2; // ebp
  char *v3; // esi
  void (__cdecl **v4)(void *, void *, int, int); // edi
  char v5; // al
  struct QVMGetNameContext_s *p_tGetNameContext; // edx
  char *v7; // ecx
  int nSize; // esi
  char *zScript; // ebp
  struct File_s *v10; // esi
  struct ScriptControlBlock_s *v11; // eax
  struct ScriptControlBlock_s *ptHead; // eax
  struct ScriptControlBlock_s *i; // esi
  struct ScriptControlBlock_s *v14; // eax

  File_Remove(zDestinationFile);
  strcpy(ScriptCompiler_zLeadIn, "                    ");
  igi2_frame.tControlBlockList.ptHead = (struct ScriptControlBlock_s *)&igi2_frame.tControlBlockList.ptMiddle;
  igi2_frame.tControlBlockList.ptTail = (struct ScriptControlBlock_s *)&igi2_frame.tControlBlockList;
  igi2_frame.tControlBlockList.ptMiddle = nullptr;
  ScriptCompiler_nErrors = 0;
  v2 = 0;
  v3 = ScriptCompiler_azOpCode;
  v4 = &QVM_atOpCode[0].apfOpCodeEvent[1];
  do
  {
    if ( (int)v4 >= 139287148 && (int)v4 < 139288324 && *v4 )
      (*v4)(&igi2_frame.tGetNameContext, nullptr, v2, 1);
    strcpy(v3, "                   ");
    v5 = igi2_frame.tGetNameContext.zName[0];
    if ( igi2_frame.tGetNameContext.zName[0] )
    {
      p_tGetNameContext = &igi2_frame.tGetNameContext;
      v7 = v3 + 11;
      do
      {
        *v7 = v5;
        v5 = p_tGetNameContext->zName[1];
        ++v7;
        p_tGetNameContext = (struct QVMGetNameContext_s *)((char *)p_tGetNameContext + 1);
      }
      while ( v5 );
    }
    v4 += 6;
    ++v2;
    v3 += 20;
  }
  while ( (int)v4 < 139288324 );
  igi2_frame.tParseContext.tToken.ptHead = (struct QTokenItem_s *)&igi2_frame.tParseContext.tToken.ptMiddle;
  nSize = ptScript->nSize;
  zScript = ptScript->zScript;
  igi2_frame.tParseContext.tToken.zToken = igi2_frame.zTokenBuffer;
  igi2_frame.tParseContext.ptInputStream = &igi2_frame.tInputStream;
  Script_isError = false;
  igi2_frame.tParseContext.tToken.nMaxTokenSize = 2048;
  igi2_frame.tParseContext.tToken.ptTail = (struct QTokenItem_s *)&igi2_frame.tParseContext.tToken;
  igi2_frame.tParseContext.tToken.ptMiddle = nullptr;
  igi2_frame.tInputStream.zBuffer = (char *)Mem_AllocFn(Script_nInputBufferSize, 4);
  memset(igi2_frame.tInputStream.zBuffer, 0, Script_nInputBufferSize);
  igi2_frame.tInputStream.zData = igi2_frame.tInputStream.zBuffer;
  igi2_frame.tInputStream.pxUserdata = zScript;
  igi2_frame.tInputStream.pfGetInput = SingleLine_GetInput;
  igi2_frame.tInputStream.nSize = nSize;
  igi2_frame.tInputStream.nNextLine = 0;
  igi2_frame.tInputStream.nLine = 0;
  igi2_frame.tInputStream.nPos = 0;
  v10 = File_New(zDestinationFile, "w");
  if ( v10 )
  {
    ScriptCompiler_Message("Parsing script and generating assembly code.\n");
    *(_DWORD *)igi2_frame.tGetNameContext.zName = 0;
    if ( Token_GetToken(&igi2_frame.tParseContext, &igi2_frame.tParseContext.tToken) )
    {
      while ( ScriptControl_ParseStatementBlock(&igi2_frame.tParseContext, (struct ScriptControlBlock_s **)&igi2_frame.tGetNameContext) )
      {
        v11 = (struct ScriptControlBlock_s *)List_AddTail(*(_DWORD **)igi2_frame.tGetNameContext.zName, (int)&igi2_frame.tControlBlockList);
        ScriptCompiler_ConvertControlBlockRecursive(v10, v11);
        *(_DWORD *)igi2_frame.tGetNameContext.zName = 0;
        if ( Token_GetToken(&igi2_frame.tParseContext, &igi2_frame.tParseContext.tToken) == false )
          goto LABEL_16;
      }
      ++ScriptCompiler_nErrors;
    }
LABEL_16:
    File_atDevice[v10->eDeviceID].pfWrite(v10->eDeviceID, v10, ScriptCompiler_azOpCode, 19u);
    File_atDevice[v10->eDeviceID].pfWrite(v10->eDeviceID, v10, &stru_6A4CDC, 1u);
    if ( v10 == &File_tDummyAsyncFile )
      File_tDummyAsyncFile.isAsync = false;
    else
      File_atDevice[v10->eDeviceID].pfDelete(v10->eDeviceID, v10);
  }
  else
  {
    ScriptCompiler_Error("Failed to open file '%s' for writing.", zDestinationFile);
  }
  ptHead = igi2_frame.tControlBlockList.ptHead;
  for ( i = igi2_frame.tControlBlockList.ptHead->ptNext; i; i = i->ptNext )
  {
    v14 = (struct ScriptControlBlock_s *)Node_Remove(ptHead);
    ScriptControlBlock_Delete(v14);
    ptHead = i;
  }
  InputStream_DeAlloc(&igi2_frame.tInputStream);
  return ScriptCompiler_nErrors;
}

// source: c/0/scriptcompiler.c:821  [size]
void __cdecl ScriptCompiler_SetErrorCallback(
        void (__cdecl *pfCallback)(char *, void *),
        void *pxContext)
{
  ScriptCompiler_pfErrorCallback = pfCallback;
  ScriptCompiler_pxErrorContext = pxContext;
}

// source: c/0/scriptcompiler.c:835  [size]
void __cdecl ScriptCompiler_SetWarningCallback(
        void (__cdecl *pfCallback)(char *, void *),
        void *pxContext)
{
  ScriptCompiler_pfWarningCallback = pfCallback;
  ScriptCompiler_pxWarningContext = pxContext;
}

// source: c/0/scriptcompiler.c:849  [size]
void __cdecl ScriptCompiler_SetMessageCallback(
        void (__cdecl *pfCallback)(char *, void *),
        void *pxContext)
{
  ScriptCompiler_pfMessageCallback = pfCallback;
  ScriptCompiler_pxMessageContext = pxContext;
}

// source: c/0/scriptcompiler.c:863  [size]
void __cdecl ScriptCompiler_Open()
{
  ScriptCompiler_pfErrorCallback = nullptr;
  ScriptCompiler_pfMessageCallback = nullptr;
  ScriptCompiler_pfWarningCallback = nullptr;
  ScriptCompiler_pxErrorContext = nullptr;
  ScriptCompiler_pxWarningContext = nullptr;
  ScriptCompiler_pxMessageContext = nullptr;
}

// source: c/0/scriptcompiler.c:881  [size]
void __cdecl ScriptCompiler_Close()
{
  ;
}
