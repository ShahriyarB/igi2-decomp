/* Hand-written stand-ins for code this build cannot link (support/libraries.c). tools/export_data.py
   leaves these names out of the generated library declarations. */
#pragma once

unsigned long __cdecl GetDXVersion(void);
void __cdecl Stackwalk_ShowStack(void *hThread, struct _CONTEXT *c);
void __cdecl MSS_auto_cleanup(void);

long __stdcall D3DXGetImageInfoFromFileInMemory(const void *pSrcData, unsigned int nSrcDataSize,
                                                D3DXIMAGE_INFO *ptInfo);
long __stdcall D3DXSaveSurfaceToFileA(const char *zDestFile, int eFormat, struct IDirect3DSurface8 *ptSurface,
                                      const PALETTEENTRY *ptPalette, const RECT *ptSrcRect);

int __cdecl ASEQuery_initialize(int hostport, int internet, char *address);
void __cdecl ASEQuery_shutdown(void);
int __cdecl ASEQuery_check(void);
void __cdecl ASEQuery_status(const char *hostname, const char *gametype, const char *mapname,
                             const char *gamever, int password, int numplayers, int maxplayers);
void __cdecl ASEQuery_addrule(const char *key, const char *value);
void __cdecl ASEQuery_addplayer(const char *name, const char *team, const char *skin,
                                const char *score, const char *ping, const char *time);
