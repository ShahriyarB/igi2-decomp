/* j/0/gfxoptions.c -- decompiled from the retail exe; do not edit (see overrides/). */
#include "igi2.h"

// source: j/0/gfxoptions.c:107  [anchor-mhash]
void __cdecl GfxOptions_ApplyCurrentOptionsToPlayerProfile(
        struct PlayerProfile_s *ptPlayerProfile,
        enum bool isForceApply)
{
  bool v2; // zf

  v2 = GfxOptions_eDetailLevel == GFXOPTIONS_DETAIL_CUSTOM;
  ptPlayerProfile->tGraphicOptions.eDetailLevel = GfxOptions_eDetailLevel;
  if ( v2 || isForceApply )
    qmemcpy(
      &ptPlayerProfile->tGraphicOptions.tGfxOptions,
      &GfxOptions_tActiveOptions,
      sizeof(ptPlayerProfile->tGraphicOptions.tGfxOptions));
}

// source: j/0/gfxoptions.c:125  [anchor-hash]
char *__cdecl GfxOptions_GetDetailName(enum GfxOptDetail_e eDetailLevel)
{
  if ( eDetailLevel < GFXOPTIONS_DETAIL_HIGH )
    return GfxOptions_apzDetail[0];
  if ( eDetailLevel > GFXOPTIONS_DETAIL_CUSTOM )
    eDetailLevel = GFXOPTIONS_DETAIL_CUSTOM;
  return GfxOptions_apzDetail[eDetailLevel];
}

// source: j/0/gfxoptions.c:139  [anchor-hash]
char *__cdecl GfxOptions_GetTextureDetailName(enum GfxOptTexDetail_e eTextureDetail)
{
  if ( eTextureDetail < GFXOPTIONS_TEXTUREDETAIL_HIGH )
    return GfxOptions_apzTextureDetail[0];
  if ( eTextureDetail > GFXOPTIONS_TEXTUREDETAIL_ULTRALOW )
    eTextureDetail = GFXOPTIONS_TEXTUREDETAIL_ULTRALOW;
  return GfxOptions_apzTextureDetail[eTextureDetail];
}

// source: j/0/gfxoptions.c:155  [anchor-mhash]
struct Result_s *__cdecl GfxOptions_ApplyCurrentOptions(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  int v3; // eax
  struct GfxOptions_s *v4; // edi
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  v3 = 2752 * Config_tConfig.iActiveProfile + 7392072;
  *(_DWORD *)(v3 + 12) = GfxOptions_eDetailLevel;
  v4 = (struct GfxOptions_s *)(v3 + 16);
  qmemcpy(v4, &GfxOptions_tActiveOptions, sizeof(struct GfxOptions_s));
  Rs.nResult = 0;
  Rs.vResult = 0.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/gfxoptions.c:173  [anchor-mhash]
struct Result_s *__cdecl GfxOptions_ApplyCurrentOptionsToLastPlayerProfile(
        struct Result_s *retstr,
        void *pxContex,
        struct ArgList_s *ptArgList)
{
  int *v3; // eax
  struct Result_s Rs; // [esp+0h] [ebp-18h] BYREF

  if ( Config_tConfig.nPlayerProfiles )
    v3 = &Config_atDisplayDevice[4].tDisplayModeList[33].nHeight + 688 * Config_tConfig.nPlayerProfiles;
  else
    v3 = nullptr;
  v3[3] = GfxOptions_eDetailLevel;
  qmemcpy(v3 + 4, &GfxOptions_tActiveOptions, 0x28u);
  Rs.nResult = 0;
  Rs.vResult = 0.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/gfxoptions.c:188  [anchor-mhash]
struct Result_s *__cdecl GfxOptions_IsCustomDetail(
        struct Result_s *retstr,
        void *pxUnused,
        struct ArgList_s *ptArgList)
{
  struct Result_s Rs; // [esp+Ch] [ebp-18h] BYREF

  Rs.zResult = (char *)&g_zInitialValue;
  Rs.nResult = GfxOptions_eDetailLevel == GFXOPTIONS_DETAIL_CUSTOM;
  Rs.vResult = (double)Rs.nResult;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/gfxoptions.c:201  [anchor-mhash]
struct Result_s *__cdecl GfxOptions_SetBoolValue(
        struct Result_s *retstr,
        void *pxValue,
        struct ArgList_s *ptArgList)
{
  struct ArgList_s *v3; // edi
  struct ArgList_s *v4; // eax
  bool v5; // zf
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  v3 = ptArgList;
  if ( ptArgList->isQVM )
  {
    ptArgList = nullptr;
    QVM_EvalArg(&ptArgList, 4, v3, 0, 1);
    v4 = ptArgList;
  }
  else
  {
    v4 = (struct ArgList_s *)Expression_EvalInt(*ptArgList->aptExpression);
  }
  v5 = v4 == nullptr;
  Rs.nResult = 0;
  Rs.vResult = 0.0;
  Rs.zResult = (char *)&g_zInitialValue;
  *(_DWORD *)pxValue = !v5;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/gfxoptions.c:219  [size]
struct Result_s *__cdecl GfxOptions_GetBoolValue(
        struct Result_s *retstr,
        void *pxValue,
        struct ArgList_s *ptArgList)
{
  struct Result_s Rs; // [esp+4h] [ebp-18h] BYREF

  Rs.nResult = *(_DWORD *)pxValue;
  Rs.vResult = (double)Rs.nResult;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/gfxoptions.c:238  [anchor-strings]
struct Result_s *__cdecl GfxOptions_FillDetailLevelListBox(
        struct Result_s *retstr,
        void *pxUnused,
        struct ArgList_s *ptArgList)
{
  char *LocalizedStringForLanguage; // eax
  char *v4; // eax
  char *v5; // eax
  char *v6; // eax
  struct Result_s Rs; // [esp+Ch] [ebp-18h] BYREF

  LocalizedStringForLanguage = Config_GetLocalizedStringForLanguage(
                                 "High Detail",
                                 Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eLanguage,
                                 true);
  ListBox_AddItem(LocalizedStringForLanguage, 0);
  v4 = Config_GetLocalizedStringForLanguage(
         "Medium Detail",
         Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eLanguage,
         true);
  ListBox_AddItem(v4, 1);
  v5 = Config_GetLocalizedStringForLanguage(
         "Low Detail",
         Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eLanguage,
         true);
  ListBox_AddItem(v5, 2);
  v6 = Config_GetLocalizedStringForLanguage(
         "Custom Detail",
         Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eLanguage,
         true);
  ListBox_AddItem(v6, 3);
  Rs.nResult = 0;
  Rs.vResult = 0.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/gfxoptions.c:255  [anchor-mhash]
struct Result_s *__cdecl GfxOptions_SetDetailLevelFromScript(
        struct Result_s *retstr,
        void *pxUnused,
        struct ArgList_s *ptArgList)
{
  struct ArgList_s *v3; // edi
  struct ArgList_s *v4; // eax
  enum GfxOptDetail_e v5; // eax
  struct ArgList_s *v6; // eax
  void *v7; // esi
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  v3 = ptArgList;
  if ( ptArgList->isQVM )
  {
    ptArgList = nullptr;
    QVM_EvalArg(&ptArgList, 4, v3, 0, 1);
    v4 = ptArgList;
  }
  else
  {
    v4 = (struct ArgList_s *)Expression_EvalInt(*ptArgList->aptExpression);
  }
  if ( (int)v4 >= 0 )
  {
    if ( v3->isQVM )
    {
      ptArgList = nullptr;
      QVM_EvalArg(&ptArgList, 4, v3, 0, 1);
      v6 = ptArgList;
    }
    else
    {
      v6 = (struct ArgList_s *)Expression_EvalInt(*v3->aptExpression);
    }
    if ( (int)v6 <= 3 )
      v5 = Script_EvalArgInt(v3, 0);
    else
      v5 = GFXOPTIONS_DETAIL_CUSTOM;
  }
  else
  {
    v5 = GFXOPTIONS_DETAIL_HIGH;
  }
  v7 = (void *)(2752 * Config_tConfig.iActiveProfile + 7392088);
  GfxOptions_eDetailLevel = v5;
  if ( v5 != GFXOPTIONS_DETAIL_CUSTOM || 2752 * Config_tConfig.iActiveProfile == -7392088 )
    v7 = (void *)(40 * v5 + 6828624);
  qmemcpy(&GfxOptions_tActiveOptions, v7, sizeof(GfxOptions_tActiveOptions));
  Rs.nResult = 0;
  Rs.vResult = 0.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/gfxoptions.c:270  [anchor-mhash]
struct Result_s *__cdecl GfxOptions_SetDetailLevelFromConfigFile(
        struct Result_s *retstr,
        void *pxUnused,
        struct ArgList_s *ptArgList)
{
  struct ArgList_s *v3; // edi
  struct ArgList_s *v4; // eax
  struct ArgList_s *v5; // eax
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  v3 = ptArgList;
  if ( ptArgList->isQVM )
  {
    ptArgList = nullptr;
    QVM_EvalArg(&ptArgList, 4, v3, 0, 1);
    v4 = ptArgList;
  }
  else
  {
    v4 = (struct ArgList_s *)Expression_EvalInt(*ptArgList->aptExpression);
  }
  if ( (int)v4 >= 0 )
  {
    if ( v3->isQVM )
    {
      ptArgList = nullptr;
      QVM_EvalArg(&ptArgList, 4, v3, 0, 1);
      v5 = ptArgList;
    }
    else
    {
      v5 = (struct ArgList_s *)Expression_EvalInt(*v3->aptExpression);
    }
    if ( (int)v5 <= 3 )
      GfxOptions_eDetailLevel = Script_EvalArgInt(v3, 0);
    else
      GfxOptions_eDetailLevel = GFXOPTIONS_DETAIL_CUSTOM;
  }
  else
  {
    GfxOptions_eDetailLevel = GFXOPTIONS_DETAIL_HIGH;
  }
  Rs.nResult = 0;
  Rs.vResult = 0.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/gfxoptions.c:284  [size]
struct Result_s *__cdecl GfxOptions_GetDetailLevelFromScript(
        struct Result_s *retstr,
        void *pxUnused,
        struct ArgList_s *ptArgList)
{
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  Rs.nResult = GfxOptions_eDetailLevel;
  Rs.vResult = (double)(int)GfxOptions_eDetailLevel;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/gfxoptions.c:299  [anchor-strings]
struct Result_s *__cdecl GfxOptions_FillTextureDetailListBox(
        struct Result_s *retstr,
        void *pxUnused,
        struct ArgList_s *ptArgList)
{
  char *LocalizedStringForLanguage; // eax
  char *v4; // eax
  char *v5; // eax
  struct Result_s Rs; // [esp+Ch] [ebp-18h] BYREF

  LocalizedStringForLanguage = Config_GetLocalizedStringForLanguage(
                                 "High Texture Detail",
                                 Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eLanguage,
                                 true);
  ListBox_AddItem(LocalizedStringForLanguage, 0);
  v4 = Config_GetLocalizedStringForLanguage(
         "Low Texture Detail",
         Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eLanguage,
         true);
  ListBox_AddItem(v4, 1);
  v5 = Config_GetLocalizedStringForLanguage(
         "Ultra Low Texture Detail",
         Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eLanguage,
         true);
  ListBox_AddItem(v5, 2);
  Rs.nResult = 0;
  Rs.vResult = 0.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/gfxoptions.c:315  [size]
struct Result_s *__cdecl GfxOptions_SetTextureDetailFromScript(
        struct Result_s *retstr,
        void *pxUnused,
        struct ArgList_s *ptArgList)
{
  struct ArgList_s *v3; // edi
  struct ArgList_s *v4; // eax
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  v3 = ptArgList;
  if ( ptArgList->isQVM )
  {
    ptArgList = nullptr;
    QVM_EvalArg(&ptArgList, 4, v3, 0, 1);
    v4 = ptArgList;
  }
  else
  {
    v4 = (struct ArgList_s *)Expression_EvalInt(*ptArgList->aptExpression);
  }
  GfxOptions_tActiveOptions.eTextureDetail = (enum GfxOptTexDetail_e)v4;
  Rs.nResult = 0;
  Rs.vResult = 0.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/gfxoptions.c:329  [size]
struct Result_s *__cdecl GfxOptions_GetTextureDetailFromScript(
        struct Result_s *retstr,
        void *pxUnused,
        struct ArgList_s *ptArgList)
{
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  Rs.nResult = GfxOptions_tActiveOptions.eTextureDetail;
  Rs.vResult = (double)(int)GfxOptions_tActiveOptions.eTextureDetail;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/gfxoptions.c:344  [size]
struct Result_s *__cdecl GfxOptions_FillWaterQualityLevelListBox(
        struct Result_s *retstr,
        void *pxUnused,
        struct ArgList_s *ptArgList)
{
  char *LocalizedStringForLanguage; // eax
  int v4; // esi
  int v5; // edi
  char *v6; // eax
  int v7; // esi
  int v8; // edi
  char *v9; // eax
  struct Result_s Rs; // [esp+Ch] [ebp-18h] BYREF

  LocalizedStringForLanguage = Config_GetLocalizedStringForLanguage(
                                 "Normal Water Quality",
                                 Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eLanguage,
                                 true);
  ListBox_AddItem(LocalizedStringForLanguage, 0);
  v4 = WaterRender_iQualityLevel;
  v5 = WaterRender_SetQualityLevel(3);
  WaterRender_SetQualityLevel(v4);
  if ( v5 >= 1 )
  {
    v6 = Config_GetLocalizedStringForLanguage(
           "High Water Quality",
           Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eLanguage,
           true);
    ListBox_AddItem(v6, 1);
    v7 = WaterRender_iQualityLevel;
    v8 = WaterRender_SetQualityLevel(3);
    WaterRender_SetQualityLevel(v7);
    if ( v8 >= 2 )
    {
      v9 = Config_GetLocalizedStringForLanguage(
             "Highest Water Quality",
             Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eLanguage,
             true);
      ListBox_AddItem(v9, 2);
    }
  }
  Rs.nResult = 0;
  Rs.vResult = 0.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/gfxoptions.c:366  [size]
struct Result_s *__cdecl GfxOptions_SetWaterQualityLevel(
        struct Result_s *retstr,
        void *pxUnused,
        struct ArgList_s *ptArgList)
{
  struct ArgList_s *v3; // edi
  struct ArgList_s *v4; // eax
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  v3 = ptArgList;
  if ( ptArgList->isQVM )
  {
    ptArgList = nullptr;
    QVM_EvalArg(&ptArgList, 4, v3, 0, 1);
    v4 = ptArgList;
  }
  else
  {
    v4 = (struct ArgList_s *)Expression_EvalInt(*ptArgList->aptExpression);
  }
  GfxOptions_tActiveOptions.eWaterQualityLevel = (enum WaterQualityLevel_e)v4;
  Rs.nResult = 0;
  Rs.vResult = 0.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/gfxoptions.c:380  [size]
struct Result_s *__cdecl GfxOptions_GetWaterQualityLevel(
        struct Result_s *retstr,
        void *pxUnused,
        struct ArgList_s *ptArgList)
{
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  Rs.nResult = GfxOptions_tActiveOptions.eWaterQualityLevel;
  Rs.vResult = (double)(int)GfxOptions_tActiveOptions.eWaterQualityLevel;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/gfxoptions.c:393  [anchor-hash]
char *__cdecl GfxOptions_GetWaterQualityLevelName(int eQualityLevel)
{
  if ( !eQualityLevel )
    return "WATERRENDER_QUALITY_NORMAL";
  if ( eQualityLevel == 1 )
    return "WATERRENDER_QUALITY_HIGH";
  return "WATERRENDER_QUALITY_HIGHEST";
}

// source: j/0/gfxoptions.c:418  [anchor-hash]
char *__cdecl GfxOptions_GetTextureFilteringModeName(int eMode)
{
  int v1; // eax

  v1 = eMode - 1;
  if ( !v1 )
    return "DIRECT3DRENDER_FILTERINGTYPE_TRILINEAR";
  if ( v1 == 1 )
    return "DIRECT3DRENDER_FILTERINGTYPE_ANISOTROPIC";
  return "DIRECT3DRENDER_FILTERINGTYPE_BILINEAR";
}

// source: j/0/gfxoptions.c:441  [size]
struct Result_s *__cdecl GfxOptions_FillTextureFilteringModeListBox(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  char *LocalizedStringForLanguage; // eax
  char *v4; // eax
  char *v5; // eax
  struct Result_s Rs; // [esp+Ch] [ebp-18h] BYREF

  LocalizedStringForLanguage = Config_GetLocalizedStringForLanguage(
                                 "Bilinear Filtering",
                                 Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eLanguage,
                                 true);
  ListBox_AddItem(LocalizedStringForLanguage, 0);
  if ( Direct3DRender_SetFilteringMode(Direct3DRender_eFilteringType) >= 1 )
  {
    v4 = Config_GetLocalizedStringForLanguage(
           "Trilinear Filtering",
           Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eLanguage,
           true);
    ListBox_AddItem(v4, 1);
    if ( Direct3DRender_SetFilteringMode(Direct3DRender_eFilteringType) >= 2 )
    {
      v5 = Config_GetLocalizedStringForLanguage(
             "Anisotropic Filtering",
             Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eLanguage,
             true);
      ListBox_AddItem(v5, 2);
    }
  }
  Rs.nResult = 0;
  Rs.vResult = 0.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/gfxoptions.c:463  [size]
struct Result_s *__cdecl GfxOptions_GetTextureFilteringMode(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  struct Result_s Rs; // [esp+Ch] [ebp-18h] BYREF

  Rs.nResult = Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGraphicOptions.eTextureFilteringMode;
  Rs.vResult = (double)Rs.nResult;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/gfxoptions.c:476  [size]
struct Result_s *__cdecl GfxOptions_SetTextureFilteringMode(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  struct ArgList_s *v3; // edi
  struct ArgList_s *v4; // eax
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  v3 = ptArgList;
  if ( ptArgList->isQVM )
  {
    ptArgList = nullptr;
    QVM_EvalArg(&ptArgList, 4, v3, 0, 1);
    v4 = ptArgList;
  }
  else
  {
    v4 = (struct ArgList_s *)Expression_EvalInt(*ptArgList->aptExpression);
  }
  Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGraphicOptions.eTextureFilteringMode = (int)v4;
  Rs.nResult = 0;
  Rs.vResult = 0.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/gfxoptions.c:490  [size]
struct Result_s *__cdecl GfxOptions_ConfigSetTextureFilteringMode(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  struct ArgList_s *v3; // edi
  struct ArgList_s *v4; // eax
  int *v5; // ecx
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  v3 = ptArgList;
  if ( ptArgList->isQVM )
  {
    ptArgList = nullptr;
    QVM_EvalArg(&ptArgList, 4, v3, 0, 1);
    v4 = ptArgList;
  }
  else
  {
    v4 = (struct ArgList_s *)Expression_EvalInt(*ptArgList->aptExpression);
  }
  if ( Config_tConfig.nPlayerProfiles )
    v5 = &Config_atDisplayDevice[4].tDisplayModeList[33].nHeight + 688 * Config_tConfig.nPlayerProfiles;
  else
    v5 = nullptr;
  v5[153] = (int)v4;
  Rs.nResult = 0;
  Rs.vResult = 0.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/gfxoptions.c:506  [anchor-hash]
char *__cdecl GfxOptions_GetAntialiasingModeName(int eMode)
{
  int v1; // eax
  int v2; // eax

  v1 = eMode - 1;
  if ( !v1 )
    return "GFXOPTIONS_ANTIALIASING_X2";
  v2 = v1 - 1;
  if ( !v2 )
    return "GFXOPTIONS_ANTIALIASING_X4";
  if ( v2 == 1 )
    return "GFXOPTIONS_ANTIALIASING_X6";
  return "GFXOPTIONS_ANTIALIASING_DISABLED";
}

// source: j/0/gfxoptions.c:532  [anchor-strings]
struct Result_s *__cdecl GfxOptions_FillAntialiasingModeListBox(
        struct Result_s *retstr,
        void *pxUnused,
        struct ArgList_s *ptArgList)
{
  char *LocalizedStringForLanguage; // eax
  char *v4; // eax
  char *v5; // eax
  char *v6; // eax
  struct Result_s Rs; // [esp+Ch] [ebp-18h] BYREF

  LocalizedStringForLanguage = Config_GetLocalizedStringForLanguage(
                                 "Antialiasing Disabled",
                                 Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eLanguage,
                                 true);
  ListBox_AddItem(LocalizedStringForLanguage, 0);
  v4 = Config_GetLocalizedStringForLanguage(
         "Antialiasing x 2",
         Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eLanguage,
         true);
  ListBox_AddItem(v4, 1);
  v5 = Config_GetLocalizedStringForLanguage(
         "Antialiasing x 4",
         Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eLanguage,
         true);
  ListBox_AddItem(v5, 2);
  v6 = Config_GetLocalizedStringForLanguage(
         "Antialiasing x 6",
         Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGameOptions.eLanguage,
         true);
  ListBox_AddItem(v6, 3);
  Rs.nResult = 0;
  Rs.vResult = 0.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/gfxoptions.c:549  [size]
struct Result_s *__cdecl GfxOptions_GetAntialiasingMode(
        struct Result_s *retstr,
        void *pxUnused,
        struct ArgList_s *ptArgList)
{
  struct Result_s Rs; // [esp+Ch] [ebp-18h] BYREF

  Rs.nResult = Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGraphicOptions.eAntialiasingMode;
  Rs.vResult = (double)Rs.nResult;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/gfxoptions.c:562  [size]
struct Result_s *__cdecl GfxOptions_SetAntialiasingMode(
        struct Result_s *retstr,
        void *pxUnused,
        struct ArgList_s *ptArgList)
{
  struct ArgList_s *v3; // edi
  struct ArgList_s *v4; // eax
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  v3 = ptArgList;
  if ( ptArgList->isQVM )
  {
    ptArgList = nullptr;
    QVM_EvalArg(&ptArgList, 4, v3, 0, 1);
    v4 = ptArgList;
  }
  else
  {
    v4 = (struct ArgList_s *)Expression_EvalInt(*ptArgList->aptExpression);
  }
  Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGraphicOptions.eAntialiasingMode = (int)v4;
  Rs.nResult = 0;
  Rs.vResult = 0.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/gfxoptions.c:576  [size]
struct Result_s *__cdecl GfxOptions_ConfigSetAntialiasingMode(
        struct Result_s *retstr,
        void *pxUnused,
        struct ArgList_s *ptArgList)
{
  struct ArgList_s *v3; // edi
  struct ArgList_s *v4; // eax
  int *v5; // ecx
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  v3 = ptArgList;
  if ( ptArgList->isQVM )
  {
    ptArgList = nullptr;
    QVM_EvalArg(&ptArgList, 4, v3, 0, 1);
    v4 = ptArgList;
  }
  else
  {
    v4 = (struct ArgList_s *)Expression_EvalInt(*ptArgList->aptExpression);
  }
  if ( Config_tConfig.nPlayerProfiles )
    v5 = &Config_atDisplayDevice[4].tDisplayModeList[33].nHeight + 688 * Config_tConfig.nPlayerProfiles;
  else
    v5 = nullptr;
  v5[152] = (int)v4;
  Rs.nResult = 0;
  Rs.vResult = 0.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/gfxoptions.c:592  [anchor-mhash]
struct Result_s *__cdecl GfxOptions_GetTerrainDetailLevel(
        struct Result_s *retstr,
        void *pxUnused,
        struct ArgList_s *ptArgList)
{
  struct Result_s Rs; // [esp+Ch] [ebp-18h] BYREF

  Rs.nResult = (__int64)GfxOptions_tActiveOptions.vTerrainDetail;
  Rs.vResult = GfxOptions_tActiveOptions.vTerrainDetail;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/gfxoptions.c:605  [anchor-mhash]
struct Result_s *__cdecl GfxOptions_SetTerrainDetailLevel(
        struct Result_s *retstr,
        void *pxUnused,
        struct ArgList_s *ptArgList)
{
  #pragma pack(push, 1)
  union
  {
    struct { float pxData; };
    struct { char igi2_o1[4]; struct Result_s Rs; };
    char igi2_extent[28];
  } igi2_frame; // the original stack frame: every local at its own offset
  #pragma pack(pop)
  double v3; // st7
  double v4; // st7
  double v5; // st7

  if ( ptArgList->isQVM )
  {
    igi2_frame.pxData = 0.0;
    QVM_EvalArg(&igi2_frame.pxData, 4, ptArgList, 0, 2);
    v3 = igi2_frame.pxData;
  }
  else
  {
    v3 = Expression_EvalFloat(*ptArgList->aptExpression);
  }
  if ( v3 >= 0.0 )
  {
    if ( ptArgList->isQVM )
    {
      igi2_frame.pxData = 0.0;
      QVM_EvalArg(&igi2_frame.pxData, 4, ptArgList, 0, 2);
      v5 = igi2_frame.pxData;
    }
    else
    {
      v5 = Expression_EvalFloat(*ptArgList->aptExpression);
    }
    if ( v5 <= 1.0 )
      v4 = Script_EvalArgFloat(ptArgList, 0);
    else
      v4 = 1.0;
  }
  else
  {
    v4 = 0.0;
  }
  GfxOptions_tActiveOptions.vTerrainDetail = v4;
  igi2_frame.Rs.nResult = 0;
  igi2_frame.Rs.vResult = 0.0;
  igi2_frame.Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &igi2_frame.Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/gfxoptions.c:621  [anchor-mhash]
struct Result_s *__cdecl GfxOptions_SetLODBias(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  struct ArgList_s *v3; // edi
  double v4; // st7
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  v3 = ptArgList;
  if ( ptArgList->isQVM )
  {
    *(float *)&ptArgList = 0.0;
    QVM_EvalArg(&ptArgList, 4, v3, 0, 2);
    v4 = *(float *)&ptArgList;
  }
  else
  {
    v4 = Expression_EvalFloat(*ptArgList->aptExpression);
  }
  GfxOptions_tActiveOptions.vModelDetail = 1.0 - v4;
  Rs.nResult = 0;
  Rs.vResult = 0.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/gfxoptions.c:635  [size]
struct Result_s *__cdecl GfxOptions_SetModelDetail(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  struct ArgList_s *v3; // edi
  double v4; // st7
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  v3 = ptArgList;
  if ( ptArgList->isQVM )
  {
    *(float *)&ptArgList = 0.0;
    QVM_EvalArg(&ptArgList, 4, v3, 0, 2);
    v4 = *(float *)&ptArgList;
  }
  else
  {
    v4 = Expression_EvalFloat(*ptArgList->aptExpression);
  }
  GfxOptions_tActiveOptions.vModelDetail = v4;
  Rs.nResult = 0;
  Rs.vResult = 0.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/gfxoptions.c:649  [anchor-mhash]
struct Result_s *__cdecl GfxOptions_GetModelDetail(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  double vModelDetail; // st7
  double v4; // st7
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  if ( GfxOptions_tActiveOptions.vModelDetail >= 0.0 )
  {
    if ( GfxOptions_tActiveOptions.vModelDetail <= 1.0 )
      vModelDetail = GfxOptions_tActiveOptions.vModelDetail;
    else
      vModelDetail = 1.0;
  }
  else
  {
    vModelDetail = 0.0;
  }
  Rs.nResult = (__int64)vModelDetail;
  if ( GfxOptions_tActiveOptions.vModelDetail >= 0.0 )
  {
    if ( GfxOptions_tActiveOptions.vModelDetail <= 1.0 )
      v4 = GfxOptions_tActiveOptions.vModelDetail;
    else
      v4 = 1.0;
  }
  else
  {
    v4 = 0.0;
  }
  Rs.vResult = v4;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/gfxoptions.c:664  [anchor-mhash]
struct Result_s *__cdecl GfxOptions_GetGfxOptionsFromActivePlayerProfile(
        struct Result_s *retstr,
        void *pxContext,
        struct ArgList_s *ptArgList)
{
  struct GfxOptions_s *p_tGfxOptions; // esi
  struct Result_s Rs; // [esp+8h] [ebp-18h] BYREF

  p_tGfxOptions = &Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGraphicOptions.tGfxOptions;
  GfxOptions_eDetailLevel = Config_tConfig.atPlayerProfile[Config_tConfig.iActiveProfile].tGraphicOptions.eDetailLevel;
  if ( GfxOptions_eDetailLevel != GFXOPTIONS_DETAIL_CUSTOM || !p_tGfxOptions )
    p_tGfxOptions = (struct GfxOptions_s *)(40 * GfxOptions_eDetailLevel + 6828624);
  qmemcpy(&GfxOptions_tActiveOptions, p_tGfxOptions, sizeof(GfxOptions_tActiveOptions));
  Rs.nResult = 0;
  Rs.vResult = 0.0;
  Rs.zResult = (char *)&g_zInitialValue;
  qmemcpy(retstr, &Rs, sizeof(struct Result_s));
  return retstr;
}

// source: j/0/gfxoptions.c:680  [size]
struct GfxOptions_s *__cdecl GfxOptions_GetDefaultGfxOptionsForDetailLevel(
        enum GfxOptDetail_e eDetailLevel)
{
  return (struct GfxOptions_s *)(40 * eDetailLevel + 6828624);
}

// source: j/0/gfxoptions.c:694  [size]
struct GfxOptions_s *__cdecl GfxOptions_GetActiveGfxOptions()
{
  return &GfxOptions_tActiveOptions;
}

// source: j/0/gfxoptions.c:707  [size]
enum GfxOptDetail_e __cdecl GfxOptions_GetDetailLevel()
{
  return GfxOptions_eDetailLevel;
}

// source: j/0/gfxoptions.c:722  [anchor-mhash]
enum GfxOptDetail_e __cdecl GfxOptions_SetActiveGfxOptions(
        enum GfxOptDetail_e eDetailLevel,
        struct GfxOptions_s *ptGfxOptions)
{
  struct GfxOptions_s *v2; // esi

  v2 = ptGfxOptions;
  GfxOptions_eDetailLevel = eDetailLevel;
  if ( eDetailLevel != GFXOPTIONS_DETAIL_CUSTOM || !ptGfxOptions )
    v2 = (struct GfxOptions_s *)(40 * eDetailLevel + 6828624);
  qmemcpy(&GfxOptions_tActiveOptions, v2, sizeof(GfxOptions_tActiveOptions));
  return eDetailLevel;
}

// source: j/0/gfxoptions.c:741  [anchor-strings]
struct PlayerProfile_s *__cdecl GfxOptions_WriteGraphicOptions(
        struct File_s *ptFile,
        struct PlayerProfile_s *ptPlayerProfile)
{
  File_printf(ptFile, "GfxOptions_SetDetailLevelFromConfigFile(%s);\r\n");
  File_printf(ptFile, "GfxOptions_SetTextureDetailFromScript(%s);\r\n");
  File_printf(ptFile, "GfxOptions_SetModelDetail(%.02f);\r\n");
  File_printf(ptFile, "GfxOptions_SetStencilShadows(%s);\r\n");
  File_printf(ptFile, "GfxOptions_SetTextureCompression(%s);\r\n");
  File_printf(ptFile, "GfxOptions_SetHighQualityForests(%s);\r\n");
  File_printf(ptFile, "GfxOptions_SetWindOnForests(%s);\r\n");
  File_printf(ptFile, &g_ptFile.zFilename[248]);
  File_printf(ptFile, &g_ptFile.zFilename[208]);
  File_printf(ptFile, &g_ptFile.zFilename[168]);
  File_printf(ptFile, &g_ptFile.zFilename[124]);
  File_printf(ptFile, &g_ptFile.zFilename[80]);
  File_printf(ptFile, &g_ptFile.zFilename[32]);
  return (struct PlayerProfile_s *)File_printf(ptFile, (char *)&g_ptFile);
}

// source: j/0/gfxoptions.c:770  [anchor-hash]
struct PlayerProfile_s *__cdecl GfxOptions_SetDefaultOptionsForPlayerProfile(
        struct PlayerProfile_s *ptPlayerProfile)
{
  ptPlayerProfile->tGraphicOptions.eDetailLevel = GFXOPTIONS_DETAIL_HIGH;
  qmemcpy(
    &ptPlayerProfile->tGraphicOptions.tGfxOptions,
    &GfxOptions_atDefaultOptions[3],
    sizeof(ptPlayerProfile->tGraphicOptions.tGfxOptions));
  return ptPlayerProfile;
}

// source: j/0/gfxoptions.c:786  [anchor-hash]
void __cdecl GfxOptions_Open()
{
  GfxOptions_eDetailLevel = GFXOPTIONS_DETAIL_HIGH;
  qmemcpy(&GfxOptions_tActiveOptions, GfxOptions_atDefaultOptions, sizeof(GfxOptions_tActiveOptions));
  Symbol_Register(
    "GfxOptions_IsCustomDetail",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))GfxOptions_IsCustomDetail,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "GfxOptions_ApplyCurrentOptions",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))GfxOptions_ApplyCurrentOptions,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "GfxOptions_ApplyCurrentOptionsToLastPlayerProfile",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))GfxOptions_ApplyCurrentOptionsToLastPlayerProfile,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "GfxOptions_GetGfxOptionsFromActivePlayerProfile",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))GfxOptions_GetGfxOptionsFromActivePlayerProfile,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "GfxOptions_IsStencilShadows",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))GfxOptions_GetBoolValue,
    &GfxOptions_tActiveOptions.isStencilShadows,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "GfxOptions_SetStencilShadows",
    GfxOptions_SetBoolValue,
    &GfxOptions_tActiveOptions.isStencilShadows,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "GfxOptions_IsTextureCompression",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))GfxOptions_GetBoolValue,
    &GfxOptions_tActiveOptions.isTextureCompression,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "GfxOptions_SetTextureCompression",
    GfxOptions_SetBoolValue,
    &GfxOptions_tActiveOptions.isTextureCompression,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "GfxOptions_IsHighQualityForests",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))GfxOptions_GetBoolValue,
    &GfxOptions_tActiveOptions.isHighQualityForests,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "GfxOptions_SetHighQualityForests",
    GfxOptions_SetBoolValue,
    &GfxOptions_tActiveOptions.isHighQualityForests,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "GfxOptions_IsWindOnForests",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))GfxOptions_GetBoolValue,
    &GfxOptions_tActiveOptions.isWindOnForests,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "GfxOptions_SetWindOnForests",
    GfxOptions_SetBoolValue,
    &GfxOptions_tActiveOptions.isWindOnForests,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "GfxOptions_IsLensFlares",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))GfxOptions_GetBoolValue,
    &GfxOptions_tActiveOptions.isLensFlares,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "GfxOptions_SetLensFlares",
    GfxOptions_SetBoolValue,
    &GfxOptions_tActiveOptions.isLensFlares,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "GfxOptions_IsBulletHitEffects",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))GfxOptions_GetBoolValue,
    &GfxOptions_tActiveOptions.isBulletHitEffects,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "GfxOptions_SetBulletHitEffects",
    GfxOptions_SetBoolValue,
    &GfxOptions_tActiveOptions.isBulletHitEffects,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "GfxOptions_FillDetailLevelListBox",
    GfxOptions_FillDetailLevelListBox,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "GfxOptions_SetDetailLevelFromScript",
    GfxOptions_SetDetailLevelFromScript,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "GfxOptions_SetDetailLevelFromConfigFile",
    GfxOptions_SetDetailLevelFromConfigFile,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "GfxOptions_GetDetailLevelFromScript",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))GfxOptions_GetDetailLevelFromScript,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "GfxOptions_FillTextureDetailListBox",
    GfxOptions_FillTextureDetailListBox,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "GfxOptions_SetTextureDetailFromScript",
    GfxOptions_SetTextureDetailFromScript,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "GfxOptions_GetTextureDetailFromScript",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))GfxOptions_GetTextureDetailFromScript,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "GfxOptions_SetLODBias",
    GfxOptions_SetLODBias,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "GfxOptions_SetModelDetail",
    GfxOptions_SetModelDetail,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "GfxOptions_GetModelDetail",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))GfxOptions_GetModelDetail,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "GfxOptions_FillWaterQualityLevelListBox",
    GfxOptions_FillWaterQualityLevelListBox,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "GfxOptions_SetWaterQualityLevel",
    GfxOptions_SetWaterQualityLevel,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "GfxOptions_GetWaterQualityLevel",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))GfxOptions_GetWaterQualityLevel,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "GfxOptions_GetTerrainDetailLevel",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))GfxOptions_GetTerrainDetailLevel,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "GfxOptions_SetTerrainDetailLevel",
    GfxOptions_SetTerrainDetailLevel,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "GfxOptions_FillAntialiasingModeListBox",
    GfxOptions_FillAntialiasingModeListBox,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "GfxOptions_GetAntialiasingMode",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))GfxOptions_GetAntialiasingMode,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "GfxOptions_SetAntialiasingMode",
    GfxOptions_SetAntialiasingMode,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "GfxOptions_ConfigSetAntialiasingMode",
    GfxOptions_ConfigSetAntialiasingMode,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "GfxOptions_FillTextureFilteringModeListBox",
    GfxOptions_FillTextureFilteringModeListBox,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "GfxOptions_GetTextureFilteringMode",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))GfxOptions_GetTextureFilteringMode,
    nullptr,
    0,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "GfxOptions_SetTextureFilteringMode",
    GfxOptions_SetTextureFilteringMode,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    (char *)&g_zFontName_1.tQTaskRefList.ptTail,
    GfxOptions_ConfigSetTextureFilteringMode,
    nullptr,
    1,
    QSCRIPT_SYMBOLCLASS_FUNCTION,
    QSCRIPT_SYMBOLTYPE_VOID,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "DIRECT3DRENDER_FILTERINGTYPE_BILINEAR",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    nullptr,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "DIRECT3DRENDER_FILTERINGTYPE_TRILINEAR",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)1,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "DIRECT3DRENDER_FILTERINGTYPE_ANISOTROPIC",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)2,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "GFXOPTIONS_ANTIALIASING_DISABLED",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    nullptr,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "GFXOPTIONS_ANTIALIASING_X2",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)1,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "GFXOPTIONS_ANTIALIASING_X4",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)2,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "GFXOPTIONS_ANTIALIASING_X6",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)3,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "WATERRENDER_QUALITY_NORMAL",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    nullptr,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "WATERRENDER_QUALITY_HIGH",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)1,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "WATERRENDER_QUALITY_HIGHEST",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)2,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "GFXOPTIONS_DETAIL_HIGH",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    nullptr,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "GFXOPTIONS_DETAIL_MEDIUM",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)1,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "GFXOPTIONS_DETAIL_LOW",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)2,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "GFXOPTIONS_DETAIL_CUSTOM",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)3,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "GFXOPTIONS_TEXTUREDETAIL_HIGH",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    nullptr,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "GFXOPTIONS_TEXTUREDETAIL_LOW",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)1,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
  Symbol_Register(
    "GFXOPTIONS_TEXTUREDETAIL_ULTRALOW",
    (struct Result_s *(__cdecl *)(struct Result_s *__struct_ptr, void *, struct ArgList_s *))Script_ConstInt,
    (void *)2,
    4,
    QSCRIPT_SYMBOLCLASS_CONSTANT,
    QSCRIPT_SYMBOLTYPE_INT,
    QSCRIPT_SYMBOLLIFESPAN_INFINITE);
}

// source: j/0/gfxoptions.c:856  [size]
void __cdecl GfxOptions_Close()
{
  ;
}
