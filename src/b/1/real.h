/* b/1/real.h -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: b/1/real.h:394  [size]
float __cdecl __spoils<eax> Real32_FastSin(float vAngle)
{
  return (vAngle * 651.8986206054688 - (double)(int)(__int64)(vAngle * 651.8986206054688))
       * Real32_avSin[(__int64)(vAngle * 651.8986206054688) & 0xFFF].vY
       + Real32_avSin[(__int64)(vAngle * 651.8986206054688) & 0xFFF].vX;
}

// source: b/1/real.h:394  [size]
float __cdecl __spoils<eax> Real32_FastSin__birdflock(float vAngle)
{
  return (vAngle * 651.8986206054688 - (double)(int)(__int64)(vAngle * 651.8986206054688))
       * Real32_avSin[(__int64)(vAngle * 651.8986206054688) & 0xFFF].vY
       + Real32_avSin[(__int64)(vAngle * 651.8986206054688) & 0xFFF].vX;
}
