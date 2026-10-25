/* _objects/pc_batch.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: pc_batch.obj  [size]
struct _D3DMATRIX *__cdecl D3DXMatrixIdentity(struct _D3DMATRIX *pOut)
{
  *(_QWORD *)&pOut->m[3][1] = 0;
  *(_QWORD *)&pOut->m[2][3] = 0;
  *(_QWORD *)&pOut->m[2][0] = 0;
  *(_QWORD *)&pOut->m[1][2] = 0;
  *(_QWORD *)&pOut->m[0][3] = 0;
  *(_QWORD *)&pOut->m[0][1] = 0;
  pOut->_44 = 1.0;
  pOut->_33 = 1.0;
  pOut->_22 = 1.0;
  pOut->_11 = 1.0;
  return pOut;
}
