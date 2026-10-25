/* j/0/objects/glasscontainer.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/objects/glasscontainer.c:80  [anchor-mhash]
int __cdecl GlassContainer_GetChildIndex(struct QTask_s *ptChild, struct QTask_s *ptParent)
{
  struct QTask_s *ptHead; // ecx
  int result; // eax

  ptHead = ptParent->tQTaskChildren.ptHead;
  result = 0;
  if ( !ptHead->ptNext || !ptHead )
    return -1;
  while ( ptHead != ptChild )
  {
    if ( ptHead->ptNext )
      ptHead = ptHead->ptNext->ptNext != nullptr ? ptHead->ptNext : nullptr;
    else
      ptHead = nullptr;
    ++result;
    if ( !ptHead )
      return -1;
  }
  return result;
}

// source: j/0/objects/glasscontainer.c:114  [anchor-mhash]
char *__cdecl GlassContainer_MakeHashKey(char *zKey, struct QTask_s *ptQTask)
{
  char *v2; // ebx
  struct QTask_s *ptHead; // eax
  struct QTask_s *ptNext; // esi
  int v5; // edi
  int v6; // eax
  int v7; // eax
  int v8; // eax
  struct QReference_s *v9; // ecx
  struct QTask_s *ptParent; // eax
  struct QTask_s *v11; // eax
  int v12; // edx
  int v13; // eax
  struct QReference_s *v14; // ecx

  v2 = zKey;
  *zKey = 0;
  ptHead = ptQTask->ptParent->tQTaskChildren.ptHead;
  ptNext = ptQTask[8].ptNext;
  v5 = 0;
  if ( ptHead->ptNext && ptHead )
  {
    while ( ptHead != ptQTask )
    {
      if ( ptHead->ptNext )
        ptHead = ptHead->ptNext->ptNext != nullptr ? ptHead->ptNext : nullptr;
      else
        ptHead = nullptr;
      ++v5;
      if ( !ptHead )
        goto LABEL_8;
    }
    v6 = v5;
  }
  else
  {
LABEL_8:
    v6 = -1;
  }
  v7 = sprintf(v2, &stru_68C1E0.zFilename[16], v6);
LABEL_10:
  v2 += v7;
LABEL_11:
  v8 = 0;
  while ( 1 )
  {
    v9 = Level_atLevelQTaskID[v8];
    if ( v9 )
    {
      if ( v9->pxObject == ptNext )
        break;
    }
    if ( ++v8 >= 4096 )
    {
LABEL_18:
      if ( QTask_IsQTaskTypeDerived(ptNext->eQTaskType, ModelObj_eQTaskType) )
        v2 += sprintf(v2, &stru_68C1E0.zFilename[12], *(_DWORD *)&ptNext[2].eQTaskType + 20);
      ptParent = ptNext->ptParent;
      if ( ptParent )
      {
        v11 = ptParent->tQTaskChildren.ptHead;
        v12 = 0;
        if ( v11->ptNext && v11 )
        {
          while ( v11 != ptNext )
          {
            if ( v11->ptNext )
              v11 = v11->ptNext->ptNext != nullptr ? v11->ptNext : nullptr;
            else
              v11 = nullptr;
            ++v12;
            if ( !v11 )
              goto LABEL_28;
          }
          v7 = sprintf(v2, &stru_68C1E0.zFilename[16], v12);
          ptNext = ptNext->ptParent;
        }
        else
        {
LABEL_28:
          v7 = sprintf(v2, &stru_68C1E0.zFilename[16], -1);
          ptNext = ptNext->ptParent;
        }
      }
      else
      {
        if ( QTask_IsQTaskTypeDerived(ptNext->eQTaskType, MagicObjContainer_eQTaskType) == false )
          goto LABEL_11;
        v7 = sprintf(v2, &stru_68C1E0.zFilename[8]);
        ptNext = ptNext[1].ptNext;
      }
      goto LABEL_10;
    }
  }
  if ( v8 == -1 )
    goto LABEL_18;
  if ( QTask_IsQTaskTypeDerived(ptNext->eQTaskType, ModelObj_eQTaskType) )
    v2 += sprintf(v2, &stru_68C1E0.zFilename[12], *(_DWORD *)&ptNext[2].eQTaskType + 20);
  v13 = 0;
  while ( 1 )
  {
    v14 = Level_atLevelQTaskID[v13];
    if ( v14 )
    {
      if ( v14->pxObject == ptNext )
        break;
    }
    if ( ++v13 >= 4096 )
    {
      v13 = -1;
      return (char *)sprintf(v2, (char *const)&g_ptNetManager.tReceiveCounters.tCounters[9].nBytes, v13);
    }
  }
  return (char *)sprintf(v2, (char *const)&g_ptNetManager.tReceiveCounters.tCounters[9].nBytes, v13);
}

// source: j/0/objects/glasscontainer.c:177  [anchor-mhash]
void __cdecl GlassContainer_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *v2; // esi
  struct QTask_s *v3; // eax
  struct QTask_s *v4; // esi
  struct QTask_s *v5; // edi
  unsigned int v6; // eax
  struct QTask_s *v7; // esi
  struct QTask_s *v8; // edi
  unsigned int v9; // eax

  GlassContainer_ptGlassContainer = (struct GlassContainer_s *)ptQTask;
  v2 = (struct QTask_s *)Mem_AllocFn(256, 4);
  v3 = (struct QTask_s *)Mem_AllocFn(24, 4);
  v3->ptPrev = (struct QTask_s *)64;
  v3->tQTaskChildren.ptHead = (struct QTask_s *)32;
  v3->ptNext = nullptr;
  v3->tQTaskChildren.ptMiddle = nullptr;
  v3->tQTaskChildren.ptTail = v2;
  v3->tQTaskRefList.ptHead = nullptr;
  ptQTask[1].ptNext = v3;
  v4 = (struct QTask_s *)Mem_AllocFn(40, 4);
  v4->ptPrev = (struct QTask_s *)1024;
  v4->tQTaskChildren.ptMiddle = (struct QTask_s *)QHashTable_StringHashFunction;
  v4->tQTaskChildren.ptTail = (struct QTask_s *)QHashTable_StringCompareKeyFunction;
  v4->tQTaskRefList.ptHead = (struct QReference_s *)QHashTable_StringDuplicateKeyFunction;
  v4->tQTaskRefList.ptMiddle = (struct QReference_s *)QHashTable_CreateElementChained;
  v4->tQTaskRefList.ptTail = (struct QReference_s *)QHashTable_FindElementChained;
  v4->ptParent = (struct QTask_s *)QHashTable_DeleteElementChained;
  *(_DWORD *)&v4->eQTaskType = QHashTable_MapChained;
  v4->ptNext = nullptr;
  v5 = (struct QTask_s *)Mem_AllocFn(12288, 4);
  v6 = 0;
  v4->tQTaskChildren.ptHead = v5;
  memset(v5, 0, 0x3000u);
  do
  {
    *(struct QTask_s **)((char *)&v4->tQTaskChildren.ptHead->ptNext + v6) = (struct QTask_s *)((char *)&v4->tQTaskChildren.ptHead->ptPrev
                                                                                             + v6);
    *(char **)((char *)&v4->tQTaskChildren.ptHead->tQTaskChildren.ptHead + v6) = (char *)v4->tQTaskChildren.ptHead + v6;
    *(struct QTask_s **)((char *)&v4->tQTaskChildren.ptHead->ptPrev + v6) = nullptr;
    *(struct QTask_s **)((char *)&v4->tQTaskChildren.ptHead->tQTaskChildren.ptMiddle + v6) = (struct QTask_s *)((char *)&v4->tQTaskChildren.ptHead->tQTaskChildren.ptTail + v6);
    (&v4->tQTaskChildren.ptHead->tQTaskRefList.ptHead)[v6 / 4] = (struct QReference_s *)((char *)&v4->tQTaskChildren.ptHead->tQTaskChildren.ptMiddle
                                                                                       + v6);
    *(struct QTask_s **)((char *)&v4->tQTaskChildren.ptHead->tQTaskChildren.ptTail + v6) = nullptr;
    (&v4->tQTaskChildren.ptHead->tQTaskRefList.ptMiddle)[v6 / 4] = (struct QReference_s *)&(&v4->tQTaskChildren.ptHead->tQTaskRefList.ptTail)[v6 / 4];
    *(struct QTask_s **)((char *)&v4->tQTaskChildren.ptHead->ptParent + v6) = (struct QTask_s *)&(&v4->tQTaskChildren.ptHead->tQTaskRefList.ptMiddle)[v6 / 4];
    (&v4->tQTaskChildren.ptHead->tQTaskRefList.ptTail)[v6 / 4] = nullptr;
    *(_DWORD *)((char *)&v4->tQTaskChildren.ptHead->eQTaskType + v6) = (char *)v4->tQTaskChildren.ptHead + v6 + 40;
    *(struct QTask_s **)((char *)&v4->tQTaskChildren.ptHead[1].ptPrev + v6) = (struct QTask_s *)((char *)&v4->tQTaskChildren.ptHead->eQTaskType
                                                                                               + v6);
    *(struct QTask_s **)((char *)&v4->tQTaskChildren.ptHead[1].ptNext + v6) = nullptr;
    *(char **)((char *)&v4->tQTaskChildren.ptHead[1].tQTaskChildren.ptHead + v6) = (char *)v4->tQTaskChildren.ptHead
                                                                                 + v6
                                                                                 + 52;
    *(char **)((char *)&v4->tQTaskChildren.ptHead[1].tQTaskChildren.ptTail + v6) = (char *)v4->tQTaskChildren.ptHead
                                                                                 + v6
                                                                                 + 48;
    *(struct QTask_s **)((char *)&v4->tQTaskChildren.ptHead[1].tQTaskChildren.ptMiddle + v6) = nullptr;
    (&v4->tQTaskChildren.ptHead[1].tQTaskRefList.ptHead)[v6 / 4] = (struct QReference_s *)&(&v4->tQTaskChildren.ptHead[1].tQTaskRefList.ptMiddle)[v6 / 4];
    (&v4->tQTaskChildren.ptHead[1].tQTaskRefList.ptTail)[v6 / 4] = (struct QReference_s *)((char *)&v4->tQTaskChildren.ptHead[1].tQTaskRefList
                                                                                         + v6);
    (&v4->tQTaskChildren.ptHead[1].tQTaskRefList.ptMiddle)[v6 / 4] = nullptr;
    *(char **)((char *)&v4->tQTaskChildren.ptHead[1].ptParent + v6) = (char *)v4->tQTaskChildren.ptHead + v6 + 76;
    *(char **)((char *)&v4->tQTaskChildren.ptHead[2].ptNext + v6) = (char *)v4->tQTaskChildren.ptHead + v6 + 72;
    *(_DWORD *)((char *)&v4->tQTaskChildren.ptHead[1].eQTaskType + v6) = 0;
    *(char **)((char *)&v4->tQTaskChildren.ptHead[2].ptPrev + v6) = (char *)v4->tQTaskChildren.ptHead + v6 + 88;
    *(char **)((char *)&v4->tQTaskChildren.ptHead[2].tQTaskChildren.ptMiddle + v6) = (char *)v4->tQTaskChildren.ptHead
                                                                                   + v6
                                                                                   + 84;
    *(struct QTask_s **)((char *)&v4->tQTaskChildren.ptHead[2].tQTaskChildren.ptHead + v6) = nullptr;
    v6 += 96;
  }
  while ( v6 < 0x3000 );
  ptQTask[1].tQTaskChildren.ptHead = v4;
  v7 = (struct QTask_s *)Mem_AllocFn(40, 4);
  v7->ptPrev = (struct QTask_s *)1024;
  v7->tQTaskChildren.ptMiddle = (struct QTask_s *)QHashTable_StringHashFunction;
  v7->tQTaskChildren.ptTail = (struct QTask_s *)QHashTable_StringCompareKeyFunction;
  v7->tQTaskRefList.ptHead = (struct QReference_s *)QHashTable_StringDuplicateKeyFunction;
  v7->tQTaskRefList.ptMiddle = (struct QReference_s *)QHashTable_CreateElementChained;
  v7->tQTaskRefList.ptTail = (struct QReference_s *)QHashTable_FindElementChained;
  v7->ptParent = (struct QTask_s *)QHashTable_DeleteElementChained;
  *(_DWORD *)&v7->eQTaskType = QHashTable_MapChained;
  v7->ptNext = nullptr;
  v8 = (struct QTask_s *)Mem_AllocFn(12288, 4);
  v9 = 0;
  v7->tQTaskChildren.ptHead = v8;
  memset(v8, 0, 0x3000u);
  do
  {
    *(struct QTask_s **)((char *)&v7->tQTaskChildren.ptHead->ptNext + v9) = (struct QTask_s *)((char *)&v7->tQTaskChildren.ptHead->ptPrev
                                                                                             + v9);
    *(char **)((char *)&v7->tQTaskChildren.ptHead->tQTaskChildren.ptHead + v9) = (char *)v7->tQTaskChildren.ptHead + v9;
    *(struct QTask_s **)((char *)&v7->tQTaskChildren.ptHead->ptPrev + v9) = nullptr;
    *(struct QTask_s **)((char *)&v7->tQTaskChildren.ptHead->tQTaskChildren.ptMiddle + v9) = (struct QTask_s *)((char *)&v7->tQTaskChildren.ptHead->tQTaskChildren.ptTail + v9);
    (&v7->tQTaskChildren.ptHead->tQTaskRefList.ptHead)[v9 / 4] = (struct QReference_s *)((char *)&v7->tQTaskChildren.ptHead->tQTaskChildren.ptMiddle
                                                                                       + v9);
    *(struct QTask_s **)((char *)&v7->tQTaskChildren.ptHead->tQTaskChildren.ptTail + v9) = nullptr;
    (&v7->tQTaskChildren.ptHead->tQTaskRefList.ptMiddle)[v9 / 4] = (struct QReference_s *)&(&v7->tQTaskChildren.ptHead->tQTaskRefList.ptTail)[v9 / 4];
    *(struct QTask_s **)((char *)&v7->tQTaskChildren.ptHead->ptParent + v9) = (struct QTask_s *)&(&v7->tQTaskChildren.ptHead->tQTaskRefList.ptMiddle)[v9 / 4];
    (&v7->tQTaskChildren.ptHead->tQTaskRefList.ptTail)[v9 / 4] = nullptr;
    *(_DWORD *)((char *)&v7->tQTaskChildren.ptHead->eQTaskType + v9) = (char *)v7->tQTaskChildren.ptHead + v9 + 40;
    *(struct QTask_s **)((char *)&v7->tQTaskChildren.ptHead[1].ptPrev + v9) = (struct QTask_s *)((char *)&v7->tQTaskChildren.ptHead->eQTaskType
                                                                                               + v9);
    *(struct QTask_s **)((char *)&v7->tQTaskChildren.ptHead[1].ptNext + v9) = nullptr;
    *(char **)((char *)&v7->tQTaskChildren.ptHead[1].tQTaskChildren.ptHead + v9) = (char *)v7->tQTaskChildren.ptHead
                                                                                 + v9
                                                                                 + 52;
    *(char **)((char *)&v7->tQTaskChildren.ptHead[1].tQTaskChildren.ptTail + v9) = (char *)v7->tQTaskChildren.ptHead
                                                                                 + v9
                                                                                 + 48;
    *(struct QTask_s **)((char *)&v7->tQTaskChildren.ptHead[1].tQTaskChildren.ptMiddle + v9) = nullptr;
    (&v7->tQTaskChildren.ptHead[1].tQTaskRefList.ptHead)[v9 / 4] = (struct QReference_s *)&(&v7->tQTaskChildren.ptHead[1].tQTaskRefList.ptMiddle)[v9 / 4];
    (&v7->tQTaskChildren.ptHead[1].tQTaskRefList.ptTail)[v9 / 4] = (struct QReference_s *)((char *)&v7->tQTaskChildren.ptHead[1].tQTaskRefList
                                                                                         + v9);
    (&v7->tQTaskChildren.ptHead[1].tQTaskRefList.ptMiddle)[v9 / 4] = nullptr;
    *(char **)((char *)&v7->tQTaskChildren.ptHead[1].ptParent + v9) = (char *)v7->tQTaskChildren.ptHead + v9 + 76;
    *(char **)((char *)&v7->tQTaskChildren.ptHead[2].ptNext + v9) = (char *)v7->tQTaskChildren.ptHead + v9 + 72;
    *(_DWORD *)((char *)&v7->tQTaskChildren.ptHead[1].eQTaskType + v9) = 0;
    *(char **)((char *)&v7->tQTaskChildren.ptHead[2].ptPrev + v9) = (char *)v7->tQTaskChildren.ptHead + v9 + 88;
    *(char **)((char *)&v7->tQTaskChildren.ptHead[2].tQTaskChildren.ptMiddle + v9) = (char *)v7->tQTaskChildren.ptHead
                                                                                   + v9
                                                                                   + 84;
    *(struct QTask_s **)((char *)&v7->tQTaskChildren.ptHead[2].tQTaskChildren.ptHead + v9) = nullptr;
    v9 += 96;
  }
  while ( v9 < 0x3000 );
  ptQTask[1].ptPrev = v7;
}

// source: j/0/objects/glasscontainer.c:197  [anchor-mhash]
void __cdecl GlassContainer_RunHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptNext; // eax
  struct QTask_s *i; // esi
  int v3; // eax

  ptNext = ptQTask[1].ptNext;
  for ( i = nullptr; i < ptNext->ptNext; i = (struct QTask_s *)((char *)i + 1) )
  {
    v3 = *((_DWORD *)&ptNext->tQTaskChildren.ptTail->ptNext + (_DWORD)i);
    ((void (__cdecl *)(int))QTask_aatQTaskFinalEvent[GlassContainer_eGlassRunEvent][*(unsigned __int16 *)(v3 + 36)].pfHandler)(v3);
    ptNext = ptQTask[1].ptNext;
  }
}

// source: j/0/objects/glasscontainer.c:224  [anchor-mhash]
void __cdecl GlassContainer_DeleteHandler(struct QTask_s *ptQTask)
{
  QVector_Delete((struct QVector_s *)ptQTask[1].ptNext);
  QHashTable_Delete((struct QHashTable_s *)ptQTask[1].tQTaskChildren.ptHead);
  QHashTable_Delete((struct QHashTable_s *)ptQTask[1].ptPrev);
  GlassContainer_ptGlassContainer = nullptr;
}

// source: j/0/objects/glasscontainer.c:245  [anchor-mhash]
void __cdecl GlassContainer_SerializeGlassCallback(
        struct QTask_s *ptGlassQTask,
        struct SerializeContext_s *ptSerializeContext)
{
  File_printf(ptSerializeContext->ptFile, (char *)&stru_68C1E0);
}

// source: j/0/objects/glasscontainer.c:263  [anchor-mhash]
void __cdecl GlassContainer_SerializeHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *ptNext; // ebx
  struct QTask_s *i; // edi

  ptNext = ptQTask[1].ptNext;
  for ( i = nullptr; i < ptNext->ptNext; i = (struct QTask_s *)((char *)i + 1) )
    File_printf(*((struct File_s **)pxContext + 2), (char *)&stru_68C1E0);
}

// source: j/0/objects/glasscontainer.c:279  [anchor-mhash]
struct Result_s *__cdecl GlassContainer_DeSerializeScriptFunction(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct Result_s Rs; };
    struct { char igi2_o1[24]; char zHashKey[256]; };
    char igi2_extent[280];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QHashTable_s *ptDeSerializeQHashTable; // esi
  int v4; // eax

  if ( GlassContainer_ptGlassContainer && ptArgList->nArguments == 2 )
  {
    if ( ptArgList->isQVM )
    {
      igi2_frame.zHashKey[0] = 0;
      QVM_EvalArg(igi2_frame.zHashKey, 256, ptArgList, 0, 3);
    }
    else
    {
      Expression_EvalString(*ptArgList->aptExpression, igi2_frame.zHashKey, 256);
    }
    int igi2_element = Script_EvalArgInt(ptArgList, 1);
    ptDeSerializeQHashTable = GlassContainer_ptGlassContainer->ptDeSerializeQHashTable;
    v4 = ptDeSerializeQHashTable->tPrivate.pfHashFunction(ptDeSerializeQHashTable->tPrivate.nHashTableSize, igi2_frame.zHashKey);
    ptDeSerializeQHashTable->tPrivate.pfCreateElement(ptDeSerializeQHashTable, v4, (const void *)(igi2_frame.zHashKey), (const void *)(igi2_element));
  }
  igi2_frame.Rs.nResult = 0;
  igi2_frame.Rs.vResult = 0.0;
  igi2_frame.Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &igi2_frame.Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/objects/glasscontainer.c:301  [anchor-mhash]
void __cdecl GlassContainer_DeSerializeDoneHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct GlassContainer_s *v2; // ecx
  struct QVector_s *ptQVector; // eax
  unsigned int i; // ebp
  struct QTask_s *v5; // edi
  struct QHashTable_s *ptDeSerializeQHashTable; // esi
  int v7; // eax
  enum bool v8; // esi
  struct QHashTable_s *v9; // ecx
  int v10; // [esp-14h] [ebp-1Ch]
  struct QHashTable_s *v11; // [esp+4h] [ebp-4h]

  v2 = GlassContainer_ptGlassContainer;
  ptQVector = GlassContainer_ptGlassContainer->ptQVector;
  for ( i = 0; i < ptQVector->tPrivate.nElements; ++i )
  {
    v5 = (struct QTask_s *)ptQVector->tPrivate.papxElement[i];
    ptDeSerializeQHashTable = v2->ptDeSerializeQHashTable;
    v7 = ptDeSerializeQHashTable->tPrivate.pfHashFunction(
           ptDeSerializeQHashTable->tPrivate.nHashTableSize,
           &v5[8].tQTaskRefList.ptTail);
    v8 = ((int  (__cdecl *)(struct QHashTable_s *, unsigned int, const void *))ptDeSerializeQHashTable->tPrivate.pfFindElement)(ptDeSerializeQHashTable, v7, (const void *)(&v5[8].tQTaskRefList.ptTail));
    if ( v8 )
    {
      v11 = GlassContainer_ptGlassContainer->ptDeSerializeQHashTable;
      v10 = v11->tPrivate.pfHashFunction(v11->tPrivate.nHashTableSize, &v5[8].tQTaskRefList.ptTail);
      ((void  (__cdecl *)(struct QHashTable_s *, unsigned int, const void *))v11->tPrivate.pfDeleteElement)(v11, v10, (const void *)(&v5[8].tQTaskRefList.ptTail));
      --v8;
    }
    Glass_SetBroken(v5, v8);
    v2 = GlassContainer_ptGlassContainer;
    ptQVector = GlassContainer_ptGlassContainer->ptQVector;
  }
  v9 = v2->ptDeSerializeQHashTable;
  if ( v9->tPrivate.nEntries )
    v9->tPrivate.pfMap(v9, QHashTable_DeleteElementCallback, nullptr);
}

// source: j/0/objects/glasscontainer.c:343  [anchor-mhash]
char *__cdecl GlassContainer_RegisterGlass(struct QTask_s *ptQTask)
{
  struct QHashTable_s *ptQHashTable; // esi
  int v2; // eax

  if ( !GlassContainer_ptGlassContainer )
    QTask_NewFn(&Level_ptQLevelQTask->tQTask, GlassContainer_eQTaskType, nullptr);
  g_zKey = 0;
  GlassContainer_MakeHashKey(&g_zKey, ptQTask);
  ptQHashTable = GlassContainer_ptGlassContainer->ptQHashTable;
  v2 = ptQHashTable->tPrivate.pfHashFunction(ptQHashTable->tPrivate.nHashTableSize, &g_zKey);
  ptQHashTable->tPrivate.pfCreateElement(ptQHashTable, v2, (const void *)(&g_zKey), (const void *)(ptQTask));
  QVector_AddElement(GlassContainer_ptGlassContainer->ptQVector, ptQTask);
  return &g_zKey;
}

// source: j/0/objects/glasscontainer.c:375  [anchor-mhash]
char *__cdecl GlassContainer_RemoveGlass(struct QTask_s *ptQTask, char *zGlassContainerID)
{
  void *v2; // ebx
  struct QHashTable_s *ptQHashTable; // esi
  int v4; // eax

  if ( GlassContainer_ptGlassContainer )
  {
    ptQHashTable = GlassContainer_ptGlassContainer->ptQHashTable;
    v4 = ptQHashTable->tPrivate.pfHashFunction(ptQHashTable->tPrivate.nHashTableSize, zGlassContainerID);
    ((void  (__cdecl *)(struct QHashTable_s *, unsigned int, const void *))ptQHashTable->tPrivate.pfDeleteElement)(ptQHashTable, v4, (const void *)(zGlassContainerID));
    QVector_RemoveElementByPointer(GlassContainer_ptGlassContainer->ptQVector, v2);
  }
  return zGlassContainerID;
}

// source: j/0/objects/glasscontainer.c:395  [size]
int __cdecl GlassContainer_GetGlassRunQTaskEvent()
{
  return GlassContainer_eGlassRunEvent;
}

// source: j/0/objects/glasscontainer.c:408  [anchor-hash]
void __cdecl GlassContainer_Open()
{
  unsigned __int16 BaseQTaskType; // ax
  int v1; // eax
  unsigned __int16 v2; // si

  BaseQTaskType = QTask_GetBaseQTaskType();
  GlassContainer_eQTaskType = QTask_NewQTaskType((char *)&stru_68C1E0.nAsyncBytesRead, 52, BaseQTaskType, 0, 0);
  v1 = QTask_NewQTaskEventNoContextFn(0, "GlassRun");
  v2 = GlassContainer_eQTaskType;
  GlassContainer_eGlassRunEvent = v1;
  QTask_LinkQTaskEventHandlerFn(GlassContainer_eQTaskType, 0, GlassContainer_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v2, 1, GlassContainer_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v2, 2, GlassContainer_DeleteHandler);
  QTask_LinkQTaskEventHandlerFn(v2, Serialize_eSerializeQTaskEvent, GlassContainer_SerializeHandler);
  QTask_LinkQTaskEventHandlerFn(v2, Serialize_eDeSerializeDoneQTaskEvent, GlassContainer_DeSerializeDoneHandler);
  Symbol_Register(
    (char *)&stru_68C1E0.nAsyncBytesRead,
    GlassContainer_DeSerializeScriptFunction,
    nullptr,
    -1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
}

// source: j/0/objects/glasscontainer.c:428  [anchor-strings]
void __cdecl GlassContainer_Close()
{
  Symbol_Remove((char *)&stru_68C1E0.nAsyncBytesRead);
  QTask_DeleteQTaskEventNoContext(GlassContainer_eGlassRunEvent);
  QTask_DeleteQTaskType(GlassContainer_eQTaskType);
}
