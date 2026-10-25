/* Helpers the decompiler's output uses: fixed-width aliases, byte/word extraction, rotates and
   carry/overflow tests. Written for MSVC x86 C17. */
#pragma once

#include <stdint.h>
#include <string.h>
#include <intrin.h>
#include <float.h>

#define nullptr ((void *)0)

typedef uint8_t _BYTE;
typedef uint16_t _WORD;
typedef uint32_t _DWORD;
typedef uint64_t _QWORD;
/* Hex-Rays' 1-byte bool. Not <stdbool.h>: its true/false macros would break the game's own
   "enum bool { false, true }" (the tag lives in a separate namespace from this typedef). */
typedef unsigned char bool;
typedef int _BOOL4;
typedef unsigned char _BOOL1;
typedef char _UNKNOWN;
typedef unsigned char _OWORD[16];
typedef struct { uint32_t d[4]; } IGI2_INT128;   /* a 16-byte local the decompiler typed __int128 */

/* Hex-Rays' absolute-address access, e.g. MEMORY[0] (a null dereference in the original) */
#define MEMORY ((_DWORD *)0)

/* parts of a value, little-endian; windows.h has read-only versions of some of these */
#undef LOBYTE
#undef HIBYTE
#undef LOWORD
#undef HIWORD
#define BYTEn(x, n)   (*((_BYTE *)&(x) + (n)))
#define WORDn(x, n)   (*((_WORD *)&(x) + (n)))
#define DWORDn(x, n)  (*((_DWORD *)&(x) + (n)))
#define LOBYTE(x)     BYTEn(x, 0)
#define HIBYTE(x)     BYTEn(x, sizeof(x) - 1)
#define BYTE1(x)      BYTEn(x, 1)
#define BYTE2(x)      BYTEn(x, 2)
#define BYTE3(x)      BYTEn(x, 3)
#define BYTE4(x)      BYTEn(x, 4)
#define BYTE5(x)      BYTEn(x, 5)
#define BYTE6(x)      BYTEn(x, 6)
#define BYTE7(x)      BYTEn(x, 7)
#define BYTE8(x)      BYTEn(x, 8)
#define BYTE9(x)      BYTEn(x, 9)
#define BYTE10(x)     BYTEn(x, 10)
#define BYTE11(x)     BYTEn(x, 11)
#define BYTE12(x)     BYTEn(x, 12)
#define BYTE13(x)     BYTEn(x, 13)
#define BYTE14(x)     BYTEn(x, 14)
#define BYTE15(x)     BYTEn(x, 15)
#define WORD2(x)      WORDn(x, 2)
#define WORD3(x)      WORDn(x, 3)
#define SBYTE2(x)     (*((int8_t *)&(x) + 2))
#define SBYTE3(x)     (*((int8_t *)&(x) + 3))
#define SWORD1(x)     (*((int16_t *)&(x) + 1))
#define LOWORD(x)     WORDn(x, 0)
#define HIWORD(x)     WORDn(x, sizeof(x) / 2 - 1)
#define WORD1(x)      WORDn(x, 1)
#define LODWORD(x)    DWORDn(x, 0)
#define HIDWORD(x)    DWORDn(x, 1)
#define SLOBYTE(x)    (*((int8_t *)&(x)))
#define SHIBYTE(x)    (*((int8_t *)&(x) + sizeof(x) - 1))
#define SBYTE1(x)     (*((int8_t *)&(x) + 1))
#define SLOWORD(x)    (*((int16_t *)&(x)))
#define SHIWORD(x)    (*((int16_t *)&(x) + sizeof(x) / 2 - 1))
#define SLODWORD(x)   (*((int32_t *)&(x)))
#define SHIDWORD(x)   (*((int32_t *)&(x) + 1))

#define __PAIR64__(hi, lo)  (((uint64_t)(uint32_t)(hi) << 32) | (uint32_t)(lo))
#define __SPAIR64__(hi, lo) ((int64_t)__PAIR64__(hi, lo))

static __inline uint8_t  __ROL1__(uint8_t v, int n)  { return _rotl8(v, (unsigned char)n); }
static __inline uint16_t __ROL2__(uint16_t v, int n) { return _rotl16(v, (unsigned char)n); }
static __inline uint32_t __ROL4__(uint32_t v, int n) { return _rotl(v, n); }
static __inline uint8_t  __ROR1__(uint8_t v, int n)  { return _rotr8(v, (unsigned char)n); }
static __inline uint16_t __ROR2__(uint16_t v, int n) { return _rotr16(v, (unsigned char)n); }
static __inline uint32_t __ROR4__(uint32_t v, int n) { return _rotr(v, n); }

/* reinterpret bits */
static __inline float    __coerce_float(uint32_t v)  { float f; memcpy(&f, &v, 4); return f; }
static __inline uint32_t __coerce_u32(float f)       { uint32_t v; memcpy(&v, &f, 4); return v; }
static __inline double   __coerce_double(uint64_t v) { double d; memcpy(&d, &v, 8); return d; }
#define COERCE_FLOAT(v)        __coerce_float((uint32_t)(v))
#define COERCE_UNSIGNED_INT(f) __coerce_u32(f)
#define COERCE_DOUBLE(v)       __coerce_double((uint64_t)(v))
static __inline uint64_t __coerce_u64(double d) { uint64_t v; memcpy(&v, &d, 8); return v; }
#define COERCE_UNSIGNED_INT64(v) __coerce_u64(v)

/* flags of an add/sub the decompiler could not fold into a comparison */
#define __CFADD__(a, b)  ((uint32_t)(a) + (uint32_t)(b) < (uint32_t)(a))
#define __CFSUB__(a, b)  ((uint32_t)(a) < (uint32_t)(b))
#define __OFADD__(a, b)  ((((int32_t)(a) + (int32_t)(b)) ^ (int32_t)(a)) & (((int32_t)(a) + (int32_t)(b)) ^ (int32_t)(b)) & 0x80000000u ? 1 : 0)
#define __OFSUB__(a, b)  (((((int32_t)(a) - (int32_t)(b)) ^ (int32_t)(a)) & ((int32_t)(a) ^ (int32_t)(b)) & 0x80000000u) ? 1 : 0)

#define abs32(x) abs(x)
#define abs64(x) _abs64(x)
static __inline int8_t abs8(int8_t x) { return (int8_t)(x < 0 ? -x : x); }

/* x87 compare results are tested through the parity flag: PF is set when the low byte of
   x - y has an even number of one bits */
static __inline int8_t __SETP__(int x, int y)
{
    uint8_t b = (uint8_t)(x - y);
    b ^= b >> 4;
    b ^= b >> 2;
    b ^= b >> 1;
    return (int8_t)!(b & 1);
}

/* block moves the decompiler recognised (rep movsd / rep stosd) */
#define qmemcpy memcpy
/* a float with exact bits: what the decompiler prints as "NAN" was a specific pattern
   (0xFFFFFFFF, the int -1), and C's NAN is another one */
#define IGI2_FLOAT_BITS(bits) (((union { uint32_t u; float f; }){ .u = (bits) }).f)
#define IGI2_DOUBLE_BITS(bits) (((union { uint64_t u; double d; }){ .u = (bits) }).d)
/* "fstcw cw; or cw, bits; fldcw cw": the game sets the x87 rounding mode to truncate (0C00h)
   before App_Open, before every App_Run, and after anything that may reset it (Direct3D, movies).
   The decompiler keeps only the "or" on the saved word, so the FPU was never switched and every
   operation rounded to nearest where the original truncates (the terrain line trace never ended).
   Returns the new word, which the game keeps in Real_nTempCW. */
static __inline int16_t igi2_fpu_or(uint16_t bits)
{
    uint16_t cw;
    __asm fstcw cw
    cw |= bits;
    __asm fldcw cw
    return (int16_t)cw;
}

/* The game's sqrt, sin, cos, tan and atan2 are the x87 instructions themselves (fsqrt 494 times,
   fsin 143, fcos 142, fptan 47, fpatan 26: the decompiler prints them as these calls), executed
   under the rounding and precision the game sets. Today's runtime functions compute with their
   own precision: the terrain normal came out 2 units in the last place off on every vertex. The
   result is left on the x87 stack, where a double function returns it. */
#include <math.h>
#pragma warning(push)
#pragma warning(disable: 4035)  /* no return statement: the value is in st(0) */
static __inline double igi2_fsqrt(double x) { __asm fld x __asm fsqrt }
static __inline double igi2_fsin(double x) { __asm fld x __asm fsin }
static __inline double igi2_fcos(double x) { __asm fld x __asm fcos }
static __inline double igi2_ftan(double x) { __asm fld x __asm fptan __asm fstp st(0) }
static __inline double igi2_fatan2(double y, double x) { __asm fld y __asm fld x __asm fpatan }
#pragma warning(pop)
#define sqrt(x) igi2_fsqrt(x)
#define sin(x) igi2_fsin(x)
#define cos(x) igi2_fcos(x)
#define tan(x) igi2_ftan(x)
#define atan2(y, x) igi2_fatan2(y, x)

static __inline void *memset32(void *dst, uint32_t value, size_t count)
{
    uint32_t *p = (uint32_t *)dst;
    while (count--)
        *p++ = value;
    return dst;
}

/* -DIGI2_GUARD_HEAP=ON: the game's allocations end at an inaccessible page (support/guardheap.c) */
#ifdef IGI2_GUARD_HEAP
void *igi2_guard_malloc(size_t n);
void igi2_guard_free(void *p);
void *igi2_guard_realloc(void *p, size_t n);
#define malloc igi2_guard_malloc
#define free igi2_guard_free
#define realloc igi2_guard_realloc
#endif
