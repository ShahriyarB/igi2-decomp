/* h/1/level.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: h/1/level.c:275  [anchor-mhash]
enum bool __cdecl Level_IsQTaskIDFree(int nQTaskID)
{
  struct LevelQTaskRange_s *ptHead; // ecx
  struct LevelQTaskRange_s *ptNext; // eax

  ptHead = Level_tQTaskRangeList.ptHead;
  ptNext = Level_tQTaskRangeList.ptHead->ptNext;
  if ( !Level_tQTaskRangeList.ptHead->ptNext )
    return true;
  while ( nQTaskID < ptHead->nMinQTaskID || nQTaskID >= ptHead->nMaxQTaskID )
  {
    ptHead = ptNext;
    ptNext = ptNext->ptNext;
    if ( !ptNext )
      return true;
  }
  return false;
}

// source: h/1/level.c:299  [anchor-mhash]
void __cdecl Level_GetQTaskRangeHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct LevelQTaskRange_s *ptHead; // esi
  struct LevelQTaskRange_s *i; // edx

  *((_DWORD *)pxContext + 16) = 0;
  ptHead = Level_tQTaskRangeList.ptHead;
  for ( i = Level_tQTaskRangeList.ptHead->ptNext; i; i = i->ptNext )
  {
    if ( QTask_IsQTaskTypeDerived(ptQTask->eQTaskType, ptHead->eQTaskType) )
      *((_DWORD *)pxContext + (*((_DWORD *)pxContext + 16))++) = ptHead;
    ptHead = i;
  }
}

// source: h/1/level.c:349  [anchor-mhash]
int __cdecl Level_PrintString(
        char *zBuffer,
        unsigned int nBufferSize,
        char *zString,
        enum bool isTokenizeString,
        unsigned int nMaxTokenSize)
{
  int result; // eax
  char *v6; // esi
  int v7; // ebx
  unsigned int v8; // esi
  char v9; // dl
  int v10; // edx
  unsigned int v11; // [esp+Ch] [ebp-8h]
  unsigned int v12; // [esp+10h] [ebp-4h]

  result = 0;
  v6 = zString;
  if ( isTokenizeString )
  {
    v12 = strlen(zString);
    v11 = 0;
    if ( v12 )
    {
      do
      {
        if ( result >= nBufferSize )
          break;
        *zBuffer++ = 34;
        v7 = 0;
        ++result;
        v8 = 1;
        if ( *zString )
        {
          do
          {
            if ( result >= nBufferSize )
              break;
            ++v11;
            v9 = zString[v7];
            switch ( v9 )
            {
              case 9:
                *zBuffer++ = 92;
                ++v8;
                if ( ++result < nBufferSize )
                {
                  *zBuffer = 116;
                  goto LABEL_21;
                }
                break;
              case 10:
                *zBuffer++ = 92;
                ++v8;
                if ( ++result < nBufferSize )
                {
                  *zBuffer = 110;
                  goto LABEL_21;
                }
                break;
              case 13:
                *zBuffer++ = 92;
                ++v8;
                if ( ++result < nBufferSize )
                {
                  *zBuffer = 114;
                  goto LABEL_21;
                }
                break;
              case 34:
                *zBuffer++ = 92;
                ++v8;
                if ( ++result < nBufferSize )
                {
                  *zBuffer = 34;
                  goto LABEL_21;
                }
                break;
              case 92:
                *zBuffer++ = 92;
                ++v8;
                if ( ++result < nBufferSize )
                {
                  *zBuffer = 92;
                  goto LABEL_21;
                }
                break;
              default:
                *zBuffer = v9;
LABEL_21:
                ++zBuffer;
                ++v8;
                ++result;
                break;
            }
            ++v7;
            if ( v8 >= nMaxTokenSize )
              break;
          }
          while ( zString[v7] );
        }
        zString += v7;
        if ( result < nBufferSize )
        {
          *zBuffer++ = 34;
          ++result;
        }
        if ( v11 >= v12 )
        {
          if ( result < nBufferSize )
            *zBuffer++ = 0;
        }
        else if ( result < nBufferSize )
        {
          *zBuffer++ = 32;
          ++result;
        }
      }
      while ( v11 < v12 );
    }
    else if ( nBufferSize > 2 )
    {
      strcpy(zBuffer, "\"\"");
      return 2;
    }
  }
  else
  {
    v10 = *(unsigned __int8 *)zString;
    if ( *zString )
    {
      while ( result < nBufferSize )
      {
        *zBuffer = v10;
        LOBYTE(v10) = v6[1];
        ++zBuffer;
        ++v6;
        ++result;
        if ( !(_BYTE)v10 )
          goto LABEL_36;
      }
    }
    else
    {
LABEL_36:
      if ( result < nBufferSize )
        *zBuffer = 0;
    }
  }
  return result;
}

// source: h/1/level.c:503  [anchor-mhash]
void __cdecl Level_PrintObjectPosHandler(void *pxData, void *pxContext)
{
  double vZ; // [esp+8h] [ebp-18h]
  double vY; // [esp+10h] [ebp-10h]
  double vX; // [esp+18h] [ebp-8h]

  if ( pxData == (void *)nOrigoAddress )
  {
    vX = *(double *)pxData;
    vY = *((double *)pxData + 1);
    vZ = *((double *)pxData + 2);
  }
  else
  {
    vX = (double)Origo_tDelta.nX + *(double *)pxData;
    vY = (double)Origo_tDelta.nY + *((double *)pxData + 1);
    vZ = (double)Origo_tDelta.nZ + *((double *)pxData + 2);
  }
  sprintf(*((char **)pxContext + 2), "%.20G, %.20G, %.20G", vX, vY, vZ);
}

// source: h/1/level.c:594  [anchor-caller]
void __cdecl Level_CopyQTaskNoteHandler(void *pxData, void *pxContext)
{
  struct QTaskNote_s *QTaskNoteNode; // eax
  char *zString; // ecx

  QTaskNoteNode = Level_GetQTaskNoteNode((struct QTask_s *)pxData);
  zString = QTaskNoteNode->zString;
  if ( !QTaskNoteNode )
    zString = (char *)&g_zInitialValue;
  strcpy(*(char **)pxContext, zString);
}

// source: h/1/level.c:613  [size]
void __cdecl Level_PasteQTaskNoteHandler(void *pxData, void *pxContext)
{
  ;
}

// source: h/1/level.c:632  [size]
void __cdecl Level_GetSizeQTaskNoteHandler(void *pxData, void *pxContext)
{
  *(_DWORD *)pxContext = 65;
}

// source: h/1/level.c:648  [size]
void __cdecl Level_CopyGraphHandler(void *pxData, void *pxContext)
{
  ;
}

// source: h/1/level.c:662  [size]
void __cdecl Level_PasteGraphHandler(void *pxData, void *pxContext)
{
  ;
}

// source: h/1/level.c:676  [size]
void __cdecl Level_GetSizeGraphHandler(void *pxData, void *pxContext)
{
  *(_DWORD *)pxContext = 0;
}

// source: h/1/level.c:692  [anchor-mhash]
void __cdecl Level_ParseGraphEnvelopeHandler(void *pxData, void *pxContext)
{
  void *v2; // edx
  int v3; // ebx
  int i; // eax
  int v5; // esi
  int v6; // ebp
  struct ArgList_s *v7; // edi
  double v8; // st7
  float *pvVal; // [esp+0h] [ebp-4h]

  v2 = pxContext;
  v3 = *(_DWORD *)pxContext;
  pvVal = (float *)pxData;
  for ( i = 0; i < 11; ++i )
  {
    if ( i + v3 >= (int)(**((_DWORD **)pxContext + 1)) )
    {
      LDebug_Error(
        "Too few parameters in line %d of file '%s'",
        *((_DWORD *)pxContext + 3),
        *((char **)pxContext + 2));
      abort();
    }
  }
  v5 = 0;
  v6 = v3;
  while ( 1 )
  {
    v7 = *((struct ArgList_s **)v2 + 1);
    if ( v7->isQVM )
    {
      *(float *)&pxData = 0.0;
      QVM_EvalArg(&pxData, 4, v7, v5 + v3, 2);
      v8 = *(float *)&pxData;
    }
    else
    {
      v8 = Expression_EvalFloat(v7->aptExpression[v6]);
    }
    *pvVal = v8;
    ++v5;
    ++v6;
    ++pvVal;
    if ( v5 >= 11 )
      break;
    v2 = pxContext;
  }
  *(_DWORD *)pxContext += (int)(11);
}

// source: h/1/level.c:724  [size]
void __cdecl Level_GetNumberOfArgumentsGraphEnvelopeHandler(void *pxData, void *pxContext)
{
  *(_DWORD *)pxContext = 11;
}

// source: h/1/level.c:740  [anchor-mhash]
void __cdecl Level_PrintGraphEnvelopeHandler(void *pxData, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { char *zString; };
    struct { char igi2_o1[4]; char zTemp[32]; };
    char igi2_extent[36];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  char *v2; // edi
  int v3; // ebx

  v2 = *((char **)pxContext + 2);
  igi2_frame.zString = v2;
  *v2 = 0;
  v3 = 0;
  while ( 1 )
  {
    sprintf(igi2_frame.zTemp, "%.20G", *((float *)pxData + v3));
    strcat(v2, igi2_frame.zTemp);
    if ( v3 != 10 )
      strcat(igi2_frame.zString, ", ");
    if ( ++v3 >= 11 )
      break;
    v2 = igi2_frame.zString;
  }
}

// source: h/1/level.c:782  [size]
void __cdecl Level_CopyGraphEnvelopeHandler(void *pxData, void *pxContext)
{
  qmemcpy(*(void **)pxContext, pxData, 0x2Cu);
}

// source: h/1/level.c:798  [size]
void __cdecl Level_PasteGraphEnvelopeHandler(void *pxData, void *pxContext)
{
  qmemcpy(pxData, *(void **)pxContext, 0x2Cu);
}

// source: h/1/level.c:814  [size]
void __cdecl Level_GetSizeGraphEnvelopeHandler(void *pxData, void *pxContext)
{
  *(_DWORD *)pxContext = 44;
}

// source: h/1/level.c:832  [size]
void __cdecl Level_ParseReal32Handler(void *pxData, void *pxContext)
{
  _DWORD *v2; // esi
  int v3; // eax
  struct ArgList_s *v4; // edi
  int i; // ecx

  v2 = pxContext;
  v3 = *(_DWORD *)pxContext;
  v4 = *((struct ArgList_s **)pxContext + 1);
  for ( i = 0; i < 1; ++i )
  {
    if ( i + v3 >= v4->nArguments )
    {
      LDebug_Error(
        "Too few parameters in line %d of file '%s'",
        *((_DWORD *)pxContext + 3),
        *((char **)pxContext + 2));
      abort();
    }
  }
  if ( v4->isQVM )
  {
    *(float *)&pxContext = 0.0;
    QVM_EvalArg(&pxContext, 4, v4, v3, 2);
    *(float *)pxData = *(float *)&pxContext;
  }
  else
  {
    *(float *)pxData = Expression_EvalFloat(v4->aptExpression[v3]);
  }
  ++*v2;
}

// source: h/1/level.c:861  [size]
void __cdecl Level_GetNumberOfArgumentsReal32Handler(void *pxData, void *pxContext)
{
  *(_DWORD *)pxContext = 1;
}

// source: h/1/level.c:877  [anchor-mhash]
void __cdecl Level_PrintReal32Handler(void *pxData, void *pxContext)
{
  sprintf(*((char **)pxContext + 2), "%.20G", *(float *)pxData);
}

// source: h/1/level.c:903  [size]
void __cdecl Level_CopyReal32Handler(void *pxData, void *pxContext)
{
  **(_DWORD **)pxContext = *(_DWORD *)pxData;
}

// source: h/1/level.c:921  [size]
void __cdecl Level_PasteReal32Handler(void *pxData, void *pxContext)
{
  *(_DWORD *)pxData = **(_DWORD **)pxContext;
}

// source: h/1/level.c:939  [size]
void __cdecl Level_GetSizeReal32Handler(void *pxData, void *pxContext)
{
  *(_DWORD *)pxContext = 4;
}

// source: h/1/level.c:957  [size]
void __cdecl Level_ParseReal32x3Handler(void *pxData, void *pxContext)
{
  _DWORD *v2; // ebx
  int v3; // esi
  struct ArgList_s *v4; // edi
  int i; // eax
  double v6; // st7
  struct ArgList_s *v7; // edi
  int v8; // eax
  double v9; // st7
  struct ArgList_s *v10; // edi
  int v11; // eax

  v2 = pxContext;
  v3 = *(_DWORD *)pxContext;
  v4 = *((struct ArgList_s **)pxContext + 1);
  for ( i = 0; i < 3; ++i )
  {
    if ( i + v3 >= v4->nArguments )
    {
      LDebug_Error(
        "Too few parameters in line %d of file '%s'",
        *((_DWORD *)pxContext + 3),
        *((char **)pxContext + 2));
      abort();
    }
  }
  if ( v4->isQVM )
  {
    *(float *)&pxContext = 0.0;
    QVM_EvalArg(&pxContext, 4, v4, v3, 2);
    v6 = *(float *)&pxContext;
  }
  else
  {
    v6 = Expression_EvalFloat(v4->aptExpression[v3]);
  }
  *(float *)pxData = v6;
  v7 = (struct ArgList_s *)v2[1];
  v8 = v3 + 1;
  if ( v7->isQVM )
  {
    *(float *)&pxContext = 0.0;
    QVM_EvalArg(&pxContext, 4, v7, v8, 2);
    v9 = *(float *)&pxContext;
  }
  else
  {
    v9 = Expression_EvalFloat(v7->aptExpression[v8]);
  }
  *((float *)pxData + 1) = v9;
  v10 = (struct ArgList_s *)v2[1];
  v11 = v3 + 2;
  if ( v10->isQVM )
  {
    *(float *)&pxContext = 0.0;
    QVM_EvalArg(&pxContext, 4, v10, v11, 2);
    *((float *)pxData + 2) = *(float *)&pxContext;
  }
  else
  {
    *((float *)pxData + 2) = Expression_EvalFloat(v10->aptExpression[v11]);
  }
  *v2 += 3;
}

// source: h/1/level.c:988  [size]
void __cdecl Level_GetNumberOfArgumentsReal32x3Handler(void *pxData, void *pxContext)
{
  *(_DWORD *)pxContext = 3;
}

// source: h/1/level.c:1004  [anchor-mhash]
void __cdecl Level_PrintReal32x3Handler(void *pxData, void *pxContext)
{
  sprintf(
    *((char **)pxContext + 2),
    "%.20G, %.20G, %.20G",
    *(float *)pxData,
    *((float *)pxData + 1),
    *((float *)pxData + 2));
}

// source: h/1/level.c:1030  [size]
void __cdecl Level_CopyReal32x3Handler(void *pxData, void *pxContext)
{
  _DWORD *v2; // edx

  v2 = *(_DWORD **)pxContext;
  *v2 = *(_DWORD *)pxData;
  v2[1] = *((_DWORD *)pxData + 1);
  v2[2] = *((_DWORD *)pxData + 2);
}

// source: h/1/level.c:1048  [size]
void __cdecl Level_PasteReal32x3Handler(void *pxData, void *pxContext)
{
  _DWORD *v2; // ecx

  v2 = *(_DWORD **)pxContext;
  *(_DWORD *)pxData = **(_DWORD **)pxContext;
  *((_DWORD *)pxData + 1) = v2[1];
  *((_DWORD *)pxData + 2) = v2[2];
}

// source: h/1/level.c:1066  [size]
void __cdecl Level_GetSizeReal32x3Handler(void *pxData, void *pxContext)
{
  *(_DWORD *)pxContext = 12;
}

// source: h/1/level.c:1084  [anchor-mhash]
void __cdecl Level_ParseReal32x9Handler(void *pxData, void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { float vBeta; };
    struct { char igi2_o1[16]; float v13; };
    struct { char igi2_o2[20]; float v14; };
    struct { char igi2_o3[24]; float vAlpha; };
    char igi2_extent[28];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v2; // esi
  struct ArgList_s *v3; // edi
  int i; // eax
  double v5; // st7
  struct ArgList_s *v6; // edi
  int v7; // eax
  double v8; // st7
  struct ArgList_s *v9; // edi
  int v10; // eax
  double v11; // st7

  v2 = *(_DWORD *)pxContext;
  v3 = *((struct ArgList_s **)pxContext + 1);
  for ( i = 0; i < 3; ++i )
  {
    if ( i + v2 >= v3->nArguments )
    {
      LDebug_Error(
        "Too few parameters in line %d of file '%s'",
        *((_DWORD *)pxContext + 3),
        *((char **)pxContext + 2));
      abort();
    }
  }
  if ( v3->isQVM )
  {
    igi2_frame.v13 = 0.0;
    QVM_EvalArg(&igi2_frame.v13, 4, v3, v2, 2);
    v5 = igi2_frame.v13;
  }
  else
  {
    v5 = Expression_EvalFloat(v3->aptExpression[v2]);
  }
  v6 = *((struct ArgList_s **)pxContext + 1);
  igi2_frame.vAlpha = v5;
  v7 = v2 + 1;
  if ( v6->isQVM )
  {
    igi2_frame.v13 = 0.0;
    QVM_EvalArg(&igi2_frame.v13, 4, v6, v7, 2);
    v8 = igi2_frame.v13;
  }
  else
  {
    v8 = Expression_EvalFloat(v6->aptExpression[v7]);
  }
  v9 = *((struct ArgList_s **)pxContext + 1);
  igi2_frame.v14 = v8;
  v10 = v2 + 2;
  if ( v9->isQVM )
  {
    igi2_frame.v13 = 0.0;
    QVM_EvalArg(&igi2_frame.v13, 4, v9, v10, 2);
    v11 = igi2_frame.v13;
  }
  else
  {
    v11 = Expression_EvalFloat(v9->aptExpression[v10]);
  }
  igi2_frame.vBeta = v11;
  Real32x9_Create((struct real32x9_t *)pxData, igi2_frame.vAlpha, igi2_frame.v14, igi2_frame.vBeta);
  *(_DWORD *)pxContext += (int)(3);
}

// source: h/1/level.c:1122  [size]
void __cdecl Level_GetNumberOfArgumentsReal32x9Handler(void *pxData, void *pxContext)
{
  *(_DWORD *)pxContext = 3;
}

// source: h/1/level.c:1138  [anchor-mhash]
void __cdecl Level_PrintReal32x9Handler(void *pxData, void *pxContext)
{
  char *v2; // esi
  float vA; // [esp+1Ch] [ebp-4h] BYREF

  v2 = *((char **)pxContext + 2);
  Real32x9_GetAngles((struct real32x9_t *)pxData, &vA, (float *)&pxData, (float *)&pxContext);
  sprintf(v2, "%.20G, %.20G, %.20G", vA, *(float *)&pxData, *(float *)&pxContext);
}

// source: h/1/level.c:1170  [size]
void __cdecl Level_CopyReal32x9Handler(void *pxData, void *pxContext)
{
  qmemcpy(*(void **)pxContext, pxData, 0x28u);
}

// source: h/1/level.c:1188  [size]
void __cdecl Level_PasteReal32x9Handler(void *pxData, void *pxContext)
{
  qmemcpy(pxData, *(void **)pxContext, 0x28u);
}

// source: h/1/level.c:1206  [size]
void __cdecl Level_GetSizeReal32x9Handler(void *pxData, void *pxContext)
{
  *(_DWORD *)pxContext = 40;
}

// source: h/1/level.c:1224  [anchor-mhash]
void __cdecl Level_ParseReal32x9ExactHandler(void *pxData, void *pxContext)
{
  int v2; // esi
  struct ArgList_s *v3; // edi
  int i; // eax
  double v5; // st7
  struct ArgList_s *v6; // edi
  int v7; // eax
  double v8; // st7
  struct ArgList_s *v9; // edi
  int v10; // eax
  double v11; // st7
  struct ArgList_s *v12; // edi
  int v13; // eax
  double v14; // st7
  struct ArgList_s *v15; // edi
  int v16; // eax
  double v17; // st7
  struct ArgList_s *v18; // edi
  int v19; // eax
  double v20; // st7
  struct ArgList_s *v21; // edi
  int v22; // eax
  double v23; // st7
  struct ArgList_s *v24; // edi
  int v25; // eax
  double v26; // st7
  struct ArgList_s *v27; // edi
  int v28; // eax
  double v29; // st7
  struct ArgList_s *v30; // edi
  int v31; // esi
  float v32; // [esp+Ch] [ebp-4h] BYREF

  v2 = *(_DWORD *)pxContext;
  v3 = *((struct ArgList_s **)pxContext + 1);
  for ( i = 0; i < 10; ++i )
  {
    if ( i + v2 >= v3->nArguments )
    {
      LDebug_Error(
        "Too few parameters in line %d of file '%s'",
        *((_DWORD *)pxContext + 3),
        *((char **)pxContext + 2));
      abort();
    }
  }
  if ( v3->isQVM )
  {
    v32 = 0.0;
    QVM_EvalArg(&v32, 4, v3, v2, 2);
    v5 = v32;
  }
  else
  {
    v5 = Expression_EvalFloat(v3->aptExpression[v2]);
  }
  *(float *)pxData = v5;
  v6 = *((struct ArgList_s **)pxContext + 1);
  v7 = v2 + 1;
  if ( v6->isQVM )
  {
    v32 = 0.0;
    QVM_EvalArg(&v32, 4, v6, v7, 2);
    v8 = v32;
  }
  else
  {
    v8 = Expression_EvalFloat(v6->aptExpression[v7]);
  }
  *((float *)pxData + 1) = v8;
  v9 = *((struct ArgList_s **)pxContext + 1);
  v10 = v2 + 2;
  if ( v9->isQVM )
  {
    v32 = 0.0;
    QVM_EvalArg(&v32, 4, v9, v10, 2);
    v11 = v32;
  }
  else
  {
    v11 = Expression_EvalFloat(v9->aptExpression[v10]);
  }
  *((float *)pxData + 2) = v11;
  v12 = *((struct ArgList_s **)pxContext + 1);
  v13 = v2 + 3;
  if ( v12->isQVM )
  {
    v32 = 0.0;
    QVM_EvalArg(&v32, 4, v12, v13, 2);
    v14 = v32;
  }
  else
  {
    v14 = Expression_EvalFloat(v12->aptExpression[v13]);
  }
  *((float *)pxData + 3) = v14;
  v15 = *((struct ArgList_s **)pxContext + 1);
  v16 = v2 + 4;
  if ( v15->isQVM )
  {
    v32 = 0.0;
    QVM_EvalArg(&v32, 4, v15, v16, 2);
    v17 = v32;
  }
  else
  {
    v17 = Expression_EvalFloat(v15->aptExpression[v16]);
  }
  *((float *)pxData + 4) = v17;
  v18 = *((struct ArgList_s **)pxContext + 1);
  v19 = v2 + 5;
  if ( v18->isQVM )
  {
    v32 = 0.0;
    QVM_EvalArg(&v32, 4, v18, v19, 2);
    v20 = v32;
  }
  else
  {
    v20 = Expression_EvalFloat(v18->aptExpression[v19]);
  }
  *((float *)pxData + 5) = v20;
  v21 = *((struct ArgList_s **)pxContext + 1);
  v22 = v2 + 6;
  if ( v21->isQVM )
  {
    v32 = 0.0;
    QVM_EvalArg(&v32, 4, v21, v22, 2);
    v23 = v32;
  }
  else
  {
    v23 = Expression_EvalFloat(v21->aptExpression[v22]);
  }
  *((float *)pxData + 6) = v23;
  v24 = *((struct ArgList_s **)pxContext + 1);
  v25 = v2 + 7;
  if ( v24->isQVM )
  {
    v32 = 0.0;
    QVM_EvalArg(&v32, 4, v24, v25, 2);
    v26 = v32;
  }
  else
  {
    v26 = Expression_EvalFloat(v24->aptExpression[v25]);
  }
  *((float *)pxData + 7) = v26;
  v27 = *((struct ArgList_s **)pxContext + 1);
  v28 = v2 + 8;
  if ( v27->isQVM )
  {
    v32 = 0.0;
    QVM_EvalArg(&v32, 4, v27, v28, 2);
    v29 = v32;
  }
  else
  {
    v29 = Expression_EvalFloat(v27->aptExpression[v28]);
  }
  *((float *)pxData + 8) = v29;
  v30 = *((struct ArgList_s **)pxContext + 1);
  v31 = v2 + 9;
  if ( v30->isQVM )
  {
    v32 = 0.0;
    QVM_EvalArg(&v32, 4, v30, v31, 1);
    *((float *)pxData + 9) = v32;
  }
  else
  {
    *((_DWORD *)pxData + 9) = Expression_EvalInt(v30->aptExpression[v31]);
  }
  *(_DWORD *)pxContext += (int)(10);
}

// source: h/1/level.c:1262  [size]
void __cdecl Level_GetNumberOfArgumentsReal32x9ExactHandler(void *pxData, void *pxContext)
{
  *(_DWORD *)pxContext = 10;
}

// source: h/1/level.c:1278  [anchor-strings]
void __cdecl Level_PrintReal32x9ExactHandler(void *pxData, void *pxContext)
{
  sprintf(
    *((char **)pxContext + 2),
    "%.20G, %.20G, %.20G, %.20G, %.20G, %.20G, %.20G, %.20G, %.20G, %d",
    *(float *)pxData,
    *((float *)pxData + 1),
    *((float *)pxData + 2),
    *((float *)pxData + 3),
    *((float *)pxData + 4),
    *((float *)pxData + 5),
    *((float *)pxData + 6),
    *((float *)pxData + 7),
    *((float *)pxData + 8),
    *((_DWORD *)pxData + 9));
}

// source: h/1/level.c:1308  [anchor-mhash]
void __cdecl Level_ParseQuat32Handler(void *pxData, void *pxContext)
{
  int v2; // esi
  struct ArgList_s *v3; // edi
  int i; // eax
  double v5; // st7
  struct ArgList_s *v6; // edi
  int v7; // eax
  double v8; // st7
  struct ArgList_s *v9; // edi
  int v10; // eax
  double v11; // st7
  struct ArgList_s *v12; // edi
  int v13; // eax
  double v14; // st7
  struct ArgList_s *v15; // edi
  int v16; // esi
  float v17; // [esp+Ch] [ebp-4h] BYREF

  v2 = *(_DWORD *)pxContext;
  v3 = *((struct ArgList_s **)pxContext + 1);
  for ( i = 0; i < 5; ++i )
  {
    if ( i + v2 >= v3->nArguments )
    {
      LDebug_Error(
        "Too few parameters in line %d of file '%s'",
        *((_DWORD *)pxContext + 3),
        *((char **)pxContext + 2));
      abort();
    }
  }
  if ( v3->isQVM )
  {
    v17 = 0.0;
    QVM_EvalArg(&v17, 4, v3, v2, 2);
    v5 = v17;
  }
  else
  {
    v5 = Expression_EvalFloat(v3->aptExpression[v2]);
  }
  *(float *)pxData = v5;
  v6 = *((struct ArgList_s **)pxContext + 1);
  v7 = v2 + 1;
  if ( v6->isQVM )
  {
    v17 = 0.0;
    QVM_EvalArg(&v17, 4, v6, v7, 2);
    v8 = v17;
  }
  else
  {
    v8 = Expression_EvalFloat(v6->aptExpression[v7]);
  }
  *((float *)pxData + 1) = v8;
  v9 = *((struct ArgList_s **)pxContext + 1);
  v10 = v2 + 2;
  if ( v9->isQVM )
  {
    v17 = 0.0;
    QVM_EvalArg(&v17, 4, v9, v10, 2);
    v11 = v17;
  }
  else
  {
    v11 = Expression_EvalFloat(v9->aptExpression[v10]);
  }
  *((float *)pxData + 2) = v11;
  v12 = *((struct ArgList_s **)pxContext + 1);
  v13 = v2 + 3;
  if ( v12->isQVM )
  {
    v17 = 0.0;
    QVM_EvalArg(&v17, 4, v12, v13, 2);
    v14 = v17;
  }
  else
  {
    v14 = Expression_EvalFloat(v12->aptExpression[v13]);
  }
  *((float *)pxData + 3) = v14;
  v15 = *((struct ArgList_s **)pxContext + 1);
  v16 = v2 + 4;
  if ( v15->isQVM )
  {
    v17 = 0.0;
    QVM_EvalArg(&v17, 4, v15, v16, 1);
    *((float *)pxData + 4) = v17;
  }
  else
  {
    *((_DWORD *)pxData + 4) = Expression_EvalInt(v15->aptExpression[v16]);
  }
  *(_DWORD *)pxContext += (int)(5);
}

// source: h/1/level.c:1339  [size]
void __cdecl Level_GetNumberOfArgumentsQuat32Handler(void *pxData, void *pxContext)
{
  *(_DWORD *)pxContext = 5;
}

// source: h/1/level.c:1355  [anchor-strings]
void __cdecl Level_PrintQuat32Handler(void *pxData, void *pxContext)
{
  sprintf(
    *((char **)pxContext + 2),
    "%.20G, %.20G, %.20G, %.20G, %d",
    *(float *)pxData,
    *((float *)pxData + 1),
    *((float *)pxData + 2),
    *((float *)pxData + 3),
    *((_DWORD *)pxData + 4));
}

// source: h/1/level.c:1381  [size]
void __cdecl Level_CopyQuat32Handler(void *pxData, void *pxContext)
{
  qmemcpy(*(void **)pxContext, pxData, 0x14u);
}

// source: h/1/level.c:1399  [size]
void __cdecl Level_PasteQuat32Handler(void *pxData, void *pxContext)
{
  qmemcpy(pxData, *(void **)pxContext, 0x14u);
}

// source: h/1/level.c:1417  [size]
void __cdecl Level_GetSizeQuat32Handler(void *pxData, void *pxContext)
{
  *(_DWORD *)pxContext = 20;
}

// source: h/1/level.c:1435  [size]
void __cdecl Level_ParseReal64Handler(void *pxData, void *pxContext)
{
  _DWORD *v2; // esi
  int v3; // eax
  struct ArgList_s *v4; // edi
  int i; // ecx

  v2 = pxContext;
  v3 = *(_DWORD *)pxContext;
  v4 = *((struct ArgList_s **)pxContext + 1);
  for ( i = 0; i < 1; ++i )
  {
    if ( i + v3 >= v4->nArguments )
    {
      LDebug_Error(
        "Too few parameters in line %d of file '%s'",
        *((_DWORD *)pxContext + 3),
        *((char **)pxContext + 2));
      abort();
    }
  }
  if ( v4->isQVM )
  {
    *(float *)&pxContext = 0.0;
    QVM_EvalArg(&pxContext, 4, v4, v3, 2);
    *(double *)pxData = *(float *)&pxContext;
  }
  else
  {
    *(double *)pxData = Expression_EvalFloat(v4->aptExpression[v3]);
  }
  ++*v2;
}

// source: h/1/level.c:1463  [size]
void __cdecl Level_GetNumberOfArgumentsReal64Handler(void *pxData, void *pxContext)
{
  *(_DWORD *)pxContext = 1;
}

// source: h/1/level.c:1479  [anchor-mhash]
void __cdecl Level_PrintReal64Handler(void *pxData, void *pxContext)
{
  sprintf(*((char **)pxContext + 2), "%.20G", *(double *)pxData);
}

// source: h/1/level.c:1505  [size]
void __cdecl Level_CopyReal64Handler(void *pxData, void *pxContext)
{
  _DWORD *v2; // ecx

  v2 = *(_DWORD **)pxContext;
  *v2 = *(_DWORD *)pxData;
  v2[1] = *((_DWORD *)pxData + 1);
}

// source: h/1/level.c:1523  [size]
void __cdecl Level_PasteReal64Handler(void *pxData, void *pxContext)
{
  _DWORD *v2; // ecx

  v2 = *(_DWORD **)pxContext;
  *(_DWORD *)pxData = **(_DWORD **)pxContext;
  *((_DWORD *)pxData + 1) = v2[1];
}

// source: h/1/level.c:1541  [size]
void __cdecl Level_GetSizeReal64Handler(void *pxData, void *pxContext)
{
  *(_DWORD *)pxContext = 8;
}

// source: h/1/level.c:1559  [size]
void __cdecl Level_ParseReal64x3Handler(void *pxData, void *pxContext)
{
  _DWORD *v2; // ebx
  int v3; // esi
  struct ArgList_s *v4; // edi
  int i; // eax
  double v6; // st7
  struct ArgList_s *v7; // edi
  int v8; // eax
  double v9; // st7
  struct ArgList_s *v10; // edi
  int v11; // eax

  v2 = pxContext;
  v3 = *(_DWORD *)pxContext;
  v4 = *((struct ArgList_s **)pxContext + 1);
  for ( i = 0; i < 3; ++i )
  {
    if ( i + v3 >= v4->nArguments )
    {
      LDebug_Error(
        "Too few parameters in line %d of file '%s'",
        *((_DWORD *)pxContext + 3),
        *((char **)pxContext + 2));
      abort();
    }
  }
  if ( v4->isQVM )
  {
    *(float *)&pxContext = 0.0;
    QVM_EvalArg(&pxContext, 4, v4, v3, 2);
    v6 = *(float *)&pxContext;
  }
  else
  {
    v6 = Expression_EvalFloat(v4->aptExpression[v3]);
  }
  *(double *)pxData = v6;
  v7 = (struct ArgList_s *)v2[1];
  v8 = v3 + 1;
  if ( v7->isQVM )
  {
    *(float *)&pxContext = 0.0;
    QVM_EvalArg(&pxContext, 4, v7, v8, 2);
    v9 = *(float *)&pxContext;
  }
  else
  {
    v9 = Expression_EvalFloat(v7->aptExpression[v8]);
  }
  *((double *)pxData + 1) = v9;
  v10 = (struct ArgList_s *)v2[1];
  v11 = v3 + 2;
  if ( v10->isQVM )
  {
    *(float *)&pxContext = 0.0;
    QVM_EvalArg(&pxContext, 4, v10, v11, 2);
    *((double *)pxData + 2) = *(float *)&pxContext;
  }
  else
  {
    *((double *)pxData + 2) = Expression_EvalFloat(v10->aptExpression[v11]);
  }
  *v2 += 3;
}

// source: h/1/level.c:1589  [size]
void __cdecl Level_GetNumberOfArgumentsReal64x3Handler(void *pxData, void *pxContext)
{
  *(_DWORD *)pxContext = 3;
}

// source: h/1/level.c:1605  [anchor-mhash]
void __cdecl Level_PrintReal64x3Handler(void *pxData, void *pxContext)
{
  sprintf(
    *((char **)pxContext + 2),
    "%.20G, %.20G, %.20G",
    *(double *)pxData,
    *((double *)pxData + 1),
    *((double *)pxData + 2));
}

// source: h/1/level.c:1631  [size]
void __cdecl Level_CopyReal64x3Handler(void *pxData, void *pxContext)
{
  qmemcpy(*(void **)pxContext, pxData, 0x18u);
}

// source: h/1/level.c:1649  [size]
void __cdecl Level_PasteReal64x3Handler(void *pxData, void *pxContext)
{
  qmemcpy(pxData, *(void **)pxContext, 0x18u);
}

// source: h/1/level.c:1667  [size]
void __cdecl Level_GetSizeReal64x3Handler(void *pxData, void *pxContext)
{
  *(_DWORD *)pxContext = 24;
}

// source: h/1/level.c:1685  [size]
void __cdecl Level_ParseInt32Handler(void *pxData, void *pxContext)
{
  _DWORD *v2; // esi
  int v3; // eax
  struct ArgList_s *v4; // edi
  int i; // ecx

  v2 = pxContext;
  v3 = *(_DWORD *)pxContext;
  v4 = *((struct ArgList_s **)pxContext + 1);
  for ( i = 0; i < 1; ++i )
  {
    if ( i + v3 >= v4->nArguments )
    {
      LDebug_Error(
        "Too few parameters in line %d of file '%s'",
        *((_DWORD *)pxContext + 3),
        *((char **)pxContext + 2));
      abort();
    }
  }
  if ( v4->isQVM )
  {
    pxContext = nullptr;
    QVM_EvalArg(&pxContext, 4, v4, v3, 1);
    *(_DWORD *)pxData = pxContext;
  }
  else
  {
    *(_DWORD *)pxData = Expression_EvalInt(v4->aptExpression[v3]);
  }
  ++*v2;
}

// source: h/1/level.c:1714  [size]
void __cdecl Level_GetNumberOfArgumentsInt32Handler(void *pxData, void *pxContext)
{
  *(_DWORD *)pxContext = 1;
}

// source: h/1/level.c:1730  [size]
void __cdecl Level_PrintInt32Handler(void *pxData, void *pxContext)
{
  sprintf(
    *((char **)pxContext + 2),
    (char *const)&g_ptNetManager.tReceiveCounters.tCounters[9].nBytes,
    *(_DWORD *)pxData);
}

// source: h/1/level.c:1756  [size]
void __cdecl Level_CopyInt32Handler(void *pxData, void *pxContext)
{
  **(_DWORD **)pxContext = *(_DWORD *)pxData;
}

// source: h/1/level.c:1774  [size]
void __cdecl Level_PasteInt32Handler(void *pxData, void *pxContext)
{
  *(_DWORD *)pxData = **(_DWORD **)pxContext;
}

// source: h/1/level.c:1792  [size]
void __cdecl Level_GetSizeInt32Handler(void *pxData, void *pxContext)
{
  *(_DWORD *)pxContext = 4;
}

// source: h/1/level.c:1810  [size]
void __cdecl Level_ParseInt16Handler(void *pxData, void *pxContext)
{
  _DWORD *v2; // esi
  int v3; // eax
  struct ArgList_s *v4; // edi
  int i; // ecx

  v2 = pxContext;
  v3 = *(_DWORD *)pxContext;
  v4 = *((struct ArgList_s **)pxContext + 1);
  for ( i = 0; i < 1; ++i )
  {
    if ( i + v3 >= v4->nArguments )
    {
      LDebug_Error(
        "Too few parameters in line %d of file '%s'",
        *((_DWORD *)pxContext + 3),
        *((char **)pxContext + 2));
      abort();
    }
  }
  if ( v4->isQVM )
  {
    pxContext = nullptr;
    QVM_EvalArg(&pxContext, 4, v4, v3, 1);
    *(_WORD *)pxData = (_WORD)pxContext;
  }
  else
  {
    *(_WORD *)pxData = Expression_EvalInt(v4->aptExpression[v3]);
  }
  ++*v2;
}

// source: h/1/level.c:1839  [size]
void __cdecl Level_GetNumberOfArgumentsInt16Handler(void *pxData, void *pxContext)
{
  *(_DWORD *)pxContext = 1;
}

// source: h/1/level.c:1855  [anchor-mhash]
void __cdecl Level_PrintInt16Handler(void *pxData, void *pxContext)
{
  sprintf(
    *((char **)pxContext + 2),
    (char *const)&g_ptNetManager.tReceiveCounters.tCounters[9].nBytes,
    *(__int16 *)pxData);
}

// source: h/1/level.c:1881  [size]
void __cdecl Level_CopyInt16Handler(void *pxData, void *pxContext)
{
  **(_WORD **)pxContext = *(_WORD *)pxData;
}

// source: h/1/level.c:1899  [size]
void __cdecl Level_PasteInt16Handler(void *pxData, void *pxContext)
{
  *(_WORD *)pxData = **(_WORD **)pxContext;
}

// source: h/1/level.c:1917  [size]
void __cdecl Level_GetSizeInt16Handler(void *pxData, void *pxContext)
{
  *(_DWORD *)pxContext = 2;
}

// source: h/1/level.c:1935  [anchor-mhash]
void __cdecl Level_ParseVarStringHandler(void *pxData, void *pxContext)
{
  int v2; // esi
  struct ArgList_s *v3; // edi
  int v4; // eax
  int i; // ecx
  char *v6; // eax
  char zBuffer[1024]; // [esp+14h] [ebp-400h] BYREF

  if ( *(_DWORD *)pxData )
  {
    v2 = *(_DWORD *)((*(_DWORD *)pxData - 4) & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v2);
    memset(*(void **)(v2 + 8), 0xCDu, *(_DWORD *)(v2 + 16));
    free((void *)v2);
    *(_DWORD *)pxData = 0;
  }
  v3 = *((struct ArgList_s **)pxContext + 1);
  v4 = *(_DWORD *)pxContext;
  for ( i = 0; i < 1; ++i )
  {
    if ( i + v4 >= v3->nArguments )
    {
      LDebug_Error(
        "Too few parameters in line %d of file '%s'",
        *((_DWORD *)pxContext + 3),
        *((char **)pxContext + 2));
      abort();
    }
  }
  if ( v3->isQVM )
  {
    zBuffer[0] = 0;
    QVM_EvalArg(zBuffer, 1024, v3, v4, 3);
  }
  else
  {
    Expression_EvalString(v3->aptExpression[v4], zBuffer, 1024);
  }
  if ( strlen(zBuffer) )
  {
    v6 = (char *)Mem_AllocFn(strlen(zBuffer) + 1, 4);
    *(_DWORD *)pxData = v6;
    strcpy(v6, zBuffer);
  }
  ++*(_DWORD *)pxContext;
}

// source: h/1/level.c:1976  [size]
void __cdecl Level_GetNumberOfArgumentsVarStringHandler(void *pxData, void *pxContext)
{
  *(_DWORD *)pxContext = 1;
}

// source: h/1/level.c:1992  [anchor-mhash]
void __cdecl Level_PrintVarStringHandler(void *pxData, void *pxContext)
{
  if ( *(_DWORD *)pxData )
    Level_PrintString(
      *((char **)pxContext + 2),
      *((_DWORD *)pxContext + 3),
      *(char **)pxData,
      *((enum bool *)pxContext + 1),
      0x7FCu);
  else
    Level_PrintString(
      *((char **)pxContext + 2),
      *((_DWORD *)pxContext + 3),
      (char *)&g_zInitialValue,
      *((enum bool *)pxContext + 1),
      0x7FCu);
}

// source: h/1/level.c:2021  [anchor-mhash]
void __cdecl Level_CopyVarStringHandler(void *pxData, void *pxContext)
{
  if ( *(_DWORD *)pxData )
    strcpy(*(char **)pxContext, *(char **)pxData);
  else
    **(_BYTE **)pxContext = 0;
}

// source: h/1/level.c:2050  [anchor-mhash]
void __cdecl Level_PasteVarStringHandler(void *pxData, void *pxContext)
{
  int v2; // esi
  char *v3; // eax

  if ( *(_DWORD *)pxData )
  {
    v2 = *(_DWORD *)((*(_DWORD *)pxData - 4) & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v2);
    memset(*(void **)(v2 + 8), 0xCDu, *(_DWORD *)(v2 + 16));
    free((void *)v2);
    *(_DWORD *)pxData = 0;
  }
  if ( strlen(*(char **)pxContext) )
  {
    v3 = (char *)Mem_AllocFn(strlen(*(char **)pxContext) + 1, 4);
    *(_DWORD *)pxData = v3;
    strcpy(v3, *(char **)pxContext);
  }
}

// source: h/1/level.c:2081  [anchor-mhash]
void __cdecl Level_GetSizeVarStringHandler(void *pxData, void *pxContext)
{
  if ( *(_DWORD *)pxData )
    *(_DWORD *)pxContext = strlen(*(char **)pxData) + 1;
  else
    *(_DWORD *)pxContext = 1;
}

// source: h/1/level.c:2110  [size]
void __cdecl Level_ParseString16Handler(void *pxData, void *pxContext)
{
  int v2; // eax
  struct ArgList_s *v3; // edi
  int i; // ecx

  v2 = *(_DWORD *)pxContext;
  v3 = *((struct ArgList_s **)pxContext + 1);
  for ( i = 0; i < 1; ++i )
  {
    if ( i + v2 >= v3->nArguments )
    {
      LDebug_Error(
        "Too few parameters in line %d of file '%s'",
        *((_DWORD *)pxContext + 3),
        *((char **)pxContext + 2));
      abort();
    }
  }
  if ( v3->isQVM )
  {
    *(_BYTE *)pxData = 0;
    QVM_EvalArg(pxData, 16, v3, v2, 3);
  }
  else
  {
    Expression_EvalString(v3->aptExpression[v2], (char *)pxData, 16);
  }
  ++*(_DWORD *)pxContext;
}

// source: h/1/level.c:2139  [size]
void __cdecl Level_GetNumberOfArgumentsString16Handler(void *pxData, void *pxContext)
{
  *(_DWORD *)pxContext = 1;
}

// source: h/1/level.c:2155  [anchor-mhash]
void __cdecl Level_PrintStringHandler(void *pxData, void *pxContext)
{
  Level_PrintString(
    *((char **)pxContext + 2),
    *((_DWORD *)pxContext + 3),
    (char *)pxData,
    *((enum bool *)pxContext + 1),
    0x7FCu);
}

// source: h/1/level.c:2177  [size]
void __cdecl Level_CopyString16Handler(void *pxData, void *pxContext)
{
  strcpy(*(char **)pxContext, (char *)pxData);
}

// source: h/1/level.c:2195  [size]
void __cdecl Level_PasteString16Handler(void *pxData, void *pxContext)
{
  strcpy((char *)pxData, *(char **)pxContext);
}

// source: h/1/level.c:2213  [size]
void __cdecl Level_GetSizeString16Handler(void *pxData, void *pxContext)
{
  *(_DWORD *)pxContext = strlen((char *)pxData) + 1;
}

// source: h/1/level.c:2231  [size]
void __cdecl Level_ParseString32Handler(void *pxData, void *pxContext)
{
  int v2; // eax
  struct ArgList_s *v3; // edi
  int i; // ecx

  v2 = *(_DWORD *)pxContext;
  v3 = *((struct ArgList_s **)pxContext + 1);
  for ( i = 0; i < 1; ++i )
  {
    if ( i + v2 >= v3->nArguments )
    {
      LDebug_Error(
        "Too few parameters in line %d of file '%s'",
        *((_DWORD *)pxContext + 3),
        *((char **)pxContext + 2));
      abort();
    }
  }
  if ( v3->isQVM )
  {
    *(_BYTE *)pxData = 0;
    QVM_EvalArg(pxData, 32, v3, v2, 3);
  }
  else
  {
    Expression_EvalString(v3->aptExpression[v2], (char *)pxData, 32);
  }
  ++*(_DWORD *)pxContext;
}

// source: h/1/level.c:2260  [size]
void __cdecl Level_GetNumberOfArgumentsString32Handler(void *pxData, void *pxContext)
{
  *(_DWORD *)pxContext = 1;
}

// source: h/1/level.c:2276  [size]
void __cdecl Level_CopyString32Handler(void *pxData, void *pxContext)
{
  strcpy(*(char **)pxContext, (char *)pxData);
}

// source: h/1/level.c:2294  [size]
void __cdecl Level_PasteString32Handler(void *pxData, void *pxContext)
{
  strcpy((char *)pxData, *(char **)pxContext);
}

// source: h/1/level.c:2312  [size]
void __cdecl Level_GetSizeString32Handler(void *pxData, void *pxContext)
{
  *(_DWORD *)pxContext = strlen((char *)pxData) + 1;
}

// source: h/1/level.c:2331  [size]
void __cdecl Level_ParseString256Handler(void *pxData, void *pxContext)
{
  int v2; // eax
  struct ArgList_s *v3; // edi
  int i; // ecx

  v2 = *(_DWORD *)pxContext;
  v3 = *((struct ArgList_s **)pxContext + 1);
  for ( i = 0; i < 1; ++i )
  {
    if ( i + v2 >= v3->nArguments )
    {
      LDebug_Error(
        "Too few parameters in line %d of file '%s'",
        *((_DWORD *)pxContext + 3),
        *((char **)pxContext + 2));
      abort();
    }
  }
  if ( v3->isQVM )
  {
    *(_BYTE *)pxData = 0;
    QVM_EvalArg(pxData, 256, v3, v2, 3);
  }
  else
  {
    Expression_EvalString(v3->aptExpression[v2], (char *)pxData, 256);
  }
  ++*(_DWORD *)pxContext;
}

// source: h/1/level.c:2360  [size]
void __cdecl Level_GetNumberOfArgumentsString256Handler(void *pxData, void *pxContext)
{
  *(_DWORD *)pxContext = 1;
}

// source: h/1/level.c:2405  [size]
void __cdecl Level_CopyString256Handler(void *pxData, void *pxContext)
{
  strcpy(*(char **)pxContext, (char *)pxData);
}

// source: h/1/level.c:2423  [size]
void __cdecl Level_PasteString256Handler(void *pxData, void *pxContext)
{
  strcpy((char *)pxData, *(char **)pxContext);
}

// source: h/1/level.c:2441  [size]
void __cdecl Level_GetSizeString256Handler(void *pxData, void *pxContext)
{
  *(_DWORD *)pxContext = strlen((char *)pxData) + 1;
}

// source: h/1/level.c:2459  [anchor-mhash]
void __cdecl Level_ParseLevelExpressionHandler(void *pxData, void *pxContext)
{
  int v2; // eax
  struct ArgList_s *v3; // edi
  int i; // ecx
  char *v5; // edx
  int v6; // ecx

  v2 = *(_DWORD *)pxContext;
  v3 = *((struct ArgList_s **)pxContext + 1);
  for ( i = 0; i < 1; ++i )
  {
    if ( i + v2 >= v3->nArguments )
    {
      LDebug_Error(
        "Too few parameters in line %d of file '%s'",
        *((_DWORD *)pxContext + 3),
        *((char **)pxContext + 2));
      abort();
    }
  }
  v5 = *(char **)pxData;
  v6 = strlen(*(char **)pxData);
  if ( v3->isQVM )
  {
    *v5 = 0;
    QVM_EvalArg(v5, v6, v3, v2, 3);
  }
  else
  {
    Expression_EvalString(v3->aptExpression[v2], v5, v6);
  }
  ++*(_DWORD *)pxContext;
}

// source: h/1/level.c:2488  [size]
void __cdecl Level_GetNumberOfArgumentsLevelExpressionHandler(void *pxData, void *pxContext)
{
  *(_DWORD *)pxContext = 1;
}

// source: h/1/level.c:2504  [size]
void __cdecl Level_PrintLevelExpressionHandler(void *pxData, void *pxContext)
{
  sprintf(
    *((char **)pxContext + 2),
    (char *const)&stru_6A4CDC.tDebugConsoleLineList.ptMiddle,
    *(_DWORD *)pxData);
}

// source: h/1/level.c:2532  [size]
void __cdecl Level_CopyLevelExpressionHandler(void *pxData, void *pxContext)
{
  strcpy(*(char **)pxContext, (char *)pxData);
}

// source: h/1/level.c:2550  [size]
void __cdecl Level_PasteLevelExpressionHandler(void *pxData, void *pxContext)
{
  strcpy((char *)pxData, *(char **)pxContext);
}

// source: h/1/level.c:2568  [size]
void __cdecl Level_GetSizeLevelExpressionHandler(void *pxData, void *pxContext)
{
  *(_DWORD *)pxContext = strlen((char *)pxData) + 1;
}

// source: h/1/level.c:2586  [size]
void __cdecl Level_Parsebool8Handler(void *pxData, void *pxContext)
{
  _DWORD *v2; // esi
  int v3; // eax
  struct ArgList_s *v4; // edi
  int i; // ecx

  v2 = pxContext;
  v3 = *(_DWORD *)pxContext;
  v4 = *((struct ArgList_s **)pxContext + 1);
  for ( i = 0; i < 1; ++i )
  {
    if ( i + v3 >= v4->nArguments )
    {
      LDebug_Error(
        "Too few parameters in line %d of file '%s'",
        *((_DWORD *)pxContext + 3),
        *((char **)pxContext + 2));
      abort();
    }
  }
  if ( v4->isQVM )
  {
    pxContext = nullptr;
    QVM_EvalArg(&pxContext, 4, v4, v3, 1);
    *(_BYTE *)pxData = (_BYTE)pxContext;
  }
  else
  {
    *(_BYTE *)pxData = Expression_EvalInt(v4->aptExpression[v3]);
  }
  ++*v2;
}

// source: h/1/level.c:2617  [size]
void __cdecl Level_GetNumberOfArgumentsbool8Handler(void *pxData, void *pxContext)
{
  *(_DWORD *)pxContext = 1;
}

// source: h/1/level.c:2633  [anchor-strings]
void __cdecl Level_Printbool8Handler(void *pxData, void *pxContext)
{
  char *v2; // eax

  v2 = "TRUE";
  if ( !*(_BYTE *)pxData )
    v2 = "FALSE";
  sprintf(*((char **)pxContext + 2), (char *const)&stru_6A4CDC.tDebugConsoleLineList.ptMiddle, v2);
}

// source: h/1/level.c:2659  [size]
void __cdecl Level_Copybool8Handler(void *pxData, void *pxContext)
{
  **(_BYTE **)pxContext = *(_BYTE *)pxData;
}

// source: h/1/level.c:2677  [size]
void __cdecl Level_Pastebool8Handler(void *pxData, void *pxContext)
{
  *(_BYTE *)pxData = **(_BYTE **)pxContext;
}

// source: h/1/level.c:2695  [size]
void __cdecl Level_GetSizebool8Handler(void *pxData, void *pxContext)
{
  *(_DWORD *)pxContext = 1;
}

// source: h/1/level.c:2715  [anchor-mhash]
void __cdecl Level_LevelRunHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptHead; // ecx
  int v2; // edx
  struct QTask_s *v3; // eax
  void (__cdecl *pfHandler)(struct QTask_s *); // eax
  int v5; // edx
  struct QLevelQTask_s *v6; // eax

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
  v6 = Level_ptQLevelQTask;
  Level_ptQLevelQTask->nTime += Level_ptQLevelQTask->nMilisecondsPerTick;
  ++v6->nTicks;
}

// source: h/1/level.c:2750  [size]
void __cdecl Level_LevelCreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  Level_ptQLevelQTask = (struct QLevelQTask_s *)ptQTask;
}

// source: h/1/level.c:2765  [size]
void __cdecl Level_LevelDeleteHandler(struct QTask_s *ptQTask)
{
  Level_ptQLevelQTask = nullptr;
}

// source: h/1/level.c:2780  [size]
void __cdecl Level_StaticRunHandler(struct QTask_s *ptQTask)
{
  ;
}

// source: h/1/level.c:2793  [size]
void __cdecl Level_StaticCreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  if ( !Level_ptStaticQTask )
    Level_ptStaticQTask = ptQTask;
}

// source: h/1/level.c:2809  [size]
void __cdecl Level_StaticDeleteHandler(struct QTask_s *ptQTask)
{
  if ( Level_ptStaticQTask )
    Level_ptStaticQTask = nullptr;
}

// source: h/1/level.c:2825  [size]
void __cdecl Level_StaticRegisterHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *ptHead; // eax
  int v3; // edx
  struct QTask_s *v4; // ecx
  void (__cdecl *pfHandler)(struct QTask_s *, void *); // ecx
  int v6; // edx

  ptHead = ptQTask->tQTaskChildren.ptHead;
  if ( ptHead->ptNext && ptHead )
  {
    v3 = QTask_nProtectedQTaskStackOffset;
    do
    {
      if ( ptHead->ptNext )
        v4 = ptHead->ptNext->ptNext != nullptr ? ptHead->ptNext : nullptr;
      else
        v4 = nullptr;
      QTask_atProtectedQTaskStack[v3].ptQTask = v4;
      pfHandler = (void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[DynCubeObj_eDynCubeObjRegisterQTaskEvent][ptHead->eQTaskType].pfHandler;
      v6 = v3 + 1;
      QTask_nProtectedQTaskStackOffset = v6;
      if ( pfHandler )
      {
        pfHandler(ptHead, pxContext);
        v6 = QTask_nProtectedQTaskStackOffset;
      }
      ptHead = (struct QTask_s *)dword_849C7DC[v6];
      v3 = v6 - 1;
      QTask_nProtectedQTaskStackOffset = v3;
    }
    while ( ptHead );
  }
}

// source: h/1/level.c:2839  [size]
void __cdecl Level_StaticRemoveHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *ptHead; // eax
  int v3; // edx
  struct QTask_s *v4; // ecx
  void (__cdecl *pfHandler)(struct QTask_s *, void *); // ecx
  int v6; // edx

  ptHead = ptQTask->tQTaskChildren.ptHead;
  if ( ptHead->ptNext && ptHead )
  {
    v3 = QTask_nProtectedQTaskStackOffset;
    do
    {
      if ( ptHead->ptNext )
        v4 = ptHead->ptNext->ptNext != nullptr ? ptHead->ptNext : nullptr;
      else
        v4 = nullptr;
      QTask_atProtectedQTaskStack[v3].ptQTask = v4;
      pfHandler = (void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[DynCubeObj_eDynCubeObjRemoveQTaskEvent][ptHead->eQTaskType].pfHandler;
      v6 = v3 + 1;
      QTask_nProtectedQTaskStackOffset = v6;
      if ( pfHandler )
      {
        pfHandler(ptHead, pxContext);
        v6 = QTask_nProtectedQTaskStackOffset;
      }
      ptHead = (struct QTask_s *)dword_849C7DC[v6];
      v3 = v6 - 1;
      QTask_nProtectedQTaskStackOffset = v3;
    }
    while ( ptHead );
  }
}

// source: h/1/level.c:2853  [anchor-mhash]
void __cdecl Level_DynamicRunHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptHead; // ecx
  int v2; // edx
  struct QTask_s *v3; // eax
  void (__cdecl *pfHandler)(struct QTask_s *); // eax
  int v5; // edx

  if ( !Level_isDynamicQTaskPaused )
  {
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
    RunDelayed_Run();
  }
}

// source: h/1/level.c:2873  [size]
void __cdecl Level_DynamicCreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  Level_ptDynamicQTask = ptQTask;
}

// source: h/1/level.c:2888  [size]
void __cdecl Level_DynamicDeleteHandler(struct QTask_s *ptQTask)
{
  Level_ptDynamicQTask = nullptr;
}

// source: h/1/level.c:2903  [size]
void __cdecl Level_IdleRunHandler(struct QTask_s *ptQTask)
{
  ;
}

// source: h/1/level.c:2916  [size]
void __cdecl Level_IdleCreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  Level_ptIdleQTask = ptQTask;
}

// source: h/1/level.c:2931  [size]
void __cdecl Level_IdleDeleteHandler(struct QTask_s *ptQTask)
{
  Level_ptIdleQTask = nullptr;
}

// source: h/1/level.c:2946  [size]
void __cdecl Level_CameraBaseRunHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptHead; // ecx
  int v2; // edx
  struct QTask_s *v3; // eax
  void (__cdecl *pfHandler)(struct QTask_s *); // eax
  int v5; // edx

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
}

// source: h/1/level.c:2959  [size]
void __cdecl Level_CameraBaseCreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  Level_ptCameraBaseQTask = ptQTask;
}

// source: h/1/level.c:2974  [size]
void __cdecl Level_CameraBaseDeleteHandler(struct QTask_s *ptQTask)
{
  Level_ptCameraBaseQTask = nullptr;
}

// source: h/1/level.c:2996  [anchor-callee]
struct QTask_s *__cdecl Level_GetChildQTaskOfTypeRecursive(
        enum bool *pisValid,
        struct QTask_s *ptParent,
        struct QTask_s *ptSkipQTask,
        unsigned __int16 eQTask,
        enum bool isRecursive)
{
  struct QTask_s *ptHead; // ecx
  struct QTask_s *result; // eax
  struct QTask_s *ptParenta = *(struct QTask_s * *)&ptParent; // [esp+18h] [ebp+8h] ARGSLOT

  ptHead = ptParent->tQTaskChildren.ptHead;
  result = nullptr;
  for ( ptParenta = ptHead->ptNext; ptParenta; ptParenta = ptParenta->ptNext )
  {
    if ( *pisValid )
    {
      if ( ptHead->eQTaskType == eQTask )
      {
        result = ptHead;
        goto LABEL_9;
      }
    }
    else if ( ptHead == ptSkipQTask )
    {
      *pisValid = true;
      goto LABEL_10;
    }
    if ( isRecursive )
    {
      result = Level_GetChildQTaskOfTypeRecursive(pisValid, ptHead, ptSkipQTask, eQTask, isRecursive);
LABEL_9:
      if ( result )
        return result;
    }
LABEL_10:
    ptHead = ptParenta;
  }
  return result;
}

// source: h/1/level.c:3052  [anchor-caller]
struct QTask_s *__cdecl Level_GetChildQTaskOfType(
        struct QTask_s *ptParent,
        struct QTask_s *ptSkipQTask,
        unsigned __int16 eQTask,
        enum bool isRecursive)
{
  enum bool isValid; // [esp+4h] [ebp-4h] BYREF

  isValid = ptSkipQTask == nullptr;
  return Level_GetChildQTaskOfTypeRecursive(&isValid, ptParent, ptSkipQTask, eQTask, isRecursive);
}

// source: h/1/level.c:3073  [anchor-callee]
char *__cdecl levelstrtok(char *zString, char *zFormat)
{
  BOOL v3; // ebp
  int v4; // eax
  char v5; // dl
  bool v6; // zf
  char *v7; // ebx
  int v8; // ecx
  char v10; // cl
  char *v11; // esi
  int i; // ecx

  v3 = 0;
  v4 = strlen(zFormat);
  if ( zString )
    dword_79F4390 = (int)zString;
  else
    zString = (char *)dword_79F4390;
  v5 = *zString;
  v6 = *zString == 0;
  v7 = zString;
  dword_79F53F4 = (int)zString;
  if ( v6 )
    return v7 == zString ? nullptr : v7;
  while ( 1 )
  {
    if ( v5 == 34 )
      v3 = !v3;
    if ( !v3 )
    {
      v8 = 0;
      if ( v4 > 0 )
        break;
    }
LABEL_11:
    v5 = *++zString;
    dword_79F4390 = (int)zString;
    if ( !v5 )
      return v7 == zString ? nullptr : v7;
  }
  while ( v5 != zFormat[v8] )
  {
    if ( ++v8 >= v4 )
      goto LABEL_11;
  }
  *zString = 0;
  v10 = zString[1];
  v11 = zString + 1;
  dword_79F4390 = (int)v11;
  if ( v10 )
  {
    for ( i = 0; i < v4; ++i )
    {
      if ( *v11 == zFormat[i] )
        ++v11;
    }
    dword_79F4390 = (int)v11;
  }
  return v7;
}

// source: h/1/level.c:3135  [anchor-callee]
void __cdecl Level_SplitArgumentString(char *zBuffer, int nIndent, char *zTempBuffer)
{
  char *v3; // ebp
  char *v4; // eax
  int v5; // ecx

  *zTempBuffer = 0;
  v3 = zTempBuffer;
  v4 = levelstrtok(zBuffer, (char *)&Delimiter);
  while ( v4 )
  {
    strcat(zTempBuffer, v4);
    if ( strlen(v3) < 0xFF )
    {
      v4 = levelstrtok(nullptr, (char *)&Delimiter);
      if ( !v4 )
        break;
      *(_WORD *)&zTempBuffer[strlen(zTempBuffer)] = 32;
    }
    else
    {
      strcat(zTempBuffer, "\r\n");
      v5 = nIndent;
      if ( nIndent > 0 )
      {
        do
        {
          --v5;
          *(_WORD *)&zTempBuffer[strlen(zTempBuffer)] = 32;
        }
        while ( v5 );
      }
      v3 = &zTempBuffer[strlen(zTempBuffer)];
      v4 = levelstrtok(nullptr, (char *)&Delimiter);
    }
  }
  strcpy(zBuffer, zTempBuffer);
}

// source: h/1/level.c:3187  [anchor-strings]
enum bool __cdecl Level_SaveQTaskChildren(
        struct File_s *ptFile,
        struct QTask_s *ptParent,
        char *zPrefix,
        int nIndent,
        enum bool isParentSaved,
        char *zBuffer,
        char *zTempBuffer2,
        enum bool isAutoAllocateQTaskID)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct QTask_s *ptQTask; };
    struct { char igi2_o1[4]; struct ParameterList_s *ptParameterList; };
    struct { char igi2_o2[8]; int i; };
    struct { char igi2_o3[12]; struct AllowSaveQTaskContext_s tEditMode; };
    struct { char igi2_o4[24]; struct ParameterPrintContext_s tParameterPrintContext; };
    char igi2_extent[44];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *v8; // ebx
  enum bool v9; // esi
  void (__cdecl *pfHandler)(struct QTask_s *, struct AllowSaveQTaskContext_s *); // eax
  void (__cdecl *v11)(struct QTask_s *, struct ParameterList_s **); // eax
  void (__cdecl *v12)(struct QTask_s *, _DWORD); // eax
  int v13; // edi
  int v14; // eax
  struct QReference_s *v15; // ecx
  int v16; // eax
  struct QReference_s *v17; // ecx
  char *v18; // edi
  struct QTaskNote_s *QTaskNoteNode; // eax
  struct StaticTilemap_s *zString; // esi
  int v21; // ecx
  int v22; // ecx
  int v23; // eax
  bool v24; // zf
  struct ParameterList_s *v26; // ecx
  bool v27; // cc
  int v28; // esi
  struct ParameterListItem_s *ptParameterListItem; // eax
  char *v30; // ebp
  struct QTask_s *ptNext; // ebx
  struct QTask_s *v32; // eax

  if ( isParentSaved )
  {
    v8 = ptParent;
    igi2_frame.ptQTask = ptParent;
  }
  else
  {
    igi2_frame.ptQTask = ptParent->tQTaskChildren.ptHead->ptNext != nullptr ? ptParent->tQTaskChildren.ptHead : nullptr;
    v8 = igi2_frame.ptQTask;
  }
  v9 = false;
  if ( v8 )
  {
    while ( 1 )
    {
      pfHandler = (void (__cdecl *)(struct QTask_s *, struct AllowSaveQTaskContext_s *))QTask_aatQTaskFinalEvent[Level_eAllowSaveQTaskEvent][v8->eQTaskType].pfHandler;
      if ( pfHandler )
      {
        pfHandler(v8, &igi2_frame.tEditMode);
        if ( igi2_frame.tEditMode.tReturn.isSave )
        {
          v11 = (void (__cdecl *)(struct QTask_s *, struct ParameterList_s **))QTask_aatQTaskFinalEvent[ParameterList_eGetParameterListQTaskEvent][v8->eQTaskType].pfHandler;
          igi2_frame.ptParameterList = nullptr;
          if ( v11 )
            v11(v8, &igi2_frame.ptParameterList);
          v12 = (void (__cdecl *)(struct QTask_s *, _DWORD))QTask_aatQTaskFinalEvent[Level_eSaveQTaskQTaskEvent][v8->eQTaskType].pfHandler;
          if ( v12 )
            v12(v8, 0);
          File_printf(ptFile, (char *)&stru_6A4CDC.tDebugConsoleLineList.ptMiddle);
          v13 = nIndent;
          if ( nIndent > 0 )
          {
            do
            {
              File_printf(ptFile, (char *)&Delimiter);
              --v13;
            }
            while ( v13 );
          }
          if ( isAutoAllocateQTaskID )
          {
            v14 = 0;
            while ( 1 )
            {
              v15 = Level_atLevelQTaskID[v14];
              if ( v15 )
              {
                if ( v15->pxObject == v8 )
                  break;
              }
              if ( ++v14 >= 4096 )
                goto LABEL_23;
            }
            if ( v14 < 0 || !Level_aisLevelQTaskAllocated[v14] )
LABEL_23:
              Level_AutoAllocateQTaskID(v8);
          }
          v16 = 0;
          while ( 1 )
          {
            v17 = Level_atLevelQTaskID[v16];
            if ( v17 )
            {
              if ( v17->pxObject == v8 )
                break;
            }
            if ( ++v16 >= 4096 )
              goto LABEL_31;
          }
          if ( v16 < 0 || !Level_aisLevelQTaskAllocated[v16] )
LABEL_31:
            v16 = -1;
          v18 = zBuffer;
          sprintf(zBuffer, "Task_New(%d, \"%s\", ", v16, QTask_atQTaskType[v8->eQTaskType].zName);
          dword_79F427C = (int)&zBuffer[strlen(zBuffer)];
          QTaskNoteNode = Level_GetQTaskNoteNode(v8);
          zString = (struct StaticTilemap_s *)QTaskNoteNode->zString;
          if ( !QTaskNoteNode )
            zString = &g_zInitialValue;
          v21 = dword_79F427C;
          *(_BYTE *)dword_79F427C = 34;
          v22 = v21 + 1;
          v23 = 0;
          v24 = LOBYTE(zString->ptQTilemap) == 0;
          dword_79F427C = v22;
          if ( !v24 )
          {
            do
            {
              if ( *((_BYTE *)&zString->ptQTilemap + v23) == 34 )
              {
                *(_BYTE *)(v22 + v23) = 92;
                ++v22;
              }
              *(_BYTE *)(v22 + v23) = *((_BYTE *)&zString->ptQTilemap + v23);
            }
            while ( *((_BYTE *)&zString->ptQTilemap + ++v23) );
            dword_79F427C = v22;
          }
          *(_BYTE *)(v22 + v23) = 34;
          *(_BYTE *)(v22 + v23 + 1) = 0;
          v26 = igi2_frame.ptParameterList;
          if ( igi2_frame.ptParameterList )
          {
            v27 = igi2_frame.ptParameterList->nParameters <= 0;
            igi2_frame.i = 0;
            if ( !v27 )
            {
              v28 = 0;
              do
              {
                ptParameterListItem = v26->ptParameterListItem;
                if ( (ptParameterListItem[v28].bParameterProperties & 1) != 0 )
                {
                  v30 = (char *)igi2_frame.ptQTask + ptParameterListItem[v28].nOffset;
                  strcat(v18, ", ");
                  igi2_frame.tParameterPrintContext.ptParameterListItem = nullptr;
                  igi2_frame.tParameterPrintContext.tReturn.isBufferOverflow = false;
                  igi2_frame.tParameterPrintContext.isQuoteStrings = true;
                  igi2_frame.tParameterPrintContext.nBufferSize = 0x7FFFFFFF;
                  igi2_frame.tParameterPrintContext.zBuffer = &zBuffer[strlen(zBuffer)];
                  igi2_frame.tParameterPrintContext.ptParameterListItem = &v26->ptParameterListItem[v28];
                  ParameterList_atParameterType[v26->ptParameterListItem[v28].eParameterType].apfQParameterEvent[ParameterList_eQParameterPrintEvent](
                    v30,
                    &igi2_frame.tParameterPrintContext);
                  v26 = igi2_frame.ptParameterList;
                  v18 = zBuffer;
                }
                ++v28;
                v27 = ++igi2_frame.i < v26->nParameters;
              }
              while ( v27 );
            }
          }
          Level_SplitArgumentString(v18, nIndent + 2, zTempBuffer2);
          File_printf(ptFile, (char *)&stru_6A4CDC.tDebugConsoleLineList.ptMiddle);
          if ( igi2_frame.tEditMode.tReturn.isSaveChildren )
            Level_SaveQTaskChildren(
              ptFile,
              igi2_frame.ptQTask,
              ",\r\n",
              nIndent + 2,
              false,
              v18,
              zTempBuffer2,
              isAutoAllocateQTaskID);
          if ( nIndent )
            File_printf(ptFile, (char *)&g_zSpriteName_0.tQTaskChildren.ptMiddle);
          else
            File_printf(ptFile, &g_zFileName.atPictureResources[19].zResourceFilename[56]);
          v8 = igi2_frame.ptQTask;
          v9 = true;
        }
      }
      ptNext = v8->ptNext;
      if ( ptNext )
      {
        v32 = ptNext->ptNext != nullptr ? ptNext : nullptr;
        igi2_frame.ptQTask = v32;
      }
      else
      {
        igi2_frame.ptQTask = nullptr;
        v32 = nullptr;
      }
      if ( isParentSaved || !v32 )
        break;
      v8 = igi2_frame.ptQTask;
    }
  }
  return v9;
}

// source: h/1/level.c:3331  [size]
void __cdecl Level_SaveQTaskSaveHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *((_DWORD *)pxContext + 1) = 1;
  *((_DWORD *)pxContext + 2) = 1;
  *(_DWORD *)pxContext = 1;
}

// source: h/1/level.c:3351  [size]
void __cdecl Level_SaveQTaskSaveNoChildrenHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *((_DWORD *)pxContext + 1) = 1;
  *((_DWORD *)pxContext + 2) = 0;
  *(_DWORD *)pxContext = 1;
}

// source: h/1/level.c:3371  [size]
void __cdecl Level_SaveQTaskDontSaveHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *((_DWORD *)pxContext + 1) = 0;
  *((_DWORD *)pxContext + 2) = 0;
  *(_DWORD *)pxContext = 0;
}

// source: h/1/level.c:3391  [size]
void __cdecl Level_SaveQTaskDontSaveCreateableHandler(struct QTask_s *ptQTask, void *pxContext)
{
  *((_DWORD *)pxContext + 1) = 0;
  *((_DWORD *)pxContext + 2) = 0;
  *(_DWORD *)pxContext = 1;
}

// source: h/1/level.c:3411  [anchor-hash]
int __cdecl Level_GetQTaskHash(struct QTask_s *ptQTask)
{
  return (unsigned int)ptQTask % 0xFB;
}

// source: h/1/level.c:3428  [anchor-callee]
struct QTaskNote_s *__cdecl Level_GetQTaskNoteNode(struct QTask_s *ptQTask)
{
  struct QTaskNote_s *ptHead; // esi
  struct QTaskNote_s *i; // ebx
  struct QReference_s *ptQTaskRef; // eax
  struct QTask_s *pxObject; // ecx
  int v6; // esi

  ptHead = Level_atQTaskNoteHashTable[(unsigned int)ptQTask % 0xFB].ptHead;
  for ( i = ptHead->ptNext; i; i = i->ptNext )
  {
    ptQTaskRef = ptHead->ptQTaskRef;
    pxObject = (struct QTask_s *)ptQTaskRef->pxObject;
    if ( pxObject )
    {
      if ( pxObject == ptQTask )
        return ptHead;
    }
    else
    {
      QReference_Delete(ptQTaskRef, &QTask_tQTaskRefPool);
      Node_Remove(ptHead);
      v6 = *(_DWORD *)((unsigned int)&ptHead[-1].zString[60] & 0xFFFFFFFC);
      --Mem_nCurrentAllocations;
      Node_Remove((_DWORD **)v6);
      memset(*(void **)(v6 + 8), 0xCDu, *(_DWORD *)(v6 + 16));
      free((void *)v6);
    }
    ptHead = i;
  }
  return nullptr;
}

// source: h/1/level.c:3496  [anchor-hash]
void __cdecl Level_DeleteQTaskNoteNode(struct QTaskNote_s *ptQTaskNote)
{
  int v2; // esi

  QReference_Delete(ptQTaskNote->ptQTaskRef, &QTask_tQTaskRefPool);
  Node_Remove(ptQTaskNote);
  v2 = *(_DWORD *)((unsigned int)&ptQTaskNote[-1].zString[60] & 0xFFFFFFFC);
  --Mem_nCurrentAllocations;
  Node_Remove((_DWORD **)v2);
  memset(*(void **)(v2 + 8), 0xCDu, *(_DWORD *)(v2 + 16));
  free((void *)v2);
}

// source: h/1/level.c:3514  [anchor-callee]
struct ParameterListReference_s *__cdecl Level_ClearParameterListReference(
        struct ParameterListReference_s *ptList)
{
  struct ParameterListReference_s *result; // eax
  struct ParameterListReference_s *ptHead; // ebx
  _DWORD **v3; // eax
  int v4; // esi

  result = (struct ParameterListReference_s *)ptList->tParameterReferenceList.ptHead;
  ptHead = (struct ParameterListReference_s *)result->tParameterReferenceList.ptHead;
  if ( result->tParameterReferenceList.ptHead )
  {
    do
    {
      v3 = Node_Remove(result);
      if ( v3 )
      {
        v4 = *(_DWORD *)((unsigned int)(v3 - 1) & 0xFFFFFFFC);
        --Mem_nCurrentAllocations;
        Node_Remove((_DWORD **)v4);
        memset(*(void **)(v4 + 8), 0xCDu, *(_DWORD *)(v4 + 16));
        free((void *)v4);
      }
      result = ptHead;
      ptHead = (struct ParameterListReference_s *)ptHead->tParameterReferenceList.ptHead;
    }
    while ( ptHead );
  }
  return result;
}

// source: h/1/level.c:3537  [anchor-caller]
struct Result_s *__cdecl Level_DeclareTaskParameters(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct ParameterListReference_s *ptList; };
    struct { char igi2_o1[4]; enum bool isError; };
    struct { char igi2_o2[8]; int eParameterType; };
    struct { char igi2_o3[12]; struct Result_s Rs; };
    struct { char igi2_o4[36]; char zParameterName[256]; };
    struct { char igi2_o5[292]; char zQTaskType[256]; };
    struct { char igi2_o6[548]; char zParameterType[256]; };
    char igi2_extent[804];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v3; // ebp
  unsigned __int16 QTaskTypeSafe; // ax
  int v5; // ebp
  char *v6; // eax

  igi2_frame.isError = false;
  if ( ptArgList->nArguments > 0 )
  {
    if ( ptArgList->isQVM )
    {
      igi2_frame.zQTaskType[0] = 0;
      QVM_EvalArg(igi2_frame.zQTaskType, 256, ptArgList, 0, 3);
    }
    else
    {
      Expression_EvalString(*ptArgList->aptExpression, igi2_frame.zQTaskType, 256);
    }
    v3 = 1;
    QTaskTypeSafe = QTask_GetQTaskTypeSafe(igi2_frame.zQTaskType);
    if ( QTaskTypeSafe != 512 )
    {
      igi2_frame.ptList = (struct ParameterListReference_s *)(12 * QTaskTypeSafe + 127882232);
      Level_ClearParameterListReference(igi2_frame.ptList);
      if ( ptArgList->nArguments > 1 )
      {
        while ( 1 )
        {
          if ( ptArgList->isQVM )
          {
            igi2_frame.zParameterName[0] = 0;
            QVM_EvalArg(igi2_frame.zParameterName, 256, ptArgList, v3, 3);
          }
          else
          {
            Expression_EvalString(ptArgList->aptExpression[v3], igi2_frame.zParameterName, 256);
          }
          v5 = v3 + 1;
          if ( v5 >= ptArgList->nArguments )
            break;
          if ( ptArgList->isQVM )
          {
            igi2_frame.zParameterType[0] = 0;
            QVM_EvalArg(igi2_frame.zParameterType, 256, ptArgList, v5, 3);
          }
          else
          {
            Expression_EvalString(ptArgList->aptExpression[v5], igi2_frame.zParameterType, 256);
          }
          v3 = v5 + 1;
          igi2_frame.eParameterType = ParameterList_GetParameterTypeByName(igi2_frame.zParameterType);
          if ( igi2_frame.eParameterType == -1 )
          {
            igi2_frame.isError = true;
          }
          else
          {
            v6 = (char *)Mem_AllocFn(strlen(igi2_frame.zParameterName) + 17, 4);
            *((_DWORD *)v6 + 2) = v6 + 16;
            *((_DWORD *)v6 + 1) = 0;
            *(_DWORD *)v6 = 0;
            strcpy(v6 + 16, igi2_frame.zParameterName);
            *((_DWORD *)v6 + 3) = igi2_frame.eParameterType;
            List_AddTail(v6, (int)igi2_frame.ptList);
          }
          if ( v3 >= ptArgList->nArguments )
          {
            if ( igi2_frame.isError == false )
              goto LABEL_20;
            break;
          }
        }
        Level_ClearParameterListReference(igi2_frame.ptList);
      }
    }
  }
LABEL_20:
  igi2_frame.Rs.nResult = 0;
  igi2_frame.Rs.vResult = 0.0;
  igi2_frame.Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &igi2_frame.Rs, sizeof(struct Result_s));
  return retstr;
}

// source: h/1/level.c:3628  [anchor-mhash]
struct ParameterListItem_s *__cdecl ParameterList_GetParameterListItem(
        struct ParameterList_s *ptParameterList,
        char *zName)
{
  int v2; // esi
  int i; // ebx

  v2 = 0;
  if ( ptParameterList->nParameters <= 0 )
    return nullptr;
  for ( i = 0; _stricmp(ptParameterList->ptParameterListItem[i].zName, zName); ++i )
  {
    if ( ++v2 >= ptParameterList->nParameters )
      return nullptr;
  }
  return &ptParameterList->ptParameterListItem[v2];
}

// source: h/1/level.c:3653  [anchor-caller]
struct Result_s *__cdecl Level_QTaskNew(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  #pragma pack(push, 1)
  union
  {
    struct { int iArg; };
    struct { char igi2_o1[4]; int iID; };
    struct { char igi2_o2[8]; struct ParameterItemReference_s *ptTemp; };
    struct { char igi2_o3[12]; struct ParameterList_s *ptParameterList; };
    struct { char igi2_o4[16]; struct QTask_s *ptQTask; };
    struct { char igi2_o5[20]; struct ParameterParseContext_s tParameterParseContext; };
    struct { char igi2_o6[40]; struct ParameterGetNumberOfArgumentsContext_s tContext; };
    struct { char igi2_o7[64]; struct GetParameterListContext_t tGetParameterListContext; };
    struct { char igi2_o8[68]; char zQTaskType[100]; };
    struct { char igi2_o9[168]; char zQTaskNote[64]; };
    char igi2_extent[232];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct ArgList_s *v3; // esi
  int isQVM; // eax
  int nLinenumber; // ecx
  int v6; // eax
  int v7; // ebp
  unsigned __int16 QTaskType; // ax
  struct QTask_s *ChildFn; // ebx
  unsigned __int16 v10; // ax
  int v11; // edi
  void (__cdecl *pfHandler)(struct QTask_s *, struct GetParameterListContext_t *); // eax
  int eQTaskType; // ecx
  struct ParameterItemReference_s *ptHead; // ebp
  struct ParameterItemReference_s *ptNext; // eax
  bool v16; // zf
  char *zParameterName; // ebx
  int v18; // esi
  int v19; // edi
  struct ParameterListItem_s *v20; // edx
  int v21; // ecx
  int v22; // eax
  void (__cdecl *v23)(struct QTask_s *); // eax
  void (__cdecl *v24)(struct QTask_s *, void *); // eax
  struct QHashTable_s *v25; // edi
  unsigned int v26; // eax
  int v27; // eax
  int eParameterType; // ecx
  int eParentParameterType; // eax
  struct QHashTable_s *v30; // esi
  unsigned int v31; // eax
  int v32; // eax
  struct CallQueueItem_s *v33; // eax
  struct CallQueueItem_s *v34; // edx
  int v35; // ecx

  if ( !Level_isLegalTask )
  {
    LDebug_Error("Too few parameters in line %d of file '%s'", Level_nLinenumber, Level_zScriptfile);
    goto LABEL_3;
  }
  v3 = ptArgList;
  isQVM = ptArgList->isQVM;
  ++dword_834DD2C;
  if ( isQVM )
    nLinenumber = 0;
  else
    nLinenumber = (*ptArgList->aptExpression)->nLinenumber;
  Level_nLinenumber = nLinenumber;
  if ( isQVM )
  {
    igi2_frame.iID = 0;
    QVM_EvalArg(&igi2_frame.iID, 4, ptArgList, 0, 1);
    v6 = igi2_frame.iID;
  }
  else
  {
    v6 = Expression_EvalInt(*ptArgList->aptExpression);
  }
  igi2_frame.iID = v6;
  if ( Level_isDisableDefineQTaskIDInScript )
    igi2_frame.iID = -1;
  v7 = 3;
  if ( ptArgList->isQVM )
  {
    igi2_frame.zQTaskType[0] = 0;
    QVM_EvalArg(igi2_frame.zQTaskType, 100, ptArgList, 1, 3);
  }
  else
  {
    Expression_EvalString(ptArgList->aptExpression[1], igi2_frame.zQTaskType, 100);
  }
  if ( ptArgList->isQVM )
  {
    igi2_frame.zQTaskNote[0] = 0;
    QVM_EvalArg(igi2_frame.zQTaskNote, 64, ptArgList, 2, 3);
  }
  else
  {
    Expression_EvalString(ptArgList->aptExpression[2], igi2_frame.zQTaskNote, 64);
  }
  igi2_frame.iArg = 3;
  if ( Level_isFirstChild )
  {
    QTaskType = QTask_GetQTaskType(igi2_frame.zQTaskType);
    ChildFn = QTask_NewFirstChildFn((struct QTask_s *)pxData, QTaskType, nullptr);
    igi2_frame.ptQTask = ChildFn;
    Level_isFirstChild = 0;
  }
  else
  {
    v10 = QTask_GetQTaskType(igi2_frame.zQTaskType);
    igi2_frame.ptQTask = QTask_NewFn((struct QTask_s *)pxData, v10, nullptr);
    ChildFn = igi2_frame.ptQTask;
  }
  if ( !Level_ptRootQTask )
    Level_ptRootQTask = ChildFn;
  v11 = igi2_frame.iID;
  if ( igi2_frame.iID >= 0 )
  {
    Level_aisLevelQTaskAllocated[igi2_frame.iID] = 0;
    Level_DefineQTaskID(v11, ChildFn);
  }
  pfHandler = (void (__cdecl *)(struct QTask_s *, struct GetParameterListContext_t *))QTask_aatQTaskFinalEvent[ParameterList_eGetParameterListQTaskEvent][ChildFn->eQTaskType].pfHandler;
  if ( pfHandler )
  {
    pfHandler(ChildFn, &igi2_frame.tGetParameterListContext);
    igi2_frame.ptParameterList = igi2_frame.tGetParameterListContext.ptParameterList;
    if ( igi2_frame.tGetParameterListContext.ptParameterList )
    {
      igi2_frame.tParameterParseContext.nLinenumber = Level_nLinenumber;
      eQTaskType = ChildFn->eQTaskType;
      igi2_frame.tParameterParseContext.iArg = 3;
      ptHead = Level_atQTaskTypeParameterListReference[eQTaskType].tParameterReferenceList.ptHead;
      igi2_frame.tParameterParseContext.zScriptfile = Level_zScriptfile;
      igi2_frame.tParameterParseContext.ptArgumentList = ptArgList;
      ptNext = ptHead->ptNext;
      v16 = ptHead->ptNext == nullptr;
      Level_isLegalTask = 0;
      igi2_frame.ptTemp = ptNext;
      if ( !v16 )
      {
        do
        {
          zParameterName = ptHead->zParameterName;
          v18 = 0;
          if ( igi2_frame.ptParameterList->nParameters <= 0 )
          {
LABEL_32:
            v20 = nullptr;
          }
          else
          {
            v19 = 0;
            while ( _stricmp(igi2_frame.ptParameterList->ptParameterListItem[v19].zName, zParameterName) )
            {
              ++v18;
              ++v19;
              if ( v18 >= igi2_frame.ptParameterList->nParameters )
                goto LABEL_32;
            }
            v20 = &igi2_frame.ptParameterList->ptParameterListItem[v18];
            if ( v20 )
            {
              eParameterType = v20->eParameterType;
              while ( 2 )
              {
                eParentParameterType = ptHead->eParameterType;
                do
                {
                  if ( eParentParameterType == eParameterType )
                  {
                    igi2_frame.tParameterParseContext.ptParameterListItem = &igi2_frame.ptParameterList->ptParameterListItem[v18];
                    ParameterList_atParameterType[ptHead->eParameterType].apfQParameterEvent[ParameterList_eQParameterParseEvent](
                      (char *)igi2_frame.ptQTask + v20->nOffset,
                      &igi2_frame.tParameterParseContext);
                    v22 = igi2_frame.tParameterParseContext.iArg;
                    goto LABEL_34;
                  }
                  eParentParameterType = ParameterList_atParameterType[eParentParameterType].eParentParameterType;
                }
                while ( eParentParameterType != -1 );
                eParameterType = ParameterList_atParameterType[eParameterType].eParentParameterType;
                if ( eParameterType != -1 )
                  continue;
                break;
              }
            }
          }
          igi2_frame.tContext.iArg = igi2_frame.tParameterParseContext.iArg;
          igi2_frame.tContext.zScriptfile = igi2_frame.tParameterParseContext.zScriptfile;
          v21 = 19 * ptHead->eParameterType;
          igi2_frame.tContext.ptArgumentList = igi2_frame.tParameterParseContext.ptArgumentList;
          igi2_frame.tContext.ptParameterListItem = v20;
          igi2_frame.tContext.nLinenumber = igi2_frame.tParameterParseContext.nLinenumber;
          igi2_frame.tContext.nArguments = 1;
          (*((void (__cdecl **)(void *, struct ParameterGetNumberOfArgumentsContext_s *))&ParameterList_atParameterType[0].apfQParameterEvent[ParameterList_eQParameterGetNumberOfArgumentsEvent]
           + v21))(
            pxData,
            &igi2_frame.tContext);
          v22 = igi2_frame.tContext.nArguments + igi2_frame.iArg;
          igi2_frame.tParameterParseContext.iArg = igi2_frame.tContext.nArguments + igi2_frame.iArg;
LABEL_34:
          ptHead = igi2_frame.ptTemp;
          igi2_frame.iArg = v22;
          igi2_frame.ptTemp = igi2_frame.ptTemp->ptNext;
        }
        while ( igi2_frame.ptTemp );
        ChildFn = igi2_frame.ptQTask;
        v3 = ptArgList;
      }
      v7 = igi2_frame.iArg;
    }
  }
  Level_isLegalTask = 1;
  if ( igi2_frame.iID >= 0 )
  {
    v23 = (void (__cdecl *)(struct QTask_s *))QTask_aatQTaskFinalEvent[Level_eRegisterLevelScriptSymbolsEvent][ChildFn->eQTaskType].pfHandler;
    if ( v23 )
      v23(ChildFn);
  }
  v24 = (void (__cdecl *)(struct QTask_s *, void *))QTask_aatQTaskFinalEvent[ParameterList_eUpdateInternalDataQTaskEvent][ChildFn->eQTaskType].pfHandler;
  if ( v24 )
    v24(ChildFn, &unk_6B65C4);
  v25 = Symbol_ptSymbolHashTable;
  v26 = Symbol_ptSymbolHashTable->tPrivate.pfHashFunction(Symbol_ptSymbolHashTable->tPrivate.nHashTableSize, "Task_New");
  v27 = ((int  (__cdecl *)(struct QHashTable_s *, unsigned int, const void *))Symbol_ptSymbolHashTable->tPrivate.pfFindElement)(v25, v26, (const void *)("Task_New"));
  if ( !v27 || !*(_DWORD *)(v27 + 20) )
    goto LABEL_63;
  *(_DWORD *)(v27 + 24) = ChildFn;
  if ( v7 < v3->nArguments )
  {
    do
    {
      if ( v3->isQVM )
      {
        igi2_frame.ptTemp = nullptr;
        QVM_EvalArg(&igi2_frame.ptTemp, 4, v3, v7, 1);
      }
      else
      {
        Expression_EvalInt(v3->aptExpression[v7]);
      }
      ++v7;
    }
    while ( v7 < v3->nArguments );
    igi2_frame.iArg = v7;
  }
  v30 = Symbol_ptSymbolHashTable;
  v31 = Symbol_ptSymbolHashTable->tPrivate.pfHashFunction(Symbol_ptSymbolHashTable->tPrivate.nHashTableSize, "Task_New");
  v32 = ((int  (__cdecl *)(struct QHashTable_s *, unsigned int, const void *))Symbol_ptSymbolHashTable->tPrivate.pfFindElement)(v30, v31, (const void *)("Task_New"));
  if ( !v32 || !*(_DWORD *)(v32 + 20) )
  {
LABEL_63:
    LDebug_Error("Script_SetSymbolContext(): Symbol not found: %s", "Task_New");
LABEL_3:
    abort();
  }
  *(_DWORD *)(v32 + 24) = pxData;
  if ( !--dword_834DD2C )
  {
    v33 = CallQueue_ptFirstFreeItem;
    v34 = CallQueue_ptFirstFreeItem->ptNext;
    v35 = Level_eUpdateInternalDataAfterLoadEvent;
    CallQueue_ptFirstFreeItem->ptQTask = ChildFn;
    v33->uEvent.eQTaskEventNoContext = v35;
    v33->isNoContext = true;
    v33->pxContext = nullptr;
    v33->ptNext = nullptr;
    CallQueue_ptFirstFreeItem = v34;
    *Level_tCallQueue.pptLast = v33;
    Level_tCallQueue.pptLast = &v33->ptNext;
  }
  igi2_frame.tContext.nArguments = v7;
  *(double *)&igi2_frame.tContext.ptArgumentList = (double)igi2_frame.iArg;
  igi2_frame.tContext.nLinenumber = (int)&g_zInitialValue;
  qmemcpy(retstr, &igi2_frame.tContext, sizeof(struct Result_s));
  return retstr;
}

// source: h/1/level.c:3884  [anchor-callee]
void __cdecl Level_ValidateLevelExpression(struct LevelExpression_s *ptLevelExpression)
{
  int v1; // edx
  int nExpressionReference; // ecx
  struct ExpressionReference_s *atExpressionReference; // edi
  struct ExpressionReference_s *v4; // eax
  int v5; // esi
  struct MemPoolFreeItem_s *ptQTaskRef; // eax
  char *zCompiledExpression; // eax
  int v8; // esi
  struct QExpression_s *ptExpression; // eax

  v1 = 1;
  if ( ptLevelExpression->nExpressionReference > 0 )
  {
    nExpressionReference = ptLevelExpression->nExpressionReference;
    atExpressionReference = ptLevelExpression->atExpressionReference;
    v4 = ptLevelExpression->atExpressionReference;
    do
    {
      if ( !v4->ptQTaskRef->pxObject )
        v1 = 0;
      ++v4;
      --nExpressionReference;
    }
    while ( nExpressionReference );
    if ( !v1 )
    {
      v5 = 0;
      do
      {
        ptQTaskRef = (struct MemPoolFreeItem_s *)atExpressionReference->ptQTaskRef;
        if ( atExpressionReference->ptQTaskRef->ptNext )
          ptQTaskRef = (struct MemPoolFreeItem_s *)Node_Remove(ptQTaskRef);
        --QTask_tQTaskRefPool.nAllocatedBlocks;
        ptQTaskRef->ptNext = QTask_tQTaskRefPool.tMemPoolFreeList.ptHead;
        QTask_tQTaskRefPool.tMemPoolFreeList.ptHead = ptQTaskRef;
        ++v5;
        ++atExpressionReference;
      }
      while ( v5 < ptLevelExpression->nExpressionReference );
      zCompiledExpression = ptLevelExpression->zCompiledExpression;
      ptLevelExpression->nExpressionReference = 0;
      if ( zCompiledExpression )
      {
        v8 = *(_DWORD *)((unsigned int)(zCompiledExpression - 4) & 0xFFFFFFFC);
        --Mem_nCurrentAllocations;
        Node_Remove((_DWORD **)v8);
        memset(*(void **)(v8 + 8), 0xCDu, *(_DWORD *)(v8 + 16));
        free((void *)v8);
      }
      ptExpression = ptLevelExpression->ptExpression;
      ptLevelExpression->zCompiledExpression = nullptr;
      if ( ptExpression )
      {
        Expression_Delete(ptExpression);
        ptLevelExpression->ptExpression = nullptr;
      }
    }
  }
}

// source: h/1/level.c:3965  [anchor-strings]
char *__cdecl Level_LoadMTP(char *zName)
{
  int v1; // eax
  char v2; // cl
  char *result; // eax
  char zRootDir[64]; // [esp+0h] [ebp-40h] BYREF

  sprintf(zRootDir, (char *const)&stru_6A4CDC.tDebugConsoleLineList.ptMiddle, zName);
  v1 = 0;
  do
  {
    v2 = zRootDir[v1];
    MTP_zRootDir[v1++] = v2;
  }
  while ( v2 );
  result = (char *)MTP_Load("mission");
  Level_ptMTP = (struct MTP_s *)result;
  return result;
}

// source: h/1/level.c:3987  [size]
void __cdecl Level_FreeMTP()
{
  MTP_Free(Level_ptMTP);
}

// source: h/1/level.c:4001  [size]
struct MTP_s *__cdecl Level_SetMTP(struct MTP_s *ptMTP)
{
  Level_ptMTP = ptMTP;
  return ptMTP;
}

// source: h/1/level.c:4018  [anchor-callee]
struct QTask_s *__cdecl Level_LoadQTask(
        struct QTask_s *ptParent,
        char *zFilename,
        enum bool isFirstChild)
{
  struct ParameterListReference_s *v3; // esi
  struct QHashTable_s *v4; // esi
  unsigned int v5; // eax
  int v6; // eax
  struct Script_s *v7; // eax
  struct Script_s *v8; // esi

  v3 = Level_atQTaskTypeParameterListReference;
  do
    Level_ClearParameterListReference(v3++);
  while ( (int)v3 < 127888364 );
  v4 = Symbol_ptSymbolHashTable;
  v5 = Symbol_ptSymbolHashTable->tPrivate.pfHashFunction(Symbol_ptSymbolHashTable->tPrivate.nHashTableSize, "Task_New");
  v6 = ((int  (__cdecl *)(struct QHashTable_s *, unsigned int, const void *))Symbol_ptSymbolHashTable->tPrivate.pfFindElement)(v4, v5, (const void *)("Task_New"));
  if ( !v6 || !*(_DWORD *)(v6 + 20) )
  {
    LDebug_Error("Script_SetSymbolContext(): Symbol not found: %s", "Task_New");
    abort();
  }
  *(_DWORD *)(v6 + 24) = ptParent;
  v7 = Script_New(zFilename);
  v8 = v7;
  if ( !v7 )
    return nullptr;
  Level_tCallQueue.pptLast = (struct CallQueueItem_s **)&Level_tCallQueue;
  Level_tCallQueue.ptFirst = nullptr;
  Level_zScriptfile = zFilename;
  Level_isLegalTask = 1;
  Level_nLinenumber = 0;
  Level_isFirstChild = isFirstChild;
  Level_ptRootQTask = nullptr;
  Script_Execute(v7);
  Script_Delete(v8);
  CallQueue_CallHandlersRecursively(&Level_tCallQueue);
  return Level_ptRootQTask;
}

// source: h/1/level.c:4057  [anchor-hash]
void __cdecl Level_LoadObjectFile(char *zFilename, int nFrequency)
{
  struct QLevelQTask_s *v2; // ecx

  memset(Level_aisLevelQTaskAllocated, 0, sizeof(Level_aisLevelQTaskAllocated));
  Level_LoadQTask(&Level_ptQLevelQTask->tQTask, zFilename, false);
  v2 = Level_ptQLevelQTask;
  Level_ptQLevelQTask->nTime = 0;
  v2->nTicks = 0;
  v2->nFrequency = nFrequency;
  v2->nMilisecondsPerTick = 1000 / nFrequency;
}

// source: h/1/level.c:4104  [anchor-hash]
char *__cdecl Level_LoadDynamicObjectFile(char *zFilename, int nFrequency)
{
  struct QLevelQTask_s *v4; // ecx

  if ( !Level_LoadQTask(Level_ptDynamicQTask, zFilename, false) )
  {
    LDebug_Error("Level_Load(): Couldn't load script: %s", zFilename);
    abort();
  }
  v4 = Level_ptQLevelQTask;
  Level_ptQLevelQTask->nTime = 0;
  v4->nTicks = 0;
  v4->nFrequency = nFrequency;
  v4->nMilisecondsPerTick = 1000 / nFrequency;
  return (char *)(1000 / nFrequency);
}

// source: h/1/level.c:4135  [anchor-strings]
char *__cdecl Level_LoadObjects(char *zName, int nFrequency)
{
  struct QLevelQTask_s *v3; // ecx
  char zScript[260]; // [esp+8h] [ebp-104h] BYREF

  sprintf(zScript, "%s/objects.qsc", zName);
  memset(Level_aisLevelQTaskAllocated, 0, sizeof(Level_aisLevelQTaskAllocated));
  Level_LoadQTask(&Level_ptQLevelQTask->tQTask, zScript, false);
  v3 = Level_ptQLevelQTask;
  Level_ptQLevelQTask->nTime = 0;
  v3->nTicks = 0;
  v3->nFrequency = nFrequency;
  v3->nMilisecondsPerTick = 1000 / nFrequency;
  return (char *)(1000 / nFrequency);
}

// source: h/1/level.c:4152  [size]
void __cdecl Level_SetLoadContext(
        char *zScript,
        enum bool isLegalTask,
        int nLineNumber,
        enum bool isFirstChild)
{
  Level_zScriptfile = zScript;
  Level_isLegalTask = isLegalTask;
  Level_nLinenumber = nLineNumber;
  Level_isFirstChild = isFirstChild;
  Level_ptRootQTask = nullptr;
}

// source: h/1/level.c:4169  [anchor-hash]
void __cdecl Level_FreeObjects()
{
  if ( Level_ptQLevelQTask )
    QTask_DeleteChildren(&Level_ptQLevelQTask->tQTask);
  memset(Level_aisLevelQTaskAllocated, 0, sizeof(Level_aisLevelQTaskAllocated));
}

// source: h/1/level.c:4195  [anchor-hash]
void __cdecl Level_FreeDynamicObjects()
{
  int i; // eax
  struct QReference_s *v1; // ecx

  if ( Level_ptDynamicQTask )
    QTask_DeleteChildren(Level_ptDynamicQTask);
  for ( i = 0; i < 4096; ++i )
  {
    v1 = Level_atLevelQTaskID[i];
    if ( v1 )
    {
      if ( !v1->pxObject )
        Level_aisLevelQTaskAllocated[i] = 0;
    }
  }
}

// source: h/1/level.c:4224  [size]
struct QTask_s *__cdecl Level_GetStaticQTask()
{
  return Level_ptStaticQTask;
}

// source: h/1/level.c:4237  [size]
struct QTask_s *__cdecl Level_GetDynamicQTask()
{
  return Level_ptDynamicQTask;
}

// source: h/1/level.c:4250  [size]
struct QTask_s *__cdecl Level_GetIdleQTask()
{
  return Level_ptIdleQTask;
}

// source: h/1/level.c:4263  [size]
struct QTask_s *__cdecl Level_GetCameraBaseQTask()
{
  return Level_ptCameraBaseQTask;
}

// source: h/1/level.c:4276  [size]
int __cdecl Level_GetParameterTypePushButton()
{
  return Level_eParameterTypePushButton;
}

// source: h/1/level.c:4289  [size]
int __cdecl Level_GetParameterTypeDropDownCombo()
{
  return Level_eParameterTypeDropDownCombo;
}

// source: h/1/level.c:4302  [size]
int __cdecl Level_GetParameterTypeScriptFile()
{
  return Level_eParameterTypeScriptFile;
}

// source: h/1/level.c:4315  [size]
int __cdecl Level_GetParameterTypeBitfield()
{
  return Level_eParameterTypeBitfield;
}

// source: h/1/level.c:4328  [size]
int __cdecl Level_GetParameterTypeQuat32()
{
  return Level_eParameterTypeQuat32;
}

// source: h/1/level.c:4343  [size]
int __cdecl Level_GetParameterTypeAngle()
{
  return Level_eParameterTypeAngle;
}

// source: h/1/level.c:4358  [size]
int __cdecl Level_GetParameterTypeDegrees()
{
  return Level_eParameterTypeDegrees;
}

// source: h/1/level.c:4373  [size]
int __cdecl Level_GetParameterTypeRGB()
{
  return Level_eParameterTypeRGB;
}

// source: h/1/level.c:4388  [size]
int __cdecl Level_GetParameterTypeReal32()
{
  return Level_eParameterTypeReal32;
}

// source: h/1/level.c:4403  [size]
int __cdecl Level_GetParameterTypeReal32x3()
{
  return Level_eParameterTypeReal32x3;
}

// source: h/1/level.c:4418  [size]
int __cdecl Level_GetParameterTypeReal32x9()
{
  return Level_eParameterTypeReal32x9;
}

// source: h/1/level.c:4433  [size]
int __cdecl Level_GetParameterTypeReal32x9Exact()
{
  return Level_eParameterTypeReal32x9Exact;
}

// source: h/1/level.c:4448  [size]
int __cdecl Level_GetParameterTypeReal64()
{
  return Level_eParameterTypeReal64;
}

// source: h/1/level.c:4463  [size]
int __cdecl Level_GetParameterTypeReal64x3()
{
  return Level_eParameterTypeReal64x3;
}

// source: h/1/level.c:4478  [size]
int __cdecl Level_GetParameterTypeint32()
{
  return Level_eParameterTypeInt32;
}

// source: h/1/level.c:4493  [size]
int __cdecl Level_GetParameterTypeint16()
{
  return Level_eParameterTypeInt16;
}

// source: h/1/level.c:4508  [size]
int __cdecl Level_GetParameterTypeQTaskNote()
{
  return Level_eParameterTypeQTaskNote;
}

// source: h/1/level.c:4523  [size]
int __cdecl Level_GetParameterTypeVarString()
{
  return Level_eParameterTypeVarString;
}

// source: h/1/level.c:4538  [size]
int __cdecl Level_GetParameterTypeString16()
{
  return Level_eParameterTypeString16;
}

// source: h/1/level.c:4554  [size]
int __cdecl Level_GetParameterTypeString32()
{
  return Level_eParameterTypeString32;
}

// source: h/1/level.c:4570  [size]
int __cdecl Level_GetParameterTypeString256()
{
  return Level_eParameterTypeString256;
}

// source: h/1/level.c:4586  [size]
int __cdecl Level_GetParameterTypeExpression()
{
  return Level_eParameterTypeLevelExpression;
}

// source: h/1/level.c:4601  [size]
int __cdecl Level_GetParameterTypebool8()
{
  return Level_eParameterTypebool8;
}

// source: h/1/level.c:4616  [size]
int __cdecl Level_GetParameterTypeObjectPos()
{
  return Level_eParameterTypeObjectPos;
}

// source: h/1/level.c:4631  [size]
int __cdecl Level_GetParameterTypeGraph()
{
  return Level_eParameterTypeGraph;
}

// source: h/1/level.c:4646  [size]
int __cdecl Level_GetParameterTypeGraphEnvelope()
{
  return Level_eParameterTypeGraphEnvelope;
}

// source: h/1/level.c:4661  [size]
int __cdecl Level_GetParameterTypePitchGraph()
{
  return Level_eParameterTypePitchGraph;
}

// source: h/1/level.c:4676  [size]
enum bool __cdecl Level_IsLevelQTaskIDAllocated(int iQTaskID)
{
  return Level_aisLevelQTaskAllocated[iQTaskID];
}

// source: h/1/level.c:4692  [anchor-hash]
struct QTask_s *__cdecl Level_GetQTaskFromLevelQTaskID(int iQTaskRef)
{
  struct QReference_s *v1; // eax

  if ( (unsigned int)iQTaskRef < 0x1000 && (v1 = Level_atLevelQTaskID[iQTaskRef]) != nullptr )
    return (struct QTask_s *)v1->pxObject;
  else
    return nullptr;
}

// source: h/1/level.c:4720  [anchor-callee]
int __cdecl Level_GetLevelQTaskIDFromQTask(struct QTask_s *ptQTask)
{
  int result; // eax
  struct QReference_s *v2; // ecx

  result = 0;
  while ( 1 )
  {
    v2 = Level_atLevelQTaskID[result];
    if ( v2 )
    {
      if ( v2->pxObject == ptQTask )
        break;
    }
    if ( ++result >= 4096 )
      return -1;
  }
  return result;
}

// source: h/1/level.c:4748  [anchor-mhash]
int __cdecl Level_GetLevelQTaskIDFromQTaskAllocated(struct QTask_s *ptQTask)
{
  int result; // eax
  struct QReference_s *v2; // ecx

  result = 0;
  while ( 1 )
  {
    v2 = Level_atLevelQTaskID[result];
    if ( v2 )
    {
      if ( v2->pxObject == ptQTask )
        break;
    }
    if ( ++result >= 4096 )
      return -1;
  }
  if ( result < 0 || !Level_aisLevelQTaskAllocated[result] )
    return -1;
  return result;
}

// source: h/1/level.c:4771  [size]
int __cdecl Level_GetTime()
{
  return Level_ptQLevelQTask->nTime;
}

// source: h/1/level.c:4788  [size]
int __cdecl Level_GetTicks()
{
  return Level_ptQLevelQTask->nTicks;
}

// source: h/1/level.c:4805  [size]
int __cdecl Level_GetMilisecondsPerTick()
{
  return Level_ptQLevelQTask->nMilisecondsPerTick;
}

// source: h/1/level.c:4822  [anchor-strings]
void __cdecl Level_DefineQTaskID(int iQTaskID, struct QTask_s *ptQTask)
{
  int v2; // esi
  struct QReference_s *v3; // eax
  struct QReference_s *v4; // eax
  struct QReference_s *v5; // eax

  v2 = 0;
  while ( 1 )
  {
    v3 = Level_atLevelQTaskID[v2];
    if ( v3 )
    {
      if ( v3->pxObject == ptQTask )
        break;
    }
    if ( ++v2 >= 4096 )
      goto LABEL_10;
  }
  if ( v2 >= 0 )
  {
    if ( Level_aisLevelQTaskAllocated[v2] )
      return;
    v4 = Level_atLevelQTaskID[v2];
    if ( v4 )
    {
      QReference_Delete(v4, &QTask_tQTaskRefPool);
      Level_atLevelQTaskID[v2] = nullptr;
    }
  }
LABEL_10:
  if ( Level_aisLevelQTaskAllocated[iQTaskID] && Level_atLevelQTaskID[iQTaskID]->pxObject )
  {
    LDebug_Error("LevelQTaskID %d already defined", iQTaskID);
    abort();
  }
  v5 = Level_atLevelQTaskID[iQTaskID];
  if ( v5 )
  {
    QReference_Delete(v5, &QTask_tQTaskRefPool);
    Level_atLevelQTaskID[iQTaskID] = nullptr;
  }
  Level_atLevelQTaskID[iQTaskID] = QTask_NewQTaskRef(ptQTask);
  Level_aisLevelQTaskAllocated[iQTaskID] = 1;
}

// source: h/1/level.c:4863  [size]
int __cdecl Level_ClearQTaskID(int iQTaskID)
{
  Level_aisLevelQTaskAllocated[iQTaskID] = 0;
  return iQTaskID;
}

// source: h/1/level.c:4896  [anchor-caller]
int __cdecl Level_AllocQTaskID(
        struct QTask_s *ptQTask,
        enum bool isUseRange,
        int iMinID,
        int iMaxID)
{
  int i; // edi
  struct LevelQTaskRange_s *ptNext; // eax
  struct LevelQTaskRange_s *ptHead; // ecx

  if ( isUseRange == false )
  {
    iMinID = 0;
    iMaxID = 4096;
  }
  for ( i = iMaxID - 1; i >= iMinID; --i )
  {
    if ( !Level_aisLevelQTaskAllocated[i] )
    {
      if ( isUseRange
        || (ptNext = Level_tQTaskRangeList.ptHead->ptNext,
            ptHead = Level_tQTaskRangeList.ptHead,
            !Level_tQTaskRangeList.ptHead->ptNext) )
      {
LABEL_10:
        Level_DefineQTaskID(i, ptQTask);
        return i;
      }
      while ( i < ptHead->nMinQTaskID || i >= ptHead->nMaxQTaskID )
      {
        ptHead = ptNext;
        ptNext = ptNext->ptNext;
        if ( !ptNext )
          goto LABEL_10;
      }
    }
  }
  return -1;
}

// source: h/1/level.c:4928  [anchor-mhash]
enum bool __cdecl Level_IsLevelQTaskIDValidForQTask(int nQTaskID, struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { enum bool isForceRange; };
    struct { char igi2_o1[4]; struct GetLevelQTaskRangeContext_s tGetLevelQTaskRangeContext; };
    char igi2_extent[76];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *v2; // esi
  int nRanges; // edx
  void (__cdecl *pfHandler)(struct QTask_s *, struct GetLevelQTaskRangeContext_s *); // eax
  int v5; // eax
  struct LevelQTaskRange_s *v6; // ecx
  struct LevelQTaskRange_s *ptHead; // ecx
  struct LevelQTaskRange_s *ptNext; // eax

  igi2_frame.isForceRange = false;
  memset(&igi2_frame.tGetLevelQTaskRangeContext, 0, sizeof(igi2_frame.tGetLevelQTaskRangeContext));
  v2 = ptQTask;
  if ( ptQTask )
  {
    nRanges = igi2_frame.tGetLevelQTaskRangeContext.nRanges;
    do
    {
      pfHandler = (void (__cdecl *)(struct QTask_s *, struct GetLevelQTaskRangeContext_s *))QTask_aatQTaskFinalEvent[Level_eGetLevelQTaskRangeQTaskEvent][v2->eQTaskType].pfHandler;
      if ( pfHandler )
      {
        pfHandler(v2, &igi2_frame.tGetLevelQTaskRangeContext);
        nRanges = igi2_frame.tGetLevelQTaskRangeContext.nRanges;
      }
      if ( nRanges )
      {
        v5 = 0;
        igi2_frame.isForceRange = true;
        if ( nRanges > 0 )
        {
          do
          {
            v6 = igi2_frame.tGetLevelQTaskRangeContext.aptLevelQTaskRange[v5];
            if ( nQTaskID >= v6->nMinQTaskID && nQTaskID < v6->nMaxQTaskID )
              return true;
          }
          while ( ++v5 < nRanges );
        }
        memset(&igi2_frame.tGetLevelQTaskRangeContext, 0, sizeof(igi2_frame.tGetLevelQTaskRangeContext));
        nRanges = igi2_frame.tGetLevelQTaskRangeContext.nRanges;
      }
      v2 = v2->ptParent;
    }
    while ( v2 );
    if ( igi2_frame.isForceRange )
      return false;
  }
  ptHead = Level_tQTaskRangeList.ptHead;
  ptNext = Level_tQTaskRangeList.ptHead->ptNext;
  if ( !Level_tQTaskRangeList.ptHead->ptNext )
    return true;
  while ( nQTaskID < ptHead->nMinQTaskID || nQTaskID >= ptHead->nMaxQTaskID )
  {
    ptHead = ptNext;
    ptNext = ptNext->ptNext;
    if ( !ptNext )
      return true;
  }
  return false;
}

// source: h/1/level.c:4986  [anchor-callee]
int __cdecl Level_AutoAllocateQTaskID(struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { enum bool isForceRange; };
    struct { char igi2_o1[4]; struct GetLevelQTaskRangeContext_s tGetLevelQTaskRangeContext; };
    char igi2_extent[76];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *v1; // ebx
  void (__cdecl *pfHandler)(struct QTask_s *, struct GetLevelQTaskRangeContext_s *); // eax
  int v3; // esi
  struct LevelQTaskRange_s *v4; // eax
  int nMinQTaskID; // ecx
  int v6; // edi
  struct LevelQTaskRange_s *ptNext; // eax
  struct LevelQTaskRange_s *ptHead; // ecx

  v1 = ptQTask;
  igi2_frame.isForceRange = false;
  memset(&igi2_frame.tGetLevelQTaskRangeContext, 0, sizeof(igi2_frame.tGetLevelQTaskRangeContext));
  if ( ptQTask )
  {
    do
    {
      pfHandler = (void (__cdecl *)(struct QTask_s *, struct GetLevelQTaskRangeContext_s *))QTask_aatQTaskFinalEvent[Level_eGetLevelQTaskRangeQTaskEvent][v1->eQTaskType].pfHandler;
      if ( pfHandler )
        pfHandler(v1, &igi2_frame.tGetLevelQTaskRangeContext);
      if ( igi2_frame.tGetLevelQTaskRangeContext.nRanges )
      {
        v3 = 0;
        for ( igi2_frame.isForceRange = true; v3 < igi2_frame.tGetLevelQTaskRangeContext.nRanges; ++v3 )
        {
          v4 = igi2_frame.tGetLevelQTaskRangeContext.aptLevelQTaskRange[v3];
          nMinQTaskID = v4->nMinQTaskID;
          v6 = v4->nMaxQTaskID - 1;
          if ( v6 >= nMinQTaskID )
          {
            while ( Level_aisLevelQTaskAllocated[v6] )
            {
              if ( --v6 < nMinQTaskID )
                goto LABEL_11;
            }
            Level_DefineQTaskID(v6, ptQTask);
            if ( v6 > 0 )
              return v6;
          }
LABEL_11:
          ;
        }
        memset(&igi2_frame.tGetLevelQTaskRangeContext, 0, sizeof(igi2_frame.tGetLevelQTaskRangeContext));
      }
      v1 = v1->ptParent;
    }
    while ( v1 );
    if ( igi2_frame.isForceRange )
      return -1;
    v1 = ptQTask;
  }
  v6 = 4095;
  while ( Level_aisLevelQTaskAllocated[v6] )
  {
LABEL_24:
    if ( --v6 < 0 )
      return -1;
  }
  ptNext = Level_tQTaskRangeList.ptHead->ptNext;
  ptHead = Level_tQTaskRangeList.ptHead;
  if ( Level_tQTaskRangeList.ptHead->ptNext )
  {
    while ( v6 < ptHead->nMinQTaskID || v6 >= ptHead->nMaxQTaskID )
    {
      ptHead = ptNext;
      ptNext = ptNext->ptNext;
      if ( !ptNext )
        goto LABEL_22;
    }
    goto LABEL_24;
  }
LABEL_22:
  Level_DefineQTaskID(v6, v1);
  return v6;
}

// source: h/1/level.c:5040  [anchor-callee]
void __cdecl Level_ClearQTaskIDRecursive(struct QTask_s *ptQTask)
{
  int v1; // eax
  struct QReference_s *v2; // ecx
  struct QTask_s *ptHead; // esi

  v1 = 0;
  while ( 1 )
  {
    v2 = Level_atLevelQTaskID[v1];
    if ( v2 )
    {
      if ( v2->pxObject == ptQTask )
        break;
    }
    if ( ++v1 >= 4096 )
      goto LABEL_8;
  }
  if ( v1 >= 0 )
    Level_aisLevelQTaskAllocated[v1] = 0;
LABEL_8:
  ptHead = ptQTask->tQTaskChildren.ptHead;
  if ( ptHead->ptNext && ptHead )
  {
    do
    {
      Level_ClearQTaskIDRecursive(ptHead);
      ptHead = ptHead->ptNext;
    }
    while ( ptHead && ptHead->ptNext );
  }
}

// source: h/1/level.c:5089  [size]
unsigned __int16 __cdecl Level_GetStaticQTaskType()
{
  return Level_eStaticQTaskType;
}

// source: h/1/level.c:5102  [size]
unsigned __int16 __cdecl Level_GetDynamicQTaskType()
{
  return Level_eDynamicQTaskType;
}

// source: h/1/level.c:5115  [size]
unsigned __int16 __cdecl Level_GetLevelQTaskType()
{
  return Level_eLevelQTaskType;
}

// source: h/1/level.c:5128  [size]
unsigned __int16 __cdecl Level_GetIdleQTaskType()
{
  return Level_eIdleQTaskType;
}

// source: h/1/level.c:5141  [size]
unsigned __int16 __cdecl Level_GetCameraBaseQTaskType()
{
  return Level_eCameraBaseQTaskType;
}

// source: h/1/level.c:5154  [size]
void __cdecl Level_SetDynamicQTaskPauseMode(enum bool isPaused)
{
  Level_isDynamicQTaskPaused = isPaused;
}

// source: h/1/level.c:5167  [size]
enum bool __cdecl Level_GetDynamicQTaskPauseMode()
{
  return Level_isDynamicQTaskPaused;
}

// source: h/1/level.c:5180  [size]
void __cdecl Level_SetDynamicQTaskActivityMode(enum bool isActivity)
{
  Level_isDynamicQTaskActive = isActivity;
}

// source: h/1/level.c:5193  [anchor-hash]
enum bool __cdecl Level_DynamicQTaskActive()
{
  return Level_isDynamicQTaskActive || !Level_isDynamicQTaskPaused;
}

// source: h/1/level.c:5206  [anchor-hash]
char *__cdecl Level_GetQTaskNote(struct QTask_s *ptQTask)
{
  struct QTaskNote_s *QTaskNoteNode; // eax

  QTaskNoteNode = Level_GetQTaskNoteNode(ptQTask);
  if ( QTaskNoteNode )
    return QTaskNoteNode->zString;
  else
    return (char *)&g_zInitialValue;
}

// source: h/1/level.c:5224  [size]
void __cdecl Level_SetQTaskNote(struct QTask_s *ptQTask, char *zString)
{
  ;
}

// source: h/1/level.c:5255  [size]
void __cdecl Level_DeleteQTaskNote(struct QTask_s *ptQTask)
{
  ;
}

// source: h/1/level.c:5277  [size]
__int16 __cdecl Level_GetPrintQTaskInfoQTaskEvent()
{
  return Level_ePrintQTaskInfoQTaskEvent;
}

// source: h/1/level.c:5292  [size]
__int16 __cdecl Level_GetUniqueQTaskNameEvent()
{
  return Level_eGetUniqueQTaskNameEvent;
}

// source: h/1/level.c:5307  [size]
int __cdecl Level_GetRegisterLevelScriptSymbolsEvent()
{
  return Level_eRegisterLevelScriptSymbolsEvent;
}

// source: h/1/level.c:5322  [size]
int __cdecl Level_GetRemoveLevelScriptSymbolsEvent()
{
  return Level_eRemoveLevelScriptSymbolsEvent;
}

// source: h/1/level.c:5337  [size]
int __cdecl Level_GetUpdateInternalDataAfterLoadEvent()
{
  return Level_eUpdateInternalDataAfterLoadEvent;
}

// source: h/1/level.c:5352  [anchor-hash]
int __cdecl Level_GetUniqueQTaskID()
{
  int result; // eax
  struct QReference_s *v1; // ecx

  for ( result = 0; (unsigned int)result < 0x1000; ++result )
  {
    v1 = Level_atLevelQTaskID[result];
    if ( !v1 || !v1->pxObject )
      break;
  }
  return result;
}

// source: h/1/level.c:5374  [anchor-callee]
void __cdecl Level_GetUniqueQTaskNameFromTask(char *zUniqueQTaskName, struct QTask_s *ptQTask)
{
  unsigned __int16 eQTaskType; // ax
  void (__cdecl *pfHandler)(struct QTask_s *, struct GetUniqueQTaskNameContext_s *); // ecx
  int v4; // edx
  struct QReference_s *v5; // ecx
  char *QTaskTypeName; // eax
  struct GetUniqueQTaskNameContext_s tGetUniqueQTaskNameContext; // [esp+0h] [ebp-40h] BYREF

  eQTaskType = ptQTask->eQTaskType;
  pfHandler = (void (__cdecl *)(struct QTask_s *, struct GetUniqueQTaskNameContext_s *))QTask_aatQTaskFinalEvent[Level_eGetUniqueQTaskNameEvent][eQTaskType].pfHandler;
  if ( pfHandler )
  {
    pfHandler(ptQTask, &tGetUniqueQTaskNameContext);
    strcpy(zUniqueQTaskName, tGetUniqueQTaskNameContext.zUniqueQTaskName);
  }
  else
  {
    v4 = 0;
    while ( 1 )
    {
      v5 = Level_atLevelQTaskID[v4];
      if ( v5 )
      {
        if ( v5->pxObject == ptQTask )
          break;
      }
      if ( ++v4 >= 4096 )
      {
        v4 = -1;
        break;
      }
    }
    QTaskTypeName = QTask_GetQTaskTypeName(eQTaskType);
    sprintf(zUniqueQTaskName, "%s_%d", QTaskTypeName, v4);
  }
}

// source: h/1/level.c:5410  [anchor-hash]
struct QTask_s *__cdecl Level_GetQTaskFromUniqueQTaskName(char *zUniqueQTaskName)
{
  char *v1; // ecx
  char v2; // al
  unsigned int v3; // eax
  struct QReference_s *v4; // eax

  v1 = &zUniqueQTaskName[strlen(zUniqueQTaskName) - 1];
  v2 = *v1;
  if ( *v1 == 95 )
  {
LABEL_6:
    v3 = atoi(v1 + 1);
    if ( v3 < 0x1000 )
    {
      v4 = Level_atLevelQTaskID[v3];
      if ( v4 )
        return (struct QTask_s *)v4->pxObject;
    }
  }
  else
  {
    while ( v1 != zUniqueQTaskName && v2 >= 48 && v2 <= 57 )
    {
      v2 = *--v1;
      if ( v2 == 95 )
        goto LABEL_6;
    }
  }
  return nullptr;
}

// source: h/1/level.c:5451  [anchor-hash]
struct LevelExpression_s *__cdecl Level_InitLevelExpression(
        struct LevelExpression_s *ptLevelExpression)
{
  ptLevelExpression->zExpression = nullptr;
  ptLevelExpression->zCompiledExpression = nullptr;
  ptLevelExpression->ptExpression = nullptr;
  ptLevelExpression->nExpressionReference = 0;
  return ptLevelExpression;
}

// source: h/1/level.c:5467  [anchor-hash]
void __cdecl Level_DeinitLevelExpression(struct LevelExpression_s *ptLevelExpression)
{
  int v1; // edi
  struct ExpressionReference_s *atExpressionReference; // ebx
  struct MemPoolFreeItem_s *ptQTaskRef; // eax
  char *zExpression; // eax
  bool v5; // zf
  int v6; // ebx
  char *zCompiledExpression; // eax
  int v8; // ebx

  v1 = 0;
  if ( ptLevelExpression->nExpressionReference > 0 )
  {
    atExpressionReference = ptLevelExpression->atExpressionReference;
    do
    {
      ptQTaskRef = (struct MemPoolFreeItem_s *)atExpressionReference->ptQTaskRef;
      if ( atExpressionReference->ptQTaskRef->ptNext )
        ptQTaskRef = (struct MemPoolFreeItem_s *)Node_Remove(ptQTaskRef);
      --QTask_tQTaskRefPool.nAllocatedBlocks;
      ptQTaskRef->ptNext = QTask_tQTaskRefPool.tMemPoolFreeList.ptHead;
      QTask_tQTaskRefPool.tMemPoolFreeList.ptHead = ptQTaskRef;
      ++v1;
      ++atExpressionReference;
    }
    while ( v1 < ptLevelExpression->nExpressionReference );
  }
  zExpression = ptLevelExpression->zExpression;
  v5 = ptLevelExpression->zExpression == nullptr;
  ptLevelExpression->nExpressionReference = 0;
  if ( !v5 )
  {
    --Mem_nCurrentAllocations;
    v6 = *(_DWORD *)((unsigned int)(zExpression - 4) & 0xFFFFFFFC);
    Node_Remove((_DWORD **)v6);
    memset(*(void **)(v6 + 8), 0xCDu, *(_DWORD *)(v6 + 16));
    free((void *)v6);
    ptLevelExpression->zExpression = nullptr;
  }
  zCompiledExpression = ptLevelExpression->zCompiledExpression;
  if ( zCompiledExpression )
  {
    --Mem_nCurrentAllocations;
    v8 = *(_DWORD *)((unsigned int)(zCompiledExpression - 4) & 0xFFFFFFFC);
    Node_Remove((_DWORD **)v8);
    memset(*(void **)(v8 + 8), 0xCDu, *(_DWORD *)(v8 + 16));
    free((void *)v8);
    ptLevelExpression->zCompiledExpression = nullptr;
  }
  if ( ptLevelExpression->ptExpression )
  {
    Expression_Delete(ptLevelExpression->ptExpression);
    ptLevelExpression->ptExpression = nullptr;
  }
}

// source: h/1/level.c:5526  [anchor-hash]
struct QTask_s *__cdecl Level_RegisterScriptDependency(
        struct LevelExpression_s *ptLevelExpression,
        struct QTask_s *ptQTask,
        struct QTask_s *ptBaseQTask)
{
  int nExpressionReference; // edi
  int v4; // ecx
  struct ExpressionReference_s *atExpressionReference; // edx

  nExpressionReference = ptLevelExpression->nExpressionReference;
  v4 = 0;
  if ( nExpressionReference <= 0 )
  {
LABEL_5:
    if ( nExpressionReference != 16 )
    {
      ptQTask = (struct QTask_s *)QTask_NewQTaskRef(ptQTask);
      ptLevelExpression->atExpressionReference[ptLevelExpression->nExpressionReference++].ptQTaskRef = (struct QReference_s *)ptQTask;
    }
  }
  else
  {
    atExpressionReference = ptLevelExpression->atExpressionReference;
    while ( atExpressionReference->ptQTaskRef->pxObject != ptQTask )
    {
      ++v4;
      ++atExpressionReference;
      if ( v4 >= ptLevelExpression->nExpressionReference )
        goto LABEL_5;
    }
  }
  return ptQTask;
}

// source: h/1/level.c:5608  [anchor-strings]
void __cdecl Level_CompileLevelExpression(struct LevelExpression_s *ptLevelExpression, struct QTask_s *ptQTask)
{
  #pragma pack(push, 1)
  union
  {
    struct { char *zSource; };
    struct { char igi2_o1[4]; char *zTarget; };
    struct { char igi2_o2[8]; char zSymbol[128]; };
    struct { char igi2_o3[136]; char zName[128]; };
    struct { char igi2_o4[264]; char zMember[128]; };
    struct { char igi2_o5[392]; char zTemp[1028]; };
    char igi2_extent[1420];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  char *zExpression; // ebx
  int nExpressionReference; // eax
  int v4; // edi
  struct ExpressionReference_s *atExpressionReference; // esi
  struct MemPoolFreeItem_s *ptQTaskRef; // eax
  int TargetQTaskIDFromSymbol; // eax
  struct QReference_s *v8; // eax
  struct QTask_s *pxObject; // eax
  int v10; // esi
  int v11; // ecx
  struct ExpressionReference_s *v12; // edx
  int v13; // eax
  char v14; // cl
  char *v15; // esi
  int v16; // eax
  char *v17; // ecx
  char *zCompiledExpression; // eax
  int v19; // esi
  char *v20; // edx

  zExpression = ptLevelExpression->zExpression;
  igi2_frame.zTarget = igi2_frame.zTemp;
  nExpressionReference = ptLevelExpression->nExpressionReference;
  v4 = 0;
  igi2_frame.zSource = zExpression;
  igi2_frame.zTemp[0] = 0;
  if ( nExpressionReference > 0 )
  {
    atExpressionReference = ptLevelExpression->atExpressionReference;
    do
    {
      ptQTaskRef = (struct MemPoolFreeItem_s *)atExpressionReference->ptQTaskRef;
      if ( atExpressionReference->ptQTaskRef->ptNext )
        ptQTaskRef = (struct MemPoolFreeItem_s *)Node_Remove(ptQTaskRef);
      --QTask_tQTaskRefPool.nAllocatedBlocks;
      ptQTaskRef->ptNext = QTask_tQTaskRefPool.tMemPoolFreeList.ptHead;
      QTask_tQTaskRefPool.tMemPoolFreeList.ptHead = ptQTaskRef;
      atExpressionReference->ptQTaskRef = nullptr;
      ++v4;
      ++atExpressionReference;
    }
    while ( v4 < ptLevelExpression->nExpressionReference );
  }
  if ( ptLevelExpression->ptExpression )
    Expression_Delete(ptLevelExpression->ptExpression);
  ptLevelExpression->nExpressionReference = 0;
  if ( zExpression )
  {
    while ( 1 )
    {
      if ( !*zExpression )
        goto LABEL_43;
      if ( String_GetWordEx((int)zExpression, igi2_frame.zSymbol, &igi2_frame.zSource, 127, 0) )
      {
        TargetQTaskIDFromSymbol = Level_GetTargetQTaskIDFromSymbol(igi2_frame.zSymbol);
        if ( TargetQTaskIDFromSymbol >= 0 && (igi2_frame.zSymbol[0] < 48 || igi2_frame.zSymbol[0] > 57) && TargetQTaskIDFromSymbol < 4096 )
        {
          v8 = Level_atLevelQTaskID[TargetQTaskIDFromSymbol];
          if ( v8 )
          {
            pxObject = (struct QTask_s *)v8->pxObject;
            if ( pxObject )
            {
              v10 = ptLevelExpression->nExpressionReference;
              v11 = 0;
              if ( v10 <= 0 )
              {
LABEL_21:
                if ( v10 != 16 )
                  ptLevelExpression->atExpressionReference[ptLevelExpression->nExpressionReference++].ptQTaskRef = QTask_NewQTaskRef(pxObject);
              }
              else
              {
                v12 = ptLevelExpression->atExpressionReference;
                while ( v12->ptQTaskRef->pxObject != pxObject )
                {
                  ++v11;
                  ++v12;
                  if ( v11 >= ptLevelExpression->nExpressionReference )
                    goto LABEL_21;
                }
              }
            }
          }
        }
        if ( igi2_frame.zSymbol[0] == 116 && igi2_frame.zSymbol[1] == 104 && igi2_frame.zSymbol[2] == 105 && igi2_frame.zSymbol[3] == 115 && igi2_frame.zSymbol[4] == 46 )
        {
          v13 = 0;
          do
          {
            v14 = igi2_frame.zSymbol[v13 + 5];
            igi2_frame.zMember[v13++] = v14;
          }
          while ( v14 );
          Level_GetUniqueQTaskNameFromTask(igi2_frame.zName, ptQTask);
          sprintf(igi2_frame.zSymbol, "%s.%s", igi2_frame.zName, igi2_frame.zMember);
        }
        if ( strstr(igi2_frame.zSymbol, ".isExists") )
          strcpy(igi2_frame.zSymbol, "1");
        v15 = strcpy(igi2_frame.zTarget, igi2_frame.zSymbol);
        zExpression = igi2_frame.zSource;
        igi2_frame.zTarget = (char *)&v15[strlen(v15)];
        goto LABEL_42;
      }
      zExpression = igi2_frame.zSource;
      v16 = (unsigned __int8)*igi2_frame.zSource;
      if ( *igi2_frame.zSource == 47 && igi2_frame.zSource[1] == 47 )
        break;
      v17 = igi2_frame.zTarget;
      *(_WORD *)igi2_frame.zTarget = (unsigned __int8)v16;
      if ( *zExpression )
      {
        igi2_frame.zTarget = v17 + 1;
        ++zExpression;
LABEL_41:
        igi2_frame.zSource = zExpression;
      }
LABEL_42:
      if ( !zExpression )
        goto LABEL_43;
    }
    do
    {
      if ( (_BYTE)v16 == 10 )
        break;
      LOBYTE(v16) = *++zExpression;
    }
    while ( (_BYTE)v16 );
    goto LABEL_41;
  }
LABEL_43:
  *igi2_frame.zTarget = 0;
  zCompiledExpression = ptLevelExpression->zCompiledExpression;
  if ( zCompiledExpression )
  {
    v19 = *(_DWORD *)((unsigned int)(zCompiledExpression - 4) & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v19);
    memset(*(void **)(v19 + 8), 0xCDu, *(_DWORD *)(v19 + 16));
    free((void *)v19);
    ptLevelExpression->zCompiledExpression = nullptr;
  }
  if ( !Script_nSP )
  {
    LDebug_Error("Script: Stack underflow.");
LABEL_49:
    abort();
  }
  Script_anWarningLevelStack[--Script_nSP] = Script_nWarningLevel;
  Script_nWarningLevel = 0;
  ptLevelExpression->zCompiledExpression = (char *)Mem_AllocFn(strlen(igi2_frame.zTemp) + 1, 4);
  ptLevelExpression->ptExpression = Script_ParseLine(igi2_frame.zTemp);
  if ( Script_nSP >= 256 )
  {
    LDebug_Error("Script: Stack overflow.");
    goto LABEL_49;
  }
  Script_nWarningLevel = Script_anWarningLevelStack[Script_nSP];
  v20 = ptLevelExpression->zCompiledExpression;
  ++Script_nSP;
  strcpy(v20, igi2_frame.zTemp);
}

// source: h/1/level.c:5776  [anchor-hash]
enum bool __cdecl Level_LevelExpressionDefined(struct LevelExpression_s *ptLevelExpression)
{
  return ptLevelExpression->zExpression
      && *ptLevelExpression->zCompiledExpression
      && ptLevelExpression->ptExpression != nullptr;
}

// source: h/1/level.c:5806  [anchor-callee]
double __cdecl Level_RunLevelExpression(
        struct LevelExpression_s *ptLevelExpression,
        struct QTask_s *ptQTask)
{
  struct QExpression_s *ptExpression; // ebx

  if ( !ptLevelExpression->zCompiledExpression
    || (Level_ValidateLevelExpression(ptLevelExpression), !ptLevelExpression->zCompiledExpression) )
  {
    Level_CompileLevelExpression(ptLevelExpression, ptQTask);
  }
  ptExpression = ptLevelExpression->ptExpression;
  if ( ptExpression )
    return Expression_EvalFloat(ptExpression);
  else
    return 0.0;
}

// source: h/1/level.c:5845  [size]
struct QTask_s *__cdecl Level_GetLevelQTask()
{
  return &Level_ptQLevelQTask->tQTask;
}

// source: h/1/level.c:5858  [anchor-callee]
int __cdecl Level_GetTargetQTaskIDFromSymbol(char *zSymbol)
{
  char v1; // al
  int v2; // ebp
  int v3; // edi
  int v4; // ecx
  char *v5; // edx
  char v6; // bl

  v1 = *zSymbol;
  v2 = 0;
  v3 = 0;
  v4 = 1;
  v5 = zSymbol;
  if ( *zSymbol != 46 )
  {
    do
    {
      if ( !v1 )
        break;
      v1 = *++v5;
    }
    while ( v1 != 46 );
    if ( v5 < zSymbol )
      return -1;
  }
  while ( 1 )
  {
    v6 = *--v5;
    if ( v6 < 48 || v6 > 57 )
      break;
    v2 += v4 * (v6 - 48);
    v4 *= 10;
    v3 = 1;
    if ( v5 < zSymbol )
      return -1;
  }
  if ( v3 )
    return v2;
  else
    return -1;
}

// source: h/1/level.c:5916  [size]
__int16 __cdecl Level_GetAllowSaveQTaskEvent()
{
  return Level_eAllowSaveQTaskEvent;
}

// source: h/1/level.c:5929  [size]
__int16 __cdecl Level_GetSaveQTaskEvent()
{
  return Level_eSaveQTaskQTaskEvent;
}

// source: h/1/level.c:5944  [size]
void __cdecl Level_SetQTaskTypeSaved(unsigned __int16 eQTaskType)
{
  QTask_LinkQTaskEventHandlerFn(
    eQTaskType,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveHandler);
}

// source: h/1/level.c:5959  [size]
void __cdecl Level_SetQTaskTypeSavedNoChildren(unsigned __int16 eQTaskType)
{
  QTask_LinkQTaskEventHandlerFn(
    eQTaskType,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskSaveNoChildrenHandler);
}

// source: h/1/level.c:5974  [size]
void __cdecl Level_SetQTaskTypeNotSaved(unsigned __int16 eQTaskType)
{
  QTask_LinkQTaskEventHandlerFn(
    eQTaskType,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskDontSaveHandler);
}

// source: h/1/level.c:5989  [size]
void __cdecl Level_SetQTaskTypeNotSavedCreateable(unsigned __int16 eQTaskType)
{
  QTask_LinkQTaskEventHandlerFn(
    eQTaskType,
    Level_eAllowSaveQTaskEvent,
    (void (__cdecl *)(struct QTask_s *, void *))Level_SaveQTaskDontSaveCreateableHandler);
}

// source: h/1/level.c:6010  [anchor-strings]
enum bool __cdecl Level_SaveQTask(
        char *zFilename,
        struct QTask_s *ptParent,
        enum bool isParentSaved,
        enum bool isAutoAllocateQTaskID)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct ParameterList_s *ptParameterList; };
    struct { char igi2_o1[4]; int i; };
    struct { char igi2_o2[8]; char *zTemp2; };
    struct { char igi2_o3[12]; struct QTaskType_s *v30; };
    struct { char igi2_o4[16]; struct File_s *ptFile; };
    struct { char igi2_o5[20]; int v32; };
    struct { char igi2_o6[24]; int eQTaskType; };
    struct { char igi2_o7[28]; char zBackupFilename[260]; };
    struct { char igi2_o8[288]; char zFilenameTemp[260]; };
    struct { char igi2_o9[548]; char zTempFilename[260]; };
    char igi2_extent[808];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  char *v4; // esi
  int v5; // edx
  char v6; // cl
  char v7; // al
  int v8; // ecx
  char *v9; // eax
  struct File_s *v10; // esi
  int v11; // ebx
  char *v12; // ebp
  void *pfHandler; // edx
  struct ParameterList_s *v14; // eax
  int v15; // ebx
  bool v16; // cc
  char *zName; // eax
  char *v18; // eax
  char *v19; // ebx
  int v20; // esi
  int v21; // esi
  void *v22; // edi
  enum bool result; // eax
  char v24; // cl
  struct File_s *v25; // eax
  struct File_s *v26; // esi

  v4 = zFilename;
  Level_zErrorString = nullptr;
  v5 = igi2_frame.zFilenameTemp - zFilename;
  do
  {
    v6 = *zFilename;
    zFilename[v5] = *zFilename;
    ++zFilename;
  }
  while ( v6 );
  strcpy(igi2_frame.zBackupFilename, v4);
  if ( File_IsValidDevicename(nullptr, igi2_frame.zBackupFilename) && (v7 = igi2_frame.zBackupFilename[0], v8 = 0, igi2_frame.zBackupFilename[0]) )
  {
    while ( v7 != 58 )
    {
      v7 = igi2_frame.zBackupFilename[++v8];
      if ( !v7 )
        goto LABEL_7;
    }
    v9 = &igi2_frame.zBackupFilename[v8 + 1];
  }
  else
  {
LABEL_7:
    v9 = igi2_frame.zBackupFilename;
  }
  strcpy(v9, "temptask.txt");
  v10 = File_New(igi2_frame.zBackupFilename, "w");
  v11 = 0;
  igi2_frame.ptFile = v10;
  if ( v10 )
  {
    v12 = (char *)Mem_AllocFn(0x40000, 4);
    igi2_frame.zTemp2 = (char *)Mem_AllocFn(0x40000, 4);
    igi2_frame.eQTaskType = 0;
    igi2_frame.v32 = 0;
    igi2_frame.v30 = QTask_atQTaskType;
    do
    {
      pfHandler = QTask_aatQTaskFinalEvent[ParameterList_eGetParameterListQTaskEvent][igi2_frame.v32].pfHandler;
      igi2_frame.ptParameterList = nullptr;
      if ( pfHandler )
      {
        QTask_QTaskTypeTriggerQTaskEvent(v11, ParameterList_eGetParameterListQTaskEvent, &igi2_frame.ptParameterList);
        if ( igi2_frame.ptParameterList )
        {
          igi2_frame.i = 1;
          if ( Level_GetChildQTaskOfTypeRecursive((enum bool *)&igi2_frame.i, ptParent, nullptr, v11, true)
            || ptParent->eQTaskType == (_WORD)v11 )
          {
            sprintf(v12, "Task_DeclareParameters(\"%s\"", igi2_frame.v30->zName);
            v14 = igi2_frame.ptParameterList;
            v15 = 0;
            v16 = igi2_frame.ptParameterList->nParameters <= 0;
            igi2_frame.i = 0;
            if ( !v16 )
            {
              do
              {
                if ( (v14->ptParameterListItem[v15].bParameterProperties & 1) != 0 )
                {
                  strcat(v12, ", ");
                  *(_WORD *)&v12[strlen(v12)] = 34;
                  zName = igi2_frame.ptParameterList->ptParameterListItem[v15].zName;
                  strcat(v12, zName);
                  strcat(v12, "\", \"");
                  v18 = ParameterList_atParameterType[igi2_frame.ptParameterList->ptParameterListItem[v15].eParameterType].zName;
                  strcat(v12, v18);
                  v10 = igi2_frame.ptFile;
                  *(_WORD *)&v12[strlen(v12)] = 34;
                  v14 = igi2_frame.ptParameterList;
                }
                ++v15;
                v16 = ++igi2_frame.i < v14->nParameters;
              }
              while ( v16 );
            }
            v19 = igi2_frame.zTemp2;
            *(_DWORD *)&v12[strlen(v12)] = 670505;
            Level_SplitArgumentString(v12, 2, v19);
            File_atDevice[v10->eDeviceID].pfWrite(v10->eDeviceID, v10, v12, strlen(v12));
            v11 = igi2_frame.eQTaskType;
          }
        }
      }
      igi2_frame.eQTaskType = ++v11;
      ++igi2_frame.v32;
      ++igi2_frame.v30;
    }
    while ( (unsigned __int16)v11 < 0x1FFu );
    Level_SaveQTaskChildren(
      v10,
      ptParent,
      (char *)&g_zInitialValue,
      0,
      isParentSaved,
      v12,
      igi2_frame.zTemp2,
      isAutoAllocateQTaskID);
    if ( v10 == &File_tDummyAsyncFile )
      File_tDummyAsyncFile.isAsync = false;
    else
      File_atDevice[v10->eDeviceID].pfDelete(v10->eDeviceID, v10);
    if ( v12 )
    {
      v20 = *(_DWORD *)((unsigned int)(v12 - 4) & 0xFFFFFFFC);
      --Mem_nCurrentAllocations;
      Node_Remove((_DWORD **)v20);
      memset(*(void **)(v20 + 8), 0xCDu, *(_DWORD *)(v20 + 16));
      free((void *)v20);
    }
    if ( igi2_frame.zTemp2 )
    {
      --Mem_nCurrentAllocations;
      v21 = *(_DWORD *)((unsigned int)(igi2_frame.zTemp2 - 4) & 0xFFFFFFFC);
      Node_Remove((_DWORD **)v21);
      memset(*(void **)(v21 + 8), 0xCDu, *(_DWORD *)(v21 + 16));
      free((void *)v21);
    }
    v22 = File_Load(igi2_frame.zBackupFilename, (unsigned int *)&igi2_frame.ptFile);
    result = false;
    if ( v22 )
    {
      do
      {
        v24 = igi2_frame.zFilenameTemp[result];
        igi2_frame.zTempFilename[result++] = v24;
      }
      while ( v24 );
      v25 = File_New(igi2_frame.zTempFilename, "w");
      v26 = v25;
      if ( v25 )
      {
        File_atDevice[v25->eDeviceID].pfWrite(v25->eDeviceID, v25, v22, (unsigned int)igi2_frame.ptFile);
        if ( v26 == &File_tDummyAsyncFile )
          File_tDummyAsyncFile.isAsync = false;
        else
          File_atDevice[v26->eDeviceID].pfDelete(v26->eDeviceID, v26);
        File_Flush(v22);
        if ( AppContext_tAppContext.isQVMUsed )
          Script_Compile(igi2_frame.zTempFilename);
        return true;
      }
      else
      {
        sprintf(
          Level_zErrorBuffer,
          "Failed to write to file '%s'\nSaved to backup file: '%s'",
          igi2_frame.zFilenameTemp,
          igi2_frame.zBackupFilename);
        Level_zErrorString = Level_zErrorBuffer;
        File_Flush(v22);
        return false;
      }
    }
  }
  else
  {
    sprintf(
      Level_zErrorBuffer,
      "Failed to write to backup file: '%s'. \nObject file '%s' not saved.",
      igi2_frame.zBackupFilename,
      igi2_frame.zFilenameTemp);
    Level_zErrorString = Level_zErrorBuffer;
    return false;
  }
  return result;
}

// source: h/1/level.c:6141  [anchor-hash]
char *__cdecl Level_GetErrorString()
{
  char *result; // eax

  result = Level_zErrorString;
  if ( !Level_zErrorString )
    return (char *)&g_zInitialValue;
  return result;
}

// source: h/1/level.c:6154  [size]
char *__cdecl Level_SetErrorString(char *zError)
{
  Level_zErrorString = zError;
  return zError;
}

// source: h/1/level.c:6167  [size]
struct QTask_s *__cdecl Level_New(struct QTask_s *ptParent)
{
  return QTask_NewFn(ptParent, Level_eLevelQTaskType, nullptr);
}

// source: h/1/level.c:6190  [anchor-callee]
void __cdecl Level_AllocQTaskRangeForQTaskType(unsigned __int16 eQTaskType, int nMinQTaskID, int nMaxQTaskID)
{
  struct LevelQTaskRange_s *i; // eax
  _DWORD *v4; // eax

  for ( i = Level_tQTaskRangeList.ptHead->ptNext; i; i = i->ptNext )
    ;
  v4 = Mem_AllocFn(20, 4);
  v4[3] = nMinQTaskID;
  *((_WORD *)v4 + 4) = eQTaskType;
  v4[4] = nMaxQTaskID;
  v4[1] = 0;
  *v4 = 0;
  List_AddTail(v4, (int)&Level_tQTaskRangeList);
  if ( !QTask_aatQTaskFinalEvent[Level_eGetLevelQTaskRangeQTaskEvent][eQTaskType].pfHandler )
    QTask_LinkQTaskEventHandlerFn(eQTaskType, Level_eGetLevelQTaskRangeQTaskEvent, Level_GetQTaskRangeHandler);
}

// source: h/1/level.c:6228  [anchor-hash]
void __cdecl Level_EnableDefineQTaskIDInScript(enum bool isEnabled)
{
  Level_isDisableDefineQTaskIDInScript = isEnabled == false;
}

// source: h/1/level.c:6241  [anchor-caller]
struct QTaskNoteList_s *Level_Open()
{
  struct ParameterListReference_s *v0; // eax
  struct ParameterItemReference_s **p_ptMiddle; // ecx
  unsigned __int16 BaseQTaskType; // ax
  unsigned __int16 v3; // ax
  unsigned __int16 v4; // ax
  unsigned __int16 v5; // ax
  unsigned __int16 v6; // ax
  int v7; // eax
  int v8; // eax
  unsigned __int16 v9; // si
  unsigned __int16 v10; // si
  unsigned __int16 v11; // si
  unsigned __int16 v12; // si
  unsigned __int16 v13; // si
  int v14; // esi
  enum bool *p_isUsed; // eax
  char v16; // bl
  int v17; // eax
  char v18; // dl
  int v19; // esi
  enum bool *v20; // eax
  int v21; // eax
  int v22; // esi
  enum bool *v23; // eax
  int v24; // eax
  int v25; // esi
  enum bool *v26; // eax
  int v27; // eax
  int v28; // esi
  enum bool *v29; // eax
  int v30; // eax
  int v31; // esi
  enum bool *v32; // eax
  int v33; // eax
  int v34; // esi
  enum bool *v35; // eax
  int v36; // eax
  int v37; // esi
  enum bool *v38; // eax
  int v39; // eax
  int v40; // esi
  enum bool *v41; // eax
  int v42; // eax
  int v43; // edx
  enum bool *v44; // eax
  int v45; // eax
  int v46; // esi
  int v47; // esi
  int v48; // edi
  char v49; // bl
  int v50; // esi
  enum bool *v51; // eax
  int v52; // eax
  int v53; // esi
  enum bool *v54; // eax
  int v55; // eax
  int v56; // esi
  enum bool *v57; // eax
  int v58; // eax
  int v59; // esi
  enum bool *v60; // eax
  int v61; // eax
  int v62; // esi
  enum bool *v63; // eax
  int v64; // eax
  int v65; // esi
  struct QTaskNoteList_s *result; // eax
  struct QTaskNote_s **v67; // ecx
  char v68; // [esp-18h] [ebp-18h]
  char v69; // [esp-18h] [ebp-18h]

  v0 = Level_atQTaskTypeParameterListReference;
  do
  {
    p_ptMiddle = &v0->tParameterReferenceList.ptMiddle;
    v0->tParameterReferenceList.ptHead = (struct ParameterItemReference_s *)&v0->tParameterReferenceList.ptMiddle;
    v0->tParameterReferenceList.ptTail = (struct ParameterItemReference_s *)v0;
    ++v0;
    *p_ptMiddle = nullptr;
  }
  while ( (int)v0 < 127888364 );
  BaseQTaskType = QTask_GetBaseQTaskType();
  Level_eLevelQTaskType = QTask_NewQTaskType("Level", 60, BaseQTaskType, 0, 0);
  v3 = QTask_GetBaseQTaskType();
  Level_eStaticQTaskType = QTask_NewQTaskType("Static", 40, v3, 0, 0);
  v4 = QTask_GetBaseQTaskType();
  Level_eDynamicQTaskType = QTask_NewQTaskType("Dynamic", 40, v4, 0, 0);
  v5 = QTask_GetBaseQTaskType();
  Level_eIdleQTaskType = QTask_NewQTaskType("Idle", 40, v5, 0, 0);
  v6 = QTask_GetBaseQTaskType();
  Level_eCameraBaseQTaskType = QTask_NewQTaskType("CameraBase", 40, v6, 0, 0);
  Level_ePrintQTaskInfoQTaskEvent = QTask_NewQTaskEventFn(0, "PrintQTaskInfo");
  Level_eGetUniqueQTaskNameEvent = QTask_NewQTaskEventFn(0, "GetUniqueQTaskName");
  Level_eSaveQTaskQTaskEvent = QTask_NewQTaskEventFn(0, "SaveTask");
  Level_eAllowSaveQTaskEvent = QTask_NewQTaskEventFn(0, "AllowSaveTask");
  Level_eGetLevelQTaskRangeQTaskEvent = QTask_NewQTaskEventFn(0, "GetLevelQTaskRange");
  Level_eRegisterLevelScriptSymbolsEvent = QTask_NewQTaskEventNoContextFn(0, "RegisterLevelScriptSymbols");
  Level_eRemoveLevelScriptSymbolsEvent = QTask_NewQTaskEventNoContextFn(0, "RemoveLevelScriptSymbols");
  Level_eUpdateInternalDataAfterLoadEvent = QTask_NewQTaskEventNoContextFn(0, "UpdateInternalDataAfterLoad");
  v7 = 0;
  while ( ParameterList_atParameterEvent[v7].isUsed )
  {
    if ( ++v7 >= 16 )
    {
      LDebug_Error("Unable to allocate parameter event");
      goto LABEL_7;
    }
  }
  ParameterList_atParameterEvent[v7].isUsed = true;
  Level_eParameterPrintParameterEvent = v7;
  v8 = 0;
  while ( ParameterList_atParameterEvent[v8].isUsed )
  {
    if ( ++v8 >= 16 )
    {
      LDebug_Error("Unable to allocate parameter event");
      goto LABEL_7;
    }
  }
  v9 = Level_eLevelQTaskType;
  ParameterList_atParameterEvent[v8].isUsed = true;
  Level_eParameterPrintExParameterEvent = v8;
  QTask_LinkQTaskEventHandlerNoContextFn(v9, 1, Level_LevelRunHandler);
  QTask_LinkQTaskEventHandlerFn(v9, 0, (void (__cdecl *)(struct QTask_s *, void *))Level_LevelCreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v9, 2, (void (__cdecl *)(struct QTask_s *))Level_LevelDeleteHandler);
  v10 = Level_eStaticQTaskType;
  QTask_LinkQTaskEventHandlerNoContextFn(
    Level_eStaticQTaskType,
    1,
    (void (__cdecl *)(struct QTask_s *))Level_StaticRunHandler);
  QTask_LinkQTaskEventHandlerFn(v10, 0, (void (__cdecl *)(struct QTask_s *, void *))Level_StaticCreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v10, 2, (void (__cdecl *)(struct QTask_s *))Level_StaticDeleteHandler);
  QTask_LinkQTaskEventHandlerFn(v10, DynCubeObj_eDynCubeObjRemoveQTaskEvent, Level_StaticRemoveHandler);
  QTask_LinkQTaskEventHandlerFn(v10, DynCubeObj_eDynCubeObjRegisterQTaskEvent, Level_StaticRegisterHandler);
  v11 = Level_eDynamicQTaskType;
  QTask_LinkQTaskEventHandlerNoContextFn(Level_eDynamicQTaskType, 1, Level_DynamicRunHandler);
  QTask_LinkQTaskEventHandlerFn(v11, 0, (void (__cdecl *)(struct QTask_s *, void *))Level_DynamicCreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v11, 2, (void (__cdecl *)(struct QTask_s *))Level_DynamicDeleteHandler);
  v12 = Level_eIdleQTaskType;
  QTask_LinkQTaskEventHandlerNoContextFn(
    Level_eIdleQTaskType,
    1,
    (void (__cdecl *)(struct QTask_s *))Level_IdleRunHandler);
  QTask_LinkQTaskEventHandlerFn(v12, 0, (void (__cdecl *)(struct QTask_s *, void *))Level_IdleCreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v12, 2, (void (__cdecl *)(struct QTask_s *))Level_IdleDeleteHandler);
  v13 = Level_eCameraBaseQTaskType;
  QTask_LinkQTaskEventHandlerNoContextFn(Level_eCameraBaseQTaskType, 1, Level_CameraBaseRunHandler);
  QTask_LinkQTaskEventHandlerFn(v13, 0, (void (__cdecl *)(struct QTask_s *, void *))Level_CameraBaseCreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v13, 2, (void (__cdecl *)(struct QTask_s *))Level_CameraBaseDeleteHandler);
  v14 = 0;
  p_isUsed = &ParameterList_atParameterType[0].isUsed;
  while ( *p_isUsed )
  {
    p_isUsed += 19;
    ++v14;
    if ( (int)p_isUsed >= 128883816 )
    {
LABEL_71:
      LDebug_Error("Unable to allocate parameter type");
LABEL_7:
      abort();
    }
  }
  v16 = ParameterList_eQParameterParseEvent;
  v17 = v14;
  v18 = ParameterList_eQParameterParseEvent;
  ParameterList_atParameterType[v17].isUsed = true;
  ParameterList_atParameterType[v17].zName = "Quat32";
  ParameterList_atParameterType[v17].eParentParameterType = -1;
  Level_eParameterTypeQuat32 = v14;
  ParameterList_LinkParameterEventHandler(v14, v18, Level_ParseQuat32Handler);
  ParameterList_LinkParameterEventHandler(v14, ParameterList_eQParameterPrintEvent, Level_PrintQuat32Handler);
  ParameterList_LinkParameterEventHandler(
    v14,
    ParameterList_eQParameterCopyEvent,
    (void (__cdecl *)(void *, void *))Level_CopyQuat32Handler);
  ParameterList_LinkParameterEventHandler(
    v14,
    ParameterList_eQParameterPasteEvent,
    (void (__cdecl *)(void *, void *))Level_PasteQuat32Handler);
  ParameterList_LinkParameterEventHandler(
    v14,
    ParameterList_eQParameterGetSizeEvent,
    (void (__cdecl *)(void *, void *))Level_GetSizeQuat32Handler);
  ParameterList_LinkParameterEventHandler(
    v14,
    ParameterList_eQParameterGetNumberOfArgumentsEvent,
    (void (__cdecl *)(void *, void *))Level_GetNumberOfArgumentsQuat32Handler);
  v19 = 0;
  v20 = &ParameterList_atParameterType[0].isUsed;
  while ( *v20 )
  {
    v20 += 19;
    ++v19;
    if ( (int)v20 >= 128883816 )
      goto LABEL_71;
  }
  v21 = v19;
  ParameterList_atParameterType[v21].isUsed = true;
  ParameterList_atParameterType[v21].zName = "Real32";
  ParameterList_atParameterType[v21].eParentParameterType = -1;
  Level_eParameterTypeReal32 = v19;
  ParameterList_LinkParameterEventHandler(v19, v16, Level_ParseReal32Handler);
  ParameterList_LinkParameterEventHandler(v19, ParameterList_eQParameterPrintEvent, Level_PrintReal32Handler);
  ParameterList_LinkParameterEventHandler(v19, ParameterList_eQParameterCopyEvent, Level_CopyReal32Handler);
  ParameterList_LinkParameterEventHandler(v19, ParameterList_eQParameterPasteEvent, Level_PasteReal32Handler);
  ParameterList_LinkParameterEventHandler(
    v19,
    ParameterList_eQParameterGetSizeEvent,
    (void (__cdecl *)(void *, void *))Level_GetSizeReal32Handler);
  ParameterList_LinkParameterEventHandler(
    v19,
    ParameterList_eQParameterGetNumberOfArgumentsEvent,
    (void (__cdecl *)(void *, void *))Level_GetNumberOfArgumentsReal32Handler);
  v22 = 0;
  v23 = &ParameterList_atParameterType[0].isUsed;
  while ( *v23 )
  {
    v23 += 19;
    ++v22;
    if ( (int)v23 >= 128883816 )
      goto LABEL_71;
  }
  v24 = v22;
  ParameterList_atParameterType[v24].isUsed = true;
  ParameterList_atParameterType[v24].zName = "Real32x3";
  ParameterList_atParameterType[v24].eParentParameterType = -1;
  Level_eParameterTypeReal32x3 = v22;
  ParameterList_LinkParameterEventHandler(v22, v16, Level_ParseReal32x3Handler);
  ParameterList_LinkParameterEventHandler(v22, ParameterList_eQParameterPrintEvent, Level_PrintReal32x3Handler);
  ParameterList_LinkParameterEventHandler(v22, ParameterList_eQParameterCopyEvent, Level_CopyReal32x3Handler);
  ParameterList_LinkParameterEventHandler(v22, ParameterList_eQParameterPasteEvent, Level_PasteReal32x3Handler);
  ParameterList_LinkParameterEventHandler(
    v22,
    ParameterList_eQParameterGetSizeEvent,
    (void (__cdecl *)(void *, void *))Level_GetSizeReal32x3Handler);
  ParameterList_LinkParameterEventHandler(
    v22,
    ParameterList_eQParameterGetNumberOfArgumentsEvent,
    (void (__cdecl *)(void *, void *))Level_GetNumberOfArgumentsReal32x3Handler);
  v25 = 0;
  v26 = &ParameterList_atParameterType[0].isUsed;
  while ( *v26 )
  {
    v26 += 19;
    ++v25;
    if ( (int)v26 >= 128883816 )
      goto LABEL_71;
  }
  v27 = v25;
  ParameterList_atParameterType[v27].isUsed = true;
  ParameterList_atParameterType[v27].zName = "Real32x9";
  ParameterList_atParameterType[v27].eParentParameterType = -1;
  Level_eParameterTypeReal32x9 = v25;
  ParameterList_LinkParameterEventHandler(v25, v16, Level_ParseReal32x9Handler);
  ParameterList_LinkParameterEventHandler(v25, ParameterList_eQParameterPrintEvent, Level_PrintReal32x9Handler);
  ParameterList_LinkParameterEventHandler(
    v25,
    ParameterList_eQParameterCopyEvent,
    (void (__cdecl *)(void *, void *))Level_CopyReal32x9Handler);
  ParameterList_LinkParameterEventHandler(
    v25,
    ParameterList_eQParameterPasteEvent,
    (void (__cdecl *)(void *, void *))Level_PasteReal32x9Handler);
  ParameterList_LinkParameterEventHandler(
    v25,
    ParameterList_eQParameterGetSizeEvent,
    (void (__cdecl *)(void *, void *))Level_GetSizeReal32x9Handler);
  ParameterList_LinkParameterEventHandler(
    v25,
    ParameterList_eQParameterGetNumberOfArgumentsEvent,
    (void (__cdecl *)(void *, void *))Level_GetNumberOfArgumentsReal32x9Handler);
  v28 = 0;
  v29 = &ParameterList_atParameterType[0].isUsed;
  while ( *v29 )
  {
    v29 += 19;
    ++v28;
    if ( (int)v29 >= 128883816 )
      goto LABEL_71;
  }
  v30 = v28;
  ParameterList_atParameterType[v30].isUsed = true;
  ParameterList_atParameterType[v30].zName = "Real64";
  ParameterList_atParameterType[v30].eParentParameterType = -1;
  Level_eParameterTypeReal64 = v28;
  ParameterList_LinkParameterEventHandler(v28, v16, Level_ParseReal64Handler);
  ParameterList_LinkParameterEventHandler(v28, ParameterList_eQParameterPrintEvent, Level_PrintReal64Handler);
  ParameterList_LinkParameterEventHandler(v28, ParameterList_eQParameterCopyEvent, Level_CopyReal64Handler);
  ParameterList_LinkParameterEventHandler(v28, ParameterList_eQParameterPasteEvent, Level_PasteReal64Handler);
  ParameterList_LinkParameterEventHandler(
    v28,
    ParameterList_eQParameterGetSizeEvent,
    (void (__cdecl *)(void *, void *))Level_GetSizeReal64Handler);
  ParameterList_LinkParameterEventHandler(
    v28,
    ParameterList_eQParameterGetNumberOfArgumentsEvent,
    (void (__cdecl *)(void *, void *))Level_GetNumberOfArgumentsReal64Handler);
  v31 = 0;
  v32 = &ParameterList_atParameterType[0].isUsed;
  while ( *v32 )
  {
    v32 += 19;
    ++v31;
    if ( (int)v32 >= 128883816 )
      goto LABEL_71;
  }
  v33 = v31;
  ParameterList_atParameterType[v33].isUsed = true;
  ParameterList_atParameterType[v33].zName = "Real64x3";
  ParameterList_atParameterType[v33].eParentParameterType = -1;
  Level_eParameterTypeReal64x3 = v31;
  ParameterList_LinkParameterEventHandler(v31, v16, Level_ParseReal64x3Handler);
  ParameterList_LinkParameterEventHandler(v31, ParameterList_eQParameterPrintEvent, Level_PrintReal64x3Handler);
  ParameterList_LinkParameterEventHandler(
    v31,
    ParameterList_eQParameterCopyEvent,
    (void (__cdecl *)(void *, void *))Level_CopyReal64x3Handler);
  ParameterList_LinkParameterEventHandler(
    v31,
    ParameterList_eQParameterPasteEvent,
    (void (__cdecl *)(void *, void *))Level_PasteReal64x3Handler);
  ParameterList_LinkParameterEventHandler(
    v31,
    ParameterList_eQParameterGetSizeEvent,
    (void (__cdecl *)(void *, void *))Level_GetSizeReal64x3Handler);
  ParameterList_LinkParameterEventHandler(
    v31,
    ParameterList_eQParameterGetNumberOfArgumentsEvent,
    (void (__cdecl *)(void *, void *))Level_GetNumberOfArgumentsReal64x3Handler);
  v34 = 0;
  v35 = &ParameterList_atParameterType[0].isUsed;
  while ( *v35 )
  {
    v35 += 19;
    ++v34;
    if ( (int)v35 >= 128883816 )
      goto LABEL_71;
  }
  v36 = v34;
  ParameterList_atParameterType[v36].isUsed = true;
  ParameterList_atParameterType[v36].zName = "Int32";
  ParameterList_atParameterType[v36].eParentParameterType = -1;
  Level_eParameterTypeInt32 = v34;
  ParameterList_LinkParameterEventHandler(v34, v16, Level_ParseInt32Handler);
  ParameterList_LinkParameterEventHandler(v34, ParameterList_eQParameterPrintEvent, Level_PrintInt32Handler);
  ParameterList_LinkParameterEventHandler(v34, ParameterList_eQParameterCopyEvent, Level_CopyInt32Handler);
  ParameterList_LinkParameterEventHandler(v34, ParameterList_eQParameterPasteEvent, Level_PasteInt32Handler);
  ParameterList_LinkParameterEventHandler(
    v34,
    ParameterList_eQParameterGetSizeEvent,
    (void (__cdecl *)(void *, void *))Level_GetSizeInt32Handler);
  ParameterList_LinkParameterEventHandler(
    v34,
    ParameterList_eQParameterGetNumberOfArgumentsEvent,
    (void (__cdecl *)(void *, void *))Level_GetNumberOfArgumentsInt32Handler);
  v37 = 0;
  v38 = &ParameterList_atParameterType[0].isUsed;
  while ( *v38 )
  {
    v38 += 19;
    ++v37;
    if ( (int)v38 >= 128883816 )
      goto LABEL_71;
  }
  v39 = v37;
  ParameterList_atParameterType[v39].isUsed = true;
  ParameterList_atParameterType[v39].zName = "Int16";
  ParameterList_atParameterType[v39].eParentParameterType = -1;
  Level_eParameterTypeInt16 = v37;
  ParameterList_LinkParameterEventHandler(v37, v16, Level_ParseInt16Handler);
  ParameterList_LinkParameterEventHandler(v37, ParameterList_eQParameterPrintEvent, Level_PrintInt16Handler);
  ParameterList_LinkParameterEventHandler(v37, ParameterList_eQParameterCopyEvent, Level_CopyInt16Handler);
  ParameterList_LinkParameterEventHandler(v37, ParameterList_eQParameterPasteEvent, Level_PasteInt16Handler);
  ParameterList_LinkParameterEventHandler(
    v37,
    ParameterList_eQParameterGetSizeEvent,
    (void (__cdecl *)(void *, void *))Level_GetSizeInt16Handler);
  ParameterList_LinkParameterEventHandler(
    v37,
    ParameterList_eQParameterGetNumberOfArgumentsEvent,
    (void (__cdecl *)(void *, void *))Level_GetNumberOfArgumentsInt16Handler);
  v40 = 0;
  v41 = &ParameterList_atParameterType[0].isUsed;
  while ( *v41 )
  {
    v41 += 19;
    ++v40;
    if ( (int)v41 >= 128883816 )
      goto LABEL_71;
  }
  v42 = v40;
  ParameterList_atParameterType[v42].isUsed = true;
  ParameterList_atParameterType[v42].zName = "VarString";
  ParameterList_atParameterType[v42].eParentParameterType = -1;
  Level_eParameterTypeVarString = v40;
  ParameterList_LinkParameterEventHandler(v40, v16, Level_ParseVarStringHandler);
  ParameterList_LinkParameterEventHandler(v40, ParameterList_eQParameterPrintEvent, Level_PrintVarStringHandler);
  ParameterList_LinkParameterEventHandler(v40, ParameterList_eQParameterCopyEvent, Level_CopyVarStringHandler);
  ParameterList_LinkParameterEventHandler(v40, ParameterList_eQParameterPasteEvent, Level_PasteVarStringHandler);
  ParameterList_LinkParameterEventHandler(v40, ParameterList_eQParameterGetSizeEvent, Level_GetSizeVarStringHandler);
  ParameterList_LinkParameterEventHandler(
    v40,
    ParameterList_eQParameterGetNumberOfArgumentsEvent,
    (void (__cdecl *)(void *, void *))Level_GetNumberOfArgumentsVarStringHandler);
  v43 = 0;
  v44 = &ParameterList_atParameterType[0].isUsed;
  while ( *v44 )
  {
    v44 += 19;
    ++v43;
    if ( (int)v44 >= 128883816 )
      goto LABEL_71;
  }
  v45 = v43;
  ParameterList_atParameterType[v45].isUsed = true;
  ParameterList_atParameterType[v45].zName = "FixedString";
  ParameterList_atParameterType[v45].eParentParameterType = -1;
  Level_eParameterTypeFixedString = v43;
  v46 = ParameterList_NewParameterType("String16", v43);
  Level_eParameterTypeString16 = v46;
  ParameterList_LinkParameterEventHandler(v46, ParameterList_eQParameterParseEvent, Level_ParseString16Handler);
  ParameterList_LinkParameterEventHandler(v46, ParameterList_eQParameterPrintEvent, Level_PrintStringHandler);
  ParameterList_LinkParameterEventHandler(v46, ParameterList_eQParameterCopyEvent, Level_CopyString16Handler);
  ParameterList_LinkParameterEventHandler(v46, ParameterList_eQParameterPasteEvent, Level_PasteString16Handler);
  ParameterList_LinkParameterEventHandler(v46, ParameterList_eQParameterGetSizeEvent, Level_GetSizeString16Handler);
  ParameterList_LinkParameterEventHandler(
    v46,
    ParameterList_eQParameterGetNumberOfArgumentsEvent,
    (void (__cdecl *)(void *, void *))Level_GetNumberOfArgumentsString16Handler);
  v47 = ParameterList_NewParameterType("String32", Level_eParameterTypeFixedString);
  Level_eParameterTypeString32 = v47;
  ParameterList_LinkParameterEventHandler(v47, ParameterList_eQParameterParseEvent, Level_ParseString32Handler);
  ParameterList_LinkParameterEventHandler(v47, ParameterList_eQParameterPrintEvent, Level_PrintStringHandler);
  ParameterList_LinkParameterEventHandler(v47, ParameterList_eQParameterCopyEvent, Level_CopyString32Handler);
  ParameterList_LinkParameterEventHandler(v47, ParameterList_eQParameterPasteEvent, Level_PasteString32Handler);
  ParameterList_LinkParameterEventHandler(v47, ParameterList_eQParameterGetSizeEvent, Level_GetSizeString32Handler);
  ParameterList_LinkParameterEventHandler(
    v47,
    ParameterList_eQParameterGetNumberOfArgumentsEvent,
    (void (__cdecl *)(void *, void *))Level_GetNumberOfArgumentsString32Handler);
  v48 = ParameterList_NewParameterType("String256", Level_eParameterTypeFixedString);
  Level_eParameterTypeString256 = v48;
  ParameterList_LinkParameterEventHandler(v48, ParameterList_eQParameterParseEvent, Level_ParseString256Handler);
  ParameterList_LinkParameterEventHandler(v48, ParameterList_eQParameterPrintEvent, Level_PrintStringHandler);
  v49 = ParameterList_eQParameterCopyEvent;
  ParameterList_LinkParameterEventHandler(v48, ParameterList_eQParameterCopyEvent, Level_CopyString256Handler);
  ParameterList_LinkParameterEventHandler(v48, ParameterList_eQParameterPasteEvent, Level_PasteString256Handler);
  ParameterList_LinkParameterEventHandler(v48, ParameterList_eQParameterGetSizeEvent, Level_GetSizeString256Handler);
  ParameterList_LinkParameterEventHandler(
    v48,
    ParameterList_eQParameterGetNumberOfArgumentsEvent,
    (void (__cdecl *)(void *, void *))Level_GetNumberOfArgumentsString256Handler);
  v50 = 0;
  v51 = &ParameterList_atParameterType[0].isUsed;
  while ( *v51 )
  {
    v51 += 19;
    ++v50;
    if ( (int)v51 >= 128883816 )
      goto LABEL_71;
  }
  v52 = v50;
  v68 = ParameterList_eQParameterParseEvent;
  ParameterList_atParameterType[v52].isUsed = true;
  ParameterList_atParameterType[v52].zName = "LevelExpression";
  ParameterList_atParameterType[v52].eParentParameterType = -1;
  Level_eParameterTypeLevelExpression = v50;
  ParameterList_LinkParameterEventHandler(v50, v68, Level_ParseLevelExpressionHandler);
  ParameterList_LinkParameterEventHandler(v50, ParameterList_eQParameterPrintEvent, Level_PrintLevelExpressionHandler);
  ParameterList_LinkParameterEventHandler(v50, v49, Level_CopyLevelExpressionHandler);
  ParameterList_LinkParameterEventHandler(v50, ParameterList_eQParameterPasteEvent, Level_PasteLevelExpressionHandler);
  ParameterList_LinkParameterEventHandler(
    v50,
    ParameterList_eQParameterGetSizeEvent,
    Level_GetSizeLevelExpressionHandler);
  ParameterList_LinkParameterEventHandler(
    v50,
    ParameterList_eQParameterGetNumberOfArgumentsEvent,
    (void (__cdecl *)(void *, void *))Level_GetNumberOfArgumentsLevelExpressionHandler);
  v53 = 0;
  v54 = &ParameterList_atParameterType[0].isUsed;
  while ( *v54 )
  {
    v54 += 19;
    ++v53;
    if ( (int)v54 >= 128883816 )
      goto LABEL_71;
  }
  v55 = v53;
  v69 = ParameterList_eQParameterPrintEvent;
  ParameterList_atParameterType[v55].isUsed = true;
  ParameterList_atParameterType[v55].zName = "QTaskNote";
  ParameterList_atParameterType[v55].eParentParameterType = -1;
  Level_eParameterTypeQTaskNote = v53;
  ParameterList_LinkParameterEventHandler(v53, v69, Level_PrintStringHandler);
  ParameterList_LinkParameterEventHandler(v53, v49, Level_CopyQTaskNoteHandler);
  ParameterList_LinkParameterEventHandler(
    v53,
    ParameterList_eQParameterPasteEvent,
    (void (__cdecl *)(void *, void *))Level_PasteQTaskNoteHandler);
  ParameterList_LinkParameterEventHandler(
    v53,
    ParameterList_eQParameterGetSizeEvent,
    (void (__cdecl *)(void *, void *))Level_GetSizeQTaskNoteHandler);
  ParameterList_LinkParameterEventHandler(
    v53,
    ParameterList_eQParameterGetNumberOfArgumentsEvent,
    (void (__cdecl *)(void *, void *))Level_GetNumberOfArgumentsString16Handler);
  v56 = 0;
  v57 = &ParameterList_atParameterType[0].isUsed;
  while ( *v57 )
  {
    v57 += 19;
    ++v56;
    if ( (int)v57 >= 128883816 )
      goto LABEL_71;
  }
  v58 = v56;
  ParameterList_atParameterType[v58].isUsed = true;
  ParameterList_atParameterType[v58].zName = "bool8";
  ParameterList_atParameterType[v58].eParentParameterType = -1;
  Level_eParameterTypebool8 = v56;
  ParameterList_LinkParameterEventHandler(v56, ParameterList_eQParameterParseEvent, Level_Parsebool8Handler);
  ParameterList_LinkParameterEventHandler(v56, ParameterList_eQParameterPrintEvent, Level_Printbool8Handler);
  ParameterList_LinkParameterEventHandler(v56, v49, Level_Copybool8Handler);
  ParameterList_LinkParameterEventHandler(v56, ParameterList_eQParameterPasteEvent, Level_Pastebool8Handler);
  ParameterList_LinkParameterEventHandler(
    v56,
    ParameterList_eQParameterGetSizeEvent,
    (void (__cdecl *)(void *, void *))Level_GetSizebool8Handler);
  ParameterList_LinkParameterEventHandler(
    v56,
    ParameterList_eQParameterGetNumberOfArgumentsEvent,
    (void (__cdecl *)(void *, void *))Level_GetNumberOfArgumentsbool8Handler);
  v59 = 0;
  v60 = &ParameterList_atParameterType[0].isUsed;
  while ( *v60 )
  {
    v60 += 19;
    ++v59;
    if ( (int)v60 >= 128883816 )
      goto LABEL_71;
  }
  v61 = v59;
  ParameterList_atParameterType[v61].isUsed = true;
  ParameterList_atParameterType[v61].zName = "Graph";
  ParameterList_atParameterType[v61].eParentParameterType = -1;
  Level_eParameterTypeGraph = v59;
  ParameterList_LinkParameterEventHandler(v59, v49, (void (__cdecl *)(void *, void *))Level_CopyGraphHandler);
  ParameterList_LinkParameterEventHandler(
    v59,
    ParameterList_eQParameterPasteEvent,
    (void (__cdecl *)(void *, void *))Level_PasteGraphHandler);
  ParameterList_LinkParameterEventHandler(
    v59,
    ParameterList_eQParameterGetSizeEvent,
    (void (__cdecl *)(void *, void *))Level_GetSizeGraphHandler);
  v62 = 0;
  v63 = &ParameterList_atParameterType[0].isUsed;
  while ( *v63 )
  {
    v63 += 19;
    ++v62;
    if ( (int)v63 >= 128883816 )
      goto LABEL_71;
  }
  v64 = v62;
  ParameterList_atParameterType[v64].isUsed = true;
  ParameterList_atParameterType[v64].zName = "GraphEnvelope";
  ParameterList_atParameterType[v64].eParentParameterType = -1;
  Level_eParameterTypeGraphEnvelope = v62;
  ParameterList_LinkParameterEventHandler(v62, ParameterList_eQParameterParseEvent, Level_ParseGraphEnvelopeHandler);
  ParameterList_LinkParameterEventHandler(v62, ParameterList_eQParameterPrintEvent, Level_PrintGraphEnvelopeHandler);
  ParameterList_LinkParameterEventHandler(v62, v49, (void (__cdecl *)(void *, void *))Level_CopyGraphEnvelopeHandler);
  ParameterList_LinkParameterEventHandler(
    v62,
    ParameterList_eQParameterPasteEvent,
    (void (__cdecl *)(void *, void *))Level_PasteGraphEnvelopeHandler);
  ParameterList_LinkParameterEventHandler(
    v62,
    ParameterList_eQParameterGetSizeEvent,
    (void (__cdecl *)(void *, void *))Level_GetSizeGraphEnvelopeHandler);
  ParameterList_LinkParameterEventHandler(
    v62,
    ParameterList_eQParameterGetNumberOfArgumentsEvent,
    (void (__cdecl *)(void *, void *))Level_GetNumberOfArgumentsGraphEnvelopeHandler);
  Level_eParameterTypeScriptFile = ParameterList_NewParameterType("ScriptFile", v48);
  Level_eParameterTypeBitfield = ParameterList_NewParameterType("Bitfield", Level_eParameterTypeInt32);
  Level_eParameterTypePitchGraph = ParameterList_NewParameterType("PitchGraph", Level_eParameterTypeGraphEnvelope);
  Level_eParameterTypeRGB = ParameterList_NewParameterType("RGB", Level_eParameterTypeReal32x3);
  Level_eParameterTypeAngle = ParameterList_NewParameterType("Angle", Level_eParameterTypeReal32);
  Level_eParameterTypeDegrees = ParameterList_NewParameterType("Degrees", Level_eParameterTypeReal32);
  Level_eParameterTypeObjectPos = ParameterList_NewParameterType("ObjectPos", Level_eParameterTypeReal64x3);
  ParameterList_LinkParameterEventHandler(
    Level_eParameterTypeObjectPos,
    ParameterList_eQParameterPrintEvent,
    Level_PrintObjectPosHandler);
  Level_eParameterTypePushButton = ParameterList_NewParameterType("PushButton", Level_eParameterTypebool8);
  Level_eParameterTypeDropDownCombo = ParameterList_NewParameterType("DropDownCombo", Level_eParameterTypeVarString);
  v65 = ParameterList_NewParameterType("Real32x9Exact", Level_eParameterTypeReal32x9);
  Level_eParameterTypeReal32x9Exact = v65;
  ParameterList_LinkParameterEventHandler(v65, ParameterList_eQParameterPrintEvent, Level_PrintReal32x9ExactHandler);
  ParameterList_LinkParameterEventHandler(v65, ParameterList_eQParameterParseEvent, Level_ParseReal32x9ExactHandler);
  ParameterList_LinkParameterEventHandler(
    v65,
    ParameterList_eQParameterGetNumberOfArgumentsEvent,
    (void (__cdecl *)(void *, void *))Level_GetNumberOfArgumentsReal32x9ExactHandler);
  Symbol_Register(
    "Task_New",
    Level_QTaskNew,
    nullptr,
    -1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "Task_DeclareParameters",
    Level_DeclareTaskParameters,
    nullptr,
    -1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Level_isDynamicQTaskPaused = 0;
  Level_isDynamicQTaskActive = 0;
  result = Level_atQTaskNoteHashTable;
  do
  {
    v67 = &result->ptMiddle;
    result->ptHead = (struct QTaskNote_s *)&result->ptMiddle;
    result->ptTail = (struct QTaskNote_s *)result;
    ++result;
    *v67 = nullptr;
  }
  while ( (int)result < 127877748 );
  Level_ptLoadObjectsProfileRegion = nullptr;
  Level_ptRunLevelExpressionRegion = nullptr;
  Level_tQTaskRangeList.ptHead = (struct LevelQTaskRange_s *)&Level_tQTaskRangeList.ptMiddle;
  Level_tQTaskRangeList.ptTail = (struct LevelQTaskRange_s *)&Level_tQTaskRangeList;
  Level_tQTaskRangeList.ptMiddle = nullptr;
  return result;
}

// source: h/1/level.c:6507  [anchor-caller]
void __cdecl Level_Close()
{
  struct LevelQTaskRange_s *ptHead; // eax
  struct LevelQTaskRange_s *i; // ebx
  _DWORD **v2; // eax
  int v3; // esi
  struct QTaskNoteList_s *v4; // eax
  struct QTaskNote_s *v5; // esi
  struct QTaskNote_s *ptNext; // ebx
  struct MemPoolFreeItem_s *ptQTaskRef; // eax
  int v8; // esi
  struct ParameterListReference_s *v9; // esi
  int v10; // edx
  int v11; // ecx
  int v12; // edx
  int v13; // ecx
  int v14; // edx
  int v15; // ecx
  int v16; // eax
  int v17; // ecx
  int v18; // edx
  int v19; // eax
  int v20; // ecx
  int v21; // edx
  int v22; // eax
  int v23; // ecx
  int v24; // edx
  int v25; // eax
  int v26; // ecx
  int v27; // edx
  int v28; // eax
  int v29; // ecx
  int v30; // edx
  int v31; // eax
  int v32; // ecx
  int v33; // edx
  int v34; // ecx
  int v35; // edx
  struct QReference_s **v36; // esi
  struct MemPoolFreeItem_s *v37; // eax
  struct QTaskNoteList_s *v38; // [esp+10h] [ebp-4h]

  ptHead = Level_tQTaskRangeList.ptHead;
  for ( i = Level_tQTaskRangeList.ptHead->ptNext; i; i = i->ptNext )
  {
    v2 = Node_Remove(ptHead);
    if ( v2 )
    {
      v3 = *(_DWORD *)((unsigned int)(v2 - 1) & 0xFFFFFFFC);
      --Mem_nCurrentAllocations;
      Node_Remove((_DWORD **)v3);
      memset(*(void **)(v3 + 8), 0xCDu, *(_DWORD *)(v3 + 16));
      free((void *)v3);
    }
    ptHead = i;
  }
  v4 = Level_atQTaskNoteHashTable;
  v38 = Level_atQTaskNoteHashTable;
  do
  {
    v5 = v4->ptHead;
    ptNext = v4->ptHead->ptNext;
    if ( ptNext )
    {
      do
      {
        ptQTaskRef = (struct MemPoolFreeItem_s *)v5->ptQTaskRef;
        if ( ptQTaskRef->ptNext )
          ptQTaskRef = (struct MemPoolFreeItem_s *)Node_Remove(ptQTaskRef);
        --QTask_tQTaskRefPool.nAllocatedBlocks;
        ptQTaskRef->ptNext = QTask_tQTaskRefPool.tMemPoolFreeList.ptHead;
        QTask_tQTaskRefPool.tMemPoolFreeList.ptHead = ptQTaskRef;
        Node_Remove(v5);
        v8 = *(_DWORD *)((unsigned int)&v5[-1].zString[60] & 0xFFFFFFFC);
        --Mem_nCurrentAllocations;
        Node_Remove((_DWORD **)v8);
        memset(*(void **)(v8 + 8), 0xCDu, *(_DWORD *)(v8 + 16));
        free((void *)v8);
        v5 = ptNext;
        ptNext = ptNext->ptNext;
      }
      while ( ptNext );
      v4 = v38;
    }
    v38 = ++v4;
  }
  while ( (int)v4 < 127877748 );
  v9 = Level_atQTaskTypeParameterListReference;
  do
    Level_ClearParameterListReference(v9++);
  while ( (int)v9 < 127888364 );
  v10 = Level_eParameterTypePushButton;
  v11 = Level_eParameterTypeScriptFile;
  ParameterList_atParameterType[Level_eParameterTypeDropDownCombo].isUsed = false;
  ParameterList_atParameterType[v11].isUsed = false;
  ParameterList_atParameterType[v10].isUsed = false;
  v12 = Level_eParameterTypeDegrees;
  v13 = Level_eParameterTypeAngle;
  ParameterList_atParameterType[Level_eParameterTypeObjectPos].isUsed = false;
  ParameterList_atParameterType[v13].isUsed = false;
  ParameterList_atParameterType[v12].isUsed = false;
  v14 = Level_eParameterTypeBitfield;
  v15 = Level_eParameterTypePitchGraph;
  ParameterList_atParameterType[Level_eParameterTypeRGB].isUsed = false;
  v16 = Level_eParameterTypeGraphEnvelope;
  ParameterList_atParameterType[v15].isUsed = false;
  v17 = Level_eParameterTypeGraph;
  ParameterList_atParameterType[v14].isUsed = false;
  v18 = Level_eParameterTypeQuat32;
  ParameterList_atParameterType[v16].isUsed = false;
  v19 = Level_eParameterTypeReal64;
  ParameterList_atParameterType[v17].isUsed = false;
  v20 = Level_eParameterTypeReal64x3;
  ParameterList_atParameterType[v18].isUsed = false;
  v21 = Level_eParameterTypeReal32;
  ParameterList_atParameterType[v19].isUsed = false;
  v22 = Level_eParameterTypeReal32x3;
  ParameterList_atParameterType[v20].isUsed = false;
  v23 = Level_eParameterTypeReal32x9;
  ParameterList_atParameterType[v21].isUsed = false;
  v24 = Level_eParameterTypeReal32x9Exact;
  ParameterList_atParameterType[v22].isUsed = false;
  v25 = Level_eParameterTypeInt32;
  ParameterList_atParameterType[v23].isUsed = false;
  v26 = Level_eParameterTypeInt16;
  ParameterList_atParameterType[v24].isUsed = false;
  v27 = Level_eParameterTypeVarString;
  ParameterList_atParameterType[v25].isUsed = false;
  v28 = Level_eParameterTypeFixedString;
  ParameterList_atParameterType[v26].isUsed = false;
  v29 = Level_eParameterTypeString16;
  ParameterList_atParameterType[v27].isUsed = false;
  v30 = Level_eParameterTypeString32;
  ParameterList_atParameterType[v28].isUsed = false;
  v31 = Level_eParameterTypeString256;
  ParameterList_atParameterType[v29].isUsed = false;
  v32 = Level_eParameterTypeLevelExpression;
  ParameterList_atParameterType[v30].isUsed = false;
  v33 = Level_eParameterTypeQTaskNote;
  ParameterList_atParameterType[v31].isUsed = false;
  ParameterList_atParameterType[v32].isUsed = false;
  ParameterList_atParameterType[v33].isUsed = false;
  v34 = Level_eParameterPrintParameterEvent;
  v35 = Level_eParameterPrintExParameterEvent;
  ParameterList_atParameterType[Level_eParameterTypebool8].isUsed = false;
  LOWORD(v31) = Level_eSaveQTaskQTaskEvent;
  ParameterList_atParameterEvent[v34].isUsed = false;
  ParameterList_atParameterEvent[v35].isUsed = false;
  QTask_DeleteQTaskEvent(v31);
  QTask_DeleteQTaskEvent(Level_eAllowSaveQTaskEvent);
  QTask_DeleteQTaskEvent(Level_ePrintQTaskInfoQTaskEvent);
  QTask_DeleteQTaskEvent(Level_eGetUniqueQTaskNameEvent);
  QTask_DeleteQTaskEvent(Level_eGetLevelQTaskRangeQTaskEvent);
  QTask_DeleteQTaskEventNoContext(Level_eRegisterLevelScriptSymbolsEvent);
  QTask_DeleteQTaskEventNoContext(Level_eRemoveLevelScriptSymbolsEvent);
  QTask_DeleteQTaskEventNoContext(Level_eUpdateInternalDataAfterLoadEvent);
  Level_ePrintQTaskInfoQTaskEvent = 512;
  Level_eGetUniqueQTaskNameEvent = 512;
  Level_eRegisterLevelScriptSymbolsEvent = 512;
  Level_eRemoveLevelScriptSymbolsEvent = 512;
  Level_eUpdateInternalDataAfterLoadEvent = 512;
  QTask_DeleteQTaskType(Level_eStaticQTaskType);
  QTask_DeleteQTaskType(Level_eDynamicQTaskType);
  QTask_DeleteQTaskType(Level_eIdleQTaskType);
  QTask_DeleteQTaskType(Level_eCameraBaseQTaskType);
  QTask_DeleteQTaskType(Level_eLevelQTaskType);
  v36 = Level_atLevelQTaskID;
  do
  {
    v37 = (struct MemPoolFreeItem_s *)*v36;
    if ( *v36 )
    {
      if ( v37->ptNext )
        v37 = (struct MemPoolFreeItem_s *)Node_Remove(v37);
      --QTask_tQTaskRefPool.nAllocatedBlocks;
      v37->ptNext = QTask_tQTaskRefPool.tMemPoolFreeList.ptHead;
      QTask_tQTaskRefPool.tMemPoolFreeList.ptHead = v37;
      *v36 = nullptr;
    }
    ++v36;
  }
  while ( (int)v36 < 127904760 );
}
