/* The C runtime's maths (sqrt, sin, cos, atan2, pow...) on 32-bit x86 takes SSE2 code when the
   processor has it, and computes in double precision. The game's 2003 runtime computed on the
   x87 unit, under the precision and rounding the game sets there (truncation, Direct3D's single
   precision): results differed in their last bits (the player's ground normal by 2 units in the
   last place on the first frame of a mission), and the differences grew. The runtime's own
   switch sends its maths back to x87 code, before any game code runs. */
#include <math.h>

static void __cdecl Igi2_InitFpuMaths(void)
{
    _set_SSE2_enable(0);
}

#pragma section(".CRT$XCT", read)
__declspec(allocate(".CRT$XCT")) static void (__cdecl *const kInitFpuMaths)(void) = Igi2_InitFpuMaths;
