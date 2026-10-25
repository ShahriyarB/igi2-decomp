/* _objects/clipping.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: clipping.obj  [size]
struct D3DXVECTOR4 *__cdecl D3DXVec4Subtract(
        struct D3DXVECTOR4 *pOut,
        struct D3DXVECTOR4 *pV1,
        struct D3DXVECTOR4 *pV2)
{
  pOut->x = pV1->x - pV2->x;
  pOut->y = pV1->y - pV2->y;
  pOut->z = pV1->z - pV2->z;
  pOut->w = pV1->w - pV2->w;
  return pOut;
}
