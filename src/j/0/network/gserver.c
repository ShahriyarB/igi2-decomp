/* j/0/network/gserver.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/network/gserver.c:43  [anchor-callee]
char *__cdecl mytok(char *instr, char delim)
{
  char v2; // dl
  char *v3; // esi
  char *result; // eax

  if ( instr )
    dword_7BD0CA8 = (int)instr;
  else
    instr = (char *)dword_7BD0CA8;
  v2 = *instr;
  v3 = instr;
  if ( !*instr )
    goto LABEL_8;
  do
  {
    if ( v2 == delim )
      break;
    v2 = *++instr;
  }
  while ( v2 );
  dword_7BD0CA8 = (int)instr;
  if ( instr == v3 )
LABEL_8:
    v3 = nullptr;
  result = v3;
  if ( *instr )
  {
    *instr = 0;
    dword_7BD0CA8 = (int)(instr + 1);
  }
  return result;
}

// source: j/0/network/gserver.c:63  [anchor-caller]
char *__cdecl LookupKey(struct GServerImplementation *server, char *k)
{
  char **v2; // eax
  char *v4; // eax
  struct HashImplementation *keylist; // [esp-8h] [ebp-Ch]

  v2 = (char **)TableLookup(server->keylist, &k);
  if ( v2 )
    return *v2;
  v4 = goastrdup(k);
  keylist = server->keylist;
  k = v4;
  TableEnter(keylist, &k);
  return k;
}

// source: j/0/network/gserver.c:75  [anchor-mhash]
void __cdecl ServerFree(void *elem)
{
  void *v1; // esi

  v1 = *(void **)elem;
  TableFree(*(struct HashImplementation **)(*(_DWORD *)elem + 12));
  free(v1);
}

// source: j/0/network/gserver.c:84  [anchor-mhash]
void __cdecl ServerSetAddressFromString(struct GServerImplementation *server, char *address)
{
  char *v2; // eax
  char *v3; // esi

  v2 = strchr(address, 58);
  v3 = v2;
  if ( v2 )
  {
    *v2 = 0;
    server->ip = inet_addr(address);
    server->port = atoi(v3 + 1);
  }
}

// source: j/0/network/gserver.c:95  [anchor-strings]
struct GServerImplementation *__cdecl ServerNewData(
        char **fieldlist,
        int fieldcount,
        char *serverdata,
        enum GQueryType qtype,
        struct HashImplementation *keylist)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct HashImplementation *v22; };
    struct { struct HashImplementation *v23; };
    struct { char igi2_o2[24]; int curfield; };
    struct { char igi2_o3[28]; struct GKeyValuePair kvpair; };
    char igi2_extent[36];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct GServerImplementation *v5; // ebp
  char *v6; // ebx
  char *v7; // eax
  char *v8; // esi
  char *v9; // eax
  struct HashImplementation *v11; // edi
  char **v12; // eax
  char *v13; // eax
  char *v14; // eax
  struct HashImplementation *v15; // edi
  char **v16; // eax
  char *v17; // eax
  char *v18; // eax
  char *v19; // eax
  char v20; // cl

  igi2_frame.curfield = 0;
  v5 = ServerNew(0, 0, qtype, keylist);
  v6 = mytok(serverdata + 1, 92);
  if ( fieldcount > 0 )
  {
    while ( 1 )
    {
      if ( !v6 )
        v6 = (char *)&g_zInitialValue;
      if ( !strcmp(fieldlist[igi2_frame.curfield], "ip") )
      {
        v7 = strchr(v6, 58);
        v8 = v7;
        if ( v7 )
        {
          *v7 = 0;
          v5->ip = inet_addr(v6);
          v5->port = atoi(v8 + 1);
        }
      }
      else if ( qtype == qt_grouprooms && !strcmp(fieldlist[igi2_frame.curfield], "other") )
      {
        v9 = v6;
        if ( *v6 )
        {
          do
          {
            if ( *v9 == 1 )
              *v9 = 92;
          }
          while ( *++v9 );
        }
        ServerParseKeyVals(v5, v6);
      }
      else
      {
        v11 = v5->keylist;
        serverdata = fieldlist[igi2_frame.curfield];
        v12 = (char **)TableLookup(v11, &serverdata);
        if ( v12 )
        {
          v13 = *v12;
        }
        else
        {
          v14 = goastrdup(serverdata);
          igi2_frame.v22 = v5->keylist;
          serverdata = v14;
          TableEnter(igi2_frame.v22, &serverdata);
          v13 = serverdata;
        }
        igi2_frame.kvpair.key = v13;
        v15 = v5->keylist;
        serverdata = v6;
        v16 = (char **)TableLookup(v15, &serverdata);
        if ( v16 )
        {
          v17 = *v16;
        }
        else
        {
          v18 = goastrdup(serverdata);
          igi2_frame.v23 = v5->keylist;
          serverdata = v18;
          TableEnter(igi2_frame.v23, &serverdata);
          v17 = serverdata;
        }
        igi2_frame.kvpair.value = v17;
        TableEnter(v5->keyvals, &igi2_frame.kvpair);
      }
      if ( ++igi2_frame.curfield >= fieldcount )
        break;
      v19 = (char *)dword_7BD0CA8;
      v20 = *(_BYTE *)dword_7BD0CA8;
      v6 = (char *)dword_7BD0CA8;
      if ( !*(_BYTE *)dword_7BD0CA8 )
        goto LABEL_26;
      do
      {
        if ( v20 == 92 )
          break;
        v20 = *++v19;
      }
      while ( v20 );
      dword_7BD0CA8 = (int)v19;
      if ( v19 == v6 )
LABEL_26:
        v6 = nullptr;
      if ( *v19 )
      {
        *v19 = 0;
        dword_7BD0CA8 = (int)(v19 + 1);
      }
    }
  }
  return v5;
}

// source: j/0/network/gserver.c:134  [anchor-callee]
struct GServerImplementation *__cdecl ServerNew(
        unsigned int ip,
        unsigned __int16 port,
        enum GQueryType qtype,
        struct HashImplementation *keylist)
{
  struct GServerImplementation *v4; // esi
  int v5; // eax
  int v6; // ecx

  v4 = (struct GServerImplementation *)malloc(0x14u);
  v4->ip = ip;
  v4->port = port;
  v4->ping = 9999;
  v4->querytype = qtype;
  switch ( qtype )
  {
    case qt_basic:
      v5 = 4;
      v6 = 2;
      break;
    case qt_info:
      v5 = 6;
      v6 = 2;
      break;
    case qt_rules:
    case qt_players:
      v6 = 2;
      goto LABEL_6;
    default:
      v6 = 4;
LABEL_6:
      v5 = 8;
      break;
  }
  v4->keyvals = TableNew2(
                  8,
                  v5,
                  v6,
                  KeyValHashKeyP,
                  (int (__cdecl *)(void *, void *))KeyValCompareKeyP,
                  nullptr);
  v4->keylist = keylist;
  return v4;
}

// source: j/0/network/gserver.c:173  [anchor-strings]
int __cdecl CheckValidKey(char *key)
{
  int v1; // edi
  char *InvalidKeys[2]; // [esp+10h] [ebp-8h]

  InvalidKeys[0] = unk_68580C;
  InvalidKeys[1] = (char *)&unk_685804;
  v1 = 0;
  while ( strcmp(key, InvalidKeys[v1]) )
  {
    if ( (unsigned int)++v1 >= 2 )
      return 1;
  }
  return 0;
}

// source: j/0/network/gserver.c:185  [anchor-callee]
void __cdecl ServerParseKeyVals(struct GServerImplementation *server, char *keyvals)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct HashImplementation *keylist; };
    struct { struct HashImplementation *v20; };
    struct { char igi2_o2[24]; char *newElem; };
    struct { char igi2_o3[28]; struct GKeyValuePair kvpair; };
    char igi2_extent[36];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  char *v2; // edi
  char *v3; // esi
  char v4; // al
  char *v5; // ecx
  char *v6; // ebx
  char **v7; // eax
  char *v8; // eax
  char *v9; // eax
  char *v10; // edi
  struct HashImplementation *v11; // edi
  char **v12; // eax
  char *v13; // eax
  char *v14; // eax
  char *v15; // edi
  struct HashImplementation *v16; // ecx
  char v17; // al
  char *v18; // ecx

  v2 = mytok(keyvals + 1, 92);
  if ( v2 )
  {
    v3 = (char *)dword_7BD0CA8;
    do
    {
      v4 = *v3;
      v5 = v3;
      if ( !*v3 )
        goto LABEL_7;
      do
      {
        if ( v4 == 92 )
          break;
        v4 = *++v3;
      }
      while ( v4 );
      dword_7BD0CA8 = (int)v3;
      if ( v3 == v5 )
LABEL_7:
        v5 = nullptr;
      if ( *v3 )
      {
        *v3++ = 0;
        dword_7BD0CA8 = (int)v3;
      }
      v6 = v5;
      if ( !v5 )
        v6 = (char *)&g_zInitialValue;
      if ( CheckValidKey(v2) )
      {
        igi2_frame.newElem = v2;
        v7 = (char **)TableLookup(server->keylist, &igi2_frame.newElem);
        if ( v7 )
        {
          v8 = *v7;
        }
        else
        {
          v9 = igi2_frame.newElem;
          v10 = igi2_frame.newElem;
          if ( igi2_frame.newElem )
          {
            v9 = (char *)malloc(strlen(igi2_frame.newElem) + 1);
            if ( v9 )
              strcpy(v9, v10);
          }
          igi2_frame.keylist = server->keylist;
          igi2_frame.newElem = v9;
          TableEnter(igi2_frame.keylist, &igi2_frame.newElem);
          v8 = igi2_frame.newElem;
        }
        v11 = server->keylist;
        igi2_frame.kvpair.key = v8;
        igi2_frame.newElem = (char *)v6;
        v12 = (char **)TableLookup(v11, &igi2_frame.newElem);
        if ( v12 )
        {
          v13 = *v12;
        }
        else
        {
          v14 = igi2_frame.newElem;
          v15 = igi2_frame.newElem;
          if ( igi2_frame.newElem )
          {
            v14 = (char *)malloc(strlen(igi2_frame.newElem) + 1);
            if ( v14 )
              strcpy(v14, v15);
          }
          igi2_frame.v20 = server->keylist;
          igi2_frame.newElem = v14;
          TableEnter(igi2_frame.v20, &igi2_frame.newElem);
          v13 = igi2_frame.newElem;
        }
        v16 = server->keyvals;
        igi2_frame.kvpair.value = v13;
        TableEnter(v16, &igi2_frame.kvpair);
        v3 = (char *)dword_7BD0CA8;
      }
      v17 = *v3;
      v18 = v3;
      if ( !*v3 )
        goto LABEL_30;
      do
      {
        if ( v17 == 92 )
          break;
        v17 = *++v3;
      }
      while ( v17 );
      dword_7BD0CA8 = (int)v3;
      if ( v3 == v18 )
LABEL_30:
        v18 = nullptr;
      if ( *v3 )
      {
        *v3++ = 0;
        dword_7BD0CA8 = (int)v3;
      }
      v2 = v18;
    }
    while ( v18 );
  }
}

// source: j/0/network/gserver.c:211  [size]
int __cdecl ServerGetPing(struct GServerImplementation *server)
{
  return server->ping;
}

// source: j/0/network/gserver.c:219  [anchor-hash]
char *__cdecl ServerGetAddress(struct GServerImplementation *server)
{
  return inet_ntoa((*(struct in_addr *)&server->ip));
}

// source: j/0/network/gserver.c:227  [size]
unsigned int __cdecl ServerGetInetAddress(struct GServerImplementation *server)
{
  return server->ip;
}

// source: j/0/network/gserver.c:236  [size]
int __cdecl ServerGetQueryPort(struct GServerImplementation *server)
{
  return server->port;
}

// source: j/0/network/gserver.c:241  [anchor-mhash]
struct GKeyValuePair *__cdecl ServerRuleLookup(struct GServerImplementation *server, char *key)
{
  struct GKeyValuePair *result; // eax
  struct HashImplementation *keyvals; // edi
  struct GKeyValuePair kvp; // [esp+4h] [ebp-8h] BYREF

  result = (struct GKeyValuePair *)TableLookup(server->keylist, &key);
  if ( result )
  {
    keyvals = server->keyvals;
    kvp.key = result->key;
    return (struct GKeyValuePair *)TableLookup(keyvals, &kvp);
  }
  return result;
}

// source: j/0/network/gserver.c:255  [anchor-strings]
char *__cdecl ServerGetStringValue(
        struct GServerImplementation *server,
        char *key,
        char *sdefault)
{
  #pragma pack(push, 1)
  union
  {
    struct { char *elemKey; };
    struct { char igi2_o1[4]; int v9; };
    char igi2_extent[12];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct HashImplementation *keylist; // edi
  int *v5; // eax
  struct HashImplementation *keyvals; // edi
  void *v7; // eax

  if ( !strcmp(key, "hostaddr") )
    return inet_ntoa((*(struct in_addr *)&server->ip));
  keylist = server->keylist;
  igi2_frame.elemKey = key;
  v5 = (int *)TableLookup(keylist, &igi2_frame.elemKey);
  if ( v5 && (keyvals = server->keyvals, igi2_frame.v9 = *v5, (v7 = TableLookup(keyvals, &igi2_frame.v9)) != nullptr) )
    return *((char **)v7 + 1);
  else
    return sdefault;
}

// source: j/0/network/gserver.c:267  [anchor-callee]
int __cdecl ServerGetIntValue(struct GServerImplementation *server, char *key, int idefault)
{
  #pragma pack(push, 1)
  union
  {
    struct { char *elemKey; };
    struct { char igi2_o1[4]; int v9; };
    char igi2_extent[12];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct HashImplementation *keylist; // edi
  int *v5; // eax
  struct HashImplementation *keyvals; // edi
  char **v7; // eax

  if ( !strcmp(key, "ping") )
    return server->ping;
  keylist = server->keylist;
  igi2_frame.elemKey = key;
  v5 = (int *)TableLookup(keylist, &igi2_frame.elemKey);
  if ( v5 && (keyvals = server->keyvals, igi2_frame.v9 = *v5, (v7 = (char **)TableLookup(keyvals, &igi2_frame.v9)) != nullptr) )
    return atoi(v7[1]);
  else
    return idefault;
}

// source: j/0/network/gserver.c:280  [anchor-mhash]
double __cdecl ServerGetFloatValue(
        struct GServerImplementation *server,
        char *key,
        double fdefault)
{
  #pragma pack(push, 1)
  union
  {
    struct { char *elemKey; };
    struct { char igi2_o1[4]; int v9; };
    char igi2_extent[12];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct HashImplementation *keylist; // edi
  int *v4; // eax
  struct HashImplementation *keyvals; // edi
  _DWORD *v6; // eax

  keylist = server->keylist;
  igi2_frame.elemKey = key;
  v4 = (int *)TableLookup(keylist, &igi2_frame.elemKey);
  if ( v4 && (keyvals = server->keyvals, igi2_frame.v9 = *v4, (v6 = TableLookup(keyvals, &igi2_frame.v9)) != nullptr) )
    return atof((char *)v6[1]);
  else
    return fdefault;
}

// source: j/0/network/gserver.c:290  [anchor-mhash]
int __cdecl ServerGetBoolValue(struct GServerImplementation *server, char *key, int bdefault)
{
  #pragma pack(push, 1)
  union
  {
    struct { char *elemKey; };
    struct { char igi2_o1[4]; int v10; };
    char igi2_extent[12];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct HashImplementation *keylist; // edi
  int *v4; // eax
  struct HashImplementation *keyvals; // edi
  _BYTE **v6; // eax
  char v8; // al

  keylist = server->keylist;
  igi2_frame.elemKey = key;
  v4 = (int *)TableLookup(keylist, &igi2_frame.elemKey);
  if ( !v4 )
    return bdefault;
  keyvals = server->keyvals;
  igi2_frame.v10 = *v4;
  v6 = (_BYTE **)TableLookup(keyvals, &igi2_frame.v10);
  if ( !v6 )
    return bdefault;
  v8 = *v6[1];
  return v8 != 48 && v8 != 70 && v8 != 102 && v8 != 78 && v8 != 110;
}

// source: j/0/network/gserver.c:306  [anchor-caller]
char *__cdecl ServerGetPlayerStringValue(
        struct GServerImplementation *server,
        int playernum,
        char *key,
        char *sdefault)
{
  char newkey[32]; // [esp+0h] [ebp-20h] BYREF

  sprintf(newkey, "%s_%d", key, playernum);
  return ServerGetStringValue(server, newkey, sdefault);
}

// source: j/0/network/gserver.c:313  [anchor-caller]
int __cdecl ServerGetPlayerIntValue(
        struct GServerImplementation *server,
        int playernum,
        char *key,
        int idefault)
{
  char newkey[32]; // [esp+0h] [ebp-20h] BYREF

  sprintf(newkey, "%s_%d", key, playernum);
  return ServerGetIntValue(server, newkey, idefault);
}

// source: j/0/network/gserver.c:321  [anchor-mhash]
double __cdecl ServerGetPlayerFloatValue(
        struct GServerImplementation *server,
        int playernum,
        char *key,
        double fdefault)
{
  int v4; // eax
  char *v5; // ecx
  struct GServerImplementation *v6; // esi
  char newkey[32]; // [esp+0h] [ebp-20h] BYREF

  sprintf(newkey, "%s_%d", v5, v4);
  return ServerGetFloatValue(v6, newkey, COERCE_DOUBLE(__PAIR64__(playernum, (unsigned int)server)));
}

// source: j/0/network/gserver.c:336  [anchor-mhash]
void __cdecl KeyMapF(void *elem, void *clientData)
{
  (*(void (__cdecl **)(_DWORD, _DWORD, _DWORD))clientData)(
    *(_DWORD *)elem,
    *((_DWORD *)elem + 1),
    *((_DWORD *)clientData + 1));
}

// source: j/0/network/gserver.c:344  [anchor-mhash]
struct GServerImplementation *__cdecl ServerEnumKeys(
        struct GServerImplementation *server,
        void (__cdecl *KeyFn)(char *, char *, void *),
        void *instance)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct HashImplementation *keyvals; };
    struct { char igi2_o1[12]; struct GEnumData ed; };
    char igi2_extent[24];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct GServerImplementation *result; // eax

  igi2_frame.ed.instance = instance;
  igi2_frame.ed.EnumFn = KeyFn;
  igi2_frame.keyvals = server->keyvals;
  igi2_frame.ed.keylist = server->keylist;
  TableMap(igi2_frame.keyvals, KeyMapF, &igi2_frame.ed);
  return result;
}

// source: j/0/network/gserver.c:361  [anchor-mhash]
int __cdecl StringHash(char *s, int numbuckets)
{
  char *v2; // edi
  char v3; // al
  unsigned int v4; // esi

  v2 = s;
  v3 = *s;
  v4 = 0;
  if ( v3 )
  {
    do
    {
      ++v2;
      v4 = tolower(v3) - 1664117991 * v4;
      v3 = *v2;
    }
    while ( *v2 );
  }
  return v4 % numbuckets;
}

// source: j/0/network/gserver.c:373  [size]
int __cdecl GStringHash(void *elem, int numbuckets)
{
  return StringHash(*(char **)elem, numbuckets);
}

// source: j/0/network/gserver.c:378  [size]
int __cdecl KeyValHashKeyP(void *elem, int numbuckets)
{
  return StringHash(*(char **)elem, numbuckets);
}

// source: j/0/network/gserver.c:391  [size]
int __cdecl GCaseInsensitiveCompare(void *entry1, void *entry2)
{
  return _stricmp(*(char **)entry1, *(char **)entry2);
}

// source: j/0/network/gserver.c:399  [size]
int __cdecl KeyValCompareKeyP(void *entry1, void *entry2)
{
  return *(_DWORD *)entry1 - *(_DWORD *)entry2;
}

// source: j/0/network/gserver.c:404  [size]
void __cdecl GStringFree(void *elem)
{
  free(*(void **)elem);
}
