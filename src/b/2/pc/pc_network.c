/* b/2/pc/pc_network.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: b/2/pc/pc_network.c:298  [anchor-hash]
unsigned int __cdecl Network_InitGuaranteedCounters(unsigned int eNetworkID)
{
  Network_nGuaranteedPacketID[eNetworkID] = 1;
  Network_nLastReceivedGuaranteedPacketID[eNetworkID] = 0;
  return eNetworkID;
}

// source: b/2/pc/pc_network.c:315  [anchor-hash]
char *__cdecl Network_GetErrorDesc(int nCode)
{
  int v1; // eax
  char *result; // eax
  int v3; // eax
  int v4; // eax

  if ( nCode > 10053 )
  {
    if ( nCode > 10101 )
    {
      v4 = nCode - 11001;
      if ( v4 )
      {
        if ( v4 != 3 )
          return "Unknown error code";
        return "WSANO_DATA:No host data of that type was found";
      }
      else
      {
        return "WSAHOST_NOT_FOUND:Host not found";
      }
    }
    else if ( nCode == 10101 )
    {
      return "WSAEDISCON:Graceful shutdown in progress";
    }
    else
    {
      switch ( nCode )
      {
        case 10054:
          result = "WSAECONNRESET:Connection reset by peer";
          break;
        case 10055:
          result = "WSAENOBUFS:No buffer space available";
          break;
        case 10056:
          result = "WSAEISCONN:Socket is already connected";
          break;
        case 10057:
          result = "WSAENOTCONN:Socket is not connected";
          break;
        case 10058:
          result = "WSAESHUTDOWN:Can't send after socket shutdown";
          break;
        case 10059:
          result = "WSAETOOMANYREFS:Too many references, can't splice";
          break;
        case 10060:
          result = "WSAETIMEDOUT:Connection timed out";
          break;
        case 10061:
          result = "WSAECONNREFUSED:Connection refused";
          break;
        case 10062:
          result = "WSAELOOP:Too many levels of symbolic links";
          break;
        case 10063:
          result = "WSAENAMETOOLONG:File name too long";
          break;
        case 10064:
          result = "WSAEHOSTDOWN:Host is down";
          break;
        case 10065:
          result = "WSAEHOSTUNREACH:No route to host";
          break;
        case 10066:
          result = "WSAENOTEMPTY:Directory not empty";
          break;
        case 10067:
          result = "WSAEPROCLIM:Too many processes";
          break;
        case 10068:
          result = "WSAEUSERS:Too many users";
          break;
        case 10069:
          result = "WSAEDQUOT:Disc quota exceeded";
          break;
        case 10070:
          result = "WSAESTALE:Stale NFS file handle";
          break;
        case 10071:
          result = "WSAEREMOTE:Too many levels of remote in path";
          break;
        case 10091:
          result = "WSASYSNOTREADY:Network system is unavailable";
          break;
        case 10092:
          result = "WSAVERNOTSUPPORTED:Winsock version out of range";
          break;
        case 10093:
          result = "WSANOTINITIALISED:WSAStartup not yet called";
          break;
        default:
          return "Unknown error code";
      }
    }
  }
  else
  {
    if ( nCode == 10053 )
      return "WSAECONNABORTED:Software caused connection abort";
    if ( nCode > 10040 )
    {
      switch ( nCode )
      {
        case 10041:
          result = "WSAEPROTOTYPE:Protocol wrong type for socket";
          break;
        case 10042:
          result = "WSAENOPROTOOPT:Bad protocol option";
          break;
        case 10043:
          result = "WSAEPROTONOSUPPORT:Protocol not supported";
          break;
        case 10044:
          result = "WSAESOCKTNOSUPPORT:Socket type not supported";
          break;
        case 10045:
          result = "WSAEOPNOTSUPP:Operation not supported on socket";
          break;
        case 10046:
          result = "WSAEPFNOSUPPORT:Protocol family not supported";
          break;
        case 10047:
          result = "WSAEAFNOSUPPORT:Address family not supported";
          break;
        case 10048:
          result = "WSAEADDRINUSE:Address already in use";
          break;
        case 10049:
          result = "WSAEADDRNOTAVAIL:Can't assign requested address";
          break;
        case 10050:
          result = "WSAENETDOWN:Network is down";
          break;
        case 10051:
          result = "WSAENETUNREACH:Network is unreachable";
          break;
        case 10052:
          result = "WSAENETRESET:Net connection reset";
          break;
      }
    }
    else
    {
      if ( nCode == 10040 )
        return "WSAEMSGSIZE:Message too long";
      if ( nCode <= 10024 )
      {
        if ( nCode == 10024 )
          return "WSAEMFILE:Too many open sockets";
        if ( nCode > 10013 )
        {
          v3 = nCode - 10014;
          if ( !v3 )
            return "WSAEFAULT:Bad address";
          if ( v3 == 8 )
            return "WSAEINVAL:Invalid argument";
        }
        else
        {
          if ( nCode == 10013 )
            return "WSAEACCES:Permission denied";
          if ( !nCode )
            return "No error";
          v1 = nCode - 10004;
          if ( !v1 )
            return "WSAEINTR:Interrupted system call";
          if ( v1 == 5 )
            return "WSAEBADF:Bad file number";
        }
        return "Unknown error code";
      }
      switch ( nCode )
      {
        case 10035:
          result = "WSAEWOULDBLOCK:Operation would block";
          break;
        case 10036:
          result = "WSAEINPROGRESS:Operation now in progress";
          break;
        case 10037:
          result = "WSAEALREADY:Operation already in progress";
          break;
        case 10038:
          result = "WSAENOTSOCK:Socket operation on non-socket";
          break;
        case 10039:
          result = "WSAEDESTADDRREQ:Destination address required";
          break;
        default:
          return "Unknown error code";
      }
    }
  }
  return result;
}

// source: b/2/pc/pc_network.c:391  [anchor-strings]
void __cdecl Network_DebugError(char *zLocal, int nErrorCode)
{
  #pragma pack(push, 1)
  union
  {
    struct { char *ErrorDesc; };
    struct { char igi2_o1[4]; char zTemp[256]; };
    char igi2_extent[260];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)

  if ( nErrorCode != 10054 )
  {
    igi2_frame.ErrorDesc = Network_GetErrorDesc(nErrorCode);
    _snprintf(igi2_frame.zTemp, 0xFFu, "\n%s:error code=%d, desc=%s\n", zLocal, nErrorCode, igi2_frame.ErrorDesc);
    NetManager_LogMessage(igi2_frame.zTemp);
  }
  WSASetLastError(0);
}

// source: b/2/pc/pc_network.c:443  [anchor-hash]
void __cdecl Network_PrintSocket(char *zString, int nLength, struct sockaddr_in *ptSocket)
{
  int v3; // [esp-4h] [ebp-4h]

  v3 = ntohs(ptSocket->sin_port);
  _snprintf(
    zString,
    0x16u,
    "%d.%d.%d.%d:%d",
    ptSocket->sin_addr.S_un.S_un_b.s_b1,
    ptSocket->sin_addr.S_un.S_un_b.s_b2,
    ptSocket->sin_addr.S_un.S_un_b.s_b3,
    ptSocket->sin_addr.S_un.S_un_b.s_b4,
    v3);
}

// source: b/2/pc/pc_network.c:466  [anchor-hash]
struct sockaddr_in *__cdecl Network_PrintIP(char *zString, int nLength, struct sockaddr_in *ptSocket)
{
  return (struct sockaddr_in *)_snprintf(
                                 zString,
                                 0x10u,
                                 "%d.%d.%d.%d",
                                 ptSocket->sin_addr.S_un.S_un_b.s_b1,
                                 ptSocket->sin_addr.S_un.S_un_b.s_b2,
                                 ptSocket->sin_addr.S_un.S_un_b.s_b3,
                                 ptSocket->sin_addr.S_un.S_un_b.s_b4);
}

// source: b/2/pc/pc_network.c:491  [size]
void __cdecl Network_CreateUDPSocket(unsigned int *ptSocket)
{
  *ptSocket = socket(2, 2, 17);
}

// source: b/2/pc/pc_network.c:506  [size]
void __cdecl Network_CreateGlobalUDPSocket()
{
  Network_UDPSocket = socket(2, 2, 17);
}

// source: b/2/pc/pc_network.c:521  [anchor-hash]
unsigned int *__cdecl Network_CloseUDPSocket(unsigned int *ptSocket)
{
  SOCKET v1; // eax
  unsigned int *result; // eax

  v1 = *ptSocket;
  if ( v1 == -1 )
  {
    NetManager_LogMessage("Network_CloseUDPSocket: Socket was invalid\n");
  }
  else
  {
    closesocket(v1);
    NetManager_LogMessage("Network_CloseUDPSocket: Socket closed\n");
  }
  return result;
}

// source: b/2/pc/pc_network.c:543  [anchor-hash]
void __cdecl Network_CloseGlobalUDPSocket()
{
  if ( Network_UDPSocket == -1 )
  {
    NetManager_LogMessage("Network_CloseUDPSocket: Socket was invalid\n");
  }
  else
  {
    closesocket(Network_UDPSocket);
    NetManager_LogMessage("Network_CloseUDPSocket: Socket closed\n");
  }
}

// source: b/2/pc/pc_network.c:558  [size]
unsigned int __cdecl Network_GetGlobalUDPSocket()
{
  return Network_UDPSocket;
}

// source: b/2/pc/pc_network.c:571  [anchor-strings]
void __cdecl Network_StoreLocalAddress()
{
  #pragma pack(push, 1)
  union
  {
    struct { int nLength; };
    struct { char igi2_o1[4]; char zLocalAddress[100]; };
    struct { char igi2_o2[104]; char zTemp[256]; };
    char igi2_extent[360];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int Error; // eax
  u_short v1; // ax

  *(_DWORD *)&Network_LocalAddress.sin_family = 0;
  Network_LocalAddress.sin_addr.S_un.S_addr = 0;
  *(_DWORD *)Network_LocalAddress.sin_zero = 0;
  *(_DWORD *)&Network_LocalAddress.sin_zero[4] = 0;
  igi2_frame.nLength = 16;
  if ( getsockname(Network_UDPSocket, (struct sockaddr *)&Network_LocalAddress, &igi2_frame.nLength) == -1 )
  {
    Error = WSAGetLastError();
    Network_DebugError("Network_StoreLocalAddress -getsockname\n", Error);
  }
  else
  {
    v1 = ntohs(Network_LocalAddress.sin_port);
    _snprintf(
      igi2_frame.zLocalAddress,
      0x16u,
      "%d.%d.%d.%d:%d",
      Network_LocalAddress.sin_addr.S_un.S_un_b.s_b1,
      Network_LocalAddress.sin_addr.S_un.S_un_b.s_b2,
      Network_LocalAddress.sin_addr.S_un.S_un_b.s_b3,
      Network_LocalAddress.sin_addr.S_un.S_un_b.s_b4,
      v1);
    _snprintf(igi2_frame.zTemp, 0xFFu, "Network: Bound to [%s]\n", igi2_frame.zLocalAddress);
    NetManager_LogMessage(igi2_frame.zTemp);
  }
}

// source: b/2/pc/pc_network.c:609  [anchor-hash]
enum bool __cdecl Network_IsLocalSocket(struct sockaddr *ptSockAddr)
{
  return memcmp(&Network_LocalAddress, ptSockAddr, 8u) == 0;
}

// source: b/2/pc/pc_network.c:628  [anchor-strings]
int __cdecl Network_ClientBindGlobalUDPSocket(struct NetworkAdapterItem_s *ptAdapter, int nClientPort)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct sockaddr_in tInetAddr; };
    struct { char igi2_o1[16]; char zTemp[256]; };
    char igi2_extent[272];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v2; // esi
  int Error; // eax
  int v4; // ecx
  char *ErrorDesc; // eax

  v2 = nClientPort;
  if ( !ptAdapter )
    NetManager_LogMessage("Network: No local address found\n");
  while ( 1 )
  {
    igi2_frame.tInetAddr.sin_family = 2;
    igi2_frame.tInetAddr.sin_port = htons(v2);
    igi2_frame.tInetAddr.sin_addr.S_un.S_addr = *(_DWORD *)ptAdapter->pnAddress;
    if ( bind(Network_UDPSocket, (struct sockaddr *)&igi2_frame.tInetAddr, 16) != -1 )
      break;
    Error = WSAGetLastError();
    v4 = Error;
    if ( Error != 10054 )
    {
      ErrorDesc = Network_GetErrorDesc(Error);
      _snprintf(
        igi2_frame.zTemp,
        0xFFu,
        "\n%s:error code=%d, desc=%s\n",
        "Network_ClientBindGlobalUDPSocket: bind()",
        v4,
        ErrorDesc);
      NetManager_LogMessage(igi2_frame.zTemp);
    }
    WSASetLastError(0);
    if ( ++v2 > nClientPort + 10 )
      return -1;
  }
  _snprintf(igi2_frame.zTemp, 0xFFu, "Client successfully bound to port %d.\n", v2);
  NetManager_LogMessage(igi2_frame.zTemp);
  Network_StoreLocalAddress();
  return v2;
}

// source: b/2/pc/pc_network.c:699  [anchor-callee]
void __cdecl Network_FreeIDList()
{
  struct Node_s *ptHead; // eax
  struct Node_s *i; // ebx
  _DWORD **v2; // eax
  int v3; // esi

  ptHead = Network_tIDList.ptHead;
  for ( i = Network_tIDList.ptHead->ptNext; i; i = i->ptNext )
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
}

// source: b/2/pc/pc_network.c:722  [anchor-callee]
enum bool __cdecl Network_AddIDItem(int eID, struct sockaddr_in *ptSockAddr)
{
  struct Node_s *ptHead; // ecx
  struct Node_s *ptNext; // eax
  struct sockaddr_in *v4; // esi
  DWORD PerformanceCounter; // eax

  ptHead = Network_tIDList.ptHead;
  ptNext = Network_tIDList.ptHead->ptNext;
  if ( Network_tIDList.ptHead->ptNext )
  {
    while ( ptHead[1].ptNext != (struct Node_s *)eID )
    {
      ptHead = ptNext;
      ptNext = ptNext->ptNext;
      if ( !ptNext )
        goto LABEL_4;
    }
    return false;
  }
  else
  {
LABEL_4:
    v4 = (struct sockaddr_in *)Mem_AllocFn(32, 4);
    v4->sin_addr.S_un.S_addr = 0;
    *(_DWORD *)&v4->sin_family = 0;
    *(_DWORD *)v4->sin_zero = eID;
    v4[1] = *ptSockAddr;
    if ( Timer_isPerformanceCounter )
      PerformanceCounter = Timer_GetPerformanceCounter();
    else
      PerformanceCounter = GetTickCount();
    *(_DWORD *)&v4->sin_zero[4] = PerformanceCounter - Timer_nStartTime;
    List_AddTail(v4, (int)&Network_tIDList);
    return true;
  }
}

// source: b/2/pc/pc_network.c:774  [size]
struct NetworkIDListItem_s *__cdecl Network_GetIDItemFromID(int eID)
{
  struct NetworkIDListItem_s *result; // eax
  struct NetworkIDListItem_s *ptNext; // ecx

  result = (struct NetworkIDListItem_s *)Network_tIDList.ptHead;
  ptNext = (struct NetworkIDListItem_s *)Network_tIDList.ptHead->ptNext;
  if ( !Network_tIDList.ptHead->ptNext )
    return nullptr;
  while ( result->eID != eID )
  {
    result = ptNext;
    ptNext = (struct NetworkIDListItem_s *)ptNext->tNode.ptNext;
    if ( !ptNext )
      return nullptr;
  }
  return result;
}

// source: b/2/pc/pc_network.c:803  [anchor-strings]
enum bool __cdecl Network_IsItemIDExisitingAndIsCreatedBefore(int eID, int nCreateTime)
{
  struct Node_s *ptHead; // ecx
  enum bool result; // eax
  char zTemp[256]; // [esp+0h] [ebp-100h] BYREF

  ptHead = Network_tIDList.ptHead;
  result = (enum bool)Network_tIDList.ptHead->ptNext;
  if ( Network_tIDList.ptHead->ptNext )
  {
    while ( ptHead[1].ptNext != (struct Node_s *)eID )
    {
      ptHead = (struct Node_s *)result;
      result = *(_DWORD *)result;
      if ( result == false )
        return result;
    }
    if ( (int)ptHead[1].ptPrev < nCreateTime )
    {
      _snprintf(zTemp, 0xFFu, "Network_IsItemIDExisitingAndIsCreatedBefore: Existing and old, id=%d\n", eID);
      NetManager_LogMessage(zTemp);
      return true;
    }
    _snprintf(zTemp, 0xFFu, "Network_IsItemIDExisitingAndIsCreatedBefore: Existing, not old, id=%d\n", eID);
    NetManager_LogMessage(zTemp);
  }
  return false;
}

// source: b/2/pc/pc_network.c:845  [anchor-callee]
enum bool __cdecl Network_RemoveIDItemFromID(int eID)
{
  struct Node_s *ptHead; // eax
  struct Node_s *ptNext; // ecx
  int v4; // esi

  ptHead = Network_tIDList.ptHead;
  ptNext = Network_tIDList.ptHead->ptNext;
  if ( !Network_tIDList.ptHead->ptNext )
    return false;
  while ( ptHead[1].ptNext != (struct Node_s *)eID )
  {
    ptHead = ptNext;
    ptNext = ptNext->ptNext;
    if ( !ptNext )
      return false;
  }
  v4 = *(_DWORD *)((unsigned int)(Node_Remove(ptHead) - 1) & 0xFFFFFFFC);
  --Mem_nCurrentAllocations;
  Node_Remove((_DWORD **)v4);
  memset(*(void **)(v4 + 8), 0xCDu, *(_DWORD *)(v4 + 16));
  free((void *)v4);
  return true;
}

// source: b/2/pc/pc_network.c:876  [anchor-callee]
struct NetworkIDListItem_s *__cdecl Network_GetIDItemFromAddr(struct sockaddr_in *ptSockAddr)
{
  struct NetworkIDListItem_s *result; // eax
  struct NetworkIDListItem_s *ptNext; // edx

  result = (struct NetworkIDListItem_s *)Network_tIDList.ptHead;
  ptNext = (struct NetworkIDListItem_s *)Network_tIDList.ptHead->ptNext;
  if ( !Network_tIDList.ptHead->ptNext )
    return nullptr;
  while ( memcmp(&result->tSockAddr, ptSockAddr, 8u) )
  {
    result = ptNext;
    ptNext = (struct NetworkIDListItem_s *)ptNext->tNode.ptNext;
    if ( !ptNext )
      return nullptr;
  }
  return result;
}

// source: b/2/pc/pc_network.c:905  [anchor-hash]
int __cdecl Network_GetNetworkIDFromAddr(struct sockaddr_in *ptSockAddr)
{
  struct NetworkIDListItem_s *IDItemFromAddr; // eax

  IDItemFromAddr = Network_GetIDItemFromAddr(ptSockAddr);
  if ( IDItemFromAddr )
    return IDItemFromAddr->eID;
  else
    return -1;
}

// source: b/2/pc/pc_network.c:932  [anchor-strings]
void __cdecl Network_PrintSocketFromID(char *zString, int nLength, int eID)
{
  struct Node_s *ptHead; // esi
  struct Node_s *ptNext; // eax
  u_short v5; // ax

  ptHead = Network_tIDList.ptHead;
  ptNext = Network_tIDList.ptHead->ptNext;
  if ( Network_tIDList.ptHead->ptNext )
  {
    while ( ptHead[1].ptNext != (struct Node_s *)eID )
    {
      ptHead = ptNext;
      ptNext = ptNext->ptNext;
      if ( !ptNext )
        goto LABEL_4;
    }
    v5 = ntohs(HIWORD(ptHead[2].ptNext));
    _snprintf(
      zString,
      0x16u,
      "%d.%d.%d.%d:%d",
      LOBYTE(ptHead[2].ptPrev),
      BYTE1(ptHead[2].ptPrev),
      BYTE2(ptHead[2].ptPrev),
      HIBYTE(ptHead[2].ptPrev),
      v5);
  }
  else
  {
LABEL_4:
    _snprintf(zString, nLength, "NOT FOUND");
  }
}

// source: b/2/pc/pc_network.c:960  [anchor-strings]
void __cdecl Network_FreeQueues()
{
  #pragma pack(push, 1)
  union
  {
    struct { int iQueue; };
    struct { char igi2_o1[4]; struct Queue_s *v8; };
    struct { char igi2_o2[8]; char zTemp[256]; };
    char igi2_extent[264];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct Queue_s *v0; // eax
  struct Node_s *ptHead; // esi
  struct Node_s *ptNext; // ebx
  struct Node_s *v3; // eax
  int v4; // ebp
  int v5; // ecx
  int v6; // esi

  v0 = Network_atQueues;
  igi2_frame.iQueue = 0;
  igi2_frame.v8 = Network_atQueues;
  do
  {
    ptHead = v0->tList.ptHead;
    ptNext = v0->tList.ptHead->ptNext;
    if ( ptNext )
    {
      do
      {
        Node_Remove(ptHead);
        _snprintf(
          igi2_frame.zTemp,
          0xFFu,
          "Network_FreeQueues. Removing %d from queue[%d]\n",
          HIWORD(ptHead[3].ptNext[1].ptPrev),
          igi2_frame.iQueue);
        NetManager_LogMessage(igi2_frame.zTemp);
        v3 = ptHead[3].ptNext;
        if ( v3 )
        {
          --Mem_nCurrentAllocations;
          v4 = *(_DWORD *)((unsigned int)&v3[-1].ptPrev & 0xFFFFFFFC);
          Node_Remove((_DWORD **)v4);
          memset(*(void **)(v4 + 8), 0xCDu, *(_DWORD *)(v4 + 16));
          free((void *)v4);
        }
        v5 = Mem_nCurrentAllocations;
        ptHead[3].ptNext = nullptr;
        v6 = *(_DWORD *)((unsigned int)&ptHead[-1].ptPrev & 0xFFFFFFFC);
        Mem_nCurrentAllocations = v5 - 1;
        Node_Remove((_DWORD **)v6);
        memset(*(void **)(v6 + 8), 0xCDu, *(_DWORD *)(v6 + 16));
        free((void *)v6);
        ptHead = ptNext;
        ptNext = ptNext->ptNext;
      }
      while ( ptNext );
      v0 = igi2_frame.v8;
    }
    ++v0;
    ++igi2_frame.iQueue;
    igi2_frame.v8 = v0;
  }
  while ( (int)v0 < 7587040 );
}

// source: b/2/pc/pc_network.c:1006  [anchor-strings]
void __cdecl Network_FreeQueuesTo(int nID)
{
  #pragma pack(push, 1)
  union
  {
    struct { int iQueue; };
    struct { char igi2_o1[4]; struct Queue_s *v11; };
    struct { char igi2_o2[8]; int nRemoved; };
    struct { char igi2_o3[12]; char zTemp[256]; };
    char igi2_extent[268];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct Queue_s *v1; // eax
  struct Node_s *ptHead; // ebx
  struct Node_s *ptNext; // ebp
  int v4; // esi
  struct Node_s *v5; // eax
  int v6; // esi
  int v7; // ecx
  int v8; // esi
  bool v9; // cc

  v1 = Network_atQueues;
  igi2_frame.iQueue = 0;
  igi2_frame.v11 = Network_atQueues;
  do
  {
    ptHead = v1->tList.ptHead;
    ptNext = v1->tList.ptHead->ptNext;
    v4 = 0;
    if ( ptNext )
    {
      do
      {
        if ( ptHead[1].ptNext == (struct Node_s *)nID )
        {
          Node_Remove(ptHead);
          v5 = ptHead[3].ptNext;
          igi2_frame.nRemoved = HIWORD(v5[1].ptPrev) + v4;
          if ( v5 )
          {
            v6 = *(_DWORD *)((unsigned int)&v5[-1].ptPrev & 0xFFFFFFFC);
            --Mem_nCurrentAllocations;
            Node_Remove((_DWORD **)v6);
            memset(*(void **)(v6 + 8), 0xCDu, *(_DWORD *)(v6 + 16));
            free((void *)v6);
          }
          v7 = Mem_nCurrentAllocations;
          ptHead[3].ptNext = nullptr;
          v8 = *(_DWORD *)((unsigned int)&ptHead[-1].ptPrev & 0xFFFFFFFC);
          Mem_nCurrentAllocations = v7 - 1;
          Node_Remove((_DWORD **)v8);
          memset(*(void **)(v8 + 8), 0xCDu, *(_DWORD *)(v8 + 16));
          free((void *)v8);
          v4 = igi2_frame.nRemoved;
        }
        ptHead = ptNext;
        ptNext = ptNext->ptNext;
      }
      while ( ptNext );
      if ( v4 > 0 )
      {
        _snprintf(igi2_frame.zTemp, 0xFFu, "Network_FreeQueuesTo. Removed %d from queue[%d] to [%d]\n", v4, igi2_frame.iQueue, nID);
        NetManager_LogMessage(igi2_frame.zTemp);
      }
    }
    v1 = igi2_frame.v11 + 1;
    v9 = (int)&igi2_frame.v11[1] < 7587040;
    ++igi2_frame.iQueue;
    ++igi2_frame.v11;
  }
  while ( v9 );
}

// source: b/2/pc/pc_network.c:1057  [anchor-mhash]
void __cdecl Network_EnumAdapters()
{
  #pragma pack(push, 1)
  union
  {
    struct { void **v7; };
    struct { char igi2_o1[4]; char name[1024]; };
    char igi2_extent[1028];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct hostent *v0; // eax
  struct hostent *v1; // ebp
  void **h_addr_list; // eax
  void *v3; // esi
  _DWORD *v4; // ebx
  void *v5; // eax

  if ( gethostname(igi2_frame.name, 1024) != -1 )
  {
    v0 = gethostbyname(igi2_frame.name);
    v1 = v0;
    if ( v0 )
    {
      h_addr_list = (void **)v0->h_addr_list;
      v3 = *h_addr_list;
      igi2_frame.v7 = h_addr_list + 1;
      if ( *h_addr_list )
      {
        do
        {
          if ( v1->h_addrtype == 2 || v1->h_addrtype == 23 )
          {
            v4 = Mem_AllocFn(16, 4);
            v4[1] = 0;
            *v4 = 0;
            *((_WORD *)v4 + 4) = v1->h_addrtype;
            *((_WORD *)v4 + 5) = v1->h_length;
            v5 = Mem_AllocFn(v1->h_length, 4);
            v4[3] = v5;
            qmemcpy(v5, v3, v1->h_length);
            List_AddTail(v4, (int)&Network_tAdapterList);
          }
          v3 = *igi2_frame.v7;
        }
        while ( *igi2_frame.v7++ != nullptr );
      }
    }
  }
}

// source: b/2/pc/pc_network.c:1173  [anchor-hash]
void __cdecl Network_FreeAdapters()
{
  struct Node_s *ptHead; // ebp
  struct Node_s *i; // ebx
  struct Node_s *ptPrev; // eax
  int v3; // esi
  int v4; // ecx
  int v5; // esi

  ptHead = Network_tAdapterList.ptHead;
  for ( i = Network_tAdapterList.ptHead->ptNext; i; i = i->ptNext )
  {
    Node_Remove(ptHead);
    ptPrev = ptHead[1].ptPrev;
    if ( ptPrev )
    {
      v3 = *(_DWORD *)((unsigned int)&ptPrev[-1].ptPrev & 0xFFFFFFFC);
      --Mem_nCurrentAllocations;
      Node_Remove((_DWORD **)v3);
      memset(*(void **)(v3 + 8), 0xCDu, *(_DWORD *)(v3 + 16));
      free((void *)v3);
    }
    v4 = Mem_nCurrentAllocations;
    ptHead[1].ptPrev = nullptr;
    v5 = *(_DWORD *)((unsigned int)&ptHead[-1].ptPrev & 0xFFFFFFFC);
    Mem_nCurrentAllocations = v4 - 1;
    Node_Remove((_DWORD **)v5);
    memset(*(void **)(v5 + 8), 0xCDu, *(_DWORD *)(v5 + 16));
    free((void *)v5);
    ptHead = i;
  }
}

// source: b/2/pc/pc_network.c:1201  [anchor-hash]
void __cdecl Network_FreeGuaranteedQueue()
{
  struct Node_s *ptHead; // esi
  struct Node_s *i; // ebx
  int v2; // esi
  char zTemp[256]; // [esp+8h] [ebp-100h] BYREF

  ptHead = Network_tWaitingGuaranteedPackets.ptHead;
  for ( i = Network_tWaitingGuaranteedPackets.ptHead->ptNext; i; i = i->ptNext )
  {
    Node_Remove(ptHead);
    _snprintf(zTemp, 0xFFu, "Network_FreeGuaranteedQueue: Removing packet\n");
    NetManager_LogMessage(zTemp);
    if ( ptHead )
    {
      v2 = *(_DWORD *)((unsigned int)&ptHead[-1].ptPrev & 0xFFFFFFFC);
      --Mem_nCurrentAllocations;
      Node_Remove((_DWORD **)v2);
      memset(*(void **)(v2 + 8), 0xCDu, *(_DWORD *)(v2 + 16));
      free((void *)v2);
    }
    ptHead = i;
  }
}

// source: b/2/pc/pc_network.c:1235  [anchor-hash]
enum bool __cdecl Network_IsBanned(unsigned __int8 *nIP)
{
  struct Node_s *ptHead; // eax
  struct Node_s *ptNext; // ecx

  ptHead = Network_tBannedList.ptHead;
  ptNext = Network_tBannedList.ptHead->ptNext;
  if ( !Network_tBannedList.ptHead->ptNext )
    return false;
  while ( LOBYTE(ptHead[1].ptNext) != *nIP
       || BYTE1(ptHead[1].ptNext) != nIP[1]
       || BYTE2(ptHead[1].ptNext) != nIP[2]
       || HIBYTE(ptHead[1].ptNext) != nIP[3] )
  {
    ptHead = ptNext;
    ptNext = ptNext->ptNext;
    if ( !ptNext )
      return false;
  }
  return true;
}

// source: b/2/pc/pc_network.c:1270  [anchor-hash]
enum bool __cdecl Network_AddToBannedList(unsigned __int8 *nIP)
{
  _BYTE *v2; // eax

  if ( Network_IsBanned(nIP) )
  {
    NetManager_LogMessage("Network_AddToBannedList: IP already banned\n");
    return false;
  }
  else
  {
    v2 = Mem_AllocFn(12, 4);
    v2[8] = *nIP;
    v2[9] = nIP[1];
    v2[10] = nIP[2];
    v2[11] = nIP[3];
    *((_DWORD *)v2 + 1) = 0;
    *(_DWORD *)v2 = 0;
    List_AddTail(v2, (int)&Network_tBannedList);
    return true;
  }
}

// source: b/2/pc/pc_network.c:1308  [anchor-hash]
void __cdecl Network_PrintBannedList()
{
  unsigned __int8 *ptHead; // eax
  struct Node_s *ptNext; // esi
  int i; // edi
  char zTemp[256]; // [esp+8h] [ebp-100h] BYREF

  ptHead = (unsigned __int8 *)Network_tBannedList.ptHead;
  ptNext = Network_tBannedList.ptHead->ptNext;
  for ( i = 0; ptNext; ++i )
  {
    _snprintf(zTemp, 0xFFu, "[%d]: %u.%u.%u.%u\n", i, ptHead[8], ptHead[9], ptHead[10], ptHead[11]);
    NetManager_LogMessage(zTemp);
    ptHead = (unsigned __int8 *)ptNext;
    ptNext = ptNext->ptNext;
  }
}

// source: b/2/pc/pc_network.c:1334  [size]
struct List_s *__cdecl Network_GetBannedList()
{
  return &Network_tBannedList;
}

// source: b/2/pc/pc_network.c:1348  [anchor-callee]
void __cdecl Network_FreeBannedList()
{
  struct Node_s *ptHead; // eax
  struct Node_s *i; // ebx
  _DWORD **v2; // eax
  int v3; // esi

  ptHead = Network_tBannedList.ptHead;
  for ( i = Network_tBannedList.ptHead->ptNext; i; i = i->ptNext )
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
}

// source: b/2/pc/pc_network.c:1373  [anchor-mhash]
unsigned __int16 __cdecl Network_CalculateCRC(unsigned __int8 *pnData, int nSize)
{
  unsigned __int16 result; // ax
  int i; // ecx

  result = 0;
  for ( i = 0; i < nSize; ++i )
    result += pnData[i];
  return result;
}

// source: b/2/pc/pc_network.c:1397  [anchor-hash]
enum bool __cdecl Network_ValidatePacket(struct NetworkParseContext_s *ptParseContext)
{
  u_short v1; // di
  int v3; // ecx
  __int16 v4; // di
  int v5; // eax

  v1 = LOWORD(ptParseContext->nParsePacketOffset) - 24;
  if ( ntohs(*(_WORD *)&ptParseContext->anParsePacket[14]) > v1 )
    return false;
  v3 = ntohs(*(_WORD *)&ptParseContext->anParsePacket[14]);
  v4 = 0;
  v5 = 0;
  if ( v3 )
  {
    do
    {
      v4 += ptParseContext->anParsePacket[v5 + 20];
      ++v5;
    }
    while ( v5 < v3 );
  }
  return v4 == (__int16)ntohs(*(_WORD *)&ptParseContext->anParsePacket[12]);
}

// source: b/2/pc/pc_network.c:1446  [anchor-hash]
struct NetworkParseContext_s *__cdecl Network_ClearParseContext(
        struct NetworkParseContext_s *ptParseContext)
{
  ptParseContext->nCheckLong = 0;
  ptParseContext->nParsePacketOffset = 0;
  ptParseContext->isInsidePacket = false;
  return ptParseContext;
}

// source: b/2/pc/pc_network.c:1462  [size]
struct NetworkParseContext_s *__cdecl Network_SetupParsePacket(
        struct NetworkParseContext_s *ptParseContext,
        unsigned __int8 *pnReceiveBuffer,
        unsigned int nReceiveBufferSize)
{
  ptParseContext->pnReceiveBuffer = pnReceiveBuffer;
  ptParseContext->nReceiveBufferSize = nReceiveBufferSize;
  ptParseContext->nReceiveBufferOffset = 0;
  return ptParseContext;
}

// source: b/2/pc/pc_network.c:1478  [anchor-caller]
enum bool __cdecl Network_ParsePacket(struct NetworkParseContext_s *ptParseContext)
{
  unsigned int nCheckLong; // ebp
  u_long v2; // ebp
  BOOL v3; // esi
  int v4; // edi
  u_long v5; // eax
  unsigned int v6; // ecx
  unsigned int nParseCopyBegin; // eax
  unsigned int v8; // ecx
  enum bool isInsidePacket; // eax
  unsigned int v10; // eax

  nCheckLong = ptParseContext->nCheckLong;
  if ( ptParseContext->isInsidePacket )
    ptParseContext->nParseCopyBegin = 0;
  while ( ptParseContext->nReceiveBufferOffset < ptParseContext->nReceiveBufferSize )
  {
    v2 = ptParseContext->pnReceiveBuffer[ptParseContext->nReceiveBufferOffset] | nCheckLong;
    v3 = 0;
    v4 = 0;
    v5 = ntohl(v2);
    if ( v2 == -1159812114 )
      v4 = 1;
    else
      v3 = v2 == -559038737;
    v6 = ptParseContext->nReceiveBufferOffset + 1;
    nCheckLong = v2 << 8;
    ptParseContext->nReceiveBufferOffset = v6;
    if ( v3 )
    {
      ptParseContext->isInsidePacket = true;
      ptParseContext->nParseCopyBegin = v6;
      ptParseContext->nParsePacketOffset = 4;
      *(_DWORD *)ptParseContext->anParsePacket = v5;
    }
    if ( v4 && ptParseContext->isInsidePacket )
    {
      nParseCopyBegin = ptParseContext->nParseCopyBegin;
      v8 = ptParseContext->nReceiveBufferOffset - nParseCopyBegin;
      if ( v8 )
      {
        qmemcpy(
          &ptParseContext->anParsePacket[ptParseContext->nParsePacketOffset],
          &ptParseContext->pnReceiveBuffer[nParseCopyBegin],
          v8);
        ptParseContext->nParsePacketOffset += ptParseContext->nReceiveBufferOffset - ptParseContext->nParseCopyBegin;
      }
      if ( Network_ValidatePacket(ptParseContext) )
      {
        ptParseContext->nCheckLong = 0;
        ptParseContext->nParsePacketOffset = 0;
        ptParseContext->isInsidePacket = false;
        return true;
      }
      ptParseContext->nCheckLong = 0;
      ptParseContext->nParsePacketOffset = 0;
      ptParseContext->isInsidePacket = false;
    }
  }
  isInsidePacket = ptParseContext->isInsidePacket;
  ptParseContext->nCheckLong = nCheckLong;
  if ( isInsidePacket )
  {
    v10 = ptParseContext->nParseCopyBegin;
    if ( ptParseContext->nReceiveBufferOffset != v10 )
    {
      qmemcpy(
        &ptParseContext->anParsePacket[ptParseContext->nParsePacketOffset],
        &ptParseContext->pnReceiveBuffer[v10],
        ptParseContext->nReceiveBufferOffset - v10);
      ptParseContext->nParsePacketOffset += ptParseContext->nReceiveBufferOffset - ptParseContext->nParseCopyBegin;
    }
  }
  return false;
}

// source: b/2/pc/pc_network.c:1614  [anchor-mhash]
void __cdecl Network_InitPacket(
        struct NetworkPacket_s *ptPacket,
        unsigned __int8 ePacketType,
        int nSize)
{
  ptPacket->nPacketHeader = htonl(0xDEADBEEF);
  ptPacket->nCRC = 0;
  ptPacket->nSize = htons(nSize);
  ptPacket->ePacketType = ePacketType;
  *(unsigned int *)((char *)&ptPacket[1].nPacketHeader + nSize) = htonl(0xBADEABEE);
}

// source: b/2/pc/pc_network.c:1644  [anchor-callee]
struct NetworkPacket_s *__cdecl Network_AcquirePacket(unsigned __int8 ePacketType, int nSize)
{
  struct NetworkPacket_s *v2; // esi

  v2 = (struct NetworkPacket_s *)Mem_AllocFn(nSize + 24, 4);
  v2->nPacketHeader = htonl(0xDEADBEEF);
  v2->nCRC = 0;
  v2->nSize = htons(nSize);
  v2->ePacketType = ePacketType;
  *(unsigned int *)((char *)&v2[1].nPacketHeader + nSize) = htonl(0xBADEABEE);
  return v2;
}

// source: b/2/pc/pc_network.c:1668  [anchor-hash]
void __cdecl Network_PrintPacketLoss()
{
  if ( ServerConfig_tServerConfig.isLocalWeapon )
  {
    DebugConsole_printf("\nADDED PACKET LOSS ON SEND");
    DebugConsole_printf(
      "\nLosing %d/1000. Sent=%d. Lost=%d\n",
      ServerConfig_tServerConfig.isLocalWeapon,
      Network_nSendCounter,
      Network_nLoseCounter);
  }
  else
  {
    DebugConsole_printf("\nNO ADDED PACKET LOSS ON SEND");
  }
  DebugConsole_printf("\nNO ADDED PACKET LOSS ON RECEIVE");
}

// source: b/2/pc/pc_network.c:1698  [anchor-hash]
enum bool __cdecl Network_isLosePacket()
{
  unsigned int v1; // eax
  unsigned int v2; // edx
  unsigned int v3; // ecx
  int v4; // ecx
  int v5; // edx
  bool v6; // sf
  int v7; // eax

  if ( ServerConfig_tServerConfig.isLocalWeapon <= false )
    return false;
  if ( ServerConfig_tServerConfig.isLocalWeapon >= 1000 )
    return true;
  if ( Network_isRandomInitiated )
  {
    v3 = Network_tRandomState.anRandom[2];
    v2 = Network_tRandomState.anRandom[1];
    v1 = Network_tRandomState.anRandom[0];
  }
  else
  {
    v1 = -775290094;
    v2 = -965413034;
    v3 = 499061453;
    Network_isRandomInitiated = true;
  }
  v4 = (v1 >> 7) ^ v3;
  v5 = v4 ^ v2;
  v6 = (int)(v5 + v1) < 0;
  v7 = v5 + v1;
  Network_tRandomState.anRandom[2] = v4;
  Network_tRandomState.anRandom[1] = v5;
  Network_tRandomState.anRandom[0] = v7;
  if ( v6 )
    v7 = -v7;
  return v7 % 1000 < ServerConfig_tServerConfig.isLocalWeapon;
}

// source: b/2/pc/pc_network.c:1754  [anchor-callee]
enum bool __cdecl Network_IsShouldSendQuit()
{
  unsigned int v0; // eax
  unsigned int v1; // edx
  unsigned int v2; // ecx
  int v3; // ecx
  int v4; // edx
  bool v5; // sf
  int v6; // eax

  if ( Network_isRandomInitiated )
  {
    v2 = Network_tRandomState.anRandom[2];
    v1 = Network_tRandomState.anRandom[1];
    v0 = Network_tRandomState.anRandom[0];
  }
  else
  {
    v0 = -775290094;
    v1 = -965413034;
    v2 = 499061453;
    Network_isRandomInitiated = true;
  }
  v3 = (v0 >> 7) ^ v2;
  v4 = v3 ^ v1;
  v5 = (int)(v4 + v0) < 0;
  v6 = v4 + v0;
  Network_tRandomState.anRandom[2] = v3;
  Network_tRandomState.anRandom[1] = v4;
  Network_tRandomState.anRandom[0] = v6;
  if ( v5 )
    v6 = -v6;
  return v6 % 3 == 0;
}

// source: b/2/pc/pc_network.c:1784  [anchor-hash]
void __cdecl Network_PrintNetworkStats(void (*pfPrint)(char *, ...))
{
  char Buffer[256]; // [esp+0h] [ebp-100h] BYREF

  pfPrint((char *)&stru_6A4CDC);
  _snprintf(
    Buffer,
    0xFFu,
    "out [all %d][new %d][re %d][ack %d][ext %d][ok %d][err %d]\n",
    Network_nSendERROR + Network_nSendOK,
    Network_aSendType[0],
    Network_aSendType[1],
    Network_aSendType[2],
    Network_aSendType[3],
    Network_nSendOK,
    Network_nSendERROR);
  pfPrint(Buffer);
  _snprintf(
    Buffer,
    0xFFu,
    "out [max50 %d][max100 %d]  in [max50 %d][max100 %d]\n",
    dword_834E0C8,
    dword_834E0CC,
    dword_834E0D0,
    dword_834E0D4);
  pfPrint(Buffer);
}

// source: b/2/pc/pc_network.c:1847  [anchor-hash]
void __cdecl Network_ClearNetworkStats()
{
  DWORD PerformanceCounter; // eax

  Network_nSendOK = 0;
  Network_nSendERROR = 0;
  Network_nSendBytes = 0;
  dword_834E0C8 = 0;
  dword_834E0CC = 0;
  dword_834E0D0 = 0;
  dword_834E0D4 = 0;
  if ( Timer_isPerformanceCounter )
    PerformanceCounter = Timer_GetPerformanceCounter();
  else
    PerformanceCounter = GetTickCount();
  Network_nSendStatTimer = PerformanceCounter - Timer_nStartTime;
  Network_aSendType[0] = 0;
  Network_aSendType[1] = 0;
  Network_aSendType[2] = 0;
  Network_nReceivedQUIT = 0;
  Network_aSendType[3] = 0;
}

// source: b/2/pc/pc_network.c:1873  [anchor-strings]
enum bool __cdecl Network_IsManySendErrors(int nMinSent, float vPercent)
{
  #pragma pack(push, 1)
  union
  {
    struct { int nTotal; };
    struct { char igi2_o1[4]; char zTemp[256]; };
    char igi2_extent[260];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  double v2; // st7

  if ( Network_nSendERROR + Network_nSendOK < nMinSent )
    return false;
  v2 = (double)Network_nSendERROR * 100.0 / (double)(Network_nSendERROR + Network_nSendOK);
  *(float *)&igi2_frame.nTotal = v2;
  if ( v2 > 0.0 )
  {
    _snprintf(igi2_frame.zTemp, 0xFFu, "Network: Error send percent: %.1f\n", *(float *)&igi2_frame.nTotal);
    NetManager_LogMessage(igi2_frame.zTemp);
  }
  return *(float *)&igi2_frame.nTotal >= (double)vPercent;
}

// source: b/2/pc/pc_network.c:1914  [anchor-mhash]
enum bool __cdecl Network_IsNoSendErrors(int nMinSent)
{
  return Network_nSendERROR + Network_nSendOK >= nMinSent && !Network_nSendERROR;
}

// source: b/2/pc/pc_network.c:1932  [size]
struct NetworkStat_s *__cdecl Network_GetSendStats(int *index, int *nMax)
{
  *index = Network_nSendStatIndex;
  *nMax = 200;
  return Network_aSendStat;
}

double __cdecl sub_447A40(int a1)
{
  int v1; // ebx
  DWORD PerformanceCounter; // eax
  DWORD v3; // esi
  int v4; // ecx
  int nSize; // edx
  int v6; // eax
  int v7; // edx
  int v8; // eax
  int v9; // edx
  int v10; // eax
  int v11; // edx
  int v12; // eax
  int v13; // edx
  int v14; // eax
  int v15; // edx
  int v16; // eax
  int v17; // edx
  int v18; // eax
  int v19; // edx
  int v20; // eax
  int v21; // edx
  int v22; // eax
  int v23; // edx
  int v24; // eax
  double result; // st7
  int v26; // [esp+Ch] [ebp-Ch]
  int v27; // [esp+10h] [ebp-8h]
  int v28; // [esp+14h] [ebp-4h]

  v1 = 0;
  v26 = 0;
  v27 = 0;
  if ( Timer_isPerformanceCounter )
    PerformanceCounter = Timer_GetPerformanceCounter();
  else
    PerformanceCounter = GetTickCount();
  v3 = PerformanceCounter - Timer_nStartTime;
  v4 = Network_nSendStatIndex + 2;
  v28 = 20;
  do
  {
    nSize = Network_aSendStat[(v4 - 1) % 200].nSize;
    v6 = v3 - Network_aSendStat[(v4 - 1) % 200].nTime;
    if ( v6 < a1 )
      v26 += nSize;
    if ( v6 < 50 )
      v1 += nSize;
    if ( v6 < 100 )
      v27 += nSize;
    v7 = Network_aSendStat[v4 % 200].nSize;
    v8 = v3 - Network_aSendStat[v4 % 200].nTime;
    if ( v8 < a1 )
      v26 += v7;
    if ( v8 < 50 )
      v1 += v7;
    if ( v8 < 100 )
      v27 += v7;
    v9 = Network_aSendStat[(v4 + 1) % 200].nSize;
    v10 = v3 - Network_aSendStat[(v4 + 1) % 200].nTime;
    if ( v10 < a1 )
      v26 += v9;
    if ( v10 < 50 )
      v1 += v9;
    if ( v10 < 100 )
      v27 += v9;
    v11 = Network_aSendStat[(v4 + 2) % 200].nSize;
    v12 = v3 - Network_aSendStat[(v4 + 2) % 200].nTime;
    if ( v12 < a1 )
      v26 += v11;
    if ( v12 < 50 )
      v1 += v11;
    if ( v12 < 100 )
      v27 += v11;
    v13 = Network_aSendStat[(v4 + 3) % 200].nSize;
    v14 = v3 - Network_aSendStat[(v4 + 3) % 200].nTime;
    if ( v14 < a1 )
      v26 += v13;
    if ( v14 < 50 )
      v1 += v13;
    if ( v14 < 100 )
      v27 += v13;
    v15 = Network_aSendStat[(v4 + 4) % 200].nSize;
    v16 = v3 - Network_aSendStat[(v4 + 4) % 200].nTime;
    if ( v16 < a1 )
      v26 += v15;
    if ( v16 < 50 )
      v1 += v15;
    if ( v16 < 100 )
      v27 += v15;
    v17 = Network_aSendStat[(v4 + 5) % 200].nSize;
    v18 = v3 - Network_aSendStat[(v4 + 5) % 200].nTime;
    if ( v18 < a1 )
      v26 += v17;
    if ( v18 < 50 )
      v1 += v17;
    if ( v18 < 100 )
      v27 += v17;
    v19 = Network_aSendStat[(v4 + 6) % 200].nSize;
    v20 = v3 - Network_aSendStat[(v4 + 6) % 200].nTime;
    if ( v20 < a1 )
      v26 += v19;
    if ( v20 < 50 )
      v1 += v19;
    if ( v20 < 100 )
      v27 += v19;
    v21 = Network_aSendStat[(v4 + 7) % 200].nSize;
    v22 = v3 - Network_aSendStat[(v4 + 7) % 200].nTime;
    if ( v22 < a1 )
      v26 += v21;
    if ( v22 < 50 )
      v1 += v21;
    if ( v22 < 100 )
      v27 += v21;
    v23 = Network_aSendStat[(v4 + 8) % 200].nSize;
    v24 = v3 - Network_aSendStat[(v4 + 8) % 200].nTime;
    if ( v24 < a1 )
      v26 += v23;
    if ( v24 < 50 )
      v1 += v23;
    if ( v24 < 100 )
      v27 += v23;
    v4 += 10;
    --v28;
  }
  while ( v28 );
  if ( v1 > dword_834E0C8 )
    dword_834E0C8 = v1;
  result = (double)v26 * 0.0009765625 / ((double)a1 * 0.0010000000474974513);
  if ( v27 > dword_834E0CC )
    dword_834E0CC = v27;
  return result;
}

double __cdecl sub_447CF0(int a1)
{
  int v1; // ebx
  DWORD PerformanceCounter; // eax
  DWORD v3; // esi
  int v4; // ecx
  int nSize; // edx
  int v6; // eax
  int v7; // edx
  int v8; // eax
  int v9; // edx
  int v10; // eax
  int v11; // edx
  int v12; // eax
  int v13; // edx
  int v14; // eax
  int v15; // edx
  int v16; // eax
  int v17; // edx
  int v18; // eax
  int v19; // edx
  int v20; // eax
  int v21; // edx
  int v22; // eax
  int v23; // edx
  int v24; // eax
  double result; // st7
  int v26; // [esp+Ch] [ebp-Ch]
  int v27; // [esp+10h] [ebp-8h]
  int v28; // [esp+14h] [ebp-4h]

  v1 = 0;
  v26 = 0;
  v27 = 0;
  if ( Timer_isPerformanceCounter )
    PerformanceCounter = Timer_GetPerformanceCounter();
  else
    PerformanceCounter = GetTickCount();
  v3 = PerformanceCounter - Timer_nStartTime;
  v4 = Network_nReceiveStatIndex + 2;
  v28 = 20;
  do
  {
    nSize = Network_aReceiveStat[(v4 - 1) % 200].nSize;
    v6 = v3 - Network_aReceiveStat[(v4 - 1) % 200].nTime;
    if ( v6 < a1 )
      v26 += nSize;
    if ( v6 < 50 )
      v1 += nSize;
    if ( v6 < 100 )
      v27 += nSize;
    v7 = Network_aReceiveStat[v4 % 200].nSize;
    v8 = v3 - Network_aReceiveStat[v4 % 200].nTime;
    if ( v8 < a1 )
      v26 += v7;
    if ( v8 < 50 )
      v1 += v7;
    if ( v8 < 100 )
      v27 += v7;
    v9 = Network_aReceiveStat[(v4 + 1) % 200].nSize;
    v10 = v3 - Network_aReceiveStat[(v4 + 1) % 200].nTime;
    if ( v10 < a1 )
      v26 += v9;
    if ( v10 < 50 )
      v1 += v9;
    if ( v10 < 100 )
      v27 += v9;
    v11 = Network_aReceiveStat[(v4 + 2) % 200].nSize;
    v12 = v3 - Network_aReceiveStat[(v4 + 2) % 200].nTime;
    if ( v12 < a1 )
      v26 += v11;
    if ( v12 < 50 )
      v1 += v11;
    if ( v12 < 100 )
      v27 += v11;
    v13 = Network_aReceiveStat[(v4 + 3) % 200].nSize;
    v14 = v3 - Network_aReceiveStat[(v4 + 3) % 200].nTime;
    if ( v14 < a1 )
      v26 += v13;
    if ( v14 < 50 )
      v1 += v13;
    if ( v14 < 100 )
      v27 += v13;
    v15 = Network_aReceiveStat[(v4 + 4) % 200].nSize;
    v16 = v3 - Network_aReceiveStat[(v4 + 4) % 200].nTime;
    if ( v16 < a1 )
      v26 += v15;
    if ( v16 < 50 )
      v1 += v15;
    if ( v16 < 100 )
      v27 += v15;
    v17 = Network_aReceiveStat[(v4 + 5) % 200].nSize;
    v18 = v3 - Network_aReceiveStat[(v4 + 5) % 200].nTime;
    if ( v18 < a1 )
      v26 += v17;
    if ( v18 < 50 )
      v1 += v17;
    if ( v18 < 100 )
      v27 += v17;
    v19 = Network_aReceiveStat[(v4 + 6) % 200].nSize;
    v20 = v3 - Network_aReceiveStat[(v4 + 6) % 200].nTime;
    if ( v20 < a1 )
      v26 += v19;
    if ( v20 < 50 )
      v1 += v19;
    if ( v20 < 100 )
      v27 += v19;
    v21 = Network_aReceiveStat[(v4 + 7) % 200].nSize;
    v22 = v3 - Network_aReceiveStat[(v4 + 7) % 200].nTime;
    if ( v22 < a1 )
      v26 += v21;
    if ( v22 < 50 )
      v1 += v21;
    if ( v22 < 100 )
      v27 += v21;
    v23 = Network_aReceiveStat[(v4 + 8) % 200].nSize;
    v24 = v3 - Network_aReceiveStat[(v4 + 8) % 200].nTime;
    if ( v24 < a1 )
      v26 += v23;
    if ( v24 < 50 )
      v1 += v23;
    if ( v24 < 100 )
      v27 += v23;
    v4 += 10;
    --v28;
  }
  while ( v28 );
  if ( v1 > dword_834E0D0 )
    dword_834E0D0 = v1;
  result = (double)v26 * 0.0009765625 / ((double)a1 * 0.0010000000474974513);
  if ( v27 > dword_834E0D4 )
    dword_834E0D4 = v27;
  return result;
}

// source: b/2/pc/pc_network.c:1947  [size]
struct NetworkStat_s *__cdecl Network_GetReceiveStats(int *index, int *nMax)
{
  *index = Network_nReceiveStatIndex;
  *nMax = 200;
  return Network_aReceiveStat;
}

// source: b/2/pc/pc_network.c:1964  [anchor-strings]
int __cdecl Network_Send(char *buf, int nLen, struct sockaddr *ptSockAddr, int nSockAddrSize)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct timeval timeout; };
    struct { char igi2_o1[8]; char Buffer[256]; };
    struct { char igi2_o2[264]; fd_set writefds; };
    char igi2_extent[524];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  _DWORD *v5; // esi
  SOCKET v6; // edi
  int v7; // eax
  int Error; // eax
  int v9; // ecx
  char *ErrorDesc; // eax
  int v11; // eax
  int v12; // eax
  int v13; // eax
  int v14; // ecx
  char *v15; // eax
  int v16; // eax
  int v17; // ebx
  bool v18; // zf
  DWORD TickCount; // eax
  int result; // eax

  igi2_frame.timeout.tv_sec = 0;
  igi2_frame.timeout.tv_usec = 0;
  v5 = (_DWORD *)(16 * Network_nSendStatIndex + 7587184);
  v6 = Network_UDPSocket;
  igi2_frame.writefds.fd_array[0] = Network_UDPSocket;
  igi2_frame.writefds.fd_count = 1;
  Network_nSendStatIndex = (Network_nSendStatIndex + 1) % 200;
  v7 = select(64, nullptr, &igi2_frame.writefds, nullptr, &igi2_frame.timeout);
  if ( v7 == -1 )
  {
    v5[2] = 1;
    v5[3] = WSAGetLastError();
    Error = WSAGetLastError();
    v9 = Error;
    if ( Error != 10054 )
    {
      ErrorDesc = Network_GetErrorDesc(Error);
      _snprintf(igi2_frame.Buffer, 0xFFu, "\n%s:error code=%d, desc=%s\n", "Network_Send: DROPPING DATA. select():", v9, ErrorDesc);
      NetManager_LogMessage(igi2_frame.Buffer);
    }
LABEL_4:
    WSASetLastError(0);
    ++Network_nSendERROR;
    goto LABEL_15;
  }
  if ( v7 )
  {
    v12 = sendto(v6, buf, nLen, 0, ptSockAddr, nSockAddrSize);
    if ( v12 == -1 )
    {
      v5[2] = 2;
      v5[3] = WSAGetLastError();
      v13 = WSAGetLastError();
      v14 = v13;
      if ( v13 != 10054 )
      {
        v15 = Network_GetErrorDesc(v13);
        _snprintf(igi2_frame.Buffer, 0xFFu, "\n%s:error code=%d, desc=%s\n", "Network_Send():sendto", v14, v15);
        NetManager_LogMessage(igi2_frame.Buffer);
      }
      goto LABEL_4;
    }
    if ( v12 != nLen )
    {
      _snprintf(igi2_frame.Buffer, 0xFFu, "Network_Send():incomplete packet sent (%d/%d)\n", v12, nLen);
      NetManager_LogMessage(igi2_frame.Buffer);
    }
    v16 = Network_nSendOK + 1;
    v5[2] = 0;
    Network_nSendOK = v16;
  }
  else
  {
    v11 = Network_nSendERROR + 1;
    v5[2] = 3;
    Network_nSendERROR = v11;
  }
  v5[3] = 0;
LABEL_15:
  v17 = nLen + 28;
  v18 = Timer_isPerformanceCounter == 0;
  Network_nSendBytes += v17;
  v5[1] = v17;
  if ( v18 )
    TickCount = GetTickCount();
  else
    TickCount = Timer_GetPerformanceCounter();
  result = TickCount - Timer_nStartTime;
  *v5 = result;
  return result;
}

// source: b/2/pc/pc_network.c:2071  [anchor-caller]
void __cdecl Network_SendSocketMessage(
        struct sockaddr *ptSockAddr,
        int nSockAddrSize,
        struct NetworkPacket_s *ptPacket,
        enum bool isDeleteWhenSent,
        enum NetworkSendType_e eSendType)
{
  int v7; // ecx
  u_short v8; // dx
  int v9; // eax
  u_short v10; // ax
  int v11; // esi

  v7 = ntohs(ptPacket->nSize);
  v8 = 0;
  v9 = 0;
  if ( v7 )
  {
    do
      v8 += *((unsigned __int8 *)&ptPacket[1].nPacketHeader + v9++);
    while ( v9 < v7 );
  }
  ptPacket->nCRC = htons(v8);
  ++Network_aSendType[eSendType];
  if ( !memcmp(&Network_LocalAddress, ptSockAddr, 8u) || Network_isLosePacket() == false )
  {
    v10 = ntohs(ptPacket->nSize);
    ++Network_nSendCounter;
    Network_Send((char *)ptPacket, v10 + 24, ptSockAddr, nSockAddrSize);
  }
  else
  {
    ++Network_nLoseCounter;
  }
  if ( isDeleteWhenSent )
  {
    v11 = *(_DWORD *)((unsigned int)&ptPacket[-1].ePacketType & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v11);
    memset(*(void **)(v11 + 8), 0xCDu, *(_DWORD *)(v11 + 16));
    free((void *)v11);
  }
}

// source: b/2/pc/pc_network.c:2118  [anchor-callee]
void __cdecl Network_SetSocketData(
        struct sockaddr_in *ptSocket,
        unsigned __int8 *nIP,
        unsigned __int16 *nPort)
{
  *nPort = ntohs(ptSocket->sin_port);
  *(IN_ADDR *)nIP = ptSocket->sin_addr;
}

// source: b/2/pc/pc_network.c:2140  [anchor-strings]
void __cdecl Network_GetHostnameByNetworkID(char *zString, int nLength, int eNetworkID)
{
  struct Node_s *ptHead; // ecx
  struct Node_s *ptNext; // eax
  unsigned __int8 *v5; // esi
  u_short v6; // ax

  ptHead = Network_tIDList.ptHead;
  ptNext = Network_tIDList.ptHead->ptNext;
  if ( Network_tIDList.ptHead->ptNext )
  {
    while ( ptHead[1].ptNext != (struct Node_s *)eNetworkID )
    {
      ptHead = ptNext;
      ptNext = ptNext->ptNext;
      if ( !ptNext )
        goto LABEL_4;
    }
    v5 = (unsigned __int8 *)&ptHead[2];
    if ( ptHead == (struct Node_s *)-16 )
    {
      strncpy(zString, "[NO IP:PORT]", nLength);
    }
    else
    {
      v6 = ntohs(HIWORD(ptHead[2].ptNext));
      _snprintf(zString, nLength, "%u.%u.%u.%u:%d", v5[4], v5[5], v5[6], v5[7], v6);
    }
  }
  else
  {
LABEL_4:
    strncpy(zString, "[NO ITEM]", nLength);
  }
}

// source: b/2/pc/pc_network.c:2180  [anchor-mhash]
unsigned int __cdecl Network_GetUserIPByNetworkID(int eNetworkID)
{
  struct Node_s *ptHead; // ecx
  struct Node_s *ptNext; // eax

  ptHead = Network_tIDList.ptHead;
  ptNext = Network_tIDList.ptHead->ptNext;
  if ( !Network_tIDList.ptHead->ptNext )
    return 0;
  while ( ptHead[1].ptNext != (struct Node_s *)eNetworkID )
  {
    ptHead = ptNext;
    ptNext = ptNext->ptNext;
    if ( !ptNext )
      return 0;
  }
  if ( ptHead == (struct Node_s *)-16 )
    return 0;
  else
    return (unsigned int)ptHead[2].ptPrev;
}

// source: b/2/pc/pc_network.c:2209  [anchor-strings]
void __cdecl Network_HandleSendQueues()
{
  #pragma pack(push, 1)
  union
  {
    struct { int iQueue; };
    struct { char igi2_o1[4]; struct Node_s *ptTemp; };
    struct { char igi2_o2[8]; char zTemp[256]; };
    struct { char igi2_o3[264]; char Buffer[256]; };
    char igi2_extent[520];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v0; // eax
  struct Node_s *ptHead; // esi
  struct Node_s *v2; // edi
  struct Node_s *v3; // ecx
  int v4; // eax
  int v5; // esi
  int ResendDelay; // ebx
  DWORD TickCount; // eax
  int v8; // eax
  enum NetworkSendType_e v9; // ebx
  DWORD PerformanceCounter; // eax
  int v11; // ecx
  struct Node_s *v12; // ecx
  struct Node_s *ptNext; // eax
  struct sockaddr *v14; // edi
  struct Node_s *v15; // eax
  int v16; // ebx
  int v17; // esi

  v0 = 0;
  igi2_frame.iQueue = 0;
  do
  {
    ptHead = Network_atQueues[v0].tList.ptHead;
    for ( igi2_frame.ptTemp = ptHead->ptNext; igi2_frame.ptTemp; v0 = igi2_frame.iQueue )
    {
      if ( v0 )
      {
        v12 = Network_tIDList.ptHead;
        ptNext = Network_tIDList.ptHead->ptNext;
        if ( Network_tIDList.ptHead->ptNext )
        {
          while ( v12[1].ptNext != ptHead[1].ptNext )
          {
            v12 = ptNext;
            ptNext = ptNext->ptNext;
            if ( !ptNext )
              goto LABEL_21;
          }
          v14 = (struct sockaddr *)v12;
        }
        else
        {
LABEL_21:
          v14 = nullptr;
        }
        NetManager_LogMessage("Network_HandleSendQueues: Non-guaranteed queue non-empty\n");
        if ( v14 )
        {
          ptHead[3].ptNext->ptPrev = ptHead[1].ptPrev;
          ptHead[3].ptNext[1].ptNext = ptHead[1].ptNext;
          Network_SendSocketMessage(
            v14 + 1,
            16,
            (struct NetworkPacket_s *)ptHead[3].ptNext,
            true,
            NETWORK_SENDTYPE_FRESH);
        }
        else
        {
          _snprintf(
            igi2_frame.Buffer,
            0xFFu,
            "Network_HandleSendQueues: No socket found for [%d], skipping non-guaranteed message\n",
            ptHead[1].ptNext);
          NetManager_LogMessage(igi2_frame.Buffer);
          v15 = ptHead[3].ptNext;
          if ( v15 )
          {
            --Mem_nCurrentAllocations;
            v16 = *(_DWORD *)((unsigned int)&v15[-1].ptPrev & 0xFFFFFFFC);
            Node_Remove((_DWORD **)v16);
            memset(*(void **)(v16 + 8), 0xCDu, *(_DWORD *)(v16 + 16));
            free((void *)v16);
          }
          ptHead[3].ptNext = nullptr;
        }
        Node_Remove(ptHead);
        v17 = *(_DWORD *)((unsigned int)&ptHead[-1].ptPrev & 0xFFFFFFFC);
        --Mem_nCurrentAllocations;
        Node_Remove((_DWORD **)v17);
        memset(*(void **)(v17 + 8), 0xCDu, *(_DWORD *)(v17 + 16));
        free((void *)v17);
      }
      else
      {
        v2 = Network_tIDList.ptHead;
        v3 = Network_tIDList.ptHead->ptNext;
        if ( Network_tIDList.ptHead->ptNext )
        {
          v4 = (int)ptHead[1].ptNext;
          while ( v2[1].ptNext != (struct Node_s *)v4 )
          {
            v2 = v3;
            v3 = v3->ptNext;
            if ( !v3 )
              goto LABEL_8;
          }
          ResendDelay = NetManager_GetResendDelay((int)ptHead[2].ptPrev, v4);
          if ( !ptHead[2].ptPrev
            || (!Timer_isPerformanceCounter ? (TickCount = GetTickCount()) : (TickCount = Timer_GetPerformanceCounter()),
                (int)(TickCount - Timer_nStartTime - (unsigned int)ptHead[2].ptNext) > ResendDelay) )
          {
            ptHead[3].ptNext->ptPrev = ptHead[1].ptPrev;
            v8 = Timer_isPerformanceCounter;
            ptHead[3].ptNext[1].ptNext = ptHead[1].ptNext;
            v9 = ptHead[2].ptPrev != nullptr;
            if ( v8 )
              PerformanceCounter = Timer_GetPerformanceCounter();
            else
              PerformanceCounter = GetTickCount();
            v11 = (int)&ptHead[2].ptPrev->ptNext + 1;
            ptHead[2].ptNext = (struct Node_s *)(PerformanceCounter - Timer_nStartTime);
            ptHead[2].ptPrev = (struct Node_s *)v11;
            Network_SendSocketMessage(
              (struct sockaddr *)&v2[2],
              16,
              (struct NetworkPacket_s *)ptHead[3].ptNext,
              false,
              v9);
          }
        }
        else
        {
LABEL_8:
          _snprintf(
            igi2_frame.zTemp,
            0xFFu,
            "Network_HandleSendQueues: No socket found for [%d], deleting guaranteed message\n",
            ptHead[1].ptNext);
          NetManager_LogMessage(igi2_frame.zTemp);
          Node_Remove(ptHead);
          v5 = *(_DWORD *)((unsigned int)&ptHead[-1].ptPrev & 0xFFFFFFFC);
          --Mem_nCurrentAllocations;
          Node_Remove((_DWORD **)v5);
          memset(*(void **)(v5 + 8), 0xCDu, *(_DWORD *)(v5 + 16));
          free((void *)v5);
        }
      }
      ptHead = igi2_frame.ptTemp;
      igi2_frame.ptTemp = igi2_frame.ptTemp->ptNext;
    }
    igi2_frame.iQueue = ++v0;
  }
  while ( v0 < 4 );
}

// source: b/2/pc/pc_network.c:2348  [anchor-hash]
int __cdecl Network_NumberOfGuaranteedBufferedForHost(int eNetworkID)
{
  struct Node_s *ptHead; // edx
  struct Node_s *ptNext; // ecx
  int result; // eax

  ptHead = Network_atQueues[0].tList.ptHead;
  ptNext = Network_atQueues[0].tList.ptHead->ptNext;
  for ( result = 0; ptNext; ptNext = ptNext->ptNext )
  {
    if ( ptHead[1].ptNext == (struct Node_s *)eNetworkID )
      ++result;
    ptHead = ptNext;
  }
  return result;
}

// source: b/2/pc/pc_network.c:2378  [anchor-callee]
enum bool __cdecl Network_ProcessGuaranteedPackage(
        struct NetworkThreadContext_s *ptThreadContext,
        struct NetworkPacket_s *ptIncomingPacket,
        unsigned int eNetworkID,
        struct sockaddr_in *ptSockAddr)
{
  unsigned int nPacketID; // edx
  unsigned int v6; // eax
  struct Node_s *ptHead; // ecx
  struct Node_s *ptNext; // eax
  int v10; // esi
  _DWORD *v11; // eax

  nPacketID = ptIncomingPacket->nPacketID;
  v6 = Network_nLastReceivedGuaranteedPacketID[eNetworkID] + 1;
  if ( nPacketID == v6 )
  {
    Network_nLastReceivedGuaranteedPacketID[eNetworkID] = v6;
    return true;
  }
  else
  {
    if ( nPacketID > v6 )
    {
      ptHead = Network_tWaitingGuaranteedPackets.ptHead;
      ptNext = Network_tWaitingGuaranteedPackets.ptHead->ptNext;
      v10 = 0;
      if ( !Network_tWaitingGuaranteedPackets.ptHead->ptNext )
        goto LABEL_9;
      do
      {
        if ( ptHead[12].ptPrev == (struct Node_s *)nPacketID )
          v10 = 1;
        ptHead = ptNext;
        ptNext = ptNext->ptNext;
      }
      while ( ptNext );
      if ( !v10 )
      {
LABEL_9:
        v11 = Mem_AllocFn(16484, 4);
        v11[1] = 0;
        *v11 = 0;
        v11[2] = *(_DWORD *)&ptSockAddr->sin_family;
        v11[3] = ptSockAddr->sin_addr.S_un.S_addr;
        v11[4] = *(_DWORD *)ptSockAddr->sin_zero;
        v11[5] = *(_DWORD *)&ptSockAddr->sin_zero[4];
        qmemcpy(v11 + 6, ptThreadContext, 0x404Cu);
        List_AddTail(v11, (int)&Network_tWaitingGuaranteedPackets);
      }
    }
    return false;
  }
}

// source: b/2/pc/pc_network.c:2450  [size]
unsigned __int8 __cdecl Network_GetLastConnectionResponse()
{
  return Network_nLastConnectionResponse;
}

// source: b/2/pc/pc_network.c:2464  [anchor-strings]
void __cdecl Network_ClientHandleReceivedPacket(
        struct NetworkThreadContext_s *ptThreadContext,
        struct NetworkParseContext_s *ptParseContext,
        struct sockaddr_in *ptSockAddr)
{
  #pragma pack(push, 1)
  union
  {
    struct { char *v18; };
    struct { char igi2_o1[24]; int eNetworkID[8]; };
    struct { char igi2_o2[56]; char Buffer[256]; };
    char igi2_extent[312];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct NetworkIDListItem_s *IDItemFromAddr; // eax
  ULONG S_addr; // eax
  int v7; // edx
  int v8; // eax
  int v9; // ecx
  int v10; // edx
  int v11; // eax
  enum NetworkMessage_e v12; // ebp
  unsigned int v13; // ecx
  struct NetworkPacket_s *v14; // eax
  struct Node_s *ptHead; // esi
  struct Node_s *i; // edi
  _DWORD **v17; // eax

  igi2_frame.eNetworkID[0] = -1;
  IDItemFromAddr = Network_GetIDItemFromAddr(ptSockAddr);
  if ( IDItemFromAddr )
    igi2_frame.eNetworkID[0] = IDItemFromAddr->eID;
  S_addr = ptSockAddr->sin_addr.S_un.S_addr;
  igi2_frame.eNetworkID[1] = *(_DWORD *)&ptSockAddr->sin_family;
  v7 = *(_DWORD *)ptSockAddr->sin_zero;
  igi2_frame.eNetworkID[2] = S_addr;
  v8 = *(_DWORD *)&ptSockAddr->sin_zero[4];
  v9 = *(unsigned __int16 *)&ptParseContext->anParsePacket[14];
  igi2_frame.eNetworkID[3] = v7;
  igi2_frame.eNetworkID[4] = v8;
  igi2_frame.eNetworkID[5] = (int)ptThreadContext;
  igi2_frame.eNetworkID[6] = (int)&ptParseContext->anParsePacket[20];
  v10 = ntohs(v9);
  v11 = ptParseContext->anParsePacket[16] - 1;
  igi2_frame.eNetworkID[7] = v10;
  switch ( v11 )
  {
    case 0:
      Network_nLastConnectionResponse = ptParseContext->anParsePacket[20];
      switch ( Network_nLastConnectionResponse )
      {
        case 0u:
          v12 = NETWORKMESSAGE_CLIENT_CONNECTIONSUCCESS;
          Network_AddIDItem(0, ptSockAddr);
          Network_AddIDItem(*(_DWORD *)&ptParseContext->anParsePacket[28], &ptThreadContext->tSockAddr);
          ptThreadContext->eStatus = NETWORK_THREADSTATUS_CONNECTED;
          _snprintf(
            igi2_frame.Buffer,
            0xFFu,
            "Network: Connection succeeded, got networkID=%d\n",
            *(_DWORD *)&ptParseContext->anParsePacket[28]);
          NetManager_LogMessage(igi2_frame.Buffer);
          goto LABEL_16;
        case 1u:
          igi2_frame.v18 = "Network: Connection failed: PASSWORD\n";
          goto LABEL_15;
        case 2u:
          igi2_frame.v18 = "Network: Connection failed: BANNED\n";
          goto LABEL_15;
        case 3u:
          igi2_frame.v18 = "Network: Connection failed: SERVERFULL\n";
          goto LABEL_15;
        case 4u:
          igi2_frame.v18 = "Network: Connection failed: WRONG_MAP\n";
          goto LABEL_15;
        case 5u:
          igi2_frame.v18 = "Network: Connection failed: Server out of IDs\n";
          goto LABEL_15;
        case 6u:
          igi2_frame.v18 = "Network: Connection failed: SOCKET BUSY\n";
          goto LABEL_15;
        default:
          igi2_frame.v18 = "Network: Invalid message\n";
LABEL_15:
          ptThreadContext->eStatus = NETWORK_THREADSTATUS_NOTCONNECTED;
          v12 = NETWORKMESSAGE_CLIENT_CONNECTIONFAILED;
          NetManager_LogMessage(igi2_frame.v18);
LABEL_16:
          ptThreadContext->pfHandler(
            ptThreadContext->pxHandlerContext,
            v12,
            (struct NetworkMessageContext_s *)igi2_frame.eNetworkID);
          break;
      }
      break;
    case 1:
      if ( igi2_frame.eNetworkID[0] != -1 )
        NetManager_RegisterInput(igi2_frame.eNetworkID[0]);
      ptThreadContext->pfHandler(
        ptThreadContext->pxHandlerContext,
        NETWORKMESSAGE_RECEIVEDDATA,
        (struct NetworkMessageContext_s *)igi2_frame.eNetworkID);
      break;
    case 2:
      v13 = igi2_frame.eNetworkID[0];
      if ( igi2_frame.eNetworkID[0] != -1 )
      {
        NetManager_RegisterInput(igi2_frame.eNetworkID[0]);
        v13 = igi2_frame.eNetworkID[0];
      }
      if ( Network_ProcessGuaranteedPackage(
             ptThreadContext,
             (struct NetworkPacket_s *)ptParseContext->anParsePacket,
             v13,
             ptSockAddr) )
      {
        ptThreadContext->pfHandler(
          ptThreadContext->pxHandlerContext,
          NETWORKMESSAGE_RECEIVEDGUARANTEEDDATA,
          (struct NetworkMessageContext_s *)igi2_frame.eNetworkID);
      }
      v14 = Network_AcquirePacket(4u, 20);
      v14->nPacketID = *(_DWORD *)&ptParseContext->anParsePacket[4];
      v14->eDestinationID = *(_DWORD *)&ptParseContext->anParsePacket[8];
      Network_SendSocketMessage((struct sockaddr *)&ptThreadContext->tSockAddr, 16, v14, true, NETWORK_SENDTYPE_ACK);
      break;
    case 3:
      NetManager_RegisterInput(igi2_frame.eNetworkID[0]);
      ptHead = Network_atQueues[0].tList.ptHead;
      for ( i = Network_atQueues[0].tList.ptHead->ptNext; i; i = i->ptNext )
      {
        if ( ptHead[1].ptPrev == *(struct Node_s **)&ptParseContext->anParsePacket[4]
          && ptHead[1].ptNext == *(struct Node_s **)&ptParseContext->anParsePacket[8] )
        {
          Mem_DeAllocFn(ptHead[3].ptNext);
          ptHead[3].ptNext = nullptr;
          v17 = Node_Remove(ptHead);
          Mem_DeAllocFn(v17);
        }
        ptHead = i;
      }
      break;
    case 5:
      NetManager_LogMessage("Received server info\n");
      ptThreadContext->pfHandler(
        ptThreadContext->pxHandlerContext,
        NETWORKMESSAGE_CLIENT_SERVERINFO,
        (struct NetworkMessageContext_s *)igi2_frame.eNetworkID);
      break;
    case 6:
      ++Network_nReceivedQUIT;
      NetManager_LogMessage("Received QUIT message\n");
      break;
    case 7:
      NetManager_LogMessage("Received CONSOLE message\n");
      break;
    default:
      return;
  }
}

// source: b/2/pc/pc_network.c:2697  [size]
enum bool __cdecl Network_IsReceivedQuit(int nNumber)
{
  return Network_nReceivedQUIT >= nNumber;
}

// source: b/2/pc/pc_network.c:2714  [anchor-callee]
void __cdecl Network_SendQuitMessage(struct sockaddr_in *ptSockAddr)
{
  struct NetworkPacket_s *v1; // esi

  v1 = (struct NetworkPacket_s *)Mem_AllocFn(44, 4);
  v1->nPacketHeader = htonl(0xDEADBEEF);
  v1->nCRC = 0;
  v1->nSize = htons(0x14u);
  v1->ePacketType = 7;
  v1[2].nPacketHeader = htonl(0xBADEABEE);
  v1->nPacketID = 0;
  v1->eDestinationID = 0;
  Network_SendSocketMessage((struct sockaddr *)ptSockAddr, 16, v1, true, NETWORK_SENDTYPE_EXTERNAL);
}

// source: b/2/pc/pc_network.c:2739  [anchor-callee]
void __cdecl Network_SendConsoleMessage(struct sockaddr_in *ptSockAddr, char *zText)
{
  struct NetworkPacket_s *v3; // ebp
  unsigned int v4; // eax
  char *v5; // ecx

  if ( strlen(zText) )
  {
    v3 = Network_AcquirePacket(8u, strlen(zText) + 4);
    v3[1].nPacketHeader = strlen(zText);
    LOBYTE(v3[1].nPacketID) = 0;
    v4 = strlen(zText) + 1;
    v5 = (char *)&v3[1].nPacketHeader + 3;
    while ( *++v5 )
      ;
    qmemcpy(v5, zText, v4);
    Network_SendSocketMessage((struct sockaddr *)ptSockAddr, 16, v3, true, NETWORK_SENDTYPE_EXTERNAL);
  }
}

// source: b/2/pc/pc_network.c:2773  [anchor-strings]
void __cdecl Network_SometimesSendQuit(struct sockaddr_in *ptSockAddr)
{
  #pragma pack(push, 1)
  union
  {
    struct { UCHAR nIP_1; };
    struct { char igi2_o1[1]; UCHAR nIP_2; };
    struct { char igi2_o2[2]; UCHAR nIP_3; };
    struct { char igi2_o3[3]; char zTemp[256]; };
    char igi2_extent[259];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  u_short v1; // ax
  UCHAR s_b1; // bl
  u_short v3; // di

  if ( Network_IsShouldSendQuit() )
  {
    v1 = ntohs(ptSockAddr->sin_port);
    s_b1 = ptSockAddr->sin_addr.S_un.S_un_b.s_b1;
    igi2_frame.nIP_1 = ptSockAddr->sin_addr.S_un.S_un_b.s_b2;
    v3 = v1;
    igi2_frame.nIP_2 = ptSockAddr->sin_addr.S_un.S_un_b.s_b3;
    igi2_frame.nIP_3 = ptSockAddr->sin_addr.S_un.S_un_b.s_b4;
    Network_SendQuitMessage(ptSockAddr);
    _snprintf(igi2_frame.zTemp, 0xFFu, "Network: QUIT message sent to %u.%u.%u.%u:%d\n", s_b1, igi2_frame.nIP_1, igi2_frame.nIP_2, igi2_frame.nIP_3, v3);
    NetManager_LogMessage(igi2_frame.zTemp);
  }
}

// source: b/2/pc/pc_network.c:2798  [anchor-strings]
enum bool __cdecl Network_RemoveFromLoadQueue(struct sockaddr_in *ptSockAddr)
{
  signed int nAllocated; // ebp
  signed int v2; // edx
  void **papxElement; // ebx

  nAllocated = Network_ptLoadingHosts->nAllocated;
  v2 = 0;
  if ( nAllocated <= 0 )
  {
LABEL_5:
    NetManager_LogMessage("Network_RemoveFromLoadQueue: Socket not found in load queue\n");
    return false;
  }
  else
  {
    papxElement = Network_ptLoadingHosts->papxElement;
    while ( memcmp(ptSockAddr, *papxElement, 0x10u) )
    {
      ++v2;
      ++papxElement;
      if ( v2 >= nAllocated )
        goto LABEL_5;
    }
    QObjectVector_RemoveElement(Network_ptLoadingHosts, v2);
    NetManager_LogMessage("Network_RemoveFromLoadQueue: Socket removed from load queue\n");
    return true;
  }
}

// source: b/2/pc/pc_network.c:2837  [anchor-strings]
enum bool __cdecl Network_RemoveOneLoadingTimedOut(int nTimeOut)
{
  struct QObjectVector_s *v1; // eax
  unsigned int v2; // edi
  unsigned __int8 *v3; // esi
  int v4; // ebx
  DWORD v5; // eax
  u_short v7; // ax
  char zTemp[256]; // [esp+14h] [ebp-100h] BYREF

  v1 = Network_ptLoadingHosts;
  v2 = 0;
  if ( (int)Network_ptLoadingHosts->nAllocated <= 0 )
    return false;
  while ( 1 )
  {
    v3 = (unsigned __int8 *)v1->papxElement[v2];
    v4 = *((_DWORD *)v3 + 4);
    v5 = Timer_isPerformanceCounter ? Timer_GetPerformanceCounter() : GetTickCount();
    if ( nTimeOut + v4 < (int)(v5 - Timer_nStartTime) )
      break;
    v1 = Network_ptLoadingHosts;
    if ( (signed int)++v2 >= (signed int)Network_ptLoadingHosts->nAllocated )
      return false;
  }
  v7 = ntohs(*((_WORD *)v3 + 1));
  _snprintf(zTemp, 0xFFu, "Network: Loading host timed out: [%u.%u.%u.%u:%d]\n", v3[4], v3[5], v3[6], v3[7], v7);
  NetManager_LogMessage(zTemp);
  QObjectVector_RemoveElement(Network_ptLoadingHosts, v2);
  return true;
}

// source: b/2/pc/pc_network.c:2896  [anchor-hash]
int __cdecl Network_NumberOfLoadingHosts()
{
  if ( Network_ptLoadingHosts )
    return Network_ptLoadingHosts->nAllocated;
  else
    return 0;
}

// source: b/2/pc/pc_network.c:2916  [anchor-callee]
struct NetworkTimedSocket_s *__cdecl Network_GetFromLoadQueue(struct sockaddr_in *ptSockAddr)
{
  int v1; // ebx
  void **i; // edx
  struct NetworkTimedSocket_s *result; // eax

  v1 = 0;
  if ( (int)Network_ptLoadingHosts->nAllocated <= 0 )
    return nullptr;
  for ( i = (void **)Network_ptLoadingHosts->papxElement; ; ++i )
  {
    result = (struct NetworkTimedSocket_s *)*i;
    if ( !memcmp(ptSockAddr, *i, 0x10u) )
      break;
    if ( ++v1 >= (signed int)Network_ptLoadingHosts->nAllocated )
      return nullptr;
  }
  return result;
}

// source: b/2/pc/pc_network.c:2954  [anchor-strings]
void __cdecl Network_AddToLoadQueue(struct sockaddr_in *ptSockAddr)
{
  u_short v1; // ax
  struct NetworkTimedSocket_s *Queue; // edi
  unsigned int *p_nAllocated; // ebx
  struct QObjectVector_s *v4; // edi
  char Buffer[256]; // [esp+Ch] [ebp-100h] BYREF

  v1 = ntohs(ptSockAddr->sin_port);
  _snprintf(
    Buffer,
    0xFFu,
    "Network_AddToLoadQueue: [%u.%u.%u.%u:%d]\n",
    ptSockAddr->sin_addr.S_un.S_un_b.s_b1,
    ptSockAddr->sin_addr.S_un.S_un_b.s_b2,
    ptSockAddr->sin_addr.S_un.S_un_b.s_b3,
    ptSockAddr->sin_addr.S_un.S_un_b.s_b4,
    v1);
  NetManager_LogMessage(Buffer);
  Queue = Network_GetFromLoadQueue(ptSockAddr);
  if ( !Queue )
  {
    p_nAllocated = &Network_ptLoadingHosts->nAllocated;
    v4 = Network_ptLoadingHosts;
    if ( Network_ptLoadingHosts->nAllocated == Network_ptLoadingHosts->nSize )
      QObjectVector_Realloc(Network_ptLoadingHosts, Network_ptLoadingHosts->nReallocSize);
    Queue = (struct NetworkTimedSocket_s *)v4->papxElement[(*p_nAllocated)++];
    Queue->tSockAddr = *ptSockAddr;
  }
  if ( Timer_isPerformanceCounter )
    Queue->nStartTime = Timer_GetPerformanceCounter() - Timer_nStartTime;
  else
    Queue->nStartTime = GetTickCount() - Timer_nStartTime;
}

// source: b/2/pc/pc_network.c:3004  [anchor-strings]
void __cdecl Network_ServerHandleReceivedPacket(
        struct NetworkThreadContext_s *ptThreadContext,
        struct NetworkParseContext_s *ptParseContext,
        struct sockaddr_in *ptSockAddr)
{
  #pragma pack(push, 1)
  union
  {
    struct { ULONG v22; };
    struct { char igi2_o1[8]; int v23; };
    struct { char igi2_o2[8]; int v24; };
    struct { char igi2_o3[12]; int v25; };
    struct { char igi2_o4[12]; int v26; };
    struct { char igi2_o5[16]; int v27; };
    struct { char igi2_o6[16]; int v28; };
    struct { char igi2_o7[40]; unsigned __int8 nIP[4]; };
    struct { char igi2_o8[44]; struct sockaddr_in ptSocket; };
    struct { char igi2_o9[60]; int v31; };
    struct { char igi2_o10[64]; ULONG v32; };
    struct { char igi2_o11[68]; int v33; };
    struct { char igi2_o12[72]; int v34; };
    struct { char igi2_o13[76]; struct NetworkThreadContext_s *v35; };
    struct { char igi2_o14[80]; struct NetworkPacket_s *v36; };
    struct { char igi2_o15[84]; int v37; };
    struct { char igi2_o16[88]; char Buffer[256]; };
    struct { char igi2_o17[344]; char zString[52]; };
    char igi2_extent[396];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct NetworkPacket_s *anParsePacket; // esi
  struct NetworkIDListItem_s *IDItemFromAddr; // edi
  ULONG S_addr; // eax
  int v6; // edx
  int nSize; // ecx
  int v8; // edx
  int ePacketType; // eax
  int sin_family; // esi
  int v11; // ebx
  struct NetworkPacket_s *v12; // ebp
  int v13; // eax
  unsigned int eDestinationID; // eax
  struct NetworkIDListItem_s *v15; // eax
  ULONG v16; // edx
  struct NetworkPacket_s *v17; // edx
  struct NetworkPacket_s *v18; // eax
  struct Node_s *ptHead; // edi
  struct Node_s *i; // ebx
  _DWORD **v21; // eax

  anParsePacket = (struct NetworkPacket_s *)ptParseContext->anParsePacket;
  IDItemFromAddr = Network_GetIDItemFromAddr(ptSockAddr);
  if ( IDItemFromAddr )
    *(_DWORD *)&igi2_frame.ptSocket.sin_zero[4] = IDItemFromAddr->eID;
  else
    *(_DWORD *)&igi2_frame.ptSocket.sin_zero[4] = -1;
  S_addr = ptSockAddr->sin_addr.S_un.S_addr;
  igi2_frame.v31 = *(_DWORD *)&ptSockAddr->sin_family;
  v6 = *(_DWORD *)ptSockAddr->sin_zero;
  igi2_frame.v32 = S_addr;
  nSize = anParsePacket->nSize;
  igi2_frame.v34 = *(_DWORD *)&ptSockAddr->sin_zero[4];
  igi2_frame.v33 = v6;
  igi2_frame.v35 = ptThreadContext;
  igi2_frame.v36 = anParsePacket + 1;
  v8 = ntohs(nSize);
  ePacketType = anParsePacket->ePacketType;
  igi2_frame.v37 = v8;
  switch ( ePacketType )
  {
    case 0:
      Network_SetSocketData(ptSockAddr, igi2_frame.nIP, &igi2_frame.ptSocket.sin_family);
      sin_family = igi2_frame.ptSocket.sin_family;
      igi2_frame.v27 = igi2_frame.ptSocket.sin_family;
      igi2_frame.v25 = igi2_frame.nIP[3];
      igi2_frame.v23 = igi2_frame.nIP[2];
      igi2_frame.v22 = igi2_frame.nIP[0];
      *(_DWORD *)&igi2_frame.ptSocket.sin_family = igi2_frame.nIP[3];
      *(_DWORD *)igi2_frame.ptSocket.sin_zero = igi2_frame.nIP[2];
      *(_DWORD *)igi2_frame.nIP = igi2_frame.nIP[1];
      igi2_frame.ptSocket.sin_addr.S_un.S_addr = igi2_frame.v22;
      _snprintf(
        igi2_frame.Buffer,
        0xFFu,
        "NETWORKPACKET_TYPE_CLIENTCONNECT [%u.%u.%u.%u:%d]\n",
        igi2_frame.v22,
        *(_DWORD *)igi2_frame.nIP,
        igi2_frame.v23,
        igi2_frame.v25,
        igi2_frame.v27);
      NetManager_LogMessage(igi2_frame.Buffer);
      Network_RemoveFromLoadQueue(ptSockAddr);
      v11 = ptThreadContext->pfHandler(
              ptThreadContext->pxHandlerContext,
              NETWORKMESSAGE_SERVER_CONNECTIONREQUEST,
              (struct NetworkMessageContext_s *)&igi2_frame.ptSocket.sin_zero[4]);
      v12 = Network_AcquirePacket(1u, 12);
      v12[1].nPacketID = Timer_Read();
      LOBYTE(v12[1].nPacketHeader) = v11;
      if ( v11 )
      {
        if ( v11 == 7 )
        {
          v15 = Network_GetIDItemFromAddr(ptSockAddr);
          igi2_frame.v28 = *(_DWORD *)&igi2_frame.ptSocket.sin_family;
          v16 = igi2_frame.ptSocket.sin_addr.S_un.S_addr;
          igi2_frame.v26 = *(_DWORD *)igi2_frame.ptSocket.sin_zero;
          v12[1].eDestinationID = v15->eID;
          igi2_frame.v24 = *(_DWORD *)igi2_frame.nIP;
          LOBYTE(v12[1].nPacketHeader) = 0;
          _snprintf(
            igi2_frame.Buffer,
            0xFFu,
            "NETWORKCONNECTIONRESPONSE_ALREADY_UP [%u.%u.%u.%u:%d]\n",
            v16,
            igi2_frame.v24,
            igi2_frame.v26,
            igi2_frame.v28,
            sin_family);
          NetManager_LogMessage(igi2_frame.Buffer);
        }
        else
        {
          _snprintf(
            igi2_frame.Buffer,
            0xFFu,
            "NETWORKCONNECTIONRESPONSE FAILED [%u.%u.%u.%u:%d]\n",
            igi2_frame.ptSocket.sin_addr.S_un.S_addr,
            *(_DWORD *)igi2_frame.nIP,
            *(_DWORD *)igi2_frame.ptSocket.sin_zero,
            *(_DWORD *)&igi2_frame.ptSocket.sin_family,
            sin_family);
          NetManager_LogMessage(igi2_frame.Buffer);
          v12[1].eDestinationID = -1;
        }
      }
      else
      {
        _snprintf(
          igi2_frame.Buffer,
          0xFFu,
          "NETWORKCONNECTIONRESPONSE_SUCCESS [%u.%u.%u.%u:%d]\n",
          igi2_frame.ptSocket.sin_addr.S_un.S_addr,
          *(_DWORD *)igi2_frame.nIP,
          *(_DWORD *)igi2_frame.ptSocket.sin_zero,
          *(_DWORD *)&igi2_frame.ptSocket.sin_family,
          sin_family);
        NetManager_LogMessage(igi2_frame.Buffer);
        Network_PrintSocket(igi2_frame.zString, 50, ptSockAddr);
        v13 = Server_PopFreeNID();
        v12[1].eDestinationID = v13;
        if ( v13 == -1 )
        {
          NetManager_LogMessage("Out of NIDS, resynching pool...\n");
          Server_ResynchPool();
          v12[1].eDestinationID = Server_PopFreeNID();
        }
        eDestinationID = v12[1].eDestinationID;
        if ( eDestinationID == -1 )
        {
          NetManager_LogMessage("Cannot retrieve a NID. This should never happen. Restart the server\n");
          LOBYTE(v12[1].nPacketHeader) = 5;
        }
        else
        {
          Network_nGuaranteedPacketID[eDestinationID] = 1;
          Network_nLastReceivedGuaranteedPacketID[eDestinationID] = 0;
          Network_AddIDItem(v12[1].eDestinationID, ptSockAddr);
          _snprintf(
            igi2_frame.Buffer,
            0xFFu,
            "Popped new networkID for joining client: [%d][%s]\n",
            v12[1].eDestinationID,
            igi2_frame.zString);
          NetManager_LogMessage(igi2_frame.Buffer);
        }
      }
      Network_SendSocketMessage((struct sockaddr *)ptSockAddr, 16, v12, true, NETWORK_SENDTYPE_EXTERNAL);
      break;
    case 2:
      if ( !IDItemFromAddr )
        goto LABEL_26;
      NetManager_RegisterInput(*(int *)&igi2_frame.ptSocket.sin_zero[4]);
      ptThreadContext->pfHandler(
        ptThreadContext->pxHandlerContext,
        NETWORKMESSAGE_RECEIVEDDATA,
        (struct NetworkMessageContext_s *)&igi2_frame.ptSocket.sin_zero[4]);
      break;
    case 3:
      if ( IDItemFromAddr )
      {
        NetManager_RegisterInput(*(int *)&igi2_frame.ptSocket.sin_zero[4]);
        if ( Network_ProcessGuaranteedPackage(
               ptThreadContext,
               anParsePacket,
               *(unsigned int *)&igi2_frame.ptSocket.sin_zero[4],
               ptSockAddr) )
        {
          ptThreadContext->pfHandler(
            ptThreadContext->pxHandlerContext,
            NETWORKMESSAGE_RECEIVEDGUARANTEEDDATA,
            (struct NetworkMessageContext_s *)&igi2_frame.ptSocket.sin_zero[4]);
        }
        v18 = Network_AcquirePacket(4u, 20);
        v18->nPacketID = anParsePacket->nPacketID;
        v18->eDestinationID = anParsePacket->eDestinationID;
        Network_SendSocketMessage((struct sockaddr *)ptSockAddr, 16, v18, true, NETWORK_SENDTYPE_ACK);
      }
      else
      {
LABEL_26:
        Network_SometimesSendQuit(ptSockAddr);
      }
      break;
    case 4:
      if ( IDItemFromAddr )
        NetManager_RegisterInput(*(int *)&igi2_frame.ptSocket.sin_zero[4]);
      ptHead = Network_atQueues[0].tList.ptHead;
      for ( i = Network_atQueues[0].tList.ptHead->ptNext; i; i = i->ptNext )
      {
        if ( ptHead[1].ptPrev == (struct Node_s *)anParsePacket->nPacketID
          && ptHead[1].ptNext == (struct Node_s *)anParsePacket->eDestinationID )
        {
          Mem_DeAllocFn(ptHead[3].ptNext);
          ptHead[3].ptNext = nullptr;
          v21 = Node_Remove(ptHead);
          Mem_DeAllocFn(v21);
        }
        ptHead = i;
      }
      break;
    case 5:
      if ( ptThreadContext->pfHandler(
             ptThreadContext->pxHandlerContext,
             NETWORKMESSAGE_SERVER_INFOREQUEST,
             (struct NetworkMessageContext_s *)&igi2_frame.ptSocket.sin_zero[4]) )
      {
        Network_SetSocketData(ptSockAddr, igi2_frame.nIP, &igi2_frame.ptSocket.sin_family);
        NetManager_UpdateServerSettings();
        if ( NetManager_IsShouldSendServerInfo() )
        {
          v17 = Network_AcquirePacket(6u, ptThreadContext->nApplicationDataSize + 2);
          LOWORD(v17[1].nPacketHeader) = ptThreadContext->nApplicationDataSize;
          qmemcpy(
            (char *)&v17[1].nPacketHeader + 2,
            ptThreadContext->pxApplicationData,
            ptThreadContext->nApplicationDataSize);
          Network_SendSocketMessage((struct sockaddr *)ptSockAddr, 16, v17, true, NETWORK_SENDTYPE_EXTERNAL);
          _snprintf(
            igi2_frame.Buffer,
            0xFFu,
            "Server info sent to %u.%u.%u.%u:%d\n",
            igi2_frame.nIP[0],
            igi2_frame.nIP[1],
            igi2_frame.nIP[2],
            igi2_frame.nIP[3],
            igi2_frame.ptSocket.sin_family);
          NetManager_LogMessage(igi2_frame.Buffer);
          if ( NetManager_IsServerFullIncludingLoading() )
          {
            NetManager_LogMessage("Network: Server full incl. loading hosts, not adding host to load queue\n");
            Network_RemoveFromLoadQueue(ptSockAddr);
          }
          else
          {
            Network_AddToLoadQueue(ptSockAddr);
          }
        }
        else
        {
          _snprintf(
            igi2_frame.Buffer,
            0xFFu,
            "Server info requested, no answer sent to %u.%u.%u.%u:%d\n",
            igi2_frame.nIP[0],
            igi2_frame.nIP[1],
            igi2_frame.nIP[2],
            igi2_frame.nIP[3],
            igi2_frame.ptSocket.sin_family);
          NetManager_LogMessage(igi2_frame.Buffer);
        }
      }
      break;
    case 7:
      NetManager_LogMessage("Server received QUIT message... doing nothing\n");
      break;
    case 8:
      NetManager_LogMessage("Received CONSOLE message\n");
      break;
    default:
      NetManager_LogMessage("Network_ServerHandleReceivedPacket: Unknown message type\n");
      break;
  }
}

// source: b/2/pc/pc_network.c:3346  [size]
void __cdecl Network_SetExternalReceiveHandler(
        char zChar1,
        char zChar2,
        void (__cdecl *pfNetworkExternalReceiveHandler)(char *, int, struct sockaddr *))
{
  Network_pfExternalReceiveHandler = pfNetworkExternalReceiveHandler;
  Network_ExternalReceiveMarkerI = zChar1;
  Network_ExternalReceiveMarkerII = zChar2;
}

// source: b/2/pc/pc_network.c:3367  [anchor-hash]
void __cdecl Network_SetConsoleReceiveHandler(
        char zChar1,
        void (__cdecl *pfConsoleReceiveHandler)(char *, int, struct sockaddr *))
{
  Network_pfConsoleReceiveHandler = pfConsoleReceiveHandler;
  Network_ConsoleReceiveMarker = zChar1;
}

// source: b/2/pc/pc_network.c:3385  [anchor-strings]
void *__cdecl Network_StartServer(
        struct NetworkServerContext_s *ptServerContext,
        int (__cdecl *pfHandler__)(void *, enum NetworkMessage_e, struct NetworkMessageContext_s *),
        void *pxHandlerContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { void *v36; };
    struct { char igi2_o1[4]; u_long argp; };
    struct { char igi2_o2[8]; struct sockaddr name; };
    struct { char igi2_o3[24]; char Buffer[256]; };
    char igi2_extent[280];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  _DWORD *v3; // esi
  struct QObjectVector_s *v4; // eax
  struct Queue_s *v5; // eax
  struct Node_s **p_ptMiddle; // ecx
  SOCKET v7; // eax
  int Error; // eax
  int v9; // edi
  char *ErrorDesc; // eax
  int v11; // eax
  int v12; // ecx
  char *v13; // eax
  int v14; // eax
  int v15; // ecx
  char *v16; // eax
  u_short nPort; // dx
  int v18; // eax
  int v19; // ecx
  char *v20; // eax
  int v21; // esi
  struct QObjectVector_s *v23; // esi
  struct MemPoolSegment_s *v24; // edi
  int v25; // eax
  unsigned int nBlocks; // ebp
  struct MemPoolFreeItem_s *ptHead; // ecx
  struct MemPoolFreeItem_s *pxData; // eax
  char *v29; // ebx
  unsigned int nBlockSize; // eax
  char *v31; // ecx
  unsigned int v32; // eax
  struct MemPoolFreeItem_s *v33; // eax
  unsigned int v34; // edx
  struct MemPoolFreeItem_s *v35; // eax

  igi2_frame.argp = 1;
  v3 = Mem_AllocFn(16460, 4);
  memset(v3, 0, 0x404Cu);
  v3[7] = pfHandler__;
  v3[8] = pxHandlerContext;
  v3[9] = ptServerContext->pxApplicationData;
  v3[10] = ptServerContext->nApplicationDataSize;
  v4 = Network_ptLoadingHosts;
  v3[15] = 0;
  v3[16] = 0;
  v3[14] = 0;
  igi2_frame.v36 = v3;
  Network_tIDList.ptHead = (struct Node_s *)&Network_tIDList.ptMiddle;
  Network_tIDList.ptTail = (struct Node_s *)&Network_tIDList;
  Network_tIDList.ptMiddle = nullptr;
  if ( v4 )
  {
    NetManager_LogMessage("Network_StartServer: Cleared non-empty loading queue\n");
    QObjectVector_Delete(Network_ptLoadingHosts);
  }
  v5 = Network_atQueues;
  do
  {
    p_ptMiddle = &v5->tList.ptMiddle;
    v5->tList.ptHead = (struct Node_s *)&v5->tList.ptMiddle;
    v5->tList.ptTail = (struct Node_s *)v5;
    ++v5;
    *p_ptMiddle = nullptr;
  }
  while ( (int)v5 < 7587040 );
  memset(Network_nLastReceivedGuaranteedPacketID, 0, sizeof(Network_nLastReceivedGuaranteedPacketID));
  Network_tWaitingGuaranteedPackets.ptHead = (struct Node_s *)&Network_tWaitingGuaranteedPackets.ptMiddle;
  Network_tWaitingGuaranteedPackets.ptTail = (struct Node_s *)&Network_tWaitingGuaranteedPackets;
  Network_tWaitingGuaranteedPackets.ptMiddle = nullptr;
  memset32(Network_nGuaranteedPacketID, 1, 0x23u);
  v7 = socket(2, 2, 17);
  Network_UDPSocket = v7;
  if ( v7 == -1 )
  {
    Error = WSAGetLastError();
    v9 = Error;
    if ( Error != 10054 )
    {
      ErrorDesc = Network_GetErrorDesc(Error);
      _snprintf(igi2_frame.Buffer, 0xFFu, "\n%s:error code=%d, desc=%s\n", "Network_StartServer:socket()", v9, ErrorDesc);
      NetManager_LogMessage(igi2_frame.Buffer);
    }
    WSASetLastError(0);
    if ( v9 != 10093 )
    {
LABEL_23:
      if ( Network_UDPSocket != -1 )
      {
        closesocket(Network_UDPSocket);
        NetManager_LogMessage("Network_CloseUDPSocket: Socket closed\n");
LABEL_26:
        v21 = *(_DWORD *)((unsigned int)(v3 - 1) & 0xFFFFFFFC);
        --Mem_nCurrentAllocations;
        Node_Remove((_DWORD **)v21);
        memset(*(void **)(v21 + 8), 0xCDu, *(_DWORD *)(v21 + 16));
        free((void *)v21);
        return nullptr;
      }
LABEL_25:
      NetManager_LogMessage("Network_CloseUDPSocket: Socket was invalid\n");
      goto LABEL_26;
    }
    NetManager_LogMessage("Network_StartServer: Restarting network, trying again...\n");
    if ( WSACleanup() == -1 )
    {
      v11 = WSAGetLastError();
      v12 = v11;
      if ( v11 != 10054 )
      {
        v13 = Network_GetErrorDesc(v11);
        _snprintf(igi2_frame.Buffer, 0xFFu, "\n%s:error code=%d, desc=%s\n", "Network_CloseSockLib():", v12, v13);
        NetManager_LogMessage(igi2_frame.Buffer);
      }
      WSASetLastError(0);
    }
    else
    {
      NetManager_LogMessage("Winsock closed and cleaned up\n");
    }
    Sleep(0x7D0u);
    Network_StartSockLib();
    Network_UDPSocket = socket(2, 2, 17);
    if ( Network_UDPSocket == -1 )
      goto LABEL_25;
    NetManager_LogMessage("Network_StartServer: Socket created after restarting winsock\n");
    v7 = Network_UDPSocket;
  }
  if ( ioctlsocket(v7, -2147195266, &igi2_frame.argp) == -1 )
  {
    v14 = WSAGetLastError();
    v15 = v14;
    if ( v14 != 10054 )
    {
      v16 = Network_GetErrorDesc(v14);
      _snprintf(igi2_frame.Buffer, 0xFFu, "\n%s:error code=%d, desc=%s\n", "Network_StartServer:ictlsocket(..FIONBIO..)", v15, v16);
      NetManager_LogMessage(igi2_frame.Buffer);
    }
LABEL_22:
    WSASetLastError(0);
    goto LABEL_23;
  }
  nPort = ptServerContext->nPort;
  igi2_frame.name.sa_family = 2;
  *(_WORD *)igi2_frame.name.sa_data = htons(nPort);
  *(_DWORD *)&igi2_frame.name.sa_data[2] = *(_DWORD *)ptServerContext->ptAdapter->pnAddress;
  if ( bind(Network_UDPSocket, &igi2_frame.name, 16) == -1 )
  {
    v18 = WSAGetLastError();
    v19 = v18;
    if ( v18 != 10054 )
    {
      v20 = Network_GetErrorDesc(v18);
      _snprintf(igi2_frame.Buffer, 0xFFu, "\n%s:error code=%d, desc=%s\n", "Network_StartServer:bind()", v19, v20);
      NetManager_LogMessage(igi2_frame.Buffer);
    }
    goto LABEL_22;
  }
  Network_StoreLocalAddress();
  v3[4114] = Mem_AllocFn(0x4000, 4);
  Network_AddIDItem(0, (struct sockaddr_in *)&igi2_frame.name);
  v23 = (struct QObjectVector_s *)Mem_AllocFn(52, 4);
  v23->nElementSize = 24;
  v23->tMemPool.nBlockSize = 24;
  v23->isStrictOrder = false;
  v23->nSize = 0;
  v23->nAllocated = 0;
  v23->nReallocSize = 3;
  v23->papxElement = nullptr;
  v23->tMemPool.nBlocks = 0;
  v23->tMemPool.nAllocatedBlocks = 0;
  v23->tMemPool.nAlignment = 4;
  v23->tMemPool.nReAllocBlocks = 3;
  v23->tMemPool.tMemPoolFreeList.ptHead = nullptr;
  v23->tMemPool.tMemPoolSegmentList.ptHead = nullptr;
  v24 = (struct MemPoolSegment_s *)Mem_AllocFn(12, 4);
  v25 = 5 * v23->tMemPool.nBlockSize;
  v24->nByteSize = v25;
  v24->pxData = Mem_AllocFn(v25, v23->tMemPool.nAlignment);
  v24->ptNext = v23->tMemPool.tMemPoolSegmentList.ptHead;
  nBlocks = v23->tMemPool.nBlocks;
  ptHead = v23->tMemPool.tMemPoolFreeList.ptHead;
  v23->tMemPool.tMemPoolSegmentList.ptHead = v24;
  v23->tMemPool.nBlocks = nBlocks + 5;
  pxData = (struct MemPoolFreeItem_s *)v24->pxData;
  pxData->ptNext = ptHead;
  v23->tMemPool.tMemPoolFreeList.ptHead = pxData;
  v29 = (char *)v24->pxData;
  nBlockSize = v23->tMemPool.nBlockSize;
  *(_DWORD *)&v29[nBlockSize] = v23->tMemPool.tMemPoolFreeList.ptHead;
  v23->tMemPool.tMemPoolFreeList.ptHead = (struct MemPoolFreeItem_s *)&v29[nBlockSize];
  v31 = (char *)v24->pxData;
  v32 = v23->tMemPool.nBlockSize;
  *(_DWORD *)&v31[2 * v32] = v23->tMemPool.tMemPoolFreeList.ptHead;
  v23->tMemPool.tMemPoolFreeList.ptHead = (struct MemPoolFreeItem_s *)&v31[2 * v32];
  v33 = (struct MemPoolFreeItem_s *)((char *)v24->pxData + 3 * v23->tMemPool.nBlockSize);
  v33->ptNext = v23->tMemPool.tMemPoolFreeList.ptHead;
  v34 = v23->tMemPool.nBlockSize;
  v23->tMemPool.tMemPoolFreeList.ptHead = v33;
  v35 = (struct MemPoolFreeItem_s *)((char *)v24->pxData + 4 * v34);
  v35->ptNext = v23->tMemPool.tMemPoolFreeList.ptHead;
  v23->tMemPool.tMemPoolFreeList.ptHead = v35;
  QObjectVector_Realloc(v23, 5u);
  Network_ptLoadingHosts = v23;
  return igi2_frame.v36;
}

// source: b/2/pc/pc_network.c:3536  [size]
unsigned int __cdecl Network_GetSocket(void *pxContext)
{
  return Network_UDPSocket;
}

// source: b/2/pc/pc_network.c:3565  [anchor-strings]
int __cdecl Network_Receive(unsigned int socket_, char *buf, struct sockaddr_in *ptSockAddr)
{
  #pragma pack(push, 1)
  union
  {
    struct { int fromlen; };
    struct { char igi2_o1[4]; struct timeval timeout; };
    struct { char igi2_o2[12]; char Buffer[256]; };
    struct { char igi2_o3[268]; fd_set readfds; };
    char igi2_extent[528];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v4; // eax
  _DWORD *v5; // esi
  int v6; // edx
  bool v7; // zf
  DWORD TickCount; // eax
  int Error; // eax
  int v10; // ecx
  char *ErrorDesc; // eax
  DWORD PerformanceCounter; // eax
  DWORD v14; // esi
  int v15; // edi
  DWORD v16; // eax
  DWORD v17; // eax
  _DWORD *v18; // esi
  int v19; // edx
  DWORD v20; // eax
  int v21; // eax
  int v22; // ecx
  char *v23; // eax
  _DWORD *v24; // esi
  int v25; // eax
  DWORD v26; // eax

  igi2_frame.timeout.tv_sec = 0;
  igi2_frame.timeout.tv_usec = 0;
  igi2_frame.readfds.fd_array[0] = socket_;
  igi2_frame.readfds.fd_count = 1;
  v4 = select(64, &igi2_frame.readfds, nullptr, nullptr, &igi2_frame.timeout);
  if ( v4 == -1 )
  {
    v5 = (_DWORD *)(16 * Network_nReceiveStatIndex + 7583752);
    v6 = (Network_nReceiveStatIndex + 1) % 200;
    v7 = Timer_isPerformanceCounter == 0;
    v5[2] = 1;
    v5[1] = 0;
    Network_nReceiveStatIndex = v6;
    if ( v7 )
      TickCount = GetTickCount();
    else
      TickCount = Timer_GetPerformanceCounter();
    *v5 = TickCount - Timer_nStartTime;
    v5[3] = WSAGetLastError();
    Error = WSAGetLastError();
    v10 = Error;
    if ( Error != 10054 )
    {
      ErrorDesc = Network_GetErrorDesc(Error);
      _snprintf(igi2_frame.Buffer, 0xFFu, "\n%s:error code=%d, desc=%s\n", "Network_Receive: select():", v10, ErrorDesc);
      NetManager_LogMessage(igi2_frame.Buffer);
    }
    WSASetLastError(0);
    return -1;
  }
  else if ( v4 )
  {
    igi2_frame.fromlen = 16;
    if ( Timer_isPerformanceCounter )
      PerformanceCounter = Timer_GetPerformanceCounter();
    else
      PerformanceCounter = GetTickCount();
    v14 = PerformanceCounter - Timer_nStartTime;
    v15 = recvfrom(socket_, buf, 0x3FFF, 0, (struct sockaddr *)ptSockAddr, &igi2_frame.fromlen);
    if ( Timer_isPerformanceCounter )
      v16 = Timer_GetPerformanceCounter();
    else
      v16 = GetTickCount();
    if ( (int)(v16 - Timer_nStartTime - v14) > 10 )
    {
      if ( Timer_isPerformanceCounter )
        v17 = Timer_GetPerformanceCounter();
      else
        v17 = GetTickCount();
      _snprintf(igi2_frame.Buffer, 0xFFu, "Network_receive: Slow recvfrom(): %dms\n", v17 - Timer_nStartTime - v14);
      NetManager_LogMessage(igi2_frame.Buffer);
    }
    if ( v15 == -1 )
    {
      if ( WSAGetLastError() == 10054 )
      {
        WSASetLastError(0);
        return 0;
      }
      else
      {
        v18 = (_DWORD *)(16 * Network_nReceiveStatIndex + 7583752);
        v19 = (Network_nReceiveStatIndex + 1) % 200;
        v7 = Timer_isPerformanceCounter == 0;
        v18[2] = 4;
        v18[1] = 0;
        Network_nReceiveStatIndex = v19;
        if ( v7 )
          v20 = GetTickCount();
        else
          v20 = Timer_GetPerformanceCounter();
        *v18 = v20 - Timer_nStartTime;
        v18[3] = WSAGetLastError();
        v21 = WSAGetLastError();
        v22 = v21;
        if ( v21 != 10054 )
        {
          v23 = Network_GetErrorDesc(v21);
          _snprintf(igi2_frame.Buffer, 0xFFu, "\n%s:error code=%d, desc=%s\n", "Network_receive:recvfrom", v22, v23);
          NetManager_LogMessage(igi2_frame.Buffer);
        }
        WSASetLastError(0);
        return -1;
      }
    }
    else
    {
      v24 = (_DWORD *)(16 * Network_nReceiveStatIndex + 7583752);
      v25 = Timer_isPerformanceCounter;
      Network_nReceiveStatIndex = (Network_nReceiveStatIndex + 1) % 200;
      if ( v15 <= 0 )
      {
        v24[2] = 5;
        v24[1] = 0;
        if ( v25 )
          v26 = Timer_GetPerformanceCounter();
        else
          v26 = GetTickCount();
        *v24 = v26 - Timer_nStartTime;
        v24[3] = 0;
        NetManager_LogMessage("Network_Receive(): Got 0 bytes but no error\n");
        return -1;
      }
      else
      {
        v24[2] = 0;
        v24[1] = v15 + 28;
        if ( v25 )
          *v24 = Timer_GetPerformanceCounter() - Timer_nStartTime;
        else
          *v24 = GetTickCount() - Timer_nStartTime;
        v24[3] = 0;
        return v15;
      }
    }
  }
  else
  {
    return -2;
  }
}

// source: b/2/pc/pc_network.c:3704  [anchor-callee]
int __cdecl Network_RunServer(void *pxContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct Node_s *ptTemp; };
    struct { char igi2_o1[8]; struct sockaddr_in tSockAddr; };
    struct { char igi2_o2[24]; char zIP[52]; };
    struct { char igi2_o3[76]; char zTemp[256]; };
    char igi2_extent[332];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct NetworkThreadContext_s *v1; // edi
  int v2; // ebp
  int v3; // esi
  bool i; // zf
  void (__cdecl *v5)(char *, int, struct sockaddr *); // edx
  char *pnReceiveBuffer; // eax
  void (__cdecl *v7)(char *, int, struct sockaddr *); // ecx
  char *v8; // eax
  struct Node_s *ptHead; // ebx
  struct Node_s *v10; // edx
  struct Node_s *ptNext; // eax
  u_short v12; // ax
  int v13; // esi
  int v15; // esi

  v1 = (struct NetworkThreadContext_s *)pxContext;
  v2 = 0;
  Network_HandleSendQueues();
  v3 = Network_Receive(Network_UDPSocket, *((char **)pxContext + 4114), &igi2_frame.tSockAddr);
  for ( i = v3 == 0; v3 >= 0; i = v3 == 0 )
  {
    if ( !i )
    {
      v5 = Network_pfExternalReceiveHandler;
      ++v2;
      if ( Network_pfExternalReceiveHandler )
      {
        pnReceiveBuffer = v1->pnReceiveBuffer;
        if ( *pnReceiveBuffer == Network_ExternalReceiveMarkerI || *pnReceiveBuffer == Network_ExternalReceiveMarkerII )
        {
          pnReceiveBuffer[v3] = 0;
          v5(v1->pnReceiveBuffer, v3, (struct sockaddr *)&igi2_frame.tSockAddr);
        }
      }
      v7 = Network_pfConsoleReceiveHandler;
      if ( Network_pfConsoleReceiveHandler )
      {
        v8 = v1->pnReceiveBuffer;
        if ( *v8 == Network_ConsoleReceiveMarker )
        {
          v8[v3] = 0;
          v7(v1->pnReceiveBuffer, v3, (struct sockaddr *)&igi2_frame.tSockAddr);
        }
      }
      v1->tParseContext.pnReceiveBuffer = (unsigned __int8 *)v1->pnReceiveBuffer;
      v1->tParseContext.nReceiveBufferSize = v3;
      v1->tParseContext.nReceiveBufferOffset = 0;
      while ( Network_ParsePacket(&v1->tParseContext) )
        Network_ServerHandleReceivedPacket(v1, &v1->tParseContext, &igi2_frame.tSockAddr);
      ptHead = Network_tWaitingGuaranteedPackets.ptHead;
      if ( Network_tWaitingGuaranteedPackets.ptHead != (struct Node_s *)&Network_tWaitingGuaranteedPackets.ptMiddle )
      {
        igi2_frame.ptTemp = Network_tWaitingGuaranteedPackets.ptHead->ptNext;
        if ( Network_tWaitingGuaranteedPackets.ptHead->ptNext )
        {
          do
          {
            v10 = Network_tIDList.ptHead;
            ptNext = Network_tIDList.ptHead->ptNext;
            if ( !Network_tIDList.ptHead->ptNext )
              goto LABEL_17;
            while ( memcmp(&v10[2], &ptHead[1], 8u) )
            {
              v10 = ptNext;
              ptNext = ptNext->ptNext;
              if ( !ptNext )
                goto LABEL_17;
            }
            if ( v10 )
            {
              if ( ptHead[12].ptPrev == (struct Node_s *)(Network_nLastReceivedGuaranteedPacketID[(int)v10[1].ptNext] + 1) )
              {
                Network_ServerHandleReceivedPacket(
                  (struct NetworkThreadContext_s *)&ptHead[3],
                  (struct NetworkParseContext_s *)&ptHead[8].ptPrev,
                  (struct sockaddr_in *)&ptHead[1]);
                Node_Remove(ptHead);
                if ( ptHead )
                {
                  v15 = *(_DWORD *)((unsigned int)&ptHead[-1].ptPrev & 0xFFFFFFFC);
                  --Mem_nCurrentAllocations;
                  Node_Remove((_DWORD **)v15);
                  memset(*(void **)(v15 + 8), 0xCDu, *(_DWORD *)(v15 + 16));
                  free((void *)v15);
                }
              }
            }
            else
            {
LABEL_17:
              v12 = ntohs(HIWORD(ptHead[1].ptNext));
              _snprintf(
                igi2_frame.zIP,
                0x16u,
                "%d.%d.%d.%d:%d",
                LOBYTE(ptHead[1].ptPrev),
                BYTE1(ptHead[1].ptPrev),
                BYTE2(ptHead[1].ptPrev),
                HIBYTE(ptHead[1].ptPrev),
                v12);
              Node_Remove(ptHead);
              if ( ptHead )
              {
                v13 = *(_DWORD *)((unsigned int)&ptHead[-1].ptPrev & 0xFFFFFFFC);
                --Mem_nCurrentAllocations;
                Node_Remove((_DWORD **)v13);
                memset(*(void **)(v13 + 8), 0xCDu, *(_DWORD *)(v13 + 16));
                free((void *)v13);
              }
              _snprintf(igi2_frame.zTemp, 0xFFu, "Removed inbound guaranteed message from unknown source[%s]\n", igi2_frame.zIP);
              NetManager_LogMessage(igi2_frame.zTemp);
            }
            ptHead = igi2_frame.ptTemp;
            igi2_frame.ptTemp = igi2_frame.ptTemp->ptNext;
          }
          while ( igi2_frame.ptTemp );
          v1 = (struct NetworkThreadContext_s *)pxContext;
        }
      }
    }
    v3 = Network_Receive(Network_UDPSocket, v1->pnReceiveBuffer, &igi2_frame.tSockAddr);
  }
  return v2;
}

// source: b/2/pc/pc_network.c:3823  [anchor-strings]
void *__cdecl Network_StartClient(
        struct NetworkClientContext_s *ptClientContext,
        int (__cdecl *pfHandler__)(void *, enum NetworkMessage_e, struct NetworkMessageContext_s *),
        void *pxHandlerContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { char *ErrorDesc; };
    struct { char *v13; };
    struct { char igi2_o2[16]; unsigned int BlockStat; };
    struct { char igi2_o3[20]; char Buffer[256]; };
    char igi2_extent[276];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  _DWORD *v3; // esi
  struct Queue_s *v4; // eax
  struct Node_s **p_ptMiddle; // ecx
  int Error; // eax
  int v7; // ecx
  int v8; // eax
  int v9; // ecx
  int v10; // esi

  igi2_frame.BlockStat = 1;
  v3 = Mem_AllocFn(16460, 4);
  memset(v3, 0, 0x404Cu);
  v3[7] = pfHandler__;
  *v3 = 1;
  v3[8] = pxHandlerContext;
  v3[9] = 0;
  v3[10] = 0;
  v3[15] = 0;
  v3[16] = 0;
  v3[14] = 0;
  *(struct sockaddr_in *)(v3 + 3) = ptClientContext->tSockAddr;
  Network_nLastConnectionResponse = 8;
  Network_tIDList.ptHead = (struct Node_s *)&Network_tIDList.ptMiddle;
  Network_tIDList.ptTail = (struct Node_s *)&Network_tIDList;
  Network_tIDList.ptMiddle = nullptr;
  v4 = Network_atQueues;
  do
  {
    p_ptMiddle = &v4->tList.ptMiddle;
    v4->tList.ptHead = (struct Node_s *)&v4->tList.ptMiddle;
    v4->tList.ptTail = (struct Node_s *)v4;
    ++v4;
    *p_ptMiddle = nullptr;
  }
  while ( (int)v4 < 7587040 );
  memset(Network_nLastReceivedGuaranteedPacketID, 0, sizeof(Network_nLastReceivedGuaranteedPacketID));
  memset32(Network_nGuaranteedPacketID, 1, 0x23u);
  Network_tWaitingGuaranteedPackets.ptHead = (struct Node_s *)&Network_tWaitingGuaranteedPackets.ptMiddle;
  Network_tWaitingGuaranteedPackets.ptTail = (struct Node_s *)&Network_tWaitingGuaranteedPackets;
  Network_tWaitingGuaranteedPackets.ptMiddle = nullptr;
  if ( Network_UDPSocket == -1 )
  {
    Error = WSAGetLastError();
    v7 = Error;
    if ( Error != 10054 )
    {
      igi2_frame.ErrorDesc = Network_GetErrorDesc(Error);
      _snprintf(igi2_frame.Buffer, 0xFFu, "\n%s:error code=%d, desc=%s\n", "Network_StartClient:getglobalsocket", v7, igi2_frame.ErrorDesc);
LABEL_9:
      NetManager_LogMessage(igi2_frame.Buffer);
    }
  }
  else
  {
    if ( ioctlsocket(Network_UDPSocket, -2147195266, &igi2_frame.BlockStat) != -1 )
    {
      v3[4114] = Mem_AllocFn(0x4000, 4);
      return v3;
    }
    v8 = WSAGetLastError();
    v9 = v8;
    if ( v8 != 10054 )
    {
      igi2_frame.v13 = Network_GetErrorDesc(v8);
      _snprintf(igi2_frame.Buffer, 0xFFu, "\n%s:error code=%d, desc=%s\n", "Network_StartClient:ictlsocket(..FIONBIO..)", v9, igi2_frame.v13);
      goto LABEL_9;
    }
  }
  WSASetLastError(0);
  if ( Network_UDPSocket == -1 )
  {
    NetManager_LogMessage("Network_CloseUDPSocket: Socket was invalid\n");
  }
  else
  {
    closesocket(Network_UDPSocket);
    NetManager_LogMessage("Network_CloseUDPSocket: Socket closed\n");
  }
  v10 = *(_DWORD *)((unsigned int)(v3 - 1) & 0xFFFFFFFC);
  --Mem_nCurrentAllocations;
  Node_Remove((_DWORD **)v10);
  memset(*(void **)(v10 + 8), 0xCDu, *(_DWORD *)(v10 + 16));
  free((void *)v10);
  return nullptr;
}

// source: b/2/pc/pc_network.c:3922  [anchor-strings]
void __cdecl Network_StartSockLib()
{
  #pragma pack(push, 1)
  union
  {
    struct { char zTemp[256]; };
    struct { char igi2_o1[256]; struct WSAData data; };
    char igi2_extent[656];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int Error; // eax

  if ( WSAStartup(0x101u, &igi2_frame.data) )
  {
    Error = WSAGetLastError();
    Network_DebugError("Network_StartSockLib():", Error);
  }
  else
  {
    _snprintf(igi2_frame.zTemp, 0xFFu, "Winsock %d %d started\n", igi2_frame.data.wHighVersion, igi2_frame.data.wVersion);
    NetManager_LogMessage(igi2_frame.zTemp);
    _snprintf(igi2_frame.zTemp, 0xFFu, "Winsock description: '%s'\n", igi2_frame.data.szDescription);
    NetManager_LogMessage(igi2_frame.zTemp);
    _snprintf(igi2_frame.zTemp, 0xFFu, "Winsock system status: '%s'\n", igi2_frame.data.szSystemStatus);
    NetManager_LogMessage(igi2_frame.zTemp);
  }
}

// source: b/2/pc/pc_network.c:3958  [anchor-hash]
void __cdecl Network_CloseSockLib()
{
  int Error; // eax

  if ( WSACleanup() == -1 )
  {
    Error = WSAGetLastError();
    Network_DebugError("Network_CloseSockLib():", Error);
  }
  else
  {
    NetManager_LogMessage("Winsock closed and cleaned up\n");
  }
}

// source: b/2/pc/pc_network.c:3978  [anchor-callee]
void __cdecl Network_ClientConnectedReceive(struct NetworkThreadContext_s *ptContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct Node_s *ptTemp; };
    struct { char igi2_o1[4]; struct sockaddr_in tSockAddr; };
    char igi2_extent[20];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct NetworkThreadContext_s *v1; // esi
  int v2; // eax
  bool v3; // zf
  struct Node_s *ptHead; // ebx
  struct Node_s *v5; // eax
  struct Node_s *ptNext; // edx
  int v7; // esi

  v1 = ptContext;
  v2 = Network_Receive(Network_UDPSocket, ptContext->pnReceiveBuffer, &igi2_frame.tSockAddr);
  v3 = v2 == 0;
  if ( v2 >= 0 )
  {
    while ( 1 )
    {
      if ( !v3 )
      {
        v1->tParseContext.pnReceiveBuffer = (unsigned __int8 *)v1->pnReceiveBuffer;
        v1->tParseContext.nReceiveBufferSize = v2;
        v1->tParseContext.nReceiveBufferOffset = 0;
        while ( Network_ParsePacket(&v1->tParseContext) )
          Network_ClientHandleReceivedPacket(v1, &v1->tParseContext, &igi2_frame.tSockAddr);
        ptHead = Network_tWaitingGuaranteedPackets.ptHead;
        if ( Network_tWaitingGuaranteedPackets.ptHead != (struct Node_s *)&Network_tWaitingGuaranteedPackets.ptMiddle )
        {
          igi2_frame.ptTemp = Network_tWaitingGuaranteedPackets.ptHead->ptNext;
          if ( Network_tWaitingGuaranteedPackets.ptHead->ptNext )
            break;
        }
      }
LABEL_15:
      v2 = Network_Receive(Network_UDPSocket, v1->pnReceiveBuffer, &igi2_frame.tSockAddr);
      v3 = v2 == 0;
      if ( v2 < 0 )
        return;
    }
    while ( 1 )
    {
      v5 = Network_tIDList.ptHead;
      ptNext = Network_tIDList.ptHead->ptNext;
      if ( !Network_tIDList.ptHead->ptNext )
        break;
      while ( memcmp(&v5[2], &ptHead[1], 8u) )
      {
        v5 = ptNext;
        ptNext = ptNext->ptNext;
        if ( !ptNext )
          goto LABEL_10;
      }
      if ( !v5 )
        break;
      if ( ptHead[12].ptPrev == (struct Node_s *)(Network_nLastReceivedGuaranteedPacketID[(int)v5[1].ptNext] + 1) )
      {
        Network_ClientHandleReceivedPacket(
          (struct NetworkThreadContext_s *)&ptHead[3],
          (struct NetworkParseContext_s *)&ptHead[8].ptPrev,
          (struct sockaddr_in *)&ptHead[1]);
LABEL_11:
        Node_Remove(ptHead);
        if ( ptHead )
        {
          v7 = *(_DWORD *)((unsigned int)&ptHead[-1].ptPrev & 0xFFFFFFFC);
          --Mem_nCurrentAllocations;
          Node_Remove((_DWORD **)v7);
          memset(*(void **)(v7 + 8), 0xCDu, *(_DWORD *)(v7 + 16));
          free((void *)v7);
        }
      }
      ptHead = igi2_frame.ptTemp;
      igi2_frame.ptTemp = igi2_frame.ptTemp->ptNext;
      if ( !igi2_frame.ptTemp )
      {
        v1 = ptContext;
        goto LABEL_15;
      }
    }
LABEL_10:
    NetManager_LogMessage("Removing inbound message from unknown source\n");
    goto LABEL_11;
  }
}

// source: b/2/pc/pc_network.c:4072  [anchor-callee]
int __cdecl Network_NumberOfWaitingFromHost(int eNetworkID)
{
  struct Node_s *ptHead; // ecx
  struct Node_s *ptNext; // eax
  struct Node_s *v3; // edx
  struct Node_s *v4; // ebx
  struct Node_s *v5; // ebp
  struct Node_s *ptTemp; // [esp+0h] [ebp-Ch]
  int nCounter; // [esp+4h] [ebp-8h]

  ptHead = Network_tWaitingGuaranteedPackets.ptHead;
  nCounter = 0;
  if ( Network_tWaitingGuaranteedPackets.ptHead == (struct Node_s *)&Network_tWaitingGuaranteedPackets.ptMiddle )
    return 0;
  ptNext = Network_tWaitingGuaranteedPackets.ptHead->ptNext;
  ptTemp = Network_tWaitingGuaranteedPackets.ptHead->ptNext;
  if ( !Network_tWaitingGuaranteedPackets.ptHead->ptNext )
    return 0;
  do
  {
    v3 = Network_tIDList.ptHead->ptNext;
    v4 = Network_tIDList.ptHead;
    if ( Network_tIDList.ptHead->ptNext )
    {
      v5 = ptHead + 1;
      while ( memcmp(&v4[2], v5, 8u) )
      {
        v4 = v3;
        v3 = v3->ptNext;
        if ( !v3 )
          goto LABEL_11;
      }
      if ( v4 )
      {
        if ( (struct Node_s *)eNetworkID == v4[1].ptNext )
          ++nCounter;
      }
LABEL_11:
      ptNext = ptTemp;
    }
    ptHead = ptNext;
    ptNext = ptNext->ptNext;
    ptTemp = ptNext;
  }
  while ( ptNext );
  return nCounter;
}

// source: b/2/pc/pc_network.c:4117  [size]
enum bool __cdecl Network_IsInConnectState(void *pxContext, enum NetworkThreadStatus_e eStatus)
{
  return *(_DWORD *)pxContext == eStatus;
}

// source: b/2/pc/pc_network.c:4136  [anchor-hash]
void __cdecl Network_RunClient(void *pxContext)
{
  if ( !pxContext )
    NetManager_LogMessage("Network_RunClient: No interface\n");
  if ( *(_DWORD *)pxContext )
  {
    if ( *(_DWORD *)pxContext == 1 )
    {
      NetManager_LogMessage("Network_RunClient called in the CONNECTING case\n");
    }
    else if ( *(_DWORD *)pxContext == 2 )
    {
      Network_HandleSendQueues();
    }
    else
    {
      NetManager_LogMessage("Network_RunClient: Unknown network state");
    }
  }
  if ( *(_DWORD *)pxContext == 2 )
    Network_ClientConnectedReceive((struct NetworkThreadContext_s *)pxContext);
}

// source: b/2/pc/pc_network.c:4193  [anchor-strings]
void __cdecl Network_PostLoadServerContact(void *pxContext, char *zServerPassword)
{
  struct NetworkPacket_s *v2; // esi
  struct QTask_s *ptNext; // eax
  int v4; // esi
  char zTemp[256]; // [esp+0h] [ebp-100h] BYREF

  if ( *(_DWORD *)pxContext == 1 )
  {
    v2 = Network_AcquirePacket(0, 20);
    if ( NetManager_nSelectedSession == -1 )
      ptNext = Flow_ptFlow->ptNetManagerQTask[3].ptNext;
    else
      ptNext = (struct QTask_s *)dword_704B18[60 * NetManager_nSelectedSession];
    v2[1].nPacketHeader = (unsigned int)ptNext;
    strncpy((char *)&v2[1].nPacketID, zServerPassword, 0x10u);
    _snprintf(zTemp, 0xFFu, "Sending connect request to server, password '%s'...\n", (char *)&v2[1].nPacketID);
    NetManager_LogMessage(zTemp);
    Network_SendSocketMessage((struct sockaddr *)((char *)pxContext + 12), 16, v2, true, NETWORK_SENDTYPE_EXTERNAL);
    NetManager_LogMessage("Network_PostLoadServerContact(): Sent connect message, waiting for response\n...");
    Sleep(0x14u);
    v4 = 0;
    while ( 1 )
    {
      Network_ClientConnectedReceive((struct NetworkThreadContext_s *)pxContext);
      if ( *(_DWORD *)pxContext != 1 )
        break;
      Sleep(0x14u);
      if ( ++v4 >= 100 )
        return;
    }
    NetManager_LogMessage("Network_PostLoadServerContact(): Received connect response, ending wait\n");
  }
  else
  {
    NetManager_LogMessage("Network_PostLoadServerContact(), but not in connecting state\n");
  }
}

// source: b/2/pc/pc_network.c:4316  [layout]
void __cdecl Network_StopNetwork(void *pxInterface)
{
  int v1; // eax
  int v2; // ebx
  int v3; // ebx

  NetManager_LogMessage("Stopping network\n");
  Network_FreeQueues();
  NetManager_LogMessage("Queues freed\n");
  Network_FreeGuaranteedQueue();
  NetManager_LogMessage("Guaranteed queue freed\n");
  Network_FreeIDList();
  NetManager_LogMessage("ID list freed\n");
  v1 = *((_DWORD *)pxInterface + 4114);
  if ( v1 )
  {
    --Mem_nCurrentAllocations;
    v2 = *(_DWORD *)((v1 - 4) & 0xFFFFFFFC);
    Node_Remove((_DWORD **)v2);
    memset(*(void **)(v2 + 8), 0xCDu, *(_DWORD *)(v2 + 16));
    free((void *)v2);
  }
  *((_DWORD *)pxInterface + 4114) = 0;
  NetManager_LogMessage("Receive buffer freed\n");
  if ( Network_UDPSocket == -1 )
  {
    NetManager_LogMessage("Network_CloseUDPSocket: Socket was invalid\n");
  }
  else
  {
    closesocket(Network_UDPSocket);
    NetManager_LogMessage("Network_CloseUDPSocket: Socket closed\n");
  }
  NetManager_LogMessage("Game socket closed\n");
  v3 = *(_DWORD *)(((int)pxInterface - 4) & 0xFFFFFFFC);
  --Mem_nCurrentAllocations;
  Node_Remove((_DWORD **)v3);
  memset(*(void **)(v3 + 8), 0xCDu, *(_DWORD *)(v3 + 16));
  free((void *)v3);
  NetManager_LogMessage("Network context freed\n");
  Network_nLastReceivedPacketID = 0;
  Network_nSendCounter = 0;
  Network_nLoseCounter = 0;
  Network_nSendOK = 0;
  Network_nSendERROR = 0;
  Network_nSendBytes = 0;
  Network_nSendStatTimer = 0;
  dword_834E0C8 = 0;
  dword_834E0CC = 0;
  dword_834E0D0 = 0;
  dword_834E0D4 = 0;
  Network_nSendStatIndex = 0;
  Network_nReceiveStatIndex = 0;
  Network_nPrintTime = 0;
  Network_nReceivedQUIT = 0;
  Network_nPacketID = 1;
}

// source: b/2/pc/pc_network.c:4334  [anchor-caller]
void *__cdecl Network_StopClient(void *pxInterface)
{
  void *result; // eax

  Network_StopNetwork(pxInterface);
  Network_nLastConnectionResponse = 8;
  return result;
}

// source: b/2/pc/pc_network.c:4353  [anchor-strings]
enum bool __cdecl Network_BanPlayer(int eNetworkID)
{
  #pragma pack(push, 1)
  union
  {
    struct { unsigned __int8 nIP[4]; };
    struct { char igi2_o1[4]; char zTemp[256]; };
    char igi2_extent[260];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct Node_s *ptHead; // ecx
  struct Node_s *ptNext; // eax
  struct Node_s *v3; // esi
  unsigned __int8 ptPrev; // al
  unsigned __int8 v5; // cl
  unsigned __int8 ptPrev_high; // bl

  ptHead = Network_tIDList.ptHead;
  ptNext = Network_tIDList.ptHead->ptNext;
  if ( Network_tIDList.ptHead->ptNext )
  {
    while ( ptHead[1].ptNext != (struct Node_s *)eNetworkID )
    {
      ptHead = ptNext;
      ptNext = ptNext->ptNext;
      if ( !ptNext )
        goto LABEL_4;
    }
  }
  else
  {
LABEL_4:
    ptHead = nullptr;
  }
  if ( ptHead )
  {
    v3 = ptHead + 2;
    if ( ptHead == (struct Node_s *)-16 )
    {
      _snprintf(igi2_frame.zTemp, 0xFFu, "Network_BanPlayer: no socket for player[%d]\n", eNetworkID);
      NetManager_LogMessage(igi2_frame.zTemp);
      return false;
    }
    else
    {
      ntohs(HIWORD(ptHead[2].ptNext));
      ptPrev = (unsigned __int8)v3->ptPrev;
      v5 = BYTE1(v3->ptPrev);
      ptPrev_high = HIBYTE(v3->ptPrev);
      igi2_frame.nIP[2] = BYTE2(v3->ptPrev);
      igi2_frame.nIP[1] = v5;
      igi2_frame.nIP[0] = ptPrev;
      igi2_frame.nIP[3] = ptPrev_high;
      _snprintf(igi2_frame.zTemp, 0xFFu, "Network_BanPlayer: banning player at ip=%u.%u.%u.%u\n", ptPrev, v5, igi2_frame.nIP[2], ptPrev_high);
      NetManager_LogMessage(igi2_frame.zTemp);
      return Network_AddToBannedList(igi2_frame.nIP);
    }
  }
  else
  {
    _snprintf(igi2_frame.zTemp, 0xFFu, "Network_BanPlayer: No item for player[%d]\n", eNetworkID);
    NetManager_LogMessage(igi2_frame.zTemp);
    return false;
  }
}

// source: b/2/pc/pc_network.c:4409  [anchor-strings]
enum bool __cdecl Network_UnbanPlayer(int nIndex)
{
  struct Node_s *ptHead; // esi
  struct Node_s *ptNext; // eax
  int v3; // ecx
  int v5; // esi
  char zTemp[256]; // [esp+4h] [ebp-100h] BYREF

  ptHead = Network_tBannedList.ptHead;
  ptNext = Network_tBannedList.ptHead->ptNext;
  v3 = 0;
  if ( Network_tBannedList.ptHead->ptNext )
  {
    while ( v3 != nIndex )
    {
      ptHead = ptNext;
      ptNext = ptNext->ptNext;
      ++v3;
      if ( !ptNext )
        goto LABEL_4;
    }
    _snprintf(
      zTemp,
      0xFFu,
      "Removing ban on [%d]: %u.%u.%u.%u\n",
      v3,
      LOBYTE(ptHead[1].ptNext),
      BYTE1(ptHead[1].ptNext),
      BYTE2(ptHead[1].ptNext),
      HIBYTE(ptHead[1].ptNext));
    NetManager_LogMessage(zTemp);
    Node_Remove(ptHead);
    v5 = *(_DWORD *)((unsigned int)&ptHead[-1].ptPrev & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v5);
    memset(*(void **)(v5 + 8), 0xCDu, *(_DWORD *)(v5 + 16));
    free((void *)v5);
    return true;
  }
  else
  {
LABEL_4:
    _snprintf(zTemp, 0xFFu, "Network: Entry [%d] not in ban list\n", nIndex);
    NetManager_LogMessage(zTemp);
    return false;
  }
}

// source: b/2/pc/pc_network.c:4460  [anchor-mhash]
void __cdecl Network_Open()
{
  int *p_nSize; // eax
  int *v1; // eax
  struct WSAData tData; // [esp+4h] [ebp-190h] BYREF

  p_nSize = &Network_aSendStat[0].nSize;
  do
  {
    p_nSize[1] = 0;
    *p_nSize = 0;
    p_nSize[2] = 0;
    *(p_nSize - 1) = 0;
    p_nSize += 4;
  }
  while ( (int)p_nSize < 7590388 );
  Network_nSendStatIndex = 0;
  v1 = &Network_aReceiveStat[0].nSize;
  do
  {
    v1[1] = 0;
    *v1 = 0;
    v1[2] = 0;
    *(v1 - 1) = 0;
    v1 += 4;
  }
  while ( (int)v1 < 7586956 );
  Network_nReceiveStatIndex = 0;
  Network_tAdapterList.ptHead = (struct Node_s *)&Network_tAdapterList.ptMiddle;
  Network_tAdapterList.ptTail = (struct Node_s *)&Network_tAdapterList;
  Network_tAdapterList.ptMiddle = nullptr;
  if ( !WSAStartup(0x101u, &tData) )
  {
    Network_EnumAdapters();
    Network_pfExternalReceiveHandler = nullptr;
    Network_pfConsoleReceiveHandler = nullptr;
    Network_isRandomInitiated = false;
    Network_tBannedList.ptHead = (struct Node_s *)&Network_tBannedList.ptMiddle;
    Network_tBannedList.ptTail = (struct Node_s *)&Network_tBannedList;
    Network_tBannedList.ptMiddle = nullptr;
  }
}

// source: b/2/pc/pc_network.c:4539  [anchor-hash]
void __cdecl Network_Close()
{
  NetManager_LogMessage("Network_Close()\n");
  Network_pfExternalReceiveHandler = nullptr;
  Network_pfConsoleReceiveHandler = nullptr;
  Network_FreeAdapters();
  Network_FreeBannedList();
  WSACleanup();
}

// source: b/2/pc/pc_network.c:4568  [anchor-strings]
void __cdecl Network_AddPacketToQueue(
        int eNetworkID,
        enum NetworkQueue_e eQueue,
        unsigned __int8 *pnData,
        unsigned int nDataSize)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct Node_s *ptHead; };
    struct { char igi2_o1[4]; char zTemp[256]; };
    char igi2_extent[260];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  _WORD *v5; // ebx
  _DWORD *v6; // eax
  struct Node_s *ptNext; // eax
  struct NetworkPacket_s *v8; // ebx
  unsigned int v9; // eax

  if ( eQueue )
  {
    igi2_frame.ptHead = Network_tIDList.ptHead;
    ptNext = Network_tIDList.ptHead->ptNext;
    if ( Network_tIDList.ptHead->ptNext )
    {
      while ( igi2_frame.ptHead[1].ptNext != (struct Node_s *)eNetworkID )
      {
        igi2_frame.ptHead = ptNext;
        ptNext = ptNext->ptNext;
        if ( !ptNext )
          goto LABEL_6;
      }
      v8 = (struct NetworkPacket_s *)Mem_AllocFn(nDataSize + 24, 4);
      v8->nPacketHeader = htonl(0xDEADBEEF);
      v8->nCRC = 0;
      v8->nSize = htons(nDataSize);
      v8->ePacketType = 2;
      *(unsigned int *)((char *)&v8[1].nPacketHeader + nDataSize) = htonl(0xBADEABEE);
      qmemcpy(&v8[1], pnData, nDataSize);
      v9 = Network_nPacketID;
      v8->nPacketID = Network_nPacketID;
      Network_nPacketID = v9 + 1;
      v8->eDestinationID = eNetworkID;
      Network_SendSocketMessage((struct sockaddr *)&igi2_frame.ptHead[2], 16, v8, true, NETWORK_SENDTYPE_FRESH);
    }
    else
    {
LABEL_6:
      _snprintf(
        igi2_frame.zTemp,
        0xFFu,
        "Network_AddPacketToQueue: No socket found for [%d], skipping non-guaranteed message\n",
        eNetworkID);
      NetManager_LogMessage(igi2_frame.zTemp);
    }
  }
  else
  {
    v5 = Mem_AllocFn(nDataSize + 24, 4);
    *(_DWORD *)v5 = htonl(0xDEADBEEF);
    v5[6] = 0;
    v5[7] = htons(nDataSize);
    *((_BYTE *)v5 + 16) = 3;
    *(_DWORD *)((char *)v5 + nDataSize + 20) = htonl(0xBADEABEE);
    qmemcpy(v5 + 10, pnData, nDataSize);
    v6 = Mem_AllocFn(28, 4);
    v6[1] = 0;
    *v6 = 0;
    v6[2] = eNetworkID;
    v6[6] = v5;
    v6[3] = Network_nGuaranteedPacketID[eNetworkID]++;
    v6[5] = 0;
    v6[4] = -1;
    List_AddTail(v6, (int)Network_atQueues);
  }
}

// source: b/2/pc/pc_network.c:4670  [size]
struct List_s *__cdecl Network_GetAdapterList()
{
  return &Network_tAdapterList;
}

// source: b/2/pc/pc_network.c:4685  [anchor-strings]
enum bool __cdecl Network_RunEnumeration(void *pxInterface)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct sockaddr_in tSockAddr; };
    struct { char igi2_o1[16]; struct NetworkMessageContext_s tMessageContext; };
    char igi2_extent[48];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v1; // eax
  bool v2; // zf
  int v3; // ecx
  u_short v4; // ax

  v1 = Network_Receive(Network_UDPSocket, *((char **)pxInterface + 4114), &igi2_frame.tSockAddr);
  v2 = v1 == 0;
  if ( v1 < 0 )
    return false;
  while ( 1 )
  {
    if ( !v2 )
    {
      *((_DWORD *)pxInterface + 11) = *((_DWORD *)pxInterface + 4114);
      *((_DWORD *)pxInterface + 12) = v1;
      *((_DWORD *)pxInterface + 13) = 0;
      if ( Network_ParsePacket((struct NetworkParseContext_s *)((char *)pxInterface + 44)) )
        break;
    }
LABEL_6:
    v1 = Network_Receive(Network_UDPSocket, *((char **)pxInterface + 4114), &igi2_frame.tSockAddr);
    v2 = v1 == 0;
    if ( v1 < 0 )
      return false;
  }
  while ( 1 )
  {
    igi2_frame.tMessageContext.tSockAddr.sin_addr.S_un.S_addr = igi2_frame.tSockAddr.sin_addr.S_un.S_addr;
    v3 = *((unsigned __int16 *)pxInterface + 43);
    *(_DWORD *)&igi2_frame.tMessageContext.tSockAddr.sin_family = *(_DWORD *)&igi2_frame.tSockAddr.sin_family;
    *(_DWORD *)igi2_frame.tMessageContext.tSockAddr.sin_zero = *(_DWORD *)igi2_frame.tSockAddr.sin_zero;
    *(_DWORD *)&igi2_frame.tMessageContext.tSockAddr.sin_zero[4] = *(_DWORD *)&igi2_frame.tSockAddr.sin_zero[4];
    igi2_frame.tMessageContext.pxInterface = pxInterface;
    igi2_frame.tMessageContext.pxNetworkPacketContents = (char *)pxInterface + 92;
    v4 = ntohs(v3);
    v2 = *((_BYTE *)pxInterface + 88) == 6;
    igi2_frame.tMessageContext.nPacketContentsSize = v4;
    if ( v2 )
      break;
    if ( Network_ParsePacket((struct NetworkParseContext_s *)((char *)pxInterface + 44)) == false )
      goto LABEL_6;
  }
  NetManager_LogMessage("Network_RunEnumeration: Got client_serverinfo reply from server\n");
  (*((void (__cdecl **)(_DWORD, int, struct NetworkMessageContext_s *))pxInterface + 7))(
    *((_DWORD *)pxInterface + 8),
    4,
    &igi2_frame.tMessageContext);
  return true;
}

// source: b/2/pc/pc_network.c:4748  [anchor-hash]
void __cdecl Network_StopEnumeration(void *pxInterface)
{
  int v2; // eax
  int v3; // esi
  int v4; // esi

  v2 = *((_DWORD *)pxInterface + 4114);
  if ( v2 )
  {
    v3 = *(_DWORD *)((v2 - 4) & 0xFFFFFFFC);
    --Mem_nCurrentAllocations;
    Node_Remove((_DWORD **)v3);
    memset(*(void **)(v3 + 8), 0xCDu, *(_DWORD *)(v3 + 16));
    free((void *)v3);
  }
  *((_DWORD *)pxInterface + 4114) = 0;
  NetManager_LogMessage("Network_StopEnumeration(): keeping socket alive\n");
  v4 = *(_DWORD *)(((int)pxInterface - 4) & 0xFFFFFFFC);
  --Mem_nCurrentAllocations;
  Node_Remove((_DWORD **)v4);
  memset(*(void **)(v4 + 8), 0xCDu, *(_DWORD *)(v4 + 16));
  free((void *)v4);
}

// source: b/2/pc/pc_network.c:4772  [anchor-strings]
void *__cdecl Network_FindServer(
        struct NetworkAdapterItem_s *ptAdapter,
        int (__cdecl *pfHandler__)(void *, enum NetworkMessage_e, struct NetworkMessageContext_s *),
        unsigned __int8 *zIpString,
        int nPort,
        int nClientPort)
{
  _DWORD *v5; // esi
  int Error; // eax
  int v8; // esi

  v5 = Mem_AllocFn(16460, 4);
  memset(v5, 0, 0x404Cu);
  v5[7] = pfHandler__;
  *v5 = 1;
  v5[8] = 0;
  v5[15] = 0;
  v5[16] = 0;
  v5[14] = 0;
  *((_WORD *)v5 + 6) = 2;
  *((_WORD *)v5 + 7) = htons(nPort);
  v5[4] = *(_DWORD *)zIpString;
  Network_UDPSocket = socket(2, 2, 17);
  if ( Network_UDPSocket == -1 )
  {
    Error = WSAGetLastError();
    Network_DebugError("Network_FindServer:socket()", Error);
  }
  else
  {
    if ( Network_ClientBindGlobalUDPSocket(ptAdapter, nClientPort) > 0 )
    {
      v5[4114] = Mem_AllocFn(0x4000, 4);
      return v5;
    }
    NetManager_LogMessage("Failed to bind to client socket\n");
  }
  if ( Network_UDPSocket == -1 )
  {
    NetManager_LogMessage("Network_CloseUDPSocket: Socket was invalid\n");
  }
  else
  {
    closesocket(Network_UDPSocket);
    NetManager_LogMessage("Network_CloseUDPSocket: Socket closed\n");
  }
  v8 = *(_DWORD *)((unsigned int)(v5 - 1) & 0xFFFFFFFC);
  --Mem_nCurrentAllocations;
  Node_Remove((_DWORD **)v8);
  memset(*(void **)(v8 + 8), 0xCDu, *(_DWORD *)(v8 + 16));
  free((void *)v8);
  return nullptr;
}

// source: b/2/pc/pc_network.c:4847  [anchor-strings]
void __cdecl Network_SendRequestInfo(void *pxContext)
{
  struct NetworkPacket_s *v1; // esi

  v1 = (struct NetworkPacket_s *)Mem_AllocFn(24, 4);
  v1->nPacketHeader = htonl(0xDEADBEEF);
  v1->nCRC = 0;
  v1->nSize = htons(0);
  v1->ePacketType = 5;
  v1[1].nPacketHeader = htonl(0xBADEABEE);
  Network_SendSocketMessage((struct sockaddr *)((char *)pxContext + 12), 16, v1, true, NETWORK_SENDTYPE_EXTERNAL);
  NetManager_LogMessage("Find server: Sent server info request...\n");
}
