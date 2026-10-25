/* g/0/compress.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: g/0/compress.c:40  [size]
struct CompressBitStream_t *__cdecl Compress_OpenOutputBitStream(
        struct CompressBitStream_t *ptStream,
        void *pxDest)
{
  ptStream->pxCurrent = (unsigned __int8 *)pxDest;
  ptStream->nRack = 0;
  ptStream->bMask = 128;
  return ptStream;
}

// source: g/0/compress.c:56  [anchor-hash]
struct CompressBitStream_t *__cdecl Compress_CloseOutputBitStream(
        struct CompressBitStream_t *ptStream)
{
  if ( ptStream->bMask != 128 )
    *ptStream->pxCurrent++ = ptStream->nRack;
  return ptStream;
}

// source: g/0/compress.c:73  [size]
struct CompressBitStream_t *__cdecl Compress_OpenInputBitStream(
        struct CompressBitStream_t *ptStream,
        void *pxInput)
{
  ptStream->pxCurrent = (unsigned __int8 *)pxInput;
  ptStream->nRack = 0;
  ptStream->bMask = 128;
  return ptStream;
}

// source: g/0/compress.c:89  [size]
void __cdecl Compress_CloseInputBitStream(struct CompressBitStream_t *ptStream)
{
  ;
}

// source: g/0/compress.c:104  [anchor-mhash]
struct CompressBitStream_t *__cdecl Compress_OutputBit(
        struct CompressBitStream_t *ptOutputStream,
        int nBit)
{
  int v2; // ecx

  if ( nBit )
    ptOutputStream->nRack |= ptOutputStream->bMask;
  v2 = ptOutputStream->bMask >> 1;
  ptOutputStream->bMask = v2;
  if ( !v2 )
  {
    *ptOutputStream->pxCurrent++ = ptOutputStream->nRack;
    ptOutputStream->nRack = 0;
    ptOutputStream->bMask = 128;
  }
  return ptOutputStream;
}

// source: g/0/compress.c:131  [anchor-mhash]
struct CompressBitStream_t *__cdecl Compress_OutputBits(
        struct CompressBitStream_t *ptOutputStream,
        unsigned int nCode,
        int nCount)
{
  unsigned int i; // edx
  int v4; // ecx

  for ( i = 1 << (nCount - 1); i; i >>= 1 )
  {
    if ( (i & nCode) != 0 )
      ptOutputStream->nRack |= ptOutputStream->bMask;
    v4 = ptOutputStream->bMask >> 1;
    ptOutputStream->bMask = v4;
    if ( !v4 )
    {
      *ptOutputStream->pxCurrent++ = ptOutputStream->nRack;
      ptOutputStream->nRack = 0;
      ptOutputStream->bMask = 128;
    }
  }
  return ptOutputStream;
}

// source: g/0/compress.c:165  [anchor-hash]
int __cdecl Compress_InputBit(struct CompressBitStream_t *ptInputStream)
{
  int bMask; // ecx
  unsigned __int8 *v2; // edx
  int v3; // edx
  int v4; // ecx

  bMask = ptInputStream->bMask;
  if ( bMask == 128 )
  {
    v2 = ptInputStream->pxCurrent + 1;
    ptInputStream->nRack = *ptInputStream->pxCurrent;
    ptInputStream->pxCurrent = v2;
  }
  v3 = bMask & ptInputStream->nRack;
  v4 = bMask >> 1;
  ptInputStream->bMask = v4;
  if ( !v4 )
    ptInputStream->bMask = 128;
  return v3 != 0;
}

// source: g/0/compress.c:196  [anchor-mhash]
unsigned int __cdecl Compress_InputBits(
        struct CompressBitStream_t *ptInputStream,
        int nBitCount)
{
  unsigned int v2; // esi
  unsigned int result; // eax
  int bMask; // ecx
  unsigned __int8 *v5; // edi
  int v6; // ecx

  v2 = 1 << (nBitCount - 1);
  result = 0;
  while ( v2 )
  {
    bMask = ptInputStream->bMask;
    if ( bMask == 128 )
    {
      v5 = ptInputStream->pxCurrent + 1;
      ptInputStream->nRack = *ptInputStream->pxCurrent;
      ptInputStream->pxCurrent = v5;
    }
    if ( (bMask & ptInputStream->nRack) != 0 )
      result |= v2;
    v6 = bMask >> 1;
    v2 >>= 1;
    ptInputStream->bMask = v6;
    if ( !v6 )
      ptInputStream->bMask = 128;
  }
  return result;
}

// source: g/0/compress.c:237  [size]
struct CompressAlgorithm_t *__cdecl Compress_RegisterAlgorithm(
        enum CompressAlgorithm_e eAlgo,
        struct CompressAlgorithm_t *ptAlgorithm)
{
  Compress_aptAlgorithm[eAlgo] = ptAlgorithm;
  return ptAlgorithm;
}

// source: g/0/compress.c:253  [anchor-mhash]
int __cdecl Compress_Encode(
        enum CompressAlgorithm_e eAlgo,
        int nBytes,
        void *pxSource,
        void *pxDest)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct CompressBitStream_t tOutputStream; };
    struct { char igi2_o1[12]; struct CompressBitStream_t tInputStream; };
    char igi2_extent[24];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct CompressAlgorithm_t *v4; // esi
  int v5; // edi
  void (__cdecl *pfDeInitEncode)(void *); // esi

  v4 = Compress_aptAlgorithm[eAlgo];
  v5 = 0;
  igi2_frame.tInputStream.pxCurrent = (unsigned __int8 *)pxSource;
  igi2_frame.tInputStream.nRack = 0;
  igi2_frame.tInputStream.bMask = 128;
  igi2_frame.tOutputStream.pxCurrent = (unsigned __int8 *)pxDest;
  igi2_frame.tOutputStream.nRack = 0;
  igi2_frame.tOutputStream.bMask = 128;
  if ( v4->pfInitEncode )
    v5 = (int)v4->pfInitEncode(nBytes, pxSource);
  Compress_OutputBits(&igi2_frame.tOutputStream, eAlgo, 8);
  v4->pfEncode((void *)v5, nBytes, &igi2_frame.tInputStream, &igi2_frame.tOutputStream);
  pfDeInitEncode = v4->pfDeInitEncode;
  if ( pfDeInitEncode )
    pfDeInitEncode((void *)v5);
  if ( igi2_frame.tOutputStream.bMask != 128 )
    *igi2_frame.tOutputStream.pxCurrent++ = igi2_frame.tOutputStream.nRack;
  return igi2_frame.tOutputStream.pxCurrent - (unsigned __int8 *)pxDest;
}

// source: g/0/compress.c:306  [anchor-mhash]
int __cdecl Compress_Decode(void *pxSource, void *pxDest)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct CompressBitStream_t tOutputStream; };
    struct { char igi2_o1[12]; struct CompressBitStream_t tInputStream; };
    char igi2_extent[24];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  struct CompressAlgorithm_t *v3; // esi
  void *(__cdecl *pfInitDecode)(void *); // eax
  void *v5; // edi
  void (__cdecl *pfDeInitDecode)(void *); // esi

  igi2_frame.tInputStream.pxCurrent = (unsigned __int8 *)pxSource;
  igi2_frame.tInputStream.nRack = 0;
  igi2_frame.tInputStream.bMask = 128;
  igi2_frame.tOutputStream.pxCurrent = (unsigned __int8 *)pxDest;
  igi2_frame.tOutputStream.nRack = 0;
  igi2_frame.tOutputStream.bMask = 128;
  v3 = Compress_aptAlgorithm[Compress_InputBits(&igi2_frame.tInputStream, 8)];
  pfInitDecode = v3->pfInitDecode;
  if ( pfInitDecode )
    v5 = pfInitDecode(pxSource);
  else
    v5 = pxDest;
  v3->pfDecode(v5, &igi2_frame.tInputStream, &igi2_frame.tOutputStream);
  pfDeInitDecode = v3->pfDeInitDecode;
  if ( pfDeInitDecode )
    pfDeInitDecode(v5);
  if ( igi2_frame.tOutputStream.bMask != 128 )
    *igi2_frame.tOutputStream.pxCurrent++ = igi2_frame.tOutputStream.nRack;
  return igi2_frame.tOutputStream.pxCurrent - (unsigned __int8 *)pxDest;
}

// source: g/0/compress.c:357  [size]
void __cdecl Compress_Open()
{
  ;
}

// source: g/0/compress.c:372  [size]
void __cdecl Compress_Close()
{
  ;
}
