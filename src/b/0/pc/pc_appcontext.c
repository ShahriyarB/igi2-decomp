/* b/0/pc/pc_appcontext.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: b/0/pc/pc_appcontext.c:67  [size]
char *__cdecl AppContext_GetCmdLine()
{
  return (char *)Display_eBlitPrim;
}

// source: b/0/pc/pc_appcontext.c:80  [size]
struct HINSTANCE__ *__cdecl AppContext_GethInstance()
{
  return (struct HINSTANCE__ *)Display_eSnapshotPrim;
}

// source: b/0/pc/pc_appcontext.c:93  [size]
struct HWND__ *__cdecl AppContext_GethWnd()
{
  return (struct HWND__ *)Display_eGetGFXCapsMethod;
}

// source: b/0/pc/pc_appcontext.c:106  [size]
char *__cdecl AppContext_GetFileConfig()
{
  return (char *)Display_eOpenMethod;
}

// source: b/0/pc/pc_appcontext.c:136  [size]
char *__cdecl AppContext_GetName()
{
  return (char *)Display_eCloseMethod;
}

// source: b/0/pc/pc_appcontext.c:149  [size]
void __cdecl AppContext_SetCmdLine(char *zCmdLine)
{
  ;
}

// source: b/0/pc/pc_appcontext.c:164  [size]
void __cdecl AppContext_SethInstance(struct HINSTANCE__ *hInstance)
{
  ;
}

// source: b/0/pc/pc_appcontext.c:177  [size]
void __cdecl AppContext_SethWnd(struct HWND__ *hWnd)
{
  ;
}

// source: b/0/pc/pc_appcontext.c:190  [size]
void __cdecl AppContext_SetFileConfig(char *zFileConfig)
{
  ;
}

// source: b/0/pc/pc_appcontext.c:244  [size]
void __cdecl AppContext_SetRenderMode(enum RenderMode_enum eRenderMode)
{
  ;
}

// source: b/0/pc/pc_appcontext.c:257  [size]
enum RenderMode_enum __cdecl AppContext_GetRenderMode()
{
  return Display_eClearMethod;
}

// source: b/0/pc/pc_appcontext.c:283  [size]
enum bool __cdecl AppContext_IsFullscreen()
{
  return Display_eEnumDevicesMethod;
}

// source: b/0/pc/pc_appcontext.c:296  [anchor-hash]
enum bool __cdecl AppContext_SetActive(enum bool isActive)
{
  AppContext_tAppContext.isDebugged = (char)isActive;
  if ( AppContext_tAppContext.pfActivateCallback )
    AppContext_tAppContext.pfActivateCallback(isActive, AppContext_tAppContext.pxActivateCallbackContext);
  return isActive;
}

// source: b/0/pc/pc_appcontext.c:317  [size]
enum bool __cdecl AppContext_IsActive()
{
  return AppContext_tAppContext.isDebugged;
}

// source: b/0/pc/pc_appcontext.c:330  [size]
void __cdecl AppContext_SetActivatedDeactivateCallback(
        void (__cdecl *pfCallback)(enum bool, void *),
        void *pxContext)
{
  AppContext_tAppContext.pfActivateCallback = pfCallback;
  AppContext_tAppContext.pxActivateCallbackContext = pxContext;
}

// source: b/0/pc/pc_appcontext.c:344  [size]
void __cdecl AppContext_SetDebugged(enum bool isDebugged)
{
  AppContext_tAppContext.isDebugtext = (char)isDebugged;
}

// source: b/0/pc/pc_appcontext.c:357  [size]
enum bool __cdecl AppContext_IsDebugged()
{
  return AppContext_tAppContext.isDebugtext;
}

// source: b/0/pc/pc_appcontext.c:370  [size]
int __cdecl AppContext_GetFrequency()
{
  return AppContext_tAppContext.nFrequency;
}

// source: b/0/pc/pc_appcontext.c:383  [size]
int __cdecl AppContext_SetFrequency(int nFrequency)
{
  AppContext_tAppContext.nFrequency = nFrequency;
  return nFrequency;
}

// source: b/0/pc/pc_appcontext.c:396  [size]
void __cdecl AppContext_SetUseQVMState(enum bool isQVMUsed)
{
  AppContext_tAppContext.isTerrainLightmapsDisabled = (char)isQVMUsed;
}

// source: b/0/pc/pc_appcontext.c:409  [size]
enum bool __cdecl AppContext_IsQVMUsed()
{
  return AppContext_tAppContext.isTerrainLightmapsDisabled;
}

// source: b/0/pc/pc_appcontext.c:422  [size]
void __cdecl AppContext_SetDebugtextState(enum bool isDebugtext)
{
  AppContext_tAppContext.isQVMOnly = (char)isDebugtext;
}

// source: b/0/pc/pc_appcontext.c:435  [size]
enum bool __cdecl AppContext_IsDebugtext()
{
  return AppContext_tAppContext.isQVMOnly;
}

// source: b/0/pc/pc_appcontext.c:448  [size]
enum bool __cdecl AppContext_SetEditorState(enum bool isEditorState)
{
  AppContext_tAppContext.isFullscreen = isEditorState;
  return isEditorState;
}

// source: b/0/pc/pc_appcontext.c:461  [size]
enum bool __cdecl AppContext_GetEditorState()
{
  return AppContext_tAppContext.isFullscreen;
}

// source: b/0/pc/pc_appcontext.c:474  [size]
enum bool __cdecl AppContext_SetMainMenuState(enum bool isMainMenu)
{
  AppContext_tAppContext.isEditorState = isMainMenu;
  return isMainMenu;
}

// source: b/0/pc/pc_appcontext.c:487  [size]
enum bool __cdecl AppContext_GetMainMenuState()
{
  return AppContext_tAppContext.isEditorState;
}

// source: b/0/pc/pc_appcontext.c:513  [size~]
enum bool __cdecl AppContext_SetLightmapsUsed(enum bool isLightmapsUsed)
{
  AppContext_tAppContext.isLightmapsUsed = isLightmapsUsed;
  return isLightmapsUsed;
}

// source: b/0/pc/pc_appcontext.c:526  [size]
enum bool __cdecl AppContext_SetLightmapsDisabled(enum bool isLightmapsDisabled)
{
  AppContext_tAppContext.isTerrainLightmapsUsed = isLightmapsDisabled;
  return isLightmapsDisabled;
}

// source: b/0/pc/pc_appcontext.c:552  [size~]
void __cdecl AppContext_SetTerrainLightmapsUsed(enum bool isLightmapsUsed)
{
  ;
}

// source: b/0/pc/pc_appcontext.c:565  [size]
enum bool __cdecl AppContext_SetTerrainLightmapsDisabled(
        enum bool isTerrainLightmapsDisabled)
{
  AppContext_tAppContext.isClient = isTerrainLightmapsDisabled;
  return isTerrainLightmapsDisabled;
}

// source: b/0/pc/pc_appcontext.c:578  [size]
enum bool __cdecl AppContext_IsUseWinMessageInput()
{
  return AppContext_tAppContext.isGermany;
}

// source: b/0/pc/pc_appcontext.c:591  [size]
enum bool __cdecl AppContext_SetUseWinMessageInput(enum bool isUsed)
{
  AppContext_tAppContext.isGermany = isUsed;
  return isUsed;
}

// source: b/0/pc/pc_appcontext.c:604  [size]
enum bool __cdecl AppContext_SetServerState(enum bool isServerState)
{
  AppContext_tAppContext.isDrawingDisabled = isServerState;
  return isServerState;
}

// source: b/0/pc/pc_appcontext.c:617  [size]
enum bool __cdecl AppContext_GetServerState()
{
  return AppContext_tAppContext.isDrawingDisabled;
}

// source: b/0/pc/pc_appcontext.c:630  [anchor-hash]
enum bool __cdecl AppContext_SetServerDedicatedState(enum bool isServerState)
{
  AppContext_tAppContext.isServer = isServerState;
  if ( isServerState )
    AppContext_tAppContext.isMainMenu = true;
  return isServerState;
}

// source: b/0/pc/pc_appcontext.c:649  [size]
enum bool __cdecl AppContext_GetServerDedicatedState()
{
  return AppContext_tAppContext.isServer;
}

// source: b/0/pc/pc_appcontext.c:664  [size]
char *__cdecl AppContext_SetPlayer(char *zPlayer)
{
  return strncpy(AppContext_tAppContext.zPlayer, zPlayer, 0x40u);
}

// source: b/0/pc/pc_appcontext.c:676  [size]
char *__cdecl AppContext_GetPlayer()
{
  return AppContext_tAppContext.zPlayer;
}

// source: b/0/pc/pc_appcontext.c:691  [size]
char *__cdecl AppContext_SetPassword(char *zPassword)
{
  return strncpy(AppContext_tAppContext.zPassword, zPassword, 0x40u);
}

// source: b/0/pc/pc_appcontext.c:703  [size]
char *__cdecl AppContext_GetPassword()
{
  return AppContext_tAppContext.zPassword;
}

// source: b/0/pc/pc_appcontext.c:745  [size]
void __cdecl AppContext_SetPort(int nPort)
{
  ;
}

// source: b/0/pc/pc_appcontext.c:758  [size]
int __cdecl AppContext_GetPort(int ltcg_eax)
{
  AppContext_tAppContext.nPort = ltcg_eax;
  return ltcg_eax;
}

// source: b/0/pc/pc_appcontext.c:787  [size]
void __cdecl AppContext_SetTrackNum(int nTrack)
{
  ;
}

// source: b/0/pc/pc_appcontext.c:800  [size]
int __cdecl AppContext_GetTrackNum(int ltcg_eax)
{
  AppContext_tAppContext.nTrack = ltcg_eax;
  return ltcg_eax;
}

// source: b/0/pc/pc_appcontext.c:813  [size]
void __cdecl AppContext_SetGermany(enum bool isGermany)
{
  ;
}

// source: b/0/pc/pc_appcontext.c:826  [size~]
enum bool __cdecl AppContext_IsGermany()
{
  return false;
}

// source: b/0/pc/pc_appcontext.c:852  [size]
char *__cdecl AppContext_GetCountry()
{
  return AppContext_tAppContext.zCountry;
}

// source: b/0/pc/pc_appcontext.c:878  [size]
enum bool __cdecl AppContext_SetUseQVMOnly(enum bool isQVMOnly)
{
  AppContext_tAppContext.isQVMUsed = isQVMOnly;
  return isQVMOnly;
}

// source: b/0/pc/pc_appcontext.c:891  [size]
enum bool __cdecl AppContext_IsQVMOnly()
{
  return AppContext_tAppContext.isQVMUsed;
}

// source: b/0/pc/pc_appcontext.c:904  [size]
enum bool __cdecl AppContext_IsDraw()
{
  return AppContext_tAppContext.isMainMenu == false;
}

// source: b/0/pc/pc_appcontext.c:917  [size]
void __cdecl AppContext_SetDraw(enum bool isDraw)
{
  AppContext_tAppContext.isMainMenu = isDraw == false;
}

// source: b/0/pc/pc_appcontext.c:936  [anchor-refs]
int __cdecl AppContext_QueryRegistry(
        char *zDir,
        char *zKey,
        char *zValue,
        int nLength)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct HKEY__ *hKey; };
    struct { char igi2_o1[4]; unsigned int dwBufLen; };
    char igi2_extent[8];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)

  igi2_frame.dwBufLen = nLength;
  if ( RegOpenKeyExA(HKEY_LOCAL_MACHINE, zDir, 0, 1u, &igi2_frame.hKey)
    || RegQueryValueExA(igi2_frame.hKey, zKey, nullptr, nullptr, (LPBYTE)zValue, &igi2_frame.dwBufLen) )
  {
    *zValue = 0;
  }
  return RegCloseKey(igi2_frame.hKey);
}
