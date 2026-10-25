/* j/0/network/nonport.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/network/nonport.c:198  [size]
// attributes: thunk
unsigned int __cdecl current_time()
{
  return GetTickCount();
}

// source: j/0/network/nonport.c:247  [anchor-hash]
void __cdecl msleep(unsigned int msec)
{
  Sleep(msec);
}

// source: j/0/network/nonport.c:274  [size]
void __cdecl SocketStartUp()
{
  struct WSAData data; // [esp+0h] [ebp-190h] BYREF

  WSAStartup(0x101u, &data);
}

// source: j/0/network/nonport.c:284  [size]
// attributes: thunk
void __cdecl SocketShutDown()
{
  WSACleanup();
}

// source: j/0/network/nonport.c:294  [anchor-callee]
char *__cdecl goastrdup(char *src)
{
  char *result; // eax

  if ( !src )
    return nullptr;
  result = (char *)malloc(strlen(src) + 1);
  if ( result )
    strcpy(result, src);
  return result;
}

// source: j/0/network/nonport.c:334  [anchor-mhash]
int __cdecl SetSockBlocking(unsigned int sock, int isblocking)
{
  unsigned int argp; // [esp+0h] [ebp-4h] BYREF

  argp = isblocking == 0;
  return ioctlsocket(sock, -2147195266, &argp) == 0;
}

// source: j/0/network/nonport.c:395  [anchor-mhash]
int __cdecl DisableNagle(unsigned int sock)
{
  int noDelay; // [esp+0h] [ebp-4h] BYREF

  noDelay = 1;
  return setsockopt(sock, 6, 1, (char *)&noDelay, 4) != -1;
}

// source: j/0/network/nonport.c:412  [anchor-mhash]
int __cdecl SetReceiveBufferSize(unsigned int sock, int size)
{
  return setsockopt(sock, 0xFFFF, 4098, (char *)&size, 4) != -1;
}

// source: j/0/network/nonport.c:554  [anchor-hash]
int __cdecl nextlongrand(int seed)
{
  unsigned int v1; // ecx
  unsigned int v2; // eax
  int result; // eax

  v1 = 16807 * HIWORD(seed);
  v2 = ((v1 & 0x7FFF) << 16) + 16807 * (unsigned __int16)seed;
  if ( v2 > 0x7FFFFFFF )
    v2 = (v2 & 0x7FFFFFFF) + 1;
  result = (v1 >> 15) + v2;
  if ( (unsigned int)result > 0x7FFFFFFF )
    return (result & 0x7FFFFFFF) + 1;
  return result;
}

// source: j/0/network/nonport.c:579  [anchor-hash]
int __cdecl longrand()
{
  unsigned int v0; // eax
  int result; // eax

  v0 = (((16807 * HIWORD(randomnum)) & 0x7FFF) << 16) + 16807 * (unsigned __int16)randomnum;
  if ( v0 > 0x7FFFFFFF )
    v0 = (v0 & 0x7FFFFFFF) + 1;
  result = ((16807 * (unsigned int)HIWORD(randomnum)) >> 15) + v0;
  if ( (unsigned int)result > 0x7FFFFFFF )
    result = (result & 0x7FFFFFFF) + 1;
  randomnum = result;
  return result;
}

// source: j/0/network/nonport.c:586  [anchor-hash]
unsigned int __cdecl Util_RandSeed(unsigned int seed)
{
  if ( seed )
  {
    seed &= ~0x80000000;
    randomnum = seed;
  }
  else
  {
    randomnum = 1;
  }
  return seed;
}

// source: j/0/network/nonport.c:593  [anchor-caller]
int __cdecl Util_RandInt(int low, int high)
{
  return low + longrand() % (high - low);
}

// source: j/0/network/nonport.c:730  [anchor-strings]
void __cdecl GenerateID(char *keyval)
{
  #pragma pack(push, 1)
  union
  {
    struct { union _LARGE_INTEGER l1; };
    struct { char igi2_o1[8]; char crypttab[64]; };
    char igi2_extent[72];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  DWORD v1; // edi
  __time32_t v2; // esi
  int v3; // esi
  DWORD v4; // esi
  int i; // esi

  strcpy(igi2_frame.crypttab, "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");
  if ( QueryPerformanceCounter(&igi2_frame.l1) )
    v1 = igi2_frame.l1.LowPart ^ igi2_frame.l1.HighPart;
  else
    v1 = 0;
  v2 = time(nullptr);
  v3 = clock() ^ v2;
  v4 = v1 ^ GetTickCount() ^ v3;
  if ( v4 )
    randomnum = v4 & 0x7FFFFFFF;
  else
    randomnum = 1;
  for ( i = 0; i < 19; ++i )
  {
    if ( i == 4 || i == 9 || i == 14 )
      keyval[i] = 45;
    else
      keyval[i] = igi2_frame.crypttab[longrand() % 62];
  }
  keyval[19] = 0;
}

// source: j/0/network/nonport.c:758  [anchor-strings]
char *__cdecl GOAGetUniqueID()
{
  #pragma pack(push, 1)
  union
  {
    struct { struct HKEY__ *thekey; };
    struct { char igi2_o1[4]; unsigned int len; };
    struct { char igi2_o2[8]; unsigned int thetype; };
    struct { char igi2_o3[12]; unsigned int disp; };
    char igi2_extent[16];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  BOOL v0; // esi

  igi2_frame.thetype = 1;
  igi2_frame.len = 260;
  v0 = RegOpenKeyExA(HKEY_CURRENT_USER, "Software\\GameSpy\\GameSpy 3D\\Registration", 0, 0xF003Fu, &igi2_frame.thekey) != 0;
  if ( RegQueryValueExA(igi2_frame.thekey, "Crypt", nullptr, &igi2_frame.thetype, g_keyval, &igi2_frame.len) || strlen((char *)g_keyval) != 19 )
  {
    GenerateID((char *)g_keyval);
    if ( v0 )
      RegCreateKeyExA(
        HKEY_CURRENT_USER,
        "Software\\GameSpy\\GameSpy 3D\\Registration",
        0,
        nullptr,
        0,
        0xF003Fu,
        nullptr,
        &igi2_frame.thekey,
        &igi2_frame.disp);
    RegSetValueExA(igi2_frame.thekey, "Crypt", 0, 1u, g_keyval, strlen((char *)g_keyval) + 1);
  }
  RegCloseKey(igi2_frame.thekey);
  memmove(&unk_834D9DC, &unk_834D9DD, 4u);
  memmove(&unk_834D9E0, &unk_834D9E2, 4u);
  memmove(&unk_834D9E4, &unk_834D9E7, 4u);
  byte_834D9E8 = 0;
  return (char *)g_keyval;
}
