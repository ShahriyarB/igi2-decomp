/* j/0/network/packman.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/network/packman.c:28  [size]
struct PackMan_t *__cdecl PackMan_Clear(struct PackMan_t *ptPackMan)
{
  ptPackMan->buffer = nullptr;
  return ptPackMan;
}

// source: j/0/network/packman.c:42  [anchor-mhash]
unsigned int __cdecl PackMan_GetBits(unsigned int range_max)
{
  unsigned int result; // eax

  result = 1;
  if ( range_max > 1 )
  {
    do
      ++result;
    while ( (1 << result) - 1 < range_max );
  }
  return result;
}

// source: j/0/network/packman.c:70  [anchor-hash]
__int16 __cdecl PackMan_GetBitsFast(unsigned int n)
{
  int v1; // ecx
  unsigned int v2; // eax

  v1 = (n & 0xFFFF0000) != 0 ? 0x10 : 0;
  v2 = n >> v1;
  if ( BYTE1(v2) )
  {
    v1 |= 8u;
    v2 >>= 8;
  }
  if ( (v2 & 0xF0) != 0 )
  {
    v1 |= 4u;
    v2 >>= 4;
  }
  if ( (v2 & 0xC) != 0 )
  {
    v1 |= 2u;
    v2 >>= 2;
  }
  return v1 | (v2 >> 1);
}

// source: j/0/network/packman.c:95  [size]
struct PackMan_t *__cdecl PackMan_Reset(
        struct PackMan_t *ptPackMan,
        unsigned __int8 *buffer)
{
  ptPackMan->buffer = (unsigned int *)buffer;
  ptPackMan->nNextBitWrite = 0;
  ptPackMan->nNextBitRead = 0;
  return ptPackMan;
}

// source: j/0/network/packman.c:116  [anchor-mhash]
unsigned int __cdecl PackMan_Pack(
        struct PackMan_t *ptPackMan,
        unsigned int value,
        unsigned int nBitsToPack)
{
  int nNextBitWrite; // esi
  int v6; // ecx
  unsigned int *buffer; // edx
  unsigned int result; // eax

  nNextBitWrite = ptPackMan->nNextBitWrite;
  v6 = nNextBitWrite % 32;
  buffer = ptPackMan->buffer;
  ptPackMan->nNextBitWrite = nBitsToPack + nNextBitWrite;
  result = (unsigned int)&buffer[nNextBitWrite / 32];
  if ( nNextBitWrite % 32 > 0 )
  {
    *(_DWORD *)result |= value << v6;
    if ( 32 - v6 >= (int)nBitsToPack )
      return result;
    result += 4;
    value >>= 32 - v6;
  }
  *(_DWORD *)result = value;
  return result;
}

// source: j/0/network/packman.c:164  [anchor-hash]
int __cdecl PackMan_Length(struct PackMan_t *ptPackMan)
{
  return (ptPackMan->nNextBitWrite + 7) / 8;
}

// source: j/0/network/packman.c:190  [anchor-callee]
unsigned int __cdecl PackMan_Unpack(struct PackMan_t *ptPackMan, unsigned int nBitsToUnpack)
{
  int nNextBitRead; // ecx
  int v5; // esi
  unsigned int *v6; // edx
  unsigned int v8; // eax

  nNextBitRead = ptPackMan->nNextBitRead;
  v5 = nNextBitRead % 32;
  v6 = &ptPackMan->buffer[nNextBitRead / 32];
  ptPackMan->nNextBitRead = nBitsToUnpack + nNextBitRead;
  if ( !(nNextBitRead % 32) )
    return *v6 & (0xFFFFFFFF >> (32 - nBitsToUnpack));
  v8 = 0xFFFFFFFF >> (64 - v5 - nBitsToUnpack);
  if ( 32 - v5 < nBitsToUnpack )
    return (*v6 >> v5) | ((v6[1] & v8) << (32 - v5));
  else
    return (*v6 & v8) >> v5;
}
