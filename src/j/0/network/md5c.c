/* j/0/network/md5c.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/network/md5c.c:104  [anchor-hash]
struct MD5_CTX *__cdecl MD5Init(struct MD5_CTX *context)
{
  context->count[1] = 0;
  context->count[0] = 0;
  context->state[0] = 1732584193;
  context->state[1] = -271733879;
  context->state[2] = -1732584194;
  context->state[3] = 271733878;
  return context;
}

// source: j/0/network/md5c.c:122  [anchor-callee]
void __cdecl MD5Update(struct MD5_CTX *context, unsigned __int8 *input, unsigned int inputLen)
{
  unsigned int v3; // ecx
  unsigned int v4; // edx
  unsigned int v5; // eax
  unsigned int v6; // ebp
  unsigned int v7; // esi
  unsigned int i; // edi

  v3 = inputLen;
  v4 = context->count[0] + 8 * inputLen;
  v5 = (context->count[0] >> 3) & 0x3F;
  context->count[0] = v4;
  if ( v4 < 8 * inputLen )
    ++context->count[1];
  v6 = 64 - v5;
  context->count[1] += inputLen >> 29;
  if ( inputLen < 64 - v5 )
  {
    i = 0;
  }
  else
  {
    qmemcpy(&context->buffer[v5], input, v6);
    MD5Transform(context->state, context->buffer);
    v7 = v6 + 63;
    for ( i = v6; v7 < inputLen; i += 64 )
    {
      MD5Transform(context->state, &input[v7 - 63]);
      v7 += 64;
    }
    v3 = inputLen;
    v5 = 0;
  }
  qmemcpy(&context->buffer[v5], &input[i], v3 - i);
}

// source: j/0/network/md5c.c:160  [anchor-callee]
struct MD5_CTX *__cdecl MD5Final(unsigned __int8 *digest, struct MD5_CTX *context)
{
  unsigned int v3; // ecx
  unsigned __int8 *v4; // eax
  unsigned int v5; // ecx
  int v6; // eax
  unsigned __int8 *v7; // ecx
  unsigned __int8 *v8; // eax
  int v9; // esi
  unsigned __int8 bits[8]; // [esp+Ch] [ebp-8h] BYREF

  v3 = 0;
  v4 = (unsigned __int8 *)context->count + 2;
  do
  {
    bits[v3] = *(v4 - 2);
    bits[v3 + 1] = *(v4 - 1);
    bits[v3 + 2] = *v4;
    bits[v3 + 3] = v4[1];
    v3 += 4;
    v4 += 4;
  }
  while ( v3 < 8 );
  v5 = (context->count[0] >> 3) & 0x3F;
  v6 = 56;
  if ( v5 >= 0x38 )
    v6 = 120;
  MD5Update(context, PADDING, v6 - v5);
  MD5Update(context, bits, 8u);
  v7 = digest + 1;
  v8 = (unsigned __int8 *)context->state + 2;
  v9 = 4;
  do
  {
    *(v7 - 1) = *(v8 - 2);
    *v7 = *(v8 - 1);
    v7[1] = *v8;
    v7[2] = v8[1];
    v8 += 4;
    v7 += 4;
    --v9;
  }
  while ( v9 );
  memset(context, 0, sizeof(struct MD5_CTX));
  return nullptr;
}

// source: j/0/network/md5c.c:189  [anchor-callee]
void __cdecl MD5Transform(unsigned int *state, unsigned __int8 *block)
{
  unsigned __int8 *v2; // ecx
  unsigned int *v3; // esi
  int v4; // edi
  int v5; // ebx
  unsigned __int16 v6; // dx
  unsigned int v7; // esi
  unsigned int v8; // edi
  unsigned int v9; // edx
  unsigned int v10; // eax
  unsigned int v11; // eax
  unsigned int v12; // ecx
  unsigned int v13; // ecx
  unsigned int v14; // edx
  unsigned int v15; // edx
  unsigned int v16; // esi
  unsigned int v17; // esi
  unsigned int v18; // eax
  unsigned int v19; // eax
  unsigned int v20; // ecx
  unsigned int v21; // ecx
  unsigned int v22; // edx
  unsigned int v23; // edx
  unsigned int v24; // esi
  unsigned int v25; // esi
  unsigned int v26; // eax
  unsigned int v27; // eax
  unsigned int v28; // ecx
  int v29; // ecx
  unsigned int v30; // edx
  int v31; // edx
  unsigned int v32; // esi
  int v33; // esi
  unsigned int v34; // eax
  int v35; // eax
  unsigned int v36; // ecx
  int v37; // ecx
  unsigned int v38; // edx
  int v39; // edx
  unsigned int v40; // esi
  int v41; // esi
  unsigned int v42; // eax
  int v43; // eax
  unsigned int v44; // ecx
  int v45; // ecx
  unsigned int v46; // edx
  int v47; // edx
  unsigned int v48; // esi
  int v49; // esi
  unsigned int v50; // eax
  int v51; // eax
  unsigned int v52; // ecx
  int v53; // ecx
  int v54; // edx
  unsigned int v55; // esi
  int v56; // esi
  unsigned int v57; // eax
  int v58; // eax
  unsigned int v59; // ecx
  int v60; // ecx
  unsigned int v61; // edx
  int v62; // edx
  unsigned int v63; // esi
  int v64; // esi
  int v65; // eax
  unsigned int v66; // ecx
  int v67; // ecx
  unsigned int v68; // edx
  int v69; // edx
  unsigned int v70; // esi
  int v71; // esi
  unsigned int v72; // eax
  int v73; // eax
  unsigned int v74; // edi
  int v75; // edi
  int v76; // edx
  unsigned int v77; // ecx
  int v78; // ecx
  unsigned int v79; // eax
  int v80; // eax
  unsigned int v81; // esi
  int v82; // esi
  unsigned int v83; // edx
  int v84; // edx
  unsigned int v85; // ecx
  int v86; // ecx
  unsigned int v87; // eax
  int v88; // eax
  unsigned int v89; // esi
  int v90; // esi
  unsigned int v91; // edx
  int v92; // edi
  unsigned int v93; // ecx
  int v94; // ecx
  unsigned int v95; // eax
  int v96; // eax
  unsigned int v97; // edx
  int v98; // edx
  unsigned int v99; // esi
  int v100; // esi
  unsigned int v101; // ecx
  int v102; // ecx
  unsigned int v103; // eax
  int v104; // eax
  unsigned int v105; // edx
  int v106; // edx
  unsigned int v107; // esi
  int v108; // esi
  unsigned int v109; // ecx
  int v110; // ecx
  unsigned int v111; // eax
  int v112; // eax
  unsigned int v113; // edx
  int v114; // edx
  unsigned int v115; // esi
  int v116; // esi
  unsigned int v117; // ecx
  int v118; // ecx
  unsigned int v119; // eax
  int v120; // eax
  unsigned int v121; // edx
  int v122; // edx
  unsigned int v123; // esi
  int v124; // esi
  unsigned int v125; // ecx
  int v126; // ecx
  unsigned int v127; // eax
  int v128; // eax
  unsigned int v129; // edx
  int v130; // edx
  unsigned int v131; // edi
  int v132; // edi
  unsigned int v133; // ecx
  unsigned int x[16]; // [esp+14h] [ebp-40h] BYREF

  v2 = block + 2;
  v3 = x;
  v4 = 16;
  do
  {
    v5 = *(v2 - 1);
    HIBYTE(v6) = v2[1];
    ++v3;
    v2 += 4;
    LOBYTE(v6) = *(v2 - 4);
    --v4;
    *(v3 - 1) = *(v2 - 6) | ((v5 | (v6 << 8)) << 8);
  }
  while ( v4 );
  v7 = state[1];
  v8 = state[2];
  v9 = state[3];
  v10 = *state + x[0] + (v7 & v8 | v9 & ~v7) - 680876936;
  v11 = v7 + ((v10 << 7) | (v10 >> 25));
  v12 = v9 + x[1] + (v11 & v7 | v8 & ~v11) - 389564586;
  v13 = v11 + ((v12 << 12) | (v12 >> 20));
  v14 = v8 + x[2] + (v11 & v13 | v7 & ~v13) + 606105819;
  v15 = v13 + ((v14 << 17) | (v14 >> 15));
  v16 = v7 + x[3] + (v15 & v13 | v11 & ~v15) - 1044525330;
  v17 = v15 + ((v16 >> 10) | (v16 << 22));
  v18 = v11 + x[4] + (v17 & v15 | v13 & ~v17) - 176418897;
  v19 = v17 + ((v18 << 7) | (v18 >> 25));
  v20 = v13 + x[5] + (v19 & v17 | v15 & ~v19) + 1200080426;
  v21 = v19 + ((v20 << 12) | (v20 >> 20));
  v22 = v15 + x[6] + (v19 & v21 | v17 & ~v21) - 1473231341;
  v23 = v21 + ((v22 << 17) | (v22 >> 15));
  v24 = v17 + x[7] + (v23 & v21 | v19 & ~v23) - 45705983;
  v25 = v23 + ((v24 >> 10) | (v24 << 22));
  v26 = v19 + x[8] + (v25 & v23 | v21 & ~v25) + 1770035416;
  v27 = v25 + ((v26 << 7) | (v26 >> 25));
  v28 = v21 + x[9] + (v27 & v25 | v23 & ~v27) - 1958414417;
  v29 = v27 + ((v28 << 12) | (v28 >> 20));
  v30 = v23 + x[10] + (v27 & v29 | v25 & ~v29) - 42063;
  v31 = v29 + ((v30 << 17) | (v30 >> 15));
  v32 = v25 + x[11] + (v31 & v29 | v27 & ~v31) - 1990404162;
  v33 = v31 + ((v32 >> 10) | (v32 << 22));
  v34 = v27 + x[12] + (v33 & v31 | v29 & ~v33) + 1804603682;
  v35 = v33 + ((v34 << 7) | (v34 >> 25));
  v36 = v29 + x[13] + (v35 & v33 | v31 & ~v35) - 40341101;
  v37 = v35 + ((v36 << 12) | (v36 >> 20));
  v38 = v31 + x[14] + (v35 & v37 | v33 & ~v37) - 1502002290;
  v39 = v37 + ((v38 << 17) | (v38 >> 15));
  v40 = v33 + x[15] + (v39 & v37 | v35 & ~v39) + 1236535329;
  v41 = v39 + ((v40 >> 10) | (v40 << 22));
  v42 = v35 + x[1] + (v41 & v37 | v39 & ~v37) - 165796510;
  v43 = v41 + ((32 * v42) | (v42 >> 27));
  v44 = v37 + x[6] + (v43 & v39 | v41 & ~v39) - 1069501632;
  v45 = v43 + ((v44 << 9) | (v44 >> 23));
  v46 = v39 + x[11] + (v41 & v45 | v43 & ~v41) + 643717713;
  v47 = v45 + ((v46 << 14) | (v46 >> 18));
  v48 = v41 + x[0] + (v43 & v47 | v45 & ~v43) - 373897302;
  v49 = v47 + ((v48 >> 12) | (v48 << 20));
  v50 = v43 + x[5] + (v49 & v45 | v47 & ~v45) - 701558691;
  v51 = v49 + ((32 * v50) | (v50 >> 27));
  v52 = (unsigned int)&MTP_atLODVirModel[151].atBoneVertexRefs[23].atVertexRefs[286].iVertex
      + v45
      + x[10]
      + (v51 & v47 | v49 & ~v47)
      + 3;
  v53 = v51 + ((v52 << 9) | (v52 >> 23));
  v54 = v53
      + (((v47 + x[15] + (v49 & v53 | v51 & ~v49) - 660478335) << 14)
       | ((v47 + x[15] + (v49 & v53 | v51 & ~v49) - 660478335) >> 18));
  v55 = v49 + x[4] + (v51 & v54 | v53 & ~v51) - 405537848;
  v56 = v54 + ((v55 >> 12) | (v55 << 20));
  v57 = v51 + x[9] + (v56 & v53 | v54 & ~v53) + 568446438;
  v58 = v56 + ((32 * v57) | (v57 >> 27));
  v59 = v53 + x[14] + (v58 & v54 | v56 & ~v54) - 1019803690;
  v60 = v58 + ((v59 << 9) | (v59 >> 23));
  v61 = v54 + x[3] + (v56 & v60 | v58 & ~v56) - 187363961;
  v62 = v60 + ((v61 << 14) | (v61 >> 18));
  v63 = v56 + x[8] + (v58 & v62 | v60 & ~v58) + 1163531501;
  v64 = v62 + ((v63 >> 12) | (v63 << 20));
  v65 = v64
      + ((32 * (v58 + x[13] + (v64 & v60 | v62 & ~v60) - 1444681467))
       | ((v58 + x[13] + (v64 & v60 | v62 & ~v60) - 1444681467) >> 27));
  v66 = v60 + x[2] + (v65 & v62 | v64 & ~v62) - 51403784;
  v67 = v65 + ((v66 << 9) | (v66 >> 23));
  v68 = v62 + x[7] + (v64 & v67 | v65 & ~v64) + 1735328473;
  v69 = v67 + ((v68 << 14) | (v68 >> 18));
  v70 = v64 + x[12] + (v65 & v69 | v67 & ~v65) - 1926607734;
  v71 = v69 + ((v70 >> 12) | (v70 << 20));
  v72 = v65 + x[5] + (v71 ^ v69 ^ v67) - 378558;
  v73 = v71 + ((16 * v72) | (v72 >> 28));
  v74 = v67 + x[8] + (v73 ^ v71 ^ v69) - 2022574463;
  v75 = v73 + ((v74 << 11) | (v74 >> 21));
  v76 = v75
      + (((v69 + x[11] + (v73 ^ v71 ^ v75) + 1839030562) << 16) | ((v69 + x[11] + (v73 ^ v71 ^ v75) + 1839030562) >> 16));
  v77 = v71 + x[14] + (v73 ^ v76 ^ v75) - 35309556;
  v78 = v76 + ((v77 >> 9) | (v77 << 23));
  v79 = v73 + x[1] + (v78 ^ v76 ^ v75) - 1530992060;
  v80 = v78 + ((16 * v79) | (v79 >> 28));
  v81 = v75 + x[4] + (v80 ^ v78 ^ v76) + 1272893353;
  v82 = v80 + ((v81 << 11) | (v81 >> 21));
  v83 = v76 + x[7] + (v80 ^ v78 ^ v82) - 155497632;
  v84 = v82 + ((v83 << 16) | HIWORD(v83));
  v85 = v78 + x[10] + (v80 ^ v84 ^ v82) - 1094730640;
  v86 = v84 + ((v85 >> 9) | (v85 << 23));
  v87 = v80 + x[13] + (v86 ^ v84 ^ v82) + 681279174;
  v88 = v86 + ((16 * v87) | (v87 >> 28));
  v89 = v82 + x[0] + (v88 ^ v86 ^ v84) - 358537222;
  v90 = v88 + ((v89 << 11) | (v89 >> 21));
  v91 = v84 + x[3] + (v88 ^ v86 ^ v90) - 722521979;
  v92 = v90 + ((v91 << 16) | HIWORD(v91));
  v93 = (unsigned int)&MTP_atLODVirModel[341].atBoneVertexRefs[13].atVertexRefs[653].iVertex
      + v86
      + x[6]
      + (v88 ^ v92 ^ v90)
      + 1;
  v94 = v92 + ((v93 >> 9) | (v93 << 23));
  v95 = v88 + x[9] + (v94 ^ v92 ^ v90) - 640364487;
  v96 = v94 + ((16 * v95) | (v95 >> 28));
  v97 = v90 + x[12] + (v96 ^ v94 ^ v92) - 421815835;
  v98 = v96 + ((v97 << 11) | (v97 >> 21));
  v99 = v92 + x[15] + (v96 ^ v94 ^ v98) + 530742520;
  v100 = v98 + ((v99 << 16) | HIWORD(v99));
  v101 = v94 + x[2] + (v96 ^ v100 ^ v98) - 995338651;
  v102 = v100 + ((v101 >> 9) | (v101 << 23));
  v103 = v96 + x[0] + (v100 ^ (v102 | ~v98)) - 198630844;
  v104 = v102 + ((v103 << 6) | (v103 >> 26));
  v105 = v98 + x[7] + (v102 ^ (v104 | ~v100)) + 1126891415;
  v106 = v104 + ((v105 << 10) | (v105 >> 22));
  v107 = v100 + x[14] + (v104 ^ (v106 | ~v102)) - 1416354905;
  v108 = v106 + ((v107 << 15) | (v107 >> 17));
  v109 = v102 + x[5] + (v106 ^ (v108 | ~v104)) - 57434055;
  v110 = v108 + ((v109 >> 11) | (v109 << 21));
  v111 = v104 + x[12] + (v108 ^ (v110 | ~v106)) + 1700485571;
  v112 = v110 + ((v111 << 6) | (v111 >> 26));
  v113 = v106 + x[3] + (v110 ^ (v112 | ~v108)) - 1894986606;
  v114 = v112 + ((v113 << 10) | (v113 >> 22));
  v115 = v108 + x[10] + (v112 ^ (v114 | ~v110)) - 1051523;
  v116 = v114 + ((v115 << 15) | (v115 >> 17));
  v117 = v110 + x[1] + (v114 ^ (v116 | ~v112)) - 2054922799;
  v118 = v116 + ((v117 >> 11) | (v117 << 21));
  v119 = v112 + x[8] + (v116 ^ (v118 | ~v114)) + 1873313359;
  v120 = v118 + ((v119 << 6) | (v119 >> 26));
  v121 = v114 + x[15] + (v118 ^ (v120 | ~v116)) - 30611744;
  v122 = v120 + ((v121 << 10) | (v121 >> 22));
  v123 = v116 + x[6] + (v120 ^ (v122 | ~v118)) - 1560198380;
  v124 = v122 + ((v123 << 15) | (v123 >> 17));
  v125 = v118 + x[13] + (v122 ^ (v124 | ~v120)) + 1309151649;
  v126 = v124 + ((v125 >> 11) | (v125 << 21));
  v127 = v120 + x[4] + (v124 ^ (v126 | ~v122)) - 145523070;
  v128 = v126 + ((v127 << 6) | (v127 >> 26));
  v129 = v122 + x[11] + (v126 ^ (v128 | ~v124)) - 1120210379;
  v130 = v128 + ((v129 << 10) | (v129 >> 22));
  v131 = v124 + x[2] + (v128 ^ (v130 | ~v126)) + 718787259;
  v132 = v130 + ((v131 << 15) | (v131 >> 17));
  v133 = v126 + x[9] + (v130 ^ (v132 | ~v128)) - 343485551;
  *state += v128;
  state[1] += v132 + ((v133 >> 11) | (v133 << 21));
  state[2] += v132;
  state[3] += v130;
}

// source: j/0/network/md5c.c:283  [anchor-mhash]
unsigned int *__cdecl Encode(unsigned __int8 *output, unsigned int *input, unsigned int len)
{
  unsigned __int8 *v3; // ecx
  unsigned int v4; // esi

  if ( len )
  {
    v3 = output + 1;
    input = (unsigned int *)((char *)input + 2);
    v4 = ((len - 1) >> 2) + 1;
    do
    {
      *(v3 - 1) = *((_BYTE *)input - 2);
      *v3 = *((_BYTE *)input - 1);
      v3[1] = *(_BYTE *)input;
      v3[2] = *((_BYTE *)input++ + 1);
      v3 += 4;
      --v4;
    }
    while ( v4 );
  }
  return input;
}

// source: j/0/network/md5c.c:301  [anchor-mhash]
unsigned __int8 *__cdecl Decode(
        unsigned int *output,
        unsigned __int8 *input,
        unsigned int len)
{
  unsigned int v4; // ecx
  int v5; // edi
  unsigned __int16 v6; // dx

  if ( len )
  {
    input += 2;
    v4 = ((len - 1) >> 2) + 1;
    do
    {
      v5 = *(input - 1);
      HIBYTE(v6) = input[1];
      ++output;
      input += 4;
      LOBYTE(v6) = *(input - 4);
      --v4;
      *(output - 1) = *(input - 6) | ((v5 | (v6 << 8)) << 8);
    }
    while ( v4 );
  }
  return input;
}

// source: j/0/network/md5c.c:315  [anchor-mhash]
unsigned __int8 *__cdecl MD5_memcpy(
        unsigned __int8 *output,
        unsigned __int8 *input,
        unsigned int len)
{
  qmemcpy(output, input, len);
  return (unsigned __int8 *)len;
}

// source: j/0/network/md5c.c:329  [anchor-mhash]
void __cdecl MD5_memset(unsigned __int8 *output, int value, unsigned int len)
{
  int v3; // ebx
  char v5; // dl
  unsigned int v6; // ecx
  int v7; // eax

  LOBYTE(v3) = value;
  BYTE1(v3) = value;
  v5 = len;
  v6 = len >> 2;
  v7 = v3 << 16;
  LOWORD(v7) = v3;
  memset32(output, v7, v6);
  memset(&output[4 * v6], value, v5 & 3);
}

// source: j/0/network/md5c.c:340  [anchor-hash]
char *__cdecl MD5Print(unsigned __int8 *digest, char *output)
{
  unsigned int i; // esi
  char *result; // eax

  for ( i = 0; i < 0x10; ++i )
  {
    result = (char *)sprintf(output, "%02x", digest[i]);
    output += 2;
  }
  return result;
}

// source: j/0/network/md5c.c:352  [anchor-callee]
unsigned int __cdecl MD5Digest(unsigned __int8 *input, unsigned int len, char *output)
{
  #pragma pack(push, 1)
  union
  {
    struct { unsigned __int8 digest[16]; };
    struct { char igi2_o1[16]; struct MD5_CTX ctx; };
    char igi2_extent[104];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  unsigned int v3; // esi
  unsigned int result; // eax

  v3 = 0;
  igi2_frame.ctx.count[1] = 0;
  igi2_frame.ctx.count[0] = 0;
  igi2_frame.ctx.state[0] = 1732584193;
  igi2_frame.ctx.state[1] = -271733879;
  igi2_frame.ctx.state[2] = -1732584194;
  igi2_frame.ctx.state[3] = 271733878;
  MD5Update(&igi2_frame.ctx, input, len);
  MD5Final(igi2_frame.digest, &igi2_frame.ctx);
  do
  {
    result = sprintf(output, "%02x", igi2_frame.digest[v3++]);
    output += 2;
  }
  while ( v3 < 0x10 );
  return result;
}
