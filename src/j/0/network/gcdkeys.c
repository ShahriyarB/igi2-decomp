/* j/0/network/gcdkeys.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/network/gcdkeys.c:130  [anchor-mhash]
int __cdecl gcd_init(int productid)
{
  #pragma pack(push, 1)
  union
  {
    struct { char defaulthost[16]; };
    struct { char igi2_o1[16]; struct WSAData WSAData; };
    char igi2_extent[416];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int result; // eax
  int v2; // eax
  char v3; // cl

  strcpy(igi2_frame.defaulthost, "key.gamespy.com");
  WSAStartup(0x101u, &igi2_frame.WSAData);
  result = init_incoming_socket();
  if ( result >= 0 )
  {
    if ( !gcd_hostname[0] )
    {
      v2 = 0;
      do
      {
        v3 = igi2_frame.defaulthost[v2];
        gcd_hostname[v2++] = v3;
      }
      while ( v3 );
    }
    get_sockaddrin__gcdkeys(gcd_hostname, 29910, &valaddr, nullptr);
    gcd_init_common(productid);
    return 0;
  }
  return result;
}

// source: j/0/network/gcdkeys.c:157  [anchor-mhash]
int __cdecl gcd_init_qr(struct qr_implementation_s *qrec, int productid)
{
  struct qr_implementation_s *v2; // esi
  unsigned int querysock; // eax

  v2 = qrec;
  if ( !qrec )
    v2 = &stru_6B0500;
  querysock = v2->querysock;
  v2->cdkeyprocess = cdkey_process_buf;
  *(_DWORD *)&valaddr.sin_family = 2;
  valaddr.sin_addr.S_un.S_addr = 0;
  *(_DWORD *)valaddr.sin_zero = 0;
  localport = -1;
  g_sock = querysock;
  *(_DWORD *)&valaddr.sin_zero[4] = 0;
  valaddr.sin_port = htons(0x74D6u);
  valaddr.sin_addr.S_un.S_addr = v2->hbaddr.sin_addr.S_un.S_addr;
  gcd_init_common(productid);
  return 0;
}

// source: j/0/network/gcdkeys.c:179  [anchor-hash]
void __cdecl gcd_shutdown()
{
  gcd_disconnect_all();
  closesocket(g_sock);
  g_sock = -1;
  WSACleanup();
}

// source: j/0/network/gcdkeys.c:189  [anchor-caller]
void __cdecl gcd_authenticate_user(
        int localid,
        unsigned int userip,
        char *challenge,
        char *response,
        void (__cdecl *authfn__)(int, int, char *, void *),
        void *instance)
{
  #pragma pack(push, 1)
  union
  {
    struct { char *errmsg; };
    struct { char igi2_o1[4]; char badcdkey_t[12]; };
    struct { char igi2_o2[16]; char keyinuse_t[16]; };
    struct { char igi2_o3[32]; char hkey[36]; };
    char igi2_extent[68];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct gsnode_s *next; // edi
  struct gsclient_s *v7; // esi
  struct gsnode_s *v8; // eax
  struct gsnode_s *v9; // ecx
  struct gsnode_s **p_next; // edx
  struct gsnode_s *v11; // ebx

  igi2_frame.errmsg = nullptr;
  strcpy(igi2_frame.badcdkey_t, "Bad CD Key");
  strcpy(igi2_frame.keyinuse_t, "CD Key in use");
  strncpy(igi2_frame.hkey, response, 0x20u);
  igi2_frame.hkey[32] = 0;
  if ( strlen(response) < 0x48 )
    igi2_frame.errmsg = goastrdup(igi2_frame.badcdkey_t);
  next = clientq.next;
  if ( clientq.next )
  {
    while ( strcmp(igi2_frame.hkey, next->client->hkey) )
    {
      next = next->next;
      if ( !next )
        goto LABEL_8;
    }
    igi2_frame.errmsg = goastrdup(igi2_frame.keyinuse_t);
  }
LABEL_8:
  v7 = (struct gsclient_s *)malloc(0x50u);
  v7->localid = localid;
  v7->instance = instance;
  v7->ip = userip;
  v7->authfn = authfn__;
  v7->errmsg = nullptr;
  v7->reqstr = nullptr;
  strcpy(v7->hkey, igi2_frame.hkey);
  v8 = (struct gsnode_s *)malloc(0xCu);
  v8->client = v7;
  v9 = &clientq;
  if ( clientq.next )
  {
    p_next = &clientq.next;
    do
    {
      v9 = *p_next;
      v11 = (*p_next)->next;
      p_next = &(*p_next)->next;
    }
    while ( v11 );
  }
  v9->next = v8;
  v8->next = nullptr;
  v8->prev = v9;
  if ( igi2_frame.errmsg )
  {
    v7->state = cs_gotnok;
    v7->errmsg = igi2_frame.errmsg;
  }
  else
  {
    send_auth_req(v7, challenge, response);
  }
}

// source: j/0/network/gcdkeys.c:244  [anchor-hash]
void __cdecl gcd_disconnect_user(int localid)
{
  struct gsnode_s *next; // esi
  struct gsnode_s *v2; // eax

  next = clientq.next;
  if ( clientq.next )
  {
    while ( next->client->localid != localid )
    {
      next = next->next;
      if ( !next )
        return;
    }
    send_disconnect_req(next->client);
    next->prev->next = next->next;
    v2 = next->next;
    if ( v2 )
      v2->prev = next->prev;
    if ( next->client->reqstr )
      free(next->client->reqstr);
    free(next->client);
    free(next);
  }
}

// source: j/0/network/gcdkeys.c:269  [anchor-hash]
void __cdecl gcd_disconnect_all()
{
  struct gsnode_s *i; // esi
  struct gsnode_s *next; // eax

  for ( i = clientq.next; clientq.next; i = clientq.next )
  {
    send_disconnect_req(i->client);
    i->prev->next = i->next;
    next = i->next;
    if ( next )
      next->prev = i->prev;
    if ( i->client->reqstr )
      free(i->client->reqstr);
    free(i->client);
    free(i);
  }
}

// source: j/0/network/gcdkeys.c:287  [anchor-mhash]
char *__cdecl gcd_getkeyhash(int localid)
{
  struct gsnode_s *next; // eax

  next = clientq.next;
  if ( !clientq.next )
    return (char *)&g_zInitialValue;
  while ( next->client->localid != localid )
  {
    next = next->next;
    if ( !next )
      return (char *)&g_zInitialValue;
  }
  return next->client->hkey;
}

// source: j/0/network/gcdkeys.c:298  [anchor-caller]
void __cdecl gcd_think()
{
  #pragma pack(push, 1)
  union
  {
    struct { char validated_t[12]; };
    struct { char igi2_o1[12]; char timeout_t[20]; };
    struct { char igi2_o2[32]; int saddrlen; };
    struct { char igi2_o3[36]; struct timeval timeout; };
    struct { char igi2_o4[44]; struct sockaddr_in saddr; };
    struct { char igi2_o5[60]; struct fd_set set; };
    char igi2_extent[320];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int i; // eax
  int v1; // eax
  struct gsnode_s *next; // ecx
  struct gsnode_s *v3; // edi
  struct gsclient_s *client; // esi
  enum gsclientstate_t state; // eax
  __int32 v6; // eax
  void **p_client; // esi
  bool v8; // zf
  struct gsnode_s *v9; // eax
  struct gsnode_s *v10; // ecx
  struct StaticTilemap_s *v11; // ecx
  DWORD TickCount; // eax
  int reqlen; // edx
  int v14; // ecx
  char *reqstr; // eax
  char *v16; // eax

  igi2_frame.saddrlen = 16;
  igi2_frame.timeout.tv_sec = 0;
  igi2_frame.timeout.tv_usec = 0;
  strcpy(igi2_frame.validated_t, "Validated");
  strcpy(igi2_frame.timeout_t, "Validation Timeout");
  if ( localport != -1 )
  {
    igi2_frame.set.fd_array[0] = g_sock;
    igi2_frame.set.fd_count = 1;
    for ( i = select(64, &igi2_frame.set, nullptr, nullptr, &igi2_frame.timeout); i != -1; i = select(64, &igi2_frame.set, nullptr, nullptr, &igi2_frame.timeout) )
    {
      if ( !i )
        break;
      v1 = recvfrom(g_sock, buf_7bd1218, 1023, 0, (struct sockaddr *)&igi2_frame.saddr, &igi2_frame.saddrlen);
      if ( v1 != -1 )
      {
        (&buf_7bd1218)[v1] = 0;
        cdkey_process_buf(buf_7bd1218, v1, (struct sockaddr *)&igi2_frame.saddr);
      }
    }
  }
  next = clientq.next;
  v3 = clientq.next;
  if ( clientq.next )
  {
    while ( 1 )
    {
      client = v3->client;
      state = v3->client->state;
      if ( state )
      {
        v6 = state - 1;
        if ( v6 )
        {
          if ( v6 == 1 )
          {
            p_client = (void **)&v3->client;
            v8 = v3 == nullptr;
            v3 = v3->prev;
            v9 = (struct gsnode_s *)p_client;
            if ( !v8 || (v9 = next) != nullptr )
            {
              v9->prev->next = v9->next;
              v10 = v9->next;
              if ( v10 )
                v10->prev = v9->prev;
            }
            v11 = *((struct StaticTilemap_s **)*p_client + 17);
            if ( !v11 )
              v11 = &g_zInitialValue;
            (*((void (__cdecl **)(_DWORD, _DWORD, struct StaticTilemap_s *, _DWORD))*p_client + 16))(
              *(_DWORD *)*p_client,
              0,
              v11,
              *((_DWORD *)*p_client + 15));
            free(*((void **)*p_client + 18));
            if ( *((_DWORD *)*p_client + 17) )
              free(*((void **)*p_client + 17));
            free(*p_client);
            free(p_client);
          }
          goto LABEL_28;
        }
      }
      else
      {
        client = v3->client;
        if ( GetTickCount() < client->sttime + 2000 )
          goto LABEL_28;
        if ( client->ntries <= 2 )
        {
          TickCount = GetTickCount();
          reqlen = client->reqlen;
          v14 = client->ntries + 1;
          client->sttime = TickCount;
          reqstr = client->reqstr;
          client->ntries = v14;
          sendto(g_sock, reqstr, reqlen, 0, (struct sockaddr *)&valaddr, 16);
          goto LABEL_28;
        }
      }
      v16 = igi2_frame.validated_t;
      if ( client->state != cs_gotok )
        v16 = igi2_frame.timeout_t;
      client->authfn(client->localid, 1, v16, client->instance);
      v3->client->state = cs_done;
      free(v3->client->reqstr);
      v3->client->reqstr = nullptr;
LABEL_28:
      v3 = v3->next;
      if ( !v3 )
        return;
      next = clientq.next;
    }
  }
}

// source: j/0/network/gcdkeys.c:377  [anchor-caller]
void __cdecl cdkey_process_buf(char *buf, int len, struct sockaddr *fromaddr)
{
  #pragma pack(push, 1)
  union
  {
    struct { char uok_t[4]; };
    struct { char igi2_o1[4]; char unok_t[8]; };
    struct { char igi2_o2[12]; char ison_t[8]; };
    struct { char igi2_o3[20]; char ucount_t[7]; };
    struct { char igi2_o4[28]; char tok[32]; };
    char igi2_extent[60];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  bool v3; // zf
  unsigned int v4; // edi

  strcpy(igi2_frame.uok_t, "uok");
  strcpy(igi2_frame.unok_t, "unok");
  strcpy(igi2_frame.ison_t, "ison");
  strcpy(igi2_frame.ucount_t, "ucount");
  xcode_buf(buf, len);
  v3 = *buf == 92;
  igi2_frame.tok[0] = 0;
  if ( v3 )
  {
    v4 = strchr(buf + 1, 92) - buf;
    if ( v4 <= 0x20 )
    {
      strncpy(igi2_frame.tok, buf + 1, v4 - 1);
      igi2_frame.tok[v4 - 1] = 0;
    }
    if ( igi2_frame.tok[0] )
    {
      if ( !strcmp(igi2_frame.tok, igi2_frame.uok_t) )
      {
        process_oks(buf, 1);
      }
      else if ( !strcmp(igi2_frame.tok, igi2_frame.unok_t) )
      {
        process_oks(buf, 0);
      }
      else if ( !strcmp(igi2_frame.tok, igi2_frame.ison_t) )
      {
        process_ison(buf, (struct sockaddr_in *)fromaddr);
      }
      else if ( !strcmp(igi2_frame.tok, igi2_frame.ucount_t) )
      {
        process_ucount((struct sockaddr_in *)fromaddr);
      }
    }
  }
}

// source: j/0/network/gcdkeys.c:416  [anchor-mhash]
int __cdecl init_incoming_socket()
{
  #pragma pack(push, 1)
  union
  {
    struct { int saddrlen; };
    struct { char igi2_o1[4]; struct sockaddr_in saddr; };
    char igi2_extent[20];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)

  g_sock = socket(2, 2, 17);
  if ( g_sock == -1 )
    return -1;
  get_sockaddrin__gcdkeys(nullptr, 0, &igi2_frame.saddr, nullptr);
  if ( bind(g_sock, (struct sockaddr *)&igi2_frame.saddr, 16) == -1 )
    return -1;
  igi2_frame.saddrlen = 16;
  if ( getsockname(g_sock, (struct sockaddr *)&igi2_frame.saddr, &igi2_frame.saddrlen) == -1 )
    return -1;
  localport = igi2_frame.saddr.sin_port;
  return 0;
}

// source: j/0/network/gcdkeys.c:439  [anchor-hash]
int __cdecl gcd_init_common(int productid)
{
  DWORD TickCount; // eax
  int result; // eax

  pid_7bd1838 = productid;
  clientq.next = nullptr;
  clientq.prev = nullptr;
  clientq.client = nullptr;
  TickCount = GetTickCount();
  srand(TickCount);
  result = 0;
  byte_7BD1208[7] = 0;
  byte_7BD1208[0] = 103;
  byte_7BD1208[1] = 97;
  byte_7BD1208[2] = 109;
  byte_7BD1208[3] = 101;
  byte_7BD1208[4] = 115;
  byte_7BD1208[5] = 112;
  byte_7BD1208[6] = 121;
  return result;
}

// source: j/0/network/gcdkeys.c:449  [anchor-callee]
struct gsclient_s *__cdecl find_client(char *keyhash)
{
  struct gsnode_s *next; // edi

  next = clientq.next;
  if ( !clientq.next )
    return nullptr;
  while ( strcmp(keyhash, next->client->hkey) )
  {
    next = next->next;
    if ( !next )
      return nullptr;
  }
  return next->client;
}

// source: j/0/network/gcdkeys.c:462  [anchor-caller]
char *__cdecl process_oks(char *buf, int isok)
{
  #pragma pack(push, 1)
  union
  {
    struct { char cd_t[4]; };
    struct { char igi2_o1[4]; char skey_t[8]; };
    struct { char igi2_o2[12]; char errmsg_t[8]; };
    struct { char igi2_o3[20]; char keyhash[36]; };
    char igi2_extent[56];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  char *v3; // eax
  int v4; // ebp
  char *v5; // eax
  char *result; // eax
  char *v7; // esi
  char *v8; // eax

  strcpy(igi2_frame.errmsg_t, "errmsg");
  strcpy(igi2_frame.skey_t, "skey");
  strcpy(igi2_frame.cd_t, "cd");
  v3 = value_for_key__gcdkeys(buf, igi2_frame.skey_t);
  v4 = atoi(v3);
  v5 = value_for_key__gcdkeys(buf, igi2_frame.cd_t);
  strncpy(igi2_frame.keyhash, v5, 0x20u);
  igi2_frame.keyhash[32] = 0;
  result = (char *)find_client(igi2_frame.keyhash);
  v7 = result;
  if ( result && *((_DWORD *)result + 10) == v4 && *((_DWORD *)result + 14) != 3 )
  {
    if ( isok )
    {
      *((_DWORD *)result + 14) = 1;
    }
    else
    {
      *((_DWORD *)result + 14) = 2;
      v8 = value_for_key__gcdkeys(buf, igi2_frame.errmsg_t);
      result = goastrdup(v8);
      *((_DWORD *)v7 + 17) = result;
    }
  }
  return result;
}

// source: j/0/network/gcdkeys.c:494  [anchor-callee]
void __cdecl process_ucount(struct sockaddr_in *fromaddr)
{
  #pragma pack(push, 1)
  union
  {
    struct { char ucountformat[12]; };
    struct { char igi2_o1[12]; char outbuf[64]; };
    char igi2_extent[76];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct gsnode_s *next; // eax
  int v2; // ecx
  int v3; // esi
  int v4; // edx
  char *i; // ecx
  char v6; // bl
  char v7; // al

  next = clientq.next;
  strcpy(igi2_frame.ucountformat, "\\ucount\\%d");
  v2 = 0;
  if ( clientq.next )
  {
    do
    {
      next = next->next;
      ++v2;
    }
    while ( next );
  }
  v3 = sprintf(igi2_frame.outbuf, igi2_frame.ucountformat, v2);
  v4 = 0;
  for ( i = byte_7BD1208; v4 < v3; ++v4 )
  {
    v6 = *i ^ igi2_frame.outbuf[v4];
    v7 = *++i;
    igi2_frame.outbuf[v4] = v6;
    if ( !v7 )
      i = byte_7BD1208;
  }
  sendto(g_sock, igi2_frame.outbuf, v3, 0, (struct sockaddr *)fromaddr, 16);
}

// source: j/0/network/gcdkeys.c:511  [anchor-caller]
char *__cdecl process_ison(char *buf, struct sockaddr_in *fromaddr)
{
  #pragma pack(push, 1)
  union
  {
    struct { char cd_t[4]; };
    struct { char igi2_o1[4]; char skey_t[8]; };
    struct { char igi2_o2[12]; char uonformat[16]; };
    struct { char igi2_o3[28]; char uoffformat[16]; };
    struct { char igi2_o4[44]; char outbuf[64]; };
    char igi2_extent[108];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  char *v3; // eax
  int v4; // edi
  char *v5; // eax
  struct gsclient_s *client; // eax
  int v7; // eax
  int v8; // edi
  int v9; // esi
  char *i; // ecx
  char v11; // dl
  char v12; // al

  strcpy(igi2_frame.uonformat, "\\uon\\\\skey\\%d");
  strcpy(igi2_frame.uoffformat, "\\uoff\\\\skey\\%d");
  strcpy(igi2_frame.skey_t, "skey");
  strcpy(igi2_frame.cd_t, "cd");
  v3 = value_for_key__gcdkeys(buf, igi2_frame.skey_t);
  v4 = atoi(v3);
  v5 = value_for_key__gcdkeys(buf, igi2_frame.cd_t);
  client = find_client(v5);
  if ( client && client->state == cs_done )
    v7 = sprintf(igi2_frame.outbuf, igi2_frame.uonformat, v4);
  else
    v7 = sprintf(igi2_frame.outbuf, igi2_frame.uoffformat, v4);
  v8 = v7;
  v9 = 0;
  for ( i = byte_7BD1208; v9 < v8; ++v9 )
  {
    v11 = *i ^ igi2_frame.outbuf[v9];
    v12 = *++i;
    igi2_frame.outbuf[v9] = v11;
    if ( !v12 )
      i = byte_7BD1208;
  }
  return (char *)sendto(g_sock, igi2_frame.outbuf, v8, 0, (struct sockaddr *)fromaddr, 16);
}

// source: j/0/network/gcdkeys.c:534  [anchor-callee]
void __cdecl send_disconnect_req(struct gsclient_s *client)
{
  #pragma pack(push, 1)
  union
  {
    struct { char discformat[28]; };
    struct { char igi2_o1[28]; char buf[512]; };
    char igi2_extent[540];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v1; // esi
  int v2; // edx
  char *i; // ecx
  char v4; // bl
  char v5; // al

  strcpy(igi2_frame.discformat, "\\disc\\\\pid\\%d\\cd\\%s\\ip\\%d");
  v1 = sprintf(igi2_frame.buf, igi2_frame.discformat, pid_7bd1838, client->hkey, client->ip);
  v2 = 0;
  for ( i = byte_7BD1208; v2 < v1; ++v2 )
  {
    v4 = *i ^ igi2_frame.buf[v2];
    v5 = *++i;
    igi2_frame.buf[v2] = v4;
    if ( !v5 )
      i = byte_7BD1208;
  }
  sendto(g_sock, igi2_frame.buf, v1, 0, (struct sockaddr *)&valaddr, 16);
}

// source: j/0/network/gcdkeys.c:547  [anchor-caller]
void __cdecl send_auth_req(struct gsclient_s *client, char *challenge, char *response)
{
  #pragma pack(push, 1)
  union
  {
    struct { int v11; };
    struct { char igi2_o1[16]; int sesskey; };
    struct { char igi2_o2[32]; char authformat[44]; };
    struct { char igi2_o3[76]; char buf[512]; };
    char igi2_extent[588];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  unsigned __int16 TickCount; // bp
  DWORD v4; // eax
  int ip; // ecx
  int v6; // edi
  char *v7; // eax
  int i; // ecx
  char *v10; // eax

  strcpy(igi2_frame.authformat, "\\auth\\\\pid\\%d\\ch\\%s\\resp\\%s\\ip\\%d\\skey\\%d");
  client->state = cs_sentreq;
  TickCount = GetTickCount();
  client->sesskey = (TickCount ^ (unsigned __int16)rand()) & 0x3FFF;
  v4 = GetTickCount();
  ip = client->ip;
  client->sttime = v4;
  igi2_frame.sesskey = client->sesskey;
  igi2_frame.v11 = pid_7bd1838;
  client->ntries = 1;
  v6 = sprintf(igi2_frame.buf, igi2_frame.authformat, igi2_frame.v11, challenge, response, ip, igi2_frame.sesskey);
  v7 = byte_7BD1208;
  for ( i = 0; i < v6; ++i )
  {
    igi2_frame.buf[i] ^= *v7;
    if ( !*++v7 )
      v7 = byte_7BD1208;
  }
  sendto(g_sock, igi2_frame.buf, v6, 0, (struct sockaddr *)&valaddr, 16);
  v10 = (char *)malloc(v6);
  client->reqstr = v10;
  memmove(v10, igi2_frame.buf, v6);
  client->reqlen = v6;
}

// source: j/0/network/gcdkeys.c:568  [anchor-hash]
void __cdecl resend_auth_req(struct gsclient_s *client)
{
  DWORD TickCount; // eax
  int ntries; // edx
  char *reqstr; // ecx
  int reqlen; // [esp-10h] [ebp-10h]

  TickCount = GetTickCount();
  ntries = client->ntries;
  reqstr = client->reqstr;
  client->sttime = TickCount;
  reqlen = client->reqlen;
  client->ntries = ntries + 1;
  sendto(g_sock, reqstr, reqlen, 0, (struct sockaddr *)&valaddr, 16);
}

// source: j/0/network/gcdkeys.c:578  [anchor-callee]
char *__cdecl value_for_key__gcdkeys(char *s, char *key)
{
  #pragma pack(push, 1)
  union
  {
    struct { char slash_t[3]; };
    struct { char igi2_o1[3]; char v18; };
    struct { char igi2_o2[4]; char keyspec[256]; };
    char igi2_extent[260];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v2; // eax
  char v3; // cl
  unsigned int v4; // eax
  char *v5; // edi
  unsigned int v7; // eax
  char *v8; // edi
  char *v10; // eax
  char *v12; // eax
  char v13; // cl
  char *v14; // ebx
  char *v15; // esi
  int v16; // edi

  dword_7BD1214 ^= 1u;
  strcpy(igi2_frame.slash_t, "\\");
  v2 = 0;
  do
  {
    v3 = igi2_frame.slash_t[v2];
    igi2_frame.keyspec[v2++] = v3;
  }
  while ( v3 );
  v4 = strlen(key) + 1;
  v5 = &igi2_frame.v18;
  while ( *++v5 )
    ;
  qmemcpy(v5, key, v4);
  v7 = &igi2_frame.slash_t[strlen(igi2_frame.slash_t) + 1] - igi2_frame.slash_t;
  v8 = &igi2_frame.v18;
  while ( *++v8 )
    ;
  qmemcpy(v8, igi2_frame.slash_t, v7);
  v10 = strstr(s, igi2_frame.keyspec);
  if ( !v10 )
    return (char *)&g_zInitialValue;
  v12 = &v10[strlen(igi2_frame.keyspec)];
  v13 = *v12;
  v14 = (char *)&unk_7BD1638 + 256 * dword_7BD1214;
  v15 = v14;
  if ( *v12 )
  {
    v16 = 0;
    do
    {
      if ( v13 == 92 )
        break;
      if ( v16 >= 200 )
        break;
      *v15 = v13;
      v13 = v12[1];
      ++v15;
      ++v16;
      ++v12;
    }
    while ( v13 );
  }
  *v15 = 0;
  return v14;
}

// source: j/0/network/gcdkeys.c:602  [anchor-callee]
void __cdecl xcode_buf(char *buf, int len)
{
  int v2; // ecx
  char *i; // eax
  char v4; // bl

  v2 = 0;
  for ( i = byte_7BD1208; v2 < len; ++v2 )
  {
    v4 = *i++ ^ buf[v2];
    buf[v2] = v4;
    if ( !*i )
      i = byte_7BD1208;
  }
}

// source: j/0/network/gcdkeys.c:617  [anchor-mhash]
int __cdecl get_sockaddrin__gcdkeys(
        char *host,
        int port,
        struct sockaddr_in *saddr,
        struct hostent **savehent)
{
  int result; // eax
  char broadcast_t[16]; // [esp+4h] [ebp-10h] BYREF

  qmemcpy(broadcast_t, "255", 3);
  qmemcpy(&broadcast_t[4], "255", 3);
  qmemcpy(&broadcast_t[8], "255", 3);
  qmemcpy(&broadcast_t[12], "255", 3);
  *(_DWORD *)&saddr->sin_family = 0;
  saddr->sin_addr.S_un.S_addr = 0;
  broadcast_t[3] = 46;
  broadcast_t[7] = 46;
  broadcast_t[11] = 46;
  *(_DWORD *)saddr->sin_zero = 0;
  *(_DWORD *)&saddr->sin_zero[4] = 0;
  broadcast_t[15] = 0;
  saddr->sin_family = 2;
  saddr->sin_port = htons(port);
  if ( host )
    saddr->sin_addr.S_un.S_addr = inet_addr(host);
  else
    saddr->sin_addr.S_un.S_addr = 0;
  if ( saddr->sin_addr.S_un.S_addr != -1 || !strcmp(host, broadcast_t) )
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

// source: j/0/network/gcdkeys.c:651  [anchor-mhash]
struct gsnode_s *__cdecl add_to_queue(struct gsnode_s *t, struct gsnode_s *que)
{
  for ( ; que->next; que = que->next )
    ;
  que->next = t;
  t->prev = que;
  t->next = nullptr;
  return que;
}

// source: j/0/network/gcdkeys.c:667  [anchor-mhash]
struct gsnode_s *__cdecl remove_from_queue(struct gsnode_s *t, struct gsnode_s *que)
{
  struct gsnode_s *next; // ecx

  if ( t || (t = que->next) != nullptr )
  {
    t->prev->next = t->next;
    next = t->next;
    if ( next )
      next->prev = t->prev;
  }
  return t;
}
