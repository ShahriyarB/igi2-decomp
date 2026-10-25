/* b/4/pc/pc_dshow.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: b/4/pc/pc_dshow.c:49  [size]
int __cdecl PlayCutscene(char *szMovie, struct HINSTANCE__ *hInstance)
{
  char *v2; // edi
  int result; // eax

  result = GetInterfaces();
  if ( result >= 0 )
    return PlayMedia(v2, (struct HINSTANCE__ *)szMovie);
  return result;
}

// source: b/4/pc/pc_dshow.c:63  [size]
int __cdecl GetInterfaces()
{
  HRESULT Instance; // esi

  Instance = CoCreateInstance(&CLSID_CLSID_FilgraphManager, nullptr, 3u, &CLSID_IGraphBuilder, (LPVOID *)&pGB);
  if ( Instance >= 0 )
  {
    Instance = pGB->lpVtbl->QueryInterface(pGB, &CLSID_IMediaControl, (void **)&pMC);
    if ( Instance >= 0 )
    {
      Instance = pGB->lpVtbl->QueryInterface(pGB, &CLSID_IVideoWindow, (void **)&pVW);
      if ( Instance >= 0 )
      {
        Instance = pGB->lpVtbl->QueryInterface(pGB, &CLSID_IMediaEventEx, (void **)&pME);
        if ( Instance >= 0 )
          return 0;
      }
    }
  }
  CleanupInterfaces();
  return Instance;
}

// source: b/4/pc/pc_dshow.c:86  [size]
void __cdecl CleanupInterfaces()
{
  if ( pGB )
    pGB->lpVtbl->Release(pGB);
  pGB = nullptr;
  if ( pMC )
    pMC->lpVtbl->Release(pMC);
  pMC = nullptr;
  if ( pVW )
    pVW->lpVtbl->Release(pVW);
  pVW = nullptr;
  if ( pME )
    pME->lpVtbl->Release(pME);
  pME = nullptr;
}

// source: b/4/pc/pc_dshow.c:96  [size]
void __cdecl CloseApp()
{
  if ( pMC )
    pMC->lpVtbl->Stop(pMC);
  g_bContinue = 0;
}

// source: b/4/pc/pc_dshow.c:107  [size]
int __cdecl PlayMedia(char *lpszMovie, struct HINSTANCE__ *hInstance)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct tagRECT grc; };
    struct { char igi2_o1[16]; unsigned __int16 wFileName[260]; };
    char igi2_extent[536];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  char v2; // al
  char *v3; // ecx
  unsigned __int16 *i; // edx
  struct IGraphBuilder *v5; // eax
  int result; // eax

  g_bContinue = 0;
  strcpy(g_szMovie, lpszMovie);
  v2 = *lpszMovie;
  v3 = lpszMovie;
  for ( i = igi2_frame.wFileName; *v3; ++i )
  {
    ++v3;
    *i = v2;
    v2 = *v3;
  }
  v5 = pGB;
  *i = *v3;
  result = v5->lpVtbl->RenderFile(v5, igi2_frame.wFileName, nullptr);
  if ( result >= 0 )
  {
    pVW->lpVtbl->put_Owner(pVW, (int)AppContext_tAppContext.hWnd);
    pVW->lpVtbl->put_WindowStyle(pVW, 1140850688);
    GetClientRect(AppContext_tAppContext.hWnd, &igi2_frame.grc);
    pVW->lpVtbl->SetWindowPosition(pVW, 0, 0, igi2_frame.grc.right, igi2_frame.grc.bottom);
    result = pVW->lpVtbl->put_MessageDrain(pVW, (int)AppContext_tAppContext.hWnd);
    if ( result >= 0 )
    {
      result = pMC->lpVtbl->Pause(pMC);
      if ( result >= 0 )
      {
        result = pMC->lpVtbl->Run(pMC);
        if ( result >= 0 )
          g_bContinue = 1;
      }
    }
  }
  return result;
}

// source: b/4/pc/pc_dshow.c:173  [size]
int __cdecl PlayLoop()
{
  #pragma pack(push, 1)
  union
  {
    struct { int lEventCode; };
    struct { char igi2_o1[4]; int lParam2; };
    struct { char igi2_o2[8]; int lParam1; };
    char igi2_extent[12];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int result; // eax

  if ( !g_bContinue || pME->lpVtbl->GetEvent(pME, &igi2_frame.lEventCode, &igi2_frame.lParam1, &igi2_frame.lParam2, 0) == -2147467260 )
    return 0;
  result = pME->lpVtbl->FreeEventParams(pME, igi2_frame.lEventCode, igi2_frame.lParam1, igi2_frame.lParam2);
  if ( igi2_frame.lEventCode == 1 )
    g_bContinue = 0;
  return result;
}

// source: b/4/pc/pc_dshow.c:202  [size]
void Msg_4434b0(char *szFormat, ...)
{
  ;
}

// source: b/4/pc/pc_dshow.c:229  [size]
enum bool __cdecl Movie_Begin(char *zFilename)
{
  struct HINSTANCE__ *hInstance; // esi

  hInstance = AppContext_tAppContext.hInstance;
  if ( GetInterfaces() >= 0 )
    PlayMedia((char *)zFilename, hInstance);
  return g_bContinue;
}

// source: b/4/pc/pc_dshow.c:243  [size]
enum bool __cdecl Movie_Play()
{
  PlayLoop();
  Real_nTempCW = igi2_fpu_or(0xC00u);
  return g_bContinue;
}

// source: b/4/pc/pc_dshow.c:261  [size]
enum bool __cdecl Movie_IsPlaying()
{
  return g_bContinue;
}

// source: b/4/pc/pc_dshow.c:274  [size]
void __cdecl Movie_End()
{
  if ( pMC )
    pMC->lpVtbl->Stop(pMC);
  g_bContinue = 0;
  CleanupInterfaces();
  Real_nTempCW = igi2_fpu_or(0xC00u);
}
