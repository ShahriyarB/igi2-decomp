/* b/1/calendar.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: b/1/calendar.c:29  [anchor-strings]
int __cdecl QCalendar_PrintDate(struct QCalendar_s *ptCalendar, char *zBuffer, int nBuffersize)
{
  return sprintf(zBuffer, "%04d-%02d-%02d", ptCalendar->nYear, ptCalendar->nMonth, ptCalendar->nDay);
}

// source: b/1/calendar.c:45  [anchor-strings]
int __cdecl QCalendar_PrintTime(struct QCalendar_s *ptCalendar, char *zBuffer, int nBuffersize)
{
  return sprintf(zBuffer, "%02d-%02d-%02d", ptCalendar->nHour, ptCalendar->nMinute, ptCalendar->nSecond);
}

// source: b/1/calendar.c:61  [size]
int __cdecl QCalendar_PrintMilliseconds(
        struct QCalendar_s *ptCalendar,
        char *zBuffer,
        int nBuffersize)
{
  return sprintf(zBuffer, "%04d", ptCalendar->nMilliseconds);
}

// source: b/1/calendar.c:81  [anchor-callee]
void __cdecl QCalendar_Init(struct QCalendar_s *ptCalendar)
{
  int wMonth; // edx
  int wDay; // eax
  int wHour; // ecx
  int wMinute; // edx
  int wSecond; // eax
  int wMilliseconds; // ecx
  struct _SYSTEMTIME tSystemTime; // [esp+0h] [ebp-10h] BYREF

  GetLocalTime(&tSystemTime);
  wMonth = tSystemTime.wMonth;
  wDay = tSystemTime.wDay;
  ptCalendar->nYear = tSystemTime.wYear;
  wHour = tSystemTime.wHour;
  ptCalendar->nMonth = wMonth;
  wMinute = tSystemTime.wMinute;
  ptCalendar->nDay = wDay;
  wSecond = tSystemTime.wSecond;
  ptCalendar->nHour = wHour;
  wMilliseconds = tSystemTime.wMilliseconds;
  ptCalendar->nMinute = wMinute;
  ptCalendar->nSecond = wSecond;
  ptCalendar->nMilliseconds = wMilliseconds;
}

// source: b/1/calendar.c:158  [anchor-strings]
int __cdecl QCalendar_Print(
        struct QCalendar_s *ptCalendar,
        char *zBuffer,
        int nBuffersize,
        int isPrintDate,
        int isPrintTime,
        int isPrintMilliseconds)
{
  char *v6; // esi
  int v7; // ebp
  BOOL v8; // edi
  int v9; // ebp
  char *v10; // esi

  v6 = zBuffer;
  v7 = 0;
  *zBuffer = 0;
  v8 = isPrintTime || isPrintMilliseconds;
  if ( isPrintDate )
  {
    v9 = sprintf(zBuffer, "%04d-%02d-%02d", ptCalendar->nYear, ptCalendar->nMonth, ptCalendar->nDay);
    if ( v8 )
    {
      strcat(v6, "-");
      ++v9;
    }
    v10 = &v6[strlen(v6)];
    v7 = sprintf(v10, "%02d-%02d-%02d", ptCalendar->nHour, ptCalendar->nMinute, ptCalendar->nSecond) + v9;
    if ( isPrintMilliseconds )
    {
      strcat(v10, "-");
      ++v7;
    }
    v6 = &v10[strlen(v10)];
  }
  if ( isPrintMilliseconds )
    v7 += sprintf(v6, "%04d", ptCalendar->nMilliseconds);
  return v7;
}

// source: b/1/calendar.c:203  [anchor-strings]
int __cdecl QCalendar_FromString(struct QCalendar_s *ptCalendar, char *zString)
{
  #pragma pack(push, 1)
  union
  {
    struct { int nYear; };
    struct { char igi2_o1[4]; int nMonth; };
    struct { char igi2_o2[8]; int nDay; };
    struct { char igi2_o3[12]; int nHour; };
    struct { char igi2_o4[16]; int nMinute; };
    struct { char igi2_o5[20]; int nSecond; };
    struct { char igi2_o6[24]; int nMillisecond; };
    struct { char igi2_o7[28]; int nTemp; };
    char igi2_extent[32];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  int v4; // ecx
  char v5; // al
  int v6; // ecx
  int v8; // edx
  int v9; // eax
  int v10; // ecx
  int v11; // eax
  int v12; // edx
  int v13; // ecx

  QCalendar_Init(ptCalendar);
  ptCalendar->nMilliseconds = 0;
  igi2_frame.nTemp = strlen(zString);
  if ( !igi2_frame.nTemp )
    return 0;
  v4 = ptCalendar->nMonth;
  igi2_frame.nYear = ptCalendar->nYear;
  igi2_frame.nDay = ptCalendar->nDay;
  v5 = *zString;
  igi2_frame.nMonth = v4;
  v6 = 0;
  igi2_frame.nHour = 0;
  igi2_frame.nMinute = 0;
  igi2_frame.nSecond = 0;
  igi2_frame.nMillisecond = 0;
  if ( !v5 )
    goto LABEL_9;
  do
  {
    if ( v5 == 45 )
      ++v6;
    v5 = *++zString;
  }
  while ( v5 );
  if ( v6 >= 5 )
  {
    if ( scprintf(zString, unk_685304, &igi2_frame.nYear, &igi2_frame.nMonth, &igi2_frame.nDay, &igi2_frame.nHour, &igi2_frame.nMinute, &igi2_frame.nSecond, &igi2_frame.nMillisecond) < 5 )
      return 0;
  }
  else
  {
LABEL_9:
    igi2_frame.nTemp = 0;
    scprintf(zString, &g_ptNetManager.tReceiveCounters.tCounters[9].nBytes, &igi2_frame.nTemp);
    if ( igi2_frame.nTemp <= 1999 )
    {
      if ( scprintf(zString, &g_ptParentQTask.tQTaskChildren, &igi2_frame.nHour, &igi2_frame.nMinute, &igi2_frame.nSecond, &igi2_frame.nMillisecond) < 3 )
        return 0;
    }
    else if ( scprintf(zString, unk_6852F8, &igi2_frame.nYear, &igi2_frame.nMonth, &igi2_frame.nDay) != 3 )
    {
      return 0;
    }
  }
  v8 = igi2_frame.nMonth;
  v9 = igi2_frame.nDay;
  ptCalendar->nYear = igi2_frame.nYear;
  v10 = igi2_frame.nHour;
  ptCalendar->nDay = v9;
  v11 = igi2_frame.nSecond;
  ptCalendar->nMonth = v8;
  v12 = igi2_frame.nMinute;
  ptCalendar->nHour = v10;
  v13 = igi2_frame.nMillisecond;
  ptCalendar->nSecond = v11;
  ptCalendar->nMinute = v12;
  ptCalendar->nMilliseconds = v13;
  return 1;
}

// source: b/1/calendar.c:294  [anchor-strings]
int __cdecl QCalendar_Compare(struct QCalendar_s *ptCalendar1, struct QCalendar_s *ptCalendar2)
{
  #pragma pack(push, 1)
  union
  {
    struct { int v11; };
    struct { char igi2_o1[4]; int v12; };
    struct { char igi2_o2[8]; int v13; };
    struct { char igi2_o3[16]; int nYear; };
    struct { char igi2_o4[20]; int nMonth; };
    struct { char igi2_o5[24]; int nDay; };
    struct { char igi2_o6[39]; char v17; };
    struct { char igi2_o7[40]; char zTemp2[256]; };
    struct { char igi2_o8[296]; char zTemp1[256]; };
    char igi2_extent[552];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  char *v4; // edi
  char *v6; // ebp
  char *v7; // edi
  char *v9; // esi

  igi2_frame.nDay = ptCalendar1->nDay;
  igi2_frame.nMonth = ptCalendar1->nMonth;
  igi2_frame.nYear = ptCalendar1->nYear;
  igi2_frame.zTemp1[0] = 0;
  sprintf(igi2_frame.zTemp1, "%04d-%02d-%02d", igi2_frame.nYear, igi2_frame.nMonth, igi2_frame.nDay);
  v4 = &igi2_frame.zTemp2[255];
  while ( *++v4 )
    ;
  strcpy(v4, "-");
  v6 = &igi2_frame.zTemp1[strlen(igi2_frame.zTemp1)];
  sprintf(v6, "%02d-%02d-%02d", ptCalendar1->nHour, ptCalendar1->nMinute, ptCalendar1->nSecond);
  strcat(v6, "-");
  sprintf(&v6[strlen(v6)], "%04d", ptCalendar1->nMilliseconds);
  igi2_frame.v13 = ptCalendar2->nDay;
  igi2_frame.v12 = ptCalendar2->nMonth;
  igi2_frame.v11 = ptCalendar2->nYear;
  igi2_frame.zTemp2[0] = 0;
  sprintf(igi2_frame.zTemp2, "%04d-%02d-%02d", igi2_frame.v11, igi2_frame.v12, igi2_frame.v13);
  v7 = &igi2_frame.v17;
  while ( *++v7 )
    ;
  strcpy(v7, "-");
  v9 = &igi2_frame.zTemp2[strlen(igi2_frame.zTemp2)];
  sprintf(v9, "%02d-%02d-%02d", ptCalendar2->nHour, ptCalendar2->nMinute, ptCalendar2->nSecond);
  strcat(v9, "-");
  sprintf(&v9[strlen(v9)], "%04d", ptCalendar2->nMilliseconds);
  return strcmp(igi2_frame.zTemp1, igi2_frame.zTemp2);
}

// source: b/1/calendar.c:324  [anchor-mhash]
int __cdecl QCalendar_GetDifferenceInDays(
        struct QCalendar_s *ptCalendar1,
        struct QCalendar_s *ptCalendar2)
{
  return ptCalendar1->nDay
       + 365 * (ptCalendar1->nYear - ptCalendar2->nYear)
       + 31 * (ptCalendar1->nMonth - ptCalendar2->nMonth)
       - ptCalendar2->nDay;
}

// source: b/1/calendar.c:355  [anchor-mhash]
int __cdecl QCalendar_GetDifferenceInMilliseconds(
        struct QCalendar_s *ptCalendar1,
        struct QCalendar_s *ptCalendar2)
{
  int v2; // eax

  v2 = ptCalendar1->nDay
     + 365 * (ptCalendar1->nYear - ptCalendar2->nYear)
     + 31 * (ptCalendar1->nMonth - ptCalendar2->nMonth)
     - ptCalendar2->nDay;
  if ( v2 >= 12 )
    return 0x40000000;
  if ( v2 > -12 )
    return ptCalendar1->nMilliseconds
         + 1000
         * (ptCalendar1->nSecond
          + 60
          * (ptCalendar1->nMinute + 60 * (ptCalendar1->nHour + 24 * v2 - ptCalendar2->nHour) - ptCalendar2->nMinute)
          - ptCalendar2->nSecond)
         - ptCalendar2->nMilliseconds;
  return -1073741824;
}
