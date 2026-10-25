/* System headers the game was built against. Types they define are not re-emitted from the PDB;
   igi2_types.h asserts their sizes instead. Direct3D 8 and D3DX 8 types come from the PDB, since
   the Windows SDK no longer ships those headers. */
#pragma once

#define DIRECTINPUT_VERSION 0x0800
#define DIRECTSOUND_VERSION 0x0700
#define _CRT_SECURE_NO_WARNINGS

#include <windows.h>
#include <mmsystem.h>
#include <wininet.h>
#include <dinput.h>
#include <dsound.h>
#include <ddraw.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <locale.h>
#include <setjmp.h>
