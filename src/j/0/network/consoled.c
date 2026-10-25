/* j/0/network/consoled.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/network/consoled.c:39  [anchor-callee]
struct ConsoledUser_s *__cdecl Consoled_GetUser(struct sockaddr *sender)
{
  struct QTask_s *ptNext; // eax
  int v2; // ebx
  void **i; // edx
  struct ConsoledUser_s *result; // eax
  int v5; // [esp+10h] [ebp-4h]

  ptNext = QTask_GetFirstChildOfType(Flow_ptFlow->ptNetManagerQTask, Consoled_eQTaskType)[1].ptNext;
  v2 = 0;
  v5 = *(_DWORD *)&ptNext->eQTaskType;
  if ( v5 <= 0 )
    return nullptr;
  for ( i = (void **)&ptNext[1].tQTaskChildren.ptHead->ptNext; ; ++i )
  {
    result = (struct ConsoledUser_s *)*i;
    if ( !memcmp(*i, sender, 0x10u) )
      break;
    if ( ++v2 >= v5 )
      return nullptr;
  }
  return result;
}

// source: j/0/network/consoled.c:82  [anchor-strings]
void __cdecl Consoled_AddUser(struct sockaddr *sender)
{
  struct QObjectVector_s *ptNext; // esi
  unsigned int nAllocated; // eax
  struct sockaddr *v3; // ebx
  DWORD PerformanceCounter; // eax

  ptNext = (struct QObjectVector_s *)QTask_GetFirstChildOfType(Flow_ptFlow->ptNetManagerQTask, Consoled_eQTaskType)[1].ptNext;
  if ( ptNext->nAllocated == ptNext->nSize )
    QObjectVector_Realloc(ptNext, ptNext->nReallocSize);
  nAllocated = ptNext->nAllocated;
  v3 = (struct sockaddr *)ptNext->papxElement[nAllocated];
  ptNext->nAllocated = nAllocated + 1;
  *v3 = *sender;
  if ( Timer_isPerformanceCounter )
    PerformanceCounter = Timer_GetPerformanceCounter();
  else
    PerformanceCounter = GetTickCount();
  *(_DWORD *)&v3[1].sa_family = PerformanceCounter - Timer_nStartTime;
  NetManager_LogMessage("Consoled: User added\n");
}

// source: j/0/network/consoled.c:128  [anchor-strings]
enum bool __cdecl Consoled_RemoveIdleUser(struct Consoled_s *ptConsoled)
{
  DWORD PerformanceCounter; // eax
  struct QObjectVector_s *ptUsers; // ebx
  int nAllocated; // edi
  signed int v5; // edx
  void **papxElement; // ecx
  struct sockaddr_in *v7; // esi
  int nMaxIdleTime; // [esp+14h] [ebp-4h]

  if ( Timer_isPerformanceCounter )
    PerformanceCounter = Timer_GetPerformanceCounter();
  else
    PerformanceCounter = GetTickCount();
  ptUsers = ptConsoled->ptUsers;
  nAllocated = ptUsers->nAllocated;
  v5 = 0;
  if ( nAllocated <= 0 )
    return false;
  papxElement = ptUsers->papxElement;
  nMaxIdleTime = ptConsoled->nMaxIdleTime;
  while ( 1 )
  {
    v7 = (struct sockaddr_in *)*papxElement;
    if ( (int)(PerformanceCounter - Timer_nStartTime) > (int)(nMaxIdleTime + *((_DWORD *)*papxElement + 4)) )
      break;
    ++v5;
    ++papxElement;
    if ( v5 >= nAllocated )
      return false;
  }
  QObjectVector_RemoveElement(ptUsers, v5);
  Network_SendConsoleMessage(v7, "Timed out, please log in again");
  NetManager_LogMessage("Consoled: User timed out\n");
  return true;
}

// source: j/0/network/consoled.c:175  [anchor-hash]
void __cdecl Consoled_RemoveAllIdleUsers(struct Consoled_s *ptConsoled)
{
  while ( Consoled_RemoveIdleUser(ptConsoled) )
    ;
}

// source: j/0/network/consoled.c:194  [anchor-hash]
enum bool __cdecl Consoled_IsAuthenticationValid(char *zText)
{
  if ( !strncmp(zText, ServerConfig_tServerConfig.zRConPassword, 8u) )
  {
    NetManager_LogMessage("Authentication OK\n");
    return true;
  }
  else
  {
    NetManager_LogMessage("Authentication failed\n");
    return false;
  }
}

// source: j/0/network/consoled.c:220  [anchor-hash]
enum bool __cdecl Consoled_IsEvalProgress()
{
  struct QTask_s *FirstChildOfType; // eax

  FirstChildOfType = QTask_GetFirstChildOfType(Flow_ptFlow->ptNetManagerQTask, Consoled_eQTaskType);
  return FirstChildOfType && FirstChildOfType[1].tQTaskRefList.ptHead;
}

// source: j/0/network/consoled.c:242  [anchor-hash]
struct sockaddr *__cdecl Consoled_GetConsoleAddress()
{
  return (struct sockaddr *)&QTask_GetFirstChildOfType(Flow_ptFlow->ptNetManagerQTask, Consoled_eQTaskType)[1].ptPrev;
}

// source: j/0/network/consoled.c:262  [anchor-hash]
struct NetManagerGameMessageList *__cdecl Consoled_ConfigListMessage(
        struct NetManagerGameMessageList *ptGameMessage)
{
  unsigned __int16 v1; // dx
  struct QTask_s *ptNetManagerQTask; // esi
  struct NetManagerGameMessageList *result; // eax
  struct Flow_t *v5; // ecx
  unsigned __int16 v6; // dx
  struct QTask_s **p_ptPrev; // eax
  struct sockaddr *p_tSockAddr; // edi

  v1 = Consoled_eQTaskType;
  ptNetManagerQTask = Flow_ptFlow->ptNetManagerQTask;
  result = (struct NetManagerGameMessageList *)QTask_GetFirstChildOfType(ptNetManagerQTask, Consoled_eQTaskType);
  if ( result
    && (result = (struct NetManagerGameMessageList *)QTask_GetFirstChildOfType(ptNetManagerQTask, v1)) != nullptr
    && result[1].nCommandID )
  {
    NetManager_LogMessage("Consoled_ConfigListMessage: Console eval observed\n");
    v5 = Flow_ptFlow;
    v6 = Consoled_eQTaskType;
    ptGameMessage->isConsole = 1;
    p_ptPrev = &QTask_GetFirstChildOfType(v5->ptNetManagerQTask, v6)[1].ptPrev;
    p_tSockAddr = &ptGameMessage->tSockAddr;
    *(_DWORD *)&p_tSockAddr->sa_family = *p_ptPrev;
    *(_DWORD *)&p_tSockAddr->sa_data[2] = p_ptPrev[1];
    *(_DWORD *)&p_tSockAddr->sa_data[6] = p_ptPrev[2];
    result = (struct NetManagerGameMessageList *)p_ptPrev[3];
    *(_DWORD *)&p_tSockAddr->sa_data[10] = result;
  }
  else
  {
    ptGameMessage->isConsole = 0;
  }
  return result;
}

// source: j/0/network/consoled.c:290  [anchor-hash]
void __cdecl Console_SetRemoteConsoleEval(struct sockaddr *console)
{
  struct QTask_s *FirstChildOfType; // eax

  FirstChildOfType = QTask_GetFirstChildOfType(Flow_ptFlow->ptNetManagerQTask, Consoled_eQTaskType);
  FirstChildOfType[1].tQTaskRefList.ptHead = (struct QReference_s *)1;
  *(struct sockaddr *)&FirstChildOfType[1].ptPrev = *console;
}

// source: j/0/network/consoled.c:311  [anchor-hash]
void __cdecl Console_ClearConsoleEval()
{
  QTask_GetFirstChildOfType(Flow_ptFlow->ptNetManagerQTask, Consoled_eQTaskType)[1].tQTaskRefList.ptHead = nullptr;
}

// source: j/0/network/consoled.c:330  [anchor-strings]
void __cdecl Consoled_ProcessInput(
        char *query,
        int len,
        struct sockaddr *sender,
        unsigned __int8 *nIP,
        unsigned __int16 nPort)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct QTask_s **p_ptPrev; };
    struct { char igi2_o1[4]; char zResponse[256]; };
    struct { char igi2_o2[260]; char zTemp[256]; };
    char igi2_extent[516];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct QTask_s *FirstChildOfType; // edi
  struct ConsoledUser_s *User; // ebx
  struct QTask_s *v8; // edx
  bool v9; // zf
  char *v10; // edi

  FirstChildOfType = QTask_GetFirstChildOfType(Flow_ptFlow->ptNetManagerQTask, Consoled_eQTaskType);
  User = Consoled_GetUser(sender);
  _snprintf(igi2_frame.zTemp, 0xFFu, "Consoled: '%s' run from %u.%u.%u.%u:%d\n", query, *nIP, nIP[1], nIP[2], nIP[3], nPort);
  NetManager_LogMessage(igi2_frame.zTemp);
  if ( User )
  {
    v8 = *(struct QTask_s **)&User->tSockAddr.sa_family;
    igi2_frame.p_ptPrev = &FirstChildOfType[1].ptPrev;
    FirstChildOfType[1].ptPrev = v8;
    FirstChildOfType[1].tQTaskChildren.ptHead = *(struct QTask_s **)&User->tSockAddr.sa_data[2];
    FirstChildOfType[1].tQTaskChildren.ptMiddle = *(struct QTask_s **)&User->tSockAddr.sa_data[6];
    FirstChildOfType[1].tQTaskChildren.ptTail = *(struct QTask_s **)&User->tSockAddr.sa_data[10];
    FirstChildOfType[1].tQTaskRefList.ptHead = (struct QReference_s *)1;
    if ( !strcmp(query, "food") )
      Network_SendConsoleMessage((struct sockaddr_in *)&FirstChildOfType[1].ptPrev, "FAARIKAAL!");
    else
      NetworkCommand_ParseEvalCommandLine(query);
    v9 = Timer_isPerformanceCounter == 0;
    FirstChildOfType[1].tQTaskRefList.ptHead = nullptr;
    if ( v9 )
      User->nLastAccessed = GetTickCount() - Timer_nStartTime;
    else
      User->nLastAccessed = Timer_GetPerformanceCounter() - Timer_nStartTime;
  }
  else
  {
    memset(igi2_frame.zResponse, 0, 255);
    if ( !strncmp(query, ServerConfig_tServerConfig.zRConPassword, 8u) )
    {
      NetManager_LogMessage("Authentication OK\n");
      _snprintf(igi2_frame.zResponse, 0xFFu, "Access granted to IGI2 server (v.%s)", g_zPlayer1);
      Consoled_AddUser(sender);
    }
    else
    {
      NetManager_LogMessage("Authentication failed\n");
      v10 = (char *)&igi2_frame.p_ptPrev + 3;
      while ( *++v10 )
        ;
      strcpy(v10, "Please enter password + <enter>");
      NetManager_LogMessage("Unauthenticated user accessing console\n");
    }
    Network_SendConsoleMessage((struct sockaddr_in *)sender, igi2_frame.zResponse);
  }
}

// source: j/0/network/consoled.c:399  [anchor-caller]
void __cdecl Consoled_CB(char *query, int len, struct sockaddr *sender)
{
  int v3; // edi
  struct sockaddr *v4; // esi
  u_short v5; // ax
  CHAR v6; // dl
  CHAR v7; // cl
  CHAR v8; // dl

  v3 = len;
  if ( len > 0 && *query == 47 )
  {
    if ( query[len - 1] == 10 )
    {
      query[len - 1] = 0;
      --v3;
    }
    v4 = sender;
    v5 = ntohs(*(_WORD *)sender->sa_data);
    v6 = v4->sa_data[3];
    LOBYTE(len) = v4->sa_data[2];
    v7 = v4->sa_data[4];
    BYTE1(len) = v6;
    v8 = v4->sa_data[5];
    BYTE2(len) = v7;
    HIBYTE(len) = v8;
    Consoled_ProcessInput(query + 1, v3 - 1, v4, (unsigned __int8 *)&len, v5);
  }
}

// source: j/0/network/consoled.c:436  [size]
struct QTask_s *__cdecl Consoled_New(
        struct QTask_s *ptParentQTask,
        struct ConsoledCreateContext_s *ptCreateContext)
{
  return QTask_NewFn(ptParentQTask, Consoled_eQTaskType, ptCreateContext);
}

// source: j/0/network/consoled.c:458  [size]
unsigned __int16 __cdecl Consoled_GetQTaskType()
{
  return Consoled_eQTaskType;
}

// source: j/0/network/consoled.c:475  [size]
struct Consoled_s *__cdecl Consoled_GetConsoled()
{
  return (struct Consoled_s *)QTask_GetFirstChildOfType(Flow_ptFlow->ptNetManagerQTask, Consoled_eQTaskType);
}

// source: j/0/network/consoled.c:488  [anchor-strings]
void __cdecl Consoled_CreateHandler(struct QTask_s *ptQTask, void *pxContext)
{
  struct QObjectVector_s *v2; // esi
  bool v3; // zf
  DWORD TickCount; // eax

  v2 = (struct QObjectVector_s *)Mem_AllocFn(52, 4);
  v2->isStrictOrder = false;
  v2->nSize = 0;
  v2->nAllocated = 0;
  v2->nReallocSize = 3;
  v2->papxElement = nullptr;
  v2->nElementSize = 24;
  v2->tMemPool.nBlocks = 0;
  v2->tMemPool.nAllocatedBlocks = 0;
  v2->tMemPool.nAlignment = 4;
  v2->tMemPool.nBlockSize = 24;
  v2->tMemPool.nReAllocBlocks = 3;
  v2->tMemPool.tMemPoolFreeList.ptHead = nullptr;
  v2->tMemPool.tMemPoolSegmentList.ptHead = nullptr;
  MemPool_ReAlloc(&v2->tMemPool, 0xAu);
  QObjectVector_Realloc(v2, 0xAu);
  v3 = Timer_isPerformanceCounter == 0;
  ptQTask[1].ptNext = (struct QTask_s *)v2;
  ptQTask[1].tQTaskRefList.ptHead = nullptr;
  if ( v3 )
    TickCount = GetTickCount();
  else
    TickCount = Timer_GetPerformanceCounter();
  ptQTask[1].tQTaskRefList.ptMiddle = (struct QReference_s *)(TickCount - Timer_nStartTime);
  ptQTask[1].tQTaskRefList.ptTail = *(struct QReference_s **)pxContext;
  ptQTask[1].ptParent = *((struct QTask_s **)pxContext + 1);
  Network_pfConsoleReceiveHandler = Consoled_CB;
  Network_ConsoleReceiveMarker = 47;
  NetManager_LogMessage("Consoled created\n");
}

// source: j/0/network/consoled.c:520  [anchor-mhash]
void __cdecl Consoled_RunHandler(struct QTask_s *ptQTask)
{
  DWORD PerformanceCounter; // eax

  if ( Timer_isPerformanceCounter )
    PerformanceCounter = Timer_GetPerformanceCounter();
  else
    PerformanceCounter = GetTickCount();
  if ( (signed int)(PerformanceCounter - Timer_nStartTime - (unsigned int)ptQTask[1].tQTaskRefList.ptMiddle) > (int)ptQTask[1].tQTaskRefList.ptTail )
  {
    while ( Consoled_RemoveIdleUser((struct Consoled_s *)ptQTask) )
      ;
    if ( Timer_isPerformanceCounter )
      ptQTask[1].tQTaskRefList.ptMiddle = (struct QReference_s *)(Timer_GetPerformanceCounter() - Timer_nStartTime);
    else
      ptQTask[1].tQTaskRefList.ptMiddle = (struct QReference_s *)(GetTickCount() - Timer_nStartTime);
  }
}

// source: j/0/network/consoled.c:543  [anchor-strings]
void __cdecl Consoled_DeleteHandler(struct QTask_s *ptQTask)
{
  struct QTask_s *ptNext; // eax

  *(_DWORD *)&ptQTask[1].ptNext->eQTaskType = 0;
  ptNext = ptQTask[1].ptNext;
  Network_pfConsoleReceiveHandler = nullptr;
  Network_ConsoleReceiveMarker = 47;
  QObjectVector_Delete((struct QObjectVector_s *)ptNext);
  ptQTask[1].ptNext = nullptr;
  NetManager_LogMessage("Consoled was shut down\n");
}

// source: j/0/network/consoled.c:565  [size]
void __cdecl Consoled_Close()
{
  QTask_DeleteQTaskType(Consoled_eQTaskType);
}

// source: j/0/network/consoled.c:579  [anchor-hash]
void __cdecl Consoled_Open()
{
  unsigned __int16 BaseQTaskType; // ax
  unsigned __int16 v1; // si

  BaseQTaskType = QTask_GetBaseQTaskType();
  v1 = QTask_NewQTaskType("Consoled", 76, BaseQTaskType, 0, 0);
  Consoled_eQTaskType = v1;
  QTask_LinkQTaskEventHandlerFn(v1, 0, Consoled_CreateHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 1, Consoled_RunHandler);
  QTask_LinkQTaskEventHandlerNoContextFn(v1, 2, Consoled_DeleteHandler);
}
