// source: b/1/real.c:435  [override: the original clamps its argument in place and jumps into asin]
// The decompiler cannot follow the stack argument reused by the tail jump.
double __cdecl Real64_Asin(double vValue)
{
  if ( vValue < -1.0 )
    vValue = -1.0;
  else if ( vValue > 1.0 )
    vValue = 1.0;
  return asin(vValue);
}
