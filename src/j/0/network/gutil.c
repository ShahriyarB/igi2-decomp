/* j/0/network/gutil.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/network/gutil.c:29  [size]
unsigned __int8 *__cdecl swap_byte__gutil(unsigned __int8 *a, unsigned __int8 *b)
{
  unsigned __int8 v2; // dl

  v2 = *a;
  *a = *b;
  *b = v2;
  return b;
}

// source: j/0/network/gutil.c:38  [size]
unsigned __int8 __cdecl encode_ct__gutil(unsigned __int8 c)
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

// source: j/0/network/gutil.c:49  [anchor-callee]
void __cdecl cengine_gs_encode(unsigned __int8 *ins, int size, unsigned __int8 *result)
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

// source: j/0/network/gutil.c:70  [anchor-callee]
int __cdecl cengine_gs_encrypt(
        unsigned __int8 *key,
        int key_len,
        unsigned __int8 *buffer_ptr,
        int buffer_len)
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

// source: j/0/network/gutil.c:145  [anchor-callee]
unsigned int __cdecl crypt_seek(
        struct crypt_key *L,
        unsigned int tree_num,
        unsigned int leaf_num)
{
  unsigned int v3; // edx
  unsigned int v4; // eax
  int v5; // ebx
  unsigned int v6; // edi
  unsigned int v7; // edx
  unsigned int v8; // eax
  unsigned int v9; // edx
  unsigned int v10; // edx
  unsigned int v11; // esi
  unsigned int v12; // eax
  unsigned int v13; // esi

  v3 = tree_num;
  v4 = 0;
  v5 = 0x8000;
  v6 = 1;
  L->index = 0;
  do
  {
    v7 = v6 + v3;
    v8 = v7 + v4;
    v9 = v8 + v7;
    if ( (v5 & leaf_num) != 0 )
    {
      v10 = L->F[(unsigned __int8)((unsigned __int16)~(_WORD)v9 >> 8)] ^ ((~v9 >> 8) | (~v9 << 24));
      v11 = L->F[(unsigned __int8)v8] ^ v8;
      v3 = L->F[BYTE1(v10)] ^ ((v10 >> 8) | (v10 << 24));
      v6 = 2 * v6 + 1;
      v4 = ((L->F[HIBYTE(v11)] ^ ((v11 << 8) | HIBYTE(v11))) << 8)
         | ((unsigned __int64)(L->F[HIBYTE(v11)] ^ ((v11 << 8) | HIBYTE(v11))) >> 24);
    }
    else
    {
      L->x_stack[L->index] = v9;
      L->y_stack[L->index] = v8;
      L->z_stack[L->index++] = v6;
      v12 = L->F[BYTE1(v8)] ^ ((v8 >> 8) | (v8 << 24));
      v13 = L->F[(unsigned __int8)v9] ^ v9;
      v4 = L->F[BYTE1(v12)] ^ ((v12 >> 8) | (v12 << 24));
      v3 = ((L->F[HIBYTE(v13)] ^ ((v13 << 8) | HIBYTE(v13))) << 8)
         | ((unsigned __int64)(L->F[HIBYTE(v13)] ^ ((v13 << 8) | HIBYTE(v13))) >> 24);
      v6 *= 2;
    }
    v5 >>= 1;
  }
  while ( v5 > 0 );
  L->z = v6;
  L->tree_num = tree_num;
  L->y = v4;
  L->x = v3;
  return v3 ^ v4;
}

// source: j/0/network/gutil.c:185  [anchor-callee]
int __cdecl crypt_encrypt(struct crypt_key *L, unsigned int *dest, int nodes)
{
  unsigned int y; // ecx
  unsigned int *v4; // edx
  int result; // eax
  int index; // ebp
  unsigned int z; // edi
  unsigned int *v8; // ebx
  int v9; // eax
  unsigned int v10; // ecx
  unsigned int v11; // eax
  unsigned int v12; // ecx
  unsigned int v13; // edx
  unsigned int v14; // eax
  unsigned __int64 v15; // kr08_8
  unsigned int v16; // ecx
  unsigned int *dest_max; // [esp+Ch] [ebp-4h]

  y = L->y;
  v4 = &dest[nodes];
  result = L->x;
  index = L->index;
  z = L->z;
  for ( dest_max = v4; dest < dest_max; z = 2 * L->z_stack[index] + 1 )
  {
    if ( z < 0x10000 )
    {
      v8 = &L->y_stack[index];
      do
      {
        v9 = z + result;
        v10 = v9 + y;
        v11 = v10 + v9;
        *v8 = v10;
        *(v8 - 16) = v11;
        v8[16] = z;
        z *= 2;
        v12 = L->F[BYTE1(v10)] ^ ((v10 >> 8) | (v10 << 24));
        v13 = L->F[(unsigned __int8)v11] ^ v11;
        y = L->F[BYTE1(v12)] ^ ((v12 >> 8) | (v12 << 24));
        ++index;
        ++v8;
        result = ((L->F[HIBYTE(v13)] ^ ((v13 << 8) | HIBYTE(v13))) << 8)
               | ((unsigned __int64)(L->F[HIBYTE(v13)] ^ ((v13 << 8) | HIBYTE(v13))) >> 24);
      }
      while ( z < 0x10000 );
    }
    *dest = result ^ y;
    --index;
    ++dest;
    if ( index < 0 )
      index = 0;
    v14 = L->F[(unsigned __int8)((unsigned __int16)~LOWORD(L->x_stack[index]) >> 8)]
        ^ ((~L->x_stack[index] >> 8) | (~L->x_stack[index] << 24));
    v15 = (unsigned __int64)(L->F[(unsigned __int8)L->y_stack[index]] ^ L->y_stack[index]) << 8;
    result = L->F[BYTE1(v14)] ^ ((v14 >> 8) | (v14 << 24));
    v16 = L->F[(unsigned __int8)(v15 | BYTE4(v15))] ^ (v15 | HIDWORD(v15));
    y = (v16 << 8) | HIBYTE(v16);
  }
  L->z = z;
  L->index = index;
  L->x = result;
  L->y = y;
  return result;
}

// source: j/0/network/gutil.c:222  [anchor-callee]
void __cdecl init_crypt_key(unsigned __int8 *key, unsigned int bytes_in_key, struct crypt_key *L)
{
  int i; // eax
  unsigned int v4; // edi
  unsigned int *v5; // ecx
  int v6; // eax
  int v7; // eax
  unsigned int v8; // edx
  int v9; // eax
  int k; // eax
  char index; // [esp+8h] [ebp-14h]
  unsigned __int8 indexa; // [esp+8h] [ebp-14h]
  unsigned __int8 indexb; // [esp+8h] [ebp-14h]
  unsigned __int8 indexc; // [esp+8h] [ebp-14h]
  unsigned __int8 indexd; // [esp+8h] [ebp-14h]
  unsigned __int8 indexe; // [esp+8h] [ebp-14h]
  int j; // [esp+Ch] [ebp-10h]
  unsigned int v18; // [esp+10h] [ebp-Ch]
  unsigned int v19; // [esp+10h] [ebp-Ch]
  unsigned int v20; // [esp+10h] [ebp-Ch]
  unsigned int v21; // [esp+10h] [ebp-Ch]
  unsigned int v22; // [esp+10h] [ebp-Ch]
  unsigned int v23; // [esp+10h] [ebp-Ch]
  unsigned int v24; // [esp+10h] [ebp-Ch]
  unsigned int v25; // [esp+10h] [ebp-Ch]
  int v26; // [esp+14h] [ebp-8h]
  int v27; // [esp+18h] [ebp-4h]

  L->keyptr = nullptr;
  memset(L, 0, 0x400u);
  for ( j = 0; j < 4; ++j )
  {
    for ( i = 0; i < 256; ++i )
      L->F[i] = i + (L->F[i] << 8);
    index = j;
    v27 = 2;
    do
    {
      v4 = 2;
      v5 = &L->F[2];
      v26 = 32;
      do
      {
        v18 = *(v5 - 2);
        indexa = index + v18 + key[(v4 - 2) % bytes_in_key];
        *(v5 - 2) = L->F[indexa];
        L->F[indexa] = v18;
        v19 = *(v5 - 1);
        indexb = indexa + v19 + key[(v4 - 1) % bytes_in_key];
        *(v5 - 1) = L->F[indexb];
        L->F[indexb] = v19;
        v20 = *v5;
        indexc = indexb + *v5 + key[v4 % bytes_in_key];
        *v5 = L->F[indexc];
        L->F[indexc] = v20;
        v21 = v5[1];
        indexd = indexc + v21 + key[(v4 + 1) % bytes_in_key];
        v5[1] = L->F[indexd];
        L->F[indexd] = v21;
        v22 = v5[2];
        indexe = indexd + v22 + key[(v4 + 2) % bytes_in_key];
        v5[2] = L->F[indexe];
        L->F[indexe] = v22;
        v23 = v5[3];
        v5 += 8;
        v6 = (unsigned __int8)(indexe + v23 + key[(v4 + 3) % bytes_in_key]);
        *(v5 - 5) = L->F[v6];
        L->F[v6] = v23;
        v24 = *(v5 - 4);
        v7 = (unsigned __int8)(v6 + v24 + key[(v4 + 4) % bytes_in_key]);
        *(v5 - 4) = L->F[v7];
        L->F[v7] = v24;
        v25 = *(v5 - 3);
        v8 = (v4 + 5) % bytes_in_key;
        v4 += 8;
        v9 = (unsigned __int8)(v7 + v25 + key[v8]);
        *(v5 - 3) = L->F[v9];
        index = v9;
        L->F[v9] = v25;
        --v26;
      }
      while ( v26 );
      --v27;
    }
    while ( v27 );
  }
  for ( k = 0; k < 256; ++k )
    L->F[k] ^= k;
  crypt_seek(L, 0, 0);
}

// source: j/0/network/gutil.c:255  [anchor-callee]
struct crypt_key *__cdecl crypt_docrypt(struct crypt_key *L, unsigned __int8 *data, int datalen)
{
  int v3; // edi
  struct crypt_key *i; // esi
  unsigned __int8 *keyptr; // eax

  v3 = 0;
  for ( i = L; v3 < datalen; ++i->keyptr )
  {
    keyptr = i->keyptr;
    if ( !keyptr || (unsigned int)(keyptr - (unsigned __int8 *)i - 1236) >= 0x3F )
    {
      i->keyptr = (unsigned __int8 *)i->keydata;
      crypt_encrypt(i, i->keydata, 16);
    }
    L = (struct crypt_key *)i->keyptr;
    data[v3++] ^= LOBYTE(L->F[0]);
  }
  return L;
}
