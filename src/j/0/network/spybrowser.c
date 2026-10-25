/* j/0/network/spybrowser.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/network/spybrowser.c:79  [size]
unsigned __int16 __cdecl SpyBrowser_GetQTaskType()
{
  return SpyBrowser_eQTaskType;
}

// source: j/0/network/spybrowser.c:93  [size]
struct QTask_s *__cdecl SpyBrowser_New(
        struct QTask_s *ptParentQTask,
        struct SpyBrowserCreateContext_s *ptCreateContext)
{
  return QTask_NewFn(ptParentQTask, SpyBrowser_eQTaskType, ptCreateContext);
}

// source: j/0/network/spybrowser.c:112  [size]
void __cdecl SpyBrowser_RunHandler(struct QTask_s *ptQTask)
{
  ;
}

// source: j/0/network/spybrowser.c:128  [anchor-hash]
void __cdecl SpyBrowser_ClearSelection()
{
  QTask_GetFirstChildOfType(Flow_ptFlow->ptNetManagerQTask, SpyBrowser_eQTaskType)[1].tQTaskChildren.ptHead = (struct QTask_s *)-1;
}

// source: j/0/network/spybrowser.c:194  [anchor-hash]
void __cdecl SpyBrowser_RefreshUnresponsive()
{
  struct GServerListImplementation *ptNext; // edi
  struct DArrayImplementation *servers; // eax
  int count; // ecx
  int i; // esi
  struct in_addr *v4; // ebx
  char *v5; // eax

  ptNext = (struct GServerListImplementation *)QTask_GetFirstChildOfType(
                                                 Flow_ptFlow->ptNetManagerQTask,
                                                 SpyBrowser_eQTaskType)[1].ptNext;
  servers = ptNext->servers;
  count = servers->count;
  for ( i = 0; i < servers->count; ++i )
  {
    if ( i < 0 || i >= count )
      v4 = nullptr;
    else
      v4 = *(struct in_addr **)((char *)servers->list + i * servers->elemsize);
    if ( !ServerGetIntValue(
            (struct GServerImplementation *)v4,
            (char *)&g_zFileName.atSpriteResources[29].tSprite.nQAnimframes,
            0) )
    {
      v5 = inet_ntoa(*v4);
      ServerListAuxUpdate(ptNext, v5, v4[1].S_un.S_un_w.s_w1, 1, qt_info);
    }
    servers = ptNext->servers;
    count = servers->count;
  }
}

// source: j/0/network/spybrowser.c:240  [anchor-hash]
void __cdecl SpyBrowser_StatusRefreshList()
{
  struct GServerListImplementation *ptNext; // ebx
  struct DArrayImplementation *servers; // eax
  int count; // ecx
  int i; // esi
  struct in_addr *v4; // edi
  char *v5; // eax

  ptNext = (struct GServerListImplementation *)QTask_GetFirstChildOfType(
                                                 Flow_ptFlow->ptNetManagerQTask,
                                                 SpyBrowser_eQTaskType)[1].ptNext;
  servers = ptNext->servers;
  count = servers->count;
  for ( i = 0; i < servers->count; ++i )
  {
    if ( i < 0 || i >= count )
      v4 = nullptr;
    else
      v4 = *(struct in_addr **)((char *)servers->list + i * servers->elemsize);
    v5 = inet_ntoa(*v4);
    ServerListAuxUpdate(ptNext, v5, v4[1].S_un.S_un_w.s_w1, 1, qt_status);
    servers = ptNext->servers;
    count = servers->count;
  }
}

// source: j/0/network/spybrowser.c:277  [anchor-callee]
void __cdecl SpyBrowser_RemoveUnresponsive()
{
  #pragma pack(push, 1)
  union
  {
    struct { struct QTask_s *v36; };
    struct { char igi2_o1[4]; struct in_addr *v37; };
    struct { char igi2_o2[8]; int v38; };
    struct { char igi2_o3[12]; int v39; };
    struct { char igi2_o4[16]; unsigned __int16 *p_nQAnimframes; };
    struct { char igi2_o5[20]; int v41; };
    struct { char igi2_o6[24]; int (__cdecl *v42)(unsigned __int16 **, int); };
    struct { char igi2_o7[28]; int v43; };
    struct { char igi2_o8[32]; struct HashImplementation table; };
    char igi2_extent[52];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *ptNext; // ebx
  int v1; // edx
  struct QTask_s *ptPrev; // eax
  struct in_addr *v3; // ebp
  int s_w2; // eax
  ULONG S_addr; // ebx
  struct DArrayImplementation **v6; // eax
  int *v7; // edi
  int (__cdecl *v8)(unsigned __int16 **, int); // ecx
  int v9; // ebp
  int v10; // eax
  int v11; // esi
  char *v12; // eax
  int s_w1; // ebp
  struct DArrayImplementation **v14; // eax
  struct QTask_s *v15; // ecx
  int v16; // edi
  int v17; // esi
  bool v18; // cc
  int v19; // edx
  int v20; // esi
  int v21; // eax
  int *v22; // ecx
  struct HashImplementation *v23; // edi
  char **v24; // eax
  int v25; // eax
  struct HashImplementation *v26; // edi
  int (__cdecl **v27)(void *, int); // eax
  struct HashImplementation *v28; // edi
  char **v29; // eax
  struct QTask_s *v30; // edx
  int v31; // eax
  struct QTask_s *ptHead; // edi
  struct QTask_s **p_ptPrev; // ecx
  struct QTask_s *v34; // edi
  struct QTask_s *ptTail; // eax

  ptNext = QTask_GetFirstChildOfType(Flow_ptFlow->ptNetManagerQTask, SpyBrowser_eQTaskType)[1].ptNext;
  igi2_frame.v36 = ptNext;
  while ( 1 )
  {
    v1 = 0;
    igi2_frame.v38 = 0;
    if ( (int)ptNext->ptPrev->ptNext <= 0 )
      break;
    while ( 1 )
    {
      if ( v1 < 0 || (ptPrev = ptNext->ptPrev, v1 >= (int)ptPrev->ptNext) )
      {
        igi2_frame.v37 = nullptr;
        v3 = nullptr;
      }
      else
      {
        v3 = *(struct in_addr **)((char *)&ptPrev->tQTaskRefList.ptHead->ptNext + v1
                                                                                * (int)ptPrev->tQTaskChildren.ptHead);
        igi2_frame.v37 = v3;
      }
      if ( !strcmp((char *)&g_zFileName.atSpriteResources[29].tSprite.nQAnimframes, "ping") )
      {
        s_w2 = (__int16)v3[1].S_un.S_un_w.s_w2;
        goto LABEL_28;
      }
      S_addr = v3[4].S_un.S_addr;
      igi2_frame.p_nQAnimframes = &g_zFileName.atSpriteResources[29].tSprite.nQAnimframes;
      v6 = (struct DArrayImplementation **)(*(int (__cdecl **)(unsigned __int16 **, _DWORD))(S_addr + 12))(
                                             &igi2_frame.p_nQAnimframes,
                                             *(_DWORD *)(S_addr + 4));
      v7 = *(int **)(*(_DWORD *)S_addr + 4 * (_DWORD)v6);
      v8 = *(int (__cdecl **)(unsigned __int16 **, int))(S_addr + 16);
      igi2_frame.table.buckets = v6;
      igi2_frame.v42 = v8;
      if ( !v7 )
        goto LABEL_17;
      v9 = *v7;
      if ( !*v7 )
        break;
      igi2_frame.v41 = v7[2];
      v10 = v7[5];
      v11 = 0;
      igi2_frame.v43 = v10;
      if ( v9 <= 0 )
        break;
      igi2_frame.v39 = v10;
      while ( igi2_frame.v42(&igi2_frame.p_nQAnimframes, igi2_frame.v39) )
      {
        ++v11;
        igi2_frame.v39 += igi2_frame.v41;
        if ( v11 >= v9 )
          goto LABEL_16;
      }
      v20 = igi2_frame.v43 + igi2_frame.v41 * v11;
      if ( !v20 )
        break;
      v21 = (v20 - v7[5]) / v7[2];
      if ( v21 == -1 )
        break;
      v22 = (int *)(*(_DWORD *)(*(_DWORD *)(*(_DWORD *)S_addr + 4 * (int)igi2_frame.table.buckets) + 20)
                  + v21 * *(_DWORD *)(*(_DWORD *)(*(_DWORD *)S_addr + 4 * (int)igi2_frame.table.buckets) + 8));
      if ( !v22 )
        break;
      v23 = (struct HashImplementation *)igi2_frame.v37[3].S_un.S_addr;
      igi2_frame.table.nbuckets = *v22;
      v24 = (char **)TableLookup(v23, &igi2_frame.table.nbuckets);
      if ( !v24 )
        break;
      s_w2 = atoi(v24[1]);
      v3 = igi2_frame.v37;
      ptNext = igi2_frame.v36;
      v1 = igi2_frame.v38;
LABEL_28:
      if ( !s_w2 )
        goto LABEL_18;
      if ( !strcmp("ping", "ping") )
      {
        v25 = (__int16)v3[1].S_un.S_un_w.s_w2;
      }
      else
      {
        v26 = (struct HashImplementation *)v3[4].S_un.S_addr;
        igi2_frame.table.buckets = (struct DArrayImplementation **)"ping";
        v27 = (int (__cdecl **)(void *, int))TableLookup(v26, &igi2_frame.table);
        if ( !v27
          || (v28 = (struct HashImplementation *)v3[3].S_un.S_addr,
              igi2_frame.table.hashfn = *v27,
              (v29 = (char **)TableLookup(v28, &igi2_frame.table.hashfn)) == nullptr) )
        {
          v1 = igi2_frame.v38;
          goto LABEL_37;
        }
        v25 = atoi(v29[1]);
        v1 = igi2_frame.v38;
      }
      if ( v25 == 9999 )
        goto LABEL_18;
LABEL_37:
      igi2_frame.v38 = ++v1;
      if ( v1 >= (int)ptNext->ptPrev->ptNext )
        return;
    }
LABEL_16:
    v3 = igi2_frame.v37;
LABEL_17:
    ptNext = igi2_frame.v36;
LABEL_18:
    v12 = inet_ntoa(*v3);
    s_w1 = v3[1].S_un.S_un_w.s_w1;
    v14 = (struct DArrayImplementation **)inet_addr(v12);
    v15 = ptNext->ptPrev;
    v16 = (int)v15->ptNext;
    v17 = 0;
    v18 = (int)v15->ptNext <= 0;
    igi2_frame.table.buckets = v14;
    if ( !v18 )
    {
      while ( 1 )
      {
        v19 = *(int *)((char *)&v15->tQTaskRefList.ptHead->ptNext + v17 * (int)v15->tQTaskChildren.ptHead);
        if ( s_w1 == *(unsigned __int16 *)(v19 + 4) && *(struct DArrayImplementation ***)v19 == igi2_frame.table.buckets )
          break;
        if ( ++v17 >= v16 )
          goto LABEL_2;
      }
      if ( v17 == -1 )
      {
LABEL_2:
        ptNext = igi2_frame.v36;
        continue;
      }
      ptNext = igi2_frame.v36;
      if ( igi2_frame.v36->ptNext && (int)igi2_frame.v36[2].ptParent > v17 )
      {
        v30 = *(struct QTask_s **)((char *)&v15->tQTaskRefList.ptHead->ptNext + v17 * (int)v15->tQTaskChildren.ptHead);
        v31 = 0;
        if ( (int)igi2_frame.v36[2].tQTaskRefList.ptTail > 0 )
        {
          ptHead = igi2_frame.v36->tQTaskChildren.ptHead;
          p_ptPrev = &ptHead->ptPrev;
          while ( *p_ptPrev != v30 )
          {
            ++v31;
            p_ptPrev += 7;
            if ( v31 >= (int)igi2_frame.v36[2].tQTaskRefList.ptTail )
              goto LABEL_49;
          }
          if ( v31 != -1 )
            *((_DWORD *)&ptHead->ptPrev + 7 * v31) = 0;
        }
LABEL_49:
        --*(int *)&igi2_frame.v36[2].ptParent;
      }
      v34 = igi2_frame.v36->ptPrev;
      ptTail = v34->tQTaskChildren.ptTail;
      if ( ptTail )
        ((void (__cdecl *)(char *))ptTail)((char *)v34->tQTaskRefList.ptHead + v17 * (int)v34->tQTaskChildren.ptHead);
      if ( v17 < (int)(&v34->ptNext[-1].isInMemPool + 1) )
        memmove(
          (char *)v34->tQTaskRefList.ptHead + v17 * (int)v34->tQTaskChildren.ptHead,
          (char *)v34->tQTaskRefList.ptHead + (int)v34->tQTaskChildren.ptHead * (v17 + 1),
          (int)v34->tQTaskChildren.ptHead * ((int)v34->ptNext - v17 - 1));
      --*(int *)&v34->ptNext;
    }
  }
}

// source: j/0/network/spybrowser.c:401  [anchor-strings]
void __cdecl SpyBrowser_ListCallBack(
        struct GServerListImplementation *serverlist,
        int msg,
        void *instance,
        void *param1,
        void *param2)
{
  if ( msg == 1 )
  {
    switch ( serverlist->state )
    {
      case sl_idle:
      case sl_listxfer:
      case sl_lanlist:
      case sl_querying:
        return;
      default:
        NetManager_LogMessage("?UNKNOWN STATE\n");
        break;
    }
  }
}

// source: j/0/network/spybrowser.c:469  [anchor-caller]
void __cdecl SpyBrowser_StartUpdate(enum SpyBrowser_Net_e eNet, char *filter)
{
  unsigned __int16 v2; // dx
  struct Flow_t *v3; // esi
  struct QTask_s *FirstChildOfType; // ebp
  struct GServerListImplementation *v5; // edi
  int v6; // esi
  int v7; // eax
  int ServerListLANSocket; // eax
  int v9; // eax
  char *v10; // eax
  struct QTask_s *ptNext; // esi
  int ServerListSocket; // eax
  int v13; // eax
  int inited; // eax
  struct QTask_s *ptPrev; // ecx
  char *v16; // eax
  bool v17; // zf
  DWORD TickCount; // eax
  char Buffer[256]; // [esp+10h] [ebp-100h] BYREF

  v2 = SpyBrowser_eQTaskType;
  v3 = Flow_ptFlow;
  FirstChildOfType = QTask_GetFirstChildOfType(Flow_ptFlow->ptNetManagerQTask, SpyBrowser_eQTaskType);
  FirstChildOfType[1].tQTaskRefList.ptHead = nullptr;
  FirstChildOfType[1].tQTaskRefList.ptMiddle = nullptr;
  FirstChildOfType[1].tQTaskRefList.ptTail = nullptr;
  QTask_GetFirstChildOfType(v3->ptNetManagerQTask, v2)[1].tQTaskChildren.ptHead = (struct QTask_s *)-1;
  ServerListClear((struct GServerListImplementation *)FirstChildOfType[1].ptNext);
  if ( eNet )
  {
    ptNext = FirstChildOfType[1].ptNext;
    if ( ptNext->ptNext )
    {
      v6 = 4;
    }
    else
    {
      ptNext[3].tQTaskRefList.ptMiddle = (struct QReference_s *)5;
      ServerListSocket = CreateServerListSocket((struct GServerListImplementation *)ptNext);
      if ( ServerListSocket )
      {
        v6 = ServerListSocket;
      }
      else
      {
        v13 = SendListRequest((struct GServerListImplementation *)ptNext, filter);
        if ( v13 )
        {
          v6 = v13;
        }
        else
        {
          inited = InitUpdateList((struct GServerListImplementation *)ptNext);
          if ( inited )
          {
            v6 = inited;
          }
          else
          {
            ptPrev = ptNext->ptPrev;
            ptNext[2].ptParent = nullptr;
            *(_DWORD *)&ptNext[2].eQTaskType = 0;
            ptNext[3].ptParent = ptPrev->ptNext;
            ptNext[34].tQTaskChildren.ptMiddle = (struct QTask_s *)-1;
            v6 = 0;
          }
        }
      }
    }
    v16 = ServerListErrorDesc((struct GServerListImplementation *)FirstChildOfType[1].ptNext, v6);
    _snprintf(Buffer, 0xFFu, (char *const)&g_server.querytype, v6, v16);
    NetManager_LogMessage(Buffer);
    FirstChildOfType[1].ptPrev = (struct QTask_s *)2;
  }
  else
  {
    v5 = (struct GServerListImplementation *)FirstChildOfType[1].ptNext;
    if ( v5->state )
    {
      v6 = 4;
    }
    else
    {
      v7 = InitUpdateList((struct GServerListImplementation *)FirstChildOfType[1].ptNext);
      if ( v7 )
      {
        v6 = v7;
      }
      else
      {
        ServerListLANSocket = CreateServerListLANSocket(v5);
        if ( ServerListLANSocket )
        {
          v6 = ServerListLANSocket;
        }
        else
        {
          v9 = SendBroadcastRequest(v5, 26001, 26011, 1);
          v6 = 0;
          if ( v9 )
          {
            v6 = v9;
          }
          else
          {
            v5->nextupdate = 0;
            v5->abortupdate = 0;
          }
        }
      }
    }
    v10 = ServerListErrorDesc((struct GServerListImplementation *)FirstChildOfType[1].ptNext, v6);
    _snprintf(Buffer, 0xFFu, "GameSpy LAN search initated: %d, %s\n", v6, v10);
    NetManager_LogMessage(Buffer);
    FirstChildOfType[1].ptPrev = (struct QTask_s *)1;
  }
  v17 = Timer_isPerformanceCounter == 0;
  FirstChildOfType[1].ptParent = (struct QTask_s *)v6;
  if ( v17 )
    TickCount = GetTickCount();
  else
    TickCount = Timer_GetPerformanceCounter();
  FirstChildOfType[1].tQTaskChildren.ptMiddle = (struct QTask_s *)(TickCount - Timer_nStartTime - 10);
}

// source: j/0/network/spybrowser.c:522  [anchor-mhash]
struct Result_s *__cdecl SpyBrowser_IsItemEnabledCB(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  struct QTask_s *FirstChildOfType; // eax
  struct ArgList_s *v4; // edi
  struct QTask_s *v5; // esi
  int v6; // ebp
  struct ArgList_s *v7; // eax
  struct QTask_s *ptPrev; // ecx
  int port; // edi
  struct GServerImplementation *v10; // ebx
  char *StringValue; // eax
  double v13[3]; // [esp+Ch] [ebp-18h] BYREF

  FirstChildOfType = QTask_GetFirstChildOfType(Flow_ptFlow->ptNetManagerQTask, SpyBrowser_eQTaskType);
  v4 = ptArgList;
  v5 = FirstChildOfType;
  v6 = 0;
  if ( ptArgList->isQVM )
  {
    ptArgList = nullptr;
    QVM_EvalArg(&ptArgList, 4, v4, 0, 1);
    v7 = ptArgList;
  }
  else
  {
    v7 = (struct ArgList_s *)Expression_EvalInt(*ptArgList->aptExpression);
  }
  ptPrev = v5[1].ptNext->ptPrev;
  port = -1;
  if ( (int)v7 >= (int)ptPrev->ptNext )
    goto LABEL_11;
  if ( (int)v7 < 0 )
    goto LABEL_11;
  v10 = *(struct GServerImplementation **)((char *)&ptPrev->tQTaskRefList.ptHead->ptNext
                                         + (_DWORD)v7 * (int)ptPrev->tQTaskChildren.ptHead);
  if ( !v10 )
    goto LABEL_11;
  StringValue = ServerGetStringValue(v10, "gamever", (char *)&g_server);
  port = v10->port;
  if ( !strcmp(StringValue, g_zPlayer1) )
    v6 = 1;
  if ( port <= 0 || (LODWORD(v13[0]) = 1, !v6) )
LABEL_11:
    LODWORD(v13[0]) = 0;
  if ( port <= 0 || (ptArgList = (struct ArgList_s *)1, !v6) )
    ptArgList = nullptr;
  v13[1] = (double)(int)ptArgList;
  LODWORD(v13[2]) = &g_zInitialValue;
  qmemcpy(retstr, v13, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/network/spybrowser.c:587  [anchor-mhash]
struct Result_s *__cdecl SpyBrowser_SetSelectedCB(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  struct ArgList_s *v3; // edi
  struct ArgList_s *v4; // esi
  _DWORD v6[6]; // [esp+8h] [ebp-18h] BYREF

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
  QTask_GetFirstChildOfType(Flow_ptFlow->ptNetManagerQTask, SpyBrowser_eQTaskType)[1].tQTaskChildren.ptHead = (struct QTask_s *)v4;
  v6[0] = 0;
  v6[2] = 0;
  v6[3] = 0;
  v6[4] = &g_zInitialValue;
  qmemcpy(retstr, v6, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/network/spybrowser.c:612  [anchor-mhash]
struct Result_s *__cdecl SpyBrowser_GetSelectedCB(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  struct Result_s Rs; // [esp+Ch] [ebp-18h] BYREF

  Rs.nResult = (int)QTask_GetFirstChildOfType(Flow_ptFlow->ptNetManagerQTask, SpyBrowser_eQTaskType)[1].tQTaskChildren.ptHead;
  Rs.vResult = (double)Rs.nResult;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/network/spybrowser.c:630  [size]
struct Result_s *__cdecl SpyBrowser_SearchLanSessionsCB(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  SpyBrowser_StartUpdate(SPYBROWSER_LAN, nullptr);
  Rs.nResult = 0;
  Rs.vResult = 0.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/network/spybrowser.c:645  [size~]
struct Result_s *__cdecl SpyBrowser_MasterListCB(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  _DWORD v4[6]; // [esp+8h] [ebp-18h] BYREF

  SpyBrowser_StartUpdate(SPYBROWSER_INTERNET, nullptr);
  v4[0] = 0;
  v4[2] = 0;
  v4[3] = 0;
  v4[4] = &g_zInitialValue;
  qmemcpy(retstr, v4, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/network/spybrowser.c:677  [size~]
struct Result_s *__cdecl SpyBrowser_SortCB(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  #pragma pack(push, 1)
  union
  {
    struct { int (__cdecl *v9)(void *, void *); };
    struct { char igi2_o1[20]; _DWORD v10[6]; };
    char igi2_extent[44];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *FirstChildOfType; // eax
  struct ArgList_s *v4; // edi
  struct QTask_s *v5; // esi
  struct ArgList_s *v6; // edi
  struct GServerListImplementation *ptNext; // esi

  FirstChildOfType = QTask_GetFirstChildOfType(Flow_ptFlow->ptNetManagerQTask, SpyBrowser_eQTaskType);
  v4 = ptArgList;
  v5 = FirstChildOfType;
  if ( ptArgList->isQVM )
  {
    ptArgList = nullptr;
    QVM_EvalArg(&ptArgList, 4, v4, 0, 1);
    v6 = ptArgList;
  }
  else
  {
    v6 = (struct ArgList_s *)Expression_EvalInt(*ptArgList->aptExpression);
  }
  ptNext = (struct GServerListImplementation *)v5[1].ptNext;
  QTask_GetFirstChildOfType(Flow_ptFlow->ptNetManagerQTask, SpyBrowser_eQTaskType)[1].tQTaskChildren.ptHead = (struct QTask_s *)-1;
  switch ( (unsigned int)v6 )
  {
    case 0u:
      ptNext->sortkey = "ping";
      ptNext->sortascending = 1;
      goto LABEL_14;
    case 1u:
      ptNext->sortkey = "numplayers";
      goto LABEL_13;
    case 2u:
      ptNext->sortkey = &g_zFileName.atSpriteResources[29].zResourceFilename[60];
      ptNext->sortascending = 0;
      igi2_frame.v9 = StrNoCaseKeyCompare;
      goto LABEL_15;
    case 3u:
      ptNext->sortkey = "hostname";
      ptNext->sortascending = 1;
      igi2_frame.v9 = StrNoCaseKeyCompare;
      goto LABEL_15;
    case 4u:
      ptNext->sortkey = "mapname";
      ptNext->sortascending = 1;
      igi2_frame.v9 = StrNoCaseKeyCompare;
      goto LABEL_15;
    case 5u:
      ptNext->sortkey = "gamever";
      ptNext->sortascending = 1;
      igi2_frame.v9 = StrNoCaseKeyCompare;
      goto LABEL_15;
    case 6u:
      ptNext->sortkey = "password";
      goto LABEL_13;
    case 7u:
      ptNext->sortkey = "dedicated";
LABEL_13:
      ptNext->sortascending = 0;
LABEL_14:
      igi2_frame.v9 = IntKeyCompare;
LABEL_15:
      g_sortserverlist = ptNext;
      qsort(ptNext->servers->list, ptNext->servers->count, ptNext->servers->elemsize, igi2_frame.v9);
      igi2_frame.v10[0] = 0;
      igi2_frame.v10[2] = 0;
      igi2_frame.v10[3] = 0;
      igi2_frame.v10[4] = &g_zInitialValue;
      qmemcpy(retstr, igi2_frame.v10, sizeof(struct Result_s));
      return retstr;
    default:
      LDebug_Error("Bad sort method");
      abort();
  }
}

// source: j/0/network/spybrowser.c:746  [anchor-mhash]
struct Result_s *__cdecl SpyBrowser_PlayersOnlineCB(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct Result_s Rs; };
    struct { char igi2_o1[24]; char zTemp[256]; };
    char igi2_extent[280];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *FirstChildOfType; // eax

  FirstChildOfType = QTask_GetFirstChildOfType(Flow_ptFlow->ptNetManagerQTask, SpyBrowser_eQTaskType);
  _snprintf(
    igi2_frame.zTemp,
    0x100u,
    (char *const)&g_ptNetManager.tReceiveCounters.tCounters[9].nBytes,
    FirstChildOfType[1].tQTaskRefList.ptHead);
  MenuText_SetText(-1, igi2_frame.zTemp);
  igi2_frame.Rs.nResult = 0;
  igi2_frame.Rs.vResult = 0.0;
  igi2_frame.Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &igi2_frame.Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/network/spybrowser.c:772  [anchor-strings]
struct Result_s *__cdecl SpyBrowser_ServersOnlineCB(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct Result_s Rs; };
    struct { char igi2_o1[24]; char zTemp[256]; };
    char igi2_extent[280];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *FirstChildOfType; // eax

  FirstChildOfType = QTask_GetFirstChildOfType(Flow_ptFlow->ptNetManagerQTask, SpyBrowser_eQTaskType);
  _snprintf(
    igi2_frame.zTemp,
    0x100u,
    "%d / %d",
    FirstChildOfType[1].tQTaskRefList.ptTail,
    FirstChildOfType[1].tQTaskRefList.ptMiddle);
  MenuText_SetText(-1, igi2_frame.zTemp);
  igi2_frame.Rs.nResult = 0;
  igi2_frame.Rs.vResult = 0.0;
  igi2_frame.Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &igi2_frame.Rs, sizeof(struct Result_s));
  return retstr;
}

struct Result_s *__cdecl sub_492540(struct Result_s *retstr)
{
  #pragma pack(push, 1)
  union
  {
    struct { _DWORD v4[6]; };
    struct { char igi2_o1[24]; char Buffer[256]; };
    char igi2_extent[280];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *ptParent; // eax
  char *LocalizedStringForLanguage; // eax

  ptParent = QTask_GetFirstChildOfType(Flow_ptFlow->ptNetManagerQTask, SpyBrowser_eQTaskType)[1].ptParent;
  if ( !ptParent || ptParent == (struct QTask_s *)4 )
  {
    _snprintf(igi2_frame.Buffer, 0x100u, (char *const)&g_zInitialValue);
  }
  else
  {
    LocalizedStringForLanguage = Config_GetLocalizedStringForLanguage(
                                   (char *)&key_694ffc.keylist,
                                   Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eLanguage,
                                   true);
    _snprintf(igi2_frame.Buffer, 0x100u, LocalizedStringForLanguage);
  }
  MenuText_SetText(-1, igi2_frame.Buffer);
  igi2_frame.v4[0] = 0;
  igi2_frame.v4[2] = 0;
  igi2_frame.v4[3] = 0;
  igi2_frame.v4[4] = &g_zInitialValue;
  qmemcpy(retstr, igi2_frame.v4, sizeof(struct Result_s));
  return retstr;
}

struct Result_s *__cdecl sub_492600(struct Result_s *retstr)
{
  struct QTask_s *ptParent; // eax
  _DWORD v3[6]; // [esp+8h] [ebp-18h] BYREF

  ptParent = QTask_GetFirstChildOfType(Flow_ptFlow->ptNetManagerQTask, SpyBrowser_eQTaskType)[1].ptParent;
  if ( !ptParent || ptParent == (struct QTask_s *)4 )
  {
    v3[0] = 0;
    v3[3] = 0;
  }
  else
  {
    v3[0] = 1;
    v3[3] = 1072693248;
  }
  v3[4] = &g_zInitialValue;
  v3[2] = 0;
  qmemcpy(retstr, v3, sizeof(struct Result_s));
  return retstr;
}

struct Result_s *__cdecl sub_492670(struct Result_s *retstr)
{
  _DWORD v2[6]; // [esp+8h] [ebp-18h] BYREF

  MenuText_SetText(-1, (char *)&key_694ffc.keyvals);
  v2[0] = 0;
  v2[2] = 0;
  v2[3] = 0;
  v2[4] = &g_zInitialValue;
  qmemcpy(retstr, v2, sizeof(struct Result_s));
  return retstr;
}

struct Result_s *__cdecl sub_4926C0(struct Result_s *retstr)
{
  _DWORD v2[6]; // [esp+8h] [ebp-18h] BYREF

  MenuText_SetText(-1, (char *)&key_694ffc.querytype);
  v2[0] = 0;
  v2[2] = 0;
  v2[3] = 0;
  v2[4] = &g_zInitialValue;
  qmemcpy(retstr, v2, sizeof(struct Result_s));
  return retstr;
}

struct Result_s *__cdecl sub_492710(struct Result_s *retstr)
{
  _DWORD v2[6]; // [esp+8h] [ebp-18h] BYREF

  MenuText_SetText(-1, (char *)&key_694ffc.port);
  v2[0] = 0;
  v2[2] = 0;
  v2[3] = 0;
  v2[4] = &g_zInitialValue;
  qmemcpy(retstr, v2, sizeof(struct Result_s));
  return retstr;
}

struct Result_s *__cdecl sub_492760(struct Result_s *retstr)
{
  #pragma pack(push, 1)
  union
  {
    struct { char *v12; };
    struct { char igi2_o1[4]; char *v13; };
    struct { char igi2_o2[8]; char *v14; };
    struct { char igi2_o3[12]; _DWORD v15[6]; };
    struct { char igi2_o4[36]; char Buffer[256]; };
    struct { char igi2_o5[292]; char zText[256]; };
    char igi2_extent[548];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *FirstChildOfType; // eax
  struct QTask_s *ptNext; // ecx
  int ptHead; // eax
  int *ptPrev; // ecx
  struct GServerImplementation *v5; // ebx
  char *StringValue; // esi
  char *v7; // edi
  char *v8; // ebp
  char *v9; // eax
  int IntValue; // eax

  FirstChildOfType = QTask_GetFirstChildOfType(Flow_ptFlow->ptNetManagerQTask, SpyBrowser_eQTaskType);
  ptNext = FirstChildOfType[1].ptNext;
  ptHead = (int)FirstChildOfType[1].tQTaskChildren.ptHead;
  if ( ptHead >= 0
    && (ptPrev = (int *)ptNext->ptPrev, ptHead < *ptPrev)
    && (v5 = *(struct GServerImplementation **)(ptHead * ptPrev[2] + ptPrev[5])) != nullptr )
  {
    StringValue = ServerGetStringValue(
                    v5,
                    &g_zFileName.atSpriteResources[29].zResourceFilename[48],
                    (char *)&key_694ffc);
    v7 = ServerGetStringValue(v5, (char *)&g_zFileName.atSpriteResources[29].tSprite.atQAnimframe, (char *)&key_694ffc);
    ServerGetStringValue(v5, (char *)&g_zFileName.atSpriteResources[18].tSprite.atQAnimframe, (char *)&key_694ffc);
    v8 = ServerGetStringValue(v5, "sniper", (char *)&key_694ffc);
    ServerGetStringValue(v5, "bwidth", (char *)&key_694ffc);
    ServerGetStringValue(v5, "maxout", (char *)&key_694ffc);
    igi2_frame.v12 = ServerGetStringValue(v5, "timeleft", (char *)&key_694ffc);
    igi2_frame.v13 = ServerGetStringValue(v5, "mapstat", (char *)&key_694ffc);
    if ( v5->port == ServerGetIntValue(v5, "hostport", 0) )
    {
      v9 = inet_ntoa((*(struct in_addr *)&v5->ip));
      _snprintf(igi2_frame.Buffer, 0xFFu, "%s:%d", v9, v5->port);
    }
    else
    {
      igi2_frame.v14 = inet_ntoa((*(struct in_addr *)&v5->ip));
      IntValue = ServerGetIntValue(v5, "hostport", 0);
      _snprintf(igi2_frame.Buffer, 0xFFu, "%s:[%d]", igi2_frame.v14, IntValue);
    }
    _snprintf(
      igi2_frame.zText,
      0x100u,
      "roundtime_%s  %s  balance_%s  snipers_%s  spectate_%s  IP_%s",
      igi2_frame.v12,
      igi2_frame.v13,
      StringValue,
      v8,
      v7,
      igi2_frame.Buffer);
  }
  else
  {
    _snprintf(igi2_frame.zText, 0x100u, (char *const)&g_zInitialValue);
  }
  MenuText_SetText(-1, igi2_frame.zText);
  igi2_frame.v15[0] = 0;
  igi2_frame.v15[2] = 0;
  igi2_frame.v15[3] = 0;
  igi2_frame.v15[4] = &g_zInitialValue;
  qmemcpy(retstr, igi2_frame.v15, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/network/spybrowser.c:798  [anchor-mhash]
struct Result_s *__cdecl SpyBrowser_FillColumnViewCB(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  #pragma pack(push, 1)
  union
  {
    struct { int IntValue; };
    struct { char igi2_o1[20]; struct QReference_s *v46; };
    struct { char igi2_o2[24]; int v47; };
    struct { char igi2_o3[28]; struct QReference_s *v48; };
    struct { char igi2_o4[32]; struct QTask_s *v49; };
    struct { char igi2_o5[36]; struct HashImplementation table; };
    struct { char igi2_o6[56]; struct QTask_s *v51; };
    struct { char igi2_o7[60]; int elemKey; };
    struct { char igi2_o8[68]; struct HashImplementation v53; };
    struct { char igi2_o9[92]; int v54; };
    struct { char igi2_o10[100]; _DWORD v55[6]; };
    struct { char igi2_o11[124]; char Buffer[2]; };
    struct { char igi2_o12[126]; char v57; };
    struct { char igi2_o13[131]; char v58; };
    struct { char igi2_o14[133]; char v59; };
    struct { char igi2_o15[143]; char v60; };
    struct { char igi2_o16[158]; char v61; };
    char igi2_extent[380];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *FirstChildOfType; // esi
  struct QTask_s *ptNext; // edi
  int *ptPrev; // eax
  int v6; // ecx
  struct GServerImplementation *v7; // ebx
  struct QObjectVector_s *ptEntryIDVector; // esi
  struct QObjectVector_s **p_ptEntryIDVector; // edi
  unsigned int nAllocated; // eax
  int *v11; // ecx
  int v12; // ebp
  char *v13; // eax
  struct HashImplementation *keylist; // edi
  int *v15; // eax
  struct HashImplementation *keyvals; // edi
  void *v17; // eax
  char *v18; // eax
  struct HashImplementation *v19; // edi
  int *v20; // eax
  struct HashImplementation *v21; // edi
  void *v22; // eax
  char *v23; // eax
  struct HashImplementation *v24; // edi
  int (__cdecl **v25)(void *, void *); // eax
  struct HashImplementation *v26; // edi
  void *v27; // eax
  char *v28; // ecx
  struct HashImplementation *v29; // edi
  struct DArrayImplementation ***v30; // eax
  struct HashImplementation *v31; // edi
  void *v32; // eax
  int v33; // eax
  __int16 ping; // ax
  char *v35; // eax
  struct HashImplementation *v36; // edi
  void (__cdecl **v37)(void *); // eax
  struct HashImplementation *v38; // edi
  void *v39; // eax
  struct QReference_s *v40; // edi
  bool v41; // cc
  bool v42; // zf
  struct ColumnView_s *v43; // eax

  FirstChildOfType = QTask_GetFirstChildOfType(Flow_ptFlow->ptNetManagerQTask, SpyBrowser_eQTaskType);
  ptNext = FirstChildOfType[1].ptNext;
  igi2_frame.v51 = FirstChildOfType;
  igi2_frame.v46 = nullptr;
  igi2_frame.v48 = nullptr;
  igi2_frame.v49 = ptNext;
  ColumnView_DeleteEntries(ColumnView_ptActiveColumnView);
  FirstChildOfType[1].tQTaskRefList.ptMiddle = (struct QReference_s *)ptNext->ptPrev->ptNext;
  ptPrev = (int *)ptNext->ptPrev;
  v6 = 0;
  igi2_frame.v47 = 0;
  if ( *ptPrev > 0 )
  {
    while ( 1 )
    {
      if ( v6 < 0 || v6 >= *ptPrev )
        v7 = nullptr;
      else
        v7 = *(struct GServerImplementation **)(v6 * ptPrev[2] + ptPrev[5]);
      ptEntryIDVector = ColumnView_ptActiveColumnView->ptEntryIDVector;
      p_ptEntryIDVector = &ColumnView_ptActiveColumnView->ptEntryIDVector;
      if ( ptEntryIDVector->nAllocated == ptEntryIDVector->nSize )
        QObjectVector_Realloc(ColumnView_ptActiveColumnView->ptEntryIDVector, ptEntryIDVector->nReallocSize);
      nAllocated = ptEntryIDVector->nAllocated;
      v11 = (int *)ptEntryIDVector->papxElement[nAllocated];
      ptEntryIDVector->nAllocated = nAllocated + 1;
      v12 = (*p_ptEntryIDVector)->nAllocated - 1;
      *v11 = v12;
      if ( ServerGetIntValue(v7, "dedicated", 0) )
        _snprintf(igi2_frame.Buffer, 3u, (char *const)&key_694ffc.port);
      else
        _snprintf(igi2_frame.Buffer, 3u, (char *const)&g_zInitialValue);
      igi2_frame.v57 = 0;
      ColumnView_SetEntry(v12, igi2_frame.Buffer, 0, false);
      if ( ServerGetIntValue(v7, "password", 0) )
        _snprintf(igi2_frame.Buffer, 3u, (char *const)&key_694ffc.querytype);
      else
        _snprintf(igi2_frame.Buffer, 3u, (char *const)&g_zInitialValue);
      igi2_frame.v57 = 0;
      ColumnView_SetEntry(v12, igi2_frame.Buffer, 1, false);
      if ( !strcmp("hostname", "hostaddr") )
      {
        v13 = inet_ntoa((*(struct in_addr *)&v7->ip));
      }
      else
      {
        keylist = v7->keylist;
        igi2_frame.table.hashfn = (int (__cdecl *)(void *, int))"hostname";
        v15 = (int *)TableLookup(keylist, &igi2_frame.table.hashfn);
        if ( v15 && (keyvals = v7->keyvals, igi2_frame.elemKey = *v15, (v17 = TableLookup(keyvals, &igi2_frame.elemKey)) != nullptr) )
          v13 = *((char **)v17 + 1);
        else
          v13 = "-";
      }
      _snprintf(igi2_frame.Buffer, 0x23u, (char *const)&stru_6A4CDC.tDebugConsoleLineList.ptMiddle, v13);
      igi2_frame.v61 = 0;
      ColumnView_SetEntry(v12, igi2_frame.Buffer, 2, false);
      if ( !strcmp("gamever", "hostaddr") )
      {
        v18 = inet_ntoa((*(struct in_addr *)&v7->ip));
      }
      else
      {
        v19 = v7->keylist;
        igi2_frame.table.compfn = (int (__cdecl *)(void *, void *))"gamever";
        v20 = (int *)TableLookup(v19, &igi2_frame.table.compfn);
        if ( v20 && (v21 = v7->keyvals, igi2_frame.v54 = *v20, (v22 = TableLookup(v21, &igi2_frame.v54)) != nullptr) )
          v18 = *((char **)v22 + 1);
        else
          v18 = "-";
      }
      _snprintf(igi2_frame.Buffer, 8u, (char *const)&stru_6A4CDC.tDebugConsoleLineList.ptMiddle, v18);
      igi2_frame.v58 = 0;
      ColumnView_SetEntry(v12, igi2_frame.Buffer, 3, false);
      if ( !strcmp("mapname", "hostaddr") )
      {
        v23 = inet_ntoa((*(struct in_addr *)&v7->ip));
      }
      else
      {
        v24 = v7->keylist;
        igi2_frame.table.freefn = (void (__cdecl *)(void *))"mapname";
        v25 = (int (__cdecl **)(void *, void *))TableLookup(v24, &igi2_frame.table.freefn);
        if ( v25 && (v26 = v7->keyvals, igi2_frame.v53.compfn = *v25, (v27 = TableLookup(v26, &igi2_frame.v53.compfn)) != nullptr) )
          v23 = *((char **)v27 + 1);
        else
          v23 = "-";
      }
      _snprintf(igi2_frame.Buffer, 0x14u, (char *const)&stru_6A4CDC.tDebugConsoleLineList.ptMiddle, v23);
      igi2_frame.v60 = 0;
      ColumnView_SetEntry(v12, igi2_frame.Buffer, 4, false);
      if ( !strcmp(&g_zFileName.atSpriteResources[29].zResourceFilename[60], "hostaddr") )
      {
        v28 = inet_ntoa((*(struct in_addr *)&v7->ip));
      }
      else
      {
        v29 = v7->keylist;
        igi2_frame.table.buckets = (struct DArrayImplementation **)&g_zFileName.atSpriteResources[29].zResourceFilename[60];
        v30 = (struct DArrayImplementation ***)TableLookup(v29, &igi2_frame.table);
        if ( v30 && (v31 = v7->keyvals, igi2_frame.v53.buckets = *v30, (v32 = TableLookup(v31, &igi2_frame.v53)) != nullptr) )
          v28 = *((char **)v32 + 1);
        else
          v28 = "-";
      }
      ColumnView_SetEntry(v12, v28, 5, false);
      if ( ServerGetIntValue(v7, (char *)&g_zFileName.atSpriteResources[29].tSprite.nQAnimframes, 0) <= 0 )
      {
        _snprintf(igi2_frame.Buffer, 0xAu, "-");
      }
      else
      {
        igi2_frame.IntValue = ServerGetIntValue(v7, (char *)&g_zFileName.atSpriteResources[29].tSprite.nQAnimframes, 0);
        v33 = ServerGetIntValue(v7, "numplayers", 0);
        _snprintf(igi2_frame.Buffer, 0xAu, "%d/%d", v33, igi2_frame.IntValue);
        igi2_frame.v59 = 0;
      }
      ColumnView_SetEntry(v12, igi2_frame.Buffer, 6, false);
      ping = v7->ping;
      if ( ping >= 9999 )
      {
        _snprintf(igi2_frame.Buffer, 0xAu, "-");
      }
      else
      {
        _snprintf(igi2_frame.Buffer, 0xAu, (char *const)&g_ptNetManager.tReceiveCounters.tCounters[9].nBytes, ping);
        igi2_frame.v59 = 0;
      }
      ColumnView_SetEntry(v12, igi2_frame.Buffer, 7, false);
      if ( !strcmp("hostname", "hostaddr") )
      {
        v35 = inet_ntoa((*(struct in_addr *)&v7->ip));
      }
      else
      {
        v36 = v7->keylist;
        igi2_frame.table.nbuckets = (int)"hostname";
        v37 = (void (__cdecl **)(void *))TableLookup(v36, &igi2_frame.table.nbuckets);
        if ( v37 && (v38 = v7->keyvals, igi2_frame.v53.freefn = *v37, (v39 = TableLookup(v38, &igi2_frame.v53.freefn)) != nullptr) )
          v35 = *((char **)v39 + 1);
        else
          v35 = "(NONE)";
      }
      if ( strcmp("(NONE)", v35) )
        igi2_frame.v48 = (struct QReference_s *)((char *)igi2_frame.v48 + 1);
      v40 = (struct QReference_s *)((char *)igi2_frame.v46 + ServerGetIntValue(v7, "numplayers", 0));
      ptPrev = (int *)igi2_frame.v49->ptPrev;
      v41 = igi2_frame.v47 + 1 < *ptPrev;
      igi2_frame.v46 = v40;
      ++igi2_frame.v47;
      if ( !v41 )
        break;
      v6 = igi2_frame.v47;
    }
    FirstChildOfType = igi2_frame.v51;
  }
  v42 = FirstChildOfType[1].tQTaskChildren.ptHead == (struct QTask_s *)-1;
  v43 = ColumnView_ptActiveColumnView;
  FirstChildOfType[1].tQTaskRefList.ptHead = igi2_frame.v46;
  FirstChildOfType[1].tQTaskRefList.ptTail = igi2_frame.v48;
  if ( v42 )
  {
    v43->nActiveEntry = -1;
    v43->nActiveID = -1;
  }
  if ( v43->nActiveID == -1 || v43->nActiveEntry == -1 )
    QTask_GetFirstChildOfType(Flow_ptFlow->ptNetManagerQTask, SpyBrowser_eQTaskType)[1].tQTaskChildren.ptHead = (struct QTask_s *)-1;
  igi2_frame.v55[0] = 0;
  igi2_frame.v55[2] = 0;
  igi2_frame.v55[3] = 0;
  igi2_frame.v55[4] = &g_zInitialValue;
  qmemcpy(retstr, igi2_frame.v55, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/network/spybrowser.c:982  [anchor-strings]
struct Result_s *__cdecl SpyBrowser_SetSocketCB(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  #pragma pack(push, 1)
  union
  {
    struct { _DWORD v9[6]; };
    struct { char igi2_o1[24]; char Buffer[256]; };
    char igi2_extent[280];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *FirstChildOfType; // eax
  struct QTask_s *ptPrev; // ecx
  int ptHead; // eax
  struct in_addr *v6; // ebx
  char *v7; // eax

  FirstChildOfType = QTask_GetFirstChildOfType(Flow_ptFlow->ptNetManagerQTask, SpyBrowser_eQTaskType);
  ptPrev = FirstChildOfType[1].ptNext->ptPrev;
  ptHead = (int)FirstChildOfType[1].tQTaskChildren.ptHead;
  if ( ptHead < (int)ptPrev->ptNext )
  {
    if ( ptHead < 0 )
      v6 = nullptr;
    else
      v6 = *(struct in_addr **)((char *)&ptPrev->tQTaskRefList.ptHead->ptNext
                              + ptHead * (int)ptPrev->tQTaskChildren.ptHead);
    v7 = inet_ntoa(*v6);
    strncpy(AppContext_tAppContext.zIP, v7, 0x10u);
    AppContext_tAppContext.nPort = ServerGetIntValue((struct GServerImplementation *)v6, "hostport", 0);
    strncpy(AppContext_tAppContext.zPlayer, ClientConfig_tClientConfig.zPlayerName, 0x40u);
    _snprintf(
      igi2_frame.Buffer,
      0xFFu,
      "%s connecting to %s:%d...\n",
      AppContext_tAppContext.zPlayer,
      AppContext_tAppContext.zIP,
      AppContext_tAppContext.nPort);
    NetManager_LogMessage(igi2_frame.Buffer);
  }
  igi2_frame.v9[0] = 0;
  igi2_frame.v9[2] = 0;
  igi2_frame.v9[3] = 0;
  igi2_frame.v9[4] = &g_zInitialValue;
  qmemcpy(retstr, igi2_frame.v9, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/network/spybrowser.c:1030  [size]
struct Result_s *__cdecl SpyBrowser_SetManualSocketCB(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  #pragma pack(push, 1)
  union
  {
    struct { int nPort; };
    struct { char igi2_o1[4]; struct Result_s Rs; };
    struct { char igi2_o2[28]; char zTemp[256]; };
    char igi2_extent[284];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)

  if ( ptArgList && ptArgList->nArguments == 2 )
  {
    if ( ptArgList->isQVM )
    {
      igi2_frame.zTemp[0] = 0;
      QVM_EvalArg(igi2_frame.zTemp, 255, ptArgList, 1, 3);
    }
    else
    {
      Expression_EvalString(ptArgList->aptExpression[1], igi2_frame.zTemp, 255);
    }
    strncpy(AppContext_tAppContext.zIP, igi2_frame.zTemp, 0x10u);
    if ( ptArgList->isQVM )
    {
      igi2_frame.zTemp[0] = 0;
      QVM_EvalArg(igi2_frame.zTemp, 255, ptArgList, 0, 3);
    }
    else
    {
      Expression_EvalString(*ptArgList->aptExpression, igi2_frame.zTemp, 255);
    }
    scprintf(igi2_frame.zTemp, &g_ptNetManager.tReceiveCounters.tCounters[9].nBytes, &igi2_frame.nPort);
    AppContext_tAppContext.nPort = igi2_frame.nPort;
    strncpy(AppContext_tAppContext.zPlayer, ClientConfig_tClientConfig.zPlayerName, 0x40u);
  }
  _snprintf(
    igi2_frame.zTemp,
    0xFFu,
    "%s manually connecting to %s:%d...\n",
    AppContext_tAppContext.zPlayer,
    AppContext_tAppContext.zIP,
    AppContext_tAppContext.nPort);
  NetManager_LogMessage(igi2_frame.zTemp);
  igi2_frame.Rs.nResult = 0;
  igi2_frame.Rs.vResult = 0.0;
  igi2_frame.Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &igi2_frame.Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/network/spybrowser.c:1066  [size]
struct Result_s *__cdecl SpyBrowser_IsManualSocketValidCB(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  #pragma pack(push, 1)
  union
  {
    struct { int nPort; };
    struct { char igi2_o1[4]; int nIP[6]; };
    struct { char igi2_o2[28]; char zIP[256]; };
    struct { char igi2_o3[284]; char zPort[256]; };
    char igi2_extent[540];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v3; // esi
  int v4; // eax
  int v5; // ecx

  if ( !ptArgList || ptArgList->nArguments != 2 )
  {
    igi2_frame.nIP[0] = 0;
    igi2_frame.nIP[2] = 0;
    igi2_frame.nIP[3] = 0;
    goto LABEL_19;
  }
  if ( ptArgList->isQVM )
  {
    igi2_frame.zIP[0] = 0;
    QVM_EvalArg(igi2_frame.zIP, 255, ptArgList, 1, 3);
  }
  else
  {
    Expression_EvalString(ptArgList->aptExpression[1], igi2_frame.zIP, 255);
  }
  if ( ptArgList->isQVM )
  {
    igi2_frame.zPort[0] = 0;
    QVM_EvalArg(igi2_frame.zPort, 255, ptArgList, 0, 3);
  }
  else
  {
    Expression_EvalString(*ptArgList->aptExpression, igi2_frame.zPort, 255);
  }
  v3 = scprintf(igi2_frame.zIP, "%d.%d.%d.%d", igi2_frame.nIP, &igi2_frame.nIP[1], &igi2_frame.nIP[2], &igi2_frame.nIP[3]);
  v4 = scprintf(igi2_frame.zPort, &g_ptNetManager.tReceiveCounters.tCounters[9].nBytes, &igi2_frame.nPort);
  v5 = igi2_frame.nPort;
  if ( v3 == 4 && v4 == 1 && igi2_frame.nPort > 0 )
  {
    igi2_frame.nIP[0] = 1;
  }
  else
  {
    igi2_frame.nIP[0] = 0;
    if ( v3 != 4 || v4 != 1 )
      goto LABEL_16;
  }
  igi2_frame.nPort = 1;
  if ( v5 <= 0 )
LABEL_16:
    igi2_frame.nPort = 0;
  *(double *)&igi2_frame.nIP[2] = (double)igi2_frame.nPort;
LABEL_19:
  igi2_frame.nIP[4] = (int)&g_zInitialValue;
  qmemcpy(retstr, igi2_frame.nIP, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/network/spybrowser.c:1118  [anchor-mhash]
struct Result_s *__cdecl SpyBrowser_SetMaxPingCB(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  #pragma pack(push, 1)
  union
  {
    struct { int nMaxPing; };
    struct { char igi2_o1[4]; struct Result_s Rs; };
    struct { char igi2_o2[28]; char zTemp[256]; };
    char igi2_extent[284];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *FirstChildOfType; // esi

  FirstChildOfType = QTask_GetFirstChildOfType(Flow_ptFlow->ptNetManagerQTask, SpyBrowser_eQTaskType);
  if ( ptArgList && ptArgList->nArguments == 1 )
  {
    if ( ptArgList->isQVM )
    {
      igi2_frame.zTemp[0] = 0;
      QVM_EvalArg(igi2_frame.zTemp, 255, ptArgList, 0, 3);
    }
    else
    {
      Expression_EvalString(*ptArgList->aptExpression, igi2_frame.zTemp, 255);
    }
    if ( scprintf(igi2_frame.zTemp, &g_ptNetManager.tReceiveCounters.tCounters[9].nBytes, &igi2_frame.nMaxPing) == 1 && igi2_frame.nMaxPing >= 0 )
      FirstChildOfType[1].tQTaskChildren.ptTail = (struct QTask_s *)igi2_frame.nMaxPing;
  }
  igi2_frame.Rs.nResult = 0;
  igi2_frame.Rs.vResult = 0.0;
  igi2_frame.Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &igi2_frame.Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/network/spybrowser.c:1157  [anchor-mhash]
struct Result_s *__cdecl SpyBrowser_GetMaxPingCB(
        struct Result_s *retstr,
        void *pxData,
        struct ArgList_s *ptArgList)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct Result_s Rs; };
    struct { char igi2_o1[24]; char zTemp[256]; };
    char igi2_extent[280];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *FirstChildOfType; // eax
  char *v4; // eax
  int v5; // edx
  char v6; // cl

  FirstChildOfType = QTask_GetFirstChildOfType(Flow_ptFlow->ptNetManagerQTask, SpyBrowser_eQTaskType);
  _snprintf(
    igi2_frame.zTemp,
    0xFFu,
    (char *const)&g_ptNetManager.tReceiveCounters.tCounters[9].nBytes,
    FirstChildOfType[1].tQTaskChildren.ptTail);
  v4 = igi2_frame.zTemp;
  v5 = InputBox_ptActiveInputBox->zInputString - igi2_frame.zTemp;
  do
  {
    v6 = *v4;
    v4[v5] = *v4;
    ++v4;
  }
  while ( v6 );
  igi2_frame.Rs.nResult = 0;
  igi2_frame.Rs.vResult = 0.0;
  igi2_frame.Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &igi2_frame.Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/network/spybrowser.c:1181  [anchor-strings]
void __cdecl SpyBrowser_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QTask_s *v2; // eax

  v2 = (struct QTask_s *)ServerListNew(
                           "projectigi2r",
                           "projectigi2r",
                           "j4F9cY",
                           10,
                           SpyBrowser_ListCallBack,
                           1,
                           nullptr);
  ptQTask[1].ptParent = nullptr;
  ptQTask[1].ptPrev = nullptr;
  ptQTask[1].tQTaskRefList.ptHead = nullptr;
  ptQTask[1].tQTaskRefList.ptMiddle = nullptr;
  ptQTask[1].tQTaskRefList.ptTail = nullptr;
  ptQTask[1].ptNext = v2;
  ptQTask[1].tQTaskChildren.ptHead = (struct QTask_s *)-1;
  ptQTask[1].tQTaskChildren.ptTail = (struct QTask_s *)1000;
}

// source: j/0/network/spybrowser.c:1229  [anchor-hash]
void __cdecl SpyBrowser_ThinkList(struct SpyBrowser_s *ptSpyBrowser)
{
  DWORD v1; // eax
  DWORD v2; // eax
  struct GServerListImplementation *tGServerList; // eax
  enum SpyBrowser_Pass_e ePass; // eax

  if ( ptSpyBrowser->ePass )
  {
    v1 = Timer_isPerformanceCounter ? Timer_GetPerformanceCounter() : GetTickCount();
    if ( (int)(v1 - Timer_nStartTime - ptSpyBrowser->nLastRunUpdate) > 10 )
    {
      ServerListThink(ptSpyBrowser->tGServerList);
      v2 = Timer_isPerformanceCounter ? Timer_GetPerformanceCounter() : GetTickCount();
      ptSpyBrowser->nLastRunUpdate = v2 - Timer_nStartTime;
      tGServerList = ptSpyBrowser->tGServerList;
      if ( !tGServerList || tGServerList->state == sl_idle )
      {
        ePass = ptSpyBrowser->ePass;
        switch ( ePass )
        {
          case SPYBROWSER_PASS_LAN:
            ptSpyBrowser->ePass = SPYBROWSER_PASS_IDLE;
LABEL_13:
            SpyBrowser_RemoveUnresponsive();
            return;
          case SPYBROWSER_PASS_INTERNET_INIT:
            ptSpyBrowser->ePass = SPYBROWSER_PASS_INTERNET_RETRY;
            SpyBrowser_RefreshUnresponsive();
            break;
          case SPYBROWSER_PASS_INTERNET_RETRY:
            ptSpyBrowser->ePass = SPYBROWSER_PASS_INTERNET_FULL_STATUS;
            SpyBrowser_RemoveUnresponsive();
            SpyBrowser_StatusRefreshList();
            break;
          default:
            ptSpyBrowser->ePass = SPYBROWSER_PASS_IDLE;
            if ( ePass == SPYBROWSER_PASS_INTERNET_FULL_STATUS )
              goto LABEL_13;
            break;
        }
      }
    }
  }
}

// source: j/0/network/spybrowser.c:1285  [anchor-mhash]
void __cdecl SpyBrowser_DeleteHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptNext; // edi

  ptNext = ptQTask[1].ptNext;
  ArrayFree((struct DArrayImplementation *)ptNext->ptPrev);
  TableFree((struct HashImplementation *)ptNext[3].tQTaskRefList.ptTail);
  free(ptNext->tQTaskChildren.ptHead);
  free(ptNext);
  WSACleanup();
  ptQTask[1].ptNext = nullptr;
}

// source: j/0/network/spybrowser.c:1302  [anchor-hash]
void __cdecl SpyBrowser_Close()
{
  Symbol_Remove("SpyBrowser_MasterList");
  Symbol_Remove("SpyBrowser_SearchLanSessions");
  Symbol_Remove("SpyBrowser_SetSocket");
  Symbol_Remove("SpyBrowser_SetManualSocket");
  Symbol_Remove("SpyBrowser_IsManualSocketValidCB");
  Symbol_Remove("SpyBrowser_FillColumnView");
  Symbol_Remove("SpyBrowser_GetSelected");
  Symbol_Remove("SpyBrowser_SetSelected");
  Symbol_Remove("SpyBrowser_IsItemEnabled");
  Symbol_Remove("SpyBrowser_Sort");
  Symbol_Remove("SpyBrowser_PlayersOnline");
  Symbol_Remove("SpyBrowser_ServersOnline");
  Symbol_Remove("SpyBrowser_SearchStatus");
  Symbol_Remove("SpyBrowser_ServerDetails");
  Symbol_Remove("SpyBrowser_FFText");
  Symbol_Remove("SpyBrowser_DEText");
  Symbol_Remove("SpyBrowser_PWText");
  Symbol_Remove("SpyBrowser_IsSearchError");
  Symbol_Remove("SPYBROWSER_SORT_PING");
  Symbol_Remove("SPYBROWSER_SORT_NUMPLAYERS");
  Symbol_Remove("SPYBROWSER_SORT_FF");
  Symbol_Remove("SPYBROWSER_SORT_HOSTNAME");
  Symbol_Remove("SPYBROWSER_SORT_MAPNAME");
  Symbol_Remove("SPYBROWSER_SORT_VERSION");
  Symbol_Remove("SPYBROWSER_SORT_PASSWORD");
  Symbol_Remove("SPYBROWSER_SORT_DEDICATED");
  Symbol_Remove("SpyBrowser_SetMaxPing");
  Symbol_Remove("SpyBrowser_GetMaxPing");
  QTask_DeleteQTaskType(SpyBrowser_eQTaskType);
}

// source: j/0/network/spybrowser.c:1341  [anchor-strings]
void __cdecl SpyBrowser_Open()
{
  unsigned __int16 BaseQTaskType; // ax
  unsigned __int16 v1; // si

  BaseQTaskType = QTask_GetBaseQTaskType();
  v1 = QTask_NewQTaskType("SpyBrowser", 76, BaseQTaskType, 0, 0);
  SpyBrowser_eQTaskType = v1;
  QTask_LinkQTaskEventHandlerFn(v1, 0, SpyBrowser_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 1, (void (__cdecl *)(struct QTask_s *))SpyBrowser_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 2, SpyBrowser_DeleteHandler);
  Symbol_Register(
    "SpyBrowser_MasterList",
    SpyBrowser_MasterListCB,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "SpyBrowser_SearchLanSessions",
    SpyBrowser_SearchLanSessionsCB,
    nullptr,
    2,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "SpyBrowser_SetSocket",
    SpyBrowser_SetSocketCB,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "SpyBrowser_SetManualSocket",
    SpyBrowser_SetManualSocketCB,
    nullptr,
    2,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "SpyBrowser_IsManualSocketValidCB",
    SpyBrowser_IsManualSocketValidCB,
    nullptr,
    2,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "SpyBrowser_FillColumnView",
    SpyBrowser_FillColumnViewCB,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "SpyBrowser_Sort",
    SpyBrowser_SortCB,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "SpyBrowser_GetSelected",
    SpyBrowser_GetSelectedCB,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "SpyBrowser_SetSelected",
    SpyBrowser_SetSelectedCB,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "SpyBrowser_IsItemEnabled",
    SpyBrowser_IsItemEnabledCB,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "SpyBrowser_SetMaxPing",
    SpyBrowser_SetMaxPingCB,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "SpyBrowser_GetMaxPing",
    SpyBrowser_GetMaxPingCB,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "SpyBrowser_PlayersOnline",
    SpyBrowser_PlayersOnlineCB,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "SpyBrowser_ServersOnline",
    SpyBrowser_ServersOnlineCB,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "SpyBrowser_SearchStatus",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))sub_492540,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "SpyBrowser_IsSearchError",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))sub_492600,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "SpyBrowser_ServerDetails",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))sub_492760,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "SpyBrowser_FFText",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))sub_492670,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "SpyBrowser_PWText",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))sub_4926C0,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "SpyBrowser_DEText",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))sub_492710,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "SPYBROWSER_SORT_PING",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    nullptr,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "SPYBROWSER_SORT_NUMPLAYERS",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)1,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "SPYBROWSER_SORT_FF",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)2,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "SPYBROWSER_SORT_HOSTNAME",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)3,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "SPYBROWSER_SORT_MAPNAME",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)4,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "SPYBROWSER_SORT_VERSION",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)5,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "SPYBROWSER_SORT_PASSWORD",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)6,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "SPYBROWSER_SORT_DEDICATED",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)7,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
}
