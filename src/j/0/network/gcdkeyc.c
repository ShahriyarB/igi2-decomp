/* j/0/network/gcdkeyc.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/network/gcdkeyc.c:37  [anchor-strings]
char *__cdecl gcd_compute_response(char *cdkey, char *challenge, char *response)
{
  #pragma pack(push, 1)
  union
  {
    struct { char randstr[12]; };
    struct { char igi2_o1[12]; char rawout[512]; };
    char igi2_extent[524];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  char *result; // eax
  __time32_t v5; // eax
  int v6; // esi
  unsigned int v7; // esi

  result = (char *)(strlen(challenge) + 2 * strlen(cdkey) + 8);
  if ( (unsigned int)result < 0x200 )
  {
    v5 = time(nullptr);
    srand(v5 ^ 0x33333333);
    v6 = rand() << 16;
    v7 = rand() | v6;
    sprintf(igi2_frame.randstr, "%.8x", v7);
    sprintf(igi2_frame.rawout, "%s%d%s", cdkey, v7 % 0xFFFF, challenge);
    MD5Digest((unsigned __int8 *)cdkey, strlen(cdkey), response);
    strcpy(response + 32, igi2_frame.randstr);
    return (char *)MD5Digest((unsigned __int8 *)igi2_frame.rawout, strlen(igi2_frame.rawout), response + 40);
  }
  else
  {
    strcpy(response, "CD Key or challenge too long");
  }
  return result;
}
