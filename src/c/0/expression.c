/* c/0/expression.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: c/0/expression.c:37  [anchor-hash]
int __cdecl Operator_IsUnary(enum QScriptTokenType_e eOperator)
{
  int result; // eax

  switch ( eOperator )
  {
    case QSCRIPT_TOKEN_PLUS:
    case QSCRIPT_TOKEN_MINUS:
    case QSCRIPT_TOKEN_ANOT:
    case QSCRIPT_TOKEN_NOT:
      result = 1;
      break;
    default:
      result = 0;
      break;
  }
  return result;
}

// source: c/0/expression.c:60  [anchor-hash]
int __cdecl Operator_IsLeftToRightAssociative(enum QScriptTokenType_e eOperator)
{
  int result; // eax

  switch ( eOperator )
  {
    case QSCRIPT_TOKEN_PLUS:
    case QSCRIPT_TOKEN_MINUS:
    case QSCRIPT_TOKEN_ANOT:
    case QSCRIPT_TOKEN_NOT:
    case QSCRIPT_TOKEN_ASSIGN:
    case QSCRIPT_TOKEN_CONDITIONAL:
      result = 0;
      break;
    default:
      result = 1;
      break;
  }
  return result;
}

// source: c/0/expression.c:87  [anchor-strings]
int __cdecl Operator_GetLevel(enum QScriptTokenType_e eOperator)
{
  int result; // eax

  switch ( eOperator )
  {
    case QSCRIPT_TOKEN_ADD:
    case QSCRIPT_TOKEN_SUB:
      result = 4;
      break;
    case QSCRIPT_TOKEN_PLUS:
    case QSCRIPT_TOKEN_MINUS:
    case QSCRIPT_TOKEN_ANOT:
    case QSCRIPT_TOKEN_NOT:
      result = 2;
      break;
    case QSCRIPT_TOKEN_MUL:
    case QSCRIPT_TOKEN_DIV:
      result = 3;
      break;
    case QSCRIPT_TOKEN_AOR:
      result = 10;
      break;
    case QSCRIPT_TOKEN_AXOR:
      result = 9;
      break;
    case QSCRIPT_TOKEN_AAND:
      result = 8;
      break;
    case QSCRIPT_TOKEN_SHL:
    case QSCRIPT_TOKEN_SHR:
      result = 5;
      break;
    case QSCRIPT_TOKEN_EQ:
    case QSCRIPT_TOKEN_NE:
      result = 7;
      break;
    case QSCRIPT_TOKEN_LT:
    case QSCRIPT_TOKEN_GT:
    case QSCRIPT_TOKEN_LE:
    case QSCRIPT_TOKEN_GE:
      result = 6;
      break;
    case QSCRIPT_TOKEN_COMMA:
      result = 15;
      break;
    case QSCRIPT_TOKEN_ASSIGN:
      result = 14;
      break;
    case QSCRIPT_TOKEN_CALL:
      result = 1;
      break;
    case QSCRIPT_TOKEN_OR:
      result = 12;
      break;
    case QSCRIPT_TOKEN_AND:
      result = 11;
      break;
    case QSCRIPT_TOKEN_CONDITIONAL:
      result = 13;
      break;
    default:
      LDebug_Error("Script: Internal Error: Unknown opcode: %02X.", eOperator);
      abort();
  }
  return result;
}

// source: c/0/expression.c:155  [anchor-strings]
struct ArgList_s *__cdecl ParamFunction(
        struct ParseContext_s *ptParseContext,
        struct ScriptSymbol_s *ptScriptSymbol)
{
  struct QExpression_s **v4; // ebx
  int nSize; // eax
  int v6; // ebp
  struct QExpression_s **v7; // edi
  int v8; // esi
  struct ArgList_s *result; // eax
  int i; // esi
  int v11; // esi
  int v12; // edi
  int v13; // eax
  enum QScriptTokenType_e eType; // ecx
  int j; // esi
  struct QExpression_s **v16; // eax
  int v17; // esi
  int v18; // esi
  struct ParseContext_s *ptParseContexta = *(struct ParseContext_s * *)&ptScriptSymbol; // [esp+14h] [ebp+4h] ARGSLOT
  struct QExpression_s **ptParseContextb = *(struct QExpression_s ** *)&ptScriptSymbol; // [esp+14h] [ebp+4h] ARGSLOT
  struct QExpression_s **ptParseContextc = *(struct QExpression_s ** *)&ptScriptSymbol; // [esp+14h] [ebp+4h] ARGSLOT

  v4 = (struct QExpression_s **)Mem_AllocFn(4 * Script_nMaxFunctionArguments, 4);
  if ( !ptScriptSymbol || (nSize = ptScriptSymbol->nSize, nSize == -1) )
  {
    v6 = 0;
    if ( Script_nMaxFunctionArguments > 0 )
    {
      v7 = v4;
      while ( 1 )
      {
        *v7 = nullptr;
        if ( Token_GetToken(ptParseContext, &ptParseContext->tToken) == false )
        {
          Script_Error(
            "Parse error (missing \" ?) in line %d: '%s'",
            ptParseContext->ptInputStream->nLine,
            ptParseContext->ptInputStream->zBuffer);
          for ( i = 0; i < v6; ++i )
            Expression_Delete(v4[i]);
          goto LABEL_11;
        }
        if ( ptParseContext->tToken.eType == QSCRIPT_TOKEN_RPAR )
          break;
        if ( Expression_Parse(ptParseContext, v7, 0, 1) && ptParseContext->tToken.eType != QSCRIPT_TOKEN_COMMA )
        {
          ++v6;
          break;
        }
        ++v6;
        ++v7;
        if ( v6 >= Script_nMaxFunctionArguments )
          goto LABEL_10;
      }
      if ( v6 >= Script_nMaxFunctionArguments )
        goto LABEL_10;
      if ( ptParseContext->tToken.eType == QSCRIPT_TOKEN_RPAR )
      {
        ptParseContexta = (struct ParseContext_s *)Mem_AllocFn(4 * v6 + 4, 4);
        memset(ptParseContexta, 0, 4 * v6 + 4);
        if ( v6 )
          qmemcpy(ptParseContexta, v4, 4 * ((unsigned int)(4 * v6) >> 2));
        if ( v4 )
        {
          v11 = *(_DWORD *)((unsigned int)(v4 - 1) & 0xFFFFFFFC);
          --Mem_nCurrentAllocations;
          Node_Remove((_DWORD **)v11);
          memset(*(void **)(v11 + 8), 0xCDu, *(_DWORD *)(v11 + 16));
          free((void *)v11);
        }
        result = (struct ArgList_s *)Mem_AllocFn(12, 4);
        result->nArguments = v6;
        result->aptExpression = (struct QExpression_s **)ptParseContexta;
        result->isQVM = 0;
        return result;
      }
      goto LABEL_17;
    }
LABEL_10:
    Script_Error(
      "Too many arguments to function in line %d: '%s'",
      ptParseContext->ptInputStream->nLine,
      ptParseContext->ptInputStream->zBuffer);
LABEL_11:
    if ( v4 )
    {
      v8 = *(_DWORD *)((unsigned int)(v4 - 1) & 0xFFFFFFFC);
      --Mem_nCurrentAllocations;
      Node_Remove((_DWORD **)v8);
      memset(*(void **)(v8 + 8), 0xCDu, *(_DWORD *)(v8 + 16));
      free((void *)v8);
    }
    return nullptr;
  }
  v12 = 0;
  if ( nSize > 0 )
  {
    ptParseContextb = v4;
    while ( Token_GetToken(ptParseContext, &ptParseContext->tToken) )
    {
      if ( !Expression_Parse(ptParseContext, ptParseContextb, 0, 1) )
        goto LABEL_39;
      if ( ptParseContext->tToken.eType != QSCRIPT_TOKEN_COMMA && v12 < ptScriptSymbol->nSize - 1 )
      {
        Script_Error(
          "Too few arguments to functions in line %d: '%s'",
          ptParseContext->ptInputStream->nLine,
          ptParseContext->ptInputStream->zBuffer);
        goto LABEL_39;
      }
      ++v12;
      ++ptParseContextb;
      if ( v12 >= ptScriptSymbol->nSize )
        goto LABEL_33;
    }
    Script_Error(
      "Parse error (missing \" ?) in line %d: '%s'",
      ptParseContext->ptInputStream->nLine,
      ptParseContext->ptInputStream->zBuffer);
LABEL_39:
    for ( j = 0; j < v12; ++j )
      Expression_Delete(v4[j]);
    goto LABEL_11;
  }
LABEL_33:
  v13 = ptScriptSymbol->nSize;
  if ( v13 )
  {
    eType = ptParseContext->tToken.eType;
    if ( eType == QSCRIPT_TOKEN_COMMA )
      goto LABEL_10;
    if ( eType != QSCRIPT_TOKEN_RPAR )
    {
LABEL_17:
      Script_Error(
        "Syntax error in line %d: '%s'",
        ptParseContext->ptInputStream->nLine,
        ptParseContext->ptInputStream->zBuffer);
      goto LABEL_11;
    }
    v16 = (struct QExpression_s **)Mem_AllocFn(4 * v13 + 4, 4);
    memset(v16, 0, 4 * ptScriptSymbol->nSize + 4);
    ptParseContextc = v16;
    qmemcpy(v16, v4, 4 * ptScriptSymbol->nSize);
    if ( v4 )
    {
      v17 = *(_DWORD *)((unsigned int)(v4 - 1) & 0xFFFFFFFC);
      --Mem_nCurrentAllocations;
      Node_Remove((_DWORD **)v17);
      memset(*(void **)(v17 + 8), 0xCDu, *(_DWORD *)(v17 + 16));
      free((void *)v17);
    }
    result = (struct ArgList_s *)Mem_AllocFn(12, 4);
    result->aptExpression = ptParseContextc;
    result->isQVM = 0;
    result->nArguments = ptScriptSymbol->nSize;
  }
  else
  {
    if ( Token_GetToken(ptParseContext, &ptParseContext->tToken) == false )
      goto LABEL_11;
    if ( ptParseContext->tToken.eType != QSCRIPT_TOKEN_RPAR )
      goto LABEL_10;
    if ( v4 )
    {
      v18 = *(_DWORD *)((unsigned int)(v4 - 1) & 0xFFFFFFFC);
      --Mem_nCurrentAllocations;
      Node_Remove((_DWORD **)v18);
      memset(*(void **)(v18 + 8), 0xCDu, *(_DWORD *)(v18 + 16));
      free((void *)v18);
    }
    result = (struct ArgList_s *)Mem_AllocFn(12, 4);
    result->aptExpression = nullptr;
    result->isQVM = 0;
    result->nArguments = 0;
  }
  return result;
}

// source: c/0/expression.c:354  [anchor-callee]
void __cdecl Expression_AssignToSymbol(struct QExpression_s *ptExpression, struct ScriptSymbol_s *ptScriptSymbol)
{
  #pragma pack(push, 1)
  union
  {
    struct { size_t v3; };
    struct { char igi2_o1[12]; char zBuf[2052]; };
    char igi2_extent[2064];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  char *v2; // eax

  switch ( ptScriptSymbol->eType )
  {
    case QSCRIPT_SYMBOLTYPE_INT:
      if ( ptScriptSymbol->nSize == 1 )
      {
        *(_BYTE *)ptScriptSymbol->pxUserdata = Expression_EvalInt(ptExpression);
      }
      else if ( ptScriptSymbol->nSize == 2 )
      {
        *(_WORD *)ptScriptSymbol->pxUserdata = Expression_EvalInt(ptExpression);
      }
      else
      {
        *(_DWORD *)ptScriptSymbol->pxUserdata = Expression_EvalInt(ptExpression);
      }
      break;
    case QSCRIPT_SYMBOLTYPE_FLOAT:
      *(double *)ptScriptSymbol->pxUserdata = Expression_EvalFloat(ptExpression);
      break;
    case QSCRIPT_SYMBOLTYPE_STRING:
      igi2_frame.v3 = ptScriptSymbol->nSize - 1;
      v2 = Expression_EvalString(ptExpression, igi2_frame.zBuf, 2048);
      strncpy((char *)ptScriptSymbol->pxUserdata, v2, igi2_frame.v3);
      *((_BYTE *)ptScriptSymbol->pxUserdata + ptScriptSymbol->nSize - 1) = 0;
      break;
  }
}

// source: c/0/expression.c:402  [anchor-strings]
char *__cdecl Expression_EvalString(struct QExpression_s *ptExpression, char *zBuffer, int nSize)
{
  #pragma pack(push, 1)
  union
  {
    struct { _BYTE v18[24]; };
    struct { char igi2_o1[24]; char zBuffera[2048]; };
    char igi2_extent[2072];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  char *result; // eax
  struct ScriptSymbolReference_s *ptScriptSymbolReference; // eax
  int nValue; // eax
  int v6; // eax
  int v7; // eax
  struct QExpression_s *ptLeft; // eax
  char *v9; // eax
  char *v10; // eax
  char *v11; // eax
  struct QExpression_s *v12; // eax
  struct ScriptSymbolReference_s *v13; // eax
  struct QExpression_s *v14; // eax
  struct QExpression_s *v15; // ecx
  int v16; // eax
  struct ScriptSymbol_s *v17; // eax

  if ( ptExpression )
  {
    switch ( ptExpression->tExpressionHeader.eOpType )
    {
      case 0:
        switch ( ptExpression->tExpressionHeader.eType )
        {
          case 1:
          case 3:
            Script_Error("Numeric member in string expression. Line %d.", ptExpression->nLinenumber);
            goto LABEL_40;
          case 2:
            strncpy(zBuffer, ptExpression->uValue.zString, nSize - 1);
            zBuffer[nSize - 1] = 0;
            return zBuffer;
          case 4:
          case 5:
            ptScriptSymbolReference = ptExpression->uValue.tExpressionSymbolContext.ptScriptSymbolReference;
            if ( ptScriptSymbolReference && !ptScriptSymbolReference->ptScriptSymbol )
            {
              Symbol_DeleteReference(ptScriptSymbolReference);
              ptExpression->uValue.nValue = 0;
            }
            if ( !ptExpression->uValue.nValue )
              ptExpression->uValue.nValue = (int)Symbol_NewReference(ptExpression->uValue.tExpressionSymbolContext.zSymbolname);
            nValue = ptExpression->uValue.nValue;
            if ( nValue )
            {
              v6 = *(_DWORD *)(nValue + 8);
              if ( v6 )
              {
                v7 = (*(int (__cdecl **)(_BYTE *, _DWORD, struct ArgList_s *))(v6 + 16))(
                       igi2_frame.v18,
                       *(_DWORD *)(v6 + 24),
                       ptExpression->uValue.tExpressionSymbolContext.ptArgList);
                strncpy(zBuffer, *(char **)(v7 + 16), nSize - 1);
                zBuffer[nSize - 1] = 0;
                return zBuffer;
              }
            }
            ptLeft = ptExpression->ptLeft;
            if ( ptLeft )
              Script_Error(
                "Unknown identifier '%s' in expression, line %d",
                ptLeft->uValue.tExpressionSymbolContext.zSymbolname,
                ptExpression->nLinenumber);
            else
              Script_Error(
                "Unknown identifier '%s' in expression, line %d",
                ptExpression->uValue.tExpressionSymbolContext.zSymbolname,
                ptExpression->nLinenumber);
            break;
          case 6:
            v9 = Expression_EvalString(ptExpression->uValue.ptExpression, igi2_frame.zBuffera, 2048);
            if ( !v9 )
              goto LABEL_41;
            strncpy(zBuffer, v9, nSize - 1);
            zBuffer[nSize - 1] = 0;
            return zBuffer;
          default:
            goto LABEL_20;
        }
        goto LABEL_40;
      case 1:
        v10 = Expression_EvalString(ptExpression->ptLeft, igi2_frame.zBuffera, 2048);
        strncpy(zBuffer, v10, nSize - 1);
        v11 = Expression_EvalString(ptExpression->ptRight, igi2_frame.zBuffera, 2048);
        strncat(zBuffer, v11, nSize - 1);
        zBuffer[nSize - 1] = 0;
        return zBuffer;
      case 0x18:
        Expression_EvalString(ptExpression->ptLeft, zBuffer, nSize);
        return Expression_EvalString(ptExpression->ptRight, zBuffer, nSize);
      case 0x19:
        v12 = ptExpression->ptLeft;
        if ( !v12 )
          goto LABEL_40;
        if ( v12->tExpressionHeader.eType != 4 )
        {
          if ( v12->tExpressionHeader.eType != 5 )
          {
            LDebug_Error("Internal script error. Invalid assignment, line %d", ptExpression->nLinenumber);
            abort();
          }
          v13 = v12->uValue.tExpressionSymbolContext.ptScriptSymbolReference;
          if ( v13 && !v13->ptScriptSymbol )
          {
            Symbol_DeleteReference(v13);
            ptExpression->ptLeft->uValue.nValue = 0;
          }
          v14 = ptExpression->ptLeft;
          if ( !v14->uValue.nValue )
            ptExpression->ptLeft->uValue.nValue = (int)Symbol_NewReference(v14->uValue.tExpressionSymbolContext.zSymbolname);
        }
        v15 = ptExpression->ptLeft;
        v16 = v15->uValue.nValue;
        if ( v16 && (v17 = *(struct ScriptSymbol_s **)(v16 + 8)) != nullptr )
        {
          if ( v17->eClass == QSCRIPT_SYMBOLCLASS_VARIABLE )
          {
            Expression_AssignToSymbol(ptExpression->ptRight, v17);
            return Expression_EvalString(ptExpression->ptRight, zBuffer, nSize);
          }
          if ( v17->eClass == QSCRIPT_SYMBOLCLASS_CONSTANT )
            Script_Error("Expression: Cannot assign to constant, line %d", ptExpression->nLinenumber);
          else
            Script_Error("Syntax error in assignment, line %d", ptExpression->nLinenumber);
        }
        else
        {
          Script_Error(
            "Unknown identifier '%s' in expression, line %d",
            v15->uValue.tExpressionSymbolContext.zSymbolname,
            ptExpression->nLinenumber);
        }
LABEL_40:
        *(_WORD *)zBuffer = 32;
LABEL_41:
        result = nullptr;
        break;
      default:
        Script_Error("Syntax error in string expression, line %d", ptExpression->nLinenumber);
        goto LABEL_40;
    }
  }
  else
  {
LABEL_20:
    *(_WORD *)zBuffer = 32;
    return nullptr;
  }
  return result;
}

// source: c/0/expression.c:551  [anchor-strings]
int __cdecl Expression_EvalInt(struct QExpression_s *ptExpression)
{
  int result; // eax
  struct ScriptSymbolReference_s *ptScriptSymbolReference; // eax
  int nValue; // eax
  int v4; // eax
  struct QExpression_s *ptLeft; // eax
  int v6; // edi
  int v7; // edi
  int v8; // edi
  int v9; // edi
  int v10; // edi
  int v11; // edi
  int v12; // edi
  char v13; // di
  char v14; // di
  int v15; // edi
  int v16; // edi
  int v17; // edi
  int v18; // edi
  int v19; // edi
  int v20; // edi
  struct QExpression_s *v21; // eax
  struct ScriptSymbolReference_s *v22; // eax
  struct QExpression_s *v23; // eax
  struct QExpression_s *v24; // ecx
  int v25; // eax
  struct ScriptSymbol_s *v26; // eax
  _BYTE v27[24]; // [esp+Ch] [ebp-18h] BYREF

  if ( !ptExpression )
    return 0;
  switch ( ptExpression->tExpressionHeader.eOpType )
  {
    case 0:
      switch ( ptExpression->tExpressionHeader.eType )
      {
        case 1:
          return ptExpression->uValue.nValue;
        case 3:
          return (__int64)ptExpression->uValue.vValue;
        case 4:
        case 5:
          ptScriptSymbolReference = ptExpression->uValue.tExpressionSymbolContext.ptScriptSymbolReference;
          if ( ptScriptSymbolReference && !ptScriptSymbolReference->ptScriptSymbol )
          {
            Symbol_DeleteReference(ptScriptSymbolReference);
            ptExpression->uValue.nValue = 0;
          }
          if ( !ptExpression->uValue.nValue )
            ptExpression->uValue.nValue = (int)Symbol_NewReference(ptExpression->uValue.tExpressionSymbolContext.zSymbolname);
          nValue = ptExpression->uValue.nValue;
          if ( nValue )
          {
            v4 = *(_DWORD *)(nValue + 8);
            if ( v4 )
              return *(_DWORD *)(*(int (__cdecl **)(_BYTE *, _DWORD, struct ArgList_s *))(v4 + 16))(
                                  v27,
                                  *(_DWORD *)(v4 + 24),
                                  ptExpression->uValue.tExpressionSymbolContext.ptArgList);
          }
          ptLeft = ptExpression->ptLeft;
          if ( ptLeft )
            Script_Error(
              "Unknown identifier '%s' in expression, line %d",
              ptLeft->uValue.tExpressionSymbolContext.zSymbolname,
              ptExpression->nLinenumber);
          else
            Script_Error(
              "Unknown identifier '%s' in expression, line %d",
              ptExpression->uValue.tExpressionSymbolContext.zSymbolname,
              ptExpression->nLinenumber);
          break;
        case 6:
          return Expression_EvalInt(ptExpression->uValue.ptExpression);
        default:
          goto LABEL_19;
      }
      goto LABEL_19;
    case 1:
      v6 = Expression_EvalInt(ptExpression->ptRight);
      return v6 + Expression_EvalInt(ptExpression->ptLeft);
    case 2:
      v7 = Expression_EvalInt(ptExpression->ptRight);
      return Expression_EvalInt(ptExpression->ptLeft) - v7;
    case 3:
      return Expression_EvalInt(ptExpression->ptRight);
    case 4:
      return -Expression_EvalInt(ptExpression->ptRight);
    case 5:
      v8 = Expression_EvalInt(ptExpression->ptRight);
      return v8 * Expression_EvalInt(ptExpression->ptLeft);
    case 6:
      v9 = Expression_EvalInt(ptExpression->ptRight);
      if ( v9 )
        return Expression_EvalInt(ptExpression->ptLeft) / v9;
      Script_isError = true;
      return 0;
    case 8:
      v10 = Expression_EvalInt(ptExpression->ptRight);
      return v10 | Expression_EvalInt(ptExpression->ptLeft);
    case 9:
      v11 = Expression_EvalInt(ptExpression->ptRight);
      return v11 ^ Expression_EvalInt(ptExpression->ptLeft);
    case 0xA:
      v12 = Expression_EvalInt(ptExpression->ptRight);
      return v12 & Expression_EvalInt(ptExpression->ptLeft);
    case 0xB:
      v13 = Expression_EvalInt(ptExpression->ptRight);
      return Expression_EvalInt(ptExpression->ptLeft) << v13;
    case 0xC:
      v14 = Expression_EvalInt(ptExpression->ptRight);
      return Expression_EvalInt(ptExpression->ptLeft) >> v14;
    case 0xD:
      return ~Expression_EvalInt(ptExpression->ptRight);
    case 0xE:
      v19 = Expression_EvalInt(ptExpression->ptRight);
      return v19 == Expression_EvalInt(ptExpression->ptLeft);
    case 0xF:
      v20 = Expression_EvalInt(ptExpression->ptRight);
      return Expression_EvalInt(ptExpression->ptLeft) != v20;
    case 0x10:
      v15 = Expression_EvalInt(ptExpression->ptRight);
      return Expression_EvalInt(ptExpression->ptLeft) < v15;
    case 0x11:
      v16 = Expression_EvalInt(ptExpression->ptRight);
      return Expression_EvalInt(ptExpression->ptLeft) > v16;
    case 0x12:
      v17 = Expression_EvalInt(ptExpression->ptRight);
      return Expression_EvalInt(ptExpression->ptLeft) <= v17;
    case 0x13:
      v18 = Expression_EvalInt(ptExpression->ptRight);
      return Expression_EvalInt(ptExpression->ptLeft) >= v18;
    case 0x14:
      return Expression_EvalInt(ptExpression->ptRight) == 0;
    case 0x18:
      Expression_EvalInt(ptExpression->ptLeft);
      return Expression_EvalInt(ptExpression->ptRight);
    case 0x19:
      v21 = ptExpression->ptLeft;
      if ( !v21 )
        goto LABEL_67;
      if ( v21->tExpressionHeader.eType != 4 )
      {
        if ( v21->tExpressionHeader.eType != 5 )
        {
LABEL_67:
          LDebug_Error("Internal script error. Invalid assignment, line %d", ptExpression->nLinenumber);
          abort();
        }
        v22 = v21->uValue.tExpressionSymbolContext.ptScriptSymbolReference;
        if ( v22 && !v22->ptScriptSymbol )
        {
          Symbol_DeleteReference(v22);
          ptExpression->ptLeft->uValue.nValue = 0;
        }
        v23 = ptExpression->ptLeft;
        if ( !v23->uValue.nValue )
          ptExpression->ptLeft->uValue.nValue = (int)Symbol_NewReference(v23->uValue.tExpressionSymbolContext.zSymbolname);
      }
      v24 = ptExpression->ptLeft;
      v25 = v24->uValue.nValue;
      if ( v25 && (v26 = *(struct ScriptSymbol_s **)(v25 + 8)) != nullptr )
      {
        if ( v26->eClass )
        {
          if ( v26->eClass == QSCRIPT_SYMBOLCLASS_CONSTANT )
            Script_Error("Expression: Cannot assign to constant, line %d", ptExpression->nLinenumber);
          else
            Script_Error("Syntax error in assignment, line %d", ptExpression->nLinenumber);
          result = 0;
        }
        else
        {
          Expression_AssignToSymbol(ptExpression->ptRight, v26);
          result = Expression_EvalInt(ptExpression->ptRight);
        }
      }
      else
      {
        Script_Error(
          "Unknown identifier '%s' in expression, line %d",
          v24->uValue.tExpressionSymbolContext.zSymbolname,
          ptExpression->nLinenumber);
LABEL_19:
        result = 0;
      }
      break;
    case 0x1B:
      if ( !Expression_EvalInt(ptExpression->ptLeft) )
      {
        result = Expression_EvalInt(ptExpression->ptRight);
        if ( !result )
          return result;
      }
      goto LABEL_49;
    case 0x1C:
      if ( !Expression_EvalInt(ptExpression->ptLeft) || !Expression_EvalInt(ptExpression->ptRight) )
        goto LABEL_19;
LABEL_49:
      result = 1;
      break;
    case 0x1D:
      if ( Expression_EvalInt(ptExpression->uValue.ptExpression) )
        return Expression_EvalInt(ptExpression->ptLeft);
      else
        return Expression_EvalInt(ptExpression->ptRight);
    default:
      goto LABEL_19;
  }
  return result;
}

// source: c/0/expression.c:752  [anchor-strings]
double __cdecl Expression_EvalFloat(struct QExpression_s *ptExpression)
{
  #pragma pack(push, 1)
  union
  {
    struct { double v13; };
    struct { double v14; };
    struct { double v15; };
    struct { double v16; };
    struct { double v17; };
    struct { double v18; };
    struct { double v19; };
    struct { double v20; };
    struct { double v21; };
    struct { double v22; };
    struct { char igi2_o10[8]; _BYTE v23[24]; };
    char igi2_extent[32];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  double result; // st7
  struct ScriptSymbolReference_s *ptScriptSymbolReference; // eax
  int nValue; // eax
  int v5; // eax
  struct QExpression_s *ptLeft; // eax
  struct QExpression_s *v7; // eax
  struct ScriptSymbolReference_s *v8; // eax
  struct QExpression_s *v9; // eax
  struct QExpression_s *v10; // ecx
  int v11; // eax
  struct ScriptSymbol_s *v12; // eax
  int ptExpressiona = *(int *)&ptExpression; // [esp+2Ch] [ebp+4h] ARGSLOT
  int ptExpressionb = *(int *)&ptExpression; // [esp+2Ch] [ebp+4h] ARGSLOT

  if ( !ptExpression )
    return 0.0;
  switch ( ptExpression->tExpressionHeader.eOpType )
  {
    case 0:
      switch ( ptExpression->tExpressionHeader.eType )
      {
        case 1:
          return (double)ptExpression->uValue.nValue;
        case 3:
          return ptExpression->uValue.vValue;
        case 4:
        case 5:
          ptScriptSymbolReference = ptExpression->uValue.tExpressionSymbolContext.ptScriptSymbolReference;
          if ( ptScriptSymbolReference && !ptScriptSymbolReference->ptScriptSymbol )
          {
            Symbol_DeleteReference(ptScriptSymbolReference);
            ptExpression->uValue.nValue = 0;
          }
          if ( !ptExpression->uValue.nValue )
            ptExpression->uValue.nValue = (int)Symbol_NewReference(ptExpression->uValue.tExpressionSymbolContext.zSymbolname);
          nValue = ptExpression->uValue.nValue;
          if ( nValue )
          {
            v5 = *(_DWORD *)(nValue + 8);
            if ( v5 )
              return *(double *)((*(int (__cdecl **)(_BYTE *, _DWORD, struct ArgList_s *))(v5 + 16))(
                                   igi2_frame.v23,
                                   *(_DWORD *)(v5 + 24),
                                   ptExpression->uValue.tExpressionSymbolContext.ptArgList)
                               + 8);
          }
          ptLeft = ptExpression->ptLeft;
          if ( ptLeft )
            Script_Error(
              "Unknown identifier '%s' in expression, line %d",
              ptLeft->uValue.tExpressionSymbolContext.zSymbolname,
              ptExpression->nLinenumber);
          else
            Script_Error(
              "Unknown identifier '%s' in expression, line %d",
              ptExpression->uValue.tExpressionSymbolContext.zSymbolname,
              ptExpression->nLinenumber);
          break;
        case 6:
          return Expression_EvalFloat(ptExpression->uValue.ptExpression);
        default:
          return 0.0;
      }
      return 0.0;
    case 1:
      igi2_frame.v13 = Expression_EvalFloat(ptExpression->ptRight);
      return Expression_EvalFloat(ptExpression->ptLeft) + igi2_frame.v13;
    case 2:
      igi2_frame.v14 = Expression_EvalFloat(ptExpression->ptLeft);
      return igi2_frame.v14 - Expression_EvalFloat(ptExpression->ptRight);
    case 3:
      goto LABEL_56;
    case 4:
      return -Expression_EvalFloat(ptExpression->ptRight);
    case 5:
      igi2_frame.v15 = Expression_EvalFloat(ptExpression->ptRight);
      return Expression_EvalFloat(ptExpression->ptLeft) * igi2_frame.v15;
    case 6:
      igi2_frame.v16 = Expression_EvalFloat(ptExpression->ptRight);
      if ( igi2_frame.v16 != 0.0 )
        return Expression_EvalFloat(ptExpression->ptLeft) / igi2_frame.v16;
      Script_isError = true;
      return 0.0;
    case 0xE:
      igi2_frame.v21 = Expression_EvalFloat(ptExpression->ptLeft);
      return (double)(Expression_EvalFloat(ptExpression->ptRight) == igi2_frame.v21);
    case 0xF:
      igi2_frame.v22 = Expression_EvalFloat(ptExpression->ptLeft);
      return (double)(Expression_EvalFloat(ptExpression->ptRight) != igi2_frame.v22);
    case 0x10:
      igi2_frame.v17 = Expression_EvalFloat(ptExpression->ptLeft);
      return (double)(Expression_EvalFloat(ptExpression->ptRight) > igi2_frame.v17);
    case 0x11:
      igi2_frame.v18 = Expression_EvalFloat(ptExpression->ptLeft);
      return (double)(Expression_EvalFloat(ptExpression->ptRight) < igi2_frame.v18);
    case 0x12:
      igi2_frame.v19 = Expression_EvalFloat(ptExpression->ptLeft);
      return (double)(Expression_EvalFloat(ptExpression->ptRight) >= igi2_frame.v19);
    case 0x13:
      igi2_frame.v20 = Expression_EvalFloat(ptExpression->ptLeft);
      return (double)(Expression_EvalFloat(ptExpression->ptRight) <= igi2_frame.v20);
    case 0x14:
      return (double)(Expression_EvalFloat(ptExpression->ptRight) == 0.0);
    case 0x18:
      Expression_EvalInt(ptExpression->ptLeft);
      return (double)Expression_EvalInt(ptExpression->ptRight);
    case 0x19:
      v7 = ptExpression->ptLeft;
      if ( !v7 )
        return 0.0;
      if ( v7->tExpressionHeader.eType != 4 )
      {
        if ( v7->tExpressionHeader.eType != 5 )
        {
          LDebug_Error("Internal script error. Invalid assignment, line %d", ptExpression->nLinenumber);
          abort();
        }
        v8 = v7->uValue.tExpressionSymbolContext.ptScriptSymbolReference;
        if ( v8 && !v8->ptScriptSymbol )
        {
          Symbol_DeleteReference(v8);
          ptExpression->ptLeft->uValue.nValue = 0;
        }
        v9 = ptExpression->ptLeft;
        if ( !v9->uValue.nValue )
          ptExpression->ptLeft->uValue.nValue = (int)Symbol_NewReference(v9->uValue.tExpressionSymbolContext.zSymbolname);
      }
      v10 = ptExpression->ptLeft;
      v11 = v10->uValue.nValue;
      if ( !v11 || (v12 = *(struct ScriptSymbol_s **)(v11 + 8)) == nullptr )
      {
        Script_Error(
          "Unknown identifier '%s' in expression, line %d",
          v10->uValue.tExpressionSymbolContext.zSymbolname,
          ptExpression->nLinenumber);
        return 0.0;
      }
      if ( v12->eClass )
      {
        if ( v12->eClass == QSCRIPT_SYMBOLCLASS_CONSTANT )
          Script_Error("Expression: Cannot assign to constant, line %d", ptExpression->nLinenumber);
        else
          Script_Error("Syntax error in assignment, line %d", ptExpression->nLinenumber);
        result = 0.0;
      }
      else
      {
        Expression_AssignToSymbol(ptExpression->ptRight, v12);
LABEL_56:
        result = Expression_EvalFloat(ptExpression->ptRight);
      }
      break;
    case 0x1B:
      if ( Expression_EvalFloat(ptExpression->ptLeft) != 0.0 )
        return (double)1;
      ptExpressionb = 0;
      if ( Expression_EvalFloat(ptExpression->ptRight) != 0.0 )
        return (double)1;
      return (double)ptExpressionb;
    case 0x1C:
      if ( Expression_EvalFloat(ptExpression->ptLeft) == 0.0 )
        return (double)0;
      ptExpressiona = 1;
      if ( Expression_EvalFloat(ptExpression->ptRight) == 0.0 )
        return (double)0;
      return (double)ptExpressiona;
    case 0x1D:
      if ( !(unsigned int)(__int64)Expression_EvalFloat(ptExpression->uValue.ptExpression) )
        goto LABEL_56;
      return Expression_EvalFloat(ptExpression->ptLeft);
    default:
      return 0.0;
  }
  return result;
}

// source: c/0/expression.c:938  [anchor-strings]
struct QExpression_s *__cdecl Expression_New(
        enum QExpressionType_e eType,
        void *pxData,
        int nLinenumber,
        struct QExpression_s *ptConcatenate)
{
  unsigned int v6; // eax
  struct QExpression_s *v7; // ebp
  enum QScriptTokenType_e v9; // ecx
  char *p_tExpressionHeader; // edx
  struct QExpression_s *ptParent; // eax
  char *v12; // eax
  int v13; // edx
  char v14; // cl

  v6 = 0;
  if ( ptConcatenate )
  {
    v6 = strlen((char *)pxData) + strlen(ptConcatenate->uValue.zString) + 1;
  }
  else if ( eType == QEXPRESSION_TYPE_STRING )
  {
    v6 = strlen((char *)pxData) + 1;
  }
  v7 = (struct QExpression_s *)Mem_AllocFn(v6 + 40, 4);
  memset(v7, 0, sizeof(struct QExpression_s));
  v7->nLinenumber = nLinenumber + 1;
  v7->tExpressionHeader.eType = eType;
  switch ( eType )
  {
    case QEXPRESSION_TYPE_INT:
      v7->uValue.nValue = *(_DWORD *)pxData;
      return v7;
    case QEXPRESSION_TYPE_STRING:
      p_tExpressionHeader = (char *)&v7[1].tExpressionHeader;
      v7->uValue.nValue = (int)&v7[1];
      if ( ptConcatenate )
      {
        strcpy(p_tExpressionHeader, ptConcatenate->uValue.zString);
        strcat(v7->uValue.zString, (char *)pxData);
        ptParent = ptConcatenate->ptParent;
        if ( ptParent )
        {
          if ( ptParent->ptLeft == ptConcatenate )
          {
            ptParent->ptLeft = v7;
            v7->ptParent = ptConcatenate->ptParent;
            Expression_Delete(ptConcatenate);
            return v7;
          }
          if ( ptParent->ptRight == ptConcatenate )
          {
            ptParent->ptRight = v7;
            v7->ptParent = ptConcatenate->ptParent;
            Expression_Delete(ptConcatenate);
            return v7;
          }
          if ( ptParent->tExpressionHeader.eType != 6 )
          {
            LDebug_Error("Internal error!!!");
LABEL_19:
            abort();
          }
          ptParent->uValue.nValue = (int)v7;
          v7->ptParent = ptConcatenate->ptParent;
        }
        Expression_Delete(ptConcatenate);
        return v7;
      }
      else
      {
        v12 = (char *)pxData;
        v13 = p_tExpressionHeader - (_BYTE *)pxData;
        do
        {
          v14 = *v12;
          v12[v13] = *v12;
          ++v12;
        }
        while ( v14 );
        return v7;
      }
    case QEXPRESSION_TYPE_FLOAT:
      v7->uValue.nValue = *(_DWORD *)pxData;
      v7->uValue.tExpressionSymbolContext.ptArgList = *((struct ArgList_s **)pxData + 1);
      return v7;
    case QEXPRESSION_TYPE_SYMBOL:
    case QEXPRESSION_TYPE_EXPRESSION:
      goto LABEL_7;
    case QEXPRESSION_TYPE_UNDEFINED_SYMBOL:
      v7->uValue.nValue = 0;
      v7->uValue.tExpressionSymbolContext.zSymbolname = (char *)&v7[1].tExpressionHeader;
      v7->uValue.tExpressionSymbolContext.ptArgList = nullptr;
      strcpy((char *)&v7[1].tExpressionHeader, (char *)pxData);
      return v7;
    case QEXPRESSION_TYPE_CONDITIONAL:
      v7->tExpressionHeader.eOpType = 29;
      v7->tExpressionHeader.nLevel = Operator_GetLevel(QSCRIPT_TOKEN_CONDITIONAL);
LABEL_7:
      v7->uValue.nValue = (int)pxData;
      return v7;
    case QEXPRESSION_TYPE_OPERATOR:
      v9 = *(char *)pxData;
      v7->tExpressionHeader.eOpType = *(_BYTE *)pxData;
      v7->tExpressionHeader.nLevel = Operator_GetLevel(v9);
      return v7;
    default:
      LDebug_Error("Script: Internal Error: Illegal expression type.");
      goto LABEL_19;
  }
}

// source: c/0/expression.c:1050  [anchor-callee]
void __cdecl Expression_Delete(struct QExpression_s *ptExpression)
{
  _DWORD **nValue; // eax
  _DWORD *v2; // eax
  struct ArgList_s *ptArgList; // eax
  int v4; // edi
  struct QExpression_s **aptExpression; // eax
  int v7; // ebx
  struct ArgList_s *v8; // eax
  int v9; // ebx
  int v10; // esi

  if ( ptExpression )
  {
    Expression_Delete(ptExpression->ptLeft);
    Expression_Delete(ptExpression->ptRight);
    if ( ptExpression->tExpressionHeader.eType == 6 || ptExpression->tExpressionHeader.eType == 7 )
      Expression_Delete(ptExpression->uValue.ptExpression);
    if ( ptExpression->tExpressionHeader.eType == 4 || ptExpression->tExpressionHeader.eType == 5 )
    {
      nValue = (_DWORD **)ptExpression->uValue.nValue;
      if ( nValue )
      {
        v2 = Node_Remove(nValue);
        List_AddHead(v2, (int)&Symbol_tFreeReferenceList);
        --Symbol_nReferencesUsed;
      }
      ptArgList = ptExpression->uValue.tExpressionSymbolContext.ptArgList;
      if ( ptArgList )
      {
        if ( ptArgList->nArguments && *ptArgList->aptExpression )
        {
          v4 = 0;
          do
            Expression_Delete(ptExpression->uValue.tExpressionSymbolContext.ptArgList->aptExpression[v4]);
          while ( ptExpression->uValue.tExpressionSymbolContext.ptArgList->aptExpression[++v4] );
        }
        aptExpression = ptExpression->uValue.tExpressionSymbolContext.ptArgList->aptExpression;
        if ( aptExpression )
        {
          --Mem_nCurrentAllocations;
          v7 = *(_DWORD *)((unsigned int)(aptExpression - 1) & 0xFFFFFFFC);
          Node_Remove((_DWORD **)v7);
          memset(*(void **)(v7 + 8), 0xCDu, *(_DWORD *)(v7 + 16));
          free((void *)v7);
          ptExpression->uValue.tExpressionSymbolContext.ptArgList->aptExpression = nullptr;
        }
        v8 = ptExpression->uValue.tExpressionSymbolContext.ptArgList;
        if ( v8 )
        {
          --Mem_nCurrentAllocations;
          v9 = *(_DWORD *)((unsigned int)&v8[-1].aptExpression & 0xFFFFFFFC);
          Node_Remove((_DWORD **)v9);
          memset(*(void **)(v9 + 8), 0xCDu, *(_DWORD *)(v9 + 16));
          free((void *)v9);
        }
        ptExpression->uValue.tExpressionSymbolContext.ptArgList = nullptr;
      }
    }
    v10 = *(_DWORD *)((unsigned int)&ptExpression[-1].nLinenumber & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v10);
    memset(*(void **)(v10 + 8), 0xCDu, *(_DWORD *)(v10 + 16));
    free((void *)v10);
  }
}

// source: c/0/expression.c:1100  [anchor-callee]
int __cdecl Expression_Build(
        struct ParseContext_s *ptParseContext,
        struct QExpression_s **pptExpression,
        int nLevel)
{

  if ( Token_GetToken(ptParseContext, &ptParseContext->tToken) )
    return Expression_Parse(ptParseContext, pptExpression, 0, 0);
  else
    return 0;
}

// source: c/0/expression.c:1559  [anchor-strings]
int __cdecl Expression_Parse(
        struct ParseContext_s *ptParseContext,
        struct QExpression_s **pptExpression,
        int nLevel,
        int isFunctionArg)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct QExpression_s *ptExpression; };
    struct { char igi2_o1[4]; struct QExpression_s *v41; };
    struct { char igi2_o2[8]; int v42; };
    struct { char igi2_o3[12]; int v43; };
    struct { char igi2_o4[16]; int Level; };
    struct { char igi2_o5[20]; int v45; };
    char igi2_extent[28];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QExpression_s *v4; // edx
  int v5; // ebx
  enum QScriptTokenType_e eType; // eax
  enum QScriptTokenClass_e eClass; // ecx
  struct QExpression_s *v8; // eax
  int v9; // ebx
  struct QExpression_s *v10; // esi
  char v11; // al
  int v12; // ecx
  struct QExpression_s *v13; // eax
  struct InputStream_s *v14; // eax
  char *zToken; // ebx
  int v16; // esi
  struct QExpression_s *v17; // esi
  int v18; // esi
  int v19; // esi
  char *v20; // ebx
  int v21; // esi
  struct ArgList_s *v22; // eax
  int v23; // esi
  struct QExpression_s *v24; // ebx
  int nLine; // ebx
  struct QExpression_s *v26; // esi
  struct QExpression_s *ptParent; // ecx
  enum QScriptTokenType_e eOpType; // ebx
  BOOL v29; // edi
  int v30; // eax
  struct QExpression_s *v31; // ecx
  struct QExpression_s *v32; // eax
  enum QScriptTokenType_e v33; // ecx
  int v34; // ebx
  struct QExpression_s *v35; // edx
  struct QExpression_s *ptRight; // ecx
  struct InputStream_s *ptInputStream; // eax
  struct QExpression_s *i; // eax

  v4 = nullptr;
  igi2_frame.ptExpression = nullptr;
  igi2_frame.v41 = nullptr;
  igi2_frame.v42 = 0;
  igi2_frame.v43 = 0;
  v5 = 0;
  while ( 2 )
  {
    if ( igi2_frame.v43 )
      goto LABEL_97;
    eType = ptParseContext->tToken.eType;
    eClass = ptParseContext->tToken.eClass;
    igi2_frame.v45 = eType;
    if ( isFunctionArg && eType == QSCRIPT_TOKEN_COMMA )
      eClass = QSCRIPT_TOKENCLASS_EXPTERM;
    switch ( eClass )
    {
      case QSCRIPT_TOKENCLASS_EXPTERM:
        if ( igi2_frame.v41 )
        {
          Script_Error(
            "Syntax error in line %d, '%s'. Syntax error in expression.",
            ptParseContext->ptInputStream->nLine,
            ptParseContext->ptInputStream->zBuffer);
          v4 = igi2_frame.ptExpression;
          v5 = 1;
          igi2_frame.v42 = 1;
        }
        igi2_frame.v43 = 1;
        if ( !v5 )
          continue;
        goto LABEL_97;
      case QSCRIPT_TOKENCLASS_OPR:
      case QSCRIPT_TOKENCLASS_UOPR:
        if ( eType != QSCRIPT_TOKEN_LPAR )
        {
          if ( !v4 || igi2_frame.v41 )
          {
            if ( eType == QSCRIPT_TOKEN_ADD || eType == QSCRIPT_TOKEN_SUB )
            {
              igi2_frame.v45 = (eType != QSCRIPT_TOKEN_ADD) + 3;
            }
            else if ( eClass == QSCRIPT_TOKENCLASS_OPR )
            {
              Script_Error(
                "Syntax error in line %d, '%s'. Binary operator requires lvalue.",
                ptParseContext->ptInputStream->nLine,
                ptParseContext->ptInputStream->zBuffer);
              goto LABEL_95;
            }
          }
          nLine = ptParseContext->ptInputStream->nLine;
          v26 = (struct QExpression_s *)Mem_AllocFn(40, 4);
          memset(v26, 0, sizeof(struct QExpression_s));
          v26->tExpressionHeader.eType = 8;
          v26->nLinenumber = nLine + 1;
          v26->tExpressionHeader.eOpType = igi2_frame.v45;
          v26->tExpressionHeader.nLevel = Operator_GetLevel((enum QScriptTokenType_e)(char)igi2_frame.v45);
          v4 = igi2_frame.ptExpression;
          if ( igi2_frame.ptExpression )
          {
            ptParent = igi2_frame.ptExpression->ptParent;
            igi2_frame.v41 = ptParent;
          }
          else
          {
            ptParent = igi2_frame.v41;
          }
          if ( ptParent )
          {
            eOpType = v26->tExpressionHeader.eOpType;
            v29 = Operator_IsLeftToRightAssociative(eOpType) != 0;
            igi2_frame.Level = Operator_GetLevel((enum QScriptTokenType_e)ptParent->tExpressionHeader.eOpType);
            v30 = Operator_GetLevel(eOpType);
            if ( v29 + v30 > igi2_frame.Level )
            {
              do
              {
                v31 = igi2_frame.v41;
                v32 = igi2_frame.v41->ptParent;
                if ( !v32 )
                {
                  v5 = igi2_frame.v42;
                  v26->ptLeft = igi2_frame.v41;
                  v4 = nullptr;
                  v31->ptParent = v26;
                  igi2_frame.ptExpression = nullptr;
                  igi2_frame.v41 = v26;
                  goto LABEL_37;
                }
                v33 = v32->tExpressionHeader.eOpType;
                igi2_frame.v41 = igi2_frame.v41->ptParent;
                v34 = Operator_GetLevel(v33);
              }
              while ( v29 + Operator_GetLevel((enum QScriptTokenType_e)v26->tExpressionHeader.eOpType) > v34 );
            }
            v35 = igi2_frame.v41;
            ptRight = igi2_frame.v41->ptRight;
            if ( ptRight )
            {
              if ( Operator_IsUnary((enum QScriptTokenType_e)igi2_frame.v41->tExpressionHeader.eOpType) )
              {
                v5 = igi2_frame.v42;
                v26->ptRight = ptRight;
                v35->ptRight->ptParent = v26;
                v35->ptRight = v26;
                v26->ptParent = v35;
                v4 = nullptr;
                igi2_frame.ptExpression = nullptr;
                igi2_frame.v41 = v26;
                goto LABEL_37;
              }
              v26->ptLeft = ptRight;
              v35->ptRight->ptParent = v26;
            }
            v5 = igi2_frame.v42;
            v35->ptRight = v26;
            v26->ptParent = v35;
            v4 = nullptr;
            igi2_frame.ptExpression = nullptr;
            igi2_frame.v41 = v26;
          }
          else
          {
            if ( igi2_frame.ptExpression )
            {
              if ( Operator_IsUnary((enum QScriptTokenType_e)v26->tExpressionHeader.eOpType) )
                v26->ptRight = v4;
              else
                v26->ptLeft = v4;
              igi2_frame.ptExpression->ptParent = v26;
              v4 = nullptr;
              igi2_frame.ptExpression = nullptr;
            }
            v5 = igi2_frame.v42;
            igi2_frame.v41 = v26;
          }
          goto LABEL_37;
        }
        if ( !v4 )
        {
          if ( Token_GetToken(ptParseContext, &ptParseContext->tToken) )
          {
            if ( !Expression_Parse(ptParseContext, &igi2_frame.ptExpression, nLevel + 1, 0) )
              goto LABEL_95;
            if ( ptParseContext->tToken.eType == QSCRIPT_TOKEN_RPAR )
            {
              v23 = ptParseContext->ptInputStream->nLine;
              v24 = igi2_frame.ptExpression;
              v4 = (struct QExpression_s *)Mem_AllocFn(40, 4);
              memset(v4, 0, sizeof(struct QExpression_s));
              v4->tExpressionHeader.eType = 6;
              v4->nLinenumber = v23 + 1;
              v4->uValue.nValue = (int)v24;
              goto LABEL_35;
            }
            Expression_Delete(igi2_frame.ptExpression);
            ptInputStream = ptParseContext->ptInputStream;
            igi2_frame.ptExpression = nullptr;
            Script_Error("Expected ')' in line %d: '%s'", ptInputStream->nLine, ptInputStream->zBuffer);
          }
          else
          {
            Script_Error(
              "Unexpected end of file in line %d: '%s'",
              ptParseContext->ptInputStream->nLine,
              ptParseContext->ptInputStream->zBuffer);
          }
          goto LABEL_95;
        }
        if ( v4->tExpressionHeader.eType != 5 )
          goto LABEL_90;
        v22 = ParamFunction(ptParseContext, nullptr);
        igi2_frame.ptExpression->uValue.tExpressionSymbolContext.ptArgList = v22;
        v4 = igi2_frame.ptExpression;
        if ( v22 )
          goto LABEL_37;
        v5 = 1;
        goto LABEL_97;
      case QSCRIPT_TOKENCLASS_TOPR:
        if ( v4 )
        {
          if ( eType == QSCRIPT_TOKEN_CONDITIONAL )
          {
            v8 = v4->ptParent;
            for ( dword_834DCC8 = 1; v8; v8 = v8->ptParent )
            {
              if ( v8->tExpressionHeader.nLevel > 13 )
                break;
              v4 = v8;
              igi2_frame.ptExpression = v8;
            }
            v9 = ptParseContext->ptInputStream->nLine;
            igi2_frame.v43 = (int)v4;
            v10 = (struct QExpression_s *)Mem_AllocFn(40, 4);
            memset(v10, 0, sizeof(struct QExpression_s));
            v10->tExpressionHeader.eType = 7;
            v10->nLinenumber = v9 + 1;
            v10->tExpressionHeader.eOpType = 29;
            v11 = Operator_GetLevel(QSCRIPT_TOKEN_CONDITIONAL);
            v12 = igi2_frame.v43;
            v10->tExpressionHeader.nLevel = v11;
            v10->uValue.nValue = v12;
            v13 = igi2_frame.ptExpression->ptParent;
            if ( v13 )
            {
              if ( v13->ptLeft == igi2_frame.ptExpression )
              {
                v13->ptLeft = v10;
              }
              else if ( v13->ptRight == igi2_frame.ptExpression )
              {
                v13->ptRight = v10;
              }
              else
              {
                v13->uValue.nValue = (int)v10;
              }
            }
            v10->ptParent = igi2_frame.ptExpression->ptParent;
            if ( Token_GetToken(ptParseContext, &ptParseContext->tToken) )
            {
              if ( Expression_Parse(ptParseContext, &v10->ptLeft, nLevel + 1, 0) )
              {
                if ( ptParseContext->tToken.eType == QSCRIPT_TOKEN_CONDITIONAL2 )
                {
                  if ( Token_GetToken(ptParseContext, &ptParseContext->tToken) )
                  {
                    if ( Expression_Parse(ptParseContext, &v10->ptRight, nLevel + 1, 0) )
                    {
                      v5 = igi2_frame.v42;
                      v4 = v10;
                      igi2_frame.ptExpression = v10;
                      igi2_frame.v43 = 1;
                      dword_834DCC8 = 0;
                      continue;
                    }
                    goto LABEL_87;
                  }
                  goto LABEL_86;
                }
                Script_Error(
                  "Expected ':' in line %d: '%s'",
                  ptParseContext->ptInputStream->nLine,
                  ptParseContext->ptInputStream->zBuffer);
              }
LABEL_87:
              igi2_frame.v42 = 1;
              v5 = 1;
              goto LABEL_96;
            }
LABEL_86:
            Script_Error(
              "Unexpected end of file in line %d: '%s'",
              ptParseContext->ptInputStream->nLine,
              ptParseContext->ptInputStream->zBuffer);
            goto LABEL_87;
          }
          if ( dword_834DCC8 )
          {
            igi2_frame.v43 = 1;
            continue;
          }
          Script_Error(
            "Syntax error in line %d: '%s'",
            ptParseContext->ptInputStream->nLine,
            ptParseContext->ptInputStream->zBuffer);
        }
        else
        {
          Script_Error(
            "Syntax error in line %d: '%s'. Expected operand.",
            ptParseContext->ptInputStream->nLine,
            ptParseContext->ptInputStream->zBuffer);
        }
LABEL_95:
        v5 = 1;
LABEL_96:
        v4 = igi2_frame.ptExpression;
LABEL_97:
        if ( igi2_frame.v41 )
          v4 = igi2_frame.v41;
        if ( !v4 )
          goto LABEL_105;
        for ( i = v4->ptParent; i; i = i->ptParent )
          v4 = i;
        if ( v5 )
        {
          Expression_Delete(v4);
LABEL_105:
          while ( ptParseContext->tToken.eType != QSCRIPT_TOKEN_SEMICOLON
               && Token_GetToken(ptParseContext, &ptParseContext->tToken) )
            ;
          *pptExpression = nullptr;
          dword_834DCC8 = 0;
          return 0;
        }
        else
        {
          *pptExpression = v4;
          return 1;
        }
      case QSCRIPT_TOKENCLASS_QSTRING:
        if ( v4 )
        {
          v14 = ptParseContext->ptInputStream;
          if ( v4->tExpressionHeader.eType != 2 )
            goto LABEL_91;
          v4 = Expression_New(QEXPRESSION_TYPE_STRING, ptParseContext->tToken.zToken, v14->nLine, v4);
        }
        else
        {
          zToken = ptParseContext->tToken.zToken;
          v16 = ptParseContext->ptInputStream->nLine;
          v4 = (struct QExpression_s *)Mem_AllocFn(strlen(zToken) + 41, 4);
          memset(v4, 0, sizeof(struct QExpression_s));
          v4->nLinenumber = v16 + 1;
          v4->tExpressionHeader.eType = 2;
          v4->uValue.nValue = (int)&v4[1];
          strcpy((char *)&v4[1].tExpressionHeader, zToken);
LABEL_35:
          v5 = igi2_frame.v42;
        }
        goto LABEL_36;
      case QSCRIPT_TOKENCLASS_ID:
        if ( v4 )
          goto LABEL_90;
        v20 = ptParseContext->tToken.zToken;
        v21 = ptParseContext->ptInputStream->nLine;
        v4 = (struct QExpression_s *)Mem_AllocFn(strlen(v20) + 41, 4);
        memset(v4, 0, sizeof(struct QExpression_s));
        v4->nLinenumber = v21 + 1;
        v4->uValue.nValue = 0;
        v4->uValue.tExpressionSymbolContext.ptArgList = nullptr;
        v4->tExpressionHeader.eType = 5;
        v4->uValue.tExpressionSymbolContext.zSymbolname = (char *)&v4[1].tExpressionHeader;
        strcpy((char *)&v4[1].tExpressionHeader, v20);
        goto LABEL_35;
      case QSCRIPT_TOKENCLASS_REAL:
        v14 = ptParseContext->ptInputStream;
        if ( v4 )
          goto LABEL_91;
        v18 = v14->nLine;
        v4 = (struct QExpression_s *)Mem_AllocFn(40, 4);
        memset(v4, 0, sizeof(struct QExpression_s));
        v4->tExpressionHeader.eType = 3;
        v4->nLinenumber = v18 + 1;
        v4->uValue.vValue = ptParseContext->tToken.vTokenVal;
        goto LABEL_36;
      case QSCRIPT_TOKENCLASS_INT:
        if ( v4 )
        {
LABEL_90:
          v14 = ptParseContext->ptInputStream;
LABEL_91:
          Script_Error("Syntax error in line %d: '%s'.", v14->nLine, v14->zBuffer);
          goto LABEL_95;
        }
        v19 = ptParseContext->ptInputStream->nLine;
        v4 = (struct QExpression_s *)Mem_AllocFn(40, 4);
        memset(v4, 0, sizeof(struct QExpression_s));
        v4->tExpressionHeader.eType = 1;
        v4->nLinenumber = v19 + 1;
        v4->uValue.nValue = ptParseContext->tToken.nTokenVal;
LABEL_36:
        igi2_frame.ptExpression = v4;
LABEL_37:
        v17 = igi2_frame.v41;
        if ( v4 && igi2_frame.v41 )
        {
          igi2_frame.v41->ptRight = v4;
          igi2_frame.ptExpression->ptParent = v17;
          v17 = nullptr;
          igi2_frame.v41 = nullptr;
        }
        if ( Token_GetToken(ptParseContext, &ptParseContext->tToken) )
        {
          v4 = igi2_frame.ptExpression;
        }
        else
        {
          if ( v17 )
          {
            Script_Error(
              "Syntax error in line %d, '%s'. Syntax error in expression.",
              ptParseContext->ptInputStream->nLine,
              ptParseContext->ptInputStream->zBuffer);
            v5 = 1;
            igi2_frame.v42 = 1;
          }
          v4 = igi2_frame.ptExpression;
          igi2_frame.v43 = 1;
          if ( v5 )
            goto LABEL_97;
        }
        continue;
      default:
        goto LABEL_37;
    }
  }
}
