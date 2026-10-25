/* j/0/network/gqueryreporting.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/network/gqueryreporting.c:159  [anchor-callee]
struct qr_implementation_s **__cdecl init_qrec(
        struct qr_implementation_s **qrec,
        int qport,
        unsigned int hbsock,
        unsigned int querysock,
        char *gamename,
        char *secret_key,
        void (__cdecl *qr_basic_callback__)(char *, int, void *),
        void (__cdecl *qr_info_callback)(char *, int, void *),
        void (__cdecl *qr_rules_callback)(char *, int, void *),
        void (__cdecl *qr_players_callback)(char *, int, void *),
        void *userdata)
{
  struct qr_implementation_s **result; // eax

  if ( qrec )
  {
    result = (struct qr_implementation_s **)malloc(0x10Cu);
    *qrec = (struct qr_implementation_s *)result;
  }
  else
  {
    result = (struct qr_implementation_s **)&stru_6B0500;
  }
  strcpy((char *)result + 8, gamename);
  strcpy((char *)result + 72, secret_key);
  result[57] = (struct qr_implementation_s *)qport;
  result[1] = (struct qr_implementation_s *)hbsock;
  *result = (struct qr_implementation_s *)querysock;
  result[55] = (struct qr_implementation_s *)1;
  *((_BYTE *)result + 232) = 1;
  result[66] = (struct qr_implementation_s *)userdata;
  result[50] = (struct qr_implementation_s *)qr_basic_callback__;
  result[51] = (struct qr_implementation_s *)qr_info_callback;
  result[54] = nullptr;
  result[56] = nullptr;
  result[53] = (struct qr_implementation_s *)qr_players_callback;
  result[52] = (struct qr_implementation_s *)qr_rules_callback;
  result[63] = nullptr;
  return result;
}

// source: j/0/network/gqueryreporting.c:195  [anchor-strings]
// positive sp value has been detected, the output may be wrong!
int __cdecl qr_init(
        struct qr_implementation_s **qrec,
        char *ip,
        int baseport,
        char *gamename,
        char *secret_key,
        void (__cdecl *qr_basic_callback__)(char *, int, void *),
        void (__cdecl *qr_info_callback)(char *, int, void *),
        void (__cdecl *qr_rules_callback)(char *, int, void *),
        void (__cdecl *qr_players_callback)(char *, int, void *),
        void *userdata,
        int ltcg_ebx)
{
  #pragma pack(push, 1)
  union
  {
    struct { u_short v16; };
    struct { char igi2_o1[20]; int v17; };
    struct { char igi2_o2[24]; struct sockaddr v18; };
    struct { char igi2_o3[40]; int v19; };
    char igi2_extent[444];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  SOCKET v11; // ebp
  struct hostent *v12; // eax
  u_long v13; // eax
  struct qr_implementation_s **v15; // esi

  while ( 1 )
  {
    igi2_frame.v18.sa_family = 2;
    *(_WORD *)igi2_frame.v18.sa_data = htons(igi2_frame.v16);
    if ( ip )
    {
      *(_DWORD *)&igi2_frame.v18.sa_data[2] = inet_addr(ip);
      if ( *(_DWORD *)&igi2_frame.v18.sa_data[2] == -1 )
      {
        if ( strcmp(ip, "255.255.255.255") )
        {
          v12 = gethostbyname(ip);
          if ( v12 )
            *(_DWORD *)&igi2_frame.v18.sa_data[2] = **(_DWORD **)v12->h_addr_list;
        }
      }
    }
    else
    {
      *(_DWORD *)&igi2_frame.v18.sa_data[2] = 0;
    }
    v13 = htonl(0x7F000001u);
    if ( *(_DWORD *)&igi2_frame.v18.sa_data[2] == v13 )
      *(_DWORD *)&igi2_frame.v18.sa_data[2] = 0;
    if ( !bind(v11, &igi2_frame.v18, 16) )
      break;
    if ( ++ltcg_ebx >= igi2_frame.v19 )
      return 2;
  }
  if ( !ltcg_ebx )
  {
    igi2_frame.v17 = 16;
    if ( getsockname(v11, &igi2_frame.v18, &igi2_frame.v17) )
      return 2;
    ltcg_ebx = ntohs(*(u_short *)igi2_frame.v18.sa_data);
  }
  v15 = qrec;
  init_qrec(
    qrec,
    ltcg_ebx,
    v11,
    v11,
    gamename,
    secret_key,
    qr_basic_callback__,
    qr_info_callback,
    qr_rules_callback,
    qr_players_callback,
    userdata);
  if ( !qrec )
    v15 = &current_rec;
  return do_connect(v11, qr_hostname, 27900, &(*v15)->hbaddr);
}

// source: j/0/network/gqueryreporting.c:299  [anchor-caller]
void __cdecl qr_check_queries(struct qr_implementation_s *qrec)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct timeval timeout; };
    struct { char igi2_o1[8]; int saddrlen; };
    struct { char igi2_o2[12]; struct sockaddr_in saddr; };
    struct { char igi2_o3[28]; struct fd_set set; };
    char igi2_extent[288];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int qport; // eax
  int i; // eax
  char *v3; // eax
  int v4; // edx

  qport = qrec->qport;
  igi2_frame.saddrlen = 16;
  igi2_frame.timeout.tv_sec = 0;
  igi2_frame.timeout.tv_usec = 0;
  if ( qport )
  {
    igi2_frame.set.fd_array[0] = qrec->querysock;
    igi2_frame.set.fd_count = 1;
    for ( i = select(64, &igi2_frame.set, nullptr, nullptr, &igi2_frame.timeout); i != -1; i = select(64, &igi2_frame.set, nullptr, nullptr, &igi2_frame.timeout) )
    {
      if ( !i )
        break;
      v3 = (char *)recvfrom(qrec->querysock, (char *)&g_qrec, 255, 0, (struct sockaddr *)&igi2_frame.saddr, &igi2_frame.saddrlen);
      if ( v3 != (char *)-1 )
      {
        *((_BYTE *)&g_qrec.querysock + (_DWORD)v3) = 0;
        qr_parse_query(&g_qrec, v3, v4, (struct sockaddr *)&igi2_frame.saddr, (int)qrec);
      }
    }
  }
}

// source: j/0/network/gqueryreporting.c:331  [anchor-hash]
void __cdecl qr_check_send_heartbeat(struct qr_implementation_s *qrec)
{
  DWORD TickCount; // eax
  unsigned int lastheartbeat; // ecx
  char v4; // al
  bool v5; // sf

  TickCount = GetTickCount();
  if ( qrec->hbsock != -1 )
  {
    lastheartbeat = qrec->lastheartbeat;
    if ( TickCount - lastheartbeat <= 0x493E0 && lastheartbeat && TickCount >= lastheartbeat )
    {
      if ( qrec->no_query > 0 && TickCount - lastheartbeat > 0x7530 )
      {
        send_heartbeat(qrec, 0);
        v4 = qrec->no_query + 1;
        v5 = (char)(qrec->no_query - 9) < 0;
        qrec->no_query = v4;
        if ( !(v5 ^ __OFSUB__(v4, 10) | (v4 == 10)) )
          qrec->no_query = 0;
      }
    }
    else
    {
      send_heartbeat(qrec, 0);
    }
  }
}

// source: j/0/network/gqueryreporting.c:352  [anchor-hash]
struct qr_implementation_s *__cdecl qr_send_statechanged(struct qr_implementation_s *qrec)
{
  struct qr_implementation_s *v1; // esi
  struct qr_implementation_s *result; // eax

  v1 = qrec;
  if ( !qrec )
    v1 = current_rec;
  send_heartbeat(v1, 1);
  return result;
}

// source: j/0/network/gqueryreporting.c:360  [anchor-hash]
struct qr_implementation_s *__cdecl qr_send_exiting(struct qr_implementation_s *qrec)
{
  struct qr_implementation_s *v1; // esi
  struct qr_implementation_s *result; // eax

  v1 = qrec;
  if ( !qrec )
    v1 = current_rec;
  send_heartbeat(v1, 2);
  return result;
}

// source: j/0/network/gqueryreporting.c:368  [anchor-hash]
struct qr_implementation_s *__cdecl qr_shutdown(struct qr_implementation_s *qrec)
{
  struct qr_implementation_s *v1; // esi
  unsigned int hbsock; // eax

  v1 = qrec;
  if ( !qrec )
    v1 = current_rec;
  if ( v1->querysock != -1 && v1->qport )
    closesocket(v1->querysock);
  hbsock = v1->hbsock;
  if ( hbsock != -1 && hbsock != v1->querysock )
    closesocket(v1->hbsock);
  v1->hbsock = -1;
  v1->querysock = -1;
  v1->lastheartbeat = 0;
  if ( v1 != &stru_6B0500 )
    free(v1);
  return (struct qr_implementation_s *)WSACleanup();
}

// source: j/0/network/gqueryreporting.c:392  [anchor-callee]
int __cdecl do_connect(unsigned int sock, char *addr, int port, struct sockaddr_in *hbaddr)
{
  struct hostent *v4; // eax

  hbaddr->sin_family = 2;
  hbaddr->sin_port = htons(port);
  if ( addr )
    hbaddr->sin_addr.S_un.S_addr = inet_addr(addr);
  else
    hbaddr->sin_addr.S_un.S_addr = 0;
  if ( hbaddr->sin_addr.S_un.S_addr == -1 )
  {
    if ( strcmp(addr, "255.255.255.255") )
    {
      v4 = gethostbyname(addr);
      if ( v4 )
        hbaddr->sin_addr.S_un.S_addr = **(_DWORD **)v4->h_addr_list;
    }
  }
  return 0;
}

// source: j/0/network/gqueryreporting.c:411  [anchor-mhash]
int __cdecl get_sockaddrin(
        char *host,
        int port,
        struct sockaddr_in *saddr,
        struct hostent **savehent)
{
  int result; // eax

  saddr->sin_family = 2;
  saddr->sin_port = htons(port);
  if ( host )
    saddr->sin_addr.S_un.S_addr = inet_addr(host);
  else
    saddr->sin_addr.S_un.S_addr = 0;
  if ( saddr->sin_addr.S_un.S_addr != -1 || !strcmp(host, "255.255.255.255") )
  {
    result = (int)host;
  }
  else
  {
    result = (int)gethostbyname(host);
    if ( !result )
      return result;
    saddr->sin_addr.S_un.S_addr = ***(_DWORD ***)(result + 12);
  }
  if ( savehent )
    *savehent = (struct hostent *)result;
  return 1;
}

// source: j/0/network/gqueryreporting.c:440  [anchor-callee]
char *__cdecl value_for_key(char *s, char *key)
{
  #pragma pack(push, 1)
  union
  {
    struct { char v12; };
    struct { char igi2_o1[1]; char keyspec[256]; };
    char igi2_extent[257];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  unsigned int v2; // eax
  char *v3; // edi
  char *v5; // edi
  char *result; // eax
  char *v8; // eax
  char v9; // cl
  char *v10; // esi
  char *i; // edx

  strcpy(igi2_frame.keyspec, "\\");
  memset(&igi2_frame.keyspec[2], 0, 254);
  dword_7BD0F00 ^= 1u;
  v2 = strlen(key) + 1;
  v3 = &igi2_frame.v12;
  while ( *++v3 )
    ;
  qmemcpy(v3, key, v2);
  v5 = &igi2_frame.v12;
  while ( *++v5 )
    ;
  *(_WORD *)v5 = unk_6855FC;
  result = strstr(s, igi2_frame.keyspec);
  if ( result )
  {
    v8 = &result[strlen(igi2_frame.keyspec)];
    v9 = *v8;
    v10 = (char *)&unk_7BD0F08 + 256 * dword_7BD0F00;
    for ( i = v10; v9; ++v8 )
    {
      if ( v9 == 92 )
        break;
      *i = v9;
      v9 = v8[1];
      ++i;
    }
    *i = 0;
    return v10;
  }
  return result;
}

// source: j/0/network/gqueryreporting.c:466  [size]
unsigned __int8 *__cdecl swap_byte(unsigned __int8 *a, unsigned __int8 *b)
{
  unsigned __int8 v2; // dl

  v2 = *a;
  *a = *b;
  *b = v2;
  return b;
}

// source: j/0/network/gqueryreporting.c:475  [size]
unsigned __int8 __cdecl encode_ct(unsigned __int8 c)
{
  if ( c < 0x1Au )
    return c + 65;
  if ( c < 0x34u )
    return c + 71;
  if ( c < 0x3Eu )
    return c - 4;
  if ( c == 62 )
    return 43;
  return c != 63 ? 0 : 0x2F;
}

// source: j/0/network/gqueryreporting.c:486  [anchor-callee]
void __cdecl gs_encode(unsigned __int8 *ins, int size, unsigned __int8 *result)
{
  int v3; // ebp
  int v4; // edi
  int i; // eax
  int j; // ecx
  unsigned __int8 v8; // al
  unsigned __int8 v9; // al
  unsigned __int8 kwart[4]; // [esp+10h] [ebp-4h]

  v3 = size;
  v4 = 0;
  while ( v4 < v3 )
  {
    for ( i = 0; i <= 2; ++i )
    {
      if ( v4 >= v3 )
        *((_BYTE *)&size + i) = 0;
      else
        *((_BYTE *)&size + i) = *ins++;
      ++v4;
    }
    kwart[0] = (unsigned __int8)size >> 2;
    kwart[1] = (BYTE1(size) >> 4) + 16 * (size & 3);
    kwart[2] = (BYTE2(size) >> 6) + 4 * (BYTE1(size) & 0xF);
    kwart[3] = BYTE2(size) & 0x3F;
    for ( j = 0; j <= 3; ++j )
    {
      v8 = kwart[j];
      if ( v8 >= 0x1Au )
      {
        if ( v8 >= 0x34u )
        {
          if ( v8 >= 0x3Eu )
          {
            if ( v8 == 62 )
              v9 = 43;
            else
              v9 = v8 != 63 ? 0 : 0x2F;
          }
          else
          {
            v9 = v8 - 4;
          }
        }
        else
        {
          v9 = v8 + 71;
        }
      }
      else
      {
        v9 = v8 + 65;
      }
      *result++ = v9;
    }
  }
  *result = 0;
}

// source: j/0/network/gqueryreporting.c:507  [anchor-callee]
int __cdecl gs_encrypt(unsigned __int8 *key, int key_len, unsigned __int8 *buffer_ptr, int buffer_len)
{
  #pragma pack(push, 1)
  union
  {
    struct { unsigned __int8 v18; };
    struct { char igi2_o1[1]; unsigned __int8 state[256]; };
    char igi2_extent[257];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v5; // eax
  unsigned __int8 *v6; // ecx
  int v7; // edx
  unsigned __int8 v8; // al
  unsigned __int8 *v9; // ecx
  int v10; // esi
  unsigned __int8 v11; // bl
  int result; // eax
  int v13; // ebp
  int v14; // esi
  int v15; // edi
  unsigned __int8 v16; // dl
  unsigned __int8 v17; // cl

  v5 = 0;
  v6 = igi2_frame.state;
  do
    *v6++ = v5++;
  while ( (__int16)v5 < 256 );
  LOBYTE(v7) = 0;
  v8 = 0;
  v9 = igi2_frame.state;
  v10 = 256;
  do
  {
    v11 = key[(unsigned __int8)v7] + v8 + *v9;
    v7 = ((unsigned __int8)v7 + 1) % key_len;
    v8 = v11;
    igi2_frame.v18 = *v9;
    *v9++ = igi2_frame.state[v11];
    --v10;
    igi2_frame.state[v11] = igi2_frame.v18;
  }
  while ( v10 );
  result = buffer_len;
  v13 = 0;
  if ( buffer_len > 0 )
  {
    LOBYTE(v14) = 0;
    LOBYTE(v15) = 0;
    result = 0;
    do
    {
      v16 = buffer_ptr[result];
      v14 = (unsigned __int8)(v16 + v14 + 1);
      v15 = (unsigned __int8)(v15 + igi2_frame.state[v14]);
      v17 = igi2_frame.state[v14];
      igi2_frame.state[v14] = igi2_frame.state[v15];
      igi2_frame.state[v15] = v17;
      ++v13;
      buffer_ptr[result] = v16 ^ igi2_frame.state[(unsigned __int8)(igi2_frame.state[v15] + igi2_frame.state[v14])];
      result = (__int16)v13;
    }
    while ( (__int16)v13 < buffer_len );
  }
  return result;
}

// source: j/0/network/gqueryreporting.c:538  [anchor-strings]
void __cdecl packet_send(struct qr_implementation_s *qrec, struct sockaddr *addr, char *buffer)
{
  #pragma pack(push, 1)
  union
  {
    struct { int queryid; };
    struct { char igi2_o1[4]; int v4; };
    struct { char igi2_o2[24]; char keyvalue[80]; };
    char igi2_extent[104];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)

  if ( strlen(buffer) )
  {
    igi2_frame.v4 = qrec->packetnumber + 1;
    igi2_frame.queryid = qrec->queryid;
    qrec->packetnumber = igi2_frame.v4;
    sprintf(igi2_frame.keyvalue, "\\queryid\\%d.%d", igi2_frame.queryid, igi2_frame.v4);
    strcat(buffer, igi2_frame.keyvalue);
    sendto(qrec->querysock, buffer, strlen(buffer), 0, addr, 16);
    *buffer = 0;
  }
}

// source: j/0/network/gqueryreporting.c:554  [anchor-caller]
void __cdecl buffer_send(struct qr_implementation_s *qrec, struct sockaddr *sender, char *buffer, char *newdata)
{
  int v4; // ebp
  char *v5; // edi
  char *v6; // eax
  char *v7; // esi
  int i; // ecx

  v4 = 0;
  v5 = newdata;
  if ( strlen(buffer) + strlen(newdata) < 0x546 )
  {
LABEL_11:
    strcat(buffer, v5);
  }
  else
  {
    while ( strlen(v5) > 0x546 )
    {
      v6 = v5;
      v7 = v5;
      for ( i = 0; i < 1350; ++i )
      {
        if ( *v6 == 92 )
        {
          if ( !(v4 % 2) )
            v7 = v6;
          ++v4;
        }
        ++v6;
      }
      if ( v7 == v5 )
        return;
      *v7 = 0;
      buffer_send(qrec, sender, buffer, v5);
      *v7 = 92;
      v5 = v7;
      v4 = 0;
      if ( strlen(buffer) + strlen(v7) < 0x546 )
        goto LABEL_11;
    }
    packet_send(qrec, sender, buffer);
    strcpy(buffer, v5);
  }
}

// source: j/0/network/gqueryreporting.c:593  [anchor-callee]
void __cdecl send_basic(struct qr_implementation_s *qrec, struct sockaddr *sender, char *outbuf)
{
  char keyvalue[1400]; // [esp+8h] [ebp-578h] BYREF

  memset(keyvalue, 0, sizeof(keyvalue));
  qrec->qr_basic_callback(keyvalue, 1400, (void *)qrec[1].hbsock);
  buffer_send(qrec, sender, outbuf, keyvalue);
}

// source: j/0/network/gqueryreporting.c:603  [anchor-callee]
void __cdecl send_info(struct qr_implementation_s *qrec, struct sockaddr *sender, char *outbuf)
{
  char keyvalue[1400]; // [esp+8h] [ebp-578h] BYREF

  memset(keyvalue, 0, sizeof(keyvalue));
  qrec->qr_info_callback(keyvalue, 1400, (void *)qrec[1].hbsock);
  buffer_send(qrec, sender, outbuf, keyvalue);
}

// source: j/0/network/gqueryreporting.c:614  [anchor-callee]
void __cdecl send_rules(struct qr_implementation_s *qrec, struct sockaddr *sender, char *outbuf)
{
  char keyvalue[1400]; // [esp+8h] [ebp-578h] BYREF

  memset(keyvalue, 0, sizeof(keyvalue));
  qrec->qr_rules_callback(keyvalue, 1400, (void *)qrec[1].hbsock);
  buffer_send(qrec, sender, outbuf, keyvalue);
}

// source: j/0/network/gqueryreporting.c:625  [anchor-callee]
void __cdecl send_players(struct qr_implementation_s *qrec, struct sockaddr *sender, char *outbuf)
{
  char keyvalue[1400]; // [esp+8h] [ebp-578h] BYREF

  memset(keyvalue, 0, sizeof(keyvalue));
  qrec->qr_players_callback(keyvalue, 1400, (void *)qrec[1].hbsock);
  buffer_send(qrec, sender, outbuf, keyvalue);
}

// source: j/0/network/gqueryreporting.c:637  [anchor-strings]
void __cdecl send_echo(struct qr_implementation_s *qrec, struct sockaddr *sender, char *outbuf, char *echostr)
{
  char Buffer[1400]; // [esp+0h] [ebp-578h] BYREF

  if ( strlen(echostr) <= 0x32 )
  {
    sprintf(Buffer, "\\echoresponse\\%s", echostr);
    buffer_send(qrec, sender, outbuf, Buffer);
  }
}

// source: j/0/network/gqueryreporting.c:650  [anchor-strings]
char *__cdecl send_final(
        struct qr_implementation_s *qrec,
        struct sockaddr *sender,
        char *outbuf,
        char *validation)
{
  #pragma pack(push, 1)
  union
  {
    struct { unsigned __int8 key_len[128]; };
    struct { char igi2_o1[128]; char Buffer[256]; };
    struct { char igi2_o2[384]; unsigned __int8 result[200]; };
    char igi2_extent[584];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v5; // esi
  int v6; // edx
  char v7; // cl
  struct sockaddr *v8; // esi

  if ( *validation )
  {
    v5 = strlen(validation);
    if ( v5 > 128 )
      return validation;
    v6 = igi2_frame.key_len - (unsigned __int8 *)validation;
    do
    {
      v7 = *validation;
      validation[v6] = *validation;
      ++validation;
    }
    while ( v7 );
    gs_encrypt((unsigned __int8 *)qrec->secret_key, strlen(qrec->secret_key), igi2_frame.key_len, v5);
    gs_encode(igi2_frame.key_len, v5, igi2_frame.result);
    sprintf(igi2_frame.Buffer, "\\validate\\%s\\weight\\%d", (char *)igi2_frame.result, qrec[1].querysock);
    v8 = sender;
    buffer_send(qrec, sender, outbuf, igi2_frame.Buffer);
  }
  else
  {
    v8 = sender;
  }
  sprintf(igi2_frame.Buffer, "\\final\\");
  buffer_send(qrec, v8, outbuf, igi2_frame.Buffer);
  packet_send(qrec, v8, outbuf);
  return validation;
}

// source: j/0/network/gqueryreporting.c:676  [anchor-strings]
void __cdecl qr_parse_query(
        struct qr_implementation_s *qrec,
        char *query,
        int len,
        struct sockaddr *sender,
        int ltcg_eax)
{
  #pragma pack(push, 1)
  union
  {
    struct { int v17; };
    struct { char igi2_o1[4]; char **v18; };
    struct { char igi2_o2[8]; int v19; };
    struct { char igi2_o3[12]; char validation[253]; };
    struct { char igi2_o4[265]; __int16 v21; };
    struct { char igi2_o5[267]; char v22; };
    struct { char igi2_o6[268]; char v23[1397]; };
    struct { char igi2_o7[1665]; __int16 v24; };
    struct { char igi2_o8[1667]; char v25; };
    char igi2_extent[1668];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct qr_implementation_s *v5; // ebx
  int v6; // edi
  struct qr_implementation_s *v7; // esi
  void (__cdecl *cdkeyprocess)(char *, int, struct sockaddr *); // ebx
  char no_query; // al
  DWORD TickCount; // ecx
  unsigned int querysock; // eax
  unsigned int v12; // edx
  unsigned int v13; // eax
  char *v14; // eax
  char *v15; // edx
  char v16; // cl

  v5 = (struct qr_implementation_s *)ltcg_eax;
  memset(igi2_frame.v23, 0, sizeof(igi2_frame.v23));
  igi2_frame.v24 = 0;
  igi2_frame.v25 = 0;
  memset(igi2_frame.validation, 0, sizeof(igi2_frame.validation));
  igi2_frame.v21 = 0;
  igi2_frame.v22 = 0;
  v6 = 0;
  igi2_frame.v17 = 0;
  if ( !ltcg_eax )
    v5 = current_rec;
  v7 = qrec;
  if ( LOBYTE(qrec->querysock) == 59 )
  {
    cdkeyprocess = v5->cdkeyprocess;
    if ( cdkeyprocess )
      cdkeyprocess((char *)qrec, (int)query, sender);
  }
  else
  {
    no_query = v5->no_query;
    ++v5->queryid;
    v5->packetnumber = 0;
    if ( no_query > 0 )
      v5->no_query = 0;
    TickCount = GetTickCount();
    querysock = v5[1].querysock;
    v12 = (150 * (TickCount - (unsigned int)v5->udata) + 500) / 0x3E8;
    if ( v12 <= querysock )
      v5[1].querysock = querysock - v12;
    else
      v5[1].querysock = 0;
    v13 = v5[1].querysock;
    if ( v13 <= 0x9C4 )
    {
      v5[1].querysock = v13 + 10;
      v5->udata = (void *)TickCount;
      if ( !value_for_key((char *)qrec, "queryid") )
      {
        igi2_frame.v19 = 0;
        igi2_frame.v18 = (char **)&unk_6B04E4;
        while ( igi2_frame.v17 < 4 )
        {
          v14 = value_for_key((char *)v7, *igi2_frame.v18);
          if ( v14 )
          {
            ++igi2_frame.v17;
            switch ( v6 )
            {
              case 0:
                send_echo(v5, sender, igi2_frame.v23, v14);
                break;
              case 1:
                send_basic(v5, sender, igi2_frame.v23);
                send_info(v5, sender, igi2_frame.v23);
                send_rules(v5, sender, igi2_frame.v23);
                send_players(v5, sender, igi2_frame.v23);
                v6 = igi2_frame.v19;
                igi2_frame.v17 = 4;
                break;
              case 2:
                send_basic(v5, sender, igi2_frame.v23);
                break;
              case 3:
                send_info(v5, sender, igi2_frame.v23);
                break;
              case 4:
                send_rules(v5, sender, igi2_frame.v23);
                break;
              case 5:
                send_players(v5, sender, igi2_frame.v23);
                break;
              case 6:
                v15 = (char *)(igi2_frame.validation - v14);
                do
                {
                  v16 = *v14;
                  v14[(_DWORD)v15] = *v14;
                  ++v14;
                }
                while ( v16 );
                break;
              default:
                break;
            }
          }
          ++v6;
          ++igi2_frame.v18;
          igi2_frame.v19 = v6;
          if ( v6 + 1 > 7 )
            break;
          v7 = qrec;
        }
        send_final(v5, sender, igi2_frame.v23, igi2_frame.validation);
      }
    }
    else
    {
      sendto(v5->querysock, "\\f\\", 3, 0, sender, 16);
    }
  }
}

void __cdecl sub_5D7310(int a1, struct qr_implementation_s *a2, char *a3, struct sockaddr *a4)
{
  qr_parse_query(a2, a3, a1, a4, 0);
}

// source: j/0/network/gqueryreporting.c:757  [anchor-strings]
void __cdecl send_heartbeat(struct qr_implementation_s *qrec, int statechanged)
{
  char buf[256]; // [esp+0h] [ebp-100h] BYREF

  sprintf(buf, "\\heartbeat\\%d\\gamename\\%s", qrec->qport, qrec->gamename);
  if ( statechanged )
    sprintf(&buf[strlen(buf)], "\\statechanged\\%d", statechanged);
  sendto(qrec->hbsock, buf, strlen(buf), 0, (struct sockaddr *)&qrec->hbaddr, 16);
  qrec->lastheartbeat = GetTickCount();
}
