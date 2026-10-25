/* A replay (runtime/replay.c) runs unattended next to whatever the user is doing: the game must
   not take focus, cover other windows or make a sound. With IGI2_REPLAY set, before WinMain:
   - window calls in both import tables (this exe's, and the retail image's that the fallback
     filled) are wrapped: windows are created and kept off-screen at the bottom of the z-order,
     never activated, and nothing focuses, raises or captures anything;
   - the process's audio session is muted (Core Audio), so the game opens its sound as usual.
   Not built on igi2.h: the Windows audio headers and the game's definitions do not mix. */
#define COBJMACROS
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <mmdeviceapi.h>
#include <audiopolicy.h>
#include <stdlib.h>
#include <string.h>

/* the Core Audio ids (the headers declare them, no library defines them for C) */
static const CLSID kClsidEnumerator = {0xBCDE0395, 0xE52F, 0x467C, {0x8E, 0x3D, 0xC4, 0x57, 0x92, 0x91, 0x69, 0x2E}};
static const IID kIidEnumerator = {0xA95664D2, 0x9614, 0x4F35, {0xA7, 0x46, 0xDE, 0x8D, 0xB6, 0x36, 0x17, 0xE6}};
static const IID kIidSessionManager = {0xBFA971F1, 0x4D5E, 0x40BB, {0x93, 0x5E, 0x96, 0x70, 0x39, 0xBF, 0xBE, 0xE4}};

/* the real functions, from user32 itself: calls written here go through this exe's import
   table, which the hooks replace */
static HWND (WINAPI *s_pfCreateWindowExA)(DWORD, LPCSTR, LPCSTR, DWORD, int, int, int, int, HWND, HMENU, HINSTANCE, LPVOID);
static BOOL (WINAPI *s_pfShowWindow)(HWND, int);
static BOOL (WINAPI *s_pfSetWindowPos)(HWND, HWND, int, int, int, int, UINT);

#define OFFSCREEN_X (-8000)
#define OFFSCREEN_Y (-8000)

static HWND WINAPI Host_CreateWindowExA(DWORD dwExStyle, LPCSTR zClass, LPCSTR zName, DWORD dwStyle, int x, int y,
                                        int w, int h, HWND hParent, HMENU hMenu, HINSTANCE hInst, LPVOID pParam)
{
    if (!hParent) {
        dwStyle &= ~WS_VISIBLE;
        x = OFFSCREEN_X;
        y = OFFSCREEN_Y;
        dwExStyle |= WS_EX_NOACTIVATE | WS_EX_TOOLWINDOW;
    }
    return s_pfCreateWindowExA(dwExStyle, zClass, zName, dwStyle, x, y, w, h, hParent, hMenu, hInst, pParam);
}

static BOOL WINAPI Host_ShowWindow(HWND hWnd, int nCmdShow)
{
    if (nCmdShow == SW_HIDE)
        return s_pfShowWindow(hWnd, SW_HIDE);
    return s_pfSetWindowPos(hWnd, HWND_BOTTOM, OFFSCREEN_X, OFFSCREEN_Y, 0, 0,
                        SWP_NOSIZE | SWP_NOACTIVATE | SWP_SHOWWINDOW);
}

static BOOL WINAPI Host_SetWindowPos(HWND hWnd, HWND hAfter, int x, int y, int w, int h, UINT uFlags)
{
    (void)hAfter;
    (void)x;
    (void)y;
    return s_pfSetWindowPos(hWnd, HWND_BOTTOM, OFFSCREEN_X, OFFSCREEN_Y, w, h, (uFlags & ~SWP_NOZORDER) | SWP_NOACTIVATE);
}

static BOOL WINAPI Host_MoveWindow(HWND hWnd, int x, int y, int w, int h, BOOL isRepaint)
{
    (void)x;
    (void)y;
    (void)isRepaint;
    return s_pfSetWindowPos(hWnd, HWND_BOTTOM, OFFSCREEN_X, OFFSCREEN_Y, w, h, SWP_NOACTIVATE);
}

static HWND WINAPI Host_SetFocus(HWND hWnd) { (void)hWnd; return NULL; }
static BOOL WINAPI Host_SetForegroundWindow(HWND hWnd) { (void)hWnd; return TRUE; }
static HWND WINAPI Host_SetActiveWindow(HWND hWnd) { (void)hWnd; return NULL; }
static BOOL WINAPI Host_BringWindowToTop(HWND hWnd) { (void)hWnd; return TRUE; }
static HWND WINAPI Host_SetCapture(HWND hWnd) { (void)hWnd; return NULL; }
static BOOL WINAPI Host_ClipCursor(const RECT *pRect) { (void)pRect; return TRUE; }
static BOOL WINAPI Host_SetCursorPos(int x, int y) { (void)x; (void)y; return TRUE; }

static const struct { const char *zName; void *pfHook; } kHooks[] = {
    { "CreateWindowExA", (void *)Host_CreateWindowExA },
    { "ShowWindow", (void *)Host_ShowWindow },
    { "SetWindowPos", (void *)Host_SetWindowPos },
    { "MoveWindow", (void *)Host_MoveWindow },
    { "SetFocus", (void *)Host_SetFocus },
    { "SetForegroundWindow", (void *)Host_SetForegroundWindow },
    { "SetActiveWindow", (void *)Host_SetActiveWindow },
    { "BringWindowToTop", (void *)Host_BringWindowToTop },
    { "SetCapture", (void *)Host_SetCapture },
    { "ClipCursor", (void *)Host_ClipCursor },
    { "SetCursorPos", (void *)Host_SetCursorPos },
};

/* user32 entries of one module's import table, by name */
static void Host_PatchImports(unsigned char *pBase)
{
    const IMAGE_DOS_HEADER *dos = (const IMAGE_DOS_HEADER *)pBase;
    const IMAGE_NT_HEADERS32 *nt;
    const IMAGE_DATA_DIRECTORY *dir;
    const IMAGE_IMPORT_DESCRIPTOR *d;
    if (dos->e_magic != IMAGE_DOS_SIGNATURE)
        return;
    nt = (const IMAGE_NT_HEADERS32 *)(pBase + dos->e_lfanew);
    dir = &nt->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT];
    if (!dir->VirtualAddress)
        return;
    for (d = (const IMAGE_IMPORT_DESCRIPTOR *)(pBase + dir->VirtualAddress); d->Name; ++d) {
        const DWORD *pName;
        DWORD *pSlot;
        if (_stricmp((const char *)(pBase + d->Name), "user32.dll"))
            continue;
        pName = (const DWORD *)(pBase + (d->OriginalFirstThunk ? d->OriginalFirstThunk : d->FirstThunk));
        pSlot = (DWORD *)(pBase + d->FirstThunk);
        for (; *pName; ++pName, ++pSlot) {
            unsigned int k;
            const char *zName;
            if (*pName & IMAGE_ORDINAL_FLAG32)
                continue;
            zName = ((const IMAGE_IMPORT_BY_NAME *)(pBase + *pName))->Name;
            for (k = 0; k < sizeof kHooks / sizeof kHooks[0]; ++k) {
                DWORD old;
                if (strcmp(zName, kHooks[k].zName))
                    continue;
                if (VirtualProtect(pSlot, sizeof *pSlot, PAGE_READWRITE, &old)) {
                    *pSlot = (DWORD)(UINT_PTR)kHooks[k].pfHook;
                    VirtualProtect(pSlot, sizeof *pSlot, old, &old);
                }
            }
        }
    }
}

static void Host_MuteProcess(void)
{
    IMMDeviceEnumerator *ptEnum = NULL;
    IMMDevice *ptDevice = NULL;
    IAudioSessionManager *ptManager = NULL;
    ISimpleAudioVolume *ptVolume = NULL;
    HRESULT hrInit = CoInitializeEx(NULL, COINIT_MULTITHREADED);
    if (SUCCEEDED(CoCreateInstance(&kClsidEnumerator, NULL, CLSCTX_ALL, &kIidEnumerator, (void **)&ptEnum))
        && SUCCEEDED(IMMDeviceEnumerator_GetDefaultAudioEndpoint(ptEnum, eRender, eConsole, &ptDevice))
        && SUCCEEDED(IMMDevice_Activate(ptDevice, &kIidSessionManager, CLSCTX_ALL, NULL, (void **)&ptManager))
        && SUCCEEDED(IAudioSessionManager_GetSimpleAudioVolume(ptManager, NULL, FALSE, &ptVolume)))
        ISimpleAudioVolume_SetMute(ptVolume, TRUE, NULL);
    if (ptVolume) ISimpleAudioVolume_Release(ptVolume);
    if (ptManager) IAudioSessionManager_Release(ptManager);
    if (ptDevice) IMMDevice_Release(ptDevice);
    if (ptEnum) IMMDeviceEnumerator_Release(ptEnum);
    if (SUCCEEDED(hrInit))
        CoUninitialize();
}

static void __cdecl Igi2_InitReplayHost(void)
{
    const char *zReplay = getenv("IGI2_REPLAY");
    HMODULE hUser32;
    if (!zReplay || !*zReplay)
        return;
    hUser32 = GetModuleHandleA("user32.dll");
    s_pfCreateWindowExA = (void *)GetProcAddress(hUser32, "CreateWindowExA");
    s_pfShowWindow = (void *)GetProcAddress(hUser32, "ShowWindow");
    s_pfSetWindowPos = (void *)GetProcAddress(hUser32, "SetWindowPos");
    Host_PatchImports((unsigned char *)GetModuleHandleA(NULL));
    if (getenv("IGI2_FALLBACK") && *getenv("IGI2_FALLBACK"))
        Host_PatchImports((unsigned char *)(UINT_PTR)0x400000u);  /* the retail image's, filled by the fallback */
    Host_MuteProcess();
}

/* after the fallback (.CRT$XCV), which fills the retail import table */
#pragma section(".CRT$XCX", read)
__declspec(allocate(".CRT$XCX")) static void (__cdecl *const kInitReplayHost)(void) = Igi2_InitReplayHost;
