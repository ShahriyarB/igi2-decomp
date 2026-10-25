/* b/0/pc/pc_exceptionhandler.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: b/0/pc/pc_exceptionhandler.c:202  [size]
int __stdcall ExceptionHandler_UnhandledExceptionFilter(struct _EXCEPTION_POINTERS *ptExceptionInfo)
{
  struct ExceptionCallbackNode_s *ptHead; // eax
  struct ExceptionCallbackNode_s *ptNext; // esi
  bool v3; // zf
  void (__cdecl *pfExceptionCallback)(void *); // ecx

  ExceptionHandler_hReportFile = CreateFileA(
                                   ExceptionHandler_zLogFileName,
                                   0x40000000u,
                                   0,
                                   nullptr,
                                   2u,
                                   0x80000000,
                                   nullptr);
  if ( ExceptionHandler_hReportFile != (void *)-1 )
  {
    ExceptionHandler_GenerateExceptionReport(ptExceptionInfo);
    ExceptionHandler_printf("\r\nEnd.\r\n");
    CloseHandle(ExceptionHandler_hReportFile);
    ExceptionHandler_hReportFile = nullptr;
  }
  if ( !dword_834D4EC )
  {
    ptHead = ExceptionHandler_tExceptionCallbackList.ptHead;
    ptNext = ExceptionHandler_tExceptionCallbackList.ptHead->ptNext;
    v3 = ExceptionHandler_tExceptionCallbackList.ptHead->ptNext == nullptr;
    dword_834D4EC = 1;
    if ( !v3 )
    {
      do
      {
        pfExceptionCallback = ptHead->pfExceptionCallback;
        if ( pfExceptionCallback )
          pfExceptionCallback(ptHead->pxContext);
        ptHead = ptNext;
        ptNext = ptNext->ptNext;
      }
      while ( ptNext );
    }
  }
  if ( ExceptionHandler_tPreviousFilter )
    return ExceptionHandler_tPreviousFilter(ptExceptionInfo);
  else
    return 0;
}

// source: b/0/pc/pc_exceptionhandler.c:263  [size]
void __cdecl ExceptionHandler_GenerateExceptionReport(struct _EXCEPTION_POINTERS *ptExceptionInfo)
{
  #pragma pack(push, 1)
  union
  {
    struct { struct _CONTEXT *v5; };
    struct { char igi2_o1[8]; unsigned int nSection; };
    struct { char igi2_o2[12]; unsigned int nOffset; };
    struct { char igi2_o3[16]; char zFaultingModule[260]; };
    char igi2_extent[276];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  PEXCEPTION_RECORD ExceptionRecord; // esi
  char *ExceptionString; // eax
  PCONTEXT ContextRecord; // esi
  HANDLE CurrentThread; // eax

  ExceptionRecord = ptExceptionInfo->ExceptionRecord;
  ExceptionHandler_printf("UNHANDLED EXCEPTION\n\n");
  ExceptionString = ExceptionHandler_GetExceptionString(ExceptionRecord->ExceptionCode);
  ExceptionHandler_printf("Exception code: %08X %s\n", ExceptionRecord->ExceptionCode, ExceptionString);
  ExceptionHandler_GetLogicalAddress(ExceptionRecord->ExceptionAddress, igi2_frame.zFaultingModule, 0x104u, &igi2_frame.nSection, &igi2_frame.nOffset);
  ExceptionHandler_printf(
    "Fault address:  %08X %02X:%08X %s\n",
    ExceptionRecord->ExceptionAddress,
    igi2_frame.nSection,
    igi2_frame.nOffset,
    igi2_frame.zFaultingModule);
  ContextRecord = ptExceptionInfo->ContextRecord;
  ExceptionHandler_printf("\nRegisters:\n");
  ExceptionHandler_printf(
    "EAX:%08X\nEBX:%08X\nECX:%08X\nEDX:%08X\nESI:%08X\nEDI:%08X\n",
    ContextRecord->Eax,
    ContextRecord->Ebx,
    ContextRecord->Ecx,
    ContextRecord->Edx,
    ContextRecord->Esi,
    ContextRecord->Edi);
  ExceptionHandler_printf("CS:EIP:%04X:%08X\n", ContextRecord->SegCs, ContextRecord->Eip);
  ExceptionHandler_printf("SS:ESP:%04X:%08X  EBP:%08X\n", ContextRecord->SegSs, ContextRecord->Esp, ContextRecord->Ebp);
  ExceptionHandler_printf(
    "DS:%04X  ES:%04X  FS:%04X  GS:%04X\n",
    ContextRecord->SegDs,
    ContextRecord->SegEs,
    ContextRecord->SegFs,
    ContextRecord->SegGs);
  ExceptionHandler_printf("Flags:%08X\n\n", ContextRecord->EFlags);
  igi2_frame.v5 = ptExceptionInfo->ContextRecord;
  CurrentThread = GetCurrentThread();
  Stackwalk_ShowStack(CurrentThread, igi2_frame.v5);
}

// source: b/0/pc/pc_exceptionhandler.c:352  [layout]
char *__cdecl ExceptionHandler_GetExceptionString(unsigned int dwCode)
{
  char *result; // eax
  HMODULE ModuleHandleA; // eax

  if ( dwCode > 0xC000008D )
  {
    switch ( dwCode )
    {
      case 0xC000008E:
        result = "FLT_DIVIDE_BY_ZERO";
        break;
      case 0xC000008F:
        result = "FLT_INEXACT_RESULT";
        break;
      case 0xC0000090:
        result = "FLT_INVALID_OPERATION";
        break;
      case 0xC0000091:
        result = "FLT_OVERFLOW";
        break;
      case 0xC0000092:
        result = "FLT_STACK_CHECK";
        break;
      case 0xC0000093:
        result = "FLT_UNDERFLOW";
        break;
      case 0xC0000094:
        result = "INT_DIVIDE_BY_ZERO";
        break;
      case 0xC0000095:
        result = "INT_OVERFLOW";
        break;
      case 0xC0000096:
        result = "PRIV_INSTRUCTION";
        break;
      case 0xC00000FD:
        result = "STACK_OVERFLOW";
        break;
      default:
        goto LABEL_35;
    }
  }
  else if ( dwCode == -1073741683 )
  {
    return "FLT_DENORMAL_OPERAND";
  }
  else if ( dwCode > 0xC0000006 )
  {
    switch ( dwCode )
    {
      case 0xC0000008:
        result = "INVALID_HANDLE";
        break;
      case 0xC000001D:
        result = "ILLEGAL_INSTRUCTION";
        break;
      case 0xC0000025:
        result = "NONCONTINUABLE_EXCEPTION";
        break;
      case 0xC0000026:
        result = "INVALID_DISPOSITION";
        break;
      case 0xC000008C:
        result = "ARRAY_BOUNDS_EXCEEDED";
        break;
      default:
        goto LABEL_35;
    }
  }
  else if ( dwCode == -1073741818 )
  {
    return "IN_PAGE_ERROR";
  }
  else
  {
    if ( dwCode > 0x80000003 )
    {
      if ( dwCode == -2147483644 )
        return "SINGLE_STEP";
      if ( dwCode == -1073741819 )
        return "ACCESS_VIOLATION";
    }
    else
    {
      switch ( dwCode )
      {
        case 0x80000003:
          return "BREAKPOINT";
        case 0x80000001:
          return "GUARD_PAGE";
        case 0x80000002:
          return "DATATYPE_MISALIGNMENT";
      }
    }
LABEL_35:
    ModuleHandleA = GetModuleHandleA("NTDLL.DLL");
    FormatMessageA(0xA00u, ModuleHandleA, dwCode, 0, Buffer_834d798, 0x200u, nullptr);
    return Buffer_834d798;
  }
  return result;
}

// source: b/0/pc/pc_exceptionhandler.c:418  [size]
int __cdecl ExceptionHandler_GetLogicalAddress(
        void *addr,
        char *szModule,
        unsigned int len,
        unsigned int *pnSection,
        unsigned int *pnOffset)
{
  int result; // eax
  _DWORD *AllocationBase; // esi
  int v8; // eax
  int v9; // ecx
  char *v10; // eax
  char *v11; // edi
  unsigned int v12; // esi
  unsigned int v13; // edx
  char *v14; // ecx
  unsigned int v15; // ebx
  unsigned int v16; // ebp
  unsigned int v17; // ecx
  unsigned int v18; // eax
  struct _MEMORY_BASIC_INFORMATION mbi; // [esp+4h] [ebp-1Ch] BYREF

  result = VirtualQuery(addr, &mbi, 0x1Cu);
  if ( result )
  {
    AllocationBase = mbi.AllocationBase;
    if ( GetModuleFileNameA((HMODULE)mbi.AllocationBase, szModule, len)
      && (v8 = AllocationBase[15],
          v9 = *(unsigned __int16 *)((char *)AllocationBase + v8 + 20),
          v10 = (char *)AllocationBase + v8,
          v11 = (char *)((_BYTE *)addr - (_BYTE *)AllocationBase),
          v12 = *((unsigned __int16 *)v10 + 3),
          v13 = 0,
          v14 = &v10[v9 + 24],
          *((_WORD *)v10 + 3)) )
    {
      v15 = *((_DWORD *)v14 + 3);
      v16 = *((_DWORD *)v14 + 4);
      v17 = *((_DWORD *)v14 + 2);
      while ( 1 )
      {
        v18 = v16;
        if ( v16 <= v17 )
          v18 = v17;
        if ( (unsigned int)v11 >= v15 && (unsigned int)v11 <= v15 + v18 )
          break;
        ++v13;
        ++pnSection;
        if ( v13 >= v12 )
          return 0;
      }
      *pnSection = v13 + 1;
      *pnOffset = (unsigned int)&v11[-v15];
      return 1;
    }
    else
    {
      return 0;
    }
  }
  return result;
}

// source: b/0/pc/pc_exceptionhandler.c:664  [size]
int ExceptionHandler_printf(char *format, ...)
{
  #pragma pack(push, 1)
  union
  {
    struct { unsigned int nError[2]; };
    struct { char igi2_o1[8]; char zBuff[1024]; };
    struct { char igi2_o2[1032]; char zError[1024]; };
    char igi2_extent[2056];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v1; // esi
  va_list ArgList; // [esp+814h] [ebp+8h] BYREF ARGSLOT

  va_start(ArgList, format);
  v1 = vsprintf(igi2_frame.zBuff, format, ArgList);
  if ( !WriteFile(ExceptionHandler_hReportFile, igi2_frame.zBuff, v1, &igi2_frame.nError[1], nullptr) )
  {
    igi2_frame.nError[0] = GetLastError();
    FormatMessageA(0x1000u, igi2_frame.nError, igi2_frame.nError[0], 0, igi2_frame.zError, 0x400u, nullptr);
    MessageBoxA(nullptr, igi2_frame.zError, "WriteFile()", 0);
  }
  return v1;
}

// source: b/0/pc/pc_exceptionhandler.c:853  [size]
void __cdecl ExceptionHandler_RegisterExceptionCallback(void (__cdecl *pfExceptionCallback)(void *), void *pxContext)
{
  int v2; // ecx
  unsigned int v3; // eax
  _DWORD *v4; // eax
  _DWORD *v5; // eax

  v2 = 0;
  v3 = 0;
  while ( *(_DWORD *)(v3 + 137680392) )
  {
    v3 += 20;
    ++v2;
    if ( v3 >= 0x140 )
      return;
  }
  v4 = (_DWORD *)(20 * v2 + 137680376);
  v4[1] = 0;
  *v4 = 0;
  v5 = List_AddTail(v4, (int)&ExceptionHandler_tExceptionCallbackList);
  v5[2] = pfExceptionCallback;
  v5[3] = pxContext;
  v5[4] = 1;
}

// source: b/0/pc/pc_exceptionhandler.c:888  [size]
void __cdecl ExceptionHandler_RemoveExceptionCallback(void (__cdecl *pfExceptionCallback)(void *))
{
  struct ExceptionCallbackNode_s *ptHead; // ecx
  struct ExceptionCallbackNode_s *i; // eax

  ptHead = ExceptionHandler_tExceptionCallbackList.ptHead;
  for ( i = ExceptionHandler_tExceptionCallbackList.ptHead->ptNext; i; i = i->ptNext )
  {
    if ( ptHead->pfExceptionCallback == pfExceptionCallback )
      ptHead->isAllocated = false;
    ptHead = i;
  }
}

// source: b/0/pc/pc_exceptionhandler.c:916  [size]
void __cdecl ExceptionHandler_Open()
{
  char *v0; // eax
  struct HINSTANCE__ *LibraryA; // eax
  DWORD LastError; // eax
  unsigned int (__stdcall *ProcAddress)(void *, void *, char *, char *, unsigned int, unsigned int); // eax

  ExceptionHandler_tPreviousFilter = SetUnhandledExceptionFilter(ExceptionHandler_UnhandledExceptionFilter);
  GetModuleFileNameA(nullptr, ExceptionHandler_zLogFileName, 0x104u);
  v0 = strrchr(ExceptionHandler_zLogFileName, 46);
  if ( v0 )
    *(_DWORD *)(v0 + 1) = 5525586;
  ExceptionHandler_tExceptionCallbackList.ptHead = (struct ExceptionCallbackNode_s *)&ExceptionHandler_tExceptionCallbackList.ptMiddle;
  ExceptionHandler_tExceptionCallbackList.ptTail = (struct ExceptionCallbackNode_s *)&ExceptionHandler_tExceptionCallbackList;
  ExceptionHandler_tExceptionCallbackList.ptMiddle = nullptr;
  LibraryA = LoadLibraryA("imagehlp.dll");
  hImagehlpDll = LibraryA;
  if ( LibraryA )
  {
    pSC = (int (__stdcall *)(void *))GetProcAddress(LibraryA, "SymCleanup");
    pSFTA = (void *(__stdcall *)(void *, unsigned int))GetProcAddress(hImagehlpDll, "SymFunctionTableAccess");
    pSGLFA = (int (__stdcall *)(void *, unsigned int, unsigned int *, struct _IMAGEHLP_LINE *))GetProcAddress(
                                                                                                 hImagehlpDll,
                                                                                                 "SymGetLineFromAddr");
    pSGMB = (unsigned int (__stdcall *)(void *, unsigned int))GetProcAddress(hImagehlpDll, "SymGetModuleBase");
    pSGMI = (int (__stdcall *)(void *, unsigned int, struct _IMAGEHLP_MODULE *))GetProcAddress(
                                                                                  hImagehlpDll,
                                                                                  "SymGetModuleInfo");
    pSGO = (unsigned int (__stdcall *)())GetProcAddress(hImagehlpDll, "SymGetOptions");
    pSGSFA = (int (__stdcall *)(void *, unsigned int, unsigned int *, struct _IMAGEHLP_SYMBOL *))GetProcAddress(
                                                                                                   hImagehlpDll,
                                                                                                   "SymGetSymFromAddr");
    pSI = (int (__stdcall *)(void *, char *, int))GetProcAddress(hImagehlpDll, "SymInitialize");
    pSSO = (unsigned int (__stdcall *)(unsigned int))GetProcAddress(hImagehlpDll, "SymSetOptions");
    pSW = (int (__stdcall *)(unsigned int, void *, void *, struct _tagSTACKFRAME *, void *, int (__stdcall *)(void *, unsigned int, void *, unsigned int, unsigned int *), void *(__stdcall *)(void *, unsigned int), unsigned int (__stdcall *)(void *, unsigned int), unsigned int (__stdcall *)(void *, void *, struct _tagADDRESS *)))GetProcAddress(hImagehlpDll, "StackWalk");
    pUDSN = (unsigned int (__stdcall *)(char *, char *, unsigned int, unsigned int))GetProcAddress(
                                                                                            hImagehlpDll,
                                                                                            "UnDecorateSymbolName");
    ProcAddress = (unsigned int (__stdcall *)(void *, void *, char *, char *, unsigned int, unsigned int))GetProcAddress(hImagehlpDll, "SymLoadModule");
    pSLM = ProcAddress;
    if ( !pSC || !pSFTA || !pSGMB || !pSGMI || !pSGO || !pSGSFA || !pSI || !pSSO || !pSW || !pUDSN || !ProcAddress )
    {
      puts("GetProcAddress(): some required function not found.");
      FreeLibrary(hImagehlpDll);
    }
  }
  else
  {
    LastError = GetLastError();
    printf("LoadLibrary( \"imagehlp.dll\" ): gle = %lu\n", LastError);
  }
}

// source: b/0/pc/pc_exceptionhandler.c:956  [size]
void __cdecl ExceptionHandler_Close()
{
  FreeLibrary(hImagehlpDll);
  SetUnhandledExceptionFilter(ExceptionHandler_tPreviousFilter);
}

void nullsub_400()
{
  ;
}

void nullsub_401()
{
  ;
}
