/* b/1/random.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: b/1/random.c:44  [size]
void __cdecl Random_Open()
{
  ;
}

// source: b/1/random.c:65  [size]
void __cdecl Random_Close()
{
  ;
}

// source: b/1/random.c:81  [anchor-hash]
struct RandomState_s *__cdecl Random_InitState(struct RandomState_s *ptRandomState)
{
  ptRandomState->anRandom[0] = -923067897;
  ptRandomState->anRandom[1] = 971667286;
  ptRandomState->anRandom[2] = 2146516173;
  return ptRandomState;
}

// source: b/1/random.c:99  [anchor-hash]
unsigned int __cdecl Random_GetRandomNumber(struct RandomState_s *ptRandomState)
{
  unsigned int v1; // edx
  unsigned int v2; // edx
  unsigned int v3; // edx

  v1 = (ptRandomState->anRandom[0] >> 7) ^ ptRandomState->anRandom[2];
  ptRandomState->anRandom[2] = v1;
  v2 = v1 ^ ptRandomState->anRandom[1];
  ptRandomState->anRandom[1] = v2;
  v3 = v2 + ptRandomState->anRandom[0];
  ptRandomState->anRandom[0] = v3;
  return v3;
}

// source: b/1/random.c:120  [anchor-callee]
float __cdecl Random_GetRandomNumberReal32(struct RandomState_s *ptRandomState)
{
  unsigned int v1; // edx
  unsigned int v2; // edx
  unsigned int v3; // edx

  v1 = (ptRandomState->anRandom[0] >> 7) ^ ptRandomState->anRandom[2];
  ptRandomState->anRandom[2] = v1;
  v2 = v1 ^ ptRandomState->anRandom[1];
  ptRandomState->anRandom[1] = v2;
  v3 = v2 + ptRandomState->anRandom[0];
  ptRandomState->anRandom[0] = v3;
  return (double)(unsigned __int16)v3 * 0.0000152587890625;
}

// source: b/1/random.c:149  [anchor-hash]
double __cdecl Random_GetRandomNumberReal64(struct RandomState_s *ptRandomState)
{
  unsigned int v1; // edx
  unsigned int v2; // edx
  unsigned int v3; // edx

  v1 = (ptRandomState->anRandom[0] >> 7) ^ ptRandomState->anRandom[2];
  ptRandomState->anRandom[2] = v1;
  v2 = v1 ^ ptRandomState->anRandom[1];
  ptRandomState->anRandom[1] = v2;
  v3 = v2 + ptRandomState->anRandom[0];
  ptRandomState->anRandom[0] = v3;
  return (double)(unsigned __int16)v3 * 0.0000152587890625;
}

// source: b/1/random.c:177  [anchor-callee]
unsigned int __cdecl Random_GetRandomNumberBelowLimit(struct RandomState_s *ptRandomState, int nLimit)
{
  unsigned int v2; // edx
  unsigned int v3; // edx
  unsigned int v4; // edx

  v2 = (ptRandomState->anRandom[0] >> 7) ^ ptRandomState->anRandom[2];
  ptRandomState->anRandom[2] = v2;
  v3 = v2 ^ ptRandomState->anRandom[1];
  ptRandomState->anRandom[1] = v3;
  v4 = v3 + ptRandomState->anRandom[0];
  ptRandomState->anRandom[0] = v4;
  return v4 % nLimit;
}

// source: b/1/random.c:196  [anchor-hash]
char __cdecl Random_GetRandomDigitOrLetter(struct RandomState_s *ptRandomState)
{
  unsigned int v1; // edx
  unsigned int v2; // edx
  unsigned int v3; // edx
  unsigned int v4; // edx

  v1 = (ptRandomState->anRandom[0] >> 7) ^ ptRandomState->anRandom[2];
  ptRandomState->anRandom[2] = v1;
  v2 = v1 ^ ptRandomState->anRandom[1];
  ptRandomState->anRandom[1] = v2;
  v3 = v2 + ptRandomState->anRandom[0];
  ptRandomState->anRandom[0] = v3;
  v4 = v3 % 0x3E;
  if ( (unsigned __int8)v4 <= 9u )
    return v4 + 48;
  if ( (unsigned __int8)v4 > 0x23u )
    return v4 + 61;
  return v4 + 55;
}

// source: b/1/random.c:238  [anchor-hash]
enum bool __cdecl Random_GetRandomBool(struct RandomState_s *ptRandomState)
{
  unsigned int v1; // edx
  unsigned int v2; // edx
  unsigned int v3; // edx

  v1 = (ptRandomState->anRandom[0] >> 7) ^ ptRandomState->anRandom[2];
  ptRandomState->anRandom[2] = v1;
  v2 = v1 ^ ptRandomState->anRandom[1];
  ptRandomState->anRandom[1] = v2;
  v3 = v2 + ptRandomState->anRandom[0];
  ptRandomState->anRandom[0] = v3;
  return (v3 & 1) == 0;
}

// source: b/1/random.c:254  [anchor-mhash]
unsigned int __cdecl Random_RandomizeState(
        struct RandomState_s *ptRandomState,
        unsigned int nSeed)
{
  unsigned int result; // eax

  ptRandomState->anRandom[0] = nSeed ^ 0xC8FB1A07;
  ptRandomState->anRandom[1] = (nSeed << 15) + 971667286;
  result = nSeed << 9;
  ptRandomState->anRandom[2] = 2146516173 - result;
  return result;
}
