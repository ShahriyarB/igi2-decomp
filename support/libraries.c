/* Hand-written stand-ins for code the retail exe links statically but this build cannot:
   C++ files of the game (left out of a C build) and SDKs that are not available.
   Signatures follow the call sites in src/ and the Final build's map. */
#include "igi2.h"

/* ---- b/1/pc/pc_checkdx.cpp: the DirectX version check (C++, a COM probe) ---------------- */

/* The original probes DirectX through COM objects and returns 0x801 for 8.1 or later; the
   game only refuses to start below 0x801. Direct3D 8 is present when d3d8.dll exports
   Direct3DCreate8, which every Windows since XP has. */
unsigned long __cdecl GetDXVersion(void)
{
    HMODULE d3d8 = LoadLibraryA("d3d8.dll");
    unsigned long version = 0;
    if (d3d8) {
        if (GetProcAddress(d3d8, "Direct3DCreate8"))
            version = 0x801;
        FreeLibrary(d3d8);
    }
    return version;
}

/* ---- b/0/pc/stackwalk.cpp: the crash reporter's stack dump (C++) -------------------------- */

void __cdecl Stackwalk_ShowStack(void *hThread, struct _CONTEXT *c)
{
    (void)hThread;
    (void)c;
    OutputDebugStringA("IGI 2: an unhandled exception occurred (no stack dump in this build)\n");
}

/* ---- Miles Sound System: the static part of mss32.lib ------------------------------------- */

/* mss.h makes AIL_startup() call this first, so the driver shuts down when the process exits */
static void __cdecl mss_shutdown_at_exit(void) { AIL_shutdown(); }

void __cdecl MSS_auto_cleanup(void)
{
    static int registered;
    if (!registered) {
        registered = 1;
        atexit(mss_shutdown_at_exit);
    }
}

/* ---- D3DX 8: two functions the DirectX 8.1 SDK's d3dx8.lib does not have ------------------- */

/* The retail exe was linked against a later D3DX 8, whose D3DXIMAGE_INFO also reports the
   resource type and the file format (28 bytes, as the game's own types declare it). */
static int image_file_format(const unsigned char *p, unsigned int n)
{
    if (n >= 4 && !memcmp(p, "DDS ", 4)) return 4;                    /* D3DXIFF_DDS */
    if (n >= 8 && !memcmp(p, "\x89PNG", 4)) return 3;                  /* D3DXIFF_PNG */
    if (n >= 2 && p[0] == 0xFF && p[1] == 0xD8) return 1;              /* D3DXIFF_JPG */
    if (n >= 2 && p[0] == 'B' && p[1] == 'M') return 0;                /* D3DXIFF_BMP */
    if (n >= 2 && p[0] == 'P' && (p[1] == '3' || p[1] == '6')) return 5; /* D3DXIFF_PPM */
    return 2;                                                          /* D3DXIFF_TGA: no magic */
}

/* The SDK can describe an image only while loading it, so load it onto a 1x1 surface. */
long __stdcall D3DXGetImageInfoFromFileInMemory(const void *pSrcData, unsigned int nSrcDataSize,
                                                D3DXIMAGE_INFO *ptInfo)
{
    struct IDirect3DSurface8 *ptSurface = NULL;
    long hr;
    memset(ptInfo, 0, sizeof *ptInfo);
    if (!Direct3D_ptDevice)
        return 0x8876086CL;  /* D3DERR_INVALIDCALL */
    hr = Direct3D_ptDevice->lpVtbl->CreateImageSurface(Direct3D_ptDevice, 1, 1, D3DFMT_A8R8G8B8, &ptSurface);
    if (hr < 0)
        return hr;
    hr = D3DXLoadSurfaceFromFileInMemory(ptSurface, NULL, NULL, pSrcData, nSrcDataSize, NULL,
                                         1 /* D3DX_FILTER_NONE */, 0, ptInfo);
    ptSurface->lpVtbl->Release(ptSurface);
    if (hr >= 0) {
        ptInfo->ResourceType = D3DRTYPE_TEXTURE;
        ptInfo->ImageFileFormat = image_file_format(pSrcData, nSrcDataSize);
    }
    return hr;
}

/* Only Envmap_Save, a development aid, writes surfaces to files. */
long __stdcall D3DXSaveSurfaceToFileA(const char *zDestFile, int eFormat, struct IDirect3DSurface8 *ptSurface,
                                      const PALETTEENTRY *ptPalette, const RECT *ptSrcRect)
{
    (void)zDestFile; (void)eFormat; (void)ptSurface; (void)ptPalette; (void)ptSrcRect;
    return 0x80004001L;  /* E_NOTIMPL */
}

/* ---- The All-Seeing Eye server-query SDK (ASEQuery_*) ------------------------------------- */

/* The static library is not available. Without it the game cannot answer ASE browser queries:
   initialisation reports failure, ASE_CreateHandler logs the error, and play is unaffected. */
int __cdecl ASEQuery_initialize(int hostport, int internet, char *address)
{
    (void)hostport;
    (void)internet;
    (void)address;
    ASEQuery_error = "the ASE query library is not part of this build";
    return 0;
}

void __cdecl ASEQuery_shutdown(void) {}

int __cdecl ASEQuery_check(void) { return 1; }

void __cdecl ASEQuery_status(const char *hostname, const char *gametype, const char *mapname,
                             const char *gamever, int password, int numplayers, int maxplayers)
{
    (void)hostname; (void)gametype; (void)mapname; (void)gamever;
    (void)password; (void)numplayers; (void)maxplayers;
}

void __cdecl ASEQuery_addrule(const char *key, const char *value)
{
    (void)key;
    (void)value;
}

void __cdecl ASEQuery_addplayer(const char *name, const char *team, const char *skin,
                                const char *score, const char *ping, const char *time)
{
    (void)name; (void)team; (void)skin; (void)score; (void)ping; (void)time;
}
