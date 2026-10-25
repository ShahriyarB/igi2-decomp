/* c/0/hermite.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: c/0/hermite.c:49  [anchor-mhash]
struct Hermite32_s *__cdecl Hermite32_Init(
        struct Hermite32_s *ptHermite,
        float vN1,
        float vN2,
        float vS1,
        float vS2)
{
  ptHermite->vS1 = vS1;
  ptHermite->vN1 = vN1;
  ptHermite->vA = vN1 + vN1 - (vN2 + vN2) + vS1 + vS2;
  ptHermite->vB = vN2 * 3.0 - vN1 * 3.0 - (vS1 + vS1) - vS2;
  return ptHermite;
}

// source: c/0/hermite.c:76  [anchor-mhash]
float __cdecl Hermite32_Evaluate(struct Hermite32_s *ptHermite, float vT)
{
  return vT * (vT * vT) * ptHermite->vA + vT * vT * ptHermite->vB + vT * ptHermite->vS1 + ptHermite->vN1;
}

// source: c/0/hermite.c:101  [size]
float __cdecl Hermite32_EvaluateTangent(struct Hermite32_s *ptHermite, float vT)
{
  double v2; // st6

  v2 = vT * ptHermite->vB;
  return vT * ptHermite->vA * vT * 3.0 + v2 + v2 + ptHermite->vS1;
}

// source: c/0/hermite.c:125  [anchor-mhash]
struct Hermite64_s *__cdecl Hermite64_Init(
        struct Hermite64_s *ptHermite,
        double vN1,
        double vN2,
        double vS1,
        double vS2)
{
  ptHermite->vS1 = vS1;
  ptHermite->vN1 = vN1;
  ptHermite->vA = vN1 + vN1 - (vN2 + vN2) + vS1 + vS2;
  ptHermite->vB = vN2 * 3.0 - vN1 * 3.0 - (vS1 + vS1) - vS2;
  return ptHermite;
}

// source: c/0/hermite.c:152  [anchor-mhash]
double __cdecl Hermite64_Evaluate(struct Hermite64_s *ptHermite, double vT)
{
  return vT * vT * vT * ptHermite->vA + vT * vT * ptHermite->vB + vT * ptHermite->vS1 + ptHermite->vN1;
}

// source: c/0/hermite.c:177  [size]
double __cdecl Hermite64_EvaluateTangent(struct Hermite64_s *ptHermite, double vT)
{
  return vT * ptHermite->vA * vT * 3.0 + vT * ptHermite->vB + vT * ptHermite->vB + ptHermite->vS1;
}
