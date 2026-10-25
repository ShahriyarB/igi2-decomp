/* b/2/pc/pc_telnethost.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: b/2/pc/pc_telnethost.c:152  [size]
void __cdecl TelnetHost_ParseQuit(int argc, char **argv, void *pxCommandContext)
{
  if ( pxCommandContext )
    *((_DWORD *)pxCommandContext + 8203) = 1;
}

// source: b/2/pc/pc_telnethost.c:171  [anchor-callee]
BOOL __cdecl TelnetHost_printf(int a1, char *Format, ...)
{
  #pragma pack(push, 1)
  union
  {
    struct { void *v5; };
    struct { char igi2_o1[8]; char Buffer[8192]; };
    char igi2_extent[8200];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v2; // edi
  char *v3; // edx
  va_list ArgList; // [esp+200Ch] [ebp+8h] BYREF ARGSLOT

  va_start(ArgList, Format);
  v2 = vsprintf(igi2_frame.Buffer, Format, ArgList);
  WaitForSingleObject(*(HANDLE *)(a1 + 16404), 0xFFFFFFFF);
  if ( (unsigned int)(v2 + *(_DWORD *)(a1 + 8)) >= 0x2000 )
    *(_DWORD *)(a1 + 8) = 0;
  v3 = (char *)(*(_DWORD *)(a1 + 8) + a1 + 8212);
  *(_DWORD *)(a1 + 8208) = v3;
  strcpy(v3, igi2_frame.Buffer);
  igi2_frame.v5 = *(void **)(a1 + 16404);
  *(_DWORD *)(a1 + 8) += (int)(v2);
  return ReleaseMutex(igi2_frame.v5);
}

// source: b/2/pc/pc_telnethost.c:210  [anchor-callee]
enum bool __cdecl TelnetHost_AuthenticateUser(char *pzUsername, char *pzPassword)
{
  char *v2; // esi
  unsigned int v3; // edi

  v2 = String1;
  v3 = 0;
  while ( _stricmp(v2 - 256, pzUsername) || _stricmp(v2, pzPassword) )
  {
    v3 += 512;
    v2 += 512;
    if ( v3 >= 0x200 )
      return false;
  }
  return true;
}

// source: b/2/pc/pc_telnethost.c:234  [anchor-mhash]
int __cdecl TelnetHost_GetTelnetOptionID(int eOption)
{
  int result; // eax

  result = 0;
  while ( stru_682610[result].eOption != eOption )
  {
    if ( (unsigned int)++result >= 0xB )
      return 0;
  }
  return result;
}

// source: b/2/pc/pc_telnethost.c:257  [size]
char *__cdecl TelnetHost_GetTelnetCommandString(int eCommand)
{
  return *((char **)&_lconv_c.decimal_point + eCommand);
}

// source: b/2/pc/pc_telnethost.c:271  [anchor-mhash]
char *__cdecl TelnetHost_GetTelnetOptionString(int eOption)
{
  int v1; // eax

  v1 = 0;
  while ( stru_682610[v1].eOption != eOption )
  {
    if ( (unsigned int)++v1 >= 0xB )
    {
      v1 = 0;
      return stru_682610[v1].zName;
    }
  }
  return stru_682610[v1].zName;
}

// source: b/2/pc/pc_telnethost.c:288  [anchor-hash]
void TelnetHost_SendTelnetCommand(struct TelnetSocketContext_s *ptTelnetSocketContext, int eCommand, ...)
{
  int v2; // eax
  int v3; // ecx
  int *p_eCommand; // edx
  char buf[8192]; // [esp+0h] [ebp-2000h] BYREF

  LOBYTE(v2) = eCommand;
  v3 = 0;
  if ( eCommand >= 0 )
  {
    p_eCommand = &eCommand;
    do
    {
      ++p_eCommand;
      buf[v3] = v2;
      v2 = *p_eCommand;
      ++v3;
    }
    while ( *p_eCommand >= 0 );
  }
  send(ptTelnetSocketContext->tSocket, buf, v3, 0);
}

// source: b/2/pc/pc_telnethost.c:325  [anchor-callee]
int __cdecl ParseTelnetWill(
        struct TelnetSocketContext_s *ptTelnetSocketContext,
        unsigned __int8 *a2)
{
  unsigned __int8 v2; // bl
  int v4; // eax

  v2 = *a2;
  v4 = 0;
  while ( stru_682610[v4].eOption != v2 )
  {
    if ( (unsigned int)++v4 >= 0xB )
    {
      v4 = 0;
      break;
    }
  }
  TelnetHost_printf((int)ptTelnetSocketContext, "%s ", stru_682610[v4].zName);
  TelnetHost_SendTelnetCommand(ptTelnetSocketContext, 255, 254, v2, -1);
  return 1;
}

// source: b/2/pc/pc_telnethost.c:354  [anchor-callee]
int __cdecl ParseTelnetDo(
        struct TelnetSocketContext_s *ptTelnetSocketContext,
        int result,
        struct TelnetSocketContext_s *ptTelnetSocketContexta)
{
  unsigned __int8 tSocket; // bl
  int v5; // eax

  if ( result >= 1 )
  {
    tSocket = ptTelnetSocketContexta->tSocket;
    v5 = 0;
    while ( stru_682610[v5].eOption != LOBYTE(ptTelnetSocketContexta->tSocket) )
    {
      if ( (unsigned int)++v5 >= 0xB )
      {
        v5 = 0;
        break;
      }
    }
    TelnetHost_printf((int)ptTelnetSocketContext, "%s ", stru_682610[v5].zName);
    TelnetHost_SendTelnetCommand(ptTelnetSocketContext, 255, 252, tSocket, -1);
    return 1;
  }
  return result;
}

// source: b/2/pc/pc_telnethost.c:384  [anchor-callee]
int __cdecl ParseTelnetDont(
        int result,
        struct TelnetSocketContext_s *ptTelnetSocketContext,
        unsigned __int8 *pCommand)
{
  int v3; // eax

  if ( result >= 1 )
  {
    v3 = 0;
    while ( stru_682610[v3].eOption != *pCommand )
    {
      if ( (unsigned int)++v3 >= 0xB )
      {
        v3 = 0;
        break;
      }
    }
    TelnetHost_printf((int)ptTelnetSocketContext, "%s ", stru_682610[v3].zName);
    return 1;
  }
  return result;
}

// source: b/2/pc/pc_telnethost.c:411  [anchor-callee]
int __cdecl ParseTelnetWont(
        int result,
        struct TelnetSocketContext_s *ptTelnetSocketContext,
        unsigned __int8 *pCommand)
{
  int v3; // eax

  if ( result >= 1 )
  {
    v3 = 0;
    while ( stru_682610[v3].eOption != *pCommand )
    {
      if ( (unsigned int)++v3 >= 0xB )
      {
        v3 = 0;
        break;
      }
    }
    TelnetHost_printf((int)ptTelnetSocketContext, "%s ", stru_682610[v3].zName);
    return 1;
  }
  return result;
}

// source: b/2/pc/pc_telnethost.c:456  [anchor-callee]
enum bool __cdecl ReadCharacterFromStream(
        unsigned __int8 *pCharacterRead,
        int *piOffset,
        unsigned __int8 *pStream,
        int nStreamLength)
{
  int v4; // eax
  unsigned __int8 v5; // dl
  int v6; // eax

  v4 = *piOffset;
  if ( nStreamLength > *piOffset )
  {
    v5 = pStream[v4];
    v6 = v4 + 1;
    if ( v5 != 0xFF )
    {
      *pCharacterRead = v5;
      *piOffset = v6;
      return true;
    }
    if ( nStreamLength > v6 )
    {
      *pCharacterRead = pStream[v6];
      *piOffset = v6 + 1;
      return *pCharacterRead == 0xFF;
    }
  }
  *piOffset = nStreamLength;
  *pCharacterRead = -1;
  return false;
}

// source: b/2/pc/pc_telnethost.c:502  [anchor-strings]
int __cdecl ParseTelnetSubNegotiation(
        struct TelnetSocketContext_s *ptTelnetSocketContext,
        unsigned __int8 *pCommand,
        int nParameterLength)
{
  #pragma pack(push, 1)
  union
  {
    struct { unsigned __int8 nChar; };
    struct { char igi2_o1[1]; int iOffset; };
    struct { char igi2_o2[5]; unsigned __int16 nWidth; };
    struct { char igi2_o3[9]; unsigned __int16 nHeight; };
    struct { char igi2_o4[13]; unsigned __int8 zValue[8192]; };
    char igi2_extent[8205];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  unsigned __int8 v3; // bl
  int v4; // eax
  u_short v6; // di
  u_short v7; // ax
  int v8; // ebx
  unsigned __int8 *v9; // esi
  unsigned __int8 v10; // cl
  unsigned __int8 v11; // cl

  if ( nParameterLength <= 0 )
    return nParameterLength;
  v3 = *pCommand;
  if ( *pCommand == 0xFF )
  {
    if ( nParameterLength <= 1 )
      return nParameterLength;
    igi2_frame.nChar = pCommand[1];
    v3 = igi2_frame.nChar;
    igi2_frame.iOffset = 2;
    if ( igi2_frame.nChar != 0xFF )
      return nParameterLength;
  }
  else
  {
    igi2_frame.nChar = *pCommand;
    igi2_frame.iOffset = 1;
  }
  v4 = 0;
  while ( stru_682610[v4].eOption != v3 )
  {
    if ( (unsigned int)++v4 >= 0xB )
    {
      v4 = 0;
      break;
    }
  }
  TelnetHost_printf((int)ptTelnetSocketContext, "%s ", stru_682610[v4].zName);
  if ( v3 == 24 )
  {
    if ( ReadCharacterFromStream(&igi2_frame.nChar, &igi2_frame.iOffset, pCommand, nParameterLength) == false )
      return nParameterLength;
    if ( igi2_frame.nChar != 1 )
    {
      if ( !igi2_frame.nChar )
      {
        v8 = igi2_frame.iOffset;
        v9 = igi2_frame.zValue;
        while ( nParameterLength > v8 )
        {
          v10 = pCommand[v8];
          if ( v10 == 0xFF )
          {
            if ( nParameterLength <= v8 + 1 )
              return nParameterLength;
            v11 = pCommand[v8 + 1];
            v8 += 2;
            if ( v11 != 0xFF )
            {
              if ( v11 != 0xF0 )
                return nParameterLength;
              TelnetHost_printf((int)ptTelnetSocketContext, "IS %s ", (char *)igi2_frame.zValue);
              return v8;
            }
            *v9++ = -1;
            *v9 = 0;
          }
          else
          {
            *v9 = v10;
            ++v8;
            *++v9 = 0;
          }
        }
      }
      return nParameterLength;
    }
    TelnetHost_printf((int)ptTelnetSocketContext, "SEND ");
    return nParameterLength;
  }
  else
  {
    if ( v3 != 31 )
    {
      TelnetHost_printf((int)ptTelnetSocketContext, "UNHANDLED OPTION: %02X ", v3);
      return nParameterLength;
    }
    if ( ReadCharacterFromStream((unsigned __int8 *)&igi2_frame.nWidth, &igi2_frame.iOffset, pCommand, nParameterLength) == false
      || ReadCharacterFromStream((unsigned __int8 *)&igi2_frame.nWidth + 1, &igi2_frame.iOffset, pCommand, nParameterLength) == false
      || ReadCharacterFromStream((unsigned __int8 *)&igi2_frame.nHeight, &igi2_frame.iOffset, pCommand, nParameterLength) == false
      || ReadCharacterFromStream((unsigned __int8 *)&igi2_frame.nHeight + 1, &igi2_frame.iOffset, pCommand, nParameterLength) == false
      || ReadCharacterFromStream(&igi2_frame.nChar, &igi2_frame.iOffset, pCommand, nParameterLength)
      || igi2_frame.nChar != 0xF0 )
    {
      return nParameterLength;
    }
    v6 = ntohs(igi2_frame.nWidth);
    v7 = ntohs(igi2_frame.nHeight);
    TelnetHost_printf((int)ptTelnetSocketContext, "%dx%d ", v6, v7);
    return igi2_frame.iOffset;
  }
}

// source: b/2/pc/pc_telnethost.c:597  [anchor-caller]
struct TelnetSocketContext_s *__cdecl ParseTelnetCommand(
        struct TelnetSocketContext_s *a1,
        int a2,
        struct TelnetSocketContext_s *ptTelnetSocketContext)
{
  struct TelnetSocketContext_s *result; // eax
  int i; // edi
  int v6; // ebp

  result = ptTelnetSocketContext;
  for ( i = 0; i < (int)ptTelnetSocketContext; result = ptTelnetSocketContext )
  {
    v6 = *(unsigned __int8 *)(i + a2);
    TelnetHost_printf((int)a1, "%s ", *((char **)&_lconv_c.decimal_point + v6));
    switch ( v6 )
    {
      case 250:
        i += ParseTelnetSubNegotiation(a1, (unsigned __int8 *)(i + 1 + a2), (int)ptTelnetSocketContext - i - 1)
           + 1;
        break;
      case 251:
        i += ParseTelnetWill(a1, (unsigned __int8 *)(i + 1 + a2)) + 1;
        break;
      case 252:
        i += ParseTelnetWont((int)ptTelnetSocketContext - i - 1, a1, (unsigned __int8 *)(i + 1 + a2)) + 1;
        break;
      case 253:
        i += ParseTelnetDo(a1, (int)ptTelnetSocketContext - i - 1, (struct TelnetSocketContext_s *)(i + 1 + a2)) + 1;
        break;
      case 254:
        i += ParseTelnetDont((int)ptTelnetSocketContext - i - 1, a1, (unsigned __int8 *)(i + 1 + a2)) + 1;
        break;
      default:
        ++i;
        break;
    }
    TelnetHost_printf((int)a1, (char *)&stru_6A4CDC);
  }
  return result;
}

// source: b/2/pc/pc_telnethost.c:660  [anchor-strings]
int __cdecl TelnetHost_ReadLineFromSocket(
        char *a1,
        struct TelnetSocketContext_s *ptTelnetSocketContext,
        char *Destination,
        size_t Count)
{
  #pragma pack(push, 1)
  union
  {
    struct { unsigned int nOffset; };
    struct { char igi2_o1[4]; int err; };
    struct { char igi2_o2[8]; char *zTemp; };
    struct { char igi2_o3[12]; unsigned __int8 *pnInput; };
    struct { char igi2_o4[16]; unsigned int tSocket; };
    struct { char igi2_o5[20]; char zBuffer[8132]; };
    char igi2_extent[8152];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct TelnetSocketContext_s *v4; // ebp
  SOCKET v5; // ebx
  int nCharsInInputBuffer; // esi
  unsigned __int8 *v7; // ecx
  int v8; // ebp
  char v9; // bl
  int v10; // eax

  v4 = ptTelnetSocketContext;
  v5 = ptTelnetSocketContext->tSocket;
  igi2_frame.tSocket = ptTelnetSocketContext->tSocket;
  if ( strlen(a1) )
    send(v5, a1, strlen(a1), 0);
  igi2_frame.zTemp = igi2_frame.zBuffer;
  igi2_frame.nOffset = 0;
  while ( 1 )
  {
LABEL_4:
    if ( v4->nCharsInInputBuffer )
    {
      nCharsInInputBuffer = v4->nCharsInInputBuffer;
      igi2_frame.err = nCharsInInputBuffer;
    }
    else
    {
      igi2_frame.err = recv(v5, (char *)v4->anInputBuffer, 0x2000, 0);
      v4->pnInput = v4->anInputBuffer;
      v4->nCharsInInputBuffer = 0;
      nCharsInInputBuffer = igi2_frame.err;
    }
    if ( nCharsInInputBuffer == -1 )
      goto LABEL_41;
    if ( nCharsInInputBuffer > 0 )
      break;
    if ( !nCharsInInputBuffer )
    {
      TelnetHost_printf((int)v4, "\r\nConnection closed.\r\n");
LABEL_41:
      closesocket(v5);
      return 0;
    }
  }
  v7 = v4->pnInput;
  v8 = 0;
  for ( igi2_frame.pnInput = v7; ; v7 = igi2_frame.pnInput )
  {
    if ( nCharsInInputBuffer > v8 )
    {
      v9 = v7[v8++];
      if ( v9 != -1 )
        goto LABEL_15;
      if ( nCharsInInputBuffer > v8 )
        break;
    }
    v8 = nCharsInInputBuffer;
    v9 = -1;
LABEL_19:
    if ( v9 != 255 )
      v8 = (int)ParseTelnetCommand(
                  ptTelnetSocketContext,
                  (int)&v7[v8 - 1],
                  (struct TelnetSocketContext_s *)(nCharsInInputBuffer - (v8 - 1)))
         + v8
         - 1;
LABEL_21:
    if ( v8 >= nCharsInInputBuffer )
    {
      v5 = igi2_frame.tSocket;
      ptTelnetSocketContext->nCharsInInputBuffer = 0;
      v4 = ptTelnetSocketContext;
      goto LABEL_4;
    }
  }
  v9 = v7[v8++];
  if ( v9 != -1 )
    goto LABEL_19;
LABEL_15:
  if ( v9 == 8 )
  {
    if ( igi2_frame.nOffset )
    {
      TelnetHost_printf((int)ptTelnetSocketContext, "\b \b");
      nCharsInInputBuffer = igi2_frame.err;
      --igi2_frame.nOffset;
      --igi2_frame.zTemp;
    }
    goto LABEL_21;
  }
  if ( _mb_cur_max_6aece0 <= 1 )
    v10 = pctype_6aecec[v9] & 0x117;
  else
    v10 = isctype(v9, 279);
  if ( v10 )
    goto LABEL_33;
  if ( _mb_cur_max_6aece0 <= 1 ? pctype_6aecec[v9] & 8 : isctype(v9, 8) )
    goto LABEL_33;
  if ( v9 != 13 )
  {
    if ( v9 != 10 )
      goto LABEL_21;
LABEL_33:
    if ( v9 != 13 && v9 != 10 )
    {
      *igi2_frame.zTemp++ = v9;
      ++igi2_frame.nOffset;
    }
  }
  TelnetHost_printf((int)ptTelnetSocketContext, "%c", v9);
  if ( igi2_frame.nOffset < 0x1FC0 && v9 != 10 )
  {
    nCharsInInputBuffer = igi2_frame.err;
    goto LABEL_21;
  }
  *igi2_frame.zTemp = 0;
  strncpy(Destination, igi2_frame.zBuffer, Count);
  Destination[Count - 1] = 0;
  ptTelnetSocketContext->pnInput += v8;
  ptTelnetSocketContext->nCharsInInputBuffer = igi2_frame.err - v8;
  return 1;
}

// source: b/2/pc/pc_telnethost.c:798  [anchor-callee]
void __cdecl TelnetHost_SendLines(struct MyThreadContext_s *ptMyThreadContext)
{
  char v1; // cl
  int v2; // edi
  int v3; // eax
  char *zOutput; // ebx

  v1 = 0;
  v2 = 0;
  v3 = 0;
  if ( ptMyThreadContext->nOutputChars > 0 )
  {
    zOutput = ptMyThreadContext->zOutput;
    do
    {
      if ( *zOutput == 10 && v1 != 13 )
      {
        send(ptMyThreadContext->tTelnetSocketContext.tSocket, &ptMyThreadContext->zOutput[v3], v2 - v3, 0);
        send(ptMyThreadContext->tTelnetSocketContext.tSocket, "\r\n", 2, 0);
        v3 = (int)&zOutput[-16415 - (_DWORD)ptMyThreadContext];
      }
      v1 = *zOutput;
      ++v2;
      ++zOutput;
    }
    while ( v2 < ptMyThreadContext->nOutputChars );
  }
  if ( v3 < v2 - 1 )
    send(ptMyThreadContext->tTelnetSocketContext.tSocket, &ptMyThreadContext->zOutput[v3], v2 - v3, 0);
}

// source: b/2/pc/pc_telnethost.c:834  [anchor-strings]
enum bool __cdecl TelnetHost_AcceptClients(struct MyThreadContext_s *ptMyThreadContext)
{
  #pragma pack(push, 1)
  union
  {
    struct { unsigned int tListenerSocket; };
    struct { char igi2_o1[4]; struct sockaddr_in sin; };
    struct { char igi2_o2[20]; char zUsername[256]; };
    struct { char igi2_o3[276]; char zIP[256]; };
    struct { char igi2_o4[532]; char zPassword[256]; };
    struct { char igi2_o5[788]; char zName[1024]; };
    struct { char igi2_o6[1812]; char zCommandline[8192]; };
    char igi2_extent[10004];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct hostent *v1; // eax
  unsigned __int8 *v2; // eax
  u_short nPort; // si
  SOCKET v4; // edi
  SOCKET v5; // eax
  unsigned int v6; // eax
  char *v7; // edi
  BOOL v9; // edi
  SOCKET v10; // eax

  gethostname(igi2_frame.zName, 1024);
  v1 = gethostbyname(igi2_frame.zName);
  if ( v1 )
  {
    v2 = (unsigned __int8 *)*v1->h_addr_list;
    if ( v2 )
    {
      nPort = ptMyThreadContext->nPort;
      sprintf(igi2_frame.zIP, "%d.%d.%d.%d:%d", *v2, v2[1], v2[2], v2[3], nPort);
      v4 = socket(2, 1, 0);
      igi2_frame.tListenerSocket = v4;
      if ( v4 != -1 )
      {
        igi2_frame.sin.sin_family = 2;
        igi2_frame.sin.sin_port = htons(nPort);
        igi2_frame.sin.sin_addr.S_un.S_addr = 0;
        if ( bind(v4, (struct sockaddr *)&igi2_frame.sin, 16) != -1 && listen(v4, 5) != -1 )
        {
          TelnetHost_printf((int)ptMyThreadContext, "Listening on port: (%s) %s\n", igi2_frame.zName, igi2_frame.zIP);
          v5 = accept(v4, nullptr, nullptr);
          ptMyThreadContext->tTelnetSocketContext.tSocket = v5;
          if ( v5 != -1 )
          {
            do
            {
              if ( send(ptMyThreadContext->tTelnetSocketContext.tSocket, "IGI2 TELNET SERVER\r\n", 20, 0) != -1
                && TelnetHost_ReadLineFromSocket(
                     "username:",
                     &ptMyThreadContext->tTelnetSocketContext,
                     igi2_frame.zUsername,
                     0x100u)
                && TelnetHost_ReadLineFromSocket(
                     "password:",
                     &ptMyThreadContext->tTelnetSocketContext,
                     igi2_frame.zPassword,
                     0x100u) )
              {
                if ( TelnetHost_AuthenticateUser(igi2_frame.zUsername, igi2_frame.zPassword) )
                {
                  send(ptMyThreadContext->tTelnetSocketContext.tSocket, "Welcome, ", 9, 0);
                  send(ptMyThreadContext->tTelnetSocketContext.tSocket, igi2_frame.zUsername, strlen(igi2_frame.zUsername), 0);
                  send(ptMyThreadContext->tTelnetSocketContext.tSocket, "\r\n", 2, 0);
                  if ( TelnetHost_ReadLineFromSocket(
                         ">",
                         &ptMyThreadContext->tTelnetSocketContext,
                         igi2_frame.zCommandline,
                         0x2000u) )
                  {
                    while ( 1 )
                    {
                      WaitForSingleObject(&ptMyThreadContext->tTelnetSocketContext.hMutex, 0xFFFFFFFF);
                      if ( strlen(igi2_frame.zCommandline) + strlen(ptMyThreadContext->zInput) < 0x2000 )
                      {
                        v6 = strlen(igi2_frame.zCommandline) + 1;
                        v7 = &ptMyThreadContext->zOutput[0x1FFF];
                        while ( *++v7 )
                          ;
                        qmemcpy(v7, igi2_frame.zCommandline, v6);
                        ptMyThreadContext->isLineReady = true;
                        ptMyThreadContext->isSleep = true;
                      }
                      ReleaseMutex(&ptMyThreadContext->tTelnetSocketContext.hMutex);
                      do
                      {
                        Sleep(0x64u);
                        WaitForSingleObject(&ptMyThreadContext->tTelnetSocketContext.hMutex, 0xFFFFFFFF);
                        v9 = ptMyThreadContext->isSleep == false;
                        if ( ptMyThreadContext->nOutputChars )
                        {
                          TelnetHost_SendLines(ptMyThreadContext);
                          ptMyThreadContext->nOutputChars = 0;
                          ptMyThreadContext->zOutput[0] = 0;
                        }
                        ReleaseMutex(&ptMyThreadContext->tTelnetSocketContext.hMutex);
                      }
                      while ( !v9 );
                      if ( ptMyThreadContext->isQuit )
                        break;
                      if ( !TelnetHost_ReadLineFromSocket(
                              ">",
                              &ptMyThreadContext->tTelnetSocketContext,
                              igi2_frame.zCommandline,
                              0x2000u) )
                      {
                        v4 = igi2_frame.tListenerSocket;
                        goto LABEL_25;
                      }
                    }
                    send(ptMyThreadContext->tTelnetSocketContext.tSocket, "Bye.\r\n", 6, 0);
                    v4 = igi2_frame.tListenerSocket;
                    ptMyThreadContext->isQuit = false;
                  }
                }
                else
                {
                  send(ptMyThreadContext->tTelnetSocketContext.tSocket, "Unknown user/password\r\n", 23, 0);
                }
              }
LABEL_25:
              closesocket(ptMyThreadContext->tTelnetSocketContext.tSocket);
              TelnetHost_printf((int)ptMyThreadContext, "Listening on port: (%s) %s\n", igi2_frame.zName, igi2_frame.zIP);
              v10 = accept(v4, nullptr, nullptr);
              ptMyThreadContext->tTelnetSocketContext.tSocket = v10;
            }
            while ( v10 != -1 );
          }
        }
        closesocket(v4);
      }
    }
  }
  return false;
}

// source: b/2/pc/pc_telnethost.c:1034  [anchor-mhash]
void __cdecl TelnetHost_DebugConsolePrintCallback(char *zString, void *pxContext)
{
  unsigned int v2; // edx
  char *v3; // edi

  if ( strlen(zString) + strlen((char *)pxContext + 16416) < 0x2000 )
  {
    v2 = strlen(zString) + 1;
    v3 = (char *)pxContext + 16415;
    while ( *++v3 )
      ;
    qmemcpy(v3, zString, v2);
    *((_DWORD *)pxContext + 4103) = strlen((char *)pxContext + 16416);
  }
}

// source: b/2/pc/pc_telnethost.c:1057  [anchor-caller]
unsigned int __stdcall TelnetHost_ListenerThread(void *pxContext)
{
  return TelnetHost_AcceptClients((struct MyThreadContext_s *)pxContext);
}

// source: b/2/pc/pc_telnethost.c:1073  [anchor-refs]
void __cdecl TelnetHost_CreateListenerThread(struct MyThreadContext_s *ptMyThreadContext)
{
  HANDLE MutexA; // eax
  unsigned int dwThreadID; // [esp+4h] [ebp-4h] BYREF

  memset(ptMyThreadContext, 0, sizeof(struct MyThreadContext_s));
  ptMyThreadContext->nPort = 23;
  ptMyThreadContext->hThread = (void *)-1;
  ptMyThreadContext->tTelnetSocketContext.hMutex = (void *)-1;
  MutexA = CreateMutexA(nullptr, 0, nullptr);
  ptMyThreadContext->tTelnetSocketContext.hMutex = MutexA;
  if ( MutexA != (HANDLE)-1 )
  {
    ptMyThreadContext->hThread = CreateThread(nullptr, 0, TelnetHost_ListenerThread, ptMyThreadContext, 0, &dwThreadID);
    ptMyThreadContext->isRunning = true;
  }
}

// source: b/2/pc/pc_telnethost.c:1104  [anchor-callee]
void __cdecl TelnetHost_TerminateListenerThread(struct MyThreadContext_s *ptMyThreadContext)
{
  void *hThread; // eax
  unsigned int dwExitCode; // [esp+4h] [ebp-4h] BYREF

  hThread = ptMyThreadContext->hThread;
  if ( hThread != (void *)-1 )
  {
    CloseHandle(hThread);
    if ( GetExitCodeThread(ptMyThreadContext->hThread, &dwExitCode) )
    {
      while ( dwExitCode == 259 && GetExitCodeThread(ptMyThreadContext->hThread, &dwExitCode) )
        ;
    }
  }
  if ( ptMyThreadContext->tTelnetSocketContext.hMutex != (void *)-1 )
    CloseHandle(ptMyThreadContext->tTelnetSocketContext.hMutex);
  ptMyThreadContext->isRunning = false;
}

// source: b/2/pc/pc_telnethost.c:1143  [anchor-hash]
void __cdecl TelnetHost_PollListenerThread(struct MyThreadContext_s *ptMyThreadContext)
{
  struct DebugConsole_s *v1; // eax

  if ( WaitForSingleObject(ptMyThreadContext->tTelnetSocketContext.hMutex, 0) != -1 )
  {
    DebugConsole_PushActiveConsole(TelnetHost_tConsoleID);
    if ( ptMyThreadContext->tTelnetSocketContext.nCharsInScreenBuffer )
    {
      DebugConsole_printf(
        (char *)&stru_6A4CDC.tDebugConsoleLineList.ptMiddle,
        ptMyThreadContext->tTelnetSocketContext.zScreenBuffer);
      ptMyThreadContext->tTelnetSocketContext.nCharsInScreenBuffer = 0;
    }
    if ( ptMyThreadContext->isLineReady )
    {
      DebugConsoleCommand_Register(
        "quit",
        (char *)&g_zInitialValue,
        "terminate connection",
        (void (__cdecl *)(int, char **, void *))TelnetHost_ParseQuit,
        ptMyThreadContext);
      v1 = DebugConsole_ptActiveDebugConsole;
      DebugConsole_ptActiveDebugConsole->pfDebugConsolePrintCallback = TelnetHost_DebugConsolePrintCallback;
      v1->pxPrintCallbackContext = ptMyThreadContext;
      DebugConsoleCommand_Parse(ptMyThreadContext->zInput);
      DebugConsoleCommand_Remove("quit");
      DebugConsole_ptActiveDebugConsole->pfDebugConsolePrintCallback = nullptr;
      ptMyThreadContext->zInput[0] = 0;
      ptMyThreadContext->isLineReady = false;
      ptMyThreadContext->isSleep = false;
    }
    DebugConsole_PopActiveConsole();
    ReleaseMutex(ptMyThreadContext->tTelnetSocketContext.hMutex);
  }
}

// source: b/2/pc/pc_telnethost.c:1183  [size]
void __cdecl TelnetHost_Update()
{
  if ( tMyThreadContext.isRunning )
    TelnetHost_PollListenerThread(&tMyThreadContext);
}

// source: b/2/pc/pc_telnethost.c:1199  [size]
void __cdecl TelnetHost_CreateThread()
{
  if ( tMyThreadContext.isRunning == false )
    TelnetHost_CreateListenerThread(&tMyThreadContext);
}

// source: b/2/pc/pc_telnethost.c:1215  [size]
void __cdecl TelnetHost_StopThread()
{
  if ( tMyThreadContext.isRunning )
    TelnetHost_TerminateListenerThread(&tMyThreadContext);
}

// source: b/2/pc/pc_telnethost.c:1231  [anchor-hash]
void __cdecl TelnetHost_Open()
{
  TelnetHost_tConsoleID = DebugConsole_Alloc("telnetd", 100);
  DebugConsole_PushActiveConsole(TelnetHost_tConsoleID);
  DebugConsoleCommand_Echo(false);
  DebugConsole_PopActiveConsole();
}

// source: b/2/pc/pc_telnethost.c:1264  [anchor-hash]
void __cdecl TelnetHost_Close()
{
  if ( tMyThreadContext.isRunning )
    TelnetHost_TerminateListenerThread(&tMyThreadContext);
  DebugConsole_DeAlloc(TelnetHost_tConsoleID);
}
