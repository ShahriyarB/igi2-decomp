/* b/1/appmain.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: b/1/appmain.c:38  [anchor-callee]
void __cdecl AppMain_QuoteFixString(char *zCommandline, char *zCmd)
{
  BOOL v3; // edx
  char *v4; // ecx
  char v5; // al

  v3 = 0;
  v4 = zCommandline;
  if ( *zCommandline )
  {
    do
    {
      v5 = *v4;
      if ( *v4 == 34 )
      {
        v3 = !v3;
      }
      else
      {
        if ( v3 || v5 != 32 )
          *zCmd = v5;
        else
          *zCmd = 1;
        ++zCmd;
      }
    }
    while ( *++v4 );
  }
}

// source: b/1/appmain.c:98  [anchor-callee]
void __cdecl AppMain_FindPrefix(
        char *zCommandline,
        char *zPrefix,
        void (__cdecl *pfParseCmdLineArg__)(char *))
{
  #pragma pack(push, 1)
  union
  {
    struct { enum bool isMatch; };
    struct { char igi2_o1[4]; char *zTemp; };
    struct { char igi2_o2[8]; char zTokens[4]; };
    struct { char igi2_o3[12]; char zCmdLine[1024]; };
    char igi2_extent[1036];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  char *v3; // eax
  signed int v4; // ebx
  char *v5; // edi
  int v6; // eax
  char v7; // cl
  char v8; // dl

  memset(igi2_frame.zCmdLine, 0, sizeof(igi2_frame.zCmdLine));
  _snprintf(igi2_frame.zTokens, 3u, "%c%c", 1, 9);
  AppMain_QuoteFixString(zCommandline, igi2_frame.zCmdLine);
  v3 = strtok(igi2_frame.zCmdLine, igi2_frame.zTokens);
  igi2_frame.zTemp = v3;
  if ( v3 )
  {
    while ( 1 )
    {
      if ( strlen(v3) >= strlen(zPrefix) )
      {
        igi2_frame.isMatch = true;
        v4 = 0;
        if ( (int)strlen(zPrefix) <= 0 )
        {
LABEL_19:
          pfParseCmdLineArg__(&v3[strlen(zPrefix)]);
        }
        else
        {
          v5 = zPrefix;
          v6 = v3 - zPrefix;
          while ( igi2_frame.isMatch )
          {
            v7 = v5[v6];
            v8 = *v5;
            if ( v7 >= 97 && v7 <= 122 )
              v7 -= 32;
            if ( v8 >= 97 && v8 <= 122 )
              v8 -= 32;
            if ( v7 != v8 )
              igi2_frame.isMatch = false;
            ++v4;
            ++v5;
            if ( v4 >= (int)strlen(zPrefix) )
            {
              if ( igi2_frame.isMatch == false )
                break;
              v3 = igi2_frame.zTemp;
              goto LABEL_19;
            }
          }
        }
      }
      igi2_frame.zTemp = strtok(nullptr, igi2_frame.zTokens);
      if ( !igi2_frame.zTemp )
        break;
      v3 = igi2_frame.zTemp;
    }
  }
}

// source: b/1/appmain.c:170  [anchor-caller]
void __cdecl AppMain_ParseCmdLineArgs(
        char *zPrefix,
        void (__cdecl *pfParseCmdLineArg__)(char *))
{
  AppMain_FindPrefix(AppContext_tAppContext.zCmdLine, zPrefix, pfParseCmdLineArg__);
}
