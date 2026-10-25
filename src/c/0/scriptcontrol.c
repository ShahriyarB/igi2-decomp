/* c/0/scriptcontrol.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: c/0/scriptcontrol.c:33  [size]
int __cdecl ScriptControl_GetLinenumber(struct ParseContext_s *ptParseContext)
{
  return ptParseContext->ptInputStream->nLine + 1;
}

// source: c/0/scriptcontrol.c:50  [anchor-hash]
int __cdecl ScriptControl_GetKeywordId(struct ParseContext_s *ptParseContext)
{
  char *zToken; // eax

  zToken = ptParseContext->tToken.zToken;
  if ( !strcmp(zToken, "{") )
    return 1;
  if ( !strcmp(zToken, "}") )
    return 2;
  if ( !strcmp(zToken, "if") )
    return 3;
  if ( !strcmp(zToken, "else") )
    return 4;
  if ( !strcmp(zToken, "do") )
    return 5;
  if ( !strcmp(zToken, "while") )
    return 6;
  return strcmp(zToken, (char *)&off_688B78) != 0 ? 0 : 7;
}

// source: c/0/scriptcontrol.c:103  [anchor-strings]
enum bool __cdecl ScriptControl_ParseStatementBlock(
        struct ParseContext_s *ptParseContext,
        struct ScriptControlBlock_s **pptScriptControlBlock)
{
  #pragma pack(push, 1)
  union
  {
    struct { enum bool isOneStatement; };
    struct { char igi2_o1[4]; struct ScriptControlBlock_s *ptControlBlock; };
    struct { char igi2_o2[8]; struct QExpression_s *ptExpression; };
    char igi2_extent[12];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct ScriptControlBlock_s *v2; // edi
  int KeywordId; // eax
  _DWORD *v5; // eax
  struct QExpression_s *v6; // edx

  *pptScriptControlBlock = nullptr;
  v2 = (struct ScriptControlBlock_s *)Mem_AllocFn(24, 4);
  v2[1].ptNext = (struct ScriptControlBlock_s *)((char *)v2 + 16);
  v2[1].ptPrev = nullptr;
  v2->eBlockType = SCRIPTCONTROLBLOCK_TYPE_BLOCK;
  v2->ptPrev = nullptr;
  v2->ptNext = nullptr;
  v2[1].eBlockType = (enum ScriptControlBlockType_e)&v2[1];
  if ( ScriptControl_GetKeywordId(ptParseContext) != 1 )
  {
    igi2_frame.isOneStatement = true;
    while ( 1 )
    {
LABEL_6:
      KeywordId = ScriptControl_GetKeywordId(ptParseContext);
      if ( KeywordId )
      {
        if ( KeywordId == 2 )
        {
          if ( igi2_frame.isOneStatement )
          {
            Script_Error("Unexpected '}' in line %d", ptParseContext->ptInputStream->nLine + 1);
            ScriptControlBlock_Delete(v2);
            return false;
          }
          else
          {
            *pptScriptControlBlock = v2;
            return true;
          }
        }
        if ( ScriptControl_ParseControlBlock(ptParseContext, &igi2_frame.ptControlBlock) == false )
          goto LABEL_21;
        List_AddTail(igi2_frame.ptControlBlock, (int)&v2[1]);
      }
      else
      {
        if ( !Expression_Parse(ptParseContext, &igi2_frame.ptExpression, 0, 0) )
        {
          if ( Script_isError )
            Script_Error("Script error: Aborting.\n");
          goto LABEL_21;
        }
        v5 = Mem_AllocFn(16, 4);
        v6 = igi2_frame.ptExpression;
        v5[2] = 7;
        v5[1] = 0;
        *v5 = 0;
        v5[3] = v6;
        List_AddTail(v5, (int)&v2[1]);
      }
      if ( igi2_frame.isOneStatement )
      {
        *pptScriptControlBlock = v2;
        return true;
      }
      if ( Token_GetToken(ptParseContext, &ptParseContext->tToken) == false )
      {
        Script_Error("Unexpected end of file.");
LABEL_21:
        ScriptControlBlock_Delete(v2);
        return false;
      }
    }
  }
  if ( Token_GetToken(ptParseContext, &ptParseContext->tToken) )
  {
    igi2_frame.isOneStatement = false;
    goto LABEL_6;
  }
  Script_Error("Unexpected end of file.");
  ScriptControlBlock_Delete(v2);
  return false;
}

// source: c/0/scriptcontrol.c:217  [anchor-strings]
enum bool __cdecl ScriptControl_ParseIfBlock(
        struct ParseContext_s *ptParseContext,
        struct ScriptControlBlock_s **pptScriptControlBlock)
{
  _DWORD *v3; // ebx
  bool v4; // zf
  struct QToken_s *p_tToken; // eax
  _DWORD *v6; // edi

  v3 = Mem_AllocFn(36, 4);
  memset(v3, 0, 0x24u);
  v3[1] = 0;
  *v3 = 0;
  v3[5] = v3 + 6;
  v3[6] = 0;
  v3[2] = 2;
  v3[7] = v3 + 5;
  *pptScriptControlBlock = (struct ScriptControlBlock_s *)v3;
  if ( Token_GetToken(ptParseContext, &ptParseContext->tToken) == false )
    goto LABEL_21;
  if ( *ptParseContext->tToken.zToken != 40
    || Token_GetToken(ptParseContext, &ptParseContext->tToken) == false
    || !Expression_Parse(ptParseContext, (struct QExpression_s **)v3 + 3, 0, 0) )
  {
    goto LABEL_22;
  }
  if ( Token_GetToken(ptParseContext, &ptParseContext->tToken) == false )
    goto LABEL_21;
  if ( ScriptControl_ParseStatementBlock(ptParseContext, (struct ScriptControlBlock_s **)v3 + 4) == false )
  {
LABEL_22:
    ScriptControlBlock_Delete(*pptScriptControlBlock);
    *pptScriptControlBlock = nullptr;
    return false;
  }
  if ( Token_GetToken(ptParseContext, &ptParseContext->tToken) == false )
    return true;
  v4 = ScriptControl_GetKeywordId(ptParseContext) == 4;
  p_tToken = &ptParseContext->tToken;
  if ( !v4 )
  {
LABEL_26:
    Token_PutToken(&ptParseContext->tToken, p_tToken);
    return true;
  }
  if ( Token_GetToken(ptParseContext, p_tToken) )
  {
    if ( ScriptControl_GetKeywordId(ptParseContext) == 3 )
    {
      if ( Token_GetToken(ptParseContext, &ptParseContext->tToken) )
      {
        while ( *ptParseContext->tToken.zToken == 40 )
        {
          v6 = Mem_AllocFn(20, 4);
          *v6 = 0;
          v6[1] = 0;
          v6[2] = 0;
          v6[3] = 0;
          v6[4] = 0;
          v6[1] = 0;
          *v6 = 0;
          v6[2] = 3;
          List_AddTail(v6, (int)(v3 + 5));
          if ( !Expression_Build(ptParseContext, (struct QExpression_s **)v6 + 3, 0) )
            break;
          if ( Token_GetToken(ptParseContext, &ptParseContext->tToken) == false )
            goto LABEL_21;
          if ( ScriptControl_ParseStatementBlock(ptParseContext, (struct ScriptControlBlock_s **)v6 + 4) == false )
            break;
          if ( Token_GetToken(ptParseContext, &ptParseContext->tToken) == false )
            return true;
          v4 = ScriptControl_GetKeywordId(ptParseContext) == 4;
          p_tToken = &ptParseContext->tToken;
          if ( !v4 )
            goto LABEL_26;
          if ( Token_GetToken(ptParseContext, p_tToken) == false )
            goto LABEL_21;
          if ( ScriptControl_GetKeywordId(ptParseContext) != 3 )
            goto LABEL_23;
          if ( Token_GetToken(ptParseContext, &ptParseContext->tToken) == false )
            goto LABEL_21;
        }
        goto LABEL_22;
      }
LABEL_21:
      Script_Error("Unexpected end of file.");
      goto LABEL_22;
    }
LABEL_23:
    if ( ScriptControl_ParseStatementBlock(ptParseContext, (struct ScriptControlBlock_s **)v3 + 8) == false )
      goto LABEL_22;
    return true;
  }
  else
  {
    Script_Error("Unexpected end of file.");
    return true;
  }
}

// source: c/0/scriptcontrol.c:397  [anchor-caller]
enum bool __cdecl ScriptControl_ParseWhileBlock(
        struct ParseContext_s *ptParseContext,
        struct ScriptControlBlock_s **pptScriptControlBlock)
{
  void *v2; // esi

  v2 = Mem_AllocFn(20, 4);
  *(_DWORD *)v2 = 0;
  *((_DWORD *)v2 + 1) = 0;
  *((_DWORD *)v2 + 2) = 0;
  *((_DWORD *)v2 + 3) = 0;
  *((_DWORD *)v2 + 4) = 0;
  *((_DWORD *)v2 + 1) = 0;
  *(_DWORD *)v2 = 0;
  *((_DWORD *)v2 + 2) = 4;
  *pptScriptControlBlock = (struct ScriptControlBlock_s *)v2;
  return Token_GetToken(ptParseContext, &ptParseContext->tToken)
      && *ptParseContext->tToken.zToken == 40
      && Token_GetToken(ptParseContext, &ptParseContext->tToken)
      && Expression_Parse(ptParseContext, (struct QExpression_s **)v2 + 3, 0, 0)
      && Token_GetToken(ptParseContext, &ptParseContext->tToken)
      && ScriptControl_ParseStatementBlock(ptParseContext, (struct ScriptControlBlock_s **)v2 + 4);
}

// source: c/0/scriptcontrol.c:462  [anchor-strings]
enum bool __cdecl ScriptControl_ParseControlBlock(
        struct ParseContext_s *ptParseContext,
        struct ScriptControlBlock_s **pptScriptControlBlock)
{
  enum bool result; // eax

  switch ( ScriptControl_GetKeywordId(ptParseContext) )
  {
    case 1:
      result = ScriptControl_ParseStatementBlock(ptParseContext, pptScriptControlBlock);
      break;
    case 3:
      result = ScriptControl_ParseIfBlock(ptParseContext, pptScriptControlBlock);
      break;
    case 4:
      Script_Error("'else' without matching 'if' in line %d", ptParseContext->ptInputStream->nLine + 1);
      result = false;
      break;
    case 6:
      result = ScriptControl_ParseWhileBlock(ptParseContext, pptScriptControlBlock);
      break;
    default:
      Script_Error("Syntax error in line %d", ptParseContext->ptInputStream->nLine + 1);
      result = false;
      break;
  }
  return result;
}

// source: c/0/scriptcontrol.c:499  [anchor-callee]
void __cdecl ScriptControlBlock_Delete(struct ScriptControlBlock_s *ptScriptControlBlock)
{
  struct ScriptControlBlock_s *ptNext; // eax
  struct ScriptControlBlock_s *i; // esi
  struct ScriptControlBlock_s *v3; // eax
  int v4; // esi
  enum ScriptControlBlockType_e eBlockType; // esi
  _DWORD *v6; // ebx
  int v7; // esi

  if ( ptScriptControlBlock )
  {
    switch ( ptScriptControlBlock->eBlockType )
    {
      case SCRIPTCONTROLBLOCK_TYPE_BLOCK:
        ptNext = ptScriptControlBlock[1].ptNext;
        for ( i = ptNext->ptNext; i; i = i->ptNext )
        {
          v3 = (struct ScriptControlBlock_s *)Node_Remove(ptNext);
          ScriptControlBlock_Delete(v3);
          ptNext = i;
        }
        goto LABEL_7;
      case SCRIPTCONTROLBLOCK_TYPE_IF:
        Expression_Delete((struct QExpression_s *)ptScriptControlBlock[1].ptNext);
        ScriptControlBlock_Delete(ptScriptControlBlock[1].ptPrev);
        eBlockType = ptScriptControlBlock[1].eBlockType;
        v6 = *(_DWORD **)eBlockType;
        if ( *(_DWORD *)eBlockType )
        {
          do
          {
            Expression_Delete(*(struct QExpression_s **)(eBlockType + 12));
            ScriptControlBlock_Delete(*(struct ScriptControlBlock_s **)(eBlockType + 16));
            Node_Remove((_DWORD **)eBlockType);
            v7 = *(_DWORD *)((eBlockType - 4) & 0xFFFFFFFC);
            --Mem_nCurrentAllocations;
            Node_Remove((_DWORD **)v7);
            memset(*(void **)(v7 + 8), 0xCDu, *(_DWORD *)(v7 + 16));
            free((void *)v7);
            eBlockType = (enum ScriptControlBlockType_e)v6;
            v6 = (_DWORD *)*v6;
          }
          while ( v6 );
        }
        if ( ptScriptControlBlock[2].eBlockType )
          ScriptControlBlock_Delete((struct ScriptControlBlock_s *)ptScriptControlBlock[2].eBlockType);
LABEL_7:
        v4 = *(_DWORD *)((unsigned int)&ptScriptControlBlock[-1].eBlockType & 0xFFFFFFFC);
        --Mem_nCurrentAllocations;
        Node_Remove((_DWORD **)v4);
        memset(*(void **)(v4 + 8), 0xCDu, *(_DWORD *)(v4 + 16));
        free((void *)v4);
        return;
      case SCRIPTCONTROLBLOCK_TYPE_WHILE:
      case SCRIPTCONTROLBLOCK_TYPE_DOWHILE:
        Expression_Delete((struct QExpression_s *)ptScriptControlBlock[1].ptNext);
        ScriptControlBlock_Delete(ptScriptControlBlock[1].ptPrev);
        Mem_DeAllocFn(ptScriptControlBlock);
        return;
      case SCRIPTCONTROLBLOCK_TYPE_FOR:
        if ( ptScriptControlBlock[1].ptNext )
          Expression_Delete((struct QExpression_s *)ptScriptControlBlock[1].ptNext);
        if ( ptScriptControlBlock[1].ptPrev )
          Expression_Delete((struct QExpression_s *)ptScriptControlBlock[1].ptPrev);
        ScriptControlBlock_Delete(ptScriptControlBlock[2].ptNext);
        if ( ptScriptControlBlock[1].eBlockType )
          Expression_Delete((struct QExpression_s *)ptScriptControlBlock[1].eBlockType);
        goto LABEL_20;
      case SCRIPTCONTROLBLOCK_TYPE_STATEMENT:
        if ( ptScriptControlBlock[1].ptNext )
        {
          Expression_Delete((struct QExpression_s *)ptScriptControlBlock[1].ptNext);
          Mem_DeAllocFn(ptScriptControlBlock);
        }
        else
        {
LABEL_20:
          Mem_DeAllocFn(ptScriptControlBlock);
        }
        break;
      default:
        LDebug_Error("Unknown block type.");
        abort();
    }
  }
}

// source: c/0/scriptcontrol.c:626  [anchor-refs]
void __cdecl ScriptControlBlock_Execute(struct ScriptControlBlock_s *ptScriptControlBlock)
{
  struct ScriptControlBlock_s *ptPrev; // edi
  unsigned __int32 v2; // eax
  _DWORD *eBlockType; // ebx
  _DWORD *v4; // esi
  struct QExpression_s *v5; // edi
  struct ScriptControlBlock_s *ptNext; // edi
  struct ScriptControlBlock_s *i; // esi
  struct QExpression_s *j; // eax

ScriptControlBlock_Execute:
  ptPrev = ptScriptControlBlock;
  v2 = ptScriptControlBlock->eBlockType - 1;
  while ( 2 )
  {
    switch ( v2 )
    {
      case 0u:
        ptNext = ptPrev[1].ptNext;
        for ( i = ptNext->ptNext; i; i = i->ptNext )
        {
          ScriptControlBlock_Execute(ptNext);
          ptNext = i;
        }
        return;
      case 1u:
        if ( Expression_EvalInt((struct QExpression_s *)ptPrev[1].ptNext) )
        {
          ptPrev = ptPrev[1].ptPrev;
LABEL_9:
          v2 = ptPrev->eBlockType - 1;
          if ( v2 > 6 )
          {
LABEL_10:
            LDebug_Error("Unknown block type.");
            abort();
          }
          continue;
        }
        eBlockType = (_DWORD *)ptPrev[1].eBlockType;
        v4 = (_DWORD *)*eBlockType;
        if ( *eBlockType )
        {
          while ( !Expression_EvalInt((struct QExpression_s *)eBlockType[3]) )
          {
            eBlockType = v4;
            v4 = (_DWORD *)*v4;
            if ( !v4 )
              goto LABEL_8;
          }
          ptScriptControlBlock = (struct ScriptControlBlock_s *)eBlockType[4];
          goto ScriptControlBlock_Execute;
        }
LABEL_8:
        ptPrev = (struct ScriptControlBlock_s *)ptPrev[2].eBlockType;
        if ( ptPrev )
          goto LABEL_9;
        return;
      case 3u:
        while ( Expression_EvalInt((struct QExpression_s *)ptPrev[1].ptNext) )
          ScriptControlBlock_Execute(ptPrev[1].ptPrev);
        return;
      case 4u:
        do
          ScriptControlBlock_Execute(ptPrev[1].ptPrev);
        while ( Expression_EvalInt((struct QExpression_s *)ptPrev[1].ptNext) );
        return;
      case 5u:
        for ( j = (struct QExpression_s *)ptPrev[1].ptNext; ; j = (struct QExpression_s *)ptPrev[1].eBlockType )
        {
          if ( j )
            Expression_EvalInt(j);
          if ( ptPrev[1].ptPrev && !Expression_EvalInt((struct QExpression_s *)ptPrev[1].ptPrev) )
            break;
          ScriptControlBlock_Execute(ptPrev[2].ptNext);
        }
        return;
      case 6u:
        v5 = (struct QExpression_s *)ptPrev[1].ptNext;
        if ( v5 )
          Expression_EvalInt(v5);
        return;
      default:
        goto LABEL_10;
    }
  }
}
