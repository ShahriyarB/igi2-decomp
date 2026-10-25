// source: b/1/real.c:190  [override: IDA decodes this function from the wrong byte]
// acos(x) = pi/2 - asin(x): the original calls Real32_FastAsin, then fsubr's it from the float
// constant at 0x6A6BD8 (pi/2).
float __cdecl Real32_FastAcos(float vCos)
{
  return flt_6A6BD8 - Real32_FastAsin(vCos);
}
