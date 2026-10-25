/* j/0/network/gserverlist.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/network/gserverlist.c:114  [anchor-callee]
struct GServerListImplementation *__cdecl ServerListNew(
        char *gamename,
        char *enginename,
        char *seckey,
        int maxconcupdates,
        void *CallBackFn,
        int CallBackFnType,
        void *instance)
{
  struct GServerListImplementation *v8; // esi
  struct DArrayImplementation *v9; // edi
  struct HashImplementation *v10; // eax
  struct UpdateInfo *v11; // edi
  struct WSAData WSAData; // [esp+10h] [ebp-190h] BYREF

  v8 = (struct GServerListImplementation *)malloc(0x5B8u);
  v8->state = sl_idle;
  v9 = (struct DArrayImplementation *)malloc(0x18u);
  v9->count = 0;
  v9->capacity = 64;
  v9->elemsize = 4;
  v9->growby = 64;
  v9->elemfreefn = ServerFree;
  v9->list = malloc(0x100u);
  v8->servers = v9;
  v10 = TableNew2(4, 500, 4, GStringHash, GCaseInsensitiveCompare, GStringFree);
  v8->maxupdates = maxconcupdates;
  maxconcupdates *= 28;
  v8->keylist = v10;
  v11 = (struct UpdateInfo *)malloc(maxconcupdates);
  v8->updatelist = v11;
  memset(v11, 0, maxconcupdates);
  strcpy(v8->gamename, gamename);
  strcpy(v8->seckey, seckey);
  strcpy(v8->enginename, enginename);
  v8->CallBackFn = (void (__cdecl *)(struct GServerListImplementation *, int, void *, void *, void *))CallBackFn;
  v8->instance = instance;
  v8->sortkey = (char *)&g_zInitialValue;
  v8->auxinsertcount = 0;
  WSAStartup(0x101u, &WSAData);
  return v8;
}

// source: j/0/network/gserverlist.c:142  [anchor-mhash]
void __cdecl ServerListFree(struct GServerListImplementation *serverlist)
{
  ArrayFree(serverlist->servers);
  TableFree(serverlist->keylist);
  free(serverlist->updatelist);
  free(serverlist);
  WSACleanup();
}

// source: j/0/network/gserverlist.c:153  [anchor-callee]
int __cdecl InitUpdateList(struct GServerListImplementation *serverlist)
{
  int v1; // ebx
  int i; // edi
  struct UpdateInfo *updatelist; // edx

  v1 = 0;
  if ( serverlist->maxupdates > 0 )
  {
    for ( i = 0; ; ++i )
    {
      serverlist->updatelist[i].s = socket(2, 2, 17);
      updatelist = serverlist->updatelist;
      if ( updatelist[i].s == -1 )
        break;
      updatelist[i].currentserver = nullptr;
      serverlist->updatelist[i].starttime = 0;
      if ( ++v1 >= serverlist->maxupdates )
        return 0;
    }
    if ( !v1 )
      return 1;
    serverlist->maxupdates = v1;
  }
  return 0;
}

// source: j/0/network/gserverlist.c:176  [anchor-hash]
int __cdecl FreeUpdateList(struct GServerListImplementation *serverlist)
{
  int v1; // esi
  int v2; // edi

  v1 = 0;
  if ( serverlist->maxupdates > 0 )
  {
    v2 = 0;
    do
    {
      closesocket(serverlist->updatelist[v2].s);
      ++v1;
      ++v2;
    }
    while ( v1 < serverlist->maxupdates );
  }
  return 0;
}

// source: j/0/network/gserverlist.c:189  [anchor-strings]
int __cdecl CreateServerListSocket(struct GServerListImplementation *serverlist)
{
  struct hostent *v1; // eax
  SOCKET v3; // eax
  struct sockaddr_in saddr; // [esp+0h] [ebp-10h] BYREF

  saddr.sin_family = 2;
  saddr.sin_port = htons(0x70E4u);
  saddr.sin_addr.S_un.S_addr = inet_addr(ServerListHostname);
  if ( saddr.sin_addr.S_un.S_addr == -1 )
  {
    v1 = gethostbyname(ServerListHostname);
    if ( !v1 )
      return 2;
    saddr.sin_addr.S_un.S_addr = **(_DWORD **)v1->h_addr_list;
  }
  v3 = socket(2, 1, 6);
  serverlist->slsocket = v3;
  if ( v3 == -1 )
    return 1;
  if ( !connect(v3, (struct sockaddr *)&saddr, 16) )
    return 0;
  closesocket(serverlist->slsocket);
  return 3;
}

// source: j/0/network/gserverlist.c:221  [anchor-callee]
int __cdecl CreateServerListLANSocket(struct GServerListImplementation *serverlist)
{
  SOCKET v1; // eax
  int optval; // [esp+0h] [ebp-4h] BYREF

  optval = 1;
  v1 = socket(2, 2, 17);
  serverlist->slsocket = v1;
  return v1 == -1 || setsockopt(v1, 0xFFFF, 32, (char *)&optval, 4) != 0;
}

// source: j/0/network/gserverlist.c:238  [anchor-mhash]
struct GServerListImplementation *__cdecl ServerListModeChange(
        struct GServerListImplementation *serverlist,
        enum GServerListState newstate)
{
  void *instance; // [esp-Ch] [ebp-Ch]

  instance = serverlist->instance;
  serverlist->state = newstate;
  return ((struct GServerListImplementation *(__cdecl *)(struct GServerListImplementation *, int, void *, _DWORD, _DWORD))serverlist->CallBackFn)(
           serverlist,
           1,
           instance,
           0,
           0);
}

// source: j/0/network/gserverlist.c:248  [anchor-strings]
int __cdecl SendListRequest(struct GServerListImplementation *serverlist, char *filter)
{
  #pragma pack(push, 1)
  union
  {
    struct { void *instance; };
    struct { char igi2_o1[16]; char data[256]; };
    struct { char igi2_o2[272]; char result[64]; };
    char igi2_extent[336];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v2; // eax
  char *v4; // eax
  unsigned __int8 *v5; // esi
  unsigned __int8 v6; // dl
  unsigned __int8 v7; // al
  unsigned __int8 v8; // cl
  unsigned __int8 v9; // dl
  unsigned __int8 v10; // al
  int v11; // eax
  enum GQueryType querytype; // eax
  char *v13; // eax
  int v14; // eax

  v2 = recv(serverlist->slsocket, igi2_frame.data, 255, 0);
  if ( v2 == -1 )
    return 3;
  igi2_frame.data[v2] = 0;
  v4 = strstr(igi2_frame.data, "\\secure\\");
  if ( !v4 )
    return 5;
  v5 = (unsigned __int8 *)(v4 + 8);
  cengine_gs_encrypt((unsigned __int8 *)serverlist->seckey, 6, (unsigned __int8 *)v4 + 8, 6);
  v6 = v5[1];
  v7 = v5[2];
  *v5 ^= serverlist->seckey[0];
  v8 = v5[3];
  v5[1] = serverlist->seckey[1] ^ v6;
  v9 = v5[4];
  v5[2] = serverlist->seckey[2] ^ v7;
  v10 = v5[5];
  v5[3] = serverlist->seckey[3] ^ v8;
  v5[4] = serverlist->seckey[4] ^ v9;
  v5[5] = serverlist->seckey[5] ^ v10;
  cengine_gs_encode(v5, 6, (unsigned __int8 *)igi2_frame.result);
  sprintf(
    igi2_frame.data,
    "\\gamename\\%s\\gamever\\%s\\location\\0\\validate\\%s\\enctype\\2\\final\\\\queryid\\1.1\\",
    serverlist->enginename,
    "1.8",
    igi2_frame.result);
  v11 = send(serverlist->slsocket, igi2_frame.data, strlen(igi2_frame.data), 0);
  if ( v11 == -1 || !v11 )
    return 3;
  querytype = serverlist->querytype;
  if ( querytype == qt_grouprooms )
  {
    v13 = (char *)&unk_685958;
    serverlist->pistate = pi_fieldcount;
  }
  else if ( querytype == qt_masterinfo )
  {
    v13 = (char *)&unk_685950;
    serverlist->pistate = pi_fieldcount;
  }
  else
  {
    v13 = (char *)&unk_68594C;
  }
  if ( filter )
    sprintf(igi2_frame.data, "\\list\\%s\\gamename\\%s\\where\\%s\\final\\", v13, serverlist->gamename, filter);
  else
    sprintf(igi2_frame.data, "\\list\\%s\\gamename\\%s\\final\\", v13, serverlist->gamename);
  v14 = send(serverlist->slsocket, igi2_frame.data, strlen(igi2_frame.data), 0);
  if ( v14 == -1 || !v14 )
    return 3;
  igi2_frame.instance = serverlist->instance;
  serverlist->state = sl_listxfer;
  serverlist->CallBackFn(serverlist, 1, igi2_frame.instance, nullptr, nullptr);
  return 0;
}

// source: j/0/network/gserverlist.c:307  [anchor-strings]
int __cdecl SendBroadcastRequest(
        struct GServerListImplementation *serverlist,
        int startport,
        int endport,
        int delta)
{
  #pragma pack(push, 1)
  union
  {
    struct { SOCKET slsocket; };
    struct { char igi2_o1[16]; void *instance; };
    struct { char igi2_o2[32]; struct sockaddr_in saddr; };
    char igi2_extent[48];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v4; // esi
  u_short v5; // ax

  v4 = startport;
  igi2_frame.saddr.sin_family = 2;
  for ( igi2_frame.saddr.sin_addr.S_un.S_addr = -1; (__int16)v4 <= endport; v4 += delta )
  {
    v5 = htons(v4);
    igi2_frame.slsocket = serverlist->slsocket;
    igi2_frame.saddr.sin_port = v5;
    sendto(igi2_frame.slsocket, "\\status\\", 8, 0, (struct sockaddr *)&igi2_frame.saddr, 16);
  }
  igi2_frame.instance = serverlist->instance;
  serverlist->state = sl_lanlist;
  serverlist->CallBackFn(serverlist, 1, igi2_frame.instance, nullptr, nullptr);
  serverlist->lanstarttime = GetTickCount();
  return 0;
}

// source: j/0/network/gserverlist.c:328  [anchor-hash]
struct GServerListImplementation *__cdecl DoSyncLoop(struct GServerListImplementation *serverlist)
{
  struct GServerListImplementation *result; // eax

  result = (struct GServerListImplementation *)serverlist->state;
  if ( result )
  {
    do
    {
      switch ( (unsigned int)result )
      {
        case 1u:
          ServerListReadList(serverlist);
          break;
        case 2u:
          ServerListLANList(serverlist);
          break;
        case 3u:
          ServerListQueryLoop(serverlist);
          break;
        default:
          break;
      }
      Sleep(0xAu);
      result = (struct GServerListImplementation *)serverlist->state;
    }
    while ( serverlist->state );
  }
  return result;
}

// source: j/0/network/gserverlist.c:342  [anchor-mhash]
int __cdecl ServerListUpdate(struct GServerListImplementation *serverlist, int async)
{
  int result; // eax

  if ( serverlist->state )
    return 4;
  serverlist->querytype = qt_status;
  result = CreateServerListSocket(serverlist);
  if ( !result )
  {
    result = SendListRequest(serverlist, nullptr);
    if ( !result )
    {
      result = InitUpdateList(serverlist);
      if ( !result )
      {
        serverlist->nextupdate = 0;
        serverlist->abortupdate = 0;
        serverlist->auxinsertcount = serverlist->servers->count;
        serverlist->cryptkey.index = -1;
        if ( !async )
          DoSyncLoop(serverlist);
        return 0;
      }
    }
  }
  return result;
}

// source: j/0/network/gserverlist.c:350  [anchor-mhash]
int __cdecl ServerListUpdate2(
        struct GServerListImplementation *serverlist,
        int async,
        char *filter,
        enum GQueryType querytype)
{
  int result; // eax
  struct DArrayImplementation *servers; // ecx

  if ( serverlist->state )
    return 4;
  serverlist->querytype = querytype;
  result = CreateServerListSocket(serverlist);
  if ( !result )
  {
    result = SendListRequest(serverlist, filter);
    if ( !result
      && (querytype == qt_grouprooms || querytype == qt_masterinfo || (result = InitUpdateList(serverlist)) == 0) )
    {
      servers = serverlist->servers;
      serverlist->nextupdate = 0;
      serverlist->abortupdate = 0;
      serverlist->auxinsertcount = servers->count;
      serverlist->cryptkey.index = -1;
      if ( !async )
        DoSyncLoop(serverlist);
      return 0;
    }
  }
  return result;
}

// source: j/0/network/gserverlist.c:378  [anchor-caller]
int __cdecl ServerListLANUpdate(
        struct GServerListImplementation *serverlist,
        int async,
        int startsearchport,
        int endsearchport,
        int searchdelta)
{
  int result; // eax

  if ( serverlist->state )
    return 4;
  result = InitUpdateList(serverlist);
  if ( !result )
  {
    result = CreateServerListLANSocket(serverlist);
    if ( !result )
    {
      result = SendBroadcastRequest(serverlist, startsearchport, endsearchport, searchdelta);
      if ( !result )
      {
        serverlist->nextupdate = 0;
        serverlist->abortupdate = 0;
        if ( !async )
          DoSyncLoop(serverlist);
        return 0;
      }
    }
  }
  return result;
}

// source: j/0/network/gserverlist.c:402  [anchor-callee]
struct GServerImplementation *__cdecl ServerListAddServerData(
        struct GServerListImplementation *serverlist,
        char **fieldlist,
        int fieldcount,
        char *serverdata,
        enum GQueryType qtype)
{
  #pragma pack(push, 1)
  union
  {
    struct { int count; };
    struct { char igi2_o1[24]; struct GServerImplementation *server; };
    char igi2_extent[28];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct GServerImplementation *v5; // eax
  struct DArrayImplementation *servers; // ebx

  v5 = ServerNewData(fieldlist, fieldcount, serverdata, qtype, serverlist->keylist);
  servers = serverlist->servers;
  igi2_frame.count = servers->count;
  igi2_frame.server = v5;
  ArrayInsertAt(servers, &igi2_frame.server, igi2_frame.count);
  return igi2_frame.server;
}

// source: j/0/network/gserverlist.c:412  [anchor-strings]
struct GServerImplementation *__cdecl ServerListAddServer(
        struct GServerListImplementation *serverlist,
        unsigned int ip,
        unsigned __int16 port,
        enum GQueryType qtype)
{
  struct GServerImplementation *v5; // eax
  struct DArrayImplementation *servers; // ebx
  struct GServerImplementation *server; // [esp+0h] [ebp-4h] BYREF

  server = (struct GServerImplementation *)port;
  if ( !serverlist )
    return nullptr;
  v5 = ServerNew(ip, port, qtype, serverlist->keylist);
  servers = serverlist->servers;
  server = v5;
  ArrayInsertAt(servers, &server, servers->count);
  printf("\nServerListAddServer: Server added.\n");
  return server;
}

// source: j/0/network/gserverlist.c:430  [anchor-caller]
struct GServerImplementation *__cdecl ServerListInsertServer(
        struct GServerListImplementation *serverlist,
        unsigned int ip,
        unsigned __int16 port,
        int pos,
        enum GQueryType qtype)
{
  struct GServerImplementation *v5; // eax
  struct DArrayImplementation *servers; // ebx
  struct GServerImplementation *server; // [esp+4h] [ebp-4h] BYREF

  v5 = ServerNew(ip, port, qtype, serverlist->keylist);
  servers = serverlist->servers;
  server = v5;
  ArrayInsertAt(servers, &server, pos);
  return server;
}

// source: j/0/network/gserverlist.c:440  [anchor-callee]
int __cdecl ServerListFindServerMax(
        struct GServerListImplementation *serverlist,
        unsigned int ip,
        int port,
        int maxcheck)
{
  int result; // eax
  struct DArrayImplementation *servers; // ecx
  int elemsize; // edx
  char *list; // esi
  int v8; // ecx

  result = 0;
  if ( maxcheck <= 0 )
    return -1;
  servers = serverlist->servers;
  elemsize = servers->elemsize;
  list = (char *)servers->list;
  while ( 1 )
  {
    v8 = *(_DWORD *)&list[result * elemsize];
    if ( port == *(unsigned __int16 *)(v8 + 4) && *(_DWORD *)v8 == ip )
      break;
    if ( ++result >= maxcheck )
      return -1;
  }
  return result;
}

// source: j/0/network/gserverlist.c:457  [anchor-caller]
int __cdecl ServerListFindServer(
        struct GServerListImplementation *serverlist,
        unsigned int ip,
        int port)
{
  return ServerListFindServerMax(serverlist, ip, port, serverlist->servers->count);
}

// source: j/0/network/gserverlist.c:464  [anchor-callee]
int __cdecl ServerListFindServerInUpdateList(
        struct GServerListImplementation *serverlist,
        struct GServerImplementation *server)
{
  int maxupdates; // edx
  int result; // eax
  struct GServerImplementation **i; // ecx

  maxupdates = serverlist->maxupdates;
  result = 0;
  if ( maxupdates <= 0 )
    return -1;
  for ( i = &serverlist->updatelist->currentserver; *i != server; i += 7 )
  {
    if ( ++result >= maxupdates )
      return -1;
  }
  return result;
}

// source: j/0/network/gserverlist.c:479  [anchor-caller]
char *__cdecl ServerListRemoveServer(struct GServerListImplementation *serverlist, char *ip, int port)
{
  unsigned int v3; // eax
  struct DArrayImplementation *servers; // esi
  char *result; // eax
  char *v6; // edi
  int ServerInUpdateList; // eax

  v3 = inet_addr(ip);
  servers = serverlist->servers;
  result = (char *)ServerListFindServerMax(serverlist, v3, port, servers->count);
  v6 = result;
  if ( result != (char *)-1 )
  {
    if ( serverlist->state && serverlist->nextupdate > (int)result )
    {
      ServerInUpdateList = ServerListFindServerInUpdateList(
                             serverlist,
                             *(struct GServerImplementation **)((char *)servers->list
                                                              + (_DWORD)result * servers->elemsize));
      if ( ServerInUpdateList != -1 )
        serverlist->updatelist[ServerInUpdateList].currentserver = nullptr;
      --serverlist->nextupdate;
    }
    ArrayDeleteAt(serverlist->servers, (int)v6);
  }
  return result;
}

// source: j/0/network/gserverlist.c:503  [anchor-callee]
int __cdecl ServerListAuxUpdate(
        struct GServerListImplementation *serverlist,
        char *ip,
        int port,
        int async,
        enum GQueryType querytype)
{
  struct GServerListImplementation *v5; // ebp
  struct GServerListImplementation *v6; // eax
  int *p_count; // esi
  int v8; // ebx
  int ServerMax; // edi
  int result; // eax
  int v11; // eax
  struct DArrayImplementation *v12; // esi
  int nextupdate; // esi
  struct GServerListImplementation *v14; // eax
  struct DArrayImplementation *servers; // ebx
  int v16; // esi
  bool v17; // cc
  int ServerInUpdateList; // eax
  void *instance; // [esp-Ch] [ebp-1Ch]

  v5 = serverlist;
  v6 = (struct GServerListImplementation *)inet_addr(ip);
  p_count = &v5->servers->count;
  v8 = *p_count;
  serverlist = v6;
  ServerMax = ServerListFindServerMax(v5, (unsigned int)v6, port, v8);
  if ( v5->state )
  {
    if ( ServerMax == -1 )
    {
      nextupdate = v5->nextupdate;
      v14 = (struct GServerListImplementation *)ServerNew((unsigned int)serverlist, port, querytype, v5->keylist);
      servers = v5->servers;
      serverlist = v14;
      ArrayInsertAt(servers, &serverlist, nextupdate);
      if ( v5->state == sl_listxfer || v5->state == sl_lanlist )
      {
        ++v5->auxinsertcount;
        return 0;
      }
    }
    else
    {
      v16 = *(_DWORD *)(ServerMax * p_count[2] + p_count[5]);
      v17 = ServerMax < v5->nextupdate;
      serverlist = (struct GServerListImplementation *)v16;
      if ( v17 )
      {
        *(_DWORD *)(v16 + 8) = querytype;
        *(_WORD *)(v16 + 6) = 9999;
        ServerInUpdateList = ServerListFindServerInUpdateList(v5, (struct GServerImplementation *)v16);
        if ( ServerInUpdateList != -1 )
          v5->updatelist[ServerInUpdateList].currentserver = nullptr;
        ArrayInsertAt(v5->servers, &serverlist, v5->nextupdate);
        ArrayRemoveAt(v5->servers, ServerMax);
        --v5->nextupdate;
      }
    }
  }
  else
  {
    result = InitUpdateList(v5);
    if ( result )
      return result;
    if ( ServerMax == -1 )
    {
      ServerListAddServer(v5, (unsigned int)serverlist, port, querytype);
    }
    else
    {
      v11 = *(_DWORD *)((char *)v5->servers->list + ServerMax * v5->servers->elemsize);
      *(_DWORD *)(v11 + 8) = querytype;
      *(_WORD *)(v11 + 6) = 9999;
      v12 = v5->servers;
      serverlist = (struct GServerListImplementation *)v11;
      ArrayRemoveAt(v12, ServerMax);
      ArrayInsertAt(v5->servers, &serverlist, v5->servers->count);
    }
    instance = v5->instance;
    v5->nextupdate = v5->servers->count - 1;
    v5->abortupdate = 0;
    v5->state = sl_querying;
    v5->CallBackFn(v5, 1, instance, nullptr, nullptr);
    if ( !async )
    {
      DoSyncLoop(v5);
      return 0;
    }
  }
  return 0;
}

// source: j/0/network/gserverlist.c:575  [anchor-strings]
int __cdecl ServerListLANList(struct GServerListImplementation *serverlist)
{
  #pragma pack(push, 1)
  union
  {
    struct { int v14; };
    struct { char igi2_o1[32]; void *instance; };
    struct { char igi2_o2[44]; int saddrlen; };
    struct { char igi2_o3[48]; int v17; };
    struct { char igi2_o4[52]; struct timeval timeout; };
    struct { char igi2_o5[60]; struct sockaddr_in saddr; };
    struct { char igi2_o6[76]; struct fd_set set; };
    struct { char igi2_o7[336]; char indata[1500]; };
    char igi2_extent[1836];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v1; // eax
  int v2; // edx
  struct DArrayImplementation *servers; // eax
  int count; // esi
  int v5; // ecx
  int elemsize; // ebx
  int v7; // eax
  u_short v8; // ax
  ULONG S_addr; // ebp
  u_short v10; // bx
  _WORD *v11; // esi
  struct DArrayImplementation *v12; // ebx

  igi2_frame.timeout.tv_sec = 0;
  igi2_frame.timeout.tv_usec = 0;
  igi2_frame.v17 = 16;
  while ( 1 )
  {
    igi2_frame.set.fd_array[0] = serverlist->slsocket;
    igi2_frame.set.fd_count = 1;
    v1 = select(64, &igi2_frame.set, nullptr, nullptr, &igi2_frame.timeout);
    if ( v1 == -1 || !v1 )
      break;
    if ( recvfrom(serverlist->slsocket, igi2_frame.indata, 1499, 0, (struct sockaddr *)&igi2_frame.saddr, &igi2_frame.v17) != -1 )
    {
      igi2_frame.indata[1499] = 0;
      if ( strstr(igi2_frame.indata, "\\final\\") )
      {
        v2 = ntohs(igi2_frame.saddr.sin_port);
        servers = serverlist->servers;
        count = servers->count;
        v5 = 0;
        if ( servers->count <= 0 )
          goto LABEL_13;
        elemsize = servers->elemsize;
        igi2_frame.saddrlen = (int)servers->list;
        while ( 1 )
        {
          v7 = *(_DWORD *)(v5 * elemsize + igi2_frame.saddrlen);
          if ( v2 == *(unsigned __int16 *)(v7 + 4) && *(_DWORD *)v7 == igi2_frame.saddr.sin_addr.S_un.S_addr )
            break;
          if ( ++v5 >= count )
            goto LABEL_13;
        }
        if ( v5 == -1 )
        {
LABEL_13:
          v8 = ntohs(igi2_frame.saddr.sin_port);
          S_addr = igi2_frame.saddr.sin_addr.S_un.S_addr;
          igi2_frame.saddrlen = (int)serverlist->keylist;
          v10 = v8;
          v11 = malloc(0x14u);
          *(_DWORD *)v11 = S_addr;
          v11[2] = v10;
          v11[3] = 9999;
          *((_DWORD *)v11 + 2) = 5;
          *((_DWORD *)v11 + 3) = TableNew2(
                                   8,
                                   8,
                                   4,
                                   KeyValHashKeyP,
                                   (int (__cdecl *)(void *, void *))KeyValCompareKeyP,
                                   nullptr);
          *((_DWORD *)v11 + 4) = igi2_frame.saddrlen;
          v12 = serverlist->servers;
          igi2_frame.v14 = v12->count;
          igi2_frame.saddrlen = (int)v11;
          ArrayInsertAt(v12, &igi2_frame.saddrlen, igi2_frame.v14);
          printf("\nServerListAddServer: Server added.\n");
        }
      }
    }
  }
  if ( GetTickCount() - serverlist->lanstarttime > 0xBB8 )
  {
    closesocket(serverlist->slsocket);
    igi2_frame.instance = serverlist->instance;
    serverlist->slsocket = -1;
    serverlist->state = sl_querying;
    serverlist->CallBackFn(serverlist, 1, igi2_frame.instance, nullptr, nullptr);
  }
  return 0;
}

// source: j/0/network/gserverlist.c:614  [anchor-mhash]
int __cdecl CountSlashOffset(char *data, int len, int slashcount)
{
  char *v3; // eax
  char *v4; // edx

  v3 = data;
  if ( !slashcount )
    return 0;
  v4 = &data[len];
  while ( v3 != v4 )
  {
    if ( *v3 == 92 )
      --slashcount;
    ++v3;
    if ( !slashcount )
      return v3 - data;
  }
  return -1;
}

// source: j/0/network/gserverlist.c:633  [anchor-strings]
int __cdecl ServerListParseInfoList(
        struct GServerListImplementation *serverlist,
        char *data,
        int len)
{
  #pragma pack(push, 1)
  union
  {
    struct { _BYTE v24[9]; };
    struct { char igi2_o1[9]; char *tempptr; };
    struct { char igi2_o2[13]; char tempfield[64]; };
    char igi2_extent[77];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  enum GParseInfoState pistate; // eax
  __int32 v6; // eax
  int v7; // ecx
  char *v8; // eax
  int v9; // ebp
  struct GServerImplementation *v11; // eax
  int v12; // ecx
  char *v13; // eax
  int v14; // eax
  int v15; // ebp
  char *v16; // eax
  struct HashImplementation *keylist; // ecx
  int v18; // eax
  int v19; // ecx
  int v20; // ecx
  char *v21; // eax
  int v22; // eax
  int v23; // eax

  printf("\nServerListParseInfoList: [%s]", data);
  pistate = serverlist->pistate;
  if ( pistate == pi_fieldcount )
  {
    v20 = 3;
    v21 = data;
    while ( v21 != &data[len] )
    {
      if ( *v21 == 92 )
        --v20;
      ++v21;
      if ( !v20 )
      {
        v22 = v21 - data;
        v15 = v22;
        if ( v22 == -1 )
          return 0;
        if ( v22 >= 12 )
        {
          strncpy(igi2_frame.tempfield, data + 12, v22 - 12);
          igi2_frame.v24[v15] = 0;
          v23 = atoi(igi2_frame.tempfield);
          *(_DWORD *)&g_fieldlist.enginename[4] = v23;
          if ( v23 <= 20 )
          {
            serverlist->pistate = pi_fields;
            if ( v23 > 0 )
              memset(&g_fieldlist, 0, 4 * v23);
            return v15 - 1;
          }
        }
        return -1;
      }
    }
    return 0;
  }
  v6 = pistate - 1;
  if ( !v6 )
  {
    v12 = 2;
    v13 = data;
    while ( v13 != &data[len] )
    {
      if ( *v13 == 92 )
        --v12;
      ++v13;
      if ( !v12 )
      {
        v14 = v13 - data;
        v15 = v14;
        if ( v14 == -1 )
          return 0;
        strncpy(igi2_frame.tempfield, data + 1, v14 - 2);
        igi2_frame.tempfield[v15 - 2] = 0;
        v16 = goastrdup(igi2_frame.tempfield);
        keylist = serverlist->keylist;
        igi2_frame.tempptr = v16;
        TableEnter(keylist, &igi2_frame.tempptr);
        v18 = 0;
        if ( *(int *)&g_fieldlist.enginename[4] <= 0 )
          return -1;
        while ( *((_DWORD *)&g_fieldlist.state + v18) )
        {
          if ( ++v18 >= *(int *)&g_fieldlist.enginename[4] )
            return -1;
        }
        v19 = *(_DWORD *)&g_fieldlist.enginename[4] - 1;
        *((_DWORD *)&g_fieldlist.state + v18) = igi2_frame.tempptr;
        if ( v18 == v19 )
        {
          serverlist->pistate = pi_servers;
          return v15 - 1;
        }
        return v15 - 1;
      }
    }
    return 0;
  }
  if ( v6 != 1 )
    return -1;
  v7 = *(_DWORD *)&g_fieldlist.enginename[4] + 1;
  v8 = data;
  if ( *(_DWORD *)&g_fieldlist.enginename[4] != -1 )
  {
    while ( v8 != &data[len] )
    {
      if ( *v8 == 92 )
        --v7;
      ++v8;
      if ( !v7 )
        goto LABEL_11;
    }
    if ( v7 )
      return 0;
  }
LABEL_11:
  v9 = v8 - data;
  if ( v8 - data == -1 )
    return 0;
  v11 = ServerListAddServerData(
          serverlist,
          (char **)&g_fieldlist,
          *(int *)&g_fieldlist.enginename[4],
          data,
          serverlist->querytype);
  data[v9 - 1] = 92;
  serverlist->CallBackFn(serverlist, 2, serverlist->instance, v11, nullptr);
  return v9 - 1;
}

// source: j/0/network/gserverlist.c:702  [anchor-callee]
int __cdecl ServerListReadList(struct GServerListImplementation *serverlist)
{
  #pragma pack(push, 1)
  union
  {
    struct { void *instance; };
    struct { void *v20; };
    struct { void *v21; };
    struct { char igi2_o3[36]; u_short port; };
    struct { char igi2_o4[40]; struct timeval timeout; };
    struct { char igi2_o5[48]; struct fd_set set; };
    char igi2_extent[308];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  unsigned int slsocket; // eax
  int v3; // eax
  int v4; // esi
  int v5; // edi
  int index; // eax
  int v7; // edi
  unsigned int *v8; // esi
  signed int v9; // eax
  signed int i; // ecx
  unsigned __int8 *v11; // ebx
  enum GQueryType querytype; // eax
  unsigned int v13; // ebx
  u_short v14; // ax
  u_short v15; // ax
  u_short v16; // ax
  int v17; // eax
  enum GQueryType v18; // eax
  bool v19; // zf

  slsocket = serverlist->slsocket;
  igi2_frame.timeout.tv_sec = 0;
  igi2_frame.timeout.tv_usec = 0;
  igi2_frame.set.fd_array[0] = slsocket;
  igi2_frame.set.fd_count = 1;
  if ( select(64, &igi2_frame.set, nullptr, nullptr, &igi2_frame.timeout) <= 0 )
    return 0;
  v3 = recv(
         serverlist->slsocket,
         &g_fieldlist.enginename[ShadowVolume_nShadowSnap + 12],
         2047 - ShadowVolume_nShadowSnap,
         0);
  v4 = v3;
  if ( v3 == -1 || !v3 )
  {
    closesocket(serverlist->slsocket);
    v19 = serverlist->state == sl_idle;
    serverlist->slsocket = -1;
    ShadowVolume_nShadowSnap = 0;
    if ( !v19 )
      serverlist->abortupdate = 1;
    igi2_frame.instance = serverlist->instance;
    serverlist->state = sl_querying;
    serverlist->CallBackFn(serverlist, 1, igi2_frame.instance, nullptr, nullptr);
    return 3;
  }
  else
  {
    v5 = ShadowVolume_nShadowSnap;
    if ( serverlist->cryptkey.index != -1 )
      crypt_docrypt(
        &serverlist->cryptkey,
        (unsigned __int8 *)&g_fieldlist.enginename[ShadowVolume_nShadowSnap + 12],
        v3);
    index = serverlist->cryptkey.index;
    v7 = v4 + v5;
    ShadowVolume_nShadowSnap = v7;
    v8 = (unsigned int *)&g_fieldlist.enginename[12];
    if ( index == -1 )
    {
      if ( v7 > (g_fieldlist.enginename[12] ^ 0xEC) )
      {
        g_fieldlist.enginename[12] ^= 0xECu;
        v9 = strlen(serverlist->seckey);
        for ( i = 0; i < v9; ++i )
          g_fieldlist.enginename[i + 13] ^= serverlist->seckey[i];
        init_crypt_key(
          (unsigned __int8 *)&g_fieldlist.enginename[13],
          g_fieldlist.enginename[12],
          &serverlist->cryptkey);
        v11 = (unsigned __int8 *)(g_fieldlist.enginename[12] + 129828009);
        crypt_docrypt(&serverlist->cryptkey, v11, v7 - (_DWORD)v11 + 129828008);
        v8 = (unsigned int *)v11;
      }
      if ( serverlist->cryptkey.index == -1 )
        goto LABEL_32;
    }
    if ( (int)(v8 - 32457002) > v7 - 6 )
    {
LABEL_32:
      ShadowVolume_nShadowSnap = &g_fieldlist.enginename[12] - (char *)v8 + v7;
      memmove(&g_fieldlist.enginename[12], v8, ShadowVolume_nShadowSnap);
      return 0;
    }
    else
    {
      while ( strncmp((char *)v8, "\\final\\", 7u) && !serverlist->abortupdate )
      {
        v7 = ShadowVolume_nShadowSnap;
        if ( ShadowVolume_nShadowSnap < 6 )
          goto LABEL_32;
        querytype = serverlist->querytype;
        if ( querytype == qt_grouprooms || querytype == qt_masterinfo )
        {
          v17 = ServerListParseInfoList(serverlist, (char *)v8, ShadowVolume_nShadowSnap - (_DWORD)v8 + 129828008);
          if ( v17 >= 0 )
          {
            if ( !v17 )
            {
              v7 = ShadowVolume_nShadowSnap;
              goto LABEL_32;
            }
            v8 = (unsigned int *)((char *)v8 + v17);
          }
          else
          {
            serverlist->abortupdate = 1;
          }
        }
        else
        {
          v13 = *v8;
          v14 = *((_WORD *)v8 + 2);
          v8 = (unsigned int *)((char *)v8 + 6);
          igi2_frame.port = v14;
          v15 = ntohs(v14);
          if ( ServerListFindServerMax(serverlist, v13, v15, serverlist->auxinsertcount) == -1 )
          {
            v16 = ntohs(igi2_frame.port);
            ServerListAddServer(serverlist, v13, v16, serverlist->querytype);
          }
        }
        v7 = ShadowVolume_nShadowSnap;
        if ( (int)(v8 - 32457002) > ShadowVolume_nShadowSnap - 6 )
          goto LABEL_32;
      }
      closesocket(serverlist->slsocket);
      v18 = serverlist->querytype;
      serverlist->slsocket = -1;
      ShadowVolume_nShadowSnap = 0;
      if ( v18 == qt_grouprooms || v18 == qt_masterinfo )
      {
        igi2_frame.v21 = serverlist->instance;
        serverlist->state = sl_idle;
        serverlist->CallBackFn(serverlist, 1, igi2_frame.v21, nullptr, nullptr);
        return 0;
      }
      else
      {
        igi2_frame.v20 = serverlist->instance;
        serverlist->state = sl_querying;
        serverlist->CallBackFn(serverlist, 1, igi2_frame.v20, nullptr, nullptr);
        return 0;
      }
    }
  }
}

// source: j/0/network/gserverlist.c:809  [anchor-callee]
int __cdecl ServerListQueryLoop(struct GServerListImplementation *serverlist)
{
  #pragma pack(push, 1)
  union
  {
    struct { void *instance; };
    struct { char igi2_o1[24]; int i; };
    struct { char igi2_o2[24]; int ia; };
    struct { char igi2_o3[28]; int scount; };
    struct { char igi2_o4[32]; int saddrlen; };
    struct { char igi2_o5[36]; struct timeval timeout; };
    struct { char igi2_o6[44]; struct sockaddr_in saddr; };
    struct { char igi2_o7[60]; struct fd_set set; };
    struct { char igi2_o8[320]; char indata[1500]; };
    char igi2_extent[1820];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int maxupdates; // ecx
  int v2; // edi
  u_int v3; // eax
  struct UpdateInfo *updatelist; // ecx
  int v5; // edx
  int v6; // eax
  int v7; // ebp
  struct UpdateInfo *v8; // eax
  struct UpdateInfo *v9; // eax
  int v10; // eax
  struct UpdateInfo *v11; // ecx
  char *v12; // eax
  struct GServerImplementation *currentserver; // ebx
  BOOL v14; // edi
  int v15; // ebx
  int v16; // ebp
  struct UpdateInfo *v17; // ecx
  struct UpdateInfo *v18; // edi
  int v19; // ebp
  int k; // edi
  struct DArrayImplementation *servers; // eax
  int nextupdate; // ecx
  struct UpdateInfo *v23; // edx
  struct GServerImplementation *v24; // ebp
  _DWORD *p_currentserver; // edx
  struct in_addr *v26; // ebp
  char *v27; // eax
  int j; // edi

  maxupdates = serverlist->maxupdates;
  v2 = 0;
  v3 = 0;
  igi2_frame.scount = 0;
  igi2_frame.timeout.tv_sec = 0;
  igi2_frame.timeout.tv_usec = 0;
  igi2_frame.saddrlen = 16;
  igi2_frame.set.fd_count = 0;
  if ( maxupdates > 0 )
  {
    updatelist = serverlist->updatelist;
    v5 = serverlist->maxupdates;
    do
    {
      if ( updatelist->currentserver )
      {
        ++v2;
        if ( v3 < 0x40 )
        {
          igi2_frame.set.fd_array[v3] = updatelist->s;
          v3 = ++igi2_frame.set.fd_count;
        }
      }
      ++updatelist;
      --v5;
    }
    while ( v5 );
    igi2_frame.scount = v2;
    if ( v2 > 0 )
    {
      v6 = select(64, &igi2_frame.set, nullptr, nullptr, &igi2_frame.timeout);
      if ( v6 != -1 )
      {
        if ( v6 )
        {
          igi2_frame.i = 0;
          if ( serverlist->maxupdates > 0 )
          {
            v7 = 0;
            do
            {
              v8 = &serverlist->updatelist[v7];
              if ( v8->currentserver )
              {
                if ( _WSAFDIsSet(v8->s, &igi2_frame.set) )
                {
                  v9 = serverlist->updatelist;
                  igi2_frame.saddrlen = 16;
                  v10 = recvfrom(v9[v7].s, igi2_frame.indata, 1499, 0, (struct sockaddr *)&igi2_frame.saddr, &igi2_frame.saddrlen);
                  v11 = &serverlist->updatelist[v7];
                  if ( igi2_frame.saddr.sin_addr.S_un.S_addr == v11->saddr.sin_addr.S_un.S_addr
                    && igi2_frame.saddr.sin_port == v11->saddr.sin_port )
                  {
                    if ( v10 == -1 )
                    {
                      v11->currentserver = nullptr;
                    }
                    else
                    {
                      igi2_frame.indata[v10] = 0;
                      v12 = strstr(igi2_frame.indata, "\\final\\");
                      currentserver = serverlist->updatelist[v7].currentserver;
                      v14 = v12 != nullptr;
                      if ( currentserver->ping == 9999 )
                        currentserver->ping = GetTickCount() - LOWORD(serverlist->updatelist[v7].starttime);
                      ServerParseKeyVals(currentserver, igi2_frame.indata);
                      if ( v14 )
                      {
                        serverlist->CallBackFn(
                          serverlist,
                          2,
                          serverlist->instance,
                          currentserver,
                          (void *)(100 * serverlist->nextupdate / serverlist->servers->count));
                        serverlist->updatelist[v7].currentserver = nullptr;
                      }
                    }
                  }
                }
              }
              ++v7;
              ++igi2_frame.i;
            }
            while ( igi2_frame.i < serverlist->maxupdates );
            v2 = igi2_frame.scount;
          }
        }
      }
    }
  }
  v15 = 0;
  if ( serverlist->maxupdates > 0 )
  {
    v16 = 0;
    do
    {
      v17 = serverlist->updatelist;
      if ( v17[v16].currentserver )
      {
        v18 = &v17[v16];
        if ( GetTickCount() - v17[v16].starttime > 0xBB8 )
          v18->currentserver = nullptr;
      }
      ++v15;
      ++v16;
    }
    while ( v15 < serverlist->maxupdates );
    v2 = igi2_frame.scount;
  }
  v19 = 0;
  if ( serverlist->abortupdate || serverlist->nextupdate >= serverlist->servers->count && !v2 )
  {
    for ( j = 0; j < serverlist->maxupdates; ++v19 )
    {
      closesocket(serverlist->updatelist[v19].s);
      ++j;
    }
    igi2_frame.instance = serverlist->instance;
    serverlist->state = sl_idle;
    serverlist->CallBackFn(serverlist, 1, igi2_frame.instance, nullptr, nullptr);
  }
  else
  {
    igi2_frame.ia = 0;
    if ( serverlist->maxupdates > 0 )
    {
      for ( k = 0; ; ++k )
      {
        servers = serverlist->servers;
        nextupdate = serverlist->nextupdate;
        if ( nextupdate >= servers->count )
          break;
        v23 = serverlist->updatelist;
        v24 = v23[k].currentserver;
        p_currentserver = &v23[k].currentserver;
        if ( !v24 )
        {
          v26 = *(struct in_addr **)((char *)servers->list + nextupdate * servers->elemsize);
          serverlist->nextupdate = nextupdate + 1;
          *p_currentserver = v26;
          serverlist->updatelist[k].saddr.sin_family = 2;
          v27 = inet_ntoa(*v26);
          serverlist->updatelist[k].saddr.sin_addr.S_un.S_addr = inet_addr(v27);
          serverlist->updatelist[k].saddr.sin_port = htons(v26[1].S_un.S_un_w.s_w1);
          sendto(
            serverlist->updatelist[k].s,
            querystrings[v26[2].S_un.S_addr],
            querylengths[v26[2].S_un.S_addr],
            0,
            (struct sockaddr *)&serverlist->updatelist[k].saddr,
            16);
          serverlist->updatelist[k].starttime = GetTickCount();
        }
        if ( ++igi2_frame.ia >= serverlist->maxupdates )
          return 0;
      }
    }
  }
  return 0;
}

// source: j/0/network/gserverlist.c:907  [anchor-hash]
int __cdecl IsServerListIdling(struct GServerListImplementation *serverlist)
{
  if ( serverlist )
    return serverlist->state == sl_idle;
  else
    return 5;
}

// source: j/0/network/gserverlist.c:924  [anchor-hash]
int __cdecl ServerListThink(struct GServerListImplementation *serverlist)
{
  int result; // eax

  if ( !serverlist )
    return 5;
  switch ( serverlist->state )
  {
    case sl_listxfer:
      result = ServerListReadList(serverlist);
      break;
    case sl_lanlist:
      result = ServerListLANList(serverlist);
      break;
    case sl_querying:
      result = ServerListQueryLoop(serverlist);
      break;
    default:
      result = 0;
      break;
  }
  return result;
}

// source: j/0/network/gserverlist.c:953  [anchor-hash]
int __cdecl ServerListHalt(struct GServerListImplementation *serverlist)
{
  if ( serverlist->state )
    serverlist->abortupdate = 1;
  return 0;
}

// source: j/0/network/gserverlist.c:965  [anchor-callee]
int __cdecl ServerListClear(struct GServerListImplementation *serverlist)
{
  struct DArrayImplementation *v2; // esi
  struct HashImplementation *keylist; // ebx

  if ( serverlist->state )
    return 4;
  ArrayFree(serverlist->servers);
  v2 = (struct DArrayImplementation *)malloc(0x18u);
  v2->count = 0;
  v2->capacity = 64;
  v2->elemsize = 4;
  v2->growby = 64;
  v2->elemfreefn = ServerFree;
  v2->list = malloc(0x100u);
  keylist = serverlist->keylist;
  serverlist->servers = v2;
  TableFree(keylist);
  serverlist->keylist = TableNew2(4, 500, 4, GStringHash, GCaseInsensitiveCompare, GStringFree);
  serverlist->auxinsertcount = 0;
  return 0;
}

// source: j/0/network/gserverlist.c:982  [size]
enum GServerListState __cdecl ServerListState(
        struct GServerListImplementation *serverlist)
{
  return serverlist->state;
}

// source: j/0/network/gserverlist.c:990  [anchor-hash]
char *__cdecl ServerListErrorDesc(struct GServerListImplementation *serverlist, int error)
{
  char *result; // eax

  switch ( error )
  {
    case 0:
      result = "No error";
      break;
    case 1:
      result = (char *)&unk_6858A0;
      break;
    case 2:
      result = (char *)&unk_685884;
      break;
    case 3:
      result = (char *)&unk_685868;
      break;
    case 4:
      result = (char *)&unk_685854;
      break;
    case 5:
      result = (char *)&unk_685834;
      break;
    default:
      result = (char *)&unk_685820;
      break;
  }
  return result;
}

// source: j/0/network/gserverlist.c:1008  [anchor-mhash]
struct GServerImplementation *__cdecl ServerListGetServer(
        struct GServerListImplementation *serverlist,
        int index)
{
  struct DArrayImplementation *servers; // eax

  if ( index < 0 )
    return nullptr;
  servers = serverlist->servers;
  if ( index >= servers->count )
    return nullptr;
  else
    return *(struct GServerImplementation **)((char *)servers->list + index * servers->elemsize);
}

// source: j/0/network/gserverlist.c:1019  [anchor-hash]
int __cdecl ServerListCount(struct GServerListImplementation *serverlist)
{
  return serverlist->servers->count;
}

// source: j/0/network/gserverlist.c:1027  [anchor-mhash]
int __cdecl IntKeyCompare(void *entry1, void *entry2)
{
  struct GServerImplementation *v2; // esi
  int IntValue; // edi
  int result; // eax

  v2 = *(struct GServerImplementation **)entry1;
  IntValue = ServerGetIntValue(*(struct GServerImplementation **)entry2, g_sortserverlist->sortkey, 0);
  result = ServerGetIntValue(v2, g_sortserverlist->sortkey, 0) - IntValue;
  if ( !g_sortserverlist->sortascending )
    return -result;
  return result;
}

// source: j/0/network/gserverlist.c:1039  [anchor-mhash]
int __cdecl FloatKeyCompare(void *entry1, void *entry2)
{
  struct GServerImplementation *v2; // edi
  double v3; // st7
  double FloatValue; // [esp+8h] [ebp-8h]

  v2 = *(struct GServerImplementation **)entry2;
  FloatValue = ServerGetFloatValue((struct GServerImplementation *)*(_DWORD *)entry1, g_sortserverlist->sortkey, 0.0);
  v3 = FloatValue - ServerGetFloatValue(v2, g_sortserverlist->sortkey, 0.0);
  if ( !g_sortserverlist->sortascending )
    v3 = -v3;
  if ( v3 > 0.0 )
    return 1;
  if ( v3 >= 0.0 )
    return 0;
  return -1;
}

// source: j/0/network/gserverlist.c:1054  [anchor-mhash]
int __cdecl StrCaseKeyCompare(void *entry1, void *entry2)
{
  struct GServerImplementation *v2; // edi
  char *StringValue; // esi
  int result; // eax

  v2 = *(struct GServerImplementation **)entry1;
  StringValue = ServerGetStringValue(
                  *(struct GServerImplementation **)entry2,
                  g_sortserverlist->sortkey,
                  (char *)&g_zInitialValue);
  result = strcmp(ServerGetStringValue(v2, g_sortserverlist->sortkey, (char *)&g_zInitialValue), StringValue);
  if ( !g_sortserverlist->sortascending )
    return -result;
  return result;
}

// source: j/0/network/gserverlist.c:1065  [anchor-mhash]
int __cdecl StrNoCaseKeyCompare(void *entry1, void *entry2)
{
  struct GServerImplementation *v2; // esi
  char *v3; // eax
  int result; // eax
  char *StringValue; // [esp-4h] [ebp-Ch]

  v2 = *(struct GServerImplementation **)entry1;
  StringValue = ServerGetStringValue(
                  *(struct GServerImplementation **)entry2,
                  g_sortserverlist->sortkey,
                  (char *)&g_zInitialValue);
  v3 = ServerGetStringValue(v2, g_sortserverlist->sortkey, (char *)&g_zInitialValue);
  result = _stricmp(v3, StringValue);
  if ( !g_sortserverlist->sortascending )
    return -result;
  return result;
}

// source: j/0/network/gserverlist.c:1080  [size]
struct GServerListImplementation *__cdecl ServerListSort(
        struct GServerListImplementation *serverlist,
        int ascending,
        char *sortkey,
        enum GCompareMode comparemode)
{
  int (__cdecl *v4)(void *, void *); // ecx

  switch ( comparemode )
  {
    case cm_int:
      v4 = IntKeyCompare;
      break;
    case cm_float:
      v4 = FloatKeyCompare;
      break;
    case cm_strcase:
      v4 = StrCaseKeyCompare;
      break;
    default:
      v4 = StrNoCaseKeyCompare;
      break;
  }
  serverlist->sortkey = sortkey;
  serverlist->sortascending = ascending;
  g_sortserverlist = serverlist;
  qsort(
                                               serverlist->servers->list,
                                               serverlist->servers->count,
                                               serverlist->servers->elemsize,
                                               v4);
  return 0;
}
